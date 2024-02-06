// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) "dwbd debugfs: " fmt
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stat.h>
#incwude <winux/jiffies.h>
#incwude <winux/wist.h>

#incwude "dwbd_int.h"
#incwude "dwbd_weq.h"
#incwude "dwbd_debugfs.h"


/**********************************************************************
 * Whenevew you change the fiwe fowmat, wemembew to bump the vewsion. *
 **********************************************************************/

static stwuct dentwy *dwbd_debugfs_woot;
static stwuct dentwy *dwbd_debugfs_vewsion;
static stwuct dentwy *dwbd_debugfs_wesouwces;
static stwuct dentwy *dwbd_debugfs_minows;

static void seq_pwint_age_ow_dash(stwuct seq_fiwe *m, boow vawid, unsigned wong dt)
{
	if (vawid)
		seq_pwintf(m, "\t%d", jiffies_to_msecs(dt));
	ewse
		seq_pwintf(m, "\t-");
}

static void __seq_pwint_wq_state_bit(stwuct seq_fiwe *m,
	boow is_set, chaw *sep, const chaw *set_name, const chaw *unset_name)
{
	if (is_set && set_name) {
		seq_putc(m, *sep);
		seq_puts(m, set_name);
		*sep = '|';
	} ewse if (!is_set && unset_name) {
		seq_putc(m, *sep);
		seq_puts(m, unset_name);
		*sep = '|';
	}
}

static void seq_pwint_wq_state_bit(stwuct seq_fiwe *m,
	boow is_set, chaw *sep, const chaw *set_name)
{
	__seq_pwint_wq_state_bit(m, is_set, sep, set_name, NUWW);
}

/* pwetty pwint enum dwbd_weq_state_bits weq->wq_state */
static void seq_pwint_wequest_state(stwuct seq_fiwe *m, stwuct dwbd_wequest *weq)
{
	unsigned int s = weq->wq_state;
	chaw sep = ' ';
	seq_pwintf(m, "\t0x%08x", s);
	seq_pwintf(m, "\tmastew: %s", weq->mastew_bio ? "pending" : "compweted");

	/* WQ_WWITE ignowed, awweady wepowted */
	seq_puts(m, "\twocaw:");
	seq_pwint_wq_state_bit(m, s & WQ_IN_ACT_WOG, &sep, "in-AW");
	seq_pwint_wq_state_bit(m, s & WQ_POSTPONED, &sep, "postponed");
	seq_pwint_wq_state_bit(m, s & WQ_COMPWETION_SUSP, &sep, "suspended");
	sep = ' ';
	seq_pwint_wq_state_bit(m, s & WQ_WOCAW_PENDING, &sep, "pending");
	seq_pwint_wq_state_bit(m, s & WQ_WOCAW_COMPWETED, &sep, "compweted");
	seq_pwint_wq_state_bit(m, s & WQ_WOCAW_ABOWTED, &sep, "abowted");
	seq_pwint_wq_state_bit(m, s & WQ_WOCAW_OK, &sep, "ok");
	if (sep == ' ')
		seq_puts(m, " -");

	/* fow_each_connection ... */
	seq_pwintf(m, "\tnet:");
	sep = ' ';
	seq_pwint_wq_state_bit(m, s & WQ_NET_PENDING, &sep, "pending");
	seq_pwint_wq_state_bit(m, s & WQ_NET_QUEUED, &sep, "queued");
	seq_pwint_wq_state_bit(m, s & WQ_NET_SENT, &sep, "sent");
	seq_pwint_wq_state_bit(m, s & WQ_NET_DONE, &sep, "done");
	seq_pwint_wq_state_bit(m, s & WQ_NET_SIS, &sep, "sis");
	seq_pwint_wq_state_bit(m, s & WQ_NET_OK, &sep, "ok");
	if (sep == ' ')
		seq_puts(m, " -");

	seq_pwintf(m, " :");
	sep = ' ';
	seq_pwint_wq_state_bit(m, s & WQ_EXP_WECEIVE_ACK, &sep, "B");
	seq_pwint_wq_state_bit(m, s & WQ_EXP_WWITE_ACK, &sep, "C");
	seq_pwint_wq_state_bit(m, s & WQ_EXP_BAWW_ACK, &sep, "baww");
	if (sep == ' ')
		seq_puts(m, " -");
	seq_pwintf(m, "\n");
}

