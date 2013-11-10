// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2013 NVIDIA Corporation. All rights reserved.

#ifndef FRAMEWORK_FOUNDATION_H
#define FRAMEWORK_FOUNDATION_H

#include <stdio.h>
#include "foundation/PxPreprocessor.h"

namespace physx
{
#ifdef PX_WIIU
	struct FILE;
#endif

	namespace shdfnd{}

	namespace pxtask
	{
		class CudaContextManager;
	}
}

namespace SampleFramework
{

	using namespace physx;
	namespace Fnd = physx::shdfnd;

#ifdef PX_WIIU
	typedef physx::FILE File;
#else
	typedef ::FILE File;
#endif

} // namespace Renderer

#include <foundation/PxSimpleTypes.h>
#include <foundation/PxVec3.h>
#include <foundation/PxMat33.h>
#include <foundation/PxMat44.h>
#include <foundation/PxTransform.h>
#include <foundation/PxBounds3.h>
#include <foundation/PxErrorCallback.h>

#endif