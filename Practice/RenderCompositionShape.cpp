
#include "stdafx.h"
#include "RenderCompositionShape.h"

#include <Renderer.h>

#include <RendererVertexBuffer.h>
#include <RendererVertexBufferDesc.h>

#include <RendererIndexBuffer.h>
#include <RendererIndexBufferDesc.h>

#include <RendererMesh.h>
#include <RendererMeshDesc.h>

#include <RendererMemoryMacros.h>

using namespace SampleRenderer;

typedef struct
{
	PxVec3 positions[4];
	PxVec3 normal;
} BoxFace;

static const BoxFace g_BoxFaces1[] =
{
	{ // Z+
		{PxVec3(-1,-1, 1), PxVec3(-1, 1, 1), PxVec3( 1, 1, 1), PxVec3( 1,-1, 1)},
			PxVec3( 0, 0, 1)
	},
	{ // X+
		{PxVec3( 1,-1, 1), PxVec3( 1, 1, 1), PxVec3( 1, 1,-1), PxVec3( 1,-1,-1)},
			PxVec3( 1, 0, 0)
		},
		{ // Z-
			{PxVec3( 1,-1,-1), PxVec3( 1, 1,-1), PxVec3(-1, 1,-1), PxVec3(-1,-1,-1)},
				PxVec3( 0, 0,-1)
		},
		{ // X-
			{PxVec3(-1,-1,-1), PxVec3(-1, 1,-1), PxVec3(-1, 1, 1), PxVec3(-1,-1, 1)},
				PxVec3(-1, 0, 0)
			},
			{ // Y+
				{PxVec3(-1, 1, 1), PxVec3(-1, 1,-1), PxVec3( 1, 1,-1), PxVec3( 1, 1, 1)},
					PxVec3( 0, 1, 0)
			},
			{ // Y-
				{PxVec3(-1,-1,-1), PxVec3(-1,-1, 1), PxVec3( 1,-1, 1), PxVec3( 1,-1,-1)},
					PxVec3( 0,-1, 0)
				}
};

static const PxVec3 g_BoxUVs1[] =
{
	PxVec3(0,1,0), PxVec3(0,0,0),
	PxVec3(1,0,0), PxVec3(1,1,0),
};

namespace physx
{
	static PxVec3 operator*(const PxVec3 &a, const PxVec3 &b)
	{
		return PxVec3(a.x*b.x, a.y*b.y, a.z*b.z);
	}
}

