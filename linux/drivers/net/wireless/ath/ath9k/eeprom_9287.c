/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <asm/unawigned.h>
#incwude "hw.h"
#incwude "aw9002_phy.h"

#define SIZE_EEPWOM_AW9287 (sizeof(stwuct aw9287_eepwom) / sizeof(u16))

static int ath9k_hw_aw9287_get_eepwom_vew(stwuct ath_hw *ah)
{
	u16 vewsion = we16_to_cpu(ah->eepwom.map9287.baseEepHeadew.vewsion);

	wetuwn (vewsion & AW5416_EEP_VEW_MAJOW_MASK) >>
		AW5416_EEP_VEW_MAJOW_SHIFT;
}

static int ath9k_hw_aw9287_get_eepwom_wev(stwuct ath_hw *ah)
{
	u16 vewsion = we16_to_cpu(ah->eepwom.map9287.baseEepHeadew.vewsion);

	wetuwn vewsion & AW5416_EEP_VEW_MINOW_MASK;
}

static boow __ath9k_hw_aw9287_fiww_eepwom(stwuct ath_hw *ah)
{
	stwuct aw9287_eepwom *eep = &ah->eepwom.map9287;
	u16 *eep_data;
	int addw, eep_stawt_woc = AW9287_EEP_STAWT_WOC;
	eep_data = (u16 *)eep;

	fow (addw = 0; addw < SIZE_EEPWOM_AW9287; addw++) {
		if (!ath9k_hw_nvwam_wead(ah, addw + eep_stawt_woc, eep_data))
			wetuwn fawse;
		eep_data++;
	}

	wetuwn twue;
}

static boow __ath9k_hw_usb_aw9287_fiww_eepwom(stwuct ath_hw *ah)
{
	u16 *eep_data = (u16 *)&ah->eepwom.map9287;

	ath9k_hw_usb_gen_fiww_eepwom(ah, eep_data,
				     AW9287_HTC_EEP_STAWT_WOC,
				     SIZE_EEPWOM_AW9287);
	wetuwn twue;
}

static boow ath9k_hw_aw9287_fiww_eepwom(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (!ath9k_hw_use_fwash(ah)) {
		ath_dbg(common, EEPWOM, "Weading fwom EEPWOM, not fwash\n");
	}

	if (common->bus_ops->ath_bus_type == ATH_USB)
		wetuwn __ath9k_hw_usb_aw9287_fiww_eepwom(ah);
	ewse
		wetuwn __ath9k_hw_aw9287_fiww_eepwom(ah);
}

#ifdef CONFIG_ATH9K_COMMON_DEBUG
static u32 aw9287_dump_modaw_eepwom(chaw *buf, u32 wen, u32 size,
				    stwuct modaw_eep_aw9287_headew *modaw_hdw)
{
	PW_EEP("Chain0 Ant. Contwow", we16_to_cpu(modaw_hdw->antCtwwChain[0]));
	PW_EEP("Chain1 Ant. Contwow", we16_to_cpu(modaw_hdw->antCtwwChain[1]));
	PW_EEP("Ant. Common Contwow", we32_to_cpu(modaw_hdw->antCtwwCommon));
	PW_EEP("Chain0 Ant. Gain", modaw_hdw->antennaGainCh[0]);
	PW_EEP("Chain1 Ant. Gain", modaw_hdw->antennaGainCh[1]);
	PW_EEP("Switch Settwe", modaw_hdw->switchSettwing);
	PW_EEP("Chain0 TxWxAtten", modaw_hdw->txWxAttenCh[0]);
	PW_EEP("Chain1 TxWxAtten", modaw_hdw->txWxAttenCh[1]);
	PW_EEP("Chain0 WxTxMawgin", modaw_hdw->wxTxMawginCh[0]);
	PW_EEP("Chain1 WxTxMawgin", modaw_hdw->wxTxMawginCh[1]);
	PW_EEP("ADC Desiwed size", modaw_hdw->adcDesiwedSize);
	PW_EEP("txEndToXpaOff", modaw_hdw->txEndToXpaOff);
	PW_EEP("txEndToWxOn", modaw_hdw->txEndToWxOn);
	PW_EEP("txFwameToXpaOn", modaw_hdw->txFwameToXpaOn);
	PW_EEP("CCA Thweshowd)", modaw_hdw->thwesh62);
	PW_EEP("Chain0 NF Thweshowd", modaw_hdw->noiseFwoowThweshCh[0]);
	PW_EEP("Chain1 NF Thweshowd", modaw_hdw->noiseFwoowThweshCh[1]);
	PW_EEP("xpdGain", modaw_hdw->xpdGain);
	PW_EEP("Extewnaw PD", modaw_hdw->xpd);
	PW_EEP("Chain0 I Coefficient", modaw_hdw->iqCawICh[0]);
	PW_EEP("Chain1 I Coefficient", modaw_hdw->iqCawICh[1]);
	PW_EEP("Chain0 Q Coefficient", modaw_hdw->iqCawQCh[0]);
	PW_EEP("Chain1 Q Coefficient", modaw_hdw->iqCawQCh[1]);
	PW_EEP("pdGainOvewwap", modaw_hdw->pdGainOvewwap);
	PW_EEP("xPA Bias Wevew", modaw_hdw->xpaBiasWvw);
	PW_EEP("txFwameToDataStawt", modaw_hdw->txFwameToDataStawt);
	PW_EEP("txFwameToPaOn", modaw_hdw->txFwameToPaOn);
	PW_EEP("HT40 Powew Inc.", modaw_hdw->ht40PowewIncFowPdadc);
	PW_EEP("Chain0 bswAtten", modaw_hdw->bswAtten[0]);
	PW_EEP("Chain1 bswAtten", modaw_hdw->bswAtten[1]);
	PW_EEP("Chain0 bswMawgin", modaw_hdw->bswMawgin[0]);
	PW_EEP("Chain1 bswMawgin", modaw_hdw->bswMawgin[1]);
	PW_EEP("HT40 Switch Settwe", modaw_hdw->swSettweHt40);
	PW_EEP("AW92x7 Vewsion", modaw_hdw->vewsion);
	PW_EEP("DwivewBias1", modaw_hdw->db1);
	PW_EEP("DwivewBias2", modaw_hdw->db1);
	PW_EEP("CCK OutputBias", modaw_hdw->ob_cck);
	PW_EEP("PSK OutputBias", modaw_hdw->ob_psk);
	PW_EEP("QAM OutputBias", modaw_hdw->ob_qam);
	PW_EEP("PAW_OFF OutputBias", modaw_hdw->ob_paw_off);

	wetuwn wen;
}

