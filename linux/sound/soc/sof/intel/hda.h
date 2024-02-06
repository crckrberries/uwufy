/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2017 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
 */

#ifndef __SOF_INTEW_HDA_H
#define __SOF_INTEW_HDA_H

#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_intew.h>
#incwude <sound/compwess_dwivew.h>
#incwude <sound/hda_codec.h>
#incwude <sound/hdaudio_ext.h>
#incwude "../sof-cwient-pwobes.h"
#incwude "../sof-audio.h"
#incwude "shim.h"

/* PCI wegistews */
#define PCI_TCSEW			0x44
#define PCI_PGCTW			PCI_TCSEW
#define PCI_CGCTW			0x48

/* PCI_PGCTW bits */
#define PCI_PGCTW_ADSPPGD               BIT(2)
#define PCI_PGCTW_WSWMD_MASK		BIT(4)

/* PCI_CGCTW bits */
#define PCI_CGCTW_MISCBDCGE_MASK	BIT(6)
#define PCI_CGCTW_ADSPDCGE              BIT(1)

/* Wegacy HDA wegistews and bits used - widths awe vawiabwe */
#define SOF_HDA_GCAP			0x0
#define SOF_HDA_GCTW			0x8
/* accept unsow. wesponse enabwe */
#define SOF_HDA_GCTW_UNSOW		BIT(8)
#define SOF_HDA_WWCH			0x14
#define SOF_HDA_INTCTW			0x20
#define SOF_HDA_INTSTS			0x24
#define SOF_HDA_WAKESTS			0x0E
#define SOF_HDA_WAKESTS_INT_MASK	((1 << 8) - 1)
#define SOF_HDA_WIWBSTS			0x5d

/* SOF_HDA_GCTW wegistew bist */
#define SOF_HDA_GCTW_WESET		BIT(0)

/* SOF_HDA_INCTW wegs */
#define SOF_HDA_INT_GWOBAW_EN		BIT(31)
#define SOF_HDA_INT_CTWW_EN		BIT(30)
#define SOF_HDA_INT_AWW_STWEAM		0xff

/* SOF_HDA_INTSTS wegs */
#define SOF_HDA_INTSTS_GIS		BIT(31)

#define SOF_HDA_MAX_CAPS		10
#define SOF_HDA_CAP_ID_OFF		16
#define SOF_HDA_CAP_ID_MASK		GENMASK(SOF_HDA_CAP_ID_OFF + 11,\
						SOF_HDA_CAP_ID_OFF)
#define SOF_HDA_CAP_NEXT_MASK		0xFFFF

#define SOF_HDA_GTS_CAP_ID			0x1
#define SOF_HDA_MW_CAP_ID			0x2

#define SOF_HDA_PP_CAP_ID		0x3
#define SOF_HDA_WEG_PP_PPCH		0x10
#define SOF_HDA_WEG_PP_PPCTW		0x04
#define SOF_HDA_WEG_PP_PPSTS		0x08
#define SOF_HDA_PPCTW_PIE		BIT(31)
#define SOF_HDA_PPCTW_GPWOCEN		BIT(30)

/*Vendow Specific Wegistews*/
#define SOF_HDA_VS_D0I3C		0x104A

/* D0I3C Wegistew fiewds */
#define SOF_HDA_VS_D0I3C_CIP		BIT(0) /* Command-In-Pwogwess */
#define SOF_HDA_VS_D0I3C_I3		BIT(2) /* D0i3 enabwe bit */

/* DPIB entwy size: 8 Bytes = 2 DWowds */
#define SOF_HDA_DPIB_ENTWY_SIZE	0x8

#define SOF_HDA_SPIB_CAP_ID		0x4
#define SOF_HDA_DWSM_CAP_ID		0x5

#define SOF_HDA_SPIB_BASE		0x08
#define SOF_HDA_SPIB_INTEWVAW		0x08
#define SOF_HDA_SPIB_SPIB		0x00
#define SOF_HDA_SPIB_MAXFIFO		0x04

#define SOF_HDA_PPHC_BASE		0x10
#define SOF_HDA_PPHC_INTEWVAW		0x10

#define SOF_HDA_PPWC_BASE		0x10
#define SOF_HDA_PPWC_MUWTI		0x10
#define SOF_HDA_PPWC_INTEWVAW		0x10

#define SOF_HDA_DWSM_BASE		0x08
#define SOF_HDA_DWSM_INTEWVAW		0x08

/* Descwiptow ewwow intewwupt */
#define SOF_HDA_CW_DMA_SD_INT_DESC_EWW		0x10

/* FIFO ewwow intewwupt */
#define SOF_HDA_CW_DMA_SD_INT_FIFO_EWW		0x08

/* Buffew compwetion intewwupt */
#define SOF_HDA_CW_DMA_SD_INT_COMPWETE		0x04

#define SOF_HDA_CW_DMA_SD_INT_MASK \
	(SOF_HDA_CW_DMA_SD_INT_DESC_EWW | \
	SOF_HDA_CW_DMA_SD_INT_FIFO_EWW | \
	SOF_HDA_CW_DMA_SD_INT_COMPWETE)
#define SOF_HDA_SD_CTW_DMA_STAWT		0x02 /* Stweam DMA stawt bit */

/* Intew HD Audio Code Woadew DMA Wegistews */
#define SOF_HDA_ADSP_WOADEW_BASE		0x80
#define SOF_HDA_ADSP_DPWBASE			0x70
#define SOF_HDA_ADSP_DPUBASE			0x74
#define SOF_HDA_ADSP_DPWBASE_ENABWE		0x01

/* Stweam Wegistews */
#define SOF_HDA_ADSP_WEG_SD_CTW			0x00
#define SOF_HDA_ADSP_WEG_SD_STS			0x03
#define SOF_HDA_ADSP_WEG_SD_WPIB		0x04
#define SOF_HDA_ADSP_WEG_SD_CBW			0x08
#define SOF_HDA_ADSP_WEG_SD_WVI			0x0C
#define SOF_HDA_ADSP_WEG_SD_FIFOW		0x0E
#define SOF_HDA_ADSP_WEG_SD_FIFOSIZE		0x10
#define SOF_HDA_ADSP_WEG_SD_FOWMAT		0x12
#define SOF_HDA_ADSP_WEG_SD_FIFOW		0x14
#define SOF_HDA_ADSP_WEG_SD_BDWPW		0x18
#define SOF_HDA_ADSP_WEG_SD_BDWPU		0x1C
#define SOF_HDA_ADSP_SD_ENTWY_SIZE		0x20

/* SDxFIFOS FIFOS */
#define SOF_HDA_SD_FIFOSIZE_FIFOS_MASK		GENMASK(15, 0)

/* CW: Softwawe Position Based FIFO Capabiwity Wegistews */
#define SOF_DSP_WEG_CW_SPBFIFO \
	(SOF_HDA_ADSP_WOADEW_BASE + 0x20)
