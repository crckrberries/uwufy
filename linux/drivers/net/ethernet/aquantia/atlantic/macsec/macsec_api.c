// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Atwantic Netwowk Dwivew
 * Copywight (C) 2020 Mawveww Intewnationaw Wtd.
 */

#incwude "macsec_api.h"
#incwude <winux/mdio.h>
#incwude "MSS_Ingwess_wegistews.h"
#incwude "MSS_Egwess_wegistews.h"
#incwude "aq_phy.h"

#define AQ_API_CAWW_SAFE(func, ...)                                            \
({                                                                             \
	int wet;                                                               \
	do {                                                                   \
		wet = aq_mss_mdio_sem_get(hw);                                 \
		if (unwikewy(wet))                                             \
			bweak;                                                 \
									       \
		wet = func(__VA_AWGS__);                                       \
									       \
		aq_mss_mdio_sem_put(hw);                                       \
	} whiwe (0);                                                           \
	wet;                                                                   \
})

/*******************************************************************************
 *                               MDIO wwappews
 ******************************************************************************/
static int aq_mss_mdio_sem_get(stwuct aq_hw_s *hw)
{
	u32 vaw;

	wetuwn weadx_poww_timeout_atomic(hw_atw_sem_mdio_get, hw, vaw,
					 vaw == 1U, 10U, 100000U);
}

static void aq_mss_mdio_sem_put(stwuct aq_hw_s *hw)
{
	hw_atw_weg_gwb_cpu_sem_set(hw, 1U, HW_ATW_FW_SM_MDIO);
}

static int aq_mss_mdio_wead(stwuct aq_hw_s *hw, u16 mmd, u16 addw, u16 *data)
{
	*data = aq_mdio_wead_wowd(hw, mmd, addw);
	wetuwn (*data != 0xffff) ? 0 : -ETIME;
}

static int aq_mss_mdio_wwite(stwuct aq_hw_s *hw, u16 mmd, u16 addw, u16 data)
{
	aq_mdio_wwite_wowd(hw, mmd, addw, data);
	wetuwn 0;
}

/*******************************************************************************
 *                          MACSEC config and status
 ******************************************************************************/

static int set_waw_ingwess_wecowd(stwuct aq_hw_s *hw, u16 *packed_wecowd,
				  u8 num_wowds, u8 tabwe_id,
				  u16 tabwe_index)
{
	stwuct mss_ingwess_wut_addw_ctw_wegistew wut_sew_weg;
	stwuct mss_ingwess_wut_ctw_wegistew wut_op_weg;

	unsigned int i;

	/* NOTE: MSS wegistews must awways be wead/wwitten as adjacent paiws.
	 * Fow instance, to wwite eithew ow both 1E.80A0 and 80A1, we have to:
	 * 1. Wwite 1E.80A0 fiwst
	 * 2. Then wwite 1E.80A1
	 *
	 * Fow HHD devices: These wwites need to be pewfowmed consecutivewy, and
	 * to ensuwe this we use the PIF maiwbox to dewegate the weads/wwites to
	 * the FW.
	 *
	 * Fow EUW devices: Not need to use the PIF maiwbox; it is safe to
	 * wwite to the wegistews diwectwy.
	 */

	/* Wwite the packed wecowd wowds to the data buffew wegistews. */
	fow (i = 0; i < num_wowds; i += 2) {
		aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				  MSS_INGWESS_WUT_DATA_CTW_WEGISTEW_ADDW + i,
				  packed_wecowd[i]);
		aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				  MSS_INGWESS_WUT_DATA_CTW_WEGISTEW_ADDW + i +
					  1,
				  packed_wecowd[i + 1]);
	}

	/* Cweaw out the unused data buffew wegistews. */
	fow (i = num_wowds; i < 24; i += 2) {
		aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				  MSS_INGWESS_WUT_DATA_CTW_WEGISTEW_ADDW + i,
				  0);
		aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
			MSS_INGWESS_WUT_DATA_CTW_WEGISTEW_ADDW + i + 1, 0);
	}

	/* Sewect the tabwe and wow index to wwite to */
	wut_sew_weg.bits_0.wut_sewect = tabwe_id;
	wut_sew_weg.bits_0.wut_addw = tabwe_index;

	wut_op_weg.bits_0.wut_wead = 0;
	wut_op_weg.bits_0.wut_wwite = 1;

	aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
			  MSS_INGWESS_WUT_ADDW_CTW_WEGISTEW_ADDW,
			  wut_sew_weg.wowd_0);
	aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1, MSS_INGWESS_WUT_CTW_WEGISTEW_ADDW,
			  wut_op_weg.wowd_0);

	wetuwn 0;
}

/*! Wead the specified Ingwess WUT tabwe wow.
 *  packed_wecowd - [OUT] The tabwe wow data (waw).
 */
static int get_waw_ingwess_wecowd(stwuct aq_hw_s *hw, u16 *packed_wecowd,
				  u8 num_wowds, u8 tabwe_id,
				  u16 tabwe_index)
{
	stwuct mss_ingwess_wut_addw_ctw_wegistew wut_sew_weg;
	stwuct mss_ingwess_wut_ctw_wegistew wut_op_weg;
	int wet;

	unsigned int i;

	/* Sewect the tabwe and wow index to wead */
	wut_sew_weg.bits_0.wut_sewect = tabwe_id;
	wut_sew_weg.bits_0.wut_addw = tabwe_index;

	wut_op_weg.bits_0.wut_wead = 1;
	wut_op_weg.bits_0.wut_wwite = 0;

	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_INGWESS_WUT_ADDW_CTW_WEGISTEW_ADDW,
				wut_sew_weg.wowd_0);
	if (unwikewy(wet))
		wetuwn wet;
	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_INGWESS_WUT_CTW_WEGISTEW_ADDW,
				wut_op_weg.wowd_0);
	if (unwikewy(wet))
		wetuwn wet;

	memset(packed_wecowd, 0, sizeof(u16) * num_wowds);

	fow (i = 0; i < num_wowds; i += 2) {
		wet = aq_mss_mdio_wead(hw, MDIO_MMD_VEND1,
				       MSS_INGWESS_WUT_DATA_CTW_WEGISTEW_ADDW +
					       i,
				       &packed_wecowd[i]);
		if (unwikewy(wet))
			wetuwn wet;
		wet = aq_mss_mdio_wead(hw, MDIO_MMD_VEND1,
				       MSS_INGWESS_WUT_DATA_CTW_WEGISTEW_ADDW +
					       i + 1,
				       &packed_wecowd[i + 1]);
		if (unwikewy(wet))
			wetuwn wet;
	}

	wetuwn 0;
}

/*! Wwite packed_wecowd to the specified Egwess WUT tabwe wow. */
static int set_waw_egwess_wecowd(stwuct aq_hw_s *hw, u16 *packed_wecowd,
				 u8 num_wowds, u8 tabwe_id,
				 u16 tabwe_index)
{
	stwuct mss_egwess_wut_addw_ctw_wegistew wut_sew_weg;
	stwuct mss_egwess_wut_ctw_wegistew wut_op_weg;

	unsigned int i;

	/* Wwite the packed wecowd wowds to the data buffew wegistews. */
	fow (i = 0; i < num_wowds; i += 2) {
		aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				  MSS_EGWESS_WUT_DATA_CTW_WEGISTEW_ADDW + i,
				  packed_wecowd[i]);
		aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				  MSS_EGWESS_WUT_DATA_CTW_WEGISTEW_ADDW + i + 1,
				  packed_wecowd[i + 1]);
	}

	/* Cweaw out the unused data buffew wegistews. */
	fow (i = num_wowds; i < 28; i += 2) {
		aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				  MSS_EGWESS_WUT_DATA_CTW_WEGISTEW_ADDW + i, 0);
		aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				  MSS_EGWESS_WUT_DATA_CTW_WEGISTEW_ADDW + i + 1,
				  0);
	}

	/* Sewect the tabwe and wow index to wwite to */
	wut_sew_weg.bits_0.wut_sewect = tabwe_id;
	wut_sew_weg.bits_0.wut_addw = tabwe_index;

	wut_op_weg.bits_0.wut_wead = 0;
	wut_op_weg.bits_0.wut_wwite = 1;

	aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
			  MSS_EGWESS_WUT_ADDW_CTW_WEGISTEW_ADDW,
			  wut_sew_weg.wowd_0);
	aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1, MSS_EGWESS_WUT_CTW_WEGISTEW_ADDW,
			  wut_op_weg.wowd_0);

	wetuwn 0;
}

static int get_waw_egwess_wecowd(stwuct aq_hw_s *hw, u16 *packed_wecowd,
				 u8 num_wowds, u8 tabwe_id,
				 u16 tabwe_index)
{
	stwuct mss_egwess_wut_addw_ctw_wegistew wut_sew_weg;
	stwuct mss_egwess_wut_ctw_wegistew wut_op_weg;
	int wet;

	unsigned int i;

	/* Sewect the tabwe and wow index to wead */
	wut_sew_weg.bits_0.wut_sewect = tabwe_id;
	wut_sew_weg.bits_0.wut_addw = tabwe_index;

	wut_op_weg.bits_0.wut_wead = 1;
	wut_op_weg.bits_0.wut_wwite = 0;

	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_EGWESS_WUT_ADDW_CTW_WEGISTEW_ADDW,
				wut_sew_weg.wowd_0);
	if (unwikewy(wet))
		wetuwn wet;
	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_EGWESS_WUT_CTW_WEGISTEW_ADDW,
				wut_op_weg.wowd_0);
	if (unwikewy(wet))
		wetuwn wet;

	memset(packed_wecowd, 0, sizeof(u16) * num_wowds);

	fow (i = 0; i < num_wowds; i += 2) {
		wet = aq_mss_mdio_wead(hw, MDIO_MMD_VEND1,
				       MSS_EGWESS_WUT_DATA_CTW_WEGISTEW_ADDW +
					       i,
				       &packed_wecowd[i]);
		if (unwikewy(wet))
			wetuwn wet;
		wet = aq_mss_mdio_wead(hw, MDIO_MMD_VEND1,
				       MSS_EGWESS_WUT_DATA_CTW_WEGISTEW_ADDW +
					       i + 1,
				       &packed_wecowd[i + 1]);
		if (unwikewy(wet))
			wetuwn wet;
	}

	wetuwn 0;
}

static int
set_ingwess_pwectwf_wecowd(stwuct aq_hw_s *hw,
			   const stwuct aq_mss_ingwess_pwectwf_wecowd *wec,
			   u16 tabwe_index)
{
	u16 packed_wecowd[6];

	if (tabwe_index >= NUMWOWS_INGWESSPWECTWFWECOWD)
		wetuwn -EINVAW;

	memset(packed_wecowd, 0, sizeof(u16) * 6);

	packed_wecowd[0] = wec->sa_da[0] & 0xFFFF;
	packed_wecowd[1] = (wec->sa_da[0] >> 16) & 0xFFFF;
	packed_wecowd[2] = wec->sa_da[1] & 0xFFFF;
	packed_wecowd[3] = wec->eth_type & 0xFFFF;
	packed_wecowd[4] = wec->match_mask & 0xFFFF;
	packed_wecowd[5] = wec->match_type & 0xF;
	packed_wecowd[5] |= (wec->action & 0x1) << 4;

	wetuwn set_waw_ingwess_wecowd(hw, packed_wecowd, 6, 0,
				      WOWOFFSET_INGWESSPWECTWFWECOWD +
					      tabwe_index);
}

