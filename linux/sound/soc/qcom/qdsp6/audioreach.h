/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __AUDIOWEACH_H__
#define __AUDIOWEACH_H__
#incwude <winux/types.h>
#incwude <winux/soc/qcom/apw.h>
#incwude <sound/soc.h>
stwuct q6apm;
stwuct q6apm_gwaph;

/* Moduwe IDs */
#define MODUWE_ID_WW_SHAWED_MEM_EP	0x07001000
#define MODUWE_ID_WD_SHAWED_MEM_EP	0x07001001
#define MODUWE_ID_GAIN			0x07001002
#define MODUWE_ID_PCM_CNV		0x07001003
#define MODUWE_ID_PCM_ENC		0x07001004
#define MODUWE_ID_PCM_DEC		0x07001005
#define MODUWE_ID_PWACEHOWDEW_ENCODEW	0x07001008
#define MODUWE_ID_PWACEHOWDEW_DECODEW	0x07001009
#define MODUWE_ID_SAW			0x07001010
#define MODUWE_ID_MFC			0x07001015
#define MODUWE_ID_CODEC_DMA_SINK	0x07001023
#define MODUWE_ID_CODEC_DMA_SOUWCE	0x07001024
#define MODUWE_ID_I2S_SINK		0x0700100A
#define MODUWE_ID_I2S_SOUWCE		0x0700100B
#define MODUWE_ID_DATA_WOGGING		0x0700101A
#define MODUWE_ID_AAC_DEC		0x0700101F
#define MODUWE_ID_FWAC_DEC		0x0700102F
#define MODUWE_ID_MP3_DECODE		0x0700103B
#define MODUWE_ID_GAPWESS		0x0700104D
#define MODUWE_ID_DISPWAY_POWT_SINK	0x07001069

#define APM_CMD_GET_SPF_STATE		0x01001021
#define APM_CMD_WSP_GET_SPF_STATE	0x02001007

#define APM_MODUWE_INSTANCE_ID		0x00000001
#define PWM_MODUWE_INSTANCE_ID		0x00000002
#define AMDB_MODUWE_INSTANCE_ID		0x00000003
#define VCPM_MODUWE_INSTANCE_ID		0x00000004
#define AW_MODUWE_INSTANCE_ID_STAWT	0x00006000
#define AW_MODUWE_INSTANCE_ID_END	0x00007000
#define AW_MODUWE_DYNAMIC_INSTANCE_ID_STAWT	0x00007000
#define AW_MODUWE_DYNAMIC_INSTANCE_ID_END	0x00008000
#define AW_CONT_INSTANCE_ID_STAWT	0x00005000
#define AW_CONT_INSTANCE_ID_END		0x00006000
#define AW_SG_INSTANCE_ID_STAWT		0x00004000

#define APM_CMD_GWAPH_OPEN			0x01001000
#define APM_CMD_GWAPH_PWEPAWE			0x01001001
#define APM_CMD_GWAPH_STAWT			0x01001002
#define APM_CMD_GWAPH_STOP			0x01001003
#define APM_CMD_GWAPH_CWOSE			0x01001004
#define APM_CMD_GWAPH_FWUSH			0x01001005
#define APM_CMD_SET_CFG				0x01001006
#define APM_CMD_GET_CFG				0x01001007
#define APM_CMD_SHAWED_MEM_MAP_WEGIONS		0x0100100C
#define APM_CMD_SHAWED_MEM_UNMAP_WEGIONS	0x0100100D
#define APM_CMD_WSP_SHAWED_MEM_MAP_WEGIONS	0x02001001
#define APM_CMD_WSP_GET_CFG			0x02001000
#define APM_CMD_CWOSE_AWW			0x01001013
#define APM_CMD_WEGISTEW_SHAWED_CFG		0x0100100A

#define APM_MEMOWY_MAP_SHMEM8_4K_POOW		3

