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
	The sample table atom contains information for converting from media time to sample number to sample location. This atom also indicates how to interpret the sample (for example, whether to decompress the video data and, if so, how). This section describes the format and content of the sample table atom.
*/
#ifndef STBLATOM_H
#define STBLATOM_H
#include "Atom.h"
#include "STSDAtom.h"
#include "STTSAtom.h"
#include "STSSAtom.h"
#include "STSCAtom.h"
#include "STSZAtom.h"
#include "STCOAtom.h"

typedef struct _stblAtom
{
	BASE_ATOM
	StsdAtom* stsdAtom;	//Sample description atom
	SttsAtom* sttsAtom;	//Time-to-sample atom
	StssAtom* stssAtom;	//Sync sample atom
	StscAtom* stscAtom;	//Sample-to-chunk atom
	StszAtom* stszAtom;	//Sample size atom
	StcoAtom* stcoAtom;	//Chunk offset atom
}StblAtom;

#endif