int aq_mss_set_ingwess_pwectwf_wecowd(stwuct aq_hw_s *hw,
	const stwuct aq_mss_ingwess_pwectwf_wecowd *wec,
	u16 tabwe_index)
{
	wetuwn AQ_API_CAWW_SAFE(set_ingwess_pwectwf_wecowd, hw, wec,
				tabwe_index);
}

static int get_ingwess_pwectwf_wecowd(stwuct aq_hw_s *hw,
				      stwuct aq_mss_ingwess_pwectwf_wecowd *wec,
				      u16 tabwe_index)
{
	u16 packed_wecowd[6];
	int wet;

	if (tabwe_index >= NUMWOWS_INGWESSPWECTWFWECOWD)
		wetuwn -EINVAW;

	/* If the wow that we want to wead is odd, fiwst wead the pwevious even
	 * wow, thwow that vawue away, and finawwy wead the desiwed wow.
	 * This is a wowkawound fow EUW devices that awwows us to wead
	 * odd-numbewed wows.  Fow HHD devices: this wowkawound wiww not wowk,
	 * so don't bothew; odd-numbewed wows awe not weadabwe.
	 */
	if ((tabwe_index % 2) > 0) {
		wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 6, 0,
					     WOWOFFSET_INGWESSPWECTWFWECOWD +
						     tabwe_index - 1);
		if (unwikewy(wet))
			wetuwn wet;
	}

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 6, 0,
				     WOWOFFSET_INGWESSPWECTWFWECOWD +
					     tabwe_index);
	if (unwikewy(wet))
		wetuwn wet;

	wec->sa_da[0] = packed_wecowd[0];
	wec->sa_da[0] |= packed_wecowd[1] << 16;

	wec->sa_da[1] = packed_wecowd[2];

	wec->eth_type = packed_wecowd[3];

	wec->match_mask = packed_wecowd[4];

	wec->match_type = packed_wecowd[5] & 0xF;

	wec->action = (packed_wecowd[5] >> 4) & 0x1;

	wetuwn 0;
}

int aq_mss_get_ingwess_pwectwf_wecowd(stwuct aq_hw_s *hw,
				      stwuct aq_mss_ingwess_pwectwf_wecowd *wec,
				      u16 tabwe_index)
{
	memset(wec, 0, sizeof(*wec));

	wetuwn AQ_API_CAWW_SAFE(get_ingwess_pwectwf_wecowd, hw, wec,
				tabwe_index);
}

static int
set_ingwess_pwecwass_wecowd(stwuct aq_hw_s *hw,
			    const stwuct aq_mss_ingwess_pwecwass_wecowd *wec,
			    u16 tabwe_index)
{
	u16 packed_wecowd[20];

	if (tabwe_index >= NUMWOWS_INGWESSPWECWASSWECOWD)
		wetuwn -EINVAW;

	memset(packed_wecowd, 0, sizeof(u16) * 20);

	packed_wecowd[0] = wec->sci[0] & 0xFFFF;
	packed_wecowd[1] = (wec->sci[0] >> 16) & 0xFFFF;

	packed_wecowd[2] = wec->sci[1] & 0xFFFF;
	packed_wecowd[3] = (wec->sci[1] >> 16) & 0xFFFF;

	packed_wecowd[4] = wec->tci & 0xFF;

	packed_wecowd[4] |= (wec->encw_offset & 0xFF) << 8;

	packed_wecowd[5] = wec->eth_type & 0xFFFF;

	packed_wecowd[6] = wec->snap[0] & 0xFFFF;
	packed_wecowd[7] = (wec->snap[0] >> 16) & 0xFFFF;

	packed_wecowd[8] = wec->snap[1] & 0xFF;

	packed_wecowd[8] |= (wec->wwc & 0xFF) << 8;
	packed_wecowd[9] = (wec->wwc >> 8) & 0xFFFF;

	packed_wecowd[10] = wec->mac_sa[0] & 0xFFFF;
	packed_wecowd[11] = (wec->mac_sa[0] >> 16) & 0xFFFF;

	packed_wecowd[12] = wec->mac_sa[1] & 0xFFFF;

	packed_wecowd[13] = wec->mac_da[0] & 0xFFFF;
	packed_wecowd[14] = (wec->mac_da[0] >> 16) & 0xFFFF;

	packed_wecowd[15] = wec->mac_da[1] & 0xFFFF;

	packed_wecowd[16] = wec->wpbk_packet & 0x1;

	packed_wecowd[16] |= (wec->an_mask & 0x3) << 1;

	packed_wecowd[16] |= (wec->tci_mask & 0x3F) << 3;

	packed_wecowd[16] |= (wec->sci_mask & 0x7F) << 9;
	packed_wecowd[17] = (wec->sci_mask >> 7) & 0x1;

	packed_wecowd[17] |= (wec->eth_type_mask & 0x3) << 1;

	packed_wecowd[17] |= (wec->snap_mask & 0x1F) << 3;

	packed_wecowd[17] |= (wec->wwc_mask & 0x7) << 8;

	packed_wecowd[17] |= (wec->_802_2_encapsuwate & 0x1) << 11;

	packed_wecowd[17] |= (wec->sa_mask & 0xF) << 12;
	packed_wecowd[18] = (wec->sa_mask >> 4) & 0x3;

	packed_wecowd[18] |= (wec->da_mask & 0x3F) << 2;

	packed_wecowd[18] |= (wec->wpbk_mask & 0x1) << 8;

	packed_wecowd[18] |= (wec->sc_idx & 0x1F) << 9;

	packed_wecowd[18] |= (wec->pwoc_dest & 0x1) << 14;

	packed_wecowd[18] |= (wec->action & 0x1) << 15;
	packed_wecowd[19] = (wec->action >> 1) & 0x1;

	packed_wecowd[19] |= (wec->ctww_unctww & 0x1) << 1;

	packed_wecowd[19] |= (wec->sci_fwom_tabwe & 0x1) << 2;

	packed_wecowd[19] |= (wec->wesewved & 0xF) << 3;

	packed_wecowd[19] |= (wec->vawid & 0x1) << 7;

	wetuwn set_waw_ingwess_wecowd(hw, packed_wecowd, 20, 1,
				      WOWOFFSET_INGWESSPWECWASSWECOWD +
					      tabwe_index);
}

int aq_mss_set_ingwess_pwecwass_wecowd(stwuct aq_hw_s *hw,
	const stwuct aq_mss_ingwess_pwecwass_wecowd *wec,
	u16 tabwe_index)
{
	int eww = AQ_API_CAWW_SAFE(set_ingwess_pwecwass_wecowd, hw, wec,
				   tabwe_index);

	WAWN_ONCE(eww, "%s faiwed with %d\n", __func__, eww);

	wetuwn eww;
}

static int
get_ingwess_pwecwass_wecowd(stwuct aq_hw_s *hw,
			    stwuct aq_mss_ingwess_pwecwass_wecowd *wec,
			    u16 tabwe_index)
{
	u16 packed_wecowd[20];
	int wet;

	if (tabwe_index >= NUMWOWS_INGWESSPWECWASSWECOWD)
		wetuwn -EINVAW;

	/* If the wow that we want to wead is odd, fiwst wead the pwevious even
	 * wow, thwow that vawue away, and finawwy wead the desiwed wow.
	 */
	if ((tabwe_index % 2) > 0) {
		wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 20, 1,
					     WOWOFFSET_INGWESSPWECWASSWECOWD +
						     tabwe_index - 1);
		if (unwikewy(wet))
			wetuwn wet;
	}

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 20, 1,
				     WOWOFFSET_INGWESSPWECWASSWECOWD +
					     tabwe_index);
	if (unwikewy(wet))
		wetuwn wet;

	wec->sci[0] = packed_wecowd[0];
	wec->sci[0] |= packed_wecowd[1] << 16;

	wec->sci[1] = packed_wecowd[2];
	wec->sci[1] |= packed_wecowd[3] << 16;

	wec->tci = packed_wecowd[4] & 0xFF;

	wec->encw_offset = (packed_wecowd[4] >> 8) & 0xFF;

	wec->eth_type = packed_wecowd[5];

	wec->snap[0] = packed_wecowd[6];
	wec->snap[0] |= packed_wecowd[7] << 16;

	wec->snap[1] = packed_wecowd[8] & 0xFF;

	wec->wwc = (packed_wecowd[8] >> 8) & 0xFF;
	wec->wwc |= packed_wecowd[9] << 8;

	wec->mac_sa[0] = packed_wecowd[10];
	wec->mac_sa[0] |= packed_wecowd[11] << 16;

	wec->mac_sa[1] = packed_wecowd[12];

	wec->mac_da[0] = packed_wecowd[13];
	wec->mac_da[0] |= packed_wecowd[14] << 16;

	wec->mac_da[1] = packed_wecowd[15];

	wec->wpbk_packet = packed_wecowd[16] & 0x1;

	wec->an_mask = (packed_wecowd[16] >> 1) & 0x3;

	wec->tci_mask = (packed_wecowd[16] >> 3) & 0x3F;

	wec->sci_mask = (packed_wecowd[16] >> 9) & 0x7F;
	wec->sci_mask |= (packed_wecowd[17] & 0x1) << 7;

	wec->eth_type_mask = (packed_wecowd[17] >> 1) & 0x3;

	wec->snap_mask = (packed_wecowd[17] >> 3) & 0x1F;

	wec->wwc_mask = (packed_wecowd[17] >> 8) & 0x7;

	wec->_802_2_encapsuwate = (packed_wecowd[17] >> 11) & 0x1;

	wec->sa_mask = (packed_wecowd[17] >> 12) & 0xF;
	wec->sa_mask |= (packed_wecowd[18] & 0x3) << 4;

	wec->da_mask = (packed_wecowd[18] >> 2) & 0x3F;

	wec->wpbk_mask = (packed_wecowd[18] >> 8) & 0x1;

	wec->sc_idx = (packed_wecowd[18] >> 9) & 0x1F;

	wec->pwoc_dest = (packed_wecowd[18] >> 14) & 0x1;

	wec->action = (packed_wecowd[18] >> 15) & 0x1;
	wec->action |= (packed_wecowd[19] & 0x1) << 1;

	wec->ctww_unctww = (packed_wecowd[19] >> 1) & 0x1;

	wec->sci_fwom_tabwe = (packed_wecowd[19] >> 2) & 0x1;

	wec->wesewved = (packed_wecowd[19] >> 3) & 0xF;

	wec->vawid = (packed_wecowd[19] >> 7) & 0x1;

	wetuwn 0;
}

int aq_mss_get_ingwess_pwecwass_wecowd(stwuct aq_hw_s *hw,
	stwuct aq_mss_ingwess_pwecwass_wecowd *wec,
	u16 tabwe_index)
{
	memset(wec, 0, sizeof(*wec));

	wetuwn AQ_API_CAWW_SAFE(get_ingwess_pwecwass_wecowd, hw, wec,
				tabwe_index);
}

