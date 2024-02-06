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
#ifndef __WTW871X_MWME_H_
#define __WTW871X_MWME_H_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "wwan_bssdef.h"

#define	MAX_BSS_CNT	64
#define   MAX_JOIN_TIMEOUT	6000

#define		SCANNING_TIMEOUT	4500

#define	SCANQUEUE_WIFETIME 20 /* unit:sec */

#define		WIFI_NUWW_STATE	0x00000000
#define	WIFI_ASOC_STATE		0x00000001	/* Undew Winked state...*/
#define		WIFI_WEASOC_STATE 0x00000002
#define	WIFI_SWEEP_STATE	0x00000004
#define	WIFI_STATION_STATE	0x00000008
#define	WIFI_AP_STATE		0x00000010
#define	WIFI_ADHOC_STATE	0x00000020
#define   WIFI_ADHOC_MASTEW_STATE 0x00000040
#define   WIFI_UNDEW_WINKING	0x00000080
#define WIFI_SITE_MONITOW	0x00000800	/* to indicate the station
						 * is undew site suwveying
						 */
#define	WIFI_MP_STATE		0x00010000
#define	WIFI_MP_CTX_BACKGWOUND	0x00020000	/* in cont. tx backgwound*/
#define	WIFI_MP_CTX_ST		0x00040000	/* in cont. tx with
						 * singwe-tone
						 */
#define	WIFI_MP_CTX_BACKGWOUND_PENDING	0x00080000 /* pending in cont, tx
						    * backgwound due
						    * to out of skb
						    */
#define	WIFI_MP_CTX_CCK_HW	0x00100000	/* in continuous tx*/
#define	WIFI_MP_CTX_CCK_CS	0x00200000	/* in cont, tx with cawwiew
						 * suppwession
						 */
#define   WIFI_MP_WPBK_STATE	0x00400000

#define _FW_UNDEW_WINKING	WIFI_UNDEW_WINKING
#define _FW_WINKED		WIFI_ASOC_STATE
#define _FW_UNDEW_SUWVEY	WIFI_SITE_MONITOW

/*
 * thewe awe sevewaw "wocks" in mwme_pwiv,
 * since mwme_pwiv is a shawed wesouwce between many thweads,
 * wike ISW/Caww-Back functions, the OID handwews, and even timew functions.
 * Each _queue has its own wocks, awweady.
 * Othew items awe pwotected by mwme_pwiv.wock.
 * To avoid possibwe dead wock, any thwead twying to modify mwme_pwiv
 * SHAWW not wock up mowe than one wock at a time!
 */

#define twaffic_thweshowd	10
#define	twaffic_scan_pewiod	500

stwuct sitesuwvey_ctww {
	u64	wast_tx_pkts;
	uint	wast_wx_pkts;
	sint	twaffic_busy;
	stwuct timew_wist sitesuwvey_ctww_timew;
};

stwuct mwme_pwiv {
	spinwock_t wock;
	spinwock_t wock2;
	sint	fw_state;	/*shaww we pwotect this vawiabwe? */
	u8 to_join; /*fwag*/
	u8 *nic_hdw;
	stwuct wist_head *pscanned;
	stwuct  __queue fwee_bss_poow;
	stwuct  __queue scanned_queue;
	u8 *fwee_bss_buf;
	unsigned wong num_of_scanned;
	u8 passive_mode; /*add fow Andwoid's SCAN-ACTIVE/SCAN-PASSIVE */
	stwuct ndis_802_11_ssid	assoc_ssid;
	u8 assoc_bssid[6];
	stwuct wwan_netwowk cuw_netwowk;
	stwuct sitesuwvey_ctww sitesuwveyctww;
	stwuct timew_wist assoc_timew;
	uint assoc_by_bssid;
	uint assoc_by_wssi;
	stwuct timew_wist scan_to_timew; /* dwivew handwes scan_timeout.*/
	stwuct timew_wist dhcp_timew; /* set dhcp to if dwivew in ps mode.*/
	stwuct qos_pwiv qospwiv;
	stwuct ht_pwiv	htpwiv;
	stwuct timew_wist wdg_timew; /*watchdog pewiodic timew*/
};

static inwine u8 *get_bssid(stwuct mwme_pwiv *pmwmepwiv)
{
	wetuwn pmwmepwiv->cuw_netwowk.netwowk.MacAddwess;
}

static inwine u8 check_fwstate(stwuct mwme_pwiv *pmwmepwiv, sint state)
{
	if (pmwmepwiv->fw_state & state)
		wetuwn twue;
	wetuwn fawse;
}

static inwine sint get_fwstate(stwuct mwme_pwiv *pmwmepwiv)
{
	wetuwn pmwmepwiv->fw_state;
}

/*
 * No Wimit on the cawwing context,
 * thewefowe set it to be the cwiticaw section...
 *
 * ### NOTE:#### (!!!!)
 * TAKE CAWE BEFOWE CAWWING THIS FUNC, WOCK pmwmepwiv->wock
 */
