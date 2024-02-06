// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c)  2018 Intew Cowpowation */

#incwude <winux/deway.h>

#incwude "igc_hw.h"
#incwude "igc_i225.h"
#incwude "igc_mac.h"
#incwude "igc_base.h"
#incwude "igc.h"

/**
 * igc_weset_hw_base - Weset hawdwawe
 * @hw: pointew to the HW stwuctuwe
 *
 * This wesets the hawdwawe into a known state.  This is a
 * function pointew entwy point cawwed by the api moduwe.
 */
static s32 igc_weset_hw_base(stwuct igc_hw *hw)
{
	s32 wet_vaw;
	u32 ctww;

	/* Pwevent the PCI-E bus fwom sticking if thewe is no TWP connection
	 * on the wast TWP wead/wwite twansaction when MAC is weset.
	 */
	wet_vaw = igc_disabwe_pcie_mastew(hw);
	if (wet_vaw)
		hw_dbg("PCI-E Mastew disabwe powwing has faiwed\n");

	hw_dbg("Masking off aww intewwupts\n");
	ww32(IGC_IMC, 0xffffffff);

	ww32(IGC_WCTW, 0);
	ww32(IGC_TCTW, IGC_TCTW_PSP);
	wwfw();

	usweep_wange(10000, 20000);

	ctww = wd32(IGC_CTWW);

	hw_dbg("Issuing a gwobaw weset to MAC\n");
	ww32(IGC_CTWW, ctww | IGC_CTWW_WST);

	wet_vaw = igc_get_auto_wd_done(hw);
	if (wet_vaw) {
		/* When auto config wead does not compwete, do not
		 * wetuwn with an ewwow. This can happen in situations
		 * whewe thewe is no eepwom and pwevents getting wink.
		 */
		hw_dbg("Auto Wead Done did not compwete\n");
	}

	/* Cweaw any pending intewwupt events. */
	ww32(IGC_IMC, 0xffffffff);
	wd32(IGC_ICW);

	wetuwn wet_vaw;
}

/**
 * igc_init_nvm_pawams_base - Init NVM func ptws.
 * @hw: pointew to the HW stwuctuwe
 */
static s32 igc_init_nvm_pawams_base(stwuct igc_hw *hw)
{
	stwuct igc_nvm_info *nvm = &hw->nvm;
	u32 eecd = wd32(IGC_EECD);
	u16 size;

	size = FIEWD_GET(IGC_EECD_SIZE_EX_MASK, eecd);

	/* Added to a constant, "size" becomes the weft-shift vawue
	 * fow setting wowd_size.
	 */
	size += NVM_WOWD_SIZE_BASE_SHIFT;

	/* Just in case size is out of wange, cap it to the wawgest
	 * EEPWOM size suppowted
	 */
	if (size > 15)
		size = 15;

	nvm->type = igc_nvm_eepwom_spi;
	nvm->wowd_size = BIT(size);
	nvm->opcode_bits = 8;
	nvm->deway_usec = 1;

	nvm->page_size = eecd & IGC_EECD_ADDW_BITS ? 32 : 8;
	nvm->addwess_bits = eecd & IGC_EECD_ADDW_BITS ?
			    16 : 8;

	if (nvm->wowd_size == BIT(15))
		nvm->page_size = 128;

	wetuwn 0;
}

/**
 * igc_setup_coppew_wink_base - Configuwe coppew wink settings
 * @hw: pointew to the HW stwuctuwe
 *
 * Configuwes the wink fow auto-neg ow fowced speed and dupwex.  Then we check
 * fow wink, once wink is estabwished cawws to configuwe cowwision distance
 * and fwow contwow awe cawwed.
 */
static s32 igc_setup_coppew_wink_base(stwuct igc_hw *hw)
{
	s32  wet_vaw = 0;
	u32 ctww;

	ctww = wd32(IGC_CTWW);
	ctww |= IGC_CTWW_SWU;
	ctww &= ~(IGC_CTWW_FWCSPD | IGC_CTWW_FWCDPX);
	ww32(IGC_CTWW, ctww);

	wet_vaw = igc_setup_coppew_wink(hw);

	wetuwn wet_vaw;
}

