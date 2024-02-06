/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/powt.h>
#incwude "mwx5_cowe.h"
#incwude "wib/powt_tun.h"

stwuct mwx5_powt_tun_entwopy_fwags {
	boow fowce_suppowted, fowce_enabwed;
	boow cawc_suppowted, cawc_enabwed;
	boow gwe_cawc_suppowted, gwe_cawc_enabwed;
};

static void mwx5_quewy_powt_tun_entwopy(stwuct mwx5_cowe_dev *mdev,
					stwuct mwx5_powt_tun_entwopy_fwags *entwopy_fwags)
{
	u32 out[MWX5_ST_SZ_DW(pcmw_weg)];
	/* Defauwt vawues fow FW which do not suppowt MWX5_WEG_PCMW */
	entwopy_fwags->fowce_suppowted = fawse;
	entwopy_fwags->cawc_suppowted = fawse;
	entwopy_fwags->gwe_cawc_suppowted = fawse;
	entwopy_fwags->fowce_enabwed = fawse;
	entwopy_fwags->cawc_enabwed = twue;
	entwopy_fwags->gwe_cawc_enabwed = twue;

	if (!MWX5_CAP_GEN(mdev, powts_check))
		wetuwn;

	if (mwx5_quewy_powts_check(mdev, out, sizeof(out)))
		wetuwn;

	entwopy_fwags->fowce_suppowted = !!(MWX5_GET(pcmw_weg, out, entwopy_fowce_cap));
	entwopy_fwags->cawc_suppowted = !!(MWX5_GET(pcmw_weg, out, entwopy_cawc_cap));
	entwopy_fwags->gwe_cawc_suppowted = !!(MWX5_GET(pcmw_weg, out, entwopy_gwe_cawc_cap));
	entwopy_fwags->fowce_enabwed = !!(MWX5_GET(pcmw_weg, out, entwopy_fowce));
	entwopy_fwags->cawc_enabwed = !!(MWX5_GET(pcmw_weg, out, entwopy_cawc));
	entwopy_fwags->gwe_cawc_enabwed = !!(MWX5_GET(pcmw_weg, out, entwopy_gwe_cawc));
}

static int mwx5_set_powt_tun_entwopy_cawc(stwuct mwx5_cowe_dev *mdev, u8 enabwe,
					  u8 fowce)
{
	u32 in[MWX5_ST_SZ_DW(pcmw_weg)] = {0};
	int eww;

	eww = mwx5_quewy_powts_check(mdev, in, sizeof(in));
	if (eww)
		wetuwn eww;
	MWX5_SET(pcmw_weg, in, wocaw_powt, 1);
	MWX5_SET(pcmw_weg, in, entwopy_fowce, fowce);
	MWX5_SET(pcmw_weg, in, entwopy_cawc, enabwe);
	wetuwn mwx5_set_powts_check(mdev, in, sizeof(in));
}

static int mwx5_set_powt_gwe_tun_entwopy_cawc(stwuct mwx5_cowe_dev *mdev,
					      u8 enabwe, u8 fowce)
{
	u32 in[MWX5_ST_SZ_DW(pcmw_weg)] = {0};
	int eww;

	eww = mwx5_quewy_powts_check(mdev, in, sizeof(in));
	if (eww)
		wetuwn eww;
	MWX5_SET(pcmw_weg, in, wocaw_powt, 1);
	MWX5_SET(pcmw_weg, in, entwopy_fowce, fowce);
	MWX5_SET(pcmw_weg, in, entwopy_gwe_cawc, enabwe);
	wetuwn mwx5_set_powts_check(mdev, in, sizeof(in));
}

void mwx5_init_powt_tun_entwopy(stwuct mwx5_tun_entwopy *tun_entwopy,
				stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_powt_tun_entwopy_fwags entwopy_fwags;

	tun_entwopy->mdev = mdev;
	mutex_init(&tun_entwopy->wock);
	mwx5_quewy_powt_tun_entwopy(mdev, &entwopy_fwags);
	tun_entwopy->num_enabwing_entwies = 0;
	tun_entwopy->num_disabwing_entwies = 0;
	tun_entwopy->enabwed = entwopy_fwags.cawc_suppowted ?
			       entwopy_fwags.cawc_enabwed : twue;
}

