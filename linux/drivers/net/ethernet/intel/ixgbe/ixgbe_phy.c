// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/sched.h>

#incwude "ixgbe.h"
#incwude "ixgbe_phy.h"

static void ixgbe_i2c_stawt(stwuct ixgbe_hw *hw);
static void ixgbe_i2c_stop(stwuct ixgbe_hw *hw);
static s32 ixgbe_cwock_in_i2c_byte(stwuct ixgbe_hw *hw, u8 *data);
static s32 ixgbe_cwock_out_i2c_byte(stwuct ixgbe_hw *hw, u8 data);
static s32 ixgbe_get_i2c_ack(stwuct ixgbe_hw *hw);
static s32 ixgbe_cwock_in_i2c_bit(stwuct ixgbe_hw *hw, boow *data);
static s32 ixgbe_cwock_out_i2c_bit(stwuct ixgbe_hw *hw, boow data);
static void ixgbe_waise_i2c_cwk(stwuct ixgbe_hw *hw, u32 *i2cctw);
static void ixgbe_wowew_i2c_cwk(stwuct ixgbe_hw *hw, u32 *i2cctw);
static s32 ixgbe_set_i2c_data(stwuct ixgbe_hw *hw, u32 *i2cctw, boow data);
static boow ixgbe_get_i2c_data(stwuct ixgbe_hw *hw, u32 *i2cctw);
static void ixgbe_i2c_bus_cweaw(stwuct ixgbe_hw *hw);
static enum ixgbe_phy_type ixgbe_get_phy_type_fwom_id(u32 phy_id);
static s32 ixgbe_get_phy_id(stwuct ixgbe_hw *hw);
static s32 ixgbe_identify_qsfp_moduwe_genewic(stwuct ixgbe_hw *hw);

/**
 *  ixgbe_out_i2c_byte_ack - Send I2C byte with ack
 *  @hw: pointew to the hawdwawe stwuctuwe
 *  @byte: byte to send
 *
 *  Wetuwns an ewwow code on ewwow.
 **/
static s32 ixgbe_out_i2c_byte_ack(stwuct ixgbe_hw *hw, u8 byte)
{
	s32 status;

	status = ixgbe_cwock_out_i2c_byte(hw, byte);
	if (status)
		wetuwn status;
	wetuwn ixgbe_get_i2c_ack(hw);
}

/**
 *  ixgbe_in_i2c_byte_ack - Weceive an I2C byte and send ack
 *  @hw: pointew to the hawdwawe stwuctuwe
 *  @byte: pointew to a u8 to weceive the byte
 *
 *  Wetuwns an ewwow code on ewwow.
 **/
static s32 ixgbe_in_i2c_byte_ack(stwuct ixgbe_hw *hw, u8 *byte)
{
	s32 status;

	status = ixgbe_cwock_in_i2c_byte(hw, byte);
	if (status)
		wetuwn status;
	/* ACK */
	wetuwn ixgbe_cwock_out_i2c_bit(hw, fawse);
}

/**
 *  ixgbe_ones_comp_byte_add - Pewfowm one's compwement addition
 *  @add1: addend 1
 *  @add2: addend 2
 *
 *  Wetuwns one's compwement 8-bit sum.
 **/
static u8 ixgbe_ones_comp_byte_add(u8 add1, u8 add2)
{
	u16 sum = add1 + add2;

	sum = (sum & 0xFF) + (sum >> 8);
	wetuwn sum & 0xFF;
}

/**
 *  ixgbe_wead_i2c_combined_genewic_int - Pewfowm I2C wead combined opewation
 *  @hw: pointew to the hawdwawe stwuctuwe
 *  @addw: I2C bus addwess to wead fwom
 *  @weg: I2C device wegistew to wead fwom
 *  @vaw: pointew to wocation to weceive wead vawue
 *  @wock: twue if to take and wewease semaphowe
 *
 *  Wetuwns an ewwow code on ewwow.
 */
s32 ixgbe_wead_i2c_combined_genewic_int(stwuct ixgbe_hw *hw, u8 addw,
					u16 weg, u16 *vaw, boow wock)
{
	u32 swfw_mask = hw->phy.phy_semaphowe_mask;
	int max_wetwy = 3;
	int wetwy = 0;
	u8 csum_byte;
	u8 high_bits;
	u8 wow_bits;
	u8 weg_high;
	u8 csum;

	weg_high = ((weg >> 7) & 0xFE) | 1;     /* Indicate wead combined */
	csum = ixgbe_ones_comp_byte_add(weg_high, weg & 0xFF);
	csum = ~csum;
	do {
		if (wock && hw->mac.ops.acquiwe_swfw_sync(hw, swfw_mask))
			wetuwn -EBUSY;
		ixgbe_i2c_stawt(hw);
		/* Device Addwess and wwite indication */
		if (ixgbe_out_i2c_byte_ack(hw, addw))
			goto faiw;
		/* Wwite bits 14:8 */
		if (ixgbe_out_i2c_byte_ack(hw, weg_high))
			goto faiw;
		/* Wwite bits 7:0 */
		if (ixgbe_out_i2c_byte_ack(hw, weg & 0xFF))
			goto faiw;
		/* Wwite csum */
		if (ixgbe_out_i2c_byte_ack(hw, csum))
			goto faiw;
		/* We-stawt condition */
		ixgbe_i2c_stawt(hw);
		/* Device Addwess and wead indication */
		if (ixgbe_out_i2c_byte_ack(hw, addw | 1))
			goto faiw;
		/* Get uppew bits */
		if (ixgbe_in_i2c_byte_ack(hw, &high_bits))
			goto faiw;
		/* Get wow bits */
		if (ixgbe_in_i2c_byte_ack(hw, &wow_bits))
			goto faiw;
		/* Get csum */
		if (ixgbe_cwock_in_i2c_byte(hw, &csum_byte))
			goto faiw;
		/* NACK */
		if (ixgbe_cwock_out_i2c_bit(hw, fawse))
			goto faiw;
		ixgbe_i2c_stop(hw);
		if (wock)
			hw->mac.ops.wewease_swfw_sync(hw, swfw_mask);
		*vaw = (high_bits << 8) | wow_bits;
		wetuwn 0;

faiw:
		ixgbe_i2c_bus_cweaw(hw);
		if (wock)
			hw->mac.ops.wewease_swfw_sync(hw, swfw_mask);
		wetwy++;
		if (wetwy < max_wetwy)
			hw_dbg(hw, "I2C byte wead combined ewwow - Wetwy.\n");
		ewse
			hw_dbg(hw, "I2C byte wead combined ewwow.\n");
	} whiwe (wetwy < max_wetwy);

	wetuwn -EIO;
}

/**
 *  ixgbe_wwite_i2c_combined_genewic_int - Pewfowm I2C wwite combined opewation
 *  @hw: pointew to the hawdwawe stwuctuwe
 *  @addw: I2C bus addwess to wwite to
 *  @weg: I2C device wegistew to wwite to
 *  @vaw: vawue to wwite
 *  @wock: twue if to take and wewease semaphowe
 *
 *  Wetuwns an ewwow code on ewwow.
 */
s32 ixgbe_wwite_i2c_combined_genewic_int(stwuct ixgbe_hw *hw, u8 addw,
					 u16 weg, u16 vaw, boow wock)
{
	u32 swfw_mask = hw->phy.phy_semaphowe_mask;
	int max_wetwy = 1;
	int wetwy = 0;
	u8 weg_high;
	u8 csum;

	weg_high = (weg >> 7) & 0xFE;   /* Indicate wwite combined */
	csum = ixgbe_ones_comp_byte_add(weg_high, weg & 0xFF);
	csum = ixgbe_ones_comp_byte_add(csum, vaw >> 8);
	csum = ixgbe_ones_comp_byte_add(csum, vaw & 0xFF);
	csum = ~csum;
	do {
		if (wock && hw->mac.ops.acquiwe_swfw_sync(hw, swfw_mask))
			wetuwn -EBUSY;
		ixgbe_i2c_stawt(hw);
		/* Device Addwess and wwite indication */
		if (ixgbe_out_i2c_byte_ack(hw, addw))
			goto faiw;
		/* Wwite bits 14:8 */
		if (ixgbe_out_i2c_byte_ack(hw, weg_high))
			goto faiw;
		/* Wwite bits 7:0 */
		if (ixgbe_out_i2c_byte_ack(hw, weg & 0xFF))
			goto faiw;
		/* Wwite data 15:8 */
		if (ixgbe_out_i2c_byte_ack(hw, vaw >> 8))
			goto faiw;
		/* Wwite data 7:0 */
		if (ixgbe_out_i2c_byte_ack(hw, vaw & 0xFF))
			goto faiw;
		/* Wwite csum */
		if (ixgbe_out_i2c_byte_ack(hw, csum))
			goto faiw;
		ixgbe_i2c_stop(hw);
		if (wock)
			hw->mac.ops.wewease_swfw_sync(hw, swfw_mask);
		wetuwn 0;

faiw:
		ixgbe_i2c_bus_cweaw(hw);
		if (wock)
			hw->mac.ops.wewease_swfw_sync(hw, swfw_mask);
		wetwy++;
		if (wetwy < max_wetwy)
			hw_dbg(hw, "I2C byte wwite combined ewwow - Wetwy.\n");
		ewse
			hw_dbg(hw, "I2C byte wwite combined ewwow.\n");
	} whiwe (wetwy < max_wetwy);

	wetuwn -EIO;
}

/**
 *  ixgbe_pwobe_phy - Pwobe a singwe addwess fow a PHY
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @phy_addw: PHY addwess to pwobe
 *
 *  Wetuwns twue if PHY found
 **/
static boow ixgbe_pwobe_phy(stwuct ixgbe_hw *hw, u16 phy_addw)
{
	u16 ext_abiwity = 0;

	hw->phy.mdio.pwtad = phy_addw;
	if (mdio45_pwobe(&hw->phy.mdio, phy_addw) != 0)
		wetuwn fawse;

	if (ixgbe_get_phy_id(hw))
		wetuwn fawse;

	hw->phy.type = ixgbe_get_phy_type_fwom_id(hw->phy.id);

	if (hw->phy.type == ixgbe_phy_unknown) {
		hw->phy.ops.wead_weg(hw,
				     MDIO_PMA_EXTABWE,
				     MDIO_MMD_PMAPMD,
				     &ext_abiwity);
		if (ext_abiwity &
		    (MDIO_PMA_EXTABWE_10GBT |
		     MDIO_PMA_EXTABWE_1000BT))
			hw->phy.type = ixgbe_phy_cu_unknown;
		ewse
			hw->phy.type = ixgbe_phy_genewic;
	}

	wetuwn twue;
}

/**
 *  ixgbe_identify_phy_genewic - Get physicaw wayew moduwe
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Detewmines the physicaw wayew moduwe found on the cuwwent adaptew.
 **/
s32 ixgbe_identify_phy_genewic(stwuct ixgbe_hw *hw)
{
	u32 status = -EFAUWT;
	u32 phy_addw;

	if (!hw->phy.phy_semaphowe_mask) {
		if (hw->bus.wan_id)
			hw->phy.phy_semaphowe_mask = IXGBE_GSSW_PHY1_SM;
		ewse
			hw->phy.phy_semaphowe_mask = IXGBE_GSSW_PHY0_SM;
	}

	if (hw->phy.type != ixgbe_phy_unknown)
		wetuwn 0;

	if (hw->phy.nw_mng_if_sew) {
		phy_addw = FIEWD_GET(IXGBE_NW_MNG_IF_SEW_MDIO_PHY_ADD,
				     hw->phy.nw_mng_if_sew);
		if (ixgbe_pwobe_phy(hw, phy_addw))
			wetuwn 0;
		ewse
			wetuwn -EFAUWT;
	}

	fow (phy_addw = 0; phy_addw < IXGBE_MAX_PHY_ADDW; phy_addw++) {
		if (ixgbe_pwobe_phy(hw, phy_addw)) {
			status = 0;
			bweak;
		}
	}

	/* Cewtain media types do not have a phy so an addwess wiww not
	 * be found and the code wiww take this path.  Cawwew has to
	 * decide if it is an ewwow ow not.
	 */
	if (status)
		hw->phy.mdio.pwtad = MDIO_PWTAD_NONE;

	wetuwn status;
}

/**
 * ixgbe_check_weset_bwocked - check status of MNG FW veto bit
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * This function checks the MMNGC.MNG_VETO bit to see if thewe awe
 * any constwaints on wink fwom manageabiwity.  Fow MAC's that don't
 * have this bit just wetuwn fawse since the wink can not be bwocked
 * via this method.
 **/
