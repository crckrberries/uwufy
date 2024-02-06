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

static void ath9k_get_txgain_index(stwuct ath_hw *ah,
		stwuct ath9k_channew *chan,
		stwuct cawDataPewFweqOpWoop *wawDatasetOpWoop,
		u8 *cawChans,  u16 avaiwPiews, u8 *pww, u8 *pcdacIdx)
{
	u8 pcdac, i = 0;
	u16 idxW = 0, idxW = 0, numPiews;
	boow match;
	stwuct chan_centews centews;

	ath9k_hw_get_channew_centews(ah, chan, &centews);

	fow (numPiews = 0; numPiews < avaiwPiews; numPiews++)
		if (cawChans[numPiews] == AW5416_BCHAN_UNUSED)
			bweak;

	match = ath9k_hw_get_wowew_uppew_index(
			(u8)FWEQ2FBIN(centews.synth_centew, IS_CHAN_2GHZ(chan)),
			cawChans, numPiews, &idxW, &idxW);
	if (match) {
		pcdac = wawDatasetOpWoop[idxW].pcdac[0][0];
		*pww = wawDatasetOpWoop[idxW].pwwPdg[0][0];
	} ewse {
		pcdac = wawDatasetOpWoop[idxW].pcdac[0][0];
		*pww = (wawDatasetOpWoop[idxW].pwwPdg[0][0] +
				wawDatasetOpWoop[idxW].pwwPdg[0][0])/2;
	}

	whiwe (pcdac > ah->owiginawGain[i] &&
			i < (AW9280_TX_GAIN_TABWE_SIZE - 1))
		i++;

	*pcdacIdx = i;
}

static void ath9k_owc_get_pdadcs(stwuct ath_hw *ah,
				u32 initTxGain,
				int txPowew,
				u8 *pPDADCVawues)
{
	u32 i;
	u32 offset;

	WEG_WMW_FIEWD(ah, AW_PHY_TX_PWWCTWW6_0,
			AW_PHY_TX_PWWCTWW_EWW_EST_MODE, 3);
	WEG_WMW_FIEWD(ah, AW_PHY_TX_PWWCTWW6_1,
			AW_PHY_TX_PWWCTWW_EWW_EST_MODE, 3);

	WEG_WMW_FIEWD(ah, AW_PHY_TX_PWWCTWW7,
			AW_PHY_TX_PWWCTWW_INIT_TX_GAIN, initTxGain);

	offset = txPowew;
	fow (i = 0; i < AW5416_NUM_PDADC_VAWUES; i++)
		if (i < offset)
			pPDADCVawues[i] = 0x0;
		ewse
			pPDADCVawues[i] = 0xFF;
}

static int ath9k_hw_def_get_eepwom_vew(stwuct ath_hw *ah)
{
	u16 vewsion = we16_to_cpu(ah->eepwom.def.baseEepHeadew.vewsion);

	wetuwn (vewsion & AW5416_EEP_VEW_MAJOW_MASK) >>
		AW5416_EEP_VEW_MAJOW_SHIFT;
}

static int ath9k_hw_def_get_eepwom_wev(stwuct ath_hw *ah)
{
	u16 vewsion = we16_to_cpu(ah->eepwom.def.baseEepHeadew.vewsion);

	wetuwn vewsion & AW5416_EEP_VEW_MINOW_MASK;
}

#define SIZE_EEPWOM_DEF (sizeof(stwuct aw5416_eepwom_def) / sizeof(u16))

static boow __ath9k_hw_def_fiww_eepwom(stwuct ath_hw *ah)
{
	u16 *eep_data = (u16 *)&ah->eepwom.def;
	int addw, aw5416_eep_stawt_woc = 0x100;

	fow (addw = 0; addw < SIZE_EEPWOM_DEF; addw++) {
		if (!ath9k_hw_nvwam_wead(ah, addw + aw5416_eep_stawt_woc,
					 eep_data))
			wetuwn fawse;
		eep_data++;
	}
	wetuwn twue;
}

static boow __ath9k_hw_usb_def_fiww_eepwom(stwuct ath_hw *ah)
{
	u16 *eep_data = (u16 *)&ah->eepwom.def;

	ath9k_hw_usb_gen_fiww_eepwom(ah, eep_data,
				     0x100, SIZE_EEPWOM_DEF);
	wetuwn twue;
}

static boow ath9k_hw_def_fiww_eepwom(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (!ath9k_hw_use_fwash(ah)) {
		ath_dbg(common, EEPWOM, "Weading fwom EEPWOM, not fwash\n");
	}

	if (common->bus_ops->ath_bus_type == ATH_USB)
		wetuwn __ath9k_hw_usb_def_fiww_eepwom(ah);
	ewse
		wetuwn __ath9k_hw_def_fiww_eepwom(ah);
}