RendererCompositionShape::RendererCompositionShape(Renderer &renderer, 
	const PxVec3& pos1, const PxVec3& extents1, 
	const PxVec3& pos2, const PxVec3& extents2,
	const PxReal* userUVs) :
	RendererShape(renderer)
{
	//const PxU32 numVerts = 24;
	//const PxU32 numIndices = 36;
	const PxU32 numVerts = 48;
	const PxU32 numIndices = 72;

	RendererVertexBufferDesc vbdesc;
	vbdesc.hint = RendererVertexBuffer::HINT_STATIC;
	vbdesc.semanticFormats[RendererVertexBuffer::SEMANTIC_POSITION]  = RendererVertexBuffer::FORMAT_FLOAT3;
	vbdesc.semanticFormats[RendererVertexBuffer::SEMANTIC_NORMAL] = RendererVertexBuffer::FORMAT_FLOAT3;
	vbdesc.semanticFormats[RendererVertexBuffer::SEMANTIC_TEXCOORD0] = RendererVertexBuffer::FORMAT_FLOAT2;
	vbdesc.maxVertices = numVerts;
	m_vertexBuffer = m_renderer.createVertexBuffer(vbdesc);
	RENDERER_ASSERT(m_vertexBuffer, "Failed to create Vertex Buffer.");
	if(m_vertexBuffer)
	{
		PxU32 positionStride = 0;
		void *positions = m_vertexBuffer->lockSemantic(RendererVertexBuffer::SEMANTIC_POSITION, positionStride);
		PxU32 normalStride = 0;
		void *normals = m_vertexBuffer->lockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL, normalStride);
		PxU32 uvStride = 0;
		void *uvs = m_vertexBuffer->lockSemantic(RendererVertexBuffer::SEMANTIC_TEXCOORD0, uvStride);
		if(positions && normals && uvs)
		{
			for(PxU32 i=0; i<6; i++)
			{
				const BoxFace &bf = g_BoxFaces1[i];
				for(PxU32 j=0; j<4; j++)
				{
					PxVec3 &p  = *(PxVec3*)positions; 
					positions = ((PxU8*)positions) + positionStride;

					PxVec3 &n  = *(PxVec3*)normals;   
					normals   = ((PxU8*)normals)   + normalStride;

					PxF32 *uv  =  (PxF32*)uvs;        
					uvs       = ((PxU8*)uvs)       + uvStride;

					n = bf.normal;
					p = bf.positions[j] * extents1;
					if(userUVs)
					{
						uv[0] = *userUVs++;
						uv[1] = *userUVs++;
					}
					else
					{
						uv[0] = g_BoxUVs1[j].x;
						uv[1] = g_BoxUVs1[j].y;
					}
				}
			}



			for(PxU32 i=0; i<6; i++)
			{
				const BoxFace &bf = g_BoxFaces1[i];
				for(PxU32 j=0; j<4; j++)
				{
					PxVec3 &p  = *(PxVec3*)positions; 
					positions = ((PxU8*)positions) + positionStride;

					PxVec3 &n  = *(PxVec3*)normals;   
					normals   = ((PxU8*)normals)   + normalStride;

					PxF32 *uv  =  (PxF32*)uvs;        
					uvs       = ((PxU8*)uvs)       + uvStride;

					n = bf.normal;
					p = bf.positions[j] * extents2 + pos2;
					if(userUVs)
					{
						uv[0] = *userUVs++;
						uv[1] = *userUVs++;
					}
					else
					{
						uv[0] = g_BoxUVs1[j].x;
						uv[1] = g_BoxUVs1[j].y;
					}
				}
			}


		}
		m_vertexBuffer->unlockSemantic(RendererVertexBuffer::SEMANTIC_TEXCOORD0);
		m_vertexBuffer->unlockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL);
		m_vertexBuffer->unlockSemantic(RendererVertexBuffer::SEMANTIC_POSITION);
	}

	RendererIndexBufferDesc ibdesc;
	ibdesc.hint       = RendererIndexBuffer::HINT_STATIC;
	ibdesc.format     = RendererIndexBuffer::FORMAT_UINT16;
	ibdesc.maxIndices = numIndices;
	m_indexBuffer = m_renderer.createIndexBuffer(ibdesc);
	RENDERER_ASSERT(m_indexBuffer, "Failed to create Index Buffer.");
	if(m_indexBuffer)
	{
		PxU16 *indices = (PxU16*)m_indexBuffer->lock();
		if(indices)
		{
			//for(PxU8 i=0; i<6; i++)
			for(PxU8 i=0; i<12; i++)
			{
				const PxU16 base = i*4;
				*(indices++) = base+0;
				*(indices++) = base+1;
				*(indices++) = base+2;
				*(indices++) = base+0;
				*(indices++) = base+2;
				*(indices++) = base+3;
			}
		}
		m_indexBuffer->unlock();
	}

	if(m_vertexBuffer && m_indexBuffer)
	{
		RendererMeshDesc meshdesc;
		meshdesc.primitives       = RendererMesh::PRIMITIVE_TRIANGLES;
		meshdesc.vertexBuffers    = &m_vertexBuffer;
		meshdesc.numVertexBuffers = 1;
		meshdesc.firstVertex      = 0;
		meshdesc.numVertices      = numVerts;
		meshdesc.indexBuffer      = m_indexBuffer;
		meshdesc.firstIndex       = 0;
		meshdesc.numIndices       = numIndices;
		m_mesh = m_renderer.createMesh(meshdesc);
		RENDERER_ASSERT(m_mesh, "Failed to create Mesh.");
	}
}

