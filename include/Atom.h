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

#ifndef ATOM_H
#define ATOM_H

#include "Type.h"
#include "FileReader.h"

//Atom type
enum {
	FTYP	=	CONVERT_CHAR2INT('f', 't', 'y', 'p'),
	MOOV	=	CONVERT_CHAR2INT('m', 'o', 'o', 'v'),
	MVHD	=	CONVERT_CHAR2INT('m', 'v', 'h', 'd'),
	TRAK	=	CONVERT_CHAR2INT('t', 'r', 'a', 'k'),
	TKHD	=	CONVERT_CHAR2INT('t', 'k', 'h', 'd'),
	MDIA	=	CONVERT_CHAR2INT('m', 'd', 'i', 'a'),
	MDHD	=	CONVERT_CHAR2INT('m', 'd', 'h', 'd'),
	HDLR	=	CONVERT_CHAR2INT('h', 'd', 'l', 'r'),
	MINF	=	CONVERT_CHAR2INT('m', 'i', 'n', 'f'),
	VMHD	=	CONVERT_CHAR2INT('v', 'm', 'h', 'd'),
	SMHD	=	CONVERT_CHAR2INT('s', 'm', 'h', 'd'),
	DINF	=	CONVERT_CHAR2INT('d', 'i', 'n', 'f'),
	DREF	=	CONVERT_CHAR2INT('d', 'r', 'e', 'f'),
	URL		=	CONVERT_CHAR2INT('u', 'r', 'l', ' '),
	STBL	=	CONVERT_CHAR2INT('s', 't', 'b', 'l'),
	STSD	=	CONVERT_CHAR2INT('s', 't', 's', 'd'),
	AVC1	=	CONVERT_CHAR2INT('a', 'v', 'c', '1'),
	AVCC	=	CONVERT_CHAR2INT('a', 'v', 'c', 'C'),
	STTS	=	CONVERT_CHAR2INT('s', 't', 't', 's'),
	STSS	=	CONVERT_CHAR2INT('s', 't', 's', 's'),
	STSC	=	CONVERT_CHAR2INT('s', 't', 's', 'c'),
	STSZ	=	CONVERT_CHAR2INT('s', 't', 's', 'z'),
	STCO	=	CONVERT_CHAR2INT('s', 't', 'c', 'o'),
	MP4A	=	CONVERT_CHAR2INT('m', 'p', '4', 'a'),
	ESDS	=	CONVERT_CHAR2INT('e', 's', 'd', 's'),
	UDTA	=	CONVERT_CHAR2INT('u', 'd', 't', 'a'),
	META	=	CONVERT_CHAR2INT('m', 'e', 't', 'a'),
	FREE	=	CONVERT_CHAR2INT('f', 'r', 'e', 'e'),
	MDAT	=	CONVERT_CHAR2INT('m', 'd', 'a', 't'),
};

//Handle reference
enum {
	VIDE	=	CONVERT_CHAR2INT('v', 'i', 'd', 'e'),
	SOUN	=	CONVERT_CHAR2INT('s', 'o', 'u', 'n'),
};

#define BASE_ATOM																\
	uint size;																	\
	int64 size64;																\
	uint type;																	\
	ErrInfo (*createDataFromFile)(struct _atom* me, FileReader* fileReader);	\
	void (*destroy)(struct _atom* me);											\
	int remainBytes;															\

#define FULL_ATOM	\
	BASE_ATOM		\
	uchar version;	\
	uchar* flags;	\

typedef struct _atom
{
	BASE_ATOM
}Atom;

//Parse fully 1 atom includes: header(size and type) and data
ErrInfo ParseAtom(Atom** atom, FileReader* fileReader);

//Create header that includes: size and type
ErrInfo CreateFtypAtom(Atom** me, uint size, uint type);
ErrInfo CreateMoovAtom(Atom** me, uint size, uint type);
ErrInfo CreateMvhdAtom(Atom** me, uint size, uint type);
ErrInfo CreateTrakAtom(Atom** me, uint size, uint type);
ErrInfo CreateTkhdAtom(Atom** me, uint size, uint type);
ErrInfo CreateMdiaAtom(Atom** me, uint size, uint type);
ErrInfo CreateMdhdAtom(Atom** me, uint size, uint type);
ErrInfo CreateHdlrAtom(Atom** me, uint size, uint type);
ErrInfo CreateMinfAtom(Atom** me, uint size, uint type);
ErrInfo CreateVmhdAtom(Atom** me, uint size, uint type);
ErrInfo CreateSmhdAtom(Atom** me, uint size, uint type);
ErrInfo CreateDinfAtom(Atom** me, uint size, uint type);
ErrInfo CreateDrefAtom(Atom** me, uint size, uint type);
ErrInfo CreateUrlAtom (Atom** me, uint size, uint type);
ErrInfo CreateStblAtom(Atom** me, uint size, uint type);
ErrInfo CreateStsdAtom(Atom** me, uint size, uint type);
ErrInfo CreateAvc1Atom(Atom** me, uint size, uint type);
ErrInfo CreateAvccAtom(Atom** me, uint size, uint type);
ErrInfo CreateSttsAtom(Atom** me, uint size, uint type);
ErrInfo CreateStssAtom(Atom** me, uint size, uint type);
ErrInfo CreateStscAtom(Atom** me, uint size, uint type);
ErrInfo CreateStszAtom(Atom** me, uint size, uint type);
ErrInfo CreateStcoAtom(Atom** me, uint size, uint type);
ErrInfo CreateMp4aAtom(Atom** me, uint size, uint type);
ErrInfo CreateEsdsAtom(Atom** me, uint size, uint type);
ErrInfo CreateUdtaAtom(Atom** me, uint size, uint type);
ErrInfo CreateMetaAtom(Atom** me, uint size, uint type);
ErrInfo CreateFreeAtom(Atom** me, uint size, uint type);
ErrInfo CreateMdatAtom(Atom** me, uint size, uint type);

#endif //ATOM_H
