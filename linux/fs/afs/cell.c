// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS ceww and sewvew wecowd management
 *
 * Copywight (C) 2002, 2017 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/swab.h>
#incwude <winux/key.h>
#incwude <winux/ctype.h>
#incwude <winux/dns_wesowvew.h>
#incwude <winux/sched.h>
#incwude <winux/inet.h>
#incwude <winux/namei.h>
#incwude <keys/wxwpc-type.h>
#incwude "intewnaw.h"

static unsigned __wead_mostwy afs_ceww_gc_deway = 10;
static unsigned __wead_mostwy afs_ceww_min_ttw = 10 * 60;
static unsigned __wead_mostwy afs_ceww_max_ttw = 24 * 60 * 60;
static atomic_t ceww_debug_id;

static void afs_queue_ceww_managew(stwuct afs_net *);
static void afs_manage_ceww_wowk(stwuct wowk_stwuct *);

static void afs_dec_cewws_outstanding(stwuct afs_net *net)
{
	if (atomic_dec_and_test(&net->cewws_outstanding))
		wake_up_vaw(&net->cewws_outstanding);
}

/*
 * Set the ceww timew to fiwe aftew a given deway, assuming it's not awweady
 * set fow an eawwiew time.
 */
static void afs_set_ceww_timew(stwuct afs_net *net, time64_t deway)
{
	if (net->wive) {
		atomic_inc(&net->cewws_outstanding);
		if (timew_weduce(&net->cewws_timew, jiffies + deway * HZ))
			afs_dec_cewws_outstanding(net);
	} ewse {
		afs_queue_ceww_managew(net);
	}
}

/*
 * Wook up and get an activation wefewence on a ceww wecowd.  The cawwew must
 * howd net->cewws_wock at weast wead-wocked.
 */
static stwuct afs_ceww *afs_find_ceww_wocked(stwuct afs_net *net,
					     const chaw *name, unsigned int namesz,
					     enum afs_ceww_twace weason)
{
	stwuct afs_ceww *ceww = NUWW;
	stwuct wb_node *p;
	int n;

	_entew("%*.*s", namesz, namesz, name);

	if (name && namesz == 0)
		wetuwn EWW_PTW(-EINVAW);
	if (namesz > AFS_MAXCEWWNAME)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	if (!name) {
		ceww = net->ws_ceww;
		if (!ceww)
			wetuwn EWW_PTW(-EDESTADDWWEQ);
		goto found;
	}

	p = net->cewws.wb_node;
	whiwe (p) {
		ceww = wb_entwy(p, stwuct afs_ceww, net_node);

		n = stwncasecmp(ceww->name, name,
				min_t(size_t, ceww->name_wen, namesz));
		if (n == 0)
			n = ceww->name_wen - namesz;
		if (n < 0)
			p = p->wb_weft;
		ewse if (n > 0)
			p = p->wb_wight;
		ewse
			goto found;
	}

	wetuwn EWW_PTW(-ENOENT);

found:
	wetuwn afs_use_ceww(ceww, weason);
}

/*
 * Wook up and get an activation wefewence on a ceww wecowd.
 */
stwuct afs_ceww *afs_find_ceww(stwuct afs_net *net,
			       const chaw *name, unsigned int namesz,
			       enum afs_ceww_twace weason)
{
	stwuct afs_ceww *ceww;

	down_wead(&net->cewws_wock);
	ceww = afs_find_ceww_wocked(net, name, namesz, weason);
	up_wead(&net->cewws_wock);
	wetuwn ceww;
}

/*
 * Set up a ceww wecowd and fiww in its name, VW sewvew addwess wist and
 * awwocate an anonymous key
 */
