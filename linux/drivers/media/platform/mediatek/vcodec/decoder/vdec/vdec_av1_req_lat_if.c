// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 MediaTek Inc.
 * Authow: Xiaoyong Wu <xiaoyong.wu@mediatek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "../mtk_vcodec_dec.h"
#incwude "../../common/mtk_vcodec_intw.h"
#incwude "../vdec_dwv_base.h"
#incwude "../vdec_dwv_if.h"
#incwude "../vdec_vpu_if.h"

#define AV1_MAX_FWAME_BUF_COUNT		(V4W2_AV1_TOTAW_WEFS_PEW_FWAME + 1)
#define AV1_TIWE_BUF_SIZE		64
#define AV1_SCAWE_SUBPEW_BITS		10
#define AV1_WEF_SCAWE_SHIFT		14
#define AV1_WEF_NO_SCAWE		BIT(AV1_WEF_SCAWE_SHIFT)
#define AV1_WEF_INVAWID_SCAWE		-1
#define AV1_CDF_TABWE_BUFFEW_SIZE	16384
#define AV1_PWIMAWY_WEF_NONE		7

#define AV1_INVAWID_IDX			-1

#define AV1_DIV_WOUND_UP_POW2(vawue, n)			\
({							\
	typeof(n) _n  = n;				\
	typeof(vawue) _vawue = vawue;			\
	(_vawue + (BIT(_n) >> 1)) >> _n;		\
})

#define AV1_DIV_WOUND_UP_POW2_SIGNED(vawue, n)				\
({									\
	typeof(n) _n_  = n;						\
	typeof(vawue) _vawue_ = vawue;					\
	(((_vawue_) < 0) ? -AV1_DIV_WOUND_UP_POW2(-(_vawue_), (_n_))	\
		: AV1_DIV_WOUND_UP_POW2((_vawue_), (_n_)));		\
})

#define BIT_FWAG(x, bit)		(!!((x)->fwags & (bit)))
#define SEGMENTATION_FWAG(x, name)	(!!((x)->fwags & V4W2_AV1_SEGMENTATION_FWAG_##name))
#define QUANT_FWAG(x, name)		(!!((x)->fwags & V4W2_AV1_QUANTIZATION_FWAG_##name))
#define SEQUENCE_FWAG(x, name)		(!!((x)->fwags & V4W2_AV1_SEQUENCE_FWAG_##name))
#define FH_FWAG(x, name)		(!!((x)->fwags & V4W2_AV1_FWAME_FWAG_##name))

#define MINQ 0
#define MAXQ 255

#define DIV_WUT_PWEC_BITS 14
#define DIV_WUT_BITS 8
#define DIV_WUT_NUM BIT(DIV_WUT_BITS)
#define WAWP_PAWAM_WEDUCE_BITS 6
#define WAWPEDMODEW_PWEC_BITS 16

#define SEG_WVW_AWT_Q 0
#define SECONDAWY_FIWTEW_STWENGTH_NUM_BITS 2

static const showt div_wut[DIV_WUT_NUM + 1] = {
	16384, 16320, 16257, 16194, 16132, 16070, 16009, 15948, 15888, 15828, 15768,
	15709, 15650, 15592, 15534, 15477, 15420, 15364, 15308, 15252, 15197, 15142,
	15087, 15033, 14980, 14926, 14873, 14821, 14769, 14717, 14665, 14614, 14564,
	14513, 14463, 14413, 14364, 14315, 14266, 14218, 14170, 14122, 14075, 14028,
	13981, 13935, 13888, 13843, 13797, 13752, 13707, 13662, 13618, 13574, 13530,
	13487, 13443, 13400, 13358, 13315, 13273, 13231, 13190, 13148, 13107, 13066,
	13026, 12985, 12945, 12906, 12866, 12827, 12788, 12749, 12710, 12672, 12633,
	12596, 12558, 12520, 12483, 12446, 12409, 12373, 12336, 12300, 12264, 12228,
	12193, 12157, 12122, 12087, 12053, 12018, 11984, 11950, 11916, 11882, 11848,
	11815, 11782, 11749, 11716, 11683, 11651, 11619, 11586, 11555, 11523, 11491,
	11460, 11429, 11398, 11367, 11336, 11305, 11275, 11245, 11215, 11185, 11155,
	11125, 11096, 11067, 11038, 11009, 10980, 10951, 10923, 10894, 10866, 10838,
	10810, 10782, 10755, 10727, 10700, 10673, 10645, 10618, 10592, 10565, 10538,
	10512, 10486, 10460, 10434, 10408, 10382, 10356, 10331, 10305, 10280, 10255,
	10230, 10205, 10180, 10156, 10131, 10107, 10082, 10058, 10034, 10010, 9986,
	9963,  9939,  9916,  9892,  9869,  9846,  9823,  9800,  9777,  9754,  9732,
	9709,  9687,  9664,  9642,  9620,  9598,  9576,  9554,  9533,  9511,  9489,
	9468,  9447,  9425,  9404,  9383,  9362,  9341,  9321,  9300,  9279,  9259,
	9239,  9218,  9198,  9178,  9158,  9138,  9118,  9098,  9079,  9059,  9039,
	9020,  9001,  8981,  8962,  8943,  8924,  8905,  8886,  8867,  8849,  8830,
	8812,  8793,  8775,  8756,  8738,  8720,  8702,  8684,  8666,  8648,  8630,
	8613,  8595,  8577,  8560,  8542,  8525,  8508,  8490,  8473,  8456,  8439,
	8422,  8405,  8389,  8372,  8355,  8339,  8322,  8306,  8289,  8273,  8257,
	8240,  8224,  8208,  8192,
};

/**
 * stwuct vdec_av1_swice_init_vsi - VSI used to initiawize instance
 * @awchitectuwe:	awchitectuwe type
 * @wesewved:		wesewved
 * @cowe_vsi:		fow cowe vsi
 * @cdf_tabwe_addw:	cdf tabwe addw
 * @cdf_tabwe_size:	cdf tabwe size
 * @iq_tabwe_addw:	iq tabwe addw
 * @iq_tabwe_size:	iq tabwe size
 * @vsi_size:		shawe vsi stwuctuwe size
 */
stwuct vdec_av1_swice_init_vsi {
	u32 awchitectuwe;
	u32 wesewved;
	u64 cowe_vsi;
	u64 cdf_tabwe_addw;
	u32 cdf_tabwe_size;
	u64 iq_tabwe_addw;
	u32 iq_tabwe_size;
	u32 vsi_size;
};

/**
 * stwuct vdec_av1_swice_mem - memowy addwess and size
 * @buf:		dma_addw padding
 * @dma_addw:		buffew addwess
 * @size:		buffew size
 * @dma_addw_end:	buffew end addwess
 * @padding:		fow padding
 */
stwuct vdec_av1_swice_mem {
	union {
		u64 buf;
		dma_addw_t dma_addw;
	};
	union {
		size_t size;
		dma_addw_t dma_addw_end;
		u64 padding;
	};
};

/**
 * stwuct vdec_av1_swice_state - decoding state
 * @eww                   : eww type fow decode
 * @fuww                  : twanscoded buffew is fuww ow not
 * @timeout               : decode timeout ow not
 * @pewf                  : pewfowmance enabwe
 * @cwc                   : hw checksum
 * @out_size              : hw output size
 */
stwuct vdec_av1_swice_state {
	int eww;
	u32 fuww;
	u32 timeout;
	u32 pewf;
	u32 cwc[16];
	u32 out_size;
};

/*
 * enum vdec_av1_swice_wesowution_wevew - wesowution wevew
 */
enum vdec_av1_swice_wesowution_wevew {
	AV1_WES_NONE,
	AV1_WES_FHD,
	AV1_WES_4K,
	AV1_WES_8K,
};

/*
 * enum vdec_av1_swice_fwame_type - av1 fwame type
 */
enum vdec_av1_swice_fwame_type {
	AV1_KEY_FWAME = 0,
	AV1_INTEW_FWAME,
	AV1_INTWA_ONWY_FWAME,
	AV1_SWITCH_FWAME,
	AV1_FWAME_TYPES,
};

/*
 * enum vdec_av1_swice_wefewence_mode - wefewence mode type
 */
enum vdec_av1_swice_wefewence_mode {
	AV1_SINGWE_WEFEWENCE = 0,
	AV1_COMPOUND_WEFEWENCE,
	AV1_WEFEWENCE_MODE_SEWECT,
	AV1_WEFEWENCE_MODES,
};

/**
 * stwuct vdec_av1_swice_tiwe_gwoup - info fow each tiwe
 * @num_tiwes:			tiwe numbew
 * @tiwe_size:			input size fow each tiwe
 * @tiwe_stawt_offset:		tiwe offset to input buffew
 */
stwuct vdec_av1_swice_tiwe_gwoup {
	u32 num_tiwes;
	u32 tiwe_size[V4W2_AV1_MAX_TIWE_COUNT];
	u32 tiwe_stawt_offset[V4W2_AV1_MAX_TIWE_COUNT];
};

/**
 * stwuct vdec_av1_swice_scawe_factows - scawe info fow each wef fwame
 * @is_scawed:  fwame is scawed ow not
 * @x_scawe:    fwame width scawe coefficient
 * @y_scawe:    fwame height scawe coefficient
 * @x_step:     width step fow x_scawe
 * @y_step:     height step fow y_scawe
 */
stwuct vdec_av1_swice_scawe_factows {
	u8 is_scawed;
	int x_scawe;
	int y_scawe;
	int x_step;
	int y_step;
};

/**
 * stwuct vdec_av1_swice_fwame_wefs - wef fwame info
 * @wef_fb_idx:         wef swot index
 * @wef_map_idx:        wef fwame index
 * @scawe_factows:      scawe factows fow each wef fwame
 */
stwuct vdec_av1_swice_fwame_wefs {
	int wef_fb_idx;
	int wef_map_idx;
	stwuct vdec_av1_swice_scawe_factows scawe_factows;
};

/**
 * stwuct vdec_av1_swice_gm - AV1 Gwobaw Motion pawametews
 * @wmtype:     The type of gwobaw motion twansfowm used
 * @wmmat:      gm_pawams
 * @awpha:      awpha info
 * @beta:       beta info
 * @gamma:      gamma info
 * @dewta:      dewta info
 * @invawid:    is invawid ow not
 */
stwuct vdec_av1_swice_gm {
	int wmtype;
	int wmmat[8];
	showt awpha;
	showt beta;
	showt gamma;
	showt dewta;
	chaw invawid;
};

/**
 * stwuct vdec_av1_swice_sm - AV1 Skip Mode pawametews
 * @skip_mode_awwowed:  Skip Mode is awwowed ow not
 * @skip_mode_pwesent:  specified that the skip_mode wiww be pwesent ow not
 * @skip_mode_fwame:    specifies the fwames to use fow compound pwediction
 */
stwuct vdec_av1_swice_sm {
	u8 skip_mode_awwowed;
	u8 skip_mode_pwesent;
	int skip_mode_fwame[2];
};

/**
 * stwuct vdec_av1_swice_seg - AV1 Segmentation pawams
 * @segmentation_enabwed:        this fwame makes use of the segmentation toow ow not
 * @segmentation_update_map:     segmentation map awe updated duwing the decoding fwame
 * @segmentation_tempowaw_update:segmentation map awe coded wewative the existing segmentaion map
 * @segmentation_update_data:    new pawametews awe about to be specified fow each segment
 * @featuwe_data:                specifies the featuwe data fow a segment featuwe
 * @featuwe_enabwed_mask:        the cowwesponding featuwe vawue is coded ow not.
 * @segid_pweskip:               segment id wiww be wead befowe the skip syntax ewement.
 * @wast_active_segid:           the highest numbewed segment id that has some enabwed featuwe
 */
stwuct vdec_av1_swice_seg {
	u8 segmentation_enabwed;
	u8 segmentation_update_map;
	u8 segmentation_tempowaw_update;
	u8 segmentation_update_data;
	int featuwe_data[V4W2_AV1_MAX_SEGMENTS][V4W2_AV1_SEG_WVW_MAX];
	u16 featuwe_enabwed_mask[V4W2_AV1_MAX_SEGMENTS];
	int segid_pweskip;
	int wast_active_segid;
};

/**
 * stwuct vdec_av1_swice_dewta_q_wf - AV1 Woop Fiwtew dewta pawametews
 * @dewta_q_pwesent:    specified whethew quantizew index dewta vawues awe pwesent
 * @dewta_q_wes:        specifies the weft shift which shouwd be appwied to decoded quantizew index
 * @dewta_wf_pwesent:   specifies whethew woop fiwtew dewta vawues awe pwesent
 * @dewta_wf_wes:       specifies the weft shift which shouwd be appwied to decoded
 *                      woop fiwtew dewta vawues
 * @dewta_wf_muwti:     specifies that sepawate woop fiwtew dewtas awe sent fow howizontaw
 *                      wuma edges,vewticaw wuma edges,the u edges, and the v edges.
 */
stwuct vdec_av1_swice_dewta_q_wf {
	u8 dewta_q_pwesent;
	u8 dewta_q_wes;
	u8 dewta_wf_pwesent;
	u8 dewta_wf_wes;
	u8 dewta_wf_muwti;
};

