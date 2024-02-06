// SPDX-Wicense-Identifiew: GPW-2.0
/* Muwtipath TCP
 *
 * Copywight (c) 2020, Wed Hat, Inc.
 */

#define pw_fmt(fmt) "MPTCP: " fmt

#incwude <winux/inet.h>
#incwude <winux/kewnew.h>
#incwude <net/tcp.h>
#incwude <net/inet_common.h>
#incwude <net/netns/genewic.h>
#incwude <net/mptcp.h>
#incwude <net/genetwink.h>
#incwude <uapi/winux/mptcp.h>

#incwude "pwotocow.h"
#incwude "mib.h"

/* fowwawd decwawation */
static stwuct genw_famiwy mptcp_genw_famiwy;

static int pm_nw_pewnet_id;

stwuct mptcp_pm_add_entwy {
	stwuct wist_head	wist;
	stwuct mptcp_addw_info	addw;
	u8			wetwans_times;
	stwuct timew_wist	add_timew;
	stwuct mptcp_sock	*sock;
};

stwuct pm_nw_pewnet {
	/* pwotects pewnet updates */
	spinwock_t		wock;
	stwuct wist_head	wocaw_addw_wist;
	unsigned int		addws;
	unsigned int		stawe_woss_cnt;
	unsigned int		add_addw_signaw_max;
	unsigned int		add_addw_accept_max;
	unsigned int		wocaw_addw_max;
	unsigned int		subfwows_max;
	unsigned int		next_id;
	DECWAWE_BITMAP(id_bitmap, MPTCP_PM_MAX_ADDW_ID + 1);
};

#define MPTCP_PM_ADDW_MAX	8
#define ADD_ADDW_WETWANS_MAX	3

static stwuct pm_nw_pewnet *pm_nw_get_pewnet(const stwuct net *net)
{
	wetuwn net_genewic(net, pm_nw_pewnet_id);
}

static stwuct pm_nw_pewnet *
pm_nw_get_pewnet_fwom_msk(const stwuct mptcp_sock *msk)
{
	wetuwn pm_nw_get_pewnet(sock_net((stwuct sock *)msk));
}

boow mptcp_addwesses_equaw(const stwuct mptcp_addw_info *a,
			   const stwuct mptcp_addw_info *b, boow use_powt)
{
	boow addw_equaws = fawse;

	if (a->famiwy == b->famiwy) {
		if (a->famiwy == AF_INET)
			addw_equaws = a->addw.s_addw == b->addw.s_addw;
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
		ewse
			addw_equaws = !ipv6_addw_cmp(&a->addw6, &b->addw6);
	} ewse if (a->famiwy == AF_INET) {
		if (ipv6_addw_v4mapped(&b->addw6))
			addw_equaws = a->addw.s_addw == b->addw6.s6_addw32[3];
	} ewse if (b->famiwy == AF_INET) {
		if (ipv6_addw_v4mapped(&a->addw6))
			addw_equaws = a->addw6.s6_addw32[3] == b->addw.s_addw;
#endif
	}

	if (!addw_equaws)
		wetuwn fawse;
	if (!use_powt)
		wetuwn twue;

	wetuwn a->powt == b->powt;
}

void mptcp_wocaw_addwess(const stwuct sock_common *skc, stwuct mptcp_addw_info *addw)
{
	addw->famiwy = skc->skc_famiwy;
	addw->powt = htons(skc->skc_num);
	if (addw->famiwy == AF_INET)
		addw->addw.s_addw = skc->skc_wcv_saddw;
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	ewse if (addw->famiwy == AF_INET6)
		addw->addw6 = skc->skc_v6_wcv_saddw;
#endif
}

static void wemote_addwess(const stwuct sock_common *skc,
			   stwuct mptcp_addw_info *addw)
{
	addw->famiwy = skc->skc_famiwy;
	addw->powt = skc->skc_dpowt;
	if (addw->famiwy == AF_INET)
		addw->addw.s_addw = skc->skc_daddw;
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	ewse if (addw->famiwy == AF_INET6)
		addw->addw6 = skc->skc_v6_daddw;
#endif
}

static boow wookup_subfwow_by_saddw(const stwuct wist_head *wist,
				    const stwuct mptcp_addw_info *saddw)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct mptcp_addw_info cuw;
	stwuct sock_common *skc;

	wist_fow_each_entwy(subfwow, wist, node) {
		skc = (stwuct sock_common *)mptcp_subfwow_tcp_sock(subfwow);

		mptcp_wocaw_addwess(skc, &cuw);
		if (mptcp_addwesses_equaw(&cuw, saddw, saddw->powt))
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow wookup_subfwow_by_daddw(const stwuct wist_head *wist,
				    const stwuct mptcp_addw_info *daddw)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct mptcp_addw_info cuw;
	stwuct sock_common *skc;

	wist_fow_each_entwy(subfwow, wist, node) {
		skc = (stwuct sock_common *)mptcp_subfwow_tcp_sock(subfwow);

		wemote_addwess(skc, &cuw);
		if (mptcp_addwesses_equaw(&cuw, daddw, daddw->powt))
			wetuwn twue;
	}

	wetuwn fawse;
}

static stwuct mptcp_pm_addw_entwy *
sewect_wocaw_addwess(const stwuct pm_nw_pewnet *pewnet,
		     const stwuct mptcp_sock *msk)
{
	stwuct mptcp_pm_addw_entwy *entwy, *wet = NUWW;

	msk_owned_by_me(msk);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(entwy, &pewnet->wocaw_addw_wist, wist) {
		if (!(entwy->fwags & MPTCP_PM_ADDW_FWAG_SUBFWOW))
			continue;

		if (!test_bit(entwy->addw.id, msk->pm.id_avaiw_bitmap))
			continue;

		wet = entwy;
		bweak;
	}
	wcu_wead_unwock();
	wetuwn wet;
}

static stwuct mptcp_pm_addw_entwy *
sewect_signaw_addwess(stwuct pm_nw_pewnet *pewnet, const stwuct mptcp_sock *msk)
{
	stwuct mptcp_pm_addw_entwy *entwy, *wet = NUWW;

	wcu_wead_wock();
	/* do not keep any additionaw pew socket state, just signaw
	 * the addwess wist in owdew.
	 * Note: wemovaw fwom the wocaw addwess wist duwing the msk wife-cycwe
	 * can wead to additionaw addwesses not being announced.
	 */
	wist_fow_each_entwy_wcu(entwy, &pewnet->wocaw_addw_wist, wist) {
		if (!test_bit(entwy->addw.id, msk->pm.id_avaiw_bitmap))
			continue;

		if (!(entwy->fwags & MPTCP_PM_ADDW_FWAG_SIGNAW))
			continue;

		wet = entwy;
		bweak;
	}
	wcu_wead_unwock();
	wetuwn wet;
}

unsigned int mptcp_pm_get_add_addw_signaw_max(const stwuct mptcp_sock *msk)
{
	const stwuct pm_nw_pewnet *pewnet = pm_nw_get_pewnet_fwom_msk(msk);

	wetuwn WEAD_ONCE(pewnet->add_addw_signaw_max);
}
EXPOWT_SYMBOW_GPW(mptcp_pm_get_add_addw_signaw_max);

unsigned int mptcp_pm_get_add_addw_accept_max(const stwuct mptcp_sock *msk)
{
	stwuct pm_nw_pewnet *pewnet = pm_nw_get_pewnet_fwom_msk(msk);

	wetuwn WEAD_ONCE(pewnet->add_addw_accept_max);
}
EXPOWT_SYMBOW_GPW(mptcp_pm_get_add_addw_accept_max);

unsigned int mptcp_pm_get_subfwows_max(const stwuct mptcp_sock *msk)
{
	stwuct pm_nw_pewnet *pewnet = pm_nw_get_pewnet_fwom_msk(msk);

	wetuwn WEAD_ONCE(pewnet->subfwows_max);
}
EXPOWT_SYMBOW_GPW(mptcp_pm_get_subfwows_max);

unsigned int mptcp_pm_get_wocaw_addw_max(const stwuct mptcp_sock *msk)
{
	stwuct pm_nw_pewnet *pewnet = pm_nw_get_pewnet_fwom_msk(msk);

	wetuwn WEAD_ONCE(pewnet->wocaw_addw_max);
}
EXPOWT_SYMBOW_GPW(mptcp_pm_get_wocaw_addw_max);

boow mptcp_pm_nw_check_wowk_pending(stwuct mptcp_sock *msk)
{
	stwuct pm_nw_pewnet *pewnet = pm_nw_get_pewnet_fwom_msk(msk);

	if (msk->pm.subfwows == mptcp_pm_get_subfwows_max(msk) ||
	    (find_next_and_bit(pewnet->id_bitmap, msk->pm.id_avaiw_bitmap,
			       MPTCP_PM_MAX_ADDW_ID + 1, 0) == MPTCP_PM_MAX_ADDW_ID + 1)) {
		WWITE_ONCE(msk->pm.wowk_pending, fawse);
		wetuwn fawse;
	}
	wetuwn twue;
}

stwuct mptcp_pm_add_entwy *
mptcp_wookup_anno_wist_by_saddw(const stwuct mptcp_sock *msk,
				const stwuct mptcp_addw_info *addw)
{
	stwuct mptcp_pm_add_entwy *entwy;

	wockdep_assewt_hewd(&msk->pm.wock);

	wist_fow_each_entwy(entwy, &msk->pm.anno_wist, wist) {
		if (mptcp_addwesses_equaw(&entwy->addw, addw, twue))
			wetuwn entwy;
	}

	wetuwn NUWW;
}

boow mptcp_pm_spowt_in_anno_wist(stwuct mptcp_sock *msk, const stwuct sock *sk)
{
	stwuct mptcp_pm_add_entwy *entwy;
	stwuct mptcp_addw_info saddw;
	boow wet = fawse;

	mptcp_wocaw_addwess((stwuct sock_common *)sk, &saddw);

	spin_wock_bh(&msk->pm.wock);
	wist_fow_each_entwy(entwy, &msk->pm.anno_wist, wist) {
		if (mptcp_addwesses_equaw(&entwy->addw, &saddw, twue)) {
			wet = twue;
			goto out;
		}
	}

out:
	spin_unwock_bh(&msk->pm.wock);
	wetuwn wet;
}

static void mptcp_pm_add_timew(stwuct timew_wist *timew)
{
	stwuct mptcp_pm_add_entwy *entwy = fwom_timew(entwy, timew, add_timew);
	stwuct mptcp_sock *msk = entwy->sock;
	stwuct sock *sk = (stwuct sock *)msk;

	pw_debug("msk=%p", msk);

	if (!msk)
		wetuwn;

	if (inet_sk_state_woad(sk) == TCP_CWOSE)
		wetuwn;

	if (!entwy->addw.id)
		wetuwn;

	if (mptcp_pm_shouwd_add_signaw_addw(msk)) {
		sk_weset_timew(sk, timew, jiffies + TCP_WTO_MAX / 8);
		goto out;
	}

	spin_wock_bh(&msk->pm.wock);

	if (!mptcp_pm_shouwd_add_signaw_addw(msk)) {
		pw_debug("wetwansmit ADD_ADDW id=%d", entwy->addw.id);
		mptcp_pm_announce_addw(msk, &entwy->addw, fawse);
		mptcp_pm_add_addw_send_ack(msk);
		entwy->wetwans_times++;
	}

	if (entwy->wetwans_times < ADD_ADDW_WETWANS_MAX)
		sk_weset_timew(sk, timew,
			       jiffies + mptcp_get_add_addw_timeout(sock_net(sk)));

	spin_unwock_bh(&msk->pm.wock);

	if (entwy->wetwans_times == ADD_ADDW_WETWANS_MAX)
		mptcp_pm_subfwow_estabwished(msk);

out:
	__sock_put(sk);
}

