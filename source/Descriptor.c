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

#include "Descriptor.h"

ErrInfo ParseDescriptor(struct Desc** desc, FileReader* fileReader)
{
	ErrInfo err = NoError;
	uchar TAG, length;
	int sizeOfInstance;
	uchar nextByte, sizeByte;
	int readBytes;
	
	//read the descriptor TAG
	err = fileReader->read1Byte(fileReader, &TAG);
	CHECK_ERROR(err);

	//read the descriptor size
	err = fileReader->read1Byte(fileReader, &length);
	CHECK_ERROR(err);
	sizeOfInstance = 0;
	nextByte = 1;
	readBytes = 1;
	while(nextByte) {
		nextByte = length & 0x80;
		sizeByte = length & 0x7F;
		sizeOfInstance = sizeOfInstance << 7 | sizeByte;
		readBytes++;
	}
	length = sizeOfInstance + readBytes;

	switch(TAG){
		case ES:
			err = CreateESDesc (desc, TAG, length); break;
		case DEC:
			err = CreateDECDesc(desc, TAG, length); break;
		case DSI:
			err = CreateDSIDesc(desc, TAG, length); break;
		case SLC:
			err = CreateSLCDesc(desc, TAG, length); break;
		default:
			err = UnkownDescriptor; break;
	}

	if(err == NoError)
	{
		err = (*desc)->createDescFromFile(*desc, fileReader);
	}

	return err;
}

/* ES_Descriptor */
#if 1
static ErrInfo createESDescFromFile(struct Desc* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	struct ES_Descriptor* myself;
	struct Desc* newDesc;
	uint remainBytes;
	uchar temp;

	myself = (struct ES_Descriptor*)me;
	remainBytes = myself->length - 2;

	//read ES_ID
	err = fileReader->read2Bytes(fileReader, &myself->ES_ID);
	remainBytes -= 2;
	CHECK_ERROR(err);

	//read next 1 byte
	err = fileReader->read1Byte(fileReader, &temp);
	remainBytes -= 1;
	CHECK_ERROR(err);

	//get streamDependenceFlag, URL_Flag, OCRstreamFlag, streamPriority
	myself->streamDependenceFlag = temp & (1 << 7) ? 1 : 0;
	myself->URL_Flag = temp & (1 << 6) ? 1 : 0;
	myself->OCRstreamFlag = temp & (1 << 5) ? 1 : 0;
	myself->streamPriority = temp & 0x1f;

	//read dependsOn_ES_ID
	if(myself->streamDependenceFlag)
	{
		//unsupport
	}

	//read URLstring, URLlength
	if(myself->URL_Flag)
	{
		//unsupport
	}

	//read OCR_ES_Id
	if(myself->OCRstreamFlag)
	{
		//unsupport
	}

	//read Elementary Stream Descriptor
	while(remainBytes)
	{
		err = ParseDescriptor(&newDesc, fileReader);
		CHECK_ERROR(err);
		switch(newDesc->TAG)
		{
			case DEC: myself->decConfigDescr = newDesc; break;
			case SLC: myself->slConfigDescr = newDesc; break;
			default: err = UnkownDescriptor; break;
		}
		remainBytes -= newDesc->length;
	};

	return err;
}

static void destroyESDesc(struct Desc* me)
{
	struct ES_Descriptor* myself;
	myself = (struct ES_Descriptor*)me;

	myself->decConfigDescr->destroy(myself->decConfigDescr);
	myself->slConfigDescr->destroy(myself->slConfigDescr);
	free(myself);
}

ErrInfo CreateESDesc(struct Desc** me, uchar TAG, uchar length)
{
	ErrInfo err = NoError;
	struct ES_Descriptor* myself;

	myself = (struct ES_Descriptor*) malloc(sizeof(struct ES_Descriptor));
	myself->TAG = TAG;
	myself->length = length;
	myself->createDescFromFile = createESDescFromFile;
	myself->destroy = destroyESDesc;
	*me = (struct Desc*)myself;
	return err;
}
#endif

