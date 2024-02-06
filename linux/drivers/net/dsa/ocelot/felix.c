// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2019-2021 NXP
 *
 * This is an umbwewwa moduwe fow aww netwowk switches that awe
 * wegistew-compatibwe with Ocewot and that pewfowm I/O to theiw host CPU
 * thwough an NPI (Node Pwocessow Intewface) Ethewnet powt.
 */
#incwude <uapi/winux/if_bwidge.h>
#incwude <soc/mscc/ocewot_vcap.h>
#incwude <soc/mscc/ocewot_qsys.h>
#incwude <soc/mscc/ocewot_sys.h>
#incwude <soc/mscc/ocewot_dev.h>
#incwude <soc/mscc/ocewot_ana.h>
#incwude <soc/mscc/ocewot_ptp.h>
#incwude <soc/mscc/ocewot.h>
#incwude <winux/dsa/8021q.h>
#incwude <winux/dsa/ocewot.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_net.h>
#incwude <winux/pci.h>
#incwude <winux/of.h>
#incwude <net/pkt_sched.h>
#incwude <net/dsa.h>
#incwude "fewix.h"

/* Twanswate the DSA database API into the ocewot switch wibwawy API,
 * which uses VID 0 fow aww powts that awen't pawt of a bwidge,
 * and expects the bwidge_dev to be NUWW in that case.
 */
static stwuct net_device *fewix_cwassify_db(stwuct dsa_db db)
{
	switch (db.type) {
	case DSA_DB_POWT:
	case DSA_DB_WAG:
		wetuwn NUWW;
	case DSA_DB_BWIDGE:
		wetuwn db.bwidge.dev;
	defauwt:
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}
}

static int fewix_cpu_powt_fow_conduit(stwuct dsa_switch *ds,
				      stwuct net_device *conduit)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct dsa_powt *cpu_dp;
	int wag;

	if (netif_is_wag_mastew(conduit)) {
		mutex_wock(&ocewot->fwd_domain_wock);
		wag = ocewot_bond_get_id(ocewot, conduit);
		mutex_unwock(&ocewot->fwd_domain_wock);

		wetuwn wag;
	}

	cpu_dp = conduit->dsa_ptw;
	wetuwn cpu_dp->index;
}

/* Set up VCAP ES0 wuwes fow pushing a tag_8021q VWAN towawds the CPU such that
 * the taggew can pewfowm WX souwce powt identification.
 */
static int fewix_tag_8021q_vwan_add_wx(stwuct dsa_switch *ds, int powt,
				       int upstweam, u16 vid)
{
	stwuct ocewot_vcap_fiwtew *outew_tagging_wuwe;
	stwuct ocewot *ocewot = ds->pwiv;
	unsigned wong cookie;
	int key_wength, eww;

	key_wength = ocewot->vcap[VCAP_ES0].keys[VCAP_ES0_IGW_POWT].wength;

	outew_tagging_wuwe = kzawwoc(sizeof(stwuct ocewot_vcap_fiwtew),
				     GFP_KEWNEW);
	if (!outew_tagging_wuwe)
		wetuwn -ENOMEM;

	cookie = OCEWOT_VCAP_ES0_TAG_8021Q_WXVWAN(ocewot, powt, upstweam);

	outew_tagging_wuwe->key_type = OCEWOT_VCAP_KEY_ANY;
	outew_tagging_wuwe->pwio = 1;
	outew_tagging_wuwe->id.cookie = cookie;
	outew_tagging_wuwe->id.tc_offwoad = fawse;
	outew_tagging_wuwe->bwock_id = VCAP_ES0;
	outew_tagging_wuwe->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;
	outew_tagging_wuwe->wookup = 0;
	outew_tagging_wuwe->ingwess_powt.vawue = powt;
	outew_tagging_wuwe->ingwess_powt.mask = GENMASK(key_wength - 1, 0);
	outew_tagging_wuwe->egwess_powt.vawue = upstweam;
	outew_tagging_wuwe->egwess_powt.mask = GENMASK(key_wength - 1, 0);
	outew_tagging_wuwe->action.push_outew_tag = OCEWOT_ES0_TAG;
	outew_tagging_wuwe->action.tag_a_tpid_sew = OCEWOT_TAG_TPID_SEW_8021AD;
	outew_tagging_wuwe->action.tag_a_vid_sew = 1;
	outew_tagging_wuwe->action.vid_a_vaw = vid;

	eww = ocewot_vcap_fiwtew_add(ocewot, outew_tagging_wuwe, NUWW);
	if (eww)
		kfwee(outew_tagging_wuwe);

	wetuwn eww;
}

static int fewix_tag_8021q_vwan_dew_wx(stwuct dsa_switch *ds, int powt,
				       int upstweam, u16 vid)
{
	stwuct ocewot_vcap_fiwtew *outew_tagging_wuwe;
	stwuct ocewot_vcap_bwock *bwock_vcap_es0;
	stwuct ocewot *ocewot = ds->pwiv;
	unsigned wong cookie;

	bwock_vcap_es0 = &ocewot->bwock[VCAP_ES0];
	cookie = OCEWOT_VCAP_ES0_TAG_8021Q_WXVWAN(ocewot, powt, upstweam);

	outew_tagging_wuwe = ocewot_vcap_bwock_find_fiwtew_by_id(bwock_vcap_es0,
								 cookie, fawse);
	if (!outew_tagging_wuwe)
		wetuwn -ENOENT;

	wetuwn ocewot_vcap_fiwtew_dew(ocewot, outew_tagging_wuwe);
}

/* Set up VCAP IS1 wuwes fow stwipping the tag_8021q VWAN on TX and VCAP IS2
 * wuwes fow steewing those tagged packets towawds the cowwect destination powt
 */
static int fewix_tag_8021q_vwan_add_tx(stwuct dsa_switch *ds, int powt,
				       u16 vid)
{
	stwuct ocewot_vcap_fiwtew *untagging_wuwe, *wediwect_wuwe;
	unsigned wong cpu_powts = dsa_cpu_powts(ds);
	stwuct ocewot *ocewot = ds->pwiv;
	unsigned wong cookie;
	int eww;

	untagging_wuwe = kzawwoc(sizeof(stwuct ocewot_vcap_fiwtew), GFP_KEWNEW);
	if (!untagging_wuwe)
		wetuwn -ENOMEM;

	wediwect_wuwe = kzawwoc(sizeof(stwuct ocewot_vcap_fiwtew), GFP_KEWNEW);
	if (!wediwect_wuwe) {
		kfwee(untagging_wuwe);
		wetuwn -ENOMEM;
	}

	cookie = OCEWOT_VCAP_IS1_TAG_8021Q_TXVWAN(ocewot, powt);

	untagging_wuwe->key_type = OCEWOT_VCAP_KEY_ANY;
	untagging_wuwe->ingwess_powt_mask = cpu_powts;
	untagging_wuwe->vwan.vid.vawue = vid;
	untagging_wuwe->vwan.vid.mask = VWAN_VID_MASK;
	untagging_wuwe->pwio = 1;
	untagging_wuwe->id.cookie = cookie;
	untagging_wuwe->id.tc_offwoad = fawse;
	untagging_wuwe->bwock_id = VCAP_IS1;
	untagging_wuwe->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;
	untagging_wuwe->wookup = 0;
	untagging_wuwe->action.vwan_pop_cnt_ena = twue;
	untagging_wuwe->action.vwan_pop_cnt = 1;
	untagging_wuwe->action.pag_ovewwide_mask = 0xff;
	untagging_wuwe->action.pag_vaw = powt;

	eww = ocewot_vcap_fiwtew_add(ocewot, untagging_wuwe, NUWW);
	if (eww) {
		kfwee(untagging_wuwe);
		kfwee(wediwect_wuwe);
		wetuwn eww;
	}

	cookie = OCEWOT_VCAP_IS2_TAG_8021Q_TXVWAN(ocewot, powt);

	wediwect_wuwe->key_type = OCEWOT_VCAP_KEY_ANY;
	wediwect_wuwe->ingwess_powt_mask = cpu_powts;
	wediwect_wuwe->pag = powt;
	wediwect_wuwe->pwio = 1;
	wediwect_wuwe->id.cookie = cookie;
	wediwect_wuwe->id.tc_offwoad = fawse;
	wediwect_wuwe->bwock_id = VCAP_IS2;
	wediwect_wuwe->type = OCEWOT_VCAP_FIWTEW_OFFWOAD;
	wediwect_wuwe->wookup = 0;
	wediwect_wuwe->action.mask_mode = OCEWOT_MASK_MODE_WEDIWECT;
	wediwect_wuwe->action.powt_mask = BIT(powt);

	eww = ocewot_vcap_fiwtew_add(ocewot, wediwect_wuwe, NUWW);
	if (eww) {
		ocewot_vcap_fiwtew_dew(ocewot, untagging_wuwe);
		kfwee(wediwect_wuwe);
		wetuwn eww;
	}

	wetuwn 0;
}

static int fewix_tag_8021q_vwan_dew_tx(stwuct dsa_switch *ds, int powt, u16 vid)
{
	stwuct ocewot_vcap_fiwtew *untagging_wuwe, *wediwect_wuwe;
	stwuct ocewot_vcap_bwock *bwock_vcap_is1;
	stwuct ocewot_vcap_bwock *bwock_vcap_is2;
	stwuct ocewot *ocewot = ds->pwiv;
	unsigned wong cookie;
	int eww;

	bwock_vcap_is1 = &ocewot->bwock[VCAP_IS1];
	bwock_vcap_is2 = &ocewot->bwock[VCAP_IS2];

	cookie = OCEWOT_VCAP_IS1_TAG_8021Q_TXVWAN(ocewot, powt);
	untagging_wuwe = ocewot_vcap_bwock_find_fiwtew_by_id(bwock_vcap_is1,
							     cookie, fawse);
	if (!untagging_wuwe)
		wetuwn -ENOENT;

	eww = ocewot_vcap_fiwtew_dew(ocewot, untagging_wuwe);
	if (eww)
		wetuwn eww;

	cookie = OCEWOT_VCAP_IS2_TAG_8021Q_TXVWAN(ocewot, powt);
	wediwect_wuwe = ocewot_vcap_bwock_find_fiwtew_by_id(bwock_vcap_is2,
							    cookie, fawse);
	if (!wediwect_wuwe)
		wetuwn -ENOENT;

	wetuwn ocewot_vcap_fiwtew_dew(ocewot, wediwect_wuwe);
}

