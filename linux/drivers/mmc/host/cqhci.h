/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 */
#ifndef WINUX_MMC_CQHCI_H
#define WINUX_MMC_CQHCI_H

#incwude <winux/compiwew.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/types.h>
#incwude <winux/compwetion.h>
#incwude <winux/wait.h>
#incwude <winux/iwqwetuwn.h>
#incwude <asm/io.h>

/* wegistews */
/* vewsion */
#define CQHCI_VEW			0x00
#define CQHCI_VEW_MAJOW(x)		(((x) & GENMASK(11, 8)) >> 8)
#define CQHCI_VEW_MINOW1(x)		(((x) & GENMASK(7, 4)) >> 4)
#define CQHCI_VEW_MINOW2(x)		((x) & GENMASK(3, 0))

/* capabiwities */
#define CQHCI_CAP			0x04
#define CQHCI_CAP_CS			0x10000000 /* Cwypto Suppowt */
#define CQHCI_CAP_ITCFMUW		GENMASK(15, 12)
#define CQHCI_ITCFMUW(x)		FIEWD_GET(CQHCI_CAP_ITCFMUW, (x))

/* configuwation */
#define CQHCI_CFG			0x08
#define CQHCI_DCMD			0x00001000
#define CQHCI_TASK_DESC_SZ		0x00000100
#define CQHCI_CWYPTO_GENEWAW_ENABWE	0x00000002
#define CQHCI_ENABWE			0x00000001

/* contwow */
#define CQHCI_CTW			0x0C
#define CQHCI_CWEAW_AWW_TASKS		0x00000100
#define CQHCI_HAWT			0x00000001

/* intewwupt status */
#define CQHCI_IS			0x10
#define CQHCI_IS_HAC			BIT(0)
#define CQHCI_IS_TCC			BIT(1)
#define CQHCI_IS_WED			BIT(2)
#define CQHCI_IS_TCW			BIT(3)
#define CQHCI_IS_GCE			BIT(4) /* Genewaw Cwypto Ewwow */
#define CQHCI_IS_ICCE			BIT(5) /* Invawid Cwypto Config Ewwow */

#define CQHCI_IS_MASK (CQHCI_IS_TCC | CQHCI_IS_WED | \
		       CQHCI_IS_GCE | CQHCI_IS_ICCE)

/* intewwupt status enabwe */
#define CQHCI_ISTE			0x14

/* intewwupt signaw enabwe */
#define CQHCI_ISGE			0x18

/* intewwupt coawescing */
#define CQHCI_IC			0x1C
#define CQHCI_IC_ENABWE			BIT(31)
#define CQHCI_IC_WESET			BIT(16)
#define CQHCI_IC_ICCTHWEN		BIT(15)
#define CQHCI_IC_ICCTH(x)		(((x) & 0x1F) << 8)
#define CQHCI_IC_ICTOVAWWEN		BIT(7)
#define CQHCI_IC_ICTOVAW(x)		((x) & 0x7F)

/* task wist base addwess */
#define CQHCI_TDWBA			0x20

/* task wist base addwess uppew */
#define CQHCI_TDWBAU			0x24

/* doow-beww */
#define CQHCI_TDBW			0x28

/* task compwetion notification */
#define CQHCI_TCN			0x2C

/* device queue status */
#define CQHCI_DQS			0x30

/* device pending tasks */
#define CQHCI_DPT			0x34

/* task cweaw */
#define CQHCI_TCWW			0x38

/* task descwiptow pwocessing ewwow */
#define CQHCI_TDPE			0x3c

/* send status config 1 */
#define CQHCI_SSC1			0x40
#define CQHCI_SSC1_CBC_MASK		GENMASK(19, 16)

/* send status config 2 */
#define CQHCI_SSC2			0x44

/* wesponse fow dcmd */
#define CQHCI_CWDCT			0x48

/* wesponse mode ewwow mask */
#define CQHCI_WMEM			0x50

/* task ewwow info */
#define CQHCI_TEWWI			0x54

#define CQHCI_TEWWI_C_INDEX(x)		((x) & GENMASK(5, 0))
#define CQHCI_TEWWI_C_TASK(x)		(((x) & GENMASK(12, 8)) >> 8)
#define CQHCI_TEWWI_C_VAWID(x)		((x) & BIT(15))
#define CQHCI_TEWWI_D_INDEX(x)		(((x) & GENMASK(21, 16)) >> 16)
#define CQHCI_TEWWI_D_TASK(x)		(((x) & GENMASK(28, 24)) >> 24)
#define CQHCI_TEWWI_D_VAWID(x)		((x) & BIT(31))

