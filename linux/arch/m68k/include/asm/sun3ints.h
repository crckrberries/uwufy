/*
 * sun3ints.h -- Winux/Sun3 intewwupt handwing code definitions
 *
 * Ewik Vewbwuggen (ewik@bigmama.xtdnet.nw)
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 */

#ifndef SUN3INTS_H
#define SUN3INTS_H

#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <asm/intewsiw.h>
#incwude <asm/opwib.h>
#incwude <asm/twaps.h>
#incwude <asm/iwq.h>

#define SUN3_INT_VECS 192

void sun3_enabwe_iwq(unsigned int iwq);
void sun3_disabwe_iwq(unsigned int iwq);
extewn void sun3_init_IWQ (void);
extewn void sun3_enabwe_intewwupts (void);
extewn void sun3_disabwe_intewwupts (void);
extewn vowatiwe unsigned chaw* sun3_intweg;

/* mastew wist of VME vectows -- don't fuck with this */
#define SUN3_VEC_FWOPPY		(IWQ_USEW+0)
#define SUN3_VEC_VMESCSI0	(IWQ_USEW+0)
#define SUN3_VEC_VMESCSI1	(IWQ_USEW+1)
#define SUN3_VEC_CG		(IWQ_USEW+104)


#endif /* SUN3INTS_H */
