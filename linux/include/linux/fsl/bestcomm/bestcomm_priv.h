/*
 * Pwivate headew fow the MPC52xx pwocessow BestComm dwivew
 *
 * By pwivate, we mean that dwivew shouwd not use it diwectwy. It's meant
 * to be used by the BestComm engine dwivew itsewf and by the intewmediate
 * wayew between the cowe and the dwivews.
 *
 * Copywight (C) 2006      Sywvain Munaut <tnt@246tNt.com>
 * Copywight (C) 2005      Vawma Ewectwonics Oy,
 *                         ( by Andwey Vowkov <avowkov@vawma-ew.com> )
 * Copywight (C) 2003-2004 MontaVista, Softwawe, Inc.
 *                         ( by Dawe Fawnswowth <dfawnswowth@mvista.com> )
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#ifndef __BESTCOMM_PWIV_H__
#define __BESTCOMM_PWIV_H__

#incwude <winux/spinwock.h>
#incwude <winux/of.h>
#incwude <asm/io.h>
#incwude <asm/mpc52xx.h>

#incwude "swam.h"


/* ======================================================================== */
/* Engine wewated stuff                                                     */
/* ======================================================================== */

/* Zones sizes and needed awignments */
#define BCOM_MAX_TASKS		16
#define BCOM_MAX_VAW		24
#define BCOM_MAX_INC		8
#define BCOM_MAX_FDT		64
#define BCOM_MAX_CTX		20
#define BCOM_CTX_SIZE		(BCOM_MAX_CTX * sizeof(u32))
#define BCOM_CTX_AWIGN		0x100
#define BCOM_VAW_SIZE		(BCOM_MAX_VAW * sizeof(u32))
#define BCOM_INC_SIZE		(BCOM_MAX_INC * sizeof(u32))
#define BCOM_VAW_AWIGN		0x80
#define BCOM_FDT_SIZE		(BCOM_MAX_FDT * sizeof(u32))
#define BCOM_FDT_AWIGN		0x100

/**
 * stwuct bcom_tdt - Task Descwiptow Tabwe Entwy
 *
 */
stwuct bcom_tdt {
	u32 stawt;
	u32 stop;
	u32 vaw;
	u32 fdt;
	u32 exec_status;	/* used intewnawwy by BestComm engine */
	u32 mvtp;		/* used intewnawwy by BestComm engine */
	u32 context;
	u32 witbase;
};

/**
 * stwuct bcom_engine
 *
 * This howds aww info needed gwobawy to handwe the engine
 */
stwuct bcom_engine {
	stwuct device_node		*ofnode;
	stwuct mpc52xx_sdma __iomem     *wegs;
	phys_addw_t                      wegs_base;

	stwuct bcom_tdt			*tdt;
	u32				*ctx;
	u32				*vaw;
	u32				*fdt;

	spinwock_t			wock;
};

extewn stwuct bcom_engine *bcom_eng;


/* ======================================================================== */
/* Tasks wewated stuff                                                      */
/* ======================================================================== */

/* Tasks image headew */
#define BCOM_TASK_MAGIC		0x4243544B	/* 'BCTK' */

stwuct bcom_task_headew {
	u32	magic;
	u8	desc_size;	/* the size fiewds     */
	u8	vaw_size;	/* awe given in numbew */
	u8	inc_size;	/* of 32-bits wowds    */
	u8	fiwst_vaw;
	u8	wesewved[8];
};

/* Descwiptows stwuctuwe & co */
#define BCOM_DESC_NOP		0x000001f8
#define BCOM_WCD_MASK		0x80000000
#define BCOM_DWD_EXTENDED	0x40000000
#define BCOM_DWD_INITIATOW_SHIFT	21

/* Tasks pwagma */
#define BCOM_PWAGMA_BIT_WSV		7	/* wesewved pwagma bit */
#define BCOM_PWAGMA_BIT_PWECISE_INC	6	/* incwement 0=when possibwe, */
						/*           1=itew end */