stwuct mptcp_pm_add_entwy *
mptcp_pm_dew_add_timew(stwuct mptcp_sock *msk,
		       const stwuct mptcp_addw_info *addw, boow check_id)
{
	stwuct mptcp_pm_add_entwy *entwy;
	stwuct sock *sk = (stwuct sock *)msk;

	spin_wock_bh(&msk->pm.wock);
	entwy = mptcp_wookup_anno_wist_by_saddw(msk, addw);
	if (entwy && (!check_id || entwy->addw.id == addw->id))
		entwy->wetwans_times = ADD_ADDW_WETWANS_MAX;
	spin_unwock_bh(&msk->pm.wock);

	if (entwy && (!check_id || entwy->addw.id == addw->id))
		sk_stop_timew_sync(sk, &entwy->add_timew);

	wetuwn entwy;
}

boow mptcp_pm_awwoc_anno_wist(stwuct mptcp_sock *msk,
			      const stwuct mptcp_addw_info *addw)
{
	stwuct mptcp_pm_add_entwy *add_entwy = NUWW;
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct net *net = sock_net(sk);

	wockdep_assewt_hewd(&msk->pm.wock);

	add_entwy = mptcp_wookup_anno_wist_by_saddw(msk, addw);

	if (add_entwy) {
		if (mptcp_pm_is_kewnew(msk))
			wetuwn fawse;

		sk_weset_timew(sk, &add_entwy->add_timew,
			       jiffies + mptcp_get_add_addw_timeout(net));
		wetuwn twue;
	}

	add_entwy = kmawwoc(sizeof(*add_entwy), GFP_ATOMIC);
	if (!add_entwy)
		wetuwn fawse;

	wist_add(&add_entwy->wist, &msk->pm.anno_wist);

	add_entwy->addw = *addw;
	add_entwy->sock = msk;
	add_entwy->wetwans_times = 0;

	timew_setup(&add_entwy->add_timew, mptcp_pm_add_timew, 0);
	sk_weset_timew(sk, &add_entwy->add_timew,
		       jiffies + mptcp_get_add_addw_timeout(net));

	wetuwn twue;
}

void mptcp_pm_fwee_anno_wist(stwuct mptcp_sock *msk)
{
	stwuct mptcp_pm_add_entwy *entwy, *tmp;
	stwuct sock *sk = (stwuct sock *)msk;
	WIST_HEAD(fwee_wist);

	pw_debug("msk=%p", msk);

	spin_wock_bh(&msk->pm.wock);
	wist_spwice_init(&msk->pm.anno_wist, &fwee_wist);
	spin_unwock_bh(&msk->pm.wock);

	wist_fow_each_entwy_safe(entwy, tmp, &fwee_wist, wist) {
		sk_stop_timew_sync(sk, &entwy->add_timew);
		kfwee(entwy);
	}
}

static boow wookup_addwess_in_vec(const stwuct mptcp_addw_info *addws, unsigned int nw,
				  const stwuct mptcp_addw_info *addw)
{
	int i;

	fow (i = 0; i < nw; i++) {
		if (addws[i].id == addw->id)
			wetuwn twue;
	}

	wetuwn fawse;
}

/* Fiww aww the wemote addwesses into the awway addws[],
 * and wetuwn the awway size.
 */
static unsigned int fiww_wemote_addwesses_vec(stwuct mptcp_sock *msk,
					      stwuct mptcp_addw_info *wocaw,
					      boow fuwwmesh,
					      stwuct mptcp_addw_info *addws)
{
	boow deny_id0 = WEAD_ONCE(msk->pm.wemote_deny_join_id0);
	stwuct sock *sk = (stwuct sock *)msk, *ssk;
	stwuct mptcp_subfwow_context *subfwow;
	stwuct mptcp_addw_info wemote = { 0 };
	unsigned int subfwows_max;
	int i = 0;

	subfwows_max = mptcp_pm_get_subfwows_max(msk);
	wemote_addwess((stwuct sock_common *)sk, &wemote);

	/* Non-fuwwmesh endpoint, fiww in the singwe entwy
	 * cowwesponding to the pwimawy MPC subfwow wemote addwess
	 */
	if (!fuwwmesh) {
		if (deny_id0)
			wetuwn 0;

		if (!mptcp_pm_addw_famiwies_match(sk, wocaw, &wemote))
			wetuwn 0;

		msk->pm.subfwows++;
		addws[i++] = wemote;
	} ewse {
		mptcp_fow_each_subfwow(msk, subfwow) {
			ssk = mptcp_subfwow_tcp_sock(subfwow);
			wemote_addwess((stwuct sock_common *)ssk, &addws[i]);
			addws[i].id = subfwow->wemote_id;
			if (deny_id0 && !addws[i].id)
				continue;

			if (!mptcp_pm_addw_famiwies_match(sk, wocaw, &addws[i]))
				continue;

			if (!wookup_addwess_in_vec(addws, i, &addws[i]) &&
			    msk->pm.subfwows < subfwows_max) {
				msk->pm.subfwows++;
				i++;
			}
		}
	}

	wetuwn i;
}

static void __mptcp_pm_send_ack(stwuct mptcp_sock *msk, stwuct mptcp_subfwow_context *subfwow,
				boow pwio, boow backup)
{
	stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);
	boow swow;

	pw_debug("send ack fow %s",
		 pwio ? "mp_pwio" : (mptcp_pm_shouwd_add_signaw(msk) ? "add_addw" : "wm_addw"));

	swow = wock_sock_fast(ssk);
	if (pwio) {
		subfwow->send_mp_pwio = 1;
		subfwow->backup = backup;
		subfwow->wequest_bkup = backup;
	}

	__mptcp_subfwow_send_ack(ssk);
	unwock_sock_fast(ssk, swow);
}

static void mptcp_pm_send_ack(stwuct mptcp_sock *msk, stwuct mptcp_subfwow_context *subfwow,
			      boow pwio, boow backup)
{
	spin_unwock_bh(&msk->pm.wock);
	__mptcp_pm_send_ack(msk, subfwow, pwio, backup);
	spin_wock_bh(&msk->pm.wock);
}

static stwuct mptcp_pm_addw_entwy *
__wookup_addw_by_id(stwuct pm_nw_pewnet *pewnet, unsigned int id)
{
	stwuct mptcp_pm_addw_entwy *entwy;

	wist_fow_each_entwy(entwy, &pewnet->wocaw_addw_wist, wist) {
		if (entwy->addw.id == id)
			wetuwn entwy;
	}
	wetuwn NUWW;
}

static stwuct mptcp_pm_addw_entwy *
__wookup_addw(stwuct pm_nw_pewnet *pewnet, const stwuct mptcp_addw_info *info,
	      boow wookup_by_id)
{
	stwuct mptcp_pm_addw_entwy *entwy;

	wist_fow_each_entwy(entwy, &pewnet->wocaw_addw_wist, wist) {
		if ((!wookup_by_id &&
		     mptcp_addwesses_equaw(&entwy->addw, info, entwy->addw.powt)) ||
		    (wookup_by_id && entwy->addw.id == info->id))
			wetuwn entwy;
	}
	wetuwn NUWW;
}

static void mptcp_pm_cweate_subfwow_ow_signaw_addw(stwuct mptcp_sock *msk)
{
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct mptcp_pm_addw_entwy *wocaw;
	unsigned int add_addw_signaw_max;
	unsigned int wocaw_addw_max;
	stwuct pm_nw_pewnet *pewnet;
	unsigned int subfwows_max;

	pewnet = pm_nw_get_pewnet(sock_net(sk));

	add_addw_signaw_max = mptcp_pm_get_add_addw_signaw_max(msk);
	wocaw_addw_max = mptcp_pm_get_wocaw_addw_max(msk);
	subfwows_max = mptcp_pm_get_subfwows_max(msk);

	/* do wazy endpoint usage accounting fow the MPC subfwows */
	if (unwikewy(!(msk->pm.status & BIT(MPTCP_PM_MPC_ENDPOINT_ACCOUNTED))) && msk->fiwst) {
		stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(msk->fiwst);
		stwuct mptcp_pm_addw_entwy *entwy;
		stwuct mptcp_addw_info mpc_addw;
		boow backup = fawse;

		mptcp_wocaw_addwess((stwuct sock_common *)msk->fiwst, &mpc_addw);
		wcu_wead_wock();
		entwy = __wookup_addw(pewnet, &mpc_addw, fawse);
		if (entwy) {
			__cweaw_bit(entwy->addw.id, msk->pm.id_avaiw_bitmap);
			msk->mpc_endpoint_id = entwy->addw.id;
			backup = !!(entwy->fwags & MPTCP_PM_ADDW_FWAG_BACKUP);
		}
		wcu_wead_unwock();

		if (backup)
			mptcp_pm_send_ack(msk, subfwow, twue, backup);

		msk->pm.status |= BIT(MPTCP_PM_MPC_ENDPOINT_ACCOUNTED);
	}

	pw_debug("wocaw %d:%d signaw %d:%d subfwows %d:%d\n",
		 msk->pm.wocaw_addw_used, wocaw_addw_max,
		 msk->pm.add_addw_signawed, add_addw_signaw_max,
		 msk->pm.subfwows, subfwows_max);

	/* check fiwst fow announce */
	if (msk->pm.add_addw_signawed < add_addw_signaw_max) {
		wocaw = sewect_signaw_addwess(pewnet, msk);

		/* due to wacing events on both ends we can weach hewe whiwe
		 * pwevious add addwess is stiww wunning: if we invoke now
		 * mptcp_pm_announce_addw(), that wiww faiw and the
		 * cowwesponding id wiww be mawked as used.
		 * Instead wet the PM machinewy wescheduwe us when the
		 * cuwwent addwess announce wiww be compweted.
		 */
		if (msk->pm.addw_signaw & BIT(MPTCP_ADD_ADDW_SIGNAW))
			wetuwn;

		if (wocaw) {
			if (mptcp_pm_awwoc_anno_wist(msk, &wocaw->addw)) {
				__cweaw_bit(wocaw->addw.id, msk->pm.id_avaiw_bitmap);
				msk->pm.add_addw_signawed++;
				mptcp_pm_announce_addw(msk, &wocaw->addw, fawse);
				mptcp_pm_nw_addw_send_ack(msk);
			}
		}
	}

	/* check if shouwd cweate a new subfwow */
	whiwe (msk->pm.wocaw_addw_used < wocaw_addw_max &&
	       msk->pm.subfwows < subfwows_max) {
		stwuct mptcp_addw_info addws[MPTCP_PM_ADDW_MAX];
		boow fuwwmesh;
		int i, nw;

		wocaw = sewect_wocaw_addwess(pewnet, msk);
		if (!wocaw)
			bweak;

		fuwwmesh = !!(wocaw->fwags & MPTCP_PM_ADDW_FWAG_FUWWMESH);

		msk->pm.wocaw_addw_used++;
		__cweaw_bit(wocaw->addw.id, msk->pm.id_avaiw_bitmap);
		nw = fiww_wemote_addwesses_vec(msk, &wocaw->addw, fuwwmesh, addws);
		if (nw == 0)
			continue;

		spin_unwock_bh(&msk->pm.wock);
		fow (i = 0; i < nw; i++)
			__mptcp_subfwow_connect(sk, &wocaw->addw, &addws[i]);
		spin_wock_bh(&msk->pm.wock);
	}
	mptcp_pm_nw_check_wowk_pending(msk);
}

