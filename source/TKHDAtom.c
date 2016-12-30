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

#include "TKHDAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	TkhdAtom* myself;
	int i;

	myself = (TkhdAtom*)me;
	CAL_DATASIZE(myself)

	//read Version
	READ_BYTE(fileReader, myself, myself->version)

	//read Flags
	READ_BYTES(fileReader, myself, myself->flags, 3)

	//read Creation Time
	READ_4BYTES(fileReader, myself, myself->creationTime)

	//read Modification Time
	READ_4BYTES(fileReader, myself, myself->modificationTime)

	//read Track ID
	READ_4BYTES(fileReader, myself, myself->trackID)

	//read Reserved1
	READ_BYTES(fileReader, myself, myself->reserved1, 4)

	//read Duration
	READ_4BYTES(fileReader, myself, myself->duration)

	//read Reserved2
	READ_BYTES(fileReader, myself, myself->reserved2, 8)

	////read Layer
	READ_2BYTES(fileReader, myself, myself->layer)

	//read Alternate Group
	READ_2BYTES(fileReader, myself, myself->alternateGroup)

	//read Volume
	READ_2BYTES(fileReader, myself, myself->volume)

	//read Reserved3
	READ_BYTES(fileReader, myself, myself->reserved3, 2)

	//read Matrix Structure
	for(i = 0; i < 9; i++)
	{
		READ_4BYTES(fileReader, myself, myself->matrixStructure[i])
	}

	//read Track Width
	READ_4BYTES(fileReader, myself, myself->trackWidth)
	myself->trackWidth >>= 16;	//Only get the integer part

	//read Track Height
	READ_4BYTES(fileReader, myself, myself->trackHeight)
	myself->trackHeight >>= 16;	//Only get the integer part

	return err;
}

static void destroy(Atom* me)
{
	TkhdAtom* myself;
	myself = (TkhdAtom*)me;

	FREE_FULLATOM(myself)
	free(myself->reserved1);
	free(myself->reserved2);
	free(myself->reserved3);
	free(myself);
}

ErrInfo CreateTkhdAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	TkhdAtom* myself;

	myself = (TkhdAtom*) malloc(sizeof(TkhdAtom));
	SET_BASEATOM(myself);
	*me = (Atom*)myself;
	return err;
}