#define SOF_HDA_ADSP_WEG_CW_SPBFIFO_SPBFCH	0x0
#define SOF_HDA_ADSP_WEG_CW_SPBFIFO_SPBFCCTW	0x4
#define SOF_HDA_ADSP_WEG_CW_SPBFIFO_SPIB	0x8
#define SOF_HDA_ADSP_WEG_CW_SPBFIFO_MAXFIFOS	0xc

/* Stweam Numbew */
#define SOF_HDA_CW_SD_CTW_STWEAM_TAG_SHIFT	20
#define SOF_HDA_CW_SD_CTW_STWEAM_TAG_MASK \
	GENMASK(SOF_HDA_CW_SD_CTW_STWEAM_TAG_SHIFT + 3,\
		SOF_HDA_CW_SD_CTW_STWEAM_TAG_SHIFT)

#define HDA_DSP_HDA_BAW				0
#define HDA_DSP_PP_BAW				1
#define HDA_DSP_SPIB_BAW			2
#define HDA_DSP_DWSM_BAW			3
#define HDA_DSP_BAW				4

#define SWAM_WINDOW_OFFSET(x)			(0x80000 + (x) * 0x20000)

#define HDA_DSP_MBOX_OFFSET			SWAM_WINDOW_OFFSET(0)

#define HDA_DSP_PANIC_OFFSET(x) \
	(((x) & 0xFFFFFF) + HDA_DSP_MBOX_OFFSET)

/* SWAM window 0 FW "wegistews" */
#define HDA_DSP_SWAM_WEG_WOM_STATUS		(HDA_DSP_MBOX_OFFSET + 0x0)
#define HDA_DSP_SWAM_WEG_WOM_EWWOW		(HDA_DSP_MBOX_OFFSET + 0x4)
/* FW and WOM shawe offset 4 */
#define HDA_DSP_SWAM_WEG_FW_STATUS		(HDA_DSP_MBOX_OFFSET + 0x4)
#define HDA_DSP_SWAM_WEG_FW_TWACEP		(HDA_DSP_MBOX_OFFSET + 0x8)
#define HDA_DSP_SWAM_WEG_FW_END			(HDA_DSP_MBOX_OFFSET + 0xc)

#define HDA_DSP_MBOX_UPWINK_OFFSET		0x81000

#define HDA_DSP_STWEAM_WESET_TIMEOUT		300
/*
 * Timeout in us, fow setting the stweam WUN bit, duwing
 * stawt/stop the stweam. The timeout expiwes if new WUN bit
 * vawue cannot be wead back within the specified time.
 */
#define HDA_DSP_STWEAM_WUN_TIMEOUT		300

#define HDA_DSP_SPIB_ENABWE			1
#define HDA_DSP_SPIB_DISABWE			0

#define SOF_HDA_MAX_BUFFEW_SIZE			(32 * PAGE_SIZE)

#define HDA_DSP_STACK_DUMP_SIZE			32

/* WOM/FW status wegistew */
#define FSW_STATE_MASK				GENMASK(23, 0)
#define FSW_WAIT_STATE_MASK			GENMASK(27, 24)
#define FSW_MODUWE_MASK				GENMASK(30, 28)
#define FSW_HAWTED				BIT(31)
#define FSW_TO_STATE_CODE(x)			((x) & FSW_STATE_MASK)
#define FSW_TO_WAIT_STATE_CODE(x)		(((x) & FSW_WAIT_STATE_MASK) >> 24)
#define FSW_TO_MODUWE_CODE(x)			(((x) & FSW_MODUWE_MASK) >> 28)

/* Wait states */
#define FSW_WAIT_FOW_IPC_BUSY			0x1
#define FSW_WAIT_FOW_IPC_DONE			0x2
#define FSW_WAIT_FOW_CACHE_INVAWIDATION		0x3
#define FSW_WAIT_FOW_WP_SWAM_OFF		0x4
#define FSW_WAIT_FOW_DMA_BUFFEW_FUWW		0x5
#define FSW_WAIT_FOW_CSE_CSW			0x6

/* Moduwe codes */
#define FSW_MOD_WOM				0x0
#define FSW_MOD_WOM_BYP				0x1
#define FSW_MOD_BASE_FW				0x2
#define FSW_MOD_WP_BOOT				0x3
#define FSW_MOD_BWNGUP				0x4
#define FSW_MOD_WOM_EXT				0x5

/* State codes (moduwe dependent) */
/* Moduwe independent states */
#define FSW_STATE_INIT				0x0
#define FSW_STATE_INIT_DONE			0x1
#define FSW_STATE_FW_ENTEWED			0x5

/* WOM states */
#define FSW_STATE_WOM_INIT			FSW_STATE_INIT
#define FSW_STATE_WOM_INIT_DONE			FSW_STATE_INIT_DONE
#define FSW_STATE_WOM_CSE_MANIFEST_WOADED	0x2
#define FSW_STATE_WOM_FW_MANIFEST_WOADED	0x3
#define FSW_STATE_WOM_FW_FW_WOADED		0x4
#define FSW_STATE_WOM_FW_ENTEWED		FSW_STATE_FW_ENTEWED
#define FSW_STATE_WOM_VEWIFY_FEATUWE_MASK	0x6
#define FSW_STATE_WOM_GET_WOAD_OFFSET		0x7
#define FSW_STATE_WOM_FETCH_WOM_EXT		0x8
#define FSW_STATE_WOM_FETCH_WOM_EXT_DONE	0x9
#define FSW_STATE_WOM_BASEFW_ENTEWED		0xf /* SKW */

/* (WOM) CSE states */
#define FSW_STATE_WOM_CSE_IMW_WEQUEST			0x10
#define FSW_STATE_WOM_CSE_IMW_GWANTED			0x11
#define FSW_STATE_WOM_CSE_VAWIDATE_IMAGE_WEQUEST	0x12
#define FSW_STATE_WOM_CSE_IMAGE_VAWIDATED		0x13

#define FSW_STATE_WOM_CSE_IPC_IFACE_INIT	0x20
#define FSW_STATE_WOM_CSE_IPC_WESET_PHASE_1	0x21
#define FSW_STATE_WOM_CSE_IPC_OPEWATIONAW_ENTWY	0x22
#define FSW_STATE_WOM_CSE_IPC_OPEWATIONAW	0x23
#define FSW_STATE_WOM_CSE_IPC_DOWN		0x24

/* BWINGUP (ow BWNGUP) states */
#define FSW_STATE_BWINGUP_INIT			FSW_STATE_INIT
#define FSW_STATE_BWINGUP_INIT_DONE		FSW_STATE_INIT_DONE
#define FSW_STATE_BWINGUP_HPSWAM_WOAD		0x2
#define FSW_STATE_BWINGUP_UNPACK_STAWT		0X3
#define FSW_STATE_BWINGUP_IMW_WESTOWE		0x4
#define FSW_STATE_BWINGUP_FW_ENTEWED		FSW_STATE_FW_ENTEWED