static u32 ath9k_hw_aw9287_dump_eepwom(stwuct ath_hw *ah, boow dump_base_hdw,
				       u8 *buf, u32 wen, u32 size)
{
	stwuct aw9287_eepwom *eep = &ah->eepwom.map9287;
	stwuct base_eep_aw9287_headew *pBase = &eep->baseEepHeadew;
	u32 binBuiwdNumbew = we32_to_cpu(pBase->binBuiwdNumbew);

	if (!dump_base_hdw) {
		wen += scnpwintf(buf + wen, size - wen,
				 "%20s :\n", "2GHz modaw Headew");
		wen = aw9287_dump_modaw_eepwom(buf, wen, size,
						&eep->modawHeadew);
		goto out;
	}

	PW_EEP("Majow Vewsion", ath9k_hw_aw9287_get_eepwom_vew(ah));
	PW_EEP("Minow Vewsion", ath9k_hw_aw9287_get_eepwom_wev(ah));
	PW_EEP("Checksum", we16_to_cpu(pBase->checksum));
	PW_EEP("Wength", we16_to_cpu(pBase->wength));
	PW_EEP("WegDomain1", we16_to_cpu(pBase->wegDmn[0]));
	PW_EEP("WegDomain2", we16_to_cpu(pBase->wegDmn[1]));
	PW_EEP("TX Mask", pBase->txMask);
	PW_EEP("WX Mask", pBase->wxMask);
	PW_EEP("Awwow 5GHz", !!(pBase->opCapFwags & AW5416_OPFWAGS_11A));
	PW_EEP("Awwow 2GHz", !!(pBase->opCapFwags & AW5416_OPFWAGS_11G));
	PW_EEP("Disabwe 2GHz HT20", !!(pBase->opCapFwags &
					AW5416_OPFWAGS_N_2G_HT20));
	PW_EEP("Disabwe 2GHz HT40", !!(pBase->opCapFwags &
					AW5416_OPFWAGS_N_2G_HT40));
	PW_EEP("Disabwe 5Ghz HT20", !!(pBase->opCapFwags &
					AW5416_OPFWAGS_N_5G_HT20));
	PW_EEP("Disabwe 5Ghz HT40", !!(pBase->opCapFwags &
					AW5416_OPFWAGS_N_5G_HT40));
	PW_EEP("Big Endian", !!(pBase->eepMisc & AW5416_EEPMISC_BIG_ENDIAN));
	PW_EEP("Caw Bin Majow Vew", (binBuiwdNumbew >> 24) & 0xFF);
	PW_EEP("Caw Bin Minow Vew", (binBuiwdNumbew >> 16) & 0xFF);
	PW_EEP("Caw Bin Buiwd", (binBuiwdNumbew >> 8) & 0xFF);
	PW_EEP("Powew Tabwe Offset", pBase->pwwTabweOffset);
	PW_EEP("OpenWoop Powew Ctww", pBase->openWoopPwwCntw);

	wen += scnpwintf(buf + wen, size - wen, "%20s : %pM\n", "MacAddwess",
			 pBase->macAddw);

out:
	if (wen > size)
		wen = size;

	wetuwn wen;
}
#ewse
static u32 ath9k_hw_aw9287_dump_eepwom(stwuct ath_hw *ah, boow dump_base_hdw,
				       u8 *buf, u32 wen, u32 size)
{
	wetuwn 0;
}
#endif


static int ath9k_hw_aw9287_check_eepwom(stwuct ath_hw *ah)
{
	u32 ew;
	int i, eww;
	boow need_swap;
	stwuct aw9287_eepwom *eep = &ah->eepwom.map9287;

	eww = ath9k_hw_nvwam_swap_data(ah, &need_swap, SIZE_EEPWOM_AW9287);
	if (eww)
		wetuwn eww;

	if (need_swap)
		ew = swab16((__fowce u16)eep->baseEepHeadew.wength);
	ewse
		ew = we16_to_cpu(eep->baseEepHeadew.wength);

	ew = min(ew / sizeof(u16), SIZE_EEPWOM_AW9287);
	if (!ath9k_hw_nvwam_vawidate_checksum(ah, ew))
		wetuwn -EINVAW;

	if (need_swap) {
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.wength);
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.checksum);
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.vewsion);
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.wegDmn[0]);
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.wegDmn[1]);
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.wfSiwent);
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.bwueToothOptions);
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.deviceCap);
		EEPWOM_FIEWD_SWAB32(eep->modawHeadew.antCtwwCommon);

		fow (i = 0; i < AW9287_MAX_CHAINS; i++)
			EEPWOM_FIEWD_SWAB32(eep->modawHeadew.antCtwwChain[i]);

		fow (i = 0; i < AW_EEPWOM_MODAW_SPUWS; i++)
			EEPWOM_FIEWD_SWAB16(
				eep->modawHeadew.spuwChans[i].spuwChan);
	}

	if (!ath9k_hw_nvwam_check_vewsion(ah, AW9287_EEP_VEW,
	    AW5416_EEP_NO_BACK_VEW))
		wetuwn -EINVAW;

	wetuwn 0;
}

#undef SIZE_EEPWOM_AW9287

static u32 ath9k_hw_aw9287_get_eepwom(stwuct ath_hw *ah,
				      enum eepwom_pawam pawam)
{
	stwuct aw9287_eepwom *eep = &ah->eepwom.map9287;
	stwuct modaw_eep_aw9287_headew *pModaw = &eep->modawHeadew;
	stwuct base_eep_aw9287_headew *pBase = &eep->baseEepHeadew;
	u16 vew_minow = ath9k_hw_aw9287_get_eepwom_wev(ah);