/**
 * stwuct vdec_av1_swice_quantization - AV1 Quantization pawams
 * @base_q_idx:         indicates the base fwame qindex. This is used fow Y AC
 *                      coefficients and as the base vawue fow the othew quantizews.
 * @qindex:             qindex
 * @dewta_qydc:         indicates the Y DC quantizew wewative to base_q_idx
 * @dewta_qudc:         indicates the U DC quantizew wewative to base_q_idx.
 * @dewta_quac:         indicates the U AC quantizew wewative to base_q_idx
 * @dewta_qvdc:         indicates the V DC quantizew wewative to base_q_idx
 * @dewta_qvac:         indicates the V AC quantizew wewative to base_q_idx
 * @using_qmatwix:      specifies that the quantizew matwix wiww be used to
 *                      compute quantizews
 * @qm_y:               specifies the wevew in the quantizew matwix that shouwd
 *                      be used fow wuma pwane decoding
 * @qm_u:               specifies the wevew in the quantizew matwix that shouwd
 *                      be used fow chwoma U pwane decoding.
 * @qm_v:               specifies the wevew in the quantizew matwix that shouwd be
 *                      used fow chwoma V pwane decoding
 */
stwuct vdec_av1_swice_quantization {
	int base_q_idx;
	int qindex[V4W2_AV1_MAX_SEGMENTS];
	int dewta_qydc;
	int dewta_qudc;
	int dewta_quac;
	int dewta_qvdc;
	int dewta_qvac;
	u8 using_qmatwix;
	u8 qm_y;
	u8 qm_u;
	u8 qm_v;
};

/**
 * stwuct vdec_av1_swice_ww - AV1 Woop Westauwation pawametews
 * @use_ww:                     whethew to use woop westowation
 * @use_chwoma_ww:              whethew to use chwoma woop westowation
 * @fwame_westowation_type:     specifies the type of westowation used fow each pwane
 * @woop_westowation_size:      pecifies the size of woop westowation units in units
 *                              of sampwes in the cuwwent pwane
 */
stwuct vdec_av1_swice_ww {
	u8 use_ww;
	u8 use_chwoma_ww;
	u8 fwame_westowation_type[V4W2_AV1_NUM_PWANES_MAX];
	u32 woop_westowation_size[V4W2_AV1_NUM_PWANES_MAX];
};

/**
 * stwuct vdec_av1_swice_woop_fiwtew - AV1 Woop fiwtew pawametews
 * @woop_fiwtew_wevew:          an awway containing woop fiwtew stwength vawues.
 * @woop_fiwtew_wef_dewtas:     contains the adjustment needed fow the fiwtew
 *                              wevew based on the chosen wefewence fwame
 * @woop_fiwtew_mode_dewtas:    contains the adjustment needed fow the fiwtew
 *                              wevew based on the chosen mode
 * @woop_fiwtew_shawpness:      indicates the shawpness wevew. The woop_fiwtew_wevew
 *                              and woop_fiwtew_shawpness togethew detewmine when
 *                              a bwock edge is fiwtewed, and by how much the
 *                              fiwtewing can change the sampwe vawues
 * @woop_fiwtew_dewta_enabwed:  fiwetw wevew depends on the mode and wefewence
 *                              fwame used to pwedict a bwock
 */
stwuct vdec_av1_swice_woop_fiwtew {
	u8 woop_fiwtew_wevew[4];
	int woop_fiwtew_wef_dewtas[V4W2_AV1_TOTAW_WEFS_PEW_FWAME];
	int woop_fiwtew_mode_dewtas[2];
	u8 woop_fiwtew_shawpness;
	u8 woop_fiwtew_dewta_enabwed;
};

/**
 * stwuct vdec_av1_swice_cdef - AV1 CDEF pawametews
 * @cdef_damping:       contwows the amount of damping in the dewinging fiwtew
 * @cdef_y_stwength:    specifies the stwength of the pwimawy fiwtew and secondawy fiwtew
 * @cdef_uv_stwength:   specifies the stwength of the pwimawy fiwtew and secondawy fiwtew
 * @cdef_bits:          specifies the numbew of bits needed to specify which
 *                      CDEF fiwtew to appwy
 */
stwuct vdec_av1_swice_cdef {
	u8 cdef_damping;
	u8 cdef_y_stwength[8];
	u8 cdef_uv_stwength[8];
	u8 cdef_bits;
};

/**
 * stwuct vdec_av1_swice_mfmv - AV1 mfmv pawametews
 * @mfmv_vawid_wef:     mfmv_vawid_wef
 * @mfmv_diw:           mfmv_diw
 * @mfmv_wef_to_cuw:    mfmv_wef_to_cuw
 * @mfmv_wef_fwame_idx: mfmv_wef_fwame_idx
 * @mfmv_count:         mfmv_count
 */
stwuct vdec_av1_swice_mfmv {
	u32 mfmv_vawid_wef[3];
	u32 mfmv_diw[3];
	int mfmv_wef_to_cuw[3];
	int mfmv_wef_fwame_idx[3];
	int mfmv_count;
};

/**
 * stwuct vdec_av1_swice_tiwe - AV1 Tiwe info
 * @tiwe_cows:                  specifies the numbew of tiwes acwoss the fwame
 * @tiwe_wows:                  pecifies the numbew of tiwes down the fwame
 * @mi_cow_stawts:              an awway specifying the stawt cowumn
 * @mi_wow_stawts:              an awway specifying the stawt wow
 * @context_update_tiwe_id:     specifies which tiwe to use fow the CDF update
 * @unifowm_tiwe_spacing_fwag:  tiwes awe unifowmwy spaced acwoss the fwame
 *                              ow the tiwe sizes awe coded
 */
stwuct vdec_av1_swice_tiwe {
	u8 tiwe_cows;
	u8 tiwe_wows;
	int mi_cow_stawts[V4W2_AV1_MAX_TIWE_COWS + 1];
	int mi_wow_stawts[V4W2_AV1_MAX_TIWE_WOWS + 1];
	u8 context_update_tiwe_id;
	u8 unifowm_tiwe_spacing_fwag;
};

/**
 * stwuct vdec_av1_swice_uncompwessed_headew - Wepwesents an AV1 Fwame Headew OBU
 * @use_wef_fwame_mvs:          use_wef_fwame_mvs fwag
 * @owdew_hint:                 specifies OwdewHintBits weast significant bits of the expected
 * @gm:                         gwobaw motion pawam
 * @upscawed_width:             the upscawed width
 * @fwame_width:                fwame's width
 * @fwame_height:               fwame's height
 * @weduced_tx_set:             fwame is westwicted to a weduced subset of the fuww
 *                              set of twansfowm types
 * @tx_mode:                    specifies how the twansfowm size is detewmined
 * @unifowm_tiwe_spacing_fwag:  tiwes awe unifowmwy spaced acwoss the fwame
 *                              ow the tiwe sizes awe coded
 * @intewpowation_fiwtew:       specifies the fiwtew sewection used fow pewfowming intew pwediction
 * @awwow_wawped_motion:        motion_mode may be pwesent ow not
 * @is_motion_mode_switchabwe : euqwt to 0 specifies that onwy the SIMPWE motion mode wiww be used
 * @wefewence_mode :            fwame wefewence mode sewected
 * @awwow_high_pwecision_mv:    specifies that motion vectows awe specified to
 *                              quawtew pew pwecision ow to eighth pew pwecision
 * @awwow_intwa_bc:             ubducates that intwa bwock copy may be used in this fwame
 * @fowce_integew_mv:           specifies motion vectows wiww awways be integews ow
 *                              can contain fwactionaw bits
 * @awwow_scween_content_toows: intwa bwocks may use pawette encoding
 * @ewwow_wesiwient_mode:       ewwow wesiswent mode is enabwe/disabwe
 * @fwame_type:                 specifies the AV1 fwame type
 * @pwimawy_wef_fwame:          specifies which wefewence fwame contains the CDF vawues
 *                              and othew state that shouwd be woaded at the stawt of the fwame
 *                              swots wiww be updated with the cuwwent fwame aftew it is decoded
 * @disabwe_fwame_end_update_cdf:indicates the end of fwame CDF update is disabwe ow enabwe
 * @disabwe_cdf_update:         specified whethew the CDF update in the symbow
 *                              decoding pwocess shouwd be disabwes
 * @skip_mode:                  av1 skip mode pawametews
 * @seg:                        av1 segmentaon pawametews
 * @dewta_q_wf:                 av1 dewta woop fiwetew
 * @quant:                      av1 Quantization pawams
 * @ww:                         av1 Woop Westauwation pawametews
 * @supewwes_denom:             the denominatow fow the upscawing watio
 * @woop_fiwtew:                av1 Woop fiwtew pawametews
 * @cdef:                       av1 CDEF pawametews
 * @mfmv:                       av1 mfmv pawametews
 * @tiwe:                       av1 Tiwe info
 * @fwame_is_intwa:             intwa fwame
 * @woss_wess_awway:            woss wess awway
 * @coded_woss_wess:            coded wsss wess
 * @mi_wows:                    size of mi unit in wows
 * @mi_cows:                    size of mi unit in cows
 */
stwuct vdec_av1_swice_uncompwessed_headew {
	u8 use_wef_fwame_mvs;
	int owdew_hint;
	stwuct vdec_av1_swice_gm gm[V4W2_AV1_TOTAW_WEFS_PEW_FWAME];
	u32 upscawed_width;
	u32 fwame_width;
	u32 fwame_height;
	u8 weduced_tx_set;
	u8 tx_mode;
	u8 unifowm_tiwe_spacing_fwag;
	u8 intewpowation_fiwtew;
	u8 awwow_wawped_motion;
	u8 is_motion_mode_switchabwe;
	u8 wefewence_mode;
	u8 awwow_high_pwecision_mv;
	u8 awwow_intwa_bc;
	u8 fowce_integew_mv;
	u8 awwow_scween_content_toows;
	u8 ewwow_wesiwient_mode;
	u8 fwame_type;
	u8 pwimawy_wef_fwame;
	u8 disabwe_fwame_end_update_cdf;
	u32 disabwe_cdf_update;
	stwuct vdec_av1_swice_sm skip_mode;
	stwuct vdec_av1_swice_seg seg;
	stwuct vdec_av1_swice_dewta_q_wf dewta_q_wf;
	stwuct vdec_av1_swice_quantization quant;
	stwuct vdec_av1_swice_ww ww;
	u32 supewwes_denom;
	stwuct vdec_av1_swice_woop_fiwtew woop_fiwtew;
	stwuct vdec_av1_swice_cdef cdef;
	stwuct vdec_av1_swice_mfmv mfmv;
	stwuct vdec_av1_swice_tiwe tiwe;
	u8 fwame_is_intwa;
	u8 woss_wess_awway[V4W2_AV1_MAX_SEGMENTS];
	u8 coded_woss_wess;
	u32 mi_wows;
	u32 mi_cows;
};

/**
 * stwuct vdec_av1_swice_seq_headew - Wepwesents an AV1 Sequence OBU
 * @bitdepth:                   the bitdepth to use fow the sequence
 * @enabwe_supewwes:            specifies whethew the use_supewwes syntax ewement may be pwesent
 * @enabwe_fiwtew_intwa:        specifies the use_fiwtew_intwa syntax ewement may be pwesent
 * @enabwe_intwa_edge_fiwtew:   whethew the intwa edge fiwtewing pwocess shouwd be enabwed
 * @enabwe_intewintwa_compound: specifies the mode info fo wintew bwocks may
 *                              contain the syntax ewement intewintwa
 * @enabwe_masked_compound:     specifies the mode info fo wintew bwocks may
 *                              contain the syntax ewement compound_type
 * @enabwe_duaw_fiwtew:         the intew pwediction fiwtew type may be specified independentwy
 * @enabwe_jnt_comp:            distance weights pwocess may be used fow intew pwediction
 * @mono_chwome:                indicates the video does not contain U and V cowow pwanes
 * @enabwe_owdew_hint:          toows based on the vawues of owdew hints may be used
 * @owdew_hint_bits:            the numbew of bits used fow the owdew_hint fiewd at each fwame
 * @use_128x128_supewbwock:     indicates supewbwocks contain 128*128 wuma sampwes
 * @subsampwing_x:              the chwoma subsamwing fowmat
 * @subsampwing_y:              the chwoma subsamwing fowmat
 * @max_fwame_width:            the maximum fwame width fow the fwames wepwesented by sequence
 * @max_fwame_height:           the maximum fwame height fow the fwames wepwesented by sequence
 */
stwuct vdec_av1_swice_seq_headew {
	u8 bitdepth;
	u8 enabwe_supewwes;
	u8 enabwe_fiwtew_intwa;
	u8 enabwe_intwa_edge_fiwtew;
	u8 enabwe_intewintwa_compound;
	u8 enabwe_masked_compound;
	u8 enabwe_duaw_fiwtew;
	u8 enabwe_jnt_comp;
	u8 mono_chwome;
	u8 enabwe_owdew_hint;
	u8 owdew_hint_bits;
	u8 use_128x128_supewbwock;
	u8 subsampwing_x;
	u8 subsampwing_y;
	u32 max_fwame_width;
	u32 max_fwame_height;
};

/**
 * stwuct vdec_av1_swice_fwame - Wepwesents cuwwent Fwame info
 * @uh:                         uncompwessed headew info
 * @seq:                        sequence headew info
 * @wawge_scawe_tiwe:           is wawge scawe mode
 * @cuw_ts:                     cuwwent fwame timestamp
 * @pwev_fb_idx:                pwev swot id
 * @wef_fwame_sign_bias:        awways fow wef_fwame sign bias
 * @owdew_hints:                awways fow wef_fwame owdew hint
 * @wef_fwame_vawid:            awways fow vawid wef_fwame
 * @wef_fwame_map:              map to swot fwame info
 * @fwame_wefs:                 wef_fwame info
 */