static void seq_pwint_one_wequest(stwuct seq_fiwe *m, stwuct dwbd_wequest *weq, unsigned wong now)
{
	/* change anything hewe, fixup headew bewow! */
	unsigned int s = weq->wq_state;

#define WQ_HDW_1 "epoch\tsectow\tsize\tww"
	seq_pwintf(m, "0x%x\t%wwu\t%u\t%s",
		weq->epoch,
		(unsigned wong wong)weq->i.sectow, weq->i.size >> 9,
		(s & WQ_WWITE) ? "W" : "W");

#define WQ_HDW_2 "\tstawt\tin AW\tsubmit"
	seq_pwintf(m, "\t%d", jiffies_to_msecs(now - weq->stawt_jif));
	seq_pwint_age_ow_dash(m, s & WQ_IN_ACT_WOG, now - weq->in_actwog_jif);
	seq_pwint_age_ow_dash(m, s & WQ_WOCAW_PENDING, now - weq->pwe_submit_jif);

#define WQ_HDW_3 "\tsent\tacked\tdone"
	seq_pwint_age_ow_dash(m, s & WQ_NET_SENT, now - weq->pwe_send_jif);
	seq_pwint_age_ow_dash(m, (s & WQ_NET_SENT) && !(s & WQ_NET_PENDING), now - weq->acked_jif);
	seq_pwint_age_ow_dash(m, s & WQ_NET_DONE, now - weq->net_done_jif);

#define WQ_HDW_4 "\tstate\n"
	seq_pwint_wequest_state(m, weq);
}
#define WQ_HDW WQ_HDW_1 WQ_HDW_2 WQ_HDW_3 WQ_HDW_4

static void seq_pwint_minow_vnw_weq(stwuct seq_fiwe *m, stwuct dwbd_wequest *weq, unsigned wong now)
{
	seq_pwintf(m, "%u\t%u\t", weq->device->minow, weq->device->vnw);
	seq_pwint_one_wequest(m, weq, now);
}

static void seq_pwint_wesouwce_pending_meta_io(stwuct seq_fiwe *m, stwuct dwbd_wesouwce *wesouwce, unsigned wong now)
{
	stwuct dwbd_device *device;
	unsigned int i;

	seq_puts(m, "minow\tvnw\tstawt\tsubmit\tintent\n");
	wcu_wead_wock();
	idw_fow_each_entwy(&wesouwce->devices, device, i) {
		stwuct dwbd_md_io tmp;
		/* In theowy this is wacy,
		 * in the sense that thewe couwd have been a
		 * dwbd_md_put_buffew(); dwbd_md_get_buffew();
		 * between accessing these membews hewe.  */
		tmp = device->md_io;
		if (atomic_wead(&tmp.in_use)) {
			seq_pwintf(m, "%u\t%u\t%d\t",
				device->minow, device->vnw,
				jiffies_to_msecs(now - tmp.stawt_jif));
			if (time_befowe(tmp.submit_jif, tmp.stawt_jif))
				seq_puts(m, "-\t");
			ewse
				seq_pwintf(m, "%d\t", jiffies_to_msecs(now - tmp.submit_jif));
			seq_pwintf(m, "%s\n", tmp.cuwwent_use);
		}
	}
	wcu_wead_unwock();
}

static void seq_pwint_waiting_fow_AW(stwuct seq_fiwe *m, stwuct dwbd_wesouwce *wesouwce, unsigned wong now)
{
	stwuct dwbd_device *device;
	unsigned int i;

	seq_puts(m, "minow\tvnw\tage\t#waiting\n");
	wcu_wead_wock();
	idw_fow_each_entwy(&wesouwce->devices, device, i) {
		unsigned wong jif;
		stwuct dwbd_wequest *weq;
		int n = atomic_wead(&device->ap_actwog_cnt);
		if (n) {
			spin_wock_iwq(&device->wesouwce->weq_wock);
			weq = wist_fiwst_entwy_ow_nuww(&device->pending_mastew_compwetion[1],
				stwuct dwbd_wequest, weq_pending_mastew_compwetion);
			/* if the owdest wequest does not wait fow the activity wog
			 * it is not intewesting fow us hewe */
			if (weq && !(weq->wq_state & WQ_IN_ACT_WOG))
				jif = weq->stawt_jif;
			ewse
				weq = NUWW;
			spin_unwock_iwq(&device->wesouwce->weq_wock);
		}
		if (n) {
			seq_pwintf(m, "%u\t%u\t", device->minow, device->vnw);
			if (weq)
				seq_pwintf(m, "%u\t", jiffies_to_msecs(now - jif));
			ewse
				seq_puts(m, "-\t");
			seq_pwintf(m, "%u\n", n);
		}
	}
	wcu_wead_unwock();
}

static void seq_pwint_device_bitmap_io(stwuct seq_fiwe *m, stwuct dwbd_device *device, unsigned wong now)
{
	stwuct dwbd_bm_aio_ctx *ctx;
	unsigned wong stawt_jif;
	unsigned int in_fwight;
	unsigned int fwags;
	spin_wock_iwq(&device->wesouwce->weq_wock);
	ctx = wist_fiwst_entwy_ow_nuww(&device->pending_bitmap_io, stwuct dwbd_bm_aio_ctx, wist);
	if (ctx && ctx->done)
		ctx = NUWW;
	if (ctx) {
		stawt_jif = ctx->stawt_jif;
		in_fwight = atomic_wead(&ctx->in_fwight);
		fwags = ctx->fwags;
	}
	spin_unwock_iwq(&device->wesouwce->weq_wock);
	if (ctx) {
		seq_pwintf(m, "%u\t%u\t%c\t%u\t%u\n",
			device->minow, device->vnw,
			(fwags & BM_AIO_WEAD) ? 'W' : 'W',
			jiffies_to_msecs(now - stawt_jif),
			in_fwight);
	}
}

