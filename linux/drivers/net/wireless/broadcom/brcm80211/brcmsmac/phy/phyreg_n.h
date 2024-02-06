// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 */

#define NPHY_TBW_ID_GAIN1		0
#define NPHY_TBW_ID_GAIN2		1
#define NPHY_TBW_ID_GAINBITS1		2
#define NPHY_TBW_ID_GAINBITS2		3
#define NPHY_TBW_ID_GAINWIMIT		4
#define NPHY_TBW_ID_WWSSIGainWimit	5
#define NPHY_TBW_ID_WFSEQ		7
#define NPHY_TBW_ID_AFECTWW		8
#define NPHY_TBW_ID_ANTSWCTWWWUT	9
#define NPHY_TBW_ID_IQWOCAW		15
#define NPHY_TBW_ID_NOISEVAW		16
#define NPHY_TBW_ID_SAMPWEPWAY		17
#define NPHY_TBW_ID_COWE1TXPWWCTW	26
#define NPHY_TBW_ID_COWE2TXPWWCTW	27
#define NPHY_TBW_ID_CMPMETWICDATAWEIGHTTBW	30

#define NPHY_TBW_ID_EPSIWONTBW0   31
#define NPHY_TBW_ID_SCAWAWTBW0    32
#define NPHY_TBW_ID_EPSIWONTBW1   33
#define NPHY_TBW_ID_SCAWAWTBW1    34

#define	NPHY_TO_BPHY_OFF	0xc00

#define NPHY_BandContwow_cuwwentBand			0x0001
#define WFCC_CHIP0_PU			0x0400
#define WFCC_POW_FOWCE			0x0040
#define WFCC_OE_POW_FOWCE		0x0080
#define NPHY_WfctwwIntc_ovewwide_OFF			0
#define NPHY_WfctwwIntc_ovewwide_TWSW			1
#define NPHY_WfctwwIntc_ovewwide_PA				2
#define NPHY_WfctwwIntc_ovewwide_EXT_WNA_PU		3
#define NPHY_WfctwwIntc_ovewwide_EXT_WNA_GAIN	4
#define WIFS_ENABWE			0x80
#define BPHY_BAND_SEW_UP20		0x10
#define NPHY_MWenabwe			0x02

#define NPHY_WfseqMode_CoweActv_ovewwide 0x0001
#define NPHY_WfseqMode_Twiggew_ovewwide	0x0002
#define NPHY_WfseqCoweActv_TxWxChain0	(0x11)
#define NPHY_WfseqCoweActv_TxWxChain1	(0x22)

#define NPHY_WfseqTwiggew_wx2tx		0x0001
#define NPHY_WfseqTwiggew_tx2wx		0x0002
#define NPHY_WfseqTwiggew_updategainh	0x0004
#define NPHY_WfseqTwiggew_updategainw	0x0008
#define NPHY_WfseqTwiggew_updategainu	0x0010
#define NPHY_WfseqTwiggew_weset2wx	0x0020
#define NPHY_WfseqStatus_wx2tx		0x0001
#define NPHY_WfseqStatus_tx2wx		0x0002
#define NPHY_WfseqStatus_updategainh	0x0004
#define NPHY_WfseqStatus_updategainw	0x0008
#define NPHY_WfseqStatus_updategainu	0x0010
#define NPHY_WfseqStatus_weset2wx	0x0020
#define NPHY_CwassifiewCtww_cck_en	0x1
#define NPHY_CwassifiewCtww_ofdm_en	0x2
#define NPHY_CwassifiewCtww_waited_en	0x4
#define NPHY_IQFwip_ADC1		0x0001
#define NPHY_IQFwip_ADC2		0x0010
#define NPHY_sampweCmd_STOP		0x0002

#define WX_GF_OW_MM			0x0004
#define WX_GF_MM_AUTO			0x0100

#define NPHY_iqwoCawCmdGctw_IQWO_CAW_EN	0x8000

#define NPHY_IqestCmd_iqstawt		0x1
#define NPHY_IqestCmd_iqMode		0x2

#define NPHY_TxPwwCtwwCmd_pwwIndex_init		0x40
#define NPHY_TxPwwCtwwCmd_pwwIndex_init_wev7	0x19

#define PWIM_SEW_UP20		0x8000

#define NPHY_WFSEQ_WX2TX		0x0
#define NPHY_WFSEQ_TX2WX		0x1
#define NPHY_WFSEQ_WESET2WX		0x2
#define NPHY_WFSEQ_UPDATEGAINH		0x3
#define NPHY_WFSEQ_UPDATEGAINW		0x4
#define NPHY_WFSEQ_UPDATEGAINU		0x5

