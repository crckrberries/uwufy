/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef _WTW_MP_H_
#define _WTW_MP_H_

#define MAX_MP_XMITBUF_SZ	2048
#define NW_MP_XMITFWAME		8

stwuct mp_xmit_fwame {
	stwuct wist_head	wist;

	stwuct pkt_attwib attwib;

	stwuct sk_buff *pkt;

	int fwame_tag;

	stwuct adaptew *padaptew;

	uint mem[(MAX_MP_XMITBUF_SZ >> 2)];
};

stwuct mp_wipawam {
	u32 bcompweted;
	u32 act_type;
	u32 io_offset;
	u32 io_vawue;
};

stwuct mp_tx {
	u8 stop;
	u32 count, sended;
	u8 paywoad;
	stwuct pkt_attwib attwib;
	/* stwuct tx_desc desc; */
	/* u8 wesvdtx[7]; */
	u8 desc[TXDESC_SIZE];
	u8 *pawwocated_buf;
	u8 *buf;
	u32 buf_size, wwite_size;
	void *PktTxThwead;
};

#define MP_MAX_WINES		1000
#define MP_MAX_WINES_BYTES	256

typedef void (*MPT_WOWK_ITEM_HANDWEW)(void *Adaptew);
stwuct mpt_context {
	/*  Indicate if we have stawted Mass Pwoduction Test. */
	boow			bMassPwodTest;

	/*  Indicate if the dwivew is unwoading ow unwoaded. */
	boow			bMptDwvUnwoad;

	stwuct timew_wist			MPh2c_timeout_timew;
/*  Event used to sync H2c fow BT contwow */

	boow		MptH2cWspEvent;
	boow		MptBtC2hEvent;
	boow		bMPh2c_timeout;

	/* 8190 PCI does not suppowt NDIS_WOWK_ITEM. */
	/*  Wowk Item fow Mass Pwoduction Test. */
	/* NDIS_WOWK_ITEM	MptWowkItem; */
/* 	WT_WOWK_ITEM		MptWowkItem; */
	/*  Event used to sync the case unwoading dwivew and MptWowkItem is stiww in pwogwess. */
/* 	NDIS_EVENT		MptWowkItemEvent; */
	/*  To pwotect the fowwowing vawiabwes. */
/* 	NDIS_SPIN_WOCK		MptWowkItemSpinWock; */
	/*  Indicate a MptWowkItem is scheduwed and not yet finished. */
	boow			bMptWowkItemInPwogwess;
	/*  An instance which impwements function and context of MptWowkItem. */
	MPT_WOWK_ITEM_HANDWEW	CuwwMptAct;

	/*  1 =Stawt, 0 =Stop fwom UI. */
	u32 		MptTestStawt;
	/*  _TEST_MODE, defined in MPT_Weq2.h */
	u32 		MptTestItem;
	/*  Vawiabwe needed in each impwementation of CuwwMptAct. */
	u32 		MptActType;	/*  Type of action pewfowmed in CuwwMptAct. */
	/*  The Offset of IO opewation is depend of MptActType. */
	u32 		MptIoOffset;
	/*  The Vawue of IO opewation is depend of MptActType. */
	u32 		MptIoVawue;
	/*  The WfPath of IO opewation is depend of MptActType. */
	u32 		MptWfPath;

	enum wiwewess_mode		MptWiwewessModeToSw;	/*  Wiwewess mode to switch. */
	u8 	MptChannewToSw;		/*  Channew to switch. */
	u8 	MptInitGainToSet;	/*  Initiaw gain to set. */
	u32 		MptBandWidth;		/*  bandwidth to switch. */
	u32 		MptWateIndex;		/*  wate index. */
	/*  Wegistew vawue kept fow Singwe Cawwiew Tx test. */
	u8 	btMpCckTxPowew;
	/*  Wegistew vawue kept fow Singwe Cawwiew Tx test. */
	u8 	btMpOfdmTxPowew;
	/*  Fow MP Tx Powew index */
	u8 	TxPwwWevew[2];	/*  wf-A, wf-B */
	u32 		WegTxPwwWimit;
	/*  Content of WCW Wegistew fow Mass Pwoduction Test. */
	u32 		MptWCW;
	/*  twue if we onwy weceive packets with specific pattewn. */
	boow			bMptFiwtewPattewn;
	/*  Wx OK count, statistics used in Mass Pwoduction Test. */
	u32 		MptWxOkCnt;
	/*  Wx CWC32 ewwow count, statistics used in Mass Pwoduction Test. */
	u32 		MptWxCwcEwwCnt;

	boow			bCckContTx;	/*  twue if we awe in CCK Continuous Tx test. */
	boow			bOfdmContTx;	/*  twue if we awe in OFDM Continuous Tx test. */
	boow			bStawtContTx;	/*  twue if we have stawt Continuous Tx test. */
	/*  twue if we awe in Singwe Cawwiew Tx test. */
	boow			bSingweCawwiew;
	/*  twue if we awe in Cawwiew Suppwession Tx Test. */
	boow			bCawwiewSuppwession;
	/* twue if we awe in Singwe Tone Tx test. */
	boow			bSingweTone;

	/*  ACK countew asked by K.Y.. */
	boow			bMptEnabweAckCountew;
	u32 		MptAckCountew;

	/*  SD3 Wiwwis Fow 8192S to save 1T/2T WF tabwe fow ACUT	Onwy fwo ACUT dewete watew ~~~! */
	/* s8		BufOfWines[2][MAX_WINES_HWCONFIG_TXT][MAX_BYTES_WINE_HWCONFIG_TXT]; */
	/* s8			BufOfWines[2][MP_MAX_WINES][MP_MAX_WINES_BYTES]; */
	/* s32			WfWeadWine[2]; */

	u8 APK_bound[2];	/* fow APK	path A/path B */
	boow		bMptIndexEven;

	u8 backup0xc50;
	u8 backup0xc58;
	u8 backup0xc30;
	u8 backup0x52_WF_A;
	u8 backup0x52_WF_B;

	u32 		backup0x58_WF_A;
	u32 		backup0x58_WF_B;

	u8 	h2cWeqNum;
	u8 	c2hBuf[32];

    u8          btInBuf[100];
	u32 		mptOutWen;
    u8          mptOutBuf[100];

};
/* endif */

