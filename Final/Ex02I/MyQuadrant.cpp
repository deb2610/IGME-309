#include "MyQuadrant.h"
using namespace Simplex;
void MyQuadrant::Resize(void)
{
	//Default values so the box can have an initial size
	m_fSize = 12.0f; //remember as a quadrant the size of x, y and z should be the same size. (the largest)
	m_v3Center = vector3(3.0f, 5.5f, 0.0f);
	m_v3Min = m_v3Center - (vector3(7.0f, 7.0f, 4.0f));
	m_v3Max = m_v3Center + (vector3(7.0f, 7.0f, 4.0f));
#pragma region Your Code Goes Here
	//Override the values of the previous values here, with the new calculated ones
	//for each entity if there x max is > current x max box.x = entity.maxX
	//std::cout <<  << std::endl;

	m_fSize = 100;
	m_v3Max = vector3(-m_fSize);
	m_v3Min = vector3(m_fSize);

	const int objCount = m_pEntityMngr->GetEntityCount();
	
	vector3 objects[6];
	//storeing the positions
	objects[0] = m_pEntityMngr->GetEntity(0)->GetPosition();
	objects[1] = m_pEntityMngr->GetEntity(1)->GetPosition();
	objects[2] = m_pEntityMngr->GetEntity(2)->GetPosition();
	objects[3] = m_pEntityMngr->GetEntity(3)->GetPosition();
	objects[4] = m_pEntityMngr->GetEntity(4)->GetPosition();
	objects[5] = m_pEntityMngr->GetEntity(5)->GetPosition();

	/*objects[0] = m_pEntityMngr->GetEntity(0)->GetRigidBody()->GetCenterGlobal();
	objects[1] = m_pEntityMngr->GetEntity(1)->GetRigidBody()->GetCenterGlobal();
	objects[2] = m_pEntityMngr->GetEntity(2)->GetRigidBody()->GetCenterGlobal();
	objects[3] = m_pEntityMngr->GetEntity(3)->GetRigidBody()->GetCenterGlobal();
	objects[4] = m_pEntityMngr->GetEntity(4)->GetRigidBody()->GetCenterGlobal();
	objects[5] = m_pEntityMngr->GetEntity(5)->GetRigidBody()->GetCenterGlobal();*/
	//getcenter
	float avgX = 0;
	float avgY = 0;
	float avgZ = 0;

	for (size_t i = 0; i < objCount; i++)
	{
		avgX += objects[i].x;
		avgY += objects[i].y;
		avgZ += objects[i].z;
	}

	avgX = avgX / objCount;
	avgY = avgY / objCount;
	avgZ = avgZ / objCount;

	m_v3Center = vector3(avgX, avgY, avgZ);

	//get size

	for (size_t i = 0; i < objCount; i++)
	{
		vector3 maxL = m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMaxGlobal();
		vector3 minL = m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMinGlobal();

		m_v3Min = m_v3Center - (vector3(0));
		m_v3Max = m_v3Center + (vector3(0));
		//checking the size bounds
		if ((maxL.x )> m_v3Max.x) {
			m_v3Max.x = maxL.x;
		}
		if ((minL.x) < m_v3Min.x) {
			m_v3Min.x = minL.x;
		}

		if ((maxL.y) > m_v3Max.y) {
			m_v3Max.y = maxL.y;
		}
		if ((minL.y) < m_v3Min.y) {
			m_v3Min.y = minL.y;
		}

		if ((maxL.z) > m_v3Max.z) {
			m_v3Max.z = maxL.z;
		}
		if ((minL.z) < m_v3Min.z) {
			m_v3Min.z = minL.z;
		}
	}
	//std::cout << "max: " << m_v3Max.x << " " << m_v3Max.y << " " << m_v3Max.z << std::endl;
	//std::cout << "min: " << m_v3Min.x << " " << m_v3Min.y << " " << m_v3Min.z << std::endl;
	
	//get the extents

	float extents[6];
	extents[0] = glm::abs(m_v3Max.x);
	extents[1] = glm::abs(m_v3Max.y);
	extents[2] = glm::abs(m_v3Max.z);
	extents[3] = glm::abs(m_v3Min.x);
	extents[4] = glm::abs(m_v3Min.y);
	extents[5] = glm::abs(m_v3Min.z);
	m_fSize = 0;
	for (size_t i = 0; i < 6; i++)
	{
		//std::cout << "Extent "<< i << " " << extents[i] << std::endl;
		//std::cout << "m_fSize: " << m_fSize << std::endl;
		if (m_fSize > extents[i])
		{
			continue;
		}
		if (m_fSize < extents[i]);
		{

			m_fSize = extents[i]*1.55;
			//std::cout << "NEW m_fSize: " << m_fSize << std::endl << std::endl;
		}
	}

#pragma endregion
}
void MyQuadrant::Subdivide(void)
{
#pragma region DOES NOT NEED CHANGES
	//If this node has reach the maximum depth return without changes
	if (m_uLevel >= m_uMaxLevel)
		return;

	//If this node has been already subdivided return without changes
	if (m_uChildren != 0)
		return;

	//As this will have children it will not be a leaf
	m_uChildren = 0;
#pragma endregion


#pragma region Your Code Goes Here
	//Yikes i forgot how to actually code this b here is the gist of it in sudocode :)

	//for each entity we have
	//for (size_t i = 0; i < 6; i++)
	//{
		//if there is a entity in the space split the area in half
		//if(entity.position < octant.max && entity.position > octant.min){
		//	its in there oh boy. time to subdivide again
			//Subdivide();
		//}
	//}

	//this was my best shot at it but it exploded so *shrug*
/*
	for (size_t i = 0; i < 6; i++)
	{
		vector3 pos = m_pEntityMngr->GetEntity(i)->GetPosition();
		if (pos.x < m_v3Max.x && pos.x > m_v3Min.x)
		{
			if (pos.y < m_v3Max.y && pos.y > m_v3Min.y)
			{
				Subdivide();
			}
		}

	}*/

#pragma endregion


#pragma region DOES NOT NEED CHANGES
	for (uint nIndex = 0; nIndex < 4; nIndex++)
	{
		if (m_pChild[nIndex])
		{
			m_uChildren++;
			m_pChild[nIndex]->m_pRoot = m_pRoot;
			m_pChild[nIndex]->m_pParent = this;
			m_pChild[nIndex]->m_uLevel = m_uLevel + 1;
			m_pChild[nIndex]->m_bIgnoreARBB = m_bIgnoreARBB;
			if (m_pChild[nIndex]->ContainsMoreThan(m_uIdealEntityCount))
			{
				m_pChild[nIndex]->Subdivide();
			}
		}
	}
#pragma endregion
}
#pragma region DOES NOT NEED CHANGES
MyQuadrant::MyQuadrant(vector3 a_v3Center, float a_fSize)
{
	//Init the default values
	Init();
	m_v3Center = a_v3Center;
	m_fSize = a_fSize;

	vector3 v3Size = vector3(m_fSize / 2.0f, m_fSize / 2.0f, 3.0f);

	m_v3Min = m_v3Center - v3Size;
	m_v3Max = m_v3Center + v3Size;

	m_uQuadrantCount++;
}
bool MyQuadrant::IsColliding(uint a_uRBIndex)
{
	//If flag is enabled don't check for ARBBs
	if(m_bIgnoreARBB)
		return true;

	uint nObjectCount = m_pEntityMngr->GetEntityCount();
	//If the index given is larger than the number of elements in the bounding object there is no collision
	if (a_uRBIndex >= nObjectCount)
		return false;
	//As the Octree will never rotate or scale this collision is as easy as an Axis Alligned Bounding Box
	//Get all vectors in global space (the octant ones are already in Global)
	MyEntity* pEntity = m_pEntityMngr->GetEntity(a_uRBIndex);
	MyRigidBody* pRigidBody = pEntity->GetRigidBody();
	vector3 v3MinO = pRigidBody->GetMinGlobal();
	vector3 v3MaxO = pRigidBody->GetMaxGlobal();

	//Check for X
	if (m_v3Max.x < v3MinO.x)
		return false;
	if (m_v3Min.x > v3MaxO.x)
		return false;

	//Check for Y
	if (m_v3Max.y < v3MinO.y)
		return false;
	if (m_v3Min.y > v3MaxO.y)
		return false;

	//Check for Z
	if (m_v3Max.z < v3MinO.z)
		return false;
	if (m_v3Min.z > v3MaxO.z)
		return false;

	return true;
}
//  MyOctant
uint MyQuadrant::m_uQuadrantCount = 0;
uint MyQuadrant::m_uMaxLevel = 3;
uint MyQuadrant::m_uIdealEntityCount = 5;
uint MyQuadrant::GetOctantCount(void){ return m_uQuadrantCount; }
void MyQuadrant::Init(void)
{
	m_uChildren = 0;

	m_fSize = 0.0f;

	m_uID = m_uQuadrantCount;
	m_uLevel = 0;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();

	m_pRoot = nullptr;
	m_pParent = nullptr;

	bool m_bIgnoreARBB = false;

	for (uint n = 0; n < 4; n++)
	{
		m_pChild[n] = nullptr;
	}
}
void MyQuadrant::Swap(MyQuadrant& other)
{
	std::swap(m_uChildren, other.m_uChildren);

	std::swap(m_fSize, other.m_fSize);
	std::swap(m_uID, other.m_uID);
	std::swap(m_pRoot, other.m_pRoot);
	std::swap(m_lChild, other.m_lChild);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();

	std::swap(m_uLevel, other.m_uLevel);
	std::swap(m_pParent, other.m_pParent);
	for (uint i = 0; i < 8; i++)
	{
		std::swap(m_pChild[i], other.m_pChild[i]);
	}
}
MyQuadrant * MyQuadrant::GetParent(void) { return m_pParent; }
void MyQuadrant::Release(void)
{
	//this is a special kind of release, it will only happen for the root
	if (m_uLevel == 0)
	{
		KillBranches();
	}
	m_uChildren = 0;
	m_fSize = 0.0f;
	m_EntityList.clear();
	m_lChild.clear();
}
//The big 3
MyQuadrant::MyQuadrant(uint a_nMaxLevel, uint a_nIdealEntityCount, bool a_bIgnoreARBB)
{
	//Init the default values
	Init();

	m_uQuadrantCount = 0;
	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = a_nIdealEntityCount;
	m_uID = m_uQuadrantCount;

	m_pRoot = this;
	m_lChild.clear();

	m_bIgnoreARBB = a_bIgnoreARBB;

	Resize();

	m_uQuadrantCount++;

	ConstructTree(m_uMaxLevel);
}
MyQuadrant::MyQuadrant(MyQuadrant const& other)
{
	m_uChildren = other.m_uChildren;
	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_fSize = other.m_fSize;
	m_uID = other.m_uID;
	m_uLevel = other.m_uLevel;
	m_pParent = other.m_pParent;

	m_pRoot, other.m_pRoot;
	m_lChild, other.m_lChild;

	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();

	for (uint i = 0; i < 4; i++)
	{
		m_pChild[i] = other.m_pChild[i];
	}
}
MyQuadrant& MyQuadrant::operator=(MyQuadrant const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyQuadrant temp(other);
		Swap(temp);
	}
	return *this;
}
MyQuadrant::~MyQuadrant() { Release(); };
//Accessors
float MyQuadrant::GetSize(void) { return m_fSize; }
vector3 MyQuadrant::GetCenterGlobal(void) { return m_v3Center; }
vector3 MyQuadrant::GetMinGlobal(void) { return m_v3Min; }
vector3 MyQuadrant::GetMaxGlobal(void) { return m_v3Max; }
//--- Non Standard Singleton Methods
void MyQuadrant::Display(uint a_nIndex, vector3 a_v3Color)
{
	if (m_uID == a_nIndex)
	{
		m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) *
			glm::scale(vector3(m_fSize)), a_v3Color, RENDER_WIRE);

		return;
	}
	for (uint nIndex = 0; nIndex < m_uChildren; nIndex++)
	{
		m_pChild[nIndex]->Display(a_nIndex);
	}
}
void MyQuadrant::Display(vector3 a_v3Color)
{
	for (uint nIndex = 0; nIndex < m_uChildren; nIndex++)
	{
		m_pChild[nIndex]->Display(a_v3Color);
	}
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) *
		glm::scale(vector3(m_fSize, m_fSize, 3.0f)), a_v3Color, RENDER_WIRE);
}
MyQuadrant * MyQuadrant::GetChild(uint a_nChild)
{
	if (a_nChild > 3) return nullptr;
	return m_pChild[a_nChild];
}
bool MyQuadrant::IsLeaf(void) { return m_uChildren == 0; }
bool MyQuadrant::ContainsMoreThan(uint a_nEntities)
{
	uint nCount = 0;
	uint nObjectCount = m_pEntityMngr->GetEntityCount();
	for (uint n = 0; n < nObjectCount; n++)
	{
		if (IsColliding(n))
			nCount++;
		if (nCount > a_nEntities)
			return true;
	}
	return false;
}
void MyQuadrant::KillBranches(void)
{
	//Solution for an Assignment; code unnecessary for this test
}
void MyQuadrant::DisplayLeafs(vector3 a_v3Color)
{
	//Solution for an Assignment; code unnecessary for this test
}
void MyQuadrant::ClearEntityList(void)
{
	//Solution for an Assignment; code unnecessary for this test
}
void MyQuadrant::ConstructTree(uint a_nMaxLevel)
{
	//If this method is tried to be applied to something else
	//other than the root, don't.
	if (m_uLevel != 0)
		return;

	m_uMaxLevel = a_nMaxLevel;

	m_uQuadrantCount = 1;
	
	//ClearEntityList();
	m_EntityList.clear();

	//clear the tree
	KillBranches();
	m_lChild.clear();

	//If the base tree
	if (ContainsMoreThan(m_uIdealEntityCount))
	{
		Subdivide();
	}

	//Add octant ID to Entities
	AssignIDtoEntity();

	//construct the list of objects
	ConstructList();
}
void MyQuadrant::AssignIDtoEntity(void)
{
	//Solution for an Assignment; code unnecessary for this test
}
void MyQuadrant::ConstructList(void)
{
	//Solution for an Assignment; code unnecessary for this test
}
#pragma endregion
