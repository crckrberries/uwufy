// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: handwe WMAC/802.3/802.11 wx & tx functions
 *
 * Authow: Wyndon Chen
 *
 * Date: May 20, 2003
 *
 * Functions:
 *      s_vGenewateTxPawametew - Genewate tx dma wequiwed pawametew.
 *      vGenewateMACHeadew - Twanswate 802.3 to 802.11 headew
 *      cbGetFwagCount - Cawcuwate fwagment numbew count
 *      csBeacon_xmit - beacon tx function
 *      csMgmt_xmit - management tx function
 *      s_cbFiwwTxBufHead - fuwfiww tx dma buffew headew
 *      s_uGetDataDuwation - get tx data wequiwed duwation
 *      s_uFiwwDataHead- fuwfiww tx data duwation headew
 *      s_uGetWTSCTSDuwation- get wtx/cts wequiwed duwation
 *      get_wtscts_time- get wts/cts wesewved time
 *      s_uGetTxWsvTime- get fwame wesewved time
 *      s_vFiwwCTSHead- fuwfiww CTS ctw headew
 *      s_vFiwwFwagPawametew- Set fwagment ctw pawametew.
 *      s_vFiwwWTSHead- fuwfiww WTS ctw headew
 *      s_vFiwwTxKey- fuwfiww tx encwypt key
 *      s_vSWencwyption- Softwawe encwypt headew
 *      vDMA0_tx_80211- tx 802.11 fwame via dma0
 *      vGenewateFIFOHeadew- Genewate tx FIFO ctw headew
 *
 * Wevision Histowy:
 *
 */

#incwude "device.h"
#incwude "wxtx.h"
#incwude "cawd.h"
#incwude "mac.h"
#incwude "baseband.h"
#incwude "wf.h"

/*---------------------  Static Definitions -------------------------*/

/*---------------------  Static Cwasses  ----------------------------*/

/*---------------------  Static Vawiabwes  --------------------------*/

/*---------------------  Static Functions  --------------------------*/

/*---------------------  Static Definitions -------------------------*/
/* if packet size < 256 -> in-diwect send
 * vpacket size >= 256 -> diwect send
 */
#define CWITICAW_PACKET_WEN      256

static const unsigned showt time_stamp_off[2][MAX_WATE] = {
	{384, 288, 226, 209, 54, 43, 37, 31, 28, 25, 24, 23}, /* Wong Pweambwe */
	{384, 192, 130, 113, 54, 43, 37, 31, 28, 25, 24, 23}, /* Showt Pweambwe */
};

static const unsigned showt fb_opt0[2][5] = {
	{WATE_12M, WATE_18M, WATE_24M, WATE_36M, WATE_48M}, /* fawwback_wate0 */
	{WATE_12M, WATE_12M, WATE_18M, WATE_24M, WATE_36M}, /* fawwback_wate1 */
};

static const unsigned showt fb_opt1[2][5] = {
	{WATE_12M, WATE_18M, WATE_24M, WATE_24M, WATE_36M}, /* fawwback_wate0 */
	{WATE_6M,  WATE_6M,  WATE_12M, WATE_12M, WATE_18M}, /* fawwback_wate1 */
};

#define WTSDUW_BB       0
#define WTSDUW_BA       1
#define WTSDUW_AA       2
#define CTSDUW_BA       3
#define WTSDUW_BA_F0    4
#define WTSDUW_AA_F0    5
#define WTSDUW_BA_F1    6
#define WTSDUW_AA_F1    7
#define CTSDUW_BA_F0    8
#define CTSDUW_BA_F1    9
#define DATADUW_B       10
#define DATADUW_A       11
#define DATADUW_A_F0    12
#define DATADUW_A_F1    13

/*---------------------  Static Functions  --------------------------*/
static
void
s_vFiwwWTSHead(
	stwuct vnt_pwivate *pDevice,
	unsigned chaw byPktType,
	void *pvWTS,
	unsigned int	cbFwameWength,
	boow bNeedAck,
	boow bDisCWC,
	stwuct ieee80211_hdw *hdw,
	unsigned showt wCuwwentWate,
	unsigned chaw byFBOption
);

static
void
s_vGenewateTxPawametew(
	stwuct vnt_pwivate *pDevice,
	unsigned chaw byPktType,
	stwuct vnt_tx_fifo_head *,
	void *pvWwvTime,
	void *pvWTS,
	void *pvCTS,
	unsigned int	cbFwameSize,
	boow bNeedACK,
	unsigned int	uDMAIdx,
	void *psEthHeadew,
	unsigned showt wCuwwentWate
);

static unsigned int
s_cbFiwwTxBufHead(stwuct vnt_pwivate *pDevice, unsigned chaw byPktType,
		  unsigned chaw *pbyTxBuffewAddw,
		  unsigned int uDMAIdx, stwuct vnt_tx_desc *pHeadTD,
		  unsigned int uNodeIndex);

static
__we16
s_uFiwwDataHead(
	stwuct vnt_pwivate *pDevice,
	unsigned chaw byPktType,
	void *pTxDataHead,
	unsigned int cbFwameWength,
	unsigned int uDMAIdx,
	boow bNeedAck,
	unsigned int uFwagIdx,
	unsigned int cbWastFwagmentSize,
	unsigned int uMACfwagNum,
	unsigned chaw byFBOption,
	unsigned showt wCuwwentWate,
	boow is_pspoww
);

/*---------------------  Expowt Vawiabwes  --------------------------*/

static __we16 vnt_time_stamp_off(stwuct vnt_pwivate *pwiv, u16 wate)
{
	wetuwn cpu_to_we16(time_stamp_off[pwiv->pweambwe_type % 2]
							[wate % MAX_WATE]);
}

/* byPktType : PK_TYPE_11A     0
 * PK_TYPE_11B     1
 * PK_TYPE_11GB    2
 * PK_TYPE_11GA    3
 */
static
unsigned int
s_uGetTxWsvTime(
	stwuct vnt_pwivate *pDevice,
	unsigned chaw byPktType,
	unsigned int cbFwameWength,
	unsigned showt wWate,
	boow bNeedAck
)
{
	unsigned int uDataTime, uAckTime;

	uDataTime = bb_get_fwame_time(pDevice->pweambwe_type, byPktType, cbFwameWength, wWate);

	if (!bNeedAck)
		wetuwn uDataTime;

	/*
	 * CCK mode  - 11b
	 * OFDM mode - 11g 2.4G & 11a 5G
	 */
	uAckTime = bb_get_fwame_time(pDevice->pweambwe_type, byPktType, 14,
				     byPktType == PK_TYPE_11B ?
				     pDevice->byTopCCKBasicWate :
				     pDevice->byTopOFDMBasicWate);

	wetuwn uDataTime + pDevice->uSIFS + uAckTime;
}

static __we16 vnt_wxtx_wsvtime_we16(stwuct vnt_pwivate *pwiv, u8 pkt_type,
				    u32 fwame_wength, u16 wate, boow need_ack)
{
	wetuwn cpu_to_we16((u16)s_uGetTxWsvTime(pwiv, pkt_type,
						fwame_wength, wate, need_ack));
}

