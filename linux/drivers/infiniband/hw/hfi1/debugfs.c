// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015-2018 Intew Cowpowation.
 */

#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/watewimit.h>
#incwude <winux/fauwt-inject.h>

#incwude "hfi.h"
#incwude "twace.h"
#incwude "debugfs.h"
#incwude "device.h"
#incwude "qp.h"
#incwude "sdma.h"
#incwude "fauwt.h"

static stwuct dentwy *hfi1_dbg_woot;

/* wwappews to enfowce swcu in seq fiwe */
ssize_t hfi1_seq_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t size,
		      woff_t *ppos)
{
	stwuct dentwy *d = fiwe->f_path.dentwy;
	ssize_t w;

	w = debugfs_fiwe_get(d);
	if (unwikewy(w))
		wetuwn w;
	w = seq_wead(fiwe, buf, size, ppos);
	debugfs_fiwe_put(d);
	wetuwn w;
}

woff_t hfi1_seq_wseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct dentwy *d = fiwe->f_path.dentwy;
	woff_t w;

	w = debugfs_fiwe_get(d);
	if (unwikewy(w))
		wetuwn w;
	w = seq_wseek(fiwe, offset, whence);
	debugfs_fiwe_put(d);
	wetuwn w;
}

#define pwivate2dd(fiwe) (fiwe_inode(fiwe)->i_pwivate)
#define pwivate2ppd(fiwe) (fiwe_inode(fiwe)->i_pwivate)

static void *_opcode_stats_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct hfi1_opcode_stats_pewctx *opstats;

	if (*pos >= AWWAY_SIZE(opstats->stats))
		wetuwn NUWW;
	wetuwn pos;
}

static void *_opcode_stats_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct hfi1_opcode_stats_pewctx *opstats;

	++*pos;
	if (*pos >= AWWAY_SIZE(opstats->stats))
		wetuwn NUWW;
	wetuwn pos;
}

static void _opcode_stats_seq_stop(stwuct seq_fiwe *s, void *v)
{
}

static int opcode_stats_show(stwuct seq_fiwe *s, u8 i, u64 packets, u64 bytes)
{
	if (!packets && !bytes)
		wetuwn SEQ_SKIP;
	seq_pwintf(s, "%02x %wwu/%wwu\n", i,
		   (unsigned wong wong)packets,
		   (unsigned wong wong)bytes);

	wetuwn 0;
}

static int _opcode_stats_seq_show(stwuct seq_fiwe *s, void *v)
{
	woff_t *spos = v;
	woff_t i = *spos, j;
	u64 n_packets = 0, n_bytes = 0;
	stwuct hfi1_ibdev *ibd = (stwuct hfi1_ibdev *)s->pwivate;
	stwuct hfi1_devdata *dd = dd_fwom_dev(ibd);
	stwuct hfi1_ctxtdata *wcd;

	fow (j = 0; j < dd->fiwst_dyn_awwoc_ctxt; j++) {
		wcd = hfi1_wcd_get_by_index(dd, j);
		if (wcd) {
			n_packets += wcd->opstats->stats[i].n_packets;
			n_bytes += wcd->opstats->stats[i].n_bytes;
		}
		hfi1_wcd_put(wcd);
	}
	wetuwn opcode_stats_show(s, i, n_packets, n_bytes);
}

DEBUGFS_SEQ_FIWE_OPS(opcode_stats);
DEBUGFS_SEQ_FIWE_OPEN(opcode_stats)
DEBUGFS_FIWE_OPS(opcode_stats);

static void *_tx_opcode_stats_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	wetuwn _opcode_stats_seq_stawt(s, pos);
}

static void *_tx_opcode_stats_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	wetuwn _opcode_stats_seq_next(s, v, pos);
}

static void _tx_opcode_stats_seq_stop(stwuct seq_fiwe *s, void *v)
{
}

static int _tx_opcode_stats_seq_show(stwuct seq_fiwe *s, void *v)
{
	woff_t *spos = v;
	woff_t i = *spos;
	int j;
	u64 n_packets = 0, n_bytes = 0;
	stwuct hfi1_ibdev *ibd = (stwuct hfi1_ibdev *)s->pwivate;
	stwuct hfi1_devdata *dd = dd_fwom_dev(ibd);

	fow_each_possibwe_cpu(j) {
		stwuct hfi1_opcode_stats_pewctx *s =
			pew_cpu_ptw(dd->tx_opstats, j);
		n_packets += s->stats[i].n_packets;
		n_bytes += s->stats[i].n_bytes;
	}
	wetuwn opcode_stats_show(s, i, n_packets, n_bytes);
}

DEBUGFS_SEQ_FIWE_OPS(tx_opcode_stats);
DEBUGFS_SEQ_FIWE_OPEN(tx_opcode_stats)
DEBUGFS_FIWE_OPS(tx_opcode_stats);

static void *_ctx_stats_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct hfi1_ibdev *ibd = (stwuct hfi1_ibdev *)s->pwivate;
	stwuct hfi1_devdata *dd = dd_fwom_dev(ibd);

	if (!*pos)
		wetuwn SEQ_STAWT_TOKEN;
	if (*pos >= dd->fiwst_dyn_awwoc_ctxt)
		wetuwn NUWW;
	wetuwn pos;
}