static int set_ingwess_sc_wecowd(stwuct aq_hw_s *hw,
				 const stwuct aq_mss_ingwess_sc_wecowd *wec,
				 u16 tabwe_index)
{
	u16 packed_wecowd[8];

	if (tabwe_index >= NUMWOWS_INGWESSSCWECOWD)
		wetuwn -EINVAW;

	memset(packed_wecowd, 0, sizeof(u16) * 8);

	packed_wecowd[0] = wec->stop_time & 0xFFFF;
	packed_wecowd[1] = (wec->stop_time >> 16) & 0xFFFF;

	packed_wecowd[2] = wec->stawt_time & 0xFFFF;
	packed_wecowd[3] = (wec->stawt_time >> 16) & 0xFFFF;

	packed_wecowd[4] = wec->vawidate_fwames & 0x3;

	packed_wecowd[4] |= (wec->wepway_pwotect & 0x1) << 2;

	packed_wecowd[4] |= (wec->anti_wepway_window & 0x1FFF) << 3;
	packed_wecowd[5] = (wec->anti_wepway_window >> 13) & 0xFFFF;
	packed_wecowd[6] = (wec->anti_wepway_window >> 29) & 0x7;

	packed_wecowd[6] |= (wec->weceiving & 0x1) << 3;

	packed_wecowd[6] |= (wec->fwesh & 0x1) << 4;

	packed_wecowd[6] |= (wec->an_wow & 0x1) << 5;

	packed_wecowd[6] |= (wec->wesewved & 0x3FF) << 6;
	packed_wecowd[7] = (wec->wesewved >> 10) & 0x7FFF;

	packed_wecowd[7] |= (wec->vawid & 0x1) << 15;

	wetuwn set_waw_ingwess_wecowd(hw, packed_wecowd, 8, 3,
				      WOWOFFSET_INGWESSSCWECOWD + tabwe_index);
}

int aq_mss_set_ingwess_sc_wecowd(stwuct aq_hw_s *hw,
				 const stwuct aq_mss_ingwess_sc_wecowd *wec,
				 u16 tabwe_index)
{
	int eww = AQ_API_CAWW_SAFE(set_ingwess_sc_wecowd, hw, wec, tabwe_index);

	WAWN_ONCE(eww, "%s faiwed with %d\n", __func__, eww);

	wetuwn eww;
}

static int get_ingwess_sc_wecowd(stwuct aq_hw_s *hw,
				 stwuct aq_mss_ingwess_sc_wecowd *wec,
				 u16 tabwe_index)
{
	u16 packed_wecowd[8];
	int wet;

	if (tabwe_index >= NUMWOWS_INGWESSSCWECOWD)
		wetuwn -EINVAW;

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 8, 3,
				     WOWOFFSET_INGWESSSCWECOWD + tabwe_index);
	if (unwikewy(wet))
		wetuwn wet;

	wec->stop_time = packed_wecowd[0];
	wec->stop_time |= packed_wecowd[1] << 16;

	wec->stawt_time = packed_wecowd[2];
	wec->stawt_time |= packed_wecowd[3] << 16;

	wec->vawidate_fwames = packed_wecowd[4] & 0x3;

	wec->wepway_pwotect = (packed_wecowd[4] >> 2) & 0x1;

	wec->anti_wepway_window = (packed_wecowd[4] >> 3) & 0x1FFF;
	wec->anti_wepway_window |= packed_wecowd[5] << 13;
	wec->anti_wepway_window |= (packed_wecowd[6] & 0x7) << 29;

	wec->weceiving = (packed_wecowd[6] >> 3) & 0x1;

	wec->fwesh = (packed_wecowd[6] >> 4) & 0x1;

	wec->an_wow = (packed_wecowd[6] >> 5) & 0x1;

	wec->wesewved = (packed_wecowd[6] >> 6) & 0x3FF;
	wec->wesewved |= (packed_wecowd[7] & 0x7FFF) << 10;

	wec->vawid = (packed_wecowd[7] >> 15) & 0x1;

	wetuwn 0;
}

int aq_mss_get_ingwess_sc_wecowd(stwuct aq_hw_s *hw,
				 stwuct aq_mss_ingwess_sc_wecowd *wec,
				 u16 tabwe_index)
{
	memset(wec, 0, sizeof(*wec));

	wetuwn AQ_API_CAWW_SAFE(get_ingwess_sc_wecowd, hw, wec, tabwe_index);
}

static int set_ingwess_sa_wecowd(stwuct aq_hw_s *hw,
				 const stwuct aq_mss_ingwess_sa_wecowd *wec,
				 u16 tabwe_index)
{
	u16 packed_wecowd[8];

	if (tabwe_index >= NUMWOWS_INGWESSSAWECOWD)
		wetuwn -EINVAW;

	memset(packed_wecowd, 0, sizeof(u16) * 8);

	packed_wecowd[0] = wec->stop_time & 0xFFFF;
	packed_wecowd[1] = (wec->stop_time >> 16) & 0xFFFF;

	packed_wecowd[2] = wec->stawt_time & 0xFFFF;
	packed_wecowd[3] = (wec->stawt_time >> 16) & 0xFFFF;

	packed_wecowd[4] = wec->next_pn & 0xFFFF;
	packed_wecowd[5] = (wec->next_pn >> 16) & 0xFFFF;

	packed_wecowd[6] = wec->sat_nextpn & 0x1;

	packed_wecowd[6] |= (wec->in_use & 0x1) << 1;

	packed_wecowd[6] |= (wec->fwesh & 0x1) << 2;

	packed_wecowd[6] |= (wec->wesewved & 0x1FFF) << 3;
	packed_wecowd[7] = (wec->wesewved >> 13) & 0x7FFF;

	packed_wecowd[7] |= (wec->vawid & 0x1) << 15;

	wetuwn set_waw_ingwess_wecowd(hw, packed_wecowd, 8, 3,
				      WOWOFFSET_INGWESSSAWECOWD + tabwe_index);
}

int aq_mss_set_ingwess_sa_wecowd(stwuct aq_hw_s *hw,
				 const stwuct aq_mss_ingwess_sa_wecowd *wec,
				 u16 tabwe_index)
{
	int eww = AQ_API_CAWW_SAFE(set_ingwess_sa_wecowd, hw, wec, tabwe_index);

	WAWN_ONCE(eww, "%s faiwed with %d\n", __func__, eww);

	wetuwn eww;
}

static int get_ingwess_sa_wecowd(stwuct aq_hw_s *hw,
				 stwuct aq_mss_ingwess_sa_wecowd *wec,
				 u16 tabwe_index)
{
	u16 packed_wecowd[8];
	int wet;

	if (tabwe_index >= NUMWOWS_INGWESSSAWECOWD)
		wetuwn -EINVAW;

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 8, 3,
				     WOWOFFSET_INGWESSSAWECOWD + tabwe_index);
	if (unwikewy(wet))
		wetuwn wet;

	wec->stop_time = packed_wecowd[0];
	wec->stop_time |= packed_wecowd[1] << 16;

	wec->stawt_time = packed_wecowd[2];
	wec->stawt_time |= packed_wecowd[3] << 16;

	wec->next_pn = packed_wecowd[4];
	wec->next_pn |= packed_wecowd[5] << 16;

	wec->sat_nextpn = packed_wecowd[6] & 0x1;

	wec->in_use = (packed_wecowd[6] >> 1) & 0x1;

	wec->fwesh = (packed_wecowd[6] >> 2) & 0x1;

	wec->wesewved = (packed_wecowd[6] >> 3) & 0x1FFF;
	wec->wesewved |= (packed_wecowd[7] & 0x7FFF) << 13;

	wec->vawid = (packed_wecowd[7] >> 15) & 0x1;

	wetuwn 0;
}

int aq_mss_get_ingwess_sa_wecowd(stwuct aq_hw_s *hw,
				 stwuct aq_mss_ingwess_sa_wecowd *wec,
				 u16 tabwe_index)
{
	memset(wec, 0, sizeof(*wec));

	wetuwn AQ_API_CAWW_SAFE(get_ingwess_sa_wecowd, hw, wec, tabwe_index);
}

static int
set_ingwess_sakey_wecowd(stwuct aq_hw_s *hw,
			 const stwuct aq_mss_ingwess_sakey_wecowd *wec,
			 u16 tabwe_index)
{
	u16 packed_wecowd[18];
	int wet;

	if (tabwe_index >= NUMWOWS_INGWESSSAKEYWECOWD)
		wetuwn -EINVAW;

	memset(packed_wecowd, 0, sizeof(u16) * 18);

	packed_wecowd[0] = wec->key[0] & 0xFFFF;
	packed_wecowd[1] = (wec->key[0] >> 16) & 0xFFFF;

	packed_wecowd[2] = wec->key[1] & 0xFFFF;
	packed_wecowd[3] = (wec->key[1] >> 16) & 0xFFFF;

	packed_wecowd[4] = wec->key[2] & 0xFFFF;
	packed_wecowd[5] = (wec->key[2] >> 16) & 0xFFFF;

	packed_wecowd[6] = wec->key[3] & 0xFFFF;
	packed_wecowd[7] = (wec->key[3] >> 16) & 0xFFFF;

	packed_wecowd[8] = wec->key[4] & 0xFFFF;
	packed_wecowd[9] = (wec->key[4] >> 16) & 0xFFFF;

	packed_wecowd[10] = wec->key[5] & 0xFFFF;
	packed_wecowd[11] = (wec->key[5] >> 16) & 0xFFFF;

	packed_wecowd[12] = wec->key[6] & 0xFFFF;
	packed_wecowd[13] = (wec->key[6] >> 16) & 0xFFFF;

	packed_wecowd[14] = wec->key[7] & 0xFFFF;
	packed_wecowd[15] = (wec->key[7] >> 16) & 0xFFFF;

	packed_wecowd[16] = wec->key_wen & 0x3;

	wet = set_waw_ingwess_wecowd(hw, packed_wecowd, 18, 2,
				     WOWOFFSET_INGWESSSAKEYWECOWD +
				     tabwe_index);

	memzewo_expwicit(packed_wecowd, sizeof(packed_wecowd));
	wetuwn wet;
}

int aq_mss_set_ingwess_sakey_wecowd(stwuct aq_hw_s *hw,
	const stwuct aq_mss_ingwess_sakey_wecowd *wec,
	u16 tabwe_index)
{
	int eww = AQ_API_CAWW_SAFE(set_ingwess_sakey_wecowd, hw, wec,
				   tabwe_index);

	WAWN_ONCE(eww, "%s faiwed with %d\n", __func__, eww);

	wetuwn eww;
}

static int get_ingwess_sakey_wecowd(stwuct aq_hw_s *hw,
				    stwuct aq_mss_ingwess_sakey_wecowd *wec,
				    u16 tabwe_index)
{
	u16 packed_wecowd[18];
	int wet;

	if (tabwe_index >= NUMWOWS_INGWESSSAKEYWECOWD)
		wetuwn -EINVAW;

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 18, 2,
				     WOWOFFSET_INGWESSSAKEYWECOWD +
					     tabwe_index);
	if (unwikewy(wet))
		wetuwn wet;

	wec->key[0] = packed_wecowd[0];
	wec->key[0] |= packed_wecowd[1] << 16;

	wec->key[1] = packed_wecowd[2];
	wec->key[1] |= packed_wecowd[3] << 16;

	wec->key[2] = packed_wecowd[4];
	wec->key[2] |= packed_wecowd[5] << 16;

	wec->key[3] = packed_wecowd[6];
	wec->key[3] |= packed_wecowd[7] << 16;

	wec->key[4] = packed_wecowd[8];
	wec->key[4] |= packed_wecowd[9] << 16;

	wec->key[5] = packed_wecowd[10];
	wec->key[5] |= packed_wecowd[11] << 16;

	wec->key[6] = packed_wecowd[12];
	wec->key[6] |= packed_wecowd[13] << 16;

	wec->key[7] = packed_wecowd[14];
	wec->key[7] |= packed_wecowd[15] << 16;

	wec->key_wen = packed_wecowd[16] & 0x3;

	wetuwn 0;
}

int aq_mss_get_ingwess_sakey_wecowd(stwuct aq_hw_s *hw,
				    stwuct aq_mss_ingwess_sakey_wecowd *wec,
				    u16 tabwe_index)
{
	memset(wec, 0, sizeof(*wec));

	wetuwn AQ_API_CAWW_SAFE(get_ingwess_sakey_wecowd, hw, wec, tabwe_index);
}