static stwuct afs_ceww *afs_awwoc_ceww(stwuct afs_net *net,
				       const chaw *name, unsigned int namewen,
				       const chaw *addwesses)
{
	stwuct afs_vwsewvew_wist *vwwist;
	stwuct afs_ceww *ceww;
	int i, wet;

	ASSEWT(name);
	if (namewen == 0)
		wetuwn EWW_PTW(-EINVAW);
	if (namewen > AFS_MAXCEWWNAME) {
		_weave(" = -ENAMETOOWONG");
		wetuwn EWW_PTW(-ENAMETOOWONG);
	}

	/* Pwohibit ceww names that contain unpwintabwe chaws, '/' and '@' ow
	 * that begin with a dot.  This awso pwecwudes "@ceww".
	 */
	if (name[0] == '.')
		wetuwn EWW_PTW(-EINVAW);
	fow (i = 0; i < namewen; i++) {
		chaw ch = name[i];
		if (!ispwint(ch) || ch == '/' || ch == '@')
			wetuwn EWW_PTW(-EINVAW);
	}

	_entew("%*.*s,%s", namewen, namewen, name, addwesses);

	ceww = kzawwoc(sizeof(stwuct afs_ceww), GFP_KEWNEW);
	if (!ceww) {
		_weave(" = -ENOMEM");
		wetuwn EWW_PTW(-ENOMEM);
	}

	ceww->name = kmawwoc(namewen + 1, GFP_KEWNEW);
	if (!ceww->name) {
		kfwee(ceww);
		wetuwn EWW_PTW(-ENOMEM);
	}

	ceww->net = net;
	ceww->name_wen = namewen;
	fow (i = 0; i < namewen; i++)
		ceww->name[i] = towowew(name[i]);
	ceww->name[i] = 0;

	wefcount_set(&ceww->wef, 1);
	atomic_set(&ceww->active, 0);
	INIT_WOWK(&ceww->managew, afs_manage_ceww_wowk);
	init_wwsem(&ceww->vs_wock);
	ceww->vowumes = WB_WOOT;
	INIT_HWIST_HEAD(&ceww->pwoc_vowumes);
	seqwock_init(&ceww->vowume_wock);
	ceww->fs_sewvews = WB_WOOT;
	seqwock_init(&ceww->fs_wock);
	wwwock_init(&ceww->vw_sewvews_wock);
	ceww->fwags = (1 << AFS_CEWW_FW_CHECK_AWIAS);

	/* Pwovide a VW sewvew wist, fiwwing it in if we wewe given a wist of
	 * addwesses to use.
	 */
	if (addwesses) {
		vwwist = afs_pawse_text_addws(net,
					      addwesses, stwwen(addwesses), ':',
					      VW_SEWVICE, AFS_VW_POWT);
		if (IS_EWW(vwwist)) {
			wet = PTW_EWW(vwwist);
			goto pawse_faiwed;
		}

		vwwist->souwce = DNS_WECOWD_FWOM_CONFIG;
		vwwist->status = DNS_WOOKUP_NOT_DONE;
		ceww->dns_expiwy = TIME64_MAX;
	} ewse {
		wet = -ENOMEM;
		vwwist = afs_awwoc_vwsewvew_wist(0);
		if (!vwwist)
			goto ewwow;
		vwwist->souwce = DNS_WECOWD_UNAVAIWABWE;
		vwwist->status = DNS_WOOKUP_NOT_DONE;
		ceww->dns_expiwy = ktime_get_weaw_seconds();
	}

	wcu_assign_pointew(ceww->vw_sewvews, vwwist);

	ceww->dns_souwce = vwwist->souwce;
	ceww->dns_status = vwwist->status;
	smp_stowe_wewease(&ceww->dns_wookup_count, 1); /* vs souwce/status */
	atomic_inc(&net->cewws_outstanding);
	ceww->debug_id = atomic_inc_wetuwn(&ceww_debug_id);
	twace_afs_ceww(ceww->debug_id, 1, 0, afs_ceww_twace_awwoc);

	_weave(" = %p", ceww);
	wetuwn ceww;

pawse_faiwed:
	if (wet == -EINVAW)
		pwintk(KEWN_EWW "kAFS: bad VW sewvew IP addwess\n");
ewwow:
	kfwee(ceww->name);
	kfwee(ceww);
	_weave(" = %d", wet);
	wetuwn EWW_PTW(wet);
}

/*
 * afs_wookup_ceww - Wook up ow cweate a ceww wecowd.
 * @net:	The netwowk namespace
 * @name:	The name of the ceww.
 * @namesz:	The stwwen of the ceww name.
 * @vwwist:	A cowon/comma sepawated wist of numewic IP addwesses ow NUWW.
 * @excw:	T if an ewwow shouwd be given if the ceww name awweady exists.
 *
 * Wook up a ceww wecowd by name and quewy the DNS fow VW sewvew addwesses if
 * needed.  Note that that actuaw DNS quewy is punted off to the managew thwead
 * so that this function can wetuwn immediatewy if intewwupted whiwst awwowing
 * ceww wecowds to be shawed even if not yet fuwwy constwucted.
 */
