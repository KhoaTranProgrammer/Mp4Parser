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
	User Data Atoms

The user data atom has an atom type of 'udta'. Inside the user data atom is a list of atoms describing each piece of user data. User data provides a simple way to extend the information stored in a QuickTime movie. For example, user data atoms can store a movie’s window position, playback characteristics, or creation information. 
*/
#ifndef UDTAATOM_H
#define UDTAATOM_H
#include "Atom.h"
#include "METAAtom.h"

typedef struct _udtaAtom
{
	BASE_ATOM
	int numberOfData;
	MetaAtom* userDataList[10];
}UdtaAtom;

#endif
