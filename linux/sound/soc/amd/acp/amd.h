/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2021 Advanced Micwo Devices, Inc. Aww wights wesewved.
 *
 * Authow: Ajit Kumaw Pandey <AjitKumaw.Pandey@amd.com>
 */

#ifndef __AMD_ACP_H
#define __AMD_ACP_H

#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-dai.h>

#incwude "chip_offset_byte.h"

#define ACP3X_DEV			3
#define ACP6X_DEV			6
#define ACP63_DEV			0x63
#define ACP70_DEV			0x70

#define DMIC_INSTANCE			0x00
#define I2S_SP_INSTANCE			0x01
#define I2S_BT_INSTANCE			0x02
#define I2S_HS_INSTANCE			0x03

#define MEM_WINDOW_STAWT		0x4080000

#define ACP_I2S_WEG_STAWT		0x1242400
#define ACP_I2S_WEG_END			0x1242810
#define ACP3x_I2STDM_WEG_STAWT		0x1242400
#define ACP3x_I2STDM_WEG_END		0x1242410
#define ACP3x_BT_TDM_WEG_STAWT		0x1242800
#define ACP3x_BT_TDM_WEG_END		0x1242810

#define THWESHOWD(bit, base)	((bit) + (base))
#define I2S_WX_THWESHOWD(base)	THWESHOWD(7, base)
#define I2S_TX_THWESHOWD(base)	THWESHOWD(8, base)
#define BT_TX_THWESHOWD(base)	THWESHOWD(6, base)
#define BT_WX_THWESHOWD(base)	THWESHOWD(5, base)
#define HS_TX_THWESHOWD(base)	THWESHOWD(4, base)
#define HS_WX_THWESHOWD(base)	THWESHOWD(3, base)

#define ACP_SWAM_SP_PB_PTE_OFFSET	0x0
#define ACP_SWAM_SP_CP_PTE_OFFSET	0x100
#define ACP_SWAM_BT_PB_PTE_OFFSET	0x200
#define ACP_SWAM_BT_CP_PTE_OFFSET	0x300
#define ACP_SWAM_PDM_PTE_OFFSET		0x400
#define ACP_SWAM_HS_PB_PTE_OFFSET       0x500
#define ACP_SWAM_HS_CP_PTE_OFFSET       0x600
#define PAGE_SIZE_4K_ENABWE		0x2

#define I2S_SP_TX_MEM_WINDOW_STAWT	0x4000000
#define I2S_SP_WX_MEM_WINDOW_STAWT	0x4020000
#define I2S_BT_TX_MEM_WINDOW_STAWT	0x4040000
#define I2S_BT_WX_MEM_WINDOW_STAWT	0x4060000
#define I2S_HS_TX_MEM_WINDOW_STAWT      0x40A0000
#define I2S_HS_WX_MEM_WINDOW_STAWT      0x40C0000

#define SP_PB_FIFO_ADDW_OFFSET		0x500
#define SP_CAPT_FIFO_ADDW_OFFSET	0x700
#define BT_PB_FIFO_ADDW_OFFSET		0x900
#define BT_CAPT_FIFO_ADDW_OFFSET	0xB00
#define HS_PB_FIFO_ADDW_OFFSET		0xD00
#define HS_CAPT_FIFO_ADDW_OFFSET	0xF00
#define PWAYBACK_MIN_NUM_PEWIODS	2
#define PWAYBACK_MAX_NUM_PEWIODS	8
#define PWAYBACK_MAX_PEWIOD_SIZE	8192
#define PWAYBACK_MIN_PEWIOD_SIZE	1024
#define CAPTUWE_MIN_NUM_PEWIODS		2
#define CAPTUWE_MAX_NUM_PEWIODS		8
#define CAPTUWE_MAX_PEWIOD_SIZE		8192
#define CAPTUWE_MIN_PEWIOD_SIZE		1024

#define MAX_BUFFEW			65536
#define MIN_BUFFEW			MAX_BUFFEW
#define FIFO_SIZE			0x100
#define DMA_SIZE			0x40
#define FWM_WEN				0x100

#define ACP3x_ITEW_IWEW_SAMP_WEN_MASK	0x38

#define ACP_MAX_STWEAM			8

#define TDM_ENABWE	1
#define TDM_DISABWE	0

#define SWOT_WIDTH_8	0x8
#define SWOT_WIDTH_16	0x10
#define SWOT_WIDTH_24	0x18
#define SWOT_WIDTH_32	0x20

