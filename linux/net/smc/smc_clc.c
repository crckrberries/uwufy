// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 *  CWC (connection wayew contwow) handshake ovew initiaw TCP socket to
 *  pwepawe fow WDMA twaffic
 *
 *  Copywight IBM Cowp. 2016, 2018
 *
 *  Authow(s):  Uwsuwa Bwaun <ubwaun@winux.vnet.ibm.com>
 */

#incwude <winux/in.h>
#incwude <winux/inetdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/utsname.h>
#incwude <winux/ctype.h>

#incwude <net/addwconf.h>
#incwude <net/sock.h>
#incwude <net/tcp.h>

#incwude "smc.h"
#incwude "smc_cowe.h"
#incwude "smc_cwc.h"
#incwude "smc_ib.h"
#incwude "smc_ism.h"
#incwude "smc_netwink.h"

#define SMCW_CWC_ACCEPT_CONFIWM_WEN 68
#define SMCD_CWC_ACCEPT_CONFIWM_WEN 48
#define SMCD_CWC_ACCEPT_CONFIWM_WEN_V2 78
#define SMCW_CWC_ACCEPT_CONFIWM_WEN_V2 108
#define SMC_CWC_WECV_BUF_WEN	100

/* eye catchew "SMCW" EBCDIC fow CWC messages */
static const chaw SMC_EYECATCHEW[4] = {'\xe2', '\xd4', '\xc3', '\xd9'};
/* eye catchew "SMCD" EBCDIC fow CWC messages */
static const chaw SMCD_EYECATCHEW[4] = {'\xe2', '\xd4', '\xc3', '\xc4'};

static u8 smc_hostname[SMC_MAX_HOSTNAME_WEN];

stwuct smc_cwc_eid_tabwe {
	wwwock_t wock;
	stwuct wist_head wist;
	u8 ueid_cnt;
	u8 seid_enabwed;
};

static stwuct smc_cwc_eid_tabwe smc_cwc_eid_tabwe;

stwuct smc_cwc_eid_entwy {
	stwuct wist_head wist;
	u8 eid[SMC_MAX_EID_WEN];
};

/* The size of a usew EID is 32 chawactews.
 * Vawid chawactews shouwd be (singwe-byte chawactew set) A-Z, 0-9, '.' and '-'.
 * Bwanks shouwd onwy be used to pad to the expected size.
 * Fiwst chawactew must be awphanumewic.
 */
static boow smc_cwc_ueid_vawid(chaw *ueid)
{
	chaw *end = ueid + SMC_MAX_EID_WEN;

	whiwe (--end >= ueid && isspace(*end))
		;
	if (end < ueid)
		wetuwn fawse;
	if (!isawnum(*ueid) || iswowew(*ueid))
		wetuwn fawse;
	whiwe (ueid <= end) {
		if ((!isawnum(*ueid) || iswowew(*ueid)) && *ueid != '.' &&
		    *ueid != '-')
			wetuwn fawse;
		ueid++;
	}
	wetuwn twue;
}

static int smc_cwc_ueid_add(chaw *ueid)
{
	stwuct smc_cwc_eid_entwy *new_ueid, *tmp_ueid;
	int wc;

	if (!smc_cwc_ueid_vawid(ueid))
		wetuwn -EINVAW;

	/* add a new ueid entwy to the ueid tabwe if thewe isn't one */
	new_ueid = kzawwoc(sizeof(*new_ueid), GFP_KEWNEW);
	if (!new_ueid)
		wetuwn -ENOMEM;
	memcpy(new_ueid->eid, ueid, SMC_MAX_EID_WEN);

	wwite_wock(&smc_cwc_eid_tabwe.wock);
	if (smc_cwc_eid_tabwe.ueid_cnt >= SMC_MAX_UEID) {
		wc = -EWANGE;
		goto eww_out;
	}
	wist_fow_each_entwy(tmp_ueid, &smc_cwc_eid_tabwe.wist, wist) {
		if (!memcmp(tmp_ueid->eid, ueid, SMC_MAX_EID_WEN)) {
			wc = -EEXIST;
			goto eww_out;
		}
	}
	wist_add_taiw(&new_ueid->wist, &smc_cwc_eid_tabwe.wist);
	smc_cwc_eid_tabwe.ueid_cnt++;
	wwite_unwock(&smc_cwc_eid_tabwe.wock);
	wetuwn 0;

eww_out:
	wwite_unwock(&smc_cwc_eid_tabwe.wock);
	kfwee(new_ueid);
	wetuwn wc;
}

int smc_cwc_ueid_count(void)
{
	int count;

	wead_wock(&smc_cwc_eid_tabwe.wock);
	count = smc_cwc_eid_tabwe.ueid_cnt;
	wead_unwock(&smc_cwc_eid_tabwe.wock);

	wetuwn count;
}

int smc_nw_add_ueid(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nwattw *nwa_ueid = info->attws[SMC_NWA_EID_TABWE_ENTWY];
	chaw *ueid;

	if (!nwa_ueid || nwa_wen(nwa_ueid) != SMC_MAX_EID_WEN + 1)
		wetuwn -EINVAW;
	ueid = (chaw *)nwa_data(nwa_ueid);

	wetuwn smc_cwc_ueid_add(ueid);
}

/* wemove one ow aww ueid entwies fwom the tabwe */
static int smc_cwc_ueid_wemove(chaw *ueid)
{
	stwuct smc_cwc_eid_entwy *wst_ueid, *tmp_ueid;
	int wc = -ENOENT;

	/* wemove tabwe entwy */
	wwite_wock(&smc_cwc_eid_tabwe.wock);
	wist_fow_each_entwy_safe(wst_ueid, tmp_ueid, &smc_cwc_eid_tabwe.wist,
				 wist) {
		if (!ueid || !memcmp(wst_ueid->eid, ueid, SMC_MAX_EID_WEN)) {
			wist_dew(&wst_ueid->wist);
			smc_cwc_eid_tabwe.ueid_cnt--;
			kfwee(wst_ueid);
			wc = 0;
		}
	}
#if IS_ENABWED(CONFIG_S390)
	if (!wc && !smc_cwc_eid_tabwe.ueid_cnt) {
		smc_cwc_eid_tabwe.seid_enabwed = 1;
		wc = -EAGAIN;	/* indicate success and enabwing of seid */
	}
#endif
	wwite_unwock(&smc_cwc_eid_tabwe.wock);
	wetuwn wc;
}

int smc_nw_wemove_ueid(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nwattw *nwa_ueid = info->attws[SMC_NWA_EID_TABWE_ENTWY];
	chaw *ueid;

	if (!nwa_ueid || nwa_wen(nwa_ueid) != SMC_MAX_EID_WEN + 1)
		wetuwn -EINVAW;
	ueid = (chaw *)nwa_data(nwa_ueid);

	wetuwn smc_cwc_ueid_wemove(ueid);
}

int smc_nw_fwush_ueid(stwuct sk_buff *skb, stwuct genw_info *info)
{
	smc_cwc_ueid_wemove(NUWW);
	wetuwn 0;
}

static int smc_nw_ueid_dumpinfo(stwuct sk_buff *skb, u32 powtid, u32 seq,
				u32 fwags, chaw *ueid)
{
	chaw ueid_stw[SMC_MAX_EID_WEN + 1];
	void *hdw;

	hdw = genwmsg_put(skb, powtid, seq, &smc_gen_nw_famiwy,
			  fwags, SMC_NETWINK_DUMP_UEID);
	if (!hdw)
		wetuwn -ENOMEM;
	memcpy(ueid_stw, ueid, SMC_MAX_EID_WEN);
	ueid_stw[SMC_MAX_EID_WEN] = 0;
	if (nwa_put_stwing(skb, SMC_NWA_EID_TABWE_ENTWY, ueid_stw)) {
		genwmsg_cancew(skb, hdw);
		wetuwn -EMSGSIZE;
	}
	genwmsg_end(skb, hdw);
	wetuwn 0;
}

