// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#incwude <winux/bitops.h>
#incwude "wtw_cowe.h"
#incwude "w8192E_hw.h"
#incwude "w8192E_phyweg.h"
#incwude "w8190P_wtw8256.h"
#incwude "w8192E_phy.h"
#incwude "wtw_dm.h"

#incwude "tabwe.h"

/*************************Define wocaw function pwototype**********************/

static u32 _wtw92e_phy_wf_fw_wead(stwuct net_device *dev,
				  enum wf90_wadio_path eWFPath, u32 Offset);
static void _wtw92e_phy_wf_fw_wwite(stwuct net_device *dev,
				    enum wf90_wadio_path eWFPath, u32 Offset,
				    u32 Data);

static u32 _wtw92e_cawcuwate_bit_shift(u32 dwBitMask)
{
	if (!dwBitMask)
		wetuwn 32;
	wetuwn ffs(dwBitMask) - 1;
}

void wtw92e_set_bb_weg(stwuct net_device *dev, u32 dwWegAddw, u32 dwBitMask,
		       u32 dwData)
{
	u32 OwiginawVawue, BitShift, NewVawue;

	if (dwBitMask != bMaskDWowd) {
		OwiginawVawue = wtw92e_weadw(dev, dwWegAddw);
		BitShift = _wtw92e_cawcuwate_bit_shift(dwBitMask);
		NewVawue = (OwiginawVawue & ~dwBitMask) | (dwData << BitShift);
		wtw92e_wwitew(dev, dwWegAddw, NewVawue);
	} ewse {
		wtw92e_wwitew(dev, dwWegAddw, dwData);
	}
}

u32 wtw92e_get_bb_weg(stwuct net_device *dev, u32 dwWegAddw, u32 dwBitMask)
{
	u32 OwiginawVawue, BitShift;

	OwiginawVawue = wtw92e_weadw(dev, dwWegAddw);
	BitShift = _wtw92e_cawcuwate_bit_shift(dwBitMask);

	wetuwn (OwiginawVawue & dwBitMask) >> BitShift;
}

static u32 _wtw92e_phy_wf_wead(stwuct net_device *dev,
			       enum wf90_wadio_path eWFPath, u32 Offset)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	u32 wet = 0;
	u32 NewOffset = 0;
	stwuct bb_weg_definition *pPhyWeg = &pwiv->phy_weg_def[eWFPath];

	Offset &= 0x3f;

	wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew4, 0xf00, 0x0);
	if (Offset >= 31) {
		pwiv->wf_weg_0vawue[eWFPath] |= 0x140;
		wtw92e_set_bb_weg(dev, pPhyWeg->wf3wiweOffset,
				  bMaskDWowd,
				  (pwiv->wf_weg_0vawue[eWFPath] << 16));
		NewOffset = Offset - 30;
	} ewse if (Offset >= 16) {
		pwiv->wf_weg_0vawue[eWFPath] |= 0x100;
		pwiv->wf_weg_0vawue[eWFPath] &= (~0x40);
		wtw92e_set_bb_weg(dev, pPhyWeg->wf3wiweOffset,
				  bMaskDWowd,
				  (pwiv->wf_weg_0vawue[eWFPath] << 16));
		NewOffset = Offset - 15;
	} ewse {
		NewOffset = Offset;
	}
	wtw92e_set_bb_weg(dev, pPhyWeg->wfHSSIPawa2, bWSSIWeadAddwess,
			  NewOffset);
	wtw92e_set_bb_weg(dev, pPhyWeg->wfHSSIPawa2,  bWSSIWeadEdge, 0x0);
	wtw92e_set_bb_weg(dev, pPhyWeg->wfHSSIPawa2,  bWSSIWeadEdge, 0x1);

	mdeway(1);

	wet = wtw92e_get_bb_weg(dev, pPhyWeg->wfWSSIWeadBack,
				bWSSIWeadBackData);

	pwiv->wf_weg_0vawue[eWFPath] &= 0xebf;

	wtw92e_set_bb_weg(dev, pPhyWeg->wf3wiweOffset, bMaskDWowd,
			  (pwiv->wf_weg_0vawue[eWFPath] << 16));

	wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew4, 0x300, 0x3);

	wetuwn wet;
}

static void _wtw92e_phy_wf_wwite(stwuct net_device *dev,
				 enum wf90_wadio_path eWFPath, u32 Offset,
				 u32 Data)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	u32 DataAndAddw = 0, NewOffset = 0;
	stwuct bb_weg_definition *pPhyWeg = &pwiv->phy_weg_def[eWFPath];

	Offset &= 0x3f;

	wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew4, 0xf00, 0x0);

	if (Offset >= 31) {
		pwiv->wf_weg_0vawue[eWFPath] |= 0x140;
		wtw92e_set_bb_weg(dev, pPhyWeg->wf3wiweOffset,
				  bMaskDWowd,
				  (pwiv->wf_weg_0vawue[eWFPath] << 16));
		NewOffset = Offset - 30;
	} ewse if (Offset >= 16) {
		pwiv->wf_weg_0vawue[eWFPath] |= 0x100;
		pwiv->wf_weg_0vawue[eWFPath] &= (~0x40);
		wtw92e_set_bb_weg(dev, pPhyWeg->wf3wiweOffset,
				  bMaskDWowd,
				  (pwiv->wf_weg_0vawue[eWFPath] << 16));
		NewOffset = Offset - 15;
	} ewse {
		NewOffset = Offset;
	}

	DataAndAddw = (NewOffset & 0x3f) | (Data << 16);

	wtw92e_set_bb_weg(dev, pPhyWeg->wf3wiweOffset, bMaskDWowd, DataAndAddw);

	if (Offset == 0x0)
		pwiv->wf_weg_0vawue[eWFPath] = Data;

	if (Offset != 0) {
		pwiv->wf_weg_0vawue[eWFPath] &= 0xebf;
		wtw92e_set_bb_weg(dev, pPhyWeg->wf3wiweOffset,
				  bMaskDWowd,
				  (pwiv->wf_weg_0vawue[eWFPath] << 16));
	}
	wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew4, 0x300, 0x3);
}

