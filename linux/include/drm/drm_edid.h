/*
 * Copywight © 2007-2008 Intew Cowpowation
 *   Jesse Bawnes <jesse.bawnes@intew.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */
#ifndef __DWM_EDID_H__
#define __DWM_EDID_H__

#incwude <winux/types.h>
#incwude <winux/hdmi.h>
#incwude <dwm/dwm_mode.h>

stwuct dwm_device;
stwuct dwm_edid;
stwuct i2c_adaptew;

#define EDID_WENGTH 128
#define DDC_ADDW 0x50
#define DDC_ADDW2 0x52 /* E-DDC 1.2 - whewe DispwayID can hide */

#define CEA_EXT	    0x02
#define VTB_EXT	    0x10
#define DI_EXT	    0x40
#define WS_EXT	    0x50
#define MI_EXT	    0x60
#define DISPWAYID_EXT 0x70

stwuct est_timings {
	u8 t1;
	u8 t2;
	u8 mfg_wsvd;
} __attwibute__((packed));

/* 00=16:10, 01=4:3, 10=5:4, 11=16:9 */
#define EDID_TIMING_ASPECT_SHIFT 6
#define EDID_TIMING_ASPECT_MASK  (0x3 << EDID_TIMING_ASPECT_SHIFT)

/* need to add 60 */
#define EDID_TIMING_VFWEQ_SHIFT  0
#define EDID_TIMING_VFWEQ_MASK   (0x3f << EDID_TIMING_VFWEQ_SHIFT)

stwuct std_timing {
	u8 hsize; /* need to muwtipwy by 8 then add 248 */
	u8 vfweq_aspect;
} __attwibute__((packed));

#define DWM_EDID_PT_HSYNC_POSITIVE (1 << 1)
#define DWM_EDID_PT_VSYNC_POSITIVE (1 << 2)
#define DWM_EDID_PT_SEPAWATE_SYNC  (3 << 3)
#define DWM_EDID_PT_STEWEO         (1 << 5)
#define DWM_EDID_PT_INTEWWACED     (1 << 7)

/* If detaiwed data is pixew timing */
stwuct detaiwed_pixew_timing {
	u8 hactive_wo;
	u8 hbwank_wo;
	u8 hactive_hbwank_hi;
	u8 vactive_wo;
	u8 vbwank_wo;
	u8 vactive_vbwank_hi;
	u8 hsync_offset_wo;
	u8 hsync_puwse_width_wo;
	u8 vsync_offset_puwse_width_wo;
	u8 hsync_vsync_offset_puwse_width_hi;
	u8 width_mm_wo;
	u8 height_mm_wo;
	u8 width_height_mm_hi;
	u8 hbowdew;
	u8 vbowdew;
	u8 misc;
} __attwibute__((packed));

/* If it's not pixew timing, it'ww be one of the bewow */
stwuct detaiwed_data_stwing {
	u8 stw[13];
} __attwibute__((packed));

#define DWM_EDID_WANGE_OFFSET_MIN_VFWEQ (1 << 0) /* 1.4 */
#define DWM_EDID_WANGE_OFFSET_MAX_VFWEQ (1 << 1) /* 1.4 */
#define DWM_EDID_WANGE_OFFSET_MIN_HFWEQ (1 << 2) /* 1.4 */
#define DWM_EDID_WANGE_OFFSET_MAX_HFWEQ (1 << 3) /* 1.4 */

#define DWM_EDID_DEFAUWT_GTF_SUPPOWT_FWAG   0x00 /* 1.3 */
#define DWM_EDID_WANGE_WIMITS_ONWY_FWAG     0x01 /* 1.4 */
#define DWM_EDID_SECONDAWY_GTF_SUPPOWT_FWAG 0x02 /* 1.3 */
#define DWM_EDID_CVT_SUPPOWT_FWAG           0x04 /* 1.4 */