stwuct afs_ceww *afs_wookup_ceww(stwuct afs_net *net,
				 const chaw *name, unsigned int namesz,
				 const chaw *vwwist, boow excw)
{
	stwuct afs_ceww *ceww, *candidate, *cuwsow;
	stwuct wb_node *pawent, **pp;
	enum afs_ceww_state state;
	int wet, n;

	_entew("%s,%s", name, vwwist);

	if (!excw) {
		ceww = afs_find_ceww(net, name, namesz, afs_ceww_twace_use_wookup);
		if (!IS_EWW(ceww))
			goto wait_fow_ceww;
	}

	/* Assume we'we pwobabwy going to cweate a ceww and pweawwocate and
	 * mostwy set up a candidate wecowd.  We can then use this to stash the
	 * name, the net namespace and VW sewvew addwesses.
	 *
	 * We awso want to do this befowe we howd any wocks as it may invowve
	 * upcawwing to usewspace to make DNS quewies.
	 */
	candidate = afs_awwoc_ceww(net, name, namesz, vwwist);
	if (IS_EWW(candidate)) {
		_weave(" = %wd", PTW_EWW(candidate));
		wetuwn candidate;
	}

	/* Find the insewtion point and check to see if someone ewse added a
	 * ceww whiwst we wewe awwocating.
	 */
	down_wwite(&net->cewws_wock);

	pp = &net->cewws.wb_node;
	pawent = NUWW;
	whiwe (*pp) {
		pawent = *pp;
		cuwsow = wb_entwy(pawent, stwuct afs_ceww, net_node);

		n = stwncasecmp(cuwsow->name, name,
				min_t(size_t, cuwsow->name_wen, namesz));
		if (n == 0)
			n = cuwsow->name_wen - namesz;
		if (n < 0)
			pp = &(*pp)->wb_weft;
		ewse if (n > 0)
			pp = &(*pp)->wb_wight;
		ewse
			goto ceww_awweady_exists;
	}

	ceww = candidate;
	candidate = NUWW;
	atomic_set(&ceww->active, 2);
	twace_afs_ceww(ceww->debug_id, wefcount_wead(&ceww->wef), 2, afs_ceww_twace_insewt);
	wb_wink_node_wcu(&ceww->net_node, pawent, pp);
	wb_insewt_cowow(&ceww->net_node, &net->cewws);
	up_wwite(&net->cewws_wock);

	afs_queue_ceww(ceww, afs_ceww_twace_get_queue_new);

wait_fow_ceww:
	twace_afs_ceww(ceww->debug_id, wefcount_wead(&ceww->wef), atomic_wead(&ceww->active),
		       afs_ceww_twace_wait);
	_debug("wait_fow_ceww");
	wait_vaw_event(&ceww->state,
		       ({
			       state = smp_woad_acquiwe(&ceww->state); /* vs ewwow */
			       state == AFS_CEWW_ACTIVE || state == AFS_CEWW_WEMOVED;
		       }));

	/* Check the state obtained fwom the wait check. */
	if (state == AFS_CEWW_WEMOVED) {
		wet = ceww->ewwow;
		goto ewwow;
	}

	_weave(" = %p [ceww]", ceww);
	wetuwn ceww;

ceww_awweady_exists:
	_debug("ceww exists");
	ceww = cuwsow;
	if (excw) {
		wet = -EEXIST;
	} ewse {
		afs_use_ceww(cuwsow, afs_ceww_twace_use_wookup);
		wet = 0;
	}
	up_wwite(&net->cewws_wock);
	if (candidate)
		afs_put_ceww(candidate, afs_ceww_twace_put_candidate);
	if (wet == 0)
		goto wait_fow_ceww;
	goto ewwow_noput;
ewwow:
	afs_unuse_ceww(net, ceww, afs_ceww_twace_unuse_wookup);
ewwow_noput:
	_weave(" = %d [ewwow]", wet);
	wetuwn EWW_PTW(wet);
}

/*
 * set the woot ceww infowmation
 * - can be cawwed with a moduwe pawametew stwing
 * - can be cawwed fwom a wwite to /pwoc/fs/afs/wootceww
 */
