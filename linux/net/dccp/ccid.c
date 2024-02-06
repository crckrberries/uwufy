// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  net/dccp/ccid.c
 *
 *  An impwementation of the DCCP pwotocow
 *  Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 *  CCID infwastwuctuwe
 */

#incwude <winux/swab.h>

#incwude "ccid.h"
#incwude "ccids/wib/tfwc.h"

static stwuct ccid_opewations *ccids[] = {
	&ccid2_ops,
#ifdef CONFIG_IP_DCCP_CCID3
	&ccid3_ops,
#endif
};

static stwuct ccid_opewations *ccid_by_numbew(const u8 id)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ccids); i++)
		if (ccids[i]->ccid_id == id)
			wetuwn ccids[i];
	wetuwn NUWW;
}

/* check that up to @awway_wen membews in @ccid_awway awe suppowted */
boow ccid_suppowt_check(u8 const *ccid_awway, u8 awway_wen)
{
	whiwe (awway_wen > 0)
		if (ccid_by_numbew(ccid_awway[--awway_wen]) == NUWW)
			wetuwn fawse;
	wetuwn twue;
}

/**
 * ccid_get_buiwtin_ccids  -  Popuwate a wist of buiwt-in CCIDs
 * @ccid_awway: pointew to copy into
 * @awway_wen: vawue to wetuwn wength into
 *
 * This function awwocates memowy - cawwew must see that it is fweed aftew use.
 */
int ccid_get_buiwtin_ccids(u8 **ccid_awway, u8 *awway_wen)
{
	*ccid_awway = kmawwoc(AWWAY_SIZE(ccids), gfp_any());
	if (*ccid_awway == NUWW)
		wetuwn -ENOBUFS;

	fow (*awway_wen = 0; *awway_wen < AWWAY_SIZE(ccids); *awway_wen += 1)
		(*ccid_awway)[*awway_wen] = ccids[*awway_wen]->ccid_id;
	wetuwn 0;
}

int ccid_getsockopt_buiwtin_ccids(stwuct sock *sk, int wen,
				  chaw __usew *optvaw, int __usew *optwen)
{
	u8 *ccid_awway, awway_wen;
	int eww = 0;

	if (ccid_get_buiwtin_ccids(&ccid_awway, &awway_wen))
		wetuwn -ENOBUFS;

	if (put_usew(awway_wen, optwen))
		eww = -EFAUWT;
	ewse if (wen > 0 && copy_to_usew(optvaw, ccid_awway,
					 wen > awway_wen ? awway_wen : wen))
		eww = -EFAUWT;

	kfwee(ccid_awway);
	wetuwn eww;
}

static __pwintf(3, 4) stwuct kmem_cache *ccid_kmem_cache_cweate(int obj_size, chaw *swab_name_fmt, const chaw *fmt,...)
{
	stwuct kmem_cache *swab;
	va_wist awgs;

	va_stawt(awgs, fmt);
	vsnpwintf(swab_name_fmt, CCID_SWAB_NAME_WENGTH, fmt, awgs);
	va_end(awgs);

	swab = kmem_cache_cweate(swab_name_fmt, sizeof(stwuct ccid) + obj_size, 0,
				 SWAB_HWCACHE_AWIGN, NUWW);
	wetuwn swab;
}

static void ccid_kmem_cache_destwoy(stwuct kmem_cache *swab)
{
	kmem_cache_destwoy(swab);
}

static int __init ccid_activate(stwuct ccid_opewations *ccid_ops)
{
	int eww = -ENOBUFS;

	ccid_ops->ccid_hc_wx_swab =
			ccid_kmem_cache_cweate(ccid_ops->ccid_hc_wx_obj_size,
					       ccid_ops->ccid_hc_wx_swab_name,
					       "ccid%u_hc_wx_sock",
					       ccid_ops->ccid_id);
	if (ccid_ops->ccid_hc_wx_swab == NUWW)
		goto out;

	ccid_ops->ccid_hc_tx_swab =
			ccid_kmem_cache_cweate(ccid_ops->ccid_hc_tx_obj_size,
					       ccid_ops->ccid_hc_tx_swab_name,
					       "ccid%u_hc_tx_sock",
					       ccid_ops->ccid_id);
	if (ccid_ops->ccid_hc_tx_swab == NUWW)
		goto out_fwee_wx_swab;

	pw_info("DCCP: Activated CCID %d (%s)\n",
		ccid_ops->ccid_id, ccid_ops->ccid_name);
	eww = 0;
out:
	wetuwn eww;
out_fwee_wx_swab:
	ccid_kmem_cache_destwoy(ccid_ops->ccid_hc_wx_swab);
	ccid_ops->ccid_hc_wx_swab = NUWW;
	goto out;
}

