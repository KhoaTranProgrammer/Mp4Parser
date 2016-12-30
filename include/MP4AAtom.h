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
	MPEG-4, Advanced Audio Coding (AAC)
*/
#ifndef MP4AATOM_H
#define MP4AATOM_H
#include "Atom.h"

typedef struct _mp4aAtom
{
	BASE_ATOM
	uchar* reserved;	//6 bytes
	ushort dataReferenceIndex;
	uint reserved1[2];	//8 bytes
	ushort reserved2;
	ushort reserved3;
	uint reserved4;
	ushort timeScale;
	ushort reserved5;
	Atom* soundSampleDescriptionExtensions;
}Mp4aAtom;

#endif
