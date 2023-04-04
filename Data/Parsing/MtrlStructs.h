#pragma once
#include <cstdint>

// https://github.com/NotAdam/Lumina/blob/master/src/Lumina/Data/Parsing/MtrlStructs.cs
static class MtrlStructs
{
public:
    enum class TextureUsage : uint32_t
    {
        Sampler = 0x88408C04,
        Sampler0 = 0x213CB439,
        Sampler1 = 0x563B84AF,
        SamplerCatchlight = 0xFEA0F3D2,
        SamplerColorMap0 = 0x1E6FEF9C,
        SamplerColorMap1 = 0x6968DF0A,
        SamplerDiffuse = 0x115306BE,
        SamplerEnvMap = 0xF8D7957A,
        SamplerMask = 0x8A4E82B6,
        SamplerNormal = 0x0C5EC1F1,
        SamplerNormalMap0 = 0xAAB4D9E9,
        SamplerNormalMap1 = 0xDDB3E97F,
        SamplerReflection = 0x87F6474D,
        SamplerSpecular = 0x2B99E025,
        SamplerSpecularMap0 = 0x1BBC2F12,
        SamplerSpecularMap1 = 0x6CBB1F84,
        SamplerWaveMap = 0xE6321AFC,
        SamplerWaveletMap0 = 0x574E22D6,
        SamplerWaveletMap1 = 0x20491240,
        SamplerWhitecapMap = 0x95E1F64D
    };
    struct MaterialFileHeader {
        uint32_t Version;
        uint16_t FileSize;
        // TODO: DataSetSize = FileSize >> 16;
        uint16_t DataSetSize;
        uint16_t StringTableSize;
        uint16_t ShaderPackageNameOffset;
        uint8_t TextureCount;
        uint8_t UvSetCount;
        uint8_t ColorSetCount;
        uint8_t AdditionalDataSize;
    };

    struct MaterialHeader {
        uint16_t ShaderValueListSize;
        uint16_t ShaderKeyCount;
        uint16_t ConstantCount;
        uint16_t SamplerCount;
        uint16_t Unknown1;
        uint16_t Unknown2;
    };

    struct TextureOffset {
        uint16_t Offset;
        uint16_t Flags;
    };

    struct Constant {
        uint32_t ConstantId;
        uint16_t ValueOffset;
        uint16_t ValueSize;
    };

    struct Sampler {
        uint32_t SamplerId;
        uint32_t Flags;
        uint8_t TextureIndex;
        unsigned char Padding[3];
    };

    struct ShaderKey {
        uint32_t Category;
        uint32_t Value;
    };

    struct UvColorSet {
        uint16_t NameOffset;
        uint8_t Index;
        unsigned char Unknown1;
    };

    struct ColorSet {
        uint16_t NameOffset;
        uint8_t Index;
        unsigned char Unknown1;
    };

    struct ColorSetInfo {
        uint16_t Data[256];
    };

    struct ColorSetDyeInfo {
        uint16_t Data[16];
    };
};