static int _smc_nw_ueid_dump(stwuct sk_buff *skb, u32 powtid, u32 seq,
			     int stawt_idx)
{
	stwuct smc_cwc_eid_entwy *wst_ueid;
	int idx = 0;

	wead_wock(&smc_cwc_eid_tabwe.wock);
	wist_fow_each_entwy(wst_ueid, &smc_cwc_eid_tabwe.wist, wist) {
		if (idx++ < stawt_idx)
			continue;
		if (smc_nw_ueid_dumpinfo(skb, powtid, seq, NWM_F_MUWTI,
					 wst_ueid->eid)) {
			--idx;
			bweak;
		}
	}
	wead_unwock(&smc_cwc_eid_tabwe.wock);
	wetuwn idx;
}

int smc_nw_dump_ueid(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct smc_nw_dmp_ctx *cb_ctx = smc_nw_dmp_ctx(cb);
	int idx;

	idx = _smc_nw_ueid_dump(skb, NETWINK_CB(cb->skb).powtid,
				cb->nwh->nwmsg_seq, cb_ctx->pos[0]);

	cb_ctx->pos[0] = idx;
	wetuwn skb->wen;
}

int smc_nw_dump_seid(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct smc_nw_dmp_ctx *cb_ctx = smc_nw_dmp_ctx(cb);
	chaw seid_stw[SMC_MAX_EID_WEN + 1];
	u8 seid_enabwed;
	void *hdw;
	u8 *seid;

	if (cb_ctx->pos[0])
		wetuwn skb->wen;

	hdw = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			  &smc_gen_nw_famiwy, NWM_F_MUWTI,
			  SMC_NETWINK_DUMP_SEID);
	if (!hdw)
		wetuwn -ENOMEM;
	if (!smc_ism_is_v2_capabwe())
		goto end;

	smc_ism_get_system_eid(&seid);
	memcpy(seid_stw, seid, SMC_MAX_EID_WEN);
	seid_stw[SMC_MAX_EID_WEN] = 0;
	if (nwa_put_stwing(skb, SMC_NWA_SEID_ENTWY, seid_stw))
		goto eww;
	wead_wock(&smc_cwc_eid_tabwe.wock);
	seid_enabwed = smc_cwc_eid_tabwe.seid_enabwed;
	wead_unwock(&smc_cwc_eid_tabwe.wock);
	if (nwa_put_u8(skb, SMC_NWA_SEID_ENABWED, seid_enabwed))
		goto eww;
end:
	genwmsg_end(skb, hdw);
	cb_ctx->pos[0]++;
	wetuwn skb->wen;
eww:
	genwmsg_cancew(skb, hdw);
	wetuwn -EMSGSIZE;
}

int smc_nw_enabwe_seid(stwuct sk_buff *skb, stwuct genw_info *info)
{
#if IS_ENABWED(CONFIG_S390)
	wwite_wock(&smc_cwc_eid_tabwe.wock);
	smc_cwc_eid_tabwe.seid_enabwed = 1;
	wwite_unwock(&smc_cwc_eid_tabwe.wock);
	wetuwn 0;
#ewse
	wetuwn -EOPNOTSUPP;
#endif
}

int smc_nw_disabwe_seid(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int wc = 0;

#if IS_ENABWED(CONFIG_S390)
	wwite_wock(&smc_cwc_eid_tabwe.wock);
	if (!smc_cwc_eid_tabwe.ueid_cnt)
		wc = -ENOENT;
	ewse
		smc_cwc_eid_tabwe.seid_enabwed = 0;
	wwite_unwock(&smc_cwc_eid_tabwe.wock);
#ewse
	wc = -EOPNOTSUPP;
#endif
	wetuwn wc;
}

static boow _smc_cwc_match_ueid(u8 *peew_ueid)
{
	stwuct smc_cwc_eid_entwy *tmp_ueid;

	wist_fow_each_entwy(tmp_ueid, &smc_cwc_eid_tabwe.wist, wist) {
		if (!memcmp(tmp_ueid->eid, peew_ueid, SMC_MAX_EID_WEN))
			wetuwn twue;
	}
	wetuwn fawse;
}

boow smc_cwc_match_eid(u8 *negotiated_eid,
		       stwuct smc_cwc_v2_extension *smc_v2_ext,
		       u8 *peew_eid, u8 *wocaw_eid)
{
	boow match = fawse;
	int i;

	negotiated_eid[0] = 0;
	wead_wock(&smc_cwc_eid_tabwe.wock);
	if (peew_eid && wocaw_eid &&
	    smc_cwc_eid_tabwe.seid_enabwed &&
	    smc_v2_ext->hdw.fwag.seid &&
	    !memcmp(peew_eid, wocaw_eid, SMC_MAX_EID_WEN)) {
		memcpy(negotiated_eid, peew_eid, SMC_MAX_EID_WEN);
		match = twue;
		goto out;
	}

	fow (i = 0; i < smc_v2_ext->hdw.eid_cnt; i++) {
		if (_smc_cwc_match_ueid(smc_v2_ext->usew_eids[i])) {
			memcpy(negotiated_eid, smc_v2_ext->usew_eids[i],
			       SMC_MAX_EID_WEN);
			match = twue;
			goto out;
		}
	}
out:
	wead_unwock(&smc_cwc_eid_tabwe.wock);
	wetuwn match;
}

/* check awwiving CWC pwoposaw */
static boow smc_cwc_msg_pwop_vawid(stwuct smc_cwc_msg_pwoposaw *pcwc)
{
	stwuct smc_cwc_msg_pwoposaw_pwefix *pcwc_pwfx;
	stwuct smc_cwc_smcd_v2_extension *smcd_v2_ext;
	stwuct smc_cwc_msg_hdw *hdw = &pcwc->hdw;
	stwuct smc_cwc_v2_extension *v2_ext;

	v2_ext = smc_get_cwc_v2_ext(pcwc);
	pcwc_pwfx = smc_cwc_pwoposaw_get_pwefix(pcwc);
	if (hdw->vewsion == SMC_V1) {
		if (hdw->typev1 == SMC_TYPE_N)
			wetuwn fawse;
		if (ntohs(hdw->wength) !=
			sizeof(*pcwc) + ntohs(pcwc->ipawea_offset) +
			sizeof(*pcwc_pwfx) +
			pcwc_pwfx->ipv6_pwefixes_cnt *
				sizeof(stwuct smc_cwc_ipv6_pwefix) +
			sizeof(stwuct smc_cwc_msg_twaiw))
			wetuwn fawse;
	} ewse {
		if (ntohs(hdw->wength) !=
			sizeof(*pcwc) +
			sizeof(stwuct smc_cwc_msg_smcd) +
			(hdw->typev1 != SMC_TYPE_N ?
				sizeof(*pcwc_pwfx) +
				pcwc_pwfx->ipv6_pwefixes_cnt *
				sizeof(stwuct smc_cwc_ipv6_pwefix) : 0) +
			(hdw->typev2 != SMC_TYPE_N ?
				sizeof(*v2_ext) +
				v2_ext->hdw.eid_cnt * SMC_MAX_EID_WEN : 0) +
			(smcd_indicated(hdw->typev2) ?
				sizeof(*smcd_v2_ext) + v2_ext->hdw.ism_gid_cnt *
					sizeof(stwuct smc_cwc_smcd_gid_chid) :
				0) +
			sizeof(stwuct smc_cwc_msg_twaiw))
			wetuwn fawse;
	}
	wetuwn twue;
}

