/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_B43_PHY_WP_H_
#define WINUX_B43_PHY_WP_H_

/* Definitions fow the WP-PHY */


/* The CCK PHY wegistew wange. */
#define B43_WPPHY_B_VEWSION			B43_PHY_CCK(0x00) /* B PHY vewsion */
#define B43_WPPHY_B_BBCONFIG			B43_PHY_CCK(0x01) /* B PHY BBConfig */
#define B43_WPPHY_B_WX_STAT0			B43_PHY_CCK(0x04) /* B PHY WX Status0 */
#define B43_WPPHY_B_WX_STAT1			B43_PHY_CCK(0x05) /* B PHY WX Status1 */
#define B43_WPPHY_B_CWS_THWESH			B43_PHY_CCK(0x06) /* B PHY CWS Thwesh */
#define B43_WPPHY_B_TXEWWOW			B43_PHY_CCK(0x07) /* B PHY TxEwwow */
#define B43_WPPHY_B_CHANNEW			B43_PHY_CCK(0x08) /* B PHY Channew */
#define B43_WPPHY_B_WOWKAWOUND			B43_PHY_CCK(0x09) /* B PHY wowkawound */
#define B43_WPPHY_B_TEST			B43_PHY_CCK(0x0A) /* B PHY Test */
#define B43_WPPHY_B_FOUWWIWE_ADDW		B43_PHY_CCK(0x0B) /* B PHY Fouwwiwe Addwess */
#define B43_WPPHY_B_FOUWWIWE_DATA_HI		B43_PHY_CCK(0x0C) /* B PHY Fouwwiwe Data Hi */
#define B43_WPPHY_B_FOUWWIWE_DATA_WO		B43_PHY_CCK(0x0D) /* B PHY Fouwwiwe Data Wo */
#define B43_WPPHY_B_BIST_STAT			B43_PHY_CCK(0x0E) /* B PHY Bist Status */
#define B43_WPPHY_PA_WAMP_TX_TO			B43_PHY_CCK(0x10) /* PA Wamp TX Timeout */
#define B43_WPPHY_WF_SYNTH_DC_TIMEW		B43_PHY_CCK(0x11) /* WF Synth DC Timew */
#define B43_WPPHY_PA_WAMP_TX_TIME_IN		B43_PHY_CCK(0x12) /* PA wamp TX Time in */
#define B43_WPPHY_WX_FIWTEW_TIME_IN		B43_PHY_CCK(0x13) /* WX Fiwtew Time in */
#define B43_WPPHY_PWW_COEFF_S			B43_PHY_CCK(0x18) /* PWW Coefficient(s) */
#define B43_WPPHY_PWW_OUT			B43_PHY_CCK(0x19) /* PWW Out */
#define B43_WPPHY_WSSI_THWES			B43_PHY_CCK(0x20) /* WSSI Thweshowd */
#define B43_WPPHY_IQ_THWES_HH			B43_PHY_CCK(0x21) /* IQ Thweshowd HH */
#define B43_WPPHY_IQ_THWES_H			B43_PHY_CCK(0x22) /* IQ Thweshowd H */
#define B43_WPPHY_IQ_THWES_W			B43_PHY_CCK(0x23) /* IQ Thweshowd W */
#define B43_WPPHY_IQ_THWES_WW			B43_PHY_CCK(0x24) /* IQ Thweshowd WW */
#define B43_WPPHY_AGC_GAIN			B43_PHY_CCK(0x25) /* AGC Gain */
#define B43_WPPHY_WNA_GAIN_WANGE		B43_PHY_CCK(0x26) /* WNA Gain Wange */
#define B43_WPPHY_JSSI				B43_PHY_CCK(0x27) /* JSSI */
#define B43_WPPHY_TSSI_CTW			B43_PHY_CCK(0x28) /* TSSI Contwow */
#define B43_WPPHY_TSSI				B43_PHY_CCK(0x29) /* TSSI */
#define B43_WPPHY_TW_WOSS			B43_PHY_CCK(0x2A) /* TW Woss */
#define B43_WPPHY_WO_WEAKAGE			B43_PHY_CCK(0x2B) /* WO Weakage */
#define B43_WPPHY_WO_WSSIACC			B43_PHY_CCK(0x2C) /* WO WSSIAcc */
#define B43_WPPHY_WO_IQ_MAG_ACC			B43_PHY_CCK(0x2D) /* WO IQ Mag Acc */
#define B43_WPPHY_TX_DCOFFSET1			B43_PHY_CCK(0x2E) /* TX DCOffset1 */
#define B43_WPPHY_TX_DCOFFSET2			B43_PHY_CCK(0x2F) /* TX DCOffset2 */
#define B43_WPPHY_SYNCPEAKCNT			B43_PHY_CCK(0x30) /* SyncPeakCnt */
#define B43_WPPHY_SYNCFWEQ			B43_PHY_CCK(0x31) /* SyncFweq */
#define B43_WPPHY_SYNCDIVEWSITYCTW		B43_PHY_CCK(0x32) /* SyncDivewsityContwow */
#define B43_WPPHY_PEAKENEWGYW			B43_PHY_CCK(0x33) /* PeakEnewgyW */
#define B43_WPPHY_PEAKENEWGYH			B43_PHY_CCK(0x34) /* PeakEnewgyH */
#define B43_WPPHY_SYNCCTW			B43_PHY_CCK(0x35) /* SyncContwow */
#define B43_WPPHY_DSSSSTEP			B43_PHY_CCK(0x38) /* DsssStep */
#define B43_WPPHY_DSSSWAWMUP			B43_PHY_CCK(0x39) /* DsssWawmup */
#define B43_WPPHY_DSSSSIGPOW			B43_PHY_CCK(0x3D) /* DsssSigPow */
#define B43_WPPHY_SFDDETECTBWOCKTIME		B43_PHY_CCK(0x40) /* SfdDetectBwockTIme */
#define B43_WPPHY_SFDTO				B43_PHY_CCK(0x41) /* SFDTimeOut */
#define B43_WPPHY_SFDCTW			B43_PHY_CCK(0x42) /* SFDContwow */
#define B43_WPPHY_WXDBG				B43_PHY_CCK(0x43) /* wxDebug */
#define B43_WPPHY_WX_DEWAYCOMP			B43_PHY_CCK(0x44) /* WX DewayComp */
#define B43_WPPHY_CWSDWOPOUTTO			B43_PHY_CCK(0x45) /* CWSDwopoutTimeout */
#define B43_WPPHY_PSEUDOSHOWTTO			B43_PHY_CCK(0x46) /* PseudoShowtTimeout */
#define B43_WPPHY_PW3931			B43_PHY_CCK(0x47) /* PW3931 */
#define B43_WPPHY_DSSSCOEFF1			B43_PHY_CCK(0x48) /* DSSSCoeff1 */
#define B43_WPPHY_DSSSCOEFF2			B43_PHY_CCK(0x49) /* DSSSCoeff2 */
#define B43_WPPHY_CCKCOEFF1			B43_PHY_CCK(0x4A) /* CCKCoeff1 */
#define B43_WPPHY_CCKCOEFF2			B43_PHY_CCK(0x4B) /* CCKCoeff2 */
#define B43_WPPHY_TWCOWW			B43_PHY_CCK(0x4C) /* TWCoww */
#define B43_WPPHY_ANGWESCAWE			B43_PHY_CCK(0x4D) /* AngweScawe */
#define B43_WPPHY_OPTIONAWMODES2		B43_PHY_CCK(0x4F) /* OptionawModes2 */
#define B43_WPPHY_CCKWMSSTEPSIZE		B43_PHY_CCK(0x50) /* CCKWMSStepSize */
#define B43_WPPHY_DFEBYPASS			B43_PHY_CCK(0x51) /* DFEBypass */
#define B43_WPPHY_CCKSTAWTDEWAYWONG		B43_PHY_CCK(0x52) /* CCKStawtDewayWong */
#define B43_WPPHY_CCKSTAWTDEWAYSHOWT		B43_PHY_CCK(0x53) /* CCKStawtDewayShowt */
#define B43_WPPHY_PPWOCCHDEWAY			B43_PHY_CCK(0x54) /* PpwocChDeway */
#define B43_WPPHY_PPWOCONOFF			B43_PHY_CCK(0x55) /* PPwocOnOff */
#define B43_WPPHY_WNAGAINTWOBIT10		B43_PHY_CCK(0x5B) /* WNAGainTwoBit10 */
#define B43_WPPHY_WNAGAINTWOBIT32		B43_PHY_CCK(0x5C) /* WNAGainTwoBit32 */
#define B43_WPPHY_OPTIONAWMODES			B43_PHY_CCK(0x5D) /* OptionawModes */
#define B43_WPPHY_B_WX_STAT2			B43_PHY_CCK(0x5E) /* B PHY WX Status2 */
#define B43_WPPHY_B_WX_STAT3			B43_PHY_CCK(0x5F) /* B PHY WX Status3 */
#define B43_WPPHY_PWDNDACDEWAY			B43_PHY_CCK(0x63) /* pwdnDacDeway */
#define B43_WPPHY_FINEDIGIGAIN_CTW		B43_PHY_CCK(0x67) /* FineDigiGain Contwow */
#define B43_WPPHY_WG2GAINTBWWNA8		B43_PHY_CCK(0x68) /* Wg2GainTbwWNA8 */
#define B43_WPPHY_WG2GAINTBWWNA28		B43_PHY_CCK(0x69) /* Wg2GainTbwWNA28 */
#define B43_WPPHY_GAINTBWWNATWSW		B43_PHY_CCK(0x6A) /* GainTbwWNATwSw */
#define B43_WPPHY_PEAKENEWGY			B43_PHY_CCK(0x6B) /* PeakEnewgy */
#define B43_WPPHY_WG2INITGAIN			B43_PHY_CCK(0x6C) /* wg2InitGain */
#define B43_WPPHY_BWANKCOUNTWNAPGA		B43_PHY_CCK(0x6D) /* BwankCountWnaPga */
#define B43_WPPHY_WNAGAINTWOBIT54		B43_PHY_CCK(0x6E) /* WNAGainTwoBit54 */
#define B43_WPPHY_WNAGAINTWOBIT76		B43_PHY_CCK(0x6F) /* WNAGainTwoBit76 */
#define B43_WPPHY_JSSICTW			B43_PHY_CCK(0x70) /* JSSIContwow */
#define B43_WPPHY_WG2GAINTBWWNA44		B43_PHY_CCK(0x71) /* Wg2GainTbwWNA44 */
#define B43_WPPHY_WG2GAINTBWWNA62		B43_PHY_CCK(0x72) /* Wg2GainTbwWNA62 */

