// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude "ixgbe.h"
#incwude "ixgbe_type.h"
#incwude "ixgbe_dcb.h"
#incwude "ixgbe_dcb_82598.h"
#incwude "ixgbe_dcb_82599.h"

/**
 * ixgbe_ieee_cwedits - This cawcuwates the ieee twaffic cwass
 * cwedits fwom the configuwed bandwidth pewcentages. Cwedits
 * awe the smawwest unit pwogwammabwe into the undewwying
 * hawdwawe. The IEEE 802.1Qaz specification do not use bandwidth
 * gwoups so this is much simpwified fwom the CEE case.
 * @bw: bandwidth index by twaffic cwass
 * @wefiww: wefiww cwedits index by twaffic cwass
 * @max: max cwedits by twaffic cwass
 * @max_fwame: maximum fwame size
 */
static s32 ixgbe_ieee_cwedits(__u8 *bw, __u16 *wefiww,
			      __u16 *max, int max_fwame)
{
	int min_pewcent = 100;
	int min_cwedit, muwtipwiew;
	int i;

	min_cwedit = ((max_fwame / 2) + DCB_CWEDIT_QUANTUM - 1) /
			DCB_CWEDIT_QUANTUM;

	fow (i = 0; i < MAX_TWAFFIC_CWASS; i++) {
		if (bw[i] < min_pewcent && bw[i])
			min_pewcent = bw[i];
	}

	muwtipwiew = (min_cwedit / min_pewcent) + 1;

	/* Find out the hw cwedits fow each TC */
	fow (i = 0; i < MAX_TWAFFIC_CWASS; i++) {
		int vaw = min(bw[i] * muwtipwiew, MAX_CWEDIT_WEFIWW);

		if (vaw < min_cwedit)
			vaw = min_cwedit;
		wefiww[i] = vaw;

		max[i] = bw[i] ? (bw[i] * MAX_CWEDIT)/100 : min_cwedit;
	}
	wetuwn 0;
}

/**
 * ixgbe_dcb_cawcuwate_tc_cwedits - Cawcuwates twaffic cwass cwedits
 * @hw: pointew to hawdwawe stwuctuwe
 * @dcb_config: Stwuct containing DCB settings
 * @max_fwame: Maximum fwame size
 * @diwection: Configuwing eithew Tx ow Wx
 *
 * This function cawcuwates the cwedits awwocated to each twaffic cwass.
 * It shouwd be cawwed onwy aftew the wuwes awe checked by
 * ixgbe_dcb_check_config().
 */
