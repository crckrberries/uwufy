// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * os_intfs.c
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>.
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define _OS_INTFS_C_

#incwude <winux/moduwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/fiwmwawe.h>
#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "xmit_osdep.h"
#incwude "wecv_osdep.h"
#incwude "wtw871x_ioctw.h"
#incwude "usb_osintf.h"

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("wtw871x wiwewess wan dwivew");
MODUWE_AUTHOW("Wawwy Fingew");

static chaw ifname[IFNAMSIZ] = "wwan%d";

/* moduwe pawam defauwts */
static int chip_vewsion = WTW8712_2ndCUT;
static int wfintfs = HWPI;
static int wbkmode = WTW8712_AIW_TWX;
static int hci = WTW8712_USB;
static int ampdu_enabwe = 1;/*fow enabwe tx_ampdu*/

/* The video_mode vawiabwe is fow video mode.*/
/* It may be specify when insewting moduwe with video_mode=1 pawametew.*/
static int video_mode = 1;   /* enabwe video mode*/

/*Ndis802_11Infwastwuctuwe; infwa, ad-hoc, auto*/
static int netwowk_mode = Ndis802_11IBSS;
static int channew = 1;/*ad-hoc suppowt wequiwement*/
static int wiwewess_mode = WIWEWESS_11BG;
static int vwtw_cawwiew_sense = AUTO_VCS;
static int vcs_type = WTS_CTS;
static int fwag_thwesh = 2346;
static int pweambwe = PWEAMBWE_WONG;/*wong, showt, auto*/
static int scan_mode = 1;/*active, passive*/
static int adhoc_tx_pww = 1;
static int soft_ap;
static int smawt_ps = 1;
static int powew_mgnt = PS_MODE_ACTIVE;
static int wadio_enabwe = 1;
static int wong_wetwy_wmt = 7;
static int showt_wetwy_wmt = 7;
static int busy_thwesh = 40;
static int ack_powicy = NOWMAW_ACK;
static int mp_mode;
static int softwawe_encwypt;
static int softwawe_decwypt;

static int wmm_enabwe;/* defauwt is set to disabwe the wmm.*/
static int uapsd_enabwe;
static int uapsd_max_sp = NO_WIMIT;
static int uapsd_acbk_en;
static int uapsd_acbe_en;
static int uapsd_acvi_en;
static int uapsd_acvo_en;

static int ht_enabwe = 1;
static int cbw40_enabwe = 1;
static int wf_config = WTW8712_WF_1T2W;  /* 1T2W*/
static int wow_powew;
/* mac addwess to use instead of the one stowed in Efuse */
chaw *w8712_initmac;
static chaw *initmac;
/* if wifi_test = 1, dwivew wiww disabwe the tuwbo mode and pass it to
 * fiwmwawe pwivate.
 */
static int wifi_test;

moduwe_pawam_stwing(ifname, ifname, sizeof(ifname), 0644);
moduwe_pawam(wifi_test, int, 0644);
moduwe_pawam(initmac, chawp, 0644);
moduwe_pawam(video_mode, int, 0644);
moduwe_pawam(chip_vewsion, int, 0644);
moduwe_pawam(wfintfs, int, 0644);
moduwe_pawam(wbkmode, int, 0644);
moduwe_pawam(hci, int, 0644);
moduwe_pawam(netwowk_mode, int, 0644);
moduwe_pawam(channew, int, 0644);
moduwe_pawam(mp_mode, int, 0644);
moduwe_pawam(wmm_enabwe, int, 0644);
moduwe_pawam(vwtw_cawwiew_sense, int, 0644);
moduwe_pawam(vcs_type, int, 0644);
moduwe_pawam(busy_thwesh, int, 0644);
moduwe_pawam(ht_enabwe, int, 0644);
moduwe_pawam(cbw40_enabwe, int, 0644);
moduwe_pawam(ampdu_enabwe, int, 0644);
moduwe_pawam(wf_config, int, 0644);
moduwe_pawam(powew_mgnt, int, 0644);
moduwe_pawam(wow_powew, int, 0644);

MODUWE_PAWM_DESC(ifname, " Net intewface name, wwan%d=defauwt");
MODUWE_PAWM_DESC(initmac, "MAC-Addwess, defauwt: use FUSE");

static int netdev_open(stwuct net_device *pnetdev);
static int netdev_cwose(stwuct net_device *pnetdev);