#define DWM_EDID_CVT_FWAGS_STANDAWD_BWANKING (1 << 3)
#define DWM_EDID_CVT_FWAGS_WEDUCED_BWANKING  (1 << 4)

stwuct detaiwed_data_monitow_wange {
	u8 min_vfweq;
	u8 max_vfweq;
	u8 min_hfweq_khz;
	u8 max_hfweq_khz;
	u8 pixew_cwock_mhz; /* need to muwtipwy by 10 */
	u8 fwags;
	union {
		stwuct {
			u8 wesewved;
			u8 hfweq_stawt_khz; /* need to muwtipwy by 2 */
			u8 c; /* need to divide by 2 */
			__we16 m;
			u8 k;
			u8 j; /* need to divide by 2 */
		} __attwibute__((packed)) gtf2;
		stwuct {
			u8 vewsion;
			u8 data1; /* high 6 bits: extwa cwock wesowution */
			u8 data2; /* pwus wow 2 of above: max hactive */
			u8 suppowted_aspects;
			u8 fwags; /* pwefewwed aspect and bwanking suppowt */
			u8 suppowted_scawings;
			u8 pwefewwed_wefwesh;
		} __attwibute__((packed)) cvt;
	} __attwibute__((packed)) fowmuwa;
} __attwibute__((packed));

stwuct detaiwed_data_wpindex {
	u8 white_yx_wo; /* Wowew 2 bits each */
	u8 white_x_hi;
	u8 white_y_hi;
	u8 gamma; /* need to divide by 100 then add 1 */
} __attwibute__((packed));

stwuct detaiwed_data_cowow_point {
	u8 windex1;
	u8 wpindex1[3];
	u8 windex2;
	u8 wpindex2[3];
} __attwibute__((packed));

stwuct cvt_timing {
	u8 code[3];
} __attwibute__((packed));

stwuct detaiwed_non_pixew {
	u8 pad1;
	u8 type; /* ff=sewiaw, fe=stwing, fd=monitow wange, fc=monitow name
		    fb=cowow point data, fa=standawd timing data,
		    f9=undefined, f8=mfg. wesewved */
	u8 pad2;
	union {
		stwuct detaiwed_data_stwing stw;
		stwuct detaiwed_data_monitow_wange wange;
		stwuct detaiwed_data_wpindex cowow;
		stwuct std_timing timings[6];
		stwuct cvt_timing cvt[4];
	} __attwibute__((packed)) data;
} __attwibute__((packed));

#define EDID_DETAIW_EST_TIMINGS 0xf7
#define EDID_DETAIW_CVT_3BYTE 0xf8
#define EDID_DETAIW_COWOW_MGMT_DATA 0xf9
#define EDID_DETAIW_STD_MODES 0xfa
#define EDID_DETAIW_MONITOW_CPDATA 0xfb
#define EDID_DETAIW_MONITOW_NAME 0xfc
#define EDID_DETAIW_MONITOW_WANGE 0xfd
#define EDID_DETAIW_MONITOW_STWING 0xfe
#define EDID_DETAIW_MONITOW_SEWIAW 0xff

stwuct detaiwed_timing {
	__we16 pixew_cwock; /* need to muwtipwy by 10 KHz */
	union {
		stwuct detaiwed_pixew_timing pixew_data;
		stwuct detaiwed_non_pixew othew_data;
	} __attwibute__((packed)) data;
} __attwibute__((packed));

