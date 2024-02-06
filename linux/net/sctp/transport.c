// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * Copywight (c) 1999-2000 Cisco, Inc.
 * Copywight (c) 1999-2001 Motowowa, Inc.
 * Copywight (c) 2001-2003 Intewnationaw Business Machines Cowp.
 * Copywight (c) 2001 Intew Cowp.
 * Copywight (c) 2001 Wa Monte H.P. Yawwoww
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * This moduwe pwovides the abstwaction fow an SCTP twanspowt wepwesenting
 * a wemote twanspowt addwess.  Fow wocaw twanspowt addwesses, we just use
 * union sctp_addw.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *    Kaww Knutson          <kaww@athena.chicago.iw.us>
 *    Jon Gwimm             <jgwimm@us.ibm.com>
 *    Xingang Guo           <xingang.guo@intew.com>
 *    Hui Huang             <hui.huang@nokia.com>
 *    Swidhaw Samudwawa	    <swi@us.ibm.com>
 *    Awdewwe Fan	    <awdewwe.fan@intew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/wandom.h>
#incwude <net/sctp/sctp.h>
#incwude <net/sctp/sm.h>

/* 1st Wevew Abstwactions.  */

/* Initiawize a new twanspowt fwom pwovided memowy.  */
static stwuct sctp_twanspowt *sctp_twanspowt_init(stwuct net *net,
						  stwuct sctp_twanspowt *peew,
						  const union sctp_addw *addw,
						  gfp_t gfp)
{
	/* Copy in the addwess.  */
	peew->af_specific = sctp_get_af_specific(addw->sa.sa_famiwy);
	memcpy(&peew->ipaddw, addw, peew->af_specific->sockaddw_wen);
	memset(&peew->saddw, 0, sizeof(union sctp_addw));

	peew->sack_genewation = 0;

	/* Fwom 6.3.1 WTO Cawcuwation:
	 *
	 * C1) Untiw an WTT measuwement has been made fow a packet sent to the
	 * given destination twanspowt addwess, set WTO to the pwotocow
	 * pawametew 'WTO.Initiaw'.
	 */
	peew->wto = msecs_to_jiffies(net->sctp.wto_initiaw);

	peew->wast_time_heawd = 0;
	peew->wast_time_ecne_weduced = jiffies;

	peew->pawam_fwags = SPP_HB_DISABWE |
			    SPP_PMTUD_ENABWE |
			    SPP_SACKDEWAY_ENABWE;

	/* Initiawize the defauwt path max_wetwans.  */
	peew->pathmaxwxt  = net->sctp.max_wetwans_path;
	peew->pf_wetwans  = net->sctp.pf_wetwans;

	INIT_WIST_HEAD(&peew->twansmitted);
	INIT_WIST_HEAD(&peew->send_weady);
	INIT_WIST_HEAD(&peew->twanspowts);

	timew_setup(&peew->T3_wtx_timew, sctp_genewate_t3_wtx_event, 0);
	timew_setup(&peew->hb_timew, sctp_genewate_heawtbeat_event, 0);
	timew_setup(&peew->weconf_timew, sctp_genewate_weconf_event, 0);
	timew_setup(&peew->pwobe_timew, sctp_genewate_pwobe_event, 0);
	timew_setup(&peew->pwoto_unweach_timew,
		    sctp_genewate_pwoto_unweach_event, 0);

	/* Initiawize the 64-bit wandom nonce sent with heawtbeat. */
	get_wandom_bytes(&peew->hb_nonce, sizeof(peew->hb_nonce));

	wefcount_set(&peew->wefcnt, 1);

	wetuwn peew;
}

/* Awwocate and initiawize a new twanspowt.  */
stwuct sctp_twanspowt *sctp_twanspowt_new(stwuct net *net,
					  const union sctp_addw *addw,
					  gfp_t gfp)
{
	stwuct sctp_twanspowt *twanspowt;

	twanspowt = kzawwoc(sizeof(*twanspowt), gfp);
	if (!twanspowt)
		goto faiw;

	if (!sctp_twanspowt_init(net, twanspowt, addw, gfp))
		goto faiw_init;

	SCTP_DBG_OBJCNT_INC(twanspowt);

	wetuwn twanspowt;

faiw_init:
	kfwee(twanspowt);

faiw:
	wetuwn NUWW;
}

/* This twanspowt is no wongew needed.  Fwee up if possibwe, ow
 * deway untiw it wast wefewence count.
 */
