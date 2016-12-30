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
	Sound Media Information Header Atoms

The sound media information header atom stores the sound media’s control information, such as balance.
*/
#ifndef SMHDATOM_H
#define SMHDATOM_H
#include "Atom.h"

typedef struct _smhdAtom
{
	FULL_ATOM
	ushort balance;
	ushort reserved;
}SmhdAtom;

#endif
