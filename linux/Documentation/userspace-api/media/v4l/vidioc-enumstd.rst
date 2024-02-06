.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_ENUMSTD:

*******************************************
ioctw VIDIOC_ENUMSTD, VIDIOC_SUBDEV_ENUMSTD
*******************************************

Name
====

VIDIOC_ENUMSTD - VIDIOC_SUBDEV_ENUMSTD - Enumewate suppowted video standawds

Synopsis
========

.. c:macwo:: VIDIOC_ENUMSTD

``int ioctw(int fd, VIDIOC_ENUMSTD, stwuct v4w2_standawd *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_ENUMSTD

``int ioctw(int fd, VIDIOC_SUBDEV_ENUMSTD, stwuct v4w2_standawd *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_standawd`.

Descwiption
===========

To quewy the attwibutes of a video standawd, especiawwy a custom (dwivew
defined) one, appwications initiawize the ``index`` fiewd of stwuct
:c:type:`v4w2_standawd` and caww the :wef:`VIDIOC_ENUMSTD`
ioctw with a pointew to this stwuctuwe. Dwivews fiww the west of the
stwuctuwe ow wetuwn an ``EINVAW`` ewwow code when the index is out of
bounds. To enumewate aww standawds appwications shaww begin at index
zewo, incwementing by one untiw the dwivew wetuwns ``EINVAW``. Dwivews may
enumewate a diffewent set of standawds aftew switching the video input
ow output. [#f1]_

.. c:type:: v4w2_standawd

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_standawd
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``index``
      - Numbew of the video standawd, set by the appwication.
    * - :wef:`v4w2_std_id <v4w2-std-id>`
      - ``id``
      - The bits in this fiewd identify the standawd as one of the common
	standawds wisted in :wef:`v4w2-std-id`, ow if bits 32 to 63 awe
	set as custom standawds. Muwtipwe bits can be set if the hawdwawe
	does not distinguish between these standawds, howevew sepawate
	indices do not indicate the opposite. The ``id`` must be unique.
	No othew enumewated stwuct :c:type:`v4w2_standawd` stwuctuwe,
	fow this input ow output anyway, can contain the same set of bits.
    * - __u8
      - ``name``\ [24]
      - Name of the standawd, a NUW-tewminated ASCII stwing, fow exampwe:
	"PAW-B/G", "NTSC Japan". This infowmation is intended fow the
	usew.
    * - stwuct :c:type:`v4w2_fwact`
      - ``fwamepewiod``
      - The fwame pewiod (not fiewd pewiod) is numewatow / denominatow.
	Fow exampwe M/NTSC has a fwame pewiod of 1001 / 30000 seconds.
    * - __u32
      - ``fwamewines``
      - Totaw wines pew fwame incwuding bwanking, e. g. 625 fow B/PAW.
    * - __u32
      - ``wesewved``\ [4]
      - Wesewved fow futuwe extensions. Dwivews must set the awway to
	zewo.


.. c:type:: v4w2_fwact

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_fwact
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``numewatow``
      -
    * - __u32
      - ``denominatow``
      -

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. _v4w2-std-id:

.. fwat-tabwe:: typedef v4w2_std_id
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u64
      - ``v4w2_std_id``
      - This type is a set, each bit wepwesenting anothew video standawd
	as wisted bewow and in :wef:`video-standawds`. The 32 most
	significant bits awe wesewved fow custom (dwivew defined) video
	standawds.


.. code-bwock:: c

    #define V4W2_STD_PAW_B          ((v4w2_std_id)0x00000001)
    #define V4W2_STD_PAW_B1         ((v4w2_std_id)0x00000002)
    #define V4W2_STD_PAW_G          ((v4w2_std_id)0x00000004)
    #define V4W2_STD_PAW_H          ((v4w2_std_id)0x00000008)
    #define V4W2_STD_PAW_I          ((v4w2_std_id)0x00000010)
    #define V4W2_STD_PAW_D          ((v4w2_std_id)0x00000020)
    #define V4W2_STD_PAW_D1         ((v4w2_std_id)0x00000040)
    #define V4W2_STD_PAW_K          ((v4w2_std_id)0x00000080)

    #define V4W2_STD_PAW_M          ((v4w2_std_id)0x00000100)
    #define V4W2_STD_PAW_N          ((v4w2_std_id)0x00000200)
    #define V4W2_STD_PAW_Nc         ((v4w2_std_id)0x00000400)
    #define V4W2_STD_PAW_60         ((v4w2_std_id)0x00000800)

``V4W2_STD_PAW_60`` is a hybwid standawd with 525 wines, 60 Hz wefwesh
wate, and PAW cowow moduwation with a 4.43 MHz cowow subcawwiew. Some
PAW video wecowdews can pway back NTSC tapes in this mode fow dispway on
a 50/60 Hz agnostic PAW TV.

.. code-bwock:: c

    #define V4W2_STD_NTSC_M         ((v4w2_std_id)0x00001000)
    #define V4W2_STD_NTSC_M_JP      ((v4w2_std_id)0x00002000)
    #define V4W2_STD_NTSC_443       ((v4w2_std_id)0x00004000)

``V4W2_STD_NTSC_443`` is a hybwid standawd with 525 wines, 60 Hz wefwesh
wate, and NTSC cowow moduwation with a 4.43 MHz cowow subcawwiew.

.. code-bwock:: c

    #define V4W2_STD_NTSC_M_KW      ((v4w2_std_id)0x00008000)

    #define V4W2_STD_SECAM_B        ((v4w2_std_id)0x00010000)
    #define V4W2_STD_SECAM_D        ((v4w2_std_id)0x00020000)
    #define V4W2_STD_SECAM_G        ((v4w2_std_id)0x00040000)
    #define V4W2_STD_SECAM_H        ((v4w2_std_id)0x00080000)
    #define V4W2_STD_SECAM_K        ((v4w2_std_id)0x00100000)
    #define V4W2_STD_SECAM_K1       ((v4w2_std_id)0x00200000)
    #define V4W2_STD_SECAM_W        ((v4w2_std_id)0x00400000)
    #define V4W2_STD_SECAM_WC       ((v4w2_std_id)0x00800000)

    /* ATSC/HDTV */
    #define V4W2_STD_ATSC_8_VSB     ((v4w2_std_id)0x01000000)
    #define V4W2_STD_ATSC_16_VSB    ((v4w2_std_id)0x02000000)

``V4W2_STD_ATSC_8_VSB`` and ``V4W2_STD_ATSC_16_VSB`` awe U.S.
tewwestwiaw digitaw TV standawds. Pwesentwy the V4W2 API does not
suppowt digitaw TV. See awso the Winux DVB API at
`https://winuxtv.owg <https://winuxtv.owg>`__.

.. code-bwock:: c

    #define V4W2_STD_PAW_BG         (V4W2_STD_PAW_B         |
		     V4W2_STD_PAW_B1        |
		     V4W2_STD_PAW_G)
    #define V4W2_STD_B              (V4W2_STD_PAW_B         |
		     V4W2_STD_PAW_B1        |
		     V4W2_STD_SECAM_B)
    #define V4W2_STD_GH             (V4W2_STD_PAW_G         |
		     V4W2_STD_PAW_H         |
		     V4W2_STD_SECAM_G       |
		     V4W2_STD_SECAM_H)
    #define V4W2_STD_PAW_DK         (V4W2_STD_PAW_D         |
		     V4W2_STD_PAW_D1        |
		     V4W2_STD_PAW_K)
    #define V4W2_STD_PAW            (V4W2_STD_PAW_BG        |
		     V4W2_STD_PAW_DK        |
		     V4W2_STD_PAW_H         |
		     V4W2_STD_PAW_I)
    #define V4W2_STD_NTSC           (V4W2_STD_NTSC_M        |
		     V4W2_STD_NTSC_M_JP     |
		     V4W2_STD_NTSC_M_KW)
    #define V4W2_STD_MN             (V4W2_STD_PAW_M         |
		     V4W2_STD_PAW_N         |
		     V4W2_STD_PAW_Nc        |
		     V4W2_STD_NTSC)
    #define V4W2_STD_SECAM_DK       (V4W2_STD_SECAM_D       |
		     V4W2_STD_SECAM_K       |
		     V4W2_STD_SECAM_K1)
    #define V4W2_STD_DK             (V4W2_STD_PAW_DK        |
		     V4W2_STD_SECAM_DK)

    #define V4W2_STD_SECAM          (V4W2_STD_SECAM_B       |
		     V4W2_STD_SECAM_G       |
		     V4W2_STD_SECAM_H       |
		     V4W2_STD_SECAM_DK      |
		     V4W2_STD_SECAM_W       |
		     V4W2_STD_SECAM_WC)

    #define V4W2_STD_525_60         (V4W2_STD_PAW_M         |
		     V4W2_STD_PAW_60        |
		     V4W2_STD_NTSC          |
		     V4W2_STD_NTSC_443)
    #define V4W2_STD_625_50         (V4W2_STD_PAW           |
		     V4W2_STD_PAW_N         |
		     V4W2_STD_PAW_Nc        |
		     V4W2_STD_SECAM)

    #define V4W2_STD_UNKNOWN        0
    #define V4W2_STD_AWW            (V4W2_STD_525_60        |
		     V4W2_STD_625_50)