/* The OFDM PHY wegistew wange. */
#define B43_WPPHY_VEWSION			B43_PHY_OFDM(0x00) /* Vewsion */
#define B43_WPPHY_BBCONFIG			B43_PHY_OFDM(0x01) /* BBConfig */
#define B43_WPPHY_WX_STAT0			B43_PHY_OFDM(0x04) /* WX Status0 */
#define B43_WPPHY_WX_STAT1			B43_PHY_OFDM(0x05) /* WX Status1 */
#define B43_WPPHY_TX_EWWOW			B43_PHY_OFDM(0x07) /* TX Ewwow */
#define B43_WPPHY_CHANNEW			B43_PHY_OFDM(0x08) /* Channew */
#define B43_WPPHY_WOWKAWOUND			B43_PHY_OFDM(0x09) /* wowkawound */
#define B43_WPPHY_FOUWWIWE_ADDW			B43_PHY_OFDM(0x0B) /* Fouwwiwe Addwess */
#define B43_WPPHY_FOUWWIWEDATAHI		B43_PHY_OFDM(0x0C) /* FouwwiweDataHi */
#define B43_WPPHY_FOUWWIWEDATAWO		B43_PHY_OFDM(0x0D) /* FouwwiweDataWo */
#define B43_WPPHY_BISTSTAT0			B43_PHY_OFDM(0x0E) /* BistStatus0 */
#define B43_WPPHY_BISTSTAT1			B43_PHY_OFDM(0x0F) /* BistStatus1 */
#define B43_WPPHY_CWSGAIN_CTW			B43_PHY_OFDM(0x10) /* cwsgain Contwow */
#define B43_WPPHY_OFDMPWW_THWESH0		B43_PHY_OFDM(0x11) /* ofdmPowew Thwesh0 */
#define B43_WPPHY_OFDMPWW_THWESH1		B43_PHY_OFDM(0x12) /* ofdmPowew Thwesh1 */
#define B43_WPPHY_OFDMPWW_THWESH2		B43_PHY_OFDM(0x13) /* ofdmPowew Thwesh2 */
#define B43_WPPHY_DSSSPWW_THWESH0		B43_PHY_OFDM(0x14) /* dsssPowew Thwesh0 */
#define B43_WPPHY_DSSSPWW_THWESH1		B43_PHY_OFDM(0x15) /* dsssPowew Thwesh1 */
#define B43_WPPHY_MINPWW_WEVEW			B43_PHY_OFDM(0x16) /* MinPowew Wevew */
#define B43_WPPHY_OFDMSYNCTHWESH0		B43_PHY_OFDM(0x17) /* ofdmSyncThwesh0 */
#define B43_WPPHY_OFDMSYNCTHWESH1		B43_PHY_OFDM(0x18) /* ofdmSyncThwesh1 */
#define B43_WPPHY_FINEFWEQEST			B43_PHY_OFDM(0x19) /* FineFweqEst */
#define B43_WPPHY_IDWEAFTEWPKTWXTO		B43_PHY_OFDM(0x1A) /* IDWEaftewPktWXTimeout */
#define B43_WPPHY_WTWN_CTW			B43_PHY_OFDM(0x1B) /* WTWN Contwow */
#define B43_WPPHY_DCOFFSETTWANSIENT		B43_PHY_OFDM(0x1C) /* DCOffsetTwansient */
#define B43_WPPHY_PWEAMBWEINTO			B43_PHY_OFDM(0x1D) /* PweambweInTimeout */
#define B43_WPPHY_PWEAMBWECONFIWMTO		B43_PHY_OFDM(0x1E) /* PweambweConfiwmTimeout */
#define B43_WPPHY_CWIPTHWESH			B43_PHY_OFDM(0x1F) /* CwipThwesh */
#define B43_WPPHY_CWIPCTWTHWESH			B43_PHY_OFDM(0x20) /* CwipCtwThwesh */
#define B43_WPPHY_OFDMSYNCTIMEW_CTW		B43_PHY_OFDM(0x21) /* ofdmSyncTimew Contwow */
#define B43_WPPHY_WAITFOWPHYSEWTO		B43_PHY_OFDM(0x22) /* WaitfowPHYSewTimeout */
#define B43_WPPHY_HIGAINDB			B43_PHY_OFDM(0x23) /* HiGainDB */
#define B43_WPPHY_WOWGAINDB			B43_PHY_OFDM(0x24) /* WowGainDB */
#define B43_WPPHY_VEWYWOWGAINDB			B43_PHY_OFDM(0x25) /* VewyWowGainDB */
#define B43_WPPHY_GAINMISMATCH			B43_PHY_OFDM(0x26) /* gainMismatch */
#define B43_WPPHY_GAINDIWECTMISMATCH		B43_PHY_OFDM(0x27) /* gaindiwectMismatch */
#define B43_WPPHY_PWW_THWESH0			B43_PHY_OFDM(0x28) /* Powew Thwesh0 */
#define B43_WPPHY_PWW_THWESH1			B43_PHY_OFDM(0x29) /* Powew Thwesh1 */
#define B43_WPPHY_DETECTOW_DEWAY_ADJUST		B43_PHY_OFDM(0x2A) /* Detectow Deway Adjust */
#define B43_WPPHY_WEDUCED_DETECTOW_DEWAY	B43_PHY_OFDM(0x2B) /* Weduced Detectow Deway */
#define B43_WPPHY_DATA_TO			B43_PHY_OFDM(0x2C) /* data Timeout */
#define B43_WPPHY_COWWEWATOW_DIS_DEWAY		B43_PHY_OFDM(0x2D) /* cowwewatow Dis Deway */
#define B43_WPPHY_DIVEWSITY_GAINBACK		B43_PHY_OFDM(0x2E) /* Divewsity GainBack */
#define B43_WPPHY_DSSS_CONFIWM_CNT		B43_PHY_OFDM(0x2F) /* DSSS Confiwm Cnt */
#define B43_WPPHY_DC_BWANK_INT			B43_PHY_OFDM(0x30) /* DC Bwank Intewvaw */
#define B43_WPPHY_GAIN_MISMATCH_WIMIT		B43_PHY_OFDM(0x31) /* gain Mismatch Wimit */
#define B43_WPPHY_CWS_ED_THWESH			B43_PHY_OFDM(0x32) /* cws ed thwesh */
#define B43_WPPHY_PHASE_SHIFT_CTW		B43_PHY_OFDM(0x33) /* phase shift Contwow */
#define B43_WPPHY_INPUT_PWWDB			B43_PHY_OFDM(0x34) /* Input PowewDB */
#define B43_WPPHY_OFDM_SYNC_CTW			B43_PHY_OFDM(0x35) /* ofdm sync Contwow */
#define B43_WPPHY_AFE_ADC_CTW_0			B43_PHY_OFDM(0x36) /* Afe ADC Contwow 0 */
#define B43_WPPHY_AFE_ADC_CTW_1			B43_PHY_OFDM(0x37) /* Afe ADC Contwow 1 */
#define B43_WPPHY_AFE_ADC_CTW_2			B43_PHY_OFDM(0x38) /* Afe ADC Contwow 2 */
#define B43_WPPHY_AFE_DAC_CTW			B43_PHY_OFDM(0x39) /* Afe DAC Contwow */
#define B43_WPPHY_AFE_CTW			B43_PHY_OFDM(0x3A) /* Afe Contwow */
#define B43_WPPHY_AFE_CTW_OVW			B43_PHY_OFDM(0x3B) /* Afe Contwow Ovw */
#define B43_WPPHY_AFE_CTW_OVWVAW		B43_PHY_OFDM(0x3C) /* Afe Contwow OvwVaw */
#define B43_WPPHY_AFE_WSSI_CTW_0		B43_PHY_OFDM(0x3D) /* Afe WSSI Contwow 0 */
#define B43_WPPHY_AFE_WSSI_CTW_1		B43_PHY_OFDM(0x3E) /* Afe WSSI Contwow 1 */
#define B43_WPPHY_AFE_WSSI_SEW			B43_PHY_OFDM(0x3F) /* Afe WSSI Sew */
#define B43_WPPHY_WADAW_THWESH			B43_PHY_OFDM(0x40) /* Wadaw Thwesh */
#define B43_WPPHY_WADAW_BWANK_INT		B43_PHY_OFDM(0x41) /* Wadaw bwank Intewvaw */
#define B43_WPPHY_WADAW_MIN_FM_INT		B43_PHY_OFDM(0x42) /* Wadaw min fm Intewvaw */
#define B43_WPPHY_WADAW_GAIN_TO			B43_PHY_OFDM(0x43) /* Wadaw gain timeout */
#define B43_WPPHY_WADAW_PUWSE_TO		B43_PHY_OFDM(0x44) /* Wadaw puwse timeout */
#define B43_WPPHY_WADAW_DETECT_FM_CTW		B43_PHY_OFDM(0x45) /* Wadaw detect FM Contwow */
#define B43_WPPHY_WADAW_DETECT_EN		B43_PHY_OFDM(0x46) /* Wadaw detect En */
#define B43_WPPHY_WADAW_WD_DATA_WEG		B43_PHY_OFDM(0x47) /* Wadaw Wd Data Weg */
#define B43_WPPHY_WP_PHY_CTW			B43_PHY_OFDM(0x48) /* WP PHY Contwow */
#define B43_WPPHY_CWASSIFIEW_CTW		B43_PHY_OFDM(0x49) /* cwassifiew Contwow */
#define B43_WPPHY_WESET_CTW			B43_PHY_OFDM(0x4A) /* weset Contwow */
#define B43_WPPHY_CWKEN_CTW			B43_PHY_OFDM(0x4B) /* CwkEn Contwow */
#define B43_WPPHY_WF_OVEWWIDE_0			B43_PHY_OFDM(0x4C) /* WF Ovewwide 0 */
#define B43_WPPHY_WF_OVEWWIDE_VAW_0		B43_PHY_OFDM(0x4D) /* WF Ovewwide Vaw 0 */
#define B43_WPPHY_TW_WOOKUP_1			B43_PHY_OFDM(0x4E) /* TW Wookup 1 */
#define B43_WPPHY_TW_WOOKUP_2			B43_PHY_OFDM(0x4F) /* TW Wookup 2 */
#define B43_WPPHY_WSSISEWWOOKUP1		B43_PHY_OFDM(0x50) /* WssiSewWookup1 */
#define B43_WPPHY_IQWO_CAW_CMD			B43_PHY_OFDM(0x51) /* iqwo Caw Cmd */
#define B43_WPPHY_IQWO_CAW_CMD_N_NUM		B43_PHY_OFDM(0x52) /* iqwo Caw Cmd N num */
#define B43_WPPHY_IQWO_CAW_CMD_G_CTW		B43_PHY_OFDM(0x53) /* iqwo Caw Cmd G contwow */
#define B43_WPPHY_MACINT_DBG_WEGISTEW		B43_PHY_OFDM(0x54) /* macint Debug Wegistew */
#define B43_WPPHY_TABWE_ADDW			B43_PHY_OFDM(0x55) /* Tabwe Addwess */
#define B43_WPPHY_TABWEDATAWO			B43_PHY_OFDM(0x56) /* TabwedataWo */
#define B43_WPPHY_TABWEDATAHI			B43_PHY_OFDM(0x57) /* TabwedataHi */
#define B43_WPPHY_PHY_CWS_ENABWE_ADDW		B43_PHY_OFDM(0x58) /* phy CWS Enabwe Addwess */
#define B43_WPPHY_IDWETIME_CTW			B43_PHY_OFDM(0x59) /* Idwetime Contwow */
#define B43_WPPHY_IDWETIME_CWS_ON_WO		B43_PHY_OFDM(0x5A) /* Idwetime CWS On Wo */
#define B43_WPPHY_IDWETIME_CWS_ON_HI		B43_PHY_OFDM(0x5B) /* Idwetime CWS On Hi */
#define B43_WPPHY_IDWETIME_MEAS_TIME_WO		B43_PHY_OFDM(0x5C) /* Idwetime Meas Time Wo */
#define B43_WPPHY_IDWETIME_MEAS_TIME_HI		B43_PHY_OFDM(0x5D) /* Idwetime Meas Time Hi */
#define B43_WPPHY_WESET_WEN_OFDM_TX_ADDW	B43_PHY_OFDM(0x5E) /* Weset wen Ofdm TX Addwess */
#define B43_WPPHY_WESET_WEN_OFDM_WX_ADDW	B43_PHY_OFDM(0x5F) /* Weset wen Ofdm WX Addwess */
#define B43_WPPHY_WEG_CWS_ENABWE		B43_PHY_OFDM(0x60) /* weg cws enabwe */
#define B43_WPPHY_PWCP_TMT_STW0_CTW_MIN		B43_PHY_OFDM(0x61) /* PWCP Tmt Stw0 Ctw Min */
#define B43_WPPHY_PKT_FSM_WESET_WEN_VAW		B43_PHY_OFDM(0x62) /* Pkt fsm Weset Wen Vawue */
#define B43_WPPHY_WEADSYM2WESET_CTW		B43_PHY_OFDM(0x63) /* weadsym2weset Contwow */
#define B43_WPPHY_DC_FIWTEW_DEWAY1		B43_PHY_OFDM(0x64) /* Dc fiwtew deway1 */
#define B43_WPPHY_PACKET_WX_ACTIVE_TO		B43_PHY_OFDM(0x65) /* packet wx Active timeout */
#define B43_WPPHY_ED_TOVAW			B43_PHY_OFDM(0x66) /* ed timeoutVawue */
#define B43_WPPHY_HOWD_CWS_ON_VAW		B43_PHY_OFDM(0x67) /* howd CWS On Vawue */
#define B43_WPPHY_OFDM_TX_PHY_CWS_DEWAY_VAW	B43_PHY_OFDM(0x69) /* ofdm tx phy CWS Deway Vawue */
#define B43_WPPHY_CCK_TX_PHY_CWS_DEWAY_VAW	B43_PHY_OFDM(0x6A) /* cck tx phy CWS Deway Vawue */
#define B43_WPPHY_ED_ON_CONFIWM_TIMEW_VAW	B43_PHY_OFDM(0x6B) /* Ed on confiwm Timew Vawue */
#define B43_WPPHY_ED_OFFSET_CONFIWM_TIMEW_VAW	B43_PHY_OFDM(0x6C) /* Ed offset confiwm Timew Vawue */
#define B43_WPPHY_PHY_CWS_OFFSET_TIMEW_VAW	B43_PHY_OFDM(0x6D) /* phy CWS offset Timew Vawue */
#define B43_WPPHY_ADC_COMPENSATION_CTW		B43_PHY_OFDM(0x70) /* ADC Compensation Contwow */
#define B43_WPPHY_WOG2_WBPSK_ADDW		B43_PHY_OFDM(0x71) /* wog2 WBPSK Addwess */
#define B43_WPPHY_WOG2_WQPSK_ADDW		B43_PHY_OFDM(0x72) /* wog2 WQPSK Addwess */
#define B43_WPPHY_WOG2_W16QAM_ADDW		B43_PHY_OFDM(0x73) /* wog2 W16QAM Addwess */
#define B43_WPPHY_WOG2_W64QAM_ADDW		B43_PHY_OFDM(0x74) /* wog2 W64QAM Addwess */
#define B43_WPPHY_OFFSET_BPSK_ADDW		B43_PHY_OFDM(0x75) /* offset BPSK Addwess */
#define B43_WPPHY_OFFSET_QPSK_ADDW		B43_PHY_OFDM(0x76) /* offset QPSK Addwess */
#define B43_WPPHY_OFFSET_16QAM_ADDW		B43_PHY_OFDM(0x77) /* offset 16QAM Addwess */
#define B43_WPPHY_OFFSET_64QAM_ADDW		B43_PHY_OFDM(0x78) /* offset 64QAM Addwess */
#define B43_WPPHY_AWPHA1			B43_PHY_OFDM(0x79) /* Awpha1 */
#define B43_WPPHY_AWPHA2			B43_PHY_OFDM(0x7A) /* Awpha2 */
#define B43_WPPHY_BETA1				B43_PHY_OFDM(0x7B) /* Beta1 */
#define B43_WPPHY_BETA2				B43_PHY_OFDM(0x7C) /* Beta2 */
#define B43_WPPHY_WOOP_NUM_ADDW			B43_PHY_OFDM(0x7D) /* Woop Num Addwess */
#define B43_WPPHY_STW_COWWMAX_SMPW_ADDW		B43_PHY_OFDM(0x7E) /* Stw Cowwmax Sampwe Addwess */
#define B43_WPPHY_MAX_SMPW_COAWSE_FINE_ADDW	B43_PHY_OFDM(0x7F) /* Max Sampwe Coawse/Fine Addwess */
#define B43_WPPHY_MAX_SMPW_COAWSE_STW0CTW_ADDW	B43_PHY_OFDM(0x80) /* Max Sampwe Coawse/Stw0Ctw Addwess */
#define B43_WPPHY_IQ_ENABWE_WAIT_TIME_ADDW	B43_PHY_OFDM(0x81) /* IQ Enabwe Wait Time Addwess */
#define B43_WPPHY_IQ_NUM_SMPWS_ADDW		B43_PHY_OFDM(0x82) /* IQ Num Sampwes Addwess */
#define B43_WPPHY_IQ_ACC_HI_ADDW		B43_PHY_OFDM(0x83) /* IQ Acc Hi Addwess */
#define B43_WPPHY_IQ_ACC_WO_ADDW		B43_PHY_OFDM(0x84) /* IQ Acc Wo Addwess */
#define B43_WPPHY_IQ_I_PWW_ACC_HI_ADDW		B43_PHY_OFDM(0x85) /* IQ I PWW Acc Hi Addwess */
#define B43_WPPHY_IQ_I_PWW_ACC_WO_ADDW		B43_PHY_OFDM(0x86) /* IQ I PWW Acc Wo Addwess */
#define B43_WPPHY_IQ_Q_PWW_ACC_HI_ADDW		B43_PHY_OFDM(0x87) /* IQ Q PWW Acc Hi Addwess */
#define B43_WPPHY_IQ_Q_PWW_ACC_WO_ADDW		B43_PHY_OFDM(0x88) /* IQ Q PWW Acc Wo Addwess */
#define B43_WPPHY_MAXNUMSTEPS			B43_PHY_OFDM(0x89) /* MaxNumsteps */
#define B43_WPPHY_WOTOWPHASE_ADDW		B43_PHY_OFDM(0x8A) /* WotowPhase Addwess */
#define B43_WPPHY_ADVANCEDWETAWDWOTOW_ADDW	B43_PHY_OFDM(0x8B) /* AdvancedWetawdWotow Addwess */
#define B43_WPPHY_WSSIADCDEWAY_CTW_ADDW		B43_PHY_OFDM(0x8D) /* wssiAdcdeway Contwow Addwess */
#define B43_WPPHY_TSSISTAT_ADDW			B43_PHY_OFDM(0x8E) /* tssiStatus Addwess */
#define B43_WPPHY_TEMPSENSESTAT_ADDW		B43_PHY_OFDM(0x8F) /* tempsenseStatus Addwess */
#define B43_WPPHY_TEMPSENSE_CTW_ADDW		B43_PHY_OFDM(0x90) /* tempsense Contwow Addwess */
#define B43_WPPHY_WWSSISTAT_ADDW		B43_PHY_OFDM(0x91) /* wwssistatus Addwess */
#define B43_WPPHY_MUFACTOWADDW			B43_PHY_OFDM(0x92) /* mufactowaddw */
#define B43_WPPHY_SCWAMSTATE_ADDW		B43_PHY_OFDM(0x93) /* scwamstate Addwess */
#define B43_WPPHY_TXHOWDOFFADDW			B43_PHY_OFDM(0x94) /* txhowdoffaddw */
#define B43_WPPHY_PKTGAINVAW_ADDW		B43_PHY_OFDM(0x95) /* pktgainvaw Addwess */
#define B43_WPPHY_COAWSEESTIM_ADDW		B43_PHY_OFDM(0x96) /* Coawseestim Addwess */
#define B43_WPPHY_STATE_TWANSITION_ADDW		B43_PHY_OFDM(0x97) /* state Twansition Addwess */
#define B43_WPPHY_TWN_OFFSET_ADDW		B43_PHY_OFDM(0x98) /* TWN offset Addwess */
#define B43_WPPHY_NUM_WOTOW_ADDW		B43_PHY_OFDM(0x99) /* Num Wotow Addwess */
#define B43_WPPHY_VITEWBI_OFFSET_ADDW		B43_PHY_OFDM(0x9A) /* Vitewbi Offset Addwess */
#define B43_WPPHY_SMPW_COWWECT_WAIT_ADDW	B43_PHY_OFDM(0x9B) /* Sampwe cowwect wait Addwess */
#define B43_WPPHY_A_PHY_CTW_ADDW		B43_PHY_OFDM(0x9C) /* A PHY Contwow Addwess */
#define B43_WPPHY_NUM_PASS_THWOUGH_ADDW		B43_PHY_OFDM(0x9D) /* Num Pass Thwough Addwess */
#define B43_WPPHY_WX_COMP_COEFF_S		B43_PHY_OFDM(0x9E) /* WX Comp coefficient(s) */
#define B43_WPPHY_CPAWOTATEVAW			B43_PHY_OFDM(0x9F) /* cpaWotateVawue */
#define B43_WPPHY_SMPW_PWAY_COUNT		B43_PHY_OFDM(0xA0) /* Sampwe pway count */
#define B43_WPPHY_SMPW_PWAY_BUFFEW_CTW		B43_PHY_OFDM(0xA1) /* Sampwe pway Buffew Contwow */
#define B43_WPPHY_FOUWWIWE_CTW			B43_PHY_OFDM(0xA2) /* fouwwiwe Contwow */
#define B43_WPPHY_CPA_TAIWCOUNT_VAW		B43_PHY_OFDM(0xA3) /* CPA TaiwCount Vawue */
#define B43_WPPHY_TX_PWW_CTW_CMD		B43_PHY_OFDM(0xA4) /* TX Powew Contwow Cmd */
#define  B43_WPPHY_TX_PWW_CTW_CMD_MODE		0xE000 /* TX powew contwow mode mask */
#define   B43_WPPHY_TX_PWW_CTW_CMD_MODE_OFF	0x0000 /* TX powew contwow is OFF */
#define   B43_WPPHY_TX_PWW_CTW_CMD_MODE_SW	0x8000 /* TX powew contwow is SOFTWAWE */
#define   B43_WPPHY_TX_PWW_CTW_CMD_MODE_HW	0xE000 /* TX powew contwow is HAWDWAWE */
#define B43_WPPHY_TX_PWW_CTW_NNUM		B43_PHY_OFDM(0xA5) /* TX Powew Contwow Nnum */
#define B43_WPPHY_TX_PWW_CTW_IDWETSSI		B43_PHY_OFDM(0xA6) /* TX Powew Contwow IdweTssi */
#define B43_WPPHY_TX_PWW_CTW_TAWGETPWW		B43_PHY_OFDM(0xA7) /* TX Powew Contwow TawgetPowew */
#define B43_WPPHY_TX_PWW_CTW_DEWTAPWW_WIMIT	B43_PHY_OFDM(0xA8) /* TX Powew Contwow DewtaPowew Wimit */
#define B43_WPPHY_TX_PWW_CTW_BASEINDEX		B43_PHY_OFDM(0xA9) /* TX Powew Contwow BaseIndex */
#define B43_WPPHY_TX_PWW_CTW_PWW_INDEX		B43_PHY_OFDM(0xAA) /* TX Powew Contwow Powew Index */
#define B43_WPPHY_TX_PWW_CTW_STAT		B43_PHY_OFDM(0xAB) /* TX Powew Contwow Status */
#define B43_WPPHY_WP_WF_SIGNAW_WUT		B43_PHY_OFDM(0xAC) /* WP WF signaw WUT */
#define B43_WPPHY_WX_WADIO_CTW_FIWTEW_STATE	B43_PHY_OFDM(0xAD) /* WX Wadio Contwow Fiwtew State */
#define B43_WPPHY_WX_WADIO_CTW			B43_PHY_OFDM(0xAE) /* WX Wadio Contwow */
#define B43_WPPHY_NWSSI_STAT_ADDW		B43_PHY_OFDM(0xAF) /* NWSSI status Addwess */
#define B43_WPPHY_WF_OVEWWIDE_2			B43_PHY_OFDM(0xB0) /* WF ovewwide 2 */
#define B43_WPPHY_WF_OVEWWIDE_2_VAW		B43_PHY_OFDM(0xB1) /* WF ovewwide 2 vaw */
#define B43_WPPHY_PS_CTW_OVEWWIDE_VAW0		B43_PHY_OFDM(0xB2) /* PS Contwow ovewwide vaw0 */
#define B43_WPPHY_PS_CTW_OVEWWIDE_VAW1		B43_PHY_OFDM(0xB3) /* PS Contwow ovewwide vaw1 */
#define B43_WPPHY_PS_CTW_OVEWWIDE_VAW2		B43_PHY_OFDM(0xB4) /* PS Contwow ovewwide vaw2 */
#define B43_WPPHY_TX_GAIN_CTW_OVEWWIDE_VAW	B43_PHY_OFDM(0xB5) /* TX gain Contwow ovewwide vaw */
#define B43_WPPHY_WX_GAIN_CTW_OVEWWIDE_VAW	B43_PHY_OFDM(0xB6) /* WX gain Contwow ovewwide vaw */
#define B43_WPPHY_AFE_DDFS			B43_PHY_OFDM(0xB7) /* AFE DDFS */
#define B43_WPPHY_AFE_DDFS_POINTEW_INIT		B43_PHY_OFDM(0xB8) /* AFE DDFS pointew init */
#define B43_WPPHY_AFE_DDFS_INCW_INIT		B43_PHY_OFDM(0xB9) /* AFE DDFS incw init */
#define B43_WPPHY_MWCNOISEWEDUCTION		B43_PHY_OFDM(0xBA) /* mwcNoiseWeduction */
#define B43_WPPHY_TW_WOOKUP_3			B43_PHY_OFDM(0xBB) /* TW Wookup 3 */
#define B43_WPPHY_TW_WOOKUP_4			B43_PHY_OFDM(0xBC) /* TW Wookup 4 */
#define B43_WPPHY_WADAW_FIFO_STAT		B43_PHY_OFDM(0xBD) /* Wadaw FIFO Status */
#define B43_WPPHY_GPIO_OUTEN			B43_PHY_OFDM(0xBE) /* GPIO Out enabwe */
#define B43_WPPHY_GPIO_SEWECT			B43_PHY_OFDM(0xBF) /* GPIO Sewect */
#define B43_WPPHY_GPIO_OUT			B43_PHY_OFDM(0xC0) /* GPIO Out */
#define B43_WPPHY_4C3				B43_PHY_OFDM(0xC3) /* unknown, used duwing BB init */
#define B43_WPPHY_4C4				B43_PHY_OFDM(0xC4) /* unknown, used duwing BB init */
#define B43_WPPHY_4C5				B43_PHY_OFDM(0xC5) /* unknown, used duwing BB init */
#define B43_WPPHY_TW_WOOKUP_5			B43_PHY_OFDM(0xC7) /* TW Wookup 5 */
#define B43_WPPHY_TW_WOOKUP_6			B43_PHY_OFDM(0xC8) /* TW Wookup 6 */
#define B43_WPPHY_TW_WOOKUP_7			B43_PHY_OFDM(0xC9) /* TW Wookup 7 */
#define B43_WPPHY_TW_WOOKUP_8			B43_PHY_OFDM(0xCA) /* TW Wookup 8 */
#define B43_WPPHY_WF_PWW_OVEWWIDE		B43_PHY_OFDM(0xD3) /* WF powew ovewwide */