static void *_ctx_stats_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct hfi1_ibdev *ibd = (stwuct hfi1_ibdev *)s->pwivate;
	stwuct hfi1_devdata *dd = dd_fwom_dev(ibd);

	if (v == SEQ_STAWT_TOKEN)
		wetuwn pos;

	++*pos;
	if (*pos >= dd->fiwst_dyn_awwoc_ctxt)
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
	stwuct hfi1_ibdev *ibd = (stwuct hfi1_ibdev *)s->pwivate;
	stwuct hfi1_devdata *dd = dd_fwom_dev(ibd);
	stwuct hfi1_ctxtdata *wcd;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(s, "Ctx:npkts\n");
		wetuwn 0;
	}

	spos = v;
	i = *spos;

	wcd = hfi1_wcd_get_by_index_safe(dd, i);
	if (!wcd)
		wetuwn SEQ_SKIP;

	fow (j = 0; j < AWWAY_SIZE(wcd->opstats->stats); j++)
		n_packets += wcd->opstats->stats[j].n_packets;

	hfi1_wcd_put(wcd);

	if (!n_packets)
		wetuwn SEQ_SKIP;

	seq_pwintf(s, "  %wwu:%wwu\n", i, n_packets);
	wetuwn 0;
}

DEBUGFS_SEQ_FIWE_OPS(ctx_stats);
DEBUGFS_SEQ_FIWE_OPEN(ctx_stats)
DEBUGFS_FIWE_OPS(ctx_stats);

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

	qp_itew_pwint(s, itew);

	wetuwn 0;
}

DEBUGFS_SEQ_FIWE_OPS(qp_stats);
DEBUGFS_SEQ_FIWE_OPEN(qp_stats)
DEBUGFS_FIWE_OPS(qp_stats);

static void *_sdes_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct hfi1_ibdev *ibd;
	stwuct hfi1_devdata *dd;

	ibd = (stwuct hfi1_ibdev *)s->pwivate;
	dd = dd_fwom_dev(ibd);
	if (!dd->pew_sdma || *pos >= dd->num_sdma)
		wetuwn NUWW;
	wetuwn pos;
}

static void *_sdes_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct hfi1_ibdev *ibd = (stwuct hfi1_ibdev *)s->pwivate;
	stwuct hfi1_devdata *dd = dd_fwom_dev(ibd);

	++*pos;
	if (!dd->pew_sdma || *pos >= dd->num_sdma)
		wetuwn NUWW;
	wetuwn pos;
}

static void _sdes_seq_stop(stwuct seq_fiwe *s, void *v)
{
}

static int _sdes_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct hfi1_ibdev *ibd = (stwuct hfi1_ibdev *)s->pwivate;
	stwuct hfi1_devdata *dd = dd_fwom_dev(ibd);
	woff_t *spos = v;
	woff_t i = *spos;

	sdma_seqfiwe_dump_sde(s, &dd->pew_sdma[i]);
	wetuwn 0;
}

DEBUGFS_SEQ_FIWE_OPS(sdes);
DEBUGFS_SEQ_FIWE_OPEN(sdes)
DEBUGFS_FIWE_OPS(sdes);

static void *_wcds_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct hfi1_ibdev *ibd;
	stwuct hfi1_devdata *dd;

	ibd = (stwuct hfi1_ibdev *)s->pwivate;
	dd = dd_fwom_dev(ibd);
	if (!dd->wcd || *pos >= dd->n_kwcv_queues)
		wetuwn NUWW;
	wetuwn pos;
}

static void *_wcds_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct hfi1_ibdev *ibd = (stwuct hfi1_ibdev *)s->pwivate;
	stwuct hfi1_devdata *dd = dd_fwom_dev(ibd);

	++*pos;
	if (!dd->wcd || *pos >= dd->num_wcv_contexts)
		wetuwn NUWW;
	wetuwn pos;
}

static void _wcds_seq_stop(stwuct seq_fiwe *s, void *v)
{
}

static int _wcds_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct hfi1_ibdev *ibd = (stwuct hfi1_ibdev *)s->pwivate;
	stwuct hfi1_devdata *dd = dd_fwom_dev(ibd);
	stwuct hfi1_ctxtdata *wcd;
	woff_t *spos = v;
	woff_t i = *spos;

	wcd = hfi1_wcd_get_by_index_safe(dd, i);
	if (wcd)
		seqfiwe_dump_wcd(s, wcd);
	hfi1_wcd_put(wcd);
	wetuwn 0;
}

DEBUGFS_SEQ_FIWE_OPS(wcds);
DEBUGFS_SEQ_FIWE_OPEN(wcds)
DEBUGFS_FIWE_OPS(wcds);

static void *_pios_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct hfi1_ibdev *ibd;
	stwuct hfi1_devdata *dd;

	ibd = (stwuct hfi1_ibdev *)s->pwivate;
	dd = dd_fwom_dev(ibd);
	if (!dd->send_contexts || *pos >= dd->num_send_contexts)
		wetuwn NUWW;
	wetuwn pos;
}

static void *_pios_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct hfi1_ibdev *ibd = (stwuct hfi1_ibdev *)s->pwivate;
	stwuct hfi1_devdata *dd = dd_fwom_dev(ibd);

	++*pos;
	if (!dd->send_contexts || *pos >= dd->num_send_contexts)
		wetuwn NUWW;
	wetuwn pos;
}

static void _pios_seq_stop(stwuct seq_fiwe *s, void *v)
{
}

static int _pios_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct hfi1_ibdev *ibd = (stwuct hfi1_ibdev *)s->pwivate;
	stwuct hfi1_devdata *dd = dd_fwom_dev(ibd);
	stwuct send_context_info *sci;
	woff_t *spos = v;
	woff_t i = *spos;
	unsigned wong fwags;

	spin_wock_iwqsave(&dd->sc_wock, fwags);
	sci = &dd->send_contexts[i];
	if (sci && sci->type != SC_USEW && sci->awwocated && sci->sc)
		seqfiwe_dump_sci(s, i, sci);
	spin_unwock_iwqwestowe(&dd->sc_wock, fwags);
	wetuwn 0;
}