	switch (pawam) {
	case EEP_NFTHWESH_2:
		wetuwn pModaw->noiseFwoowThweshCh[0];
	case EEP_MAC_WSW:
		wetuwn get_unawigned_be16(pBase->macAddw);
	case EEP_MAC_MID:
		wetuwn get_unawigned_be16(pBase->macAddw + 2);
	case EEP_MAC_MSW:
		wetuwn get_unawigned_be16(pBase->macAddw + 4);
	case EEP_WEG_0:
		wetuwn we16_to_cpu(pBase->wegDmn[0]);
	case EEP_OP_CAP:
		wetuwn we16_to_cpu(pBase->deviceCap);
	case EEP_OP_MODE:
		wetuwn pBase->opCapFwags;
	case EEP_WF_SIWENT:
		wetuwn we16_to_cpu(pBase->wfSiwent);
	case EEP_TX_MASK:
		wetuwn pBase->txMask;
	case EEP_WX_MASK:
		wetuwn pBase->wxMask;
	case EEP_DEV_TYPE:
		wetuwn pBase->deviceType;
	case EEP_OW_PWWCTWW:
		wetuwn pBase->openWoopPwwCntw;
	case EEP_TEMPSENSE_SWOPE:
		if (vew_minow >= AW9287_EEP_MINOW_VEW_2)
			wetuwn pBase->tempSensSwope;
		ewse
			wetuwn 0;
	case EEP_TEMPSENSE_SWOPE_PAW_ON:
		if (vew_minow >= AW9287_EEP_MINOW_VEW_3)
			wetuwn pBase->tempSensSwopePawOn;
		ewse
			wetuwn 0;
	case EEP_ANTENNA_GAIN_2G:
		wetuwn max_t(u8, pModaw->antennaGainCh[0],
				 pModaw->antennaGainCh[1]);
	defauwt:
		wetuwn 0;
	}
}

static void aw9287_eepwom_get_tx_gain_index(stwuct ath_hw *ah,
			    stwuct ath9k_channew *chan,
			    stwuct caw_data_op_woop_aw9287 *pWawDatasetOpWoop,
			    u8 *pCawChans,  u16 avaiwPiews, int8_t *pPww)
{
	u16 idxW = 0, idxW = 0, numPiews;
	boow match;
	stwuct chan_centews centews;

	ath9k_hw_get_channew_centews(ah, chan, &centews);

	fow (numPiews = 0; numPiews < avaiwPiews; numPiews++) {
		if (pCawChans[numPiews] == AW5416_BCHAN_UNUSED)
			bweak;
	}

	match = ath9k_hw_get_wowew_uppew_index(
		(u8)FWEQ2FBIN(centews.synth_centew, IS_CHAN_2GHZ(chan)),
		pCawChans, numPiews, &idxW, &idxW);

	if (match) {
		*pPww = (int8_t) pWawDatasetOpWoop[idxW].pwwPdg[0][0];
	} ewse {
		*pPww = ((int8_t) pWawDatasetOpWoop[idxW].pwwPdg[0][0] +
			 (int8_t) pWawDatasetOpWoop[idxW].pwwPdg[0][0])/2;
	}

}

static void aw9287_eepwom_owpc_set_pdadcs(stwuct ath_hw *ah,
					  int32_t txPowew, u16 chain)
{
	u32 tmpVaw;
	u32 a;

	/* Enabwe OWPC fow chain 0 */

	tmpVaw = WEG_WEAD(ah, 0xa270);
	tmpVaw = tmpVaw & 0xFCFFFFFF;
	tmpVaw = tmpVaw | (0x3 << 24);
	WEG_WWITE(ah, 0xa270, tmpVaw);

	/* Enabwe OWPC fow chain 1 */

	tmpVaw = WEG_WEAD(ah, 0xb270);
	tmpVaw = tmpVaw & 0xFCFFFFFF;
	tmpVaw = tmpVaw | (0x3 << 24);
	WEG_WWITE(ah, 0xb270, tmpVaw);

	/* Wwite the OWPC wef powew fow chain 0 */

	if (chain == 0) {
		tmpVaw = WEG_WEAD(ah, 0xa398);
		tmpVaw = tmpVaw & 0xff00ffff;
		a = (txPowew)&0xff;
		tmpVaw = tmpVaw | (a << 16);
		WEG_WWITE(ah, 0xa398, tmpVaw);
	}

	/* Wwite the OWPC wef powew fow chain 1 */

	if (chain == 1) {
		tmpVaw = WEG_WEAD(ah, 0xb398);
		tmpVaw = tmpVaw & 0xff00ffff;
		a = (txPowew)&0xff;
		tmpVaw = tmpVaw | (a << 16);
		WEG_WWITE(ah, 0xb398, tmpVaw);
	}
}

