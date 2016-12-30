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

#include "MDIAAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	MdiaAtom* myself;
	Atom* newAtom;
	uint remainBytes;
	int i;

	myself = (MdiaAtom*)me;
	CAL_DATASIZE(myself)

	while(myself->remainBytes)
	{
		err = ParseAtom(&newAtom, fileReader);
		CHECK_ERROR(err);

		switch(newAtom->type){
			case MDHD:
				myself->mdhdAtom = (MdhdAtom*)newAtom; break;
			case HDLR:
				myself->hdlrAtom = (HdlrAtom*)newAtom; break;
			case MINF:
				myself->minfAtom = (MinfAtom*)newAtom; break;
			default:
				err = UnkownAtom; break;
		}
		myself->remainBytes -= newAtom->size;
	};

	return err;
}

static void destroy(Atom* me)
{
	MdiaAtom* myself;
	myself = (MdiaAtom*)me;

	FREE_BASEATOM(myself);
	if(myself->mdhdAtom != NULL) myself->mdhdAtom->destroy(myself->mdhdAtom);
	if(myself->hdlrAtom != NULL) myself->hdlrAtom->destroy(myself->hdlrAtom);
	if(myself->minfAtom != NULL) myself->minfAtom->destroy(myself->minfAtom);
	free(myself);
}

ErrInfo CreateMdiaAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	MdiaAtom* myself;

	myself = (MdiaAtom*) malloc(sizeof(MdiaAtom));
	SET_BASEATOM(myself);
	myself->mdhdAtom = NULL;
	myself->hdlrAtom = NULL;
	myself->minfAtom = NULL;
	*me = (Atom*)myself;
	return err;
}
