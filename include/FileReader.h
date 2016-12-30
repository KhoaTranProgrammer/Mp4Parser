/*
 * Copyright (C) 2016 KhoaTran Programmer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FILEREADER_H
#define FILEREADER_H
#include "Type.h"

typedef struct _fileReader
{
	FILE* f;
	void (*destroy)(struct _fileReader* me);
	ErrInfo (*readDataFromFile)(struct _fileReader* me, uchar **outData, int bytes);
	ErrInfo (*read1Byte)(struct _fileReader* me, uchar* outData);
	ErrInfo (*read2Bytes)(struct _fileReader* me, uint* outData);
	ErrInfo (*read4Bytes)(struct _fileReader* me, uint* outData);
} FileReader;

ErrInfo CreateMp4FileReader(FileReader** me, char* filename);
#endif //FILEREADER_H
