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
	Media atoms describe and define a track’s media type and sample data. The media atom contains information that specifies:

    The media type, such as sound, video or timed metadata

    The media handler component used to interpret the sample data

    The media timescale and track duration

    Media-and-track-specific information, such as sound volume or graphics mode

    The media data references, which typically specify the file where the sample data is stored

    The sample table atoms, which, for each media sample, specify the sample description, duration, and byte offset from the data reference
*/
#ifndef MDIAATOM_H
#define MDIAATOM_H
#include "Atom.h"
#include "MDHDAtom.h"
#include "HDLRAtom.h"
#include "MINFAtom.h"

typedef struct _mdiaAtom
{
	BASE_ATOM
	MdhdAtom* mdhdAtom;	//Media header atom
	HdlrAtom* hdlrAtom;	//Handler reference atom
	MinfAtom* minfAtom;	//Media information atom
}MdiaAtom;

#endif
