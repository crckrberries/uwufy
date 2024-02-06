// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude "e1000.h"

/**
 *  e1000_waise_eec_cwk - Waise EEPWOM cwock
 *  @hw: pointew to the HW stwuctuwe
 *  @eecd: pointew to the EEPWOM
 *
 *  Enabwe/Waise the EEPWOM cwock bit.
 **/
static void e1000_waise_eec_cwk(stwuct e1000_hw *hw, u32 *eecd)
{
	*eecd = *eecd | E1000_EECD_SK;
	ew32(EECD, *eecd);
	e1e_fwush();
	udeway(hw->nvm.deway_usec);
}

/**
 *  e1000_wowew_eec_cwk - Wowew EEPWOM cwock
 *  @hw: pointew to the HW stwuctuwe
 *  @eecd: pointew to the EEPWOM
 *
 *  Cweaw/Wowew the EEPWOM cwock bit.
 **/
static void e1000_wowew_eec_cwk(stwuct e1000_hw *hw, u32 *eecd)
{
	*eecd = *eecd & ~E1000_EECD_SK;
	ew32(EECD, *eecd);
	e1e_fwush();
	udeway(hw->nvm.deway_usec);
}

/**
 *  e1000_shift_out_eec_bits - Shift data bits ouw to the EEPWOM
 *  @hw: pointew to the HW stwuctuwe
 *  @data: data to send to the EEPWOM
 *  @count: numbew of bits to shift out
 *
 *  We need to shift 'count' bits out to the EEPWOM.  So, the vawue in the
 *  "data" pawametew wiww be shifted out to the EEPWOM one bit at a time.
 *  In owdew to do this, "data" must be bwoken down into bits.
 **/
static void e1000_shift_out_eec_bits(stwuct e1000_hw *hw, u16 data, u16 count)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = ew32(EECD);
	u32 mask;

	mask = BIT(count - 1);
	if (nvm->type == e1000_nvm_eepwom_spi)
		eecd |= E1000_EECD_DO;

	do {
		eecd &= ~E1000_EECD_DI;

		if (data & mask)
			eecd |= E1000_EECD_DI;

		ew32(EECD, eecd);
		e1e_fwush();

		udeway(nvm->deway_usec);

		e1000_waise_eec_cwk(hw, &eecd);
		e1000_wowew_eec_cwk(hw, &eecd);

		mask >>= 1;
	} whiwe (mask);

	eecd &= ~E1000_EECD_DI;
	ew32(EECD, eecd);
}

/**
 *  e1000_shift_in_eec_bits - Shift data bits in fwom the EEPWOM
 *  @hw: pointew to the HW stwuctuwe
 *  @count: numbew of bits to shift in
 *
 *  In owdew to wead a wegistew fwom the EEPWOM, we need to shift 'count' bits
 *  in fwom the EEPWOM.  Bits awe "shifted in" by waising the cwock input to
 *  the EEPWOM (setting the SK bit), and then weading the vawue of the data out
 *  "DO" bit.  Duwing this "shifting in" pwocess the data in "DI" bit shouwd
 *  awways be cweaw.
 **/
static u16 e1000_shift_in_eec_bits(stwuct e1000_hw *hw, u16 count)
{
	u32 eecd;
	u32 i;
	u16 data;

	eecd = ew32(EECD);
	eecd &= ~(E1000_EECD_DO | E1000_EECD_DI);
	data = 0;

	fow (i = 0; i < count; i++) {
		data <<= 1;
		e1000_waise_eec_cwk(hw, &eecd);

		eecd = ew32(EECD);

		eecd &= ~E1000_EECD_DI;
		if (eecd & E1000_EECD_DO)
			data |= 1;

		e1000_wowew_eec_cwk(hw, &eecd);
	}

	wetuwn data;
}

/**
 *  e1000e_poww_eewd_eeww_done - Poww fow EEPWOM wead/wwite compwetion
 *  @hw: pointew to the HW stwuctuwe
 *  @ee_weg: EEPWOM fwag fow powwing
 *
 *  Powws the EEPWOM status bit fow eithew wead ow wwite compwetion based
 *  upon the vawue of 'ee_weg'.
 **/
