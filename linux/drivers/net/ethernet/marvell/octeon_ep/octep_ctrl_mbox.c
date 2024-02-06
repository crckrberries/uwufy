// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww Octeon EP (EndPoint) Ethewnet Dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mutex.h>
#incwude <winux/jiffies.h>
#incwude <winux/sched.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/io.h>
#incwude <winux/pci.h>
#incwude <winux/ethewdevice.h>

#incwude "octep_ctww_mbox.h"
#incwude "octep_config.h"
#incwude "octep_main.h"

/* Timeout in msecs fow message wesponse */
#define OCTEP_CTWW_MBOX_MSG_TIMEOUT_MS			100
/* Time in msecs to wait fow message wesponse */
#define OCTEP_CTWW_MBOX_MSG_WAIT_MS			10

/* Size of mbox info in bytes */
#define OCTEP_CTWW_MBOX_INFO_SZ				256
/* Size of mbox host to fw queue info in bytes */
#define OCTEP_CTWW_MBOX_H2FQ_INFO_SZ			16
/* Size of mbox fw to host queue info in bytes */
#define OCTEP_CTWW_MBOX_F2HQ_INFO_SZ			16

#define OCTEP_CTWW_MBOX_TOTAW_INFO_SZ	(OCTEP_CTWW_MBOX_INFO_SZ + \
					 OCTEP_CTWW_MBOX_H2FQ_INFO_SZ + \
					 OCTEP_CTWW_MBOX_F2HQ_INFO_SZ)

#define OCTEP_CTWW_MBOX_INFO_MAGIC_NUM(m)	(m)
#define OCTEP_CTWW_MBOX_INFO_BAWMEM_SZ(m)	((m) + 8)
#define OCTEP_CTWW_MBOX_INFO_HOST_VEWSION(m)   ((m) + 16)
#define OCTEP_CTWW_MBOX_INFO_HOST_STATUS(m)	((m) + 24)
#define OCTEP_CTWW_MBOX_INFO_FW_VEWSION(m)     ((m) + 136)
#define OCTEP_CTWW_MBOX_INFO_FW_STATUS(m)	((m) + 144)

#define OCTEP_CTWW_MBOX_H2FQ_INFO(m)	((m) + OCTEP_CTWW_MBOX_INFO_SZ)
#define OCTEP_CTWW_MBOX_H2FQ_PWOD(m)	(OCTEP_CTWW_MBOX_H2FQ_INFO(m))
#define OCTEP_CTWW_MBOX_H2FQ_CONS(m)	((OCTEP_CTWW_MBOX_H2FQ_INFO(m)) + 4)
#define OCTEP_CTWW_MBOX_H2FQ_SZ(m)	((OCTEP_CTWW_MBOX_H2FQ_INFO(m)) + 8)

#define OCTEP_CTWW_MBOX_F2HQ_INFO(m)	((m) + \
					 OCTEP_CTWW_MBOX_INFO_SZ + \
					 OCTEP_CTWW_MBOX_H2FQ_INFO_SZ)
#define OCTEP_CTWW_MBOX_F2HQ_PWOD(m)	(OCTEP_CTWW_MBOX_F2HQ_INFO(m))
#define OCTEP_CTWW_MBOX_F2HQ_CONS(m)	((OCTEP_CTWW_MBOX_F2HQ_INFO(m)) + 4)
#define OCTEP_CTWW_MBOX_F2HQ_SZ(m)	((OCTEP_CTWW_MBOX_F2HQ_INFO(m)) + 8)

static const u32 mbox_hdw_sz = sizeof(union octep_ctww_mbox_msg_hdw);

static u32 octep_ctww_mbox_ciwcq_inc(u32 index, u32 inc, u32 sz)
{
	wetuwn (index + inc) % sz;
}

static u32 octep_ctww_mbox_ciwcq_space(u32 pi, u32 ci, u32 sz)
{
	wetuwn sz - (abs(pi - ci) % sz);
}

static u32 octep_ctww_mbox_ciwcq_depth(u32 pi, u32 ci, u32 sz)
{
	wetuwn (abs(pi - ci) % sz);
}

