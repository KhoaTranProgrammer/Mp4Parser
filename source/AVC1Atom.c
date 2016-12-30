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

#include "AVC1Atom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	Avc1Atom* myself;
	Atom* newAtom;
	uint remainBytes;
	int i;
	short temp;
	uint i4;

	myself = (Avc1Atom*)me;
	CAL_DATASIZE(myself)

	//read six bytes Reserved
	READ_BYTES(fileReader, myself, myself->reserved, 6)

	//read Data reference index
	READ_2BYTES(fileReader, myself, myself->dataReferenceIndex)

	//read Reserved1
	READ_BYTES(fileReader, myself, myself->reserved1, 16)

	//read Reserved2
	READ_4BYTES(fileReader, myself, myself->reserved2)

	//read Reserved3
	READ_4BYTES(fileReader, myself, myself->reserved3)

	//read Reserved4
	READ_4BYTES(fileReader, myself, myself->reserved4)

	//read Reserved5
	READ_4BYTES(fileReader, myself, myself->reserved5)
	
	//read Reserved6
	READ_2BYTES(fileReader, myself, myself->reserved6)

	//read Reserved7
	READ_BYTES(fileReader, myself, myself->reserved7, 32)

	//read Reserved8
	READ_2BYTES(fileReader, myself, myself->reserved8)

	//read Reserved9
	READ_2BYTES(fileReader, myself, myself->reserved9)

	while(myself->remainBytes)
	{
		err = ParseAtom(&newAtom, fileReader);
		CHECK_ERROR(err);
		myself->videoSampleDescriptionExtensions = (AvccAtom*)newAtom;
		myself->remainBytes -= newAtom->size;
	};
	
	return err;
}

static void destroy(Atom* me)
{
	Avc1Atom* myself;
	myself = (Avc1Atom*)me;

	FREE_BASEATOM(myself)
	free(myself->reserved);
	free(myself->reserved1);
	free(myself->reserved7);
	if (myself->videoSampleDescriptionExtensions) myself->videoSampleDescriptionExtensions->destroy(myself->videoSampleDescriptionExtensions);
	free(myself);
}

ErrInfo CreateAvc1Atom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	Avc1Atom* myself;

	myself = (Avc1Atom*) malloc(sizeof(Avc1Atom));
	SET_BASEATOM(myself);
	myself->videoSampleDescriptionExtensions = NULL;
	*me = (Atom*)myself;
	return err;
}