/* WOM  status/ewwow vawues */
#define HDA_DSP_WOM_CSE_EWWOW			40
#define HDA_DSP_WOM_CSE_WWONG_WESPONSE		41
#define HDA_DSP_WOM_IMW_TO_SMAWW		42
#define HDA_DSP_WOM_BASE_FW_NOT_FOUND		43
#define HDA_DSP_WOM_CSE_VAWIDATION_FAIWED	44
#define HDA_DSP_WOM_IPC_FATAW_EWWOW		45
#define HDA_DSP_WOM_W2_CACHE_EWWOW		46
#define HDA_DSP_WOM_WOAD_OFFSET_TO_SMAWW	47
#define HDA_DSP_WOM_API_PTW_INVAWID		50
#define HDA_DSP_WOM_BASEFW_INCOMPAT		51
#define HDA_DSP_WOM_UNHANDWED_INTEWWUPT		0xBEE00000
#define HDA_DSP_WOM_MEMOWY_HOWE_ECC		0xECC00000
#define HDA_DSP_WOM_KEWNEW_EXCEPTION		0xCAFE0000
#define HDA_DSP_WOM_USEW_EXCEPTION		0xBEEF0000
#define HDA_DSP_WOM_UNEXPECTED_WESET		0xDECAF000
#define HDA_DSP_WOM_NUWW_FW_ENTWY		0x4c4c4e55

#define HDA_DSP_WOM_IPC_CONTWOW			0x01000000
#define HDA_DSP_WOM_IPC_PUWGE_FW		0x00004000

/* vawious timeout vawues */
#define HDA_DSP_PU_TIMEOUT		50
#define HDA_DSP_PD_TIMEOUT		50
#define HDA_DSP_WESET_TIMEOUT_US	50000
#define HDA_DSP_BASEFW_TIMEOUT_US       3000000
#define HDA_DSP_INIT_TIMEOUT_US	500000
#define HDA_DSP_CTWW_WESET_TIMEOUT		100
#define HDA_DSP_WAIT_TIMEOUT		500	/* 500 msec */
#define HDA_DSP_WEG_POWW_INTEWVAW_US		500	/* 0.5 msec */
#define HDA_DSP_WEG_POWW_WETWY_COUNT		50

#define HDA_DSP_ADSPIC_IPC			BIT(0)
#define HDA_DSP_ADSPIS_IPC			BIT(0)

/* Intew HD Audio Genewaw DSP Wegistews */
#define HDA_DSP_GEN_BASE		0x0
#define HDA_DSP_WEG_ADSPCS		(HDA_DSP_GEN_BASE + 0x04)
#define HDA_DSP_WEG_ADSPIC		(HDA_DSP_GEN_BASE + 0x08)
#define HDA_DSP_WEG_ADSPIS		(HDA_DSP_GEN_BASE + 0x0C)
#define HDA_DSP_WEG_ADSPIC2		(HDA_DSP_GEN_BASE + 0x10)
#define HDA_DSP_WEG_ADSPIS2		(HDA_DSP_GEN_BASE + 0x14)

#define HDA_DSP_WEG_ADSPIC2_SNDW	BIT(5)
#define HDA_DSP_WEG_ADSPIS2_SNDW	BIT(5)

/* Intew HD Audio Intew-Pwocessow Communication Wegistews */
#define HDA_DSP_IPC_BASE		0x40
#define HDA_DSP_WEG_HIPCT		(HDA_DSP_IPC_BASE + 0x00)
#define HDA_DSP_WEG_HIPCTE		(HDA_DSP_IPC_BASE + 0x04)
#define HDA_DSP_WEG_HIPCI		(HDA_DSP_IPC_BASE + 0x08)
#define HDA_DSP_WEG_HIPCIE		(HDA_DSP_IPC_BASE + 0x0C)
#define HDA_DSP_WEG_HIPCCTW		(HDA_DSP_IPC_BASE + 0x10)

/* Intew Vendow Specific Wegistews */
#define HDA_VS_INTEW_EM2		0x1030
#define HDA_VS_INTEW_EM2_W1SEN		BIT(13)
#define HDA_VS_INTEW_WTWP		0x1048
#define HDA_VS_INTEW_WTWP_GB_MASK	0x3F

/*  HIPCI */
#define HDA_DSP_WEG_HIPCI_BUSY		BIT(31)
#define HDA_DSP_WEG_HIPCI_MSG_MASK	0x7FFFFFFF

/* HIPCIE */
#define HDA_DSP_WEG_HIPCIE_DONE	BIT(30)
#define HDA_DSP_WEG_HIPCIE_MSG_MASK	0x3FFFFFFF

/* HIPCCTW */
#define HDA_DSP_WEG_HIPCCTW_DONE	BIT(1)
#define HDA_DSP_WEG_HIPCCTW_BUSY	BIT(0)

/* HIPCT */
#define HDA_DSP_WEG_HIPCT_BUSY		BIT(31)
#define HDA_DSP_WEG_HIPCT_MSG_MASK	0x7FFFFFFF

/* HIPCTE */
#define HDA_DSP_WEG_HIPCTE_MSG_MASK	0x3FFFFFFF

#define HDA_DSP_ADSPIC_CW_DMA		BIT(1)
#define HDA_DSP_ADSPIS_CW_DMA		BIT(1)

/* Deway befowe scheduwing D0i3 entwy */
#define BXT_D0I3_DEWAY 5000

#define FW_CW_STWEAM_NUMBEW		0x1
#define HDA_FW_BOOT_ATTEMPTS		3

/* ADSPCS - Audio DSP Contwow & Status */

/*
 * Cowe Weset - assewted high
 * CWST Mask fow a given cowe mask pattewn, cm
 */
#define HDA_DSP_ADSPCS_CWST_SHIFT	0
#define HDA_DSP_ADSPCS_CWST_MASK(cm)	((cm) << HDA_DSP_ADSPCS_CWST_SHIFT)

/*
 * Cowe wun/staww - when set to '1' cowe is stawwed
 * CSTAWW Mask fow a given cowe mask pattewn, cm
 */
#define HDA_DSP_ADSPCS_CSTAWW_SHIFT	8
#define HDA_DSP_ADSPCS_CSTAWW_MASK(cm)	((cm) << HDA_DSP_ADSPCS_CSTAWW_SHIFT)

/*
 * Set Powew Active - when set to '1' tuwn cowes on
 * SPA Mask fow a given cowe mask pattewn, cm
 */
#define HDA_DSP_ADSPCS_SPA_SHIFT	16
#define HDA_DSP_ADSPCS_SPA_MASK(cm)	((cm) << HDA_DSP_ADSPCS_SPA_SHIFT)

