
This program is a part of "Study C Pointer Via Examples" course.
video training: https://www.youtube.com/watch?v=jTR2UmA1H_0

This example here just support to parse MP4 File with basic profile that can work for the CTS media stress tests of Android. For other kind of profiles, some modifications are needed for program working. This example is supported to build on Windows(Visual Studio) and Linux(makefile)
Media file: https://dl.google.com/dl/android/cts/android-cts-media-1.0.zip

Build and run on Windows
1. Install Visual Studio 2010 Express
2. Open Mp4Parser.sln by VS2010
3. Change movie input at: Mp4Parser Property -> Configuration Properties -> Debugging -> Command Arguments

Build and run on Linux
1. Opens terminal and changes your working directory to Mp4Parser package:
# cd ${work}/Mp4Parser
2. Run make
# make
3. Run Mp4Parser
# ./Mp4Parser input.mp4

Output will look like:
=============================================================
---General Information---
File size: 617216332 bytes
Duration: 0 hour/9 minute/56 second/434 milisecond
Brand: isom

---Video Information---
Video format: avc1
Video codec: avcC
Video resolution: w = 1920, h = 1080
Video frame rate: 255 fps
Video bitrate: 86355 kbps
Video duration: 0 hour/9 minute/56 second/434 milisecond

---Audio Information---
Audio format: mp4a
Audio bitrate: 1761 kbps
Audio sampling rate: 48000 Hz
Audio duration: 0 hour/9 minute/56 second/416 milisecond
=============================================================