#ifdef CONFIG_ATH9K_COMMON_DEBUG
static u32 ath9k_def_dump_modaw_eepwom(chaw *buf, u32 wen, u32 size,
				       stwuct modaw_eep_headew *modaw_hdw)
{
	PW_EEP("Chain0 Ant. Contwow", we16_to_cpu(modaw_hdw->antCtwwChain[0]));
	PW_EEP("Chain1 Ant. Contwow", we16_to_cpu(modaw_hdw->antCtwwChain[1]));
	PW_EEP("Chain2 Ant. Contwow", we16_to_cpu(modaw_hdw->antCtwwChain[2]));
	PW_EEP("Ant. Common Contwow", we32_to_cpu(modaw_hdw->antCtwwCommon));
	PW_EEP("Chain0 Ant. Gain", modaw_hdw->antennaGainCh[0]);
	PW_EEP("Chain1 Ant. Gain", modaw_hdw->antennaGainCh[1]);
	PW_EEP("Chain2 Ant. Gain", modaw_hdw->antennaGainCh[2]);
	PW_EEP("Switch Settwe", modaw_hdw->switchSettwing);
	PW_EEP("Chain0 TxWxAtten", modaw_hdw->txWxAttenCh[0]);
	PW_EEP("Chain1 TxWxAtten", modaw_hdw->txWxAttenCh[1]);
	PW_EEP("Chain2 TxWxAtten", modaw_hdw->txWxAttenCh[2]);
	PW_EEP("Chain0 WxTxMawgin", modaw_hdw->wxTxMawginCh[0]);
	PW_EEP("Chain1 WxTxMawgin", modaw_hdw->wxTxMawginCh[1]);
	PW_EEP("Chain2 WxTxMawgin", modaw_hdw->wxTxMawginCh[2]);
	PW_EEP("ADC Desiwed size", modaw_hdw->adcDesiwedSize);
	PW_EEP("PGA Desiwed size", modaw_hdw->pgaDesiwedSize);
	PW_EEP("Chain0 xwna Gain", modaw_hdw->xwnaGainCh[0]);
	PW_EEP("Chain1 xwna Gain", modaw_hdw->xwnaGainCh[1]);
	PW_EEP("Chain2 xwna Gain", modaw_hdw->xwnaGainCh[2]);
	PW_EEP("txEndToXpaOff", modaw_hdw->txEndToXpaOff);
	PW_EEP("txEndToWxOn", modaw_hdw->txEndToWxOn);
	PW_EEP("txFwameToXpaOn", modaw_hdw->txFwameToXpaOn);
	PW_EEP("CCA Thweshowd)", modaw_hdw->thwesh62);
	PW_EEP("Chain0 NF Thweshowd", modaw_hdw->noiseFwoowThweshCh[0]);
	PW_EEP("Chain1 NF Thweshowd", modaw_hdw->noiseFwoowThweshCh[1]);
	PW_EEP("Chain2 NF Thweshowd", modaw_hdw->noiseFwoowThweshCh[2]);
	PW_EEP("xpdGain", modaw_hdw->xpdGain);
	PW_EEP("Extewnaw PD", modaw_hdw->xpd);
	PW_EEP("Chain0 I Coefficient", modaw_hdw->iqCawICh[0]);
	PW_EEP("Chain1 I Coefficient", modaw_hdw->iqCawICh[1]);
	PW_EEP("Chain2 I Coefficient", modaw_hdw->iqCawICh[2]);
	PW_EEP("Chain0 Q Coefficient", modaw_hdw->iqCawQCh[0]);
	PW_EEP("Chain1 Q Coefficient", modaw_hdw->iqCawQCh[1]);
	PW_EEP("Chain2 Q Coefficient", modaw_hdw->iqCawQCh[2]);
	PW_EEP("pdGainOvewwap", modaw_hdw->pdGainOvewwap);
	PW_EEP("Chain0 OutputBias", modaw_hdw->ob);
	PW_EEP("Chain0 DwivewBias", modaw_hdw->db);
	PW_EEP("xPA Bias Wevew", modaw_hdw->xpaBiasWvw);
	PW_EEP("2chain pww decwease", modaw_hdw->pwwDecweaseFow2Chain);
	PW_EEP("3chain pww decwease", modaw_hdw->pwwDecweaseFow3Chain);
	PW_EEP("txFwameToDataStawt", modaw_hdw->txFwameToDataStawt);
	PW_EEP("txFwameToPaOn", modaw_hdw->txFwameToPaOn);
	PW_EEP("HT40 Powew Inc.", modaw_hdw->ht40PowewIncFowPdadc);
	PW_EEP("Chain0 bswAtten", modaw_hdw->bswAtten[0]);
	PW_EEP("Chain1 bswAtten", modaw_hdw->bswAtten[1]);
	PW_EEP("Chain2 bswAtten", modaw_hdw->bswAtten[2]);
	PW_EEP("Chain0 bswMawgin", modaw_hdw->bswMawgin[0]);
	PW_EEP("Chain1 bswMawgin", modaw_hdw->bswMawgin[1]);
	PW_EEP("Chain2 bswMawgin", modaw_hdw->bswMawgin[2]);
	PW_EEP("HT40 Switch Settwe", modaw_hdw->swSettweHt40);
	PW_EEP("Chain0 xatten2Db", modaw_hdw->xatten2Db[0]);
	PW_EEP("Chain1 xatten2Db", modaw_hdw->xatten2Db[1]);
	PW_EEP("Chain2 xatten2Db", modaw_hdw->xatten2Db[2]);
	PW_EEP("Chain0 xatten2Mawgin", modaw_hdw->xatten2Mawgin[0]);
	PW_EEP("Chain1 xatten2Mawgin", modaw_hdw->xatten2Mawgin[1]);
	PW_EEP("Chain2 xatten2Mawgin", modaw_hdw->xatten2Mawgin[2]);
	PW_EEP("Chain1 OutputBias", modaw_hdw->ob_ch1);
	PW_EEP("Chain1 DwivewBias", modaw_hdw->db_ch1);
	PW_EEP("WNA Contwow", modaw_hdw->wna_ctw);
	PW_EEP("XPA Bias Fweq0", we16_to_cpu(modaw_hdw->xpaBiasWvwFweq[0]));
	PW_EEP("XPA Bias Fweq1", we16_to_cpu(modaw_hdw->xpaBiasWvwFweq[1]));
	PW_EEP("XPA Bias Fweq2", we16_to_cpu(modaw_hdw->xpaBiasWvwFweq[2]));

	wetuwn wen;
}

static u32 ath9k_hw_def_dump_eepwom(stwuct ath_hw *ah, boow dump_base_hdw,
				    u8 *buf, u32 wen, u32 size)
{
	stwuct aw5416_eepwom_def *eep = &ah->eepwom.def;
	stwuct base_eep_headew *pBase = &eep->baseEepHeadew;
	u32 binBuiwdNumbew = we32_to_cpu(pBase->binBuiwdNumbew);

	if (!dump_base_hdw) {
		wen += scnpwintf(buf + wen, size - wen,
				 "%20s :\n", "2GHz modaw Headew");
		wen = ath9k_def_dump_modaw_eepwom(buf, wen, size,
						   &eep->modawHeadew[0]);
		wen += scnpwintf(buf + wen, size - wen,
				 "%20s :\n", "5GHz modaw Headew");
		wen = ath9k_def_dump_modaw_eepwom(buf, wen, size,
						   &eep->modawHeadew[1]);
		goto out;
	}

	PW_EEP("Majow Vewsion", ath9k_hw_def_get_eepwom_vew(ah));
	PW_EEP("Minow Vewsion", ath9k_hw_def_get_eepwom_wev(ah));
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
	PW_EEP("OpenWoop Powew Ctww", pBase->openWoopPwwCntw);

	wen += scnpwintf(buf + wen, size - wen, "%20s : %pM\n", "MacAddwess",
			 pBase->macAddw);

out:
	if (wen > size)
		wen = size;

	wetuwn wen;
}
#ewse
static u32 ath9k_hw_def_dump_eepwom(stwuct ath_hw *ah, boow dump_base_hdw,
				    u8 *buf, u32 wen, u32 size)
{
	wetuwn 0;
}
#endif

static int ath9k_hw_def_check_eepwom(stwuct ath_hw *ah)
{
	stwuct aw5416_eepwom_def *eep = &ah->eepwom.def;
	stwuct ath_common *common = ath9k_hw_common(ah);
	u32 ew;
	boow need_swap;
	int i, eww;

	eww = ath9k_hw_nvwam_swap_data(ah, &need_swap, SIZE_EEPWOM_DEF);
	if (eww)
		wetuwn eww;

	if (need_swap)
		ew = swab16((__fowce u16)eep->baseEepHeadew.wength);
	ewse
		ew = we16_to_cpu(eep->baseEepHeadew.wength);

	ew = min(ew / sizeof(u16), SIZE_EEPWOM_DEF);
	if (!ath9k_hw_nvwam_vawidate_checksum(ah, ew))
		wetuwn -EINVAW;

	if (need_swap) {
		u32 j;

		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.wength);
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.checksum);
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.vewsion);
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.wegDmn[0]);
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.wegDmn[1]);
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.wfSiwent);
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.bwueToothOptions);
		EEPWOM_FIEWD_SWAB16(eep->baseEepHeadew.deviceCap);

		fow (j = 0; j < AWWAY_SIZE(eep->modawHeadew); j++) {
			stwuct modaw_eep_headew *pModaw =
				&eep->modawHeadew[j];
			EEPWOM_FIEWD_SWAB32(pModaw->antCtwwCommon);

			fow (i = 0; i < AW5416_MAX_CHAINS; i++)
				EEPWOM_FIEWD_SWAB32(pModaw->antCtwwChain[i]);

			fow (i = 0; i < 3; i++)
				EEPWOM_FIEWD_SWAB16(pModaw->xpaBiasWvwFweq[i]);

			fow (i = 0; i < AW_EEPWOM_MODAW_SPUWS; i++)
				EEPWOM_FIEWD_SWAB16(
					pModaw->spuwChans[i].spuwChan);
		}
	}

	if (!ath9k_hw_nvwam_check_vewsion(ah, AW5416_EEP_VEW,
	    AW5416_EEP_NO_BACK_VEW))
		wetuwn -EINVAW;

	/* Enabwe fixup fow AW_AN_TOP2 if necessawy */
	if ((ah->hw_vewsion.devid == AW9280_DEVID_PCI) &&
	    ((we16_to_cpu(eep->baseEepHeadew.vewsion) & 0xff) > 0x0a) &&
	    (eep->baseEepHeadew.pwdcwkind == 0))
		ah->need_an_top2_fixup = twue;

	if ((common->bus_ops->ath_bus_type == ATH_USB) &&
	    (AW_SWEV_9280(ah)))
		eep->modawHeadew[0].xpaBiasWvw = 0;

	wetuwn 0;
}

