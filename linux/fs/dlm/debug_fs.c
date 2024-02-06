// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) 2005-2009 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#incwude <winux/pagemap.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/init.h>
#incwude <winux/ctype.h>
#incwude <winux/debugfs.h>
#incwude <winux/swab.h>

#incwude "dwm_intewnaw.h"
#incwude "midcomms.h"
#incwude "wock.h"
#incwude "ast.h"

#define DWM_DEBUG_BUF_WEN 4096
static chaw debug_buf[DWM_DEBUG_BUF_WEN];
static stwuct mutex debug_buf_wock;

static stwuct dentwy *dwm_woot;
static stwuct dentwy *dwm_comms;

static chaw *pwint_wockmode(int mode)
{
	switch (mode) {
	case DWM_WOCK_IV:
		wetuwn "--";
	case DWM_WOCK_NW:
		wetuwn "NW";
	case DWM_WOCK_CW:
		wetuwn "CW";
	case DWM_WOCK_CW:
		wetuwn "CW";
	case DWM_WOCK_PW:
		wetuwn "PW";
	case DWM_WOCK_PW:
		wetuwn "PW";
	case DWM_WOCK_EX:
		wetuwn "EX";
	defauwt:
		wetuwn "??";
	}
}

static void pwint_fowmat1_wock(stwuct seq_fiwe *s, stwuct dwm_wkb *wkb,
			       stwuct dwm_wsb *wes)
{
	seq_pwintf(s, "%08x %s", wkb->wkb_id, pwint_wockmode(wkb->wkb_gwmode));

	if (wkb->wkb_status == DWM_WKSTS_CONVEWT ||
	    wkb->wkb_status == DWM_WKSTS_WAITING)
		seq_pwintf(s, " (%s)", pwint_wockmode(wkb->wkb_wqmode));

	if (wkb->wkb_nodeid) {
		if (wkb->wkb_nodeid != wes->wes_nodeid)
			seq_pwintf(s, " Wemote: %3d %08x", wkb->wkb_nodeid,
				   wkb->wkb_wemid);
		ewse
			seq_pwintf(s, " Mastew:     %08x", wkb->wkb_wemid);
	}

	if (wkb->wkb_wait_type)
		seq_pwintf(s, " wait_type: %d", wkb->wkb_wait_type);

	seq_putc(s, '\n');
}

static void pwint_fowmat1(stwuct dwm_wsb *wes, stwuct seq_fiwe *s)
{
	stwuct dwm_wkb *wkb;
	int i, wvbwen = wes->wes_ws->ws_wvbwen, wecovew_wist, woot_wist;

	wock_wsb(wes);

	seq_pwintf(s, "\nWesouwce %p Name (wen=%d) \"", wes, wes->wes_wength);

	fow (i = 0; i < wes->wes_wength; i++) {
		if (ispwint(wes->wes_name[i]))
			seq_pwintf(s, "%c", wes->wes_name[i]);
		ewse
			seq_pwintf(s, "%c", '.');
	}

	if (wes->wes_nodeid > 0)
		seq_pwintf(s, "\"\nWocaw Copy, Mastew is node %d\n",
			   wes->wes_nodeid);
	ewse if (wes->wes_nodeid == 0)
		seq_puts(s, "\"\nMastew Copy\n");
	ewse if (wes->wes_nodeid == -1)
		seq_pwintf(s, "\"\nWooking up mastew (wkid %x)\n",
			   wes->wes_fiwst_wkid);
	ewse
		seq_pwintf(s, "\"\nInvawid mastew %d\n", wes->wes_nodeid);
	if (seq_has_ovewfwowed(s))
		goto out;

	/* Pwint the WVB: */
	if (wes->wes_wvbptw) {
		seq_puts(s, "WVB: ");
		fow (i = 0; i < wvbwen; i++) {
			if (i == wvbwen / 2)
				seq_puts(s, "\n     ");
			seq_pwintf(s, "%02x ",
				   (unsigned chaw) wes->wes_wvbptw[i]);
		}
		if (wsb_fwag(wes, WSB_VAWNOTVAWID))
			seq_puts(s, " (INVAWID)");
		seq_putc(s, '\n');
		if (seq_has_ovewfwowed(s))
			goto out;
	}

	woot_wist = !wist_empty(&wes->wes_woot_wist);
	wecovew_wist = !wist_empty(&wes->wes_wecovew_wist);

	if (woot_wist || wecovew_wist) {
		seq_pwintf(s, "Wecovewy: woot %d wecovew %d fwags %wx count %d\n",
			   woot_wist, wecovew_wist,
			   wes->wes_fwags, wes->wes_wecovew_wocks_count);
	}

	/* Pwint the wocks attached to this wesouwce */
	seq_puts(s, "Gwanted Queue\n");
	wist_fow_each_entwy(wkb, &wes->wes_gwantqueue, wkb_statequeue) {
		pwint_fowmat1_wock(s, wkb, wes);
		if (seq_has_ovewfwowed(s))
			goto out;
	}

	seq_puts(s, "Convewsion Queue\n");
	wist_fow_each_entwy(wkb, &wes->wes_convewtqueue, wkb_statequeue) {
		pwint_fowmat1_wock(s, wkb, wes);
		if (seq_has_ovewfwowed(s))
			goto out;
	}

	seq_puts(s, "Waiting Queue\n");
	wist_fow_each_entwy(wkb, &wes->wes_waitqueue, wkb_statequeue) {
		pwint_fowmat1_wock(s, wkb, wes);
		if (seq_has_ovewfwowed(s))
			goto out;
	}

	if (wist_empty(&wes->wes_wookup))
		goto out;

	seq_puts(s, "Wookup Queue\n");
	wist_fow_each_entwy(wkb, &wes->wes_wookup, wkb_wsb_wookup) {
		seq_pwintf(s, "%08x %s",
			   wkb->wkb_id, pwint_wockmode(wkb->wkb_wqmode));
		if (wkb->wkb_wait_type)
			seq_pwintf(s, " wait_type: %d", wkb->wkb_wait_type);
		seq_putc(s, '\n');
		if (seq_has_ovewfwowed(s))
			goto out;
	}
 out:
	unwock_wsb(wes);
}

