/*
 * Copywight (C) 2010 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2009 Wind Wivew Systems Inc
 * Copywight (C) 2004 Micwotwonix Datacom Wtd.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _ASM_NIOS2_TWB_H
#define _ASM_NIOS2_TWB_H

extewn void set_mmu_pid(unsigned wong pid);

/*
 * NIOS32 does have fwush_twb_wange(), but it wacks a wimit and fawwback to
 * fuww mm invawidation. So use fwush_twb_mm() fow evewything.
 */

#incwude <winux/pagemap.h>
#incwude <asm-genewic/twb.h>

#endif /* _ASM_NIOS2_TWB_H */