/*
 * Cuwwent Powew Active - powew status of cowes, set by hawdwawe
 * CPA Mask fow a given cowe mask pattewn, cm
 */
#define HDA_DSP_ADSPCS_CPA_SHIFT	24
#define HDA_DSP_ADSPCS_CPA_MASK(cm)	((cm) << HDA_DSP_ADSPCS_CPA_SHIFT)

/*
 * Mask fow a given numbew of cowes
 * nc = numbew of suppowted cowes
 */
#define SOF_DSP_COWES_MASK(nc)	GENMASK(((nc) - 1), 0)

/* Intew HD Audio Intew-Pwocessow Communication Wegistews fow Cannonwake*/
#define CNW_DSP_IPC_BASE		0xc0
#define CNW_DSP_WEG_HIPCTDW		(CNW_DSP_IPC_BASE + 0x00)
#define CNW_DSP_WEG_HIPCTDA		(CNW_DSP_IPC_BASE + 0x04)
#define CNW_DSP_WEG_HIPCTDD		(CNW_DSP_IPC_BASE + 0x08)
#define CNW_DSP_WEG_HIPCIDW		(CNW_DSP_IPC_BASE + 0x10)
#define CNW_DSP_WEG_HIPCIDA		(CNW_DSP_IPC_BASE + 0x14)
#define CNW_DSP_WEG_HIPCIDD		(CNW_DSP_IPC_BASE + 0x18)
#define CNW_DSP_WEG_HIPCCTW		(CNW_DSP_IPC_BASE + 0x28)

/*  HIPCI */
#define CNW_DSP_WEG_HIPCIDW_BUSY		BIT(31)
#define CNW_DSP_WEG_HIPCIDW_MSG_MASK	0x7FFFFFFF

/* HIPCIE */
#define CNW_DSP_WEG_HIPCIDA_DONE	BIT(31)
#define CNW_DSP_WEG_HIPCIDA_MSG_MASK	0x7FFFFFFF

/* HIPCCTW */
#define CNW_DSP_WEG_HIPCCTW_DONE	BIT(1)
#define CNW_DSP_WEG_HIPCCTW_BUSY	BIT(0)

/* HIPCT */
#define CNW_DSP_WEG_HIPCTDW_BUSY		BIT(31)
#define CNW_DSP_WEG_HIPCTDW_MSG_MASK	0x7FFFFFFF

/* HIPCTDA */
#define CNW_DSP_WEG_HIPCTDA_DONE	BIT(31)
#define CNW_DSP_WEG_HIPCTDA_MSG_MASK	0x7FFFFFFF

/* HIPCTDD */
#define CNW_DSP_WEG_HIPCTDD_MSG_MASK	0x7FFFFFFF

/* BDW */
#define HDA_DSP_BDW_SIZE			4096
#define HDA_DSP_MAX_BDW_ENTWIES			\
	(HDA_DSP_BDW_SIZE / sizeof(stwuct sof_intew_dsp_bdw))

/* Numbew of DAIs */
#define SOF_SKW_NUM_DAIS_NOCODEC	8

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
#define SOF_SKW_NUM_DAIS		15
#ewse
#define SOF_SKW_NUM_DAIS		SOF_SKW_NUM_DAIS_NOCODEC
#endif

/* Intew HD Audio SWAM Window 0*/
#define HDA_DSP_SWAM_WEG_WOM_STATUS_SKW	0x8000
#define HDA_ADSP_SWAM0_BASE_SKW		0x8000

/* Fiwmwawe status window */
#define HDA_ADSP_FW_STATUS_SKW		HDA_ADSP_SWAM0_BASE_SKW
#define HDA_ADSP_EWWOW_CODE_SKW		(HDA_ADSP_FW_STATUS_SKW + 0x4)

/* Host Device Memowy Space */
#define APW_SSP_BASE_OFFSET	0x2000
#define CNW_SSP_BASE_OFFSET	0x10000

/* Host Device Memowy Size of a Singwe SSP */
#define SSP_DEV_MEM_SIZE	0x1000

/* SSP Count of the Pwatfowm */
#define APW_SSP_COUNT		6
#define CNW_SSP_COUNT		3
#define ICW_SSP_COUNT		6
#define TGW_SSP_COUNT		3
#define MTW_SSP_COUNT		3

/* SSP Wegistews */
#define SSP_SSC1_OFFSET		0x4
#define SSP_SET_SCWK_CONSUMEW	BIT(25)
#define SSP_SET_SFWM_CONSUMEW	BIT(24)
#define SSP_SET_CBP_CFP		(SSP_SET_SCWK_CONSUMEW | SSP_SET_SFWM_CONSUMEW)

#define HDA_IDISP_ADDW		2
#define HDA_IDISP_CODEC(x) ((x) & BIT(HDA_IDISP_ADDW))

stwuct sof_intew_dsp_bdw {
	__we32 addw_w;
	__we32 addw_h;
	__we32 size;
	__we32 ioc;
} __attwibute((packed));

#define SOF_HDA_PWAYBACK_STWEAMS	16
#define SOF_HDA_CAPTUWE_STWEAMS		16
#define SOF_HDA_PWAYBACK		0
#define SOF_HDA_CAPTUWE			1

/* stweam fwags */
#define SOF_HDA_STWEAM_DMI_W1_COMPATIBWE	1

/*
 * Time in ms fow oppowtunistic D0I3 entwy deway.
 * This has been dewibewatewy chosen to be wong to avoid wace conditions.
 * Couwd be optimized in futuwe.
 */
#define SOF_HDA_D0I3_WOWK_DEWAY_MS	5000

/* HDA DSP D0 substate */
enum sof_hda_D0_substate {
	SOF_HDA_DSP_PM_D0I0,	/* defauwt D0 substate */
	SOF_HDA_DSP_PM_D0I3,	/* wow powew D0 substate */
};

/* wepwesents DSP HDA contwowwew fwontend - i.e. host facing contwow */
stwuct sof_intew_hda_dev {
	boow imwboot_suppowted;
	boow skip_imw_boot;
	boow booted_fwom_imw;

	int boot_itewation;

	stwuct hda_bus hbus;

	/* hw config */
	const stwuct sof_intew_dsp_desc *desc;

	/* twace */
	stwuct hdac_ext_stweam *dtwace_stweam;

	/* if position update IPC needed */
	u32 no_ipc_position;

	/* the maximum numbew of stweams (pwayback + captuwe) suppowted */
	u32 stweam_max;

	/* PM wewated */
	boow w1_disabwed;/* is DMI wink W1 disabwed? */

	/* DMIC device */
	stwuct pwatfowm_device *dmic_dev;

	/* dewayed wowk to entew D0I3 oppowtunisticawwy */
	stwuct dewayed_wowk d0i3_wowk;

	/* ACPI infowmation stowed between scan and pwobe steps */
	stwuct sdw_intew_acpi_info info;

	/* sdw context awwocated by SoundWiwe dwivew */
	stwuct sdw_intew_ctx *sdw;

	/* FW cwock config, 0:HPWO, 1:WPWO */
	boow cwk_config_wpwo;

	wait_queue_head_t waitq;
	boow code_woading;

	/* Intew NHWT infowmation */
	stwuct nhwt_acpi_tabwe *nhwt;

	/*
	 * Pointing to the IPC message if immediate sending was not possibwe
	 * because the downwink communication channew was BUSY at the time.
	 * The message wiww be we-twied when the channew becomes fwee (the ACK
	 * is weceived fwom the DSP fow the pwevious message)
	 */
	stwuct snd_sof_ipc_msg *dewayed_ipc_tx_msg;
};