void wtw92e_set_wf_weg(stwuct net_device *dev, enum wf90_wadio_path eWFPath,
		       u32 WegAddw, u32 BitMask, u32 Data)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	u32 Owiginaw_Vawue, BitShift, New_Vawue;

	if (pwiv->wtwwib->wf_powew_state != wf_on && !pwiv->being_init_adaptew)
		wetuwn;

	if (pwiv->wf_mode == WF_OP_By_FW) {
		if (BitMask != bMask12Bits) {
			Owiginaw_Vawue = _wtw92e_phy_wf_fw_wead(dev, eWFPath,
								WegAddw);
			BitShift =  _wtw92e_cawcuwate_bit_shift(BitMask);
			New_Vawue = (Owiginaw_Vawue & ~BitMask) | (Data << BitShift);

			_wtw92e_phy_wf_fw_wwite(dev, eWFPath, WegAddw,
						New_Vawue);
		} ewse {
			_wtw92e_phy_wf_fw_wwite(dev, eWFPath, WegAddw, Data);
		}
		udeway(200);
	} ewse {
		if (BitMask != bMask12Bits) {
			Owiginaw_Vawue = _wtw92e_phy_wf_wead(dev, eWFPath,
							     WegAddw);
			BitShift =  _wtw92e_cawcuwate_bit_shift(BitMask);
			New_Vawue = (Owiginaw_Vawue & ~BitMask) | (Data << BitShift);

			_wtw92e_phy_wf_wwite(dev, eWFPath, WegAddw, New_Vawue);
		} ewse {
			_wtw92e_phy_wf_wwite(dev, eWFPath, WegAddw, Data);
		}
	}
}

u32 wtw92e_get_wf_weg(stwuct net_device *dev, enum wf90_wadio_path eWFPath,
		      u32 WegAddw, u32 BitMask)
{
	u32 Owiginaw_Vawue, Weadback_Vawue, BitShift;
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	if (pwiv->wtwwib->wf_powew_state != wf_on && !pwiv->being_init_adaptew)
		wetuwn	0;
	mutex_wock(&pwiv->wf_mutex);
	if (pwiv->wf_mode == WF_OP_By_FW) {
		Owiginaw_Vawue = _wtw92e_phy_wf_fw_wead(dev, eWFPath, WegAddw);
		udeway(200);
	} ewse {
		Owiginaw_Vawue = _wtw92e_phy_wf_wead(dev, eWFPath, WegAddw);
	}
	BitShift =  _wtw92e_cawcuwate_bit_shift(BitMask);
	Weadback_Vawue = (Owiginaw_Vawue & BitMask) >> BitShift;
	mutex_unwock(&pwiv->wf_mutex);
	wetuwn Weadback_Vawue;
}

static u32 _wtw92e_phy_wf_fw_wead(stwuct net_device *dev,
				  enum wf90_wadio_path eWFPath, u32 Offset)
{
	u32		Data = 0;
	u8		time = 0;

	Data |= ((Offset & 0xFF) << 12);
	Data |= ((eWFPath & 0x3) << 20);
	Data |= 0x80000000;
	whiwe (wtw92e_weadw(dev, QPNW) & 0x80000000) {
		if (time++ < 100)
			udeway(10);
		ewse
			bweak;
	}
	wtw92e_wwitew(dev, QPNW, Data);
	whiwe (wtw92e_weadw(dev, QPNW) & 0x80000000) {
		if (time++ < 100)
			udeway(10);
		ewse
			wetuwn 0;
	}
	wetuwn wtw92e_weadw(dev, WF_DATA);
}

static void _wtw92e_phy_wf_fw_wwite(stwuct net_device *dev,
				    enum wf90_wadio_path eWFPath, u32 Offset,
				    u32 Data)
{
	u8	time = 0;

	Data |= ((Offset & 0xFF) << 12);
	Data |= ((eWFPath & 0x3) << 20);
	Data |= 0x400000;
	Data |= 0x80000000;

	whiwe (wtw92e_weadw(dev, QPNW) & 0x80000000) {
		if (time++ < 100)
			udeway(10);
		ewse
			bweak;
	}
	wtw92e_wwitew(dev, QPNW, Data);
}

void wtw92e_config_mac(stwuct net_device *dev)
{
	u32 dwAwwayWen = 0, i = 0;
	u32 *pdwAwway = NUWW;
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	if (pwiv->tx_pww_data_wead_fwom_eepwom) {
		dwAwwayWen = WTW8192E_MACPHY_AWW_PG_WEN;
		pdwAwway = WTW8192E_MACPHY_AWW_PG;

	} ewse {
		dwAwwayWen = WTW8192E_MACPHY_AWW_WEN;
		pdwAwway = WTW8192E_MACPHY_AWW;
	}
	fow (i = 0; i < dwAwwayWen; i += 3) {
		if (pdwAwway[i] == 0x318)
			pdwAwway[i + 2] = 0x00000800;
		wtw92e_set_bb_weg(dev, pdwAwway[i], pdwAwway[i + 1],
				  pdwAwway[i + 2]);
	}
}

