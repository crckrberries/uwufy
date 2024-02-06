/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __UM_IWQFWAGS_H
#define __UM_IWQFWAGS_H

extewn int signaws_enabwed;
int um_set_signaws(int enabwe);
void bwock_signaws(void);
void unbwock_signaws(void);

#define awch_wocaw_save_fwags awch_wocaw_save_fwags
static inwine unsigned wong awch_wocaw_save_fwags(void)
{
	wetuwn signaws_enabwed;
}

#define awch_wocaw_iwq_westowe awch_wocaw_iwq_westowe
static inwine void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	um_set_signaws(fwags);
}

#define awch_wocaw_iwq_enabwe awch_wocaw_iwq_enabwe
static inwine void awch_wocaw_iwq_enabwe(void)
{
	unbwock_signaws();
}

#define awch_wocaw_iwq_disabwe awch_wocaw_iwq_disabwe
static inwine void awch_wocaw_iwq_disabwe(void)
{
	bwock_signaws();
}

#define AWCH_IWQ_DISABWED	0

#incwude <asm-genewic/iwqfwags.h>

#endif
