#include "MyOctant.h"

using namespace Simplex;

uint MyOctant::m_uOctantCount = 0;
uint MyOctant::m_uMaxLevel = 3;
uint MyOctant::m_uIdealEntityCount = 5;
uint MyOctant::GetOctantCount(void) { return m_uOctantCount; }
//DEFAULT DATA
void MyOctant::Init(void) {
	//stuff
	m_uChildren = 0;
	m_fSize = 0.0f;
	m_uID = m_uOctantCount;
	m_uLevel = 0;

	//vectors
	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();

	m_pRoot = nullptr;
	m_pParent = nullptr;
	for (size_t i = 0; i < 8; i++)
	{
		m_pChild[i] = nullptr;
	}

}
//swaps an octant with another
void MyOctant::Swap(MyOctant& other) {
	std::swap(m_uChildren, other.m_uChildren);
	std::swap(m_fSize, other.m_fSize);
	std::swap(m_uID,other.m_uID);
	std::swap(m_pRoot,other.m_pRoot);
	std::swap(m_lChild, other.m_lChild);
	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min,other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);
	std::swap(m_uLevel, other.m_uLevel);
	std::swap(m_pParent, other.m_pParent);

	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();
	for (size_t i = 0; i < 8; i++)
	{
		std::swap(m_pChild[i], other.m_pChild[i]);
	}
}
//returns parent octant
MyOctant * MyOctant::GetParent(void) {
	return m_pParent;
}
//special delet
void MyOctant::Release(void) {
	//root release
	if (m_uLevel == 0)
	{
		KillBranches();
	}
	m_uChildren = 0;
	m_fSize = 0.0;
	m_EntityList.clear();
	m_lChild.clear();
}
//rule of threes
MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount) {
	//call init to get starting values
	Init();

	m_uOctantCount = 0;
	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = a_nIdealEntityCount;
	m_uID = m_uOctantCount;

	m_pRoot = this;
	m_lChild.clear();

	//holds all of the minmax bouding objects
	std::vector<vector3> lMinMax;

	uint nObjects = m_pEntityMngr->GetEntityCount();
	for (size_t i = 0; i < nObjects; i++)
	{
		MyEntity* pEntity = m_pEntityMngr->GetEntity(i);
		MyRigidBody* pRigidBody = pEntity->GetRigidBody();
		lMinMax.push_back(pRigidBody->GetMinGlobal());
		lMinMax.push_back(pRigidBody->GetMaxGlobal());
	}
	MyRigidBody* pRigidBody = new MyRigidBody(lMinMax);

	vector3 vHalfWidth = pRigidBody->GetHalfWidth();
	float fMax = vHalfWidth.x;
	for (size_t i = 1; i < 3; i++)
	{
		if (fMax < vHalfWidth[i])
		{
			fMax = vHalfWidth[i];
		}
	}
	vector3 v3Center = pRigidBody->GetCenterLocal();
	lMinMax.clear();
	SafeDelete(pRigidBody);

	m_fSize = fMax * 2.0f;
	m_v3Center = v3Center;
	m_v3Min = m_v3Center - (vector3(fMax));
	m_v3Max = m_v3Center + (vector3(fMax));

	m_uOctantCount++;

	ConstructTree(m_uMaxLevel);
}
//rule of threes
MyOctant::MyOctant(vector3 a_v3Center, float a_fSize) {

	Init();
	m_v3Center = a_v3Center;
	m_fSize = a_fSize;

	m_v3Min = m_v3Center - (vector3(m_fSize)/2.0f);
	m_v3Max = m_v3Center + (vector3(m_fSize)/2.0f);

	m_uOctantCount++;
}
//rule of threes
MyOctant::MyOctant(MyOctant const& other) {

	m_uChildren = other.m_uChildren;
	m_v3Center = other.m_v3Center;
	m_v3Max = other.m_v3Max;
	m_v3Min = other.m_v3Min;
	m_fSize = other.m_fSize;
	m_uID = other.m_uID;
	m_uLevel = other.m_uLevel;
	m_pParent = other.m_pParent;
	m_pRoot = other.m_pRoot;
	m_lChild = other.m_lChild;

	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();

	for (size_t i = 0; i < 8; i++)
	{
		m_pChild[i], other.m_pChild[i];
	}
}
//rule of threes
MyOctant& MyOctant::operator=(MyOctant const& other) {
	if (this != &other)
	{
		Release();
		Init();
		MyOctant temp(other);
		Swap(temp);
	}
	return *this;
}
//delet
MyOctant::~MyOctant() {
	Release(); 
}
//accessors
float MyOctant::GetSize(void) {
	return m_fSize;
}
vector3 MyOctant::GetCenterGlobal(void){
	return m_v3Center;
}
vector3 MyOctant::GetMaxGlobal(void){
	return m_v3Max;
}
vector3 MyOctant::GetMinGlobal(void){
	return m_v3Min;
}
//displays the yellow wires
void MyOctant::Display(uint a_nIndex,vector3 a_v3Color) {
	if (m_uID == a_nIndex)
	{
		m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize)), a_v3Color, RENDER_WIRE);
		return;
	}
	for (size_t i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->Display(a_nIndex);
	}
}
//displays the yellow wires
void MyOctant::Display(vector3 a_v3Color) {
	for (size_t i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->Display(a_v3Color);
	}
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize)), a_v3Color, RENDER_WIRE);
}
//this breaks down the oct into smaller ones. also a juicy method
void MyOctant::Subdivide(void) {
	if (m_uLevel >= m_uMaxLevel)
	{
		return;
	}
	if (m_uChildren != 0) {
		return;
	}
	m_uChildren = 8;
	float fSize = m_fSize / 4.0f;
	float fSizeD = fSize * 2.0f;
	vector3 v3Center;

	//octant 0 - bottom left back
	v3Center = m_v3Center;
	v3Center.x -= fSize;
	v3Center.y -= fSize;
	v3Center.z -= fSize;
	//create a new octant
	m_pChild[0] = new MyOctant(v3Center, fSizeD);

	//octant 1 - bottom right back
	v3Center.x += fSizeD;
	//create a new octant
	m_pChild[1] = new MyOctant(v3Center, fSizeD);
	
	//octant 2 - bottom right front
	v3Center.z += fSizeD;
	//create a new octant
	m_pChild[2] = new MyOctant(v3Center, fSizeD);
	
	//octant 3 - bottom left front
	v3Center.x -= fSizeD;
	//create a new octant
	m_pChild[3] = new MyOctant(v3Center, fSizeD);
	
	//octant 4 - top left front
	v3Center.y += fSizeD;
	//create a new octant
	m_pChild[4] = new MyOctant(v3Center, fSizeD);
	
	//octant 5 - top left back
	v3Center.z -= fSizeD;
	//create a new octant
	m_pChild[5] = new MyOctant(v3Center, fSizeD);
	
	//octant 6 - top right back
	v3Center.x += fSizeD;
	//create a new octant
	m_pChild[6] = new MyOctant(v3Center, fSizeD);

	//octant 7 - top right back
	v3Center.z += fSizeD;
	//create a new octant
	m_pChild[7] = new MyOctant(v3Center, fSizeD);

	for (size_t i = 0; i < 8; i++)
	{
		m_pChild[i]->m_pRoot = m_pRoot;
		m_pChild[i]->m_pParent = this;
		m_pChild[i]->m_uLevel = m_uLevel + 1;
		if (m_pChild[i]->ContainsMoreThan(m_uIdealEntityCount))
		{
			m_pChild[i]->Subdivide();
		}
	}

}
//gets the children
MyOctant * MyOctant::GetChild(uint a_nChild) {
	if (a_nChild >7)
	{
		return nullptr;
	}
	return m_pChild[a_nChild];
}
//checks the collions to see if an object is within an octant
bool MyOctant::IsColliding(uint a_uRBIndex) {
	uint nObjectCount = m_pEntityMngr->GetEntityCount();

	if (a_uRBIndex>=nObjectCount)
	{
		return false;
	}
	MyEntity* pEntity = m_pEntityMngr->GetEntity(a_uRBIndex);
	MyRigidBody* pRigidBody = pEntity->GetRigidBody();
	vector3 v3MinG = pRigidBody->GetMinGlobal();
	vector3 v3MaxG = pRigidBody->GetMaxGlobal();

	//min max checks

	//x
	if (m_v3Max.x < v3MaxG.x)
	{
		return false;
	}
	if (m_v3Min.x > v3MinG.x)
	{
		return false;
	}
	//y
	if (m_v3Max.y < v3MaxG.y)
	{
		return false;
	}
	if (m_v3Min.y > v3MinG.y)
	{
		return false;
	}
	//z
	if (m_v3Max.z < v3MaxG.z)
	{
		return false;
	}
	if (m_v3Min.z > v3MinG.z)
	{
		return false;
	}
	return true;

}
//leafy boi
bool MyOctant::IsLeaf(void) {
	return m_uChildren == 0;
}
//compares
bool MyOctant::ContainsMoreThan(uint a_nEntities) {
	uint nCount = 0;
	uint nObjectCount = m_pEntityMngr->GetEntityCount();

	for (size_t i = 0; i < nObjectCount; i++)
	{
		if (IsColliding(i))
		{
			nCount++;
		}
		if (nCount > a_nEntities)
		{
			return true;
		}
	}
	return false;
}
//recursivly kills off children
void MyOctant::KillBranches(void) {
	for (size_t i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->KillBranches();
		delete m_pChild[i];
		m_pChild[i] = nullptr;
	}
	m_uChildren = 0;
}
//displays the small octants
void MyOctant::DisplayLeafs(vector3 a_v3Color) {
	uint nLeaf = m_lChild.size();
	for (size_t i = 0; i < nLeaf; i++)
	{
		m_lChild[i]->DisplayLeafs(a_v3Color);
	}
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize)), a_v3Color, RENDER_WIRE);
}
//destroys each childrens entory list and than its own
void MyOctant::ClearEntityList(void) {
	for (size_t i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->ClearEntityList();
	}
	m_EntityList.clear();
}
//creat the tree
void MyOctant::ConstructTree(uint a_nMaxLevel) {

	if (m_uLevel !=0)
	{
		return;
	}
	m_uMaxLevel = a_nMaxLevel;
	m_uOctantCount = 1;

	//clear a bunch of stuff
	m_EntityList.clear();
	KillBranches();
	m_lChild.clear();

	//break down the tree if base
	if (ContainsMoreThan(m_uIdealEntityCount))
	{
		Subdivide();
	}
	AssignIDtoEntity();
	ConstructList();
}
//this is the juicy bit. it assigns onjects to each octent if they collide
void MyOctant::AssignIDtoEntity(void) {
	for (size_t i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->AssignIDtoEntity();
	}
	//leafy boi
	if (m_uChildren == 0)
	{
		uint nEntities = m_pEntityMngr->GetEntityCount();
		for (size_t i = 0; i < nEntities; i++)
		{
			if (IsColliding(i))
			{
				m_EntityList.push_back(i);
				m_pEntityMngr->AddDimension(i, m_uID);
			}
		}
	}
}
//list construcor
void MyOctant::ConstructList(void) {
	for (size_t i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->ConstructList();
	}
	if (m_EntityList.size() > 0)
	{
		m_pRoot->m_lChild.push_back(this);
	}
}