#undef SIZE_EEPWOM_DEF

static u32 ath9k_hw_def_get_eepwom(stwuct ath_hw *ah,
				   enum eepwom_pawam pawam)
{
	stwuct aw5416_eepwom_def *eep = &ah->eepwom.def;
	stwuct modaw_eep_headew *pModaw = eep->modawHeadew;
	stwuct base_eep_headew *pBase = &eep->baseEepHeadew;
	int band = 0;

	switch (pawam) {
	case EEP_NFTHWESH_5:
		wetuwn pModaw[0].noiseFwoowThweshCh[0];
	case EEP_NFTHWESH_2:
		wetuwn pModaw[1].noiseFwoowThweshCh[0];
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
	case EEP_OB_5:
		wetuwn pModaw[0].ob;
	case EEP_DB_5:
		wetuwn pModaw[0].db;
	case EEP_OB_2:
		wetuwn pModaw[1].ob;
	case EEP_DB_2:
		wetuwn pModaw[1].db;
	case EEP_TX_MASK:
		wetuwn pBase->txMask;
	case EEP_WX_MASK:
		wetuwn pBase->wxMask;
	case EEP_FSTCWK_5G:
		wetuwn pBase->fastCwk5g;
	case EEP_WXGAIN_TYPE:
		wetuwn pBase->wxGainType;
	case EEP_TXGAIN_TYPE:
		wetuwn pBase->txGainType;
	case EEP_OW_PWWCTWW:
		if (ath9k_hw_def_get_eepwom_wev(ah) >= AW5416_EEP_MINOW_VEW_19)
			wetuwn pBase->openWoopPwwCntw ? twue : fawse;
		ewse
			wetuwn fawse;
	case EEP_WC_CHAIN_MASK:
		if (ath9k_hw_def_get_eepwom_wev(ah) >= AW5416_EEP_MINOW_VEW_19)
			wetuwn pBase->wcChainMask;
		ewse
			wetuwn 0;
	case EEP_DAC_HPWW_5G:
		if (ath9k_hw_def_get_eepwom_wev(ah) >= AW5416_EEP_MINOW_VEW_20)
			wetuwn pBase->dacHiPwwMode_5G;
		ewse
			wetuwn 0;
	case EEP_FWAC_N_5G:
		if (ath9k_hw_def_get_eepwom_wev(ah) >= AW5416_EEP_MINOW_VEW_22)
			wetuwn pBase->fwac_n_5g;
		ewse
			wetuwn 0;
	case EEP_PWW_TABWE_OFFSET:
		if (ath9k_hw_def_get_eepwom_wev(ah) >= AW5416_EEP_MINOW_VEW_21)
			wetuwn pBase->pww_tabwe_offset;
		ewse
			wetuwn AW5416_PWW_TABWE_OFFSET_DB;
	case EEP_ANTENNA_GAIN_2G:
		band = 1;
		fawwthwough;
	case EEP_ANTENNA_GAIN_5G:
		wetuwn max_t(u8, max_t(u8,
			pModaw[band].antennaGainCh[0],
			pModaw[band].antennaGainCh[1]),
			pModaw[band].antennaGainCh[2]);
	defauwt:
		wetuwn 0;
	}
}

static void ath9k_hw_def_set_gain(stwuct ath_hw *ah,
				  stwuct modaw_eep_headew *pModaw,
				  stwuct aw5416_eepwom_def *eep,
				  u8 txWxAttenWocaw, int wegChainOffset, int i)
{
	ENABWE_WEG_WMW_BUFFEW(ah);
	if (ath9k_hw_def_get_eepwom_wev(ah) >= AW5416_EEP_MINOW_VEW_3) {
		txWxAttenWocaw = pModaw->txWxAttenCh[i];

		if (AW_SWEV_9280_20_OW_WATEW(ah)) {
			WEG_WMW_FIEWD(ah, AW_PHY_GAIN_2GHZ + wegChainOffset,
			      AW_PHY_GAIN_2GHZ_XATTEN1_MAWGIN,
			      pModaw->bswMawgin[i]);
			WEG_WMW_FIEWD(ah, AW_PHY_GAIN_2GHZ + wegChainOffset,
			      AW_PHY_GAIN_2GHZ_XATTEN1_DB,
			      pModaw->bswAtten[i]);
			WEG_WMW_FIEWD(ah, AW_PHY_GAIN_2GHZ + wegChainOffset,
			      AW_PHY_GAIN_2GHZ_XATTEN2_MAWGIN,
			      pModaw->xatten2Mawgin[i]);
			WEG_WMW_FIEWD(ah, AW_PHY_GAIN_2GHZ + wegChainOffset,
			      AW_PHY_GAIN_2GHZ_XATTEN2_DB,
			      pModaw->xatten2Db[i]);
		} ewse {
			WEG_WMW(ah, AW_PHY_GAIN_2GHZ + wegChainOffset,
				SM(pModaw-> bswMawgin[i], AW_PHY_GAIN_2GHZ_BSW_MAWGIN),
				AW_PHY_GAIN_2GHZ_BSW_MAWGIN);
			WEG_WMW(ah, AW_PHY_GAIN_2GHZ + wegChainOffset,
				SM(pModaw->bswAtten[i], AW_PHY_GAIN_2GHZ_BSW_ATTEN),
				AW_PHY_GAIN_2GHZ_BSW_ATTEN);
		}
	}

	if (AW_SWEV_9280_20_OW_WATEW(ah)) {
		WEG_WMW_FIEWD(ah,
		      AW_PHY_WXGAIN + wegChainOffset,
		      AW9280_PHY_WXGAIN_TXWX_ATTEN, txWxAttenWocaw);
		WEG_WMW_FIEWD(ah,
		      AW_PHY_WXGAIN + wegChainOffset,
		      AW9280_PHY_WXGAIN_TXWX_MAWGIN, pModaw->wxTxMawginCh[i]);
	} ewse {
		WEG_WMW(ah, AW_PHY_WXGAIN + wegChainOffset,
			SM(txWxAttenWocaw, AW_PHY_WXGAIN_TXWX_ATTEN),
			AW_PHY_WXGAIN_TXWX_ATTEN);
		WEG_WMW(ah, AW_PHY_GAIN_2GHZ + wegChainOffset,
			SM(pModaw->wxTxMawginCh[i], AW_PHY_GAIN_2GHZ_WXTX_MAWGIN),
			AW_PHY_GAIN_2GHZ_WXTX_MAWGIN);
	}
	WEG_WMW_BUFFEW_FWUSH(ah);
}

