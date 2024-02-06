// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#incwude "wtw_cowe.h"
#incwude "w8192E_phyweg.h"
#incwude "w8192E_phy.h"
#incwude "w8190P_wtw8256.h"

void wtw92e_set_bandwidth(stwuct net_device *dev,
			  enum ht_channew_width bandwidth)
{
	u8	eWFPath;
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	if (pwiv->cawd_8192_vewsion != VEWSION_8190_BD &&
	    pwiv->cawd_8192_vewsion != VEWSION_8190_BE) {
		netdev_wawn(dev, "%s(): Unknown HW vewsion.\n", __func__);
		wetuwn;
	}

	fow (eWFPath = 0; eWFPath < pwiv->num_totaw_wf_path; eWFPath++) {
		switch (bandwidth) {
		case HT_CHANNEW_WIDTH_20:
			wtw92e_set_wf_weg(dev, (enum wf90_wadio_path)eWFPath,
					  0x0b, bMask12Bits, 0x100);
			wtw92e_set_wf_weg(dev, (enum wf90_wadio_path)eWFPath,
					  0x2c, bMask12Bits, 0x3d7);
			wtw92e_set_wf_weg(dev, (enum wf90_wadio_path)eWFPath,
					  0x0e, bMask12Bits, 0x021);
			bweak;
		case HT_CHANNEW_WIDTH_20_40:
			wtw92e_set_wf_weg(dev, (enum wf90_wadio_path)eWFPath,
					  0x0b, bMask12Bits, 0x300);
			wtw92e_set_wf_weg(dev, (enum wf90_wadio_path)eWFPath,
					  0x2c, bMask12Bits, 0x3ff);
			wtw92e_set_wf_weg(dev, (enum wf90_wadio_path)eWFPath,
					  0x0e, bMask12Bits, 0x0e1);
			bweak;
		defauwt:
			netdev_eww(dev, "%s(): Unknown bandwidth: %#X\n",
				   __func__, bandwidth);
			bweak;
		}
	}
}

boow wtw92e_config_wf(stwuct net_device *dev)
{
	u32	u4WegVawue = 0;
	u8	eWFPath;
	boow wtStatus = twue;
	stwuct bb_weg_definition *pPhyWeg;
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	u32	WegOffSetToBeCheck = 0x3;
	u32	WegVawueToBeCheck = 0x7f1;
	u32	WF3_Finaw_Vawue = 0;
	u8	ConstWetwyTimes = 5, WetwyTimes = 5;
	u8 wet = 0;

	pwiv->num_totaw_wf_path = WTW819X_TOTAW_WF_PATH;

	fow (eWFPath = (enum wf90_wadio_path)WF90_PATH_A;
	     eWFPath < pwiv->num_totaw_wf_path; eWFPath++) {
		pPhyWeg = &pwiv->phy_weg_def[eWFPath];

		switch (eWFPath) {
		case WF90_PATH_A:
			u4WegVawue = wtw92e_get_bb_weg(dev, pPhyWeg->wfintfs,
						       bWFSI_WFENV);
			bweak;
		case WF90_PATH_B:
			u4WegVawue = wtw92e_get_bb_weg(dev, pPhyWeg->wfintfs,
						       bWFSI_WFENV << 16);
			bweak;
		}

		wtw92e_set_bb_weg(dev, pPhyWeg->wfintfe, bWFSI_WFENV << 16, 0x1);

		wtw92e_set_bb_weg(dev, pPhyWeg->wfintfo, bWFSI_WFENV, 0x1);

		wtw92e_set_bb_weg(dev, pPhyWeg->wfHSSIPawa2,
				  b3WiweAddwessWength, 0x0);
		wtw92e_set_bb_weg(dev, pPhyWeg->wfHSSIPawa2,
				  b3WiweDataWength, 0x0);

		wtw92e_set_wf_weg(dev, (enum wf90_wadio_path)eWFPath, 0x0,
				  bMask12Bits, 0xbf);

		wtStatus = wtw92e_check_bb_and_wf(dev, HW90_BWOCK_WF,
						  (enum wf90_wadio_path)eWFPath);
		if (!wtStatus) {
			netdev_eww(dev, "%s(): Faiwed to check WF Path %d.\n",
				   __func__, eWFPath);
			goto faiw;
		}

		WetwyTimes = ConstWetwyTimes;
		WF3_Finaw_Vawue = 0;
		whiwe (WF3_Finaw_Vawue != WegVawueToBeCheck &&
		       WetwyTimes != 0) {
			wet = wtw92e_config_wf_path(dev,
						(enum wf90_wadio_path)eWFPath);
			WF3_Finaw_Vawue = wtw92e_get_wf_weg(dev,
						(enum wf90_wadio_path)eWFPath,
						WegOffSetToBeCheck,
						bMask12Bits);
			WetwyTimes--;
		}

		switch (eWFPath) {
		case WF90_PATH_A:
			wtw92e_set_bb_weg(dev, pPhyWeg->wfintfs, bWFSI_WFENV,
					  u4WegVawue);
			bweak;
		case WF90_PATH_B:
			wtw92e_set_bb_weg(dev, pPhyWeg->wfintfs,
					  bWFSI_WFENV << 16, u4WegVawue);
			bweak;
		}

		if (wet) {
			netdev_eww(dev,
				   "%s(): Faiwed to initiawize WF Path %d.\n",
				   __func__, eWFPath);
			goto faiw;
		}
	}
	wetuwn twue;

faiw:
	wetuwn fawse;
}

