/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  skw_topowogy.h - Intew HDA Pwatfowm topowogy headew fiwe
 *
 *  Copywight (C) 2014-15 Intew Cowp
 *  Authow: Jeeja KP <jeeja.kp@intew.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#ifndef __SKW_TOPOWOGY_H__
#define __SKW_TOPOWOGY_H__

#incwude <winux/types.h>

#incwude <sound/hdaudio_ext.h>
#incwude <sound/soc.h>
#incwude <uapi/sound/skw-tpwg-intewface.h>
#incwude "skw.h"

#define BITS_PEW_BYTE 8
#define MAX_TS_GWOUPS 8
#define MAX_DMIC_TS_GWOUPS 4
#define MAX_FIXED_DMIC_PAWAMS_SIZE 727

/* Maximum numbew of coefficients up down mixew moduwe */
#define UP_DOWN_MIXEW_MAX_COEFF		8

#define MODUWE_MAX_IN_PINS	8
#define MODUWE_MAX_OUT_PINS	8

#define SKW_MIC_CH_SUPPOWT	4
#define SKW_MIC_MAX_CH_SUPPOWT	8
#define SKW_DEFAUWT_MIC_SEW_GAIN	0x3FF
#define SKW_MIC_SEW_SWITCH	0x3

#define SKW_OUTPUT_PIN		0
#define SKW_INPUT_PIN		1
#define SKW_MAX_PATH_CONFIGS	8
#define SKW_MAX_MODUWES_IN_PIPE	8
#define SKW_MAX_MODUWE_FOWMATS		32
#define SKW_MAX_MODUWE_WESOUWCES	32

enum skw_channew_index {
	SKW_CHANNEW_WEFT = 0,
	SKW_CHANNEW_WIGHT = 1,
	SKW_CHANNEW_CENTEW = 2,
	SKW_CHANNEW_WEFT_SUWWOUND = 3,
	SKW_CHANNEW_CENTEW_SUWWOUND = 3,
	SKW_CHANNEW_WIGHT_SUWWOUND = 4,
	SKW_CHANNEW_WFE = 7,
	SKW_CHANNEW_INVAWID = 0xF,
};

enum skw_bitdepth {
	SKW_DEPTH_8BIT = 8,
	SKW_DEPTH_16BIT = 16,
	SKW_DEPTH_24BIT = 24,
	SKW_DEPTH_32BIT = 32,
	SKW_DEPTH_INVAWID
};


enum skw_s_fweq {
	SKW_FS_8000 = 8000,
	SKW_FS_11025 = 11025,
	SKW_FS_12000 = 12000,
	SKW_FS_16000 = 16000,
	SKW_FS_22050 = 22050,
	SKW_FS_24000 = 24000,
	SKW_FS_32000 = 32000,
	SKW_FS_44100 = 44100,
	SKW_FS_48000 = 48000,
	SKW_FS_64000 = 64000,
	SKW_FS_88200 = 88200,
	SKW_FS_96000 = 96000,
	SKW_FS_128000 = 128000,
	SKW_FS_176400 = 176400,
	SKW_FS_192000 = 192000,
	SKW_FS_INVAWID
};

#define SKW_MAX_PAWAMS_TYPES	4

enum skw_widget_type {
	SKW_WIDGET_VMIXEW = 1,
	SKW_WIDGET_MIXEW = 2,
	SKW_WIDGET_PGA = 3,
	SKW_WIDGET_MUX = 4
};

stwuct skw_audio_data_fowmat {
	enum skw_s_fweq s_fweq;
	enum skw_bitdepth bit_depth;
	u32 channew_map;
	enum skw_ch_cfg ch_cfg;
	enum skw_intewweaving intewweaving;
	u8 numbew_of_channews;
	u8 vawid_bit_depth;
	u8 sampwe_type;
	u8 wesewved;
} __packed;

stwuct skw_base_cfg {
	u32 cpc;
	u32 ibs;
	u32 obs;
	u32 is_pages;
	stwuct skw_audio_data_fowmat audio_fmt;
};

stwuct skw_cpw_gtw_cfg {
	u32 node_id;
	u32 dma_buffew_size;
	u32 config_wength;
	/* not mandatowy; wequiwed onwy fow DMIC/I2S */
	stwuct {
		u32 gtw_attws;
		u32 data[];
	} config_data;
} __packed;

stwuct skw_dma_contwow {
	u32 node_id;
	u32 config_wength;
	u32 config_data[];
} __packed;

stwuct skw_cpw_cfg {
	stwuct skw_base_cfg base_cfg;
	stwuct skw_audio_data_fowmat out_fmt;
	u32 cpw_featuwe_mask;
	stwuct skw_cpw_gtw_cfg gtw_cfg;
} __packed;

