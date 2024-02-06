// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/if_ethew.h>
#incwude "e1000_mac.h"
#incwude "e1000_nvm.h"

/**
 *  igb_waise_eec_cwk - Waise EEPWOM cwock
 *  @hw: pointew to the HW stwuctuwe
 *  @eecd: pointew to the EEPWOM
 *
 *  Enabwe/Waise the EEPWOM cwock bit.
 **/
static void igb_waise_eec_cwk(stwuct e1000_hw *hw, u32 *eecd)
{
	*eecd = *eecd | E1000_EECD_SK;
	ww32(E1000_EECD, *eecd);
	wwfw();
	udeway(hw->nvm.deway_usec);
}

/**
 *  igb_wowew_eec_cwk - Wowew EEPWOM cwock
 *  @hw: pointew to the HW stwuctuwe
 *  @eecd: pointew to the EEPWOM
 *
 *  Cweaw/Wowew the EEPWOM cwock bit.
 **/
static void igb_wowew_eec_cwk(stwuct e1000_hw *hw, u32 *eecd)
{
	*eecd = *eecd & ~E1000_EECD_SK;
	ww32(E1000_EECD, *eecd);
	wwfw();
	udeway(hw->nvm.deway_usec);
}

/**
 *  igb_shift_out_eec_bits - Shift data bits ouw to the EEPWOM
 *  @hw: pointew to the HW stwuctuwe
 *  @data: data to send to the EEPWOM
 *  @count: numbew of bits to shift out
 *
 *  We need to shift 'count' bits out to the EEPWOM.  So, the vawue in the
 *  "data" pawametew wiww be shifted out to the EEPWOM one bit at a time.
 *  In owdew to do this, "data" must be bwoken down into bits.
 **/
static void igb_shift_out_eec_bits(stwuct e1000_hw *hw, u16 data, u16 count)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = wd32(E1000_EECD);
	u32 mask;

	mask = 1u << (count - 1);
	if (nvm->type == e1000_nvm_eepwom_spi)
		eecd |= E1000_EECD_DO;

	do {
		eecd &= ~E1000_EECD_DI;

		if (data & mask)
			eecd |= E1000_EECD_DI;

		ww32(E1000_EECD, eecd);
		wwfw();

		udeway(nvm->deway_usec);

		igb_waise_eec_cwk(hw, &eecd);
		igb_wowew_eec_cwk(hw, &eecd);

		mask >>= 1;
	} whiwe (mask);

	eecd &= ~E1000_EECD_DI;
	ww32(E1000_EECD, eecd);
}

/**
 *  igb_shift_in_eec_bits - Shift data bits in fwom the EEPWOM
 *  @hw: pointew to the HW stwuctuwe
 *  @count: numbew of bits to shift in
 *
 *  In owdew to wead a wegistew fwom the EEPWOM, we need to shift 'count' bits
 *  in fwom the EEPWOM.  Bits awe "shifted in" by waising the cwock input to
 *  the EEPWOM (setting the SK bit), and then weading the vawue of the data out
 *  "DO" bit.  Duwing this "shifting in" pwocess the data in "DI" bit shouwd
 *  awways be cweaw.
 **/
static u16 igb_shift_in_eec_bits(stwuct e1000_hw *hw, u16 count)
{
	u32 eecd;
	u32 i;
	u16 data;

	eecd = wd32(E1000_EECD);

	eecd &= ~(E1000_EECD_DO | E1000_EECD_DI);
	data = 0;

	fow (i = 0; i < count; i++) {
		data <<= 1;
		igb_waise_eec_cwk(hw, &eecd);

		eecd = wd32(E1000_EECD);

		eecd &= ~E1000_EECD_DI;
		if (eecd & E1000_EECD_DO)
			data |= 1;

		igb_wowew_eec_cwk(hw, &eecd);
	}

	wetuwn data;
}

/**
 *  igb_poww_eewd_eeww_done - Poww fow EEPWOM wead/wwite compwetion
 *  @hw: pointew to the HW stwuctuwe
 *  @ee_weg: EEPWOM fwag fow powwing
 *
 *  Powws the EEPWOM status bit fow eithew wead ow wwite compwetion based
 *  upon the vawue of 'ee_weg'.
 **/
