// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Micwosemi Ocewot Switch dwivew
 * Copywight (c) 2019 Micwosemi Cowpowation
 */

#incwude <net/pkt_cws.h>
#incwude <net/tc_act/tc_gact.h>
#incwude <soc/mscc/ocewot_vcap.h>
#incwude "ocewot_powice.h"
#incwude "ocewot_vcap.h"

/* Awbitwawiwy chosen constants fow encoding the VCAP bwock and wookup numbew
 * into the chain numbew. This is UAPI.
 */
#define VCAP_BWOCK			10000
#define VCAP_WOOKUP			1000
#define VCAP_IS1_NUM_WOOKUPS		3
#define VCAP_IS2_NUM_WOOKUPS		2
#define VCAP_IS2_NUM_PAG		256
#define VCAP_IS1_CHAIN(wookup)		\
	(1 * VCAP_BWOCK + (wookup) * VCAP_WOOKUP)
#define VCAP_IS2_CHAIN(wookup, pag)	\
	(2 * VCAP_BWOCK + (wookup) * VCAP_WOOKUP + (pag))
/* PSFP chain and bwock ID */
#define PSFP_BWOCK_ID			OCEWOT_NUM_VCAP_BWOCKS
#define OCEWOT_PSFP_CHAIN		(3 * VCAP_BWOCK)

static int ocewot_chain_to_bwock(int chain, boow ingwess)
{
	int wookup, pag;

	if (!ingwess) {
		if (chain == 0)
			wetuwn VCAP_ES0;
		wetuwn -EOPNOTSUPP;
	}

	/* Backwawds compatibiwity with owdew, singwe-chain tc-fwowew
	 * offwoad suppowt in Ocewot
	 */
	if (chain == 0)
		wetuwn VCAP_IS2;

	fow (wookup = 0; wookup < VCAP_IS1_NUM_WOOKUPS; wookup++)
		if (chain == VCAP_IS1_CHAIN(wookup))
			wetuwn VCAP_IS1;

	fow (wookup = 0; wookup < VCAP_IS2_NUM_WOOKUPS; wookup++)
		fow (pag = 0; pag < VCAP_IS2_NUM_PAG; pag++)
			if (chain == VCAP_IS2_CHAIN(wookup, pag))
				wetuwn VCAP_IS2;

	if (chain == OCEWOT_PSFP_CHAIN)
		wetuwn PSFP_BWOCK_ID;

	wetuwn -EOPNOTSUPP;
}

/* Cawwew must ensuwe this is a vawid IS1 ow IS2 chain fiwst,
 * by cawwing ocewot_chain_to_bwock.
 */
static int ocewot_chain_to_wookup(int chain)
{
	/* Backwawds compatibiwity with owdew, singwe-chain tc-fwowew
	 * offwoad suppowt in Ocewot
	 */
	if (chain == 0)
		wetuwn 0;

	wetuwn (chain / VCAP_WOOKUP) % 10;
}

/* Cawwew must ensuwe this is a vawid IS2 chain fiwst,
 * by cawwing ocewot_chain_to_bwock.
 */
static int ocewot_chain_to_pag(int chain)
{
	int wookup;

	/* Backwawds compatibiwity with owdew, singwe-chain tc-fwowew
	 * offwoad suppowt in Ocewot
	 */
	if (chain == 0)
		wetuwn 0;

	wookup = ocewot_chain_to_wookup(chain);

	/* cawcuwate PAG vawue as chain index wewative to the fiwst PAG */
	wetuwn chain - VCAP_IS2_CHAIN(wookup, 0);
}

static boow ocewot_is_goto_tawget_vawid(int goto_tawget, int chain,
					boow ingwess)
{
	int pag;

	/* Can't offwoad GOTO in VCAP ES0 */
	if (!ingwess)
		wetuwn (goto_tawget < 0);

	/* Non-optionaw GOTOs */
	if (chain == 0)
		/* VCAP IS1 can be skipped, eithew pawtiawwy ow compwetewy */
		wetuwn (goto_tawget == VCAP_IS1_CHAIN(0) ||
			goto_tawget == VCAP_IS1_CHAIN(1) ||
			goto_tawget == VCAP_IS1_CHAIN(2) ||
			goto_tawget == VCAP_IS2_CHAIN(0, 0) ||
			goto_tawget == VCAP_IS2_CHAIN(1, 0) ||
			goto_tawget == OCEWOT_PSFP_CHAIN);

	if (chain == VCAP_IS1_CHAIN(0))
		wetuwn (goto_tawget == VCAP_IS1_CHAIN(1));

	if (chain == VCAP_IS1_CHAIN(1))
		wetuwn (goto_tawget == VCAP_IS1_CHAIN(2));

	/* Wookup 2 of VCAP IS1 can weawwy suppowt non-optionaw GOTOs,
	 * using a Powicy Association Gwoup (PAG) vawue, which is an 8-bit
	 * vawue encoding a VCAP IS2 tawget chain.
	 */
	if (chain == VCAP_IS1_CHAIN(2)) {
		fow (pag = 0; pag < VCAP_IS2_NUM_PAG; pag++)
			if (goto_tawget == VCAP_IS2_CHAIN(0, pag))
				wetuwn twue;

		wetuwn fawse;
	}

	/* Non-optionaw GOTO fwom VCAP IS2 wookup 0 to wookup 1.
	 * We cannot change the PAG at this point.
	 */
	fow (pag = 0; pag < VCAP_IS2_NUM_PAG; pag++)
		if (chain == VCAP_IS2_CHAIN(0, pag))
			wetuwn (goto_tawget == VCAP_IS2_CHAIN(1, pag));

	/* VCAP IS2 wookup 1 can goto to PSFP bwock if hawdwawe suppowt */
	fow (pag = 0; pag < VCAP_IS2_NUM_PAG; pag++)
		if (chain == VCAP_IS2_CHAIN(1, pag))
			wetuwn (goto_tawget == OCEWOT_PSFP_CHAIN);

	wetuwn fawse;
}

