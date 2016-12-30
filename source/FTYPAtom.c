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

#include "FTYPAtom.h"

static ErrInfo createDataFromFile(Atom* me, FileReader* fileReader)
{
	ErrInfo err = NoError;
	FtypAtom* myself;
	int i;

	myself = (FtypAtom*)me;
	CAL_DATASIZE(myself)

	//read Major_Brand
	READ_4BYTES(fileReader, myself, myself->majorBrand)

	//read Minor_Version
	READ_4BYTES(fileReader, myself, myself->minorVersion)

	//read Compatible_Brands
	myself->cbItem = myself->remainBytes / 4;
	myself->compatibleBrands = (uint*)malloc(myself->cbItem * sizeof(int));
	for(i = 0; i < myself->cbItem; i++)
	{
		READ_4BYTES(fileReader, myself, myself->compatibleBrands[i])
	}

	return err;
}

static void destroy(Atom* me)
{
	FtypAtom* myself;
	myself = (FtypAtom*)me;

	FREE_BASEATOM(myself);
	free(myself->compatibleBrands);
	free(myself);
}

ErrInfo CreateFtypAtom(Atom** me, uint size, uint type)
{
	ErrInfo err = NoError;
	FtypAtom* myself;

	myself = (FtypAtom*) malloc(sizeof(FtypAtom));
	SET_BASEATOM(myself);
	*me = (Atom*)myself;
	return err;
}
