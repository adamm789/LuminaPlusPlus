#include "LuminaBinaryReader.h"

LuminaBinaryReader::LuminaBinaryReader(std::vector<std::byte> arr) {
	Data = arr;
}

void LuminaBinaryReader::MemCpy(void* dest, int numBytes) {
	memcpy(dest, &Data[Position], numBytes);
	Position += numBytes;
}

void LuminaBinaryReader::Seek(long pos) {
	Position = pos;
}

unsigned char LuminaBinaryReader::ReadByte() {
	unsigned char ret = (unsigned char)Data[Position];
	Position += sizeof(unsigned char);
	return ret;
}

unsigned char* LuminaBinaryReader::ReadBytes(int num) {
	unsigned char* ret = new unsigned char[num];
	memcpy(ret, &Data[Position], num);
	Position += num;
	return ret;
}

int16_t LuminaBinaryReader::ReadInt16()
{
	int16_t val;
	memcpy(&val, &Data[Position], sizeof(int16_t));
	Position += sizeof(int16_t);
	return val;
}

uint16_t LuminaBinaryReader::ReadUInt16()
{
	uint16_t val;
	memcpy(&val, &Data[Position], sizeof(uint16_t));
	Position += sizeof(uint16_t);
	return val;
}

uint32_t LuminaBinaryReader::ReadUInt32()
{
	uint32_t val;
	memcpy(&val, &Data[Position], sizeof(uint32_t));
	Position += sizeof(uint32_t);
	return val;
}
