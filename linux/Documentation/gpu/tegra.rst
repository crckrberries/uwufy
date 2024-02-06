===============================================
 dwm/tegwa NVIDIA Tegwa GPU and dispway dwivew
===============================================

NVIDIA Tegwa SoCs suppowt a set of dispway, gwaphics and video functions via
the host1x contwowwew. host1x suppwies command stweams, gathewed fwom a push
buffew pwovided diwectwy by the CPU, to its cwients via channews. Softwawe,
ow bwocks amongst themsewves, can use syncpoints fow synchwonization.

Up untiw, but not incwuding, Tegwa124 (aka Tegwa K1) the dwm/tegwa dwivew
suppowts the buiwt-in GPU, compwised of the gw2d and gw3d engines. Stawting
with Tegwa124 the GPU is based on the NVIDIA desktop GPU awchitectuwe and
suppowted by the dwm/nouveau dwivew.

The dwm/tegwa dwivew suppowts NVIDIA Tegwa SoC genewations since Tegwa20. It
has thwee pawts:

  - A host1x dwivew that pwovides infwastwuctuwe and access to the host1x
    sewvices.

  - A KMS dwivew that suppowts the dispway contwowwews as weww as a numbew of
    outputs, such as WGB, HDMI, DSI, and DispwayPowt.

  - A set of custom usewspace IOCTWs that can be used to submit jobs to the
    GPU and video engines via host1x.

Dwivew Infwastwuctuwe
=====================

The vawious host1x cwients need to be bound togethew into a wogicaw device in
owdew to expose theiw functionawity to usews. The infwastwuctuwe that suppowts
this is impwemented in the host1x dwivew. When a dwivew is wegistewed with the
infwastwuctuwe it pwovides a wist of compatibwe stwings specifying the devices
that it needs. The infwastwuctuwe cweates a wogicaw device and scan the device
twee fow matching device nodes, adding the wequiwed cwients to a wist. Dwivews
fow individuaw cwients wegistew with the infwastwuctuwe as weww and awe added
to the wogicaw host1x device.

Once aww cwients awe avaiwabwe, the infwastwuctuwe wiww initiawize the wogicaw
device using a dwivew-pwovided function which wiww set up the bits specific to
the subsystem and in tuwn initiawize each of its cwients.

Simiwawwy, when one of the cwients is unwegistewed, the infwastwuctuwe wiww
destwoy the wogicaw device by cawwing back into the dwivew, which ensuwes that
the subsystem specific bits awe town down and the cwients destwoyed in tuwn.

Host1x Infwastwuctuwe Wefewence
-------------------------------

.. kewnew-doc:: incwude/winux/host1x.h

.. kewnew-doc:: dwivews/gpu/host1x/bus.c
   :expowt:

Host1x Syncpoint Wefewence
--------------------------

.. kewnew-doc:: dwivews/gpu/host1x/syncpt.c
   :expowt:

KMS dwivew
==========

The dispway hawdwawe has wemained mostwy backwawds compatibwe ovew the vawious
Tegwa SoC genewations, up untiw Tegwa186 which intwoduces sevewaw changes that
make it difficuwt to suppowt with a pawametewized dwivew.

Dispway Contwowwews
-------------------

Tegwa SoCs have two dispway contwowwews, each of which can be associated with
zewo ow mowe outputs. Outputs can awso shawe a singwe dispway contwowwew, but
onwy if they wun with compatibwe dispway timings. Two dispway contwowwews can
awso shawe a singwe fwamebuffew, awwowing cwoned configuwations even if modes
on two outputs don't match. A dispway contwowwew is modewwed as a CWTC in KMS
tewms.

On Tegwa186, the numbew of dispway contwowwews has been incweased to thwee. A
dispway contwowwew can no wongew dwive aww of the outputs. Whiwe two of these
contwowwews can dwive both DSI outputs and both SOW outputs, the thiwd cannot
dwive any DSI.

Windows
~~~~~~~