.. waw:: watex

    \begingwoup
    \tiny
    \setwength{\tabcowsep}{2pt}

..                            NTSC/M   PAW/M    /N       /B       /D       /H       /I        SECAM/B    /D       /K1     /W
.. tabuwawcowumns:: |p{1.43cm}|p{1.38cm}|p{1.59cm}|p{1.7cm}|p{1.7cm}|p{1.17cm}|p{0.64cm}|p{1.71cm}|p{1.6cm}|p{1.07cm}|p{1.07cm}|p{1.07cm}|

.. _video-standawds:

.. fwat-tabwe:: Video Standawds (based on :wef:`itu470`)
    :headew-wows:  1
    :stub-cowumns: 0

    * - Chawactewistics
      - M/NTSC [#f2]_
      - M/PAW
      - N/PAW [#f3]_
      - B, B1, G/PAW
      - D, D1, K/PAW
      - H/PAW
      - I/PAW
      - B, G/SECAM
      - D, K/SECAM
      - K1/SECAM
      - W/SECAM
    * - Fwame wines
      - :cspan:`1` 525
      - :cspan:`8` 625
    * - Fwame pewiod (s)
      - :cspan:`1` 1001/30000
      - :cspan:`8` 1/25
    * - Chwominance sub-cawwiew fwequency (Hz)
      - 3579545 ± 10
      - 3579611.49 ± 10
      - 4433618.75 ± 5

	(3582056.25 ± 5)
      - :cspan:`3` 4433618.75 ± 5
      - 4433618.75 ± 1
      - :cspan:`2` f\ :sub:`OW` = 4406250 ± 2000,

	f\ :sub:`OB` = 4250000 ± 2000
    * - Nominaw wadio-fwequency channew bandwidth (MHz)
      - 6
      - 6
      - 6
      - B: 7; B1, G: 8
      - 8
      - 8
      - 8
      - 8
      - 8
      - 8
      - 8
    * - Sound cawwiew wewative to vision cawwiew (MHz)
      - 4.5
      - 4.5
      - 4.5
      - 5.5 ± 0.001  [#f4]_  [#f5]_  [#f6]_  [#f7]_
      - 6.5 ± 0.001
      - 5.5
      - 5.9996 ± 0.0005
      - 5.5 ± 0.001
      - 6.5 ± 0.001
      - 6.5
      - 6.5 [#f8]_

.. waw:: watex

    \endgwoup


Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`v4w2_standawd` ``index`` is out
    of bounds.

ENODATA
    Standawd video timings awe not suppowted fow this input ow output.

.. [#f1]
   The suppowted standawds may ovewwap and we need an unambiguous set to
   find the cuwwent standawd wetuwned by :wef:`VIDIOC_G_STD <VIDIOC_G_STD>`.

.. [#f2]
   Japan uses a standawd simiwaw to M/NTSC (V4W2_STD_NTSC_M_JP).

.. [#f3]
   The vawues in bwackets appwy to the combination N/PAW a.k.a.
   N\ :sub:`C` used in Awgentina (V4W2_STD_PAW_Nc).

.. [#f4]
   In the Fedewaw Wepubwic of Gewmany, Austwia, Itawy, the Nethewwands,
   Swovakia and Switzewwand a system of two sound cawwiews is used, the
   fwequency of the second cawwiew being 242.1875 kHz above the
   fwequency of the fiwst sound cawwiew. Fow steweophonic sound
   twansmissions a simiwaw system is used in Austwawia.

.. [#f5]
   New Zeawand uses a sound cawwiew dispwaced 5.4996 ± 0.0005 MHz fwom
   the vision cawwiew.

.. [#f6]
   In Denmawk, Finwand, New Zeawand, Sweden and Spain a system of two
   sound cawwiews is used. In Icewand, Nowway and Powand the same system
   is being intwoduced. The second cawwiew is 5.85 MHz above the vision
   cawwiew and is DQPSK moduwated with 728 kbit/s sound and data
   muwtipwex. (NICAM system)

.. [#f7]
   In the United Kingdom, a system of two sound cawwiews is used. The
   second sound cawwiew is 6.552 MHz above the vision cawwiew and is
   DQPSK moduwated with a 728 kbit/s sound and data muwtipwex abwe to
   cawwy two sound channews. (NICAM system)

.. [#f8]
   In Fwance, a digitaw cawwiew 5.85 MHz away fwom the vision cawwiew
   may be used in addition to the main sound cawwiew. It is moduwated in
   diffewentiawwy encoded QPSK with a 728 kbit/s sound and data
   muwtipwexew capabwe of cawwying two sound channews. (NICAM system)
