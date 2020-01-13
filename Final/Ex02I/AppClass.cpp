#include "AppClass.h"
using namespace Simplex;

void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 0.0f, 35.0f), //Position
		vector3(0.0f, 0.0f, 0.0f),	//Target
		AXIS_Y);					//Up

	m_pCameraMngr->SetCameraMode(BTO_CAMERAMODE::CAM_ORTHO_Z);

	for (uint i = 0; i < 6; ++i)
	{
		//Positions
		m_lPosition.push_back(vector3(vector2(glm::linearRand(vector3(-6.0f), vector3(6.0f))),0.0f));

		//Orientations
		float angle = glm::linearRand(-180.0f, 180.0f);
		vector3 axis = glm::normalize(glm::linearRand(vector3(0.0f), vector3(1.0f)));
		quaternion q = glm::angleAxis(angle, axis);
		m_lOrientation.push_back(q);
	}
	
	matrix4 m4Transform = glm::translate(vector3(3.0f, 3.0f, 0.0f)) * glm::translate(m_lPosition[0]) * ToMatrix4(m_lOrientation[0]);
	m_pEntityMngr->AddEntity("Minecraft\\Cow.obj", "Cow", m4Transform);
	m4Transform = glm::translate(vector3(3.0f, 3.0f, 0.0f)) * glm::translate(m_lPosition[1]) * ToMatrix4(m_lOrientation[1]);
	m_pEntityMngr->AddEntity("Minecraft\\Creeper.obj", "Creeper", m4Transform);
	m4Transform = glm::translate(vector3(3.0f, 3.0f, 0.0f)) * glm::translate(m_lPosition[2]) * ToMatrix4(m_lOrientation[2]);
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube", m4Transform);
	m4Transform = glm::translate(vector3(3.0f, 3.0f, 0.0f)) * glm::translate(m_lPosition[3]) * ToMatrix4(m_lOrientation[3]);
	m_pEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve", m4Transform);
	m4Transform = glm::translate(vector3(3.0f, 3.0f, 0.0f)) * glm::translate(m_lPosition[4]) * ToMatrix4(m_lOrientation[4]);
	m_pEntityMngr->AddEntity("Minecraft\\Zombie.obj", "Zombie", m4Transform);
	m4Transform = glm::translate(vector3(3.0f, 3.0f, 0.0f)) * glm::translate(m_lPosition[5]) * ToMatrix4(m_lOrientation[5]);
	m_pEntityMngr->AddEntity("Minecraft\\Pig.obj", "Pig", m4Transform);

	m_pRoot = new MyQuadrant(3, 1, false);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	//draw a reference grid
	//m_pMeshMngr->AddGridToRenderList();
	m_pRoot->Display();

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();

	//draw gui,
	DrawGUI();

	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Release MyEntityManager
	MyEntityManager::ReleaseInstance();

	//release GUI
	ShutdownGUI();
}