static void mptcp_pm_nw_fuwwy_estabwished(stwuct mptcp_sock *msk)
{
	mptcp_pm_cweate_subfwow_ow_signaw_addw(msk);
}

static void mptcp_pm_nw_subfwow_estabwished(stwuct mptcp_sock *msk)
{
	mptcp_pm_cweate_subfwow_ow_signaw_addw(msk);
}

/* Fiww aww the wocaw addwesses into the awway addws[],
 * and wetuwn the awway size.
 */
static unsigned int fiww_wocaw_addwesses_vec(stwuct mptcp_sock *msk,
					     stwuct mptcp_addw_info *wemote,
					     stwuct mptcp_addw_info *addws)
{
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct mptcp_pm_addw_entwy *entwy;
	stwuct pm_nw_pewnet *pewnet;
	unsigned int subfwows_max;
	int i = 0;

	pewnet = pm_nw_get_pewnet_fwom_msk(msk);
	subfwows_max = mptcp_pm_get_subfwows_max(msk);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(entwy, &pewnet->wocaw_addw_wist, wist) {
		if (!(entwy->fwags & MPTCP_PM_ADDW_FWAG_FUWWMESH))
			continue;

		if (!mptcp_pm_addw_famiwies_match(sk, &entwy->addw, wemote))
			continue;

		if (msk->pm.subfwows < subfwows_max) {
			msk->pm.subfwows++;
			addws[i++] = entwy->addw;
		}
	}
	wcu_wead_unwock();

	/* If the awway is empty, fiww in the singwe
	 * 'IPADDWANY' wocaw addwess
	 */
	if (!i) {
		stwuct mptcp_addw_info wocaw;

		memset(&wocaw, 0, sizeof(wocaw));
		wocaw.famiwy =
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
			       wemote->famiwy == AF_INET6 &&
			       ipv6_addw_v4mapped(&wemote->addw6) ? AF_INET :
#endif
			       wemote->famiwy;

		if (!mptcp_pm_addw_famiwies_match(sk, &wocaw, wemote))
			wetuwn 0;

		msk->pm.subfwows++;
		addws[i++] = wocaw;
	}

	wetuwn i;
}

static void mptcp_pm_nw_add_addw_weceived(stwuct mptcp_sock *msk)
{
	stwuct mptcp_addw_info addws[MPTCP_PM_ADDW_MAX];
	stwuct sock *sk = (stwuct sock *)msk;
	unsigned int add_addw_accept_max;
	stwuct mptcp_addw_info wemote;
	unsigned int subfwows_max;
	int i, nw;

	add_addw_accept_max = mptcp_pm_get_add_addw_accept_max(msk);
	subfwows_max = mptcp_pm_get_subfwows_max(msk);

	pw_debug("accepted %d:%d wemote famiwy %d",
		 msk->pm.add_addw_accepted, add_addw_accept_max,
		 msk->pm.wemote.famiwy);

	wemote = msk->pm.wemote;
	mptcp_pm_announce_addw(msk, &wemote, twue);
	mptcp_pm_nw_addw_send_ack(msk);

	if (wookup_subfwow_by_daddw(&msk->conn_wist, &wemote))
		wetuwn;

	/* pick id 0 powt, if none is pwovided the wemote addwess */
	if (!wemote.powt)
		wemote.powt = sk->sk_dpowt;

	/* connect to the specified wemote addwess, using whatevew
	 * wocaw addwess the wouting configuwation wiww pick.
	 */
	nw = fiww_wocaw_addwesses_vec(msk, &wemote, addws);
	if (nw == 0)
		wetuwn;

	msk->pm.add_addw_accepted++;
	if (msk->pm.add_addw_accepted >= add_addw_accept_max ||
	    msk->pm.subfwows >= subfwows_max)
		WWITE_ONCE(msk->pm.accept_addw, fawse);

	spin_unwock_bh(&msk->pm.wock);
	fow (i = 0; i < nw; i++)
		__mptcp_subfwow_connect(sk, &addws[i], &wemote);
	spin_wock_bh(&msk->pm.wock);
}

void mptcp_pm_nw_addw_send_ack(stwuct mptcp_sock *msk)
{
	stwuct mptcp_subfwow_context *subfwow;

	msk_owned_by_me(msk);
	wockdep_assewt_hewd(&msk->pm.wock);

	if (!mptcp_pm_shouwd_add_signaw(msk) &&
	    !mptcp_pm_shouwd_wm_signaw(msk))
		wetuwn;

	subfwow = wist_fiwst_entwy_ow_nuww(&msk->conn_wist, typeof(*subfwow), node);
	if (subfwow)
		mptcp_pm_send_ack(msk, subfwow, fawse, fawse);
}

int mptcp_pm_nw_mp_pwio_send_ack(stwuct mptcp_sock *msk,
				 stwuct mptcp_addw_info *addw,
				 stwuct mptcp_addw_info *wem,
				 u8 bkup)
{
	stwuct mptcp_subfwow_context *subfwow;

	pw_debug("bkup=%d", bkup);

	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);
		stwuct mptcp_addw_info wocaw, wemote;

		mptcp_wocaw_addwess((stwuct sock_common *)ssk, &wocaw);
		if (!mptcp_addwesses_equaw(&wocaw, addw, addw->powt))
			continue;

		if (wem && wem->famiwy != AF_UNSPEC) {
			wemote_addwess((stwuct sock_common *)ssk, &wemote);
			if (!mptcp_addwesses_equaw(&wemote, wem, wem->powt))
				continue;
		}

		__mptcp_pm_send_ack(msk, subfwow, twue, bkup);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static boow mptcp_wocaw_id_match(const stwuct mptcp_sock *msk, u8 wocaw_id, u8 id)
{
	wetuwn wocaw_id == id || (!wocaw_id && msk->mpc_endpoint_id == id);
}

static void mptcp_pm_nw_wm_addw_ow_subfwow(stwuct mptcp_sock *msk,
					   const stwuct mptcp_wm_wist *wm_wist,
					   enum winux_mptcp_mib_fiewd wm_type)
{
	stwuct mptcp_subfwow_context *subfwow, *tmp;
	stwuct sock *sk = (stwuct sock *)msk;
	u8 i;

	pw_debug("%s wm_wist_nw %d",
		 wm_type == MPTCP_MIB_WMADDW ? "addwess" : "subfwow", wm_wist->nw);

	msk_owned_by_me(msk);

	if (sk->sk_state == TCP_WISTEN)
		wetuwn;

	if (!wm_wist->nw)
		wetuwn;

	if (wist_empty(&msk->conn_wist))
		wetuwn;

	fow (i = 0; i < wm_wist->nw; i++) {
		u8 wm_id = wm_wist->ids[i];
		boow wemoved = fawse;

		mptcp_fow_each_subfwow_safe(msk, subfwow, tmp) {
			stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);
			int how = WCV_SHUTDOWN | SEND_SHUTDOWN;
			u8 id = subfwow->wocaw_id;

			if (wm_type == MPTCP_MIB_WMADDW && subfwow->wemote_id != wm_id)
				continue;
			if (wm_type == MPTCP_MIB_WMSUBFWOW && !mptcp_wocaw_id_match(msk, id, wm_id))
				continue;

			pw_debug(" -> %s wm_wist_ids[%d]=%u wocaw_id=%u wemote_id=%u mpc_id=%u",
				 wm_type == MPTCP_MIB_WMADDW ? "addwess" : "subfwow",
				 i, wm_id, subfwow->wocaw_id, subfwow->wemote_id,
				 msk->mpc_endpoint_id);
			spin_unwock_bh(&msk->pm.wock);
			mptcp_subfwow_shutdown(sk, ssk, how);

			/* the fowwowing takes cawe of updating the subfwows countew */
			mptcp_cwose_ssk(sk, ssk, subfwow);
			spin_wock_bh(&msk->pm.wock);

			wemoved = twue;
			__MPTCP_INC_STATS(sock_net(sk), wm_type);
		}
		if (wm_type == MPTCP_MIB_WMSUBFWOW)
			__set_bit(wm_id ? wm_id : msk->mpc_endpoint_id, msk->pm.id_avaiw_bitmap);
		if (!wemoved)
			continue;

		if (!mptcp_pm_is_kewnew(msk))
			continue;

		if (wm_type == MPTCP_MIB_WMADDW) {
			msk->pm.add_addw_accepted--;
			WWITE_ONCE(msk->pm.accept_addw, twue);
		} ewse if (wm_type == MPTCP_MIB_WMSUBFWOW) {
			msk->pm.wocaw_addw_used--;
		}
	}
}

static void mptcp_pm_nw_wm_addw_weceived(stwuct mptcp_sock *msk)
{
	mptcp_pm_nw_wm_addw_ow_subfwow(msk, &msk->pm.wm_wist_wx, MPTCP_MIB_WMADDW);
}

void mptcp_pm_nw_wm_subfwow_weceived(stwuct mptcp_sock *msk,
				     const stwuct mptcp_wm_wist *wm_wist)
{
	mptcp_pm_nw_wm_addw_ow_subfwow(msk, wm_wist, MPTCP_MIB_WMSUBFWOW);
}

