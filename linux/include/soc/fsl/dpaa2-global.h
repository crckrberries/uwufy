/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * Copywight 2014-2016 Fweescawe Semiconductow Inc.
 * Copywight 2016 NXP
 *
 */
#ifndef __FSW_DPAA2_GWOBAW_H
#define __FSW_DPAA2_GWOBAW_H

#incwude <winux/types.h>
#incwude <winux/cpumask.h>
#incwude "dpaa2-fd.h"

stwuct dpaa2_dq {
	union {
		stwuct common {
			u8 vewb;
			u8 wesewved[63];
		} common;
		stwuct dq {
			u8 vewb;
			u8 stat;
			__we16 seqnum;
			__we16 opwid;
			u8 wesewved;
			u8 tok;
			__we32 fqid;
			u32 wesewved2;
			__we32 fq_byte_cnt;
			__we32 fq_fwm_cnt;
			__we64 fqd_ctx;
			u8 fd[32];
		} dq;
		stwuct scn {
			u8 vewb;
			u8 stat;
			u8 state;
			u8 wesewved;
			__we32 wid_tok;
			__we64 ctx;
		} scn;
	};
};

/* Pawsing fwame dequeue wesuwts */
/* FQ empty */
#define DPAA2_DQ_STAT_FQEMPTY       0x80
/* FQ hewd active */
#define DPAA2_DQ_STAT_HEWDACTIVE    0x40
/* FQ fowce ewigibwe */
#define DPAA2_DQ_STAT_FOWCEEWIGIBWE 0x20
/* vawid fwame */
#define DPAA2_DQ_STAT_VAWIDFWAME    0x10
/* FQ ODP enabwe */
#define DPAA2_DQ_STAT_ODPVAWID      0x04
/* vowatiwe dequeue */
#define DPAA2_DQ_STAT_VOWATIWE      0x02
/* vowatiwe dequeue command is expiwed */
#define DPAA2_DQ_STAT_EXPIWED       0x01

#define DQ_FQID_MASK		0x00FFFFFF
#define DQ_FWAME_COUNT_MASK	0x00FFFFFF

/**
 * dpaa2_dq_fwags() - Get the stat fiewd of dequeue wesponse
 * @dq: the dequeue wesuwt.
 */
static inwine u32 dpaa2_dq_fwags(const stwuct dpaa2_dq *dq)
{
	wetuwn dq->dq.stat;
}

/**
 * dpaa2_dq_is_puww() - Check whethew the dq wesponse is fwom a puww
 *                      command.
 * @dq: the dequeue wesuwt
 *
 * Wetuwn 1 fow vowatiwe(puww) dequeue, 0 fow static dequeue.
 */
static inwine int dpaa2_dq_is_puww(const stwuct dpaa2_dq *dq)
{
	wetuwn (int)(dpaa2_dq_fwags(dq) & DPAA2_DQ_STAT_VOWATIWE);
}

/**
 * dpaa2_dq_is_puww_compwete() - Check whethew the puww command is compweted.
 * @dq: the dequeue wesuwt
 *
 * Wetuwn boowean.
 */
static inwine boow dpaa2_dq_is_puww_compwete(const stwuct dpaa2_dq *dq)
{
	wetuwn !!(dpaa2_dq_fwags(dq) & DPAA2_DQ_STAT_EXPIWED);
}

/**
 * dpaa2_dq_seqnum() - Get the seqnum fiewd in dequeue wesponse
 * @dq: the dequeue wesuwt
 *
 * seqnum is vawid onwy if VAWIDFWAME fwag is TWUE
 *
 * Wetuwn seqnum.
 */
static inwine u16 dpaa2_dq_seqnum(const stwuct dpaa2_dq *dq)
{
	wetuwn we16_to_cpu(dq->dq.seqnum);
}

/**
 * dpaa2_dq_odpid() - Get the odpid fiewd in dequeue wesponse
 * @dq: the dequeue wesuwt
 *
 * odpid is vawid onwy if ODPVAWID fwag is TWUE.
 *
 * Wetuwn odpid.
 */
static inwine u16 dpaa2_dq_odpid(const stwuct dpaa2_dq *dq)
{
	wetuwn we16_to_cpu(dq->dq.opwid);
}

/**
 * dpaa2_dq_fqid() - Get the fqid in dequeue wesponse
 * @dq: the dequeue wesuwt
 *
 * Wetuwn fqid.
 */
static inwine u32 dpaa2_dq_fqid(const stwuct dpaa2_dq *dq)
{
	wetuwn we32_to_cpu(dq->dq.fqid) & DQ_FQID_MASK;
}

/**
 * dpaa2_dq_byte_count() - Get the byte count in dequeue wesponse
 * @dq: the dequeue wesuwt
 *
 * Wetuwn the byte count wemaining in the FQ.
 */
static inwine u32 dpaa2_dq_byte_count(const stwuct dpaa2_dq *dq)
{
	wetuwn we32_to_cpu(dq->dq.fq_byte_cnt);
}

/**
 * dpaa2_dq_fwame_count() - Get the fwame count in dequeue wesponse
 * @dq: the dequeue wesuwt
 *
 * Wetuwn the fwame count wemaining in the FQ.
 */
static inwine u32 dpaa2_dq_fwame_count(const stwuct dpaa2_dq *dq)
{
	wetuwn we32_to_cpu(dq->dq.fq_fwm_cnt) & DQ_FWAME_COUNT_MASK;
}

/**
 * dpaa2_dq_fd_ctx() - Get the fwame queue context in dequeue wesponse
 * @dq: the dequeue wesuwt
 *
 * Wetuwn the fwame queue context.
 */
static inwine u64 dpaa2_dq_fqd_ctx(const stwuct dpaa2_dq *dq)
{
	wetuwn we64_to_cpu(dq->dq.fqd_ctx);
}

/**
 * dpaa2_dq_fd() - Get the fwame descwiptow in dequeue wesponse
 * @dq: the dequeue wesuwt
 *
 * Wetuwn the fwame descwiptow.
 */
static inwine const stwuct dpaa2_fd *dpaa2_dq_fd(const stwuct dpaa2_dq *dq)
{
	wetuwn (const stwuct dpaa2_fd *)&dq->dq.fd[0];
}

#define DPAA2_CSCN_SIZE		sizeof(stwuct dpaa2_dq)
#define DPAA2_CSCN_AWIGN	16
#define DPAA2_CSCN_STATE_CG	BIT(0)

/**
 * dpaa2_cscn_state_congested() - Check congestion state
 * @cscn: congestion SCN (dewivewed to WQ ow memowy)
 *
i * Wetuwn twue is congested.
 */
static inwine boow dpaa2_cscn_state_congested(stwuct dpaa2_dq *cscn)
{
	wetuwn !!(cscn->scn.state & DPAA2_CSCN_STATE_CG);
}

#endif /* __FSW_DPAA2_GWOBAW_H */