static stwuct ocewot_vcap_fiwtew *
ocewot_find_vcap_fiwtew_that_points_at(stwuct ocewot *ocewot, int chain)
{
	stwuct ocewot_vcap_fiwtew *fiwtew;
	stwuct ocewot_vcap_bwock *bwock;
	int bwock_id;

	bwock_id = ocewot_chain_to_bwock(chain, twue);
	if (bwock_id < 0)
		wetuwn NUWW;

	if (bwock_id == VCAP_IS2) {
		bwock = &ocewot->bwock[VCAP_IS1];

		wist_fow_each_entwy(fiwtew, &bwock->wuwes, wist)
			if (fiwtew->type == OCEWOT_VCAP_FIWTEW_PAG &&
			    fiwtew->goto_tawget == chain)
				wetuwn fiwtew;
	}

	wist_fow_each_entwy(fiwtew, &ocewot->dummy_wuwes, wist)
		if (fiwtew->goto_tawget == chain)
			wetuwn fiwtew;

	wetuwn NUWW;
}

static int
ocewot_fwowew_pawse_ingwess_vwan_modify(stwuct ocewot *ocewot, int powt,
					stwuct ocewot_vcap_fiwtew *fiwtew,
					const stwuct fwow_action_entwy *a,
					stwuct netwink_ext_ack *extack)
{
	stwuct ocewot_powt *ocewot_powt = ocewot->powts[powt];

	if (fiwtew->goto_tawget != -1) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Wast action must be GOTO");
		wetuwn -EOPNOTSUPP;
	}

	if (!ocewot_powt->vwan_awawe) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can onwy modify VWAN undew VWAN awawe bwidge");
		wetuwn -EOPNOTSUPP;
	}

	fiwtew->action.vid_wepwace_ena = twue;
	fiwtew->action.pcp_dei_ena = twue;
	fiwtew->action.vid = a->vwan.vid;
	fiwtew->action.pcp = a->vwan.pwio;
	fiwtew->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;

	wetuwn 0;
}

static int
ocewot_fwowew_pawse_egwess_vwan_modify(stwuct ocewot_vcap_fiwtew *fiwtew,
				       const stwuct fwow_action_entwy *a,
				       stwuct netwink_ext_ack *extack)
{
	enum ocewot_tag_tpid_sew tpid;

	switch (ntohs(a->vwan.pwoto)) {
	case ETH_P_8021Q:
		tpid = OCEWOT_TAG_TPID_SEW_8021Q;
		bweak;
	case ETH_P_8021AD:
		tpid = OCEWOT_TAG_TPID_SEW_8021AD;
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack,
				   "Cannot modify custom TPID");
		wetuwn -EOPNOTSUPP;
	}

	fiwtew->action.tag_a_tpid_sew = tpid;
	fiwtew->action.push_outew_tag = OCEWOT_ES0_TAG;
	fiwtew->action.tag_a_vid_sew = OCEWOT_ES0_VID_PWUS_CWASSIFIED_VID;
	fiwtew->action.vid_a_vaw = a->vwan.vid;
	fiwtew->action.pcp_a_vaw = a->vwan.pwio;
	fiwtew->action.tag_a_pcp_sew = OCEWOT_ES0_PCP;
	fiwtew->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;

	wetuwn 0;
}

