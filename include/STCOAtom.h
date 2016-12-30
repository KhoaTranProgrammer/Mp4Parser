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
	Chunk Offset Atoms

Chunk offset atoms identify the location of each chunk of data in the media’s data stream. Chunk offset atoms have an atom type of 'stco'.

The chunk-offset table gives the index of each chunk into the containing file. There are two variants, permitting the use of 32-bit or 64-bit offsets. The latter is useful when managing very large movies. Only one of these variants occurs in any single instance of a sample table atom.
*/
#ifndef STCOATOM_H
#define STCOATOM_H
#include "Atom.h"

typedef struct _stcoAtom
{
	FULL_ATOM
	uint numberOfEntries;
	//Chunk offset table
	uint* chunkOffsetTable;
}StcoAtom;

#endif
