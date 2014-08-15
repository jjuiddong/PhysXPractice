
#include "stdafx.h"
#include "SamplePreprocessor.h"
#include "SampleHelloWorld.h"
#include "SampleUtils.h"
#include "SampleConsole.h"
#include "RendererMemoryMacros.h"
#include "RenderMeshActor.h"

#include "PxPhysics.h"
#include "PxScene.h"
#include "PxRigidDynamic.h"
#include "PxShape.h"
#include "PxPhysicsAPI.h"
#include "RenderBoxActor.h"
#include "RendererShape.h"
#include "RenderComposition.h"


#include <SampleBaseInputEventIds.h>
#include <SamplePlatform.h>
#include <SampleUserInput.h>
#include <SampleUserInputIds.h>
#include <SampleUserInputDefines.h>

using namespace SampleRenderer;
using namespace SampleFramework;

REGISTER_SAMPLE(SampleHelloWorld, "SampleHelloWorld")


struct NodeGroup
{
	enum Enum
	{
		HEAD		= (1 << 0),
		BODY		= (1 << 1),
		L_ARM		= (1 << 2),
		R_ARM		= (1 << 3),
	};
};


///////////////////////////////////////////////////////////////////////////////

SampleHelloWorld::SampleHelloWorld(PhysXSampleApplication& app) :
	PhysXSample(app)
,	m_value1(1)
{
}

SampleHelloWorld::~SampleHelloWorld()
{
}

void SampleHelloWorld::onTickPreRender(float dtime)
{
	PhysXSample::onTickPreRender(dtime);
}

void SampleHelloWorld::onTickPostRender(float dtime)
{
	PhysXSample::onTickPostRender(dtime);
}

void SampleHelloWorld::customizeSceneDesc(PxSceneDesc& sceneDesc)
{
	sceneDesc.flags |= PxSceneFlag::eREQUIRE_RW_LOCK;
}

void SampleHelloWorld::newMesh(const RAWMesh& data)
{
}

static void gValue(Console* console, const char* text, void* userData)
{
	if(!text)
	{
		console->out("Usage: value <float>");
		return;
	}

	const float val = (float)::atof(text);
	printf("value: %f\n", val);
}

static void gExport(Console* console, const char* text, void* userData)
{
	if(!text)
	{
		console->out("Usage: export <filename>");
		return;
	}
}

static void gImport(Console* console, const char* text, void* userData)
{
	if(!text)
	{
		console->out("Usage: import <filename>");
		return;
	}
}

void SampleHelloWorld::onInit()
{
	if (getConsole())
	{
		getConsole()->addCmd("value", gValue);
		getConsole()->addCmd("export", gExport);
		getConsole()->addCmd("import", gImport);
	}

	PhysXSample::onInit();

	mApplication.setMouseCursorHiding(true);
	mApplication.setMouseCursorRecentering(true);
	mCameraController.init(PxVec3(0.0f, 10.0f, 0.0f), PxVec3(0.0f, 0.0f, 0.0f));
	mCameraController.setMouseSensitivity(0.5f);


	PxRigidDynamic* actor1 = NULL;
	const PxVec3 pos = getCamera().getPos();
	const PxVec3 vel = getCamera().getViewDir() * getDebugObjectsVelocity();
	actor1 = createSphere(pos, getDebugSphereObjectRadius(), &vel, mManagedMaterials[MATERIAL_GREEN], mDefaultDensity);

	PxRigidDynamic* actor2 = NULL;
	PxVec3 pos2 = getCamera().getPos();
	pos2.x += 1.f;
	actor2 = createSphere(pos2, getDebugSphereObjectRadius(), &vel, mManagedMaterials[MATERIAL_GREEN], mDefaultDensity);


	// Joint Test
	const float scale = 1.f;
	const float plankDepth = 2.f;
	//PxRevoluteJoint* j = PxRevoluteJointCreate(getPhysics(), 
	//PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
	PxSphericalJoint* j = PxSphericalJointCreate(getPhysics(), 
		actor1, PxTransform(PxVec3(0,0, plankDepth)*scale),
		actor2, PxTransform(PxVec3(0,0,-plankDepth)*scale));
	if(j)
		j->setProjectionLinearTolerance(.5f);

}


PxRigidDynamic*	createJointSphere(const PxVec3& pos, PxReal radius, const PxVec3* linVel, 
	RenderMaterial* material, PxReal density )
{


	return NULL;
}


void SampleHelloWorld::collectInputEvents(std::vector<const SampleFramework::InputEvent*>& inputEvents)
{
	PhysXSample::collectInputEvents(inputEvents);
	getApplication().getPlatform()->getSampleUserInput()->unregisterInputEvent(CAMERA_SPEED_INCREASE);
	getApplication().getPlatform()->getSampleUserInput()->unregisterInputEvent(CAMERA_SPEED_DECREASE);
    
	//touch events
	DIGITAL_INPUT_EVENT_DEF(PICKUP, WKEY_SPACE,			XKEY_1,			PS3KEY_1,		AKEY_UNKNOWN,	OSXKEY_1,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_1,			WIIUKEY_UNKNOWN		);
	DIGITAL_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT2, WKEY_2,			XKEY_1,			PS3KEY_1,		AKEY_UNKNOWN,	OSXKEY_1,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_1,			WIIUKEY_UNKNOWN		);
	DIGITAL_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT3, WKEY_3,			XKEY_1,			PS3KEY_1,		AKEY_UNKNOWN,	OSXKEY_1,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_1,			WIIUKEY_UNKNOWN		);
	DIGITAL_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT4, WKEY_4,			XKEY_1,			PS3KEY_1,		AKEY_UNKNOWN,	OSXKEY_1,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_1,			WIIUKEY_UNKNOWN		);
	DIGITAL_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT5, WKEY_5,			XKEY_1,			PS3KEY_1,		AKEY_UNKNOWN,	OSXKEY_1,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_1,			WIIUKEY_UNKNOWN		);
	DIGITAL_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT6, WKEY_6,			XKEY_1,			PS3KEY_1,		AKEY_UNKNOWN,	OSXKEY_1,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_1,			WIIUKEY_UNKNOWN		);
	DIGITAL_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT7, WKEY_7,			XKEY_1,			PS3KEY_1,		AKEY_UNKNOWN,	OSXKEY_1,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_1,			WIIUKEY_UNKNOWN		);
	DIGITAL_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT8, WKEY_8,			XKEY_1,			PS3KEY_1,		AKEY_UNKNOWN,	OSXKEY_1,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_1,			WIIUKEY_UNKNOWN		);
	DIGITAL_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT9, WKEY_9,			XKEY_1,			PS3KEY_1,		AKEY_UNKNOWN,	OSXKEY_1,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_1,			WIIUKEY_UNKNOWN		);
	DIGITAL_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT0, WKEY_0,			XKEY_1,			PS3KEY_1,		AKEY_UNKNOWN,	OSXKEY_1,		PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_1,			WIIUKEY_UNKNOWN		);

	TOUCH_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT,	"Throw Object", ABUTTON_5,	IBUTTON_5);
	TOUCH_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT2,	"Throw Object", ABUTTON_5,	IBUTTON_5);
	TOUCH_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT3,	"Throw Object", ABUTTON_5,	IBUTTON_5);
	TOUCH_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT4,	"Throw Object", ABUTTON_5,	IBUTTON_5);
	TOUCH_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT5,	"Throw Object", ABUTTON_5,	IBUTTON_5);
	TOUCH_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT6,	"Throw Object", ABUTTON_5,	IBUTTON_5);
	TOUCH_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT7,	"Throw Object", ABUTTON_5,	IBUTTON_5);
	TOUCH_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT8,	"Throw Object", ABUTTON_5,	IBUTTON_5);
	TOUCH_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT9,	"Throw Object", ABUTTON_5,	IBUTTON_5);
	TOUCH_INPUT_EVENT_DEF(SPAWN_DEBUG_OBJECT0,	"Throw Object", ABUTTON_5,	IBUTTON_5);



}

