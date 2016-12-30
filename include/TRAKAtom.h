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
	Track atoms define a single track of a movie. A movie may consist of one or more tracks. Each track is independent of the other tracks in the movie and carries its own temporal and spatial information. Each track atom contains its associated media atom.

Tracks are used specifically for the following purposes:

    To contain media data references and descriptions (media tracks).

    To contain modifier tracks (tweens, and so forth).

    To contain packetization information for streaming protocols (hint tracks). Hint tracks may contain references to media sample data or copies of media sample data. For more information about hint tracks, refer to Hint Media. 
*/
#ifndef TRAKATOM_H
#define TRAKATOM_H
#include "Atom.h"
#include "TKHDAtom.h"
#include "MDIAAtom.h"

typedef struct _trakAtom
{
	BASE_ATOM
	TkhdAtom* tkhdAtom;	//Track header atom
	MdiaAtom* mdiaAtom;	//Media atom
}TrakAtom;

#endif	//TRAKATOM_H