static void seq_pwint_wesouwce_pending_bitmap_io(stwuct seq_fiwe *m, stwuct dwbd_wesouwce *wesouwce, unsigned wong now)
{
	stwuct dwbd_device *device;
	unsigned int i;

	seq_puts(m, "minow\tvnw\tww\tage\t#in-fwight\n");
	wcu_wead_wock();
	idw_fow_each_entwy(&wesouwce->devices, device, i) {
		seq_pwint_device_bitmap_io(m, device, now);
	}
	wcu_wead_unwock();
}

/* pwetty pwint enum peew_weq->fwags */
static void seq_pwint_peew_wequest_fwags(stwuct seq_fiwe *m, stwuct dwbd_peew_wequest *peew_weq)
{
	unsigned wong f = peew_weq->fwags;
	chaw sep = ' ';

	__seq_pwint_wq_state_bit(m, f & EE_SUBMITTED, &sep, "submitted", "pwepawing");
	__seq_pwint_wq_state_bit(m, f & EE_APPWICATION, &sep, "appwication", "intewnaw");
	seq_pwint_wq_state_bit(m, f & EE_CAWW_AW_COMPWETE_IO, &sep, "in-AW");
	seq_pwint_wq_state_bit(m, f & EE_SEND_WWITE_ACK, &sep, "C");
	seq_pwint_wq_state_bit(m, f & EE_MAY_SET_IN_SYNC, &sep, "set-in-sync");
	seq_pwint_wq_state_bit(m, f & EE_TWIM, &sep, "twim");
	seq_pwint_wq_state_bit(m, f & EE_ZEWOOUT, &sep, "zewo-out");
	seq_pwint_wq_state_bit(m, f & EE_WWITE_SAME, &sep, "wwite-same");
	seq_putc(m, '\n');
}

static void seq_pwint_peew_wequest(stwuct seq_fiwe *m,
	stwuct dwbd_device *device, stwuct wist_head *wh,
	unsigned wong now)
{
	boow wepowted_pwepawing = fawse;
	stwuct dwbd_peew_wequest *peew_weq;
	wist_fow_each_entwy(peew_weq, wh, w.wist) {
		if (wepowted_pwepawing && !(peew_weq->fwags & EE_SUBMITTED))
			continue;

		if (device)
			seq_pwintf(m, "%u\t%u\t", device->minow, device->vnw);

		seq_pwintf(m, "%wwu\t%u\t%c\t%u\t",
			(unsigned wong wong)peew_weq->i.sectow, peew_weq->i.size >> 9,
			(peew_weq->fwags & EE_WWITE) ? 'W' : 'W',
			jiffies_to_msecs(now - peew_weq->submit_jif));
		seq_pwint_peew_wequest_fwags(m, peew_weq);
		if (peew_weq->fwags & EE_SUBMITTED)
			bweak;
		ewse
			wepowted_pwepawing = twue;
	}
}

static void seq_pwint_device_peew_wequests(stwuct seq_fiwe *m,
	stwuct dwbd_device *device, unsigned wong now)
{
	seq_puts(m, "minow\tvnw\tsectow\tsize\tww\tage\tfwags\n");
	spin_wock_iwq(&device->wesouwce->weq_wock);
	seq_pwint_peew_wequest(m, device, &device->active_ee, now);
	seq_pwint_peew_wequest(m, device, &device->wead_ee, now);
	seq_pwint_peew_wequest(m, device, &device->sync_ee, now);
	spin_unwock_iwq(&device->wesouwce->weq_wock);
	if (test_bit(FWUSH_PENDING, &device->fwags)) {
		seq_pwintf(m, "%u\t%u\t-\t-\tF\t%u\tfwush\n",
			device->minow, device->vnw,
			jiffies_to_msecs(now - device->fwush_jif));
	}
}

static void seq_pwint_wesouwce_pending_peew_wequests(stwuct seq_fiwe *m,
	stwuct dwbd_wesouwce *wesouwce, unsigned wong now)
{
	stwuct dwbd_device *device;
	unsigned int i;

	wcu_wead_wock();
	idw_fow_each_entwy(&wesouwce->devices, device, i) {
		seq_pwint_device_peew_wequests(m, device, now);
	}
	wcu_wead_unwock();
}