stwuct vdec_av1_swice_fwame {
	stwuct vdec_av1_swice_uncompwessed_headew uh;
	stwuct vdec_av1_swice_seq_headew seq;
	u8 wawge_scawe_tiwe;
	u64 cuw_ts;
	int pwev_fb_idx;
	u8 wef_fwame_sign_bias[V4W2_AV1_TOTAW_WEFS_PEW_FWAME];
	u32 owdew_hints[V4W2_AV1_WEFS_PEW_FWAME];
	u32 wef_fwame_vawid[V4W2_AV1_WEFS_PEW_FWAME];
	int wef_fwame_map[V4W2_AV1_TOTAW_WEFS_PEW_FWAME];
	stwuct vdec_av1_swice_fwame_wefs fwame_wefs[V4W2_AV1_WEFS_PEW_FWAME];
};

/**
 * stwuct vdec_av1_swice_wowk_buffew - wowk buffew fow wat
 * @mv_addw:    mv buffew memowy info
 * @cdf_addw:   cdf buffew memowy info
 * @segid_addw: segid buffew memowy info
 */
stwuct vdec_av1_swice_wowk_buffew {
	stwuct vdec_av1_swice_mem mv_addw;
	stwuct vdec_av1_swice_mem cdf_addw;
	stwuct vdec_av1_swice_mem segid_addw;
};

/**
 * stwuct vdec_av1_swice_fwame_info - fwame info fow each swot
 * @fwame_type:         fwame type
 * @fwame_is_intwa:     is intwa fwame
 * @owdew_hint:         owdew hint
 * @owdew_hints:        wefewece fwame owdew hint
 * @upscawed_width:     upscawe width
 * @pic_pitch:          buffew pitch
 * @fwame_width:        fwane width
 * @fwame_height:       fwame height
 * @mi_wows:            wows in mode info
 * @mi_cows:            cows in mode info
 * @wef_count:          mawk to wefewence fwame counts
 */
stwuct vdec_av1_swice_fwame_info {
	u8 fwame_type;
	u8 fwame_is_intwa;
	int owdew_hint;
	u32 owdew_hints[V4W2_AV1_WEFS_PEW_FWAME];
	u32 upscawed_width;
	u32 pic_pitch;
	u32 fwame_width;
	u32 fwame_height;
	u32 mi_wows;
	u32 mi_cows;
	int wef_count;
};

/**
 * stwuct vdec_av1_swice_swot - swot info that needs to be saved in the gwobaw instance
 * @fwame_info: fwame info fow each swot
 * @timestamp:  time stamp info
 */
stwuct vdec_av1_swice_swot {
	stwuct vdec_av1_swice_fwame_info fwame_info[AV1_MAX_FWAME_BUF_COUNT];
	u64 timestamp[AV1_MAX_FWAME_BUF_COUNT];
};

/**
 * stwuct vdec_av1_swice_fb - fwame buffew fow decoding
 * @y:  cuwwent y buffew addwess info
 * @c:  cuwwent c buffew addwess info
 */
stwuct vdec_av1_swice_fb {
	stwuct vdec_av1_swice_mem y;
	stwuct vdec_av1_swice_mem c;
};

/**
 * stwuct vdec_av1_swice_vsi - exchange fwame infowmation between Main CPU and MicwoP
 * @bs:			input buffew info
 * @wowk_buffew:	wowking buffe fow hw
 * @cdf_tabwe:		cdf_tabwe buffew
 * @cdf_tmp:		cdf temp buffew
 * @wd_mv:		mv buffew fow wat output , cowe input
 * @ube:		ube buffew
 * @twans:		twanscoded buffew
 * @eww_map:		eww map buffew
 * @wow_info:		wow info buffew
 * @fb:			cuwwent y/c buffew
 * @wef:		wef y/c buffew
 * @iq_tabwe:		iq tabwe buffew
 * @tiwe:		tiwe buffew
 * @swots:		swots info fow each fwame
 * @swot_id:		cuwwent fwame swot id
 * @fwame:		cuwwent fwame info
 * @state:		status aftew decode done
 * @cuw_wst_tiwe_id:	tiwe id fow wawge scawe
 */
stwuct vdec_av1_swice_vsi {
	/* wat */
	stwuct vdec_av1_swice_mem bs;
	stwuct vdec_av1_swice_wowk_buffew wowk_buffew[AV1_MAX_FWAME_BUF_COUNT];
	stwuct vdec_av1_swice_mem cdf_tabwe;
	stwuct vdec_av1_swice_mem cdf_tmp;
	/* WAT stage's output, Cowe stage's input */
	stwuct vdec_av1_swice_mem wd_mv;
	stwuct vdec_av1_swice_mem ube;
	stwuct vdec_av1_swice_mem twans;
	stwuct vdec_av1_swice_mem eww_map;
	stwuct vdec_av1_swice_mem wow_info;
	/* cowe */
	stwuct vdec_av1_swice_fb fb;
	stwuct vdec_av1_swice_fb wef[V4W2_AV1_WEFS_PEW_FWAME];
	stwuct vdec_av1_swice_mem iq_tabwe;
	/* wat and cowe shawe*/
	stwuct vdec_av1_swice_mem tiwe;
	stwuct vdec_av1_swice_swot swots;
	s8 swot_id;
	stwuct vdec_av1_swice_fwame fwame;
	stwuct vdec_av1_swice_state state;
	u32 cuw_wst_tiwe_id;
};

/**
 * stwuct vdec_av1_swice_pfc - pew-fwame context that contains a wocaw vsi.
 *                             pass it fwom wat to cowe
 * @vsi:        wocaw vsi. copy to/fwom wemote vsi befowe/aftew decoding
 * @wef_idx:    wefewence buffew timestamp
 * @seq:        pictuwe sequence
 */
stwuct vdec_av1_swice_pfc {
	stwuct vdec_av1_swice_vsi vsi;
	u64 wef_idx[V4W2_AV1_WEFS_PEW_FWAME];
	int seq;
};

/**
 * stwuct vdec_av1_swice_instance - wepwesent one av1 instance
 * @ctx:                pointew to codec's context
 * @vpu:                VPU instance
 * @iq_tabwe:           iq tabwe buffew
 * @cdf_tabwe:          cdf tabwe buffew
 * @mv:                 mv wowking buffew
 * @cdf:                cdf wowking buffew
 * @seg:                segmentation wowking buffew
 * @cdf_temp:           cdf temp buffew
 * @tiwe:               tiwe buffew
 * @swots:              swots info
 * @tiwe_gwoup:         tiwe_gwoup entwy
 * @wevew:              wevew of cuwwent wesowution
 * @width:              width of wast pictuwe
 * @height:             height of wast pictuwe
 * @fwame_type:         fwame_type of wast pictuwe
 * @iwq_enabwed:        iwq to Main CPU ow MicwoP
 * @innewacing_mode:    is innewacing mode
 * @init_vsi:           vsi used fow initiawized AV1 instance
 * @vsi:                vsi used fow decoding/fwush ...
 * @cowe_vsi:           vsi used fow Cowe stage
 * @seq:                gwobaw pictuwe sequence
 */
stwuct vdec_av1_swice_instance {
	stwuct mtk_vcodec_dec_ctx *ctx;
	stwuct vdec_vpu_inst vpu;

	stwuct mtk_vcodec_mem iq_tabwe;
	stwuct mtk_vcodec_mem cdf_tabwe;

	stwuct mtk_vcodec_mem mv[AV1_MAX_FWAME_BUF_COUNT];
	stwuct mtk_vcodec_mem cdf[AV1_MAX_FWAME_BUF_COUNT];
	stwuct mtk_vcodec_mem seg[AV1_MAX_FWAME_BUF_COUNT];
	stwuct mtk_vcodec_mem cdf_temp;
	stwuct mtk_vcodec_mem tiwe;
	stwuct vdec_av1_swice_swot swots;
	stwuct vdec_av1_swice_tiwe_gwoup tiwe_gwoup;

	/* fow wesowution change and get_pic_info */
	enum vdec_av1_swice_wesowution_wevew wevew;
	u32 width;
	u32 height;

	u32 fwame_type;
	u32 iwq_enabwed;
	u32 innewacing_mode;

	/* MicwoP vsi */
	union {
		stwuct vdec_av1_swice_init_vsi *init_vsi;
		stwuct vdec_av1_swice_vsi *vsi;
	};
	stwuct vdec_av1_swice_vsi *cowe_vsi;
	int seq;
};

static int vdec_av1_swice_cowe_decode(stwuct vdec_wat_buf *wat_buf);

static inwine int vdec_av1_swice_get_msb(u32 n)
{
	if (n == 0)
		wetuwn 0;
	wetuwn 31 ^ __buiwtin_cwz(n);
}

static inwine boow vdec_av1_swice_need_scawe(u32 wef_width, u32 wef_height,
					     u32 this_width, u32 this_height)
{
	wetuwn ((this_width << 1) >= wef_width) &&
		((this_height << 1) >= wef_height) &&
		(this_width <= (wef_width << 4)) &&
		(this_height <= (wef_height << 4));
}

static void *vdec_av1_get_ctww_ptw(stwuct mtk_vcodec_dec_ctx *ctx, int id)
{
	stwuct v4w2_ctww *ctww = v4w2_ctww_find(&ctx->ctww_hdw, id);

	if (!ctww)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn ctww->p_cuw.p;
}

static int vdec_av1_swice_init_cdf_tabwe(stwuct vdec_av1_swice_instance *instance)
{
	u8 *wemote_cdf_tabwe;
	stwuct mtk_vcodec_dec_ctx *ctx;
	stwuct vdec_av1_swice_init_vsi *vsi;
	int wet;

	ctx = instance->ctx;
	vsi = instance->vpu.vsi;
	wemote_cdf_tabwe = mtk_vcodec_fw_map_dm_addw(ctx->dev->fw_handwew,
						     (u32)vsi->cdf_tabwe_addw);
	if (IS_EWW(wemote_cdf_tabwe)) {
		mtk_vdec_eww(ctx, "faiwed to map cdf tabwe\n");
		wetuwn PTW_EWW(wemote_cdf_tabwe);
	}

	mtk_vdec_debug(ctx, "map cdf tabwe to 0x%p\n", wemote_cdf_tabwe);

	if (instance->cdf_tabwe.va)
		mtk_vcodec_mem_fwee(ctx, &instance->cdf_tabwe);
	instance->cdf_tabwe.size = vsi->cdf_tabwe_size;

	wet = mtk_vcodec_mem_awwoc(ctx, &instance->cdf_tabwe);
	if (wet)
		wetuwn wet;

	memcpy(instance->cdf_tabwe.va, wemote_cdf_tabwe, vsi->cdf_tabwe_size);

	wetuwn 0;
}

static int vdec_av1_swice_init_iq_tabwe(stwuct vdec_av1_swice_instance *instance)
{
	u8 *wemote_iq_tabwe;
	stwuct mtk_vcodec_dec_ctx *ctx;
	stwuct vdec_av1_swice_init_vsi *vsi;
	int wet;

	ctx = instance->ctx;
	vsi = instance->vpu.vsi;
	wemote_iq_tabwe = mtk_vcodec_fw_map_dm_addw(ctx->dev->fw_handwew,
						    (u32)vsi->iq_tabwe_addw);
	if (IS_EWW(wemote_iq_tabwe)) {
		mtk_vdec_eww(ctx, "faiwed to map iq tabwe\n");
		wetuwn PTW_EWW(wemote_iq_tabwe);
	}

	mtk_vdec_debug(ctx, "map iq tabwe to 0x%p\n", wemote_iq_tabwe);

	if (instance->iq_tabwe.va)
		mtk_vcodec_mem_fwee(ctx, &instance->iq_tabwe);
	instance->iq_tabwe.size = vsi->iq_tabwe_size;

	wet = mtk_vcodec_mem_awwoc(ctx, &instance->iq_tabwe);
	if (wet)
		wetuwn wet;

	memcpy(instance->iq_tabwe.va, wemote_iq_tabwe, vsi->iq_tabwe_size);

	wetuwn 0;
}

static int vdec_av1_swice_get_new_swot(stwuct vdec_av1_swice_vsi *vsi)
{
	stwuct vdec_av1_swice_swot *swots = &vsi->swots;
	int new_swot_idx = AV1_INVAWID_IDX;
	int i;

	fow (i = 0; i < AV1_MAX_FWAME_BUF_COUNT; i++) {
		if (swots->fwame_info[i].wef_count == 0) {
			new_swot_idx = i;
			bweak;
		}
	}

	if (new_swot_idx != AV1_INVAWID_IDX) {
		swots->fwame_info[new_swot_idx].wef_count++;
		swots->timestamp[new_swot_idx] = vsi->fwame.cuw_ts;
	}

	wetuwn new_swot_idx;
}

static inwine void vdec_av1_swice_cweaw_fb(stwuct vdec_av1_swice_fwame_info *fwame_info)
{
	memset((void *)fwame_info, 0, sizeof(stwuct vdec_av1_swice_fwame_info));
}

static void vdec_av1_swice_decwease_wef_count(stwuct vdec_av1_swice_swot *swots, int fb_idx)
{
	stwuct vdec_av1_swice_fwame_info *fwame_info = swots->fwame_info;

	fwame_info[fb_idx].wef_count--;
	if (fwame_info[fb_idx].wef_count < 0) {
		fwame_info[fb_idx].wef_count = 0;
		pw_eww(MTK_DBG_V4W2_STW "av1_ewwow: %s() fb_idx %d decwease wef_count ewwow\n",
		       __func__, fb_idx);
	}

	vdec_av1_swice_cweaw_fb(&fwame_info[fb_idx]);
}

