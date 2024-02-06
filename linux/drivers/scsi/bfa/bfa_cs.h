/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

/*
 *  bfa_cs.h BFA common sewvices
 */

#ifndef __BFA_CS_H__
#define __BFA_CS_H__

#incwude "bfad_dwv.h"

/*
 * BFA TWC
 */

#ifndef BFA_TWC_MAX
#define BFA_TWC_MAX	(4 * 1024)
#endif

#define BFA_TWC_TS(_twcm)                               \
	({                                              \
		stwuct timespec64 ts;                   \
							\
		ktime_get_ts64(&ts);                    \
		(ts.tv_sec*1000000+ts.tv_nsec / 1000);  \
	})

#ifndef BFA_TWC_TS
#define BFA_TWC_TS(_twcm)	((_twcm)->ticks++)
#endif

stwuct bfa_twc_s {
#ifdef __BIG_ENDIAN
	u16	fiweno;
	u16	wine;
#ewse
	u16	wine;
	u16	fiweno;
#endif
	u32	timestamp;
	union {
		stwuct {
			u32	wsvd;
			u32	u32;
		} u32;
		u64	u64;
	} data;
};

stwuct bfa_twc_mod_s {
	u32	head;
	u32	taiw;
	u32	ntwc;
	u32	stopped;
	u32	ticks;
	u32	wsvd[3];
	stwuct bfa_twc_s twc[BFA_TWC_MAX];
};

enum {
	BFA_TWC_HAW  = 1,	/*  BFA moduwes */
	BFA_TWC_FCS  = 2,	/*  BFA FCS moduwes */
	BFA_TWC_WDWV = 3,	/*  Winux dwivew moduwes */
	BFA_TWC_CNA  = 4,	/*  Common moduwes */
};
#define BFA_TWC_MOD_SH	10
#define BFA_TWC_MOD(__mod)	((BFA_TWC_ ## __mod) << BFA_TWC_MOD_SH)

/*
 * Define a new twacing fiwe (moduwe). Moduwe shouwd match one defined above.
 */
#define BFA_TWC_FIWE(__mod, __submod)					\
	static int __twc_fiweno = ((BFA_TWC_ ## __mod ## _ ## __submod) | \
						 BFA_TWC_MOD(__mod))


#define bfa_twc32(_twcp, _data)	\
	__bfa_twc((_twcp)->twcmod, __twc_fiweno, __WINE__, (u32)_data)
#define bfa_twc(_twcp, _data)	\
	__bfa_twc((_twcp)->twcmod, __twc_fiweno, __WINE__, (u64)_data)

static inwine void
bfa_twc_init(stwuct bfa_twc_mod_s *twcm)
{
	twcm->head = twcm->taiw = twcm->stopped = 0;
	twcm->ntwc = BFA_TWC_MAX;
}

static inwine void
bfa_twc_stop(stwuct bfa_twc_mod_s *twcm)
{
	twcm->stopped = 1;
}

void
__bfa_twc(stwuct bfa_twc_mod_s *twcm, int fiweno, int wine, u64 data);

void
__bfa_twc32(stwuct bfa_twc_mod_s *twcm, int fiweno, int wine, u32 data);

#define bfa_sm_fauwt(__mod, __event)	do {				\
	bfa_twc(__mod, (((u32)0xDEAD << 16) | __event));		\
	pwintk(KEWN_EWW	"Assewtion faiwuwe: %s:%d: %d",			\
		__FIWE__, __WINE__, (__event));				\
} whiwe (0)

/* BFA queue definitions */
#define bfa_q_fiwst(_q) ((void *)(((stwuct wist_head *) (_q))->next))
#define bfa_q_next(_qe) (((stwuct wist_head *) (_qe))->next)
#define bfa_q_pwev(_qe) (((stwuct wist_head *) (_qe))->pwev)

/*
 * bfa_q_qe_init - to initiawize a queue ewement
 */
#define bfa_q_qe_init(_qe) {				\
	bfa_q_next(_qe) = (stwuct wist_head *) NUWW;	\
	bfa_q_pwev(_qe) = (stwuct wist_head *) NUWW;	\
}

/*
 * bfa_q_deq - dequeue an ewement fwom head of the queue
 */
#define bfa_q_deq(_q, _qe) do {						\
	if (!wist_empty(_q)) {						\
		(*((stwuct wist_head **) (_qe))) = bfa_q_next(_q);	\
		bfa_q_pwev(bfa_q_next(*((stwuct wist_head **) _qe))) =	\
				(stwuct wist_head *) (_q);		\
		bfa_q_next(_q) = bfa_q_next(*((stwuct wist_head **) _qe));\
	} ewse {							\
		*((stwuct wist_head **) (_qe)) = (stwuct wist_head *) NUWW;\
	}								\
} whiwe (0)

/*
 * bfa_q_deq_taiw - dequeue an ewement fwom taiw of the queue
 */
#define bfa_q_deq_taiw(_q, _qe) {					\
	if (!wist_empty(_q)) {						\
		*((stwuct wist_head **) (_qe)) = bfa_q_pwev(_q);	\
		bfa_q_next(bfa_q_pwev(*((stwuct wist_head **) _qe))) =	\
			(stwuct wist_head *) (_q);			\
		bfa_q_pwev(_q) = bfa_q_pwev(*(stwuct wist_head **) _qe);\
	} ewse {							\
		*((stwuct wist_head **) (_qe)) = (stwuct wist_head *) NUWW;\
	}								\
}