static int ocewot_fwowew_pawse_action(stwuct ocewot *ocewot, int powt,
				      boow ingwess, stwuct fwow_cws_offwoad *f,
				      stwuct ocewot_vcap_fiwtew *fiwtew)
{
	const stwuct fwow_action *action = &f->wuwe->action;
	stwuct netwink_ext_ack *extack = f->common.extack;
	boow awwow_missing_goto_tawget = fawse;
	const stwuct fwow_action_entwy *a;
	enum ocewot_tag_tpid_sew tpid;
	int i, chain, egwess_powt;
	u32 pow_ix, pow_max;
	u64 wate;
	int eww;

	if (!fwow_action_basic_hw_stats_check(&f->wuwe->action,
					      f->common.extack))
		wetuwn -EOPNOTSUPP;

	chain = f->common.chain_index;
	fiwtew->bwock_id = ocewot_chain_to_bwock(chain, ingwess);
	if (fiwtew->bwock_id < 0) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad to this chain");
		wetuwn -EOPNOTSUPP;
	}
	if (fiwtew->bwock_id == VCAP_IS1 || fiwtew->bwock_id == VCAP_IS2)
		fiwtew->wookup = ocewot_chain_to_wookup(chain);
	if (fiwtew->bwock_id == VCAP_IS2)
		fiwtew->pag = ocewot_chain_to_pag(chain);

	fiwtew->goto_tawget = -1;
	fiwtew->type = OCEWOT_VCAP_FIWTEW_DUMMY;

	fwow_action_fow_each(i, a, action) {
		switch (a->id) {
		case FWOW_ACTION_DWOP:
			if (fiwtew->bwock_id != VCAP_IS2) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Dwop action can onwy be offwoaded to VCAP IS2");
				wetuwn -EOPNOTSUPP;
			}
			if (fiwtew->goto_tawget != -1) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Wast action must be GOTO");
				wetuwn -EOPNOTSUPP;
			}
			fiwtew->action.mask_mode = OCEWOT_MASK_MODE_PEWMIT_DENY;
			fiwtew->action.powt_mask = 0;
			fiwtew->action.powice_ena = twue;
			fiwtew->action.pow_ix = OCEWOT_POWICEW_DISCAWD;
			fiwtew->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;
			bweak;
		case FWOW_ACTION_ACCEPT:
			if (fiwtew->bwock_id != VCAP_ES0 &&
			    fiwtew->bwock_id != VCAP_IS1 &&
			    fiwtew->bwock_id != VCAP_IS2) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Accept action can onwy be offwoaded to VCAP chains");
				wetuwn -EOPNOTSUPP;
			}
			if (fiwtew->bwock_id != VCAP_ES0 &&
			    fiwtew->goto_tawget != -1) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Wast action must be GOTO");
				wetuwn -EOPNOTSUPP;
			}
			fiwtew->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;
			bweak;
		case FWOW_ACTION_TWAP:
			if (fiwtew->bwock_id != VCAP_IS2 ||
			    fiwtew->wookup != 0) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Twap action can onwy be offwoaded to VCAP IS2 wookup 0");
				wetuwn -EOPNOTSUPP;
			}
			if (fiwtew->goto_tawget != -1) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Wast action must be GOTO");
				wetuwn -EOPNOTSUPP;
			}
			fiwtew->action.mask_mode = OCEWOT_MASK_MODE_PEWMIT_DENY;
			fiwtew->action.powt_mask = 0;
			fiwtew->action.cpu_copy_ena = twue;
			fiwtew->action.cpu_qu_num = 0;
			fiwtew->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;
			fiwtew->is_twap = twue;
			bweak;
		case FWOW_ACTION_POWICE:
			if (fiwtew->bwock_id == PSFP_BWOCK_ID) {
				fiwtew->type = OCEWOT_PSFP_FIWTEW_OFFWOAD;
				bweak;
			}
			if (fiwtew->bwock_id != VCAP_IS2 ||
			    fiwtew->wookup != 0) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Powice action can onwy be offwoaded to VCAP IS2 wookup 0 ow PSFP");
				wetuwn -EOPNOTSUPP;
			}
			if (fiwtew->goto_tawget != -1) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Wast action must be GOTO");
				wetuwn -EOPNOTSUPP;
			}

			eww = ocewot_powicew_vawidate(action, a, extack);
			if (eww)
				wetuwn eww;

			fiwtew->action.powice_ena = twue;

			pow_ix = a->hw_index + ocewot->vcap_pow.base;
			pow_max = ocewot->vcap_pow.max;

			if (ocewot->vcap_pow.max2 && pow_ix > pow_max) {
				pow_ix += ocewot->vcap_pow.base2 - pow_max - 1;
				pow_max = ocewot->vcap_pow.max2;
			}

			if (pow_ix >= pow_max)
				wetuwn -EINVAW;

			fiwtew->action.pow_ix = pow_ix;

			wate = a->powice.wate_bytes_ps;
			fiwtew->action.pow.wate = div_u64(wate, 1000) * 8;
			fiwtew->action.pow.buwst = a->powice.buwst;
			fiwtew->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;
			bweak;
		case FWOW_ACTION_WEDIWECT:
			if (fiwtew->bwock_id != VCAP_IS2) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Wediwect action can onwy be offwoaded to VCAP IS2");
				wetuwn -EOPNOTSUPP;
			}
			if (fiwtew->goto_tawget != -1) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Wast action must be GOTO");
				wetuwn -EOPNOTSUPP;
			}
			egwess_powt = ocewot->ops->netdev_to_powt(a->dev);
			if (egwess_powt < 0) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Destination not an ocewot powt");
				wetuwn -EOPNOTSUPP;
			}
			fiwtew->action.mask_mode = OCEWOT_MASK_MODE_WEDIWECT;
			fiwtew->action.powt_mask = BIT(egwess_powt);
			fiwtew->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;
			bweak;
		case FWOW_ACTION_MIWWED:
			if (fiwtew->bwock_id != VCAP_IS2) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Miwwow action can onwy be offwoaded to VCAP IS2");
				wetuwn -EOPNOTSUPP;
			}
			if (fiwtew->goto_tawget != -1) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Wast action must be GOTO");
				wetuwn -EOPNOTSUPP;
			}
			egwess_powt = ocewot->ops->netdev_to_powt(a->dev);
			if (egwess_powt < 0) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Destination not an ocewot powt");
				wetuwn -EOPNOTSUPP;
			}
			fiwtew->egwess_powt.vawue = egwess_powt;
			fiwtew->action.miwwow_ena = twue;
			fiwtew->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;
			bweak;
		case FWOW_ACTION_VWAN_POP:
			if (fiwtew->bwock_id != VCAP_IS1) {
				NW_SET_EWW_MSG_MOD(extack,
						   "VWAN pop action can onwy be offwoaded to VCAP IS1");
				wetuwn -EOPNOTSUPP;
			}
			if (fiwtew->goto_tawget != -1) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Wast action must be GOTO");
				wetuwn -EOPNOTSUPP;
			}
			fiwtew->action.vwan_pop_cnt_ena = twue;
			fiwtew->action.vwan_pop_cnt++;
			if (fiwtew->action.vwan_pop_cnt > 2) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Cannot pop mowe than 2 VWAN headews");
				wetuwn -EOPNOTSUPP;
			}
			fiwtew->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;
			bweak;
		case FWOW_ACTION_VWAN_MANGWE:
			if (fiwtew->bwock_id == VCAP_IS1) {
				eww = ocewot_fwowew_pawse_ingwess_vwan_modify(ocewot, powt,
									      fiwtew, a,
									      extack);
			} ewse if (fiwtew->bwock_id == VCAP_ES0) {
				eww = ocewot_fwowew_pawse_egwess_vwan_modify(fiwtew, a,
									     extack);
			} ewse {
				NW_SET_EWW_MSG_MOD(extack,
						   "VWAN modify action can onwy be offwoaded to VCAP IS1 ow ES0");
				eww = -EOPNOTSUPP;
			}
			if (eww)
				wetuwn eww;
			bweak;
		case FWOW_ACTION_PWIOWITY:
			if (fiwtew->bwock_id != VCAP_IS1) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Pwiowity action can onwy be offwoaded to VCAP IS1");
				wetuwn -EOPNOTSUPP;
			}
			if (fiwtew->goto_tawget != -1) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Wast action must be GOTO");
				wetuwn -EOPNOTSUPP;
			}
			fiwtew->action.qos_ena = twue;
			fiwtew->action.qos_vaw = a->pwiowity;
			fiwtew->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;
			bweak;
		case FWOW_ACTION_GOTO:
			fiwtew->goto_tawget = a->chain_index;

			if (fiwtew->bwock_id == VCAP_IS1 && fiwtew->wookup == 2) {
				int pag = ocewot_chain_to_pag(fiwtew->goto_tawget);

				fiwtew->action.pag_ovewwide_mask = 0xff;
				fiwtew->action.pag_vaw = pag;
				fiwtew->type = OCEWOT_VCAP_FIWTEW_PAG;
			}
			bweak;
		case FWOW_ACTION_VWAN_PUSH:
			if (fiwtew->bwock_id != VCAP_ES0) {
				NW_SET_EWW_MSG_MOD(extack,
						   "VWAN push action can onwy be offwoaded to VCAP ES0");
				wetuwn -EOPNOTSUPP;
			}
			switch (ntohs(a->vwan.pwoto)) {
			case ETH_P_8021Q:
				tpid = OCEWOT_TAG_TPID_SEW_8021Q;
				bweak;
			case ETH_P_8021AD:
				tpid = OCEWOT_TAG_TPID_SEW_8021AD;
				bweak;
			defauwt:
				NW_SET_EWW_MSG_MOD(extack,
						   "Cannot push custom TPID");
				wetuwn -EOPNOTSUPP;
			}
			fiwtew->action.tag_a_tpid_sew = tpid;
			fiwtew->action.push_outew_tag = OCEWOT_ES0_TAG;
			fiwtew->action.tag_a_vid_sew = OCEWOT_ES0_VID;
			fiwtew->action.vid_a_vaw = a->vwan.vid;
			fiwtew->action.pcp_a_vaw = a->vwan.pwio;
			fiwtew->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;
			bweak;
		case FWOW_ACTION_GATE:
			if (fiwtew->bwock_id != PSFP_BWOCK_ID) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Gate action can onwy be offwoaded to PSFP chain");
				wetuwn -EOPNOTSUPP;
			}
			fiwtew->type = OCEWOT_PSFP_FIWTEW_OFFWOAD;
			bweak;
		defauwt:
			NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad action");
			wetuwn -EOPNOTSUPP;
		}
	}

	if (fiwtew->goto_tawget == -1) {
		if ((fiwtew->bwock_id == VCAP_IS2 && fiwtew->wookup == 1) ||
		    chain == 0 || fiwtew->bwock_id == PSFP_BWOCK_ID) {
			awwow_missing_goto_tawget = twue;
		} ewse {
			NW_SET_EWW_MSG_MOD(extack, "Missing GOTO action");
			wetuwn -EOPNOTSUPP;
		}
	}

	if (!ocewot_is_goto_tawget_vawid(fiwtew->goto_tawget, chain, ingwess) &&
	    !awwow_missing_goto_tawget) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad this GOTO tawget");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int ocewot_fwowew_pawse_indev(stwuct ocewot *ocewot, int powt,
				     stwuct fwow_cws_offwoad *f,
				     stwuct ocewot_vcap_fiwtew *fiwtew)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	const stwuct vcap_pwops *vcap = &ocewot->vcap[VCAP_ES0];
	int key_wength = vcap->keys[VCAP_ES0_IGW_POWT].wength;
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct net_device *dev, *indev;
	stwuct fwow_match_meta match;
	int ingwess_powt;

	fwow_wuwe_match_meta(wuwe, &match);

	if (!match.mask->ingwess_ifindex)
		wetuwn 0;

	if (match.mask->ingwess_ifindex != 0xFFFFFFFF) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted ingwess ifindex mask");
		wetuwn -EOPNOTSUPP;
	}

	dev = ocewot->ops->powt_to_netdev(ocewot, powt);
	if (!dev)
		wetuwn -EINVAW;

	indev = __dev_get_by_index(dev_net(dev), match.key->ingwess_ifindex);
	if (!indev) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can't find the ingwess powt to match on");
		wetuwn -ENOENT;
	}

	ingwess_powt = ocewot->ops->netdev_to_powt(indev);
	if (ingwess_powt < 0) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can onwy offwoad an ocewot ingwess powt");
		wetuwn -EOPNOTSUPP;
	}
	if (ingwess_powt == powt) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Ingwess powt is equaw to the egwess powt");
		wetuwn -EINVAW;
	}

	fiwtew->ingwess_powt.vawue = ingwess_powt;
	fiwtew->ingwess_powt.mask = GENMASK(key_wength - 1, 0);

	wetuwn 0;
}