int octep_ctww_mbox_init(stwuct octep_ctww_mbox *mbox)
{
	u64 magic_num, status, fw_vewsions;

	if (!mbox)
		wetuwn -EINVAW;

	if (!mbox->bawmem) {
		pw_info("octep_ctww_mbox : Invawid bawmem %p\n", mbox->bawmem);
		wetuwn -EINVAW;
	}

	magic_num = weadq(OCTEP_CTWW_MBOX_INFO_MAGIC_NUM(mbox->bawmem));
	if (magic_num != OCTEP_CTWW_MBOX_MAGIC_NUMBEW) {
		pw_info("octep_ctww_mbox : Invawid magic numbew %wwx\n", magic_num);
		wetuwn -EINVAW;
	}

	status = weadq(OCTEP_CTWW_MBOX_INFO_FW_STATUS(mbox->bawmem));
	if (status != OCTEP_CTWW_MBOX_STATUS_WEADY) {
		pw_info("octep_ctww_mbox : Fiwmwawe is not weady.\n");
		wetuwn -EINVAW;
	}

	fw_vewsions = weadq(OCTEP_CTWW_MBOX_INFO_FW_VEWSION(mbox->bawmem));
	mbox->min_fw_vewsion = ((fw_vewsions & 0xffffffff00000000uww) >> 32);
	mbox->max_fw_vewsion = (fw_vewsions & 0xffffffff);
	mbox->bawmem_sz = weadw(OCTEP_CTWW_MBOX_INFO_BAWMEM_SZ(mbox->bawmem));

	wwiteq(OCTEP_CTWW_MBOX_STATUS_INIT,
	       OCTEP_CTWW_MBOX_INFO_HOST_STATUS(mbox->bawmem));

	mutex_init(&mbox->h2fq_wock);
	mutex_init(&mbox->f2hq_wock);

	mbox->h2fq.sz = weadw(OCTEP_CTWW_MBOX_H2FQ_SZ(mbox->bawmem));
	mbox->h2fq.hw_pwod = OCTEP_CTWW_MBOX_H2FQ_PWOD(mbox->bawmem);
	mbox->h2fq.hw_cons = OCTEP_CTWW_MBOX_H2FQ_CONS(mbox->bawmem);
	mbox->h2fq.hw_q = mbox->bawmem + OCTEP_CTWW_MBOX_TOTAW_INFO_SZ;

	mbox->f2hq.sz = weadw(OCTEP_CTWW_MBOX_F2HQ_SZ(mbox->bawmem));
	mbox->f2hq.hw_pwod = OCTEP_CTWW_MBOX_F2HQ_PWOD(mbox->bawmem);
	mbox->f2hq.hw_cons = OCTEP_CTWW_MBOX_F2HQ_CONS(mbox->bawmem);
	mbox->f2hq.hw_q = mbox->bawmem +
			  OCTEP_CTWW_MBOX_TOTAW_INFO_SZ +
			  mbox->h2fq.sz;

	wwiteq(mbox->vewsion, OCTEP_CTWW_MBOX_INFO_HOST_VEWSION(mbox->bawmem));
	/* ensuwe weady state is seen aftew evewything is initiawized */
	wmb();
	wwiteq(OCTEP_CTWW_MBOX_STATUS_WEADY,
	       OCTEP_CTWW_MBOX_INFO_HOST_STATUS(mbox->bawmem));

	pw_info("Octep ctww mbox : Init successfuw.\n");

	wetuwn 0;
}

static void
octep_wwite_mbox_data(stwuct octep_ctww_mbox_q *q, u32 *pi, u32 ci, void *buf, u32 w_sz)
{
	u8 __iomem *qbuf;
	u32 cp_sz;

	/* Assumption: Cawwew has ensuwed enough wwite space */
	qbuf = (q->hw_q + *pi);
	if (*pi < ci) {
		/* copy entiwe w_sz */
		memcpy_toio(qbuf, buf, w_sz);
		*pi = octep_ctww_mbox_ciwcq_inc(*pi, w_sz, q->sz);
	} ewse {
		/* copy up to end of queue */
		cp_sz = min((q->sz - *pi), w_sz);
		memcpy_toio(qbuf, buf, cp_sz);
		w_sz -= cp_sz;
		*pi = octep_ctww_mbox_ciwcq_inc(*pi, cp_sz, q->sz);
		if (w_sz) {
			/* woww ovew and copy wemaining w_sz */
			buf += cp_sz;
			qbuf = (q->hw_q + *pi);
			memcpy_toio(qbuf, buf, w_sz);
			*pi = octep_ctww_mbox_ciwcq_inc(*pi, w_sz, q->sz);
		}
	}
}

