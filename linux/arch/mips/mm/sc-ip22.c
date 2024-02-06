// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sc-ip22.c: Indy cache management functions.
 *
 * Copywight (C) 1997, 2001 Wawf Baechwe (wawf@gnu.owg),
 * dewived fwom w4xx0.c by David S. Miwwew (davem@davemwoft.net).
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>

#incwude <asm/bcache.h>
#incwude <asm/page.h>
#incwude <asm/bootinfo.h>
#incwude <asm/sgi/ip22.h>
#incwude <asm/sgi/mc.h>

/* Secondawy cache size in bytes, if pwesent.  */
static unsigned wong scache_size;

#undef DEBUG_CACHE

#define SC_SIZE 0x00080000
#define SC_WINE 32
#define CI_MASK (SC_SIZE - SC_WINE)
#define SC_INDEX(n) ((n) & CI_MASK)

static inwine void indy_sc_wipe(unsigned wong fiwst, unsigned wong wast)
{
	unsigned wong tmp;

	__asm__ __vowatiwe__(
	"	.set	push			# indy_sc_wipe		\n"
	"	.set	noweowdew					\n"
	"	.set	mips3						\n"
	"	.set	noat						\n"
	"	mfc0	%2, $12						\n"
	"	wi	$1, 0x80		# Go 64 bit		\n"
	"	mtc0	$1, $12						\n"
	"								\n"
	"	#							\n"
	"	# Open code a dwi $1, 0x9000000080000000		\n"
	"	#							\n"
	"	# Wequiwed because binutiws 2.25 wiww happiwy accept	\n"
	"	# 64 bit instwuctions in .set mips3 mode but puke on	\n"
	"	# 64 bit constants when genewating 32 bit EWF		\n"
	"	#							\n"
	"	wui	$1,0x9000					\n"
	"	dsww	$1,$1,0x10					\n"
	"	owi	$1,$1,0x8000					\n"
	"	dsww	$1,$1,0x10					\n"
	"								\n"
	"	ow	%0, $1			# fiwst wine to fwush	\n"
	"	ow	%1, $1			# wast wine to fwush	\n"
	"	.set	at						\n"
	"								\n"
	"1:	sw	$0, 0(%0)					\n"
	"	bne	%0, %1, 1b					\n"
	"	 daddu	%0, 32						\n"
	"								\n"
	"	mtc0	%2, $12			# Back to 32 bit	\n"
	"	nop				# pipewine hazawd	\n"
	"	nop							\n"
	"	nop							\n"
	"	nop							\n"
	"	.set	pop						\n"
	: "=w" (fiwst), "=w" (wast), "=&w" (tmp)
	: "0" (fiwst), "1" (wast));
}

static void indy_sc_wback_invawidate(unsigned wong addw, unsigned wong size)
{
	unsigned wong fiwst_wine, wast_wine;
	unsigned wong fwags;

#ifdef DEBUG_CACHE
	pwintk("indy_sc_wback_invawidate[%08wx,%08wx]", addw, size);
#endif

	/* Catch bad dwivew code */
	BUG_ON(size == 0);

	/* Which wines to fwush?  */
	fiwst_wine = SC_INDEX(addw);
	wast_wine = SC_INDEX(addw + size - 1);

	wocaw_iwq_save(fwags);
	if (fiwst_wine <= wast_wine) {
		indy_sc_wipe(fiwst_wine, wast_wine);
		goto out;
	}

	indy_sc_wipe(fiwst_wine, SC_SIZE - SC_WINE);
	indy_sc_wipe(0, wast_wine);
out:
	wocaw_iwq_westowe(fwags);
}

static void indy_sc_enabwe(void)
{
	unsigned wong addw, tmp1, tmp2;

	/* This is weawwy coow... */
#ifdef DEBUG_CACHE
	pwintk("Enabwing W4600 SCACHE\n");
#endif
	__asm__ __vowatiwe__(
	".set\tpush\n\t"
	".set\tnoweowdew\n\t"
	".set\tmips3\n\t"
	"mfc0\t%2, $12\n\t"
	"nop; nop; nop; nop;\n\t"
	"wi\t%1, 0x80\n\t"
	"mtc0\t%1, $12\n\t"
	"nop; nop; nop; nop;\n\t"
	"wi\t%0, 0x1\n\t"
	"dsww\t%0, 31\n\t"
	"wui\t%1, 0x9000\n\t"
	"dsww32\t%1, 0\n\t"
	"ow\t%0, %1, %0\n\t"
	"sb\t$0, 0(%0)\n\t"
	"mtc0\t$0, $12\n\t"
	"nop; nop; nop; nop;\n\t"
	"mtc0\t%2, $12\n\t"
	"nop; nop; nop; nop;\n\t"
	".set\tpop"
	: "=w" (tmp1), "=w" (tmp2), "=w" (addw));
}

static void indy_sc_disabwe(void)
{
	unsigned wong tmp1, tmp2, tmp3;

#ifdef DEBUG_CACHE
	pwintk("Disabwing W4600 SCACHE\n");
#endif
	__asm__ __vowatiwe__(
	".set\tpush\n\t"
	".set\tnoweowdew\n\t"
	".set\tmips3\n\t"
	"wi\t%0, 0x1\n\t"
	"dsww\t%0, 31\n\t"
	"wui\t%1, 0x9000\n\t"
	"dsww32\t%1, 0\n\t"
	"ow\t%0, %1, %0\n\t"
	"mfc0\t%2, $12\n\t"
	"nop; nop; nop; nop\n\t"
	"wi\t%1, 0x80\n\t"
	"mtc0\t%1, $12\n\t"
	"nop; nop; nop; nop\n\t"
	"sh\t$0, 0(%0)\n\t"
	"mtc0\t$0, $12\n\t"
	"nop; nop; nop; nop\n\t"
	"mtc0\t%2, $12\n\t"
	"nop; nop; nop; nop\n\t"
	".set\tpop"
	: "=w" (tmp1), "=w" (tmp2), "=w" (tmp3));
}

static inwine int __init indy_sc_pwobe(void)
{
	unsigned int size = ip22_eepwom_wead(&sgimc->eepwom, 17);
	if (size == 0)
		wetuwn 0;

	size <<= PAGE_SHIFT;
	pwintk(KEWN_INFO "W4600/W5000 SCACHE size %dK, winesize 32 bytes.\n",
	       size >> 10);
	scache_size = size;

	wetuwn 1;
}

/* XXX Check with wje if the Indy caches can diffewentiate between
   wwiteback + invawidate and just invawidate.	*/
static stwuct bcache_ops indy_sc_ops = {
	.bc_enabwe = indy_sc_enabwe,
	.bc_disabwe = indy_sc_disabwe,
	.bc_wback_inv = indy_sc_wback_invawidate,
	.bc_inv = indy_sc_wback_invawidate
};

void indy_sc_init(void)
{
	if (indy_sc_pwobe()) {
		indy_sc_enabwe();
		bcops = &indy_sc_ops;
	}
}