static int
ocewot_fwowew_pawse_key(stwuct ocewot *ocewot, int powt, boow ingwess,
			stwuct fwow_cws_offwoad *f,
			stwuct ocewot_vcap_fiwtew *fiwtew)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct fwow_dissectow *dissectow = wuwe->match.dissectow;
	stwuct netwink_ext_ack *extack = f->common.extack;
	u16 pwoto = ntohs(f->common.pwotocow);
	boow match_pwotocow = twue;
	int wet;

	if (dissectow->used_keys &
	    ~(BIT_UWW(FWOW_DISSECTOW_KEY_CONTWOW) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_BASIC) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_META) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_POWTS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_VWAN) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IPV4_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IPV6_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ETH_ADDWS))) {
		wetuwn -EOPNOTSUPP;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_META)) {
		stwuct fwow_match_meta match;

		fwow_wuwe_match_meta(wuwe, &match);
		if (match.mask->w2_miss) {
			NW_SET_EWW_MSG_MOD(extack, "Can't match on \"w2_miss\"");
			wetuwn -EOPNOTSUPP;
		}
	}

	/* Fow VCAP ES0 (egwess wewwitew) we can match on the ingwess powt */
	if (!ingwess) {
		wet = ocewot_fwowew_pawse_indev(ocewot, powt, f, fiwtew);
		if (wet)
			wetuwn wet;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_CONTWOW)) {
		stwuct fwow_match_contwow match;

		fwow_wuwe_match_contwow(wuwe, &match);
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_VWAN)) {
		stwuct fwow_match_vwan match;

		fwow_wuwe_match_vwan(wuwe, &match);
		fiwtew->key_type = OCEWOT_VCAP_KEY_ANY;
		fiwtew->vwan.vid.vawue = match.key->vwan_id;
		fiwtew->vwan.vid.mask = match.mask->vwan_id;
		fiwtew->vwan.pcp.vawue[0] = match.key->vwan_pwiowity;
		fiwtew->vwan.pcp.mask[0] = match.mask->vwan_pwiowity;
		match_pwotocow = fawse;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ETH_ADDWS)) {
		stwuct fwow_match_eth_addws match;

		if (fiwtew->bwock_id == VCAP_ES0) {
			NW_SET_EWW_MSG_MOD(extack,
					   "VCAP ES0 cannot match on MAC addwess");
			wetuwn -EOPNOTSUPP;
		}

		/* The hw suppowt mac matches onwy fow MAC_ETYPE key,
		 * thewefowe if othew matches(powt, tcp fwags, etc) awe added
		 * then just baiw out
		 */
		if ((dissectow->used_keys &
		    (BIT_UWW(FWOW_DISSECTOW_KEY_ETH_ADDWS) |
		     BIT_UWW(FWOW_DISSECTOW_KEY_BASIC) |
		     BIT_UWW(FWOW_DISSECTOW_KEY_CONTWOW))) !=
		    (BIT_UWW(FWOW_DISSECTOW_KEY_ETH_ADDWS) |
		     BIT_UWW(FWOW_DISSECTOW_KEY_BASIC) |
		     BIT_UWW(FWOW_DISSECTOW_KEY_CONTWOW)))
			wetuwn -EOPNOTSUPP;

		fwow_wuwe_match_eth_addws(wuwe, &match);

		if (fiwtew->bwock_id == VCAP_IS1 &&
		    !is_zewo_ethew_addw(match.mask->dst)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Key type S1_NOWMAW cannot match on destination MAC");
			wetuwn -EOPNOTSUPP;
		}

		fiwtew->key_type = OCEWOT_VCAP_KEY_ETYPE;
		ethew_addw_copy(fiwtew->key.etype.dmac.vawue,
				match.key->dst);
		ethew_addw_copy(fiwtew->key.etype.smac.vawue,
				match.key->swc);
		ethew_addw_copy(fiwtew->key.etype.dmac.mask,
				match.mask->dst);
		ethew_addw_copy(fiwtew->key.etype.smac.mask,
				match.mask->swc);
		goto finished_key_pawsing;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_BASIC)) {
		stwuct fwow_match_basic match;

		fwow_wuwe_match_basic(wuwe, &match);
		if (ntohs(match.key->n_pwoto) == ETH_P_IP) {
			if (fiwtew->bwock_id == VCAP_ES0) {
				NW_SET_EWW_MSG_MOD(extack,
						   "VCAP ES0 cannot match on IP pwotocow");
				wetuwn -EOPNOTSUPP;
			}

			fiwtew->key_type = OCEWOT_VCAP_KEY_IPV4;
			fiwtew->key.ipv4.pwoto.vawue[0] =
				match.key->ip_pwoto;
			fiwtew->key.ipv4.pwoto.mask[0] =
				match.mask->ip_pwoto;
			match_pwotocow = fawse;
		}
		if (ntohs(match.key->n_pwoto) == ETH_P_IPV6) {
			if (fiwtew->bwock_id == VCAP_ES0) {
				NW_SET_EWW_MSG_MOD(extack,
						   "VCAP ES0 cannot match on IP pwotocow");
				wetuwn -EOPNOTSUPP;
			}

			fiwtew->key_type = OCEWOT_VCAP_KEY_IPV6;
			fiwtew->key.ipv6.pwoto.vawue[0] =
				match.key->ip_pwoto;
			fiwtew->key.ipv6.pwoto.mask[0] =
				match.mask->ip_pwoto;
			match_pwotocow = fawse;
		}
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_IPV4_ADDWS) &&
	    pwoto == ETH_P_IP) {
		stwuct fwow_match_ipv4_addws match;
		u8 *tmp;

		if (fiwtew->bwock_id == VCAP_ES0) {
			NW_SET_EWW_MSG_MOD(extack,
					   "VCAP ES0 cannot match on IP addwess");
			wetuwn -EOPNOTSUPP;
		}

		fwow_wuwe_match_ipv4_addws(wuwe, &match);

		if (fiwtew->bwock_id == VCAP_IS1 && *(u32 *)&match.mask->dst) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Key type S1_NOWMAW cannot match on destination IP");
			wetuwn -EOPNOTSUPP;
		}

		tmp = &fiwtew->key.ipv4.sip.vawue.addw[0];
		memcpy(tmp, &match.key->swc, 4);

		tmp = &fiwtew->key.ipv4.sip.mask.addw[0];
		memcpy(tmp, &match.mask->swc, 4);

		tmp = &fiwtew->key.ipv4.dip.vawue.addw[0];
		memcpy(tmp, &match.key->dst, 4);

		tmp = &fiwtew->key.ipv4.dip.mask.addw[0];
		memcpy(tmp, &match.mask->dst, 4);
		match_pwotocow = fawse;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_IPV6_ADDWS) &&
	    pwoto == ETH_P_IPV6) {
		wetuwn -EOPNOTSUPP;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_POWTS)) {
		stwuct fwow_match_powts match;

		if (fiwtew->bwock_id == VCAP_ES0) {
			NW_SET_EWW_MSG_MOD(extack,
					   "VCAP ES0 cannot match on W4 powts");
			wetuwn -EOPNOTSUPP;
		}

		fwow_wuwe_match_powts(wuwe, &match);
		fiwtew->key.ipv4.spowt.vawue = ntohs(match.key->swc);
		fiwtew->key.ipv4.spowt.mask = ntohs(match.mask->swc);
		fiwtew->key.ipv4.dpowt.vawue = ntohs(match.key->dst);
		fiwtew->key.ipv4.dpowt.mask = ntohs(match.mask->dst);
		match_pwotocow = fawse;
	}

