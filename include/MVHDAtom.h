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
	You use the movie header atom to specify the characteristics of an entire QuickTime movie. The data contained in this atom defines characteristics of the entire QuickTime movie, such as time scale and duration.
*/
#ifndef MVHDATOM_H
#define MVHDATOM_H
#include "Atom.h"

typedef struct _mvhdAtom
{
	FULL_ATOM
	uint creationTime;
	uint modificationTime;
	uint timeScale;
	uint duration;
	uint preferredRate;
	ushort preferredVolume;
	uchar* reserved;
	uint matrixStructure[9];
	uint previewTime;
	uint previewDuration;
	uint posterTime;
	uint selectionTime;
	uint selectionDuration;
	uint currentTime;
	uint nextTrackID;
}MvhdAtom;

#endif