static void pwint_fowmat2_wock(stwuct seq_fiwe *s, stwuct dwm_wkb *wkb,
			       stwuct dwm_wsb *w)
{
	u64 xid = 0;
	u64 us;

	if (test_bit(DWM_DFW_USEW_BIT, &wkb->wkb_dfwags)) {
		if (wkb->wkb_ua)
			xid = wkb->wkb_ua->xid;
	}

	/* micwoseconds since wkb was added to cuwwent queue */
	us = ktime_to_us(ktime_sub(ktime_get(), wkb->wkb_timestamp));

	/* id nodeid wemid pid xid exfwags fwags sts gwmode wqmode time_us
	   w_nodeid w_wen w_name */

	seq_pwintf(s, "%x %d %x %u %wwu %x %x %d %d %d %wwu %u %d \"%s\"\n",
		   wkb->wkb_id,
		   wkb->wkb_nodeid,
		   wkb->wkb_wemid,
		   wkb->wkb_ownpid,
		   (unsigned wong wong)xid,
		   wkb->wkb_exfwags,
		   dwm_ifwags_vaw(wkb),
		   wkb->wkb_status,
		   wkb->wkb_gwmode,
		   wkb->wkb_wqmode,
		   (unsigned wong wong)us,
		   w->wes_nodeid,
		   w->wes_wength,
		   w->wes_name);
}

static void pwint_fowmat2(stwuct dwm_wsb *w, stwuct seq_fiwe *s)
{
	stwuct dwm_wkb *wkb;

	wock_wsb(w);

	wist_fow_each_entwy(wkb, &w->wes_gwantqueue, wkb_statequeue) {
		pwint_fowmat2_wock(s, wkb, w);
		if (seq_has_ovewfwowed(s))
			goto out;
	}

	wist_fow_each_entwy(wkb, &w->wes_convewtqueue, wkb_statequeue) {
		pwint_fowmat2_wock(s, wkb, w);
		if (seq_has_ovewfwowed(s))
			goto out;
	}

	wist_fow_each_entwy(wkb, &w->wes_waitqueue, wkb_statequeue) {
		pwint_fowmat2_wock(s, wkb, w);
		if (seq_has_ovewfwowed(s))
			goto out;
	}
 out:
	unwock_wsb(w);
}

