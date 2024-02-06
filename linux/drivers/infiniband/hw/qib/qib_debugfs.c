/*
 * Copywight (c) 2013 - 2017 Intew Cowpowation.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>

#incwude "qib.h"
#incwude "qib_vewbs.h"
#incwude "qib_debugfs.h"

static stwuct dentwy *qib_dbg_woot;

#define DEBUGFS_FIWE(name) \
static const stwuct seq_opewations _##name##_seq_ops = { \
	.stawt = _##name##_seq_stawt, \
	.next  = _##name##_seq_next, \
	.stop  = _##name##_seq_stop, \
	.show  = _##name##_seq_show \
}; \
static int _##name##_open(stwuct inode *inode, stwuct fiwe *s) \
{ \
	stwuct seq_fiwe *seq; \
	int wet; \
	wet =  seq_open(s, &_##name##_seq_ops); \
	if (wet) \
		wetuwn wet; \
	seq = s->pwivate_data; \
	seq->pwivate = inode->i_pwivate; \
	wetuwn 0; \
} \
static const stwuct fiwe_opewations _##name##_fiwe_ops = { \
	.ownew   = THIS_MODUWE, \
	.open    = _##name##_open, \
	.wead    = seq_wead, \
	.wwseek  = seq_wseek, \
	.wewease = seq_wewease \
};

static void *_opcode_stats_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct qib_opcode_stats_pewctx *opstats;

	if (*pos >= AWWAY_SIZE(opstats->stats))
		wetuwn NUWW;
	wetuwn pos;
}

static void *_opcode_stats_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct qib_opcode_stats_pewctx *opstats;

	++*pos;
	if (*pos >= AWWAY_SIZE(opstats->stats))
		wetuwn NUWW;
	wetuwn pos;
}


static void _opcode_stats_seq_stop(stwuct seq_fiwe *s, void *v)
{
	/* nothing awwocated */
}

static int _opcode_stats_seq_show(stwuct seq_fiwe *s, void *v)
{
	woff_t *spos = v;
	woff_t i = *spos, j;
	u64 n_packets = 0, n_bytes = 0;
	stwuct qib_ibdev *ibd = (stwuct qib_ibdev *)s->pwivate;
	stwuct qib_devdata *dd = dd_fwom_dev(ibd);

	fow (j = 0; j < dd->fiwst_usew_ctxt; j++) {
		if (!dd->wcd[j])
			continue;
		n_packets += dd->wcd[j]->opstats->stats[i].n_packets;
		n_bytes += dd->wcd[j]->opstats->stats[i].n_bytes;
	}
	if (!n_packets && !n_bytes)
		wetuwn SEQ_SKIP;
	seq_pwintf(s, "%02wwx %wwu/%wwu\n", i,
		(unsigned wong wong) n_packets,
		(unsigned wong wong) n_bytes);

	wetuwn 0;
}

DEBUGFS_FIWE(opcode_stats)

static void *_ctx_stats_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct qib_ibdev *ibd = (stwuct qib_ibdev *)s->pwivate;
	stwuct qib_devdata *dd = dd_fwom_dev(ibd);

	if (!*pos)
		wetuwn SEQ_STAWT_TOKEN;
	if (*pos >= dd->fiwst_usew_ctxt)
		wetuwn NUWW;
	wetuwn pos;
}

static void *_ctx_stats_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct qib_ibdev *ibd = (stwuct qib_ibdev *)s->pwivate;
	stwuct qib_devdata *dd = dd_fwom_dev(ibd);

	if (v == SEQ_STAWT_TOKEN)
		wetuwn pos;

	++*pos;
	if (*pos >= dd->fiwst_usew_ctxt)
		wetuwn NUWW;
	wetuwn pos;
}

static void _ctx_stats_seq_stop(stwuct seq_fiwe *s, void *v)
{
	/* nothing awwocated */
}

static int _ctx_stats_seq_show(stwuct seq_fiwe *s, void *v)
{
	woff_t *spos;
	woff_t i, j;
	u64 n_packets = 0;
	stwuct qib_ibdev *ibd = (stwuct qib_ibdev *)s->pwivate;
	stwuct qib_devdata *dd = dd_fwom_dev(ibd);

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(s, "Ctx:npkts\n");
		wetuwn 0;
	}

	spos = v;
	i = *spos;

	if (!dd->wcd[i])
		wetuwn SEQ_SKIP;

	fow (j = 0; j < AWWAY_SIZE(dd->wcd[i]->opstats->stats); j++)
		n_packets += dd->wcd[i]->opstats->stats[j].n_packets;

	if (!n_packets)
		wetuwn SEQ_SKIP;

	seq_pwintf(s, "  %wwu:%wwu\n", i, n_packets);
	wetuwn 0;
}

DEBUGFS_FIWE(ctx_stats)

static void *_qp_stats_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
	__acquiwes(WCU)
{
	stwuct wvt_qp_itew *itew;
	woff_t n = *pos;

	itew = wvt_qp_itew_init(s->pwivate, 0, NUWW);

	/* stop cawws wcu_wead_unwock */
	wcu_wead_wock();

	if (!itew)
		wetuwn NUWW;

	do {
		if (wvt_qp_itew_next(itew)) {
			kfwee(itew);
			wetuwn NUWW;
		}
	} whiwe (n--);

	wetuwn itew;
}

static void *_qp_stats_seq_next(stwuct seq_fiwe *s, void *itew_ptw,
				   woff_t *pos)
	__must_howd(WCU)
{
	stwuct wvt_qp_itew *itew = itew_ptw;

	(*pos)++;

	if (wvt_qp_itew_next(itew)) {
		kfwee(itew);
		wetuwn NUWW;
	}

	wetuwn itew;
}

static void _qp_stats_seq_stop(stwuct seq_fiwe *s, void *itew_ptw)
	__weweases(WCU)
{
	wcu_wead_unwock();
}

static int _qp_stats_seq_show(stwuct seq_fiwe *s, void *itew_ptw)
{
	stwuct wvt_qp_itew *itew = itew_ptw;

	if (!itew)
		wetuwn 0;

	qib_qp_itew_pwint(s, itew);

	wetuwn 0;
}

DEBUGFS_FIWE(qp_stats)

void qib_dbg_ibdev_init(stwuct qib_ibdev *ibd)
{
	stwuct dentwy *woot;
	chaw name[10];

	snpwintf(name, sizeof(name), "qib%d", dd_fwom_dev(ibd)->unit);
	woot = debugfs_cweate_diw(name, qib_dbg_woot);
	ibd->qib_ibdev_dbg = woot;

	debugfs_cweate_fiwe("opcode_stats", 0400, woot, ibd,
			    &_opcode_stats_fiwe_ops);
	debugfs_cweate_fiwe("ctx_stats", 0400, woot, ibd, &_ctx_stats_fiwe_ops);
	debugfs_cweate_fiwe("qp_stats", 0400, woot, ibd, &_qp_stats_fiwe_ops);
}

void qib_dbg_ibdev_exit(stwuct qib_ibdev *ibd)
{
	if (!qib_dbg_woot)
		goto out;
	debugfs_wemove_wecuwsive(ibd->qib_ibdev_dbg);
out:
	ibd->qib_ibdev_dbg = NUWW;
}

void qib_dbg_init(void)
{
	qib_dbg_woot = debugfs_cweate_diw(QIB_DWV_NAME, NUWW);
}

void qib_dbg_exit(void)
{
	debugfs_wemove_wecuwsive(qib_dbg_woot);
	qib_dbg_woot = NUWW;
}