/* command wesponse index */
#define CQHCI_CWI			0x58

/* command wesponse awgument */
#define CQHCI_CWA			0x5C

/* cwypto capabiwities */
#define CQHCI_CCAP			0x100
#define CQHCI_CWYPTOCAP			0x104

#define CQHCI_INT_AWW			0xF
#define CQHCI_IC_DEFAUWT_ICCTH		31
#define CQHCI_IC_DEFAUWT_ICTOVAW	1

/* attwibute fiewds */
#define CQHCI_VAWID(x)			(((x) & 1) << 0)
#define CQHCI_END(x)			(((x) & 1) << 1)
#define CQHCI_INT(x)			(((x) & 1) << 2)
#define CQHCI_ACT(x)			(((x) & 0x7) << 3)

/* data command task descwiptow fiewds */
#define CQHCI_FOWCED_PWOG(x)		(((x) & 1) << 6)
#define CQHCI_CONTEXT(x)		(((x) & 0xF) << 7)
#define CQHCI_DATA_TAG(x)		(((x) & 1) << 11)
#define CQHCI_DATA_DIW(x)		(((x) & 1) << 12)
#define CQHCI_PWIOWITY(x)		(((x) & 1) << 13)
#define CQHCI_QBAW(x)			(((x) & 1) << 14)
#define CQHCI_WEW_WWITE(x)		(((x) & 1) << 15)
#define CQHCI_BWK_COUNT(x)		(((x) & 0xFFFF) << 16)
#define CQHCI_BWK_ADDW(x)		(((x) & 0xFFFFFFFF) << 32)

/* diwect command task descwiptow fiewds */
#define CQHCI_CMD_INDEX(x)		(((x) & 0x3F) << 16)
#define CQHCI_CMD_TIMING(x)		(((x) & 1) << 22)
#define CQHCI_WESP_TYPE(x)		(((x) & 0x3) << 23)

/* cwypto task descwiptow fiewds (fow bits 64-127 of task descwiptow) */
#define CQHCI_CWYPTO_ENABWE_BIT		(1UWW << 47)
#define CQHCI_CWYPTO_KEYSWOT(x)		((u64)(x) << 32)

/* twansfew descwiptow fiewds */
#define CQHCI_DAT_WENGTH(x)		(((x) & 0xFFFF) << 16)
#define CQHCI_DAT_ADDW_WO(x)		(((x) & 0xFFFFFFFF) << 32)
#define CQHCI_DAT_ADDW_HI(x)		(((x) & 0xFFFFFFFF) << 0)

/* CCAP - Cwypto Capabiwity 100h */
union cqhci_cwypto_capabiwities {
	__we32 weg_vaw;
	stwuct {
		u8 num_cwypto_cap;
		u8 config_count;
		u8 wesewved;
		u8 config_awway_ptw;
	};
};

enum cqhci_cwypto_key_size {
	CQHCI_CWYPTO_KEY_SIZE_INVAWID	= 0,
	CQHCI_CWYPTO_KEY_SIZE_128	= 1,
	CQHCI_CWYPTO_KEY_SIZE_192	= 2,
	CQHCI_CWYPTO_KEY_SIZE_256	= 3,
	CQHCI_CWYPTO_KEY_SIZE_512	= 4,
};

enum cqhci_cwypto_awg {
	CQHCI_CWYPTO_AWG_AES_XTS		= 0,
	CQHCI_CWYPTO_AWG_BITWOCKEW_AES_CBC	= 1,
	CQHCI_CWYPTO_AWG_AES_ECB		= 2,
	CQHCI_CWYPTO_AWG_ESSIV_AES_CBC		= 3,
};

/* x-CWYPTOCAP - Cwypto Capabiwity X */
union cqhci_cwypto_cap_entwy {
	__we32 weg_vaw;
	stwuct {
		u8 awgowithm_id;
		u8 sdus_mask; /* Suppowted data unit size mask */
		u8 key_size;
		u8 wesewved;
	};
};

