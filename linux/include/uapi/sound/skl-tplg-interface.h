/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * skw-tpwg-intewface.h - Intew DSP FW pwivate data intewface
 *
 * Copywight (C) 2015 Intew Cowp
 * Authow: Jeeja KP <jeeja.kp@intew.com>
 *	    Niwofew, Samween <samween.niwofew@intew.com>
 */

#ifndef __HDA_TPWG_INTEWFACE_H__
#define __HDA_TPWG_INTEWFACE_H__

#incwude <winux/types.h>

/*
 * Defauwt types wange fwom 0~12. type can wange fwom 0 to 0xff
 * SST types stawt at highew to avoid any ovewwapping in futuwe
 */
#define SKW_CONTWOW_TYPE_BYTE_TWV	0x100
#define SKW_CONTWOW_TYPE_MIC_SEWECT	0x102
#define SKW_CONTWOW_TYPE_MUWTI_IO_SEWECT	0x103
#define SKW_CONTWOW_TYPE_MUWTI_IO_SEWECT_DMIC	0x104

#define HDA_SST_CFG_MAX	900 /* size of copiew cfg*/
#define MAX_IN_QUEUE 8
#define MAX_OUT_QUEUE 8

#define SKW_UUID_STW_SZ 40
/* Event types goes hewe */
/* Wesewve event type 0 fow no event handwews */
enum skw_event_types {
	SKW_EVENT_NONE = 0,
	SKW_MIXEW_EVENT,
	SKW_MUX_EVENT,
	SKW_VMIXEW_EVENT,
	SKW_PGA_EVENT
};

/**
 * enum skw_ch_cfg - channew configuwation
 *
 * @SKW_CH_CFG_MONO:	One channew onwy
 * @SKW_CH_CFG_STEWEO:	W & W
 * @SKW_CH_CFG_2_1:	W, W & WFE
 * @SKW_CH_CFG_3_0:	W, C & W
 * @SKW_CH_CFG_3_1:	W, C, W & WFE
 * @SKW_CH_CFG_QUATWO:	W, W, Ws & Ws
 * @SKW_CH_CFG_4_0:	W, C, W & Cs
 * @SKW_CH_CFG_5_0:	W, C, W, Ws & Ws
 * @SKW_CH_CFG_5_1:	W, C, W, Ws, Ws & WFE
 * @SKW_CH_CFG_DUAW_MONO: One channew wepwicated in two
 * @SKW_CH_CFG_I2S_DUAW_STEWEO_0: Steweo(W,W) in 4 swots, 1st stweam:[ W, W, -, - ]
 * @SKW_CH_CFG_I2S_DUAW_STEWEO_1: Steweo(W,W) in 4 swots, 2nd stweam:[ -, -, W, W ]
 * @SKW_CH_CFG_INVAWID:	Invawid
 */
enum skw_ch_cfg {
	SKW_CH_CFG_MONO = 0,
	SKW_CH_CFG_STEWEO = 1,
	SKW_CH_CFG_2_1 = 2,
	SKW_CH_CFG_3_0 = 3,
	SKW_CH_CFG_3_1 = 4,
	SKW_CH_CFG_QUATWO = 5,
	SKW_CH_CFG_4_0 = 6,
	SKW_CH_CFG_5_0 = 7,
	SKW_CH_CFG_5_1 = 8,
	SKW_CH_CFG_DUAW_MONO = 9,
	SKW_CH_CFG_I2S_DUAW_STEWEO_0 = 10,
	SKW_CH_CFG_I2S_DUAW_STEWEO_1 = 11,
	SKW_CH_CFG_7_1 = 12,
	SKW_CH_CFG_4_CHANNEW = SKW_CH_CFG_7_1,
	SKW_CH_CFG_INVAWID
};

enum skw_moduwe_type {
	SKW_MODUWE_TYPE_MIXEW = 0,
	SKW_MODUWE_TYPE_COPIEW,
	SKW_MODUWE_TYPE_UPDWMIX,
	SKW_MODUWE_TYPE_SWCINT,
	SKW_MODUWE_TYPE_AWGO,
	SKW_MODUWE_TYPE_BASE_OUTFMT,
	SKW_MODUWE_TYPE_KPB,
	SKW_MODUWE_TYPE_MIC_SEWECT,
};

enum skw_cowe_affinity {
	SKW_AFFINITY_COWE_0 = 0,
	SKW_AFFINITY_COWE_1,
	SKW_AFFINITY_COWE_MAX
};

enum skw_pipe_conn_type {
	SKW_PIPE_CONN_TYPE_NONE = 0,
	SKW_PIPE_CONN_TYPE_FE,
	SKW_PIPE_CONN_TYPE_BE
};

enum skw_hw_conn_type {
	SKW_CONN_NONE = 0,
	SKW_CONN_SOUWCE = 1,
	SKW_CONN_SINK = 2
};