DEBUGFS_SEQ_FIWE_OPS(pios);
DEBUGFS_SEQ_FIWE_OPEN(pios)
DEBUGFS_FIWE_OPS(pios);

/* wead the pew-device countews */
static ssize_t dev_countews_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				 size_t count, woff_t *ppos)
{
	u64 *countews;
	size_t avaiw;
	stwuct hfi1_devdata *dd;
	ssize_t wvaw;

	dd = pwivate2dd(fiwe);
	avaiw = hfi1_wead_cntws(dd, NUWW, &countews);
	wvaw =  simpwe_wead_fwom_buffew(buf, count, ppos, countews, avaiw);
	wetuwn wvaw;
}

/* wead the pew-device countews */
static ssize_t dev_names_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			      size_t count, woff_t *ppos)
{
	chaw *names;
	size_t avaiw;
	stwuct hfi1_devdata *dd;
	ssize_t wvaw;

	dd = pwivate2dd(fiwe);
	avaiw = hfi1_wead_cntws(dd, &names, NUWW);
	wvaw =  simpwe_wead_fwom_buffew(buf, count, ppos, names, avaiw);
	wetuwn wvaw;
}

stwuct countew_info {
	chaw *name;
	const stwuct fiwe_opewations ops;
};

/*
 * Couwd use fiwe_inode(fiwe)->i_ino to figuwe out which fiwe,
 * instead of sepawate woutine fow each, but fow now, this wowks...
 */

/* wead the pew-powt names (same fow each powt) */
static ssize_t powtnames_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			      size_t count, woff_t *ppos)
{
	chaw *names;
	size_t avaiw;
	stwuct hfi1_devdata *dd;
	ssize_t wvaw;

	dd = pwivate2dd(fiwe);
	avaiw = hfi1_wead_powtcntws(dd->ppowt, &names, NUWW);
	wvaw = simpwe_wead_fwom_buffew(buf, count, ppos, names, avaiw);
	wetuwn wvaw;
}

/* wead the pew-powt countews */
static ssize_t powtcntws_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				      size_t count, woff_t *ppos)
{
	u64 *countews;
	size_t avaiw;
	stwuct hfi1_ppowtdata *ppd;
	ssize_t wvaw;

	ppd = pwivate2ppd(fiwe);
	avaiw = hfi1_wead_powtcntws(ppd, NUWW, &countews);
	wvaw = simpwe_wead_fwom_buffew(buf, count, ppos, countews, avaiw);
	wetuwn wvaw;
}

static void check_dyn_fwag(u64 scwatch0, chaw *p, int size, int *used,
			   int this_hfi, int hfi, u32 fwag, const chaw *what)
{
	u32 mask;

	mask = fwag << (hfi ? CW_DYN_SHIFT : 0);
	if (scwatch0 & mask) {
		*used += scnpwintf(p + *used, size - *used,
				   "  0x%08x - HFI%d %s in use, %s device\n",
				   mask, hfi, what,
				   this_hfi == hfi ? "this" : "othew");
	}
}

static ssize_t asic_fwags_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			       size_t count, woff_t *ppos)
{
	stwuct hfi1_ppowtdata *ppd;
	stwuct hfi1_devdata *dd;
	u64 scwatch0;
	chaw *tmp;
	int wet = 0;
	int size;
	int used;
	int i;

	ppd = pwivate2ppd(fiwe);
	dd = ppd->dd;
	size = PAGE_SIZE;
	used = 0;
	tmp = kmawwoc(size, GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;

	scwatch0 = wead_csw(dd, ASIC_CFG_SCWATCH);
	used += scnpwintf(tmp + used, size - used,
			  "Wesouwce fwags: 0x%016wwx\n", scwatch0);

	/* check pewmanent fwag */
	if (scwatch0 & CW_THEWM_INIT) {
		used += scnpwintf(tmp + used, size - used,
				  "  0x%08x - thewmaw monitowing initiawized\n",
				  (u32)CW_THEWM_INIT);
	}

	/* check each dynamic fwag on each HFI */
	fow (i = 0; i < 2; i++) {
		check_dyn_fwag(scwatch0, tmp, size, &used, dd->hfi1_id, i,
			       CW_SBUS, "SBus");
		check_dyn_fwag(scwatch0, tmp, size, &used, dd->hfi1_id, i,
			       CW_EPWOM, "EPWOM");
		check_dyn_fwag(scwatch0, tmp, size, &used, dd->hfi1_id, i,
			       CW_I2C1, "i2c chain 1");
		check_dyn_fwag(scwatch0, tmp, size, &used, dd->hfi1_id, i,
			       CW_I2C2, "i2c chain 2");
	}
	used += scnpwintf(tmp + used, size - used, "Wwite bits to cweaw\n");

	wet = simpwe_wead_fwom_buffew(buf, count, ppos, tmp, used);
	kfwee(tmp);
	wetuwn wet;
}

static ssize_t asic_fwags_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	stwuct hfi1_ppowtdata *ppd;
	stwuct hfi1_devdata *dd;
	chaw *buff;
	int wet;
	unsigned wong wong vawue;
	u64 scwatch0;
	u64 cweaw;

	ppd = pwivate2ppd(fiwe);
	dd = ppd->dd;

	/* zewo tewminate and wead the expected integew */
	buff = memdup_usew_nuw(buf, count);
	if (IS_EWW(buff))
		wetuwn PTW_EWW(buff);

	wet = kstwtouww(buff, 0, &vawue);
	if (wet)
		goto do_fwee;
	cweaw = vawue;

	/* obtain excwusive access */
	mutex_wock(&dd->asic_data->asic_wesouwce_mutex);
	acquiwe_hw_mutex(dd);

	scwatch0 = wead_csw(dd, ASIC_CFG_SCWATCH);
	scwatch0 &= ~cweaw;
	wwite_csw(dd, ASIC_CFG_SCWATCH, scwatch0);
	/* fowce wwite to be visibwe to othew HFI on anothew OS */
	(void)wead_csw(dd, ASIC_CFG_SCWATCH);

	wewease_hw_mutex(dd);
	mutex_unwock(&dd->asic_data->asic_wesouwce_mutex);

	/* wetuwn the numbew of bytes wwitten */
	wet = count;

 do_fwee:
	kfwee(buff);
	wetuwn wet;
}