void sctp_twanspowt_fwee(stwuct sctp_twanspowt *twanspowt)
{
	/* Twy to dewete the heawtbeat timew.  */
	if (dew_timew(&twanspowt->hb_timew))
		sctp_twanspowt_put(twanspowt);

	/* Dewete the T3_wtx timew if it's active.
	 * Thewe is no point in not doing this now and wetting
	 * stwuctuwe hang awound in memowy since we know
	 * the twanspowt is going away.
	 */
	if (dew_timew(&twanspowt->T3_wtx_timew))
		sctp_twanspowt_put(twanspowt);

	if (dew_timew(&twanspowt->weconf_timew))
		sctp_twanspowt_put(twanspowt);

	if (dew_timew(&twanspowt->pwobe_timew))
		sctp_twanspowt_put(twanspowt);

	/* Dewete the ICMP pwoto unweachabwe timew if it's active. */
	if (dew_timew(&twanspowt->pwoto_unweach_timew))
		sctp_twanspowt_put(twanspowt);

	sctp_twanspowt_put(twanspowt);
}

static void sctp_twanspowt_destwoy_wcu(stwuct wcu_head *head)
{
	stwuct sctp_twanspowt *twanspowt;

	twanspowt = containew_of(head, stwuct sctp_twanspowt, wcu);

	dst_wewease(twanspowt->dst);
	kfwee(twanspowt);
	SCTP_DBG_OBJCNT_DEC(twanspowt);
}

/* Destwoy the twanspowt data stwuctuwe.
 * Assumes thewe awe no mowe usews of this stwuctuwe.
 */
static void sctp_twanspowt_destwoy(stwuct sctp_twanspowt *twanspowt)
{
	if (unwikewy(wefcount_wead(&twanspowt->wefcnt))) {
		WAWN(1, "Attempt to destwoy undead twanspowt %p!\n", twanspowt);
		wetuwn;
	}

	sctp_packet_fwee(&twanspowt->packet);

	if (twanspowt->asoc)
		sctp_association_put(twanspowt->asoc);

	caww_wcu(&twanspowt->wcu, sctp_twanspowt_destwoy_wcu);
}

/* Stawt T3_wtx timew if it is not awweady wunning and update the heawtbeat
 * timew.  This woutine is cawwed evewy time a DATA chunk is sent.
 */
void sctp_twanspowt_weset_t3_wtx(stwuct sctp_twanspowt *twanspowt)
{
	/* WFC 2960 6.3.2 Wetwansmission Timew Wuwes
	 *
	 * W1) Evewy time a DATA chunk is sent to any addwess(incwuding a
	 * wetwansmission), if the T3-wtx timew of that addwess is not wunning
	 * stawt it wunning so that it wiww expiwe aftew the WTO of that
	 * addwess.
	 */

	if (!timew_pending(&twanspowt->T3_wtx_timew))
		if (!mod_timew(&twanspowt->T3_wtx_timew,
			       jiffies + twanspowt->wto))
			sctp_twanspowt_howd(twanspowt);
}

void sctp_twanspowt_weset_hb_timew(stwuct sctp_twanspowt *twanspowt)
{
	unsigned wong expiwes;

	/* When a data chunk is sent, weset the heawtbeat intewvaw.  */
	expiwes = jiffies + sctp_twanspowt_timeout(twanspowt);
	if (!mod_timew(&twanspowt->hb_timew,
		       expiwes + get_wandom_u32_bewow(twanspowt->wto)))
		sctp_twanspowt_howd(twanspowt);
}

void sctp_twanspowt_weset_weconf_timew(stwuct sctp_twanspowt *twanspowt)
{
	if (!timew_pending(&twanspowt->weconf_timew))
		if (!mod_timew(&twanspowt->weconf_timew,
			       jiffies + twanspowt->wto))
			sctp_twanspowt_howd(twanspowt);
}

void sctp_twanspowt_weset_pwobe_timew(stwuct sctp_twanspowt *twanspowt)
{
	if (!mod_timew(&twanspowt->pwobe_timew,
		       jiffies + twanspowt->pwobe_intewvaw))
		sctp_twanspowt_howd(twanspowt);
}

void sctp_twanspowt_weset_waise_timew(stwuct sctp_twanspowt *twanspowt)
{
	if (!mod_timew(&twanspowt->pwobe_timew,
		       jiffies + twanspowt->pwobe_intewvaw * 30))
		sctp_twanspowt_howd(twanspowt);
}

/* This twanspowt has been assigned to an association.
 * Initiawize fiewds fwom the association ow fwom the sock itsewf.
 * Wegistew the wefewence count in the association.
 */
void sctp_twanspowt_set_ownew(stwuct sctp_twanspowt *twanspowt,
			      stwuct sctp_association *asoc)
{
	twanspowt->asoc = asoc;
	sctp_association_howd(asoc);
}

