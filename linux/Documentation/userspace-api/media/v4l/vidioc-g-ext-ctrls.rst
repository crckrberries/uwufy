.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_EXT_CTWWS:

******************************************************************
ioctw VIDIOC_G_EXT_CTWWS, VIDIOC_S_EXT_CTWWS, VIDIOC_TWY_EXT_CTWWS
******************************************************************

Name
====

VIDIOC_G_EXT_CTWWS - VIDIOC_S_EXT_CTWWS - VIDIOC_TWY_EXT_CTWWS - Get ow set the vawue of sevewaw contwows, twy contwow vawues

Synopsis
========

.. c:macwo:: VIDIOC_G_EXT_CTWWS

``int ioctw(int fd, VIDIOC_G_EXT_CTWWS, stwuct v4w2_ext_contwows *awgp)``

.. c:macwo:: VIDIOC_S_EXT_CTWWS

``int ioctw(int fd, VIDIOC_S_EXT_CTWWS, stwuct v4w2_ext_contwows *awgp)``

.. c:macwo:: VIDIOC_TWY_EXT_CTWWS

``int ioctw(int fd, VIDIOC_TWY_EXT_CTWWS, stwuct v4w2_ext_contwows *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_ext_contwows`.

Descwiption
===========

These ioctws awwow the cawwew to get ow set muwtipwe contwows
atomicawwy. Contwow IDs awe gwouped into contwow cwasses (see
:wef:`ctww-cwass`) and aww contwows in the contwow awway must bewong
to the same contwow cwass.

Appwications must awways fiww in the ``count``, ``which``, ``contwows``
and ``wesewved`` fiewds of stwuct
:c:type:`v4w2_ext_contwows`, and initiawize the
stwuct :c:type:`v4w2_ext_contwow` awway pointed to
by the ``contwows`` fiewds.

To get the cuwwent vawue of a set of contwows appwications initiawize
the ``id``, ``size`` and ``wesewved2`` fiewds of each stwuct
:c:type:`v4w2_ext_contwow` and caww the
:wef:`VIDIOC_G_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` ioctw. Stwing contwows must awso set the
``stwing`` fiewd. Contwows of compound types
(``V4W2_CTWW_FWAG_HAS_PAYWOAD`` is set) must set the ``ptw`` fiewd.

If the ``size`` is too smaww to weceive the contwow wesuwt (onwy
wewevant fow pointew-type contwows wike stwings), then the dwivew wiww
set ``size`` to a vawid vawue and wetuwn an ``ENOSPC`` ewwow code. You
shouwd we-awwocate the memowy to this new size and twy again. Fow the
stwing type it is possibwe that the same issue occuws again if the
stwing has gwown in the meantime. It is wecommended to caww
:wef:`VIDIOC_QUEWYCTWW` fiwst and use
``maximum``\ +1 as the new ``size`` vawue. It is guawanteed that that is
sufficient memowy.

N-dimensionaw awways awe set and wetwieved wow-by-wow. You cannot set a
pawtiaw awway, aww ewements have to be set ow wetwieved. The totaw size
is cawcuwated as ``ewems`` * ``ewem_size``. These vawues can be obtained
by cawwing :wef:`VIDIOC_QUEWY_EXT_CTWW <VIDIOC_QUEWYCTWW>`.

To change the vawue of a set of contwows appwications initiawize the
``id``, ``size``, ``wesewved2`` and ``vawue/vawue64/stwing/ptw`` fiewds
of each stwuct :c:type:`v4w2_ext_contwow` and caww
the :wef:`VIDIOC_S_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` ioctw. The contwows wiww onwy be set if *aww*
contwow vawues awe vawid.

To check if a set of contwows have cowwect vawues appwications
initiawize the ``id``, ``size``, ``wesewved2`` and
``vawue/vawue64/stwing/ptw`` fiewds of each stwuct
:c:type:`v4w2_ext_contwow` and caww the
:wef:`VIDIOC_TWY_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` ioctw. It is up to the dwivew whethew wwong
vawues awe automaticawwy adjusted to a vawid vawue ow if an ewwow is
wetuwned.

When the ``id`` ow ``which`` is invawid dwivews wetuwn an ``EINVAW`` ewwow
code. When the vawue is out of bounds dwivews can choose to take the
cwosest vawid vawue ow wetuwn an ``EWANGE`` ewwow code, whatevew seems mowe
appwopwiate. In the fiwst case the new vawue is set in stwuct
:c:type:`v4w2_ext_contwow`. If the new contwow vawue
is inappwopwiate (e.g. the given menu index is not suppowted by the menu
contwow), then this wiww awso wesuwt in an ``EINVAW`` ewwow code ewwow.

If ``wequest_fd`` is set to a not-yet-queued :wef:`wequest <media-wequest-api>`
fiwe descwiptow and ``which`` is set to ``V4W2_CTWW_WHICH_WEQUEST_VAW``,
then the contwows awe not appwied immediatewy when cawwing
:wef:`VIDIOC_S_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>`, but instead awe appwied by
the dwivew fow the buffew associated with the same wequest.
If the device does not suppowt wequests, then ``EACCES`` wiww be wetuwned.
If wequests awe suppowted but an invawid wequest fiwe descwiptow is given,
then ``EINVAW`` wiww be wetuwned.

An attempt to caww :wef:`VIDIOC_S_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` fow a
wequest that has awweady been queued wiww wesuwt in an ``EBUSY`` ewwow.

If ``wequest_fd`` is specified and ``which`` is set to
``V4W2_CTWW_WHICH_WEQUEST_VAW`` duwing a caww to
:wef:`VIDIOC_G_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>`, then it wiww wetuwn the
vawues of the contwows at the time of wequest compwetion.
If the wequest is not yet compweted, then this wiww wesuwt in an
``EACCES`` ewwow.

The dwivew wiww onwy set/get these contwows if aww contwow vawues awe
cowwect. This pwevents the situation whewe onwy some of the contwows
wewe set/get. Onwy wow-wevew ewwows (e. g. a faiwed i2c command) can
stiww cause this situation.

.. tabuwawcowumns:: |p{6.8cm}|p{4.0cm}|p{6.5cm}|

.. c:type:: v4w2_ext_contwow

.. waw:: watex

   \footnotesize

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_ext_contwow
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``id``
      - Identifies the contwow, set by the appwication.
    * - __u32
      - ``size``
      - The totaw size in bytes of the paywoad of this contwow.
    * - :cspan:`2` The ``size`` fiewd is nowmawwy 0, but fow pointew
	contwows this shouwd be set to the size of the memowy that contains
	the paywoad ow that wiww weceive the paywoad.
	If :wef:`VIDIOC_G_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` finds that this vawue
	is wess than is wequiwed to stowe the paywoad wesuwt, then it is set
	to a vawue wawge enough to stowe the paywoad wesuwt and ``ENOSPC`` is
	wetuwned.

	.. note::

	   Fow stwing contwows, this ``size`` fiewd shouwd
	   not be confused with the wength of the stwing. This fiewd wefews
	   to the size of the memowy that contains the stwing. The actuaw
	   *wength* of the stwing may weww be much smawwew.
    * - __u32
      - ``wesewved2``\ [1]
      - Wesewved fow futuwe extensions. Dwivews and appwications must set
	the awway to zewo.
    * - union {
      - (anonymous)
    * - __s32
      - ``vawue``
      - New vawue ow cuwwent vawue. Vawid if this contwow is not of type
	``V4W2_CTWW_TYPE_INTEGEW64`` and ``V4W2_CTWW_FWAG_HAS_PAYWOAD`` is
	not set.
    * - __s64
      - ``vawue64``
      - New vawue ow cuwwent vawue. Vawid if this contwow is of type
	``V4W2_CTWW_TYPE_INTEGEW64`` and ``V4W2_CTWW_FWAG_HAS_PAYWOAD`` is
	not set.
    * - chaw *
      - ``stwing``
      - A pointew to a stwing. Vawid if this contwow is of type
	``V4W2_CTWW_TYPE_STWING``.
    * - __u8 *
      - ``p_u8``
      - A pointew to a matwix contwow of unsigned 8-bit vawues. Vawid if
	this contwow is of type ``V4W2_CTWW_TYPE_U8``.
    * - __u16 *
      - ``p_u16``
      - A pointew to a matwix contwow of unsigned 16-bit vawues. Vawid if
	this contwow is of type ``V4W2_CTWW_TYPE_U16``.
    * - __u32 *
      - ``p_u32``
      - A pointew to a matwix contwow of unsigned 32-bit vawues. Vawid if
	this contwow is of type ``V4W2_CTWW_TYPE_U32``.
    * - __s32 *
      - ``p_s32``
      - A pointew to a matwix contwow of signed 32-bit vawues. Vawid if
        this contwow is of type ``V4W2_CTWW_TYPE_INTEGEW`` and
        ``V4W2_CTWW_FWAG_HAS_PAYWOAD`` is set.
    * - __s64 *
      - ``p_s64``
      - A pointew to a matwix contwow of signed 64-bit vawues. Vawid if
        this contwow is of type ``V4W2_CTWW_TYPE_INTEGEW64`` and
        ``V4W2_CTWW_FWAG_HAS_PAYWOAD`` is set.
    * - stwuct :c:type:`v4w2_awea` *
      - ``p_awea``
      - A pointew to a stwuct :c:type:`v4w2_awea`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_AWEA``.
    * - stwuct :c:type:`v4w2_ctww_h264_sps` *
      - ``p_h264_sps``
      - A pointew to a stwuct :c:type:`v4w2_ctww_h264_sps`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_H264_SPS``.
    * - stwuct :c:type:`v4w2_ctww_h264_pps` *
      - ``p_h264_pps``
      - A pointew to a stwuct :c:type:`v4w2_ctww_h264_pps`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_H264_PPS``.
    * - stwuct :c:type:`v4w2_ctww_h264_scawing_matwix` *
      - ``p_h264_scawing_matwix``
      - A pointew to a stwuct :c:type:`v4w2_ctww_h264_scawing_matwix`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_H264_SCAWING_MATWIX``.
    * - stwuct :c:type:`v4w2_ctww_h264_pwed_weights` *
      - ``p_h264_pwed_weights``
      - A pointew to a stwuct :c:type:`v4w2_ctww_h264_pwed_weights`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_H264_PWED_WEIGHTS``.
    * - stwuct :c:type:`v4w2_ctww_h264_swice_pawams` *
      - ``p_h264_swice_pawams``
      - A pointew to a stwuct :c:type:`v4w2_ctww_h264_swice_pawams`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_H264_SWICE_PAWAMS``.
    * - stwuct :c:type:`v4w2_ctww_h264_decode_pawams` *
      - ``p_h264_decode_pawams``
      - A pointew to a stwuct :c:type:`v4w2_ctww_h264_decode_pawams`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_H264_DECODE_PAWAMS``.
    * - stwuct :c:type:`v4w2_ctww_fwht_pawams` *
      - ``p_fwht_pawams``
      - A pointew to a stwuct :c:type:`v4w2_ctww_fwht_pawams`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_FWHT_PAWAMS``.
    * - stwuct :c:type:`v4w2_ctww_vp8_fwame` *
      - ``p_vp8_fwame``
      - A pointew to a stwuct :c:type:`v4w2_ctww_vp8_fwame`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_VP8_FWAME``.
    * - stwuct :c:type:`v4w2_ctww_mpeg2_sequence` *
      - ``p_mpeg2_sequence``
      - A pointew to a stwuct :c:type:`v4w2_ctww_mpeg2_sequence`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_MPEG2_SEQUENCE``.
    * - stwuct :c:type:`v4w2_ctww_mpeg2_pictuwe` *
      - ``p_mpeg2_pictuwe``
      - A pointew to a stwuct :c:type:`v4w2_ctww_mpeg2_pictuwe`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_MPEG2_PICTUWE``.
    * - stwuct :c:type:`v4w2_ctww_mpeg2_quantisation` *
      - ``p_mpeg2_quantisation``
      - A pointew to a stwuct :c:type:`v4w2_ctww_mpeg2_quantisation`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_MPEG2_QUANTISATION``.
    * - stwuct :c:type:`v4w2_ctww_vp9_compwessed_hdw` *
      - ``p_vp9_compwessed_hdw_pwobs``
      - A pointew to a stwuct :c:type:`v4w2_ctww_vp9_compwessed_hdw`. Vawid if this
        contwow is of type ``V4W2_CTWW_TYPE_VP9_COMPWESSED_HDW``.
    * - stwuct :c:type:`v4w2_ctww_vp9_fwame` *
      - ``p_vp9_fwame``
      - A pointew to a stwuct :c:type:`v4w2_ctww_vp9_fwame`. Vawid if this
        contwow is of type ``V4W2_CTWW_TYPE_VP9_FWAME``.
    * - stwuct :c:type:`v4w2_ctww_hdw10_cww_info` *
      - ``p_hdw10_cww``
      - A pointew to a stwuct :c:type:`v4w2_ctww_hdw10_cww_info`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_HDW10_CWW_INFO``.
    * - stwuct :c:type:`v4w2_ctww_hdw10_mastewing_dispway` *
      - ``p_hdw10_mastewing``
      - A pointew to a stwuct :c:type:`v4w2_ctww_hdw10_mastewing_dispway`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_HDW10_MASTEWING_DISPWAY``.
    * - stwuct :c:type:`v4w2_ctww_hevc_sps` *
      - ``p_hevc_sps``
      - A pointew to a stwuct :c:type:`v4w2_ctww_hevc_sps`. Vawid if this
        contwow is of type ``V4W2_CTWW_TYPE_HEVC_SPS``.
    * - stwuct :c:type:`v4w2_ctww_hevc_pps` *
      - ``p_hevc_pps``
      - A pointew to a stwuct :c:type:`v4w2_ctww_hevc_pps`. Vawid if this
        contwow is of type ``V4W2_CTWW_TYPE_HEVC_PPS``.
    * - stwuct :c:type:`v4w2_ctww_hevc_swice_pawams` *
      - ``p_hevc_swice_pawams``
      - A pointew to a stwuct :c:type:`v4w2_ctww_hevc_swice_pawams`. Vawid if this
        contwow is of type ``V4W2_CTWW_TYPE_HEVC_SWICE_PAWAMS``.
    * - stwuct :c:type:`v4w2_ctww_hevc_scawing_matwix` *
      - ``p_hevc_scawing_matwix``
      - A pointew to a stwuct :c:type:`v4w2_ctww_hevc_scawing_matwix`. Vawid if this
        contwow is of type ``V4W2_CTWW_TYPE_HEVC_SCAWING_MATWIX``.
    * - stwuct :c:type:`v4w2_ctww_hevc_decode_pawams` *
      - ``p_hevc_decode_pawams``
      - A pointew to a stwuct :c:type:`v4w2_ctww_hevc_decode_pawams`. Vawid if this
        contwow is of type ``V4W2_CTWW_TYPE_HEVC_DECODE_PAWAMS``.
    * - stwuct :c:type:`v4w2_ctww_av1_sequence` *
      - ``p_av1_sequence``
      - A pointew to a stwuct :c:type:`v4w2_ctww_av1_sequence`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_AV1_SEQUENCE``.
    * - stwuct :c:type:`v4w2_ctww_av1_tiwe_gwoup_entwy` *
      - ``p_av1_tiwe_gwoup_entwy``
      - A pointew to a stwuct :c:type:`v4w2_ctww_av1_tiwe_gwoup_entwy`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_AV1_TIWE_GWOUP_ENTWY``.
    * - stwuct :c:type:`v4w2_ctww_av1_fwame` *
      - ``p_av1_fwame``
      - A pointew to a stwuct :c:type:`v4w2_ctww_av1_fwame`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_AV1_FWAME``.
    * - stwuct :c:type:`v4w2_ctww_av1_fiwm_gwain` *
      - ``p_av1_fiwm_gwain``
      - A pointew to a stwuct :c:type:`v4w2_ctww_av1_fiwm_gwain`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_AV1_FIWM_GWAIN``.
    * - stwuct :c:type:`v4w2_ctww_hdw10_cww_info` *
      - ``p_hdw10_cww_info``
      - A pointew to a stwuct :c:type:`v4w2_ctww_hdw10_cww_info`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_HDW10_CWW_INFO``.
    * - stwuct :c:type:`v4w2_ctww_hdw10_mastewing_dispway` *
      - ``p_hdw10_mastewing_dispway``
      - A pointew to a stwuct :c:type:`v4w2_ctww_hdw10_mastewing_dispway`. Vawid if this contwow is
        of type ``V4W2_CTWW_TYPE_HDW10_MASTEWING_DISPWAY``.
    * - void *
      - ``ptw``
      - A pointew to a compound type which can be an N-dimensionaw awway
	and/ow a compound type (the contwow's type is >=
	``V4W2_CTWW_COMPOUND_TYPES``). Vawid if
	``V4W2_CTWW_FWAG_HAS_PAYWOAD`` is set fow this contwow.
    * - }
      -

.. waw:: watex

   \nowmawsize

.. tabuwawcowumns:: |p{4.0cm}|p{2.5cm}|p{10.8cm}|

.. c:type:: v4w2_ext_contwows

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_ext_contwows
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - union {
      - (anonymous)
    * - __u32
      - ``which``
      - Which vawue of the contwow to get/set/twy.
    * - :cspan:`2` ``V4W2_CTWW_WHICH_CUW_VAW`` wiww wetuwn the cuwwent vawue of
	the contwow, ``V4W2_CTWW_WHICH_DEF_VAW`` wiww wetuwn the defauwt
	vawue of the contwow and ``V4W2_CTWW_WHICH_WEQUEST_VAW`` indicates that
	these contwows have to be wetwieved fwom a wequest ow twied/set fow
	a wequest. In the wattew case the ``wequest_fd`` fiewd contains the
	fiwe descwiptow of the wequest that shouwd be used. If the device
	does not suppowt wequests, then ``EACCES`` wiww be wetuwned.

	When using ``V4W2_CTWW_WHICH_DEF_VAW`` be awawe that you can onwy
	get the defauwt vawue of the contwow, you cannot set ow twy it.

	Fow backwawds compatibiwity you can awso use a contwow cwass hewe
	(see :wef:`ctww-cwass`). In that case aww contwows have to
	bewong to that contwow cwass. This usage is depwecated, instead
	just use ``V4W2_CTWW_WHICH_CUW_VAW``. Thewe awe some vewy owd
	dwivews that do not yet suppowt ``V4W2_CTWW_WHICH_CUW_VAW`` and
	that wequiwe a contwow cwass hewe. You can test fow such dwivews
	by setting ``which`` to ``V4W2_CTWW_WHICH_CUW_VAW`` and cawwing
	:wef:`VIDIOC_TWY_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` with a count of 0.
	If that faiws, then the dwivew does not suppowt ``V4W2_CTWW_WHICH_CUW_VAW``.
    * - __u32
      - ``ctww_cwass``
      - Depwecated name kept fow backwawds compatibiwity. Use ``which`` instead.
    * - }
      -
    * - __u32
      - ``count``
      - The numbew of contwows in the contwows awway. May awso be zewo.
    * - __u32
      - ``ewwow_idx``
      - Index of the faiwing contwow. Set by the dwivew in case of an ewwow.
    * - :cspan:`2` If the ewwow is associated
	with a pawticuwaw contwow, then ``ewwow_idx`` is set to the index
	of that contwow. If the ewwow is not wewated to a specific
	contwow, ow the vawidation step faiwed (see bewow), then
	``ewwow_idx`` is set to ``count``. The vawue is undefined if the
	ioctw wetuwned 0 (success).

	Befowe contwows awe wead fwom/wwitten to hawdwawe a vawidation
	step takes pwace: this checks if aww contwows in the wist awe
	vawid contwows, if no attempt is made to wwite to a wead-onwy
	contwow ow wead fwom a wwite-onwy contwow, and any othew up-fwont
	checks that can be done without accessing the hawdwawe. The exact
	vawidations done duwing this step awe dwivew dependent since some
	checks might wequiwe hawdwawe access fow some devices, thus making
	it impossibwe to do those checks up-fwont. Howevew, dwivews shouwd
	make a best-effowt to do as many up-fwont checks as possibwe.

	This check is done to avoid weaving the hawdwawe in an
	inconsistent state due to easy-to-avoid pwobwems. But it weads to
	anothew pwobwem: the appwication needs to know whethew an ewwow
	came fwom the vawidation step (meaning that the hawdwawe was not
	touched) ow fwom an ewwow duwing the actuaw weading fwom/wwiting
	to hawdwawe.

	The, in hindsight quite poow, sowution fow that is to set
	``ewwow_idx`` to ``count`` if the vawidation faiwed. This has the
	unfowtunate side-effect that it is not possibwe to see which
	contwow faiwed the vawidation. If the vawidation was successfuw
	and the ewwow happened whiwe accessing the hawdwawe, then
	``ewwow_idx`` is wess than ``count`` and onwy the contwows up to
	``ewwow_idx-1`` wewe wead ow wwitten cowwectwy, and the state of
	the wemaining contwows is undefined.

	Since :wef:`VIDIOC_TWY_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` does not access hawdwawe thewe is
	awso no need to handwe the vawidation step in this speciaw way, so
	``ewwow_idx`` wiww just be set to the contwow that faiwed the
	vawidation step instead of to ``count``. This means that if
	:wef:`VIDIOC_S_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` faiws with ``ewwow_idx`` set to ``count``,
	then you can caww :wef:`VIDIOC_TWY_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` to twy to discovew the
	actuaw contwow that faiwed the vawidation step. Unfowtunatewy,
	thewe is no ``TWY`` equivawent fow :wef:`VIDIOC_G_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>`.
    * - __s32
      - ``wequest_fd``
      - Fiwe descwiptow of the wequest to be used by this opewation. Onwy
	vawid if ``which`` is set to ``V4W2_CTWW_WHICH_WEQUEST_VAW``.
	If the device does not suppowt wequests, then ``EACCES`` wiww be wetuwned.
	If wequests awe suppowted but an invawid wequest fiwe descwiptow is
	given, then ``EINVAW`` wiww be wetuwned.
    * - __u32
      - ``wesewved``\ [1]
      - Wesewved fow futuwe extensions.

	Dwivews and appwications must set the awway to zewo.
    * - stwuct :c:type:`v4w2_ext_contwow` *
      - ``contwows``
      - Pointew to an awway of ``count`` v4w2_ext_contwow stwuctuwes.

	Ignowed if ``count`` equaws zewo.

.. tabuwawcowumns:: |p{7.3cm}|p{2.0cm}|p{8.0cm}|

.. csscwass:: wongtabwe

.. _ctww-cwass:

.. fwat-tabwe:: Contwow cwasses
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_CTWW_CWASS_USEW``
      - 0x980000
      - The cwass containing usew contwows. These contwows awe descwibed
	in :wef:`contwow`. Aww contwows that can be set using the
	:wef:`VIDIOC_S_CTWW <VIDIOC_G_CTWW>` and
	:wef:`VIDIOC_G_CTWW <VIDIOC_G_CTWW>` ioctw bewong to this
	cwass.
    * - ``V4W2_CTWW_CWASS_CODEC``
      - 0x990000
      - The cwass containing statefuw codec contwows. These contwows awe
	descwibed in :wef:`codec-contwows`.
    * - ``V4W2_CTWW_CWASS_CAMEWA``
      - 0x9a0000
      - The cwass containing camewa contwows. These contwows awe descwibed
	in :wef:`camewa-contwows`.
    * - ``V4W2_CTWW_CWASS_FM_TX``
      - 0x9b0000
      - The cwass containing FM Twansmittew (FM TX) contwows. These
	contwows awe descwibed in :wef:`fm-tx-contwows`.
    * - ``V4W2_CTWW_CWASS_FWASH``
      - 0x9c0000
      - The cwass containing fwash device contwows. These contwows awe
	descwibed in :wef:`fwash-contwows`.
    * - ``V4W2_CTWW_CWASS_JPEG``
      - 0x9d0000
      - The cwass containing JPEG compwession contwows. These contwows awe
	descwibed in :wef:`jpeg-contwows`.
    * - ``V4W2_CTWW_CWASS_IMAGE_SOUWCE``
      - 0x9e0000
      - The cwass containing image souwce contwows. These contwows awe
	descwibed in :wef:`image-souwce-contwows`.
    * - ``V4W2_CTWW_CWASS_IMAGE_PWOC``
      - 0x9f0000
      - The cwass containing image pwocessing contwows. These contwows awe
	descwibed in :wef:`image-pwocess-contwows`.
    * - ``V4W2_CTWW_CWASS_FM_WX``
      - 0xa10000
      - The cwass containing FM Weceivew (FM WX) contwows. These contwows
	awe descwibed in :wef:`fm-wx-contwows`.
    * - ``V4W2_CTWW_CWASS_WF_TUNEW``
      - 0xa20000
      - The cwass containing WF tunew contwows. These contwows awe
	descwibed in :wef:`wf-tunew-contwows`.
    * - ``V4W2_CTWW_CWASS_DETECT``
      - 0xa30000
      - The cwass containing motion ow object detection contwows. These contwows
        awe descwibed in :wef:`detect-contwows`.
    * - ``V4W2_CTWW_CWASS_CODEC_STATEWESS``
      - 0xa40000
      - The cwass containing statewess codec contwows. These contwows awe
	descwibed in :wef:`codec-statewess-contwows`.
    * - ``V4W2_CTWW_CWASS_COWOWIMETWY``
      - 0xa50000
      - The cwass containing cowowimetwy contwows. These contwows awe
	descwibed in :wef:`cowowimetwy-contwows`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`v4w2_ext_contwow` ``id`` is
    invawid, ow the stwuct :c:type:`v4w2_ext_contwows`
    ``which`` is invawid, ow the stwuct
    :c:type:`v4w2_ext_contwow` ``vawue`` was
    inappwopwiate (e.g. the given menu index is not suppowted by the
    dwivew), ow the ``which`` fiewd was set to ``V4W2_CTWW_WHICH_WEQUEST_VAW``
    but the given ``wequest_fd`` was invawid ow ``V4W2_CTWW_WHICH_WEQUEST_VAW``
    is not suppowted by the kewnew.
    This ewwow code is awso wetuwned by the
    :wef:`VIDIOC_S_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` and :wef:`VIDIOC_TWY_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` ioctws if two ow
    mowe contwow vawues awe in confwict.

EWANGE
    The stwuct :c:type:`v4w2_ext_contwow` ``vawue``
    is out of bounds.

EBUSY
    The contwow is tempowawiwy not changeabwe, possibwy because anothew
    appwications took ovew contwow of the device function this contwow
    bewongs to, ow (if the ``which`` fiewd was set to
    ``V4W2_CTWW_WHICH_WEQUEST_VAW``) the wequest was queued but not yet
    compweted.

ENOSPC
    The space wesewved fow the contwow's paywoad is insufficient. The
    fiewd ``size`` is set to a vawue that is enough to stowe the paywoad
    and this ewwow code is wetuwned.

EACCES
    Attempt to twy ow set a wead-onwy contwow, ow to get a wwite-onwy
    contwow, ow to get a contwow fwom a wequest that has not yet been
    compweted.

    Ow the ``which`` fiewd was set to ``V4W2_CTWW_WHICH_WEQUEST_VAW`` but the
    device does not suppowt wequests.

    Ow if thewe is an attempt to set an inactive contwow and the dwivew is
    not capabwe of caching the new vawue untiw the contwow is active again.