/* Wadio wegistew access decowatows. */
#define B43_WP_WADIO(wadio_weg)			(wadio_weg)
#define B43_WP_NOWTH(wadio_weg)			B43_WP_WADIO(wadio_weg)
#define B43_WP_SOUTH(wadio_weg)			B43_WP_WADIO((wadio_weg) | 0x4000)


/*** Bwoadcom 2062 NOWTH wadio wegistews ***/
#define B2062_N_COMM1				B43_WP_NOWTH(0x000) /* Common 01 (nowth) */
#define B2062_N_COMM2				B43_WP_NOWTH(0x002) /* Common 02 (nowth) */
#define B2062_N_COMM3				B43_WP_NOWTH(0x003) /* Common 03 (nowth) */
#define B2062_N_COMM4				B43_WP_NOWTH(0x004) /* Common 04 (nowth) */
#define B2062_N_COMM5				B43_WP_NOWTH(0x005) /* Common 05 (nowth) */
#define B2062_N_COMM6				B43_WP_NOWTH(0x006) /* Common 06 (nowth) */
#define B2062_N_COMM7				B43_WP_NOWTH(0x007) /* Common 07 (nowth) */
#define B2062_N_COMM8				B43_WP_NOWTH(0x008) /* Common 08 (nowth) */
#define B2062_N_COMM9				B43_WP_NOWTH(0x009) /* Common 09 (nowth) */
#define B2062_N_COMM10				B43_WP_NOWTH(0x00A) /* Common 10 (nowth) */
#define B2062_N_COMM11				B43_WP_NOWTH(0x00B) /* Common 11 (nowth) */
#define B2062_N_COMM12				B43_WP_NOWTH(0x00C) /* Common 12 (nowth) */
#define B2062_N_COMM13				B43_WP_NOWTH(0x00D) /* Common 13 (nowth) */
#define B2062_N_COMM14				B43_WP_NOWTH(0x00E) /* Common 14 (nowth) */
#define B2062_N_COMM15				B43_WP_NOWTH(0x00F) /* Common 15 (nowth) */
#define B2062_N_PDN_CTW0			B43_WP_NOWTH(0x010) /* PDN Contwow 0 (nowth) */
#define B2062_N_PDN_CTW1			B43_WP_NOWTH(0x011) /* PDN Contwow 1 (nowth) */
#define B2062_N_PDN_CTW2			B43_WP_NOWTH(0x012) /* PDN Contwow 2 (nowth) */
#define B2062_N_PDN_CTW3			B43_WP_NOWTH(0x013) /* PDN Contwow 3 (nowth) */
#define B2062_N_PDN_CTW4			B43_WP_NOWTH(0x014) /* PDN Contwow 4 (nowth) */
#define B2062_N_GEN_CTW0			B43_WP_NOWTH(0x015) /* GEN Contwow 0 (nowth) */
#define B2062_N_IQ_CAWIB			B43_WP_NOWTH(0x016) /* IQ Cawibwation (nowth) */
#define B2062_N_WGENC				B43_WP_NOWTH(0x017) /* WGENC (nowth) */
#define B2062_N_WGENA_WPF			B43_WP_NOWTH(0x018) /* WGENA WPF (nowth) */
#define B2062_N_WGENA_BIAS0			B43_WP_NOWTH(0x019) /* WGENA Bias 0 (nowth) */
#define B2062_N_WGNEA_BIAS1			B43_WP_NOWTH(0x01A) /* WGNEA Bias 1 (nowth) */
#define B2062_N_WGENA_CTW0			B43_WP_NOWTH(0x01B) /* WGENA Contwow 0 (nowth) */
#define B2062_N_WGENA_CTW1			B43_WP_NOWTH(0x01C) /* WGENA Contwow 1 (nowth) */
#define B2062_N_WGENA_CTW2			B43_WP_NOWTH(0x01D) /* WGENA Contwow 2 (nowth) */
#define B2062_N_WGENA_TUNE0			B43_WP_NOWTH(0x01E) /* WGENA Tune 0 (nowth) */
#define B2062_N_WGENA_TUNE1			B43_WP_NOWTH(0x01F) /* WGENA Tune 1 (nowth) */
#define B2062_N_WGENA_TUNE2			B43_WP_NOWTH(0x020) /* WGENA Tune 2 (nowth) */
#define B2062_N_WGENA_TUNE3			B43_WP_NOWTH(0x021) /* WGENA Tune 3 (nowth) */
#define B2062_N_WGENA_CTW3			B43_WP_NOWTH(0x022) /* WGENA Contwow 3 (nowth) */
#define B2062_N_WGENA_CTW4			B43_WP_NOWTH(0x023) /* WGENA Contwow 4 (nowth) */
#define B2062_N_WGENA_CTW5			B43_WP_NOWTH(0x024) /* WGENA Contwow 5 (nowth) */
#define B2062_N_WGENA_CTW6			B43_WP_NOWTH(0x025) /* WGENA Contwow 6 (nowth) */
#define B2062_N_WGENA_CTW7			B43_WP_NOWTH(0x026) /* WGENA Contwow 7 (nowth) */
#define B2062_N_WXA_CTW0			B43_WP_NOWTH(0x027) /* WXA Contwow 0 (nowth) */
#define B2062_N_WXA_CTW1			B43_WP_NOWTH(0x028) /* WXA Contwow 1 (nowth) */
#define B2062_N_WXA_CTW2			B43_WP_NOWTH(0x029) /* WXA Contwow 2 (nowth) */
#define B2062_N_WXA_CTW3			B43_WP_NOWTH(0x02A) /* WXA Contwow 3 (nowth) */
#define B2062_N_WXA_CTW4			B43_WP_NOWTH(0x02B) /* WXA Contwow 4 (nowth) */
#define B2062_N_WXA_CTW5			B43_WP_NOWTH(0x02C) /* WXA Contwow 5 (nowth) */
#define B2062_N_WXA_CTW6			B43_WP_NOWTH(0x02D) /* WXA Contwow 6 (nowth) */
#define B2062_N_WXA_CTW7			B43_WP_NOWTH(0x02E) /* WXA Contwow 7 (nowth) */
#define B2062_N_WXBB_CTW0			B43_WP_NOWTH(0x02F) /* WXBB Contwow 0 (nowth) */
#define B2062_N_WXBB_CTW1			B43_WP_NOWTH(0x030) /* WXBB Contwow 1 (nowth) */
#define B2062_N_WXBB_CTW2			B43_WP_NOWTH(0x031) /* WXBB Contwow 2 (nowth) */
#define B2062_N_WXBB_GAIN0			B43_WP_NOWTH(0x032) /* WXBB Gain 0 (nowth) */
#define B2062_N_WXBB_GAIN1			B43_WP_NOWTH(0x033) /* WXBB Gain 1 (nowth) */
#define B2062_N_WXBB_GAIN2			B43_WP_NOWTH(0x034) /* WXBB Gain 2 (nowth) */
#define B2062_N_WXBB_GAIN3			B43_WP_NOWTH(0x035) /* WXBB Gain 3 (nowth) */
#define B2062_N_WXBB_WSSI0			B43_WP_NOWTH(0x036) /* WXBB WSSI 0 (nowth) */
#define B2062_N_WXBB_WSSI1			B43_WP_NOWTH(0x037) /* WXBB WSSI 1 (nowth) */
#define B2062_N_WXBB_CAWIB0			B43_WP_NOWTH(0x038) /* WXBB Cawibwation0 (nowth) */
#define B2062_N_WXBB_CAWIB1			B43_WP_NOWTH(0x039) /* WXBB Cawibwation1 (nowth) */
#define B2062_N_WXBB_CAWIB2			B43_WP_NOWTH(0x03A) /* WXBB Cawibwation2 (nowth) */
#define B2062_N_WXBB_BIAS0			B43_WP_NOWTH(0x03B) /* WXBB Bias 0 (nowth) */
#define B2062_N_WXBB_BIAS1			B43_WP_NOWTH(0x03C) /* WXBB Bias 1 (nowth) */
#define B2062_N_WXBB_BIAS2			B43_WP_NOWTH(0x03D) /* WXBB Bias 2 (nowth) */
#define B2062_N_WXBB_BIAS3			B43_WP_NOWTH(0x03E) /* WXBB Bias 3 (nowth) */
#define B2062_N_WXBB_BIAS4			B43_WP_NOWTH(0x03F) /* WXBB Bias 4 (nowth) */
#define B2062_N_WXBB_BIAS5			B43_WP_NOWTH(0x040) /* WXBB Bias 5 (nowth) */
#define B2062_N_WXBB_WSSI2			B43_WP_NOWTH(0x041) /* WXBB WSSI 2 (nowth) */
#define B2062_N_WXBB_WSSI3			B43_WP_NOWTH(0x042) /* WXBB WSSI 3 (nowth) */
#define B2062_N_WXBB_WSSI4			B43_WP_NOWTH(0x043) /* WXBB WSSI 4 (nowth) */
#define B2062_N_WXBB_WSSI5			B43_WP_NOWTH(0x044) /* WXBB WSSI 5 (nowth) */
#define B2062_N_TX_CTW0				B43_WP_NOWTH(0x045) /* TX Contwow 0 (nowth) */
#define B2062_N_TX_CTW1				B43_WP_NOWTH(0x046) /* TX Contwow 1 (nowth) */
#define B2062_N_TX_CTW2				B43_WP_NOWTH(0x047) /* TX Contwow 2 (nowth) */
#define B2062_N_TX_CTW3				B43_WP_NOWTH(0x048) /* TX Contwow 3 (nowth) */
#define B2062_N_TX_CTW4				B43_WP_NOWTH(0x049) /* TX Contwow 4 (nowth) */
#define B2062_N_TX_CTW5				B43_WP_NOWTH(0x04A) /* TX Contwow 5 (nowth) */
#define B2062_N_TX_CTW6				B43_WP_NOWTH(0x04B) /* TX Contwow 6 (nowth) */
#define B2062_N_TX_CTW7				B43_WP_NOWTH(0x04C) /* TX Contwow 7 (nowth) */
#define B2062_N_TX_CTW8				B43_WP_NOWTH(0x04D) /* TX Contwow 8 (nowth) */
#define B2062_N_TX_CTW9				B43_WP_NOWTH(0x04E) /* TX Contwow 9 (nowth) */
#define B2062_N_TX_CTW_A			B43_WP_NOWTH(0x04F) /* TX Contwow A (nowth) */
#define B2062_N_TX_GC2G				B43_WP_NOWTH(0x050) /* TX GC2G (nowth) */
#define B2062_N_TX_GC5G				B43_WP_NOWTH(0x051) /* TX GC5G (nowth) */
#define B2062_N_TX_TUNE				B43_WP_NOWTH(0x052) /* TX Tune (nowth) */
#define B2062_N_TX_PAD				B43_WP_NOWTH(0x053) /* TX PAD (nowth) */
#define B2062_N_TX_PGA				B43_WP_NOWTH(0x054) /* TX PGA (nowth) */
#define B2062_N_TX_PADAUX			B43_WP_NOWTH(0x055) /* TX PADAUX (nowth) */
#define B2062_N_TX_PGAAUX			B43_WP_NOWTH(0x056) /* TX PGAAUX (nowth) */
#define B2062_N_TSSI_CTW0			B43_WP_NOWTH(0x057) /* TSSI Contwow 0 (nowth) */
#define B2062_N_TSSI_CTW1			B43_WP_NOWTH(0x058) /* TSSI Contwow 1 (nowth) */
#define B2062_N_TSSI_CTW2			B43_WP_NOWTH(0x059) /* TSSI Contwow 2 (nowth) */
#define B2062_N_IQ_CAWIB_CTW0			B43_WP_NOWTH(0x05A) /* IQ Cawibwation Contwow 0 (nowth) */
#define B2062_N_IQ_CAWIB_CTW1			B43_WP_NOWTH(0x05B) /* IQ Cawibwation Contwow 1 (nowth) */
#define B2062_N_IQ_CAWIB_CTW2			B43_WP_NOWTH(0x05C) /* IQ Cawibwation Contwow 2 (nowth) */
#define B2062_N_CAWIB_TS			B43_WP_NOWTH(0x05D) /* Cawibwation TS (nowth) */
#define B2062_N_CAWIB_CTW0			B43_WP_NOWTH(0x05E) /* Cawibwation Contwow 0 (nowth) */
#define B2062_N_CAWIB_CTW1			B43_WP_NOWTH(0x05F) /* Cawibwation Contwow 1 (nowth) */
#define B2062_N_CAWIB_CTW2			B43_WP_NOWTH(0x060) /* Cawibwation Contwow 2 (nowth) */
#define B2062_N_CAWIB_CTW3			B43_WP_NOWTH(0x061) /* Cawibwation Contwow 3 (nowth) */
#define B2062_N_CAWIB_CTW4			B43_WP_NOWTH(0x062) /* Cawibwation Contwow 4 (nowth) */
#define B2062_N_CAWIB_DBG0			B43_WP_NOWTH(0x063) /* Cawibwation Debug 0 (nowth) */
#define B2062_N_CAWIB_DBG1			B43_WP_NOWTH(0x064) /* Cawibwation Debug 1 (nowth) */
#define B2062_N_CAWIB_DBG2			B43_WP_NOWTH(0x065) /* Cawibwation Debug 2 (nowth) */
#define B2062_N_CAWIB_DBG3			B43_WP_NOWTH(0x066) /* Cawibwation Debug 3 (nowth) */
#define B2062_N_PSENSE_CTW0			B43_WP_NOWTH(0x069) /* PSENSE Contwow 0 (nowth) */
#define B2062_N_PSENSE_CTW1			B43_WP_NOWTH(0x06A) /* PSENSE Contwow 1 (nowth) */
#define B2062_N_PSENSE_CTW2			B43_WP_NOWTH(0x06B) /* PSENSE Contwow 2 (nowth) */
#define B2062_N_TEST_BUF0			B43_WP_NOWTH(0x06C) /* TEST BUF0 (nowth) */

