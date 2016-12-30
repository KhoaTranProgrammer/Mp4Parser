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

#include "MOOVAtom.h"
//#include "TRAKAtom.h"
//#include "MDIAAtom.h"
//#include "HDLRAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	MoovAtom* myself;
	Atom* newAtom;
	uint remainBytes;
	uint tracktype;
	int i;

	myself = (MoovAtom*)me;
	CAL_DATASIZE(myself)

	while(myself->remainBytes > 0)
	{
		err = ParseAtom(&newAtom, fileReader);
		CHECK_ERROR(err);

		switch(newAtom->type)
		{
			case MVHD:
				myself->mvhdAtom = (MvhdAtom*)newAtom; break;
			case TRAK:
				tracktype = getTrackType(newAtom);
				if(tracktype == VIDE)
				{
					myself->videAtom = (TrakAtom*)newAtom;
				}
				else if(tracktype == SOUN)
				{
					myself->sounAtom = (TrakAtom*)newAtom;
				}
				break;
			case UDTA: myself->udtaAtom = newAtom; break;
			default:
				err = UnkownAtom; break;
		}
		myself->remainBytes -= newAtom->size;
	};

	return err;
}

static void destroy(Atom* me)
{
	MoovAtom* myself;
	myself = (MoovAtom*)me;

	FREE_BASEATOM(myself);
	if(myself->mvhdAtom) myself->mvhdAtom->destroy(myself->mvhdAtom);
	if(myself->udtaAtom) myself->udtaAtom->destroy(myself->udtaAtom);
	if(myself->videAtom) myself->videAtom->destroy(myself->videAtom);
	if(myself->sounAtom) myself->sounAtom->destroy(myself->sounAtom);
	free(myself);
}

ErrInfo CreateMoovAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	MoovAtom* myself;

	myself = (MoovAtom*) malloc(sizeof(MoovAtom));
	SET_BASEATOM(myself);
	myself->mvhdAtom = NULL;
	myself->udtaAtom = NULL;
	myself->videAtom = NULL;
	myself->sounAtom = NULL;
	*me = (Atom*)myself;
	return err;
}

//get the type of track: video or audio
int getTrackType(Atom* newAtom)
{
	TrakAtom* trakAtom;
	trakAtom = (TrakAtom*)newAtom;

	return CONVERT_CHAR2INT(
		trakAtom->mdiaAtom->hdlrAtom->componentSubtype[0],
		trakAtom->mdiaAtom->hdlrAtom->componentSubtype[1],
		trakAtom->mdiaAtom->hdlrAtom->componentSubtype[2],
		trakAtom->mdiaAtom->hdlrAtom->componentSubtype[3]
		);
}