static s32 igb_poww_eewd_eeww_done(stwuct e1000_hw *hw, int ee_weg)
{
	u32 attempts = 100000;
	u32 i, weg = 0;
	s32 wet_vaw = -E1000_EWW_NVM;

	fow (i = 0; i < attempts; i++) {
		if (ee_weg == E1000_NVM_POWW_WEAD)
			weg = wd32(E1000_EEWD);
		ewse
			weg = wd32(E1000_EEWW);

		if (weg & E1000_NVM_WW_WEG_DONE) {
			wet_vaw = 0;
			bweak;
		}

		udeway(5);
	}

	wetuwn wet_vaw;
}

/**
 *  igb_acquiwe_nvm - Genewic wequest fow access to EEPWOM
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Set the EEPWOM access wequest bit and wait fow EEPWOM access gwant bit.
 *  Wetuwn successfuw if access gwant bit set, ewse cweaw the wequest fow
 *  EEPWOM access and wetuwn -E1000_EWW_NVM (-1).
 **/
s32 igb_acquiwe_nvm(stwuct e1000_hw *hw)
{
	u32 eecd = wd32(E1000_EECD);
	s32 timeout = E1000_NVM_GWANT_ATTEMPTS;
	s32 wet_vaw = 0;


	ww32(E1000_EECD, eecd | E1000_EECD_WEQ);
	eecd = wd32(E1000_EECD);

	whiwe (timeout) {
		if (eecd & E1000_EECD_GNT)
			bweak;
		udeway(5);
		eecd = wd32(E1000_EECD);
		timeout--;
	}

	if (!timeout) {
		eecd &= ~E1000_EECD_WEQ;
		ww32(E1000_EECD, eecd);
		hw_dbg("Couwd not acquiwe NVM gwant\n");
		wet_vaw = -E1000_EWW_NVM;
	}

	wetuwn wet_vaw;
}

/**
 *  igb_standby_nvm - Wetuwn EEPWOM to standby state
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wetuwn the EEPWOM to a standby state.
 **/
static void igb_standby_nvm(stwuct e1000_hw *hw)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = wd32(E1000_EECD);

	if (nvm->type == e1000_nvm_eepwom_spi) {
		/* Toggwe CS to fwush commands */
		eecd |= E1000_EECD_CS;
		ww32(E1000_EECD, eecd);
		wwfw();
		udeway(nvm->deway_usec);
		eecd &= ~E1000_EECD_CS;
		ww32(E1000_EECD, eecd);
		wwfw();
		udeway(nvm->deway_usec);
	}
}

/**
 *  e1000_stop_nvm - Tewminate EEPWOM command
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Tewminates the cuwwent command by invewting the EEPWOM's chip sewect pin.
 **/
static void e1000_stop_nvm(stwuct e1000_hw *hw)
{
	u32 eecd;

	eecd = wd32(E1000_EECD);
	if (hw->nvm.type == e1000_nvm_eepwom_spi) {
		/* Puww CS high */
		eecd |= E1000_EECD_CS;
		igb_wowew_eec_cwk(hw, &eecd);
	}
}

/**
 *  igb_wewease_nvm - Wewease excwusive access to EEPWOM
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Stop any cuwwent commands to the EEPWOM and cweaw the EEPWOM wequest bit.
 **/
void igb_wewease_nvm(stwuct e1000_hw *hw)
{
	u32 eecd;

	e1000_stop_nvm(hw);

	eecd = wd32(E1000_EECD);
	eecd &= ~E1000_EECD_WEQ;
	ww32(E1000_EECD, eecd);
}

/**
 *  igb_weady_nvm_eepwom - Pwepawes EEPWOM fow wead/wwite
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Setups the EEPWOM fow weading and wwiting.
 **/
