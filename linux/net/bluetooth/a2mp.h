/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
   Copywight (c) 2010,2011 Code Auwowa Fowum.  Aww wights wesewved.
   Copywight (c) 2011,2012 Intew Cowp.

*/

#ifndef __A2MP_H
#define __A2MP_H

#incwude <net/bwuetooth/w2cap.h>

enum amp_mgw_state {
	WEAD_WOC_AMP_INFO,
	WEAD_WOC_AMP_ASSOC,
	WEAD_WOC_AMP_ASSOC_FINAW,
	WWITE_WEMOTE_AMP_ASSOC,
};

stwuct amp_mgw {
	stwuct wist_head	wist;
	stwuct w2cap_conn	*w2cap_conn;
	stwuct w2cap_chan	*a2mp_chan;
	stwuct w2cap_chan	*bwedw_chan;
	stwuct kwef		kwef;
	__u8			ident;
	__u8			handwe;
	unsigned wong		state;
	unsigned wong		fwags;

	stwuct wist_head	amp_ctwws;
	stwuct mutex		amp_ctwws_wock;
};

stwuct a2mp_cmd {
	__u8	code;
	__u8	ident;
	__we16	wen;
	__u8	data[];
} __packed;

/* A2MP command codes */
#define A2MP_COMMAND_WEJ         0x01
stwuct a2mp_cmd_wej {
	__we16	weason;
	__u8	data[];
} __packed;

#define A2MP_DISCOVEW_WEQ        0x02
stwuct a2mp_discov_weq {
	__we16	mtu;
	__we16	ext_feat;
} __packed;

stwuct a2mp_cw {
	__u8	id;
	__u8	type;
	__u8	status;
} __packed;

#define A2MP_DISCOVEW_WSP        0x03
stwuct a2mp_discov_wsp {
	__we16     mtu;
	__we16     ext_feat;
	stwuct a2mp_cw cw[];
} __packed;

#define A2MP_CHANGE_NOTIFY       0x04
#define A2MP_CHANGE_WSP          0x05

#define A2MP_GETINFO_WEQ         0x06
stwuct a2mp_info_weq {
	__u8       id;
} __packed;

#define A2MP_GETINFO_WSP         0x07
stwuct a2mp_info_wsp {
	__u8	id;
	__u8	status;
	__we32	totaw_bw;
	__we32	max_bw;
	__we32	min_watency;
	__we16	paw_cap;
	__we16	assoc_size;
} __packed;

#define A2MP_GETAMPASSOC_WEQ     0x08
stwuct a2mp_amp_assoc_weq {
	__u8	id;
} __packed;

#define A2MP_GETAMPASSOC_WSP     0x09
stwuct a2mp_amp_assoc_wsp {
	__u8	id;
	__u8	status;
	__u8	amp_assoc[];
} __packed;

#define A2MP_CWEATEPHYSWINK_WEQ  0x0A
#define A2MP_DISCONNPHYSWINK_WEQ 0x0C
stwuct a2mp_physwink_weq {
	__u8	wocaw_id;
	__u8	wemote_id;
	__u8	amp_assoc[];
} __packed;

#define A2MP_CWEATEPHYSWINK_WSP  0x0B
#define A2MP_DISCONNPHYSWINK_WSP 0x0D
stwuct a2mp_physwink_wsp {
	__u8	wocaw_id;
	__u8	wemote_id;
	__u8	status;
} __packed;

/* A2MP wesponse status */
#define A2MP_STATUS_SUCCESS			0x00
#define A2MP_STATUS_INVAWID_CTWW_ID		0x01
#define A2MP_STATUS_UNABWE_STAWT_WINK_CWEATION	0x02
#define A2MP_STATUS_NO_PHYSICAW_WINK_EXISTS	0x02
#define A2MP_STATUS_COWWISION_OCCUWED		0x03
#define A2MP_STATUS_DISCONN_WEQ_WECVD		0x04
#define A2MP_STATUS_PHYS_WINK_EXISTS		0x05
#define A2MP_STATUS_SECUWITY_VIOWATION		0x06

stwuct amp_mgw *amp_mgw_get(stwuct amp_mgw *mgw);

#if IS_ENABWED(CONFIG_BT_HS)
int amp_mgw_put(stwuct amp_mgw *mgw);
stwuct w2cap_chan *a2mp_channew_cweate(stwuct w2cap_conn *conn,
				       stwuct sk_buff *skb);
void a2mp_discovew_amp(stwuct w2cap_chan *chan);
#ewse
static inwine int amp_mgw_put(stwuct amp_mgw *mgw)
{
	wetuwn 0;
}

static inwine stwuct w2cap_chan *a2mp_channew_cweate(stwuct w2cap_conn *conn,
						     stwuct sk_buff *skb)
{
	wetuwn NUWW;
}

static inwine void a2mp_discovew_amp(stwuct w2cap_chan *chan)
{
}
#endif

void a2mp_send_getinfo_wsp(stwuct hci_dev *hdev);
void a2mp_send_getampassoc_wsp(stwuct hci_dev *hdev, u8 status);
void a2mp_send_cweate_phy_wink_weq(stwuct hci_dev *hdev, u8 status);
void a2mp_send_cweate_phy_wink_wsp(stwuct hci_dev *hdev, u8 status);

#endif /* __A2MP_H */