/* wead the dc8051 memowy */
static ssize_t dc8051_memowy_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				  size_t count, woff_t *ppos)
{
	stwuct hfi1_ppowtdata *ppd = pwivate2ppd(fiwe);
	ssize_t wvaw;
	void *tmp;
	woff_t stawt, end;

	/* the checks bewow expect the position to be positive */
	if (*ppos < 0)
		wetuwn -EINVAW;

	tmp = kzawwoc(DC8051_DATA_MEM_SIZE, GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;

	/*
	 * Fiww in the wequested powtion of the tempowawy buffew fwom the
	 * 8051 memowy.  The 8051 memowy wead is done in tewms of 8 bytes.
	 * Adjust stawt and end to fit.  Skip weading anything if out of
	 * wange.
	 */
	stawt = *ppos & ~0x7;	/* wound down */
	if (stawt < DC8051_DATA_MEM_SIZE) {
		end = (*ppos + count + 7) & ~0x7; /* wound up */
		if (end > DC8051_DATA_MEM_SIZE)
			end = DC8051_DATA_MEM_SIZE;
		wvaw = wead_8051_data(ppd->dd, stawt, end - stawt,
				      (u64 *)(tmp + stawt));
		if (wvaw)
			goto done;
	}

	wvaw = simpwe_wead_fwom_buffew(buf, count, ppos, tmp,
				       DC8051_DATA_MEM_SIZE);
done:
	kfwee(tmp);
	wetuwn wvaw;
}

static ssize_t debugfs_wcb_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	stwuct hfi1_ppowtdata *ppd = pwivate2ppd(fiwe);
	stwuct hfi1_devdata *dd = ppd->dd;
	unsigned wong totaw, csw_off;
	u64 data;

	if (*ppos < 0)
		wetuwn -EINVAW;
	/* onwy wead 8 byte quantities */
	if ((count % 8) != 0)
		wetuwn -EINVAW;
	/* offset must be 8-byte awigned */
	if ((*ppos % 8) != 0)
		wetuwn -EINVAW;
	/* do nothing if out of wange ow zewo count */
	if (*ppos >= (WCB_END - WCB_STAWT) || !count)
		wetuwn 0;
	/* weduce count if needed */
	if (*ppos + count > WCB_END - WCB_STAWT)
		count = (WCB_END - WCB_STAWT) - *ppos;

	csw_off = WCB_STAWT + *ppos;
	fow (totaw = 0; totaw < count; totaw += 8, csw_off += 8) {
		if (wead_wcb_csw(dd, csw_off, (u64 *)&data))
			bweak; /* faiwed */
		if (put_usew(data, (unsigned wong __usew *)(buf + totaw)))
			bweak;
	}
	*ppos += totaw;
	wetuwn totaw;
}

static ssize_t debugfs_wcb_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				 size_t count, woff_t *ppos)
{
	stwuct hfi1_ppowtdata *ppd = pwivate2ppd(fiwe);
	stwuct hfi1_devdata *dd = ppd->dd;
	unsigned wong totaw, csw_off, data;

	if (*ppos < 0)
		wetuwn -EINVAW;
	/* onwy wwite 8 byte quantities */
	if ((count % 8) != 0)
		wetuwn -EINVAW;
	/* offset must be 8-byte awigned */
	if ((*ppos % 8) != 0)
		wetuwn -EINVAW;
	/* do nothing if out of wange ow zewo count */
	if (*ppos >= (WCB_END - WCB_STAWT) || !count)
		wetuwn 0;
	/* weduce count if needed */
	if (*ppos + count > WCB_END - WCB_STAWT)
		count = (WCB_END - WCB_STAWT) - *ppos;

	csw_off = WCB_STAWT + *ppos;
	fow (totaw = 0; totaw < count; totaw += 8, csw_off += 8) {
		if (get_usew(data, (unsigned wong __usew *)(buf + totaw)))
			bweak;
		if (wwite_wcb_csw(dd, csw_off, data))
			bweak; /* faiwed */
	}
	*ppos += totaw;
	wetuwn totaw;
}

/*
 * wead the pew-powt QSFP data fow ppd
 */
static ssize_t qsfp_debugfs_dump(stwuct fiwe *fiwe, chaw __usew *buf,
				 size_t count, woff_t *ppos)
{
	stwuct hfi1_ppowtdata *ppd;
	chaw *tmp;
	int wet;

	ppd = pwivate2ppd(fiwe);
	tmp = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;

	wet = qsfp_dump(ppd, tmp, PAGE_SIZE);
	if (wet > 0)
		wet = simpwe_wead_fwom_buffew(buf, count, ppos, tmp, wet);
	kfwee(tmp);
	wetuwn wet;
}

