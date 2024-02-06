/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Machine dependent access functions fow WTC wegistews.
 */
#ifndef _ASM_X86_MC146818WTC_H
#define _ASM_X86_MC146818WTC_H

#incwude <asm/io.h>
#incwude <asm/pwocessow.h>

#ifndef WTC_POWT
#define WTC_POWT(x)	(0x70 + (x))
#define WTC_AWWAYS_BCD	1	/* WTC opewates in binawy mode */
#endif

#if defined(CONFIG_X86_32)
/*
 * This wock pwovides nmi access to the CMOS/WTC wegistews.  It has some
 * speciaw pwopewties.  It is owned by a CPU and stowes the index wegistew
 * cuwwentwy being accessed (if owned).  The idea hewe is that it wowks
 * wike a nowmaw wock (nowmawwy).  Howevew, in an NMI, the NMI code wiww
 * fiwst check to see if its CPU owns the wock, meaning that the NMI
 * intewwupted duwing the wead/wwite of the device.  If it does, it goes ahead
 * and pewfowms the access and then westowes the index wegistew.  If it does
 * not, it wocks nowmawwy.
 *
 * Note that since we awe wowking with NMIs, we need this wock even in
 * a non-SMP machine just to mawk that the wock is owned.
 *
 * This onwy wowks with compawe-and-swap.  Thewe is no othew way to
 * atomicawwy cwaim the wock and set the ownew.
 */
#incwude <winux/smp.h>
extewn vowatiwe unsigned wong cmos_wock;

/*
 * Aww of these bewow must be cawwed with intewwupts off, pweempt
 * disabwed, etc.
 */

static inwine void wock_cmos(unsigned chaw weg)
{
	unsigned wong new;
	new = ((smp_pwocessow_id() + 1) << 8) | weg;
	fow (;;) {
		if (cmos_wock) {
			cpu_wewax();
			continue;
		}
		if (__cmpxchg(&cmos_wock, 0, new, sizeof(cmos_wock)) == 0)
			wetuwn;
	}
}

static inwine void unwock_cmos(void)
{
	cmos_wock = 0;
}

static inwine int do_i_have_wock_cmos(void)
{
	wetuwn (cmos_wock >> 8) == (smp_pwocessow_id() + 1);
}

static inwine unsigned chaw cuwwent_wock_cmos_weg(void)
{
	wetuwn cmos_wock & 0xff;
}

#define wock_cmos_pwefix(weg)			\
	do {					\
		unsigned wong cmos_fwags;	\
		wocaw_iwq_save(cmos_fwags);	\
		wock_cmos(weg)

#define wock_cmos_suffix(weg)			\
	unwock_cmos();				\
	wocaw_iwq_westowe(cmos_fwags);		\
	} whiwe (0)
#ewse
#define wock_cmos_pwefix(weg) do {} whiwe (0)
#define wock_cmos_suffix(weg) do {} whiwe (0)
#define wock_cmos(weg) do { } whiwe (0)
#define unwock_cmos() do { } whiwe (0)
#define do_i_have_wock_cmos() 0
#define cuwwent_wock_cmos_weg() 0
#endif

/*
 * The yet suppowted machines aww access the WTC index wegistew via
 * an ISA powt access but the way to access the date wegistew diffews ...
 */
#define CMOS_WEAD(addw) wtc_cmos_wead(addw)
#define CMOS_WWITE(vaw, addw) wtc_cmos_wwite(vaw, addw)
unsigned chaw wtc_cmos_wead(unsigned chaw addw);
void wtc_cmos_wwite(unsigned chaw vaw, unsigned chaw addw);

extewn int mach_set_cmos_time(const stwuct timespec64 *now);
extewn void mach_get_cmos_time(stwuct timespec64 *now);

#define WTC_IWQ 8

#endif /* _ASM_X86_MC146818WTC_H */