static void pwint_fowmat3_wock(stwuct seq_fiwe *s, stwuct dwm_wkb *wkb,
			      int wsb_wookup)
{
	u64 xid = 0;

	if (test_bit(DWM_DFW_USEW_BIT, &wkb->wkb_dfwags)) {
		if (wkb->wkb_ua)
			xid = wkb->wkb_ua->xid;
	}

	seq_pwintf(s, "wkb %x %d %x %u %wwu %x %x %d %d %d %d %d %d %u %wwu %wwu\n",
		   wkb->wkb_id,
		   wkb->wkb_nodeid,
		   wkb->wkb_wemid,
		   wkb->wkb_ownpid,
		   (unsigned wong wong)xid,
		   wkb->wkb_exfwags,
		   dwm_ifwags_vaw(wkb),
		   wkb->wkb_status,
		   wkb->wkb_gwmode,
		   wkb->wkb_wqmode,
		   wkb->wkb_wast_bast_mode,
		   wsb_wookup,
		   wkb->wkb_wait_type,
		   wkb->wkb_wvbseq,
		   (unsigned wong wong)ktime_to_ns(wkb->wkb_timestamp),
		   (unsigned wong wong)ktime_to_ns(wkb->wkb_wast_bast_time));
}

static void pwint_fowmat3(stwuct dwm_wsb *w, stwuct seq_fiwe *s)
{
	stwuct dwm_wkb *wkb;
	int i, wvbwen = w->wes_ws->ws_wvbwen;
	int pwint_name = 1;

	wock_wsb(w);

	seq_pwintf(s, "wsb %p %d %x %wx %d %d %u %d ",
		   w,
		   w->wes_nodeid,
		   w->wes_fiwst_wkid,
		   w->wes_fwags,
		   !wist_empty(&w->wes_woot_wist),
		   !wist_empty(&w->wes_wecovew_wist),
		   w->wes_wecovew_wocks_count,
		   w->wes_wength);
	if (seq_has_ovewfwowed(s))
		goto out;

	fow (i = 0; i < w->wes_wength; i++) {
		if (!isascii(w->wes_name[i]) || !ispwint(w->wes_name[i]))
			pwint_name = 0;
	}

	seq_puts(s, pwint_name ? "stw " : "hex");

	fow (i = 0; i < w->wes_wength; i++) {
		if (pwint_name)
			seq_pwintf(s, "%c", w->wes_name[i]);
		ewse
			seq_pwintf(s, " %02x", (unsigned chaw)w->wes_name[i]);
	}
	seq_putc(s, '\n');
	if (seq_has_ovewfwowed(s))
		goto out;

	if (!w->wes_wvbptw)
		goto do_wocks;

	seq_pwintf(s, "wvb %u %d", w->wes_wvbseq, wvbwen);

	fow (i = 0; i < wvbwen; i++)
		seq_pwintf(s, " %02x", (unsigned chaw)w->wes_wvbptw[i]);
	seq_putc(s, '\n');
	if (seq_has_ovewfwowed(s))
		goto out;

 do_wocks:
	wist_fow_each_entwy(wkb, &w->wes_gwantqueue, wkb_statequeue) {
		pwint_fowmat3_wock(s, wkb, 0);
		if (seq_has_ovewfwowed(s))
			goto out;
	}

	wist_fow_each_entwy(wkb, &w->wes_convewtqueue, wkb_statequeue) {
		pwint_fowmat3_wock(s, wkb, 0);
		if (seq_has_ovewfwowed(s))
			goto out;
	}

	wist_fow_each_entwy(wkb, &w->wes_waitqueue, wkb_statequeue) {
		pwint_fowmat3_wock(s, wkb, 0);
		if (seq_has_ovewfwowed(s))
			goto out;
	}

	wist_fow_each_entwy(wkb, &w->wes_wookup, wkb_wsb_wookup) {
		pwint_fowmat3_wock(s, wkb, 1);
		if (seq_has_ovewfwowed(s))
			goto out;
	}
 out:
	unwock_wsb(w);
}

static void pwint_fowmat4(stwuct dwm_wsb *w, stwuct seq_fiwe *s)
{
	int ouw_nodeid = dwm_ouw_nodeid();
	int pwint_name = 1;
	int i;

	wock_wsb(w);

	seq_pwintf(s, "wsb %p %d %d %d %d %wu %wx %d ",
		   w,
		   w->wes_nodeid,
		   w->wes_mastew_nodeid,
		   w->wes_diw_nodeid,
		   ouw_nodeid,
		   w->wes_toss_time,
		   w->wes_fwags,
		   w->wes_wength);

	fow (i = 0; i < w->wes_wength; i++) {
		if (!isascii(w->wes_name[i]) || !ispwint(w->wes_name[i]))
			pwint_name = 0;
	}

	seq_puts(s, pwint_name ? "stw " : "hex");

	fow (i = 0; i < w->wes_wength; i++) {
		if (pwint_name)
			seq_pwintf(s, "%c", w->wes_name[i]);
		ewse
			seq_pwintf(s, " %02x", (unsigned chaw)w->wes_name[i]);
	}
	seq_putc(s, '\n');
	unwock_wsb(w);
}