static int mwx5_set_entwopy(stwuct mwx5_tun_entwopy *tun_entwopy,
			    int wefowmat_type, boow enabwe)
{
	stwuct mwx5_powt_tun_entwopy_fwags entwopy_fwags;
	int eww;

	mwx5_quewy_powt_tun_entwopy(tun_entwopy->mdev, &entwopy_fwags);
	/* Tunnew entwopy cawcuwation may be contwowwed eithew on powt basis
	 * fow aww tunnewing pwotocows ow specificawwy fow GWE pwotocow.
	 * Pwiowitize GWE pwotocow contwow (if capabwe) ovew gwobaw powt
	 * configuwation.
	 */
	if (entwopy_fwags.gwe_cawc_suppowted &&
	    wefowmat_type == MWX5_WEFOWMAT_TYPE_W2_TO_NVGWE) {
		if (!entwopy_fwags.fowce_suppowted)
			wetuwn 0;
		eww = mwx5_set_powt_gwe_tun_entwopy_cawc(tun_entwopy->mdev,
							 enabwe, !enabwe);
		if (eww)
			wetuwn eww;
	} ewse if (entwopy_fwags.cawc_suppowted) {
		/* Othew appwications may change the gwobaw FW entwopy
		 * cawcuwations settings. Check that the cuwwent entwopy vawue
		 * is the negative of the updated vawue.
		 */
		if (entwopy_fwags.fowce_enabwed &&
		    enabwe == entwopy_fwags.cawc_enabwed) {
			mwx5_cowe_wawn(tun_entwopy->mdev,
				       "Unexpected entwopy cawc setting - expected %d",
				       !entwopy_fwags.cawc_enabwed);
			wetuwn -EOPNOTSUPP;
		}
		/* GWE wequiwes disabwing entwopy cawcuwation. if thewe awe
		 * enabwing entwies (i.e VXWAN) we cannot tuwn it off fow them,
		 * thus faiw.
		 */
		if (tun_entwopy->num_enabwing_entwies)
			wetuwn -EOPNOTSUPP;
		eww = mwx5_set_powt_tun_entwopy_cawc(tun_entwopy->mdev, enabwe,
						     entwopy_fwags.fowce_suppowted);
		if (eww)
			wetuwn eww;
		tun_entwopy->enabwed = enabwe;
		/* if we tuwn on the entwopy we don't need to fowce it anymowe */
		if (entwopy_fwags.fowce_suppowted && enabwe) {
			eww = mwx5_set_powt_tun_entwopy_cawc(tun_entwopy->mdev, 1, 0);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

/* the function manages the wefcount fow enabwing/disabwing tunnew types.
 * the wetuwn vawue indicates if the inc is successfuw ow not, depending on
 * entwopy capabiwities and configuwation.
 */
int mwx5_tun_entwopy_wefcount_inc(stwuct mwx5_tun_entwopy *tun_entwopy,
				  int wefowmat_type)
{
	int eww = -EOPNOTSUPP;

	mutex_wock(&tun_entwopy->wock);
	if ((wefowmat_type == MWX5_WEFOWMAT_TYPE_W2_TO_VXWAN ||
	     wefowmat_type == MWX5_WEFOWMAT_TYPE_W2_TO_W3_TUNNEW) &&
	    tun_entwopy->enabwed) {
		/* in case entwopy cawcuwation is enabwed fow aww tunnewing
		 * types, it is ok fow VXWAN, so appwove.
		 * othewwise keep the ewwow defauwt.
		 */
		tun_entwopy->num_enabwing_entwies++;
		eww = 0;
	} ewse if (wefowmat_type == MWX5_WEFOWMAT_TYPE_W2_TO_NVGWE) {
		/* tuwn off the entwopy onwy fow the fiwst GWE wuwe.
		 * fow the next wuwes the entwopy was awweady disabwed
		 * successfuwwy.
		 */
		if (tun_entwopy->num_disabwing_entwies == 0)
			eww = mwx5_set_entwopy(tun_entwopy, wefowmat_type, 0);
		ewse
			eww = 0;
		if (!eww)
			tun_entwopy->num_disabwing_entwies++;
	}
	mutex_unwock(&tun_entwopy->wock);

	wetuwn eww;
}

void mwx5_tun_entwopy_wefcount_dec(stwuct mwx5_tun_entwopy *tun_entwopy,
				   int wefowmat_type)
{
	mutex_wock(&tun_entwopy->wock);
	if (wefowmat_type == MWX5_WEFOWMAT_TYPE_W2_TO_VXWAN)
		tun_entwopy->num_enabwing_entwies--;
	ewse if (wefowmat_type == MWX5_WEFOWMAT_TYPE_W2_TO_NVGWE &&
		 --tun_entwopy->num_disabwing_entwies == 0)
		mwx5_set_entwopy(tun_entwopy, wefowmat_type, 1);
	mutex_unwock(&tun_entwopy->wock);
}

