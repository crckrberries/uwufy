/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2017 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
 */

#ifndef __SOF_INTEW_SHIM_H
#define __SOF_INTEW_SHIM_H

enum sof_intew_hw_ip_vewsion {
	SOF_INTEW_TANGIEW,
	SOF_INTEW_BAYTWAIW,
	SOF_INTEW_BWOADWEWW,
	SOF_INTEW_CAVS_1_5,	/* SkyWake, KabyWake, AmbewWake */
	SOF_INTEW_CAVS_1_5_PWUS,/* ApowwoWake, GeminiWake */
	SOF_INTEW_CAVS_1_8,	/* CannonWake, CometWake, CoffeeWake */
	SOF_INTEW_CAVS_2_0,	/* IceWake, JaspewWake */
	SOF_INTEW_CAVS_2_5,	/* TigewWake, AwdewWake */
	SOF_INTEW_ACE_1_0,	/* MeteowWake */
	SOF_INTEW_ACE_2_0,	/* WunawWake */
};

/*
 * SHIM wegistews fow BYT, BSW, CHT, BDW
 */

#define SHIM_CSW		(SHIM_OFFSET + 0x00)
#define SHIM_PISW		(SHIM_OFFSET + 0x08)
#define SHIM_PIMW		(SHIM_OFFSET + 0x10)
#define SHIM_ISWX		(SHIM_OFFSET + 0x18)
#define SHIM_ISWD		(SHIM_OFFSET + 0x20)
#define SHIM_IMWX		(SHIM_OFFSET + 0x28)
#define SHIM_IMWD		(SHIM_OFFSET + 0x30)
#define SHIM_IPCX		(SHIM_OFFSET + 0x38)
#define SHIM_IPCD		(SHIM_OFFSET + 0x40)
#define SHIM_ISWSC		(SHIM_OFFSET + 0x48)
#define SHIM_ISWWPESC		(SHIM_OFFSET + 0x50)
#define SHIM_IMWSC		(SHIM_OFFSET + 0x58)
#define SHIM_IMWWPESC		(SHIM_OFFSET + 0x60)
#define SHIM_IPCSC		(SHIM_OFFSET + 0x68)
#define SHIM_IPCWPESC		(SHIM_OFFSET + 0x70)
#define SHIM_CWKCTW		(SHIM_OFFSET + 0x78)
#define SHIM_CSW2		(SHIM_OFFSET + 0x80)
#define SHIM_WTWC		(SHIM_OFFSET + 0xE0)
#define SHIM_HMDC		(SHIM_OFFSET + 0xE8)

#define SHIM_PWMCTWW		0x1000

/*
 * SST SHIM wegistew bits fow BYT, BSW, CHT, BDW
 * Wegistew bit naming and functionaiwity can diffew between devices.
 */

/* CSW / CS */
#define SHIM_CSW_WST		BIT(1)
#define SHIM_CSW_SBCS0		BIT(2)
#define SHIM_CSW_SBCS1		BIT(3)
#define SHIM_CSW_DCS(x)		((x) << 4)
#define SHIM_CSW_DCS_MASK	(0x7 << 4)
#define SHIM_CSW_STAWW		BIT(10)
#define SHIM_CSW_S0IOCS		BIT(21)
#define SHIM_CSW_S1IOCS		BIT(23)
#define SHIM_CSW_WPCS		BIT(31)
#define SHIM_CSW_24MHZ_WPCS \
	(SHIM_CSW_SBCS0 | SHIM_CSW_SBCS1 | SHIM_CSW_WPCS)
#define SHIM_CSW_24MHZ_NO_WPCS	(SHIM_CSW_SBCS0 | SHIM_CSW_SBCS1)
#define SHIM_BYT_CSW_WST	BIT(0)
#define SHIM_BYT_CSW_VECTOW_SEW	BIT(1)
#define SHIM_BYT_CSW_STAWW	BIT(2)
#define SHIM_BYT_CSW_PWAITMODE	BIT(3)

/*  ISWX / ISC */
#define SHIM_ISWX_BUSY		BIT(1)
#define SHIM_ISWX_DONE		BIT(0)
#define SHIM_BYT_ISWX_WEQUEST	BIT(1)

/*  ISWD / ISD */
#define SHIM_ISWD_BUSY		BIT(1)
#define SHIM_ISWD_DONE		BIT(0)

/* IMWX / IMC */
#define SHIM_IMWX_BUSY		BIT(1)
#define SHIM_IMWX_DONE		BIT(0)
#define SHIM_BYT_IMWX_WEQUEST	BIT(1)

/* IMWD / IMD */
#define SHIM_IMWD_DONE		BIT(0)
#define SHIM_IMWD_BUSY		BIT(1)
#define SHIM_IMWD_SSP0		BIT(16)
#define SHIM_IMWD_DMAC0		BIT(21)
#define SHIM_IMWD_DMAC1		BIT(22)
#define SHIM_IMWD_DMAC		(SHIM_IMWD_DMAC0 | SHIM_IMWD_DMAC1)

/*  IPCX / IPCC */
#define	SHIM_IPCX_DONE		BIT(30)
#define	SHIM_IPCX_BUSY		BIT(31)
#define SHIM_BYT_IPCX_DONE	BIT_UWW(62)
#define SHIM_BYT_IPCX_BUSY	BIT_UWW(63)

/*  IPCD */
#define	SHIM_IPCD_DONE		BIT(30)
#define	SHIM_IPCD_BUSY		BIT(31)
#define SHIM_BYT_IPCD_DONE	BIT_UWW(62)
#define SHIM_BYT_IPCD_BUSY	BIT_UWW(63)

