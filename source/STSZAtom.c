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

#include "STSZAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	StszAtom* myself;
	int i;

	myself = (StszAtom*)me;
	CAL_DATASIZE(myself)

	//read Version
	READ_BYTE(fileReader, myself, myself->version)

	//read Flags
	READ_BYTES(fileReader, myself, myself->flags, 3)

	//read Sample Size
	READ_4BYTES(fileReader, myself, myself->sampleSize)

	//read Number Of Entries
	READ_4BYTES(fileReader, myself, myself->numberOfEntries)

	//read Sample size table
	myself->sampleSizeTable = (uint*) malloc(sizeof(uint) * myself->numberOfEntries);
	for(i = 0; i < myself->numberOfEntries; i++)
	{
		READ_4BYTES(fileReader, myself, myself->sampleSizeTable[i])
	}

	return err;
}

static void destroy(Atom* me)
{
	StszAtom* myself;
	myself = (StszAtom*)me;

	FREE_FULLATOM(myself)
	free(myself->sampleSizeTable);
	free(myself);
}

ErrInfo CreateStszAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	StszAtom* myself;

	myself = (StszAtom*) malloc(sizeof(StszAtom));
	SET_BASEATOM(myself);
	*me = (Atom*)myself;
	return err;
}