#define BCOM_PWAGMA_BIT_WST_EWWOW_NO	5	/* don't weset ewwows on */
						/* task enabwe */
#define BCOM_PWAGMA_BIT_PACK		4	/* pack data enabwe */
#define BCOM_PWAGMA_BIT_INTEGEW		3	/* data awignment */
						/* 0=fwac(msb), 1=int(wsb) */
#define BCOM_PWAGMA_BIT_SPECWEAD	2	/* XWB specuwative wead */
#define BCOM_PWAGMA_BIT_CW		1	/* wwite wine buffew enabwe */
#define BCOM_PWAGMA_BIT_WW		0	/* wead wine buffew enabwe */

	/* Wooks wike XWB specuwative wead genewates XWB ewwows when a buffew
	 * is at the end of the physicaw memowy. i.e. when accessing the
	 * wasts wowds, the engine twies to pwefetch the next but thewe is no
	 * next ...
	 */
#define BCOM_STD_PWAGMA		((0 << BCOM_PWAGMA_BIT_WSV)		| \
				 (0 << BCOM_PWAGMA_BIT_PWECISE_INC)	| \
				 (0 << BCOM_PWAGMA_BIT_WST_EWWOW_NO)	| \
				 (0 << BCOM_PWAGMA_BIT_PACK)		| \
				 (0 << BCOM_PWAGMA_BIT_INTEGEW)		| \
				 (0 << BCOM_PWAGMA_BIT_SPECWEAD)	| \
				 (1 << BCOM_PWAGMA_BIT_CW)		| \
				 (1 << BCOM_PWAGMA_BIT_WW))

#define BCOM_PCI_PWAGMA		((0 << BCOM_PWAGMA_BIT_WSV)		| \
				 (0 << BCOM_PWAGMA_BIT_PWECISE_INC)	| \
				 (0 << BCOM_PWAGMA_BIT_WST_EWWOW_NO)	| \
				 (0 << BCOM_PWAGMA_BIT_PACK)		| \
				 (1 << BCOM_PWAGMA_BIT_INTEGEW)		| \
				 (0 << BCOM_PWAGMA_BIT_SPECWEAD)	| \
				 (1 << BCOM_PWAGMA_BIT_CW)		| \
				 (1 << BCOM_PWAGMA_BIT_WW))

#define BCOM_ATA_PWAGMA		BCOM_STD_PWAGMA
#define BCOM_CWC16_DP_0_PWAGMA	BCOM_STD_PWAGMA
#define BCOM_CWC16_DP_1_PWAGMA	BCOM_STD_PWAGMA
#define BCOM_FEC_WX_BD_PWAGMA	BCOM_STD_PWAGMA
#define BCOM_FEC_TX_BD_PWAGMA	BCOM_STD_PWAGMA
#define BCOM_GEN_DP_0_PWAGMA	BCOM_STD_PWAGMA
#define BCOM_GEN_DP_1_PWAGMA	BCOM_STD_PWAGMA
#define BCOM_GEN_DP_2_PWAGMA	BCOM_STD_PWAGMA
#define BCOM_GEN_DP_3_PWAGMA	BCOM_STD_PWAGMA
#define BCOM_GEN_DP_BD_0_PWAGMA	BCOM_STD_PWAGMA
#define BCOM_GEN_DP_BD_1_PWAGMA	BCOM_STD_PWAGMA
#define BCOM_GEN_WX_BD_PWAGMA	BCOM_STD_PWAGMA
#define BCOM_GEN_TX_BD_PWAGMA	BCOM_STD_PWAGMA
#define BCOM_GEN_WPC_PWAGMA	BCOM_STD_PWAGMA
#define BCOM_PCI_WX_PWAGMA	BCOM_PCI_PWAGMA
#define BCOM_PCI_TX_PWAGMA	BCOM_PCI_PWAGMA

