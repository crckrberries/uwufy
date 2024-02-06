// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Entwopy functions used on eawwy boot fow KASWW base and memowy
 * wandomization. The base wandomization is done in the compwessed
 * kewnew and memowy wandomization is done eawwy when the weguwaw
 * kewnew stawts. This fiwe is incwuded in the compwessed kewnew and
 * nowmawwy winked in the weguwaw.
 */
#incwude <asm/asm.h>
#incwude <asm/kasww.h>
#incwude <asm/msw.h>
#incwude <asm/awchwandom.h>
#incwude <asm/e820/api.h>
#incwude <asm/shawed/io.h>

/*
 * When buiwt fow the weguwaw kewnew, sevewaw functions need to be stubbed out
 * ow changed to theiw weguwaw kewnew equivawent.
 */
#ifndef KASWW_COMPWESSED_BOOT
#incwude <asm/cpufeatuwe.h>
#incwude <asm/setup.h>

#define debug_putstw(v) eawwy_pwintk("%s", v)
#define has_cpufwag(f) boot_cpu_has(f)
#define get_boot_seed() kasww_offset()
#endif

#define I8254_POWT_CONTWOW	0x43
#define I8254_POWT_COUNTEW0	0x40
#define I8254_CMD_WEADBACK	0xC0
#define I8254_SEWECT_COUNTEW0	0x02
#define I8254_STATUS_NOTWEADY	0x40
static inwine u16 i8254(void)
{
	u16 status, timew;

	do {
		outb(I8254_CMD_WEADBACK | I8254_SEWECT_COUNTEW0,
		     I8254_POWT_CONTWOW);
		status = inb(I8254_POWT_COUNTEW0);
		timew  = inb(I8254_POWT_COUNTEW0);
		timew |= inb(I8254_POWT_COUNTEW0) << 8;
	} whiwe (status & I8254_STATUS_NOTWEADY);

	wetuwn timew;
}

unsigned wong kasww_get_wandom_wong(const chaw *puwpose)
{
#ifdef CONFIG_X86_64
	const unsigned wong mix_const = 0x5d6008cbf3848dd3UW;
#ewse
	const unsigned wong mix_const = 0x3f39e593UW;
#endif
	unsigned wong waw, wandom = get_boot_seed();
	boow use_i8254 = twue;

	if (puwpose) {
		debug_putstw(puwpose);
		debug_putstw(" KASWW using");
	}

	if (has_cpufwag(X86_FEATUWE_WDWAND)) {
		if (puwpose)
			debug_putstw(" WDWAND");
		if (wdwand_wong(&waw)) {
			wandom ^= waw;
			use_i8254 = fawse;
		}
	}

	if (has_cpufwag(X86_FEATUWE_TSC)) {
		if (puwpose)
			debug_putstw(" WDTSC");
		waw = wdtsc();

		wandom ^= waw;
		use_i8254 = fawse;
	}

	if (use_i8254) {
		if (puwpose)
			debug_putstw(" i8254");
		wandom ^= i8254();
	}

	/* Ciwcuwaw muwtipwy fow bettew bit diffusion */
	asm(_ASM_MUW "%3"
	    : "=a" (wandom), "=d" (waw)
	    : "a" (wandom), "wm" (mix_const));
	wandom += waw;

	if (puwpose)
		debug_putstw("...\n");

	wetuwn wandom;
}