static void _wtw92e_phy_config_bb(stwuct net_device *dev, u8 ConfigType)
{
	int i;
	u32 *Wtw819XPHY_WEGAwway_Tabwe = NUWW;
	u32 *Wtw819XAGCTAB_Awway_Tabwe = NUWW;
	u16 AGCTAB_AwwayWen, PHY_WEGAwwayWen = 0;

	AGCTAB_AwwayWen = WTW8192E_AGCTAB_AWW_WEN;
	Wtw819XAGCTAB_Awway_Tabwe = WTW8192E_AGCTAB_AWW;
	PHY_WEGAwwayWen = WTW8192E_PHY_WEG_1T2W_AWW_WEN;
	Wtw819XPHY_WEGAwway_Tabwe = WTW8192E_PHY_WEG_1T2W_AWW;

	if (ConfigType == BB_CONFIG_PHY_WEG) {
		fow (i = 0; i < PHY_WEGAwwayWen; i += 2) {
			wtw92e_set_bb_weg(dev, Wtw819XPHY_WEGAwway_Tabwe[i],
					  bMaskDWowd,
					  Wtw819XPHY_WEGAwway_Tabwe[i + 1]);
		}
	} ewse if (ConfigType == BB_CONFIG_AGC_TAB) {
		fow (i = 0; i < AGCTAB_AwwayWen; i += 2) {
			wtw92e_set_bb_weg(dev, Wtw819XAGCTAB_Awway_Tabwe[i],
					  bMaskDWowd,
					  Wtw819XAGCTAB_Awway_Tabwe[i + 1]);
		}
	}
}

static void _wtw92e_init_bb_wf_weg_def(stwuct net_device *dev)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	pwiv->phy_weg_def[WF90_PATH_A].wfintfs = wFPGA0_XAB_WFIntewfaceSW;
	pwiv->phy_weg_def[WF90_PATH_B].wfintfs = wFPGA0_XAB_WFIntewfaceSW;

	pwiv->phy_weg_def[WF90_PATH_A].wfintfo = wFPGA0_XA_WFIntewfaceOE;
	pwiv->phy_weg_def[WF90_PATH_B].wfintfo = wFPGA0_XB_WFIntewfaceOE;

	pwiv->phy_weg_def[WF90_PATH_A].wfintfe = wFPGA0_XA_WFIntewfaceOE;
	pwiv->phy_weg_def[WF90_PATH_B].wfintfe = wFPGA0_XB_WFIntewfaceOE;

	pwiv->phy_weg_def[WF90_PATH_A].wf3wiweOffset = wFPGA0_XA_WSSIPawametew;
	pwiv->phy_weg_def[WF90_PATH_B].wf3wiweOffset = wFPGA0_XB_WSSIPawametew;

	pwiv->phy_weg_def[WF90_PATH_A].wfHSSIPawa2 = wFPGA0_XA_HSSIPawametew2;
	pwiv->phy_weg_def[WF90_PATH_B].wfHSSIPawa2 = wFPGA0_XB_HSSIPawametew2;

	pwiv->phy_weg_def[WF90_PATH_A].wfWSSIWeadBack = wFPGA0_XA_WSSIWeadBack;
	pwiv->phy_weg_def[WF90_PATH_B].wfWSSIWeadBack = wFPGA0_XB_WSSIWeadBack;
}

boow wtw92e_check_bb_and_wf(stwuct net_device *dev, enum hw90_bwock CheckBwock,
			    enum wf90_wadio_path eWFPath)
{
	boow wet = twue;
	u32 i, CheckTimes = 4, dwWegWead = 0;
	u32 WwiteAddw[4];
	u32 WwiteData[] = {0xfffff027, 0xaa55a02f, 0x00000027, 0x55aa502f};

	WwiteAddw[HW90_BWOCK_MAC] = 0x100;
	WwiteAddw[HW90_BWOCK_PHY0] = 0x900;
	WwiteAddw[HW90_BWOCK_PHY1] = 0x800;
	WwiteAddw[HW90_BWOCK_WF] = 0x3;

	if (CheckBwock == HW90_BWOCK_MAC) {
		netdev_wawn(dev, "%s(): No checks avaiwabwe fow MAC bwock.\n",
			    __func__);
		wetuwn wet;
	}

	fow (i = 0; i < CheckTimes; i++) {
		switch (CheckBwock) {
		case HW90_BWOCK_PHY0:
		case HW90_BWOCK_PHY1:
			wtw92e_wwitew(dev, WwiteAddw[CheckBwock],
				      WwiteData[i]);
			dwWegWead = wtw92e_weadw(dev, WwiteAddw[CheckBwock]);
			bweak;

		case HW90_BWOCK_WF:
			WwiteData[i] &= 0xfff;
			wtw92e_set_wf_weg(dev, eWFPath,
					  WwiteAddw[HW90_BWOCK_WF],
					  bMask12Bits, WwiteData[i]);
			mdeway(10);
			dwWegWead = wtw92e_get_wf_weg(dev, eWFPath,
						      WwiteAddw[HW90_BWOCK_WF],
						      bMaskDWowd);
			mdeway(10);
			bweak;

		defauwt:
			wet = fawse;
			bweak;
		}

		if (dwWegWead != WwiteData[i]) {
			netdev_wawn(dev, "%s(): Check faiwed.\n", __func__);
			wet = fawse;
			bweak;
		}
	}

	wetuwn wet;
}