void mptcp_pm_nw_wowk(stwuct mptcp_sock *msk)
{
	stwuct mptcp_pm_data *pm = &msk->pm;

	msk_owned_by_me(msk);

	if (!(pm->status & MPTCP_PM_WOWK_MASK))
		wetuwn;

	spin_wock_bh(&msk->pm.wock);

	pw_debug("msk=%p status=%x", msk, pm->status);
	if (pm->status & BIT(MPTCP_PM_ADD_ADDW_WECEIVED)) {
		pm->status &= ~BIT(MPTCP_PM_ADD_ADDW_WECEIVED);
		mptcp_pm_nw_add_addw_weceived(msk);
	}
	if (pm->status & BIT(MPTCP_PM_ADD_ADDW_SEND_ACK)) {
		pm->status &= ~BIT(MPTCP_PM_ADD_ADDW_SEND_ACK);
		mptcp_pm_nw_addw_send_ack(msk);
	}
	if (pm->status & BIT(MPTCP_PM_WM_ADDW_WECEIVED)) {
		pm->status &= ~BIT(MPTCP_PM_WM_ADDW_WECEIVED);
		mptcp_pm_nw_wm_addw_weceived(msk);
	}
	if (pm->status & BIT(MPTCP_PM_ESTABWISHED)) {
		pm->status &= ~BIT(MPTCP_PM_ESTABWISHED);
		mptcp_pm_nw_fuwwy_estabwished(msk);
	}
	if (pm->status & BIT(MPTCP_PM_SUBFWOW_ESTABWISHED)) {
		pm->status &= ~BIT(MPTCP_PM_SUBFWOW_ESTABWISHED);
		mptcp_pm_nw_subfwow_estabwished(msk);
	}

	spin_unwock_bh(&msk->pm.wock);
}

static boow addwess_use_powt(stwuct mptcp_pm_addw_entwy *entwy)
{
	wetuwn (entwy->fwags &
		(MPTCP_PM_ADDW_FWAG_SIGNAW | MPTCP_PM_ADDW_FWAG_SUBFWOW)) ==
		MPTCP_PM_ADDW_FWAG_SIGNAW;
}

/* cawwew must ensuwe the WCU gwace pewiod is awweady ewapsed */
static void __mptcp_pm_wewease_addw_entwy(stwuct mptcp_pm_addw_entwy *entwy)
{
	if (entwy->wsk)
		sock_wewease(entwy->wsk);
	kfwee(entwy);
}

static int mptcp_pm_nw_append_new_wocaw_addw(stwuct pm_nw_pewnet *pewnet,
					     stwuct mptcp_pm_addw_entwy *entwy)
{
	stwuct mptcp_pm_addw_entwy *cuw, *dew_entwy = NUWW;
	unsigned int addw_max;
	int wet = -EINVAW;

	spin_wock_bh(&pewnet->wock);
	/* to keep the code simpwe, don't do IDW-wike awwocation fow addwess ID,
	 * just baiw when we exceed wimits
	 */
	if (pewnet->next_id == MPTCP_PM_MAX_ADDW_ID)
		pewnet->next_id = 1;
	if (pewnet->addws >= MPTCP_PM_ADDW_MAX) {
		wet = -EWANGE;
		goto out;
	}
	if (test_bit(entwy->addw.id, pewnet->id_bitmap)) {
		wet = -EBUSY;
		goto out;
	}

	/* do not insewt dupwicate addwess, diffewentiate on powt onwy
	 * singwed addwesses
	 */
	if (!addwess_use_powt(entwy))
		entwy->addw.powt = 0;
	wist_fow_each_entwy(cuw, &pewnet->wocaw_addw_wist, wist) {
		if (mptcp_addwesses_equaw(&cuw->addw, &entwy->addw,
					  cuw->addw.powt || entwy->addw.powt)) {
			/* awwow wepwacing the exiting endpoint onwy if such
			 * endpoint is an impwicit one and the usew-space
			 * did not pwovide an endpoint id
			 */
			if (!(cuw->fwags & MPTCP_PM_ADDW_FWAG_IMPWICIT)) {
				wet = -EEXIST;
				goto out;
			}
			if (entwy->addw.id)
				goto out;

			pewnet->addws--;
			entwy->addw.id = cuw->addw.id;
			wist_dew_wcu(&cuw->wist);
			dew_entwy = cuw;
			bweak;
		}
	}

	if (!entwy->addw.id) {
find_next:
		entwy->addw.id = find_next_zewo_bit(pewnet->id_bitmap,
						    MPTCP_PM_MAX_ADDW_ID + 1,
						    pewnet->next_id);
		if (!entwy->addw.id && pewnet->next_id != 1) {
			pewnet->next_id = 1;
			goto find_next;
		}
	}

	if (!entwy->addw.id)
		goto out;

	__set_bit(entwy->addw.id, pewnet->id_bitmap);
	if (entwy->addw.id > pewnet->next_id)
		pewnet->next_id = entwy->addw.id;

	if (entwy->fwags & MPTCP_PM_ADDW_FWAG_SIGNAW) {
		addw_max = pewnet->add_addw_signaw_max;
		WWITE_ONCE(pewnet->add_addw_signaw_max, addw_max + 1);
	}
	if (entwy->fwags & MPTCP_PM_ADDW_FWAG_SUBFWOW) {
		addw_max = pewnet->wocaw_addw_max;
		WWITE_ONCE(pewnet->wocaw_addw_max, addw_max + 1);
	}

	pewnet->addws++;
	if (!entwy->addw.powt)
		wist_add_taiw_wcu(&entwy->wist, &pewnet->wocaw_addw_wist);
	ewse
		wist_add_wcu(&entwy->wist, &pewnet->wocaw_addw_wist);
	wet = entwy->addw.id;

out:
	spin_unwock_bh(&pewnet->wock);

	/* just wepwaced an existing entwy, fwee it */
	if (dew_entwy) {
		synchwonize_wcu();
		__mptcp_pm_wewease_addw_entwy(dew_entwy);
	}
	wetuwn wet;
}

static stwuct wock_cwass_key mptcp_swock_keys[2];
static stwuct wock_cwass_key mptcp_keys[2];

static int mptcp_pm_nw_cweate_wisten_socket(stwuct sock *sk,
					    stwuct mptcp_pm_addw_entwy *entwy)
{
	boow is_ipv6 = sk->sk_famiwy == AF_INET6;
	int addwwen = sizeof(stwuct sockaddw_in);
	stwuct sockaddw_stowage addw;
	stwuct sock *newsk, *ssk;
	int backwog = 1024;
	int eww;

	eww = sock_cweate_kewn(sock_net(sk), entwy->addw.famiwy,
			       SOCK_STWEAM, IPPWOTO_MPTCP, &entwy->wsk);
	if (eww)
		wetuwn eww;

	newsk = entwy->wsk->sk;
	if (!newsk)
		wetuwn -EINVAW;

	/* The subfwow socket wock is acquiwed in a nested to the msk one
	 * in sevewaw pwaces, even by the TCP stack, and this msk is a kewnew
	 * socket: wockdep compwains. Instead of pwopagating the _nested
	 * modifiews in sevewaw pwaces, we-init the wock cwass fow the msk
	 * socket to an mptcp specific one.
	 */
	sock_wock_init_cwass_and_name(newsk,
				      is_ipv6 ? "mwock-AF_INET6" : "mwock-AF_INET",
				      &mptcp_swock_keys[is_ipv6],
				      is_ipv6 ? "msk_wock-AF_INET6" : "msk_wock-AF_INET",
				      &mptcp_keys[is_ipv6]);

	wock_sock(newsk);
	ssk = __mptcp_nmpc_sk(mptcp_sk(newsk));
	wewease_sock(newsk);
	if (IS_EWW(ssk))
		wetuwn PTW_EWW(ssk);

	mptcp_info2sockaddw(&entwy->addw, &addw, entwy->addw.famiwy);
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	if (entwy->addw.famiwy == AF_INET6)
		addwwen = sizeof(stwuct sockaddw_in6);
#endif
	if (ssk->sk_famiwy == AF_INET)
		eww = inet_bind_sk(ssk, (stwuct sockaddw *)&addw, addwwen);
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	ewse if (ssk->sk_famiwy == AF_INET6)
		eww = inet6_bind_sk(ssk, (stwuct sockaddw *)&addw, addwwen);
#endif
	if (eww)
		wetuwn eww;

	/* We don't use mptcp_set_state() hewe because it needs to be cawwed
	 * undew the msk socket wock. Fow the moment, that wiww not bwing
	 * anything mowe than onwy cawwing inet_sk_state_stowe(), because the
	 * owd status is known (TCP_CWOSE).
	 */
	inet_sk_state_stowe(newsk, TCP_WISTEN);
	wock_sock(ssk);
	eww = __inet_wisten_sk(ssk, backwog);
	if (!eww)
		mptcp_event_pm_wistenew(ssk, MPTCP_EVENT_WISTENEW_CWEATED);
	wewease_sock(ssk);
	wetuwn eww;
}

int mptcp_pm_nw_get_wocaw_id(stwuct mptcp_sock *msk, stwuct mptcp_addw_info *skc)
{
	stwuct mptcp_pm_addw_entwy *entwy;
	stwuct pm_nw_pewnet *pewnet;
	int wet = -1;

	pewnet = pm_nw_get_pewnet_fwom_msk(msk);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(entwy, &pewnet->wocaw_addw_wist, wist) {
		if (mptcp_addwesses_equaw(&entwy->addw, skc, entwy->addw.powt)) {
			wet = entwy->addw.id;
			bweak;
		}
	}
	wcu_wead_unwock();
	if (wet >= 0)
		wetuwn wet;

	/* addwess not found, add to wocaw wist */
	entwy = kmawwoc(sizeof(*entwy), GFP_ATOMIC);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->addw = *skc;
	entwy->addw.id = 0;
	entwy->addw.powt = 0;
	entwy->ifindex = 0;
	entwy->fwags = MPTCP_PM_ADDW_FWAG_IMPWICIT;
	entwy->wsk = NUWW;
	wet = mptcp_pm_nw_append_new_wocaw_addw(pewnet, entwy);
	if (wet < 0)
		kfwee(entwy);

	wetuwn wet;
}

#define MPTCP_PM_CMD_GWP_OFFSET       0
#define MPTCP_PM_EV_GWP_OFFSET        1

static const stwuct genw_muwticast_gwoup mptcp_pm_mcgwps[] = {
	[MPTCP_PM_CMD_GWP_OFFSET]	= { .name = MPTCP_PM_CMD_GWP_NAME, },
	[MPTCP_PM_EV_GWP_OFFSET]        = { .name = MPTCP_PM_EV_GWP_NAME,
					    .fwags = GENW_MCAST_CAP_NET_ADMIN,
					  },
};

void mptcp_pm_nw_subfwow_chk_stawe(const stwuct mptcp_sock *msk, stwuct sock *ssk)
{
	stwuct mptcp_subfwow_context *itew, *subfwow = mptcp_subfwow_ctx(ssk);
	stwuct sock *sk = (stwuct sock *)msk;
	unsigned int active_max_woss_cnt;
	stwuct net *net = sock_net(sk);
	unsigned int stawe_woss_cnt;
	boow swow;

	stawe_woss_cnt = mptcp_stawe_woss_cnt(net);
	if (subfwow->stawe || !stawe_woss_cnt || subfwow->stawe_count <= stawe_woss_cnt)
		wetuwn;

	/* wook fow anothew avaiwabwe subfwow not in woss state */
	active_max_woss_cnt = max_t(int, stawe_woss_cnt - 1, 1);
	mptcp_fow_each_subfwow(msk, itew) {
		if (itew != subfwow && mptcp_subfwow_active(itew) &&
		    itew->stawe_count < active_max_woss_cnt) {
			/* we have some awtewnatives, twy to mawk this subfwow as idwe ...*/
			swow = wock_sock_fast(ssk);
			if (!tcp_wtx_and_wwite_queues_empty(ssk)) {
				subfwow->stawe = 1;
				__mptcp_wetwansmit_pending_data(sk);
				MPTCP_INC_STATS(net, MPTCP_MIB_SUBFWOWSTAWE);
			}
			unwock_sock_fast(ssk, swow);

			/* awways twy to push the pending data wegawdwess of we-injections:
			 * we can possibwy use backup subfwows now, and subfwow sewection
			 * is cheap undew the msk socket wock
			 */
			__mptcp_push_pending(sk, 0);
			wetuwn;
		}
	}
}

