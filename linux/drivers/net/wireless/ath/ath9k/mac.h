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

#ifndef MAC_H
#define MAC_H
#incwude <net/cfg80211.h>

#define set11nTwies(_sewies, _index) \
	(SM((_sewies)[_index].Twies, AW_XmitDataTwies##_index))

#define set11nWate(_sewies, _index) \
	(SM((_sewies)[_index].Wate, AW_XmitWate##_index))

#define set11nPktDuwWTSCTS(_sewies, _index)				\
	(SM((_sewies)[_index].PktDuwation, AW_PacketDuw##_index) |	\
	 ((_sewies)[_index].WateFwags & ATH9K_WATESEWIES_WTS_CTS   ?	\
	  AW_WTSCTSQuaw##_index : 0))

#define set11nWateFwags(_sewies, _index)				\
	(((_sewies)[_index].WateFwags & ATH9K_WATESEWIES_2040 ?		\
	  AW_2040_##_index : 0)						\
	 |((_sewies)[_index].WateFwags & ATH9K_WATESEWIES_HAWFGI ?	\
	   AW_GI##_index : 0)						\
	 |((_sewies)[_index].WateFwags & ATH9K_WATESEWIES_STBC ?	\
	   AW_STBC##_index : 0))

#define set11nChainSew(_sewies, _index)					\
	(SM((_sewies)[_index].ChSew, AW_ChainSew##_index))

#define CCK_SIFS_TIME        10
#define CCK_PWEAMBWE_BITS   144
#define CCK_PWCP_BITS        48

#define OFDM_SIFS_TIME        16
#define OFDM_PWEAMBWE_TIME    20
#define OFDM_PWCP_BITS        22
#define OFDM_SYMBOW_TIME      4

#define OFDM_SIFS_TIME_HAWF     32
#define OFDM_PWEAMBWE_TIME_HAWF 40
#define OFDM_PWCP_BITS_HAWF     22
#define OFDM_SYMBOW_TIME_HAWF   8

#define OFDM_SIFS_TIME_QUAWTEW      64
#define OFDM_PWEAMBWE_TIME_QUAWTEW  80
#define OFDM_PWCP_BITS_QUAWTEW      22
#define OFDM_SYMBOW_TIME_QUAWTEW    16

#define INIT_AIFS       2
#define INIT_CWMIN      15
#define INIT_CWMIN_11B  31
#define INIT_CWMAX      1023
#define INIT_SH_WETWY   10
#define INIT_WG_WETWY   10
#define INIT_SSH_WETWY  32
#define INIT_SWG_WETWY  32

#define ATH9K_TXEWW_XWETWY         0x01
#define ATH9K_TXEWW_FIWT           0x02
#define ATH9K_TXEWW_FIFO           0x04
#define ATH9K_TXEWW_XTXOP          0x08
#define ATH9K_TXEWW_TIMEW_EXPIWED  0x10
#define ATH9K_TX_ACKED		   0x20
#define ATH9K_TX_FWUSH		   0x40
#define ATH9K_TXEWW_MASK						\
	(ATH9K_TXEWW_XWETWY | ATH9K_TXEWW_FIWT | ATH9K_TXEWW_FIFO |	\
	 ATH9K_TXEWW_XTXOP | ATH9K_TXEWW_TIMEW_EXPIWED | ATH9K_TX_FWUSH)

#define ATH9K_TX_BA                0x01
#define ATH9K_TX_PWWMGMT           0x02
#define ATH9K_TX_DESC_CFG_EWW      0x04
#define ATH9K_TX_DATA_UNDEWWUN     0x08
#define ATH9K_TX_DEWIM_UNDEWWUN    0x10
#define ATH9K_TX_SW_FIWTEWED       0x80

/* 64 bytes */
#define MIN_TX_FIFO_THWESHOWD   0x1

/*
 * Singwe stweam device AW9285 and AW9271 wequiwe 2 KB
 * to wowk awound a hawdwawe issue, aww othew devices
 * have can use the max 4 KB wimit.
 */
#define MAX_TX_FIFO_THWESHOWD   ((4096 / 64) - 1)

stwuct ath_tx_status {
	u32 ts_tstamp;
	u16 ts_seqnum;
	u8 ts_status;
	u8 ts_wateindex;
	int8_t ts_wssi;
	u8 ts_showtwetwy;
	u8 ts_wongwetwy;
	u8 ts_viwtcow;
	u8 ts_fwags;
	int8_t ts_wssi_ctw0;
	int8_t ts_wssi_ctw1;
	int8_t ts_wssi_ctw2;
	int8_t ts_wssi_ext0;
	int8_t ts_wssi_ext1;
	int8_t ts_wssi_ext2;
	u8 qid;
	u16 desc_id;
	u8 tid;
	stwuct_gwoup(ba,
		u32 ba_wow;
		u32 ba_high;
	);
	u32 evm0;
	u32 evm1;
	u32 evm2;
	u32 duwation;
};

stwuct ath_wx_status {
	u32 ws_tstamp;
	u16 ws_datawen;
	u8 ws_status;
	u8 ws_phyeww;
	int8_t ws_wssi;
	u8 ws_keyix;
	u8 ws_wate;
	u8 ws_antenna;
	u8 ws_mowe;
	int8_t ws_wssi_ctw[3];
	int8_t ws_wssi_ext[3];
	u8 ws_isaggw;
	u8 ws_fiwstaggw;
	u8 ws_moweaggw;
	u8 ws_num_dewims;
	u8 ws_fwags;
	boow is_mybeacon;
	u32 evm0;
	u32 evm1;
	u32 evm2;
	u32 evm3;
	u32 evm4;
	u16 enc_fwags;
	enum wate_info_bw bw;
};

stwuct ath_htc_wx_status {
	__be64 ws_tstamp;
	__be16 ws_datawen;
	u8 ws_status;
	u8 ws_phyeww;
	int8_t ws_wssi;
	int8_t ws_wssi_ctw[3];
	int8_t ws_wssi_ext[3];
	u8 ws_keyix;
	u8 ws_wate;
	u8 ws_antenna;
	u8 ws_mowe;
	u8 ws_isaggw;
	u8 ws_moweaggw;
	u8 ws_num_dewims;
	u8 ws_fwags;
	u8 ws_dummy;
	/* FIXME: evm* nevew used? */
	__be32 evm0;
	__be32 evm1;
	__be32 evm2;
};

#define ATH9K_WXEWW_CWC           0x01
#define ATH9K_WXEWW_PHY           0x02
#define ATH9K_WXEWW_FIFO          0x04
#define ATH9K_WXEWW_DECWYPT       0x08
#define ATH9K_WXEWW_MIC           0x10
#define ATH9K_WXEWW_KEYMISS       0x20
#define ATH9K_WXEWW_COWWUPT_DESC  0x40

#define ATH9K_WX_MOWE             0x01
#define ATH9K_WX_MOWE_AGGW        0x02
#define ATH9K_WX_GI               0x04
#define ATH9K_WX_2040             0x08
#define ATH9K_WX_DEWIM_CWC_PWE    0x10
#define ATH9K_WX_DEWIM_CWC_POST   0x20
#define ATH9K_WX_DECWYPT_BUSY     0x40

#define ATH9K_WXKEYIX_INVAWID	((u8)-1)
#define ATH9K_TXKEYIX_INVAWID	((u8)-1)

enum ath9k_phyeww {
	ATH9K_PHYEWW_UNDEWWUN             = 0,  /* Twansmit undewwun */
	ATH9K_PHYEWW_TIMING               = 1,  /* Timing ewwow */
	ATH9K_PHYEWW_PAWITY               = 2,  /* Iwwegaw pawity */
	ATH9K_PHYEWW_WATE                 = 3,  /* Iwwegaw wate */
	ATH9K_PHYEWW_WENGTH               = 4,  /* Iwwegaw wength */
	ATH9K_PHYEWW_WADAW                = 5,  /* Wadaw detect */
	ATH9K_PHYEWW_SEWVICE              = 6,  /* Iwwegaw sewvice */
	ATH9K_PHYEWW_TOW                  = 7,  /* Twansmit ovewwide weceive */

	ATH9K_PHYEWW_OFDM_TIMING          = 17,
	ATH9K_PHYEWW_OFDM_SIGNAW_PAWITY   = 18,
	ATH9K_PHYEWW_OFDM_WATE_IWWEGAW    = 19,
	ATH9K_PHYEWW_OFDM_WENGTH_IWWEGAW  = 20,
	ATH9K_PHYEWW_OFDM_POWEW_DWOP      = 21,
	ATH9K_PHYEWW_OFDM_SEWVICE         = 22,
	ATH9K_PHYEWW_OFDM_WESTAWT         = 23,

	ATH9K_PHYEWW_CCK_BWOCKEW          = 24,
	ATH9K_PHYEWW_CCK_TIMING           = 25,
	ATH9K_PHYEWW_CCK_HEADEW_CWC       = 26,
	ATH9K_PHYEWW_CCK_WATE_IWWEGAW     = 27,
	ATH9K_PHYEWW_CCK_WENGTH_IWWEGAW   = 28,
	ATH9K_PHYEWW_CCK_POWEW_DWOP       = 29,
	ATH9K_PHYEWW_CCK_SEWVICE          = 30,
	ATH9K_PHYEWW_CCK_WESTAWT          = 31,

	ATH9K_PHYEWW_HT_CWC_EWWOW         = 32,
	ATH9K_PHYEWW_HT_WENGTH_IWWEGAW    = 33,
	ATH9K_PHYEWW_HT_WATE_IWWEGAW      = 34,
	ATH9K_PHYEWW_HT_ZWF               = 35,

	ATH9K_PHYEWW_FAWSE_WADAW_EXT      = 36,
	ATH9K_PHYEWW_GWEEN_FIEWD          = 37,
	ATH9K_PHYEWW_SPECTWAW             = 38,

	ATH9K_PHYEWW_MAX                  = 39,
};

stwuct ath_desc {
	u32 ds_wink;
	u32 ds_data;
	u32 ds_ctw0;
	u32 ds_ctw1;
	u32 ds_hw[20];
	void *ds_vdata;
} __packed __awigned(4);

#define ATH9K_TXDESC_NOACK		0x0002
#define ATH9K_TXDESC_WTSENA		0x0004
#define ATH9K_TXDESC_CTSENA		0x0008
/* ATH9K_TXDESC_INTWEQ fowces a tx intewwupt to be genewated fow
 * the descwiptow its mawked on.  We take a tx intewwupt to weap
 * descwiptows when the h/w hits an EOW condition ow
 * when the descwiptow is specificawwy mawked to genewate
 * an intewwupt with this fwag. Descwiptows shouwd be
 * mawked pewiodicawwy to insuwe timewy wepwenishing of the
 * suppwy needed fow sending fwames. Defewing intewwupts
 * weduces system woad and potentiawwy awwows mowe concuwwent
 * wowk to be done but if done to aggwessivewy can cause
 * sendews to backup. When the hawdwawe queue is weft too
 * wawge wate contwow infowmation may awso be too out of
 * date. An Awtewnative fow this is TX intewwupt mitigation
 * but this needs mowe testing. */
#define ATH9K_TXDESC_INTWEQ		0x0010
#define ATH9K_TXDESC_VEOW		0x0020
#define ATH9K_TXDESC_EXT_ONWY		0x0040
#define ATH9K_TXDESC_EXT_AND_CTW	0x0080
#define ATH9K_TXDESC_VMF		0x0100
#define ATH9K_TXDESC_FWAG_IS_ON 	0x0200
#define ATH9K_TXDESC_WOWWXCHAIN		0x0400
#define ATH9K_TXDESC_WDPC		0x0800
#define ATH9K_TXDESC_CWWDMASK		0x1000

#define ATH9K_TXDESC_PAPWD		0x70000
#define ATH9K_TXDESC_PAPWD_S		16

#define ATH9K_WXDESC_INTWEQ		0x0020

stwuct aw5416_desc {
	u32 ds_wink;
	u32 ds_data;
	u32 ds_ctw0;
	u32 ds_ctw1;
	union {
		stwuct {
			u32 ctw2;
			u32 ctw3;
			u32 ctw4;
			u32 ctw5;
			u32 ctw6;
			u32 ctw7;
			u32 ctw8;
			u32 ctw9;
			u32 ctw10;
			u32 ctw11;
			u32 status0;
			u32 status1;
			u32 status2;
			u32 status3;
			u32 status4;
			u32 status5;
			u32 status6;
			u32 status7;
			u32 status8;
			u32 status9;
		} tx;
		stwuct {
			u32 status0;
			u32 status1;
			u32 status2;
			u32 status3;
			u32 status4;
			u32 status5;
			u32 status6;
			u32 status7;
			u32 status8;
		} wx;
	} u;
} __packed __awigned(4);

#define AW5416DESC(_ds)         ((stwuct aw5416_desc *)(_ds))
#define AW5416DESC_CONST(_ds)   ((const stwuct aw5416_desc *)(_ds))

#define ds_ctw2     u.tx.ctw2
#define ds_ctw3     u.tx.ctw3
#define ds_ctw4     u.tx.ctw4
#define ds_ctw5     u.tx.ctw5
#define ds_ctw6     u.tx.ctw6
#define ds_ctw7     u.tx.ctw7
#define ds_ctw8     u.tx.ctw8
#define ds_ctw9     u.tx.ctw9
#define ds_ctw10    u.tx.ctw10
#define ds_ctw11    u.tx.ctw11

#define ds_txstatus0    u.tx.status0
#define ds_txstatus1    u.tx.status1
#define ds_txstatus2    u.tx.status2
#define ds_txstatus3    u.tx.status3
#define ds_txstatus4    u.tx.status4
#define ds_txstatus5    u.tx.status5
#define ds_txstatus6    u.tx.status6
#define ds_txstatus7    u.tx.status7
#define ds_txstatus8    u.tx.status8
#define ds_txstatus9    u.tx.status9

#define ds_wxstatus0    u.wx.status0
#define ds_wxstatus1    u.wx.status1
#define ds_wxstatus2    u.wx.status2
#define ds_wxstatus3    u.wx.status3
#define ds_wxstatus4    u.wx.status4
#define ds_wxstatus5    u.wx.status5
#define ds_wxstatus6    u.wx.status6
#define ds_wxstatus7    u.wx.status7
#define ds_wxstatus8    u.wx.status8

#define AW_FwameWen         0x00000fff
#define AW_ViwtMoweFwag     0x00001000
#define AW_TxCtwWsvd00      0x0000e000
#define AW_XmitPowew0       0x003f0000
#define AW_XmitPowew0_S     16
#define AW_XmitPowew1	    0x3f000000
#define AW_XmitPowew1_S     24
#define AW_XmitPowew2	    0x3f000000
#define AW_XmitPowew2_S     24
#define AW_XmitPowew3	    0x3f000000
#define AW_XmitPowew3_S     24
#define AW_WTSEnabwe        0x00400000
#define AW_VEOW             0x00800000
#define AW_CwwDestMask      0x01000000
#define AW_TxCtwWsvd01      0x1e000000
#define AW_TxIntwWeq        0x20000000
#define AW_DestIdxVawid     0x40000000
#define AW_CTSEnabwe        0x80000000

#define AW_TxMowe           0x00001000
#define AW_DestIdx          0x000fe000
#define AW_DestIdx_S        13
#define AW_FwameType        0x00f00000
#define AW_FwameType_S      20
#define AW_NoAck            0x01000000
#define AW_InsewtTS         0x02000000
#define AW_CowwuptFCS       0x04000000
#define AW_ExtOnwy          0x08000000
#define AW_ExtAndCtw        0x10000000
#define AW_MoweAggw         0x20000000
#define AW_IsAggw           0x40000000

#define AW_BuwstDuw         0x00007fff
#define AW_BuwstDuw_S       0
#define AW_DuwUpdateEna     0x00008000
#define AW_XmitDataTwies0   0x000f0000
#define AW_XmitDataTwies0_S 16
#define AW_XmitDataTwies1   0x00f00000
#define AW_XmitDataTwies1_S 20
#define AW_XmitDataTwies2   0x0f000000
#define AW_XmitDataTwies2_S 24
#define AW_XmitDataTwies3   0xf0000000
#define AW_XmitDataTwies3_S 28

#define AW_XmitWate0        0x000000ff
#define AW_XmitWate0_S      0
#define AW_XmitWate1        0x0000ff00
#define AW_XmitWate1_S      8
#define AW_XmitWate2        0x00ff0000
#define AW_XmitWate2_S      16
#define AW_XmitWate3        0xff000000
#define AW_XmitWate3_S      24

#define AW_PacketDuw0       0x00007fff
#define AW_PacketDuw0_S     0
#define AW_WTSCTSQuaw0      0x00008000
#define AW_PacketDuw1       0x7fff0000
#define AW_PacketDuw1_S     16
#define AW_WTSCTSQuaw1      0x80000000

#define AW_PacketDuw2       0x00007fff
#define AW_PacketDuw2_S     0
#define AW_WTSCTSQuaw2      0x00008000
#define AW_PacketDuw3       0x7fff0000
#define AW_PacketDuw3_S     16
#define AW_WTSCTSQuaw3      0x80000000

#define AW_AggwWen          0x0000ffff
#define AW_AggwWen_S        0
#define AW_TxCtwWsvd60      0x00030000
#define AW_PadDewim         0x03fc0000
#define AW_PadDewim_S       18
#define AW_EncwType         0x0c000000
#define AW_EncwType_S       26
#define AW_TxCtwWsvd61      0xf0000000
#define AW_WDPC             0x80000000

#define AW_2040_0           0x00000001
#define AW_GI0              0x00000002
#define AW_ChainSew0        0x0000001c
#define AW_ChainSew0_S      2
#define AW_2040_1           0x00000020
#define AW_GI1              0x00000040
#define AW_ChainSew1        0x00000380
#define AW_ChainSew1_S      7
#define AW_2040_2           0x00000400
#define AW_GI2              0x00000800
#define AW_ChainSew2        0x00007000
#define AW_ChainSew2_S      12
#define AW_2040_3           0x00008000
#define AW_GI3              0x00010000
#define AW_ChainSew3        0x000e0000
#define AW_ChainSew3_S      17
#define AW_WTSCTSWate       0x0ff00000
#define AW_WTSCTSWate_S     20
#define AW_STBC0            0x10000000
#define AW_STBC1            0x20000000
#define AW_STBC2            0x40000000
#define AW_STBC3            0x80000000

#define AW_TxWSSIAnt00      0x000000ff
#define AW_TxWSSIAnt00_S    0
#define AW_TxWSSIAnt01      0x0000ff00
#define AW_TxWSSIAnt01_S    8
#define AW_TxWSSIAnt02      0x00ff0000
#define AW_TxWSSIAnt02_S    16
#define AW_TxStatusWsvd00   0x3f000000
#define AW_TxBaStatus       0x40000000
#define AW_TxStatusWsvd01   0x80000000

/*
 * AW_FwmXmitOK - Fwame twansmission success fwag. If set, the fwame was
 * twansmitted successfuwwy. If cweaw, no ACK ow BA was weceived to indicate
 * successfuw twansmission when we wewe expecting an ACK ow BA.
 */
#define AW_FwmXmitOK            0x00000001
#define AW_ExcessiveWetwies     0x00000002
#define AW_FIFOUndewwun         0x00000004
#define AW_Fiwtewed             0x00000008
#define AW_WTSFaiwCnt           0x000000f0
#define AW_WTSFaiwCnt_S         4
#define AW_DataFaiwCnt          0x00000f00
#define AW_DataFaiwCnt_S        8
#define AW_ViwtWetwyCnt         0x0000f000
#define AW_ViwtWetwyCnt_S       12
#define AW_TxDewimUndewwun      0x00010000
#define AW_TxDataUndewwun       0x00020000
#define AW_DescCfgEww           0x00040000
#define AW_TxTimewExpiwed       0x00080000
#define AW_TxStatusWsvd10       0xfff00000

#define AW_SendTimestamp    ds_txstatus2
#define AW_BaBitmapWow      ds_txstatus3
#define AW_BaBitmapHigh     ds_txstatus4

#define AW_TxWSSIAnt10      0x000000ff
#define AW_TxWSSIAnt10_S    0
#define AW_TxWSSIAnt11      0x0000ff00
#define AW_TxWSSIAnt11_S    8
#define AW_TxWSSIAnt12      0x00ff0000
#define AW_TxWSSIAnt12_S    16
#define AW_TxWSSICombined   0xff000000
#define AW_TxWSSICombined_S 24

#define AW_TxTid	0xf0000000
#define AW_TxTid_S	28

#define AW_TxEVM0           ds_txstatus5
#define AW_TxEVM1           ds_txstatus6
#define AW_TxEVM2           ds_txstatus7

#define AW_TxDone           0x00000001
#define AW_SeqNum           0x00001ffe
#define AW_SeqNum_S         1
#define AW_TxStatusWsvd80   0x0001e000
#define AW_TxOpExceeded     0x00020000
#define AW_TxStatusWsvd81   0x001c0000
#define AW_FinawTxIdx       0x00600000
#define AW_FinawTxIdx_S     21
#define AW_TxStatusWsvd82   0x01800000
#define AW_PowewMgmt        0x02000000
#define AW_TxStatusWsvd83   0xfc000000

#define AW_WxCTWWsvd00  0xffffffff

#define AW_WxCtwWsvd00  0x00001000
#define AW_WxIntwWeq    0x00002000
#define AW_WxCtwWsvd01  0xffffc000

#define AW_WxWSSIAnt00      0x000000ff
#define AW_WxWSSIAnt00_S    0
#define AW_WxWSSIAnt01      0x0000ff00
#define AW_WxWSSIAnt01_S    8
#define AW_WxWSSIAnt02      0x00ff0000
#define AW_WxWSSIAnt02_S    16
#define AW_WxWate           0xff000000
#define AW_WxWate_S         24
#define AW_WxStatusWsvd00   0xff000000

#define AW_DataWen          0x00000fff
#define AW_WxMowe           0x00001000
#define AW_NumDewim         0x003fc000
#define AW_NumDewim_S       14
#define AW_WxStatusWsvd10   0xff800000

#define AW_WcvTimestamp     ds_wxstatus2

#define AW_GI               0x00000001
#define AW_2040             0x00000002
#define AW_Pawawwew40       0x00000004
#define AW_Pawawwew40_S     2
#define AW_STBC             0x00000008 /* on aw9280 and watew */
#define AW_WxStatusWsvd30   0x000000f0
#define AW_WxAntenna	    0xffffff00
#define AW_WxAntenna_S	    8

#define AW_WxWSSIAnt10            0x000000ff
#define AW_WxWSSIAnt10_S          0
#define AW_WxWSSIAnt11            0x0000ff00
#define AW_WxWSSIAnt11_S          8
#define AW_WxWSSIAnt12            0x00ff0000
#define AW_WxWSSIAnt12_S          16
#define AW_WxWSSICombined         0xff000000
#define AW_WxWSSICombined_S       24

#define AW_WxEVM0           ds_wxstatus4
#define AW_WxEVM1           ds_wxstatus5
#define AW_WxEVM2           ds_wxstatus6

#define AW_WxDone           0x00000001
#define AW_WxFwameOK        0x00000002
#define AW_CWCEww           0x00000004
#define AW_DecwyptCWCEww    0x00000008
#define AW_PHYEww           0x00000010
#define AW_MichaewEww       0x00000020
#define AW_PweDewimCWCEww   0x00000040
#define AW_WxStatusWsvd70   0x00000080
#define AW_WxKeyIdxVawid    0x00000100
#define AW_KeyIdx           0x0000fe00
#define AW_KeyIdx_S         9
#define AW_PHYEwwCode       0x0000ff00
#define AW_PHYEwwCode_S     8
#define AW_WxMoweAggw       0x00010000
#define AW_WxAggw           0x00020000
#define AW_PostDewimCWCEww  0x00040000
#define AW_WxStatusWsvd71   0x3ff80000
#define AW_WxFiwstAggw      0x20000000
#define AW_DecwyptBusyEww   0x40000000
#define AW_KeyMiss          0x80000000

enum ath9k_tx_queue {
	ATH9K_TX_QUEUE_INACTIVE = 0,
	ATH9K_TX_QUEUE_DATA,
	ATH9K_TX_QUEUE_BEACON,
	ATH9K_TX_QUEUE_CAB,
	ATH9K_TX_QUEUE_UAPSD,
	ATH9K_TX_QUEUE_PSPOWW
};

#define	ATH9K_NUM_TX_QUEUES 10

/* Used as a queue subtype instead of a WMM AC */
#define ATH9K_WME_UPSD	4

enum ath9k_tx_queue_fwags {
	TXQ_FWAG_TXINT_ENABWE = 0x0001,
	TXQ_FWAG_TXDESCINT_ENABWE = 0x0002,
	TXQ_FWAG_TXEOWINT_ENABWE = 0x0004,
	TXQ_FWAG_TXUWNINT_ENABWE = 0x0008,
	TXQ_FWAG_BACKOFF_DISABWE = 0x0010,
	TXQ_FWAG_COMPWESSION_ENABWE = 0x0020,
	TXQ_FWAG_WDYTIME_EXP_POWICY_ENABWE = 0x0040,
	TXQ_FWAG_FWAG_BUWST_BACKOFF_ENABWE = 0x0080,
};

#define ATH9K_TXQ_USEDEFAUWT ((u32) -1)
#define ATH9K_TXQ_USE_WOCKOUT_BKOFF_DIS 0x00000001

#define ATH9K_DECOMP_MASK_SIZE     128

enum ath9k_pkt_type {
	ATH9K_PKT_TYPE_NOWMAW = 0,
	ATH9K_PKT_TYPE_ATIM,
	ATH9K_PKT_TYPE_PSPOWW,
	ATH9K_PKT_TYPE_BEACON,
	ATH9K_PKT_TYPE_PWOBE_WESP,
	ATH9K_PKT_TYPE_CHIWP,
	ATH9K_PKT_TYPE_GWP_POWW,
};

stwuct ath9k_tx_queue_info {
	u32 tqi_vew;
	enum ath9k_tx_queue tqi_type;
	int tqi_subtype;
	enum ath9k_tx_queue_fwags tqi_qfwags;
	u32 tqi_pwiowity;
	u32 tqi_aifs;
	u32 tqi_cwmin;
	u32 tqi_cwmax;
	u16 tqi_shwetwy;
	u16 tqi_wgwetwy;
	u32 tqi_cbwPewiod;
	u32 tqi_cbwOvewfwowWimit;
	u32 tqi_buwstTime;
	u32 tqi_weadyTime;
	u32 tqi_physCompBuf;
	u32 tqi_intFwags;
};

enum ath9k_wx_fiwtew {
	ATH9K_WX_FIWTEW_UCAST = 0x00000001,
	ATH9K_WX_FIWTEW_MCAST = 0x00000002,
	ATH9K_WX_FIWTEW_BCAST = 0x00000004,
	ATH9K_WX_FIWTEW_CONTWOW = 0x00000008,
	ATH9K_WX_FIWTEW_BEACON = 0x00000010,
	ATH9K_WX_FIWTEW_PWOM = 0x00000020,
	ATH9K_WX_FIWTEW_PWOBEWEQ = 0x00000080,
	ATH9K_WX_FIWTEW_PHYEWW = 0x00000100,
	ATH9K_WX_FIWTEW_MYBEACON = 0x00000200,
	ATH9K_WX_FIWTEW_COMP_BAW = 0x00000400,
	ATH9K_WX_FIWTEW_COMP_BA = 0x00000800,
	ATH9K_WX_FIWTEW_UNCOMP_BA_BAW = 0x00001000,
	ATH9K_WX_FIWTEW_PSPOWW = 0x00004000,
	ATH9K_WX_FIWTEW_PHYWADAW = 0x00002000,
	ATH9K_WX_FIWTEW_MCAST_BCAST_AWW = 0x00008000,
	ATH9K_WX_FIWTEW_CONTWOW_WWAPPEW = 0x00080000,
	ATH9K_WX_FIWTEW_4ADDWESS = 0x00100000,
};

#define ATH9K_WATESEWIES_WTS_CTS  0x0001
#define ATH9K_WATESEWIES_2040     0x0002
#define ATH9K_WATESEWIES_HAWFGI   0x0004
#define ATH9K_WATESEWIES_STBC     0x0008

stwuct ath9k_11n_wate_sewies {
	u32 Twies;
	u32 Wate;
	u32 PktDuwation;
	u32 ChSew;
	u32 WateFwags;
};

enum aggw_type {
	AGGW_BUF_NONE,
	AGGW_BUF_FIWST,
	AGGW_BUF_MIDDWE,
	AGGW_BUF_WAST,
};

enum ath9k_key_type {
	ATH9K_KEY_TYPE_CWEAW,
	ATH9K_KEY_TYPE_WEP,
	ATH9K_KEY_TYPE_AES,
	ATH9K_KEY_TYPE_TKIP,
};

stwuct ath_tx_info {
	u8 qcu;

	boow is_fiwst;
	boow is_wast;

	enum aggw_type aggw;
	u8 ndewim;
	u16 aggw_wen;

	dma_addw_t wink;
	int pkt_wen;
	u32 fwags;

	dma_addw_t buf_addw[4];
	int buf_wen[4];

	stwuct ath9k_11n_wate_sewies wates[4];
	u8 wtscts_wate;
	boow duw_update;

	enum ath9k_pkt_type type;
	enum ath9k_key_type keytype;
	u8 keyix;
	u8 txpowew[4];
};

stwuct ath_hw;
stwuct ath9k_channew;
enum ath9k_int;

u32 ath9k_hw_gettxbuf(stwuct ath_hw *ah, u32 q);
void ath9k_hw_puttxbuf(stwuct ath_hw *ah, u32 q, u32 txdp);
void ath9k_hw_txstawt(stwuct ath_hw *ah, u32 q);
u32 ath9k_hw_numtxpending(stwuct ath_hw *ah, u32 q);
boow ath9k_hw_updatetxtwigwevew(stwuct ath_hw *ah, boow bIncTwigWevew);
boow ath9k_hw_stop_dma_queue(stwuct ath_hw *ah, u32 q);
void ath9k_hw_abowt_tx_dma(stwuct ath_hw *ah);
boow ath9k_hw_set_txq_pwops(stwuct ath_hw *ah, int q,
			    const stwuct ath9k_tx_queue_info *qinfo);
boow ath9k_hw_get_txq_pwops(stwuct ath_hw *ah, int q,
			    stwuct ath9k_tx_queue_info *qinfo);
int ath9k_hw_setuptxqueue(stwuct ath_hw *ah, enum ath9k_tx_queue type,
			  const stwuct ath9k_tx_queue_info *qinfo);
boow ath9k_hw_weweasetxqueue(stwuct ath_hw *ah, u32 q);
boow ath9k_hw_wesettxqueue(stwuct ath_hw *ah, u32 q);
int ath9k_hw_wxpwocdesc(stwuct ath_hw *ah, stwuct ath_desc *ds,
			stwuct ath_wx_status *ws);
void ath9k_hw_setupwxdesc(stwuct ath_hw *ah, stwuct ath_desc *ds,
			  u32 size, u32 fwags);
boow ath9k_hw_setwxabowt(stwuct ath_hw *ah, boow set);
void ath9k_hw_putwxbuf(stwuct ath_hw *ah, u32 wxdp);
void ath9k_hw_stawtpcuweceive(stwuct ath_hw *ah, boow is_scanning);
void ath9k_hw_abowtpcuwecv(stwuct ath_hw *ah);
boow ath9k_hw_stopdmawecv(stwuct ath_hw *ah, boow *weset);
int ath9k_hw_beaconq_setup(stwuct ath_hw *ah);
void ath9k_hw_set_tx_fiwtew(stwuct ath_hw *ah, u8 destidx, boow set);

/* Intewwupt Handwing */
boow ath9k_hw_intwpend(stwuct ath_hw *ah);
void ath9k_hw_set_intewwupts(stwuct ath_hw *ah);
void ath9k_hw_enabwe_intewwupts(stwuct ath_hw *ah);
void ath9k_hw_disabwe_intewwupts(stwuct ath_hw *ah);
void ath9k_hw_kiww_intewwupts(stwuct ath_hw *ah);
void ath9k_hw_wesume_intewwupts(stwuct ath_hw *ah);

void aw9002_hw_attach_mac_ops(stwuct ath_hw *ah);

#endif /* MAC_H */
