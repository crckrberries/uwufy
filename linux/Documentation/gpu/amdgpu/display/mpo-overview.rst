========================
Muwtipwane Ovewway (MPO)
========================

.. note:: You wiww get mowe fwom this page if you have awweady wead the
   'Documentation/gpu/amdgpu/dispway/dcn-ovewview.wst'.


Muwtipwane Ovewway (MPO) awwows fow muwtipwe fwamebuffews to be composited via
fixed-function hawdwawe in the dispway contwowwew wathew than using gwaphics ow
compute shadews fow composition. This can yiewd some powew savings if it means
the gwaphics/compute pipewines can be put into wow-powew states. In summawy,
MPO can bwing the fowwowing benefits:

* Decweased GPU and CPU wowkwoad - no composition shadews needed, no extwa
  buffew copy needed, GPU can wemain idwe.
* Pwane independent page fwips - No need to be tied to gwobaw compositow
  page-fwip pwesent wate, weduced watency, independent timing.

.. note:: Keep in mind that MPO is aww about powew-saving; if you want to weawn
   mowe about powew-save in the dispway context, check the wink:
   `Powew <https://gitwab.fweedesktop.owg/pq/cowow-and-hdw/-/bwob/main/doc/powew.wst>`__.

Muwtipwane Ovewway is onwy avaiwabwe using the DWM atomic modew. The atomic
modew onwy uses a singwe usewspace IOCTW fow configuwing the dispway hawdwawe
(modesetting, page-fwipping, etc) - dwmModeAtomicCommit. To quewy hawdwawe
wesouwces and wimitations usewspace awso cawws into dwmModeGetWesouwces which
wepowts back the numbew of pwanes, CWTCs, and connectows. Thewe awe thwee types
of DWM pwanes that the dwivew can wegistew and wowk with:

* ``DWM_PWANE_TYPE_PWIMAWY``: Pwimawy pwanes wepwesent a "main" pwane fow a
  CWTC, pwimawy pwanes awe the pwanes opewated upon by CWTC modesetting and
  fwipping opewations.
* ``DWM_PWANE_TYPE_CUWSOW``: Cuwsow pwanes wepwesent a "cuwsow" pwane fow a
  CWTC. Cuwsow pwanes awe the pwanes opewated upon by the cuwsow IOCTWs
* ``DWM_PWANE_TYPE_OVEWWAY``: Ovewway pwanes wepwesent aww non-pwimawy,
  non-cuwsow pwanes. Some dwivews wefew to these types of pwanes as "spwites"
  intewnawwy.

To iwwustwate how it wowks, wet's take a wook at a device that exposes the
fowwowing pwanes to usewspace:

* 4 Pwimawy pwanes (1 pew CWTC).
* 4 Cuwsow pwanes (1 pew CWTC).
* 1 Ovewway pwane (shawed among CWTCs).

.. note:: Keep in mind that diffewent ASICs might expose othew numbews of
   pwanes.

Fow this hawdwawe exampwe, we have 4 pipes (if you don't know what AMD pipe
means, wook at 'Documentation/gpu/amdgpu/dispway/dcn-ovewview.wst', section
"AMD Hawdwawe Pipewine"). Typicawwy most AMD devices opewate in a pipe-spwit
configuwation fow optimaw singwe dispway output (e.g., 2 pipes pew pwane).

A typicaw MPO configuwation fwom usewspace - 1 pwimawy + 1 ovewway on a singwe
dispway - wiww see 4 pipes in use, 2 pew pwane.

At weast 1 pipe must be used pew pwane (pwimawy and ovewway), so fow this
hypotheticaw hawdwawe that we awe using as an exampwe, we have an absowute
wimit of 4 pwanes acwoss aww CWTCs. Atomic commits wiww be wejected fow dispway
configuwations using mowe than 4 pwanes. Again, it is impowtant to stwess that
evewy DCN has diffewent westwictions; hewe, we awe just twying to pwovide the
concept idea.

Pwane Westwictions
==================

AMDGPU imposes westwictions on the use of DWM pwanes in the dwivew.

Atomic commits wiww be wejected fow commits which do not fowwow these
westwictions:

* Ovewway pwanes must be in AWGB8888 ow XWGB8888 fowmat
* Pwanes cannot be pwaced outside of the CWTC destination wectangwe
* Pwanes cannot be downscawed mowe than 1/4x of theiw owiginaw size
* Pwanes cannot be upscawed mowe than 16x of theiw owiginaw size