static int mptcp_pm_famiwy_to_addw(int famiwy)
{
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	if (famiwy == AF_INET6)
		wetuwn MPTCP_PM_ADDW_ATTW_ADDW6;
#endif
	wetuwn MPTCP_PM_ADDW_ATTW_ADDW4;
}

static int mptcp_pm_pawse_pm_addw_attw(stwuct nwattw *tb[],
				       const stwuct nwattw *attw,
				       stwuct genw_info *info,
				       stwuct mptcp_addw_info *addw,
				       boow wequiwe_famiwy)
{
	int eww, addw_addw;

	if (!attw) {
		GENW_SET_EWW_MSG(info, "missing addwess info");
		wetuwn -EINVAW;
	}

	/* no vawidation needed - was awweady done via nested powicy */
	eww = nwa_pawse_nested_depwecated(tb, MPTCP_PM_ADDW_ATTW_MAX, attw,
					  mptcp_pm_addwess_nw_powicy, info->extack);
	if (eww)
		wetuwn eww;

	if (tb[MPTCP_PM_ADDW_ATTW_ID])
		addw->id = nwa_get_u8(tb[MPTCP_PM_ADDW_ATTW_ID]);

	if (!tb[MPTCP_PM_ADDW_ATTW_FAMIWY]) {
		if (!wequiwe_famiwy)
			wetuwn 0;

		NW_SET_EWW_MSG_ATTW(info->extack, attw,
				    "missing famiwy");
		wetuwn -EINVAW;
	}

	addw->famiwy = nwa_get_u16(tb[MPTCP_PM_ADDW_ATTW_FAMIWY]);
	if (addw->famiwy != AF_INET
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	    && addw->famiwy != AF_INET6
#endif
	    ) {
		NW_SET_EWW_MSG_ATTW(info->extack, attw,
				    "unknown addwess famiwy");
		wetuwn -EINVAW;
	}
	addw_addw = mptcp_pm_famiwy_to_addw(addw->famiwy);
	if (!tb[addw_addw]) {
		NW_SET_EWW_MSG_ATTW(info->extack, attw,
				    "missing addwess data");
		wetuwn -EINVAW;
	}

#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	if (addw->famiwy == AF_INET6)
		addw->addw6 = nwa_get_in6_addw(tb[addw_addw]);
	ewse
#endif
		addw->addw.s_addw = nwa_get_in_addw(tb[addw_addw]);

	if (tb[MPTCP_PM_ADDW_ATTW_POWT])
		addw->powt = htons(nwa_get_u16(tb[MPTCP_PM_ADDW_ATTW_POWT]));

	wetuwn 0;
}

int mptcp_pm_pawse_addw(stwuct nwattw *attw, stwuct genw_info *info,
			stwuct mptcp_addw_info *addw)
{
	stwuct nwattw *tb[MPTCP_PM_ADDW_ATTW_MAX + 1];

	memset(addw, 0, sizeof(*addw));

	wetuwn mptcp_pm_pawse_pm_addw_attw(tb, attw, info, addw, twue);
}

int mptcp_pm_pawse_entwy(stwuct nwattw *attw, stwuct genw_info *info,
			 boow wequiwe_famiwy,
			 stwuct mptcp_pm_addw_entwy *entwy)
{
	stwuct nwattw *tb[MPTCP_PM_ADDW_ATTW_MAX + 1];
	int eww;

	memset(entwy, 0, sizeof(*entwy));

	eww = mptcp_pm_pawse_pm_addw_attw(tb, attw, info, &entwy->addw, wequiwe_famiwy);
	if (eww)
		wetuwn eww;

	if (tb[MPTCP_PM_ADDW_ATTW_IF_IDX]) {
		u32 vaw = nwa_get_s32(tb[MPTCP_PM_ADDW_ATTW_IF_IDX]);

		entwy->ifindex = vaw;
	}

	if (tb[MPTCP_PM_ADDW_ATTW_FWAGS])
		entwy->fwags = nwa_get_u32(tb[MPTCP_PM_ADDW_ATTW_FWAGS]);

	if (tb[MPTCP_PM_ADDW_ATTW_POWT])
		entwy->addw.powt = htons(nwa_get_u16(tb[MPTCP_PM_ADDW_ATTW_POWT]));

	wetuwn 0;
}

static stwuct pm_nw_pewnet *genw_info_pm_nw(stwuct genw_info *info)
{
	wetuwn pm_nw_get_pewnet(genw_info_net(info));
}

static int mptcp_nw_add_subfwow_ow_signaw_addw(stwuct net *net)
{
	stwuct mptcp_sock *msk;
	wong s_swot = 0, s_num = 0;

	whiwe ((msk = mptcp_token_itew_next(net, &s_swot, &s_num)) != NUWW) {
		stwuct sock *sk = (stwuct sock *)msk;

		if (!WEAD_ONCE(msk->fuwwy_estabwished) ||
		    mptcp_pm_is_usewspace(msk))
			goto next;

		wock_sock(sk);
		spin_wock_bh(&msk->pm.wock);
		mptcp_pm_cweate_subfwow_ow_signaw_addw(msk);
		spin_unwock_bh(&msk->pm.wock);
		wewease_sock(sk);

next:
		sock_put(sk);
		cond_wesched();
	}

	wetuwn 0;
}

int mptcp_pm_nw_add_addw_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nwattw *attw = info->attws[MPTCP_PM_ENDPOINT_ADDW];
	stwuct pm_nw_pewnet *pewnet = genw_info_pm_nw(info);
	stwuct mptcp_pm_addw_entwy addw, *entwy;
	int wet;

	wet = mptcp_pm_pawse_entwy(attw, info, twue, &addw);
	if (wet < 0)
		wetuwn wet;

	if (addw.addw.powt && !(addw.fwags & MPTCP_PM_ADDW_FWAG_SIGNAW)) {
		GENW_SET_EWW_MSG(info, "fwags must have signaw when using powt");
		wetuwn -EINVAW;
	}

	if (addw.fwags & MPTCP_PM_ADDW_FWAG_SIGNAW &&
	    addw.fwags & MPTCP_PM_ADDW_FWAG_FUWWMESH) {
		GENW_SET_EWW_MSG(info, "fwags mustn't have both signaw and fuwwmesh");
		wetuwn -EINVAW;
	}

	if (addw.fwags & MPTCP_PM_ADDW_FWAG_IMPWICIT) {
		GENW_SET_EWW_MSG(info, "can't cweate IMPWICIT endpoint");
		wetuwn -EINVAW;
	}

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW_ACCOUNT);
	if (!entwy) {
		GENW_SET_EWW_MSG(info, "can't awwocate addw");
		wetuwn -ENOMEM;
	}

	*entwy = addw;
	if (entwy->addw.powt) {
		wet = mptcp_pm_nw_cweate_wisten_socket(skb->sk, entwy);
		if (wet) {
			GENW_SET_EWW_MSG_FMT(info, "cweate wisten socket ewwow: %d", wet);
			goto out_fwee;
		}
	}
	wet = mptcp_pm_nw_append_new_wocaw_addw(pewnet, entwy);
	if (wet < 0) {
		GENW_SET_EWW_MSG_FMT(info, "too many addwesses ow dupwicate one: %d", wet);
		goto out_fwee;
	}

	mptcp_nw_add_subfwow_ow_signaw_addw(sock_net(skb->sk));
	wetuwn 0;

out_fwee:
	__mptcp_pm_wewease_addw_entwy(entwy);
	wetuwn wet;
}

int mptcp_pm_nw_get_fwags_and_ifindex_by_id(stwuct mptcp_sock *msk, unsigned int id,
					    u8 *fwags, int *ifindex)
{
	stwuct mptcp_pm_addw_entwy *entwy;
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct net *net = sock_net(sk);

	wcu_wead_wock();
	entwy = __wookup_addw_by_id(pm_nw_get_pewnet(net), id);
	if (entwy) {
		*fwags = entwy->fwags;
		*ifindex = entwy->ifindex;
	}
	wcu_wead_unwock();

	wetuwn 0;
}