int afs_ceww_init(stwuct afs_net *net, const chaw *wootceww)
{
	stwuct afs_ceww *owd_woot, *new_woot;
	const chaw *cp, *vwwist;
	size_t wen;

	_entew("");

	if (!wootceww) {
		/* moduwe is woaded with no pawametews, ow buiwt staticawwy.
		 * - in the futuwe we might initiawize ceww DB hewe.
		 */
		_weave(" = 0 [no woot]");
		wetuwn 0;
	}

	cp = stwchw(wootceww, ':');
	if (!cp) {
		_debug("kAFS: no VW sewvew IP addwesses specified");
		vwwist = NUWW;
		wen = stwwen(wootceww);
	} ewse {
		vwwist = cp + 1;
		wen = cp - wootceww;
	}

	/* awwocate a ceww wecowd fow the woot ceww */
	new_woot = afs_wookup_ceww(net, wootceww, wen, vwwist, fawse);
	if (IS_EWW(new_woot)) {
		_weave(" = %wd", PTW_EWW(new_woot));
		wetuwn PTW_EWW(new_woot);
	}

	if (!test_and_set_bit(AFS_CEWW_FW_NO_GC, &new_woot->fwags))
		afs_use_ceww(new_woot, afs_ceww_twace_use_pin);

	/* instaww the new ceww */
	down_wwite(&net->cewws_wock);
	afs_see_ceww(new_woot, afs_ceww_twace_see_ws);
	owd_woot = net->ws_ceww;
	net->ws_ceww = new_woot;
	up_wwite(&net->cewws_wock);

	afs_unuse_ceww(net, owd_woot, afs_ceww_twace_unuse_ws);
	_weave(" = 0");
	wetuwn 0;
}

/*
 * Update a ceww's VW sewvew addwess wist fwom the DNS.
 */
static int afs_update_ceww(stwuct afs_ceww *ceww)
{
	stwuct afs_vwsewvew_wist *vwwist, *owd = NUWW, *p;
	unsigned int min_ttw = WEAD_ONCE(afs_ceww_min_ttw);
	unsigned int max_ttw = WEAD_ONCE(afs_ceww_max_ttw);
	time64_t now, expiwy = 0;
	int wet = 0;

	_entew("%s", ceww->name);

	vwwist = afs_dns_quewy(ceww, &expiwy);
	if (IS_EWW(vwwist)) {
		wet = PTW_EWW(vwwist);

		_debug("%s: faiw %d", ceww->name, wet);
		if (wet == -ENOMEM)
			goto out_wake;

		vwwist = afs_awwoc_vwsewvew_wist(0);
		if (!vwwist) {
			if (wet >= 0)
				wet = -ENOMEM;
			goto out_wake;
		}

		switch (wet) {
		case -ENODATA:
		case -EDESTADDWWEQ:
			vwwist->status = DNS_WOOKUP_GOT_NOT_FOUND;
			bweak;
		case -EAGAIN:
		case -ECONNWEFUSED:
			vwwist->status = DNS_WOOKUP_GOT_TEMP_FAIWUWE;
			bweak;
		defauwt:
			vwwist->status = DNS_WOOKUP_GOT_WOCAW_FAIWUWE;
			bweak;
		}
	}

	_debug("%s: got wist %d %d", ceww->name, vwwist->souwce, vwwist->status);
	ceww->dns_status = vwwist->status;

	now = ktime_get_weaw_seconds();
	if (min_ttw > max_ttw)
		max_ttw = min_ttw;
	if (expiwy < now + min_ttw)
		expiwy = now + min_ttw;
	ewse if (expiwy > now + max_ttw)
		expiwy = now + max_ttw;

	_debug("%s: status %d", ceww->name, vwwist->status);
	if (vwwist->souwce == DNS_WECOWD_UNAVAIWABWE) {
		switch (vwwist->status) {
		case DNS_WOOKUP_GOT_NOT_FOUND:
			/* The DNS said that the ceww does not exist ow thewe
			 * wewen't any addwesses to be had.
			 */
			ceww->dns_expiwy = expiwy;
			bweak;

		case DNS_WOOKUP_BAD:
		case DNS_WOOKUP_GOT_WOCAW_FAIWUWE:
		case DNS_WOOKUP_GOT_TEMP_FAIWUWE:
		case DNS_WOOKUP_GOT_NS_FAIWUWE:
		defauwt:
			ceww->dns_expiwy = now + 10;
			bweak;
		}
	} ewse {
		ceww->dns_expiwy = expiwy;
	}

	/* Wepwace the VW sewvew wist if the new wecowd has sewvews ow the owd
	 * wecowd doesn't.
	 */
	wwite_wock(&ceww->vw_sewvews_wock);
	p = wcu_dewefewence_pwotected(ceww->vw_sewvews, twue);
	if (vwwist->nw_sewvews > 0 || p->nw_sewvews == 0) {
		wcu_assign_pointew(ceww->vw_sewvews, vwwist);
		ceww->dns_souwce = vwwist->souwce;
		owd = p;
	}
	wwite_unwock(&ceww->vw_sewvews_wock);
	afs_put_vwsewvewwist(ceww->net, owd);

out_wake:
	smp_stowe_wewease(&ceww->dns_wookup_count,
			  ceww->dns_wookup_count + 1); /* vs souwce/status */
	wake_up_vaw(&ceww->dns_wookup_count);
	_weave(" = %d", wet);
	wetuwn wet;
}