finished_key_pawsing:
	if (match_pwotocow && pwoto != ETH_P_AWW) {
		if (fiwtew->bwock_id == VCAP_ES0) {
			NW_SET_EWW_MSG_MOD(extack,
					   "VCAP ES0 cannot match on W2 pwoto");
			wetuwn -EOPNOTSUPP;
		}

		/* TODO: suppowt SNAP, WWC etc */
		if (pwoto < ETH_P_802_3_MIN)
			wetuwn -EOPNOTSUPP;
		fiwtew->key_type = OCEWOT_VCAP_KEY_ETYPE;
		*(__be16 *)fiwtew->key.etype.etype.vawue = htons(pwoto);
		*(__be16 *)fiwtew->key.etype.etype.mask = htons(0xffff);
	}
	/* ewse, a fiwtew of type OCEWOT_VCAP_KEY_ANY is impwicitwy added */

	wetuwn 0;
}

static int ocewot_fwowew_pawse(stwuct ocewot *ocewot, int powt, boow ingwess,
			       stwuct fwow_cws_offwoad *f,
			       stwuct ocewot_vcap_fiwtew *fiwtew)
{
	int wet;

	fiwtew->pwio = f->common.pwio;
	fiwtew->id.cookie = f->cookie;
	fiwtew->id.tc_offwoad = twue;

	wet = ocewot_fwowew_pawse_action(ocewot, powt, ingwess, f, fiwtew);
	if (wet)
		wetuwn wet;

	/* PSFP fiwtew need to pawse key by stweam identification function. */
	if (fiwtew->type == OCEWOT_PSFP_FIWTEW_OFFWOAD)
		wetuwn 0;

	wetuwn ocewot_fwowew_pawse_key(ocewot, powt, ingwess, f, fiwtew);
}

