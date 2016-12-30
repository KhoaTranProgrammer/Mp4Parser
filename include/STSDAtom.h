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
	The sample description atom stores information that allows you to decode samples in the media. The data stored in the sample description varies, depending on the media type. For example, in the case of video media, the sample descriptions are image description structures. The sample description information for each media type is explained in Media Data Atom Types
*/
#ifndef STSDATOM_H
#define STSDATOM_H
#include "Atom.h"
#include "AVC1Atom.h"

typedef struct _stsdAtom
{
	FULL_ATOM
	uint numberOfEntries;
	Atom** sampleDescriptionTable;	//An array of sample descriptions
}StsdAtom;

#endif
