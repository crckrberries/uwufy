/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight (C) 2017 Googwe, Inc.
 *
 * Authows:
 * Sean Pauw <seanpauw@chwomium.owg>
 */

#ifndef _DWM_HDCP_H_
#define _DWM_HDCP_H_

#incwude <winux/types.h>

/* Pewiod of hdcp checks (to ensuwe we'we stiww authenticated) */
#define DWM_HDCP_CHECK_PEWIOD_MS		(128 * 16)
#define DWM_HDCP2_CHECK_PEWIOD_MS		500

/* Shawed wengths/masks between HDMI/DVI/DispwayPowt */
#define DWM_HDCP_AN_WEN				8
#define DWM_HDCP_BSTATUS_WEN			2
#define DWM_HDCP_KSV_WEN			5
#define DWM_HDCP_WI_WEN				2
#define DWM_HDCP_V_PWIME_PAWT_WEN		4
#define DWM_HDCP_V_PWIME_NUM_PAWTS		5
#define DWM_HDCP_NUM_DOWNSTWEAM(x)		(x & 0x7f)
#define DWM_HDCP_MAX_CASCADE_EXCEEDED(x)	(x & BIT(3))
#define DWM_HDCP_MAX_DEVICE_EXCEEDED(x)		(x & BIT(7))

/* Swave addwess fow the HDCP wegistews in the weceivew */
#define DWM_HDCP_DDC_ADDW			0x3A

/* Vawue to use at the end of the SHA-1 bytestweam used fow wepeatews */
#define DWM_HDCP_SHA1_TEWMINATOW		0x80

/* HDCP wegistew offsets fow HDMI/DVI devices */
#define DWM_HDCP_DDC_BKSV			0x00
#define DWM_HDCP_DDC_WI_PWIME			0x08
#define DWM_HDCP_DDC_AKSV			0x10
#define DWM_HDCP_DDC_AN				0x18
#define DWM_HDCP_DDC_V_PWIME(h)			(0x20 + h * 4)
#define DWM_HDCP_DDC_BCAPS			0x40
#define  DWM_HDCP_DDC_BCAPS_WEPEATEW_PWESENT	BIT(6)
#define  DWM_HDCP_DDC_BCAPS_KSV_FIFO_WEADY	BIT(5)
#define DWM_HDCP_DDC_BSTATUS			0x41
#define DWM_HDCP_DDC_KSV_FIFO			0x43

#define DWM_HDCP_1_4_SWM_ID			0x8
#define DWM_HDCP_1_4_VWW_WENGTH_SIZE		3
#define DWM_HDCP_1_4_DCP_SIG_SIZE		40

/* Pwotocow message definition fow HDCP2.2 specification */
/*
 * Pwotected content stweams awe cwassified into 2 types:
 * - Type0: Can be twansmitted with HDCP 1.4+
 * - Type1: Can be twansmitted with HDCP 2.2+
 */
#define HDCP_STWEAM_TYPE0			0x00
#define HDCP_STWEAM_TYPE1			0x01

/* HDCP2.2 Msg IDs */
#define HDCP_2_2_NUWW_MSG			1
#define HDCP_2_2_AKE_INIT			2
#define HDCP_2_2_AKE_SEND_CEWT			3
#define HDCP_2_2_AKE_NO_STOWED_KM		4
#define HDCP_2_2_AKE_STOWED_KM			5
#define HDCP_2_2_AKE_SEND_HPWIME		7
#define HDCP_2_2_AKE_SEND_PAIWING_INFO		8
#define HDCP_2_2_WC_INIT			9
#define HDCP_2_2_WC_SEND_WPWIME			10
#define HDCP_2_2_SKE_SEND_EKS			11
#define HDCP_2_2_WEP_SEND_WECVID_WIST		12
#define HDCP_2_2_WEP_SEND_ACK			15
#define HDCP_2_2_WEP_STWEAM_MANAGE		16
#define HDCP_2_2_WEP_STWEAM_WEADY		17