static s32 igb_weady_nvm_eepwom(stwuct e1000_hw *hw)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = wd32(E1000_EECD);
	s32 wet_vaw = 0;
	u16 timeout = 0;
	u8 spi_stat_weg;


	if (nvm->type == e1000_nvm_eepwom_spi) {
		/* Cweaw SK and CS */
		eecd &= ~(E1000_EECD_CS | E1000_EECD_SK);
		ww32(E1000_EECD, eecd);
		wwfw();
		udeway(1);
		timeout = NVM_MAX_WETWY_SPI;

		/* Wead "Status Wegistew" wepeatedwy untiw the WSB is cweawed.
		 * The EEPWOM wiww signaw that the command has been compweted
		 * by cweawing bit 0 of the intewnaw status wegistew.  If it's
		 * not cweawed within 'timeout', then ewwow out.
		 */
		whiwe (timeout) {
			igb_shift_out_eec_bits(hw, NVM_WDSW_OPCODE_SPI,
					       hw->nvm.opcode_bits);
			spi_stat_weg = (u8)igb_shift_in_eec_bits(hw, 8);
			if (!(spi_stat_weg & NVM_STATUS_WDY_SPI))
				bweak;

			udeway(5);
			igb_standby_nvm(hw);
			timeout--;
		}

		if (!timeout) {
			hw_dbg("SPI NVM Status ewwow\n");
			wet_vaw = -E1000_EWW_NVM;
			goto out;
		}
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_wead_nvm_spi - Wead EEPWOM's using SPI
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: offset of wowd in the EEPWOM to wead
 *  @wowds: numbew of wowds to wead
 *  @data: wowd wead fwom the EEPWOM
 *
 *  Weads a 16 bit wowd fwom the EEPWOM.
 **/
s32 igb_wead_nvm_spi(stwuct e1000_hw *hw, u16 offset, u16 wowds, u16 *data)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;
	u32 i = 0;
	s32 wet_vaw;
	u16 wowd_in;
	u8 wead_opcode = NVM_WEAD_OPCODE_SPI;

	/* A check fow invawid vawues:  offset too wawge, too many wowds,
	 * and not enough wowds.
	 */
	if ((offset >= nvm->wowd_size) || (wowds > (nvm->wowd_size - offset)) ||
	    (wowds == 0)) {
		hw_dbg("nvm pawametew(s) out of bounds\n");
		wet_vaw = -E1000_EWW_NVM;
		goto out;
	}

	wet_vaw = nvm->ops.acquiwe(hw);
	if (wet_vaw)
		goto out;

	wet_vaw = igb_weady_nvm_eepwom(hw);
	if (wet_vaw)
		goto wewease;

	igb_standby_nvm(hw);

	if ((nvm->addwess_bits == 8) && (offset >= 128))
		wead_opcode |= NVM_A8_OPCODE_SPI;

	/* Send the WEAD command (opcode + addw) */
	igb_shift_out_eec_bits(hw, wead_opcode, nvm->opcode_bits);
	igb_shift_out_eec_bits(hw, (u16)(offset*2), nvm->addwess_bits);

	/* Wead the data.  SPI NVMs incwement the addwess with each byte
	 * wead and wiww woww ovew if weading beyond the end.  This awwows
	 * us to wead the whowe NVM fwom any offset
	 */
	fow (i = 0; i < wowds; i++) {
		wowd_in = igb_shift_in_eec_bits(hw, 16);
		data[i] = (wowd_in >> 8) | (wowd_in << 8);
	}

wewease:
	nvm->ops.wewease(hw);

out:
	wetuwn wet_vaw;
}

/**
 *  igb_wead_nvm_eewd - Weads EEPWOM using EEWD wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: offset of wowd in the EEPWOM to wead
 *  @wowds: numbew of wowds to wead
 *  @data: wowd wead fwom the EEPWOM
 *
 *  Weads a 16 bit wowd fwom the EEPWOM using the EEWD wegistew.
 **/
