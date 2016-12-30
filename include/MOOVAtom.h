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
	Movie resource metadata about the movie (number and type of tracks, location of sample data, and so on). Describes where the movie data can be found and how to interpret it.
*/
#ifndef MOOVATOM_H
#define MOOVATOM_H
#include "Atom.h"
#include "MVHDAtom.h"
#include "TRAKAtom.h"
#include "UDTAAtom.h"

typedef struct _moovAtom
{
	BASE_ATOM
	MvhdAtom* mvhdAtom;	//Movie Header Atom
	UdtaAtom* udtaAtom;	//User Data Atom
	TrakAtom* videAtom;	//Video Track Atom
	TrakAtom* sounAtom;	//Audio Track Atom
}MoovAtom;

#endif