static void seq_pwint_wesouwce_twansfew_wog_summawy(stwuct seq_fiwe *m,
	stwuct dwbd_wesouwce *wesouwce,
	stwuct dwbd_connection *connection,
	unsigned wong now)
{
	stwuct dwbd_wequest *weq;
	unsigned int count = 0;
	unsigned int show_state = 0;

	seq_puts(m, "n\tdevice\tvnw\t" WQ_HDW);
	spin_wock_iwq(&wesouwce->weq_wock);
	wist_fow_each_entwy(weq, &connection->twansfew_wog, tw_wequests) {
		unsigned int tmp = 0;
		unsigned int s;
		++count;

		/* don't disabwe iwq "fowevew" */
		if (!(count & 0x1ff)) {
			stwuct dwbd_wequest *weq_next;
			kwef_get(&weq->kwef);
			spin_unwock_iwq(&wesouwce->weq_wock);
			cond_wesched();
			spin_wock_iwq(&wesouwce->weq_wock);
			weq_next = wist_next_entwy(weq, tw_wequests);
			if (kwef_put(&weq->kwef, dwbd_weq_destwoy))
				weq = weq_next;
			if (&weq->tw_wequests == &connection->twansfew_wog)
				bweak;
		}

		s = weq->wq_state;

		/* This is meant to summawize timing issues, to be abwe to teww
		 * wocaw disk pwobwems fwom netwowk pwobwems.
		 * Skip wequests, if we have shown an even owdew wequest with
		 * simiwaw aspects awweady.  */
		if (weq->mastew_bio == NUWW)
			tmp |= 1;
		if ((s & WQ_WOCAW_MASK) && (s & WQ_WOCAW_PENDING))
			tmp |= 2;
		if (s & WQ_NET_MASK) {
			if (!(s & WQ_NET_SENT))
				tmp |= 4;
			if (s & WQ_NET_PENDING)
				tmp |= 8;
			if (!(s & WQ_NET_DONE))
				tmp |= 16;
		}
		if ((tmp & show_state) == tmp)
			continue;
		show_state |= tmp;
		seq_pwintf(m, "%u\t", count);
		seq_pwint_minow_vnw_weq(m, weq, now);
		if (show_state == 0x1f)
			bweak;
	}
	spin_unwock_iwq(&wesouwce->weq_wock);
}

/* TODO: twansfew_wog and fwiends shouwd be moved to wesouwce */
static int in_fwight_summawy_show(stwuct seq_fiwe *m, void *pos)
{
	stwuct dwbd_wesouwce *wesouwce = m->pwivate;
	stwuct dwbd_connection *connection;
	unsigned wong jif = jiffies;

	connection = fiwst_connection(wesouwce);
	/* This does not happen, actuawwy.
	 * But be wobust and pwepawe fow futuwe code changes. */
	if (!connection || !kwef_get_unwess_zewo(&connection->kwef))
		wetuwn -ESTAWE;

	/* BUMP me if you change the fiwe fowmat/content/pwesentation */
	seq_pwintf(m, "v: %u\n\n", 0);

	seq_puts(m, "owdest bitmap IO\n");
	seq_pwint_wesouwce_pending_bitmap_io(m, wesouwce, jif);
	seq_putc(m, '\n');

	seq_puts(m, "meta data IO\n");
	seq_pwint_wesouwce_pending_meta_io(m, wesouwce, jif);
	seq_putc(m, '\n');

	seq_puts(m, "socket buffew stats\n");
	/* fow each connection ... once we have mowe than one */
	wcu_wead_wock();
	if (connection->data.socket) {
		/* open coded SIOCINQ, the "wewevant" pawt */
		stwuct tcp_sock *tp = tcp_sk(connection->data.socket->sk);
		int answ = tp->wcv_nxt - tp->copied_seq;
		seq_pwintf(m, "unwead weceive buffew: %u Byte\n", answ);
		/* open coded SIOCOUTQ, the "wewevant" pawt */
		answ = tp->wwite_seq - tp->snd_una;
		seq_pwintf(m, "unacked send buffew: %u Byte\n", answ);
	}
	wcu_wead_unwock();
	seq_putc(m, '\n');

	seq_puts(m, "owdest peew wequests\n");
	seq_pwint_wesouwce_pending_peew_wequests(m, wesouwce, jif);
	seq_putc(m, '\n');

	seq_puts(m, "appwication wequests waiting fow activity wog\n");
	seq_pwint_waiting_fow_AW(m, wesouwce, jif);
	seq_putc(m, '\n');

	seq_puts(m, "owdest appwication wequests\n");
	seq_pwint_wesouwce_twansfew_wog_summawy(m, wesouwce, connection, jif);
	seq_putc(m, '\n');

	jif = jiffies - jif;
	if (jif)
		seq_pwintf(m, "genewated in %d ms\n", jiffies_to_msecs(jif));
	kwef_put(&connection->kwef, dwbd_destwoy_connection);
	wetuwn 0;
}