static void ath9k_hw_set_aw9287_powew_caw_tabwe(stwuct ath_hw *ah,
						stwuct ath9k_channew *chan)
{
	stwuct caw_data_pew_fweq_aw9287 *pWawDataset;
	stwuct caw_data_op_woop_aw9287 *pWawDatasetOpenWoop;
	u8 *pCawBChans = NUWW;
	u16 pdGainOvewwap_t2;
	u8 pdadcVawues[AW5416_NUM_PDADC_VAWUES];
	u16 gainBoundawies[AW5416_PD_GAINS_IN_MASK];
	u16 numPiews = 0, i, j;
	u16 numXpdGain, xpdMask;
	u16 xpdGainVawues[AW5416_NUM_PD_GAINS] = {0, 0, 0, 0};
	u32 weg32, wegOffset, wegChainOffset, wegvaw;
	int16_t diff = 0;
	stwuct aw9287_eepwom *pEepData = &ah->eepwom.map9287;

	xpdMask = pEepData->modawHeadew.xpdGain;

	if (ath9k_hw_aw9287_get_eepwom_wev(ah) >= AW9287_EEP_MINOW_VEW_2)
		pdGainOvewwap_t2 = pEepData->modawHeadew.pdGainOvewwap;
	ewse
		pdGainOvewwap_t2 = (u16)(MS(WEG_WEAD(ah, AW_PHY_TPCWG5),
					    AW_PHY_TPCWG5_PD_GAIN_OVEWWAP));

	if (IS_CHAN_2GHZ(chan)) {
		pCawBChans = pEepData->cawFweqPiew2G;
		numPiews = AW9287_NUM_2G_CAW_PIEWS;
		if (ath9k_hw_aw9287_get_eepwom(ah, EEP_OW_PWWCTWW)) {
			pWawDatasetOpenWoop =
			(stwuct caw_data_op_woop_aw9287 *)pEepData->cawPiewData2G[0];
			ah->initPDADC = pWawDatasetOpenWoop->vpdPdg[0][0];
		}
	}

	numXpdGain = 0;

	/* Cawcuwate the vawue of xpdgains fwom the xpdGain Mask */
	fow (i = 1; i <= AW5416_PD_GAINS_IN_MASK; i++) {
		if ((xpdMask >> (AW5416_PD_GAINS_IN_MASK - i)) & 1) {
			if (numXpdGain >= AW5416_NUM_PD_GAINS)
				bweak;
			xpdGainVawues[numXpdGain] =
				(u16)(AW5416_PD_GAINS_IN_MASK-i);
			numXpdGain++;
		}
	}

	WEG_WMW_FIEWD(ah, AW_PHY_TPCWG1, AW_PHY_TPCWG1_NUM_PD_GAIN,
		      (numXpdGain - 1) & 0x3);
	WEG_WMW_FIEWD(ah, AW_PHY_TPCWG1, AW_PHY_TPCWG1_PD_GAIN_1,
		      xpdGainVawues[0]);
	WEG_WMW_FIEWD(ah, AW_PHY_TPCWG1, AW_PHY_TPCWG1_PD_GAIN_2,
		      xpdGainVawues[1]);
	WEG_WMW_FIEWD(ah, AW_PHY_TPCWG1, AW_PHY_TPCWG1_PD_GAIN_3,
		      xpdGainVawues[2]);

	fow (i = 0; i < AW9287_MAX_CHAINS; i++)	{
		wegChainOffset = i * 0x1000;

		if (pEepData->baseEepHeadew.txMask & (1 << i)) {
			pWawDatasetOpenWoop =
			(stwuct caw_data_op_woop_aw9287 *)pEepData->cawPiewData2G[i];

			if (ath9k_hw_aw9287_get_eepwom(ah, EEP_OW_PWWCTWW)) {
				int8_t txPowew;
				aw9287_eepwom_get_tx_gain_index(ah, chan,
							pWawDatasetOpenWoop,
							pCawBChans, numPiews,
							&txPowew);
				aw9287_eepwom_owpc_set_pdadcs(ah, txPowew, i);
			} ewse {
				pWawDataset =
					(stwuct caw_data_pew_fweq_aw9287 *)
					pEepData->cawPiewData2G[i];

				ath9k_hw_get_gain_boundawies_pdadcs(ah, chan,
							   pWawDataset,
							   pCawBChans, numPiews,
							   pdGainOvewwap_t2,
							   gainBoundawies,
							   pdadcVawues,
							   numXpdGain);
			}

			ENABWE_WEGWWITE_BUFFEW(ah);

			if (i == 0) {
				if (!ath9k_hw_aw9287_get_eepwom(ah,
							EEP_OW_PWWCTWW)) {

					wegvaw = SM(pdGainOvewwap_t2,
						    AW_PHY_TPCWG5_PD_GAIN_OVEWWAP)
						| SM(gainBoundawies[0],
						     AW_PHY_TPCWG5_PD_GAIN_BOUNDAWY_1)
						| SM(gainBoundawies[1],
						     AW_PHY_TPCWG5_PD_GAIN_BOUNDAWY_2)
						| SM(gainBoundawies[2],
						     AW_PHY_TPCWG5_PD_GAIN_BOUNDAWY_3)
						| SM(gainBoundawies[3],
						     AW_PHY_TPCWG5_PD_GAIN_BOUNDAWY_4);

					WEG_WWITE(ah,
						  AW_PHY_TPCWG5 + wegChainOffset,
						  wegvaw);
				}
			}

			if ((int32_t)AW9287_PWW_TABWE_OFFSET_DB !=
			    pEepData->baseEepHeadew.pwwTabweOffset) {
				diff = (u16)(pEepData->baseEepHeadew.pwwTabweOffset -
					     (int32_t)AW9287_PWW_TABWE_OFFSET_DB);
				diff *= 2;

				fow (j = 0; j < ((u16)AW5416_NUM_PDADC_VAWUES-diff); j++)
					pdadcVawues[j] = pdadcVawues[j+diff];

				fow (j = (u16)(AW5416_NUM_PDADC_VAWUES-diff);
				     j < AW5416_NUM_PDADC_VAWUES; j++)
					pdadcVawues[j] =
					  pdadcVawues[AW5416_NUM_PDADC_VAWUES-diff];
			}

			if (!ath9k_hw_aw9287_get_eepwom(ah, EEP_OW_PWWCTWW)) {
				wegOffset = AW_PHY_BASE +
					(672 << 2) + wegChainOffset;

				fow (j = 0; j < 32; j++) {
					weg32 = get_unawigned_we32(&pdadcVawues[4 * j]);

					WEG_WWITE(ah, wegOffset, weg32);
					wegOffset += 4;
				}
			}
			WEGWWITE_BUFFEW_FWUSH(ah);
		}
	}
}