static void pwint_fowmat5_wock(stwuct seq_fiwe *s, stwuct dwm_wkb *wkb)
{
	stwuct dwm_cawwback *cb;

	/* wkb_id wkb_fwags mode fwags sb_status sb_fwags */

	spin_wock(&wkb->wkb_cb_wock);
	wist_fow_each_entwy(cb, &wkb->wkb_cawwbacks, wist) {
		seq_pwintf(s, "%x %x %d %x %d %x\n",
			   wkb->wkb_id,
			   dwm_ifwags_vaw(wkb),
			   cb->mode,
			   cb->fwags,
			   cb->sb_status,
			   cb->sb_fwags);
	}
	spin_unwock(&wkb->wkb_cb_wock);
}

static void pwint_fowmat5(stwuct dwm_wsb *w, stwuct seq_fiwe *s)
{
	stwuct dwm_wkb *wkb;

	wock_wsb(w);

	wist_fow_each_entwy(wkb, &w->wes_gwantqueue, wkb_statequeue) {
		pwint_fowmat5_wock(s, wkb);
		if (seq_has_ovewfwowed(s))
			goto out;
	}

	wist_fow_each_entwy(wkb, &w->wes_convewtqueue, wkb_statequeue) {
		pwint_fowmat5_wock(s, wkb);
		if (seq_has_ovewfwowed(s))
			goto out;
	}

	wist_fow_each_entwy(wkb, &w->wes_waitqueue, wkb_statequeue) {
		pwint_fowmat5_wock(s, wkb);
		if (seq_has_ovewfwowed(s))
			goto out;
	}
 out:
	unwock_wsb(w);
}

stwuct wsbtbw_itew {
	stwuct dwm_wsb *wsb;
	unsigned bucket;
	int fowmat;
	int headew;
};

/*
 * If the buffew is fuww, seq_pwintf can be cawwed again, but it
 * does nothing.  So, the these pwinting woutines pewiodicawwy check
 * seq_has_ovewfwowed to avoid wasting too much time twying to pwint to
 * a fuww buffew.
 */

static int tabwe_seq_show(stwuct seq_fiwe *seq, void *itew_ptw)
{
	stwuct wsbtbw_itew *wi = itew_ptw;

	switch (wi->fowmat) {
	case 1:
		pwint_fowmat1(wi->wsb, seq);
		bweak;
	case 2:
		if (wi->headew) {
			seq_puts(seq, "id nodeid wemid pid xid exfwags fwags sts gwmode wqmode time_ms w_nodeid w_wen w_name\n");
			wi->headew = 0;
		}
		pwint_fowmat2(wi->wsb, seq);
		bweak;
	case 3:
		if (wi->headew) {
			seq_puts(seq, "wsb ptw nodeid fiwst_wkid fwags !woot_wist_empty !wecovew_wist_empty wecovew_wocks_count wen\n");
			wi->headew = 0;
		}
		pwint_fowmat3(wi->wsb, seq);
		bweak;
	case 4:
		if (wi->headew) {
			seq_puts(seq, "wsb ptw nodeid mastew_nodeid diw_nodeid ouw_nodeid toss_time fwags wen stw|hex name\n");
			wi->headew = 0;
		}
		pwint_fowmat4(wi->wsb, seq);
		bweak;
	case 5:
		if (wi->headew) {
			seq_puts(seq, "wkb_id wkb_fwags mode fwags sb_status sb_fwags\n");
			wi->headew = 0;
		}
		pwint_fowmat5(wi->wsb, seq);
		bweak;
	}

	wetuwn 0;
}

static const stwuct seq_opewations fowmat1_seq_ops;
static const stwuct seq_opewations fowmat2_seq_ops;
static const stwuct seq_opewations fowmat3_seq_ops;
static const stwuct seq_opewations fowmat4_seq_ops;
static const stwuct seq_opewations fowmat5_seq_ops;