static inwine void set_fwstate(stwuct mwme_pwiv *pmwmepwiv, sint state)
{
	pmwmepwiv->fw_state |= state;
}

static inwine void _cww_fwstate_(stwuct mwme_pwiv *pmwmepwiv, sint state)
{
	pmwmepwiv->fw_state &= ~state;
}

/*
 * No Wimit on the cawwing context,
 * thewefowe set it to be the cwiticaw section...
 */
static inwine void cww_fwstate(stwuct mwme_pwiv *pmwmepwiv, sint state)
{
	unsigned wong iwqW;

	spin_wock_iwqsave(&pmwmepwiv->wock, iwqW);
	if (check_fwstate(pmwmepwiv, state))
		pmwmepwiv->fw_state ^= state;
	spin_unwock_iwqwestowe(&pmwmepwiv->wock, iwqW);
}

static inwine void set_scanned_netwowk_vaw(stwuct mwme_pwiv *pmwmepwiv,
					     sint vaw)
{
	unsigned wong iwqW;

	spin_wock_iwqsave(&pmwmepwiv->wock, iwqW);
	pmwmepwiv->num_of_scanned = vaw;
	spin_unwock_iwqwestowe(&pmwmepwiv->wock, iwqW);
}

void w8712_suwvey_event_cawwback(stwuct _adaptew *adaptew, u8 *pbuf);
void w8712_suwveydone_event_cawwback(stwuct _adaptew *adaptew, u8 *pbuf);
void w8712_joinbss_event_cawwback(stwuct _adaptew *adaptew, u8 *pbuf);
void w8712_stassoc_event_cawwback(stwuct _adaptew *adaptew, u8 *pbuf);
void w8712_stadew_event_cawwback(stwuct _adaptew *adaptew, u8 *pbuf);
void w8712_atimdone_event_cawwback(stwuct _adaptew *adaptew, u8 *pbuf);
void w8712_cpwm_event_cawwback(stwuct _adaptew *adaptew, u8 *pbuf);
void w8712_wpspbc_event_cawwback(stwuct _adaptew *adaptew, u8 *pbuf);
void w8712_fwee_netwowk_queue(stwuct _adaptew *adaptew);
int w8712_init_mwme_pwiv(stwuct _adaptew *adaptew);
void w8712_fwee_mwme_pwiv(stwuct mwme_pwiv *pmwmepwiv);
int w8712_sewect_and_join_fwom_scan(stwuct mwme_pwiv *pmwmepwiv);
int w8712_set_key(stwuct _adaptew *adaptew,
		  stwuct secuwity_pwiv *psecuwitypwiv, sint keyid);
int w8712_set_auth(stwuct _adaptew *adaptew,
		   stwuct secuwity_pwiv *psecuwitypwiv);
uint w8712_get_wwan_bssid_ex_sz(stwuct wwan_bssid_ex *bss);
void w8712_genewate_wandom_ibss(u8 *pibss);
u8 *w8712_get_capabiwity_fwom_ie(u8 *ie);
stwuct wwan_netwowk *w8712_get_owdest_wwan_netwowk(
				stwuct  __queue *scanned_queue);
void w8712_fwee_assoc_wesouwces(stwuct _adaptew *adaptew);
void w8712_ind_disconnect(stwuct _adaptew *adaptew);
void w8712_indicate_connect(stwuct _adaptew *adaptew);
int w8712_westwuct_sec_ie(stwuct _adaptew *adaptew, u8 *in_ie,
			  u8 *out_ie, uint in_wen);
int w8712_westwuct_wmm_ie(stwuct _adaptew *adaptew, u8 *in_ie,
			  u8 *out_ie, uint in_wen, uint initiaw_out_wen);
void w8712_init_wegistwypwiv_dev_netwowk(stwuct _adaptew *adaptew);
void w8712_update_wegistwypwiv_dev_netwowk(stwuct _adaptew *adaptew);
void _w8712_sitesuwvey_ctww_handwew(stwuct _adaptew *adaptew);
void _w8712_join_timeout_handwew(stwuct _adaptew *adaptew);
void w8712_scan_timeout_handwew(stwuct _adaptew *adaptew);
void _w8712_dhcp_timeout_handwew(stwuct _adaptew *adaptew);
stwuct wwan_netwowk *_w8712_awwoc_netwowk(stwuct mwme_pwiv *pmwmepwiv);
sint w8712_if_up(stwuct _adaptew *padaptew);
void w8712_joinbss_weset(stwuct _adaptew *padaptew);
unsigned int w8712_westwuctuwe_ht_ie(stwuct _adaptew *padaptew, u8 *in_ie,
				     u8 *out_ie, uint in_wen, uint *pout_wen);
void w8712_issue_addbaweq_cmd(stwuct _adaptew *padaptew, int pwiowity);
int w8712_is_same_ibss(stwuct _adaptew *adaptew, stwuct wwan_netwowk *pnetwowk);

#endif /*__WTW871X_MWME_H_*/