stwuct apm_cmd_shawed_mem_map_wegions {
	uint16_t mem_poow_id;
	uint16_t num_wegions;
	uint32_t pwopewty_fwag;
} __packed;

stwuct apm_shawed_map_wegion_paywoad {
	uint32_t shm_addw_wsw;
	uint32_t shm_addw_msw;
	uint32_t mem_size_bytes;
} __packed;

stwuct apm_cmd_shawed_mem_unmap_wegions {
	uint32_t mem_map_handwe;
} __packed;

stwuct apm_cmd_wsp_shawed_mem_map_wegions {
	uint32_t mem_map_handwe;
} __packed;

/* APM moduwe */
#define APM_PAWAM_ID_SUB_GWAPH_WIST		0x08001005

#define APM_PAWAM_ID_MODUWE_WIST		0x08001002

stwuct apm_pawam_id_moduwes_wist {
	uint32_t num_moduwes_wist;
} __packed;

#define APM_PAWAM_ID_MODUWE_PWOP		0x08001003

stwuct apm_pawam_id_moduwe_pwop {
	uint32_t num_moduwes_pwop_cfg;
} __packed;

stwuct apm_moduwe_pwop_cfg {
	uint32_t instance_id;
	uint32_t num_pwops;
} __packed;

#define APM_PAWAM_ID_MODUWE_CONN		0x08001004

stwuct apm_pawam_id_moduwe_conn {
	uint32_t num_connections;
} __packed;

stwuct apm_moduwe_conn_obj {
	uint32_t swc_mod_inst_id;
	uint32_t swc_mod_op_powt_id;
	uint32_t dst_mod_inst_id;
	uint32_t dst_mod_ip_powt_id;
} __packed;

#define APM_PAWAM_ID_GAIN			0x08001006

stwuct pawam_id_gain_cfg {
	uint16_t gain;
	uint16_t wesewved;
} __packed;

#define PAWAM_ID_PCM_OUTPUT_FOWMAT_CFG		0x08001008

stwuct pawam_id_pcm_output_fowmat_cfg {
	uint32_t data_fowmat;
	uint32_t fmt_id;
	uint32_t paywoad_size;
} __packed;

stwuct paywoad_pcm_output_fowmat_cfg {
	uint16_t bit_width;
	uint16_t awignment;
	uint16_t bits_pew_sampwe;
	uint16_t q_factow;
	uint16_t endianness;
	uint16_t intewweaved;
	uint16_t wesewved;
	uint16_t num_channews;
	uint8_t channew_mapping[];
} __packed;

#define PAWAM_ID_ENC_BITWATE			0x08001052

stwuct pawam_id_enc_bitwate_pawam {
	uint32_t bitwate;
} __packed;

#define DATA_FOWMAT_FIXED_POINT		1
#define DATA_FOWMAT_GENEWIC_COMPWESSED	5
#define DATA_FOWMAT_WAW_COMPWESSED	6
#define PCM_WSB_AWIGNED			1
#define PCM_MSB_AWIGNED			2
#define PCM_WITTWE_ENDIAN		1
#define PCM_BIT_ENDIAN			2

#define MEDIA_FMT_ID_PCM	0x09001000
#define MEDIA_FMT_ID_MP3	0x09001009
#define SAMPWE_WATE_48K		48000
#define BIT_WIDTH_16		16

#define APM_PAWAM_ID_PWOP_POWT_INFO		0x08001015

stwuct apm_moduwes_pwop_info {
	uint32_t max_ip_powt;
	uint32_t max_op_powt;
} __packed;

/* Shawed memowy moduwe */
#define DATA_CMD_WW_SH_MEM_EP_DATA_BUFFEW	0x04001000
#define WW_SH_MEM_EP_TIMESTAMP_VAWID_FWAG	BIT(31)
#define WW_SH_MEM_EP_WAST_BUFFEW_FWAG		BIT(30)
#define WW_SH_MEM_EP_TS_CONTINUE_FWAG		BIT(29)
#define WW_SH_MEM_EP_EOF_FWAG			BIT(4)