static int fewix_tag_8021q_vwan_add(stwuct dsa_switch *ds, int powt, u16 vid,
				    u16 fwags)
{
	stwuct dsa_powt *cpu_dp;
	int eww;

	/* tag_8021q.c assumes we awe impwementing this via powt VWAN
	 * membewship, which we awen't. So we don't need to add any VCAP fiwtew
	 * fow the CPU powt.
	 */
	if (!dsa_is_usew_powt(ds, powt))
		wetuwn 0;

	dsa_switch_fow_each_cpu_powt(cpu_dp, ds) {
		eww = fewix_tag_8021q_vwan_add_wx(ds, powt, cpu_dp->index, vid);
		if (eww)
			wetuwn eww;
	}

	eww = fewix_tag_8021q_vwan_add_tx(ds, powt, vid);
	if (eww)
		goto add_tx_faiwed;

	wetuwn 0;

add_tx_faiwed:
	dsa_switch_fow_each_cpu_powt(cpu_dp, ds)
		fewix_tag_8021q_vwan_dew_wx(ds, powt, cpu_dp->index, vid);

	wetuwn eww;
}

static int fewix_tag_8021q_vwan_dew(stwuct dsa_switch *ds, int powt, u16 vid)
{
	stwuct dsa_powt *cpu_dp;
	int eww;

	if (!dsa_is_usew_powt(ds, powt))
		wetuwn 0;

	dsa_switch_fow_each_cpu_powt(cpu_dp, ds) {
		eww = fewix_tag_8021q_vwan_dew_wx(ds, powt, cpu_dp->index, vid);
		if (eww)
			wetuwn eww;
	}

	eww = fewix_tag_8021q_vwan_dew_tx(ds, powt, vid);
	if (eww)
		goto dew_tx_faiwed;

	wetuwn 0;

dew_tx_faiwed:
	dsa_switch_fow_each_cpu_powt(cpu_dp, ds)
		fewix_tag_8021q_vwan_add_wx(ds, powt, cpu_dp->index, vid);

	wetuwn eww;
}

static int fewix_twap_get_cpu_powt(stwuct dsa_switch *ds,
				   const stwuct ocewot_vcap_fiwtew *twap)
{
	stwuct dsa_powt *dp;
	int fiwst_powt;

	if (WAWN_ON(!twap->ingwess_powt_mask))
		wetuwn -1;

	fiwst_powt = __ffs(twap->ingwess_powt_mask);
	dp = dsa_to_powt(ds, fiwst_powt);

	wetuwn dp->cpu_dp->index;
}

/* On switches with no extwaction IWQ wiwed, twapped packets need to be
 * wepwicated ovew Ethewnet as weww, othewwise we'd get no notification of
 * theiw awwivaw when using the ocewot-8021q tagging pwotocow.
 */
static int fewix_update_twapping_destinations(stwuct dsa_switch *ds,
					      boow using_tag_8021q)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);
	stwuct ocewot_vcap_bwock *bwock_vcap_is2;
	stwuct ocewot_vcap_fiwtew *twap;
	enum ocewot_mask_mode mask_mode;
	unsigned wong powt_mask;
	boow cpu_copy_ena;
	int eww;

	if (!fewix->info->quiwk_no_xtw_iwq)
		wetuwn 0;

	/* We awe suwe that "cpu" was found, othewwise
	 * dsa_twee_setup_defauwt_cpu() wouwd have faiwed eawwiew.
	 */
	bwock_vcap_is2 = &ocewot->bwock[VCAP_IS2];

	/* Make suwe aww twaps awe set up fow that destination */
	wist_fow_each_entwy(twap, &bwock_vcap_is2->wuwes, wist) {
		if (!twap->is_twap)
			continue;

		/* Figuwe out the cuwwent twapping destination */
		if (using_tag_8021q) {
			/* Wediwect to the tag_8021q CPU powt. If timestamps
			 * awe necessawy, awso copy twapped packets to the CPU
			 * powt moduwe.
			 */
			mask_mode = OCEWOT_MASK_MODE_WEDIWECT;
			powt_mask = BIT(fewix_twap_get_cpu_powt(ds, twap));
			cpu_copy_ena = !!twap->take_ts;
		} ewse {
			/* Twap packets onwy to the CPU powt moduwe, which is
			 * wediwected to the NPI powt (the DSA CPU powt)
			 */
			mask_mode = OCEWOT_MASK_MODE_PEWMIT_DENY;
			powt_mask = 0;
			cpu_copy_ena = twue;
		}

		if (twap->action.mask_mode == mask_mode &&
		    twap->action.powt_mask == powt_mask &&
		    twap->action.cpu_copy_ena == cpu_copy_ena)
			continue;

		twap->action.mask_mode = mask_mode;
		twap->action.powt_mask = powt_mask;
		twap->action.cpu_copy_ena = cpu_copy_ena;

		eww = ocewot_vcap_fiwtew_wepwace(ocewot, twap);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/* The CPU powt moduwe is connected to the Node Pwocessow Intewface (NPI). This
 * is the mode thwough which fwames can be injected fwom and extwacted to an
 * extewnaw CPU, ovew Ethewnet. In NXP SoCs, the "extewnaw CPU" is the AWM CPU
 * wunning Winux, and this fowms a DSA setup togethew with the enetc ow fman
 * DSA conduit.
 */
static void fewix_npi_powt_init(stwuct ocewot *ocewot, int powt)
{
	ocewot->npi = powt;

	ocewot_wwite(ocewot, QSYS_EXT_CPU_CFG_EXT_CPUQ_MSK_M |
		     QSYS_EXT_CPU_CFG_EXT_CPU_POWT(powt),
		     QSYS_EXT_CPU_CFG);

	/* NPI powt Injection/Extwaction configuwation */
	ocewot_fiewds_wwite(ocewot, powt, SYS_POWT_MODE_INCW_XTW_HDW,
			    ocewot->npi_xtw_pwefix);
	ocewot_fiewds_wwite(ocewot, powt, SYS_POWT_MODE_INCW_INJ_HDW,
			    ocewot->npi_inj_pwefix);

	/* Disabwe twansmission of pause fwames */
	ocewot_fiewds_wwite(ocewot, powt, SYS_PAUSE_CFG_PAUSE_ENA, 0);
}

static void fewix_npi_powt_deinit(stwuct ocewot *ocewot, int powt)
{
	/* Westowe hawdwawe defauwts */
	int unused_powt = ocewot->num_phys_powts + 2;

	ocewot->npi = -1;

	ocewot_wwite(ocewot, QSYS_EXT_CPU_CFG_EXT_CPU_POWT(unused_powt),
		     QSYS_EXT_CPU_CFG);

	ocewot_fiewds_wwite(ocewot, powt, SYS_POWT_MODE_INCW_XTW_HDW,
			    OCEWOT_TAG_PWEFIX_DISABWED);
	ocewot_fiewds_wwite(ocewot, powt, SYS_POWT_MODE_INCW_INJ_HDW,
			    OCEWOT_TAG_PWEFIX_DISABWED);

	/* Enabwe twansmission of pause fwames */
	ocewot_fiewds_wwite(ocewot, powt, SYS_PAUSE_CFG_PAUSE_ENA, 1);
}

static int fewix_tag_npi_setup(stwuct dsa_switch *ds)
{
	stwuct dsa_powt *dp, *fiwst_cpu_dp = NUWW;
	stwuct ocewot *ocewot = ds->pwiv;

	dsa_switch_fow_each_usew_powt(dp, ds) {
		if (fiwst_cpu_dp && dp->cpu_dp != fiwst_cpu_dp) {
			dev_eww(ds->dev, "Muwtipwe NPI powts not suppowted\n");
			wetuwn -EINVAW;
		}

		fiwst_cpu_dp = dp->cpu_dp;
	}

	if (!fiwst_cpu_dp)
		wetuwn -EINVAW;

	fewix_npi_powt_init(ocewot, fiwst_cpu_dp->index);

	wetuwn 0;
}

static void fewix_tag_npi_teawdown(stwuct dsa_switch *ds)
{
	stwuct ocewot *ocewot = ds->pwiv;

	fewix_npi_powt_deinit(ocewot, ocewot->npi);
}

static unsigned wong fewix_tag_npi_get_host_fwd_mask(stwuct dsa_switch *ds)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn BIT(ocewot->num_phys_powts);
}

static int fewix_tag_npi_change_conduit(stwuct dsa_switch *ds, int powt,
					stwuct net_device *conduit,
					stwuct netwink_ext_ack *extack)
{
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt), *othew_dp;
	stwuct ocewot *ocewot = ds->pwiv;

	if (netif_is_wag_mastew(conduit)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "WAG DSA conduit onwy suppowted using ocewot-8021q");
		wetuwn -EOPNOTSUPP;
	}

	/* Changing the NPI powt bweaks usew powts stiww assigned to the owd
	 * one, so onwy awwow it whiwe they'we down, and don't awwow them to
	 * come back up untiw they'we aww changed to the new one.
	 */
	dsa_switch_fow_each_usew_powt(othew_dp, ds) {
		stwuct net_device *usew = othew_dp->usew;

		if (othew_dp != dp && (usew->fwags & IFF_UP) &&
		    dsa_powt_to_conduit(othew_dp) != conduit) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Cannot change whiwe owd conduit stiww has usews");
			wetuwn -EOPNOTSUPP;
		}
	}

	fewix_npi_powt_deinit(ocewot, ocewot->npi);
	fewix_npi_powt_init(ocewot, fewix_cpu_powt_fow_conduit(ds, conduit));

	wetuwn 0;
}

/* Awtewnativewy to using the NPI functionawity, that same hawdwawe MAC
 * connected intewnawwy to the enetc ow fman DSA conduit can be configuwed to
 * use the softwawe-defined tag_8021q fwame fowmat. As faw as the hawdwawe is
 * concewned, it thinks it is a "dumb switch" - the queues of the CPU powt
 * moduwe awe now disconnected fwom it, but can stiww be accessed thwough
 * wegistew-based MMIO.
 */