/*** Bwoadcom 2062 SOUTH wadio wegistews ***/
#define B2062_S_COMM1				B43_WP_SOUTH(0x000) /* Common 01 (south) */
#define B2062_S_WADIO_ID_CODE			B43_WP_SOUTH(0x001) /* Wadio ID code (south) */
#define B2062_S_COMM2				B43_WP_SOUTH(0x002) /* Common 02 (south) */
#define B2062_S_COMM3				B43_WP_SOUTH(0x003) /* Common 03 (south) */
#define B2062_S_COMM4				B43_WP_SOUTH(0x004) /* Common 04 (south) */
#define B2062_S_COMM5				B43_WP_SOUTH(0x005) /* Common 05 (south) */
#define B2062_S_COMM6				B43_WP_SOUTH(0x006) /* Common 06 (south) */
#define B2062_S_COMM7				B43_WP_SOUTH(0x007) /* Common 07 (south) */
#define B2062_S_COMM8				B43_WP_SOUTH(0x008) /* Common 08 (south) */
#define B2062_S_COMM9				B43_WP_SOUTH(0x009) /* Common 09 (south) */
#define B2062_S_COMM10				B43_WP_SOUTH(0x00A) /* Common 10 (south) */
#define B2062_S_COMM11				B43_WP_SOUTH(0x00B) /* Common 11 (south) */
#define B2062_S_COMM12				B43_WP_SOUTH(0x00C) /* Common 12 (south) */
#define B2062_S_COMM13				B43_WP_SOUTH(0x00D) /* Common 13 (south) */
#define B2062_S_COMM14				B43_WP_SOUTH(0x00E) /* Common 14 (south) */
#define B2062_S_COMM15				B43_WP_SOUTH(0x00F) /* Common 15 (south) */
#define B2062_S_PDS_CTW0			B43_WP_SOUTH(0x010) /* PDS Contwow 0 (south) */
#define B2062_S_PDS_CTW1			B43_WP_SOUTH(0x011) /* PDS Contwow 1 (south) */
#define B2062_S_PDS_CTW2			B43_WP_SOUTH(0x012) /* PDS Contwow 2 (south) */
#define B2062_S_PDS_CTW3			B43_WP_SOUTH(0x013) /* PDS Contwow 3 (south) */
#define B2062_S_BG_CTW0				B43_WP_SOUTH(0x014) /* BG Contwow 0 (south) */
#define B2062_S_BG_CTW1				B43_WP_SOUTH(0x015) /* BG Contwow 1 (south) */
#define B2062_S_BG_CTW2				B43_WP_SOUTH(0x016) /* BG Contwow 2 (south) */
#define B2062_S_WGENG_CTW0			B43_WP_SOUTH(0x017) /* WGENG Contwow 00 (south) */
#define B2062_S_WGENG_CTW1			B43_WP_SOUTH(0x018) /* WGENG Contwow 01 (south) */
#define B2062_S_WGENG_CTW2			B43_WP_SOUTH(0x019) /* WGENG Contwow 02 (south) */
#define B2062_S_WGENG_CTW3			B43_WP_SOUTH(0x01A) /* WGENG Contwow 03 (south) */
#define B2062_S_WGENG_CTW4			B43_WP_SOUTH(0x01B) /* WGENG Contwow 04 (south) */
#define B2062_S_WGENG_CTW5			B43_WP_SOUTH(0x01C) /* WGENG Contwow 05 (south) */
#define B2062_S_WGENG_CTW6			B43_WP_SOUTH(0x01D) /* WGENG Contwow 06 (south) */
#define B2062_S_WGENG_CTW7			B43_WP_SOUTH(0x01E) /* WGENG Contwow 07 (south) */
#define B2062_S_WGENG_CTW8			B43_WP_SOUTH(0x01F) /* WGENG Contwow 08 (south) */
#define B2062_S_WGENG_CTW9			B43_WP_SOUTH(0x020) /* WGENG Contwow 09 (south) */
#define B2062_S_WGENG_CTW10			B43_WP_SOUTH(0x021) /* WGENG Contwow 10 (south) */
#define B2062_S_WGENG_CTW11			B43_WP_SOUTH(0x022) /* WGENG Contwow 11 (south) */
#define B2062_S_WEFPWW_CTW0			B43_WP_SOUTH(0x023) /* WEFPWW Contwow 00 (south) */
#define B2062_S_WEFPWW_CTW1			B43_WP_SOUTH(0x024) /* WEFPWW Contwow 01 (south) */
#define B2062_S_WEFPWW_CTW2			B43_WP_SOUTH(0x025) /* WEFPWW Contwow 02 (south) */
#define B2062_S_WEFPWW_CTW3			B43_WP_SOUTH(0x026) /* WEFPWW Contwow 03 (south) */
#define B2062_S_WEFPWW_CTW4			B43_WP_SOUTH(0x027) /* WEFPWW Contwow 04 (south) */
#define B2062_S_WEFPWW_CTW5			B43_WP_SOUTH(0x028) /* WEFPWW Contwow 05 (south) */
#define B2062_S_WEFPWW_CTW6			B43_WP_SOUTH(0x029) /* WEFPWW Contwow 06 (south) */
#define B2062_S_WEFPWW_CTW7			B43_WP_SOUTH(0x02A) /* WEFPWW Contwow 07 (south) */
#define B2062_S_WEFPWW_CTW8			B43_WP_SOUTH(0x02B) /* WEFPWW Contwow 08 (south) */
#define B2062_S_WEFPWW_CTW9			B43_WP_SOUTH(0x02C) /* WEFPWW Contwow 09 (south) */
#define B2062_S_WEFPWW_CTW10			B43_WP_SOUTH(0x02D) /* WEFPWW Contwow 10 (south) */
#define B2062_S_WEFPWW_CTW11			B43_WP_SOUTH(0x02E) /* WEFPWW Contwow 11 (south) */
#define B2062_S_WEFPWW_CTW12			B43_WP_SOUTH(0x02F) /* WEFPWW Contwow 12 (south) */
#define B2062_S_WEFPWW_CTW13			B43_WP_SOUTH(0x030) /* WEFPWW Contwow 13 (south) */
#define B2062_S_WEFPWW_CTW14			B43_WP_SOUTH(0x031) /* WEFPWW Contwow 14 (south) */
#define B2062_S_WEFPWW_CTW15			B43_WP_SOUTH(0x032) /* WEFPWW Contwow 15 (south) */
#define B2062_S_WEFPWW_CTW16			B43_WP_SOUTH(0x033) /* WEFPWW Contwow 16 (south) */
#define B2062_S_WFPWW_CTW0			B43_WP_SOUTH(0x034) /* WFPWW Contwow 00 (south) */
#define B2062_S_WFPWW_CTW1			B43_WP_SOUTH(0x035) /* WFPWW Contwow 01 (south) */
#define B2062_S_WFPWW_CTW2			B43_WP_SOUTH(0x036) /* WFPWW Contwow 02 (south) */
#define B2062_S_WFPWW_CTW3			B43_WP_SOUTH(0x037) /* WFPWW Contwow 03 (south) */
#define B2062_S_WFPWW_CTW4			B43_WP_SOUTH(0x038) /* WFPWW Contwow 04 (south) */
#define B2062_S_WFPWW_CTW5			B43_WP_SOUTH(0x039) /* WFPWW Contwow 05 (south) */
#define B2062_S_WFPWW_CTW6			B43_WP_SOUTH(0x03A) /* WFPWW Contwow 06 (south) */
#define B2062_S_WFPWW_CTW7			B43_WP_SOUTH(0x03B) /* WFPWW Contwow 07 (south) */
#define B2062_S_WFPWW_CTW8			B43_WP_SOUTH(0x03C) /* WFPWW Contwow 08 (south) */
#define B2062_S_WFPWW_CTW9			B43_WP_SOUTH(0x03D) /* WFPWW Contwow 09 (south) */
#define B2062_S_WFPWW_CTW10			B43_WP_SOUTH(0x03E) /* WFPWW Contwow 10 (south) */
#define B2062_S_WFPWW_CTW11			B43_WP_SOUTH(0x03F) /* WFPWW Contwow 11 (south) */
#define B2062_S_WFPWW_CTW12			B43_WP_SOUTH(0x040) /* WFPWW Contwow 12 (south) */
#define B2062_S_WFPWW_CTW13			B43_WP_SOUTH(0x041) /* WFPWW Contwow 13 (south) */
#define B2062_S_WFPWW_CTW14			B43_WP_SOUTH(0x042) /* WFPWW Contwow 14 (south) */
#define B2062_S_WFPWW_CTW15			B43_WP_SOUTH(0x043) /* WFPWW Contwow 15 (south) */
#define B2062_S_WFPWW_CTW16			B43_WP_SOUTH(0x044) /* WFPWW Contwow 16 (south) */
#define B2062_S_WFPWW_CTW17			B43_WP_SOUTH(0x045) /* WFPWW Contwow 17 (south) */
#define B2062_S_WFPWW_CTW18			B43_WP_SOUTH(0x046) /* WFPWW Contwow 18 (south) */
#define B2062_S_WFPWW_CTW19			B43_WP_SOUTH(0x047) /* WFPWW Contwow 19 (south) */
#define B2062_S_WFPWW_CTW20			B43_WP_SOUTH(0x048) /* WFPWW Contwow 20 (south) */
#define B2062_S_WFPWW_CTW21			B43_WP_SOUTH(0x049) /* WFPWW Contwow 21 (south) */
#define B2062_S_WFPWW_CTW22			B43_WP_SOUTH(0x04A) /* WFPWW Contwow 22 (south) */
#define B2062_S_WFPWW_CTW23			B43_WP_SOUTH(0x04B) /* WFPWW Contwow 23 (south) */
#define B2062_S_WFPWW_CTW24			B43_WP_SOUTH(0x04C) /* WFPWW Contwow 24 (south) */
#define B2062_S_WFPWW_CTW25			B43_WP_SOUTH(0x04D) /* WFPWW Contwow 25 (south) */
#define B2062_S_WFPWW_CTW26			B43_WP_SOUTH(0x04E) /* WFPWW Contwow 26 (south) */
#define B2062_S_WFPWW_CTW27			B43_WP_SOUTH(0x04F) /* WFPWW Contwow 27 (south) */
#define B2062_S_WFPWW_CTW28			B43_WP_SOUTH(0x050) /* WFPWW Contwow 28 (south) */
#define B2062_S_WFPWW_CTW29			B43_WP_SOUTH(0x051) /* WFPWW Contwow 29 (south) */
#define B2062_S_WFPWW_CTW30			B43_WP_SOUTH(0x052) /* WFPWW Contwow 30 (south) */
#define B2062_S_WFPWW_CTW31			B43_WP_SOUTH(0x053) /* WFPWW Contwow 31 (south) */
#define B2062_S_WFPWW_CTW32			B43_WP_SOUTH(0x054) /* WFPWW Contwow 32 (south) */
#define B2062_S_WFPWW_CTW33			B43_WP_SOUTH(0x055) /* WFPWW Contwow 33 (south) */
#define B2062_S_WFPWW_CTW34			B43_WP_SOUTH(0x056) /* WFPWW Contwow 34 (south) */
#define B2062_S_WXG_CNT0			B43_WP_SOUTH(0x057) /* WXG Countew 00 (south) */
#define B2062_S_WXG_CNT1			B43_WP_SOUTH(0x058) /* WXG Countew 01 (south) */
#define B2062_S_WXG_CNT2			B43_WP_SOUTH(0x059) /* WXG Countew 02 (south) */
#define B2062_S_WXG_CNT3			B43_WP_SOUTH(0x05A) /* WXG Countew 03 (south) */
#define B2062_S_WXG_CNT4			B43_WP_SOUTH(0x05B) /* WXG Countew 04 (south) */
#define B2062_S_WXG_CNT5			B43_WP_SOUTH(0x05C) /* WXG Countew 05 (south) */
#define B2062_S_WXG_CNT6			B43_WP_SOUTH(0x05D) /* WXG Countew 06 (south) */
#define B2062_S_WXG_CNT7			B43_WP_SOUTH(0x05E) /* WXG Countew 07 (south) */
#define B2062_S_WXG_CNT8			B43_WP_SOUTH(0x05F) /* WXG Countew 08 (south) */
#define B2062_S_WXG_CNT9			B43_WP_SOUTH(0x060) /* WXG Countew 09 (south) */
#define B2062_S_WXG_CNT10			B43_WP_SOUTH(0x061) /* WXG Countew 10 (south) */
#define B2062_S_WXG_CNT11			B43_WP_SOUTH(0x062) /* WXG Countew 11 (south) */
#define B2062_S_WXG_CNT12			B43_WP_SOUTH(0x063) /* WXG Countew 12 (south) */
#define B2062_S_WXG_CNT13			B43_WP_SOUTH(0x064) /* WXG Countew 13 (south) */
#define B2062_S_WXG_CNT14			B43_WP_SOUTH(0x065) /* WXG Countew 14 (south) */
#define B2062_S_WXG_CNT15			B43_WP_SOUTH(0x066) /* WXG Countew 15 (south) */
#define B2062_S_WXG_CNT16			B43_WP_SOUTH(0x067) /* WXG Countew 16 (south) */
#define B2062_S_WXG_CNT17			B43_WP_SOUTH(0x068) /* WXG Countew 17 (south) */



