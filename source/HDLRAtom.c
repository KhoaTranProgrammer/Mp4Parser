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

#include "HDLRAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	HdlrAtom* myself;

	myself = (HdlrAtom*)me;
	CAL_DATASIZE(myself)

	//read Version
	READ_BYTE(fileReader, myself, myself->version)

	//read Flags
	READ_BYTES(fileReader, myself, myself->flags, 3)

	//read Component Type
	READ_BYTES(fileReader, myself, myself->componentType, 4)

	//read Component Subtype
	READ_BYTES(fileReader, myself, myself->componentSubtype, 4)

	//read Component manufacturer
	READ_4BYTES(fileReader, myself, myself->componentManufacture)

	//read Component flags
	READ_4BYTES(fileReader, myself, myself->componentFlags)

	//read Component flags mask
	READ_4BYTES(fileReader, myself, myself->componentFlagsMask)

	//read Component name
	if(myself->remainBytes > 0)
	{
		myself->nameLength = myself->remainBytes;
		READ_BYTES(fileReader, myself, myself->componentName, myself->remainBytes)
		myself->remainBytes = 0;
	}

	return err;
}

static void destroy(Atom* me)
{
	HdlrAtom* myself;
	myself = (HdlrAtom*)me;

	FREE_FULLATOM(myself)
	free(myself->componentType);
	free(myself->componentSubtype);
	free(myself->componentName);
	free(myself);
}

ErrInfo CreateHdlrAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	HdlrAtom* myself;

	myself = (HdlrAtom*) malloc(sizeof(HdlrAtom));
	SET_BASEATOM(myself);
	*me = (Atom*)myself;
	return err;
}