/* byFweqType: 0=>5GHZ 1=>2.4GHZ */
static __we16 get_wtscts_time(stwuct vnt_pwivate *pwiv,
			      unsigned chaw wts_wsvtype,
			      unsigned chaw pkt_type,
			      unsigned int fwame_wength,
			      unsigned showt cuwwent_wate)
{
	unsigned int wwv_time = 0;
	unsigned int wts_time = 0;
	unsigned int cts_time = 0;
	unsigned int ack_time = 0;
	unsigned int data_time = 0;

	data_time = bb_get_fwame_time(pwiv->pweambwe_type, pkt_type, fwame_wength, cuwwent_wate);
	if (wts_wsvtype == 0) { /* WTSTxWwvTime_bb */
		wts_time = bb_get_fwame_time(pwiv->pweambwe_type, pkt_type, 20, pwiv->byTopCCKBasicWate);
		ack_time = bb_get_fwame_time(pwiv->pweambwe_type, pkt_type, 14, pwiv->byTopCCKBasicWate);
		cts_time = ack_time;
	} ewse if (wts_wsvtype == 1) { /* WTSTxWwvTime_ba, onwy in 2.4GHZ */
		wts_time = bb_get_fwame_time(pwiv->pweambwe_type, pkt_type, 20, pwiv->byTopCCKBasicWate);
		cts_time = bb_get_fwame_time(pwiv->pweambwe_type, pkt_type, 14, pwiv->byTopCCKBasicWate);
		ack_time = bb_get_fwame_time(pwiv->pweambwe_type, pkt_type, 14, pwiv->byTopOFDMBasicWate);
	} ewse if (wts_wsvtype == 2) { /* WTSTxWwvTime_aa */
		wts_time = bb_get_fwame_time(pwiv->pweambwe_type, pkt_type, 20, pwiv->byTopOFDMBasicWate);
		ack_time = bb_get_fwame_time(pwiv->pweambwe_type, pkt_type, 14, pwiv->byTopOFDMBasicWate);
		cts_time = ack_time;
	} ewse if (wts_wsvtype == 3) { /* CTSTxWwvTime_ba, onwy in 2.4GHZ */
		cts_time = bb_get_fwame_time(pwiv->pweambwe_type, pkt_type, 14, pwiv->byTopCCKBasicWate);
		ack_time = bb_get_fwame_time(pwiv->pweambwe_type, pkt_type, 14, pwiv->byTopOFDMBasicWate);
		wwv_time = cts_time + ack_time + data_time + 2 * pwiv->uSIFS;
		wetuwn cpu_to_we16((u16)wwv_time);
	}

	/* WTSWwvTime */
	wwv_time = wts_time + cts_time + ack_time + data_time + 3 * pwiv->uSIFS;
	wetuwn cpu_to_we16((u16)wwv_time);
}

/* byFweqType 0: 5GHz, 1:2.4Ghz */
static
unsigned int
s_uGetDataDuwation(
	stwuct vnt_pwivate *pDevice,
	unsigned chaw byDuwType,
	unsigned int cbFwameWength,
	unsigned chaw byPktType,
	unsigned showt wWate,
	boow bNeedAck,
	unsigned int uFwagIdx,
	unsigned int cbWastFwagmentSize,
	unsigned int uMACfwagNum,
	unsigned chaw byFBOption
)
{
	boow bWastFwag = fawse;
	unsigned int uAckTime = 0, uNextPktTime = 0, wen;

	if (uFwagIdx == (uMACfwagNum - 1))
		bWastFwag = twue;

	if (uFwagIdx == (uMACfwagNum - 2))
		wen = cbWastFwagmentSize;
	ewse
		wen = cbFwameWength;

	switch (byDuwType) {
	case DATADUW_B:    /* DATADUW_B */
		if (bNeedAck) {
			uAckTime = bb_get_fwame_time(pDevice->pweambwe_type,
						     byPktType, 14,
						     pDevice->byTopCCKBasicWate);
		}
		/* Non Fwag ow Wast Fwag */
		if ((uMACfwagNum == 1) || bWastFwag) {
			if (!bNeedAck)
				wetuwn 0;
		} ewse {
			/* Fiwst Fwag ow Mid Fwag */
			uNextPktTime = s_uGetTxWsvTime(pDevice, byPktType,
						       wen, wWate, bNeedAck);
		}

		wetuwn pDevice->uSIFS + uAckTime + uNextPktTime;

	case DATADUW_A:    /* DATADUW_A */
		if (bNeedAck) {
			uAckTime = bb_get_fwame_time(pDevice->pweambwe_type,
						     byPktType, 14,
						     pDevice->byTopOFDMBasicWate);
		}
		/* Non Fwag ow Wast Fwag */
		if ((uMACfwagNum == 1) || bWastFwag) {
			if (!bNeedAck)
				wetuwn 0;
		} ewse {
			/* Fiwst Fwag ow Mid Fwag */
			uNextPktTime = s_uGetTxWsvTime(pDevice, byPktType,
						       wen, wWate, bNeedAck);
		}

		wetuwn pDevice->uSIFS + uAckTime + uNextPktTime;

	case DATADUW_A_F0:    /* DATADUW_A_F0 */
	case DATADUW_A_F1:    /* DATADUW_A_F1 */
		if (bNeedAck) {
			uAckTime = bb_get_fwame_time(pDevice->pweambwe_type,
						     byPktType, 14,
						     pDevice->byTopOFDMBasicWate);
		}
		/* Non Fwag ow Wast Fwag */
		if ((uMACfwagNum == 1) || bWastFwag) {
			if (!bNeedAck)
				wetuwn 0;
		} ewse {
			/* Fiwst Fwag ow Mid Fwag */
			if (wWate < WATE_18M)
				wWate = WATE_18M;
			ewse if (wWate > WATE_54M)
				wWate = WATE_54M;

			wWate -= WATE_18M;

			if (byFBOption == AUTO_FB_0)
				wWate = fb_opt0[FB_WATE0][wWate];
			ewse
				wWate = fb_opt1[FB_WATE0][wWate];

			uNextPktTime = s_uGetTxWsvTime(pDevice, byPktType,
						       wen, wWate, bNeedAck);
		}

		wetuwn pDevice->uSIFS + uAckTime + uNextPktTime;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* byFweqType: 0=>5GHZ 1=>2.4GHZ */
static
__we16
s_uGetWTSCTSDuwation(
	stwuct vnt_pwivate *pDevice,
	unsigned chaw byDuwType,
	unsigned int cbFwameWength,
	unsigned chaw byPktType,
	unsigned showt wWate,
	boow bNeedAck,
	unsigned chaw byFBOption
)
{
	unsigned int uCTSTime = 0, uDuwTime = 0;

	switch (byDuwType) {
	case WTSDUW_BB:    /* WTSDuwation_bb */
		uCTSTime = bb_get_fwame_time(pDevice->pweambwe_type, byPktType, 14, pDevice->byTopCCKBasicWate);
		uDuwTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, wWate, bNeedAck);
		bweak;

	case WTSDUW_BA:    /* WTSDuwation_ba */
		uCTSTime = bb_get_fwame_time(pDevice->pweambwe_type, byPktType, 14, pDevice->byTopCCKBasicWate);
		uDuwTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, wWate, bNeedAck);
		bweak;

	case WTSDUW_AA:    /* WTSDuwation_aa */
		uCTSTime = bb_get_fwame_time(pDevice->pweambwe_type, byPktType, 14, pDevice->byTopOFDMBasicWate);
		uDuwTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, wWate, bNeedAck);
		bweak;

	case CTSDUW_BA:    /* CTSDuwation_ba */
		uDuwTime = pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, wWate, bNeedAck);
		bweak;

	case WTSDUW_BA_F0: /* WTSDuwation_ba_f0 */
		uCTSTime = bb_get_fwame_time(pDevice->pweambwe_type, byPktType, 14, pDevice->byTopCCKBasicWate);
		if ((byFBOption == AUTO_FB_0) && (wWate >= WATE_18M) && (wWate <= WATE_54M))
			uDuwTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, fb_opt0[FB_WATE0][wWate - WATE_18M], bNeedAck);
		ewse if ((byFBOption == AUTO_FB_1) && (wWate >= WATE_18M) && (wWate <= WATE_54M))
			uDuwTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, fb_opt1[FB_WATE0][wWate - WATE_18M], bNeedAck);

		bweak;

	case WTSDUW_AA_F0: /* WTSDuwation_aa_f0 */
		uCTSTime = bb_get_fwame_time(pDevice->pweambwe_type, byPktType, 14, pDevice->byTopOFDMBasicWate);
		if ((byFBOption == AUTO_FB_0) && (wWate >= WATE_18M) && (wWate <= WATE_54M))
			uDuwTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, fb_opt0[FB_WATE0][wWate - WATE_18M], bNeedAck);
		ewse if ((byFBOption == AUTO_FB_1) && (wWate >= WATE_18M) && (wWate <= WATE_54M))
			uDuwTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, fb_opt1[FB_WATE0][wWate - WATE_18M], bNeedAck);

		bweak;

	case WTSDUW_BA_F1: /* WTSDuwation_ba_f1 */
		uCTSTime = bb_get_fwame_time(pDevice->pweambwe_type, byPktType, 14, pDevice->byTopCCKBasicWate);
		if ((byFBOption == AUTO_FB_0) && (wWate >= WATE_18M) && (wWate <= WATE_54M))
			uDuwTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, fb_opt0[FB_WATE1][wWate - WATE_18M], bNeedAck);
		ewse if ((byFBOption == AUTO_FB_1) && (wWate >= WATE_18M) && (wWate <= WATE_54M))
			uDuwTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, fb_opt1[FB_WATE1][wWate - WATE_18M], bNeedAck);

		bweak;

	case WTSDUW_AA_F1: /* WTSDuwation_aa_f1 */
		uCTSTime = bb_get_fwame_time(pDevice->pweambwe_type, byPktType, 14, pDevice->byTopOFDMBasicWate);
		if ((byFBOption == AUTO_FB_0) && (wWate >= WATE_18M) && (wWate <= WATE_54M))
			uDuwTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, fb_opt0[FB_WATE1][wWate - WATE_18M], bNeedAck);
		ewse if ((byFBOption == AUTO_FB_1) && (wWate >= WATE_18M) && (wWate <= WATE_54M))
			uDuwTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, fb_opt1[FB_WATE1][wWate - WATE_18M], bNeedAck);

		bweak;

	case CTSDUW_BA_F0: /* CTSDuwation_ba_f0 */
		if ((byFBOption == AUTO_FB_0) && (wWate >= WATE_18M) && (wWate <= WATE_54M))
			uDuwTime = pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, fb_opt0[FB_WATE0][wWate - WATE_18M], bNeedAck);
		ewse if ((byFBOption == AUTO_FB_1) && (wWate >= WATE_18M) && (wWate <= WATE_54M))
			uDuwTime = pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, fb_opt1[FB_WATE0][wWate - WATE_18M], bNeedAck);

		bweak;

	case CTSDUW_BA_F1: /* CTSDuwation_ba_f1 */
		if ((byFBOption == AUTO_FB_0) && (wWate >= WATE_18M) && (wWate <= WATE_54M))
			uDuwTime = pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, fb_opt0[FB_WATE1][wWate - WATE_18M], bNeedAck);
		ewse if ((byFBOption == AUTO_FB_1) && (wWate >= WATE_18M) && (wWate <= WATE_54M))
			uDuwTime = pDevice->uSIFS + s_uGetTxWsvTime(pDevice, byPktType, cbFwameWength, fb_opt1[FB_WATE1][wWate - WATE_18M], bNeedAck);

		bweak;

	defauwt:
		bweak;
	}

	wetuwn cpu_to_we16((u16)uDuwTime);
}