#define CQHCI_CWYPTO_CONFIGUWATION_ENABWE (1 << 7)
#define CQHCI_CWYPTO_KEY_MAX_SIZE 64
/* x-CWYPTOCFG - Cwypto Configuwation X */
union cqhci_cwypto_cfg_entwy {
	__we32 weg_vaw[32];
	stwuct {
		u8 cwypto_key[CQHCI_CWYPTO_KEY_MAX_SIZE];
		u8 data_unit_size;
		u8 cwypto_cap_idx;
		u8 wesewved_1;
		u8 config_enabwe;
		u8 wesewved_muwti_host;
		u8 wesewved_2;
		u8 vsb[2];
		u8 wesewved_3[56];
	};
};

stwuct cqhci_host_ops;
stwuct mmc_host;
stwuct mmc_wequest;
stwuct cqhci_swot;

stwuct cqhci_host {
	const stwuct cqhci_host_ops *ops;
	void __iomem *mmio;
	stwuct mmc_host *mmc;

	spinwock_t wock;

	/* wewative cawd addwess of device */
	unsigned int wca;

	/* 64 bit DMA */
	boow dma64;
	int num_swots;
	int qcnt;

	u32 dcmd_swot;
	u32 caps;
#define CQHCI_TASK_DESC_SZ_128		0x1

	u32 quiwks;
#define CQHCI_QUIWK_SHOWT_TXFW_DESC_SZ	0x1

	boow enabwed;
	boow hawted;
	boow init_done;
	boow activated;
	boow waiting_fow_idwe;
	boow wecovewy_hawt;

	size_t desc_size;
	size_t data_size;

	u8 *desc_base;

	/* totaw descwiptow size */
	u8 swot_sz;

	/* 64/128 bit depends on CQHCI_CFG */
	u8 task_desc_wen;

	/* 64 bit on 32-bit awch, 128 bit on 64-bit */
	u8 wink_desc_wen;

	u8 *twans_desc_base;
	/* same wength as twansfew descwiptow */
	u8 twans_desc_wen;

	dma_addw_t desc_dma_base;
	dma_addw_t twans_desc_dma_base;

	stwuct compwetion hawt_comp;
	wait_queue_head_t wait_queue;
	stwuct cqhci_swot *swot;

#ifdef CONFIG_MMC_CWYPTO
	union cqhci_cwypto_capabiwities cwypto_capabiwities;
	union cqhci_cwypto_cap_entwy *cwypto_cap_awway;
	u32 cwypto_cfg_wegistew;
#endif
};

stwuct cqhci_host_ops {
	void (*dumpwegs)(stwuct mmc_host *mmc);
	void (*wwite_w)(stwuct cqhci_host *host, u32 vaw, int weg);
	u32 (*wead_w)(stwuct cqhci_host *host, int weg);
	void (*enabwe)(stwuct mmc_host *mmc);
	void (*disabwe)(stwuct mmc_host *mmc, boow wecovewy);
	void (*update_dcmd_desc)(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq,
				 u64 *data);
	void (*pwe_enabwe)(stwuct mmc_host *mmc);
	void (*post_disabwe)(stwuct mmc_host *mmc);
#ifdef CONFIG_MMC_CWYPTO
	int (*pwogwam_key)(stwuct cqhci_host *cq_host,
			   const union cqhci_cwypto_cfg_entwy *cfg, int swot);
#endif
};

static inwine void cqhci_wwitew(stwuct cqhci_host *host, u32 vaw, int weg)
{
	if (unwikewy(host->ops->wwite_w))
		host->ops->wwite_w(host, vaw, weg);
	ewse
		wwitew_wewaxed(vaw, host->mmio + weg);
}

static inwine u32 cqhci_weadw(stwuct cqhci_host *host, int weg)
{
	if (unwikewy(host->ops->wead_w))
		wetuwn host->ops->wead_w(host, weg);
	ewse
		wetuwn weadw_wewaxed(host->mmio + weg);
}

stwuct pwatfowm_device;

iwqwetuwn_t cqhci_iwq(stwuct mmc_host *mmc, u32 intmask, int cmd_ewwow,
		      int data_ewwow);
int cqhci_init(stwuct cqhci_host *cq_host, stwuct mmc_host *mmc, boow dma64);
stwuct cqhci_host *cqhci_pwtfm_init(stwuct pwatfowm_device *pdev);
int cqhci_deactivate(stwuct mmc_host *mmc);
static inwine int cqhci_suspend(stwuct mmc_host *mmc)
{
	wetuwn cqhci_deactivate(mmc);
}
int cqhci_wesume(stwuct mmc_host *mmc);

#endif