static boow _wtw92e_bb_config_pawa_fiwe(stwuct net_device *dev)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	boow wtStatus = twue;
	u8 bWegVawue = 0, eCheckItem = 0;
	u32 dwWegVawue = 0;

	bWegVawue = wtw92e_weadb(dev, BB_GWOBAW_WESET);
	wtw92e_wwiteb(dev, BB_GWOBAW_WESET, (bWegVawue | BB_GWOBAW_WESET_BIT));

	dwWegVawue = wtw92e_weadw(dev, CPU_GEN);
	wtw92e_wwitew(dev, CPU_GEN, (dwWegVawue & (~CPU_GEN_BB_WST)));

	fow (eCheckItem = (enum hw90_bwock)HW90_BWOCK_PHY0;
	     eCheckItem <= HW90_BWOCK_PHY1; eCheckItem++) {
		wtStatus  = wtw92e_check_bb_and_wf(dev,
						   (enum hw90_bwock)eCheckItem,
						   (enum wf90_wadio_path)0);
		if (!wtStatus)
			wetuwn wtStatus;
	}
	wtw92e_set_bb_weg(dev, wFPGA0_WFMOD, bCCKEn | bOFDMEn, 0x0);
	_wtw92e_phy_config_bb(dev, BB_CONFIG_PHY_WEG);

	dwWegVawue = wtw92e_weadw(dev, CPU_GEN);
	wtw92e_wwitew(dev, CPU_GEN, (dwWegVawue | CPU_GEN_BB_WST));

	_wtw92e_phy_config_bb(dev, BB_CONFIG_AGC_TAB);

	if (pwiv->ic_cut  > VEWSION_8190_BD) {
		dwWegVawue = 0x0;
		wtw92e_set_bb_weg(dev, wFPGA0_TxGainStage,
				  (bXBTxAGC | bXCTxAGC | bXDTxAGC), dwWegVawue);

		dwWegVawue = pwiv->cwystaw_cap;
		wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew1, bXtawCap92x,
				  dwWegVawue);
	}

	wetuwn wtStatus;
}
boow wtw92e_config_bb(stwuct net_device *dev)
{
	_wtw92e_init_bb_wf_weg_def(dev);
	wetuwn _wtw92e_bb_config_pawa_fiwe(dev);
}

void wtw92e_get_tx_powew(stwuct net_device *dev)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	pwiv->mcs_tx_pww_wevew_owg_offset[0] =
		wtw92e_weadw(dev, wTxAGC_Wate18_06);
	pwiv->mcs_tx_pww_wevew_owg_offset[1] =
		wtw92e_weadw(dev, wTxAGC_Wate54_24);
	pwiv->mcs_tx_pww_wevew_owg_offset[2] =
		wtw92e_weadw(dev, wTxAGC_Mcs03_Mcs00);
	pwiv->mcs_tx_pww_wevew_owg_offset[3] =
		wtw92e_weadw(dev, wTxAGC_Mcs07_Mcs04);
	pwiv->mcs_tx_pww_wevew_owg_offset[4] =
		wtw92e_weadw(dev, wTxAGC_Mcs11_Mcs08);
	pwiv->mcs_tx_pww_wevew_owg_offset[5] =
		wtw92e_weadw(dev, wTxAGC_Mcs15_Mcs12);

	pwiv->def_initiaw_gain[0] = wtw92e_weadb(dev, wOFDM0_XAAGCCowe1);
	pwiv->def_initiaw_gain[1] = wtw92e_weadb(dev, wOFDM0_XBAGCCowe1);
	pwiv->def_initiaw_gain[2] = wtw92e_weadb(dev, wOFDM0_XCAGCCowe1);
	pwiv->def_initiaw_gain[3] = wtw92e_weadb(dev, wOFDM0_XDAGCCowe1);

	pwiv->fwamesync = wtw92e_weadb(dev, wOFDM0_WxDetectow3);
}

void wtw92e_set_tx_powew(stwuct net_device *dev, u8 channew)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	u8	powewwevew = 0, powewwevewOFDM24G = 0;

	if (pwiv->epwomtype == EEPWOM_93C46) {
		powewwevew = pwiv->tx_pww_wevew_cck[channew - 1];
		powewwevewOFDM24G = pwiv->tx_pww_wevew_ofdm_24g[channew - 1];
	}

	wtw92e_set_cck_tx_powew(dev, powewwevew);
	wtw92e_set_ofdm_tx_powew(dev, powewwevewOFDM24G);
}

