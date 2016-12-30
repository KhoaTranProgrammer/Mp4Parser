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

#include "MP4AAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	Mp4aAtom* myself;
	Atom* newAtom;
	
	myself = (Mp4aAtom*)me;
	CAL_DATASIZE(myself)

	//read six bytes Reserved
	READ_BYTES(fileReader, myself, myself->reserved, 6)

	//read Data reference index
	READ_2BYTES(fileReader, myself, myself->dataReferenceIndex)

	//read reserved1
	READ_4BYTES(fileReader, myself, myself->reserved1[0])
	READ_4BYTES(fileReader, myself, myself->reserved1[1])

	//read reserved2
	READ_2BYTES(fileReader, myself, myself->reserved2)

	//read reserved3
	READ_2BYTES(fileReader, myself, myself->reserved3)

	//read reserved4
	READ_4BYTES(fileReader, myself, myself->reserved4)

	//read timeScale
	READ_2BYTES(fileReader, myself, myself->timeScale)

	//read reserved5
	READ_2BYTES(fileReader, myself, myself->reserved5)

	while(myself->remainBytes > 0)
	{
		err = ParseAtom(&newAtom, fileReader);
		CHECK_ERROR(err);
		myself->soundSampleDescriptionExtensions = newAtom;
		myself->remainBytes -= newAtom->size;
	};

	return err;
}

static void destroy(Atom* me)
{
	Mp4aAtom* myself;
	myself = (Mp4aAtom*)me;

	FREE_BASEATOM(myself)
	free(myself->reserved);
	myself->soundSampleDescriptionExtensions->destroy(myself->soundSampleDescriptionExtensions);
	free(myself);
}

ErrInfo CreateMp4aAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	Mp4aAtom* myself;

	myself = (Mp4aAtom*) malloc(sizeof(Mp4aAtom));
	SET_BASEATOM(myself);
	*me = (Atom*)myself;
	return err;
}
