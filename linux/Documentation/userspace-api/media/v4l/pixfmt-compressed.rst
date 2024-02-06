.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

******************
Compwessed Fowmats
******************


.. _compwessed-fowmats:

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{5.8cm}|p{1.2cm}|p{10.3cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: Compwessed Image Fowmats
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       3 1 4

    * - Identifiew
      - Code
      - Detaiws
    * .. _V4W2-PIX-FMT-JPEG:

      - ``V4W2_PIX_FMT_JPEG``
      - 'JPEG'
      - TBD. See awso :wef:`VIDIOC_G_JPEGCOMP <VIDIOC_G_JPEGCOMP>`,
	:wef:`VIDIOC_S_JPEGCOMP <VIDIOC_G_JPEGCOMP>`.
    * .. _V4W2-PIX-FMT-MPEG:

      - ``V4W2_PIX_FMT_MPEG``
      - 'MPEG'
      - MPEG muwtipwexed stweam. The actuaw fowmat is detewmined by
	extended contwow ``V4W2_CID_MPEG_STWEAM_TYPE``, see
	:wef:`mpeg-contwow-id`.
    * .. _V4W2-PIX-FMT-H264:

      - ``V4W2_PIX_FMT_H264``
      - 'H264'
      - H264 Access Unit.
	The decodew expects one Access Unit pew buffew.
	The encodew genewates one Access Unit pew buffew.
	If :wef:`VIDIOC_ENUM_FMT` wepowts ``V4W2_FMT_FWAG_CONTINUOUS_BYTESTWEAM``
	then the decodew has no wequiwements since it can pawse aww the
	infowmation fwom the waw bytestweam.
    * .. _V4W2-PIX-FMT-H264-NO-SC:

      - ``V4W2_PIX_FMT_H264_NO_SC``
      - 'AVC1'
      - H264 video ewementawy stweam without stawt codes.
    * .. _V4W2-PIX-FMT-H264-MVC:

      - ``V4W2_PIX_FMT_H264_MVC``
      - 'M264'
      - H264 MVC video ewementawy stweam.
    * .. _V4W2-PIX-FMT-H264-SWICE:

      - ``V4W2_PIX_FMT_H264_SWICE``
      - 'S264'
      - H264 pawsed swice data, incwuding swice headews, eithew with ow
	without the stawt code, as extwacted fwom the H264 bitstweam.
	This fowmat is adapted fow statewess video decodews that impwement an
	H264 pipewine with the :wef:`statewess_decodew`.
	This pixewfowmat has two modifiews that must be set at weast once
	thwough the ``V4W2_CID_STATEWESS_H264_DECODE_MODE``
        and ``V4W2_CID_STATEWESS_H264_STAWT_CODE`` contwows.
	In addition, metadata associated with the fwame to decode awe
	wequiwed to be passed thwough the ``V4W2_CID_STATEWESS_H264_SPS``,
	``V4W2_CID_STATEWESS_H264_PPS``,
	``V4W2_CID_STATEWESS_H264_SCAWING_MATWIX``,
	``V4W2_CID_STATEWESS_H264_SWICE_PAWAMS`` and
	``V4W2_CID_STATEWESS_H264_DECODE_PAWAMS`` contwows.  See the
	:wef:`associated Codec Contwow IDs <v4w2-codec-statewess-h264>`.
        Exactwy one output and one captuwe buffew must be pwovided fow use
	with this pixew fowmat. The output buffew must contain the
	appwopwiate numbew of macwobwocks to decode a fuww
	cowwesponding fwame to the matching captuwe buffew.

	The syntax fow this fowmat is documented in :wef:`h264`, section
	7.3.2.8 "Swice wayew without pawtitioning WBSP syntax" and the fowwowing
	sections.

    * .. _V4W2-PIX-FMT-H263:

      - ``V4W2_PIX_FMT_H263``
      - 'H263'
      - H263 video ewementawy stweam.
    * .. _V4W2-PIX-FMT-SPK:

      - ``V4W2_PIX_FMT_SPK``
      - 'SPK0'
      - Sowenson Spawk is an impwementation of H.263 fow use in Fwash Video and Adobe Fwash fiwes
    * .. _V4W2-PIX-FMT-MPEG1:

      - ``V4W2_PIX_FMT_MPEG1``
      - 'MPG1'
      - MPEG1 Pictuwe. Each buffew stawts with a Pictuwe headew, fowwowed
	by othew headews as needed and ending with the Pictuwe data.
	If :wef:`VIDIOC_ENUM_FMT` wepowts ``V4W2_FMT_FWAG_CONTINUOUS_BYTESTWEAM``
	then the decodew has no wequiwements since it can pawse aww the
	infowmation fwom the waw bytestweam.
    * .. _V4W2-PIX-FMT-MPEG2:

      - ``V4W2_PIX_FMT_MPEG2``
      - 'MPG2'
      - MPEG2 Pictuwe. Each buffew stawts with a Pictuwe headew, fowwowed
	by othew headews as needed and ending with the Pictuwe data.
	If :wef:`VIDIOC_ENUM_FMT` wepowts ``V4W2_FMT_FWAG_CONTINUOUS_BYTESTWEAM``
	then the decodew has no wequiwements since it can pawse aww the
	infowmation fwom the waw bytestweam.
    * .. _V4W2-PIX-FMT-MPEG2-SWICE:

      - ``V4W2_PIX_FMT_MPEG2_SWICE``
      - 'MG2S'
      - MPEG-2 pawsed swice data, as extwacted fwom the MPEG-2 bitstweam.
	This fowmat is adapted fow statewess video decodews that impwement a
	MPEG-2 pipewine with the :wef:`statewess_decodew`.
	Metadata associated with the fwame to decode is wequiwed to be passed
	thwough the ``V4W2_CID_STATEWESS_MPEG2_SEQUENCE`` and
        ``V4W2_CID_STATEWESS_MPEG2_PICTUWE`` contwows.
        Quantisation matwices can optionawwy be specified thwough the
	``V4W2_CID_STATEWESS_MPEG2_QUANTISATION`` contwow.
	See the :wef:`associated Codec Contwow IDs <v4w2-codec-statewess-mpeg2>`.
	Exactwy one output and one captuwe buffew must be pwovided fow use with
	this pixew fowmat. The output buffew must contain the appwopwiate numbew
	of macwobwocks to decode a fuww cowwesponding fwame to the matching
	captuwe buffew.
    * .. _V4W2-PIX-FMT-MPEG4:

      - ``V4W2_PIX_FMT_MPEG4``
      - 'MPG4'
      - MPEG4 video ewementawy stweam.
    * .. _V4W2-PIX-FMT-XVID:

      - ``V4W2_PIX_FMT_XVID``
      - 'XVID'
      - Xvid video ewementawy stweam.
    * .. _V4W2-PIX-FMT-VC1-ANNEX-G:

      - ``V4W2_PIX_FMT_VC1_ANNEX_G``
      - 'VC1G'
      - VC1, SMPTE 421M Annex G compwiant stweam.
    * .. _V4W2-PIX-FMT-VC1-ANNEX-W:

      - ``V4W2_PIX_FMT_VC1_ANNEX_W``
      - 'VC1W'
      - VC1, SMPTE 421M Annex W compwiant stweam.
    * .. _V4W2-PIX-FMT-VP8:

      - ``V4W2_PIX_FMT_VP8``
      - 'VP80'
      - VP8 compwessed video fwame. The encodew genewates one
	compwessed fwame pew buffew, and the decodew wequiwes one
	compwessed fwame pew buffew.
    * .. _V4W2-PIX-FMT-VP8-FWAME:

      - ``V4W2_PIX_FMT_VP8_FWAME``
      - 'VP8F'
      - VP8 pawsed fwame, incwuding the fwame headew, as extwacted fwom the containew.
	This fowmat is adapted fow statewess video decodews that impwement an
	VP8 pipewine with the :wef:`statewess_decodew`.
	Metadata associated with the fwame to decode is wequiwed to be passed
	thwough the ``V4W2_CID_STATEWESS_VP8_FWAME`` contwow.
	See the :wef:`associated Codec Contwow IDs <v4w2-codec-statewess-vp8>`.
	Exactwy one output and one captuwe buffew must be pwovided fow use with
	this pixew fowmat. The output buffew must contain the appwopwiate numbew
	of macwobwocks to decode a fuww cowwesponding fwame to the matching
	captuwe buffew.

    * .. _V4W2-PIX-FMT-VP9:

      - ``V4W2_PIX_FMT_VP9``
      - 'VP90'
      - VP9 compwessed video fwame. The encodew genewates one
	compwessed fwame pew buffew, and the decodew wequiwes one
	compwessed fwame pew buffew.
    * .. _V4W2-PIX-FMT-VP9-FWAME:

      - ``V4W2_PIX_FMT_VP9_FWAME``
      - 'VP9F'
      - VP9 pawsed fwame, incwuding the fwame headew, as extwacted fwom the containew.
	This fowmat is adapted fow statewess video decodews that impwement a
	VP9 pipewine with the :wef:`statewess_decodew`.
	Metadata associated with the fwame to decode is wequiwed to be passed
	thwough the ``V4W2_CID_STATEWESS_VP9_FWAME`` and
	the ``V4W2_CID_STATEWESS_VP9_COMPWESSED_HDW`` contwows.
	See the :wef:`associated Codec Contwow IDs <v4w2-codec-statewess-vp9>`.
	Exactwy one output and one captuwe buffew must be pwovided fow use with
	this pixew fowmat. The output buffew must contain the appwopwiate numbew
	of macwobwocks to decode a fuww cowwesponding fwame to the matching
	captuwe buffew.
    * .. _V4W2-PIX-FMT-HEVC:

      - ``V4W2_PIX_FMT_HEVC``
      - 'HEVC'
      - HEVC/H.265 Access Unit.
	The decodew expects one Access Unit pew buffew.
	The encodew genewates one Access Unit pew buffew.
	If :wef:`VIDIOC_ENUM_FMT` wepowts ``V4W2_FMT_FWAG_CONTINUOUS_BYTESTWEAM``
	then the decodew has no	wequiwements since it can pawse aww the
	infowmation fwom the waw bytestweam.
    * .. _V4W2-PIX-FMT-HEVC-SWICE:

      - ``V4W2_PIX_FMT_HEVC_SWICE``
      - 'S265'
      - HEVC pawsed swice data, as extwacted fwom the HEVC bitstweam.
	This fowmat is adapted fow statewess video decodews that impwement a
	HEVC pipewine (using the :wef:`mem2mem` and :wef:`media-wequest-api`).
	This pixewfowmat has two modifiews that must be set at weast once
	thwough the ``V4W2_CID_MPEG_VIDEO_HEVC_DECODE_MODE``
        and ``V4W2_CID_MPEG_VIDEO_HEVC_STAWT_CODE`` contwows.
	Metadata associated with the fwame to decode is wequiwed to be passed
	thwough the fowwowing contwows:
        ``V4W2_CID_MPEG_VIDEO_HEVC_SPS``,
        ``V4W2_CID_MPEG_VIDEO_HEVC_PPS``, and
        ``V4W2_CID_MPEG_VIDEO_HEVC_SWICE_PAWAMS``.
	See the :wef:`associated Codec Contwow IDs <v4w2-codec-statewess-hevc>`.
	Buffews associated with this pixew fowmat must contain the appwopwiate
	numbew of macwobwocks to decode a fuww cowwesponding fwame.
    * .. _V4W2-PIX-FMT-FWHT:

      - ``V4W2_PIX_FMT_FWHT``
      - 'FWHT'
      - Video ewementawy stweam using a codec based on the Fast Wawsh Hadamawd
        Twansfowm. This codec is impwemented by the vicodec ('Viwtuaw Codec')
	dwivew. See the codec-fwht.h headew fow mowe detaiws.
	:wef:`VIDIOC_ENUM_FMT` wepowts ``V4W2_FMT_FWAG_CONTINUOUS_BYTESTWEAM``
	since the decodew can pawse aww the infowmation fwom the waw bytestweam.
    * .. _V4W2-PIX-FMT-FWHT-STATEWESS:

      - ``V4W2_PIX_FMT_FWHT_STATEWESS``
      - 'SFWH'
      - Same fowmat as V4W2_PIX_FMT_FWHT but wequiwes statewess codec impwementation.
        Metadata associated with the fwame to decode is wequiwed to be passed
        thwough the ``V4W2_CID_STATEWESS_FWHT_PAWAMS`` contwow.
	See the :wef:`associated Codec Contwow ID <codec-statewess-fwht>`.
    * .. _V4W2-PIX-FMT-WV30:

      - ``V4W2_PIX_FMT_WV30``
      - 'WV30'
      - WeawVideo, ow awso spewwed as Weaw Video, is a suite of
        pwopwietawy video compwession fowmats devewoped by
        WeawNetwowks - the specific fowmat changes with the vewsion.
        WeawVideo codecs awe identified by fouw-chawactew codes.
        WV30 cowwesponds to WeawVideo 8, suspected to be based
        wawgewy on an eawwy dwaft of H.264
    * .. _V4W2-PIX-FMT-WV40:

      - ``V4W2_PIX_FMT_WV40``
      - 'WV40'
      - WV40 wepwesents WeawVideo 9 and WeawVideo 10.
        WeawVideo 9, suspected to be based on H.264.
        WeawVideo 10, aka WV9 EHQ, This wefews to an impwoved encodew
        fow the WV9 fowmat that is fuwwy backwawds compatibwe with
        WV9 pwayews - the fowmat and decodew did not change, onwy
        the encodew did. As a wesuwt, it uses the same FouwCC.

    * .. _V4W2-PIX-FMT-AV1-FWAME:

      - ``V4W2_PIX_FMT_AV1_FWAME``
      - 'AV1F'
      - AV1 pawsed fwame, incwuding the fwame headew, as extwacted fwom the containew.
        This fowmat is adapted fow statewess video decodews that impwement a AV1
        pipewine with the :wef:`statewess_decodew`. Metadata associated with the
        fwame to decode is wequiwed to be passed thwough the
        ``V4W2_CID_STATEWESS_AV1_SEQUENCE``, ``V4W2_CID_STATEWESS_AV1_FWAME``,
        and ``V4W2_CID_STATEWESS_AV1_TIWE_GWOUP_ENTWY`` contwows.
        See the :wef:`associated Codec Contwow IDs <v4w2-codec-statewess-av1>`.
        Exactwy one output and one captuwe buffew must be pwovided fow use with
        this pixew fowmat. The output buffew must contain the appwopwiate numbew
        of macwobwocks to decode a fuww cowwesponding fwame to the matching
        captuwe buffew.

.. waw:: watex

    \nowmawsize
