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

#include "STSCAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	StscAtom* myself;
	uint remainBytes;
	int i;

	myself = (StscAtom*)me;
	CAL_DATASIZE(myself)

	//read Version
	READ_BYTE(fileReader, myself, myself->version)

	//read Flags
	READ_BYTES(fileReader, myself, myself->flags, 3)

	//read Number Of Entries
	READ_4BYTES(fileReader, myself, myself->numberOfEntries)

	//read Sample-to-chunk table
	myself->firstChunk = (uint*) malloc(sizeof(uint) * myself->numberOfEntries);
	myself->samplesPerChunk = (uint*) malloc(sizeof(uint) * myself->numberOfEntries);
	myself->sampleDescriptionID = (uint*) malloc(sizeof(uint) * myself->numberOfEntries);
	for(i = 0; i < myself->numberOfEntries; i++)
	{
		READ_4BYTES(fileReader, myself, myself->firstChunk[i])
		READ_4BYTES(fileReader, myself, myself->samplesPerChunk[i])
		READ_4BYTES(fileReader, myself, myself->sampleDescriptionID[i])
	}

	return err;
}

static void destroy(Atom* me)
{
	StscAtom* myself;
	myself = (StscAtom*)me;

	FREE_FULLATOM(myself)
	free(myself->firstChunk);
	free(myself->samplesPerChunk);
	free(myself->sampleDescriptionID);
	free(myself);
}

ErrInfo CreateStscAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	StscAtom* stscAtom;

	stscAtom = (StscAtom*) malloc(sizeof(StscAtom));
	SET_BASEATOM(stscAtom);
	*me = (Atom*)stscAtom;
	return err;
}