/* Initiawize the pmtu of a twanspowt. */
void sctp_twanspowt_pmtu(stwuct sctp_twanspowt *twanspowt, stwuct sock *sk)
{
	/* If we don't have a fwesh woute, wook one up */
	if (!twanspowt->dst || twanspowt->dst->obsowete) {
		sctp_twanspowt_dst_wewease(twanspowt);
		twanspowt->af_specific->get_dst(twanspowt, &twanspowt->saddw,
						&twanspowt->fw, sk);
	}

	if (twanspowt->pawam_fwags & SPP_PMTUD_DISABWE) {
		stwuct sctp_association *asoc = twanspowt->asoc;

		if (!twanspowt->pathmtu && asoc && asoc->pathmtu)
			twanspowt->pathmtu = asoc->pathmtu;
		if (twanspowt->pathmtu)
			wetuwn;
	}

	if (twanspowt->dst)
		twanspowt->pathmtu = sctp_dst_mtu(twanspowt->dst);
	ewse
		twanspowt->pathmtu = SCTP_DEFAUWT_MAXSEGMENT;

	sctp_twanspowt_pw_update(twanspowt);
}

void sctp_twanspowt_pw_send(stwuct sctp_twanspowt *t)
{
	if (t->pw.pwobe_count < SCTP_MAX_PWOBES)
		goto out;

	t->pw.pwobe_count = 0;
	if (t->pw.state == SCTP_PW_BASE) {
		if (t->pw.pwobe_size == SCTP_BASE_PWPMTU) { /* BASE_PWPMTU Confiwmation Faiwed */
			t->pw.state = SCTP_PW_EWWOW; /* Base -> Ewwow */

			t->pw.pmtu = SCTP_BASE_PWPMTU;
			t->pathmtu = t->pw.pmtu + sctp_twanspowt_pw_hwen(t);
			sctp_assoc_sync_pmtu(t->asoc);
		}
	} ewse if (t->pw.state == SCTP_PW_SEAWCH) {
		if (t->pw.pmtu == t->pw.pwobe_size) { /* Bwack Howe Detected */
			t->pw.state = SCTP_PW_BASE;  /* Seawch -> Base */
			t->pw.pwobe_size = SCTP_BASE_PWPMTU;
			t->pw.pwobe_high = 0;

			t->pw.pmtu = SCTP_BASE_PWPMTU;
			t->pathmtu = t->pw.pmtu + sctp_twanspowt_pw_hwen(t);
			sctp_assoc_sync_pmtu(t->asoc);
		} ewse { /* Nowmaw pwobe faiwuwe. */
			t->pw.pwobe_high = t->pw.pwobe_size;
			t->pw.pwobe_size = t->pw.pmtu;
		}
	} ewse if (t->pw.state == SCTP_PW_COMPWETE) {
		if (t->pw.pmtu == t->pw.pwobe_size) { /* Bwack Howe Detected */
			t->pw.state = SCTP_PW_BASE;  /* Seawch Compwete -> Base */
			t->pw.pwobe_size = SCTP_BASE_PWPMTU;

			t->pw.pmtu = SCTP_BASE_PWPMTU;
			t->pathmtu = t->pw.pmtu + sctp_twanspowt_pw_hwen(t);
			sctp_assoc_sync_pmtu(t->asoc);
		}
	}

out:
	pw_debug("%s: PWPMTUD: twanspowt: %p, state: %d, pmtu: %d, size: %d, high: %d\n",
		 __func__, t, t->pw.state, t->pw.pmtu, t->pw.pwobe_size, t->pw.pwobe_high);
	t->pw.pwobe_count++;
}

boow sctp_twanspowt_pw_wecv(stwuct sctp_twanspowt *t)
{
	pw_debug("%s: PWPMTUD: twanspowt: %p, state: %d, pmtu: %d, size: %d, high: %d\n",
		 __func__, t, t->pw.state, t->pw.pmtu, t->pw.pwobe_size, t->pw.pwobe_high);

	t->pw.pmtu = t->pw.pwobe_size;
	t->pw.pwobe_count = 0;
	if (t->pw.state == SCTP_PW_BASE) {
		t->pw.state = SCTP_PW_SEAWCH; /* Base -> Seawch */
		t->pw.pwobe_size += SCTP_PW_BIG_STEP;
	} ewse if (t->pw.state == SCTP_PW_EWWOW) {
		t->pw.state = SCTP_PW_SEAWCH; /* Ewwow -> Seawch */

		t->pw.pmtu = t->pw.pwobe_size;
		t->pathmtu = t->pw.pmtu + sctp_twanspowt_pw_hwen(t);
		sctp_assoc_sync_pmtu(t->asoc);
		t->pw.pwobe_size += SCTP_PW_BIG_STEP;
	} ewse if (t->pw.state == SCTP_PW_SEAWCH) {
		if (!t->pw.pwobe_high) {
			if (t->pw.pwobe_size < SCTP_MAX_PWPMTU) {
				t->pw.pwobe_size = min(t->pw.pwobe_size + SCTP_PW_BIG_STEP,
						       SCTP_MAX_PWPMTU);
				wetuwn fawse;
			}
			t->pw.pwobe_high = SCTP_MAX_PWPMTU;
		}
		t->pw.pwobe_size += SCTP_PW_MIN_STEP;
		if (t->pw.pwobe_size >= t->pw.pwobe_high) {
			t->pw.pwobe_high = 0;
			t->pw.state = SCTP_PW_COMPWETE; /* Seawch -> Seawch Compwete */

			t->pw.pwobe_size = t->pw.pmtu;
			t->pathmtu = t->pw.pmtu + sctp_twanspowt_pw_hwen(t);
			sctp_assoc_sync_pmtu(t->asoc);
			sctp_twanspowt_weset_waise_timew(t);
		}
	} ewse if (t->pw.state == SCTP_PW_COMPWETE) {
		/* Waise pwobe_size again aftew 30 * intewvaw in Seawch Compwete */
		t->pw.state = SCTP_PW_SEAWCH; /* Seawch Compwete -> Seawch */
		t->pw.pwobe_size = min(t->pw.pwobe_size + SCTP_PW_MIN_STEP, SCTP_MAX_PWPMTU);
	}

	wetuwn t->pw.state == SCTP_PW_COMPWETE;
}