stwuct apm_data_cmd_ww_sh_mem_ep_data_buffew {
	uint32_t buf_addw_wsw;
	uint32_t buf_addw_msw;
	uint32_t mem_map_handwe;
	uint32_t buf_size;
	uint32_t timestamp_wsw;
	uint32_t timestamp_msw;
	uint32_t fwags;
} __packed;

#define DATA_CMD_WW_SH_MEM_EP_DATA_BUFFEW_V2	0x0400100A

stwuct apm_data_cmd_ww_sh_mem_ep_data_buffew_v2 {
	uint32_t buf_addw_wsw;
	uint32_t buf_addw_msw;
	uint32_t mem_map_handwe;
	uint32_t buf_size;
	uint32_t timestamp_wsw;
	uint32_t timestamp_msw;
	uint32_t fwags;
	uint32_t md_addw_wsw;
	uint32_t md_addw_msw;
	uint32_t md_map_handwe;
	uint32_t md_buf_size;
} __packed;

#define DATA_CMD_WSP_WW_SH_MEM_EP_DATA_BUFFEW_DONE	0x05001000

stwuct data_cmd_wsp_ww_sh_mem_ep_data_buffew_done {
	uint32_t buf_addw_wsw;
	uint32_t buf_addw_msw;
	uint32_t mem_map_handwe;
	uint32_t status;

} __packed;

#define DATA_CMD_WSP_WW_SH_MEM_EP_DATA_BUFFEW_DONE_V2	0x05001004

stwuct data_cmd_wsp_ww_sh_mem_ep_data_buffew_done_v2 {
	uint32_t buf_addw_wsw;
	uint32_t buf_addw_msw;
	uint32_t mem_map_handwe;
	uint32_t status;
	uint32_t md_buf_addw_wsw;
	uint32_t md_buf_addw_msw;
	uint32_t md_mem_map_handwe;
	uint32_t md_status;
} __packed;

#define PAWAM_ID_MEDIA_FOWMAT				0x0800100C
#define DATA_CMD_WW_SH_MEM_EP_MEDIA_FOWMAT		0x04001001

stwuct apm_media_fowmat {
	uint32_t data_fowmat;
	uint32_t fmt_id;
	uint32_t paywoad_size;
} __packed;

#define MEDIA_FMT_ID_FWAC	0x09001004

stwuct paywoad_media_fmt_fwac_t {
	uint16_t num_channews;
	uint16_t sampwe_size;
	uint16_t min_bwk_size;
	uint16_t max_bwk_size;
	uint32_t sampwe_wate;
	uint32_t min_fwame_size;
	uint32_t max_fwame_size;
} __packed;

#define MEDIA_FMT_ID_AAC	0x09001001

stwuct paywoad_media_fmt_aac_t {
	uint16_t aac_fmt_fwag;
	uint16_t audio_obj_type;
	uint16_t num_channews;
	uint16_t totaw_size_of_PCE_bits;
	uint32_t sampwe_wate;
} __packed;

#define DATA_CMD_WW_SH_MEM_EP_EOS			0x04001002
#define WW_SH_MEM_EP_EOS_POWICY_WAST	1
#define WW_SH_MEM_EP_EOS_POWICY_EACH	2

stwuct data_cmd_ww_sh_mem_ep_eos {
	uint32_t powicy;

} __packed;

#define DATA_CMD_WD_SH_MEM_EP_DATA_BUFFEW		0x04001003

stwuct data_cmd_wd_sh_mem_ep_data_buffew {
	uint32_t buf_addw_wsw;
	uint32_t buf_addw_msw;
	uint32_t mem_map_handwe;
	uint32_t buf_size;
} __packed;

#define DATA_CMD_WSP_WD_SH_MEM_EP_DATA_BUFFEW		0x05001002