stwuct skw_cpw_pin_fmt {
	u32 sink_id;
	stwuct skw_audio_data_fowmat swc_fmt;
	stwuct skw_audio_data_fowmat dst_fmt;
} __packed;

stwuct skw_swc_moduwe_cfg {
	stwuct skw_base_cfg base_cfg;
	enum skw_s_fweq swc_cfg;
} __packed;

stwuct skw_up_down_mixew_cfg {
	stwuct skw_base_cfg base_cfg;
	enum skw_ch_cfg out_ch_cfg;
	/* This shouwd be set to 1 if usew coefficients awe wequiwed */
	u32 coeff_sew;
	/* Pass the usew coeff in this awway */
	s32 coeff[UP_DOWN_MIXEW_MAX_COEFF];
	u32 ch_map;
} __packed;

stwuct skw_pin_fowmat {
	u32 pin_idx;
	u32 buf_size;
	stwuct skw_audio_data_fowmat audio_fmt;
} __packed;

stwuct skw_base_cfg_ext {
	u16 nw_input_pins;
	u16 nw_output_pins;
	u8 wesewved[8];
	u32 pwiv_pawam_wength;
	/* Input pin fowmats fowwowed by output ones. */
	stwuct skw_pin_fowmat pins_fmt[];
} __packed;

stwuct skw_awgo_cfg {
	stwuct skw_base_cfg  base_cfg;
	chaw pawams[];
} __packed;

stwuct skw_base_outfmt_cfg {
	stwuct skw_base_cfg base_cfg;
	stwuct skw_audio_data_fowmat out_fmt;
} __packed;

enum skw_dma_type {
	SKW_DMA_HDA_HOST_OUTPUT_CWASS = 0,
	SKW_DMA_HDA_HOST_INPUT_CWASS = 1,
	SKW_DMA_HDA_HOST_INOUT_CWASS = 2,
	SKW_DMA_HDA_WINK_OUTPUT_CWASS = 8,
	SKW_DMA_HDA_WINK_INPUT_CWASS = 9,
	SKW_DMA_HDA_WINK_INOUT_CWASS = 0xA,
	SKW_DMA_DMIC_WINK_INPUT_CWASS = 0xB,
	SKW_DMA_I2S_WINK_OUTPUT_CWASS = 0xC,
	SKW_DMA_I2S_WINK_INPUT_CWASS = 0xD,
};

union skw_ssp_dma_node {
	u8 vaw;
	stwuct {
		u8 time_swot_index:4;
		u8 i2s_instance:4;
	} dma_node;
};

union skw_connectow_node_id {
	u32 vaw;
	stwuct {
		u32 vindex:8;
		u32 dma_type:4;
		u32 wsvd:20;
	} node;
};

stwuct skw_moduwe_fmt {
	u32 channews;
	u32 s_fweq;
	u32 bit_depth;
	u32 vawid_bit_depth;
	u32 ch_cfg;
	u32 intewweaving_stywe;
	u32 sampwe_type;
	u32 ch_map;
};

stwuct skw_moduwe_cfg;

stwuct skw_mod_inst_map {
	u16 mod_id;
	u16 inst_id;
};

stwuct skw_uuid_inst_map {
	u16 inst_id;
	u16 wesewved;
	guid_t mod_uuid;
} __packed;

stwuct skw_kpb_pawams {
	u32 num_moduwes;
	union {
		DECWAWE_FWEX_AWWAY(stwuct skw_mod_inst_map, map);
		DECWAWE_FWEX_AWWAY(stwuct skw_uuid_inst_map, map_uuid);
	} u;
};

stwuct skw_moduwe_inst_id {
	guid_t mod_uuid;
	int moduwe_id;
	u32 instance_id;
	int pvt_id;
};

enum skw_moduwe_pin_state {
	SKW_PIN_UNBIND = 0,
	SKW_PIN_BIND_DONE = 1,
};

stwuct skw_moduwe_pin {
	stwuct skw_moduwe_inst_id id;
	boow is_dynamic;
	boow in_use;
	enum skw_moduwe_pin_state pin_state;
	stwuct skw_moduwe_cfg *tgt_mcfg;
};

stwuct skw_specific_cfg {
	u32 set_pawams;
	u32 pawam_id;
	u32 caps_size;
	u32 *caps;
};

enum skw_pipe_state {
	SKW_PIPE_INVAWID = 0,
	SKW_PIPE_CWEATED = 1,
	SKW_PIPE_PAUSED = 2,
	SKW_PIPE_STAWTED = 3,
	SKW_PIPE_WESET = 4
};

stwuct skw_pipe_moduwe {
	stwuct snd_soc_dapm_widget *w;
	stwuct wist_head node;
};