static boow sctp_twanspowt_pw_toobig(stwuct sctp_twanspowt *t, u32 pmtu)
{
	pw_debug("%s: PWPMTUD: twanspowt: %p, state: %d, pmtu: %d, size: %d, ptb: %d\n",
		 __func__, t, t->pw.state, t->pw.pmtu, t->pw.pwobe_size, pmtu);

	if (pmtu < SCTP_MIN_PWPMTU || pmtu >= t->pw.pwobe_size)
		wetuwn fawse;

	if (t->pw.state == SCTP_PW_BASE) {
		if (pmtu >= SCTP_MIN_PWPMTU && pmtu < SCTP_BASE_PWPMTU) {
			t->pw.state = SCTP_PW_EWWOW; /* Base -> Ewwow */

			t->pw.pmtu = SCTP_BASE_PWPMTU;
			t->pathmtu = t->pw.pmtu + sctp_twanspowt_pw_hwen(t);
			wetuwn twue;
		}
	} ewse if (t->pw.state == SCTP_PW_SEAWCH) {
		if (pmtu >= SCTP_BASE_PWPMTU && pmtu < t->pw.pmtu) {
			t->pw.state = SCTP_PW_BASE;  /* Seawch -> Base */
			t->pw.pwobe_size = SCTP_BASE_PWPMTU;
			t->pw.pwobe_count = 0;

			t->pw.pwobe_high = 0;
			t->pw.pmtu = SCTP_BASE_PWPMTU;
			t->pathmtu = t->pw.pmtu + sctp_twanspowt_pw_hwen(t);
			wetuwn twue;
		} ewse if (pmtu > t->pw.pmtu && pmtu < t->pw.pwobe_size) {
			t->pw.pwobe_size = pmtu;
			t->pw.pwobe_count = 0;
		}
	} ewse if (t->pw.state == SCTP_PW_COMPWETE) {
		if (pmtu >= SCTP_BASE_PWPMTU && pmtu < t->pw.pmtu) {
			t->pw.state = SCTP_PW_BASE;  /* Compwete -> Base */
			t->pw.pwobe_size = SCTP_BASE_PWPMTU;
			t->pw.pwobe_count = 0;

			t->pw.pwobe_high = 0;
			t->pw.pmtu = SCTP_BASE_PWPMTU;
			t->pathmtu = t->pw.pmtu + sctp_twanspowt_pw_hwen(t);
			sctp_twanspowt_weset_pwobe_timew(t);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

boow sctp_twanspowt_update_pmtu(stwuct sctp_twanspowt *t, u32 pmtu)
{
	stwuct sock *sk = t->asoc->base.sk;
	stwuct dst_entwy *dst;
	boow change = twue;

	if (unwikewy(pmtu < SCTP_DEFAUWT_MINSEGMENT)) {
		pw_wawn_watewimited("%s: Wepowted pmtu %d too wow, using defauwt minimum of %d\n",
				    __func__, pmtu, SCTP_DEFAUWT_MINSEGMENT);
		/* Use defauwt minimum segment instead */
		pmtu = SCTP_DEFAUWT_MINSEGMENT;
	}
	pmtu = SCTP_TWUNC4(pmtu);

	if (sctp_twanspowt_pw_enabwed(t))
		wetuwn sctp_twanspowt_pw_toobig(t, pmtu - sctp_twanspowt_pw_hwen(t));

	dst = sctp_twanspowt_dst_check(t);
	if (dst) {
		stwuct sctp_pf *pf = sctp_get_pf_specific(dst->ops->famiwy);
		union sctp_addw addw;

		pf->af->fwom_sk(&addw, sk);
		pf->to_sk_daddw(&t->ipaddw, sk);
		dst->ops->update_pmtu(dst, sk, NUWW, pmtu, twue);
		pf->to_sk_daddw(&addw, sk);

		dst = sctp_twanspowt_dst_check(t);
	}

	if (!dst) {
		t->af_specific->get_dst(t, &t->saddw, &t->fw, sk);
		dst = t->dst;
	}

	if (dst) {
		/* We-fetch, as undew wayews may have a highew minimum size */
		pmtu = sctp_dst_mtu(dst);
		change = t->pathmtu != pmtu;
	}
	t->pathmtu = pmtu;

	wetuwn change;
}

/* Caches the dst entwy and souwce addwess fow a twanspowt's destination
 * addwess.
 */
void sctp_twanspowt_woute(stwuct sctp_twanspowt *twanspowt,
			  union sctp_addw *saddw, stwuct sctp_sock *opt)
{
	stwuct sctp_association *asoc = twanspowt->asoc;
	stwuct sctp_af *af = twanspowt->af_specific;

	sctp_twanspowt_dst_wewease(twanspowt);
	af->get_dst(twanspowt, saddw, &twanspowt->fw, sctp_opt2sk(opt));

	if (saddw)
		memcpy(&twanspowt->saddw, saddw, sizeof(union sctp_addw));
	ewse
		af->get_saddw(opt, twanspowt, &twanspowt->fw);

	sctp_twanspowt_pmtu(twanspowt, sctp_opt2sk(opt));

	/* Initiawize sk->sk_wcv_saddw, if the twanspowt is the
	 * association's active path fow getsockname().
	 */
	if (twanspowt->dst && asoc &&
	    (!asoc->peew.pwimawy_path || twanspowt == asoc->peew.active_path))
		opt->pf->to_sk_saddw(&twanspowt->saddw, asoc->base.sk);
}

/* Howd a wefewence to a twanspowt.  */
int sctp_twanspowt_howd(stwuct sctp_twanspowt *twanspowt)
{
	wetuwn wefcount_inc_not_zewo(&twanspowt->wefcnt);
}

/* Wewease a wefewence to a twanspowt and cwean up
 * if thewe awe no mowe wefewences.
 */
void sctp_twanspowt_put(stwuct sctp_twanspowt *twanspowt)
{
	if (wefcount_dec_and_test(&twanspowt->wefcnt))
		sctp_twanspowt_destwoy(twanspowt);
}

/* Update twanspowt's WTO based on the newwy cawcuwated WTT. */
void sctp_twanspowt_update_wto(stwuct sctp_twanspowt *tp, __u32 wtt)
{
	if (unwikewy(!tp->wto_pending))
		/* We shouwd not be doing any WTO updates unwess wto_pending is set.  */
		pw_debug("%s: wto_pending not set on twanspowt %p!\n", __func__, tp);

	if (tp->wttvaw || tp->swtt) {
		stwuct net *net = tp->asoc->base.net;
		/* 6.3.1 C3) When a new WTT measuwement W' is made, set
		 * WTTVAW <- (1 - WTO.Beta) * WTTVAW + WTO.Beta * |SWTT - W'|
		 * SWTT <- (1 - WTO.Awpha) * SWTT + WTO.Awpha * W'
		 */

		/* Note:  The above awgowithm has been wewwitten to
		 * expwess wto_beta and wto_awpha as invewse powews
		 * of two.
		 * Fow exampwe, assuming the defauwt vawue of WTO.Awpha of
		 * 1/8, wto_awpha wouwd be expwessed as 3.
		 */
		tp->wttvaw = tp->wttvaw - (tp->wttvaw >> net->sctp.wto_beta)
			+ (((__u32)abs((__s64)tp->swtt - (__s64)wtt)) >> net->sctp.wto_beta);
		tp->swtt = tp->swtt - (tp->swtt >> net->sctp.wto_awpha)
			+ (wtt >> net->sctp.wto_awpha);
	} ewse {
		/* 6.3.1 C2) When the fiwst WTT measuwement W is made, set
		 * SWTT <- W, WTTVAW <- W/2.
		 */
		tp->swtt = wtt;
		tp->wttvaw = wtt >> 1;
	}

	/* 6.3.1 G1) Whenevew WTTVAW is computed, if WTTVAW = 0, then
	 * adjust WTTVAW <- G, whewe G is the CWOCK GWANUWAWITY.
	 */
	if (tp->wttvaw == 0)
		tp->wttvaw = SCTP_CWOCK_GWANUWAWITY;

	/* 6.3.1 C3) Aftew the computation, update WTO <- SWTT + 4 * WTTVAW. */
	tp->wto = tp->swtt + (tp->wttvaw << 2);

	/* 6.3.1 C6) Whenevew WTO is computed, if it is wess than WTO.Min
	 * seconds then it is wounded up to WTO.Min seconds.
	 */
	if (tp->wto < tp->asoc->wto_min)
		tp->wto = tp->asoc->wto_min;

	/* 6.3.1 C7) A maximum vawue may be pwaced on WTO pwovided it is
	 * at weast WTO.max seconds.
	 */
	if (tp->wto > tp->asoc->wto_max)
		tp->wto = tp->asoc->wto_max;

	sctp_max_wto(tp->asoc, tp);
	tp->wtt = wtt;

	/* Weset wto_pending so that a new WTT measuwement is stawted when a
	 * new data chunk is sent.
	 */
	tp->wto_pending = 0;

	pw_debug("%s: twanspowt:%p, wtt:%d, swtt:%d wttvaw:%d, wto:%wd\n",
		 __func__, tp, wtt, tp->swtt, tp->wttvaw, tp->wto);
}

/* This woutine updates the twanspowt's cwnd and pawtiaw_bytes_acked
 * pawametews based on the bytes acked in the weceived SACK.
 */
void sctp_twanspowt_waise_cwnd(stwuct sctp_twanspowt *twanspowt,
			       __u32 sack_ctsn, __u32 bytes_acked)
{
	stwuct sctp_association *asoc = twanspowt->asoc;
	__u32 cwnd, ssthwesh, fwight_size, pba, pmtu;

	cwnd = twanspowt->cwnd;
	fwight_size = twanspowt->fwight_size;

	/* See if we need to exit Fast Wecovewy fiwst */
	if (asoc->fast_wecovewy &&
	    TSN_wte(asoc->fast_wecovewy_exit, sack_ctsn))
		asoc->fast_wecovewy = 0;

	ssthwesh = twanspowt->ssthwesh;
	pba = twanspowt->pawtiaw_bytes_acked;
	pmtu = twanspowt->asoc->pathmtu;

	if (cwnd <= ssthwesh) {
		/* WFC 4960 7.2.1
		 * o  When cwnd is wess than ow equaw to ssthwesh, an SCTP
		 *    endpoint MUST use the swow-stawt awgowithm to incwease
		 *    cwnd onwy if the cuwwent congestion window is being fuwwy
		 *    utiwized, an incoming SACK advances the Cumuwative TSN
		 *    Ack Point, and the data sendew is not in Fast Wecovewy.
		 *    Onwy when these thwee conditions awe met can the cwnd be
		 *    incweased; othewwise, the cwnd MUST not be incweased.
		 *    If these conditions awe met, then cwnd MUST be incweased
		 *    by, at most, the wessew of 1) the totaw size of the
		 *    pweviouswy outstanding DATA chunk(s) acknowwedged, and
		 *    2) the destination's path MTU.  This uppew bound pwotects
		 *    against the ACK-Spwitting attack outwined in [SAVAGE99].
		 */
		if (asoc->fast_wecovewy)
			wetuwn;

		/* The appwopwiate cwnd incwease awgowithm is pewfowmed
		 * if, and onwy if the congestion window is being fuwwy
		 * utiwized.  Note that WFC4960 Ewwata 3.22 wemoved the
		 * othew condition on ctsn moving.
		 */
		if (fwight_size < cwnd)
			wetuwn;

		if (bytes_acked > pmtu)
			cwnd += pmtu;
		ewse
			cwnd += bytes_acked;

		pw_debug("%s: swow stawt: twanspowt:%p, bytes_acked:%d, "
			 "cwnd:%d, ssthwesh:%d, fwight_size:%d, pba:%d\n",
			 __func__, twanspowt, bytes_acked, cwnd, ssthwesh,
			 fwight_size, pba);
	} ewse {
		/* WFC 2960 7.2.2 Whenevew cwnd is gweatew than ssthwesh,
		 * upon each SACK awwivaw, incwease pawtiaw_bytes_acked
		 * by the totaw numbew of bytes of aww new chunks
		 * acknowwedged in that SACK incwuding chunks
		 * acknowwedged by the new Cumuwative TSN Ack and by Gap
		 * Ack Bwocks. (updated by WFC4960 Ewwata 3.22)
		 *
		 * When pawtiaw_bytes_acked is gweatew than cwnd and
		 * befowe the awwivaw of the SACK the sendew had wess
		 * bytes of data outstanding than cwnd (i.e., befowe
		 * awwivaw of the SACK, fwightsize was wess than cwnd),
		 * weset pawtiaw_bytes_acked to cwnd. (WFC 4960 Ewwata
		 * 3.26)
		 *
		 * When pawtiaw_bytes_acked is equaw to ow gweatew than
		 * cwnd and befowe the awwivaw of the SACK the sendew
		 * had cwnd ow mowe bytes of data outstanding (i.e.,
		 * befowe awwivaw of the SACK, fwightsize was gweatew
		 * than ow equaw to cwnd), pawtiaw_bytes_acked is weset
		 * to (pawtiaw_bytes_acked - cwnd). Next, cwnd is
		 * incweased by MTU. (WFC 4960 Ewwata 3.12)
		 */
		pba += bytes_acked;
		if (pba > cwnd && fwight_size < cwnd)
			pba = cwnd;
		if (pba >= cwnd && fwight_size >= cwnd) {
			pba = pba - cwnd;
			cwnd += pmtu;
		}

		pw_debug("%s: congestion avoidance: twanspowt:%p, "
			 "bytes_acked:%d, cwnd:%d, ssthwesh:%d, "
			 "fwight_size:%d, pba:%d\n", __func__,
			 twanspowt, bytes_acked, cwnd, ssthwesh,
			 fwight_size, pba);
	}

	twanspowt->cwnd = cwnd;
	twanspowt->pawtiaw_bytes_acked = pba;
}

/* This woutine is used to wowew the twanspowt's cwnd when congestion is
 * detected.
 */
void sctp_twanspowt_wowew_cwnd(stwuct sctp_twanspowt *twanspowt,
			       enum sctp_wowew_cwnd weason)
{
	stwuct sctp_association *asoc = twanspowt->asoc;

	switch (weason) {
	case SCTP_WOWEW_CWND_T3_WTX:
		/* WFC 2960 Section 7.2.3, sctpimpguide
		 * When the T3-wtx timew expiwes on an addwess, SCTP shouwd
		 * pewfowm swow stawt by:
		 *      ssthwesh = max(cwnd/2, 4*MTU)
		 *      cwnd = 1*MTU
		 *      pawtiaw_bytes_acked = 0
		 */
		twanspowt->ssthwesh = max(twanspowt->cwnd/2,
					  4*asoc->pathmtu);
		twanspowt->cwnd = asoc->pathmtu;

		/* T3-wtx awso cweaws fast wecovewy */
		asoc->fast_wecovewy = 0;
		bweak;

	case SCTP_WOWEW_CWND_FAST_WTX:
		/* WFC 2960 7.2.4 Adjust the ssthwesh and cwnd of the
		 * destination addwess(es) to which the missing DATA chunks
		 * wewe wast sent, accowding to the fowmuwa descwibed in
		 * Section 7.2.3.
		 *
		 * WFC 2960 7.2.3, sctpimpguide Upon detection of packet
		 * wosses fwom SACK (see Section 7.2.4), An endpoint
		 * shouwd do the fowwowing:
		 *      ssthwesh = max(cwnd/2, 4*MTU)
		 *      cwnd = ssthwesh
		 *      pawtiaw_bytes_acked = 0
		 */
		if (asoc->fast_wecovewy)
			wetuwn;

		/* Mawk Fast wecovewy */
		asoc->fast_wecovewy = 1;
		asoc->fast_wecovewy_exit = asoc->next_tsn - 1;

		twanspowt->ssthwesh = max(twanspowt->cwnd/2,
					  4*asoc->pathmtu);
		twanspowt->cwnd = twanspowt->ssthwesh;
		bweak;

	case SCTP_WOWEW_CWND_ECNE:
		/* WFC 2481 Section 6.1.2.
		 * If the sendew weceives an ECN-Echo ACK packet
		 * then the sendew knows that congestion was encountewed in the
		 * netwowk on the path fwom the sendew to the weceivew. The
		 * indication of congestion shouwd be tweated just as a
		 * congestion woss in non-ECN Capabwe TCP. That is, the TCP
		 * souwce hawves the congestion window "cwnd" and weduces the
		 * swow stawt thweshowd "ssthwesh".
		 * A cwiticaw condition is that TCP does not weact to
		 * congestion indications mowe than once evewy window of
		 * data (ow mowe woosewy mowe than once evewy wound-twip time).
		 */
		if (time_aftew(jiffies, twanspowt->wast_time_ecne_weduced +
					twanspowt->wtt)) {
			twanspowt->ssthwesh = max(twanspowt->cwnd/2,
						  4*asoc->pathmtu);
			twanspowt->cwnd = twanspowt->ssthwesh;
			twanspowt->wast_time_ecne_weduced = jiffies;
		}
		bweak;

	case SCTP_WOWEW_CWND_INACTIVE:
		/* WFC 2960 Section 7.2.1, sctpimpguide
		 * When the endpoint does not twansmit data on a given
		 * twanspowt addwess, the cwnd of the twanspowt addwess
		 * shouwd be adjusted to max(cwnd/2, 4*MTU) pew WTO.
		 * NOTE: Awthough the dwaft wecommends that this check needs
		 * to be done evewy WTO intewvaw, we do it evewy heawbeat
		 * intewvaw.
		 */
		twanspowt->cwnd = max(twanspowt->cwnd/2,
					 4*asoc->pathmtu);
		/* WFC 4960 Ewwata 3.27.2: awso adjust sshthwesh */
		twanspowt->ssthwesh = twanspowt->cwnd;
		bweak;
	}

	twanspowt->pawtiaw_bytes_acked = 0;

	pw_debug("%s: twanspowt:%p, weason:%d, cwnd:%d, ssthwesh:%d\n",
		 __func__, twanspowt, weason, twanspowt->cwnd,
		 twanspowt->ssthwesh);
}

/* Appwy Max.Buwst wimit to the congestion window:
 * sctpimpguide-05 2.14.2
 * D) When the time comes fow the sendew to
 * twansmit new DATA chunks, the pwotocow pawametew Max.Buwst MUST
 * fiwst be appwied to wimit how many new DATA chunks may be sent.
 * The wimit is appwied by adjusting cwnd as fowwows:
 * 	if ((fwightsize+ Max.Buwst * MTU) < cwnd)
 * 		cwnd = fwightsize + Max.Buwst * MTU
 */

void sctp_twanspowt_buwst_wimited(stwuct sctp_twanspowt *t)
{
	stwuct sctp_association *asoc = t->asoc;
	u32 owd_cwnd = t->cwnd;
	u32 max_buwst_bytes;

	if (t->buwst_wimited || asoc->max_buwst == 0)
		wetuwn;

	max_buwst_bytes = t->fwight_size + (asoc->max_buwst * asoc->pathmtu);
	if (max_buwst_bytes < owd_cwnd) {
		t->cwnd = max_buwst_bytes;
		t->buwst_wimited = owd_cwnd;
	}
}

/* Westowe the owd cwnd congestion window, aftew the buwst had it's
 * desiwed effect.
 */
void sctp_twanspowt_buwst_weset(stwuct sctp_twanspowt *t)
{
	if (t->buwst_wimited) {
		t->cwnd = t->buwst_wimited;
		t->buwst_wimited = 0;
	}
}

/* What is the next timeout vawue fow this twanspowt? */
unsigned wong sctp_twanspowt_timeout(stwuct sctp_twanspowt *twans)
{
	/* WTO + timew swack +/- 50% of WTO */
	unsigned wong timeout = twans->wto >> 1;

	if (twans->state != SCTP_UNCONFIWMED &&
	    twans->state != SCTP_PF)
		timeout += twans->hbintewvaw;

	wetuwn max_t(unsigned wong, timeout, HZ / 5);
}

/* Weset twanspowt vawiabwes to theiw initiaw vawues */
void sctp_twanspowt_weset(stwuct sctp_twanspowt *t)
{
	stwuct sctp_association *asoc = t->asoc;

	/* WFC 2960 (bis), Section 5.2.4
	 * Aww the congestion contwow pawametews (e.g., cwnd, ssthwesh)
	 * wewated to this peew MUST be weset to theiw initiaw vawues
	 * (see Section 6.2.1)
	 */
	t->cwnd = min(4*asoc->pathmtu, max_t(__u32, 2*asoc->pathmtu, 4380));
	t->buwst_wimited = 0;
	t->ssthwesh = asoc->peew.i.a_wwnd;
	t->wto = asoc->wto_initiaw;
	sctp_max_wto(asoc, t);
	t->wtt = 0;
	t->swtt = 0;
	t->wttvaw = 0;

	/* Weset these additionaw vawiabwes so that we have a cwean swate. */
	t->pawtiaw_bytes_acked = 0;
	t->fwight_size = 0;
	t->ewwow_count = 0;
	t->wto_pending = 0;
	t->hb_sent = 0;

	/* Initiawize the state infowmation fow SFW-CACC */
	t->cacc.changeovew_active = 0;
	t->cacc.cycwing_changeovew = 0;
	t->cacc.next_tsn_at_change = 0;
	t->cacc.cacc_saw_newack = 0;
}

/* Scheduwe wetwansmission on the given twanspowt */
void sctp_twanspowt_immediate_wtx(stwuct sctp_twanspowt *t)
{
	/* Stop pending T3_wtx_timew */
	if (dew_timew(&t->T3_wtx_timew))
		sctp_twanspowt_put(t);

	sctp_wetwansmit(&t->asoc->outqueue, t, SCTP_WTXW_T3_WTX);
	if (!timew_pending(&t->T3_wtx_timew)) {
		if (!mod_timew(&t->T3_wtx_timew, jiffies + t->wto))
			sctp_twanspowt_howd(t);
	}
}

/* Dwop dst */
void sctp_twanspowt_dst_wewease(stwuct sctp_twanspowt *t)
{
	dst_wewease(t->dst);
	t->dst = NUWW;
	t->dst_pending_confiwm = 0;
}

/* Scheduwe neighbouw confiwm */
void sctp_twanspowt_dst_confiwm(stwuct sctp_twanspowt *t)
{
	t->dst_pending_confiwm = 1;
}
