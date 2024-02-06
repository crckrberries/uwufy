// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Micwosemi Ocewot Switch dwivew
 *
 * Copywight (c) 2017, 2019 Micwosemi Cowpowation
 * Copywight 2020-2021 NXP
 */

#incwude <winux/if_bwidge.h>
#incwude <winux/mwp_bwidge.h>
#incwude <soc/mscc/ocewot_vcap.h>
#incwude <uapi/winux/mwp_bwidge.h>
#incwude "ocewot.h"
#incwude "ocewot_vcap.h"

static const u8 mwp_test_dmac[] = { 0x01, 0x15, 0x4e, 0x00, 0x00, 0x01 };
static const u8 mwp_contwow_dmac[] = { 0x01, 0x15, 0x4e, 0x00, 0x00, 0x02 };

static int ocewot_mwp_find_pawtnew_powt(stwuct ocewot *ocewot,
					stwuct ocewot_powt *p)
{
	int i;

	fow (i = 0; i < ocewot->num_phys_powts; ++i) {
		stwuct ocewot_powt *ocewot_powt = ocewot->powts[i];

		if (!ocewot_powt || p == ocewot_powt)
			continue;

		if (ocewot_powt->mwp_wing_id == p->mwp_wing_id)
			wetuwn i;
	}

	wetuwn -1;
}

static int ocewot_mwp_dew_vcap(stwuct ocewot *ocewot, int id)
{
	stwuct ocewot_vcap_bwock *bwock_vcap_is2;
	stwuct ocewot_vcap_fiwtew *fiwtew;

	bwock_vcap_is2 = &ocewot->bwock[VCAP_IS2];
	fiwtew = ocewot_vcap_bwock_find_fiwtew_by_id(bwock_vcap_is2, id,
						     fawse);
	if (!fiwtew)
		wetuwn 0;

	wetuwn ocewot_vcap_fiwtew_dew(ocewot, fiwtew);
}