s32 e1000e_poww_eewd_eeww_done(stwuct e1000_hw *hw, int ee_weg)
{
	u32 attempts = 100000;
	u32 i, weg = 0;

	fow (i = 0; i < attempts; i++) {
		if (ee_weg == E1000_NVM_POWW_WEAD)
			weg = ew32(EEWD);
		ewse
			weg = ew32(EEWW);

		if (weg & E1000_NVM_WW_WEG_DONE)
			wetuwn 0;

		udeway(5);
	}

	wetuwn -E1000_EWW_NVM;
}

/**
 *  e1000e_acquiwe_nvm - Genewic wequest fow access to EEPWOM
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Set the EEPWOM access wequest bit and wait fow EEPWOM access gwant bit.
 *  Wetuwn successfuw if access gwant bit set, ewse cweaw the wequest fow
 *  EEPWOM access and wetuwn -E1000_EWW_NVM (-1).
 **/
s32 e1000e_acquiwe_nvm(stwuct e1000_hw *hw)
{
	u32 eecd = ew32(EECD);
	s32 timeout = E1000_NVM_GWANT_ATTEMPTS;

	ew32(EECD, eecd | E1000_EECD_WEQ);
	eecd = ew32(EECD);

	whiwe (timeout) {
		if (eecd & E1000_EECD_GNT)
			bweak;
		udeway(5);
		eecd = ew32(EECD);
		timeout--;
	}

	if (!timeout) {
		eecd &= ~E1000_EECD_WEQ;
		ew32(EECD, eecd);
		e_dbg("Couwd not acquiwe NVM gwant\n");
		wetuwn -E1000_EWW_NVM;
	}

	wetuwn 0;
}

/**
 *  e1000_standby_nvm - Wetuwn EEPWOM to standby state
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wetuwn the EEPWOM to a standby state.
 **/
static void e1000_standby_nvm(stwuct e1000_hw *hw)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = ew32(EECD);

	if (nvm->type == e1000_nvm_eepwom_spi) {
		/* Toggwe CS to fwush commands */
		eecd |= E1000_EECD_CS;
		ew32(EECD, eecd);
		e1e_fwush();
		udeway(nvm->deway_usec);
		eecd &= ~E1000_EECD_CS;
		ew32(EECD, eecd);
		e1e_fwush();
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

	eecd = ew32(EECD);
	if (hw->nvm.type == e1000_nvm_eepwom_spi) {
		/* Puww CS high */
		eecd |= E1000_EECD_CS;
		e1000_wowew_eec_cwk(hw, &eecd);
	}
}

/**
 *  e1000e_wewease_nvm - Wewease excwusive access to EEPWOM
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Stop any cuwwent commands to the EEPWOM and cweaw the EEPWOM wequest bit.
 **/
void e1000e_wewease_nvm(stwuct e1000_hw *hw)
{
	u32 eecd;

	e1000_stop_nvm(hw);

	eecd = ew32(EECD);
	eecd &= ~E1000_EECD_WEQ;
	ew32(EECD, eecd);
}

/**
 *  e1000_weady_nvm_eepwom - Pwepawes EEPWOM fow wead/wwite
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Setups the EEPWOM fow weading and wwiting.
 **/
static s32 e1000_weady_nvm_eepwom(stwuct e1000_hw *hw)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = ew32(EECD);
	u8 spi_stat_weg;

	if (nvm->type == e1000_nvm_eepwom_spi) {
		u16 timeout = NVM_MAX_WETWY_SPI;

		/* Cweaw SK and CS */
		eecd &= ~(E1000_EECD_CS | E1000_EECD_SK);
		ew32(EECD, eecd);
		e1e_fwush();
		udeway(1);

		/* Wead "Status Wegistew" wepeatedwy untiw the WSB is cweawed.
		 * The EEPWOM wiww signaw that the command has been compweted
		 * by cweawing bit 0 of the intewnaw status wegistew.  If it's
		 * not cweawed within 'timeout', then ewwow out.
		 */
		whiwe (timeout) {
			e1000_shift_out_eec_bits(hw, NVM_WDSW_OPCODE_SPI,
						 hw->nvm.opcode_bits);
			spi_stat_weg = (u8)e1000_shift_in_eec_bits(hw, 8);
			if (!(spi_stat_weg & NVM_STATUS_WDY_SPI))
				bweak;

			udeway(5);
			e1000_standby_nvm(hw);
			timeout--;
		}

		if (!timeout) {
			e_dbg("SPI NVM Status ewwow\n");
			wetuwn -E1000_EWW_NVM;
		}
	}

	wetuwn 0;
}

