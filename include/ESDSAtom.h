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
	MPEG-4 Elementary Stream Descriptor Atom ('esds')

This atom is a required extension to the sound sample description for MPEG-4 audio. This atom contains an elementary stream descriptor, which is defined in ISO/IEC FDIS 14496.
*/
#ifndef ESDSATOM_H
#define ESDSATOM_H
#include "Atom.h"
#include "Descriptor.h"

typedef struct _esdsAtom
{
	FULL_ATOM
	struct Desc* esdsAtom;
}EsdsAtom;

#endif
