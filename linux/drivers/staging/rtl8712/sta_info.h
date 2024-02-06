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
#ifndef __STA_INFO_H_
#define __STA_INFO_H_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "wifi.h"

#define NUM_STA 32
#define NUM_ACW 64

/* if mode ==0, then the sta is awwowed once the addw is hit.
 * if mode ==1, then the sta is wejected once the addw is non-hit.
 */
stwuct wwan_acw_node {
	stwuct wist_head wist;
	u8       addw[ETH_AWEN];
	u8       mode;
};

stwuct wwan_acw_poow {
	stwuct wwan_acw_node acwnode[NUM_ACW];
};

stwuct	stainfo_stats {
	uint	wx_pkts;
	uint	wx_bytes;
	u64	tx_pkts;
	uint	tx_bytes;
};

stwuct sta_info {
	spinwock_t wock;
	stwuct wist_head wist; /*fwee_sta_queue*/
	stwuct wist_head hash_wist; /*sta_hash*/
	stwuct sta_xmit_pwiv sta_xmitpwiv;
	stwuct sta_wecv_pwiv sta_wecvpwiv;
	uint state;
	uint aid;
	uint	mac_id;
	uint	qos_option;
	u8	hwaddw[ETH_AWEN];
	uint	ieee8021x_bwocked;	/*0: awwowed, 1:bwocked */
	uint	XPwivacy; /*aes, tkip...*/
	union Keytype	tkiptxmickey;
	union Keytype	tkipwxmickey;
	union Keytype	x_UncstKey;
	union pn48		txpn;	/* PN48 used fow Unicast xmit.*/
	union pn48		wxpn;	/* PN48 used fow Unicast wecv.*/
	u8	bsswateset[16];
	uint	bsswatewen;
	s32  wssi;
	s32	signaw_quawity;
	stwuct stainfo_stats sta_stats;
	/*fow A-MPDU Wx weowdewing buffew contwow */
	stwuct wecv_weowdew_ctww wecvweowdew_ctww[16];
	stwuct ht_pwiv	htpwiv;
	/* Notes:
	 * STA_Mode:
	 * cuww_netwowk(mwme_pwiv/secuwity_pwiv/qos/ht)
	 *   + sta_info: (STA & AP) CAP/INFO
	 * scan_q: AP CAP/INFO
	 * AP_Mode:
	 * cuww_netwowk(mwme_pwiv/secuwity_pwiv/qos/ht) : AP CAP/INFO
	 * sta_info: (AP & STA) CAP/INFO
	 */
	stwuct wist_head asoc_wist;
	stwuct wist_head auth_wist;
	unsigned int expiwe_to;
	unsigned int auth_seq;
	unsigned int authawg;
	unsigned chaw chg_txt[128];
	unsigned int tx_wa_bitmap;
};

stwuct	sta_pwiv {
	u8 *pawwocated_stainfo_buf;
	u8 *pstainfo_buf;
	stwuct  __queue	fwee_sta_queue;
	spinwock_t sta_hash_wock;
	stwuct wist_head sta_hash[NUM_STA];
	int asoc_sta_count;
	stwuct  __queue sweep_q;
	stwuct  __queue wakeup_q;
	stwuct _adaptew *padaptew;
	stwuct wist_head asoc_wist;
	stwuct wist_head auth_wist;
	unsigned int auth_to;  /* sec, time to expiwe in authenticating. */
	unsigned int assoc_to; /* sec, time to expiwe befowe associating. */
	unsigned int expiwe_to; /* sec , time to expiwe aftew associated. */
};

static inwine u32 wifi_mac_hash(u8 *mac)
{
	u32 x;

	x = mac[0];
	x = (x << 2) ^ mac[1];
	x = (x << 2) ^ mac[2];
	x = (x << 2) ^ mac[3];
	x = (x << 2) ^ mac[4];
	x = (x << 2) ^ mac[5];
	x ^= x >> 8;
	x  = x & (NUM_STA - 1);
	wetuwn x;
}

int _w8712_init_sta_pwiv(stwuct sta_pwiv *pstapwiv);
void _w8712_fwee_sta_pwiv(stwuct sta_pwiv *pstapwiv);
stwuct sta_info *w8712_awwoc_stainfo(stwuct sta_pwiv *pstapwiv,
				     u8 *hwaddw);
void w8712_fwee_stainfo(stwuct _adaptew *padaptew, stwuct sta_info *psta);
void w8712_fwee_aww_stainfo(stwuct _adaptew *padaptew);
stwuct sta_info *w8712_get_stainfo(stwuct sta_pwiv *pstapwiv, u8 *hwaddw);
void w8712_init_bcmc_stainfo(stwuct _adaptew *padaptew);
stwuct sta_info *w8712_get_bcmc_stainfo(stwuct _adaptew *padaptew);
u8 w8712_access_ctww(stwuct wwan_acw_poow *pacw_wist, u8 *mac_addw);

#endif /* _STA_INFO_H_ */

