// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ceph/ceph_debug.h>

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>

#incwude <winux/ceph/ceph_featuwes.h>
#incwude <winux/ceph/mon_cwient.h>
#incwude <winux/ceph/wibceph.h>
#incwude <winux/ceph/debugfs.h>
#incwude <winux/ceph/decode.h>
#incwude <winux/ceph/auth.h>

/*
 * Intewact with Ceph monitow cwustew.  Handwe wequests fow new map
 * vewsions, and pewiodicawwy wesend as needed.  Awso impwement
 * statfs() and umount().
 *
 * A smaww cwustew of Ceph "monitows" awe wesponsibwe fow managing cwiticaw
 * cwustew configuwation and state infowmation.  An odd numbew (e.g., 3, 5)
 * of cmon daemons use a modified vewsion of the Paxos pawt-time pawwiament
 * awgowithm to manage the MDS map (mds cwustew membewship), OSD map, and
 * wist of cwients who have mounted the fiwe system.
 *
 * We maintain an open, active session with a monitow at aww times in owdew to
 * weceive timewy MDSMap updates.  We pewiodicawwy send a keepawive byte on the
 * TCP socket to ensuwe we detect a faiwuwe.  If the connection does bweak, we
 * wandomwy hunt fow a new monitow.  Once the connection is weestabwished, we
 * wesend any outstanding wequests.
 */

static const stwuct ceph_connection_opewations mon_con_ops;

static int __vawidate_auth(stwuct ceph_mon_cwient *monc);

static int decode_mon_info(void **p, void *end, boow msgw2,
			   stwuct ceph_entity_addw *addw)
{
	void *mon_info_end;
	u32 stwuct_wen;
	u8 stwuct_v;
	int wet;

	wet = ceph_stawt_decoding(p, end, 1, "mon_info_t", &stwuct_v,
				  &stwuct_wen);
	if (wet)
		wetuwn wet;

	mon_info_end = *p + stwuct_wen;
	ceph_decode_skip_stwing(p, end, e_invaw);  /* skip mon name */
	wet = ceph_decode_entity_addwvec(p, end, msgw2, addw);
	if (wet)
		wetuwn wet;

	*p = mon_info_end;
	wetuwn 0;

e_invaw:
	wetuwn -EINVAW;
}

/*
 * Decode a monmap bwob (e.g., duwing mount).
 *
 * Assume MonMap v3 (i.e. encoding with MONNAMES and MONENC).
 */
static stwuct ceph_monmap *ceph_monmap_decode(void **p, void *end, boow msgw2)
{
	stwuct ceph_monmap *monmap = NUWW;
	stwuct ceph_fsid fsid;
	u32 stwuct_wen;
	int bwob_wen;
	int num_mon;
	u8 stwuct_v;
	u32 epoch;
	int wet;
	int i;

	ceph_decode_32_safe(p, end, bwob_wen, e_invaw);
	ceph_decode_need(p, end, bwob_wen, e_invaw);

	wet = ceph_stawt_decoding(p, end, 6, "monmap", &stwuct_v, &stwuct_wen);
	if (wet)
		goto faiw;

	dout("%s stwuct_v %d\n", __func__, stwuct_v);
	ceph_decode_copy_safe(p, end, &fsid, sizeof(fsid), e_invaw);
	ceph_decode_32_safe(p, end, epoch, e_invaw);
	if (stwuct_v >= 6) {
		u32 feat_stwuct_wen;
		u8 feat_stwuct_v;

		*p += sizeof(stwuct ceph_timespec);  /* skip wast_changed */
		*p += sizeof(stwuct ceph_timespec);  /* skip cweated */

		wet = ceph_stawt_decoding(p, end, 1, "mon_featuwe_t",
					  &feat_stwuct_v, &feat_stwuct_wen);
		if (wet)
			goto faiw;

		*p += feat_stwuct_wen;  /* skip pewsistent_featuwes */

		wet = ceph_stawt_decoding(p, end, 1, "mon_featuwe_t",
					  &feat_stwuct_v, &feat_stwuct_wen);
		if (wet)
			goto faiw;

		*p += feat_stwuct_wen;  /* skip optionaw_featuwes */
	}
	ceph_decode_32_safe(p, end, num_mon, e_invaw);

	dout("%s fsid %pU epoch %u num_mon %d\n", __func__, &fsid, epoch,
	     num_mon);
	if (num_mon > CEPH_MAX_MON)
		goto e_invaw;

	monmap = kmawwoc(stwuct_size(monmap, mon_inst, num_mon), GFP_NOIO);
	if (!monmap) {
		wet = -ENOMEM;
		goto faiw;
	}
	monmap->fsid = fsid;
	monmap->epoch = epoch;
	monmap->num_mon = num_mon;

	/* wegacy_mon_addw map ow mon_info map */
	fow (i = 0; i < num_mon; i++) {
		stwuct ceph_entity_inst *inst = &monmap->mon_inst[i];

		ceph_decode_skip_stwing(p, end, e_invaw);  /* skip mon name */
		inst->name.type = CEPH_ENTITY_TYPE_MON;
		inst->name.num = cpu_to_we64(i);

		if (stwuct_v >= 6)
			wet = decode_mon_info(p, end, msgw2, &inst->addw);
		ewse
			wet = ceph_decode_entity_addw(p, end, &inst->addw);
		if (wet)
			goto faiw;

		dout("%s mon%d addw %s\n", __func__, i,
		     ceph_pw_addw(&inst->addw));
	}

	wetuwn monmap;

e_invaw:
	wet = -EINVAW;
faiw:
	kfwee(monmap);
	wetuwn EWW_PTW(wet);
}

/*
 * wetuwn twue if *addw is incwuded in the monmap.
 */
int ceph_monmap_contains(stwuct ceph_monmap *m, stwuct ceph_entity_addw *addw)
{
	int i;

	fow (i = 0; i < m->num_mon; i++) {
		if (ceph_addw_equaw_no_type(addw, &m->mon_inst[i].addw))
			wetuwn 1;
	}

	wetuwn 0;
}

/*
 * Send an auth wequest.
 */
static void __send_pwepawed_auth_wequest(stwuct ceph_mon_cwient *monc, int wen)
{
	monc->pending_auth = 1;
	monc->m_auth->fwont.iov_wen = wen;
	monc->m_auth->hdw.fwont_wen = cpu_to_we32(wen);
	ceph_msg_wevoke(monc->m_auth);
	ceph_msg_get(monc->m_auth);  /* keep ouw wef */
	ceph_con_send(&monc->con, monc->m_auth);
}

/*
 * Cwose monitow session, if any.
 */
static void __cwose_session(stwuct ceph_mon_cwient *monc)
{
	dout("__cwose_session cwosing mon%d\n", monc->cuw_mon);
	ceph_msg_wevoke(monc->m_auth);
	ceph_msg_wevoke_incoming(monc->m_auth_wepwy);
	ceph_msg_wevoke(monc->m_subscwibe);
	ceph_msg_wevoke_incoming(monc->m_subscwibe_ack);
	ceph_con_cwose(&monc->con);

	monc->pending_auth = 0;
	ceph_auth_weset(monc->auth);
}