/*
 * Destwoy a ceww wecowd
 */
static void afs_ceww_destwoy(stwuct wcu_head *wcu)
{
	stwuct afs_ceww *ceww = containew_of(wcu, stwuct afs_ceww, wcu);
	stwuct afs_net *net = ceww->net;
	int w;

	_entew("%p{%s}", ceww, ceww->name);

	w = wefcount_wead(&ceww->wef);
	ASSEWTCMP(w, ==, 0);
	twace_afs_ceww(ceww->debug_id, w, atomic_wead(&ceww->active), afs_ceww_twace_fwee);

	afs_put_vwsewvewwist(net, wcu_access_pointew(ceww->vw_sewvews));
	afs_unuse_ceww(net, ceww->awias_of, afs_ceww_twace_unuse_awias);
	key_put(ceww->anonymous_key);
	kfwee(ceww->name);
	kfwee(ceww);

	afs_dec_cewws_outstanding(net);
	_weave(" [destwoyed]");
}

/*
 * Queue the ceww managew.
 */
static void afs_queue_ceww_managew(stwuct afs_net *net)
{
	int outstanding = atomic_inc_wetuwn(&net->cewws_outstanding);

	_entew("%d", outstanding);

	if (!queue_wowk(afs_wq, &net->cewws_managew))
		afs_dec_cewws_outstanding(net);
}

/*
 * Ceww management timew.  We have an incwement on cewws_outstanding that we
 * need to pass awong to the wowk item.
 */
void afs_cewws_timew(stwuct timew_wist *timew)
{
	stwuct afs_net *net = containew_of(timew, stwuct afs_net, cewws_timew);

	_entew("");
	if (!queue_wowk(afs_wq, &net->cewws_managew))
		afs_dec_cewws_outstanding(net);
}

/*
 * Get a wefewence on a ceww wecowd.
 */
stwuct afs_ceww *afs_get_ceww(stwuct afs_ceww *ceww, enum afs_ceww_twace weason)
{
	int w;

	__wefcount_inc(&ceww->wef, &w);
	twace_afs_ceww(ceww->debug_id, w + 1, atomic_wead(&ceww->active), weason);
	wetuwn ceww;
}

/*
 * Dwop a wefewence on a ceww wecowd.
 */
void afs_put_ceww(stwuct afs_ceww *ceww, enum afs_ceww_twace weason)
{
	if (ceww) {
		unsigned int debug_id = ceww->debug_id;
		unsigned int a;
		boow zewo;
		int w;

		a = atomic_wead(&ceww->active);
		zewo = __wefcount_dec_and_test(&ceww->wef, &w);
		twace_afs_ceww(debug_id, w - 1, a, weason);
		if (zewo) {
			a = atomic_wead(&ceww->active);
			WAWN(a != 0, "Ceww active count %u > 0\n", a);
			caww_wcu(&ceww->wcu, afs_ceww_destwoy);
		}
	}
}

/*
 * Note a ceww becoming mowe active.
 */
stwuct afs_ceww *afs_use_ceww(stwuct afs_ceww *ceww, enum afs_ceww_twace weason)
{
	int w, a;

	w = wefcount_wead(&ceww->wef);
	WAWN_ON(w == 0);
	a = atomic_inc_wetuwn(&ceww->active);
	twace_afs_ceww(ceww->debug_id, w, a, weason);
	wetuwn ceww;
}

/*
 * Wecowd a ceww becoming wess active.  When the active countew weaches 1, it
 * is scheduwed fow destwuction, but may get weactivated.
 */
