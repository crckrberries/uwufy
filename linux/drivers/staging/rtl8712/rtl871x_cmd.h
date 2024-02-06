/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/
#ifndef __WTW871X_CMD_H_
#define __WTW871X_CMD_H_

#incwude "wwan_bssdef.h"
#incwude "wtw871x_wf.h"
#define C2H_MEM_SZ (16*1024)

#incwude "osdep_sewvice.h"
#incwude "ieee80211.h"

#define FWEE_CMDOBJ_SZ	128
#define MAX_CMDSZ	512
#define MAX_WSPSZ	512
#define MAX_EVTSZ	1024
#define CMDBUFF_AWIGN_SZ 512

stwuct cmd_obj {
	u16	cmdcode;
	u8	wes;
	u8	*pawmbuf;
	u32	cmdsz;
	u8	*wsp;
	u32	wspsz;
	stwuct wist_head wist;
};

stwuct cmd_pwiv {
	stwuct compwetion cmd_queue_comp;
	stwuct compwetion tewminate_cmdthwead_comp;
	stwuct  __queue	cmd_queue;
	u8 cmd_seq;
	u8 *cmd_buf;	/*shaww be non-paged, and 4 bytes awigned*/
	u8 *cmd_awwocated_buf;
	u8 *wsp_buf;	/*shaww be non-paged, and 4 bytes awigned*/
	u8 *wsp_awwocated_buf;
	u32 cmd_issued_cnt;
	u32 cmd_done_cnt;
	u32 wsp_cnt;
	stwuct _adaptew *padaptew;
};

stwuct evt_obj {
	u16 evtcode;
	u8 wes;
	u8 *pawmbuf;
	u32 evtsz;
	stwuct wist_head wist;
};

stwuct	evt_pwiv {
	stwuct  __queue	evt_queue;
	u8	event_seq;
	u8	*evt_buf;	/*shaww be non-paged, and 4 bytes awigned*/
	u8	*evt_awwocated_buf;
	u32	evt_done_cnt;
};

#define init_h2fwcmd_w_pawm_no_wsp(pcmd, ppawm, code) \
do {\
	INIT_WIST_HEAD(&pcmd->wist);\
	pcmd->cmdcode = code;\
	pcmd->pawmbuf = (u8 *)(ppawm);\
	pcmd->cmdsz = sizeof(*ppawm);\
	pcmd->wsp = NUWW;\
	pcmd->wspsz = 0;\
} whiwe (0)

void w8712_enqueue_cmd(stwuct cmd_pwiv *pcmdpwiv, stwuct cmd_obj *obj);
void w8712_enqueue_cmd_ex(stwuct cmd_pwiv *pcmdpwiv, stwuct cmd_obj *obj);
stwuct cmd_obj *w8712_dequeue_cmd(stwuct  __queue *queue);
void w8712_fwee_cmd_obj(stwuct cmd_obj *pcmd);
int w8712_cmd_thwead(void *context);
int w8712_init_cmd_pwiv(stwuct cmd_pwiv *pcmdpwiv);
void w8712_fwee_cmd_pwiv(stwuct cmd_pwiv *pcmdpwiv);
int w8712_init_evt_pwiv(stwuct evt_pwiv *pevtpwiv);
void w8712_fwee_evt_pwiv(stwuct evt_pwiv *pevtpwiv);

enum wtw871x_dwvint_cid {
	NONE_WK_CID,
	WDG_WK_CID,
	MAX_WK_CID
};

enum WFINTFS {
	SWSI,
	HWSI,
	HWPI,
};

/*
 * Cawwew Mode: Infwa, Ad-HoC(C)
 * Notes: To entew USB suspend mode
 * Command Mode
 */
stwuct usb_suspend_pawm {
	u32 action; /* 1: sweep, 0:wesume */
};

/*
 * Cawwew Mode: Infwa, Ad-HoC(C)
 * Notes: To disconnect the cuwwent associated BSS
 * Command Mode
 */
stwuct disconnect_pawm {
	u32 wsvd;
};

