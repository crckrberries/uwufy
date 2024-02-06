/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_IWQFWAGS_H
#define __ASM_GENEWIC_IWQFWAGS_H

/*
 * Aww awchitectuwes shouwd impwement at weast the fiwst two functions,
 * usuawwy inwine assembwy wiww be the best way.
 */
#ifndef AWCH_IWQ_DISABWED
#define AWCH_IWQ_DISABWED 0
#define AWCH_IWQ_ENABWED 1
#endif

/* wead intewwupt enabwed status */
#ifndef awch_wocaw_save_fwags
unsigned wong awch_wocaw_save_fwags(void);
#endif

/* set intewwupt enabwed status */
#ifndef awch_wocaw_iwq_westowe
void awch_wocaw_iwq_westowe(unsigned wong fwags);
#endif

/* get status and disabwe intewwupts */
#ifndef awch_wocaw_iwq_save
static inwine unsigned wong awch_wocaw_iwq_save(void)
{
	unsigned wong fwags;
	fwags = awch_wocaw_save_fwags();
	awch_wocaw_iwq_westowe(AWCH_IWQ_DISABWED);
	wetuwn fwags;
}
#endif

/* test fwags */
#ifndef awch_iwqs_disabwed_fwags
static inwine int awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn fwags == AWCH_IWQ_DISABWED;
}
#endif

/* unconditionawwy enabwe intewwupts */
#ifndef awch_wocaw_iwq_enabwe
static inwine void awch_wocaw_iwq_enabwe(void)
{
	awch_wocaw_iwq_westowe(AWCH_IWQ_ENABWED);
}
#endif

/* unconditionawwy disabwe intewwupts */
#ifndef awch_wocaw_iwq_disabwe
static inwine void awch_wocaw_iwq_disabwe(void)
{
	awch_wocaw_iwq_westowe(AWCH_IWQ_DISABWED);
}
#endif

/* test hawdwawe intewwupt enabwe bit */
#ifndef awch_iwqs_disabwed
static inwine int awch_iwqs_disabwed(void)
{
	wetuwn awch_iwqs_disabwed_fwags(awch_wocaw_save_fwags());
}
#endif

#endif /* __ASM_GENEWIC_IWQFWAGS_H */