void SampleHelloWorld::helpRender(PxU32 x, PxU32 y, PxU8 textAlpha)
{
	Renderer* renderer = getRenderer();
	const PxU32 yInc = 18;
	const PxReal scale = 0.5f;
	const PxReal shadowOffset = 6.0f;
	const RendererColor textColor(255, 255, 255, textAlpha);
	const bool isMouseSupported = getApplication().getPlatform()->getSampleUserInput()->mouseSupported();
	const bool isPadSupported = getApplication().getPlatform()->getSampleUserInput()->gamepadSupported();
	const char* msg;

	if (isMouseSupported && isPadSupported)
		renderer->print(x, y += yInc, "Use mouse or right stick to rotate", scale, shadowOffset, textColor);
	else if (isMouseSupported)
		renderer->print(x, y += yInc, "Use mouse to rotate", scale, shadowOffset, textColor);
	else if (isPadSupported)
		renderer->print(x, y += yInc, "Use right stick to rotate", scale, shadowOffset, textColor);
	if (isPadSupported)
		renderer->print(x, y += yInc, "Use left stick to move",scale, shadowOffset, textColor);
	msg = mApplication.inputMoveInfoMsg("Press "," to move", CAMERA_MOVE_FORWARD,CAMERA_MOVE_BACKWARD, CAMERA_MOVE_LEFT, CAMERA_MOVE_RIGHT);
	if(msg)
		renderer->print(x, y += yInc, msg,scale, shadowOffset, textColor);
	msg = mApplication.inputInfoMsg("Press "," to move fast", CAMERA_SHIFT_SPEED, -1);
	if(msg)
		renderer->print(x, y += yInc, msg, scale, shadowOffset, textColor);
	msg = mApplication.inputInfoMsg("Press "," to throw an object", SPAWN_DEBUG_OBJECT, -1);
	if(msg)
		renderer->print(x, y += yInc, msg,scale, shadowOffset, textColor);
}

void SampleHelloWorld::descriptionRender(PxU32 x, PxU32 y, PxU8 textAlpha)
{
	bool print=(textAlpha!=0.0f);

	if(print)
	{
		Renderer* renderer = getRenderer();
		const PxU32 yInc = 18;
		const PxReal scale = 0.5f;
		const PxReal shadowOffset = 6.0f;
		const RendererColor textColor(255, 255, 255, textAlpha);

		char line1[256]="This sample demonstrates how to set up and simulate a PhysX";
		char line2[256]="scene.  Further, it illustrates the creation, simulation and";
		char line3[256]="collision of simple dynamic objects.";
		renderer->print(x, y+=yInc, line1, scale, shadowOffset, textColor);
		renderer->print(x, y+=yInc, line2, scale, shadowOffset, textColor);
		renderer->print(x, y+=yInc, line3, scale, shadowOffset, textColor);
	}
}

PxU32 SampleHelloWorld::getDebugObjectTypes() const
{
	return DEBUG_OBJECT_BOX | DEBUG_OBJECT_SPHERE | DEBUG_OBJECT_CAPSULE | DEBUG_OBJECT_CONVEX;
}