/* DecoderConfigDescriptor */
#if 1
static ErrInfo createDECDescFromFile(struct Desc* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	struct DecoderConfigDescriptor* myself;
	struct Desc* newDesc;
	uint remainBytes;
	uchar temp;

	myself = (struct DecoderConfigDescriptor*)me;
	remainBytes = myself->length - 2;

	//read objectTypeIndication
	err = fileReader->read1Byte(fileReader, &myself->objectTypeIndication);
	remainBytes -= 1;
	CHECK_ERROR(err);

	//read next 1 byte
	err = fileReader->read1Byte(fileReader, &temp);
	remainBytes -= 1;
	CHECK_ERROR(err);

	//get streamType, upStream, reserved
	myself->streamType = temp >> 2;
	myself->upStream = (temp >> 1) & 1;
	myself->reserved = temp & 1;

	//read bufferSizeDB
	err = fileReader->readDataFromFile(fileReader, (uchar**)(&myself->bufferSizeDB), 3);
	remainBytes -= 3;
	CHECK_ERROR(err);

	//read maxBitrate
	err = fileReader->read4Bytes(fileReader, &myself->maxBitrate);
	remainBytes -= 4;
	CHECK_ERROR(err);

	//read avgBitrate
	err = fileReader->read4Bytes(fileReader, &myself->avgBitrate);
	remainBytes -= 4;
	CHECK_ERROR(err);

	//read Elementary Stream Descriptor
	while(remainBytes)
	{
		err = ParseDescriptor(&newDesc, fileReader);
		CHECK_ERROR(err);
		switch(newDesc->TAG)
		{
			case DSI: myself->decSpecificInfo = newDesc; break;
			default: err = UnkownDescriptor; break;
		}
		remainBytes -= newDesc->length;
	};

	return err;
}

static void destroyDECDesc(struct Desc* me)
{
	struct DecoderConfigDescriptor* myself;
	myself = (struct DecoderConfigDescriptor*)me;

	free(myself->bufferSizeDB);
	myself->decSpecificInfo->destroy(myself->decSpecificInfo);
	free(myself);
}

ErrInfo CreateDECDesc(struct Desc** me, uchar TAG, uchar length)
{
	ErrInfo err = NoError;
	struct DecoderConfigDescriptor* myself;

	myself = (struct DecoderConfigDescriptor*) malloc(sizeof(struct DecoderConfigDescriptor));
	myself->TAG = TAG;
	myself->length = length;
	myself->createDescFromFile = createDECDescFromFile;
	myself->destroy = destroyDECDesc;
	*me = (struct Desc*)myself;
	return err;
}
#endif

/* DecoderSpecificInfo */
#if 1
static ErrInfo createDSIDescFromFile(struct Desc* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	struct DecoderSpecificInfo* myself;
	struct Desc* newDesc;
	uint remainBytes;

	myself = (struct DecoderSpecificInfo*)me;
	remainBytes = myself->length - 2;

	//read data
	if(remainBytes > 0)
	{
		err = fileReader->readDataFromFile(fileReader, (uchar**)(&myself->data), remainBytes);
		remainBytes = 0;
		CHECK_ERROR(err);
	}

	return err;
}

static void destroyDSIDesc(struct Desc* me)
{
	struct DecoderConfigDescriptor* myself;
	myself = (struct DecoderSpecificInfo*)me;

	free(myself);
}

ErrInfo CreateDSIDesc(struct Desc** me, uchar TAG, uchar length)
{
	ErrInfo err = NoError;
	struct DecoderConfigDescriptor* myself;

	myself = (struct DecoderSpecificInfo*) malloc(sizeof(struct DecoderSpecificInfo));
	myself->TAG = TAG;
	myself->length = length;
	myself->createDescFromFile = createDSIDescFromFile;
	myself->destroy = destroyDSIDesc;
	*me = (struct Desc*)myself;
	return err;
}
#endif

/* SLConfigDescriptor */
#if 1
static ErrInfo createSLCDescFromFile(struct Desc* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	struct SLConfigDescriptor* myself;
	uint remainBytes;

	myself = (struct SLConfigDescriptor*)me;
	remainBytes = myself->length - 2;

	//read predefined
	err = fileReader->read1Byte(fileReader, &myself->predefined);
	remainBytes -= 1;
	CHECK_ERROR(err);

	if (myself->predefined == 0)
	{
		//unsupport
	}
	return err;
}

static void destroySLCDesc(struct Desc* me)
{
	struct SLConfigDescriptor* myself;
	myself = (struct SLConfigDescriptor*)me;

	free(myself);
}

ErrInfo CreateSLCDesc(struct Desc** me, uchar TAG, uchar length)
{
	ErrInfo err = NoError;
	struct SLConfigDescriptor* myself;

	myself = (struct SLConfigDescriptor*) malloc(sizeof(struct SLConfigDescriptor));
	myself->TAG = TAG;
	myself->length = length;
	myself->createDescFromFile = createSLCDescFromFile;
	myself->destroy = destroySLCDesc;
	*me = (struct Desc*)myself;
	return err;
}
#endif
