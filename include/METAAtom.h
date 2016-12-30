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
	Metadata Atom

The metadata atom is the container for carrying metadata.
*/
#ifndef METAATOM_H
#define METAATOM_H
#include "Atom.h"
#include "HDLRAtom.h"

typedef struct _metaAtom
{
	FULL_ATOM
	HdlrAtom* hdlrAtom;	//Metadata Handler Atom
	//unsupport: mhdr, keys, ilst
	uchar* data;
}MetaAtom;

#endif