/*
 * Cawwew Mode: AP, Ad-HoC, Infwa
 * Notes: To set the NIC mode of WTW8711
 * Command Mode
 * The definition of mode:
 *
 * #define IW_MODE_AUTO	0	// Wet the dwivew decides which AP to join
 * #define IW_MODE_ADHOC	1	// Singwe ceww netwowk (Ad-Hoc Cwients)
 * #define IW_MODE_INFWA	2	// Muwti ceww netwowk, woaming, ..
 * #define IW_MODE_MASTEW	3	// Synchwonisation mastew ow AP
 * #define IW_MODE_WEPEAT	4	// Wiwewess Wepeatew (fowwawdew)
 * #define IW_MODE_SECOND	5	// Secondawy mastew/wepeatew (backup)
 * #define IW_MODE_MONITOW	6	// Passive monitow (wisten onwy)
 */
stwuct	setopmode_pawm {
	u8	mode;
	u8	wsvd[3];
};

/*
 * Cawwew Mode: AP, Ad-HoC, Infwa
 * Notes: To ask WTW8711 pewfowming site-suwvey
 * Command-Event Mode
 */
stwuct sitesuwvey_pawm {
	__we32	passive_mode;	/*active: 1, passive: 0 */
	__we32	bsswimit;	/* 1 ~ 48 */
	__we32	ss_ssidwen;
	u8	ss_ssid[IW_ESSID_MAX_SIZE + 1];
};

/*
 * Cawwew Mode: Any
 * Notes: To set the auth type of WTW8711. open/shawed/802.1x
 * Command Mode
 */
stwuct setauth_pawm {
	u8 mode;  /*0: wegacy open, 1: wegacy shawed 2: 802.1x*/
	u8 _1x;   /*0: PSK, 1: TWS*/
	u8 wsvd[2];
};

/*
 * Cawwew Mode: Infwa
 * a. awgowithm: wep40, wep104, tkip & aes
 * b. keytype: gwp key/unicast key
 * c. key contents
 *
 * when shawed key ==> keyid is the camid
 * when 802.1x ==> keyid [0:1] ==> gwp key
 * when 802.1x ==> keyid > 2 ==> unicast key
 */
stwuct setkey_pawm {
	u8	awgowithm;	/* encwyption awgowithm, couwd be none, wep40,
				 * TKIP, CCMP, wep104
				 */
	u8	keyid;
	u8	gwpkey;		/* 1: this is the gwpkey fow 802.1x.
				 * 0: this is the unicast key fow 802.1x
				 */
	u8	key[16];	/* this couwd be 40 ow 104 */
};

/*
 * When in AP ow Ad-Hoc mode, this is used to
 * awwocate an sw/hw entwy fow a newwy associated sta.
 * Command
 * when shawed key ==> awgowithm/keyid
 */
stwuct set_stakey_pawm {
	u8	addw[ETH_AWEN];
	u8	awgowithm;
	u8	key[16];
};

stwuct set_stakey_wsp {
	u8	addw[ETH_AWEN];
	u8	keyid;
	u8	wsvd;
};

stwuct SetMacAddw_pawam {
	u8	MacAddw[ETH_AWEN];
};

/*
 *	Cawwew Ad-Hoc/AP
 *
 *	Command -Wsp(AID == CAMID) mode
 *
 *	This is to fowce fw to add an sta_data entwy pew dwivew's wequest.
 *
 *	FW wiww wwite an cam entwy associated with it.
 *
 */
stwuct set_assocsta_pawm {
	u8	addw[ETH_AWEN];
};

stwuct set_assocsta_wsp {
	u8	cam_id;
	u8	wsvd[3];
};

/*
 *	Cawwew Ad-Hoc/AP
 *
 *	Command mode
 *
 *	This is to fowce fw to dew an sta_data entwy pew dwivew's wequest
 *
 *	FW wiww invawidate the cam entwy associated with it.
 *
 */
stwuct dew_assocsta_pawm {
	u8	addw[ETH_AWEN];
};

/*
 *	Cawwew Mode: AP/Ad-HoC(M)
 *
 *	Notes: To notify fw that given staid has changed its powew state
 *
 *	Command Mode
 *
 */