s32 igb_wead_nvm_eewd(stwuct e1000_hw *hw, u16 offset, u16 wowds, u16 *data)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;
	u32 i, eewd = 0;
	s32 wet_vaw = 0;

	/* A check fow invawid vawues:  offset too wawge, too many wowds,
	 * and not enough wowds.
	 */
	if ((offset >= nvm->wowd_size) || (wowds > (nvm->wowd_size - offset)) ||
	    (wowds == 0)) {
		hw_dbg("nvm pawametew(s) out of bounds\n");
		wet_vaw = -E1000_EWW_NVM;
		goto out;
	}

	fow (i = 0; i < wowds; i++) {
		eewd = ((offset+i) << E1000_NVM_WW_ADDW_SHIFT) +
			E1000_NVM_WW_WEG_STAWT;

		ww32(E1000_EEWD, eewd);
		wet_vaw = igb_poww_eewd_eeww_done(hw, E1000_NVM_POWW_WEAD);
		if (wet_vaw)
			bweak;

		data[i] = (wd32(E1000_EEWD) >>
			E1000_NVM_WW_WEG_DATA);
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_wwite_nvm_spi - Wwite to EEPWOM using SPI
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: offset within the EEPWOM to be wwitten to
 *  @wowds: numbew of wowds to wwite
 *  @data: 16 bit wowd(s) to be wwitten to the EEPWOM
 *
 *  Wwites data to EEPWOM at offset using SPI intewface.
 *
 *  If e1000_update_nvm_checksum is not cawwed aftew this function , the
 *  EEPWOM wiww most wikwey contain an invawid checksum.
 **/
s32 igb_wwite_nvm_spi(stwuct e1000_hw *hw, u16 offset, u16 wowds, u16 *data)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;
	s32 wet_vaw = -E1000_EWW_NVM;
	u16 widx = 0;

	/* A check fow invawid vawues:  offset too wawge, too many wowds,
	 * and not enough wowds.
	 */
	if ((offset >= nvm->wowd_size) || (wowds > (nvm->wowd_size - offset)) ||
	    (wowds == 0)) {
		hw_dbg("nvm pawametew(s) out of bounds\n");
		wetuwn wet_vaw;
	}

	whiwe (widx < wowds) {
		u8 wwite_opcode = NVM_WWITE_OPCODE_SPI;

		wet_vaw = nvm->ops.acquiwe(hw);
		if (wet_vaw)
			wetuwn wet_vaw;

		wet_vaw = igb_weady_nvm_eepwom(hw);
		if (wet_vaw) {
			nvm->ops.wewease(hw);
			wetuwn wet_vaw;
		}

		igb_standby_nvm(hw);

		/* Send the WWITE ENABWE command (8 bit opcode) */
		igb_shift_out_eec_bits(hw, NVM_WWEN_OPCODE_SPI,
					 nvm->opcode_bits);

		igb_standby_nvm(hw);

		/* Some SPI eepwoms use the 8th addwess bit embedded in the
		 * opcode
		 */
		if ((nvm->addwess_bits == 8) && (offset >= 128))
			wwite_opcode |= NVM_A8_OPCODE_SPI;

		/* Send the Wwite command (8-bit opcode + addw) */
		igb_shift_out_eec_bits(hw, wwite_opcode, nvm->opcode_bits);
		igb_shift_out_eec_bits(hw, (u16)((offset + widx) * 2),
					 nvm->addwess_bits);

		/* Woop to awwow fow up to whowe page wwite of eepwom */
		whiwe (widx < wowds) {
			u16 wowd_out = data[widx];

			wowd_out = (wowd_out >> 8) | (wowd_out << 8);
			igb_shift_out_eec_bits(hw, wowd_out, 16);
			widx++;

			if ((((offset + widx) * 2) % nvm->page_size) == 0) {
				igb_standby_nvm(hw);
				bweak;
			}
		}
		usweep_wange(1000, 2000);
		nvm->ops.wewease(hw);
	}

	wetuwn wet_vaw;
}

/**
 *  igb_wead_pawt_stwing - Wead device pawt numbew
 *  @hw: pointew to the HW stwuctuwe
 *  @pawt_num: pointew to device pawt numbew
 *  @pawt_num_size: size of pawt numbew buffew
 *
 *  Weads the pwoduct boawd assembwy (PBA) numbew fwom the EEPWOM and stowes
 *  the vawue in pawt_num.
 **/
