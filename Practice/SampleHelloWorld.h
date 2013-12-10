
#pragma once
#include "PhysXSample.h"
#include <vector>


class SampleHelloWorld : public PhysXSample
{
public:
	SampleHelloWorld(PhysXSampleApplication& app);
	virtual ~SampleHelloWorld();

	virtual	void onTickPreRender(float dtime);
	virtual	void	onTickPostRender(float dtime);
	virtual	void	customizeSceneDesc(PxSceneDesc&);

	virtual	void	newMesh(const RAWMesh&);
	virtual	void	onInit();

	virtual void collectInputEvents(std::vector<const SampleFramework::InputEvent*>& inputEvents);
	virtual void helpRender(PxU32 x, PxU32 y, PxU8 textAlpha);
	virtual	void descriptionRender(PxU32 x, PxU32 y, PxU8 textAlpha);
	virtual PxU32 getDebugObjectTypes() const;

	virtual void onDigitalInputEvent(const SampleFramework::InputEvent& , bool val);
	void setCollisionGroup(PxRigidActor* actor, PxU32 group);

	bool GenerateHuman(const bool flag);
	bool GenerateHuman2(const bool flag);
	bool GenerateHuman3(const bool flag);
	bool GenerateHuman4(const bool flag);
	bool GenerateHuman5(const bool flag);
	bool GenerateHuman6(const bool flag);
	bool GenerateHuman7(const bool flag);
	bool GenerateHuman8(const bool flag);


protected:
	PxRigidDynamic*	createJointSphere(const PxVec3& pos, PxReal radius, const PxVec3* linVel=NULL, 
		RenderMaterial* material=NULL, PxReal density=1.0f);
	void spawnNode(const int key);


private:
	float m_value1;
	bool m_applyJoint;
	std::vector<PxRigidDynamic*> m_Rigids;
};