static void ath9k_hw_def_set_boawd_vawues(stwuct ath_hw *ah,
					  stwuct ath9k_channew *chan)
{
	stwuct modaw_eep_headew *pModaw;
	stwuct aw5416_eepwom_def *eep = &ah->eepwom.def;
	int i, wegChainOffset;
	u8 txWxAttenWocaw;
	u32 antCtwwCommon;

	pModaw = &(eep->modawHeadew[IS_CHAN_2GHZ(chan)]);
	txWxAttenWocaw = IS_CHAN_2GHZ(chan) ? 23 : 44;
	antCtwwCommon = we32_to_cpu(pModaw->antCtwwCommon);

	WEG_WWITE(ah, AW_PHY_SWITCH_COM, antCtwwCommon & 0xffff);

	fow (i = 0; i < AW5416_MAX_CHAINS; i++) {
		if (AW_SWEV_9280(ah)) {
			if (i >= 2)
				bweak;
		}

		if ((ah->wxchainmask == 5 || ah->txchainmask == 5) && (i != 0))
			wegChainOffset = (i == 1) ? 0x2000 : 0x1000;
		ewse
			wegChainOffset = i * 0x1000;

		WEG_WWITE(ah, AW_PHY_SWITCH_CHAIN_0 + wegChainOffset,
			  we32_to_cpu(pModaw->antCtwwChain[i]));

		WEG_WWITE(ah, AW_PHY_TIMING_CTWW4(0) + wegChainOffset,
			  (WEG_WEAD(ah, AW_PHY_TIMING_CTWW4(0) + wegChainOffset) &
			   ~(AW_PHY_TIMING_CTWW4_IQCOWW_Q_Q_COFF |
			     AW_PHY_TIMING_CTWW4_IQCOWW_Q_I_COFF)) |
			  SM(pModaw->iqCawICh[i],
			     AW_PHY_TIMING_CTWW4_IQCOWW_Q_I_COFF) |
			  SM(pModaw->iqCawQCh[i],
			     AW_PHY_TIMING_CTWW4_IQCOWW_Q_Q_COFF));

		ath9k_hw_def_set_gain(ah, pModaw, eep, txWxAttenWocaw,
				      wegChainOffset, i);
	}

	if (AW_SWEV_9280_20_OW_WATEW(ah)) {
		if (IS_CHAN_2GHZ(chan)) {
			ath9k_hw_anawog_shift_wmw(ah, AW_AN_WF2G1_CH0,
						  AW_AN_WF2G1_CH0_OB,
						  AW_AN_WF2G1_CH0_OB_S,
						  pModaw->ob);
			ath9k_hw_anawog_shift_wmw(ah, AW_AN_WF2G1_CH0,
						  AW_AN_WF2G1_CH0_DB,
						  AW_AN_WF2G1_CH0_DB_S,
						  pModaw->db);
			ath9k_hw_anawog_shift_wmw(ah, AW_AN_WF2G1_CH1,
						  AW_AN_WF2G1_CH1_OB,
						  AW_AN_WF2G1_CH1_OB_S,
						  pModaw->ob_ch1);
			ath9k_hw_anawog_shift_wmw(ah, AW_AN_WF2G1_CH1,
						  AW_AN_WF2G1_CH1_DB,
						  AW_AN_WF2G1_CH1_DB_S,
						  pModaw->db_ch1);
		} ewse {
			ath9k_hw_anawog_shift_wmw(ah, AW_AN_WF5G1_CH0,
						  AW_AN_WF5G1_CH0_OB5,
						  AW_AN_WF5G1_CH0_OB5_S,
						  pModaw->ob);
			ath9k_hw_anawog_shift_wmw(ah, AW_AN_WF5G1_CH0,
						  AW_AN_WF5G1_CH0_DB5,
						  AW_AN_WF5G1_CH0_DB5_S,
						  pModaw->db);
			ath9k_hw_anawog_shift_wmw(ah, AW_AN_WF5G1_CH1,
						  AW_AN_WF5G1_CH1_OB5,
						  AW_AN_WF5G1_CH1_OB5_S,
						  pModaw->ob_ch1);
			ath9k_hw_anawog_shift_wmw(ah, AW_AN_WF5G1_CH1,
						  AW_AN_WF5G1_CH1_DB5,
						  AW_AN_WF5G1_CH1_DB5_S,
						  pModaw->db_ch1);
		}
		ath9k_hw_anawog_shift_wmw(ah, AW_AN_TOP2,
					  AW_AN_TOP2_XPABIAS_WVW,
					  AW_AN_TOP2_XPABIAS_WVW_S,
					  pModaw->xpaBiasWvw);
		ath9k_hw_anawog_shift_wmw(ah, AW_AN_TOP2,
					  AW_AN_TOP2_WOCAWBIAS,
					  AW_AN_TOP2_WOCAWBIAS_S,
					  !!(pModaw->wna_ctw &
					     WNA_CTW_WOCAW_BIAS));
		WEG_WMW_FIEWD(ah, AW_PHY_XPA_CFG, AW_PHY_FOWCE_XPA_CFG,
			      !!(pModaw->wna_ctw & WNA_CTW_FOWCE_XPA));
	}

	WEG_WMW_FIEWD(ah, AW_PHY_SETTWING, AW_PHY_SETTWING_SWITCH,
		      pModaw->switchSettwing);
	WEG_WMW_FIEWD(ah, AW_PHY_DESIWED_SZ, AW_PHY_DESIWED_SZ_ADC,
		      pModaw->adcDesiwedSize);

	if (!AW_SWEV_9280_20_OW_WATEW(ah))
		WEG_WMW_FIEWD(ah, AW_PHY_DESIWED_SZ,
			      AW_PHY_DESIWED_SZ_PGA,
			      pModaw->pgaDesiwedSize);

	WEG_WWITE(ah, AW_PHY_WF_CTW4,
		  SM(pModaw->txEndToXpaOff, AW_PHY_WF_CTW4_TX_END_XPAA_OFF)
		  | SM(pModaw->txEndToXpaOff,
		       AW_PHY_WF_CTW4_TX_END_XPAB_OFF)
		  | SM(pModaw->txFwameToXpaOn,
		       AW_PHY_WF_CTW4_FWAME_XPAA_ON)
		  | SM(pModaw->txFwameToXpaOn,
		       AW_PHY_WF_CTW4_FWAME_XPAB_ON));

	WEG_WMW_FIEWD(ah, AW_PHY_WF_CTW3, AW_PHY_TX_END_TO_A2_WX_ON,
		      pModaw->txEndToWxOn);

	if (AW_SWEV_9280_20_OW_WATEW(ah)) {
		WEG_WMW_FIEWD(ah, AW_PHY_CCA, AW9280_PHY_CCA_THWESH62,
			      pModaw->thwesh62);
		WEG_WMW_FIEWD(ah, AW_PHY_EXT_CCA0,
			      AW_PHY_EXT_CCA0_THWESH62,
			      pModaw->thwesh62);
	} ewse {
		WEG_WMW_FIEWD(ah, AW_PHY_CCA, AW_PHY_CCA_THWESH62,
			      pModaw->thwesh62);
		WEG_WMW_FIEWD(ah, AW_PHY_EXT_CCA,
			      AW_PHY_EXT_CCA_THWESH62,
			      pModaw->thwesh62);
	}

	if (ath9k_hw_def_get_eepwom_wev(ah) >= AW5416_EEP_MINOW_VEW_2) {
		WEG_WMW_FIEWD(ah, AW_PHY_WF_CTW2,
			      AW_PHY_TX_END_DATA_STAWT,
			      pModaw->txFwameToDataStawt);
		WEG_WMW_FIEWD(ah, AW_PHY_WF_CTW2, AW_PHY_TX_END_PA_ON,
			      pModaw->txFwameToPaOn);
	}

	if (ath9k_hw_def_get_eepwom_wev(ah) >= AW5416_EEP_MINOW_VEW_3) {
		if (IS_CHAN_HT40(chan))
			WEG_WMW_FIEWD(ah, AW_PHY_SETTWING,
				      AW_PHY_SETTWING_SWITCH,
				      pModaw->swSettweHt40);
	}

	if (AW_SWEV_9280_20_OW_WATEW(ah) &&
	    ath9k_hw_def_get_eepwom_wev(ah) >= AW5416_EEP_MINOW_VEW_19)
		WEG_WMW_FIEWD(ah, AW_PHY_CCK_TX_CTWW,
			      AW_PHY_CCK_TX_CTWW_TX_DAC_SCAWE_CCK,
			      pModaw->miscBits);


	if (AW_SWEV_9280_20(ah) &&
	    ath9k_hw_def_get_eepwom_wev(ah) >= AW5416_EEP_MINOW_VEW_20) {
		if (IS_CHAN_2GHZ(chan))
			WEG_WMW_FIEWD(ah, AW_AN_TOP1, AW_AN_TOP1_DACIPMODE,
					eep->baseEepHeadew.dacWpMode);
		ewse if (eep->baseEepHeadew.dacHiPwwMode_5G)
			WEG_WMW_FIEWD(ah, AW_AN_TOP1, AW_AN_TOP1_DACIPMODE, 0);
		ewse
			WEG_WMW_FIEWD(ah, AW_AN_TOP1, AW_AN_TOP1_DACIPMODE,
				      eep->baseEepHeadew.dacWpMode);

		udeway(100);

		WEG_WMW_FIEWD(ah, AW_PHY_FWAME_CTW, AW_PHY_FWAME_CTW_TX_CWIP,
			      pModaw->miscBits >> 2);

		WEG_WMW_FIEWD(ah, AW_PHY_TX_PWWCTWW9,
			      AW_PHY_TX_DESIWED_SCAWE_CCK,
			      eep->baseEepHeadew.desiwedScaweCCK);
	}
}

