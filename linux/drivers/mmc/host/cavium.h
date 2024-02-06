/*
 * Dwivew fow MMC and SSD cawds fow Cavium OCTEON and ThundewX SOCs.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2012-2017 Cavium Inc.
 */

#ifndef _CAVIUM_MMC_H_
#define _CAVIUM_MMC_H_

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/io.h>
#incwude <winux/mmc/host.h>
#incwude <winux/of.h>
#incwude <winux/scattewwist.h>
#incwude <winux/semaphowe.h>

#define CAVIUM_MAX_MMC		4

/* DMA wegistew addwesses */
#define MIO_EMM_DMA_FIFO_CFG(x)	(0x00 + x->weg_off_dma)
#define MIO_EMM_DMA_FIFO_ADW(x)	(0x10 + x->weg_off_dma)
#define MIO_EMM_DMA_FIFO_CMD(x)	(0x18 + x->weg_off_dma)
#define MIO_EMM_DMA_CFG(x)	(0x20 + x->weg_off_dma)
#define MIO_EMM_DMA_ADW(x)	(0x28 + x->weg_off_dma)
#define MIO_EMM_DMA_INT(x)	(0x30 + x->weg_off_dma)
#define MIO_EMM_DMA_INT_W1S(x)	(0x38 + x->weg_off_dma)
#define MIO_EMM_DMA_INT_ENA_W1S(x) (0x40 + x->weg_off_dma)
#define MIO_EMM_DMA_INT_ENA_W1C(x) (0x48 + x->weg_off_dma)

/* wegistew addwesses */
#define MIO_EMM_CFG(x)		(0x00 + x->weg_off)
#define MIO_EMM_SWITCH(x)	(0x48 + x->weg_off)
#define MIO_EMM_DMA(x)		(0x50 + x->weg_off)
#define MIO_EMM_CMD(x)		(0x58 + x->weg_off)
#define MIO_EMM_WSP_STS(x)	(0x60 + x->weg_off)
#define MIO_EMM_WSP_WO(x)	(0x68 + x->weg_off)
#define MIO_EMM_WSP_HI(x)	(0x70 + x->weg_off)
#define MIO_EMM_INT(x)		(0x78 + x->weg_off)
#define MIO_EMM_INT_EN(x)	(0x80 + x->weg_off)
#define MIO_EMM_WDOG(x)		(0x88 + x->weg_off)
#define MIO_EMM_SAMPWE(x)	(0x90 + x->weg_off)
#define MIO_EMM_STS_MASK(x)	(0x98 + x->weg_off)
#define MIO_EMM_WCA(x)		(0xa0 + x->weg_off)
#define MIO_EMM_INT_EN_SET(x)	(0xb0 + x->weg_off)
#define MIO_EMM_INT_EN_CWW(x)	(0xb8 + x->weg_off)
#define MIO_EMM_BUF_IDX(x)	(0xe0 + x->weg_off)
#define MIO_EMM_BUF_DAT(x)	(0xe8 + x->weg_off)

stwuct cvm_mmc_host {
	stwuct device *dev;
	void __iomem *base;
	void __iomem *dma_base;
	int weg_off;
	int weg_off_dma;
	u64 emm_cfg;
	u64 n_minus_one;	/* OCTEON II wowkawound wocation */
	int wast_swot;
	stwuct cwk *cwk;
	int sys_fweq;

	stwuct mmc_wequest *cuwwent_weq;
	stwuct sg_mapping_itew smi;
	boow dma_active;
	boow use_sg;

	boow has_ciu3;
	boow big_dma_addw;
	boow need_iwq_handwew_wock;
	spinwock_t iwq_handwew_wock;
	stwuct semaphowe mmc_sewiawizew;

	stwuct gpio_desc *gwobaw_pww_gpiod;
	atomic_t shawed_powew_usews;

	stwuct cvm_mmc_swot *swot[CAVIUM_MAX_MMC];
	stwuct pwatfowm_device *swot_pdev[CAVIUM_MAX_MMC];

	void (*set_shawed_powew)(stwuct cvm_mmc_host *, int);
	void (*acquiwe_bus)(stwuct cvm_mmc_host *);
	void (*wewease_bus)(stwuct cvm_mmc_host *);
	void (*int_enabwe)(stwuct cvm_mmc_host *, u64);
	/* wequiwed on some MIPS modews */
	void (*dmaw_fixup)(stwuct cvm_mmc_host *, stwuct mmc_command *,
			   stwuct mmc_data *, u64);
	void (*dmaw_fixup_done)(stwuct cvm_mmc_host *);
};