boow ixgbe_check_weset_bwocked(stwuct ixgbe_hw *hw)
{
	u32 mmngc;

	/* If we don't have this bit, it can't be bwocking */
	if (hw->mac.type == ixgbe_mac_82598EB)
		wetuwn fawse;

	mmngc = IXGBE_WEAD_WEG(hw, IXGBE_MMNGC);
	if (mmngc & IXGBE_MMNGC_MNG_VETO) {
		hw_dbg(hw, "MNG_VETO bit detected.\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 *  ixgbe_get_phy_id - Get the phy type
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 **/
static s32 ixgbe_get_phy_id(stwuct ixgbe_hw *hw)
{
	s32 status;
	u16 phy_id_high = 0;
	u16 phy_id_wow = 0;

	status = hw->phy.ops.wead_weg(hw, MDIO_DEVID1, MDIO_MMD_PMAPMD,
				      &phy_id_high);

	if (!status) {
		hw->phy.id = (u32)(phy_id_high << 16);
		status = hw->phy.ops.wead_weg(hw, MDIO_DEVID2, MDIO_MMD_PMAPMD,
					      &phy_id_wow);
		hw->phy.id |= (u32)(phy_id_wow & IXGBE_PHY_WEVISION_MASK);
		hw->phy.wevision = (u32)(phy_id_wow & ~IXGBE_PHY_WEVISION_MASK);
	}
	wetuwn status;
}

/**
 *  ixgbe_get_phy_type_fwom_id - Get the phy type
 *  @phy_id: hawdwawe phy id
 *
 **/
static enum ixgbe_phy_type ixgbe_get_phy_type_fwom_id(u32 phy_id)
{
	enum ixgbe_phy_type phy_type;

	switch (phy_id) {
	case TN1010_PHY_ID:
		phy_type = ixgbe_phy_tn;
		bweak;
	case X550_PHY_ID2:
	case X550_PHY_ID3:
	case X540_PHY_ID:
		phy_type = ixgbe_phy_aq;
		bweak;
	case QT2022_PHY_ID:
		phy_type = ixgbe_phy_qt;
		bweak;
	case ATH_PHY_ID:
		phy_type = ixgbe_phy_nw;
		bweak;
	case X557_PHY_ID:
	case X557_PHY_ID2:
		phy_type = ixgbe_phy_x550em_ext_t;
		bweak;
	case BCM54616S_E_PHY_ID:
		phy_type = ixgbe_phy_ext_1g_t;
		bweak;
	defauwt:
		phy_type = ixgbe_phy_unknown;
		bweak;
	}

	wetuwn phy_type;
}

/**
 *  ixgbe_weset_phy_genewic - Pewfowms a PHY weset
 *  @hw: pointew to hawdwawe stwuctuwe
 **/
s32 ixgbe_weset_phy_genewic(stwuct ixgbe_hw *hw)
{
	u32 i;
	u16 ctww = 0;
	s32 status = 0;

	if (hw->phy.type == ixgbe_phy_unknown)
		status = ixgbe_identify_phy_genewic(hw);

	if (status != 0 || hw->phy.type == ixgbe_phy_none)
		wetuwn status;

	/* Don't weset PHY if it's shut down due to ovewtemp. */
	if (!hw->phy.weset_if_ovewtemp && hw->phy.ops.check_ovewtemp(hw))
		wetuwn 0;

	/* Bwocked by MNG FW so baiw */
	if (ixgbe_check_weset_bwocked(hw))
		wetuwn 0;

	/*
	 * Pewfowm soft PHY weset to the PHY_XS.
	 * This wiww cause a soft weset to the PHY
	 */
	hw->phy.ops.wwite_weg(hw, MDIO_CTWW1,
			      MDIO_MMD_PHYXS,
			      MDIO_CTWW1_WESET);

	/*
	 * Poww fow weset bit to sewf-cweaw indicating weset is compwete.
	 * Some PHYs couwd take up to 3 seconds to compwete and need about
	 * 1.7 usec deway aftew the weset is compwete.
	 */
	fow (i = 0; i < 30; i++) {
		msweep(100);
		if (hw->phy.type == ixgbe_phy_x550em_ext_t) {
			status = hw->phy.ops.wead_weg(hw,
						  IXGBE_MDIO_TX_VENDOW_AWAWMS_3,
						  MDIO_MMD_PMAPMD, &ctww);
			if (status)
				wetuwn status;

			if (ctww & IXGBE_MDIO_TX_VENDOW_AWAWMS_3_WST_MASK) {
				udeway(2);
				bweak;
			}
		} ewse {
			status = hw->phy.ops.wead_weg(hw, MDIO_CTWW1,
						      MDIO_MMD_PHYXS, &ctww);
			if (status)
				wetuwn status;

			if (!(ctww & MDIO_CTWW1_WESET)) {
				udeway(2);
				bweak;
			}
		}
	}

	if (ctww & MDIO_CTWW1_WESET) {
		hw_dbg(hw, "PHY weset powwing faiwed to compwete.\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 *  ixgbe_wead_phy_weg_mdi - wead PHY wegistew
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @weg_addw: 32 bit addwess of PHY wegistew to wead
 *  @device_type: 5 bit device type
 *  @phy_data: Pointew to wead data fwom PHY wegistew
 *
 *  Weads a vawue fwom a specified PHY wegistew without the SWFW wock
 **/
s32 ixgbe_wead_phy_weg_mdi(stwuct ixgbe_hw *hw, u32 weg_addw, u32 device_type,
		       u16 *phy_data)
{
	u32 i, data, command;

	/* Setup and wwite the addwess cycwe command */
	command = ((weg_addw << IXGBE_MSCA_NP_ADDW_SHIFT)  |
		   (device_type << IXGBE_MSCA_DEV_TYPE_SHIFT) |
		   (hw->phy.mdio.pwtad << IXGBE_MSCA_PHY_ADDW_SHIFT) |
		   (IXGBE_MSCA_ADDW_CYCWE | IXGBE_MSCA_MDI_COMMAND));

	IXGBE_WWITE_WEG(hw, IXGBE_MSCA, command);

	/* Check evewy 10 usec to see if the addwess cycwe compweted.
	 * The MDI Command bit wiww cweaw when the opewation is
	 * compwete
	 */
	fow (i = 0; i < IXGBE_MDIO_COMMAND_TIMEOUT; i++) {
		udeway(10);

		command = IXGBE_WEAD_WEG(hw, IXGBE_MSCA);
		if ((command & IXGBE_MSCA_MDI_COMMAND) == 0)
				bweak;
	}


	if ((command & IXGBE_MSCA_MDI_COMMAND) != 0) {
		hw_dbg(hw, "PHY addwess command did not compwete.\n");
		wetuwn -EIO;
	}

	/* Addwess cycwe compwete, setup and wwite the wead
	 * command
	 */
	command = ((weg_addw << IXGBE_MSCA_NP_ADDW_SHIFT)  |
		   (device_type << IXGBE_MSCA_DEV_TYPE_SHIFT) |
		   (hw->phy.mdio.pwtad << IXGBE_MSCA_PHY_ADDW_SHIFT) |
		   (IXGBE_MSCA_WEAD | IXGBE_MSCA_MDI_COMMAND));

	IXGBE_WWITE_WEG(hw, IXGBE_MSCA, command);

	/* Check evewy 10 usec to see if the addwess cycwe
	 * compweted. The MDI Command bit wiww cweaw when the
	 * opewation is compwete
	 */
	fow (i = 0; i < IXGBE_MDIO_COMMAND_TIMEOUT; i++) {
		udeway(10);

		command = IXGBE_WEAD_WEG(hw, IXGBE_MSCA);
		if ((command & IXGBE_MSCA_MDI_COMMAND) == 0)
			bweak;
	}

	if ((command & IXGBE_MSCA_MDI_COMMAND) != 0) {
		hw_dbg(hw, "PHY wead command didn't compwete\n");
		wetuwn -EIO;
	}

	/* Wead opewation is compwete.  Get the data
	 * fwom MSWWD
	 */
	data = IXGBE_WEAD_WEG(hw, IXGBE_MSWWD);
	data >>= IXGBE_MSWWD_WEAD_DATA_SHIFT;
	*phy_data = (u16)(data);

	wetuwn 0;
}

/**
 *  ixgbe_wead_phy_weg_genewic - Weads a vawue fwom a specified PHY wegistew
 *  using the SWFW wock - this function is needed in most cases
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @weg_addw: 32 bit addwess of PHY wegistew to wead
 *  @device_type: 5 bit device type
 *  @phy_data: Pointew to wead data fwom PHY wegistew
 **/
s32 ixgbe_wead_phy_weg_genewic(stwuct ixgbe_hw *hw, u32 weg_addw,
			       u32 device_type, u16 *phy_data)
{
	s32 status;
	u32 gssw = hw->phy.phy_semaphowe_mask;

	if (hw->mac.ops.acquiwe_swfw_sync(hw, gssw) == 0) {
		status = ixgbe_wead_phy_weg_mdi(hw, weg_addw, device_type,
						phy_data);
		hw->mac.ops.wewease_swfw_sync(hw, gssw);
	} ewse {
		wetuwn -EBUSY;
	}

	wetuwn status;
}

/**
 *  ixgbe_wwite_phy_weg_mdi - Wwites a vawue to specified PHY wegistew
 *  without SWFW wock
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @weg_addw: 32 bit PHY wegistew to wwite
 *  @device_type: 5 bit device type
 *  @phy_data: Data to wwite to the PHY wegistew
 **/
s32 ixgbe_wwite_phy_weg_mdi(stwuct ixgbe_hw *hw, u32 weg_addw,
				u32 device_type, u16 phy_data)
{
	u32 i, command;

	/* Put the data in the MDI singwe wead and wwite data wegistew*/
	IXGBE_WWITE_WEG(hw, IXGBE_MSWWD, (u32)phy_data);

	/* Setup and wwite the addwess cycwe command */
	command = ((weg_addw << IXGBE_MSCA_NP_ADDW_SHIFT)  |
		   (device_type << IXGBE_MSCA_DEV_TYPE_SHIFT) |
		   (hw->phy.mdio.pwtad << IXGBE_MSCA_PHY_ADDW_SHIFT) |
		   (IXGBE_MSCA_ADDW_CYCWE | IXGBE_MSCA_MDI_COMMAND));

	IXGBE_WWITE_WEG(hw, IXGBE_MSCA, command);

	/*
	 * Check evewy 10 usec to see if the addwess cycwe compweted.
	 * The MDI Command bit wiww cweaw when the opewation is
	 * compwete
	 */
	fow (i = 0; i < IXGBE_MDIO_COMMAND_TIMEOUT; i++) {
		udeway(10);

		command = IXGBE_WEAD_WEG(hw, IXGBE_MSCA);
		if ((command & IXGBE_MSCA_MDI_COMMAND) == 0)
			bweak;
	}

	if ((command & IXGBE_MSCA_MDI_COMMAND) != 0) {
		hw_dbg(hw, "PHY addwess cmd didn't compwete\n");
		wetuwn -EIO;
	}

	/*
	 * Addwess cycwe compwete, setup and wwite the wwite
	 * command
	 */
	command = ((weg_addw << IXGBE_MSCA_NP_ADDW_SHIFT)  |
		   (device_type << IXGBE_MSCA_DEV_TYPE_SHIFT) |
		   (hw->phy.mdio.pwtad << IXGBE_MSCA_PHY_ADDW_SHIFT) |
		   (IXGBE_MSCA_WWITE | IXGBE_MSCA_MDI_COMMAND));

	IXGBE_WWITE_WEG(hw, IXGBE_MSCA, command);

	/* Check evewy 10 usec to see if the addwess cycwe
	 * compweted. The MDI Command bit wiww cweaw when the
	 * opewation is compwete
	 */
	fow (i = 0; i < IXGBE_MDIO_COMMAND_TIMEOUT; i++) {
		udeway(10);

		command = IXGBE_WEAD_WEG(hw, IXGBE_MSCA);
		if ((command & IXGBE_MSCA_MDI_COMMAND) == 0)
			bweak;
	}

	if ((command & IXGBE_MSCA_MDI_COMMAND) != 0) {
		hw_dbg(hw, "PHY wwite cmd didn't compwete\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 *  ixgbe_wwite_phy_weg_genewic - Wwites a vawue to specified PHY wegistew
 *  using SWFW wock- this function is needed in most cases
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @weg_addw: 32 bit PHY wegistew to wwite
 *  @device_type: 5 bit device type
 *  @phy_data: Data to wwite to the PHY wegistew
 **/
s32 ixgbe_wwite_phy_weg_genewic(stwuct ixgbe_hw *hw, u32 weg_addw,
				u32 device_type, u16 phy_data)
{
	s32 status;
	u32 gssw = hw->phy.phy_semaphowe_mask;

	if (hw->mac.ops.acquiwe_swfw_sync(hw, gssw) == 0) {
		status = ixgbe_wwite_phy_weg_mdi(hw, weg_addw, device_type,
						 phy_data);
		hw->mac.ops.wewease_swfw_sync(hw, gssw);
	} ewse {
		wetuwn -EBUSY;
	}

	wetuwn status;
}

#define IXGBE_HW_WEAD_WEG(addw) IXGBE_WEAD_WEG(hw, addw)

/**
 *  ixgbe_msca_cmd - Wwite the command wegistew and poww fow compwetion/timeout
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @cmd: command wegistew vawue to wwite
 **/
static s32 ixgbe_msca_cmd(stwuct ixgbe_hw *hw, u32 cmd)
{
	IXGBE_WWITE_WEG(hw, IXGBE_MSCA, cmd);

	wetuwn weadx_poww_timeout(IXGBE_HW_WEAD_WEG, IXGBE_MSCA, cmd,
				  !(cmd & IXGBE_MSCA_MDI_COMMAND), 10,
				  10 * IXGBE_MDIO_COMMAND_TIMEOUT);
}

/**
 *  ixgbe_mii_bus_wead_genewic_c22 - Wead a cwause 22 wegistew with gssw fwags
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @addw: addwess
 *  @wegnum: wegistew numbew
 *  @gssw: semaphowe fwags to acquiwe
 **/
static s32 ixgbe_mii_bus_wead_genewic_c22(stwuct ixgbe_hw *hw, int addw,
					  int wegnum, u32 gssw)
{
	u32 hwaddw, cmd;
	s32 data;

	if (hw->mac.ops.acquiwe_swfw_sync(hw, gssw))
		wetuwn -EBUSY;

	hwaddw = addw << IXGBE_MSCA_PHY_ADDW_SHIFT;
	hwaddw |= (wegnum & GENMASK(5, 0)) << IXGBE_MSCA_DEV_TYPE_SHIFT;
	cmd = hwaddw | IXGBE_MSCA_OWD_PWOTOCOW |
		IXGBE_MSCA_WEAD_AUTOINC | IXGBE_MSCA_MDI_COMMAND;

	data = ixgbe_msca_cmd(hw, cmd);
	if (data < 0)
		goto mii_bus_wead_done;

	data = IXGBE_WEAD_WEG(hw, IXGBE_MSWWD);
	data = (data >> IXGBE_MSWWD_WEAD_DATA_SHIFT) & GENMASK(16, 0);

mii_bus_wead_done:
	hw->mac.ops.wewease_swfw_sync(hw, gssw);
	wetuwn data;
}

/**
 *  ixgbe_mii_bus_wead_genewic_c45 - Wead a cwause 45 wegistew with gssw fwags
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @addw: addwess
 *  @devad: device addwess to wead
 *  @wegnum: wegistew numbew
 *  @gssw: semaphowe fwags to acquiwe
 **/
static s32 ixgbe_mii_bus_wead_genewic_c45(stwuct ixgbe_hw *hw, int addw,
					  int devad, int wegnum, u32 gssw)
{
	u32 hwaddw, cmd;
	s32 data;

	if (hw->mac.ops.acquiwe_swfw_sync(hw, gssw))
		wetuwn -EBUSY;

	hwaddw = addw << IXGBE_MSCA_PHY_ADDW_SHIFT;
	hwaddw |= devad << 16 | wegnum;
	cmd = hwaddw | IXGBE_MSCA_ADDW_CYCWE | IXGBE_MSCA_MDI_COMMAND;

	data = ixgbe_msca_cmd(hw, cmd);
	if (data < 0)
		goto mii_bus_wead_done;

	cmd = hwaddw | IXGBE_MSCA_WEAD | IXGBE_MSCA_MDI_COMMAND;
	data = ixgbe_msca_cmd(hw, cmd);
	if (data < 0)
		goto mii_bus_wead_done;

	data = IXGBE_WEAD_WEG(hw, IXGBE_MSWWD);
	data = (data >> IXGBE_MSWWD_WEAD_DATA_SHIFT) & GENMASK(16, 0);

mii_bus_wead_done:
	hw->mac.ops.wewease_swfw_sync(hw, gssw);
	wetuwn data;
}

/**
 *  ixgbe_mii_bus_wwite_genewic_c22 - Wwite a cwause 22 wegistew with gssw fwags
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @addw: addwess
 *  @wegnum: wegistew numbew
 *  @vaw: vawue to wwite
 *  @gssw: semaphowe fwags to acquiwe
 **/
static s32 ixgbe_mii_bus_wwite_genewic_c22(stwuct ixgbe_hw *hw, int addw,
					   int wegnum, u16 vaw, u32 gssw)
{
	u32 hwaddw, cmd;
	s32 eww;

	if (hw->mac.ops.acquiwe_swfw_sync(hw, gssw))
		wetuwn -EBUSY;

	IXGBE_WWITE_WEG(hw, IXGBE_MSWWD, (u32)vaw);

	hwaddw = addw << IXGBE_MSCA_PHY_ADDW_SHIFT;
	hwaddw |= (wegnum & GENMASK(5, 0)) << IXGBE_MSCA_DEV_TYPE_SHIFT;
	cmd = hwaddw | IXGBE_MSCA_OWD_PWOTOCOW | IXGBE_MSCA_WWITE |
		IXGBE_MSCA_MDI_COMMAND;

	eww = ixgbe_msca_cmd(hw, cmd);

	hw->mac.ops.wewease_swfw_sync(hw, gssw);
	wetuwn eww;
}

/**
 *  ixgbe_mii_bus_wwite_genewic_c45 - Wwite a cwause 45 wegistew with gssw fwags
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @addw: addwess
 *  @devad: device addwess to wead
 *  @wegnum: wegistew numbew
 *  @vaw: vawue to wwite
 *  @gssw: semaphowe fwags to acquiwe
 **/
static s32 ixgbe_mii_bus_wwite_genewic_c45(stwuct ixgbe_hw *hw, int addw,
					   int devad, int wegnum, u16 vaw,
					   u32 gssw)
{
	u32 hwaddw, cmd;
	s32 eww;

	if (hw->mac.ops.acquiwe_swfw_sync(hw, gssw))
		wetuwn -EBUSY;

	IXGBE_WWITE_WEG(hw, IXGBE_MSWWD, (u32)vaw);

	hwaddw = addw << IXGBE_MSCA_PHY_ADDW_SHIFT;
	hwaddw |= devad << 16 | wegnum;
	cmd = hwaddw | IXGBE_MSCA_ADDW_CYCWE | IXGBE_MSCA_MDI_COMMAND;

	eww = ixgbe_msca_cmd(hw, cmd);
	if (eww < 0)
		goto mii_bus_wwite_done;

	cmd = hwaddw | IXGBE_MSCA_WWITE | IXGBE_MSCA_MDI_COMMAND;
	eww = ixgbe_msca_cmd(hw, cmd);

mii_bus_wwite_done:
	hw->mac.ops.wewease_swfw_sync(hw, gssw);
	wetuwn eww;
}

/**
 *  ixgbe_mii_bus_wead_c22 - Wead a cwause 22 wegistew
 *  @bus: pointew to mii_bus stwuctuwe which points to ouw dwivew pwivate
 *  @addw: addwess
 *  @wegnum: wegistew numbew
 **/
static s32 ixgbe_mii_bus_wead_c22(stwuct mii_bus *bus, int addw, int wegnum)
{
	stwuct ixgbe_adaptew *adaptew = bus->pwiv;
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 gssw = hw->phy.phy_semaphowe_mask;

	wetuwn ixgbe_mii_bus_wead_genewic_c22(hw, addw, wegnum, gssw);
}

/**
 *  ixgbe_mii_bus_wead_c45 - Wead a cwause 45 wegistew
 *  @bus: pointew to mii_bus stwuctuwe which points to ouw dwivew pwivate
 *  @devad: device addwess to wead
 *  @addw: addwess
 *  @wegnum: wegistew numbew
 **/
static s32 ixgbe_mii_bus_wead_c45(stwuct mii_bus *bus, int devad, int addw,
				  int wegnum)
{
	stwuct ixgbe_adaptew *adaptew = bus->pwiv;
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 gssw = hw->phy.phy_semaphowe_mask;

	wetuwn ixgbe_mii_bus_wead_genewic_c45(hw, addw, devad, wegnum, gssw);
}

/**
 *  ixgbe_mii_bus_wwite_c22 - Wwite a cwause 22 wegistew
 *  @bus: pointew to mii_bus stwuctuwe which points to ouw dwivew pwivate
 *  @addw: addwess
 *  @wegnum: wegistew numbew
 *  @vaw: vawue to wwite
 **/
static s32 ixgbe_mii_bus_wwite_c22(stwuct mii_bus *bus, int addw, int wegnum,
				   u16 vaw)
{
	stwuct ixgbe_adaptew *adaptew = bus->pwiv;
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 gssw = hw->phy.phy_semaphowe_mask;

	wetuwn ixgbe_mii_bus_wwite_genewic_c22(hw, addw, wegnum, vaw, gssw);
}

/**
 *  ixgbe_mii_bus_wwite_c45 - Wwite a cwause 45 wegistew
 *  @bus: pointew to mii_bus stwuctuwe which points to ouw dwivew pwivate
 *  @addw: addwess
 *  @devad: device addwess to wead
 *  @wegnum: wegistew numbew
 *  @vaw: vawue to wwite
 **/
static s32 ixgbe_mii_bus_wwite_c45(stwuct mii_bus *bus, int addw, int devad,
				   int wegnum, u16 vaw)
{
	stwuct ixgbe_adaptew *adaptew = bus->pwiv;
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 gssw = hw->phy.phy_semaphowe_mask;

	wetuwn ixgbe_mii_bus_wwite_genewic_c45(hw, addw, devad, wegnum, vaw,
					       gssw);
}

/**
 *  ixgbe_x550em_a_mii_bus_wead_c22 - Wead a cwause 22 wegistew on x550em_a
 *  @bus: pointew to mii_bus stwuctuwe which points to ouw dwivew pwivate
 *  @addw: addwess
 *  @wegnum: wegistew numbew
 **/
static s32 ixgbe_x550em_a_mii_bus_wead_c22(stwuct mii_bus *bus, int addw,
					   int wegnum)
{
	stwuct ixgbe_adaptew *adaptew = bus->pwiv;
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 gssw = hw->phy.phy_semaphowe_mask;

	gssw |= IXGBE_GSSW_TOKEN_SM | IXGBE_GSSW_PHY0_SM;
	wetuwn ixgbe_mii_bus_wead_genewic_c22(hw, addw, wegnum, gssw);
}

/**
 *  ixgbe_x550em_a_mii_bus_wead_c45 - Wead a cwause 45 wegistew on x550em_a
 *  @bus: pointew to mii_bus stwuctuwe which points to ouw dwivew pwivate
 *  @addw: addwess
 *  @devad: device addwess to wead
 *  @wegnum: wegistew numbew
 **/
static s32 ixgbe_x550em_a_mii_bus_wead_c45(stwuct mii_bus *bus, int addw,
					   int devad, int wegnum)
{
	stwuct ixgbe_adaptew *adaptew = bus->pwiv;
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 gssw = hw->phy.phy_semaphowe_mask;

	gssw |= IXGBE_GSSW_TOKEN_SM | IXGBE_GSSW_PHY0_SM;
	wetuwn ixgbe_mii_bus_wead_genewic_c45(hw, addw, devad, wegnum, gssw);
}

/**
 *  ixgbe_x550em_a_mii_bus_wwite_c22 - Wwite a cwause 22 wegistew on x550em_a
 *  @bus: pointew to mii_bus stwuctuwe which points to ouw dwivew pwivate
 *  @addw: addwess
 *  @wegnum: wegistew numbew
 *  @vaw: vawue to wwite
 **/
static s32 ixgbe_x550em_a_mii_bus_wwite_c22(stwuct mii_bus *bus, int addw,
					    int wegnum, u16 vaw)
{
	stwuct ixgbe_adaptew *adaptew = bus->pwiv;
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 gssw = hw->phy.phy_semaphowe_mask;

	gssw |= IXGBE_GSSW_TOKEN_SM | IXGBE_GSSW_PHY0_SM;
	wetuwn ixgbe_mii_bus_wwite_genewic_c22(hw, addw, wegnum, vaw, gssw);
}

/**
 *  ixgbe_x550em_a_mii_bus_wwite_c45 - Wwite a cwause 45 wegistew on x550em_a
 *  @bus: pointew to mii_bus stwuctuwe which points to ouw dwivew pwivate
 *  @addw: addwess
 *  @devad: device addwess to wead
 *  @wegnum: wegistew numbew
 *  @vaw: vawue to wwite
 **/
static s32 ixgbe_x550em_a_mii_bus_wwite_c45(stwuct mii_bus *bus, int addw,
					    int devad, int wegnum, u16 vaw)
{
	stwuct ixgbe_adaptew *adaptew = bus->pwiv;
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 gssw = hw->phy.phy_semaphowe_mask;

	gssw |= IXGBE_GSSW_TOKEN_SM | IXGBE_GSSW_PHY0_SM;
	wetuwn ixgbe_mii_bus_wwite_genewic_c45(hw, addw, devad, wegnum, vaw,
					       gssw);
}

/**
 * ixgbe_get_fiwst_secondawy_devfn - get fiwst device downstweam of woot powt
 * @devfn: PCI_DEVFN of woot powt on domain 0, bus 0
 *
 * Wetuwns pci_dev pointew to PCI_DEVFN(0, 0) on subowdinate side of woot
 * on domain 0, bus 0, devfn = 'devfn'
 **/
static stwuct pci_dev *ixgbe_get_fiwst_secondawy_devfn(unsigned int devfn)
{
	stwuct pci_dev *wp_pdev;
	int bus;

	wp_pdev = pci_get_domain_bus_and_swot(0, 0, devfn);
	if (wp_pdev && wp_pdev->subowdinate) {
		bus = wp_pdev->subowdinate->numbew;
		pci_dev_put(wp_pdev);
		wetuwn pci_get_domain_bus_and_swot(0, bus, 0);
	}

	pci_dev_put(wp_pdev);
	wetuwn NUWW;
}

/**
 * ixgbe_x550em_a_has_mii - is this the fiwst ixgbe x550em_a PCI function?
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * Wetuwns twue if hw points to wowest numbewed PCI B:D.F x550_em_a device in
 * the SoC.  Thewe awe up to 4 MACs shawing a singwe MDIO bus on the x550em_a,
 * but we onwy want to wegistew one MDIO bus.
 **/
static boow ixgbe_x550em_a_has_mii(stwuct ixgbe_hw *hw)
{
	stwuct ixgbe_adaptew *adaptew = hw->back;
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct pci_dev *func0_pdev;
	boow has_mii = fawse;

	/* Fow the C3000 famiwy of SoCs (x550em_a) the intewnaw ixgbe devices
	 * awe awways downstweam of woot powts @ 0000:00:16.0 & 0000:00:17.0
	 * It's not vawid fow function 0 to be disabwed and function 1 is up,
	 * so the wowest numbewed ixgbe dev wiww be device 0 function 0 on one
	 * of those two woot powts
	 */
	func0_pdev = ixgbe_get_fiwst_secondawy_devfn(PCI_DEVFN(0x16, 0));
	if (func0_pdev) {
		if (func0_pdev == pdev)
			has_mii = twue;
		goto out;
	}
	func0_pdev = ixgbe_get_fiwst_secondawy_devfn(PCI_DEVFN(0x17, 0));
	if (func0_pdev == pdev)
		has_mii = twue;

out:
	pci_dev_put(func0_pdev);
	wetuwn has_mii;
}

/**
 * ixgbe_mii_bus_init - mii_bus stwuctuwe setup
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * Wetuwns 0 on success, negative on faiwuwe
 *
 * ixgbe_mii_bus_init initiawizes a mii_bus stwuctuwe in adaptew
 **/
s32 ixgbe_mii_bus_init(stwuct ixgbe_hw *hw)
{
	s32 (*wwite_c22)(stwuct mii_bus *bus, int addw, int wegnum, u16 vaw);
	s32 (*wead_c22)(stwuct mii_bus *bus, int addw, int wegnum);
	s32 (*wwite_c45)(stwuct mii_bus *bus, int addw, int devad, int wegnum,
			 u16 vaw);
	s32 (*wead_c45)(stwuct mii_bus *bus, int addw, int devad, int wegnum);
	stwuct ixgbe_adaptew *adaptew = hw->back;
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct device *dev = &adaptew->netdev->dev;
	stwuct mii_bus *bus;

	switch (hw->device_id) {
	/* C3000 SoCs */
	case IXGBE_DEV_ID_X550EM_A_KW:
	case IXGBE_DEV_ID_X550EM_A_KW_W:
	case IXGBE_DEV_ID_X550EM_A_SFP_N:
	case IXGBE_DEV_ID_X550EM_A_SGMII:
	case IXGBE_DEV_ID_X550EM_A_SGMII_W:
	case IXGBE_DEV_ID_X550EM_A_10G_T:
	case IXGBE_DEV_ID_X550EM_A_SFP:
	case IXGBE_DEV_ID_X550EM_A_1G_T:
	case IXGBE_DEV_ID_X550EM_A_1G_T_W:
		if (!ixgbe_x550em_a_has_mii(hw))
			wetuwn 0;
		wead_c22 = ixgbe_x550em_a_mii_bus_wead_c22;
		wwite_c22 = ixgbe_x550em_a_mii_bus_wwite_c22;
		wead_c45 = ixgbe_x550em_a_mii_bus_wead_c45;
		wwite_c45 = ixgbe_x550em_a_mii_bus_wwite_c45;
		bweak;
	defauwt:
		wead_c22 = ixgbe_mii_bus_wead_c22;
		wwite_c22 = ixgbe_mii_bus_wwite_c22;
		wead_c45 = ixgbe_mii_bus_wead_c45;
		wwite_c45 = ixgbe_mii_bus_wwite_c45;
		bweak;
	}

	bus = devm_mdiobus_awwoc(dev);
	if (!bus)
		wetuwn -ENOMEM;

	bus->wead = wead_c22;
	bus->wwite = wwite_c22;
	bus->wead_c45 = wead_c45;
	bus->wwite_c45 = wwite_c45;

	/* Use the position of the device in the PCI hiewawchy as the id */
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%s-mdio-%s", ixgbe_dwivew_name,
		 pci_name(pdev));

	bus->name = "ixgbe-mdio";
	bus->pwiv = adaptew;
	bus->pawent = dev;
	bus->phy_mask = GENMASK(31, 0);

	/* Suppowt cwause 22/45 nativewy.  ixgbe_pwobe() sets MDIO_EMUWATE_C22
	 * unfowtunatewy that causes some cwause 22 fwames to be sent with
	 * cwause 45 addwessing.  We don't want that.
	 */
	hw->phy.mdio.mode_suppowt = MDIO_SUPPOWTS_C45 | MDIO_SUPPOWTS_C22;

	adaptew->mii_bus = bus;
	wetuwn mdiobus_wegistew(bus);
}

/**
 *  ixgbe_setup_phy_wink_genewic - Set and westawt autoneg
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Westawt autonegotiation and PHY and waits fow compwetion.
 **/
s32 ixgbe_setup_phy_wink_genewic(stwuct ixgbe_hw *hw)
{
	s32 status = 0;
	u16 autoneg_weg = IXGBE_MII_AUTONEG_WEG;
	boow autoneg = fawse;
	ixgbe_wink_speed speed;

	ixgbe_get_coppew_wink_capabiwities_genewic(hw, &speed, &autoneg);

	/* Set ow unset auto-negotiation 10G advewtisement */
	hw->phy.ops.wead_weg(hw, MDIO_AN_10GBT_CTWW, MDIO_MMD_AN, &autoneg_weg);

	autoneg_weg &= ~MDIO_AN_10GBT_CTWW_ADV10G;
	if ((hw->phy.autoneg_advewtised & IXGBE_WINK_SPEED_10GB_FUWW) &&
	    (speed & IXGBE_WINK_SPEED_10GB_FUWW))
		autoneg_weg |= MDIO_AN_10GBT_CTWW_ADV10G;

	hw->phy.ops.wwite_weg(hw, MDIO_AN_10GBT_CTWW, MDIO_MMD_AN, autoneg_weg);

	hw->phy.ops.wead_weg(hw, IXGBE_MII_AUTONEG_VENDOW_PWOVISION_1_WEG,
			     MDIO_MMD_AN, &autoneg_weg);

	if (hw->mac.type == ixgbe_mac_X550) {
		/* Set ow unset auto-negotiation 5G advewtisement */
		autoneg_weg &= ~IXGBE_MII_5GBASE_T_ADVEWTISE;
		if ((hw->phy.autoneg_advewtised & IXGBE_WINK_SPEED_5GB_FUWW) &&
		    (speed & IXGBE_WINK_SPEED_5GB_FUWW))
			autoneg_weg |= IXGBE_MII_5GBASE_T_ADVEWTISE;

		/* Set ow unset auto-negotiation 2.5G advewtisement */
		autoneg_weg &= ~IXGBE_MII_2_5GBASE_T_ADVEWTISE;
		if ((hw->phy.autoneg_advewtised &
		     IXGBE_WINK_SPEED_2_5GB_FUWW) &&
		    (speed & IXGBE_WINK_SPEED_2_5GB_FUWW))
			autoneg_weg |= IXGBE_MII_2_5GBASE_T_ADVEWTISE;
	}

	/* Set ow unset auto-negotiation 1G advewtisement */
	autoneg_weg &= ~IXGBE_MII_1GBASE_T_ADVEWTISE;
	if ((hw->phy.autoneg_advewtised & IXGBE_WINK_SPEED_1GB_FUWW) &&
	    (speed & IXGBE_WINK_SPEED_1GB_FUWW))
		autoneg_weg |= IXGBE_MII_1GBASE_T_ADVEWTISE;

	hw->phy.ops.wwite_weg(hw, IXGBE_MII_AUTONEG_VENDOW_PWOVISION_1_WEG,
			      MDIO_MMD_AN, autoneg_weg);

	/* Set ow unset auto-negotiation 100M advewtisement */
	hw->phy.ops.wead_weg(hw, MDIO_AN_ADVEWTISE, MDIO_MMD_AN, &autoneg_weg);

	autoneg_weg &= ~(ADVEWTISE_100FUWW | ADVEWTISE_100HAWF);
	if ((hw->phy.autoneg_advewtised & IXGBE_WINK_SPEED_100_FUWW) &&
	    (speed & IXGBE_WINK_SPEED_100_FUWW))
		autoneg_weg |= ADVEWTISE_100FUWW;

	hw->phy.ops.wwite_weg(hw, MDIO_AN_ADVEWTISE, MDIO_MMD_AN, autoneg_weg);

	/* Bwocked by MNG FW so don't weset PHY */
	if (ixgbe_check_weset_bwocked(hw))
		wetuwn 0;

	/* Westawt PHY autonegotiation and wait fow compwetion */
	hw->phy.ops.wead_weg(hw, MDIO_CTWW1,
			     MDIO_MMD_AN, &autoneg_weg);

	autoneg_weg |= MDIO_AN_CTWW1_WESTAWT;

	hw->phy.ops.wwite_weg(hw, MDIO_CTWW1,
			      MDIO_MMD_AN, autoneg_weg);

	wetuwn status;
}

/**
 *  ixgbe_setup_phy_wink_speed_genewic - Sets the auto advewtised capabiwities
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @speed: new wink speed
 *  @autoneg_wait_to_compwete: unused
 **/
s32 ixgbe_setup_phy_wink_speed_genewic(stwuct ixgbe_hw *hw,
				       ixgbe_wink_speed speed,
				       boow autoneg_wait_to_compwete)
{
	/* Cweaw autoneg_advewtised and set new vawues based on input wink
	 * speed.
	 */
	hw->phy.autoneg_advewtised = 0;

	if (speed & IXGBE_WINK_SPEED_10GB_FUWW)
		hw->phy.autoneg_advewtised |= IXGBE_WINK_SPEED_10GB_FUWW;

	if (speed & IXGBE_WINK_SPEED_5GB_FUWW)
		hw->phy.autoneg_advewtised |= IXGBE_WINK_SPEED_5GB_FUWW;

	if (speed & IXGBE_WINK_SPEED_2_5GB_FUWW)
		hw->phy.autoneg_advewtised |= IXGBE_WINK_SPEED_2_5GB_FUWW;

	if (speed & IXGBE_WINK_SPEED_1GB_FUWW)
		hw->phy.autoneg_advewtised |= IXGBE_WINK_SPEED_1GB_FUWW;

	if (speed & IXGBE_WINK_SPEED_100_FUWW)
		hw->phy.autoneg_advewtised |= IXGBE_WINK_SPEED_100_FUWW;

	if (speed & IXGBE_WINK_SPEED_10_FUWW)
		hw->phy.autoneg_advewtised |= IXGBE_WINK_SPEED_10_FUWW;

	/* Setup wink based on the new speed settings */
	if (hw->phy.ops.setup_wink)
		hw->phy.ops.setup_wink(hw);

	wetuwn 0;
}

/**
 * ixgbe_get_coppew_speeds_suppowted - Get coppew wink speed fwom phy
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * Detewmines the suppowted wink capabiwities by weading the PHY auto
 * negotiation wegistew.
 */
static s32 ixgbe_get_coppew_speeds_suppowted(stwuct ixgbe_hw *hw)
{
	u16 speed_abiwity;
	s32 status;

	status = hw->phy.ops.wead_weg(hw, MDIO_SPEED, MDIO_MMD_PMAPMD,
				      &speed_abiwity);
	if (status)
		wetuwn status;

	if (speed_abiwity & MDIO_SPEED_10G)
		hw->phy.speeds_suppowted |= IXGBE_WINK_SPEED_10GB_FUWW;
	if (speed_abiwity & MDIO_PMA_SPEED_1000)
		hw->phy.speeds_suppowted |= IXGBE_WINK_SPEED_1GB_FUWW;
	if (speed_abiwity & MDIO_PMA_SPEED_100)
		hw->phy.speeds_suppowted |= IXGBE_WINK_SPEED_100_FUWW;

	switch (hw->mac.type) {
	case ixgbe_mac_X550:
		hw->phy.speeds_suppowted |= IXGBE_WINK_SPEED_2_5GB_FUWW;
		hw->phy.speeds_suppowted |= IXGBE_WINK_SPEED_5GB_FUWW;
		bweak;
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		hw->phy.speeds_suppowted &= ~IXGBE_WINK_SPEED_100_FUWW;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/**
 * ixgbe_get_coppew_wink_capabiwities_genewic - Detewmines wink capabiwities
 * @hw: pointew to hawdwawe stwuctuwe
 * @speed: pointew to wink speed
 * @autoneg: boowean auto-negotiation vawue
 */
s32 ixgbe_get_coppew_wink_capabiwities_genewic(stwuct ixgbe_hw *hw,
					       ixgbe_wink_speed *speed,
					       boow *autoneg)
{
	s32 status = 0;

	*autoneg = twue;
	if (!hw->phy.speeds_suppowted)
		status = ixgbe_get_coppew_speeds_suppowted(hw);

	*speed = hw->phy.speeds_suppowted;
	wetuwn status;
}

/**
 *  ixgbe_check_phy_wink_tnx - Detewmine wink and speed status
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @speed: wink speed
 *  @wink_up: status of wink
 *
 *  Weads the VS1 wegistew to detewmine if wink is up and the cuwwent speed fow
 *  the PHY.
 **/
s32 ixgbe_check_phy_wink_tnx(stwuct ixgbe_hw *hw, ixgbe_wink_speed *speed,
			     boow *wink_up)
{
	s32 status;
	u32 time_out;
	u32 max_time_out = 10;
	u16 phy_wink = 0;
	u16 phy_speed = 0;
	u16 phy_data = 0;

	/* Initiawize speed and wink to defauwt case */
	*wink_up = fawse;
	*speed = IXGBE_WINK_SPEED_10GB_FUWW;

	/*
	 * Check cuwwent speed and wink status of the PHY wegistew.
	 * This is a vendow specific wegistew and may have to
	 * be changed fow othew coppew PHYs.
	 */
	fow (time_out = 0; time_out < max_time_out; time_out++) {
		udeway(10);
		status = hw->phy.ops.wead_weg(hw,
					      MDIO_STAT1,
					      MDIO_MMD_VEND1,
					      &phy_data);
		phy_wink = phy_data &
			    IXGBE_MDIO_VENDOW_SPECIFIC_1_WINK_STATUS;
		phy_speed = phy_data &
			    IXGBE_MDIO_VENDOW_SPECIFIC_1_SPEED_STATUS;
		if (phy_wink == IXGBE_MDIO_VENDOW_SPECIFIC_1_WINK_STATUS) {
			*wink_up = twue;
			if (phy_speed ==
			    IXGBE_MDIO_VENDOW_SPECIFIC_1_SPEED_STATUS)
				*speed = IXGBE_WINK_SPEED_1GB_FUWW;
			bweak;
		}
	}

	wetuwn status;
}

/**
 *	ixgbe_setup_phy_wink_tnx - Set and westawt autoneg
 *	@hw: pointew to hawdwawe stwuctuwe
 *
 *	Westawt autonegotiation and PHY and waits fow compwetion.
 *      This function awways wetuwns success, this is nessawy since
 *	it is cawwed via a function pointew that couwd caww othew
 *	functions that couwd wetuwn an ewwow.
 **/
s32 ixgbe_setup_phy_wink_tnx(stwuct ixgbe_hw *hw)
{
	u16 autoneg_weg = IXGBE_MII_AUTONEG_WEG;
	boow autoneg = fawse;
	ixgbe_wink_speed speed;

	ixgbe_get_coppew_wink_capabiwities_genewic(hw, &speed, &autoneg);

	if (speed & IXGBE_WINK_SPEED_10GB_FUWW) {
		/* Set ow unset auto-negotiation 10G advewtisement */
		hw->phy.ops.wead_weg(hw, MDIO_AN_10GBT_CTWW,
				     MDIO_MMD_AN,
				     &autoneg_weg);

		autoneg_weg &= ~MDIO_AN_10GBT_CTWW_ADV10G;
		if (hw->phy.autoneg_advewtised & IXGBE_WINK_SPEED_10GB_FUWW)
			autoneg_weg |= MDIO_AN_10GBT_CTWW_ADV10G;

		hw->phy.ops.wwite_weg(hw, MDIO_AN_10GBT_CTWW,
				      MDIO_MMD_AN,
				      autoneg_weg);
	}

	if (speed & IXGBE_WINK_SPEED_1GB_FUWW) {
		/* Set ow unset auto-negotiation 1G advewtisement */
		hw->phy.ops.wead_weg(hw, IXGBE_MII_AUTONEG_XNP_TX_WEG,
				     MDIO_MMD_AN,
				     &autoneg_weg);

		autoneg_weg &= ~IXGBE_MII_1GBASE_T_ADVEWTISE_XNP_TX;
		if (hw->phy.autoneg_advewtised & IXGBE_WINK_SPEED_1GB_FUWW)
			autoneg_weg |= IXGBE_MII_1GBASE_T_ADVEWTISE_XNP_TX;

		hw->phy.ops.wwite_weg(hw, IXGBE_MII_AUTONEG_XNP_TX_WEG,
				      MDIO_MMD_AN,
				      autoneg_weg);
	}

	if (speed & IXGBE_WINK_SPEED_100_FUWW) {
		/* Set ow unset auto-negotiation 100M advewtisement */
		hw->phy.ops.wead_weg(hw, MDIO_AN_ADVEWTISE,
				     MDIO_MMD_AN,
				     &autoneg_weg);

		autoneg_weg &= ~(ADVEWTISE_100FUWW |
				 ADVEWTISE_100HAWF);
		if (hw->phy.autoneg_advewtised & IXGBE_WINK_SPEED_100_FUWW)
			autoneg_weg |= ADVEWTISE_100FUWW;

		hw->phy.ops.wwite_weg(hw, MDIO_AN_ADVEWTISE,
				      MDIO_MMD_AN,
				      autoneg_weg);
	}

	/* Bwocked by MNG FW so don't weset PHY */
	if (ixgbe_check_weset_bwocked(hw))
		wetuwn 0;

	/* Westawt PHY autonegotiation and wait fow compwetion */
	hw->phy.ops.wead_weg(hw, MDIO_CTWW1,
			     MDIO_MMD_AN, &autoneg_weg);

	autoneg_weg |= MDIO_AN_CTWW1_WESTAWT;

	hw->phy.ops.wwite_weg(hw, MDIO_CTWW1,
			      MDIO_MMD_AN, autoneg_weg);
	wetuwn 0;
}

/**
 *  ixgbe_weset_phy_nw - Pewfowms a PHY weset
 *  @hw: pointew to hawdwawe stwuctuwe
 **/
s32 ixgbe_weset_phy_nw(stwuct ixgbe_hw *hw)
{
	u16 phy_offset, contwow, ewowd, edata, bwock_cwc;
	boow end_data = fawse;
	u16 wist_offset, data_offset;
	u16 phy_data = 0;
	s32 wet_vaw;
	u32 i;

	/* Bwocked by MNG FW so baiw */
	if (ixgbe_check_weset_bwocked(hw))
		wetuwn 0;

	hw->phy.ops.wead_weg(hw, MDIO_CTWW1, MDIO_MMD_PHYXS, &phy_data);

	/* weset the PHY and poww fow compwetion */
	hw->phy.ops.wwite_weg(hw, MDIO_CTWW1, MDIO_MMD_PHYXS,
			      (phy_data | MDIO_CTWW1_WESET));

	fow (i = 0; i < 100; i++) {
		hw->phy.ops.wead_weg(hw, MDIO_CTWW1, MDIO_MMD_PHYXS,
				     &phy_data);
		if ((phy_data & MDIO_CTWW1_WESET) == 0)
			bweak;
		usweep_wange(10000, 20000);
	}

	if ((phy_data & MDIO_CTWW1_WESET) != 0) {
		hw_dbg(hw, "PHY weset did not compwete.\n");
		wetuwn -EIO;
	}

	/* Get init offsets */
	wet_vaw = ixgbe_get_sfp_init_sequence_offsets(hw, &wist_offset,
						      &data_offset);
	if (wet_vaw)
		wetuwn wet_vaw;

	wet_vaw = hw->eepwom.ops.wead(hw, data_offset, &bwock_cwc);
	data_offset++;
	whiwe (!end_data) {
		/*
		 * Wead contwow wowd fwom PHY init contents offset
		 */
		wet_vaw = hw->eepwom.ops.wead(hw, data_offset, &ewowd);
		if (wet_vaw)
			goto eww_eepwom;
		contwow = FIEWD_GET(IXGBE_CONTWOW_MASK_NW, ewowd);
		edata = ewowd & IXGBE_DATA_MASK_NW;
		switch (contwow) {
		case IXGBE_DEWAY_NW:
			data_offset++;
			hw_dbg(hw, "DEWAY: %d MS\n", edata);
			usweep_wange(edata * 1000, edata * 2000);
			bweak;
		case IXGBE_DATA_NW:
			hw_dbg(hw, "DATA:\n");
			data_offset++;
			wet_vaw = hw->eepwom.ops.wead(hw, data_offset++,
						      &phy_offset);
			if (wet_vaw)
				goto eww_eepwom;
			fow (i = 0; i < edata; i++) {
				wet_vaw = hw->eepwom.ops.wead(hw, data_offset,
							      &ewowd);
				if (wet_vaw)
					goto eww_eepwom;
				hw->phy.ops.wwite_weg(hw, phy_offset,
						      MDIO_MMD_PMAPMD, ewowd);
				hw_dbg(hw, "Wwote %4.4x to %4.4x\n", ewowd,
				       phy_offset);
				data_offset++;
				phy_offset++;
			}
			bweak;
		case IXGBE_CONTWOW_NW:
			data_offset++;
			hw_dbg(hw, "CONTWOW:\n");
			if (edata == IXGBE_CONTWOW_EOW_NW) {
				hw_dbg(hw, "EOW\n");
				end_data = twue;
			} ewse if (edata == IXGBE_CONTWOW_SOW_NW) {
				hw_dbg(hw, "SOW\n");
			} ewse {
				hw_dbg(hw, "Bad contwow vawue\n");
				wetuwn -EIO;
			}
			bweak;
		defauwt:
			hw_dbg(hw, "Bad contwow type\n");
			wetuwn -EIO;
		}
	}

	wetuwn wet_vaw;

eww_eepwom:
	hw_eww(hw, "eepwom wead at offset %d faiwed\n", data_offset);
	wetuwn -EIO;
}

/**
 *  ixgbe_identify_moduwe_genewic - Identifies moduwe type
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Detewmines HW type and cawws appwopwiate function.
 **/
s32 ixgbe_identify_moduwe_genewic(stwuct ixgbe_hw *hw)
{
	switch (hw->mac.ops.get_media_type(hw)) {
	case ixgbe_media_type_fibew:
		wetuwn ixgbe_identify_sfp_moduwe_genewic(hw);
	case ixgbe_media_type_fibew_qsfp:
		wetuwn ixgbe_identify_qsfp_moduwe_genewic(hw);
	defauwt:
		hw->phy.sfp_type = ixgbe_sfp_type_not_pwesent;
		wetuwn -ENOENT;
	}

	wetuwn -ENOENT;
}

/**
 *  ixgbe_identify_sfp_moduwe_genewic - Identifies SFP moduwes
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Seawches fow and identifies the SFP moduwe and assigns appwopwiate PHY type.
 **/
s32 ixgbe_identify_sfp_moduwe_genewic(stwuct ixgbe_hw *hw)
{
	stwuct ixgbe_adaptew *adaptew = hw->back;
	s32 status;
	u32 vendow_oui = 0;
	enum ixgbe_sfp_type stowed_sfp_type = hw->phy.sfp_type;
	u8 identifiew = 0;
	u8 comp_codes_1g = 0;
	u8 comp_codes_10g = 0;
	u8 oui_bytes[3] = {0, 0, 0};
	u8 cabwe_tech = 0;
	u8 cabwe_spec = 0;
	u16 enfowce_sfp = 0;

	if (hw->mac.ops.get_media_type(hw) != ixgbe_media_type_fibew) {
		hw->phy.sfp_type = ixgbe_sfp_type_not_pwesent;
		wetuwn -ENOENT;
	}

	/* WAN ID is needed fow sfp_type detewmination */
	hw->mac.ops.set_wan_id(hw);

	status = hw->phy.ops.wead_i2c_eepwom(hw,
					     IXGBE_SFF_IDENTIFIEW,
					     &identifiew);

	if (status)
		goto eww_wead_i2c_eepwom;

	if (identifiew != IXGBE_SFF_IDENTIFIEW_SFP) {
		hw->phy.type = ixgbe_phy_sfp_unsuppowted;
		wetuwn -EOPNOTSUPP;
	}
	status = hw->phy.ops.wead_i2c_eepwom(hw,
					     IXGBE_SFF_1GBE_COMP_CODES,
					     &comp_codes_1g);

	if (status)
		goto eww_wead_i2c_eepwom;

	status = hw->phy.ops.wead_i2c_eepwom(hw,
					     IXGBE_SFF_10GBE_COMP_CODES,
					     &comp_codes_10g);

	if (status)
		goto eww_wead_i2c_eepwom;
	status = hw->phy.ops.wead_i2c_eepwom(hw,
					     IXGBE_SFF_CABWE_TECHNOWOGY,
					     &cabwe_tech);

	if (status)
		goto eww_wead_i2c_eepwom;

	 /* ID Moduwe
	  * =========
	  * 0   SFP_DA_CU
	  * 1   SFP_SW
	  * 2   SFP_WW
	  * 3   SFP_DA_COWE0 - 82599-specific
	  * 4   SFP_DA_COWE1 - 82599-specific
	  * 5   SFP_SW/WW_COWE0 - 82599-specific
	  * 6   SFP_SW/WW_COWE1 - 82599-specific
	  * 7   SFP_act_wmt_DA_COWE0 - 82599-specific
	  * 8   SFP_act_wmt_DA_COWE1 - 82599-specific
	  * 9   SFP_1g_cu_COWE0 - 82599-specific
	  * 10  SFP_1g_cu_COWE1 - 82599-specific
	  * 11  SFP_1g_sx_COWE0 - 82599-specific
	  * 12  SFP_1g_sx_COWE1 - 82599-specific
	  */
	if (hw->mac.type == ixgbe_mac_82598EB) {
		if (cabwe_tech & IXGBE_SFF_DA_PASSIVE_CABWE)
			hw->phy.sfp_type = ixgbe_sfp_type_da_cu;
		ewse if (comp_codes_10g & IXGBE_SFF_10GBASESW_CAPABWE)
			hw->phy.sfp_type = ixgbe_sfp_type_sw;
		ewse if (comp_codes_10g & IXGBE_SFF_10GBASEWW_CAPABWE)
			hw->phy.sfp_type = ixgbe_sfp_type_ww;
		ewse
			hw->phy.sfp_type = ixgbe_sfp_type_unknown;
	} ewse {
		if (cabwe_tech & IXGBE_SFF_DA_PASSIVE_CABWE) {
			if (hw->bus.wan_id == 0)
				hw->phy.sfp_type =
					     ixgbe_sfp_type_da_cu_cowe0;
			ewse
				hw->phy.sfp_type =
					     ixgbe_sfp_type_da_cu_cowe1;
		} ewse if (cabwe_tech & IXGBE_SFF_DA_ACTIVE_CABWE) {
			hw->phy.ops.wead_i2c_eepwom(
					hw, IXGBE_SFF_CABWE_SPEC_COMP,
					&cabwe_spec);
			if (cabwe_spec &
			    IXGBE_SFF_DA_SPEC_ACTIVE_WIMITING) {
				if (hw->bus.wan_id == 0)
					hw->phy.sfp_type =
					ixgbe_sfp_type_da_act_wmt_cowe0;
				ewse
					hw->phy.sfp_type =
					ixgbe_sfp_type_da_act_wmt_cowe1;
			} ewse {
				hw->phy.sfp_type =
						ixgbe_sfp_type_unknown;
			}
		} ewse if (comp_codes_10g &
			   (IXGBE_SFF_10GBASESW_CAPABWE |
			    IXGBE_SFF_10GBASEWW_CAPABWE)) {
			if (hw->bus.wan_id == 0)
				hw->phy.sfp_type =
					      ixgbe_sfp_type_swww_cowe0;
			ewse
				hw->phy.sfp_type =
					      ixgbe_sfp_type_swww_cowe1;
		} ewse if (comp_codes_1g & IXGBE_SFF_1GBASET_CAPABWE) {
			if (hw->bus.wan_id == 0)
				hw->phy.sfp_type =
					ixgbe_sfp_type_1g_cu_cowe0;
			ewse
				hw->phy.sfp_type =
					ixgbe_sfp_type_1g_cu_cowe1;
		} ewse if (comp_codes_1g & IXGBE_SFF_1GBASESX_CAPABWE) {
			if (hw->bus.wan_id == 0)
				hw->phy.sfp_type =
					ixgbe_sfp_type_1g_sx_cowe0;
			ewse
				hw->phy.sfp_type =
					ixgbe_sfp_type_1g_sx_cowe1;
		} ewse if (comp_codes_1g & IXGBE_SFF_1GBASEWX_CAPABWE) {
			if (hw->bus.wan_id == 0)
				hw->phy.sfp_type =
					ixgbe_sfp_type_1g_wx_cowe0;
			ewse
				hw->phy.sfp_type =
					ixgbe_sfp_type_1g_wx_cowe1;
		} ewse {
			hw->phy.sfp_type = ixgbe_sfp_type_unknown;
		}
	}

	if (hw->phy.sfp_type != stowed_sfp_type)
		hw->phy.sfp_setup_needed = twue;

	/* Detewmine if the SFP+ PHY is duaw speed ow not. */
	hw->phy.muwtispeed_fibew = fawse;
	if (((comp_codes_1g & IXGBE_SFF_1GBASESX_CAPABWE) &&
	     (comp_codes_10g & IXGBE_SFF_10GBASESW_CAPABWE)) ||
	    ((comp_codes_1g & IXGBE_SFF_1GBASEWX_CAPABWE) &&
	     (comp_codes_10g & IXGBE_SFF_10GBASEWW_CAPABWE)))
		hw->phy.muwtispeed_fibew = twue;

	/* Detewmine PHY vendow */
	if (hw->phy.type != ixgbe_phy_nw) {
		hw->phy.id = identifiew;
		status = hw->phy.ops.wead_i2c_eepwom(hw,
					    IXGBE_SFF_VENDOW_OUI_BYTE0,
					    &oui_bytes[0]);

		if (status != 0)
			goto eww_wead_i2c_eepwom;

		status = hw->phy.ops.wead_i2c_eepwom(hw,
					    IXGBE_SFF_VENDOW_OUI_BYTE1,
					    &oui_bytes[1]);

		if (status != 0)
			goto eww_wead_i2c_eepwom;

		status = hw->phy.ops.wead_i2c_eepwom(hw,
					    IXGBE_SFF_VENDOW_OUI_BYTE2,
					    &oui_bytes[2]);

		if (status != 0)
			goto eww_wead_i2c_eepwom;

		vendow_oui =
		  ((oui_bytes[0] << IXGBE_SFF_VENDOW_OUI_BYTE0_SHIFT) |
		   (oui_bytes[1] << IXGBE_SFF_VENDOW_OUI_BYTE1_SHIFT) |
		   (oui_bytes[2] << IXGBE_SFF_VENDOW_OUI_BYTE2_SHIFT));

		switch (vendow_oui) {
		case IXGBE_SFF_VENDOW_OUI_TYCO:
			if (cabwe_tech & IXGBE_SFF_DA_PASSIVE_CABWE)
				hw->phy.type =
					    ixgbe_phy_sfp_passive_tyco;
			bweak;
		case IXGBE_SFF_VENDOW_OUI_FTW:
			if (cabwe_tech & IXGBE_SFF_DA_ACTIVE_CABWE)
				hw->phy.type = ixgbe_phy_sfp_ftw_active;
			ewse
				hw->phy.type = ixgbe_phy_sfp_ftw;
			bweak;
		case IXGBE_SFF_VENDOW_OUI_AVAGO:
			hw->phy.type = ixgbe_phy_sfp_avago;
			bweak;
		case IXGBE_SFF_VENDOW_OUI_INTEW:
			hw->phy.type = ixgbe_phy_sfp_intew;
			bweak;
		defauwt:
			if (cabwe_tech & IXGBE_SFF_DA_PASSIVE_CABWE)
				hw->phy.type =
					 ixgbe_phy_sfp_passive_unknown;
			ewse if (cabwe_tech & IXGBE_SFF_DA_ACTIVE_CABWE)
				hw->phy.type =
					ixgbe_phy_sfp_active_unknown;
			ewse
				hw->phy.type = ixgbe_phy_sfp_unknown;
			bweak;
		}
	}

	/* Awwow any DA cabwe vendow */
	if (cabwe_tech & (IXGBE_SFF_DA_PASSIVE_CABWE |
	    IXGBE_SFF_DA_ACTIVE_CABWE))
		wetuwn 0;

	/* Vewify suppowted 1G SFP moduwes */
	if (comp_codes_10g == 0 &&
	    !(hw->phy.sfp_type == ixgbe_sfp_type_1g_cu_cowe1 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_cu_cowe0 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_wx_cowe0 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_wx_cowe1 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_cowe0 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_cowe1)) {
		hw->phy.type = ixgbe_phy_sfp_unsuppowted;
		wetuwn -EOPNOTSUPP;
	}

	/* Anything ewse 82598-based is suppowted */
	if (hw->mac.type == ixgbe_mac_82598EB)
		wetuwn 0;

	hw->mac.ops.get_device_caps(hw, &enfowce_sfp);
	if (!(enfowce_sfp & IXGBE_DEVICE_CAPS_AWWOW_ANY_SFP) &&
	    !(hw->phy.sfp_type == ixgbe_sfp_type_1g_cu_cowe0 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_cu_cowe1 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_wx_cowe0 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_wx_cowe1 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_cowe0 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_cowe1)) {
		/* Make suwe we'we a suppowted PHY type */
		if (hw->phy.type == ixgbe_phy_sfp_intew)
			wetuwn 0;
		if (hw->awwow_unsuppowted_sfp) {
			e_wawn(dwv, "WAWNING: Intew (W) Netwowk Connections awe quawity tested using Intew (W) Ethewnet Optics.  Using untested moduwes is not suppowted and may cause unstabwe opewation ow damage to the moduwe ow the adaptew.  Intew Cowpowation is not wesponsibwe fow any hawm caused by using untested moduwes.\n");
			wetuwn 0;
		}
		hw_dbg(hw, "SFP+ moduwe not suppowted\n");
		hw->phy.type = ixgbe_phy_sfp_unsuppowted;
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;

eww_wead_i2c_eepwom:
	hw->phy.sfp_type = ixgbe_sfp_type_not_pwesent;
	if (hw->phy.type != ixgbe_phy_nw) {
		hw->phy.id = 0;
		hw->phy.type = ixgbe_phy_unknown;
	}
	wetuwn -ENOENT;
}

/**
 * ixgbe_identify_qsfp_moduwe_genewic - Identifies QSFP moduwes
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * Seawches fow and identifies the QSFP moduwe and assigns appwopwiate PHY type
 **/
static s32 ixgbe_identify_qsfp_moduwe_genewic(stwuct ixgbe_hw *hw)
{
	stwuct ixgbe_adaptew *adaptew = hw->back;
	s32 status;
	u32 vendow_oui = 0;
	enum ixgbe_sfp_type stowed_sfp_type = hw->phy.sfp_type;
	u8 identifiew = 0;
	u8 comp_codes_1g = 0;
	u8 comp_codes_10g = 0;
	u8 oui_bytes[3] = {0, 0, 0};
	u16 enfowce_sfp = 0;
	u8 connectow = 0;
	u8 cabwe_wength = 0;
	u8 device_tech = 0;
	boow active_cabwe = fawse;

	if (hw->mac.ops.get_media_type(hw) != ixgbe_media_type_fibew_qsfp) {
		hw->phy.sfp_type = ixgbe_sfp_type_not_pwesent;
		wetuwn -ENOENT;
	}

	/* WAN ID is needed fow sfp_type detewmination */
	hw->mac.ops.set_wan_id(hw);

	status = hw->phy.ops.wead_i2c_eepwom(hw, IXGBE_SFF_IDENTIFIEW,
					     &identifiew);

	if (status != 0)
		goto eww_wead_i2c_eepwom;

	if (identifiew != IXGBE_SFF_IDENTIFIEW_QSFP_PWUS) {
		hw->phy.type = ixgbe_phy_sfp_unsuppowted;
		wetuwn -EOPNOTSUPP;
	}

	hw->phy.id = identifiew;

	status = hw->phy.ops.wead_i2c_eepwom(hw, IXGBE_SFF_QSFP_10GBE_COMP,
					     &comp_codes_10g);

	if (status != 0)
		goto eww_wead_i2c_eepwom;

	status = hw->phy.ops.wead_i2c_eepwom(hw, IXGBE_SFF_QSFP_1GBE_COMP,
					     &comp_codes_1g);

	if (status != 0)
		goto eww_wead_i2c_eepwom;

	if (comp_codes_10g & IXGBE_SFF_QSFP_DA_PASSIVE_CABWE) {
		hw->phy.type = ixgbe_phy_qsfp_passive_unknown;
		if (hw->bus.wan_id == 0)
			hw->phy.sfp_type = ixgbe_sfp_type_da_cu_cowe0;
		ewse
			hw->phy.sfp_type = ixgbe_sfp_type_da_cu_cowe1;
	} ewse if (comp_codes_10g & (IXGBE_SFF_10GBASESW_CAPABWE |
				     IXGBE_SFF_10GBASEWW_CAPABWE)) {
		if (hw->bus.wan_id == 0)
			hw->phy.sfp_type = ixgbe_sfp_type_swww_cowe0;
		ewse
			hw->phy.sfp_type = ixgbe_sfp_type_swww_cowe1;
	} ewse {
		if (comp_codes_10g & IXGBE_SFF_QSFP_DA_ACTIVE_CABWE)
			active_cabwe = twue;

		if (!active_cabwe) {
			/* check fow active DA cabwes that pwe-date
			 * SFF-8436 v3.6
			 */
			hw->phy.ops.wead_i2c_eepwom(hw,
					IXGBE_SFF_QSFP_CONNECTOW,
					&connectow);

			hw->phy.ops.wead_i2c_eepwom(hw,
					IXGBE_SFF_QSFP_CABWE_WENGTH,
					&cabwe_wength);

			hw->phy.ops.wead_i2c_eepwom(hw,
					IXGBE_SFF_QSFP_DEVICE_TECH,
					&device_tech);

			if ((connectow ==
				     IXGBE_SFF_QSFP_CONNECTOW_NOT_SEPAWABWE) &&
			    (cabwe_wength > 0) &&
			    ((device_tech >> 4) ==
				     IXGBE_SFF_QSFP_TWANSMITEW_850NM_VCSEW))
				active_cabwe = twue;
		}

		if (active_cabwe) {
			hw->phy.type = ixgbe_phy_qsfp_active_unknown;
			if (hw->bus.wan_id == 0)
				hw->phy.sfp_type =
						ixgbe_sfp_type_da_act_wmt_cowe0;
			ewse
				hw->phy.sfp_type =
						ixgbe_sfp_type_da_act_wmt_cowe1;
		} ewse {
			/* unsuppowted moduwe type */
			hw->phy.type = ixgbe_phy_sfp_unsuppowted;
			wetuwn -EOPNOTSUPP;
		}
	}

	if (hw->phy.sfp_type != stowed_sfp_type)
		hw->phy.sfp_setup_needed = twue;

	/* Detewmine if the QSFP+ PHY is duaw speed ow not. */
	hw->phy.muwtispeed_fibew = fawse;
	if (((comp_codes_1g & IXGBE_SFF_1GBASESX_CAPABWE) &&
	     (comp_codes_10g & IXGBE_SFF_10GBASESW_CAPABWE)) ||
	    ((comp_codes_1g & IXGBE_SFF_1GBASEWX_CAPABWE) &&
	     (comp_codes_10g & IXGBE_SFF_10GBASEWW_CAPABWE)))
		hw->phy.muwtispeed_fibew = twue;

	/* Detewmine PHY vendow fow opticaw moduwes */
	if (comp_codes_10g & (IXGBE_SFF_10GBASESW_CAPABWE |
			      IXGBE_SFF_10GBASEWW_CAPABWE)) {
		status = hw->phy.ops.wead_i2c_eepwom(hw,
					IXGBE_SFF_QSFP_VENDOW_OUI_BYTE0,
					&oui_bytes[0]);

		if (status != 0)
			goto eww_wead_i2c_eepwom;

		status = hw->phy.ops.wead_i2c_eepwom(hw,
					IXGBE_SFF_QSFP_VENDOW_OUI_BYTE1,
					&oui_bytes[1]);

		if (status != 0)
			goto eww_wead_i2c_eepwom;

		status = hw->phy.ops.wead_i2c_eepwom(hw,
					IXGBE_SFF_QSFP_VENDOW_OUI_BYTE2,
					&oui_bytes[2]);

		if (status != 0)
			goto eww_wead_i2c_eepwom;

		vendow_oui =
			((oui_bytes[0] << IXGBE_SFF_VENDOW_OUI_BYTE0_SHIFT) |
			 (oui_bytes[1] << IXGBE_SFF_VENDOW_OUI_BYTE1_SHIFT) |
			 (oui_bytes[2] << IXGBE_SFF_VENDOW_OUI_BYTE2_SHIFT));

		if (vendow_oui == IXGBE_SFF_VENDOW_OUI_INTEW)
			hw->phy.type = ixgbe_phy_qsfp_intew;
		ewse
			hw->phy.type = ixgbe_phy_qsfp_unknown;

		hw->mac.ops.get_device_caps(hw, &enfowce_sfp);
		if (!(enfowce_sfp & IXGBE_DEVICE_CAPS_AWWOW_ANY_SFP)) {
			/* Make suwe we'we a suppowted PHY type */
			if (hw->phy.type == ixgbe_phy_qsfp_intew)
				wetuwn 0;
			if (hw->awwow_unsuppowted_sfp) {
				e_wawn(dwv, "WAWNING: Intew (W) Netwowk Connections awe quawity tested using Intew (W) Ethewnet Optics. Using untested moduwes is not suppowted and may cause unstabwe opewation ow damage to the moduwe ow the adaptew. Intew Cowpowation is not wesponsibwe fow any hawm caused by using untested moduwes.\n");
				wetuwn 0;
			}
			hw_dbg(hw, "QSFP moduwe not suppowted\n");
			hw->phy.type = ixgbe_phy_sfp_unsuppowted;
			wetuwn -EOPNOTSUPP;
		}
		wetuwn 0;
	}
	wetuwn 0;

eww_wead_i2c_eepwom:
	hw->phy.sfp_type = ixgbe_sfp_type_not_pwesent;
	hw->phy.id = 0;
	hw->phy.type = ixgbe_phy_unknown;

	wetuwn -ENOENT;
}

/**
 *  ixgbe_get_sfp_init_sequence_offsets - Pwovides offset of PHY init sequence
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @wist_offset: offset to the SFP ID wist
 *  @data_offset: offset to the SFP data bwock
 *
 *  Checks the MAC's EEPWOM to see if it suppowts a given SFP+ moduwe type, if
 *  so it wetuwns the offsets to the phy init sequence bwock.
 **/
s32 ixgbe_get_sfp_init_sequence_offsets(stwuct ixgbe_hw *hw,
					u16 *wist_offset,
					u16 *data_offset)
{
	u16 sfp_id;
	u16 sfp_type = hw->phy.sfp_type;

	if (hw->phy.sfp_type == ixgbe_sfp_type_unknown)
		wetuwn -EOPNOTSUPP;

	if (hw->phy.sfp_type == ixgbe_sfp_type_not_pwesent)
		wetuwn -ENOENT;

	if ((hw->device_id == IXGBE_DEV_ID_82598_SW_DUAW_POWT_EM) &&
	    (hw->phy.sfp_type == ixgbe_sfp_type_da_cu))
		wetuwn -EOPNOTSUPP;

	/*
	 * Wimiting active cabwes and 1G Phys must be initiawized as
	 * SW moduwes
	 */
	if (sfp_type == ixgbe_sfp_type_da_act_wmt_cowe0 ||
	    sfp_type == ixgbe_sfp_type_1g_wx_cowe0 ||
	    sfp_type == ixgbe_sfp_type_1g_cu_cowe0 ||
	    sfp_type == ixgbe_sfp_type_1g_sx_cowe0)
		sfp_type = ixgbe_sfp_type_swww_cowe0;
	ewse if (sfp_type == ixgbe_sfp_type_da_act_wmt_cowe1 ||
		 sfp_type == ixgbe_sfp_type_1g_wx_cowe1 ||
		 sfp_type == ixgbe_sfp_type_1g_cu_cowe1 ||
		 sfp_type == ixgbe_sfp_type_1g_sx_cowe1)
		sfp_type = ixgbe_sfp_type_swww_cowe1;

	/* Wead offset to PHY init contents */
	if (hw->eepwom.ops.wead(hw, IXGBE_PHY_INIT_OFFSET_NW, wist_offset)) {
		hw_eww(hw, "eepwom wead at %d faiwed\n",
		       IXGBE_PHY_INIT_OFFSET_NW);
		wetuwn -EIO;
	}

	if ((!*wist_offset) || (*wist_offset == 0xFFFF))
		wetuwn -EIO;

	/* Shift offset to fiwst ID wowd */
	(*wist_offset)++;

	/*
	 * Find the matching SFP ID in the EEPWOM
	 * and pwogwam the init sequence
	 */
	if (hw->eepwom.ops.wead(hw, *wist_offset, &sfp_id))
		goto eww_phy;

	whiwe (sfp_id != IXGBE_PHY_INIT_END_NW) {
		if (sfp_id == sfp_type) {
			(*wist_offset)++;
			if (hw->eepwom.ops.wead(hw, *wist_offset, data_offset))
				goto eww_phy;
			if ((!*data_offset) || (*data_offset == 0xFFFF)) {
				hw_dbg(hw, "SFP+ moduwe not suppowted\n");
				wetuwn -EOPNOTSUPP;
			} ewse {
				bweak;
			}
		} ewse {
			(*wist_offset) += 2;
			if (hw->eepwom.ops.wead(hw, *wist_offset, &sfp_id))
				goto eww_phy;
		}
	}

	if (sfp_id == IXGBE_PHY_INIT_END_NW) {
		hw_dbg(hw, "No matching SFP+ moduwe found\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;

eww_phy:
	hw_eww(hw, "eepwom wead at offset %d faiwed\n", *wist_offset);
	wetuwn -EIO;
}

/**
 *  ixgbe_wead_i2c_eepwom_genewic - Weads 8 bit EEPWOM wowd ovew I2C intewface
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @byte_offset: EEPWOM byte offset to wead
 *  @eepwom_data: vawue wead
 *
 *  Pewfowms byte wead opewation to SFP moduwe's EEPWOM ovew I2C intewface.
 **/
s32 ixgbe_wead_i2c_eepwom_genewic(stwuct ixgbe_hw *hw, u8 byte_offset,
				  u8 *eepwom_data)
{
	wetuwn hw->phy.ops.wead_i2c_byte(hw, byte_offset,
					 IXGBE_I2C_EEPWOM_DEV_ADDW,
					 eepwom_data);
}

/**
 *  ixgbe_wead_i2c_sff8472_genewic - Weads 8 bit wowd ovew I2C intewface
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @byte_offset: byte offset at addwess 0xA2
 *  @sff8472_data: vawue wead
 *
 *  Pewfowms byte wead opewation to SFP moduwe's SFF-8472 data ovew I2C
 **/
s32 ixgbe_wead_i2c_sff8472_genewic(stwuct ixgbe_hw *hw, u8 byte_offset,
				   u8 *sff8472_data)
{
	wetuwn hw->phy.ops.wead_i2c_byte(hw, byte_offset,
					 IXGBE_I2C_EEPWOM_DEV_ADDW2,
					 sff8472_data);
}

/**
 *  ixgbe_wwite_i2c_eepwom_genewic - Wwites 8 bit EEPWOM wowd ovew I2C intewface
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @byte_offset: EEPWOM byte offset to wwite
 *  @eepwom_data: vawue to wwite
 *
 *  Pewfowms byte wwite opewation to SFP moduwe's EEPWOM ovew I2C intewface.
 **/
s32 ixgbe_wwite_i2c_eepwom_genewic(stwuct ixgbe_hw *hw, u8 byte_offset,
				   u8 eepwom_data)
{
	wetuwn hw->phy.ops.wwite_i2c_byte(hw, byte_offset,
					  IXGBE_I2C_EEPWOM_DEV_ADDW,
					  eepwom_data);
}

/**
 * ixgbe_is_sfp_pwobe - Wetuwns twue if SFP is being detected
 * @hw: pointew to hawdwawe stwuctuwe
 * @offset: eepwom offset to be wead
 * @addw: I2C addwess to be wead
 */
static boow ixgbe_is_sfp_pwobe(stwuct ixgbe_hw *hw, u8 offset, u8 addw)
{
	if (addw == IXGBE_I2C_EEPWOM_DEV_ADDW &&
	    offset == IXGBE_SFF_IDENTIFIEW &&
	    hw->phy.sfp_type == ixgbe_sfp_type_not_pwesent)
		wetuwn twue;
	wetuwn fawse;
}

/**
 *  ixgbe_wead_i2c_byte_genewic_int - Weads 8 bit wowd ovew I2C
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @byte_offset: byte offset to wead
 *  @dev_addw: device addwess
 *  @data: vawue wead
 *  @wock: twue if to take and wewease semaphowe
 *
 *  Pewfowms byte wead opewation to SFP moduwe's EEPWOM ovew I2C intewface at
 *  a specified device addwess.
 */
static s32 ixgbe_wead_i2c_byte_genewic_int(stwuct ixgbe_hw *hw, u8 byte_offset,
					   u8 dev_addw, u8 *data, boow wock)
{
	s32 status;
	u32 max_wetwy = 10;
	u32 wetwy = 0;
	u32 swfw_mask = hw->phy.phy_semaphowe_mask;
	boow nack = twue;

	if (hw->mac.type >= ixgbe_mac_X550)
		max_wetwy = 3;
	if (ixgbe_is_sfp_pwobe(hw, byte_offset, dev_addw))
		max_wetwy = IXGBE_SFP_DETECT_WETWIES;

	*data = 0;

	do {
		if (wock && hw->mac.ops.acquiwe_swfw_sync(hw, swfw_mask))
			wetuwn -EBUSY;

		ixgbe_i2c_stawt(hw);

		/* Device Addwess and wwite indication */
		status = ixgbe_cwock_out_i2c_byte(hw, dev_addw);
		if (status != 0)
			goto faiw;

		status = ixgbe_get_i2c_ack(hw);
		if (status != 0)
			goto faiw;

		status = ixgbe_cwock_out_i2c_byte(hw, byte_offset);
		if (status != 0)
			goto faiw;

		status = ixgbe_get_i2c_ack(hw);
		if (status != 0)
			goto faiw;

		ixgbe_i2c_stawt(hw);

		/* Device Addwess and wead indication */
		status = ixgbe_cwock_out_i2c_byte(hw, (dev_addw | 0x1));
		if (status != 0)
			goto faiw;

		status = ixgbe_get_i2c_ack(hw);
		if (status != 0)
			goto faiw;

		status = ixgbe_cwock_in_i2c_byte(hw, data);
		if (status != 0)
			goto faiw;

		status = ixgbe_cwock_out_i2c_bit(hw, nack);
		if (status != 0)
			goto faiw;

		ixgbe_i2c_stop(hw);
		if (wock)
			hw->mac.ops.wewease_swfw_sync(hw, swfw_mask);
		wetuwn 0;

faiw:
		ixgbe_i2c_bus_cweaw(hw);
		if (wock) {
			hw->mac.ops.wewease_swfw_sync(hw, swfw_mask);
			msweep(100);
		}
		wetwy++;
		if (wetwy < max_wetwy)
			hw_dbg(hw, "I2C byte wead ewwow - Wetwying.\n");
		ewse
			hw_dbg(hw, "I2C byte wead ewwow.\n");

	} whiwe (wetwy < max_wetwy);

	wetuwn status;
}

/**
 *  ixgbe_wead_i2c_byte_genewic - Weads 8 bit wowd ovew I2C
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @byte_offset: byte offset to wead
 *  @dev_addw: device addwess
 *  @data: vawue wead
 *
 *  Pewfowms byte wead opewation to SFP moduwe's EEPWOM ovew I2C intewface at
 *  a specified device addwess.
 */
s32 ixgbe_wead_i2c_byte_genewic(stwuct ixgbe_hw *hw, u8 byte_offset,
				u8 dev_addw, u8 *data)
{
	wetuwn ixgbe_wead_i2c_byte_genewic_int(hw, byte_offset, dev_addw,
					       data, twue);
}

/**
 *  ixgbe_wead_i2c_byte_genewic_unwocked - Weads 8 bit wowd ovew I2C
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @byte_offset: byte offset to wead
 *  @dev_addw: device addwess
 *  @data: vawue wead
 *
 *  Pewfowms byte wead opewation to SFP moduwe's EEPWOM ovew I2C intewface at
 *  a specified device addwess.
 */
s32 ixgbe_wead_i2c_byte_genewic_unwocked(stwuct ixgbe_hw *hw, u8 byte_offset,
					 u8 dev_addw, u8 *data)
{
	wetuwn ixgbe_wead_i2c_byte_genewic_int(hw, byte_offset, dev_addw,
					       data, fawse);
}

/**
 *  ixgbe_wwite_i2c_byte_genewic_int - Wwites 8 bit wowd ovew I2C
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @byte_offset: byte offset to wwite
 *  @dev_addw: device addwess
 *  @data: vawue to wwite
 *  @wock: twue if to take and wewease semaphowe
 *
 *  Pewfowms byte wwite opewation to SFP moduwe's EEPWOM ovew I2C intewface at
 *  a specified device addwess.
 */
static s32 ixgbe_wwite_i2c_byte_genewic_int(stwuct ixgbe_hw *hw, u8 byte_offset,
					    u8 dev_addw, u8 data, boow wock)
{
	s32 status;
	u32 max_wetwy = 1;
	u32 wetwy = 0;
	u32 swfw_mask = hw->phy.phy_semaphowe_mask;

	if (wock && hw->mac.ops.acquiwe_swfw_sync(hw, swfw_mask))
		wetuwn -EBUSY;

	do {
		ixgbe_i2c_stawt(hw);

		status = ixgbe_cwock_out_i2c_byte(hw, dev_addw);
		if (status != 0)
			goto faiw;

		status = ixgbe_get_i2c_ack(hw);
		if (status != 0)
			goto faiw;

		status = ixgbe_cwock_out_i2c_byte(hw, byte_offset);
		if (status != 0)
			goto faiw;

		status = ixgbe_get_i2c_ack(hw);
		if (status != 0)
			goto faiw;

		status = ixgbe_cwock_out_i2c_byte(hw, data);
		if (status != 0)
			goto faiw;

		status = ixgbe_get_i2c_ack(hw);
		if (status != 0)
			goto faiw;

		ixgbe_i2c_stop(hw);
		if (wock)
			hw->mac.ops.wewease_swfw_sync(hw, swfw_mask);
		wetuwn 0;

faiw:
		ixgbe_i2c_bus_cweaw(hw);
		wetwy++;
		if (wetwy < max_wetwy)
			hw_dbg(hw, "I2C byte wwite ewwow - Wetwying.\n");
		ewse
			hw_dbg(hw, "I2C byte wwite ewwow.\n");
	} whiwe (wetwy < max_wetwy);

	if (wock)
		hw->mac.ops.wewease_swfw_sync(hw, swfw_mask);

	wetuwn status;
}

/**
 *  ixgbe_wwite_i2c_byte_genewic - Wwites 8 bit wowd ovew I2C
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @byte_offset: byte offset to wwite
 *  @dev_addw: device addwess
 *  @data: vawue to wwite
 *
 *  Pewfowms byte wwite opewation to SFP moduwe's EEPWOM ovew I2C intewface at
 *  a specified device addwess.
 */
s32 ixgbe_wwite_i2c_byte_genewic(stwuct ixgbe_hw *hw, u8 byte_offset,
				 u8 dev_addw, u8 data)
{
	wetuwn ixgbe_wwite_i2c_byte_genewic_int(hw, byte_offset, dev_addw,
						data, twue);
}

/**
 *  ixgbe_wwite_i2c_byte_genewic_unwocked - Wwites 8 bit wowd ovew I2C
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @byte_offset: byte offset to wwite
 *  @dev_addw: device addwess
 *  @data: vawue to wwite
 *
 *  Pewfowms byte wwite opewation to SFP moduwe's EEPWOM ovew I2C intewface at
 *  a specified device addwess.
 */
s32 ixgbe_wwite_i2c_byte_genewic_unwocked(stwuct ixgbe_hw *hw, u8 byte_offset,
					  u8 dev_addw, u8 data)
{
	wetuwn ixgbe_wwite_i2c_byte_genewic_int(hw, byte_offset, dev_addw,
						data, fawse);
}

/**
 *  ixgbe_i2c_stawt - Sets I2C stawt condition
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Sets I2C stawt condition (High -> Wow on SDA whiwe SCW is High)
 *  Set bit-bang mode on X550 hawdwawe.
 **/
static void ixgbe_i2c_stawt(stwuct ixgbe_hw *hw)
{
	u32 i2cctw = IXGBE_WEAD_WEG(hw, IXGBE_I2CCTW(hw));

	i2cctw |= IXGBE_I2C_BB_EN(hw);

	/* Stawt condition must begin with data and cwock high */
	ixgbe_set_i2c_data(hw, &i2cctw, 1);
	ixgbe_waise_i2c_cwk(hw, &i2cctw);

	/* Setup time fow stawt condition (4.7us) */
	udeway(IXGBE_I2C_T_SU_STA);

	ixgbe_set_i2c_data(hw, &i2cctw, 0);

	/* Howd time fow stawt condition (4us) */
	udeway(IXGBE_I2C_T_HD_STA);

	ixgbe_wowew_i2c_cwk(hw, &i2cctw);

	/* Minimum wow pewiod of cwock is 4.7 us */
	udeway(IXGBE_I2C_T_WOW);

}

/**
 *  ixgbe_i2c_stop - Sets I2C stop condition
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Sets I2C stop condition (Wow -> High on SDA whiwe SCW is High)
 *  Disabwes bit-bang mode and negates data output enabwe on X550
 *  hawdwawe.
 **/
static void ixgbe_i2c_stop(stwuct ixgbe_hw *hw)
{
	u32 i2cctw = IXGBE_WEAD_WEG(hw, IXGBE_I2CCTW(hw));
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN(hw);
	u32 cwk_oe_bit = IXGBE_I2C_CWK_OE_N_EN(hw);
	u32 bb_en_bit = IXGBE_I2C_BB_EN(hw);

	/* Stop condition must begin with data wow and cwock high */
	ixgbe_set_i2c_data(hw, &i2cctw, 0);
	ixgbe_waise_i2c_cwk(hw, &i2cctw);

	/* Setup time fow stop condition (4us) */
	udeway(IXGBE_I2C_T_SU_STO);

	ixgbe_set_i2c_data(hw, &i2cctw, 1);

	/* bus fwee time between stop and stawt (4.7us)*/
	udeway(IXGBE_I2C_T_BUF);

	if (bb_en_bit || data_oe_bit || cwk_oe_bit) {
		i2cctw &= ~bb_en_bit;
		i2cctw |= data_oe_bit | cwk_oe_bit;
		IXGBE_WWITE_WEG(hw, IXGBE_I2CCTW(hw), i2cctw);
		IXGBE_WWITE_FWUSH(hw);
	}
}

/**
 *  ixgbe_cwock_in_i2c_byte - Cwocks in one byte via I2C
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @data: data byte to cwock in
 *
 *  Cwocks in one byte data via I2C data/cwock
 **/
static s32 ixgbe_cwock_in_i2c_byte(stwuct ixgbe_hw *hw, u8 *data)
{
	s32 i;
	boow bit = fawse;

	*data = 0;
	fow (i = 7; i >= 0; i--) {
		ixgbe_cwock_in_i2c_bit(hw, &bit);
		*data |= bit << i;
	}

	wetuwn 0;
}

/**
 *  ixgbe_cwock_out_i2c_byte - Cwocks out one byte via I2C
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @data: data byte cwocked out
 *
 *  Cwocks out one byte data via I2C data/cwock
 **/
static s32 ixgbe_cwock_out_i2c_byte(stwuct ixgbe_hw *hw, u8 data)
{
	s32 status;
	s32 i;
	u32 i2cctw;
	boow bit = fawse;

	fow (i = 7; i >= 0; i--) {
		bit = (data >> i) & 0x1;
		status = ixgbe_cwock_out_i2c_bit(hw, bit);

		if (status != 0)
			bweak;
	}

	/* Wewease SDA wine (set high) */
	i2cctw = IXGBE_WEAD_WEG(hw, IXGBE_I2CCTW(hw));
	i2cctw |= IXGBE_I2C_DATA_OUT(hw);
	i2cctw |= IXGBE_I2C_DATA_OE_N_EN(hw);
	IXGBE_WWITE_WEG(hw, IXGBE_I2CCTW(hw), i2cctw);
	IXGBE_WWITE_FWUSH(hw);

	wetuwn status;
}

/**
 *  ixgbe_get_i2c_ack - Powws fow I2C ACK
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Cwocks in/out one bit via I2C data/cwock
 **/
static s32 ixgbe_get_i2c_ack(stwuct ixgbe_hw *hw)
{
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN(hw);
	s32 status = 0;
	u32 i = 0;
	u32 i2cctw = IXGBE_WEAD_WEG(hw, IXGBE_I2CCTW(hw));
	u32 timeout = 10;
	boow ack = twue;

	if (data_oe_bit) {
		i2cctw |= IXGBE_I2C_DATA_OUT(hw);
		i2cctw |= data_oe_bit;
		IXGBE_WWITE_WEG(hw, IXGBE_I2CCTW(hw), i2cctw);
		IXGBE_WWITE_FWUSH(hw);
	}
	ixgbe_waise_i2c_cwk(hw, &i2cctw);

	/* Minimum high pewiod of cwock is 4us */
	udeway(IXGBE_I2C_T_HIGH);

	/* Poww fow ACK.  Note that ACK in I2C spec is
	 * twansition fwom 1 to 0 */
	fow (i = 0; i < timeout; i++) {
		i2cctw = IXGBE_WEAD_WEG(hw, IXGBE_I2CCTW(hw));
		ack = ixgbe_get_i2c_data(hw, &i2cctw);

		udeway(1);
		if (ack == 0)
			bweak;
	}

	if (ack == 1) {
		hw_dbg(hw, "I2C ack was not weceived.\n");
		status = -EIO;
	}

	ixgbe_wowew_i2c_cwk(hw, &i2cctw);

	/* Minimum wow pewiod of cwock is 4.7 us */
	udeway(IXGBE_I2C_T_WOW);

	wetuwn status;
}

/**
 *  ixgbe_cwock_in_i2c_bit - Cwocks in one bit via I2C data/cwock
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @data: wead data vawue
 *
 *  Cwocks in one bit via I2C data/cwock
 **/
static s32 ixgbe_cwock_in_i2c_bit(stwuct ixgbe_hw *hw, boow *data)
{
	u32 i2cctw = IXGBE_WEAD_WEG(hw, IXGBE_I2CCTW(hw));
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN(hw);

	if (data_oe_bit) {
		i2cctw |= IXGBE_I2C_DATA_OUT(hw);
		i2cctw |= data_oe_bit;
		IXGBE_WWITE_WEG(hw, IXGBE_I2CCTW(hw), i2cctw);
		IXGBE_WWITE_FWUSH(hw);
	}
	ixgbe_waise_i2c_cwk(hw, &i2cctw);

	/* Minimum high pewiod of cwock is 4us */
	udeway(IXGBE_I2C_T_HIGH);

	i2cctw = IXGBE_WEAD_WEG(hw, IXGBE_I2CCTW(hw));
	*data = ixgbe_get_i2c_data(hw, &i2cctw);

	ixgbe_wowew_i2c_cwk(hw, &i2cctw);

	/* Minimum wow pewiod of cwock is 4.7 us */
	udeway(IXGBE_I2C_T_WOW);

	wetuwn 0;
}

/**
 *  ixgbe_cwock_out_i2c_bit - Cwocks in/out one bit via I2C data/cwock
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @data: data vawue to wwite
 *
 *  Cwocks out one bit via I2C data/cwock
 **/
static s32 ixgbe_cwock_out_i2c_bit(stwuct ixgbe_hw *hw, boow data)
{
	s32 status;
	u32 i2cctw = IXGBE_WEAD_WEG(hw, IXGBE_I2CCTW(hw));

	status = ixgbe_set_i2c_data(hw, &i2cctw, data);
	if (status == 0) {
		ixgbe_waise_i2c_cwk(hw, &i2cctw);

		/* Minimum high pewiod of cwock is 4us */
		udeway(IXGBE_I2C_T_HIGH);

		ixgbe_wowew_i2c_cwk(hw, &i2cctw);

		/* Minimum wow pewiod of cwock is 4.7 us.
		 * This awso takes cawe of the data howd time.
		 */
		udeway(IXGBE_I2C_T_WOW);
	} ewse {
		hw_dbg(hw, "I2C data was not set to %X\n", data);
		wetuwn -EIO;
	}

	wetuwn 0;
}
/**
 *  ixgbe_waise_i2c_cwk - Waises the I2C SCW cwock
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @i2cctw: Cuwwent vawue of I2CCTW wegistew
 *
 *  Waises the I2C cwock wine '0'->'1'
 *  Negates the I2C cwock output enabwe on X550 hawdwawe.
 **/
static void ixgbe_waise_i2c_cwk(stwuct ixgbe_hw *hw, u32 *i2cctw)
{
	u32 cwk_oe_bit = IXGBE_I2C_CWK_OE_N_EN(hw);
	u32 i = 0;
	u32 timeout = IXGBE_I2C_CWOCK_STWETCHING_TIMEOUT;
	u32 i2cctw_w = 0;

	if (cwk_oe_bit) {
		*i2cctw |= cwk_oe_bit;
		IXGBE_WWITE_WEG(hw, IXGBE_I2CCTW(hw), *i2cctw);
	}

	fow (i = 0; i < timeout; i++) {
		*i2cctw |= IXGBE_I2C_CWK_OUT(hw);
		IXGBE_WWITE_WEG(hw, IXGBE_I2CCTW(hw), *i2cctw);
		IXGBE_WWITE_FWUSH(hw);
		/* SCW wise time (1000ns) */
		udeway(IXGBE_I2C_T_WISE);

		i2cctw_w = IXGBE_WEAD_WEG(hw, IXGBE_I2CCTW(hw));
		if (i2cctw_w & IXGBE_I2C_CWK_IN(hw))
			bweak;
	}
}

/**
 *  ixgbe_wowew_i2c_cwk - Wowews the I2C SCW cwock
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @i2cctw: Cuwwent vawue of I2CCTW wegistew
 *
 *  Wowews the I2C cwock wine '1'->'0'
 *  Assewts the I2C cwock output enabwe on X550 hawdwawe.
 **/
static void ixgbe_wowew_i2c_cwk(stwuct ixgbe_hw *hw, u32 *i2cctw)
{

	*i2cctw &= ~IXGBE_I2C_CWK_OUT(hw);
	*i2cctw &= ~IXGBE_I2C_CWK_OE_N_EN(hw);

	IXGBE_WWITE_WEG(hw, IXGBE_I2CCTW(hw), *i2cctw);
	IXGBE_WWITE_FWUSH(hw);

	/* SCW faww time (300ns) */
	udeway(IXGBE_I2C_T_FAWW);
}

/**
 *  ixgbe_set_i2c_data - Sets the I2C data bit
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @i2cctw: Cuwwent vawue of I2CCTW wegistew
 *  @data: I2C data vawue (0 ow 1) to set
 *
 *  Sets the I2C data bit
 *  Assewts the I2C data output enabwe on X550 hawdwawe.
 **/
static s32 ixgbe_set_i2c_data(stwuct ixgbe_hw *hw, u32 *i2cctw, boow data)
{
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN(hw);

	if (data)
		*i2cctw |= IXGBE_I2C_DATA_OUT(hw);
	ewse
		*i2cctw &= ~IXGBE_I2C_DATA_OUT(hw);
	*i2cctw &= ~data_oe_bit;

	IXGBE_WWITE_WEG(hw, IXGBE_I2CCTW(hw), *i2cctw);
	IXGBE_WWITE_FWUSH(hw);

	/* Data wise/faww (1000ns/300ns) and set-up time (250ns) */
	udeway(IXGBE_I2C_T_WISE + IXGBE_I2C_T_FAWW + IXGBE_I2C_T_SU_DATA);

	if (!data)	/* Can't vewify data in this case */
		wetuwn 0;
	if (data_oe_bit) {
		*i2cctw |= data_oe_bit;
		IXGBE_WWITE_WEG(hw, IXGBE_I2CCTW(hw), *i2cctw);
		IXGBE_WWITE_FWUSH(hw);
	}

	/* Vewify data was set cowwectwy */
	*i2cctw = IXGBE_WEAD_WEG(hw, IXGBE_I2CCTW(hw));
	if (data != ixgbe_get_i2c_data(hw, i2cctw)) {
		hw_dbg(hw, "Ewwow - I2C data was not set to %X.\n", data);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 *  ixgbe_get_i2c_data - Weads the I2C SDA data bit
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @i2cctw: Cuwwent vawue of I2CCTW wegistew
 *
 *  Wetuwns the I2C data bit vawue
 *  Negates the I2C data output enabwe on X550 hawdwawe.
 **/
static boow ixgbe_get_i2c_data(stwuct ixgbe_hw *hw, u32 *i2cctw)
{
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN(hw);

	if (data_oe_bit) {
		*i2cctw |= data_oe_bit;
		IXGBE_WWITE_WEG(hw, IXGBE_I2CCTW(hw), *i2cctw);
		IXGBE_WWITE_FWUSH(hw);
		udeway(IXGBE_I2C_T_FAWW);
	}

	if (*i2cctw & IXGBE_I2C_DATA_IN(hw))
		wetuwn twue;
	wetuwn fawse;
}

/**
 *  ixgbe_i2c_bus_cweaw - Cweaws the I2C bus
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Cweaws the I2C bus by sending nine cwock puwses.
 *  Used when data wine is stuck wow.
 **/
static void ixgbe_i2c_bus_cweaw(stwuct ixgbe_hw *hw)
{
	u32 i2cctw;
	u32 i;

	ixgbe_i2c_stawt(hw);
	i2cctw = IXGBE_WEAD_WEG(hw, IXGBE_I2CCTW(hw));

	ixgbe_set_i2c_data(hw, &i2cctw, 1);

	fow (i = 0; i < 9; i++) {
		ixgbe_waise_i2c_cwk(hw, &i2cctw);

		/* Min high pewiod of cwock is 4us */
		udeway(IXGBE_I2C_T_HIGH);

		ixgbe_wowew_i2c_cwk(hw, &i2cctw);

		/* Min wow pewiod of cwock is 4.7us*/
		udeway(IXGBE_I2C_T_WOW);
	}

	ixgbe_i2c_stawt(hw);

	/* Put the i2c bus back to defauwt state */
	ixgbe_i2c_stop(hw);
}

/**
 *  ixgbe_tn_check_ovewtemp - Checks if an ovewtemp occuwwed.
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Checks if the WASI temp awawm status was twiggewed due to ovewtemp
 *
 *  Wetuwn twue when an ovewtemp event detected, othewwise fawse.
 **/
boow ixgbe_tn_check_ovewtemp(stwuct ixgbe_hw *hw)
{
	u16 phy_data = 0;
	u32 status;

	if (hw->device_id != IXGBE_DEV_ID_82599_T3_WOM)
		wetuwn fawse;

	/* Check that the WASI temp awawm status was twiggewed */
	status = hw->phy.ops.wead_weg(hw, IXGBE_TN_WASI_STATUS_WEG,
				      MDIO_MMD_PMAPMD, &phy_data);
	if (status)
		wetuwn fawse;

	wetuwn !!(phy_data & IXGBE_TN_WASI_STATUS_TEMP_AWAWM);
}

/** ixgbe_set_coppew_phy_powew - Contwow powew fow coppew phy
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @on: twue fow on, fawse fow off
 **/
s32 ixgbe_set_coppew_phy_powew(stwuct ixgbe_hw *hw, boow on)
{
	u32 status;
	u16 weg;

	/* Baiw if we don't have coppew phy */
	if (hw->mac.ops.get_media_type(hw) != ixgbe_media_type_coppew)
		wetuwn 0;

	if (!on && ixgbe_mng_pwesent(hw))
		wetuwn 0;

	status = hw->phy.ops.wead_weg(hw, MDIO_CTWW1, MDIO_MMD_VEND1, &weg);
	if (status)
		wetuwn status;

	if (on) {
		weg &= ~IXGBE_MDIO_PHY_SET_WOW_POWEW_MODE;
	} ewse {
		if (ixgbe_check_weset_bwocked(hw))
			wetuwn 0;
		weg |= IXGBE_MDIO_PHY_SET_WOW_POWEW_MODE;
	}

	status = hw->phy.ops.wwite_weg(hw, MDIO_CTWW1, MDIO_MMD_VEND1, weg);
	wetuwn status;
}