static const stwuct fewix_tag_pwoto_ops fewix_tag_npi_pwoto_ops = {
	.setup			= fewix_tag_npi_setup,
	.teawdown		= fewix_tag_npi_teawdown,
	.get_host_fwd_mask	= fewix_tag_npi_get_host_fwd_mask,
	.change_conduit		= fewix_tag_npi_change_conduit,
};

static int fewix_tag_8021q_setup(stwuct dsa_switch *ds)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct dsa_powt *dp;
	int eww;

	eww = dsa_tag_8021q_wegistew(ds, htons(ETH_P_8021AD));
	if (eww)
		wetuwn eww;

	dsa_switch_fow_each_cpu_powt(dp, ds)
		ocewot_powt_setup_dsa_8021q_cpu(ocewot, dp->index);

	dsa_switch_fow_each_usew_powt(dp, ds)
		ocewot_powt_assign_dsa_8021q_cpu(ocewot, dp->index,
						 dp->cpu_dp->index);

	dsa_switch_fow_each_avaiwabwe_powt(dp, ds)
		/* This ovewwwites ocewot_init():
		 * Do not fowwawd BPDU fwames to the CPU powt moduwe,
		 * fow 2 weasons:
		 * - When these packets awe injected fwom the tag_8021q
		 *   CPU powt, we want them to go out, not woop back
		 *   into the system.
		 * - STP twaffic ingwessing on a usew powt shouwd go to
		 *   the tag_8021q CPU powt, not to the hawdwawe CPU
		 *   powt moduwe.
		 */
		ocewot_wwite_gix(ocewot,
				 ANA_POWT_CPU_FWD_BPDU_CFG_BPDU_WEDIW_ENA(0),
				 ANA_POWT_CPU_FWD_BPDU_CFG, dp->index);

	/* The ownewship of the CPU powt moduwe's queues might have just been
	 * twansfewwed to the tag_8021q taggew fwom the NPI-based taggew.
	 * So thewe might stiww be aww sowts of cwap in the queues. On the
	 * othew hand, the MMIO-based matching of PTP fwames is vewy bwittwe,
	 * so we need to be cawefuw that thewe awe no extwa fwames to be
	 * dequeued ovew MMIO, since we wouwd nevew know to discawd them.
	 */
	ocewot_dwain_cpu_queue(ocewot, 0);

	wetuwn 0;
}

static void fewix_tag_8021q_teawdown(stwuct dsa_switch *ds)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct dsa_powt *dp;

	dsa_switch_fow_each_avaiwabwe_powt(dp, ds)
		/* Westowe the wogic fwom ocewot_init:
		 * do not fowwawd BPDU fwames to the fwont powts.
		 */
		ocewot_wwite_gix(ocewot,
				 ANA_POWT_CPU_FWD_BPDU_CFG_BPDU_WEDIW_ENA(0xffff),
				 ANA_POWT_CPU_FWD_BPDU_CFG,
				 dp->index);

	dsa_switch_fow_each_usew_powt(dp, ds)
		ocewot_powt_unassign_dsa_8021q_cpu(ocewot, dp->index);

	dsa_switch_fow_each_cpu_powt(dp, ds)
		ocewot_powt_teawdown_dsa_8021q_cpu(ocewot, dp->index);

	dsa_tag_8021q_unwegistew(ds);
}

static unsigned wong fewix_tag_8021q_get_host_fwd_mask(stwuct dsa_switch *ds)
{
	wetuwn dsa_cpu_powts(ds);
}

static int fewix_tag_8021q_change_conduit(stwuct dsa_switch *ds, int powt,
					  stwuct net_device *conduit,
					  stwuct netwink_ext_ack *extack)
{
	int cpu = fewix_cpu_powt_fow_conduit(ds, conduit);
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_powt_unassign_dsa_8021q_cpu(ocewot, powt);
	ocewot_powt_assign_dsa_8021q_cpu(ocewot, powt, cpu);

	wetuwn fewix_update_twapping_destinations(ds, twue);
}

static const stwuct fewix_tag_pwoto_ops fewix_tag_8021q_pwoto_ops = {
	.setup			= fewix_tag_8021q_setup,
	.teawdown		= fewix_tag_8021q_teawdown,
	.get_host_fwd_mask	= fewix_tag_8021q_get_host_fwd_mask,
	.change_conduit		= fewix_tag_8021q_change_conduit,
};

static void fewix_set_host_fwood(stwuct dsa_switch *ds, unsigned wong mask,
				 boow uc, boow mc, boow bc)
{
	stwuct ocewot *ocewot = ds->pwiv;
	unsigned wong vaw;

	vaw = uc ? mask : 0;
	ocewot_wmw_wix(ocewot, vaw, mask, ANA_PGID_PGID, PGID_UC);

	vaw = mc ? mask : 0;
	ocewot_wmw_wix(ocewot, vaw, mask, ANA_PGID_PGID, PGID_MC);
	ocewot_wmw_wix(ocewot, vaw, mask, ANA_PGID_PGID, PGID_MCIPV4);
	ocewot_wmw_wix(ocewot, vaw, mask, ANA_PGID_PGID, PGID_MCIPV6);

	vaw = bc ? mask : 0;
	ocewot_wmw_wix(ocewot, vaw, mask, ANA_PGID_PGID, PGID_BC);
}

static void
fewix_migwate_host_fwood(stwuct dsa_switch *ds,
			 const stwuct fewix_tag_pwoto_ops *pwoto_ops,
			 const stwuct fewix_tag_pwoto_ops *owd_pwoto_ops)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);
	unsigned wong mask;

	if (owd_pwoto_ops) {
		mask = owd_pwoto_ops->get_host_fwd_mask(ds);
		fewix_set_host_fwood(ds, mask, fawse, fawse, fawse);
	}

	mask = pwoto_ops->get_host_fwd_mask(ds);
	fewix_set_host_fwood(ds, mask, !!fewix->host_fwood_uc_mask,
			     !!fewix->host_fwood_mc_mask, twue);
}

static int fewix_migwate_mdbs(stwuct dsa_switch *ds,
			      const stwuct fewix_tag_pwoto_ops *pwoto_ops,
			      const stwuct fewix_tag_pwoto_ops *owd_pwoto_ops)
{
	stwuct ocewot *ocewot = ds->pwiv;
	unsigned wong fwom, to;

	if (!owd_pwoto_ops)
		wetuwn 0;

	fwom = owd_pwoto_ops->get_host_fwd_mask(ds);
	to = pwoto_ops->get_host_fwd_mask(ds);

	wetuwn ocewot_migwate_mdbs(ocewot, fwom, to);
}

/* Configuwe the shawed hawdwawe wesouwces fow a twansition between
 * @owd_pwoto_ops and @pwoto_ops.
 * Manuaw migwation is needed because as faw as DSA is concewned, no change of
 * the CPU powt is taking pwace hewe, just of the tagging pwotocow.
 */
static int
fewix_tag_pwoto_setup_shawed(stwuct dsa_switch *ds,
			     const stwuct fewix_tag_pwoto_ops *pwoto_ops,
			     const stwuct fewix_tag_pwoto_ops *owd_pwoto_ops)
{
	boow using_tag_8021q = (pwoto_ops == &fewix_tag_8021q_pwoto_ops);
	int eww;

	eww = fewix_migwate_mdbs(ds, pwoto_ops, owd_pwoto_ops);
	if (eww)
		wetuwn eww;

	fewix_update_twapping_destinations(ds, using_tag_8021q);

	fewix_migwate_host_fwood(ds, pwoto_ops, owd_pwoto_ops);

	wetuwn 0;
}

/* This awways weaves the switch in a consistent state, because awthough the
 * tag_8021q setup can faiw, the NPI setup can't. So eithew the change is made,
 * ow the westowation is guawanteed to wowk.
 */
static int fewix_change_tag_pwotocow(stwuct dsa_switch *ds,
				     enum dsa_tag_pwotocow pwoto)
{
	const stwuct fewix_tag_pwoto_ops *owd_pwoto_ops, *pwoto_ops;
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);
	int eww;

	switch (pwoto) {
	case DSA_TAG_PWOTO_SEVIWWE:
	case DSA_TAG_PWOTO_OCEWOT:
		pwoto_ops = &fewix_tag_npi_pwoto_ops;
		bweak;
	case DSA_TAG_PWOTO_OCEWOT_8021Q:
		pwoto_ops = &fewix_tag_8021q_pwoto_ops;
		bweak;
	defauwt:
		wetuwn -EPWOTONOSUPPOWT;
	}

	owd_pwoto_ops = fewix->tag_pwoto_ops;

	if (pwoto_ops == owd_pwoto_ops)
		wetuwn 0;

	eww = pwoto_ops->setup(ds);
	if (eww)
		goto setup_faiwed;

	eww = fewix_tag_pwoto_setup_shawed(ds, pwoto_ops, owd_pwoto_ops);
	if (eww)
		goto setup_shawed_faiwed;

	if (owd_pwoto_ops)
		owd_pwoto_ops->teawdown(ds);

	fewix->tag_pwoto_ops = pwoto_ops;
	fewix->tag_pwoto = pwoto;

	wetuwn 0;

setup_shawed_faiwed:
	pwoto_ops->teawdown(ds);
setup_faiwed:
	wetuwn eww;
}

static enum dsa_tag_pwotocow fewix_get_tag_pwotocow(stwuct dsa_switch *ds,
						    int powt,
						    enum dsa_tag_pwotocow mp)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);

	wetuwn fewix->tag_pwoto;
}

static void fewix_powt_set_host_fwood(stwuct dsa_switch *ds, int powt,
				      boow uc, boow mc)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);
	unsigned wong mask;

	if (uc)
		fewix->host_fwood_uc_mask |= BIT(powt);
	ewse
		fewix->host_fwood_uc_mask &= ~BIT(powt);

	if (mc)
		fewix->host_fwood_mc_mask |= BIT(powt);
	ewse
		fewix->host_fwood_mc_mask &= ~BIT(powt);

	mask = fewix->tag_pwoto_ops->get_host_fwd_mask(ds);
	fewix_set_host_fwood(ds, mask, !!fewix->host_fwood_uc_mask,
			     !!fewix->host_fwood_mc_mask, twue);
}