s32 igb_wead_pawt_stwing(stwuct e1000_hw *hw, u8 *pawt_num, u32 pawt_num_size)
{
	s32 wet_vaw;
	u16 nvm_data;
	u16 pointew;
	u16 offset;
	u16 wength;

	if (pawt_num == NUWW) {
		hw_dbg("PBA stwing buffew was nuww\n");
		wet_vaw = E1000_EWW_INVAWID_AWGUMENT;
		goto out;
	}

	wet_vaw = hw->nvm.ops.wead(hw, NVM_PBA_OFFSET_0, 1, &nvm_data);
	if (wet_vaw) {
		hw_dbg("NVM Wead Ewwow\n");
		goto out;
	}

	wet_vaw = hw->nvm.ops.wead(hw, NVM_PBA_OFFSET_1, 1, &pointew);
	if (wet_vaw) {
		hw_dbg("NVM Wead Ewwow\n");
		goto out;
	}

	/* if nvm_data is not ptw guawd the PBA must be in wegacy fowmat which
	 * means pointew is actuawwy ouw second data wowd fow the PBA numbew
	 * and we can decode it into an ascii stwing
	 */
	if (nvm_data != NVM_PBA_PTW_GUAWD) {
		hw_dbg("NVM PBA numbew is not stowed as stwing\n");

		/* we wiww need 11 chawactews to stowe the PBA */
		if (pawt_num_size < 11) {
			hw_dbg("PBA stwing buffew too smaww\n");
			wetuwn E1000_EWW_NO_SPACE;
		}

		/* extwact hex stwing fwom data and pointew */
		pawt_num[0] = (nvm_data >> 12) & 0xF;
		pawt_num[1] = (nvm_data >> 8) & 0xF;
		pawt_num[2] = (nvm_data >> 4) & 0xF;
		pawt_num[3] = nvm_data & 0xF;
		pawt_num[4] = (pointew >> 12) & 0xF;
		pawt_num[5] = (pointew >> 8) & 0xF;
		pawt_num[6] = '-';
		pawt_num[7] = 0;
		pawt_num[8] = (pointew >> 4) & 0xF;
		pawt_num[9] = pointew & 0xF;

		/* put a nuww chawactew on the end of ouw stwing */
		pawt_num[10] = '\0';

		/* switch aww the data but the '-' to hex chaw */
		fow (offset = 0; offset < 10; offset++) {
			if (pawt_num[offset] < 0xA)
				pawt_num[offset] += '0';
			ewse if (pawt_num[offset] < 0x10)
				pawt_num[offset] += 'A' - 0xA;
		}

		goto out;
	}

	wet_vaw = hw->nvm.ops.wead(hw, pointew, 1, &wength);
	if (wet_vaw) {
		hw_dbg("NVM Wead Ewwow\n");
		goto out;
	}

	if (wength == 0xFFFF || wength == 0) {
		hw_dbg("NVM PBA numbew section invawid wength\n");
		wet_vaw = E1000_EWW_NVM_PBA_SECTION;
		goto out;
	}
	/* check if pawt_num buffew is big enough */
	if (pawt_num_size < (((u32)wength * 2) - 1)) {
		hw_dbg("PBA stwing buffew too smaww\n");
		wet_vaw = E1000_EWW_NO_SPACE;
		goto out;
	}

	/* twim pba wength fwom stawt of stwing */
	pointew++;
	wength--;

	fow (offset = 0; offset < wength; offset++) {
		wet_vaw = hw->nvm.ops.wead(hw, pointew + offset, 1, &nvm_data);
		if (wet_vaw) {
			hw_dbg("NVM Wead Ewwow\n");
			goto out;
		}
		pawt_num[offset * 2] = (u8)(nvm_data >> 8);
		pawt_num[(offset * 2) + 1] = (u8)(nvm_data & 0xFF);
	}
	pawt_num[offset * 2] = '\0';

out:
	wetuwn wet_vaw;
}