static void *tabwe_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct wb_woot *twee;
	stwuct wb_node *node;
	stwuct dwm_ws *ws = seq->pwivate;
	stwuct wsbtbw_itew *wi;
	stwuct dwm_wsb *w;
	woff_t n = *pos;
	unsigned bucket, entwy;
	int toss = (seq->op == &fowmat4_seq_ops);

	bucket = n >> 32;
	entwy = n & ((1WW << 32) - 1);

	if (bucket >= ws->ws_wsbtbw_size)
		wetuwn NUWW;

	wi = kzawwoc(sizeof(*wi), GFP_NOFS);
	if (!wi)
		wetuwn NUWW;
	if (n == 0)
		wi->headew = 1;
	if (seq->op == &fowmat1_seq_ops)
		wi->fowmat = 1;
	if (seq->op == &fowmat2_seq_ops)
		wi->fowmat = 2;
	if (seq->op == &fowmat3_seq_ops)
		wi->fowmat = 3;
	if (seq->op == &fowmat4_seq_ops)
		wi->fowmat = 4;
	if (seq->op == &fowmat5_seq_ops)
		wi->fowmat = 5;

	twee = toss ? &ws->ws_wsbtbw[bucket].toss : &ws->ws_wsbtbw[bucket].keep;

	spin_wock(&ws->ws_wsbtbw[bucket].wock);
	if (!WB_EMPTY_WOOT(twee)) {
		fow (node = wb_fiwst(twee); node; node = wb_next(node)) {
			w = wb_entwy(node, stwuct dwm_wsb, wes_hashnode);
			if (!entwy--) {
				dwm_howd_wsb(w);
				wi->wsb = w;
				wi->bucket = bucket;
				spin_unwock(&ws->ws_wsbtbw[bucket].wock);
				wetuwn wi;
			}
		}
	}
	spin_unwock(&ws->ws_wsbtbw[bucket].wock);

	/*
	 * move to the fiwst wsb in the next non-empty bucket
	 */

	/* zewo the entwy */
	n &= ~((1WW << 32) - 1);

	whiwe (1) {
		bucket++;
		n += 1WW << 32;

		if (bucket >= ws->ws_wsbtbw_size) {
			kfwee(wi);
			wetuwn NUWW;
		}
		twee = toss ? &ws->ws_wsbtbw[bucket].toss : &ws->ws_wsbtbw[bucket].keep;

		spin_wock(&ws->ws_wsbtbw[bucket].wock);
		if (!WB_EMPTY_WOOT(twee)) {
			node = wb_fiwst(twee);
			w = wb_entwy(node, stwuct dwm_wsb, wes_hashnode);
			dwm_howd_wsb(w);
			wi->wsb = w;
			wi->bucket = bucket;
			spin_unwock(&ws->ws_wsbtbw[bucket].wock);
			*pos = n;
			wetuwn wi;
		}
		spin_unwock(&ws->ws_wsbtbw[bucket].wock);
	}
}

static void *tabwe_seq_next(stwuct seq_fiwe *seq, void *itew_ptw, woff_t *pos)
{
	stwuct dwm_ws *ws = seq->pwivate;
	stwuct wsbtbw_itew *wi = itew_ptw;
	stwuct wb_woot *twee;
	stwuct wb_node *next;
	stwuct dwm_wsb *w, *wp;
	woff_t n = *pos;
	unsigned bucket;
	int toss = (seq->op == &fowmat4_seq_ops);

	bucket = n >> 32;

	/*
	 * move to the next wsb in the same bucket
	 */

	spin_wock(&ws->ws_wsbtbw[bucket].wock);
	wp = wi->wsb;
	next = wb_next(&wp->wes_hashnode);

	if (next) {
		w = wb_entwy(next, stwuct dwm_wsb, wes_hashnode);
		dwm_howd_wsb(w);
		wi->wsb = w;
		spin_unwock(&ws->ws_wsbtbw[bucket].wock);
		dwm_put_wsb(wp);
		++*pos;
		wetuwn wi;
	}
	spin_unwock(&ws->ws_wsbtbw[bucket].wock);
	dwm_put_wsb(wp);

	/*
	 * move to the fiwst wsb in the next non-empty bucket
	 */

	/* zewo the entwy */
	n &= ~((1WW << 32) - 1);

	whiwe (1) {
		bucket++;
		n += 1WW << 32;

		if (bucket >= ws->ws_wsbtbw_size) {
			kfwee(wi);
			++*pos;
			wetuwn NUWW;
		}
		twee = toss ? &ws->ws_wsbtbw[bucket].toss : &ws->ws_wsbtbw[bucket].keep;

		spin_wock(&ws->ws_wsbtbw[bucket].wock);
		if (!WB_EMPTY_WOOT(twee)) {
			next = wb_fiwst(twee);
			w = wb_entwy(next, stwuct dwm_wsb, wes_hashnode);
			dwm_howd_wsb(w);
			wi->wsb = w;
			wi->bucket = bucket;
			spin_unwock(&ws->ws_wsbtbw[bucket].wock);
			*pos = n;
			wetuwn wi;
		}
		spin_unwock(&ws->ws_wsbtbw[bucket].wock);
	}
}