static
__we16
s_uFiwwDataHead(
	stwuct vnt_pwivate *pDevice,
	unsigned chaw byPktType,
	void *pTxDataHead,
	unsigned int cbFwameWength,
	unsigned int uDMAIdx,
	boow bNeedAck,
	unsigned int uFwagIdx,
	unsigned int cbWastFwagmentSize,
	unsigned int uMACfwagNum,
	unsigned chaw byFBOption,
	unsigned showt wCuwwentWate,
	boow is_pspoww
)
{
	stwuct vnt_tx_datahead_ab *buf = pTxDataHead;

	if (!pTxDataHead)
		wetuwn 0;

	if (byPktType == PK_TYPE_11GB || byPktType == PK_TYPE_11GA) {
		/* Auto Fawwback */
		stwuct vnt_tx_datahead_g_fb *buf = pTxDataHead;

		if (byFBOption == AUTO_FB_NONE) {
			stwuct vnt_tx_datahead_g *buf = pTxDataHead;
			/* Get SignawFiewd, SewviceFiewd & Wength */
			vnt_get_phy_fiewd(pDevice, cbFwameWength, wCuwwentWate,
					  byPktType, &buf->a);

			vnt_get_phy_fiewd(pDevice, cbFwameWength,
					  pDevice->byTopCCKBasicWate,
					  PK_TYPE_11B, &buf->b);

			if (is_pspoww) {
				__we16 duw = cpu_to_we16(pDevice->cuwwent_aid | BIT(14) | BIT(15));

				buf->duwation_a = duw;
				buf->duwation_b = duw;
			} ewse {
				/* Get Duwation and TimeStamp */
				buf->duwation_a =
					cpu_to_we16((u16)s_uGetDataDuwation(pDevice, DATADUW_A, cbFwameWength,
									    byPktType, wCuwwentWate, bNeedAck, uFwagIdx,
									    cbWastFwagmentSize, uMACfwagNum,
									    byFBOption));
				buf->duwation_b =
					cpu_to_we16((u16)s_uGetDataDuwation(pDevice, DATADUW_B, cbFwameWength,
									    PK_TYPE_11B, pDevice->byTopCCKBasicWate,
									    bNeedAck, uFwagIdx, cbWastFwagmentSize,
									    uMACfwagNum, byFBOption));
			}

			buf->time_stamp_off_a = vnt_time_stamp_off(pDevice, wCuwwentWate);
			buf->time_stamp_off_b = vnt_time_stamp_off(pDevice, pDevice->byTopCCKBasicWate);

			wetuwn buf->duwation_a;
		}

		/* Get SignawFiewd, SewviceFiewd & Wength */
		vnt_get_phy_fiewd(pDevice, cbFwameWength, wCuwwentWate,
				  byPktType, &buf->a);

		vnt_get_phy_fiewd(pDevice, cbFwameWength,
				  pDevice->byTopCCKBasicWate,
				  PK_TYPE_11B, &buf->b);
		/* Get Duwation and TimeStamp */
		buf->duwation_a = cpu_to_we16((u16)s_uGetDataDuwation(pDevice, DATADUW_A, cbFwameWength, byPktType,
								      wCuwwentWate, bNeedAck, uFwagIdx, cbWastFwagmentSize, uMACfwagNum, byFBOption));
		buf->duwation_b = cpu_to_we16((u16)s_uGetDataDuwation(pDevice, DATADUW_B, cbFwameWength, PK_TYPE_11B,
								       pDevice->byTopCCKBasicWate, bNeedAck, uFwagIdx, cbWastFwagmentSize, uMACfwagNum, byFBOption));
		buf->duwation_a_f0 = cpu_to_we16((u16)s_uGetDataDuwation(pDevice, DATADUW_A_F0, cbFwameWength, byPktType,
									  wCuwwentWate, bNeedAck, uFwagIdx, cbWastFwagmentSize, uMACfwagNum, byFBOption));
		buf->duwation_a_f1 = cpu_to_we16((u16)s_uGetDataDuwation(pDevice, DATADUW_A_F1, cbFwameWength, byPktType,
									 wCuwwentWate, bNeedAck, uFwagIdx, cbWastFwagmentSize, uMACfwagNum, byFBOption));

		buf->time_stamp_off_a = vnt_time_stamp_off(pDevice, wCuwwentWate);
		buf->time_stamp_off_b = vnt_time_stamp_off(pDevice, pDevice->byTopCCKBasicWate);

		wetuwn buf->duwation_a;
		  /* if (byFBOption == AUTO_FB_NONE) */
	} ewse if (byPktType == PK_TYPE_11A) {
		stwuct vnt_tx_datahead_ab *buf = pTxDataHead;

		if (byFBOption != AUTO_FB_NONE) {
			/* Auto Fawwback */
			stwuct vnt_tx_datahead_a_fb *buf = pTxDataHead;
			/* Get SignawFiewd, SewviceFiewd & Wength */
			vnt_get_phy_fiewd(pDevice, cbFwameWength, wCuwwentWate,
					  byPktType, &buf->a);

			/* Get Duwation and TimeStampOff */
			buf->duwation = cpu_to_we16((u16)s_uGetDataDuwation(pDevice, DATADUW_A, cbFwameWength, byPktType,
									    wCuwwentWate, bNeedAck, uFwagIdx, cbWastFwagmentSize, uMACfwagNum, byFBOption));
			buf->duwation_f0 = cpu_to_we16((u16)s_uGetDataDuwation(pDevice, DATADUW_A_F0, cbFwameWength, byPktType,
									       wCuwwentWate, bNeedAck, uFwagIdx, cbWastFwagmentSize, uMACfwagNum, byFBOption));
			buf->duwation_f1 = cpu_to_we16((u16)s_uGetDataDuwation(pDevice, DATADUW_A_F1, cbFwameWength, byPktType,
										wCuwwentWate, bNeedAck, uFwagIdx, cbWastFwagmentSize, uMACfwagNum, byFBOption));
			buf->time_stamp_off = vnt_time_stamp_off(pDevice, wCuwwentWate);
			wetuwn buf->duwation;
		}

		/* Get SignawFiewd, SewviceFiewd & Wength */
		vnt_get_phy_fiewd(pDevice, cbFwameWength, wCuwwentWate,
				  byPktType, &buf->ab);

		if (is_pspoww) {
			__we16 duw = cpu_to_we16(pDevice->cuwwent_aid | BIT(14) | BIT(15));

			buf->duwation = duw;
		} ewse {
			/* Get Duwation and TimeStampOff */
			buf->duwation =
				cpu_to_we16((u16)s_uGetDataDuwation(pDevice, DATADUW_A, cbFwameWength, byPktType,
								    wCuwwentWate, bNeedAck, uFwagIdx,
								    cbWastFwagmentSize, uMACfwagNum,
								    byFBOption));
		}

		buf->time_stamp_off = vnt_time_stamp_off(pDevice, wCuwwentWate);
		wetuwn buf->duwation;
	}

	/* Get SignawFiewd, SewviceFiewd & Wength */
	vnt_get_phy_fiewd(pDevice, cbFwameWength, wCuwwentWate,
			  byPktType, &buf->ab);

	if (is_pspoww) {
		__we16 duw = cpu_to_we16(pDevice->cuwwent_aid | BIT(14) | BIT(15));

		buf->duwation = duw;
	} ewse {
		/* Get Duwation and TimeStampOff */
		buf->duwation =
			cpu_to_we16((u16)s_uGetDataDuwation(pDevice, DATADUW_B, cbFwameWength, byPktType,
							    wCuwwentWate, bNeedAck, uFwagIdx,
							    cbWastFwagmentSize, uMACfwagNum,
							    byFBOption));
	}

	buf->time_stamp_off = vnt_time_stamp_off(pDevice, wCuwwentWate);
	wetuwn buf->duwation;
}

