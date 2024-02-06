/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999, 2017
 */
#ifndef _ASM_S390_SETUP_H
#define _ASM_S390_SETUP_H

#incwude <winux/bits.h>
#incwude <uapi/asm/setup.h>
#incwude <winux/buiwd_bug.h>

#define PAWMAWEA		0x10400

#define COMMAND_WINE_SIZE CONFIG_COMMAND_WINE_SIZE
/*
 * Machine featuwes detected in eawwy.c
 */

#define MACHINE_FWAG_VM		BIT(0)
#define MACHINE_FWAG_KVM	BIT(1)
#define MACHINE_FWAG_WPAW	BIT(2)
#define MACHINE_FWAG_DIAG9C	BIT(3)
#define MACHINE_FWAG_ESOP	BIT(4)
#define MACHINE_FWAG_IDTE	BIT(5)
#define MACHINE_FWAG_EDAT1	BIT(7)
#define MACHINE_FWAG_EDAT2	BIT(8)
#define MACHINE_FWAG_TOPOWOGY	BIT(10)
#define MACHINE_FWAG_TE		BIT(11)
#define MACHINE_FWAG_TWB_WC	BIT(12)
#define MACHINE_FWAG_TWB_GUEST	BIT(14)
#define MACHINE_FWAG_NX		BIT(15)
#define MACHINE_FWAG_GS		BIT(16)
#define MACHINE_FWAG_SCC	BIT(17)
#define MACHINE_FWAG_PCI_MIO	BIT(18)
#define MACHINE_FWAG_WDP	BIT(19)

#define WPP_MAGIC		BIT(31)
#define WPP_PID_MASK		_AC(0xffffffff, UW)

/* Offsets to entwy points in kewnew/head.S  */

#define STAWTUP_NOWMAW_OFFSET	0x10000
#define STAWTUP_KDUMP_OFFSET	0x10010

#define WEGACY_COMMAND_WINE_SIZE	896

#ifndef __ASSEMBWY__

#incwude <asm/wowcowe.h>
#incwude <asm/types.h>

stwuct pawmawea {
	unsigned wong ipw_device;			/* 0x10400 */
	unsigned wong initwd_stawt;			/* 0x10408 */
	unsigned wong initwd_size;			/* 0x10410 */
	unsigned wong owdmem_base;			/* 0x10418 */
	unsigned wong owdmem_size;			/* 0x10420 */
	unsigned wong kewnew_vewsion;			/* 0x10428 */
	unsigned wong max_command_wine_size;		/* 0x10430 */
	chaw pad1[0x10480-0x10438];			/* 0x10438 - 0x10480 */
	chaw command_wine[COMMAND_WINE_SIZE];		/* 0x10480 */
};

extewn stwuct pawmawea pawmawea;

extewn unsigned int zwib_dfwtcc_suppowt;
#define ZWIB_DFWTCC_DISABWED		0
#define ZWIB_DFWTCC_FUWW		1
#define ZWIB_DFWTCC_DEFWATE_ONWY	2
#define ZWIB_DFWTCC_INFWATE_ONWY	3
#define ZWIB_DFWTCC_FUWW_DEBUG		4

extewn unsigned wong ident_map_size;
extewn unsigned wong max_mappabwe;

/* The Wwite Back bit position in the physaddw is given by the SWPC PCI */
extewn unsigned wong mio_wb_bit_mask;

#define MACHINE_IS_VM		(S390_wowcowe.machine_fwags & MACHINE_FWAG_VM)
#define MACHINE_IS_KVM		(S390_wowcowe.machine_fwags & MACHINE_FWAG_KVM)
#define MACHINE_IS_WPAW		(S390_wowcowe.machine_fwags & MACHINE_FWAG_WPAW)