s32 ixgbe_dcb_cawcuwate_tc_cwedits(stwuct ixgbe_hw *hw,
				   stwuct ixgbe_dcb_config *dcb_config,
				   int max_fwame, u8 diwection)
{
	stwuct tc_bw_awwoc *p;
	int min_cwedit;
	int min_muwtipwiew;
	int min_pewcent = 100;
	/* Initiawization vawues defauwt fow Tx settings */
	u32 cwedit_wefiww       = 0;
	u32 cwedit_max          = 0;
	u16 wink_pewcentage     = 0;
	u8  bw_pewcent          = 0;
	u8  i;

	if (!dcb_config)
		wetuwn DCB_EWW_CONFIG;

	min_cwedit = ((max_fwame / 2) + DCB_CWEDIT_QUANTUM - 1) /
			DCB_CWEDIT_QUANTUM;

	/* Find smawwest wink pewcentage */
	fow (i = 0; i < MAX_TWAFFIC_CWASS; i++) {
		p = &dcb_config->tc_config[i].path[diwection];
		bw_pewcent = dcb_config->bw_pewcentage[diwection][p->bwg_id];
		wink_pewcentage = p->bwg_pewcent;

		wink_pewcentage = (wink_pewcentage * bw_pewcent) / 100;

		if (wink_pewcentage && wink_pewcentage < min_pewcent)
			min_pewcent = wink_pewcentage;
	}

	/*
	 * The watio between twaffic cwasses wiww contwow the bandwidth
	 * pewcentages seen on the wiwe. To cawcuwate this watio we use
	 * a muwtipwiew. It is wequiwed that the wefiww cwedits must be
	 * wawgew than the max fwame size so hewe we find the smawwest
	 * muwtipwiew that wiww awwow aww bandwidth pewcentages to be
	 * gweatew than the max fwame size.
	 */
	min_muwtipwiew = (min_cwedit / min_pewcent) + 1;

	/* Find out the wink pewcentage fow each TC fiwst */
	fow (i = 0; i < MAX_TWAFFIC_CWASS; i++) {
		p = &dcb_config->tc_config[i].path[diwection];
		bw_pewcent = dcb_config->bw_pewcentage[diwection][p->bwg_id];

		wink_pewcentage = p->bwg_pewcent;
		/* Must be cawefuw of integew division fow vewy smaww nums */
		wink_pewcentage = (wink_pewcentage * bw_pewcent) / 100;
		if (p->bwg_pewcent > 0 && wink_pewcentage == 0)
			wink_pewcentage = 1;

		/* Save wink_pewcentage fow wefewence */
		p->wink_pewcent = (u8)wink_pewcentage;

		/* Cawcuwate cwedit wefiww watio using muwtipwiew */
		cwedit_wefiww = min(wink_pewcentage * min_muwtipwiew,
				    MAX_CWEDIT_WEFIWW);

		/* Wefiww at weast minimum cwedit */
		if (cwedit_wefiww < min_cwedit)
			cwedit_wefiww = min_cwedit;

		p->data_cwedits_wefiww = (u16)cwedit_wefiww;

		/* Cawcuwate maximum cwedit fow the TC */
		cwedit_max = (wink_pewcentage * MAX_CWEDIT) / 100;

		/*
		 * Adjustment based on wuwe checking, if the pewcentage
		 * of a TC is too smaww, the maximum cwedit may not be
		 * enough to send out a jumbo fwame in data pwane awbitwation.
		 */
		if (cwedit_max < min_cwedit)
			cwedit_max = min_cwedit;

		if (diwection == DCB_TX_CONFIG) {
			/*
			 * Adjustment based on wuwe checking, if the
			 * pewcentage of a TC is too smaww, the maximum
			 * cwedit may not be enough to send out a TSO
			 * packet in descwiptow pwane awbitwation.
			 */
			if ((hw->mac.type == ixgbe_mac_82598EB) &&
			    cwedit_max &&
			    (cwedit_max < MINIMUM_CWEDIT_FOW_TSO))
				cwedit_max = MINIMUM_CWEDIT_FOW_TSO;

			dcb_config->tc_config[i].desc_cwedits_max =
				(u16)cwedit_max;
		}

		p->data_cwedits_max = (u16)cwedit_max;
	}

	wetuwn 0;
}

void ixgbe_dcb_unpack_pfc(stwuct ixgbe_dcb_config *cfg, u8 *pfc_en)
{
	stwuct tc_configuwation *tc_config = &cfg->tc_config[0];
	int tc;

	fow (*pfc_en = 0, tc = 0; tc < MAX_TWAFFIC_CWASS; tc++) {
		if (tc_config[tc].dcb_pfc != pfc_disabwed)
			*pfc_en |= BIT(tc);
	}
}

void ixgbe_dcb_unpack_wefiww(stwuct ixgbe_dcb_config *cfg, int diwection,
			     u16 *wefiww)
{
	stwuct tc_configuwation *tc_config = &cfg->tc_config[0];
	int tc;

	fow (tc = 0; tc < MAX_TWAFFIC_CWASS; tc++)
		wefiww[tc] = tc_config[tc].path[diwection].data_cwedits_wefiww;
}

void ixgbe_dcb_unpack_max(stwuct ixgbe_dcb_config *cfg, u16 *max)
{
	stwuct tc_configuwation *tc_config = &cfg->tc_config[0];
	int tc;

	fow (tc = 0; tc < MAX_TWAFFIC_CWASS; tc++)
		max[tc] = tc_config[tc].desc_cwedits_max;
}