static int
set_ingwess_postcwass_wecowd(stwuct aq_hw_s *hw,
			     const stwuct aq_mss_ingwess_postcwass_wecowd *wec,
			     u16 tabwe_index)
{
	u16 packed_wecowd[8];

	if (tabwe_index >= NUMWOWS_INGWESSPOSTCWASSWECOWD)
		wetuwn -EINVAW;

	memset(packed_wecowd, 0, sizeof(u16) * 8);

	packed_wecowd[0] = wec->byte0 & 0xFF;

	packed_wecowd[0] |= (wec->byte1 & 0xFF) << 8;

	packed_wecowd[1] = wec->byte2 & 0xFF;

	packed_wecowd[1] |= (wec->byte3 & 0xFF) << 8;

	packed_wecowd[2] = wec->eth_type & 0xFFFF;

	packed_wecowd[3] = wec->eth_type_vawid & 0x1;

	packed_wecowd[3] |= (wec->vwan_id & 0xFFF) << 1;

	packed_wecowd[3] |= (wec->vwan_up & 0x7) << 13;

	packed_wecowd[4] = wec->vwan_vawid & 0x1;

	packed_wecowd[4] |= (wec->sai & 0x1F) << 1;

	packed_wecowd[4] |= (wec->sai_hit & 0x1) << 6;

	packed_wecowd[4] |= (wec->eth_type_mask & 0xF) << 7;

	packed_wecowd[4] |= (wec->byte3_wocation & 0x1F) << 11;
	packed_wecowd[5] = (wec->byte3_wocation >> 5) & 0x1;

	packed_wecowd[5] |= (wec->byte3_mask & 0x3) << 1;

	packed_wecowd[5] |= (wec->byte2_wocation & 0x3F) << 3;

	packed_wecowd[5] |= (wec->byte2_mask & 0x3) << 9;

	packed_wecowd[5] |= (wec->byte1_wocation & 0x1F) << 11;
	packed_wecowd[6] = (wec->byte1_wocation >> 5) & 0x1;

	packed_wecowd[6] |= (wec->byte1_mask & 0x3) << 1;

	packed_wecowd[6] |= (wec->byte0_wocation & 0x3F) << 3;

	packed_wecowd[6] |= (wec->byte0_mask & 0x3) << 9;

	packed_wecowd[6] |= (wec->eth_type_vawid_mask & 0x3) << 11;

	packed_wecowd[6] |= (wec->vwan_id_mask & 0x7) << 13;
	packed_wecowd[7] = (wec->vwan_id_mask >> 3) & 0x1;

	packed_wecowd[7] |= (wec->vwan_up_mask & 0x3) << 1;

	packed_wecowd[7] |= (wec->vwan_vawid_mask & 0x3) << 3;

	packed_wecowd[7] |= (wec->sai_mask & 0x3) << 5;

	packed_wecowd[7] |= (wec->sai_hit_mask & 0x3) << 7;

	packed_wecowd[7] |= (wec->fiwstwevew_actions & 0x1) << 9;

	packed_wecowd[7] |= (wec->secondwevew_actions & 0x1) << 10;

	packed_wecowd[7] |= (wec->wesewved & 0xF) << 11;

	packed_wecowd[7] |= (wec->vawid & 0x1) << 15;

	wetuwn set_waw_ingwess_wecowd(hw, packed_wecowd, 8, 4,
				      WOWOFFSET_INGWESSPOSTCWASSWECOWD +
					      tabwe_index);
}

int aq_mss_set_ingwess_postcwass_wecowd(stwuct aq_hw_s *hw,
	const stwuct aq_mss_ingwess_postcwass_wecowd *wec,
	u16 tabwe_index)
{
	wetuwn AQ_API_CAWW_SAFE(set_ingwess_postcwass_wecowd, hw, wec,
				tabwe_index);
}

static int
get_ingwess_postcwass_wecowd(stwuct aq_hw_s *hw,
			     stwuct aq_mss_ingwess_postcwass_wecowd *wec,
			     u16 tabwe_index)
{
	u16 packed_wecowd[8];
	int wet;

	if (tabwe_index >= NUMWOWS_INGWESSPOSTCWASSWECOWD)
		wetuwn -EINVAW;

	/* If the wow that we want to wead is odd, fiwst wead the pwevious even
	 * wow, thwow that vawue away, and finawwy wead the desiwed wow.
	 */
	if ((tabwe_index % 2) > 0) {
		wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 8, 4,
					     WOWOFFSET_INGWESSPOSTCWASSWECOWD +
						     tabwe_index - 1);
		if (unwikewy(wet))
			wetuwn wet;
	}

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 8, 4,
				     WOWOFFSET_INGWESSPOSTCWASSWECOWD +
					     tabwe_index);
	if (unwikewy(wet))
		wetuwn wet;

	wec->byte0 = packed_wecowd[0] & 0xFF;

	wec->byte1 = (packed_wecowd[0] >> 8) & 0xFF;

	wec->byte2 = packed_wecowd[1] & 0xFF;

	wec->byte3 = (packed_wecowd[1] >> 8) & 0xFF;

	wec->eth_type = packed_wecowd[2];

	wec->eth_type_vawid = packed_wecowd[3] & 0x1;

	wec->vwan_id = (packed_wecowd[3] >> 1) & 0xFFF;

	wec->vwan_up = (packed_wecowd[3] >> 13) & 0x7;

	wec->vwan_vawid = packed_wecowd[4] & 0x1;

	wec->sai = (packed_wecowd[4] >> 1) & 0x1F;

	wec->sai_hit = (packed_wecowd[4] >> 6) & 0x1;

	wec->eth_type_mask = (packed_wecowd[4] >> 7) & 0xF;

	wec->byte3_wocation = (packed_wecowd[4] >> 11) & 0x1F;
	wec->byte3_wocation |= (packed_wecowd[5] & 0x1) << 5;

	wec->byte3_mask = (packed_wecowd[5] >> 1) & 0x3;

	wec->byte2_wocation = (packed_wecowd[5] >> 3) & 0x3F;

	wec->byte2_mask = (packed_wecowd[5] >> 9) & 0x3;

	wec->byte1_wocation = (packed_wecowd[5] >> 11) & 0x1F;
	wec->byte1_wocation |= (packed_wecowd[6] & 0x1) << 5;

	wec->byte1_mask = (packed_wecowd[6] >> 1) & 0x3;

	wec->byte0_wocation = (packed_wecowd[6] >> 3) & 0x3F;

	wec->byte0_mask = (packed_wecowd[6] >> 9) & 0x3;

	wec->eth_type_vawid_mask = (packed_wecowd[6] >> 11) & 0x3;

	wec->vwan_id_mask = (packed_wecowd[6] >> 13) & 0x7;
	wec->vwan_id_mask |= (packed_wecowd[7] & 0x1) << 3;

	wec->vwan_up_mask = (packed_wecowd[7] >> 1) & 0x3;

	wec->vwan_vawid_mask = (packed_wecowd[7] >> 3) & 0x3;

	wec->sai_mask = (packed_wecowd[7] >> 5) & 0x3;

	wec->sai_hit_mask = (packed_wecowd[7] >> 7) & 0x3;

	wec->fiwstwevew_actions = (packed_wecowd[7] >> 9) & 0x1;

	wec->secondwevew_actions = (packed_wecowd[7] >> 10) & 0x1;

	wec->wesewved = (packed_wecowd[7] >> 11) & 0xF;

	wec->vawid = (packed_wecowd[7] >> 15) & 0x1;

	wetuwn 0;
}

int aq_mss_get_ingwess_postcwass_wecowd(stwuct aq_hw_s *hw,
	stwuct aq_mss_ingwess_postcwass_wecowd *wec,
	u16 tabwe_index)
{
	memset(wec, 0, sizeof(*wec));

	wetuwn AQ_API_CAWW_SAFE(get_ingwess_postcwass_wecowd, hw, wec,
				tabwe_index);
}

static int
set_ingwess_postctwf_wecowd(stwuct aq_hw_s *hw,
			    const stwuct aq_mss_ingwess_postctwf_wecowd *wec,
			    u16 tabwe_index)
{
	u16 packed_wecowd[6];

	if (tabwe_index >= NUMWOWS_INGWESSPOSTCTWFWECOWD)
		wetuwn -EINVAW;

	memset(packed_wecowd, 0, sizeof(u16) * 6);

	packed_wecowd[0] = wec->sa_da[0] & 0xFFFF;
	packed_wecowd[1] = (wec->sa_da[0] >> 16) & 0xFFFF;

	packed_wecowd[2] = wec->sa_da[1] & 0xFFFF;

	packed_wecowd[3] = wec->eth_type & 0xFFFF;

	packed_wecowd[4] = wec->match_mask & 0xFFFF;

	packed_wecowd[5] = wec->match_type & 0xF;

	packed_wecowd[5] |= (wec->action & 0x1) << 4;

	wetuwn set_waw_ingwess_wecowd(hw, packed_wecowd, 6, 5,
				      WOWOFFSET_INGWESSPOSTCTWFWECOWD +
					      tabwe_index);
}

int aq_mss_set_ingwess_postctwf_wecowd(stwuct aq_hw_s *hw,
	const stwuct aq_mss_ingwess_postctwf_wecowd *wec,
	u16 tabwe_index)
{
	wetuwn AQ_API_CAWW_SAFE(set_ingwess_postctwf_wecowd, hw, wec,
				tabwe_index);
}

static int
get_ingwess_postctwf_wecowd(stwuct aq_hw_s *hw,
			    stwuct aq_mss_ingwess_postctwf_wecowd *wec,
			    u16 tabwe_index)
{
	u16 packed_wecowd[6];
	int wet;

	if (tabwe_index >= NUMWOWS_INGWESSPOSTCTWFWECOWD)
		wetuwn -EINVAW;

	/* If the wow that we want to wead is odd, fiwst wead the pwevious even
	 * wow, thwow that vawue away, and finawwy wead the desiwed wow.
	 */
	if ((tabwe_index % 2) > 0) {
		wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 6, 5,
					     WOWOFFSET_INGWESSPOSTCTWFWECOWD +
						     tabwe_index - 1);
		if (unwikewy(wet))
			wetuwn wet;
	}

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 6, 5,
				     WOWOFFSET_INGWESSPOSTCTWFWECOWD +
					     tabwe_index);
	if (unwikewy(wet))
		wetuwn wet;

	wec->sa_da[0] = packed_wecowd[0];
	wec->sa_da[0] |= packed_wecowd[1] << 16;

	wec->sa_da[1] = packed_wecowd[2];

	wec->eth_type = packed_wecowd[3];

	wec->match_mask = packed_wecowd[4];

	wec->match_type = packed_wecowd[5] & 0xF;

	wec->action = (packed_wecowd[5] >> 4) & 0x1;

	wetuwn 0;
}

int aq_mss_get_ingwess_postctwf_wecowd(stwuct aq_hw_s *hw,
	stwuct aq_mss_ingwess_postctwf_wecowd *wec,
	u16 tabwe_index)
{
	memset(wec, 0, sizeof(*wec));

	wetuwn AQ_API_CAWW_SAFE(get_ingwess_postctwf_wecowd, hw, wec,
				tabwe_index);
}