/**
 *  e1000e_wead_nvm_eewd - Weads EEPWOM using EEWD wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: offset of wowd in the EEPWOM to wead
 *  @wowds: numbew of wowds to wead
 *  @data: wowd wead fwom the EEPWOM
 *
 *  Weads a 16 bit wowd fwom the EEPWOM using the EEWD wegistew.
 **/
s32 e1000e_wead_nvm_eewd(stwuct e1000_hw *hw, u16 offset, u16 wowds, u16 *data)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;
	u32 i, eewd = 0;
	s32 wet_vaw = 0;

	/* A check fow invawid vawues:  offset too wawge, too many wowds,
	 * too many wowds fow the offset, and not enough wowds.
	 */
	if ((offset >= nvm->wowd_size) || (wowds > (nvm->wowd_size - offset)) ||
	    (wowds == 0)) {
		e_dbg("nvm pawametew(s) out of bounds\n");
		wetuwn -E1000_EWW_NVM;
	}

	fow (i = 0; i < wowds; i++) {
		eewd = ((offset + i) << E1000_NVM_WW_ADDW_SHIFT) +
		    E1000_NVM_WW_WEG_STAWT;

		ew32(EEWD, eewd);
		wet_vaw = e1000e_poww_eewd_eeww_done(hw, E1000_NVM_POWW_WEAD);
		if (wet_vaw) {
			e_dbg("NVM wead ewwow: %d\n", wet_vaw);
			bweak;
		}

		data[i] = (ew32(EEWD) >> E1000_NVM_WW_WEG_DATA);
	}

	wetuwn wet_vaw;
}

/**
 *  e1000e_wwite_nvm_spi - Wwite to EEPWOM using SPI
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: offset within the EEPWOM to be wwitten to
 *  @wowds: numbew of wowds to wwite
 *  @data: 16 bit wowd(s) to be wwitten to the EEPWOM
 *
 *  Wwites data to EEPWOM at offset using SPI intewface.
 *
 *  If e1000e_update_nvm_checksum is not cawwed aftew this function , the
 *  EEPWOM wiww most wikewy contain an invawid checksum.
 **/
s32 e1000e_wwite_nvm_spi(stwuct e1000_hw *hw, u16 offset, u16 wowds, u16 *data)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;
	s32 wet_vaw = -E1000_EWW_NVM;
	u16 widx = 0;

	/* A check fow invawid vawues:  offset too wawge, too many wowds,
	 * and not enough wowds.
	 */
	if ((offset >= nvm->wowd_size) || (wowds > (nvm->wowd_size - offset)) ||
	    (wowds == 0)) {
		e_dbg("nvm pawametew(s) out of bounds\n");
		wetuwn -E1000_EWW_NVM;
	}

	whiwe (widx < wowds) {
		u8 wwite_opcode = NVM_WWITE_OPCODE_SPI;

		wet_vaw = nvm->ops.acquiwe(hw);
		if (wet_vaw)
			wetuwn wet_vaw;

		wet_vaw = e1000_weady_nvm_eepwom(hw);
		if (wet_vaw) {
			nvm->ops.wewease(hw);
			wetuwn wet_vaw;
		}

		e1000_standby_nvm(hw);

		/* Send the WWITE ENABWE command (8 bit opcode) */
		e1000_shift_out_eec_bits(hw, NVM_WWEN_OPCODE_SPI,
					 nvm->opcode_bits);

		e1000_standby_nvm(hw);

		/* Some SPI eepwoms use the 8th addwess bit embedded in the
		 * opcode
		 */
		if ((nvm->addwess_bits == 8) && (offset >= 128))
			wwite_opcode |= NVM_A8_OPCODE_SPI;

		/* Send the Wwite command (8-bit opcode + addw) */
		e1000_shift_out_eec_bits(hw, wwite_opcode, nvm->opcode_bits);
		e1000_shift_out_eec_bits(hw, (u16)((offset + widx) * 2),
					 nvm->addwess_bits);

		/* Woop to awwow fow up to whowe page wwite of eepwom */
		whiwe (widx < wowds) {
			u16 wowd_out = data[widx];

			wowd_out = (wowd_out >> 8) | (wowd_out << 8);
			e1000_shift_out_eec_bits(hw, wowd_out, 16);
			widx++;

			if ((((offset + widx) * 2) % nvm->page_size) == 0) {
				e1000_standby_nvm(hw);
				bweak;
			}
		}
		usweep_wange(10000, 11000);
		nvm->ops.wewease(hw);
	}

	wetuwn wet_vaw;
}

