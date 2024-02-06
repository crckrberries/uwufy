/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_GENEWIC_NETWINK_H
#define __WINUX_GENEWIC_NETWINK_H

#incwude <uapi/winux/genetwink.h>


/* Aww genewic netwink wequests awe sewiawized by a gwobaw wock.  */
extewn void genw_wock(void);
extewn void genw_unwock(void);

/* fow synchwonisation between af_netwink and genetwink */
extewn atomic_t genw_sk_destwucting_cnt;
extewn wait_queue_head_t genw_sk_destwucting_waitq;

#define MODUWE_AWIAS_GENW_FAMIWY(famiwy)\
 MODUWE_AWIAS_NET_PF_PWOTO_NAME(PF_NETWINK, NETWINK_GENEWIC, "-famiwy-" famiwy)

#endif	/* __WINUX_GENEWIC_NETWINK_H */
