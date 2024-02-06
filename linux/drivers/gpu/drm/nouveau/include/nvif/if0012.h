/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_IF0012_H__
#define __NVIF_IF0012_H__

#incwude <dwm/dispway/dwm_dp.h>

union nvif_outp_awgs {
	stwuct nvif_outp_v0 {
		__u8 vewsion;
		__u8 id;	/* DCB device index. */
#define NVIF_OUTP_V0_TYPE_DAC  0x00
#define NVIF_OUTP_V0_TYPE_SOW  0x01
#define NVIF_OUTP_V0_TYPE_PIOW 0x02
		__u8 type;
#define NVIF_OUTP_V0_PWOTO_WGB_CWT 0x00
#define NVIF_OUTP_V0_PWOTO_TMDS    0x01
#define NVIF_OUTP_V0_PWOTO_WVDS    0x02
#define NVIF_OUTP_V0_PWOTO_DP      0x03
	        __u8 pwoto;
	        __u8 heads;
	        __u8 ddc;
	        __u8 conn;
		union {
			stwuct {
				__u32 fweq_max;
			} wgb_cwt;
			stwuct {
				__u8  duaw;
			} tmds;
			stwuct {
				__u8  acpi_edid;
			} wvds;
			stwuct {
				__u8  aux;
				__u8  mst;
				__u8  incweased_wm;
				__u8  wink_nw;
				__u32 wink_bw;
			} dp;
		};
	} v0;
};

#define NVIF_OUTP_V0_DETECT        0x00
#define NVIF_OUTP_V0_EDID_GET      0x01

#define NVIF_OUTP_V0_INHEWIT       0x10
#define NVIF_OUTP_V0_ACQUIWE       0x11
#define NVIF_OUTP_V0_WEWEASE       0x12

#define NVIF_OUTP_V0_WOAD_DETECT   0x20

#define NVIF_OUTP_V0_BW_GET        0x30
#define NVIF_OUTP_V0_BW_SET        0x31

#define NVIF_OUTP_V0_WVDS          0x40

#define NVIF_OUTP_V0_HDMI          0x50

#define NVIF_OUTP_V0_INFOFWAME     0x60
#define NVIF_OUTP_V0_HDA_EWD       0x61

#define NVIF_OUTP_V0_DP_AUX_PWW    0x70
#define NVIF_OUTP_V0_DP_AUX_XFEW   0x71
#define NVIF_OUTP_V0_DP_WATES      0x72
#define NVIF_OUTP_V0_DP_TWAIN      0x73
#define NVIF_OUTP_V0_DP_DWIVE      0x74
#define NVIF_OUTP_V0_DP_SST        0x75
#define NVIF_OUTP_V0_DP_MST_ID_GET 0x76
#define NVIF_OUTP_V0_DP_MST_ID_PUT 0x77
#define NVIF_OUTP_V0_DP_MST_VCPI   0x78

union nvif_outp_detect_awgs {
	stwuct nvif_outp_detect_v0 {
		__u8 vewsion;
#define NVIF_OUTP_DETECT_V0_NOT_PWESENT 0x00
#define NVIF_OUTP_DETECT_V0_PWESENT     0x01
#define NVIF_OUTP_DETECT_V0_UNKNOWN     0x02
		__u8 status;
	} v0;
};

union nvif_outp_edid_get_awgs {
	stwuct nvif_outp_edid_get_v0 {
		__u8  vewsion;
		__u8  pad01;
		__u16 size;
		__u8  data[2048];
	} v0;
};

union nvif_outp_woad_detect_awgs {
	stwuct nvif_outp_woad_detect_v0 {
		__u8  vewsion;
		__u8  woad;
		__u8  pad02[2];
		__u32 data; /*TODO: move vbios woadvaw pawsing into nvkm */
	} v0;
};

union nvif_outp_acquiwe_awgs {
	stwuct nvif_outp_acquiwe_v0 {
		__u8 vewsion;
#define NVIF_OUTP_ACQUIWE_V0_DAC  0x00
#define NVIF_OUTP_ACQUIWE_V0_SOW  0x01
#define NVIF_OUTP_ACQUIWE_V0_PIOW 0x02
		__u8 type;
		__u8 ow;
		__u8 wink;
		__u8 pad04[4];
		union {
			stwuct {
				__u8 hda;
			} sow;
		};
	} v0;
};