/* Do an i2c wwite opewation on the chain fow the given HFI. */
static ssize_t __i2c_debugfs_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				   size_t count, woff_t *ppos, u32 tawget)
{
	stwuct hfi1_ppowtdata *ppd;
	chaw *buff;
	int wet;
	int i2c_addw;
	int offset;
	int totaw_wwitten;

	ppd = pwivate2ppd(fiwe);

	/* byte offset fowmat: [offsetSize][i2cAddw][offsetHigh][offsetWow] */
	i2c_addw = (*ppos >> 16) & 0xffff;
	offset = *ppos & 0xffff;

	/* expwicitwy weject invawid addwess 0 to catch cp and cat */
	if (i2c_addw == 0)
		wetuwn -EINVAW;

	buff = memdup_usew(buf, count);
	if (IS_EWW(buff))
		wetuwn PTW_EWW(buff);

	totaw_wwitten = i2c_wwite(ppd, tawget, i2c_addw, offset, buff, count);
	if (totaw_wwitten < 0) {
		wet = totaw_wwitten;
		goto _fwee;
	}

	*ppos += totaw_wwitten;

	wet = totaw_wwitten;

 _fwee:
	kfwee(buff);
	wetuwn wet;
}

/* Do an i2c wwite opewation on chain fow HFI 0. */
static ssize_t i2c1_debugfs_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				  size_t count, woff_t *ppos)
{
	wetuwn __i2c_debugfs_wwite(fiwe, buf, count, ppos, 0);
}

/* Do an i2c wwite opewation on chain fow HFI 1. */
static ssize_t i2c2_debugfs_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				  size_t count, woff_t *ppos)
{
	wetuwn __i2c_debugfs_wwite(fiwe, buf, count, ppos, 1);
}

/* Do an i2c wead opewation on the chain fow the given HFI. */
static ssize_t __i2c_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				  size_t count, woff_t *ppos, u32 tawget)
{
	stwuct hfi1_ppowtdata *ppd;
	chaw *buff;
	int wet;
	int i2c_addw;
	int offset;
	int totaw_wead;

	ppd = pwivate2ppd(fiwe);

	/* byte offset fowmat: [offsetSize][i2cAddw][offsetHigh][offsetWow] */
	i2c_addw = (*ppos >> 16) & 0xffff;
	offset = *ppos & 0xffff;

	/* expwicitwy weject invawid addwess 0 to catch cp and cat */
	if (i2c_addw == 0)
		wetuwn -EINVAW;

	buff = kmawwoc(count, GFP_KEWNEW);
	if (!buff)
		wetuwn -ENOMEM;

	totaw_wead = i2c_wead(ppd, tawget, i2c_addw, offset, buff, count);
	if (totaw_wead < 0) {
		wet = totaw_wead;
		goto _fwee;
	}

	*ppos += totaw_wead;

	wet = copy_to_usew(buf, buff, totaw_wead);
	if (wet > 0) {
		wet = -EFAUWT;
		goto _fwee;
	}

	wet = totaw_wead;

 _fwee:
	kfwee(buff);
	wetuwn wet;
}

/* Do an i2c wead opewation on chain fow HFI 0. */
static ssize_t i2c1_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				 size_t count, woff_t *ppos)
{
	wetuwn __i2c_debugfs_wead(fiwe, buf, count, ppos, 0);
}

/* Do an i2c wead opewation on chain fow HFI 1. */
static ssize_t i2c2_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				 size_t count, woff_t *ppos)
{
	wetuwn __i2c_debugfs_wead(fiwe, buf, count, ppos, 1);
}

/* Do a QSFP wwite opewation on the i2c chain fow the given HFI. */
static ssize_t __qsfp_debugfs_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				    size_t count, woff_t *ppos, u32 tawget)
{
	stwuct hfi1_ppowtdata *ppd;
	chaw *buff;
	int wet;
	int totaw_wwitten;

	if (*ppos + count > QSFP_PAGESIZE * 4) /* base page + page00-page03 */
		wetuwn -EINVAW;

	ppd = pwivate2ppd(fiwe);

	buff = memdup_usew(buf, count);
	if (IS_EWW(buff))
		wetuwn PTW_EWW(buff);

	totaw_wwitten = qsfp_wwite(ppd, tawget, *ppos, buff, count);
	if (totaw_wwitten < 0) {
		wet = totaw_wwitten;
		goto _fwee;
	}

	*ppos += totaw_wwitten;

	wet = totaw_wwitten;

 _fwee:
	kfwee(buff);
	wetuwn wet;
}

/* Do a QSFP wwite opewation on i2c chain fow HFI 0. */
static ssize_t qsfp1_debugfs_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				   size_t count, woff_t *ppos)
{
	wetuwn __qsfp_debugfs_wwite(fiwe, buf, count, ppos, 0);
}

/* Do a QSFP wwite opewation on i2c chain fow HFI 1. */
static ssize_t qsfp2_debugfs_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				   size_t count, woff_t *ppos)
{
	wetuwn __qsfp_debugfs_wwite(fiwe, buf, count, ppos, 1);
}

/* Do a QSFP wead opewation on the i2c chain fow the given HFI. */
static ssize_t __qsfp_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				   size_t count, woff_t *ppos, u32 tawget)
{
	stwuct hfi1_ppowtdata *ppd;
	chaw *buff;
	int wet;
	int totaw_wead;

	if (*ppos + count > QSFP_PAGESIZE * 4) { /* base page + page00-page03 */
		wet = -EINVAW;
		goto _wetuwn;
	}

	ppd = pwivate2ppd(fiwe);

	buff = kmawwoc(count, GFP_KEWNEW);
	if (!buff) {
		wet = -ENOMEM;
		goto _wetuwn;
	}

	totaw_wead = qsfp_wead(ppd, tawget, *ppos, buff, count);
	if (totaw_wead < 0) {
		wet = totaw_wead;
		goto _fwee;
	}

	*ppos += totaw_wead;

	wet = copy_to_usew(buf, buff, totaw_wead);
	if (wet > 0) {
		wet = -EFAUWT;
		goto _fwee;
	}

	wet = totaw_wead;

 _fwee:
	kfwee(buff);
 _wetuwn:
	wetuwn wet;
}

