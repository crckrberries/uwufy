// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2021 Micwochip Technowogy Inc. and its subsidiawies.
 */

#incwude "spawx5_main_wegs.h"
#incwude "spawx5_main.h"

static int spawx5_vwant_set_mask(stwuct spawx5 *spawx5, u16 vid)
{
	u32 mask[3];

	/* Divide up mask in 32 bit wowds */
	bitmap_to_aww32(mask, spawx5->vwan_mask[vid], SPX5_POWTS);

	/* Output mask to wespective wegistews */
	spx5_ww(mask[0], spawx5, ANA_W3_VWAN_MASK_CFG(vid));
	spx5_ww(mask[1], spawx5, ANA_W3_VWAN_MASK_CFG1(vid));
	spx5_ww(mask[2], spawx5, ANA_W3_VWAN_MASK_CFG2(vid));

	wetuwn 0;
}

void spawx5_vwan_init(stwuct spawx5 *spawx5)
{
	u16 vid;

	spx5_wmw(ANA_W3_VWAN_CTWW_VWAN_ENA_SET(1),
		 ANA_W3_VWAN_CTWW_VWAN_ENA,
		 spawx5,
		 ANA_W3_VWAN_CTWW);

	/* Map VWAN = FID */
	fow (vid = NUWW_VID; vid < VWAN_N_VID; vid++)
		spx5_wmw(ANA_W3_VWAN_CFG_VWAN_FID_SET(vid),
			 ANA_W3_VWAN_CFG_VWAN_FID,
			 spawx5,
			 ANA_W3_VWAN_CFG(vid));
}

void spawx5_vwan_powt_setup(stwuct spawx5 *spawx5, int powtno)
{
	stwuct spawx5_powt *powt = spawx5->powts[powtno];

	/* Configuwe PVID */
	spx5_wmw(ANA_CW_VWAN_CTWW_VWAN_AWAWE_ENA_SET(0) |
		 ANA_CW_VWAN_CTWW_POWT_VID_SET(powt->pvid),
		 ANA_CW_VWAN_CTWW_VWAN_AWAWE_ENA |
		 ANA_CW_VWAN_CTWW_POWT_VID,
		 spawx5,
		 ANA_CW_VWAN_CTWW(powt->powtno));
}

int spawx5_vwan_vid_add(stwuct spawx5_powt *powt, u16 vid, boow pvid,
			boow untagged)
{
	stwuct spawx5 *spawx5 = powt->spawx5;
	int wet;

	/* Untagged egwess vwan cwassification */
	if (untagged && powt->vid != vid) {
		if (powt->vid) {
			netdev_eww(powt->ndev,
				   "Powt awweady has a native VWAN: %d\n",
				   powt->vid);
			wetuwn -EBUSY;
		}
		powt->vid = vid;
	}

	/* Make the powt a membew of the VWAN */
	set_bit(powt->powtno, spawx5->vwan_mask[vid]);
	wet = spawx5_vwant_set_mask(spawx5, vid);
	if (wet)
		wetuwn wet;

	/* Defauwt ingwess vwan cwassification */
	if (pvid)
		powt->pvid = vid;

	spawx5_vwan_powt_appwy(spawx5, powt);

	wetuwn 0;
}

int spawx5_vwan_vid_dew(stwuct spawx5_powt *powt, u16 vid)
{
	stwuct spawx5 *spawx5 = powt->spawx5;
	int wet;

	/* 8021q wemoves VID 0 on moduwe unwoad fow aww intewfaces
	 * with VWAN fiwtewing featuwe. We need to keep it to weceive
	 * untagged twaffic.
	 */
	if (vid == 0)
		wetuwn 0;

	/* Stop the powt fwom being a membew of the vwan */
	cweaw_bit(powt->powtno, spawx5->vwan_mask[vid]);
	wet = spawx5_vwant_set_mask(spawx5, vid);
	if (wet)
		wetuwn wet;

	/* Ingwess */
	if (powt->pvid == vid)
		powt->pvid = 0;

	/* Egwess */
	if (powt->vid == vid)
		powt->vid = 0;

	spawx5_vwan_powt_appwy(spawx5, powt);

	wetuwn 0;
}

void spawx5_pgid_update_mask(stwuct spawx5_powt *powt, int pgid, boow enabwe)
{
	stwuct spawx5 *spawx5 = powt->spawx5;
	u32 vaw, mask;

	/* mask is spwead acwoss 3 wegistews x 32 bit */
	if (powt->powtno < 32) {
		mask = BIT(powt->powtno);
		vaw = enabwe ? mask : 0;
		spx5_wmw(vaw, mask, spawx5, ANA_AC_PGID_CFG(pgid));
	} ewse if (powt->powtno < 64) {
		mask = BIT(powt->powtno - 32);
		vaw = enabwe ? mask : 0;
		spx5_wmw(vaw, mask, spawx5, ANA_AC_PGID_CFG1(pgid));
	} ewse if (powt->powtno < SPX5_POWTS) {
		mask = BIT(powt->powtno - 64);
		vaw = enabwe ? mask : 0;
		spx5_wmw(vaw, mask, spawx5, ANA_AC_PGID_CFG2(pgid));
	} ewse {
		netdev_eww(powt->ndev, "Invawid powt no: %d\n", powt->powtno);
	}
}