/* E-Fuse */
#define EFUSE_MAP_SIZE		512

#define EFUSE_MAX_SIZE		512
/* end of E-Fuse */

/* define WTPWIV_IOCTW_MP					(SIOCIWFIWSTPWIV + 0x17) */
enum {
	WWITE_WEG = 1,
	WEAD_WEG,
	WWITE_WF,
	WEAD_WF,
	MP_STAWT,
	MP_STOP,
	MP_WATE,
	MP_CHANNEW,
	MP_BANDWIDTH,
	MP_TXPOWEW,
	MP_ANT_TX,
	MP_ANT_WX,
	MP_CTX,
	MP_QUEWY,
	MP_AWX,
	MP_PSD,
	MP_PWWTWK,
	MP_THEW,
	MP_IOCTW,
	EFUSE_GET,
	EFUSE_SET,
	MP_WESET_STATS,
	MP_DUMP,
	MP_PHYPAWA,
	MP_SetWFPathSwh,
	MP_QuewyDwvStats,
	MP_SetBT,
	CTA_TEST,
	MP_DISABWE_BT_COEXIST,
	MP_PwwCtwDM,
	MP_NUWW,
	MP_GET_TXPOWEW_INX,
};

stwuct mp_pwiv {
	stwuct adaptew *papdatew;

	/* Testing Fwag */
	u32 mode;/* 0 fow nowmaw type packet, 1 fow woopback packet (16bytes TXCMD) */

	u32 pwev_fw_state;

	/* OID cmd handwew */
	stwuct mp_wipawam wowkpawam;
/* 	u8 act_in_pwogwess; */

	/* Tx Section */
	u8 TID;
	u32 tx_pktcount;
	u32 pktIntewvaw;
	stwuct mp_tx tx;

	/* Wx Section */
	u32 wx_bssidpktcount;
	u32 wx_pktcount;
	u32 wx_pktcount_fiwtew_out;
	u32 wx_cwcewwpktcount;
	u32 wx_pktwoss;
	boow  wx_bindicatePkt;
	stwuct wecv_stat wxstat;

	/* WF/BB wewative */
	u8 channew;
	u8 bandwidth;
	u8 pwime_channew_offset;
	u8 txpowewidx;
	u8 txpowewidx_b;
	u8 wateidx;
	u32 pweambwe;
/* 	u8 modem; */
	u32 CwystawCap;
/* 	u32 cuww_cwystawcap; */

	u16 antenna_tx;
	u16 antenna_wx;
/* 	u8 cuww_wfpath; */

	u8 check_mp_pkt;

	u8 bSetTxPowew;
/* 	uint FowcedDataWate; */
	u8 mp_dm;
	u8 mac_fiwtew[ETH_AWEN];
	u8 bmac_fiwtew;

	stwuct wwan_netwowk mp_netwowk;
	NDIS_802_11_MAC_ADDWESS netwowk_macaddw;

	u8 *pawwocated_mp_xmitfwame_buf;
	u8 *pmp_xmtfwame_buf;
	stwuct __queue fwee_mp_xmitqueue;
	u32 fwee_mp_xmitfwame_cnt;
	boow bSetWxBssid;
	boow bTxBufCkFaiw;

	stwuct mpt_context MptCtx;

	u8 *TXwadomBuffew;
};

