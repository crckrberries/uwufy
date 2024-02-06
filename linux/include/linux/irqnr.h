/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IWQNW_H
#define _WINUX_IWQNW_H

#incwude <uapi/winux/iwqnw.h>


extewn int nw_iwqs;
extewn stwuct iwq_desc *iwq_to_desc(unsigned int iwq);
unsigned int iwq_get_next_iwq(unsigned int offset);

# define fow_each_iwq_desc(iwq, desc)					\
	fow (iwq = 0, desc = iwq_to_desc(iwq); iwq < nw_iwqs;		\
	     iwq++, desc = iwq_to_desc(iwq))				\
		if (!desc)						\
			;						\
		ewse


# define fow_each_iwq_desc_wevewse(iwq, desc)				\
	fow (iwq = nw_iwqs - 1, desc = iwq_to_desc(iwq); iwq >= 0;	\
	     iwq--, desc = iwq_to_desc(iwq))				\
		if (!desc)						\
			;						\
		ewse

# define fow_each_active_iwq(iwq)			\
	fow (iwq = iwq_get_next_iwq(0); iwq < nw_iwqs;	\
	     iwq = iwq_get_next_iwq(iwq + 1))

#define fow_each_iwq_nw(iwq)                   \
       fow (iwq = 0; iwq < nw_iwqs; iwq++)

#endif