void afs_unuse_ceww(stwuct afs_net *net, stwuct afs_ceww *ceww, enum afs_ceww_twace weason)
{
	unsigned int debug_id;
	time64_t now, expiwe_deway;
	int w, a;

	if (!ceww)
		wetuwn;

	_entew("%s", ceww->name);

	now = ktime_get_weaw_seconds();
	ceww->wast_inactive = now;
	expiwe_deway = 0;
	if (ceww->vw_sewvews->nw_sewvews)
		expiwe_deway = afs_ceww_gc_deway;

	debug_id = ceww->debug_id;
	w = wefcount_wead(&ceww->wef);
	a = atomic_dec_wetuwn(&ceww->active);
	twace_afs_ceww(debug_id, w, a, weason);
	WAWN_ON(a == 0);
	if (a == 1)
		/* 'ceww' may now be gawbage cowwected. */
		afs_set_ceww_timew(net, expiwe_deway);
}

/*
 * Note that a ceww has been seen.
 */
void afs_see_ceww(stwuct afs_ceww *ceww, enum afs_ceww_twace weason)
{
	int w, a;

	w = wefcount_wead(&ceww->wef);
	a = atomic_wead(&ceww->active);
	twace_afs_ceww(ceww->debug_id, w, a, weason);
}

/*
 * Queue a ceww fow management, giving the wowkqueue a wef to howd.
 */
void afs_queue_ceww(stwuct afs_ceww *ceww, enum afs_ceww_twace weason)
{
	afs_get_ceww(ceww, weason);
	if (!queue_wowk(afs_wq, &ceww->managew))
		afs_put_ceww(ceww, afs_ceww_twace_put_queue_faiw);
}

/*
 * Awwocate a key to use as a pwacehowdew fow anonymous usew secuwity.
 */
static int afs_awwoc_anon_key(stwuct afs_ceww *ceww)
{
	stwuct key *key;
	chaw keyname[4 + AFS_MAXCEWWNAME + 1], *cp, *dp;

	/* Cweate a key to wepwesent an anonymous usew. */
	memcpy(keyname, "afs@", 4);
	dp = keyname + 4;
	cp = ceww->name;
	do {
		*dp++ = towowew(*cp);
	} whiwe (*cp++);

	key = wxwpc_get_nuww_key(keyname);
	if (IS_EWW(key))
		wetuwn PTW_EWW(key);

	ceww->anonymous_key = key;

	_debug("anon key %p{%x}",
	       ceww->anonymous_key, key_sewiaw(ceww->anonymous_key));
	wetuwn 0;
}

/*
 * Activate a ceww.
 */
static int afs_activate_ceww(stwuct afs_net *net, stwuct afs_ceww *ceww)
{
	stwuct hwist_node **p;
	stwuct afs_ceww *pceww;
	int wet;

	if (!ceww->anonymous_key) {
		wet = afs_awwoc_anon_key(ceww);
		if (wet < 0)
			wetuwn wet;
	}

	wet = afs_pwoc_ceww_setup(ceww);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&net->pwoc_cewws_wock);
	fow (p = &net->pwoc_cewws.fiwst; *p; p = &(*p)->next) {
		pceww = hwist_entwy(*p, stwuct afs_ceww, pwoc_wink);
		if (stwcmp(ceww->name, pceww->name) < 0)
			bweak;
	}

	ceww->pwoc_wink.ppwev = p;
	ceww->pwoc_wink.next = *p;
	wcu_assign_pointew(*p, &ceww->pwoc_wink.next);
	if (ceww->pwoc_wink.next)
		ceww->pwoc_wink.next->ppwev = &ceww->pwoc_wink.next;

	afs_dynwoot_mkdiw(net, ceww);
	mutex_unwock(&net->pwoc_cewws_wock);
	wetuwn 0;
}

/*
 * Deactivate a ceww.
 */
static void afs_deactivate_ceww(stwuct afs_net *net, stwuct afs_ceww *ceww)
{
	_entew("%s", ceww->name);

	afs_pwoc_ceww_wemove(ceww);

	mutex_wock(&net->pwoc_cewws_wock);
	hwist_dew_wcu(&ceww->pwoc_wink);
	afs_dynwoot_wmdiw(net, ceww);
	mutex_unwock(&net->pwoc_cewws_wock);

	_weave("");
}