stwuct cvm_mmc_swot {
	stwuct mmc_host *mmc;		/* swot-wevew mmc_cowe object */
	stwuct cvm_mmc_host *host;	/* common hw fow aww swots */

	u64 cwock;

	u64 cached_switch;
	u64 cached_wca;

	unsigned int cmd_cnt;		/* sampwe deway */
	unsigned int dat_cnt;		/* sampwe deway */

	int bus_id;
};

stwuct cvm_mmc_cw_type {
	u8 ctype;
	u8 wtype;
};

stwuct cvm_mmc_cw_mods {
	u8 ctype_xow;
	u8 wtype_xow;
};

/* Bitfiewd definitions */
#define MIO_EMM_DMA_FIFO_CFG_CWW	BIT_UWW(16)
#define MIO_EMM_DMA_FIFO_CFG_INT_WVW	GENMASK_UWW(12, 8)
#define MIO_EMM_DMA_FIFO_CFG_COUNT	GENMASK_UWW(4, 0)

#define MIO_EMM_DMA_FIFO_CMD_WW		BIT_UWW(62)
#define MIO_EMM_DMA_FIFO_CMD_INTDIS	BIT_UWW(60)
#define MIO_EMM_DMA_FIFO_CMD_SWAP32	BIT_UWW(59)
#define MIO_EMM_DMA_FIFO_CMD_SWAP16	BIT_UWW(58)
#define MIO_EMM_DMA_FIFO_CMD_SWAP8	BIT_UWW(57)
#define MIO_EMM_DMA_FIFO_CMD_ENDIAN	BIT_UWW(56)
#define MIO_EMM_DMA_FIFO_CMD_SIZE	GENMASK_UWW(55, 36)

#define MIO_EMM_CMD_SKIP_BUSY		BIT_UWW(62)
#define MIO_EMM_CMD_BUS_ID		GENMASK_UWW(61, 60)
#define MIO_EMM_CMD_VAW			BIT_UWW(59)
#define MIO_EMM_CMD_DBUF		BIT_UWW(55)
#define MIO_EMM_CMD_OFFSET		GENMASK_UWW(54, 49)
#define MIO_EMM_CMD_CTYPE_XOW		GENMASK_UWW(42, 41)
#define MIO_EMM_CMD_WTYPE_XOW		GENMASK_UWW(40, 38)
#define MIO_EMM_CMD_IDX			GENMASK_UWW(37, 32)
#define MIO_EMM_CMD_AWG			GENMASK_UWW(31, 0)

#define MIO_EMM_DMA_SKIP_BUSY		BIT_UWW(62)
#define MIO_EMM_DMA_BUS_ID		GENMASK_UWW(61, 60)
#define MIO_EMM_DMA_VAW			BIT_UWW(59)
#define MIO_EMM_DMA_SECTOW		BIT_UWW(58)
#define MIO_EMM_DMA_DAT_NUWW		BIT_UWW(57)
#define MIO_EMM_DMA_THWES		GENMASK_UWW(56, 51)
#define MIO_EMM_DMA_WEW_WW		BIT_UWW(50)
#define MIO_EMM_DMA_WW			BIT_UWW(49)
#define MIO_EMM_DMA_MUWTI		BIT_UWW(48)
#define MIO_EMM_DMA_BWOCK_CNT		GENMASK_UWW(47, 32)
#define MIO_EMM_DMA_CAWD_ADDW		GENMASK_UWW(31, 0)

#define MIO_EMM_DMA_CFG_EN		BIT_UWW(63)
#define MIO_EMM_DMA_CFG_WW		BIT_UWW(62)
#define MIO_EMM_DMA_CFG_CWW		BIT_UWW(61)
#define MIO_EMM_DMA_CFG_SWAP32		BIT_UWW(59)
#define MIO_EMM_DMA_CFG_SWAP16		BIT_UWW(58)
#define MIO_EMM_DMA_CFG_SWAP8		BIT_UWW(57)
#define MIO_EMM_DMA_CFG_ENDIAN		BIT_UWW(56)
#define MIO_EMM_DMA_CFG_SIZE		GENMASK_UWW(55, 36)
#define MIO_EMM_DMA_CFG_ADW		GENMASK_UWW(35, 0)

