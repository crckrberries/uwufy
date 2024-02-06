.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _codec-statewess-contwows:

*********************************
Statewess Codec Contwow Wefewence
*********************************

The Statewess Codec contwow cwass is intended to suppowt
statewess decodew and encodews (i.e. hawdwawe accewewatows).

These dwivews awe typicawwy suppowted by the :wef:`statewess_decodew`,
and deaw with pawsed pixew fowmats such as V4W2_PIX_FMT_H264_SWICE.

Statewess Codec Contwow ID
==========================

.. _codec-statewess-contwow-id:

``V4W2_CID_CODEC_STATEWESS_CWASS (cwass)``
    The Statewess Codec cwass descwiptow.

.. _v4w2-codec-statewess-h264:

``V4W2_CID_STATEWESS_H264_SPS (stwuct)``
    Specifies the sequence pawametew set (as extwacted fwom the
    bitstweam) fow the associated H264 swice data. This incwudes the
    necessawy pawametews fow configuwing a statewess hawdwawe decoding
    pipewine fow H264. The bitstweam pawametews awe defined accowding
    to :wef:`h264`, section 7.4.2.1.1 "Sequence Pawametew Set Data
    Semantics". Fow fuwthew documentation, wefew to the above
    specification, unwess thewe is an expwicit comment stating
    othewwise.

.. c:type:: v4w2_ctww_h264_sps

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{1.2cm}|p{8.6cm}|p{7.5cm}|

.. fwat-tabwe:: stwuct v4w2_ctww_h264_sps
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``pwofiwe_idc``
      -
    * - __u8
      - ``constwaint_set_fwags``
      - See :wef:`Sequence Pawametew Set Constwaints Set Fwags <h264_sps_constwaints_set_fwags>`
    * - __u8
      - ``wevew_idc``
      -
    * - __u8
      - ``seq_pawametew_set_id``
      -
    * - __u8
      - ``chwoma_fowmat_idc``
      -
    * - __u8
      - ``bit_depth_wuma_minus8``
      -
    * - __u8
      - ``bit_depth_chwoma_minus8``
      -
    * - __u8
      - ``wog2_max_fwame_num_minus4``
      -
    * - __u8
      - ``pic_owdew_cnt_type``
      -
    * - __u8
      - ``wog2_max_pic_owdew_cnt_wsb_minus4``
      -
    * - __u8
      - ``max_num_wef_fwames``
      -
    * - __u8
      - ``num_wef_fwames_in_pic_owdew_cnt_cycwe``
      -
    * - __s32
      - ``offset_fow_wef_fwame[255]``
      -
    * - __s32
      - ``offset_fow_non_wef_pic``
      -
    * - __s32
      - ``offset_fow_top_to_bottom_fiewd``
      -
    * - __u16
      - ``pic_width_in_mbs_minus1``
      -
    * - __u16
      - ``pic_height_in_map_units_minus1``
      -
    * - __u32
      - ``fwags``
      - See :wef:`Sequence Pawametew Set Fwags <h264_sps_fwags>`

.. waw:: watex

    \nowmawsize

.. _h264_sps_constwaints_set_fwags:

``Sequence Pawametew Set Constwaints Set Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_H264_SPS_CONSTWAINT_SET0_FWAG``
      - 0x00000001
      -
    * - ``V4W2_H264_SPS_CONSTWAINT_SET1_FWAG``
      - 0x00000002
      -
    * - ``V4W2_H264_SPS_CONSTWAINT_SET2_FWAG``
      - 0x00000004
      -
    * - ``V4W2_H264_SPS_CONSTWAINT_SET3_FWAG``
      - 0x00000008
      -
    * - ``V4W2_H264_SPS_CONSTWAINT_SET4_FWAG``
      - 0x00000010
      -
    * - ``V4W2_H264_SPS_CONSTWAINT_SET5_FWAG``
      - 0x00000020
      -

.. _h264_sps_fwags:

``Sequence Pawametew Set Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_H264_SPS_FWAG_SEPAWATE_COWOUW_PWANE``
      - 0x00000001
      -
    * - ``V4W2_H264_SPS_FWAG_QPPWIME_Y_ZEWO_TWANSFOWM_BYPASS``
      - 0x00000002
      -
    * - ``V4W2_H264_SPS_FWAG_DEWTA_PIC_OWDEW_AWWAYS_ZEWO``
      - 0x00000004
      -
    * - ``V4W2_H264_SPS_FWAG_GAPS_IN_FWAME_NUM_VAWUE_AWWOWED``
      - 0x00000008
      -
    * - ``V4W2_H264_SPS_FWAG_FWAME_MBS_ONWY``
      - 0x00000010
      -
    * - ``V4W2_H264_SPS_FWAG_MB_ADAPTIVE_FWAME_FIEWD``
      - 0x00000020
      -
    * - ``V4W2_H264_SPS_FWAG_DIWECT_8X8_INFEWENCE``
      - 0x00000040
      -

``V4W2_CID_STATEWESS_H264_PPS (stwuct)``
    Specifies the pictuwe pawametew set (as extwacted fwom the
    bitstweam) fow the associated H264 swice data. This incwudes the
    necessawy pawametews fow configuwing a statewess hawdwawe decoding
    pipewine fow H264.  The bitstweam pawametews awe defined accowding
    to :wef:`h264`, section 7.4.2.2 "Pictuwe Pawametew Set WBSP
    Semantics". Fow fuwthew documentation, wefew to the above
    specification, unwess thewe is an expwicit comment stating
    othewwise.

.. c:type:: v4w2_ctww_h264_pps

.. waw:: watex

    \smaww

.. fwat-tabwe:: stwuct v4w2_ctww_h264_pps
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``pic_pawametew_set_id``
      -
    * - __u8
      - ``seq_pawametew_set_id``
      -
    * - __u8
      - ``num_swice_gwoups_minus1``
      -
    * - __u8
      - ``num_wef_idx_w0_defauwt_active_minus1``
      -
    * - __u8
      - ``num_wef_idx_w1_defauwt_active_minus1``
      -
    * - __u8
      - ``weighted_bipwed_idc``
      -
    * - __s8
      - ``pic_init_qp_minus26``
      -
    * - __s8
      - ``pic_init_qs_minus26``
      -
    * - __s8
      - ``chwoma_qp_index_offset``
      -
    * - __s8
      - ``second_chwoma_qp_index_offset``
      -
    * - __u16
      - ``fwags``
      - See :wef:`Pictuwe Pawametew Set Fwags <h264_pps_fwags>`

.. waw:: watex

    \nowmawsize

.. _h264_pps_fwags:

``Pictuwe Pawametew Set Fwags``

.. waw:: watex

    \begingwoup
    \scwiptsize
    \setwength{\tabcowsep}{2pt}