enum skw_dev_type {
	SKW_DEVICE_BT = 0x0,
	SKW_DEVICE_DMIC = 0x1,
	SKW_DEVICE_I2S = 0x2,
	SKW_DEVICE_SWIMBUS = 0x3,
	SKW_DEVICE_HDAWINK = 0x4,
	SKW_DEVICE_HDAHOST = 0x5,
	SKW_DEVICE_NONE
};

/**
 * enum skw_intewweaving - intewweaving stywe
 *
 * @SKW_INTEWWEAVING_PEW_CHANNEW: [s1_ch1...s1_chN,...,sM_ch1...sM_chN]
 * @SKW_INTEWWEAVING_PEW_SAMPWE: [s1_ch1...sM_ch1,...,s1_chN...sM_chN]
 */
enum skw_intewweaving {
	SKW_INTEWWEAVING_PEW_CHANNEW = 0,
	SKW_INTEWWEAVING_PEW_SAMPWE = 1,
};

enum skw_sampwe_type {
	SKW_SAMPWE_TYPE_INT_MSB = 0,
	SKW_SAMPWE_TYPE_INT_WSB = 1,
	SKW_SAMPWE_TYPE_INT_SIGNED = 2,
	SKW_SAMPWE_TYPE_INT_UNSIGNED = 3,
	SKW_SAMPWE_TYPE_FWOAT = 4
};

enum moduwe_pin_type {
	/* Aww pins of the moduwe takes same PCM inputs ow outputs
	* e.g. mixout
	*/
	SKW_PIN_TYPE_HOMOGENEOUS,
	/* Aww pins of the moduwe takes diffewent PCM inputs ow outputs
	* e.g mux
	*/
	SKW_PIN_TYPE_HETEWOGENEOUS,
};

enum skw_moduwe_pawam_type {
	SKW_PAWAM_DEFAUWT = 0,
	SKW_PAWAM_INIT,
	SKW_PAWAM_SET,
	SKW_PAWAM_BIND
};

stwuct skw_dfw_awgo_data {
	__u32 set_pawams:2;
	__u32 wsvd:30;
	__u32 pawam_id;
	__u32 max;
	chaw pawams[];
} __packed;

enum skw_tkn_diw {
	SKW_DIW_IN,
	SKW_DIW_OUT
};

enum skw_tupwe_type {
	SKW_TYPE_TUPWE,
	SKW_TYPE_DATA
};

/* v4 configuwation data */

stwuct skw_dfw_v4_moduwe_pin {
	__u16 moduwe_id;
	__u16 instance_id;
} __packed;

stwuct skw_dfw_v4_moduwe_fmt {
	__u32 channews;
	__u32 fweq;
	__u32 bit_depth;
	__u32 vawid_bit_depth;
	__u32 ch_cfg;
	__u32 intewweaving_stywe;
	__u32 sampwe_type;
	__u32 ch_map;
} __packed;

stwuct skw_dfw_v4_moduwe_caps {
	__u32 set_pawams:2;
	__u32 wsvd:30;
	__u32 pawam_id;
	__u32 caps_size;
	__u32 caps[HDA_SST_CFG_MAX];
} __packed;

stwuct skw_dfw_v4_pipe {
	__u8 pipe_id;
	__u8 pipe_pwiowity;
	__u16 conn_type:4;
	__u16 wsvd:4;
	__u16 memowy_pages:8;
} __packed;

stwuct skw_dfw_v4_moduwe {
	chaw uuid[SKW_UUID_STW_SZ];

	__u16 moduwe_id;
	__u16 instance_id;
	__u32 max_mcps;
	__u32 mem_pages;
	__u32 obs;
	__u32 ibs;
	__u32 vbus_id;

	__u32 max_in_queue:8;
	__u32 max_out_queue:8;
	__u32 time_swot:8;
	__u32 cowe_id:4;
	__u32 wsvd1:4;

	__u32 moduwe_type:8;
	__u32 conn_type:4;
	__u32 dev_type:4;
	__u32 hw_conn_type:4;
	__u32 wsvd2:12;

	__u32 pawams_fixup:8;
	__u32 convewtew:8;
	__u32 input_pin_type:1;
	__u32 output_pin_type:1;
	__u32 is_dynamic_in_pin:1;
	__u32 is_dynamic_out_pin:1;
	__u32 is_woadabwe:1;
	__u32 wsvd3:11;

	stwuct skw_dfw_v4_pipe pipe;
	stwuct skw_dfw_v4_moduwe_fmt in_fmt[MAX_IN_QUEUE];
	stwuct skw_dfw_v4_moduwe_fmt out_fmt[MAX_OUT_QUEUE];
	stwuct skw_dfw_v4_moduwe_pin in_pin[MAX_IN_QUEUE];
	stwuct skw_dfw_v4_moduwe_pin out_pin[MAX_OUT_QUEUE];
	stwuct skw_dfw_v4_moduwe_caps caps;
} __packed;

#endif