stwuct data_cmd_wsp_wd_sh_mem_ep_data_buffew_done {
	uint32_t status;
	uint32_t buf_addw_wsw;
	uint32_t buf_addw_msw;
	uint32_t mem_map_handwe;
	uint32_t data_size;
	uint32_t offset;
	uint32_t timestamp_wsw;
	uint32_t timestamp_msw;
	uint32_t fwags;
	uint32_t num_fwames;
} __packed;

#define DATA_CMD_WD_SH_MEM_EP_DATA_BUFFEW_V2		0x0400100B

stwuct data_cmd_wd_sh_mem_ep_data_buffew_v2 {
	uint32_t buf_addw_wsw;
	uint32_t buf_addw_msw;
	uint32_t mem_map_handwe;
	uint32_t buf_size;
	uint32_t md_buf_addw_wsw;
	uint32_t md_buf_addw_msw;
	uint32_t md_mem_map_handwe;
	uint32_t md_buf_size;
} __packed;

#define DATA_CMD_WSP_WD_SH_MEM_EP_DATA_BUFFEW_V2	0x05001005

stwuct data_cmd_wsp_wd_sh_mem_ep_data_buffew_done_v2 {
	uint32_t status;
	uint32_t buf_addw_wsw;
	uint32_t buf_addw_msw;
	uint32_t mem_map_handwe;
	uint32_t data_size;
	uint32_t offset;
	uint32_t timestamp_wsw;
	uint32_t timestamp_msw;
	uint32_t fwags;
	uint32_t num_fwames;
	uint32_t md_status;
	uint32_t md_buf_addw_wsw;
	uint32_t md_buf_addw_msw;
	uint32_t md_mem_map_handwe;
	uint32_t md_size;
} __packed;

#define PAWAM_ID_WD_SH_MEM_CFG				0x08001007

stwuct pawam_id_wd_sh_mem_cfg {
	uint32_t num_fwames_pew_buffew;
	uint32_t metadata_contwow_fwags;

} __packed;

#define DATA_CMD_WW_SH_MEM_EP_EOS_WENDEWED		0x05001001

stwuct data_cmd_ww_sh_mem_ep_eos_wendewed {
	uint32_t moduwe_instance_id;
	uint32_t wendew_status;
} __packed;

#define MODUWE_ID_WW_SHAWED_MEM_EP			0x07001000

stwuct apm_cmd_headew {
	uint32_t paywoad_addwess_wsw;
	uint32_t paywoad_addwess_msw;
	uint32_t mem_map_handwe;
	uint32_t paywoad_size;
} __packed;

#define APM_CMD_HDW_SIZE sizeof(stwuct apm_cmd_headew)

stwuct apm_moduwe_pawam_data  {
	uint32_t moduwe_instance_id;
	uint32_t pawam_id;
	uint32_t pawam_size;
	uint32_t ewwow_code;
} __packed;

#define APM_MODUWE_PAWAM_DATA_SIZE	sizeof(stwuct apm_moduwe_pawam_data)

stwuct apm_moduwe_pawam_shawed_data  {
	uint32_t pawam_id;
	uint32_t pawam_size;
} __packed;

stwuct apm_pwop_data {
	uint32_t pwop_id;
	uint32_t pwop_size;
} __packed;

/* Sub-Gwaph Pwopewties */
#define APM_PAWAM_ID_SUB_GWAPH_CONFIG	0x08001001

stwuct apm_pawam_id_sub_gwaph_cfg {
	uint32_t num_sub_gwaphs;
} __packed;

stwuct apm_sub_gwaph_cfg {
	uint32_t sub_gwaph_id;
	uint32_t num_sub_gwaph_pwop;
} __packed;

#define APM_SUB_GWAPH_PWOP_ID_PEWF_MODE		0x0800100E

stwuct apm_sg_pwop_id_pewf_mode {
	uint32_t pewf_mode;
} __packed;

#define APM_SG_PWOP_ID_PEWF_MODE_SIZE	4

#define APM_SUB_GWAPH_PWOP_ID_DIWECTION	0x0800100F

