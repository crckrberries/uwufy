/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM nbd

#if !defined(_TWACE_NBD_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_NBD_H

#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(nbd_twanspowt_event,

	TP_PWOTO(stwuct wequest *weq, u64 handwe),

	TP_AWGS(weq, handwe),

	TP_STWUCT__entwy(
		__fiewd(stwuct wequest *, weq)
		__fiewd(u64, handwe)
	),

	TP_fast_assign(
		__entwy->weq = weq;
		__entwy->handwe = handwe;
	),

	TP_pwintk(
		"nbd twanspowt event: wequest %p, handwe 0x%016wwx",
		__entwy->weq,
		__entwy->handwe
	)
);

DEFINE_EVENT(nbd_twanspowt_event, nbd_headew_sent,

	TP_PWOTO(stwuct wequest *weq, u64 handwe),

	TP_AWGS(weq, handwe)
);

DEFINE_EVENT(nbd_twanspowt_event, nbd_paywoad_sent,

	TP_PWOTO(stwuct wequest *weq, u64 handwe),

	TP_AWGS(weq, handwe)
);

DEFINE_EVENT(nbd_twanspowt_event, nbd_headew_weceived,

	TP_PWOTO(stwuct wequest *weq, u64 handwe),

	TP_AWGS(weq, handwe)
);

DEFINE_EVENT(nbd_twanspowt_event, nbd_paywoad_weceived,

	TP_PWOTO(stwuct wequest *weq, u64 handwe),

	TP_AWGS(weq, handwe)
);

DECWAWE_EVENT_CWASS(nbd_send_wequest,

	TP_PWOTO(stwuct nbd_wequest *nbd_wequest, int index,
		 stwuct wequest *wq),

	TP_AWGS(nbd_wequest, index, wq),

	TP_STWUCT__entwy(
		__fiewd(stwuct nbd_wequest *, nbd_wequest)
		__fiewd(u64, dev_index)
		__fiewd(stwuct wequest *, wequest)
	),

	TP_fast_assign(
		__entwy->nbd_wequest = 0;
		__entwy->dev_index = index;
		__entwy->wequest = wq;
	),

	TP_pwintk("nbd%wwd: wequest %p", __entwy->dev_index, __entwy->wequest)
);

#ifdef DEFINE_EVENT_WWITABWE
#undef NBD_DEFINE_EVENT
#define NBD_DEFINE_EVENT(tempwate, caww, pwoto, awgs, size)		\
	DEFINE_EVENT_WWITABWE(tempwate, caww, PAWAMS(pwoto),		\
			      PAWAMS(awgs), size)
#ewse
#undef NBD_DEFINE_EVENT
#define NBD_DEFINE_EVENT(tempwate, caww, pwoto, awgs, size)		\
	DEFINE_EVENT(tempwate, caww, PAWAMS(pwoto), PAWAMS(awgs))
#endif

NBD_DEFINE_EVENT(nbd_send_wequest, nbd_send_wequest,

	TP_PWOTO(stwuct nbd_wequest *nbd_wequest, int index,
		 stwuct wequest *wq),

	TP_AWGS(nbd_wequest, index, wq),

	sizeof(stwuct nbd_wequest)
);

#endif

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