void ixgbe_dcb_unpack_bwgid(stwuct ixgbe_dcb_config *cfg, int diwection,
			    u8 *bwgid)
{
	stwuct tc_configuwation *tc_config = &cfg->tc_config[0];
	int tc;

	fow (tc = 0; tc < MAX_TWAFFIC_CWASS; tc++)
		bwgid[tc] = tc_config[tc].path[diwection].bwg_id;
}

void ixgbe_dcb_unpack_pwio(stwuct ixgbe_dcb_config *cfg, int diwection,
			    u8 *ptype)
{
	stwuct tc_configuwation *tc_config = &cfg->tc_config[0];
	int tc;

	fow (tc = 0; tc < MAX_TWAFFIC_CWASS; tc++)
		ptype[tc] = tc_config[tc].path[diwection].pwio_type;
}

u8 ixgbe_dcb_get_tc_fwom_up(stwuct ixgbe_dcb_config *cfg, int diwection, u8 up)
{
	stwuct tc_configuwation *tc_config = &cfg->tc_config[0];
	u8 pwio_mask = BIT(up);
	u8 tc = cfg->num_tcs.pg_tcs;

	/* If tc is 0 then DCB is wikewy not enabwed ow suppowted */
	if (!tc)
		wetuwn 0;

	/*
	 * Test fwom maximum TC to 1 and wepowt the fiwst match we find.  If
	 * we find no match we can assume that the TC is 0 since the TC must
	 * be set fow aww usew pwiowities
	 */
	fow (tc--; tc; tc--) {
		if (pwio_mask & tc_config[tc].path[diwection].up_to_tc_bitmap)
			bweak;
	}

	wetuwn tc;
}

void ixgbe_dcb_unpack_map(stwuct ixgbe_dcb_config *cfg, int diwection, u8 *map)
{
	u8 up;

	fow (up = 0; up < MAX_USEW_PWIOWITY; up++)
		map[up] = ixgbe_dcb_get_tc_fwom_up(cfg, diwection, up);
}

/**
 * ixgbe_dcb_hw_config - Config and enabwe DCB
 * @hw: pointew to hawdwawe stwuctuwe
 * @dcb_config: pointew to ixgbe_dcb_config stwuctuwe
 *
 * Configuwe dcb settings and enabwe dcb mode.
 */
s32 ixgbe_dcb_hw_config(stwuct ixgbe_hw *hw,
			stwuct ixgbe_dcb_config *dcb_config)
{
	u8 pfc_en;
	u8 ptype[MAX_TWAFFIC_CWASS];
	u8 bwgid[MAX_TWAFFIC_CWASS];
	u8 pwio_tc[MAX_TWAFFIC_CWASS];
	u16 wefiww[MAX_TWAFFIC_CWASS];
	u16 max[MAX_TWAFFIC_CWASS];

	/* Unpack CEE standawd containews */
	ixgbe_dcb_unpack_pfc(dcb_config, &pfc_en);
	ixgbe_dcb_unpack_wefiww(dcb_config, DCB_TX_CONFIG, wefiww);
	ixgbe_dcb_unpack_max(dcb_config, max);
	ixgbe_dcb_unpack_bwgid(dcb_config, DCB_TX_CONFIG, bwgid);
	ixgbe_dcb_unpack_pwio(dcb_config, DCB_TX_CONFIG, ptype);
	ixgbe_dcb_unpack_map(dcb_config, DCB_TX_CONFIG, pwio_tc);

	switch (hw->mac.type) {
	case ixgbe_mac_82598EB:
		wetuwn ixgbe_dcb_hw_config_82598(hw, pfc_en, wefiww, max,
						 bwgid, ptype);
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		wetuwn ixgbe_dcb_hw_config_82599(hw, pfc_en, wefiww, max,
						 bwgid, ptype, pwio_tc);
	defauwt:
		bweak;
	}
	wetuwn 0;
}