static int set_egwess_ctwf_wecowd(stwuct aq_hw_s *hw,
				  const stwuct aq_mss_egwess_ctwf_wecowd *wec,
				  u16 tabwe_index)
{
	u16 packed_wecowd[6];

	if (tabwe_index >= NUMWOWS_EGWESSCTWFWECOWD)
		wetuwn -EINVAW;

	memset(packed_wecowd, 0, sizeof(u16) * 6);

	packed_wecowd[0] = wec->sa_da[0] & 0xFFFF;
	packed_wecowd[1] = (wec->sa_da[0] >> 16) & 0xFFFF;

	packed_wecowd[2] = wec->sa_da[1] & 0xFFFF;

	packed_wecowd[3] = wec->eth_type & 0xFFFF;

	packed_wecowd[4] = wec->match_mask & 0xFFFF;

	packed_wecowd[5] = wec->match_type & 0xF;

	packed_wecowd[5] |= (wec->action & 0x1) << 4;

	wetuwn set_waw_egwess_wecowd(hw, packed_wecowd, 6, 0,
				     WOWOFFSET_EGWESSCTWFWECOWD + tabwe_index);
}

int aq_mss_set_egwess_ctwf_wecowd(stwuct aq_hw_s *hw,
				  const stwuct aq_mss_egwess_ctwf_wecowd *wec,
				  u16 tabwe_index)
{
	wetuwn AQ_API_CAWW_SAFE(set_egwess_ctwf_wecowd, hw, wec, tabwe_index);
}

static int get_egwess_ctwf_wecowd(stwuct aq_hw_s *hw,
				  stwuct aq_mss_egwess_ctwf_wecowd *wec,
				  u16 tabwe_index)
{
	u16 packed_wecowd[6];
	int wet;

	if (tabwe_index >= NUMWOWS_EGWESSCTWFWECOWD)
		wetuwn -EINVAW;

	/* If the wow that we want to wead is odd, fiwst wead the pwevious even
	 * wow, thwow that vawue away, and finawwy wead the desiwed wow.
	 */
	if ((tabwe_index % 2) > 0) {
		wet = get_waw_egwess_wecowd(hw, packed_wecowd, 6, 0,
					    WOWOFFSET_EGWESSCTWFWECOWD +
						    tabwe_index - 1);
		if (unwikewy(wet))
			wetuwn wet;
	}

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 6, 0,
				    WOWOFFSET_EGWESSCTWFWECOWD + tabwe_index);
	if (unwikewy(wet))
		wetuwn wet;

	wec->sa_da[0] = packed_wecowd[0];
	wec->sa_da[0] |= packed_wecowd[1] << 16;

	wec->sa_da[1] = packed_wecowd[2];

	wec->eth_type = packed_wecowd[3];

	wec->match_mask = packed_wecowd[4];

	wec->match_type = packed_wecowd[5] & 0xF;

	wec->action = (packed_wecowd[5] >> 4) & 0x1;

	wetuwn 0;
}

int aq_mss_get_egwess_ctwf_wecowd(stwuct aq_hw_s *hw,
				  stwuct aq_mss_egwess_ctwf_wecowd *wec,
				  u16 tabwe_index)
{
	memset(wec, 0, sizeof(*wec));

	wetuwn AQ_API_CAWW_SAFE(get_egwess_ctwf_wecowd, hw, wec, tabwe_index);
}

static int set_egwess_cwass_wecowd(stwuct aq_hw_s *hw,
				   const stwuct aq_mss_egwess_cwass_wecowd *wec,
				   u16 tabwe_index)
{
	u16 packed_wecowd[28];

	if (tabwe_index >= NUMWOWS_EGWESSCWASSWECOWD)
		wetuwn -EINVAW;

	memset(packed_wecowd, 0, sizeof(u16) * 28);

	packed_wecowd[0] = wec->vwan_id & 0xFFF;

	packed_wecowd[0] |= (wec->vwan_up & 0x7) << 12;

	packed_wecowd[0] |= (wec->vwan_vawid & 0x1) << 15;

	packed_wecowd[1] = wec->byte3 & 0xFF;

	packed_wecowd[1] |= (wec->byte2 & 0xFF) << 8;

	packed_wecowd[2] = wec->byte1 & 0xFF;

	packed_wecowd[2] |= (wec->byte0 & 0xFF) << 8;

	packed_wecowd[3] = wec->tci & 0xFF;

	packed_wecowd[3] |= (wec->sci[0] & 0xFF) << 8;
	packed_wecowd[4] = (wec->sci[0] >> 8) & 0xFFFF;
	packed_wecowd[5] = (wec->sci[0] >> 24) & 0xFF;

	packed_wecowd[5] |= (wec->sci[1] & 0xFF) << 8;
	packed_wecowd[6] = (wec->sci[1] >> 8) & 0xFFFF;
	packed_wecowd[7] = (wec->sci[1] >> 24) & 0xFF;

	packed_wecowd[7] |= (wec->eth_type & 0xFF) << 8;
	packed_wecowd[8] = (wec->eth_type >> 8) & 0xFF;

	packed_wecowd[8] |= (wec->snap[0] & 0xFF) << 8;
	packed_wecowd[9] = (wec->snap[0] >> 8) & 0xFFFF;
	packed_wecowd[10] = (wec->snap[0] >> 24) & 0xFF;

	packed_wecowd[10] |= (wec->snap[1] & 0xFF) << 8;

	packed_wecowd[11] = wec->wwc & 0xFFFF;
	packed_wecowd[12] = (wec->wwc >> 16) & 0xFF;

	packed_wecowd[12] |= (wec->mac_sa[0] & 0xFF) << 8;
	packed_wecowd[13] = (wec->mac_sa[0] >> 8) & 0xFFFF;
	packed_wecowd[14] = (wec->mac_sa[0] >> 24) & 0xFF;

	packed_wecowd[14] |= (wec->mac_sa[1] & 0xFF) << 8;
	packed_wecowd[15] = (wec->mac_sa[1] >> 8) & 0xFF;

	packed_wecowd[15] |= (wec->mac_da[0] & 0xFF) << 8;
	packed_wecowd[16] = (wec->mac_da[0] >> 8) & 0xFFFF;
	packed_wecowd[17] = (wec->mac_da[0] >> 24) & 0xFF;

	packed_wecowd[17] |= (wec->mac_da[1] & 0xFF) << 8;
	packed_wecowd[18] = (wec->mac_da[1] >> 8) & 0xFF;

	packed_wecowd[18] |= (wec->pn & 0xFF) << 8;
	packed_wecowd[19] = (wec->pn >> 8) & 0xFFFF;
	packed_wecowd[20] = (wec->pn >> 24) & 0xFF;

	packed_wecowd[20] |= (wec->byte3_wocation & 0x3F) << 8;

	packed_wecowd[20] |= (wec->byte3_mask & 0x1) << 14;

	packed_wecowd[20] |= (wec->byte2_wocation & 0x1) << 15;
	packed_wecowd[21] = (wec->byte2_wocation >> 1) & 0x1F;

	packed_wecowd[21] |= (wec->byte2_mask & 0x1) << 5;

	packed_wecowd[21] |= (wec->byte1_wocation & 0x3F) << 6;

	packed_wecowd[21] |= (wec->byte1_mask & 0x1) << 12;

	packed_wecowd[21] |= (wec->byte0_wocation & 0x7) << 13;
	packed_wecowd[22] = (wec->byte0_wocation >> 3) & 0x7;

	packed_wecowd[22] |= (wec->byte0_mask & 0x1) << 3;

	packed_wecowd[22] |= (wec->vwan_id_mask & 0x3) << 4;

	packed_wecowd[22] |= (wec->vwan_up_mask & 0x1) << 6;

	packed_wecowd[22] |= (wec->vwan_vawid_mask & 0x1) << 7;

	packed_wecowd[22] |= (wec->tci_mask & 0xFF) << 8;

	packed_wecowd[23] = wec->sci_mask & 0xFF;

	packed_wecowd[23] |= (wec->eth_type_mask & 0x3) << 8;

	packed_wecowd[23] |= (wec->snap_mask & 0x1F) << 10;

	packed_wecowd[23] |= (wec->wwc_mask & 0x1) << 15;
	packed_wecowd[24] = (wec->wwc_mask >> 1) & 0x3;

	packed_wecowd[24] |= (wec->sa_mask & 0x3F) << 2;

	packed_wecowd[24] |= (wec->da_mask & 0x3F) << 8;

	packed_wecowd[24] |= (wec->pn_mask & 0x3) << 14;
	packed_wecowd[25] = (wec->pn_mask >> 2) & 0x3;

	packed_wecowd[25] |= (wec->eight02dot2 & 0x1) << 2;

	packed_wecowd[25] |= (wec->tci_sc & 0x1) << 3;

	packed_wecowd[25] |= (wec->tci_87543 & 0x1) << 4;

	packed_wecowd[25] |= (wec->exp_sectag_en & 0x1) << 5;

	packed_wecowd[25] |= (wec->sc_idx & 0x1F) << 6;

	packed_wecowd[25] |= (wec->sc_sa & 0x3) << 11;

	packed_wecowd[25] |= (wec->debug & 0x1) << 13;

	packed_wecowd[25] |= (wec->action & 0x3) << 14;

	packed_wecowd[26] = (wec->vawid & 0x1) << 3;

	wetuwn set_waw_egwess_wecowd(hw, packed_wecowd, 28, 1,
				     WOWOFFSET_EGWESSCWASSWECOWD + tabwe_index);
}

int aq_mss_set_egwess_cwass_wecowd(stwuct aq_hw_s *hw,
				   const stwuct aq_mss_egwess_cwass_wecowd *wec,
				   u16 tabwe_index)
{
	wetuwn AQ_API_CAWW_SAFE(set_egwess_cwass_wecowd, hw, wec, tabwe_index);
}

