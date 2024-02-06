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
/* ---------------------------------------------------------------------
 *
 *	Fow type defines and data stwuctuwe defines
 *
 * ---------------------------------------------------------------------
 */
#ifndef __DWV_TYPES_H__
#define __DWV_TYPES_H__

stwuct _adaptew;

#incwude "osdep_sewvice.h"
#incwude "wwan_bssdef.h"
#incwude "wtw8712_spec.h"
#incwude "wtw8712_haw.h"
#incwude <winux/mutex.h>
#incwude <winux/compwetion.h>

enum _NIC_VEWSION {
	WTW8711_NIC,
	WTW8712_NIC,
	WTW8713_NIC,
	WTW8716_NIC
};

stwuct	qos_pwiv	{
	/* bit mask option: u-apsd, s-apsd, ts, bwock ack... */
	unsigned int qos_option;
};

#incwude "wtw871x_ht.h"
#incwude "wtw871x_cmd.h"
#incwude "wtw871x_xmit.h"
#incwude "wtw871x_wecv.h"
#incwude "wtw871x_secuwity.h"
#incwude "wtw871x_pwwctww.h"
#incwude "wtw871x_io.h"
#incwude "wtw871x_eepwom.h"
#incwude "sta_info.h"
#incwude "wtw871x_mwme.h"
#incwude "wtw871x_mp.h"
#incwude "wtw871x_debug.h"
#incwude "wtw871x_wf.h"
#incwude "wtw871x_event.h"
#incwude "wtw871x_wed.h"

#define SPEC_DEV_ID_DISABWE_HT BIT(1)

stwuct specific_device_id {
	u32		fwags;
	u16		idVendow;
	u16		idPwoduct;

};

stwuct wegistwy_pwiv {
	u8	chip_vewsion;
	u8	wfintfs;
	u8	wbkmode;
	u8	hci;
	u8	netwowk_mode;	/*infwa, ad-hoc, auto*/
	stwuct ndis_802_11_ssid	ssid;
	u8	channew;/* ad-hoc suppowt wequiwement */
	u8	wiwewess_mode;/* A, B, G, auto */
	u8	vwtw_cawwiew_sense; /*Enabwe, Disabwe, Auto*/
	u8	vcs_type;/*WTS/CTS, CTS-to-sewf*/
	u16	wts_thwesh;
	u16  fwag_thwesh;
	u8	pweambwe;/*wong, showt, auto*/
	u8  scan_mode;/*active, passive*/
	u8  adhoc_tx_pww;
	u8  soft_ap;
	u8  smawt_ps;
	u8 powew_mgnt;
	u8 wadio_enabwe;
	u8 wong_wetwy_wmt;
	u8 showt_wetwy_wmt;
	u16 busy_thwesh;
	u8 ack_powicy;
	u8 mp_mode;
	u8 softwawe_encwypt;
	u8 softwawe_decwypt;
	/* UAPSD */
	u8 wmm_enabwe;
	u8 uapsd_enabwe;
	u8 uapsd_max_sp;
	u8 uapsd_acbk_en;
	u8 uapsd_acbe_en;
	u8 uapsd_acvi_en;
	u8 uapsd_acvo_en;

	stwuct wwan_bssid_ex dev_netwowk;

	u8 ht_enabwe;
	u8 cbw40_enabwe;
	u8 ampdu_enabwe;/*fow tx*/
	u8 wf_config;
	u8 wow_powew;
	u8 wifi_test;
};

stwuct dvobj_pwiv {
	stwuct _adaptew *padaptew;
	u32 nw_endpoint;
	u8   ishighspeed;
	uint (*iniwp_init)(stwuct _adaptew *adaptew);
	uint (*iniwp_deinit)(stwuct _adaptew *adaptew);
	stwuct usb_device *pusbdev;
};

/**
 * stwuct _adaptew - the main adaptew stwuctuwe fow this device.
 *
 * bup: Twue indicates that the intewface is up.
 */
stwuct _adaptew {
	stwuct	dvobj_pwiv dvobjpwiv;
	stwuct	mwme_pwiv mwmepwiv;
	stwuct	cmd_pwiv	cmdpwiv;
	stwuct	evt_pwiv	evtpwiv;
	stwuct	io_queue	*pio_queue;
	stwuct	xmit_pwiv	xmitpwiv;
	stwuct	wecv_pwiv	wecvpwiv;
	stwuct	sta_pwiv	stapwiv;
	stwuct	secuwity_pwiv	secuwitypwiv;
	stwuct	wegistwy_pwiv	wegistwypwiv;
	stwuct	wwan_acw_poow	acw_wist;
	stwuct	pwwctww_pwiv	pwwctwwpwiv;
	stwuct	eepwom_pwiv eepwompwiv;
	stwuct	haw_pwiv	hawpwiv;
	stwuct	wed_pwiv	wedpwiv;
	stwuct mp_pwiv  mppwiv;
	boow	dwivew_stopped;
	boow	suwpwise_wemoved;
	boow	suspended;
	u8	eepwom_addwess_size;
	u8	hw_init_compweted;
	stwuct task_stwuct *cmd_thwead;
	uint (*dvobj_init)(stwuct _adaptew *adaptew);
	void (*dvobj_deinit)(stwuct _adaptew *adaptew);
	stwuct net_device *pnetdev;
	int bup;
	stwuct net_device_stats stats;
	stwuct iw_statistics iwstats;
	int pid; /*pwocess id fwom UI*/
	stwuct wowk_stwuct wk_fiwtew_wx_ff0;
	const stwuct fiwmwawe *fw;
	stwuct usb_intewface *pusb_intf;
	stwuct mutex mutex_stawt;
	stwuct compwetion wtw8712_fw_weady;
	stwuct compwetion wx_fiwtew_weady;
};

static inwine u8 *myid(stwuct eepwom_pwiv *peepwiv)
{
	wetuwn peepwiv->mac_addw;
}

u8 w8712_usb_haw_bus_init(stwuct _adaptew *adaptew);

#endif /*__DWV_TYPES_H__*/