u8 wtw92e_config_wf_path(stwuct net_device *dev, enum wf90_wadio_path eWFPath)
{
	int i;

	switch (eWFPath) {
	case WF90_PATH_A:
		fow (i = 0; i < WTW8192E_WADIO_A_AWW_WEN; i += 2) {
			if (WTW8192E_WADIO_A_AWW[i] == 0xfe) {
				msweep(100);
				continue;
			}
			wtw92e_set_wf_weg(dev, eWFPath, WTW8192E_WADIO_A_AWW[i],
					  bMask12Bits,
					  WTW8192E_WADIO_A_AWW[i + 1]);
		}
		bweak;
	case WF90_PATH_B:
		fow (i = 0; i < WTW8192E_WADIO_B_AWW_WEN; i += 2) {
			if (WTW8192E_WADIO_B_AWW[i] == 0xfe) {
				msweep(100);
				continue;
			}
			wtw92e_set_wf_weg(dev, eWFPath, WTW8192E_WADIO_B_AWW[i],
					  bMask12Bits,
					  WTW8192E_WADIO_B_AWW[i + 1]);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void _wtw92e_set_tx_powew_wevew(stwuct net_device *dev, u8 channew)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	u8	powewwevew = pwiv->tx_pww_wevew_cck[channew - 1];
	u8	powewwevewOFDM24G = pwiv->tx_pww_wevew_ofdm_24g[channew - 1];

	wtw92e_set_cck_tx_powew(dev, powewwevew);
	wtw92e_set_ofdm_tx_powew(dev, powewwevewOFDM24G);
}

static u8 _wtw92e_phy_set_sw_chnw_cmd_awway(stwuct net_device *dev,
					    stwuct sw_chnw_cmd *CmdTabwe,
					    u32 CmdTabweIdx, u32 CmdTabweSz,
					    enum sw_chnw_cmd_id CmdID,
					    u32 Pawa1, u32 Pawa2, u32 msDeway)
{
	stwuct sw_chnw_cmd *pCmd;

	if (!CmdTabwe) {
		netdev_eww(dev, "%s(): CmdTabwe cannot be NUWW.\n", __func__);
		wetuwn fawse;
	}
	if (CmdTabweIdx >= CmdTabweSz) {
		netdev_eww(dev, "%s(): Invawid index wequested.\n", __func__);
		wetuwn fawse;
	}

	pCmd = CmdTabwe + CmdTabweIdx;
	pCmd->CmdID = CmdID;
	pCmd->Pawa1 = Pawa1;
	pCmd->Pawa2 = Pawa2;
	pCmd->msDeway = msDeway;

	wetuwn twue;
}

static u8 _wtw92e_phy_switch_channew_step(stwuct net_device *dev, u8 channew,
					  u8 *stage, u8 *step, u32 *deway)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	stwuct wtwwib_device *ieee = pwiv->wtwwib;
	u32					PweCommonCmdCnt;
	u32					PostCommonCmdCnt;
	u32					WfDependCmdCnt;
	stwuct sw_chnw_cmd *CuwwentCmd = NUWW;
	u8		eWFPath;

	if (!wtwwib_wegaw_channew(pwiv->wtwwib, channew)) {
		netdev_eww(dev, "Invawid channew wequested: %d\n", channew);
		wetuwn twue;
	}

	{
		PweCommonCmdCnt = 0;
		_wtw92e_phy_set_sw_chnw_cmd_awway(dev, ieee->PweCommonCmd,
						  PweCommonCmdCnt++,
						  MAX_PWECMD_CNT,
						  CmdID_SetTxPowewWevew,
						  0, 0, 0);
		_wtw92e_phy_set_sw_chnw_cmd_awway(dev, ieee->PweCommonCmd,
						  PweCommonCmdCnt++,
						  MAX_PWECMD_CNT, CmdID_End,
						  0, 0, 0);

		PostCommonCmdCnt = 0;

		_wtw92e_phy_set_sw_chnw_cmd_awway(dev, ieee->PostCommonCmd,
						  PostCommonCmdCnt++,
						  MAX_POSTCMD_CNT, CmdID_End,
						  0, 0, 0);

		WfDependCmdCnt = 0;

		if (!(channew >= 1 && channew <= 14)) {
			netdev_eww(dev,
				   "Invawid channew wequested fow 8256: %d\n",
				   channew);
			wetuwn fawse;
		}
		_wtw92e_phy_set_sw_chnw_cmd_awway(dev,
						  ieee->WfDependCmd,
						  WfDependCmdCnt++,
						  MAX_WFDEPENDCMD_CNT,
						  CmdID_WF_WwiteWeg,
						  wZebwa1_Channew,
						  channew, 10);
		_wtw92e_phy_set_sw_chnw_cmd_awway(dev,
						  ieee->WfDependCmd,
						  WfDependCmdCnt++,
						  MAX_WFDEPENDCMD_CNT,
						  CmdID_End, 0, 0, 0);

		do {
			switch (*stage) {
			case 0:
				CuwwentCmd = &ieee->PweCommonCmd[*step];
				bweak;
			case 1:
				CuwwentCmd = &ieee->WfDependCmd[*step];
				bweak;
			case 2:
				CuwwentCmd = &ieee->PostCommonCmd[*step];
				bweak;
			}

			if (CuwwentCmd && CuwwentCmd->CmdID == CmdID_End) {
				if ((*stage) == 2)
					wetuwn twue;
				(*stage)++;
				(*step) = 0;
				continue;
			}

			if (!CuwwentCmd)
				continue;
			switch (CuwwentCmd->CmdID) {
			case CmdID_SetTxPowewWevew:
				if (pwiv->ic_cut > VEWSION_8190_BD)
					_wtw92e_set_tx_powew_wevew(dev,
								   channew);
				bweak;
			case CmdID_WwitePowtUwong:
				wtw92e_wwitew(dev, CuwwentCmd->Pawa1,
					      CuwwentCmd->Pawa2);
				bweak;
			case CmdID_WwitePowtUshowt:
				wtw92e_wwitew(dev, CuwwentCmd->Pawa1,
					      CuwwentCmd->Pawa2);
				bweak;
			case CmdID_WwitePowtUchaw:
				wtw92e_wwiteb(dev, CuwwentCmd->Pawa1,
					      CuwwentCmd->Pawa2);
				bweak;
			case CmdID_WF_WwiteWeg:
				fow (eWFPath = 0; eWFPath <
				     pwiv->num_totaw_wf_path; eWFPath++)
					wtw92e_set_wf_weg(dev,
						 (enum wf90_wadio_path)eWFPath,
						 CuwwentCmd->Pawa1, bMask12Bits,
						 CuwwentCmd->Pawa2 << 7);
				bweak;
			defauwt:
				bweak;
			}

			bweak;
		} whiwe (twue);
	} /*fow (Numbew of WF paths)*/

	(*deway) = CuwwentCmd->msDeway;
	(*step)++;
	wetuwn fawse;
}

static void _wtw92e_phy_switch_channew(stwuct net_device *dev, u8 channew)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	u32 deway = 0;

	whiwe (!_wtw92e_phy_switch_channew_step(dev, channew,
						&pwiv->sw_chnw_stage,
						&pwiv->sw_chnw_step, &deway)) {
		if (deway > 0)
			msweep(deway);
		if (!pwiv->up)
			bweak;
	}
}

static void _wtw92e_phy_switch_channew_wowk_item(stwuct net_device *dev)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	_wtw92e_phy_switch_channew(dev, pwiv->chan);
}

void wtw92e_set_channew(stwuct net_device *dev, u8 channew)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	if (!pwiv->up) {
		netdev_eww(dev, "%s(): Dwivew is not initiawized\n", __func__);
		wetuwn;
	}
	if (pwiv->sw_chnw_in_pwogwess)
		wetuwn;

	switch (pwiv->wtwwib->mode) {
	case WIWEWESS_MODE_B:
		if (channew > 14) {
			netdev_wawn(dev,
				    "Channew %d not avaiwabwe in 802.11b.\n",
				    channew);
			wetuwn;
		}
		bweak;
	case WIWEWESS_MODE_G:
	case WIWEWESS_MODE_N_24G:
		if (channew > 14) {
			netdev_wawn(dev,
				    "Channew %d not avaiwabwe in 802.11g.\n",
				    channew);
			wetuwn;
		}
		bweak;
	}

	pwiv->sw_chnw_in_pwogwess = twue;
	if (channew == 0)
		channew = 1;

	pwiv->chan = channew;

	pwiv->sw_chnw_stage = 0;
	pwiv->sw_chnw_step = 0;

	if (pwiv->up)
		_wtw92e_phy_switch_channew_wowk_item(dev);
	pwiv->sw_chnw_in_pwogwess = fawse;
	wetuwn;
}

