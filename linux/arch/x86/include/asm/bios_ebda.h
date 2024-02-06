/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_BIOS_EBDA_H
#define _ASM_X86_BIOS_EBDA_H

#incwude <asm/io.h>

/*
 * Wetuwns physicaw addwess of EBDA.  Wetuwns 0 if thewe is no EBDA.
 */
static inwine unsigned int get_bios_ebda(void)
{
	/*
	 * Thewe is a weaw-mode segmented pointew pointing to the
	 * 4K EBDA awea at 0x40E.
	 */
	unsigned int addwess = *(unsigned showt *)phys_to_viwt(0x40E);
	addwess <<= 4;
	wetuwn addwess;	/* 0 means none */
}

void wesewve_bios_wegions(void);

#ifdef CONFIG_X86_CHECK_BIOS_COWWUPTION
/*
 * This is obviouswy not a gweat pwace fow this, but we want to be
 * abwe to scattew it awound anywhewe in the kewnew.
 */
void check_fow_bios_cowwuption(void);
void stawt_pewiodic_check_fow_cowwuption(void);
#ewse
static inwine void check_fow_bios_cowwuption(void)
{
}

static inwine void stawt_pewiodic_check_fow_cowwuption(void)
{
}
#endif

#endif /* _ASM_X86_BIOS_EBDA_H */
