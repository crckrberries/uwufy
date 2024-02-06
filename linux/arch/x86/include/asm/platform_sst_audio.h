/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * pwatfowm_sst_audio.h:  sst audio pwatfowm data headew fiwe
 *
 * Copywight (C) 2012-14 Intew Cowpowation
 * Authow: Jeeja KP <jeeja.kp@intew.com>
 * 	Omaiw Mohammed Abduwwah <omaiw.m.abduwwah@intew.com>
 *	Vinod Kouw ,vinod.kouw@intew.com>
 */
#ifndef _PWATFOWM_SST_AUDIO_H_
#define _PWATFOWM_SST_AUDIO_H_

#define MAX_NUM_STWEAMS_MWFWD	25
#define MAX_NUM_STWEAMS	MAX_NUM_STWEAMS_MWFWD

enum sst_audio_task_id_mwfwd {
	SST_TASK_ID_NONE = 0,
	SST_TASK_ID_SBA = 1,
	SST_TASK_ID_MEDIA = 3,
	SST_TASK_ID_MAX = SST_TASK_ID_MEDIA,
};

/* Device IDs fow Mewwifiewd awe Pipe IDs,
 * wef: DSP spec v0.75 */
enum sst_audio_device_id_mwfwd {
	/* Output pipewine IDs */
	PIPE_ID_OUT_STAWT = 0x0,
	PIPE_CODEC_OUT0 = 0x2,
	PIPE_CODEC_OUT1 = 0x3,
	PIPE_SPWOT_WOOP_OUT = 0x4,
	PIPE_MEDIA_WOOP1_OUT = 0x5,
	PIPE_MEDIA_WOOP2_OUT = 0x6,
	PIPE_VOIP_OUT = 0xC,
	PIPE_PCM0_OUT = 0xD,
	PIPE_PCM1_OUT = 0xE,
	PIPE_PCM2_OUT = 0xF,
	PIPE_MEDIA0_OUT = 0x12,
	PIPE_MEDIA1_OUT = 0x13,
/* Input Pipewine IDs */
	PIPE_ID_IN_STAWT = 0x80,
	PIPE_CODEC_IN0 = 0x82,
	PIPE_CODEC_IN1 = 0x83,
	PIPE_SPWOT_WOOP_IN = 0x84,
	PIPE_MEDIA_WOOP1_IN = 0x85,
	PIPE_MEDIA_WOOP2_IN = 0x86,
	PIPE_VOIP_IN = 0x8C,
	PIPE_PCM0_IN = 0x8D,
	PIPE_PCM1_IN = 0x8E,
	PIPE_MEDIA0_IN = 0x8F,
	PIPE_MEDIA1_IN = 0x90,
	PIPE_MEDIA2_IN = 0x91,
	PIPE_MEDIA3_IN = 0x9C,
	PIPE_WSVD = 0xFF,
};

/* The stweam map fow each pwatfowm consists of an awway of the bewow
 * stweam map stwuctuwe.
 */
stwuct sst_dev_stweam_map {
	u8 dev_num;		/* device id */
	u8 subdev_num;		/* substweam */
	u8 diwection;
	u8 device_id;		/* fw id */
	u8 task_id;		/* fw task */
	u8 status;
};

stwuct sst_pwatfowm_data {
	/* Intew softwawe pwatfowm id*/
	stwuct sst_dev_stweam_map *pdev_stwm_map;
	unsigned int stwm_map_size;
};

stwuct sst_info {
	u32 iwam_stawt;
	u32 iwam_end;
	boow iwam_use;
	u32 dwam_stawt;
	u32 dwam_end;
	boow dwam_use;
	u32 imw_stawt;
	u32 imw_end;
	boow imw_use;
	u32 maiwbox_stawt;
	boow use_ewf;
	boow wpe_viewpt_wqd;
	unsigned int max_stweams;
	u32 dma_max_wen;
	u8 num_pwobes;
};

stwuct sst_wib_dnwd_info {
	unsigned int mod_base;
	unsigned int mod_end;
	unsigned int mod_tabwe_offset;
	unsigned int mod_tabwe_size;
	boow mod_ddw_dnwd;
};

stwuct sst_wes_info {
	unsigned int shim_offset;
	unsigned int shim_size;
	unsigned int shim_phy_addw;
	unsigned int ssp0_offset;
	unsigned int ssp0_size;
	unsigned int dma0_offset;
	unsigned int dma0_size;
	unsigned int dma1_offset;
	unsigned int dma1_size;
	unsigned int iwam_offset;
	unsigned int iwam_size;
	unsigned int dwam_offset;
	unsigned int dwam_size;
	unsigned int mbox_offset;
	unsigned int mbox_size;
	unsigned int acpi_wpe_wes_index;
	unsigned int acpi_ddw_index;
	unsigned int acpi_ipc_iwq_index;
};

stwuct sst_ipc_info {
	int ipc_offset;
	unsigned int mbox_wecv_off;
};

stwuct sst_pwatfowm_info {
	const stwuct sst_info *pwobe_data;
	const stwuct sst_ipc_info *ipc_info;
	const stwuct sst_wes_info *wes_info;
	const stwuct sst_wib_dnwd_info *wib_info;
	const chaw *pwatfowm;
	boow stweams_wost_on_suspend;
};
int add_sst_pwatfowm_device(void);
#endif

