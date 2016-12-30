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
	The track header atom specifies the characteristics of a single track within a movie. A track header atom contains a size field that specifies the number of bytes and a type field that indicates the format of the data (defined by the atom type 'tkhd').
*/
#ifndef TKHDATOM_H
#define TKHDATOM_H
#include "Atom.h"

typedef struct _tkhdAtom
{
	FULL_ATOM
	uint creationTime;
	uint modificationTime;
	uint trackID;
	uchar* reserved1;
	uint duration;
	uchar* reserved2;
	ushort layer;
	ushort alternateGroup;
	ushort volume;
	uchar* reserved3;
	uint matrixStructure[9];
	uint trackWidth;	//A 32-bit fixed-point number that specifies the width of this track in pixels.
	uint trackHeight;	//A 32-bit fixed-point number that indicates the height of this track in pixels.
}TkhdAtom;

#endif //TKHDATOM_H
