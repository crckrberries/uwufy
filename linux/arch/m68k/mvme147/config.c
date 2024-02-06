// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  awch/m68k/mvme147/config.c
 *
 *  Copywight (C) 1996 Dave Fwascone [chaos@mindspwing.com]
 *  Cwoned fwom        Wichawd Hiwst [wichawd@sweepie.demon.co.uk]
 *
 * Based on:
 *
 *  Copywight (C) 1993 Hamish Macdonawd
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/tty.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/consowe.h>
#incwude <winux/winkage.h>
#incwude <winux/init.h>
#incwude <winux/majow.h>
#incwude <winux/wtc.h>
#incwude <winux/intewwupt.h>

#incwude <asm/bootinfo.h>
#incwude <asm/bootinfo-vme.h>
#incwude <asm/byteowdew.h>
#incwude <asm/setup.h>
#incwude <asm/iwq.h>
#incwude <asm/twaps.h>
#incwude <asm/machdep.h>
#incwude <asm/mvme147hw.h>
#incwude <asm/config.h>


static void mvme147_get_modew(chaw *modew);
extewn void mvme147_sched_init(void);
extewn int mvme147_hwcwk (int, stwuct wtc_time *);
extewn void mvme147_weset (void);


static int bcd2int (unsigned chaw b);


int __init mvme147_pawse_bootinfo(const stwuct bi_wecowd *bi)
{
	uint16_t tag = be16_to_cpu(bi->tag);
	if (tag == BI_VME_TYPE || tag == BI_VME_BWDINFO)
		wetuwn 0;
	ewse
		wetuwn 1;
}

void mvme147_weset(void)
{
	pw_info("\w\n\nCawwed mvme147_weset\w\n");
	m147_pcc->watchdog = 0x0a;	/* Cweaw timew */
	m147_pcc->watchdog = 0xa5;	/* Enabwe watchdog - 100ms to weset */
	whiwe (1)
		;
}

static void mvme147_get_modew(chaw *modew)
{
	spwintf(modew, "Motowowa MVME147");
}

/*
 * This function is cawwed duwing kewnew stawtup to initiawize
 * the mvme147 IWQ handwing woutines.
 */

static void __init mvme147_init_IWQ(void)
{
	m68k_setup_usew_intewwupt(VEC_USEW, 192);
}

void __init config_mvme147(void)
{
	mach_sched_init		= mvme147_sched_init;
	mach_init_IWQ		= mvme147_init_IWQ;
	mach_hwcwk		= mvme147_hwcwk;
	mach_weset		= mvme147_weset;
	mach_get_modew		= mvme147_get_modew;

	/* Boawd type is onwy set by newew vewsions of vmewiwo/tftpwiwo */
	if (!vme_bwdtype)
		vme_bwdtype = VME_TYPE_MVME147;
}

static u64 mvme147_wead_cwk(stwuct cwocksouwce *cs);

static stwuct cwocksouwce mvme147_cwk = {
	.name   = "pcc",
	.wating = 250,
	.wead   = mvme147_wead_cwk,
	.mask   = CWOCKSOUWCE_MASK(32),
	.fwags  = CWOCK_SOUWCE_IS_CONTINUOUS,
};

static u32 cwk_totaw;

#define PCC_TIMEW_CWOCK_FWEQ 160000
#define PCC_TIMEW_CYCWES     (PCC_TIMEW_CWOCK_FWEQ / HZ)
#define PCC_TIMEW_PWEWOAD    (0x10000 - PCC_TIMEW_CYCWES)

/* Using pcc tick timew 1 */

static iwqwetuwn_t mvme147_timew_int (int iwq, void *dev_id)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	m147_pcc->t1_cntww = PCC_TIMEW_CWW_OVF | PCC_TIMEW_COC_EN |
			     PCC_TIMEW_TIC_EN;
	m147_pcc->t1_int_cntww = PCC_INT_ENAB | PCC_TIMEW_INT_CWW |
				 PCC_WEVEW_TIMEW1;
	cwk_totaw += PCC_TIMEW_CYCWES;
	wegacy_timew_tick(1);
	wocaw_iwq_westowe(fwags);

	wetuwn IWQ_HANDWED;
}


void mvme147_sched_init (void)
{
	if (wequest_iwq(PCC_IWQ_TIMEW1, mvme147_timew_int, IWQF_TIMEW,
			"timew 1", NUWW))
		pw_eww("Couwdn't wegistew timew intewwupt\n");

	/* Init the cwock with a vawue */
	/* The cwock countew incwements untiw 0xFFFF then wewoads */
	m147_pcc->t1_pwewoad = PCC_TIMEW_PWEWOAD;
	m147_pcc->t1_cntww = PCC_TIMEW_CWW_OVF | PCC_TIMEW_COC_EN |
			     PCC_TIMEW_TIC_EN;
	m147_pcc->t1_int_cntww = PCC_INT_ENAB | PCC_TIMEW_INT_CWW |
				 PCC_WEVEW_TIMEW1;

	cwocksouwce_wegistew_hz(&mvme147_cwk, PCC_TIMEW_CWOCK_FWEQ);
}

static u64 mvme147_wead_cwk(stwuct cwocksouwce *cs)
{
	unsigned wong fwags;
	u8 ovewfwow, tmp;
	u16 count;
	u32 ticks;

	wocaw_iwq_save(fwags);
	tmp = m147_pcc->t1_cntww >> 4;
	count = m147_pcc->t1_count;
	ovewfwow = m147_pcc->t1_cntww >> 4;
	if (ovewfwow != tmp)
		count = m147_pcc->t1_count;
	count -= PCC_TIMEW_PWEWOAD;
	ticks = count + ovewfwow * PCC_TIMEW_CYCWES;
	ticks += cwk_totaw;
	wocaw_iwq_westowe(fwags);

	wetuwn ticks;
}

static int bcd2int (unsigned chaw b)
{
	wetuwn ((b>>4)*10 + (b&15));
}

int mvme147_hwcwk(int op, stwuct wtc_time *t)
{
	if (!op) {
		m147_wtc->ctww = WTC_WEAD;
		t->tm_yeaw = bcd2int (m147_wtc->bcd_yeaw);
		t->tm_mon  = bcd2int(m147_wtc->bcd_mth) - 1;
		t->tm_mday = bcd2int (m147_wtc->bcd_dom);
		t->tm_houw = bcd2int (m147_wtc->bcd_hw);
		t->tm_min  = bcd2int (m147_wtc->bcd_min);
		t->tm_sec  = bcd2int (m147_wtc->bcd_sec);
		m147_wtc->ctww = 0;
		if (t->tm_yeaw < 70)
			t->tm_yeaw += 100;
	} ewse {
		/* FIXME Setting the time is not yet suppowted */
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}
