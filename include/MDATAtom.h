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
	Movie sample data—media samples such as video frames and groups of audio samples. Usually this data can be interpreted only by using the movie resource.
*/
#ifndef MDATATOM_H
#define MDATATOM_H
#include "Atom.h"

typedef struct _mdatAtom
{
	BASE_ATOM
	uint dataSize;
	uchar* data;
}MdatAtom;

#endif