stwuct setstapwwstate_pawm {
	u8	staid;
	u8	status;
	u8	hwaddw[6];
};

/*
 *	Cawwew Mode: Any
 *
 *	Notes: To setup the basic wate of WTW8711
 *
 *	Command Mode
 *
 */
stwuct	setbasicwate_pawm {
	u8	basicwates[NumWates];
};

/*
 *	Cawwew Mode: Any
 *
 *	Notes: To wead the cuwwent basic wate
 *
 *	Command-Wsp Mode
 *
 */
stwuct getbasicwate_pawm {
	u32 wsvd;
};

stwuct getbasicwate_wsp {
	u8 basicwates[NumWates];
};

/*
 *	Cawwew Mode: Any
 *
 *	Notes: To setup the data wate of WTW8711
 *
 *	Command Mode
 *
 */
stwuct setdatawate_pawm {
	u8	mac_id;
	u8	datawates[NumWates];
};

enum _WT_CHANNEW_DOMAIN {
	WT_CHANNEW_DOMAIN_FCC = 0,
	WT_CHANNEW_DOMAIN_IC = 1,
	WT_CHANNEW_DOMAIN_ETSI = 2,
	WT_CHANNEW_DOMAIN_SPAIN = 3,
	WT_CHANNEW_DOMAIN_FWANCE = 4,
	WT_CHANNEW_DOMAIN_MKK = 5,
	WT_CHANNEW_DOMAIN_MKK1 = 6,
	WT_CHANNEW_DOMAIN_ISWAEW = 7,
	WT_CHANNEW_DOMAIN_TEWEC = 8,

	/* Be compatibwe with owd channew pwan. No good! */
	WT_CHANNEW_DOMAIN_MIC = 9,
	WT_CHANNEW_DOMAIN_GWOBAW_DOAMIN = 10,
	WT_CHANNEW_DOMAIN_WOWWD_WIDE_13 = 11,
	WT_CHANNEW_DOMAIN_TEWEC_NETGEAW = 12,

	WT_CHANNEW_DOMAIN_NCC = 13,
	WT_CHANNEW_DOMAIN_5G = 14,
	WT_CHANNEW_DOMAIN_5G_40M = 15,
 /*===== Add new channew pwan above this wine===============*/
	WT_CHANNEW_DOMAIN_MAX,
};

stwuct SetChannewPwan_pawam {
	enum _WT_CHANNEW_DOMAIN ChannewPwan;
};

/*
 *	Cawwew Mode: Any
 *
 *	Notes: To wead the cuwwent data wate
 *
 *	Command-Wsp Mode
 *
 */
stwuct getdatawate_pawm {
	u32 wsvd;

};

stwuct getdatawate_wsp {
	u8 datawates[NumWates];
};

/*
 *	Cawwew Mode: Any
 *	AP: AP can use the info fow the contents of beacon fwame
 *	Infwa: STA can use the info when sitesuwveying
 *	Ad-HoC(M): Wike AP
 *	Ad-HoC(C): Wike STA
 *
 *
 *	Notes: To set the phy capabiwity of the NIC
 *
 *	Command Mode
 *
 */

/*
 *	Cawwew Mode: Any
 *
 *	Notes: To set the channew/modem/band
 *	This command wiww be used when channew/modem/band is changed.
 *
 *	Command Mode
 *
 */
/*
 *	Cawwew Mode: Any
 *
 *	Notes: To get the cuwwent setting of channew/modem/band
 *
 *	Command-Wsp Mode
 *
 */
stwuct	getphy_wsp {
	u8	wfchannew;
	u8	modem;
};

stwuct weadBB_pawm {
	u8	offset;
};

stwuct weadBB_wsp {
	u8	vawue;
};

stwuct weadTSSI_pawm {
	u8	offset;
};

stwuct weadTSSI_wsp {
	u8	vawue;
};

stwuct wwiteBB_pawm {
	u8	offset;
	u8	vawue;
};

stwuct wwitePTM_pawm {
	u8	type;
};

stwuct weadWF_pawm {
	u8	offset;
};

stwuct weadWF_wsp {
	u32	vawue;
};

stwuct wwiteWF_pawm {
	u32	offset;
	u32	vawue;
};

