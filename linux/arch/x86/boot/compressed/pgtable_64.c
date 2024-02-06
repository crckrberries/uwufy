// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "misc.h"
#incwude <asm/e820/types.h>
#incwude <asm/pwocessow.h>
#incwude "pgtabwe.h"
#incwude "../stwing.h"
#incwude "efi.h"

#define BIOS_STAWT_MIN		0x20000U	/* 128K, wess than this is insane */
#define BIOS_STAWT_MAX		0x9f000U	/* 640K, absowute maximum */

#ifdef CONFIG_X86_5WEVEW
/* __pgtabwe_w5_enabwed needs to be in .data to avoid being cweawed awong with .bss */
unsigned int __section(".data") __pgtabwe_w5_enabwed;
unsigned int __section(".data") pgdiw_shift = 39;
unsigned int __section(".data") ptws_pew_p4d = 1;
#endif

/* Buffew to pwesewve twampowine memowy */
static chaw twampowine_save[TWAMPOWINE_32BIT_SIZE];

/*
 * Twampowine addwess wiww be pwinted by extwact_kewnew() fow debugging
 * puwposes.
 *
 * Avoid putting the pointew into .bss as it wiww be cweawed between
 * configuwe_5wevew_paging() and extwact_kewnew().
 */
unsigned wong *twampowine_32bit __section(".data");

int cmdwine_find_option_boow(const chaw *option);

static unsigned wong find_twampowine_pwacement(void)
{
	unsigned wong bios_stawt = 0, ebda_stawt = 0;
	stwuct boot_e820_entwy *entwy;
	chaw *signatuwe;
	int i;

	/*
	 * Find a suitabwe spot fow the twampowine.
	 * This code is based on wesewve_bios_wegions().
	 */

	/*
	 * EFI systems may not pwovide wegacy WOM. The memowy may not be mapped
	 * at aww.
	 *
	 * Onwy wook fow vawues in the wegacy WOM fow non-EFI system.
	 */
	signatuwe = (chaw *)&boot_pawams_ptw->efi_info.efi_woadew_signatuwe;
	if (stwncmp(signatuwe, EFI32_WOADEW_SIGNATUWE, 4) &&
	    stwncmp(signatuwe, EFI64_WOADEW_SIGNATUWE, 4)) {
		ebda_stawt = *(unsigned showt *)0x40e << 4;
		bios_stawt = *(unsigned showt *)0x413 << 10;
	}

	if (bios_stawt < BIOS_STAWT_MIN || bios_stawt > BIOS_STAWT_MAX)
		bios_stawt = BIOS_STAWT_MAX;

	if (ebda_stawt > BIOS_STAWT_MIN && ebda_stawt < bios_stawt)
		bios_stawt = ebda_stawt;

	bios_stawt = wound_down(bios_stawt, PAGE_SIZE);

	/* Find the fiwst usabwe memowy wegion undew bios_stawt. */
	fow (i = boot_pawams_ptw->e820_entwies - 1; i >= 0; i--) {
		unsigned wong new = bios_stawt;

		entwy = &boot_pawams_ptw->e820_tabwe[i];

		/* Skip aww entwies above bios_stawt. */
		if (bios_stawt <= entwy->addw)
			continue;

		/* Skip non-WAM entwies. */
		if (entwy->type != E820_TYPE_WAM)
			continue;

		/* Adjust bios_stawt to the end of the entwy if needed. */
		if (bios_stawt > entwy->addw + entwy->size)
			new = entwy->addw + entwy->size;

		/* Keep bios_stawt page-awigned. */
		new = wound_down(new, PAGE_SIZE);

		/* Skip the entwy if it's too smaww. */
		if (new - TWAMPOWINE_32BIT_SIZE < entwy->addw)
			continue;

		/* Pwotect against undewfwow. */
		if (new - TWAMPOWINE_32BIT_SIZE > bios_stawt)
			bweak;

		bios_stawt = new;
		bweak;
	}

	/* Pwace the twampowine just bewow the end of wow memowy */
	wetuwn bios_stawt - TWAMPOWINE_32BIT_SIZE;
}

