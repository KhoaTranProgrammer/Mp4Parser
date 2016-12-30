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
	H.264 video
*/
#ifndef AVC1ATOM_H
#define AVC1ATOM_H
#include "Atom.h"
#include "AVCCAtom.h"

typedef struct _avc1Atom
{
	BASE_ATOM
	uchar* reserved;	//6 bytes
	ushort dataReferenceIndex;
	uint* reserved1;	//16 bytes
	uint reserved2;
	uint reserved3;
	uint reserved4;
	uint reserved5;
	ushort reserved6;
	uchar* reserved7;
	ushort reserved8;
	ushort reserved9;
	AvccAtom* videoSampleDescriptionExtensions;
}Avc1Atom;

#endif