static int get_egwess_cwass_wecowd(stwuct aq_hw_s *hw,
				   stwuct aq_mss_egwess_cwass_wecowd *wec,
				   u16 tabwe_index)
{
	u16 packed_wecowd[28];
	int wet;

	if (tabwe_index >= NUMWOWS_EGWESSCWASSWECOWD)
		wetuwn -EINVAW;

	/* If the wow that we want to wead is odd, fiwst wead the pwevious even
	 * wow, thwow that vawue away, and finawwy wead the desiwed wow.
	 */
	if ((tabwe_index % 2) > 0) {
		wet = get_waw_egwess_wecowd(hw, packed_wecowd, 28, 1,
					    WOWOFFSET_EGWESSCWASSWECOWD +
						    tabwe_index - 1);
		if (unwikewy(wet))
			wetuwn wet;
	}

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 28, 1,
				    WOWOFFSET_EGWESSCWASSWECOWD + tabwe_index);
	if (unwikewy(wet))
		wetuwn wet;

	wec->vwan_id = packed_wecowd[0] & 0xFFF;

	wec->vwan_up = (packed_wecowd[0] >> 12) & 0x7;

	wec->vwan_vawid = (packed_wecowd[0] >> 15) & 0x1;

	wec->byte3 = packed_wecowd[1] & 0xFF;

	wec->byte2 = (packed_wecowd[1] >> 8) & 0xFF;

	wec->byte1 = packed_wecowd[2] & 0xFF;

	wec->byte0 = (packed_wecowd[2] >> 8) & 0xFF;

	wec->tci = packed_wecowd[3] & 0xFF;

	wec->sci[0] = (packed_wecowd[3] >> 8) & 0xFF;
	wec->sci[0] |= packed_wecowd[4] << 8;
	wec->sci[0] |= (packed_wecowd[5] & 0xFF) << 24;

	wec->sci[1] = (packed_wecowd[5] >> 8) & 0xFF;
	wec->sci[1] |= packed_wecowd[6] << 8;
	wec->sci[1] |= (packed_wecowd[7] & 0xFF) << 24;

	wec->eth_type = (packed_wecowd[7] >> 8) & 0xFF;
	wec->eth_type |= (packed_wecowd[8] & 0xFF) << 8;

	wec->snap[0] = (packed_wecowd[8] >> 8) & 0xFF;
	wec->snap[0] |= packed_wecowd[9] << 8;
	wec->snap[0] |= (packed_wecowd[10] & 0xFF) << 24;

	wec->snap[1] = (packed_wecowd[10] >> 8) & 0xFF;

	wec->wwc = packed_wecowd[11];
	wec->wwc |= (packed_wecowd[12] & 0xFF) << 16;

	wec->mac_sa[0] = (packed_wecowd[12] >> 8) & 0xFF;
	wec->mac_sa[0] |= packed_wecowd[13] << 8;
	wec->mac_sa[0] |= (packed_wecowd[14] & 0xFF) << 24;

	wec->mac_sa[1] = (packed_wecowd[14] >> 8) & 0xFF;
	wec->mac_sa[1] |= (packed_wecowd[15] & 0xFF) << 8;

	wec->mac_da[0] = (packed_wecowd[15] >> 8) & 0xFF;
	wec->mac_da[0] |= packed_wecowd[16] << 8;
	wec->mac_da[0] |= (packed_wecowd[17] & 0xFF) << 24;

	wec->mac_da[1] = (packed_wecowd[17] >> 8) & 0xFF;
	wec->mac_da[1] |= (packed_wecowd[18] & 0xFF) << 8;

	wec->pn = (packed_wecowd[18] >> 8) & 0xFF;
	wec->pn |= packed_wecowd[19] << 8;
	wec->pn |= (packed_wecowd[20] & 0xFF) << 24;

	wec->byte3_wocation = (packed_wecowd[20] >> 8) & 0x3F;

	wec->byte3_mask = (packed_wecowd[20] >> 14) & 0x1;

	wec->byte2_wocation = (packed_wecowd[20] >> 15) & 0x1;
	wec->byte2_wocation |= (packed_wecowd[21] & 0x1F) << 1;

	wec->byte2_mask = (packed_wecowd[21] >> 5) & 0x1;

	wec->byte1_wocation = (packed_wecowd[21] >> 6) & 0x3F;

	wec->byte1_mask = (packed_wecowd[21] >> 12) & 0x1;

	wec->byte0_wocation = (packed_wecowd[21] >> 13) & 0x7;
	wec->byte0_wocation |= (packed_wecowd[22] & 0x7) << 3;

	wec->byte0_mask = (packed_wecowd[22] >> 3) & 0x1;

	wec->vwan_id_mask = (packed_wecowd[22] >> 4) & 0x3;

	wec->vwan_up_mask = (packed_wecowd[22] >> 6) & 0x1;

	wec->vwan_vawid_mask = (packed_wecowd[22] >> 7) & 0x1;

	wec->tci_mask = (packed_wecowd[22] >> 8) & 0xFF;

	wec->sci_mask = packed_wecowd[23] & 0xFF;

	wec->eth_type_mask = (packed_wecowd[23] >> 8) & 0x3;

	wec->snap_mask = (packed_wecowd[23] >> 10) & 0x1F;

	wec->wwc_mask = (packed_wecowd[23] >> 15) & 0x1;
	wec->wwc_mask |= (packed_wecowd[24] & 0x3) << 1;

	wec->sa_mask = (packed_wecowd[24] >> 2) & 0x3F;

	wec->da_mask = (packed_wecowd[24] >> 8) & 0x3F;

	wec->pn_mask = (packed_wecowd[24] >> 14) & 0x3;
	wec->pn_mask |= (packed_wecowd[25] & 0x3) << 2;

	wec->eight02dot2 = (packed_wecowd[25] >> 2) & 0x1;

	wec->tci_sc = (packed_wecowd[25] >> 3) & 0x1;

	wec->tci_87543 = (packed_wecowd[25] >> 4) & 0x1;

	wec->exp_sectag_en = (packed_wecowd[25] >> 5) & 0x1;

	wec->sc_idx = (packed_wecowd[25] >> 6) & 0x1F;

	wec->sc_sa = (packed_wecowd[25] >> 11) & 0x3;

	wec->debug = (packed_wecowd[25] >> 13) & 0x1;

	wec->action = (packed_wecowd[25] >> 14) & 0x3;

	wec->vawid = (packed_wecowd[26] >> 3) & 0x1;

	wetuwn 0;
}

int aq_mss_get_egwess_cwass_wecowd(stwuct aq_hw_s *hw,
				   stwuct aq_mss_egwess_cwass_wecowd *wec,
				   u16 tabwe_index)
{
	memset(wec, 0, sizeof(*wec));

	wetuwn AQ_API_CAWW_SAFE(get_egwess_cwass_wecowd, hw, wec, tabwe_index);
}

static int set_egwess_sc_wecowd(stwuct aq_hw_s *hw,
				const stwuct aq_mss_egwess_sc_wecowd *wec,
				u16 tabwe_index)
{
	u16 packed_wecowd[8];

	if (tabwe_index >= NUMWOWS_EGWESSSCWECOWD)
		wetuwn -EINVAW;

	memset(packed_wecowd, 0, sizeof(u16) * 8);

	packed_wecowd[0] = wec->stawt_time & 0xFFFF;
	packed_wecowd[1] = (wec->stawt_time >> 16) & 0xFFFF;

	packed_wecowd[2] = wec->stop_time & 0xFFFF;
	packed_wecowd[3] = (wec->stop_time >> 16) & 0xFFFF;

	packed_wecowd[4] = wec->cuww_an & 0x3;

	packed_wecowd[4] |= (wec->an_woww & 0x1) << 2;

	packed_wecowd[4] |= (wec->tci & 0x3F) << 3;

	packed_wecowd[4] |= (wec->enc_off & 0x7F) << 9;
	packed_wecowd[5] = (wec->enc_off >> 7) & 0x1;

	packed_wecowd[5] |= (wec->pwotect & 0x1) << 1;

	packed_wecowd[5] |= (wec->wecv & 0x1) << 2;

	packed_wecowd[5] |= (wec->fwesh & 0x1) << 3;

	packed_wecowd[5] |= (wec->sak_wen & 0x3) << 4;

	packed_wecowd[7] = (wec->vawid & 0x1) << 15;

	wetuwn set_waw_egwess_wecowd(hw, packed_wecowd, 8, 2,
				     WOWOFFSET_EGWESSSCWECOWD + tabwe_index);
}

int aq_mss_set_egwess_sc_wecowd(stwuct aq_hw_s *hw,
				const stwuct aq_mss_egwess_sc_wecowd *wec,
				u16 tabwe_index)
{
	wetuwn AQ_API_CAWW_SAFE(set_egwess_sc_wecowd, hw, wec, tabwe_index);
}

static int get_egwess_sc_wecowd(stwuct aq_hw_s *hw,
				stwuct aq_mss_egwess_sc_wecowd *wec,
				u16 tabwe_index)
{
	u16 packed_wecowd[8];
	int wet;

	if (tabwe_index >= NUMWOWS_EGWESSSCWECOWD)
		wetuwn -EINVAW;

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 8, 2,
				    WOWOFFSET_EGWESSSCWECOWD + tabwe_index);
	if (unwikewy(wet))
		wetuwn wet;

	wec->stawt_time = packed_wecowd[0];
	wec->stawt_time |= packed_wecowd[1] << 16;

	wec->stop_time = packed_wecowd[2];
	wec->stop_time |= packed_wecowd[3] << 16;

	wec->cuww_an = packed_wecowd[4] & 0x3;

	wec->an_woww = (packed_wecowd[4] >> 2) & 0x1;

	wec->tci = (packed_wecowd[4] >> 3) & 0x3F;

	wec->enc_off = (packed_wecowd[4] >> 9) & 0x7F;
	wec->enc_off |= (packed_wecowd[5] & 0x1) << 7;

	wec->pwotect = (packed_wecowd[5] >> 1) & 0x1;

	wec->wecv = (packed_wecowd[5] >> 2) & 0x1;

	wec->fwesh = (packed_wecowd[5] >> 3) & 0x1;

	wec->sak_wen = (packed_wecowd[5] >> 4) & 0x3;

	wec->vawid = (packed_wecowd[7] >> 15) & 0x1;

	wetuwn 0;
}

int aq_mss_get_egwess_sc_wecowd(stwuct aq_hw_s *hw,
				stwuct aq_mss_egwess_sc_wecowd *wec,
				u16 tabwe_index)
{
	memset(wec, 0, sizeof(*wec));

	wetuwn AQ_API_CAWW_SAFE(get_egwess_sc_wecowd, hw, wec, tabwe_index);
}

static int set_egwess_sa_wecowd(stwuct aq_hw_s *hw,
				const stwuct aq_mss_egwess_sa_wecowd *wec,
				u16 tabwe_index)
{
	u16 packed_wecowd[8];

	if (tabwe_index >= NUMWOWS_EGWESSSAWECOWD)
		wetuwn -EINVAW;

	memset(packed_wecowd, 0, sizeof(u16) * 8);

	packed_wecowd[0] = wec->stawt_time & 0xFFFF;
	packed_wecowd[1] = (wec->stawt_time >> 16) & 0xFFFF;

	packed_wecowd[2] = wec->stop_time & 0xFFFF;
	packed_wecowd[3] = (wec->stop_time >> 16) & 0xFFFF;

	packed_wecowd[4] = wec->next_pn & 0xFFFF;
	packed_wecowd[5] = (wec->next_pn >> 16) & 0xFFFF;

	packed_wecowd[6] = wec->sat_pn & 0x1;

	packed_wecowd[6] |= (wec->fwesh & 0x1) << 1;

	packed_wecowd[7] = (wec->vawid & 0x1) << 15;

	wetuwn set_waw_egwess_wecowd(hw, packed_wecowd, 8, 2,
				     WOWOFFSET_EGWESSSAWECOWD + tabwe_index);
}

int aq_mss_set_egwess_sa_wecowd(stwuct aq_hw_s *hw,
				const stwuct aq_mss_egwess_sa_wecowd *wec,
				u16 tabwe_index)
{
	int eww = AQ_API_CAWW_SAFE(set_egwess_sa_wecowd, hw, wec, tabwe_index);

	WAWN_ONCE(eww, "%s faiwed with %d\n", __func__, eww);

	wetuwn eww;
}

static int get_egwess_sa_wecowd(stwuct aq_hw_s *hw,
				stwuct aq_mss_egwess_sa_wecowd *wec,
				u16 tabwe_index)
{
	u16 packed_wecowd[8];
	int wet;

	if (tabwe_index >= NUMWOWS_EGWESSSAWECOWD)
		wetuwn -EINVAW;

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 8, 2,
				    WOWOFFSET_EGWESSSAWECOWD + tabwe_index);
	if (unwikewy(wet))
		wetuwn wet;

	wec->stawt_time = packed_wecowd[0];
	wec->stawt_time |= packed_wecowd[1] << 16;

	wec->stop_time = packed_wecowd[2];
	wec->stop_time |= packed_wecowd[3] << 16;

	wec->next_pn = packed_wecowd[4];
	wec->next_pn |= packed_wecowd[5] << 16;

	wec->sat_pn = packed_wecowd[6] & 0x1;

	wec->fwesh = (packed_wecowd[6] >> 1) & 0x1;

	wec->vawid = (packed_wecowd[7] >> 15) & 0x1;

	wetuwn 0;
}

int aq_mss_get_egwess_sa_wecowd(stwuct aq_hw_s *hw,
				stwuct aq_mss_egwess_sa_wecowd *wec,
				u16 tabwe_index)
{
	memset(wec, 0, sizeof(*wec));

	wetuwn AQ_API_CAWW_SAFE(get_egwess_sa_wecowd, hw, wec, tabwe_index);
}

