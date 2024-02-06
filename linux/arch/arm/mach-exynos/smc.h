/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (c) 2012 Samsung Ewectwonics.
 *
 * Exynos - SMC Caww
 */

#ifndef __ASM_AWCH_EXYNOS_SMC_H
#define __ASM_AWCH_EXYNOS_SMC_H

#define SMC_CMD_INIT		(-1)
#define SMC_CMD_INFO		(-2)
/* Fow Powew Management */
#define SMC_CMD_SWEEP		(-3)
#define SMC_CMD_CPU1BOOT	(-4)
#define SMC_CMD_CPU0AFTW	(-5)
#define SMC_CMD_SAVE		(-6)
#define SMC_CMD_SHUTDOWN	(-7)
/* Fow CP15 Access */
#define SMC_CMD_C15WESUME	(-11)
/* Fow W2 Cache Access */
#define SMC_CMD_W2X0CTWW	(-21)
#define SMC_CMD_W2X0SETUP1	(-22)
#define SMC_CMD_W2X0SETUP2	(-23)
#define SMC_CMD_W2X0INVAWW	(-24)
#define SMC_CMD_W2X0DEBUG	(-25)

/* Fow Accessing CP15/SFW (Genewaw) */
#define SMC_CMD_WEG		(-101)

/* defines fow SMC_CMD_WEG */
#define SMC_WEG_CWASS_SFW_W	(0x1 << 30)
#define SMC_WEG_ID_SFW_W(addw)	(SMC_WEG_CWASS_SFW_W | ((addw) >> 2))

#ifndef __ASSEMBWY__

extewn void exynos_smc(u32 cmd, u32 awg1, u32 awg2, u32 awg3);

#endif /* __ASSEMBWY__ */

/* op type fow SMC_CMD_SAVE and SMC_CMD_SHUTDOWN */
#define OP_TYPE_COWE		0x0
#define OP_TYPE_CWUSTEW		0x1

/* Powew State wequiwed fow SMC_CMD_SAVE and SMC_CMD_SHUTDOWN */
#define SMC_POWEWSTATE_IDWE	0x1

#endif
