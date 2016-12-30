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

#include "UDTAAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	UdtaAtom* myself;
	Atom* newAtom;

	myself = (UdtaAtom*)me;
	CAL_DATASIZE(myself)

	myself->numberOfData = 0;
	while(myself->remainBytes)
	{
		err = ParseAtom(&newAtom, fileReader);
		CHECK_ERROR(err);
		myself->userDataList[myself->numberOfData++] = (MetaAtom*)newAtom;
		myself->remainBytes -= newAtom->size;
	};

	return err;
}

static void destroy(Atom* me)
{
	int i;
	UdtaAtom* myself;
	myself = (UdtaAtom*)me;

	FREE_BASEATOM(myself)
	for(i = 0; i < myself->numberOfData; i++)
	{
		myself->userDataList[i]->destroy(myself->userDataList[i]);
	}
	free(myself);
}

ErrInfo CreateUdtaAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	UdtaAtom* myself;

	myself = (UdtaAtom*) malloc(sizeof(UdtaAtom));
	SET_BASEATOM(myself);
	*me = (Atom*)myself;
	return err;
}