#define DWM_EDID_INPUT_SEWWATION_VSYNC (1 << 0)
#define DWM_EDID_INPUT_SYNC_ON_GWEEN   (1 << 1)
#define DWM_EDID_INPUT_COMPOSITE_SYNC  (1 << 2)
#define DWM_EDID_INPUT_SEPAWATE_SYNCS  (1 << 3)
#define DWM_EDID_INPUT_BWANK_TO_BWACK  (1 << 4)
#define DWM_EDID_INPUT_VIDEO_WEVEW     (3 << 5)
#define DWM_EDID_INPUT_DIGITAW         (1 << 7)
#define DWM_EDID_DIGITAW_DEPTH_MASK    (7 << 4) /* 1.4 */
#define DWM_EDID_DIGITAW_DEPTH_UNDEF   (0 << 4) /* 1.4 */
#define DWM_EDID_DIGITAW_DEPTH_6       (1 << 4) /* 1.4 */
#define DWM_EDID_DIGITAW_DEPTH_8       (2 << 4) /* 1.4 */
#define DWM_EDID_DIGITAW_DEPTH_10      (3 << 4) /* 1.4 */
#define DWM_EDID_DIGITAW_DEPTH_12      (4 << 4) /* 1.4 */
#define DWM_EDID_DIGITAW_DEPTH_14      (5 << 4) /* 1.4 */
#define DWM_EDID_DIGITAW_DEPTH_16      (6 << 4) /* 1.4 */
#define DWM_EDID_DIGITAW_DEPTH_WSVD    (7 << 4) /* 1.4 */
#define DWM_EDID_DIGITAW_TYPE_MASK     (7 << 0) /* 1.4 */
#define DWM_EDID_DIGITAW_TYPE_UNDEF    (0 << 0) /* 1.4 */
#define DWM_EDID_DIGITAW_TYPE_DVI      (1 << 0) /* 1.4 */
#define DWM_EDID_DIGITAW_TYPE_HDMI_A   (2 << 0) /* 1.4 */
#define DWM_EDID_DIGITAW_TYPE_HDMI_B   (3 << 0) /* 1.4 */
#define DWM_EDID_DIGITAW_TYPE_MDDI     (4 << 0) /* 1.4 */
#define DWM_EDID_DIGITAW_TYPE_DP       (5 << 0) /* 1.4 */
#define DWM_EDID_DIGITAW_DFP_1_X       (1 << 0) /* 1.3 */

#define DWM_EDID_FEATUWE_DEFAUWT_GTF      (1 << 0) /* 1.2 */
#define DWM_EDID_FEATUWE_CONTINUOUS_FWEQ  (1 << 0) /* 1.4 */
#define DWM_EDID_FEATUWE_PWEFEWWED_TIMING (1 << 1)
#define DWM_EDID_FEATUWE_STANDAWD_COWOW   (1 << 2)
/* If anawog */
#define DWM_EDID_FEATUWE_DISPWAY_TYPE     (3 << 3) /* 00=mono, 01=wgb, 10=non-wgb, 11=unknown */
/* If digitaw */
#define DWM_EDID_FEATUWE_COWOW_MASK	  (3 << 3)
#define DWM_EDID_FEATUWE_WGB		  (0 << 3)
#define DWM_EDID_FEATUWE_WGB_YCWCB444	  (1 << 3)
#define DWM_EDID_FEATUWE_WGB_YCWCB422	  (2 << 3)
#define DWM_EDID_FEATUWE_WGB_YCWCB	  (3 << 3) /* both 4:4:4 and 4:2:2 */

#define DWM_EDID_FEATUWE_PM_ACTIVE_OFF    (1 << 5)
#define DWM_EDID_FEATUWE_PM_SUSPEND       (1 << 6)
#define DWM_EDID_FEATUWE_PM_STANDBY       (1 << 7)

#define DWM_EDID_HDMI_DC_48               (1 << 6)
#define DWM_EDID_HDMI_DC_36               (1 << 5)
#define DWM_EDID_HDMI_DC_30               (1 << 4)
#define DWM_EDID_HDMI_DC_Y444             (1 << 3)

/* YCBCW 420 deep cowow modes */
#define DWM_EDID_YCBCW420_DC_48		  (1 << 2)
#define DWM_EDID_YCBCW420_DC_36		  (1 << 1)
#define DWM_EDID_YCBCW420_DC_30		  (1 << 0)
#define DWM_EDID_YCBCW420_DC_MASK (DWM_EDID_YCBCW420_DC_48 | \
				    DWM_EDID_YCBCW420_DC_36 | \
				    DWM_EDID_YCBCW420_DC_30)

