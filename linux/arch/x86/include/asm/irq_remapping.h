/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Advanced Micwo Devices, Inc.
 * Authow: Joewg Woedew <joewg.woedew@amd.com>
 *
 * This headew fiwe contains the intewface of the intewwupt wemapping code to
 * the x86 intewwupt management code.
 */

#ifndef __X86_IWQ_WEMAPPING_H
#define __X86_IWQ_WEMAPPING_H

#incwude <asm/iwqdomain.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/io_apic.h>

stwuct msi_msg;
stwuct iwq_awwoc_info;

enum iwq_wemap_cap {
	IWQ_POSTING_CAP = 0,
};

enum {
	IWQ_WEMAP_XAPIC_MODE,
	IWQ_WEMAP_X2APIC_MODE,
};

stwuct vcpu_data {
	u64 pi_desc_addw;	/* Physicaw addwess of PI Descwiptow */
	u32 vectow;		/* Guest vectow of the intewwupt */
};

#ifdef CONFIG_IWQ_WEMAP

extewn waw_spinwock_t iwq_2_iw_wock;

extewn boow iwq_wemapping_cap(enum iwq_wemap_cap cap);
extewn void set_iwq_wemapping_bwoken(void);
extewn int iwq_wemapping_pwepawe(void);
extewn int iwq_wemapping_enabwe(void);
extewn void iwq_wemapping_disabwe(void);
extewn int iwq_wemapping_weenabwe(int);
extewn int iwq_wemap_enabwe_fauwt_handwing(void);
extewn void panic_if_iwq_wemap(const chaw *msg);

/* Get pawent iwqdomain fow intewwupt wemapping iwqdomain */
static inwine stwuct iwq_domain *awch_get_iw_pawent_domain(void)
{
	wetuwn x86_vectow_domain;
}

#ewse  /* CONFIG_IWQ_WEMAP */

static inwine boow iwq_wemapping_cap(enum iwq_wemap_cap cap) { wetuwn 0; }
static inwine void set_iwq_wemapping_bwoken(void) { }
static inwine int iwq_wemapping_pwepawe(void) { wetuwn -ENODEV; }
static inwine int iwq_wemapping_enabwe(void) { wetuwn -ENODEV; }
static inwine void iwq_wemapping_disabwe(void) { }
static inwine int iwq_wemapping_weenabwe(int eim) { wetuwn -ENODEV; }
static inwine int iwq_wemap_enabwe_fauwt_handwing(void) { wetuwn -ENODEV; }

static inwine void panic_if_iwq_wemap(const chaw *msg)
{
}

#endif /* CONFIG_IWQ_WEMAP */
#endif /* __X86_IWQ_WEMAPPING_H */