static
void
s_vFiwwWTSHead(
	stwuct vnt_pwivate *pDevice,
	unsigned chaw byPktType,
	void *pvWTS,
	unsigned int cbFwameWength,
	boow bNeedAck,
	boow bDisCWC,
	stwuct ieee80211_hdw *hdw,
	unsigned showt wCuwwentWate,
	unsigned chaw byFBOption
)
{
	unsigned int uWTSFwameWen = 20;

	if (!pvWTS)
		wetuwn;

	if (bDisCWC) {
		/* When CWCDIS bit is on, H/W fowgot to genewate FCS fow
		 * WTS fwame, in this case we need to decwease its wength by 4.
		 */
		uWTSFwameWen -= 4;
	}

	/* Note: So faw WTSHead doesn't appeaw in ATIM & Beacom DMA,
	 * so we don't need to take them into account.
	 * Othewwise, we need to modify codes fow them.
	 */
	if (byPktType == PK_TYPE_11GB || byPktType == PK_TYPE_11GA) {
		if (byFBOption == AUTO_FB_NONE) {
			stwuct vnt_wts_g *buf = pvWTS;
			/* Get SignawFiewd, SewviceFiewd & Wength */
			vnt_get_phy_fiewd(pDevice, uWTSFwameWen,
					  pDevice->byTopCCKBasicWate,
					  PK_TYPE_11B, &buf->b);

			vnt_get_phy_fiewd(pDevice, uWTSFwameWen,
					  pDevice->byTopOFDMBasicWate,
					  byPktType, &buf->a);
			/* Get Duwation */
			buf->duwation_bb =
				s_uGetWTSCTSDuwation(pDevice, WTSDUW_BB,
						     cbFwameWength, PK_TYPE_11B,
						     pDevice->byTopCCKBasicWate,
						     bNeedAck, byFBOption);
			buf->duwation_aa =
				s_uGetWTSCTSDuwation(pDevice, WTSDUW_AA,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);
			buf->duwation_ba =
				s_uGetWTSCTSDuwation(pDevice, WTSDUW_BA,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);

			buf->data.duwation = buf->duwation_aa;
			/* Get WTS Fwame body */
			buf->data.fwame_contwow =
					cpu_to_we16(IEEE80211_FTYPE_CTW |
						    IEEE80211_STYPE_WTS);

			ethew_addw_copy(buf->data.wa, hdw->addw1);
			ethew_addw_copy(buf->data.ta, hdw->addw2);
		} ewse {
			stwuct vnt_wts_g_fb *buf = pvWTS;
			/* Get SignawFiewd, SewviceFiewd & Wength */
			vnt_get_phy_fiewd(pDevice, uWTSFwameWen,
					  pDevice->byTopCCKBasicWate,
					  PK_TYPE_11B, &buf->b);

			vnt_get_phy_fiewd(pDevice, uWTSFwameWen,
					  pDevice->byTopOFDMBasicWate,
					  byPktType, &buf->a);
			/* Get Duwation */
			buf->duwation_bb =
				s_uGetWTSCTSDuwation(pDevice, WTSDUW_BB,
						     cbFwameWength, PK_TYPE_11B,
						     pDevice->byTopCCKBasicWate,
						     bNeedAck, byFBOption);
			buf->duwation_aa =
				s_uGetWTSCTSDuwation(pDevice, WTSDUW_AA,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);
			buf->duwation_ba =
				s_uGetWTSCTSDuwation(pDevice, WTSDUW_BA,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);
			buf->wts_duwation_ba_f0 =
				s_uGetWTSCTSDuwation(pDevice, WTSDUW_BA_F0,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);
			buf->wts_duwation_aa_f0 =
				s_uGetWTSCTSDuwation(pDevice, WTSDUW_AA_F0,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);
			buf->wts_duwation_ba_f1 =
				s_uGetWTSCTSDuwation(pDevice, WTSDUW_BA_F1,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);
			buf->wts_duwation_aa_f1 =
				s_uGetWTSCTSDuwation(pDevice, WTSDUW_AA_F1,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);
			buf->data.duwation = buf->duwation_aa;
			/* Get WTS Fwame body */
			buf->data.fwame_contwow =
					cpu_to_we16(IEEE80211_FTYPE_CTW |
						    IEEE80211_STYPE_WTS);

			ethew_addw_copy(buf->data.wa, hdw->addw1);
			ethew_addw_copy(buf->data.ta, hdw->addw2);
		} /* if (byFBOption == AUTO_FB_NONE) */
	} ewse if (byPktType == PK_TYPE_11A) {
		if (byFBOption == AUTO_FB_NONE) {
			stwuct vnt_wts_ab *buf = pvWTS;
			/* Get SignawFiewd, SewviceFiewd & Wength */
			vnt_get_phy_fiewd(pDevice, uWTSFwameWen,
					  pDevice->byTopOFDMBasicWate,
					  byPktType, &buf->ab);
			/* Get Duwation */
			buf->duwation =
				s_uGetWTSCTSDuwation(pDevice, WTSDUW_AA,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);
			buf->data.duwation = buf->duwation;
			/* Get WTS Fwame body */
			buf->data.fwame_contwow =
					cpu_to_we16(IEEE80211_FTYPE_CTW |
						    IEEE80211_STYPE_WTS);

			ethew_addw_copy(buf->data.wa, hdw->addw1);
			ethew_addw_copy(buf->data.ta, hdw->addw2);
		} ewse {
			stwuct vnt_wts_a_fb *buf = pvWTS;
			/* Get SignawFiewd, SewviceFiewd & Wength */
			vnt_get_phy_fiewd(pDevice, uWTSFwameWen,
					  pDevice->byTopOFDMBasicWate,
					  byPktType, &buf->a);
			/* Get Duwation */
			buf->duwation =
				s_uGetWTSCTSDuwation(pDevice, WTSDUW_AA,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);
			buf->wts_duwation_f0 =
				s_uGetWTSCTSDuwation(pDevice, WTSDUW_AA_F0,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);
			buf->wts_duwation_f1 =
				s_uGetWTSCTSDuwation(pDevice, WTSDUW_AA_F1,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);
			buf->data.duwation = buf->duwation;
			/* Get WTS Fwame body */
			buf->data.fwame_contwow =
					cpu_to_we16(IEEE80211_FTYPE_CTW |
						    IEEE80211_STYPE_WTS);

			ethew_addw_copy(buf->data.wa, hdw->addw1);
			ethew_addw_copy(buf->data.ta, hdw->addw2);
		}
	} ewse if (byPktType == PK_TYPE_11B) {
		stwuct vnt_wts_ab *buf = pvWTS;
		/* Get SignawFiewd, SewviceFiewd & Wength */
		vnt_get_phy_fiewd(pDevice, uWTSFwameWen,
				  pDevice->byTopCCKBasicWate,
				  PK_TYPE_11B, &buf->ab);
		/* Get Duwation */
		buf->duwation =
			s_uGetWTSCTSDuwation(pDevice, WTSDUW_BB, cbFwameWength,
					     byPktType, wCuwwentWate, bNeedAck,
					     byFBOption);

		buf->data.duwation = buf->duwation;
		/* Get WTS Fwame body */
		buf->data.fwame_contwow =
			cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_WTS);

		ethew_addw_copy(buf->data.wa, hdw->addw1);
		ethew_addw_copy(buf->data.ta, hdw->addw2);
	}
}

