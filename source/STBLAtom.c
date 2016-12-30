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

#include "STBLAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	StblAtom* myself;
	Atom* newAtom;
	uint remainBytes;
	int i;

	myself = (StblAtom*)me;
	CAL_DATASIZE(myself)

	while(myself->remainBytes > 0)
	{
		err = ParseAtom(&newAtom, fileReader);
		CHECK_ERROR(err);

		switch(newAtom->type){
			case STSD:
				myself->stsdAtom = (StsdAtom*)newAtom; break;
			case STTS:
				myself->sttsAtom = (SttsAtom*)newAtom; break;
			case STSS:
				myself->stssAtom = (StssAtom*)newAtom; break;
			case STSC:
				myself->stscAtom = (StscAtom*)newAtom; break;
			case STSZ:
				myself->stszAtom = (StszAtom*)newAtom; break;
			case STCO:
				myself->stcoAtom = (StcoAtom*)newAtom; break;
			default:
				err = UnkownAtom; break;
		}
		myself->remainBytes -= newAtom->size;
	};

	return err;
}

static void destroy(Atom* me)
{
	StblAtom* myself;
	myself = (StblAtom*)me;
	
	FREE_BASEATOM(myself)
	if(myself->stcoAtom != NULL) myself->stcoAtom->destroy(myself->stcoAtom);
	if(myself->stscAtom != NULL) myself->stscAtom->destroy(myself->stscAtom);
	if(myself->stsdAtom != NULL) myself->stsdAtom->destroy(myself->stsdAtom);
	if(myself->stssAtom != NULL) myself->stssAtom->destroy(myself->stssAtom);
	if(myself->stszAtom != NULL) myself->stszAtom->destroy(myself->stszAtom);
	if(myself->sttsAtom != NULL) myself->sttsAtom->destroy(myself->sttsAtom);
	free(myself);
}

ErrInfo CreateStblAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	StblAtom* myself;

	myself = (StblAtom*) malloc(sizeof(StblAtom));
	SET_BASEATOM(myself);
	myself->stcoAtom = NULL;
	myself->stscAtom = NULL;
	myself->stsdAtom = NULL;
	myself->stssAtom = NULL;
	myself->stszAtom = NULL;
	myself->sttsAtom = NULL;
	*me = (Atom*)myself;
	return err;
}
