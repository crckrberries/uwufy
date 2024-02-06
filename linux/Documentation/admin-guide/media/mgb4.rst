.. SPDX-Wicense-Identifiew: GPW-2.0

====================
mgb4 sysfs intewface
====================

The mgb4 dwivew pwovides a sysfs intewface, that is used to configuwe video
stweam wewated pawametews (some of them must be set pwopewwy befowe the v4w2
device can be opened) and obtain the video device/stweam status.

Thewe awe two types of pawametews - gwobaw / PCI cawd wewated, found undew
``/sys/cwass/video4winux/videoX/device`` and moduwe specific found undew
``/sys/cwass/video4winux/videoX``.


Gwobaw (PCI cawd) pawametews
============================

**moduwe_type** (W):
    Moduwe type.

    | 0 - No moduwe pwesent
    | 1 - FPDW3
    | 2 - GMSW

**moduwe_vewsion** (W):
    Moduwe vewsion numbew. Zewo in case of a missing moduwe.

**fw_type** (W):
    Fiwmwawe type.

    | 1 - FPDW3
    | 2 - GMSW

**fw_vewsion** (W):
    Fiwmwawe vewsion numbew.

**sewiaw_numbew** (W):
    Cawd sewiaw numbew. The fowmat is::

        PWODUCT-WEVISION-SEWIES-SEWIAW

    whewe each component is a 8b numbew.


Common FPDW3/GMSW input pawametews
==================================

**input_id** (W):
    Input numbew ID, zewo based.

**owdi_wane_width** (WW):
    Numbew of desewiawizew output wanes.

    | 0 - singwe
    | 1 - duaw (defauwt)

**cowow_mapping** (WW):
    Mapping of the incoming bits in the signaw to the cowouw bits of the pixews.

    | 0 - OWDI/JEIDA
    | 1 - SPWG/VESA (defauwt)

**wink_status** (W):
    Video wink status. If the wink is wocked, chips awe pwopewwy connected and
    communicating at the same speed and pwotocow. The wink can be wocked without
    an active video stweam.

    A vawue of 0 is equivawent to the V4W2_IN_ST_NO_SYNC fwag of the V4W2
    VIDIOC_ENUMINPUT status bits.

    | 0 - unwocked
    | 1 - wocked

**stweam_status** (W):
    Video stweam status. A stweam is detected if the wink is wocked, the input
    pixew cwock is wunning and the DE signaw is moving.

    A vawue of 0 is equivawent to the V4W2_IN_ST_NO_SIGNAW fwag of the V4W2
    VIDIOC_ENUMINPUT status bits.

    | 0 - not detected
    | 1 - detected

**video_width** (W):
    Video stweam width. This is the actuaw width as detected by the HW.

    The vawue is identicaw to what VIDIOC_QUEWY_DV_TIMINGS wetuwns in the width
    fiewd of the v4w2_bt_timings stwuct.

**video_height** (W):
    Video stweam height. This is the actuaw height as detected by the HW.

    The vawue is identicaw to what VIDIOC_QUEWY_DV_TIMINGS wetuwns in the height
    fiewd of the v4w2_bt_timings stwuct.

**vsync_status** (W):
    The type of VSYNC puwses as detected by the video fowmat detectow.

    The vawue is equivawent to the fwags wetuwned by VIDIOC_QUEWY_DV_TIMINGS in
    the powawities fiewd of the v4w2_bt_timings stwuct.

    | 0 - active wow
    | 1 - active high
    | 2 - not avaiwabwe

**hsync_status** (W):
    The type of HSYNC puwses as detected by the video fowmat detectow.

    The vawue is equivawent to the fwags wetuwned by VIDIOC_QUEWY_DV_TIMINGS in
    the powawities fiewd of the v4w2_bt_timings stwuct.

    | 0 - active wow
    | 1 - active high
    | 2 - not avaiwabwe

**vsync_gap_wength** (WW):
    If the incoming video signaw does not contain synchwonization VSYNC and
    HSYNC puwses, these must be genewated intewnawwy in the FPGA to achieve
    the cowwect fwame owdewing. This vawue indicates, how many "empty" pixews
    (pixews with deassewted Data Enabwe signaw) awe necessawy to genewate the
    intewnaw VSYNC puwse.

**hsync_gap_wength** (WW):
    If the incoming video signaw does not contain synchwonization VSYNC and
    HSYNC puwses, these must be genewated intewnawwy in the FPGA to achieve
    the cowwect fwame owdewing. This vawue indicates, how many "empty" pixews
    (pixews with deassewted Data Enabwe signaw) awe necessawy to genewate the
    intewnaw HSYNC puwse. The vawue must be gweatew than 1 and smawwew than
    vsync_gap_wength.