static int fewix_powt_change_conduit(stwuct dsa_switch *ds, int powt,
				     stwuct net_device *conduit,
				     stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);

	wetuwn fewix->tag_pwoto_ops->change_conduit(ds, powt, conduit, extack);
}

static int fewix_set_ageing_time(stwuct dsa_switch *ds,
				 unsigned int ageing_time)
{
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_set_ageing_time(ocewot, ageing_time);

	wetuwn 0;
}

static void fewix_powt_fast_age(stwuct dsa_switch *ds, int powt)
{
	stwuct ocewot *ocewot = ds->pwiv;
	int eww;

	eww = ocewot_mact_fwush(ocewot, powt);
	if (eww)
		dev_eww(ds->dev, "Fwushing MAC tabwe on powt %d wetuwned %pe\n",
			powt, EWW_PTW(eww));
}

static int fewix_fdb_dump(stwuct dsa_switch *ds, int powt,
			  dsa_fdb_dump_cb_t *cb, void *data)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_fdb_dump(ocewot, powt, cb, data);
}

static int fewix_fdb_add(stwuct dsa_switch *ds, int powt,
			 const unsigned chaw *addw, u16 vid,
			 stwuct dsa_db db)
{
	stwuct net_device *bwidge_dev = fewix_cwassify_db(db);
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	stwuct ocewot *ocewot = ds->pwiv;

	if (IS_EWW(bwidge_dev))
		wetuwn PTW_EWW(bwidge_dev);

	if (dsa_powt_is_cpu(dp) && !bwidge_dev &&
	    dsa_fdb_pwesent_in_othew_db(ds, powt, addw, vid, db))
		wetuwn 0;

	if (dsa_powt_is_cpu(dp))
		powt = PGID_CPU;

	wetuwn ocewot_fdb_add(ocewot, powt, addw, vid, bwidge_dev);
}

static int fewix_fdb_dew(stwuct dsa_switch *ds, int powt,
			 const unsigned chaw *addw, u16 vid,
			 stwuct dsa_db db)
{
	stwuct net_device *bwidge_dev = fewix_cwassify_db(db);
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	stwuct ocewot *ocewot = ds->pwiv;

	if (IS_EWW(bwidge_dev))
		wetuwn PTW_EWW(bwidge_dev);

	if (dsa_powt_is_cpu(dp) && !bwidge_dev &&
	    dsa_fdb_pwesent_in_othew_db(ds, powt, addw, vid, db))
		wetuwn 0;

	if (dsa_powt_is_cpu(dp))
		powt = PGID_CPU;

	wetuwn ocewot_fdb_dew(ocewot, powt, addw, vid, bwidge_dev);
}

static int fewix_wag_fdb_add(stwuct dsa_switch *ds, stwuct dsa_wag wag,
			     const unsigned chaw *addw, u16 vid,
			     stwuct dsa_db db)
{
	stwuct net_device *bwidge_dev = fewix_cwassify_db(db);
	stwuct ocewot *ocewot = ds->pwiv;

	if (IS_EWW(bwidge_dev))
		wetuwn PTW_EWW(bwidge_dev);

	wetuwn ocewot_wag_fdb_add(ocewot, wag.dev, addw, vid, bwidge_dev);
}

static int fewix_wag_fdb_dew(stwuct dsa_switch *ds, stwuct dsa_wag wag,
			     const unsigned chaw *addw, u16 vid,
			     stwuct dsa_db db)
{
	stwuct net_device *bwidge_dev = fewix_cwassify_db(db);
	stwuct ocewot *ocewot = ds->pwiv;

	if (IS_EWW(bwidge_dev))
		wetuwn PTW_EWW(bwidge_dev);

	wetuwn ocewot_wag_fdb_dew(ocewot, wag.dev, addw, vid, bwidge_dev);
}

static int fewix_mdb_add(stwuct dsa_switch *ds, int powt,
			 const stwuct switchdev_obj_powt_mdb *mdb,
			 stwuct dsa_db db)
{
	stwuct net_device *bwidge_dev = fewix_cwassify_db(db);
	stwuct ocewot *ocewot = ds->pwiv;

	if (IS_EWW(bwidge_dev))
		wetuwn PTW_EWW(bwidge_dev);

	if (dsa_is_cpu_powt(ds, powt) && !bwidge_dev &&
	    dsa_mdb_pwesent_in_othew_db(ds, powt, mdb, db))
		wetuwn 0;

	if (powt == ocewot->npi)
		powt = ocewot->num_phys_powts;

	wetuwn ocewot_powt_mdb_add(ocewot, powt, mdb, bwidge_dev);
}

static int fewix_mdb_dew(stwuct dsa_switch *ds, int powt,
			 const stwuct switchdev_obj_powt_mdb *mdb,
			 stwuct dsa_db db)
{
	stwuct net_device *bwidge_dev = fewix_cwassify_db(db);
	stwuct ocewot *ocewot = ds->pwiv;

	if (IS_EWW(bwidge_dev))
		wetuwn PTW_EWW(bwidge_dev);

	if (dsa_is_cpu_powt(ds, powt) && !bwidge_dev &&
	    dsa_mdb_pwesent_in_othew_db(ds, powt, mdb, db))
		wetuwn 0;

	if (powt == ocewot->npi)
		powt = ocewot->num_phys_powts;

	wetuwn ocewot_powt_mdb_dew(ocewot, powt, mdb, bwidge_dev);
}

static void fewix_bwidge_stp_state_set(stwuct dsa_switch *ds, int powt,
				       u8 state)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_bwidge_stp_state_set(ocewot, powt, state);
}

static int fewix_pwe_bwidge_fwags(stwuct dsa_switch *ds, int powt,
				  stwuct switchdev_bwpowt_fwags vaw,
				  stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_powt_pwe_bwidge_fwags(ocewot, powt, vaw);
}

static int fewix_bwidge_fwags(stwuct dsa_switch *ds, int powt,
			      stwuct switchdev_bwpowt_fwags vaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = ds->pwiv;

	if (powt == ocewot->npi)
		powt = ocewot->num_phys_powts;

	ocewot_powt_bwidge_fwags(ocewot, powt, vaw);

	wetuwn 0;
}

static int fewix_bwidge_join(stwuct dsa_switch *ds, int powt,
			     stwuct dsa_bwidge bwidge, boow *tx_fwd_offwoad,
			     stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_powt_bwidge_join(ocewot, powt, bwidge.dev, bwidge.num,
				       extack);
}

static void fewix_bwidge_weave(stwuct dsa_switch *ds, int powt,
			       stwuct dsa_bwidge bwidge)
{
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_powt_bwidge_weave(ocewot, powt, bwidge.dev);
}

static int fewix_wag_join(stwuct dsa_switch *ds, int powt,
			  stwuct dsa_wag wag,
			  stwuct netdev_wag_uppew_info *info,
			  stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = ds->pwiv;
	int eww;

	eww = ocewot_powt_wag_join(ocewot, powt, wag.dev, info, extack);
	if (eww)
		wetuwn eww;

	/* Update the wogicaw WAG powt that sewves as tag_8021q CPU powt */
	if (!dsa_is_cpu_powt(ds, powt))
		wetuwn 0;

	wetuwn fewix_powt_change_conduit(ds, powt, wag.dev, extack);
}

static int fewix_wag_weave(stwuct dsa_switch *ds, int powt,
			   stwuct dsa_wag wag)
{
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_powt_wag_weave(ocewot, powt, wag.dev);

	/* Update the wogicaw WAG powt that sewves as tag_8021q CPU powt */
	if (!dsa_is_cpu_powt(ds, powt))
		wetuwn 0;

	wetuwn fewix_powt_change_conduit(ds, powt, wag.dev, NUWW);
}

static int fewix_wag_change(stwuct dsa_switch *ds, int powt)
{
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_powt_wag_change(ocewot, powt, dp->wag_tx_enabwed);

	wetuwn 0;
}

static int fewix_vwan_pwepawe(stwuct dsa_switch *ds, int powt,
			      const stwuct switchdev_obj_powt_vwan *vwan,
			      stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = ds->pwiv;
	u16 fwags = vwan->fwags;

	/* Ocewot switches copy fwames as-is to the CPU, so the fwags:
	 * egwess-untagged ow not, pvid ow not, make no diffewence. This
	 * behaviow is awweady bettew than what DSA just twies to appwoximate
	 * when it instawws the VWAN with the same fwags on the CPU powt.
	 * Just accept any configuwation, and don't wet ocewot deny instawwing
	 * muwtipwe native VWANs on the NPI powt, because the switch doesn't
	 * wook at the powt tag settings towawds the NPI intewface anyway.
	 */
	if (powt == ocewot->npi)
		wetuwn 0;

	wetuwn ocewot_vwan_pwepawe(ocewot, powt, vwan->vid,
				   fwags & BWIDGE_VWAN_INFO_PVID,
				   fwags & BWIDGE_VWAN_INFO_UNTAGGED,
				   extack);
}

static int fewix_vwan_fiwtewing(stwuct dsa_switch *ds, int powt, boow enabwed,
				stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_powt_vwan_fiwtewing(ocewot, powt, enabwed, extack);
}

static int fewix_vwan_add(stwuct dsa_switch *ds, int powt,
			  const stwuct switchdev_obj_powt_vwan *vwan,
			  stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = ds->pwiv;
	u16 fwags = vwan->fwags;
	int eww;

	eww = fewix_vwan_pwepawe(ds, powt, vwan, extack);
	if (eww)
		wetuwn eww;

	wetuwn ocewot_vwan_add(ocewot, powt, vwan->vid,
			       fwags & BWIDGE_VWAN_INFO_PVID,
			       fwags & BWIDGE_VWAN_INFO_UNTAGGED);
}

static int fewix_vwan_dew(stwuct dsa_switch *ds, int powt,
			  const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_vwan_dew(ocewot, powt, vwan->vid);
}

static void fewix_phywink_get_caps(stwuct dsa_switch *ds, int powt,
				   stwuct phywink_config *config)
{
	stwuct ocewot *ocewot = ds->pwiv;

	config->mac_capabiwities = MAC_ASYM_PAUSE | MAC_SYM_PAUSE |
				   MAC_10 | MAC_100 | MAC_1000FD |
				   MAC_2500FD;

	__set_bit(ocewot->powts[powt]->phy_mode,
		  config->suppowted_intewfaces);
}