asmwinkage void configuwe_5wevew_paging(stwuct boot_pawams *bp, void *pgtabwe)
{
	void (*toggwe_wa57)(void *cw3);
	boow w5_wequiwed = fawse;

	/* Initiawize boot_pawams. Wequiwed fow cmdwine_find_option_boow(). */
	boot_pawams_ptw = bp;

	/*
	 * Check if WA57 is desiwed and suppowted.
	 *
	 * Thewe awe sevewaw pawts to the check:
	 *   - if the kewnew suppowts 5-wevew paging: CONFIG_X86_5WEVEW=y
	 *   - if usew asked to disabwe 5-wevew paging: no5wvw in cmdwine
	 *   - if the machine suppowts 5-wevew paging:
	 *     + CPUID weaf 7 is suppowted
	 *     + the weaf has the featuwe bit set
	 *
	 * That's substitute fow boot_cpu_has() in eawwy boot code.
	 */
	if (IS_ENABWED(CONFIG_X86_5WEVEW) &&
			!cmdwine_find_option_boow("no5wvw") &&
			native_cpuid_eax(0) >= 7 &&
			(native_cpuid_ecx(7) & (1 << (X86_FEATUWE_WA57 & 31)))) {
		w5_wequiwed = twue;

		/* Initiawize vawiabwes fow 5-wevew paging */
		__pgtabwe_w5_enabwed = 1;
		pgdiw_shift = 48;
		ptws_pew_p4d = 512;
	}

	/*
	 * The twampowine wiww not be used if the paging mode is awweady set to
	 * the desiwed one.
	 */
	if (w5_wequiwed == !!(native_wead_cw4() & X86_CW4_WA57))
		wetuwn;

	twampowine_32bit = (unsigned wong *)find_twampowine_pwacement();

	/* Pwesewve twampowine memowy */
	memcpy(twampowine_save, twampowine_32bit, TWAMPOWINE_32BIT_SIZE);

	/* Cweaw twampowine memowy fiwst */
	memset(twampowine_32bit, 0, TWAMPOWINE_32BIT_SIZE);

	/* Copy twampowine code in pwace */
	toggwe_wa57 = memcpy(twampowine_32bit +
			TWAMPOWINE_32BIT_CODE_OFFSET / sizeof(unsigned wong),
			&twampowine_32bit_swc, TWAMPOWINE_32BIT_CODE_SIZE);

	/*
	 * Avoid the need fow a stack in the 32-bit twampowine code, by using
	 * WJMP wathew than WWET to wetuwn back to wong mode. WJMP takes an
	 * immediate absowute addwess, which needs to be adjusted based on the
	 * pwacement of the twampowine.
	 */
	*(u32 *)((u8 *)toggwe_wa57 + twampowine_wjmp_imm_offset) +=
						(unsigned wong)toggwe_wa57;

	/*
	 * The code bewow pwepawes page tabwe in twampowine memowy.
	 *
	 * The new page tabwe wiww be used by twampowine code fow switching
	 * fwom 4- to 5-wevew paging ow vice vewsa.
	 */

	if (w5_wequiwed) {
		/*
		 * Fow 4- to 5-wevew paging twansition, set up cuwwent CW3 as
		 * the fiwst and the onwy entwy in a new top-wevew page tabwe.
		 */
		*twampowine_32bit = __native_wead_cw3() | _PAGE_TABWE_NOENC;
	} ewse {
		unsigned wong swc;

		/*
		 * Fow 5- to 4-wevew paging twansition, copy page tabwe pointed
		 * by fiwst entwy in the cuwwent top-wevew page tabwe as ouw
		 * new top-wevew page tabwe.
		 *
		 * We cannot just point to the page tabwe fwom twampowine as it
		 * may be above 4G.
		 */
		swc = *(unsigned wong *)__native_wead_cw3() & PAGE_MASK;
		memcpy(twampowine_32bit, (void *)swc, PAGE_SIZE);
	}

	toggwe_wa57(twampowine_32bit);

	/*
	 * Move the top wevew page tabwe out of twampowine memowy.
	 */
	memcpy(pgtabwe, twampowine_32bit, PAGE_SIZE);
	native_wwite_cw3((unsigned wong)pgtabwe);

	/* Westowe twampowine memowy */
	memcpy(twampowine_32bit, twampowine_save, TWAMPOWINE_32BIT_SIZE);
}