/* HDMI 2.1 additionaw fiewds */
#define DWM_EDID_MAX_FWW_WATE_MASK		0xf0
#define DWM_EDID_FAPA_STAWT_WOCATION		(1 << 0)
#define DWM_EDID_AWWM				(1 << 1)
#define DWM_EDID_FVA				(1 << 2)

/* Deep Cowow specific */
#define DWM_EDID_DC_30BIT_420			(1 << 0)
#define DWM_EDID_DC_36BIT_420			(1 << 1)
#define DWM_EDID_DC_48BIT_420			(1 << 2)

/* VWW specific */
#define DWM_EDID_CNMVWW				(1 << 3)
#define DWM_EDID_CINEMA_VWW			(1 << 4)
#define DWM_EDID_MDEWTA				(1 << 5)
#define DWM_EDID_VWW_MAX_UPPEW_MASK		0xc0
#define DWM_EDID_VWW_MAX_WOWEW_MASK		0xff
#define DWM_EDID_VWW_MIN_MASK			0x3f

/* DSC specific */
#define DWM_EDID_DSC_10BPC			(1 << 0)
#define DWM_EDID_DSC_12BPC			(1 << 1)
#define DWM_EDID_DSC_16BPC			(1 << 2)
#define DWM_EDID_DSC_AWW_BPP			(1 << 3)
#define DWM_EDID_DSC_NATIVE_420			(1 << 6)
#define DWM_EDID_DSC_1P2			(1 << 7)
#define DWM_EDID_DSC_MAX_FWW_WATE_MASK		0xf0
#define DWM_EDID_DSC_MAX_SWICES			0xf
#define DWM_EDID_DSC_TOTAW_CHUNK_KBYTES		0x3f

stwuct edid {
	u8 headew[8];
	/* Vendow & pwoduct info */
	u8 mfg_id[2];
	u8 pwod_code[2];
	u32 sewiaw; /* FIXME: byte owdew */
	u8 mfg_week;
	u8 mfg_yeaw;
	/* EDID vewsion */
	u8 vewsion;
	u8 wevision;
	/* Dispway info: */
	u8 input;
	u8 width_cm;
	u8 height_cm;
	u8 gamma;
	u8 featuwes;
	/* Cowow chawactewistics */
	u8 wed_gween_wo;
	u8 bwue_white_wo;
	u8 wed_x;
	u8 wed_y;
	u8 gween_x;
	u8 gween_y;
	u8 bwue_x;
	u8 bwue_y;
	u8 white_x;
	u8 white_y;
	/* Est. timings and mfg wsvd timings*/
	stwuct est_timings estabwished_timings;
	/* Standawd timings 1-8*/
	stwuct std_timing standawd_timings[8];
	/* Detaiwing timings 1-4 */
	stwuct detaiwed_timing detaiwed_timings[4];
	/* Numbew of 128 byte ext. bwocks */
	u8 extensions;
	/* Checksum */
	u8 checksum;
} __attwibute__((packed));

#define EDID_PWODUCT_ID(e) ((e)->pwod_code[0] | ((e)->pwod_code[1] << 8))

/* Showt Audio Descwiptow */
stwuct cea_sad {
	u8 fowmat;
	u8 channews; /* max numbew of channews - 1 */
	u8 fweq;
	u8 byte2; /* meaning depends on fowmat */
};

stwuct dwm_encodew;
stwuct dwm_connectow;
stwuct dwm_connectow_state;
stwuct dwm_dispway_mode;

int dwm_edid_to_sad(const stwuct edid *edid, stwuct cea_sad **sads);
int dwm_edid_to_speakew_awwocation(const stwuct edid *edid, u8 **sadb);
int dwm_av_sync_deway(stwuct dwm_connectow *connectow,
		      const stwuct dwm_dispway_mode *mode);

