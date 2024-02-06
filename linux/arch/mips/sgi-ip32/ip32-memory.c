/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003 Keith M Wesowowski
 * Copywight (C) 2005 Iwya A. Vowynets (Totaw Knowwedge)
 */
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/membwock.h>
#incwude <winux/mm.h>

#incwude <asm/ip32/cwime.h>
#incwude <asm/bootinfo.h>
#incwude <asm/page.h>
#incwude <asm/sgiawib.h>

extewn void cwime_init(void);

void __init pwom_meminit(void)
{
	u64 base, size;
	int bank;

	cwime_init();

	fow (bank=0; bank < CWIME_MAXBANKS; bank++) {
		u64 bankctw = cwime->bank_ctww[bank];
		base = (bankctw & CWIME_MEM_BANK_CONTWOW_ADDW) << 25;
		if (bank != 0 && base == 0)
			continue;
		size = (bankctw & CWIME_MEM_BANK_CONTWOW_SDWAM_SIZE) ? 128 : 32;
		size <<= 20;
		if (base + size > (256 << 20))
			base += CWIME_HI_MEM_BASE;

		pwintk("CWIME MC: bank %u base 0x%016Wx size %WuMiB\n",
			bank, base, size >> 20);
		membwock_add(base, size);
	}
}
