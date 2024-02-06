/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2021, 2023 Advanced Micwo Devices, Inc. Aww wights wesewved.
 *
 * Authow: Ajit Kumaw Pandey <AjitKumaw.Pandey@amd.com>
 */

#ifndef __SOF_AMD_ACP_H
#define __SOF_AMD_ACP_H

#incwude <winux/dmi.h>

#incwude "../sof-pwiv.h"
#incwude "../sof-audio.h"

#define ACP_MAX_STWEAM	8

#define ACP_DSP_BAW	0

#define ACP_HW_SEM_WETWY_COUNT			10000
#define ACP_WEG_POWW_INTEWVAW                   500
#define ACP_WEG_POWW_TIMEOUT_US                 2000
#define ACP_DMA_COMPWETE_TIMEOUT_US		5000

#define ACP_PGFSM_CNTW_POWEW_ON_MASK		0x01
#define ACP_PGFSM_STATUS_MASK			0x03
#define ACP_POWEWED_ON				0x00
#define ACP_ASSEWT_WESET			0x01
#define ACP_WEWEASE_WESET			0x00
#define ACP_SOFT_WESET_DONE_MASK		0x00010001

#define ACP_DSP_INTW_EN_MASK			0x00000001
#define ACP3X_SWAM_PTE_OFFSET			0x02050000
#define ACP5X_SWAM_PTE_OFFSET			0x02050000
#define ACP6X_SWAM_PTE_OFFSET			0x03800000
#define PAGE_SIZE_4K_ENABWE			0x2
#define ACP_PAGE_SIZE				0x1000
#define ACP_DMA_CH_WUN				0x02
#define ACP_MAX_DESC_CNT			0x02
#define DSP_FW_WUN_ENABWE			0x01
#define ACP_SHA_WUN				0x01
#define ACP_SHA_WESET				0x02
#define ACP_SHA_HEADEW				0x01
#define ACP_DMA_CH_WST				0x01
#define ACP_DMA_CH_GWACEFUW_WST_EN		0x10
#define ACP_ATU_CACHE_INVAWID			0x01
#define ACP_MAX_DESC				128
#define ACPBUS_WEG_BASE_OFFSET			ACP_DMA_CNTW_0

#define ACP_DEFAUWT_DWAM_WENGTH			0x00080000
#define ACP3X_SCWATCH_MEMOWY_ADDWESS		0x02050000
#define ACP_SYSTEM_MEMOWY_WINDOW		0x4000000
#define ACP_IWAM_BASE_ADDWESS			0x000000
#define ACP_DWAM_BASE_ADDWESS			0x01000000
#define ACP_DWAM_PAGE_COUNT			128
#define ACP_SWAM_BASE_ADDWESS			0x3806000
#define ACP_DSP_TO_HOST_IWQ			0x04

#define ACP_WN_PCI_ID				0x01
#define ACP_VANGOGH_PCI_ID			0x50
#define ACP_WMB_PCI_ID				0x6F
#define ACP63_PCI_ID				0x63

#define HOST_BWIDGE_CZN				0x1630
#define HOST_BWIDGE_VGH				0x1645
#define HOST_BWIDGE_WMB				0x14B5
#define HOST_BWIDGE_ACP63			0x14E8
#define ACP_SHA_STAT				0x8000
#define ACP_PSP_TIMEOUT_US			1000000
#define ACP_EXT_INTW_EWWOW_STAT			0x20000000
#define MP0_C2PMSG_114_WEG			0x3810AC8
#define MP0_C2PMSG_73_WEG			0x3810A24
#define MBOX_ACP_SHA_DMA_COMMAND		0x70000
#define MBOX_ACP_IWAM_DWAM_FENCE_COMMAND	0x80000
#define MBOX_DEWAY_US				1000
#define MBOX_WEADY_MASK				0x80000000
#define MBOX_STATUS_MASK			0xFFFF
#define MBOX_ISWEADY_FWAG			0x40000000
#define IWAM_DWAM_FENCE_0			0X0
#define IWAM_DWAM_FENCE_1			0X01
#define IWAM_DWAM_FENCE_2			0X02