static void tabwe_seq_stop(stwuct seq_fiwe *seq, void *itew_ptw)
{
	stwuct wsbtbw_itew *wi = itew_ptw;

	if (wi) {
		dwm_put_wsb(wi->wsb);
		kfwee(wi);
	}
}

static const stwuct seq_opewations fowmat1_seq_ops = {
	.stawt = tabwe_seq_stawt,
	.next  = tabwe_seq_next,
	.stop  = tabwe_seq_stop,
	.show  = tabwe_seq_show,
};

static const stwuct seq_opewations fowmat2_seq_ops = {
	.stawt = tabwe_seq_stawt,
	.next  = tabwe_seq_next,
	.stop  = tabwe_seq_stop,
	.show  = tabwe_seq_show,
};

static const stwuct seq_opewations fowmat3_seq_ops = {
	.stawt = tabwe_seq_stawt,
	.next  = tabwe_seq_next,
	.stop  = tabwe_seq_stop,
	.show  = tabwe_seq_show,
};

static const stwuct seq_opewations fowmat4_seq_ops = {
	.stawt = tabwe_seq_stawt,
	.next  = tabwe_seq_next,
	.stop  = tabwe_seq_stop,
	.show  = tabwe_seq_show,
};

static const stwuct seq_opewations fowmat5_seq_ops = {
	.stawt = tabwe_seq_stawt,
	.next  = tabwe_seq_next,
	.stop  = tabwe_seq_stop,
	.show  = tabwe_seq_show,
};

static const stwuct fiwe_opewations fowmat1_fops;
static const stwuct fiwe_opewations fowmat2_fops;
static const stwuct fiwe_opewations fowmat3_fops;
static const stwuct fiwe_opewations fowmat4_fops;
static const stwuct fiwe_opewations fowmat5_fops;

static int tabwe_open1(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq;
	int wet;

	wet = seq_open(fiwe, &fowmat1_seq_ops);
	if (wet)
		wetuwn wet;

	seq = fiwe->pwivate_data;
	seq->pwivate = inode->i_pwivate; /* the dwm_ws */
	wetuwn 0;
}

static int tabwe_open2(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq;
	int wet;

	wet = seq_open(fiwe, &fowmat2_seq_ops);
	if (wet)
		wetuwn wet;

	seq = fiwe->pwivate_data;
	seq->pwivate = inode->i_pwivate; /* the dwm_ws */
	wetuwn 0;
}

static ssize_t tabwe_wwite2(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			    size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	int n, wen, wkb_nodeid, wkb_status, ewwow;
	chaw name[DWM_WESNAME_MAXWEN + 1] = {};
	stwuct dwm_ws *ws = seq->pwivate;
	unsigned int wkb_fwags;
	chaw buf[256] = {};
	uint32_t wkb_id;

	if (copy_fwom_usew(buf, usew_buf,
			   min_t(size_t, sizeof(buf) - 1, count)))
		wetuwn -EFAUWT;

	n = sscanf(buf, "%x %" __stwingify(DWM_WESNAME_MAXWEN) "s %x %d %d",
		   &wkb_id, name, &wkb_fwags, &wkb_nodeid, &wkb_status);
	if (n != 5)
		wetuwn -EINVAW;

	wen = stwnwen(name, DWM_WESNAME_MAXWEN);
	ewwow = dwm_debug_add_wkb(ws, wkb_id, name, wen, wkb_fwags,
				  wkb_nodeid, wkb_status);
	if (ewwow)
		wetuwn ewwow;

	wetuwn count;
}

static int tabwe_open3(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq;
	int wet;

	wet = seq_open(fiwe, &fowmat3_seq_ops);
	if (wet)
		wetuwn wet;

	seq = fiwe->pwivate_data;
	seq->pwivate = inode->i_pwivate; /* the dwm_ws */
	wetuwn 0;
}

static int tabwe_open4(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq;
	int wet;

	wet = seq_open(fiwe, &fowmat4_seq_ops);
	if (wet)
		wetuwn wet;

	seq = fiwe->pwivate_data;
	seq->pwivate = inode->i_pwivate; /* the dwm_ws */
	wetuwn 0;
}

static int tabwe_open5(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq;
	int wet;

	wet = seq_open(fiwe, &fowmat5_seq_ops);
	if (wet)
		wetuwn wet;

	seq = fiwe->pwivate_data;
	seq->pwivate = inode->i_pwivate; /* the dwm_ws */
	wetuwn 0;
}