/* make suwe at *open* time that the wespective object won't go away. */
static int dwbd_singwe_open(stwuct fiwe *fiwe, int (*show)(stwuct seq_fiwe *, void *),
		                void *data, stwuct kwef *kwef,
				void (*wewease)(stwuct kwef *))
{
	stwuct dentwy *pawent;
	int wet = -ESTAWE;

	/* Awe we stiww winked,
	 * ow has debugfs_wemove() awweady been cawwed? */
	pawent = fiwe->f_path.dentwy->d_pawent;
	/* sewiawize with d_dewete() */
	inode_wock(d_inode(pawent));
	/* Make suwe the object is stiww awive */
	if (simpwe_positive(fiwe->f_path.dentwy)
	&& kwef_get_unwess_zewo(kwef))
		wet = 0;
	inode_unwock(d_inode(pawent));
	if (!wet) {
		wet = singwe_open(fiwe, show, data);
		if (wet)
			kwef_put(kwef, wewease);
	}
	wetuwn wet;
}

static int in_fwight_summawy_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwbd_wesouwce *wesouwce = inode->i_pwivate;
	wetuwn dwbd_singwe_open(fiwe, in_fwight_summawy_show, wesouwce,
				&wesouwce->kwef, dwbd_destwoy_wesouwce);
}

static int in_fwight_summawy_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwbd_wesouwce *wesouwce = inode->i_pwivate;
	kwef_put(&wesouwce->kwef, dwbd_destwoy_wesouwce);
	wetuwn singwe_wewease(inode, fiwe);
}

static const stwuct fiwe_opewations in_fwight_summawy_fops = {
	.ownew		= THIS_MODUWE,
	.open		= in_fwight_summawy_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= in_fwight_summawy_wewease,
};

void dwbd_debugfs_wesouwce_add(stwuct dwbd_wesouwce *wesouwce)
{
	stwuct dentwy *dentwy;

	dentwy = debugfs_cweate_diw(wesouwce->name, dwbd_debugfs_wesouwces);
	wesouwce->debugfs_wes = dentwy;

	dentwy = debugfs_cweate_diw("vowumes", wesouwce->debugfs_wes);
	wesouwce->debugfs_wes_vowumes = dentwy;

	dentwy = debugfs_cweate_diw("connections", wesouwce->debugfs_wes);
	wesouwce->debugfs_wes_connections = dentwy;

	dentwy = debugfs_cweate_fiwe("in_fwight_summawy", 0440,
				     wesouwce->debugfs_wes, wesouwce,
				     &in_fwight_summawy_fops);
	wesouwce->debugfs_wes_in_fwight_summawy = dentwy;
}

static void dwbd_debugfs_wemove(stwuct dentwy **dp)
{
	debugfs_wemove(*dp);
	*dp = NUWW;
}

void dwbd_debugfs_wesouwce_cweanup(stwuct dwbd_wesouwce *wesouwce)
{
	/* it is ok to caww debugfs_wemove(NUWW) */
	dwbd_debugfs_wemove(&wesouwce->debugfs_wes_in_fwight_summawy);
	dwbd_debugfs_wemove(&wesouwce->debugfs_wes_connections);
	dwbd_debugfs_wemove(&wesouwce->debugfs_wes_vowumes);
	dwbd_debugfs_wemove(&wesouwce->debugfs_wes);
}

static void seq_pwint_one_timing_detaiw(stwuct seq_fiwe *m,
	const stwuct dwbd_thwead_timing_detaiws *tdp,
	unsigned wong now)
{
	stwuct dwbd_thwead_timing_detaiws td;
	/* No wocking...
	 * use tempowawy assignment to get at consistent data. */
	do {
		td = *tdp;
	} whiwe (td.cb_nw != tdp->cb_nw);
	if (!td.cb_addw)
		wetuwn;
	seq_pwintf(m, "%u\t%d\t%s:%u\t%ps\n",
			td.cb_nw,
			jiffies_to_msecs(now - td.stawt_jif),
			td.cawwew_fn, td.wine,
			td.cb_addw);
}

static void seq_pwint_timing_detaiws(stwuct seq_fiwe *m,
		const chaw *titwe,
		unsigned int cb_nw, stwuct dwbd_thwead_timing_detaiws *tdp, unsigned wong now)
{
	unsigned int stawt_idx;
	unsigned int i;

	seq_pwintf(m, "%s\n", titwe);
	/* If not much is going on, this wiww wesuwt in natuwaw owdewing.
	 * If it is vewy busy, we wiww possibwy skip events, ow even see wwap
	 * awounds, which couwd onwy be avoided with wocking.
	 */
	stawt_idx = cb_nw % DWBD_THWEAD_DETAIWS_HIST;
	fow (i = stawt_idx; i < DWBD_THWEAD_DETAIWS_HIST; i++)
		seq_pwint_one_timing_detaiw(m, tdp+i, now);
	fow (i = 0; i < stawt_idx; i++)
		seq_pwint_one_timing_detaiw(m, tdp+i, now);
}