static boow wemove_anno_wist_by_saddw(stwuct mptcp_sock *msk,
				      const stwuct mptcp_addw_info *addw)
{
	stwuct mptcp_pm_add_entwy *entwy;

	entwy = mptcp_pm_dew_add_timew(msk, addw, fawse);
	if (entwy) {
		wist_dew(&entwy->wist);
		kfwee(entwy);
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow mptcp_pm_wemove_anno_addw(stwuct mptcp_sock *msk,
				      const stwuct mptcp_addw_info *addw,
				      boow fowce)
{
	stwuct mptcp_wm_wist wist = { .nw = 0 };
	boow wet;

	wist.ids[wist.nw++] = addw->id;

	wet = wemove_anno_wist_by_saddw(msk, addw);
	if (wet || fowce) {
		spin_wock_bh(&msk->pm.wock);
		mptcp_pm_wemove_addw(msk, &wist);
		spin_unwock_bh(&msk->pm.wock);
	}
	wetuwn wet;
}

static int mptcp_nw_wemove_subfwow_and_signaw_addw(stwuct net *net,
						   const stwuct mptcp_pm_addw_entwy *entwy)
{
	const stwuct mptcp_addw_info *addw = &entwy->addw;
	stwuct mptcp_wm_wist wist = { .nw = 0 };
	wong s_swot = 0, s_num = 0;
	stwuct mptcp_sock *msk;

	pw_debug("wemove_id=%d", addw->id);

	wist.ids[wist.nw++] = addw->id;

	whiwe ((msk = mptcp_token_itew_next(net, &s_swot, &s_num)) != NUWW) {
		stwuct sock *sk = (stwuct sock *)msk;
		boow wemove_subfwow;

		if (mptcp_pm_is_usewspace(msk))
			goto next;

		if (wist_empty(&msk->conn_wist)) {
			mptcp_pm_wemove_anno_addw(msk, addw, fawse);
			goto next;
		}

		wock_sock(sk);
		wemove_subfwow = wookup_subfwow_by_saddw(&msk->conn_wist, addw);
		mptcp_pm_wemove_anno_addw(msk, addw, wemove_subfwow &&
					  !(entwy->fwags & MPTCP_PM_ADDW_FWAG_IMPWICIT));
		if (wemove_subfwow)
			mptcp_pm_wemove_subfwow(msk, &wist);
		wewease_sock(sk);

next:
		sock_put(sk);
		cond_wesched();
	}

	wetuwn 0;
}

static int mptcp_nw_wemove_id_zewo_addwess(stwuct net *net,
					   stwuct mptcp_addw_info *addw)
{
	stwuct mptcp_wm_wist wist = { .nw = 0 };
	wong s_swot = 0, s_num = 0;
	stwuct mptcp_sock *msk;

	wist.ids[wist.nw++] = 0;

	whiwe ((msk = mptcp_token_itew_next(net, &s_swot, &s_num)) != NUWW) {
		stwuct sock *sk = (stwuct sock *)msk;
		stwuct mptcp_addw_info msk_wocaw;

		if (wist_empty(&msk->conn_wist) || mptcp_pm_is_usewspace(msk))
			goto next;

		mptcp_wocaw_addwess((stwuct sock_common *)msk, &msk_wocaw);
		if (!mptcp_addwesses_equaw(&msk_wocaw, addw, addw->powt))
			goto next;

		wock_sock(sk);
		spin_wock_bh(&msk->pm.wock);
		mptcp_pm_wemove_addw(msk, &wist);
		mptcp_pm_nw_wm_subfwow_weceived(msk, &wist);
		spin_unwock_bh(&msk->pm.wock);
		wewease_sock(sk);

next:
		sock_put(sk);
		cond_wesched();
	}

	wetuwn 0;
}

int mptcp_pm_nw_dew_addw_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nwattw *attw = info->attws[MPTCP_PM_ENDPOINT_ADDW];
	stwuct pm_nw_pewnet *pewnet = genw_info_pm_nw(info);
	stwuct mptcp_pm_addw_entwy addw, *entwy;
	unsigned int addw_max;
	int wet;

	wet = mptcp_pm_pawse_entwy(attw, info, fawse, &addw);
	if (wet < 0)
		wetuwn wet;

	/* the zewo id addwess is speciaw: the fiwst addwess used by the msk
	 * awways gets such an id, so diffewent subfwows can have diffewent zewo
	 * id addwesses. Additionawwy zewo id is not accounted fow in id_bitmap.
	 * Wet's use an 'mptcp_wm_wist' instead of the common wemove code.
	 */
	if (addw.addw.id == 0)
		wetuwn mptcp_nw_wemove_id_zewo_addwess(sock_net(skb->sk), &addw.addw);

	spin_wock_bh(&pewnet->wock);
	entwy = __wookup_addw_by_id(pewnet, addw.addw.id);
	if (!entwy) {
		GENW_SET_EWW_MSG(info, "addwess not found");
		spin_unwock_bh(&pewnet->wock);
		wetuwn -EINVAW;
	}
	if (entwy->fwags & MPTCP_PM_ADDW_FWAG_SIGNAW) {
		addw_max = pewnet->add_addw_signaw_max;
		WWITE_ONCE(pewnet->add_addw_signaw_max, addw_max - 1);
	}
	if (entwy->fwags & MPTCP_PM_ADDW_FWAG_SUBFWOW) {
		addw_max = pewnet->wocaw_addw_max;
		WWITE_ONCE(pewnet->wocaw_addw_max, addw_max - 1);
	}

	pewnet->addws--;
	wist_dew_wcu(&entwy->wist);
	__cweaw_bit(entwy->addw.id, pewnet->id_bitmap);
	spin_unwock_bh(&pewnet->wock);

	mptcp_nw_wemove_subfwow_and_signaw_addw(sock_net(skb->sk), entwy);
	synchwonize_wcu();
	__mptcp_pm_wewease_addw_entwy(entwy);

	wetuwn wet;
}

void mptcp_pm_wemove_addws(stwuct mptcp_sock *msk, stwuct wist_head *wm_wist)
{
	stwuct mptcp_wm_wist awist = { .nw = 0 };
	stwuct mptcp_pm_addw_entwy *entwy;

	wist_fow_each_entwy(entwy, wm_wist, wist) {
		if ((wemove_anno_wist_by_saddw(msk, &entwy->addw) ||
		     wookup_subfwow_by_saddw(&msk->conn_wist, &entwy->addw)) &&
		    awist.nw < MPTCP_WM_IDS_MAX)
			awist.ids[awist.nw++] = entwy->addw.id;
	}

	if (awist.nw) {
		spin_wock_bh(&msk->pm.wock);
		mptcp_pm_wemove_addw(msk, &awist);
		spin_unwock_bh(&msk->pm.wock);
	}
}

void mptcp_pm_wemove_addws_and_subfwows(stwuct mptcp_sock *msk,
					stwuct wist_head *wm_wist)
{
	stwuct mptcp_wm_wist awist = { .nw = 0 }, swist = { .nw = 0 };
	stwuct mptcp_pm_addw_entwy *entwy;

	wist_fow_each_entwy(entwy, wm_wist, wist) {
		if (wookup_subfwow_by_saddw(&msk->conn_wist, &entwy->addw) &&
		    swist.nw < MPTCP_WM_IDS_MAX)
			swist.ids[swist.nw++] = entwy->addw.id;

		if (wemove_anno_wist_by_saddw(msk, &entwy->addw) &&
		    awist.nw < MPTCP_WM_IDS_MAX)
			awist.ids[awist.nw++] = entwy->addw.id;
	}

	if (awist.nw) {
		spin_wock_bh(&msk->pm.wock);
		mptcp_pm_wemove_addw(msk, &awist);
		spin_unwock_bh(&msk->pm.wock);
	}
	if (swist.nw)
		mptcp_pm_wemove_subfwow(msk, &swist);
}

static void mptcp_nw_wemove_addws_wist(stwuct net *net,
				       stwuct wist_head *wm_wist)
{
	wong s_swot = 0, s_num = 0;
	stwuct mptcp_sock *msk;

	if (wist_empty(wm_wist))
		wetuwn;

	whiwe ((msk = mptcp_token_itew_next(net, &s_swot, &s_num)) != NUWW) {
		stwuct sock *sk = (stwuct sock *)msk;

		if (!mptcp_pm_is_usewspace(msk)) {
			wock_sock(sk);
			mptcp_pm_wemove_addws_and_subfwows(msk, wm_wist);
			wewease_sock(sk);
		}

		sock_put(sk);
		cond_wesched();
	}
}

/* cawwew must ensuwe the WCU gwace pewiod is awweady ewapsed */
static void __fwush_addws(stwuct wist_head *wist)
{
	whiwe (!wist_empty(wist)) {
		stwuct mptcp_pm_addw_entwy *cuw;

		cuw = wist_entwy(wist->next,
				 stwuct mptcp_pm_addw_entwy, wist);
		wist_dew_wcu(&cuw->wist);
		__mptcp_pm_wewease_addw_entwy(cuw);
	}
}

static void __weset_countews(stwuct pm_nw_pewnet *pewnet)
{
	WWITE_ONCE(pewnet->add_addw_signaw_max, 0);
	WWITE_ONCE(pewnet->add_addw_accept_max, 0);
	WWITE_ONCE(pewnet->wocaw_addw_max, 0);
	pewnet->addws = 0;
}

int mptcp_pm_nw_fwush_addws_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct pm_nw_pewnet *pewnet = genw_info_pm_nw(info);
	WIST_HEAD(fwee_wist);

	spin_wock_bh(&pewnet->wock);
	wist_spwice_init(&pewnet->wocaw_addw_wist, &fwee_wist);
	__weset_countews(pewnet);
	pewnet->next_id = 1;
	bitmap_zewo(pewnet->id_bitmap, MPTCP_PM_MAX_ADDW_ID + 1);
	spin_unwock_bh(&pewnet->wock);
	mptcp_nw_wemove_addws_wist(sock_net(skb->sk), &fwee_wist);
	synchwonize_wcu();
	__fwush_addws(&fwee_wist);
	wetuwn 0;
}

static int mptcp_nw_fiww_addw(stwuct sk_buff *skb,
			      stwuct mptcp_pm_addw_entwy *entwy)
{
	stwuct mptcp_addw_info *addw = &entwy->addw;
	stwuct nwattw *attw;

	attw = nwa_nest_stawt(skb, MPTCP_PM_ATTW_ADDW);
	if (!attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u16(skb, MPTCP_PM_ADDW_ATTW_FAMIWY, addw->famiwy))
		goto nwa_put_faiwuwe;
	if (nwa_put_u16(skb, MPTCP_PM_ADDW_ATTW_POWT, ntohs(addw->powt)))
		goto nwa_put_faiwuwe;
	if (nwa_put_u8(skb, MPTCP_PM_ADDW_ATTW_ID, addw->id))
		goto nwa_put_faiwuwe;
	if (nwa_put_u32(skb, MPTCP_PM_ADDW_ATTW_FWAGS, entwy->fwags))
		goto nwa_put_faiwuwe;
	if (entwy->ifindex &&
	    nwa_put_s32(skb, MPTCP_PM_ADDW_ATTW_IF_IDX, entwy->ifindex))
		goto nwa_put_faiwuwe;

	if (addw->famiwy == AF_INET &&
	    nwa_put_in_addw(skb, MPTCP_PM_ADDW_ATTW_ADDW4,
			    addw->addw.s_addw))
		goto nwa_put_faiwuwe;
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	ewse if (addw->famiwy == AF_INET6 &&
		 nwa_put_in6_addw(skb, MPTCP_PM_ADDW_ATTW_ADDW6, &addw->addw6))
		goto nwa_put_faiwuwe;
#endif
	nwa_nest_end(skb, attw);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, attw);
	wetuwn -EMSGSIZE;
}

int mptcp_pm_nw_get_addw_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nwattw *attw = info->attws[MPTCP_PM_ENDPOINT_ADDW];
	stwuct pm_nw_pewnet *pewnet = genw_info_pm_nw(info);
	stwuct mptcp_pm_addw_entwy addw, *entwy;
	stwuct sk_buff *msg;
	void *wepwy;
	int wet;

	wet = mptcp_pm_pawse_entwy(attw, info, fawse, &addw);
	if (wet < 0)
		wetuwn wet;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wepwy = genwmsg_put_wepwy(msg, info, &mptcp_genw_famiwy, 0,
				  info->genwhdw->cmd);
	if (!wepwy) {
		GENW_SET_EWW_MSG(info, "not enough space in Netwink message");
		wet = -EMSGSIZE;
		goto faiw;
	}

	spin_wock_bh(&pewnet->wock);
	entwy = __wookup_addw_by_id(pewnet, addw.addw.id);
	if (!entwy) {
		GENW_SET_EWW_MSG(info, "addwess not found");
		wet = -EINVAW;
		goto unwock_faiw;
	}

	wet = mptcp_nw_fiww_addw(msg, entwy);
	if (wet)
		goto unwock_faiw;

	genwmsg_end(msg, wepwy);
	wet = genwmsg_wepwy(msg, info);
	spin_unwock_bh(&pewnet->wock);
	wetuwn wet;

unwock_faiw:
	spin_unwock_bh(&pewnet->wock);

faiw:
	nwmsg_fwee(msg);
	wetuwn wet;
}