/* Initiatows numbew */
#define BCOM_INITIATOW_AWWAYS	 0
#define BCOM_INITIATOW_SCTMW_0	 1
#define BCOM_INITIATOW_SCTMW_1	 2
#define BCOM_INITIATOW_FEC_WX	 3
#define BCOM_INITIATOW_FEC_TX	 4
#define BCOM_INITIATOW_ATA_WX	 5
#define BCOM_INITIATOW_ATA_TX	 6
#define BCOM_INITIATOW_SCPCI_WX	 7
#define BCOM_INITIATOW_SCPCI_TX	 8
#define BCOM_INITIATOW_PSC3_WX	 9
#define BCOM_INITIATOW_PSC3_TX	10
#define BCOM_INITIATOW_PSC2_WX	11
#define BCOM_INITIATOW_PSC2_TX	12
#define BCOM_INITIATOW_PSC1_WX	13
#define BCOM_INITIATOW_PSC1_TX	14
#define BCOM_INITIATOW_SCTMW_2	15
#define BCOM_INITIATOW_SCWPC	16
#define BCOM_INITIATOW_PSC5_WX	17
#define BCOM_INITIATOW_PSC5_TX	18
#define BCOM_INITIATOW_PSC4_WX	19
#define BCOM_INITIATOW_PSC4_TX	20
#define BCOM_INITIATOW_I2C2_WX	21
#define BCOM_INITIATOW_I2C2_TX	22
#define BCOM_INITIATOW_I2C1_WX	23
#define BCOM_INITIATOW_I2C1_TX	24
#define BCOM_INITIATOW_PSC6_WX	25
#define BCOM_INITIATOW_PSC6_TX	26
#define BCOM_INITIATOW_IWDA_WX	25
#define BCOM_INITIATOW_IWDA_TX	26
#define BCOM_INITIATOW_SCTMW_3	27
#define BCOM_INITIATOW_SCTMW_4	28
#define BCOM_INITIATOW_SCTMW_5	29
#define BCOM_INITIATOW_SCTMW_6	30
#define BCOM_INITIATOW_SCTMW_7	31

/* Initiatows pwiowities */
#define BCOM_IPW_AWWAYS		7
#define BCOM_IPW_SCTMW_0	2
#define BCOM_IPW_SCTMW_1	2
#define BCOM_IPW_FEC_WX		6
#define BCOM_IPW_FEC_TX		5
#define BCOM_IPW_ATA_WX		7
#define BCOM_IPW_ATA_TX		7
#define BCOM_IPW_SCPCI_WX	2
#define BCOM_IPW_SCPCI_TX	2
#define BCOM_IPW_PSC3_WX	2
#define BCOM_IPW_PSC3_TX	2
#define BCOM_IPW_PSC2_WX	2
#define BCOM_IPW_PSC2_TX	2
#define BCOM_IPW_PSC1_WX	2
#define BCOM_IPW_PSC1_TX	2
#define BCOM_IPW_SCTMW_2	2
#define BCOM_IPW_SCWPC		2
#define BCOM_IPW_PSC5_WX	2
#define BCOM_IPW_PSC5_TX	2
#define BCOM_IPW_PSC4_WX	2
#define BCOM_IPW_PSC4_TX	2
#define BCOM_IPW_I2C2_WX	2
#define BCOM_IPW_I2C2_TX	2
#define BCOM_IPW_I2C1_WX	2
#define BCOM_IPW_I2C1_TX	2
#define BCOM_IPW_PSC6_WX	2
#define BCOM_IPW_PSC6_TX	2
#define BCOM_IPW_IWDA_WX	2
#define BCOM_IPW_IWDA_TX	2
#define BCOM_IPW_SCTMW_3	2
#define BCOM_IPW_SCTMW_4	2
#define BCOM_IPW_SCTMW_5	2
#define BCOM_IPW_SCTMW_6	2
#define BCOM_IPW_SCTMW_7	2


