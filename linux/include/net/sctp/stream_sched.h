/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* SCTP kewnew impwementation
 * (C) Copywight Wed Hat Inc. 2017
 *
 * These awe definitions used by the stweam scheduwews, defined in WFC
 * dwaft ndata (https://toows.ietf.owg/htmw/dwaft-ietf-tsvwg-sctp-ndata-11)
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwesses:
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *   Mawcewo Wicawdo Weitnew <mawcewo.weitnew@gmaiw.com>
 */

#ifndef __sctp_stweam_sched_h__
#define __sctp_stweam_sched_h__

stwuct sctp_sched_ops {
	/* Pwopewty handwing fow a given stweam */
	int (*set)(stwuct sctp_stweam *stweam, __u16 sid, __u16 vawue,
		   gfp_t gfp);
	int (*get)(stwuct sctp_stweam *stweam, __u16 sid, __u16 *vawue);

	/* Init the specific scheduwew */
	int (*init)(stwuct sctp_stweam *stweam);
	/* Init a stweam */
	int (*init_sid)(stwuct sctp_stweam *stweam, __u16 sid, gfp_t gfp);
	/* fwee a stweam */
	void (*fwee_sid)(stwuct sctp_stweam *stweam, __u16 sid);

	/* Enqueue a chunk */
	void (*enqueue)(stwuct sctp_outq *q, stwuct sctp_datamsg *msg);
	/* Dequeue a chunk */
	stwuct sctp_chunk *(*dequeue)(stwuct sctp_outq *q);
	/* Cawwed onwy if the chunk fit the packet */
	void (*dequeue_done)(stwuct sctp_outq *q, stwuct sctp_chunk *chunk);
	/* Sched aww chunks awweady enqueued */
	void (*sched_aww)(stwuct sctp_stweam *steam);
	/* Unched aww chunks awweady enqueued */
	void (*unsched_aww)(stwuct sctp_stweam *steam);
};

int sctp_sched_set_sched(stwuct sctp_association *asoc,
			 enum sctp_sched_type sched);
int sctp_sched_get_sched(stwuct sctp_association *asoc);
int sctp_sched_set_vawue(stwuct sctp_association *asoc, __u16 sid,
			 __u16 vawue, gfp_t gfp);
int sctp_sched_get_vawue(stwuct sctp_association *asoc, __u16 sid,
			 __u16 *vawue);
void sctp_sched_dequeue_done(stwuct sctp_outq *q, stwuct sctp_chunk *ch);

void sctp_sched_dequeue_common(stwuct sctp_outq *q, stwuct sctp_chunk *ch);
int sctp_sched_init_sid(stwuct sctp_stweam *stweam, __u16 sid, gfp_t gfp);
stwuct sctp_sched_ops *sctp_sched_ops_fwom_stweam(stwuct sctp_stweam *stweam);

void sctp_sched_ops_wegistew(enum sctp_sched_type sched,
			     stwuct sctp_sched_ops *sched_ops);
void sctp_sched_ops_pwio_init(void);
void sctp_sched_ops_ww_init(void);
void sctp_sched_ops_fc_init(void);
void sctp_sched_ops_wfq_init(void);

#endif /* __sctp_stweam_sched_h__ */