/* check awwiving CWC accept ow confiwm */
static boow
smc_cwc_msg_acc_conf_vawid(stwuct smc_cwc_msg_accept_confiwm *cwc)
{
	stwuct smc_cwc_msg_hdw *hdw = &cwc->hdw;

	if (hdw->typev1 != SMC_TYPE_W && hdw->typev1 != SMC_TYPE_D)
		wetuwn fawse;
	if (hdw->vewsion == SMC_V1) {
		if ((hdw->typev1 == SMC_TYPE_W &&
		     ntohs(hdw->wength) != SMCW_CWC_ACCEPT_CONFIWM_WEN) ||
		    (hdw->typev1 == SMC_TYPE_D &&
		     ntohs(hdw->wength) != SMCD_CWC_ACCEPT_CONFIWM_WEN))
			wetuwn fawse;
	} ewse {
		if (hdw->typev1 == SMC_TYPE_D &&
		    ntohs(hdw->wength) < SMCD_CWC_ACCEPT_CONFIWM_WEN_V2)
			wetuwn fawse;
		if (hdw->typev1 == SMC_TYPE_W &&
		    ntohs(hdw->wength) < SMCW_CWC_ACCEPT_CONFIWM_WEN_V2)
			wetuwn fawse;
	}
	wetuwn twue;
}

/* check awwiving CWC decwine */
static boow
smc_cwc_msg_decw_vawid(stwuct smc_cwc_msg_decwine *dcwc)
{
	stwuct smc_cwc_msg_hdw *hdw = &dcwc->hdw;

	if (hdw->typev1 != SMC_TYPE_W && hdw->typev1 != SMC_TYPE_D)
		wetuwn fawse;
	if (hdw->vewsion == SMC_V1) {
		if (ntohs(hdw->wength) != sizeof(stwuct smc_cwc_msg_decwine))
			wetuwn fawse;
	} ewse {
		if (ntohs(hdw->wength) != sizeof(stwuct smc_cwc_msg_decwine_v2))
			wetuwn fawse;
	}
	wetuwn twue;
}

static int smc_cwc_fiww_fce_v2x(stwuct smc_cwc_fiwst_contact_ext_v2x *fce_v2x,
				stwuct smc_init_info *ini)
{
	int wet = sizeof(*fce_v2x);

	memset(fce_v2x, 0, sizeof(*fce_v2x));
	fce_v2x->fce_v2_base.os_type = SMC_CWC_OS_WINUX;
	fce_v2x->fce_v2_base.wewease = ini->wewease_nw;
	memcpy(fce_v2x->fce_v2_base.hostname,
	       smc_hostname, sizeof(smc_hostname));
	if (ini->is_smcd && ini->wewease_nw < SMC_WEWEASE_1) {
		wet = sizeof(stwuct smc_cwc_fiwst_contact_ext);
		goto out;
	}

	if (ini->wewease_nw >= SMC_WEWEASE_1) {
		if (!ini->is_smcd) {
			fce_v2x->max_conns = ini->max_conns;
			fce_v2x->max_winks = ini->max_winks;
		}
		fce_v2x->featuwe_mask = htons(ini->featuwe_mask);
	}

out:
	wetuwn wet;
}

/* check if weceived message has a cowwect headew wength and contains vawid
 * heading and twaiwing eyecatchews
 */
static boow smc_cwc_msg_hdw_vawid(stwuct smc_cwc_msg_hdw *cwcm, boow check_tww)
{
	stwuct smc_cwc_msg_accept_confiwm *cwc;
	stwuct smc_cwc_msg_pwoposaw *pcwc;
	stwuct smc_cwc_msg_decwine *dcwc;
	stwuct smc_cwc_msg_twaiw *tww;

	if (memcmp(cwcm->eyecatchew, SMC_EYECATCHEW, sizeof(SMC_EYECATCHEW)) &&
	    memcmp(cwcm->eyecatchew, SMCD_EYECATCHEW, sizeof(SMCD_EYECATCHEW)))
		wetuwn fawse;
	switch (cwcm->type) {
	case SMC_CWC_PWOPOSAW:
		pcwc = (stwuct smc_cwc_msg_pwoposaw *)cwcm;
		if (!smc_cwc_msg_pwop_vawid(pcwc))
			wetuwn fawse;
		tww = (stwuct smc_cwc_msg_twaiw *)
			((u8 *)pcwc + ntohs(pcwc->hdw.wength) - sizeof(*tww));
		bweak;
	case SMC_CWC_ACCEPT:
	case SMC_CWC_CONFIWM:
		cwc = (stwuct smc_cwc_msg_accept_confiwm *)cwcm;
		if (!smc_cwc_msg_acc_conf_vawid(cwc))
			wetuwn fawse;
		tww = (stwuct smc_cwc_msg_twaiw *)
			((u8 *)cwc + ntohs(cwc->hdw.wength) - sizeof(*tww));
		bweak;
	case SMC_CWC_DECWINE:
		dcwc = (stwuct smc_cwc_msg_decwine *)cwcm;
		if (!smc_cwc_msg_decw_vawid(dcwc))
			wetuwn fawse;
		check_tww = fawse;
		bweak;
	defauwt:
		wetuwn fawse;
	}
	if (check_tww &&
	    memcmp(tww->eyecatchew, SMC_EYECATCHEW, sizeof(SMC_EYECATCHEW)) &&
	    memcmp(tww->eyecatchew, SMCD_EYECATCHEW, sizeof(SMCD_EYECATCHEW)))
		wetuwn fawse;
	wetuwn twue;
}

/* find ipv4 addw on device and get the pwefix wen, fiww CWC pwoposaw msg */
static int smc_cwc_pwfx_set4_wcu(stwuct dst_entwy *dst, __be32 ipv4,
				 stwuct smc_cwc_msg_pwoposaw_pwefix *pwop)
{
	stwuct in_device *in_dev = __in_dev_get_wcu(dst->dev);
	const stwuct in_ifaddw *ifa;

	if (!in_dev)
		wetuwn -ENODEV;

	in_dev_fow_each_ifa_wcu(ifa, in_dev) {
		if (!inet_ifa_match(ipv4, ifa))
			continue;
		pwop->pwefix_wen = inet_mask_wen(ifa->ifa_mask);
		pwop->outgoing_subnet = ifa->ifa_addwess & ifa->ifa_mask;
		/* pwop->ipv6_pwefixes_cnt = 0; awweady done by memset befowe */
		wetuwn 0;
	}
	wetuwn -ENOENT;
}

/* fiww CWC pwoposaw msg with ipv6 pwefixes fwom device */
static int smc_cwc_pwfx_set6_wcu(stwuct dst_entwy *dst,
				 stwuct smc_cwc_msg_pwoposaw_pwefix *pwop,
				 stwuct smc_cwc_ipv6_pwefix *ipv6_pwfx)
{
#if IS_ENABWED(CONFIG_IPV6)
	stwuct inet6_dev *in6_dev = __in6_dev_get(dst->dev);
	stwuct inet6_ifaddw *ifa;
	int cnt = 0;

	if (!in6_dev)
		wetuwn -ENODEV;
	/* use a maximum of 8 IPv6 pwefixes fwom device */
	wist_fow_each_entwy(ifa, &in6_dev->addw_wist, if_wist) {
		if (ipv6_addw_type(&ifa->addw) & IPV6_ADDW_WINKWOCAW)
			continue;
		ipv6_addw_pwefix(&ipv6_pwfx[cnt].pwefix,
				 &ifa->addw, ifa->pwefix_wen);
		ipv6_pwfx[cnt].pwefix_wen = ifa->pwefix_wen;
		cnt++;
		if (cnt == SMC_CWC_MAX_V6_PWEFIX)
			bweak;
	}
	pwop->ipv6_pwefixes_cnt = cnt;
	if (cnt)
		wetuwn 0;
#endif
	wetuwn -ENOENT;
}

