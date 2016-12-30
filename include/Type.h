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

#ifndef TYPE_H
#define TYPE_H

#include "stdio.h"
#include "malloc.h"

typedef long long int64;
typedef unsigned long long uint64;
typedef unsigned int uint;
typedef int ErrInfo;
typedef unsigned char uchar;
typedef unsigned short ushort;

enum
{
	NoError,
	NoInputFound,
	FileEOF,
	MemError,
	NullAtom,
	UnkownAtom,
	UnkownDescriptor,
};

#define CONVERT_CHAR2INT( a, b, c, d ) (((a) << 24) | ((b) << 16)| ((c) << 8) | (d))
#define CONVERT_CHAR2SHORT( c, d ) (((c) << 8) | (d))

#define CHECK_MEM(p)		\
	if(p == NULL)			\
		return MemError;	\

#define FREE_MEM(p)	\
	if(p == NULL)	\
		free(p);	\

#define CHECK_ERROR(err)\
	if(err != NoError)	\
		return err;		\

#define READ_BYTES(fileReader, myself, data, number)							\
	err = fileReader->readDataFromFile(fileReader, (uchar**)(&data), number);	\
	CHECK_ERROR(err);															\
	myself->remainBytes -= number;												\

#define READ_BYTE(fileReader, myself, data)			\
	err = fileReader->read1Byte(fileReader, &data);	\
	CHECK_ERROR(err);								\
	myself->remainBytes -= 1;						\

#define READ_2BYTES(fileReader, myself, data)			\
	err = fileReader->read2Bytes(fileReader, &data);	\
	CHECK_ERROR(err);									\
	myself->remainBytes -= 2;							\

#define READ_4BYTES(fileReader, myself, data)			\
	err = fileReader->read4Bytes(fileReader, &data);	\
	CHECK_ERROR(err);									\
	myself->remainBytes -= 4;							\

#define SET_BASEATOM(atom)							\
	CHECK_MEM(atom);								\
	atom->createDataFromFile = createDataFromFile;	\
	atom->destroy = destroy;						\
	atom->size = size;								\
	atom->type = type;								\

#define FREE_BASEATOM(atom)				\
	atom->createDataFromFile = NULL;	\
	atom->destroy = NULL;				\

#define FREE_FULLATOM(atom)	\
	FREE_BASEATOM(atom)		\
	free(atom->flags);		\

//update the size of data after subtracting header size
#define CAL_DATASIZE(myself)					\
	if(myself->size == 1)						\
	{											\
		/* unsupport */							\
	}else{										\
		myself->remainBytes = myself->size - 8;	\
	}											\

#endif //TYPE_H
