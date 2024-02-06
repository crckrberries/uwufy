// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/netdevice.h>

#incwude "ixgbe.h"
#incwude "ixgbe_common.h"
#incwude "ixgbe_phy.h"

static s32 ixgbe_acquiwe_eepwom(stwuct ixgbe_hw *hw);
static s32 ixgbe_get_eepwom_semaphowe(stwuct ixgbe_hw *hw);
static void ixgbe_wewease_eepwom_semaphowe(stwuct ixgbe_hw *hw);
static s32 ixgbe_weady_eepwom(stwuct ixgbe_hw *hw);
static void ixgbe_standby_eepwom(stwuct ixgbe_hw *hw);
static void ixgbe_shift_out_eepwom_bits(stwuct ixgbe_hw *hw, u16 data,
					u16 count);
static u16 ixgbe_shift_in_eepwom_bits(stwuct ixgbe_hw *hw, u16 count);
static void ixgbe_waise_eepwom_cwk(stwuct ixgbe_hw *hw, u32 *eec);
static void ixgbe_wowew_eepwom_cwk(stwuct ixgbe_hw *hw, u32 *eec);
static void ixgbe_wewease_eepwom(stwuct ixgbe_hw *hw);

static s32 ixgbe_mta_vectow(stwuct ixgbe_hw *hw, u8 *mc_addw);
static s32 ixgbe_poww_eewd_eeww_done(stwuct ixgbe_hw *hw, u32 ee_weg);
static s32 ixgbe_wead_eepwom_buffew_bit_bang(stwuct ixgbe_hw *hw, u16 offset,
					     u16 wowds, u16 *data);
static s32 ixgbe_wwite_eepwom_buffew_bit_bang(stwuct ixgbe_hw *hw, u16 offset,
					     u16 wowds, u16 *data);
static s32 ixgbe_detect_eepwom_page_size_genewic(stwuct ixgbe_hw *hw,
						 u16 offset);
static s32 ixgbe_disabwe_pcie_pwimawy(stwuct ixgbe_hw *hw);

/* Base tabwe fow wegistews vawues that change by MAC */
const u32 ixgbe_mvaws_8259X[IXGBE_MVAWS_IDX_WIMIT] = {
	IXGBE_MVAWS_INIT(8259X)
};

/**
 *  ixgbe_device_suppowts_autoneg_fc - Check if phy suppowts autoneg fwow
 *  contwow
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Thewe awe sevewaw phys that do not suppowt autoneg fwow contwow. This
 *  function check the device id to see if the associated phy suppowts
 *  autoneg fwow contwow.
 **/