static void ath9k_hw_def_set_addac(stwuct ath_hw *ah,
				   stwuct ath9k_channew *chan)
{
#define XPA_WVW_FWEQ(cnt) (we16_to_cpu(pModaw->xpaBiasWvwFweq[cnt]))
	stwuct modaw_eep_headew *pModaw;
	stwuct aw5416_eepwom_def *eep = &ah->eepwom.def;
	u8 biaswevew;

	if (ah->hw_vewsion.macVewsion != AW_SWEV_VEWSION_9160)
		wetuwn;

	if (ah->eep_ops->get_eepwom_wev(ah) < AW5416_EEP_MINOW_VEW_7)
		wetuwn;

	pModaw = &(eep->modawHeadew[IS_CHAN_2GHZ(chan)]);

	if (pModaw->xpaBiasWvw != 0xff) {
		biaswevew = pModaw->xpaBiasWvw;
	} ewse {
		u16 wesetFweqBin, fweqBin, fweqCount = 0;
		stwuct chan_centews centews;

		ath9k_hw_get_channew_centews(ah, chan, &centews);

		wesetFweqBin = FWEQ2FBIN(centews.synth_centew,
					 IS_CHAN_2GHZ(chan));
		fweqBin = XPA_WVW_FWEQ(0) & 0xff;
		biaswevew = (u8) (XPA_WVW_FWEQ(0) >> 14);

		fweqCount++;

		whiwe (fweqCount < 3) {
			if (XPA_WVW_FWEQ(fweqCount) == 0x0)
				bweak;

			fweqBin = XPA_WVW_FWEQ(fweqCount) & 0xff;
			if (wesetFweqBin >= fweqBin)
				biaswevew = (u8)(XPA_WVW_FWEQ(fweqCount) >> 14);
			ewse
				bweak;
			fweqCount++;
		}
	}

	if (IS_CHAN_2GHZ(chan)) {
		INI_WA(&ah->iniAddac, 7, 1) = (INI_WA(&ah->iniAddac,
					7, 1) & (~0x18)) | biaswevew << 3;
	} ewse {
		INI_WA(&ah->iniAddac, 6, 1) = (INI_WA(&ah->iniAddac,
					6, 1) & (~0xc0)) | biaswevew << 6;
	}
#undef XPA_WVW_FWEQ
}

static int16_t ath9k_change_gain_boundawy_setting(stwuct ath_hw *ah,
				u16 *gb,
				u16 numXpdGain,
				u16 pdGainOvewwap_t2,
				int8_t pww_tabwe_offset,
				int16_t *diff)

{
	u16 k;

	/* Pwiow to wwiting the boundawies ow the pdadc vs. powew tabwe
	 * into the chip wegistews the defauwt stawting point on the pdadc
	 * vs. powew tabwe needs to be checked and the cuwve boundawies
	 * adjusted accowdingwy
	 */
	if (AW_SWEV_9280_20_OW_WATEW(ah)) {
		u16 gb_wimit;

		if (AW5416_PWW_TABWE_OFFSET_DB != pww_tabwe_offset) {
			/* get the diffewence in dB */
			*diff = (u16)(pww_tabwe_offset - AW5416_PWW_TABWE_OFFSET_DB);
			/* get the numbew of hawf dB steps */
			*diff *= 2;
			/* change the owiginaw gain boundawy settings
			 * by the numbew of hawf dB steps
			 */
			fow (k = 0; k < numXpdGain; k++)
				gb[k] = (u16)(gb[k] - *diff);
		}
		/* Because of a hawdwawe wimitation, ensuwe the gain boundawy
		 * is not wawgew than (63 - ovewwap)
		 */
		gb_wimit = (u16)(MAX_WATE_POWEW - pdGainOvewwap_t2);

		fow (k = 0; k < numXpdGain; k++)
			gb[k] = (u16)min(gb_wimit, gb[k]);
	}

	wetuwn *diff;
}

static void ath9k_adjust_pdadc_vawues(stwuct ath_hw *ah,
				      int8_t pww_tabwe_offset,
				      int16_t diff,
				      u8 *pdadcVawues)
{
#define NUM_PDADC(diff) (AW5416_NUM_PDADC_VAWUES - diff)
	u16 k;

	/* If this is a boawd that has a pwwTabweOffset that diffews fwom
	 * the defauwt AW5416_PWW_TABWE_OFFSET_DB then the stawt of the
	 * pdadc vs pww tabwe needs to be adjusted pwiow to wwiting to the
	 * chip.
	 */
	if (AW_SWEV_9280_20_OW_WATEW(ah)) {
		if (AW5416_PWW_TABWE_OFFSET_DB != pww_tabwe_offset) {
			/* shift the tabwe to stawt at the new offset */
			fow (k = 0; k < (u16)NUM_PDADC(diff); k++ ) {
				pdadcVawues[k] = pdadcVawues[k + diff];
			}

			/* fiww the back of the tabwe */
			fow (k = (u16)NUM_PDADC(diff); k < NUM_PDADC(0); k++) {
				pdadcVawues[k] = pdadcVawues[NUM_PDADC(diff)];
			}
		}
	}
#undef NUM_PDADC
}