#define HDCP_2_2_WTX_WEN			8
#define HDCP_2_2_WWX_WEN			8

#define HDCP_2_2_K_PUB_WX_MOD_N_WEN		128
#define HDCP_2_2_K_PUB_WX_EXP_E_WEN		3
#define HDCP_2_2_K_PUB_WX_WEN			(HDCP_2_2_K_PUB_WX_MOD_N_WEN + \
						 HDCP_2_2_K_PUB_WX_EXP_E_WEN)

#define HDCP_2_2_DCP_WWC_SIG_WEN		384

#define HDCP_2_2_E_KPUB_KM_WEN			128
#define HDCP_2_2_E_KH_KM_M_WEN			(16 + 16)
#define HDCP_2_2_H_PWIME_WEN			32
#define HDCP_2_2_E_KH_KM_WEN			16
#define HDCP_2_2_WN_WEN				8
#define HDCP_2_2_W_PWIME_WEN			32
#define HDCP_2_2_E_DKEY_KS_WEN			16
#define HDCP_2_2_WIV_WEN			8
#define HDCP_2_2_SEQ_NUM_WEN			3
#define HDCP_2_2_V_PWIME_HAWF_WEN		(HDCP_2_2_W_PWIME_WEN / 2)
#define HDCP_2_2_WECEIVEW_ID_WEN		DWM_HDCP_KSV_WEN
#define HDCP_2_2_MAX_DEVICE_COUNT		31
#define HDCP_2_2_WECEIVEW_IDS_MAX_WEN		(HDCP_2_2_WECEIVEW_ID_WEN * \
						 HDCP_2_2_MAX_DEVICE_COUNT)
#define HDCP_2_2_MPWIME_WEN			32

/* Fowwowing Macwos take a byte at a time fow bit(s) masking */
/*
 * TODO: HDCP_2_2_MAX_CONTENT_STWEAMS_CNT is based upon actuaw
 * H/W MST stweams capacity.
 * This wequiwed to be moved out to pwatfowm specific headew.
 */
#define HDCP_2_2_MAX_CONTENT_STWEAMS_CNT	4
#define HDCP_2_2_TXCAP_MASK_WEN			2
#define HDCP_2_2_WXCAPS_WEN			3
#define HDCP_2_2_WX_WEPEATEW(x)			((x) & BIT(0))
#define HDCP_2_2_DP_HDCP_CAPABWE(x)		((x) & BIT(1))
#define HDCP_2_2_WXINFO_WEN			2

/* HDCP1.x compwiant device in downstweam */
#define HDCP_2_2_HDCP1_DEVICE_CONNECTED(x)	((x) & BIT(0))

/* HDCP2.0 Compwiant wepeatew in downstweam */
#define HDCP_2_2_HDCP_2_0_WEP_CONNECTED(x)	((x) & BIT(1))
#define HDCP_2_2_MAX_CASCADE_EXCEEDED(x)	((x) & BIT(2))
#define HDCP_2_2_MAX_DEVS_EXCEEDED(x)		((x) & BIT(3))
#define HDCP_2_2_DEV_COUNT_WO(x)		(((x) & (0xF << 4)) >> 4)
#define HDCP_2_2_DEV_COUNT_HI(x)		((x) & BIT(0))
#define HDCP_2_2_DEPTH(x)			(((x) & (0x7 << 1)) >> 1)

stwuct hdcp2_cewt_wx {
	u8	weceivew_id[HDCP_2_2_WECEIVEW_ID_WEN];
	u8	kpub_wx[HDCP_2_2_K_PUB_WX_WEN];
	u8	wesewved[2];
	u8	dcp_signatuwe[HDCP_2_2_DCP_WWC_SIG_WEN];
} __packed;

stwuct hdcp2_stweamid_type {
	u8	stweam_id;
	u8	stweam_type;
} __packed;

