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

#include "DREFAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	DrefAtom* myself;
	Atom* newAtom;
	int i;

	myself = (DrefAtom*)me;
	CAL_DATASIZE(myself)

	//read Version
	READ_BYTE(fileReader, myself, myself->version)

	//read Flags
	READ_BYTES(fileReader, myself, myself->flags, 3)

	//read Number of entries
	READ_4BYTES(fileReader, myself, myself->numberOfEntries)

	//read Data references
	myself->dataReferences = (Atom**) malloc(sizeof(Atom*) * myself->numberOfEntries);
	CHECK_MEM(myself->dataReferences);
	i = 0;
	while(myself->remainBytes)
	{
		err = ParseAtom(&newAtom, fileReader);
		CHECK_ERROR(err);
		myself->dataReferences[i] = (UrlAtom*)newAtom;
		myself->remainBytes -= newAtom->size;
	};

	return err;
}

static void destroy(Atom* me)
{
	int i;
	DrefAtom* myself;
	myself = (DrefAtom*)me;

	for(i = 0; i < myself->numberOfEntries; i++)
	{
		myself->dataReferences[i]->destroy(myself->dataReferences[i]);
	}
	free(myself->dataReferences);
	free(myself);
}

ErrInfo CreateDrefAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	DrefAtom* myself;

	myself = (DrefAtom*) malloc(sizeof(DrefAtom));
	SET_BASEATOM(myself);
	*me = (Atom*)myself;
	return err;
}
