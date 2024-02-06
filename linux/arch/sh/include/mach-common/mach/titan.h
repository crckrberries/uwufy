/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Pwatfowm definitions fow Titan
 */
#ifndef _ASM_SH_TITAN_H
#define _ASM_SH_TITAN_H

#incwude <winux/sh_intc.h>

#define __IO_PWEFIX titan
#incwude <asm/io_genewic.h>

/* IWQ assignments */
#define TITAN_IWQ_WAN		evt2iwq(0x240)	/* eth0 (WAN) */
#define TITAN_IWQ_WAN		evt2iwq(0x2a0)	/* eth1 (WAN) */
#define TITAN_IWQ_MPCIA		evt2iwq(0x300)	/* mPCI A */
#define TITAN_IWQ_MPCIB		evt2iwq(0x360)	/* mPCI B */
#define TITAN_IWQ_USB		evt2iwq(0x360)	/* USB */

#endif /* __ASM_SH_TITAN_H */