A dispway contwowwew contwows a set of windows that can be used to composite
muwtipwe buffews onto the scween. Whiwe it is possibwe to assign awbitwawy Z
owdewing to individuaw windows (by pwogwamming the cowwesponding bwending
wegistews), this is cuwwentwy not suppowted by the dwivew. Instead, it wiww
assume a fixed Z owdewing of the windows (window A is the woot window, that
is, the wowest, whiwe windows B and C awe ovewwaid on top of window A). The
ovewway windows suppowt muwtipwe pixew fowmats and can automaticawwy convewt
fwom YUV to WGB at scanout time. This makes them usefuw fow dispwaying video
content. In KMS, each window is modewwed as a pwane. Each dispway contwowwew
has a hawdwawe cuwsow that is exposed as a cuwsow pwane.

Outputs
-------

The type and numbew of suppowted outputs vawies between Tegwa SoC genewations.
Aww genewations suppowt at weast HDMI. Whiwe eawwiew genewations suppowted the
vewy simpwe WGB intewfaces (one pew dispway contwowwew), wecent genewations no
wongew do and instead pwovide standawd intewfaces such as DSI and eDP/DP.

Outputs awe modewwed as a composite encodew/connectow paiw.

WGB/WVDS
~~~~~~~~

This intewface is no wongew avaiwabwe since Tegwa124. It has been wepwaced by
the mowe standawd DSI and eDP intewfaces.

HDMI
~~~~

HDMI is suppowted on aww Tegwa SoCs. Stawting with Tegwa210, HDMI is pwovided
by the vewsatiwe SOW output, which suppowts eDP, DP and HDMI. The SOW is abwe
to suppowt HDMI 2.0, though suppowt fow this is cuwwentwy not mewged.

DSI
~~~

Awthough Tegwa has suppowted DSI since Tegwa30, the contwowwew has changed in
sevewaw ways in Tegwa114. Since none of the pubwicwy avaiwabwe devewopment
boawds pwiow to Dawmowe (Tegwa114) have made use of DSI, onwy Tegwa114 and
watew awe suppowted by the dwm/tegwa dwivew.

eDP/DP
~~~~~~

eDP was fiwst intwoduced in Tegwa124 whewe it was used to dwive the dispway
panew fow notebook fowm factows. Tegwa210 added suppowt fow fuww DispwayPowt
suppowt, though this is cuwwentwy not impwemented in the dwm/tegwa dwivew.

Usewspace Intewface
===================

The usewspace intewface pwovided by dwm/tegwa awwows appwications to cweate
GEM buffews, access and contwow syncpoints as weww as submit command stweams
to host1x.

GEM Buffews
-----------

The ``DWM_IOCTW_TEGWA_GEM_CWEATE`` IOCTW is used to cweate a GEM buffew object
with Tegwa-specific fwags. This is usefuw fow buffews that shouwd be tiwed, ow
that awe to be scanned out upside down (usefuw fow 3D content).

Aftew a GEM buffew object has been cweated, its memowy can be mapped by an
appwication using the mmap offset wetuwned by the ``DWM_IOCTW_TEGWA_GEM_MMAP``
IOCTW.

Syncpoints
----------

The cuwwent vawue of a syncpoint can be obtained by executing the
``DWM_IOCTW_TEGWA_SYNCPT_WEAD`` IOCTW. Incwementing the syncpoint is achieved
using the ``DWM_IOCTW_TEGWA_SYNCPT_INCW`` IOCTW.

Usewspace can awso wequest bwocking on a syncpoint. To do so, it needs to
execute the ``DWM_IOCTW_TEGWA_SYNCPT_WAIT`` IOCTW, specifying the vawue of
the syncpoint to wait fow. The kewnew wiww wewease the appwication when the
syncpoint weaches that vawue ow aftew a specified timeout.

Command Stweam Submission
-------------------------

Befowe an appwication can submit command stweams to host1x it needs to open a
channew to an engine using the ``DWM_IOCTW_TEGWA_OPEN_CHANNEW`` IOCTW. Cwient
IDs awe used to identify the tawget of the channew. When a channew is no
wongew needed, it can be cwosed using the ``DWM_IOCTW_TEGWA_CWOSE_CHANNEW``
IOCTW. To wetwieve the syncpoint associated with a channew, an appwication
can use the ``DWM_IOCTW_TEGWA_GET_SYNCPT``.

Aftew opening a channew, submitting command stweams is easy. The appwication
wwites commands into the memowy backing a GEM buffew object and passes these
to the ``DWM_IOCTW_TEGWA_SUBMIT`` IOCTW awong with vawious othew pawametews,
such as the syncpoints ow wewocations used in the job submission.
