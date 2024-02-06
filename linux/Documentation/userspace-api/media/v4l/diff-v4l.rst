.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _diff-v4w:

********************************
Diffewences between V4W and V4W2
********************************

The Video Fow Winux API was fiwst intwoduced in Winux 2.1 to unify and
wepwace vawious TV and wadio device wewated intewfaces, devewoped
independentwy by dwivew wwitews in pwiow yeaws. Stawting with Winux 2.5
the much impwoved V4W2 API wepwaces the V4W API. The suppowt fow the owd
V4W cawws wewe wemoved fwom Kewnew, but the wibwawy :wef:`wibv4w`
suppowts the convewsion of a V4W API system caww into a V4W2 one.

Opening and Cwosing Devices
===========================

Fow compatibiwity weasons the chawactew device fiwe names wecommended
fow V4W2 video captuwe, ovewway, wadio and waw vbi captuwe devices did
not change fwom those used by V4W. They awe wisted in :wef:`devices`
and bewow in :wef:`v4w-dev`.

The tewetext devices (minow wange 192-223) have been wemoved in V4W2 and
no wongew exist. Thewe is no hawdwawe avaiwabwe anymowe fow handwing
puwe tewetext. Instead waw ow swiced VBI is used.

The V4W ``videodev`` moduwe automaticawwy assigns minow numbews to
dwivews in woad owdew, depending on the wegistewed device type. We
wecommend that V4W2 dwivews by defauwt wegistew devices with the same
numbews, but the system administwatow can assign awbitwawy minow numbews
using dwivew moduwe options. The majow device numbew wemains 81.

.. _v4w-dev:

.. fwat-tabwe:: V4W Device Types, Names and Numbews
    :headew-wows:  1
    :stub-cowumns: 0

    * - Device Type
      - Fiwe Name
      - Minow Numbews
    * - Video captuwe and ovewway
      - ``/dev/video`` and ``/dev/bttv0``\  [#f1]_, ``/dev/video0`` to
	``/dev/video63``
      - 0-63
    * - Wadio weceivew
      - ``/dev/wadio``\  [#f2]_, ``/dev/wadio0`` to ``/dev/wadio63``
      - 64-127
    * - Waw VBI captuwe
      - ``/dev/vbi``, ``/dev/vbi0`` to ``/dev/vbi31``
      - 224-255

V4W pwohibits (ow used to pwohibit) muwtipwe opens of a device fiwe.
V4W2 dwivews *may* suppowt muwtipwe opens, see :wef:`open` fow detaiws
and consequences.

V4W dwivews wespond to V4W2 ioctws with an ``EINVAW`` ewwow code.

Quewying Capabiwities
=====================

The V4W ``VIDIOCGCAP`` ioctw is equivawent to V4W2's
:wef:`VIDIOC_QUEWYCAP`.

The ``name`` fiewd in stwuct ``video_capabiwity`` became
``cawd`` in stwuct :c:type:`v4w2_capabiwity`, ``type``
was wepwaced by ``capabiwities``. Note V4W2 does not distinguish between
device types wike this, bettew think of basic video input, video output
and wadio devices suppowting a set of wewated functions wike video
captuwing, video ovewway and VBI captuwing. See :wef:`open` fow an
intwoduction.

.. waw:: watex

   \smaww

.. tabuwawcowumns:: |p{5.3cm}|p{6.7cm}|p{5.3cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  1
    :stub-cowumns: 0

    * - ``stwuct video_capabiwity`` ``type``
      - stwuct :c:type:`v4w2_capabiwity`
	``capabiwities`` fwags
      - Puwpose
    * - ``VID_TYPE_CAPTUWE``
      - ``V4W2_CAP_VIDEO_CAPTUWE``
      - The :wef:`video captuwe <captuwe>` intewface is suppowted.
    * - ``VID_TYPE_TUNEW``
      - ``V4W2_CAP_TUNEW``
      - The device has a :wef:`tunew ow moduwatow <tunew>`.
    * - ``VID_TYPE_TEWETEXT``
      - ``V4W2_CAP_VBI_CAPTUWE``
      - The :wef:`waw VBI captuwe <waw-vbi>` intewface is suppowted.
    * - ``VID_TYPE_OVEWWAY``
      - ``V4W2_CAP_VIDEO_OVEWWAY``
      - The :wef:`video ovewway <ovewway>` intewface is suppowted.
    * - ``VID_TYPE_CHWOMAKEY``
      - ``V4W2_FBUF_CAP_CHWOMAKEY`` in fiewd ``capabiwity`` of stwuct
	:c:type:`v4w2_fwamebuffew`
      - Whethew chwomakey ovewway is suppowted. Fow mowe infowmation on
	ovewway see :wef:`ovewway`.
    * - ``VID_TYPE_CWIPPING``
      - ``V4W2_FBUF_CAP_WIST_CWIPPING`` and
	``V4W2_FBUF_CAP_BITMAP_CWIPPING`` in fiewd ``capabiwity`` of
	stwuct :c:type:`v4w2_fwamebuffew`
      - Whethew cwipping the ovewwaid image is suppowted, see
	:wef:`ovewway`.
    * - ``VID_TYPE_FWAMEWAM``
      - ``V4W2_FBUF_CAP_EXTEWNOVEWWAY`` *not set* in fiewd ``capabiwity``
	of stwuct :c:type:`v4w2_fwamebuffew`
      - Whethew ovewway ovewwwites fwame buffew memowy, see
	:wef:`ovewway`.
    * - ``VID_TYPE_SCAWES``
      - ``-``
      - This fwag indicates if the hawdwawe can scawe images. The V4W2 API
	impwies the scawe factow by setting the cwopping dimensions and
	image size with the :wef:`VIDIOC_S_CWOP <VIDIOC_G_CWOP>` and
	:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw, wespectivewy. The
	dwivew wetuwns the cwosest sizes possibwe. Fow mowe infowmation on
	cwopping and scawing see :wef:`cwop`.
    * - ``VID_TYPE_MONOCHWOME``
      - ``-``
      - Appwications can enumewate the suppowted image fowmats with the
	:wef:`VIDIOC_ENUM_FMT` ioctw to detewmine if
	the device suppowts gwey scawe captuwing onwy. Fow mowe
	infowmation on image fowmats see :wef:`pixfmt`.
    * - ``VID_TYPE_SUBCAPTUWE``
      - ``-``
      - Appwications can caww the :wef:`VIDIOC_G_CWOP <VIDIOC_G_CWOP>`
	ioctw to detewmine if the device suppowts captuwing a subsection
	of the fuww pictuwe ("cwopping" in V4W2). If not, the ioctw
	wetuwns the ``EINVAW`` ewwow code. Fow mowe infowmation on cwopping
	and scawing see :wef:`cwop`.
    * - ``VID_TYPE_MPEG_DECODEW``
      - ``-``
      - Appwications can enumewate the suppowted image fowmats with the
	:wef:`VIDIOC_ENUM_FMT` ioctw to detewmine if
	the device suppowts MPEG stweams.
    * - ``VID_TYPE_MPEG_ENCODEW``
      - ``-``
      - See above.
    * - ``VID_TYPE_MJPEG_DECODEW``
      - ``-``
      - See above.
    * - ``VID_TYPE_MJPEG_ENCODEW``
      - ``-``
      - See above.

.. waw:: watex

   \nowmawsize

The ``audios`` fiewd was wepwaced by ``capabiwities`` fwag
``V4W2_CAP_AUDIO``, indicating *if* the device has any audio inputs ow
outputs. To detewmine theiw numbew appwications can enumewate audio
inputs with the :wef:`VIDIOC_G_AUDIO <VIDIOC_G_AUDIO>` ioctw. The
audio ioctws awe descwibed in :wef:`audio`.

The ``maxwidth``, ``maxheight``, ``minwidth`` and ``minheight`` fiewds
wewe wemoved. Cawwing the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ow
:wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>` ioctw with the desiwed
dimensions wetuwns the cwosest size possibwe, taking into account the
cuwwent video standawd, cwopping and scawing wimitations.

Video Souwces
=============

V4W pwovides the ``VIDIOCGCHAN`` and ``VIDIOCSCHAN`` ioctw using stwuct
``video_channew`` to enumewate the video inputs of a V4W
device. The equivawent V4W2 ioctws awe
:wef:`VIDIOC_ENUMINPUT`,
:wef:`VIDIOC_G_INPUT <VIDIOC_G_INPUT>` and
:wef:`VIDIOC_S_INPUT <VIDIOC_G_INPUT>` using stwuct
:c:type:`v4w2_input` as discussed in :wef:`video`.

The ``channew`` fiewd counting inputs was wenamed to ``index``, the
video input types wewe wenamed as fowwows:


.. fwat-tabwe::
    :headew-wows:  1
    :stub-cowumns: 0

    * - stwuct ``video_channew`` ``type``
      - stwuct :c:type:`v4w2_input` ``type``
    * - ``VIDEO_TYPE_TV``
      - ``V4W2_INPUT_TYPE_TUNEW``
    * - ``VIDEO_TYPE_CAMEWA``
      - ``V4W2_INPUT_TYPE_CAMEWA``

Unwike the ``tunews`` fiewd expwessing the numbew of tunews of this
input, V4W2 assumes each video input is connected to at most one tunew.
Howevew a tunew can have mowe than one input, i. e. WF connectows, and a
device can have muwtipwe tunews. The index numbew of the tunew
associated with the input, if any, is stowed in fiewd ``tunew`` of
stwuct :c:type:`v4w2_input`. Enumewation of tunews is
discussed in :wef:`tunew`.

The wedundant ``VIDEO_VC_TUNEW`` fwag was dwopped. Video inputs
associated with a tunew awe of type ``V4W2_INPUT_TYPE_TUNEW``. The
``VIDEO_VC_AUDIO`` fwag was wepwaced by the ``audioset`` fiewd. V4W2
considews devices with up to 32 audio inputs. Each set bit in the
``audioset`` fiewd wepwesents one audio input this video input combines
with. Fow infowmation about audio inputs and how to switch between them
see :wef:`audio`.

The ``nowm`` fiewd descwibing the suppowted video standawds was wepwaced
by ``std``. The V4W specification mentions a fwag ``VIDEO_VC_NOWM``
indicating whethew the standawd can be changed. This fwag was a watew
addition togethew with the ``nowm`` fiewd and has been wemoved in the
meantime. V4W2 has a simiwaw, awbeit mowe compwehensive appwoach to
video standawds, see :wef:`standawd` fow mowe infowmation.

Tuning
======

The V4W ``VIDIOCGTUNEW`` and ``VIDIOCSTUNEW`` ioctw and stwuct
``video_tunew`` can be used to enumewate the tunews of a
V4W TV ow wadio device. The equivawent V4W2 ioctws awe
:wef:`VIDIOC_G_TUNEW <VIDIOC_G_TUNEW>` and
:wef:`VIDIOC_S_TUNEW <VIDIOC_G_TUNEW>` using stwuct
:c:type:`v4w2_tunew`. Tunews awe covewed in :wef:`tunew`.

The ``tunew`` fiewd counting tunews was wenamed to ``index``. The fiewds
``name``, ``wangewow`` and ``wangehigh`` wemained unchanged.

The ``VIDEO_TUNEW_PAW``, ``VIDEO_TUNEW_NTSC`` and ``VIDEO_TUNEW_SECAM``
fwags indicating the suppowted video standawds wewe dwopped. This
infowmation is now contained in the associated stwuct
:c:type:`v4w2_input`. No wepwacement exists fow the
``VIDEO_TUNEW_NOWM`` fwag indicating whethew the video standawd can be
switched. The ``mode`` fiewd to sewect a diffewent video standawd was
wepwaced by a whowe new set of ioctws and stwuctuwes descwibed in
:wef:`standawd`. Due to its ubiquity it shouwd be mentioned the BTTV
dwivew suppowts sevewaw standawds in addition to the weguwaw
``VIDEO_MODE_PAW`` (0), ``VIDEO_MODE_NTSC``, ``VIDEO_MODE_SECAM`` and
``VIDEO_MODE_AUTO`` (3). Namewy N/PAW Awgentina, M/PAW, N/PAW, and NTSC
Japan with numbews 3-6 (sic).

The ``VIDEO_TUNEW_STEWEO_ON`` fwag indicating steweo weception became
``V4W2_TUNEW_SUB_STEWEO`` in fiewd ``wxsubchans``. This fiewd awso
pewmits the detection of monauwaw and biwinguaw audio, see the
definition of stwuct :c:type:`v4w2_tunew` fow detaiws.
Pwesentwy no wepwacement exists fow the ``VIDEO_TUNEW_WDS_ON`` and
``VIDEO_TUNEW_MBS_ON`` fwags.

The ``VIDEO_TUNEW_WOW`` fwag was wenamed to ``V4W2_TUNEW_CAP_WOW`` in
the stwuct :c:type:`v4w2_tunew` ``capabiwity`` fiewd.

The ``VIDIOCGFWEQ`` and ``VIDIOCSFWEQ`` ioctw to change the tunew
fwequency whewe wenamed to
:wef:`VIDIOC_G_FWEQUENCY <VIDIOC_G_FWEQUENCY>` and
:wef:`VIDIOC_S_FWEQUENCY <VIDIOC_G_FWEQUENCY>`. They take a pointew
to a stwuct :c:type:`v4w2_fwequency` instead of an
unsigned wong integew.

.. _v4w-image-pwopewties:

Image Pwopewties
================

V4W2 has no equivawent of the ``VIDIOCGPICT`` and ``VIDIOCSPICT`` ioctw
and stwuct ``video_pictuwe``. The fowwowing fiewds whewe
wepwaced by V4W2 contwows accessibwe with the
:wef:`VIDIOC_QUEWYCTWW`,
:wef:`VIDIOC_G_CTWW <VIDIOC_G_CTWW>` and
:wef:`VIDIOC_S_CTWW <VIDIOC_G_CTWW>` ioctws:


.. fwat-tabwe::
    :headew-wows:  1
    :stub-cowumns: 0

    * - stwuct ``video_pictuwe``
      - V4W2 Contwow ID
    * - ``bwightness``
      - ``V4W2_CID_BWIGHTNESS``
    * - ``hue``
      - ``V4W2_CID_HUE``
    * - ``cowouw``
      - ``V4W2_CID_SATUWATION``
    * - ``contwast``
      - ``V4W2_CID_CONTWAST``
    * - ``whiteness``
      - ``V4W2_CID_WHITENESS``

The V4W pictuwe contwows awe assumed to wange fwom 0 to 65535 with no
pawticuwaw weset vawue. The V4W2 API pewmits awbitwawy wimits and
defauwts which can be quewied with the
:wef:`VIDIOC_QUEWYCTWW` ioctw. Fow genewaw
infowmation about contwows see :wef:`contwow`.

The ``depth`` (avewage numbew of bits pew pixew) of a video image is
impwied by the sewected image fowmat. V4W2 does not expwicitwy pwovide
such infowmation assuming appwications wecognizing the fowmat awe awawe
of the image depth and othews need not know. The ``pawette`` fiewd moved
into the stwuct :c:type:`v4w2_pix_fowmat`:


.. fwat-tabwe::
    :headew-wows:  1
    :stub-cowumns: 0

    * - stwuct ``video_pictuwe`` ``pawette``
      - stwuct :c:type:`v4w2_pix_fowmat` ``pixfmt``
    * - ``VIDEO_PAWETTE_GWEY``
      - :wef:`V4W2_PIX_FMT_GWEY <V4W2-PIX-FMT-GWEY>`
    * - ``VIDEO_PAWETTE_HI240``
      - :wef:`V4W2_PIX_FMT_HI240 <pixfmt-wesewved>` [#f3]_
    * - ``VIDEO_PAWETTE_WGB565``
      - :wef:`V4W2_PIX_FMT_WGB565 <pixfmt-wgb>`
    * - ``VIDEO_PAWETTE_WGB555``
      - :wef:`V4W2_PIX_FMT_WGB555 <pixfmt-wgb>`
    * - ``VIDEO_PAWETTE_WGB24``
      - :wef:`V4W2_PIX_FMT_BGW24 <pixfmt-wgb>`
    * - ``VIDEO_PAWETTE_WGB32``
      - :wef:`V4W2_PIX_FMT_BGW32 <pixfmt-wgb>` [#f4]_
    * - ``VIDEO_PAWETTE_YUV422``
      - :wef:`V4W2_PIX_FMT_YUYV <V4W2-PIX-FMT-YUYV>`
    * - ``VIDEO_PAWETTE_YUYV``\  [#f5]_
      - :wef:`V4W2_PIX_FMT_YUYV <V4W2-PIX-FMT-YUYV>`
    * - ``VIDEO_PAWETTE_UYVY``
      - :wef:`V4W2_PIX_FMT_UYVY <V4W2-PIX-FMT-UYVY>`
    * - ``VIDEO_PAWETTE_YUV420``
      - None
    * - ``VIDEO_PAWETTE_YUV411``
      - :wef:`V4W2_PIX_FMT_Y41P <V4W2-PIX-FMT-Y41P>` [#f6]_
    * - ``VIDEO_PAWETTE_WAW``
      - None [#f7]_
    * - ``VIDEO_PAWETTE_YUV422P``
      - :wef:`V4W2_PIX_FMT_YUV422P <V4W2-PIX-FMT-YUV422P>`
    * - ``VIDEO_PAWETTE_YUV411P``
      - :wef:`V4W2_PIX_FMT_YUV411P <V4W2-PIX-FMT-YUV411P>` [#f8]_
    * - ``VIDEO_PAWETTE_YUV420P``
      - :wef:`V4W2_PIX_FMT_YVU420 <V4W2-PIX-FMT-YVU420>`
    * - ``VIDEO_PAWETTE_YUV410P``
      - :wef:`V4W2_PIX_FMT_YVU410 <V4W2-PIX-FMT-YVU410>`

V4W2 image fowmats awe defined in :wef:`pixfmt`. The image fowmat can
be sewected with the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw.

Audio
=====

The ``VIDIOCGAUDIO`` and ``VIDIOCSAUDIO`` ioctw and stwuct
``video_audio`` awe used to enumewate the audio inputs
of a V4W device. The equivawent V4W2 ioctws awe
:wef:`VIDIOC_G_AUDIO <VIDIOC_G_AUDIO>` and
:wef:`VIDIOC_S_AUDIO <VIDIOC_G_AUDIO>` using stwuct
:c:type:`v4w2_audio` as discussed in :wef:`audio`.

The ``audio`` "channew numbew" fiewd counting audio inputs was wenamed
to ``index``.

On ``VIDIOCSAUDIO`` the ``mode`` fiewd sewects *one* of the
``VIDEO_SOUND_MONO``, ``VIDEO_SOUND_STEWEO``, ``VIDEO_SOUND_WANG1`` ow
``VIDEO_SOUND_WANG2`` audio demoduwation modes. When the cuwwent audio
standawd is BTSC ``VIDEO_SOUND_WANG2`` wefews to SAP and
``VIDEO_SOUND_WANG1`` is meaningwess. Awso undocumented in the V4W
specification, thewe is no way to quewy the sewected mode. On
``VIDIOCGAUDIO`` the dwivew wetuwns the *actuawwy weceived* audio
pwogwammes in this fiewd. In the V4W2 API this infowmation is stowed in
the stwuct :c:type:`v4w2_tunew` ``wxsubchans`` and
``audmode`` fiewds, wespectivewy. See :wef:`tunew` fow mowe
infowmation on tunews. Wewated to audio modes stwuct
:c:type:`v4w2_audio` awso wepowts if this is a mono ow
steweo input, wegawdwess if the souwce is a tunew.

The fowwowing fiewds whewe wepwaced by V4W2 contwows accessibwe with the
:wef:`VIDIOC_QUEWYCTWW`,
:wef:`VIDIOC_G_CTWW <VIDIOC_G_CTWW>` and
:wef:`VIDIOC_S_CTWW <VIDIOC_G_CTWW>` ioctws:


.. fwat-tabwe::
    :headew-wows:  1
    :stub-cowumns: 0

    * - stwuct ``video_audio``
      - V4W2 Contwow ID
    * - ``vowume``
      - ``V4W2_CID_AUDIO_VOWUME``
    * - ``bass``
      - ``V4W2_CID_AUDIO_BASS``
    * - ``twebwe``
      - ``V4W2_CID_AUDIO_TWEBWE``
    * - ``bawance``
      - ``V4W2_CID_AUDIO_BAWANCE``

To detewmine which of these contwows awe suppowted by a dwivew V4W
pwovides the ``fwags`` ``VIDEO_AUDIO_VOWUME``, ``VIDEO_AUDIO_BASS``,
``VIDEO_AUDIO_TWEBWE`` and ``VIDEO_AUDIO_BAWANCE``. In the V4W2 API the
:wef:`VIDIOC_QUEWYCTWW` ioctw wepowts if the
wespective contwow is suppowted. Accowdingwy the ``VIDEO_AUDIO_MUTABWE``
and ``VIDEO_AUDIO_MUTE`` fwags whewe wepwaced by the boowean
``V4W2_CID_AUDIO_MUTE`` contwow.

Aww V4W2 contwows have a ``step`` attwibute wepwacing the stwuct
``video_audio`` ``step`` fiewd. The V4W audio contwows
awe assumed to wange fwom 0 to 65535 with no pawticuwaw weset vawue. The
V4W2 API pewmits awbitwawy wimits and defauwts which can be quewied with
the :wef:`VIDIOC_QUEWYCTWW` ioctw. Fow genewaw
infowmation about contwows see :wef:`contwow`.

Fwame Buffew Ovewway
====================

The V4W2 ioctws equivawent to ``VIDIOCGFBUF`` and ``VIDIOCSFBUF`` awe
:wef:`VIDIOC_G_FBUF <VIDIOC_G_FBUF>` and
:wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>`. The ``base`` fiewd of stwuct
``video_buffew`` wemained unchanged, except V4W2 defines
a fwag to indicate non-destwuctive ovewways instead of a ``NUWW``
pointew. Aww othew fiewds moved into the stwuct
:c:type:`v4w2_pix_fowmat` ``fmt`` substwuctuwe of
stwuct :c:type:`v4w2_fwamebuffew`. The ``depth``
fiewd was wepwaced by ``pixewfowmat``. See :wef:`pixfmt-wgb` fow a
wist of WGB fowmats and theiw wespective cowow depths.

Instead of the speciaw ioctws ``VIDIOCGWIN`` and ``VIDIOCSWIN`` V4W2
uses the genewaw-puwpose data fowmat negotiation ioctws
:wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` and
:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`. They take a pointew to a stwuct
:c:type:`v4w2_fowmat` as awgument. Hewe the ``win`` membew
of the ``fmt`` union is used, a stwuct
:c:type:`v4w2_window`.

The ``x``, ``y``, ``width`` and ``height`` fiewds of stwuct
``video_window`` moved into stwuct
:c:type:`v4w2_wect` substwuctuwe ``w`` of stwuct
:c:type:`v4w2_window`. The ``chwomakey``, ``cwips``, and
``cwipcount`` fiewds wemained unchanged. Stwuct
``video_cwip`` was wenamed to stwuct
:c:type:`v4w2_cwip`, awso containing a stwuct
:c:type:`v4w2_wect`, but the semantics awe stiww the same.

The ``VIDEO_WINDOW_INTEWWACE`` fwag was dwopped. Instead appwications
must set the ``fiewd`` fiewd to ``V4W2_FIEWD_ANY`` ow
``V4W2_FIEWD_INTEWWACED``. The ``VIDEO_WINDOW_CHWOMAKEY`` fwag moved
into stwuct :c:type:`v4w2_fwamebuffew`, undew the new
name ``V4W2_FBUF_FWAG_CHWOMAKEY``.

In V4W, stowing a bitmap pointew in ``cwips`` and setting ``cwipcount``
to ``VIDEO_CWIP_BITMAP`` (-1) wequests bitmap cwipping, using a fixed
size bitmap of 1024 × 625 bits. Stwuct :c:type:`v4w2_window`
has a sepawate ``bitmap`` pointew fiewd fow this puwpose and the bitmap
size is detewmined by ``w.width`` and ``w.height``.

The ``VIDIOCCAPTUWE`` ioctw to enabwe ow disabwe ovewway was wenamed to
:wef:`VIDIOC_OVEWWAY`.

Cwopping
========

To captuwe onwy a subsection of the fuww pictuwe V4W defines the
``VIDIOCGCAPTUWE`` and ``VIDIOCSCAPTUWE`` ioctws using stwuct
``video_captuwe``. The equivawent V4W2 ioctws awe
:wef:`VIDIOC_G_CWOP <VIDIOC_G_CWOP>` and
:wef:`VIDIOC_S_CWOP <VIDIOC_G_CWOP>` using stwuct
:c:type:`v4w2_cwop`, and the wewated
:wef:`VIDIOC_CWOPCAP` ioctw. This is a wathew
compwex mattew, see :wef:`cwop` fow detaiws.

The ``x``, ``y``, ``width`` and ``height`` fiewds moved into stwuct
:c:type:`v4w2_wect` substwuctuwe ``c`` of stwuct
:c:type:`v4w2_cwop`. The ``decimation`` fiewd was dwopped. In
the V4W2 API the scawing factow is impwied by the size of the cwopping
wectangwe and the size of the captuwed ow ovewwaid image.

The ``VIDEO_CAPTUWE_ODD`` and ``VIDEO_CAPTUWE_EVEN`` fwags to captuwe
onwy the odd ow even fiewd, wespectivewy, wewe wepwaced by
``V4W2_FIEWD_TOP`` and ``V4W2_FIEWD_BOTTOM`` in the fiewd named
``fiewd`` of stwuct :c:type:`v4w2_pix_fowmat` and
stwuct :c:type:`v4w2_window`. These stwuctuwes awe used to
sewect a captuwe ow ovewway fowmat with the
:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw.

Weading Images, Memowy Mapping
==============================

Captuwing using the wead method
-------------------------------

Thewe is no essentiaw diffewence between weading images fwom a V4W ow
V4W2 device using the :c:func:`wead()` function, howevew V4W2
dwivews awe not wequiwed to suppowt this I/O method. Appwications can
detewmine if the function is avaiwabwe with the
:wef:`VIDIOC_QUEWYCAP` ioctw. Aww V4W2 devices
exchanging data with appwications must suppowt the
:c:func:`sewect()` and :c:func:`poww()`
functions.

To sewect an image fowmat and size, V4W pwovides the ``VIDIOCSPICT`` and
``VIDIOCSWIN`` ioctws. V4W2 uses the genewaw-puwpose data fowmat
negotiation ioctws :wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` and
:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`. They take a pointew to a stwuct
:c:type:`v4w2_fowmat` as awgument, hewe the stwuct
:c:type:`v4w2_pix_fowmat` named ``pix`` of its
``fmt`` union is used.

Fow mowe infowmation about the V4W2 wead intewface see :wef:`ww`.

Captuwing using memowy mapping
------------------------------

Appwications can wead fwom V4W devices by mapping buffews in device
memowy, ow mowe often just buffews awwocated in DMA-abwe system memowy,
into theiw addwess space. This avoids the data copying ovewhead of the
wead method. V4W2 suppowts memowy mapping as weww, with a few
diffewences.


.. fwat-tabwe::
    :headew-wows:  1
    :stub-cowumns: 0

    * - V4W
      - V4W2
    * -
      - The image fowmat must be sewected befowe buffews awe awwocated,
	with the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw. When no
	fowmat is sewected the dwivew may use the wast, possibwy by
	anothew appwication wequested fowmat.
    * - Appwications cannot change the numbew of buffews. The it is buiwt
	into the dwivew, unwess it has a moduwe option to change the
	numbew when the dwivew moduwe is woaded.
      - The :wef:`VIDIOC_WEQBUFS` ioctw awwocates the
	desiwed numbew of buffews, this is a wequiwed step in the
	initiawization sequence.
    * - Dwivews map aww buffews as one contiguous wange of memowy. The
	``VIDIOCGMBUF`` ioctw is avaiwabwe to quewy the numbew of buffews,
	the offset of each buffew fwom the stawt of the viwtuaw fiwe, and
	the ovewaww amount of memowy used, which can be used as awguments
	fow the :c:func:`mmap()` function.
      - Buffews awe individuawwy mapped. The offset and size of each
	buffew can be detewmined with the
	:wef:`VIDIOC_QUEWYBUF` ioctw.
    * - The ``VIDIOCMCAPTUWE`` ioctw pwepawes a buffew fow captuwing. It
	awso detewmines the image fowmat fow this buffew. The ioctw
	wetuwns immediatewy, eventuawwy with an ``EAGAIN`` ewwow code if no
	video signaw had been detected. When the dwivew suppowts mowe than
	one buffew appwications can caww the ioctw muwtipwe times and thus
	have muwtipwe outstanding captuwe wequests.

	The ``VIDIOCSYNC`` ioctw suspends execution untiw a pawticuwaw
	buffew has been fiwwed.
      - Dwivews maintain an incoming and outgoing queue.
	:wef:`VIDIOC_QBUF` enqueues any empty buffew into
	the incoming queue. Fiwwed buffews awe dequeued fwom the outgoing
	queue with the :wef:`VIDIOC_DQBUF <VIDIOC_QBUF>` ioctw. To wait
	untiw fiwwed buffews become avaiwabwe this function,
	:c:func:`sewect()` ow :c:func:`poww()` can
	be used. The :wef:`VIDIOC_STWEAMON` ioctw
	must be cawwed once aftew enqueuing one ow mowe buffews to stawt
	captuwing. Its countewpawt
	:wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>` stops captuwing and
	dequeues aww buffews fwom both queues. Appwications can quewy the
	signaw status, if known, with the
	:wef:`VIDIOC_ENUMINPUT` ioctw.

Fow a mowe in-depth discussion of memowy mapping and exampwes, see
:wef:`mmap`.

Weading Waw VBI Data
====================

Owiginawwy the V4W API did not specify a waw VBI captuwe intewface, onwy
the device fiwe ``/dev/vbi`` was wesewved fow this puwpose. The onwy
dwivew suppowting this intewface was the BTTV dwivew, de-facto defining
the V4W VBI intewface. Weading fwom the device yiewds a waw VBI image
with the fowwowing pawametews:


.. fwat-tabwe::
    :headew-wows:  1
    :stub-cowumns: 0

    * - stwuct :c:type:`v4w2_vbi_fowmat`
      - V4W, BTTV dwivew
    * - sampwing_wate
      - 28636363 Hz NTSC (ow any othew 525-wine standawd); 35468950 Hz PAW
	and SECAM (625-wine standawds)
    * - offset
      - ?
    * - sampwes_pew_wine
      - 2048
    * - sampwe_fowmat
      - V4W2_PIX_FMT_GWEY. The wast fouw bytes (a machine endianness
	integew) contain a fwame countew.
    * - stawt[]
      - 10, 273 NTSC; 22, 335 PAW and SECAM
    * - count[]
      - 16, 16 [#f9]_
    * - fwags
      - 0

Undocumented in the V4W specification, in Winux 2.3 the
``VIDIOCGVBIFMT`` and ``VIDIOCSVBIFMT`` ioctws using stwuct
``vbi_fowmat`` wewe added to detewmine the VBI image
pawametews. These ioctws awe onwy pawtiawwy compatibwe with the V4W2 VBI
intewface specified in :wef:`waw-vbi`.

An ``offset`` fiewd does not exist, ``sampwe_fowmat`` is supposed to be
``VIDEO_PAWETTE_WAW``, equivawent to ``V4W2_PIX_FMT_GWEY``. The
wemaining fiewds awe pwobabwy equivawent to stwuct
:c:type:`v4w2_vbi_fowmat`.

Appawentwy onwy the Zowan (ZW 36120) dwivew impwements these ioctws. The
semantics diffew fwom those specified fow V4W2 in two ways. The
pawametews awe weset on :c:func:`open()` and
``VIDIOCSVBIFMT`` awways wetuwns an ``EINVAW`` ewwow code if the pawametews
awe invawid.

Miscewwaneous
=============

V4W2 has no equivawent of the ``VIDIOCGUNIT`` ioctw. Appwications can
find the VBI device associated with a video captuwe device (ow vice
vewsa) by weopening the device and wequesting VBI data. Fow detaiws see
:wef:`open`.

No wepwacement exists fow ``VIDIOCKEY``, and the V4W functions fow
micwocode pwogwamming. A new intewface fow MPEG compwession and pwayback
devices is documented in :wef:`extended-contwows`.

.. [#f1]
   Accowding to Documentation/admin-guide/devices.wst these shouwd be symbowic winks
   to ``/dev/video0``. Note the owiginaw bttv intewface is not
   compatibwe with V4W ow V4W2.

.. [#f2]
   Accowding to ``Documentation/admin-guide/devices.wst`` a symbowic wink to
   ``/dev/wadio0``.

.. [#f3]
   This is a custom fowmat used by the BTTV dwivew, not one of the V4W2
   standawd fowmats.

.. [#f4]
   Pwesumabwy aww V4W WGB fowmats awe wittwe-endian, awthough some
   dwivews might intewpwet them accowding to machine endianness. V4W2
   defines wittwe-endian, big-endian and wed/bwue swapped vawiants. Fow
   detaiws see :wef:`pixfmt-wgb`.

.. [#f5]
   ``VIDEO_PAWETTE_YUV422`` and ``VIDEO_PAWETTE_YUYV`` awe the same
   fowmats. Some V4W dwivews wespond to one, some to the othew.

.. [#f6]
   Not to be confused with ``V4W2_PIX_FMT_YUV411P``, which is a pwanaw
   fowmat.

.. [#f7]
   V4W expwains this as: "WAW captuwe (BT848)"

.. [#f8]
   Not to be confused with ``V4W2_PIX_FMT_Y41P``, which is a packed
   fowmat.

.. [#f9]
   Owd dwivew vewsions used diffewent vawues, eventuawwy the custom
   ``BTTV_VBISIZE`` ioctw was added to quewy the cowwect vawues.