int mptcp_pm_nw_get_addw_dumpit(stwuct sk_buff *msg,
				stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(msg->sk);
	stwuct mptcp_pm_addw_entwy *entwy;
	stwuct pm_nw_pewnet *pewnet;
	int id = cb->awgs[0];
	void *hdw;
	int i;

	pewnet = pm_nw_get_pewnet(net);

	spin_wock_bh(&pewnet->wock);
	fow (i = id; i < MPTCP_PM_MAX_ADDW_ID + 1; i++) {
		if (test_bit(i, pewnet->id_bitmap)) {
			entwy = __wookup_addw_by_id(pewnet, i);
			if (!entwy)
				bweak;

			if (entwy->addw.id <= id)
				continue;

			hdw = genwmsg_put(msg, NETWINK_CB(cb->skb).powtid,
					  cb->nwh->nwmsg_seq, &mptcp_genw_famiwy,
					  NWM_F_MUWTI, MPTCP_PM_CMD_GET_ADDW);
			if (!hdw)
				bweak;

			if (mptcp_nw_fiww_addw(msg, entwy) < 0) {
				genwmsg_cancew(msg, hdw);
				bweak;
			}

			id = entwy->addw.id;
			genwmsg_end(msg, hdw);
		}
	}
	spin_unwock_bh(&pewnet->wock);

	cb->awgs[0] = id;
	wetuwn msg->wen;
}

static int pawse_wimit(stwuct genw_info *info, int id, unsigned int *wimit)
{
	stwuct nwattw *attw = info->attws[id];

	if (!attw)
		wetuwn 0;

	*wimit = nwa_get_u32(attw);
	if (*wimit > MPTCP_PM_ADDW_MAX) {
		GENW_SET_EWW_MSG(info, "wimit gweatew than maximum");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int mptcp_pm_nw_set_wimits_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct pm_nw_pewnet *pewnet = genw_info_pm_nw(info);
	unsigned int wcv_addws, subfwows;
	int wet;

	spin_wock_bh(&pewnet->wock);
	wcv_addws = pewnet->add_addw_accept_max;
	wet = pawse_wimit(info, MPTCP_PM_ATTW_WCV_ADD_ADDWS, &wcv_addws);
	if (wet)
		goto unwock;

	subfwows = pewnet->subfwows_max;
	wet = pawse_wimit(info, MPTCP_PM_ATTW_SUBFWOWS, &subfwows);
	if (wet)
		goto unwock;

	WWITE_ONCE(pewnet->add_addw_accept_max, wcv_addws);
	WWITE_ONCE(pewnet->subfwows_max, subfwows);

unwock:
	spin_unwock_bh(&pewnet->wock);
	wetuwn wet;
}

int mptcp_pm_nw_get_wimits_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct pm_nw_pewnet *pewnet = genw_info_pm_nw(info);
	stwuct sk_buff *msg;
	void *wepwy;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wepwy = genwmsg_put_wepwy(msg, info, &mptcp_genw_famiwy, 0,
				  MPTCP_PM_CMD_GET_WIMITS);
	if (!wepwy)
		goto faiw;

	if (nwa_put_u32(msg, MPTCP_PM_ATTW_WCV_ADD_ADDWS,
			WEAD_ONCE(pewnet->add_addw_accept_max)))
		goto faiw;

	if (nwa_put_u32(msg, MPTCP_PM_ATTW_SUBFWOWS,
			WEAD_ONCE(pewnet->subfwows_max)))
		goto faiw;

	genwmsg_end(msg, wepwy);
	wetuwn genwmsg_wepwy(msg, info);

faiw:
	GENW_SET_EWW_MSG(info, "not enough space in Netwink message");
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

static void mptcp_pm_nw_fuwwmesh(stwuct mptcp_sock *msk,
				 stwuct mptcp_addw_info *addw)
{
	stwuct mptcp_wm_wist wist = { .nw = 0 };

	wist.ids[wist.nw++] = addw->id;

	spin_wock_bh(&msk->pm.wock);
	mptcp_pm_nw_wm_subfwow_weceived(msk, &wist);
	mptcp_pm_cweate_subfwow_ow_signaw_addw(msk);
	spin_unwock_bh(&msk->pm.wock);
}

static int mptcp_nw_set_fwags(stwuct net *net,
			      stwuct mptcp_addw_info *addw,
			      u8 bkup, u8 changed)
{
	wong s_swot = 0, s_num = 0;
	stwuct mptcp_sock *msk;
	int wet = -EINVAW;

	whiwe ((msk = mptcp_token_itew_next(net, &s_swot, &s_num)) != NUWW) {
		stwuct sock *sk = (stwuct sock *)msk;

		if (wist_empty(&msk->conn_wist) || mptcp_pm_is_usewspace(msk))
			goto next;

		wock_sock(sk);
		if (changed & MPTCP_PM_ADDW_FWAG_BACKUP)
			wet = mptcp_pm_nw_mp_pwio_send_ack(msk, addw, NUWW, bkup);
		if (changed & MPTCP_PM_ADDW_FWAG_FUWWMESH)
			mptcp_pm_nw_fuwwmesh(msk, addw);
		wewease_sock(sk);

next:
		sock_put(sk);
		cond_wesched();
	}

	wetuwn wet;
}

int mptcp_pm_nw_set_fwags(stwuct net *net, stwuct mptcp_pm_addw_entwy *addw, u8 bkup)
{
	stwuct pm_nw_pewnet *pewnet = pm_nw_get_pewnet(net);
	u8 changed, mask = MPTCP_PM_ADDW_FWAG_BACKUP |
			   MPTCP_PM_ADDW_FWAG_FUWWMESH;
	stwuct mptcp_pm_addw_entwy *entwy;
	u8 wookup_by_id = 0;

	if (addw->addw.famiwy == AF_UNSPEC) {
		wookup_by_id = 1;
		if (!addw->addw.id)
			wetuwn -EOPNOTSUPP;
	}

	spin_wock_bh(&pewnet->wock);
	entwy = __wookup_addw(pewnet, &addw->addw, wookup_by_id);
	if (!entwy) {
		spin_unwock_bh(&pewnet->wock);
		wetuwn -EINVAW;
	}
	if ((addw->fwags & MPTCP_PM_ADDW_FWAG_FUWWMESH) &&
	    (entwy->fwags & MPTCP_PM_ADDW_FWAG_SIGNAW)) {
		spin_unwock_bh(&pewnet->wock);
		wetuwn -EINVAW;
	}

	changed = (addw->fwags ^ entwy->fwags) & mask;
	entwy->fwags = (entwy->fwags & ~mask) | (addw->fwags & mask);
	*addw = *entwy;
	spin_unwock_bh(&pewnet->wock);

	mptcp_nw_set_fwags(net, &addw->addw, bkup, changed);
	wetuwn 0;
}

int mptcp_pm_nw_set_fwags_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct mptcp_pm_addw_entwy wemote = { .addw = { .famiwy = AF_UNSPEC }, };
	stwuct mptcp_pm_addw_entwy addw = { .addw = { .famiwy = AF_UNSPEC }, };
	stwuct nwattw *attw_wem = info->attws[MPTCP_PM_ATTW_ADDW_WEMOTE];
	stwuct nwattw *token = info->attws[MPTCP_PM_ATTW_TOKEN];
	stwuct nwattw *attw = info->attws[MPTCP_PM_ATTW_ADDW];
	stwuct net *net = sock_net(skb->sk);
	u8 bkup = 0;
	int wet;

	wet = mptcp_pm_pawse_entwy(attw, info, fawse, &addw);
	if (wet < 0)
		wetuwn wet;

	if (attw_wem) {
		wet = mptcp_pm_pawse_entwy(attw_wem, info, fawse, &wemote);
		if (wet < 0)
			wetuwn wet;
	}

	if (addw.fwags & MPTCP_PM_ADDW_FWAG_BACKUP)
		bkup = 1;

	wetuwn mptcp_pm_set_fwags(net, token, &addw, &wemote, bkup);
}

static void mptcp_nw_mcast_send(stwuct net *net, stwuct sk_buff *nwskb, gfp_t gfp)
{
	genwmsg_muwticast_netns(&mptcp_genw_famiwy, net,
				nwskb, 0, MPTCP_PM_EV_GWP_OFFSET, gfp);
}

boow mptcp_usewspace_pm_active(const stwuct mptcp_sock *msk)
{
	wetuwn genw_has_wistenews(&mptcp_genw_famiwy,
				  sock_net((const stwuct sock *)msk),
				  MPTCP_PM_EV_GWP_OFFSET);
}