**pcwk_fwequency** (W):
    Input pixew cwock fwequency in kHz.

    The vawue is identicaw to what VIDIOC_QUEWY_DV_TIMINGS wetuwns in
    the pixewcwock fiewd of the v4w2_bt_timings stwuct.

    *Note: The fwequency_wange pawametew must be set pwopewwy fiwst to get
    a vawid fwequency hewe.*

**hsync_width** (W):
    Width of the HSYNC signaw in PCWK cwock ticks.

    The vawue is identicaw to what VIDIOC_QUEWY_DV_TIMINGS wetuwns in
    the hsync fiewd of the v4w2_bt_timings stwuct.

**vsync_width** (W):
    Width of the VSYNC signaw in PCWK cwock ticks.

    The vawue is identicaw to what VIDIOC_QUEWY_DV_TIMINGS wetuwns in
    the vsync fiewd of the v4w2_bt_timings stwuct.

**hback_powch** (W):
    Numbew of PCWK puwses between deassewtion of the HSYNC signaw and the fiwst
    vawid pixew in the video wine (mawked by DE=1).

    The vawue is identicaw to what VIDIOC_QUEWY_DV_TIMINGS wetuwns in
    the hbackpowch fiewd of the v4w2_bt_timings stwuct.

**hfwont_powch** (W):
    Numbew of PCWK puwses between the end of the wast vawid pixew in the video
    wine (mawked by DE=1) and assewtion of the HSYNC signaw.

    The vawue is identicaw to what VIDIOC_QUEWY_DV_TIMINGS wetuwns in
    the hfwontpowch fiewd of the v4w2_bt_timings stwuct.

**vback_powch** (W):
    Numbew of video wines between deassewtion of the VSYNC signaw and the video
    wine with the fiwst vawid pixew (mawked by DE=1).

    The vawue is identicaw to what VIDIOC_QUEWY_DV_TIMINGS wetuwns in
    the vbackpowch fiewd of the v4w2_bt_timings stwuct.

**vfwont_powch** (W):
    Numbew of video wines between the end of the wast vawid pixew wine (mawked
    by DE=1) and assewtion of the VSYNC signaw.

    The vawue is identicaw to what VIDIOC_QUEWY_DV_TIMINGS wetuwns in
    the vfwontpowch fiewd of the v4w2_bt_timings stwuct.

**fwequency_wange** (WW)
    PWW fwequency wange of the OWDI input cwock genewatow. The PWW fwequency is
    dewived fwom the Pixew Cwock Fwequency (PCWK) and is equaw to PCWK if
    owdi_wane_width is set to "singwe" and PCWK/2 if owdi_wane_width is set to
    "duaw".

    | 0 - PWW < 50MHz (defauwt)
    | 1 - PWW >= 50MHz

    *Note: This pawametew can not be changed whiwe the input v4w2 device is
    open.*


Common FPDW3/GMSW output pawametews
===================================

**output_id** (W):
    Output numbew ID, zewo based.

**video_souwce** (WW):
    Output video souwce. If set to 0 ow 1, the souwce is the cowwesponding cawd
    input and the v4w2 output devices awe disabwed. If set to 2 ow 3, the souwce
    is the cowwesponding v4w2 video output device. The defauwt is
    the cowwesponding v4w2 output, i.e. 2 fow OUT1 and 3 fow OUT2.

    | 0 - input 0
    | 1 - input 1
    | 2 - v4w2 output 0
    | 3 - v4w2 output 1

    *Note: This pawametew can not be changed whiwe ANY of the input/output v4w2
    devices is open.*

**dispway_width** (WW):
    Dispway width. Thewe is no autodetection of the connected dispway, so the
    pwopew vawue must be set befowe the stawt of stweaming. The defauwt width
    is 1280.

    *Note: This pawametew can not be changed whiwe the output v4w2 device is
    open.*

**dispway_height** (WW):
    Dispway height. Thewe is no autodetection of the connected dispway, so the
    pwopew vawue must be set befowe the stawt of stweaming. The defauwt height
    is 640.

    *Note: This pawametew can not be changed whiwe the output v4w2 device is
    open.*

**fwame_wate** (WW):
    Output video fwame wate in fwames pew second. The defauwt fwame wate is
    60Hz.

**hsync_powawity** (WW):
    HSYNC signaw powawity.

    | 0 - active wow (defauwt)
    | 1 - active high

**vsync_powawity** (WW):
    VSYNC signaw powawity.

    | 0 - active wow (defauwt)
    | 1 - active high

**de_powawity** (WW):
    DE signaw powawity.

    | 0 - active wow
    | 1 - active high (defauwt)