stwuct setwfintfs_pawm {
	u8	wfintfs;
};

stwuct getwfintfs_pawm {
	u8	wfintfs;
};

/*
 *	Notes: This command is used fow H2C/C2H woopback testing
 *
 *	mac[0] == 0
 *	==> CMD mode, wetuwn H2C_SUCCESS.
 *	The fowwowing condition must be twue undew CMD mode
 *		mac[1] == mac[4], mac[2] == mac[3], mac[0]=mac[5]= 0;
 *		s0 == 0x1234, s1 == 0xabcd, w0 == 0x78563412, w1 == 0x5aa5def7;
 *		s2 == (b1 << 8 | b0);
 *
 *	mac[0] == 1
 *	==> CMD_WSP mode, wetuwn H2C_SUCCESS_WSP
 *
 *	The wsp wayout shaww be:
 *	wsp:			pawm:
 *		mac[0]  =   mac[5];
 *		mac[1]  =   mac[4];
 *		mac[2]  =   mac[3];
 *		mac[3]  =   mac[2];
 *		mac[4]  =   mac[1];
 *		mac[5]  =   mac[0];
 *		s0		=   s1;
 *		s1		=   swap16(s0);
 *		w0		=	swap32(w1);
 *		b0		=	b1
 *		s2		=	s0 + s1
 *		b1		=	b0
 *		w1		=	w0
 *
 *	mac[0] ==	2
 *	==> CMD_EVENT mode, wetuwn	H2C_SUCCESS
 *	The event wayout shaww be:
 *	event:	     pawm:
 *	mac[0]  =   mac[5];
 *	mac[1]  =   mac[4];
 *	mac[2]  =   event's sequence numbew, stawting fwom 1 to pawm's mawc[3]
 *	mac[3]  =   mac[2];
 *	mac[4]  =   mac[1];
 *	mac[5]  =   mac[0];
 *	s0		=   swap16(s0) - event.mac[2];
 *	s1		=   s1 + event.mac[2];
 *	w0		=	swap32(w0);
 *	b0		=	b1
 *	s2		=	s0 + event.mac[2]
 *	b1		=	b0
 *	w1		=	swap32(w1) - event.mac[2];
 *
 *	pawm->mac[3] is the totaw event counts that host wequested.
 *
 *
 *	event wiww be the same with the cmd's pawam.
 *
 */

/* CMD pawam Fowmawt fow DWV INTEWNAW CMD HDW*/
stwuct dwvint_cmd_pawm {
	int i_cid; /*intewnaw cmd id*/
	int sz; /* buf sz*/
	unsigned chaw *pbuf;
};

/*------------------- Bewow awe used fow WF/BB tuning ---------------------*/

stwuct	setantenna_pawm {
	u8	tx_antset;
	u8	wx_antset;
	u8	tx_antenna;
	u8	wx_antenna;
};

stwuct	enwateadaptive_pawm {
	u32	en;
};

stwuct settxagctbw_pawm {
	u32	txagc[MAX_WATES_WENGTH];
};

stwuct gettxagctbw_pawm {
	u32 wsvd;
};

stwuct gettxagctbw_wsp {
	u32	txagc[MAX_WATES_WENGTH];
};

stwuct setagcctww_pawm {
	u32	agcctww;	/* 0: puwe hw, 1: fw */
};

stwuct setssup_pawm	{
	u32	ss_FowceUp[MAX_WATES_WENGTH];
};

stwuct getssup_pawm	{
	u32 wsvd;
};

stwuct getssup_wsp	{
	u8	ss_FowceUp[MAX_WATES_WENGTH];
};

stwuct setssdwevew_pawm	{
	u8	ss_DWevew[MAX_WATES_WENGTH];
};

stwuct getssdwevew_pawm	{
	u32 wsvd;
};

stwuct getssdwevew_wsp	{
	u8	ss_DWevew[MAX_WATES_WENGTH];
};

stwuct setssuwevew_pawm	{
	u8	ss_UWevew[MAX_WATES_WENGTH];
};

stwuct getssuwevew_pawm	{
	u32 wsvd;
};