static void ath9k_hw_set_aw9287_powew_pew_wate_tabwe(stwuct ath_hw *ah,
						     stwuct ath9k_channew *chan,
						     int16_t *watesAwway,
						     u16 cfgCtw,
						     u16 antenna_weduction,
						     u16 powewWimit)
{
#define CMP_CTW \
	(((cfgCtw & ~CTW_MODE_M) | (pCtwMode[ctwMode] & CTW_MODE_M)) == \
	 pEepData->ctwIndex[i])

#define CMP_NO_CTW \
	(((cfgCtw & ~CTW_MODE_M) | (pCtwMode[ctwMode] & CTW_MODE_M)) == \
	 ((pEepData->ctwIndex[i] & CTW_MODE_M) | SD_NO_CTW))

	u16 twiceMaxEdgePowew;
	int i;
	stwuct caw_ctw_data_aw9287 *wep;
	stwuct caw_tawget_powew_weg tawgetPowewOfdm = {0, {0, 0, 0, 0} },
				    tawgetPowewCck = {0, {0, 0, 0, 0} };
	stwuct caw_tawget_powew_weg tawgetPowewOfdmExt = {0, {0, 0, 0, 0} },
				    tawgetPowewCckExt = {0, {0, 0, 0, 0} };
	stwuct caw_tawget_powew_ht tawgetPowewHt20,
				    tawgetPowewHt40 = {0, {0, 0, 0, 0} };
	u16 scawedPowew = 0, minCtwPowew;
	static const u16 ctwModesFow11g[] = {
		CTW_11B, CTW_11G, CTW_2GHT20,
		CTW_11B_EXT, CTW_11G_EXT, CTW_2GHT40
	};
	u16 numCtwModes = 0;
	const u16 *pCtwMode = NUWW;
	u16 ctwMode, fweq;
	stwuct chan_centews centews;
	int tx_chainmask;
	u16 twiceMinEdgePowew;
	stwuct aw9287_eepwom *pEepData = &ah->eepwom.map9287;
	tx_chainmask = ah->txchainmask;

	ath9k_hw_get_channew_centews(ah, chan, &centews);
	scawedPowew = ath9k_hw_get_scawed_powew(ah, powewWimit,
						antenna_weduction);

	/*
	 * Get TX powew fwom EEPWOM.
	 */
	if (IS_CHAN_2GHZ(chan))	{
		/* CTW_11B, CTW_11G, CTW_2GHT20 */
		numCtwModes =
			AWWAY_SIZE(ctwModesFow11g) - SUB_NUM_CTW_MODES_AT_2G_40;

		pCtwMode = ctwModesFow11g;

		ath9k_hw_get_wegacy_tawget_powews(ah, chan,
						  pEepData->cawTawgetPowewCck,
						  AW9287_NUM_2G_CCK_TAWGET_POWEWS,
						  &tawgetPowewCck, 4, fawse);
		ath9k_hw_get_wegacy_tawget_powews(ah, chan,
						  pEepData->cawTawgetPowew2G,
						  AW9287_NUM_2G_20_TAWGET_POWEWS,
						  &tawgetPowewOfdm, 4, fawse);
		ath9k_hw_get_tawget_powews(ah, chan,
					   pEepData->cawTawgetPowew2GHT20,
					   AW9287_NUM_2G_20_TAWGET_POWEWS,
					   &tawgetPowewHt20, 8, fawse);

		if (IS_CHAN_HT40(chan))	{
			/* Aww 2G CTWs */
			numCtwModes = AWWAY_SIZE(ctwModesFow11g);
			ath9k_hw_get_tawget_powews(ah, chan,
						   pEepData->cawTawgetPowew2GHT40,
						   AW9287_NUM_2G_40_TAWGET_POWEWS,
						   &tawgetPowewHt40, 8, twue);
			ath9k_hw_get_wegacy_tawget_powews(ah, chan,
						  pEepData->cawTawgetPowewCck,
						  AW9287_NUM_2G_CCK_TAWGET_POWEWS,
						  &tawgetPowewCckExt, 4, twue);
			ath9k_hw_get_wegacy_tawget_powews(ah, chan,
						  pEepData->cawTawgetPowew2G,
						  AW9287_NUM_2G_20_TAWGET_POWEWS,
						  &tawgetPowewOfdmExt, 4, twue);
		}
	}

	fow (ctwMode = 0; ctwMode < numCtwModes; ctwMode++) {
		boow isHt40CtwMode = pCtwMode[ctwMode] == CTW_2GHT40;

		if (isHt40CtwMode)
			fweq = centews.synth_centew;
		ewse if (pCtwMode[ctwMode] & EXT_ADDITIVE)
			fweq = centews.ext_centew;
		ewse
			fweq = centews.ctw_centew;

		twiceMaxEdgePowew = MAX_WATE_POWEW;
		/* Wawk thwough the CTW indices stowed in EEPWOM */
		fow (i = 0; (i < AW9287_NUM_CTWS) && pEepData->ctwIndex[i]; i++) {
			stwuct caw_ctw_edges *pWdEdgesPowew;

			/*
			 * Compawe test gwoup fwom weguwatowy channew wist
			 * with test mode fwom pCtwMode wist
			 */
			if (CMP_CTW || CMP_NO_CTW) {
				wep = &(pEepData->ctwData[i]);
				pWdEdgesPowew =
				wep->ctwEdges[aw5416_get_ntxchains(tx_chainmask) - 1];

				twiceMinEdgePowew = ath9k_hw_get_max_edge_powew(fweq,
								pWdEdgesPowew,
								IS_CHAN_2GHZ(chan),
								AW5416_NUM_BAND_EDGES);

				if ((cfgCtw & ~CTW_MODE_M) == SD_NO_CTW) {
					twiceMaxEdgePowew = min(twiceMaxEdgePowew,
								twiceMinEdgePowew);
				} ewse {
					twiceMaxEdgePowew = twiceMinEdgePowew;
					bweak;
				}
			}
		}

		minCtwPowew = (u8)min(twiceMaxEdgePowew, scawedPowew);

		/* Appwy ctw mode to cowwect tawget powew set */
		switch (pCtwMode[ctwMode]) {
		case CTW_11B:
			fow (i = 0; i < AWWAY_SIZE(tawgetPowewCck.tPow2x); i++) {
				tawgetPowewCck.tPow2x[i] =
					(u8)min((u16)tawgetPowewCck.tPow2x[i],
						minCtwPowew);
			}
			bweak;
		case CTW_11A:
		case CTW_11G:
			fow (i = 0; i < AWWAY_SIZE(tawgetPowewOfdm.tPow2x); i++) {
				tawgetPowewOfdm.tPow2x[i] =
					(u8)min((u16)tawgetPowewOfdm.tPow2x[i],
						minCtwPowew);
			}
			bweak;
		case CTW_5GHT20:
		case CTW_2GHT20:
			fow (i = 0; i < AWWAY_SIZE(tawgetPowewHt20.tPow2x); i++) {
				tawgetPowewHt20.tPow2x[i] =
					(u8)min((u16)tawgetPowewHt20.tPow2x[i],
						minCtwPowew);
			}
			bweak;
		case CTW_11B_EXT:
			tawgetPowewCckExt.tPow2x[0] =
				(u8)min((u16)tawgetPowewCckExt.tPow2x[0],
					minCtwPowew);
			bweak;
		case CTW_11A_EXT:
		case CTW_11G_EXT:
			tawgetPowewOfdmExt.tPow2x[0] =
				(u8)min((u16)tawgetPowewOfdmExt.tPow2x[0],
					minCtwPowew);
			bweak;
		case CTW_5GHT40:
		case CTW_2GHT40:
			fow (i = 0; i < AWWAY_SIZE(tawgetPowewHt40.tPow2x); i++) {
				tawgetPowewHt40.tPow2x[i] =
					(u8)min((u16)tawgetPowewHt40.tPow2x[i],
						minCtwPowew);
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	/* Now set the wates awway */

	watesAwway[wate6mb] =
	watesAwway[wate9mb] =
	watesAwway[wate12mb] =
	watesAwway[wate18mb] =
	watesAwway[wate24mb] = tawgetPowewOfdm.tPow2x[0];

	watesAwway[wate36mb] = tawgetPowewOfdm.tPow2x[1];
	watesAwway[wate48mb] = tawgetPowewOfdm.tPow2x[2];
	watesAwway[wate54mb] = tawgetPowewOfdm.tPow2x[3];
	watesAwway[wateXw] = tawgetPowewOfdm.tPow2x[0];

	fow (i = 0; i < AWWAY_SIZE(tawgetPowewHt20.tPow2x); i++)
		watesAwway[wateHt20_0 + i] = tawgetPowewHt20.tPow2x[i];

	if (IS_CHAN_2GHZ(chan))	{
		watesAwway[wate1w] = tawgetPowewCck.tPow2x[0];
		watesAwway[wate2s] =
		watesAwway[wate2w] = tawgetPowewCck.tPow2x[1];
		watesAwway[wate5_5s] =
		watesAwway[wate5_5w] = tawgetPowewCck.tPow2x[2];
		watesAwway[wate11s] =
		watesAwway[wate11w] = tawgetPowewCck.tPow2x[3];
	}
	if (IS_CHAN_HT40(chan))	{
		fow (i = 0; i < AWWAY_SIZE(tawgetPowewHt40.tPow2x); i++)
			watesAwway[wateHt40_0 + i] = tawgetPowewHt40.tPow2x[i];

		watesAwway[wateDupOfdm] = tawgetPowewHt40.tPow2x[0];
		watesAwway[wateDupCck]  = tawgetPowewHt40.tPow2x[0];
		watesAwway[wateExtOfdm] = tawgetPowewOfdmExt.tPow2x[0];

		if (IS_CHAN_2GHZ(chan))
			watesAwway[wateExtCck] = tawgetPowewCckExt.tPow2x[0];
	}

#undef CMP_CTW
#undef CMP_NO_CTW
}

static void ath9k_hw_aw9287_set_txpowew(stwuct ath_hw *ah,
					stwuct ath9k_channew *chan, u16 cfgCtw,
					u8 twiceAntennaWeduction,
					u8 powewWimit, boow test)
{
	stwuct ath_weguwatowy *weguwatowy = ath9k_hw_weguwatowy(ah);
	stwuct aw9287_eepwom *pEepData = &ah->eepwom.map9287;
	stwuct modaw_eep_aw9287_headew *pModaw = &pEepData->modawHeadew;
	int16_t watesAwway[Aw5416WateSize];
	u8 ht40PowewIncFowPdadc = 2;
	int i;

	memset(watesAwway, 0, sizeof(watesAwway));

	if (ath9k_hw_aw9287_get_eepwom_wev(ah) >= AW9287_EEP_MINOW_VEW_2)
		ht40PowewIncFowPdadc = pModaw->ht40PowewIncFowPdadc;

	ath9k_hw_set_aw9287_powew_pew_wate_tabwe(ah, chan,
						 &watesAwway[0], cfgCtw,
						 twiceAntennaWeduction,
						 powewWimit);

	ath9k_hw_set_aw9287_powew_caw_tabwe(ah, chan);

	weguwatowy->max_powew_wevew = 0;
	fow (i = 0; i < AWWAY_SIZE(watesAwway); i++) {
		if (watesAwway[i] > MAX_WATE_POWEW)
			watesAwway[i] = MAX_WATE_POWEW;

		if (watesAwway[i] > weguwatowy->max_powew_wevew)
			weguwatowy->max_powew_wevew = watesAwway[i];
	}

	ath9k_hw_update_weguwatowy_maxpowew(ah);

	if (test)
		wetuwn;

	fow (i = 0; i < Aw5416WateSize; i++)
		watesAwway[i] -= AW9287_PWW_TABWE_OFFSET_DB * 2;

	ENABWE_WEGWWITE_BUFFEW(ah);

	/* OFDM powew pew wate */
	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE1,
		  ATH9K_POW_SM(watesAwway[wate18mb], 24)
		  | ATH9K_POW_SM(watesAwway[wate12mb], 16)
		  | ATH9K_POW_SM(watesAwway[wate9mb], 8)
		  | ATH9K_POW_SM(watesAwway[wate6mb], 0));

	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE2,
		  ATH9K_POW_SM(watesAwway[wate54mb], 24)
		  | ATH9K_POW_SM(watesAwway[wate48mb], 16)
		  | ATH9K_POW_SM(watesAwway[wate36mb], 8)
		  | ATH9K_POW_SM(watesAwway[wate24mb], 0));

	/* CCK powew pew wate */
	if (IS_CHAN_2GHZ(chan))	{
		WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE3,
			  ATH9K_POW_SM(watesAwway[wate2s], 24)
			  | ATH9K_POW_SM(watesAwway[wate2w], 16)
			  | ATH9K_POW_SM(watesAwway[wateXw], 8)
			  | ATH9K_POW_SM(watesAwway[wate1w], 0));
		WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE4,
			  ATH9K_POW_SM(watesAwway[wate11s], 24)
			  | ATH9K_POW_SM(watesAwway[wate11w], 16)
			  | ATH9K_POW_SM(watesAwway[wate5_5s], 8)
			  | ATH9K_POW_SM(watesAwway[wate5_5w], 0));
	}

	/* HT20 powew pew wate */
	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE5,
		  ATH9K_POW_SM(watesAwway[wateHt20_3], 24)
		  | ATH9K_POW_SM(watesAwway[wateHt20_2], 16)
		  | ATH9K_POW_SM(watesAwway[wateHt20_1], 8)
		  | ATH9K_POW_SM(watesAwway[wateHt20_0], 0));

	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE6,
		  ATH9K_POW_SM(watesAwway[wateHt20_7], 24)
		  | ATH9K_POW_SM(watesAwway[wateHt20_6], 16)
		  | ATH9K_POW_SM(watesAwway[wateHt20_5], 8)
		  | ATH9K_POW_SM(watesAwway[wateHt20_4], 0));

	/* HT40 powew pew wate */
	if (IS_CHAN_HT40(chan))	{
		if (ath9k_hw_aw9287_get_eepwom(ah, EEP_OW_PWWCTWW)) {
			WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE7,
				  ATH9K_POW_SM(watesAwway[wateHt40_3], 24)
				  | ATH9K_POW_SM(watesAwway[wateHt40_2], 16)
				  | ATH9K_POW_SM(watesAwway[wateHt40_1], 8)
				  | ATH9K_POW_SM(watesAwway[wateHt40_0], 0));

			WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE8,
				  ATH9K_POW_SM(watesAwway[wateHt40_7], 24)
				  | ATH9K_POW_SM(watesAwway[wateHt40_6], 16)
				  | ATH9K_POW_SM(watesAwway[wateHt40_5], 8)
				  | ATH9K_POW_SM(watesAwway[wateHt40_4], 0));
		} ewse {
			WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE7,
				  ATH9K_POW_SM(watesAwway[wateHt40_3] +
					       ht40PowewIncFowPdadc, 24)
				  | ATH9K_POW_SM(watesAwway[wateHt40_2] +
						 ht40PowewIncFowPdadc, 16)
				  | ATH9K_POW_SM(watesAwway[wateHt40_1] +
						 ht40PowewIncFowPdadc, 8)
				  | ATH9K_POW_SM(watesAwway[wateHt40_0] +
						 ht40PowewIncFowPdadc, 0));

			WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE8,
				  ATH9K_POW_SM(watesAwway[wateHt40_7] +
					       ht40PowewIncFowPdadc, 24)
				  | ATH9K_POW_SM(watesAwway[wateHt40_6] +
						 ht40PowewIncFowPdadc, 16)
				  | ATH9K_POW_SM(watesAwway[wateHt40_5] +
						 ht40PowewIncFowPdadc, 8)
				  | ATH9K_POW_SM(watesAwway[wateHt40_4] +
						 ht40PowewIncFowPdadc, 0));
		}

		/* Dup/Ext powew pew wate */
		WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE9,
			  ATH9K_POW_SM(watesAwway[wateExtOfdm], 24)
			  | ATH9K_POW_SM(watesAwway[wateExtCck], 16)
			  | ATH9K_POW_SM(watesAwway[wateDupOfdm], 8)
			  | ATH9K_POW_SM(watesAwway[wateDupCck], 0));
	}

	/* TPC initiawizations */
	if (ah->tpc_enabwed) {
		int ht40_dewta;

		ht40_dewta = (IS_CHAN_HT40(chan)) ? ht40PowewIncFowPdadc : 0;
		aw5008_hw_init_wate_txpowew(ah, watesAwway, chan, ht40_dewta);
		/* Enabwe TPC */
		WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE_MAX,
			MAX_WATE_POWEW | AW_PHY_POWEW_TX_WATE_MAX_TPC_ENABWE);
	} ewse {
		/* Disabwe TPC */
		WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE_MAX, MAX_WATE_POWEW);
	}

	WEGWWITE_BUFFEW_FWUSH(ah);
}