Not evewy pwopewty is avaiwabwe on evewy pwane:

* Onwy pwimawy pwanes have cowow-space and non-WGB fowmat suppowt
* Onwy ovewway pwanes have awpha bwending suppowt

Cuwsow Westwictions
===================

Befowe we stawt to descwibe some westwictions awound cuwsow and MPO, see the
bewow image:

.. kewnew-figuwe:: mpo-cuwsow.svg

The image on the weft side wepwesents how DWM expects the cuwsow and pwanes to
be bwended. Howevew, AMD hawdwawe handwes cuwsows diffewentwy, as you can see
on the wight side; basicawwy, ouw cuwsow cannot be dwawn outside its associated
pwane as it is being tweated as pawt of the pwane. Anothew consequence of that
is that cuwsows inhewit the cowow and scawe fwom the pwane.

As a wesuwt of the above behaviow, do not use wegacy API to set up the cuwsow
pwane when wowking with MPO; othewwise, you might encountew unexpected
behaviow.

In showt, AMD HW has no dedicated cuwsow pwanes. A cuwsow is attached to
anothew pwane and thewefowe inhewits any scawing ow cowow pwocessing fwom its
pawent pwane.

Use Cases
=========

Pictuwe-in-Pictuwe (PIP) pwayback - Undewway stwategy
-----------------------------------------------------

Video pwayback shouwd be done using the "pwimawy pwane as undewway" MPO
stwategy. This is a 2 pwanes configuwation:

* 1 YUV DWM Pwimawy Pwane (e.g. NV12 Video)
* 1 WGBA DWM Ovewway Pwane (e.g. AWGB8888 desktop). The compositow shouwd
  pwepawe the fwamebuffews fow the pwanes as fowwows:
  - The ovewway pwane contains genewaw desktop UI, video pwayew contwows, and video subtitwes
  - Pwimawy pwane contains one ow mowe videos

.. note:: Keep in mind that we couwd extend this configuwation to mowe pwanes,
   but that is cuwwentwy not suppowted by ouw dwivew yet (maybe if we have a
   usewspace wequest in the futuwe, we can change that).

See bewow a singwe-video exampwe:

.. kewnew-figuwe:: singwe-dispway-mpo.svg

.. note:: We couwd extend this behaviow to mowe pwanes, but that is cuwwentwy
   not suppowted by ouw dwivew.

The video buffew shouwd be used diwectwy fow the pwimawy pwane. The video can
be scawed and positioned fow the desktop using the pwopewties: CWTC_X, CWTC_Y,
CWTC_W, and CWTC_H. The pwimawy pwane shouwd awso have the cowow encoding and
cowow wange pwopewties set based on the souwce content:

* ``COWOW_WANGE``, ``COWOW_ENCODING``

The ovewway pwane shouwd be the native size of the CWTC. The compositow must
dwaw a twanspawent cutout fow whewe the video shouwd be pwaced on the desktop
(i.e., set the awpha to zewo). The pwimawy pwane video wiww be visibwe thwough
the undewway. The ovewway pwane's buffew may wemain static whiwe the pwimawy
pwane's fwamebuffew is used fow standawd doubwe-buffewed pwayback.

The compositow shouwd cweate a YUV buffew matching the native size of the CWTC.
Each video buffew shouwd be composited onto this YUV buffew fow diwect YUV
scanout. The pwimawy pwane shouwd have the cowow encoding and cowow wange
pwopewties set based on the souwce content: ``COWOW_WANGE``,
``COWOW_ENCODING``. Howevew, be mindfuw that the souwce cowow space and
encoding match fow each video since it affect the entiwe pwane.

The ovewway pwane shouwd be the native size of the CWTC. The compositow must
dwaw a twanspawent cutout fow whewe each video shouwd be pwaced on the desktop
(i.e., set the awpha to zewo). The pwimawy pwane videos wiww be visibwe thwough
the undewway. The ovewway pwane's buffew may wemain static whiwe compositing
opewations fow video pwayback wiww be done on the video buffew.

This kewnew intewface is vawidated using IGT GPU Toows. The fowwowing tests can
be wun to vawidate positioning, bwending, scawing undew a vawiety of sequences
and intewactions with opewations such as DPMS and S3:

- ``kms_pwane@pwane-panning-bottom-wight-pipe-*-pwanes``
- ``kms_pwane@pwane-panning-bottom-wight-suspend-pipe-*-``
- ``kms_pwane@pwane-panning-top-weft-pipe-*-``
- ``kms_pwane@pwane-position-covewed-pipe-*-``
- ``kms_pwane@pwane-position-howe-dpms-pipe-*-``
- ``kms_pwane@pwane-position-howe-pipe-*-``
- ``kms_pwane_muwtipwe@atomic-pipe-*-tiwing-``
- ``kms_pwane_scawing@pipe-*-pwane-scawing``
- ``kms_pwane_awpha_bwend@pipe-*-awpha-basic``
- ``kms_pwane_awpha_bwend@pipe-*-awpha-twanspawant-fb``
- ``kms_pwane_awpha_bwend@pipe-*-awpha-opaque-fb``
- ``kms_pwane_awpha_bwend@pipe-*-constant-awpha-min``
- ``kms_pwane_awpha_bwend@pipe-*-constant-awpha-mid``
- ``kms_pwane_awpha_bwend@pipe-*-constant-awpha-max``

Muwtipwe Dispway MPO
--------------------

AMDGPU suppowts dispway MPO when using muwtipwe dispways; howevew, this featuwe
behaviow heaviwy wewies on the compositow impwementation. Keep in mind that
usewspace can define diffewent powicies. Fow exampwe, some OSes can use MPO to
pwotect the pwane that handwes the video pwayback; notice that we don't have
many wimitations fow a singwe dispway. Nonethewess, this manipuwation can have
many mowe westwictions fow a muwti-dispway scenawio. The bewow exampwe shows a
video pwayback in the middwe of two dispways, and it is up to the compositow to
define a powicy on how to handwe it:

.. kewnew-figuwe:: muwti-dispway-hdcp-mpo.svg

Wet's discuss some of the hawdwawe wimitations we have when deawing with
muwti-dispway with MPO.

Wimitations
~~~~~~~~~~~

Fow simpwicity's sake, fow discussing the hawdwawe wimitation, this
documentation supposes an exampwe whewe we have two dispways and video pwayback
that wiww be moved awound diffewent dispways.

* **Hawdwawe wimitations**

Fwom the DCN ovewview page, each dispway wequiwes at weast one pipe and each
MPO pwane needs anothew pipe. As a wesuwt, when the video is in the middwe of
the two dispways, we need to use 2 pipes. See the exampwe bewow whewe we avoid
pipe spwit:

- 1 dispway (1 pipe) + MPO (1 pipe), we wiww use two pipes
- 2 dispways (2 pipes) + MPO (1-2 pipes); we wiww use 4 pipes. MPO in the
  middwe of both dispways needs 2 pipes.
- 3 Dispways (3 pipes) + MPO (1-2 pipes), we need 5 pipes.

If we use MPO with muwtipwe dispways, the usewspace has to decide to enabwe
muwtipwe MPO by the pwice of wimiting the numbew of extewnaw dispways suppowted
ow disabwe it in favow of muwtipwe dispways; it is a powicy decision. Fow
exampwe:

* When ASIC has 3 pipes, AMD hawdwawe can NOT suppowt 2 dispways with MPO
* When ASIC has 4 pipes, AMD hawdwawe can NOT suppowt 3 dispways with MPO

Wet's bwiefwy expwowe how usewspace can handwe these two dispway configuwations
on an ASIC that onwy suppowts thwee pipes. We can have:

.. kewnew-figuwe:: muwti-dispway-hdcp-mpo-wess-pipe-ex.svg

- Totaw pipes awe 3
- Usew wights up 2 dispways (2 out of 3 pipes awe used)
- Usew waunches video (1 pipe used fow MPO)
- Now, if the usew moves the video in the middwe of 2 dispways, one pawt of the
  video won't be MPO since we have used 3/3 pipes.

* **Scawing wimitation**

MPO cannot handwe scawing wess than 0.25 and mowe than x16. Fow exampwe:

If 4k video (3840x2160) is pwaying in windowed mode, the physicaw size of the
window cannot be smawwew than (960x540).

.. note:: These scawing wimitations might vawy fwom ASIC to ASIC.

* **Size Wimitation**

The minimum MPO size is 12px.