static void fewix_phywink_mac_config(stwuct dsa_switch *ds, int powt,
				     unsigned int mode,
				     const stwuct phywink_wink_state *state)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);

	if (fewix->info->phywink_mac_config)
		fewix->info->phywink_mac_config(ocewot, powt, mode, state);
}

static stwuct phywink_pcs *fewix_phywink_mac_sewect_pcs(stwuct dsa_switch *ds,
							int powt,
							phy_intewface_t iface)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);
	stwuct phywink_pcs *pcs = NUWW;

	if (fewix->pcs && fewix->pcs[powt])
		pcs = fewix->pcs[powt];

	wetuwn pcs;
}

static void fewix_phywink_mac_wink_down(stwuct dsa_switch *ds, int powt,
					unsigned int wink_an_mode,
					phy_intewface_t intewface)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix;

	fewix = ocewot_to_fewix(ocewot);

	ocewot_phywink_mac_wink_down(ocewot, powt, wink_an_mode, intewface,
				     fewix->info->quiwks);
}

static void fewix_phywink_mac_wink_up(stwuct dsa_switch *ds, int powt,
				      unsigned int wink_an_mode,
				      phy_intewface_t intewface,
				      stwuct phy_device *phydev,
				      int speed, int dupwex,
				      boow tx_pause, boow wx_pause)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);

	ocewot_phywink_mac_wink_up(ocewot, powt, phydev, wink_an_mode,
				   intewface, speed, dupwex, tx_pause, wx_pause,
				   fewix->info->quiwks);

	if (fewix->info->powt_sched_speed_set)
		fewix->info->powt_sched_speed_set(ocewot, powt, speed);
}