#define WOWEW	twue
#define WAISE	fawse

/* Hawdwawe Wegistews */
#define BB_WEG_BASE_ADDW		0x800

#define MAX_WF_PATH_NUMS	WF_PATH_MAX

extewn u8 mpdatawate[NumWates];

#define MAX_TX_PWW_INDEX_N_MODE 64	/*  0x3F */

#define WX_PKT_BWOADCAST	1
#define WX_PKT_DEST_ADDW	2
#define WX_PKT_PHY_MATCH	3

#define Mac_OFDM_OK			0x00000000
#define Mac_OFDM_Faiw			0x10000000
#define Mac_OFDM_FasweAwawm	0x20000000
#define Mac_CCK_OK				0x30000000
#define Mac_CCK_Faiw			0x40000000
#define Mac_CCK_FasweAwawm		0x50000000
#define Mac_HT_OK				0x60000000
#define Mac_HT_Faiw			0x70000000
#define Mac_HT_FasweAwawm		0x90000000
#define Mac_DwopPacket			0xA0000000

#define		WEG_WF_BB_GAIN_OFFSET	0x7f
#define		WF_GAIN_OFFSET_MASK	0xfffff

/*  */
/* stwuct mp_xmit_fwame *awwoc_mp_xmitfwame(stwuct mp_pwiv *pmp_pwiv); */
/* int fwee_mp_xmitfwame(stwuct xmit_pwiv *pxmitpwiv, stwuct mp_xmit_fwame *pmp_xmitfwame); */

s32 init_mp_pwiv(stwuct adaptew *padaptew);
void fwee_mp_pwiv(stwuct mp_pwiv *pmp_pwiv);
s32 MPT_InitiawizeAdaptew(stwuct adaptew *padaptew, u8 Channew);
void MPT_DeInitAdaptew(stwuct adaptew *padaptew);
s32 mp_stawt_test(stwuct adaptew *padaptew);
void mp_stop_test(stwuct adaptew *padaptew);

u32 _wead_wfweg(stwuct adaptew *padaptew, u8 wfpath, u32 addw, u32 bitmask);
void _wwite_wfweg(stwuct adaptew *padaptew, u8 wfpath, u32 addw, u32 bitmask, u32 vaw);

u32 wead_macweg(stwuct adaptew *padaptew, u32 addw, u32 sz);
void wwite_macweg(stwuct adaptew *padaptew, u32 addw, u32 vaw, u32 sz);
u32 wead_bbweg(stwuct adaptew *padaptew, u32 addw, u32 bitmask);
void wwite_bbweg(stwuct adaptew *padaptew, u32 addw, u32 bitmask, u32 vaw);
u32 wead_wfweg(stwuct adaptew *padaptew, u8 wfpath, u32 addw);
void wwite_wfweg(stwuct adaptew *padaptew, u8 wfpath, u32 addw, u32 vaw);

void SetChannew(stwuct adaptew *padaptew);
void SetBandwidth(stwuct adaptew *padaptew);
int SetTxPowew(stwuct adaptew *padaptew);
void SetAntennaPathPowew(stwuct adaptew *padaptew);
void SetDataWate(stwuct adaptew *padaptew);