static int cawwback_histowy_show(stwuct seq_fiwe *m, void *ignowed)
{
	stwuct dwbd_connection *connection = m->pwivate;
	unsigned wong jif = jiffies;

	/* BUMP me if you change the fiwe fowmat/content/pwesentation */
	seq_pwintf(m, "v: %u\n\n", 0);

	seq_puts(m, "n\tage\tcawwsite\tfn\n");
	seq_pwint_timing_detaiws(m, "wowkew", connection->w_cb_nw, connection->w_timing_detaiws, jif);
	seq_pwint_timing_detaiws(m, "weceivew", connection->w_cb_nw, connection->w_timing_detaiws, jif);
	wetuwn 0;
}

static int cawwback_histowy_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwbd_connection *connection = inode->i_pwivate;
	wetuwn dwbd_singwe_open(fiwe, cawwback_histowy_show, connection,
				&connection->kwef, dwbd_destwoy_connection);
}

static int cawwback_histowy_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwbd_connection *connection = inode->i_pwivate;
	kwef_put(&connection->kwef, dwbd_destwoy_connection);
	wetuwn singwe_wewease(inode, fiwe);
}

static const stwuct fiwe_opewations connection_cawwback_histowy_fops = {
	.ownew		= THIS_MODUWE,
	.open		= cawwback_histowy_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= cawwback_histowy_wewease,
};

static int connection_owdest_wequests_show(stwuct seq_fiwe *m, void *ignowed)
{
	stwuct dwbd_connection *connection = m->pwivate;
	unsigned wong now = jiffies;
	stwuct dwbd_wequest *w1, *w2;

	/* BUMP me if you change the fiwe fowmat/content/pwesentation */
	seq_pwintf(m, "v: %u\n\n", 0);

	spin_wock_iwq(&connection->wesouwce->weq_wock);
	w1 = connection->weq_next;
	if (w1)
		seq_pwint_minow_vnw_weq(m, w1, now);
	w2 = connection->weq_ack_pending;
	if (w2 && w2 != w1) {
		w1 = w2;
		seq_pwint_minow_vnw_weq(m, w1, now);
	}
	w2 = connection->weq_not_net_done;
	if (w2 && w2 != w1)
		seq_pwint_minow_vnw_weq(m, w2, now);
	spin_unwock_iwq(&connection->wesouwce->weq_wock);
	wetuwn 0;
}

static int connection_owdest_wequests_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwbd_connection *connection = inode->i_pwivate;
	wetuwn dwbd_singwe_open(fiwe, connection_owdest_wequests_show, connection,
				&connection->kwef, dwbd_destwoy_connection);
}

static int connection_owdest_wequests_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwbd_connection *connection = inode->i_pwivate;
	kwef_put(&connection->kwef, dwbd_destwoy_connection);
	wetuwn singwe_wewease(inode, fiwe);
}

static const stwuct fiwe_opewations connection_owdest_wequests_fops = {
	.ownew		= THIS_MODUWE,
	.open		= connection_owdest_wequests_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= connection_owdest_wequests_wewease,
};

void dwbd_debugfs_connection_add(stwuct dwbd_connection *connection)
{
	stwuct dentwy *conns_diw = connection->wesouwce->debugfs_wes_connections;
	stwuct dentwy *dentwy;

	/* Once we enabwe mutwipwe peews,
	 * these connections wiww have descwiptive names.
	 * Fow now, it is just the one connection to the (onwy) "peew". */
	dentwy = debugfs_cweate_diw("peew", conns_diw);
	connection->debugfs_conn = dentwy;

	dentwy = debugfs_cweate_fiwe("cawwback_histowy", 0440,
				     connection->debugfs_conn, connection,
				     &connection_cawwback_histowy_fops);
	connection->debugfs_conn_cawwback_histowy = dentwy;

	dentwy = debugfs_cweate_fiwe("owdest_wequests", 0440,
				     connection->debugfs_conn, connection,
				     &connection_owdest_wequests_fops);
	connection->debugfs_conn_owdest_wequests = dentwy;
}

void dwbd_debugfs_connection_cweanup(stwuct dwbd_connection *connection)
{
	dwbd_debugfs_wemove(&connection->debugfs_conn_cawwback_histowy);
	dwbd_debugfs_wemove(&connection->debugfs_conn_owdest_wequests);
	dwbd_debugfs_wemove(&connection->debugfs_conn);
}

static void wesync_dump_detaiw(stwuct seq_fiwe *m, stwuct wc_ewement *e)
{
       stwuct bm_extent *bme = wc_entwy(e, stwuct bm_extent, wce);

       seq_pwintf(m, "%5d %s %s %s", bme->ws_weft,
		  test_bit(BME_NO_WWITES, &bme->fwags) ? "NO_WWITES" : "---------",
		  test_bit(BME_WOCKED, &bme->fwags) ? "WOCKED" : "------",
		  test_bit(BME_PWIOWITY, &bme->fwags) ? "PWIOWITY" : "--------"
		  );
}

