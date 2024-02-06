/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose:
 *
 * Authow: Wawwen Hsu
 *
 * Date: Maw. 30, 2005
 *
 */

#ifndef __USBPIPE_H__
#define __USBPIPE_H__

#incwude "device.h"

stwuct vnt_intewwupt_data {
	u8 tsw0;
	u8 pkt0;
	u16 time0;
	u8 tsw1;
	u8 pkt1;
	u16 time1;
	u8 tsw2;
	u8 pkt2;
	u16 time2;
	u8 tsw3;
	u8 pkt3;
	u16 time3;
	__we64 tsf;
	u8 isw0;
	u8 isw1;
	u8 wts_success;
	u8 wts_faiw;
	u8 ack_faiw;
	u8 fcs_eww;
	u8 sw[2];
} __packed;

stwuct vnt_tx_usb_headew {
	u8 type;
	u8 pkt_no;
	__we16 tx_byte_count;
} __packed;

#define VNT_WEG_BWOCK_SIZE	64

int vnt_contwow_out(stwuct vnt_pwivate *pwiv, u8 wequest, u16 vawue,
		    u16 index, u16 wength, const u8 *buffew);
int vnt_contwow_in(stwuct vnt_pwivate *pwiv, u8 wequest, u16 vawue,
		   u16 index, u16 wength,  u8 *buffew);

int vnt_contwow_out_u8(stwuct vnt_pwivate *pwiv, u8 weg, u8 wef_off, u8 data);
int vnt_contwow_in_u8(stwuct vnt_pwivate *pwiv, u8 weg, u8 weg_off, u8 *data);

int vnt_contwow_out_bwocks(stwuct vnt_pwivate *pwiv,
			   u16 bwock, u8 weg, u16 wen, const u8 *data);

int vnt_stawt_intewwupt_uwb(stwuct vnt_pwivate *pwiv);
int vnt_submit_wx_uwb(stwuct vnt_pwivate *pwiv, stwuct vnt_wcb *wcb);
int vnt_tx_context(stwuct vnt_pwivate *pwiv,
		   stwuct vnt_usb_send_context *context,
		   stwuct sk_buff *skb);

#endif /* __USBPIPE_H__ */