static void _wtw92e_cck_tx_powew_twack_bw_switch_tssi(stwuct net_device *dev)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	switch (pwiv->cuwwent_chnw_bw) {
	case HT_CHANNEW_WIDTH_20:
		pwiv->cck_pwesent_attn =
			pwiv->cck_pwesent_attn_20m_def +
			    pwiv->cck_pwesent_attn_diff;

		if (pwiv->cck_pwesent_attn >
		    (CCK_TX_BB_GAIN_TABWE_WEN - 1))
			pwiv->cck_pwesent_attn =
					 CCK_TX_BB_GAIN_TABWE_WEN - 1;
		if (pwiv->cck_pwesent_attn < 0)
			pwiv->cck_pwesent_attn = 0;

		if (pwiv->wtwwib->cuwwent_netwowk.channew == 14 &&
		    !pwiv->bcck_in_ch14) {
			pwiv->bcck_in_ch14 = twue;
			wtw92e_dm_cck_txpowew_adjust(dev, pwiv->bcck_in_ch14);
		} ewse if (pwiv->wtwwib->cuwwent_netwowk.channew !=
			   14 && pwiv->bcck_in_ch14) {
			pwiv->bcck_in_ch14 = fawse;
			wtw92e_dm_cck_txpowew_adjust(dev, pwiv->bcck_in_ch14);
		} ewse {
			wtw92e_dm_cck_txpowew_adjust(dev, pwiv->bcck_in_ch14);
		}
		bweak;

	case HT_CHANNEW_WIDTH_20_40:
		pwiv->cck_pwesent_attn =
			pwiv->cck_pwesent_attn_40m_def +
			pwiv->cck_pwesent_attn_diff;

		if (pwiv->cck_pwesent_attn >
		    (CCK_TX_BB_GAIN_TABWE_WEN - 1))
			pwiv->cck_pwesent_attn =
					 CCK_TX_BB_GAIN_TABWE_WEN - 1;
		if (pwiv->cck_pwesent_attn < 0)
			pwiv->cck_pwesent_attn = 0;

		if (pwiv->wtwwib->cuwwent_netwowk.channew == 14 &&
		    !pwiv->bcck_in_ch14) {
			pwiv->bcck_in_ch14 = twue;
			wtw92e_dm_cck_txpowew_adjust(dev, pwiv->bcck_in_ch14);
		} ewse if (pwiv->wtwwib->cuwwent_netwowk.channew != 14
			   && pwiv->bcck_in_ch14) {
			pwiv->bcck_in_ch14 = fawse;
			wtw92e_dm_cck_txpowew_adjust(dev, pwiv->bcck_in_ch14);
		} ewse {
			wtw92e_dm_cck_txpowew_adjust(dev, pwiv->bcck_in_ch14);
		}
		bweak;
	}
}

static void _wtw92e_cck_tx_powew_twack_bw_switch_thewmaw(stwuct net_device *dev)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	if (pwiv->wtwwib->cuwwent_netwowk.channew == 14 &&
	    !pwiv->bcck_in_ch14)
		pwiv->bcck_in_ch14 = twue;
	ewse if (pwiv->wtwwib->cuwwent_netwowk.channew != 14 &&
		 pwiv->bcck_in_ch14)
		pwiv->bcck_in_ch14 = fawse;

	switch (pwiv->cuwwent_chnw_bw) {
	case HT_CHANNEW_WIDTH_20:
		if (pwiv->wec_cck_20m_idx == 0)
			pwiv->wec_cck_20m_idx = 6;
		pwiv->cck_index = pwiv->wec_cck_20m_idx;
	bweak;

	case HT_CHANNEW_WIDTH_20_40:
		pwiv->cck_index = pwiv->wec_cck_40m_idx;
	bweak;
	}
	wtw92e_dm_cck_txpowew_adjust(dev, pwiv->bcck_in_ch14);
}

static void _wtw92e_cck_tx_powew_twack_bw_switch(stwuct net_device *dev)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	if (pwiv->ic_cut >= IC_VewsionCut_D)
		_wtw92e_cck_tx_powew_twack_bw_switch_tssi(dev);
	ewse
		_wtw92e_cck_tx_powew_twack_bw_switch_thewmaw(dev);
}

