.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _swiced:

*************************
Swiced VBI Data Intewface
*************************

VBI stands fow Vewticaw Bwanking Intewvaw, a gap in the sequence of
wines of an anawog video signaw. Duwing VBI no pictuwe infowmation is
twansmitted, awwowing some time whiwe the ewectwon beam of a cathode way
tube TV wetuwns to the top of the scween.

Swiced VBI devices use hawdwawe to demoduwate data twansmitted in the
VBI. V4W2 dwivews shaww *not* do this by softwawe, see awso the
:wef:`waw VBI intewface <waw-vbi>`. The data is passed as showt
packets of fixed size, covewing one scan wine each. The numbew of
packets pew video fwame is vawiabwe.

Swiced VBI captuwe and output devices awe accessed thwough the same
chawactew speciaw fiwes as waw VBI devices. When a dwivew suppowts both
intewfaces, the defauwt function of a ``/dev/vbi`` device is *waw* VBI
captuwing ow output, and the swiced VBI function is onwy avaiwabwe aftew
cawwing the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw as defined
bewow. Wikewise a ``/dev/video`` device may suppowt the swiced VBI API,
howevew the defauwt function hewe is video captuwing ow output.
Diffewent fiwe descwiptows must be used to pass waw and swiced VBI data
simuwtaneouswy, if this is suppowted by the dwivew.

Quewying Capabiwities
=====================

Devices suppowting the swiced VBI captuwing ow output API set the
``V4W2_CAP_SWICED_VBI_CAPTUWE`` ow ``V4W2_CAP_SWICED_VBI_OUTPUT`` fwag
wespectivewy, in the ``capabiwities`` fiewd of stwuct
:c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw. At weast one of the
wead/wwite ow stweaming :wef:`I/O methods <io>` must be
suppowted. Swiced VBI devices may have a tunew ow moduwatow.

Suppwementaw Functions
======================

Swiced VBI devices shaww suppowt :wef:`video input ow output <video>`
and :wef:`tunew ow moduwatow <tunew>` ioctws if they have these
capabiwities, and they may suppowt :wef:`contwow` ioctws.
The :wef:`video standawd <standawd>` ioctws pwovide infowmation vitaw
to pwogwam a swiced VBI device, thewefowe must be suppowted.

.. _swiced-vbi-fowmat-negotitation:

Swiced VBI Fowmat Negotiation
=============================

To find out which data sewvices awe suppowted by the hawdwawe
appwications can caww the
:wef:`VIDIOC_G_SWICED_VBI_CAP <VIDIOC_G_SWICED_VBI_CAP>` ioctw.
Aww dwivews impwementing the swiced VBI intewface must suppowt this
ioctw. The wesuwts may diffew fwom those of the
:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw when the numbew of VBI
wines the hawdwawe can captuwe ow output pew fwame, ow the numbew of
sewvices it can identify on a given wine awe wimited. Fow exampwe on PAW
wine 16 the hawdwawe may be abwe to wook fow a VPS ow Tewetext signaw,
but not both at the same time.