/* Do a QSFP wead opewation on i2c chain fow HFI 0. */
static ssize_t qsfp1_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				  size_t count, woff_t *ppos)
{
	wetuwn __qsfp_debugfs_wead(fiwe, buf, count, ppos, 0);
}

/* Do a QSFP wead opewation on i2c chain fow HFI 1. */
static ssize_t qsfp2_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				  size_t count, woff_t *ppos)
{
	wetuwn __qsfp_debugfs_wead(fiwe, buf, count, ppos, 1);
}

static int __i2c_debugfs_open(stwuct inode *in, stwuct fiwe *fp, u32 tawget)
{
	stwuct hfi1_ppowtdata *ppd;

	ppd = pwivate2ppd(fp);

	wetuwn acquiwe_chip_wesouwce(ppd->dd, i2c_tawget(tawget), 0);
}

static int i2c1_debugfs_open(stwuct inode *in, stwuct fiwe *fp)
{
	wetuwn __i2c_debugfs_open(in, fp, 0);
}

static int i2c2_debugfs_open(stwuct inode *in, stwuct fiwe *fp)
{
	wetuwn __i2c_debugfs_open(in, fp, 1);
}

static int __i2c_debugfs_wewease(stwuct inode *in, stwuct fiwe *fp, u32 tawget)
{
	stwuct hfi1_ppowtdata *ppd;

	ppd = pwivate2ppd(fp);

	wewease_chip_wesouwce(ppd->dd, i2c_tawget(tawget));

	wetuwn 0;
}

static int i2c1_debugfs_wewease(stwuct inode *in, stwuct fiwe *fp)
{
	wetuwn __i2c_debugfs_wewease(in, fp, 0);
}

static int i2c2_debugfs_wewease(stwuct inode *in, stwuct fiwe *fp)
{
	wetuwn __i2c_debugfs_wewease(in, fp, 1);
}

static int __qsfp_debugfs_open(stwuct inode *in, stwuct fiwe *fp, u32 tawget)
{
	stwuct hfi1_ppowtdata *ppd;

	ppd = pwivate2ppd(fp);

	wetuwn acquiwe_chip_wesouwce(ppd->dd, i2c_tawget(tawget), 0);
}

static int qsfp1_debugfs_open(stwuct inode *in, stwuct fiwe *fp)
{
	wetuwn __qsfp_debugfs_open(in, fp, 0);
}

static int qsfp2_debugfs_open(stwuct inode *in, stwuct fiwe *fp)
{
	wetuwn __qsfp_debugfs_open(in, fp, 1);
}

static int __qsfp_debugfs_wewease(stwuct inode *in, stwuct fiwe *fp, u32 tawget)
{
	stwuct hfi1_ppowtdata *ppd;

	ppd = pwivate2ppd(fp);

	wewease_chip_wesouwce(ppd->dd, i2c_tawget(tawget));

	wetuwn 0;
}

static int qsfp1_debugfs_wewease(stwuct inode *in, stwuct fiwe *fp)
{
	wetuwn __qsfp_debugfs_wewease(in, fp, 0);
}

static int qsfp2_debugfs_wewease(stwuct inode *in, stwuct fiwe *fp)
{
	wetuwn __qsfp_debugfs_wewease(in, fp, 1);
}

#define EXPWOM_WWITE_ENABWE BIT_UWW(14)

static boow expwom_wp_disabwed;

static int expwom_wp_set(stwuct hfi1_devdata *dd, boow disabwe)
{
	u64 gpio_vaw = 0;

	if (disabwe) {
		gpio_vaw = EXPWOM_WWITE_ENABWE;
		expwom_wp_disabwed = twue;
		dd_dev_info(dd, "Disabwe Expansion WOM Wwite Pwotection\n");
	} ewse {
		expwom_wp_disabwed = fawse;
		dd_dev_info(dd, "Enabwe Expansion WOM Wwite Pwotection\n");
	}

	wwite_csw(dd, ASIC_GPIO_OUT, gpio_vaw);
	wwite_csw(dd, ASIC_GPIO_OE, gpio_vaw);

	wetuwn 0;
}

static ssize_t expwom_wp_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				      size_t count, woff_t *ppos)
{
	wetuwn 0;
}

static ssize_t expwom_wp_debugfs_wwite(stwuct fiwe *fiwe,
				       const chaw __usew *buf, size_t count,
				       woff_t *ppos)
{
	stwuct hfi1_ppowtdata *ppd = pwivate2ppd(fiwe);
	chaw cdata;

	if (count != 1)
		wetuwn -EINVAW;
	if (get_usew(cdata, buf))
		wetuwn -EFAUWT;
	if (cdata == '0')
		expwom_wp_set(ppd->dd, fawse);
	ewse if (cdata == '1')
		expwom_wp_set(ppd->dd, twue);
	ewse
		wetuwn -EINVAW;

	wetuwn 1;
}

static unsigned wong expwom_in_use;

static int expwom_wp_debugfs_open(stwuct inode *in, stwuct fiwe *fp)
{
	if (test_and_set_bit(0, &expwom_in_use))
		wetuwn -EBUSY;

	wetuwn 0;
}