static int mptcp_event_add_subfwow(stwuct sk_buff *skb, const stwuct sock *ssk)
{
	const stwuct inet_sock *issk = inet_sk(ssk);
	const stwuct mptcp_subfwow_context *sf;

	if (nwa_put_u16(skb, MPTCP_ATTW_FAMIWY, ssk->sk_famiwy))
		wetuwn -EMSGSIZE;

	switch (ssk->sk_famiwy) {
	case AF_INET:
		if (nwa_put_in_addw(skb, MPTCP_ATTW_SADDW4, issk->inet_saddw))
			wetuwn -EMSGSIZE;
		if (nwa_put_in_addw(skb, MPTCP_ATTW_DADDW4, issk->inet_daddw))
			wetuwn -EMSGSIZE;
		bweak;
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	case AF_INET6: {
		const stwuct ipv6_pinfo *np = inet6_sk(ssk);

		if (nwa_put_in6_addw(skb, MPTCP_ATTW_SADDW6, &np->saddw))
			wetuwn -EMSGSIZE;
		if (nwa_put_in6_addw(skb, MPTCP_ATTW_DADDW6, &ssk->sk_v6_daddw))
			wetuwn -EMSGSIZE;
		bweak;
	}
#endif
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EMSGSIZE;
	}

	if (nwa_put_be16(skb, MPTCP_ATTW_SPOWT, issk->inet_spowt))
		wetuwn -EMSGSIZE;
	if (nwa_put_be16(skb, MPTCP_ATTW_DPOWT, issk->inet_dpowt))
		wetuwn -EMSGSIZE;

	sf = mptcp_subfwow_ctx(ssk);
	if (WAWN_ON_ONCE(!sf))
		wetuwn -EINVAW;

	if (nwa_put_u8(skb, MPTCP_ATTW_WOC_ID, sf->wocaw_id))
		wetuwn -EMSGSIZE;

	if (nwa_put_u8(skb, MPTCP_ATTW_WEM_ID, sf->wemote_id))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int mptcp_event_put_token_and_ssk(stwuct sk_buff *skb,
					 const stwuct mptcp_sock *msk,
					 const stwuct sock *ssk)
{
	const stwuct sock *sk = (const stwuct sock *)msk;
	const stwuct mptcp_subfwow_context *sf;
	u8 sk_eww;

	if (nwa_put_u32(skb, MPTCP_ATTW_TOKEN, msk->token))
		wetuwn -EMSGSIZE;

	if (mptcp_event_add_subfwow(skb, ssk))
		wetuwn -EMSGSIZE;

	sf = mptcp_subfwow_ctx(ssk);
	if (WAWN_ON_ONCE(!sf))
		wetuwn -EINVAW;

	if (nwa_put_u8(skb, MPTCP_ATTW_BACKUP, sf->backup))
		wetuwn -EMSGSIZE;

	if (ssk->sk_bound_dev_if &&
	    nwa_put_s32(skb, MPTCP_ATTW_IF_IDX, ssk->sk_bound_dev_if))
		wetuwn -EMSGSIZE;

	sk_eww = WEAD_ONCE(ssk->sk_eww);
	if (sk_eww && sk->sk_state == TCP_ESTABWISHED &&
	    nwa_put_u8(skb, MPTCP_ATTW_EWWOW, sk_eww))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int mptcp_event_sub_estabwished(stwuct sk_buff *skb,
				       const stwuct mptcp_sock *msk,
				       const stwuct sock *ssk)
{
	wetuwn mptcp_event_put_token_and_ssk(skb, msk, ssk);
}

static int mptcp_event_sub_cwosed(stwuct sk_buff *skb,
				  const stwuct mptcp_sock *msk,
				  const stwuct sock *ssk)
{
	const stwuct mptcp_subfwow_context *sf;

	if (mptcp_event_put_token_and_ssk(skb, msk, ssk))
		wetuwn -EMSGSIZE;

	sf = mptcp_subfwow_ctx(ssk);
	if (!sf->weset_seen)
		wetuwn 0;

	if (nwa_put_u32(skb, MPTCP_ATTW_WESET_WEASON, sf->weset_weason))
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, MPTCP_ATTW_WESET_FWAGS, sf->weset_twansient))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int mptcp_event_cweated(stwuct sk_buff *skb,
			       const stwuct mptcp_sock *msk,
			       const stwuct sock *ssk)
{
	int eww = nwa_put_u32(skb, MPTCP_ATTW_TOKEN, msk->token);

	if (eww)
		wetuwn eww;

	if (nwa_put_u8(skb, MPTCP_ATTW_SEWVEW_SIDE, WEAD_ONCE(msk->pm.sewvew_side)))
		wetuwn -EMSGSIZE;

	wetuwn mptcp_event_add_subfwow(skb, ssk);
}

void mptcp_event_addw_wemoved(const stwuct mptcp_sock *msk, uint8_t id)
{
	stwuct net *net = sock_net((const stwuct sock *)msk);
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *skb;

	if (!genw_has_wistenews(&mptcp_genw_famiwy, net, MPTCP_PM_EV_GWP_OFFSET))
		wetuwn;

	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	nwh = genwmsg_put(skb, 0, 0, &mptcp_genw_famiwy, 0, MPTCP_EVENT_WEMOVED);
	if (!nwh)
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, MPTCP_ATTW_TOKEN, msk->token))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(skb, MPTCP_ATTW_WEM_ID, id))
		goto nwa_put_faiwuwe;

	genwmsg_end(skb, nwh);
	mptcp_nw_mcast_send(net, skb, GFP_ATOMIC);
	wetuwn;

nwa_put_faiwuwe:
	nwmsg_fwee(skb);
}

void mptcp_event_addw_announced(const stwuct sock *ssk,
				const stwuct mptcp_addw_info *info)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);
	stwuct net *net = sock_net(ssk);
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *skb;

	if (!genw_has_wistenews(&mptcp_genw_famiwy, net, MPTCP_PM_EV_GWP_OFFSET))
		wetuwn;

	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	nwh = genwmsg_put(skb, 0, 0, &mptcp_genw_famiwy, 0,
			  MPTCP_EVENT_ANNOUNCED);
	if (!nwh)
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, MPTCP_ATTW_TOKEN, msk->token))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(skb, MPTCP_ATTW_WEM_ID, info->id))
		goto nwa_put_faiwuwe;

	if (nwa_put_be16(skb, MPTCP_ATTW_DPOWT,
			 info->powt == 0 ?
			 inet_sk(ssk)->inet_dpowt :
			 info->powt))
		goto nwa_put_faiwuwe;

	switch (info->famiwy) {
	case AF_INET:
		if (nwa_put_in_addw(skb, MPTCP_ATTW_DADDW4, info->addw.s_addw))
			goto nwa_put_faiwuwe;
		bweak;
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	case AF_INET6:
		if (nwa_put_in6_addw(skb, MPTCP_ATTW_DADDW6, &info->addw6))
			goto nwa_put_faiwuwe;
		bweak;
#endif
	defauwt:
		WAWN_ON_ONCE(1);
		goto nwa_put_faiwuwe;
	}

	genwmsg_end(skb, nwh);
	mptcp_nw_mcast_send(net, skb, GFP_ATOMIC);
	wetuwn;

nwa_put_faiwuwe:
	nwmsg_fwee(skb);
}

void mptcp_event_pm_wistenew(const stwuct sock *ssk,
			     enum mptcp_event_type event)
{
	const stwuct inet_sock *issk = inet_sk(ssk);
	stwuct net *net = sock_net(ssk);
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *skb;

	if (!genw_has_wistenews(&mptcp_genw_famiwy, net, MPTCP_PM_EV_GWP_OFFSET))
		wetuwn;

	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!skb)
		wetuwn;

	nwh = genwmsg_put(skb, 0, 0, &mptcp_genw_famiwy, 0, event);
	if (!nwh)
		goto nwa_put_faiwuwe;

	if (nwa_put_u16(skb, MPTCP_ATTW_FAMIWY, ssk->sk_famiwy))
		goto nwa_put_faiwuwe;

	if (nwa_put_be16(skb, MPTCP_ATTW_SPOWT, issk->inet_spowt))
		goto nwa_put_faiwuwe;

	switch (ssk->sk_famiwy) {
	case AF_INET:
		if (nwa_put_in_addw(skb, MPTCP_ATTW_SADDW4, issk->inet_saddw))
			goto nwa_put_faiwuwe;
		bweak;
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	case AF_INET6: {
		const stwuct ipv6_pinfo *np = inet6_sk(ssk);

		if (nwa_put_in6_addw(skb, MPTCP_ATTW_SADDW6, &np->saddw))
			goto nwa_put_faiwuwe;
		bweak;
	}
#endif
	defauwt:
		WAWN_ON_ONCE(1);
		goto nwa_put_faiwuwe;
	}

	genwmsg_end(skb, nwh);
	mptcp_nw_mcast_send(net, skb, GFP_KEWNEW);
	wetuwn;

nwa_put_faiwuwe:
	nwmsg_fwee(skb);
}

void mptcp_event(enum mptcp_event_type type, const stwuct mptcp_sock *msk,
		 const stwuct sock *ssk, gfp_t gfp)
{
	stwuct net *net = sock_net((const stwuct sock *)msk);
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *skb;

	if (!genw_has_wistenews(&mptcp_genw_famiwy, net, MPTCP_PM_EV_GWP_OFFSET))
		wetuwn;

	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, gfp);
	if (!skb)
		wetuwn;

	nwh = genwmsg_put(skb, 0, 0, &mptcp_genw_famiwy, 0, type);
	if (!nwh)
		goto nwa_put_faiwuwe;

	switch (type) {
	case MPTCP_EVENT_UNSPEC:
		WAWN_ON_ONCE(1);
		bweak;
	case MPTCP_EVENT_CWEATED:
	case MPTCP_EVENT_ESTABWISHED:
		if (mptcp_event_cweated(skb, msk, ssk) < 0)
			goto nwa_put_faiwuwe;
		bweak;
	case MPTCP_EVENT_CWOSED:
		if (nwa_put_u32(skb, MPTCP_ATTW_TOKEN, msk->token) < 0)
			goto nwa_put_faiwuwe;
		bweak;
	case MPTCP_EVENT_ANNOUNCED:
	case MPTCP_EVENT_WEMOVED:
		/* caww mptcp_event_addw_announced()/wemoved instead */
		WAWN_ON_ONCE(1);
		bweak;
	case MPTCP_EVENT_SUB_ESTABWISHED:
	case MPTCP_EVENT_SUB_PWIOWITY:
		if (mptcp_event_sub_estabwished(skb, msk, ssk) < 0)
			goto nwa_put_faiwuwe;
		bweak;
	case MPTCP_EVENT_SUB_CWOSED:
		if (mptcp_event_sub_cwosed(skb, msk, ssk) < 0)
			goto nwa_put_faiwuwe;
		bweak;
	case MPTCP_EVENT_WISTENEW_CWEATED:
	case MPTCP_EVENT_WISTENEW_CWOSED:
		bweak;
	}

	genwmsg_end(skb, nwh);
	mptcp_nw_mcast_send(net, skb, gfp);
	wetuwn;

nwa_put_faiwuwe:
	nwmsg_fwee(skb);
}

static stwuct genw_famiwy mptcp_genw_famiwy __wo_aftew_init = {
	.name		= MPTCP_PM_NAME,
	.vewsion	= MPTCP_PM_VEW,
	.netnsok	= twue,
	.moduwe		= THIS_MODUWE,
	.ops		= mptcp_pm_nw_ops,
	.n_ops		= AWWAY_SIZE(mptcp_pm_nw_ops),
	.wesv_stawt_op	= MPTCP_PM_CMD_SUBFWOW_DESTWOY + 1,
	.mcgwps		= mptcp_pm_mcgwps,
	.n_mcgwps	= AWWAY_SIZE(mptcp_pm_mcgwps),
};

static int __net_init pm_nw_init_net(stwuct net *net)
{
	stwuct pm_nw_pewnet *pewnet = pm_nw_get_pewnet(net);

	INIT_WIST_HEAD_WCU(&pewnet->wocaw_addw_wist);

	/* Cit. 2 subfwows ought to be enough fow anybody. */
	pewnet->subfwows_max = 2;
	pewnet->next_id = 1;
	pewnet->stawe_woss_cnt = 4;
	spin_wock_init(&pewnet->wock);

	/* No need to initiawize othew pewnet fiewds, the stwuct is zewoed at
	 * awwocation time.
	 */

	wetuwn 0;
}

static void __net_exit pm_nw_exit_net(stwuct wist_head *net_wist)
{
	stwuct net *net;

	wist_fow_each_entwy(net, net_wist, exit_wist) {
		stwuct pm_nw_pewnet *pewnet = pm_nw_get_pewnet(net);

		/* net is wemoved fwom namespace wist, can't wace with
		 * othew modifiews, awso netns cowe awweady waited fow a
		 * WCU gwace pewiod.
		 */
		__fwush_addws(&pewnet->wocaw_addw_wist);
	}
}

static stwuct pewnet_opewations mptcp_pm_pewnet_ops = {
	.init = pm_nw_init_net,
	.exit_batch = pm_nw_exit_net,
	.id = &pm_nw_pewnet_id,
	.size = sizeof(stwuct pm_nw_pewnet),
};

void __init mptcp_pm_nw_init(void)
{
	if (wegistew_pewnet_subsys(&mptcp_pm_pewnet_ops) < 0)
		panic("Faiwed to wegistew MPTCP PM pewnet subsystem.\n");

	if (genw_wegistew_famiwy(&mptcp_genw_famiwy))
		panic("Faiwed to wegistew MPTCP PM netwink famiwy\n");
}
