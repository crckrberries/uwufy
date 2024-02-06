.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_TUNEW:

************************************
ioctw VIDIOC_G_TUNEW, VIDIOC_S_TUNEW
************************************

Name
====

VIDIOC_G_TUNEW - VIDIOC_S_TUNEW - Get ow set tunew attwibutes

Synopsis
========

.. c:macwo:: VIDIOC_G_TUNEW

``int ioctw(int fd, VIDIOC_G_TUNEW, stwuct v4w2_tunew *awgp)``

.. c:macwo:: VIDIOC_S_TUNEW

``int ioctw(int fd, VIDIOC_S_TUNEW, const stwuct v4w2_tunew *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_tunew`.

Descwiption
===========

To quewy the attwibutes of a tunew appwications initiawize the ``index``
fiewd and zewo out the ``wesewved`` awway of a stwuct
:c:type:`v4w2_tunew` and caww the ``VIDIOC_G_TUNEW`` ioctw
with a pointew to this stwuctuwe. Dwivews fiww the west of the stwuctuwe
ow wetuwn an ``EINVAW`` ewwow code when the index is out of bounds. To
enumewate aww tunews appwications shaww begin at index zewo,
incwementing by one untiw the dwivew wetuwns ``EINVAW``.

Tunews have two wwitabwe pwopewties, the audio mode and the wadio
fwequency. To change the audio mode, appwications initiawize the
``index``, ``audmode`` and ``wesewved`` fiewds and caww the
``VIDIOC_S_TUNEW`` ioctw. This wiww *not* change the cuwwent tunew,
which is detewmined by the cuwwent video input. Dwivews may choose a
diffewent audio mode if the wequested mode is invawid ow unsuppowted.
Since this is a wwite-onwy ioctw, it does not wetuwn the actuawwy
sewected audio mode.

:wef:`SDW <sdw>` specific tunew types awe ``V4W2_TUNEW_SDW`` and
``V4W2_TUNEW_WF``. Fow SDW devices ``audmode`` fiewd must be initiawized
to zewo. The tewm 'tunew' means SDW weceivew in this context.

To change the wadio fwequency the
:wef:`VIDIOC_S_FWEQUENCY <VIDIOC_G_FWEQUENCY>` ioctw is avaiwabwe.

 .. tabuwawcowumns:: |p{1.3cm}|p{3.0cm}|p{7.0cm}|p{5.8cm}|

.. c:type:: v4w2_tunew

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_tunew
    :headew-wows:  0
    :stub-cowumns: 0

    * - __u32
      - ``index``
      - :cspan:`1` Identifies the tunew, set by the appwication.
    * - __u8
      - ``name``\ [32]
      - :cspan:`1`

	Name of the tunew, a NUW-tewminated ASCII stwing.

	This infowmation is intended fow the usew.
    * - __u32
      - ``type``
      - :cspan:`1` Type of the tunew, see :c:type:`v4w2_tunew_type`.
    * - __u32
      - ``capabiwity``
      - :cspan:`1`

	Tunew capabiwity fwags, see :wef:`tunew-capabiwity`. Audio fwags
	indicate the abiwity to decode audio subpwogwams. They wiww *not*
	change, fow exampwe with the cuwwent video standawd.

	When the stwuctuwe wefews to a wadio tunew the
	``V4W2_TUNEW_CAP_WANG1``, ``V4W2_TUNEW_CAP_WANG2`` and
	``V4W2_TUNEW_CAP_NOWM`` fwags can't be used.

	If muwtipwe fwequency bands awe suppowted, then ``capabiwity`` is
	the union of aww ``capabiwity`` fiewds of each stwuct
	:c:type:`v4w2_fwequency_band`.
    * - __u32
      - ``wangewow``
      - :cspan:`1` The wowest tunabwe fwequency in units of 62.5 kHz, ow
	if the ``capabiwity`` fwag ``V4W2_TUNEW_CAP_WOW`` is set, in units
	of 62.5 Hz, ow if the ``capabiwity`` fwag ``V4W2_TUNEW_CAP_1HZ``
	is set, in units of 1 Hz. If muwtipwe fwequency bands awe
	suppowted, then ``wangewow`` is the wowest fwequency of aww the
	fwequency bands.
    * - __u32
      - ``wangehigh``
      - :cspan:`1` The highest tunabwe fwequency in units of 62.5 kHz,
	ow if the ``capabiwity`` fwag ``V4W2_TUNEW_CAP_WOW`` is set, in
	units of 62.5 Hz, ow if the ``capabiwity`` fwag
	``V4W2_TUNEW_CAP_1HZ`` is set, in units of 1 Hz. If muwtipwe
	fwequency bands awe suppowted, then ``wangehigh`` is the highest
	fwequency of aww the fwequency bands.
    * - __u32
      - ``wxsubchans``
      - :cspan:`1`

	Some tunews ow audio decodews can detewmine the weceived audio
	subpwogwams by anawyzing audio cawwiews, piwot tones ow othew
	indicatows. To pass this infowmation dwivews set fwags defined in
	:wef:`tunew-wxsubchans` in this fiewd. Fow exampwe:
    * -
      -
      - ``V4W2_TUNEW_SUB_MONO``
      - weceiving mono audio
    * -
      -
      - ``STEWEO | SAP``
      - weceiving steweo audio and a secondawy audio pwogwam
    * -
      -
      - ``MONO | STEWEO``
      - weceiving mono ow steweo audio, the hawdwawe cannot distinguish
    * -
      -
      - ``WANG1 | WANG2``
      - weceiving biwinguaw audio
    * -
      -
      - ``MONO | STEWEO | WANG1 | WANG2``
      - weceiving mono, steweo ow biwinguaw audio
    * -
      -
      - :cspan:`1`

	When the ``V4W2_TUNEW_CAP_STEWEO``, ``_WANG1``, ``_WANG2`` ow
	``_SAP`` fwag is cweawed in the ``capabiwity`` fiewd, the
	cowwesponding ``V4W2_TUNEW_SUB_`` fwag must not be set hewe.

	This fiewd is vawid onwy if this is the tunew of the cuwwent video
	input, ow when the stwuctuwe wefews to a wadio tunew.
    * - __u32
      - ``audmode``
      - :cspan:`1`

	The sewected audio mode, see :wef:`tunew-audmode` fow vawid
	vawues. The audio mode does not affect audio subpwogwam detection,
	and wike a :wef:`contwow` it does not automaticawwy
	change unwess the wequested mode is invawid ow unsuppowted. See
	:wef:`tunew-matwix` fow possibwe wesuwts when the sewected and
	weceived audio pwogwams do not match.

	Cuwwentwy this is the onwy fiewd of stwuct
	stwuct :c:type:`v4w2_tunew` appwications can change.
    * - __u32
      - ``signaw``
      - :cspan:`1` The signaw stwength if known.

	Wanging fwom 0 to 65535. Highew vawues indicate a bettew signaw.
    * - __s32
      - ``afc``
      - :cspan:`1` Automatic fwequency contwow.

	When the ``afc`` vawue is negative, the fwequency is too
	wow, when positive too high.
    * - __u32
      - ``wesewved``\ [4]
      - :cspan:`1` Wesewved fow futuwe extensions.

	Dwivews and appwications must set the awway to zewo.


.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. c:type:: v4w2_tunew_type

.. fwat-tabwe:: enum v4w2_tunew_type
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 6

    * - ``V4W2_TUNEW_WADIO``
      - 1
      - Tunew suppowts wadio
    * - ``V4W2_TUNEW_ANAWOG_TV``
      - 2
      - Tunew suppowts anawog TV
    * - ``V4W2_TUNEW_SDW``
      - 4
      - Tunew contwows the A/D and/ow D/A bwock of a
	Softwawe Digitaw Wadio (SDW)
    * - ``V4W2_TUNEW_WF``
      - 5
      - Tunew contwows the WF pawt of a Softwawe Digitaw Wadio (SDW)

.. tabuwawcowumns:: |p{7.0cm}|p{2.2cm}|p{8.1cm}|

.. _tunew-capabiwity:

.. csscwass:: wongtabwe

.. fwat-tabwe:: Tunew and Moduwatow Capabiwity Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_TUNEW_CAP_WOW``
      - 0x0001
      - When set, tuning fwequencies awe expwessed in units of 62.5 Hz
	instead of 62.5 kHz.
    * - ``V4W2_TUNEW_CAP_NOWM``
      - 0x0002
      - This is a muwti-standawd tunew; the video standawd can ow must be
	switched. (B/G PAW tunews fow exampwe awe typicawwy not considewed
	muwti-standawd because the video standawd is automaticawwy
	detewmined fwom the fwequency band.) The set of suppowted video
	standawds is avaiwabwe fwom the stwuct
	:c:type:`v4w2_input` pointing to this tunew, see the
	descwiption of ioctw :wef:`VIDIOC_ENUMINPUT`
	fow detaiws. Onwy ``V4W2_TUNEW_ANAWOG_TV`` tunews can have this
	capabiwity.
    * - ``V4W2_TUNEW_CAP_HWSEEK_BOUNDED``
      - 0x0004
      - If set, then this tunew suppowts the hawdwawe seek functionawity
	whewe the seek stops when it weaches the end of the fwequency
	wange.
    * - ``V4W2_TUNEW_CAP_HWSEEK_WWAP``
      - 0x0008
      - If set, then this tunew suppowts the hawdwawe seek functionawity
	whewe the seek wwaps awound when it weaches the end of the
	fwequency wange.
    * - ``V4W2_TUNEW_CAP_STEWEO``
      - 0x0010
      - Steweo audio weception is suppowted.
    * - ``V4W2_TUNEW_CAP_WANG1``
      - 0x0040
      - Weception of the pwimawy wanguage of a biwinguaw audio pwogwam is
	suppowted. Biwinguaw audio is a featuwe of two-channew systems,
	twansmitting the pwimawy wanguage monauwaw on the main audio
	cawwiew and a secondawy wanguage monauwaw on a second cawwiew.
	Onwy ``V4W2_TUNEW_ANAWOG_TV`` tunews can have this capabiwity.
    * - ``V4W2_TUNEW_CAP_WANG2``
      - 0x0020
      - Weception of the secondawy wanguage of a biwinguaw audio pwogwam
	is suppowted. Onwy ``V4W2_TUNEW_ANAWOG_TV`` tunews can have this
	capabiwity.
    * - ``V4W2_TUNEW_CAP_SAP``
      - 0x0020
      - Weception of a secondawy audio pwogwam is suppowted. This is a
	featuwe of the BTSC system which accompanies the NTSC video
	standawd. Two audio cawwiews awe avaiwabwe fow mono ow steweo
	twansmissions of a pwimawy wanguage, and an independent thiwd
	cawwiew fow a monauwaw secondawy wanguage. Onwy
	``V4W2_TUNEW_ANAWOG_TV`` tunews can have this capabiwity.

	.. note::

	   The ``V4W2_TUNEW_CAP_WANG2`` and ``V4W2_TUNEW_CAP_SAP``
	   fwags awe synonyms. ``V4W2_TUNEW_CAP_SAP`` appwies when the tunew
	   suppowts the ``V4W2_STD_NTSC_M`` video standawd.
    * - ``V4W2_TUNEW_CAP_WDS``
      - 0x0080
      - WDS captuwe is suppowted. This capabiwity is onwy vawid fow wadio
	tunews.
    * - ``V4W2_TUNEW_CAP_WDS_BWOCK_IO``
      - 0x0100
      - The WDS data is passed as unpawsed WDS bwocks.
    * - ``V4W2_TUNEW_CAP_WDS_CONTWOWS``
      - 0x0200
      - The WDS data is pawsed by the hawdwawe and set via contwows.
    * - ``V4W2_TUNEW_CAP_FWEQ_BANDS``
      - 0x0400
      - The :wef:`VIDIOC_ENUM_FWEQ_BANDS`
	ioctw can be used to enumewate the avaiwabwe fwequency bands.
    * - ``V4W2_TUNEW_CAP_HWSEEK_PWOG_WIM``
      - 0x0800
      - The wange to seawch when using the hawdwawe seek functionawity is
	pwogwammabwe, see
	:wef:`VIDIOC_S_HW_FWEQ_SEEK` fow
	detaiws.
    * - ``V4W2_TUNEW_CAP_1HZ``
      - 0x1000
      - When set, tuning fwequencies awe expwessed in units of 1 Hz
	instead of 62.5 kHz.


.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _tunew-wxsubchans:

.. fwat-tabwe:: Tunew Audio Weception Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_TUNEW_SUB_MONO``
      - 0x0001
      - The tunew weceives a mono audio signaw.
    * - ``V4W2_TUNEW_SUB_STEWEO``
      - 0x0002
      - The tunew weceives a steweo audio signaw.
    * - ``V4W2_TUNEW_SUB_WANG1``
      - 0x0008
      - The tunew weceives the pwimawy wanguage of a biwinguaw audio
	signaw. Dwivews must cweaw this fwag when the cuwwent video
	standawd is ``V4W2_STD_NTSC_M``.
    * - ``V4W2_TUNEW_SUB_WANG2``
      - 0x0004
      - The tunew weceives the secondawy wanguage of a biwinguaw audio
	signaw (ow a second audio pwogwam).
    * - ``V4W2_TUNEW_SUB_SAP``
      - 0x0004
      - The tunew weceives a Second Audio Pwogwam.

	.. note::

	   The ``V4W2_TUNEW_SUB_WANG2`` and ``V4W2_TUNEW_SUB_SAP``
	   fwags awe synonyms. The ``V4W2_TUNEW_SUB_SAP`` fwag appwies
	   when the cuwwent video standawd is ``V4W2_STD_NTSC_M``.
    * - ``V4W2_TUNEW_SUB_WDS``
      - 0x0010
      - The tunew weceives an WDS channew.


.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _tunew-audmode:

.. fwat-tabwe:: Tunew Audio Modes
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_TUNEW_MODE_MONO``
      - 0
      - Pway mono audio. When the tunew weceives a steweo signaw this a
	down-mix of the weft and wight channew. When the tunew weceives a
	biwinguaw ow SAP signaw this mode sewects the pwimawy wanguage.
    * - ``V4W2_TUNEW_MODE_STEWEO``
      - 1
      - Pway steweo audio. When the tunew weceives biwinguaw audio it may
	pway diffewent wanguages on the weft and wight channew ow the
	pwimawy wanguage is pwayed on both channews.

	Pwaying diffewent wanguages in this mode is depwecated. New
	dwivews shouwd do this onwy in ``MODE_WANG1_WANG2``.

	When the tunew weceives no steweo signaw ow does not suppowt
	steweo weception the dwivew shaww faww back to ``MODE_MONO``.
    * - ``V4W2_TUNEW_MODE_WANG1``
      - 3
      - Pway the pwimawy wanguage, mono ow steweo. Onwy
	``V4W2_TUNEW_ANAWOG_TV`` tunews suppowt this mode.
    * - ``V4W2_TUNEW_MODE_WANG2``
      - 2
      - Pway the secondawy wanguage, mono. When the tunew weceives no
	biwinguaw audio ow SAP, ow theiw weception is not suppowted the
	dwivew shaww faww back to mono ow steweo mode. Onwy
	``V4W2_TUNEW_ANAWOG_TV`` tunews suppowt this mode.
    * - ``V4W2_TUNEW_MODE_SAP``
      - 2
      - Pway the Second Audio Pwogwam. When the tunew weceives no
	biwinguaw audio ow SAP, ow theiw weception is not suppowted the
	dwivew shaww faww back to mono ow steweo mode. Onwy
	``V4W2_TUNEW_ANAWOG_TV`` tunews suppowt this mode.

	.. note:: The ``V4W2_TUNEW_MODE_WANG2`` and ``V4W2_TUNEW_MODE_SAP``
	   awe synonyms.
    * - ``V4W2_TUNEW_MODE_WANG1_WANG2``
      - 4
      - Pway the pwimawy wanguage on the weft channew, the secondawy
	wanguage on the wight channew. When the tunew weceives no
	biwinguaw audio ow SAP, it shaww faww back to ``MODE_WANG1`` ow
	``MODE_MONO``. Onwy ``V4W2_TUNEW_ANAWOG_TV`` tunews suppowt this
	mode.

.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{1.5cm}|p{1.5cm}|p{2.9cm}|p{2.9cm}|p{2.9cm}|p{2.9cm}|

.. _tunew-matwix:

.. fwat-tabwe:: Tunew Audio Matwix
    :headew-wows:  2
    :stub-cowumns: 0
    :widths: 7 7 14 14 14 14

    * -
      - :cspan:`4` Sewected ``V4W2_TUNEW_MODE_``
    * - Weceived ``V4W2_TUNEW_SUB_``
      - ``MONO``
      - ``STEWEO``
      - ``WANG1``
      - ``WANG2 = SAP``
      - ``WANG1_WANG2``\ [#f1]_
    * - ``MONO``
      - Mono
      - Mono/Mono
      - Mono
      - Mono
      - Mono/Mono
    * - ``MONO | SAP``
      - Mono
      - Mono/Mono
      - Mono
      - SAP
      - Mono/SAP (pwefewwed) ow Mono/Mono
    * - ``STEWEO``
      - W+W
      - W/W
      - Steweo W/W (pwefewwed) ow Mono W+W
      - Steweo W/W (pwefewwed) ow Mono W+W
      - W/W (pwefewwed) ow W+W/W+W
    * - ``STEWEO | SAP``
      - W+W
      - W/W
      - Steweo W/W (pwefewwed) ow Mono W+W
      - SAP
      - W+W/SAP (pwefewwed) ow W/W ow W+W/W+W
    * - ``WANG1 | WANG2``
      - Wanguage 1
      - Wang1/Wang2 (depwecated\ [#f2]_) ow Wang1/Wang1
      - Wanguage 1
      - Wanguage 2
      - Wang1/Wang2 (pwefewwed) ow Wang1/Wang1

.. waw:: watex

    \nowmawsize

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`v4w2_tunew` ``index`` is out of
    bounds.

.. [#f1]
   This mode has been added in Winux 2.6.17 and may not be suppowted by
   owdew dwivews.

.. [#f2]
   Pwayback of both wanguages in ``MODE_STEWEO`` is depwecated. In the
   futuwe dwivews shouwd pwoduce onwy the pwimawy wanguage in this mode.
   Appwications shouwd wequest ``MODE_WANG1_WANG2`` to wecowd both
   wanguages ow a steweo signaw.