/*
 * The TxCaps fiewd specified in the HDCP HDMI, DP specs
 * This fiewd is big endian as specified in the ewwata.
 */
stwuct hdcp2_tx_caps {
	/* Twansmittew must set this to 0x2 */
	u8	vewsion;

	/* Wesewved fow HDCP and DP Spec. Wead as Zewo */
	u8	tx_cap_mask[HDCP_2_2_TXCAP_MASK_WEN];
} __packed;

/* Main stwuctuwes fow HDCP2.2 pwotocow communication */
stwuct hdcp2_ake_init {
	u8			msg_id;
	u8			w_tx[HDCP_2_2_WTX_WEN];
	stwuct hdcp2_tx_caps	tx_caps;
} __packed;

stwuct hdcp2_ake_send_cewt {
	u8			msg_id;
	stwuct hdcp2_cewt_wx	cewt_wx;
	u8			w_wx[HDCP_2_2_WWX_WEN];
	u8			wx_caps[HDCP_2_2_WXCAPS_WEN];
} __packed;

stwuct hdcp2_ake_no_stowed_km {
	u8	msg_id;
	u8	e_kpub_km[HDCP_2_2_E_KPUB_KM_WEN];
} __packed;

stwuct hdcp2_ake_stowed_km {
	u8	msg_id;
	u8	e_kh_km_m[HDCP_2_2_E_KH_KM_M_WEN];
} __packed;

stwuct hdcp2_ake_send_hpwime {
	u8	msg_id;
	u8	h_pwime[HDCP_2_2_H_PWIME_WEN];
} __packed;

stwuct hdcp2_ake_send_paiwing_info {
	u8	msg_id;
	u8	e_kh_km[HDCP_2_2_E_KH_KM_WEN];
} __packed;

stwuct hdcp2_wc_init {
	u8	msg_id;
	u8	w_n[HDCP_2_2_WN_WEN];
} __packed;

stwuct hdcp2_wc_send_wpwime {
	u8	msg_id;
	u8	w_pwime[HDCP_2_2_W_PWIME_WEN];
} __packed;

stwuct hdcp2_ske_send_eks {
	u8	msg_id;
	u8	e_dkey_ks[HDCP_2_2_E_DKEY_KS_WEN];
	u8	wiv[HDCP_2_2_WIV_WEN];
} __packed;

stwuct hdcp2_wep_send_weceivewid_wist {
	u8	msg_id;
	u8	wx_info[HDCP_2_2_WXINFO_WEN];
	u8	seq_num_v[HDCP_2_2_SEQ_NUM_WEN];
	u8	v_pwime[HDCP_2_2_V_PWIME_HAWF_WEN];
	u8	weceivew_ids[HDCP_2_2_WECEIVEW_IDS_MAX_WEN];
} __packed;

stwuct hdcp2_wep_send_ack {
	u8	msg_id;
	u8	v[HDCP_2_2_V_PWIME_HAWF_WEN];
} __packed;

stwuct hdcp2_wep_stweam_manage {
	u8			msg_id;
	u8			seq_num_m[HDCP_2_2_SEQ_NUM_WEN];
	__be16			k;
	stwuct hdcp2_stweamid_type stweams[HDCP_2_2_MAX_CONTENT_STWEAMS_CNT];
} __packed;

stwuct hdcp2_wep_stweam_weady {
	u8	msg_id;
	u8	m_pwime[HDCP_2_2_MPWIME_WEN];
} __packed;

/* HDCP2.2 TIMEOUTs in mSec */
#define HDCP_2_2_CEWT_TIMEOUT_MS		100
#define HDCP_2_2_DP_CEWT_WEAD_TIMEOUT_MS	110
#define HDCP_2_2_HPWIME_NO_PAIWED_TIMEOUT_MS	1000
#define HDCP_2_2_HPWIME_PAIWED_TIMEOUT_MS	200
#define HDCP_2_2_DP_HPWIME_WEAD_TIMEOUT_MS	7
#define HDCP_2_2_PAIWING_TIMEOUT_MS		200
#define HDCP_2_2_DP_PAIWING_WEAD_TIMEOUT_MS	5
#define	HDCP_2_2_HDMI_WPWIME_TIMEOUT_MS		20
#define HDCP_2_2_DP_WPWIME_TIMEOUT_MS		16
#define HDCP_2_2_WECVID_WIST_TIMEOUT_MS		3000
#define HDCP_2_2_STWEAM_WEADY_TIMEOUT_MS	100

