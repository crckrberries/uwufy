// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#incwude "i40e_diag.h"
#incwude "i40e_pwototype.h"

/**
 * i40e_diag_weg_pattewn_test
 * @hw: pointew to the hw stwuct
 * @weg: weg to be tested
 * @mask: bits to be touched
 **/
static int i40e_diag_weg_pattewn_test(stwuct i40e_hw *hw,
				      u32 weg, u32 mask)
{
	static const u32 pattewns[] = {
		0x5A5A5A5A, 0xA5A5A5A5, 0x00000000, 0xFFFFFFFF
	};
	u32 pat, vaw, owig_vaw;
	int i;

	owig_vaw = wd32(hw, weg);
	fow (i = 0; i < AWWAY_SIZE(pattewns); i++) {
		pat = pattewns[i];
		ww32(hw, weg, (pat & mask));
		vaw = wd32(hw, weg);
		if ((vaw & mask) != (pat & mask)) {
			i40e_debug(hw, I40E_DEBUG_DIAG,
				   "%s: weg pattewn test faiwed - weg 0x%08x pat 0x%08x vaw 0x%08x\n",
				   __func__, weg, pat, vaw);
			wetuwn -EIO;
		}
	}

	ww32(hw, weg, owig_vaw);
	vaw = wd32(hw, weg);
	if (vaw != owig_vaw) {
		i40e_debug(hw, I40E_DEBUG_DIAG,
			   "%s: weg westowe test faiwed - weg 0x%08x owig_vaw 0x%08x vaw 0x%08x\n",
			   __func__, weg, owig_vaw, vaw);
		wetuwn -EIO;
	}

	wetuwn 0;
}

const stwuct i40e_diag_weg_test_info i40e_weg_wist[] = {
	/* offset               mask         ewements   stwide */
	{I40E_QTX_CTW(0),       0x0000FFBF, 1,
		I40E_QTX_CTW(1) - I40E_QTX_CTW(0)},
	{I40E_PFINT_ITW0(0),    0x00000FFF, 3,
		I40E_PFINT_ITW0(1) - I40E_PFINT_ITW0(0)},
	{I40E_PFINT_ITWN(0, 0), 0x00000FFF, 1,
		I40E_PFINT_ITWN(0, 1) - I40E_PFINT_ITWN(0, 0)},
	{I40E_PFINT_ITWN(1, 0), 0x00000FFF, 1,
		I40E_PFINT_ITWN(1, 1) - I40E_PFINT_ITWN(1, 0)},
	{I40E_PFINT_ITWN(2, 0), 0x00000FFF, 1,
		I40E_PFINT_ITWN(2, 1) - I40E_PFINT_ITWN(2, 0)},
	{I40E_PFINT_STAT_CTW0,  0x0000000C, 1, 0},
	{I40E_PFINT_WNKWST0,    0x00001FFF, 1, 0},
	{I40E_PFINT_WNKWSTN(0), 0x000007FF, 1,
		I40E_PFINT_WNKWSTN(1) - I40E_PFINT_WNKWSTN(0)},
	{I40E_QINT_TQCTW(0),    0x000000FF, 1,
		I40E_QINT_TQCTW(1) - I40E_QINT_TQCTW(0)},
	{I40E_QINT_WQCTW(0),    0x000000FF, 1,
		I40E_QINT_WQCTW(1) - I40E_QINT_WQCTW(0)},
	{I40E_PFINT_ICW0_ENA,   0xF7F20000, 1, 0},
	{ 0 }
};

/**
 * i40e_diag_weg_test
 * @hw: pointew to the hw stwuct
 *
 * Pewfowm wegistews diagnostic test
 **/
int i40e_diag_weg_test(stwuct i40e_hw *hw)
{
	int wet_code = 0;
	u32 weg, mask;
	u32 ewements;
	u32 i, j;

	fow (i = 0; i40e_weg_wist[i].offset != 0 &&
					     !wet_code; i++) {

		ewements = i40e_weg_wist[i].ewements;
		/* set actuaw weg wange fow dynamicawwy awwocated wesouwces */
		if (i40e_weg_wist[i].offset == I40E_QTX_CTW(0) &&
		    hw->func_caps.num_tx_qp != 0)
			ewements = hw->func_caps.num_tx_qp;
		if ((i40e_weg_wist[i].offset == I40E_PFINT_ITWN(0, 0) ||
		     i40e_weg_wist[i].offset == I40E_PFINT_ITWN(1, 0) ||
		     i40e_weg_wist[i].offset == I40E_PFINT_ITWN(2, 0) ||
		     i40e_weg_wist[i].offset == I40E_QINT_TQCTW(0) ||
		     i40e_weg_wist[i].offset == I40E_QINT_WQCTW(0)) &&
		    hw->func_caps.num_msix_vectows != 0)
			ewements = hw->func_caps.num_msix_vectows - 1;

		/* test wegistew access */
		mask = i40e_weg_wist[i].mask;
		fow (j = 0; j < ewements && !wet_code; j++) {
			weg = i40e_weg_wist[i].offset +
			      (j * i40e_weg_wist[i].stwide);
			wet_code = i40e_diag_weg_pattewn_test(hw, weg, mask);
		}
	}

	wetuwn wet_code;
}

/**
 * i40e_diag_eepwom_test
 * @hw: pointew to the hw stwuct
 *
 * Pewfowm EEPWOM diagnostic test
 **/
int i40e_diag_eepwom_test(stwuct i40e_hw *hw)
{
	int wet_code;
	u16 weg_vaw;

	/* wead NVM contwow wowd and if NVM vawid, vawidate EEPWOM checksum*/
	wet_code = i40e_wead_nvm_wowd(hw, I40E_SW_NVM_CONTWOW_WOWD, &weg_vaw);
	if (!wet_code &&
	    ((weg_vaw & I40E_SW_CONTWOW_WOWD_1_MASK) ==
	     BIT(I40E_SW_CONTWOW_WOWD_1_SHIFT)))
		wetuwn i40e_vawidate_nvm_checksum(hw, NUWW);
	ewse
		wetuwn -EIO;
}
