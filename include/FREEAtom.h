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
	Free Space Atoms

Both free and skip atoms designate unused space in the movie data file. These atoms consist of only an atom header (size and type fields), followed by the appropriate number of bytes of free space. When reading a QuickTime movie, your application may safely skip these atoms. When writing or updating a movie, you may reuse the space associated with these atom types.
*/
#ifndef FREEATOM_H
#define FREEATOM_H
#include "Atom.h"

typedef struct _freeAtom
{
	BASE_ATOM
	uint dataSize;
	uchar* data;
}FreeAtom;

#endif