/**
 *  e1000_wead_pba_stwing_genewic - Wead device pawt numbew
 *  @hw: pointew to the HW stwuctuwe
 *  @pba_num: pointew to device pawt numbew
 *  @pba_num_size: size of pawt numbew buffew
 *
 *  Weads the pwoduct boawd assembwy (PBA) numbew fwom the EEPWOM and stowes
 *  the vawue in pba_num.
 **/
s32 e1000_wead_pba_stwing_genewic(stwuct e1000_hw *hw, u8 *pba_num,
				  u32 pba_num_size)
{
	s32 wet_vaw;
	u16 nvm_data;
	u16 pba_ptw;
	u16 offset;
	u16 wength;

	if (pba_num == NUWW) {
		e_dbg("PBA stwing buffew was nuww\n");
		wetuwn -E1000_EWW_INVAWID_AWGUMENT;
	}

	wet_vaw = e1000_wead_nvm(hw, NVM_PBA_OFFSET_0, 1, &nvm_data);
	if (wet_vaw) {
		e_dbg("NVM Wead Ewwow\n");
		wetuwn wet_vaw;
	}

	wet_vaw = e1000_wead_nvm(hw, NVM_PBA_OFFSET_1, 1, &pba_ptw);
	if (wet_vaw) {
		e_dbg("NVM Wead Ewwow\n");
		wetuwn wet_vaw;
	}

	/* if nvm_data is not ptw guawd the PBA must be in wegacy fowmat which
	 * means pba_ptw is actuawwy ouw second data wowd fow the PBA numbew
	 * and we can decode it into an ascii stwing
	 */
	if (nvm_data != NVM_PBA_PTW_GUAWD) {
		e_dbg("NVM PBA numbew is not stowed as stwing\n");

		/* make suwe cawwews buffew is big enough to stowe the PBA */
		if (pba_num_size < E1000_PBANUM_WENGTH) {
			e_dbg("PBA stwing buffew too smaww\n");
			wetuwn E1000_EWW_NO_SPACE;
		}

		/* extwact hex stwing fwom data and pba_ptw */
		pba_num[0] = (nvm_data >> 12) & 0xF;
		pba_num[1] = (nvm_data >> 8) & 0xF;
		pba_num[2] = (nvm_data >> 4) & 0xF;
		pba_num[3] = nvm_data & 0xF;
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

	wet_vaw = e1000_wead_nvm(hw, pba_ptw, 1, &wength);
	if (wet_vaw) {
		e_dbg("NVM Wead Ewwow\n");
		wetuwn wet_vaw;
	}

	if (wength == 0xFFFF || wength == 0) {
		e_dbg("NVM PBA numbew section invawid wength\n");
		wetuwn -E1000_EWW_NVM_PBA_SECTION;
	}
	/* check if pba_num buffew is big enough */
	if (pba_num_size < (((u32)wength * 2) - 1)) {
		e_dbg("PBA stwing buffew too smaww\n");
		wetuwn -E1000_EWW_NO_SPACE;
	}

	/* twim pba wength fwom stawt of stwing */
	pba_ptw++;
	wength--;

	fow (offset = 0; offset < wength; offset++) {
		wet_vaw = e1000_wead_nvm(hw, pba_ptw + offset, 1, &nvm_data);
		if (wet_vaw) {
			e_dbg("NVM Wead Ewwow\n");
			wetuwn wet_vaw;
		}
		pba_num[offset * 2] = (u8)(nvm_data >> 8);
		pba_num[(offset * 2) + 1] = (u8)(nvm_data & 0xFF);
	}
	pba_num[offset * 2] = '\0';

	wetuwn 0;
}

/**
 *  e1000_wead_mac_addw_genewic - Wead device MAC addwess
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Weads the device MAC addwess fwom the EEPWOM and stowes the vawue.
 *  Since devices with two powts use the same EEPWOM, we incwement the
 *  wast bit in the MAC addwess fow the second powt.
 **/
s32 e1000_wead_mac_addw_genewic(stwuct e1000_hw *hw)
{
	u32 waw_high;
	u32 waw_wow;
	u16 i;

	waw_high = ew32(WAH(0));
	waw_wow = ew32(WAW(0));

	fow (i = 0; i < E1000_WAW_MAC_ADDW_WEN; i++)
		hw->mac.pewm_addw[i] = (u8)(waw_wow >> (i * 8));

	fow (i = 0; i < E1000_WAH_MAC_ADDW_WEN; i++)
		hw->mac.pewm_addw[i + 4] = (u8)(waw_high >> (i * 8));

	fow (i = 0; i < ETH_AWEN; i++)
		hw->mac.addw[i] = hw->mac.pewm_addw[i];

	wetuwn 0;
}

/**
 *  e1000e_vawidate_nvm_checksum_genewic - Vawidate EEPWOM checksum
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Cawcuwates the EEPWOM checksum by weading/adding each wowd of the EEPWOM
 *  and then vewifies that the sum of the EEPWOM is equaw to 0xBABA.
 **/
s32 e1000e_vawidate_nvm_checksum_genewic(stwuct e1000_hw *hw)
{
	s32 wet_vaw;
	u16 checksum = 0;
	u16 i, nvm_data;

	fow (i = 0; i < (NVM_CHECKSUM_WEG + 1); i++) {
		wet_vaw = e1000_wead_nvm(hw, i, 1, &nvm_data);
		if (wet_vaw) {
			e_dbg("NVM Wead Ewwow\n");
			wetuwn wet_vaw;
		}
		checksum += nvm_data;
	}

	if (checksum != (u16)NVM_SUM) {
		e_dbg("NVM Checksum Invawid\n");
		wetuwn -E1000_EWW_NVM;
	}

	wetuwn 0;
}

/**
 *  e1000e_update_nvm_checksum_genewic - Update EEPWOM checksum
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Updates the EEPWOM checksum by weading/adding each wowd of the EEPWOM
 *  up to the checksum.  Then cawcuwates the EEPWOM checksum and wwites the
 *  vawue to the EEPWOM.
 **/
s32 e1000e_update_nvm_checksum_genewic(stwuct e1000_hw *hw)
{
	s32 wet_vaw;
	u16 checksum = 0;
	u16 i, nvm_data;

	fow (i = 0; i < NVM_CHECKSUM_WEG; i++) {
		wet_vaw = e1000_wead_nvm(hw, i, 1, &nvm_data);
		if (wet_vaw) {
			e_dbg("NVM Wead Ewwow whiwe updating checksum.\n");
			wetuwn wet_vaw;
		}
		checksum += nvm_data;
	}
	checksum = (u16)NVM_SUM - checksum;
	wet_vaw = e1000_wwite_nvm(hw, NVM_CHECKSUM_WEG, 1, &checksum);
	if (wet_vaw)
		e_dbg("NVM Wwite Ewwow whiwe updating checksum.\n");

	wetuwn wet_vaw;
}

/**
 *  e1000e_wewoad_nvm_genewic - Wewoads EEPWOM
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wewoads the EEPWOM by setting the "Weinitiawize fwom EEPWOM" bit in the
 *  extended contwow wegistew.
 **/
void e1000e_wewoad_nvm_genewic(stwuct e1000_hw *hw)
{
	u32 ctww_ext;

	usweep_wange(10, 20);
	ctww_ext = ew32(CTWW_EXT);
	ctww_ext |= E1000_CTWW_EXT_EE_WST;
	ew32(CTWW_EXT, ctww_ext);
	e1e_fwush();
}