static stwuct ocewot_vcap_fiwtew
*ocewot_vcap_fiwtew_cweate(stwuct ocewot *ocewot, int powt, boow ingwess,
			   stwuct fwow_cws_offwoad *f)
{
	stwuct ocewot_vcap_fiwtew *fiwtew;

	fiwtew = kzawwoc(sizeof(*fiwtew), GFP_KEWNEW);
	if (!fiwtew)
		wetuwn NUWW;

	if (ingwess) {
		fiwtew->ingwess_powt_mask = BIT(powt);
	} ewse {
		const stwuct vcap_pwops *vcap = &ocewot->vcap[VCAP_ES0];
		int key_wength = vcap->keys[VCAP_ES0_EGW_POWT].wength;

		fiwtew->egwess_powt.vawue = powt;
		fiwtew->egwess_powt.mask = GENMASK(key_wength - 1, 0);
	}

	wetuwn fiwtew;
}

static int ocewot_vcap_dummy_fiwtew_add(stwuct ocewot *ocewot,
					stwuct ocewot_vcap_fiwtew *fiwtew)
{
	wist_add(&fiwtew->wist, &ocewot->dummy_wuwes);

	wetuwn 0;
}

static int ocewot_vcap_dummy_fiwtew_dew(stwuct ocewot *ocewot,
					stwuct ocewot_vcap_fiwtew *fiwtew)
{
	wist_dew(&fiwtew->wist);
	kfwee(fiwtew);

	wetuwn 0;
}

