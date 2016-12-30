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

#include "MP4Movie.h"

ErrInfo CreateMp4Handle(Mp4Movie** me, char* filename)
{
	ErrInfo err = NoError;

	*me = (Mp4Movie*) malloc(sizeof(Mp4Movie));
	CHECK_MEM(me);

	CreateMp4FileReader(&(*me)->fileReader, filename);
	return err;
}

ErrInfo ReadMp4Movie(Mp4Movie* me)
{
	ErrInfo err = NoError;
	Atom* newAtom;

	me->size = 0;
	me->ftypAtom = NULL;
	me->moovAtom = NULL;
	me->freeAtom = NULL;
	me->mdatAtom = NULL;
	while(err != FileEOF)
	{
		err = ParseAtom(&newAtom, me->fileReader);
		CHECK_ERROR(err);

		switch(newAtom->type){
			case FTYP: me->ftypAtom = (FtypAtom*)newAtom; break;
			case MOOV: me->moovAtom = (MoovAtom*)newAtom; break;
			case FREE: me->freeAtom = (FreeAtom*)newAtom; break;
			case MDAT: me->mdatAtom = (MdatAtom*)newAtom; break;
			default: err = UnkownAtom; break;
		}
		me->size += newAtom->size;
	}

	return err;
}

struct Mp4Info GetMp4Information(Mp4Movie* me)
{
	struct Mp4Info mp4Info;
	uint duration;
	uint majorBrand;
	uint type;
	int i;
	uint64 total_bitrates;

	//get size
	mp4Info.size = me->size;

	//calculate duration
	duration = me->moovAtom->mvhdAtom->duration;
	mp4Info.duration.millisecond = duration % 1000;
	mp4Info.duration.second = duration / 1000;	//total second: hour*60*60 + minute*60 + second
	mp4Info.duration.hour = mp4Info.duration.second / 60 / 60;
	mp4Info.duration.second = mp4Info.duration.second - mp4Info.duration.hour * 60 * 60; //result of: minute*60 + second
	mp4Info.duration.minute = mp4Info.duration.second / 60;
	mp4Info.duration.second = mp4Info.duration.second - mp4Info.duration.minute * 60;

	//get brand
	majorBrand = me->ftypAtom->majorBrand;
	mp4Info.brand[0] = majorBrand >> 24;
	mp4Info.brand[1] = majorBrand >> 16;
	mp4Info.brand[2] = majorBrand >> 8;
	mp4Info.brand[3] = majorBrand;
	mp4Info.brand[4] = '\0';

	//process video track
	if (me->moovAtom->videAtom)
	{
		//duration
		duration = me->moovAtom->videAtom->tkhdAtom->duration;
		mp4Info.videoDuration.millisecond = duration % 1000;
		mp4Info.videoDuration.second = duration / 1000;	//total second: hour*60*60 + minute*60 + second
		mp4Info.videoDuration.hour   = mp4Info.videoDuration.second / 60 / 60;
		mp4Info.videoDuration.second = mp4Info.videoDuration.second - mp4Info.videoDuration.hour * 60 * 60; //result of: minute*60 + second
		mp4Info.videoDuration.minute = mp4Info.videoDuration.second / 60;
		mp4Info.videoDuration.second = mp4Info.videoDuration.second - mp4Info.videoDuration.minute * 60;

		//width, height
		mp4Info.width = me->moovAtom->videAtom->tkhdAtom->trackWidth;
		mp4Info.height = me->moovAtom->videAtom->tkhdAtom->trackHeight;

		//video format
		type = me->moovAtom->videAtom->mdiaAtom->minfAtom->stblAtom->stsdAtom->sampleDescriptionTable[0]->type;
		mp4Info.videoFormat[0] = type >> 24;
		mp4Info.videoFormat[1] = type >> 16;
		mp4Info.videoFormat[2] = type >> 8;
		mp4Info.videoFormat[3] = type;
		mp4Info.videoFormat[4] = '\0';
		
		//video codecs
		type = ((Avc1Atom*)(me->moovAtom->videAtom->mdiaAtom->minfAtom->stblAtom->stsdAtom->sampleDescriptionTable[0]))->videoSampleDescriptionExtensions->type;
		mp4Info.videoCodec[0] = type >> 24;
		mp4Info.videoCodec[1] = type >> 16;
		mp4Info.videoCodec[2] = type >> 8;
		mp4Info.videoCodec[3] = type;
		mp4Info.videoCodec[4] = '\0';
		
		//frameRate
		mp4Info.frameRate = me->moovAtom->videAtom->mdiaAtom->minfAtom->stblAtom->stszAtom->numberOfEntries / mp4Info.videoDuration.second;
		
		//videoBitrate
		total_bitrates = 0;
		for (i = 0; i < me->moovAtom->videAtom->mdiaAtom->minfAtom->stblAtom->stszAtom->numberOfEntries; i++)
		{
			total_bitrates += me->moovAtom->videAtom->mdiaAtom->minfAtom->stblAtom->stszAtom->sampleSizeTable[i];
		}
		mp4Info.videoBitrate = total_bitrates * 8 / mp4Info.videoDuration.second / 1000;
	}

	//process audio track
	if (me->moovAtom->sounAtom)
	{
		//duration
		duration = me->moovAtom->sounAtom->tkhdAtom->duration;
		mp4Info.audioDuration.millisecond = duration % 1000;
		mp4Info.audioDuration.second = duration / 1000;	//total second: hour*60*60 + minute*60 + second
		mp4Info.audioDuration.hour   = mp4Info.audioDuration.second / 60 / 60;
		mp4Info.audioDuration.second = mp4Info.audioDuration.second - mp4Info.audioDuration.hour * 60 * 60; //result of: minute*60 + second
		mp4Info.audioDuration.minute = mp4Info.audioDuration.second / 60;
		mp4Info.audioDuration.second = mp4Info.audioDuration.second - mp4Info.audioDuration.minute * 60;

		//audio format
		type = me->moovAtom->sounAtom->mdiaAtom->minfAtom->stblAtom->stsdAtom->sampleDescriptionTable[0]->type;
		mp4Info.audioFormat[0] = type >> 24;
		mp4Info.audioFormat[1] = type >> 16;
		mp4Info.audioFormat[2] = type >> 8;
		mp4Info.audioFormat[3] = type;
		mp4Info.audioFormat[4] = '\0';

		//sampling rate
		mp4Info.audioSamplingRate = me->moovAtom->sounAtom->mdiaAtom->mdhdAtom->timeScale;

		//audioBitrate
		total_bitrates = 0;
		for (i = 0; i < me->moovAtom->sounAtom->mdiaAtom->minfAtom->stblAtom->stszAtom->numberOfEntries; i++)
		{
			total_bitrates += me->moovAtom->sounAtom->mdiaAtom->minfAtom->stblAtom->stszAtom->sampleSizeTable[i];
		}
		mp4Info.audioBitrate = total_bitrates * 8 / mp4Info.audioDuration.second / 1000;
	}

	return mp4Info;
}

void ReleaseMp4Movie(Mp4Movie* me)
{
	FREE_BASEATOM(me)
	if(me->fileReader) me->fileReader->destroy(me->fileReader);
	if(me->ftypAtom) me->ftypAtom->destroy(me->ftypAtom);
	if(me->moovAtom) me->moovAtom->destroy(me->moovAtom);
	if(me->mdatAtom) me->mdatAtom->destroy(me->mdatAtom);
	if(me->freeAtom) me->freeAtom->destroy(me->freeAtom);
	free(me);
}
