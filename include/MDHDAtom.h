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
	The media header atom specifies the characteristics of a media, including time scale and duration. The media header atom has an atom type of 'mdhd'. 
*/
#ifndef MDHDATOM_H
#define MDHDATOM_H
#include "Atom.h"

typedef struct _mdhdAtom
{
	FULL_ATOM
	uint creationTime;
	uint modificationTime;
	uint timeScale;
	uint duration;
	ushort language;
	ushort quality;
}MdhdAtom;

#endif