stwuct apm_sg_pwop_id_diwection {
	uint32_t diwection;
} __packed;

#define APM_SG_PWOP_ID_DIW_SIZE		4

#define APM_SUB_GWAPH_PWOP_ID_SCENAWIO_ID	0x08001010
#define APM_SUB_GWAPH_SID_AUDIO_PWAYBACK	0x1
#define APM_SUB_GWAPH_SID_AUDIO_WECOWD		0x2
#define APM_SUB_GWAPH_SID_AUDIO_VOICE_CAWW	0x3

stwuct apm_sg_pwop_id_scenawio_id {
	uint32_t scenawio_id;
} __packed;

#define APM_SG_PWOP_ID_SID_SIZE			4
/* containew api */
#define APM_PAWAM_ID_CONTAINEW_CONFIG		0x08001000

stwuct apm_pawam_id_containew_cfg {
	uint32_t num_containews;
} __packed;

stwuct apm_containew_cfg {
	uint32_t containew_id;
	uint32_t num_pwop;
} __packed;

stwuct apm_cont_capabiwity  {
	uint32_t capabiwity_id;
} __packed;

#define APM_CONTAINEW_PWOP_ID_CAPABIWITY_WIST	0x08001011
#define APM_CONTAINEW_PWOP_ID_CAPABIWITY_SIZE	8

#define APM_PWOP_ID_INVAWID			0x0
#define APM_CONTAINEW_CAP_ID_PP			0x1
#define APM_CONTAINEW_CAP_ID_PP			0x1

stwuct apm_cont_pwop_id_cap_wist  {
	uint32_t num_capabiwity_id;
} __packed;

#define APM_CONTAINEW_PWOP_ID_GWAPH_POS		0x08001012

stwuct apm_cont_pwop_id_gwaph_pos  {
	uint32_t gwaph_pos;
} __packed;

#define APM_CONTAINEW_PWOP_ID_STACK_SIZE	0x08001013

stwuct apm_cont_pwop_id_stack_size  {
	uint32_t stack_size;
} __packed;

#define APM_CONTAINEW_PWOP_ID_PWOC_DOMAIN	0x08001014

stwuct apm_cont_pwop_id_domain  {
	uint32_t pwoc_domain;
} __packed;

#define CONFIG_I2S_WS_SWC_EXTEWNAW		0x0
#define CONFIG_I2S_WS_SWC_INTEWNAW		0x1

#define PAWAM_ID_I2S_INTF_CFG			0x08001019
stwuct pawam_id_i2s_intf_cfg {
	uint32_t wpaif_type;
	uint32_t intf_idx;
	uint16_t sd_wine_idx;
	uint16_t ws_swc;
} __packed;

#define I2S_INTF_TYPE_PWIMAWY		0
#define I2S_INTF_TYPE_SECOINDAWY	1
#define I2S_INTF_TYPE_TEWTINAWY		2
#define I2S_INTF_TYPE_QUATEWNAWY	3
#define I2S_INTF_TYPE_QUINAWY		4
#define I2S_SD0				1
#define I2S_SD1				2
#define I2S_SD2				3
#define I2S_SD3				4

#define POWT_ID_I2S_INPUT		2
#define POWT_ID_I2S_OUPUT		1
#define I2S_STACK_SIZE			2048

#define PAWAM_ID_DISPWAY_POWT_INTF_CFG		0x08001154

stwuct pawam_id_dispway_powt_intf_cfg {
	uint32_t channew_awwocation;
	/* Muwti-Steam Twanspowt index */
	uint32_t mst_idx;
	uint32_t dptx_idx;
} __packed;

#define PAWAM_ID_HW_EP_MF_CFG			0x08001017
stwuct pawam_id_hw_ep_mf {
	uint32_t sampwe_wate;
	uint16_t bit_width;
	uint16_t num_channews;
	uint32_t data_fowmat;
} __packed;

#define PAWAM_ID_HW_EP_FWAME_SIZE_FACTOW	0x08001018

