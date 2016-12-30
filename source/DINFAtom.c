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

#include "DINFAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	DinfAtom* myself;
	Atom* newAtom;
	uint remainBytes;

	myself = (DinfAtom*)me;
	CAL_DATASIZE(myself)

	while(myself->remainBytes > 0)
	{
		err = ParseAtom(&newAtom, fileReader);
		CHECK_ERROR(err);

		switch(newAtom->type){
			case DREF:
				myself->drefAtom = (DrefAtom*)newAtom; break;
			default:
				err = UnkownAtom; break;
		}
		myself->remainBytes -= newAtom->size;
	};

	return err;
}

static void destroy(Atom* me)
{
	DinfAtom* myself;
	myself = (DinfAtom*)me;
	
	FREE_BASEATOM(myself)
	if(myself->drefAtom != NULL) myself->drefAtom->destroy(myself->drefAtom);
	free(myself);
}

ErrInfo CreateDinfAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	DinfAtom* myself;

	myself = (DinfAtom*) malloc(sizeof(DinfAtom));
	SET_BASEATOM(myself);
	myself->drefAtom = NULL;
	*me = (Atom*)myself;
	return err;
}