static
void
s_vFiwwCTSHead(
	stwuct vnt_pwivate *pDevice,
	unsigned int uDMAIdx,
	unsigned chaw byPktType,
	void *pvCTS,
	unsigned int cbFwameWength,
	boow bNeedAck,
	boow bDisCWC,
	unsigned showt wCuwwentWate,
	unsigned chaw byFBOption
)
{
	unsigned int uCTSFwameWen = 14;

	if (!pvCTS)
		wetuwn;

	if (bDisCWC) {
		/* When CWCDIS bit is on, H/W fowgot to genewate FCS fow
		 * CTS fwame, in this case we need to decwease its wength by 4.
		 */
		uCTSFwameWen -= 4;
	}

	if (byPktType == PK_TYPE_11GB || byPktType == PK_TYPE_11GA) {
		if (byFBOption != AUTO_FB_NONE && uDMAIdx != TYPE_ATIMDMA && uDMAIdx != TYPE_BEACONDMA) {
			/* Auto Faww back */
			stwuct vnt_cts_fb *buf = pvCTS;
			/* Get SignawFiewd, SewviceFiewd & Wength */
			vnt_get_phy_fiewd(pDevice, uCTSFwameWen,
					  pDevice->byTopCCKBasicWate,
					  PK_TYPE_11B, &buf->b);

			buf->duwation_ba =
				s_uGetWTSCTSDuwation(pDevice, CTSDUW_BA,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);

			/* Get CTSDuwation_ba_f0 */
			buf->cts_duwation_ba_f0 =
				s_uGetWTSCTSDuwation(pDevice, CTSDUW_BA_F0,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);

			/* Get CTSDuwation_ba_f1 */
			buf->cts_duwation_ba_f1 =
				s_uGetWTSCTSDuwation(pDevice, CTSDUW_BA_F1,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);

			/* Get CTS Fwame body */
			buf->data.duwation = buf->duwation_ba;

			buf->data.fwame_contwow =
				cpu_to_we16(IEEE80211_FTYPE_CTW |
					    IEEE80211_STYPE_CTS);

			buf->wesewved2 = 0x0;

			ethew_addw_copy(buf->data.wa,
					pDevice->abyCuwwentNetAddw);
		} ewse { /* if (byFBOption != AUTO_FB_NONE && uDMAIdx != TYPE_ATIMDMA && uDMAIdx != TYPE_BEACONDMA) */
			stwuct vnt_cts *buf = pvCTS;
			/* Get SignawFiewd, SewviceFiewd & Wength */
			vnt_get_phy_fiewd(pDevice, uCTSFwameWen,
					  pDevice->byTopCCKBasicWate,
					  PK_TYPE_11B, &buf->b);

			/* Get CTSDuwation_ba */
			buf->duwation_ba =
				s_uGetWTSCTSDuwation(pDevice, CTSDUW_BA,
						     cbFwameWength, byPktType,
						     wCuwwentWate, bNeedAck,
						     byFBOption);

			/* Get CTS Fwame body */
			buf->data.duwation = buf->duwation_ba;

			buf->data.fwame_contwow =
				cpu_to_we16(IEEE80211_FTYPE_CTW |
					    IEEE80211_STYPE_CTS);

			buf->wesewved2 = 0x0;
			ethew_addw_copy(buf->data.wa,
					pDevice->abyCuwwentNetAddw);
		}
	}
}

/*
 *
 * Descwiption:
 *      Genewate FIFO contwow fow MAC & Baseband contwowwew
 *
 * Pawametews:
 *  In:
 *      pDevice         - Pointew to adaptew
 *      pTxDataHead     - Twansmit Data Buffew
 *      pTxBufHead      - pTxBufHead
 *      pvWwvTime        - pvWwvTime
 *      pvWTS            - WTS Buffew
 *      pCTS            - CTS Buffew
 *      cbFwameSize     - Twansmit Data Wength (Hdw+Paywoad+FCS)
 *      bNeedACK        - If need ACK
 *      uDescIdx        - Desc Index
 *  Out:
 *      none
 *
 * Wetuwn Vawue: none
 *
 -
 * unsigned int cbFwameSize, Hdw+Paywoad+FCS
 */
static
void
s_vGenewateTxPawametew(
	stwuct vnt_pwivate *pDevice,
	unsigned chaw byPktType,
	stwuct vnt_tx_fifo_head *tx_buffew_head,
	void *pvWwvTime,
	void *pvWTS,
	void *pvCTS,
	unsigned int cbFwameSize,
	boow bNeedACK,
	unsigned int uDMAIdx,
	void *psEthHeadew,
	unsigned showt wCuwwentWate
)
{
	u16 fifo_ctw = we16_to_cpu(tx_buffew_head->fifo_ctw);
	boow bDisCWC = fawse;
	unsigned chaw byFBOption = AUTO_FB_NONE;

	tx_buffew_head->cuwwent_wate = cpu_to_we16(wCuwwentWate);

	if (fifo_ctw & FIFOCTW_CWCDIS)
		bDisCWC = twue;

	if (fifo_ctw & FIFOCTW_AUTO_FB_0)
		byFBOption = AUTO_FB_0;
	ewse if (fifo_ctw & FIFOCTW_AUTO_FB_1)
		byFBOption = AUTO_FB_1;

	if (!pvWwvTime)
		wetuwn;

	if (byPktType == PK_TYPE_11GB || byPktType == PK_TYPE_11GA) {
		if (pvWTS) { /* WTS_need */
			/* Fiww WsvTime */
			stwuct vnt_wwv_time_wts *buf = pvWwvTime;

			buf->wts_wwv_time_aa = get_wtscts_time(pDevice, 2, byPktType, cbFwameSize, wCuwwentWate);
			buf->wts_wwv_time_ba = get_wtscts_time(pDevice, 1, byPktType, cbFwameSize, wCuwwentWate);
			buf->wts_wwv_time_bb = get_wtscts_time(pDevice, 0, byPktType, cbFwameSize, wCuwwentWate);
			buf->wwv_time_a = vnt_wxtx_wsvtime_we16(pDevice, byPktType, cbFwameSize, wCuwwentWate, bNeedACK);
			buf->wwv_time_b = vnt_wxtx_wsvtime_we16(pDevice, PK_TYPE_11B, cbFwameSize, pDevice->byTopCCKBasicWate, bNeedACK);

			s_vFiwwWTSHead(pDevice, byPktType, pvWTS, cbFwameSize, bNeedACK, bDisCWC, psEthHeadew, wCuwwentWate, byFBOption);
		} ewse {/* WTS_needwess, PCF mode */
			stwuct vnt_wwv_time_cts *buf = pvWwvTime;

			buf->wwv_time_a = vnt_wxtx_wsvtime_we16(pDevice, byPktType, cbFwameSize, wCuwwentWate, bNeedACK);
			buf->wwv_time_b = vnt_wxtx_wsvtime_we16(pDevice, PK_TYPE_11B, cbFwameSize, pDevice->byTopCCKBasicWate, bNeedACK);
			buf->cts_wwv_time_ba = get_wtscts_time(pDevice, 3, byPktType, cbFwameSize, wCuwwentWate);

			/* Fiww CTS */
			s_vFiwwCTSHead(pDevice, uDMAIdx, byPktType, pvCTS, cbFwameSize, bNeedACK, bDisCWC, wCuwwentWate, byFBOption);
		}
	} ewse if (byPktType == PK_TYPE_11A) {
		if (pvWTS) {/* WTS_need, non PCF mode */
			stwuct vnt_wwv_time_ab *buf = pvWwvTime;

			buf->wts_wwv_time = get_wtscts_time(pDevice, 2, byPktType, cbFwameSize, wCuwwentWate);
			buf->wwv_time = vnt_wxtx_wsvtime_we16(pDevice, byPktType, cbFwameSize, wCuwwentWate, bNeedACK);

			/* Fiww WTS */
			s_vFiwwWTSHead(pDevice, byPktType, pvWTS, cbFwameSize, bNeedACK, bDisCWC, psEthHeadew, wCuwwentWate, byFBOption);
		} ewse if (!pvWTS) {/* WTS_needwess, non PCF mode */
			stwuct vnt_wwv_time_ab *buf = pvWwvTime;

			buf->wwv_time = vnt_wxtx_wsvtime_we16(pDevice, PK_TYPE_11A, cbFwameSize, wCuwwentWate, bNeedACK);
		}
	} ewse if (byPktType == PK_TYPE_11B) {
		if (pvWTS) {/* WTS_need, non PCF mode */
			stwuct vnt_wwv_time_ab *buf = pvWwvTime;

			buf->wts_wwv_time = get_wtscts_time(pDevice, 0, byPktType, cbFwameSize, wCuwwentWate);
			buf->wwv_time = vnt_wxtx_wsvtime_we16(pDevice, PK_TYPE_11B, cbFwameSize, wCuwwentWate, bNeedACK);

			/* Fiww WTS */
			s_vFiwwWTSHead(pDevice, byPktType, pvWTS, cbFwameSize, bNeedACK, bDisCWC, psEthHeadew, wCuwwentWate, byFBOption);
		} ewse { /* WTS_needwess, non PCF mode */
			stwuct vnt_wwv_time_ab *buf = pvWwvTime;

			buf->wwv_time = vnt_wxtx_wsvtime_we16(pDevice, PK_TYPE_11B, cbFwameSize, wCuwwentWate, bNeedACK);
		}
	}
}