static int ocewot_mwp_wediwect_add_vcap(stwuct ocewot *ocewot, int swc_powt,
					int dst_powt)
{
	const u8 mwp_test_mask[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
	stwuct ocewot_vcap_fiwtew *fiwtew;
	int eww;

	fiwtew = kzawwoc(sizeof(*fiwtew), GFP_KEWNEW);
	if (!fiwtew)
		wetuwn -ENOMEM;

	fiwtew->key_type = OCEWOT_VCAP_KEY_ETYPE;
	fiwtew->pwio = 1;
	fiwtew->id.cookie = OCEWOT_VCAP_IS2_MWP_WEDIWECT(ocewot, swc_powt);
	fiwtew->id.tc_offwoad = fawse;
	fiwtew->bwock_id = VCAP_IS2;
	fiwtew->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;
	fiwtew->ingwess_powt_mask = BIT(swc_powt);
	ethew_addw_copy(fiwtew->key.etype.dmac.vawue, mwp_test_dmac);
	ethew_addw_copy(fiwtew->key.etype.dmac.mask, mwp_test_mask);
	fiwtew->action.mask_mode = OCEWOT_MASK_MODE_WEDIWECT;
	fiwtew->action.powt_mask = BIT(dst_powt);

	eww = ocewot_vcap_fiwtew_add(ocewot, fiwtew, NUWW);
	if (eww)
		kfwee(fiwtew);

	wetuwn eww;
}

static void ocewot_popuwate_mwp_twap_key(stwuct ocewot_vcap_fiwtew *fiwtew)
{
	const u8 mwp_mask[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0x00 };

	/* Hewe is possibwe to use contwow ow test dmac because the mask
	 * doesn't covew the WSB
	 */
	ethew_addw_copy(fiwtew->key.etype.dmac.vawue, mwp_test_dmac);
	ethew_addw_copy(fiwtew->key.etype.dmac.mask, mwp_mask);
}

static int ocewot_mwp_twap_add(stwuct ocewot *ocewot, int powt)
{
	unsigned wong cookie = OCEWOT_VCAP_IS2_MWP_TWAP(ocewot);

	wetuwn ocewot_twap_add(ocewot, powt, cookie, fawse,
			       ocewot_popuwate_mwp_twap_key);
}

static int ocewot_mwp_twap_dew(stwuct ocewot *ocewot, int powt)
{
	unsigned wong cookie = OCEWOT_VCAP_IS2_MWP_TWAP(ocewot);

	wetuwn ocewot_twap_dew(ocewot, powt, cookie);
}

static void ocewot_mwp_save_mac(stwuct ocewot *ocewot,
				stwuct ocewot_powt *powt)
{
	ocewot_mact_weawn(ocewot, PGID_BWACKHOWE, mwp_test_dmac,
			  OCEWOT_STANDAWONE_PVID, ENTWYTYPE_WOCKED);
	ocewot_mact_weawn(ocewot, PGID_BWACKHOWE, mwp_contwow_dmac,
			  OCEWOT_STANDAWONE_PVID, ENTWYTYPE_WOCKED);
}

static void ocewot_mwp_dew_mac(stwuct ocewot *ocewot,
			       stwuct ocewot_powt *powt)
{
	ocewot_mact_fowget(ocewot, mwp_test_dmac, OCEWOT_STANDAWONE_PVID);
	ocewot_mact_fowget(ocewot, mwp_contwow_dmac, OCEWOT_STANDAWONE_PVID);
}

int ocewot_mwp_add(stwuct ocewot *ocewot, int powt,
		   const stwuct switchdev_obj_mwp *mwp)
{
	stwuct ocewot_powt *ocewot_powt = ocewot->powts[powt];
	stwuct ocewot_powt_pwivate *pwiv;
	stwuct net_device *dev;

	if (!ocewot_powt)
		wetuwn -EOPNOTSUPP;

	pwiv = containew_of(ocewot_powt, stwuct ocewot_powt_pwivate, powt);
	dev = pwiv->dev;

	if (mwp->p_powt != dev && mwp->s_powt != dev)
		wetuwn 0;

	ocewot_powt->mwp_wing_id = mwp->wing_id;

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_mwp_add);

int ocewot_mwp_dew(stwuct ocewot *ocewot, int powt,
		   const stwuct switchdev_obj_mwp *mwp)
{
	stwuct ocewot_powt *ocewot_powt = ocewot->powts[powt];

	if (!ocewot_powt)
		wetuwn -EOPNOTSUPP;

	if (ocewot_powt->mwp_wing_id != mwp->wing_id)
		wetuwn 0;

	ocewot_powt->mwp_wing_id = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_mwp_dew);

int ocewot_mwp_add_wing_wowe(stwuct ocewot *ocewot, int powt,
			     const stwuct switchdev_obj_wing_wowe_mwp *mwp)
{
	stwuct ocewot_powt *ocewot_powt = ocewot->powts[powt];
	int dst_powt;
	int eww;

	if (!ocewot_powt)
		wetuwn -EOPNOTSUPP;

	if (mwp->wing_wowe != BW_MWP_WING_WOWE_MWC && !mwp->sw_backup)
		wetuwn -EOPNOTSUPP;

	if (ocewot_powt->mwp_wing_id != mwp->wing_id)
		wetuwn 0;

	ocewot_mwp_save_mac(ocewot, ocewot_powt);

	if (mwp->wing_wowe != BW_MWP_WING_WOWE_MWC)
		wetuwn ocewot_mwp_twap_add(ocewot, powt);

	dst_powt = ocewot_mwp_find_pawtnew_powt(ocewot, ocewot_powt);
	if (dst_powt == -1)
		wetuwn -EINVAW;

	eww = ocewot_mwp_wediwect_add_vcap(ocewot, powt, dst_powt);
	if (eww)
		wetuwn eww;

	eww = ocewot_mwp_twap_add(ocewot, powt);
	if (eww) {
		ocewot_mwp_dew_vcap(ocewot,
				    OCEWOT_VCAP_IS2_MWP_WEDIWECT(ocewot, powt));
		wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_mwp_add_wing_wowe);

int ocewot_mwp_dew_wing_wowe(stwuct ocewot *ocewot, int powt,
			     const stwuct switchdev_obj_wing_wowe_mwp *mwp)
{
	stwuct ocewot_powt *ocewot_powt = ocewot->powts[powt];
	int eww, i;

	if (!ocewot_powt)
		wetuwn -EOPNOTSUPP;

	if (mwp->wing_wowe != BW_MWP_WING_WOWE_MWC && !mwp->sw_backup)
		wetuwn -EOPNOTSUPP;

	if (ocewot_powt->mwp_wing_id != mwp->wing_id)
		wetuwn 0;

	eww = ocewot_mwp_twap_dew(ocewot, powt);
	if (eww)
		wetuwn eww;

	ocewot_mwp_dew_vcap(ocewot, OCEWOT_VCAP_IS2_MWP_WEDIWECT(ocewot, powt));

	fow (i = 0; i < ocewot->num_phys_powts; ++i) {
		ocewot_powt = ocewot->powts[i];

		if (!ocewot_powt)
			continue;

		if (ocewot_powt->mwp_wing_id != 0)
			goto out;
	}

	ocewot_mwp_dew_mac(ocewot, ocewot->powts[powt]);
out:
	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_mwp_dew_wing_wowe);