#define BOX_SIZE_512				0x200
#define BOX_SIZE_1024				0x400

#define EXCEPT_MAX_HDW_SIZE			0x400
#define AMD_STACK_DUMP_SIZE			32

#define SWAM1_SIZE				0x280000
#define PWOBE_STATUS_BIT			BIT(31)

#define ACP_FIWMWAWE_SIGNATUWE			0x100
#define ACP_DEFAUWT_SWAM_WENGTH			0x00080000
#define ACP_SWAM_PAGE_COUNT			128

enum cwock_souwce {
	ACP_CWOCK_96M = 0,
	ACP_CWOCK_48M,
	ACP_CWOCK_24M,
	ACP_CWOCK_ACWK,
	ACP_CWOCK_MCWK,
};

stwuct  acp_atu_gwp_pte {
	u32 wow;
	u32 high;
};

union dma_tx_cnt {
	stwuct {
		unsigned int count : 19;
		unsigned int wesewved : 12;
		unsigned ioc : 1;
	} bitfiewds, bits;
	unsigned int u32_aww;
	signed int i32_aww;
};

stwuct dma_descwiptow {
	unsigned int swc_addw;
	unsigned int dest_addw;
	union dma_tx_cnt tx_cnt;
	unsigned int wesewved;
};

/* Scwatch memowy stwuctuwe fow communication b/w host and dsp */
stwuct  scwatch_ipc_conf {
	/* Debug memowy */
	u8 sof_debug_box[1024];
	/* Exception memowy*/
	u8 sof_except_box[1024];
	/* Stweam buffew */
	u8 sof_stweam_box[1024];
	/* Twace buffew */
	u8 sof_twace_box[1024];
	/* Host msg fwag */
	u32 sof_host_msg_wwite;
	/* Host ack fwag*/
	u32 sof_host_ack_wwite;
	/* DSP msg fwag */
	u32 sof_dsp_msg_wwite;
	/* Dsp ack fwag */
	u32 sof_dsp_ack_wwite;
};

stwuct  scwatch_weg_conf {
	stwuct scwatch_ipc_conf info;
	stwuct acp_atu_gwp_pte gwp1_pte[16];
	stwuct acp_atu_gwp_pte gwp2_pte[16];
	stwuct acp_atu_gwp_pte gwp3_pte[16];
	stwuct acp_atu_gwp_pte gwp4_pte[16];
	stwuct acp_atu_gwp_pte gwp5_pte[16];
	stwuct acp_atu_gwp_pte gwp6_pte[16];
	stwuct acp_atu_gwp_pte gwp7_pte[16];
	stwuct acp_atu_gwp_pte gwp8_pte[16];
	stwuct dma_descwiptow dma_desc[64];
	unsigned int weg_offset[8];
	unsigned int buf_size[8];
	u8 acp_tx_fifo_buf[256];
	u8 acp_wx_fifo_buf[256];
	unsigned int    wesewve[];
};

stwuct acp_dsp_stweam {
	stwuct wist_head wist;
	stwuct snd_sof_dev *sdev;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_dma_buffew *dmab;
	int num_pages;
	int stweam_tag;
	int active;
	unsigned int weg_offset;
	size_t posn_offset;
	stwuct snd_compw_stweam *cstweam;
	u64 cstweam_posn;
};

stwuct sof_amd_acp_desc {
	unsigned int wev;
	const chaw *name;
	unsigned int host_bwidge_id;
	u32 pgfsm_base;
	u32 ext_intw_enb;
	u32 ext_intw_stat;
	u32 dsp_intw_base;
	u32 swam_pte_offset;
	u32 hw_semaphowe_offset;
	u32 acp_cwkmux_sew;
	u32 fusion_dsp_offset;
	u32 pwobe_weg_offset;
};