RendererCompositionShape::~RendererCompositionShape(void)
{
	SAFE_RELEASE(m_vertexBuffer);
	SAFE_RELEASE(m_indexBuffer);
	SAFE_RELEASE(m_mesh);
}


/**
 @brief 
 @date 2014-01-02
*/
RendererCompositionShape::RendererCompositionShape(Renderer &renderer, 
	RendererShape *shape0, const PxTransform &tm0, 
	RendererShape *shape1, const PxTransform &tm1, 
	const PxReal* uvs0) :
	RendererShape(renderer)
{
	GenerateCompositionShape(shape0, tm0, shape1, tm1, 6, 18);

	RendererMesh *mesh0 = shape0->getMesh();
	RendererMesh *mesh1 = shape1->getMesh();
	
	SampleRenderer::RendererVertexBuffer **vtx0 = mesh0->getVertexBuffersEdit();
	SampleRenderer::RendererIndexBuffer *idx0 = mesh0->getIndexBufferEdit();
	const PxU32 numVtxBuff0 = mesh0->getNumVertexBuffers();

	SampleRenderer::RendererVertexBuffer **vtx1 = mesh1->getVertexBuffersEdit();
	SampleRenderer::RendererIndexBuffer *idx1 = mesh1->getIndexBufferEdit();
	const PxU32 numVtxBuff1 = mesh1->getNumVertexBuffers();

	if ((numVtxBuff0 <= 0) || (numVtxBuff1 <= 0))
		return;

	PxU32 positionStride0 = 0;
	void *positions0 = vtx0[ 0]->lockSemantic(RendererVertexBuffer::SEMANTIC_POSITION, positionStride0);
	PxU32 normalStride0 = 0;
	void *normals0 = vtx0[ 0]->lockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL, normalStride0);

	PxU32 positionStride1 = 0;
	void *positions1 = vtx1[ 0]->lockSemantic(RendererVertexBuffer::SEMANTIC_POSITION, positionStride1);
	PxU32 normalStride1 = 0;
	void *normals1 = vtx1[ 0]->lockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL, normalStride1);

	PxU16 *indices0 = (PxU16*)idx0->lock();
	PxU16 *indices1 = (PxU16*)idx1->lock();
	PxU32 idx0Size = idx0->getMaxIndices();
	PxU32 idx1Size = idx1->getMaxIndices();

	const PxU32 numVtx0 = vtx0[0]->getMaxVertices();
	const PxU32 numVtx1 = vtx1[0]->getMaxVertices();

	if (indices0 && positions0 && normals0 && indices1 && positions1 && normals1)
	{
		float minLen = 100000.f;
		int minFaceIdx0 = -1;
		int minFaceIdx1 = -1;
		for (PxU8 i=0; i<idx0Size; i+=3)
		{
			PxVec3 center0;
			PxVec3 center0Normal;
			{
				const PxU16 vidx0 = indices0[ i];
				const PxU16 vidx1 = indices0[ i+1];
				const PxU16 vidx2 = indices0[ i+2];

				PxVec3 &p0 = *(PxVec3*)(((PxU8*)positions0) + (positionStride0 * vidx0));
				PxVec3 &p1 = *(PxVec3*)(((PxU8*)positions0) + (positionStride0 * vidx1));
				PxVec3 &p2 = *(PxVec3*)(((PxU8*)positions0) + (positionStride0 * vidx2));

				PxVec3 &n0 = *(PxVec3*)(((PxU8*)normals0) + (normalStride0 * vidx0));
				PxVec3 &n1 = *(PxVec3*)(((PxU8*)normals0) + (normalStride0 * vidx1));
				PxVec3 &n2 = *(PxVec3*)(((PxU8*)normals0) + (normalStride0 * vidx2));

				center0 = p0 + p1 + p2;
				center0 /= 3.f;

				center0Normal = n0;
			}

			for (PxU8 k=0; k<idx1Size; k+=3)
			{
				PxVec3 center1;
				PxVec3 center1Normal;
				{
					const PxU16 vidx0 = indices1[ k];
					const PxU16 vidx1 = indices1[ k+1];
					const PxU16 vidx2 = indices1[ k+2];

					PxVec3 &p0 = *(PxVec3*)(((PxU8*)positions1) + (positionStride1 * vidx0)) + PxVec3(1,0,0);
					PxVec3 &p1 = *(PxVec3*)(((PxU8*)positions1) + (positionStride1 * vidx1)) + PxVec3(1,0,0);
					PxVec3 &p2 = *(PxVec3*)(((PxU8*)positions1) + (positionStride1 * vidx2)) + PxVec3(1,0,0);

					PxVec3 &n0 = *(PxVec3*)(((PxU8*)normals1) + (normalStride1 * vidx0));
					PxVec3 &n1 = *(PxVec3*)(((PxU8*)normals1) + (normalStride1 * vidx1));
					PxVec3 &n2 = *(PxVec3*)(((PxU8*)normals1) + (normalStride1 * vidx2));

					center1 = p0 + p1 + p2;
					center1 /= 3.f;

					center1Normal = n0;
				}

				PxVec3 len = center0 - center1;
				if ((minLen > len.magnitude()) && (center0Normal.dot(center1Normal) < 0) )
				{
					minFaceIdx0 = i;
					minFaceIdx1 = k;
					minLen = len.magnitude();	
				}
			}
		}

		// gen face
		if (minFaceIdx0 >= 0)
		{
			const PxU16 vidx00 = indices0[ minFaceIdx0];
			const PxU16 vidx01 = indices0[ minFaceIdx0+1];
			const PxU16 vidx02 = indices0[ minFaceIdx0+2];

			PxVec3 &p00 = *(PxVec3*)(((PxU8*)positions0) + (positionStride0 * vidx00));
			PxVec3 &p01 = *(PxVec3*)(((PxU8*)positions0) + (positionStride0 * vidx01));
			PxVec3 &p02 = *(PxVec3*)(((PxU8*)positions0) + (positionStride0 * vidx02));

			PxVec3 &n00 = *(PxVec3*)(((PxU8*)normals0) + (normalStride0 * vidx00));
			PxVec3 &n01 = *(PxVec3*)(((PxU8*)normals0) + (normalStride0 * vidx01));
			PxVec3 &n02 = *(PxVec3*)(((PxU8*)normals0) + (normalStride0 * vidx02));


			const PxU16 vidx10 = indices1[ minFaceIdx1];
			const PxU16 vidx11 = indices1[ minFaceIdx1+1];
			const PxU16 vidx12 = indices1[ minFaceIdx1+2];

			PxVec3 &p10 = *(PxVec3*)(((PxU8*)positions1) + (positionStride1 * vidx10));
			PxVec3 &p11 = *(PxVec3*)(((PxU8*)positions1) + (positionStride1 * vidx11));
			PxVec3 &p12 = *(PxVec3*)(((PxU8*)positions1) + (positionStride1 * vidx12));

			PxVec3 &n10 = *(PxVec3*)(((PxU8*)normals1) + (normalStride1 * vidx10));
			PxVec3 &n11 = *(PxVec3*)(((PxU8*)normals1) + (normalStride1 * vidx11));
			PxVec3 &n12 = *(PxVec3*)(((PxU8*)normals1) + (normalStride1 * vidx12));

			
			PxU32 positionStride = 0;
			void *positions = m_vertexBuffer->lockSemantic(RendererVertexBuffer::SEMANTIC_POSITION, positionStride);
			PxU32 normalStride = 0;
			void *normals = m_vertexBuffer->lockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL, normalStride);
			PxU32 uvStride = 0;
			void *uvs = m_vertexBuffer->lockSemantic(RendererVertexBuffer::SEMANTIC_TEXCOORD0, uvStride);

			PxU32 startVtxIdx = numVtx0 + numVtx1;
			*(PxVec3*)(((PxU8*)positions) + (positionStride * startVtxIdx)) = p00;
			*(PxVec3*)(((PxU8*)positions) + (positionStride * (startVtxIdx+1))) = p01;
			*(PxVec3*)(((PxU8*)positions) + (positionStride * (startVtxIdx+2))) = p02;
			*(PxVec3*)(((PxU8*)positions) + (positionStride * (startVtxIdx+3))) = p10 + PxVec3(1,0,0);
			*(PxVec3*)(((PxU8*)positions) + (positionStride * (startVtxIdx+4))) = p11 + PxVec3(1,0,0);
			*(PxVec3*)(((PxU8*)positions) + (positionStride * (startVtxIdx+5))) = p12 + PxVec3(1,0,0);

			m_vertexBuffer->unlockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL);
			m_vertexBuffer->unlockSemantic(RendererVertexBuffer::SEMANTIC_POSITION);
			m_vertexBuffer->unlockSemantic(RendererVertexBuffer::SEMANTIC_TEXCOORD0);

			vector<PxVec3> v0;
			v0.push_back(p00);
			v0.push_back(p01);
			v0.push_back(p02);

			vector<PxVec3> v1;
			v1.push_back(p10);
			v1.push_back(p11);
			v1.push_back(p12);

			vector<int> line(3);
			for (unsigned int i=0; i < v0.size(); ++i)
			{
				float minLen = 10000;
				for (unsigned int k=0; k < v1.size(); ++k)
				{
					PxVec3 v = v0[ i] - v1[ k];
					if (minLen > v.magnitude())
					{
						line[ i] = (unsigned int)v0.size() + k;
						minLen = v.magnitude();
					}
				}
			}
			
			PxU16 *indices = (PxU16*)m_indexBuffer->lock();
			PxU32 idxSize = m_indexBuffer->getMaxIndices();

			PxU32 startIndexIdx = idx0Size + idx1Size;

			// face1
			indices[ startIndexIdx++] = startVtxIdx;
			indices[ startIndexIdx++] = startVtxIdx+1;
			indices[ startIndexIdx++] = startVtxIdx+line[0];

			indices[ startIndexIdx++] = startVtxIdx+line[1];
			indices[ startIndexIdx++] = startVtxIdx+line[0];
			indices[ startIndexIdx++] = startVtxIdx+1;

			// face2
			indices[ startIndexIdx++] = startVtxIdx+2;
			indices[ startIndexIdx++] = startVtxIdx;
			indices[ startIndexIdx++] = startVtxIdx+line[2];

			indices[ startIndexIdx++] = startVtxIdx+line[0];
			indices[ startIndexIdx++] = startVtxIdx+line[2];
			indices[ startIndexIdx++] = startVtxIdx;

			// face3
			indices[ startIndexIdx++] = startVtxIdx+2;
			indices[ startIndexIdx++] = startVtxIdx+1;
			indices[ startIndexIdx++] = startVtxIdx+line[2];

			indices[ startIndexIdx++] = startVtxIdx+line[1];
			indices[ startIndexIdx++] = startVtxIdx+line[2];
			indices[ startIndexIdx++] = startVtxIdx+1;

			m_indexBuffer->unlock();
		}
	}


	idx0->unlock();
	idx1->unlock();
	vtx0[ 0]->unlockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL);
	vtx0[ 0]->unlockSemantic(RendererVertexBuffer::SEMANTIC_POSITION);
	vtx1[ 0]->unlockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL);
	vtx1[ 0]->unlockSemantic(RendererVertexBuffer::SEMANTIC_POSITION);

}