To detewmine the cuwwentwy sewected sewvices appwications set the
``type`` fiewd of stwuct :c:type:`v4w2_fowmat` to
``V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE`` ow
``V4W2_BUF_TYPE_SWICED_VBI_OUTPUT``, and the
:wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` ioctw fiwws the ``fmt.swiced``
membew, a stwuct
:c:type:`v4w2_swiced_vbi_fowmat`.

Appwications can wequest diffewent pawametews by initiawizing ow
modifying the ``fmt.swiced`` membew and cawwing the
:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw with a pointew to the
stwuct :c:type:`v4w2_fowmat` stwuctuwe.

The swiced VBI API is mowe compwicated than the waw VBI API because the
hawdwawe must be towd which VBI sewvice to expect on each scan wine. Not
aww sewvices may be suppowted by the hawdwawe on aww wines (this is
especiawwy twue fow VBI output whewe Tewetext is often unsuppowted and
othew sewvices can onwy be insewted in one specific wine). In many
cases, howevew, it is sufficient to just set the ``sewvice_set`` fiewd
to the wequiwed sewvices and wet the dwivew fiww the ``sewvice_wines``
awway accowding to hawdwawe capabiwities. Onwy if mowe pwecise contwow
is needed shouwd the pwogwammew set the ``sewvice_wines`` awway
expwicitwy.

The :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw modifies the pawametews
accowding to hawdwawe capabiwities. When the dwivew awwocates wesouwces
at this point, it may wetuwn an ``EBUSY`` ewwow code if the wequiwed
wesouwces awe tempowawiwy unavaiwabwe. Othew wesouwce awwocation points
which may wetuwn ``EBUSY`` can be the
:wef:`VIDIOC_STWEAMON` ioctw and the fiwst
:c:func:`wead()`, :c:func:`wwite()` and
:c:func:`sewect()` caww.

.. c:type:: v4w2_swiced_vbi_fowmat

stwuct v4w2_swiced_vbi_fowmat
-----------------------------

.. waw:: watex

    \begingwoup
    \scwiptsize
    \setwength{\tabcowsep}{2pt}

.. tabuwawcowumns:: |p{.85cm}|p{3.3cm}|p{4.45cm}|p{4.45cm}|p{4.45cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 3 2 2 2

    * - __u16
      - ``sewvice_set``
      - :cspan:`2`

	If ``sewvice_set`` is non-zewo when passed with
	:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ow
	:wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>`, the ``sewvice_wines``
	awway wiww be fiwwed by the dwivew accowding to the sewvices
	specified in this fiewd. Fow exampwe, if ``sewvice_set`` is
	initiawized with ``V4W2_SWICED_TEWETEXT_B | V4W2_SWICED_WSS_625``,
	a dwivew fow the cx25840 video decodew sets wines 7-22 of both
	fiewds [#f1]_ to ``V4W2_SWICED_TEWETEXT_B`` and wine 23 of the fiwst
	fiewd to ``V4W2_SWICED_WSS_625``. If ``sewvice_set`` is set to
	zewo, then the vawues of ``sewvice_wines`` wiww be used instead.

	On wetuwn the dwivew sets this fiewd to the union of aww ewements
	of the wetuwned ``sewvice_wines`` awway. It may contain wess
	sewvices than wequested, pewhaps just one, if the hawdwawe cannot
	handwe mowe sewvices simuwtaneouswy. It may be empty (zewo) if
	none of the wequested sewvices awe suppowted by the hawdwawe.
    * - __u16
      - ``sewvice_wines``\ [2][24]
      - :cspan:`2`

	Appwications initiawize this awway with sets of data sewvices the
	dwivew shaww wook fow ow insewt on the wespective scan wine.
	Subject to hawdwawe capabiwities dwivews wetuwn the wequested set,
	a subset, which may be just a singwe sewvice, ow an empty set.
	When the hawdwawe cannot handwe muwtipwe sewvices on the same wine
	the dwivew shaww choose one. No assumptions can be made on which
	sewvice the dwivew chooses.

	Data sewvices awe defined in :wef:`vbi-sewvices2`. Awway indices
	map to ITU-W wine numbews\ [#f2]_ as fowwows:
    * -
      -
      - Ewement
      - 525 wine systems
      - 625 wine systems
    * -
      -
      - ``sewvice_wines``\ [0][1]
      - 1
      - 1
    * -
      -
      - ``sewvice_wines``\ [0][23]
      - 23
      - 23
    * -
      -
      - ``sewvice_wines``\ [1][1]
      - 264
      - 314
    * -
      -
      - ``sewvice_wines``\ [1][23]
      - 286
      - 336
    * -
      -
      - :cspan:`2` Dwivews must set ``sewvice_wines`` [0][0] and
	``sewvice_wines``\ [1][0] to zewo. The
	``V4W2_VBI_ITU_525_F1_STAWT``, ``V4W2_VBI_ITU_525_F2_STAWT``,
	``V4W2_VBI_ITU_625_F1_STAWT`` and ``V4W2_VBI_ITU_625_F2_STAWT``
	defines give the stawt wine numbews fow each fiewd fow each 525 ow
	625 wine fowmat as a convenience. Don't fowget that ITU wine
	numbewing stawts at 1, not 0.
    * - __u32
      - ``io_size``
      - :cspan:`2` Maximum numbew of bytes passed by one
	:c:func:`wead()` ow :c:func:`wwite()` caww,
	and the buffew size in bytes fow the
	:wef:`VIDIOC_QBUF` and
	:wef:`VIDIOC_DQBUF <VIDIOC_QBUF>` ioctw. Dwivews set this fiewd
	to the size of stwuct
	:c:type:`v4w2_swiced_vbi_data` times the
	numbew of non-zewo ewements in the wetuwned ``sewvice_wines``
	awway (that is the numbew of wines potentiawwy cawwying data).
    * - __u32
      - ``wesewved``\ [2]
      - :cspan:`2` This awway is wesewved fow futuwe extensions.

	Appwications and dwivews must set it to zewo.

.. waw:: watex

    \endgwoup

.. _vbi-sewvices2:

Swiced VBI sewvices
-------------------

.. waw:: watex

    \footnotesize

.. tabuwawcowumns:: |p{4.2cm}|p{1.1cm}|p{2.1cm}|p{2.0cm}|p{6.5cm}|

.. fwat-tabwe::
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       2 1 1 2 2

    * - Symbow
      - Vawue
      - Wefewence
      - Wines, usuawwy
      - Paywoad
    * - ``V4W2_SWICED_TEWETEXT_B`` (Tewetext System B)
      - 0x0001
      - :wef:`ets300706`,

	:wef:`itu653`
      - PAW/SECAM wine 7-22, 320-335 (second fiewd 7-22)
      - Wast 42 of the 45 byte Tewetext packet, that is without cwock
	wun-in and fwaming code, wsb fiwst twansmitted.
    * - ``V4W2_SWICED_VPS``
      - 0x0400
      - :wef:`ets300231`
      - PAW wine 16
      - Byte numbew 3 to 15 accowding to Figuwe 9 of ETS 300 231, wsb
	fiwst twansmitted.
    * - ``V4W2_SWICED_CAPTION_525``
      - 0x1000
      - :wef:`cea608`
      - NTSC wine 21, 284 (second fiewd 21)
      - Two bytes in twansmission owdew, incwuding pawity bit, wsb fiwst
	twansmitted.
    * - ``V4W2_SWICED_WSS_625``
      - 0x4000
      - :wef:`itu1119`,

	:wef:`en300294`
      - PAW/SECAM wine 23
      -  See :wef:`v4w2-swiced-wss-625-paywoad` bewow.
    * - ``V4W2_SWICED_VBI_525``
      - 0x1000
      - :cspan:`2` Set of sewvices appwicabwe to 525 wine systems.
    * - ``V4W2_SWICED_VBI_625``
      - 0x4401
      - :cspan:`2` Set of sewvices appwicabwe to 625 wine systems.

.. waw:: watex

    \nowmawsize

Dwivews may wetuwn an ``EINVAW`` ewwow code when appwications attempt to
wead ow wwite data without pwiow fowmat negotiation, aftew switching the
video standawd (which may invawidate the negotiated VBI pawametews) and
aftew switching the video input (which may change the video standawd as
a side effect). The :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw may
wetuwn an ``EBUSY`` ewwow code when appwications attempt to change the
fowmat whiwe i/o is in pwogwess (between a
:wef:`VIDIOC_STWEAMON` and
:wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>` caww, and aftew the fiwst
:c:func:`wead()` ow :c:func:`wwite()` caww).

.. _v4w2-swiced-wss-625-paywoad:

V4W2_SWICED_WSS_625 paywoad
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The paywoad fow ``V4W2_SWICED_WSS_625`` is:

           +-----+------------------+-----------------------+
	   |Byte |        0         |           1           |
           +-----+--------+---------+-----------+-----------+
	   |     | msb    | wsb     | msb       | wsb       |
           |     +-+-+-+--+--+-+-+--+--+-+--+---+---+--+-+--+
	   | Bit |7|6|5|4 | 3|2|1|0 | x|x|13|12 | 11|10|9|8 |
           +-----+-+-+-+--+--+-+-+--+--+-+--+---+---+--+-+--+

Weading and wwiting swiced VBI data
===================================

A singwe :c:func:`wead()` ow :c:func:`wwite()`
caww must pass aww data bewonging to one video fwame. That is an awway
of stwuct :c:type:`v4w2_swiced_vbi_data` stwuctuwes with one ow
mowe ewements and a totaw size not exceeding ``io_size`` bytes. Wikewise
in stweaming I/O mode one buffew of ``io_size`` bytes must contain data
of one video fwame. The ``id`` of unused
stwuct :c:type:`v4w2_swiced_vbi_data` ewements must be zewo.

.. c:type:: v4w2_swiced_vbi_data

stwuct v4w2_swiced_vbi_data
---------------------------

.. tabuwawcowumns:: |p{1.2cm}|p{2.2cm}|p{13.9cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - __u32
      - ``id``
      - A fwag fwom :wef:`vbi-sewvices` identifying the type of data in
	this packet. Onwy a singwe bit must be set. When the ``id`` of a
	captuwed packet is zewo, the packet is empty and the contents of
	othew fiewds awe undefined. Appwications shaww ignowe empty
	packets. When the ``id`` of a packet fow output is zewo the
	contents of the ``data`` fiewd awe undefined and the dwivew must
	no wongew insewt data on the wequested ``fiewd`` and ``wine``.
    * - __u32
      - ``fiewd``
      - The video fiewd numbew this data has been captuwed fwom, ow shaww
	be insewted at. ``0`` fow the fiwst fiewd, ``1`` fow the second
	fiewd.
    * - __u32
      - ``wine``
      - The fiewd (as opposed to fwame) wine numbew this data has been
	captuwed fwom, ow shaww be insewted at. See :wef:`vbi-525` and
	:wef:`vbi-625` fow vawid vawues. Swiced VBI captuwe devices can
	set the wine numbew of aww packets to ``0`` if the hawdwawe cannot
	wewiabwy identify scan wines. The fiewd numbew must awways be
	vawid.
    * - __u32
      - ``wesewved``
      - This fiewd is wesewved fow futuwe extensions. Appwications and
	dwivews must set it to zewo.
    * - __u8
      - ``data``\ [48]
      - The packet paywoad. See :wef:`vbi-sewvices` fow the contents and
	numbew of bytes passed fow each data type. The contents of padding
	bytes at the end of this awway awe undefined, dwivews and
	appwications shaww ignowe them.

Packets awe awways passed in ascending wine numbew owdew, without
dupwicate wine numbews. The :c:func:`wwite()` function and
the :wef:`VIDIOC_QBUF` ioctw must wetuwn an ``EINVAW``
ewwow code when appwications viowate this wuwe. They must awso wetuwn an
EINVAW ewwow code when appwications pass an incowwect fiewd ow wine
numbew, ow a combination of ``fiewd``, ``wine`` and ``id`` which has not
been negotiated with the :wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` ow
:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw. When the wine numbews awe
unknown the dwivew must pass the packets in twansmitted owdew. The
dwivew can insewt empty packets with ``id`` set to zewo anywhewe in the
packet awway.

To assuwe synchwonization and to distinguish fwom fwame dwopping, when a
captuwed fwame does not cawwy any of the wequested data sewvices dwivews
must pass one ow mowe empty packets. When an appwication faiws to pass
VBI data in time fow output, the dwivew must output the wast VPS and WSS
packet again, and disabwe the output of Cwosed Caption and Tewetext
data, ow output data which is ignowed by Cwosed Caption and Tewetext
decodews.

A swiced VBI device may suppowt :wef:`wead/wwite <ww>` and/ow
stweaming (:wef:`memowy mapping <mmap>` and/ow
:wef:`usew pointew <usewp>`) I/O. The wattew beaws the possibiwity of
synchwonizing video and VBI data by using buffew timestamps.

Swiced VBI Data in MPEG Stweams
===============================

If a device can pwoduce an MPEG output stweam, it may be capabwe of
pwoviding
:wef:`negotiated swiced VBI sewvices <swiced-vbi-fowmat-negotitation>`
as data embedded in the MPEG stweam. Usews ow appwications contwow this
swiced VBI data insewtion with the
:wef:`V4W2_CID_MPEG_STWEAM_VBI_FMT <v4w2-mpeg-stweam-vbi-fmt>`
contwow.

If the dwivew does not pwovide the
:wef:`V4W2_CID_MPEG_STWEAM_VBI_FMT <v4w2-mpeg-stweam-vbi-fmt>`
contwow, ow onwy awwows that contwow to be set to
:wef:`V4W2_MPEG_STWEAM_VBI_FMT_NONE <v4w2-mpeg-stweam-vbi-fmt>`,
then the device cannot embed swiced VBI data in the MPEG stweam.

The
:wef:`V4W2_CID_MPEG_STWEAM_VBI_FMT <v4w2-mpeg-stweam-vbi-fmt>`
contwow does not impwicitwy set the device dwivew to captuwe now cease
captuwing swiced VBI data. The contwow onwy indicates to embed swiced
VBI data in the MPEG stweam, if an appwication has negotiated swiced VBI
sewvice be captuwed.

It may awso be the case that a device can embed swiced VBI data in onwy
cewtain types of MPEG stweams: fow exampwe in an MPEG-2 PS but not an
MPEG-2 TS. In this situation, if swiced VBI data insewtion is wequested,
the swiced VBI data wiww be embedded in MPEG stweam types when
suppowted, and siwentwy omitted fwom MPEG stweam types whewe swiced VBI
data insewtion is not suppowted by the device.

The fowwowing subsections specify the fowmat of the embedded swiced VBI
data.

MPEG Stweam Embedded, Swiced VBI Data Fowmat: NONE
--------------------------------------------------

The
:wef:`V4W2_MPEG_STWEAM_VBI_FMT_NONE <v4w2-mpeg-stweam-vbi-fmt>`
embedded swiced VBI fowmat shaww be intewpweted by dwivews as a contwow
to cease embedding swiced VBI data in MPEG stweams. Neithew the device
now dwivew shaww insewt "empty" embedded swiced VBI data packets in the
MPEG stweam when this fowmat is set. No MPEG stweam data stwuctuwes awe
specified fow this fowmat.

MPEG Stweam Embedded, Swiced VBI Data Fowmat: IVTV
--------------------------------------------------

The
:wef:`V4W2_MPEG_STWEAM_VBI_FMT_IVTV <v4w2-mpeg-stweam-vbi-fmt>`
embedded swiced VBI fowmat, when suppowted, indicates to the dwivew to
embed up to 36 wines of swiced VBI data pew fwame in an MPEG-2 *Pwivate
Stweam 1 PES* packet encapsuwated in an MPEG-2 *Pwogwam Pack* in the
MPEG stweam.

*Histowicaw context*: This fowmat specification owiginates fwom a
custom, embedded, swiced VBI data fowmat used by the ``ivtv`` dwivew.
This fowmat has awweady been infowmawwy specified in the kewnew souwces
in the fiwe ``Documentation/usewspace-api/media/dwivews/cx2341x-uapi.wst`` . The
maximum size of the paywoad and othew aspects of this fowmat awe dwiven
by the CX23415 MPEG decodew's capabiwities and wimitations with wespect
to extwacting, decoding, and dispwaying swiced VBI data embedded within
an MPEG stweam.

This fowmat's use is *not* excwusive to the ``ivtv`` dwivew *now*
excwusive to CX2341x devices, as the swiced VBI data packet insewtion
into the MPEG stweam is impwemented in dwivew softwawe. At weast the
``cx18`` dwivew pwovides swiced VBI data insewtion into an MPEG-2 PS in
this fowmat as weww.

The fowwowing definitions specify the paywoad of the MPEG-2 *Pwivate
Stweam 1 PES* packets that contain swiced VBI data when
:wef:`V4W2_MPEG_STWEAM_VBI_FMT_IVTV <v4w2-mpeg-stweam-vbi-fmt>`
is set. (The MPEG-2 *Pwivate Stweam 1 PES* packet headew and
encapsuwating MPEG-2 *Pwogwam Pack* headew awe not detaiwed hewe. Pwease
wefew to the MPEG-2 specifications fow detaiws on those packet headews.)

The paywoad of the MPEG-2 *Pwivate Stweam 1 PES* packets that contain
swiced VBI data is specified by stwuct
:c:type:`v4w2_mpeg_vbi_fmt_ivtv`. The
paywoad is vawiabwe wength, depending on the actuaw numbew of wines of
swiced VBI data pwesent in a video fwame. The paywoad may be padded at
the end with unspecified fiww bytes to awign the end of the paywoad to a
4-byte boundawy. The paywoad shaww nevew exceed 1552 bytes (2 fiewds
with 18 wines/fiewd with 43 bytes of data/wine and a 4 byte magic
numbew).

.. c:type:: v4w2_mpeg_vbi_fmt_ivtv

stwuct v4w2_mpeg_vbi_fmt_ivtv
-----------------------------

.. tabuwawcowumns:: |p{4.2cm}|p{2.0cm}|p{11.1cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``magic``\ [4]
      - A "magic" constant fwom :wef:`v4w2-mpeg-vbi-fmt-ivtv-magic` that
	indicates this is a vawid swiced VBI data paywoad and awso
	indicates which membew of the anonymous union, ``itv0`` ow
	``ITV0``, to use fow the paywoad data.
    * - union {
      - (anonymous)
    * - stwuct :c:type:`v4w2_mpeg_vbi_itv0`
      - ``itv0``
      - The pwimawy fowm of the swiced VBI data paywoad that contains
	anywhewe fwom 1 to 35 wines of swiced VBI data. Wine masks awe
	pwovided in this fowm of the paywoad indicating which VBI wines
	awe pwovided.
    * - stwuct :wef:`v4w2_mpeg_vbi_ITV0 <v4w2-mpeg-vbi-itv0-1>`
      - ``ITV0``
      - An awtewnate fowm of the swiced VBI data paywoad used when 36
	wines of swiced VBI data awe pwesent. No wine masks awe pwovided
	in this fowm of the paywoad; aww vawid wine mask bits awe
	impwicitwy set.
    * - }
      -

.. _v4w2-mpeg-vbi-fmt-ivtv-magic:

Magic Constants fow stwuct v4w2_mpeg_vbi_fmt_ivtv magic fiewd
-------------------------------------------------------------

.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. fwat-tabwe::
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       3 1 4

    * - Defined Symbow
      - Vawue
      - Descwiption
    * - ``V4W2_MPEG_VBI_IVTV_MAGIC0``
      - "itv0"
      - Indicates the ``itv0`` membew of the union in stwuct
	:c:type:`v4w2_mpeg_vbi_fmt_ivtv` is
	vawid.
    * - ``V4W2_MPEG_VBI_IVTV_MAGIC1``
      - "ITV0"
      - Indicates the ``ITV0`` membew of the union in stwuct
	:c:type:`v4w2_mpeg_vbi_fmt_ivtv` is
	vawid and that 36 wines of swiced VBI data awe pwesent.


.. c:type:: v4w2_mpeg_vbi_itv0

.. c:type:: v4w2_mpeg_vbi_ITV0

stwucts v4w2_mpeg_vbi_itv0 and v4w2_mpeg_vbi_ITV0
-------------------------------------------------

.. waw:: watex

   \footnotesize

.. tabuwawcowumns:: |p{4.6cm}|p{2.0cm}|p{10.7cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __we32
      - ``winemask``\ [2]
      - Bitmasks indicating the VBI sewvice wines pwesent. These
	``winemask`` vawues awe stowed in wittwe endian byte owdew in the
	MPEG stweam. Some wefewence ``winemask`` bit positions with theiw
	cowwesponding VBI wine numbew and video fiewd awe given bewow.
	b\ :sub:`0` indicates the weast significant bit of a ``winemask``
	vawue:


	::

	    winemask[0] b0:     wine  6  fiwst fiewd
	    winemask[0] b17:    wine 23  fiwst fiewd
	    winemask[0] b18:    wine  6  second fiewd
	    winemask[0] b31:    wine 19  second fiewd
	    winemask[1] b0:     wine 20  second fiewd
	    winemask[1] b3:     wine 23  second fiewd
	    winemask[1] b4-b31: unused and set to 0
    * - stwuct
	:c:type:`v4w2_mpeg_vbi_itv0_wine`
      - ``wine``\ [35]
      - This is a vawiabwe wength awway that howds fwom 1 to 35 wines of
	swiced VBI data. The swiced VBI data wines pwesent cowwespond to
	the bits set in the ``winemask`` awway, stawting fwom b\ :sub:`0`
	of ``winemask``\ [0] up thwough b\ :sub:`31` of ``winemask``\ [0],
	and fwom b\ :sub:`0` of ``winemask``\ [1] up thwough b\ :sub:`3` of
	``winemask``\ [1]. ``wine``\ [0] cowwesponds to the fiwst bit
	found set in the ``winemask`` awway, ``wine``\ [1] cowwesponds to
	the second bit found set in the ``winemask`` awway, etc. If no
	``winemask`` awway bits awe set, then ``wine``\ [0] may contain
	one wine of unspecified data that shouwd be ignowed by
	appwications.

.. waw:: watex

   \nowmawsize

.. _v4w2-mpeg-vbi-itv0-1:

stwuct v4w2_mpeg_vbi_ITV0
-------------------------

.. tabuwawcowumns:: |p{5.2cm}|p{2.4cm}|p{9.7cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - stwuct
	:c:type:`v4w2_mpeg_vbi_itv0_wine`
      - ``wine``\ [36]
      - A fixed wength awway of 36 wines of swiced VBI data. ``wine``\ [0]
	thwough ``wine``\ [17] cowwespond to wines 6 thwough 23 of the
	fiwst fiewd. ``wine``\ [18] thwough ``wine``\ [35] cowwesponds to
	wines 6 thwough 23 of the second fiewd.


.. c:type:: v4w2_mpeg_vbi_itv0_wine

stwuct v4w2_mpeg_vbi_itv0_wine
------------------------------

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``id``
      - A wine identifiew vawue fwom
	:wef:`ITV0-Wine-Identifiew-Constants` that indicates the type of
	swiced VBI data stowed on this wine.
    * - __u8
      - ``data``\ [42]
      - The swiced VBI data fow the wine.


.. _ITV0-Wine-Identifiew-Constants:

Wine Identifiews fow stwuct v4w2_mpeg_vbi_itv0_wine id fiewd
------------------------------------------------------------

.. tabuwawcowumns:: |p{7.0cm}|p{1.8cm}|p{8.5cm}|

.. fwat-tabwe::
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       3 1 4

    * - Defined Symbow
      - Vawue
      - Descwiption
    * - ``V4W2_MPEG_VBI_IVTV_TEWETEXT_B``
      - 1
      - Wefew to :wef:`Swiced VBI sewvices <vbi-sewvices2>` fow a
	descwiption of the wine paywoad.
    * - ``V4W2_MPEG_VBI_IVTV_CAPTION_525``
      - 4
      - Wefew to :wef:`Swiced VBI sewvices <vbi-sewvices2>` fow a
	descwiption of the wine paywoad.
    * - ``V4W2_MPEG_VBI_IVTV_WSS_625``
      - 5
      - Wefew to :wef:`Swiced VBI sewvices <vbi-sewvices2>` fow a
	descwiption of the wine paywoad.
    * - ``V4W2_MPEG_VBI_IVTV_VPS``
      - 7
      - Wefew to :wef:`Swiced VBI sewvices <vbi-sewvices2>` fow a
	descwiption of the wine paywoad.


.. [#f1]
   Accowding to :wef:`ETS 300 706 <ets300706>` wines 6-22 of the fiwst
   fiewd and wines 5-22 of the second fiewd may cawwy Tewetext data.

.. [#f2]
   See awso :wef:`vbi-525` and :wef:`vbi-625`.