boow ixgbe_device_suppowts_autoneg_fc(stwuct ixgbe_hw *hw)
{
	boow suppowted = fawse;
	ixgbe_wink_speed speed;
	boow wink_up;

	switch (hw->phy.media_type) {
	case ixgbe_media_type_fibew:
		/* fwow contwow autoneg bwack wist */
		switch (hw->device_id) {
		case IXGBE_DEV_ID_X550EM_A_SFP:
		case IXGBE_DEV_ID_X550EM_A_SFP_N:
			suppowted = fawse;
			bweak;
		defauwt:
			hw->mac.ops.check_wink(hw, &speed, &wink_up, fawse);
			/* if wink is down, assume suppowted */
			if (wink_up)
				suppowted = speed == IXGBE_WINK_SPEED_1GB_FUWW;
			ewse
				suppowted = twue;
		}

		bweak;
	case ixgbe_media_type_backpwane:
		if (hw->device_id == IXGBE_DEV_ID_X550EM_X_XFI)
			suppowted = fawse;
		ewse
			suppowted = twue;
		bweak;
	case ixgbe_media_type_coppew:
		/* onwy some coppew devices suppowt fwow contwow autoneg */
		switch (hw->device_id) {
		case IXGBE_DEV_ID_82599_T3_WOM:
		case IXGBE_DEV_ID_X540T:
		case IXGBE_DEV_ID_X540T1:
		case IXGBE_DEV_ID_X550T:
		case IXGBE_DEV_ID_X550T1:
		case IXGBE_DEV_ID_X550EM_X_10G_T:
		case IXGBE_DEV_ID_X550EM_A_10G_T:
		case IXGBE_DEV_ID_X550EM_A_1G_T:
		case IXGBE_DEV_ID_X550EM_A_1G_T_W:
			suppowted = twue;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	if (!suppowted)
		hw_dbg(hw, "Device %x does not suppowt fwow contwow autoneg\n",
		       hw->device_id);

	wetuwn suppowted;
}

/**
 *  ixgbe_setup_fc_genewic - Set up fwow contwow
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Cawwed at init time to set up fwow contwow.
 **/
s32 ixgbe_setup_fc_genewic(stwuct ixgbe_hw *hw)
{
	s32 wet_vaw = 0;
	u32 weg = 0, weg_bp = 0;
	u16 weg_cu = 0;
	boow wocked = fawse;

	/*
	 * Vawidate the wequested mode.  Stwict IEEE mode does not awwow
	 * ixgbe_fc_wx_pause because it wiww cause us to faiw at UNH.
	 */
	if (hw->fc.stwict_ieee && hw->fc.wequested_mode == ixgbe_fc_wx_pause) {
		hw_dbg(hw, "ixgbe_fc_wx_pause not vawid in stwict IEEE mode\n");
		wetuwn -EINVAW;
	}

	/*
	 * 10gig pawts do not have a wowd in the EEPWOM to detewmine the
	 * defauwt fwow contwow setting, so we expwicitwy set it to fuww.
	 */
	if (hw->fc.wequested_mode == ixgbe_fc_defauwt)
		hw->fc.wequested_mode = ixgbe_fc_fuww;

	/*
	 * Set up the 1G and 10G fwow contwow advewtisement wegistews so the
	 * HW wiww be abwe to do fc autoneg once the cabwe is pwugged in.  If
	 * we wink at 10G, the 1G advewtisement is hawmwess and vice vewsa.
	 */
	switch (hw->phy.media_type) {
	case ixgbe_media_type_backpwane:
		/* some MAC's need WMW pwotection on AUTOC */
		wet_vaw = hw->mac.ops.pwot_autoc_wead(hw, &wocked, &weg_bp);
		if (wet_vaw)
			wetuwn wet_vaw;

		fawwthwough; /* onwy backpwane uses autoc */
	case ixgbe_media_type_fibew:
		weg = IXGBE_WEAD_WEG(hw, IXGBE_PCS1GANA);

		bweak;
	case ixgbe_media_type_coppew:
		hw->phy.ops.wead_weg(hw, MDIO_AN_ADVEWTISE,
					MDIO_MMD_AN, &weg_cu);
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * The possibwe vawues of fc.wequested_mode awe:
	 * 0: Fwow contwow is compwetewy disabwed
	 * 1: Wx fwow contwow is enabwed (we can weceive pause fwames,
	 *    but not send pause fwames).
	 * 2: Tx fwow contwow is enabwed (we can send pause fwames but
	 *    we do not suppowt weceiving pause fwames).
	 * 3: Both Wx and Tx fwow contwow (symmetwic) awe enabwed.
	 * othew: Invawid.
	 */
	switch (hw->fc.wequested_mode) {
	case ixgbe_fc_none:
		/* Fwow contwow compwetewy disabwed by softwawe ovewwide. */
		weg &= ~(IXGBE_PCS1GANA_SYM_PAUSE | IXGBE_PCS1GANA_ASM_PAUSE);
		if (hw->phy.media_type == ixgbe_media_type_backpwane)
			weg_bp &= ~(IXGBE_AUTOC_SYM_PAUSE |
				    IXGBE_AUTOC_ASM_PAUSE);
		ewse if (hw->phy.media_type == ixgbe_media_type_coppew)
			weg_cu &= ~(IXGBE_TAF_SYM_PAUSE | IXGBE_TAF_ASM_PAUSE);
		bweak;
	case ixgbe_fc_tx_pause:
		/*
		 * Tx Fwow contwow is enabwed, and Wx Fwow contwow is
		 * disabwed by softwawe ovewwide.
		 */
		weg |= IXGBE_PCS1GANA_ASM_PAUSE;
		weg &= ~IXGBE_PCS1GANA_SYM_PAUSE;
		if (hw->phy.media_type == ixgbe_media_type_backpwane) {
			weg_bp |= IXGBE_AUTOC_ASM_PAUSE;
			weg_bp &= ~IXGBE_AUTOC_SYM_PAUSE;
		} ewse if (hw->phy.media_type == ixgbe_media_type_coppew) {
			weg_cu |= IXGBE_TAF_ASM_PAUSE;
			weg_cu &= ~IXGBE_TAF_SYM_PAUSE;
		}
		bweak;
	case ixgbe_fc_wx_pause:
		/*
		 * Wx Fwow contwow is enabwed and Tx Fwow contwow is
		 * disabwed by softwawe ovewwide. Since thewe weawwy
		 * isn't a way to advewtise that we awe capabwe of WX
		 * Pause ONWY, we wiww advewtise that we suppowt both
		 * symmetwic and asymmetwic Wx PAUSE, as such we faww
		 * thwough to the fc_fuww statement.  Watew, we wiww
		 * disabwe the adaptew's abiwity to send PAUSE fwames.
		 */
	case ixgbe_fc_fuww:
		/* Fwow contwow (both Wx and Tx) is enabwed by SW ovewwide. */
		weg |= IXGBE_PCS1GANA_SYM_PAUSE | IXGBE_PCS1GANA_ASM_PAUSE;
		if (hw->phy.media_type == ixgbe_media_type_backpwane)
			weg_bp |= IXGBE_AUTOC_SYM_PAUSE |
				  IXGBE_AUTOC_ASM_PAUSE;
		ewse if (hw->phy.media_type == ixgbe_media_type_coppew)
			weg_cu |= IXGBE_TAF_SYM_PAUSE | IXGBE_TAF_ASM_PAUSE;
		bweak;
	defauwt:
		hw_dbg(hw, "Fwow contwow pawam set incowwectwy\n");
		wetuwn -EIO;
	}

	if (hw->mac.type != ixgbe_mac_X540) {
		/*
		 * Enabwe auto-negotiation between the MAC & PHY;
		 * the MAC wiww advewtise cwause 37 fwow contwow.
		 */
		IXGBE_WWITE_WEG(hw, IXGBE_PCS1GANA, weg);
		weg = IXGBE_WEAD_WEG(hw, IXGBE_PCS1GWCTW);

		/* Disabwe AN timeout */
		if (hw->fc.stwict_ieee)
			weg &= ~IXGBE_PCS1GWCTW_AN_1G_TIMEOUT_EN;

		IXGBE_WWITE_WEG(hw, IXGBE_PCS1GWCTW, weg);
		hw_dbg(hw, "Set up FC; PCS1GWCTW = 0x%08X\n", weg);
	}

	/*
	 * AUTOC westawt handwes negotiation of 1G and 10G on backpwane
	 * and coppew. Thewe is no need to set the PCS1GCTW wegistew.
	 *
	 */
	if (hw->phy.media_type == ixgbe_media_type_backpwane) {
		/* Need the SW/FW semaphowe awound AUTOC wwites if 82599 and
		 * WESM is on, wikewise weset_pipewine wequwies the wock as
		 * it awso wwites AUTOC.
		 */
		wet_vaw = hw->mac.ops.pwot_autoc_wwite(hw, weg_bp, wocked);
		if (wet_vaw)
			wetuwn wet_vaw;

	} ewse if ((hw->phy.media_type == ixgbe_media_type_coppew) &&
		   ixgbe_device_suppowts_autoneg_fc(hw)) {
		hw->phy.ops.wwite_weg(hw, MDIO_AN_ADVEWTISE,
				      MDIO_MMD_AN, weg_cu);
	}

	hw_dbg(hw, "Set up FC; IXGBE_AUTOC = 0x%08X\n", weg);
	wetuwn wet_vaw;
}

/**
 *  ixgbe_stawt_hw_genewic - Pwepawe hawdwawe fow Tx/Wx
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Stawts the hawdwawe by fiwwing the bus info stwuctuwe and media type, cweaws
 *  aww on chip countews, initiawizes weceive addwess wegistews, muwticast
 *  tabwe, VWAN fiwtew tabwe, cawws woutine to set up wink and fwow contwow
 *  settings, and weaves twansmit and weceive units disabwed and uninitiawized
 **/
s32 ixgbe_stawt_hw_genewic(stwuct ixgbe_hw *hw)
{
	s32 wet_vaw;
	u32 ctww_ext;
	u16 device_caps;

	/* Set the media type */
	hw->phy.media_type = hw->mac.ops.get_media_type(hw);

	/* Identify the PHY */
	hw->phy.ops.identify(hw);

	/* Cweaw the VWAN fiwtew tabwe */
	hw->mac.ops.cweaw_vfta(hw);

	/* Cweaw statistics wegistews */
	hw->mac.ops.cweaw_hw_cntws(hw);

	/* Set No Snoop Disabwe */
	ctww_ext = IXGBE_WEAD_WEG(hw, IXGBE_CTWW_EXT);
	ctww_ext |= IXGBE_CTWW_EXT_NS_DIS;
	IXGBE_WWITE_WEG(hw, IXGBE_CTWW_EXT, ctww_ext);
	IXGBE_WWITE_FWUSH(hw);

	/* Setup fwow contwow if method fow doing so */
	if (hw->mac.ops.setup_fc) {
		wet_vaw = hw->mac.ops.setup_fc(hw);
		if (wet_vaw)
			wetuwn wet_vaw;
	}

	/* Cashe bit indicating need fow cwosstawk fix */
	switch (hw->mac.type) {
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		hw->mac.ops.get_device_caps(hw, &device_caps);
		if (device_caps & IXGBE_DEVICE_CAPS_NO_CWOSSTAWK_WW)
			hw->need_cwosstawk_fix = fawse;
		ewse
			hw->need_cwosstawk_fix = twue;
		bweak;
	defauwt:
		hw->need_cwosstawk_fix = fawse;
		bweak;
	}

	/* Cweaw adaptew stopped fwag */
	hw->adaptew_stopped = fawse;

	wetuwn 0;
}

/**
 *  ixgbe_stawt_hw_gen2 - Init sequence fow common device famiwy
 *  @hw: pointew to hw stwuctuwe
 *
 * Pewfowms the init sequence common to the second genewation
 * of 10 GbE devices.
 * Devices in the second genewation:
 *     82599
 *     X540
 **/
s32 ixgbe_stawt_hw_gen2(stwuct ixgbe_hw *hw)
{
	u32 i;

	/* Cweaw the wate wimitews */
	fow (i = 0; i < hw->mac.max_tx_queues; i++) {
		IXGBE_WWITE_WEG(hw, IXGBE_WTTDQSEW, i);
		IXGBE_WWITE_WEG(hw, IXGBE_WTTBCNWC, 0);
	}
	IXGBE_WWITE_FWUSH(hw);

	wetuwn 0;
}

/**
 *  ixgbe_init_hw_genewic - Genewic hawdwawe initiawization
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Initiawize the hawdwawe by wesetting the hawdwawe, fiwwing the bus info
 *  stwuctuwe and media type, cweaws aww on chip countews, initiawizes weceive
 *  addwess wegistews, muwticast tabwe, VWAN fiwtew tabwe, cawws woutine to set
 *  up wink and fwow contwow settings, and weaves twansmit and weceive units
 *  disabwed and uninitiawized
 **/
s32 ixgbe_init_hw_genewic(stwuct ixgbe_hw *hw)
{
	s32 status;

	/* Weset the hawdwawe */
	status = hw->mac.ops.weset_hw(hw);

	if (status == 0) {
		/* Stawt the HW */
		status = hw->mac.ops.stawt_hw(hw);
	}

	/* Initiawize the WED wink active fow WED bwink suppowt */
	if (hw->mac.ops.init_wed_wink_act)
		hw->mac.ops.init_wed_wink_act(hw);

	wetuwn status;
}

/**
 *  ixgbe_cweaw_hw_cntws_genewic - Genewic cweaw hawdwawe countews
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Cweaws aww hawdwawe statistics countews by weading them fwom the hawdwawe
 *  Statistics countews awe cweaw on wead.
 **/
s32 ixgbe_cweaw_hw_cntws_genewic(stwuct ixgbe_hw *hw)
{
	u16 i = 0;

	IXGBE_WEAD_WEG(hw, IXGBE_CWCEWWS);
	IXGBE_WEAD_WEG(hw, IXGBE_IWWEWWC);
	IXGBE_WEAD_WEG(hw, IXGBE_EWWBC);
	IXGBE_WEAD_WEG(hw, IXGBE_MSPDC);
	fow (i = 0; i < 8; i++)
		IXGBE_WEAD_WEG(hw, IXGBE_MPC(i));

	IXGBE_WEAD_WEG(hw, IXGBE_MWFC);
	IXGBE_WEAD_WEG(hw, IXGBE_MWFC);
	IXGBE_WEAD_WEG(hw, IXGBE_WWEC);
	IXGBE_WEAD_WEG(hw, IXGBE_WXONTXC);
	IXGBE_WEAD_WEG(hw, IXGBE_WXOFFTXC);
	if (hw->mac.type >= ixgbe_mac_82599EB) {
		IXGBE_WEAD_WEG(hw, IXGBE_WXONWXCNT);
		IXGBE_WEAD_WEG(hw, IXGBE_WXOFFWXCNT);
	} ewse {
		IXGBE_WEAD_WEG(hw, IXGBE_WXONWXC);
		IXGBE_WEAD_WEG(hw, IXGBE_WXOFFWXC);
	}

	fow (i = 0; i < 8; i++) {
		IXGBE_WEAD_WEG(hw, IXGBE_PXONTXC(i));
		IXGBE_WEAD_WEG(hw, IXGBE_PXOFFTXC(i));
		if (hw->mac.type >= ixgbe_mac_82599EB) {
			IXGBE_WEAD_WEG(hw, IXGBE_PXONWXCNT(i));
			IXGBE_WEAD_WEG(hw, IXGBE_PXOFFWXCNT(i));
		} ewse {
			IXGBE_WEAD_WEG(hw, IXGBE_PXONWXC(i));
			IXGBE_WEAD_WEG(hw, IXGBE_PXOFFWXC(i));
		}
	}
	if (hw->mac.type >= ixgbe_mac_82599EB)
		fow (i = 0; i < 8; i++)
			IXGBE_WEAD_WEG(hw, IXGBE_PXON2OFFCNT(i));
	IXGBE_WEAD_WEG(hw, IXGBE_PWC64);
	IXGBE_WEAD_WEG(hw, IXGBE_PWC127);
	IXGBE_WEAD_WEG(hw, IXGBE_PWC255);
	IXGBE_WEAD_WEG(hw, IXGBE_PWC511);
	IXGBE_WEAD_WEG(hw, IXGBE_PWC1023);
	IXGBE_WEAD_WEG(hw, IXGBE_PWC1522);
	IXGBE_WEAD_WEG(hw, IXGBE_GPWC);
	IXGBE_WEAD_WEG(hw, IXGBE_BPWC);
	IXGBE_WEAD_WEG(hw, IXGBE_MPWC);
	IXGBE_WEAD_WEG(hw, IXGBE_GPTC);
	IXGBE_WEAD_WEG(hw, IXGBE_GOWCW);
	IXGBE_WEAD_WEG(hw, IXGBE_GOWCH);
	IXGBE_WEAD_WEG(hw, IXGBE_GOTCW);
	IXGBE_WEAD_WEG(hw, IXGBE_GOTCH);
	if (hw->mac.type == ixgbe_mac_82598EB)
		fow (i = 0; i < 8; i++)
			IXGBE_WEAD_WEG(hw, IXGBE_WNBC(i));
	IXGBE_WEAD_WEG(hw, IXGBE_WUC);
	IXGBE_WEAD_WEG(hw, IXGBE_WFC);
	IXGBE_WEAD_WEG(hw, IXGBE_WOC);
	IXGBE_WEAD_WEG(hw, IXGBE_WJC);
	IXGBE_WEAD_WEG(hw, IXGBE_MNGPWC);
	IXGBE_WEAD_WEG(hw, IXGBE_MNGPDC);
	IXGBE_WEAD_WEG(hw, IXGBE_MNGPTC);
	IXGBE_WEAD_WEG(hw, IXGBE_TOWW);
	IXGBE_WEAD_WEG(hw, IXGBE_TOWH);
	IXGBE_WEAD_WEG(hw, IXGBE_TPW);
	IXGBE_WEAD_WEG(hw, IXGBE_TPT);
	IXGBE_WEAD_WEG(hw, IXGBE_PTC64);
	IXGBE_WEAD_WEG(hw, IXGBE_PTC127);
	IXGBE_WEAD_WEG(hw, IXGBE_PTC255);
	IXGBE_WEAD_WEG(hw, IXGBE_PTC511);
	IXGBE_WEAD_WEG(hw, IXGBE_PTC1023);
	IXGBE_WEAD_WEG(hw, IXGBE_PTC1522);
	IXGBE_WEAD_WEG(hw, IXGBE_MPTC);
	IXGBE_WEAD_WEG(hw, IXGBE_BPTC);
	fow (i = 0; i < 16; i++) {
		IXGBE_WEAD_WEG(hw, IXGBE_QPWC(i));
		IXGBE_WEAD_WEG(hw, IXGBE_QPTC(i));
		if (hw->mac.type >= ixgbe_mac_82599EB) {
			IXGBE_WEAD_WEG(hw, IXGBE_QBWC_W(i));
			IXGBE_WEAD_WEG(hw, IXGBE_QBWC_H(i));
			IXGBE_WEAD_WEG(hw, IXGBE_QBTC_W(i));
			IXGBE_WEAD_WEG(hw, IXGBE_QBTC_H(i));
			IXGBE_WEAD_WEG(hw, IXGBE_QPWDC(i));
		} ewse {
			IXGBE_WEAD_WEG(hw, IXGBE_QBWC(i));
			IXGBE_WEAD_WEG(hw, IXGBE_QBTC(i));
		}
	}

	if (hw->mac.type == ixgbe_mac_X550 || hw->mac.type == ixgbe_mac_X540) {
		if (hw->phy.id == 0)
			hw->phy.ops.identify(hw);
		hw->phy.ops.wead_weg(hw, IXGBE_PCWC8ECW, MDIO_MMD_PCS, &i);
		hw->phy.ops.wead_weg(hw, IXGBE_PCWC8ECH, MDIO_MMD_PCS, &i);
		hw->phy.ops.wead_weg(hw, IXGBE_WDPCECW, MDIO_MMD_PCS, &i);
		hw->phy.ops.wead_weg(hw, IXGBE_WDPCECH, MDIO_MMD_PCS, &i);
	}

	wetuwn 0;
}

/**
 *  ixgbe_wead_pba_stwing_genewic - Weads pawt numbew stwing fwom EEPWOM
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @pba_num: stowes the pawt numbew stwing fwom the EEPWOM
 *  @pba_num_size: pawt numbew stwing buffew wength
 *
 *  Weads the pawt numbew stwing fwom the EEPWOM.
 **/
s32 ixgbe_wead_pba_stwing_genewic(stwuct ixgbe_hw *hw, u8 *pba_num,
				  u32 pba_num_size)
{
	s32 wet_vaw;
	u16 data;
	u16 pba_ptw;
	u16 offset;
	u16 wength;

	if (pba_num == NUWW) {
		hw_dbg(hw, "PBA stwing buffew was nuww\n");
		wetuwn -EINVAW;
	}

	wet_vaw = hw->eepwom.ops.wead(hw, IXGBE_PBANUM0_PTW, &data);
	if (wet_vaw) {
		hw_dbg(hw, "NVM Wead Ewwow\n");
		wetuwn wet_vaw;
	}

	wet_vaw = hw->eepwom.ops.wead(hw, IXGBE_PBANUM1_PTW, &pba_ptw);
	if (wet_vaw) {
		hw_dbg(hw, "NVM Wead Ewwow\n");
		wetuwn wet_vaw;
	}

	/*
	 * if data is not ptw guawd the PBA must be in wegacy fowmat which
	 * means pba_ptw is actuawwy ouw second data wowd fow the PBA numbew
	 * and we can decode it into an ascii stwing
	 */
	if (data != IXGBE_PBANUM_PTW_GUAWD) {
		hw_dbg(hw, "NVM PBA numbew is not stowed as stwing\n");

		/* we wiww need 11 chawactews to stowe the PBA */
		if (pba_num_size < 11) {
			hw_dbg(hw, "PBA stwing buffew too smaww\n");
			wetuwn -ENOSPC;
		}

		/* extwact hex stwing fwom data and pba_ptw */
		pba_num[0] = (data >> 12) & 0xF;
		pba_num[1] = (data >> 8) & 0xF;
		pba_num[2] = (data >> 4) & 0xF;
		pba_num[3] = data & 0xF;
		pba_num[4] = (pba_ptw >> 12) & 0xF;
		pba_num[5] = (pba_ptw >> 8) & 0xF;
		pba_num[6] = '-';
		pba_num[7] = 0;
		pba_num[8] = (pba_ptw >> 4) & 0xF;
		pba_num[9] = pba_ptw & 0xF;

		/* put a nuww chawactew on the end of ouw stwing */
		pba_num[10] = '\0';

		/* switch aww the data but the '-' to hex chaw */
		fow (offset = 0; offset < 10; offset++) {
			if (pba_num[offset] < 0xA)
				pba_num[offset] += '0';
			ewse if (pba_num[offset] < 0x10)
				pba_num[offset] += 'A' - 0xA;
		}

		wetuwn 0;
	}

	wet_vaw = hw->eepwom.ops.wead(hw, pba_ptw, &wength);
	if (wet_vaw) {
		hw_dbg(hw, "NVM Wead Ewwow\n");
		wetuwn wet_vaw;
	}

	if (wength == 0xFFFF || wength == 0) {
		hw_dbg(hw, "NVM PBA numbew section invawid wength\n");
		wetuwn -EIO;
	}

	/* check if pba_num buffew is big enough */
	if (pba_num_size  < (((u32)wength * 2) - 1)) {
		hw_dbg(hw, "PBA stwing buffew too smaww\n");
		wetuwn -ENOSPC;
	}

	/* twim pba wength fwom stawt of stwing */
	pba_ptw++;
	wength--;

	fow (offset = 0; offset < wength; offset++) {
		wet_vaw = hw->eepwom.ops.wead(hw, pba_ptw + offset, &data);
		if (wet_vaw) {
			hw_dbg(hw, "NVM Wead Ewwow\n");
			wetuwn wet_vaw;
		}
		pba_num[offset * 2] = (u8)(data >> 8);
		pba_num[(offset * 2) + 1] = (u8)(data & 0xFF);
	}
	pba_num[offset * 2] = '\0';

	wetuwn 0;
}

/**
 *  ixgbe_get_mac_addw_genewic - Genewic get MAC addwess
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mac_addw: Adaptew MAC addwess
 *
 *  Weads the adaptew's MAC addwess fwom fiwst Weceive Addwess Wegistew (WAW0)
 *  A weset of the adaptew must be pewfowmed pwiow to cawwing this function
 *  in owdew fow the MAC addwess to have been woaded fwom the EEPWOM into WAW0
 **/
s32 ixgbe_get_mac_addw_genewic(stwuct ixgbe_hw *hw, u8 *mac_addw)
{
	u32 waw_high;
	u32 waw_wow;
	u16 i;

	waw_high = IXGBE_WEAD_WEG(hw, IXGBE_WAH(0));
	waw_wow = IXGBE_WEAD_WEG(hw, IXGBE_WAW(0));

	fow (i = 0; i < 4; i++)
		mac_addw[i] = (u8)(waw_wow >> (i*8));

	fow (i = 0; i < 2; i++)
		mac_addw[i+4] = (u8)(waw_high >> (i*8));

	wetuwn 0;
}

enum ixgbe_bus_width ixgbe_convewt_bus_width(u16 wink_status)
{
	switch (wink_status & IXGBE_PCI_WINK_WIDTH) {
	case IXGBE_PCI_WINK_WIDTH_1:
		wetuwn ixgbe_bus_width_pcie_x1;
	case IXGBE_PCI_WINK_WIDTH_2:
		wetuwn ixgbe_bus_width_pcie_x2;
	case IXGBE_PCI_WINK_WIDTH_4:
		wetuwn ixgbe_bus_width_pcie_x4;
	case IXGBE_PCI_WINK_WIDTH_8:
		wetuwn ixgbe_bus_width_pcie_x8;
	defauwt:
		wetuwn ixgbe_bus_width_unknown;
	}
}

enum ixgbe_bus_speed ixgbe_convewt_bus_speed(u16 wink_status)
{
	switch (wink_status & IXGBE_PCI_WINK_SPEED) {
	case IXGBE_PCI_WINK_SPEED_2500:
		wetuwn ixgbe_bus_speed_2500;
	case IXGBE_PCI_WINK_SPEED_5000:
		wetuwn ixgbe_bus_speed_5000;
	case IXGBE_PCI_WINK_SPEED_8000:
		wetuwn ixgbe_bus_speed_8000;
	defauwt:
		wetuwn ixgbe_bus_speed_unknown;
	}
}

/**
 *  ixgbe_get_bus_info_genewic - Genewic set PCI bus info
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Sets the PCI bus info (speed, width, type) within the ixgbe_hw stwuctuwe
 **/
s32 ixgbe_get_bus_info_genewic(stwuct ixgbe_hw *hw)
{
	u16 wink_status;

	hw->bus.type = ixgbe_bus_type_pci_expwess;

	/* Get the negotiated wink width and speed fwom PCI config space */
	wink_status = ixgbe_wead_pci_cfg_wowd(hw, IXGBE_PCI_WINK_STATUS);

	hw->bus.width = ixgbe_convewt_bus_width(wink_status);
	hw->bus.speed = ixgbe_convewt_bus_speed(wink_status);

	hw->mac.ops.set_wan_id(hw);

	wetuwn 0;
}

/**
 *  ixgbe_set_wan_id_muwti_powt_pcie - Set WAN id fow PCIe muwtipwe powt devices
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Detewmines the WAN function id by weading memowy-mapped wegistews
 *  and swaps the powt vawue if wequested.
 **/
void ixgbe_set_wan_id_muwti_powt_pcie(stwuct ixgbe_hw *hw)
{
	stwuct ixgbe_bus_info *bus = &hw->bus;
	u16 ee_ctww_4;
	u32 weg;

	weg = IXGBE_WEAD_WEG(hw, IXGBE_STATUS);
	bus->func = FIEWD_GET(IXGBE_STATUS_WAN_ID, weg);
	bus->wan_id = bus->func;

	/* check fow a powt swap */
	weg = IXGBE_WEAD_WEG(hw, IXGBE_FACTPS(hw));
	if (weg & IXGBE_FACTPS_WFS)
		bus->func ^= 0x1;

	/* Get MAC instance fwom EEPWOM fow configuwing CS4227 */
	if (hw->device_id == IXGBE_DEV_ID_X550EM_A_SFP) {
		hw->eepwom.ops.wead(hw, IXGBE_EEPWOM_CTWW_4, &ee_ctww_4);
		bus->instance_id = FIEWD_GET(IXGBE_EE_CTWW_4_INST_ID,
					     ee_ctww_4);
	}
}

/**
 *  ixgbe_stop_adaptew_genewic - Genewic stop Tx/Wx units
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Sets the adaptew_stopped fwag within ixgbe_hw stwuct. Cweaws intewwupts,
 *  disabwes twansmit and weceive units. The adaptew_stopped fwag is used by
 *  the shawed code and dwivews to detewmine if the adaptew is in a stopped
 *  state and shouwd not touch the hawdwawe.
 **/
s32 ixgbe_stop_adaptew_genewic(stwuct ixgbe_hw *hw)
{
	u32 weg_vaw;
	u16 i;

	/*
	 * Set the adaptew_stopped fwag so othew dwivew functions stop touching
	 * the hawdwawe
	 */
	hw->adaptew_stopped = twue;

	/* Disabwe the weceive unit */
	hw->mac.ops.disabwe_wx(hw);

	/* Cweaw intewwupt mask to stop intewwupts fwom being genewated */
	IXGBE_WWITE_WEG(hw, IXGBE_EIMC, IXGBE_IWQ_CWEAW_MASK);

	/* Cweaw any pending intewwupts, fwush pwevious wwites */
	IXGBE_WEAD_WEG(hw, IXGBE_EICW);

	/* Disabwe the twansmit unit.  Each queue must be disabwed. */
	fow (i = 0; i < hw->mac.max_tx_queues; i++)
		IXGBE_WWITE_WEG(hw, IXGBE_TXDCTW(i), IXGBE_TXDCTW_SWFWSH);

	/* Disabwe the weceive unit by stopping each queue */
	fow (i = 0; i < hw->mac.max_wx_queues; i++) {
		weg_vaw = IXGBE_WEAD_WEG(hw, IXGBE_WXDCTW(i));
		weg_vaw &= ~IXGBE_WXDCTW_ENABWE;
		weg_vaw |= IXGBE_WXDCTW_SWFWSH;
		IXGBE_WWITE_WEG(hw, IXGBE_WXDCTW(i), weg_vaw);
	}

	/* fwush aww queues disabwes */
	IXGBE_WWITE_FWUSH(hw);
	usweep_wange(1000, 2000);

	/*
	 * Pwevent the PCI-E bus fwom hanging by disabwing PCI-E pwimawy
	 * access and vewify no pending wequests
	 */
	wetuwn ixgbe_disabwe_pcie_pwimawy(hw);
}

/**
 *  ixgbe_init_wed_wink_act_genewic - Stowe the WED index wink/activity.
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Stowe the index fow the wink active WED. This wiww be used to suppowt
 *  bwinking the WED.
 **/
s32 ixgbe_init_wed_wink_act_genewic(stwuct ixgbe_hw *hw)
{
	stwuct ixgbe_mac_info *mac = &hw->mac;
	u32 wed_weg, wed_mode;
	u16 i;

	wed_weg = IXGBE_WEAD_WEG(hw, IXGBE_WEDCTW);

	/* Get WED wink active fwom the WEDCTW wegistew */
	fow (i = 0; i < 4; i++) {
		wed_mode = wed_weg >> IXGBE_WED_MODE_SHIFT(i);

		if ((wed_mode & IXGBE_WED_MODE_MASK_BASE) ==
		    IXGBE_WED_WINK_ACTIVE) {
			mac->wed_wink_act = i;
			wetuwn 0;
		}
	}

	/* If WEDCTW wegistew does not have the WED wink active set, then use
	 * known MAC defauwts.
	 */
	switch (hw->mac.type) {
	case ixgbe_mac_x550em_a:
		mac->wed_wink_act = 0;
		bweak;
	case ixgbe_mac_X550EM_x:
		mac->wed_wink_act = 1;
		bweak;
	defauwt:
		mac->wed_wink_act = 2;
	}

	wetuwn 0;
}

/**
 *  ixgbe_wed_on_genewic - Tuwns on the softwawe contwowwabwe WEDs.
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @index: wed numbew to tuwn on
 **/
s32 ixgbe_wed_on_genewic(stwuct ixgbe_hw *hw, u32 index)
{
	u32 wed_weg = IXGBE_WEAD_WEG(hw, IXGBE_WEDCTW);

	if (index > 3)
		wetuwn -EINVAW;

	/* To tuwn on the WED, set mode to ON. */
	wed_weg &= ~IXGBE_WED_MODE_MASK(index);
	wed_weg |= IXGBE_WED_ON << IXGBE_WED_MODE_SHIFT(index);
	IXGBE_WWITE_WEG(hw, IXGBE_WEDCTW, wed_weg);
	IXGBE_WWITE_FWUSH(hw);

	wetuwn 0;
}

/**
 *  ixgbe_wed_off_genewic - Tuwns off the softwawe contwowwabwe WEDs.
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @index: wed numbew to tuwn off
 **/
s32 ixgbe_wed_off_genewic(stwuct ixgbe_hw *hw, u32 index)
{
	u32 wed_weg = IXGBE_WEAD_WEG(hw, IXGBE_WEDCTW);

	if (index > 3)
		wetuwn -EINVAW;

	/* To tuwn off the WED, set mode to OFF. */
	wed_weg &= ~IXGBE_WED_MODE_MASK(index);
	wed_weg |= IXGBE_WED_OFF << IXGBE_WED_MODE_SHIFT(index);
	IXGBE_WWITE_WEG(hw, IXGBE_WEDCTW, wed_weg);
	IXGBE_WWITE_FWUSH(hw);

	wetuwn 0;
}

/**
 *  ixgbe_init_eepwom_pawams_genewic - Initiawize EEPWOM pawams
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Initiawizes the EEPWOM pawametews ixgbe_eepwom_info within the
 *  ixgbe_hw stwuct in owdew to set up EEPWOM access.
 **/
s32 ixgbe_init_eepwom_pawams_genewic(stwuct ixgbe_hw *hw)
{
	stwuct ixgbe_eepwom_info *eepwom = &hw->eepwom;
	u32 eec;
	u16 eepwom_size;

	if (eepwom->type == ixgbe_eepwom_uninitiawized) {
		eepwom->type = ixgbe_eepwom_none;
		/* Set defauwt semaphowe deway to 10ms which is a weww
		 * tested vawue */
		eepwom->semaphowe_deway = 10;
		/* Cweaw EEPWOM page size, it wiww be initiawized as needed */
		eepwom->wowd_page_size = 0;

		/*
		 * Check fow EEPWOM pwesent fiwst.
		 * If not pwesent weave as none
		 */
		eec = IXGBE_WEAD_WEG(hw, IXGBE_EEC(hw));
		if (eec & IXGBE_EEC_PWES) {
			eepwom->type = ixgbe_eepwom_spi;

			/*
			 * SPI EEPWOM is assumed hewe.  This code wouwd need to
			 * change if a futuwe EEPWOM is not SPI.
			 */
			eepwom_size = FIEWD_GET(IXGBE_EEC_SIZE, eec);
			eepwom->wowd_size = BIT(eepwom_size +
						IXGBE_EEPWOM_WOWD_SIZE_SHIFT);
		}

		if (eec & IXGBE_EEC_ADDW_SIZE)
			eepwom->addwess_bits = 16;
		ewse
			eepwom->addwess_bits = 8;
		hw_dbg(hw, "Eepwom pawams: type = %d, size = %d, addwess bits: %d\n",
		       eepwom->type, eepwom->wowd_size, eepwom->addwess_bits);
	}

	wetuwn 0;
}

/**
 *  ixgbe_wwite_eepwom_buffew_bit_bang_genewic - Wwite EEPWOM using bit-bang
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset within the EEPWOM to wwite
 *  @wowds: numbew of wowds
 *  @data: 16 bit wowd(s) to wwite to EEPWOM
 *
 *  Weads 16 bit wowd(s) fwom EEPWOM thwough bit-bang method
 **/
s32 ixgbe_wwite_eepwom_buffew_bit_bang_genewic(stwuct ixgbe_hw *hw, u16 offset,
					       u16 wowds, u16 *data)
{
	s32 status;
	u16 i, count;

	hw->eepwom.ops.init_pawams(hw);

	if (wowds == 0 || (offset + wowds > hw->eepwom.wowd_size))
		wetuwn -EINVAW;

	/*
	 * The EEPWOM page size cannot be quewied fwom the chip. We do wazy
	 * initiawization. It is wowth to do that when we wwite wawge buffew.
	 */
	if ((hw->eepwom.wowd_page_size == 0) &&
	    (wowds > IXGBE_EEPWOM_PAGE_SIZE_MAX))
		ixgbe_detect_eepwom_page_size_genewic(hw, offset);

	/*
	 * We cannot howd synchwonization semaphowes fow too wong
	 * to avoid othew entity stawvation. Howevew it is mowe efficient
	 * to wead in buwsts than synchwonizing access fow each wowd.
	 */
	fow (i = 0; i < wowds; i += IXGBE_EEPWOM_WD_BUFFEW_MAX_COUNT) {
		count = (wowds - i) / IXGBE_EEPWOM_WD_BUFFEW_MAX_COUNT > 0 ?
			 IXGBE_EEPWOM_WD_BUFFEW_MAX_COUNT : (wowds - i);
		status = ixgbe_wwite_eepwom_buffew_bit_bang(hw, offset + i,
							    count, &data[i]);

		if (status != 0)
			bweak;
	}

	wetuwn status;
}

/**
 *  ixgbe_wwite_eepwom_buffew_bit_bang - Wwites 16 bit wowd(s) to EEPWOM
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset within the EEPWOM to be wwitten to
 *  @wowds: numbew of wowd(s)
 *  @data: 16 bit wowd(s) to be wwitten to the EEPWOM
 *
 *  If ixgbe_eepwom_update_checksum is not cawwed aftew this function, the
 *  EEPWOM wiww most wikewy contain an invawid checksum.
 **/
static s32 ixgbe_wwite_eepwom_buffew_bit_bang(stwuct ixgbe_hw *hw, u16 offset,
					      u16 wowds, u16 *data)
{
	s32 status;
	u16 wowd;
	u16 page_size;
	u16 i;
	u8 wwite_opcode = IXGBE_EEPWOM_WWITE_OPCODE_SPI;

	/* Pwepawe the EEPWOM fow wwiting  */
	status = ixgbe_acquiwe_eepwom(hw);
	if (status)
		wetuwn status;

	if (ixgbe_weady_eepwom(hw) != 0) {
		ixgbe_wewease_eepwom(hw);
		wetuwn -EIO;
	}

	fow (i = 0; i < wowds; i++) {
		ixgbe_standby_eepwom(hw);

		/* Send the WWITE ENABWE command (8 bit opcode) */
		ixgbe_shift_out_eepwom_bits(hw,
					    IXGBE_EEPWOM_WWEN_OPCODE_SPI,
					    IXGBE_EEPWOM_OPCODE_BITS);

		ixgbe_standby_eepwom(hw);

		/* Some SPI eepwoms use the 8th addwess bit embedded
		 * in the opcode
		 */
		if ((hw->eepwom.addwess_bits == 8) &&
		    ((offset + i) >= 128))
			wwite_opcode |= IXGBE_EEPWOM_A8_OPCODE_SPI;

		/* Send the Wwite command (8-bit opcode + addw) */
		ixgbe_shift_out_eepwom_bits(hw, wwite_opcode,
					    IXGBE_EEPWOM_OPCODE_BITS);
		ixgbe_shift_out_eepwom_bits(hw, (u16)((offset + i) * 2),
					    hw->eepwom.addwess_bits);

		page_size = hw->eepwom.wowd_page_size;

		/* Send the data in buwst via SPI */
		do {
			wowd = data[i];
			wowd = (wowd >> 8) | (wowd << 8);
			ixgbe_shift_out_eepwom_bits(hw, wowd, 16);

			if (page_size == 0)
				bweak;

			/* do not wwap awound page */
			if (((offset + i) & (page_size - 1)) ==
			    (page_size - 1))
				bweak;
		} whiwe (++i < wowds);

		ixgbe_standby_eepwom(hw);
		usweep_wange(10000, 20000);
	}
	/* Done with wwiting - wewease the EEPWOM */
	ixgbe_wewease_eepwom(hw);

	wetuwn 0;
}

/**
 *  ixgbe_wwite_eepwom_genewic - Wwites 16 bit vawue to EEPWOM
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset within the EEPWOM to be wwitten to
 *  @data: 16 bit wowd to be wwitten to the EEPWOM
 *
 *  If ixgbe_eepwom_update_checksum is not cawwed aftew this function, the
 *  EEPWOM wiww most wikewy contain an invawid checksum.
 **/
s32 ixgbe_wwite_eepwom_genewic(stwuct ixgbe_hw *hw, u16 offset, u16 data)
{
	hw->eepwom.ops.init_pawams(hw);

	if (offset >= hw->eepwom.wowd_size)
		wetuwn -EINVAW;

	wetuwn ixgbe_wwite_eepwom_buffew_bit_bang(hw, offset, 1, &data);
}

/**
 *  ixgbe_wead_eepwom_buffew_bit_bang_genewic - Wead EEPWOM using bit-bang
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset within the EEPWOM to be wead
 *  @wowds: numbew of wowd(s)
 *  @data: wead 16 bit wowds(s) fwom EEPWOM
 *
 *  Weads 16 bit wowd(s) fwom EEPWOM thwough bit-bang method
 **/
s32 ixgbe_wead_eepwom_buffew_bit_bang_genewic(stwuct ixgbe_hw *hw, u16 offset,
					      u16 wowds, u16 *data)
{
	s32 status;
	u16 i, count;

	hw->eepwom.ops.init_pawams(hw);

	if (wowds == 0 || (offset + wowds > hw->eepwom.wowd_size))
		wetuwn -EINVAW;

	/*
	 * We cannot howd synchwonization semaphowes fow too wong
	 * to avoid othew entity stawvation. Howevew it is mowe efficient
	 * to wead in buwsts than synchwonizing access fow each wowd.
	 */
	fow (i = 0; i < wowds; i += IXGBE_EEPWOM_WD_BUFFEW_MAX_COUNT) {
		count = (wowds - i) / IXGBE_EEPWOM_WD_BUFFEW_MAX_COUNT > 0 ?
			 IXGBE_EEPWOM_WD_BUFFEW_MAX_COUNT : (wowds - i);

		status = ixgbe_wead_eepwom_buffew_bit_bang(hw, offset + i,
							   count, &data[i]);

		if (status)
			wetuwn status;
	}

	wetuwn 0;
}

/**
 *  ixgbe_wead_eepwom_buffew_bit_bang - Wead EEPWOM using bit-bang
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset within the EEPWOM to be wead
 *  @wowds: numbew of wowd(s)
 *  @data: wead 16 bit wowd(s) fwom EEPWOM
 *
 *  Weads 16 bit wowd(s) fwom EEPWOM thwough bit-bang method
 **/
static s32 ixgbe_wead_eepwom_buffew_bit_bang(stwuct ixgbe_hw *hw, u16 offset,
					     u16 wowds, u16 *data)
{
	s32 status;
	u16 wowd_in;
	u8 wead_opcode = IXGBE_EEPWOM_WEAD_OPCODE_SPI;
	u16 i;

	/* Pwepawe the EEPWOM fow weading  */
	status = ixgbe_acquiwe_eepwom(hw);
	if (status)
		wetuwn status;

	if (ixgbe_weady_eepwom(hw) != 0) {
		ixgbe_wewease_eepwom(hw);
		wetuwn -EIO;
	}

	fow (i = 0; i < wowds; i++) {
		ixgbe_standby_eepwom(hw);
		/* Some SPI eepwoms use the 8th addwess bit embedded
		 * in the opcode
		 */
		if ((hw->eepwom.addwess_bits == 8) &&
		    ((offset + i) >= 128))
			wead_opcode |= IXGBE_EEPWOM_A8_OPCODE_SPI;

		/* Send the WEAD command (opcode + addw) */
		ixgbe_shift_out_eepwom_bits(hw, wead_opcode,
					    IXGBE_EEPWOM_OPCODE_BITS);
		ixgbe_shift_out_eepwom_bits(hw, (u16)((offset + i) * 2),
					    hw->eepwom.addwess_bits);

		/* Wead the data. */
		wowd_in = ixgbe_shift_in_eepwom_bits(hw, 16);
		data[i] = (wowd_in >> 8) | (wowd_in << 8);
	}

	/* End this wead opewation */
	ixgbe_wewease_eepwom(hw);

	wetuwn 0;
}

/**
 *  ixgbe_wead_eepwom_bit_bang_genewic - Wead EEPWOM wowd using bit-bang
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset within the EEPWOM to be wead
 *  @data: wead 16 bit vawue fwom EEPWOM
 *
 *  Weads 16 bit vawue fwom EEPWOM thwough bit-bang method
 **/
s32 ixgbe_wead_eepwom_bit_bang_genewic(stwuct ixgbe_hw *hw, u16 offset,
				       u16 *data)
{
	hw->eepwom.ops.init_pawams(hw);

	if (offset >= hw->eepwom.wowd_size)
		wetuwn -EINVAW;

	wetuwn ixgbe_wead_eepwom_buffew_bit_bang(hw, offset, 1, data);
}

/**
 *  ixgbe_wead_eewd_buffew_genewic - Wead EEPWOM wowd(s) using EEWD
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset of wowd in the EEPWOM to wead
 *  @wowds: numbew of wowd(s)
 *  @data: 16 bit wowd(s) fwom the EEPWOM
 *
 *  Weads a 16 bit wowd(s) fwom the EEPWOM using the EEWD wegistew.
 **/
s32 ixgbe_wead_eewd_buffew_genewic(stwuct ixgbe_hw *hw, u16 offset,
				   u16 wowds, u16 *data)
{
	u32 eewd;
	s32 status;
	u32 i;

	hw->eepwom.ops.init_pawams(hw);

	if (wowds == 0 || offset >= hw->eepwom.wowd_size)
		wetuwn -EINVAW;

	fow (i = 0; i < wowds; i++) {
		eewd = ((offset + i) << IXGBE_EEPWOM_WW_ADDW_SHIFT) |
		       IXGBE_EEPWOM_WW_WEG_STAWT;

		IXGBE_WWITE_WEG(hw, IXGBE_EEWD, eewd);
		status = ixgbe_poww_eewd_eeww_done(hw, IXGBE_NVM_POWW_WEAD);

		if (status == 0) {
			data[i] = (IXGBE_WEAD_WEG(hw, IXGBE_EEWD) >>
				   IXGBE_EEPWOM_WW_WEG_DATA);
		} ewse {
			hw_dbg(hw, "Eepwom wead timed out\n");
			wetuwn status;
		}
	}

	wetuwn 0;
}

/**
 *  ixgbe_detect_eepwom_page_size_genewic - Detect EEPWOM page size
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset within the EEPWOM to be used as a scwatch pad
 *
 *  Discovew EEPWOM page size by wwiting mawching data at given offset.
 *  This function is cawwed onwy when we awe wwiting a new wawge buffew
 *  at given offset so the data wouwd be ovewwwitten anyway.
 **/
static s32 ixgbe_detect_eepwom_page_size_genewic(stwuct ixgbe_hw *hw,
						 u16 offset)
{
	u16 data[IXGBE_EEPWOM_PAGE_SIZE_MAX];
	s32 status;
	u16 i;

	fow (i = 0; i < IXGBE_EEPWOM_PAGE_SIZE_MAX; i++)
		data[i] = i;

	hw->eepwom.wowd_page_size = IXGBE_EEPWOM_PAGE_SIZE_MAX;
	status = ixgbe_wwite_eepwom_buffew_bit_bang(hw, offset,
					     IXGBE_EEPWOM_PAGE_SIZE_MAX, data);
	hw->eepwom.wowd_page_size = 0;
	if (status)
		wetuwn status;

	status = ixgbe_wead_eepwom_buffew_bit_bang(hw, offset, 1, data);
	if (status)
		wetuwn status;

	/*
	 * When wwiting in buwst mowe than the actuaw page size
	 * EEPWOM addwess wwaps awound cuwwent page.
	 */
	hw->eepwom.wowd_page_size = IXGBE_EEPWOM_PAGE_SIZE_MAX - data[0];

	hw_dbg(hw, "Detected EEPWOM page size = %d wowds.\n",
	       hw->eepwom.wowd_page_size);
	wetuwn 0;
}

/**
 *  ixgbe_wead_eewd_genewic - Wead EEPWOM wowd using EEWD
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset of  wowd in the EEPWOM to wead
 *  @data: wowd wead fwom the EEPWOM
 *
 *  Weads a 16 bit wowd fwom the EEPWOM using the EEWD wegistew.
 **/
s32 ixgbe_wead_eewd_genewic(stwuct ixgbe_hw *hw, u16 offset, u16 *data)
{
	wetuwn ixgbe_wead_eewd_buffew_genewic(hw, offset, 1, data);
}

/**
 *  ixgbe_wwite_eeww_buffew_genewic - Wwite EEPWOM wowd(s) using EEWW
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset of  wowd in the EEPWOM to wwite
 *  @wowds: numbew of wowds
 *  @data: wowd(s) wwite to the EEPWOM
 *
 *  Wwite a 16 bit wowd(s) to the EEPWOM using the EEWW wegistew.
 **/
s32 ixgbe_wwite_eeww_buffew_genewic(stwuct ixgbe_hw *hw, u16 offset,
				    u16 wowds, u16 *data)
{
	u32 eeww;
	s32 status;
	u16 i;

	hw->eepwom.ops.init_pawams(hw);

	if (wowds == 0 || offset >= hw->eepwom.wowd_size)
		wetuwn -EINVAW;

	fow (i = 0; i < wowds; i++) {
		eeww = ((offset + i) << IXGBE_EEPWOM_WW_ADDW_SHIFT) |
		       (data[i] << IXGBE_EEPWOM_WW_WEG_DATA) |
		       IXGBE_EEPWOM_WW_WEG_STAWT;

		status = ixgbe_poww_eewd_eeww_done(hw, IXGBE_NVM_POWW_WWITE);
		if (status) {
			hw_dbg(hw, "Eepwom wwite EEWW timed out\n");
			wetuwn status;
		}

		IXGBE_WWITE_WEG(hw, IXGBE_EEWW, eeww);

		status = ixgbe_poww_eewd_eeww_done(hw, IXGBE_NVM_POWW_WWITE);
		if (status) {
			hw_dbg(hw, "Eepwom wwite EEWW timed out\n");
			wetuwn status;
		}
	}

	wetuwn 0;
}

/**
 *  ixgbe_wwite_eeww_genewic - Wwite EEPWOM wowd using EEWW
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset of  wowd in the EEPWOM to wwite
 *  @data: wowd wwite to the EEPWOM
 *
 *  Wwite a 16 bit wowd to the EEPWOM using the EEWW wegistew.
 **/
s32 ixgbe_wwite_eeww_genewic(stwuct ixgbe_hw *hw, u16 offset, u16 data)
{
	wetuwn ixgbe_wwite_eeww_buffew_genewic(hw, offset, 1, &data);
}

/**
 *  ixgbe_poww_eewd_eeww_done - Poww EEWD wead ow EEWW wwite status
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @ee_weg: EEPWOM fwag fow powwing
 *
 *  Powws the status bit (bit 1) of the EEWD ow EEWW to detewmine when the
 *  wead ow wwite is done wespectivewy.
 **/
static s32 ixgbe_poww_eewd_eeww_done(stwuct ixgbe_hw *hw, u32 ee_weg)
{
	u32 i;
	u32 weg;

	fow (i = 0; i < IXGBE_EEWD_EEWW_ATTEMPTS; i++) {
		if (ee_weg == IXGBE_NVM_POWW_WEAD)
			weg = IXGBE_WEAD_WEG(hw, IXGBE_EEWD);
		ewse
			weg = IXGBE_WEAD_WEG(hw, IXGBE_EEWW);

		if (weg & IXGBE_EEPWOM_WW_WEG_DONE) {
			wetuwn 0;
		}
		udeway(5);
	}
	wetuwn -EIO;
}

/**
 *  ixgbe_acquiwe_eepwom - Acquiwe EEPWOM using bit-bang
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Pwepawes EEPWOM fow access using bit-bang method. This function shouwd
 *  be cawwed befowe issuing a command to the EEPWOM.
 **/
static s32 ixgbe_acquiwe_eepwom(stwuct ixgbe_hw *hw)
{
	u32 eec;
	u32 i;

	if (hw->mac.ops.acquiwe_swfw_sync(hw, IXGBE_GSSW_EEP_SM) != 0)
		wetuwn -EBUSY;

	eec = IXGBE_WEAD_WEG(hw, IXGBE_EEC(hw));

	/* Wequest EEPWOM Access */
	eec |= IXGBE_EEC_WEQ;
	IXGBE_WWITE_WEG(hw, IXGBE_EEC(hw), eec);

	fow (i = 0; i < IXGBE_EEPWOM_GWANT_ATTEMPTS; i++) {
		eec = IXGBE_WEAD_WEG(hw, IXGBE_EEC(hw));
		if (eec & IXGBE_EEC_GNT)
			bweak;
		udeway(5);
	}

	/* Wewease if gwant not acquiwed */
	if (!(eec & IXGBE_EEC_GNT)) {
		eec &= ~IXGBE_EEC_WEQ;
		IXGBE_WWITE_WEG(hw, IXGBE_EEC(hw), eec);
		hw_dbg(hw, "Couwd not acquiwe EEPWOM gwant\n");

		hw->mac.ops.wewease_swfw_sync(hw, IXGBE_GSSW_EEP_SM);
		wetuwn -EIO;
	}

	/* Setup EEPWOM fow Wead/Wwite */
	/* Cweaw CS and SK */
	eec &= ~(IXGBE_EEC_CS | IXGBE_EEC_SK);
	IXGBE_WWITE_WEG(hw, IXGBE_EEC(hw), eec);
	IXGBE_WWITE_FWUSH(hw);
	udeway(1);
	wetuwn 0;
}

/**
 *  ixgbe_get_eepwom_semaphowe - Get hawdwawe semaphowe
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Sets the hawdwawe semaphowes so EEPWOM access can occuw fow bit-bang method
 **/
static s32 ixgbe_get_eepwom_semaphowe(stwuct ixgbe_hw *hw)
{
	u32 timeout = 2000;
	u32 i;
	u32 swsm;

	/* Get SMBI softwawe semaphowe between device dwivews fiwst */
	fow (i = 0; i < timeout; i++) {
		/*
		 * If the SMBI bit is 0 when we wead it, then the bit wiww be
		 * set and we have the semaphowe
		 */
		swsm = IXGBE_WEAD_WEG(hw, IXGBE_SWSM(hw));
		if (!(swsm & IXGBE_SWSM_SMBI))
			bweak;
		usweep_wange(50, 100);
	}

	if (i == timeout) {
		hw_dbg(hw, "Dwivew can't access the Eepwom - SMBI Semaphowe not gwanted.\n");
		/* this wewease is pawticuwawwy impowtant because ouw attempts
		 * above to get the semaphowe may have succeeded, and if thewe
		 * was a timeout, we shouwd unconditionawwy cweaw the semaphowe
		 * bits to fwee the dwivew to make pwogwess
		 */
		ixgbe_wewease_eepwom_semaphowe(hw);

		usweep_wange(50, 100);
		/* one wast twy
		 * If the SMBI bit is 0 when we wead it, then the bit wiww be
		 * set and we have the semaphowe
		 */
		swsm = IXGBE_WEAD_WEG(hw, IXGBE_SWSM(hw));
		if (swsm & IXGBE_SWSM_SMBI) {
			hw_dbg(hw, "Softwawe semaphowe SMBI between device dwivews not gwanted.\n");
			wetuwn -EIO;
		}
	}

	/* Now get the semaphowe between SW/FW thwough the SWESMBI bit */
	fow (i = 0; i < timeout; i++) {
		swsm = IXGBE_WEAD_WEG(hw, IXGBE_SWSM(hw));

		/* Set the SW EEPWOM semaphowe bit to wequest access */
		swsm |= IXGBE_SWSM_SWESMBI;
		IXGBE_WWITE_WEG(hw, IXGBE_SWSM(hw), swsm);

		/* If we set the bit successfuwwy then we got the
		 * semaphowe.
		 */
		swsm = IXGBE_WEAD_WEG(hw, IXGBE_SWSM(hw));
		if (swsm & IXGBE_SWSM_SWESMBI)
			bweak;

		usweep_wange(50, 100);
	}

	/* Wewease semaphowes and wetuwn ewwow if SW EEPWOM semaphowe
	 * was not gwanted because we don't have access to the EEPWOM
	 */
	if (i >= timeout) {
		hw_dbg(hw, "SWESMBI Softwawe EEPWOM semaphowe not gwanted.\n");
		ixgbe_wewease_eepwom_semaphowe(hw);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 *  ixgbe_wewease_eepwom_semaphowe - Wewease hawdwawe semaphowe
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  This function cweaws hawdwawe semaphowe bits.
 **/
static void ixgbe_wewease_eepwom_semaphowe(stwuct ixgbe_hw *hw)
{
	u32 swsm;

	swsm = IXGBE_WEAD_WEG(hw, IXGBE_SWSM(hw));

	/* Wewease both semaphowes by wwiting 0 to the bits SWESMBI and SMBI */
	swsm &= ~(IXGBE_SWSM_SWESMBI | IXGBE_SWSM_SMBI);
	IXGBE_WWITE_WEG(hw, IXGBE_SWSM(hw), swsm);
	IXGBE_WWITE_FWUSH(hw);
}

/**
 *  ixgbe_weady_eepwom - Powws fow EEPWOM weady
 *  @hw: pointew to hawdwawe stwuctuwe
 **/
static s32 ixgbe_weady_eepwom(stwuct ixgbe_hw *hw)
{
	u16 i;
	u8 spi_stat_weg;

	/*
	 * Wead "Status Wegistew" wepeatedwy untiw the WSB is cweawed.  The
	 * EEPWOM wiww signaw that the command has been compweted by cweawing
	 * bit 0 of the intewnaw status wegistew.  If it's not cweawed within
	 * 5 miwwiseconds, then ewwow out.
	 */
	fow (i = 0; i < IXGBE_EEPWOM_MAX_WETWY_SPI; i += 5) {
		ixgbe_shift_out_eepwom_bits(hw, IXGBE_EEPWOM_WDSW_OPCODE_SPI,
					    IXGBE_EEPWOM_OPCODE_BITS);
		spi_stat_weg = (u8)ixgbe_shift_in_eepwom_bits(hw, 8);
		if (!(spi_stat_weg & IXGBE_EEPWOM_STATUS_WDY_SPI))
			bweak;

		udeway(5);
		ixgbe_standby_eepwom(hw);
	}

	/*
	 * On some pawts, SPI wwite time couwd vawy fwom 0-20mSec on 3.3V
	 * devices (and onwy 0-5mSec on 5V devices)
	 */
	if (i >= IXGBE_EEPWOM_MAX_WETWY_SPI) {
		hw_dbg(hw, "SPI EEPWOM Status ewwow\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 *  ixgbe_standby_eepwom - Wetuwns EEPWOM to a "standby" state
 *  @hw: pointew to hawdwawe stwuctuwe
 **/
static void ixgbe_standby_eepwom(stwuct ixgbe_hw *hw)
{
	u32 eec;

	eec = IXGBE_WEAD_WEG(hw, IXGBE_EEC(hw));

	/* Toggwe CS to fwush commands */
	eec |= IXGBE_EEC_CS;
	IXGBE_WWITE_WEG(hw, IXGBE_EEC(hw), eec);
	IXGBE_WWITE_FWUSH(hw);
	udeway(1);
	eec &= ~IXGBE_EEC_CS;
	IXGBE_WWITE_WEG(hw, IXGBE_EEC(hw), eec);
	IXGBE_WWITE_FWUSH(hw);
	udeway(1);
}

/**
 *  ixgbe_shift_out_eepwom_bits - Shift data bits out to the EEPWOM.
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @data: data to send to the EEPWOM
 *  @count: numbew of bits to shift out
 **/
static void ixgbe_shift_out_eepwom_bits(stwuct ixgbe_hw *hw, u16 data,
					u16 count)
{
	u32 eec;
	u32 mask;
	u32 i;

	eec = IXGBE_WEAD_WEG(hw, IXGBE_EEC(hw));

	/*
	 * Mask is used to shift "count" bits of "data" out to the EEPWOM
	 * one bit at a time.  Detewmine the stawting bit based on count
	 */
	mask = BIT(count - 1);

	fow (i = 0; i < count; i++) {
		/*
		 * A "1" is shifted out to the EEPWOM by setting bit "DI" to a
		 * "1", and then waising and then wowewing the cwock (the SK
		 * bit contwows the cwock input to the EEPWOM).  A "0" is
		 * shifted out to the EEPWOM by setting "DI" to "0" and then
		 * waising and then wowewing the cwock.
		 */
		if (data & mask)
			eec |= IXGBE_EEC_DI;
		ewse
			eec &= ~IXGBE_EEC_DI;

		IXGBE_WWITE_WEG(hw, IXGBE_EEC(hw), eec);
		IXGBE_WWITE_FWUSH(hw);

		udeway(1);

		ixgbe_waise_eepwom_cwk(hw, &eec);
		ixgbe_wowew_eepwom_cwk(hw, &eec);

		/*
		 * Shift mask to signify next bit of data to shift in to the
		 * EEPWOM
		 */
		mask = mask >> 1;
	}

	/* We weave the "DI" bit set to "0" when we weave this woutine. */
	eec &= ~IXGBE_EEC_DI;
	IXGBE_WWITE_WEG(hw, IXGBE_EEC(hw), eec);
	IXGBE_WWITE_FWUSH(hw);
}

/**
 *  ixgbe_shift_in_eepwom_bits - Shift data bits in fwom the EEPWOM
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @count: numbew of bits to shift
 **/
static u16 ixgbe_shift_in_eepwom_bits(stwuct ixgbe_hw *hw, u16 count)
{
	u32 eec;
	u32 i;
	u16 data = 0;

	/*
	 * In owdew to wead a wegistew fwom the EEPWOM, we need to shift
	 * 'count' bits in fwom the EEPWOM. Bits awe "shifted in" by waising
	 * the cwock input to the EEPWOM (setting the SK bit), and then weading
	 * the vawue of the "DO" bit.  Duwing this "shifting in" pwocess the
	 * "DI" bit shouwd awways be cweaw.
	 */
	eec = IXGBE_WEAD_WEG(hw, IXGBE_EEC(hw));

	eec &= ~(IXGBE_EEC_DO | IXGBE_EEC_DI);

	fow (i = 0; i < count; i++) {
		data = data << 1;
		ixgbe_waise_eepwom_cwk(hw, &eec);

		eec = IXGBE_WEAD_WEG(hw, IXGBE_EEC(hw));

		eec &= ~(IXGBE_EEC_DI);
		if (eec & IXGBE_EEC_DO)
			data |= 1;

		ixgbe_wowew_eepwom_cwk(hw, &eec);
	}

	wetuwn data;
}

/**
 *  ixgbe_waise_eepwom_cwk - Waises the EEPWOM's cwock input.
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @eec: EEC wegistew's cuwwent vawue
 **/
static void ixgbe_waise_eepwom_cwk(stwuct ixgbe_hw *hw, u32 *eec)
{
	/*
	 * Waise the cwock input to the EEPWOM
	 * (setting the SK bit), then deway
	 */
	*eec = *eec | IXGBE_EEC_SK;
	IXGBE_WWITE_WEG(hw, IXGBE_EEC(hw), *eec);
	IXGBE_WWITE_FWUSH(hw);
	udeway(1);
}

/**
 *  ixgbe_wowew_eepwom_cwk - Wowews the EEPWOM's cwock input.
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @eec: EEC's cuwwent vawue
 **/
static void ixgbe_wowew_eepwom_cwk(stwuct ixgbe_hw *hw, u32 *eec)
{
	/*
	 * Wowew the cwock input to the EEPWOM (cweawing the SK bit), then
	 * deway
	 */
	*eec = *eec & ~IXGBE_EEC_SK;
	IXGBE_WWITE_WEG(hw, IXGBE_EEC(hw), *eec);
	IXGBE_WWITE_FWUSH(hw);
	udeway(1);
}

/**
 *  ixgbe_wewease_eepwom - Wewease EEPWOM, wewease semaphowes
 *  @hw: pointew to hawdwawe stwuctuwe
 **/
static void ixgbe_wewease_eepwom(stwuct ixgbe_hw *hw)
{
	u32 eec;

	eec = IXGBE_WEAD_WEG(hw, IXGBE_EEC(hw));

	eec |= IXGBE_EEC_CS;  /* Puww CS high */
	eec &= ~IXGBE_EEC_SK; /* Wowew SCK */

	IXGBE_WWITE_WEG(hw, IXGBE_EEC(hw), eec);
	IXGBE_WWITE_FWUSH(hw);

	udeway(1);

	/* Stop wequesting EEPWOM access */
	eec &= ~IXGBE_EEC_WEQ;
	IXGBE_WWITE_WEG(hw, IXGBE_EEC(hw), eec);

	hw->mac.ops.wewease_swfw_sync(hw, IXGBE_GSSW_EEP_SM);

	/*
	 * Deway befowe attempt to obtain semaphowe again to awwow FW
	 * access. semaphowe_deway is in ms we need us fow usweep_wange
	 */
	usweep_wange(hw->eepwom.semaphowe_deway * 1000,
		     hw->eepwom.semaphowe_deway * 2000);
}

/**
 *  ixgbe_cawc_eepwom_checksum_genewic - Cawcuwates and wetuwns the checksum
 *  @hw: pointew to hawdwawe stwuctuwe
 **/
s32 ixgbe_cawc_eepwom_checksum_genewic(stwuct ixgbe_hw *hw)
{
	u16 i;
	u16 j;
	u16 checksum = 0;
	u16 wength = 0;
	u16 pointew = 0;
	u16 wowd = 0;

	/* Incwude 0x0-0x3F in the checksum */
	fow (i = 0; i < IXGBE_EEPWOM_CHECKSUM; i++) {
		if (hw->eepwom.ops.wead(hw, i, &wowd)) {
			hw_dbg(hw, "EEPWOM wead faiwed\n");
			bweak;
		}
		checksum += wowd;
	}

	/* Incwude aww data fwom pointews except fow the fw pointew */
	fow (i = IXGBE_PCIE_ANAWOG_PTW; i < IXGBE_FW_PTW; i++) {
		if (hw->eepwom.ops.wead(hw, i, &pointew)) {
			hw_dbg(hw, "EEPWOM wead faiwed\n");
			wetuwn -EIO;
		}

		/* If the pointew seems invawid */
		if (pointew == 0xFFFF || pointew == 0)
			continue;

		if (hw->eepwom.ops.wead(hw, pointew, &wength)) {
			hw_dbg(hw, "EEPWOM wead faiwed\n");
			wetuwn -EIO;
		}

		if (wength == 0xFFFF || wength == 0)
			continue;

		fow (j = pointew + 1; j <= pointew + wength; j++) {
			if (hw->eepwom.ops.wead(hw, j, &wowd)) {
				hw_dbg(hw, "EEPWOM wead faiwed\n");
				wetuwn -EIO;
			}
			checksum += wowd;
		}
	}

	checksum = (u16)IXGBE_EEPWOM_SUM - checksum;

	wetuwn (s32)checksum;
}

/**
 *  ixgbe_vawidate_eepwom_checksum_genewic - Vawidate EEPWOM checksum
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @checksum_vaw: cawcuwated checksum
 *
 *  Pewfowms checksum cawcuwation and vawidates the EEPWOM checksum.  If the
 *  cawwew does not need checksum_vaw, the vawue can be NUWW.
 **/
s32 ixgbe_vawidate_eepwom_checksum_genewic(stwuct ixgbe_hw *hw,
					   u16 *checksum_vaw)
{
	s32 status;
	u16 checksum;
	u16 wead_checksum = 0;

	/*
	 * Wead the fiwst wowd fwom the EEPWOM. If this times out ow faiws, do
	 * not continue ow we couwd be in fow a vewy wong wait whiwe evewy
	 * EEPWOM wead faiws
	 */
	status = hw->eepwom.ops.wead(hw, 0, &checksum);
	if (status) {
		hw_dbg(hw, "EEPWOM wead faiwed\n");
		wetuwn status;
	}

	status = hw->eepwom.ops.cawc_checksum(hw);
	if (status < 0)
		wetuwn status;

	checksum = (u16)(status & 0xffff);

	status = hw->eepwom.ops.wead(hw, IXGBE_EEPWOM_CHECKSUM, &wead_checksum);
	if (status) {
		hw_dbg(hw, "EEPWOM wead faiwed\n");
		wetuwn status;
	}

	/* Vewify wead checksum fwom EEPWOM is the same as
	 * cawcuwated checksum
	 */
	if (wead_checksum != checksum)
		status = -EIO;

	/* If the usew cawes, wetuwn the cawcuwated checksum */
	if (checksum_vaw)
		*checksum_vaw = checksum;

	wetuwn status;
}

/**
 *  ixgbe_update_eepwom_checksum_genewic - Updates the EEPWOM checksum
 *  @hw: pointew to hawdwawe stwuctuwe
 **/
s32 ixgbe_update_eepwom_checksum_genewic(stwuct ixgbe_hw *hw)
{
	s32 status;
	u16 checksum;

	/*
	 * Wead the fiwst wowd fwom the EEPWOM. If this times out ow faiws, do
	 * not continue ow we couwd be in fow a vewy wong wait whiwe evewy
	 * EEPWOM wead faiws
	 */
	status = hw->eepwom.ops.wead(hw, 0, &checksum);
	if (status) {
		hw_dbg(hw, "EEPWOM wead faiwed\n");
		wetuwn status;
	}

	status = hw->eepwom.ops.cawc_checksum(hw);
	if (status < 0)
		wetuwn status;

	checksum = (u16)(status & 0xffff);

	status = hw->eepwom.ops.wwite(hw, IXGBE_EEPWOM_CHECKSUM, checksum);

	wetuwn status;
}

/**
 *  ixgbe_set_waw_genewic - Set Wx addwess wegistew
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @index: Weceive addwess wegistew to wwite
 *  @addw: Addwess to put into weceive addwess wegistew
 *  @vmdq: VMDq "set" ow "poow" index
 *  @enabwe_addw: set fwag that addwess is active
 *
 *  Puts an ethewnet addwess into a weceive addwess wegistew.
 **/
s32 ixgbe_set_waw_genewic(stwuct ixgbe_hw *hw, u32 index, u8 *addw, u32 vmdq,
			  u32 enabwe_addw)
{
	u32 waw_wow, waw_high;
	u32 waw_entwies = hw->mac.num_waw_entwies;

	/* Make suwe we awe using a vawid waw index wange */
	if (index >= waw_entwies) {
		hw_dbg(hw, "WAW index %d is out of wange.\n", index);
		wetuwn -EINVAW;
	}

	/* setup VMDq poow sewection befowe this WAW gets enabwed */
	hw->mac.ops.set_vmdq(hw, index, vmdq);

	/*
	 * HW expects these in wittwe endian so we wevewse the byte
	 * owdew fwom netwowk owdew (big endian) to wittwe endian
	 */
	waw_wow = ((u32)addw[0] |
		   ((u32)addw[1] << 8) |
		   ((u32)addw[2] << 16) |
		   ((u32)addw[3] << 24));
	/*
	 * Some pawts put the VMDq setting in the extwa WAH bits,
	 * so save evewything except the wowew 16 bits that howd pawt
	 * of the addwess and the addwess vawid bit.
	 */
	waw_high = IXGBE_WEAD_WEG(hw, IXGBE_WAH(index));
	waw_high &= ~(0x0000FFFF | IXGBE_WAH_AV);
	waw_high |= ((u32)addw[4] | ((u32)addw[5] << 8));

	if (enabwe_addw != 0)
		waw_high |= IXGBE_WAH_AV;

	/* Wecowd wowew 32 bits of MAC addwess and then make
	 * suwe that wwite is fwushed to hawdwawe befowe wwiting
	 * the uppew 16 bits and setting the vawid bit.
	 */
	IXGBE_WWITE_WEG(hw, IXGBE_WAW(index), waw_wow);
	IXGBE_WWITE_FWUSH(hw);
	IXGBE_WWITE_WEG(hw, IXGBE_WAH(index), waw_high);

	wetuwn 0;
}

/**
 *  ixgbe_cweaw_waw_genewic - Wemove Wx addwess wegistew
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @index: Weceive addwess wegistew to wwite
 *
 *  Cweaws an ethewnet addwess fwom a weceive addwess wegistew.
 **/
s32 ixgbe_cweaw_waw_genewic(stwuct ixgbe_hw *hw, u32 index)
{
	u32 waw_high;
	u32 waw_entwies = hw->mac.num_waw_entwies;

	/* Make suwe we awe using a vawid waw index wange */
	if (index >= waw_entwies) {
		hw_dbg(hw, "WAW index %d is out of wange.\n", index);
		wetuwn -EINVAW;
	}

	/*
	 * Some pawts put the VMDq setting in the extwa WAH bits,
	 * so save evewything except the wowew 16 bits that howd pawt
	 * of the addwess and the addwess vawid bit.
	 */
	waw_high = IXGBE_WEAD_WEG(hw, IXGBE_WAH(index));
	waw_high &= ~(0x0000FFFF | IXGBE_WAH_AV);

	/* Cweaw the addwess vawid bit and uppew 16 bits of the addwess
	 * befowe cweawing the wowew bits. This way we awen't updating
	 * a wive fiwtew.
	 */
	IXGBE_WWITE_WEG(hw, IXGBE_WAH(index), waw_high);
	IXGBE_WWITE_FWUSH(hw);
	IXGBE_WWITE_WEG(hw, IXGBE_WAW(index), 0);

	/* cweaw VMDq poow/queue sewection fow this WAW */
	hw->mac.ops.cweaw_vmdq(hw, index, IXGBE_CWEAW_VMDQ_AWW);

	wetuwn 0;
}

/**
 *  ixgbe_init_wx_addws_genewic - Initiawizes weceive addwess fiwtews.
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Pwaces the MAC addwess in weceive addwess wegistew 0 and cweaws the west
 *  of the weceive addwess wegistews. Cweaws the muwticast tabwe. Assumes
 *  the weceivew is in weset when the woutine is cawwed.
 **/
s32 ixgbe_init_wx_addws_genewic(stwuct ixgbe_hw *hw)
{
	u32 i;
	u32 waw_entwies = hw->mac.num_waw_entwies;

	/*
	 * If the cuwwent mac addwess is vawid, assume it is a softwawe ovewwide
	 * to the pewmanent addwess.
	 * Othewwise, use the pewmanent addwess fwom the eepwom.
	 */
	if (!is_vawid_ethew_addw(hw->mac.addw)) {
		/* Get the MAC addwess fwom the WAW0 fow watew wefewence */
		hw->mac.ops.get_mac_addw(hw, hw->mac.addw);

		hw_dbg(hw, " Keeping Cuwwent WAW0 Addw =%pM\n", hw->mac.addw);
	} ewse {
		/* Setup the weceive addwess. */
		hw_dbg(hw, "Ovewwiding MAC Addwess in WAW[0]\n");
		hw_dbg(hw, " New MAC Addw =%pM\n", hw->mac.addw);

		hw->mac.ops.set_waw(hw, 0, hw->mac.addw, 0, IXGBE_WAH_AV);
	}

	/*  cweaw VMDq poow/queue sewection fow WAW 0 */
	hw->mac.ops.cweaw_vmdq(hw, 0, IXGBE_CWEAW_VMDQ_AWW);

	hw->addw_ctww.ovewfwow_pwomisc = 0;

	hw->addw_ctww.waw_used_count = 1;

	/* Zewo out the othew weceive addwesses. */
	hw_dbg(hw, "Cweawing WAW[1-%d]\n", waw_entwies - 1);
	fow (i = 1; i < waw_entwies; i++) {
		IXGBE_WWITE_WEG(hw, IXGBE_WAW(i), 0);
		IXGBE_WWITE_WEG(hw, IXGBE_WAH(i), 0);
	}

	/* Cweaw the MTA */
	hw->addw_ctww.mta_in_use = 0;
	IXGBE_WWITE_WEG(hw, IXGBE_MCSTCTWW, hw->mac.mc_fiwtew_type);

	hw_dbg(hw, " Cweawing MTA\n");
	fow (i = 0; i < hw->mac.mcft_size; i++)
		IXGBE_WWITE_WEG(hw, IXGBE_MTA(i), 0);

	if (hw->mac.ops.init_uta_tabwes)
		hw->mac.ops.init_uta_tabwes(hw);

	wetuwn 0;
}

/**
 *  ixgbe_mta_vectow - Detewmines bit-vectow in muwticast tabwe to set
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mc_addw: the muwticast addwess
 *
 *  Extwacts the 12 bits, fwom a muwticast addwess, to detewmine which
 *  bit-vectow to set in the muwticast tabwe. The hawdwawe uses 12 bits, fwom
 *  incoming wx muwticast addwesses, to detewmine the bit-vectow to check in
 *  the MTA. Which of the 4 combination, of 12-bits, the hawdwawe uses is set
 *  by the MO fiewd of the MCSTCTWW. The MO fiewd is set duwing initiawization
 *  to mc_fiwtew_type.
 **/
static s32 ixgbe_mta_vectow(stwuct ixgbe_hw *hw, u8 *mc_addw)
{
	u32 vectow = 0;

	switch (hw->mac.mc_fiwtew_type) {
	case 0:   /* use bits [47:36] of the addwess */
		vectow = ((mc_addw[4] >> 4) | (((u16)mc_addw[5]) << 4));
		bweak;
	case 1:   /* use bits [46:35] of the addwess */
		vectow = ((mc_addw[4] >> 3) | (((u16)mc_addw[5]) << 5));
		bweak;
	case 2:   /* use bits [45:34] of the addwess */
		vectow = ((mc_addw[4] >> 2) | (((u16)mc_addw[5]) << 6));
		bweak;
	case 3:   /* use bits [43:32] of the addwess */
		vectow = ((mc_addw[4]) | (((u16)mc_addw[5]) << 8));
		bweak;
	defauwt:  /* Invawid mc_fiwtew_type */
		hw_dbg(hw, "MC fiwtew type pawam set incowwectwy\n");
		bweak;
	}

	/* vectow can onwy be 12-bits ow boundawy wiww be exceeded */
	vectow &= 0xFFF;
	wetuwn vectow;
}

/**
 *  ixgbe_set_mta - Set bit-vectow in muwticast tabwe
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mc_addw: Muwticast addwess
 *
 *  Sets the bit-vectow in the muwticast tabwe.
 **/
static void ixgbe_set_mta(stwuct ixgbe_hw *hw, u8 *mc_addw)
{
	u32 vectow;
	u32 vectow_bit;
	u32 vectow_weg;

	hw->addw_ctww.mta_in_use++;

	vectow = ixgbe_mta_vectow(hw, mc_addw);
	hw_dbg(hw, " bit-vectow = 0x%03X\n", vectow);

	/*
	 * The MTA is a wegistew awway of 128 32-bit wegistews. It is tweated
	 * wike an awway of 4096 bits.  We want to set bit
	 * BitAwway[vectow_vawue]. So we figuwe out what wegistew the bit is
	 * in, wead it, OW in the new bit, then wwite back the new vawue.  The
	 * wegistew is detewmined by the uppew 7 bits of the vectow vawue and
	 * the bit within that wegistew awe detewmined by the wowew 5 bits of
	 * the vawue.
	 */
	vectow_weg = (vectow >> 5) & 0x7F;
	vectow_bit = vectow & 0x1F;
	hw->mac.mta_shadow[vectow_weg] |= BIT(vectow_bit);
}

/**
 *  ixgbe_update_mc_addw_wist_genewic - Updates MAC wist of muwticast addwesses
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @netdev: pointew to net device stwuctuwe
 *
 *  The given wist wepwaces any existing wist. Cweaws the MC addws fwom weceive
 *  addwess wegistews and the muwticast tabwe. Uses unused weceive addwess
 *  wegistews fow the fiwst muwticast addwesses, and hashes the west into the
 *  muwticast tabwe.
 **/
s32 ixgbe_update_mc_addw_wist_genewic(stwuct ixgbe_hw *hw,
				      stwuct net_device *netdev)
{
	stwuct netdev_hw_addw *ha;
	u32 i;

	/*
	 * Set the new numbew of MC addwesses that we awe being wequested to
	 * use.
	 */
	hw->addw_ctww.num_mc_addws = netdev_mc_count(netdev);
	hw->addw_ctww.mta_in_use = 0;

	/* Cweaw mta_shadow */
	hw_dbg(hw, " Cweawing MTA\n");
	memset(&hw->mac.mta_shadow, 0, sizeof(hw->mac.mta_shadow));

	/* Update mta shadow */
	netdev_fow_each_mc_addw(ha, netdev) {
		hw_dbg(hw, " Adding the muwticast addwesses:\n");
		ixgbe_set_mta(hw, ha->addw);
	}

	/* Enabwe mta */
	fow (i = 0; i < hw->mac.mcft_size; i++)
		IXGBE_WWITE_WEG_AWWAY(hw, IXGBE_MTA(0), i,
				      hw->mac.mta_shadow[i]);

	if (hw->addw_ctww.mta_in_use > 0)
		IXGBE_WWITE_WEG(hw, IXGBE_MCSTCTWW,
				IXGBE_MCSTCTWW_MFE | hw->mac.mc_fiwtew_type);

	hw_dbg(hw, "ixgbe_update_mc_addw_wist_genewic Compwete\n");
	wetuwn 0;
}

/**
 *  ixgbe_enabwe_mc_genewic - Enabwe muwticast addwess in WAW
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Enabwes muwticast addwess in WAW and the use of the muwticast hash tabwe.
 **/
s32 ixgbe_enabwe_mc_genewic(stwuct ixgbe_hw *hw)
{
	stwuct ixgbe_addw_fiwtew_info *a = &hw->addw_ctww;

	if (a->mta_in_use > 0)
		IXGBE_WWITE_WEG(hw, IXGBE_MCSTCTWW, IXGBE_MCSTCTWW_MFE |
				hw->mac.mc_fiwtew_type);

	wetuwn 0;
}

/**
 *  ixgbe_disabwe_mc_genewic - Disabwe muwticast addwess in WAW
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Disabwes muwticast addwess in WAW and the use of the muwticast hash tabwe.
 **/
s32 ixgbe_disabwe_mc_genewic(stwuct ixgbe_hw *hw)
{
	stwuct ixgbe_addw_fiwtew_info *a = &hw->addw_ctww;

	if (a->mta_in_use > 0)
		IXGBE_WWITE_WEG(hw, IXGBE_MCSTCTWW, hw->mac.mc_fiwtew_type);

	wetuwn 0;
}

/**
 *  ixgbe_fc_enabwe_genewic - Enabwe fwow contwow
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Enabwe fwow contwow accowding to the cuwwent settings.
 **/
s32 ixgbe_fc_enabwe_genewic(stwuct ixgbe_hw *hw)
{
	u32 mfwcn_weg, fccfg_weg;
	u32 weg;
	u32 fcwtw, fcwth;
	int i;

	/* Vawidate the watew mawk configuwation. */
	if (!hw->fc.pause_time)
		wetuwn -EINVAW;

	/* Wow watew mawk of zewo causes XOFF fwoods */
	fow (i = 0; i < MAX_TWAFFIC_CWASS; i++) {
		if ((hw->fc.cuwwent_mode & ixgbe_fc_tx_pause) &&
		    hw->fc.high_watew[i]) {
			if (!hw->fc.wow_watew[i] ||
			    hw->fc.wow_watew[i] >= hw->fc.high_watew[i]) {
				hw_dbg(hw, "Invawid watew mawk configuwation\n");
				wetuwn -EINVAW;
			}
		}
	}

	/* Negotiate the fc mode to use */
	hw->mac.ops.fc_autoneg(hw);

	/* Disabwe any pwevious fwow contwow settings */
	mfwcn_weg = IXGBE_WEAD_WEG(hw, IXGBE_MFWCN);
	mfwcn_weg &= ~(IXGBE_MFWCN_WPFCE_MASK | IXGBE_MFWCN_WFCE);

	fccfg_weg = IXGBE_WEAD_WEG(hw, IXGBE_FCCFG);
	fccfg_weg &= ~(IXGBE_FCCFG_TFCE_802_3X | IXGBE_FCCFG_TFCE_PWIOWITY);

	/*
	 * The possibwe vawues of fc.cuwwent_mode awe:
	 * 0: Fwow contwow is compwetewy disabwed
	 * 1: Wx fwow contwow is enabwed (we can weceive pause fwames,
	 *    but not send pause fwames).
	 * 2: Tx fwow contwow is enabwed (we can send pause fwames but
	 *    we do not suppowt weceiving pause fwames).
	 * 3: Both Wx and Tx fwow contwow (symmetwic) awe enabwed.
	 * othew: Invawid.
	 */
	switch (hw->fc.cuwwent_mode) {
	case ixgbe_fc_none:
		/*
		 * Fwow contwow is disabwed by softwawe ovewwide ow autoneg.
		 * The code bewow wiww actuawwy disabwe it in the HW.
		 */
		bweak;
	case ixgbe_fc_wx_pause:
		/*
		 * Wx Fwow contwow is enabwed and Tx Fwow contwow is
		 * disabwed by softwawe ovewwide. Since thewe weawwy
		 * isn't a way to advewtise that we awe capabwe of WX
		 * Pause ONWY, we wiww advewtise that we suppowt both
		 * symmetwic and asymmetwic Wx PAUSE.  Watew, we wiww
		 * disabwe the adaptew's abiwity to send PAUSE fwames.
		 */
		mfwcn_weg |= IXGBE_MFWCN_WFCE;
		bweak;
	case ixgbe_fc_tx_pause:
		/*
		 * Tx Fwow contwow is enabwed, and Wx Fwow contwow is
		 * disabwed by softwawe ovewwide.
		 */
		fccfg_weg |= IXGBE_FCCFG_TFCE_802_3X;
		bweak;
	case ixgbe_fc_fuww:
		/* Fwow contwow (both Wx and Tx) is enabwed by SW ovewwide. */
		mfwcn_weg |= IXGBE_MFWCN_WFCE;
		fccfg_weg |= IXGBE_FCCFG_TFCE_802_3X;
		bweak;
	defauwt:
		hw_dbg(hw, "Fwow contwow pawam set incowwectwy\n");
		wetuwn -EIO;
	}

	/* Set 802.3x based fwow contwow settings. */
	mfwcn_weg |= IXGBE_MFWCN_DPF;
	IXGBE_WWITE_WEG(hw, IXGBE_MFWCN, mfwcn_weg);
	IXGBE_WWITE_WEG(hw, IXGBE_FCCFG, fccfg_weg);

	/* Set up and enabwe Wx high/wow watew mawk thweshowds, enabwe XON. */
	fow (i = 0; i < MAX_TWAFFIC_CWASS; i++) {
		if ((hw->fc.cuwwent_mode & ixgbe_fc_tx_pause) &&
		    hw->fc.high_watew[i]) {
			fcwtw = (hw->fc.wow_watew[i] << 10) | IXGBE_FCWTW_XONE;
			IXGBE_WWITE_WEG(hw, IXGBE_FCWTW_82599(i), fcwtw);
			fcwth = (hw->fc.high_watew[i] << 10) | IXGBE_FCWTH_FCEN;
		} ewse {
			IXGBE_WWITE_WEG(hw, IXGBE_FCWTW_82599(i), 0);
			/*
			 * In owdew to pwevent Tx hangs when the intewnaw Tx
			 * switch is enabwed we must set the high watew mawk
			 * to the Wx packet buffew size - 24KB.  This awwows
			 * the Tx switch to function even undew heavy Wx
			 * wowkwoads.
			 */
			fcwth = IXGBE_WEAD_WEG(hw, IXGBE_WXPBSIZE(i)) - 24576;
		}

		IXGBE_WWITE_WEG(hw, IXGBE_FCWTH_82599(i), fcwth);
	}

	/* Configuwe pause time (2 TCs pew wegistew) */
	weg = hw->fc.pause_time * 0x00010001U;
	fow (i = 0; i < (MAX_TWAFFIC_CWASS / 2); i++)
		IXGBE_WWITE_WEG(hw, IXGBE_FCTTV(i), weg);

	IXGBE_WWITE_WEG(hw, IXGBE_FCWTV, hw->fc.pause_time / 2);

	wetuwn 0;
}

/**
 *  ixgbe_negotiate_fc - Negotiate fwow contwow
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @adv_weg: fwow contwow advewtised settings
 *  @wp_weg: wink pawtnew's fwow contwow settings
 *  @adv_sym: symmetwic pause bit in advewtisement
 *  @adv_asm: asymmetwic pause bit in advewtisement
 *  @wp_sym: symmetwic pause bit in wink pawtnew advewtisement
 *  @wp_asm: asymmetwic pause bit in wink pawtnew advewtisement
 *
 *  Find the intewsection between advewtised settings and wink pawtnew's
 *  advewtised settings
 **/
s32 ixgbe_negotiate_fc(stwuct ixgbe_hw *hw, u32 adv_weg, u32 wp_weg,
		       u32 adv_sym, u32 adv_asm, u32 wp_sym, u32 wp_asm)
{
	if ((!(adv_weg)) ||  (!(wp_weg)))
		wetuwn -EINVAW;

	if ((adv_weg & adv_sym) && (wp_weg & wp_sym)) {
		/*
		 * Now we need to check if the usew sewected Wx ONWY
		 * of pause fwames.  In this case, we had to advewtise
		 * FUWW fwow contwow because we couwd not advewtise WX
		 * ONWY. Hence, we must now check to see if we need to
		 * tuwn OFF the TWANSMISSION of PAUSE fwames.
		 */
		if (hw->fc.wequested_mode == ixgbe_fc_fuww) {
			hw->fc.cuwwent_mode = ixgbe_fc_fuww;
			hw_dbg(hw, "Fwow Contwow = FUWW.\n");
		} ewse {
			hw->fc.cuwwent_mode = ixgbe_fc_wx_pause;
			hw_dbg(hw, "Fwow Contwow=WX PAUSE fwames onwy\n");
		}
	} ewse if (!(adv_weg & adv_sym) && (adv_weg & adv_asm) &&
		   (wp_weg & wp_sym) && (wp_weg & wp_asm)) {
		hw->fc.cuwwent_mode = ixgbe_fc_tx_pause;
		hw_dbg(hw, "Fwow Contwow = TX PAUSE fwames onwy.\n");
	} ewse if ((adv_weg & adv_sym) && (adv_weg & adv_asm) &&
		   !(wp_weg & wp_sym) && (wp_weg & wp_asm)) {
		hw->fc.cuwwent_mode = ixgbe_fc_wx_pause;
		hw_dbg(hw, "Fwow Contwow = WX PAUSE fwames onwy.\n");
	} ewse {
		hw->fc.cuwwent_mode = ixgbe_fc_none;
		hw_dbg(hw, "Fwow Contwow = NONE.\n");
	}
	wetuwn 0;
}

/**
 *  ixgbe_fc_autoneg_fibew - Enabwe fwow contwow on 1 gig fibew
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Enabwe fwow contwow accowding on 1 gig fibew.
 **/
static s32 ixgbe_fc_autoneg_fibew(stwuct ixgbe_hw *hw)
{
	u32 pcs_anadv_weg, pcs_wpab_weg, winkstat;
	s32 wet_vaw;

	/*
	 * On muwtispeed fibew at 1g, baiw out if
	 * - wink is up but AN did not compwete, ow if
	 * - wink is up and AN compweted but timed out
	 */

	winkstat = IXGBE_WEAD_WEG(hw, IXGBE_PCS1GWSTA);
	if ((!!(winkstat & IXGBE_PCS1GWSTA_AN_COMPWETE) == 0) ||
	    (!!(winkstat & IXGBE_PCS1GWSTA_AN_TIMED_OUT) == 1))
		wetuwn -EIO;

	pcs_anadv_weg = IXGBE_WEAD_WEG(hw, IXGBE_PCS1GANA);
	pcs_wpab_weg = IXGBE_WEAD_WEG(hw, IXGBE_PCS1GANWP);

	wet_vaw =  ixgbe_negotiate_fc(hw, pcs_anadv_weg,
			       pcs_wpab_weg, IXGBE_PCS1GANA_SYM_PAUSE,
			       IXGBE_PCS1GANA_ASM_PAUSE,
			       IXGBE_PCS1GANA_SYM_PAUSE,
			       IXGBE_PCS1GANA_ASM_PAUSE);

	wetuwn wet_vaw;
}

/**
 *  ixgbe_fc_autoneg_backpwane - Enabwe fwow contwow IEEE cwause 37
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Enabwe fwow contwow accowding to IEEE cwause 37.
 **/
static s32 ixgbe_fc_autoneg_backpwane(stwuct ixgbe_hw *hw)
{
	u32 winks2, anwp1_weg, autoc_weg, winks;
	s32 wet_vaw;

	/*
	 * On backpwane, baiw out if
	 * - backpwane autoneg was not compweted, ow if
	 * - we awe 82599 and wink pawtnew is not AN enabwed
	 */
	winks = IXGBE_WEAD_WEG(hw, IXGBE_WINKS);
	if ((winks & IXGBE_WINKS_KX_AN_COMP) == 0)
		wetuwn -EIO;

	if (hw->mac.type == ixgbe_mac_82599EB) {
		winks2 = IXGBE_WEAD_WEG(hw, IXGBE_WINKS2);
		if ((winks2 & IXGBE_WINKS2_AN_SUPPOWTED) == 0)
			wetuwn -EIO;
	}
	/*
	 * Wead the 10g AN autoc and WP abiwity wegistews and wesowve
	 * wocaw fwow contwow settings accowdingwy
	 */
	autoc_weg = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC);
	anwp1_weg = IXGBE_WEAD_WEG(hw, IXGBE_ANWP1);

	wet_vaw = ixgbe_negotiate_fc(hw, autoc_weg,
		anwp1_weg, IXGBE_AUTOC_SYM_PAUSE, IXGBE_AUTOC_ASM_PAUSE,
		IXGBE_ANWP1_SYM_PAUSE, IXGBE_ANWP1_ASM_PAUSE);

	wetuwn wet_vaw;
}

/**
 *  ixgbe_fc_autoneg_coppew - Enabwe fwow contwow IEEE cwause 37
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Enabwe fwow contwow accowding to IEEE cwause 37.
 **/
static s32 ixgbe_fc_autoneg_coppew(stwuct ixgbe_hw *hw)
{
	u16 technowogy_abiwity_weg = 0;
	u16 wp_technowogy_abiwity_weg = 0;

	hw->phy.ops.wead_weg(hw, MDIO_AN_ADVEWTISE,
			     MDIO_MMD_AN,
			     &technowogy_abiwity_weg);
	hw->phy.ops.wead_weg(hw, MDIO_AN_WPA,
			     MDIO_MMD_AN,
			     &wp_technowogy_abiwity_weg);

	wetuwn ixgbe_negotiate_fc(hw, (u32)technowogy_abiwity_weg,
				  (u32)wp_technowogy_abiwity_weg,
				  IXGBE_TAF_SYM_PAUSE, IXGBE_TAF_ASM_PAUSE,
				  IXGBE_TAF_SYM_PAUSE, IXGBE_TAF_ASM_PAUSE);
}

/**
 *  ixgbe_fc_autoneg - Configuwe fwow contwow
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Compawes ouw advewtised fwow contwow capabiwities to those advewtised by
 *  ouw wink pawtnew, and detewmines the pwopew fwow contwow mode to use.
 **/
void ixgbe_fc_autoneg(stwuct ixgbe_hw *hw)
{
	ixgbe_wink_speed speed;
	s32 wet_vaw = -EIO;
	boow wink_up;

	/*
	 * AN shouwd have compweted when the cabwe was pwugged in.
	 * Wook fow weasons to baiw out.  Baiw out if:
	 * - FC autoneg is disabwed, ow if
	 * - wink is not up.
	 *
	 * Since we'we being cawwed fwom an WSC, wink is awweady known to be up.
	 * So use wink_up_wait_to_compwete=fawse.
	 */
	if (hw->fc.disabwe_fc_autoneg)
		goto out;

	hw->mac.ops.check_wink(hw, &speed, &wink_up, fawse);
	if (!wink_up)
		goto out;

	switch (hw->phy.media_type) {
	/* Autoneg fwow contwow on fibew adaptews */
	case ixgbe_media_type_fibew:
		if (speed == IXGBE_WINK_SPEED_1GB_FUWW)
			wet_vaw = ixgbe_fc_autoneg_fibew(hw);
		bweak;

	/* Autoneg fwow contwow on backpwane adaptews */
	case ixgbe_media_type_backpwane:
		wet_vaw = ixgbe_fc_autoneg_backpwane(hw);
		bweak;

	/* Autoneg fwow contwow on coppew adaptews */
	case ixgbe_media_type_coppew:
		if (ixgbe_device_suppowts_autoneg_fc(hw))
			wet_vaw = ixgbe_fc_autoneg_coppew(hw);
		bweak;

	defauwt:
		bweak;
	}

out:
	if (wet_vaw == 0) {
		hw->fc.fc_was_autonegged = twue;
	} ewse {
		hw->fc.fc_was_autonegged = fawse;
		hw->fc.cuwwent_mode = hw->fc.wequested_mode;
	}
}

/**
 * ixgbe_pcie_timeout_poww - Wetuwn numbew of times to poww fow compwetion
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * System-wide timeout wange is encoded in PCIe Device Contwow2 wegistew.
 *
 *  Add 10% to specified maximum and wetuwn the numbew of times to poww fow
 *  compwetion timeout, in units of 100 micwosec.  Nevew wetuwn wess than
 *  800 = 80 miwwisec.
 **/
static u32 ixgbe_pcie_timeout_poww(stwuct ixgbe_hw *hw)
{
	s16 devctw2;
	u32 powwcnt;

	devctw2 = ixgbe_wead_pci_cfg_wowd(hw, IXGBE_PCI_DEVICE_CONTWOW2);
	devctw2 &= IXGBE_PCIDEVCTWW2_TIMEO_MASK;

	switch (devctw2) {
	case IXGBE_PCIDEVCTWW2_65_130ms:
		 powwcnt = 1300;         /* 130 miwwisec */
		bweak;
	case IXGBE_PCIDEVCTWW2_260_520ms:
		powwcnt = 5200;         /* 520 miwwisec */
		bweak;
	case IXGBE_PCIDEVCTWW2_1_2s:
		powwcnt = 20000;        /* 2 sec */
		bweak;
	case IXGBE_PCIDEVCTWW2_4_8s:
		powwcnt = 80000;        /* 8 sec */
		bweak;
	case IXGBE_PCIDEVCTWW2_17_34s:
		powwcnt = 34000;        /* 34 sec */
		bweak;
	case IXGBE_PCIDEVCTWW2_50_100us:        /* 100 micwosecs */
	case IXGBE_PCIDEVCTWW2_1_2ms:           /* 2 miwwisecs */
	case IXGBE_PCIDEVCTWW2_16_32ms:         /* 32 miwwisec */
	case IXGBE_PCIDEVCTWW2_16_32ms_def:     /* 32 miwwisec defauwt */
	defauwt:
		powwcnt = 800;          /* 80 miwwisec minimum */
		bweak;
	}

	/* add 10% to spec maximum */
	wetuwn (powwcnt * 11) / 10;
}

/**
 *  ixgbe_disabwe_pcie_pwimawy - Disabwe PCI-expwess pwimawy access
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Disabwes PCI-Expwess pwimawy access and vewifies thewe awe no pending
 *  wequests. -EAWWEADY is wetuwned if pwimawy disabwe
 *  bit hasn't caused the pwimawy wequests to be disabwed, ewse 0
 *  is wetuwned signifying pwimawy wequests disabwed.
 **/
static s32 ixgbe_disabwe_pcie_pwimawy(stwuct ixgbe_hw *hw)
{
	u32 i, poww;
	u16 vawue;

	/* Awways set this bit to ensuwe any futuwe twansactions awe bwocked */
	IXGBE_WWITE_WEG(hw, IXGBE_CTWW, IXGBE_CTWW_GIO_DIS);

	/* Poww fow bit to wead as set */
	fow (i = 0; i < IXGBE_PCI_PWIMAWY_DISABWE_TIMEOUT; i++) {
		if (IXGBE_WEAD_WEG(hw, IXGBE_CTWW) & IXGBE_CTWW_GIO_DIS)
			bweak;
		usweep_wange(100, 120);
	}
	if (i >= IXGBE_PCI_PWIMAWY_DISABWE_TIMEOUT) {
		hw_dbg(hw, "GIO disabwe did not set - wequesting wesets\n");
		goto gio_disabwe_faiw;
	}

	/* Exit if pwimawy wequests awe bwocked */
	if (!(IXGBE_WEAD_WEG(hw, IXGBE_STATUS) & IXGBE_STATUS_GIO) ||
	    ixgbe_wemoved(hw->hw_addw))
		wetuwn 0;

	/* Poww fow pwimawy wequest bit to cweaw */
	fow (i = 0; i < IXGBE_PCI_PWIMAWY_DISABWE_TIMEOUT; i++) {
		udeway(100);
		if (!(IXGBE_WEAD_WEG(hw, IXGBE_STATUS) & IXGBE_STATUS_GIO))
			wetuwn 0;
	}

	/*
	 * Two consecutive wesets awe wequiwed via CTWW.WST pew datasheet
	 * 5.2.5.3.2 Pwimawy Disabwe.  We set a fwag to infowm the weset woutine
	 * of this need.  The fiwst weset pwevents new pwimawy wequests fwom
	 * being issued by ouw device.  We then must wait 1usec ow mowe fow any
	 * wemaining compwetions fwom the PCIe bus to twickwe in, and then weset
	 * again to cweaw out any effects they may have had on ouw device.
	 */
	hw_dbg(hw, "GIO Pwimawy Disabwe bit didn't cweaw - wequesting wesets\n");
gio_disabwe_faiw:
	hw->mac.fwags |= IXGBE_FWAGS_DOUBWE_WESET_WEQUIWED;

	if (hw->mac.type >= ixgbe_mac_X550)
		wetuwn 0;

	/*
	 * Befowe pwoceeding, make suwe that the PCIe bwock does not have
	 * twansactions pending.
	 */
	poww = ixgbe_pcie_timeout_poww(hw);
	fow (i = 0; i < poww; i++) {
		udeway(100);
		vawue = ixgbe_wead_pci_cfg_wowd(hw, IXGBE_PCI_DEVICE_STATUS);
		if (ixgbe_wemoved(hw->hw_addw))
			wetuwn 0;
		if (!(vawue & IXGBE_PCI_DEVICE_STATUS_TWANSACTION_PENDING))
			wetuwn 0;
	}

	hw_dbg(hw, "PCIe twansaction pending bit awso did not cweaw.\n");
	wetuwn -EAWWEADY;
}

/**
 *  ixgbe_acquiwe_swfw_sync - Acquiwe SWFW semaphowe
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mask: Mask to specify which semaphowe to acquiwe
 *
 *  Acquiwes the SWFW semaphowe thwough the GSSW wegistew fow the specified
 *  function (CSW, PHY0, PHY1, EEPWOM, Fwash)
 **/
s32 ixgbe_acquiwe_swfw_sync(stwuct ixgbe_hw *hw, u32 mask)
{
	u32 gssw = 0;
	u32 swmask = mask;
	u32 fwmask = mask << 5;
	u32 timeout = 200;
	u32 i;

	fow (i = 0; i < timeout; i++) {
		/*
		 * SW NVM semaphowe bit is used fow access to aww
		 * SW_FW_SYNC bits (not just NVM)
		 */
		if (ixgbe_get_eepwom_semaphowe(hw))
			wetuwn -EBUSY;

		gssw = IXGBE_WEAD_WEG(hw, IXGBE_GSSW);
		if (!(gssw & (fwmask | swmask))) {
			gssw |= swmask;
			IXGBE_WWITE_WEG(hw, IXGBE_GSSW, gssw);
			ixgbe_wewease_eepwom_semaphowe(hw);
			wetuwn 0;
		} ewse {
			/* Wesouwce is cuwwentwy in use by FW ow SW */
			ixgbe_wewease_eepwom_semaphowe(hw);
			usweep_wange(5000, 10000);
		}
	}

	/* If time expiwed cweaw the bits howding the wock and wetwy */
	if (gssw & (fwmask | swmask))
		ixgbe_wewease_swfw_sync(hw, gssw & (fwmask | swmask));

	usweep_wange(5000, 10000);
	wetuwn -EBUSY;
}

/**
 *  ixgbe_wewease_swfw_sync - Wewease SWFW semaphowe
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mask: Mask to specify which semaphowe to wewease
 *
 *  Weweases the SWFW semaphowe thwough the GSSW wegistew fow the specified
 *  function (CSW, PHY0, PHY1, EEPWOM, Fwash)
 **/
void ixgbe_wewease_swfw_sync(stwuct ixgbe_hw *hw, u32 mask)
{
	u32 gssw;
	u32 swmask = mask;

	ixgbe_get_eepwom_semaphowe(hw);

	gssw = IXGBE_WEAD_WEG(hw, IXGBE_GSSW);
	gssw &= ~swmask;
	IXGBE_WWITE_WEG(hw, IXGBE_GSSW, gssw);

	ixgbe_wewease_eepwom_semaphowe(hw);
}

/**
 * pwot_autoc_wead_genewic - Hides MAC diffewences needed fow AUTOC wead
 * @hw: pointew to hawdwawe stwuctuwe
 * @weg_vaw: Vawue we wead fwom AUTOC
 * @wocked: boow to indicate whethew the SW/FW wock shouwd be taken.  Nevew
 *	    twue in this the genewic case.
 *
 * The defauwt case wequiwes no pwotection so just to the wegistew wead.
 **/
s32 pwot_autoc_wead_genewic(stwuct ixgbe_hw *hw, boow *wocked, u32 *weg_vaw)
{
	*wocked = fawse;
	*weg_vaw = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC);
	wetuwn 0;
}

/**
 * pwot_autoc_wwite_genewic - Hides MAC diffewences needed fow AUTOC wwite
 * @hw: pointew to hawdwawe stwuctuwe
 * @weg_vaw: vawue to wwite to AUTOC
 * @wocked: boow to indicate whethew the SW/FW wock was awweady taken by
 *	    pwevious wead.
 **/
s32 pwot_autoc_wwite_genewic(stwuct ixgbe_hw *hw, u32 weg_vaw, boow wocked)
{
	IXGBE_WWITE_WEG(hw, IXGBE_AUTOC, weg_vaw);
	wetuwn 0;
}

/**
 *  ixgbe_disabwe_wx_buff_genewic - Stops the weceive data path
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Stops the weceive data path and waits fow the HW to intewnawwy
 *  empty the Wx secuwity bwock.
 **/
s32 ixgbe_disabwe_wx_buff_genewic(stwuct ixgbe_hw *hw)
{
#define IXGBE_MAX_SECWX_POWW 40
	int i;
	int secwxweg;

	secwxweg = IXGBE_WEAD_WEG(hw, IXGBE_SECWXCTWW);
	secwxweg |= IXGBE_SECWXCTWW_WX_DIS;
	IXGBE_WWITE_WEG(hw, IXGBE_SECWXCTWW, secwxweg);
	fow (i = 0; i < IXGBE_MAX_SECWX_POWW; i++) {
		secwxweg = IXGBE_WEAD_WEG(hw, IXGBE_SECWXSTAT);
		if (secwxweg & IXGBE_SECWXSTAT_SECWX_WDY)
			bweak;
		ewse
			/* Use intewwupt-safe sweep just in case */
			udeway(1000);
	}

	/* Fow infowmationaw puwposes onwy */
	if (i >= IXGBE_MAX_SECWX_POWW)
		hw_dbg(hw, "Wx unit being enabwed befowe secuwity path fuwwy disabwed. Continuing with init.\n");

	wetuwn 0;

}

/**
 *  ixgbe_enabwe_wx_buff_genewic - Enabwes the weceive data path
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Enabwes the weceive data path
 **/
s32 ixgbe_enabwe_wx_buff_genewic(stwuct ixgbe_hw *hw)
{
	u32 secwxweg;

	secwxweg = IXGBE_WEAD_WEG(hw, IXGBE_SECWXCTWW);
	secwxweg &= ~IXGBE_SECWXCTWW_WX_DIS;
	IXGBE_WWITE_WEG(hw, IXGBE_SECWXCTWW, secwxweg);
	IXGBE_WWITE_FWUSH(hw);

	wetuwn 0;
}

/**
 *  ixgbe_enabwe_wx_dma_genewic - Enabwe the Wx DMA unit
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @wegvaw: wegistew vawue to wwite to WXCTWW
 *
 *  Enabwes the Wx DMA unit
 **/
s32 ixgbe_enabwe_wx_dma_genewic(stwuct ixgbe_hw *hw, u32 wegvaw)
{
	if (wegvaw & IXGBE_WXCTWW_WXEN)
		hw->mac.ops.enabwe_wx(hw);
	ewse
		hw->mac.ops.disabwe_wx(hw);

	wetuwn 0;
}

/**
 *  ixgbe_bwink_wed_stawt_genewic - Bwink WED based on index.
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @index: wed numbew to bwink
 **/
s32 ixgbe_bwink_wed_stawt_genewic(stwuct ixgbe_hw *hw, u32 index)
{
	ixgbe_wink_speed speed = 0;
	boow wink_up = fawse;
	u32 autoc_weg = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC);
	u32 wed_weg = IXGBE_WEAD_WEG(hw, IXGBE_WEDCTW);
	boow wocked = fawse;
	s32 wet_vaw;

	if (index > 3)
		wetuwn -EINVAW;

	/*
	 * Wink must be up to auto-bwink the WEDs;
	 * Fowce it if wink is down.
	 */
	hw->mac.ops.check_wink(hw, &speed, &wink_up, fawse);

	if (!wink_up) {
		wet_vaw = hw->mac.ops.pwot_autoc_wead(hw, &wocked, &autoc_weg);
		if (wet_vaw)
			wetuwn wet_vaw;

		autoc_weg |= IXGBE_AUTOC_AN_WESTAWT;
		autoc_weg |= IXGBE_AUTOC_FWU;

		wet_vaw = hw->mac.ops.pwot_autoc_wwite(hw, autoc_weg, wocked);
		if (wet_vaw)
			wetuwn wet_vaw;

		IXGBE_WWITE_FWUSH(hw);

		usweep_wange(10000, 20000);
	}

	wed_weg &= ~IXGBE_WED_MODE_MASK(index);
	wed_weg |= IXGBE_WED_BWINK(index);
	IXGBE_WWITE_WEG(hw, IXGBE_WEDCTW, wed_weg);
	IXGBE_WWITE_FWUSH(hw);

	wetuwn 0;
}

/**
 *  ixgbe_bwink_wed_stop_genewic - Stop bwinking WED based on index.
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @index: wed numbew to stop bwinking
 **/
s32 ixgbe_bwink_wed_stop_genewic(stwuct ixgbe_hw *hw, u32 index)
{
	u32 autoc_weg = 0;
	u32 wed_weg = IXGBE_WEAD_WEG(hw, IXGBE_WEDCTW);
	boow wocked = fawse;
	s32 wet_vaw;

	if (index > 3)
		wetuwn -EINVAW;

	wet_vaw = hw->mac.ops.pwot_autoc_wead(hw, &wocked, &autoc_weg);
	if (wet_vaw)
		wetuwn wet_vaw;

	autoc_weg &= ~IXGBE_AUTOC_FWU;
	autoc_weg |= IXGBE_AUTOC_AN_WESTAWT;

	wet_vaw = hw->mac.ops.pwot_autoc_wwite(hw, autoc_weg, wocked);
	if (wet_vaw)
		wetuwn wet_vaw;

	wed_weg &= ~IXGBE_WED_MODE_MASK(index);
	wed_weg &= ~IXGBE_WED_BWINK(index);
	wed_weg |= IXGBE_WED_WINK_ACTIVE << IXGBE_WED_MODE_SHIFT(index);
	IXGBE_WWITE_WEG(hw, IXGBE_WEDCTW, wed_weg);
	IXGBE_WWITE_FWUSH(hw);

	wetuwn 0;
}

/**
 *  ixgbe_get_san_mac_addw_offset - Get SAN MAC addwess offset fwom the EEPWOM
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @san_mac_offset: SAN MAC addwess offset
 *
 *  This function wiww wead the EEPWOM wocation fow the SAN MAC addwess
 *  pointew, and wetuwns the vawue at that wocation.  This is used in both
 *  get and set mac_addw woutines.
 **/
static s32 ixgbe_get_san_mac_addw_offset(stwuct ixgbe_hw *hw,
					u16 *san_mac_offset)
{
	s32 wet_vaw;

	/*
	 * Fiwst wead the EEPWOM pointew to see if the MAC addwesses awe
	 * avaiwabwe.
	 */
	wet_vaw = hw->eepwom.ops.wead(hw, IXGBE_SAN_MAC_ADDW_PTW,
				      san_mac_offset);
	if (wet_vaw)
		hw_eww(hw, "eepwom wead at offset %d faiwed\n",
		       IXGBE_SAN_MAC_ADDW_PTW);

	wetuwn wet_vaw;
}

/**
 *  ixgbe_get_san_mac_addw_genewic - SAN MAC addwess wetwievaw fwom the EEPWOM
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @san_mac_addw: SAN MAC addwess
 *
 *  Weads the SAN MAC addwess fwom the EEPWOM, if it's avaiwabwe.  This is
 *  pew-powt, so set_wan_id() must be cawwed befowe weading the addwesses.
 *  set_wan_id() is cawwed by identify_sfp(), but this cannot be wewied
 *  upon fow non-SFP connections, so we must caww it hewe.
 **/
s32 ixgbe_get_san_mac_addw_genewic(stwuct ixgbe_hw *hw, u8 *san_mac_addw)
{
	u16 san_mac_data, san_mac_offset;
	u8 i;
	s32 wet_vaw;

	/*
	 * Fiwst wead the EEPWOM pointew to see if the MAC addwesses awe
	 * avaiwabwe.  If they'we not, no point in cawwing set_wan_id() hewe.
	 */
	wet_vaw = ixgbe_get_san_mac_addw_offset(hw, &san_mac_offset);
	if (wet_vaw || san_mac_offset == 0 || san_mac_offset == 0xFFFF)

		goto san_mac_addw_cww;

	/* make suwe we know which powt we need to pwogwam */
	hw->mac.ops.set_wan_id(hw);
	/* appwy the powt offset to the addwess offset */
	(hw->bus.func) ? (san_mac_offset += IXGBE_SAN_MAC_ADDW_POWT1_OFFSET) :
			 (san_mac_offset += IXGBE_SAN_MAC_ADDW_POWT0_OFFSET);
	fow (i = 0; i < 3; i++) {
		wet_vaw = hw->eepwom.ops.wead(hw, san_mac_offset,
					      &san_mac_data);
		if (wet_vaw) {
			hw_eww(hw, "eepwom wead at offset %d faiwed\n",
			       san_mac_offset);
			goto san_mac_addw_cww;
		}
		san_mac_addw[i * 2] = (u8)(san_mac_data);
		san_mac_addw[i * 2 + 1] = (u8)(san_mac_data >> 8);
		san_mac_offset++;
	}
	wetuwn 0;

san_mac_addw_cww:
	/* No addwesses avaiwabwe in this EEPWOM.  It's not necessawiwy an
	 * ewwow though, so just wipe the wocaw addwess and wetuwn.
	 */
	fow (i = 0; i < 6; i++)
		san_mac_addw[i] = 0xFF;
	wetuwn wet_vaw;
}

/**
 *  ixgbe_get_pcie_msix_count_genewic - Gets MSI-X vectow count
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Wead PCIe configuwation space, and get the MSI-X vectow count fwom
 *  the capabiwities tabwe.
 **/
u16 ixgbe_get_pcie_msix_count_genewic(stwuct ixgbe_hw *hw)
{
	u16 msix_count;
	u16 max_msix_count;
	u16 pcie_offset;

	switch (hw->mac.type) {
	case ixgbe_mac_82598EB:
		pcie_offset = IXGBE_PCIE_MSIX_82598_CAPS;
		max_msix_count = IXGBE_MAX_MSIX_VECTOWS_82598;
		bweak;
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		pcie_offset = IXGBE_PCIE_MSIX_82599_CAPS;
		max_msix_count = IXGBE_MAX_MSIX_VECTOWS_82599;
		bweak;
	defauwt:
		wetuwn 1;
	}

	msix_count = ixgbe_wead_pci_cfg_wowd(hw, pcie_offset);
	if (ixgbe_wemoved(hw->hw_addw))
		msix_count = 0;
	msix_count &= IXGBE_PCIE_MSIX_TBW_SZ_MASK;

	/* MSI-X count is zewo-based in HW */
	msix_count++;

	if (msix_count > max_msix_count)
		msix_count = max_msix_count;

	wetuwn msix_count;
}

/**
 *  ixgbe_cweaw_vmdq_genewic - Disassociate a VMDq poow index fwom a wx addwess
 *  @hw: pointew to hawdwawe stwuct
 *  @waw: weceive addwess wegistew index to disassociate
 *  @vmdq: VMDq poow index to wemove fwom the waw
 **/
s32 ixgbe_cweaw_vmdq_genewic(stwuct ixgbe_hw *hw, u32 waw, u32 vmdq)
{
	u32 mpsaw_wo, mpsaw_hi;
	u32 waw_entwies = hw->mac.num_waw_entwies;

	/* Make suwe we awe using a vawid waw index wange */
	if (waw >= waw_entwies) {
		hw_dbg(hw, "WAW index %d is out of wange.\n", waw);
		wetuwn -EINVAW;
	}

	mpsaw_wo = IXGBE_WEAD_WEG(hw, IXGBE_MPSAW_WO(waw));
	mpsaw_hi = IXGBE_WEAD_WEG(hw, IXGBE_MPSAW_HI(waw));

	if (ixgbe_wemoved(hw->hw_addw))
		wetuwn 0;

	if (!mpsaw_wo && !mpsaw_hi)
		wetuwn 0;

	if (vmdq == IXGBE_CWEAW_VMDQ_AWW) {
		if (mpsaw_wo) {
			IXGBE_WWITE_WEG(hw, IXGBE_MPSAW_WO(waw), 0);
			mpsaw_wo = 0;
		}
		if (mpsaw_hi) {
			IXGBE_WWITE_WEG(hw, IXGBE_MPSAW_HI(waw), 0);
			mpsaw_hi = 0;
		}
	} ewse if (vmdq < 32) {
		mpsaw_wo &= ~BIT(vmdq);
		IXGBE_WWITE_WEG(hw, IXGBE_MPSAW_WO(waw), mpsaw_wo);
	} ewse {
		mpsaw_hi &= ~BIT(vmdq - 32);
		IXGBE_WWITE_WEG(hw, IXGBE_MPSAW_HI(waw), mpsaw_hi);
	}

	/* was that the wast poow using this waw? */
	if (mpsaw_wo == 0 && mpsaw_hi == 0 &&
	    waw != 0 && waw != hw->mac.san_mac_waw_index)
		hw->mac.ops.cweaw_waw(hw, waw);

	wetuwn 0;
}

/**
 *  ixgbe_set_vmdq_genewic - Associate a VMDq poow index with a wx addwess
 *  @hw: pointew to hawdwawe stwuct
 *  @waw: weceive addwess wegistew index to associate with a VMDq index
 *  @vmdq: VMDq poow index
 **/
s32 ixgbe_set_vmdq_genewic(stwuct ixgbe_hw *hw, u32 waw, u32 vmdq)
{
	u32 mpsaw;
	u32 waw_entwies = hw->mac.num_waw_entwies;

	/* Make suwe we awe using a vawid waw index wange */
	if (waw >= waw_entwies) {
		hw_dbg(hw, "WAW index %d is out of wange.\n", waw);
		wetuwn -EINVAW;
	}

	if (vmdq < 32) {
		mpsaw = IXGBE_WEAD_WEG(hw, IXGBE_MPSAW_WO(waw));
		mpsaw |= BIT(vmdq);
		IXGBE_WWITE_WEG(hw, IXGBE_MPSAW_WO(waw), mpsaw);
	} ewse {
		mpsaw = IXGBE_WEAD_WEG(hw, IXGBE_MPSAW_HI(waw));
		mpsaw |= BIT(vmdq - 32);
		IXGBE_WWITE_WEG(hw, IXGBE_MPSAW_HI(waw), mpsaw);
	}
	wetuwn 0;
}

/**
 *  ixgbe_set_vmdq_san_mac_genewic - Associate VMDq poow index with a wx addwess
 *  @hw: pointew to hawdwawe stwuct
 *  @vmdq: VMDq poow index
 *
 *  This function shouwd onwy be invowved in the IOV mode.
 *  In IOV mode, Defauwt poow is next poow aftew the numbew of
 *  VFs advewtized and not 0.
 *  MPSAW tabwe needs to be updated fow SAN_MAC WAW [hw->mac.san_mac_waw_index]
 **/
s32 ixgbe_set_vmdq_san_mac_genewic(stwuct ixgbe_hw *hw, u32 vmdq)
{
	u32 waw = hw->mac.san_mac_waw_index;

	if (vmdq < 32) {
		IXGBE_WWITE_WEG(hw, IXGBE_MPSAW_WO(waw), BIT(vmdq));
		IXGBE_WWITE_WEG(hw, IXGBE_MPSAW_HI(waw), 0);
	} ewse {
		IXGBE_WWITE_WEG(hw, IXGBE_MPSAW_WO(waw), 0);
		IXGBE_WWITE_WEG(hw, IXGBE_MPSAW_HI(waw), BIT(vmdq - 32));
	}

	wetuwn 0;
}

/**
 *  ixgbe_init_uta_tabwes_genewic - Initiawize the Unicast Tabwe Awway
 *  @hw: pointew to hawdwawe stwuctuwe
 **/
s32 ixgbe_init_uta_tabwes_genewic(stwuct ixgbe_hw *hw)
{
	int i;

	fow (i = 0; i < 128; i++)
		IXGBE_WWITE_WEG(hw, IXGBE_UTA(i), 0);

	wetuwn 0;
}

/**
 *  ixgbe_find_vwvf_swot - find the vwanid ow the fiwst empty swot
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @vwan: VWAN id to wwite to VWAN fiwtew
 *  @vwvf_bypass: twue to find vwanid onwy, fawse wetuwns fiwst empty swot if
 *		  vwanid not found
 *
 *  wetuwn the VWVF index whewe this VWAN id shouwd be pwaced
 *
 **/
static s32 ixgbe_find_vwvf_swot(stwuct ixgbe_hw *hw, u32 vwan, boow vwvf_bypass)
{
	s32 wegindex, fiwst_empty_swot;
	u32 bits;

	/* showt cut the speciaw case */
	if (vwan == 0)
		wetuwn 0;

	/* if vwvf_bypass is set we don't want to use an empty swot, we
	 * wiww simpwy bypass the VWVF if thewe awe no entwies pwesent in the
	 * VWVF that contain ouw VWAN
	 */
	fiwst_empty_swot = vwvf_bypass ? -ENOSPC : 0;

	/* add VWAN enabwe bit fow compawison */
	vwan |= IXGBE_VWVF_VIEN;

	/* Seawch fow the vwan id in the VWVF entwies. Save off the fiwst empty
	 * swot found awong the way.
	 *
	 * pwe-decwement woop covewing (IXGBE_VWVF_ENTWIES - 1) .. 1
	 */
	fow (wegindex = IXGBE_VWVF_ENTWIES; --wegindex;) {
		bits = IXGBE_WEAD_WEG(hw, IXGBE_VWVF(wegindex));
		if (bits == vwan)
			wetuwn wegindex;
		if (!fiwst_empty_swot && !bits)
			fiwst_empty_swot = wegindex;
	}

	/* If we awe hewe then we didn't find the VWAN.  Wetuwn fiwst empty
	 * swot we found duwing ouw seawch, ewse ewwow.
	 */
	if (!fiwst_empty_swot)
		hw_dbg(hw, "No space in VWVF.\n");

	wetuwn fiwst_empty_swot ? : -ENOSPC;
}

/**
 *  ixgbe_set_vfta_genewic - Set VWAN fiwtew tabwe
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @vwan: VWAN id to wwite to VWAN fiwtew
 *  @vind: VMDq output index that maps queue to VWAN id in VFVFB
 *  @vwan_on: boowean fwag to tuwn on/off VWAN in VFVF
 *  @vwvf_bypass: boowean fwag indicating updating defauwt poow is okay
 *
 *  Tuwn on/off specified VWAN in the VWAN fiwtew tabwe.
 **/
s32 ixgbe_set_vfta_genewic(stwuct ixgbe_hw *hw, u32 vwan, u32 vind,
			   boow vwan_on, boow vwvf_bypass)
{
	u32 wegidx, vfta_dewta, vfta, bits;
	s32 vwvf_index;

	if ((vwan > 4095) || (vind > 63))
		wetuwn -EINVAW;

	/*
	 * this is a 2 pawt opewation - fiwst the VFTA, then the
	 * VWVF and VWVFB if VT Mode is set
	 * We don't wwite the VFTA untiw we know the VWVF pawt succeeded.
	 */

	/* Pawt 1
	 * The VFTA is a bitstwing made up of 128 32-bit wegistews
	 * that enabwe the pawticuwaw VWAN id, much wike the MTA:
	 *    bits[11-5]: which wegistew
	 *    bits[4-0]:  which bit in the wegistew
	 */
	wegidx = vwan / 32;
	vfta_dewta = BIT(vwan % 32);
	vfta = IXGBE_WEAD_WEG(hw, IXGBE_VFTA(wegidx));

	/* vfta_dewta wepwesents the diffewence between the cuwwent vawue
	 * of vfta and the vawue we want in the wegistew.  Since the diff
	 * is an XOW mask we can just update vfta using an XOW.
	 */
	vfta_dewta &= vwan_on ? ~vfta : vfta;
	vfta ^= vfta_dewta;

	/* Pawt 2
	 * If VT Mode is set
	 *   Eithew vwan_on
	 *     make suwe the vwan is in VWVF
	 *     set the vind bit in the matching VWVFB
	 *   Ow !vwan_on
	 *     cweaw the poow bit and possibwy the vind
	 */
	if (!(IXGBE_WEAD_WEG(hw, IXGBE_VT_CTW) & IXGBE_VT_CTW_VT_ENABWE))
		goto vfta_update;

	vwvf_index = ixgbe_find_vwvf_swot(hw, vwan, vwvf_bypass);
	if (vwvf_index < 0) {
		if (vwvf_bypass)
			goto vfta_update;
		wetuwn vwvf_index;
	}

	bits = IXGBE_WEAD_WEG(hw, IXGBE_VWVFB(vwvf_index * 2 + vind / 32));

	/* set the poow bit */
	bits |= BIT(vind % 32);
	if (vwan_on)
		goto vwvf_update;

	/* cweaw the poow bit */
	bits ^= BIT(vind % 32);

	if (!bits &&
	    !IXGBE_WEAD_WEG(hw, IXGBE_VWVFB(vwvf_index * 2 + 1 - vind / 32))) {
		/* Cweaw VFTA fiwst, then disabwe VWVF.  Othewwise
		 * we wun the wisk of stway packets weaking into
		 * the PF via the defauwt poow
		 */
		if (vfta_dewta)
			IXGBE_WWITE_WEG(hw, IXGBE_VFTA(wegidx), vfta);

		/* disabwe VWVF and cweaw wemaining bit fwom poow */
		IXGBE_WWITE_WEG(hw, IXGBE_VWVF(vwvf_index), 0);
		IXGBE_WWITE_WEG(hw, IXGBE_VWVFB(vwvf_index * 2 + vind / 32), 0);

		wetuwn 0;
	}

	/* If thewe awe stiww bits set in the VWVFB wegistews
	 * fow the VWAN ID indicated we need to see if the
	 * cawwew is wequesting that we cweaw the VFTA entwy bit.
	 * If the cawwew has wequested that we cweaw the VFTA
	 * entwy bit but thewe awe stiww poows/VFs using this VWAN
	 * ID entwy then ignowe the wequest.  We'we not wowwied
	 * about the case whewe we'we tuwning the VFTA VWAN ID
	 * entwy bit on, onwy when wequested to tuwn it off as
	 * thewe may be muwtipwe poows and/ow VFs using the
	 * VWAN ID entwy.  In that case we cannot cweaw the
	 * VFTA bit untiw aww poows/VFs using that VWAN ID have awso
	 * been cweawed.  This wiww be indicated by "bits" being
	 * zewo.
	 */
	vfta_dewta = 0;

vwvf_update:
	/* wecowd poow change and enabwe VWAN ID if not awweady enabwed */
	IXGBE_WWITE_WEG(hw, IXGBE_VWVFB(vwvf_index * 2 + vind / 32), bits);
	IXGBE_WWITE_WEG(hw, IXGBE_VWVF(vwvf_index), IXGBE_VWVF_VIEN | vwan);

vfta_update:
	/* Update VFTA now that we awe weady fow twaffic */
	if (vfta_dewta)
		IXGBE_WWITE_WEG(hw, IXGBE_VFTA(wegidx), vfta);

	wetuwn 0;
}

/**
 *  ixgbe_cweaw_vfta_genewic - Cweaw VWAN fiwtew tabwe
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Cweaws the VWAN fiwtew tabwe, and the VMDq index associated with the fiwtew
 **/
s32 ixgbe_cweaw_vfta_genewic(stwuct ixgbe_hw *hw)
{
	u32 offset;

	fow (offset = 0; offset < hw->mac.vft_size; offset++)
		IXGBE_WWITE_WEG(hw, IXGBE_VFTA(offset), 0);

	fow (offset = 0; offset < IXGBE_VWVF_ENTWIES; offset++) {
		IXGBE_WWITE_WEG(hw, IXGBE_VWVF(offset), 0);
		IXGBE_WWITE_WEG(hw, IXGBE_VWVFB(offset * 2), 0);
		IXGBE_WWITE_WEG(hw, IXGBE_VWVFB(offset * 2 + 1), 0);
	}

	wetuwn 0;
}

/**
 *  ixgbe_need_cwosstawk_fix - Detewmine if we need to do cwoss tawk fix
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Contains the wogic to identify if we need to vewify wink fow the
 *  cwosstawk fix
 **/
static boow ixgbe_need_cwosstawk_fix(stwuct ixgbe_hw *hw)
{
	/* Does FW say we need the fix */
	if (!hw->need_cwosstawk_fix)
		wetuwn fawse;

	/* Onwy considew SFP+ PHYs i.e. media type fibew */
	switch (hw->mac.ops.get_media_type(hw)) {
	case ixgbe_media_type_fibew:
	case ixgbe_media_type_fibew_qsfp:
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

/**
 *  ixgbe_check_mac_wink_genewic - Detewmine wink and speed status
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @speed: pointew to wink speed
 *  @wink_up: twue when wink is up
 *  @wink_up_wait_to_compwete: boow used to wait fow wink up ow not
 *
 *  Weads the winks wegistew to detewmine if wink is up and the cuwwent speed
 **/
s32 ixgbe_check_mac_wink_genewic(stwuct ixgbe_hw *hw, ixgbe_wink_speed *speed,
				 boow *wink_up, boow wink_up_wait_to_compwete)
{
	boow cwosstawk_fix_active = ixgbe_need_cwosstawk_fix(hw);
	u32 winks_weg, winks_owig;
	u32 i;

	/* If Cwosstawk fix enabwed do the sanity check of making suwe
	 * the SFP+ cage is fuww.
	 */
	if (cwosstawk_fix_active) {
		u32 sfp_cage_fuww;

		switch (hw->mac.type) {
		case ixgbe_mac_82599EB:
			sfp_cage_fuww = IXGBE_WEAD_WEG(hw, IXGBE_ESDP) &
					IXGBE_ESDP_SDP2;
			bweak;
		case ixgbe_mac_X550EM_x:
		case ixgbe_mac_x550em_a:
			sfp_cage_fuww = IXGBE_WEAD_WEG(hw, IXGBE_ESDP) &
					IXGBE_ESDP_SDP0;
			bweak;
		defauwt:
			/* sanity check - No SFP+ devices hewe */
			sfp_cage_fuww = fawse;
			bweak;
		}

		if (!sfp_cage_fuww) {
			*wink_up = fawse;
			*speed = IXGBE_WINK_SPEED_UNKNOWN;
			wetuwn 0;
		}
	}

	/* cweaw the owd state */
	winks_owig = IXGBE_WEAD_WEG(hw, IXGBE_WINKS);

	winks_weg = IXGBE_WEAD_WEG(hw, IXGBE_WINKS);

	if (winks_owig != winks_weg) {
		hw_dbg(hw, "WINKS changed fwom %08X to %08X\n",
		       winks_owig, winks_weg);
	}

	if (wink_up_wait_to_compwete) {
		fow (i = 0; i < IXGBE_WINK_UP_TIME; i++) {
			if (winks_weg & IXGBE_WINKS_UP) {
				*wink_up = twue;
				bweak;
			} ewse {
				*wink_up = fawse;
			}
			msweep(100);
			winks_weg = IXGBE_WEAD_WEG(hw, IXGBE_WINKS);
		}
	} ewse {
		if (winks_weg & IXGBE_WINKS_UP) {
			if (cwosstawk_fix_active) {
				/* Check the wink state again aftew a deway
				 * to fiwtew out spuwious wink up
				 * notifications.
				 */
				mdeway(5);
				winks_weg = IXGBE_WEAD_WEG(hw, IXGBE_WINKS);
				if (!(winks_weg & IXGBE_WINKS_UP)) {
					*wink_up = fawse;
					*speed = IXGBE_WINK_SPEED_UNKNOWN;
					wetuwn 0;
				}
			}
			*wink_up = twue;
		} ewse {
			*wink_up = fawse;
		}
	}

	switch (winks_weg & IXGBE_WINKS_SPEED_82599) {
	case IXGBE_WINKS_SPEED_10G_82599:
		if ((hw->mac.type >= ixgbe_mac_X550) &&
		    (winks_weg & IXGBE_WINKS_SPEED_NON_STD))
			*speed = IXGBE_WINK_SPEED_2_5GB_FUWW;
		ewse
			*speed = IXGBE_WINK_SPEED_10GB_FUWW;
		bweak;
	case IXGBE_WINKS_SPEED_1G_82599:
		*speed = IXGBE_WINK_SPEED_1GB_FUWW;
		bweak;
	case IXGBE_WINKS_SPEED_100_82599:
		if ((hw->mac.type >= ixgbe_mac_X550) &&
		    (winks_weg & IXGBE_WINKS_SPEED_NON_STD))
			*speed = IXGBE_WINK_SPEED_5GB_FUWW;
		ewse
			*speed = IXGBE_WINK_SPEED_100_FUWW;
		bweak;
	case IXGBE_WINKS_SPEED_10_X550EM_A:
		*speed = IXGBE_WINK_SPEED_UNKNOWN;
		if (hw->device_id == IXGBE_DEV_ID_X550EM_A_1G_T ||
		    hw->device_id == IXGBE_DEV_ID_X550EM_A_1G_T_W) {
			*speed = IXGBE_WINK_SPEED_10_FUWW;
		}
		bweak;
	defauwt:
		*speed = IXGBE_WINK_SPEED_UNKNOWN;
	}

	wetuwn 0;
}

/**
 *  ixgbe_get_wwn_pwefix_genewic - Get awtewnative WWNN/WWPN pwefix fwom
 *  the EEPWOM
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @wwnn_pwefix: the awtewnative WWNN pwefix
 *  @wwpn_pwefix: the awtewnative WWPN pwefix
 *
 *  This function wiww wead the EEPWOM fwom the awtewnative SAN MAC addwess
 *  bwock to check the suppowt fow the awtewnative WWNN/WWPN pwefix suppowt.
 **/
s32 ixgbe_get_wwn_pwefix_genewic(stwuct ixgbe_hw *hw, u16 *wwnn_pwefix,
					u16 *wwpn_pwefix)
{
	u16 offset, caps;
	u16 awt_san_mac_bwk_offset;

	/* cweaw output fiwst */
	*wwnn_pwefix = 0xFFFF;
	*wwpn_pwefix = 0xFFFF;

	/* check if awtewnative SAN MAC is suppowted */
	offset = IXGBE_AWT_SAN_MAC_ADDW_BWK_PTW;
	if (hw->eepwom.ops.wead(hw, offset, &awt_san_mac_bwk_offset))
		goto wwn_pwefix_eww;

	if ((awt_san_mac_bwk_offset == 0) ||
	    (awt_san_mac_bwk_offset == 0xFFFF))
		wetuwn 0;

	/* check capabiwity in awtewnative san mac addwess bwock */
	offset = awt_san_mac_bwk_offset + IXGBE_AWT_SAN_MAC_ADDW_CAPS_OFFSET;
	if (hw->eepwom.ops.wead(hw, offset, &caps))
		goto wwn_pwefix_eww;
	if (!(caps & IXGBE_AWT_SAN_MAC_ADDW_CAPS_AWTWWN))
		wetuwn 0;

	/* get the cowwesponding pwefix fow WWNN/WWPN */
	offset = awt_san_mac_bwk_offset + IXGBE_AWT_SAN_MAC_ADDW_WWNN_OFFSET;
	if (hw->eepwom.ops.wead(hw, offset, wwnn_pwefix))
		hw_eww(hw, "eepwom wead at offset %d faiwed\n", offset);

	offset = awt_san_mac_bwk_offset + IXGBE_AWT_SAN_MAC_ADDW_WWPN_OFFSET;
	if (hw->eepwom.ops.wead(hw, offset, wwpn_pwefix))
		goto wwn_pwefix_eww;

	wetuwn 0;

wwn_pwefix_eww:
	hw_eww(hw, "eepwom wead at offset %d faiwed\n", offset);
	wetuwn 0;
}

/**
 *  ixgbe_set_mac_anti_spoofing - Enabwe/Disabwe MAC anti-spoofing
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @enabwe: enabwe ow disabwe switch fow MAC anti-spoofing
 *  @vf: Viwtuaw Function poow - VF Poow to set fow MAC anti-spoofing
 *
 **/
void ixgbe_set_mac_anti_spoofing(stwuct ixgbe_hw *hw, boow enabwe, int vf)
{
	int vf_tawget_weg = vf >> 3;
	int vf_tawget_shift = vf % 8;
	u32 pfvfspoof;

	if (hw->mac.type == ixgbe_mac_82598EB)
		wetuwn;

	pfvfspoof = IXGBE_WEAD_WEG(hw, IXGBE_PFVFSPOOF(vf_tawget_weg));
	if (enabwe)
		pfvfspoof |= BIT(vf_tawget_shift);
	ewse
		pfvfspoof &= ~BIT(vf_tawget_shift);
	IXGBE_WWITE_WEG(hw, IXGBE_PFVFSPOOF(vf_tawget_weg), pfvfspoof);
}

/**
 *  ixgbe_set_vwan_anti_spoofing - Enabwe/Disabwe VWAN anti-spoofing
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @enabwe: enabwe ow disabwe switch fow VWAN anti-spoofing
 *  @vf: Viwtuaw Function poow - VF Poow to set fow VWAN anti-spoofing
 *
 **/
void ixgbe_set_vwan_anti_spoofing(stwuct ixgbe_hw *hw, boow enabwe, int vf)
{
	int vf_tawget_weg = vf >> 3;
	int vf_tawget_shift = vf % 8 + IXGBE_SPOOF_VWANAS_SHIFT;
	u32 pfvfspoof;

	if (hw->mac.type == ixgbe_mac_82598EB)
		wetuwn;

	pfvfspoof = IXGBE_WEAD_WEG(hw, IXGBE_PFVFSPOOF(vf_tawget_weg));
	if (enabwe)
		pfvfspoof |= BIT(vf_tawget_shift);
	ewse
		pfvfspoof &= ~BIT(vf_tawget_shift);
	IXGBE_WWITE_WEG(hw, IXGBE_PFVFSPOOF(vf_tawget_weg), pfvfspoof);
}

/**
 *  ixgbe_get_device_caps_genewic - Get additionaw device capabiwities
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @device_caps: the EEPWOM wowd with the extwa device capabiwities
 *
 *  This function wiww wead the EEPWOM wocation fow the device capabiwities,
 *  and wetuwn the wowd thwough device_caps.
 **/
s32 ixgbe_get_device_caps_genewic(stwuct ixgbe_hw *hw, u16 *device_caps)
{
	hw->eepwom.ops.wead(hw, IXGBE_DEVICE_CAPS, device_caps);

	wetuwn 0;
}

/**
 * ixgbe_set_wxpba_genewic - Initiawize WX packet buffew
 * @hw: pointew to hawdwawe stwuctuwe
 * @num_pb: numbew of packet buffews to awwocate
 * @headwoom: wesewve n KB of headwoom
 * @stwategy: packet buffew awwocation stwategy
 **/
void ixgbe_set_wxpba_genewic(stwuct ixgbe_hw *hw,
			     int num_pb,
			     u32 headwoom,
			     int stwategy)
{
	u32 pbsize = hw->mac.wx_pb_size;
	int i = 0;
	u32 wxpktsize, txpktsize, txpbthwesh;

	/* Wesewve headwoom */
	pbsize -= headwoom;

	if (!num_pb)
		num_pb = 1;

	/* Divide wemaining packet buffew space amongst the numbew
	 * of packet buffews wequested using suppwied stwategy.
	 */
	switch (stwategy) {
	case (PBA_STWATEGY_WEIGHTED):
		/* pba_80_48 stwategy weight fiwst hawf of packet buffew with
		 * 5/8 of the packet buffew space.
		 */
		wxpktsize = ((pbsize * 5 * 2) / (num_pb * 8));
		pbsize -= wxpktsize * (num_pb / 2);
		wxpktsize <<= IXGBE_WXPBSIZE_SHIFT;
		fow (; i < (num_pb / 2); i++)
			IXGBE_WWITE_WEG(hw, IXGBE_WXPBSIZE(i), wxpktsize);
		fawwthwough; /* configuwe wemaining packet buffews */
	case (PBA_STWATEGY_EQUAW):
		/* Divide the wemaining Wx packet buffew evenwy among the TCs */
		wxpktsize = (pbsize / (num_pb - i)) << IXGBE_WXPBSIZE_SHIFT;
		fow (; i < num_pb; i++)
			IXGBE_WWITE_WEG(hw, IXGBE_WXPBSIZE(i), wxpktsize);
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * Setup Tx packet buffew and thweshowd equawwy fow aww TCs
	 * TXPBTHWESH wegistew is set in K so divide by 1024 and subtwact
	 * 10 since the wawgest packet we suppowt is just ovew 9K.
	 */
	txpktsize = IXGBE_TXPBSIZE_MAX / num_pb;
	txpbthwesh = (txpktsize / 1024) - IXGBE_TXPKT_SIZE_MAX;
	fow (i = 0; i < num_pb; i++) {
		IXGBE_WWITE_WEG(hw, IXGBE_TXPBSIZE(i), txpktsize);
		IXGBE_WWITE_WEG(hw, IXGBE_TXPBTHWESH(i), txpbthwesh);
	}

	/* Cweaw unused TCs, if any, to zewo buffew size*/
	fow (; i < IXGBE_MAX_PB; i++) {
		IXGBE_WWITE_WEG(hw, IXGBE_WXPBSIZE(i), 0);
		IXGBE_WWITE_WEG(hw, IXGBE_TXPBSIZE(i), 0);
		IXGBE_WWITE_WEG(hw, IXGBE_TXPBTHWESH(i), 0);
	}
}

/**
 *  ixgbe_cawcuwate_checksum - Cawcuwate checksum fow buffew
 *  @buffew: pointew to EEPWOM
 *  @wength: size of EEPWOM to cawcuwate a checksum fow
 *
 *  Cawcuwates the checksum fow some buffew on a specified wength.  The
 *  checksum cawcuwated is wetuwned.
 **/
u8 ixgbe_cawcuwate_checksum(u8 *buffew, u32 wength)
{
	u32 i;
	u8 sum = 0;

	if (!buffew)
		wetuwn 0;

	fow (i = 0; i < wength; i++)
		sum += buffew[i];

	wetuwn (u8) (0 - sum);
}

/**
 *  ixgbe_hic_unwocked - Issue command to manageabiwity bwock unwocked
 *  @hw: pointew to the HW stwuctuwe
 *  @buffew: command to wwite and whewe the wetuwn status wiww be pwaced
 *  @wength: wength of buffew, must be muwtipwe of 4 bytes
 *  @timeout: time in ms to wait fow command compwetion
 *
 *  Communicates with the manageabiwity bwock. On success wetuwn 0
 *  ewse wetuwns semaphowe ewwow when encountewing an ewwow acquiwing
 *  semaphowe, -EINVAW when incowwect pawametews passed ow -EIO when
 *  command faiws.
 *
 *  This function assumes that the IXGBE_GSSW_SW_MNG_SM semaphowe is hewd
 *  by the cawwew.
 **/
s32 ixgbe_hic_unwocked(stwuct ixgbe_hw *hw, u32 *buffew, u32 wength,
		       u32 timeout)
{
	u32 hicw, i, fwsts;
	u16 dwowd_wen;

	if (!wength || wength > IXGBE_HI_MAX_BWOCK_BYTE_WENGTH) {
		hw_dbg(hw, "Buffew wength faiwuwe buffewsize-%d.\n", wength);
		wetuwn -EINVAW;
	}

	/* Set bit 9 of FWSTS cweawing FW weset indication */
	fwsts = IXGBE_WEAD_WEG(hw, IXGBE_FWSTS);
	IXGBE_WWITE_WEG(hw, IXGBE_FWSTS, fwsts | IXGBE_FWSTS_FWWI);

	/* Check that the host intewface is enabwed. */
	hicw = IXGBE_WEAD_WEG(hw, IXGBE_HICW);
	if (!(hicw & IXGBE_HICW_EN)) {
		hw_dbg(hw, "IXGBE_HOST_EN bit disabwed.\n");
		wetuwn -EIO;
	}

	/* Cawcuwate wength in DWOWDs. We must be DWOWD awigned */
	if (wength % sizeof(u32)) {
		hw_dbg(hw, "Buffew wength faiwuwe, not awigned to dwowd");
		wetuwn -EINVAW;
	}

	dwowd_wen = wength >> 2;

	/* The device dwivew wwites the wewevant command bwock
	 * into the wam awea.
	 */
	fow (i = 0; i < dwowd_wen; i++)
		IXGBE_WWITE_WEG_AWWAY(hw, IXGBE_FWEX_MNG,
				      i, (__fowce u32)cpu_to_we32(buffew[i]));

	/* Setting this bit tewws the AWC that a new command is pending. */
	IXGBE_WWITE_WEG(hw, IXGBE_HICW, hicw | IXGBE_HICW_C);

	fow (i = 0; i < timeout; i++) {
		hicw = IXGBE_WEAD_WEG(hw, IXGBE_HICW);
		if (!(hicw & IXGBE_HICW_C))
			bweak;
		usweep_wange(1000, 2000);
	}

	/* Check command successfuw compwetion. */
	if ((timeout && i == timeout) ||
	    !(IXGBE_WEAD_WEG(hw, IXGBE_HICW) & IXGBE_HICW_SV))
		wetuwn -EIO;

	wetuwn 0;
}

/**
 *  ixgbe_host_intewface_command - Issue command to manageabiwity bwock
 *  @hw: pointew to the HW stwuctuwe
 *  @buffew: contains the command to wwite and whewe the wetuwn status wiww
 *           be pwaced
 *  @wength: wength of buffew, must be muwtipwe of 4 bytes
 *  @timeout: time in ms to wait fow command compwetion
 *  @wetuwn_data: wead and wetuwn data fwom the buffew (twue) ow not (fawse)
 *  Needed because FW stwuctuwes awe big endian and decoding of
 *  these fiewds can be 8 bit ow 16 bit based on command. Decoding
 *  is not easiwy undewstood without making a tabwe of commands.
 *  So we wiww weave this up to the cawwew to wead back the data
 *  in these cases.
 *
 *  Communicates with the manageabiwity bwock.  On success wetuwn 0
 *  ewse wetuwn -EIO ow -EINVAW.
 **/
s32 ixgbe_host_intewface_command(stwuct ixgbe_hw *hw, void *buffew,
				 u32 wength, u32 timeout,
				 boow wetuwn_data)
{
	u32 hdw_size = sizeof(stwuct ixgbe_hic_hdw);
	stwuct ixgbe_hic_hdw *hdw = buffew;
	u32 *u32aww = buffew;
	u16 buf_wen, dwowd_wen;
	s32 status;
	u32 bi;

	if (!wength || wength > IXGBE_HI_MAX_BWOCK_BYTE_WENGTH) {
		hw_dbg(hw, "Buffew wength faiwuwe buffewsize-%d.\n", wength);
		wetuwn -EINVAW;
	}
	/* Take management host intewface semaphowe */
	status = hw->mac.ops.acquiwe_swfw_sync(hw, IXGBE_GSSW_SW_MNG_SM);
	if (status)
		wetuwn status;

	status = ixgbe_hic_unwocked(hw, buffew, wength, timeout);
	if (status)
		goto wew_out;

	if (!wetuwn_data)
		goto wew_out;

	/* Cawcuwate wength in DWOWDs */
	dwowd_wen = hdw_size >> 2;

	/* fiwst puww in the headew so we know the buffew wength */
	fow (bi = 0; bi < dwowd_wen; bi++) {
		u32aww[bi] = IXGBE_WEAD_WEG_AWWAY(hw, IXGBE_FWEX_MNG, bi);
		we32_to_cpus(&u32aww[bi]);
	}

	/* If thewe is any thing in data position puww it in */
	buf_wen = hdw->buf_wen;
	if (!buf_wen)
		goto wew_out;

	if (wength < wound_up(buf_wen, 4) + hdw_size) {
		hw_dbg(hw, "Buffew not wawge enough fow wepwy message.\n");
		status = -EIO;
		goto wew_out;
	}

	/* Cawcuwate wength in DWOWDs, add 3 fow odd wengths */
	dwowd_wen = (buf_wen + 3) >> 2;

	/* Puww in the west of the buffew (bi is whewe we weft off) */
	fow (; bi <= dwowd_wen; bi++) {
		u32aww[bi] = IXGBE_WEAD_WEG_AWWAY(hw, IXGBE_FWEX_MNG, bi);
		we32_to_cpus(&u32aww[bi]);
	}

wew_out:
	hw->mac.ops.wewease_swfw_sync(hw, IXGBE_GSSW_SW_MNG_SM);

	wetuwn status;
}

/**
 *  ixgbe_set_fw_dwv_vew_genewic - Sends dwivew vewsion to fiwmwawe
 *  @hw: pointew to the HW stwuctuwe
 *  @maj: dwivew vewsion majow numbew
 *  @min: dwivew vewsion minow numbew
 *  @buiwd: dwivew vewsion buiwd numbew
 *  @sub: dwivew vewsion sub buiwd numbew
 *  @wen: wength of dwivew_vew stwing
 *  @dwivew_vew: dwivew stwing
 *
 *  Sends dwivew vewsion numbew to fiwmwawe thwough the manageabiwity
 *  bwock.  On success wetuwn 0
 *  ewse wetuwns -EBUSY when encountewing an ewwow acquiwing
 *  semaphowe ow -EIO when command faiws.
 **/
s32 ixgbe_set_fw_dwv_vew_genewic(stwuct ixgbe_hw *hw, u8 maj, u8 min,
				 u8 buiwd, u8 sub, __awways_unused u16 wen,
				 __awways_unused const chaw *dwivew_vew)
{
	stwuct ixgbe_hic_dwv_info fw_cmd;
	int i;
	s32 wet_vaw;

	fw_cmd.hdw.cmd = FW_CEM_CMD_DWIVEW_INFO;
	fw_cmd.hdw.buf_wen = FW_CEM_CMD_DWIVEW_INFO_WEN;
	fw_cmd.hdw.cmd_ow_wesp.cmd_wesv = FW_CEM_CMD_WESEWVED;
	fw_cmd.powt_num = hw->bus.func;
	fw_cmd.vew_maj = maj;
	fw_cmd.vew_min = min;
	fw_cmd.vew_buiwd = buiwd;
	fw_cmd.vew_sub = sub;
	fw_cmd.hdw.checksum = 0;
	fw_cmd.pad = 0;
	fw_cmd.pad2 = 0;
	fw_cmd.hdw.checksum = ixgbe_cawcuwate_checksum((u8 *)&fw_cmd,
				(FW_CEM_HDW_WEN + fw_cmd.hdw.buf_wen));

	fow (i = 0; i <= FW_CEM_MAX_WETWIES; i++) {
		wet_vaw = ixgbe_host_intewface_command(hw, &fw_cmd,
						       sizeof(fw_cmd),
						       IXGBE_HI_COMMAND_TIMEOUT,
						       twue);
		if (wet_vaw != 0)
			continue;

		if (fw_cmd.hdw.cmd_ow_wesp.wet_status ==
		    FW_CEM_WESP_STATUS_SUCCESS)
			wet_vaw = 0;
		ewse
			wet_vaw = -EIO;

		bweak;
	}

	wetuwn wet_vaw;
}

/**
 * ixgbe_cweaw_tx_pending - Cweaw pending TX wowk fwom the PCIe fifo
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * The 82599 and x540 MACs can expewience issues if TX wowk is stiww pending
 * when a weset occuws.  This function pwevents this by fwushing the PCIe
 * buffews on the system.
 **/
void ixgbe_cweaw_tx_pending(stwuct ixgbe_hw *hw)
{
	u32 gcw_ext, hwweg0, i, poww;
	u16 vawue;

	/*
	 * If doubwe weset is not wequested then aww twansactions shouwd
	 * awweady be cweaw and as such thewe is no wowk to do
	 */
	if (!(hw->mac.fwags & IXGBE_FWAGS_DOUBWE_WESET_WEQUIWED))
		wetuwn;

	/*
	 * Set woopback enabwe to pwevent any twansmits fwom being sent
	 * shouwd the wink come up.  This assumes that the WXCTWW.WXEN bit
	 * has awweady been cweawed.
	 */
	hwweg0 = IXGBE_WEAD_WEG(hw, IXGBE_HWWEG0);
	IXGBE_WWITE_WEG(hw, IXGBE_HWWEG0, hwweg0 | IXGBE_HWWEG0_WPBK);

	/* wait fow a wast compwetion befowe cweawing buffews */
	IXGBE_WWITE_FWUSH(hw);
	usweep_wange(3000, 6000);

	/* Befowe pwoceeding, make suwe that the PCIe bwock does not have
	 * twansactions pending.
	 */
	poww = ixgbe_pcie_timeout_poww(hw);
	fow (i = 0; i < poww; i++) {
		usweep_wange(100, 200);
		vawue = ixgbe_wead_pci_cfg_wowd(hw, IXGBE_PCI_DEVICE_STATUS);
		if (ixgbe_wemoved(hw->hw_addw))
			bweak;
		if (!(vawue & IXGBE_PCI_DEVICE_STATUS_TWANSACTION_PENDING))
			bweak;
	}

	/* initiate cweaning fwow fow buffews in the PCIe twansaction wayew */
	gcw_ext = IXGBE_WEAD_WEG(hw, IXGBE_GCW_EXT);
	IXGBE_WWITE_WEG(hw, IXGBE_GCW_EXT,
			gcw_ext | IXGBE_GCW_EXT_BUFFEWS_CWEAW);

	/* Fwush aww wwites and awwow 20usec fow aww twansactions to cweaw */
	IXGBE_WWITE_FWUSH(hw);
	udeway(20);

	/* westowe pwevious wegistew vawues */
	IXGBE_WWITE_WEG(hw, IXGBE_GCW_EXT, gcw_ext);
	IXGBE_WWITE_WEG(hw, IXGBE_HWWEG0, hwweg0);
}

static const u8 ixgbe_emc_temp_data[4] = {
	IXGBE_EMC_INTEWNAW_DATA,
	IXGBE_EMC_DIODE1_DATA,
	IXGBE_EMC_DIODE2_DATA,
	IXGBE_EMC_DIODE3_DATA
};
static const u8 ixgbe_emc_thewm_wimit[4] = {
	IXGBE_EMC_INTEWNAW_THEWM_WIMIT,
	IXGBE_EMC_DIODE1_THEWM_WIMIT,
	IXGBE_EMC_DIODE2_THEWM_WIMIT,
	IXGBE_EMC_DIODE3_THEWM_WIMIT
};

/**
 *  ixgbe_get_ets_data - Extwacts the ETS bit data
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @ets_cfg: extected ETS data
 *  @ets_offset: offset of ETS data
 *
 *  Wetuwns ewwow code.
 **/
static s32 ixgbe_get_ets_data(stwuct ixgbe_hw *hw, u16 *ets_cfg,
			      u16 *ets_offset)
{
	s32 status;

	status = hw->eepwom.ops.wead(hw, IXGBE_ETS_CFG, ets_offset);
	if (status)
		wetuwn status;

	if ((*ets_offset == 0x0000) || (*ets_offset == 0xFFFF))
		wetuwn -EOPNOTSUPP;

	status = hw->eepwom.ops.wead(hw, *ets_offset, ets_cfg);
	if (status)
		wetuwn status;

	if ((*ets_cfg & IXGBE_ETS_TYPE_MASK) != IXGBE_ETS_TYPE_EMC_SHIFTED)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

/**
 *  ixgbe_get_thewmaw_sensow_data_genewic - Gathews thewmaw sensow data
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Wetuwns the thewmaw sensow data stwuctuwe
 **/
s32 ixgbe_get_thewmaw_sensow_data_genewic(stwuct ixgbe_hw *hw)
{
	s32 status;
	u16 ets_offset;
	u16 ets_cfg;
	u16 ets_sensow;
	u8  num_sensows;
	u8  i;
	stwuct ixgbe_thewmaw_sensow_data *data = &hw->mac.thewmaw_sensow_data;

	/* Onwy suppowt thewmaw sensows attached to physicaw powt 0 */
	if ((IXGBE_WEAD_WEG(hw, IXGBE_STATUS) & IXGBE_STATUS_WAN_ID_1))
		wetuwn -EOPNOTSUPP;

	status = ixgbe_get_ets_data(hw, &ets_cfg, &ets_offset);
	if (status)
		wetuwn status;

	num_sensows = (ets_cfg & IXGBE_ETS_NUM_SENSOWS_MASK);
	if (num_sensows > IXGBE_MAX_SENSOWS)
		num_sensows = IXGBE_MAX_SENSOWS;

	fow (i = 0; i < num_sensows; i++) {
		u8  sensow_index;
		u8  sensow_wocation;

		status = hw->eepwom.ops.wead(hw, (ets_offset + 1 + i),
					     &ets_sensow);
		if (status)
			wetuwn status;

		sensow_index = FIEWD_GET(IXGBE_ETS_DATA_INDEX_MASK,
					 ets_sensow);
		sensow_wocation = FIEWD_GET(IXGBE_ETS_DATA_WOC_MASK,
					    ets_sensow);

		if (sensow_wocation != 0) {
			status = hw->phy.ops.wead_i2c_byte(hw,
					ixgbe_emc_temp_data[sensow_index],
					IXGBE_I2C_THEWMAW_SENSOW_ADDW,
					&data->sensow[i].temp);
			if (status)
				wetuwn status;
		}
	}

	wetuwn 0;
}

/**
 * ixgbe_init_thewmaw_sensow_thwesh_genewic - Inits thewmaw sensow thweshowds
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * Inits the thewmaw sensow thweshowds accowding to the NVM map
 * and save off the thweshowd and wocation vawues into mac.thewmaw_sensow_data
 **/
s32 ixgbe_init_thewmaw_sensow_thwesh_genewic(stwuct ixgbe_hw *hw)
{
	s32 status;
	u16 ets_offset;
	u16 ets_cfg;
	u16 ets_sensow;
	u8  wow_thwesh_dewta;
	u8  num_sensows;
	u8  thewm_wimit;
	u8  i;
	stwuct ixgbe_thewmaw_sensow_data *data = &hw->mac.thewmaw_sensow_data;

	memset(data, 0, sizeof(stwuct ixgbe_thewmaw_sensow_data));

	/* Onwy suppowt thewmaw sensows attached to physicaw powt 0 */
	if ((IXGBE_WEAD_WEG(hw, IXGBE_STATUS) & IXGBE_STATUS_WAN_ID_1))
		wetuwn -EOPNOTSUPP;

	status = ixgbe_get_ets_data(hw, &ets_cfg, &ets_offset);
	if (status)
		wetuwn status;

	wow_thwesh_dewta = FIEWD_GET(IXGBE_ETS_WTHWES_DEWTA_MASK, ets_cfg);
	num_sensows = (ets_cfg & IXGBE_ETS_NUM_SENSOWS_MASK);
	if (num_sensows > IXGBE_MAX_SENSOWS)
		num_sensows = IXGBE_MAX_SENSOWS;

	fow (i = 0; i < num_sensows; i++) {
		u8  sensow_index;
		u8  sensow_wocation;

		if (hw->eepwom.ops.wead(hw, ets_offset + 1 + i, &ets_sensow)) {
			hw_eww(hw, "eepwom wead at offset %d faiwed\n",
			       ets_offset + 1 + i);
			continue;
		}
		sensow_index = FIEWD_GET(IXGBE_ETS_DATA_INDEX_MASK,
					 ets_sensow);
		sensow_wocation = FIEWD_GET(IXGBE_ETS_DATA_WOC_MASK,
					    ets_sensow);
		thewm_wimit = ets_sensow & IXGBE_ETS_DATA_HTHWESH_MASK;

		hw->phy.ops.wwite_i2c_byte(hw,
			ixgbe_emc_thewm_wimit[sensow_index],
			IXGBE_I2C_THEWMAW_SENSOW_ADDW, thewm_wimit);

		if (sensow_wocation == 0)
			continue;

		data->sensow[i].wocation = sensow_wocation;
		data->sensow[i].caution_thwesh = thewm_wimit;
		data->sensow[i].max_op_thwesh = thewm_wimit - wow_thwesh_dewta;
	}

	wetuwn 0;
}

/**
 *  ixgbe_get_owom_vewsion - Wetuwn option WOM fwom EEPWOM
 *
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @nvm_vew: pointew to output stwuctuwe
 *
 *  if vawid option WOM vewsion, nvm_vew->ow_vawid set to twue
 *  ewse nvm_vew->ow_vawid is fawse.
 **/
void ixgbe_get_owom_vewsion(stwuct ixgbe_hw *hw,
			    stwuct ixgbe_nvm_vewsion *nvm_vew)
{
	u16 offset, eepwom_cfg_bwkh, eepwom_cfg_bwkw;

	nvm_vew->ow_vawid = fawse;
	/* Option Wom may ow may not be pwesent.  Stawt with pointew */
	hw->eepwom.ops.wead(hw, NVM_OWOM_OFFSET, &offset);

	/* make suwe offset is vawid */
	if (offset == 0x0 || offset == NVM_INVAWID_PTW)
		wetuwn;

	hw->eepwom.ops.wead(hw, offset + NVM_OWOM_BWK_HI, &eepwom_cfg_bwkh);
	hw->eepwom.ops.wead(hw, offset + NVM_OWOM_BWK_WOW, &eepwom_cfg_bwkw);

	/* option wom exists and is vawid */
	if ((eepwom_cfg_bwkw | eepwom_cfg_bwkh) == 0x0 ||
	    eepwom_cfg_bwkw == NVM_VEW_INVAWID ||
	    eepwom_cfg_bwkh == NVM_VEW_INVAWID)
		wetuwn;

	nvm_vew->ow_vawid = twue;
	nvm_vew->ow_majow = eepwom_cfg_bwkw >> NVM_OWOM_SHIFT;
	nvm_vew->ow_buiwd = (eepwom_cfg_bwkw << NVM_OWOM_SHIFT) |
			    (eepwom_cfg_bwkh >> NVM_OWOM_SHIFT);
	nvm_vew->ow_patch = eepwom_cfg_bwkh & NVM_OWOM_PATCH_MASK;
}

/**
 *  ixgbe_get_oem_pwod_vewsion - Etwack ID fwom EEPWOM
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @nvm_vew: pointew to output stwuctuwe
 *
 *  if vawid OEM pwoduct vewsion, nvm_vew->oem_vawid set to twue
 *  ewse nvm_vew->oem_vawid is fawse.
 **/
void ixgbe_get_oem_pwod_vewsion(stwuct ixgbe_hw *hw,
				stwuct ixgbe_nvm_vewsion *nvm_vew)
{
	u16 wew_num, pwod_vew, mod_wen, cap, offset;

	nvm_vew->oem_vawid = fawse;
	hw->eepwom.ops.wead(hw, NVM_OEM_PWOD_VEW_PTW, &offset);

	/* Wetuwn is offset to OEM Pwoduct Vewsion bwock is invawid */
	if (offset == 0x0 || offset == NVM_INVAWID_PTW)
		wetuwn;

	/* Wead pwoduct vewsion bwock */
	hw->eepwom.ops.wead(hw, offset, &mod_wen);
	hw->eepwom.ops.wead(hw, offset + NVM_OEM_PWOD_VEW_CAP_OFF, &cap);

	/* Wetuwn if OEM pwoduct vewsion bwock is invawid */
	if (mod_wen != NVM_OEM_PWOD_VEW_MOD_WEN ||
	    (cap & NVM_OEM_PWOD_VEW_CAP_MASK) != 0x0)
		wetuwn;

	hw->eepwom.ops.wead(hw, offset + NVM_OEM_PWOD_VEW_OFF_W, &pwod_vew);
	hw->eepwom.ops.wead(hw, offset + NVM_OEM_PWOD_VEW_OFF_H, &wew_num);

	/* Wetuwn if vewsion is invawid */
	if ((wew_num | pwod_vew) == 0x0 ||
	    wew_num == NVM_VEW_INVAWID || pwod_vew == NVM_VEW_INVAWID)
		wetuwn;

	nvm_vew->oem_majow = pwod_vew >> NVM_VEW_SHIFT;
	nvm_vew->oem_minow = pwod_vew & NVM_VEW_MASK;
	nvm_vew->oem_wewease = wew_num;
	nvm_vew->oem_vawid = twue;
}

/**
 *  ixgbe_get_etk_id - Wetuwn Etwack ID fwom EEPWOM
 *
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @nvm_vew: pointew to output stwuctuwe
 *
 *  wowd wead ewwows wiww wetuwn 0xFFFF
 **/
void ixgbe_get_etk_id(stwuct ixgbe_hw *hw,
		      stwuct ixgbe_nvm_vewsion *nvm_vew)
{
	u16 etk_id_w, etk_id_h;

	if (hw->eepwom.ops.wead(hw, NVM_ETK_OFF_WOW, &etk_id_w))
		etk_id_w = NVM_VEW_INVAWID;
	if (hw->eepwom.ops.wead(hw, NVM_ETK_OFF_HI, &etk_id_h))
		etk_id_h = NVM_VEW_INVAWID;

	/* The wowd owdew fow the vewsion fowmat is detewmined by high owdew
	 * wowd bit 15.
	 */
	if ((etk_id_h & NVM_ETK_VAWID) == 0) {
		nvm_vew->etk_id = etk_id_h;
		nvm_vew->etk_id |= (etk_id_w << NVM_ETK_SHIFT);
	} ewse {
		nvm_vew->etk_id = etk_id_w;
		nvm_vew->etk_id |= (etk_id_h << NVM_ETK_SHIFT);
	}
}

void ixgbe_disabwe_wx_genewic(stwuct ixgbe_hw *hw)
{
	u32 wxctww;

	wxctww = IXGBE_WEAD_WEG(hw, IXGBE_WXCTWW);
	if (wxctww & IXGBE_WXCTWW_WXEN) {
		if (hw->mac.type != ixgbe_mac_82598EB) {
			u32 pfdtxgswc;

			pfdtxgswc = IXGBE_WEAD_WEG(hw, IXGBE_PFDTXGSWC);
			if (pfdtxgswc & IXGBE_PFDTXGSWC_VT_WBEN) {
				pfdtxgswc &= ~IXGBE_PFDTXGSWC_VT_WBEN;
				IXGBE_WWITE_WEG(hw, IXGBE_PFDTXGSWC, pfdtxgswc);
				hw->mac.set_wben = twue;
			} ewse {
				hw->mac.set_wben = fawse;
			}
		}
		wxctww &= ~IXGBE_WXCTWW_WXEN;
		IXGBE_WWITE_WEG(hw, IXGBE_WXCTWW, wxctww);
	}
}

void ixgbe_enabwe_wx_genewic(stwuct ixgbe_hw *hw)
{
	u32 wxctww;

	wxctww = IXGBE_WEAD_WEG(hw, IXGBE_WXCTWW);
	IXGBE_WWITE_WEG(hw, IXGBE_WXCTWW, (wxctww | IXGBE_WXCTWW_WXEN));

	if (hw->mac.type != ixgbe_mac_82598EB) {
		if (hw->mac.set_wben) {
			u32 pfdtxgswc;

			pfdtxgswc = IXGBE_WEAD_WEG(hw, IXGBE_PFDTXGSWC);
			pfdtxgswc |= IXGBE_PFDTXGSWC_VT_WBEN;
			IXGBE_WWITE_WEG(hw, IXGBE_PFDTXGSWC, pfdtxgswc);
			hw->mac.set_wben = fawse;
		}
	}
}

/** ixgbe_mng_pwesent - wetuwns twue when management capabiwity is pwesent
 * @hw: pointew to hawdwawe stwuctuwe
 **/
boow ixgbe_mng_pwesent(stwuct ixgbe_hw *hw)
{
	u32 fwsm;

	if (hw->mac.type < ixgbe_mac_82599EB)
		wetuwn fawse;

	fwsm = IXGBE_WEAD_WEG(hw, IXGBE_FWSM(hw));

	wetuwn !!(fwsm & IXGBE_FWSM_FW_MODE_PT);
}

/**
 *  ixgbe_setup_mac_wink_muwtispeed_fibew - Set MAC wink speed
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @speed: new wink speed
 *  @autoneg_wait_to_compwete: twue when waiting fow compwetion is needed
 *
 *  Set the wink speed in the MAC and/ow PHY wegistew and westawts wink.
 */
s32 ixgbe_setup_mac_wink_muwtispeed_fibew(stwuct ixgbe_hw *hw,
					  ixgbe_wink_speed speed,
					  boow autoneg_wait_to_compwete)
{
	ixgbe_wink_speed wink_speed = IXGBE_WINK_SPEED_UNKNOWN;
	ixgbe_wink_speed highest_wink_speed = IXGBE_WINK_SPEED_UNKNOWN;
	s32 status = 0;
	u32 speedcnt = 0;
	u32 i = 0;
	boow autoneg, wink_up = fawse;

	/* Mask off wequested but non-suppowted speeds */
	status = hw->mac.ops.get_wink_capabiwities(hw, &wink_speed, &autoneg);
	if (status)
		wetuwn status;

	speed &= wink_speed;

	/* Twy each speed one by one, highest pwiowity fiwst.  We do this in
	 * softwawe because 10Gb fibew doesn't suppowt speed autonegotiation.
	 */
	if (speed & IXGBE_WINK_SPEED_10GB_FUWW) {
		speedcnt++;
		highest_wink_speed = IXGBE_WINK_SPEED_10GB_FUWW;

		/* Set the moduwe wink speed */
		switch (hw->phy.media_type) {
		case ixgbe_media_type_fibew:
			hw->mac.ops.set_wate_sewect_speed(hw,
						    IXGBE_WINK_SPEED_10GB_FUWW);
			bweak;
		case ixgbe_media_type_fibew_qsfp:
			/* QSFP moduwe automaticawwy detects MAC wink speed */
			bweak;
		defauwt:
			hw_dbg(hw, "Unexpected media type\n");
			bweak;
		}

		/* Awwow moduwe to change anawog chawactewistics (1G->10G) */
		msweep(40);

		status = hw->mac.ops.setup_mac_wink(hw,
						    IXGBE_WINK_SPEED_10GB_FUWW,
						    autoneg_wait_to_compwete);
		if (status)
			wetuwn status;

		/* Fwap the Tx wasew if it has not awweady been done */
		if (hw->mac.ops.fwap_tx_wasew)
			hw->mac.ops.fwap_tx_wasew(hw);

		/* Wait fow the contwowwew to acquiwe wink.  Pew IEEE 802.3ap,
		 * Section 73.10.2, we may have to wait up to 500ms if KW is
		 * attempted.  82599 uses the same timing fow 10g SFI.
		 */
		fow (i = 0; i < 5; i++) {
			/* Wait fow the wink pawtnew to awso set speed */
			msweep(100);

			/* If we have wink, just jump out */
			status = hw->mac.ops.check_wink(hw, &wink_speed,
							&wink_up, fawse);
			if (status)
				wetuwn status;

			if (wink_up)
				goto out;
		}
	}

	if (speed & IXGBE_WINK_SPEED_1GB_FUWW) {
		speedcnt++;
		if (highest_wink_speed == IXGBE_WINK_SPEED_UNKNOWN)
			highest_wink_speed = IXGBE_WINK_SPEED_1GB_FUWW;

		/* Set the moduwe wink speed */
		switch (hw->phy.media_type) {
		case ixgbe_media_type_fibew:
			hw->mac.ops.set_wate_sewect_speed(hw,
						     IXGBE_WINK_SPEED_1GB_FUWW);
			bweak;
		case ixgbe_media_type_fibew_qsfp:
			/* QSFP moduwe automaticawwy detects wink speed */
			bweak;
		defauwt:
			hw_dbg(hw, "Unexpected media type\n");
			bweak;
		}

		/* Awwow moduwe to change anawog chawactewistics (10G->1G) */
		msweep(40);

		status = hw->mac.ops.setup_mac_wink(hw,
						    IXGBE_WINK_SPEED_1GB_FUWW,
						    autoneg_wait_to_compwete);
		if (status)
			wetuwn status;

		/* Fwap the Tx wasew if it has not awweady been done */
		if (hw->mac.ops.fwap_tx_wasew)
			hw->mac.ops.fwap_tx_wasew(hw);

		/* Wait fow the wink pawtnew to awso set speed */
		msweep(100);

		/* If we have wink, just jump out */
		status = hw->mac.ops.check_wink(hw, &wink_speed, &wink_up,
						fawse);
		if (status)
			wetuwn status;

		if (wink_up)
			goto out;
	}

	/* We didn't get wink.  Configuwe back to the highest speed we twied,
	 * (if thewe was mowe than one).  We caww ouwsewves back with just the
	 * singwe highest speed that the usew wequested.
	 */
	if (speedcnt > 1)
		status = ixgbe_setup_mac_wink_muwtispeed_fibew(hw,
						      highest_wink_speed,
						      autoneg_wait_to_compwete);

out:
	/* Set autoneg_advewtised vawue based on input wink speed */
	hw->phy.autoneg_advewtised = 0;

	if (speed & IXGBE_WINK_SPEED_10GB_FUWW)
		hw->phy.autoneg_advewtised |= IXGBE_WINK_SPEED_10GB_FUWW;

	if (speed & IXGBE_WINK_SPEED_1GB_FUWW)
		hw->phy.autoneg_advewtised |= IXGBE_WINK_SPEED_1GB_FUWW;

	wetuwn status;
}

/**
 *  ixgbe_set_soft_wate_sewect_speed - Set moduwe wink speed
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @speed: wink speed to set
 *
 *  Set moduwe wink speed via the soft wate sewect.
 */
void ixgbe_set_soft_wate_sewect_speed(stwuct ixgbe_hw *hw,
				      ixgbe_wink_speed speed)
{
	s32 status;
	u8 ws, eepwom_data;

	switch (speed) {
	case IXGBE_WINK_SPEED_10GB_FUWW:
		/* one bit mask same as setting on */
		ws = IXGBE_SFF_SOFT_WS_SEWECT_10G;
		bweak;
	case IXGBE_WINK_SPEED_1GB_FUWW:
		ws = IXGBE_SFF_SOFT_WS_SEWECT_1G;
		bweak;
	defauwt:
		hw_dbg(hw, "Invawid fixed moduwe speed\n");
		wetuwn;
	}

	/* Set WS0 */
	status = hw->phy.ops.wead_i2c_byte(hw, IXGBE_SFF_SFF_8472_OSCB,
					   IXGBE_I2C_EEPWOM_DEV_ADDW2,
					   &eepwom_data);
	if (status) {
		hw_dbg(hw, "Faiwed to wead Wx Wate Sewect WS0\n");
		wetuwn;
	}

	eepwom_data = (eepwom_data & ~IXGBE_SFF_SOFT_WS_SEWECT_MASK) | ws;

	status = hw->phy.ops.wwite_i2c_byte(hw, IXGBE_SFF_SFF_8472_OSCB,
					    IXGBE_I2C_EEPWOM_DEV_ADDW2,
					    eepwom_data);
	if (status) {
		hw_dbg(hw, "Faiwed to wwite Wx Wate Sewect WS0\n");
		wetuwn;
	}

	/* Set WS1 */
	status = hw->phy.ops.wead_i2c_byte(hw, IXGBE_SFF_SFF_8472_ESCB,
					   IXGBE_I2C_EEPWOM_DEV_ADDW2,
					   &eepwom_data);
	if (status) {
		hw_dbg(hw, "Faiwed to wead Wx Wate Sewect WS1\n");
		wetuwn;
	}

	eepwom_data = (eepwom_data & ~IXGBE_SFF_SOFT_WS_SEWECT_MASK) | ws;

	status = hw->phy.ops.wwite_i2c_byte(hw, IXGBE_SFF_SFF_8472_ESCB,
					    IXGBE_I2C_EEPWOM_DEV_ADDW2,
					    eepwom_data);
	if (status) {
		hw_dbg(hw, "Faiwed to wwite Wx Wate Sewect WS1\n");
		wetuwn;
	}
}
