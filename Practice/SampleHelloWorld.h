
#pragma once
#include "PhysXSample.h"


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

public:
	PxRigidDynamic*	createJointSphere(const PxVec3& pos, PxReal radius, const PxVec3* linVel=NULL, 
		RenderMaterial* material=NULL, PxReal density=1.0f);


};