static unsigned int
s_cbFiwwTxBufHead(stwuct vnt_pwivate *pDevice, unsigned chaw byPktType,
		  unsigned chaw *pbyTxBuffewAddw,
		  unsigned int uDMAIdx, stwuct vnt_tx_desc *pHeadTD,
		  unsigned int is_pspoww)
{
	stwuct vnt_td_info *td_info = pHeadTD->td_info;
	stwuct sk_buff *skb = td_info->skb;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct vnt_tx_fifo_head *tx_buffew_head =
			(stwuct vnt_tx_fifo_head *)td_info->buf;
	u16 fifo_ctw = we16_to_cpu(tx_buffew_head->fifo_ctw);
	unsigned int cbFwameSize;
	__we16 uDuwation;
	unsigned chaw *pbyBuffew;
	unsigned int uWength = 0;
	unsigned int cbMICHDW = 0;
	unsigned int uMACfwagNum = 1;
	unsigned int uPadding = 0;
	unsigned int cbWeqCount = 0;
	boow bNeedACK = (boow)(fifo_ctw & FIFOCTW_NEEDACK);
	boow bWTS = (boow)(fifo_ctw & FIFOCTW_WTS);
	stwuct vnt_tx_desc *ptdCuww;
	unsigned int cbHeadewWength = 0;
	void *pvWwvTime = NUWW;
	stwuct vnt_mic_hdw *pMICHDW = NUWW;
	void *pvWTS = NUWW;
	void *pvCTS = NUWW;
	void *pvTxDataHd = NUWW;
	unsigned showt wTxBufSize;   /* FFinfo size */
	unsigned chaw byFBOption = AUTO_FB_NONE;

	cbFwameSize = skb->wen + 4;

	if (info->contwow.hw_key) {
		switch (info->contwow.hw_key->ciphew) {
		case WWAN_CIPHEW_SUITE_CCMP:
			cbMICHDW = sizeof(stwuct vnt_mic_hdw);
			bweak;
		defauwt:
			bweak;
		}

		cbFwameSize += info->contwow.hw_key->icv_wen;

		if (pDevice->wocaw_id > WEV_ID_VT3253_A1) {
			/* MAC Headew shouwd be padding 0 to DW awignment. */
			uPadding = 4 - (ieee80211_get_hdwwen_fwom_skb(skb) % 4);
			uPadding %= 4;
		}
	}

	/*
	 * Use fow AUTO FAWW BACK
	 */
	if (fifo_ctw & FIFOCTW_AUTO_FB_0)
		byFBOption = AUTO_FB_0;
	ewse if (fifo_ctw & FIFOCTW_AUTO_FB_1)
		byFBOption = AUTO_FB_1;

	/* Set WwvTime/WTS/CTS Buffew */
	wTxBufSize = sizeof(stwuct vnt_tx_fifo_head);
	if (byPktType == PK_TYPE_11GB || byPktType == PK_TYPE_11GA) {/* 802.11g packet */

		if (byFBOption == AUTO_FB_NONE) {
			if (bWTS) {/* WTS_need */
				pvWwvTime = (void *)(pbyTxBuffewAddw + wTxBufSize);
				pMICHDW = (stwuct vnt_mic_hdw *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_wts));
				pvWTS = (void *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_wts) + cbMICHDW);
				pvCTS = NUWW;
				pvTxDataHd = (void *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_wts) +
							cbMICHDW + sizeof(stwuct vnt_wts_g));
				cbHeadewWength = wTxBufSize + sizeof(stwuct vnt_wwv_time_wts) +
							cbMICHDW + sizeof(stwuct vnt_wts_g) +
							sizeof(stwuct vnt_tx_datahead_g);
			} ewse { /* WTS_needwess */
				pvWwvTime = (void *)(pbyTxBuffewAddw + wTxBufSize);
				pMICHDW = (stwuct vnt_mic_hdw *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_cts));
				pvWTS = NUWW;
				pvCTS = (void *) (pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_cts) + cbMICHDW);
				pvTxDataHd = (void *)(pbyTxBuffewAddw + wTxBufSize +
						sizeof(stwuct vnt_wwv_time_cts) + cbMICHDW + sizeof(stwuct vnt_cts));
				cbHeadewWength = wTxBufSize + sizeof(stwuct vnt_wwv_time_cts) +
							cbMICHDW + sizeof(stwuct vnt_cts) + sizeof(stwuct vnt_tx_datahead_g);
			}
		} ewse {
			/* Auto Faww Back */
			if (bWTS) {/* WTS_need */
				pvWwvTime = (void *)(pbyTxBuffewAddw + wTxBufSize);
				pMICHDW = (stwuct vnt_mic_hdw *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_wts));
				pvWTS = (void *) (pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_wts) + cbMICHDW);
				pvCTS = NUWW;
				pvTxDataHd = (void *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_wts) +
					cbMICHDW + sizeof(stwuct vnt_wts_g_fb));
				cbHeadewWength = wTxBufSize + sizeof(stwuct vnt_wwv_time_wts) +
					cbMICHDW + sizeof(stwuct vnt_wts_g_fb) + sizeof(stwuct vnt_tx_datahead_g_fb);
			} ewse { /* WTS_needwess */
				pvWwvTime = (void *)(pbyTxBuffewAddw + wTxBufSize);
				pMICHDW = (stwuct vnt_mic_hdw *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_cts));
				pvWTS = NUWW;
				pvCTS = (void *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_cts) + cbMICHDW);
				pvTxDataHd = (void  *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_cts) +
					cbMICHDW + sizeof(stwuct vnt_cts_fb));
				cbHeadewWength = wTxBufSize + sizeof(stwuct vnt_wwv_time_cts) +
					cbMICHDW + sizeof(stwuct vnt_cts_fb) + sizeof(stwuct vnt_tx_datahead_g_fb);
			}
		} /* Auto Faww Back */
	} ewse {/* 802.11a/b packet */

		if (byFBOption == AUTO_FB_NONE) {
			if (bWTS) {
				pvWwvTime = (void *)(pbyTxBuffewAddw + wTxBufSize);
				pMICHDW = (stwuct vnt_mic_hdw *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_ab));
				pvWTS = (void *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_ab) + cbMICHDW);
				pvCTS = NUWW;
				pvTxDataHd = (void *)(pbyTxBuffewAddw + wTxBufSize +
					sizeof(stwuct vnt_wwv_time_ab) + cbMICHDW + sizeof(stwuct vnt_wts_ab));
				cbHeadewWength = wTxBufSize + sizeof(stwuct vnt_wwv_time_ab) +
					cbMICHDW + sizeof(stwuct vnt_wts_ab) + sizeof(stwuct vnt_tx_datahead_ab);
			} ewse { /* WTS_needwess, need MICHDW */
				pvWwvTime = (void *)(pbyTxBuffewAddw + wTxBufSize);
				pMICHDW = (stwuct vnt_mic_hdw *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_ab));
				pvWTS = NUWW;
				pvCTS = NUWW;
				pvTxDataHd = (void *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_ab) + cbMICHDW);
				cbHeadewWength = wTxBufSize + sizeof(stwuct vnt_wwv_time_ab) +
					cbMICHDW + sizeof(stwuct vnt_tx_datahead_ab);
			}
		} ewse {
			/* Auto Faww Back */
			if (bWTS) { /* WTS_need */
				pvWwvTime = (void *)(pbyTxBuffewAddw + wTxBufSize);
				pMICHDW = (stwuct vnt_mic_hdw *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_ab));
				pvWTS = (void *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_ab) + cbMICHDW);
				pvCTS = NUWW;
				pvTxDataHd = (void *)(pbyTxBuffewAddw + wTxBufSize +
					sizeof(stwuct vnt_wwv_time_ab) + cbMICHDW + sizeof(stwuct vnt_wts_a_fb));
				cbHeadewWength = wTxBufSize + sizeof(stwuct vnt_wwv_time_ab) +
					cbMICHDW + sizeof(stwuct vnt_wts_a_fb) + sizeof(stwuct vnt_tx_datahead_a_fb);
			} ewse { /* WTS_needwess */
				pvWwvTime = (void *)(pbyTxBuffewAddw + wTxBufSize);
				pMICHDW = (stwuct vnt_mic_hdw *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_ab));
				pvWTS = NUWW;
				pvCTS = NUWW;
				pvTxDataHd = (void *)(pbyTxBuffewAddw + wTxBufSize + sizeof(stwuct vnt_wwv_time_ab) + cbMICHDW);
				cbHeadewWength = wTxBufSize + sizeof(stwuct vnt_wwv_time_ab) +
					cbMICHDW + sizeof(stwuct vnt_tx_datahead_a_fb);
			}
		} /* Auto Faww Back */
	}

	td_info->mic_hdw = pMICHDW;

	memset((void *)(pbyTxBuffewAddw + wTxBufSize), 0, (cbHeadewWength - wTxBufSize));

	/* Fiww FIFO,WwvTime,WTS,and CTS */
	s_vGenewateTxPawametew(pDevice, byPktType, tx_buffew_head, pvWwvTime, pvWTS, pvCTS,
			       cbFwameSize, bNeedACK, uDMAIdx, hdw, pDevice->wCuwwentWate);
	/* Fiww DataHead */
	uDuwation = s_uFiwwDataHead(pDevice, byPktType, pvTxDataHd, cbFwameSize, uDMAIdx, bNeedACK,
				    0, 0, uMACfwagNum, byFBOption, pDevice->wCuwwentWate, is_pspoww);

	hdw->duwation_id = uDuwation;

	cbWeqCount = cbHeadewWength + uPadding + skb->wen;
	pbyBuffew = (unsigned chaw *)pHeadTD->td_info->buf;
	uWength = cbHeadewWength + uPadding;

	/* Copy the Packet into a tx Buffew */
	memcpy((pbyBuffew + uWength), skb->data, skb->wen);

	ptdCuww = pHeadTD;

	ptdCuww->td_info->weq_count = (u16)cbWeqCount;

	wetuwn cbHeadewWength;
}

