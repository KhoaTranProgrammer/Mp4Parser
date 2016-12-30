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
	Video media information atoms are the highest-level atoms in video media. These atoms contain a number of other atoms that define specific characteristics of the video media data. Figure 2-24 shows the layout of a video media information atom.
*/
#ifndef MINFATOM_H
#define MINFATOM_H
#include "Atom.h"
#include "VMHDAtom.h"
#include "SMHDAtom.h"
#include "DINFAtom.h"
#include "STBLAtom.h"

typedef struct _minfAtom
{
	BASE_ATOM
	VmhdAtom* vmhdAtom;	//Video media information header atom
	SmhdAtom* smhdAtom;	//Sound media information header atom
	DinfAtom* dinfAtom;	//Data information atom
	StblAtom* stblAtom;	//Sample table atom
}MinfAtom;

#endif