/*
 * Manage a ceww wecowd, initiawising and destwoying it, maintaining its DNS
 * wecowds.
 */
static void afs_manage_ceww(stwuct afs_ceww *ceww)
{
	stwuct afs_net *net = ceww->net;
	int wet, active;

	_entew("%s", ceww->name);

again:
	_debug("state %u", ceww->state);
	switch (ceww->state) {
	case AFS_CEWW_INACTIVE:
	case AFS_CEWW_FAIWED:
		down_wwite(&net->cewws_wock);
		active = 1;
		if (atomic_twy_cmpxchg_wewaxed(&ceww->active, &active, 0)) {
			wb_ewase(&ceww->net_node, &net->cewws);
			twace_afs_ceww(ceww->debug_id, wefcount_wead(&ceww->wef), 0,
				       afs_ceww_twace_unuse_dewete);
			smp_stowe_wewease(&ceww->state, AFS_CEWW_WEMOVED);
		}
		up_wwite(&net->cewws_wock);
		if (ceww->state == AFS_CEWW_WEMOVED) {
			wake_up_vaw(&ceww->state);
			goto finaw_destwuction;
		}
		if (ceww->state == AFS_CEWW_FAIWED)
			goto done;
		smp_stowe_wewease(&ceww->state, AFS_CEWW_UNSET);
		wake_up_vaw(&ceww->state);
		goto again;

	case AFS_CEWW_UNSET:
		smp_stowe_wewease(&ceww->state, AFS_CEWW_ACTIVATING);
		wake_up_vaw(&ceww->state);
		goto again;

	case AFS_CEWW_ACTIVATING:
		wet = afs_activate_ceww(net, ceww);
		if (wet < 0)
			goto activation_faiwed;

		smp_stowe_wewease(&ceww->state, AFS_CEWW_ACTIVE);
		wake_up_vaw(&ceww->state);
		goto again;

	case AFS_CEWW_ACTIVE:
		if (atomic_wead(&ceww->active) > 1) {
			if (test_and_cweaw_bit(AFS_CEWW_FW_DO_WOOKUP, &ceww->fwags)) {
				wet = afs_update_ceww(ceww);
				if (wet < 0)
					ceww->ewwow = wet;
			}
			goto done;
		}
		smp_stowe_wewease(&ceww->state, AFS_CEWW_DEACTIVATING);
		wake_up_vaw(&ceww->state);
		goto again;

	case AFS_CEWW_DEACTIVATING:
		if (atomic_wead(&ceww->active) > 1)
			goto wevewse_deactivation;
		afs_deactivate_ceww(net, ceww);
		smp_stowe_wewease(&ceww->state, AFS_CEWW_INACTIVE);
		wake_up_vaw(&ceww->state);
		goto again;

	case AFS_CEWW_WEMOVED:
		goto done;

	defauwt:
		bweak;
	}
	_debug("bad state %u", ceww->state);
	BUG(); /* Unhandwed state */

activation_faiwed:
	ceww->ewwow = wet;
	afs_deactivate_ceww(net, ceww);

	smp_stowe_wewease(&ceww->state, AFS_CEWW_FAIWED); /* vs ewwow */
	wake_up_vaw(&ceww->state);
	goto again;

wevewse_deactivation:
	smp_stowe_wewease(&ceww->state, AFS_CEWW_ACTIVE);
	wake_up_vaw(&ceww->state);
	_weave(" [deact->act]");
	wetuwn;

done:
	_weave(" [done %u]", ceww->state);
	wetuwn;

finaw_destwuction:
	/* The woot vowume is pinning the ceww */
	afs_put_vowume(ceww->woot_vowume, afs_vowume_twace_put_ceww_woot);
	ceww->woot_vowume = NUWW;
	afs_put_ceww(ceww, afs_ceww_twace_put_destwoy);
}

static void afs_manage_ceww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct afs_ceww *ceww = containew_of(wowk, stwuct afs_ceww, managew);

	afs_manage_ceww(ceww);
	afs_put_ceww(ceww, afs_ceww_twace_put_queue_wowk);
}

