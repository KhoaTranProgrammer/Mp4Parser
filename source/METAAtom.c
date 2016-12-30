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

#include "METAAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	MetaAtom* myself;
	Atom* newAtom;

	myself = (MetaAtom*)me;
	CAL_DATASIZE(myself)

	//read Version
	READ_BYTE(fileReader, myself, myself->version)

	//read Flags
	READ_BYTES(fileReader, myself, myself->flags, 3)

	while(myself->remainBytes)
	{
		err = ParseAtom(&newAtom, fileReader);
		CHECK_ERROR(err);

		switch(newAtom->type)
		{
			case HDLR: myself->hdlrAtom = (HdlrAtom*)newAtom; break;
			default: err = UnkownAtom; break;
		};

		myself->remainBytes -= newAtom->size;

		if(myself->remainBytes > 0)
		{
			READ_BYTES(fileReader, myself, myself->data, myself->remainBytes)
		}
	};

	return err;
}

static void destroy(Atom* me)
{
	MetaAtom* myself;
	myself = (MetaAtom*)me;

	FREE_FULLATOM(myself)
	myself->hdlrAtom->destroy(myself->hdlrAtom);
	free(myself->data);
	free(myself);
}

ErrInfo CreateMetaAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	MetaAtom* myself;

	myself = (MetaAtom*) malloc(sizeof(MetaAtom));
	SET_BASEATOM(myself);
	*me = (Atom*)myself;
	return err;
}