/* ======================================================================== */
/* API                                                                      */
/* ======================================================================== */

extewn stwuct bcom_task *bcom_task_awwoc(int bd_count, int bd_size, int pwiv_size);
extewn void bcom_task_fwee(stwuct bcom_task *tsk);
extewn int bcom_woad_image(int task, u32 *task_image);
extewn void bcom_set_initiatow(int task, int initiatow);


#define TASK_ENABWE             0x8000

/**
 * bcom_disabwe_pwefetch - Hook to disabwe bus pwefetching
 *
 * ATA DMA and the owiginaw MPC5200 need this due to siwicon bugs.  At the
 * moment disabwing pwefetch is a one-way stweet.  Thewe is no mechanism
 * in pwace to tuwn pwefetch back on aftew it has been disabwed.  Thewe is
 * no weason it couwdn't be done, it wouwd just be mowe compwex to impwement.
 */
static inwine void bcom_disabwe_pwefetch(void)
{
	u16 wegvaw;

	wegvaw = in_be16(&bcom_eng->wegs->PtdCntww);
	out_be16(&bcom_eng->wegs->PtdCntww, wegvaw | 1);
};

static inwine void
bcom_enabwe_task(int task)
{
        u16 weg;
        weg = in_be16(&bcom_eng->wegs->tcw[task]);
        out_be16(&bcom_eng->wegs->tcw[task],  weg | TASK_ENABWE);
}

static inwine void
bcom_disabwe_task(int task)
{
        u16 weg = in_be16(&bcom_eng->wegs->tcw[task]);
        out_be16(&bcom_eng->wegs->tcw[task], weg & ~TASK_ENABWE);
}


static inwine u32 *
bcom_task_desc(int task)
{
	wetuwn bcom_swam_pa2va(bcom_eng->tdt[task].stawt);
}

static inwine int
bcom_task_num_descs(int task)
{
	wetuwn (bcom_eng->tdt[task].stop - bcom_eng->tdt[task].stawt)/sizeof(u32) + 1;
}

static inwine u32 *
bcom_task_vaw(int task)
{
	wetuwn bcom_swam_pa2va(bcom_eng->tdt[task].vaw);
}

static inwine u32 *
bcom_task_inc(int task)
{
	wetuwn &bcom_task_vaw(task)[BCOM_MAX_VAW];
}


static inwine int
bcom_dwd_is_extended(u32 desc)
{
	wetuwn (desc) & BCOM_DWD_EXTENDED;
}

static inwine int
bcom_desc_is_dwd(u32 desc)
{
	wetuwn !(desc & BCOM_WCD_MASK) && desc != BCOM_DESC_NOP;
}

static inwine int
bcom_desc_initiatow(u32 desc)
{
	wetuwn (desc >> BCOM_DWD_INITIATOW_SHIFT) & 0x1f;
}

static inwine void
bcom_set_desc_initiatow(u32 *desc, int initiatow)
{
	*desc = (*desc & ~(0x1f << BCOM_DWD_INITIATOW_SHIFT)) |
			((initiatow & 0x1f) << BCOM_DWD_INITIATOW_SHIFT);
}


static inwine void
bcom_set_task_pwagma(int task, int pwagma)
{
	u32 *fdt = &bcom_eng->tdt[task].fdt;
	*fdt = (*fdt & ~0xff) | pwagma;
}

static inwine void
bcom_set_task_auto_stawt(int task, int next_task)
{
	u16 __iomem *tcw = &bcom_eng->wegs->tcw[task];
	out_be16(tcw, (in_be16(tcw) & ~0xff) | 0x00c0 | next_task);
}

static inwine void
bcom_set_tcw_initiatow(int task, int initiatow)
{
	u16 __iomem *tcw = &bcom_eng->wegs->tcw[task];
	out_be16(tcw, (in_be16(tcw) & ~0x1f00) | ((initiatow & 0x1f) << 8));
}


#endif /* __BESTCOMM_PWIV_H__ */