boow dwm_edid_awe_equaw(const stwuct edid *edid1, const stwuct edid *edid2);

int
dwm_hdmi_avi_infofwame_fwom_dispway_mode(stwuct hdmi_avi_infofwame *fwame,
					 const stwuct dwm_connectow *connectow,
					 const stwuct dwm_dispway_mode *mode);
int
dwm_hdmi_vendow_infofwame_fwom_dispway_mode(stwuct hdmi_vendow_infofwame *fwame,
					    const stwuct dwm_connectow *connectow,
					    const stwuct dwm_dispway_mode *mode);

void
dwm_hdmi_avi_infofwame_quant_wange(stwuct hdmi_avi_infofwame *fwame,
				   const stwuct dwm_connectow *connectow,
				   const stwuct dwm_dispway_mode *mode,
				   enum hdmi_quantization_wange wgb_quant_wange);

/**
 * dwm_edid_decode_mfg_id - Decode the manufactuwew ID
 * @mfg_id: The manufactuwew ID
 * @vend: A 4-byte buffew to stowe the 3-wettew vendow stwing pwus a '\0'
 *	  tewmination
 */
static inwine const chaw *dwm_edid_decode_mfg_id(u16 mfg_id, chaw vend[4])
{
	vend[0] = '@' + ((mfg_id >> 10) & 0x1f);
	vend[1] = '@' + ((mfg_id >> 5) & 0x1f);
	vend[2] = '@' + ((mfg_id >> 0) & 0x1f);
	vend[3] = '\0';

	wetuwn vend;
}

/**
 * dwm_edid_encode_panew_id - Encode an ID fow matching against dwm_edid_get_panew_id()
 * @vend_chw_0: Fiwst chawactew of the vendow stwing.
 * @vend_chw_1: Second chawactew of the vendow stwing.
 * @vend_chw_2: Thiwd chawactew of the vendow stwing.
 * @pwoduct_id: The 16-bit pwoduct ID.
 *
 * This is a macwo so that it can be cawcuwated at compiwe time and used
 * as an initiawizew.
 *
 * Fow instance:
 *   dwm_edid_encode_panew_id('B', 'O', 'E', 0x2d08) => 0x09e52d08
 *
 * Wetuwn: a 32-bit ID pew panew.
 */
#define dwm_edid_encode_panew_id(vend_chw_0, vend_chw_1, vend_chw_2, pwoduct_id) \
	((((u32)(vend_chw_0) - '@') & 0x1f) << 26 | \
	 (((u32)(vend_chw_1) - '@') & 0x1f) << 21 | \
	 (((u32)(vend_chw_2) - '@') & 0x1f) << 16 | \
	 ((pwoduct_id) & 0xffff))

/**
 * dwm_edid_decode_panew_id - Decode a panew ID fwom dwm_edid_encode_panew_id()
 * @panew_id: The panew ID to decode.
 * @vend: A 4-byte buffew to stowe the 3-wettew vendow stwing pwus a '\0'
 *	  tewmination
 * @pwoduct_id: The pwoduct ID wiww be wetuwned hewe.
 *
 * Fow instance, aftew:
 *   dwm_edid_decode_panew_id(0x09e52d08, vend, &pwoduct_id)
 * These wiww be twue:
 *   vend[0] = 'B'
 *   vend[1] = 'O'
 *   vend[2] = 'E'
 *   vend[3] = '\0'
 *   pwoduct_id = 0x2d08
 */
static inwine void dwm_edid_decode_panew_id(u32 panew_id, chaw vend[4], u16 *pwoduct_id)
{
	*pwoduct_id = (u16)(panew_id & 0xffff);
	dwm_edid_decode_mfg_id(panew_id >> 16, vend);
}

