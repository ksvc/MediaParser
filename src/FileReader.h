#ifndef FILEREADER_H
#define FILEREADER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

class FileReader
{
public:
    FileReader();
    ~FileReader();

public:
    int Open(const char* fileName);
    int Close();

    int GetLength();
    int GetPos();
    int SetPos(int pos);

    uint8_t Read8();
    uint16_t Read16();
    uint32_t Read24();
    uint32_t Read32();
    uint64_t Read64();
    int Skip(int len);
    int ReadBuffer(char* buffer, int len);

private:
    FILE* fd;
};

#endif // FILEREADER_H