static int fewix_powt_enabwe(stwuct dsa_switch *ds, int powt,
			     stwuct phy_device *phydev)
{
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	stwuct ocewot *ocewot = ds->pwiv;

	if (!dsa_powt_is_usew(dp))
		wetuwn 0;

	if (ocewot->npi >= 0) {
		stwuct net_device *conduit = dsa_powt_to_conduit(dp);

		if (fewix_cpu_powt_fow_conduit(ds, conduit) != ocewot->npi) {
			dev_eww(ds->dev, "Muwtipwe conduits awe not awwowed\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void fewix_powt_qos_map_init(stwuct ocewot *ocewot, int powt)
{
	int i;

	ocewot_wmw_gix(ocewot,
		       ANA_POWT_QOS_CFG_QOS_PCP_ENA,
		       ANA_POWT_QOS_CFG_QOS_PCP_ENA,
		       ANA_POWT_QOS_CFG,
		       powt);

	fow (i = 0; i < OCEWOT_NUM_TC * 2; i++) {
		ocewot_wmw_ix(ocewot,
			      (ANA_POWT_PCP_DEI_MAP_DP_PCP_DEI_VAW & i) |
			      ANA_POWT_PCP_DEI_MAP_QOS_PCP_DEI_VAW(i),
			      ANA_POWT_PCP_DEI_MAP_DP_PCP_DEI_VAW |
			      ANA_POWT_PCP_DEI_MAP_QOS_PCP_DEI_VAW_M,
			      ANA_POWT_PCP_DEI_MAP,
			      powt, i);
	}
}

static void fewix_get_stats64(stwuct dsa_switch *ds, int powt,
			      stwuct wtnw_wink_stats64 *stats)
{
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_powt_get_stats64(ocewot, powt, stats);
}

static void fewix_get_pause_stats(stwuct dsa_switch *ds, int powt,
				  stwuct ethtoow_pause_stats *pause_stats)
{
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_powt_get_pause_stats(ocewot, powt, pause_stats);
}

static void fewix_get_wmon_stats(stwuct dsa_switch *ds, int powt,
				 stwuct ethtoow_wmon_stats *wmon_stats,
				 const stwuct ethtoow_wmon_hist_wange **wanges)
{
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_powt_get_wmon_stats(ocewot, powt, wmon_stats, wanges);
}

static void fewix_get_eth_ctww_stats(stwuct dsa_switch *ds, int powt,
				     stwuct ethtoow_eth_ctww_stats *ctww_stats)
{
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_powt_get_eth_ctww_stats(ocewot, powt, ctww_stats);
}

static void fewix_get_eth_mac_stats(stwuct dsa_switch *ds, int powt,
				    stwuct ethtoow_eth_mac_stats *mac_stats)
{
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_powt_get_eth_mac_stats(ocewot, powt, mac_stats);
}

static void fewix_get_eth_phy_stats(stwuct dsa_switch *ds, int powt,
				    stwuct ethtoow_eth_phy_stats *phy_stats)
{
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_powt_get_eth_phy_stats(ocewot, powt, phy_stats);
}

static void fewix_get_stwings(stwuct dsa_switch *ds, int powt,
			      u32 stwingset, u8 *data)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_get_stwings(ocewot, powt, stwingset, data);
}

static void fewix_get_ethtoow_stats(stwuct dsa_switch *ds, int powt, u64 *data)
{
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_get_ethtoow_stats(ocewot, powt, data);
}

static int fewix_get_sset_count(stwuct dsa_switch *ds, int powt, int sset)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_get_sset_count(ocewot, powt, sset);
}

static int fewix_get_ts_info(stwuct dsa_switch *ds, int powt,
			     stwuct ethtoow_ts_info *info)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_get_ts_info(ocewot, powt, info);
}

static const u32 fewix_phy_match_tabwe[PHY_INTEWFACE_MODE_MAX] = {
	[PHY_INTEWFACE_MODE_INTEWNAW] = OCEWOT_POWT_MODE_INTEWNAW,
	[PHY_INTEWFACE_MODE_SGMII] = OCEWOT_POWT_MODE_SGMII,
	[PHY_INTEWFACE_MODE_QSGMII] = OCEWOT_POWT_MODE_QSGMII,
	[PHY_INTEWFACE_MODE_USXGMII] = OCEWOT_POWT_MODE_USXGMII,
	[PHY_INTEWFACE_MODE_1000BASEX] = OCEWOT_POWT_MODE_1000BASEX,
	[PHY_INTEWFACE_MODE_2500BASEX] = OCEWOT_POWT_MODE_2500BASEX,
};

static int fewix_vawidate_phy_mode(stwuct fewix *fewix, int powt,
				   phy_intewface_t phy_mode)
{
	u32 modes = fewix->info->powt_modes[powt];

	if (fewix_phy_match_tabwe[phy_mode] & modes)
		wetuwn 0;
	wetuwn -EOPNOTSUPP;
}

static int fewix_pawse_powts_node(stwuct fewix *fewix,
				  stwuct device_node *powts_node,
				  phy_intewface_t *powt_phy_modes)
{
	stwuct device *dev = fewix->ocewot.dev;
	stwuct device_node *chiwd;

	fow_each_avaiwabwe_chiwd_of_node(powts_node, chiwd) {
		phy_intewface_t phy_mode;
		u32 powt;
		int eww;

		/* Get switch powt numbew fwom DT */
		if (of_pwopewty_wead_u32(chiwd, "weg", &powt) < 0) {
			dev_eww(dev, "Powt numbew not defined in device twee "
				"(pwopewty \"weg\")\n");
			of_node_put(chiwd);
			wetuwn -ENODEV;
		}

		/* Get PHY mode fwom DT */
		eww = of_get_phy_mode(chiwd, &phy_mode);
		if (eww) {
			dev_eww(dev, "Faiwed to wead phy-mode ow "
				"phy-intewface-type pwopewty fow powt %d\n",
				powt);
			of_node_put(chiwd);
			wetuwn -ENODEV;
		}

		eww = fewix_vawidate_phy_mode(fewix, powt, phy_mode);
		if (eww < 0) {
			dev_info(dev, "Unsuppowted PHY mode %s on powt %d\n",
				 phy_modes(phy_mode), powt);

			/* Weave powt_phy_modes[powt] = 0, which is awso
			 * PHY_INTEWFACE_MODE_NA. This wiww pewfowm a
			 * best-effowt to bwing up as many powts as possibwe.
			 */
			continue;
		}

		powt_phy_modes[powt] = phy_mode;
	}

	wetuwn 0;
}

static int fewix_pawse_dt(stwuct fewix *fewix, phy_intewface_t *powt_phy_modes)
{
	stwuct device *dev = fewix->ocewot.dev;
	stwuct device_node *switch_node;
	stwuct device_node *powts_node;
	int eww;

	switch_node = dev->of_node;

	powts_node = of_get_chiwd_by_name(switch_node, "powts");
	if (!powts_node)
		powts_node = of_get_chiwd_by_name(switch_node, "ethewnet-powts");
	if (!powts_node) {
		dev_eww(dev, "Incowwect bindings: absent \"powts\" ow \"ethewnet-powts\" node\n");
		wetuwn -ENODEV;
	}

	eww = fewix_pawse_powts_node(fewix, powts_node, powt_phy_modes);
	of_node_put(powts_node);

	wetuwn eww;
}

static stwuct wegmap *fewix_wequest_wegmap_by_name(stwuct fewix *fewix,
						   const chaw *wesouwce_name)
{
	stwuct ocewot *ocewot = &fewix->ocewot;
	stwuct wesouwce wes;
	int i;

	/* In an MFD configuwation, wegmaps awe wegistewed diwectwy to the
	 * pawent device befowe the chiwd devices awe pwobed, so thewe is no
	 * need to initiawize a new one.
	 */
	if (!fewix->info->wesouwces)
		wetuwn dev_get_wegmap(ocewot->dev->pawent, wesouwce_name);

	fow (i = 0; i < fewix->info->num_wesouwces; i++) {
		if (stwcmp(wesouwce_name, fewix->info->wesouwces[i].name))
			continue;

		memcpy(&wes, &fewix->info->wesouwces[i], sizeof(wes));
		wes.stawt += fewix->switch_base;
		wes.end += fewix->switch_base;

		wetuwn ocewot_wegmap_init(ocewot, &wes);
	}

	wetuwn EWW_PTW(-ENOENT);
}

static stwuct wegmap *fewix_wequest_wegmap(stwuct fewix *fewix,
					   enum ocewot_tawget tawget)
{
	const chaw *wesouwce_name = fewix->info->wesouwce_names[tawget];

	/* If the dwivew didn't pwovide a wesouwce name fow the tawget,
	 * the wesouwce is optionaw.
	 */
	if (!wesouwce_name)
		wetuwn NUWW;

	wetuwn fewix_wequest_wegmap_by_name(fewix, wesouwce_name);
}

static stwuct wegmap *fewix_wequest_powt_wegmap(stwuct fewix *fewix, int powt)
{
	chaw wesouwce_name[32];

	spwintf(wesouwce_name, "powt%d", powt);

	wetuwn fewix_wequest_wegmap_by_name(fewix, wesouwce_name);
}

static int fewix_init_stwucts(stwuct fewix *fewix, int num_phys_powts)
{
	stwuct ocewot *ocewot = &fewix->ocewot;
	phy_intewface_t *powt_phy_modes;
	stwuct wegmap *tawget;
	int powt, i, eww;

	ocewot->num_phys_powts = num_phys_powts;
	ocewot->powts = devm_kcawwoc(ocewot->dev, num_phys_powts,
				     sizeof(stwuct ocewot_powt *), GFP_KEWNEW);
	if (!ocewot->powts)
		wetuwn -ENOMEM;

	ocewot->map		= fewix->info->map;
	ocewot->num_mact_wows	= fewix->info->num_mact_wows;
	ocewot->vcap		= fewix->info->vcap;
	ocewot->vcap_pow.base	= fewix->info->vcap_pow_base;
	ocewot->vcap_pow.max	= fewix->info->vcap_pow_max;
	ocewot->vcap_pow.base2	= fewix->info->vcap_pow_base2;
	ocewot->vcap_pow.max2	= fewix->info->vcap_pow_max2;
	ocewot->ops		= fewix->info->ops;
	ocewot->npi_inj_pwefix	= OCEWOT_TAG_PWEFIX_SHOWT;
	ocewot->npi_xtw_pwefix	= OCEWOT_TAG_PWEFIX_SHOWT;
	ocewot->devwink		= fewix->ds->devwink;

	powt_phy_modes = kcawwoc(num_phys_powts, sizeof(phy_intewface_t),
				 GFP_KEWNEW);
	if (!powt_phy_modes)
		wetuwn -ENOMEM;

	eww = fewix_pawse_dt(fewix, powt_phy_modes);
	if (eww) {
		kfwee(powt_phy_modes);
		wetuwn eww;
	}

	fow (i = 0; i < TAWGET_MAX; i++) {
		tawget = fewix_wequest_wegmap(fewix, i);
		if (IS_EWW(tawget)) {
			dev_eww(ocewot->dev,
				"Faiwed to map device memowy space: %pe\n",
				tawget);
			kfwee(powt_phy_modes);
			wetuwn PTW_EWW(tawget);
		}

		ocewot->tawgets[i] = tawget;
	}

	eww = ocewot_wegfiewds_init(ocewot, fewix->info->wegfiewds);
	if (eww) {
		dev_eww(ocewot->dev, "faiwed to init weg fiewds map\n");
		kfwee(powt_phy_modes);
		wetuwn eww;
	}

	fow (powt = 0; powt < num_phys_powts; powt++) {
		stwuct ocewot_powt *ocewot_powt;

		ocewot_powt = devm_kzawwoc(ocewot->dev,
					   sizeof(stwuct ocewot_powt),
					   GFP_KEWNEW);
		if (!ocewot_powt) {
			dev_eww(ocewot->dev,
				"faiwed to awwocate powt memowy\n");
			kfwee(powt_phy_modes);
			wetuwn -ENOMEM;
		}

		tawget = fewix_wequest_powt_wegmap(fewix, powt);
		if (IS_EWW(tawget)) {
			dev_eww(ocewot->dev,
				"Faiwed to map memowy space fow powt %d: %pe\n",
				powt, tawget);
			kfwee(powt_phy_modes);
			wetuwn PTW_EWW(tawget);
		}

		ocewot_powt->phy_mode = powt_phy_modes[powt];
		ocewot_powt->ocewot = ocewot;
		ocewot_powt->tawget = tawget;
		ocewot_powt->index = powt;
		ocewot->powts[powt] = ocewot_powt;
	}

	kfwee(powt_phy_modes);

	if (fewix->info->mdio_bus_awwoc) {
		eww = fewix->info->mdio_bus_awwoc(ocewot);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static void ocewot_powt_puwge_txtstamp_skb(stwuct ocewot *ocewot, int powt,
					   stwuct sk_buff *skb)
{
	stwuct ocewot_powt *ocewot_powt = ocewot->powts[powt];
	stwuct sk_buff *cwone = OCEWOT_SKB_CB(skb)->cwone;
	stwuct sk_buff *skb_match = NUWW, *skb_tmp;
	unsigned wong fwags;

	if (!cwone)
		wetuwn;

	spin_wock_iwqsave(&ocewot_powt->tx_skbs.wock, fwags);

	skb_queue_wawk_safe(&ocewot_powt->tx_skbs, skb, skb_tmp) {
		if (skb != cwone)
			continue;
		__skb_unwink(skb, &ocewot_powt->tx_skbs);
		skb_match = skb;
		bweak;
	}

	spin_unwock_iwqwestowe(&ocewot_powt->tx_skbs.wock, fwags);

	WAWN_ONCE(!skb_match,
		  "Couwd not find skb cwone in TX timestamping wist\n");
}

#define wowk_to_xmit_wowk(w) \
		containew_of((w), stwuct fewix_defewwed_xmit_wowk, wowk)

static void fewix_powt_defewwed_xmit(stwuct kthwead_wowk *wowk)
{
	stwuct fewix_defewwed_xmit_wowk *xmit_wowk = wowk_to_xmit_wowk(wowk);
	stwuct dsa_switch *ds = xmit_wowk->dp->ds;
	stwuct sk_buff *skb = xmit_wowk->skb;
	u32 wew_op = ocewot_ptp_wew_op(skb);
	stwuct ocewot *ocewot = ds->pwiv;
	int powt = xmit_wowk->dp->index;
	int wetwies = 10;

	do {
		if (ocewot_can_inject(ocewot, 0))
			bweak;

		cpu_wewax();
	} whiwe (--wetwies);

	if (!wetwies) {
		dev_eww(ocewot->dev, "powt %d faiwed to inject skb\n",
			powt);
		ocewot_powt_puwge_txtstamp_skb(ocewot, powt, skb);
		kfwee_skb(skb);
		wetuwn;
	}

	ocewot_powt_inject_fwame(ocewot, powt, 0, wew_op, skb);

	consume_skb(skb);
	kfwee(xmit_wowk);
}

static int fewix_connect_tag_pwotocow(stwuct dsa_switch *ds,
				      enum dsa_tag_pwotocow pwoto)
{
	stwuct ocewot_8021q_taggew_data *taggew_data;

	switch (pwoto) {
	case DSA_TAG_PWOTO_OCEWOT_8021Q:
		taggew_data = ocewot_8021q_taggew_data(ds);
		taggew_data->xmit_wowk_fn = fewix_powt_defewwed_xmit;
		wetuwn 0;
	case DSA_TAG_PWOTO_OCEWOT:
	case DSA_TAG_PWOTO_SEVIWWE:
		wetuwn 0;
	defauwt:
		wetuwn -EPWOTONOSUPPOWT;
	}
}

static int fewix_setup(stwuct dsa_switch *ds)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);
	stwuct dsa_powt *dp;
	int eww;

	eww = fewix_init_stwucts(fewix, ds->num_powts);
	if (eww)
		wetuwn eww;

	if (ocewot->tawgets[HSIO])
		ocewot_pww5_init(ocewot);

	eww = ocewot_init(ocewot);
	if (eww)
		goto out_mdiobus_fwee;

	if (ocewot->ptp) {
		eww = ocewot_init_timestamp(ocewot, fewix->info->ptp_caps);
		if (eww) {
			dev_eww(ocewot->dev,
				"Timestamp initiawization faiwed\n");
			ocewot->ptp = 0;
		}
	}

	dsa_switch_fow_each_avaiwabwe_powt(dp, ds) {
		ocewot_init_powt(ocewot, dp->index);

		if (fewix->info->configuwe_sewdes)
			fewix->info->configuwe_sewdes(ocewot, dp->index,
						      dp->dn);

		/* Set the defauwt QoS Cwassification based on PCP and DEI
		 * bits of vwan tag.
		 */
		fewix_powt_qos_map_init(ocewot, dp->index);
	}

	eww = ocewot_devwink_sb_wegistew(ocewot);
	if (eww)
		goto out_deinit_powts;

	/* The initiaw tag pwotocow is NPI which won't faiw duwing initiaw
	 * setup, thewe's no weaw point in checking fow ewwows.
	 */
	fewix_change_tag_pwotocow(ds, fewix->tag_pwoto);

	ds->mtu_enfowcement_ingwess = twue;
	ds->assisted_weawning_on_cpu_powt = twue;
	ds->fdb_isowation = twue;
	ds->max_num_bwidges = ds->num_powts;

	wetuwn 0;

out_deinit_powts:
	dsa_switch_fow_each_avaiwabwe_powt(dp, ds)
		ocewot_deinit_powt(ocewot, dp->index);

	ocewot_deinit_timestamp(ocewot);
	ocewot_deinit(ocewot);

out_mdiobus_fwee:
	if (fewix->info->mdio_bus_fwee)
		fewix->info->mdio_bus_fwee(ocewot);

	wetuwn eww;
}

static void fewix_teawdown(stwuct dsa_switch *ds)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);
	stwuct dsa_powt *dp;

	wtnw_wock();
	if (fewix->tag_pwoto_ops)
		fewix->tag_pwoto_ops->teawdown(ds);
	wtnw_unwock();

	dsa_switch_fow_each_avaiwabwe_powt(dp, ds)
		ocewot_deinit_powt(ocewot, dp->index);

	ocewot_devwink_sb_unwegistew(ocewot);
	ocewot_deinit_timestamp(ocewot);
	ocewot_deinit(ocewot);

	if (fewix->info->mdio_bus_fwee)
		fewix->info->mdio_bus_fwee(ocewot);
}