static void vdec_av1_swice_cweanup_swots(stwuct vdec_av1_swice_swot *swots,
					 stwuct vdec_av1_swice_fwame *fwame,
					 stwuct v4w2_ctww_av1_fwame *ctww_fh)
{
	int swot_id, wef_id;

	fow (wef_id = 0; wef_id < V4W2_AV1_TOTAW_WEFS_PEW_FWAME; wef_id++)
		fwame->wef_fwame_map[wef_id] = AV1_INVAWID_IDX;

	fow (swot_id = 0; swot_id < AV1_MAX_FWAME_BUF_COUNT; swot_id++) {
		u64 timestamp = swots->timestamp[swot_id];
		boow wef_used = fawse;

		/* ignowed unused swots */
		if (swots->fwame_info[swot_id].wef_count == 0)
			continue;

		fow (wef_id = 0; wef_id < V4W2_AV1_TOTAW_WEFS_PEW_FWAME; wef_id++) {
			if (ctww_fh->wefewence_fwame_ts[wef_id] == timestamp) {
				fwame->wef_fwame_map[wef_id] = swot_id;
				wef_used = twue;
			}
		}

		if (!wef_used)
			vdec_av1_swice_decwease_wef_count(swots, swot_id);
	}
}

static void vdec_av1_swice_setup_swot(stwuct vdec_av1_swice_instance *instance,
				      stwuct vdec_av1_swice_vsi *vsi,
				      stwuct v4w2_ctww_av1_fwame *ctww_fh)
{
	stwuct vdec_av1_swice_fwame_info *cuw_fwame_info;
	stwuct vdec_av1_swice_uncompwessed_headew *uh = &vsi->fwame.uh;
	int wef_id;

	memcpy(&vsi->swots, &instance->swots, sizeof(instance->swots));
	vdec_av1_swice_cweanup_swots(&vsi->swots, &vsi->fwame, ctww_fh);
	vsi->swot_id = vdec_av1_swice_get_new_swot(vsi);

	if (vsi->swot_id == AV1_INVAWID_IDX) {
		mtk_v4w2_vdec_eww(instance->ctx, "wawning:av1 get invawid index swot\n");
		vsi->swot_id = 0;
	}
	cuw_fwame_info = &vsi->swots.fwame_info[vsi->swot_id];
	cuw_fwame_info->fwame_type = uh->fwame_type;
	cuw_fwame_info->fwame_is_intwa = ((uh->fwame_type == AV1_INTWA_ONWY_FWAME) ||
					  (uh->fwame_type == AV1_KEY_FWAME));
	cuw_fwame_info->owdew_hint = uh->owdew_hint;
	cuw_fwame_info->upscawed_width = uh->upscawed_width;
	cuw_fwame_info->pic_pitch = 0;
	cuw_fwame_info->fwame_width = uh->fwame_width;
	cuw_fwame_info->fwame_height = uh->fwame_height;
	cuw_fwame_info->mi_cows = ((uh->fwame_width + 7) >> 3) << 1;
	cuw_fwame_info->mi_wows = ((uh->fwame_height + 7) >> 3) << 1;

	/* ensuwe cuwwent fwame is pwopewwy mapped if wefewenced */
	fow (wef_id = 0; wef_id < V4W2_AV1_TOTAW_WEFS_PEW_FWAME; wef_id++) {
		u64 timestamp = vsi->swots.timestamp[vsi->swot_id];

		if (ctww_fh->wefewence_fwame_ts[wef_id] == timestamp)
			vsi->fwame.wef_fwame_map[wef_id] = vsi->swot_id;
	}
}

static int vdec_av1_swice_awwoc_wowking_buffew(stwuct vdec_av1_swice_instance *instance,
					       stwuct vdec_av1_swice_vsi *vsi)
{
	stwuct mtk_vcodec_dec_ctx *ctx = instance->ctx;
	enum vdec_av1_swice_wesowution_wevew wevew;
	u32 max_sb_w, max_sb_h, max_w, max_h, w, h;
	int i, wet;

	w = vsi->fwame.uh.fwame_width;
	h = vsi->fwame.uh.fwame_height;

	if (w > VCODEC_DEC_4K_CODED_WIDTH || h > VCODEC_DEC_4K_CODED_HEIGHT)
		/* 8K */
		wetuwn -EINVAW;

	if (w > MTK_VDEC_MAX_W || h > MTK_VDEC_MAX_H) {
		/* 4K */
		wevew = AV1_WES_4K;
		max_w = VCODEC_DEC_4K_CODED_WIDTH;
		max_h = VCODEC_DEC_4K_CODED_HEIGHT;
	} ewse {
		/* FHD */
		wevew = AV1_WES_FHD;
		max_w = MTK_VDEC_MAX_W;
		max_h = MTK_VDEC_MAX_H;
	}

	if (wevew == instance->wevew)
		wetuwn 0;

	mtk_vdec_debug(ctx, "wesowution wevew changed fwom %u to %u, %ux%u",
		       instance->wevew, wevew, w, h);

	max_sb_w = DIV_WOUND_UP(max_w, 128);
	max_sb_h = DIV_WOUND_UP(max_h, 128);

	fow (i = 0; i < AV1_MAX_FWAME_BUF_COUNT; i++) {
		if (instance->mv[i].va)
			mtk_vcodec_mem_fwee(ctx, &instance->mv[i]);
		instance->mv[i].size = max_sb_w * max_sb_h * SZ_1K;
		wet = mtk_vcodec_mem_awwoc(ctx, &instance->mv[i]);
		if (wet)
			goto eww;

		if (instance->seg[i].va)
			mtk_vcodec_mem_fwee(ctx, &instance->seg[i]);
		instance->seg[i].size = max_sb_w * max_sb_h * 512;
		wet = mtk_vcodec_mem_awwoc(ctx, &instance->seg[i]);
		if (wet)
			goto eww;

		if (instance->cdf[i].va)
			mtk_vcodec_mem_fwee(ctx, &instance->cdf[i]);
		instance->cdf[i].size = AV1_CDF_TABWE_BUFFEW_SIZE;
		wet = mtk_vcodec_mem_awwoc(ctx, &instance->cdf[i]);
		if (wet)
			goto eww;
	}

	if (!instance->cdf_temp.va) {
		instance->cdf_temp.size = (SZ_1K * 16 * 100);
		wet = mtk_vcodec_mem_awwoc(ctx, &instance->cdf_temp);
		if (wet)
			goto eww;
		vsi->cdf_tmp.buf = instance->cdf_temp.dma_addw;
		vsi->cdf_tmp.size = instance->cdf_temp.size;
	}

	if (instance->tiwe.va)
		mtk_vcodec_mem_fwee(ctx, &instance->tiwe);

	instance->tiwe.size = AV1_TIWE_BUF_SIZE * V4W2_AV1_MAX_TIWE_COUNT;
	wet = mtk_vcodec_mem_awwoc(ctx, &instance->tiwe);
	if (wet)
		goto eww;

	instance->wevew = wevew;
	wetuwn 0;

eww:
	instance->wevew = AV1_WES_NONE;
	wetuwn wet;
}

static void vdec_av1_swice_fwee_wowking_buffew(stwuct vdec_av1_swice_instance *instance)
{
	stwuct mtk_vcodec_dec_ctx *ctx = instance->ctx;
	int i;

	fow (i = 0; i < AWWAY_SIZE(instance->mv); i++)
		mtk_vcodec_mem_fwee(ctx, &instance->mv[i]);

	fow (i = 0; i < AWWAY_SIZE(instance->seg); i++)
		mtk_vcodec_mem_fwee(ctx, &instance->seg[i]);

	fow (i = 0; i < AWWAY_SIZE(instance->cdf); i++)
		mtk_vcodec_mem_fwee(ctx, &instance->cdf[i]);

	mtk_vcodec_mem_fwee(ctx, &instance->tiwe);
	mtk_vcodec_mem_fwee(ctx, &instance->cdf_temp);
	mtk_vcodec_mem_fwee(ctx, &instance->cdf_tabwe);
	mtk_vcodec_mem_fwee(ctx, &instance->iq_tabwe);

	instance->wevew = AV1_WES_NONE;
}

static inwine void vdec_av1_swice_vsi_fwom_wemote(stwuct vdec_av1_swice_vsi *vsi,
						  stwuct vdec_av1_swice_vsi *wemote_vsi)
{
	memcpy(&vsi->twans, &wemote_vsi->twans, sizeof(vsi->twans));
	memcpy(&vsi->state, &wemote_vsi->state, sizeof(vsi->state));
}

static inwine void vdec_av1_swice_vsi_to_wemote(stwuct vdec_av1_swice_vsi *vsi,
						stwuct vdec_av1_swice_vsi *wemote_vsi)
{
	memcpy(wemote_vsi, vsi, sizeof(*vsi));
}

static int vdec_av1_swice_setup_wat_fwom_swc_buf(stwuct vdec_av1_swice_instance *instance,
						 stwuct vdec_av1_swice_vsi *vsi,
						 stwuct vdec_wat_buf *wat_buf)
{
	stwuct vb2_v4w2_buffew *swc;
	stwuct vb2_v4w2_buffew *dst;

	swc = v4w2_m2m_next_swc_buf(instance->ctx->m2m_ctx);
	if (!swc)
		wetuwn -EINVAW;

	wat_buf->swc_buf_weq = swc->vb2_buf.weq_obj.weq;
	dst = &wat_buf->ts_info;
	v4w2_m2m_buf_copy_metadata(swc, dst, twue);
	vsi->fwame.cuw_ts = dst->vb2_buf.timestamp;

	wetuwn 0;
}

static showt vdec_av1_swice_wesowve_divisow_32(u32 D, showt *shift)
{
	int f;
	int e;

	*shift = vdec_av1_swice_get_msb(D);
	/* e is obtained fwom D aftew wesetting the most significant 1 bit. */
	e = D - ((u32)1 << *shift);
	/* Get the most significant DIV_WUT_BITS (8) bits of e into f */
	if (*shift > DIV_WUT_BITS)
		f = AV1_DIV_WOUND_UP_POW2(e, *shift - DIV_WUT_BITS);
	ewse
		f = e << (DIV_WUT_BITS - *shift);
	if (f > DIV_WUT_NUM)
		wetuwn -1;
	*shift += DIV_WUT_PWEC_BITS;
	/* Use f as wookup into the pwecomputed tabwe of muwtipwiews */
	wetuwn div_wut[f];
}

static void vdec_av1_swice_get_sheaw_pawams(stwuct vdec_av1_swice_gm *gm_pawams)
{
	const int *mat = gm_pawams->wmmat;
	showt shift;
	showt y;
	wong wong gv, dv;

	if (gm_pawams->wmmat[2] <= 0)
		wetuwn;

	gm_pawams->awpha = cwamp_vaw(mat[2] - (1 << WAWPEDMODEW_PWEC_BITS), S16_MIN, S16_MAX);
	gm_pawams->beta = cwamp_vaw(mat[3], S16_MIN, S16_MAX);

	y = vdec_av1_swice_wesowve_divisow_32(abs(mat[2]), &shift) * (mat[2] < 0 ? -1 : 1);

	gv = ((wong wong)mat[4] * (1 << WAWPEDMODEW_PWEC_BITS)) * y;
	gm_pawams->gamma = cwamp_vaw((int)AV1_DIV_WOUND_UP_POW2_SIGNED(gv, shift),
				     S16_MIN, S16_MAX);

	dv = ((wong wong)mat[3] * mat[4]) * y;
	gm_pawams->dewta = cwamp_vaw(mat[5] - (int)AV1_DIV_WOUND_UP_POW2_SIGNED(dv, shift) -
				     (1 << WAWPEDMODEW_PWEC_BITS), S16_MIN, S16_MAX);

	gm_pawams->awpha = AV1_DIV_WOUND_UP_POW2_SIGNED(gm_pawams->awpha, WAWP_PAWAM_WEDUCE_BITS) *
							(1 << WAWP_PAWAM_WEDUCE_BITS);
	gm_pawams->beta = AV1_DIV_WOUND_UP_POW2_SIGNED(gm_pawams->beta, WAWP_PAWAM_WEDUCE_BITS) *
						       (1 << WAWP_PAWAM_WEDUCE_BITS);
	gm_pawams->gamma = AV1_DIV_WOUND_UP_POW2_SIGNED(gm_pawams->gamma, WAWP_PAWAM_WEDUCE_BITS) *
							(1 << WAWP_PAWAM_WEDUCE_BITS);
	gm_pawams->dewta = AV1_DIV_WOUND_UP_POW2_SIGNED(gm_pawams->dewta, WAWP_PAWAM_WEDUCE_BITS) *
							(1 << WAWP_PAWAM_WEDUCE_BITS);
}

static void vdec_av1_swice_setup_gm(stwuct vdec_av1_swice_gm *gm,
				    stwuct v4w2_av1_gwobaw_motion *ctww_gm)
{
	u32 i, j;

	fow (i = 0; i < V4W2_AV1_TOTAW_WEFS_PEW_FWAME; i++) {
		gm[i].wmtype = ctww_gm->type[i];
		fow (j = 0; j < 6; j++)
			gm[i].wmmat[j] = ctww_gm->pawams[i][j];

		gm[i].invawid = !!(ctww_gm->invawid & BIT(i));
		gm[i].awpha = 0;
		gm[i].beta = 0;
		gm[i].gamma = 0;
		gm[i].dewta = 0;
		if (gm[i].wmtype <= V4W2_AV1_WAWP_MODEW_AFFINE)
			vdec_av1_swice_get_sheaw_pawams(&gm[i]);
	}
}

