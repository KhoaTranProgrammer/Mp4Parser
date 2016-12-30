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

#include "Atom.h"

ErrInfo ParseAtom(Atom** atom, FileReader* fileReader)
{
	ErrInfo err = NoError;
	uint size, type;
	
	//read the atom size first
	err = fileReader->read4Bytes(fileReader, &size);
	CHECK_ERROR(err);

	//read the atom type
	err = fileReader->read4Bytes(fileReader, &type);
	CHECK_ERROR(err);

	switch(type)
	{
		case FTYP:
			err = CreateFtypAtom(atom, size, type); break;
		case MOOV:
			err = CreateMoovAtom(atom, size, type); break;
		case MVHD:
			err = CreateMvhdAtom(atom, size, type); break;
		case TRAK:
			err = CreateTrakAtom(atom, size, type); break;
		case TKHD:
			err = CreateTkhdAtom(atom, size, type); break;
		case MDIA:
			err = CreateMdiaAtom(atom, size, type); break;
		case MDHD:
			err = CreateMdhdAtom(atom, size, type); break;
		case HDLR:
			err = CreateHdlrAtom(atom, size, type); break;
		case MINF:
			err = CreateMinfAtom(atom, size, type); break;
		case VMHD:
			err = CreateVmhdAtom(atom, size, type); break;
		case SMHD:
			err = CreateSmhdAtom(atom, size, type); break;
		case DINF:
			err = CreateDinfAtom(atom, size, type); break;
		case DREF:
			err = CreateDrefAtom(atom, size, type); break;
		case URL:
			err = CreateUrlAtom (atom, size, type); break;
		case STBL:
			err = CreateStblAtom(atom, size, type); break;
		case STSD:
			err = CreateStsdAtom(atom, size, type); break;
		case AVC1:
			err = CreateAvc1Atom(atom, size, type); break;
		case AVCC:
			err = CreateAvccAtom(atom, size, type); break;
		case STTS:
			err = CreateSttsAtom(atom, size, type); break;
		case STSS:
			err = CreateStssAtom(atom, size, type); break;
		case STSC:
			err = CreateStscAtom(atom, size, type); break;
		case STSZ:
			err = CreateStszAtom(atom, size, type); break;
		case STCO:
			err = CreateStcoAtom(atom, size, type); break;
		case MP4A:
			err = CreateMp4aAtom(atom, size, type); break;
		case ESDS:
			err = CreateEsdsAtom(atom, size, type); break;
		case UDTA:
			err = CreateUdtaAtom(atom, size, type); break;
		case META:
			err = CreateMetaAtom(atom, size, type); break;
		case FREE:
			err = CreateFreeAtom(atom, size, type); break;
		case MDAT:
			err = CreateMdatAtom(atom, size, type); break;
		default:
			err = UnkownAtom; break;
	}

	if(err == NoError)
	{
		err = (*atom)->createDataFromFile(*atom, fileReader);
	}

	return err;
}
