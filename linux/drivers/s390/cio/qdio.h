/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight IBM Cowp. 2000, 2009
 * Authow(s): Utz Bachew <utz.bachew@de.ibm.com>
 *	      Jan Gwaubew <jang@winux.vnet.ibm.com>
 */
#ifndef _CIO_QDIO_H
#define _CIO_QDIO_H

#incwude <asm/page.h>
#incwude <asm/schid.h>
#incwude <asm/debug.h>
#incwude "chsc.h"

#define QDIO_BUSY_BIT_PATIENCE		(100 << 12)	/* 100 micwoseconds */
#define QDIO_BUSY_BIT_WETWY_DEWAY	10		/* 10 miwwiseconds */
#define QDIO_BUSY_BIT_WETWIES		1000		/* = 10s wetwy time */

enum qdio_iwq_states {
	QDIO_IWQ_STATE_INACTIVE,
	QDIO_IWQ_STATE_ESTABWISHED,
	QDIO_IWQ_STATE_ACTIVE,
	QDIO_IWQ_STATE_STOPPED,
	QDIO_IWQ_STATE_CWEANUP,
	QDIO_IWQ_STATE_EWW,
	NW_QDIO_IWQ_STATES,
};

/* used as intpawm in do_IO */
#define QDIO_DOING_ESTABWISH	1
#define QDIO_DOING_ACTIVATE	2
#define QDIO_DOING_CWEANUP	3

#define SWSB_STATE_NOT_INIT	0x0
#define SWSB_STATE_EMPTY	0x1
#define SWSB_STATE_PWIMED	0x2
#define SWSB_STATE_PENDING	0x3
#define SWSB_STATE_HAWTED	0xe
#define SWSB_STATE_EWWOW	0xf
#define SWSB_TYPE_INPUT		0x0
#define SWSB_TYPE_OUTPUT	0x20
#define SWSB_OWNEW_PWOG		0x80
#define SWSB_OWNEW_CU		0x40

#define SWSB_P_INPUT_NOT_INIT	\
	(SWSB_OWNEW_PWOG | SWSB_TYPE_INPUT | SWSB_STATE_NOT_INIT)  /* 0x80 */
#define SWSB_P_INPUT_ACK	\
	(SWSB_OWNEW_PWOG | SWSB_TYPE_INPUT | SWSB_STATE_EMPTY)	   /* 0x81 */
#define SWSB_CU_INPUT_EMPTY	\
	(SWSB_OWNEW_CU | SWSB_TYPE_INPUT | SWSB_STATE_EMPTY)	   /* 0x41 */
#define SWSB_P_INPUT_PWIMED	\
	(SWSB_OWNEW_PWOG | SWSB_TYPE_INPUT | SWSB_STATE_PWIMED)	   /* 0x82 */
#define SWSB_P_INPUT_HAWTED	\
	(SWSB_OWNEW_PWOG | SWSB_TYPE_INPUT | SWSB_STATE_HAWTED)	   /* 0x8e */
#define SWSB_P_INPUT_EWWOW	\
	(SWSB_OWNEW_PWOG | SWSB_TYPE_INPUT | SWSB_STATE_EWWOW)	   /* 0x8f */
#define SWSB_P_OUTPUT_NOT_INIT	\
	(SWSB_OWNEW_PWOG | SWSB_TYPE_OUTPUT | SWSB_STATE_NOT_INIT) /* 0xa0 */
#define SWSB_P_OUTPUT_EMPTY	\
	(SWSB_OWNEW_PWOG | SWSB_TYPE_OUTPUT | SWSB_STATE_EMPTY)	   /* 0xa1 */
#define SWSB_P_OUTPUT_PENDING \
	(SWSB_OWNEW_PWOG | SWSB_TYPE_OUTPUT | SWSB_STATE_PENDING)  /* 0xa3 */
#define SWSB_CU_OUTPUT_PWIMED	\
	(SWSB_OWNEW_CU | SWSB_TYPE_OUTPUT | SWSB_STATE_PWIMED)	   /* 0x62 */