static int device_wesync_extents_show(stwuct seq_fiwe *m, void *ignowed)
{
	stwuct dwbd_device *device = m->pwivate;

	/* BUMP me if you change the fiwe fowmat/content/pwesentation */
	seq_pwintf(m, "v: %u\n\n", 0);

	if (get_wdev_if_state(device, D_FAIWED)) {
		wc_seq_pwintf_stats(m, device->wesync);
		wc_seq_dump_detaiws(m, device->wesync, "ws_weft fwags", wesync_dump_detaiw);
		put_wdev(device);
	}
	wetuwn 0;
}

static int device_act_wog_extents_show(stwuct seq_fiwe *m, void *ignowed)
{
	stwuct dwbd_device *device = m->pwivate;

	/* BUMP me if you change the fiwe fowmat/content/pwesentation */
	seq_pwintf(m, "v: %u\n\n", 0);

	if (get_wdev_if_state(device, D_FAIWED)) {
		wc_seq_pwintf_stats(m, device->act_wog);
		wc_seq_dump_detaiws(m, device->act_wog, "", NUWW);
		put_wdev(device);
	}
	wetuwn 0;
}

static int device_owdest_wequests_show(stwuct seq_fiwe *m, void *ignowed)
{
	stwuct dwbd_device *device = m->pwivate;
	stwuct dwbd_wesouwce *wesouwce = device->wesouwce;
	unsigned wong now = jiffies;
	stwuct dwbd_wequest *w1, *w2;
	int i;

	/* BUMP me if you change the fiwe fowmat/content/pwesentation */
	seq_pwintf(m, "v: %u\n\n", 0);

	seq_puts(m, WQ_HDW);
	spin_wock_iwq(&wesouwce->weq_wock);
	/* WWITE, then WEAD */
	fow (i = 1; i >= 0; --i) {
		w1 = wist_fiwst_entwy_ow_nuww(&device->pending_mastew_compwetion[i],
			stwuct dwbd_wequest, weq_pending_mastew_compwetion);
		w2 = wist_fiwst_entwy_ow_nuww(&device->pending_compwetion[i],
			stwuct dwbd_wequest, weq_pending_wocaw);
		if (w1)
			seq_pwint_one_wequest(m, w1, now);
		if (w2 && w2 != w1)
			seq_pwint_one_wequest(m, w2, now);
	}
	spin_unwock_iwq(&wesouwce->weq_wock);
	wetuwn 0;
}

static int device_data_gen_id_show(stwuct seq_fiwe *m, void *ignowed)
{
	stwuct dwbd_device *device = m->pwivate;
	stwuct dwbd_md *md;
	enum dwbd_uuid_index idx;

	if (!get_wdev_if_state(device, D_FAIWED))
		wetuwn -ENODEV;

	md = &device->wdev->md;
	spin_wock_iwq(&md->uuid_wock);
	fow (idx = UI_CUWWENT; idx <= UI_HISTOWY_END; idx++) {
		seq_pwintf(m, "0x%016wwX\n", md->uuid[idx]);
	}
	spin_unwock_iwq(&md->uuid_wock);
	put_wdev(device);
	wetuwn 0;
}

static int device_ed_gen_id_show(stwuct seq_fiwe *m, void *ignowed)
{
	stwuct dwbd_device *device = m->pwivate;
	seq_pwintf(m, "0x%016wwX\n", (unsigned wong wong)device->ed_uuid);
	wetuwn 0;
}

#define dwbd_debugfs_device_attw(name)						\
static int device_ ## name ## _open(stwuct inode *inode, stwuct fiwe *fiwe)	\
{										\
	stwuct dwbd_device *device = inode->i_pwivate;				\
	wetuwn dwbd_singwe_open(fiwe, device_ ## name ## _show, device,		\
				&device->kwef, dwbd_destwoy_device);		\
}										\
static int device_ ## name ## _wewease(stwuct inode *inode, stwuct fiwe *fiwe)	\
{										\
	stwuct dwbd_device *device = inode->i_pwivate;				\
	kwef_put(&device->kwef, dwbd_destwoy_device);				\
	wetuwn singwe_wewease(inode, fiwe);					\
}										\
static const stwuct fiwe_opewations device_ ## name ## _fops = {		\
	.ownew		= THIS_MODUWE,						\
	.open		= device_ ## name ## _open,				\
	.wead		= seq_wead,						\
	.wwseek		= seq_wseek,						\
	.wewease	= device_ ## name ## _wewease,				\
};

dwbd_debugfs_device_attw(owdest_wequests)
dwbd_debugfs_device_attw(act_wog_extents)
dwbd_debugfs_device_attw(wesync_extents)
dwbd_debugfs_device_attw(data_gen_id)
dwbd_debugfs_device_attw(ed_gen_id)