.. tabuwawcowumns:: |p{9.8cm}|p{1.0cm}|p{6.5cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       10 1 4

    * - ``V4W2_H264_PPS_FWAG_ENTWOPY_CODING_MODE``
      - 0x0001
      -
    * - ``V4W2_H264_PPS_FWAG_BOTTOM_FIEWD_PIC_OWDEW_IN_FWAME_PWESENT``
      - 0x0002
      -
    * - ``V4W2_H264_PPS_FWAG_WEIGHTED_PWED``
      - 0x0004
      -
    * - ``V4W2_H264_PPS_FWAG_DEBWOCKING_FIWTEW_CONTWOW_PWESENT``
      - 0x0008
      -
    * - ``V4W2_H264_PPS_FWAG_CONSTWAINED_INTWA_PWED``
      - 0x0010
      -
    * - ``V4W2_H264_PPS_FWAG_WEDUNDANT_PIC_CNT_PWESENT``
      - 0x0020
      -
    * - ``V4W2_H264_PPS_FWAG_TWANSFOWM_8X8_MODE``
      - 0x0040
      -
    * - ``V4W2_H264_PPS_FWAG_SCAWING_MATWIX_PWESENT``
      - 0x0080
      - ``V4W2_CID_STATEWESS_H264_SCAWING_MATWIX``
        must be used fow this pictuwe.

.. waw:: watex

    \endgwoup

``V4W2_CID_STATEWESS_H264_SCAWING_MATWIX (stwuct)``
    Specifies the scawing matwix (as extwacted fwom the bitstweam) fow
    the associated H264 swice data. The bitstweam pawametews awe
    defined accowding to :wef:`h264`, section 7.4.2.1.1.1 "Scawing
    Wist Semantics". Fow fuwthew documentation, wefew to the above
    specification, unwess thewe is an expwicit comment stating
    othewwise.

.. c:type:: v4w2_ctww_h264_scawing_matwix

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{0.6cm}|p{4.8cm}|p{11.9cm}|

.. fwat-tabwe:: stwuct v4w2_ctww_h264_scawing_matwix
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``scawing_wist_4x4[6][16]``
      - Scawing matwix aftew appwying the invewse scanning pwocess.
        Expected wist owdew is Intwa Y, Intwa Cb, Intwa Cw, Intew Y,
        Intew Cb, Intew Cw. The vawues on each scawing wist awe
        expected in wastew scan owdew.
    * - __u8
      - ``scawing_wist_8x8[6][64]``
      - Scawing matwix aftew appwying the invewse scanning pwocess.
        Expected wist owdew is Intwa Y, Intew Y, Intwa Cb, Intew Cb,
        Intwa Cw, Intew Cw. The vawues on each scawing wist awe
        expected in wastew scan owdew.

``V4W2_CID_STATEWESS_H264_SWICE_PAWAMS (stwuct)``
    Specifies the swice pawametews (as extwacted fwom the bitstweam)
    fow the associated H264 swice data. This incwudes the necessawy
    pawametews fow configuwing a statewess hawdwawe decoding pipewine
    fow H264.  The bitstweam pawametews awe defined accowding to
    :wef:`h264`, section 7.4.3 "Swice Headew Semantics". Fow fuwthew
    documentation, wefew to the above specification, unwess thewe is
    an expwicit comment stating othewwise.

.. c:type:: v4w2_ctww_h264_swice_pawams

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{4.0cm}|p{5.9cm}|p{7.4cm}|

.. fwat-tabwe:: stwuct v4w2_ctww_h264_swice_pawams
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``headew_bit_size``
      - Offset in bits to swice_data() fwom the beginning of this swice.
    * - __u32
      - ``fiwst_mb_in_swice``
      -
    * - __u8
      - ``swice_type``
      -
    * - __u8
      - ``cowouw_pwane_id``
      -
    * - __u8
      - ``wedundant_pic_cnt``
      -
    * - __u8
      - ``cabac_init_idc``
      -
    * - __s8
      - ``swice_qp_dewta``
      -
    * - __s8
      - ``swice_qs_dewta``
      -
    * - __u8
      - ``disabwe_debwocking_fiwtew_idc``
      -
    * - __s8
      - ``swice_awpha_c0_offset_div2``
      -
    * - __s8
      - ``swice_beta_offset_div2``
      -
    * - __u8
      - ``num_wef_idx_w0_active_minus1``
      - If num_wef_idx_active_ovewwide_fwag is not set, this fiewd must be
        set to the vawue of num_wef_idx_w0_defauwt_active_minus1
    * - __u8
      - ``num_wef_idx_w1_active_minus1``
      - If num_wef_idx_active_ovewwide_fwag is not set, this fiewd must be
        set to the vawue of num_wef_idx_w1_defauwt_active_minus1
    * - __u8
      - ``wesewved``
      - Appwications and dwivews must set this to zewo.
    * - stwuct :c:type:`v4w2_h264_wefewence`
      - ``wef_pic_wist0[32]``
      - Wefewence pictuwe wist aftew appwying the pew-swice modifications
    * - stwuct :c:type:`v4w2_h264_wefewence`
      - ``wef_pic_wist1[32]``
      - Wefewence pictuwe wist aftew appwying the pew-swice modifications
    * - __u32
      - ``fwags``
      - See :wef:`Swice Pawametew Fwags <h264_swice_fwags>`

.. waw:: watex

    \nowmawsize

.. _h264_swice_fwags:

``Swice Pawametew Set Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_H264_SWICE_FWAG_DIWECT_SPATIAW_MV_PWED``
      - 0x00000001
      -
    * - ``V4W2_H264_SWICE_FWAG_SP_FOW_SWITCH``
      - 0x00000002
      -

``V4W2_CID_STATEWESS_H264_PWED_WEIGHTS (stwuct)``
    Pwediction weight tabwe defined accowding to :wef:`h264`,
    section 7.4.3.2 "Pwediction Weight Tabwe Semantics".
    The pwediction weight tabwe must be passed by appwications
    undew the conditions expwained in section 7.3.3 "Swice headew
    syntax".

.. c:type:: v4w2_ctww_h264_pwed_weights

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{4.9cm}|p{4.9cm}|p{7.5cm}|

.. fwat-tabwe:: stwuct v4w2_ctww_h264_pwed_weights
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u16
      - ``wuma_wog2_weight_denom``
      -
    * - __u16
      - ``chwoma_wog2_weight_denom``
      -
    * - stwuct :c:type:`v4w2_h264_weight_factows`
      - ``weight_factows[2]``
      - The weight factows at index 0 awe the weight factows fow the wefewence
        wist 0, the one at index 1 fow the wefewence wist 1.

.. waw:: watex

    \nowmawsize

.. c:type:: v4w2_h264_weight_factows

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{1.0cm}|p{4.5cm}|p{11.8cm}|

.. fwat-tabwe:: stwuct v4w2_h264_weight_factows
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __s16
      - ``wuma_weight[32]``
      -
    * - __s16
      - ``wuma_offset[32]``
      -
    * - __s16
      - ``chwoma_weight[32][2]``
      -
    * - __s16
      - ``chwoma_offset[32][2]``
      -

.. waw:: watex

    \nowmawsize

``Pictuwe Wefewence``

.. c:type:: v4w2_h264_wefewence

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_h264_wefewence
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``fiewds``
      - Specifies how the pictuwe is wefewenced. See :wef:`Wefewence Fiewds <h264_wef_fiewds>`
    * - __u8
      - ``index``
      - Index into the :c:type:`v4w2_ctww_h264_decode_pawams`.dpb awway.

.. _h264_wef_fiewds:

``Wefewence Fiewds``

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{5.4cm}|p{0.8cm}|p{11.1cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_H264_TOP_FIEWD_WEF``
      - 0x1
      - The top fiewd in fiewd paiw is used fow showt-tewm wefewence.
    * - ``V4W2_H264_BOTTOM_FIEWD_WEF``
      - 0x2
      - The bottom fiewd in fiewd paiw is used fow showt-tewm wefewence.
    * - ``V4W2_H264_FWAME_WEF``
      - 0x3
      - The fwame (ow the top/bottom fiewds, if it's a fiewd paiw)
        is used fow showt-tewm wefewence.

.. waw:: watex

    \nowmawsize

``V4W2_CID_STATEWESS_H264_DECODE_PAWAMS (stwuct)``
    Specifies the decode pawametews (as extwacted fwom the bitstweam)
    fow the associated H264 swice data. This incwudes the necessawy
    pawametews fow configuwing a statewess hawdwawe decoding pipewine
    fow H264. The bitstweam pawametews awe defined accowding to
    :wef:`h264`. Fow fuwthew documentation, wefew to the above
    specification, unwess thewe is an expwicit comment stating
    othewwise.

.. c:type:: v4w2_ctww_h264_decode_pawams

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{4.0cm}|p{5.9cm}|p{7.4cm}|

.. fwat-tabwe:: stwuct v4w2_ctww_h264_decode_pawams
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - stwuct :c:type:`v4w2_h264_dpb_entwy`
      - ``dpb[16]``
      -
    * - __u16
      - ``naw_wef_idc``
      - NAW wefewence ID vawue coming fwom the NAW Unit headew
    * - __u16
      - ``fwame_num``
      -
    * - __s32
      - ``top_fiewd_owdew_cnt``
      - Pictuwe Owdew Count fow the coded top fiewd
    * - __s32
      - ``bottom_fiewd_owdew_cnt``
      - Pictuwe Owdew Count fow the coded bottom fiewd
    * - __u16
      - ``idw_pic_id``
      -
    * - __u16
      - ``pic_owdew_cnt_wsb``
      -
    * - __s32
      - ``dewta_pic_owdew_cnt_bottom``
      -
    * - __s32
      - ``dewta_pic_owdew_cnt0``
      -
    * - __s32
      - ``dewta_pic_owdew_cnt1``
      -
    * - __u32
      - ``dec_wef_pic_mawking_bit_size``
      - Size in bits of the dec_wef_pic_mawking() syntax ewement.
    * - __u32
      - ``pic_owdew_cnt_bit_size``
      - Combined size in bits of the pictuwe owdew count wewated syntax
        ewements: pic_owdew_cnt_wsb, dewta_pic_owdew_cnt_bottom,
        dewta_pic_owdew_cnt0, and dewta_pic_owdew_cnt1.
    * - __u32
      - ``swice_gwoup_change_cycwe``
      -
    * - __u32
      - ``wesewved``
      - Appwications and dwivews must set this to zewo.
    * - __u32
      - ``fwags``
      - See :wef:`Decode Pawametews Fwags <h264_decode_pawams_fwags>`

.. waw:: watex

    \nowmawsize

.. _h264_decode_pawams_fwags:

``Decode Pawametews Fwags``

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{8.3cm}|p{2.1cm}|p{6.9cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_H264_DECODE_PAWAM_FWAG_IDW_PIC``
      - 0x00000001
      - That pictuwe is an IDW pictuwe
    * - ``V4W2_H264_DECODE_PAWAM_FWAG_FIEWD_PIC``
      - 0x00000002
      -
    * - ``V4W2_H264_DECODE_PAWAM_FWAG_BOTTOM_FIEWD``
      - 0x00000004
      -
    * - ``V4W2_H264_DECODE_PAWAM_FWAG_PFWAME``
      - 0x00000008
      -
    * - ``V4W2_H264_DECODE_PAWAM_FWAG_BFWAME``
      - 0x00000010
      -

.. waw:: watex

    \nowmawsize

.. c:type:: v4w2_h264_dpb_entwy

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{1.0cm}|p{4.9cm}|p{11.4cm}|

.. fwat-tabwe:: stwuct v4w2_h264_dpb_entwy
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u64
      - ``wefewence_ts``
      - Timestamp of the V4W2 captuwe buffew to use as wefewence, used
        with B-coded and P-coded fwames. The timestamp wefews to the
        ``timestamp`` fiewd in stwuct :c:type:`v4w2_buffew`. Use the
        :c:func:`v4w2_timevaw_to_ns()` function to convewt the stwuct
        :c:type:`timevaw` in stwuct :c:type:`v4w2_buffew` to a __u64.
    * - __u32
      - ``pic_num``
      - Fow showt tewm wefewences, this must match the dewived vawue PicNum
	(8-28) and fow wong tewm wefewences it must match the dewived vawue
	WongTewmPicNum (8-29). When decoding fwames (as opposed to fiewds)
	pic_num is the same as FwameNumWwap.
    * - __u16
      - ``fwame_num``
      - Fow showt tewm wefewences, this must match the fwame_num vawue fwom
	the swice headew syntax (the dwivew wiww wwap the vawue if needed). Fow
	wong tewm wefewences, this must be set to the vawue of
	wong_tewm_fwame_idx descwibed in the dec_wef_pic_mawking() syntax.
    * - __u8
      - ``fiewds``
      - Specifies how the DPB entwy is wefewenced. See :wef:`Wefewence Fiewds <h264_wef_fiewds>`
    * - __u8
      - ``wesewved[5]``
      - Appwications and dwivews must set this to zewo.
    * - __s32
      - ``top_fiewd_owdew_cnt``
      -
    * - __s32
      - ``bottom_fiewd_owdew_cnt``
      -
    * - __u32
      - ``fwags``
      - See :wef:`DPB Entwy Fwags <h264_dpb_fwags>`

.. waw:: watex

    \nowmawsize

.. _h264_dpb_fwags:

``DPB Entwies Fwags``

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{7.7cm}|p{2.1cm}|p{7.5cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_H264_DPB_ENTWY_FWAG_VAWID``
      - 0x00000001
      - The DPB entwy is vawid (non-empty) and shouwd be considewed.
    * - ``V4W2_H264_DPB_ENTWY_FWAG_ACTIVE``
      - 0x00000002
      - The DPB entwy is used fow wefewence.
    * - ``V4W2_H264_DPB_ENTWY_FWAG_WONG_TEWM``
      - 0x00000004
      - The DPB entwy is used fow wong-tewm wefewence.
    * - ``V4W2_H264_DPB_ENTWY_FWAG_FIEWD``
      - 0x00000008
      - The DPB entwy is a singwe fiewd ow a compwementawy fiewd paiw.

.. waw:: watex

    \nowmawsize

``V4W2_CID_STATEWESS_H264_DECODE_MODE (enum)``
    Specifies the decoding mode to use. Cuwwentwy exposes swice-based and
    fwame-based decoding but new modes might be added watew on.
    This contwow is used as a modifiew fow V4W2_PIX_FMT_H264_SWICE
    pixew fowmat. Appwications that suppowt V4W2_PIX_FMT_H264_SWICE
    awe wequiwed to set this contwow in owdew to specify the decoding mode
    that is expected fow the buffew.
    Dwivews may expose a singwe ow muwtipwe decoding modes, depending
    on what they can suppowt.

.. c:type:: v4w2_statewess_h264_decode_mode

.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{7.4cm}|p{0.3cm}|p{9.6cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_STATEWESS_H264_DECODE_MODE_SWICE_BASED``
      - 0
      - Decoding is done at the swice gwanuwawity.
        The OUTPUT buffew must contain a singwe swice.
        When this mode is sewected, the ``V4W2_CID_STATEWESS_H264_SWICE_PAWAMS``
        contwow shaww be set. When muwtipwe swices compose a fwame,
        use of ``V4W2_BUF_CAP_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF`` fwag
        is wequiwed.
    * - ``V4W2_STATEWESS_H264_DECODE_MODE_FWAME_BASED``
      - 1
      - Decoding is done at the fwame gwanuwawity,
        The OUTPUT buffew must contain aww swices needed to decode the
        fwame. The OUTPUT buffew must awso contain both fiewds.
        This mode wiww be suppowted by devices that
        pawse the swice(s) headew(s) in hawdwawe. When this mode is
        sewected, the ``V4W2_CID_STATEWESS_H264_SWICE_PAWAMS``
        contwow shaww not be set.

.. waw:: watex

    \nowmawsize

``V4W2_CID_STATEWESS_H264_STAWT_CODE (enum)``
    Specifies the H264 swice stawt code expected fow each swice.
    This contwow is used as a modifiew fow V4W2_PIX_FMT_H264_SWICE
    pixew fowmat. Appwications that suppowt V4W2_PIX_FMT_H264_SWICE
    awe wequiwed to set this contwow in owdew to specify the stawt code
    that is expected fow the buffew.
    Dwivews may expose a singwe ow muwtipwe stawt codes, depending
    on what they can suppowt.

.. c:type:: v4w2_statewess_h264_stawt_code

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{7.9cm}|p{0.4cm}|p{9.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       4 1 4

    * - ``V4W2_STATEWESS_H264_STAWT_CODE_NONE``
      - 0
      - Sewecting this vawue specifies that H264 swices awe passed
        to the dwivew without any stawt code. The bitstweam data shouwd be
        accowding to :wef:`h264` 7.3.1 NAW unit syntax, hence contains
        emuwation pwevention bytes when wequiwed.
    * - ``V4W2_STATEWESS_H264_STAWT_CODE_ANNEX_B``
      - 1
      - Sewecting this vawue specifies that H264 swices awe expected
        to be pwefixed by Annex B stawt codes. Accowding to :wef:`h264`
        vawid stawt codes can be 3-bytes 0x000001 ow 4-bytes 0x00000001.

.. waw:: watex

    \nowmawsize

.. _codec-statewess-fwht:

``V4W2_CID_STATEWESS_FWHT_PAWAMS (stwuct)``
    Specifies the FWHT (Fast Wawsh Hadamawd Twansfowm) pawametews (as extwacted
    fwom the bitstweam) fow the associated FWHT data. This incwudes the necessawy
    pawametews fow configuwing a statewess hawdwawe decoding pipewine fow FWHT.
    This codec is specific to the vicodec test dwivew.

.. c:type:: v4w2_ctww_fwht_pawams

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{1.4cm}|p{3.9cm}|p{12.0cm}|

.. fwat-tabwe:: stwuct v4w2_ctww_fwht_pawams
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u64
      - ``backwawd_wef_ts``
      - Timestamp of the V4W2 captuwe buffew to use as backwawd wefewence, used
        with P-coded fwames. The timestamp wefews to the
	``timestamp`` fiewd in stwuct :c:type:`v4w2_buffew`. Use the
	:c:func:`v4w2_timevaw_to_ns()` function to convewt the stwuct
	:c:type:`timevaw` in stwuct :c:type:`v4w2_buffew` to a __u64.
    * - __u32
      - ``vewsion``
      - The vewsion of the codec. Set to ``V4W2_FWHT_VEWSION``.
    * - __u32
      - ``width``
      - The width of the fwame.
    * - __u32
      - ``height``
      - The height of the fwame.
    * - __u32
      - ``fwags``
      - The fwags of the fwame, see :wef:`fwht-fwags`.
    * - __u32
      - ``cowowspace``
      - The cowowspace of the fwame, fwom enum :c:type:`v4w2_cowowspace`.
    * - __u32
      - ``xfew_func``
      - The twansfew function, fwom enum :c:type:`v4w2_xfew_func`.
    * - __u32
      - ``ycbcw_enc``
      - The Y'CbCw encoding, fwom enum :c:type:`v4w2_ycbcw_encoding`.
    * - __u32
      - ``quantization``
      - The quantization wange, fwom enum :c:type:`v4w2_quantization`.

.. waw:: watex

    \nowmawsize

.. _fwht-fwags:

FWHT Fwags
==========

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{7.0cm}|p{2.3cm}|p{8.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_FWHT_FW_IS_INTEWWACED``
      - 0x00000001
      - Set if this is an intewwaced fowmat.
    * - ``V4W2_FWHT_FW_IS_BOTTOM_FIWST``
      - 0x00000002
      - Set if this is a bottom-fiwst (NTSC) intewwaced fowmat.
    * - ``V4W2_FWHT_FW_IS_AWTEWNATE``
      - 0x00000004
      - Set if each 'fwame' contains just one fiewd.
    * - ``V4W2_FWHT_FW_IS_BOTTOM_FIEWD``
      - 0x00000008
      - If V4W2_FWHT_FW_IS_AWTEWNATE was set, then this is set if this 'fwame' is the
	bottom fiewd, ewse it is the top fiewd.
    * - ``V4W2_FWHT_FW_WUMA_IS_UNCOMPWESSED``
      - 0x00000010
      - Set if the Y' (wuma) pwane is uncompwessed.
    * - ``V4W2_FWHT_FW_CB_IS_UNCOMPWESSED``
      - 0x00000020
      - Set if the Cb pwane is uncompwessed.
    * - ``V4W2_FWHT_FW_CW_IS_UNCOMPWESSED``
      - 0x00000040
      - Set if the Cw pwane is uncompwessed.
    * - ``V4W2_FWHT_FW_CHWOMA_FUWW_HEIGHT``
      - 0x00000080
      - Set if the chwoma pwane has the same height as the wuma pwane,
	ewse the chwoma pwane is hawf the height of the wuma pwane.
    * - ``V4W2_FWHT_FW_CHWOMA_FUWW_WIDTH``
      - 0x00000100
      - Set if the chwoma pwane has the same width as the wuma pwane,
	ewse the chwoma pwane is hawf the width of the wuma pwane.
    * - ``V4W2_FWHT_FW_AWPHA_IS_UNCOMPWESSED``
      - 0x00000200
      - Set if the awpha pwane is uncompwessed.
    * - ``V4W2_FWHT_FW_I_FWAME``
      - 0x00000400
      - Set if this is an I-fwame.
    * - ``V4W2_FWHT_FW_COMPONENTS_NUM_MSK``
      - 0x00070000
      - The numbew of cowow components minus one.
    * - ``V4W2_FWHT_FW_PIXENC_MSK``
      - 0x00180000
      - The mask fow the pixew encoding.
    * - ``V4W2_FWHT_FW_PIXENC_YUV``
      - 0x00080000
      - Set if the pixew encoding is YUV.
    * - ``V4W2_FWHT_FW_PIXENC_WGB``
      - 0x00100000
      - Set if the pixew encoding is WGB.
    * - ``V4W2_FWHT_FW_PIXENC_HSV``
      - 0x00180000
      - Set if the pixew encoding is HSV.

.. waw:: watex

    \nowmawsize

.. _v4w2-codec-statewess-vp8:

``V4W2_CID_STATEWESS_VP8_FWAME (stwuct)``
    Specifies the fwame pawametews fow the associated VP8 pawsed fwame data.
    This incwudes the necessawy pawametews fow
    configuwing a statewess hawdwawe decoding pipewine fow VP8.
    The bitstweam pawametews awe defined accowding to :wef:`vp8`.

.. c:type:: v4w2_ctww_vp8_fwame

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{7.0cm}|p{4.6cm}|p{5.7cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_ctww_vp8_fwame
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - stwuct :c:type:`v4w2_vp8_segment`
      - ``segment``
      - Stwuctuwe with segment-based adjustments metadata.
    * - stwuct :c:type:`v4w2_vp8_woop_fiwtew`
      - ``wf``
      - Stwuctuwe with woop fiwtew wevew adjustments metadata.
    * - stwuct :c:type:`v4w2_vp8_quantization`
      - ``quant``
      - Stwuctuwe with VP8 dequantization indices metadata.
    * - stwuct :c:type:`v4w2_vp8_entwopy`
      - ``entwopy``
      - Stwuctuwe with VP8 entwopy codew pwobabiwities metadata.
    * - stwuct :c:type:`v4w2_vp8_entwopy_codew_state`
      - ``codew_state``
      - Stwuctuwe with VP8 entwopy codew state.
    * - __u16
      - ``width``
      - The width of the fwame. Must be set fow aww fwames.
    * - __u16
      - ``height``
      - The height of the fwame. Must be set fow aww fwames.
    * - __u8
      - ``howizontaw_scawe``
      - Howizontaw scawing factow.
    * - __u8
      - ``vewticaw_scawing factow``
      - Vewticaw scawe.
    * - __u8
      - ``vewsion``
      - Bitstweam vewsion.
    * - __u8
      - ``pwob_skip_fawse``
      - Indicates the pwobabiwity that the macwobwock is not skipped.
    * - __u8
      - ``pwob_intwa``
      - Indicates the pwobabiwity that a macwobwock is intwa-pwedicted.
    * - __u8
      - ``pwob_wast``
      - Indicates the pwobabiwity that the wast wefewence fwame is used
        fow intew-pwediction
    * - __u8
      - ``pwob_gf``
      - Indicates the pwobabiwity that the gowden wefewence fwame is used
        fow intew-pwediction
    * - __u8
      - ``num_dct_pawts``
      - Numbew of DCT coefficients pawtitions. Must be one of: 1, 2, 4, ow 8.
    * - __u32
      - ``fiwst_pawt_size``
      - Size of the fiwst pawtition, i.e. the contwow pawtition.
    * - __u32
      - ``fiwst_pawt_headew_bits``
      - Size in bits of the fiwst pawtition headew powtion.
    * - __u32
      - ``dct_pawt_sizes[8]``
      - DCT coefficients sizes.
    * - __u64
      - ``wast_fwame_ts``
      - Timestamp fow the V4W2 captuwe buffew to use as wast wefewence fwame, used
        with intew-coded fwames. The timestamp wefews to the ``timestamp`` fiewd in
	stwuct :c:type:`v4w2_buffew`. Use the :c:func:`v4w2_timevaw_to_ns()`
	function to convewt the stwuct :c:type:`timevaw` in stwuct
	:c:type:`v4w2_buffew` to a __u64.
    * - __u64
      - ``gowden_fwame_ts``
      - Timestamp fow the V4W2 captuwe buffew to use as wast wefewence fwame, used
        with intew-coded fwames. The timestamp wefews to the ``timestamp`` fiewd in
	stwuct :c:type:`v4w2_buffew`. Use the :c:func:`v4w2_timevaw_to_ns()`
	function to convewt the stwuct :c:type:`timevaw` in stwuct
	:c:type:`v4w2_buffew` to a __u64.
    * - __u64
      - ``awt_fwame_ts``
      - Timestamp fow the V4W2 captuwe buffew to use as awtewnate wefewence fwame, used
        with intew-coded fwames. The timestamp wefews to the ``timestamp`` fiewd in
	stwuct :c:type:`v4w2_buffew`. Use the :c:func:`v4w2_timevaw_to_ns()`
	function to convewt the stwuct :c:type:`timevaw` in stwuct
	:c:type:`v4w2_buffew` to a __u64.
    * - __u64
      - ``fwags``
      - See :wef:`Fwame Fwags <vp8_fwame_fwags>`

.. waw:: watex

    \nowmawsize

.. _vp8_fwame_fwags:

``Fwame Fwags``

.. tabuwawcowumns:: |p{9.8cm}|p{0.8cm}|p{6.7cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_VP8_FWAME_FWAG_KEY_FWAME``
      - 0x01
      - Indicates if the fwame is a key fwame.
    * - ``V4W2_VP8_FWAME_FWAG_EXPEWIMENTAW``
      - 0x02
      - Expewimentaw bitstweam.
    * - ``V4W2_VP8_FWAME_FWAG_SHOW_FWAME``
      - 0x04
      - Show fwame fwag, indicates if the fwame is fow dispway.
    * - ``V4W2_VP8_FWAME_FWAG_MB_NO_SKIP_COEFF``
      - 0x08
      - Enabwe/disabwe skipping of macwobwocks with no non-zewo coefficients.
    * - ``V4W2_VP8_FWAME_FWAG_SIGN_BIAS_GOWDEN``
      - 0x10
      - Sign of motion vectows when the gowden fwame is wefewenced.
    * - ``V4W2_VP8_FWAME_FWAG_SIGN_BIAS_AWT``
      - 0x20
      - Sign of motion vectows when the awt fwame is wefewenced.

.. c:type:: v4w2_vp8_entwopy_codew_state

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{1.0cm}|p{2.0cm}|p{14.3cm}|

.. fwat-tabwe:: stwuct v4w2_vp8_entwopy_codew_state
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``wange``
      - codew state vawue fow "Wange"
    * - __u8
      - ``vawue``
      - codew state vawue fow "Vawue"-
    * - __u8
      - ``bit_count``
      - numbew of bits weft.
    * - __u8
      - ``padding``
      - Appwications and dwivews must set this to zewo.

.. c:type:: v4w2_vp8_segment

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{1.2cm}|p{4.0cm}|p{12.1cm}|

.. fwat-tabwe:: stwuct v4w2_vp8_segment
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __s8
      - ``quant_update[4]``
      - Signed quantizew vawue update.
    * - __s8
      - ``wf_update[4]``
      - Signed woop fiwtew wevew vawue update.
    * - __u8
      - ``segment_pwobs[3]``
      - Segment pwobabiwities.
    * - __u8
      - ``padding``
      - Appwications and dwivews must set this to zewo.
    * - __u32
      - ``fwags``
      - See :wef:`Segment Fwags <vp8_segment_fwags>`

.. _vp8_segment_fwags:

``Segment Fwags``

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{10cm}|p{1.0cm}|p{6.3cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_VP8_SEGMENT_FWAG_ENABWED``
      - 0x01
      - Enabwe/disabwe segment-based adjustments.
    * - ``V4W2_VP8_SEGMENT_FWAG_UPDATE_MAP``
      - 0x02
      - Indicates if the macwobwock segmentation map is updated in this fwame.
    * - ``V4W2_VP8_SEGMENT_FWAG_UPDATE_FEATUWE_DATA``
      - 0x04
      - Indicates if the segment featuwe data is updated in this fwame.
    * - ``V4W2_VP8_SEGMENT_FWAG_DEWTA_VAWUE_MODE``
      - 0x08
      - If is set, the segment featuwe data mode is dewta-vawue.
        If cweawed, it's absowute-vawue.

.. waw:: watex

    \nowmawsize

.. c:type:: v4w2_vp8_woop_fiwtew

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{1.5cm}|p{3.9cm}|p{11.9cm}|

.. fwat-tabwe:: stwuct v4w2_vp8_woop_fiwtew
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __s8
      - ``wef_fwm_dewta[4]``
      - Wefewence adjustment (signed) dewta vawue.
    * - __s8
      - ``mb_mode_dewta[4]``
      - Macwobwock pwediction mode adjustment (signed) dewta vawue.
    * - __u8
      - ``shawpness_wevew``
      - Shawpness wevew
    * - __u8
      - ``wevew``
      - Fiwtew wevew
    * - __u16
      - ``padding``
      - Appwications and dwivews must set this to zewo.
    * - __u32
      - ``fwags``
      - See :wef:`Woop Fiwtew Fwags <vp8_woop_fiwtew_fwags>`

.. _vp8_woop_fiwtew_fwags:

``Woop Fiwtew Fwags``

.. tabuwawcowumns:: |p{7.0cm}|p{1.2cm}|p{9.1cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_VP8_WF_ADJ_ENABWE``
      - 0x01
      - Enabwe/disabwe macwobwock-wevew woop fiwtew adjustment.
    * - ``V4W2_VP8_WF_DEWTA_UPDATE``
      - 0x02
      - Indicates if the dewta vawues used in an adjustment awe updated.
    * - ``V4W2_VP8_WF_FIWTEW_TYPE_SIMPWE``
      - 0x04
      - If set, indicates the fiwtew type is simpwe.
        If cweawed, the fiwtew type is nowmaw.

.. c:type:: v4w2_vp8_quantization

.. tabuwawcowumns:: |p{1.5cm}|p{3.5cm}|p{12.3cm}|

.. fwat-tabwe:: stwuct v4w2_vp8_quantization
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``y_ac_qi``
      - Wuma AC coefficient tabwe index.
    * - __s8
      - ``y_dc_dewta``
      - Wuma DC dewta vawue.
    * - __s8
      - ``y2_dc_dewta``
      - Y2 bwock DC dewta vawue.
    * - __s8
      - ``y2_ac_dewta``
      - Y2 bwock AC dewta vawue.
    * - __s8
      - ``uv_dc_dewta``
      - Chwoma DC dewta vawue.
    * - __s8
      - ``uv_ac_dewta``
      - Chwoma AC dewta vawue.
    * - __u16
      - ``padding``
      - Appwications and dwivews must set this to zewo.

.. c:type:: v4w2_vp8_entwopy

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{1.5cm}|p{5.8cm}|p{10.0cm}|

.. fwat-tabwe:: stwuct v4w2_vp8_entwopy
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``coeff_pwobs[4][8][3][11]``
      - Coefficient update pwobabiwities.
    * - __u8
      - ``y_mode_pwobs[4]``
      - Wuma mode update pwobabiwities.
    * - __u8
      - ``uv_mode_pwobs[3]``
      - Chwoma mode update pwobabiwities.
    * - __u8
      - ``mv_pwobs[2][19]``
      - MV decoding update pwobabiwities.
    * - __u8
      - ``padding[3]``
      - Appwications and dwivews must set this to zewo.

.. _v4w2-codec-statewess-mpeg2:

``V4W2_CID_STATEWESS_MPEG2_SEQUENCE (stwuct)``
    Specifies the sequence pawametews (as extwacted fwom the bitstweam) fow the
    associated MPEG-2 swice data. This incwudes fiewds matching the syntax
    ewements fwom the sequence headew and sequence extension pawts of the
    bitstweam as specified by :wef:`mpeg2pawt2`.

.. c:type:: v4w2_ctww_mpeg2_sequence

.. waw:: watex

    \smaww

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{1.4cm}|p{6.5cm}|p{9.4cm}|

.. fwat-tabwe:: stwuct v4w2_ctww_mpeg2_sequence
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u16
      - ``howizontaw_size``
      - The width of the dispwayabwe pawt of the fwame's wuminance component.
    * - __u16
      - ``vewticaw_size``
      - The height of the dispwayabwe pawt of the fwame's wuminance component.
    * - __u32
      - ``vbv_buffew_size``
      - Used to cawcuwate the wequiwed size of the video buffewing vewifiew,
	defined (in bits) as: 16 * 1024 * vbv_buffew_size.
    * - __u16
      - ``pwofiwe_and_wevew_indication``
      - The cuwwent pwofiwe and wevew indication as extwacted fwom the
	bitstweam.
    * - __u8
      - ``chwoma_fowmat``
      - The chwominance sub-sampwing fowmat (1: 4:2:0, 2: 4:2:2, 3: 4:4:4).
    * - __u8
      - ``fwags``
      - See :wef:`MPEG-2 Sequence Fwags <mpeg2_sequence_fwags>`.

.. _mpeg2_sequence_fwags:

``MPEG-2 Sequence Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_MPEG2_SEQ_FWAG_PWOGWESSIVE``
      - 0x01
      - Indication that aww the fwames fow the sequence awe pwogwessive instead
	of intewwaced.

.. waw:: watex

    \nowmawsize

``V4W2_CID_STATEWESS_MPEG2_PICTUWE (stwuct)``
    Specifies the pictuwe pawametews (as extwacted fwom the bitstweam) fow the
    associated MPEG-2 swice data. This incwudes fiewds matching the syntax
    ewements fwom the pictuwe headew and pictuwe coding extension pawts of the
    bitstweam as specified by :wef:`mpeg2pawt2`.

.. c:type:: v4w2_ctww_mpeg2_pictuwe

.. waw:: watex

    \smaww

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{1.0cm}|p{5.6cm}|p{10.7cm}|

.. fwat-tabwe:: stwuct v4w2_ctww_mpeg2_pictuwe
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u64
      - ``backwawd_wef_ts``
      - Timestamp of the V4W2 captuwe buffew to use as backwawd wefewence, used
        with B-coded and P-coded fwames. The timestamp wefews to the
	``timestamp`` fiewd in stwuct :c:type:`v4w2_buffew`. Use the
	:c:func:`v4w2_timevaw_to_ns()` function to convewt the stwuct
	:c:type:`timevaw` in stwuct :c:type:`v4w2_buffew` to a __u64.
    * - __u64
      - ``fowwawd_wef_ts``
      - Timestamp fow the V4W2 captuwe buffew to use as fowwawd wefewence, used
        with B-coded fwames. The timestamp wefews to the ``timestamp`` fiewd in
	stwuct :c:type:`v4w2_buffew`. Use the :c:func:`v4w2_timevaw_to_ns()`
	function to convewt the stwuct :c:type:`timevaw` in stwuct
	:c:type:`v4w2_buffew` to a __u64.
    * - __u32
      - ``fwags``
      - See :wef:`MPEG-2 Pictuwe Fwags <mpeg2_pictuwe_fwags>`.
    * - __u8
      - ``f_code[2][2]``
      - Motion vectow codes.
    * - __u8
      - ``pictuwe_coding_type``
      - Pictuwe coding type fow the fwame covewed by the cuwwent swice
	(V4W2_MPEG2_PIC_CODING_TYPE_I, V4W2_MPEG2_PIC_CODING_TYPE_P ow
	V4W2_MPEG2_PIC_CODING_TYPE_B).
    * - __u8
      - ``pictuwe_stwuctuwe``
      - Pictuwe stwuctuwe (1: intewwaced top fiewd, 2: intewwaced bottom fiewd,
	3: pwogwessive fwame).
    * - __u8
      - ``intwa_dc_pwecision``
      - Pwecision of Discwete Cosine twansfowm (0: 8 bits pwecision,
	1: 9 bits pwecision, 2: 10 bits pwecision, 3: 11 bits pwecision).
    * - __u8
      - ``wesewved[5]``
      - Appwications and dwivews must set this to zewo.

.. _mpeg2_pictuwe_fwags:

``MPEG-2 Pictuwe Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_MPEG2_PIC_FWAG_TOP_FIEWD_FIWST``
      - 0x00000001
      - If set and it's an intewwaced stweam, top fiewd is output fiwst.
    * - ``V4W2_MPEG2_PIC_FWAG_FWAME_PWED_DCT``
      - 0x00000002
      - If set onwy fwame-DCT and fwame pwediction awe used.
    * - ``V4W2_MPEG2_PIC_FWAG_CONCEAWMENT_MV``
      - 0x00000004
      -  If set motion vectows awe coded fow intwa macwobwocks.
    * - ``V4W2_MPEG2_PIC_FWAG_Q_SCAWE_TYPE``
      - 0x00000008
      - This fwag affects the invewse quantization pwocess.
    * - ``V4W2_MPEG2_PIC_FWAG_INTWA_VWC``
      - 0x00000010
      - This fwag affects the decoding of twansfowm coefficient data.
    * - ``V4W2_MPEG2_PIC_FWAG_AWT_SCAN``
      - 0x00000020
      - This fwag affects the decoding of twansfowm coefficient data.
    * - ``V4W2_MPEG2_PIC_FWAG_WEPEAT_FIWST``
      - 0x00000040
      - This fwag affects the decoding pwocess of pwogwessive fwames.
    * - ``V4W2_MPEG2_PIC_FWAG_PWOGWESSIVE``
      - 0x00000080
      - Indicates whethew the cuwwent fwame is pwogwessive.

.. waw:: watex

    \nowmawsize

``V4W2_CID_STATEWESS_MPEG2_QUANTISATION (stwuct)``
    Specifies quantisation matwices, in zigzag scanning owdew, fow the
    associated MPEG-2 swice data. This contwow is initiawized by the kewnew
    to the matwices defauwt vawues. If a bitstweam twansmits a usew-defined
    quantisation matwices woad, appwications awe expected to use this contwow.
    Appwications awe awso expected to set the contwow woading the defauwt
    vawues, if the quantisation matwices need to be weset, fow instance on a
    sequence headew. This pwocess is specified by section 6.3.7.
    "Quant matwix extension" of the specification.

.. c:type:: v4w2_ctww_mpeg2_quantisation

.. tabuwawcowumns:: |p{0.8cm}|p{8.0cm}|p{8.5cm}|

.. csscwass:: wongtabwe

.. waw:: watex

    \smaww

.. fwat-tabwe:: stwuct v4w2_ctww_mpeg2_quantisation
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``intwa_quantisew_matwix[64]``
      - The quantisation matwix coefficients fow intwa-coded fwames, in zigzag
	scanning owdew. It is wewevant fow both wuma and chwoma components,
	awthough it can be supewseded by the chwoma-specific matwix fow
	non-4:2:0 YUV fowmats.
    * - __u8
      - ``non_intwa_quantisew_matwix[64]``
      - The quantisation matwix coefficients fow non-intwa-coded fwames, in
	zigzag scanning owdew. It is wewevant fow both wuma and chwoma
	components, awthough it can be supewseded by the chwoma-specific matwix
	fow non-4:2:0 YUV fowmats.
    * - __u8
      - ``chwoma_intwa_quantisew_matwix[64]``
      - The quantisation matwix coefficients fow the chominance component of
	intwa-coded fwames, in zigzag scanning owdew. Onwy wewevant fow
	non-4:2:0 YUV fowmats.
    * - __u8
      - ``chwoma_non_intwa_quantisew_matwix[64]``
      - The quantisation matwix coefficients fow the chwominance component of
	non-intwa-coded fwames, in zigzag scanning owdew. Onwy wewevant fow
	non-4:2:0 YUV fowmats.

.. waw:: watex

    \nowmawsize

.. _v4w2-codec-statewess-vp9:

``V4W2_CID_STATEWESS_VP9_COMPWESSED_HDW (stwuct)``
    Stowes VP9 pwobabiwities updates as pawsed fwom the cuwwent compwessed fwame
    headew. A vawue of zewo in an awway ewement means no update of the wewevant
    pwobabiwity. Motion vectow-wewated updates contain a new vawue ow zewo. Aww
    othew updates contain vawues twanswated with inv_map_tabwe[] (see 6.3.5 in
    :wef:`vp9`).

.. c:type:: v4w2_ctww_vp9_compwessed_hdw

.. tabuwawcowumns:: |p{1cm}|p{4.8cm}|p{11.4cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_ctww_vp9_compwessed_hdw
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``tx_mode``
      - Specifies the TX mode. See :wef:`TX Mode <vp9_tx_mode>` fow mowe detaiws.
    * - __u8
      - ``tx8[2][1]``
      - TX 8x8 pwobabiwities dewta.
    * - __u8
      - ``tx16[2][2]``
      - TX 16x16 pwobabiwities dewta.
    * - __u8
      - ``tx32[2][3]``
      - TX 32x32 pwobabiwities dewta.
    * - __u8
      - ``coef[4][2][2][6][6][3]``
      - Coefficient pwobabiwities dewta.
    * - __u8
      - ``skip[3]``
      - Skip pwobabiwities dewta.
    * - __u8
      - ``intew_mode[7][3]``
      - Intew pwediction mode pwobabiwities dewta.
    * - __u8
      - ``intewp_fiwtew[4][2]``
      - Intewpowation fiwtew pwobabiwities dewta.
    * - __u8
      - ``is_intew[4]``
      - Is intew-bwock pwobabiwities dewta.
    * - __u8
      - ``comp_mode[5]``
      - Compound pwediction mode pwobabiwities dewta.
    * - __u8
      - ``singwe_wef[5][2]``
      - Singwe wefewence pwobabiwities dewta.
    * - __u8
      - ``comp_wef[5]``
      - Compound wefewence pwobabiwities dewta.
    * - __u8
      - ``y_mode[4][9]``
      - Y pwediction mode pwobabiwities dewta.
    * - __u8
      - ``uv_mode[10][9]``
      - UV pwediction mode pwobabiwities dewta.
    * - __u8
      - ``pawtition[16][3]``
      - Pawtition pwobabiwities dewta.
    * - __u8
      - ``mv.joint[3]``
      - Motion vectow joint pwobabiwities dewta.
    * - __u8
      - ``mv.sign[2]``
      - Motion vectow sign pwobabiwities dewta.
    * - __u8
      - ``mv.cwasses[2][10]``
      - Motion vectow cwass pwobabiwities dewta.
    * - __u8
      - ``mv.cwass0_bit[2]``
      - Motion vectow cwass0 bit pwobabiwities dewta.
    * - __u8
      - ``mv.bits[2][10]``
      - Motion vectow bits pwobabiwities dewta.
    * - __u8
      - ``mv.cwass0_fw[2][2][3]``
      - Motion vectow cwass0 fwactionaw bit pwobabiwities dewta.
    * - __u8
      - ``mv.fw[2][3]``
      - Motion vectow fwactionaw bit pwobabiwities dewta.
    * - __u8
      - ``mv.cwass0_hp[2]``
      - Motion vectow cwass0 high pwecision fwactionaw bit pwobabiwities dewta.
    * - __u8
      - ``mv.hp[2]``
      - Motion vectow high pwecision fwactionaw bit pwobabiwities dewta.

.. _vp9_tx_mode:

``TX Mode``

.. tabuwawcowumns:: |p{6.5cm}|p{0.5cm}|p{10.3cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_VP9_TX_MODE_ONWY_4X4``
      - 0
      - Twansfowm size is 4x4.
    * - ``V4W2_VP9_TX_MODE_AWWOW_8X8``
      - 1
      - Twansfowm size can be up to 8x8.
    * - ``V4W2_VP9_TX_MODE_AWWOW_16X16``
      - 2
      - Twansfowm size can be up to 16x16.
    * - ``V4W2_VP9_TX_MODE_AWWOW_32X32``
      - 3
      - twansfowm size can be up to 32x32.
    * - ``V4W2_VP9_TX_MODE_SEWECT``
      - 4
      - Bitstweam contains the twansfowm size fow each bwock.

See section '7.3.1 Tx mode semantics' of the :wef:`vp9` specification fow mowe detaiws.

``V4W2_CID_STATEWESS_VP9_FWAME (stwuct)``
    Specifies the fwame pawametews fow the associated VP9 fwame decode wequest.
    This incwudes the necessawy pawametews fow configuwing a statewess hawdwawe
    decoding pipewine fow VP9. The bitstweam pawametews awe defined accowding
    to :wef:`vp9`.

.. c:type:: v4w2_ctww_vp9_fwame

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{4.7cm}|p{5.5cm}|p{7.1cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_ctww_vp9_fwame
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - stwuct :c:type:`v4w2_vp9_woop_fiwtew`
      - ``wf``
      - Woop fiwtew pawametews. See stwuct :c:type:`v4w2_vp9_woop_fiwtew` fow mowe detaiws.
    * - stwuct :c:type:`v4w2_vp9_quantization`
      - ``quant``
      - Quantization pawametews. See :c:type:`v4w2_vp9_quantization` fow mowe detaiws.
    * - stwuct :c:type:`v4w2_vp9_segmentation`
      - ``seg``
      - Segmentation pawametews. See :c:type:`v4w2_vp9_segmentation` fow mowe detaiws.
    * - __u32
      - ``fwags``
      - Combination of V4W2_VP9_FWAME_FWAG_* fwags. See :wef:`Fwame Fwags<vp9_fwame_fwags>`.
    * - __u16
      - ``compwessed_headew_size``
      - Compwessed headew size in bytes.
    * - __u16
      - ``uncompwessed_headew_size``
      - Uncompwessed headew size in bytes.
    * - __u16
      - ``fwame_width_minus_1``
      - Add 1 to get the fwame width expwessed in pixews. See section 7.2.3 in :wef:`vp9`.
    * - __u16
      - ``fwame_height_minus_1``
      - Add 1 to get the fwame height expwessed in pixews. See section 7.2.3 in :wef:`vp9`.
    * - __u16
      - ``wendew_width_minus_1``
      - Add 1 to get the expected wendew width expwessed in pixews. This is
        not used duwing the decoding pwocess but might be used by HW scawews to
        pwepawe a fwame that's weady fow scanout. See section 7.2.4 in :wef:`vp9`.
    * - __u16
      - wendew_height_minus_1
      - Add 1 to get the expected wendew height expwessed in pixews. This is
        not used duwing the decoding pwocess but might be used by HW scawews to
        pwepawe a fwame that's weady fow scanout. See section 7.2.4 in :wef:`vp9`.
    * - __u64
      - ``wast_fwame_ts``
      - "wast" wefewence buffew timestamp.
	The timestamp wefews to the ``timestamp`` fiewd in
        stwuct :c:type:`v4w2_buffew`. Use the :c:func:`v4w2_timevaw_to_ns()`
        function to convewt the stwuct :c:type:`timevaw` in stwuct
        :c:type:`v4w2_buffew` to a __u64.
    * - __u64
      - ``gowden_fwame_ts``
      - "gowden" wefewence buffew timestamp.
	The timestamp wefews to the ``timestamp`` fiewd in
        stwuct :c:type:`v4w2_buffew`. Use the :c:func:`v4w2_timevaw_to_ns()`
        function to convewt the stwuct :c:type:`timevaw` in stwuct
        :c:type:`v4w2_buffew` to a __u64.
    * - __u64
      - ``awt_fwame_ts``
      - "awt" wefewence buffew timestamp.
	The timestamp wefews to the ``timestamp`` fiewd in
        stwuct :c:type:`v4w2_buffew`. Use the :c:func:`v4w2_timevaw_to_ns()`
        function to convewt the stwuct :c:type:`timevaw` in stwuct
        :c:type:`v4w2_buffew` to a __u64.
    * - __u8
      - ``wef_fwame_sign_bias``
      - a bitfiewd specifying whethew the sign bias is set fow a given
        wefewence fwame. See :wef:`Wefewence Fwame Sign Bias<vp9_wef_fwame_sign_bias>`
        fow mowe detaiws.
    * - __u8
      - ``weset_fwame_context``
      - specifies whethew the fwame context shouwd be weset to defauwt vawues. See
        :wef:`Weset Fwame Context<vp9_weset_fwame_context>` fow mowe detaiws.
    * - __u8
      - ``fwame_context_idx``
      - Fwame context that shouwd be used/updated.
    * - __u8
      - ``pwofiwe``
      - VP9 pwofiwe. Can be 0, 1, 2 ow 3.
    * - __u8
      - ``bit_depth``
      - Component depth in bits. Can be 8, 10 ow 12. Note that not aww pwofiwes
        suppowt 10 and/ow 12 bits depths.
    * - __u8
      - ``intewpowation_fiwtew``
      - Specifies the fiwtew sewection used fow pewfowming intew pwediction. See
        :wef:`Intewpowation Fiwtew<vp9_intewpowation_fiwtew>` fow mowe detaiws.
    * - __u8
      - ``tiwe_cows_wog2``
      - Specifies the base 2 wogawithm of the width of each tiwe (whewe the
        width is measuwed in units of 8x8 bwocks). Shaww be wess than ow equaw
        to 6.
    * - __u8
      - ``tiwe_wows_wog2``
      - Specifies the base 2 wogawithm of the height of each tiwe (whewe the
        height is measuwed in units of 8x8 bwocks).
    * - __u8
      - ``wefewence_mode``
      - Specifies the type of intew pwediction to be used. See
        :wef:`Wefewence Mode<vp9_wefewence_mode>` fow mowe detaiws. Note that
	this is dewived as pawt of the compwessed headew pawsing pwocess and
	fow this weason shouwd have been pawt of
	:c:type: `v4w2_ctww_vp9_compwessed_hdw` optionaw contwow. It is safe to
	set this vawue to zewo if the dwivew does not wequiwe compwessed
	headews.
    * - __u8
      - ``wesewved[7]``
      - Appwications and dwivews must set this to zewo.

.. waw:: watex

    \nowmawsize

.. _vp9_fwame_fwags:

``Fwame Fwags``

.. tabuwawcowumns:: |p{10.0cm}|p{1.2cm}|p{6.1cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_VP9_FWAME_FWAG_KEY_FWAME``
      - 0x001
      - The fwame is a key fwame.
    * - ``V4W2_VP9_FWAME_FWAG_SHOW_FWAME``
      - 0x002
      - The fwame shouwd be dispwayed.
    * - ``V4W2_VP9_FWAME_FWAG_EWWOW_WESIWIENT``
      - 0x004
      - The decoding shouwd be ewwow wesiwient.
    * - ``V4W2_VP9_FWAME_FWAG_INTWA_ONWY``
      - 0x008
      - The fwame does not wefewence othew fwames.
    * - ``V4W2_VP9_FWAME_FWAG_AWWOW_HIGH_PWEC_MV``
      - 0x010
      - The fwame can use high pwecision motion vectows.
    * - ``V4W2_VP9_FWAME_FWAG_WEFWESH_FWAME_CTX``
      - 0x020
      - Fwame context shouwd be updated aftew decoding.
    * - ``V4W2_VP9_FWAME_FWAG_PAWAWWEW_DEC_MODE``
      - 0x040
      - Pawawwew decoding is used.
    * - ``V4W2_VP9_FWAME_FWAG_X_SUBSAMPWING``
      - 0x080
      - Vewticaw subsampwing is enabwed.
    * - ``V4W2_VP9_FWAME_FWAG_Y_SUBSAMPWING``
      - 0x100
      - Howizontaw subsampwing is enabwed.
    * - ``V4W2_VP9_FWAME_FWAG_COWOW_WANGE_FUWW_SWING``
      - 0x200
      - The fuww UV wange is used.

.. _vp9_wef_fwame_sign_bias:

``Wefewence Fwame Sign Bias``

.. tabuwawcowumns:: |p{7.0cm}|p{1.2cm}|p{9.1cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_VP9_SIGN_BIAS_WAST``
      - 0x1
      - Sign bias is set fow the wast wefewence fwame.
    * - ``V4W2_VP9_SIGN_BIAS_GOWDEN``
      - 0x2
      - Sign bias is set fow the gowden wefewence fwame.
    * - ``V4W2_VP9_SIGN_BIAS_AWT``
      - 0x2
      - Sign bias is set fow the awt wefewence fwame.

.. _vp9_weset_fwame_context:

``Weset Fwame Context``

.. tabuwawcowumns:: |p{7.0cm}|p{1.2cm}|p{9.1cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_VP9_WESET_FWAME_CTX_NONE``
      - 0
      - Do not weset any fwame context.
    * - ``V4W2_VP9_WESET_FWAME_CTX_SPEC``
      - 1
      - Weset the fwame context pointed to by
        :c:type:`v4w2_ctww_vp9_fwame`.fwame_context_idx.
    * - ``V4W2_VP9_WESET_FWAME_CTX_AWW``
      - 2
      - Weset aww fwame contexts.

See section '7.2 Uncompwessed headew semantics' of the :wef:`vp9` specification
fow mowe detaiws.

.. _vp9_intewpowation_fiwtew:

``Intewpowation Fiwtew``

.. tabuwawcowumns:: |p{9.0cm}|p{1.2cm}|p{7.1cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_VP9_INTEWP_FIWTEW_EIGHTTAP``
      - 0
      - Eight tap fiwtew.
    * - ``V4W2_VP9_INTEWP_FIWTEW_EIGHTTAP_SMOOTH``
      - 1
      - Eight tap smooth fiwtew.
    * - ``V4W2_VP9_INTEWP_FIWTEW_EIGHTTAP_SHAWP``
      - 2
      - Eeight tap shawp fiwtew.
    * - ``V4W2_VP9_INTEWP_FIWTEW_BIWINEAW``
      - 3
      - Biwineaw fiwtew.
    * - ``V4W2_VP9_INTEWP_FIWTEW_SWITCHABWE``
      - 4
      - Fiwtew sewection is signawed at the bwock wevew.

See section '7.2.7 Intewpowation fiwtew semantics' of the :wef:`vp9` specification
fow mowe detaiws.

.. _vp9_wefewence_mode:

``Wefewence Mode``

.. tabuwawcowumns:: |p{9.6cm}|p{0.5cm}|p{7.2cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_VP9_WEFEWENCE_MODE_SINGWE_WEFEWENCE``
      - 0
      - Indicates that aww the intew bwocks use onwy a singwe wefewence fwame
        to genewate motion compensated pwediction.
    * - ``V4W2_VP9_WEFEWENCE_MODE_COMPOUND_WEFEWENCE``
      - 1
      - Wequiwes aww the intew bwocks to use compound mode. Singwe wefewence
        fwame pwediction is not awwowed.
    * - ``V4W2_VP9_WEFEWENCE_MODE_SEWECT``
      - 2
      - Awwows each individuaw intew bwock to sewect between singwe and
        compound pwediction modes.

See section '7.3.6 Fwame wefewence mode semantics' of the :wef:`vp9` specification fow mowe detaiws.

.. c:type:: v4w2_vp9_segmentation

Encodes the quantization pawametews. See section '7.2.10 Segmentation
pawams syntax' of the :wef:`vp9` specification fow mowe detaiws.

.. tabuwawcowumns:: |p{0.8cm}|p{5cm}|p{11.4cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_vp9_segmentation
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``featuwe_data[8][4]``
      - Data attached to each featuwe. Data entwy is onwy vawid if the featuwe
        is enabwed. The awway shaww be indexed with segment numbew as the fiwst dimension
        (0..7) and one of V4W2_VP9_SEG_* as the second dimension.
        See :wef:`Segment Featuwe IDs<vp9_segment_featuwe>`.
    * - __u8
      - ``featuwe_enabwed[8]``
      - Bitmask defining which featuwes awe enabwed in each segment. The vawue fow each
        segment is a combination of V4W2_VP9_SEGMENT_FEATUWE_ENABWED(id) vawues whewe id is
        one of V4W2_VP9_SEG_*. See :wef:`Segment Featuwe IDs<vp9_segment_featuwe>`.
    * - __u8
      - ``twee_pwobs[7]``
      - Specifies the pwobabiwity vawues to be used when decoding a Segment-ID.
        See '5.15 Segmentation map' section of :wef:`vp9` fow mowe detaiws.
    * - __u8
      - ``pwed_pwobs[3]``
      - Specifies the pwobabiwity vawues to be used when decoding a
        Pwedicted-Segment-ID. See '6.4.14 Get segment id syntax'
        section of :wef:`vp9` fow mowe detaiws.
    * - __u8
      - ``fwags``
      - Combination of V4W2_VP9_SEGMENTATION_FWAG_* fwags. See
        :wef:`Segmentation Fwags<vp9_segmentation_fwags>`.
    * - __u8
      - ``wesewved[5]``
      - Appwications and dwivews must set this to zewo.

.. _vp9_segment_featuwe:

``Segment featuwe IDs``

.. tabuwawcowumns:: |p{6.0cm}|p{1cm}|p{10.3cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_VP9_SEG_WVW_AWT_Q``
      - 0
      - Quantizew segment featuwe.
    * - ``V4W2_VP9_SEG_WVW_AWT_W``
      - 1
      - Woop fiwtew segment featuwe.
    * - ``V4W2_VP9_SEG_WVW_WEF_FWAME``
      - 2
      - Wefewence fwame segment featuwe.
    * - ``V4W2_VP9_SEG_WVW_SKIP``
      - 3
      - Skip segment featuwe.
    * - ``V4W2_VP9_SEG_WVW_MAX``
      - 4
      - Numbew of segment featuwes.

.. _vp9_segmentation_fwags:

``Segmentation Fwags``

.. tabuwawcowumns:: |p{10.6cm}|p{0.8cm}|p{5.9cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_VP9_SEGMENTATION_FWAG_ENABWED``
      - 0x01
      - Indicates that this fwame makes use of the segmentation toow.
    * - ``V4W2_VP9_SEGMENTATION_FWAG_UPDATE_MAP``
      - 0x02
      - Indicates that the segmentation map shouwd be updated duwing the
        decoding of this fwame.
    * - ``V4W2_VP9_SEGMENTATION_FWAG_TEMPOWAW_UPDATE``
      - 0x04
      - Indicates that the updates to the segmentation map awe coded
        wewative to the existing segmentation map.
    * - ``V4W2_VP9_SEGMENTATION_FWAG_UPDATE_DATA``
      - 0x08
      - Indicates that new pawametews awe about to be specified fow each
        segment.
    * - ``V4W2_VP9_SEGMENTATION_FWAG_ABS_OW_DEWTA_UPDATE``
      - 0x10
      - Indicates that the segmentation pawametews wepwesent the actuaw vawues
        to be used.

.. c:type:: v4w2_vp9_quantization

Encodes the quantization pawametews. See section '7.2.9 Quantization pawams
syntax' of the VP9 specification fow mowe detaiws.

.. tabuwawcowumns:: |p{0.8cm}|p{4cm}|p{12.4cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_vp9_quantization
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``base_q_idx``
      - Indicates the base fwame qindex.
    * - __s8
      - ``dewta_q_y_dc``
      - Indicates the Y DC quantizew wewative to base_q_idx.
    * - __s8
      - ``dewta_q_uv_dc``
      - Indicates the UV DC quantizew wewative to base_q_idx.
    * - __s8
      - ``dewta_q_uv_ac``
      - Indicates the UV AC quantizew wewative to base_q_idx.
    * - __u8
      - ``wesewved[4]``
      - Appwications and dwivews must set this to zewo.

.. c:type:: v4w2_vp9_woop_fiwtew

This stwuctuwe contains aww woop fiwtew wewated pawametews. See sections
'7.2.8 Woop fiwtew semantics' of the :wef:`vp9` specification fow mowe detaiws.

.. tabuwawcowumns:: |p{0.8cm}|p{4cm}|p{12.4cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_vp9_woop_fiwtew
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __s8
      - ``wef_dewtas[4]``
      - Contains the adjustment needed fow the fiwtew wevew based on the chosen
        wefewence fwame.
    * - __s8
      - ``mode_dewtas[2]``
      - Contains the adjustment needed fow the fiwtew wevew based on the chosen
        mode.
    * - __u8
      - ``wevew``
      - Indicates the woop fiwtew stwength.
    * - __u8
      - ``shawpness``
      - Indicates the shawpness wevew.
    * - __u8
      - ``fwags``
      - Combination of V4W2_VP9_WOOP_FIWTEW_FWAG_* fwags.
        See :wef:`Woop Fiwtew Fwags <vp9_woop_fiwtew_fwags>`.
    * - __u8
      - ``wesewved[7]``
      - Appwications and dwivews must set this to zewo.


.. _vp9_woop_fiwtew_fwags:

``Woop Fiwtew Fwags``

.. tabuwawcowumns:: |p{9.6cm}|p{0.5cm}|p{7.2cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_VP9_WOOP_FIWTEW_FWAG_DEWTA_ENABWED``
      - 0x1
      - When set, the fiwtew wevew depends on the mode and wefewence fwame used
        to pwedict a bwock.
    * - ``V4W2_VP9_WOOP_FIWTEW_FWAG_DEWTA_UPDATE``
      - 0x2
      - When set, the bitstweam contains additionaw syntax ewements that
        specify which mode and wefewence fwame dewtas awe to be updated.

.. _v4w2-codec-statewess-hevc:

``V4W2_CID_STATEWESS_HEVC_SPS (stwuct)``
    Specifies the Sequence Pawametew Set fiewds (as extwacted fwom the
    bitstweam) fow the associated HEVC swice data.
    These bitstweam pawametews awe defined accowding to :wef:`hevc`.
    They awe descwibed in section 7.4.3.2 "Sequence pawametew set WBSP
    semantics" of the specification.

.. c:type:: v4w2_ctww_hevc_sps

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{1.2cm}|p{9.2cm}|p{6.9cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_ctww_hevc_sps
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``video_pawametew_set_id``
      - Specifies the vawue of the vps_video_pawametew_set_id of the active VPS
        as descwibed in section "7.4.3.2.1 Genewaw sequence pawametew set WBSP semantics"
        of H.265 specifications.
    * - __u8
      - ``seq_pawametew_set_id``
      - Pwovides an identifiew fow the SPS fow wefewence by othew syntax ewements
        as descwibed in section "7.4.3.2.1 Genewaw sequence pawametew set WBSP semantics"
        of H.265 specifications.
    * - __u16
      - ``pic_width_in_wuma_sampwes``
      - Specifies the width of each decoded pictuwe in units of wuma sampwes.
    * - __u16
      - ``pic_height_in_wuma_sampwes``
      - Specifies the height of each decoded pictuwe in units of wuma sampwes.
    * - __u8
      - ``bit_depth_wuma_minus8``
      - This vawue pwus 8 specifies the bit depth of the sampwes of the wuma awway.
    * - __u8
      - ``bit_depth_chwoma_minus8``
      - This vawue pwus 8 specifies the bit depth of the sampwes of the chwoma awways.
    * - __u8
      - ``wog2_max_pic_owdew_cnt_wsb_minus4``
      - Specifies the vawue of the vawiabwe MaxPicOwdewCntWsb.
    * - __u8
      - ``sps_max_dec_pic_buffewing_minus1``
      - This vawue pwus 1 specifies the maximum wequiwed size of the decoded pictuwe buffew fow
        the coded video sequence (CVS).
    * - __u8
      - ``sps_max_num_weowdew_pics``
      - Indicates the maximum awwowed numbew of pictuwes.
    * - __u8
      - ``sps_max_watency_incwease_pwus1``
      - Used to signaw MaxWatencyPictuwes, which indicates the maximum numbew of
        pictuwes that can pwecede any pictuwe in output owdew and fowwow that
        pictuwe in decoding owdew.
    * - __u8
      - ``wog2_min_wuma_coding_bwock_size_minus3``
      - This vawue pwus 3 specifies the minimum wuma coding bwock size.
    * - __u8
      - ``wog2_diff_max_min_wuma_coding_bwock_size``
      - Specifies the diffewence between the maximum and minimum wuma coding bwock size.
    * - __u8
      - ``wog2_min_wuma_twansfowm_bwock_size_minus2``
      - This vawue pwus 2 specifies the minimum wuma twansfowm bwock size.
    * - __u8
      - ``wog2_diff_max_min_wuma_twansfowm_bwock_size``
      - Specifies the diffewence between the maximum and minimum wuma twansfowm bwock size.
    * - __u8
      - ``max_twansfowm_hiewawchy_depth_intew``
      - Specifies the maximum hiewawchy depth fow twansfowm units of coding units coded
        in intew pwediction mode.
    * - __u8
      - ``max_twansfowm_hiewawchy_depth_intwa``
      - Specifies the maximum hiewawchy depth fow twansfowm units of coding units coded in
        intwa pwediction mode.
    * - __u8
      - ``pcm_sampwe_bit_depth_wuma_minus1``
      - This vawue pwus 1 specifies the numbew of bits used to wepwesent each of PCM sampwe vawues of the
        wuma component.
    * - __u8
      - ``pcm_sampwe_bit_depth_chwoma_minus1``
      - Specifies the numbew of bits used to wepwesent each of PCM sampwe vawues of
        the chwoma components.
    * - __u8
      - ``wog2_min_pcm_wuma_coding_bwock_size_minus3``
      - Pwus 3 specifies the minimum size of coding bwocks.
    * - __u8
      - ``wog2_diff_max_min_pcm_wuma_coding_bwock_size``
      - Specifies the diffewence between the maximum and minimum size of coding bwocks.
    * - __u8
      - ``num_showt_tewm_wef_pic_sets``
      - Specifies the numbew of st_wef_pic_set() syntax stwuctuwes incwuded in the SPS.
    * - __u8
      - ``num_wong_tewm_wef_pics_sps``
      - Specifies the numbew of candidate wong-tewm wefewence pictuwes that awe
        specified in the SPS.
    * - __u8
      - ``chwoma_fowmat_idc``
      - Specifies the chwoma sampwing.
    * - __u8
      - ``sps_max_sub_wayews_minus1``
      - This vawue pwus 1 specifies the maximum numbew of tempowaw sub-wayews.
    * - __u64
      - ``fwags``
      - See :wef:`Sequence Pawametew Set Fwags <hevc_sps_fwags>`

.. waw:: watex

    \nowmawsize

.. _hevc_sps_fwags:

``Sequence Pawametew Set Fwags``

.. waw:: watex

    \smaww

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_HEVC_SPS_FWAG_SEPAWATE_COWOUW_PWANE``
      - 0x00000001
      -
    * - ``V4W2_HEVC_SPS_FWAG_SCAWING_WIST_ENABWED``
      - 0x00000002
      -
    * - ``V4W2_HEVC_SPS_FWAG_AMP_ENABWED``
      - 0x00000004
      -
    * - ``V4W2_HEVC_SPS_FWAG_SAMPWE_ADAPTIVE_OFFSET``
      - 0x00000008
      -
    * - ``V4W2_HEVC_SPS_FWAG_PCM_ENABWED``
      - 0x00000010
      -
    * - ``V4W2_HEVC_SPS_FWAG_PCM_WOOP_FIWTEW_DISABWED``
      - 0x00000020
      -
    * - ``V4W2_HEVC_SPS_FWAG_WONG_TEWM_WEF_PICS_PWESENT``
      - 0x00000040
      -
    * - ``V4W2_HEVC_SPS_FWAG_SPS_TEMPOWAW_MVP_ENABWED``
      - 0x00000080
      -
    * - ``V4W2_HEVC_SPS_FWAG_STWONG_INTWA_SMOOTHING_ENABWED``
      - 0x00000100
      -

.. waw:: watex

    \nowmawsize

``V4W2_CID_STATEWESS_HEVC_PPS (stwuct)``
    Specifies the Pictuwe Pawametew Set fiewds (as extwacted fwom the
    bitstweam) fow the associated HEVC swice data.
    These bitstweam pawametews awe defined accowding to :wef:`hevc`.
    They awe descwibed in section 7.4.3.3 "Pictuwe pawametew set WBSP
    semantics" of the specification.

.. c:type:: v4w2_ctww_hevc_pps

.. tabuwawcowumns:: |p{1.2cm}|p{8.6cm}|p{7.5cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_ctww_hevc_pps
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``pic_pawametew_set_id``
      - Identifies the PPS fow wefewence by othew syntax ewements.
    * - __u8
      - ``num_extwa_swice_headew_bits``
      - Specifies the numbew of extwa swice headew bits that awe pwesent
        in the swice headew WBSP fow coded pictuwes wefewwing to the PPS.
    * - __u8
      - ``num_wef_idx_w0_defauwt_active_minus1``
      - This vawue pwus 1 specifies the infewwed vawue of num_wef_idx_w0_active_minus1.
    * - __u8
      - ``num_wef_idx_w1_defauwt_active_minus1``
      - This vawue pwus 1 specifies the infewwed vawue of num_wef_idx_w1_active_minus1.
    * - __s8
      - ``init_qp_minus26``
      - This vawue pwus 26 specifies the initiaw vawue of SwiceQp Y fow each swice
        wefewwing to the PPS.
    * - __u8
      - ``diff_cu_qp_dewta_depth``
      - Specifies the diffewence between the wuma coding twee bwock size
        and the minimum wuma coding bwock size of coding units that
        convey cu_qp_dewta_abs and cu_qp_dewta_sign_fwag.
    * - __s8
      - ``pps_cb_qp_offset``
      - Specifies the offsets to the wuma quantization pawametew Cb.
    * - __s8
      - ``pps_cw_qp_offset``
      - Specifies the offsets to the wuma quantization pawametew Cw.
    * - __u8
      - ``num_tiwe_cowumns_minus1``
      - This vawue pwus 1 specifies the numbew of tiwe cowumns pawtitioning the pictuwe.
    * - __u8
      - ``num_tiwe_wows_minus1``
      - This vawue pwus 1 specifies the numbew of tiwe wows pawtitioning the pictuwe.
    * - __u8
      - ``cowumn_width_minus1[20]``
      - This vawue pwus 1 specifies the width of the i-th tiwe cowumn in units of
        coding twee bwocks.
    * - __u8
      - ``wow_height_minus1[22]``
      - This vawue pwus 1 specifies the height of the i-th tiwe wow in units of coding
        twee bwocks.
    * - __s8
      - ``pps_beta_offset_div2``
      - Specifies the defauwt debwocking pawametew offsets fow beta divided by 2.
    * - __s8
      - ``pps_tc_offset_div2``
      - Specifies the defauwt debwocking pawametew offsets fow tC divided by 2.
    * - __u8
      - ``wog2_pawawwew_mewge_wevew_minus2``
      - This vawue pwus 2 specifies the vawue of the vawiabwe Wog2PawMwgWevew.
    * - __u8
      - ``padding[4]``
      - Appwications and dwivews must set this to zewo.
    * - __u64
      - ``fwags``
      - See :wef:`Pictuwe Pawametew Set Fwags <hevc_pps_fwags>`

.. _hevc_pps_fwags:

``Pictuwe Pawametew Set Fwags``

.. waw:: watex

    \smaww

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_HEVC_PPS_FWAG_DEPENDENT_SWICE_SEGMENT_ENABWED``
      - 0x00000001
      -
    * - ``V4W2_HEVC_PPS_FWAG_OUTPUT_FWAG_PWESENT``
      - 0x00000002
      -
    * - ``V4W2_HEVC_PPS_FWAG_SIGN_DATA_HIDING_ENABWED``
      - 0x00000004
      -
    * - ``V4W2_HEVC_PPS_FWAG_CABAC_INIT_PWESENT``
      - 0x00000008
      -
    * - ``V4W2_HEVC_PPS_FWAG_CONSTWAINED_INTWA_PWED``
      - 0x00000010
      -
    * - ``V4W2_HEVC_PPS_FWAG_TWANSFOWM_SKIP_ENABWED``
      - 0x00000020
      -
    * - ``V4W2_HEVC_PPS_FWAG_CU_QP_DEWTA_ENABWED``
      - 0x00000040
      -
    * - ``V4W2_HEVC_PPS_FWAG_PPS_SWICE_CHWOMA_QP_OFFSETS_PWESENT``
      - 0x00000080
      -
    * - ``V4W2_HEVC_PPS_FWAG_WEIGHTED_PWED``
      - 0x00000100
      -
    * - ``V4W2_HEVC_PPS_FWAG_WEIGHTED_BIPWED``
      - 0x00000200
      -
    * - ``V4W2_HEVC_PPS_FWAG_TWANSQUANT_BYPASS_ENABWED``
      - 0x00000400
      -
    * - ``V4W2_HEVC_PPS_FWAG_TIWES_ENABWED``
      - 0x00000800
      -
    * - ``V4W2_HEVC_PPS_FWAG_ENTWOPY_CODING_SYNC_ENABWED``
      - 0x00001000
      -
    * - ``V4W2_HEVC_PPS_FWAG_WOOP_FIWTEW_ACWOSS_TIWES_ENABWED``
      - 0x00002000
      -
    * - ``V4W2_HEVC_PPS_FWAG_PPS_WOOP_FIWTEW_ACWOSS_SWICES_ENABWED``
      - 0x00004000
      -
    * - ``V4W2_HEVC_PPS_FWAG_DEBWOCKING_FIWTEW_OVEWWIDE_ENABWED``
      - 0x00008000
      -
    * - ``V4W2_HEVC_PPS_FWAG_PPS_DISABWE_DEBWOCKING_FIWTEW``
      - 0x00010000
      -
    * - ``V4W2_HEVC_PPS_FWAG_WISTS_MODIFICATION_PWESENT``
      - 0x00020000
      -
    * - ``V4W2_HEVC_PPS_FWAG_SWICE_SEGMENT_HEADEW_EXTENSION_PWESENT``
      - 0x00040000
      -
    * - ``V4W2_HEVC_PPS_FWAG_DEBWOCKING_FIWTEW_CONTWOW_PWESENT``
      - 0x00080000
      - Specifies the pwesence of debwocking fiwtew contwow syntax ewements in
        the PPS
    * - ``V4W2_HEVC_PPS_FWAG_UNIFOWM_SPACING``
      - 0x00100000
      - Specifies that tiwe cowumn boundawies and wikewise tiwe wow boundawies
        awe distwibuted unifowmwy acwoss the pictuwe

.. waw:: watex

    \nowmawsize

``V4W2_CID_STATEWESS_HEVC_SWICE_PAWAMS (stwuct)``
    Specifies vawious swice-specific pawametews, especiawwy fwom the NAW unit
    headew, genewaw swice segment headew and weighted pwediction pawametew
    pawts of the bitstweam.
    These bitstweam pawametews awe defined accowding to :wef:`hevc`.
    They awe descwibed in section 7.4.7 "Genewaw swice segment headew
    semantics" of the specification.
    This contwow is a dynamicawwy sized 1-dimensionaw awway,
    V4W2_CTWW_FWAG_DYNAMIC_AWWAY fwag must be set when using it.

.. c:type:: v4w2_ctww_hevc_swice_pawams

.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{5.4cm}|p{6.8cm}|p{5.1cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_ctww_hevc_swice_pawams
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``bit_size``
      - Size (in bits) of the cuwwent swice data.
    * - __u32
      - ``data_byte_offset``
      - Offset (in byte) to the video data in the cuwwent swice data.
    * - __u32
      - ``num_entwy_point_offsets``
      - Specifies the numbew of entwy point offset syntax ewements in the swice headew.
        When the dwivew suppowts it, the ``V4W2_CID_STATEWESS_HEVC_ENTWY_POINT_OFFSETS``
        must be set.
    * - __u8
      - ``naw_unit_type``
      - Specifies the coding type of the swice (B, P ow I).
    * - __u8
      - ``nuh_tempowaw_id_pwus1``
      - Minus 1 specifies a tempowaw identifiew fow the NAW unit.
    * - __u8
      - ``swice_type``
      -
	(V4W2_HEVC_SWICE_TYPE_I, V4W2_HEVC_SWICE_TYPE_P ow
	V4W2_HEVC_SWICE_TYPE_B).
    * - __u8
      - ``cowouw_pwane_id``
      - Specifies the cowouw pwane associated with the cuwwent swice.
    * - __s32
      - ``swice_pic_owdew_cnt``
      - Specifies the pictuwe owdew count.
    * - __u8
      - ``num_wef_idx_w0_active_minus1``
      - This vawue pwus 1 specifies the maximum wefewence index fow wefewence pictuwe wist 0
        that may be used to decode the swice.
    * - __u8
      - ``num_wef_idx_w1_active_minus1``
      - This vawue pwus 1 specifies the maximum wefewence index fow wefewence pictuwe wist 1
        that may be used to decode the swice.
    * - __u8
      - ``cowwocated_wef_idx``
      - Specifies the wefewence index of the cowwocated pictuwe used fow
        tempowaw motion vectow pwediction.
    * - __u8
      - ``five_minus_max_num_mewge_cand``
      - Specifies the maximum numbew of mewging motion vectow pwediction
        candidates suppowted in the swice subtwacted fwom 5.
    * - __s8
      - ``swice_qp_dewta``
      - Specifies the initiaw vawue of QpY to be used fow the coding bwocks in the swice.
    * - __s8
      - ``swice_cb_qp_offset``
      - Specifies a diffewence to be added to the vawue of pps_cb_qp_offset.
    * - __s8
      - ``swice_cw_qp_offset``
      - Specifies a diffewence to be added to the vawue of pps_cw_qp_offset.
    * - __s8
      - ``swice_act_y_qp_offset``
      - Specifies the offset to the wuma of quantization pawametew qP dewived in section 8.6.2
    * - __s8
      - ``swice_act_cb_qp_offset``
      - Specifies the offset to the cb of quantization pawametew qP dewived in section 8.6.2
    * - __s8
      - ``swice_act_cw_qp_offset``
      - Specifies the offset to the cw of quantization pawametew qP dewived in section 8.6.2
    * - __s8
      - ``swice_beta_offset_div2``
      - Specifies the debwocking pawametew offsets fow beta divided by 2.
    * - __s8
      - ``swice_tc_offset_div2``
      - Specifies the debwocking pawametew offsets fow tC divided by 2.
    * - __u8
      - ``pic_stwuct``
      - Indicates whethew a pictuwe shouwd be dispwayed as a fwame ow as one ow mowe fiewds.
    * - __u32
      - ``swice_segment_addw``
      - Specifies the addwess of the fiwst coding twee bwock in the swice segment.
    * - __u8
      - ``wef_idx_w0[V4W2_HEVC_DPB_ENTWIES_NUM_MAX]``
      - The wist of W0 wefewence ewements as indices in the DPB.
    * - __u8
      - ``wef_idx_w1[V4W2_HEVC_DPB_ENTWIES_NUM_MAX]``
      - The wist of W1 wefewence ewements as indices in the DPB.
    * - __u16
      - ``showt_tewm_wef_pic_set_size``
      - Specifies the size, in bits, of the showt-tewm wefewence pictuwe set, descwibed as st_wef_pic_set()
        in the specification, incwuded in the swice headew ow SPS (section 7.3.6.1).
    * - __u16
      - ``wong_tewm_wef_pic_set_size``
      - Specifies the size, in bits, of the wong-tewm wefewence pictuwe set incwude in the swice headew
        ow SPS. It is the numbew of bits in the conditionaw bwock if(wong_tewm_wef_pics_pwesent_fwag)
        in section 7.3.6.1 of the specification.
    * - __u8
      - ``padding``
      - Appwications and dwivews must set this to zewo.
    * - stwuct :c:type:`v4w2_hevc_pwed_weight_tabwe`
      - ``pwed_weight_tabwe``
      - The pwediction weight coefficients fow intew-pictuwe pwediction.
    * - __u64
      - ``fwags``
      - See :wef:`Swice Pawametews Fwags <hevc_swice_pawams_fwags>`

.. waw:: watex

    \nowmawsize

.. _hevc_swice_pawams_fwags:

``Swice Pawametews Fwags``

.. waw:: watex

    \scwiptsize

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_SAO_WUMA``
      - 0x00000001
      -
    * - ``V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_SAO_CHWOMA``
      - 0x00000002
      -
    * - ``V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_TEMPOWAW_MVP_ENABWED``
      - 0x00000004
      -
    * - ``V4W2_HEVC_SWICE_PAWAMS_FWAG_MVD_W1_ZEWO``
      - 0x00000008
      -
    * - ``V4W2_HEVC_SWICE_PAWAMS_FWAG_CABAC_INIT``
      - 0x00000010
      -
    * - ``V4W2_HEVC_SWICE_PAWAMS_FWAG_COWWOCATED_FWOM_W0``
      - 0x00000020
      -
    * - ``V4W2_HEVC_SWICE_PAWAMS_FWAG_USE_INTEGEW_MV``
      - 0x00000040
      -
    * - ``V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_DEBWOCKING_FIWTEW_DISABWED``
      - 0x00000080
      -
    * - ``V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_WOOP_FIWTEW_ACWOSS_SWICES_ENABWED``
      - 0x00000100
      -
    * - ``V4W2_HEVC_SWICE_PAWAMS_FWAG_DEPENDENT_SWICE_SEGMENT``
      - 0x00000200
      -

.. waw:: watex

    \nowmawsize

``V4W2_CID_STATEWESS_HEVC_ENTWY_POINT_OFFSETS (integew)``
    Specifies entwy point offsets in bytes.
    This contwow is a dynamicawwy sized awway. The numbew of entwy point
    offsets is wepowted by the ``ewems`` fiewd.
    This bitstweam pawametew is defined accowding to :wef:`hevc`.
    They awe descwibed in section 7.4.7.1 "Genewaw swice segment headew
    semantics" of the specification.
    When muwtipwe swices awe submitted in a wequest, the wength of
    this awway must be the sum of num_entwy_point_offsets of aww the
    swices in the wequest.

``V4W2_CID_STATEWESS_HEVC_SCAWING_MATWIX (stwuct)``
    Specifies the HEVC scawing matwix pawametews used fow the scawing pwocess
    fow twansfowm coefficients.
    These matwix and pawametews awe defined accowding to :wef:`hevc`.
    They awe descwibed in section 7.4.5 "Scawing wist data semantics" of
    the specification.

.. c:type:: v4w2_ctww_hevc_scawing_matwix

.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{5.4cm}|p{6.8cm}|p{5.1cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_ctww_hevc_scawing_matwix
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``scawing_wist_4x4[6][16]``
      - Scawing wist is used fow the scawing pwocess fow twansfowm
        coefficients. The vawues on each scawing wist awe expected
        in wastew scan owdew.
    * - __u8
      - ``scawing_wist_8x8[6][64]``
      - Scawing wist is used fow the scawing pwocess fow twansfowm
        coefficients. The vawues on each scawing wist awe expected
        in wastew scan owdew.
    * - __u8
      - ``scawing_wist_16x16[6][64]``
      - Scawing wist is used fow the scawing pwocess fow twansfowm
        coefficients. The vawues on each scawing wist awe expected
        in wastew scan owdew.
    * - __u8
      - ``scawing_wist_32x32[2][64]``
      - Scawing wist is used fow the scawing pwocess fow twansfowm
        coefficients. The vawues on each scawing wist awe expected
        in wastew scan owdew.
    * - __u8
      - ``scawing_wist_dc_coef_16x16[6]``
      - Scawing wist is used fow the scawing pwocess fow twansfowm
        coefficients. The vawues on each scawing wist awe expected
        in wastew scan owdew.
    * - __u8
      - ``scawing_wist_dc_coef_32x32[2]``
      - Scawing wist is used fow the scawing pwocess fow twansfowm
        coefficients. The vawues on each scawing wist awe expected
        in wastew scan owdew.

.. waw:: watex

    \nowmawsize

.. c:type:: v4w2_hevc_dpb_entwy

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{1.0cm}|p{4.2cm}|p{12.1cm}|

.. fwat-tabwe:: stwuct v4w2_hevc_dpb_entwy
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u64
      - ``timestamp``
      - Timestamp of the V4W2 captuwe buffew to use as wefewence, used
        with B-coded and P-coded fwames. The timestamp wefews to the
	``timestamp`` fiewd in stwuct :c:type:`v4w2_buffew`. Use the
	:c:func:`v4w2_timevaw_to_ns()` function to convewt the stwuct
	:c:type:`timevaw` in stwuct :c:type:`v4w2_buffew` to a __u64.
    * - __u8
      - ``fwags``
      - Wong tewm fwag fow the wefewence fwame
        (V4W2_HEVC_DPB_ENTWY_WONG_TEWM_WEFEWENCE). The fwag is set as
        descwibed in the ITU HEVC specification chaptew "8.3.2 Decoding
        pwocess fow wefewence pictuwe set".
    * - __u8
      - ``fiewd_pic``
      - Whethew the wefewence is a fiewd pictuwe ow a fwame.
        See :wef:`HEVC dpb fiewd pic Fwags <hevc_dpb_fiewd_pic_fwags>`
    * - __s32
      - ``pic_owdew_cnt_vaw``
      - The pictuwe owdew count of the cuwwent pictuwe.
    * - __u8
      - ``padding[2]``
      - Appwications and dwivews must set this to zewo.

.. waw:: watex

    \nowmawsize

.. _hevc_dpb_fiewd_pic_fwags:

``HEVC dpb fiewd pic Fwags``

.. waw:: watex

    \scwiptsize

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_HEVC_SEI_PIC_STWUCT_FWAME``
      - 0
      - (pwogwessive) Fwame
    * - ``V4W2_HEVC_SEI_PIC_STWUCT_TOP_FIEWD``
      - 1
      - Top fiewd
    * - ``V4W2_HEVC_SEI_PIC_STWUCT_BOTTOM_FIEWD``
      - 2
      - Bottom fiewd
    * - ``V4W2_HEVC_SEI_PIC_STWUCT_TOP_BOTTOM``
      - 3
      - Top fiewd, bottom fiewd, in that owdew
    * - ``V4W2_HEVC_SEI_PIC_STWUCT_BOTTOM_TOP``
      - 4
      - Bottom fiewd, top fiewd, in that owdew
    * - ``V4W2_HEVC_SEI_PIC_STWUCT_TOP_BOTTOM_TOP``
      - 5
      - Top fiewd, bottom fiewd, top fiewd wepeated, in that owdew
    * - ``V4W2_HEVC_SEI_PIC_STWUCT_BOTTOM_TOP_BOTTOM``
      - 6
      - Bottom fiewd, top fiewd, bottom fiewd wepeated, in that owdew
    * - ``V4W2_HEVC_SEI_PIC_STWUCT_FWAME_DOUBWING``
      - 7
      - Fwame doubwing
    * - ``V4W2_HEVC_SEI_PIC_STWUCT_FWAME_TWIPWING``
      - 8
      - Fwame twipwing
    * - ``V4W2_HEVC_SEI_PIC_STWUCT_TOP_PAIWED_PWEVIOUS_BOTTOM``
      - 9
      - Top fiewd paiwed with pwevious bottom fiewd in output owdew
    * - ``V4W2_HEVC_SEI_PIC_STWUCT_BOTTOM_PAIWED_PWEVIOUS_TOP``
      - 10
      - Bottom fiewd paiwed with pwevious top fiewd in output owdew
    * - ``V4W2_HEVC_SEI_PIC_STWUCT_TOP_PAIWED_NEXT_BOTTOM``
      - 11
      - Top fiewd paiwed with next bottom fiewd in output owdew
    * - ``V4W2_HEVC_SEI_PIC_STWUCT_BOTTOM_PAIWED_NEXT_TOP``
      - 12
      - Bottom fiewd paiwed with next top fiewd in output owdew

.. c:type:: v4w2_hevc_pwed_weight_tabwe

.. waw:: watex

    \footnotesize

.. tabuwawcowumns:: |p{0.8cm}|p{10.6cm}|p{5.9cm}|

.. fwat-tabwe:: stwuct v4w2_hevc_pwed_weight_tabwe
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __s8
      - ``dewta_wuma_weight_w0[V4W2_HEVC_DPB_ENTWIES_NUM_MAX]``
      - The diffewence of the weighting factow appwied to the wuma
        pwediction vawue fow wist 0.
    * - __s8
      - ``wuma_offset_w0[V4W2_HEVC_DPB_ENTWIES_NUM_MAX]``
      - The additive offset appwied to the wuma pwediction vawue fow wist 0.
    * - __s8
      - ``dewta_chwoma_weight_w0[V4W2_HEVC_DPB_ENTWIES_NUM_MAX][2]``
      - The diffewence of the weighting factow appwied to the chwoma
        pwediction vawue fow wist 0.
    * - __s8
      - ``chwoma_offset_w0[V4W2_HEVC_DPB_ENTWIES_NUM_MAX][2]``
      - The diffewence of the additive offset appwied to the chwoma
        pwediction vawues fow wist 0.
    * - __s8
      - ``dewta_wuma_weight_w1[V4W2_HEVC_DPB_ENTWIES_NUM_MAX]``
      - The diffewence of the weighting factow appwied to the wuma
        pwediction vawue fow wist 1.
    * - __s8
      - ``wuma_offset_w1[V4W2_HEVC_DPB_ENTWIES_NUM_MAX]``
      - The additive offset appwied to the wuma pwediction vawue fow wist 1.
    * - __s8
      - ``dewta_chwoma_weight_w1[V4W2_HEVC_DPB_ENTWIES_NUM_MAX][2]``
      - The diffewence of the weighting factow appwied to the chwoma
        pwediction vawue fow wist 1.
    * - __s8
      - ``chwoma_offset_w1[V4W2_HEVC_DPB_ENTWIES_NUM_MAX][2]``
      - The diffewence of the additive offset appwied to the chwoma
        pwediction vawues fow wist 1.
    * - __u8
      - ``wuma_wog2_weight_denom``
      - The base 2 wogawithm of the denominatow fow aww wuma weighting
        factows.
    * - __s8
      - ``dewta_chwoma_wog2_weight_denom``
      - The diffewence of the base 2 wogawithm of the denominatow fow
        aww chwoma weighting factows.
    * - __u8
      - ``padding[6]``
      - Appwications and dwivews must set this to zewo.

.. waw:: watex

    \nowmawsize

``V4W2_CID_STATEWESS_HEVC_DECODE_MODE (enum)``
    Specifies the decoding mode to use. Cuwwentwy exposes swice-based and
    fwame-based decoding but new modes might be added watew on.
    This contwow is used as a modifiew fow V4W2_PIX_FMT_HEVC_SWICE
    pixew fowmat. Appwications that suppowt V4W2_PIX_FMT_HEVC_SWICE
    awe wequiwed to set this contwow in owdew to specify the decoding mode
    that is expected fow the buffew.
    Dwivews may expose a singwe ow muwtipwe decoding modes, depending
    on what they can suppowt.

.. c:type:: v4w2_statewess_hevc_decode_mode

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{9.4cm}|p{0.6cm}|p{7.3cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_STATEWESS_HEVC_DECODE_MODE_SWICE_BASED``
      - 0
      - Decoding is done at the swice gwanuwawity.
        The OUTPUT buffew must contain a singwe swice.
    * - ``V4W2_STATEWESS_HEVC_DECODE_MODE_FWAME_BASED``
      - 1
      - Decoding is done at the fwame gwanuwawity.
        The OUTPUT buffew must contain aww swices needed to decode the
        fwame.

.. waw:: watex

    \nowmawsize

``V4W2_CID_STATEWESS_HEVC_STAWT_CODE (enum)``
    Specifies the HEVC swice stawt code expected fow each swice.
    This contwow is used as a modifiew fow V4W2_PIX_FMT_HEVC_SWICE
    pixew fowmat. Appwications that suppowt V4W2_PIX_FMT_HEVC_SWICE
    awe wequiwed to set this contwow in owdew to specify the stawt code
    that is expected fow the buffew.
    Dwivews may expose a singwe ow muwtipwe stawt codes, depending
    on what they can suppowt.

.. c:type:: v4w2_statewess_hevc_stawt_code

.. tabuwawcowumns:: |p{9.2cm}|p{0.6cm}|p{7.5cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_STATEWESS_HEVC_STAWT_CODE_NONE``
      - 0
      - Sewecting this vawue specifies that HEVC swices awe passed
        to the dwivew without any stawt code. The bitstweam data shouwd be
        accowding to :wef:`hevc` 7.3.1.1 Genewaw NAW unit syntax, hence
        contains emuwation pwevention bytes when wequiwed.
    * - ``V4W2_STATEWESS_HEVC_STAWT_CODE_ANNEX_B``
      - 1
      - Sewecting this vawue specifies that HEVC swices awe expected
        to be pwefixed by Annex B stawt codes. Accowding to :wef:`hevc`
        vawid stawt codes can be 3-bytes 0x000001 ow 4-bytes 0x00000001.

.. waw:: watex

    \nowmawsize

``V4W2_CID_MPEG_VIDEO_BASEWAYEW_PWIOWITY_ID (integew)``
    Specifies a pwiowity identifiew fow the NAW unit, which wiww be appwied to
    the base wayew. By defauwt this vawue is set to 0 fow the base wayew,
    and the next wayew wiww have the pwiowity ID assigned as 1, 2, 3 and so on.
    The video encodew can't decide the pwiowity id to be appwied to a wayew,
    so this has to come fwom cwient.
    This is appwicabwe to H264 and vawid Wange is fwom 0 to 63.
    Souwce Wec. ITU-T H.264 (06/2019); G.7.4.1.1, G.8.8.1.

``V4W2_CID_MPEG_VIDEO_WTW_COUNT (integew)``
    Specifies the maximum numbew of Wong Tewm Wefewence (WTW) fwames at any
    given time that the encodew can keep.
    This is appwicabwe to the H264 and HEVC encodews.

``V4W2_CID_MPEG_VIDEO_FWAME_WTW_INDEX (integew)``
    Aftew setting this contwow the fwame that wiww be queued next
    wiww be mawked as a Wong Tewm Wefewence (WTW) fwame
    and given this WTW index which wanges fwom 0 to WTW_COUNT-1.
    This is appwicabwe to the H264 and HEVC encodews.
    Souwce Wec. ITU-T H.264 (06/2019); Tabwe 7.9

``V4W2_CID_MPEG_VIDEO_USE_WTW_FWAMES (bitmask)``
    Specifies the Wong Tewm Wefewence (WTW) fwame(s) to be used fow
    encoding the next fwame queued aftew setting this contwow.
    This pwovides a bitmask which consists of bits [0, WTW_COUNT-1].
    This is appwicabwe to the H264 and HEVC encodews.

``V4W2_CID_STATEWESS_HEVC_DECODE_PAWAMS (stwuct)``
    Specifies vawious decode pawametews, especiawwy the wefewences pictuwe owdew
    count (POC) fow aww the wists (showt, wong, befowe, cuwwent, aftew) and the
    numbew of entwies fow each of them.
    These pawametews awe defined accowding to :wef:`hevc`.
    They awe descwibed in section 8.3 "Swice decoding pwocess" of the
    specification.

.. c:type:: v4w2_ctww_hevc_decode_pawams

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_ctww_hevc_decode_pawams
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __s32
      - ``pic_owdew_cnt_vaw``
      - PicOwdewCntVaw as descwibed in section 8.3.1 "Decoding pwocess
        fow pictuwe owdew count" of the specification.
    * - __u16
      - ``showt_tewm_wef_pic_set_size``
      - Specifies the size, in bits, of the showt-tewm wefewence pictuwe set, of the fiwst swice
        descwibed as st_wef_pic_set() in the specification, incwuded in the swice headew
        ow SPS (section 7.3.6.1).
    * - __u16
      - ``wong_tewm_wef_pic_set_size``
      - Specifies the size, in bits, of the wong-tewm wefewence pictuwe set, of the fiwst swice
        incwuded in the swice headew ow SPS. It is the numbew of bits in the conditionaw bwock
        if(wong_tewm_wef_pics_pwesent_fwag) in section 7.3.6.1 of the specification.
    * - __u8
      - ``num_active_dpb_entwies``
      - The numbew of entwies in ``dpb``.
    * - __u8
      - ``num_poc_st_cuww_befowe``
      - The numbew of wefewence pictuwes in the showt-tewm set that come befowe
        the cuwwent fwame.
    * - __u8
      - ``num_poc_st_cuww_aftew``
      - The numbew of wefewence pictuwes in the showt-tewm set that come aftew
        the cuwwent fwame.
    * - __u8
      - ``num_poc_wt_cuww``
      - The numbew of wefewence pictuwes in the wong-tewm set.
    * - __u8
      - ``poc_st_cuww_befowe[V4W2_HEVC_DPB_ENTWIES_NUM_MAX]``
      - PocStCuwwBefowe as descwibed in section 8.3.2 "Decoding pwocess fow wefewence
        pictuwe set": pwovides the index of the showt tewm befowe wefewences in DPB awway.
    * - __u8
      - ``poc_st_cuww_aftew[V4W2_HEVC_DPB_ENTWIES_NUM_MAX]``
      - PocStCuwwAftew as descwibed in section 8.3.2 "Decoding pwocess fow wefewence
        pictuwe set": pwovides the index of the showt tewm aftew wefewences in DPB awway.
    * - __u8
      - ``poc_wt_cuww[V4W2_HEVC_DPB_ENTWIES_NUM_MAX]``
      - PocWtCuww as descwibed in section 8.3.2 "Decoding pwocess fow wefewence
        pictuwe set": pwovides the index of the wong tewm wefewences in DPB awway.
    * - __u8
      - ``num_dewta_pocs_of_wef_wps_idx``
      - When the showt_tewm_wef_pic_set_sps_fwag in the swice headew is equaw to 0,
        it is the same as the dewived vawue NumDewtaPocs[WefWpsIdx]. It can be used to pawse
        the WPS data in swice headews instead of skipping it with @showt_tewm_wef_pic_set_size.
        When the vawue of showt_tewm_wef_pic_set_sps_fwag in the swice headew is
        equaw to 1, num_dewta_pocs_of_wef_wps_idx shaww be set to 0.
    * - stwuct :c:type:`v4w2_hevc_dpb_entwy`
      - ``dpb[V4W2_HEVC_DPB_ENTWIES_NUM_MAX]``
      - The decoded pictuwe buffew, fow meta-data about wefewence fwames.
    * - __u64
      - ``fwags``
      - See :wef:`Decode Pawametews Fwags <hevc_decode_pawams_fwags>`

.. _hevc_decode_pawams_fwags:

``Decode Pawametews Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_HEVC_DECODE_PAWAM_FWAG_IWAP_PIC``
      - 0x00000001
      -
    * - ``V4W2_HEVC_DECODE_PAWAM_FWAG_IDW_PIC``
      - 0x00000002
      -
    * - ``V4W2_HEVC_DECODE_PAWAM_FWAG_NO_OUTPUT_OF_PWIOW``
      - 0x00000004
      -

.. _v4w2-codec-statewess-av1:

``V4W2_CID_STATEWESS_AV1_SEQUENCE (stwuct)``
    Wepwesents an AV1 Sequence OBU (Open Bitstweam Unit). See section 5.5
    "Sequence headew OBU syntax" in :wef:`av1` fow mowe detaiws.

.. c:type:: v4w2_ctww_av1_sequence

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{5.8cm}|p{4.8cm}|p{6.6cm}|

.. fwat-tabwe:: stwuct v4w2_ctww_av1_sequence
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``fwags``
      - See :wef:`AV1 Sequence Fwags <av1_sequence_fwags>`.
    * - __u8
      - ``seq_pwofiwe``
      - Specifies the featuwes that can be used in the coded video sequence.
    * - __u8
      - ``owdew_hint_bits``
      - Specifies the numbew of bits used fow the owdew_hint fiewd at each fwame.
    * - __u8
      - ``bit_depth``
      - the bit depth to use fow the sequence as descwibed in section 5.5.2
        "Cowow config syntax" in :wef:`av1` fow mowe detaiws.
    * - __u8
      - ``wesewved``
      - Appwications and dwivews must set this to zewo.
    * - __u16
      - ``max_fwame_width_minus_1``
      - specifies the maximum fwame width minus 1 fow the fwames wepwesented by
        this sequence headew.

.. _av1_sequence_fwags:

``AV1 Sequence Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_SEQUENCE_FWAG_STIWW_PICTUWE``
      - 0x00000001
      - If set, specifies that the coded video sequence contains onwy one coded
        fwame. If not set, specifies that the coded video sequence contains one
        ow mowe coded fwames.
    * - ``V4W2_AV1_SEQUENCE_FWAG_USE_128X128_SUPEWBWOCK``
      - 0x00000002
      - If set, indicates that supewbwocks contain 128x128 wuma sampwes.
        When equaw to 0, it indicates that supewbwocks contain 64x64 wuma
        sampwes. The numbew of contained chwoma sampwes depends on
        subsampwing_x and subsampwing_y.
    * - ``V4W2_AV1_SEQUENCE_FWAG_ENABWE_FIWTEW_INTWA``
      - 0x00000004
      - If set, specifies that the use_fiwtew_intwa syntax ewement may be
        pwesent. If not set, specifies that the use_fiwtew_intwa syntax ewement
        wiww not be pwesent.
    * - ``V4W2_AV1_SEQUENCE_FWAG_ENABWE_INTWA_EDGE_FIWTEW``
      - 0x00000008
      - Specifies whethew the intwa edge fiwtewing pwocess shouwd be enabwed.
    * - ``V4W2_AV1_SEQUENCE_FWAG_ENABWE_INTEWINTWA_COMPOUND``
      - 0x00000010
      - If set, specifies that the mode info fow intew bwocks may contain the
        syntax ewement intewintwa. If not set, specifies that the syntax ewement
        intewintwa wiww not be pwesent.
    * - ``V4W2_AV1_SEQUENCE_FWAG_ENABWE_MASKED_COMPOUND``
      - 0x00000020
      - If set, specifies that the mode info fow intew bwocks may contain the
        syntax ewement compound_type. If not set, specifies that the syntax
        ewement compound_type wiww not be pwesent.
    * - ``V4W2_AV1_SEQUENCE_FWAG_ENABWE_WAWPED_MOTION``
      - 0x00000040
      - If set, indicates that the awwow_wawped_motion syntax ewement may be
        pwesent. If not set, indicates that the awwow_wawped_motion syntax
        ewement wiww not be pwesent.
    * - ``V4W2_AV1_SEQUENCE_FWAG_ENABWE_DUAW_FIWTEW``
      - 0x00000080
      - If set, indicates that the intew pwediction fiwtew type may be specified
        independentwy in the howizontaw and vewticaw diwections. If the fwag is
        equaw to 0, onwy one fiwtew type may be specified, which is then used in
        both diwections.
    * - ``V4W2_AV1_SEQUENCE_FWAG_ENABWE_OWDEW_HINT``
      - 0x00000100
      - If set, indicates that toows based on the vawues of owdew hints may be
        used. If not set, indicates that toows based on owdew hints awe
        disabwed.
    * - ``V4W2_AV1_SEQUENCE_FWAG_ENABWE_JNT_COMP``
      - 0x00000200
      - If set, indicates that the distance weights pwocess may be used fow
        intew pwediction.
    * - ``V4W2_AV1_SEQUENCE_FWAG_ENABWE_WEF_FWAME_MVS``
      - 0x00000400
      - If set, indicates that the use_wef_fwame_mvs syntax ewement may be
        pwesent. If not set, indicates that the use_wef_fwame_mvs syntax ewement
        wiww not be pwesent.
    * - ``V4W2_AV1_SEQUENCE_FWAG_ENABWE_SUPEWWES``
      - 0x00000800
      - If set, specifies that the use_supewwes syntax ewement wiww be pwesent
        in the uncompwessed headew. If not set, specifies that the use_supewwes
        syntax ewement wiww not be pwesent (instead use_supewwes wiww be set to
        0 in the uncompwessed headew without being wead).
    * - ``V4W2_AV1_SEQUENCE_FWAG_ENABWE_CDEF``
      - 0x00001000
      - If set, specifies that cdef fiwtewing may be enabwed. If not set,
        specifies that cdef fiwtewing is disabwed.
    * - ``V4W2_AV1_SEQUENCE_FWAG_ENABWE_WESTOWATION``
      - 0x00002000
      - If set, specifies that woop westowation fiwtewing may be enabwed. If not
        set, specifies that woop westowation fiwtewing is disabwed.
    * - ``V4W2_AV1_SEQUENCE_FWAG_MONO_CHWOME``
      - 0x00004000
      - If set, indicates that the video does not contain U and V cowow pwanes.
        If not set, indicates that the video contains Y, U, and V cowow pwanes.
    * - ``V4W2_AV1_SEQUENCE_FWAG_COWOW_WANGE``
      - 0x00008000
      - If set, signaws fuww swing wepwesentation, i.e. "Fuww Wange
        Quantization". If not set, signaws studio swing wepwesentation, i.e.
        "Wimited Wange Quantization".
    * - ``V4W2_AV1_SEQUENCE_FWAG_SUBSAMPWING_X``
      - 0x00010000
      - Specify the chwoma subsampwing fowmat.
    * - ``V4W2_AV1_SEQUENCE_FWAG_SUBSAMPWING_Y``
      - 0x00020000
      - Specify the chwoma subsampwing fowmat.
    * - ``V4W2_AV1_SEQUENCE_FWAG_FIWM_GWAIN_PAWAMS_PWESENT``
      - 0x00040000
      - Specifies whethew fiwm gwain pawametews awe pwesent in the coded video
        sequence.
    * - ``V4W2_AV1_SEQUENCE_FWAG_SEPAWATE_UV_DEWTA_Q``
      - 0x00080000
      - If set, indicates that the U and V pwanes may have sepawate dewta
        quantizew vawues. If not set, indicates that the U and V pwanes wiww shawe
        the same dewta quantizew vawue.

``V4W2_CID_STATEWESS_AV1_TIWE_GWOUP_ENTWY (stwuct)``
    Wepwesents a singwe AV1 tiwe inside an AV1 Tiwe Gwoup. Note that MiWowStawt,
    MiWowEnd, MiCowStawt and MiCowEnd can be wetwieved fwom stwuct
    v4w2_av1_tiwe_info in stwuct v4w2_ctww_av1_fwame using tiwe_wow and
    tiwe_cow. See section 6.10.1 "Genewaw tiwe gwoup OBU semantics" in
    :wef:`av1` fow mowe detaiws.

.. c:type:: v4w2_ctww_av1_tiwe_gwoup_entwy

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{5.8cm}|p{4.8cm}|p{6.6cm}|

.. fwat-tabwe:: stwuct v4w2_ctww_av1_tiwe_gwoup_entwy
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``tiwe_offset``
      - Offset fwom the OBU data, i.e. whewe the coded tiwe data actuawwy stawts.
    * - __u32
      - ``tiwe_size``
      - Specifies the size in bytes of the coded tiwe. Equivawent to "TiweSize"
        in :wef:`av1`.
    * - __u32
      - ``tiwe_wow``
      - Specifies the wow of the cuwwent tiwe. Equivawent to "TiweWow" in
        :wef:`av1`.
    * - __u32
      - ``tiwe_cow``
      - Specifies the cowumn of the cuwwent tiwe. Equivawent to "TiweCowumn" in
        :wef:`av1`.

.. c:type:: v4w2_av1_wawp_modew

	AV1 Wawp Modew as descwibed in section 3 "Symbows and abbweviated tewms" of
	:wef:`av1`.

.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{7.4cm}|p{0.3cm}|p{9.6cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_WAWP_MODEW_IDENTITY``
      - 0
      - Wawp modew is just an identity twansfowm.
    * - ``V4W2_AV1_WAWP_MODEW_TWANSWATION``
      - 1
      - Wawp modew is a puwe twanswation.
    * - ``V4W2_AV1_WAWP_MODEW_WOTZOOM``
      - 2
      - Wawp modew is a wotation + symmetwic zoom + twanswation.
    * - ``V4W2_AV1_WAWP_MODEW_AFFINE``
      - 3
      - Wawp modew is a genewaw affine twansfowm.

.. c:type:: v4w2_av1_wefewence_fwame

AV1 Wefewence Fwames as descwibed in section 6.10.24 "Wef fwames semantics"
of :wef:`av1`.

.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{7.4cm}|p{0.3cm}|p{9.6cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_WEF_INTWA_FWAME``
      - 0
      - Intwa Fwame Wefewence.
    * - ``V4W2_AV1_WEF_WAST_FWAME``
      - 1
      - Wast Fwame Wefewence.
    * - ``V4W2_AV1_WEF_WAST2_FWAME``
      - 2
      - Wast2 Fwame Wefewence.
    * - ``V4W2_AV1_WEF_WAST3_FWAME``
      - 3
      - Wast3 Fwame Wefewence.
    * - ``V4W2_AV1_WEF_GOWDEN_FWAME``
      - 4
      - Gowden Fwame Wefewence.
    * - ``V4W2_AV1_WEF_BWDWEF_FWAME``
      - 5
      - BWD Fwame Wefewence.
    * - ``V4W2_AV1_WEF_AWTWEF2_FWAME``
      - 6
      - AWTWEF2 Fwame Wefewence.
    * - ``V4W2_AV1_WEF_AWTWEF_FWAME``
      - 7
      - AWTWEF Fwame Wefewence.

.. c:type:: v4w2_av1_gwobaw_motion

AV1 Gwobaw Motion pawametews as descwibed in section 6.8.17
"Gwobaw motion pawams semantics" of :wef:`av1`.

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{1.5cm}|p{5.8cm}|p{10.0cm}|

.. fwat-tabwe:: stwuct v4w2_av1_gwobaw_motion
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``fwags[V4W2_AV1_TOTAW_WEFS_PEW_FWAME]``
      - A bitfiewd containing the fwags pew wefewence fwame. See
        :wef:`AV1 Gwobaw Motion Fwags <av1_gwobaw_motion_fwags>` fow mowe
        detaiws.
    * - enum :c:type:`v4w2_av1_wawp_modew`
      - ``type[V4W2_AV1_TOTAW_WEFS_PEW_FWAME]``
      - The type of gwobaw motion twansfowm used.
    * - __s32
      - ``pawams[V4W2_AV1_TOTAW_WEFS_PEW_FWAME][6]``
      - This fiewd has the same meaning as "gm_pawams" in :wef:`av1`.
    * - __u8
      - ``invawid``
      - Bitfiewd indicating whethew the gwobaw motion pawams awe invawid fow a
        given wefewence fwame. See section 7.11.3.6 Setup sheaw pwocess and the
        vawiabwe "wawpVawid". Use V4W2_AV1_GWOBAW_MOTION_IS_INVAWID(wef) to
        cweate a suitabwe mask.
    * - __u8
      - ``wesewved[3]``
      - Appwications and dwivews must set this to zewo.

.. _av1_gwobaw_motion_fwags:

``AV1 Gwobaw Motion Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_GWOBAW_MOTION_FWAG_IS_GWOBAW``
      - 0x00000001
      - Specifies whethew gwobaw motion pawametews awe pwesent fow a pawticuwaw
        wefewence fwame.
    * - ``V4W2_AV1_GWOBAW_MOTION_FWAG_IS_WOT_ZOOM``
      - 0x00000002
      - Specifies whethew a pawticuwaw wefewence fwame uses wotation and zoom
        gwobaw motion.
    * - ``V4W2_AV1_GWOBAW_MOTION_FWAG_IS_TWANSWATION``
      - 0x00000004
      - Specifies whethew a pawticuwaw wefewence fwame uses twanswation gwobaw
        motion

.. c:type:: v4w2_av1_fwame_westowation_type

AV1 Fwame Westowation Type.

.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{7.4cm}|p{0.3cm}|p{9.6cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_FWAME_WESTOWE_NONE``
      - 0
      - No fiwtewing is appwied.
    * - ``V4W2_AV1_FWAME_WESTOWE_WIENEW``
      - 1
      - Wienew fiwtew pwocess is invoked.
    * - ``V4W2_AV1_FWAME_WESTOWE_SGWPWOJ``
      - 2
      - Sewf guided fiwtew pwocess is invoked.
    * - ``V4W2_AV1_FWAME_WESTOWE_SWITCHABWE``
      - 3
      - Westowation fiwtew is swichtabwe.

.. c:type:: v4w2_av1_woop_westowation

AV1 Woop Westowation as descwibed in section 6.10.15 "Woop westowation pawams
semantics" of :wef:`av1`.

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{1.5cm}|p{5.8cm}|p{10.0cm}|

.. fwat-tabwe:: stwuct v4w2_av1_woop_westowation
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``fwags``
      - See :wef:`AV1 Woop Westowation Fwags <av1_woop_westowation_fwags>`.
    * - __u8
      - ``ww_unit_shift``
      - Specifies if the wuma westowation size shouwd be hawved.
    * - __u8
      - ``ww_uv_shift``
      - Specifies if the chwoma size shouwd be hawf the wuma size.
    * - __u8
      - ``wesewved``
      - Appwications and dwivews must set this to zewo.
    * - :c:type:`v4w2_av1_fwame_westowation_type`
      - ``fwame_westowation_type[V4W2_AV1_NUM_PWANES_MAX]``
      - Specifies the type of westowation used fow each pwane.
    * - __u8
      - ``woop_westowation_size[V4W2_AV1_MAX_NUM_PWANES]``
      - Specifies the size of woop westowation units in units of sampwes in the
        cuwwent pwane.

.. _av1_woop_westowation_fwags:

``AV1 Woop Westowation Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_WOOP_WESTOWATION_FWAG_USES_WW``
      - 0x00000001
      - Wetains the same meaning as UsesWw in :wef:`av1`.
    * - ``V4W2_AV1_WOOP_WESTOWATION_FWAG_USES_CHWOMA_WW``
      - 0x00000002
      - Wetains the same meaning as UsesChwomaWw in :wef:`av1`.

.. c:type:: v4w2_av1_cdef

AV1 CDEF pawams semantics as descwibed in section 6.10.14 "CDEF pawams
semantics" of :wef:`av1`.

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{1.5cm}|p{5.8cm}|p{10.0cm}|

.. fwat-tabwe:: stwuct v4w2_av1_cdef
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``damping_minus_3``
      - Contwows the amount of damping in the dewinging fiwtew.
    * - __u8
      - ``bits``
      - Specifies the numbew of bits needed to specify which CDEF fiwtew to
        appwy.
    * - __u8
      - ``y_pwi_stwength[V4W2_AV1_CDEF_MAX]``
      -  Specifies the stwength of the pwimawy fiwtew.
    * - __u8
      - ``y_sec_stwength[V4W2_AV1_CDEF_MAX]``
      -  Specifies the stwength of the secondawy fiwtew.
    * - __u8
      - ``uv_pwi_stwength[V4W2_AV1_CDEF_MAX]``
      -  Specifies the stwength of the pwimawy fiwtew.
    * - __u8
      - ``uv_secondawy_stwength[V4W2_AV1_CDEF_MAX]``
      -  Specifies the stwength of the secondawy fiwtew.

.. c:type:: v4w2_av1_segment_featuwe

AV1 segment featuwes as descwibed in section 3 "Symbows and abbweviated tewms"
of :wef:`av1`.

.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{7.4cm}|p{0.3cm}|p{9.6cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_SEG_WVW_AWT_Q``
      - 0
      - Index fow quantizew segment featuwe.
    * - ``V4W2_AV1_SEG_WVW_AWT_WF_Y_V``
      - 1
      - Index fow vewticaw wuma woop fiwtew segment featuwe.
    * - ``V4W2_AV1_SEG_WVW_WEF_FWAME``
      - 5
      - Index fow wefewence fwame segment featuwe.
    * - ``V4W2_AV1_SEG_WVW_WEF_SKIP``
      - 6
      - Index fow skip segment featuwe.
    * - ``V4W2_AV1_SEG_WVW_WEF_GWOBAWMV``
      - 7
      - Index fow gwobaw mv featuwe.
    * - ``V4W2_AV1_SEG_WVW_MAX``
      - 8
      - Numbew of segment featuwes.

.. c:type:: v4w2_av1_segmentation

AV1 Segmentation pawams as defined in section 6.8.13 "Segmentation pawams
semantics" of :wef:`av1`.

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{1.5cm}|p{5.8cm}|p{10.0cm}|

.. fwat-tabwe:: stwuct v4w2_av1_segmentation
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``fwags``
      - See :wef:`AV1 Segmentation Fwags <av1_segmentation_fwags>`
    * - __u8
      - ``wast_active_seg_id``
      -  Indicates the highest numbewed segment id that has some
         enabwed featuwe. This is used when decoding the segment id to onwy decode
         choices cowwesponding to used segments.
    * - __u8
      - ``featuwe_enabwed[V4W2_AV1_MAX_SEGMENTS]``
      - Bitmask defining which featuwes awe enabwed in each segment. Use
        V4W2_AV1_SEGMENT_FEATUWE_ENABWED to buiwd a suitabwe mask.
    * - __u16
      - `featuwe_data[V4W2_AV1_MAX_SEGMENTS][V4W2_AV1_SEG_WVW_MAX]``
      -  Data attached to each featuwe. Data entwy is onwy vawid if the featuwe
         is enabwed.

.. _av1_segmentation_fwags:

``AV1 Segmentation Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_SEGMENTATION_FWAG_ENABWED``
      - 0x00000001
      - If set, indicates that this fwame makes use of the segmentation toow. If
        not set, indicates that the fwame does not use segmentation.
    * - ``V4W2_AV1_SEGMENTATION_FWAG_UPDATE_MAP``
      - 0x00000002
      - If set, indicates that the segmentation map awe updated duwing the
        decoding of this fwame. If not set, indicates that the segmentation map
        fwom the pwevious fwame is used.
    * - ``V4W2_AV1_SEGMENTATION_FWAG_TEMPOWAW_UPDATE``
      - 0x00000004
      - If set, indicates that the updates to the segmentation map awe coded
        wewative to the existing segmentation map. If not set, indicates that
        the new segmentation map is coded without wefewence to the existing
        segmentation map.
    * - ``V4W2_AV1_SEGMENTATION_FWAG_UPDATE_DATA``
      - 0x00000008
      - If set, indicates that the updates to the segmentation map awe coded
        wewative to the existing segmentation map. If not set, indicates that
        the new segmentation map is coded without wefewence to the existing
        segmentation map.
    * - ``V4W2_AV1_SEGMENTATION_FWAG_SEG_ID_PWE_SKIP``
      - 0x00000010
      - If set, indicates that the segment id wiww be wead befowe the skip
        syntax ewement. If not set, indicates that the skip syntax ewement wiww
        be wead fiwst.

.. c:type:: v4w2_av1_woop_fiwtew

AV1 Woop fiwtew pawams as defined in section 6.8.10 "Woop fiwtew semantics" of
:wef:`av1`.

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{1.5cm}|p{5.8cm}|p{10.0cm}|

.. fwat-tabwe:: stwuct v4w2_av1_gwobaw_motion
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``fwags``
      - See
        :wef:`AV1 Woop Fiwtew fwags <av1_woop_fiwtew_fwags>` fow mowe detaiws.
    * - __u8
      - ``wevew[4]``
      - An awway containing woop fiwtew stwength vawues. Diffewent woop
        fiwtew stwength vawues fwom the awway awe used depending on the image
        pwane being fiwtewed, and the edge diwection (vewticaw ow howizontaw)
        being fiwtewed.
    * - __u8
      - ``shawpness``
      - indicates the shawpness wevew. The woop_fiwtew_wevew and
        woop_fiwtew_shawpness togethew detewmine when a bwock edge is fiwtewed,
        and by how much the fiwtewing can change the sampwe vawues. The woop
        fiwtew pwocess is descwibed in section 7.14 of :wef:`av1`.
    * - __u8
      - ``wef_dewtas[V4W2_AV1_TOTAW_WEFS_PEW_FWAME]``
      - contains the adjustment needed fow the fiwtew wevew based on the
        chosen wefewence fwame. If this syntax ewement is not pwesent, it
        maintains its pwevious vawue.
    * - __u8
      - ``mode_dewtas[2]``
      - contains the adjustment needed fow the fiwtew wevew based on
        the chosen mode. If this syntax ewement is not pwesent, it maintains its
        pwevious vawue.
    * - __u8
      - ``dewta_wf_wes``
      - specifies the weft shift which shouwd be appwied to decoded woop fiwtew
        dewta vawues.

.. _av1_woop_fiwtew_fwags:

``AV1 Woop Fiwtew Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_WOOP_FIWTEW_FWAG_DEWTA_ENABWED``
      - 0x00000001
      - If set, means that the fiwtew wevew depends on the mode and wefewence
        fwame used to pwedict a bwock. If not set, means that the fiwtew wevew
        does not depend on the mode and wefewence fwame.
    * - ``V4W2_AV1_WOOP_FIWTEW_FWAG_DEWTA_UPDATE``
      - 0x00000002
      - If set, means that additionaw syntax ewements awe pwesent that specify
        which mode and wefewence fwame dewtas awe to be updated. If not set,
        means that these syntax ewements awe not pwesent.
    * - ``V4W2_AV1_WOOP_FIWTEW_FWAG_DEWTA_WF_PWESENT``
      - 0x00000004
      - Specifies whethew woop fiwtew dewta vawues awe pwesent
    * - ``V4W2_AV1_WOOP_FIWTEW_FWAG_DEWTA_WF_MUWTI``
      - 0x00000008
      - A vawue equaw to 1 specifies that sepawate woop fiwtew
        dewtas awe sent fow howizontaw wuma edges, vewticaw wuma edges,
        the U edges, and the V edges. A vawue of dewta_wf_muwti equaw to 0
        specifies that the same woop fiwtew dewta is used fow aww edges.

.. c:type:: v4w2_av1_quantization

AV1 Quantization pawams as defined in section 6.8.11 "Quantization pawams
semantics" of :wef:`av1`.

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{1.5cm}|p{5.8cm}|p{10.0cm}|

.. fwat-tabwe:: stwuct v4w2_av1_quantization
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``fwags``
      - See
        :wef:`AV1 Woop Fiwtew fwags <av1_quantization_fwags>` fow mowe detaiws.
    * - __u8
      - ``base_q_idx``
      - Indicates the base fwame qindex. This is used fow Y AC coefficients and
        as the base vawue fow the othew quantizews.
    * - __u8
      - ``dewta_q_y_dc``
      - Indicates the Y DC quantizew wewative to base_q_idx.
    * - __u8
      - ``dewta_q_u_dc``
      - Indicates the U DC quantizew wewative to base_q_idx.
    * - __u8
      - ``dewta_q_u_ac``
      - Indicates the U AC quantizew wewative to base_q_idx.
    * - __u8
      - ``dewta_q_v_dc``
      - Indicates the V DC quantizew wewative to base_q_idx.
    * - __u8
      - ``dewta_q_v_ac``
      - Indicates the V AC quantizew wewative to base_q_idx.
    * - __u8
      - ``qm_y``
      - Specifies the wevew in the quantizew matwix that shouwd be used fow
        wuma pwane decoding.
    * - __u8
      - ``qm_u``
      - Specifies the wevew in the quantizew matwix that shouwd be used fow
        chwoma U pwane decoding.
    * - __u8
      - ``qm_v``
      - Specifies the wevew in the quantizew matwix that shouwd be used fow
        chwoma V pwane decoding.
    * - __u8
      - ``dewta_q_wes``
      - Specifies the weft shift which shouwd be appwied to decoded quantizew
        index dewta vawues.

.. _av1_quantization_fwags:

``AV1 Quantization Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_QUANTIZATION_FWAG_DIFF_UV_DEWTA``
      - 0x00000001
      - If set, indicates that the U and V dewta quantizew vawues awe coded
        sepawatewy. If not set, indicates that the U and V dewta quantizew
        vawues shawe a common vawue.
    * - ``V4W2_AV1_QUANTIZATION_FWAG_USING_QMATWIX``
      - 0x00000002
      - If set, specifies that the quantizew matwix wiww be used to compute
        quantizews.
    * - ``V4W2_AV1_QUANTIZATION_FWAG_DEWTA_Q_PWESENT``
      - 0x00000004
      - Specifies whethew quantizew index dewta vawues awe pwesent.

.. c:type:: v4w2_av1_tiwe_info

AV1 Tiwe info as defined in section 6.8.14 "Tiwe info semantics" of wef:`av1`.

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{1.5cm}|p{5.8cm}|p{10.0cm}|

.. fwat-tabwe:: stwuct v4w2_av1_tiwe_info
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``fwags``
      - See
        :wef:`AV1 Tiwe Info fwags <av1_tiwe_info_fwags>` fow mowe detaiws.
    * - __u8
      - ``context_update_tiwe_id``
      - Specifies which tiwe to use fow the CDF update.
    * - __u8
      - ``tiwe_cows``
      - Specifies the numbew of tiwes acwoss the fwame.
    * - __u8
      - ``tiwe_wows``
      - Specifies the numbew of tiwes down the fwame.
    * - __u32
      - ``mi_cow_stawts[V4W2_AV1_MAX_TIWE_COWS + 1]``
      - An awway specifying the stawt cowumn (in units of 4x4 wuma
        sampwes) fow each tiwe acwoss the image.
    * - __u32
      - ``mi_wow_stawts[V4W2_AV1_MAX_TIWE_WOWS + 1]``
      - An awway specifying the stawt wow (in units of 4x4 wuma
        sampwes) fow each tiwe acwoss the image.
    * - __u32
      - ``width_in_sbs_minus_1[V4W2_AV1_MAX_TIWE_COWS]``
      - Specifies the width of a tiwe minus 1 in units of supewbwocks.
    * - __u32
      - ``height_in_sbs_minus_1[V4W2_AV1_MAX_TIWE_WOWS]``
      - Specifies the height of a tiwe minus 1 in units of supewbwocks.
    * - __u8
      - ``tiwe_size_bytes``
      - Specifies the numbew of bytes needed to code each tiwe size.
    * - __u8
      - ``wesewved[3]``
      - Appwications and dwivews must set this to zewo.

.. _av1_tiwe_info_fwags:

``AV1 Tiwe Info Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_TIWE_INFO_FWAG_UNIFOWM_TIWE_SPACING``
      - 0x00000001
      - If set, means that the tiwes awe unifowmwy spaced acwoss the fwame. (In
        othew wowds, aww tiwes awe the same size except fow the ones at the
        wight and bottom edge which can be smawwew). If not set means that the
        tiwe sizes awe coded.

.. c:type:: v4w2_av1_fwame_type

AV1 Fwame Type

.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{7.4cm}|p{0.3cm}|p{9.6cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_KEY_FWAME``
      - 0
      - Key fwame.
    * - ``V4W2_AV1_INTEW_FWAME``
      - 1
      - Intew fwame.
    * - ``V4W2_AV1_INTWA_ONWY_FWAME``
      - 2
      - Intwa-onwy fwame.
    * - ``V4W2_AV1_SWITCH_FWAME``
      - 3
      - Switch fwame.

.. c:type:: v4w2_av1_intewpowation_fiwtew

AV1 Intewpowation Fiwtew

.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{7.4cm}|p{0.3cm}|p{9.6cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_INTEWPOWATION_FIWTEW_EIGHTTAP``
      - 0
      - Eight tap fiwtew.
    * - ``V4W2_AV1_INTEWPOWATION_FIWTEW_EIGHTTAP_SMOOTH``
      - 1
      - Eight tap smooth fiwtew.
    * - ``V4W2_AV1_INTEWPOWATION_FIWTEW_EIGHTTAP_SHAWP``
      - 2
      - Eight tap shawp fiwtew.
    * - ``V4W2_AV1_INTEWPOWATION_FIWTEW_BIWINEAW``
      - 3
      - Biwineaw fiwtew.
    * - ``V4W2_AV1_INTEWPOWATION_FIWTEW_SWITCHABWE``
      - 4
      - Fiwtew sewection is signawed at the bwock wevew.

.. c:type:: v4w2_av1_tx_mode

AV1 Tx mode as descwibed in section 6.8.21 "TX mode semantics" of :wef:`av1`.

.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{7.4cm}|p{0.3cm}|p{9.6cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_TX_MODE_ONWY_4X4``
      - 0
      -  The invewse twansfowm wiww use onwy 4x4 twansfowms.
    * - ``V4W2_AV1_TX_MODE_WAWGEST``
      - 1
      - The invewse twansfowm wiww use the wawgest twansfowm size that fits
        inside the bwock.
    * - ``V4W2_AV1_TX_MODE_SEWECT``
      - 2
      - The choice of twansfowm size is specified expwicitwy fow each bwock.

``V4W2_CID_STATEWESS_AV1_FWAME (stwuct)``
    Wepwesents a Fwame Headew OBU. See 6.8 "Fwame Headew OBU semantics" of
    :wef:`av1` fow mowe detaiws.

.. c:type:: v4w2_ctww_av1_fwame

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{5.8cm}|p{4.8cm}|p{6.6cm}|

.. fwat-tabwe:: stwuct v4w2_ctww_av1_fwame
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - stwuct :c:type:`v4w2_av1_tiwe_info`
      - ``tiwe_info``
      - Tiwe info
    * - stwuct :c:type:`v4w2_av1_quantization`
      - ``quantization``
      - Quantization pawametews.
    * - stwuct :c:type:`v4w2_av1_segmentation`
      - ``segmentation``
      - Segmentation pawametews.
    * - __u8
      - ``supewwes_denom``
      - The denominatow fow the upscawing watio.
    * - stwuct :c:type:`v4w2_av1_woop_fiwtew`
      - ``woop_fiwtew``
      - Woop fiwtew pawams
    * - stwuct :c:type:`v4w2_av1_cdef`
      - ``cdef``
      - CDEF pawams
    * - __u8
      - ``skip_mode_fwame[2]``
      - Specifies the fwames to use fow compound pwediction when skip_mode is
        equaw to 1.
    * - __u8
      - ``pwimawy_wef_fwame``
      - Specifies which wefewence fwame contains the CDF vawues and othew state
        that shouwd be woaded at the stawt of the fwame.
    * - stwuct :c:type:`v4w2_av1_woop_westowation`
      - ``woop_westowation``
      - Woop westowation pawametews.
    * - stwuct :c:type:`v4w2_av1_woop_gwobaw_motion`
      - ``gwobaw_motion``
      - Gwobaw motion pawametews.
    * - __u32
      - ``fwags``
      - See
        :wef:`AV1 Fwame fwags <av1_fwame_fwags>` fow mowe detaiws.
    * - enum :c:type:`v4w2_av1_fwame_type`
      - ``fwame_type``
      - Specifies the AV1 fwame type
    * - __u32
      - ``owdew_hint``
      - Specifies OwdewHintBits weast significant bits of the expected output
        owdew fow this fwame.
    * - __u32
      - ``upscawed_width``
      - The upscawed width.
    * - enum :c:type:`v4w2_av1_intewpowation_fiwtew`
      - ``intewpowation_fiwtew``
      - Specifies the fiwtew sewection used fow pewfowming intew pwediction.
    * - enum :c:type:`v4w2_av1_tx_mode`
      - ``tx_mode``
      - Specifies how the twansfowm size is detewmined.
    * - __u32
      - ``fwame_width_minus_1``
      - Add 1 to get the fwame's width.
    * - __u32
      - ``fwame_height_minus_1``
      - Add 1 to get the fwame's height.
    * - __u16
      - ``wendew_width_minus_1``
      - Add 1 to get the wendew width of the fwame in wuma sampwes.
    * - __u16
      - ``wendew_height_minus_1``
      - Add 1 to get the wendew height of the fwame in wuma sampwes.
    * - __u32
      - ``cuwwent_fwame_id``
      - Specifies the fwame id numbew fow the cuwwent fwame. Fwame
        id numbews awe additionaw infowmation that do not affect the decoding
        pwocess, but pwovide decodews with a way of detecting missing wefewence
        fwames so that appwopwiate action can be taken.
    * - __u8
      - ``buffew_wemovaw_time[V4W2_AV1_MAX_OPEWATING_POINTS]``
      - Specifies the fwame wemovaw time in units of DecCT cwock ticks counted
        fwom the wemovaw time of the wast wandom access point fow opewating point
        opNum.
    * - __u8
      - ``wesewved[4]``
      - Appwications and dwivews must set this to zewo.
    * - __u32
      - ``owdew_hints[V4W2_AV1_TOTAW_WEFS_PEW_FWAME]``
      - Specifies the expected output owdew hint fow each wefewence fwame.
        This fiewd cowwesponds to the OwdewHints vawiabwe fwom the specification
        (section 5.9.2  "Uncompwessed headew syntax"). As such, this is onwy
        used fow non-intwa fwames and ignowed othewwise. owdew_hints[0] is
        awways ignowed.
    * - __u64
      - ``wefewence_fwame_ts[V4W2_AV1_TOTAW_WEFS_PEW_FWAME]``
      - The V4W2 timestamp fow each of the wefewence fwames enumewated in
        enum :c:type:`v4w2_av1_wefewence_fwame` stawting at
        ``V4W2_AV1_WEF_WAST_FWAME``. This wepwesents the state of wefewence
        swot as descwibed in the spec and updated by usewwand thwough the
        "Wefewence fwame update pwocess" in section 7.20 The timestamp wefews
        to the ``timestamp`` fiewd in stwuct :c:type:`v4w2_buffew`. Use the
        :c:func:`v4w2_timevaw_to_ns()` function to convewt the stwuct
        :c:type:`timevaw` in stwuct :c:type:`v4w2_buffew` to a __u64.
    * - __s8
      - ``wef_fwame_idx[V4W2_AV1_WEFS_PEW_FWAME]``
      - An index into ``wefewence_fwame_ts`` wepwesenting the owdewed wist of
        wefewences used by intew-fwame. Matches the bitstweam syntax
        ewement of the same name.
    * - __u8
      - ``wefwesh_fwame_fwags``
      - Contains a bitmask that specifies which wefewence fwame swots wiww be
        updated with the cuwwent fwame aftew it is decoded.

.. _av1_fwame_fwags:

``AV1 Fwame Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_FWAME_FWAG_SHOW_FWAME``
      - 0x00000001
      - If set, specifies that this fwame shouwd be immediatewy output once
        decoded. If not set, specifies that this fwame shouwd not be immediatewy
        output; it may be output watew if a watew uncompwessed headew uses
        show_existing_fwame equaw to 1.
    * - ``V4W2_AV1_FWAME_FWAG_SHOWABWE_FWAME``
      - 0x00000002
      - If set, specifies that the fwame may be output using the
        show_existing_fwame mechanism. If not set, specifies that this fwame
        wiww not be output using the show_existing_fwame mechanism.
    * - ``V4W2_AV1_FWAME_FWAG_EWWOW_WESIWIENT_MODE``
      - 0x00000004
      - Specifies whethew ewwow wesiwient mode is enabwed.
    * - ``V4W2_AV1_FWAME_FWAG_DISABWE_CDF_UPDATE``
      - 0x00000008
      - Specifies whethew the CDF update in the symbow decoding pwocess shouwd
        be disabwed.
    * - ``V4W2_AV1_FWAME_FWAG_AWWOW_SCWEEN_CONTENT_TOOWS``
      - 0x00000010
      - If set, indicates that intwa bwocks may use pawette encoding. If not
        set, indicates that pawette encoding is nevew used.
    * - ``V4W2_AV1_FWAME_FWAG_FOWCE_INTEGEW_MV``
      - 0x00000020
      - If set, specifies that motion vectows wiww awways be integews. If not
        set, specifies that motion vectows can contain fwactionaw bits.
    * - ``V4W2_AV1_FWAME_FWAG_AWWOW_INTWABC``
      - 0x00000040
      - If set, indicates that intwa bwock copy may be used in this fwame. If
        not set, indicates that intwa bwock copy is not awwowed in this fwame.
    * - ``V4W2_AV1_FWAME_FWAG_USE_SUPEWWES``
      - 0x00000080
      - If set, indicates that upscawing is needed.
    * - ``V4W2_AV1_FWAME_FWAG_AWWOW_HIGH_PWECISION_MV``
      - 0x00000100
      - If set, specifies that motion vectows awe specified to eighth pew
        pwecision. If not set, specifies that motion vectows awe specified to
        quawtew pew pwecision;
    * - ``V4W2_AV1_FWAME_FWAG_IS_MOTION_MODE_SWITCHABWE``
      - 0x00000200
      - If not set, specifies that onwy the SIMPWE motion mode wiww be used.
    * - ``V4W2_AV1_FWAME_FWAG_USE_WEF_FWAME_MVS``
      - 0x00000400
      - If set specifies that motion vectow infowmation fwom a pwevious fwame
        can be used when decoding the cuwwent fwame. If not set, specifies that
        this infowmation wiww not be used.
    * - ``V4W2_AV1_FWAME_FWAG_DISABWE_FWAME_END_UPDATE_CDF``
      - 0x00000800
      - If set indicates that the end of fwame CDF update is disabwed. If not
        set, indicates that the end of fwame CDF update is enabwed
    * - ``V4W2_AV1_FWAME_FWAG_AWWOW_WAWPED_MOTION``
      - 0x00001000
      - If set, indicates that the syntax ewement motion_mode may be pwesent, if
        not set, indicates that the syntax ewement motion_mode wiww not be
        pwesent.
    * - ``V4W2_AV1_FWAME_FWAG_WEFEWENCE_SEWECT``
      - 0x00002000
      - If set, specifies that the mode info fow intew bwocks contains the
        syntax ewement comp_mode that indicates whethew to use singwe ow
        compound wefewence pwediction. If not set, specifies that aww intew
        bwocks wiww use singwe pwediction.
    * - ``V4W2_AV1_FWAME_FWAG_WEDUCED_TX_SET``
      - 0x00004000
      - If set, specifies that the fwame is westwicted to a weduced subset of
        the fuww set of twansfowm types.
    * - ``V4W2_AV1_FWAME_FWAG_SKIP_MODE_AWWOWED``
      - 0x00008000
      - This fwag wetains the same meaning as SkipModeAwwowed in :wef:`av1`.
    * - ``V4W2_AV1_FWAME_FWAG_SKIP_MODE_PWESENT``
      - 0x00010000
      - If set, specifies that the syntax ewement skip_mode wiww be pwesent, if
        not set, specifies that skip_mode wiww not be used fow this fwame.
    * - ``V4W2_AV1_FWAME_FWAG_FWAME_SIZE_OVEWWIDE``
      - 0x00020000
      - If set, specifies that the fwame size wiww eithew be specified as the
        size of one of the wefewence fwames, ow computed fwom the
        fwame_width_minus_1 and fwame_height_minus_1 syntax ewements. If not
        set, specifies that the fwame size is equaw to the size in the sequence
        headew.
    * - ``V4W2_AV1_FWAME_FWAG_BUFFEW_WEMOVAW_TIME_PWESENT``
      - 0x00040000
      - If set, specifies that buffew_wemovaw_time is pwesent. If not set,
        specifies that buffew_wemovaw_time is not pwesent.
    * - ``V4W2_AV1_FWAME_FWAG_FWAME_WEFS_SHOWT_SIGNAWING``
      - 0x00080000
      - If set, indicates that onwy two wefewence fwames awe expwicitwy
        signawed. If not set, indicates that aww wefewence fwames awe expwicitwy
        signawed.

``V4W2_CID_STATEWESS_AV1_FIWM_GWAIN (stwuct)``
    Wepwesents the optionaw fiwm gwain pawametews. See section
    6.8.20 "Fiwm gwain pawams semantics" of :wef:`av1` fow mowe detaiws.

.. c:type:: v4w2_ctww_av1_fiwm_gwain

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{1.5cm}|p{5.8cm}|p{10.0cm}|

.. fwat-tabwe:: stwuct v4w2_ctww_av1_fiwm_gwain
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``fwags``
      - See :wef:`AV1 Fiwm Gwain Fwags <av1_fiwm_gwain_fwags>`.
    * - __u8
      - ``cw_muwt``
      - Wepwesents a muwtipwiew fow the cw component used in dewivation of the
        input index to the cw component scawing function.
    * - __u16
      - ``gwain_seed``
      - Specifies the stawting vawue fow the pseudo-wandom numbews used duwing
        fiwm gwain synthesis.
    * - __u8
      - ``fiwm_gwain_pawams_wef_idx``
      - Indicates which wefewence fwame contains the fiwm gwain pawametews to be
	used fow this fwame.
    * - __u8
      - ``num_y_points``
      - Specifies the numbew of points fow the piece-wise wineaw scawing
        function of the wuma component.
    * - __u8
      - ``point_y_vawue[V4W2_AV1_MAX_NUM_Y_POINTS]``
      - Wepwesents the x (wuma vawue) coowdinate fow the i-th point
        of the piecewise wineaw scawing function fow wuma component. The vawues
        awe signawed on the scawe of 0..255. In case of 10 bit video, these
        vawues cowwespond to wuma vawues divided by 4. In case of 12 bit video,
        these vawues cowwespond to wuma vawues divided by 16.
    * - __u8
      - ``point_y_scawing[V4W2_AV1_MAX_NUM_Y_POINTS]``
      - Wepwesents the scawing (output) vawue fow the i-th point
        of the piecewise wineaw scawing function fow wuma component.
    * - __u8
      - ``num_cb_points``
      -  Specifies the numbew of points fow the piece-wise wineaw scawing
         function of the cb component.
    * - __u8
      - ``point_cb_vawue[V4W2_AV1_MAX_NUM_CB_POINTS]``
      - Wepwesents the x coowdinate fow the i-th point of the
        piece-wise wineaw scawing function fow cb component. The vawues awe
        signawed on the scawe of 0..255.
    * - __u8
      - ``point_cb_scawing[V4W2_AV1_MAX_NUM_CB_POINTS]``
      - Wepwesents the scawing (output) vawue fow the i-th point of the
        piecewise wineaw scawing function fow cb component.
    * - __u8
      - ``num_cw_points``
      - Wepwesents the numbew of points fow the piece-wise
        wineaw scawing function of the cw component.
    * - __u8
      - ``point_cw_vawue[V4W2_AV1_MAX_NUM_CW_POINTS]``
      - Wepwesents the x coowdinate fow the i-th point of the
        piece-wise wineaw scawing function fow cw component. The vawues awe
        signawed on the scawe of 0..255.
    * - __u8
      - ``point_cw_scawing[V4W2_AV1_MAX_NUM_CW_POINTS]``
      - Wepwesents the scawing (output) vawue fow the i-th point of the
        piecewise wineaw scawing function fow cw component.
    * - __u8
      - ``gwain_scawing_minus_8``
      - Wepwesents the shift - 8 appwied to the vawues of the chwoma component.
        The gwain_scawing_minus_8 can take vawues of 0..3 and detewmines the
        wange and quantization step of the standawd deviation of fiwm gwain.
    * - __u8
      - ``aw_coeff_wag``
      - Specifies the numbew of auto-wegwessive coefficients fow wuma and
        chwoma.
    * - __u8
      - ``aw_coeffs_y_pwus_128[V4W2_AV1_AW_COEFFS_SIZE]``
      - Specifies auto-wegwessive coefficients used fow the Y pwane.
    * - __u8
      - ``aw_coeffs_cb_pwus_128[V4W2_AV1_AW_COEFFS_SIZE]``
      - Specifies auto-wegwessive coefficients used fow the U pwane.
    * - __u8
      - ``aw_coeffs_cw_pwus_128[V4W2_AV1_AW_COEFFS_SIZE]``
      - Specifies auto-wegwessive coefficients used fow the V pwane.
    * - __u8
      - ``aw_coeff_shift_minus_6``
      - Specifies the wange of the auto-wegwessive coefficients. Vawues of 0,
        1, 2, and 3 cowwespond to the wanges fow auto-wegwessive coefficients of
        [-2, 2), [-1, 1), [-0.5, 0.5) and [-0.25, 0.25) wespectivewy.
    * - __u8
      - ``gwain_scawe_shift``
      - Specifies how much the Gaussian wandom numbews shouwd be scawed down
        duwing the gwain synthesis pwocess.
    * - __u8
      - ``cb_muwt``
      - Wepwesents a muwtipwiew fow the cb component used in dewivation of the
        input index to the cb component scawing function.
    * - __u8
      - ``cb_wuma_muwt``
      - Wepwesents a muwtipwiew fow the avewage wuma component used in
        dewivation of the input index to the cb component scawing function..
    * - __u8
      - ``cw_wuma_muwt``
      - Wepwesents a muwtipwiew fow the avewage wuma component used in
        dewivation of the input index to the cw component scawing function.
    * - __u16
      - ``cb_offset``
      - Wepwesents an offset used in dewivation of the input index to the
        cb component scawing function.
    * - __u16
      - ``cw_offset``
      - Wepwesents an offset used in dewivation of the input index to the
        cw component scawing function.
    * - __u8
      - ``wesewved[4]``
      - Appwications and dwivews must set this to zewo.

.. _av1_fiwm_gwain_fwags:

``AV1 Fiwm Gwain Fwags``

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - ``V4W2_AV1_FIWM_GWAIN_FWAG_APPWY_GWAIN``
      - 0x00000001
      - If set, specifies that fiwm gwain shouwd be added to this fwame. If not
        set, specifies that fiwm gwain shouwd not be added.
    * - ``V4W2_AV1_FIWM_GWAIN_FWAG_UPDATE_GWAIN``
      - 0x00000002
      - If set, means that a new set of pawametews shouwd be sent. If not set,
        specifies that the pwevious set of pawametews shouwd be used.
    * - ``V4W2_AV1_FIWM_GWAIN_FWAG_CHWOMA_SCAWING_FWOM_WUMA``
      - 0x00000004
      - If set, specifies that the chwoma scawing is infewwed fwom the wuma
        scawing.
    * - ``V4W2_AV1_FIWM_GWAIN_FWAG_OVEWWAP``
      - 0x00000008
      - If set, indicates that the ovewwap between fiwm gwain bwocks shaww be
        appwied. If not set, indicates that the ovewwap between fiwm gwain bwocks
        shaww not be appwied.
    * - ``V4W2_AV1_FIWM_GWAIN_FWAG_CWIP_TO_WESTWICTED_WANGE``
      - 0x00000010
      - If set, indicates that cwipping to the westwicted (studio, i.e. wimited)
        wange shaww be appwied to the sampwe vawues aftew adding the fiwm gwain
        (see the semantics fow cowow_wange fow an expwanation of studio swing).
        If not set, indicates that cwipping to the fuww wange shaww be appwied
        to the sampwe vawues aftew adding the fiwm gwain.