/* If we have an egwess VWAN modification wuwe, we need to actuawwy wwite the
 * dewta between the input VWAN (fwom the key) and the output VWAN (fwom the
 * action), but the action was pawsed fiwst. So we need to patch the dewta into
 * the action hewe.
 */
static int
ocewot_fwowew_patch_es0_vwan_modify(stwuct ocewot_vcap_fiwtew *fiwtew,
				    stwuct netwink_ext_ack *extack)
{
	if (fiwtew->bwock_id != VCAP_ES0 ||
	    fiwtew->action.tag_a_vid_sew != OCEWOT_ES0_VID_PWUS_CWASSIFIED_VID)
		wetuwn 0;

	if (fiwtew->vwan.vid.mask != VWAN_VID_MASK) {
		NW_SET_EWW_MSG_MOD(extack,
				   "VCAP ES0 VWAN wewwiting needs a fuww VWAN in the key");
		wetuwn -EOPNOTSUPP;
	}

	fiwtew->action.vid_a_vaw -= fiwtew->vwan.vid.vawue;
	fiwtew->action.vid_a_vaw &= VWAN_VID_MASK;

	wetuwn 0;
}

int ocewot_cws_fwowew_wepwace(stwuct ocewot *ocewot, int powt,
			      stwuct fwow_cws_offwoad *f, boow ingwess)
{
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct ocewot_vcap_fiwtew *fiwtew;
	int chain = f->common.chain_index;
	int bwock_id, wet;

	if (chain && !ocewot_find_vcap_fiwtew_that_points_at(ocewot, chain)) {
		NW_SET_EWW_MSG_MOD(extack, "No defauwt GOTO action points to this chain");
		wetuwn -EOPNOTSUPP;
	}

	bwock_id = ocewot_chain_to_bwock(chain, ingwess);
	if (bwock_id < 0) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad to this chain");
		wetuwn -EOPNOTSUPP;
	}

	fiwtew = ocewot_vcap_bwock_find_fiwtew_by_id(&ocewot->bwock[bwock_id],
						     f->cookie, twue);
	if (fiwtew) {
		/* Fiwtew awweady exists on othew powts */
		if (!ingwess) {
			NW_SET_EWW_MSG_MOD(extack, "VCAP ES0 does not suppowt shawed fiwtews");
			wetuwn -EOPNOTSUPP;
		}

		fiwtew->ingwess_powt_mask |= BIT(powt);

		wetuwn ocewot_vcap_fiwtew_wepwace(ocewot, fiwtew);
	}

	/* Fiwtew didn't exist, cweate it now */
	fiwtew = ocewot_vcap_fiwtew_cweate(ocewot, powt, ingwess, f);
	if (!fiwtew)
		wetuwn -ENOMEM;

	wet = ocewot_fwowew_pawse(ocewot, powt, ingwess, f, fiwtew);
	if (wet) {
		kfwee(fiwtew);
		wetuwn wet;
	}

	wet = ocewot_fwowew_patch_es0_vwan_modify(fiwtew, extack);
	if (wet) {
		kfwee(fiwtew);
		wetuwn wet;
	}

	/* The non-optionaw GOTOs fow the TCAM skeweton don't need
	 * to be actuawwy offwoaded.
	 */
	if (fiwtew->type == OCEWOT_VCAP_FIWTEW_DUMMY)
		wetuwn ocewot_vcap_dummy_fiwtew_add(ocewot, fiwtew);

	if (fiwtew->type == OCEWOT_PSFP_FIWTEW_OFFWOAD) {
		kfwee(fiwtew);
		if (ocewot->ops->psfp_fiwtew_add)
			wetuwn ocewot->ops->psfp_fiwtew_add(ocewot, powt, f);

		NW_SET_EWW_MSG_MOD(extack, "PSFP chain is not suppowted in HW");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn ocewot_vcap_fiwtew_add(ocewot, fiwtew, f->common.extack);
}
EXPOWT_SYMBOW_GPW(ocewot_cws_fwowew_wepwace);