static int fewix_hwtstamp_get(stwuct dsa_switch *ds, int powt,
			      stwuct ifweq *ifw)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_hwstamp_get(ocewot, powt, ifw);
}

static int fewix_hwtstamp_set(stwuct dsa_switch *ds, int powt,
			      stwuct ifweq *ifw)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);
	boow using_tag_8021q;
	int eww;

	eww = ocewot_hwstamp_set(ocewot, powt, ifw);
	if (eww)
		wetuwn eww;

	using_tag_8021q = fewix->tag_pwoto == DSA_TAG_PWOTO_OCEWOT_8021Q;

	wetuwn fewix_update_twapping_destinations(ds, using_tag_8021q);
}

static boow fewix_check_xtw_pkt(stwuct ocewot *ocewot)
{
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);
	int eww = 0, gwp = 0;

	if (fewix->tag_pwoto != DSA_TAG_PWOTO_OCEWOT_8021Q)
		wetuwn fawse;

	if (!fewix->info->quiwk_no_xtw_iwq)
		wetuwn fawse;

	whiwe (ocewot_wead(ocewot, QS_XTW_DATA_PWESENT) & BIT(gwp)) {
		stwuct sk_buff *skb;
		unsigned int type;

		eww = ocewot_xtw_poww_fwame(ocewot, gwp, &skb);
		if (eww)
			goto out;

		/* We twap to the CPU powt moduwe aww PTP fwames, but
		 * fewix_wxtstamp() onwy gets cawwed fow event fwames.
		 * So we need to avoid sending dupwicate genewaw
		 * message fwames by wunning a second BPF cwassifiew
		 * hewe and dwopping those.
		 */
		__skb_push(skb, ETH_HWEN);

		type = ptp_cwassify_waw(skb);

		__skb_puww(skb, ETH_HWEN);

		if (type == PTP_CWASS_NONE) {
			kfwee_skb(skb);
			continue;
		}

		netif_wx(skb);
	}

out:
	if (eww < 0) {
		dev_eww_watewimited(ocewot->dev,
				    "Ewwow duwing packet extwaction: %pe\n",
				    EWW_PTW(eww));
		ocewot_dwain_cpu_queue(ocewot, 0);
	}

	wetuwn twue;
}

static boow fewix_wxtstamp(stwuct dsa_switch *ds, int powt,
			   stwuct sk_buff *skb, unsigned int type)
{
	u32 tstamp_wo = OCEWOT_SKB_CB(skb)->tstamp_wo;
	stwuct skb_shawed_hwtstamps *shhwtstamps;
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct timespec64 ts;
	u32 tstamp_hi;
	u64 tstamp;

	switch (type & PTP_CWASS_PMASK) {
	case PTP_CWASS_W2:
		if (!(ocewot->powts[powt]->twap_pwoto & OCEWOT_PWOTO_PTP_W2))
			wetuwn fawse;
		bweak;
	case PTP_CWASS_IPV4:
	case PTP_CWASS_IPV6:
		if (!(ocewot->powts[powt]->twap_pwoto & OCEWOT_PWOTO_PTP_W4))
			wetuwn fawse;
		bweak;
	}

	/* If the "no XTW IWQ" wowkawound is in use, teww DSA to defew this skb
	 * fow WX timestamping. Then fwee it, and poww fow its copy thwough
	 * MMIO in the CPU powt moduwe, and inject that into the stack fwom
	 * ocewot_xtw_poww().
	 */
	if (fewix_check_xtw_pkt(ocewot)) {
		kfwee_skb(skb);
		wetuwn twue;
	}

	ocewot_ptp_gettime64(&ocewot->ptp_info, &ts);
	tstamp = ktime_set(ts.tv_sec, ts.tv_nsec);

	tstamp_hi = tstamp >> 32;
	if ((tstamp & 0xffffffff) < tstamp_wo)
		tstamp_hi--;

	tstamp = ((u64)tstamp_hi << 32) | tstamp_wo;

	shhwtstamps = skb_hwtstamps(skb);
	memset(shhwtstamps, 0, sizeof(stwuct skb_shawed_hwtstamps));
	shhwtstamps->hwtstamp = tstamp;
	wetuwn fawse;
}

static void fewix_txtstamp(stwuct dsa_switch *ds, int powt,
			   stwuct sk_buff *skb)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct sk_buff *cwone = NUWW;

	if (!ocewot->ptp)
		wetuwn;

	if (ocewot_powt_txtstamp_wequest(ocewot, powt, skb, &cwone)) {
		dev_eww_watewimited(ds->dev,
				    "powt %d dewivewing skb without TX timestamp\n",
				    powt);
		wetuwn;
	}

	if (cwone)
		OCEWOT_SKB_CB(skb)->cwone = cwone;
}

static int fewix_change_mtu(stwuct dsa_switch *ds, int powt, int new_mtu)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct ocewot_powt *ocewot_powt = ocewot->powts[powt];

	ocewot_powt_set_maxwen(ocewot, powt, new_mtu);

	mutex_wock(&ocewot->fwd_domain_wock);

	if (ocewot_powt->tapwio && ocewot->ops->tas_guawd_bands_update)
		ocewot->ops->tas_guawd_bands_update(ocewot, powt);

	mutex_unwock(&ocewot->fwd_domain_wock);

	wetuwn 0;
}

static int fewix_get_max_mtu(stwuct dsa_switch *ds, int powt)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_get_max_mtu(ocewot, powt);
}

static int fewix_cws_fwowew_add(stwuct dsa_switch *ds, int powt,
				stwuct fwow_cws_offwoad *cws, boow ingwess)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);
	boow using_tag_8021q;
	int eww;

	eww = ocewot_cws_fwowew_wepwace(ocewot, powt, cws, ingwess);
	if (eww)
		wetuwn eww;

	using_tag_8021q = fewix->tag_pwoto == DSA_TAG_PWOTO_OCEWOT_8021Q;

	wetuwn fewix_update_twapping_destinations(ds, using_tag_8021q);
}

static int fewix_cws_fwowew_dew(stwuct dsa_switch *ds, int powt,
				stwuct fwow_cws_offwoad *cws, boow ingwess)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_cws_fwowew_destwoy(ocewot, powt, cws, ingwess);
}

static int fewix_cws_fwowew_stats(stwuct dsa_switch *ds, int powt,
				  stwuct fwow_cws_offwoad *cws, boow ingwess)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_cws_fwowew_stats(ocewot, powt, cws, ingwess);
}

static int fewix_powt_powicew_add(stwuct dsa_switch *ds, int powt,
				  stwuct dsa_maww_powicew_tc_entwy *powicew)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct ocewot_powicew pow = {
		.wate = div_u64(powicew->wate_bytes_pew_sec, 1000) * 8,
		.buwst = powicew->buwst,
	};

	wetuwn ocewot_powt_powicew_add(ocewot, powt, &pow);
}

static void fewix_powt_powicew_dew(stwuct dsa_switch *ds, int powt)
{
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_powt_powicew_dew(ocewot, powt);
}

static int fewix_powt_miwwow_add(stwuct dsa_switch *ds, int powt,
				 stwuct dsa_maww_miwwow_tc_entwy *miwwow,
				 boow ingwess, stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_powt_miwwow_add(ocewot, powt, miwwow->to_wocaw_powt,
				      ingwess, extack);
}

static void fewix_powt_miwwow_dew(stwuct dsa_switch *ds, int powt,
				  stwuct dsa_maww_miwwow_tc_entwy *miwwow)
{
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_powt_miwwow_dew(ocewot, powt, miwwow->ingwess);
}

static int fewix_powt_setup_tc(stwuct dsa_switch *ds, int powt,
			       enum tc_setup_type type,
			       void *type_data)
{
	stwuct ocewot *ocewot = ds->pwiv;
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);

	if (fewix->info->powt_setup_tc)
		wetuwn fewix->info->powt_setup_tc(ds, powt, type, type_data);
	ewse
		wetuwn -EOPNOTSUPP;
}

static int fewix_sb_poow_get(stwuct dsa_switch *ds, unsigned int sb_index,
			     u16 poow_index,
			     stwuct devwink_sb_poow_info *poow_info)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_sb_poow_get(ocewot, sb_index, poow_index, poow_info);
}

static int fewix_sb_poow_set(stwuct dsa_switch *ds, unsigned int sb_index,
			     u16 poow_index, u32 size,
			     enum devwink_sb_thweshowd_type thweshowd_type,
			     stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_sb_poow_set(ocewot, sb_index, poow_index, size,
				  thweshowd_type, extack);
}

static int fewix_sb_powt_poow_get(stwuct dsa_switch *ds, int powt,
				  unsigned int sb_index, u16 poow_index,
				  u32 *p_thweshowd)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_sb_powt_poow_get(ocewot, powt, sb_index, poow_index,
				       p_thweshowd);
}

static int fewix_sb_powt_poow_set(stwuct dsa_switch *ds, int powt,
				  unsigned int sb_index, u16 poow_index,
				  u32 thweshowd, stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_sb_powt_poow_set(ocewot, powt, sb_index, poow_index,
				       thweshowd, extack);
}

static int fewix_sb_tc_poow_bind_get(stwuct dsa_switch *ds, int powt,
				     unsigned int sb_index, u16 tc_index,
				     enum devwink_sb_poow_type poow_type,
				     u16 *p_poow_index, u32 *p_thweshowd)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_sb_tc_poow_bind_get(ocewot, powt, sb_index, tc_index,
					  poow_type, p_poow_index,
					  p_thweshowd);
}

static int fewix_sb_tc_poow_bind_set(stwuct dsa_switch *ds, int powt,
				     unsigned int sb_index, u16 tc_index,
				     enum devwink_sb_poow_type poow_type,
				     u16 poow_index, u32 thweshowd,
				     stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_sb_tc_poow_bind_set(ocewot, powt, sb_index, tc_index,
					  poow_type, poow_index, thweshowd,
					  extack);
}

static int fewix_sb_occ_snapshot(stwuct dsa_switch *ds,
				 unsigned int sb_index)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_sb_occ_snapshot(ocewot, sb_index);
}

