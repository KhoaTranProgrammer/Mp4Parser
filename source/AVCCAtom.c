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

#include "AVCCAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	AvccAtom* myself;
	Atom* newAtom;
	uchar temp;
	int i, j;

	myself = (AvccAtom*)me;
	CAL_DATASIZE(myself)

	//read configurationVersion
	READ_BYTE(fileReader, myself, myself->configurationVersion)

	//read avcProfileIndication
	READ_BYTE(fileReader, myself, myself->avcProfileIndication)

	//read profileCompatibility
	READ_BYTE(fileReader, myself, myself->profileCompatibility)

	//read avcLevelIndication
	READ_BYTE(fileReader, myself, myself->avcLevelIndication)

	//read reserved1 & lengthSizeMinusOne
	READ_BYTE(fileReader, myself, temp)
	myself->reserved1 = ( temp >> 2 ) & 0x3F;
	myself->lengthSizeMinusOne = temp & 0x03;

	//read reserved2 & numOfSequenceParameterSets
	READ_BYTE(fileReader, myself, temp)
	myself->reserved2 = (temp >> 5 ) & 0x07;
	myself->numOfSequenceParameterSets = temp & 0x1F;

	//read SequenceParameter
	myself->sequenceParameterSetLength = (ushort*)malloc(sizeof(ushort)* myself->numOfSequenceParameterSets);
	myself->sequenceParameterSetNALUnit = (uchar**) malloc(sizeof(ushort*) * myself->numOfSequenceParameterSets);
	for(i = 0; i < myself->numOfSequenceParameterSets; i++)
	{
		READ_2BYTES(fileReader, myself, myself->sequenceParameterSetLength[i])
		myself->sequenceParameterSetNALUnit[i] = (ushort*) malloc(sizeof(ushort) * myself->sequenceParameterSetLength[i]);
		for(j = 0; j < myself->sequenceParameterSetLength[i]; j++)
		{
			READ_BYTE(fileReader, myself, myself->sequenceParameterSetNALUnit[i][j])
		}
	}

	//read PictureParameter
	READ_BYTE(fileReader, myself, myself->numOfPictureParameterSets)
	myself->pictureParameterSetLength = (ushort*)malloc(sizeof(ushort)* myself->numOfPictureParameterSets);
	myself->pictureParameterSetNALUnit = (uchar**) malloc(sizeof(ushort*) * myself->numOfPictureParameterSets);
	for(i = 0; i < myself->numOfPictureParameterSets; i++)
	{
		READ_2BYTES(fileReader, myself, myself->pictureParameterSetLength[i])
		myself->pictureParameterSetNALUnit[i] = (ushort*) malloc(sizeof(ushort) * myself->pictureParameterSetLength[i]);
		for(j = 0; j < myself->pictureParameterSetLength[i]; j++)
		{
			READ_BYTE(fileReader, myself, myself->pictureParameterSetNALUnit[i][j])
		}
	}

	return err;
}

static void destroy(Atom* me)
{
	int i;
	AvccAtom* myself;
	myself = (AvccAtom*)me;

	FREE_BASEATOM(myself)
	
	//free SequenceParameter
	for(i = 0; i < myself->numOfSequenceParameterSets; i++)
	{
		free(myself->sequenceParameterSetNALUnit[i]);
	}
	free(myself->sequenceParameterSetNALUnit);
	free(myself->sequenceParameterSetLength);

	//free PictureParameter
	for(i = 0; i < myself->numOfPictureParameterSets; i++)
	{
		free(myself->pictureParameterSetNALUnit[i]);
	}
	free(myself->pictureParameterSetNALUnit);
	free(myself->pictureParameterSetLength);
	free(myself);
}

ErrInfo CreateAvccAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	AvccAtom* myself;

	myself = (AvccAtom*) malloc(sizeof(AvccAtom));
	SET_BASEATOM(myself);
	*me = (Atom*)myself;
	return err;
}