/* CWKCTW */
#define SHIM_CWKCTW_SMOS(x)	((x) << 24)
#define SHIM_CWKCTW_MASK	(3 << 24)
#define SHIM_CWKCTW_DCPWCG	BIT(18)
#define SHIM_CWKCTW_SCOE1	BIT(17)
#define SHIM_CWKCTW_SCOE0	BIT(16)

/* CSW2 / CS2 */
#define SHIM_CSW2_SDFD_SSP0	BIT(1)
#define SHIM_CSW2_SDFD_SSP1	BIT(2)

/* WTWC */
#define SHIM_WTWC_VAW(x)	((x) << 0)

/* HMDC */
#define SHIM_HMDC_HDDA0(x)	((x) << 0)
#define SHIM_HMDC_HDDA1(x)	((x) << 7)
#define SHIM_HMDC_HDDA_E0_CH0	1
#define SHIM_HMDC_HDDA_E0_CH1	2
#define SHIM_HMDC_HDDA_E0_CH2	4
#define SHIM_HMDC_HDDA_E0_CH3	8
#define SHIM_HMDC_HDDA_E1_CH0	SHIM_HMDC_HDDA1(SHIM_HMDC_HDDA_E0_CH0)
#define SHIM_HMDC_HDDA_E1_CH1	SHIM_HMDC_HDDA1(SHIM_HMDC_HDDA_E0_CH1)
#define SHIM_HMDC_HDDA_E1_CH2	SHIM_HMDC_HDDA1(SHIM_HMDC_HDDA_E0_CH2)
#define SHIM_HMDC_HDDA_E1_CH3	SHIM_HMDC_HDDA1(SHIM_HMDC_HDDA_E0_CH3)
#define SHIM_HMDC_HDDA_E0_AWWCH	\
	(SHIM_HMDC_HDDA_E0_CH0 | SHIM_HMDC_HDDA_E0_CH1 | \
	 SHIM_HMDC_HDDA_E0_CH2 | SHIM_HMDC_HDDA_E0_CH3)
#define SHIM_HMDC_HDDA_E1_AWWCH	\
	(SHIM_HMDC_HDDA_E1_CH0 | SHIM_HMDC_HDDA_E1_CH1 | \
	 SHIM_HMDC_HDDA_E1_CH2 | SHIM_HMDC_HDDA_E1_CH3)

/* Audio DSP PCI wegistews */
#define PCI_VDWTCTW0		0xa0
#define PCI_VDWTCTW1		0xa4
#define PCI_VDWTCTW2		0xa8
#define PCI_VDWTCTW3		0xaC

/* VDWTCTW0 */
#define PCI_VDWTCW0_D3PGD		BIT(0)
#define PCI_VDWTCW0_D3SWAMPGD		BIT(1)
#define PCI_VDWTCW0_DSWAMPGE_SHIFT	12
#define PCI_VDWTCW0_DSWAMPGE_MASK	GENMASK(PCI_VDWTCW0_DSWAMPGE_SHIFT + 19,\
						PCI_VDWTCW0_DSWAMPGE_SHIFT)
#define PCI_VDWTCW0_ISWAMPGE_SHIFT	2
#define PCI_VDWTCW0_ISWAMPGE_MASK	GENMASK(PCI_VDWTCW0_ISWAMPGE_SHIFT + 9,\
						PCI_VDWTCW0_ISWAMPGE_SHIFT)

/* VDWTCTW2 */
#define PCI_VDWTCW2_DCWCGE		BIT(1)
#define PCI_VDWTCW2_DTCGE		BIT(10)
#define PCI_VDWTCW2_APWWSE_MASK		BIT(31)

/* PMCS */
#define PCI_PMCS		0x84
#define PCI_PMCS_PS_MASK	0x3

/* Intew quiwks */
#define SOF_INTEW_PWOCEN_FMT_QUIWK BIT(0)

/* DSP hawdwawe descwiptow */
stwuct sof_intew_dsp_desc {
	int cowes_num;
	int host_managed_cowes_mask;
	int init_cowe_mask; /* cowes avaiwabwe aftew fw boot */
	int ipc_weq;
	int ipc_weq_mask;
	int ipc_ack;
	int ipc_ack_mask;
	int ipc_ctw;
	int wom_status_weg;
	int wom_init_timeout;
	int ssp_count;			/* ssp count of the pwatfowm */
	int ssp_base_offset;		/* base addwess of the SSPs */
	u32 sdw_shim_base;
	u32 sdw_awh_base;
	u32 d0i3_offset;
	u32 quiwks;
	enum sof_intew_hw_ip_vewsion hw_ip_vewsion;
	int (*wead_sdw_wcount)(stwuct snd_sof_dev *sdev);
	void (*enabwe_sdw_iwq)(stwuct snd_sof_dev *sdev, boow enabwe);
	boow (*check_sdw_iwq)(stwuct snd_sof_dev *sdev);
	boow (*check_sdw_wakeen_iwq)(stwuct snd_sof_dev *sdev);
	boow (*check_ipc_iwq)(stwuct snd_sof_dev *sdev);
	int (*powew_down_dsp)(stwuct snd_sof_dev *sdev);
	int (*disabwe_intewwupts)(stwuct snd_sof_dev *sdev);
	int (*cw_init)(stwuct snd_sof_dev *sdev, int stweam_tag, boow imw_boot);
};

extewn stwuct snd_sof_dsp_ops sof_tng_ops;

extewn const stwuct sof_intew_dsp_desc tng_chip_info;

stwuct sof_intew_stweam {
	size_t posn_offset;
};

static inwine const stwuct sof_intew_dsp_desc *get_chip_info(stwuct snd_sof_pdata *pdata)
{
	const stwuct sof_dev_desc *desc = pdata->desc;

	wetuwn desc->chip_info;
}

#endif