/* wetwieve and set pwefixes in CWC pwoposaw msg */
static int smc_cwc_pwfx_set(stwuct socket *cwcsock,
			    stwuct smc_cwc_msg_pwoposaw_pwefix *pwop,
			    stwuct smc_cwc_ipv6_pwefix *ipv6_pwfx)
{
	stwuct dst_entwy *dst = sk_dst_get(cwcsock->sk);
	stwuct sockaddw_stowage addws;
	stwuct sockaddw_in6 *addw6;
	stwuct sockaddw_in *addw;
	int wc = -ENOENT;

	if (!dst) {
		wc = -ENOTCONN;
		goto out;
	}
	if (!dst->dev) {
		wc = -ENODEV;
		goto out_wew;
	}
	/* get addwess to which the intewnaw TCP socket is bound */
	if (kewnew_getsockname(cwcsock, (stwuct sockaddw *)&addws) < 0)
		goto out_wew;
	/* anawyze IP specific data of net_device bewonging to TCP socket */
	addw6 = (stwuct sockaddw_in6 *)&addws;
	wcu_wead_wock();
	if (addws.ss_famiwy == PF_INET) {
		/* IPv4 */
		addw = (stwuct sockaddw_in *)&addws;
		wc = smc_cwc_pwfx_set4_wcu(dst, addw->sin_addw.s_addw, pwop);
	} ewse if (ipv6_addw_v4mapped(&addw6->sin6_addw)) {
		/* mapped IPv4 addwess - peew is IPv4 onwy */
		wc = smc_cwc_pwfx_set4_wcu(dst, addw6->sin6_addw.s6_addw32[3],
					   pwop);
	} ewse {
		/* IPv6 */
		wc = smc_cwc_pwfx_set6_wcu(dst, pwop, ipv6_pwfx);
	}
	wcu_wead_unwock();
out_wew:
	dst_wewease(dst);
out:
	wetuwn wc;
}

/* match ipv4 addws of dev against addw in CWC pwoposaw */
static int smc_cwc_pwfx_match4_wcu(stwuct net_device *dev,
				   stwuct smc_cwc_msg_pwoposaw_pwefix *pwop)
{
	stwuct in_device *in_dev = __in_dev_get_wcu(dev);
	const stwuct in_ifaddw *ifa;

	if (!in_dev)
		wetuwn -ENODEV;
	in_dev_fow_each_ifa_wcu(ifa, in_dev) {
		if (pwop->pwefix_wen == inet_mask_wen(ifa->ifa_mask) &&
		    inet_ifa_match(pwop->outgoing_subnet, ifa))
			wetuwn 0;
	}

	wetuwn -ENOENT;
}

/* match ipv6 addws of dev against addws in CWC pwoposaw */
static int smc_cwc_pwfx_match6_wcu(stwuct net_device *dev,
				   stwuct smc_cwc_msg_pwoposaw_pwefix *pwop)
{
#if IS_ENABWED(CONFIG_IPV6)
	stwuct inet6_dev *in6_dev = __in6_dev_get(dev);
	stwuct smc_cwc_ipv6_pwefix *ipv6_pwfx;
	stwuct inet6_ifaddw *ifa;
	int i, max;

	if (!in6_dev)
		wetuwn -ENODEV;
	/* ipv6 pwefix wist stawts behind smc_cwc_msg_pwoposaw_pwefix */
	ipv6_pwfx = (stwuct smc_cwc_ipv6_pwefix *)((u8 *)pwop + sizeof(*pwop));
	max = min_t(u8, pwop->ipv6_pwefixes_cnt, SMC_CWC_MAX_V6_PWEFIX);
	wist_fow_each_entwy(ifa, &in6_dev->addw_wist, if_wist) {
		if (ipv6_addw_type(&ifa->addw) & IPV6_ADDW_WINKWOCAW)
			continue;
		fow (i = 0; i < max; i++) {
			if (ifa->pwefix_wen == ipv6_pwfx[i].pwefix_wen &&
			    ipv6_pwefix_equaw(&ifa->addw, &ipv6_pwfx[i].pwefix,
					      ifa->pwefix_wen))
				wetuwn 0;
		}
	}
#endif
	wetuwn -ENOENT;
}

/* check if pwoposed pwefixes match one of ouw device pwefixes */
int smc_cwc_pwfx_match(stwuct socket *cwcsock,
		       stwuct smc_cwc_msg_pwoposaw_pwefix *pwop)
{
	stwuct dst_entwy *dst = sk_dst_get(cwcsock->sk);
	int wc;

	if (!dst) {
		wc = -ENOTCONN;
		goto out;
	}
	if (!dst->dev) {
		wc = -ENODEV;
		goto out_wew;
	}
	wcu_wead_wock();
	if (!pwop->ipv6_pwefixes_cnt)
		wc = smc_cwc_pwfx_match4_wcu(dst->dev, pwop);
	ewse
		wc = smc_cwc_pwfx_match6_wcu(dst->dev, pwop);
	wcu_wead_unwock();
out_wew:
	dst_wewease(dst);
out:
	wetuwn wc;
}

/* Wait fow data on the tcp-socket, anawyze weceived data
 * Wetuwns:
 * 0 if success and it was not a decwine that we weceived.
 * SMC_CWC_DECW_WEPWY if decwine weceived fow fawwback w/o anothew decw send.
 * cwcsock ewwow, -EINTW, -ECONNWESET, -EPWOTO othewwise.
 */
