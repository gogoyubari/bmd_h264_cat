# bmd_h264_cat
Blackmagic Design H.264 Pro Recorder console utility

## drivers
Latest working driver is **Desktop Video 10.11.4 (media express 3.5.7)**, see  https://www.blackmagicdesign.com/support/download/ceb304a75100442e9e763d6b371690d0/Windows

## binaries
* http://research.m1stereo.tv/bmd_h264_cat/2021-05-17/bmd_h264_cat.exe.win32.7z
* http://research.m1stereo.tv/bmd_h264_cat/2021-05-17/bmd_h264_cat.exe.x64.7z 


## feature
* receiving MPEG-TS stream from Blackmagic Design H.264 Pro Recorder
* save to file
* send to stdout
* UDP multicast/unicast
* TCP stream saving

## usage
<pre>
Usage:
    bmd_h264_cat.exe &lt;args&gt; [- | filename]
Where args are:
    -ab &lt;INT&gt;          audio bitrate in kbs
    -vb &lt;INT&gt;          video bitrate in kbs
    -ar &lt;INT&gt;          audio samplerate
    -ac &lt;INT&gt;          audio channels
    -framerate &lt;STR&gt;   framerate, see list below
    -profile &lt;STR&gt;     h264 encoding profile to use, see list below
    -entropy &lt;STR&gt;     h264 encoding entropy to use, see list below
    -level &lt;STR&gt;       h264 encoding level to use, see list below
    -preset &lt;STR&gt;      hardware encoder preset name to use, see list in logs
    -src-x &lt;INT&gt;       source rectangle
    -src-y &lt;INT&gt;
    -src-width &lt;INT&gt;
    -src-height &lt;INT&gt;
    -dst-width &lt;INT&gt;   destination width
    -dst-height &lt;INT&gt;  destination height
    -savesegment &lt;STR&gt; save segmented files strftime format
    -cron &lt;STR&gt;        split CRON expressions
    -savefile          save files timestamped
    -udp-host &lt;STR&gt;    host where sent UDP packet
    -udp-port &lt;INT&gt;    port where sent UDP packet
    -udp-sndbuf &lt;INT&gt;  SO_SNDBUF of UDP socket
    -tcp-host &lt;STR&gt;    host where sent TCP packet
    -tcp-port &lt;INT&gt;    port where sent TCP packet
    -tcp-sndbuf &lt;INT&gt;  SO_SNDBUF of TCP socket
Framerates: [50i] [5994i] [60i] [2398p] [24p] [25p] [2997p] [30p] [50p] [5994p] [60p]
Entropyies: [CAVLC] [CABAC]
Levels: [12] [13] [2] [21] [22] [3] [31] [32] [4] [41] [42]
Profiles: [High] [Main] [Baseline]
</pre>

## examples

### sending UDP unicast stream
<pre>bmd_h264_cat.exe -savefile -preset "iPad / iPhone 4" -udp-host 10.1.5.65 -udp-port 40001</pre>

### sending UDP multicast stream
<pre>bmd_h264_cat.exe -savefile -preset "iPad / iPhone 4" -udp-host 224.1.1.1 -udp-port 40001</pre>

### sending TCP stream
<pre>bmd_h264_cat.exe -savefile -preset "iPad / iPhone 4" -tcp-host 10.1.5.57 -tcp-port 20001</pre>

it could be received by **socat** and transformed to multicast:
<pre>socat -b1316 TCP-LISTEN:20001,reuseaddr,fork UDP-DATAGRAM:224.1.1.1:30001,ttl=10</pre>

further step could be implemented with **udpxy**:
<pre>/usr/local/src/2015-11-15/udpxy-1.0.23-9/udpxy -p 10000</pre>

stream could be checked with VLC by networks links:
* udp://@224.1.1.1:30001
* http://10.1.5.57:10000/udp/224.1.1.1:30001/demo.ts

### rtmp publishing

<pre>
bmd_h264_cat.exe -savefile -preset "YouTube 720p" - | c:\ffmpeg\bin\ffmpeg_flv_aac_seq_header.exe -f mpegts -i - -acodec copy -vcodec copy -flvflags aac_seq_header_detect -bsf:a aac_adtstoasc -f flv rtmp://a.rtmp.youtube.com/live2/foo-bar-key
</pre>

please note, that in this case custom version of ffmpeg used, because of http://lists.ffmpeg.org/pipermail/ffmpeg-devel/2015-November/183483.html

if you have no this version or patch not applied then you have to re-encode audio only.

## -savefile
is argument that could save receivied stream into auto-timestamp-named file - that could helps to avoid loosing some files

## CRON expressions
A CRON expression is a string composed of six fields (in some implementation seven) separated by a whites space representing a time schedule. The general form is the following (with the years being optional):
<pre>
&lt;seconds&gt; &lt;minutes&gt; &lt;hours&gt; &lt;days of month&gt; &lt;months&gt; &lt;days of week&gt; &lt;years&gt;
</pre>
* https://github.com/mariusbancila/croncpp

## limitation
not all arguments are really working. API support it, but firmware does not. bitrate, preset, profile parameters works