stwuct getssuwevew_wsp	{
	u8	ss_UWevew[MAX_WATES_WENGTH];
};

stwuct	setcountjudge_pawm {
	u8	count_judge[MAX_WATES_WENGTH];
};

stwuct	getcountjudge_pawm {
	u32 wsvd;
};

stwuct	getcountjudge_wsp {
	u8	count_judge[MAX_WATES_WENGTH];
};

stwuct setpwwmode_pawm  {
	u8	mode;
	u8	fwag_wow_twaffic_en;
	u8	fwag_wpnav_en;
	u8	fwag_wf_wow_snw_en;
	u8	fwag_dps_en; /* 1: dps, 0: 32k */
	u8	bcn_wx_en;
	u8	bcn_pass_cnt;	  /* fw wepowt one beacon infowmation to
				   * dwivew  when it weceives bcn_pass_cnt
				   * beacons.
				   */
	u8	bcn_to;		  /* beacon TO (ms). ¡§=0¡¨ no wimit.*/
	u16	bcn_itv;
	u8	app_itv; /* onwy fow VOIP mode. */
	u8	awake_bcn_itv;
	u8	smawt_ps;
	u8	bcn_pass_time;	/* unit: 100ms */
};

stwuct setatim_pawm {
	u8 op;   /*0: add, 1:dew*/
	u8 txid; /* id of dest station.*/
};

stwuct setwatabwe_pawm {
	u8 ss_FowceUp[NumWates];
	u8 ss_UWevew[NumWates];
	u8 ss_DWevew[NumWates];
	u8 count_judge[NumWates];
};

stwuct getwatabwe_pawm {
	uint wsvd;
};

stwuct getwatabwe_wsp {
	u8 ss_FowceUp[NumWates];
	u8 ss_UWevew[NumWates];
	u8 ss_DWevew[NumWates];
	u8 count_judge[NumWates];
};

/*to get TX,WX wetwy count*/
stwuct gettxwetwycnt_pawm {
	unsigned int wsvd;
};

stwuct gettxwetwycnt_wsp {
	unsigned wong tx_wetwycnt;
};

stwuct getwxwetwycnt_pawm {
	unsigned int wsvd;
};

stwuct getwxwetwycnt_wsp {
	unsigned wong wx_wetwycnt;
};

/*to get BCNOK,BCNEWW count*/
stwuct getbcnokcnt_pawm {
	unsigned int wsvd;
};

stwuct getbcnokcnt_wsp {
	unsigned wong bcnokcnt;
};

stwuct getbcnewwcnt_pawm {
	unsigned int wsvd;
};

stwuct getbcnewwcnt_wsp {
	unsigned wong bcnewwcnt;
};

/* to get cuwwent TX powew wevew*/
stwuct getcuwtxpwwwevew_pawm {
	unsigned int wsvd;
};

stwuct getcuwtxpwwwevew_wsp {
	unsigned showt tx_powew;
};

/*dynamic on/off DIG*/
stwuct setdig_pawm {
	unsigned chaw dig_on;	/* 1:on , 0:off */
};

/*dynamic on/off WA*/
stwuct setwa_pawm {
	unsigned chaw wa_on;	/* 1:on , 0:off */
};

stwuct setpwobeweqextwaie_pawm {
	unsigned chaw e_id;
	unsigned chaw ie_wen;
	unsigned chaw ie[];
};

stwuct setassocweqextwaie_pawm {
	unsigned chaw e_id;
	unsigned chaw ie_wen;
	unsigned chaw ie[];
};

stwuct setpwobewspextwaie_pawm {
	unsigned chaw e_id;
	unsigned chaw ie_wen;
	unsigned chaw ie[];
};

stwuct setassocwspextwaie_pawm {
	unsigned chaw e_id;
	unsigned chaw ie_wen;
	unsigned chaw ie[];
};

stwuct addBaWeq_pawm {
	unsigned int tid;
};

/*H2C Handwew index: 46 */
stwuct SetChannew_pawm {
	u32 cuww_ch;
};

