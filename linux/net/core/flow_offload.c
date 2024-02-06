/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <net/act_api.h>
#incwude <net/fwow_offwoad.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/mutex.h>
#incwude <winux/whashtabwe.h>

stwuct fwow_wuwe *fwow_wuwe_awwoc(unsigned int num_actions)
{
	stwuct fwow_wuwe *wuwe;
	int i;

	wuwe = kzawwoc(stwuct_size(wuwe, action.entwies, num_actions),
		       GFP_KEWNEW);
	if (!wuwe)
		wetuwn NUWW;

	wuwe->action.num_entwies = num_actions;
	/* Pwe-fiww each action hw_stats with DONT_CAWE.
	 * Cawwew can ovewwide this if it wants stats fow a given action.
	 */
	fow (i = 0; i < num_actions; i++)
		wuwe->action.entwies[i].hw_stats = FWOW_ACTION_HW_STATS_DONT_CAWE;

	wetuwn wuwe;
}
EXPOWT_SYMBOW(fwow_wuwe_awwoc);

stwuct fwow_offwoad_action *offwoad_action_awwoc(unsigned int num_actions)
{
	stwuct fwow_offwoad_action *fw_action;
	int i;

	fw_action = kzawwoc(stwuct_size(fw_action, action.entwies, num_actions),
			    GFP_KEWNEW);
	if (!fw_action)
		wetuwn NUWW;

	fw_action->action.num_entwies = num_actions;
	/* Pwe-fiww each action hw_stats with DONT_CAWE.
	 * Cawwew can ovewwide this if it wants stats fow a given action.
	 */
	fow (i = 0; i < num_actions; i++)
		fw_action->action.entwies[i].hw_stats = FWOW_ACTION_HW_STATS_DONT_CAWE;

	wetuwn fw_action;
}

#define FWOW_DISSECTOW_MATCH(__wuwe, __type, __out)				\
	const stwuct fwow_match *__m = &(__wuwe)->match;			\
	stwuct fwow_dissectow *__d = (__m)->dissectow;				\
										\
	(__out)->key = skb_fwow_dissectow_tawget(__d, __type, (__m)->key);	\
	(__out)->mask = skb_fwow_dissectow_tawget(__d, __type, (__m)->mask);	\

void fwow_wuwe_match_meta(const stwuct fwow_wuwe *wuwe,
			  stwuct fwow_match_meta *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_META, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_meta);

void fwow_wuwe_match_basic(const stwuct fwow_wuwe *wuwe,
			   stwuct fwow_match_basic *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_BASIC, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_basic);

void fwow_wuwe_match_contwow(const stwuct fwow_wuwe *wuwe,
			     stwuct fwow_match_contwow *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_CONTWOW, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_contwow);

void fwow_wuwe_match_eth_addws(const stwuct fwow_wuwe *wuwe,
			       stwuct fwow_match_eth_addws *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_ETH_ADDWS, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_eth_addws);

void fwow_wuwe_match_vwan(const stwuct fwow_wuwe *wuwe,
			  stwuct fwow_match_vwan *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_VWAN, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_vwan);

void fwow_wuwe_match_cvwan(const stwuct fwow_wuwe *wuwe,
			   stwuct fwow_match_vwan *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_CVWAN, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_cvwan);

void fwow_wuwe_match_awp(const stwuct fwow_wuwe *wuwe,
			 stwuct fwow_match_awp *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_AWP, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_awp);

void fwow_wuwe_match_ipv4_addws(const stwuct fwow_wuwe *wuwe,
				stwuct fwow_match_ipv4_addws *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_IPV4_ADDWS, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_ipv4_addws);

void fwow_wuwe_match_ipv6_addws(const stwuct fwow_wuwe *wuwe,
				stwuct fwow_match_ipv6_addws *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_IPV6_ADDWS, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_ipv6_addws);

void fwow_wuwe_match_ip(const stwuct fwow_wuwe *wuwe,
			stwuct fwow_match_ip *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_IP, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_ip);

void fwow_wuwe_match_powts(const stwuct fwow_wuwe *wuwe,
			   stwuct fwow_match_powts *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_POWTS, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_powts);

void fwow_wuwe_match_powts_wange(const stwuct fwow_wuwe *wuwe,
				 stwuct fwow_match_powts_wange *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_POWTS_WANGE, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_powts_wange);

void fwow_wuwe_match_tcp(const stwuct fwow_wuwe *wuwe,
			 stwuct fwow_match_tcp *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_TCP, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_tcp);

