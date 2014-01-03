/**
 @filename RenderCompositionShape.h
 
 
*/
#pragma once

#include <RendererShape.h>


namespace SampleRenderer
{
	class RendererVertexBuffer;
	class RendererIndexBuffer;

	class RendererCompositionShape : public RendererShape
	{
	public:
		RendererCompositionShape(Renderer &renderer, 
			const PxVec3& pos1, const PxVec3& extents1, 
			const PxVec3& pos2, const PxVec3& extents2,
			const PxReal* uvs=NULL);

		RendererCompositionShape(Renderer &renderer, 
			RendererShape *shape0, const PxTransform &tm0, 
			RendererShape *shape1, const PxTransform &tm1, const PxReal* uvs=NULL);

		virtual ~RendererCompositionShape(void);


	protected:
		void GenerateCompositionShape( RendererShape *shape0, const PxTransform &tm0, 
			RendererShape *shape1, const PxTransform &tm1, 
			const int additionalVtxBuffSize, const int additionalIdxBuffSize );



	private:
		RendererVertexBuffer *m_vertexBuffer;
		RendererIndexBuffer  *m_indexBuffer;
	};

}