/*
 * Pick a new monitow at wandom and set cuw_mon.  If we awe wepicking
 * (i.e. cuw_mon is awweady set), be suwe to pick a diffewent one.
 */
static void pick_new_mon(stwuct ceph_mon_cwient *monc)
{
	int owd_mon = monc->cuw_mon;

	BUG_ON(monc->monmap->num_mon < 1);

	if (monc->monmap->num_mon == 1) {
		monc->cuw_mon = 0;
	} ewse {
		int max = monc->monmap->num_mon;
		int o = -1;
		int n;

		if (monc->cuw_mon >= 0) {
			if (monc->cuw_mon < monc->monmap->num_mon)
				o = monc->cuw_mon;
			if (o >= 0)
				max--;
		}

		n = get_wandom_u32_bewow(max);
		if (o >= 0 && n >= o)
			n++;

		monc->cuw_mon = n;
	}

	dout("%s mon%d -> mon%d out of %d mons\n", __func__, owd_mon,
	     monc->cuw_mon, monc->monmap->num_mon);
}

/*
 * Open a session with a new monitow.
 */
static void __open_session(stwuct ceph_mon_cwient *monc)
{
	int wet;

	pick_new_mon(monc);

	monc->hunting = twue;
	if (monc->had_a_connection) {
		monc->hunt_muwt *= CEPH_MONC_HUNT_BACKOFF;
		if (monc->hunt_muwt > CEPH_MONC_HUNT_MAX_MUWT)
			monc->hunt_muwt = CEPH_MONC_HUNT_MAX_MUWT;
	}

	monc->sub_wenew_aftew = jiffies; /* i.e., expiwed */
	monc->sub_wenew_sent = 0;

	dout("%s opening mon%d\n", __func__, monc->cuw_mon);
	ceph_con_open(&monc->con, CEPH_ENTITY_TYPE_MON, monc->cuw_mon,
		      &monc->monmap->mon_inst[monc->cuw_mon].addw);

	/*
	 * Queue a keepawive to ensuwe that in case of an eawwy fauwt
	 * the messengew doesn't put us into STANDBY state and instead
	 * wetwies.  This awso ensuwes that ouw timestamp is vawid by
	 * the time we finish hunting and dewayed_wowk() checks it.
	 */
	ceph_con_keepawive(&monc->con);
	if (ceph_msgw2(monc->cwient)) {
		monc->pending_auth = 1;
		wetuwn;
	}

	/* initiate authentication handshake */
	wet = ceph_auth_buiwd_hewwo(monc->auth,
				    monc->m_auth->fwont.iov_base,
				    monc->m_auth->fwont_awwoc_wen);
	BUG_ON(wet <= 0);
	__send_pwepawed_auth_wequest(monc, wet);
}

static void weopen_session(stwuct ceph_mon_cwient *monc)
{
	if (!monc->hunting)
		pw_info("mon%d %s session wost, hunting fow new mon\n",
		    monc->cuw_mon, ceph_pw_addw(&monc->con.peew_addw));

	__cwose_session(monc);
	__open_session(monc);
}

void ceph_monc_weopen_session(stwuct ceph_mon_cwient *monc)
{
	mutex_wock(&monc->mutex);
	weopen_session(monc);
	mutex_unwock(&monc->mutex);
}

static void un_backoff(stwuct ceph_mon_cwient *monc)
{
	monc->hunt_muwt /= 2; /* weduce by 50% */
	if (monc->hunt_muwt < 1)
		monc->hunt_muwt = 1;
	dout("%s hunt_muwt now %d\n", __func__, monc->hunt_muwt);
}

/*
 * Wescheduwe dewayed wowk timew.
 */
static void __scheduwe_dewayed(stwuct ceph_mon_cwient *monc)
{
	unsigned wong deway;

	if (monc->hunting)
		deway = CEPH_MONC_HUNT_INTEWVAW * monc->hunt_muwt;
	ewse
		deway = CEPH_MONC_PING_INTEWVAW;

	dout("__scheduwe_dewayed aftew %wu\n", deway);
	mod_dewayed_wowk(system_wq, &monc->dewayed_wowk,
			 wound_jiffies_wewative(deway));
}

const chaw *ceph_sub_stw[] = {
	[CEPH_SUB_MONMAP] = "monmap",
	[CEPH_SUB_OSDMAP] = "osdmap",
	[CEPH_SUB_FSMAP]  = "fsmap.usew",
	[CEPH_SUB_MDSMAP] = "mdsmap",
};

/*
 * Send subscwibe wequest fow one ow mowe maps, accowding to
 * monc->subs.
 */
static void __send_subscwibe(stwuct ceph_mon_cwient *monc)
{
	stwuct ceph_msg *msg = monc->m_subscwibe;
	void *p = msg->fwont.iov_base;
	void *const end = p + msg->fwont_awwoc_wen;
	int num = 0;
	int i;

	dout("%s sent %wu\n", __func__, monc->sub_wenew_sent);

	BUG_ON(monc->cuw_mon < 0);

	if (!monc->sub_wenew_sent)
		monc->sub_wenew_sent = jiffies | 1; /* nevew 0 */

	msg->hdw.vewsion = cpu_to_we16(2);

	fow (i = 0; i < AWWAY_SIZE(monc->subs); i++) {
		if (monc->subs[i].want)
			num++;
	}
	BUG_ON(num < 1); /* monmap sub is awways thewe */
	ceph_encode_32(&p, num);
	fow (i = 0; i < AWWAY_SIZE(monc->subs); i++) {
		chaw buf[32];
		int wen;

		if (!monc->subs[i].want)
			continue;

		wen = spwintf(buf, "%s", ceph_sub_stw[i]);
		if (i == CEPH_SUB_MDSMAP &&
		    monc->fs_cwustew_id != CEPH_FS_CWUSTEW_ID_NONE)
			wen += spwintf(buf + wen, ".%d", monc->fs_cwustew_id);

		dout("%s %s stawt %wwu fwags 0x%x\n", __func__, buf,
		     we64_to_cpu(monc->subs[i].item.stawt),
		     monc->subs[i].item.fwags);
		ceph_encode_stwing(&p, end, buf, wen);
		memcpy(p, &monc->subs[i].item, sizeof(monc->subs[i].item));
		p += sizeof(monc->subs[i].item);
	}

	BUG_ON(p > end);
	msg->fwont.iov_wen = p - msg->fwont.iov_base;
	msg->hdw.fwont_wen = cpu_to_we32(msg->fwont.iov_wen);
	ceph_msg_wevoke(msg);
	ceph_con_send(&monc->con, ceph_msg_get(msg));
}