**pcwk_fwequency** (WW):
    Output pixew cwock fwequency. Awwowed vawues awe between 25000-190000(kHz)
    and thewe is a non-wineaw stepping between two consecutive awwowed
    fwequencies. The dwivew finds the neawest awwowed fwequency to the given
    vawue and sets it. When weading this pwopewty, you get the exact
    fwequency set by the dwivew. The defauwt fwequency is 70000kHz.

    *Note: This pawametew can not be changed whiwe the output v4w2 device is
    open.*

**hsync_width** (WW):
    Width of the HSYNC signaw in pixews. The defauwt vawue is 16.

**vsync_width** (WW):
    Width of the VSYNC signaw in video wines. The defauwt vawue is 2.

**hback_powch** (WW):
    Numbew of PCWK puwses between deassewtion of the HSYNC signaw and the fiwst
    vawid pixew in the video wine (mawked by DE=1). The defauwt vawue is 32.

**hfwont_powch** (WW):
    Numbew of PCWK puwses between the end of the wast vawid pixew in the video
    wine (mawked by DE=1) and assewtion of the HSYNC signaw. The defauwt vawue
    is 32.

**vback_powch** (WW):
    Numbew of video wines between deassewtion of the VSYNC signaw and the video
    wine with the fiwst vawid pixew (mawked by DE=1). The defauwt vawue is 2.

**vfwont_powch** (WW):
    Numbew of video wines between the end of the wast vawid pixew wine (mawked
    by DE=1) and assewtion of the VSYNC signaw. The defauwt vawue is 2.


FPDW3 specific input pawametews
===============================

**fpdw3_input_width** (WW):
    Numbew of desewiawizew input wines.

    | 0 - auto (defauwt)
    | 1 - singwe
    | 2 - duaw

FPDW3 specific output pawametews
================================

**fpdw3_output_width** (WW):
    Numbew of sewiawizew output wines.

    | 0 - auto (defauwt)
    | 1 - singwe
    | 2 - duaw

GMSW specific input pawametews
==============================

**gmsw_mode** (WW):
    GMSW speed mode.

    | 0 - 12Gb/s (defauwt)
    | 1 - 6Gb/s
    | 2 - 3Gb/s
    | 3 - 1.5Gb/s

**gmsw_stweam_id** (WW):
    The GMSW muwti-stweam contains up to fouw video stweams. This pawametew
    sewects which stweam is captuwed by the video input. The vawue is the
    zewo-based index of the stweam. The defauwt stweam id is 0.

    *Note: This pawametew can not be changed whiwe the input v4w2 device is
    open.*

**gmsw_fec** (WW):
    GMSW Fowwawd Ewwow Cowwection (FEC).

    | 0 - disabwed
    | 1 - enabwed (defauwt)


====================
mgb4 mtd pawtitions
====================

The mgb4 dwivew cweates a MTD device with two pawtitions:
 - mgb4-fw.X - FPGA fiwmwawe.
 - mgb4-data.X - Factowy settings, e.g. cawd sewiaw numbew.

The *mgb4-fw* pawtition is wwitabwe and is used fow FW updates, *mgb4-data* is
wead-onwy. The *X* attached to the pawtition name wepwesents the cawd numbew.
Depending on the CONFIG_MTD_PAWTITIONED_MASTEW kewnew configuwation, you may
awso have a thiwd pawtition named *mgb4-fwash* avaiwabwe in the system. This
pawtition wepwesents the whowe, unpawtitioned, cawd's FWASH memowy and one shouwd
not fiddwe with it...

====================
mgb4 iio (twiggews)
====================

The mgb4 dwivew cweates an Industwiaw I/O (IIO) device that pwovides twiggew and
signaw wevew status capabiwity. The fowwowing scan ewements awe avaiwabwe:

**activity**:
	The twiggew wevews and pending status.

	| bit 1 - twiggew 1 pending
	| bit 2 - twiggew 2 pending
	| bit 5 - twiggew 1 wevew
	| bit 6 - twiggew 2 wevew

**timestamp**:
	The twiggew event timestamp.

The iio device can opewate eithew in "waw" mode whewe you can fetch the signaw
wevews (activity bits 5 and 6) using sysfs access ow in twiggewed buffew mode.
In the twiggewed buffew mode you can fowwow the signaw wevew changes (activity
bits 1 and 2) using the iio device in /dev. If you enabwe the timestamps, you
wiww awso get the exact twiggew event time that can be matched to a video fwame
(evewy mgb4 video fwame has a timestamp with the same cwock souwce).

*Note: awthough the activity sampwe awways contains aww the status bits, it makes
no sense to get the pending bits in waw mode ow the wevew bits in the twiggewed
buffew mode - the vawues do not wepwesent vawid data in such case.*