/**
 @brief 
 @date 2013-12-10
*/
bool SampleHelloWorld::GenerateHuman(const bool flag)
{
	const PxVec3 pos = getCamera().getPos() + (getCamera().getViewDir()*10.f);
	const PxVec3 vel = getCamera().getViewDir() * 20.f;

	//PxRigidDynamic* actor1 = createBox(pos, PxVec3(0.3f, 0.3f, 0.3f), &vel, getManageMaterial(MATERIAL_RED), 1.f);
	//PxRigidDynamic* actor2 = createBox(pos, PxVec3(0.8f, 0.3f, 0.8f), &vel, getManageMaterial(MATERIAL_YELLOW), 1.f);
	//PxRigidDynamic* actor3 = createBox(pos, PxVec3(1.f, 0.3f, 0.3f), &vel, getManageMaterial(MATERIAL_GREEN), 1.f);
	//PxRigidDynamic* actor3_1 = createBox(pos, PxVec3(0.1f, 0.1f, 0.1f), &vel, getManageMaterial(MATERIAL_RED), 1.f);
	//PxRigidDynamic* actor4 = createBox(pos, PxVec3(1.f, 0.3f, 0.3f), &vel, etManageMaterial(MATERIAL_BLUE), 1.f);
	//PxRigidDynamic* actor4_1 = createBox(pos, PxVec3(0.1f, 0.1f, 0.1f), &vel, getManageMaterial(MATERIAL_RED), 1.f);
	//PxRigidDynamic* actor5 = createBox(pos, PxVec3(1.f, 0.3f, 0.3f), &vel, getManageMaterial(MATERIAL_GREEN), 1.f);
	//PxRigidDynamic* actor6 = createBox(pos, PxVec3(1.f, 0.3f, 0.3f), &vel, getManageMaterial(MATERIAL_BLUE), 1.f);

	PxRigidDynamic* head = createSphere(pos+PxVec3(0,0,1.6f), 0.5f, NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* body = createBox(pos, PxVec3(1,.3f,1), NULL, getManageMaterial(MATERIAL_YELLOW), 1.f);

	PxRigidDynamic* left_shoulder_joint1 = createSphere(pos+PxVec3(1.4f,0,.7f), 0.3f, NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* left_shoulder_joint2 = createSphere(pos+PxVec3(2.0f,0,.7f), 0.3f, NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	//PxRigidDynamic* left_arm_joint1 = createSphere(pos+PxVec3(3.6f,0,.7f), 0.3f, &vel, getManageMaterial(MATERIAL_GREEN), 1.f);
	//PxRigidDynamic* left_arm_joint2 = createSphere(pos+PxVec3(3.4f,0,.7f), 0.3f, &vel, getManageMaterial(MATERIAL_BLUE), 1.f);
	PxRigidDynamic* left_arm_1 = createBox(pos+PxVec3(3.3f,0,.7f), PxVec3(1, 0.3f, 0.3f), NULL, getManageMaterial(MATERIAL_GREY), 1.f);
	//PxRigidDynamic* left_arm_2 = createBox(pos+PxVec3(4.4f,0,.7f), PxVec3(1, 0.3f, 0.3f), NULL, getManageMaterial(MATERIAL_RED), 1.f);
	PxRigidDynamic* left_pelvis_joint1 = createSphere(pos+PxVec3(.7f,0,-1.4f), 0.3f, NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* left_pelvis_joint2 = createSphere(pos+PxVec3(.7f,0,-2.0f), 0.3f, NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	PxRigidDynamic* left_leg_1 = createBox(pos+PxVec3(1,0,-3.3f), PxVec3(0.3f, 0.3f, 1), NULL, getManageMaterial(MATERIAL_GREY), 1.f);


	PxRigidDynamic* right_shoulder_joint1 = createSphere(pos+PxVec3(-1.4f,0,.7f), 0.3f, NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* right_shoulder_joint2 = createSphere(pos+PxVec3(-2.0f,0,.7f), 0.3f, NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	//PxRigidDynamic* right_arm_joint1 = createSphere(pos, 0.3f, &vel, getManageMaterial(MATERIAL_GREEN), 1.f);
	//PxRigidDynamic* right_arm_joint2 = createSphere(pos, 0.3f, &vel, getManageMaterial(MATERIAL_BLUE), 1.f);
	PxRigidDynamic* right_arm_1 = createBox(pos+PxVec3(-3.3f,0,.7f), PxVec3(1, 0.3f, 0.3f), NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	//PxRigidDynamic* right_arm_2 = createBox(PxVec3(pos.x+1.4f, pos.y, pos.z), PxVec3(1, 0.3f, 0.3f), NULL, getManageMaterial(MATERIAL_RED), 1.f);
	PxRigidDynamic* right_pelvis_joint1 = createSphere(pos+PxVec3(-.7f,0,-1.4f), 0.3f, NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* right_pelvis_joint2 = createSphere(pos+PxVec3(-.7f,0,-2.0f), 0.3f, NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	PxRigidDynamic* right_leg_1 = createBox(pos+PxVec3(-1,0,-3.3f), PxVec3(0.3f, 0.3f, 1), NULL, getManageMaterial(MATERIAL_BLUE), 1.f);

	//m_pHead = head;

	m_Rigids.push_back(left_shoulder_joint1);
	m_Rigids.push_back(left_shoulder_joint2);
	m_Rigids.push_back(left_pelvis_joint1);
	m_Rigids.push_back(left_pelvis_joint2);
	m_Rigids.push_back(right_shoulder_joint1);
	m_Rigids.push_back(right_shoulder_joint2);
	m_Rigids.push_back(right_pelvis_joint1);
	m_Rigids.push_back(right_pelvis_joint2);

 	const float scale = 1.f;
	// body - head
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		head, PxTransform(PxVec3(0,0,1.6f))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	// body - left shoulder
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		left_shoulder_joint1, PxTransform(PxVec3(1.4f,0,.7f))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	// left shoulder joint
	if (PxSphericalJoint* j = PxSphericalJointCreate(getPhysics(), 
		left_shoulder_joint1, PxTransform(PxVec3(0,0,0)*scale),
		left_shoulder_joint2, PxTransform(PxVec3(.6f,0,0)*scale)))
	{
		//if (flag)
		//{
		//	j->setLimitCone(PxJointLimitCone(0, PxPi/6, 0.01f));
		//	j->setSphericalJointFlag(PxSphericalJointFlag::eLIMIT_ENABLED, true);
		//}
		j->setProjectionLinearTolerance(0.1f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	// left shoulder - left arm
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		left_shoulder_joint2, PxTransform(PxVec3(0,0,0)*scale),
		left_arm_1, PxTransform(PxVec3(1.3f,0,0)*scale)))
	{
		j->setProjectionLinearTolerance(0);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}


	// body - left pelvis joint
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		left_pelvis_joint1, PxTransform(PxVec3(.7f,0,-1.4f))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	// left pelvis  joint
	if (PxSphericalJoint* j = PxSphericalJointCreate(getPhysics(), 
		left_pelvis_joint1, PxTransform(PxVec3(0,0,0)*scale),
		left_pelvis_joint2, PxTransform(PxVec3(0,0,-.6f)*scale)))
	{
		//if (flag)
		//{
		//	j->setLimitCone(PxJointLimitCone(0, PxPi/6, 0.01f));
		//	j->setSphericalJointFlag(PxSphericalJointFlag::eLIMIT_ENABLED, true);
		//}
		j->setProjectionLinearTolerance(0.1f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	// left pelvis joint - left leg
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		left_pelvis_joint2, PxTransform(PxVec3(0,0,0)*scale),
		left_leg_1, PxTransform(PxVec3(0,0,-1.3f)*scale)))
	{
		j->setProjectionLinearTolerance(0);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}



	// body - right shoulder
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		right_shoulder_joint1, PxTransform(PxVec3(-1.4f,0,.7f))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	// right shoulder joint
	if (PxSphericalJoint* j = PxSphericalJointCreate(getPhysics(), 
		right_shoulder_joint1, PxTransform(PxVec3(0,0,0)*scale),
		right_shoulder_joint2, PxTransform(PxVec3(-.6f,0,0)*scale)))
	{
		//if (flag)
		//{
		//	j->setLimitCone(PxJointLimitCone(0, PxPi/6, 0.01f));
		//	j->setSphericalJointFlag(PxSphericalJointFlag::eLIMIT_ENABLED, true);
		//}
		j->setProjectionLinearTolerance(0.1f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	// right shoulder - right arm
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		right_shoulder_joint2, PxTransform(PxVec3(0,0,0)*scale),
		right_arm_1, PxTransform(PxVec3(-1.3f,0,0)*scale)))
	{
		j->setProjectionLinearTolerance(0);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}


	// body - right pelvis joint
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		right_pelvis_joint1, PxTransform(PxVec3(-.7f,0,-1.4f))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}
	
	// right pelvis  joint
	if (PxSphericalJoint* j = PxSphericalJointCreate(getPhysics(), 
		right_pelvis_joint1, PxTransform(PxVec3(0,0,0)*scale),
		right_pelvis_joint2, PxTransform(PxVec3(0,0,-.6f)*scale)))
	{
		//if (flag)
		//{
		//	j->setLimitCone(PxJointLimitCone(0, PxPi/6, 0.01f));
		//	j->setSphericalJointFlag(PxSphericalJointFlag::eLIMIT_ENABLED, true);
		//}
		j->setProjectionLinearTolerance(0.1f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	// right pelvis joint - left leg
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		right_pelvis_joint2, PxTransform(PxVec3(0,0,0)*scale),
		right_leg_1, PxTransform(PxVec3(0,0,-1.3f)*scale)))
	{
		j->setProjectionLinearTolerance(0);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}



	// left arm
	//if (PxSphericalJoint* j = PxSphericalJointCreate(getPhysics(), 
	//	left_arm_joint1, PxTransform(PxVec3(0,0,0)*scale),
	//	left_arm_joint2, PxTransform(PxVec3(-.7f,0,0)*scale)))
	//{
	//	if (flag)
	//	{
	//		j->setLimitCone(PxJointLimitCone(PxPi/2, PxPi/6, 0.01f));
	//		j->setSphericalJointFlag(PxSphericalJointFlag::eLIMIT_ENABLED, true);
	//	}
	//	j->setProjectionLinearTolerance(0.5f);
	//}

	//if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
	//	left_arm_1, PxTransform(PxVec3(0,0,0)*scale),
	//	left_arm_joint1, PxTransform(PxVec3(1,0,0)*scale)))
	//{
	//	j->setProjectionLinearTolerance(.5f);
	//}

	//if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
	//	left_arm_2, PxTransform(PxVec3(-1.4f,0,0)*scale),
	//	left_arm_joint2, PxTransform(PxVec3(0,0,0)*scale)))
	//{
	//	j->setProjectionLinearTolerance(.5f);
	//}




	// right shoulder
	//if (PxSphericalJoint* j = PxSphericalJointCreate(getPhysics(), 
	//	right_shoulder_joint1, PxTransform(PxVec3(0,0,0)*scale),
	//	right_shoulder_joint2, PxTransform(PxVec3(-.7f,0,0)*scale)))
	//{
	//	if (flag)
	//	{
	//		j->setLimitCone(PxJointLimitCone(PxPi/2, PxPi/6, 0.01f));
	//		j->setSphericalJointFlag(PxSphericalJointFlag::eLIMIT_ENABLED, true);
	//	}
	//	j->setProjectionLinearTolerance(0.5f);
	//}

	//if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
	//	body, PxTransform(PxVec3(0,0,0)*scale),
	//	right_shoulder_joint1, PxTransform(PxVec3(-1,0,.7f)*scale)))
	//{
	//	j->setProjectionLinearTolerance(.5f);
	//}





	// right arm
	//if (PxSphericalJoint* j = PxSphericalJointCreate(getPhysics(), 
	//	right_arm_joint1, PxTransform(PxVec3(0,0,0)*scale),
	//	right_arm_joint2, PxTransform(PxVec3(-.7f,0,0)*scale)))
	//{
	//	if (flag)
	//	{
	//		j->setLimitCone(PxJointLimitCone(PxPi/2, PxPi/6, 0.01f));
	//		j->setSphericalJointFlag(PxSphericalJointFlag::eLIMIT_ENABLED, true);
	//	}
	//	j->setProjectionLinearTolerance(0.5f);
	//}

	//if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
	//	right_arm_1, PxTransform(PxVec3(1.4f,0,0)*scale),
	//	right_arm_joint1, PxTransform(PxVec3(0,0,0)*scale)))
	//{
	//	j->setProjectionLinearTolerance(.5f);
	//}

	//if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
	//	right_arm_2, PxTransform(PxVec3(-1.4f,0,0)*scale),
	//	right_arm_joint2, PxTransform(PxVec3(0,0,0)*scale)))
	//{
	//	j->setProjectionLinearTolerance(.5f);
	//}









	//// left arm
	//if (PxRevoluteJoint* j = PxRevoluteJointCreate(getPhysics(), 
	//	actor2, PxTransform(PxVec3(0,0,0)*scale),
	//	actor3_1, PxTransform(PxVec3(1.f,0, 0.8f)*scale)))
	//{
	//	PxJointAngularLimitPair limitPair(-PxPi/20.f, PxPi/20.f, 0.1f);
	//	j->setLimit(limitPair);
	//	j->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
	//	j->setDriveVelocity(10.0f);
	//	j->setProjectionLinearTolerance(0.5f);
	//}

	//if (PxSphericalJoint* j = PxSphericalJointCreate(getPhysics(), 
	//	actor3_1, PxTransform(PxVec3(0,0,0)*scale),
	//	actor3, PxTransform(PxVec3(2.f,0, 0.8f)*scale)))
	//{
	//	if (flag)
	//	{
	//		//PxJointAngularLimitPair limitPair(-PxPi/4, PxPi/4, 0.1f);
	//		//j->setLimit(limitPair);
	//		//j->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);

	//		j->setLimitCone(PxJointLimitCone(PxPi/2, PxPi/6, 0.01f));
	//		j->setSphericalJointFlag(PxSphericalJointFlag::eLIMIT_ENABLED, true);
	//	}

	//	j->setProjectionLinearTolerance(.5f);
	//}


	// righ arm
	//if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
	//	actor2, PxTransform(PxVec3(0,0,0)*scale),
	//	actor4_1, PxTransform(PxVec3(-0.95f,0, 0.8f)*scale)))
	//{
	//	j->setProjectionLinearTolerance(.5f);
	//}

	//if (PxSphericalJoint* j = PxSphericalJointCreate(getPhysics(), 
	//	actor4_1, PxTransform(PxVec3(0,0,0)*scale),
	//	actor4, PxTransform(PxVec3(-1.f,0, 0.8f)*scale)))
	//{
	//	j->setProjectionLinearTolerance(.5f);
	//}



	//PxTransform m1(PxVec3(0,0,0), PxQuat(3.14f/2.f, PxVec3(0,1,0)));
	//PxTransform m2(PxVec3(0.5f, 0, -2.f));

	//if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
	//	actor2, PxTransform(PxVec3(0,0,0)*scale),
	//	actor5, m1*m2))
	//{
	//	j->setProjectionLinearTolerance(.5f);
	//}

	//if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
	//	actor2, PxTransform(PxVec3(0,0,0)*scale),
	//	actor6, m1*PxTransform(PxVec3(-0.5f, 0, -2.f))) )
	//{
	//	j->setProjectionLinearTolerance(.5f);
	//}

	return true;
}


bool SampleHelloWorld::GenerateHuman2(const bool flag)
{
	const PxVec3 pos = getCamera().getPos() + (getCamera().getViewDir()*10.f);
	const PxVec3 vel = getCamera().getViewDir() * 20.f;

	PxVec3 inPosition = pos;
	PxReal yRot(0);
	PxRigidDynamic *mSubmarineActor;

	//PX_ASSERT(mSubmarineActor == NULL);

	std::vector<PxTransform> localPoses;
	std::vector<const PxGeometry*> geometries;

	// cabin
	PxSphereGeometry cabinGeom(1.5f);
	PxTransform	cabinPose = PxTransform(PxIdentity); 
	cabinPose.p.x = -0.5f;

	// engine
	PxBoxGeometry engineGeom(0.25f, 1.0f, 1.0f);
	PxTransform	enginePose = PxTransform(PxIdentity); 
	enginePose.p.x = cabinPose.p.x + cabinGeom.radius + engineGeom.halfExtents.x;

	// tanks
	PxCapsuleGeometry tankGeom(0.5f, 1.8f);
	PxTransform	tank1Pose = PxTransform(PxIdentity); 
	tank1Pose.p = PxVec3(0,-cabinGeom.radius, cabinGeom.radius);
	PxTransform	tank2Pose = PxTransform(PxIdentity); 
	tank2Pose.p = PxVec3(0,-cabinGeom.radius, -cabinGeom.radius);

	localPoses.push_back(cabinPose);
	geometries.push_back(&cabinGeom);
	localPoses.push_back(enginePose);
	geometries.push_back(&engineGeom);
	localPoses.push_back(tank1Pose);
	geometries.push_back(&tankGeom);
	localPoses.push_back(tank2Pose);
	geometries.push_back(&tankGeom);

	// put the shapes together into one actor
	mSubmarineActor = createCompound(inPosition, localPoses, geometries, 0,  getManageMaterial(MATERIAL_YELLOW), 
		1.0f)->is<PxRigidDynamic>();

	//if(!mSubmarineActor) fatalError("createCompound failed!");

	//disable the current and buoyancy effect for the sub.
	//mSubmarineActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);

	// set the filtering group for the submarine
	//setupFiltering(mSubmarineActor, FilterGroup::eSUBMARINE, FilterGroup::eMINE_HEAD | FilterGroup::eMINE_LINK);

	mSubmarineActor->setLinearDamping(0.15f);
	mSubmarineActor->setAngularDamping(15.0f);

	PxTransform globalPose; 
	globalPose.p = inPosition;
	globalPose.q = PxQuat(yRot, PxVec3(0,1,0));
	mSubmarineActor->setGlobalPose(globalPose);

	mSubmarineActor->setCMassLocalPose(PxTransform(PxIdentity));

	return true;
}


/**
 @brief generate snowMan
 @date 2013-12-03
*/
bool SampleHelloWorld::GenerateHuman3(const bool flag)
{
	const PxVec3 pos = getCamera().getPos() + (getCamera().getViewDir()*10.f);
	const PxVec3 vel = getCamera().getViewDir() * 20.f;

	PxRigidDynamic* snowmanActor = getPhysics().createRigidDynamic(PxTransform(pos));
	//if(!snowmanActor)
	//	fatalError("create snowman actor failed");

	PxMaterial&	material = getDefaultMaterial();
	PxShape* armL = NULL; PxShape* armR = NULL;

	{
		PxShape* shape = NULL;
		shape = snowmanActor->createShape(PxSphereGeometry(.2),material);
		shape->setLocalPose(PxTransform(PxVec3(0,-.29,0)));
		PxRigidBodyExt::updateMassAndInertia(*snowmanActor,10);

		shape = snowmanActor->createShape(PxSphereGeometry(.5),material);
		shape = snowmanActor->createShape(PxSphereGeometry(.4),material);
		shape->setLocalPose(PxTransform(PxVec3(0,.6,0)));

		shape = snowmanActor->createShape(PxSphereGeometry(.3),material);
		shape->setLocalPose(PxTransform(PxVec3(0,1.1,0)));

		armL = snowmanActor->createShape(PxCapsuleGeometry(.1,.1),material);
		armL->setLocalPose(PxTransform(PxVec3(-.4,.7,0)));

		armR = snowmanActor->createShape(PxCapsuleGeometry(.1,.1),material);
		armR->setLocalPose(PxTransform(PxVec3( .4,.7,0)));
	}

	createRenderObjectsFromActor(snowmanActor, getManageMaterial(MATERIAL_GREY));

	getActiveScene().addActor(*snowmanActor);

	return true;
}


/**
 @brief 
 @date 2013-12-03
*/
bool SampleHelloWorld::GenerateHuman4(const bool flag)
{
	const PxVec3 pos = getCamera().getPos() + (getCamera().getViewDir()*10.f);
	const PxVec3 vel = getCamera().getViewDir() * 20.f;

	PxRigidDynamic* head = createSphere(pos+PxVec3(0,0,0), 0.5f, NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* body = createBox(pos+PxVec3(0,-2.5f,0), PxVec3(1,2,0.8f), NULL, getManageMaterial(MATERIAL_YELLOW), 10.f);

	// body - head
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		head, PxTransform(PxVec3(0,0,0)),
		body, PxTransform(PxVec3(0,2.5f,0))) )
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	//head->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	//body->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	setCollisionGroup(head, NodeGroup::HEAD);
	setCollisionGroup(body, NodeGroup::BODY);

	PxRigidDynamic* left_shoulder_joint1 = createSphere(pos+PxVec3(-1.4f,0,.7f), 0.3f, NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* left_shoulder_joint2 = createSphere(pos+PxVec3(-2.0f,0,.7f), 0.3f, NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	PxRigidDynamic* left_arm_1 = createBox(pos+PxVec3(-3.3f,0,.7f), PxVec3(1, 0.3f, 0.3f), NULL, getManageMaterial(MATERIAL_GREY), 1.f);

	setCollisionGroup(left_arm_1, NodeGroup::L_ARM);
	//left_shoulder_joint1->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	//left_shoulder_joint2->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);


	float scale = 1.f;

	// body - left shoulder
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		left_shoulder_joint1, PxTransform(PxVec3(1.4f,-2,0))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	// left shoulder joint
	if (PxSphericalJoint* j = PxSphericalJointCreate(getPhysics(), 
		left_shoulder_joint1, PxTransform(PxVec3(0,0,0)*scale),
		left_shoulder_joint2, PxTransform(PxVec3(.6f,0,0)*scale)))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	// left shoulder - left arm
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		left_shoulder_joint2, PxTransform(PxVec3(0,0,0)*scale),
		left_arm_1, PxTransform(PxVec3(1.3f,0,0)*scale)))
	{
		j->setProjectionLinearTolerance(0);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}


	// right
	PxRigidDynamic* right_shoulder_joint1 = createSphere(pos+PxVec3(1.4f,0,.7f), 0.3f, NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	PxRigidDynamic* right_shoulder_joint2 = createSphere(pos+PxVec3(2.0f,0,.7f), 0.3f, NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	PxRigidDynamic* right_arm_1 = createBox(pos+PxVec3(3.3f,0,.7f), PxVec3(1, 0.3f, 0.3f), NULL, getManageMaterial(MATERIAL_BLUE), 1.f);

	setCollisionGroup(right_arm_1, NodeGroup::R_ARM);

	// body - left shoulder
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		right_shoulder_joint1, PxTransform(PxVec3(-1.4f,-2,0))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	// left shoulder joint
	if (PxSphericalJoint* j = PxSphericalJointCreate(getPhysics(), 
		right_shoulder_joint1, PxTransform(PxVec3(0,0,0)*scale),
		right_shoulder_joint2, PxTransform(PxVec3(-.6f,0,0)*scale)))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	// left shoulder - left arm
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		right_shoulder_joint2, PxTransform(PxVec3(0,0,0)*scale),
		right_arm_1, PxTransform(PxVec3(-1.3f,0,0)*scale)))
	{
		j->setProjectionLinearTolerance(0);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	//setupFiltering(left_arm_1, FilterGroup::eSUBMARINE, FilterGroup::eMINE_HEAD | FilterGroup::eMINE_LINK);
	//setupFiltering(body, FilterGroup::eMINE_HEAD, FilterGroup::eSUBMARINE);

	//m_pHead = head;
	m_Rigids.push_back(left_shoulder_joint1);
	m_Rigids.push_back(left_shoulder_joint2);
	//m_Joints.push_back(left_pelvis_joint1);
	//m_Joints.push_back(left_pelvis_joint2);
	m_Rigids.push_back(right_shoulder_joint1);
	m_Rigids.push_back(right_shoulder_joint2);
	//m_Joints.push_back(right_pelvis_joint1);
	//m_Joints.push_back(right_pelvis_joint2);
/**/

	return true;
}



/**
 @brief 
 @date 2014-02-10
*/
void quatRotationArc(PxQuat &q, const PxVec3& v0, const PxVec3& v1)
{
	PxVec3 c = v1.cross(v0);
	//cross(&c, v0, v1);
	//real s = sqrtf((1.0f+dot(v0,v1))*2.0f);
	double s = sqrtf((1.0f+v0.dot(v1))*2.0f);
	q.x = c.x/s;
	q.y = c.y/s;
	q.z = c.z/s;
	q.w = s/2.0f;
}



/**
 @brief 
 @date 2013-12-03
*/
bool SampleHelloWorld::GenerateHuman5(const bool flag)
{
	const PxVec3 pos = getCamera().getPos() + (getCamera().getViewDir()*10.f);
	const PxVec3 vel = getCamera().getViewDir() * 20.f;

	PxRigidDynamic* body = createBox(pos+PxVec3(0,0,0), PxVec3(0.3f,0.3f,0.3f), NULL, getManageMaterial(MATERIAL_YELLOW), 1.f);

	PxRigidDynamic* left_shoulder_joint1 = createBox(pos+PxVec3(0,-1.f,0), PxVec3(0.3f,0.3f,0.3f), NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	//PxRigidDynamic* left_shoulder_joint2 = createBox(pos+PxVec3(-2.0f,0,.7f), PxVec3(0.3f,0.3f,0.3f), NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	//PxRigidDynamic* left_arm_1 = createBox(pos+PxVec3(-3.3f,0,.7f), PxVec3(1, 0.3f, 0.3f), NULL, getManageMaterial(MATERIAL_GREY), 1.f);

	//setCollisionGroup(left_arm_1, NodeGroup::L_ARM);
	body->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	//left_shoulder_joint2->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);

	PxVec3 origDir(0,1,0);
	PxVec3 gravDir(0.2f, 0.9f,0);
	gravDir.normalize();
	PxQuat grav;
	quatRotationArc(grav, origDir, gravDir);

	// test quaternion
	PxTransform tm = PxTransform(PxQuat(0,PxVec3(0,0,1))) * PxTransform(PxVec3(0,0,0));
	PxTransform tm2 = PxTransform(PxVec3(0,-1,0)) * PxTransform(PxQuat(1,PxVec3(0,1,0))) * PxTransform(grav);;
	//PxTransform tm2 = PxTransform(PxVec3(1,0,0)) * PxTransform(PxQuat(1.3f,PxVec3(0,0,1)));

	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), body, tm, left_shoulder_joint1, tm2))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	//// left shoulder joint
	//if (PxSphericalJoint* j = PxSphericalJointCreate(getPhysics(), 
	//	left_shoulder_joint1, PxTransform(PxVec3(0,0,0)),
	//	left_shoulder_joint2, PxTransform(PxVec3(1,0,0))))
	//{
	//	if (flag)
	//	{
	//		j->setLimitCone(PxJointLimitCone(PxPi/2, PxPi/6, PxSpring(0,0)));
	//		j->setSphericalJointFlag(PxSphericalJointFlag::eLIMIT_ENABLED, true);
	//	}
	//	j->setProjectionLinearTolerance(0.0f);
	//	j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	//}

	//// left shoulder - left arm
	//if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
	//	left_shoulder_joint2, PxTransform(PxVec3(0,0,0)),
	//	left_arm_1, PxTransform(PxVec3(1.3f,0,0))))
	//{
	//	j->setProjectionLinearTolerance(0);
	//	j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	//}

	//m_Rigids.push_back(left_shoulder_joint1);
	//m_Rigids.push_back(left_shoulder_joint2);

	return true;
}


/**
 @brief joint test
 @date 2013-12-04
*/
bool SampleHelloWorld::GenerateHuman6(const bool flag)
{
	const PxVec3 pos = getCamera().getPos() + (getCamera().getViewDir()*10.f);
	const PxVec3 vel = getCamera().getViewDir() * 20.f;

	PxRigidDynamic* body = createBox(pos+PxVec3(0,-2.5f,0), PxVec3(0.3f,0.3f,0.3f), NULL, getManageMaterial(MATERIAL_YELLOW), 1.f);

	PxRigidDynamic* left_shoulder_joint1 = createBox(pos+PxVec3(-1.4f,0,.7f), PxVec3(0.3f,0.3f,0.3f), NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* left_shoulder_joint2 = createBox(pos+PxVec3(-2.0f,0,.7f), PxVec3(0.3f,0.3f,0.3f), NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	PxRigidDynamic* left_arm_1 = createBox(pos+PxVec3(-3.3f,0,.7f), PxVec3(1, 0.3f, 0.3f), NULL, getManageMaterial(MATERIAL_GREY), 1.f);

	setCollisionGroup(left_arm_1, NodeGroup::L_ARM);
	//left_shoulder_joint1->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	//left_shoulder_joint2->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);

	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		left_shoulder_joint1, PxTransform(PxVec3(0.6f,0,0))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	// left shoulder joint
	if (PxSphericalJoint* j = PxSphericalJointCreate(getPhysics(), 
		left_shoulder_joint1, PxTransform(PxVec3(0,0,0)),
		left_shoulder_joint2, PxTransform(PxVec3(1,0,0))))
	{
		if (flag)
		{
			j->setLimitCone(PxJointLimitCone(PxPi/2, PxPi/6, PxSpring(0,0)));
			j->setSphericalJointFlag(PxSphericalJointFlag::eLIMIT_ENABLED, true);
		}
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	// left shoulder - left arm
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		left_shoulder_joint2, PxTransform(PxVec3(0,0,0)),
		left_arm_1, PxTransform(PxVec3(1.3f,0,0))))
	{
		j->setProjectionLinearTolerance(0);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	m_Rigids.push_back(left_shoulder_joint1);
	m_Rigids.push_back(left_shoulder_joint2);

	return true;
}


/**
 @brief Revolution Join
 @date 2013-12-05
*/
bool SampleHelloWorld::GenerateHuman7(const bool flag)
{
	const PxVec3 pos = getCamera().getPos() + (getCamera().getViewDir()*10.f);
	const PxVec3 vel = getCamera().getViewDir() * 20.f;

	//PxRigidDynamic* body = createBox(pos+PxVec3(0,-2.5f,0), PxVec3(0.3f,0.3f,0.3f), NULL, getManageMaterial(MATERIAL_YELLOW), 1.f);

	PxRigidDynamic* left_shoulder_joint1 = createBox(pos+PxVec3(-1.4f,0,.7f), PxVec3(0.5f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* left_shoulder_joint2 = createBox(pos+PxVec3(-1.4f,-1,.7f), PxVec3(0.5f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	//PxRigidDynamic* left_arm_1 = createBox(pos+PxVec3(-3.3f,0,.7f), PxVec3(1, 0.3f, 0.3f), NULL, getManageMaterial(MATERIAL_GREY), 1.f);

	//setCollisionGroup(left_arm_1, NodeGroup::L_ARM);
	//left_shoulder_joint1->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	//left_shoulder_joint2->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
/*
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		left_shoulder_joint1, PxTransform(PxVec3(0.6f,0,0))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}*/

	// left shoulder joint
	if (PxRevoluteJoint* j = PxRevoluteJointCreate(getPhysics(), 
		left_shoulder_joint1, PxTransform(PxVec3(0,0,0)),
		left_shoulder_joint2, PxTransform(PxVec3(0,.6f,0))))
	{
		if (flag)
		{
			j->setLimit(PxJointAngularLimitPair(-PxPi/4, PxPi/4, 0.1f)); // upper, lower, tolerance
			j->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
			j->setDriveVelocity(m_value1);
			j->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
		}

		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);

		//m_Joints.push_back(j);
	}

	//// left shoulder - left arm
	//if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
	//	left_shoulder_joint2, PxTransform(PxVec3(0,0,0)),
	//	left_arm_1, PxTransform(PxVec3(1.3f,0,0))))
	//{
	//	j->setProjectionLinearTolerance(0);
	//	j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	//}

	m_Rigids.push_back(left_shoulder_joint1);
	m_Rigids.push_back(left_shoulder_joint2);

	return true;
}


/**
 @brief Revolution Join
 @date 2013-12-05
*/
bool SampleHelloWorld::GenerateHuman8(const bool flag)
{
	const PxVec3 pos = getCamera().getPos() + (getCamera().getViewDir()*10.f);
	const PxVec3 vel = getCamera().getViewDir() * 20.f;

	PxRigidDynamic* body = createBox(pos+PxVec3(0,-2.5f,0), PxVec3(0.3f,4.f,0.1f), NULL, getManageMaterial(MATERIAL_YELLOW), 1.f);

	PxRigidDynamic* left_shoulder_joint1 = createBox(pos+PxVec3(-1.4f,0,.7f), PxVec3(0.5f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* left_shoulder_joint2 = createBox(pos+PxVec3(-1.4f,-1,.7f), PxVec3(0.5f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	PxRigidDynamic* left_shoulder_joint3 = createBox(pos+PxVec3(-1.4f,-2,.7f), PxVec3(0.5f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* left_shoulder_joint4 = createBox(pos+PxVec3(-1.4f,-3,.7f), PxVec3(0.5f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	PxRigidDynamic* left_shoulder_joint5 = createBox(pos+PxVec3(-1.4f,-4,.7f), PxVec3(0.5f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* left_shoulder_joint6 = createBox(pos+PxVec3(-1.4f,-5,.7f), PxVec3(0.5f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	//PxRigidDynamic* left_arm_1 = createBox(pos+PxVec3(-3.3f,0,.7f), PxVec3(1, 0.3f, 0.3f), NULL, getManageMaterial(MATERIAL_GREY), 1.f);


	PxRigidDynamic* right_shoulder_joint1 = createBox(pos+PxVec3(1.4f,0,.7f), PxVec3(0.5f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* right_shoulder_joint2 = createBox(pos+PxVec3(1.4f,-1,.7f), PxVec3(0.5f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	PxRigidDynamic* right_shoulder_joint3 = createBox(pos+PxVec3(1.4f,-2,.7f), PxVec3(0.5f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* right_shoulder_joint4 = createBox(pos+PxVec3(1.4f,-3,.7f), PxVec3(0.5f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_BLUE), 1.f);
	PxRigidDynamic* right_shoulder_joint5 = createBox(pos+PxVec3(1.4f,-4,.7f), PxVec3(0.5f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_GREEN), 1.f);
	PxRigidDynamic* right_shoulder_joint6 = createBox(pos+PxVec3(1.4f,-5,.7f), PxVec3(0.5f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_BLUE), 1.f);

	//setCollisionGroup(left_arm_1, NodeGroup::L_ARM);
	//left_shoulder_joint1->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	//left_shoulder_joint2->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);

	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		left_shoulder_joint1, PxTransform(PxQuat(PxPi/2.f, PxVec3(0,0,1))) * PxTransform(PxVec3(0.6f,0,0))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		left_shoulder_joint3, PxTransform(PxQuat(PxPi/2.f, PxVec3(0,0,1))) * PxTransform(PxVec3(0.6f,-2,0))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		left_shoulder_joint5, PxTransform(PxQuat(PxPi/2.f, PxVec3(0,0,1))) * PxTransform(PxVec3(0.6f,-4,0))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}


	// left shoulder joint
	if (PxRevoluteJoint* j = PxRevoluteJointCreate(getPhysics(), 
		left_shoulder_joint1, PxTransform(PxVec3(0,0,0)),
		left_shoulder_joint2, PxTransform(PxVec3(0,.6f,0))))
	{
		if (flag)
		{
			j->setLimit(PxJointAngularLimitPair(-PxPi/4, PxPi/4, 0.1f)); // upper, lower, tolerance
			j->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
		}

		j->setDriveVelocity(1.f);
		j->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);

		//m_Joints.push_back(j);
	}

	// left shoulder joint 2
	if (PxRevoluteJoint* j = PxRevoluteJointCreate(getPhysics(), 
		left_shoulder_joint3, PxTransform(PxVec3(0,0,0)),
		left_shoulder_joint4, PxTransform(PxVec3(0,.6f,0))))
	{
		if (flag)
		{
			j->setLimit(PxJointAngularLimitPair(-PxPi/4, PxPi/4, 0.1f)); // upper, lower, tolerance
			j->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
		}

		j->setDriveVelocity(1.f);
		j->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);

		//m_Joints.push_back(j);
	}


	if (PxRevoluteJoint* j = PxRevoluteJointCreate(getPhysics(), 
		left_shoulder_joint5, PxTransform(PxVec3(0,0,0)),
		left_shoulder_joint6, PxTransform(PxVec3(0,.6f,0))))
	{
		if (flag)
		{
			j->setLimit(PxJointAngularLimitPair(-PxPi/4, PxPi/4, 0.1f)); // upper, lower, tolerance
			j->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
		}

		j->setDriveVelocity(1.f);
		j->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);

		//m_Joints.push_back(j);
	}


	// body - right shoulder
	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		right_shoulder_joint1, PxTransform(PxQuat(-PxPi/2.f, PxVec3(0,0,1))) * PxTransform(PxVec3(-0.6f,0,0))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		right_shoulder_joint3, PxTransform(PxQuat(-PxPi/2.f, PxVec3(0,0,1))) * PxTransform(PxVec3(-0.6f,-2,0))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}

	if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
		body, PxTransform(PxVec3(0,0,0)),
		right_shoulder_joint5, PxTransform(PxQuat(-PxPi/2.f, PxVec3(0,0,1))) * PxTransform(PxVec3(-0.6f,-4,0))
		))
	{
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	}


	// right shoulder joint
	if (PxRevoluteJoint* j = PxRevoluteJointCreate(getPhysics(), 
		right_shoulder_joint1, PxTransform(PxVec3(0,0,0)),
		right_shoulder_joint2, PxTransform(PxVec3(0,.6f,0))))
	{
		if (flag)
		{
			j->setLimit(PxJointAngularLimitPair(-PxPi/4, PxPi/4, 0.1f)); // upper, lower, tolerance
			j->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
		}
		j->setDriveVelocity(1.f);
		j->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);

		//m_Joints.push_back(j);
	}


	if (PxRevoluteJoint* j = PxRevoluteJointCreate(getPhysics(), 
		right_shoulder_joint3, PxTransform(PxVec3(0,0,0)),
		right_shoulder_joint4, PxTransform(PxVec3(0,.6f,0))))
	{
		if (flag)
		{
			j->setLimit(PxJointAngularLimitPair(-PxPi/4, PxPi/4, 0.1f)); // upper, lower, tolerance
			j->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
		}
		j->setDriveVelocity(1.f);
		j->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);

		//m_Joints.push_back(j);
	}

	if (PxRevoluteJoint* j = PxRevoluteJointCreate(getPhysics(), 
		right_shoulder_joint5, PxTransform(PxVec3(0,0,0)),
		right_shoulder_joint6, PxTransform(PxVec3(0,.6f,0))))
	{
		if (flag)
		{
			j->setLimit(PxJointAngularLimitPair(-PxPi/4, PxPi/4, 0.1f)); // upper, lower, tolerance
			j->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
		}
		j->setDriveVelocity(1.f);
		j->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
		j->setProjectionLinearTolerance(0.0f);
		j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);

		//m_Joints.push_back(j);
	}


	//// left shoulder - left arm
	//if (PxFixedJoint* j = PxFixedJointCreate(getPhysics(), 
	//	left_shoulder_joint2, PxTransform(PxVec3(0,0,0)),
	//	left_arm_1, PxTransform(PxVec3(1.3f,0,0))))
	//{
	//	j->setProjectionLinearTolerance(0);
	//	j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);
	//}

	m_Rigids.push_back(left_shoulder_joint1);
	m_Rigids.push_back(left_shoulder_joint2);

	return true;
}


/**
 @brief 
 @date 2014-01-02
*/
bool SampleHelloWorld::GenerateHuman9(const bool flag)
{
	const PxVec3 pos = getCamera().getPos() + (getCamera().getViewDir()*10.f) + PxVec3(0,-2.5f,0);
	const PxVec3 vel = getCamera().getViewDir() * 20.f;
	PxVec3 dims(0.3f,0.3f,0.1f);
	PxRigidDynamic* box = createBox(pos, PxVec3(0.3f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_YELLOW), 1.f);
	PxRigidDynamic* box2 = createBox(pos+PxVec3(1,0,0), PxVec3(0.3f,0.3f,0.1f), NULL, getManageMaterial(MATERIAL_YELLOW), 1.f);
	createRenderCompositionFromActor(box, box2, NULL);
	return true;
}


/**
 @brief 
 @date 2014-01-02
*/
void SampleHelloWorld::createRenderCompositionFromActor(PxRigidActor* rigidActor0, PxRigidActor* rigidActor1, RenderMaterial* material)
{
	PX_ASSERT(rigidActor0);

	PxU32 nbShapes0 = rigidActor0->getNbShapes();
	if(!nbShapes0)
		return;
	PxU32 nbShapes1 = rigidActor1->getNbShapes();
	if(!nbShapes1)
		return;

	Renderer& renderer = *getRenderer();
	PxShape** shapes0 = (PxShape**)SAMPLE_ALLOC(sizeof(PxShape*)*nbShapes0);
	PxU32 nb0 = rigidActor0->getShapes(shapes0, nbShapes0);
	PX_ASSERT(nb0==nbShapes0);

	PxShape** shapes1 = (PxShape**)SAMPLE_ALLOC(sizeof(PxShape*)*nbShapes1);
	PxU32 nb1 = rigidActor1->getShapes(shapes1, nbShapes1);
	PX_ASSERT(nb1==nbShapes1);

	RenderBaseActor *renderActor0 = getRenderActor(rigidActor0, shapes0[ 0]);
	RenderBaseActor *renderActor1 = getRenderActor(rigidActor1, shapes1[ 0]);

	if (renderActor0 && renderActor1)
	{
		RenderBaseActor* shapeRenderActor = SAMPLE_NEW(RenderComposition)(renderer, 
			renderActor0->getRenderShape(), PxTransform(), renderActor1->getRenderShape(), PxTransform() );

		if(shapeRenderActor)
		{
			//link(shapeRenderActor, shape, actor);
			mRenderActors.push_back(shapeRenderActor);
			shapeRenderActor->setRenderMaterial(material);
			shapeRenderActor->setEnableCameraCull(true);
		}
	}

	SAMPLE_FREE(shapes0);
	SAMPLE_FREE(shapes1);
}


/**
 @brief 
 @date 2013-12-05
*/
void SampleHelloWorld::setCollisionGroup(PxRigidActor* actor, PxU32 group)
{
	PxSceneWriteLock scopedLock(getActiveScene());

	PxU32 nbShapes = actor->getNbShapes();
	if( nbShapes )
	{
		SampleArray<PxShape*> shapes(nbShapes);
		actor->getShapes( &shapes[0], nbShapes);
		for( PxU32 j = 0; j < nbShapes; j++)
		{
			PxFilterData fd = shapes[j]->getSimulationFilterData();
			fd.word0 = group;
			shapes[j]->setSimulationFilterData(fd);
		}
	}
}


/**
 @brief 
 @date 2013-12-10
*/
void SampleHelloWorld::onDigitalInputEvent(const SampleFramework::InputEvent&ie , bool val)
{
	if (val)
	{
		switch (ie.m_Id)
		{
		case SPAWN_DEBUG_OBJECT:
		case SPAWN_DEBUG_OBJECT2:
		case SPAWN_DEBUG_OBJECT3:
		case SPAWN_DEBUG_OBJECT4:
		case SPAWN_DEBUG_OBJECT5:
		case SPAWN_DEBUG_OBJECT6:
		case SPAWN_DEBUG_OBJECT7:
		case SPAWN_DEBUG_OBJECT8:
		case SPAWN_DEBUG_OBJECT9:
			spawnNode(ie.m_Id);
			break;

		case SPAWN_DEBUG_OBJECT0:
			spawnDebugObject();
			break;

		case PICKUP:
			//pickup();
			break;
		}
	}
}


/**
 @brief 
 @date 2013-12-03
*/
void SampleHelloWorld::spawnNode(const int key)
{
	PxSceneWriteLock scopedLock(*mScene);
	switch (key)
	{
	case SPAWN_DEBUG_OBJECT: GenerateHuman(m_applyJoint); break;
	case SPAWN_DEBUG_OBJECT2: GenerateHuman2(m_applyJoint); break;
	case SPAWN_DEBUG_OBJECT3: GenerateHuman3(m_applyJoint); break;
	case SPAWN_DEBUG_OBJECT4: GenerateHuman4(m_applyJoint); break;
	case SPAWN_DEBUG_OBJECT5: GenerateHuman5(m_applyJoint); break;
	case SPAWN_DEBUG_OBJECT6: GenerateHuman6(m_applyJoint); break;
	case SPAWN_DEBUG_OBJECT7: GenerateHuman7(m_applyJoint); break;
	case SPAWN_DEBUG_OBJECT8: GenerateHuman8(m_applyJoint); break;
	case SPAWN_DEBUG_OBJECT9: GenerateHuman9(m_applyJoint); break;
	//case SPAWN_DEBUG_OBJECT0: GenerateByGenotype("genotype.txt"); break;
	}
}