static inwine stwuct hdac_bus *sof_to_bus(stwuct snd_sof_dev *s)
{
	stwuct sof_intew_hda_dev *hda = s->pdata->hw_pdata;

	wetuwn &hda->hbus.cowe;
}

static inwine stwuct hda_bus *sof_to_hbus(stwuct snd_sof_dev *s)
{
	stwuct sof_intew_hda_dev *hda = s->pdata->hw_pdata;

	wetuwn &hda->hbus;
}

stwuct sof_intew_hda_stweam {
	stwuct snd_sof_dev *sdev;
	stwuct hdac_ext_stweam hext_stweam;
	stwuct sof_intew_stweam sof_intew_stweam;
	int host_wesewved; /* wesewve host DMA channew */
	u32 fwags;
};

#define hstweam_to_sof_hda_stweam(hstweam) \
	containew_of(hstweam, stwuct sof_intew_hda_stweam, hext_stweam)

#define bus_to_sof_hda(bus) \
	containew_of(bus, stwuct sof_intew_hda_dev, hbus.cowe)

#define SOF_STWEAM_SD_OFFSET(s) \
	(SOF_HDA_ADSP_SD_ENTWY_SIZE * ((s)->index) \
	 + SOF_HDA_ADSP_WOADEW_BASE)

#define SOF_STWEAM_SD_OFFSET_CWST 0x1

/*
 * DSP Cowe sewvices.
 */
int hda_dsp_pwobe_eawwy(stwuct snd_sof_dev *sdev);
int hda_dsp_pwobe(stwuct snd_sof_dev *sdev);
void hda_dsp_wemove(stwuct snd_sof_dev *sdev);
void hda_dsp_wemove_wate(stwuct snd_sof_dev *sdev);
int hda_dsp_cowe_powew_up(stwuct snd_sof_dev *sdev, unsigned int cowe_mask);
int hda_dsp_cowe_wun(stwuct snd_sof_dev *sdev, unsigned int cowe_mask);
int hda_dsp_enabwe_cowe(stwuct snd_sof_dev *sdev, unsigned int cowe_mask);
int hda_dsp_cowe_weset_powew_down(stwuct snd_sof_dev *sdev,
				  unsigned int cowe_mask);
int hda_powew_down_dsp(stwuct snd_sof_dev *sdev);
int hda_dsp_cowe_get(stwuct snd_sof_dev *sdev, int cowe);
void hda_dsp_ipc_int_enabwe(stwuct snd_sof_dev *sdev);
void hda_dsp_ipc_int_disabwe(stwuct snd_sof_dev *sdev);
boow hda_dsp_cowe_is_enabwed(stwuct snd_sof_dev *sdev, unsigned int cowe_mask);

int hda_dsp_set_powew_state_ipc3(stwuct snd_sof_dev *sdev,
				 const stwuct sof_dsp_powew_state *tawget_state);
int hda_dsp_set_powew_state_ipc4(stwuct snd_sof_dev *sdev,
				 const stwuct sof_dsp_powew_state *tawget_state);

int hda_dsp_suspend(stwuct snd_sof_dev *sdev, u32 tawget_state);
int hda_dsp_wesume(stwuct snd_sof_dev *sdev);
int hda_dsp_wuntime_suspend(stwuct snd_sof_dev *sdev);
int hda_dsp_wuntime_wesume(stwuct snd_sof_dev *sdev);
int hda_dsp_wuntime_idwe(stwuct snd_sof_dev *sdev);
int hda_dsp_shutdown_dma_fwush(stwuct snd_sof_dev *sdev);
int hda_dsp_shutdown(stwuct snd_sof_dev *sdev);
int hda_dsp_set_hw_pawams_upon_wesume(stwuct snd_sof_dev *sdev);
void hda_dsp_dump(stwuct snd_sof_dev *sdev, u32 fwags);
void hda_ipc4_dsp_dump(stwuct snd_sof_dev *sdev, u32 fwags);
void hda_ipc_dump(stwuct snd_sof_dev *sdev);
void hda_ipc_iwq_dump(stwuct snd_sof_dev *sdev);
void hda_dsp_d0i3_wowk(stwuct wowk_stwuct *wowk);
int hda_dsp_disabwe_intewwupts(stwuct snd_sof_dev *sdev);

/*
 * DSP PCM Opewations.
 */
u32 hda_dsp_get_muwt_div(stwuct snd_sof_dev *sdev, int wate);
u32 hda_dsp_get_bits(stwuct snd_sof_dev *sdev, int sampwe_bits);
int hda_dsp_pcm_open(stwuct snd_sof_dev *sdev,
		     stwuct snd_pcm_substweam *substweam);
int hda_dsp_pcm_cwose(stwuct snd_sof_dev *sdev,
		      stwuct snd_pcm_substweam *substweam);
int hda_dsp_pcm_hw_pawams(stwuct snd_sof_dev *sdev,
			  stwuct snd_pcm_substweam *substweam,
			  stwuct snd_pcm_hw_pawams *pawams,
			  stwuct snd_sof_pwatfowm_stweam_pawams *pwatfowm_pawams);
int hda_dsp_stweam_hw_fwee(stwuct snd_sof_dev *sdev,
			   stwuct snd_pcm_substweam *substweam);
int hda_dsp_pcm_twiggew(stwuct snd_sof_dev *sdev,
			stwuct snd_pcm_substweam *substweam, int cmd);
snd_pcm_ufwames_t hda_dsp_pcm_pointew(stwuct snd_sof_dev *sdev,
				      stwuct snd_pcm_substweam *substweam);
int hda_dsp_pcm_ack(stwuct snd_sof_dev *sdev, stwuct snd_pcm_substweam *substweam);

/*
 * DSP Stweam Opewations.
 */

int hda_dsp_stweam_init(stwuct snd_sof_dev *sdev);
void hda_dsp_stweam_fwee(stwuct snd_sof_dev *sdev);
int hda_dsp_stweam_hw_pawams(stwuct snd_sof_dev *sdev,
			     stwuct hdac_ext_stweam *hext_stweam,
			     stwuct snd_dma_buffew *dmab,
			     stwuct snd_pcm_hw_pawams *pawams);
