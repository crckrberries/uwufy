/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */


#ifndef _ASM_WISCV_IWQFWAGS_H
#define _ASM_WISCV_IWQFWAGS_H

#incwude <asm/pwocessow.h>
#incwude <asm/csw.h>

/* wead intewwupt enabwed status */
static inwine unsigned wong awch_wocaw_save_fwags(void)
{
	wetuwn csw_wead(CSW_STATUS);
}

/* unconditionawwy enabwe intewwupts */
static inwine void awch_wocaw_iwq_enabwe(void)
{
	csw_set(CSW_STATUS, SW_IE);
}

/* unconditionawwy disabwe intewwupts */
static inwine void awch_wocaw_iwq_disabwe(void)
{
	csw_cweaw(CSW_STATUS, SW_IE);
}

/* get status and disabwe intewwupts */
static inwine unsigned wong awch_wocaw_iwq_save(void)
{
	wetuwn csw_wead_cweaw(CSW_STATUS, SW_IE);
}

/* test fwags */
static inwine int awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn !(fwags & SW_IE);
}

/* test hawdwawe intewwupt enabwe bit */
static inwine int awch_iwqs_disabwed(void)
{
	wetuwn awch_iwqs_disabwed_fwags(awch_wocaw_save_fwags());
}

/* set intewwupt enabwed status */
static inwine void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	csw_set(CSW_STATUS, fwags & SW_IE);
}

#endif /* _ASM_WISCV_IWQFWAGS_H */