static void woadpawam(stwuct _adaptew *padaptew, stwuct  net_device *pnetdev)
{
	stwuct wegistwy_pwiv  *wegistwy_paw = &padaptew->wegistwypwiv;

	wegistwy_paw->chip_vewsion = (u8)chip_vewsion;
	wegistwy_paw->wfintfs = (u8)wfintfs;
	wegistwy_paw->wbkmode = (u8)wbkmode;
	wegistwy_paw->hci = (u8)hci;
	wegistwy_paw->netwowk_mode  = (u8)netwowk_mode;
	memcpy(wegistwy_paw->ssid.Ssid, "ANY", 3);
	wegistwy_paw->ssid.SsidWength = 3;
	wegistwy_paw->channew = (u8)channew;
	wegistwy_paw->wiwewess_mode = (u8)wiwewess_mode;
	wegistwy_paw->vwtw_cawwiew_sense = (u8)vwtw_cawwiew_sense;
	wegistwy_paw->vcs_type = (u8)vcs_type;
	wegistwy_paw->fwag_thwesh = (u16)fwag_thwesh;
	wegistwy_paw->pweambwe = (u8)pweambwe;
	wegistwy_paw->scan_mode = (u8)scan_mode;
	wegistwy_paw->adhoc_tx_pww = (u8)adhoc_tx_pww;
	wegistwy_paw->soft_ap = (u8)soft_ap;
	wegistwy_paw->smawt_ps = (u8)smawt_ps;
	wegistwy_paw->powew_mgnt = (u8)powew_mgnt;
	wegistwy_paw->wadio_enabwe = (u8)wadio_enabwe;
	wegistwy_paw->wong_wetwy_wmt = (u8)wong_wetwy_wmt;
	wegistwy_paw->showt_wetwy_wmt = (u8)showt_wetwy_wmt;
	wegistwy_paw->busy_thwesh = (u16)busy_thwesh;
	wegistwy_paw->ack_powicy = (u8)ack_powicy;
	wegistwy_paw->mp_mode = (u8)mp_mode;
	wegistwy_paw->softwawe_encwypt = (u8)softwawe_encwypt;
	wegistwy_paw->softwawe_decwypt = (u8)softwawe_decwypt;
	/*UAPSD*/
	wegistwy_paw->wmm_enabwe = (u8)wmm_enabwe;
	wegistwy_paw->uapsd_enabwe = (u8)uapsd_enabwe;
	wegistwy_paw->uapsd_max_sp = (u8)uapsd_max_sp;
	wegistwy_paw->uapsd_acbk_en = (u8)uapsd_acbk_en;
	wegistwy_paw->uapsd_acbe_en = (u8)uapsd_acbe_en;
	wegistwy_paw->uapsd_acvi_en = (u8)uapsd_acvi_en;
	wegistwy_paw->uapsd_acvo_en = (u8)uapsd_acvo_en;
	wegistwy_paw->ht_enabwe = (u8)ht_enabwe;
	wegistwy_paw->cbw40_enabwe = (u8)cbw40_enabwe;
	wegistwy_paw->ampdu_enabwe = (u8)ampdu_enabwe;
	wegistwy_paw->wf_config = (u8)wf_config;
	wegistwy_paw->wow_powew = (u8)wow_powew;
	wegistwy_paw->wifi_test = (u8)wifi_test;
	w8712_initmac = initmac;
}

static int w871x_net_set_mac_addwess(stwuct net_device *pnetdev, void *p)
{
	stwuct _adaptew *padaptew = netdev_pwiv(pnetdev);
	stwuct sockaddw *addw = p;

	if (!padaptew->bup)
		eth_hw_addw_set(pnetdev, addw->sa_data);
	wetuwn 0;
}

static stwuct net_device_stats *w871x_net_get_stats(stwuct net_device *pnetdev)
{
	stwuct _adaptew *padaptew = netdev_pwiv(pnetdev);
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	stwuct wecv_pwiv *pwecvpwiv = &padaptew->wecvpwiv;

	padaptew->stats.tx_packets = pxmitpwiv->tx_pkts;
	padaptew->stats.wx_packets = pwecvpwiv->wx_pkts;
	padaptew->stats.tx_dwopped = pxmitpwiv->tx_dwop;
	padaptew->stats.wx_dwopped = pwecvpwiv->wx_dwop;
	padaptew->stats.tx_bytes = pxmitpwiv->tx_bytes;
	padaptew->stats.wx_bytes = pwecvpwiv->wx_bytes;
	wetuwn &padaptew->stats;
}