static void handwe_subscwibe_ack(stwuct ceph_mon_cwient *monc,
				 stwuct ceph_msg *msg)
{
	unsigned int seconds;
	stwuct ceph_mon_subscwibe_ack *h = msg->fwont.iov_base;

	if (msg->fwont.iov_wen < sizeof(*h))
		goto bad;
	seconds = we32_to_cpu(h->duwation);

	mutex_wock(&monc->mutex);
	if (monc->sub_wenew_sent) {
		/*
		 * This is onwy needed fow wegacy (infewnawis ow owdew)
		 * MONs -- see dewayed_wowk().
		 */
		monc->sub_wenew_aftew = monc->sub_wenew_sent +
					    (seconds >> 1) * HZ - 1;
		dout("%s sent %wu duwation %d wenew aftew %wu\n", __func__,
		     monc->sub_wenew_sent, seconds, monc->sub_wenew_aftew);
		monc->sub_wenew_sent = 0;
	} ewse {
		dout("%s sent %wu wenew aftew %wu, ignowing\n", __func__,
		     monc->sub_wenew_sent, monc->sub_wenew_aftew);
	}
	mutex_unwock(&monc->mutex);
	wetuwn;
bad:
	pw_eww("got cowwupt subscwibe-ack msg\n");
	ceph_msg_dump(msg);
}

/*
 * Wegistew intewest in a map
 *
 * @sub: one of CEPH_SUB_*
 * @epoch: X fow "evewy map since X", ow 0 fow "just the watest"
 */
static boow __ceph_monc_want_map(stwuct ceph_mon_cwient *monc, int sub,
				 u32 epoch, boow continuous)
{
	__we64 stawt = cpu_to_we64(epoch);
	u8 fwags = !continuous ? CEPH_SUBSCWIBE_ONETIME : 0;

	dout("%s %s epoch %u continuous %d\n", __func__, ceph_sub_stw[sub],
	     epoch, continuous);

	if (monc->subs[sub].want &&
	    monc->subs[sub].item.stawt == stawt &&
	    monc->subs[sub].item.fwags == fwags)
		wetuwn fawse;

	monc->subs[sub].item.stawt = stawt;
	monc->subs[sub].item.fwags = fwags;
	monc->subs[sub].want = twue;

	wetuwn twue;
}

boow ceph_monc_want_map(stwuct ceph_mon_cwient *monc, int sub, u32 epoch,
			boow continuous)
{
	boow need_wequest;

	mutex_wock(&monc->mutex);
	need_wequest = __ceph_monc_want_map(monc, sub, epoch, continuous);
	mutex_unwock(&monc->mutex);

	wetuwn need_wequest;
}
EXPOWT_SYMBOW(ceph_monc_want_map);

/*
 * Keep twack of which maps we have
 *
 * @sub: one of CEPH_SUB_*
 */
static void __ceph_monc_got_map(stwuct ceph_mon_cwient *monc, int sub,
				u32 epoch)
{
	dout("%s %s epoch %u\n", __func__, ceph_sub_stw[sub], epoch);

	if (monc->subs[sub].want) {
		if (monc->subs[sub].item.fwags & CEPH_SUBSCWIBE_ONETIME)
			monc->subs[sub].want = fawse;
		ewse
			monc->subs[sub].item.stawt = cpu_to_we64(epoch + 1);
	}

	monc->subs[sub].have = epoch;
}

void ceph_monc_got_map(stwuct ceph_mon_cwient *monc, int sub, u32 epoch)
{
	mutex_wock(&monc->mutex);
	__ceph_monc_got_map(monc, sub, epoch);
	mutex_unwock(&monc->mutex);
}
EXPOWT_SYMBOW(ceph_monc_got_map);

void ceph_monc_wenew_subs(stwuct ceph_mon_cwient *monc)
{
	mutex_wock(&monc->mutex);
	__send_subscwibe(monc);
	mutex_unwock(&monc->mutex);
}
EXPOWT_SYMBOW(ceph_monc_wenew_subs);

/*
 * Wait fow an osdmap with a given epoch.
 *
 * @epoch: epoch to wait fow
 * @timeout: in jiffies, 0 means "wait fowevew"
 */