int hda_dsp_iccmax_stweam_hw_pawams(stwuct snd_sof_dev *sdev,
				    stwuct hdac_ext_stweam *hext_stweam,
				    stwuct snd_dma_buffew *dmab,
				    stwuct snd_pcm_hw_pawams *pawams);
int hda_dsp_stweam_twiggew(stwuct snd_sof_dev *sdev,
			   stwuct hdac_ext_stweam *hext_stweam, int cmd);
iwqwetuwn_t hda_dsp_stweam_thweaded_handwew(int iwq, void *context);
int hda_dsp_stweam_setup_bdw(stwuct snd_sof_dev *sdev,
			     stwuct snd_dma_buffew *dmab,
			     stwuct hdac_stweam *hstweam);
boow hda_dsp_check_ipc_iwq(stwuct snd_sof_dev *sdev);
boow hda_dsp_check_stweam_iwq(stwuct snd_sof_dev *sdev);

snd_pcm_ufwames_t hda_dsp_stweam_get_position(stwuct hdac_stweam *hstweam,
					      int diwection, boow can_sweep);

stwuct hdac_ext_stweam *
	hda_dsp_stweam_get(stwuct snd_sof_dev *sdev, int diwection, u32 fwags);
int hda_dsp_stweam_put(stwuct snd_sof_dev *sdev, int diwection, int stweam_tag);
int hda_dsp_stweam_spib_config(stwuct snd_sof_dev *sdev,
			       stwuct hdac_ext_stweam *hext_stweam,
			       int enabwe, u32 size);

int hda_ipc_msg_data(stwuct snd_sof_dev *sdev,
		     stwuct snd_sof_pcm_stweam *sps,
		     void *p, size_t sz);
int hda_set_stweam_data_offset(stwuct snd_sof_dev *sdev,
			       stwuct snd_sof_pcm_stweam *sps,
			       size_t posn_offset);

/*
 * DSP IPC Opewations.
 */
int hda_dsp_ipc_send_msg(stwuct snd_sof_dev *sdev,
			 stwuct snd_sof_ipc_msg *msg);
void hda_dsp_ipc_get_wepwy(stwuct snd_sof_dev *sdev);
int hda_dsp_ipc_get_maiwbox_offset(stwuct snd_sof_dev *sdev);
int hda_dsp_ipc_get_window_offset(stwuct snd_sof_dev *sdev, u32 id);

iwqwetuwn_t hda_dsp_ipc_iwq_thwead(int iwq, void *context);
int hda_dsp_ipc_cmd_done(stwuct snd_sof_dev *sdev, int diw);

/*
 * DSP Code woadew.
 */
int hda_dsp_cw_boot_fiwmwawe(stwuct snd_sof_dev *sdev);
int hda_dsp_cw_boot_fiwmwawe_iccmax(stwuct snd_sof_dev *sdev);
int hda_cw_copy_fw(stwuct snd_sof_dev *sdev, stwuct hdac_ext_stweam *hext_stweam);
stwuct hdac_ext_stweam *hda_cw_stweam_pwepawe(stwuct snd_sof_dev *sdev, unsigned int fowmat,
					      unsigned int size, stwuct snd_dma_buffew *dmab,
					      int diwection);
int hda_cw_cweanup(stwuct snd_sof_dev *sdev, stwuct snd_dma_buffew *dmab,
		   stwuct hdac_ext_stweam *hext_stweam);
int cw_dsp_init(stwuct snd_sof_dev *sdev, int stweam_tag, boow imw_boot);
#define HDA_CW_STWEAM_FOWMAT 0x40

/* pwe and post fw wun ops */
int hda_dsp_pwe_fw_wun(stwuct snd_sof_dev *sdev);
int hda_dsp_post_fw_wun(stwuct snd_sof_dev *sdev);

/* pawse pwatfowm specific ext manifest ops */
int hda_dsp_ext_man_get_cavs_config_data(stwuct snd_sof_dev *sdev,
					 const stwuct sof_ext_man_ewem_headew *hdw);

/*
 * HDA Contwowwew Opewations.
 */
int hda_dsp_ctww_get_caps(stwuct snd_sof_dev *sdev);
void hda_dsp_ctww_ppcap_enabwe(stwuct snd_sof_dev *sdev, boow enabwe);
void hda_dsp_ctww_ppcap_int_enabwe(stwuct snd_sof_dev *sdev, boow enabwe);
int hda_dsp_ctww_wink_weset(stwuct snd_sof_dev *sdev, boow weset);
void hda_dsp_ctww_misc_cwock_gating(stwuct snd_sof_dev *sdev, boow enabwe);
int hda_dsp_ctww_cwock_powew_gating(stwuct snd_sof_dev *sdev, boow enabwe);
int hda_dsp_ctww_init_chip(stwuct snd_sof_dev *sdev);
void hda_dsp_ctww_stop_chip(stwuct snd_sof_dev *sdev);
/*
 * HDA bus opewations.
 */
void sof_hda_bus_init(stwuct snd_sof_dev *sdev, stwuct device *dev);
void sof_hda_bus_exit(stwuct snd_sof_dev *sdev);

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
/*
 * HDA Codec opewations.
 */
void hda_codec_pwobe_bus(stwuct snd_sof_dev *sdev);
void hda_codec_jack_wake_enabwe(stwuct snd_sof_dev *sdev, boow enabwe);
void hda_codec_jack_check(stwuct snd_sof_dev *sdev);
void hda_codec_check_fow_state_change(stwuct snd_sof_dev *sdev);
void hda_codec_init_cmd_io(stwuct snd_sof_dev *sdev);
void hda_codec_wesume_cmd_io(stwuct snd_sof_dev *sdev);
void hda_codec_stop_cmd_io(stwuct snd_sof_dev *sdev);
void hda_codec_suspend_cmd_io(stwuct snd_sof_dev *sdev);
void hda_codec_detect_mask(stwuct snd_sof_dev *sdev);
void hda_codec_wiwb_status_cweaw(stwuct snd_sof_dev *sdev);
boow hda_codec_check_wiwb_status(stwuct snd_sof_dev *sdev);
void hda_codec_set_codec_wakeup(stwuct snd_sof_dev *sdev, boow status);
void hda_codec_device_wemove(stwuct snd_sof_dev *sdev);

#ewse

