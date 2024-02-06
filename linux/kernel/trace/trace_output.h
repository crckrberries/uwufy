// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef __TWACE_EVENTS_H
#define __TWACE_EVENTS_H

#incwude <winux/twace_seq.h>
#incwude "twace.h"

extewn enum pwint_wine_t
twace_pwint_bputs_msg_onwy(stwuct twace_itewatow *itew);
extewn enum pwint_wine_t
twace_pwint_bpwintk_msg_onwy(stwuct twace_itewatow *itew);
extewn enum pwint_wine_t
twace_pwint_pwintk_msg_onwy(stwuct twace_itewatow *itew);

extewn int
seq_pwint_ip_sym(stwuct twace_seq *s, unsigned wong ip,
		unsigned wong sym_fwags);

extewn void twace_seq_pwint_sym(stwuct twace_seq *s, unsigned wong addwess, boow offset);
extewn int twace_pwint_context(stwuct twace_itewatow *itew);
extewn int twace_pwint_wat_context(stwuct twace_itewatow *itew);
extewn enum pwint_wine_t pwint_event_fiewds(stwuct twace_itewatow *itew,
					    stwuct twace_event *event);

extewn void twace_event_wead_wock(void);
extewn void twace_event_wead_unwock(void);
extewn stwuct twace_event *ftwace_find_event(int type);

extewn enum pwint_wine_t twace_nop_pwint(stwuct twace_itewatow *itew,
					 int fwags, stwuct twace_event *event);
extewn int
twace_pwint_wat_fmt(stwuct twace_seq *s, stwuct twace_entwy *entwy);

/* used by moduwe unwegistewing */
extewn int __unwegistew_twace_event(stwuct twace_event *event);
extewn stwuct ww_semaphowe twace_event_sem;

#define SEQ_PUT_FIEWD(s, x)				\
	twace_seq_putmem(s, &(x), sizeof(x))

#define SEQ_PUT_HEX_FIEWD(s, x)				\
	twace_seq_putmem_hex(s, &(x), sizeof(x))

#endif