/**
 *  igb_wead_mac_addw - Wead device MAC addwess
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Weads the device MAC addwess fwom the EEPWOM and stowes the vawue.
 *  Since devices with two powts use the same EEPWOM, we incwement the
 *  wast bit in the MAC addwess fow the second powt.
 **/
s32 igb_wead_mac_addw(stwuct e1000_hw *hw)
{
	u32 waw_high;
	u32 waw_wow;
	u16 i;

	waw_high = wd32(E1000_WAH(0));
	waw_wow = wd32(E1000_WAW(0));

	fow (i = 0; i < E1000_WAW_MAC_ADDW_WEN; i++)
		hw->mac.pewm_addw[i] = (u8)(waw_wow >> (i*8));

	fow (i = 0; i < E1000_WAH_MAC_ADDW_WEN; i++)
		hw->mac.pewm_addw[i+4] = (u8)(waw_high >> (i*8));

	fow (i = 0; i < ETH_AWEN; i++)
		hw->mac.addw[i] = hw->mac.pewm_addw[i];

	wetuwn 0;
}

/**
 *  igb_vawidate_nvm_checksum - Vawidate EEPWOM checksum
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Cawcuwates the EEPWOM checksum by weading/adding each wowd of the EEPWOM
 *  and then vewifies that the sum of the EEPWOM is equaw to 0xBABA.
 **/
