#pragma once
#include <cstdint>
static class MdlStructs
{
public:
	struct ModelFileHeader
	{
	public:
		uint32_t Version;
		uint32_t StackSize;
		uint32_t RuntimeSize;
		uint16_t VertexDeclarationCount;
		uint16_t MaterialCount;
		uint32_t VertexOffset[3];
		uint32_t IndexOffset[3];
		uint32_t VertexBufferSize[3];
		uint32_t IndexBufferSize[3];
		uint8_t LodCount;
		bool EnableIndexBufferStreaming;
		bool EnableEdgeGeometry;
		uint8_t Padding;
	};

	struct VertexElement {
	public:
		uint8_t Stream;
		uint8_t Offset;
		uint8_t Type;
		uint8_t Usage;
		uint8_t UsageIndex;
		uint8_t Padding[3];
	};

	struct VertexDeclarationStruct {
	public:
		VertexElement VertexElements[17];
	};

	struct ModelHeader {
	public:
		float Radius;
		uint16_t MeshCount;
		uint16_t AttributeCount;
		uint16_t SubmeshCount;
		uint16_t MaterialCount;
		uint16_t BoneCount;
		uint16_t BoneTableCount;
		uint16_t ShapeCount;
		uint16_t ShapeMeshCount;
		uint16_t ShapeValueCount;
		uint8_t LodCount;

		uint8_t Flags1;

		//bool DustOcclusionEnabled = (Flags1 << 0x80) > 0;
		//bool SnowOcclusionEnabled = (Flags1 << 0x40) > 0;
		//bool RainOcclusionEnabled = (Flags1 << 0x20) > 0;
		//bool Unknown1 = (Flags1 << 0x10) > 0;
		//bool LightingReflectionEnabled = (Flags1 << 0x08) > 0;
		//bool WavingAnimationDisabled = (Flags1 << 0x04) > 0;
		//bool LightShadowDisabled = (Flags1 << 0x02) > 0;
		//bool ShadowDisabled = (Flags1 << 0x01) > 0;

		uint16_t ElementIdCount;
		uint8_t TerrainShadowMeshCount;

		uint8_t Flags2;
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
		uint16_t Unknown4;
		uint16_t TerrainShadowSubmeshCount;

		uint8_t Unknown5;

		uint8_t BGChangeMaterialIndex;
		uint8_t BGCrestChangeMaterialIndex;
		uint8_t Unknown6;
		uint16_t Unknown7;
		uint16_t Unknown8;
		uint16_t Unknown9;
		uint8_t Padding[6];
	};
	struct ElementIdStruct {
	public:
		uint32_t ElementId;
		uint32_t ParentBoneName;
		float Translate[3];
		float Rotate[3];
	};

	struct LodStruct {
	public:
		uint16_t MeshIndex;
		uint16_t MeshCount;
		float ModelLodRange;
		float TextureLodRange;
		uint16_t WaterMeshIndex;
		uint16_t WaterMeshCount;
		uint16_t ShadowMeshIndex;
		uint16_t ShadowMeshCount;
		uint16_t TerrainShadowMeshIndex;
		uint16_t TerrainShadowMeshCount;
		uint16_t VerticalFogMeshIndex;
		uint16_t VerticalFogMeshCount;

		uint32_t EdgeGeometrySize;
		uint32_t EdgeGeometryDataOffset;
		uint32_t PolygonCount;
		uint32_t Unknown1;
		uint32_t VertexBufferSize;
		uint32_t IndexBufferSize;
		uint32_t VertexDataOffset;
		uint32_t IndexDataOffset;
	};

	struct ExtraLodStruct {
	public:
		uint16_t LightShaftMeshIndex;
		uint16_t LightShaftMeshCount;
		uint16_t GlassMeshIndex;
		uint16_t GlassMeshCount;
		uint16_t MaterialChangeMeshIndex;
		uint16_t MaterialChangeMeshCount;
		uint16_t CrestChangeMeshIndex;
		uint16_t CrestChangeMeshCount;
		uint16_t Unknown1;
		uint16_t Unknown2;
		uint16_t Unknown3;
		uint16_t Unknown4;
		uint16_t Unknown5;
		uint16_t Unknown6;
		uint16_t Unknown7;
		uint16_t Unknown8;
		uint16_t Unknown9;
		uint16_t Unknown10;
		uint16_t Unknown11;
		uint16_t Unknown12;
	};

	struct MeshStruct {
	public:
		uint16_t VertexCount;
		uint16_t Padding;
		uint32_t IndexCount;
		uint16_t MaterialIndex;
		uint16_t SubMeshIndex;
		uint16_t SubMeshCount;
		uint16_t BoneTableIndex;
		uint32_t StartIndex;
		uint32_t VertexBufferOffset[3];
		uint8_t VertexBufferStride[3];
		uint8_t VertexStreamCount;
	};

	struct TerrainShadowMeshStruct {
	public:
		uint32_t IndexCount;
		uint32_t StartIndex;
		uint32_t VertexBufferOffset;
		uint16_t VertexCount;
		uint16_t SubMeshIndex;
		uint16_t SubMeshCount;
		uint8_t VertexBufferStride;
		uint8_t Padding;
	};

	struct SubmeshStruct {
	public:
		uint32_t IndexOffset;
		uint32_t IndexCount;
		uint32_t AttributeIndexMask;
		uint16_t BoneStartIndex;
		uint16_t BoneCount;
	};

	struct TerrainShadowSubmeshStruct {
	public:
		uint32_t IndexOffset;
		uint32_t IndexCount;
		uint16_t Unknown1;
		uint16_t Unknown2;
	};

	struct BoneTableStruct {
	public:
		uint16_t BoneIndex[64];
		uint8_t BoneCount = 0;
		uint8_t Padding[3];
	};

	struct ShapeStruct {
	public:
		uint32_t StringOffset;
		uint16_t ShapeMeshStartIndex[3];
		uint16_t ShapeMeshCount[3];
	};

	struct ShapeMeshStruct {
	public:
		// ShapeData.ShapePart
		uint32_t StartIndex;	// offset to the index block this Shape Data should be replacing
			//StartIndex = MeshNumber?

		uint32_t ShapeValueCount;	// # of triangle indices to replace
		uint32_t ShapeValueOffset;	// the offset where this part should start reading in the Shape Data list
	};

	struct ShapeValueStruct {
	public:
		// ShapeData.ShapeDataEntry
		uint16_t Offset;	// Base Triangle Index we're replacing
		uint16_t Value;	// The vertex that Triangle Index should now point to instead
	};

	struct BoundingBoxStruct {
	public:
		float Min[4];
		float Max[4];
	};
};