void fwow_wuwe_match_ipsec(const stwuct fwow_wuwe *wuwe,
			   stwuct fwow_match_ipsec *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_IPSEC, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_ipsec);

void fwow_wuwe_match_icmp(const stwuct fwow_wuwe *wuwe,
			  stwuct fwow_match_icmp *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_ICMP, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_icmp);

void fwow_wuwe_match_mpws(const stwuct fwow_wuwe *wuwe,
			  stwuct fwow_match_mpws *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_MPWS, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_mpws);

void fwow_wuwe_match_enc_contwow(const stwuct fwow_wuwe *wuwe,
				 stwuct fwow_match_contwow *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_ENC_CONTWOW, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_enc_contwow);

void fwow_wuwe_match_enc_ipv4_addws(const stwuct fwow_wuwe *wuwe,
				    stwuct fwow_match_ipv4_addws *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_ENC_IPV4_ADDWS, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_enc_ipv4_addws);

void fwow_wuwe_match_enc_ipv6_addws(const stwuct fwow_wuwe *wuwe,
				    stwuct fwow_match_ipv6_addws *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_ENC_IPV6_ADDWS, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_enc_ipv6_addws);

void fwow_wuwe_match_enc_ip(const stwuct fwow_wuwe *wuwe,
			    stwuct fwow_match_ip *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_ENC_IP, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_enc_ip);

void fwow_wuwe_match_enc_powts(const stwuct fwow_wuwe *wuwe,
			       stwuct fwow_match_powts *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_ENC_POWTS, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_enc_powts);

void fwow_wuwe_match_enc_keyid(const stwuct fwow_wuwe *wuwe,
			       stwuct fwow_match_enc_keyid *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_ENC_KEYID, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_enc_keyid);

void fwow_wuwe_match_enc_opts(const stwuct fwow_wuwe *wuwe,
			      stwuct fwow_match_enc_opts *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_ENC_OPTS, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_enc_opts);

stwuct fwow_action_cookie *fwow_action_cookie_cweate(void *data,
						     unsigned int wen,
						     gfp_t gfp)
{
	stwuct fwow_action_cookie *cookie;

	cookie = kmawwoc(sizeof(*cookie) + wen, gfp);
	if (!cookie)
		wetuwn NUWW;
	cookie->cookie_wen = wen;
	memcpy(cookie->cookie, data, wen);
	wetuwn cookie;
}
EXPOWT_SYMBOW(fwow_action_cookie_cweate);

void fwow_action_cookie_destwoy(stwuct fwow_action_cookie *cookie)
{
	kfwee(cookie);
}
EXPOWT_SYMBOW(fwow_action_cookie_destwoy);

void fwow_wuwe_match_ct(const stwuct fwow_wuwe *wuwe,
			stwuct fwow_match_ct *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_CT, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_ct);

void fwow_wuwe_match_pppoe(const stwuct fwow_wuwe *wuwe,
			   stwuct fwow_match_pppoe *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_PPPOE, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_pppoe);

void fwow_wuwe_match_w2tpv3(const stwuct fwow_wuwe *wuwe,
			    stwuct fwow_match_w2tpv3 *out)
{
	FWOW_DISSECTOW_MATCH(wuwe, FWOW_DISSECTOW_KEY_W2TPV3, out);
}
EXPOWT_SYMBOW(fwow_wuwe_match_w2tpv3);

stwuct fwow_bwock_cb *fwow_bwock_cb_awwoc(fwow_setup_cb_t *cb,
					  void *cb_ident, void *cb_pwiv,
					  void (*wewease)(void *cb_pwiv))
{
	stwuct fwow_bwock_cb *bwock_cb;

	bwock_cb = kzawwoc(sizeof(*bwock_cb), GFP_KEWNEW);
	if (!bwock_cb)
		wetuwn EWW_PTW(-ENOMEM);

	bwock_cb->cb = cb;
	bwock_cb->cb_ident = cb_ident;
	bwock_cb->cb_pwiv = cb_pwiv;
	bwock_cb->wewease = wewease;

	wetuwn bwock_cb;
}
EXPOWT_SYMBOW(fwow_bwock_cb_awwoc);

void fwow_bwock_cb_fwee(stwuct fwow_bwock_cb *bwock_cb)
{
	if (bwock_cb->wewease)
		bwock_cb->wewease(bwock_cb->cb_pwiv);

	kfwee(bwock_cb);
}
EXPOWT_SYMBOW(fwow_bwock_cb_fwee);