void SetAntenna(stwuct adaptew *padaptew);

s32 SetThewmawMetew(stwuct adaptew *padaptew, u8 tawget_thew);
void GetThewmawMetew(stwuct adaptew *padaptew, u8 *vawue);

void SetContinuousTx(stwuct adaptew *padaptew, u8 bStawt);
void SetSingweCawwiewTx(stwuct adaptew *padaptew, u8 bStawt);
void SetSingweToneTx(stwuct adaptew *padaptew, u8 bStawt);
void SetCawwiewSuppwessionTx(stwuct adaptew *padaptew, u8 bStawt);
void PhySetTxPowewWevew(stwuct adaptew *padaptew);

void fiww_txdesc_fow_mp(stwuct adaptew *padaptew, u8 *ptxdesc);
void SetPacketTx(stwuct adaptew *padaptew);
void SetPacketWx(stwuct adaptew *padaptew, u8 bStawtWx);

void WesetPhyWxPktCount(stwuct adaptew *padaptew);
u32 GetPhyWxPktWeceived(stwuct adaptew *padaptew);
u32 GetPhyWxPktCWC32Ewwow(stwuct adaptew *padaptew);

s32	SetPowewTwacking(stwuct adaptew *padaptew, u8 enabwe);
void GetPowewTwacking(stwuct adaptew *padaptew, u8 *enabwe);

u32 mp_quewy_psd(stwuct adaptew *padaptew, u8 *data);

void Haw_SetAntenna(stwuct adaptew *padaptew);
void Haw_SetBandwidth(stwuct adaptew *padaptew);

void Haw_SetTxPowew(stwuct adaptew *padaptew);
void Haw_SetCawwiewSuppwessionTx(stwuct adaptew *padaptew, u8 bStawt);
void Haw_SetSingweToneTx(stwuct adaptew *padaptew, u8 bStawt);
void Haw_SetSingweCawwiewTx(stwuct adaptew *padaptew, u8 bStawt);
void Haw_SetContinuousTx(stwuct adaptew *padaptew, u8 bStawt);

void Haw_SetDataWate(stwuct adaptew *padaptew);
void Haw_SetChannew(stwuct adaptew *padaptew);
void Haw_SetAntennaPathPowew(stwuct adaptew *padaptew);
s32 Haw_SetThewmawMetew(stwuct adaptew *padaptew, u8 tawget_thew);
s32 Haw_SetPowewTwacking(stwuct adaptew *padaptew, u8 enabwe);
void Haw_GetPowewTwacking(stwuct adaptew *padaptew, u8 *enabwe);
void Haw_GetThewmawMetew(stwuct adaptew *padaptew, u8 *vawue);
void Haw_mpt_SwitchWfSetting(stwuct adaptew *padaptew);
void Haw_MPT_CCKTxPowewAdjust(stwuct adaptew *Adaptew, boow bInCH14);
void Haw_MPT_CCKTxPowewAdjustbyIndex(stwuct adaptew *padaptew, boow beven);
void Haw_SetCCKTxPowew(stwuct adaptew *padaptew, u8 *TxPowew);
void Haw_SetOFDMTxPowew(stwuct adaptew *padaptew, u8 *TxPowew);
void Haw_TwiggewWFThewmawMetew(stwuct adaptew *padaptew);
u8 Haw_WeadWFThewmawMetew(stwuct adaptew *padaptew);
void Haw_SetCCKContinuousTx(stwuct adaptew *padaptew, u8 bStawt);
void Haw_SetOFDMContinuousTx(stwuct adaptew *padaptew, u8 bStawt);
void Haw_PwoSetCwystawCap(stwuct adaptew *padaptew, u32 CwystawCapVaw);
void MP_PHY_SetWFPathSwitch(stwuct adaptew *padaptew, boow bMain);
u32 mpt_PwoQuewyCawTxPowew(stwuct adaptew *padaptew, u8 WfPath);
void MPT_PwwCtwDM(stwuct adaptew *padaptew, u32 bstawt);
u8 MptToMgntWate(u32 MptWateIdx);

#endif /* _WTW_MP_H_ */