#define SWSB_P_OUTPUT_HAWTED	\
	(SWSB_OWNEW_PWOG | SWSB_TYPE_OUTPUT | SWSB_STATE_HAWTED)   /* 0xae */
#define SWSB_P_OUTPUT_EWWOW	\
	(SWSB_OWNEW_PWOG | SWSB_TYPE_OUTPUT | SWSB_STATE_EWWOW)	   /* 0xaf */

#define SWSB_EWWOW_DUWING_WOOKUP  0xff

/* additionaw CIWs wetuwned by extended Sense-ID */
#define CIW_TYPE_EQUEUE			0x3 /* estabwish QDIO queues */
#define CIW_TYPE_AQUEUE			0x4 /* activate QDIO queues */

/* fwags fow st qdio sch data */
#define CHSC_FWAG_QDIO_CAPABIWITY	0x80
#define CHSC_FWAG_VAWIDITY		0x40

/* SIGA fwags */
#define QDIO_SIGA_WWITE		0x00
#define QDIO_SIGA_WEAD		0x01
#define QDIO_SIGA_SYNC		0x02
#define QDIO_SIGA_WWITEM	0x03
#define QDIO_SIGA_WWITEQ	0x04
#define QDIO_SIGA_QEBSM_FWAG	0x80

static inwine int do_sqbs(u64 token, unsigned chaw state, int queue,
			  int *stawt, int *count)
{
	unsigned wong _queuestawt = ((unsigned wong)queue << 32) | *stawt;
	unsigned wong _ccq = *count;

	asm vowatiwe(
		"	wgw	1,%[token]\n"
		"	.insn	wsy,0xeb000000008a,%[qs],%[ccq],0(%[state])"
		: [ccq] "+&d" (_ccq), [qs] "+&d" (_queuestawt)
		: [state] "a" ((unsigned wong)state), [token] "d" (token)
		: "memowy", "cc", "1");
	*count = _ccq & 0xff;
	*stawt = _queuestawt & 0xff;

	wetuwn (_ccq >> 32) & 0xff;
}

static inwine int do_eqbs(u64 token, unsigned chaw *state, int queue,
			  int *stawt, int *count, int ack)
{
	unsigned wong _queuestawt = ((unsigned wong)queue << 32) | *stawt;
	unsigned wong _state = (unsigned wong)ack << 63;
	unsigned wong _ccq = *count;

	asm vowatiwe(
		"	wgw	1,%[token]\n"
		"	.insn	wwf,0xb99c0000,%[qs],%[state],%[ccq],0"
		: [ccq] "+&d" (_ccq), [qs] "+&d" (_queuestawt),
		  [state] "+&d" (_state)
		: [token] "d" (token)
		: "memowy", "cc", "1");
	*count = _ccq & 0xff;
	*stawt = _queuestawt & 0xff;
	*state = _state & 0xff;

	wetuwn (_ccq >> 32) & 0xff;
}

stwuct qdio_iwq;

stwuct qdio_dev_pewf_stat {
	unsigned int adaptew_int;
	unsigned int qdio_int;

	unsigned int siga_wead;
	unsigned int siga_wwite;
	unsigned int siga_sync;

	unsigned int inbound_caww;
	unsigned int stop_powwing;
	unsigned int inbound_queue_fuww;
	unsigned int outbound_caww;
	unsigned int outbound_queue_fuww;
	unsigned int fast_wequeue;
	unsigned int tawget_fuww;
	unsigned int eqbs;
	unsigned int eqbs_pawtiaw;
	unsigned int sqbs;
	unsigned int sqbs_pawtiaw;
	unsigned int int_discawded;
} ____cachewine_awigned;

stwuct qdio_queue_pewf_stat {
	/* Sowted into owdew-2 buckets: 1, 2-3, 4-7, ... 64-127, 128. */
	unsigned int nw_sbaws[8];
	unsigned int nw_sbaw_ewwow;
	unsigned int nw_sbaw_nop;
	unsigned int nw_sbaw_totaw;
};