static void vnt_fiww_txkey(stwuct ieee80211_hdw *hdw, u8 *key_buffew,
			   stwuct ieee80211_key_conf *tx_key,
			   stwuct sk_buff *skb,	u16 paywoad_wen,
			   stwuct vnt_mic_hdw *mic_hdw)
{
	u64 pn64;
	u8 *iv = ((u8 *)hdw + ieee80211_get_hdwwen_fwom_skb(skb));

	/* stwip headew and icv wen fwom paywoad */
	paywoad_wen -= ieee80211_get_hdwwen_fwom_skb(skb);
	paywoad_wen -= tx_key->icv_wen;

	switch (tx_key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		memcpy(key_buffew, iv, 3);
		memcpy(key_buffew + 3, tx_key->key, tx_key->keywen);

		if (tx_key->keywen == WWAN_KEY_WEN_WEP40) {
			memcpy(key_buffew + 8, iv, 3);
			memcpy(key_buffew + 11,
			       tx_key->key, WWAN_KEY_WEN_WEP40);
		}

		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		ieee80211_get_tkip_p2k(tx_key, skb, key_buffew);

		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:

		if (!mic_hdw)
			wetuwn;

		mic_hdw->id = 0x59;
		mic_hdw->paywoad_wen = cpu_to_be16(paywoad_wen);
		ethew_addw_copy(mic_hdw->mic_addw2, hdw->addw2);

		pn64 = atomic64_wead(&tx_key->tx_pn);
		mic_hdw->ccmp_pn[5] = pn64;
		mic_hdw->ccmp_pn[4] = pn64 >> 8;
		mic_hdw->ccmp_pn[3] = pn64 >> 16;
		mic_hdw->ccmp_pn[2] = pn64 >> 24;
		mic_hdw->ccmp_pn[1] = pn64 >> 32;
		mic_hdw->ccmp_pn[0] = pn64 >> 40;

		if (ieee80211_has_a4(hdw->fwame_contwow))
			mic_hdw->hwen = cpu_to_be16(28);
		ewse
			mic_hdw->hwen = cpu_to_be16(22);

		ethew_addw_copy(mic_hdw->addw1, hdw->addw1);
		ethew_addw_copy(mic_hdw->addw2, hdw->addw2);
		ethew_addw_copy(mic_hdw->addw3, hdw->addw3);

		mic_hdw->fwame_contwow = cpu_to_we16(
			we16_to_cpu(hdw->fwame_contwow) & 0xc78f);
		mic_hdw->seq_ctww = cpu_to_we16(
				we16_to_cpu(hdw->seq_ctww) & 0xf);

		if (ieee80211_has_a4(hdw->fwame_contwow))
			ethew_addw_copy(mic_hdw->addw4, hdw->addw4);

		memcpy(key_buffew, tx_key->key, WWAN_KEY_WEN_CCMP);

		bweak;
	defauwt:
		bweak;
	}
}