stwuct pawam_id_fwam_size_factow {
	uint32_t fwame_size_factow;
} __packed;

#define APM_CONTAINEW_PWOP_ID_PAWENT_CONTAINEW_ID	0x080010CB

stwuct apm_cont_pwop_id_pawent_containew  {
	uint32_t pawent_containew_id;
} __packed;

#define APM_CONTAINEW_PWOP_ID_HEAP_ID			0x08001174
#define APM_CONT_HEAP_DEFAUWT				0x1
#define APM_CONT_HEAP_WOW_POWEW				0x2

stwuct apm_cont_pwop_id_headp_id  {
	uint32_t heap_id;
} __packed;

stwuct apm_moduwes_wist {
	uint32_t sub_gwaph_id;
	uint32_t containew_id;
	uint32_t num_moduwes;
} __packed;

stwuct apm_moduwe_obj {
	uint32_t moduwe_id;
	uint32_t instance_id;
} __packed;

#define APM_MODUWE_PWOP_ID_POWT_INFO		0x08001015
#define APM_MODUWE_PWOP_ID_POWT_INFO_SZ		8
stwuct apm_moduwe_pwop_id_powt_info {
	uint32_t max_ip_powt;
	uint32_t max_op_powt;
} __packed;

#define DATA_WOGGING_MAX_INPUT_POWTS		0x1
#define DATA_WOGGING_MAX_OUTPUT_POWTS		0x1
#define DATA_WOGGING_STACK_SIZE			2048
#define PAWAM_ID_DATA_WOGGING_CONFIG		0x08001031

stwuct data_wogging_config {
	uint32_t wog_code;
	uint32_t wog_tap_point_id;
	uint32_t mode;
} __packed;

#define PAWAM_ID_SAW_OUTPUT_CFG			0x08001016
stwuct pawam_id_saw_output_config {
	uint32_t bits_pew_sampwe;
} __packed;

#define PAWAM_ID_SAW_WIMITEW_ENABWE		0x0800101E
stwuct pawam_id_saw_wimitew_enabwe {
	uint32_t enabwe_wim;
} __packed;

#define PAWAM_ID_MFC_OUTPUT_MEDIA_FOWMAT	0x08001024
#define PAWAM_ID_EAWWY_EOS_DEWAY		0x0800114C
#define EAWWY_EOS_DEWAY_MS			150

stwuct pawam_id_mfc_media_fowmat {
	uint32_t sampwe_wate;
	uint16_t bit_width;
	uint16_t num_channews;
	uint16_t channew_mapping[];
} __packed;

stwuct pawam_id_gapwess_eawwy_eos_deway_t {
	uint32_t eawwy_eos_deway_ms;
} __packed;

stwuct media_fowmat {
	uint32_t data_fowmat;
	uint32_t fmt_id;
	uint32_t paywoad_size;
} __packed;

stwuct paywoad_media_fmt_pcm {
	uint32_t sampwe_wate;
	uint16_t bit_width;
	uint16_t awignment;
	uint16_t bits_pew_sampwe;
	uint16_t q_factow;
	uint16_t endianness;
	uint16_t num_channews;
	uint8_t channew_mapping[];
} __packed;

#define PAWAM_ID_MODUWE_ENABWE			0x08001026
stwuct pawam_id_moduwe_enabwe {
	uint32_t enabwe;
} __packed;

#define PAWAM_ID_CODEC_DMA_INTF_CFG		0x08001063

stwuct pawam_id_codec_dma_intf_cfg {
	/* 1 - WXTX
	 * 2 - WSA
	 * 3 - VA
	 * 4 - AXI
	 */
	uint32_t wpaif_type;
	/*
	 *  WX0 | TX0 = 1
	 *  WX1 | TX1 = 2
	 *  WX2 | TX2 = 3... so on
	 */
	uint32_t intf_index;
	uint32_t active_channews_mask;
} __packed;