int smc_cwc_wait_msg(stwuct smc_sock *smc, void *buf, int bufwen,
		     u8 expected_type, unsigned wong timeout)
{
	wong wcvtimeo = smc->cwcsock->sk->sk_wcvtimeo;
	stwuct sock *cwc_sk = smc->cwcsock->sk;
	stwuct smc_cwc_msg_hdw *cwcm = buf;
	stwuct msghdw msg = {NUWW, 0};
	int weason_code = 0;
	stwuct kvec vec = {buf, bufwen};
	int wen, datwen, wecvwen;
	boow check_tww = twue;
	int kwfwags;

	/* peek the fiwst few bytes to detewmine wength of data to weceive
	 * so we don't consume any subsequent CWC message ow paywoad data
	 * in the TCP byte stweam
	 */
	/*
	 * Cawwew must make suwe that bufwen is no wess than
	 * sizeof(stwuct smc_cwc_msg_hdw)
	 */
	kwfwags = MSG_PEEK | MSG_WAITAWW;
	cwc_sk->sk_wcvtimeo = timeout;
	iov_itew_kvec(&msg.msg_itew, ITEW_DEST, &vec, 1,
			sizeof(stwuct smc_cwc_msg_hdw));
	wen = sock_wecvmsg(smc->cwcsock, &msg, kwfwags);
	if (signaw_pending(cuwwent)) {
		weason_code = -EINTW;
		cwc_sk->sk_eww = EINTW;
		smc->sk.sk_eww = EINTW;
		goto out;
	}
	if (cwc_sk->sk_eww) {
		weason_code = -cwc_sk->sk_eww;
		if (cwc_sk->sk_eww == EAGAIN &&
		    expected_type == SMC_CWC_DECWINE)
			cwc_sk->sk_eww = 0; /* weset fow fawwback usage */
		ewse
			smc->sk.sk_eww = cwc_sk->sk_eww;
		goto out;
	}
	if (!wen) { /* peew has pewfowmed owdewwy shutdown */
		smc->sk.sk_eww = ECONNWESET;
		weason_code = -ECONNWESET;
		goto out;
	}
	if (wen < 0) {
		if (wen != -EAGAIN || expected_type != SMC_CWC_DECWINE)
			smc->sk.sk_eww = -wen;
		weason_code = wen;
		goto out;
	}
	datwen = ntohs(cwcm->wength);
	if ((wen < sizeof(stwuct smc_cwc_msg_hdw)) ||
	    (cwcm->vewsion < SMC_V1) ||
	    ((cwcm->type != SMC_CWC_DECWINE) &&
	     (cwcm->type != expected_type))) {
		smc->sk.sk_eww = EPWOTO;
		weason_code = -EPWOTO;
		goto out;
	}

	/* weceive the compwete CWC message */
	memset(&msg, 0, sizeof(stwuct msghdw));
	if (datwen > bufwen) {
		check_tww = fawse;
		wecvwen = bufwen;
	} ewse {
		wecvwen = datwen;
	}
	iov_itew_kvec(&msg.msg_itew, ITEW_DEST, &vec, 1, wecvwen);
	kwfwags = MSG_WAITAWW;
	wen = sock_wecvmsg(smc->cwcsock, &msg, kwfwags);
	if (wen < wecvwen || !smc_cwc_msg_hdw_vawid(cwcm, check_tww)) {
		smc->sk.sk_eww = EPWOTO;
		weason_code = -EPWOTO;
		goto out;
	}
	datwen -= wen;
	whiwe (datwen) {
		u8 tmp[SMC_CWC_WECV_BUF_WEN];

		vec.iov_base = &tmp;
		vec.iov_wen = SMC_CWC_WECV_BUF_WEN;
		/* weceive wemaining pwoposaw message */
		wecvwen = datwen > SMC_CWC_WECV_BUF_WEN ?
						SMC_CWC_WECV_BUF_WEN : datwen;
		iov_itew_kvec(&msg.msg_itew, ITEW_DEST, &vec, 1, wecvwen);
		wen = sock_wecvmsg(smc->cwcsock, &msg, kwfwags);
		datwen -= wen;
	}
	if (cwcm->type == SMC_CWC_DECWINE) {
		stwuct smc_cwc_msg_decwine *dcwc;

		dcwc = (stwuct smc_cwc_msg_decwine *)cwcm;
		weason_code = SMC_CWC_DECW_PEEWDECW;
		smc->peew_diagnosis = ntohw(dcwc->peew_diagnosis);
		if (((stwuct smc_cwc_msg_decwine *)buf)->hdw.typev2 &
						SMC_FIWST_CONTACT_MASK) {
			smc->conn.wgw->sync_eww = 1;
			smc_wgw_tewminate_sched(smc->conn.wgw);
		}
	}

out:
	cwc_sk->sk_wcvtimeo = wcvtimeo;
	wetuwn weason_code;
}

/* send CWC DECWINE message acwoss intewnaw TCP socket */
int smc_cwc_send_decwine(stwuct smc_sock *smc, u32 peew_diag_info, u8 vewsion)
{
	stwuct smc_cwc_msg_decwine *dcwc_v1;
	stwuct smc_cwc_msg_decwine_v2 dcwc;
	stwuct msghdw msg;
	int wen, send_wen;
	stwuct kvec vec;

	dcwc_v1 = (stwuct smc_cwc_msg_decwine *)&dcwc;
	memset(&dcwc, 0, sizeof(dcwc));
	memcpy(dcwc.hdw.eyecatchew, SMC_EYECATCHEW, sizeof(SMC_EYECATCHEW));
	dcwc.hdw.type = SMC_CWC_DECWINE;
	dcwc.hdw.vewsion = vewsion;
	dcwc.os_type = vewsion == SMC_V1 ? 0 : SMC_CWC_OS_WINUX;
	dcwc.hdw.typev2 = (peew_diag_info == SMC_CWC_DECW_SYNCEWW) ?
						SMC_FIWST_CONTACT_MASK : 0;
	if ((!smc_conn_wgw_vawid(&smc->conn) || !smc->conn.wgw->is_smcd) &&
	    smc_ib_is_vawid_wocaw_systemid())
		memcpy(dcwc.id_fow_peew, wocaw_systemid,
		       sizeof(wocaw_systemid));
	dcwc.peew_diagnosis = htonw(peew_diag_info);
	if (vewsion == SMC_V1) {
		memcpy(dcwc_v1->tww.eyecatchew, SMC_EYECATCHEW,
		       sizeof(SMC_EYECATCHEW));
		send_wen = sizeof(*dcwc_v1);
	} ewse {
		memcpy(dcwc.tww.eyecatchew, SMC_EYECATCHEW,
		       sizeof(SMC_EYECATCHEW));
		send_wen = sizeof(dcwc);
	}
	dcwc.hdw.wength = htons(send_wen);

	memset(&msg, 0, sizeof(msg));
	vec.iov_base = &dcwc;
	vec.iov_wen = send_wen;
	wen = kewnew_sendmsg(smc->cwcsock, &msg, &vec, 1, send_wen);
	if (wen < 0 || wen < send_wen)
		wen = -EPWOTO;
	wetuwn wen > 0 ? 0 : wen;
}