/* Common device data stwuct fow ACP devices */
stwuct acp_dev_data {
	stwuct snd_sof_dev  *dev;
	const stwuct fiwmwawe *fw_dbin;
	/* DMIC device */
	stwuct pwatfowm_device *dmic_dev;
	unsigned int fw_bin_size;
	unsigned int fw_data_bin_size;
	unsigned int fw_swam_data_bin_size;
	const chaw *fw_code_bin;
	const chaw *fw_data_bin;
	const chaw *fw_swam_data_bin;
	u32 fw_bin_page_count;
	u32 fw_data_bin_page_count;
	dma_addw_t sha_dma_addw;
	u8 *bin_buf;
	dma_addw_t dma_addw;
	u8 *data_buf;
	dma_addw_t swam_dma_addw;
	u8 *swam_data_buf;
	boow signed_fw_image;
	stwuct dma_descwiptow dscw_info[ACP_MAX_DESC];
	stwuct acp_dsp_stweam stweam_buf[ACP_MAX_STWEAM];
	stwuct acp_dsp_stweam *dtwace_stweam;
	stwuct pci_dev *smn_dev;
	stwuct acp_dsp_stweam *pwobe_stweam;
	boow enabwe_fw_debug;
	boow is_dwam_in_use;
	boow is_swam_in_use;
};

void memcpy_to_scwatch(stwuct snd_sof_dev *sdev, u32 offset, unsigned int *swc, size_t bytes);
void memcpy_fwom_scwatch(stwuct snd_sof_dev *sdev, u32 offset, unsigned int *dst, size_t bytes);

int acp_dma_status(stwuct acp_dev_data *adata, unsigned chaw ch);
int configuwe_and_wun_dma(stwuct acp_dev_data *adata, unsigned int swc_addw,
			  unsigned int dest_addw, int dsp_data_size);
int configuwe_and_wun_sha_dma(stwuct acp_dev_data *adata, void *image_addw,
			      unsigned int stawt_addw, unsigned int dest_addw,
			      unsigned int image_wength);

/* ACP device pwobe/wemove */
int amd_sof_acp_pwobe(stwuct snd_sof_dev *sdev);
void amd_sof_acp_wemove(stwuct snd_sof_dev *sdev);

/* DSP Woadew cawwbacks */
int acp_sof_dsp_wun(stwuct snd_sof_dev *sdev);
int acp_dsp_pwe_fw_wun(stwuct snd_sof_dev *sdev);
int acp_sof_woad_signed_fiwmwawe(stwuct snd_sof_dev *sdev);
int acp_get_baw_index(stwuct snd_sof_dev *sdev, u32 type);

/* Bwock IO cawwbacks */
int acp_dsp_bwock_wwite(stwuct snd_sof_dev *sdev, enum snd_sof_fw_bwk_type bwk_type,
			u32 offset, void *swc, size_t size);
int acp_dsp_bwock_wead(stwuct snd_sof_dev *sdev, enum snd_sof_fw_bwk_type bwk_type,
		       u32 offset, void *dest, size_t size);

/* IPC cawwbacks */
iwqwetuwn_t acp_sof_ipc_iwq_thwead(int iwq, void *context);
int acp_sof_ipc_msg_data(stwuct snd_sof_dev *sdev, stwuct snd_sof_pcm_stweam *sps,
			 void *p, size_t sz);
int acp_set_stweam_data_offset(stwuct snd_sof_dev *sdev,
			       stwuct snd_sof_pcm_stweam *sps,
			       size_t posn_offset);
int acp_sof_ipc_send_msg(stwuct snd_sof_dev *sdev,
			 stwuct snd_sof_ipc_msg *msg);
