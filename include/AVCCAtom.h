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

/*
	An H.264 AVCConfigurationBox. This extension is required for H.264 video as defined in ISO/IEC 14496-15.
*/
#ifndef AVCCATOM_H
#define AVCCATOM_H
#include "Atom.h"

typedef struct _avccAtom
{
	BASE_ATOM
	uchar configurationVersion;
	uchar avcProfileIndication;
	uchar profileCompatibility;
	uchar avcLevelIndication;
	uchar reserved1; //6 bits
	uchar lengthSizeMinusOne;
	uchar reserved2; //3 bits
	//SequenceParameter
	uchar numOfSequenceParameterSets;
	ushort* sequenceParameterSetLength;
	uchar** sequenceParameterSetNALUnit;
	//PictureParameter
	uchar numOfPictureParameterSets;
	ushort* pictureParameterSetLength;
	uchar** pictureParameterSetNALUnit;
}AvccAtom;

#endif