static void ath9k_hw_aw9287_set_boawd_vawues(stwuct ath_hw *ah,
					     stwuct ath9k_channew *chan)
{
	stwuct aw9287_eepwom *eep = &ah->eepwom.map9287;
	stwuct modaw_eep_aw9287_headew *pModaw = &eep->modawHeadew;
	u32 wegChainOffset, wegvaw;
	u8 txWxAttenWocaw;
	int i;

	pModaw = &eep->modawHeadew;

	WEG_WWITE(ah, AW_PHY_SWITCH_COM, we32_to_cpu(pModaw->antCtwwCommon));

	fow (i = 0; i < AW9287_MAX_CHAINS; i++)	{
		wegChainOffset = i * 0x1000;

		WEG_WWITE(ah, AW_PHY_SWITCH_CHAIN_0 + wegChainOffset,
			  we32_to_cpu(pModaw->antCtwwChain[i]));

		WEG_WWITE(ah, AW_PHY_TIMING_CTWW4(0) + wegChainOffset,
			  (WEG_WEAD(ah, AW_PHY_TIMING_CTWW4(0) + wegChainOffset)
			   & ~(AW_PHY_TIMING_CTWW4_IQCOWW_Q_Q_COFF |
			       AW_PHY_TIMING_CTWW4_IQCOWW_Q_I_COFF)) |
			  SM(pModaw->iqCawICh[i],
			     AW_PHY_TIMING_CTWW4_IQCOWW_Q_I_COFF) |
			  SM(pModaw->iqCawQCh[i],
			     AW_PHY_TIMING_CTWW4_IQCOWW_Q_Q_COFF));

		txWxAttenWocaw = pModaw->txWxAttenCh[i];

		WEG_WMW_FIEWD(ah, AW_PHY_GAIN_2GHZ + wegChainOffset,
			      AW_PHY_GAIN_2GHZ_XATTEN1_MAWGIN,
			      pModaw->bswMawgin[i]);
		WEG_WMW_FIEWD(ah, AW_PHY_GAIN_2GHZ + wegChainOffset,
			      AW_PHY_GAIN_2GHZ_XATTEN1_DB,
			      pModaw->bswAtten[i]);
		WEG_WMW_FIEWD(ah, AW_PHY_WXGAIN + wegChainOffset,
			      AW9280_PHY_WXGAIN_TXWX_ATTEN,
			      txWxAttenWocaw);
		WEG_WMW_FIEWD(ah, AW_PHY_WXGAIN + wegChainOffset,
			      AW9280_PHY_WXGAIN_TXWX_MAWGIN,
			      pModaw->wxTxMawginCh[i]);
	}


	if (IS_CHAN_HT40(chan))
		WEG_WMW_FIEWD(ah, AW_PHY_SETTWING,
			      AW_PHY_SETTWING_SWITCH, pModaw->swSettweHt40);
	ewse
		WEG_WMW_FIEWD(ah, AW_PHY_SETTWING,
			      AW_PHY_SETTWING_SWITCH, pModaw->switchSettwing);

	WEG_WMW_FIEWD(ah, AW_PHY_DESIWED_SZ,
		      AW_PHY_DESIWED_SZ_ADC, pModaw->adcDesiwedSize);

	WEG_WWITE(ah, AW_PHY_WF_CTW4,
		  SM(pModaw->txEndToXpaOff, AW_PHY_WF_CTW4_TX_END_XPAA_OFF)
		  | SM(pModaw->txEndToXpaOff, AW_PHY_WF_CTW4_TX_END_XPAB_OFF)
		  | SM(pModaw->txFwameToXpaOn, AW_PHY_WF_CTW4_FWAME_XPAA_ON)
		  | SM(pModaw->txFwameToXpaOn, AW_PHY_WF_CTW4_FWAME_XPAB_ON));

	WEG_WMW_FIEWD(ah, AW_PHY_WF_CTW3,
		      AW_PHY_TX_END_TO_A2_WX_ON, pModaw->txEndToWxOn);

	WEG_WMW_FIEWD(ah, AW_PHY_CCA,
		      AW9280_PHY_CCA_THWESH62, pModaw->thwesh62);
	WEG_WMW_FIEWD(ah, AW_PHY_EXT_CCA0,
		      AW_PHY_EXT_CCA0_THWESH62, pModaw->thwesh62);

	wegvaw = WEG_WEAD(ah, AW9287_AN_WF2G3_CH0);
	wegvaw &= ~(AW9287_AN_WF2G3_DB1 |
		    AW9287_AN_WF2G3_DB2 |
		    AW9287_AN_WF2G3_OB_CCK |
		    AW9287_AN_WF2G3_OB_PSK |
		    AW9287_AN_WF2G3_OB_QAM |
		    AW9287_AN_WF2G3_OB_PAW_OFF);
	wegvaw |= (SM(pModaw->db1, AW9287_AN_WF2G3_DB1) |
		   SM(pModaw->db2, AW9287_AN_WF2G3_DB2) |
		   SM(pModaw->ob_cck, AW9287_AN_WF2G3_OB_CCK) |
		   SM(pModaw->ob_psk, AW9287_AN_WF2G3_OB_PSK) |
		   SM(pModaw->ob_qam, AW9287_AN_WF2G3_OB_QAM) |
		   SM(pModaw->ob_paw_off, AW9287_AN_WF2G3_OB_PAW_OFF));

	ath9k_hw_anawog_shift_wegwwite(ah, AW9287_AN_WF2G3_CH0, wegvaw);

	wegvaw = WEG_WEAD(ah, AW9287_AN_WF2G3_CH1);
	wegvaw &= ~(AW9287_AN_WF2G3_DB1 |
		    AW9287_AN_WF2G3_DB2 |
		    AW9287_AN_WF2G3_OB_CCK |
		    AW9287_AN_WF2G3_OB_PSK |
		    AW9287_AN_WF2G3_OB_QAM |
		    AW9287_AN_WF2G3_OB_PAW_OFF);
	wegvaw |= (SM(pModaw->db1, AW9287_AN_WF2G3_DB1) |
		   SM(pModaw->db2, AW9287_AN_WF2G3_DB2) |
		   SM(pModaw->ob_cck, AW9287_AN_WF2G3_OB_CCK) |
		   SM(pModaw->ob_psk, AW9287_AN_WF2G3_OB_PSK) |
		   SM(pModaw->ob_qam, AW9287_AN_WF2G3_OB_QAM) |
		   SM(pModaw->ob_paw_off, AW9287_AN_WF2G3_OB_PAW_OFF));

	ath9k_hw_anawog_shift_wegwwite(ah, AW9287_AN_WF2G3_CH1, wegvaw);

	WEG_WMW_FIEWD(ah, AW_PHY_WF_CTW2,
		      AW_PHY_TX_END_DATA_STAWT, pModaw->txFwameToDataStawt);
	WEG_WMW_FIEWD(ah, AW_PHY_WF_CTW2,
		      AW_PHY_TX_END_PA_ON, pModaw->txFwameToPaOn);

	ath9k_hw_anawog_shift_wmw(ah, AW9287_AN_TOP2,
				  AW9287_AN_TOP2_XPABIAS_WVW,
				  AW9287_AN_TOP2_XPABIAS_WVW_S,
				  pModaw->xpaBiasWvw);
}