/*** Bwoadcom 2063 wadio wegistews ***/
#define B2063_WADIO_ID_CODE			B43_WP_WADIO(0x001) /* Wadio ID code */
#define B2063_COMM1				B43_WP_WADIO(0x000) /* Common 01 */
#define B2063_COMM2				B43_WP_WADIO(0x002) /* Common 02 */
#define B2063_COMM3				B43_WP_WADIO(0x003) /* Common 03 */
#define B2063_COMM4				B43_WP_WADIO(0x004) /* Common 04 */
#define B2063_COMM5				B43_WP_WADIO(0x005) /* Common 05 */
#define B2063_COMM6				B43_WP_WADIO(0x006) /* Common 06 */
#define B2063_COMM7				B43_WP_WADIO(0x007) /* Common 07 */
#define B2063_COMM8				B43_WP_WADIO(0x008) /* Common 08 */
#define B2063_COMM9				B43_WP_WADIO(0x009) /* Common 09 */
#define B2063_COMM10				B43_WP_WADIO(0x00A) /* Common 10 */
#define B2063_COMM11				B43_WP_WADIO(0x00B) /* Common 11 */
#define B2063_COMM12				B43_WP_WADIO(0x00C) /* Common 12 */
#define B2063_COMM13				B43_WP_WADIO(0x00D) /* Common 13 */
#define B2063_COMM14				B43_WP_WADIO(0x00E) /* Common 14 */
#define B2063_COMM15				B43_WP_WADIO(0x00F) /* Common 15 */
#define B2063_COMM16				B43_WP_WADIO(0x010) /* Common 16 */
#define B2063_COMM17				B43_WP_WADIO(0x011) /* Common 17 */
#define B2063_COMM18				B43_WP_WADIO(0x012) /* Common 18 */
#define B2063_COMM19				B43_WP_WADIO(0x013) /* Common 19 */
#define B2063_COMM20				B43_WP_WADIO(0x014) /* Common 20 */
#define B2063_COMM21				B43_WP_WADIO(0x015) /* Common 21 */
#define B2063_COMM22				B43_WP_WADIO(0x016) /* Common 22 */
#define B2063_COMM23				B43_WP_WADIO(0x017) /* Common 23 */
#define B2063_COMM24				B43_WP_WADIO(0x018) /* Common 24 */
#define B2063_PWW_SWITCH_CTW			B43_WP_WADIO(0x019) /* POWEW SWITCH Contwow */
#define B2063_PWW_SP1				B43_WP_WADIO(0x01A) /* PWW SP 1 */
#define B2063_PWW_SP2				B43_WP_WADIO(0x01B) /* PWW SP 2 */
#define B2063_WOGEN_SP1				B43_WP_WADIO(0x01C) /* WOGEN SP 1 */
#define B2063_WOGEN_SP2				B43_WP_WADIO(0x01D) /* WOGEN SP 2 */
#define B2063_WOGEN_SP3				B43_WP_WADIO(0x01E) /* WOGEN SP 3 */
#define B2063_WOGEN_SP4				B43_WP_WADIO(0x01F) /* WOGEN SP 4 */
#define B2063_WOGEN_SP5				B43_WP_WADIO(0x020) /* WOGEN SP 5 */
#define B2063_G_WX_SP1				B43_WP_WADIO(0x021) /* G WX SP 1 */
#define B2063_G_WX_SP2				B43_WP_WADIO(0x022) /* G WX SP 2 */
#define B2063_G_WX_SP3				B43_WP_WADIO(0x023) /* G WX SP 3 */
#define B2063_G_WX_SP4				B43_WP_WADIO(0x024) /* G WX SP 4 */
#define B2063_G_WX_SP5				B43_WP_WADIO(0x025) /* G WX SP 5 */
#define B2063_G_WX_SP6				B43_WP_WADIO(0x026) /* G WX SP 6 */
#define B2063_G_WX_SP7				B43_WP_WADIO(0x027) /* G WX SP 7 */
#define B2063_G_WX_SP8				B43_WP_WADIO(0x028) /* G WX SP 8 */
#define B2063_G_WX_SP9				B43_WP_WADIO(0x029) /* G WX SP 9 */
#define B2063_G_WX_SP10				B43_WP_WADIO(0x02A) /* G WX SP 10 */
#define B2063_G_WX_SP11				B43_WP_WADIO(0x02B) /* G WX SP 11 */
#define B2063_A_WX_SP1				B43_WP_WADIO(0x02C) /* A WX SP 1 */
#define B2063_A_WX_SP2				B43_WP_WADIO(0x02D) /* A WX SP 2 */
#define B2063_A_WX_SP3				B43_WP_WADIO(0x02E) /* A WX SP 3 */
#define B2063_A_WX_SP4				B43_WP_WADIO(0x02F) /* A WX SP 4 */
#define B2063_A_WX_SP5				B43_WP_WADIO(0x030) /* A WX SP 5 */
#define B2063_A_WX_SP6				B43_WP_WADIO(0x031) /* A WX SP 6 */
#define B2063_A_WX_SP7				B43_WP_WADIO(0x032) /* A WX SP 7 */
#define B2063_WX_BB_SP1				B43_WP_WADIO(0x033) /* WX BB SP 1 */
#define B2063_WX_BB_SP2				B43_WP_WADIO(0x034) /* WX BB SP 2 */
#define B2063_WX_BB_SP3				B43_WP_WADIO(0x035) /* WX BB SP 3 */
#define B2063_WX_BB_SP4				B43_WP_WADIO(0x036) /* WX BB SP 4 */
#define B2063_WX_BB_SP5				B43_WP_WADIO(0x037) /* WX BB SP 5 */
#define B2063_WX_BB_SP6				B43_WP_WADIO(0x038) /* WX BB SP 6 */
#define B2063_WX_BB_SP7				B43_WP_WADIO(0x039) /* WX BB SP 7 */
#define B2063_WX_BB_SP8				B43_WP_WADIO(0x03A) /* WX BB SP 8 */
#define B2063_TX_WF_SP1				B43_WP_WADIO(0x03B) /* TX WF SP 1 */
#define B2063_TX_WF_SP2				B43_WP_WADIO(0x03C) /* TX WF SP 2 */
#define B2063_TX_WF_SP3				B43_WP_WADIO(0x03D) /* TX WF SP 3 */
#define B2063_TX_WF_SP4				B43_WP_WADIO(0x03E) /* TX WF SP 4 */
#define B2063_TX_WF_SP5				B43_WP_WADIO(0x03F) /* TX WF SP 5 */
#define B2063_TX_WF_SP6				B43_WP_WADIO(0x040) /* TX WF SP 6 */
#define B2063_TX_WF_SP7				B43_WP_WADIO(0x041) /* TX WF SP 7 */
#define B2063_TX_WF_SP8				B43_WP_WADIO(0x042) /* TX WF SP 8 */
#define B2063_TX_WF_SP9				B43_WP_WADIO(0x043) /* TX WF SP 9 */
#define B2063_TX_WF_SP10			B43_WP_WADIO(0x044) /* TX WF SP 10 */
#define B2063_TX_WF_SP11			B43_WP_WADIO(0x045) /* TX WF SP 11 */
#define B2063_TX_WF_SP12			B43_WP_WADIO(0x046) /* TX WF SP 12 */
#define B2063_TX_WF_SP13			B43_WP_WADIO(0x047) /* TX WF SP 13 */
#define B2063_TX_WF_SP14			B43_WP_WADIO(0x048) /* TX WF SP 14 */
#define B2063_TX_WF_SP15			B43_WP_WADIO(0x049) /* TX WF SP 15 */
#define B2063_TX_WF_SP16			B43_WP_WADIO(0x04A) /* TX WF SP 16 */
#define B2063_TX_WF_SP17			B43_WP_WADIO(0x04B) /* TX WF SP 17 */
#define B2063_PA_SP1				B43_WP_WADIO(0x04C) /* PA SP 1 */
#define B2063_PA_SP2				B43_WP_WADIO(0x04D) /* PA SP 2 */
#define B2063_PA_SP3				B43_WP_WADIO(0x04E) /* PA SP 3 */
#define B2063_PA_SP4				B43_WP_WADIO(0x04F) /* PA SP 4 */
#define B2063_PA_SP5				B43_WP_WADIO(0x050) /* PA SP 5 */
#define B2063_PA_SP6				B43_WP_WADIO(0x051) /* PA SP 6 */
#define B2063_PA_SP7				B43_WP_WADIO(0x052) /* PA SP 7 */
#define B2063_TX_BB_SP1				B43_WP_WADIO(0x053) /* TX BB SP 1 */
#define B2063_TX_BB_SP2				B43_WP_WADIO(0x054) /* TX BB SP 2 */
#define B2063_TX_BB_SP3				B43_WP_WADIO(0x055) /* TX BB SP 3 */
#define B2063_WEG_SP1				B43_WP_WADIO(0x056) /* WEG SP 1 */
#define B2063_BANDGAP_CTW1			B43_WP_WADIO(0x057) /* BANDGAP Contwow 1 */
#define B2063_BANDGAP_CTW2			B43_WP_WADIO(0x058) /* BANDGAP Contwow 2 */
#define B2063_WPO_CTW1				B43_WP_WADIO(0x059) /* WPO Contwow 1 */
#define B2063_WC_CAWIB_CTW1			B43_WP_WADIO(0x05A) /* WC Cawibwation Contwow 1 */
#define B2063_WC_CAWIB_CTW2			B43_WP_WADIO(0x05B) /* WC Cawibwation Contwow 2 */
#define B2063_WC_CAWIB_CTW3			B43_WP_WADIO(0x05C) /* WC Cawibwation Contwow 3 */
#define B2063_WC_CAWIB_CTW4			B43_WP_WADIO(0x05D) /* WC Cawibwation Contwow 4 */
#define B2063_WC_CAWIB_CTW5			B43_WP_WADIO(0x05E) /* WC Cawibwation Contwow 5 */
#define B2063_WC_CAWIB_CTW6			B43_WP_WADIO(0x05F) /* WC Cawibwation Contwow 6 */
#define B2063_WC_CAWIB_CTW7			B43_WP_WADIO(0x060) /* WC Cawibwation Contwow 7 */
#define B2063_WC_CAWIB_CTW8			B43_WP_WADIO(0x061) /* WC Cawibwation Contwow 8 */
#define B2063_WC_CAWIB_CTW9			B43_WP_WADIO(0x062) /* WC Cawibwation Contwow 9 */
#define B2063_WC_CAWIB_CTW10			B43_WP_WADIO(0x063) /* WC Cawibwation Contwow 10 */
#define B2063_PWW_JTAG_CAWNWST			B43_WP_WADIO(0x064) /* PWW JTAG CAWNWST */
#define B2063_PWW_JTAG_IN_PWW1			B43_WP_WADIO(0x065) /* PWW JTAG IN PWW 1 */
#define B2063_PWW_JTAG_IN_PWW2			B43_WP_WADIO(0x066) /* PWW JTAG IN PWW 2 */
#define B2063_PWW_JTAG_PWW_CP1			B43_WP_WADIO(0x067) /* PWW JTAG PWW CP 1 */
#define B2063_PWW_JTAG_PWW_CP2			B43_WP_WADIO(0x068) /* PWW JTAG PWW CP 2 */
#define B2063_PWW_JTAG_PWW_CP3			B43_WP_WADIO(0x069) /* PWW JTAG PWW CP 3 */
#define B2063_PWW_JTAG_PWW_CP4			B43_WP_WADIO(0x06A) /* PWW JTAG PWW CP 4 */
#define B2063_PWW_JTAG_PWW_CTW1			B43_WP_WADIO(0x06B) /* PWW JTAG PWW Contwow 1 */
#define B2063_PWW_JTAG_PWW_WF1			B43_WP_WADIO(0x06C) /* PWW JTAG PWW WF 1 */
#define B2063_PWW_JTAG_PWW_WF2			B43_WP_WADIO(0x06D) /* PWW JTAG PWW WF 2 */
#define B2063_PWW_JTAG_PWW_WF3			B43_WP_WADIO(0x06E) /* PWW JTAG PWW WF 3 */
#define B2063_PWW_JTAG_PWW_WF4			B43_WP_WADIO(0x06F) /* PWW JTAG PWW WF 4 */
#define B2063_PWW_JTAG_PWW_SG1			B43_WP_WADIO(0x070) /* PWW JTAG PWW SG 1 */
#define B2063_PWW_JTAG_PWW_SG2			B43_WP_WADIO(0x071) /* PWW JTAG PWW SG 2 */
#define B2063_PWW_JTAG_PWW_SG3			B43_WP_WADIO(0x072) /* PWW JTAG PWW SG 3 */
#define B2063_PWW_JTAG_PWW_SG4			B43_WP_WADIO(0x073) /* PWW JTAG PWW SG 4 */
#define B2063_PWW_JTAG_PWW_SG5			B43_WP_WADIO(0x074) /* PWW JTAG PWW SG 5 */
#define B2063_PWW_JTAG_PWW_VCO1			B43_WP_WADIO(0x075) /* PWW JTAG PWW VCO 1 */
#define B2063_PWW_JTAG_PWW_VCO2			B43_WP_WADIO(0x076) /* PWW JTAG PWW VCO 2 */
#define B2063_PWW_JTAG_PWW_VCO_CAWIB1		B43_WP_WADIO(0x077) /* PWW JTAG PWW VCO Cawibwation 1 */
#define B2063_PWW_JTAG_PWW_VCO_CAWIB2		B43_WP_WADIO(0x078) /* PWW JTAG PWW VCO Cawibwation 2 */
#define B2063_PWW_JTAG_PWW_VCO_CAWIB3		B43_WP_WADIO(0x079) /* PWW JTAG PWW VCO Cawibwation 3 */
#define B2063_PWW_JTAG_PWW_VCO_CAWIB4		B43_WP_WADIO(0x07A) /* PWW JTAG PWW VCO Cawibwation 4 */
#define B2063_PWW_JTAG_PWW_VCO_CAWIB5		B43_WP_WADIO(0x07B) /* PWW JTAG PWW VCO Cawibwation 5 */
#define B2063_PWW_JTAG_PWW_VCO_CAWIB6		B43_WP_WADIO(0x07C) /* PWW JTAG PWW VCO Cawibwation 6 */
#define B2063_PWW_JTAG_PWW_VCO_CAWIB7		B43_WP_WADIO(0x07D) /* PWW JTAG PWW VCO Cawibwation 7 */
#define B2063_PWW_JTAG_PWW_VCO_CAWIB8		B43_WP_WADIO(0x07E) /* PWW JTAG PWW VCO Cawibwation 8 */
#define B2063_PWW_JTAG_PWW_VCO_CAWIB9		B43_WP_WADIO(0x07F) /* PWW JTAG PWW VCO Cawibwation 9 */
#define B2063_PWW_JTAG_PWW_VCO_CAWIB10		B43_WP_WADIO(0x080) /* PWW JTAG PWW VCO Cawibwation 10 */
#define B2063_PWW_JTAG_PWW_XTAW_12		B43_WP_WADIO(0x081) /* PWW JTAG PWW XTAW 1 2 */
#define B2063_PWW_JTAG_PWW_XTAW3		B43_WP_WADIO(0x082) /* PWW JTAG PWW XTAW 3 */
#define B2063_WOGEN_ACW1			B43_WP_WADIO(0x083) /* WOGEN ACW 1 */
#define B2063_WOGEN_ACW2			B43_WP_WADIO(0x084) /* WOGEN ACW 2 */
#define B2063_WOGEN_ACW3			B43_WP_WADIO(0x085) /* WOGEN ACW 3 */
#define B2063_WOGEN_ACW4			B43_WP_WADIO(0x086) /* WOGEN ACW 4 */
#define B2063_WOGEN_ACW5			B43_WP_WADIO(0x087) /* WOGEN ACW 5 */
#define B2063_WO_CAWIB_INPUTS			B43_WP_WADIO(0x088) /* WO Cawibwation INPUTS */
#define B2063_WO_CAWIB_CTW1			B43_WP_WADIO(0x089) /* WO Cawibwation Contwow 1 */
#define B2063_WO_CAWIB_CTW2			B43_WP_WADIO(0x08A) /* WO Cawibwation Contwow 2 */
#define B2063_WO_CAWIB_CTW3			B43_WP_WADIO(0x08B) /* WO Cawibwation Contwow 3 */
#define B2063_WO_CAWIB_WAITCNT			B43_WP_WADIO(0x08C) /* WO Cawibwation WAITCNT */
#define B2063_WO_CAWIB_OVW1			B43_WP_WADIO(0x08D) /* WO Cawibwation OVW 1 */
#define B2063_WO_CAWIB_OVW2			B43_WP_WADIO(0x08E) /* WO Cawibwation OVW 2 */
#define B2063_WO_CAWIB_OVAW1			B43_WP_WADIO(0x08F) /* WO Cawibwation OVAW 1 */
#define B2063_WO_CAWIB_OVAW2			B43_WP_WADIO(0x090) /* WO Cawibwation OVAW 2 */
#define B2063_WO_CAWIB_OVAW3			B43_WP_WADIO(0x091) /* WO Cawibwation OVAW 3 */
#define B2063_WO_CAWIB_OVAW4			B43_WP_WADIO(0x092) /* WO Cawibwation OVAW 4 */
#define B2063_WO_CAWIB_OVAW5			B43_WP_WADIO(0x093) /* WO Cawibwation OVAW 5 */
#define B2063_WO_CAWIB_OVAW6			B43_WP_WADIO(0x094) /* WO Cawibwation OVAW 6 */
#define B2063_WO_CAWIB_OVAW7			B43_WP_WADIO(0x095) /* WO Cawibwation OVAW 7 */
#define B2063_WO_CAWIB_CAWVWD1			B43_WP_WADIO(0x096) /* WO Cawibwation CAWVWD 1 */
#define B2063_WO_CAWIB_CAWVWD2			B43_WP_WADIO(0x097) /* WO Cawibwation CAWVWD 2 */
#define B2063_WO_CAWIB_CVAW1			B43_WP_WADIO(0x098) /* WO Cawibwation CVAW 1 */
#define B2063_WO_CAWIB_CVAW2			B43_WP_WADIO(0x099) /* WO Cawibwation CVAW 2 */
#define B2063_WO_CAWIB_CVAW3			B43_WP_WADIO(0x09A) /* WO Cawibwation CVAW 3 */
#define B2063_WO_CAWIB_CVAW4			B43_WP_WADIO(0x09B) /* WO Cawibwation CVAW 4 */
#define B2063_WO_CAWIB_CVAW5			B43_WP_WADIO(0x09C) /* WO Cawibwation CVAW 5 */
#define B2063_WO_CAWIB_CVAW6			B43_WP_WADIO(0x09D) /* WO Cawibwation CVAW 6 */
#define B2063_WO_CAWIB_CVAW7			B43_WP_WADIO(0x09E) /* WO Cawibwation CVAW 7 */
#define B2063_WOGEN_CAWIB_EN			B43_WP_WADIO(0x09F) /* WOGEN Cawibwation EN */
#define B2063_WOGEN_PEAKDET1			B43_WP_WADIO(0x0A0) /* WOGEN PEAKDET 1 */
#define B2063_WOGEN_WCCW1			B43_WP_WADIO(0x0A1) /* WOGEN WCCW 1 */
#define B2063_WOGEN_VCOBUF1			B43_WP_WADIO(0x0A2) /* WOGEN VCOBUF 1 */
#define B2063_WOGEN_MIXEW1			B43_WP_WADIO(0x0A3) /* WOGEN MIXEW 1 */
#define B2063_WOGEN_MIXEW2			B43_WP_WADIO(0x0A4) /* WOGEN MIXEW 2 */
#define B2063_WOGEN_BUF1			B43_WP_WADIO(0x0A5) /* WOGEN BUF 1 */
#define B2063_WOGEN_BUF2			B43_WP_WADIO(0x0A6) /* WOGEN BUF 2 */
#define B2063_WOGEN_DIV1			B43_WP_WADIO(0x0A7) /* WOGEN DIV 1 */
#define B2063_WOGEN_DIV2			B43_WP_WADIO(0x0A8) /* WOGEN DIV 2 */
#define B2063_WOGEN_DIV3			B43_WP_WADIO(0x0A9) /* WOGEN DIV 3 */
#define B2063_WOGEN_CBUFWX1			B43_WP_WADIO(0x0AA) /* WOGEN CBUFWX 1 */
#define B2063_WOGEN_CBUFWX2			B43_WP_WADIO(0x0AB) /* WOGEN CBUFWX 2 */
#define B2063_WOGEN_CBUFTX1			B43_WP_WADIO(0x0AC) /* WOGEN CBUFTX 1 */
#define B2063_WOGEN_CBUFTX2			B43_WP_WADIO(0x0AD) /* WOGEN CBUFTX 2 */
#define B2063_WOGEN_IDAC1			B43_WP_WADIO(0x0AE) /* WOGEN IDAC 1 */
#define B2063_WOGEN_SPAWE1			B43_WP_WADIO(0x0AF) /* WOGEN SPAWE 1 */
#define B2063_WOGEN_SPAWE2			B43_WP_WADIO(0x0B0) /* WOGEN SPAWE 2 */
#define B2063_WOGEN_SPAWE3			B43_WP_WADIO(0x0B1) /* WOGEN SPAWE 3 */
#define B2063_G_WX_1ST1				B43_WP_WADIO(0x0B2) /* G WX 1ST 1 */
#define B2063_G_WX_1ST2				B43_WP_WADIO(0x0B3) /* G WX 1ST 2 */
#define B2063_G_WX_1ST3				B43_WP_WADIO(0x0B4) /* G WX 1ST 3 */
#define B2063_G_WX_2ND1				B43_WP_WADIO(0x0B5) /* G WX 2ND 1 */
#define B2063_G_WX_2ND2				B43_WP_WADIO(0x0B6) /* G WX 2ND 2 */
#define B2063_G_WX_2ND3				B43_WP_WADIO(0x0B7) /* G WX 2ND 3 */
#define B2063_G_WX_2ND4				B43_WP_WADIO(0x0B8) /* G WX 2ND 4 */
#define B2063_G_WX_2ND5				B43_WP_WADIO(0x0B9) /* G WX 2ND 5 */
#define B2063_G_WX_2ND6				B43_WP_WADIO(0x0BA) /* G WX 2ND 6 */
#define B2063_G_WX_2ND7				B43_WP_WADIO(0x0BB) /* G WX 2ND 7 */
#define B2063_G_WX_2ND8				B43_WP_WADIO(0x0BC) /* G WX 2ND 8 */
#define B2063_G_WX_PS1				B43_WP_WADIO(0x0BD) /* G WX PS 1 */
#define B2063_G_WX_PS2				B43_WP_WADIO(0x0BE) /* G WX PS 2 */
#define B2063_G_WX_PS3				B43_WP_WADIO(0x0BF) /* G WX PS 3 */
#define B2063_G_WX_PS4				B43_WP_WADIO(0x0C0) /* G WX PS 4 */
#define B2063_G_WX_PS5				B43_WP_WADIO(0x0C1) /* G WX PS 5 */
#define B2063_G_WX_MIX1				B43_WP_WADIO(0x0C2) /* G WX MIX 1 */
#define B2063_G_WX_MIX2				B43_WP_WADIO(0x0C3) /* G WX MIX 2 */
#define B2063_G_WX_MIX3				B43_WP_WADIO(0x0C4) /* G WX MIX 3 */
#define B2063_G_WX_MIX4				B43_WP_WADIO(0x0C5) /* G WX MIX 4 */
#define B2063_G_WX_MIX5				B43_WP_WADIO(0x0C6) /* G WX MIX 5 */
#define B2063_G_WX_MIX6				B43_WP_WADIO(0x0C7) /* G WX MIX 6 */
#define B2063_G_WX_MIX7				B43_WP_WADIO(0x0C8) /* G WX MIX 7 */
#define B2063_G_WX_MIX8				B43_WP_WADIO(0x0C9) /* G WX MIX 8 */
#define B2063_G_WX_PDET1			B43_WP_WADIO(0x0CA) /* G WX PDET 1 */
#define B2063_G_WX_SPAWES1			B43_WP_WADIO(0x0CB) /* G WX SPAWES 1 */
#define B2063_G_WX_SPAWES2			B43_WP_WADIO(0x0CC) /* G WX SPAWES 2 */
#define B2063_G_WX_SPAWES3			B43_WP_WADIO(0x0CD) /* G WX SPAWES 3 */
#define B2063_A_WX_1ST1				B43_WP_WADIO(0x0CE) /* A WX 1ST 1 */
#define B2063_A_WX_1ST2				B43_WP_WADIO(0x0CF) /* A WX 1ST 2 */
#define B2063_A_WX_1ST3				B43_WP_WADIO(0x0D0) /* A WX 1ST 3 */
#define B2063_A_WX_1ST4				B43_WP_WADIO(0x0D1) /* A WX 1ST 4 */
#define B2063_A_WX_1ST5				B43_WP_WADIO(0x0D2) /* A WX 1ST 5 */
#define B2063_A_WX_2ND1				B43_WP_WADIO(0x0D3) /* A WX 2ND 1 */
#define B2063_A_WX_2ND2				B43_WP_WADIO(0x0D4) /* A WX 2ND 2 */
#define B2063_A_WX_2ND3				B43_WP_WADIO(0x0D5) /* A WX 2ND 3 */
#define B2063_A_WX_2ND4				B43_WP_WADIO(0x0D6) /* A WX 2ND 4 */
#define B2063_A_WX_2ND5				B43_WP_WADIO(0x0D7) /* A WX 2ND 5 */
#define B2063_A_WX_2ND6				B43_WP_WADIO(0x0D8) /* A WX 2ND 6 */
#define B2063_A_WX_2ND7				B43_WP_WADIO(0x0D9) /* A WX 2ND 7 */
#define B2063_A_WX_PS1				B43_WP_WADIO(0x0DA) /* A WX PS 1 */
#define B2063_A_WX_PS2				B43_WP_WADIO(0x0DB) /* A WX PS 2 */
#define B2063_A_WX_PS3				B43_WP_WADIO(0x0DC) /* A WX PS 3 */
#define B2063_A_WX_PS4				B43_WP_WADIO(0x0DD) /* A WX PS 4 */
#define B2063_A_WX_PS5				B43_WP_WADIO(0x0DE) /* A WX PS 5 */
#define B2063_A_WX_PS6				B43_WP_WADIO(0x0DF) /* A WX PS 6 */
#define B2063_A_WX_MIX1				B43_WP_WADIO(0x0E0) /* A WX MIX 1 */
#define B2063_A_WX_MIX2				B43_WP_WADIO(0x0E1) /* A WX MIX 2 */
#define B2063_A_WX_MIX3				B43_WP_WADIO(0x0E2) /* A WX MIX 3 */
#define B2063_A_WX_MIX4				B43_WP_WADIO(0x0E3) /* A WX MIX 4 */
#define B2063_A_WX_MIX5				B43_WP_WADIO(0x0E4) /* A WX MIX 5 */
#define B2063_A_WX_MIX6				B43_WP_WADIO(0x0E5) /* A WX MIX 6 */
#define B2063_A_WX_MIX7				B43_WP_WADIO(0x0E6) /* A WX MIX 7 */
#define B2063_A_WX_MIX8				B43_WP_WADIO(0x0E7) /* A WX MIX 8 */
#define B2063_A_WX_PWWDET1			B43_WP_WADIO(0x0E8) /* A WX PWWDET 1 */
#define B2063_A_WX_SPAWE1			B43_WP_WADIO(0x0E9) /* A WX SPAWE 1 */
#define B2063_A_WX_SPAWE2			B43_WP_WADIO(0x0EA) /* A WX SPAWE 2 */
#define B2063_A_WX_SPAWE3			B43_WP_WADIO(0x0EB) /* A WX SPAWE 3 */
#define B2063_WX_TIA_CTW1			B43_WP_WADIO(0x0EC) /* WX TIA Contwow 1 */
#define B2063_WX_TIA_CTW2			B43_WP_WADIO(0x0ED) /* WX TIA Contwow 2 */
#define B2063_WX_TIA_CTW3			B43_WP_WADIO(0x0EE) /* WX TIA Contwow 3 */
#define B2063_WX_TIA_CTW4			B43_WP_WADIO(0x0EF) /* WX TIA Contwow 4 */
#define B2063_WX_TIA_CTW5			B43_WP_WADIO(0x0F0) /* WX TIA Contwow 5 */
#define B2063_WX_TIA_CTW6			B43_WP_WADIO(0x0F1) /* WX TIA Contwow 6 */
#define B2063_WX_BB_CTW1			B43_WP_WADIO(0x0F2) /* WX BB Contwow 1 */
#define B2063_WX_BB_CTW2			B43_WP_WADIO(0x0F3) /* WX BB Contwow 2 */
#define B2063_WX_BB_CTW3			B43_WP_WADIO(0x0F4) /* WX BB Contwow 3 */
#define B2063_WX_BB_CTW4			B43_WP_WADIO(0x0F5) /* WX BB Contwow 4 */
#define B2063_WX_BB_CTW5			B43_WP_WADIO(0x0F6) /* WX BB Contwow 5 */
#define B2063_WX_BB_CTW6			B43_WP_WADIO(0x0F7) /* WX BB Contwow 6 */
#define B2063_WX_BB_CTW7			B43_WP_WADIO(0x0F8) /* WX BB Contwow 7 */
#define B2063_WX_BB_CTW8			B43_WP_WADIO(0x0F9) /* WX BB Contwow 8 */
#define B2063_WX_BB_CTW9			B43_WP_WADIO(0x0FA) /* WX BB Contwow 9 */
#define B2063_TX_WF_CTW1			B43_WP_WADIO(0x0FB) /* TX WF Contwow 1 */
#define B2063_TX_WF_IDAC_WO_WF_I		B43_WP_WADIO(0x0FC) /* TX WF IDAC WO WF I */
#define B2063_TX_WF_IDAC_WO_WF_Q		B43_WP_WADIO(0x0FD) /* TX WF IDAC WO WF Q */
#define B2063_TX_WF_IDAC_WO_BB_I		B43_WP_WADIO(0x0FE) /* TX WF IDAC WO BB I */
#define B2063_TX_WF_IDAC_WO_BB_Q		B43_WP_WADIO(0x0FF) /* TX WF IDAC WO BB Q */
#define B2063_TX_WF_CTW2			B43_WP_WADIO(0x100) /* TX WF Contwow 2 */
#define B2063_TX_WF_CTW3			B43_WP_WADIO(0x101) /* TX WF Contwow 3 */
#define B2063_TX_WF_CTW4			B43_WP_WADIO(0x102) /* TX WF Contwow 4 */
#define B2063_TX_WF_CTW5			B43_WP_WADIO(0x103) /* TX WF Contwow 5 */
#define B2063_TX_WF_CTW6			B43_WP_WADIO(0x104) /* TX WF Contwow 6 */
#define B2063_TX_WF_CTW7			B43_WP_WADIO(0x105) /* TX WF Contwow 7 */
#define B2063_TX_WF_CTW8			B43_WP_WADIO(0x106) /* TX WF Contwow 8 */
#define B2063_TX_WF_CTW9			B43_WP_WADIO(0x107) /* TX WF Contwow 9 */
#define B2063_TX_WF_CTW10			B43_WP_WADIO(0x108) /* TX WF Contwow 10 */
#define B2063_TX_WF_CTW14			B43_WP_WADIO(0x109) /* TX WF Contwow 14 */
#define B2063_TX_WF_CTW15			B43_WP_WADIO(0x10A) /* TX WF Contwow 15 */
#define B2063_PA_CTW1				B43_WP_WADIO(0x10B) /* PA Contwow 1 */
#define B2063_PA_CTW2				B43_WP_WADIO(0x10C) /* PA Contwow 2 */
#define B2063_PA_CTW3				B43_WP_WADIO(0x10D) /* PA Contwow 3 */
#define B2063_PA_CTW4				B43_WP_WADIO(0x10E) /* PA Contwow 4 */
#define B2063_PA_CTW5				B43_WP_WADIO(0x10F) /* PA Contwow 5 */
#define B2063_PA_CTW6				B43_WP_WADIO(0x110) /* PA Contwow 6 */
#define B2063_PA_CTW7				B43_WP_WADIO(0x111) /* PA Contwow 7 */
#define B2063_PA_CTW8				B43_WP_WADIO(0x112) /* PA Contwow 8 */
#define B2063_PA_CTW9				B43_WP_WADIO(0x113) /* PA Contwow 9 */
#define B2063_PA_CTW10				B43_WP_WADIO(0x114) /* PA Contwow 10 */
#define B2063_PA_CTW11				B43_WP_WADIO(0x115) /* PA Contwow 11 */
#define B2063_PA_CTW12				B43_WP_WADIO(0x116) /* PA Contwow 12 */
#define B2063_PA_CTW13				B43_WP_WADIO(0x117) /* PA Contwow 13 */
#define B2063_TX_BB_CTW1			B43_WP_WADIO(0x118) /* TX BB Contwow 1 */
#define B2063_TX_BB_CTW2			B43_WP_WADIO(0x119) /* TX BB Contwow 2 */
#define B2063_TX_BB_CTW3			B43_WP_WADIO(0x11A) /* TX BB Contwow 3 */
#define B2063_TX_BB_CTW4			B43_WP_WADIO(0x11B) /* TX BB Contwow 4 */
#define B2063_GPIO_CTW1				B43_WP_WADIO(0x11C) /* GPIO Contwow 1 */
#define B2063_VWEG_CTW1				B43_WP_WADIO(0x11D) /* VWEG Contwow 1 */
#define B2063_AMUX_CTW1				B43_WP_WADIO(0x11E) /* AMUX Contwow 1 */
#define B2063_IQ_CAWIB_GVAW			B43_WP_WADIO(0x11F) /* IQ Cawibwation GVAW */
#define B2063_IQ_CAWIB_CTW1			B43_WP_WADIO(0x120) /* IQ Cawibwation Contwow 1 */
#define B2063_IQ_CAWIB_CTW2			B43_WP_WADIO(0x121) /* IQ Cawibwation Contwow 2 */
#define B2063_TEMPSENSE_CTW1			B43_WP_WADIO(0x122) /* TEMPSENSE Contwow 1 */
#define B2063_TEMPSENSE_CTW2			B43_WP_WADIO(0x123) /* TEMPSENSE Contwow 2 */
#define B2063_TX_WX_WOOPBACK1			B43_WP_WADIO(0x124) /* TX/WX WOOPBACK 1 */
#define B2063_TX_WX_WOOPBACK2			B43_WP_WADIO(0x125) /* TX/WX WOOPBACK 2 */
#define B2063_EXT_TSSI_CTW1			B43_WP_WADIO(0x126) /* EXT TSSI Contwow 1 */
#define B2063_EXT_TSSI_CTW2			B43_WP_WADIO(0x127) /* EXT TSSI Contwow 2 */
#define B2063_AFE_CTW				B43_WP_WADIO(0x128) /* AFE Contwow */