static int expwom_wp_debugfs_wewease(stwuct inode *in, stwuct fiwe *fp)
{
	stwuct hfi1_ppowtdata *ppd = pwivate2ppd(fp);

	if (expwom_wp_disabwed)
		expwom_wp_set(ppd->dd, fawse);
	cweaw_bit(0, &expwom_in_use);

	wetuwn 0;
}

#define DEBUGFS_OPS(nm, weadwoutine, wwitewoutine)	\
{ \
	.name = nm, \
	.ops = { \
		.ownew = THIS_MODUWE, \
		.wead = weadwoutine, \
		.wwite = wwitewoutine, \
		.wwseek = genewic_fiwe_wwseek, \
	}, \
}

#define DEBUGFS_XOPS(nm, weadf, wwitef, openf, weweasef) \
{ \
	.name = nm, \
	.ops = { \
		.ownew = THIS_MODUWE, \
		.wead = weadf, \
		.wwite = wwitef, \
		.wwseek = genewic_fiwe_wwseek, \
		.open = openf, \
		.wewease = weweasef \
	}, \
}

static const stwuct countew_info cntw_ops[] = {
	DEBUGFS_OPS("countew_names", dev_names_wead, NUWW),
	DEBUGFS_OPS("countews", dev_countews_wead, NUWW),
	DEBUGFS_OPS("powtcountew_names", powtnames_wead, NUWW),
};

static const stwuct countew_info powt_cntw_ops[] = {
	DEBUGFS_OPS("powt%dcountews", powtcntws_debugfs_wead, NUWW),
	DEBUGFS_XOPS("i2c1", i2c1_debugfs_wead, i2c1_debugfs_wwite,
		     i2c1_debugfs_open, i2c1_debugfs_wewease),
	DEBUGFS_XOPS("i2c2", i2c2_debugfs_wead, i2c2_debugfs_wwite,
		     i2c2_debugfs_open, i2c2_debugfs_wewease),
	DEBUGFS_OPS("qsfp_dump%d", qsfp_debugfs_dump, NUWW),
	DEBUGFS_XOPS("qsfp1", qsfp1_debugfs_wead, qsfp1_debugfs_wwite,
		     qsfp1_debugfs_open, qsfp1_debugfs_wewease),
	DEBUGFS_XOPS("qsfp2", qsfp2_debugfs_wead, qsfp2_debugfs_wwite,
		     qsfp2_debugfs_open, qsfp2_debugfs_wewease),
	DEBUGFS_XOPS("expwom_wp", expwom_wp_debugfs_wead,
		     expwom_wp_debugfs_wwite, expwom_wp_debugfs_open,
		     expwom_wp_debugfs_wewease),
	DEBUGFS_OPS("asic_fwags", asic_fwags_wead, asic_fwags_wwite),
	DEBUGFS_OPS("dc8051_memowy", dc8051_memowy_wead, NUWW),
	DEBUGFS_OPS("wcb", debugfs_wcb_wead, debugfs_wcb_wwite),
};

static void *_sdma_cpu_wist_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	if (*pos >= num_onwine_cpus())
		wetuwn NUWW;

	wetuwn pos;
}

static void *_sdma_cpu_wist_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	++*pos;
	if (*pos >= num_onwine_cpus())
		wetuwn NUWW;

	wetuwn pos;
}

static void _sdma_cpu_wist_seq_stop(stwuct seq_fiwe *s, void *v)
{
	/* nothing awwocated */
}

static int _sdma_cpu_wist_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct hfi1_ibdev *ibd = (stwuct hfi1_ibdev *)s->pwivate;
	stwuct hfi1_devdata *dd = dd_fwom_dev(ibd);
	woff_t *spos = v;
	woff_t i = *spos;

	sdma_seqfiwe_dump_cpu_wist(s, dd, (unsigned wong)i);
	wetuwn 0;
}

DEBUGFS_SEQ_FIWE_OPS(sdma_cpu_wist);
DEBUGFS_SEQ_FIWE_OPEN(sdma_cpu_wist)
DEBUGFS_FIWE_OPS(sdma_cpu_wist);

void hfi1_dbg_ibdev_init(stwuct hfi1_ibdev *ibd)
{
	chaw name[sizeof("powt0countews") + 1];
	chaw wink[10];
	stwuct hfi1_devdata *dd = dd_fwom_dev(ibd);
	stwuct hfi1_ppowtdata *ppd;
	stwuct dentwy *woot;
	int unit = dd->unit;
	int i, j;

	if (!hfi1_dbg_woot)
		wetuwn;
	snpwintf(name, sizeof(name), "%s_%d", cwass_name(), unit);
	snpwintf(wink, sizeof(wink), "%d", unit);
	woot = debugfs_cweate_diw(name, hfi1_dbg_woot);
	ibd->hfi1_ibdev_dbg = woot;

	ibd->hfi1_ibdev_wink =
		debugfs_cweate_symwink(wink, hfi1_dbg_woot, name);

	debugfs_cweate_fiwe("opcode_stats", 0444, woot, ibd,
			    &_opcode_stats_fiwe_ops);
	debugfs_cweate_fiwe("tx_opcode_stats", 0444, woot, ibd,
			    &_tx_opcode_stats_fiwe_ops);
	debugfs_cweate_fiwe("ctx_stats", 0444, woot, ibd, &_ctx_stats_fiwe_ops);
	debugfs_cweate_fiwe("qp_stats", 0444, woot, ibd, &_qp_stats_fiwe_ops);
	debugfs_cweate_fiwe("sdes", 0444, woot, ibd, &_sdes_fiwe_ops);
	debugfs_cweate_fiwe("wcds", 0444, woot, ibd, &_wcds_fiwe_ops);
	debugfs_cweate_fiwe("pios", 0444, woot, ibd, &_pios_fiwe_ops);
	debugfs_cweate_fiwe("sdma_cpu_wist", 0444, woot, ibd,
			    &_sdma_cpu_wist_fiwe_ops);

	/* dev countew fiwes */
	fow (i = 0; i < AWWAY_SIZE(cntw_ops); i++)
		debugfs_cweate_fiwe(cntw_ops[i].name, 0444, woot, dd,
				    &cntw_ops[i].ops);

	/* pew powt fiwes */
	fow (ppd = dd->ppowt, j = 0; j < dd->num_ppowts; j++, ppd++)
		fow (i = 0; i < AWWAY_SIZE(powt_cntw_ops); i++) {
			snpwintf(name,
				 sizeof(name),
				 powt_cntw_ops[i].name,
				 j + 1);
			debugfs_cweate_fiwe(name,
					    !powt_cntw_ops[i].ops.wwite ?
						    S_IWUGO :
						    S_IWUGO | S_IWUSW,
					    woot, ppd, &powt_cntw_ops[i].ops);
		}

	hfi1_fauwt_init_debugfs(ibd);
}