/**
 @brief 
 @date 2014-01-03
*/
void RendererCompositionShape::GenerateCompositionShape( RendererShape *shape0, const PxTransform &tm0, 
	RendererShape *shape1, const PxTransform &tm1, 
	const int additionalVtxBuffSize, const int additionalIdxBuffSize )
{
	RendererMesh *mesh0 = shape0->getMesh();
	RendererMesh *mesh1 = shape1->getMesh();

	SampleRenderer::RendererVertexBuffer **vtx0 = mesh0->getVertexBuffersEdit();
	SampleRenderer::RendererIndexBuffer *idx0 = mesh0->getIndexBufferEdit();
	const PxU32 numVtxBuff0 = mesh0->getNumVertexBuffers();

	SampleRenderer::RendererVertexBuffer **vtx1 = mesh1->getVertexBuffersEdit();
	SampleRenderer::RendererIndexBuffer *idx1 = mesh1->getIndexBufferEdit();
	const PxU32 numVtxBuff1 = mesh1->getNumVertexBuffers();

	if ((numVtxBuff0 <= 0) || (numVtxBuff1 <= 0))
		return;

	PxU32 positionStride0 = 0;
	void *positions0 = vtx0[ 0]->lockSemantic(RendererVertexBuffer::SEMANTIC_POSITION, positionStride0);
	PxU32 normalStride0 = 0;
	void *normals0 = vtx0[ 0]->lockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL, normalStride0);
	PxU32 uvStride0 = 0;
	void *uvs0 = vtx0[ 0]->lockSemantic(RendererVertexBuffer::SEMANTIC_TEXCOORD0, uvStride0);

	PxU32 positionStride1 = 0;
	void *positions1 = vtx1[ 0]->lockSemantic(RendererVertexBuffer::SEMANTIC_POSITION, positionStride1);
	PxU32 normalStride1 = 0;
	void *normals1 = vtx1[ 0]->lockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL, normalStride1);
	PxU32 uvStride1 = 0;
	void *uvs1 = vtx1[ 0]->lockSemantic(RendererVertexBuffer::SEMANTIC_TEXCOORD0, uvStride1);


	PxU16 *indices0 = (PxU16*)idx0->lock();
	PxU16 *indices1 = (PxU16*)idx1->lock();
	PxU32 idx0Size = idx0->getMaxIndices();
	PxU32 idx1Size = idx1->getMaxIndices();

	const PxU32 numVtx0 = vtx0[0]->getMaxVertices();
	const PxU32 numVtx1 = vtx1[0]->getMaxVertices();

	const PxU32 numVerts =  numVtx0 + numVtx1 + additionalVtxBuffSize;
	const PxU32 numIndices = idx0Size + idx1Size + additionalIdxBuffSize;

	if (indices0 && positions0 && normals0 && indices1 && positions1 && normals1)
	{
		RendererVertexBufferDesc vbdesc;
		vbdesc.hint = RendererVertexBuffer::HINT_STATIC;
		vbdesc.semanticFormats[RendererVertexBuffer::SEMANTIC_POSITION]  = RendererVertexBuffer::FORMAT_FLOAT3;
		vbdesc.semanticFormats[RendererVertexBuffer::SEMANTIC_NORMAL] = RendererVertexBuffer::FORMAT_FLOAT3;
		vbdesc.semanticFormats[RendererVertexBuffer::SEMANTIC_TEXCOORD0] = RendererVertexBuffer::FORMAT_FLOAT2;
		vbdesc.maxVertices = numVerts;
		m_vertexBuffer = m_renderer.createVertexBuffer(vbdesc);
		RENDERER_ASSERT(m_vertexBuffer, "Failed to create Vertex Buffer.");

		PxU32 positionStride = 0;
		void *positions = m_vertexBuffer->lockSemantic(RendererVertexBuffer::SEMANTIC_POSITION, positionStride);
		PxU32 normalStride = 0;
		void *normals = m_vertexBuffer->lockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL, normalStride);
		PxU32 uvStride = 0;
		void *uvs = m_vertexBuffer->lockSemantic(RendererVertexBuffer::SEMANTIC_TEXCOORD0, uvStride);

		if (m_vertexBuffer)
		{
			// copy shape0 to current
			for (PxU32 i=0; i < numVtx0; ++i)
			{
				PxVec3 &p = *(PxVec3*)(((PxU8*)positions) + (positionStride * i));
				PxVec3 &n = *(PxVec3*)(((PxU8*)normals) + (normalStride * i));
				PxF32 *uv  =  (PxF32*)(((PxU8*)uvs) + (uvStride * i));

				PxVec3 &p0 = *(PxVec3*)(((PxU8*)positions0) + (positionStride0 * i));
				PxVec3 &n0 = *(PxVec3*)(((PxU8*)normals0) + (normalStride0 * i));
				PxF32 *uv0  =  (PxF32*)(((PxU8*)uvs0) + (uvStride0 * i));

				p = p0;
				n = n0;
				uv[ 0] = uv0[ 0];
				uv[ 1] = uv0[ 1];
			}

			// copy shape1 to current
			for (PxU32 i=0; i < numVtx1; ++i)
			{
				PxVec3 &p = *(PxVec3*)(((PxU8*)positions) + (positionStride * (i+numVtx0)));
				PxVec3 &n = *(PxVec3*)(((PxU8*)normals) + (normalStride * (i+numVtx0)));
				PxF32 *uv  =  (PxF32*)(((PxU8*)uvs) + (uvStride * (i+numVtx0)));

				PxVec3 &p0 = *(PxVec3*)(((PxU8*)positions1) + (positionStride1 * i));
				PxVec3 &n0 = *(PxVec3*)(((PxU8*)normals1) + (normalStride1 * i));
				PxF32 *uv0  =  (PxF32*)(((PxU8*)uvs1) + (uvStride1 * i));

				p = p0;
				p += PxVec3(1,0,0);

				n = n0;
				uv[ 0] = uv0[ 0];
				uv[ 1] = uv0[ 1];
			}
		}

		m_vertexBuffer->unlockSemantic(RendererVertexBuffer::SEMANTIC_TEXCOORD0);
		m_vertexBuffer->unlockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL);
		m_vertexBuffer->unlockSemantic(RendererVertexBuffer::SEMANTIC_POSITION);



		// copy index buffer
		RendererIndexBufferDesc ibdesc;
		ibdesc.hint = RendererIndexBuffer::HINT_STATIC;
		ibdesc.format = RendererIndexBuffer::FORMAT_UINT16;
		ibdesc.maxIndices = numIndices;
		m_indexBuffer = m_renderer.createIndexBuffer(ibdesc);
		RENDERER_ASSERT(m_indexBuffer, "Failed to create Index Buffer.");
		if (m_indexBuffer)
		{
			PxU16 *indices = (PxU16*)m_indexBuffer->lock();
			if (indices)
			{
				for(PxU8 i=0; i<idx0Size; i++)
					*(indices++) = indices0[ i];
				for(PxU8 i=0; i<idx1Size; i++)
					*(indices++) = numVtx0+indices1[ i];
			}

			m_indexBuffer->unlock();
		}
	}

	idx0->unlock();
	idx1->unlock();
	vtx0[ 0]->unlockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL);
	vtx0[ 0]->unlockSemantic(RendererVertexBuffer::SEMANTIC_POSITION);
	vtx0[ 0]->unlockSemantic(RendererVertexBuffer::SEMANTIC_TEXCOORD0);
	vtx1[ 0]->unlockSemantic(RendererVertexBuffer::SEMANTIC_NORMAL);
	vtx1[ 0]->unlockSemantic(RendererVertexBuffer::SEMANTIC_POSITION);
	vtx1[ 0]->unlockSemantic(RendererVertexBuffer::SEMANTIC_TEXCOORD0);

	if (m_vertexBuffer && m_indexBuffer)
	{
		RendererMeshDesc meshdesc;
		meshdesc.primitives = RendererMesh::PRIMITIVE_TRIANGLES;
		meshdesc.vertexBuffers    = &m_vertexBuffer;
		meshdesc.numVertexBuffers = 1;
		meshdesc.firstVertex      = 0;
		meshdesc.numVertices      = numVerts;
		meshdesc.indexBuffer      = m_indexBuffer;
		meshdesc.firstIndex       = 0;
		meshdesc.numIndices       = numIndices;
		m_mesh = m_renderer.createMesh(meshdesc);
		RENDERER_ASSERT(m_mesh, "Failed to create Mesh.");
	}

}