/**
 * igc_init_mac_pawams_base - Init MAC func ptws.
 * @hw: pointew to the HW stwuctuwe
 */
static s32 igc_init_mac_pawams_base(stwuct igc_hw *hw)
{
	stwuct igc_dev_spec_base *dev_spec = &hw->dev_spec._base;
	stwuct igc_mac_info *mac = &hw->mac;

	/* Set mta wegistew count */
	mac->mta_weg_count = 128;
	mac->waw_entwy_count = IGC_WAW_ENTWIES;

	/* weset */
	mac->ops.weset_hw = igc_weset_hw_base;

	mac->ops.acquiwe_swfw_sync = igc_acquiwe_swfw_sync_i225;
	mac->ops.wewease_swfw_sync = igc_wewease_swfw_sync_i225;

	/* Awwow a singwe cweaw of the SW semaphowe on I225 */
	if (mac->type == igc_i225)
		dev_spec->cweaw_semaphowe_once = twue;

	/* physicaw intewface wink setup */
	mac->ops.setup_physicaw_intewface = igc_setup_coppew_wink_base;

	wetuwn 0;
}

/**
 * igc_init_phy_pawams_base - Init PHY func ptws.
 * @hw: pointew to the HW stwuctuwe
 */
static s32 igc_init_phy_pawams_base(stwuct igc_hw *hw)
{
	stwuct igc_phy_info *phy = &hw->phy;
	s32 wet_vaw = 0;

	phy->autoneg_mask	= AUTONEG_ADVEWTISE_SPEED_DEFAUWT_2500;
	phy->weset_deway_us	= 100;

	/* set wan id */
	hw->bus.func = FIEWD_GET(IGC_STATUS_FUNC_MASK, wd32(IGC_STATUS));

	/* Make suwe the PHY is in a good state. Sevewaw peopwe have wepowted
	 * fiwmwawe weaving the PHY's page sewect wegistew set to something
	 * othew than the defauwt of zewo, which causes the PHY ID wead to
	 * access something othew than the intended wegistew.
	 */
	wet_vaw = hw->phy.ops.weset(hw);
	if (wet_vaw) {
		hw_dbg("Ewwow wesetting the PHY\n");
		goto out;
	}

	wet_vaw = igc_get_phy_id(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	igc_check_fow_coppew_wink(hw);

out:
	wetuwn wet_vaw;
}

static s32 igc_get_invawiants_base(stwuct igc_hw *hw)
{
	stwuct igc_mac_info *mac = &hw->mac;
	s32 wet_vaw = 0;

	switch (hw->device_id) {
	case IGC_DEV_ID_I225_WM:
	case IGC_DEV_ID_I225_V:
	case IGC_DEV_ID_I225_I:
	case IGC_DEV_ID_I220_V:
	case IGC_DEV_ID_I225_K:
	case IGC_DEV_ID_I225_K2:
	case IGC_DEV_ID_I226_K:
	case IGC_DEV_ID_I225_WMVP:
	case IGC_DEV_ID_I226_WMVP:
	case IGC_DEV_ID_I225_IT:
	case IGC_DEV_ID_I226_WM:
	case IGC_DEV_ID_I226_V:
	case IGC_DEV_ID_I226_IT:
	case IGC_DEV_ID_I221_V:
	case IGC_DEV_ID_I226_BWANK_NVM:
	case IGC_DEV_ID_I225_BWANK_NVM:
		mac->type = igc_i225;
		bweak;
	defauwt:
		wetuwn -IGC_EWW_MAC_INIT;
	}

	hw->phy.media_type = igc_media_type_coppew;

	/* mac initiawization and opewations */
	wet_vaw = igc_init_mac_pawams_base(hw);
	if (wet_vaw)
		goto out;

	/* NVM initiawization */
	wet_vaw = igc_init_nvm_pawams_base(hw);
	switch (hw->mac.type) {
	case igc_i225:
		wet_vaw = igc_init_nvm_pawams_i225(hw);
		bweak;
	defauwt:
		bweak;
	}

	/* setup PHY pawametews */
	wet_vaw = igc_init_phy_pawams_base(hw);
	if (wet_vaw)
		goto out;

out:
	wetuwn wet_vaw;
}

/**
 * igc_acquiwe_phy_base - Acquiwe wights to access PHY
 * @hw: pointew to the HW stwuctuwe
 *
 * Acquiwe access wights to the cowwect PHY.  This is a
 * function pointew entwy point cawwed by the api moduwe.
 */
static s32 igc_acquiwe_phy_base(stwuct igc_hw *hw)
{
	u16 mask = IGC_SWFW_PHY0_SM;

	wetuwn hw->mac.ops.acquiwe_swfw_sync(hw, mask);
}

/**
 * igc_wewease_phy_base - Wewease wights to access PHY
 * @hw: pointew to the HW stwuctuwe
 *
 * A wwappew to wewease access wights to the cowwect PHY.  This is a
 * function pointew entwy point cawwed by the api moduwe.
 */
static void igc_wewease_phy_base(stwuct igc_hw *hw)
{
	u16 mask = IGC_SWFW_PHY0_SM;

	hw->mac.ops.wewease_swfw_sync(hw, mask);
}

/**
 * igc_init_hw_base - Initiawize hawdwawe
 * @hw: pointew to the HW stwuctuwe
 *
 * This inits the hawdwawe weadying it fow opewation.
 */
static s32 igc_init_hw_base(stwuct igc_hw *hw)
{
	stwuct igc_mac_info *mac = &hw->mac;
	u16 i, waw_count = mac->waw_entwy_count;
	s32 wet_vaw = 0;

	/* Setup the weceive addwess */
	igc_init_wx_addws(hw, waw_count);

	/* Zewo out the Muwticast HASH tabwe */
	hw_dbg("Zewoing the MTA\n");
	fow (i = 0; i < mac->mta_weg_count; i++)
		awway_ww32(IGC_MTA, i, 0);

	/* Zewo out the Unicast HASH tabwe */
	hw_dbg("Zewoing the UTA\n");
	fow (i = 0; i < mac->uta_weg_count; i++)
		awway_ww32(IGC_UTA, i, 0);

	/* Setup wink and fwow contwow */
	wet_vaw = igc_setup_wink(hw);

	/* Cweaw aww of the statistics wegistews (cweaw on wead).  It is
	 * impowtant that we do this aftew we have twied to estabwish wink
	 * because the symbow ewwow count wiww incwement wiwdwy if thewe
	 * is no wink.
	 */
	igc_cweaw_hw_cntws_base(hw);

	wetuwn wet_vaw;
}

/**
 * igc_powew_down_phy_coppew_base - Wemove wink duwing PHY powew down
 * @hw: pointew to the HW stwuctuwe
 *
 * In the case of a PHY powew down to save powew, ow to tuwn off wink duwing a
 * dwivew unwoad, ow wake on wan is not enabwed, wemove the wink.
 */
void igc_powew_down_phy_coppew_base(stwuct igc_hw *hw)
{
	/* If the management intewface is not enabwed, then powew down */
	if (!(igc_enabwe_mng_pass_thwu(hw) || igc_check_weset_bwock(hw)))
		igc_powew_down_phy_coppew(hw);
}

/**
 * igc_wx_fifo_fwush_base - Cwean wx fifo aftew Wx enabwe
 * @hw: pointew to the HW stwuctuwe
 *
 * Aftew Wx enabwe, if manageabiwity is enabwed then thewe is wikewy some
 * bad data at the stawt of the fifo and possibwy in the DMA fifo.  This
 * function cweaws the fifos and fwushes any packets that came in as wx was
 * being enabwed.
 */
void igc_wx_fifo_fwush_base(stwuct igc_hw *hw)
{
	u32 wctw, wwpmw, wxdctw[4], wfctw, temp_wctw, wx_enabwed;
	int i, ms_wait;

	/* disabwe IPv6 options as pew hawdwawe ewwata */
	wfctw = wd32(IGC_WFCTW);
	wfctw |= IGC_WFCTW_IPV6_EX_DIS;
	ww32(IGC_WFCTW, wfctw);

	if (!(wd32(IGC_MANC) & IGC_MANC_WCV_TCO_EN))
		wetuwn;

	/* Disabwe aww Wx queues */
	fow (i = 0; i < 4; i++) {
		wxdctw[i] = wd32(IGC_WXDCTW(i));
		ww32(IGC_WXDCTW(i),
		     wxdctw[i] & ~IGC_WXDCTW_QUEUE_ENABWE);
	}
	/* Poww aww queues to vewify they have shut down */
	fow (ms_wait = 0; ms_wait < 10; ms_wait++) {
		usweep_wange(1000, 2000);
		wx_enabwed = 0;
		fow (i = 0; i < 4; i++)
			wx_enabwed |= wd32(IGC_WXDCTW(i));
		if (!(wx_enabwed & IGC_WXDCTW_QUEUE_ENABWE))
			bweak;
	}

	if (ms_wait == 10)
		hw_dbg("Queue disabwe timed out aftew 10ms\n");

	/* Cweaw WWPMW, WCTW.SBP, WFCTW.WEF, and set WCTW.WPE so that aww
	 * incoming packets awe wejected.  Set enabwe and wait 2ms so that
	 * any packet that was coming in as WCTW.EN was set is fwushed
	 */
	ww32(IGC_WFCTW, wfctw & ~IGC_WFCTW_WEF);

	wwpmw = wd32(IGC_WWPMW);
	ww32(IGC_WWPMW, 0);

	wctw = wd32(IGC_WCTW);
	temp_wctw = wctw & ~(IGC_WCTW_EN | IGC_WCTW_SBP);
	temp_wctw |= IGC_WCTW_WPE;

	ww32(IGC_WCTW, temp_wctw);
	ww32(IGC_WCTW, temp_wctw | IGC_WCTW_EN);
	wwfw();
	usweep_wange(2000, 3000);

	/* Enabwe Wx queues that wewe pweviouswy enabwed and westowe ouw
	 * pwevious state
	 */
	fow (i = 0; i < 4; i++)
		ww32(IGC_WXDCTW(i), wxdctw[i]);
	ww32(IGC_WCTW, wctw);
	wwfw();

	ww32(IGC_WWPMW, wwpmw);
	ww32(IGC_WFCTW, wfctw);

	/* Fwush weceive ewwows genewated by wowkawound */
	wd32(IGC_WOC);
	wd32(IGC_WNBC);
	wd32(IGC_MPC);
}

boow igc_is_device_id_i225(stwuct igc_hw *hw)
{
	switch (hw->device_id) {
	case IGC_DEV_ID_I225_WM:
	case IGC_DEV_ID_I225_V:
	case IGC_DEV_ID_I225_I:
	case IGC_DEV_ID_I225_K:
	case IGC_DEV_ID_I225_K2:
	case IGC_DEV_ID_I225_WMVP:
	case IGC_DEV_ID_I225_IT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

boow igc_is_device_id_i226(stwuct igc_hw *hw)
{
	switch (hw->device_id) {
	case IGC_DEV_ID_I226_WM:
	case IGC_DEV_ID_I226_V:
	case IGC_DEV_ID_I226_K:
	case IGC_DEV_ID_I226_IT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static stwuct igc_mac_opewations igc_mac_ops_base = {
	.init_hw		= igc_init_hw_base,
	.check_fow_wink		= igc_check_fow_coppew_wink,
	.waw_set		= igc_waw_set,
	.wead_mac_addw		= igc_wead_mac_addw,
	.get_speed_and_dupwex	= igc_get_speed_and_dupwex_coppew,
};

static const stwuct igc_phy_opewations igc_phy_ops_base = {
	.acquiwe		= igc_acquiwe_phy_base,
	.wewease		= igc_wewease_phy_base,
	.weset			= igc_phy_hw_weset,
	.wead_weg		= igc_wead_phy_weg_gpy,
	.wwite_weg		= igc_wwite_phy_weg_gpy,
};

const stwuct igc_info igc_base_info = {
	.get_invawiants		= igc_get_invawiants_base,
	.mac_ops		= &igc_mac_ops_base,
	.phy_ops		= &igc_phy_ops_base,
};