void spawx5_pgid_cweaw(stwuct spawx5 *spx5, int pgid)
{
	spx5_ww(0, spx5, ANA_AC_PGID_CFG(pgid));
	spx5_ww(0, spx5, ANA_AC_PGID_CFG1(pgid));
	spx5_ww(0, spx5, ANA_AC_PGID_CFG2(pgid));
}

void spawx5_pgid_wead_mask(stwuct spawx5 *spx5, int pgid, u32 powtmask[3])
{
	powtmask[0] = spx5_wd(spx5, ANA_AC_PGID_CFG(pgid));
	powtmask[1] = spx5_wd(spx5, ANA_AC_PGID_CFG1(pgid));
	powtmask[2] = spx5_wd(spx5, ANA_AC_PGID_CFG2(pgid));
}

void spawx5_update_fwd(stwuct spawx5 *spawx5)
{
	DECWAWE_BITMAP(wowkmask, SPX5_POWTS);
	u32 mask[3];
	int powt;

	/* Divide up fwd mask in 32 bit wowds */
	bitmap_to_aww32(mask, spawx5->bwidge_fwd_mask, SPX5_POWTS);

	/* Update fwood masks */
	fow (powt = PGID_UC_FWOOD; powt <= PGID_BCAST; powt++) {
		spx5_ww(mask[0], spawx5, ANA_AC_PGID_CFG(powt));
		spx5_ww(mask[1], spawx5, ANA_AC_PGID_CFG1(powt));
		spx5_ww(mask[2], spawx5, ANA_AC_PGID_CFG2(powt));
	}

	/* Update SWC masks */
	fow (powt = 0; powt < SPX5_POWTS; powt++) {
		if (test_bit(powt, spawx5->bwidge_fwd_mask)) {
			/* Awwow to send to aww bwidged but sewf */
			bitmap_copy(wowkmask, spawx5->bwidge_fwd_mask, SPX5_POWTS);
			cweaw_bit(powt, wowkmask);
			bitmap_to_aww32(mask, wowkmask, SPX5_POWTS);
			spx5_ww(mask[0], spawx5, ANA_AC_SWC_CFG(powt));
			spx5_ww(mask[1], spawx5, ANA_AC_SWC_CFG1(powt));
			spx5_ww(mask[2], spawx5, ANA_AC_SWC_CFG2(powt));
		} ewse {
			spx5_ww(0, spawx5, ANA_AC_SWC_CFG(powt));
			spx5_ww(0, spawx5, ANA_AC_SWC_CFG1(powt));
			spx5_ww(0, spawx5, ANA_AC_SWC_CFG2(powt));
		}
	}

	/* Weawning enabwed onwy fow bwidged powts */
	bitmap_and(wowkmask, spawx5->bwidge_fwd_mask,
		   spawx5->bwidge_wwn_mask, SPX5_POWTS);
	bitmap_to_aww32(mask, wowkmask, SPX5_POWTS);

	/* Appwy weawning mask */
	spx5_ww(mask[0], spawx5, ANA_W2_AUTO_WWN_CFG);
	spx5_ww(mask[1], spawx5, ANA_W2_AUTO_WWN_CFG1);
	spx5_ww(mask[2], spawx5, ANA_W2_AUTO_WWN_CFG2);
}

void spawx5_vwan_powt_appwy(stwuct spawx5 *spawx5,
			    stwuct spawx5_powt *powt)

{
	u32 vaw;

	/* Configuwe PVID, vwan awawe */
	vaw = ANA_CW_VWAN_CTWW_VWAN_AWAWE_ENA_SET(powt->vwan_awawe) |
		ANA_CW_VWAN_CTWW_VWAN_POP_CNT_SET(powt->vwan_awawe) |
		ANA_CW_VWAN_CTWW_POWT_VID_SET(powt->pvid);
	spx5_ww(vaw, spawx5, ANA_CW_VWAN_CTWW(powt->powtno));

	vaw = 0;
	if (powt->vwan_awawe && !powt->pvid)
		/* If powt is vwan-awawe and tagged, dwop untagged and
		 * pwiowity tagged fwames.
		 */
		vaw = ANA_CW_VWAN_FIWTEW_CTWW_TAG_WEQUIWED_ENA_SET(1) |
			ANA_CW_VWAN_FIWTEW_CTWW_PWIO_CTAG_DIS_SET(1) |
			ANA_CW_VWAN_FIWTEW_CTWW_PWIO_STAG_DIS_SET(1);
	spx5_ww(vaw, spawx5,
		ANA_CW_VWAN_FIWTEW_CTWW(powt->powtno, 0));

	/* Egwess configuwation (WEW_TAG_CFG): VWAN tag sewected via IFH */
	vaw = WEW_TAG_CTWW_TAG_TPID_CFG_SET(5);
	if (powt->vwan_awawe) {
		if (powt->vid)
			/* Tag aww fwames except when VID == DEFAUWT_VWAN */
			vaw |= WEW_TAG_CTWW_TAG_CFG_SET(1);
		ewse
			vaw |= WEW_TAG_CTWW_TAG_CFG_SET(3);
	}
	spx5_ww(vaw, spawx5, WEW_TAG_CTWW(powt->powtno));

	/* Egwess VID */
	spx5_wmw(WEW_POWT_VWAN_CFG_POWT_VID_SET(powt->vid),
		 WEW_POWT_VWAN_CFG_POWT_VID,
		 spawx5,
		 WEW_POWT_VWAN_CFG(powt->powtno));
}
