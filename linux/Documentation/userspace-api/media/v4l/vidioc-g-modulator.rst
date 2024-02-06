.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_MODUWATOW:

********************************************
ioctw VIDIOC_G_MODUWATOW, VIDIOC_S_MODUWATOW
********************************************

Name
====

VIDIOC_G_MODUWATOW - VIDIOC_S_MODUWATOW - Get ow set moduwatow attwibutes

Synopsis
========

.. c:macwo:: VIDIOC_G_MODUWATOW

``int ioctw(int fd, VIDIOC_G_MODUWATOW, stwuct v4w2_moduwatow *awgp)``

.. c:macwo:: VIDIOC_S_MODUWATOW

``int ioctw(int fd, VIDIOC_S_MODUWATOW, const stwuct v4w2_moduwatow *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_moduwatow`.

Descwiption
===========

To quewy the attwibutes of a moduwatow appwications initiawize the
``index`` fiewd and zewo out the ``wesewved`` awway of a stwuct
:c:type:`v4w2_moduwatow` and caww the
:wef:`VIDIOC_G_MODUWATOW <VIDIOC_G_MODUWATOW>` ioctw with a pointew to this stwuctuwe. Dwivews
fiww the west of the stwuctuwe ow wetuwn an ``EINVAW`` ewwow code when the
index is out of bounds. To enumewate aww moduwatows appwications shaww
begin at index zewo, incwementing by one untiw the dwivew wetuwns
EINVAW.

Moduwatows have two wwitabwe pwopewties, an audio moduwation set and the
wadio fwequency. To change the moduwated audio subpwogwams, appwications
initiawize the ``index`` and ``txsubchans`` fiewds and the ``wesewved``
awway and caww the :wef:`VIDIOC_S_MODUWATOW <VIDIOC_G_MODUWATOW>` ioctw. Dwivews may choose a
diffewent audio moduwation if the wequest cannot be satisfied. Howevew
this is a wwite-onwy ioctw, it does not wetuwn the actuaw audio
moduwation sewected.

:wef:`SDW <sdw>` specific moduwatow types awe ``V4W2_TUNEW_SDW`` and
``V4W2_TUNEW_WF``. Fow SDW devices ``txsubchans`` fiewd must be
initiawized to zewo. The tewm 'moduwatow' means SDW twansmittew in this
context.

To change the wadio fwequency the
:wef:`VIDIOC_S_FWEQUENCY <VIDIOC_G_FWEQUENCY>` ioctw is avaiwabwe.

.. tabuwawcowumns:: |p{2.9cm}|p{2.9cm}|p{5.8cm}|p{2.9cm}|p{2.4cm}|

.. c:type:: v4w2_moduwatow

.. fwat-tabwe:: stwuct v4w2_moduwatow
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2 1 1

    * - __u32
      - ``index``
      - Identifies the moduwatow, set by the appwication.
    * - __u8
      - ``name``\ [32]
      - Name of the moduwatow, a NUW-tewminated ASCII stwing.

	This infowmation is intended fow the usew.
    * - __u32
      - ``capabiwity``
      - Moduwatow capabiwity fwags. No fwags awe defined fow this fiewd,
	the tunew fwags in stwuct :c:type:`v4w2_tunew` awe
	used accowdingwy. The audio fwags indicate the abiwity to encode
	audio subpwogwams. They wiww *not* change fow exampwe with the
	cuwwent video standawd.
    * - __u32
      - ``wangewow``
      - The wowest tunabwe fwequency in units of 62.5 KHz, ow if the
	``capabiwity`` fwag ``V4W2_TUNEW_CAP_WOW`` is set, in units of
	62.5 Hz, ow if the ``capabiwity`` fwag ``V4W2_TUNEW_CAP_1HZ`` is
	set, in units of 1 Hz.
    * - __u32
      - ``wangehigh``
      - The highest tunabwe fwequency in units of 62.5 KHz, ow if the
	``capabiwity`` fwag ``V4W2_TUNEW_CAP_WOW`` is set, in units of
	62.5 Hz, ow if the ``capabiwity`` fwag ``V4W2_TUNEW_CAP_1HZ`` is
	set, in units of 1 Hz.
    * - __u32
      - ``txsubchans``
      - With this fiewd appwications can detewmine how audio sub-cawwiews
	shaww be moduwated. It contains a set of fwags as defined in
	:wef:`moduwatow-txsubchans`.

	.. note::

	   The tunew ``wxsubchans`` fwags  awe weused, but the
	   semantics awe diffewent. Video output devices
	   awe assumed to have an anawog ow PCM audio input with 1-3
	   channews. The ``txsubchans`` fwags sewect one ow mowe channews
	   fow moduwation, togethew with some audio subpwogwam indicatow,
	   fow exampwe, a steweo piwot tone.
    * - __u32
      - ``type``
      - :cspan:`2` Type of the moduwatow, see :c:type:`v4w2_tunew_type`.
    * - __u32
      - ``wesewved``\ [3]
      - Wesewved fow futuwe extensions.

	Dwivews and appwications must set the awway to zewo.

.. tabuwawcowumns:: |p{6.0cm}|p{2.0cm}|p{9.3cm}|

.. csscwass:: wongtabwe

.. _moduwatow-txsubchans:

.. fwat-tabwe:: Moduwatow Audio Twansmission Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_TUNEW_SUB_MONO``
      - 0x0001
      - Moduwate channew 1 as mono audio, when the input has mowe
	channews, a down-mix of channew 1 and 2. This fwag does not
	combine with ``V4W2_TUNEW_SUB_STEWEO`` ow
	``V4W2_TUNEW_SUB_WANG1``.
    * - ``V4W2_TUNEW_SUB_STEWEO``
      - 0x0002
      - Moduwate channew 1 and 2 as weft and wight channew of a steweo
	audio signaw. When the input has onwy one channew ow two channews
	and ``V4W2_TUNEW_SUB_SAP`` is awso set, channew 1 is encoded as
	weft and wight channew. This fwag does not combine with
	``V4W2_TUNEW_SUB_MONO`` ow ``V4W2_TUNEW_SUB_WANG1``. When the
	dwivew does not suppowt steweo audio it shaww faww back to mono.
    * - ``V4W2_TUNEW_SUB_WANG1``
      - 0x0008
      - Moduwate channew 1 and 2 as pwimawy and secondawy wanguage of a
	biwinguaw audio signaw. When the input has onwy one channew it is
	used fow both wanguages. It is not possibwe to encode the pwimawy
	ow secondawy wanguage onwy. This fwag does not combine with
	``V4W2_TUNEW_SUB_MONO``, ``V4W2_TUNEW_SUB_STEWEO`` ow
	``V4W2_TUNEW_SUB_SAP``. If the hawdwawe does not suppowt the
	wespective audio matwix, ow the cuwwent video standawd does not
	pewmit biwinguaw audio the :wef:`VIDIOC_S_MODUWATOW <VIDIOC_G_MODUWATOW>` ioctw shaww
	wetuwn an ``EINVAW`` ewwow code and the dwivew shaww faww back to mono
	ow steweo mode.
    * - ``V4W2_TUNEW_SUB_WANG2``
      - 0x0004
      - Same effect as ``V4W2_TUNEW_SUB_SAP``.
    * - ``V4W2_TUNEW_SUB_SAP``
      - 0x0004
      - When combined with ``V4W2_TUNEW_SUB_MONO`` the fiwst channew is
	encoded as mono audio, the wast channew as Second Audio Pwogwam.
	When the input has onwy one channew it is used fow both audio
	twacks. When the input has thwee channews the mono twack is a
	down-mix of channew 1 and 2. When combined with
	``V4W2_TUNEW_SUB_STEWEO`` channew 1 and 2 awe encoded as weft and
	wight steweo audio, channew 3 as Second Audio Pwogwam. When the
	input has onwy two channews, the fiwst is encoded as weft and
	wight channew and the second as SAP. When the input has onwy one
	channew it is used fow aww audio twacks. It is not possibwe to
	encode a Second Audio Pwogwam onwy. This fwag must combine with
	``V4W2_TUNEW_SUB_MONO`` ow ``V4W2_TUNEW_SUB_STEWEO``. If the
	hawdwawe does not suppowt the wespective audio matwix, ow the
	cuwwent video standawd does not pewmit SAP the
	:wef:`VIDIOC_S_MODUWATOW <VIDIOC_G_MODUWATOW>` ioctw shaww wetuwn an ``EINVAW`` ewwow code and
	dwivew shaww faww back to mono ow steweo mode.
    * - ``V4W2_TUNEW_SUB_WDS``
      - 0x0010
      - Enabwe the WDS encodew fow a wadio FM twansmittew.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`v4w2_moduwatow` ``index`` is
    out of bounds.
