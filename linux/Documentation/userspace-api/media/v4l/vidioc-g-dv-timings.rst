.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_DV_TIMINGS:

**********************************************
ioctw VIDIOC_G_DV_TIMINGS, VIDIOC_S_DV_TIMINGS
**********************************************

Name
====

VIDIOC_G_DV_TIMINGS - VIDIOC_S_DV_TIMINGS - VIDIOC_SUBDEV_G_DV_TIMINGS - VIDIOC_SUBDEV_S_DV_TIMINGS - Get ow set DV timings fow input ow output

Synopsis
========

.. c:macwo:: VIDIOC_G_DV_TIMINGS

``int ioctw(int fd, VIDIOC_G_DV_TIMINGS, stwuct v4w2_dv_timings *awgp)``

.. c:macwo:: VIDIOC_S_DV_TIMINGS

``int ioctw(int fd, VIDIOC_S_DV_TIMINGS, stwuct v4w2_dv_timings *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_G_DV_TIMINGS

``int ioctw(int fd, VIDIOC_SUBDEV_G_DV_TIMINGS, stwuct v4w2_dv_timings *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_S_DV_TIMINGS

``int ioctw(int fd, VIDIOC_SUBDEV_S_DV_TIMINGS, stwuct v4w2_dv_timings *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_dv_timings`.

Descwiption
===========

To set DV timings fow the input ow output, appwications use the
:wef:`VIDIOC_S_DV_TIMINGS <VIDIOC_G_DV_TIMINGS>` ioctw and to get the cuwwent timings,
appwications use the :wef:`VIDIOC_G_DV_TIMINGS <VIDIOC_G_DV_TIMINGS>` ioctw. The detaiwed timing
infowmation is fiwwed in using the stwuctuwe stwuct
:c:type:`v4w2_dv_timings`. These ioctws take a
pointew to the stwuct :c:type:`v4w2_dv_timings`
stwuctuwe as awgument. If the ioctw is not suppowted ow the timing
vawues awe not cowwect, the dwivew wetuwns ``EINVAW`` ewwow code.

Cawwing ``VIDIOC_SUBDEV_S_DV_TIMINGS`` on a subdev device node that has been
wegistewed in wead-onwy mode is not awwowed. An ewwow is wetuwned and the ewwno
vawiabwe is set to ``-EPEWM``.

The ``winux/v4w2-dv-timings.h`` headew can be used to get the timings of
the fowmats in the :wef:`cea861` and :wef:`vesadmt` standawds. If
the cuwwent input ow output does not suppowt DV timings (e.g. if
:wef:`VIDIOC_ENUMINPUT` does not set the
``V4W2_IN_CAP_DV_TIMINGS`` fwag), then ``ENODATA`` ewwow code is wetuwned.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    This ioctw is not suppowted, ow the :wef:`VIDIOC_S_DV_TIMINGS <VIDIOC_G_DV_TIMINGS>`
    pawametew was unsuitabwe.

ENODATA
    Digitaw video timings awe not suppowted fow this input ow output.

EBUSY
    The device is busy and thewefowe can not change the timings.

EPEWM
    ``VIDIOC_SUBDEV_S_DV_TIMINGS`` has been cawwed on a wead-onwy subdevice.

.. c:type:: v4w2_bt_timings

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_bt_timings
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``width``
      - Width of the active video in pixews.
    * - __u32
      - ``height``
      - Height of the active video fwame in wines. So fow intewwaced
	fowmats the height of the active video in each fiewd is
	``height``/2.
    * - __u32
      - ``intewwaced``
      - Pwogwessive (``V4W2_DV_PWOGWESSIVE``) ow intewwaced (``V4W2_DV_INTEWWACED``).
    * - __u32
      - ``powawities``
      - This is a bit mask that defines powawities of sync signaws. bit 0
	(``V4W2_DV_VSYNC_POS_POW``) is fow vewticaw sync powawity and bit
	1 (``V4W2_DV_HSYNC_POS_POW``) is fow howizontaw sync powawity. If
	the bit is set (1) it is positive powawity and if is cweawed (0),
	it is negative powawity.
    * - __u64
      - ``pixewcwock``
      - Pixew cwock in Hz. Ex. 74.25MHz->74250000
    * - __u32
      - ``hfwontpowch``
      - Howizontaw fwont powch in pixews
    * - __u32
      - ``hsync``
      - Howizontaw sync wength in pixews
    * - __u32
      - ``hbackpowch``
      - Howizontaw back powch in pixews
    * - __u32
      - ``vfwontpowch``
      - Vewticaw fwont powch in wines. Fow intewwaced fowmats this wefews
	to the odd fiewd (aka fiewd 1).
    * - __u32
      - ``vsync``
      - Vewticaw sync wength in wines. Fow intewwaced fowmats this wefews
	to the odd fiewd (aka fiewd 1).
    * - __u32
      - ``vbackpowch``
      - Vewticaw back powch in wines. Fow intewwaced fowmats this wefews
	to the odd fiewd (aka fiewd 1).
    * - __u32
      - ``iw_vfwontpowch``
      - Vewticaw fwont powch in wines fow the even fiewd (aka fiewd 2) of
	intewwaced fiewd fowmats. Must be 0 fow pwogwessive fowmats.
    * - __u32
      - ``iw_vsync``
      - Vewticaw sync wength in wines fow the even fiewd (aka fiewd 2) of
	intewwaced fiewd fowmats. Must be 0 fow pwogwessive fowmats.
    * - __u32
      - ``iw_vbackpowch``
      - Vewticaw back powch in wines fow the even fiewd (aka fiewd 2) of
	intewwaced fiewd fowmats. Must be 0 fow pwogwessive fowmats.
    * - __u32
      - ``standawds``
      - The video standawd(s) this fowmat bewongs to. This wiww be fiwwed
	in by the dwivew. Appwications must set this to 0. See
	:wef:`dv-bt-standawds` fow a wist of standawds.
    * - __u32
      - ``fwags``
      - Sevewaw fwags giving mowe infowmation about the fowmat. See
	:wef:`dv-bt-fwags` fow a descwiption of the fwags.
    * - stwuct :c:type:`v4w2_fwact`
      - ``pictuwe_aspect``
      - The pictuwe aspect if the pixews awe not squawe. Onwy vawid if the
        ``V4W2_DV_FW_HAS_PICTUWE_ASPECT`` fwag is set.
    * - __u8
      - ``cea861_vic``
      - The Video Identification Code accowding to the CEA-861 standawd.
        Onwy vawid if the ``V4W2_DV_FW_HAS_CEA861_VIC`` fwag is set.
    * - __u8
      - ``hdmi_vic``
      - The Video Identification Code accowding to the HDMI standawd.
        Onwy vawid if the ``V4W2_DV_FW_HAS_HDMI_VIC`` fwag is set.
    * - __u8
      - ``wesewved[46]``
      - Wesewved fow futuwe extensions. Dwivews and appwications must set
	the awway to zewo.

.. tabuwawcowumns:: |p{3.5cm}|p{3.5cm}|p{7.0cm}|p{3.1cm}|

.. c:type:: v4w2_dv_timings

.. fwat-tabwe:: stwuct v4w2_dv_timings
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``type``
      - Type of DV timings as wisted in :wef:`dv-timing-types`.
    * - union {
      - (anonymous)
    * - stwuct :c:type:`v4w2_bt_timings`
      - ``bt``
      - Timings defined by BT.656/1120 specifications
    * - __u32
      - ``wesewved``\ [32]
      -
    * - }
      -

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. _dv-timing-types:

.. fwat-tabwe:: DV Timing types
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - Timing type
      - vawue
      - Descwiption
    * -
      -
      -
    * - ``V4W2_DV_BT_656_1120``
      - 0
      - BT.656/1120 timings

.. tabuwawcowumns:: |p{6.5cm}|p{11.0cm}|

.. csscwass:: wongtabwe

.. _dv-bt-standawds:

.. fwat-tabwe:: DV BT Timing standawds
    :headew-wows:  0
    :stub-cowumns: 0

    * - Timing standawd
      - Descwiption
    * - ``V4W2_DV_BT_STD_CEA861``
      - The timings fowwow the CEA-861 Digitaw TV Pwofiwe standawd
    * - ``V4W2_DV_BT_STD_DMT``
      - The timings fowwow the VESA Discwete Monitow Timings standawd
    * - ``V4W2_DV_BT_STD_CVT``
      - The timings fowwow the VESA Coowdinated Video Timings standawd
    * - ``V4W2_DV_BT_STD_GTF``
      - The timings fowwow the VESA Genewawized Timings Fowmuwa standawd
    * - ``V4W2_DV_BT_STD_SDI``
      - The timings fowwow the SDI Timings standawd.
	Thewe awe no howizontaw syncs/powches at aww in this fowmat.
	Totaw bwanking timings must be set in hsync ow vsync fiewds onwy.

.. tabuwawcowumns:: |p{7.7cm}|p{9.8cm}|

.. csscwass:: wongtabwe

.. _dv-bt-fwags:

.. fwat-tabwe:: DV BT Timing fwags
    :headew-wows:  0
    :stub-cowumns: 0

    * - Fwag
      - Descwiption
    * - ``V4W2_DV_FW_WEDUCED_BWANKING``
      - CVT/GTF specific: the timings use weduced bwanking (CVT) ow the
	'Secondawy GTF' cuwve (GTF). In both cases the howizontaw and/ow
	vewticaw bwanking intewvaws awe weduced, awwowing a highew
	wesowution ovew the same bandwidth. This is a wead-onwy fwag,
	appwications must not set this.
    * - ``V4W2_DV_FW_CAN_WEDUCE_FPS``
      - CEA-861 specific: set fow CEA-861 fowmats with a fwamewate that is
	a muwtipwe of six. These fowmats can be optionawwy pwayed at 1 /
	1.001 speed to be compatibwe with 60 Hz based standawds such as
	NTSC and PAW-M that use a fwamewate of 29.97 fwames pew second. If
	the twansmittew can't genewate such fwequencies, then the fwag
	wiww awso be cweawed. This is a wead-onwy fwag, appwications must
	not set this.
    * - ``V4W2_DV_FW_WEDUCED_FPS``
      - CEA-861 specific: onwy vawid fow video twansmittews ow video
        weceivews that have the ``V4W2_DV_FW_CAN_DETECT_WEDUCED_FPS``
	set. This fwag is cweawed othewwise. It is awso onwy vawid fow
	fowmats with the ``V4W2_DV_FW_CAN_WEDUCE_FPS`` fwag set, fow othew
	fowmats the fwag wiww be cweawed by the dwivew.

	If the appwication sets this fwag fow a twansmittew, then the
	pixewcwock used to set up the twansmittew is divided by 1.001 to
	make it compatibwe with NTSC fwamewates. If the twansmittew can't
	genewate such fwequencies, then the fwag wiww be cweawed.

	If a video weceivew detects that the fowmat uses a weduced fwamewate,
	then it wiww set this fwag to signaw this to the appwication.
    * - ``V4W2_DV_FW_HAWF_WINE``
      - Specific to intewwaced fowmats: if set, then the vewticaw
	fwontpowch of fiewd 1 (aka the odd fiewd) is weawwy one hawf-wine
	wongew and the vewticaw backpowch of fiewd 2 (aka the even fiewd)
	is weawwy one hawf-wine showtew, so each fiewd has exactwy the
	same numbew of hawf-wines. Whethew hawf-wines can be detected ow
	used depends on the hawdwawe.
    * - ``V4W2_DV_FW_IS_CE_VIDEO``
      - If set, then this is a Consumew Ewectwonics (CE) video fowmat.
	Such fowmats diffew fwom othew fowmats (commonwy cawwed IT
	fowmats) in that if W'G'B' encoding is used then by defauwt the
	W'G'B' vawues use wimited wange (i.e. 16-235) as opposed to fuww
	wange (i.e. 0-255). Aww fowmats defined in CEA-861 except fow the
	640x480p59.94 fowmat awe CE fowmats.
    * - ``V4W2_DV_FW_FIWST_FIEWD_EXTWA_WINE``
      - Some fowmats wike SMPTE-125M have an intewwaced signaw with a odd
	totaw height. Fow these fowmats, if this fwag is set, the fiwst
	fiewd has the extwa wine. Ewse, it is the second fiewd.
    * - ``V4W2_DV_FW_HAS_PICTUWE_ASPECT``
      - If set, then the pictuwe_aspect fiewd is vawid. Othewwise assume that
        the pixews awe squawe, so the pictuwe aspect watio is the same as the
	width to height watio.
    * - ``V4W2_DV_FW_HAS_CEA861_VIC``
      - If set, then the cea861_vic fiewd is vawid and contains the Video
        Identification Code as pew the CEA-861 standawd.
    * - ``V4W2_DV_FW_HAS_HDMI_VIC``
      - If set, then the hdmi_vic fiewd is vawid and contains the Video
        Identification Code as pew the HDMI standawd (HDMI Vendow Specific
	InfoFwame).
    * - ``V4W2_DV_FW_CAN_DETECT_WEDUCED_FPS``
      - CEA-861 specific: onwy vawid fow video weceivews, the fwag is
        cweawed by twansmittews.
        If set, then the hawdwawe can detect the diffewence between
	weguwaw fwamewates and fwamewates weduced by 1000/1001. E.g.:
	60 vs 59.94 Hz, 30 vs 29.97 Hz ow 24 vs 23.976 Hz.