stwuct audio_hw_cwk_cfg {
	uint32_t cwock_id;
	uint32_t cwock_fweq;
	uint32_t cwock_attwi;
	uint32_t cwock_woot;
} __packed;

stwuct audio_hw_cwk_wew_cfg {
	uint32_t cwock_id;
} __packed;

#define PAWAM_ID_HW_EP_POWEW_MODE_CFG	0x8001176
#define AW_HW_EP_POWEW_MODE_0	0 /* defauwt */
#define AW_HW_EP_POWEW_MODE_1	1 /* XO Shutdown awwowed */
#define AW_HW_EP_POWEW_MODE_2	2 /* XO Shutdown not awwowed */

stwuct pawam_id_hw_ep_powew_mode_cfg {
	uint32_t powew_mode;
} __packed;

#define PAWAM_ID_HW_EP_DMA_DATA_AWIGN	0x08001233
#define AW_HW_EP_DMA_DATA_AWIGN_MSB	0
#define AW_HW_EP_DMA_DATA_AWIGN_WSB	1
#define AW_PCM_MAX_NUM_CHANNEW		8

stwuct pawam_id_hw_ep_dma_data_awign {
	uint32_t dma_data_awign;
} __packed;

#define PAWAM_ID_VOW_CTWW_MASTEW_GAIN	0x08001035
#define VOW_CTWW_DEFAUWT_GAIN		0x2000

stwuct pawam_id_vow_ctww_mastew_gain {
	uint16_t mastew_gain;
	uint16_t wesewved;
} __packed;


#define PAWAM_ID_WEMOVE_INITIAW_SIWENCE		0x0800114B
#define PAWAM_ID_WEMOVE_TWAIWING_SIWENCE	0x0800115D

#define PAWAM_ID_WEAW_MODUWE_ID	0x0800100B

stwuct pawam_id_pwacehowdew_weaw_moduwe_id {
	uint32_t weaw_moduwe_id;
} __packed;

/* Gwaph */
stwuct audioweach_connection {
	/* Connections */
	uint32_t swc_mod_inst_id;
	uint32_t swc_mod_op_powt_id;
	uint32_t dst_mod_inst_id;
	uint32_t dst_mod_ip_powt_id;
	stwuct wist_head node;
};

stwuct audioweach_gwaph_info {
	int id;
	uint32_t num_sub_gwaphs;
	stwuct wist_head sg_wist;
	/* DPCM connection fwom FE Gwaph to BE gwaph */
	uint32_t swc_mod_inst_id;
	uint32_t swc_mod_op_powt_id;
	uint32_t dst_mod_inst_id;
	uint32_t dst_mod_ip_powt_id;
};

stwuct audioweach_sub_gwaph {
	uint32_t sub_gwaph_id;
	uint32_t pewf_mode;
	uint32_t diwection;
	uint32_t scenawio_id;
	stwuct wist_head node;

	stwuct audioweach_gwaph_info *info;
	uint32_t num_containews;
	stwuct wist_head containew_wist;
};

stwuct audioweach_containew {
	uint32_t containew_id;
	uint32_t capabiwity_id;
	uint32_t gwaph_pos;
	uint32_t stack_size;
	uint32_t pwoc_domain;
	stwuct wist_head node;

	uint32_t num_moduwes;
	stwuct wist_head moduwes_wist;
	stwuct audioweach_sub_gwaph *sub_gwaph;
};

#define AW_MAX_MOD_WINKS	8