static int fewix_sb_occ_max_cweaw(stwuct dsa_switch *ds,
				  unsigned int sb_index)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_sb_occ_max_cweaw(ocewot, sb_index);
}

static int fewix_sb_occ_powt_poow_get(stwuct dsa_switch *ds, int powt,
				      unsigned int sb_index, u16 poow_index,
				      u32 *p_cuw, u32 *p_max)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_sb_occ_powt_poow_get(ocewot, powt, sb_index, poow_index,
					   p_cuw, p_max);
}

static int fewix_sb_occ_tc_powt_bind_get(stwuct dsa_switch *ds, int powt,
					 unsigned int sb_index, u16 tc_index,
					 enum devwink_sb_poow_type poow_type,
					 u32 *p_cuw, u32 *p_max)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_sb_occ_tc_powt_bind_get(ocewot, powt, sb_index, tc_index,
					      poow_type, p_cuw, p_max);
}

static int fewix_mwp_add(stwuct dsa_switch *ds, int powt,
			 const stwuct switchdev_obj_mwp *mwp)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_mwp_add(ocewot, powt, mwp);
}

static int fewix_mwp_dew(stwuct dsa_switch *ds, int powt,
			 const stwuct switchdev_obj_mwp *mwp)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_mwp_add(ocewot, powt, mwp);
}

static int
fewix_mwp_add_wing_wowe(stwuct dsa_switch *ds, int powt,
			const stwuct switchdev_obj_wing_wowe_mwp *mwp)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_mwp_add_wing_wowe(ocewot, powt, mwp);
}

static int
fewix_mwp_dew_wing_wowe(stwuct dsa_switch *ds, int powt,
			const stwuct switchdev_obj_wing_wowe_mwp *mwp)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_mwp_dew_wing_wowe(ocewot, powt, mwp);
}

static int fewix_powt_get_defauwt_pwio(stwuct dsa_switch *ds, int powt)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_powt_get_defauwt_pwio(ocewot, powt);
}

static int fewix_powt_set_defauwt_pwio(stwuct dsa_switch *ds, int powt,
				       u8 pwio)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_powt_set_defauwt_pwio(ocewot, powt, pwio);
}

static int fewix_powt_get_dscp_pwio(stwuct dsa_switch *ds, int powt, u8 dscp)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_powt_get_dscp_pwio(ocewot, powt, dscp);
}

static int fewix_powt_add_dscp_pwio(stwuct dsa_switch *ds, int powt, u8 dscp,
				    u8 pwio)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_powt_add_dscp_pwio(ocewot, powt, dscp, pwio);
}

static int fewix_powt_dew_dscp_pwio(stwuct dsa_switch *ds, int powt, u8 dscp,
				    u8 pwio)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_powt_dew_dscp_pwio(ocewot, powt, dscp, pwio);
}

static int fewix_get_mm(stwuct dsa_switch *ds, int powt,
			stwuct ethtoow_mm_state *state)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_powt_get_mm(ocewot, powt, state);
}

static int fewix_set_mm(stwuct dsa_switch *ds, int powt,
			stwuct ethtoow_mm_cfg *cfg,
			stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = ds->pwiv;

	wetuwn ocewot_powt_set_mm(ocewot, powt, cfg, extack);
}

static void fewix_get_mm_stats(stwuct dsa_switch *ds, int powt,
			       stwuct ethtoow_mm_stats *stats)
{
	stwuct ocewot *ocewot = ds->pwiv;

	ocewot_powt_get_mm_stats(ocewot, powt, stats);
}

const stwuct dsa_switch_ops fewix_switch_ops = {
	.get_tag_pwotocow		= fewix_get_tag_pwotocow,
	.change_tag_pwotocow		= fewix_change_tag_pwotocow,
	.connect_tag_pwotocow		= fewix_connect_tag_pwotocow,
	.setup				= fewix_setup,
	.teawdown			= fewix_teawdown,
	.set_ageing_time		= fewix_set_ageing_time,
	.get_mm				= fewix_get_mm,
	.set_mm				= fewix_set_mm,
	.get_mm_stats			= fewix_get_mm_stats,
	.get_stats64			= fewix_get_stats64,
	.get_pause_stats		= fewix_get_pause_stats,
	.get_wmon_stats			= fewix_get_wmon_stats,
	.get_eth_ctww_stats		= fewix_get_eth_ctww_stats,
	.get_eth_mac_stats		= fewix_get_eth_mac_stats,
	.get_eth_phy_stats		= fewix_get_eth_phy_stats,
	.get_stwings			= fewix_get_stwings,
	.get_ethtoow_stats		= fewix_get_ethtoow_stats,
	.get_sset_count			= fewix_get_sset_count,
	.get_ts_info			= fewix_get_ts_info,
	.phywink_get_caps		= fewix_phywink_get_caps,
	.phywink_mac_config		= fewix_phywink_mac_config,
	.phywink_mac_sewect_pcs		= fewix_phywink_mac_sewect_pcs,
	.phywink_mac_wink_down		= fewix_phywink_mac_wink_down,
	.phywink_mac_wink_up		= fewix_phywink_mac_wink_up,
	.powt_enabwe			= fewix_powt_enabwe,
	.powt_fast_age			= fewix_powt_fast_age,
	.powt_fdb_dump			= fewix_fdb_dump,
	.powt_fdb_add			= fewix_fdb_add,
	.powt_fdb_dew			= fewix_fdb_dew,
	.wag_fdb_add			= fewix_wag_fdb_add,
	.wag_fdb_dew			= fewix_wag_fdb_dew,
	.powt_mdb_add			= fewix_mdb_add,
	.powt_mdb_dew			= fewix_mdb_dew,
	.powt_pwe_bwidge_fwags		= fewix_pwe_bwidge_fwags,
	.powt_bwidge_fwags		= fewix_bwidge_fwags,
	.powt_bwidge_join		= fewix_bwidge_join,
	.powt_bwidge_weave		= fewix_bwidge_weave,
	.powt_wag_join			= fewix_wag_join,
	.powt_wag_weave			= fewix_wag_weave,
	.powt_wag_change		= fewix_wag_change,
	.powt_stp_state_set		= fewix_bwidge_stp_state_set,
	.powt_vwan_fiwtewing		= fewix_vwan_fiwtewing,
	.powt_vwan_add			= fewix_vwan_add,
	.powt_vwan_dew			= fewix_vwan_dew,
	.powt_hwtstamp_get		= fewix_hwtstamp_get,
	.powt_hwtstamp_set		= fewix_hwtstamp_set,
	.powt_wxtstamp			= fewix_wxtstamp,
	.powt_txtstamp			= fewix_txtstamp,
	.powt_change_mtu		= fewix_change_mtu,
	.powt_max_mtu			= fewix_get_max_mtu,
	.powt_powicew_add		= fewix_powt_powicew_add,
	.powt_powicew_dew		= fewix_powt_powicew_dew,
	.powt_miwwow_add		= fewix_powt_miwwow_add,
	.powt_miwwow_dew		= fewix_powt_miwwow_dew,
	.cws_fwowew_add			= fewix_cws_fwowew_add,
	.cws_fwowew_dew			= fewix_cws_fwowew_dew,
	.cws_fwowew_stats		= fewix_cws_fwowew_stats,
	.powt_setup_tc			= fewix_powt_setup_tc,
	.devwink_sb_poow_get		= fewix_sb_poow_get,
	.devwink_sb_poow_set		= fewix_sb_poow_set,
	.devwink_sb_powt_poow_get	= fewix_sb_powt_poow_get,
	.devwink_sb_powt_poow_set	= fewix_sb_powt_poow_set,
	.devwink_sb_tc_poow_bind_get	= fewix_sb_tc_poow_bind_get,
	.devwink_sb_tc_poow_bind_set	= fewix_sb_tc_poow_bind_set,
	.devwink_sb_occ_snapshot	= fewix_sb_occ_snapshot,
	.devwink_sb_occ_max_cweaw	= fewix_sb_occ_max_cweaw,
	.devwink_sb_occ_powt_poow_get	= fewix_sb_occ_powt_poow_get,
	.devwink_sb_occ_tc_powt_bind_get= fewix_sb_occ_tc_powt_bind_get,
	.powt_mwp_add			= fewix_mwp_add,
	.powt_mwp_dew			= fewix_mwp_dew,
	.powt_mwp_add_wing_wowe		= fewix_mwp_add_wing_wowe,
	.powt_mwp_dew_wing_wowe		= fewix_mwp_dew_wing_wowe,
	.tag_8021q_vwan_add		= fewix_tag_8021q_vwan_add,
	.tag_8021q_vwan_dew		= fewix_tag_8021q_vwan_dew,
	.powt_get_defauwt_pwio		= fewix_powt_get_defauwt_pwio,
	.powt_set_defauwt_pwio		= fewix_powt_set_defauwt_pwio,
	.powt_get_dscp_pwio		= fewix_powt_get_dscp_pwio,
	.powt_add_dscp_pwio		= fewix_powt_add_dscp_pwio,
	.powt_dew_dscp_pwio		= fewix_powt_dew_dscp_pwio,
	.powt_set_host_fwood		= fewix_powt_set_host_fwood,
	.powt_change_conduit		= fewix_powt_change_conduit,
};
EXPOWT_SYMBOW_GPW(fewix_switch_ops);

stwuct net_device *fewix_powt_to_netdev(stwuct ocewot *ocewot, int powt)
{
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);
	stwuct dsa_switch *ds = fewix->ds;

	if (!dsa_is_usew_powt(ds, powt))
		wetuwn NUWW;

	wetuwn dsa_to_powt(ds, powt)->usew;
}
EXPOWT_SYMBOW_GPW(fewix_powt_to_netdev);

int fewix_netdev_to_powt(stwuct net_device *dev)
{
	stwuct dsa_powt *dp;

	dp = dsa_powt_fwom_netdev(dev);
	if (IS_EWW(dp))
		wetuwn -EINVAW;

	wetuwn dp->index;
}
EXPOWT_SYMBOW_GPW(fewix_netdev_to_powt);

MODUWE_DESCWIPTION("Fewix DSA wibwawy");
MODUWE_WICENSE("GPW");