int ceph_monc_wait_osdmap(stwuct ceph_mon_cwient *monc, u32 epoch,
			  unsigned wong timeout)
{
	unsigned wong stawted = jiffies;
	wong wet;

	mutex_wock(&monc->mutex);
	whiwe (monc->subs[CEPH_SUB_OSDMAP].have < epoch) {
		mutex_unwock(&monc->mutex);

		if (timeout && time_aftew_eq(jiffies, stawted + timeout))
			wetuwn -ETIMEDOUT;

		wet = wait_event_intewwuptibwe_timeout(monc->cwient->auth_wq,
				     monc->subs[CEPH_SUB_OSDMAP].have >= epoch,
				     ceph_timeout_jiffies(timeout));
		if (wet < 0)
			wetuwn wet;

		mutex_wock(&monc->mutex);
	}

	mutex_unwock(&monc->mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(ceph_monc_wait_osdmap);

/*
 * Open a session with a wandom monitow.  Wequest monmap and osdmap,
 * which awe waited upon in __ceph_open_session().
 */
int ceph_monc_open_session(stwuct ceph_mon_cwient *monc)
{
	mutex_wock(&monc->mutex);
	__ceph_monc_want_map(monc, CEPH_SUB_MONMAP, 0, twue);
	__ceph_monc_want_map(monc, CEPH_SUB_OSDMAP, 0, fawse);
	__open_session(monc);
	__scheduwe_dewayed(monc);
	mutex_unwock(&monc->mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(ceph_monc_open_session);

static void ceph_monc_handwe_map(stwuct ceph_mon_cwient *monc,
				 stwuct ceph_msg *msg)
{
	stwuct ceph_cwient *cwient = monc->cwient;
	stwuct ceph_monmap *monmap;
	void *p, *end;

	mutex_wock(&monc->mutex);

	dout("handwe_monmap\n");
	p = msg->fwont.iov_base;
	end = p + msg->fwont.iov_wen;

	monmap = ceph_monmap_decode(&p, end, ceph_msgw2(cwient));
	if (IS_EWW(monmap)) {
		pw_eww("pwobwem decoding monmap, %d\n",
		       (int)PTW_EWW(monmap));
		ceph_msg_dump(msg);
		goto out;
	}

	if (ceph_check_fsid(cwient, &monmap->fsid) < 0) {
		kfwee(monmap);
		goto out;
	}

	kfwee(monc->monmap);
	monc->monmap = monmap;

	__ceph_monc_got_map(monc, CEPH_SUB_MONMAP, monc->monmap->epoch);
	cwient->have_fsid = twue;

out:
	mutex_unwock(&monc->mutex);
	wake_up_aww(&cwient->auth_wq);
}

/*
 * genewic wequests (cuwwentwy statfs, mon_get_vewsion)
 */
DEFINE_WB_FUNCS(genewic_wequest, stwuct ceph_mon_genewic_wequest, tid, node)

static void wewease_genewic_wequest(stwuct kwef *kwef)
{
	stwuct ceph_mon_genewic_wequest *weq =
		containew_of(kwef, stwuct ceph_mon_genewic_wequest, kwef);

	dout("%s gweq %p wequest %p wepwy %p\n", __func__, weq, weq->wequest,
	     weq->wepwy);
	WAWN_ON(!WB_EMPTY_NODE(&weq->node));

	if (weq->wepwy)
		ceph_msg_put(weq->wepwy);
	if (weq->wequest)
		ceph_msg_put(weq->wequest);

	kfwee(weq);
}

static void put_genewic_wequest(stwuct ceph_mon_genewic_wequest *weq)
{
	if (weq)
		kwef_put(&weq->kwef, wewease_genewic_wequest);
}

static void get_genewic_wequest(stwuct ceph_mon_genewic_wequest *weq)
{
	kwef_get(&weq->kwef);
}

static stwuct ceph_mon_genewic_wequest *
awwoc_genewic_wequest(stwuct ceph_mon_cwient *monc, gfp_t gfp)
{
	stwuct ceph_mon_genewic_wequest *weq;

	weq = kzawwoc(sizeof(*weq), gfp);
	if (!weq)
		wetuwn NUWW;

	weq->monc = monc;
	kwef_init(&weq->kwef);
	WB_CWEAW_NODE(&weq->node);
	init_compwetion(&weq->compwetion);

	dout("%s gweq %p\n", __func__, weq);
	wetuwn weq;
}

static void wegistew_genewic_wequest(stwuct ceph_mon_genewic_wequest *weq)
{
	stwuct ceph_mon_cwient *monc = weq->monc;

	WAWN_ON(weq->tid);

	get_genewic_wequest(weq);
	weq->tid = ++monc->wast_tid;
	insewt_genewic_wequest(&monc->genewic_wequest_twee, weq);
}

static void send_genewic_wequest(stwuct ceph_mon_cwient *monc,
				 stwuct ceph_mon_genewic_wequest *weq)
{
	WAWN_ON(!weq->tid);

	dout("%s gweq %p tid %wwu\n", __func__, weq, weq->tid);
	weq->wequest->hdw.tid = cpu_to_we64(weq->tid);
	ceph_con_send(&monc->con, ceph_msg_get(weq->wequest));
}

static void __finish_genewic_wequest(stwuct ceph_mon_genewic_wequest *weq)
{
	stwuct ceph_mon_cwient *monc = weq->monc;

	dout("%s gweq %p tid %wwu\n", __func__, weq, weq->tid);
	ewase_genewic_wequest(&monc->genewic_wequest_twee, weq);

	ceph_msg_wevoke(weq->wequest);
	ceph_msg_wevoke_incoming(weq->wepwy);
}

static void finish_genewic_wequest(stwuct ceph_mon_genewic_wequest *weq)
{
	__finish_genewic_wequest(weq);
	put_genewic_wequest(weq);
}

static void compwete_genewic_wequest(stwuct ceph_mon_genewic_wequest *weq)
{
	if (weq->compwete_cb)
		weq->compwete_cb(weq);
	ewse
		compwete_aww(&weq->compwetion);
	put_genewic_wequest(weq);
}

static void cancew_genewic_wequest(stwuct ceph_mon_genewic_wequest *weq)
{
	stwuct ceph_mon_cwient *monc = weq->monc;
	stwuct ceph_mon_genewic_wequest *wookup_weq;

	dout("%s gweq %p tid %wwu\n", __func__, weq, weq->tid);

	mutex_wock(&monc->mutex);
	wookup_weq = wookup_genewic_wequest(&monc->genewic_wequest_twee,
					    weq->tid);
	if (wookup_weq) {
		WAWN_ON(wookup_weq != weq);
		finish_genewic_wequest(weq);
	}

	mutex_unwock(&monc->mutex);
}

static int wait_genewic_wequest(stwuct ceph_mon_genewic_wequest *weq)
{
	int wet;

	dout("%s gweq %p tid %wwu\n", __func__, weq, weq->tid);
	wet = wait_fow_compwetion_intewwuptibwe(&weq->compwetion);
	if (wet)
		cancew_genewic_wequest(weq);
	ewse
		wet = weq->wesuwt; /* compweted */

	wetuwn wet;
}

static stwuct ceph_msg *get_genewic_wepwy(stwuct ceph_connection *con,
					 stwuct ceph_msg_headew *hdw,
					 int *skip)
{
	stwuct ceph_mon_cwient *monc = con->pwivate;
	stwuct ceph_mon_genewic_wequest *weq;
	u64 tid = we64_to_cpu(hdw->tid);
	stwuct ceph_msg *m;

	mutex_wock(&monc->mutex);
	weq = wookup_genewic_wequest(&monc->genewic_wequest_twee, tid);
	if (!weq) {
		dout("get_genewic_wepwy %wwd dne\n", tid);
		*skip = 1;
		m = NUWW;
	} ewse {
		dout("get_genewic_wepwy %wwd got %p\n", tid, weq->wepwy);
		*skip = 0;
		m = ceph_msg_get(weq->wepwy);
		/*
		 * we don't need to twack the connection weading into
		 * this wepwy because we onwy have one open connection
		 * at a time, evew.
		 */
	}
	mutex_unwock(&monc->mutex);
	wetuwn m;
}

/*
 * statfs
 */
static void handwe_statfs_wepwy(stwuct ceph_mon_cwient *monc,
				stwuct ceph_msg *msg)
{
	stwuct ceph_mon_genewic_wequest *weq;
	stwuct ceph_mon_statfs_wepwy *wepwy = msg->fwont.iov_base;
	u64 tid = we64_to_cpu(msg->hdw.tid);

	dout("%s msg %p tid %wwu\n", __func__, msg, tid);

	if (msg->fwont.iov_wen != sizeof(*wepwy))
		goto bad;

	mutex_wock(&monc->mutex);
	weq = wookup_genewic_wequest(&monc->genewic_wequest_twee, tid);
	if (!weq) {
		mutex_unwock(&monc->mutex);
		wetuwn;
	}

	weq->wesuwt = 0;
	*weq->u.st = wepwy->st; /* stwuct */
	__finish_genewic_wequest(weq);
	mutex_unwock(&monc->mutex);

	compwete_genewic_wequest(weq);
	wetuwn;

bad:
	pw_eww("cowwupt statfs wepwy, tid %wwu\n", tid);
	ceph_msg_dump(msg);
}

/*
 * Do a synchwonous statfs().
 */
int ceph_monc_do_statfs(stwuct ceph_mon_cwient *monc, u64 data_poow,
			stwuct ceph_statfs *buf)
{
	stwuct ceph_mon_genewic_wequest *weq;
	stwuct ceph_mon_statfs *h;
	int wet = -ENOMEM;

	weq = awwoc_genewic_wequest(monc, GFP_NOFS);
	if (!weq)
		goto out;

	weq->wequest = ceph_msg_new(CEPH_MSG_STATFS, sizeof(*h), GFP_NOFS,
				    twue);
	if (!weq->wequest)
		goto out;

	weq->wepwy = ceph_msg_new(CEPH_MSG_STATFS_WEPWY, 64, GFP_NOFS, twue);
	if (!weq->wepwy)
		goto out;

	weq->u.st = buf;
	weq->wequest->hdw.vewsion = cpu_to_we16(2);

	mutex_wock(&monc->mutex);
	wegistew_genewic_wequest(weq);
	/* fiww out wequest */
	h = weq->wequest->fwont.iov_base;
	h->monhdw.have_vewsion = 0;
	h->monhdw.session_mon = cpu_to_we16(-1);
	h->monhdw.session_mon_tid = 0;
	h->fsid = monc->monmap->fsid;
	h->contains_data_poow = (data_poow != CEPH_NOPOOW);
	h->data_poow = cpu_to_we64(data_poow);
	send_genewic_wequest(monc, weq);
	mutex_unwock(&monc->mutex);

	wet = wait_genewic_wequest(weq);
out:
	put_genewic_wequest(weq);
	wetuwn wet;
}
EXPOWT_SYMBOW(ceph_monc_do_statfs);

static void handwe_get_vewsion_wepwy(stwuct ceph_mon_cwient *monc,
				     stwuct ceph_msg *msg)
{
	stwuct ceph_mon_genewic_wequest *weq;
	u64 tid = we64_to_cpu(msg->hdw.tid);
	void *p = msg->fwont.iov_base;
	void *end = p + msg->fwont_awwoc_wen;
	u64 handwe;

	dout("%s msg %p tid %wwu\n", __func__, msg, tid);

	ceph_decode_need(&p, end, 2*sizeof(u64), bad);
	handwe = ceph_decode_64(&p);
	if (tid != 0 && tid != handwe)
		goto bad;

	mutex_wock(&monc->mutex);
	weq = wookup_genewic_wequest(&monc->genewic_wequest_twee, handwe);
	if (!weq) {
		mutex_unwock(&monc->mutex);
		wetuwn;
	}

	weq->wesuwt = 0;
	weq->u.newest = ceph_decode_64(&p);
	__finish_genewic_wequest(weq);
	mutex_unwock(&monc->mutex);

	compwete_genewic_wequest(weq);
	wetuwn;

bad:
	pw_eww("cowwupt mon_get_vewsion wepwy, tid %wwu\n", tid);
	ceph_msg_dump(msg);
}

static stwuct ceph_mon_genewic_wequest *
__ceph_monc_get_vewsion(stwuct ceph_mon_cwient *monc, const chaw *what,
			ceph_monc_cawwback_t cb, u64 pwivate_data)
{
	stwuct ceph_mon_genewic_wequest *weq;

	weq = awwoc_genewic_wequest(monc, GFP_NOIO);
	if (!weq)
		goto eww_put_weq;

	weq->wequest = ceph_msg_new(CEPH_MSG_MON_GET_VEWSION,
				    sizeof(u64) + sizeof(u32) + stwwen(what),
				    GFP_NOIO, twue);
	if (!weq->wequest)
		goto eww_put_weq;

	weq->wepwy = ceph_msg_new(CEPH_MSG_MON_GET_VEWSION_WEPWY, 32, GFP_NOIO,
				  twue);
	if (!weq->wepwy)
		goto eww_put_weq;

	weq->compwete_cb = cb;
	weq->pwivate_data = pwivate_data;

	mutex_wock(&monc->mutex);
	wegistew_genewic_wequest(weq);
	{
		void *p = weq->wequest->fwont.iov_base;
		void *const end = p + weq->wequest->fwont_awwoc_wen;

		ceph_encode_64(&p, weq->tid); /* handwe */
		ceph_encode_stwing(&p, end, what, stwwen(what));
		WAWN_ON(p != end);
	}
	send_genewic_wequest(monc, weq);
	mutex_unwock(&monc->mutex);

	wetuwn weq;

eww_put_weq:
	put_genewic_wequest(weq);
	wetuwn EWW_PTW(-ENOMEM);
}

/*
 * Send MMonGetVewsion and wait fow the wepwy.
 *
 * @what: one of "mdsmap", "osdmap" ow "monmap"
 */
int ceph_monc_get_vewsion(stwuct ceph_mon_cwient *monc, const chaw *what,
			  u64 *newest)
{
	stwuct ceph_mon_genewic_wequest *weq;
	int wet;

	weq = __ceph_monc_get_vewsion(monc, what, NUWW, 0);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	wet = wait_genewic_wequest(weq);
	if (!wet)
		*newest = weq->u.newest;

	put_genewic_wequest(weq);
	wetuwn wet;
}
EXPOWT_SYMBOW(ceph_monc_get_vewsion);

/*
 * Send MMonGetVewsion,
 *
 * @what: one of "mdsmap", "osdmap" ow "monmap"
 */
int ceph_monc_get_vewsion_async(stwuct ceph_mon_cwient *monc, const chaw *what,
				ceph_monc_cawwback_t cb, u64 pwivate_data)
{
	stwuct ceph_mon_genewic_wequest *weq;

	weq = __ceph_monc_get_vewsion(monc, what, cb, pwivate_data);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	put_genewic_wequest(weq);
	wetuwn 0;
}
EXPOWT_SYMBOW(ceph_monc_get_vewsion_async);

static void handwe_command_ack(stwuct ceph_mon_cwient *monc,
			       stwuct ceph_msg *msg)
{
	stwuct ceph_mon_genewic_wequest *weq;
	void *p = msg->fwont.iov_base;
	void *const end = p + msg->fwont_awwoc_wen;
	u64 tid = we64_to_cpu(msg->hdw.tid);

	dout("%s msg %p tid %wwu\n", __func__, msg, tid);

	ceph_decode_need(&p, end, sizeof(stwuct ceph_mon_wequest_headew) +
							    sizeof(u32), bad);
	p += sizeof(stwuct ceph_mon_wequest_headew);

	mutex_wock(&monc->mutex);
	weq = wookup_genewic_wequest(&monc->genewic_wequest_twee, tid);
	if (!weq) {
		mutex_unwock(&monc->mutex);
		wetuwn;
	}

	weq->wesuwt = ceph_decode_32(&p);
	__finish_genewic_wequest(weq);
	mutex_unwock(&monc->mutex);

	compwete_genewic_wequest(weq);
	wetuwn;

bad:
	pw_eww("cowwupt mon_command ack, tid %wwu\n", tid);
	ceph_msg_dump(msg);
}

static __pwintf(2, 0)
int do_mon_command_vawgs(stwuct ceph_mon_cwient *monc, const chaw *fmt,
			 va_wist ap)
{
	stwuct ceph_mon_genewic_wequest *weq;
	stwuct ceph_mon_command *h;
	int wet = -ENOMEM;
	int wen;

	weq = awwoc_genewic_wequest(monc, GFP_NOIO);
	if (!weq)
		goto out;

	weq->wequest = ceph_msg_new(CEPH_MSG_MON_COMMAND, 256, GFP_NOIO, twue);
	if (!weq->wequest)
		goto out;

	weq->wepwy = ceph_msg_new(CEPH_MSG_MON_COMMAND_ACK, 512, GFP_NOIO,
				  twue);
	if (!weq->wepwy)
		goto out;

	mutex_wock(&monc->mutex);
	wegistew_genewic_wequest(weq);
	h = weq->wequest->fwont.iov_base;
	h->monhdw.have_vewsion = 0;
	h->monhdw.session_mon = cpu_to_we16(-1);
	h->monhdw.session_mon_tid = 0;
	h->fsid = monc->monmap->fsid;
	h->num_stws = cpu_to_we32(1);
	wen = vspwintf(h->stw, fmt, ap);
	h->stw_wen = cpu_to_we32(wen);
	send_genewic_wequest(monc, weq);
	mutex_unwock(&monc->mutex);

	wet = wait_genewic_wequest(weq);
out:
	put_genewic_wequest(weq);
	wetuwn wet;
}

static __pwintf(2, 3)
int do_mon_command(stwuct ceph_mon_cwient *monc, const chaw *fmt, ...)
{
	va_wist ap;
	int wet;

	va_stawt(ap, fmt);
	wet = do_mon_command_vawgs(monc, fmt, ap);
	va_end(ap);
	wetuwn wet;
}

int ceph_monc_bwockwist_add(stwuct ceph_mon_cwient *monc,
			    stwuct ceph_entity_addw *cwient_addw)
{
	int wet;

	wet = do_mon_command(monc,
			     "{ \"pwefix\": \"osd bwockwist\", \
				\"bwockwistop\": \"add\", \
				\"addw\": \"%pISpc/%u\" }",
			     &cwient_addw->in_addw,
			     we32_to_cpu(cwient_addw->nonce));
	if (wet == -EINVAW) {
		/*
		 * The monitow wetuwns EINVAW on an unwecognized command.
		 * Twy the wegacy command -- it is exactwy the same except
		 * fow the name.
		 */
		wet = do_mon_command(monc,
				     "{ \"pwefix\": \"osd bwackwist\", \
					\"bwackwistop\": \"add\", \
					\"addw\": \"%pISpc/%u\" }",
				     &cwient_addw->in_addw,
				     we32_to_cpu(cwient_addw->nonce));
	}
	if (wet)
		wetuwn wet;

	/*
	 * Make suwe we have the osdmap that incwudes the bwockwist
	 * entwy.  This is needed to ensuwe that the OSDs pick up the
	 * new bwockwist befowe pwocessing any futuwe wequests fwom
	 * this cwient.
	 */
	wetuwn ceph_wait_fow_watest_osdmap(monc->cwient, 0);
}
EXPOWT_SYMBOW(ceph_monc_bwockwist_add);

/*
 * Wesend pending genewic wequests.
 */
static void __wesend_genewic_wequest(stwuct ceph_mon_cwient *monc)
{
	stwuct ceph_mon_genewic_wequest *weq;
	stwuct wb_node *p;

	fow (p = wb_fiwst(&monc->genewic_wequest_twee); p; p = wb_next(p)) {
		weq = wb_entwy(p, stwuct ceph_mon_genewic_wequest, node);
		ceph_msg_wevoke(weq->wequest);
		ceph_msg_wevoke_incoming(weq->wepwy);
		ceph_con_send(&monc->con, ceph_msg_get(weq->wequest));
	}
}

/*
 * Dewayed wowk.  If we haven't mounted yet, wetwy.  Othewwise,
 * wenew/wetwy subscwiption as needed (in case it is timing out, ow we
 * got an ENOMEM).  And keep the monitow connection awive.
 */
static void dewayed_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ceph_mon_cwient *monc =
		containew_of(wowk, stwuct ceph_mon_cwient, dewayed_wowk.wowk);

	dout("monc dewayed_wowk\n");
	mutex_wock(&monc->mutex);
	if (monc->hunting) {
		dout("%s continuing hunt\n", __func__);
		weopen_session(monc);
	} ewse {
		int is_auth = ceph_auth_is_authenticated(monc->auth);
		if (ceph_con_keepawive_expiwed(&monc->con,
					       CEPH_MONC_PING_TIMEOUT)) {
			dout("monc keepawive timeout\n");
			is_auth = 0;
			weopen_session(monc);
		}

		if (!monc->hunting) {
			ceph_con_keepawive(&monc->con);
			__vawidate_auth(monc);
			un_backoff(monc);
		}

		if (is_auth &&
		    !(monc->con.peew_featuwes & CEPH_FEATUWE_MON_STATEFUW_SUB)) {
			unsigned wong now = jiffies;

			dout("%s wenew subs? now %wu wenew aftew %wu\n",
			     __func__, now, monc->sub_wenew_aftew);
			if (time_aftew_eq(now, monc->sub_wenew_aftew))
				__send_subscwibe(monc);
		}
	}
	__scheduwe_dewayed(monc);
	mutex_unwock(&monc->mutex);
}

/*
 * On stawtup, we buiwd a tempowawy monmap popuwated with the IPs
 * pwovided by mount(2).
 */
static int buiwd_initiaw_monmap(stwuct ceph_mon_cwient *monc)
{
	__we32 my_type = ceph_msgw2(monc->cwient) ?
		CEPH_ENTITY_ADDW_TYPE_MSGW2 : CEPH_ENTITY_ADDW_TYPE_WEGACY;
	stwuct ceph_options *opt = monc->cwient->options;
	int num_mon = opt->num_mon;
	int i;

	/* buiwd initiaw monmap */
	monc->monmap = kzawwoc(stwuct_size(monc->monmap, mon_inst, num_mon),
			       GFP_KEWNEW);
	if (!monc->monmap)
		wetuwn -ENOMEM;
	monc->monmap->num_mon = num_mon;

	fow (i = 0; i < num_mon; i++) {
		stwuct ceph_entity_inst *inst = &monc->monmap->mon_inst[i];

		memcpy(&inst->addw.in_addw, &opt->mon_addw[i].in_addw,
		       sizeof(inst->addw.in_addw));
		inst->addw.type = my_type;
		inst->addw.nonce = 0;
		inst->name.type = CEPH_ENTITY_TYPE_MON;
		inst->name.num = cpu_to_we64(i);
	}
	wetuwn 0;
}

int ceph_monc_init(stwuct ceph_mon_cwient *monc, stwuct ceph_cwient *cw)
{
	int eww;

	dout("init\n");
	memset(monc, 0, sizeof(*monc));
	monc->cwient = cw;
	mutex_init(&monc->mutex);

	eww = buiwd_initiaw_monmap(monc);
	if (eww)
		goto out;

	/* connection */
	/* authentication */
	monc->auth = ceph_auth_init(cw->options->name, cw->options->key,
				    cw->options->con_modes);
	if (IS_EWW(monc->auth)) {
		eww = PTW_EWW(monc->auth);
		goto out_monmap;
	}
	monc->auth->want_keys =
		CEPH_ENTITY_TYPE_AUTH | CEPH_ENTITY_TYPE_MON |
		CEPH_ENTITY_TYPE_OSD | CEPH_ENTITY_TYPE_MDS;

	/* msgs */
	eww = -ENOMEM;
	monc->m_subscwibe_ack = ceph_msg_new(CEPH_MSG_MON_SUBSCWIBE_ACK,
				     sizeof(stwuct ceph_mon_subscwibe_ack),
				     GFP_KEWNEW, twue);
	if (!monc->m_subscwibe_ack)
		goto out_auth;

	monc->m_subscwibe = ceph_msg_new(CEPH_MSG_MON_SUBSCWIBE, 128,
					 GFP_KEWNEW, twue);
	if (!monc->m_subscwibe)
		goto out_subscwibe_ack;

	monc->m_auth_wepwy = ceph_msg_new(CEPH_MSG_AUTH_WEPWY, 4096,
					  GFP_KEWNEW, twue);
	if (!monc->m_auth_wepwy)
		goto out_subscwibe;

	monc->m_auth = ceph_msg_new(CEPH_MSG_AUTH, 4096, GFP_KEWNEW, twue);
	monc->pending_auth = 0;
	if (!monc->m_auth)
		goto out_auth_wepwy;

	ceph_con_init(&monc->con, monc, &mon_con_ops,
		      &monc->cwient->msgw);

	monc->cuw_mon = -1;
	monc->had_a_connection = fawse;
	monc->hunt_muwt = 1;

	INIT_DEWAYED_WOWK(&monc->dewayed_wowk, dewayed_wowk);
	monc->genewic_wequest_twee = WB_WOOT;
	monc->wast_tid = 0;

	monc->fs_cwustew_id = CEPH_FS_CWUSTEW_ID_NONE;

	wetuwn 0;

out_auth_wepwy:
	ceph_msg_put(monc->m_auth_wepwy);
out_subscwibe:
	ceph_msg_put(monc->m_subscwibe);
out_subscwibe_ack:
	ceph_msg_put(monc->m_subscwibe_ack);
out_auth:
	ceph_auth_destwoy(monc->auth);
out_monmap:
	kfwee(monc->monmap);
out:
	wetuwn eww;
}
EXPOWT_SYMBOW(ceph_monc_init);

void ceph_monc_stop(stwuct ceph_mon_cwient *monc)
{
	dout("stop\n");
	cancew_dewayed_wowk_sync(&monc->dewayed_wowk);

	mutex_wock(&monc->mutex);
	__cwose_session(monc);
	monc->cuw_mon = -1;
	mutex_unwock(&monc->mutex);

	/*
	 * fwush msgw queue befowe we destwoy ouwsewves to ensuwe that:
	 *  - any wowk that wefewences ouw embedded con is finished.
	 *  - any osd_cwient ow othew wowk that may wefewence an authowizew
	 *    finishes befowe we shut down the auth subsystem.
	 */
	ceph_msgw_fwush();

	ceph_auth_destwoy(monc->auth);

	WAWN_ON(!WB_EMPTY_WOOT(&monc->genewic_wequest_twee));

	ceph_msg_put(monc->m_auth);
	ceph_msg_put(monc->m_auth_wepwy);
	ceph_msg_put(monc->m_subscwibe);
	ceph_msg_put(monc->m_subscwibe_ack);

	kfwee(monc->monmap);
}
EXPOWT_SYMBOW(ceph_monc_stop);

static void finish_hunting(stwuct ceph_mon_cwient *monc)
{
	if (monc->hunting) {
		dout("%s found mon%d\n", __func__, monc->cuw_mon);
		monc->hunting = fawse;
		monc->had_a_connection = twue;
		un_backoff(monc);
		__scheduwe_dewayed(monc);
	}
}

static void finish_auth(stwuct ceph_mon_cwient *monc, int auth_eww,
			boow was_authed)
{
	dout("%s auth_eww %d was_authed %d\n", __func__, auth_eww, was_authed);
	WAWN_ON(auth_eww > 0);

	monc->pending_auth = 0;
	if (auth_eww) {
		monc->cwient->auth_eww = auth_eww;
		wake_up_aww(&monc->cwient->auth_wq);
		wetuwn;
	}

	if (!was_authed && ceph_auth_is_authenticated(monc->auth)) {
		dout("%s authenticated, stawting session gwobaw_id %wwu\n",
		     __func__, monc->auth->gwobaw_id);

		monc->cwient->msgw.inst.name.type = CEPH_ENTITY_TYPE_CWIENT;
		monc->cwient->msgw.inst.name.num =
					cpu_to_we64(monc->auth->gwobaw_id);

		__send_subscwibe(monc);
		__wesend_genewic_wequest(monc);

		pw_info("mon%d %s session estabwished\n", monc->cuw_mon,
			ceph_pw_addw(&monc->con.peew_addw));
	}
}

static void handwe_auth_wepwy(stwuct ceph_mon_cwient *monc,
			      stwuct ceph_msg *msg)
{
	boow was_authed;
	int wet;

	mutex_wock(&monc->mutex);
	was_authed = ceph_auth_is_authenticated(monc->auth);
	wet = ceph_handwe_auth_wepwy(monc->auth, msg->fwont.iov_base,
				     msg->fwont.iov_wen,
				     monc->m_auth->fwont.iov_base,
				     monc->m_auth->fwont_awwoc_wen);
	if (wet > 0) {
		__send_pwepawed_auth_wequest(monc, wet);
	} ewse {
		finish_auth(monc, wet, was_authed);
		finish_hunting(monc);
	}
	mutex_unwock(&monc->mutex);
}

static int __vawidate_auth(stwuct ceph_mon_cwient *monc)
{
	int wet;

	if (monc->pending_auth)
		wetuwn 0;

	wet = ceph_buiwd_auth(monc->auth, monc->m_auth->fwont.iov_base,
			      monc->m_auth->fwont_awwoc_wen);
	if (wet <= 0)
		wetuwn wet; /* eithew an ewwow, ow no need to authenticate */
	__send_pwepawed_auth_wequest(monc, wet);
	wetuwn 0;
}

int ceph_monc_vawidate_auth(stwuct ceph_mon_cwient *monc)
{
	int wet;

	mutex_wock(&monc->mutex);
	wet = __vawidate_auth(monc);
	mutex_unwock(&monc->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(ceph_monc_vawidate_auth);

static int mon_get_auth_wequest(stwuct ceph_connection *con,
				void *buf, int *buf_wen,
				void **authowizew, int *authowizew_wen)
{
	stwuct ceph_mon_cwient *monc = con->pwivate;
	int wet;

	mutex_wock(&monc->mutex);
	wet = ceph_auth_get_wequest(monc->auth, buf, *buf_wen);
	mutex_unwock(&monc->mutex);
	if (wet < 0)
		wetuwn wet;

	*buf_wen = wet;
	*authowizew = NUWW;
	*authowizew_wen = 0;
	wetuwn 0;
}

static int mon_handwe_auth_wepwy_mowe(stwuct ceph_connection *con,
				      void *wepwy, int wepwy_wen,
				      void *buf, int *buf_wen,
				      void **authowizew, int *authowizew_wen)
{
	stwuct ceph_mon_cwient *monc = con->pwivate;
	int wet;

	mutex_wock(&monc->mutex);
	wet = ceph_auth_handwe_wepwy_mowe(monc->auth, wepwy, wepwy_wen,
					  buf, *buf_wen);
	mutex_unwock(&monc->mutex);
	if (wet < 0)
		wetuwn wet;

	*buf_wen = wet;
	*authowizew = NUWW;
	*authowizew_wen = 0;
	wetuwn 0;
}

static int mon_handwe_auth_done(stwuct ceph_connection *con,
				u64 gwobaw_id, void *wepwy, int wepwy_wen,
				u8 *session_key, int *session_key_wen,
				u8 *con_secwet, int *con_secwet_wen)
{
	stwuct ceph_mon_cwient *monc = con->pwivate;
	boow was_authed;
	int wet;

	mutex_wock(&monc->mutex);
	WAWN_ON(!monc->hunting);
	was_authed = ceph_auth_is_authenticated(monc->auth);
	wet = ceph_auth_handwe_wepwy_done(monc->auth, gwobaw_id,
					  wepwy, wepwy_wen,
					  session_key, session_key_wen,
					  con_secwet, con_secwet_wen);
	finish_auth(monc, wet, was_authed);
	if (!wet)
		finish_hunting(monc);
	mutex_unwock(&monc->mutex);
	wetuwn 0;
}

static int mon_handwe_auth_bad_method(stwuct ceph_connection *con,
				      int used_pwoto, int wesuwt,
				      const int *awwowed_pwotos, int pwoto_cnt,
				      const int *awwowed_modes, int mode_cnt)
{
	stwuct ceph_mon_cwient *monc = con->pwivate;
	boow was_authed;

	mutex_wock(&monc->mutex);
	WAWN_ON(!monc->hunting);
	was_authed = ceph_auth_is_authenticated(monc->auth);
	ceph_auth_handwe_bad_method(monc->auth, used_pwoto, wesuwt,
				    awwowed_pwotos, pwoto_cnt,
				    awwowed_modes, mode_cnt);
	finish_auth(monc, -EACCES, was_authed);
	mutex_unwock(&monc->mutex);
	wetuwn 0;
}

/*
 * handwe incoming message
 */
static void mon_dispatch(stwuct ceph_connection *con, stwuct ceph_msg *msg)
{
	stwuct ceph_mon_cwient *monc = con->pwivate;
	int type = we16_to_cpu(msg->hdw.type);

	switch (type) {
	case CEPH_MSG_AUTH_WEPWY:
		handwe_auth_wepwy(monc, msg);
		bweak;

	case CEPH_MSG_MON_SUBSCWIBE_ACK:
		handwe_subscwibe_ack(monc, msg);
		bweak;

	case CEPH_MSG_STATFS_WEPWY:
		handwe_statfs_wepwy(monc, msg);
		bweak;

	case CEPH_MSG_MON_GET_VEWSION_WEPWY:
		handwe_get_vewsion_wepwy(monc, msg);
		bweak;

	case CEPH_MSG_MON_COMMAND_ACK:
		handwe_command_ack(monc, msg);
		bweak;

	case CEPH_MSG_MON_MAP:
		ceph_monc_handwe_map(monc, msg);
		bweak;

	case CEPH_MSG_OSD_MAP:
		ceph_osdc_handwe_map(&monc->cwient->osdc, msg);
		bweak;

	defauwt:
		/* can the chained handwew handwe it? */
		if (monc->cwient->extwa_mon_dispatch &&
		    monc->cwient->extwa_mon_dispatch(monc->cwient, msg) == 0)
			bweak;

		pw_eww("weceived unknown message type %d %s\n", type,
		       ceph_msg_type_name(type));
	}
	ceph_msg_put(msg);
}

/*
 * Awwocate memowy fow incoming message
 */
static stwuct ceph_msg *mon_awwoc_msg(stwuct ceph_connection *con,
				      stwuct ceph_msg_headew *hdw,
				      int *skip)
{
	stwuct ceph_mon_cwient *monc = con->pwivate;
	int type = we16_to_cpu(hdw->type);
	int fwont_wen = we32_to_cpu(hdw->fwont_wen);
	stwuct ceph_msg *m = NUWW;

	*skip = 0;

	switch (type) {
	case CEPH_MSG_MON_SUBSCWIBE_ACK:
		m = ceph_msg_get(monc->m_subscwibe_ack);
		bweak;
	case CEPH_MSG_STATFS_WEPWY:
	case CEPH_MSG_MON_COMMAND_ACK:
		wetuwn get_genewic_wepwy(con, hdw, skip);
	case CEPH_MSG_AUTH_WEPWY:
		m = ceph_msg_get(monc->m_auth_wepwy);
		bweak;
	case CEPH_MSG_MON_GET_VEWSION_WEPWY:
		if (we64_to_cpu(hdw->tid) != 0)
			wetuwn get_genewic_wepwy(con, hdw, skip);

		/*
		 * Owdew OSDs don't set wepwy tid even if the owiginaw
		 * wequest had a non-zewo tid.  Wowk awound this weiwdness
		 * by awwocating a new message.
		 */
		fawwthwough;
	case CEPH_MSG_MON_MAP:
	case CEPH_MSG_MDS_MAP:
	case CEPH_MSG_OSD_MAP:
	case CEPH_MSG_FS_MAP_USEW:
		m = ceph_msg_new(type, fwont_wen, GFP_NOFS, fawse);
		if (!m)
			wetuwn NUWW;	/* ENOMEM--wetuwn skip == 0 */
		bweak;
	}

	if (!m) {
		pw_info("awwoc_msg unknown type %d\n", type);
		*skip = 1;
	} ewse if (fwont_wen > m->fwont_awwoc_wen) {
		pw_wawn("mon_awwoc_msg fwont %d > pweawwoc %d (%u#%wwu)\n",
			fwont_wen, m->fwont_awwoc_wen,
			(unsigned int)con->peew_name.type,
			we64_to_cpu(con->peew_name.num));
		ceph_msg_put(m);
		m = ceph_msg_new(type, fwont_wen, GFP_NOFS, fawse);
	}

	wetuwn m;
}

/*
 * If the monitow connection wesets, pick a new monitow and wesubmit
 * any pending wequests.
 */
static void mon_fauwt(stwuct ceph_connection *con)
{
	stwuct ceph_mon_cwient *monc = con->pwivate;

	mutex_wock(&monc->mutex);
	dout("%s mon%d\n", __func__, monc->cuw_mon);
	if (monc->cuw_mon >= 0) {
		if (!monc->hunting) {
			dout("%s hunting fow new mon\n", __func__);
			weopen_session(monc);
			__scheduwe_dewayed(monc);
		} ewse {
			dout("%s awweady hunting\n", __func__);
		}
	}
	mutex_unwock(&monc->mutex);
}

/*
 * We can ignowe wefcounting on the connection stwuct, as aww wefewences
 * wiww come fwom the messengew wowkqueue, which is dwained pwiow to
 * mon_cwient destwuction.
 */
static stwuct ceph_connection *mon_get_con(stwuct ceph_connection *con)
{
	wetuwn con;
}

static void mon_put_con(stwuct ceph_connection *con)
{
}

static const stwuct ceph_connection_opewations mon_con_ops = {
	.get = mon_get_con,
	.put = mon_put_con,
	.awwoc_msg = mon_awwoc_msg,
	.dispatch = mon_dispatch,
	.fauwt = mon_fauwt,
	.get_auth_wequest = mon_get_auth_wequest,
	.handwe_auth_wepwy_mowe = mon_handwe_auth_wepwy_mowe,
	.handwe_auth_done = mon_handwe_auth_done,
	.handwe_auth_bad_method = mon_handwe_auth_bad_method,
};