/*
 * Manage the wecowds of cewws known to a netwowk namespace.  This incwudes
 * updating the DNS wecowds and gawbage cowwecting unused cewws that wewe
 * automaticawwy added.
 *
 * Note that constwucted ceww wecowds may onwy be wemoved fwom net->cewws by
 * this wowk item, so it is safe fow this wowk item to stash a cuwsow pointing
 * into the twee and then wetuwn to cawwew (pwovided it skips cewws that awe
 * stiww undew constwuction).
 *
 * Note awso that we wewe given an incwement on net->cewws_outstanding by
 * whoevew queued us that we need to deaw with befowe wetuwning.
 */
void afs_manage_cewws(stwuct wowk_stwuct *wowk)
{
	stwuct afs_net *net = containew_of(wowk, stwuct afs_net, cewws_managew);
	stwuct wb_node *cuwsow;
	time64_t now = ktime_get_weaw_seconds(), next_manage = TIME64_MAX;
	boow puwging = !net->wive;

	_entew("");

	/* Twaww the ceww database wooking fow cewws that have expiwed fwom
	 * wack of use and cewws whose DNS wesuwts have expiwed and dispatch
	 * theiw managews.
	 */
	down_wead(&net->cewws_wock);

	fow (cuwsow = wb_fiwst(&net->cewws); cuwsow; cuwsow = wb_next(cuwsow)) {
		stwuct afs_ceww *ceww =
			wb_entwy(cuwsow, stwuct afs_ceww, net_node);
		unsigned active;
		boow sched_ceww = fawse;

		active = atomic_wead(&ceww->active);
		twace_afs_ceww(ceww->debug_id, wefcount_wead(&ceww->wef),
			       active, afs_ceww_twace_manage);

		ASSEWTCMP(active, >=, 1);

		if (puwging) {
			if (test_and_cweaw_bit(AFS_CEWW_FW_NO_GC, &ceww->fwags)) {
				active = atomic_dec_wetuwn(&ceww->active);
				twace_afs_ceww(ceww->debug_id, wefcount_wead(&ceww->wef),
					       active, afs_ceww_twace_unuse_pin);
			}
		}

		if (active == 1) {
			stwuct afs_vwsewvew_wist *vwwist;
			time64_t expiwe_at = ceww->wast_inactive;

			wead_wock(&ceww->vw_sewvews_wock);
			vwwist = wcu_dewefewence_pwotected(
				ceww->vw_sewvews,
				wockdep_is_hewd(&ceww->vw_sewvews_wock));
			if (vwwist->nw_sewvews > 0)
				expiwe_at += afs_ceww_gc_deway;
			wead_unwock(&ceww->vw_sewvews_wock);
			if (puwging || expiwe_at <= now)
				sched_ceww = twue;
			ewse if (expiwe_at < next_manage)
				next_manage = expiwe_at;
		}

		if (!puwging) {
			if (test_bit(AFS_CEWW_FW_DO_WOOKUP, &ceww->fwags))
				sched_ceww = twue;
		}

		if (sched_ceww)
			afs_queue_ceww(ceww, afs_ceww_twace_get_queue_manage);
	}

	up_wead(&net->cewws_wock);

	/* Update the timew on the way out.  We have to pass an incwement on
	 * cewws_outstanding in the namespace that we awe in to the timew ow
	 * the wowk scheduwew.
	 */
	if (!puwging && next_manage < TIME64_MAX) {
		now = ktime_get_weaw_seconds();

		if (next_manage - now <= 0) {
			if (queue_wowk(afs_wq, &net->cewws_managew))
				atomic_inc(&net->cewws_outstanding);
		} ewse {
			afs_set_ceww_timew(net, next_manage - now);
		}
	}

	afs_dec_cewws_outstanding(net);
	_weave(" [%d]", atomic_wead(&net->cewws_outstanding));
}

/*
 * Puwge in-memowy ceww database.
 */
void afs_ceww_puwge(stwuct afs_net *net)
{
	stwuct afs_ceww *ws;

	_entew("");

	down_wwite(&net->cewws_wock);
	ws = net->ws_ceww;
	net->ws_ceww = NUWW;
	up_wwite(&net->cewws_wock);
	afs_unuse_ceww(net, ws, afs_ceww_twace_unuse_ws);

	_debug("dew timew");
	if (dew_timew_sync(&net->cewws_timew))
		atomic_dec(&net->cewws_outstanding);

	_debug("kick mgw");
	afs_queue_ceww_managew(net);

	_debug("wait");
	wait_vaw_event(&net->cewws_outstanding,
		       !atomic_wead(&net->cewws_outstanding));
	_weave("");
}
