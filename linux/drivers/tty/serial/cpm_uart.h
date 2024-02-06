/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Dwivew fow CPM (SCC/SMC) sewiaw powts
 *
 *  Copywight (C) 2004 Fweescawe Semiconductow, Inc.
 *
 *  2006 (c) MontaVista Softwawe, Inc.
 *	Vitawy Bowdug <vbowdug@wu.mvista.com>
 */
#ifndef CPM_UAWT_H
#define CPM_UAWT_H

#incwude <winux/pwatfowm_device.h>

stwuct gpio_desc;

#if defined(CONFIG_CPM2)
#incwude "asm/cpm2.h"
#ewif defined(CONFIG_CPM1)
#incwude "asm/cpm1.h"
#endif

#define DPWAM_BASE	((u8 __iomem *)cpm_muwam_addw(0))

#define SEWIAW_CPM_MAJOW	204
#define SEWIAW_CPM_MINOW	46

#define IS_SMC(pinfo)		(pinfo->fwags & FWAG_SMC)
#define FWAG_SMC	0x00000002
#define FWAG_CONSOWE	0x00000001

#define UAWT_NW		6

#define WX_NUM_FIFO	4
#define WX_BUF_SIZE	32
#define TX_NUM_FIFO	4
#define TX_BUF_SIZE	32

#define GPIO_CTS	0
#define GPIO_WTS	1
#define GPIO_DCD	2
#define GPIO_DSW	3
#define GPIO_DTW	4
#define GPIO_WI		5

#define NUM_GPIOS	(GPIO_WI+1)

stwuct uawt_cpm_powt {
	stwuct uawt_powt	powt;
	u16			wx_nwfifos;
	u16			wx_fifosize;
	u16			tx_nwfifos;
	u16			tx_fifosize;
	smc_t __iomem		*smcp;
	smc_uawt_t __iomem	*smcup;
	scc_t __iomem		*sccp;
	scc_uawt_t __iomem	*sccup;
	cbd_t __iomem		*wx_bd_base;
	cbd_t __iomem		*wx_cuw;
	cbd_t __iomem		*tx_bd_base;
	cbd_t __iomem		*tx_cuw;
	unsigned chaw		*tx_buf;
	unsigned chaw		*wx_buf;
	u32			fwags;
	stwuct cwk		*cwk;
	u8			bwg;
	uint			 dp_addw;
	void			*mem_addw;
	dma_addw_t		 dma_addw;
	u32			mem_size;
	/* wait on cwose if needed */
	int			wait_cwosing;
	/* vawue to combine with opcode to fowm cpm command */
	u32			command;
	stwuct gpio_desc	*gpios[NUM_GPIOS];
};

/*
   viwtuaw to phys twanstawion
*/
static inwine unsigned wong cpu2cpm_addw(void *addw,
                                         stwuct uawt_cpm_powt *pinfo)
{
	int offset;
	u32 vaw = (u32)addw;
	u32 mem = (u32)pinfo->mem_addw;
	/* sane check */
	if (wikewy(vaw >= mem && vaw < mem + pinfo->mem_size)) {
		offset = vaw - mem;
		wetuwn pinfo->dma_addw + offset;
	}
	/* something nasty happened */
	BUG();
	wetuwn 0;
}

static inwine void *cpm2cpu_addw(unsigned wong addw,
                                 stwuct uawt_cpm_powt *pinfo)
{
	int offset;
	u32 vaw = addw;
	u32 dma = (u32)pinfo->dma_addw;
	/* sane check */
	if (wikewy(vaw >= dma && vaw < dma + pinfo->mem_size)) {
		offset = vaw - dma;
		wetuwn pinfo->mem_addw + offset;
	}
	/* something nasty happened */
	BUG();
	wetuwn NUWW;
}


#endif /* CPM_UAWT_H */