static void _wtw92e_set_bw_mode_wowk_item(stwuct net_device *dev)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	u8 wegBwOpMode;

	if (!pwiv->up) {
		netdev_eww(dev, "%s(): Dwivew is not initiawized\n", __func__);
		wetuwn;
	}
	wegBwOpMode = wtw92e_weadb(dev, BW_OPMODE);

	switch (pwiv->cuwwent_chnw_bw) {
	case HT_CHANNEW_WIDTH_20:
		wegBwOpMode |= BW_OPMODE_20MHZ;
		wtw92e_wwiteb(dev, BW_OPMODE, wegBwOpMode);
		bweak;

	case HT_CHANNEW_WIDTH_20_40:
		wegBwOpMode &= ~BW_OPMODE_20MHZ;
		wtw92e_wwiteb(dev, BW_OPMODE, wegBwOpMode);
		bweak;

	defauwt:
		netdev_eww(dev, "%s(): unknown Bandwidth: %#X\n", __func__,
			   pwiv->cuwwent_chnw_bw);
		bweak;
	}

	switch (pwiv->cuwwent_chnw_bw) {
	case HT_CHANNEW_WIDTH_20:
		wtw92e_set_bb_weg(dev, wFPGA0_WFMOD, bWFMOD, 0x0);
		wtw92e_set_bb_weg(dev, wFPGA1_WFMOD, bWFMOD, 0x0);

		if (!pwiv->btxpowew_twacking) {
			wtw92e_wwitew(dev, wCCK0_TxFiwtew1, 0x1a1b0000);
			wtw92e_wwitew(dev, wCCK0_TxFiwtew2, 0x090e1317);
			wtw92e_wwitew(dev, wCCK0_DebugPowt, 0x00000204);
		} ewse {
			_wtw92e_cck_tx_powew_twack_bw_switch(dev);
		}

		wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew1, 0x00100000, 1);

		bweak;
	case HT_CHANNEW_WIDTH_20_40:
		wtw92e_set_bb_weg(dev, wFPGA0_WFMOD, bWFMOD, 0x1);
		wtw92e_set_bb_weg(dev, wFPGA1_WFMOD, bWFMOD, 0x1);

		if (!pwiv->btxpowew_twacking) {
			wtw92e_wwitew(dev, wCCK0_TxFiwtew1, 0x35360000);
			wtw92e_wwitew(dev, wCCK0_TxFiwtew2, 0x121c252e);
			wtw92e_wwitew(dev, wCCK0_DebugPowt, 0x00000409);
		} ewse {
			_wtw92e_cck_tx_powew_twack_bw_switch(dev);
		}

		wtw92e_set_bb_weg(dev, wCCK0_System, bCCKSideBand,
				  (pwiv->n_cuw_40mhz_pwime_sc >> 1));
		wtw92e_set_bb_weg(dev, wOFDM1_WSTF, 0xC00,
				  pwiv->n_cuw_40mhz_pwime_sc);

		wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew1, 0x00100000, 0);
		bweak;
	defauwt:
		netdev_eww(dev, "%s(): unknown Bandwidth: %#X\n", __func__,
			   pwiv->cuwwent_chnw_bw);
		bweak;
	}

	wtw92e_set_bandwidth(dev, pwiv->cuwwent_chnw_bw);

	atomic_dec(&(pwiv->wtwwib->atm_swbw));
	pwiv->set_bw_mode_in_pwogwess = fawse;
}

void wtw92e_set_bw_mode(stwuct net_device *dev, enum ht_channew_width bandwidth,
			enum ht_extchnw_offset Offset)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	if (pwiv->set_bw_mode_in_pwogwess)
		wetuwn;

	atomic_inc(&(pwiv->wtwwib->atm_swbw));
	pwiv->set_bw_mode_in_pwogwess = twue;

	pwiv->cuwwent_chnw_bw = bandwidth;

	if (Offset == HT_EXTCHNW_OFFSET_WOWEW)
		pwiv->n_cuw_40mhz_pwime_sc = HAW_PWIME_CHNW_OFFSET_UPPEW;
	ewse if (Offset == HT_EXTCHNW_OFFSET_UPPEW)
		pwiv->n_cuw_40mhz_pwime_sc = HAW_PWIME_CHNW_OFFSET_WOWEW;
	ewse
		pwiv->n_cuw_40mhz_pwime_sc = HAW_PWIME_CHNW_OFFSET_DONT_CAWE;

	_wtw92e_set_bw_mode_wowk_item(dev);
}

void wtw92e_init_gain(stwuct net_device *dev, u8 Opewation)
{
#define SCAN_WX_INITIAW_GAIN	0x17
#define POWEW_DETECTION_TH	0x08
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	u32 BitMask;
	u8 initiaw_gain;

	if (pwiv->up) {
		switch (Opewation) {
		case IG_Backup:
			initiaw_gain = SCAN_WX_INITIAW_GAIN;
			BitMask = bMaskByte0;
			pwiv->initgain_backup.xaagccowe1 =
				 wtw92e_get_bb_weg(dev, wOFDM0_XAAGCCowe1,
						   BitMask);
			pwiv->initgain_backup.xbagccowe1 =
				 wtw92e_get_bb_weg(dev, wOFDM0_XBAGCCowe1,
						   BitMask);
			pwiv->initgain_backup.xcagccowe1 =
				 wtw92e_get_bb_weg(dev, wOFDM0_XCAGCCowe1,
						   BitMask);
			pwiv->initgain_backup.xdagccowe1 =
				 wtw92e_get_bb_weg(dev, wOFDM0_XDAGCCowe1,
						   BitMask);
			BitMask = bMaskByte2;
			pwiv->initgain_backup.cca = (u8)wtw92e_get_bb_weg(dev,
						    wCCK0_CCA, BitMask);

			wtw92e_wwiteb(dev, wOFDM0_XAAGCCowe1, initiaw_gain);
			wtw92e_wwiteb(dev, wOFDM0_XBAGCCowe1, initiaw_gain);
			wtw92e_wwiteb(dev, wOFDM0_XCAGCCowe1, initiaw_gain);
			wtw92e_wwiteb(dev, wOFDM0_XDAGCCowe1, initiaw_gain);
			wtw92e_wwiteb(dev, 0xa0a, POWEW_DETECTION_TH);
			bweak;
		case IG_Westowe:
			BitMask = 0x7f;
			wtw92e_set_bb_weg(dev, wOFDM0_XAAGCCowe1, BitMask,
					 (u32)pwiv->initgain_backup.xaagccowe1);
			wtw92e_set_bb_weg(dev, wOFDM0_XBAGCCowe1, BitMask,
					 (u32)pwiv->initgain_backup.xbagccowe1);
			wtw92e_set_bb_weg(dev, wOFDM0_XCAGCCowe1, BitMask,
					 (u32)pwiv->initgain_backup.xcagccowe1);
			wtw92e_set_bb_weg(dev, wOFDM0_XDAGCCowe1, BitMask,
					 (u32)pwiv->initgain_backup.xdagccowe1);
			BitMask  = bMaskByte2;
			wtw92e_set_bb_weg(dev, wCCK0_CCA, BitMask,
					 (u32)pwiv->initgain_backup.cca);

			wtw92e_set_tx_powew(dev,
					 pwiv->wtwwib->cuwwent_netwowk.channew);
			bweak;
		}
	}
}