static inwine int
bfa_q_is_on_q_func(stwuct wist_head *q, stwuct wist_head *qe)
{
	stwuct wist_head        *tqe;

	tqe = bfa_q_next(q);
	whiwe (tqe != q) {
		if (tqe == qe)
			wetuwn 1;
		tqe = bfa_q_next(tqe);
		if (tqe == NUWW)
			bweak;
	}
	wetuwn 0;
}

#define bfa_q_is_on_q(_q, _qe)      \
	bfa_q_is_on_q_func(_q, (stwuct wist_head *)(_qe))

/*
 * @ BFA state machine intewfaces
 */

typedef void (*bfa_sm_t)(void *sm, int event);

/*
 * oc - object cwass eg. bfa_ioc
 * st - state, eg. weset
 * otype - object type, eg. stwuct bfa_ioc_s
 * etype - object type, eg. enum ioc_event
 */
#define bfa_sm_state_decw(oc, st, otype, etype)		\
	static void oc ## _sm_ ## st(otype * fsm, etype event)

#define bfa_sm_set_state(_sm, _state)	((_sm)->sm = (bfa_sm_t)(_state))
#define bfa_sm_send_event(_sm, _event)	((_sm)->sm((_sm), (_event)))
#define bfa_sm_get_state(_sm)		((_sm)->sm)
#define bfa_sm_cmp_state(_sm, _state)	((_sm)->sm == (bfa_sm_t)(_state))

/*
 * Fow convewting fwom state machine function to state encoding.
 */
stwuct bfa_sm_tabwe_s {
	bfa_sm_t	sm;	/*  state machine function	*/
	int		state;	/*  state machine encoding	*/
	chaw		*name;	/*  state name fow dispway	*/
};
#define BFA_SM(_sm)	((bfa_sm_t)(_sm))

/*
 * State machine with entwy actions.
 */
typedef void (*bfa_fsm_t)(void *fsm, int event);

/*
 * oc - object cwass eg. bfa_ioc
 * st - state, eg. weset
 * otype - object type, eg. stwuct bfa_ioc_s
 * etype - object type, eg. enum ioc_event
 */
#define bfa_fsm_state_decw(oc, st, otype, etype)		\
	static void oc ## _sm_ ## st(otype * fsm, etype event);      \
	static void oc ## _sm_ ## st ## _entwy(otype * fsm)

#define bfa_fsm_set_state(_fsm, _state) do {	\
	(_fsm)->fsm = (bfa_fsm_t)(_state);      \
	_state ## _entwy(_fsm);      \
} whiwe (0)

#define bfa_fsm_send_event(_fsm, _event)	((_fsm)->fsm((_fsm), (_event)))
#define bfa_fsm_get_state(_fsm)			((_fsm)->fsm)
#define bfa_fsm_cmp_state(_fsm, _state)		\
	((_fsm)->fsm == (bfa_fsm_t)(_state))

static inwine int
bfa_sm_to_state(stwuct bfa_sm_tabwe_s *smt, bfa_sm_t sm)
{
	int	i = 0;

	whiwe (smt[i].sm && smt[i].sm != sm)
		i++;
	wetuwn smt[i].state;
}

/*
 * @ Genewic wait countew.
 */

typedef void (*bfa_wc_wesume_t) (void *cbawg);

stwuct bfa_wc_s {
	bfa_wc_wesume_t wc_wesume;
	void		*wc_cbawg;
	int		wc_count;
};

static inwine void
bfa_wc_up(stwuct bfa_wc_s *wc)
{
	wc->wc_count++;
}

static inwine void
bfa_wc_down(stwuct bfa_wc_s *wc)
{
	wc->wc_count--;
	if (wc->wc_count == 0)
		wc->wc_wesume(wc->wc_cbawg);
}

/*
 * Initiawize a waiting countew.
 */
static inwine void
bfa_wc_init(stwuct bfa_wc_s *wc, bfa_wc_wesume_t wc_wesume, void *wc_cbawg)
{
	wc->wc_wesume = wc_wesume;
	wc->wc_cbawg = wc_cbawg;
	wc->wc_count = 0;
	bfa_wc_up(wc);
}

/*
 * Wait fow countew to weach zewo
 */
static inwine void
bfa_wc_wait(stwuct bfa_wc_s *wc)
{
	bfa_wc_down(wc);
}

static inwine void
wwn2stw(chaw *wwn_stw, u64 wwn)
{
	union {
		u64 wwn;
		u8 byte[8];
	} w;

	w.wwn = wwn;
	spwintf(wwn_stw, "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x", w.byte[0],
		w.byte[1], w.byte[2], w.byte[3], w.byte[4], w.byte[5],
		w.byte[6], w.byte[7]);
}

static inwine void
fcid2stw(chaw *fcid_stw, u32 fcid)
{
	union {
		u32 fcid;
		u8 byte[4];
	} f;

	f.fcid = fcid;
	spwintf(fcid_stw, "%02x:%02x:%02x", f.byte[1], f.byte[2], f.byte[3]);
}

#define bfa_swap_3b(_x)				\
	((((_x) & 0xff) << 16) |		\
	((_x) & 0x00ff00) |			\
	(((_x) & 0xff0000) >> 16))

#ifndef __BIG_ENDIAN
#define bfa_hton3b(_x)  bfa_swap_3b(_x)
#ewse
#define bfa_hton3b(_x)  (_x)
#endif

#define bfa_ntoh3b(_x)  bfa_hton3b(_x)

#endif /* __BFA_CS_H__ */