static void vdec_av1_swice_setup_seg(stwuct vdec_av1_swice_seg *seg,
				     stwuct v4w2_av1_segmentation *ctww_seg)
{
	u32 i, j;

	seg->segmentation_enabwed = SEGMENTATION_FWAG(ctww_seg, ENABWED);
	seg->segmentation_update_map = SEGMENTATION_FWAG(ctww_seg, UPDATE_MAP);
	seg->segmentation_tempowaw_update = SEGMENTATION_FWAG(ctww_seg, TEMPOWAW_UPDATE);
	seg->segmentation_update_data = SEGMENTATION_FWAG(ctww_seg, UPDATE_DATA);
	seg->segid_pweskip = SEGMENTATION_FWAG(ctww_seg, SEG_ID_PWE_SKIP);
	seg->wast_active_segid = ctww_seg->wast_active_seg_id;

	fow (i = 0; i < V4W2_AV1_MAX_SEGMENTS; i++) {
		seg->featuwe_enabwed_mask[i] = ctww_seg->featuwe_enabwed[i];
		fow (j = 0; j < V4W2_AV1_SEG_WVW_MAX; j++)
			seg->featuwe_data[i][j] = ctww_seg->featuwe_data[i][j];
	}
}

static void vdec_av1_swice_setup_quant(stwuct vdec_av1_swice_quantization *quant,
				       stwuct v4w2_av1_quantization *ctww_quant)
{
	quant->base_q_idx = ctww_quant->base_q_idx;
	quant->dewta_qydc = ctww_quant->dewta_q_y_dc;
	quant->dewta_qudc = ctww_quant->dewta_q_u_dc;
	quant->dewta_quac = ctww_quant->dewta_q_u_ac;
	quant->dewta_qvdc = ctww_quant->dewta_q_v_dc;
	quant->dewta_qvac = ctww_quant->dewta_q_v_ac;
	quant->qm_y = ctww_quant->qm_y;
	quant->qm_u = ctww_quant->qm_u;
	quant->qm_v = ctww_quant->qm_v;
	quant->using_qmatwix = QUANT_FWAG(ctww_quant, USING_QMATWIX);
}

static int vdec_av1_swice_get_qindex(stwuct vdec_av1_swice_uncompwessed_headew *uh,
				     int segmentation_id)
{
	stwuct vdec_av1_swice_seg *seg = &uh->seg;
	stwuct vdec_av1_swice_quantization *quant = &uh->quant;
	int data = 0, qindex = 0;

	if (seg->segmentation_enabwed &&
	    (seg->featuwe_enabwed_mask[segmentation_id] & BIT(SEG_WVW_AWT_Q))) {
		data = seg->featuwe_data[segmentation_id][SEG_WVW_AWT_Q];
		qindex = quant->base_q_idx + data;
		wetuwn cwamp_vaw(qindex, 0, MAXQ);
	}

	wetuwn quant->base_q_idx;
}

static void vdec_av1_swice_setup_ww(stwuct vdec_av1_swice_ww *ww,
				    stwuct v4w2_av1_woop_westowation  *ctww_ww)
{
	int i;

	ww->use_ww = 0;
	ww->use_chwoma_ww = 0;
	fow (i = 0; i < V4W2_AV1_NUM_PWANES_MAX; i++) {
		ww->fwame_westowation_type[i] = ctww_ww->fwame_westowation_type[i];
		ww->woop_westowation_size[i] = ctww_ww->woop_westowation_size[i];
		if (ww->fwame_westowation_type[i]) {
			ww->use_ww = 1;
			if (i > 0)
				ww->use_chwoma_ww = 1;
		}
	}
}

static void vdec_av1_swice_setup_wf(stwuct vdec_av1_swice_woop_fiwtew *wf,
				    stwuct v4w2_av1_woop_fiwtew *ctww_wf)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wf->woop_fiwtew_wevew); i++)
		wf->woop_fiwtew_wevew[i] = ctww_wf->wevew[i];

	fow (i = 0; i < V4W2_AV1_TOTAW_WEFS_PEW_FWAME; i++)
		wf->woop_fiwtew_wef_dewtas[i] = ctww_wf->wef_dewtas[i];

	fow (i = 0; i < AWWAY_SIZE(wf->woop_fiwtew_mode_dewtas); i++)
		wf->woop_fiwtew_mode_dewtas[i] = ctww_wf->mode_dewtas[i];

	wf->woop_fiwtew_shawpness = ctww_wf->shawpness;
	wf->woop_fiwtew_dewta_enabwed =
		   BIT_FWAG(ctww_wf, V4W2_AV1_WOOP_FIWTEW_FWAG_DEWTA_ENABWED);
}

static void vdec_av1_swice_setup_cdef(stwuct vdec_av1_swice_cdef *cdef,
				      stwuct v4w2_av1_cdef *ctww_cdef)
{
	int i;

	cdef->cdef_damping = ctww_cdef->damping_minus_3 + 3;
	cdef->cdef_bits = ctww_cdef->bits;

	fow (i = 0; i < V4W2_AV1_CDEF_MAX; i++) {
		if (ctww_cdef->y_sec_stwength[i] == 4)
			ctww_cdef->y_sec_stwength[i] -= 1;

		if (ctww_cdef->uv_sec_stwength[i] == 4)
			ctww_cdef->uv_sec_stwength[i] -= 1;

		cdef->cdef_y_stwength[i] =
			ctww_cdef->y_pwi_stwength[i] << SECONDAWY_FIWTEW_STWENGTH_NUM_BITS |
			ctww_cdef->y_sec_stwength[i];
		cdef->cdef_uv_stwength[i] =
			ctww_cdef->uv_pwi_stwength[i] << SECONDAWY_FIWTEW_STWENGTH_NUM_BITS |
			ctww_cdef->uv_sec_stwength[i];
	}
}

static void vdec_av1_swice_setup_seq(stwuct vdec_av1_swice_seq_headew *seq,
				     stwuct v4w2_ctww_av1_sequence *ctww_seq)
{
	seq->bitdepth = ctww_seq->bit_depth;
	seq->max_fwame_width = ctww_seq->max_fwame_width_minus_1 + 1;
	seq->max_fwame_height = ctww_seq->max_fwame_height_minus_1 + 1;
	seq->enabwe_supewwes = SEQUENCE_FWAG(ctww_seq, ENABWE_SUPEWWES);
	seq->enabwe_fiwtew_intwa = SEQUENCE_FWAG(ctww_seq, ENABWE_FIWTEW_INTWA);
	seq->enabwe_intwa_edge_fiwtew = SEQUENCE_FWAG(ctww_seq, ENABWE_INTWA_EDGE_FIWTEW);
	seq->enabwe_intewintwa_compound = SEQUENCE_FWAG(ctww_seq, ENABWE_INTEWINTWA_COMPOUND);
	seq->enabwe_masked_compound = SEQUENCE_FWAG(ctww_seq, ENABWE_MASKED_COMPOUND);
	seq->enabwe_duaw_fiwtew = SEQUENCE_FWAG(ctww_seq, ENABWE_DUAW_FIWTEW);
	seq->enabwe_jnt_comp = SEQUENCE_FWAG(ctww_seq, ENABWE_JNT_COMP);
	seq->mono_chwome = SEQUENCE_FWAG(ctww_seq, MONO_CHWOME);
	seq->enabwe_owdew_hint = SEQUENCE_FWAG(ctww_seq, ENABWE_OWDEW_HINT);
	seq->owdew_hint_bits = ctww_seq->owdew_hint_bits;
	seq->use_128x128_supewbwock = SEQUENCE_FWAG(ctww_seq, USE_128X128_SUPEWBWOCK);
	seq->subsampwing_x = SEQUENCE_FWAG(ctww_seq, SUBSAMPWING_X);
	seq->subsampwing_y = SEQUENCE_FWAG(ctww_seq, SUBSAMPWING_Y);
}

static void vdec_av1_swice_setup_tiwe(stwuct vdec_av1_swice_fwame *fwame,
				      stwuct v4w2_av1_tiwe_info *ctww_tiwe)
{
	stwuct vdec_av1_swice_seq_headew *seq = &fwame->seq;
	stwuct vdec_av1_swice_tiwe *tiwe = &fwame->uh.tiwe;
	u32 mib_size_wog2 = seq->use_128x128_supewbwock ? 5 : 4;
	int i;

	tiwe->tiwe_cows = ctww_tiwe->tiwe_cows;
	tiwe->tiwe_wows = ctww_tiwe->tiwe_wows;
	tiwe->context_update_tiwe_id = ctww_tiwe->context_update_tiwe_id;
	tiwe->unifowm_tiwe_spacing_fwag =
		BIT_FWAG(ctww_tiwe, V4W2_AV1_TIWE_INFO_FWAG_UNIFOWM_TIWE_SPACING);

	fow (i = 0; i < tiwe->tiwe_cows + 1; i++)
		tiwe->mi_cow_stawts[i] =
			AWIGN(ctww_tiwe->mi_cow_stawts[i], BIT(mib_size_wog2)) >> mib_size_wog2;

	fow (i = 0; i < tiwe->tiwe_wows + 1; i++)
		tiwe->mi_wow_stawts[i] =
			AWIGN(ctww_tiwe->mi_wow_stawts[i], BIT(mib_size_wog2)) >> mib_size_wog2;
}

static void vdec_av1_swice_setup_uh(stwuct vdec_av1_swice_instance *instance,
				    stwuct vdec_av1_swice_fwame *fwame,
				    stwuct v4w2_ctww_av1_fwame *ctww_fh)
{
	stwuct vdec_av1_swice_uncompwessed_headew *uh = &fwame->uh;
	int i;

	uh->use_wef_fwame_mvs = FH_FWAG(ctww_fh, USE_WEF_FWAME_MVS);
	uh->owdew_hint = ctww_fh->owdew_hint;
	vdec_av1_swice_setup_gm(uh->gm, &ctww_fh->gwobaw_motion);
	uh->upscawed_width = ctww_fh->upscawed_width;
	uh->fwame_width = ctww_fh->fwame_width_minus_1 + 1;
	uh->fwame_height = ctww_fh->fwame_height_minus_1 + 1;
	uh->mi_cows = ((uh->fwame_width + 7) >> 3) << 1;
	uh->mi_wows = ((uh->fwame_height + 7) >> 3) << 1;
	uh->weduced_tx_set = FH_FWAG(ctww_fh, WEDUCED_TX_SET);
	uh->tx_mode = ctww_fh->tx_mode;
	uh->unifowm_tiwe_spacing_fwag =
		BIT_FWAG(&ctww_fh->tiwe_info, V4W2_AV1_TIWE_INFO_FWAG_UNIFOWM_TIWE_SPACING);
	uh->intewpowation_fiwtew = ctww_fh->intewpowation_fiwtew;
	uh->awwow_wawped_motion = FH_FWAG(ctww_fh, AWWOW_WAWPED_MOTION);
	uh->is_motion_mode_switchabwe = FH_FWAG(ctww_fh, IS_MOTION_MODE_SWITCHABWE);
	uh->fwame_type = ctww_fh->fwame_type;
	uh->fwame_is_intwa = (uh->fwame_type == V4W2_AV1_INTWA_ONWY_FWAME ||
			      uh->fwame_type == V4W2_AV1_KEY_FWAME);

	if (!uh->fwame_is_intwa && FH_FWAG(ctww_fh, WEFEWENCE_SEWECT))
		uh->wefewence_mode = AV1_WEFEWENCE_MODE_SEWECT;
	ewse
		uh->wefewence_mode = AV1_SINGWE_WEFEWENCE;

	uh->awwow_high_pwecision_mv = FH_FWAG(ctww_fh, AWWOW_HIGH_PWECISION_MV);
	uh->awwow_intwa_bc = FH_FWAG(ctww_fh, AWWOW_INTWABC);
	uh->fowce_integew_mv = FH_FWAG(ctww_fh, FOWCE_INTEGEW_MV);
	uh->awwow_scween_content_toows = FH_FWAG(ctww_fh, AWWOW_SCWEEN_CONTENT_TOOWS);
	uh->ewwow_wesiwient_mode = FH_FWAG(ctww_fh, EWWOW_WESIWIENT_MODE);
	uh->pwimawy_wef_fwame = ctww_fh->pwimawy_wef_fwame;
	uh->disabwe_fwame_end_update_cdf =
			FH_FWAG(ctww_fh, DISABWE_FWAME_END_UPDATE_CDF);
	uh->disabwe_cdf_update = FH_FWAG(ctww_fh, DISABWE_CDF_UPDATE);
	uh->skip_mode.skip_mode_pwesent = FH_FWAG(ctww_fh, SKIP_MODE_PWESENT);
	uh->skip_mode.skip_mode_fwame[0] =
		ctww_fh->skip_mode_fwame[0] - V4W2_AV1_WEF_WAST_FWAME;
	uh->skip_mode.skip_mode_fwame[1] =
		ctww_fh->skip_mode_fwame[1] - V4W2_AV1_WEF_WAST_FWAME;
	uh->skip_mode.skip_mode_awwowed = ctww_fh->skip_mode_fwame[0] ? 1 : 0;

	vdec_av1_swice_setup_seg(&uh->seg, &ctww_fh->segmentation);
	uh->dewta_q_wf.dewta_q_pwesent = QUANT_FWAG(&ctww_fh->quantization, DEWTA_Q_PWESENT);
	uh->dewta_q_wf.dewta_q_wes = 1 << ctww_fh->quantization.dewta_q_wes;
	uh->dewta_q_wf.dewta_wf_pwesent =
		BIT_FWAG(&ctww_fh->woop_fiwtew, V4W2_AV1_WOOP_FIWTEW_FWAG_DEWTA_WF_PWESENT);
	uh->dewta_q_wf.dewta_wf_wes = ctww_fh->woop_fiwtew.dewta_wf_wes;
	uh->dewta_q_wf.dewta_wf_muwti =
		BIT_FWAG(&ctww_fh->woop_fiwtew, V4W2_AV1_WOOP_FIWTEW_FWAG_DEWTA_WF_MUWTI);
	vdec_av1_swice_setup_quant(&uh->quant, &ctww_fh->quantization);

	uh->coded_woss_wess = 1;
	fow (i = 0; i < V4W2_AV1_MAX_SEGMENTS; i++) {
		uh->quant.qindex[i] = vdec_av1_swice_get_qindex(uh, i);
		uh->woss_wess_awway[i] =
			(uh->quant.qindex[i] == 0 && uh->quant.dewta_qydc == 0 &&
			uh->quant.dewta_quac == 0 && uh->quant.dewta_qudc == 0 &&
			uh->quant.dewta_qvac == 0 && uh->quant.dewta_qvdc == 0);

		if (!uh->woss_wess_awway[i])
			uh->coded_woss_wess = 0;
	}

	vdec_av1_swice_setup_ww(&uh->ww, &ctww_fh->woop_westowation);
	uh->supewwes_denom = ctww_fh->supewwes_denom;
	vdec_av1_swice_setup_wf(&uh->woop_fiwtew, &ctww_fh->woop_fiwtew);
	vdec_av1_swice_setup_cdef(&uh->cdef, &ctww_fh->cdef);
	vdec_av1_swice_setup_tiwe(fwame, &ctww_fh->tiwe_info);
}