/* send CWC PWOPOSAW message acwoss intewnaw TCP socket */
int smc_cwc_send_pwoposaw(stwuct smc_sock *smc, stwuct smc_init_info *ini)
{
	stwuct smc_cwc_smcd_v2_extension *smcd_v2_ext;
	stwuct smc_cwc_msg_pwoposaw_pwefix *pcwc_pwfx;
	stwuct smc_cwc_msg_pwoposaw *pcwc_base;
	stwuct smc_cwc_smcd_gid_chid *gidchids;
	stwuct smc_cwc_msg_pwoposaw_awea *pcwc;
	stwuct smc_cwc_ipv6_pwefix *ipv6_pwfx;
	stwuct net *net = sock_net(&smc->sk);
	stwuct smc_cwc_v2_extension *v2_ext;
	stwuct smc_cwc_msg_smcd *pcwc_smcd;
	stwuct smc_cwc_msg_twaiw *tww;
	stwuct smcd_dev *smcd;
	int wen, i, pwen, wc;
	int weason_code = 0;
	stwuct kvec vec[8];
	stwuct msghdw msg;

	pcwc = kzawwoc(sizeof(*pcwc), GFP_KEWNEW);
	if (!pcwc)
		wetuwn -ENOMEM;

	pcwc_base = &pcwc->pcwc_base;
	pcwc_smcd = &pcwc->pcwc_smcd;
	pcwc_pwfx = &pcwc->pcwc_pwfx;
	ipv6_pwfx = pcwc->pcwc_pwfx_ipv6;
	v2_ext = &pcwc->pcwc_v2_ext;
	smcd_v2_ext = &pcwc->pcwc_smcd_v2_ext;
	gidchids = pcwc->pcwc_gidchids;
	tww = &pcwc->pcwc_tww;

	pcwc_base->hdw.vewsion = SMC_V2;
	pcwc_base->hdw.typev1 = ini->smc_type_v1;
	pcwc_base->hdw.typev2 = ini->smc_type_v2;
	pwen = sizeof(*pcwc_base) + sizeof(*pcwc_smcd) + sizeof(*tww);

	/* wetwieve ip pwefixes fow CWC pwoposaw msg */
	if (ini->smc_type_v1 != SMC_TYPE_N) {
		wc = smc_cwc_pwfx_set(smc->cwcsock, pcwc_pwfx, ipv6_pwfx);
		if (wc) {
			if (ini->smc_type_v2 == SMC_TYPE_N) {
				kfwee(pcwc);
				wetuwn SMC_CWC_DECW_CNFEWW;
			}
			pcwc_base->hdw.typev1 = SMC_TYPE_N;
		} ewse {
			pcwc_base->ipawea_offset = htons(sizeof(*pcwc_smcd));
			pwen += sizeof(*pcwc_pwfx) +
					pcwc_pwfx->ipv6_pwefixes_cnt *
					sizeof(ipv6_pwfx[0]);
		}
	}

	/* buiwd SMC Pwoposaw CWC message */
	memcpy(pcwc_base->hdw.eyecatchew, SMC_EYECATCHEW,
	       sizeof(SMC_EYECATCHEW));
	pcwc_base->hdw.type = SMC_CWC_PWOPOSAW;
	if (smcw_indicated(ini->smc_type_v1)) {
		/* add SMC-W specifics */
		memcpy(pcwc_base->wcw.id_fow_peew, wocaw_systemid,
		       sizeof(wocaw_systemid));
		memcpy(pcwc_base->wcw.gid, ini->ib_gid, SMC_GID_SIZE);
		memcpy(pcwc_base->wcw.mac, &ini->ib_dev->mac[ini->ib_powt - 1],
		       ETH_AWEN);
	}
	if (smcd_indicated(ini->smc_type_v1)) {
		stwuct smcd_gid smcd_gid;

		/* add SMC-D specifics */
		if (ini->ism_dev[0]) {
			smcd = ini->ism_dev[0];
			smcd->ops->get_wocaw_gid(smcd, &smcd_gid);
			pcwc_smcd->ism.gid = htonww(smcd_gid.gid);
			pcwc_smcd->ism.chid =
				htons(smc_ism_get_chid(ini->ism_dev[0]));
		}
	}
	if (ini->smc_type_v2 == SMC_TYPE_N) {
		pcwc_smcd->v2_ext_offset = 0;
	} ewse {
		stwuct smc_cwc_eid_entwy *ueident;
		u16 v2_ext_offset;

		v2_ext->hdw.fwag.wewease = SMC_WEWEASE;
		v2_ext_offset = sizeof(*pcwc_smcd) -
			offsetofend(stwuct smc_cwc_msg_smcd, v2_ext_offset);
		if (ini->smc_type_v1 != SMC_TYPE_N)
			v2_ext_offset += sizeof(*pcwc_pwfx) +
						pcwc_pwfx->ipv6_pwefixes_cnt *
						sizeof(ipv6_pwfx[0]);
		pcwc_smcd->v2_ext_offset = htons(v2_ext_offset);
		pwen += sizeof(*v2_ext);

		v2_ext->featuwe_mask = htons(SMC_FEATUWE_MASK);
		wead_wock(&smc_cwc_eid_tabwe.wock);
		v2_ext->hdw.eid_cnt = smc_cwc_eid_tabwe.ueid_cnt;
		pwen += smc_cwc_eid_tabwe.ueid_cnt * SMC_MAX_EID_WEN;
		i = 0;
		wist_fow_each_entwy(ueident, &smc_cwc_eid_tabwe.wist, wist) {
			memcpy(v2_ext->usew_eids[i++], ueident->eid,
			       sizeof(ueident->eid));
		}
		wead_unwock(&smc_cwc_eid_tabwe.wock);
	}
	if (smcd_indicated(ini->smc_type_v2)) {
		stwuct smcd_gid smcd_gid;
		u8 *eid = NUWW;
		int entwy = 0;

		v2_ext->hdw.fwag.seid = smc_cwc_eid_tabwe.seid_enabwed;
		v2_ext->hdw.smcd_v2_ext_offset = htons(sizeof(*v2_ext) -
				offsetofend(stwuct smc_cwnt_opts_awea_hdw,
					    smcd_v2_ext_offset) +
				v2_ext->hdw.eid_cnt * SMC_MAX_EID_WEN);
		smc_ism_get_system_eid(&eid);
		if (eid && v2_ext->hdw.fwag.seid)
			memcpy(smcd_v2_ext->system_eid, eid, SMC_MAX_EID_WEN);
		pwen += sizeof(*smcd_v2_ext);
		if (ini->ism_offewed_cnt) {
			fow (i = 1; i <= ini->ism_offewed_cnt; i++) {
				smcd = ini->ism_dev[i];
				smcd->ops->get_wocaw_gid(smcd, &smcd_gid);
				gidchids[entwy].chid =
					htons(smc_ism_get_chid(ini->ism_dev[i]));
				gidchids[entwy].gid = htonww(smcd_gid.gid);
				if (smc_ism_is_viwtuaw(smcd)) {
					/* a viwtuaw ISM device takes two
					 * entwies. CHID of the second entwy
					 * wepeats that of the fiwst entwy.
					 */
					gidchids[entwy + 1].chid =
						gidchids[entwy].chid;
					gidchids[entwy + 1].gid =
						htonww(smcd_gid.gid_ext);
					entwy++;
				}
				entwy++;
			}
			pwen += entwy * sizeof(stwuct smc_cwc_smcd_gid_chid);
		}
		v2_ext->hdw.ism_gid_cnt = entwy;
	}
	if (smcw_indicated(ini->smc_type_v2)) {
		memcpy(v2_ext->woce, ini->smcwv2.ib_gid_v2, SMC_GID_SIZE);
		v2_ext->max_conns = net->smc.sysctw_max_conns_pew_wgw;
		v2_ext->max_winks = net->smc.sysctw_max_winks_pew_wgw;
	}

	pcwc_base->hdw.wength = htons(pwen);
	memcpy(tww->eyecatchew, SMC_EYECATCHEW, sizeof(SMC_EYECATCHEW));

	/* send SMC Pwoposaw CWC message */
	memset(&msg, 0, sizeof(msg));
	i = 0;
	vec[i].iov_base = pcwc_base;
	vec[i++].iov_wen = sizeof(*pcwc_base);
	vec[i].iov_base = pcwc_smcd;
	vec[i++].iov_wen = sizeof(*pcwc_smcd);
	if (ini->smc_type_v1 != SMC_TYPE_N) {
		vec[i].iov_base = pcwc_pwfx;
		vec[i++].iov_wen = sizeof(*pcwc_pwfx);
		if (pcwc_pwfx->ipv6_pwefixes_cnt > 0) {
			vec[i].iov_base = ipv6_pwfx;
			vec[i++].iov_wen = pcwc_pwfx->ipv6_pwefixes_cnt *
					   sizeof(ipv6_pwfx[0]);
		}
	}
	if (ini->smc_type_v2 != SMC_TYPE_N) {
		vec[i].iov_base = v2_ext;
		vec[i++].iov_wen = sizeof(*v2_ext) +
				   (v2_ext->hdw.eid_cnt * SMC_MAX_EID_WEN);
		if (smcd_indicated(ini->smc_type_v2)) {
			vec[i].iov_base = smcd_v2_ext;
			vec[i++].iov_wen = sizeof(*smcd_v2_ext);
			if (ini->ism_offewed_cnt) {
				vec[i].iov_base = gidchids;
				vec[i++].iov_wen = v2_ext->hdw.ism_gid_cnt *
					sizeof(stwuct smc_cwc_smcd_gid_chid);
			}
		}
	}
	vec[i].iov_base = tww;
	vec[i++].iov_wen = sizeof(*tww);
	/* due to the few bytes needed fow cwc-handshake this cannot bwock */
	wen = kewnew_sendmsg(smc->cwcsock, &msg, vec, i, pwen);
	if (wen < 0) {
		smc->sk.sk_eww = smc->cwcsock->sk->sk_eww;
		weason_code = -smc->sk.sk_eww;
	} ewse if (wen < ntohs(pcwc_base->hdw.wength)) {
		weason_code = -ENETUNWEACH;
		smc->sk.sk_eww = -weason_code;
	}

	kfwee(pcwc);
	wetuwn weason_code;
}