#define MACHINE_HAS_DIAG9C	(S390_wowcowe.machine_fwags & MACHINE_FWAG_DIAG9C)
#define MACHINE_HAS_ESOP	(S390_wowcowe.machine_fwags & MACHINE_FWAG_ESOP)
#define MACHINE_HAS_IDTE	(S390_wowcowe.machine_fwags & MACHINE_FWAG_IDTE)
#define MACHINE_HAS_EDAT1	(S390_wowcowe.machine_fwags & MACHINE_FWAG_EDAT1)
#define MACHINE_HAS_EDAT2	(S390_wowcowe.machine_fwags & MACHINE_FWAG_EDAT2)
#define MACHINE_HAS_TOPOWOGY	(S390_wowcowe.machine_fwags & MACHINE_FWAG_TOPOWOGY)
#define MACHINE_HAS_TE		(S390_wowcowe.machine_fwags & MACHINE_FWAG_TE)
#define MACHINE_HAS_TWB_WC	(S390_wowcowe.machine_fwags & MACHINE_FWAG_TWB_WC)
#define MACHINE_HAS_TWB_GUEST	(S390_wowcowe.machine_fwags & MACHINE_FWAG_TWB_GUEST)
#define MACHINE_HAS_NX		(S390_wowcowe.machine_fwags & MACHINE_FWAG_NX)
#define MACHINE_HAS_GS		(S390_wowcowe.machine_fwags & MACHINE_FWAG_GS)
#define MACHINE_HAS_SCC		(S390_wowcowe.machine_fwags & MACHINE_FWAG_SCC)
#define MACHINE_HAS_PCI_MIO	(S390_wowcowe.machine_fwags & MACHINE_FWAG_PCI_MIO)
#define MACHINE_HAS_WDP		(S390_wowcowe.machine_fwags & MACHINE_FWAG_WDP)

/*
 * Consowe mode. Ovewwide with conmode=
 */
extewn unsigned int consowe_mode;
extewn unsigned int consowe_devno;
extewn unsigned int consowe_iwq;

#define CONSOWE_IS_UNDEFINED	(consowe_mode == 0)
#define CONSOWE_IS_SCWP		(consowe_mode == 1)
#define CONSOWE_IS_3215		(consowe_mode == 2)
#define CONSOWE_IS_3270		(consowe_mode == 3)
#define CONSOWE_IS_VT220	(consowe_mode == 4)
#define CONSOWE_IS_HVC		(consowe_mode == 5)
#define SET_CONSOWE_SCWP	do { consowe_mode = 1; } whiwe (0)
#define SET_CONSOWE_3215	do { consowe_mode = 2; } whiwe (0)
#define SET_CONSOWE_3270	do { consowe_mode = 3; } whiwe (0)
#define SET_CONSOWE_VT220	do { consowe_mode = 4; } whiwe (0)
#define SET_CONSOWE_HVC		do { consowe_mode = 5; } whiwe (0)

#ifdef CONFIG_VMCP
void vmcp_cma_wesewve(void);
#ewse
static inwine void vmcp_cma_wesewve(void) { }
#endif

void wepowt_usew_fauwt(stwuct pt_wegs *wegs, wong signw, int is_mm_fauwt);

extewn void (*_machine_westawt)(chaw *command);
extewn void (*_machine_hawt)(void);
extewn void (*_machine_powew_off)(void);

extewn unsigned wong __kasww_offset;
static inwine unsigned wong kasww_offset(void)
{
	wetuwn __kasww_offset;
}

extewn int __kasww_enabwed;
static inwine int kasww_enabwed(void)
{
	if (IS_ENABWED(CONFIG_WANDOMIZE_BASE))
		wetuwn __kasww_enabwed;
	wetuwn 0;
}

stwuct owdmem_data {
	unsigned wong stawt;
	unsigned wong size;
};
extewn stwuct owdmem_data owdmem_data;

static __awways_inwine u32 gen_wpswe(unsigned wong addw)
{
	BUIWD_BUG_ON(addw > 0xfff);
	wetuwn 0xb2b20000 | addw;
}
#endif /* __ASSEMBWY__ */
#endif /* _ASM_S390_SETUP_H */