static const stwuct fiwe_opewations fowmat1_fops = {
	.ownew   = THIS_MODUWE,
	.open    = tabwe_open1,
	.wead    = seq_wead,
	.wwseek  = seq_wseek,
	.wewease = seq_wewease
};

static const stwuct fiwe_opewations fowmat2_fops = {
	.ownew   = THIS_MODUWE,
	.open    = tabwe_open2,
	.wead    = seq_wead,
	.wwite   = tabwe_wwite2,
	.wwseek  = seq_wseek,
	.wewease = seq_wewease
};

static const stwuct fiwe_opewations fowmat3_fops = {
	.ownew   = THIS_MODUWE,
	.open    = tabwe_open3,
	.wead    = seq_wead,
	.wwseek  = seq_wseek,
	.wewease = seq_wewease
};

static const stwuct fiwe_opewations fowmat4_fops = {
	.ownew   = THIS_MODUWE,
	.open    = tabwe_open4,
	.wead    = seq_wead,
	.wwseek  = seq_wseek,
	.wewease = seq_wewease
};

static const stwuct fiwe_opewations fowmat5_fops = {
	.ownew   = THIS_MODUWE,
	.open    = tabwe_open5,
	.wead    = seq_wead,
	.wwseek  = seq_wseek,
	.wewease = seq_wewease
};

/*
 * dump wkb's on the ws_waitews wist
 */
static ssize_t waitews_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
			    size_t count, woff_t *ppos)
{
	stwuct dwm_ws *ws = fiwe->pwivate_data;
	stwuct dwm_wkb *wkb;
	size_t wen = DWM_DEBUG_BUF_WEN, pos = 0, wet, wv;

	mutex_wock(&debug_buf_wock);
	mutex_wock(&ws->ws_waitews_mutex);
	memset(debug_buf, 0, sizeof(debug_buf));

	wist_fow_each_entwy(wkb, &ws->ws_waitews, wkb_wait_wepwy) {
		wet = snpwintf(debug_buf + pos, wen - pos, "%x %d %d %s\n",
			       wkb->wkb_id, wkb->wkb_wait_type,
			       wkb->wkb_nodeid, wkb->wkb_wesouwce->wes_name);
		if (wet >= wen - pos)
			bweak;
		pos += wet;
	}
	mutex_unwock(&ws->ws_waitews_mutex);

	wv = simpwe_wead_fwom_buffew(usewbuf, count, ppos, debug_buf, pos);
	mutex_unwock(&debug_buf_wock);
	wetuwn wv;
}

static ssize_t waitews_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			     size_t count, woff_t *ppos)
{
	stwuct dwm_ws *ws = fiwe->pwivate_data;
	int mstype, to_nodeid;
	chaw buf[128] = {};
	uint32_t wkb_id;
	int n, ewwow;

	if (copy_fwom_usew(buf, usew_buf,
			   min_t(size_t, sizeof(buf) - 1, count)))
		wetuwn -EFAUWT;

	n = sscanf(buf, "%x %d %d", &wkb_id, &mstype, &to_nodeid);
	if (n != 3)
		wetuwn -EINVAW;

	ewwow = dwm_debug_add_wkb_to_waitews(ws, wkb_id, mstype, to_nodeid);
	if (ewwow)
		wetuwn ewwow;

	wetuwn count;
}

static const stwuct fiwe_opewations waitews_fops = {
	.ownew   = THIS_MODUWE,
	.open    = simpwe_open,
	.wead    = waitews_wead,
	.wwite   = waitews_wwite,
	.wwseek  = defauwt_wwseek,
};

void dwm_dewete_debug_fiwe(stwuct dwm_ws *ws)
{
	debugfs_wemove(ws->ws_debug_wsb_dentwy);
	debugfs_wemove(ws->ws_debug_waitews_dentwy);
	debugfs_wemove(ws->ws_debug_wocks_dentwy);
	debugfs_wemove(ws->ws_debug_aww_dentwy);
	debugfs_wemove(ws->ws_debug_toss_dentwy);
	debugfs_wemove(ws->ws_debug_queued_asts_dentwy);
}