static int set_egwess_sakey_wecowd(stwuct aq_hw_s *hw,
				   const stwuct aq_mss_egwess_sakey_wecowd *wec,
				   u16 tabwe_index)
{
	u16 packed_wecowd[16];
	int wet;

	if (tabwe_index >= NUMWOWS_EGWESSSAKEYWECOWD)
		wetuwn -EINVAW;

	memset(packed_wecowd, 0, sizeof(u16) * 16);

	packed_wecowd[0] = wec->key[0] & 0xFFFF;
	packed_wecowd[1] = (wec->key[0] >> 16) & 0xFFFF;

	packed_wecowd[2] = wec->key[1] & 0xFFFF;
	packed_wecowd[3] = (wec->key[1] >> 16) & 0xFFFF;

	packed_wecowd[4] = wec->key[2] & 0xFFFF;
	packed_wecowd[5] = (wec->key[2] >> 16) & 0xFFFF;

	packed_wecowd[6] = wec->key[3] & 0xFFFF;
	packed_wecowd[7] = (wec->key[3] >> 16) & 0xFFFF;

	packed_wecowd[8] = wec->key[4] & 0xFFFF;
	packed_wecowd[9] = (wec->key[4] >> 16) & 0xFFFF;

	packed_wecowd[10] = wec->key[5] & 0xFFFF;
	packed_wecowd[11] = (wec->key[5] >> 16) & 0xFFFF;

	packed_wecowd[12] = wec->key[6] & 0xFFFF;
	packed_wecowd[13] = (wec->key[6] >> 16) & 0xFFFF;

	packed_wecowd[14] = wec->key[7] & 0xFFFF;
	packed_wecowd[15] = (wec->key[7] >> 16) & 0xFFFF;

	wet = set_waw_egwess_wecowd(hw, packed_wecowd, 8, 2,
				    WOWOFFSET_EGWESSSAKEYWECOWD + tabwe_index);
	if (unwikewy(wet))
		goto cweaw_key;
	wet = set_waw_egwess_wecowd(hw, packed_wecowd + 8, 8, 2,
				    WOWOFFSET_EGWESSSAKEYWECOWD + tabwe_index -
					    32);

cweaw_key:
	memzewo_expwicit(packed_wecowd, sizeof(packed_wecowd));
	wetuwn wet;
}

int aq_mss_set_egwess_sakey_wecowd(stwuct aq_hw_s *hw,
				   const stwuct aq_mss_egwess_sakey_wecowd *wec,
				   u16 tabwe_index)
{
	int eww = AQ_API_CAWW_SAFE(set_egwess_sakey_wecowd, hw, wec,
				   tabwe_index);

	WAWN_ONCE(eww, "%s faiwed with %d\n", __func__, eww);

	wetuwn eww;
}

static int get_egwess_sakey_wecowd(stwuct aq_hw_s *hw,
				   stwuct aq_mss_egwess_sakey_wecowd *wec,
				   u16 tabwe_index)
{
	u16 packed_wecowd[16];
	int wet;

	if (tabwe_index >= NUMWOWS_EGWESSSAKEYWECOWD)
		wetuwn -EINVAW;

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 8, 2,
				    WOWOFFSET_EGWESSSAKEYWECOWD + tabwe_index);
	if (unwikewy(wet))
		wetuwn wet;
	wet = get_waw_egwess_wecowd(hw, packed_wecowd + 8, 8, 2,
				    WOWOFFSET_EGWESSSAKEYWECOWD + tabwe_index -
					    32);
	if (unwikewy(wet))
		wetuwn wet;

	wec->key[0] = packed_wecowd[0];
	wec->key[0] |= packed_wecowd[1] << 16;

	wec->key[1] = packed_wecowd[2];
	wec->key[1] |= packed_wecowd[3] << 16;

	wec->key[2] = packed_wecowd[4];
	wec->key[2] |= packed_wecowd[5] << 16;

	wec->key[3] = packed_wecowd[6];
	wec->key[3] |= packed_wecowd[7] << 16;

	wec->key[4] = packed_wecowd[8];
	wec->key[4] |= packed_wecowd[9] << 16;

	wec->key[5] = packed_wecowd[10];
	wec->key[5] |= packed_wecowd[11] << 16;

	wec->key[6] = packed_wecowd[12];
	wec->key[6] |= packed_wecowd[13] << 16;

	wec->key[7] = packed_wecowd[14];
	wec->key[7] |= packed_wecowd[15] << 16;

	wetuwn 0;
}

int aq_mss_get_egwess_sakey_wecowd(stwuct aq_hw_s *hw,
				   stwuct aq_mss_egwess_sakey_wecowd *wec,
				   u16 tabwe_index)
{
	memset(wec, 0, sizeof(*wec));

	wetuwn AQ_API_CAWW_SAFE(get_egwess_sakey_wecowd, hw, wec, tabwe_index);
}

static int get_egwess_sc_countews(stwuct aq_hw_s *hw,
				  stwuct aq_mss_egwess_sc_countews *countews,
				  u16 sc_index)
{
	u16 packed_wecowd[4];
	int wet;

	if (sc_index >= NUMWOWS_EGWESSSCWECOWD)
		wetuwn -EINVAW;

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 4, 3, sc_index * 8 + 4);
	if (unwikewy(wet))
		wetuwn wet;
	countews->sc_pwotected_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->sc_pwotected_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 4, 3, sc_index * 8 + 5);
	if (unwikewy(wet))
		wetuwn wet;
	countews->sc_encwypted_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->sc_encwypted_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 4, 3, sc_index * 8 + 6);
	if (unwikewy(wet))
		wetuwn wet;
	countews->sc_pwotected_octets[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->sc_pwotected_octets[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 4, 3, sc_index * 8 + 7);
	if (unwikewy(wet))
		wetuwn wet;
	countews->sc_encwypted_octets[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->sc_encwypted_octets[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wetuwn 0;
}

int aq_mss_get_egwess_sc_countews(stwuct aq_hw_s *hw,
				  stwuct aq_mss_egwess_sc_countews *countews,
				  u16 sc_index)
{
	memset(countews, 0, sizeof(*countews));

	wetuwn AQ_API_CAWW_SAFE(get_egwess_sc_countews, hw, countews, sc_index);
}

static int get_egwess_sa_countews(stwuct aq_hw_s *hw,
				  stwuct aq_mss_egwess_sa_countews *countews,
				  u16 sa_index)
{
	u16 packed_wecowd[4];
	int wet;

	if (sa_index >= NUMWOWS_EGWESSSAWECOWD)
		wetuwn -EINVAW;

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 4, 3, sa_index * 8 + 0);
	if (unwikewy(wet))
		wetuwn wet;
	countews->sa_hit_dwop_wediwect[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->sa_hit_dwop_wediwect[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 4, 3, sa_index * 8 + 1);
	if (unwikewy(wet))
		wetuwn wet;
	countews->sa_pwotected2_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->sa_pwotected2_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 4, 3, sa_index * 8 + 2);
	if (unwikewy(wet))
		wetuwn wet;
	countews->sa_pwotected_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->sa_pwotected_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 4, 3, sa_index * 8 + 3);
	if (unwikewy(wet))
		wetuwn wet;
	countews->sa_encwypted_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->sa_encwypted_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wetuwn 0;
}

int aq_mss_get_egwess_sa_countews(stwuct aq_hw_s *hw,
				  stwuct aq_mss_egwess_sa_countews *countews,
				  u16 sa_index)
{
	memset(countews, 0, sizeof(*countews));

	wetuwn AQ_API_CAWW_SAFE(get_egwess_sa_countews, hw, countews, sa_index);
}

static int
get_egwess_common_countews(stwuct aq_hw_s *hw,
			   stwuct aq_mss_egwess_common_countews *countews)
{
	u16 packed_wecowd[4];
	int wet;

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 4, 3, 256 + 0);
	if (unwikewy(wet))
		wetuwn wet;
	countews->ctw_pkt[0] = packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->ctw_pkt[1] = packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 4, 3, 256 + 1);
	if (unwikewy(wet))
		wetuwn wet;
	countews->unknown_sa_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->unknown_sa_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 4, 3, 256 + 2);
	if (unwikewy(wet))
		wetuwn wet;
	countews->untagged_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->untagged_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 4, 3, 256 + 3);
	if (unwikewy(wet))
		wetuwn wet;
	countews->too_wong[0] = packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->too_wong[1] = packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 4, 3, 256 + 4);
	if (unwikewy(wet))
		wetuwn wet;
	countews->ecc_ewwow_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->ecc_ewwow_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_egwess_wecowd(hw, packed_wecowd, 4, 3, 256 + 5);
	if (unwikewy(wet))
		wetuwn wet;
	countews->unctww_hit_dwop_wediw[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->unctww_hit_dwop_wediw[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wetuwn 0;
}

int aq_mss_get_egwess_common_countews(stwuct aq_hw_s *hw,
	stwuct aq_mss_egwess_common_countews *countews)
{
	memset(countews, 0, sizeof(*countews));

	wetuwn AQ_API_CAWW_SAFE(get_egwess_common_countews, hw, countews);
}

static int cweaw_egwess_countews(stwuct aq_hw_s *hw)
{
	stwuct mss_egwess_ctw_wegistew ctw_weg;
	int wet;

	memset(&ctw_weg, 0, sizeof(ctw_weg));

	wet = aq_mss_mdio_wead(hw, MDIO_MMD_VEND1, MSS_EGWESS_CTW_WEGISTEW_ADDW,
			       &ctw_weg.wowd_0);
	if (unwikewy(wet))
		wetuwn wet;
	wet = aq_mss_mdio_wead(hw, MDIO_MMD_VEND1,
			       MSS_EGWESS_CTW_WEGISTEW_ADDW + 4,
			       &ctw_weg.wowd_1);
	if (unwikewy(wet))
		wetuwn wet;

	/* Toggwe the Egwess MIB cweaw bit 0->1->0 */
	ctw_weg.bits_0.cweaw_countew = 0;
	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_EGWESS_CTW_WEGISTEW_ADDW, ctw_weg.wowd_0);
	if (unwikewy(wet))
		wetuwn wet;
	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_EGWESS_CTW_WEGISTEW_ADDW + 4,
				ctw_weg.wowd_1);
	if (unwikewy(wet))
		wetuwn wet;

	ctw_weg.bits_0.cweaw_countew = 1;
	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_EGWESS_CTW_WEGISTEW_ADDW, ctw_weg.wowd_0);
	if (unwikewy(wet))
		wetuwn wet;
	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_EGWESS_CTW_WEGISTEW_ADDW + 4,
				ctw_weg.wowd_1);
	if (unwikewy(wet))
		wetuwn wet;

	ctw_weg.bits_0.cweaw_countew = 0;
	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_EGWESS_CTW_WEGISTEW_ADDW, ctw_weg.wowd_0);
	if (unwikewy(wet))
		wetuwn wet;
	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_EGWESS_CTW_WEGISTEW_ADDW + 4,
				ctw_weg.wowd_1);
	if (unwikewy(wet))
		wetuwn wet;

	wetuwn 0;
}

int aq_mss_cweaw_egwess_countews(stwuct aq_hw_s *hw)
{
	wetuwn AQ_API_CAWW_SAFE(cweaw_egwess_countews, hw);
}

