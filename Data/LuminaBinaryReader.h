#pragma once

#include <memory>
#include <iostream>
#include "Parsing/MdlStructs.h"
#include <vector>


class LuminaBinaryReader {
public:
	LuminaBinaryReader(std::vector<std::byte> arr);

	void Seek(long pos);

	bool IsLittlleEndian;
	long Position = 0;
	std::vector<std::byte> Data;

	unsigned char ReadByte();
	unsigned char* ReadBytes(int num);
	int16_t ReadInt16();
	uint16_t ReadUInt16();
	int32_t ReadInt32();
	uint32_t ReadUInt32();
	int64_t ReadInt64();
	uint64_t ReadUInt64();
	float ReadSingle();
	double ReadDouble();

	template <typename T> void ReadStructure(T* arg);

	template <typename T> void CopyBytesInto(T& arg, int numBytes);

	void MemCpy(void* dest, int numBytes);
};

template<typename T>
inline void LuminaBinaryReader::ReadStructure(T* arg)
{
	memcpy(arg, &Data[Position], sizeof(T));
	Position += sizeof(T);
}

template<typename T>
inline void LuminaBinaryReader::CopyBytesInto(T& arg, int numBytes)
{
	memcpy(&arg, &Data[Position], numBytes);
	Position += numBytes;
}