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

#include "STTSAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	SttsAtom* myself;
	int i;

	myself = (SttsAtom*)me;
	CAL_DATASIZE(myself)

	//read Version
	READ_BYTE(fileReader, myself, myself->version)

	//read Flags
	READ_BYTES(fileReader, myself, myself->flags, 3)

	//read Number Of Entries
	READ_4BYTES(fileReader, myself, myself->numberOfEntries)

	//read Time-to-sample table
	myself->sampleCount = (uint*) malloc(sizeof(uint) * myself->numberOfEntries);
	CHECK_MEM(myself->sampleCount);
	myself->sampleDuration = (uint*) malloc(sizeof(uint) * myself->numberOfEntries);
	CHECK_MEM(myself->sampleDuration);
	for( i = 0; i < myself->numberOfEntries; i++)
	{
		READ_4BYTES(fileReader, myself, myself->sampleCount[i])
		READ_4BYTES(fileReader, myself, myself->sampleDuration[i])
	}

	return err;
}

static void destroy(struct Atom* me)
{
	SttsAtom* myself;
	myself = (SttsAtom*)me;

	FREE_FULLATOM(myself)
	free(myself->sampleCount);
	free(myself->sampleDuration);
	free(myself);
}

ErrInfo CreateSttsAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	SttsAtom* myself;

	myself = (SttsAtom*) malloc(sizeof(SttsAtom));
	SET_BASEATOM(myself);
	*me = (Atom*)myself;
	return err;
}