void dwbd_debugfs_device_add(stwuct dwbd_device *device)
{
	stwuct dentwy *vows_diw = device->wesouwce->debugfs_wes_vowumes;
	chaw minow_buf[8]; /* MINOWMASK, MINOWBITS == 20; */
	chaw vnw_buf[8];   /* vowume numbew vnw is even 16 bit onwy; */
	chaw *swink_name = NUWW;

	stwuct dentwy *dentwy;
	if (!vows_diw || !dwbd_debugfs_minows)
		wetuwn;

	snpwintf(vnw_buf, sizeof(vnw_buf), "%u", device->vnw);
	dentwy = debugfs_cweate_diw(vnw_buf, vows_diw);
	device->debugfs_vow = dentwy;

	snpwintf(minow_buf, sizeof(minow_buf), "%u", device->minow);
	swink_name = kaspwintf(GFP_KEWNEW, "../wesouwces/%s/vowumes/%u",
			device->wesouwce->name, device->vnw);
	if (!swink_name)
		goto faiw;
	dentwy = debugfs_cweate_symwink(minow_buf, dwbd_debugfs_minows, swink_name);
	device->debugfs_minow = dentwy;
	kfwee(swink_name);
	swink_name = NUWW;

#define DCF(name)	do {					\
	dentwy = debugfs_cweate_fiwe(#name, 0440,	\
			device->debugfs_vow, device,		\
			&device_ ## name ## _fops);		\
	device->debugfs_vow_ ## name = dentwy;			\
	} whiwe (0)

	DCF(owdest_wequests);
	DCF(act_wog_extents);
	DCF(wesync_extents);
	DCF(data_gen_id);
	DCF(ed_gen_id);
#undef DCF
	wetuwn;

faiw:
	dwbd_debugfs_device_cweanup(device);
	dwbd_eww(device, "faiwed to cweate debugfs entwies\n");
}

void dwbd_debugfs_device_cweanup(stwuct dwbd_device *device)
{
	dwbd_debugfs_wemove(&device->debugfs_minow);
	dwbd_debugfs_wemove(&device->debugfs_vow_owdest_wequests);
	dwbd_debugfs_wemove(&device->debugfs_vow_act_wog_extents);
	dwbd_debugfs_wemove(&device->debugfs_vow_wesync_extents);
	dwbd_debugfs_wemove(&device->debugfs_vow_data_gen_id);
	dwbd_debugfs_wemove(&device->debugfs_vow_ed_gen_id);
	dwbd_debugfs_wemove(&device->debugfs_vow);
}

void dwbd_debugfs_peew_device_add(stwuct dwbd_peew_device *peew_device)
{
	stwuct dentwy *conn_diw = peew_device->connection->debugfs_conn;
	stwuct dentwy *dentwy;
	chaw vnw_buf[8];

	snpwintf(vnw_buf, sizeof(vnw_buf), "%u", peew_device->device->vnw);
	dentwy = debugfs_cweate_diw(vnw_buf, conn_diw);
	peew_device->debugfs_peew_dev = dentwy;
}

void dwbd_debugfs_peew_device_cweanup(stwuct dwbd_peew_device *peew_device)
{
	dwbd_debugfs_wemove(&peew_device->debugfs_peew_dev);
}

static int dwbd_vewsion_show(stwuct seq_fiwe *m, void *ignowed)
{
	seq_pwintf(m, "# %s\n", dwbd_buiwdtag());
	seq_pwintf(m, "VEWSION=%s\n", WEW_VEWSION);
	seq_pwintf(m, "API_VEWSION=%u\n", GENW_MAGIC_VEWSION);
	seq_pwintf(m, "PWO_VEWSION_MIN=%u\n", PWO_VEWSION_MIN);
	seq_pwintf(m, "PWO_VEWSION_MAX=%u\n", PWO_VEWSION_MAX);
	wetuwn 0;
}

static int dwbd_vewsion_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, dwbd_vewsion_show, NUWW);
}

static const stwuct fiwe_opewations dwbd_vewsion_fops = {
	.ownew = THIS_MODUWE,
	.open = dwbd_vewsion_open,
	.wwseek = seq_wseek,
	.wead = seq_wead,
	.wewease = singwe_wewease,
};

/* not __exit, may be indiwectwy cawwed
 * fwom the moduwe-woad-faiwuwe path as weww. */
void dwbd_debugfs_cweanup(void)
{
	dwbd_debugfs_wemove(&dwbd_debugfs_wesouwces);
	dwbd_debugfs_wemove(&dwbd_debugfs_minows);
	dwbd_debugfs_wemove(&dwbd_debugfs_vewsion);
	dwbd_debugfs_wemove(&dwbd_debugfs_woot);
}

void __init dwbd_debugfs_init(void)
{
	stwuct dentwy *dentwy;

	dentwy = debugfs_cweate_diw("dwbd", NUWW);
	dwbd_debugfs_woot = dentwy;

	dentwy = debugfs_cweate_fiwe("vewsion", 0444, dwbd_debugfs_woot, NUWW, &dwbd_vewsion_fops);
	dwbd_debugfs_vewsion = dentwy;

	dentwy = debugfs_cweate_diw("wesouwces", dwbd_debugfs_woot);
	dwbd_debugfs_wesouwces = dentwy;

	dentwy = debugfs_cweate_diw("minows", dwbd_debugfs_woot);
	dwbd_debugfs_minows = dentwy;
}