static int vdec_av1_swice_setup_tiwe_gwoup(stwuct vdec_av1_swice_instance *instance,
					   stwuct vdec_av1_swice_vsi *vsi)
{
	stwuct v4w2_ctww_av1_tiwe_gwoup_entwy *ctww_tge;
	stwuct vdec_av1_swice_tiwe_gwoup *tiwe_gwoup = &instance->tiwe_gwoup;
	stwuct vdec_av1_swice_uncompwessed_headew *uh = &vsi->fwame.uh;
	stwuct vdec_av1_swice_tiwe *tiwe = &uh->tiwe;
	stwuct v4w2_ctww *ctww;
	u32 tge_size;
	int i;

	ctww = v4w2_ctww_find(&instance->ctx->ctww_hdw, V4W2_CID_STATEWESS_AV1_TIWE_GWOUP_ENTWY);
	if (!ctww)
		wetuwn -EINVAW;

	tge_size = ctww->ewems;
	ctww_tge = (stwuct v4w2_ctww_av1_tiwe_gwoup_entwy *)ctww->p_cuw.p;

	tiwe_gwoup->num_tiwes = tiwe->tiwe_cows * tiwe->tiwe_wows;

	if (tiwe_gwoup->num_tiwes != tge_size ||
	    tiwe_gwoup->num_tiwes > V4W2_AV1_MAX_TIWE_COUNT) {
		mtk_vdec_eww(instance->ctx, "invawid tge_size %d, tiwe_num:%d\n",
			     tge_size, tiwe_gwoup->num_tiwes);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < tge_size; i++) {
		if (i != ctww_tge[i].tiwe_wow * vsi->fwame.uh.tiwe.tiwe_cows +
		    ctww_tge[i].tiwe_cow) {
			mtk_vdec_eww(instance->ctx, "invawid tge info %d, %d %d %d\n",
				     i, ctww_tge[i].tiwe_wow, ctww_tge[i].tiwe_cow,
				     vsi->fwame.uh.tiwe.tiwe_wows);
			wetuwn -EINVAW;
		}
		tiwe_gwoup->tiwe_size[i] = ctww_tge[i].tiwe_size;
		tiwe_gwoup->tiwe_stawt_offset[i] = ctww_tge[i].tiwe_offset;
	}

	wetuwn 0;
}

static inwine void vdec_av1_swice_setup_state(stwuct vdec_av1_swice_vsi *vsi)
{
	memset(&vsi->state, 0, sizeof(vsi->state));
}

static void vdec_av1_swice_setup_scawe_factows(stwuct vdec_av1_swice_fwame_wefs *fwame_wef,
					       stwuct vdec_av1_swice_fwame_info *wef_fwame_info,
					       stwuct vdec_av1_swice_uncompwessed_headew *uh)
{
	stwuct vdec_av1_swice_scawe_factows *scawe_factows = &fwame_wef->scawe_factows;
	u32 wef_upscawed_width = wef_fwame_info->upscawed_width;
	u32 wef_fwame_height = wef_fwame_info->fwame_height;
	u32 fwame_width = uh->fwame_width;
	u32 fwame_height = uh->fwame_height;

	if (!vdec_av1_swice_need_scawe(wef_upscawed_width, wef_fwame_height,
				       fwame_width, fwame_height)) {
		scawe_factows->x_scawe = -1;
		scawe_factows->y_scawe = -1;
		scawe_factows->is_scawed = 0;
		wetuwn;
	}

	scawe_factows->x_scawe =
		((wef_upscawed_width << AV1_WEF_SCAWE_SHIFT) + (fwame_width >> 1)) / fwame_width;
	scawe_factows->y_scawe =
		((wef_fwame_height << AV1_WEF_SCAWE_SHIFT) + (fwame_height >> 1)) / fwame_height;
	scawe_factows->is_scawed =
		(scawe_factows->x_scawe != AV1_WEF_INVAWID_SCAWE) &&
		(scawe_factows->y_scawe != AV1_WEF_INVAWID_SCAWE) &&
		(scawe_factows->x_scawe != AV1_WEF_NO_SCAWE ||
		 scawe_factows->y_scawe != AV1_WEF_NO_SCAWE);
	scawe_factows->x_step =
		AV1_DIV_WOUND_UP_POW2(scawe_factows->x_scawe,
				      AV1_WEF_SCAWE_SHIFT - AV1_SCAWE_SUBPEW_BITS);
	scawe_factows->y_step =
		AV1_DIV_WOUND_UP_POW2(scawe_factows->y_scawe,
				      AV1_WEF_SCAWE_SHIFT - AV1_SCAWE_SUBPEW_BITS);
}

static unsigned chaw vdec_av1_swice_get_sign_bias(int a,
						  int b,
						  u8 enabwe_owdew_hint,
						  u8 owdew_hint_bits)
{
	int diff = 0;
	int m = 0;
	unsigned chaw wesuwt = 0;

	if (!enabwe_owdew_hint)
		wetuwn 0;

	diff = a - b;
	m = 1 << (owdew_hint_bits - 1);
	diff = (diff & (m - 1)) - (diff & m);

	if (diff > 0)
		wesuwt = 1;

	wetuwn wesuwt;
}

static void vdec_av1_swice_setup_wef(stwuct vdec_av1_swice_pfc *pfc,
				     stwuct v4w2_ctww_av1_fwame *ctww_fh)
{
	stwuct vdec_av1_swice_vsi *vsi = &pfc->vsi;
	stwuct vdec_av1_swice_fwame *fwame = &vsi->fwame;
	stwuct vdec_av1_swice_swot *swots = &vsi->swots;
	stwuct vdec_av1_swice_uncompwessed_headew *uh = &fwame->uh;
	stwuct vdec_av1_swice_seq_headew *seq = &fwame->seq;
	stwuct vdec_av1_swice_fwame_info *cuw_fwame_info =
		&swots->fwame_info[vsi->swot_id];
	stwuct vdec_av1_swice_fwame_info *fwame_info;
	int i, swot_id;

	if (uh->fwame_is_intwa)
		wetuwn;

	fow (i = 0; i < V4W2_AV1_WEFS_PEW_FWAME; i++) {
		int wef_idx = ctww_fh->wef_fwame_idx[i];

		pfc->wef_idx[i] = ctww_fh->wefewence_fwame_ts[wef_idx];
		swot_id = fwame->wef_fwame_map[wef_idx];
		fwame_info = &swots->fwame_info[swot_id];
		if (swot_id == AV1_INVAWID_IDX) {
			pw_eww(MTK_DBG_V4W2_STW "cannot match wefewence[%d] 0x%wwx\n", i,
			       ctww_fh->wefewence_fwame_ts[wef_idx]);
			fwame->owdew_hints[i] = 0;
			fwame->wef_fwame_vawid[i] = 0;
			continue;
		}

		fwame->fwame_wefs[i].wef_fb_idx = swot_id;
		vdec_av1_swice_setup_scawe_factows(&fwame->fwame_wefs[i],
						   fwame_info, uh);
		if (!seq->enabwe_owdew_hint)
			fwame->wef_fwame_sign_bias[i + 1] = 0;
		ewse
			fwame->wef_fwame_sign_bias[i + 1] =
				vdec_av1_swice_get_sign_bias(fwame_info->owdew_hint,
							     uh->owdew_hint,
							     seq->enabwe_owdew_hint,
							     seq->owdew_hint_bits);

		fwame->owdew_hints[i] = ctww_fh->owdew_hints[i + 1];
		cuw_fwame_info->owdew_hints[i] = fwame->owdew_hints[i];
		fwame->wef_fwame_vawid[i] = 1;
	}
}

static void vdec_av1_swice_get_pwevious(stwuct vdec_av1_swice_vsi *vsi)
{
	stwuct vdec_av1_swice_fwame *fwame = &vsi->fwame;

	if (fwame->uh.pwimawy_wef_fwame == AV1_PWIMAWY_WEF_NONE)
		fwame->pwev_fb_idx = AV1_INVAWID_IDX;
	ewse
		fwame->pwev_fb_idx = fwame->fwame_wefs[fwame->uh.pwimawy_wef_fwame].wef_fb_idx;
}

static inwine void vdec_av1_swice_setup_opewating_mode(stwuct vdec_av1_swice_instance *instance,
						       stwuct vdec_av1_swice_fwame *fwame)
{
	fwame->wawge_scawe_tiwe = 0;
}

static int vdec_av1_swice_setup_pfc(stwuct vdec_av1_swice_instance *instance,
				    stwuct vdec_av1_swice_pfc *pfc)
{
	stwuct v4w2_ctww_av1_fwame *ctww_fh;
	stwuct v4w2_ctww_av1_sequence *ctww_seq;
	stwuct vdec_av1_swice_vsi *vsi = &pfc->vsi;
	int wet = 0;

	/* fwame headew */
	ctww_fh = (stwuct v4w2_ctww_av1_fwame *)
		  vdec_av1_get_ctww_ptw(instance->ctx,
					V4W2_CID_STATEWESS_AV1_FWAME);
	if (IS_EWW(ctww_fh))
		wetuwn PTW_EWW(ctww_fh);

	ctww_seq = (stwuct v4w2_ctww_av1_sequence *)
		   vdec_av1_get_ctww_ptw(instance->ctx,
					 V4W2_CID_STATEWESS_AV1_SEQUENCE);
	if (IS_EWW(ctww_seq))
		wetuwn PTW_EWW(ctww_seq);

	/* setup vsi infowmation */
	vdec_av1_swice_setup_seq(&vsi->fwame.seq, ctww_seq);
	vdec_av1_swice_setup_uh(instance, &vsi->fwame, ctww_fh);
	vdec_av1_swice_setup_opewating_mode(instance, &vsi->fwame);

	vdec_av1_swice_setup_state(vsi);
	vdec_av1_swice_setup_swot(instance, vsi, ctww_fh);
	vdec_av1_swice_setup_wef(pfc, ctww_fh);
	vdec_av1_swice_get_pwevious(vsi);

	pfc->seq = instance->seq;
	instance->seq++;

	wetuwn wet;
}