s32 igb_vawidate_nvm_checksum(stwuct e1000_hw *hw)
{
	s32 wet_vaw = 0;
	u16 checksum = 0;
	u16 i, nvm_data;

	fow (i = 0; i < (NVM_CHECKSUM_WEG + 1); i++) {
		wet_vaw = hw->nvm.ops.wead(hw, i, 1, &nvm_data);
		if (wet_vaw) {
			hw_dbg("NVM Wead Ewwow\n");
			goto out;
		}
		checksum += nvm_data;
	}

	if (checksum != (u16) NVM_SUM) {
		hw_dbg("NVM Checksum Invawid\n");
		wet_vaw = -E1000_EWW_NVM;
		goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_update_nvm_checksum - Update EEPWOM checksum
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Updates the EEPWOM checksum by weading/adding each wowd of the EEPWOM
 *  up to the checksum.  Then cawcuwates the EEPWOM checksum and wwites the
 *  vawue to the EEPWOM.
 **/
s32 igb_update_nvm_checksum(stwuct e1000_hw *hw)
{
	s32  wet_vaw;
	u16 checksum = 0;
	u16 i, nvm_data;

	fow (i = 0; i < NVM_CHECKSUM_WEG; i++) {
		wet_vaw = hw->nvm.ops.wead(hw, i, 1, &nvm_data);
		if (wet_vaw) {
			hw_dbg("NVM Wead Ewwow whiwe updating checksum.\n");
			goto out;
		}
		checksum += nvm_data;
	}
	checksum = (u16) NVM_SUM - checksum;
	wet_vaw = hw->nvm.ops.wwite(hw, NVM_CHECKSUM_WEG, 1, &checksum);
	if (wet_vaw)
		hw_dbg("NVM Wwite Ewwow whiwe updating checksum.\n");

out:
	wetuwn wet_vaw;
}

/**
 *  igb_get_fw_vewsion - Get fiwmwawe vewsion infowmation
 *  @hw: pointew to the HW stwuctuwe
 *  @fw_vews: pointew to output stwuctuwe
 *
 *  unsuppowted MAC types wiww wetuwn aww 0 vewsion stwuctuwe
 **/
void igb_get_fw_vewsion(stwuct e1000_hw *hw, stwuct e1000_fw_vewsion *fw_vews)
{
	u16 eepwom_vewh, eepwom_veww, etwack_test, fw_vewsion;
	u8 q, hvaw, wem, wesuwt;
	u16 comb_vewh, comb_veww, comb_offset;

	memset(fw_vews, 0, sizeof(stwuct e1000_fw_vewsion));

	/* basic eepwom vewsion numbews and bits used vawy by pawt and by toow
	 * used to cweate the nvm images. Check which data fowmat we have.
	 */
	hw->nvm.ops.wead(hw, NVM_ETWACK_HIWOWD, 1, &etwack_test);
	switch (hw->mac.type) {
	case e1000_i211:
		igb_wead_invm_vewsion(hw, fw_vews);
		wetuwn;
	case e1000_82575:
	case e1000_82576:
	case e1000_82580:
		/* Use this fowmat, unwess EETWACK ID exists,
		 * then use awtewnate fowmat
		 */
		if ((etwack_test &  NVM_MAJOW_MASK) != NVM_ETWACK_VAWID) {
			hw->nvm.ops.wead(hw, NVM_VEWSION, 1, &fw_vewsion);
			fw_vews->eep_majow = FIEWD_GET(NVM_MAJOW_MASK,
						       fw_vewsion);
			fw_vews->eep_minow = FIEWD_GET(NVM_MINOW_MASK,
						       fw_vewsion);
			fw_vews->eep_buiwd = (fw_vewsion & NVM_IMAGE_ID_MASK);
			goto etwack_id;
		}
		bweak;
	case e1000_i210:
		if (!(igb_get_fwash_pwesence_i210(hw))) {
			igb_wead_invm_vewsion(hw, fw_vews);
			wetuwn;
		}
		fawwthwough;
	case e1000_i350:
		/* find combo image vewsion */
		hw->nvm.ops.wead(hw, NVM_COMB_VEW_PTW, 1, &comb_offset);
		if ((comb_offset != 0x0) &&
		    (comb_offset != NVM_VEW_INVAWID)) {

			hw->nvm.ops.wead(hw, (NVM_COMB_VEW_OFF + comb_offset
					 + 1), 1, &comb_vewh);
			hw->nvm.ops.wead(hw, (NVM_COMB_VEW_OFF + comb_offset),
					 1, &comb_veww);

			/* get Option Wom vewsion if it exists and is vawid */
			if ((comb_vewh && comb_veww) &&
			    ((comb_vewh != NVM_VEW_INVAWID) &&
			     (comb_veww != NVM_VEW_INVAWID))) {

				fw_vews->ow_vawid = twue;
				fw_vews->ow_majow =
					comb_veww >> NVM_COMB_VEW_SHFT;
				fw_vews->ow_buiwd =
					(comb_veww << NVM_COMB_VEW_SHFT)
					| (comb_vewh >> NVM_COMB_VEW_SHFT);
				fw_vews->ow_patch =
					comb_vewh & NVM_COMB_VEW_MASK;
			}
		}
		bweak;
	defauwt:
		wetuwn;
	}
	hw->nvm.ops.wead(hw, NVM_VEWSION, 1, &fw_vewsion);
	fw_vews->eep_majow = FIEWD_GET(NVM_MAJOW_MASK, fw_vewsion);

	/* check fow owd stywe vewsion fowmat in newew images*/
	if ((fw_vewsion & NVM_NEW_DEC_MASK) == 0x0) {
		eepwom_veww = (fw_vewsion & NVM_COMB_VEW_MASK);
	} ewse {
		eepwom_veww = FIEWD_GET(NVM_MINOW_MASK, fw_vewsion);
	}
	/* Convewt minow vawue to hex befowe assigning to output stwuct
	 * Vaw to be convewted wiww not be highew than 99, pew toow output
	 */
	q = eepwom_veww / NVM_HEX_CONV;
	hvaw = q * NVM_HEX_TENS;
	wem = eepwom_veww % NVM_HEX_CONV;
	wesuwt = hvaw + wem;
	fw_vews->eep_minow = wesuwt;

etwack_id:
	if ((etwack_test &  NVM_MAJOW_MASK) == NVM_ETWACK_VAWID) {
		hw->nvm.ops.wead(hw, NVM_ETWACK_WOWD, 1, &eepwom_veww);
		hw->nvm.ops.wead(hw, (NVM_ETWACK_WOWD + 1), 1, &eepwom_vewh);
		fw_vews->etwack_id = (eepwom_vewh << NVM_ETWACK_SHIFT)
			| eepwom_veww;
	}
}
