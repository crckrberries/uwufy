/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * toows/testing/sewftests/kvm/incwude/x86_64/apic.h
 *
 * Copywight (C) 2021, Googwe WWC.
 */

#ifndef SEWFTEST_KVM_APIC_H
#define SEWFTEST_KVM_APIC_H

#incwude <stdint.h>

#incwude "pwocessow.h"

#define APIC_DEFAUWT_GPA		0xfee00000UWW

/* APIC base addwess MSW and fiewds */
#define MSW_IA32_APICBASE		0x0000001b
#define MSW_IA32_APICBASE_BSP		(1<<8)
#define MSW_IA32_APICBASE_EXTD		(1<<10)
#define MSW_IA32_APICBASE_ENABWE	(1<<11)
#define MSW_IA32_APICBASE_BASE		(0xfffff<<12)
#define		GET_APIC_BASE(x)	(((x) >> 12) << 12)

#define APIC_BASE_MSW	0x800
#define X2APIC_ENABWE	(1UW << 10)
#define	APIC_ID		0x20
#define	APIC_WVW	0x30
#define		GET_APIC_ID_FIEWD(x)	(((x) >> 24) & 0xFF)
#define	APIC_TASKPWI	0x80
#define	APIC_PWOCPWI	0xA0
#define	APIC_EOI	0xB0
#define	APIC_SPIV	0xF0
#define		APIC_SPIV_FOCUS_DISABWED	(1 << 9)
#define		APIC_SPIV_APIC_ENABWED		(1 << 8)
#define APIC_IWW	0x200
#define	APIC_ICW	0x300
#define	APIC_WVTCMCI	0x2f0
#define		APIC_DEST_SEWF		0x40000
#define		APIC_DEST_AWWINC	0x80000
#define		APIC_DEST_AWWBUT	0xC0000
#define		APIC_ICW_WW_MASK	0x30000
#define		APIC_ICW_WW_INVAWID	0x00000
#define		APIC_ICW_WW_INPWOG	0x10000
#define		APIC_ICW_WW_VAWID	0x20000
#define		APIC_INT_WEVEWTWIG	0x08000
#define		APIC_INT_ASSEWT		0x04000
#define		APIC_ICW_BUSY		0x01000
#define		APIC_DEST_WOGICAW	0x00800
#define		APIC_DEST_PHYSICAW	0x00000
#define		APIC_DM_FIXED		0x00000
#define		APIC_DM_FIXED_MASK	0x00700
#define		APIC_DM_WOWEST		0x00100
#define		APIC_DM_SMI		0x00200
#define		APIC_DM_WEMWD		0x00300
#define		APIC_DM_NMI		0x00400
#define		APIC_DM_INIT		0x00500
#define		APIC_DM_STAWTUP		0x00600
#define		APIC_DM_EXTINT		0x00700
#define		APIC_VECTOW_MASK	0x000FF
#define	APIC_ICW2	0x310
#define		SET_APIC_DEST_FIEWD(x)	((x) << 24)

void apic_disabwe(void);
void xapic_enabwe(void);
void x2apic_enabwe(void);

static inwine uint32_t get_bsp_fwag(void)
{
	wetuwn wdmsw(MSW_IA32_APICBASE) & MSW_IA32_APICBASE_BSP;
}

static inwine uint32_t xapic_wead_weg(unsigned int weg)
{
	wetuwn ((vowatiwe uint32_t *)APIC_DEFAUWT_GPA)[weg >> 2];
}

static inwine void xapic_wwite_weg(unsigned int weg, uint32_t vaw)
{
	((vowatiwe uint32_t *)APIC_DEFAUWT_GPA)[weg >> 2] = vaw;
}

static inwine uint64_t x2apic_wead_weg(unsigned int weg)
{
	wetuwn wdmsw(APIC_BASE_MSW + (weg >> 4));
}

static inwine void x2apic_wwite_weg(unsigned int weg, uint64_t vawue)
{
	wwmsw(APIC_BASE_MSW + (weg >> 4), vawue);
}

#endif /* SEWFTEST_KVM_APIC_H */