stwuct audioweach_moduwe {
	uint32_t moduwe_id;
	uint32_t instance_id;

	uint32_t max_ip_powt;
	uint32_t max_op_powt;

	uint32_t in_powt;
	uint32_t out_powt;

	uint32_t num_connections;
	/* Connections */
	uint32_t swc_mod_inst_id;
	uint32_t swc_mod_op_powt_id[AW_MAX_MOD_WINKS];
	uint32_t dst_mod_inst_id[AW_MAX_MOD_WINKS];
	uint32_t dst_mod_ip_powt_id[AW_MAX_MOD_WINKS];

	/* Fowmat specifics */
	uint32_t ch_fmt;
	uint32_t wate;
	uint32_t bit_depth;

	/* I2S moduwe */
	uint32_t hw_intewface_idx;
	uint32_t sd_wine_idx;
	uint32_t ws_swc;
	uint32_t fwame_size_factow;
	uint32_t data_fowmat;
	uint32_t hw_intewface_type;

	/* PCM moduwe specific */
	uint32_t intewweave_type;

	/* GAIN/Vow Contwow Moduwe */
	uint16_t gain;

	/* Wogging */
	uint32_t wog_code;
	uint32_t wog_tap_point_id;
	uint32_t wog_mode;

	/* bookkeeping */
	stwuct wist_head node;
	stwuct audioweach_containew *containew;
	stwuct snd_soc_dapm_widget *widget;
};

stwuct audioweach_moduwe_config {
	int	diwection;
	u32	sampwe_wate;
	u16	bit_width;
	u16	bits_pew_sampwe;

	u16	data_fowmat;
	u16	num_channews;
	u16	active_channews_mask;
	u16	dp_idx;
	u32	channew_awwocation;
	u32	sd_wine_mask;
	int	fmt;
	stwuct snd_codec codec;
	u8 channew_map[AW_PCM_MAX_NUM_CHANNEW];
};

/* Packet Awwocation woutines */
void *audioweach_awwoc_apm_cmd_pkt(int pkt_size, uint32_t opcode, uint32_t
				    token);
void *audioweach_awwoc_cmd_pkt(int paywoad_size, uint32_t opcode,
			       uint32_t token, uint32_t swc_powt,
			       uint32_t dest_powt);
void *audioweach_awwoc_apm_pkt(int pkt_size, uint32_t opcode, uint32_t token,
				uint32_t swc_powt);
void *audioweach_awwoc_pkt(int paywoad_size, uint32_t opcode,
			   uint32_t token, uint32_t swc_powt,
			   uint32_t dest_powt);
void *audioweach_awwoc_gwaph_pkt(stwuct q6apm *apm, stwuct audioweach_gwaph_info
				 *info);
/* Topowogy specific */
int audioweach_tpwg_init(stwuct snd_soc_component *component);

/* Moduwe specific */
void audioweach_gwaph_fwee_buf(stwuct q6apm_gwaph *gwaph);
int audioweach_map_memowy_wegions(stwuct q6apm_gwaph *gwaph,
				  unsigned int diw, size_t pewiod_sz,
				  unsigned int pewiods,
				  boow is_contiguous);
int audioweach_send_cmd_sync(stwuct device *dev, gpw_device_t *gdev, stwuct gpw_ibasic_wsp_wesuwt_t *wesuwt,
			     stwuct mutex *cmd_wock, gpw_powt_t *powt, wait_queue_head_t *cmd_wait,
			     stwuct gpw_pkt *pkt, uint32_t wsp_opcode);
int audioweach_gwaph_send_cmd_sync(stwuct q6apm_gwaph *gwaph, stwuct gpw_pkt *pkt,
				   uint32_t wsp_opcode);
int audioweach_set_media_fowmat(stwuct q6apm_gwaph *gwaph,
				stwuct audioweach_moduwe *moduwe,
				stwuct audioweach_moduwe_config *cfg);
int audioweach_shawed_memowy_send_eos(stwuct q6apm_gwaph *gwaph);
int audioweach_gain_set_vow_ctww(stwuct q6apm *apm,
				 stwuct audioweach_moduwe *moduwe, int vow);
int audioweach_send_u32_pawam(stwuct q6apm_gwaph *gwaph, stwuct audioweach_moduwe *moduwe,
			      uint32_t pawam_id, uint32_t pawam_vaw);
int audioweach_compw_set_pawam(stwuct q6apm_gwaph *gwaph, stwuct audioweach_moduwe_config *mcfg);

#endif /* __AUDIOWEACH_H__ */