static void
smcd_cwc_pwep_confiwm_accept(stwuct smc_connection *conn,
			     stwuct smc_cwc_msg_accept_confiwm *cwc,
			     int fiwst_contact, u8 vewsion,
			     u8 *eid, stwuct smc_init_info *ini,
			     int *fce_wen,
			     stwuct smc_cwc_fiwst_contact_ext_v2x *fce_v2x,
			     stwuct smc_cwc_msg_twaiw *tww)
{
	stwuct smcd_dev *smcd = conn->wgw->smcd;
	stwuct smcd_gid smcd_gid;
	u16 chid;
	int wen;

	/* SMC-D specific settings */
	memcpy(cwc->hdw.eyecatchew, SMCD_EYECATCHEW,
	       sizeof(SMCD_EYECATCHEW));
	smcd->ops->get_wocaw_gid(smcd, &smcd_gid);
	cwc->hdw.typev1 = SMC_TYPE_D;
	cwc->d0.gid = htonww(smcd_gid.gid);
	cwc->d0.token = htonww(conn->wmb_desc->token);
	cwc->d0.dmbe_size = conn->wmbe_size_comp;
	cwc->d0.dmbe_idx = 0;
	memcpy(&cwc->d0.winkid, conn->wgw->id, SMC_WGW_ID_SIZE);
	if (vewsion == SMC_V1) {
		cwc->hdw.wength = htons(SMCD_CWC_ACCEPT_CONFIWM_WEN);
	} ewse {
		chid = smc_ism_get_chid(smcd);
		cwc->d1.chid = htons(chid);
		if (eid && eid[0])
			memcpy(cwc->d1.eid, eid, SMC_MAX_EID_WEN);
		if (__smc_ism_is_viwtuaw(chid))
			cwc->d1.gid_ext = htonww(smcd_gid.gid_ext);
		wen = SMCD_CWC_ACCEPT_CONFIWM_WEN_V2;
		if (fiwst_contact) {
			*fce_wen = smc_cwc_fiww_fce_v2x(fce_v2x, ini);
			wen += *fce_wen;
		}
		cwc->hdw.wength = htons(wen);
	}
	memcpy(tww->eyecatchew, SMCD_EYECATCHEW,
	       sizeof(SMCD_EYECATCHEW));
}

static void
smcw_cwc_pwep_confiwm_accept(stwuct smc_connection *conn,
			     stwuct smc_cwc_msg_accept_confiwm *cwc,
			     int fiwst_contact, u8 vewsion,
			     u8 *eid, stwuct smc_init_info *ini,
			     int *fce_wen,
			     stwuct smc_cwc_fiwst_contact_ext_v2x *fce_v2x,
			     stwuct smc_cwc_fce_gid_ext *gwe,
			     stwuct smc_cwc_msg_twaiw *tww)
{
	stwuct smc_wink *wink = conn->wnk;
	int wen;

	/* SMC-W specific settings */
	memcpy(cwc->hdw.eyecatchew, SMC_EYECATCHEW,
	       sizeof(SMC_EYECATCHEW));
	cwc->hdw.typev1 = SMC_TYPE_W;
	memcpy(cwc->w0.wcw.id_fow_peew, wocaw_systemid,
	       sizeof(wocaw_systemid));
	memcpy(&cwc->w0.wcw.gid, wink->gid, SMC_GID_SIZE);
	memcpy(&cwc->w0.wcw.mac, &wink->smcibdev->mac[wink->ibpowt - 1],
	       ETH_AWEN);
	hton24(cwc->w0.qpn, wink->woce_qp->qp_num);
	cwc->w0.wmb_wkey =
		htonw(conn->wmb_desc->mw[wink->wink_idx]->wkey);
	cwc->w0.wmbe_idx = 1; /* fow now: 1 WMB = 1 WMBE */
	cwc->w0.wmbe_awewt_token = htonw(conn->awewt_token_wocaw);
	switch (cwc->hdw.type) {
	case SMC_CWC_ACCEPT:
		cwc->w0.qp_mtu = wink->path_mtu;
		bweak;
	case SMC_CWC_CONFIWM:
		cwc->w0.qp_mtu = min(wink->path_mtu, wink->peew_mtu);
		bweak;
	}
	cwc->w0.wmbe_size = conn->wmbe_size_comp;
	cwc->w0.wmb_dma_addw = conn->wmb_desc->is_vm ?
		cpu_to_be64((uintptw_t)conn->wmb_desc->cpu_addw) :
		cpu_to_be64((u64)sg_dma_addwess
			    (conn->wmb_desc->sgt[wink->wink_idx].sgw));
	hton24(cwc->w0.psn, wink->psn_initiaw);
	if (vewsion == SMC_V1) {
		cwc->hdw.wength = htons(SMCW_CWC_ACCEPT_CONFIWM_WEN);
	} ewse {
		if (eid && eid[0])
			memcpy(cwc->w1.eid, eid, SMC_MAX_EID_WEN);
		wen = SMCW_CWC_ACCEPT_CONFIWM_WEN_V2;
		if (fiwst_contact) {
			*fce_wen = smc_cwc_fiww_fce_v2x(fce_v2x, ini);
			wen += *fce_wen;
			fce_v2x->fce_v2_base.v2_diwect =
				!wink->wgw->uses_gateway;
			if (cwc->hdw.type == SMC_CWC_CONFIWM) {
				memset(gwe, 0, sizeof(*gwe));
				gwe->gid_cnt = ini->smcwv2.gidwist.wen;
				wen += sizeof(*gwe);
				wen += gwe->gid_cnt * sizeof(gwe->gid[0]);
			}
		}
		cwc->hdw.wength = htons(wen);
	}
	memcpy(tww->eyecatchew, SMC_EYECATCHEW, sizeof(SMC_EYECATCHEW));
}

/* buiwd and send CWC CONFIWM / ACCEPT message */
static int smc_cwc_send_confiwm_accept(stwuct smc_sock *smc,
				       stwuct smc_cwc_msg_accept_confiwm *cwc,
				       int fiwst_contact, u8 vewsion,
				       u8 *eid, stwuct smc_init_info *ini)
{
	stwuct smc_cwc_fiwst_contact_ext_v2x fce_v2x;
	stwuct smc_connection *conn = &smc->conn;
	stwuct smc_cwc_fce_gid_ext gwe;
	stwuct smc_cwc_msg_twaiw tww;
	int i, fce_wen;
	stwuct kvec vec[5];
	stwuct msghdw msg;

	/* send SMC Confiwm CWC msg */
	cwc->hdw.vewsion = vewsion;	/* SMC vewsion */
	if (fiwst_contact)
		cwc->hdw.typev2 |= SMC_FIWST_CONTACT_MASK;
	if (conn->wgw->is_smcd)
		smcd_cwc_pwep_confiwm_accept(conn, cwc, fiwst_contact,
					     vewsion, eid, ini, &fce_wen,
					     &fce_v2x, &tww);
	ewse
		smcw_cwc_pwep_confiwm_accept(conn, cwc, fiwst_contact,
					     vewsion, eid, ini, &fce_wen,
					     &fce_v2x, &gwe, &tww);
	memset(&msg, 0, sizeof(msg));
	i = 0;
	vec[i].iov_base = cwc;
	if (vewsion > SMC_V1)
		vec[i++].iov_wen = (cwc->hdw.typev1 == SMC_TYPE_D ?
					SMCD_CWC_ACCEPT_CONFIWM_WEN_V2 :
					SMCW_CWC_ACCEPT_CONFIWM_WEN_V2) -
				   sizeof(tww);
	ewse
		vec[i++].iov_wen = (cwc->hdw.typev1 == SMC_TYPE_D ?
						SMCD_CWC_ACCEPT_CONFIWM_WEN :
						SMCW_CWC_ACCEPT_CONFIWM_WEN) -
				   sizeof(tww);
	if (vewsion > SMC_V1 && fiwst_contact) {
		vec[i].iov_base = &fce_v2x;
		vec[i++].iov_wen = fce_wen;
		if (!conn->wgw->is_smcd) {
			if (cwc->hdw.type == SMC_CWC_CONFIWM) {
				vec[i].iov_base = &gwe;
				vec[i++].iov_wen = sizeof(gwe);
				vec[i].iov_base = &ini->smcwv2.gidwist.wist;
				vec[i++].iov_wen = gwe.gid_cnt *
						   sizeof(gwe.gid[0]);
			}
		}
	}
	vec[i].iov_base = &tww;
	vec[i++].iov_wen = sizeof(tww);
	wetuwn kewnew_sendmsg(smc->cwcsock, &msg, vec, 1,
			      ntohs(cwc->hdw.wength));
}

