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
	File type compatibility—identifies the file type and differentiates it from similar file types, such as MPEG-4 files and JPEG-2000 files.
*/

#ifndef FTYPATOM_H
#define FTYPATOM_H
#include "Atom.h"

typedef struct _ftypAtom
{
	BASE_ATOM
	uint majorBrand;
	uint minorVersion;
	uint cbItem;		//number of items in the list of compatible brands
	uint *compatibleBrands;
}FtypAtom;

#endif