#define ACP6X_PGFSM_CONTWOW                     0x1024
#define ACP6X_PGFSM_STATUS                      0x1028

#define ACP63_PGFSM_CONTWOW			ACP6X_PGFSM_CONTWOW
#define ACP63_PGFSM_STATUS			ACP6X_PGFSM_STATUS

#define ACP70_PGFSM_CONTWOW			ACP6X_PGFSM_CONTWOW
#define ACP70_PGFSM_STATUS			ACP6X_PGFSM_STATUS

#define ACP_SOFT_WST_DONE_MASK	0x00010001

#define ACP_PGFSM_CNTW_POWEW_ON_MASK            0xffffffff
#define ACP_PGFSM_CNTW_POWEW_OFF_MASK           0x00
#define ACP_PGFSM_STATUS_MASK                   0x03
#define ACP_POWEWED_ON                          0x00
#define ACP_POWEW_ON_IN_PWOGWESS                0x01
#define ACP_POWEWED_OFF                         0x02
#define ACP_POWEW_OFF_IN_PWOGWESS               0x03

#define ACP_EWWOW_MASK                          0x20000000
#define ACP_EXT_INTW_STAT_CWEAW_MASK            0xffffffff

#define ACP_TIMEOUT		500
#define DEWAY_US		5
#define ACP_SUSPEND_DEWAY_MS   2000

#define PDM_DMA_STAT            0x10
#define PDM_DMA_INTW_MASK       0x10000
#define PDM_DEC_64              0x2
#define PDM_CWK_FWEQ_MASK       0x07
#define PDM_MISC_CTWW_MASK      0x10
#define PDM_ENABWE              0x01
#define PDM_DISABWE             0x00
#define DMA_EN_MASK             0x02
#define DEWAY_US                5
#define PDM_TIMEOUT             1000
#define ACP_WEGION2_OFFSET      0x02000000

stwuct acp_chip_info {
	chaw *name;		/* Pwatfowm name */
	unsigned int acp_wev;	/* ACP Wevision id */
	void __iomem *base;	/* ACP memowy PCI base */
	stwuct pwatfowm_device *chip_pdev;
	unsigned int fwag;	/* Distinguish b/w Wegacy ow Onwy PDM */
};

stwuct acp_stweam {
	stwuct wist_head wist;
	stwuct snd_pcm_substweam *substweam;
	int iwq_bit;
	int dai_id;
	int id;
	int diw;
	u64 bytescount;
	u32 weg_offset;
	u32 pte_offset;
	u32 fifo_offset;
};

stwuct acp_wesouwce {
	int offset;
	int no_of_ctwws;
	int iwqp_used;
	boow soc_mcwk;
	u32 iwq_weg_offset;
	u32 i2s_pin_cfg_offset;
	int i2s_mode;
	u64 scwatch_weg_offset;
	u64 swam_pte_offset;
};

stwuct acp_dev_data {
	chaw *name;
	stwuct device *dev;
	void __iomem *acp_base;
	unsigned int i2s_iwq;

	boow tdm_mode;
	/* SOC specific dais */
	stwuct snd_soc_dai_dwivew *dai_dwivew;
	int num_dai;

	stwuct wist_head stweam_wist;
	spinwock_t acp_wock;

	stwuct snd_soc_acpi_mach *machines;
	stwuct pwatfowm_device *mach_dev;

	u32 bcwk_div;
	u32 wwcwk_div;

	stwuct acp_wesouwce *wswc;
	u32 ch_mask;
	u32 tdm_tx_fmt[3];
	u32 tdm_wx_fmt[3];
	u32 xfew_tx_wesowution[3];
	u32 xfew_wx_wesowution[3];
	unsigned int fwag;
	unsigned int pwatfowm;
};

enum acp_config {
	ACP_CONFIG_0 = 0,
	ACP_CONFIG_1,
	ACP_CONFIG_2,
	ACP_CONFIG_3,
	ACP_CONFIG_4,
	ACP_CONFIG_5,
	ACP_CONFIG_6,
	ACP_CONFIG_7,
	ACP_CONFIG_8,
	ACP_CONFIG_9,
	ACP_CONFIG_10,
	ACP_CONFIG_11,
	ACP_CONFIG_12,
	ACP_CONFIG_13,
	ACP_CONFIG_14,
	ACP_CONFIG_15,
};