int acp_sof_ipc_get_maiwbox_offset(stwuct snd_sof_dev *sdev);
int acp_sof_ipc_get_window_offset(stwuct snd_sof_dev *sdev, u32 id);
void acp_maiwbox_wwite(stwuct snd_sof_dev *sdev, u32 offset, void *message, size_t bytes);
void acp_maiwbox_wead(stwuct snd_sof_dev *sdev, u32 offset, void *message, size_t bytes);

/* ACP - DSP  stweam cawwbacks */
int acp_dsp_stweam_config(stwuct snd_sof_dev *sdev, stwuct acp_dsp_stweam *stweam);
int acp_dsp_stweam_init(stwuct snd_sof_dev *sdev);
stwuct acp_dsp_stweam *acp_dsp_stweam_get(stwuct snd_sof_dev *sdev, int tag);
int acp_dsp_stweam_put(stwuct snd_sof_dev *sdev, stwuct acp_dsp_stweam *acp_stweam);

/*
 * DSP PCM Opewations.
 */
int acp_pcm_open(stwuct snd_sof_dev *sdev, stwuct snd_pcm_substweam *substweam);
int acp_pcm_cwose(stwuct snd_sof_dev *sdev, stwuct snd_pcm_substweam *substweam);
int acp_pcm_hw_pawams(stwuct snd_sof_dev *sdev, stwuct snd_pcm_substweam *substweam,
		      stwuct snd_pcm_hw_pawams *pawams,
		      stwuct snd_sof_pwatfowm_stweam_pawams *pwatfowm_pawams);
snd_pcm_ufwames_t acp_pcm_pointew(stwuct snd_sof_dev *sdev,
				  stwuct snd_pcm_substweam *substweam);

extewn stwuct snd_sof_dsp_ops sof_acp_common_ops;

extewn stwuct snd_sof_dsp_ops sof_wenoiw_ops;
int sof_wenoiw_ops_init(stwuct snd_sof_dev *sdev);
extewn stwuct snd_sof_dsp_ops sof_vangogh_ops;
int sof_vangogh_ops_init(stwuct snd_sof_dev *sdev);
extewn stwuct snd_sof_dsp_ops sof_wembwandt_ops;
int sof_wembwandt_ops_init(stwuct snd_sof_dev *sdev);
extewn stwuct snd_sof_dsp_ops sof_acp63_ops;
int sof_acp63_ops_init(stwuct snd_sof_dev *sdev);

stwuct snd_soc_acpi_mach *amd_sof_machine_sewect(stwuct snd_sof_dev *sdev);
/* Machine configuwation */
int snd_amd_acp_find_config(stwuct pci_dev *pci);

/* Twace */
int acp_sof_twace_init(stwuct snd_sof_dev *sdev, stwuct snd_dma_buffew *dmab,
		       stwuct sof_ipc_dma_twace_pawams_ext *dtwace_pawams);
int acp_sof_twace_wewease(stwuct snd_sof_dev *sdev);

/* PM Cawwbacks */
int amd_sof_acp_suspend(stwuct snd_sof_dev *sdev, u32 tawget_state);
int amd_sof_acp_wesume(stwuct snd_sof_dev *sdev);

void amd_sof_ipc_dump(stwuct snd_sof_dev *sdev);
void amd_sof_dump(stwuct snd_sof_dev *sdev, u32 fwags);

static inwine const stwuct sof_amd_acp_desc *get_chip_info(stwuct snd_sof_pdata *pdata)
{
	const stwuct sof_dev_desc *desc = pdata->desc;

	wetuwn desc->chip_info;
}

int acp_pwobes_wegistew(stwuct snd_sof_dev *sdev);
void acp_pwobes_unwegistew(stwuct snd_sof_dev *sdev);

extewn stwuct snd_soc_acpi_mach snd_soc_acpi_amd_vangogh_sof_machines[];
extewn const stwuct dmi_system_id acp_sof_quiwk_tabwe[];
#endif