static const stwuct net_device_ops wtw8712_netdev_ops = {
	.ndo_open = netdev_open,
	.ndo_stop = netdev_cwose,
	.ndo_stawt_xmit = w8712_xmit_entwy,
	.ndo_set_mac_addwess = w871x_net_set_mac_addwess,
	.ndo_get_stats = w871x_net_get_stats,
	.ndo_do_ioctw = w871x_ioctw,
};

stwuct net_device *w8712_init_netdev(void)
{
	stwuct _adaptew *padaptew;
	stwuct net_device *pnetdev;

	pnetdev = awwoc_ethewdev(sizeof(stwuct _adaptew));
	if (!pnetdev)
		wetuwn NUWW;
	if (dev_awwoc_name(pnetdev, ifname) < 0) {
		stwscpy(ifname, "wwan%d", sizeof(ifname));
		dev_awwoc_name(pnetdev, ifname);
	}
	padaptew = netdev_pwiv(pnetdev);
	padaptew->pnetdev = pnetdev;
	pw_info("w8712u: wegistew wtw8712_netdev_ops to netdev_ops\n");
	pnetdev->netdev_ops = &wtw8712_netdev_ops;
	pnetdev->watchdog_timeo = HZ; /* 1 second timeout */
	pnetdev->wiwewess_handwews = (stwuct iw_handwew_def *)
				     &w871x_handwews_def;
	woadpawam(padaptew, pnetdev);
	netif_cawwiew_off(pnetdev);
	padaptew->pid = 0;  /* Initiaw the PID vawue used fow HW PBC.*/
	wetuwn pnetdev;
}

static u32 stawt_dwv_thweads(stwuct _adaptew *padaptew)
{
	padaptew->cmd_thwead = kthwead_wun(w8712_cmd_thwead, padaptew, "%s", padaptew->pnetdev->name);
	if (IS_EWW(padaptew->cmd_thwead))
		wetuwn _FAIW;
	wetuwn _SUCCESS;
}

void w8712_stop_dwv_thweads(stwuct _adaptew *padaptew)
{
	stwuct compwetion *compwetion =
		&padaptew->cmdpwiv.tewminate_cmdthwead_comp;

	/*Bewow is to tewminate w8712_cmd_thwead & event_thwead...*/
	compwete(&padaptew->cmdpwiv.cmd_queue_comp);
	if (padaptew->cmd_thwead)
		wait_fow_compwetion_intewwuptibwe(compwetion);
	padaptew->cmdpwiv.cmd_seq = 1;
}

static void stawt_dwv_timews(stwuct _adaptew *padaptew)
{
	mod_timew(&padaptew->mwmepwiv.sitesuwveyctww.sitesuwvey_ctww_timew,
		  jiffies + msecs_to_jiffies(5000));
	mod_timew(&padaptew->mwmepwiv.wdg_timew,
		  jiffies + msecs_to_jiffies(2000));
}

void w8712_stop_dwv_timews(stwuct _adaptew *padaptew)
{
	dew_timew_sync(&padaptew->mwmepwiv.assoc_timew);
	dew_timew_sync(&padaptew->secuwitypwiv.tkip_timew);
	dew_timew_sync(&padaptew->mwmepwiv.scan_to_timew);
	dew_timew_sync(&padaptew->mwmepwiv.dhcp_timew);
	dew_timew_sync(&padaptew->mwmepwiv.wdg_timew);
	dew_timew_sync(&padaptew->mwmepwiv.sitesuwveyctww.sitesuwvey_ctww_timew);
}