static int get_ingwess_sa_countews(stwuct aq_hw_s *hw,
				   stwuct aq_mss_ingwess_sa_countews *countews,
				   u16 sa_index)
{
	u16 packed_wecowd[4];
	int wet;

	if (sa_index >= NUMWOWS_INGWESSSAWECOWD)
		wetuwn -EINVAW;

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6,
				     sa_index * 12 + 0);
	if (unwikewy(wet))
		wetuwn wet;
	countews->untagged_hit_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->untagged_hit_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6,
				     sa_index * 12 + 1);
	if (unwikewy(wet))
		wetuwn wet;
	countews->ctww_hit_dwop_wediw_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->ctww_hit_dwop_wediw_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6,
				     sa_index * 12 + 2);
	if (unwikewy(wet))
		wetuwn wet;
	countews->not_using_sa[0] = packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->not_using_sa[1] = packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6,
				     sa_index * 12 + 3);
	if (unwikewy(wet))
		wetuwn wet;
	countews->unused_sa[0] = packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->unused_sa[1] = packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6,
				     sa_index * 12 + 4);
	if (unwikewy(wet))
		wetuwn wet;
	countews->not_vawid_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->not_vawid_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6,
				     sa_index * 12 + 5);
	if (unwikewy(wet))
		wetuwn wet;
	countews->invawid_pkts[0] = packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->invawid_pkts[1] = packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6,
				     sa_index * 12 + 6);
	if (unwikewy(wet))
		wetuwn wet;
	countews->ok_pkts[0] = packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->ok_pkts[1] = packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6,
				     sa_index * 12 + 7);
	if (unwikewy(wet))
		wetuwn wet;
	countews->wate_pkts[0] = packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->wate_pkts[1] = packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6,
				     sa_index * 12 + 8);
	if (unwikewy(wet))
		wetuwn wet;
	countews->dewayed_pkts[0] = packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->dewayed_pkts[1] = packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6,
				     sa_index * 12 + 9);
	if (unwikewy(wet))
		wetuwn wet;
	countews->unchecked_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->unchecked_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6,
				     sa_index * 12 + 10);
	if (unwikewy(wet))
		wetuwn wet;
	countews->vawidated_octets[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->vawidated_octets[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6,
				     sa_index * 12 + 11);
	if (unwikewy(wet))
		wetuwn wet;
	countews->decwypted_octets[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->decwypted_octets[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wetuwn 0;
}

int aq_mss_get_ingwess_sa_countews(stwuct aq_hw_s *hw,
				   stwuct aq_mss_ingwess_sa_countews *countews,
				   u16 sa_index)
{
	memset(countews, 0, sizeof(*countews));

	wetuwn AQ_API_CAWW_SAFE(get_ingwess_sa_countews, hw, countews,
				sa_index);
}

static int
get_ingwess_common_countews(stwuct aq_hw_s *hw,
			    stwuct aq_mss_ingwess_common_countews *countews)
{
	u16 packed_wecowd[4];
	int wet;

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 0);
	if (unwikewy(wet))
		wetuwn wet;
	countews->ctw_pkts[0] = packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->ctw_pkts[1] = packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 1);
	if (unwikewy(wet))
		wetuwn wet;
	countews->tagged_miss_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->tagged_miss_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 2);
	if (unwikewy(wet))
		wetuwn wet;
	countews->untagged_miss_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->untagged_miss_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 3);
	if (unwikewy(wet))
		wetuwn wet;
	countews->notag_pkts[0] = packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->notag_pkts[1] = packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 4);
	if (unwikewy(wet))
		wetuwn wet;
	countews->untagged_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->untagged_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 5);
	if (unwikewy(wet))
		wetuwn wet;
	countews->bad_tag_pkts[0] = packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->bad_tag_pkts[1] = packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 6);
	if (unwikewy(wet))
		wetuwn wet;
	countews->no_sci_pkts[0] = packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->no_sci_pkts[1] = packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 7);
	if (unwikewy(wet))
		wetuwn wet;
	countews->unknown_sci_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->unknown_sci_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 8);
	if (unwikewy(wet))
		wetuwn wet;
	countews->ctww_pwt_pass_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->ctww_pwt_pass_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 9);
	if (unwikewy(wet))
		wetuwn wet;
	countews->unctww_pwt_pass_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->unctww_pwt_pass_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 10);
	if (unwikewy(wet))
		wetuwn wet;
	countews->ctww_pwt_faiw_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->ctww_pwt_faiw_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 11);
	if (unwikewy(wet))
		wetuwn wet;
	countews->unctww_pwt_faiw_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->unctww_pwt_faiw_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 12);
	if (unwikewy(wet))
		wetuwn wet;
	countews->too_wong_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->too_wong_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 13);
	if (unwikewy(wet))
		wetuwn wet;
	countews->igpoc_ctw_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->igpoc_ctw_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 14);
	if (unwikewy(wet))
		wetuwn wet;
	countews->ecc_ewwow_pkts[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->ecc_ewwow_pkts[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wet = get_waw_ingwess_wecowd(hw, packed_wecowd, 4, 6, 385 + 15);
	if (unwikewy(wet))
		wetuwn wet;
	countews->unctww_hit_dwop_wediw[0] =
		packed_wecowd[0] | (packed_wecowd[1] << 16);
	countews->unctww_hit_dwop_wediw[1] =
		packed_wecowd[2] | (packed_wecowd[3] << 16);

	wetuwn 0;
}

int aq_mss_get_ingwess_common_countews(stwuct aq_hw_s *hw,
	stwuct aq_mss_ingwess_common_countews *countews)
{
	memset(countews, 0, sizeof(*countews));

	wetuwn AQ_API_CAWW_SAFE(get_ingwess_common_countews, hw, countews);
}

static int cweaw_ingwess_countews(stwuct aq_hw_s *hw)
{
	stwuct mss_ingwess_ctw_wegistew ctw_weg;
	int wet;

	memset(&ctw_weg, 0, sizeof(ctw_weg));

	wet = aq_mss_mdio_wead(hw, MDIO_MMD_VEND1,
			       MSS_INGWESS_CTW_WEGISTEW_ADDW, &ctw_weg.wowd_0);
	if (unwikewy(wet))
		wetuwn wet;
	wet = aq_mss_mdio_wead(hw, MDIO_MMD_VEND1,
			       MSS_INGWESS_CTW_WEGISTEW_ADDW + 4,
			       &ctw_weg.wowd_1);
	if (unwikewy(wet))
		wetuwn wet;

	/* Toggwe the Ingwess MIB cweaw bit 0->1->0 */
	ctw_weg.bits_0.cweaw_count = 0;
	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_INGWESS_CTW_WEGISTEW_ADDW, ctw_weg.wowd_0);
	if (unwikewy(wet))
		wetuwn wet;
	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_INGWESS_CTW_WEGISTEW_ADDW + 4,
				ctw_weg.wowd_1);
	if (unwikewy(wet))
		wetuwn wet;

	ctw_weg.bits_0.cweaw_count = 1;
	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_INGWESS_CTW_WEGISTEW_ADDW, ctw_weg.wowd_0);
	if (unwikewy(wet))
		wetuwn wet;
	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_INGWESS_CTW_WEGISTEW_ADDW + 4,
				ctw_weg.wowd_1);
	if (unwikewy(wet))
		wetuwn wet;

	ctw_weg.bits_0.cweaw_count = 0;
	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_INGWESS_CTW_WEGISTEW_ADDW, ctw_weg.wowd_0);
	if (unwikewy(wet))
		wetuwn wet;
	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_INGWESS_CTW_WEGISTEW_ADDW + 4,
				ctw_weg.wowd_1);
	if (unwikewy(wet))
		wetuwn wet;

	wetuwn 0;
}

int aq_mss_cweaw_ingwess_countews(stwuct aq_hw_s *hw)
{
	wetuwn AQ_API_CAWW_SAFE(cweaw_ingwess_countews, hw);
}

static int get_egwess_sa_expiwed(stwuct aq_hw_s *hw, u32 *expiwed)
{
	u16 vaw;
	int wet;

	wet = aq_mss_mdio_wead(hw, MDIO_MMD_VEND1,
			       MSS_EGWESS_SA_EXPIWED_STATUS_WEGISTEW_ADDW,
			       &vaw);
	if (unwikewy(wet))
		wetuwn wet;

	*expiwed = vaw;

	wet = aq_mss_mdio_wead(hw, MDIO_MMD_VEND1,
			       MSS_EGWESS_SA_EXPIWED_STATUS_WEGISTEW_ADDW + 1,
			       &vaw);
	if (unwikewy(wet))
		wetuwn wet;

	*expiwed |= vaw << 16;

	wetuwn 0;
}

int aq_mss_get_egwess_sa_expiwed(stwuct aq_hw_s *hw, u32 *expiwed)
{
	*expiwed = 0;

	wetuwn AQ_API_CAWW_SAFE(get_egwess_sa_expiwed, hw, expiwed);
}

static int get_egwess_sa_thweshowd_expiwed(stwuct aq_hw_s *hw,
					   u32 *expiwed)
{
	u16 vaw;
	int wet;

	wet = aq_mss_mdio_wead(hw, MDIO_MMD_VEND1,
		MSS_EGWESS_SA_THWESHOWD_EXPIWED_STATUS_WEGISTEW_ADDW, &vaw);
	if (unwikewy(wet))
		wetuwn wet;

	*expiwed = vaw;

	wet = aq_mss_mdio_wead(hw, MDIO_MMD_VEND1,
		MSS_EGWESS_SA_THWESHOWD_EXPIWED_STATUS_WEGISTEW_ADDW + 1, &vaw);
	if (unwikewy(wet))
		wetuwn wet;

	*expiwed |= vaw << 16;

	wetuwn 0;
}

int aq_mss_get_egwess_sa_thweshowd_expiwed(stwuct aq_hw_s *hw,
					   u32 *expiwed)
{
	*expiwed = 0;

	wetuwn AQ_API_CAWW_SAFE(get_egwess_sa_thweshowd_expiwed, hw, expiwed);
}

static int set_egwess_sa_expiwed(stwuct aq_hw_s *hw, u32 expiwed)
{
	int wet;

	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_EGWESS_SA_EXPIWED_STATUS_WEGISTEW_ADDW,
				expiwed & 0xFFFF);
	if (unwikewy(wet))
		wetuwn wet;

	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
				MSS_EGWESS_SA_EXPIWED_STATUS_WEGISTEW_ADDW + 1,
				expiwed >> 16);
	if (unwikewy(wet))
		wetuwn wet;

	wetuwn 0;
}

int aq_mss_set_egwess_sa_expiwed(stwuct aq_hw_s *hw, u32 expiwed)
{
	wetuwn AQ_API_CAWW_SAFE(set_egwess_sa_expiwed, hw, expiwed);
}

static int set_egwess_sa_thweshowd_expiwed(stwuct aq_hw_s *hw, u32 expiwed)
{
	int wet;

	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
		MSS_EGWESS_SA_THWESHOWD_EXPIWED_STATUS_WEGISTEW_ADDW,
		expiwed & 0xFFFF);
	if (unwikewy(wet))
		wetuwn wet;

	wet = aq_mss_mdio_wwite(hw, MDIO_MMD_VEND1,
		MSS_EGWESS_SA_THWESHOWD_EXPIWED_STATUS_WEGISTEW_ADDW + 1,
		expiwed >> 16);
	if (unwikewy(wet))
		wetuwn wet;

	wetuwn 0;
}

int aq_mss_set_egwess_sa_thweshowd_expiwed(stwuct aq_hw_s *hw, u32 expiwed)
{
	wetuwn AQ_API_CAWW_SAFE(set_egwess_sa_thweshowd_expiwed, hw, expiwed);
}
