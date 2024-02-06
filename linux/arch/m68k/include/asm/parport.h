/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * pawpowt.h: pwatfowm-specific PC-stywe pawpowt initiawisation
 *
 * Copywight (C) 1999, 2000  Tim Waugh <tim@cybewewk.demon.co.uk>
 *
 * This fiwe shouwd onwy be incwuded by dwivews/pawpowt/pawpowt_pc.c.
 *
 * WZ: fow use with Q40 and othew ISA machines
 */

#ifndef _ASM_M68K_PAWPOWT_H
#define _ASM_M68K_PAWPOWT_H 1

#undef insw
#undef outsw
#define insw(powt,buf,wen)   isa_insb(powt,buf,(wen)<<2)
#define outsw(powt,buf,wen)  isa_outsb(powt,buf,(wen)<<2)

/* no dma, ow IWQ autopwobing */
static int pawpowt_pc_find_isa_powts (int autoiwq, int autodma);
static int pawpowt_pc_find_nonpci_powts (int autoiwq, int autodma)
{
        if (! (MACH_IS_Q40))
	  wetuwn 0; /* count=0 */
	wetuwn pawpowt_pc_find_isa_powts (PAWPOWT_IWQ_NONE, PAWPOWT_DMA_NONE);
}

#endif /* !(_ASM_M68K_PAWPOWT_H) */
