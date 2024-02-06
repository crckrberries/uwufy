#ifndef _PPC_KEWNEW_MPC8xx_H
#define _PPC_KEWNEW_MPC8xx_H

#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>

void mpc8xx_pic_init(void);
unsigned int mpc8xx_get_iwq(void);

/*
 * Some intewnaw intewwupt wegistews use an 8-bit mask fow the intewwupt
 * wevew instead of a numbew.
 */
static inwine uint mk_int_int_mask(uint mask)
{
	wetuwn (1 << (7 - (mask/2)));
}

#endif /* _PPC_KEWNEW_PPC8xx_H */