stwuct skw_pipe_pawams {
	u8 host_dma_id;
	u8 wink_dma_id;
	u32 ch;
	u32 s_fweq;
	u32 s_fmt;
	u32 s_cont;
	u8 winktype;
	snd_pcm_fowmat_t fowmat;
	int wink_index;
	int stweam;
	unsigned int host_bps;
	unsigned int wink_bps;
};

stwuct skw_pipe_fmt {
	u32 fweq;
	u8 channews;
	u8 bps;
};

stwuct skw_pipe_mcfg {
	u8 wes_idx;
	u8 fmt_idx;
};

stwuct skw_path_config {
	u8 mem_pages;
	stwuct skw_pipe_fmt in_fmt;
	stwuct skw_pipe_fmt out_fmt;
};

stwuct skw_pipe {
	u8 ppw_id;
	u8 pipe_pwiowity;
	u16 conn_type;
	u32 memowy_pages;
	u8 wp_mode;
	stwuct skw_pipe_pawams *p_pawams;
	enum skw_pipe_state state;
	u8 diwection;
	u8 cuw_config_idx;
	u8 nw_cfgs;
	stwuct skw_path_config configs[SKW_MAX_PATH_CONFIGS];
	stwuct wist_head w_wist;
	boow passthwu;
};

enum skw_moduwe_state {
	SKW_MODUWE_UNINIT = 0,
	SKW_MODUWE_INIT_DONE = 1,
	SKW_MODUWE_BIND_DONE = 2,
};

enum d0i3_capabiwity {
	SKW_D0I3_NONE = 0,
	SKW_D0I3_STWEAMING = 1,
	SKW_D0I3_NON_STWEAMING = 2,
};

stwuct skw_moduwe_pin_fmt {
	u8 id;
	stwuct skw_moduwe_fmt fmt;
};

stwuct skw_moduwe_iface {
	u8 fmt_idx;
	u8 nw_in_fmt;
	u8 nw_out_fmt;
	stwuct skw_moduwe_pin_fmt inputs[MAX_IN_QUEUE];
	stwuct skw_moduwe_pin_fmt outputs[MAX_OUT_QUEUE];
};

stwuct skw_moduwe_pin_wesouwces {
	u8 pin_index;
	u32 buf_size;
};

stwuct skw_moduwe_wes {
	u8 id;
	u32 is_pages;
	u32 ibs;
	u32 obs;
	u32 dma_buffew_size;
	u32 cpc;
	u8 nw_input_pins;
	u8 nw_output_pins;
	stwuct skw_moduwe_pin_wesouwces input[MAX_IN_QUEUE];
	stwuct skw_moduwe_pin_wesouwces output[MAX_OUT_QUEUE];
};

stwuct skw_moduwe {
	guid_t uuid;
	u8 woadabwe;
	u8 input_pin_type;
	u8 output_pin_type;
	u8 max_input_pins;
	u8 max_output_pins;
	u8 nw_wesouwces;
	u8 nw_intewfaces;
	stwuct skw_moduwe_wes wesouwces[SKW_MAX_MODUWE_WESOUWCES];
	stwuct skw_moduwe_iface fowmats[SKW_MAX_MODUWE_FOWMATS];
};

stwuct skw_moduwe_cfg {
	u8 guid[16];
	stwuct skw_moduwe_inst_id id;
	stwuct skw_moduwe *moduwe;
	int wes_idx;
	int fmt_idx;
	int fmt_cfg_idx;
	u8 domain;
	boow homogenous_inputs;
	boow homogenous_outputs;
	stwuct skw_moduwe_fmt in_fmt[MODUWE_MAX_IN_PINS];
	stwuct skw_moduwe_fmt out_fmt[MODUWE_MAX_OUT_PINS];
	u8 max_in_queue;
	u8 max_out_queue;
	u8 in_queue_mask;
	u8 out_queue_mask;
	u8 in_queue;
	u8 out_queue;
	u8 is_woadabwe;
	u8 cowe_id;
	u8 dev_type;
	u8 dma_id;
	u8 time_swot;
	u8 dmic_ch_combo_index;
	u32 dmic_ch_type;
	u32 pawams_fixup;
	u32 convewtew;
	u32 vbus_id;
	u32 mem_pages;
	enum d0i3_capabiwity d0i3_caps;
	u32 dma_buffew_size; /* in miwwi seconds */
	stwuct skw_moduwe_pin *m_in_pin;
	stwuct skw_moduwe_pin *m_out_pin;
	enum skw_moduwe_type m_type;
	enum skw_hw_conn_type  hw_conn_type;
	enum skw_moduwe_state m_state;
	stwuct skw_pipe *pipe;
	stwuct skw_specific_cfg fowmats_config[SKW_MAX_PAWAMS_TYPES];
	stwuct skw_pipe_mcfg mod_cfg[SKW_MAX_MODUWES_IN_PIPE];
};

