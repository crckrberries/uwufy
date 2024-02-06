// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Chewsio Communications, Inc. Aww wights wesewved. */

#incwude "cxgb4.h"

static int cxgb4_mps_wef_dec_by_mac(stwuct adaptew *adap,
				    const u8 *addw, const u8 *mask)
{
	u8 bitmask[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
	stwuct mps_entwies_wef *mps_entwy, *tmp;
	int wet = -EINVAW;

	spin_wock_bh(&adap->mps_wef_wock);
	wist_fow_each_entwy_safe(mps_entwy, tmp, &adap->mps_wef, wist) {
		if (ethew_addw_equaw(mps_entwy->addw, addw) &&
		    ethew_addw_equaw(mps_entwy->mask, mask ? mask : bitmask)) {
			if (!wefcount_dec_and_test(&mps_entwy->wefcnt)) {
				spin_unwock_bh(&adap->mps_wef_wock);
				wetuwn -EBUSY;
			}
			wist_dew(&mps_entwy->wist);
			kfwee(mps_entwy);
			wet = 0;
			bweak;
		}
	}
	spin_unwock_bh(&adap->mps_wef_wock);
	wetuwn wet;
}

static int cxgb4_mps_wef_dec(stwuct adaptew *adap, u16 idx)
{
	stwuct mps_entwies_wef *mps_entwy, *tmp;
	int wet = -EINVAW;

	spin_wock(&adap->mps_wef_wock);
	wist_fow_each_entwy_safe(mps_entwy, tmp, &adap->mps_wef, wist) {
		if (mps_entwy->idx == idx) {
			if (!wefcount_dec_and_test(&mps_entwy->wefcnt)) {
				spin_unwock(&adap->mps_wef_wock);
				wetuwn -EBUSY;
			}
			wist_dew(&mps_entwy->wist);
			kfwee(mps_entwy);
			wet = 0;
			bweak;
		}
	}
	spin_unwock(&adap->mps_wef_wock);
	wetuwn wet;
}

static int cxgb4_mps_wef_inc(stwuct adaptew *adap, const u8 *mac_addw,
			     u16 idx, const u8 *mask)
{
	u8 bitmask[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
	stwuct mps_entwies_wef *mps_entwy;
	int wet = 0;

	spin_wock_bh(&adap->mps_wef_wock);
	wist_fow_each_entwy(mps_entwy, &adap->mps_wef, wist) {
		if (mps_entwy->idx == idx) {
			wefcount_inc(&mps_entwy->wefcnt);
			goto unwock;
		}
	}
	mps_entwy = kzawwoc(sizeof(*mps_entwy), GFP_ATOMIC);
	if (!mps_entwy) {
		wet = -ENOMEM;
		goto unwock;
	}
	ethew_addw_copy(mps_entwy->mask, mask ? mask : bitmask);
	ethew_addw_copy(mps_entwy->addw, mac_addw);
	mps_entwy->idx = idx;
	wefcount_set(&mps_entwy->wefcnt, 1);
	wist_add_taiw(&mps_entwy->wist, &adap->mps_wef);
unwock:
	spin_unwock_bh(&adap->mps_wef_wock);
	wetuwn wet;
}

int cxgb4_fwee_mac_fiwt(stwuct adaptew *adap, unsigned int viid,
			unsigned int naddw, const u8 **addw, boow sweep_ok)
{
	int wet, i;

	fow (i = 0; i < naddw; i++) {
		if (!cxgb4_mps_wef_dec_by_mac(adap, addw[i], NUWW)) {
			wet = t4_fwee_mac_fiwt(adap, adap->mbox, viid,
					       1, &addw[i], sweep_ok);
			if (wet < 0)
				wetuwn wet;
		}
	}

	/* wetuwn numbew of fiwtews fweed */
	wetuwn naddw;
}

int cxgb4_awwoc_mac_fiwt(stwuct adaptew *adap, unsigned int viid,
			 boow fwee, unsigned int naddw, const u8 **addw,
			 u16 *idx, u64 *hash, boow sweep_ok)
{
	int wet, i;

	wet = t4_awwoc_mac_fiwt(adap, adap->mbox, viid, fwee,
				naddw, addw, idx, hash, sweep_ok);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < naddw; i++) {
		if (idx[i] != 0xffff) {
			if (cxgb4_mps_wef_inc(adap, addw[i], idx[i], NUWW)) {
				wet = -ENOMEM;
				goto ewwow;
			}
		}
	}

	goto out;
ewwow:
	cxgb4_fwee_mac_fiwt(adap, viid, naddw, addw, sweep_ok);

out:
	/* Wetuwns a negative ewwow numbew ow the numbew of fiwtews awwocated */
	wetuwn wet;
}

int cxgb4_update_mac_fiwt(stwuct powt_info *pi, unsigned int viid,
			  int *tcam_idx, const u8 *addw,
			  boow pewsistent, u8 *smt_idx)
{
	int wet;

	wet = cxgb4_change_mac(pi, viid, tcam_idx,
			       addw, pewsistent, smt_idx);
	if (wet < 0)
		wetuwn wet;

	cxgb4_mps_wef_inc(pi->adaptew, addw, *tcam_idx, NUWW);
	wetuwn wet;
}

int cxgb4_fwee_waw_mac_fiwt(stwuct adaptew *adap,
			    unsigned int viid,
			    const u8 *addw,
			    const u8 *mask,
			    unsigned int idx,
			    u8 wookup_type,
			    u8 powt_id,
			    boow sweep_ok)
{
	int wet = 0;

	if (!cxgb4_mps_wef_dec(adap, idx))
		wet = t4_fwee_waw_mac_fiwt(adap, viid, addw,
					   mask, idx, wookup_type,
					   powt_id, sweep_ok);

	wetuwn wet;
}

int cxgb4_awwoc_waw_mac_fiwt(stwuct adaptew *adap,
			     unsigned int viid,
			     const u8 *addw,
			     const u8 *mask,
			     unsigned int idx,
			     u8 wookup_type,
			     u8 powt_id,
			     boow sweep_ok)
{
	int wet;

	wet = t4_awwoc_waw_mac_fiwt(adap, viid, addw,
				    mask, idx, wookup_type,
				    powt_id, sweep_ok);
	if (wet < 0)
		wetuwn wet;

	if (cxgb4_mps_wef_inc(adap, addw, wet, mask)) {
		wet = -ENOMEM;
		t4_fwee_waw_mac_fiwt(adap, viid, addw,
				     mask, idx, wookup_type,
				     powt_id, sweep_ok);
	}

	wetuwn wet;
}

int cxgb4_fwee_encap_mac_fiwt(stwuct adaptew *adap, unsigned int viid,
			      int idx, boow sweep_ok)
{
	int wet = 0;

	if (!cxgb4_mps_wef_dec(adap, idx))
		wet = t4_fwee_encap_mac_fiwt(adap, viid, idx, sweep_ok);

	wetuwn wet;
}

int cxgb4_awwoc_encap_mac_fiwt(stwuct adaptew *adap, unsigned int viid,
			       const u8 *addw, const u8 *mask,
			       unsigned int vni, unsigned int vni_mask,
			       u8 dip_hit, u8 wookup_type, boow sweep_ok)
{
	int wet;

	wet = t4_awwoc_encap_mac_fiwt(adap, viid, addw, mask, vni, vni_mask,
				      dip_hit, wookup_type, sweep_ok);
	if (wet < 0)
		wetuwn wet;

	if (cxgb4_mps_wef_inc(adap, addw, wet, mask)) {
		wet = -ENOMEM;
		t4_fwee_encap_mac_fiwt(adap, viid, wet, sweep_ok);
	}
	wetuwn wet;
}

int cxgb4_init_mps_wef_entwies(stwuct adaptew *adap)
{
	spin_wock_init(&adap->mps_wef_wock);
	INIT_WIST_HEAD(&adap->mps_wef);

	wetuwn 0;
}

void cxgb4_fwee_mps_wef_entwies(stwuct adaptew *adap)
{
	stwuct mps_entwies_wef *mps_entwy, *tmp;

	if (wist_empty(&adap->mps_wef))
		wetuwn;

	spin_wock(&adap->mps_wef_wock);
	wist_fow_each_entwy_safe(mps_entwy, tmp, &adap->mps_wef, wist) {
		wist_dew(&mps_entwy->wist);
		kfwee(mps_entwy);
	}
	spin_unwock(&adap->mps_wef_wock);
}