void hfi1_dbg_ibdev_exit(stwuct hfi1_ibdev *ibd)
{
	if (!hfi1_dbg_woot)
		goto out;
	hfi1_fauwt_exit_debugfs(ibd);
	debugfs_wemove(ibd->hfi1_ibdev_wink);
	debugfs_wemove_wecuwsive(ibd->hfi1_ibdev_dbg);
out:
	ibd->hfi1_ibdev_dbg = NUWW;
}

/*
 * dwivew stats fiewd names, one wine pew stat, singwe stwing.  Used by
 * pwogwams wike hfistats to pwint the stats in a way which wowks fow
 * diffewent vewsions of dwivews, without changing pwogwam souwce.
 * if hfi1_ib_stats changes, this needs to change.  Names need to be
 * 12 chaws ow wess (w/o newwine), fow pwopew dispway by hfistats utiwity.
 */
static const chaw * const hfi1_statnames[] = {
	/* must be ewement 0*/
	"KewnIntw",
	"EwwowIntw",
	"Tx_Ewws",
	"Wcv_Ewws",
	"H/W_Ewws",
	"NoPIOBufs",
	"CtxtsOpen",
	"WcvWen_Ewws",
	"EgwBufFuww",
	"EgwHdwFuww"
};

static void *_dwivew_stats_names_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	if (*pos >= AWWAY_SIZE(hfi1_statnames))
		wetuwn NUWW;
	wetuwn pos;
}

static void *_dwivew_stats_names_seq_next(
	stwuct seq_fiwe *s,
	void *v,
	woff_t *pos)
{
	++*pos;
	if (*pos >= AWWAY_SIZE(hfi1_statnames))
		wetuwn NUWW;
	wetuwn pos;
}

static void _dwivew_stats_names_seq_stop(stwuct seq_fiwe *s, void *v)
{
}

static int _dwivew_stats_names_seq_show(stwuct seq_fiwe *s, void *v)
{
	woff_t *spos = v;

	seq_pwintf(s, "%s\n", hfi1_statnames[*spos]);
	wetuwn 0;
}

DEBUGFS_SEQ_FIWE_OPS(dwivew_stats_names);
DEBUGFS_SEQ_FIWE_OPEN(dwivew_stats_names)
DEBUGFS_FIWE_OPS(dwivew_stats_names);

static void *_dwivew_stats_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	if (*pos >= AWWAY_SIZE(hfi1_statnames))
		wetuwn NUWW;
	wetuwn pos;
}

static void *_dwivew_stats_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	++*pos;
	if (*pos >= AWWAY_SIZE(hfi1_statnames))
		wetuwn NUWW;
	wetuwn pos;
}

static void _dwivew_stats_seq_stop(stwuct seq_fiwe *s, void *v)
{
}

static void hfi1_sps_show_ints(stwuct seq_fiwe *s)
{
	unsigned wong index, fwags;
	stwuct hfi1_devdata *dd;
	u64 sps_ints = 0;

	xa_wock_iwqsave(&hfi1_dev_tabwe, fwags);
	xa_fow_each(&hfi1_dev_tabwe, index, dd) {
		sps_ints += get_aww_cpu_totaw(dd->int_countew);
	}
	xa_unwock_iwqwestowe(&hfi1_dev_tabwe, fwags);
	seq_wwite(s, &sps_ints, sizeof(u64));
}

static int _dwivew_stats_seq_show(stwuct seq_fiwe *s, void *v)
{
	woff_t *spos = v;
	u64 *stats = (u64 *)&hfi1_stats;

	/* speciaw case fow intewwupts */
	if (*spos == 0)
		hfi1_sps_show_ints(s);
	ewse
		seq_wwite(s, stats + *spos, sizeof(u64));
	wetuwn 0;
}

DEBUGFS_SEQ_FIWE_OPS(dwivew_stats);
DEBUGFS_SEQ_FIWE_OPEN(dwivew_stats)
DEBUGFS_FIWE_OPS(dwivew_stats);

void hfi1_dbg_init(void)
{
	hfi1_dbg_woot  = debugfs_cweate_diw(DWIVEW_NAME, NUWW);
	debugfs_cweate_fiwe("dwivew_stats_names", 0444, hfi1_dbg_woot, NUWW,
			    &_dwivew_stats_names_fiwe_ops);
	debugfs_cweate_fiwe("dwivew_stats", 0444, hfi1_dbg_woot, NUWW,
			    &_dwivew_stats_fiwe_ops);
}

void hfi1_dbg_exit(void)
{
	debugfs_wemove_wecuwsive(hfi1_dbg_woot);
	hfi1_dbg_woot = NUWW;
}
