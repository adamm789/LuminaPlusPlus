#pragma once
#include <cstdint>
static class MdlStructs
{
public:
	struct ModelFileHeader
	{
	public:
		unsigned int Version;
		unsigned int StackSize;
		unsigned int RuntimeSize;
		unsigned short VertexDeclarationCount;
		unsigned short MaterialCount;
		unsigned int VertexOffset[3];
		unsigned int IndexOffset[3];
		unsigned int VertexBufferSize[3];
		unsigned int IndexBufferSize[3];
		__int8 LodCount;
		bool EnableIndexBufferStreaming;
		bool EnableEdgeGeometry;
		__int8 Padding;
	};

	struct VertexElement {
	public:
		__int8 Stream;
		__int8 Offset;
		__int8 Type;
		__int8 Usage;
		__int8 UsageIndex;
		__int8 Padding[3];
	};

	struct VertexDeclarationStruct {
	public:
		VertexElement VertexElements[17];
	};

	struct ModelHeader {
	public:
		float Radius;
		unsigned short MeshCount;
		unsigned short AttributeCount;
		unsigned short SubmeshCount;
		unsigned short MaterialCount;
		unsigned short BoneCount;
		unsigned short BoneTableCount;
		unsigned short ShapeCount;
		unsigned short ShapeMeshCount;
		unsigned short ShapeValueCount;
		__int8 LodCount;
		__int8 Flags1;

		//bool DustOcclusionEnabled = (Flags1 << 0x80) > 0;
		//bool SnowOcclusionEnabled = (Flags1 << 0x40) > 0;
		//bool RainOcclusionEnabled = (Flags1 << 0x20) > 0;
		//bool Unknown1 = (Flags1 << 0x10) > 0;
		//bool LightingReflectionEnabled = (Flags1 << 0x08) > 0;
		//bool WavingAnimationDisabled = (Flags1 << 0x04) > 0;
		//bool LightShadowDisabled = (Flags1 << 0x02) > 0;
		//bool ShadowDisabled = (Flags1 << 0x01) > 0;

		unsigned short ElementIdCount;
		__int8 TerrainShadowMeshCount;

		__int8 Flags2;
		//bool Unknown2 = (Flags2 << 0x80) > 0;
		//bool BgUvScrollEnabled = (Flags2 << 0x40) > 0;
		//bool EnableForceNonResident = (Flags2 << 0x20) > 0;
		//bool ExtraLodEnabled = (Flags2 << 0x10) > 0;
		//bool ShadowMaskEnabled = (Flags2 << 0x08) > 0;
		//bool ForceLodRangeEnabled = (Flags2 << 0x04) > 0;
		//bool EdgeGeometryEnabled = (Flags2 << 0x02) > 0;
		//bool Unknown3 = (Flags2 << 0x01) > 0;

		float ModelClipOutDistance;
		float ShadowClipOutDistance;
		unsigned short Unknown4;
		unsigned short TerrainShadowSubmeshCount;

		__int8 Unknown5;

		__int8 BGChangeMaterialIndex;
		__int8 BGCrestChangeMaterialIndex;
		__int8 Unknown6;
		unsigned short Unknown7;
		unsigned short Unknown8;
		unsigned short Unknown9;
		__int8 Padding[6];
	};
	struct ElementIdStruct {
	public:
		unsigned int ElementId;
		unsigned int ParentBoneName;
		float Translate[3];
		float Rotate[3];
	};

	struct LodStruct {
	public:
		unsigned short MeshIndex;
		unsigned short MeshCount;
		float ModelLodRange;
		float TextureLodRange;
		unsigned short WaterMeshIndex;
		unsigned short WaterMeshCount;
		unsigned short ShadowMeshIndex;
		unsigned short ShadowMeshCount;
		unsigned short TerrainShadowMeshIndex;
		unsigned short TerrainShadowMeshCount;
		unsigned short VerticalFogMeshIndex;
		unsigned short VerticalFogMeshCount;

		unsigned int EdgeGeometrySize;
		unsigned int EdgeGeometryDataOffset;
		unsigned int PolygonCount;
		unsigned int Unknown1;
		unsigned int VertexBufferSize;
		unsigned int IndexBufferSize;
		unsigned int VertexDataOffset;
		unsigned int IndexDataOffset;
	};

	struct ExtraLodStruct {
	public:
		unsigned short LightShaftMeshIndex;
		unsigned short LightShaftMeshCount;
		unsigned short GlassMeshIndex;
		unsigned short GlassMeshCount;
		unsigned short MaterialChangeMeshIndex;
		unsigned short MaterialChangeMeshCount;
		unsigned short CrestChangeMeshIndex;
		unsigned short CrestChangeMeshCount;
		unsigned short Unknown1;
		unsigned short Unknown2;
		unsigned short Unknown3;
		unsigned short Unknown4;
		unsigned short Unknown5;
		unsigned short Unknown6;
		unsigned short Unknown7;
		unsigned short Unknown8;
		unsigned short Unknown9;
		unsigned short Unknown10;
		unsigned short Unknown11;
		unsigned short Unknown12;
	};

	struct MeshStruct {
	public:
		unsigned short VertexCount;
		unsigned short Padding;
		unsigned int IndexCount;
		unsigned short MaterialIndex;
		unsigned short SubMeshIndex;
		unsigned short SubMeshCount;
		unsigned short BoneTableIndex;
		unsigned int StartIndex;
		unsigned int VertexBufferOffset[3];
		__int8 VertexBufferStride[3];
		__int8 VertexStreamCount;
	};

	struct TerrainShadowMeshStruct {
	public:
		unsigned int IndexCount;
		unsigned int StartIndex;
		unsigned int VertexBufferOffset;
		unsigned short VertexCount;
		unsigned short SubMeshIndex;
		unsigned short SubMeshCount;
		__int8 VertexBufferStride;
		__int8 Padding;
	};

	struct SubmeshStruct {
	public:
		__int32 IndexOffset;
		__int32 IndexCount;
		__int32 AttributeIndexMask;
		unsigned short BoneStartIndex;
		unsigned short BoneCount;
	};

	struct TerrainShadowSubmeshStruct {
	public:
		unsigned int IndexOffset;
		unsigned int IndexCount;
		unsigned short Unknown1;
		unsigned short Unknown2;
	};

	struct BoneTableStruct {
	public:
		unsigned short BoneIndex[64];
		__int8 BoneCount;
		__int8 Padding[3];
	};

	struct ShapeStruct {
	public:
		unsigned int StringOffset;
		unsigned short ShapeMeshStartIndex[3];
		unsigned short ShapeMeshCount[3];
	};

	struct ShapeMeshStruct {
	public:
		unsigned int StartIndex;
		unsigned int ShapeValueCount;
		unsigned int ShapeValueOffset;
	};

	struct ShapeValueStruct {
	public:
		unsigned short Offset;
		unsigned short Value;
	};

	struct BoundingBoxStruct {
	public:
		float Min[4];
		float Max[4];
	};
};