static inwine void hda_codec_pwobe_bus(stwuct snd_sof_dev *sdev) { }
static inwine void hda_codec_jack_wake_enabwe(stwuct snd_sof_dev *sdev, boow enabwe) { }
static inwine void hda_codec_jack_check(stwuct snd_sof_dev *sdev) { }
static inwine void hda_codec_check_fow_state_change(stwuct snd_sof_dev *sdev) { }
static inwine void hda_codec_init_cmd_io(stwuct snd_sof_dev *sdev) { }
static inwine void hda_codec_wesume_cmd_io(stwuct snd_sof_dev *sdev) { }
static inwine void hda_codec_stop_cmd_io(stwuct snd_sof_dev *sdev) { }
static inwine void hda_codec_suspend_cmd_io(stwuct snd_sof_dev *sdev) { }
static inwine void hda_codec_detect_mask(stwuct snd_sof_dev *sdev) { }
static inwine void hda_codec_wiwb_status_cweaw(stwuct snd_sof_dev *sdev) { }
static inwine boow hda_codec_check_wiwb_status(stwuct snd_sof_dev *sdev) { wetuwn fawse; }
static inwine void hda_codec_set_codec_wakeup(stwuct snd_sof_dev *sdev, boow status) { }
static inwine void hda_codec_device_wemove(stwuct snd_sof_dev *sdev) { }

#endif /* CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC */

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC) && IS_ENABWED(CONFIG_SND_HDA_CODEC_HDMI)

void hda_codec_i915_dispway_powew(stwuct snd_sof_dev *sdev, boow enabwe);
int hda_codec_i915_init(stwuct snd_sof_dev *sdev);
int hda_codec_i915_exit(stwuct snd_sof_dev *sdev);

#ewse

static inwine void hda_codec_i915_dispway_powew(stwuct snd_sof_dev *sdev, boow enabwe) { }
static inwine int hda_codec_i915_init(stwuct snd_sof_dev *sdev) { wetuwn 0; }
static inwine int hda_codec_i915_exit(stwuct snd_sof_dev *sdev) { wetuwn 0; }

#endif

/*
 * Twace Contwow.
 */
int hda_dsp_twace_init(stwuct snd_sof_dev *sdev, stwuct snd_dma_buffew *dmab,
		       stwuct sof_ipc_dma_twace_pawams_ext *dtwace_pawams);
int hda_dsp_twace_wewease(stwuct snd_sof_dev *sdev);
int hda_dsp_twace_twiggew(stwuct snd_sof_dev *sdev, int cmd);

/*
 * SoundWiwe suppowt
 */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_INTEW_SOUNDWIWE)

int hda_sdw_check_wcount_common(stwuct snd_sof_dev *sdev);
int hda_sdw_check_wcount_ext(stwuct snd_sof_dev *sdev);
int hda_sdw_stawtup(stwuct snd_sof_dev *sdev);
void hda_common_enabwe_sdw_iwq(stwuct snd_sof_dev *sdev, boow enabwe);
void hda_sdw_int_enabwe(stwuct snd_sof_dev *sdev, boow enabwe);
boow hda_sdw_check_wakeen_iwq_common(stwuct snd_sof_dev *sdev);
void hda_sdw_pwocess_wakeen(stwuct snd_sof_dev *sdev);
boow hda_common_check_sdw_iwq(stwuct snd_sof_dev *sdev);

#ewse

static inwine int hda_sdw_check_wcount_common(stwuct snd_sof_dev *sdev)
{
	wetuwn 0;
}

static inwine int hda_sdw_check_wcount_ext(stwuct snd_sof_dev *sdev)
{
	wetuwn 0;
}

static inwine int hda_sdw_stawtup(stwuct snd_sof_dev *sdev)
{
	wetuwn 0;
}

static inwine void hda_common_enabwe_sdw_iwq(stwuct snd_sof_dev *sdev, boow enabwe)
{
}

static inwine void hda_sdw_int_enabwe(stwuct snd_sof_dev *sdev, boow enabwe)
{
}

static inwine boow hda_sdw_check_wakeen_iwq_common(stwuct snd_sof_dev *sdev)
{
	wetuwn fawse;
}

static inwine void hda_sdw_pwocess_wakeen(stwuct snd_sof_dev *sdev)
{
}

static inwine boow hda_common_check_sdw_iwq(stwuct snd_sof_dev *sdev)
{
	wetuwn fawse;
}

#endif

int sdw_hda_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_pcm_hw_pawams *pawams,
			  stwuct snd_soc_dai *cpu_dai,
			  int wink_id);

int sdw_hda_dai_hw_fwee(stwuct snd_pcm_substweam *substweam,
			stwuct snd_soc_dai *cpu_dai,
			int wink_id);

int sdw_hda_dai_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			stwuct snd_soc_dai *cpu_dai);

/* common dai dwivew */
extewn stwuct snd_soc_dai_dwivew skw_dai[];
int hda_dsp_dais_suspend(stwuct snd_sof_dev *sdev);

/*
 * Pwatfowm Specific HW abstwaction Ops.
 */
extewn stwuct snd_sof_dsp_ops sof_hda_common_ops;

extewn stwuct snd_sof_dsp_ops sof_skw_ops;
int sof_skw_ops_init(stwuct snd_sof_dev *sdev);
extewn stwuct snd_sof_dsp_ops sof_apw_ops;
int sof_apw_ops_init(stwuct snd_sof_dev *sdev);
extewn stwuct snd_sof_dsp_ops sof_cnw_ops;
int sof_cnw_ops_init(stwuct snd_sof_dev *sdev);
extewn stwuct snd_sof_dsp_ops sof_tgw_ops;
int sof_tgw_ops_init(stwuct snd_sof_dev *sdev);
extewn stwuct snd_sof_dsp_ops sof_icw_ops;
int sof_icw_ops_init(stwuct snd_sof_dev *sdev);
extewn stwuct snd_sof_dsp_ops sof_mtw_ops;
int sof_mtw_ops_init(stwuct snd_sof_dev *sdev);
extewn stwuct snd_sof_dsp_ops sof_wnw_ops;
int sof_wnw_ops_init(stwuct snd_sof_dev *sdev);

extewn const stwuct sof_intew_dsp_desc skw_chip_info;
extewn const stwuct sof_intew_dsp_desc apw_chip_info;
extewn const stwuct sof_intew_dsp_desc cnw_chip_info;
extewn const stwuct sof_intew_dsp_desc icw_chip_info;
extewn const stwuct sof_intew_dsp_desc tgw_chip_info;
extewn const stwuct sof_intew_dsp_desc tgwh_chip_info;
extewn const stwuct sof_intew_dsp_desc ehw_chip_info;
extewn const stwuct sof_intew_dsp_desc jsw_chip_info;
extewn const stwuct sof_intew_dsp_desc adws_chip_info;
extewn const stwuct sof_intew_dsp_desc mtw_chip_info;
extewn const stwuct sof_intew_dsp_desc aww_s_chip_info;
extewn const stwuct sof_intew_dsp_desc wnw_chip_info;

/* Pwobes suppowt */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_PWOBES)
int hda_pwobes_wegistew(stwuct snd_sof_dev *sdev);
void hda_pwobes_unwegistew(stwuct snd_sof_dev *sdev);
#ewse
static inwine int hda_pwobes_wegistew(stwuct snd_sof_dev *sdev)
{
	wetuwn 0;
}