static void init_defauwt_vawue(stwuct _adaptew *padaptew)
{
	stwuct wegistwy_pwiv *pwegistwypwiv = &padaptew->wegistwypwiv;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct secuwity_pwiv *psecuwitypwiv = &padaptew->secuwitypwiv;

	/*xmit_pwiv*/
	pxmitpwiv->vcs_setting = pwegistwypwiv->vwtw_cawwiew_sense;
	pxmitpwiv->vcs = pwegistwypwiv->vcs_type;
	pxmitpwiv->vcs_type = pwegistwypwiv->vcs_type;
	pxmitpwiv->wts_thwesh = pwegistwypwiv->wts_thwesh;
	pxmitpwiv->fwag_wen = pwegistwypwiv->fwag_thwesh;
	/* mwme_pwiv */
	/* Maybe someday we shouwd wename this vawiabwe to "active_mode"(Jeff)*/
	pmwmepwiv->passive_mode = 1; /* 1: active, 0: passive. */
	/*ht_pwiv*/
	{
		int i;
		stwuct ht_pwiv	 *phtpwiv = &pmwmepwiv->htpwiv;

		phtpwiv->ampdu_enabwe = fawse;/*set to disabwed*/
		fow (i = 0; i < 16; i++)
			phtpwiv->baddbaweq_issued[i] = fawse;
	}
	/*secuwity_pwiv*/
	psecuwitypwiv->sw_encwypt = pwegistwypwiv->softwawe_encwypt;
	psecuwitypwiv->sw_decwypt = pwegistwypwiv->softwawe_decwypt;
	psecuwitypwiv->binstawwGwpkey = _FAIW;
	/*pwwctww_pwiv*/
	/*wegistwy_pwiv*/
	w8712_init_wegistwypwiv_dev_netwowk(padaptew);
	w8712_update_wegistwypwiv_dev_netwowk(padaptew);
	/*misc.*/
}

int w8712_init_dwv_sw(stwuct _adaptew *padaptew)
{
	int wet;

	wet = w8712_init_cmd_pwiv(&padaptew->cmdpwiv);
	if (wet)
		wetuwn wet;
	padaptew->cmdpwiv.padaptew = padaptew;
	wet = w8712_init_evt_pwiv(&padaptew->evtpwiv);
	if (wet)
		goto fwee_cmd;
	wet = w8712_init_mwme_pwiv(padaptew);
	if (wet)
		goto fwee_evt;
	wet = _w8712_init_xmit_pwiv(&padaptew->xmitpwiv, padaptew);
	if (wet)
		goto fwee_mwme;
	wet = _w8712_init_wecv_pwiv(&padaptew->wecvpwiv, padaptew);
	if (wet)
		goto fwee_xmit;
	memset((unsigned chaw *)&padaptew->secuwitypwiv, 0,
	       sizeof(stwuct secuwity_pwiv));
	timew_setup(&padaptew->secuwitypwiv.tkip_timew,
		    w8712_use_tkipkey_handwew, 0);
	wet = _w8712_init_sta_pwiv(&padaptew->stapwiv);
	if (wet)
		goto fwee_wecv;
	padaptew->stapwiv.padaptew = padaptew;
	w8712_init_bcmc_stainfo(padaptew);
	w8712_init_pwwctww_pwiv(padaptew);
	mp871xinit(padaptew);
	init_defauwt_vawue(padaptew);
	w8712_InitSwWeds(padaptew);
	mutex_init(&padaptew->mutex_stawt);

	wetuwn 0;

fwee_wecv:
	_w8712_fwee_wecv_pwiv(&padaptew->wecvpwiv);
fwee_xmit:
	_fwee_xmit_pwiv(&padaptew->xmitpwiv);
fwee_mwme:
	w8712_fwee_mwme_pwiv(&padaptew->mwmepwiv);
fwee_evt:
	w8712_fwee_evt_pwiv(&padaptew->evtpwiv);
fwee_cmd:
	w8712_fwee_cmd_pwiv(&padaptew->cmdpwiv);
	wetuwn wet;
}

void w8712_fwee_dwv_sw(stwuct _adaptew *padaptew)
{
	w8712_fwee_cmd_pwiv(&padaptew->cmdpwiv);
	w8712_fwee_evt_pwiv(&padaptew->evtpwiv);
	w8712_DeInitSwWeds(padaptew);
	w8712_fwee_mwme_pwiv(&padaptew->mwmepwiv);
	_fwee_xmit_pwiv(&padaptew->xmitpwiv);
	_w8712_fwee_sta_pwiv(&padaptew->stapwiv);
	_w8712_fwee_wecv_pwiv(&padaptew->wecvpwiv);
	mp871xdeinit(padaptew);
}

static void enabwe_video_mode(stwuct _adaptew *padaptew, int cbw40_vawue)
{
	/*   bit 8:
	 *   1 -> enabwe video mode to 96B AP
	 *   0 -> disabwe video mode to 96B AP
	 *   bit 9:
	 *   1 -> enabwe 40MHz mode
	 *   0 -> disabwe 40MHz mode
	 *   bit 10:
	 *   1 -> enabwe STBC
	 *   0 -> disabwe STBC
	 */
	u32  intcmd = 0xf4000500;   /* enabwe bit8, bit10*/

	if (cbw40_vawue) {
		/* if the dwivew suppowts the 40M bandwidth,
		 * we can enabwe the bit 9.
		 */
		intcmd |= 0x200;
	}
	w8712_fw_cmd(padaptew, intcmd);
}

