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

#include "FileReader.h"

static void destroy(FileReader* me)
{
	if(me->f != NULL) fclose(me->f);
	free(me);
}

static ErrInfo readDataFromFile(FileReader* me, uchar **outData, int bytes)
{
	ErrInfo err = NoError;
	char* data;
	
	if(feof(me->f)) return FileEOF;
	data = (char*) malloc(bytes);
	CHECK_MEM(data);

	fread(data, bytes, 1, me->f);

	*outData = data;
	return err;
}

static ErrInfo read1Byte(FileReader* me, uchar* outData)
{
	ErrInfo err = NoError;
	uchar* data;

	err = readDataFromFile(me, &data, 1);
	if(err == NoError)
	{
		*outData = data[0];
	}

	FREE_MEM(data);

	return err;
}

static ErrInfo read2Bytes(FileReader* me, ushort* outData)
{
	ErrInfo err = NoError;
	uchar* data;

	err = readDataFromFile(me, &data, 2);
	if(err == NoError)
	{
		*outData = CONVERT_CHAR2SHORT(data[0], data[1]);
	}

	FREE_MEM(data);

	return err;
}

static ErrInfo read4Bytes(FileReader* me, uint* outData)
{
	ErrInfo err = NoError;
	uchar* data;

	err = readDataFromFile(me, &data, 4);
	if(err == NoError)
	{
		*outData = CONVERT_CHAR2INT(data[0], data[1], data[2], data[3]);
	}

	FREE_MEM(data);

	return err;
}

ErrInfo CreateMp4FileReader(FileReader** me, char* filename)
{
	ErrInfo err = NoError;

	*me = (FileReader*) malloc(sizeof(FileReader));
	CHECK_MEM(*me);

	(*me)->f = fopen(filename, "rb");
	CHECK_MEM((*me)->f);

	(*me)->destroy = destroy;
	(*me)->readDataFromFile = readDataFromFile;
	(*me)->read1Byte = read1Byte;
	(*me)->read2Bytes = read2Bytes;
	(*me)->read4Bytes = read4Bytes;
	return err;
}