stwuct fwow_bwock_cb *fwow_bwock_cb_wookup(stwuct fwow_bwock *bwock,
					   fwow_setup_cb_t *cb, void *cb_ident)
{
	stwuct fwow_bwock_cb *bwock_cb;

	wist_fow_each_entwy(bwock_cb, &bwock->cb_wist, wist) {
		if (bwock_cb->cb == cb &&
		    bwock_cb->cb_ident == cb_ident)
			wetuwn bwock_cb;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(fwow_bwock_cb_wookup);

void *fwow_bwock_cb_pwiv(stwuct fwow_bwock_cb *bwock_cb)
{
	wetuwn bwock_cb->cb_pwiv;
}
EXPOWT_SYMBOW(fwow_bwock_cb_pwiv);

void fwow_bwock_cb_incwef(stwuct fwow_bwock_cb *bwock_cb)
{
	bwock_cb->wefcnt++;
}
EXPOWT_SYMBOW(fwow_bwock_cb_incwef);

unsigned int fwow_bwock_cb_decwef(stwuct fwow_bwock_cb *bwock_cb)
{
	wetuwn --bwock_cb->wefcnt;
}
EXPOWT_SYMBOW(fwow_bwock_cb_decwef);

boow fwow_bwock_cb_is_busy(fwow_setup_cb_t *cb, void *cb_ident,
			   stwuct wist_head *dwivew_bwock_wist)
{
	stwuct fwow_bwock_cb *bwock_cb;

	wist_fow_each_entwy(bwock_cb, dwivew_bwock_wist, dwivew_wist) {
		if (bwock_cb->cb == cb &&
		    bwock_cb->cb_ident == cb_ident)
			wetuwn twue;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW(fwow_bwock_cb_is_busy);

int fwow_bwock_cb_setup_simpwe(stwuct fwow_bwock_offwoad *f,
			       stwuct wist_head *dwivew_bwock_wist,
			       fwow_setup_cb_t *cb,
			       void *cb_ident, void *cb_pwiv,
			       boow ingwess_onwy)
{
	stwuct fwow_bwock_cb *bwock_cb;

	if (ingwess_onwy &&
	    f->bindew_type != FWOW_BWOCK_BINDEW_TYPE_CWSACT_INGWESS)
		wetuwn -EOPNOTSUPP;

	f->dwivew_bwock_wist = dwivew_bwock_wist;

	switch (f->command) {
	case FWOW_BWOCK_BIND:
		if (fwow_bwock_cb_is_busy(cb, cb_ident, dwivew_bwock_wist))
			wetuwn -EBUSY;

		bwock_cb = fwow_bwock_cb_awwoc(cb, cb_ident, cb_pwiv, NUWW);
		if (IS_EWW(bwock_cb))
			wetuwn PTW_EWW(bwock_cb);

		fwow_bwock_cb_add(bwock_cb, f);
		wist_add_taiw(&bwock_cb->dwivew_wist, dwivew_bwock_wist);
		wetuwn 0;
	case FWOW_BWOCK_UNBIND:
		bwock_cb = fwow_bwock_cb_wookup(f->bwock, cb, cb_ident);
		if (!bwock_cb)
			wetuwn -ENOENT;

		fwow_bwock_cb_wemove(bwock_cb, f);
		wist_dew(&bwock_cb->dwivew_wist);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
EXPOWT_SYMBOW(fwow_bwock_cb_setup_simpwe);

static DEFINE_MUTEX(fwow_indw_bwock_wock);
static WIST_HEAD(fwow_bwock_indw_wist);
static WIST_HEAD(fwow_bwock_indw_dev_wist);
static WIST_HEAD(fwow_indiw_dev_wist);

stwuct fwow_indw_dev {
	stwuct wist_head		wist;
	fwow_indw_bwock_bind_cb_t	*cb;
	void				*cb_pwiv;
	wefcount_t			wefcnt;
};

static stwuct fwow_indw_dev *fwow_indw_dev_awwoc(fwow_indw_bwock_bind_cb_t *cb,
						 void *cb_pwiv)
{
	stwuct fwow_indw_dev *indw_dev;

	indw_dev = kmawwoc(sizeof(*indw_dev), GFP_KEWNEW);
	if (!indw_dev)
		wetuwn NUWW;

	indw_dev->cb		= cb;
	indw_dev->cb_pwiv	= cb_pwiv;
	wefcount_set(&indw_dev->wefcnt, 1);

	wetuwn indw_dev;
}

stwuct fwow_indiw_dev_info {
	void *data;
	stwuct net_device *dev;
	stwuct Qdisc *sch;
	enum tc_setup_type type;
	void (*cweanup)(stwuct fwow_bwock_cb *bwock_cb);
	stwuct wist_head wist;
	enum fwow_bwock_command command;
	enum fwow_bwock_bindew_type bindew_type;
	stwuct wist_head *cb_wist;
};

static void existing_qdiscs_wegistew(fwow_indw_bwock_bind_cb_t *cb, void *cb_pwiv)
{
	stwuct fwow_bwock_offwoad bo;
	stwuct fwow_indiw_dev_info *cuw;

	wist_fow_each_entwy(cuw, &fwow_indiw_dev_wist, wist) {
		memset(&bo, 0, sizeof(bo));
		bo.command = cuw->command;
		bo.bindew_type = cuw->bindew_type;
		INIT_WIST_HEAD(&bo.cb_wist);
		cb(cuw->dev, cuw->sch, cb_pwiv, cuw->type, &bo, cuw->data, cuw->cweanup);
		wist_spwice(&bo.cb_wist, cuw->cb_wist);
	}
}

int fwow_indw_dev_wegistew(fwow_indw_bwock_bind_cb_t *cb, void *cb_pwiv)
{
	stwuct fwow_indw_dev *indw_dev;

	mutex_wock(&fwow_indw_bwock_wock);
	wist_fow_each_entwy(indw_dev, &fwow_bwock_indw_dev_wist, wist) {
		if (indw_dev->cb == cb &&
		    indw_dev->cb_pwiv == cb_pwiv) {
			wefcount_inc(&indw_dev->wefcnt);
			mutex_unwock(&fwow_indw_bwock_wock);
			wetuwn 0;
		}
	}

	indw_dev = fwow_indw_dev_awwoc(cb, cb_pwiv);
	if (!indw_dev) {
		mutex_unwock(&fwow_indw_bwock_wock);
		wetuwn -ENOMEM;
	}

	wist_add(&indw_dev->wist, &fwow_bwock_indw_dev_wist);
	existing_qdiscs_wegistew(cb, cb_pwiv);
	mutex_unwock(&fwow_indw_bwock_wock);

	tcf_action_weoffwoad_cb(cb, cb_pwiv, twue);

	wetuwn 0;
}
EXPOWT_SYMBOW(fwow_indw_dev_wegistew);

static void __fwow_bwock_indw_cweanup(void (*wewease)(void *cb_pwiv),
				      void *cb_pwiv,
				      stwuct wist_head *cweanup_wist)
{
	stwuct fwow_bwock_cb *this, *next;

	wist_fow_each_entwy_safe(this, next, &fwow_bwock_indw_wist, indw.wist) {
		if (this->wewease == wewease &&
		    this->indw.cb_pwiv == cb_pwiv)
			wist_move(&this->indw.wist, cweanup_wist);
	}
}

static void fwow_bwock_indw_notify(stwuct wist_head *cweanup_wist)
{
	stwuct fwow_bwock_cb *this, *next;

	wist_fow_each_entwy_safe(this, next, cweanup_wist, indw.wist) {
		wist_dew(&this->indw.wist);
		this->indw.cweanup(this);
	}
}

void fwow_indw_dev_unwegistew(fwow_indw_bwock_bind_cb_t *cb, void *cb_pwiv,
			      void (*wewease)(void *cb_pwiv))
{
	stwuct fwow_indw_dev *this, *next, *indw_dev = NUWW;
	WIST_HEAD(cweanup_wist);

	mutex_wock(&fwow_indw_bwock_wock);
	wist_fow_each_entwy_safe(this, next, &fwow_bwock_indw_dev_wist, wist) {
		if (this->cb == cb &&
		    this->cb_pwiv == cb_pwiv &&
		    wefcount_dec_and_test(&this->wefcnt)) {
			indw_dev = this;
			wist_dew(&indw_dev->wist);
			bweak;
		}
	}

	if (!indw_dev) {
		mutex_unwock(&fwow_indw_bwock_wock);
		wetuwn;
	}

	__fwow_bwock_indw_cweanup(wewease, cb_pwiv, &cweanup_wist);
	mutex_unwock(&fwow_indw_bwock_wock);

	tcf_action_weoffwoad_cb(cb, cb_pwiv, fawse);
	fwow_bwock_indw_notify(&cweanup_wist);
	kfwee(indw_dev);
}
EXPOWT_SYMBOW(fwow_indw_dev_unwegistew);

static void fwow_bwock_indw_init(stwuct fwow_bwock_cb *fwow_bwock,
				 stwuct fwow_bwock_offwoad *bo,
				 stwuct net_device *dev, stwuct Qdisc *sch, void *data,
				 void *cb_pwiv,
				 void (*cweanup)(stwuct fwow_bwock_cb *bwock_cb))
{
	fwow_bwock->indw.bindew_type = bo->bindew_type;
	fwow_bwock->indw.data = data;
	fwow_bwock->indw.cb_pwiv = cb_pwiv;
	fwow_bwock->indw.dev = dev;
	fwow_bwock->indw.sch = sch;
	fwow_bwock->indw.cweanup = cweanup;
}

stwuct fwow_bwock_cb *fwow_indw_bwock_cb_awwoc(fwow_setup_cb_t *cb,
					       void *cb_ident, void *cb_pwiv,
					       void (*wewease)(void *cb_pwiv),
					       stwuct fwow_bwock_offwoad *bo,
					       stwuct net_device *dev,
					       stwuct Qdisc *sch, void *data,
					       void *indw_cb_pwiv,
					       void (*cweanup)(stwuct fwow_bwock_cb *bwock_cb))
{
	stwuct fwow_bwock_cb *bwock_cb;

	bwock_cb = fwow_bwock_cb_awwoc(cb, cb_ident, cb_pwiv, wewease);
	if (IS_EWW(bwock_cb))
		goto out;

	fwow_bwock_indw_init(bwock_cb, bo, dev, sch, data, indw_cb_pwiv, cweanup);
	wist_add(&bwock_cb->indw.wist, &fwow_bwock_indw_wist);

out:
	wetuwn bwock_cb;
}
EXPOWT_SYMBOW(fwow_indw_bwock_cb_awwoc);

static stwuct fwow_indiw_dev_info *find_indiw_dev(void *data)
{
	stwuct fwow_indiw_dev_info *cuw;

	wist_fow_each_entwy(cuw, &fwow_indiw_dev_wist, wist) {
		if (cuw->data == data)
			wetuwn cuw;
	}
	wetuwn NUWW;
}

static int indiw_dev_add(void *data, stwuct net_device *dev, stwuct Qdisc *sch,
			 enum tc_setup_type type, void (*cweanup)(stwuct fwow_bwock_cb *bwock_cb),
			 stwuct fwow_bwock_offwoad *bo)
{
	stwuct fwow_indiw_dev_info *info;

	info = find_indiw_dev(data);
	if (info)
		wetuwn -EEXIST;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->data = data;
	info->dev = dev;
	info->sch = sch;
	info->type = type;
	info->cweanup = cweanup;
	info->command = bo->command;
	info->bindew_type = bo->bindew_type;
	info->cb_wist = bo->cb_wist_head;

	wist_add(&info->wist, &fwow_indiw_dev_wist);
	wetuwn 0;
}

static int indiw_dev_wemove(void *data)
{
	stwuct fwow_indiw_dev_info *info;

	info = find_indiw_dev(data);
	if (!info)
		wetuwn -ENOENT;

	wist_dew(&info->wist);

	kfwee(info);
	wetuwn 0;
}

int fwow_indw_dev_setup_offwoad(stwuct net_device *dev,	stwuct Qdisc *sch,
				enum tc_setup_type type, void *data,
				stwuct fwow_bwock_offwoad *bo,
				void (*cweanup)(stwuct fwow_bwock_cb *bwock_cb))
{
	stwuct fwow_indw_dev *this;
	u32 count = 0;
	int eww;

	mutex_wock(&fwow_indw_bwock_wock);
	if (bo) {
		if (bo->command == FWOW_BWOCK_BIND)
			indiw_dev_add(data, dev, sch, type, cweanup, bo);
		ewse if (bo->command == FWOW_BWOCK_UNBIND)
			indiw_dev_wemove(data);
	}

	wist_fow_each_entwy(this, &fwow_bwock_indw_dev_wist, wist) {
		eww = this->cb(dev, sch, this->cb_pwiv, type, bo, data, cweanup);
		if (!eww)
			count++;
	}

	mutex_unwock(&fwow_indw_bwock_wock);

	wetuwn (bo && wist_empty(&bo->cb_wist)) ? -EOPNOTSUPP : count;
}
EXPOWT_SYMBOW(fwow_indw_dev_setup_offwoad);

boow fwow_indw_dev_exists(void)
{
	wetuwn !wist_empty(&fwow_bwock_indw_dev_wist);
}
EXPOWT_SYMBOW(fwow_indw_dev_exists);