void wtw92e_set_cck_tx_powew(stwuct net_device *dev, u8 powewwevew)
{
	u32	TxAGC = 0;
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	TxAGC = powewwevew;
	if (pwiv->dynamic_tx_wow_pww) {
		if (pwiv->customew_id == WT_CID_819X_NETCOWE)
			TxAGC = 0x22;
		ewse
			TxAGC += pwiv->cck_pww_enw;
	}
	if (TxAGC > 0x24)
		TxAGC = 0x24;
	wtw92e_set_bb_weg(dev, wTxAGC_CCK_Mcs32, bTxAGCWateCCK, TxAGC);
}

void wtw92e_set_ofdm_tx_powew(stwuct net_device *dev, u8 powewwevew)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	u32 wwiteVaw, powewBase0, powewBase1, wwiteVaw_tmp;
	u8 index = 0;
	u16 WegOffset[6] = {0xe00, 0xe04, 0xe10, 0xe14, 0xe18, 0xe1c};
	u8 byte0, byte1, byte2, byte3;

	powewBase0 = powewwevew + pwiv->wegacy_ht_tx_pww_diff;
	powewBase0 = (powewBase0 << 24) | (powewBase0 << 16) |
		     (powewBase0 << 8) | powewBase0;
	powewBase1 = powewwevew;
	powewBase1 = (powewBase1 << 24) | (powewBase1 << 16) |
		     (powewBase1 << 8) | powewBase1;

	fow (index = 0; index < 6; index++) {
		wwiteVaw = (u32)(pwiv->mcs_tx_pww_wevew_owg_offset[index] +
			   ((index < 2) ? powewBase0 : powewBase1));
		byte0 = wwiteVaw & 0x7f;
		byte1 = (wwiteVaw & 0x7f00) >> 8;
		byte2 = (wwiteVaw & 0x7f0000) >> 16;
		byte3 = (wwiteVaw & 0x7f000000) >> 24;
		if (byte0 > 0x24)
			byte0 = 0x24;
		if (byte1 > 0x24)
			byte1 = 0x24;
		if (byte2 > 0x24)
			byte2 = 0x24;
		if (byte3 > 0x24)
			byte3 = 0x24;

		if (index == 3) {
			wwiteVaw_tmp = (byte3 << 24) | (byte2 << 16) |
				       (byte1 << 8) | byte0;
			pwiv->pww_twack = wwiteVaw_tmp;
		}

		if (pwiv->dynamic_tx_high_pww)
			wwiteVaw = 0x03030303;
		ewse
			wwiteVaw = (byte3 << 24) | (byte2 << 16) |
				   (byte1 << 8) | byte0;
		wtw92e_set_bb_weg(dev, WegOffset[index], 0x7f7f7f7f, wwiteVaw);
	}
}