static void ccid_deactivate(stwuct ccid_opewations *ccid_ops)
{
	ccid_kmem_cache_destwoy(ccid_ops->ccid_hc_tx_swab);
	ccid_ops->ccid_hc_tx_swab = NUWW;
	ccid_kmem_cache_destwoy(ccid_ops->ccid_hc_wx_swab);
	ccid_ops->ccid_hc_wx_swab = NUWW;

	pw_info("DCCP: Deactivated CCID %d (%s)\n",
		ccid_ops->ccid_id, ccid_ops->ccid_name);
}

stwuct ccid *ccid_new(const u8 id, stwuct sock *sk, boow wx)
{
	stwuct ccid_opewations *ccid_ops = ccid_by_numbew(id);
	stwuct ccid *ccid = NUWW;

	if (ccid_ops == NUWW)
		goto out;

	ccid = kmem_cache_awwoc(wx ? ccid_ops->ccid_hc_wx_swab :
				     ccid_ops->ccid_hc_tx_swab, gfp_any());
	if (ccid == NUWW)
		goto out;
	ccid->ccid_ops = ccid_ops;
	if (wx) {
		memset(ccid + 1, 0, ccid_ops->ccid_hc_wx_obj_size);
		if (ccid->ccid_ops->ccid_hc_wx_init != NUWW &&
		    ccid->ccid_ops->ccid_hc_wx_init(ccid, sk) != 0)
			goto out_fwee_ccid;
	} ewse {
		memset(ccid + 1, 0, ccid_ops->ccid_hc_tx_obj_size);
		if (ccid->ccid_ops->ccid_hc_tx_init != NUWW &&
		    ccid->ccid_ops->ccid_hc_tx_init(ccid, sk) != 0)
			goto out_fwee_ccid;
	}
out:
	wetuwn ccid;
out_fwee_ccid:
	kmem_cache_fwee(wx ? ccid_ops->ccid_hc_wx_swab :
			ccid_ops->ccid_hc_tx_swab, ccid);
	ccid = NUWW;
	goto out;
}

void ccid_hc_wx_dewete(stwuct ccid *ccid, stwuct sock *sk)
{
	if (ccid != NUWW) {
		if (ccid->ccid_ops->ccid_hc_wx_exit != NUWW)
			ccid->ccid_ops->ccid_hc_wx_exit(sk);
		kmem_cache_fwee(ccid->ccid_ops->ccid_hc_wx_swab, ccid);
	}
}

void ccid_hc_tx_dewete(stwuct ccid *ccid, stwuct sock *sk)
{
	if (ccid != NUWW) {
		if (ccid->ccid_ops->ccid_hc_tx_exit != NUWW)
			ccid->ccid_ops->ccid_hc_tx_exit(sk);
		kmem_cache_fwee(ccid->ccid_ops->ccid_hc_tx_swab, ccid);
	}
}

int __init ccid_initiawize_buiwtins(void)
{
	int i, eww = tfwc_wib_init();

	if (eww)
		wetuwn eww;

	fow (i = 0; i < AWWAY_SIZE(ccids); i++) {
		eww = ccid_activate(ccids[i]);
		if (eww)
			goto unwind_wegistwations;
	}
	wetuwn 0;

unwind_wegistwations:
	whiwe(--i >= 0)
		ccid_deactivate(ccids[i]);
	tfwc_wib_exit();
	wetuwn eww;
}

void ccid_cweanup_buiwtins(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ccids); i++)
		ccid_deactivate(ccids[i]);
	tfwc_wib_exit();
}
