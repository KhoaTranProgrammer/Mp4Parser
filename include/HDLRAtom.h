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
	The handler reference atom specifies the media handler component that is to be used to interpret the media’s data. The handler reference atom has an atom type value of 'hdlr'.
*/
#ifndef HDLRATOM_H
#define HDLRATOM_H
#include "Atom.h"

typedef struct _hdlrAtom
{
	FULL_ATOM
	uchar* componentType;
	uchar* componentSubtype;
	uint componentManufacture;
	uint componentFlags;
	uint componentFlagsMask;
	uchar* componentName;
	int nameLength;
}HdlrAtom;

#endif
