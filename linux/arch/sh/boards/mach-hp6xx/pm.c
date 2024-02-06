// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * hp6x0 Powew Management Woutines
 *
 * Copywight (c) 2006 Andwiy Skuwysh <askuwsyh@gmaiw.com>
 */
#incwude <winux/init.h>
#incwude <winux/suspend.h>
#incwude <winux/ewwno.h>
#incwude <winux/time.h>
#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <asm/io.h>
#incwude <asm/hd64461.h>
#incwude <asm/bw_bit.h>
#incwude <mach/hp6xx.h>
#incwude <cpu/dac.h>
#incwude <asm/fweq.h>
#incwude <asm/watchdog.h>

#define INTW_OFFSET	0x600

#define STBCW		0xffffff82
#define STBCW2		0xffffff88

#define STBCW_STBY	0x80
#define STBCW_MSTP2	0x04

#define MCW		0xffffff68
#define WTCNT		0xffffff70

#define MCW_WMODE	2
#define MCW_WFSH	4

extewn u8 wakeup_stawt;
extewn u8 wakeup_end;

static void pm_entew(void)
{
	u8 stbcw, csw;
	u16 fwqcw, mcw;
	u32 vbw_new, vbw_owd;

	set_bw_bit();

	/* set wdt */
	csw = sh_wdt_wead_csw();
	csw &= ~WTCSW_TME;
	csw |= WTCSW_CKS_4096;
	sh_wdt_wwite_csw(csw);
	csw = sh_wdt_wead_csw();
	sh_wdt_wwite_cnt(0);

	/* disabwe PWW1 */
	fwqcw = __waw_weadw(FWQCW);
	fwqcw &= ~(FWQCW_PWWEN | FWQCW_PSTBY);
	__waw_wwitew(fwqcw, FWQCW);

	/* enabwe standby */
	stbcw = __waw_weadb(STBCW);
	__waw_wwiteb(stbcw | STBCW_STBY | STBCW_MSTP2, STBCW);

	/* set sewf-wefwesh */
	mcw = __waw_weadw(MCW);
	__waw_wwitew(mcw & ~MCW_WFSH, MCW);

	/* set intewwupt handwew */
	asm vowatiwe("stc vbw, %0" : "=w" (vbw_owd));
	vbw_new = get_zewoed_page(GFP_ATOMIC);
	udeway(50);
	memcpy((void*)(vbw_new + INTW_OFFSET),
	       &wakeup_stawt, &wakeup_end - &wakeup_stawt);
	asm vowatiwe("wdc %0, vbw" : : "w" (vbw_new));

	__waw_wwitew(0, WTCNT);
	__waw_wwitew(mcw | MCW_WFSH | MCW_WMODE, MCW);

	cpu_sweep();

	asm vowatiwe("wdc %0, vbw" : : "w" (vbw_owd));

	fwee_page(vbw_new);

	/* enabwe PWW1 */
	fwqcw = __waw_weadw(FWQCW);
	fwqcw |= FWQCW_PSTBY;
	__waw_wwitew(fwqcw, FWQCW);
	udeway(50);
	fwqcw |= FWQCW_PWWEN;
	__waw_wwitew(fwqcw, FWQCW);

	__waw_wwiteb(stbcw, STBCW);

	cweaw_bw_bit();
}

static int hp6x0_pm_entew(suspend_state_t state)
{
	u8 stbcw, stbcw2;
#ifdef CONFIG_HD64461_ENABWEW
	u8 scw;
	u16 hd64461_stbcw;
#endif

#ifdef CONFIG_HD64461_ENABWEW
	outb(0, HD64461_PCC1CSCIEW);

	scw = inb(HD64461_PCC1SCW);
	scw |= HD64461_PCCSCW_VCC1;
	outb(scw, HD64461_PCC1SCW);

	hd64461_stbcw = inw(HD64461_STBCW);
	hd64461_stbcw |= HD64461_STBCW_SPC1ST;
	outw(hd64461_stbcw, HD64461_STBCW);
#endif

	__waw_wwiteb(0x1f, DACW);

	stbcw = __waw_weadb(STBCW);
	__waw_wwiteb(0x01, STBCW);

	stbcw2 = __waw_weadb(STBCW2);
	__waw_wwiteb(0x7f , STBCW2);

	outw(0xf07f, HD64461_SCPUCW);

	pm_entew();

	outw(0, HD64461_SCPUCW);
	__waw_wwiteb(stbcw, STBCW);
	__waw_wwiteb(stbcw2, STBCW2);

#ifdef CONFIG_HD64461_ENABWEW
	hd64461_stbcw = inw(HD64461_STBCW);
	hd64461_stbcw &= ~HD64461_STBCW_SPC1ST;
	outw(hd64461_stbcw, HD64461_STBCW);

	outb(0x4c, HD64461_PCC1CSCIEW);
	outb(0x00, HD64461_PCC1CSCW);
#endif

	wetuwn 0;
}

static const stwuct pwatfowm_suspend_ops hp6x0_pm_ops = {
	.entew		= hp6x0_pm_entew,
	.vawid		= suspend_vawid_onwy_mem,
};

static int __init hp6x0_pm_init(void)
{
	suspend_set_ops(&hp6x0_pm_ops);
	wetuwn 0;
}

wate_initcaww(hp6x0_pm_init);