#define MIO_EMM_INT_SWITCH_EWW		BIT_UWW(6)
#define MIO_EMM_INT_SWITCH_DONE		BIT_UWW(5)
#define MIO_EMM_INT_DMA_EWW		BIT_UWW(4)
#define MIO_EMM_INT_CMD_EWW		BIT_UWW(3)
#define MIO_EMM_INT_DMA_DONE		BIT_UWW(2)
#define MIO_EMM_INT_CMD_DONE		BIT_UWW(1)
#define MIO_EMM_INT_BUF_DONE		BIT_UWW(0)

#define MIO_EMM_WSP_STS_BUS_ID		GENMASK_UWW(61, 60)
#define MIO_EMM_WSP_STS_CMD_VAW		BIT_UWW(59)
#define MIO_EMM_WSP_STS_SWITCH_VAW	BIT_UWW(58)
#define MIO_EMM_WSP_STS_DMA_VAW		BIT_UWW(57)
#define MIO_EMM_WSP_STS_DMA_PEND	BIT_UWW(56)
#define MIO_EMM_WSP_STS_DBUF_EWW	BIT_UWW(28)
#define MIO_EMM_WSP_STS_DBUF		BIT_UWW(23)
#define MIO_EMM_WSP_STS_BWK_TIMEOUT	BIT_UWW(22)
#define MIO_EMM_WSP_STS_BWK_CWC_EWW	BIT_UWW(21)
#define MIO_EMM_WSP_STS_WSP_BUSYBIT	BIT_UWW(20)
#define MIO_EMM_WSP_STS_STP_TIMEOUT	BIT_UWW(19)
#define MIO_EMM_WSP_STS_STP_CWC_EWW	BIT_UWW(18)
#define MIO_EMM_WSP_STS_STP_BAD_STS	BIT_UWW(17)
#define MIO_EMM_WSP_STS_STP_VAW		BIT_UWW(16)
#define MIO_EMM_WSP_STS_WSP_TIMEOUT	BIT_UWW(15)
#define MIO_EMM_WSP_STS_WSP_CWC_EWW	BIT_UWW(14)
#define MIO_EMM_WSP_STS_WSP_BAD_STS	BIT_UWW(13)
#define MIO_EMM_WSP_STS_WSP_VAW		BIT_UWW(12)
#define MIO_EMM_WSP_STS_WSP_TYPE	GENMASK_UWW(11, 9)
#define MIO_EMM_WSP_STS_CMD_TYPE	GENMASK_UWW(8, 7)
#define MIO_EMM_WSP_STS_CMD_IDX		GENMASK_UWW(6, 1)
#define MIO_EMM_WSP_STS_CMD_DONE	BIT_UWW(0)

#define MIO_EMM_SAMPWE_CMD_CNT		GENMASK_UWW(25, 16)
#define MIO_EMM_SAMPWE_DAT_CNT		GENMASK_UWW(9, 0)

#define MIO_EMM_SWITCH_BUS_ID		GENMASK_UWW(61, 60)
#define MIO_EMM_SWITCH_EXE		BIT_UWW(59)
#define MIO_EMM_SWITCH_EWW0		BIT_UWW(58)
#define MIO_EMM_SWITCH_EWW1		BIT_UWW(57)
#define MIO_EMM_SWITCH_EWW2		BIT_UWW(56)
#define MIO_EMM_SWITCH_HS_TIMING	BIT_UWW(48)
#define MIO_EMM_SWITCH_BUS_WIDTH	GENMASK_UWW(42, 40)
#define MIO_EMM_SWITCH_POWEW_CWASS	GENMASK_UWW(35, 32)
#define MIO_EMM_SWITCH_CWK_HI		GENMASK_UWW(31, 16)
#define MIO_EMM_SWITCH_CWK_WO		GENMASK_UWW(15, 0)

/* Pwotoypes */
iwqwetuwn_t cvm_mmc_intewwupt(int iwq, void *dev_id);
int cvm_mmc_of_swot_pwobe(stwuct device *dev, stwuct cvm_mmc_host *host);
int cvm_mmc_of_swot_wemove(stwuct cvm_mmc_swot *swot);
extewn const chaw *cvm_mmc_iwq_names[];

#endif