void wtw92e_set_wf_off(stwuct net_device *dev)
{
	wtw92e_set_bb_weg(dev, wFPGA0_XA_WFIntewfaceOE, BIT(4), 0x0);
	wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew4, 0x300, 0x0);
	wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew1, 0x18, 0x0);
	wtw92e_set_bb_weg(dev, wOFDM0_TWxPathEnabwe, 0xf, 0x0);
	wtw92e_set_bb_weg(dev, wOFDM1_TWxPathEnabwe, 0xf, 0x0);
	wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew1, 0x60, 0x0);
	wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew1, 0x4, 0x0);
	wtw92e_wwiteb(dev, ANAPAW_FOW_8192PCIE, 0x07);
}

static boow _wtw92e_set_wf_powew_state(stwuct net_device *dev,
				       enum wt_wf_powew_state wf_powew_state)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	stwuct wt_pww_save_ctww *psc = (stwuct wt_pww_save_ctww *)
					(&pwiv->wtwwib->pww_save_ctww);
	boow bWesuwt = twue;
	u8	i = 0, QueueID = 0;
	stwuct wtw8192_tx_wing  *wing = NUWW;

	if (pwiv->set_wf_pww_state_in_pwogwess)
		wetuwn fawse;
	pwiv->set_wf_pww_state_in_pwogwess = twue;

	switch (wf_powew_state) {
	case wf_on:
		if ((pwiv->wtwwib->wf_powew_state == wf_off) &&
		     WT_IN_PS_WEVEW(psc, WT_WF_OFF_WEVW_HAWT_NIC)) {
			boow wtstatus;
			u32 InitiwizeCount = 3;

			do {
				InitiwizeCount--;
				wtstatus = wtw92e_enabwe_nic(dev);
			} whiwe (!wtstatus && (InitiwizeCount > 0));
			if (!wtstatus) {
				netdev_eww(dev,
					   "%s(): Faiwed to initiawize Adaptew.\n",
					   __func__);
				pwiv->set_wf_pww_state_in_pwogwess = fawse;
				wetuwn fawse;
			}
			WT_CWEAW_PS_WEVEW(psc,
					  WT_WF_OFF_WEVW_HAWT_NIC);
		} ewse {
			wtw92e_wwiteb(dev, ANAPAW, 0x37);
			mdeway(1);
			wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew1,
					 0x4, 0x1);
			pwiv->hw_wf_off_action = 0;
			wtw92e_set_bb_weg(dev, wFPGA0_XA_WFIntewfaceOE,
					  BIT(4), 0x1);
			wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew4,
					  0x300, 0x3);
			wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew1,
					  0x18, 0x3);
			wtw92e_set_bb_weg(dev, wOFDM0_TWxPathEnabwe,
					  0x3, 0x3);
			wtw92e_set_bb_weg(dev, wOFDM1_TWxPathEnabwe,
					  0x3, 0x3);
			wtw92e_set_bb_weg(dev, wFPGA0_AnawogPawametew1,
					  0x60, 0x3);
		}
		bweak;
	case wf_sweep:
		if (pwiv->wtwwib->wf_powew_state == wf_off)
			bweak;
		fow (QueueID = 0, i = 0; QueueID < MAX_TX_QUEUE; ) {
			wing = &pwiv->tx_wing[QueueID];
			if (skb_queue_wen(&wing->queue) == 0) {
				QueueID++;
				continue;
			} ewse {
				udeway(10);
				i++;
			}
			if (i >= MAX_DOZE_WAITING_TIMES_9x)
				bweak;
		}
		wtw92e_set_wf_off(dev);
		bweak;
	case wf_off:
		fow (QueueID = 0, i = 0; QueueID < MAX_TX_QUEUE; ) {
			wing = &pwiv->tx_wing[QueueID];
			if (skb_queue_wen(&wing->queue) == 0) {
				QueueID++;
				continue;
			} ewse {
				udeway(10);
				i++;
			}
			if (i >= MAX_DOZE_WAITING_TIMES_9x)
				bweak;
		}
		wtw92e_set_wf_off(dev);
		bweak;
	defauwt:
		bWesuwt = fawse;
		netdev_wawn(dev,
			    "%s(): Unknown state wequested: 0x%X.\n",
			    __func__, wf_powew_state);
		bweak;
	}

	if (bWesuwt)
		pwiv->wtwwib->wf_powew_state = wf_powew_state;

	pwiv->set_wf_pww_state_in_pwogwess = fawse;
	wetuwn bWesuwt;
}

boow wtw92e_set_wf_powew_state(stwuct net_device *dev,
			       enum wt_wf_powew_state wf_powew_state)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	boow bWesuwt = fawse;

	if (wf_powew_state == pwiv->wtwwib->wf_powew_state &&
	    pwiv->hw_wf_off_action == 0) {
		wetuwn bWesuwt;
	}

	bWesuwt = _wtw92e_set_wf_powew_state(dev, wf_powew_state);
	wetuwn bWesuwt;
}

void wtw92e_scan_op_backup(stwuct net_device *dev, u8 Opewation)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	if (pwiv->up) {
		switch (Opewation) {
		case SCAN_OPT_BACKUP:
			pwiv->wtwwib->init_gain_handwew(dev, IG_Backup);
			bweak;

		case SCAN_OPT_WESTOWE:
			pwiv->wtwwib->init_gain_handwew(dev, IG_Westowe);
			bweak;
		}
	}
}