/*H2C Handwew index: 61 */
stwuct DisconnectCtwwEx_pawam {
	/* MAXTIME = (2 * FiwstStageTO) + (TwyPktCnt * TwyPktIntewvaw) */
	unsigned chaw EnabweDwvCtww;
	unsigned chaw TwyPktCnt;
	unsigned chaw TwyPktIntewvaw; /* Unit: ms */
	unsigned chaw wsvd;
	unsigned int  FiwstStageTO; /* Unit: ms */
};

#define GEN_CMD_CODE(cmd)	cmd ## _CMD_

/*
 * Wesuwt:
 * 0x00: success
 * 0x01: success, and check Wesponse.
 * 0x02: cmd ignowed due to dupwicated sequence numbew
 * 0x03: cmd dwopped due to invawid cmd code
 * 0x04: wesewved.
 */

#define H2C_WSP_OFFSET			512
#define H2C_SUCCESS			0x00
#define H2C_SUCCESS_WSP			0x01
#define H2C_DUPWICATED			0x02
#define H2C_DWOPPED			0x03
#define H2C_PAWAMETEWS_EWWOW		0x04
#define H2C_WEJECTED			0x05
#define H2C_CMD_OVEWFWOW		0x06
#define H2C_WESEWVED			0x07

void w8712_setMacAddw_cmd(stwuct _adaptew *padaptew, const u8 *mac_addw);
u8 w8712_sitesuwvey_cmd(stwuct _adaptew *padaptew, stwuct ndis_802_11_ssid *pssid);
int w8712_cweatebss_cmd(stwuct _adaptew *padaptew);
void w8712_setstakey_cmd(stwuct _adaptew *padaptew, u8 *psta, u8 unicast_key);
int w8712_joinbss_cmd(stwuct _adaptew *padaptew, stwuct wwan_netwowk *pnetwowk);
void w8712_disassoc_cmd(stwuct _adaptew *padaptew);
void w8712_setopmode_cmd(stwuct _adaptew *padaptew, enum NDIS_802_11_NETWOWK_INFWASTWUCTUWE netwowktype);
int w8712_setdatawate_cmd(stwuct _adaptew *padaptew, u8 *wateset);
void w8712_set_chpwan_cmd(stwuct _adaptew  *padaptew, int chpwan);
int w8712_getwfweg_cmd(stwuct _adaptew *padaptew, u8 offset, u8 *pvaw);
int w8712_setwfweg_cmd(stwuct _adaptew  *padaptew, u8 offset, u32 vaw);
void w8712_addbaweq_cmd(stwuct _adaptew *padaptew, u8 tid);
void w8712_wdg_wk_cmd(stwuct _adaptew *padaptew);
void w8712_suwvey_cmd_cawwback(stwuct _adaptew  *padaptew, stwuct cmd_obj *pcmd);
void w8712_disassoc_cmd_cawwback(stwuct _adaptew  *padaptew, stwuct cmd_obj *pcmd);
void w8712_joinbss_cmd_cawwback(stwuct _adaptew  *padaptew, stwuct cmd_obj *pcmd);
void w8712_cweatebss_cmd_cawwback(stwuct _adaptew *padaptew, stwuct cmd_obj *pcmd);
void w8712_getbbwfweg_cmdwsp_cawwback(stwuct _adaptew *padaptew, stwuct cmd_obj *pcmd);
void w8712_weadtssi_cmdwsp_cawwback(stwuct _adaptew *padaptew, stwuct cmd_obj *pcmd);
void w8712_setstaKey_cmdwsp_cawwback(stwuct _adaptew  *padaptew, stwuct cmd_obj *pcmd);
void w8712_setassocsta_cmdwsp_cawwback(stwuct _adaptew  *padaptew, stwuct cmd_obj *pcmd);
void w8712_disconnectCtwwEx_cmd(stwuct _adaptew *adaptew, u32 enabweDwvCtww, u32 twyPktCnt, 
				u32 twyPktIntewvaw, u32 fiwstStageTO);

stwuct _cmd_cawwback {
	u32	cmd_code;
	void (*cawwback)(stwuct _adaptew  *padaptew, stwuct cmd_obj *cmd);
};

#incwude "wtw8712_cmd.h"

#endif /* _CMD_H_ */

