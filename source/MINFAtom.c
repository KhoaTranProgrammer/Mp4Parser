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

#include "MINFAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	MinfAtom* myself;
	Atom* newAtom;

	myself = (MinfAtom*)me;
	CAL_DATASIZE(myself)

	while(myself->remainBytes)
	{
		err = ParseAtom(&newAtom, fileReader);
		CHECK_ERROR(err);

		switch(newAtom->type){
			case VMHD:
				myself->vmhdAtom = (VmhdAtom*)newAtom; break;
			case SMHD:
				myself->smhdAtom = (SmhdAtom*)newAtom; break;
			case DINF:
				myself->dinfAtom = (DinfAtom*)newAtom; break;
			case STBL:
				myself->stblAtom = (StblAtom*)newAtom; break;
			default:
				err = UnkownAtom; break;
		}
		myself->remainBytes -= newAtom->size;
	};

	return err;
}

static void destroy(Atom* me)
{
	MinfAtom* myself;
	myself = (MinfAtom*)me;

	FREE_BASEATOM(myself);
	if(myself->smhdAtom) myself->smhdAtom->destroy(myself->smhdAtom);
	if(myself->vmhdAtom) myself->vmhdAtom->destroy(myself->vmhdAtom);
	if(myself->dinfAtom) myself->dinfAtom->destroy(myself->dinfAtom);
	if(myself->stblAtom) myself->stblAtom->destroy(myself->stblAtom);
	free(myself);
}

ErrInfo CreateMinfAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	MinfAtom* myself;

	myself = (MinfAtom*) malloc(sizeof(MinfAtom));
	SET_BASEATOM(myself);
	myself->smhdAtom = NULL;
	myself->vmhdAtom = NULL;
	myself->dinfAtom = NULL;
	myself->stblAtom = NULL;
	*me = (Atom*)myself;
	return err;
}