enum b43_wpphy_txpctw_mode {
	B43_WPPHY_TXPCTW_UNKNOWN = 0,
	B43_WPPHY_TXPCTW_OFF,	/* TX powew contwow is OFF */
	B43_WPPHY_TXPCTW_SW,	/* TX powew contwow is set to Softwawe */
	B43_WPPHY_TXPCTW_HW,	/* TX powew contwow is set to Hawdwawe */
};

stwuct b43_phy_wp {
	/* Cuwwent TX powew contwow mode. */
	enum b43_wpphy_txpctw_mode txpctw_mode;

	/* Twansmit isowation medium band */
	u8 tx_isowation_med_band;
	/* Twansmit isowation wow band */
	u8 tx_isowation_wow_band;
	/* Twansmit isowation high band */
	u8 tx_isowation_hi_band;

	/* Max twansmit powew medium band */
	u16 max_tx_pww_med_band;
	/* Max twansmit powew wow band */
	u16 max_tx_pww_wow_band;
	/* Max twansmit powew high band */
	u16 max_tx_pww_hi_band;

	/* FIXME What awe these used fow? */
	/* FIXME Is 15 the cowwect awway size? */
	u16 tx_max_wate[15];
	u16 tx_max_watew[15];
	u16 tx_max_wateh[15];

	/* Twansmit powew awways */
	s16 txpa[3], txpaw[3], txpah[3];

	/* Weceive powew offset */
	u8 wx_pww_offset;

	/* TSSI twansmit count */
	u16 tssi_tx_count;
	/* TSSI index */
	u16 tssi_idx; /* FIXME initiaw vawue? */
	/* TSSI npt */
	u16 tssi_npt; /* FIXME initiaw vawue? */

	/* Tawget TX fwequency */
	u16 tgt_tx_fweq; /* FIXME initiaw vawue? */

	/* Twansmit powew index ovewwide */
	s8 tx_pww_idx_ovew; /* FIXME initiaw vawue? */

	/* WSSI vf */
	u8 wssi_vf;
	/* WSSI vc */
	u8 wssi_vc;
	/* WSSI gs */
	u8 wssi_gs;

	/* WC cap */
	u8 wc_cap;
	/* BX awch */
	u8 bx_awch;

	/* Fuww cawibwation channew */
	u8 fuww_cawib_chan;

	/* Twansmit iqwocaw best coeffs */
	boow tx_iqwoc_best_coeffs_vawid;
	u8 tx_iqwoc_best_coeffs[11];

	/* Used fow "Save/Westowe Dig Fiwt State" */
	u16 dig_fwt_state[9];

	boow cws_usw_disabwe, cws_sys_disabwe;

	unsigned int pdiv;

	/* The channew we awe tuned to */
	u8 channew;

	/* The active antenna divewsity mode */
	int antenna;

	/* Fwequency of the active TX tone */
	int tx_tone_fweq;
};

enum tssi_mux_mode {
	TSSI_MUX_PWEPA,
	TSSI_MUX_POSTPA,
	TSSI_MUX_EXT,
};

stwuct b43_phy_opewations;
extewn const stwuct b43_phy_opewations b43_phyops_wp;

#endif /* WINUX_B43_PHY_WP_H_ */
