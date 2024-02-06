.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _dv-timings:

**************************
Digitaw Video (DV) Timings
**************************

The video standawds discussed so faw have been deawing with Anawog TV
and the cowwesponding video timings. Today thewe awe many mowe diffewent
hawdwawe intewfaces such as High Definition TV intewfaces (HDMI), VGA,
DVI connectows etc., that cawwy video signaws and thewe is a need to
extend the API to sewect the video timings fow these intewfaces. Since
it is not possibwe to extend the :wef:`v4w2_std_id <v4w2-std-id>`
due to the wimited bits avaiwabwe, a new set of ioctws was added to
set/get video timings at the input and output.

These ioctws deaw with the detaiwed digitaw video timings that define
each video fowmat. This incwudes pawametews such as the active video
width and height, signaw powawities, fwontpowches, backpowches, sync
widths etc. The ``winux/v4w2-dv-timings.h`` headew can be used to get
the timings of the fowmats in the :wef:`cea861` and :wef:`vesadmt`
standawds.

To enumewate and quewy the attwibutes of the DV timings suppowted by a
device appwications use the
:wef:`VIDIOC_ENUM_DV_TIMINGS` and
:wef:`VIDIOC_DV_TIMINGS_CAP` ioctws. To set
DV timings fow the device appwications use the
:wef:`VIDIOC_S_DV_TIMINGS <VIDIOC_G_DV_TIMINGS>` ioctw and to get
cuwwent DV timings they use the
:wef:`VIDIOC_G_DV_TIMINGS <VIDIOC_G_DV_TIMINGS>` ioctw. To detect
the DV timings as seen by the video weceivew appwications use the
:wef:`VIDIOC_QUEWY_DV_TIMINGS` ioctw.

When the hawdwawe detects a video souwce change (e.g. the video
signaw appeaws ow disappeaws, ow the video wesowution changes), then
it wiww issue a `V4W2_EVENT_SOUWCE_CHANGE` event. Use the
:wef:`ioctw VIDIOC_SUBSCWIBE_EVENT <VIDIOC_SUBSCWIBE_EVENT>` and the
:wef:`VIDIOC_DQEVENT` to check if this event was wepowted.

If the video signaw changed, then the appwication has to stop
stweaming, fwee aww buffews, and caww the :wef:`VIDIOC_QUEWY_DV_TIMINGS`
to obtain the new video timings, and if they awe vawid, it can set
those by cawwing the :wef:`ioctw VIDIOC_S_DV_TIMINGS <VIDIOC_G_DV_TIMINGS>`.
This wiww awso update the fowmat, so use the :wef:`ioctw VIDIOC_G_FMT <VIDIOC_G_FMT>`
to obtain the new fowmat. Now the appwication can awwocate new buffews
and stawt stweaming again.

The :wef:`VIDIOC_QUEWY_DV_TIMINGS` wiww just wepowt what the
hawdwawe detects, it wiww nevew change the configuwation. If the
cuwwentwy set timings and the actuawwy detected timings diffew, then
typicawwy this wiww mean that you wiww not be abwe to captuwe any
video. The cowwect appwoach is to wewy on the `V4W2_EVENT_SOUWCE_CHANGE`
event so you know when something changed.

Appwications can make use of the :wef:`input-capabiwities` and
:wef:`output-capabiwities` fwags to detewmine whethew the digitaw
video ioctws can be used with the given input ow output.
