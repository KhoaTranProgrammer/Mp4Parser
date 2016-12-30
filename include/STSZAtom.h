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
	Sample Size Atoms

You use sample size atoms to specify the size of each sample in the media. Sample size atoms have an atom type of 'stsz'.

The sample size atom contains the sample count and a table giving the size of each sample. This allows the media data itself to be unframed. The total number of samples in the media is always indicated in the sample count. If the default size is indicated, then no table follows.
*/
#ifndef STSZATOM_H
#define STSZATOM_H
#include "Atom.h"

typedef struct _stszAtom
{
	FULL_ATOM
	uint sampleSize;
	uint numberOfEntries;
	//Sample size table
	uint* sampleSizeTable;
}StszAtom;

#endif