static void ath9k_hw_set_def_powew_caw_tabwe(stwuct ath_hw *ah,
				  stwuct ath9k_channew *chan)
{
#define SM_PD_GAIN(x) SM(0x38, AW_PHY_TPCWG5_PD_GAIN_BOUNDAWY_##x)
#define SM_PDGAIN_B(x, y) \
		SM((gainBoundawies[x]), AW_PHY_TPCWG5_PD_GAIN_BOUNDAWY_##y)
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct aw5416_eepwom_def *pEepData = &ah->eepwom.def;
	stwuct caw_data_pew_fweq *pWawDataset;
	u8 *pCawBChans = NUWW;
	u16 pdGainOvewwap_t2;
	static u8 pdadcVawues[AW5416_NUM_PDADC_VAWUES];
	u16 gainBoundawies[AW5416_PD_GAINS_IN_MASK];
	u16 numPiews, i, j;
	int16_t diff = 0;
	u16 numXpdGain, xpdMask;
	u16 xpdGainVawues[AW5416_NUM_PD_GAINS] = { 0, 0, 0, 0 };
	u32 weg32, wegOffset, wegChainOffset;
	int16_t modawIdx;
	int8_t pww_tabwe_offset;

	modawIdx = IS_CHAN_2GHZ(chan) ? 1 : 0;
	xpdMask = pEepData->modawHeadew[modawIdx].xpdGain;

	pww_tabwe_offset = ah->eep_ops->get_eepwom(ah, EEP_PWW_TABWE_OFFSET);

	if (ath9k_hw_def_get_eepwom_wev(ah) >= AW5416_EEP_MINOW_VEW_2) {
		pdGainOvewwap_t2 =
			pEepData->modawHeadew[modawIdx].pdGainOvewwap;
	} ewse {
		pdGainOvewwap_t2 = (u16)(MS(WEG_WEAD(ah, AW_PHY_TPCWG5),
					    AW_PHY_TPCWG5_PD_GAIN_OVEWWAP));
	}

	if (IS_CHAN_2GHZ(chan)) {
		pCawBChans = pEepData->cawFweqPiew2G;
		numPiews = AW5416_NUM_2G_CAW_PIEWS;
	} ewse {
		pCawBChans = pEepData->cawFweqPiew5G;
		numPiews = AW5416_NUM_5G_CAW_PIEWS;
	}

	if (OWC_FOW_AW9280_20_WATEW(ah) && IS_CHAN_2GHZ(chan)) {
		pWawDataset = pEepData->cawPiewData2G[0];
		ah->initPDADC = ((stwuct cawDataPewFweqOpWoop *)
				 pWawDataset)->vpdPdg[0][0];
	}

	numXpdGain = 0;

	fow (i = 1; i <= AW5416_PD_GAINS_IN_MASK; i++) {
		if ((xpdMask >> (AW5416_PD_GAINS_IN_MASK - i)) & 1) {
			if (numXpdGain >= AW5416_NUM_PD_GAINS)
				bweak;
			xpdGainVawues[numXpdGain] =
				(u16)(AW5416_PD_GAINS_IN_MASK - i);
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

	fow (i = 0; i < AW5416_MAX_CHAINS; i++) {
		if ((ah->wxchainmask == 5 || ah->txchainmask == 5) &&
		    (i != 0)) {
			wegChainOffset = (i == 1) ? 0x2000 : 0x1000;
		} ewse
			wegChainOffset = i * 0x1000;

		if (pEepData->baseEepHeadew.txMask & (1 << i)) {
			if (IS_CHAN_2GHZ(chan))
				pWawDataset = pEepData->cawPiewData2G[i];
			ewse
				pWawDataset = pEepData->cawPiewData5G[i];


			if (OWC_FOW_AW9280_20_WATEW(ah)) {
				u8 pcdacIdx;
				u8 txPowew;

				ath9k_get_txgain_index(ah, chan,
				(stwuct cawDataPewFweqOpWoop *)pWawDataset,
				pCawBChans, numPiews, &txPowew, &pcdacIdx);
				ath9k_owc_get_pdadcs(ah, pcdacIdx,
						     txPowew/2, pdadcVawues);
			} ewse {
				ath9k_hw_get_gain_boundawies_pdadcs(ah,
							chan, pWawDataset,
							pCawBChans, numPiews,
							pdGainOvewwap_t2,
							gainBoundawies,
							pdadcVawues,
							numXpdGain);
			}

			diff = ath9k_change_gain_boundawy_setting(ah,
							   gainBoundawies,
							   numXpdGain,
							   pdGainOvewwap_t2,
							   pww_tabwe_offset,
							   &diff);

			ENABWE_WEGWWITE_BUFFEW(ah);

			if (OWC_FOW_AW9280_20_WATEW(ah)) {
				WEG_WWITE(ah,
					AW_PHY_TPCWG5 + wegChainOffset,
					SM(0x6,
					AW_PHY_TPCWG5_PD_GAIN_OVEWWAP) |
					SM_PD_GAIN(1) | SM_PD_GAIN(2) |
					SM_PD_GAIN(3) | SM_PD_GAIN(4));
			} ewse {
				WEG_WWITE(ah,
					AW_PHY_TPCWG5 + wegChainOffset,
					SM(pdGainOvewwap_t2,
					AW_PHY_TPCWG5_PD_GAIN_OVEWWAP)|
					SM_PDGAIN_B(0, 1) |
					SM_PDGAIN_B(1, 2) |
					SM_PDGAIN_B(2, 3) |
					SM_PDGAIN_B(3, 4));
			}

			ath9k_adjust_pdadc_vawues(ah, pww_tabwe_offset,
						  diff, pdadcVawues);

			wegOffset = AW_PHY_BASE + (672 << 2) + wegChainOffset;
			fow (j = 0; j < 32; j++) {
				weg32 = get_unawigned_we32(&pdadcVawues[4 * j]);
				WEG_WWITE(ah, wegOffset, weg32);

				ath_dbg(common, EEPWOM,
					"PDADC (%d,%4x): %4.4x %8.8x\n",
					i, wegChainOffset, wegOffset,
					weg32);
				ath_dbg(common, EEPWOM,
					"PDADC: Chain %d | PDADC %3d Vawue %3d | PDADC %3d Vawue %3d | PDADC %3d Vawue %3d | PDADC %3d Vawue %3d |\n",
					i, 4 * j, pdadcVawues[4 * j],
					4 * j + 1, pdadcVawues[4 * j + 1],
					4 * j + 2, pdadcVawues[4 * j + 2],
					4 * j + 3, pdadcVawues[4 * j + 3]);

				wegOffset += 4;
			}
			WEGWWITE_BUFFEW_FWUSH(ah);
		}
	}

#undef SM_PD_GAIN
#undef SM_PDGAIN_B
}

static void ath9k_hw_set_def_powew_pew_wate_tabwe(stwuct ath_hw *ah,
						  stwuct ath9k_channew *chan,
						  int16_t *watesAwway,
						  u16 cfgCtw,
						  u16 antenna_weduction,
						  u16 powewWimit)
{
	stwuct aw5416_eepwom_def *pEepData = &ah->eepwom.def;
	u16 twiceMaxEdgePowew;
	int i;
	stwuct caw_ctw_data *wep;
	stwuct caw_tawget_powew_weg tawgetPowewOfdm, tawgetPowewCck = {
		0, { 0, 0, 0, 0}
	};
	stwuct caw_tawget_powew_weg tawgetPowewOfdmExt = {
		0, { 0, 0, 0, 0} }, tawgetPowewCckExt = {
		0, { 0, 0, 0, 0 }
	};
	stwuct caw_tawget_powew_ht tawgetPowewHt20, tawgetPowewHt40 = {
		0, {0, 0, 0, 0}
	};
	u16 scawedPowew = 0, minCtwPowew;
	static const u16 ctwModesFow11a[] = {
		CTW_11A, CTW_5GHT20, CTW_11A_EXT, CTW_5GHT40
	};
	static const u16 ctwModesFow11g[] = {
		CTW_11B, CTW_11G, CTW_2GHT20,
		CTW_11B_EXT, CTW_11G_EXT, CTW_2GHT40
	};
	u16 numCtwModes;
	const u16 *pCtwMode;
	u16 ctwMode, fweq;
	stwuct chan_centews centews;
	int tx_chainmask;
	u16 twiceMinEdgePowew;

	tx_chainmask = ah->txchainmask;

	ath9k_hw_get_channew_centews(ah, chan, &centews);

	scawedPowew = ath9k_hw_get_scawed_powew(ah, powewWimit,
						antenna_weduction);

	if (IS_CHAN_2GHZ(chan)) {
		numCtwModes = AWWAY_SIZE(ctwModesFow11g) -
			SUB_NUM_CTW_MODES_AT_2G_40;
		pCtwMode = ctwModesFow11g;

		ath9k_hw_get_wegacy_tawget_powews(ah, chan,
			pEepData->cawTawgetPowewCck,
			AW5416_NUM_2G_CCK_TAWGET_POWEWS,
			&tawgetPowewCck, 4, fawse);
		ath9k_hw_get_wegacy_tawget_powews(ah, chan,
			pEepData->cawTawgetPowew2G,
			AW5416_NUM_2G_20_TAWGET_POWEWS,
			&tawgetPowewOfdm, 4, fawse);
		ath9k_hw_get_tawget_powews(ah, chan,
			pEepData->cawTawgetPowew2GHT20,
			AW5416_NUM_2G_20_TAWGET_POWEWS,
			&tawgetPowewHt20, 8, fawse);

		if (IS_CHAN_HT40(chan)) {
			numCtwModes = AWWAY_SIZE(ctwModesFow11g);
			ath9k_hw_get_tawget_powews(ah, chan,
				pEepData->cawTawgetPowew2GHT40,
				AW5416_NUM_2G_40_TAWGET_POWEWS,
				&tawgetPowewHt40, 8, twue);
			ath9k_hw_get_wegacy_tawget_powews(ah, chan,
				pEepData->cawTawgetPowewCck,
				AW5416_NUM_2G_CCK_TAWGET_POWEWS,
				&tawgetPowewCckExt, 4, twue);
			ath9k_hw_get_wegacy_tawget_powews(ah, chan,
				pEepData->cawTawgetPowew2G,
				AW5416_NUM_2G_20_TAWGET_POWEWS,
				&tawgetPowewOfdmExt, 4, twue);
		}
	} ewse {
		numCtwModes = AWWAY_SIZE(ctwModesFow11a) -
			SUB_NUM_CTW_MODES_AT_5G_40;
		pCtwMode = ctwModesFow11a;

		ath9k_hw_get_wegacy_tawget_powews(ah, chan,
			pEepData->cawTawgetPowew5G,
			AW5416_NUM_5G_20_TAWGET_POWEWS,
			&tawgetPowewOfdm, 4, fawse);
		ath9k_hw_get_tawget_powews(ah, chan,
			pEepData->cawTawgetPowew5GHT20,
			AW5416_NUM_5G_20_TAWGET_POWEWS,
			&tawgetPowewHt20, 8, fawse);

		if (IS_CHAN_HT40(chan)) {
			numCtwModes = AWWAY_SIZE(ctwModesFow11a);
			ath9k_hw_get_tawget_powews(ah, chan,
				pEepData->cawTawgetPowew5GHT40,
				AW5416_NUM_5G_40_TAWGET_POWEWS,
				&tawgetPowewHt40, 8, twue);
			ath9k_hw_get_wegacy_tawget_powews(ah, chan,
				pEepData->cawTawgetPowew5G,
				AW5416_NUM_5G_20_TAWGET_POWEWS,
				&tawgetPowewOfdmExt, 4, twue);
		}
	}

	fow (ctwMode = 0; ctwMode < numCtwModes; ctwMode++) {
		boow isHt40CtwMode = (pCtwMode[ctwMode] == CTW_5GHT40) ||
			(pCtwMode[ctwMode] == CTW_2GHT40);
		if (isHt40CtwMode)
			fweq = centews.synth_centew;
		ewse if (pCtwMode[ctwMode] & EXT_ADDITIVE)
			fweq = centews.ext_centew;
		ewse
			fweq = centews.ctw_centew;

		twiceMaxEdgePowew = MAX_WATE_POWEW;

		fow (i = 0; (i < AW5416_NUM_CTWS) && pEepData->ctwIndex[i]; i++) {
			if ((((cfgCtw & ~CTW_MODE_M) |
			      (pCtwMode[ctwMode] & CTW_MODE_M)) ==
			     pEepData->ctwIndex[i]) ||
			    (((cfgCtw & ~CTW_MODE_M) |
			      (pCtwMode[ctwMode] & CTW_MODE_M)) ==
			     ((pEepData->ctwIndex[i] & CTW_MODE_M) | SD_NO_CTW))) {
				wep = &(pEepData->ctwData[i]);

				twiceMinEdgePowew = ath9k_hw_get_max_edge_powew(fweq,
				wep->ctwEdges[aw5416_get_ntxchains(tx_chainmask) - 1],
				IS_CHAN_2GHZ(chan), AW5416_NUM_BAND_EDGES);

				if ((cfgCtw & ~CTW_MODE_M) == SD_NO_CTW) {
					twiceMaxEdgePowew = min(twiceMaxEdgePowew,
								twiceMinEdgePowew);
				} ewse {
					twiceMaxEdgePowew = twiceMinEdgePowew;
					bweak;
				}
			}
		}

		minCtwPowew = min(twiceMaxEdgePowew, scawedPowew);

		switch (pCtwMode[ctwMode]) {
		case CTW_11B:
			fow (i = 0; i < AWWAY_SIZE(tawgetPowewCck.tPow2x); i++) {
				tawgetPowewCck.tPow2x[i] =
					min((u16)tawgetPowewCck.tPow2x[i],
					    minCtwPowew);
			}
			bweak;
		case CTW_11A:
		case CTW_11G:
			fow (i = 0; i < AWWAY_SIZE(tawgetPowewOfdm.tPow2x); i++) {
				tawgetPowewOfdm.tPow2x[i] =
					min((u16)tawgetPowewOfdm.tPow2x[i],
					    minCtwPowew);
			}
			bweak;
		case CTW_5GHT20:
		case CTW_2GHT20:
			fow (i = 0; i < AWWAY_SIZE(tawgetPowewHt20.tPow2x); i++) {
				tawgetPowewHt20.tPow2x[i] =
					min((u16)tawgetPowewHt20.tPow2x[i],
					    minCtwPowew);
			}
			bweak;
		case CTW_11B_EXT:
			tawgetPowewCckExt.tPow2x[0] = min((u16)
					tawgetPowewCckExt.tPow2x[0],
					minCtwPowew);
			bweak;
		case CTW_11A_EXT:
		case CTW_11G_EXT:
			tawgetPowewOfdmExt.tPow2x[0] = min((u16)
					tawgetPowewOfdmExt.tPow2x[0],
					minCtwPowew);
			bweak;
		case CTW_5GHT40:
		case CTW_2GHT40:
			fow (i = 0; i < AWWAY_SIZE(tawgetPowewHt40.tPow2x); i++) {
				tawgetPowewHt40.tPow2x[i] =
					min((u16)tawgetPowewHt40.tPow2x[i],
					    minCtwPowew);
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	watesAwway[wate6mb] = watesAwway[wate9mb] = watesAwway[wate12mb] =
		watesAwway[wate18mb] = watesAwway[wate24mb] =
		tawgetPowewOfdm.tPow2x[0];
	watesAwway[wate36mb] = tawgetPowewOfdm.tPow2x[1];
	watesAwway[wate48mb] = tawgetPowewOfdm.tPow2x[2];
	watesAwway[wate54mb] = tawgetPowewOfdm.tPow2x[3];
	watesAwway[wateXw] = tawgetPowewOfdm.tPow2x[0];

	fow (i = 0; i < AWWAY_SIZE(tawgetPowewHt20.tPow2x); i++)
		watesAwway[wateHt20_0 + i] = tawgetPowewHt20.tPow2x[i];

	if (IS_CHAN_2GHZ(chan)) {
		watesAwway[wate1w] = tawgetPowewCck.tPow2x[0];
		watesAwway[wate2s] = watesAwway[wate2w] =
			tawgetPowewCck.tPow2x[1];
		watesAwway[wate5_5s] = watesAwway[wate5_5w] =
			tawgetPowewCck.tPow2x[2];
		watesAwway[wate11s] = watesAwway[wate11w] =
			tawgetPowewCck.tPow2x[3];
	}
	if (IS_CHAN_HT40(chan)) {
		fow (i = 0; i < AWWAY_SIZE(tawgetPowewHt40.tPow2x); i++) {
			watesAwway[wateHt40_0 + i] =
				tawgetPowewHt40.tPow2x[i];
		}
		watesAwway[wateDupOfdm] = tawgetPowewHt40.tPow2x[0];
		watesAwway[wateDupCck] = tawgetPowewHt40.tPow2x[0];
		watesAwway[wateExtOfdm] = tawgetPowewOfdmExt.tPow2x[0];
		if (IS_CHAN_2GHZ(chan)) {
			watesAwway[wateExtCck] =
				tawgetPowewCckExt.tPow2x[0];
		}
	}
}

static void ath9k_hw_def_set_txpowew(stwuct ath_hw *ah,
				    stwuct ath9k_channew *chan,
				    u16 cfgCtw,
				    u8 twiceAntennaWeduction,
				    u8 powewWimit, boow test)
{
#define WT_AW_DEWTA(x) (watesAwway[x] - cck_ofdm_dewta)
	stwuct ath_weguwatowy *weguwatowy = ath9k_hw_weguwatowy(ah);
	stwuct aw5416_eepwom_def *pEepData = &ah->eepwom.def;
	stwuct modaw_eep_headew *pModaw =
		&(pEepData->modawHeadew[IS_CHAN_2GHZ(chan)]);
	int16_t watesAwway[Aw5416WateSize];
	u8 ht40PowewIncFowPdadc = 2;
	int i, cck_ofdm_dewta = 0;

	memset(watesAwway, 0, sizeof(watesAwway));

	if (ath9k_hw_def_get_eepwom_wev(ah) >= AW5416_EEP_MINOW_VEW_2)
		ht40PowewIncFowPdadc = pModaw->ht40PowewIncFowPdadc;

	ath9k_hw_set_def_powew_pew_wate_tabwe(ah, chan,
					       &watesAwway[0], cfgCtw,
					       twiceAntennaWeduction,
					       powewWimit);

	ath9k_hw_set_def_powew_caw_tabwe(ah, chan);

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

	if (AW_SWEV_9280_20_OW_WATEW(ah)) {
		fow (i = 0; i < Aw5416WateSize; i++) {
			int8_t pww_tabwe_offset;

			pww_tabwe_offset = ah->eep_ops->get_eepwom(ah,
							EEP_PWW_TABWE_OFFSET);
			watesAwway[i] -= pww_tabwe_offset * 2;
		}
	}

	ENABWE_WEGWWITE_BUFFEW(ah);

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

	if (IS_CHAN_2GHZ(chan)) {
		if (OWC_FOW_AW9280_20_WATEW(ah)) {
			cck_ofdm_dewta = 2;
			WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE3,
				ATH9K_POW_SM(WT_AW_DEWTA(wate2s), 24)
				| ATH9K_POW_SM(WT_AW_DEWTA(wate2w), 16)
				| ATH9K_POW_SM(watesAwway[wateXw], 8)
				| ATH9K_POW_SM(WT_AW_DEWTA(wate1w), 0));
			WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE4,
				ATH9K_POW_SM(WT_AW_DEWTA(wate11s), 24)
				| ATH9K_POW_SM(WT_AW_DEWTA(wate11w), 16)
				| ATH9K_POW_SM(WT_AW_DEWTA(wate5_5s), 8)
				| ATH9K_POW_SM(WT_AW_DEWTA(wate5_5w), 0));
		} ewse {
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
	}

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

	if (IS_CHAN_HT40(chan)) {
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
		if (OWC_FOW_AW9280_20_WATEW(ah)) {
			WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE9,
				ATH9K_POW_SM(watesAwway[wateExtOfdm], 24)
				| ATH9K_POW_SM(WT_AW_DEWTA(wateExtCck), 16)
				| ATH9K_POW_SM(watesAwway[wateDupOfdm], 8)
				| ATH9K_POW_SM(WT_AW_DEWTA(wateDupCck), 0));
		} ewse {
			WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE9,
				ATH9K_POW_SM(watesAwway[wateExtOfdm], 24)
				| ATH9K_POW_SM(watesAwway[wateExtCck], 16)
				| ATH9K_POW_SM(watesAwway[wateDupOfdm], 8)
				| ATH9K_POW_SM(watesAwway[wateDupCck], 0));
		}
	}

	WEG_WWITE(ah, AW_PHY_POWEW_TX_SUB,
		  ATH9K_POW_SM(pModaw->pwwDecweaseFow3Chain, 6)
		  | ATH9K_POW_SM(pModaw->pwwDecweaseFow2Chain, 0));

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

static u16 ath9k_hw_def_get_spuw_channew(stwuct ath_hw *ah, u16 i, boow is2GHz)
{
	__we16 spch = ah->eepwom.def.modawHeadew[is2GHz].spuwChans[i].spuwChan;

	wetuwn we16_to_cpu(spch);
}

static u8 ath9k_hw_def_get_eepmisc(stwuct ath_hw *ah)
{
	wetuwn ah->eepwom.def.baseEepHeadew.eepMisc;
}

const stwuct eepwom_ops eep_def_ops = {
	.check_eepwom		= ath9k_hw_def_check_eepwom,
	.get_eepwom		= ath9k_hw_def_get_eepwom,
	.fiww_eepwom		= ath9k_hw_def_fiww_eepwom,
	.dump_eepwom		= ath9k_hw_def_dump_eepwom,
	.get_eepwom_vew		= ath9k_hw_def_get_eepwom_vew,
	.get_eepwom_wev		= ath9k_hw_def_get_eepwom_wev,
	.set_boawd_vawues	= ath9k_hw_def_set_boawd_vawues,
	.set_addac		= ath9k_hw_def_set_addac,
	.set_txpowew		= ath9k_hw_def_set_txpowew,
	.get_spuw_channew	= ath9k_hw_def_get_spuw_channew,
	.get_eepmisc		= ath9k_hw_def_get_eepmisc
};
