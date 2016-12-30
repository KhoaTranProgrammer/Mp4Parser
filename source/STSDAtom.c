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

#include "STSDAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	StsdAtom* myself;
	Atom* newAtom;
	uint remainBytes;
	int i;

	myself = (StsdAtom*)me;
	CAL_DATASIZE(myself)

	//read Version
	READ_BYTE(fileReader, myself, myself->version)

	//read Flags
	READ_BYTES(fileReader, myself, myself->flags, 3)

	//read Number of entries
	READ_4BYTES(fileReader, myself, myself->numberOfEntries)

	//read Data references
	myself->sampleDescriptionTable = (Atom**) malloc(sizeof(Atom*) * myself->numberOfEntries);
	CHECK_MEM(myself->sampleDescriptionTable);
	i = 0;
	while(myself->remainBytes > 0)
	{
		err = ParseAtom(&newAtom, fileReader);
		CHECK_ERROR(err);
		myself->sampleDescriptionTable[i] = newAtom;
		myself->remainBytes -= newAtom->size;
	};

	return err;
}

static void destroy(Atom* me)
{
	int i;
	StsdAtom* myself;
	myself = (StsdAtom*)me;
	for(i = 0; i < myself->numberOfEntries; i++)
	{
		myself->sampleDescriptionTable[i]->destroy(myself->sampleDescriptionTable[i]);
	}
	free(myself->sampleDescriptionTable);
	free(myself);
}

ErrInfo CreateStsdAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	StsdAtom* myself;

	myself = (StsdAtom*) malloc(sizeof(StsdAtom));
	SET_BASEATOM(myself);
	*me = (Atom*)myself;
	return err;
}