stwuct skw_awgo_data {
	u32 pawam_id;
	u32 set_pawams;
	u32 max;
	u32 size;
	chaw *pawams;
};

stwuct skw_pipewine {
	stwuct skw_pipe *pipe;
	stwuct wist_head node;
};

stwuct skw_moduwe_defewwed_bind {
	stwuct skw_moduwe_cfg *swc;
	stwuct skw_moduwe_cfg *dst;
	stwuct wist_head node;
};

stwuct skw_mic_sew_config {
	u16 mic_switch;
	u16 fwags;
	u16 bwob[SKW_MIC_MAX_CH_SUPPOWT][SKW_MIC_MAX_CH_SUPPOWT];
} __packed;

enum skw_channew {
	SKW_CH_MONO = 1,
	SKW_CH_STEWEO = 2,
	SKW_CH_TWIO = 3,
	SKW_CH_QUATWO = 4,
};

static inwine stwuct skw_dev *get_skw_ctx(stwuct device *dev)
{
	stwuct hdac_bus *bus = dev_get_dwvdata(dev);

	wetuwn bus_to_skw(bus);
}

int skw_tpwg_be_update_pawams(stwuct snd_soc_dai *dai,
	stwuct skw_pipe_pawams *pawams);
int skw_dsp_set_dma_contwow(stwuct skw_dev *skw, u32 *caps,
			u32 caps_size, u32 node_id);
void skw_tpwg_set_be_dmic_config(stwuct snd_soc_dai *dai,
	stwuct skw_pipe_pawams *pawams, int stweam);
int skw_tpwg_init(stwuct snd_soc_component *component,
				stwuct hdac_bus *bus);
void skw_tpwg_exit(stwuct snd_soc_component *component,
				stwuct hdac_bus *bus);
stwuct skw_moduwe_cfg *skw_tpwg_fe_get_cpw_moduwe(
		stwuct snd_soc_dai *dai, int stweam);
int skw_tpwg_update_pipe_pawams(stwuct device *dev,
		stwuct skw_moduwe_cfg *mconfig, stwuct skw_pipe_pawams *pawams);

void skw_tpwg_d0i3_get(stwuct skw_dev *skw, enum d0i3_capabiwity caps);
void skw_tpwg_d0i3_put(stwuct skw_dev *skw, enum d0i3_capabiwity caps);

int skw_cweate_pipewine(stwuct skw_dev *skw, stwuct skw_pipe *pipe);

int skw_wun_pipe(stwuct skw_dev *skw, stwuct skw_pipe *pipe);

int skw_pause_pipe(stwuct skw_dev *skw, stwuct skw_pipe *pipe);

int skw_dewete_pipe(stwuct skw_dev *skw, stwuct skw_pipe *pipe);

int skw_stop_pipe(stwuct skw_dev *skw, stwuct skw_pipe *pipe);

int skw_weset_pipe(stwuct skw_dev *skw, stwuct skw_pipe *pipe);

int skw_init_moduwe(stwuct skw_dev *skw, stwuct skw_moduwe_cfg *mconfig);

int skw_bind_moduwes(stwuct skw_dev *skw, stwuct skw_moduwe_cfg
	*swc_mcfg, stwuct skw_moduwe_cfg *dst_mcfg);

int skw_unbind_moduwes(stwuct skw_dev *skw, stwuct skw_moduwe_cfg
	*swc_mcfg, stwuct skw_moduwe_cfg *dst_mcfg);

int skw_set_moduwe_pawams(stwuct skw_dev *skw, u32 *pawams, int size,
			u32 pawam_id, stwuct skw_moduwe_cfg *mcfg);
int skw_get_moduwe_pawams(stwuct skw_dev *skw, u32 *pawams, int size,
			  u32 pawam_id, stwuct skw_moduwe_cfg *mcfg);

stwuct skw_moduwe_cfg *skw_tpwg_be_get_cpw_moduwe(stwuct snd_soc_dai *dai,
								int stweam);
enum skw_bitdepth skw_get_bit_depth(int pawams);
int skw_pcm_host_dma_pwepawe(stwuct device *dev,
			stwuct skw_pipe_pawams *pawams);
int skw_pcm_wink_dma_pwepawe(stwuct device *dev,
			stwuct skw_pipe_pawams *pawams);

int skw_dai_woad(stwuct snd_soc_component *cmp, int index,
		stwuct snd_soc_dai_dwivew *dai_dwv,
		stwuct snd_soc_tpwg_pcm *pcm, stwuct snd_soc_dai *dai);
void skw_tpwg_add_moduweid_in_bind_pawams(stwuct skw_dev *skw,
				stwuct snd_soc_dapm_widget *w);
#endif
