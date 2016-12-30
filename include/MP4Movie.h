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

#ifndef MP4MOVIE_H
#define MP4MOVIE_H
#include "Atom.h"
#include "FileReader.h"
#include "FTYPAtom.h"
#include "MOOVAtom.h"
#include "MDATAtom.h"
#include "FREEAtom.h"
#include "AVC1Atom.h"

struct Duration
{
	int hour;
	int minute;
	int second;
	int millisecond;
};

struct Mp4Info
{
	//General Information
	uint size;
	struct Duration duration;
	char brand[5];

	//Video Information
	char videoFormat[5];
	char videoCodec[5];
	int width;
	int height;
	int frameRate;
	int videoBitrate;
	struct Duration videoDuration;

	//Audio Information
	char audioFormat[5];
	struct Duration audioDuration;
	int audioBitrate;
	int audioSamplingRate;
};

typedef struct _mp4Movie
{
	BASE_ATOM
	FileReader* fileReader;
	FtypAtom* ftypAtom;	//The File Type Compatibility Atom
	MoovAtom* moovAtom;	//Movie resource metadata about the movie
	MdatAtom* mdatAtom;	//Movie sample data
	FreeAtom* freeAtom;	//Unused space available in file
}Mp4Movie;

ErrInfo CreateMp4Handle(Mp4Movie** me, char* filename);
ErrInfo ReadMp4Movie(Mp4Movie* me);
struct Mp4Info GetMp4Information(Mp4Movie* me);
void ReleaseMp4Movie(Mp4Movie* me);

#endif