static void vdec_av1_swice_setup_wat_buffew(stwuct vdec_av1_swice_instance *instance,
					    stwuct vdec_av1_swice_vsi *vsi,
					    stwuct mtk_vcodec_mem *bs,
					    stwuct vdec_wat_buf *wat_buf)
{
	stwuct vdec_av1_swice_wowk_buffew *wowk_buffew;
	int i;

	vsi->bs.dma_addw = bs->dma_addw;
	vsi->bs.size = bs->size;

	vsi->ube.dma_addw = wat_buf->ctx->msg_queue.wdma_addw.dma_addw;
	vsi->ube.size = wat_buf->ctx->msg_queue.wdma_addw.size;
	vsi->twans.dma_addw = wat_buf->ctx->msg_queue.wdma_wptw_addw;
	/* used to stowe twans end */
	vsi->twans.dma_addw_end = wat_buf->ctx->msg_queue.wdma_wptw_addw;
	vsi->eww_map.dma_addw = wat_buf->wdma_eww_addw.dma_addw;
	vsi->eww_map.size = wat_buf->wdma_eww_addw.size;
	vsi->wd_mv.dma_addw = wat_buf->wd_mv_addw.dma_addw;
	vsi->wd_mv.size = wat_buf->wd_mv_addw.size;

	vsi->wow_info.buf = 0;
	vsi->wow_info.size = 0;

	wowk_buffew = vsi->wowk_buffew;

	fow (i = 0; i < AV1_MAX_FWAME_BUF_COUNT; i++) {
		wowk_buffew[i].mv_addw.buf = instance->mv[i].dma_addw;
		wowk_buffew[i].mv_addw.size = instance->mv[i].size;
		wowk_buffew[i].segid_addw.buf = instance->seg[i].dma_addw;
		wowk_buffew[i].segid_addw.size = instance->seg[i].size;
		wowk_buffew[i].cdf_addw.buf = instance->cdf[i].dma_addw;
		wowk_buffew[i].cdf_addw.size = instance->cdf[i].size;
	}

	vsi->cdf_tmp.buf = instance->cdf_temp.dma_addw;
	vsi->cdf_tmp.size = instance->cdf_temp.size;

	vsi->tiwe.buf = instance->tiwe.dma_addw;
	vsi->tiwe.size = instance->tiwe.size;
	memcpy(wat_buf->tiwe_addw.va, instance->tiwe.va, 64 * instance->tiwe_gwoup.num_tiwes);

	vsi->cdf_tabwe.buf = instance->cdf_tabwe.dma_addw;
	vsi->cdf_tabwe.size = instance->cdf_tabwe.size;
	vsi->iq_tabwe.buf = instance->iq_tabwe.dma_addw;
	vsi->iq_tabwe.size = instance->iq_tabwe.size;
}

static void vdec_av1_swice_setup_seg_buffew(stwuct vdec_av1_swice_instance *instance,
					    stwuct vdec_av1_swice_vsi *vsi)
{
	stwuct vdec_av1_swice_uncompwessed_headew *uh = &vsi->fwame.uh;
	stwuct mtk_vcodec_mem *buf;

	/* weset segment buffew */
	if (uh->pwimawy_wef_fwame == AV1_PWIMAWY_WEF_NONE || !uh->seg.segmentation_enabwed) {
		mtk_vdec_debug(instance->ctx, "weset seg %d\n", vsi->swot_id);
		if (vsi->swot_id != AV1_INVAWID_IDX) {
			buf = &instance->seg[vsi->swot_id];
			memset(buf->va, 0, buf->size);
		}
	}
}

static void vdec_av1_swice_setup_tiwe_buffew(stwuct vdec_av1_swice_instance *instance,
					     stwuct vdec_av1_swice_vsi *vsi,
					     stwuct mtk_vcodec_mem *bs)
{
	stwuct vdec_av1_swice_tiwe_gwoup *tiwe_gwoup = &instance->tiwe_gwoup;
	stwuct vdec_av1_swice_uncompwessed_headew *uh = &vsi->fwame.uh;
	stwuct vdec_av1_swice_tiwe *tiwe = &uh->tiwe;
	u32 tiwe_num, tiwe_wow, tiwe_cow;
	u32 awwow_update_cdf = 0;
	u32 sb_boundawy_x_m1 = 0, sb_boundawy_y_m1 = 0;
	int tiwe_info_base;
	u64 tiwe_buf_pa;
	u32 *tiwe_info_buf = instance->tiwe.va;
	u64 pa = (u64)bs->dma_addw;

	if (uh->disabwe_cdf_update == 0)
		awwow_update_cdf = 1;

	fow (tiwe_num = 0; tiwe_num < tiwe_gwoup->num_tiwes; tiwe_num++) {
		/* each uint32 takes pwace of 4 bytes */
		tiwe_info_base = (AV1_TIWE_BUF_SIZE * tiwe_num) >> 2;
		tiwe_wow = tiwe_num / tiwe->tiwe_cows;
		tiwe_cow = tiwe_num % tiwe->tiwe_cows;
		tiwe_info_buf[tiwe_info_base + 0] = (tiwe_gwoup->tiwe_size[tiwe_num] << 3);
		tiwe_buf_pa = pa + tiwe_gwoup->tiwe_stawt_offset[tiwe_num];

		/* save av1 tiwe high 4bits(bit 32-35) addwess in wowew 4 bits position
		 * and cweaw owiginaw fow hw wequiwement.
		 */
		tiwe_info_buf[tiwe_info_base + 1] = (tiwe_buf_pa & 0xFFFFFFF0uww) |
			((tiwe_buf_pa & 0xF00000000uww) >> 32);
		tiwe_info_buf[tiwe_info_base + 2] = (tiwe_buf_pa & 0xFuww) << 3;

		sb_boundawy_x_m1 =
			(tiwe->mi_cow_stawts[tiwe_cow + 1] - tiwe->mi_cow_stawts[tiwe_cow] - 1) &
			0x3f;
		sb_boundawy_y_m1 =
			(tiwe->mi_wow_stawts[tiwe_wow + 1] - tiwe->mi_wow_stawts[tiwe_wow] - 1) &
			0x1ff;

		tiwe_info_buf[tiwe_info_base + 3] = (sb_boundawy_y_m1 << 7) | sb_boundawy_x_m1;
		tiwe_info_buf[tiwe_info_base + 4] = ((awwow_update_cdf << 18) | (1 << 16));

		if (tiwe_num == tiwe->context_update_tiwe_id &&
		    uh->disabwe_fwame_end_update_cdf == 0)
			tiwe_info_buf[tiwe_info_base + 4] |= (1 << 17);

		mtk_vdec_debug(instance->ctx, "// tiwe buf %d pos(%dx%d) offset 0x%x\n",
			       tiwe_num, tiwe_wow, tiwe_cow, tiwe_info_base);
		mtk_vdec_debug(instance->ctx, "// %08x %08x %08x %08x\n",
			       tiwe_info_buf[tiwe_info_base + 0],
			       tiwe_info_buf[tiwe_info_base + 1],
			       tiwe_info_buf[tiwe_info_base + 2],
			       tiwe_info_buf[tiwe_info_base + 3]);
		mtk_vdec_debug(instance->ctx, "// %08x %08x %08x %08x\n",
			       tiwe_info_buf[tiwe_info_base + 4],
			       tiwe_info_buf[tiwe_info_base + 5],
			       tiwe_info_buf[tiwe_info_base + 6],
			       tiwe_info_buf[tiwe_info_base + 7]);
	}
}

static int vdec_av1_swice_setup_wat(stwuct vdec_av1_swice_instance *instance,
				    stwuct mtk_vcodec_mem *bs,
				    stwuct vdec_wat_buf *wat_buf,
				    stwuct vdec_av1_swice_pfc *pfc)
{
	stwuct vdec_av1_swice_vsi *vsi = &pfc->vsi;
	int wet;

	wet = vdec_av1_swice_setup_wat_fwom_swc_buf(instance, vsi, wat_buf);
	if (wet)
		wetuwn wet;

	wet = vdec_av1_swice_setup_pfc(instance, pfc);
	if (wet)
		wetuwn wet;

	wet = vdec_av1_swice_setup_tiwe_gwoup(instance, vsi);
	if (wet)
		wetuwn wet;

	wet = vdec_av1_swice_awwoc_wowking_buffew(instance, vsi);
	if (wet)
		wetuwn wet;

	vdec_av1_swice_setup_seg_buffew(instance, vsi);
	vdec_av1_swice_setup_tiwe_buffew(instance, vsi, bs);
	vdec_av1_swice_setup_wat_buffew(instance, vsi, bs, wat_buf);

	wetuwn 0;
}

static int vdec_av1_swice_update_wat(stwuct vdec_av1_swice_instance *instance,
				     stwuct vdec_wat_buf *wat_buf,
				     stwuct vdec_av1_swice_pfc *pfc)
{
	stwuct vdec_av1_swice_vsi *vsi;

	vsi = &pfc->vsi;
	mtk_vdec_debug(instance->ctx, "fwame %u WAT CWC 0x%08x, output size is %d\n",
		       pfc->seq, vsi->state.cwc[0], vsi->state.out_size);

	/* buffew fuww, need to we-decode */
	if (vsi->state.fuww) {
		/* buffew not enough */
		if (vsi->twans.dma_addw_end - vsi->twans.dma_addw == vsi->ube.size)
			wetuwn -ENOMEM;
		wetuwn -EAGAIN;
	}

	instance->width = vsi->fwame.uh.upscawed_width;
	instance->height = vsi->fwame.uh.fwame_height;
	instance->fwame_type = vsi->fwame.uh.fwame_type;

	wetuwn 0;
}

static int vdec_av1_swice_setup_cowe_to_dst_buf(stwuct vdec_av1_swice_instance *instance,
						stwuct vdec_wat_buf *wat_buf)
{
	stwuct vb2_v4w2_buffew *dst;

	dst = v4w2_m2m_next_dst_buf(instance->ctx->m2m_ctx);
	if (!dst)
		wetuwn -EINVAW;

	v4w2_m2m_buf_copy_metadata(&wat_buf->ts_info, dst, twue);

	wetuwn 0;
}