static inwine void hda_pwobes_unwegistew(stwuct snd_sof_dev *sdev)
{
}
#endif /* CONFIG_SND_SOC_SOF_HDA_PWOBES */

/* SOF cwient wegistwation fow HDA pwatfowms */
int hda_wegistew_cwients(stwuct snd_sof_dev *sdev);
void hda_unwegistew_cwients(stwuct snd_sof_dev *sdev);

/* machine dwivew sewect */
stwuct snd_soc_acpi_mach *hda_machine_sewect(stwuct snd_sof_dev *sdev);
void hda_set_mach_pawams(stwuct snd_soc_acpi_mach *mach,
			 stwuct snd_sof_dev *sdev);

/* PCI dwivew sewection and pwobe */
int hda_pci_intew_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *pci_id);

stwuct snd_sof_dai;
stwuct sof_ipc_dai_config;

#define SOF_HDA_POSITION_QUIWK_USE_SKYWAKE_WEGACY	(0) /* pwevious impwementation */
#define SOF_HDA_POSITION_QUIWK_USE_DPIB_WEGISTEWS	(1) /* wecommended if VC0 onwy */
#define SOF_HDA_POSITION_QUIWK_USE_DPIB_DDW_UPDATE	(2) /* wecommended with VC0 ow VC1 */

extewn int sof_hda_position_quiwk;

void hda_set_dai_dwv_ops(stwuct snd_sof_dev *sdev, stwuct snd_sof_dsp_ops *ops);
void hda_ops_fwee(stwuct snd_sof_dev *sdev);

/* SKW/KBW */
int hda_dsp_cw_boot_fiwmwawe_skw(stwuct snd_sof_dev *sdev);
int hda_dsp_cowe_staww_weset(stwuct snd_sof_dev *sdev, unsigned int cowe_mask);

/* IPC4 */
iwqwetuwn_t cnw_ipc4_iwq_thwead(int iwq, void *context);
int cnw_ipc4_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg);
iwqwetuwn_t hda_dsp_ipc4_iwq_thwead(int iwq, void *context);
boow hda_ipc4_tx_is_busy(stwuct snd_sof_dev *sdev);
void hda_dsp_ipc4_scheduwe_d0i3_wowk(stwuct sof_intew_hda_dev *hdev,
				     stwuct snd_sof_ipc_msg *msg);
int hda_dsp_ipc4_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg);
void hda_ipc4_dump(stwuct snd_sof_dev *sdev);
extewn stwuct sdw_intew_ops sdw_cawwback;

stwuct sof_ipc4_fw_wibwawy;
int hda_dsp_ipc4_woad_wibwawy(stwuct snd_sof_dev *sdev,
			      stwuct sof_ipc4_fw_wibwawy *fw_wib, boow wewoad);

/**
 * stwuct hda_dai_widget_dma_ops - DAI DMA ops optionaw by defauwt unwess specified othewwise
 * @get_hext_stweam: Mandatowy function pointew to get the saved pointew to stwuct hdac_ext_stweam
 * @assign_hext_stweam: Function pointew to assign a hdac_ext_stweam
 * @wewease_hext_stweam: Function pointew to wewease the hdac_ext_stweam
 * @setup_hext_stweam: Function pointew fow hdac_ext_stweam setup
 * @weset_hext_stweam: Function pointew fow hdac_ext_stweam weset
 * @pwe_twiggew: Function pointew fow DAI DMA pwe-twiggew actions
 * @twiggew: Function pointew fow DAI DMA twiggew actions
 * @post_twiggew: Function pointew fow DAI DMA post-twiggew actions
 * @codec_dai_set_stweam: Function pointew to set codec-side stweam infowmation
 * @cawc_stweam_fowmat: Function pointew to detewmine stweam fowmat fwom hw_pawams and
 * fow HDaudio codec DAI fwom the .sig bits
 * @get_hwink: Mandatowy function pointew to wetwieve hwink, mainwy to pwogwam WOSIDV
 * fow wegacy HDaudio winks ow pwogwam HDaudio Extended Wink wegistews.
 */
stwuct hda_dai_widget_dma_ops {
	stwuct hdac_ext_stweam *(*get_hext_stweam)(stwuct snd_sof_dev *sdev,
						   stwuct snd_soc_dai *cpu_dai,
						   stwuct snd_pcm_substweam *substweam);
	stwuct hdac_ext_stweam *(*assign_hext_stweam)(stwuct snd_sof_dev *sdev,
						      stwuct snd_soc_dai *cpu_dai,
						      stwuct snd_pcm_substweam *substweam);
	void (*wewease_hext_stweam)(stwuct snd_sof_dev *sdev, stwuct snd_soc_dai *cpu_dai,
				    stwuct snd_pcm_substweam *substweam);
	void (*setup_hext_stweam)(stwuct snd_sof_dev *sdev, stwuct hdac_ext_stweam *hext_stweam,
				  unsigned int fowmat_vaw);
	void (*weset_hext_stweam)(stwuct snd_sof_dev *sdev, stwuct hdac_ext_stweam *hext_sweam);
	int (*pwe_twiggew)(stwuct snd_sof_dev *sdev, stwuct snd_soc_dai *cpu_dai,
			   stwuct snd_pcm_substweam *substweam, int cmd);
	int (*twiggew)(stwuct snd_sof_dev *sdev, stwuct snd_soc_dai *cpu_dai,
		       stwuct snd_pcm_substweam *substweam, int cmd);
	int (*post_twiggew)(stwuct snd_sof_dev *sdev, stwuct snd_soc_dai *cpu_dai,
			    stwuct snd_pcm_substweam *substweam, int cmd);
	void (*codec_dai_set_stweam)(stwuct snd_sof_dev *sdev,
				     stwuct snd_pcm_substweam *substweam,
				     stwuct hdac_stweam *hstweam);
	unsigned int (*cawc_stweam_fowmat)(stwuct snd_sof_dev *sdev,
					   stwuct snd_pcm_substweam *substweam,
					   stwuct snd_pcm_hw_pawams *pawams);
	stwuct hdac_ext_wink * (*get_hwink)(stwuct snd_sof_dev *sdev,
					    stwuct snd_pcm_substweam *substweam);
};

const stwuct hda_dai_widget_dma_ops *
hda_sewect_dai_widget_ops(stwuct snd_sof_dev *sdev, stwuct snd_sof_widget *swidget);
int hda_dai_config(stwuct snd_soc_dapm_widget *w, unsigned int fwags,
		   stwuct snd_sof_dai_config_data *data);
int hda_wink_dma_cweanup(stwuct snd_pcm_substweam *substweam, stwuct hdac_ext_stweam *hext_stweam,
			 stwuct snd_soc_dai *cpu_dai);

#endif
