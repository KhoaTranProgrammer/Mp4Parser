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
	Data Information Atoms

The handler reference atom (described in Handler Reference Atoms) contains information specifying the data handler component that provides access to the media data. The data handler component uses the data information atom to interpret the media’s data. Data information atoms have an atom type value of 'dinf'.
*/
#ifndef DINFATOM_H
#define DINFATOM_H
#include "Atom.h"
#include "DREFAtom.h"

typedef struct _dinfAtom
{
	BASE_ATOM
	DrefAtom* drefAtom;	//Data reference atom
}DinfAtom;

#endif
