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
	Time-to-sample atoms store duration information for a media’s samples, providing a mapping from a time in a media to the corresponding data sample. The time-to-sample atom has an atom type of 'stts'.
*/
#ifndef STTSATOM_H
#define STTSATOM_H
#include "Atom.h"

typedef struct _sttsAtom
{
	FULL_ATOM
	uint numberOfEntries;
	//Time-to-sample table
	uint* sampleCount;
	uint* sampleDuration;
}SttsAtom;

#endif