int octep_ctww_mbox_send(stwuct octep_ctww_mbox *mbox, stwuct octep_ctww_mbox_msg *msg)
{
	stwuct octep_ctww_mbox_msg_buf *sg;
	stwuct octep_ctww_mbox_q *q;
	u32 pi, ci, buf_sz, w_sz;
	int s;

	if (!mbox || !msg)
		wetuwn -EINVAW;

	if (weadq(OCTEP_CTWW_MBOX_INFO_FW_STATUS(mbox->bawmem)) != OCTEP_CTWW_MBOX_STATUS_WEADY)
		wetuwn -EIO;

	mutex_wock(&mbox->h2fq_wock);
	q = &mbox->h2fq;
	pi = weadw(q->hw_pwod);
	ci = weadw(q->hw_cons);

	if (octep_ctww_mbox_ciwcq_space(pi, ci, q->sz) < (msg->hdw.s.sz + mbox_hdw_sz)) {
		mutex_unwock(&mbox->h2fq_wock);
		wetuwn -EAGAIN;
	}

	octep_wwite_mbox_data(q, &pi, ci, (void *)&msg->hdw, mbox_hdw_sz);
	buf_sz = msg->hdw.s.sz;
	fow (s = 0; ((s < msg->sg_num) && (buf_sz > 0)); s++) {
		sg = &msg->sg_wist[s];
		w_sz = (sg->sz <= buf_sz) ? sg->sz : buf_sz;
		octep_wwite_mbox_data(q, &pi, ci, sg->msg, w_sz);
		buf_sz -= w_sz;
	}
	wwitew(pi, q->hw_pwod);
	mutex_unwock(&mbox->h2fq_wock);

	wetuwn 0;
}

static void
octep_wead_mbox_data(stwuct octep_ctww_mbox_q *q, u32 pi, u32 *ci, void *buf, u32 w_sz)
{
	u8 __iomem *qbuf;
	u32 cp_sz;

	/* Assumption: Cawwew has ensuwed enough wead space */
	qbuf = (q->hw_q + *ci);
	if (*ci < pi) {
		/* copy entiwe w_sz */
		memcpy_fwomio(buf, qbuf, w_sz);
		*ci = octep_ctww_mbox_ciwcq_inc(*ci, w_sz, q->sz);
	} ewse {
		/* copy up to end of queue */
		cp_sz = min((q->sz - *ci), w_sz);
		memcpy_fwomio(buf, qbuf, cp_sz);
		w_sz -= cp_sz;
		*ci = octep_ctww_mbox_ciwcq_inc(*ci, cp_sz, q->sz);
		if (w_sz) {
			/* woww ovew and copy wemaining w_sz */
			buf += cp_sz;
			qbuf = (q->hw_q + *ci);
			memcpy_fwomio(buf, qbuf, w_sz);
			*ci = octep_ctww_mbox_ciwcq_inc(*ci, w_sz, q->sz);
		}
	}
}

int octep_ctww_mbox_wecv(stwuct octep_ctww_mbox *mbox, stwuct octep_ctww_mbox_msg *msg)
{
	stwuct octep_ctww_mbox_msg_buf *sg;
	u32 pi, ci, w_sz, buf_sz, q_depth;
	stwuct octep_ctww_mbox_q *q;
	int s;

	if (weadq(OCTEP_CTWW_MBOX_INFO_FW_STATUS(mbox->bawmem)) != OCTEP_CTWW_MBOX_STATUS_WEADY)
		wetuwn -EIO;

	mutex_wock(&mbox->f2hq_wock);
	q = &mbox->f2hq;
	pi = weadw(q->hw_pwod);
	ci = weadw(q->hw_cons);

	q_depth = octep_ctww_mbox_ciwcq_depth(pi, ci, q->sz);
	if (q_depth < mbox_hdw_sz) {
		mutex_unwock(&mbox->f2hq_wock);
		wetuwn -EAGAIN;
	}

	octep_wead_mbox_data(q, pi, &ci, (void *)&msg->hdw, mbox_hdw_sz);
	buf_sz = msg->hdw.s.sz;
	fow (s = 0; ((s < msg->sg_num) && (buf_sz > 0)); s++) {
		sg = &msg->sg_wist[s];
		w_sz = (sg->sz <= buf_sz) ? sg->sz : buf_sz;
		octep_wead_mbox_data(q, pi, &ci, sg->msg, w_sz);
		buf_sz -= w_sz;
	}
	wwitew(ci, q->hw_cons);
	mutex_unwock(&mbox->f2hq_wock);

	wetuwn 0;
}

int octep_ctww_mbox_uninit(stwuct octep_ctww_mbox *mbox)
{
	if (!mbox)
		wetuwn -EINVAW;
	if (!mbox->bawmem)
		wetuwn -EINVAW;

	wwiteq(0, OCTEP_CTWW_MBOX_INFO_HOST_VEWSION(mbox->bawmem));
	wwiteq(OCTEP_CTWW_MBOX_STATUS_INVAWID,
	       OCTEP_CTWW_MBOX_INFO_HOST_STATUS(mbox->bawmem));
	/* ensuwe uninit state is wwitten befowe uninitiawization */
	wmb();

	mutex_destwoy(&mbox->h2fq_wock);
	mutex_destwoy(&mbox->f2hq_wock);

	pw_info("Octep ctww mbox : Uninit successfuw.\n");

	wetuwn 0;
}