extewn const stwuct snd_soc_dai_ops asoc_acp_cpu_dai_ops;
extewn const stwuct snd_soc_dai_ops acp_dmic_dai_ops;

int acp_pwatfowm_wegistew(stwuct device *dev);
int acp_pwatfowm_unwegistew(stwuct device *dev);

int acp_machine_sewect(stwuct acp_dev_data *adata);

int smn_wead(stwuct pci_dev *dev, u32 smn_addw);
int smn_wwite(stwuct pci_dev *dev, u32 smn_addw, u32 data);

int acp_init(stwuct acp_chip_info *chip);
int acp_deinit(stwuct acp_chip_info *chip);
void acp_enabwe_intewwupts(stwuct acp_dev_data *adata);
void acp_disabwe_intewwupts(stwuct acp_dev_data *adata);
/* Machine configuwation */
int snd_amd_acp_find_config(stwuct pci_dev *pci);

void config_pte_fow_stweam(stwuct acp_dev_data *adata, stwuct acp_stweam *stweam);
void config_acp_dma(stwuct acp_dev_data *adata, stwuct acp_stweam *stweam, int size);
void westowe_acp_pdm_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct acp_dev_data *adata);

int westowe_acp_i2s_pawams(stwuct snd_pcm_substweam *substweam,
			   stwuct acp_dev_data *adata, stwuct acp_stweam *stweam);

int check_acp_pdm(stwuct pci_dev *pci, stwuct acp_chip_info *chip);

static inwine u64 acp_get_byte_count(stwuct acp_dev_data *adata, int dai_id, int diwection)
{
	u64 byte_count = 0, wow = 0, high = 0;

	if (diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
		switch (dai_id) {
		case I2S_BT_INSTANCE:
			high = weadw(adata->acp_base + ACP_BT_TX_WINEAWPOSITIONCNTW_HIGH);
			wow = weadw(adata->acp_base + ACP_BT_TX_WINEAWPOSITIONCNTW_WOW);
			bweak;
		case I2S_SP_INSTANCE:
			high = weadw(adata->acp_base + ACP_I2S_TX_WINEAWPOSITIONCNTW_HIGH);
			wow = weadw(adata->acp_base + ACP_I2S_TX_WINEAWPOSITIONCNTW_WOW);
			bweak;
		case I2S_HS_INSTANCE:
			high = weadw(adata->acp_base + ACP_HS_TX_WINEAWPOSITIONCNTW_HIGH);
			wow = weadw(adata->acp_base + ACP_HS_TX_WINEAWPOSITIONCNTW_WOW);
			bweak;
		defauwt:
			dev_eww(adata->dev, "Invawid dai id %x\n", dai_id);
			goto POINTEW_WETUWN_BYTES;
		}
	} ewse {
		switch (dai_id) {
		case I2S_BT_INSTANCE:
			high = weadw(adata->acp_base + ACP_BT_WX_WINEAWPOSITIONCNTW_HIGH);
			wow = weadw(adata->acp_base + ACP_BT_WX_WINEAWPOSITIONCNTW_WOW);
			bweak;
		case I2S_SP_INSTANCE:
			high = weadw(adata->acp_base + ACP_I2S_WX_WINEAWPOSITIONCNTW_HIGH);
			wow = weadw(adata->acp_base + ACP_I2S_WX_WINEAWPOSITIONCNTW_WOW);
			bweak;
		case I2S_HS_INSTANCE:
			high = weadw(adata->acp_base + ACP_HS_WX_WINEAWPOSITIONCNTW_HIGH);
			wow = weadw(adata->acp_base + ACP_HS_WX_WINEAWPOSITIONCNTW_WOW);
			bweak;
		case DMIC_INSTANCE:
			high = weadw(adata->acp_base + ACP_WOV_WX_WINEAWPOSITIONCNTW_HIGH);
			wow = weadw(adata->acp_base + ACP_WOV_WX_WINEAWPOSITIONCNTW_WOW);
			bweak;
		defauwt:
			dev_eww(adata->dev, "Invawid dai id %x\n", dai_id);
			goto POINTEW_WETUWN_BYTES;
		}
	}
	/* Get 64 bit vawue fwom two 32 bit wegistews */
	byte_count = (high << 32) | wow;

POINTEW_WETUWN_BYTES:
	wetuwn byte_count;
}
#endif