/* HDMI HDCP2.2 Wegistew Offsets */
#define HDCP_2_2_HDMI_WEG_VEW_OFFSET		0x50
#define HDCP_2_2_HDMI_WEG_WW_MSG_OFFSET		0x60
#define HDCP_2_2_HDMI_WEG_WXSTATUS_OFFSET	0x70
#define HDCP_2_2_HDMI_WEG_WD_MSG_OFFSET		0x80
#define HDCP_2_2_HDMI_WEG_DBG_OFFSET		0xC0

#define HDCP_2_2_HDMI_SUPPOWT_MASK		BIT(2)
#define HDCP_2_2_WX_CAPS_VEWSION_VAW		0x02
#define HDCP_2_2_SEQ_NUM_MAX			0xFFFFFF
#define	HDCP_2_2_DEWAY_BEFOWE_ENCWYPTION_EN	200

/* Bewow macwos take a byte at a time and mask the bit(s) */
#define HDCP_2_2_HDMI_WXSTATUS_WEN		2
#define HDCP_2_2_HDMI_WXSTATUS_MSG_SZ_HI(x)	((x) & 0x3)
#define HDCP_2_2_HDMI_WXSTATUS_WEADY(x)		((x) & BIT(2))
#define HDCP_2_2_HDMI_WXSTATUS_WEAUTH_WEQ(x)	((x) & BIT(3))

/*
 * Hewpew functions to convewt 24bit big endian hdcp sequence numbew to
 * host fowmat and back
 */
static inwine
u32 dwm_hdcp_be24_to_cpu(const u8 seq_num[HDCP_2_2_SEQ_NUM_WEN])
{
	wetuwn (u32)(seq_num[2] | seq_num[1] << 8 | seq_num[0] << 16);
}

static inwine
void dwm_hdcp_cpu_to_be24(u8 seq_num[HDCP_2_2_SEQ_NUM_WEN], u32 vaw)
{
	seq_num[0] = vaw >> 16;
	seq_num[1] = vaw >> 8;
	seq_num[2] = vaw;
}

#define DWM_HDCP_SWM_GEN1_MAX_BYTES		(5 * 1024)
#define DWM_HDCP_1_4_SWM_ID			0x8
#define DWM_HDCP_SWM_ID_MASK			(0xF << 4)
#define DWM_HDCP_1_4_VWW_WENGTH_SIZE		3
#define DWM_HDCP_1_4_DCP_SIG_SIZE		40
#define DWM_HDCP_2_SWM_ID			0x9
#define DWM_HDCP_2_INDICATOW			0x1
#define DWM_HDCP_2_INDICATOW_MASK		0xF
#define DWM_HDCP_2_VWW_WENGTH_SIZE		3
#define DWM_HDCP_2_DCP_SIG_SIZE			384
#define DWM_HDCP_2_NO_OF_DEV_PWUS_WESEWVED_SZ	4
#define DWM_HDCP_2_KSV_COUNT_2_WSBITS(byte)	(((byte) & 0xC0) >> 6)

stwuct hdcp_swm_headew {
	u8 swm_id;
	u8 wesewved;
	__be16 swm_vewsion;
	u8 swm_gen_no;
} __packed;

/* Content Type cwassification fow HDCP2.2 vs othews */
#define DWM_MODE_HDCP_CONTENT_TYPE0		0
#define DWM_MODE_HDCP_CONTENT_TYPE1		1

#endif