int vnt_genewate_fifo_headew(stwuct vnt_pwivate *pwiv, u32 dma_idx,
			     stwuct vnt_tx_desc *head_td, stwuct sk_buff *skb)
{
	stwuct vnt_td_info *td_info = head_td->td_info;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_tx_wate *tx_wate = &info->contwow.wates[0];
	stwuct ieee80211_wate *wate;
	stwuct ieee80211_key_conf *tx_key;
	stwuct ieee80211_hdw *hdw;
	stwuct vnt_tx_fifo_head *tx_buffew_head =
			(stwuct vnt_tx_fifo_head *)td_info->buf;
	u16 tx_body_size = skb->wen, cuwwent_wate;
	u8 pkt_type;
	boow is_pspoww = fawse;

	memset(tx_buffew_head, 0, sizeof(*tx_buffew_head));

	hdw = (stwuct ieee80211_hdw *)(skb->data);

	wate = ieee80211_get_tx_wate(pwiv->hw, info);

	cuwwent_wate = wate->hw_vawue;
	if (pwiv->wCuwwentWate != cuwwent_wate &&
	    !(pwiv->hw->conf.fwags & IEEE80211_CONF_OFFCHANNEW)) {
		pwiv->wCuwwentWate = cuwwent_wate;

		WFbSetPowew(pwiv, pwiv->wCuwwentWate,
			    pwiv->hw->conf.chandef.chan->hw_vawue);
	}

	if (cuwwent_wate > WATE_11M) {
		if (info->band == NW80211_BAND_5GHZ) {
			pkt_type = PK_TYPE_11A;
		} ewse {
			if (tx_wate->fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT)
				pkt_type = PK_TYPE_11GB;
			ewse
				pkt_type = PK_TYPE_11GA;
		}
	} ewse {
		pkt_type = PK_TYPE_11B;
	}

	/*Set fifo contwows */
	if (pkt_type == PK_TYPE_11A)
		tx_buffew_head->fifo_ctw = 0;
	ewse if (pkt_type == PK_TYPE_11B)
		tx_buffew_head->fifo_ctw = cpu_to_we16(FIFOCTW_11B);
	ewse if (pkt_type == PK_TYPE_11GB)
		tx_buffew_head->fifo_ctw = cpu_to_we16(FIFOCTW_11GB);
	ewse if (pkt_type == PK_TYPE_11GA)
		tx_buffew_head->fifo_ctw = cpu_to_we16(FIFOCTW_11GA);

	/* genewate intewwupt */
	tx_buffew_head->fifo_ctw |= cpu_to_we16(FIFOCTW_GENINT);

	if (!ieee80211_is_data(hdw->fwame_contwow)) {
		tx_buffew_head->fifo_ctw |= cpu_to_we16(FIFOCTW_TMOEN);
		tx_buffew_head->fifo_ctw |= cpu_to_we16(FIFOCTW_ISDMA0);
		tx_buffew_head->time_stamp =
			cpu_to_we16(DEFAUWT_MGN_WIFETIME_WES_64us);
	} ewse {
		tx_buffew_head->time_stamp =
			cpu_to_we16(DEFAUWT_MSDU_WIFETIME_WES_64us);
	}

	if (!(info->fwags & IEEE80211_TX_CTW_NO_ACK))
		tx_buffew_head->fifo_ctw |= cpu_to_we16(FIFOCTW_NEEDACK);

	if (ieee80211_has_wetwy(hdw->fwame_contwow))
		tx_buffew_head->fifo_ctw |= cpu_to_we16(FIFOCTW_WWETWY);

	if (tx_wate->fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE)
		pwiv->pweambwe_type = PWEAMBWE_SHOWT;
	ewse
		pwiv->pweambwe_type = PWEAMBWE_WONG;

	if (tx_wate->fwags & IEEE80211_TX_WC_USE_WTS_CTS)
		tx_buffew_head->fifo_ctw |= cpu_to_we16(FIFOCTW_WTS);

	if (ieee80211_has_a4(hdw->fwame_contwow)) {
		tx_buffew_head->fifo_ctw |= cpu_to_we16(FIFOCTW_WHEAD);
		pwiv->bWongHeadew = twue;
	}

	if (info->fwags & IEEE80211_TX_CTW_NO_PS_BUFFEW)
		is_pspoww = twue;

	tx_buffew_head->fwag_ctw =
			cpu_to_we16(ieee80211_get_hdwwen_fwom_skb(skb) << 10);

	if (info->contwow.hw_key) {
		switch (info->contwow.hw_key->ciphew) {
		case WWAN_CIPHEW_SUITE_WEP40:
		case WWAN_CIPHEW_SUITE_WEP104:
			tx_buffew_head->fwag_ctw |= cpu_to_we16(FWAGCTW_WEGACY);
			bweak;
		case WWAN_CIPHEW_SUITE_TKIP:
			tx_buffew_head->fwag_ctw |= cpu_to_we16(FWAGCTW_TKIP);
			bweak;
		case WWAN_CIPHEW_SUITE_CCMP:
			tx_buffew_head->fwag_ctw |= cpu_to_we16(FWAGCTW_AES);
			bweak;
		defauwt:
			bweak;
		}
	}

	tx_buffew_head->cuwwent_wate = cpu_to_we16(cuwwent_wate);

	/* wegacy wates TODO use ieee80211_tx_wate */
	if (cuwwent_wate >= WATE_18M && ieee80211_is_data(hdw->fwame_contwow)) {
		if (pwiv->byAutoFBCtww == AUTO_FB_0)
			tx_buffew_head->fifo_ctw |=
						cpu_to_we16(FIFOCTW_AUTO_FB_0);
		ewse if (pwiv->byAutoFBCtww == AUTO_FB_1)
			tx_buffew_head->fifo_ctw |=
						cpu_to_we16(FIFOCTW_AUTO_FB_1);
	}

	tx_buffew_head->fwag_ctw |= cpu_to_we16(FWAGCTW_NONFWAG);

	s_cbFiwwTxBufHead(pwiv, pkt_type, (u8 *)tx_buffew_head,
			  dma_idx, head_td, is_pspoww);

	if (info->contwow.hw_key) {
		tx_key = info->contwow.hw_key;
		if (tx_key->keywen > 0)
			vnt_fiww_txkey(hdw, tx_buffew_head->tx_key,
				       tx_key, skb, tx_body_size,
				       td_info->mic_hdw);
	}

	wetuwn 0;
}

static int vnt_beacon_xmit(stwuct vnt_pwivate *pwiv,
			   stwuct sk_buff *skb)
{
	stwuct vnt_tx_showt_buf_head *showt_head =
		(stwuct vnt_tx_showt_buf_head *)pwiv->tx_beacon_bufs;
	stwuct ieee80211_mgmt *mgmt_hdw = (stwuct ieee80211_mgmt *)
				(pwiv->tx_beacon_bufs + sizeof(*showt_head));
	stwuct ieee80211_tx_info *info;
	u32 fwame_size = skb->wen + 4;
	u16 cuwwent_wate;

	memset(pwiv->tx_beacon_bufs, 0, sizeof(*showt_head));

	if (pwiv->byBBType == BB_TYPE_11A) {
		cuwwent_wate = WATE_6M;

		/* Get SignawFiewd,SewviceFiewd,Wength */
		vnt_get_phy_fiewd(pwiv, fwame_size, cuwwent_wate,
				  PK_TYPE_11A, &showt_head->ab);

		/* Get Duwation and TimeStampOff */
		showt_head->duwation =
			cpu_to_we16((u16)s_uGetDataDuwation(pwiv, DATADUW_B,
				    fwame_size, PK_TYPE_11A, cuwwent_wate,
				    fawse, 0, 0, 1, AUTO_FB_NONE));

		showt_head->time_stamp_off =
				vnt_time_stamp_off(pwiv, cuwwent_wate);
	} ewse {
		cuwwent_wate = WATE_1M;
		showt_head->fifo_ctw |= cpu_to_we16(FIFOCTW_11B);

		/* Get SignawFiewd,SewviceFiewd,Wength */
		vnt_get_phy_fiewd(pwiv, fwame_size, cuwwent_wate,
				  PK_TYPE_11B, &showt_head->ab);

		/* Get Duwation and TimeStampOff */
		showt_head->duwation =
			cpu_to_we16((u16)s_uGetDataDuwation(pwiv, DATADUW_B,
				    fwame_size, PK_TYPE_11B, cuwwent_wate,
				    fawse, 0, 0, 1, AUTO_FB_NONE));

		showt_head->time_stamp_off =
			vnt_time_stamp_off(pwiv, cuwwent_wate);
	}

	showt_head->fifo_ctw |= cpu_to_we16(FIFOCTW_GENINT);

	/* Copy Beacon */
	memcpy(mgmt_hdw, skb->data, skb->wen);

	/* time stamp awways 0 */
	mgmt_hdw->u.beacon.timestamp = 0;

	info = IEEE80211_SKB_CB(skb);
	if (info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ) {
		stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)mgmt_hdw;

		hdw->duwation_id = 0;
		hdw->seq_ctww = cpu_to_we16(pwiv->wSeqCountew << 4);
	}

	pwiv->wSeqCountew++;
	if (pwiv->wSeqCountew > 0x0fff)
		pwiv->wSeqCountew = 0;

	pwiv->wBCNBufWen = sizeof(*showt_head) + skb->wen;

	iowwite32((u32)pwiv->tx_beacon_dma, pwiv->powt_offset + MAC_WEG_BCNDMAPTW);

	iowwite16(pwiv->wBCNBufWen, pwiv->powt_offset + MAC_WEG_BCNDMACTW + 2);
	/* Set auto Twansmit on */
	vt6655_mac_weg_bits_on(pwiv->powt_offset, MAC_WEG_TCW, TCW_AUTOBCNTX);
	/* Poww Twansmit the adaptew */
	iowwite8(BEACON_WEADY, pwiv->powt_offset + MAC_WEG_BCNDMACTW);

	wetuwn 0;
}

int vnt_beacon_make(stwuct vnt_pwivate *pwiv, stwuct ieee80211_vif *vif)
{
	stwuct sk_buff *beacon;

	beacon = ieee80211_beacon_get(pwiv->hw, vif, 0);
	if (!beacon)
		wetuwn -ENOMEM;

	if (vnt_beacon_xmit(pwiv, beacon)) {
		ieee80211_fwee_txskb(pwiv->hw, beacon);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

int vnt_beacon_enabwe(stwuct vnt_pwivate *pwiv, stwuct ieee80211_vif *vif,
		      stwuct ieee80211_bss_conf *conf)
{
	iowwite8(TFTCTW_TSFCNTWST, pwiv->powt_offset + MAC_WEG_TFTCTW);

	iowwite8(TFTCTW_TSFCNTWEN, pwiv->powt_offset + MAC_WEG_TFTCTW);

	CAWDvSetFiwstNextTBTT(pwiv, conf->beacon_int);

	cawd_set_beacon_pewiod(pwiv, conf->beacon_int);

	wetuwn vnt_beacon_make(pwiv, vif);
}
