#include "FileReader.h"

FileReader::FileReader()
{
    fd = NULL;
}

FileReader::~FileReader()
{
    Close();
}

int FileReader::Open(const char* fileName)
{
    fd = fopen(fileName, "rb");
    if(fd == NULL)
        return -1;
    return 0;
}

int FileReader::Close()
{
    if(fd)
    {
        fclose(fd);
        fd = NULL;
    }
    return 0;
}

int FileReader::GetLength()
{
    int cur = ftell(fd);

    fseek(fd, 0, SEEK_END);
    int file_size = ftell(fd);
    fseek(fd, cur, SEEK_SET);
    return file_size;
}

int FileReader::GetPos()
{
    return ftell(fd);
}

int FileReader::SetPos(int pos)
{
    fseek(fd, pos, SEEK_SET);
    return 0;
}

uint8_t FileReader::Read8()
{
    uint8_t ret;
    fread(&ret, 1, 1, fd);
    return ret;
}

uint16_t FileReader::Read16()
{
    uint8_t buffer[2];
    fread(buffer, 2, 1, fd);
    return ((buffer[0]<<8) | buffer[1]);
}

uint32_t FileReader::Read24()
{
    uint8_t buffer[3];
    fread(buffer, 3, 1, fd);
    return ((buffer[1]<<16) | (buffer[1]<<8) | buffer[2]);
}

uint32_t FileReader::Read32()
{
    uint8_t buffer[4] = {0};
    fread(buffer, 4, 1, fd);
    return (buffer[0]<<24) | (buffer[1]<<16) | (buffer[2]<<8) | (buffer[3]);
}

uint64_t FileReader::Read64()
{
    uint64_t h = Read32();
    uint64_t l = Read32();
    return (h<<32) | l;
}

int FileReader::Skip(int len)
{
    return fseek(fd, len, SEEK_CUR);
}

int FileReader::ReadBuffer(char* buffer, int len)
{
    return fread(buffer, 1, len, fd);
}