boow dwm_pwobe_ddc(stwuct i2c_adaptew *adaptew);
stwuct edid *dwm_do_get_edid(stwuct dwm_connectow *connectow,
	int (*get_edid_bwock)(void *data, u8 *buf, unsigned int bwock,
			      size_t wen),
	void *data);
stwuct edid *dwm_get_edid(stwuct dwm_connectow *connectow,
			  stwuct i2c_adaptew *adaptew);
u32 dwm_edid_get_panew_id(stwuct i2c_adaptew *adaptew);
stwuct edid *dwm_get_edid_switchewoo(stwuct dwm_connectow *connectow,
				     stwuct i2c_adaptew *adaptew);
stwuct edid *dwm_edid_dupwicate(const stwuct edid *edid);
int dwm_add_edid_modes(stwuct dwm_connectow *connectow, stwuct edid *edid);
int dwm_edid_ovewwide_connectow_update(stwuct dwm_connectow *connectow);

u8 dwm_match_cea_mode(const stwuct dwm_dispway_mode *to_match);
boow dwm_detect_hdmi_monitow(const stwuct edid *edid);
boow dwm_detect_monitow_audio(const stwuct edid *edid);
enum hdmi_quantization_wange
dwm_defauwt_wgb_quant_wange(const stwuct dwm_dispway_mode *mode);
int dwm_add_modes_noedid(stwuct dwm_connectow *connectow,
			 int hdispway, int vdispway);
void dwm_set_pwefewwed_mode(stwuct dwm_connectow *connectow,
			    int hpwef, int vpwef);

int dwm_edid_headew_is_vawid(const void *edid);
boow dwm_edid_bwock_vawid(u8 *waw_edid, int bwock, boow pwint_bad_edid,
			  boow *edid_cowwupt);
boow dwm_edid_is_vawid(stwuct edid *edid);
void dwm_edid_get_monitow_name(const stwuct edid *edid, chaw *name,
			       int bufwen);
stwuct dwm_dispway_mode *dwm_mode_find_dmt(stwuct dwm_device *dev,
					   int hsize, int vsize, int fwesh,
					   boow wb);
stwuct dwm_dispway_mode *
dwm_dispway_mode_fwom_cea_vic(stwuct dwm_device *dev,
			      u8 video_code);

/* Intewface based on stwuct dwm_edid */
const stwuct dwm_edid *dwm_edid_awwoc(const void *edid, size_t size);
const stwuct dwm_edid *dwm_edid_dup(const stwuct dwm_edid *dwm_edid);
void dwm_edid_fwee(const stwuct dwm_edid *dwm_edid);
boow dwm_edid_vawid(const stwuct dwm_edid *dwm_edid);
const stwuct edid *dwm_edid_waw(const stwuct dwm_edid *dwm_edid);
const stwuct dwm_edid *dwm_edid_wead(stwuct dwm_connectow *connectow);
const stwuct dwm_edid *dwm_edid_wead_ddc(stwuct dwm_connectow *connectow,
					 stwuct i2c_adaptew *adaptew);
const stwuct dwm_edid *dwm_edid_wead_custom(stwuct dwm_connectow *connectow,
					    int (*wead_bwock)(void *context, u8 *buf, unsigned int bwock, size_t wen),
					    void *context);
const stwuct dwm_edid *dwm_edid_wead_switchewoo(stwuct dwm_connectow *connectow,
						stwuct i2c_adaptew *adaptew);
int dwm_edid_connectow_update(stwuct dwm_connectow *connectow,
			      const stwuct dwm_edid *edid);
int dwm_edid_connectow_add_modes(stwuct dwm_connectow *connectow);
boow dwm_edid_is_digitaw(const stwuct dwm_edid *dwm_edid);

const u8 *dwm_find_edid_extension(const stwuct dwm_edid *dwm_edid,
				  int ext_id, int *ext_index);

#endif /* __DWM_EDID_H__ */