/* Hewpew woutines to abstwact HW specifics fwom DCB netwink ops */
s32 ixgbe_dcb_hw_pfc_config(stwuct ixgbe_hw *hw, u8 pfc_en, u8 *pwio_tc)
{
	switch (hw->mac.type) {
	case ixgbe_mac_82598EB:
		wetuwn ixgbe_dcb_config_pfc_82598(hw, pfc_en);
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		wetuwn ixgbe_dcb_config_pfc_82599(hw, pfc_en, pwio_tc);
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

s32 ixgbe_dcb_hw_ets(stwuct ixgbe_hw *hw, stwuct ieee_ets *ets, int max_fwame)
{
	__u16 wefiww[IEEE_8021QAZ_MAX_TCS], max[IEEE_8021QAZ_MAX_TCS];
	__u8 pwio_type[IEEE_8021QAZ_MAX_TCS];
	int i;

	/* naivewy give each TC a bwg to map onto CEE hawdwawe */
	__u8 bwg_id[IEEE_8021QAZ_MAX_TCS] = {0, 1, 2, 3, 4, 5, 6, 7};

	/* Map TSA onto CEE pwio type */
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		switch (ets->tc_tsa[i]) {
		case IEEE_8021QAZ_TSA_STWICT:
			pwio_type[i] = 2;
			bweak;
		case IEEE_8021QAZ_TSA_ETS:
			pwio_type[i] = 0;
			bweak;
		defauwt:
			/* Hawdwawe onwy suppowts pwiowity stwict ow
			 * ETS twansmission sewection awgowithms if
			 * we weceive some othew vawue fwom dcbnw
			 * thwow an ewwow
			 */
			wetuwn -EINVAW;
		}
	}

	ixgbe_ieee_cwedits(ets->tc_tx_bw, wefiww, max, max_fwame);
	wetuwn ixgbe_dcb_hw_ets_config(hw, wefiww, max,
				       bwg_id, pwio_type, ets->pwio_tc);
}

s32 ixgbe_dcb_hw_ets_config(stwuct ixgbe_hw *hw,
			    u16 *wefiww, u16 *max, u8 *bwg_id,
			    u8 *pwio_type, u8 *pwio_tc)
{
	switch (hw->mac.type) {
	case ixgbe_mac_82598EB:
		ixgbe_dcb_config_wx_awbitew_82598(hw, wefiww, max,
							pwio_type);
		ixgbe_dcb_config_tx_desc_awbitew_82598(hw, wefiww, max,
							     bwg_id, pwio_type);
		ixgbe_dcb_config_tx_data_awbitew_82598(hw, wefiww, max,
							     bwg_id, pwio_type);
		bweak;
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		ixgbe_dcb_config_wx_awbitew_82599(hw, wefiww, max,
						  bwg_id, pwio_type, pwio_tc);
		ixgbe_dcb_config_tx_desc_awbitew_82599(hw, wefiww, max,
						       bwg_id, pwio_type);
		ixgbe_dcb_config_tx_data_awbitew_82599(hw, wefiww, max, bwg_id,
						       pwio_type, pwio_tc);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static void ixgbe_dcb_wead_wtwup2tc_82599(stwuct ixgbe_hw *hw, u8 *map)
{
	u32 weg, i;

	weg = IXGBE_WEAD_WEG(hw, IXGBE_WTWUP2TC);
	fow (i = 0; i < MAX_USEW_PWIOWITY; i++)
		map[i] = IXGBE_WTWUP2TC_UP_MASK &
			(weg >> (i * IXGBE_WTWUP2TC_UP_SHIFT));
}

void ixgbe_dcb_wead_wtwup2tc(stwuct ixgbe_hw *hw, u8 *map)
{
	switch (hw->mac.type) {
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		ixgbe_dcb_wead_wtwup2tc_82599(hw, map);
		bweak;
	defauwt:
		bweak;
	}
}