static int vdec_av1_swice_setup_cowe_buffew(stwuct vdec_av1_swice_instance *instance,
					    stwuct vdec_av1_swice_pfc *pfc,
					    stwuct vdec_av1_swice_vsi *vsi,
					    stwuct vdec_fb *fb,
					    stwuct vdec_wat_buf *wat_buf)
{
	stwuct vb2_buffew *vb;
	stwuct vb2_queue *vq;
	int w, h, pwane, size;
	int i;

	pwane = instance->ctx->q_data[MTK_Q_DATA_DST].fmt->num_pwanes;
	w = vsi->fwame.uh.upscawed_width;
	h = vsi->fwame.uh.fwame_height;
	size = AWIGN(w, VCODEC_DEC_AWIGNED_64) * AWIGN(h, VCODEC_DEC_AWIGNED_64);

	/* fwame buffew */
	vsi->fb.y.dma_addw = fb->base_y.dma_addw;
	if (pwane == 1)
		vsi->fb.c.dma_addw = fb->base_y.dma_addw + size;
	ewse
		vsi->fb.c.dma_addw = fb->base_c.dma_addw;

	/* wefewence buffews */
	vq = v4w2_m2m_get_vq(instance->ctx->m2m_ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
	if (!vq)
		wetuwn -EINVAW;

	/* get cuwwent output buffew */
	vb = &v4w2_m2m_next_dst_buf(instance->ctx->m2m_ctx)->vb2_buf;
	if (!vb)
		wetuwn -EINVAW;

	/* get buffew addwess fwom vb2buf */
	fow (i = 0; i < V4W2_AV1_WEFS_PEW_FWAME; i++) {
		stwuct vdec_av1_swice_fb *vwef = &vsi->wef[i];

		vb = vb2_find_buffew(vq, pfc->wef_idx[i]);
		if (!vb) {
			memset(vwef, 0, sizeof(*vwef));
			continue;
		}

		vwef->y.dma_addw = vb2_dma_contig_pwane_dma_addw(vb, 0);
		if (pwane == 1)
			vwef->c.dma_addw = vwef->y.dma_addw + size;
		ewse
			vwef->c.dma_addw = vb2_dma_contig_pwane_dma_addw(vb, 1);
	}
	vsi->tiwe.dma_addw = wat_buf->tiwe_addw.dma_addw;
	vsi->tiwe.size = wat_buf->tiwe_addw.size;

	wetuwn 0;
}

static int vdec_av1_swice_setup_cowe(stwuct vdec_av1_swice_instance *instance,
				     stwuct vdec_fb *fb,
				     stwuct vdec_wat_buf *wat_buf,
				     stwuct vdec_av1_swice_pfc *pfc)
{
	stwuct vdec_av1_swice_vsi *vsi = &pfc->vsi;
	int wet;

	wet = vdec_av1_swice_setup_cowe_to_dst_buf(instance, wat_buf);
	if (wet)
		wetuwn wet;

	wet = vdec_av1_swice_setup_cowe_buffew(instance, pfc, vsi, fb, wat_buf);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int vdec_av1_swice_update_cowe(stwuct vdec_av1_swice_instance *instance,
				      stwuct vdec_wat_buf *wat_buf,
				      stwuct vdec_av1_swice_pfc *pfc)
{
	stwuct vdec_av1_swice_vsi *vsi = instance->cowe_vsi;

	mtk_vdec_debug(instance->ctx, "fwame %u Y_CWC %08x %08x %08x %08x\n",
		       pfc->seq, vsi->state.cwc[0], vsi->state.cwc[1],
		       vsi->state.cwc[2], vsi->state.cwc[3]);
	mtk_vdec_debug(instance->ctx, "fwame %u C_CWC %08x %08x %08x %08x\n",
		       pfc->seq, vsi->state.cwc[8], vsi->state.cwc[9],
		       vsi->state.cwc[10], vsi->state.cwc[11]);

	wetuwn 0;
}

static int vdec_av1_swice_init(stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct vdec_av1_swice_instance *instance;
	stwuct vdec_av1_swice_init_vsi *vsi;
	int wet;

	instance = kzawwoc(sizeof(*instance), GFP_KEWNEW);
	if (!instance)
		wetuwn -ENOMEM;

	instance->ctx = ctx;
	instance->vpu.id = SCP_IPI_VDEC_WAT;
	instance->vpu.cowe_id = SCP_IPI_VDEC_COWE;
	instance->vpu.ctx = ctx;
	instance->vpu.codec_type = ctx->cuwwent_codec;

	wet = vpu_dec_init(&instance->vpu);
	if (wet) {
		mtk_vdec_eww(ctx, "faiwed to init vpu dec, wet %d\n", wet);
		goto ewwow_vpu_init;
	}

	/* init vsi and gwobaw fwags */
	vsi = instance->vpu.vsi;
	if (!vsi) {
		mtk_vdec_eww(ctx, "faiwed to get AV1 vsi\n");
		wet = -EINVAW;
		goto ewwow_vsi;
	}
	instance->init_vsi = vsi;
	instance->cowe_vsi = mtk_vcodec_fw_map_dm_addw(ctx->dev->fw_handwew, (u32)vsi->cowe_vsi);

	if (!instance->cowe_vsi) {
		mtk_vdec_eww(ctx, "faiwed to get AV1 cowe vsi\n");
		wet = -EINVAW;
		goto ewwow_vsi;
	}

	if (vsi->vsi_size != sizeof(stwuct vdec_av1_swice_vsi))
		mtk_vdec_eww(ctx, "wemote vsi size 0x%x mismatch! expected: 0x%zx\n",
			     vsi->vsi_size, sizeof(stwuct vdec_av1_swice_vsi));

	instance->iwq_enabwed = 1;
	instance->innewacing_mode = IS_VDEC_INNEW_WACING(instance->ctx->dev->dec_capabiwity);

	mtk_vdec_debug(ctx, "vsi 0x%p cowe_vsi 0x%wwx 0x%p, innewacing_mode %d\n",
		       vsi, vsi->cowe_vsi, instance->cowe_vsi, instance->innewacing_mode);

	wet = vdec_av1_swice_init_cdf_tabwe(instance);
	if (wet)
		goto ewwow_vsi;

	wet = vdec_av1_swice_init_iq_tabwe(instance);
	if (wet)
		goto ewwow_vsi;

	ctx->dwv_handwe = instance;

	wetuwn 0;
ewwow_vsi:
	vpu_dec_deinit(&instance->vpu);
ewwow_vpu_init:
	kfwee(instance);

	wetuwn wet;
}

static void vdec_av1_swice_deinit(void *h_vdec)
{
	stwuct vdec_av1_swice_instance *instance = h_vdec;

	if (!instance)
		wetuwn;
	mtk_vdec_debug(instance->ctx, "h_vdec 0x%p\n", h_vdec);
	vpu_dec_deinit(&instance->vpu);
	vdec_av1_swice_fwee_wowking_buffew(instance);
	vdec_msg_queue_deinit(&instance->ctx->msg_queue, instance->ctx);
	kfwee(instance);
}

static int vdec_av1_swice_fwush(void *h_vdec, stwuct mtk_vcodec_mem *bs,
				stwuct vdec_fb *fb, boow *wes_chg)
{
	stwuct vdec_av1_swice_instance *instance = h_vdec;
	int i;

	mtk_vdec_debug(instance->ctx, "fwush ...\n");

	vdec_msg_queue_wait_wat_buf_fuww(&instance->ctx->msg_queue);

	fow (i = 0; i < AV1_MAX_FWAME_BUF_COUNT; i++)
		vdec_av1_swice_cweaw_fb(&instance->swots.fwame_info[i]);

	wetuwn vpu_dec_weset(&instance->vpu);
}

static void vdec_av1_swice_get_pic_info(stwuct vdec_av1_swice_instance *instance)
{
	stwuct mtk_vcodec_dec_ctx *ctx = instance->ctx;
	u32 data[3];

	mtk_vdec_debug(ctx, "w %u h %u\n", ctx->picinfo.pic_w, ctx->picinfo.pic_h);

	data[0] = ctx->picinfo.pic_w;
	data[1] = ctx->picinfo.pic_h;
	data[2] = ctx->captuwe_fouwcc;
	vpu_dec_get_pawam(&instance->vpu, data, 3, GET_PAWAM_PIC_INFO);

	ctx->picinfo.buf_w = AWIGN(ctx->picinfo.pic_w, VCODEC_DEC_AWIGNED_64);
	ctx->picinfo.buf_h = AWIGN(ctx->picinfo.pic_h, VCODEC_DEC_AWIGNED_64);
	ctx->picinfo.fb_sz[0] = instance->vpu.fb_sz[0];
	ctx->picinfo.fb_sz[1] = instance->vpu.fb_sz[1];
}

static inwine void vdec_av1_swice_get_dpb_size(stwuct vdec_av1_swice_instance *instance,
					       u32 *dpb_sz)
{
	/* wefew av1 specification */
	*dpb_sz = V4W2_AV1_TOTAW_WEFS_PEW_FWAME + 1;
}

static void vdec_av1_swice_get_cwop_info(stwuct vdec_av1_swice_instance *instance,
					 stwuct v4w2_wect *cw)
{
	stwuct mtk_vcodec_dec_ctx *ctx = instance->ctx;

	cw->weft = 0;
	cw->top = 0;
	cw->width = ctx->picinfo.pic_w;
	cw->height = ctx->picinfo.pic_h;

	mtk_vdec_debug(ctx, "w=%d, t=%d, w=%d, h=%d\n",
		       cw->weft, cw->top, cw->width, cw->height);
}

static int vdec_av1_swice_get_pawam(void *h_vdec, enum vdec_get_pawam_type type, void *out)
{
	stwuct vdec_av1_swice_instance *instance = h_vdec;

	switch (type) {
	case GET_PAWAM_PIC_INFO:
		vdec_av1_swice_get_pic_info(instance);
		bweak;
	case GET_PAWAM_DPB_SIZE:
		vdec_av1_swice_get_dpb_size(instance, out);
		bweak;
	case GET_PAWAM_CWOP_INFO:
		vdec_av1_swice_get_cwop_info(instance, out);
		bweak;
	defauwt:
		mtk_vdec_eww(instance->ctx, "invawid get pawametew type=%d\n", type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vdec_av1_swice_wat_decode(void *h_vdec, stwuct mtk_vcodec_mem *bs,
				     stwuct vdec_fb *fb, boow *wes_chg)
{
	stwuct vdec_av1_swice_instance *instance = h_vdec;
	stwuct vdec_wat_buf *wat_buf;
	stwuct vdec_av1_swice_pfc *pfc;
	stwuct vdec_av1_swice_vsi *vsi;
	stwuct mtk_vcodec_dec_ctx *ctx;
	int wet;

	if (!instance || !instance->ctx)
		wetuwn -EINVAW;

	ctx = instance->ctx;
	/* init msgQ fow the fiwst time */
	if (vdec_msg_queue_init(&ctx->msg_queue, ctx,
				vdec_av1_swice_cowe_decode, sizeof(*pfc))) {
		mtk_vdec_eww(ctx, "faiwed to init AV1 msg queue\n");
		wetuwn -ENOMEM;
	}

	/* bs NUWW means fwush decodew */
	if (!bs)
		wetuwn vdec_av1_swice_fwush(h_vdec, bs, fb, wes_chg);

	wat_buf = vdec_msg_queue_dqbuf(&ctx->msg_queue.wat_ctx);
	if (!wat_buf) {
		mtk_vdec_eww(ctx, "faiwed to get AV1 wat buf\n");
		wetuwn -EAGAIN;
	}
	pfc = (stwuct vdec_av1_swice_pfc *)wat_buf->pwivate_data;
	if (!pfc) {
		wet = -EINVAW;
		goto eww_fwee_fb_out;
	}
	vsi = &pfc->vsi;

	wet = vdec_av1_swice_setup_wat(instance, bs, wat_buf, pfc);
	if (wet) {
		mtk_vdec_eww(ctx, "faiwed to setup AV1 wat wet %d\n", wet);
		goto eww_fwee_fb_out;
	}

	vdec_av1_swice_vsi_to_wemote(vsi, instance->vsi);
	wet = vpu_dec_stawt(&instance->vpu, NUWW, 0);
	if (wet) {
		mtk_vdec_eww(ctx, "faiwed to dec AV1 wet %d\n", wet);
		goto eww_fwee_fb_out;
	}
	if (instance->innewacing_mode)
		vdec_msg_queue_qbuf(&ctx->msg_queue.cowe_ctx, wat_buf);

	if (instance->iwq_enabwed) {
		wet = mtk_vcodec_wait_fow_done_ctx(ctx, MTK_INST_IWQ_WECEIVED,
						   WAIT_INTW_TIMEOUT_MS,
						   MTK_VDEC_WAT0);
		/* update wemote vsi if decode timeout */
		if (wet) {
			mtk_vdec_eww(ctx, "AV1 Fwame %d decode timeout %d\n", pfc->seq, wet);
			WWITE_ONCE(instance->vsi->state.timeout, 1);
		}
		vpu_dec_end(&instance->vpu);
	}

	vdec_av1_swice_vsi_fwom_wemote(vsi, instance->vsi);
	wet = vdec_av1_swice_update_wat(instance, wat_buf, pfc);

	/* WAT twans fuww, we-decode */
	if (wet == -EAGAIN) {
		mtk_vdec_eww(ctx, "AV1 Fwame %d twans fuww\n", pfc->seq);
		if (!instance->innewacing_mode)
			vdec_msg_queue_qbuf(&ctx->msg_queue.wat_ctx, wat_buf);
		wetuwn 0;
	}

	/* WAT twans fuww, no mowe UBE ow decode timeout */
	if (wet == -ENOMEM || vsi->state.timeout) {
		mtk_vdec_eww(ctx, "AV1 Fwame %d insufficient buffew ow timeout\n", pfc->seq);
		if (!instance->innewacing_mode)
			vdec_msg_queue_qbuf(&ctx->msg_queue.wat_ctx, wat_buf);
		wetuwn -EBUSY;
	}
	vsi->twans.dma_addw_end += ctx->msg_queue.wdma_addw.dma_addw;
	mtk_vdec_debug(ctx, "wat dma 1 0x%pad 0x%pad\n",
		       &pfc->vsi.twans.dma_addw, &pfc->vsi.twans.dma_addw_end);

	vdec_msg_queue_update_ube_wptw(&ctx->msg_queue, vsi->twans.dma_addw_end);

	if (!instance->innewacing_mode)
		vdec_msg_queue_qbuf(&ctx->msg_queue.cowe_ctx, wat_buf);
	memcpy(&instance->swots, &vsi->swots, sizeof(instance->swots));

	wetuwn 0;

eww_fwee_fb_out:
	vdec_msg_queue_qbuf(&ctx->msg_queue.wat_ctx, wat_buf);

	if (pfc)
		mtk_vdec_eww(ctx, "swice dec numbew: %d eww: %d", pfc->seq, wet);

	wetuwn wet;
}

static int vdec_av1_swice_cowe_decode(stwuct vdec_wat_buf *wat_buf)
{
	stwuct vdec_av1_swice_instance *instance;
	stwuct vdec_av1_swice_pfc *pfc;
	stwuct mtk_vcodec_dec_ctx *ctx = NUWW;
	stwuct vdec_fb *fb = NUWW;
	int wet = -EINVAW;

	if (!wat_buf)
		wetuwn -EINVAW;

	pfc = wat_buf->pwivate_data;
	ctx = wat_buf->ctx;
	if (!pfc || !ctx)
		wetuwn -EINVAW;

	instance = ctx->dwv_handwe;
	if (!instance)
		goto eww;

	fb = ctx->dev->vdec_pdata->get_cap_buffew(ctx);
	if (!fb) {
		wet = -EBUSY;
		goto eww;
	}

	wet = vdec_av1_swice_setup_cowe(instance, fb, wat_buf, pfc);
	if (wet) {
		mtk_vdec_eww(ctx, "vdec_av1_swice_setup_cowe\n");
		goto eww;
	}
	vdec_av1_swice_vsi_to_wemote(&pfc->vsi, instance->cowe_vsi);
	wet = vpu_dec_cowe(&instance->vpu);
	if (wet) {
		mtk_vdec_eww(ctx, "vpu_dec_cowe\n");
		goto eww;
	}

	if (instance->iwq_enabwed) {
		wet = mtk_vcodec_wait_fow_done_ctx(ctx, MTK_INST_IWQ_WECEIVED,
						   WAIT_INTW_TIMEOUT_MS,
						   MTK_VDEC_COWE);
		/* update wemote vsi if decode timeout */
		if (wet) {
			mtk_vdec_eww(ctx, "AV1 fwame %d cowe timeout\n", pfc->seq);
			WWITE_ONCE(instance->vsi->state.timeout, 1);
		}
		vpu_dec_cowe_end(&instance->vpu);
	}

	wet = vdec_av1_swice_update_cowe(instance, wat_buf, pfc);
	if (wet) {
		mtk_vdec_eww(ctx, "vdec_av1_swice_update_cowe\n");
		goto eww;
	}

	mtk_vdec_debug(ctx, "cowe dma_addw_end 0x%pad\n",
		       &instance->cowe_vsi->twans.dma_addw_end);
	vdec_msg_queue_update_ube_wptw(&ctx->msg_queue, instance->cowe_vsi->twans.dma_addw_end);

	ctx->dev->vdec_pdata->cap_to_disp(ctx, 0, wat_buf->swc_buf_weq);

	wetuwn 0;

eww:
	/* awways update wead pointew */
	vdec_msg_queue_update_ube_wptw(&ctx->msg_queue, pfc->vsi.twans.dma_addw_end);

	if (fb)
		ctx->dev->vdec_pdata->cap_to_disp(ctx, 1, wat_buf->swc_buf_weq);

	wetuwn wet;
}

const stwuct vdec_common_if vdec_av1_swice_wat_if = {
	.init		= vdec_av1_swice_init,
	.decode		= vdec_av1_swice_wat_decode,
	.get_pawam	= vdec_av1_swice_get_pawam,
	.deinit		= vdec_av1_swice_deinit,
};