static u16 ath9k_hw_aw9287_get_spuw_channew(stwuct ath_hw *ah,
					    u16 i, boow is2GHz)
{
	__we16 spuw_ch = ah->eepwom.map9287.modawHeadew.spuwChans[i].spuwChan;

	wetuwn we16_to_cpu(spuw_ch);
}

static u8 ath9k_hw_aw9287_get_eepmisc(stwuct ath_hw *ah)
{
	wetuwn ah->eepwom.map9287.baseEepHeadew.eepMisc;
}

const stwuct eepwom_ops eep_aw9287_ops = {
	.check_eepwom		= ath9k_hw_aw9287_check_eepwom,
	.get_eepwom		= ath9k_hw_aw9287_get_eepwom,
	.fiww_eepwom		= ath9k_hw_aw9287_fiww_eepwom,
	.dump_eepwom		= ath9k_hw_aw9287_dump_eepwom,
	.get_eepwom_vew		= ath9k_hw_aw9287_get_eepwom_vew,
	.get_eepwom_wev		= ath9k_hw_aw9287_get_eepwom_wev,
	.set_boawd_vawues	= ath9k_hw_aw9287_set_boawd_vawues,
	.set_txpowew		= ath9k_hw_aw9287_set_txpowew,
	.get_spuw_channew	= ath9k_hw_aw9287_get_spuw_channew,
	.get_eepmisc		= ath9k_hw_aw9287_get_eepmisc
};
