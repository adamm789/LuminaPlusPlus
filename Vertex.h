#pragma once
#include <vector>
class Vertex
{
public:
	enum class VertexType : __int8 {
		Single3 = 2,
		Single4 = 3,
		UInt = 5,
		ByteFloat4 = 8,
		Half2 = 13,
		Half4 = 14
	};
	enum class VertexUsage : __int8 {
		Position = 0,
		BlendWeights = 1,
		BlendIndices = 2,
		Normal = 3,
		UV = 4,
		Tangent2 = 5,
		Tangent1 = 6,
		Color = 7
	};
	float Position[4];
	float BlendWeights[4];
	char BlendIndices[4];
	float Normal[3];
	float UV[4];
	float Color[4];
	float Tangent2[4];
	float Tangent1[4];
};

