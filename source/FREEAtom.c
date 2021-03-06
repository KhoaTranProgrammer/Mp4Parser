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

#include "FREEAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	FreeAtom* myself;
	Atom* newAtom;

	myself = (FreeAtom*)me;
	CAL_DATASIZE(myself)

	//read data
	myself->dataSize = myself->remainBytes;
	if(myself->dataSize > 0)
	{
		READ_BYTES(fileReader, myself, myself->data, myself->remainBytes)
	}

	return err;
}

static void destroy(Atom* me)
{

}

ErrInfo CreateFreeAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	FreeAtom* myself;

	myself = (FreeAtom*) malloc(sizeof(FreeAtom));
	SET_BASEATOM(myself);
	*me = (Atom*)myself;
	return err;
}
