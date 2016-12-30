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

#include "stdio.h"
#include "MP4Movie.h"

int main(int argc, char *argv[])
{
	Mp4Movie* mp4Movie;
	struct Mp4Info mp4Info;
	CreateMp4Handle(&mp4Movie, argv[1]);
	ReadMp4Movie(mp4Movie);
	mp4Info = GetMp4Information(mp4Movie);

	//General Information
	printf("\n---General Information---");
	printf("\nFile size: %d bytes", mp4Info.size);
	printf("\nDuration: %d hour/%d minute/%d second/%d milisecond", mp4Info.duration.hour, mp4Info.duration.minute, mp4Info.duration.second, mp4Info.duration.millisecond);
	printf("\nBrand: %s", mp4Info.brand);

	//Video Information
	printf("\n\n---Video Information---");
	printf("\nVideo format: %s", mp4Info.videoFormat);
	printf("\nVideo codec: %s", mp4Info.videoCodec);
	printf("\nVideo resolution: w = %d, h = %d", mp4Info.width, mp4Info.height);
	printf("\nVideo frame rate: %d fps", mp4Info.frameRate);
	printf("\nVideo bitrate: %d kbps", mp4Info.videoBitrate);
	printf("\nVideo duration: %d hour/%d minute/%d second/%d milisecond", mp4Info.videoDuration.hour, mp4Info.videoDuration.minute, mp4Info.videoDuration.second, mp4Info.videoDuration.millisecond);

	//Audio Information
	printf("\n\n---Audio Information---");
	printf("\nAudio format: %s", mp4Info.audioFormat);
	printf("\nAudio bitrate: %d kbps", mp4Info.audioBitrate);
	printf("\nAudio sampling rate: %d Hz", mp4Info.audioSamplingRate);
	printf("\nAudio duration: %d hour/%d minute/%d second/%d milisecond\n", mp4Info.audioDuration.hour, mp4Info.audioDuration.minute, mp4Info.audioDuration.second, mp4Info.audioDuration.millisecond);

	ReleaseMp4Movie(mp4Movie);
	return 0;
}