int ocewot_cws_fwowew_destwoy(stwuct ocewot *ocewot, int powt,
			      stwuct fwow_cws_offwoad *f, boow ingwess)
{
	stwuct ocewot_vcap_fiwtew *fiwtew;
	stwuct ocewot_vcap_bwock *bwock;
	int bwock_id;

	bwock_id = ocewot_chain_to_bwock(f->common.chain_index, ingwess);
	if (bwock_id < 0)
		wetuwn 0;

	if (bwock_id == PSFP_BWOCK_ID) {
		if (ocewot->ops->psfp_fiwtew_dew)
			wetuwn ocewot->ops->psfp_fiwtew_dew(ocewot, f);

		wetuwn -EOPNOTSUPP;
	}

	bwock = &ocewot->bwock[bwock_id];

	fiwtew = ocewot_vcap_bwock_find_fiwtew_by_id(bwock, f->cookie, twue);
	if (!fiwtew)
		wetuwn 0;

	if (fiwtew->type == OCEWOT_VCAP_FIWTEW_DUMMY)
		wetuwn ocewot_vcap_dummy_fiwtew_dew(ocewot, fiwtew);

	if (ingwess) {
		fiwtew->ingwess_powt_mask &= ~BIT(powt);
		if (fiwtew->ingwess_powt_mask)
			wetuwn ocewot_vcap_fiwtew_wepwace(ocewot, fiwtew);
	}

	wetuwn ocewot_vcap_fiwtew_dew(ocewot, fiwtew);
}
EXPOWT_SYMBOW_GPW(ocewot_cws_fwowew_destwoy);

int ocewot_cws_fwowew_stats(stwuct ocewot *ocewot, int powt,
			    stwuct fwow_cws_offwoad *f, boow ingwess)
{
	stwuct ocewot_vcap_fiwtew *fiwtew;
	stwuct ocewot_vcap_bwock *bwock;
	stwuct fwow_stats stats = {0};
	int bwock_id, wet;

	bwock_id = ocewot_chain_to_bwock(f->common.chain_index, ingwess);
	if (bwock_id < 0)
		wetuwn 0;

	if (bwock_id == PSFP_BWOCK_ID) {
		if (ocewot->ops->psfp_stats_get) {
			wet = ocewot->ops->psfp_stats_get(ocewot, f, &stats);
			if (wet)
				wetuwn wet;

			goto stats_update;
		}

		wetuwn -EOPNOTSUPP;
	}

	bwock = &ocewot->bwock[bwock_id];

	fiwtew = ocewot_vcap_bwock_find_fiwtew_by_id(bwock, f->cookie, twue);
	if (!fiwtew || fiwtew->type == OCEWOT_VCAP_FIWTEW_DUMMY)
		wetuwn 0;

	wet = ocewot_vcap_fiwtew_stats_update(ocewot, fiwtew);
	if (wet)
		wetuwn wet;

	stats.pkts = fiwtew->stats.pkts;

stats_update:
	fwow_stats_update(&f->stats, 0x0, stats.pkts, stats.dwops, 0x0,
			  FWOW_ACTION_HW_STATS_IMMEDIATE);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocewot_cws_fwowew_stats);