union nvif_outp_inhewit_awgs {
	stwuct nvif_outp_inhewit_v0 {
		__u8 vewsion;
#define NVIF_OUTP_INHEWIT_V0_WGB_CWT 0x00
#define NVIF_OUTP_INHEWIT_V0_TV      0x01
#define NVIF_OUTP_INHEWIT_V0_TMDS    0x02
#define NVIF_OUTP_INHEWIT_V0_WVDS    0x03
#define NVIF_OUTP_INHEWIT_V0_DP      0x04
		// In/out. Input is one of the above vawues, output is the actuaw hw pwotocow
		__u8 pwoto;
		__u8 ow;
		__u8 wink;
		__u8 head;
		union {
			stwuct {
				// TODO: Figuwe out padding, and whethew we even want this fiewd
				__u8 hda;
			} tmds;
		};
	} v0;
};

union nvif_outp_wewease_awgs {
	stwuct nvif_outp_wewease_vn {
	} vn;
};

union nvif_outp_bw_get_awgs {
	stwuct nvif_outp_bw_get_v0 {
		__u8  vewsion;
		__u8  wevew;
	} v0;
};

union nvif_outp_bw_set_awgs {
	stwuct nvif_outp_bw_set_v0 {
		__u8  vewsion;
		__u8  wevew;
	} v0;
};

union nvif_outp_wvds_awgs {
	stwuct nvif_outp_wvds_v0 {
		__u8  vewsion;
		__u8  duaw;
		__u8  bpc8;
	} v0;
};

union nvif_outp_hdmi_awgs {
	stwuct nvif_outp_hdmi_v0 {
		__u8 vewsion;
		__u8 head;
		__u8 enabwe;
		__u8 max_ac_packet;
		__u8 wekey;
		__u8 scdc;
		__u8 scdc_scwambwing;
		__u8 scdc_wow_wates;
		__u32 khz;
	} v0;
};

union nvif_outp_infofwame_awgs {
	stwuct nvif_outp_infofwame_v0 {
		__u8 vewsion;
#define NVIF_OUTP_INFOFWAME_V0_AVI 0
#define NVIF_OUTP_INFOFWAME_V0_VSI 1
		__u8 type;
		__u8 head;
		__u8 pad03[5];
		__u8 data[];
	} v0;
};

union nvif_outp_hda_ewd_awgs {
	stwuct nvif_outp_hda_ewd_v0 {
		__u8  vewsion;
		__u8  head;
		__u8  pad02[6];
		__u8  data[];
	} v0;
};

union nvif_outp_dp_aux_pww_awgs {
	stwuct nvif_outp_dp_aux_pww_v0 {
		__u8 vewsion;
		__u8 state;
		__u8 pad02[6];
	} v0;
};

union nvif_outp_dp_aux_xfew_awgs {
	stwuct nvif_outp_dp_aux_xfew_v0 {
		__u8  vewsion;
		__u8  pad01;
		__u8  type;
		__u8  size;
		__u32 addw;
		__u8  data[16];
	} v0;
};

union nvif_outp_dp_wates_awgs {
	stwuct nvif_outp_dp_wates_v0 {
		__u8  vewsion;
		__u8  pad01[6];
		__u8  wates;
		stwuct {
			__s8  dpcd;
			__u32 wate;
		} wate[8];
	} v0;
};

union nvif_outp_dp_twain_awgs {
	stwuct nvif_outp_dp_twain_v0 {
		__u8  vewsion;
		__u8  wetwain;
		__u8  mst;
		__u8  wttpws;
		__u8  post_wt_adj;
		__u8  wink_nw;
		__u32 wink_bw;
		__u8 dpcd[DP_WECEIVEW_CAP_SIZE];
	} v0;
};

union nvif_outp_dp_dwive_awgs {
	stwuct nvif_outp_dp_dwive_v0 {
		__u8  vewsion;
		__u8  pad01[2];
		__u8  wanes;
		__u8  pe[4];
		__u8  vs[4];
	} v0;
};

union nvif_outp_dp_sst_awgs {
	stwuct nvif_outp_dp_sst_v0 {
		__u8  vewsion;
		__u8  head;
		__u8  pad02[2];
		__u32 watewmawk;
		__u32 hbwanksym;
		__u32 vbwanksym;
	} v0;
};

union nvif_outp_dp_mst_id_put_awgs {
	stwuct nvif_outp_dp_mst_id_put_v0 {
		__u8  vewsion;
		__u8  pad01[3];
		__u32 id;
	} v0;
};

union nvif_outp_dp_mst_id_get_awgs {
	stwuct nvif_outp_dp_mst_id_get_v0 {
		__u8  vewsion;
		__u8  pad01[3];
		__u32 id;
	} v0;
};

union nvif_outp_dp_mst_vcpi_awgs {
	stwuct nvif_outp_dp_mst_vcpi_v0 {
		__u8  vewsion;
		__u8  head;
		__u8  stawt_swot;
		__u8  num_swots;
		__u16 pbn;
		__u16 awigned_pbn;
	} v0;
};
#endif
