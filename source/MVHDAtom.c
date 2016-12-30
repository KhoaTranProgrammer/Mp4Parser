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

#include "MVHDAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	MvhdAtom* myself;
	int i;

	myself = (MvhdAtom*)me;
	CAL_DATASIZE(myself)

	//read Version
	READ_BYTE(fileReader, myself, myself->version)

	//read Flags
	READ_BYTES(fileReader, myself, myself->flags, 3)

	//read Creation Time
	READ_4BYTES(fileReader, myself, myself->creationTime)

	//read Modification Time
	READ_4BYTES(fileReader, myself, myself->modificationTime)

	//read TimeScale
	READ_4BYTES(fileReader, myself, myself->timeScale)

	//read Duration
	READ_4BYTES(fileReader, myself, myself->duration)

	//read Preferred Rate
	READ_4BYTES(fileReader, myself, myself->preferredRate)
	
	//read Preferred Volumn
	READ_2BYTES(fileReader, myself, myself->preferredVolume)

	//read Reserved
	READ_BYTES(fileReader, myself, myself->reserved, 10)

	//read Matrix Structure
	for(i = 0; i < 9; i++)
	{
		READ_4BYTES(fileReader, myself, myself->matrixStructure[i])
	}

	//read Preview Time
	READ_4BYTES(fileReader, myself, myself->previewTime)

	//read Preview Duration
	READ_4BYTES(fileReader, myself, myself->previewDuration)

	//read Poster Time
	READ_4BYTES(fileReader, myself, myself->posterTime)

	//read Selection Time
	READ_4BYTES(fileReader, myself, myself->selectionTime)

	//read Selection Duration
	READ_4BYTES(fileReader, myself, myself->selectionDuration)

	//read Current Time
	READ_4BYTES(fileReader, myself, myself->currentTime)

	//read Next Track ID
	READ_4BYTES(fileReader, myself, myself->nextTrackID)

	return err;
}

static void destroy(Atom* me)
{
	MvhdAtom* myself;
	myself = (MvhdAtom*)me;

	FREE_FULLATOM(myself);
	free(myself->reserved);
	free(myself);
}

ErrInfo CreateMvhdAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	MvhdAtom* myself;

	myself = (MvhdAtom*) malloc(sizeof(MvhdAtom));
	SET_BASEATOM(myself);
	*me = (Atom*)myself;
	return err;
}