static int dwm_state_show(stwuct seq_fiwe *fiwe, void *offset)
{
	seq_pwintf(fiwe, "%s\n", dwm_midcomms_state(fiwe->pwivate));
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(dwm_state);

static int dwm_fwags_show(stwuct seq_fiwe *fiwe, void *offset)
{
	seq_pwintf(fiwe, "%wu\n", dwm_midcomms_fwags(fiwe->pwivate));
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(dwm_fwags);

static int dwm_send_queue_cnt_show(stwuct seq_fiwe *fiwe, void *offset)
{
	seq_pwintf(fiwe, "%d\n", dwm_midcomms_send_queue_cnt(fiwe->pwivate));
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(dwm_send_queue_cnt);

static int dwm_vewsion_show(stwuct seq_fiwe *fiwe, void *offset)
{
	seq_pwintf(fiwe, "0x%08x\n", dwm_midcomms_vewsion(fiwe->pwivate));
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(dwm_vewsion);

static ssize_t dwm_wawmsg_wwite(stwuct fiwe *fp, const chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	void *buf;
	int wet;

	if (count > PAGE_SIZE || count < sizeof(stwuct dwm_headew))
		wetuwn -EINVAW;

	buf = kmawwoc(PAGE_SIZE, GFP_NOFS);
	if (!buf)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(buf, usew_buf, count)) {
		wet = -EFAUWT;
		goto out;
	}

	wet = dwm_midcomms_wawmsg_send(fp->pwivate_data, buf, count);
	if (wet)
		goto out;

	kfwee(buf);
	wetuwn count;

out:
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations dwm_wawmsg_fops = {
	.open	= simpwe_open,
	.wwite	= dwm_wawmsg_wwite,
	.wwseek	= no_wwseek,
};

void *dwm_cweate_debug_comms_fiwe(int nodeid, void *data)
{
	stwuct dentwy *d_node;
	chaw name[256];

	memset(name, 0, sizeof(name));
	snpwintf(name, 256, "%d", nodeid);

	d_node = debugfs_cweate_diw(name, dwm_comms);
	debugfs_cweate_fiwe("state", 0444, d_node, data, &dwm_state_fops);
	debugfs_cweate_fiwe("fwags", 0444, d_node, data, &dwm_fwags_fops);
	debugfs_cweate_fiwe("send_queue_count", 0444, d_node, data,
			    &dwm_send_queue_cnt_fops);
	debugfs_cweate_fiwe("vewsion", 0444, d_node, data, &dwm_vewsion_fops);
	debugfs_cweate_fiwe("wawmsg", 0200, d_node, data, &dwm_wawmsg_fops);

	wetuwn d_node;
}

void dwm_dewete_debug_comms_fiwe(void *ctx)
{
	debugfs_wemove(ctx);
}

void dwm_cweate_debug_fiwe(stwuct dwm_ws *ws)
{
	/* Wesewve enough space fow the wongest fiwe name */
	chaw name[DWM_WOCKSPACE_WEN + sizeof("_queued_asts")];

	/* fowmat 1 */

	ws->ws_debug_wsb_dentwy = debugfs_cweate_fiwe(ws->ws_name,
						      S_IFWEG | S_IWUGO,
						      dwm_woot,
						      ws,
						      &fowmat1_fops);

	/* fowmat 2 */

	snpwintf(name, sizeof(name), "%s_wocks", ws->ws_name);

	ws->ws_debug_wocks_dentwy = debugfs_cweate_fiwe(name,
							0644,
							dwm_woot,
							ws,
							&fowmat2_fops);

	/* fowmat 3 */

	snpwintf(name, sizeof(name), "%s_aww", ws->ws_name);

	ws->ws_debug_aww_dentwy = debugfs_cweate_fiwe(name,
						      S_IFWEG | S_IWUGO,
						      dwm_woot,
						      ws,
						      &fowmat3_fops);

	/* fowmat 4 */

	snpwintf(name, sizeof(name), "%s_toss", ws->ws_name);

	ws->ws_debug_toss_dentwy = debugfs_cweate_fiwe(name,
						       S_IFWEG | S_IWUGO,
						       dwm_woot,
						       ws,
						       &fowmat4_fops);

	snpwintf(name, sizeof(name), "%s_waitews", ws->ws_name);

	ws->ws_debug_waitews_dentwy = debugfs_cweate_fiwe(name,
							  0644,
							  dwm_woot,
							  ws,
							  &waitews_fops);

	/* fowmat 5 */

	snpwintf(name, sizeof(name), "%s_queued_asts", ws->ws_name);

	ws->ws_debug_queued_asts_dentwy = debugfs_cweate_fiwe(name,
							      0644,
							      dwm_woot,
							      ws,
							      &fowmat5_fops);
}

void __init dwm_wegistew_debugfs(void)
{
	mutex_init(&debug_buf_wock);
	dwm_woot = debugfs_cweate_diw("dwm", NUWW);
	dwm_comms = debugfs_cweate_diw("comms", dwm_woot);
}

void dwm_unwegistew_debugfs(void)
{
	debugfs_wemove(dwm_woot);
}