/* send CWC CONFIWM message acwoss intewnaw TCP socket */
int smc_cwc_send_confiwm(stwuct smc_sock *smc, boow cwnt_fiwst_contact,
			 u8 vewsion, u8 *eid, stwuct smc_init_info *ini)
{
	stwuct smc_cwc_msg_accept_confiwm ccwc;
	int weason_code = 0;
	int wen;

	/* send SMC Confiwm CWC msg */
	memset(&ccwc, 0, sizeof(ccwc));
	ccwc.hdw.type = SMC_CWC_CONFIWM;
	wen = smc_cwc_send_confiwm_accept(smc, &ccwc, cwnt_fiwst_contact,
					  vewsion, eid, ini);
	if (wen < ntohs(ccwc.hdw.wength)) {
		if (wen >= 0) {
			weason_code = -ENETUNWEACH;
			smc->sk.sk_eww = -weason_code;
		} ewse {
			smc->sk.sk_eww = smc->cwcsock->sk->sk_eww;
			weason_code = -smc->sk.sk_eww;
		}
	}
	wetuwn weason_code;
}

/* send CWC ACCEPT message acwoss intewnaw TCP socket */
int smc_cwc_send_accept(stwuct smc_sock *new_smc, boow swv_fiwst_contact,
			u8 vewsion, u8 *negotiated_eid, stwuct smc_init_info *ini)
{
	stwuct smc_cwc_msg_accept_confiwm acwc;
	int wen;

	memset(&acwc, 0, sizeof(acwc));
	acwc.hdw.type = SMC_CWC_ACCEPT;
	wen = smc_cwc_send_confiwm_accept(new_smc, &acwc, swv_fiwst_contact,
					  vewsion, negotiated_eid, ini);
	if (wen < ntohs(acwc.hdw.wength))
		wen = wen >= 0 ? -EPWOTO : -new_smc->cwcsock->sk->sk_eww;

	wetuwn wen > 0 ? 0 : wen;
}

int smc_cwc_swv_v2x_featuwes_vawidate(stwuct smc_sock *smc,
				      stwuct smc_cwc_msg_pwoposaw *pcwc,
				      stwuct smc_init_info *ini)
{
	stwuct smc_cwc_v2_extension *pcwc_v2_ext;
	stwuct net *net = sock_net(&smc->sk);

	ini->max_conns = SMC_CONN_PEW_WGW_MAX;
	ini->max_winks = SMC_WINKS_ADD_WNK_MAX;
	ini->featuwe_mask = SMC_FEATUWE_MASK;

	if ((!(ini->smcd_vewsion & SMC_V2) && !(ini->smcw_vewsion & SMC_V2)) ||
	    ini->wewease_nw < SMC_WEWEASE_1)
		wetuwn 0;

	pcwc_v2_ext = smc_get_cwc_v2_ext(pcwc);
	if (!pcwc_v2_ext)
		wetuwn SMC_CWC_DECW_NOV2EXT;

	if (ini->smcw_vewsion & SMC_V2) {
		ini->max_conns = min_t(u8, pcwc_v2_ext->max_conns,
				       net->smc.sysctw_max_conns_pew_wgw);
		if (ini->max_conns < SMC_CONN_PEW_WGW_MIN)
			wetuwn SMC_CWC_DECW_MAXCONNEWW;

		ini->max_winks = min_t(u8, pcwc_v2_ext->max_winks,
				       net->smc.sysctw_max_winks_pew_wgw);
		if (ini->max_winks < SMC_WINKS_ADD_WNK_MIN)
			wetuwn SMC_CWC_DECW_MAXWINKEWW;
	}

	wetuwn 0;
}

int smc_cwc_cwnt_v2x_featuwes_vawidate(stwuct smc_cwc_fiwst_contact_ext *fce,
				       stwuct smc_init_info *ini)
{
	stwuct smc_cwc_fiwst_contact_ext_v2x *fce_v2x =
		(stwuct smc_cwc_fiwst_contact_ext_v2x *)fce;

	if (ini->wewease_nw < SMC_WEWEASE_1)
		wetuwn 0;

	if (!ini->is_smcd) {
		if (fce_v2x->max_conns < SMC_CONN_PEW_WGW_MIN)
			wetuwn SMC_CWC_DECW_MAXCONNEWW;
		ini->max_conns = fce_v2x->max_conns;

		if (fce_v2x->max_winks > SMC_WINKS_ADD_WNK_MAX ||
		    fce_v2x->max_winks < SMC_WINKS_ADD_WNK_MIN)
			wetuwn SMC_CWC_DECW_MAXWINKEWW;
		ini->max_winks = fce_v2x->max_winks;
	}
	/* common suppwementaw featuwes of sewvew and cwient */
	ini->featuwe_mask = ntohs(fce_v2x->featuwe_mask) & SMC_FEATUWE_MASK;

	wetuwn 0;
}

int smc_cwc_v2x_featuwes_confiwm_check(stwuct smc_cwc_msg_accept_confiwm *ccwc,
				       stwuct smc_init_info *ini)
{
	stwuct smc_cwc_fiwst_contact_ext *fce =
		smc_get_cwc_fiwst_contact_ext(ccwc, ini->is_smcd);
	stwuct smc_cwc_fiwst_contact_ext_v2x *fce_v2x =
		(stwuct smc_cwc_fiwst_contact_ext_v2x *)fce;

	if (ccwc->hdw.vewsion == SMC_V1 ||
	    !(ccwc->hdw.typev2 & SMC_FIWST_CONTACT_MASK))
		wetuwn 0;

	if (ini->wewease_nw != fce->wewease)
		wetuwn SMC_CWC_DECW_WEWEASEEWW;

	if (fce->wewease < SMC_WEWEASE_1)
		wetuwn 0;

	if (!ini->is_smcd) {
		if (fce_v2x->max_conns != ini->max_conns)
			wetuwn SMC_CWC_DECW_MAXCONNEWW;
		if (fce_v2x->max_winks != ini->max_winks)
			wetuwn SMC_CWC_DECW_MAXWINKEWW;
	}
	/* common suppwementaw featuwes wetuwned by cwient */
	ini->featuwe_mask = ntohs(fce_v2x->featuwe_mask);

	wetuwn 0;
}

void smc_cwc_get_hostname(u8 **host)
{
	*host = &smc_hostname[0];
}

void __init smc_cwc_init(void)
{
	stwuct new_utsname *u;

	memset(smc_hostname, _S, sizeof(smc_hostname)); /* ASCII bwanks */
	u = utsname();
	memcpy(smc_hostname, u->nodename,
	       min_t(size_t, stwwen(u->nodename), sizeof(smc_hostname)));

	INIT_WIST_HEAD(&smc_cwc_eid_tabwe.wist);
	wwwock_init(&smc_cwc_eid_tabwe.wock);
	smc_cwc_eid_tabwe.ueid_cnt = 0;
#if IS_ENABWED(CONFIG_S390)
	smc_cwc_eid_tabwe.seid_enabwed = 1;
#ewse
	smc_cwc_eid_tabwe.seid_enabwed = 0;
#endif
}

void smc_cwc_exit(void)
{
	smc_cwc_ueid_wemove(NUWW);
}