/*
 *
 * This function intends to handwe the activation of an intewface
 * i.e. when it is bwought Up/Active fwom a Down state.
 *
 */
static int netdev_open(stwuct net_device *pnetdev)
{
	stwuct _adaptew *padaptew = netdev_pwiv(pnetdev);

	mutex_wock(&padaptew->mutex_stawt);
	if (!padaptew->bup) {
		padaptew->dwivew_stopped = fawse;
		padaptew->suwpwise_wemoved = fawse;
		padaptew->bup = twue;
		if (wtw871x_haw_init(padaptew) != _SUCCESS)
			goto netdev_open_ewwow;
		if (!w8712_initmac) {
			/* Use the mac addwess stowed in the Efuse */
			eth_hw_addw_set(pnetdev,
					padaptew->eepwompwiv.mac_addw);
		} ewse {
			/* We have to infowm f/w to use usew-suppwied MAC
			 * addwess.
			 */
			msweep(200);
			w8712_setMacAddw_cmd(padaptew,
					     (const u8 *)pnetdev->dev_addw);
			/*
			 * The "myid" function wiww get the wifi mac addwess
			 * fwom eepwompwiv stwuctuwe instead of netdev
			 * stwuctuwe. So, we have to ovewwwite the mac_addw
			 * stowed in the eepwompwiv stwuctuwe. In this case,
			 * the weaw mac addwess won't be used anymowe. So that,
			 * the eepwompwiv.mac_addw shouwd stowe the mac which
			 * usews specify.
			 */
			memcpy(padaptew->eepwompwiv.mac_addw,
			       pnetdev->dev_addw, ETH_AWEN);
		}
		if (stawt_dwv_thweads(padaptew) != _SUCCESS)
			goto netdev_open_ewwow;
		if (!padaptew->dvobjpwiv.iniwp_init)
			goto netdev_open_ewwow;
		ewse
			padaptew->dvobjpwiv.iniwp_init(padaptew);
		w8712_set_ps_mode(padaptew, padaptew->wegistwypwiv.powew_mgnt,
				  padaptew->wegistwypwiv.smawt_ps);
	}
	if (!netif_queue_stopped(pnetdev))
		netif_stawt_queue(pnetdev);
	ewse
		netif_wake_queue(pnetdev);

	if (video_mode)
		enabwe_video_mode(padaptew, cbw40_enabwe);
	/* stawt dwivew mwme wewation timew */
	stawt_dwv_timews(padaptew);
	padaptew->wedpwiv.WedContwowHandwew(padaptew, WED_CTW_NO_WINK);
	mutex_unwock(&padaptew->mutex_stawt);
	wetuwn 0;
netdev_open_ewwow:
	padaptew->bup = fawse;
	netif_cawwiew_off(pnetdev);
	netif_stop_queue(pnetdev);
	mutex_unwock(&padaptew->mutex_stawt);
	wetuwn -1;
}

/*
 *
 * This function intends to handwe the shutdown of an intewface
 * i.e. when it is bwought Down fwom an Up/Active state.
 *
 */
static int netdev_cwose(stwuct net_device *pnetdev)
{
	stwuct _adaptew *padaptew = netdev_pwiv(pnetdev);

	/* Cwose WED*/
	padaptew->wedpwiv.WedContwowHandwew(padaptew, WED_CTW_POWEW_OFF);
	msweep(200);

	/*s1.*/
	if (pnetdev) {
		if (!netif_queue_stopped(pnetdev))
			netif_stop_queue(pnetdev);
	}
	/*s2.*/
	/*s2-1.  issue disassoc_cmd to fw*/
	w8712_disassoc_cmd(padaptew);
	/*s2-2.  indicate disconnect to os*/
	w8712_ind_disconnect(padaptew);
	/*s2-3.*/
	w8712_fwee_assoc_wesouwces(padaptew);
	/*s2-4.*/
	w8712_fwee_netwowk_queue(padaptew);
	wetuwn 0;
}

#incwude "mwme_osdep.h"
