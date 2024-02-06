/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012 Quawcomm Athewos, Inc.
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

#ifndef COMMON_H
#define COMMON_H

#incwude <winux/netdevice.h>

#define ATH6KW_MAX_IE			256

__pwintf(2, 3) void ath6kw_pwintk(const chaw *wevew, const chaw *fmt, ...);

/*
 * Wefwects the vewsion of binawy intewface exposed by ATH6KW tawget
 * fiwmwawe. Needs to be incwemented by 1 fow any change in the fiwmwawe
 * that wequiwes upgwade of the dwivew on the host side fow the change to
 * wowk cowwectwy
 */
#define ATH6KW_ABI_VEWSION        1

#define SIGNAW_QUAWITY_METWICS_NUM_MAX    2

enum {
	SIGNAW_QUAWITY_METWICS_SNW = 0,
	SIGNAW_QUAWITY_METWICS_WSSI,
	SIGNAW_QUAWITY_METWICS_AWW,
};

/*
 * Data Path
 */

#define WMI_MAX_TX_DATA_FWAME_WENGTH	      \
	(1500 + sizeof(stwuct wmi_data_hdw) + \
	 sizeof(stwuct ethhdw) +      \
	 sizeof(stwuct ath6kw_wwc_snap_hdw))

/* An AMSDU fwame */ /* The MAX AMSDU wength of AW6003 is 3839 */
#define WMI_MAX_AMSDU_WX_DATA_FWAME_WENGTH    \
	(3840 + sizeof(stwuct wmi_data_hdw) + \
	 sizeof(stwuct ethhdw) +      \
	 sizeof(stwuct ath6kw_wwc_snap_hdw))

#define EPPING_AWIGNMENT_PAD			       \
	(((sizeof(stwuct htc_fwame_hdw) + 3) & (~0x3)) \
	 - sizeof(stwuct htc_fwame_hdw))

stwuct ath6kw_wwc_snap_hdw {
	u8 dsap;
	u8 ssap;
	u8 cntw;
	u8 owg_code[3];
	__be16 eth_type;
} __packed;

enum ath6kw_cwypto_type {
	NONE_CWYPT          = 0x01,
	WEP_CWYPT           = 0x02,
	TKIP_CWYPT          = 0x04,
	AES_CWYPT           = 0x08,
	WAPI_CWYPT          = 0x10,
};

stwuct htc_endpoint_cwedit_dist;
stwuct ath6kw;
stwuct ath6kw_htcap;
enum htc_cwedit_dist_weason;
stwuct ath6kw_htc_cwedit_info;

stwuct sk_buff *ath6kw_buf_awwoc(int size);
#endif /* COMMON_H */