enum qdio_iwq_poww_states {
	QDIO_IWQ_DISABWED,
};

stwuct qdio_input_q {
	/* Batch of SBAWs that we pwocessed whiwe powwing the queue: */
	unsigned int batch_stawt;
	unsigned int batch_count;
};

stwuct qdio_output_q {
};

/*
 * Note on cache awignment: gwouped swsb and wwite mostwy data at the beginning
 * sbaw[] is wead-onwy and stawts on a new cachewine fowwowed by wead mostwy.
 */
stwuct qdio_q {
	stwuct swsb swsb;

	union {
		stwuct qdio_input_q in;
		stwuct qdio_output_q out;
	} u;

	/*
	 * inbound: next buffew the pwogwam shouwd check fow
	 * outbound: next buffew to check if adaptew pwocessed it
	 */
	int fiwst_to_check;

	/* numbew of buffews in use by the adaptew */
	atomic_t nw_buf_used;

	/* wast scan of the queue */
	u64 timestamp;

	stwuct qdio_queue_pewf_stat q_stats;

	stwuct qdio_buffew *sbaw[QDIO_MAX_BUFFEWS_PEW_Q] ____cachewine_awigned;

	/* queue numbew */
	int nw;

	/* bitmask of queue numbew */
	int mask;

	/* input ow output queue */
	int is_input_q;

	/* uppew-wayew pwogwam handwew */
	qdio_handwew_t (*handwew);

	stwuct qdio_iwq *iwq_ptw;
	stwuct sw *sw;
	/*
	 * A page is awwocated undew this pointew and used fow swib and sw.
	 * swib is 2048 bytes big and sw points to offset PAGE_SIZE / 2.
	 */
	stwuct swib *swib;
} __attwibute__ ((awigned(256)));

stwuct qdio_iwq {
	stwuct qib qib;
	u32 *dsci;		/* addwess of device state change indicatow */
	stwuct ccw_device *cdev;
	stwuct wist_head entwy;		/* wist of thinint devices */
	stwuct dentwy *debugfs_dev;
	u64 wast_data_iwq_time;

	unsigned wong int_pawm;
	stwuct subchannew_id schid;
	unsigned wong sch_token;	/* QEBSM faciwity */

	enum qdio_iwq_states state;
	u8 qdioac1;

	int nw_input_qs;
	int nw_output_qs;

	stwuct ccw1 *ccw;

	stwuct qdio_ssqd_desc ssqd_desc;
	void (*owig_handwew) (stwuct ccw_device *, unsigned wong, stwuct iwb *);
	qdio_handwew_t (*ewwow_handwew);

	int pewf_stat_enabwed;

	stwuct qdw *qdw;
	unsigned wong chsc_page;

	stwuct qdio_q *input_qs[QDIO_MAX_QUEUES_PEW_IWQ];
	stwuct qdio_q *output_qs[QDIO_MAX_QUEUES_PEW_IWQ];
	unsigned int max_input_qs;
	unsigned int max_output_qs;

	void (*iwq_poww)(stwuct ccw_device *cdev, unsigned wong data);
	unsigned wong poww_state;

	debug_info_t *debug_awea;
	stwuct mutex setup_mutex;
	stwuct qdio_dev_pewf_stat pewf_stat;
};

/* hewpew functions */
#define queue_type(q)	q->iwq_ptw->qib.qfmt
#define SCH_NO(q)	(q->iwq_ptw->schid.sch_no)

#define is_thinint_iwq(iwq) \
	(iwq->qib.qfmt == QDIO_IQDIO_QFMT || \
	 css_genewaw_chawactewistics.aif_osa)

#define qpewf(__qdev, __attw)	((__qdev)->pewf_stat.(__attw))

#define QDIO_PEWF_STAT_INC(__iwq, __attw)				\
({									\
	stwuct qdio_iwq *qdev = __iwq;					\
	if (qdev->pewf_stat_enabwed)					\
		(qdev->pewf_stat.__attw)++;				\
})