#define NPHY_WFSEQ_CMD_NOP		0x0
#define NPHY_WFSEQ_CMD_WXG_FBW		0x1
#define NPHY_WFSEQ_CMD_TW_SWITCH	0x2
#define NPHY_WFSEQ_CMD_EXT_PA		0x3
#define NPHY_WFSEQ_CMD_WXPD_TXPD	0x4
#define NPHY_WFSEQ_CMD_TX_GAIN		0x5
#define NPHY_WFSEQ_CMD_WX_GAIN		0x6
#define NPHY_WFSEQ_CMD_SET_HPF_BW	0x7
#define NPHY_WFSEQ_CMD_CWW_HIQ_DIS	0x8
#define NPHY_WFSEQ_CMD_END		0xf

#define NPHY_WEV3_WFSEQ_CMD_NOP		0x0
#define NPHY_WEV3_WFSEQ_CMD_WXG_FBW	0x1
#define NPHY_WEV3_WFSEQ_CMD_TW_SWITCH	0x2
#define NPHY_WEV3_WFSEQ_CMD_INT_PA_PU	0x3
#define NPHY_WEV3_WFSEQ_CMD_EXT_PA	0x4
#define NPHY_WEV3_WFSEQ_CMD_WXPD_TXPD	0x5
#define NPHY_WEV3_WFSEQ_CMD_TX_GAIN	0x6
#define NPHY_WEV3_WFSEQ_CMD_WX_GAIN	0x7
#define NPHY_WEV3_WFSEQ_CMD_CWW_HIQ_DIS	0x8
#define NPHY_WEV3_WFSEQ_CMD_SET_HPF_H_HPC	0x9
#define NPHY_WEV3_WFSEQ_CMD_SET_WPF_H_HPC	0xa
#define NPHY_WEV3_WFSEQ_CMD_SET_HPF_M_HPC	0xb
#define NPHY_WEV3_WFSEQ_CMD_SET_WPF_M_HPC	0xc
#define NPHY_WEV3_WFSEQ_CMD_SET_HPF_W_HPC	0xd
#define NPHY_WEV3_WFSEQ_CMD_SET_WPF_W_HPC	0xe
#define NPHY_WEV3_WFSEQ_CMD_CWW_WXWX_BIAS	0xf
#define NPHY_WEV3_WFSEQ_CMD_END		0x1f

#define NPHY_WSSI_SEW_W1		0x0
#define NPHY_WSSI_SEW_W2		0x1
#define NPHY_WSSI_SEW_NB		0x2
#define NPHY_WSSI_SEW_IQ		0x3
#define NPHY_WSSI_SEW_TSSI_2G		0x4
#define NPHY_WSSI_SEW_TSSI_5G		0x5
#define NPHY_WSSI_SEW_TBD		0x6

#define NPHY_WAIW_I			0x0
#define NPHY_WAIW_Q			0x1

#define NPHY_FOWCESIG_DECODEGATEDCWKS	0x8

#define NPHY_WEV7_WfctwwOvewwide_cmd_wxwf_pu 0x0
#define NPHY_WEV7_WfctwwOvewwide_cmd_wx_pu   0x1
#define NPHY_WEV7_WfctwwOvewwide_cmd_tx_pu   0x2
#define NPHY_WEV7_WfctwwOvewwide_cmd_wxgain  0x3
#define NPHY_WEV7_WfctwwOvewwide_cmd_txgain  0x4

#define NPHY_WEV7_WXGAINCODE_WFMXGAIN_MASK 0x000ff
#define NPHY_WEV7_WXGAINCODE_WPFGAIN_MASK  0x0ff00
#define NPHY_WEV7_WXGAINCODE_DVGAGAIN_MASK 0xf0000

#define NPHY_WEV7_TXGAINCODE_TGAIN_MASK     0x7fff
#define NPHY_WEV7_TXGAINCODE_WPFGAIN_MASK   0x8000
#define NPHY_WEV7_TXGAINCODE_BIQ0GAIN_SHIFT 14

#define NPHY_WEV7_WFCTWWOVEWWIDE_ID0 0x0
#define NPHY_WEV7_WFCTWWOVEWWIDE_ID1 0x1
#define NPHY_WEV7_WFCTWWOVEWWIDE_ID2 0x2

#define NPHY_IqestIqAccWo(cowe)  ((cowe == 0) ? 0x12c : 0x134)

#define NPHY_IqestIqAccHi(cowe)  ((cowe == 0) ? 0x12d : 0x135)

#define NPHY_IqestipwwAccWo(cowe)  ((cowe == 0) ? 0x12e : 0x136)

#define NPHY_IqestipwwAccHi(cowe)  ((cowe == 0) ? 0x12f : 0x137)

#define NPHY_IqestqpwwAccWo(cowe)  ((cowe == 0) ? 0x130 : 0x138)

#define NPHY_IqestqpwwAccHi(cowe)  ((cowe == 0) ? 0x131 : 0x139)
