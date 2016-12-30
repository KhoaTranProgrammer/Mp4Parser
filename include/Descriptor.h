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

/*
	Elementary Stream Descriptor

    An elementary stream descriptor for MPEG-4 audio, as defined in the MPEG-4 specification ISO/IEC 14496.
*/
#ifndef DESCRIPTORATOM_H
#define DESCRIPTORATOM_H
#include "Type.h"
#include "FileReader.h"

enum {
	ES  = 0x03,	//ES_Descriptor
	DEC = 0x04,	//DecoderConfigDescriptor
	DSI = 0x05,	//DecoderSpecificInfo
	SLC = 0x06, //SLConfigDescriptor
};

//372
#define BASE_DESC	\
	uchar TAG;		\
	uchar length;	\
					\
	ErrInfo (*createDescFromFile)(struct Desc* me, FileReader* fileReader);	\
	void (*destroy)(struct Desc* me);	\

struct Desc
{
	BASE_DESC
};

struct ES_Descriptor
{
	BASE_DESC
	ushort ES_ID;	//16 bits
	uchar streamDependenceFlag;	//1 bit
	uchar URL_Flag;	//1 bit
	uchar OCRstreamFlag;	//1 bit
	uchar streamPriority;	//5 bits
	ushort dependsOn_ES_ID;	//16 bits
	uchar URLlength;	//8 bits
	uchar* URLstring;	//8xURLlength bits
	ushort OCR_ES_Id;	//16 bits
	struct Desc* decConfigDescr;
	struct Desc* slConfigDescr;
	struct Desc* ipiPtr;
	struct Desc* ipIDS;
	struct Desc* ipmpDescrPtr;
	struct Desc* langDescr;
	struct Desc* qosDescr;
	struct Desc* regDescr;
	struct Desc* extDescr;
};

struct DecoderConfigDescriptor
{
	BASE_DESC
	uchar objectTypeIndication;	//8 bits
	uchar streamType;	//6 bits
	uchar upStream;	//1 bit
	uchar reserved;	//1 bit
	uchar* bufferSizeDB;	//24 bits
	uint maxBitrate;	//32 bits
	uint avgBitrate;	//32 bits
	struct Desc* decSpecificInfo;
	struct Desc* profileLevelIndicationIndexDescr;
};

struct DecoderSpecificInfo
{
	BASE_DESC
	uchar* data;
};

struct SLConfigDescriptor
{
	BASE_DESC
	uchar predefined;	//8 bits
    
	//if (predefined==0)
    uchar useAccessUnitStartFlag;	//1 bit
    uchar useAccessUnitEndFlag;	//1 bit
    uchar useRandomAccessPointFlag;	//1 bit
    uchar hasRandomAccessUnitsOnlyFlag;	//1 bit
    uchar usePaddingFlag;	//1 bit
    uchar useTimeStampsFlag;	//1 bit
    uchar useIdleFlag;	//1 bit
    uchar durationFlag;	//1 bit
    uint timeStampResolution;	//32 bits
    uint OCRResolution;	//32 bits
    uchar timeStampLength; //8 bits - must be <= 64
    uchar OCRLength; //8 bits - must be <= 64
    uchar AU_Length; //8 bits -  must be <= 32
    uchar instantBitrateLength;	//8 bits
    uchar degradationPriorityLength;	//4 bits
    uchar AU_seqNumLength; //5 bits - must be <= 16
    uchar packetSeqNumLength; //5 bits - must be <= 16
    uchar reserved;	//2 bits

	//if (durationFlag)
	uint timeScale;	//32 bits
	ushort accessUnitDuration;	//16 bits
	ushort compositionUnitDuration;	//16 bits
 
	//if (!useTimeStampsFlag)
	uchar* startDecodingTimeStamp;
	uchar* startCompositionTimeStamp;
};

//Parse fully 1 Descriptor includes: header(TAG and length) and data
ErrInfo ParseDescriptor(struct Desc** desc, FileReader* fileReader);

//Create basic information that includes: TAG and length
ErrInfo CreateESDesc (struct Desc** me, uchar TAG, uchar length);	//ES_Descriptor
ErrInfo CreateDECDesc(struct Desc** me, uchar TAG, uchar length);	//DecoderConfigDescriptor
ErrInfo CreateDSIDesc(struct Desc** me, uchar TAG, uchar length);	//DecoderSpecificInfo
ErrInfo CreateSLCDesc(struct Desc** me, uchar TAG, uchar length);	//SLConfigDescriptor

#endif