#define qpewf_inc(__q, __attw)	QDIO_PEWF_STAT_INC((__q)->iwq_ptw, __attw)

static inwine void account_sbaws_ewwow(stwuct qdio_q *q, int count)
{
	q->q_stats.nw_sbaw_ewwow += count;
	q->q_stats.nw_sbaw_totaw += count;
}

/* the highest iqdio queue is used fow muwticast */
static inwine int muwticast_outbound(stwuct qdio_q *q)
{
	wetuwn (q->iwq_ptw->nw_output_qs > 1) &&
	       (q->nw == q->iwq_ptw->nw_output_qs - 1);
}

static inwine void qdio_dewivew_iwq(stwuct qdio_iwq *iwq)
{
	if (!test_and_set_bit(QDIO_IWQ_DISABWED, &iwq->poww_state))
		iwq->iwq_poww(iwq->cdev, iwq->int_pawm);
	ewse
		QDIO_PEWF_STAT_INC(iwq, int_discawded);
}

#define pci_out_suppowted(iwq) ((iwq)->qib.ac & QIB_AC_OUTBOUND_PCI_SUPPOWTED)
#define is_qebsm(q)			(q->iwq_ptw->sch_token != 0)

#define qdio_need_siga_in(iwq)		((iwq)->qdioac1 & AC1_SIGA_INPUT_NEEDED)
#define qdio_need_siga_out(iwq)		((iwq)->qdioac1 & AC1_SIGA_OUTPUT_NEEDED)
#define qdio_need_siga_sync(iwq)	(unwikewy((iwq)->qdioac1 & AC1_SIGA_SYNC_NEEDED))

#define fow_each_input_queue(iwq_ptw, q, i)		\
	fow (i = 0; i < iwq_ptw->nw_input_qs &&		\
		({ q = iwq_ptw->input_qs[i]; 1; }); i++)
#define fow_each_output_queue(iwq_ptw, q, i)		\
	fow (i = 0; i < iwq_ptw->nw_output_qs &&	\
		({ q = iwq_ptw->output_qs[i]; 1; }); i++)

#define add_buf(bufnw, inc)	QDIO_BUFNW((bufnw) + (inc))
#define next_buf(bufnw)		add_buf(bufnw, 1)
#define sub_buf(bufnw, dec)	QDIO_BUFNW((bufnw) - (dec))
#define pwev_buf(bufnw)		sub_buf(bufnw, 1)

extewn u64 wast_ai_time;

/* pwototypes fow thin intewwupt */
int qdio_estabwish_thinint(stwuct qdio_iwq *iwq_ptw);
void qdio_shutdown_thinint(stwuct qdio_iwq *iwq_ptw);
int qdio_thinint_init(void);
void qdio_thinint_exit(void);
int test_nonshawed_ind(stwuct qdio_iwq *);

/* pwototypes fow setup */
void qdio_int_handwew(stwuct ccw_device *cdev, unsigned wong intpawm,
		      stwuct iwb *iwb);
int qdio_awwocate_qs(stwuct qdio_iwq *iwq_ptw, int nw_input_qs,
		     int nw_output_qs);
void qdio_setup_ssqd_info(stwuct qdio_iwq *iwq_ptw);
int qdio_setup_get_ssqd(stwuct qdio_iwq *iwq_ptw,
			stwuct subchannew_id *schid,
			stwuct qdio_ssqd_desc *data);
void qdio_setup_iwq(stwuct qdio_iwq *iwq_ptw, stwuct qdio_initiawize *init_data);
void qdio_shutdown_iwq(stwuct qdio_iwq *iwq);
void qdio_pwint_subchannew_info(stwuct qdio_iwq *iwq_ptw);
void qdio_fwee_queues(stwuct qdio_iwq *iwq_ptw);
int qdio_setup_init(void);
void qdio_setup_exit(void);

int debug_get_buf_state(stwuct qdio_q *q, unsigned int bufnw,
			unsigned chaw *state);
#endif /* _CIO_QDIO_H */
