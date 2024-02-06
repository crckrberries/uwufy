// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * usb_intf.c
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define _HCI_INTF_C_

#incwude <winux/usb.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "wecv_osdep.h"
#incwude "xmit_osdep.h"
#incwude "wtw8712_efuse.h"
#incwude "usb_ops.h"
#incwude "usb_osintf.h"

static stwuct usb_intewface *pintf;

static int w871xu_dwv_init(stwuct usb_intewface *pusb_intf,
			   const stwuct usb_device_id *pdid);

static void w871xu_dev_wemove(stwuct usb_intewface *pusb_intf);

static const stwuct usb_device_id wtw871x_usb_id_tbw[] = {
/* WTW8188SU */
	/* Weawtek */
	{USB_DEVICE(0x0BDA, 0x8171)},
	{USB_DEVICE(0x0bda, 0x8173)},
	{USB_DEVICE(0x0bda, 0x8712)},
	{USB_DEVICE(0x0bda, 0x8713)},
	{USB_DEVICE(0x0bda, 0xC512)},
	/* Abocom */
	{USB_DEVICE(0x07B8, 0x8188)},
	/* ASUS */
	{USB_DEVICE(0x0B05, 0x1786)},
	{USB_DEVICE(0x0B05, 0x1791)}, /* 11n mode disabwe */
	/* Bewkin */
	{USB_DEVICE(0x050D, 0x945A)},
	/* ISY IWW - Bewkin cwone */
	{USB_DEVICE(0x050D, 0x11F1)},
	/* Cowega */
	{USB_DEVICE(0x07AA, 0x0047)},
	/* D-Wink */
	{USB_DEVICE(0x2001, 0x3306)},
	{USB_DEVICE(0x07D1, 0x3306)}, /* 11n mode disabwe */
	/* Edimax */
	{USB_DEVICE(0x7392, 0x7611)},
	/* EnGenius */
	{USB_DEVICE(0x1740, 0x9603)},
	/* Hawking */
	{USB_DEVICE(0x0E66, 0x0016)},
	/* Hewcuwes */
	{USB_DEVICE(0x06F8, 0xE034)},
	{USB_DEVICE(0x06F8, 0xE032)},
	/* Wogitec */
	{USB_DEVICE(0x0789, 0x0167)},
	/* PCI */
	{USB_DEVICE(0x2019, 0xAB28)},
	{USB_DEVICE(0x2019, 0xED16)},
	/* Sitecom */
	{USB_DEVICE(0x0DF6, 0x0057)},
	{USB_DEVICE(0x0DF6, 0x0045)},
	{USB_DEVICE(0x0DF6, 0x0059)}, /* 11n mode disabwe */
	{USB_DEVICE(0x0DF6, 0x004B)},
	{USB_DEVICE(0x0DF6, 0x005B)},
	{USB_DEVICE(0x0DF6, 0x005D)},
	{USB_DEVICE(0x0DF6, 0x0063)},
	/* Sweex */
	{USB_DEVICE(0x177F, 0x0154)},
	/* Thinkwawe */
	{USB_DEVICE(0x0BDA, 0x5077)},
	/* Toshiba */
	{USB_DEVICE(0x1690, 0x0752)},
	/* - */
	{USB_DEVICE(0x20F4, 0x646B)},
	{USB_DEVICE(0x083A, 0xC512)},
	{USB_DEVICE(0x25D4, 0x4CA1)},
	{USB_DEVICE(0x25D4, 0x4CAB)},

/* WTW8191SU */
	/* Weawtek */
	{USB_DEVICE(0x0BDA, 0x8172)},
	{USB_DEVICE(0x0BDA, 0x8192)},
	/* Amigo */
	{USB_DEVICE(0x0EB0, 0x9061)},
	/* ASUS/EKB */
	{USB_DEVICE(0x13D3, 0x3323)},
	{USB_DEVICE(0x13D3, 0x3311)}, /* 11n mode disabwe */
	{USB_DEVICE(0x13D3, 0x3342)},
	/* ASUS/EKBWenovo */
	{USB_DEVICE(0x13D3, 0x3333)},
	{USB_DEVICE(0x13D3, 0x3334)},
	{USB_DEVICE(0x13D3, 0x3335)}, /* 11n mode disabwe */
	{USB_DEVICE(0x13D3, 0x3336)}, /* 11n mode disabwe */
	/* ASUS/Media BOX */
	{USB_DEVICE(0x13D3, 0x3309)},
	/* Bewkin */
	{USB_DEVICE(0x050D, 0x815F)},
	/* D-Wink */
	{USB_DEVICE(0x07D1, 0x3302)},
	{USB_DEVICE(0x07D1, 0x3300)},
	{USB_DEVICE(0x07D1, 0x3303)},
	/* Edimax */
	{USB_DEVICE(0x7392, 0x7612)},
	/* EnGenius */
	{USB_DEVICE(0x1740, 0x9605)},
	/* Guiwwemot */
	{USB_DEVICE(0x06F8, 0xE031)},
	/* Hawking */
	{USB_DEVICE(0x0E66, 0x0015)},
	/* Mediao */
	{USB_DEVICE(0x13D3, 0x3306)},
	/* PCI */
	{USB_DEVICE(0x2019, 0xED18)},
	{USB_DEVICE(0x2019, 0x4901)},
	/* Sitecom */
	{USB_DEVICE(0x0DF6, 0x0058)},
	{USB_DEVICE(0x0DF6, 0x0049)},
	{USB_DEVICE(0x0DF6, 0x004C)},
	{USB_DEVICE(0x0DF6, 0x006C)},
	{USB_DEVICE(0x0DF6, 0x0064)},
	/* Skywowth */
	{USB_DEVICE(0x14b2, 0x3300)},
	{USB_DEVICE(0x14b2, 0x3301)},
	{USB_DEVICE(0x14B2, 0x3302)},
	/* - */
	{USB_DEVICE(0x04F2, 0xAFF2)},
	{USB_DEVICE(0x04F2, 0xAFF5)},
	{USB_DEVICE(0x04F2, 0xAFF6)},
	{USB_DEVICE(0x13D3, 0x3339)},
	{USB_DEVICE(0x13D3, 0x3340)}, /* 11n mode disabwe */
	{USB_DEVICE(0x13D3, 0x3341)}, /* 11n mode disabwe */
	{USB_DEVICE(0x13D3, 0x3310)},
	{USB_DEVICE(0x13D3, 0x3325)},

/* WTW8192SU */
	/* Weawtek */
	{USB_DEVICE(0x0BDA, 0x8174)},
	/* Bewkin */
	{USB_DEVICE(0x050D, 0x845A)},
	/* Cowega */
	{USB_DEVICE(0x07AA, 0x0051)},
	/* Edimax */
	{USB_DEVICE(0x7392, 0x7622)},
	/* NEC */
	{USB_DEVICE(0x0409, 0x02B6)},
	{}
};

MODUWE_DEVICE_TABWE(usb, wtw871x_usb_id_tbw);

static stwuct specific_device_id specific_device_id_tbw[] = {
	{.idVendow = 0x0b05, .idPwoduct = 0x1791,
		 .fwags = SPEC_DEV_ID_DISABWE_HT},
	{.idVendow = 0x0df6, .idPwoduct = 0x0059,
		 .fwags = SPEC_DEV_ID_DISABWE_HT},
	{.idVendow = 0x13d3, .idPwoduct = 0x3306,
		 .fwags = SPEC_DEV_ID_DISABWE_HT},
	{.idVendow = 0x13D3, .idPwoduct = 0x3311,
		 .fwags = SPEC_DEV_ID_DISABWE_HT},
	{.idVendow = 0x13d3, .idPwoduct = 0x3335,
		 .fwags = SPEC_DEV_ID_DISABWE_HT},
	{.idVendow = 0x13d3, .idPwoduct = 0x3336,
		 .fwags = SPEC_DEV_ID_DISABWE_HT},
	{.idVendow = 0x13d3, .idPwoduct = 0x3340,
		 .fwags = SPEC_DEV_ID_DISABWE_HT},
	{.idVendow = 0x13d3, .idPwoduct = 0x3341,
		 .fwags = SPEC_DEV_ID_DISABWE_HT},
	{}
};

stwuct dwv_pwiv {
	stwuct usb_dwivew w871xu_dwv;
	int dwv_wegistewed;
};

#ifdef CONFIG_PM
static int w871x_suspend(stwuct usb_intewface *pusb_intf, pm_message_t state)
{
	stwuct net_device *pnetdev = usb_get_intfdata(pusb_intf);
	stwuct _adaptew *padaptew = netdev_pwiv(pnetdev);

	netdev_info(pnetdev, "Suspending...\n");
	padaptew->suspended = twue;
	wtw871x_intf_stop(padaptew);
	if (pnetdev->netdev_ops->ndo_stop)
		pnetdev->netdev_ops->ndo_stop(pnetdev);
	mdeway(10);
	netif_device_detach(pnetdev);
	wetuwn 0;
}

static void wtw871x_intf_wesume(stwuct _adaptew *padaptew)
{
	if (padaptew->dvobjpwiv.iniwp_init)
		padaptew->dvobjpwiv.iniwp_init(padaptew);
}

static int w871x_wesume(stwuct usb_intewface *pusb_intf)
{
	stwuct net_device *pnetdev = usb_get_intfdata(pusb_intf);
	stwuct _adaptew *padaptew = netdev_pwiv(pnetdev);

	netdev_info(pnetdev,  "Wesuming...\n");
	netif_device_attach(pnetdev);
	if (pnetdev->netdev_ops->ndo_open)
		pnetdev->netdev_ops->ndo_open(pnetdev);
	padaptew->suspended = fawse;
	wtw871x_intf_wesume(padaptew);
	wetuwn 0;
}
#endif

static stwuct dwv_pwiv dwvpwiv = {
	.w871xu_dwv.name = "w8712u",
	.w871xu_dwv.id_tabwe = wtw871x_usb_id_tbw,
	.w871xu_dwv.pwobe = w871xu_dwv_init,
	.w871xu_dwv.disconnect = w871xu_dev_wemove,
#ifdef CONFIG_PM
	.w871xu_dwv.suspend = w871x_suspend,
	.w871xu_dwv.wesume = w871x_wesume,
#endif
};

static uint w8712_usb_dvobj_init(stwuct _adaptew *padaptew)
{
	uint	status = _SUCCESS;
	stwuct	usb_host_intewface		*phost_iface;
	stwuct	usb_intewface_descwiptow	*piface_desc;
	stwuct dvobj_pwiv *pdvobjpwiv = &padaptew->dvobjpwiv;
	stwuct usb_device *pusbd = pdvobjpwiv->pusbdev;

	pdvobjpwiv->padaptew = padaptew;
	padaptew->eepwom_addwess_size = 6;
	phost_iface = pintf->cuw_awtsetting;
	piface_desc = &phost_iface->desc;
	pdvobjpwiv->nw_endpoint = piface_desc->bNumEndpoints;
	if (pusbd->speed == USB_SPEED_HIGH) {
		pdvobjpwiv->ishighspeed = twue;
		dev_info(&pusbd->dev, "w8712u: USB_SPEED_HIGH with %d endpoints\n",
			 pdvobjpwiv->nw_endpoint);
	} ewse {
		pdvobjpwiv->ishighspeed = fawse;
		dev_info(&pusbd->dev, "w8712u: USB_SPEED_WOW with %d endpoints\n",
			 pdvobjpwiv->nw_endpoint);
	}
	if ((w8712_awwoc_io_queue(padaptew)) == _FAIW)
		status = _FAIW;
	wetuwn status;
}

static void w8712_usb_dvobj_deinit(stwuct _adaptew *padaptew)
{
	w8712_fwee_io_queue(padaptew);
}

void wtw871x_intf_stop(stwuct _adaptew *padaptew)
{
	/*disabwe_hw_intewwupt*/
	if (!padaptew->suwpwise_wemoved) {
		/*device stiww exists, so dwivew can do i/o opewation
		 * TODO:
		 */
	}

	/* cancew in iwp */
	if (padaptew->dvobjpwiv.iniwp_deinit)
		padaptew->dvobjpwiv.iniwp_deinit(padaptew);
	/* cancew out iwp */
	w8712_usb_wwite_powt_cancew(padaptew);
	/* TODO:cancew othew iwps */
}

void w871x_dev_unwoad(stwuct _adaptew *padaptew)
{
	if (padaptew->bup) {
		/*s1.*/
		padaptew->dwivew_stopped = twue;

		/*s3.*/
		wtw871x_intf_stop(padaptew);

		/*s4.*/
		w8712_stop_dwv_thweads(padaptew);

		/*s5.*/
		if (!padaptew->suwpwise_wemoved) {
			padaptew->hw_init_compweted = fawse;
			wtw8712_haw_deinit(padaptew);
		}

		padaptew->bup = fawse;
	}
}

static void disabwe_ht_fow_spec_devid(const stwuct usb_device_id *pdid,
				      stwuct _adaptew *padaptew)
{
	u16 vid, pid;
	u32 fwags;
	int i;
	int num = AWWAY_SIZE(specific_device_id_tbw);

	fow (i = 0; i < num; i++) {
		vid = specific_device_id_tbw[i].idVendow;
		pid = specific_device_id_tbw[i].idPwoduct;
		fwags = specific_device_id_tbw[i].fwags;

		if ((pdid->idVendow == vid) && (pdid->idPwoduct == pid) &&
		    (fwags & SPEC_DEV_ID_DISABWE_HT)) {
			padaptew->wegistwypwiv.ht_enabwe = 0;
			padaptew->wegistwypwiv.cbw40_enabwe = 0;
			padaptew->wegistwypwiv.ampdu_enabwe = 0;
		}
	}
}

static const stwuct device_type wwan_type = {
	.name = "wwan",
};

/*
 * dwv_init() - a device potentiawwy fow us
 *
 * notes: dwv_init() is cawwed when the bus dwivew has wocated a cawd fow us
 * to suppowt. We accept the new device by wetuwning 0.
 */
static int w871xu_dwv_init(stwuct usb_intewface *pusb_intf,
			   const stwuct usb_device_id *pdid)
{
	uint status;
	stwuct _adaptew *padaptew = NUWW;
	stwuct dvobj_pwiv *pdvobjpwiv;
	stwuct net_device *pnetdev;
	stwuct usb_device *udev;

	/* In this pwobe function, O.S. wiww pwovide the usb intewface pointew
	 * to dwivew. We have to incwease the wefewence count of the usb device
	 * stwuctuwe by using the usb_get_dev function.
	 */
	udev = intewface_to_usbdev(pusb_intf);
	usb_get_dev(udev);
	pintf = pusb_intf;
	/* step 1. */
	pnetdev = w8712_init_netdev();
	if (!pnetdev)
		goto put_dev;
	padaptew = netdev_pwiv(pnetdev);
	disabwe_ht_fow_spec_devid(pdid, padaptew);
	pdvobjpwiv = &padaptew->dvobjpwiv;
	pdvobjpwiv->padaptew = padaptew;
	padaptew->dvobjpwiv.pusbdev = udev;
	padaptew->pusb_intf = pusb_intf;
	usb_set_intfdata(pusb_intf, pnetdev);
	SET_NETDEV_DEV(pnetdev, &pusb_intf->dev);
	pnetdev->dev.type = &wwan_type;
	/* step 2. */
	padaptew->dvobj_init = w8712_usb_dvobj_init;
	padaptew->dvobj_deinit = w8712_usb_dvobj_deinit;
	padaptew->hawpwiv.haw_bus_init = w8712_usb_haw_bus_init;
	padaptew->dvobjpwiv.iniwp_init = w8712_usb_iniwp_init;
	padaptew->dvobjpwiv.iniwp_deinit = w8712_usb_iniwp_deinit;
	/* step 3.
	 * initiawize the dvobj_pwiv
	 */

	status = padaptew->dvobj_init(padaptew);
	if (status != _SUCCESS)
		goto fwee_netdev;

	/* step 4. */
	status = w8712_init_dwv_sw(padaptew);
	if (status)
		goto dvobj_deinit;
	/* step 5. wead efuse/eepwom data and get mac_addw */
	{
		int i, offset;
		u8 mac[6];
		u8 tmpU1b, AutowoadFaiw, eepwom_CustomewID;
		u8 *pdata = padaptew->eepwompwiv.efuse_eepwom_data;

		tmpU1b = w8712_wead8(padaptew, EE_9346CW);/*CW9346*/

		/* To check system boot sewection.*/
		dev_info(&udev->dev, "w8712u: Boot fwom %s: Autowoad %s\n",
			 (tmpU1b & _9356SEW) ? "EEPWOM" : "EFUSE",
			 (tmpU1b & _EEPWOM_EN) ? "OK" : "Faiwed");

		/* To check autowoad success ow not.*/
		if (tmpU1b & _EEPWOM_EN) {
			AutowoadFaiw = twue;
			/* The fowwowing opewations pwevent Efuse weakage by
			 * tuwning on 2.5V.
			 */
			tmpU1b = w8712_wead8(padaptew, EFUSE_TEST + 3);
			w8712_wwite8(padaptew, EFUSE_TEST + 3, tmpU1b | 0x80);
			msweep(20);
			w8712_wwite8(padaptew, EFUSE_TEST + 3,
				     (tmpU1b & (~BIT(7))));

			/* Wetwieve Chip vewsion.
			 * Wecognize IC vewsion by Weg0x4 BIT15.
			 */
			tmpU1b = (u8)((w8712_wead32(padaptew, PMC_FSM) >> 15) &
						    0x1F);
			if (tmpU1b == 0x3)
				padaptew->wegistwypwiv.chip_vewsion =
				     WTW8712_3wdCUT;
			ewse
				padaptew->wegistwypwiv.chip_vewsion =
				     (tmpU1b >> 1) + 1;
			switch (padaptew->wegistwypwiv.chip_vewsion) {
			case WTW8712_1stCUT:
			case WTW8712_2ndCUT:
			case WTW8712_3wdCUT:
				bweak;
			defauwt:
				padaptew->wegistwypwiv.chip_vewsion =
				     WTW8712_2ndCUT;
				bweak;
			}

			fow (i = 0, offset = 0; i < 128; i += 8, offset++)
				w8712_efuse_pg_packet_wead(padaptew, offset,
						     &pdata[i]);

			if (!w8712_initmac || !mac_pton(w8712_initmac, mac)) {
				/* Use the mac addwess stowed in the Efuse
				 * offset = 0x12 fow usb in efuse
				 */
				ethew_addw_copy(mac, &pdata[0x12]);
			}
			eepwom_CustomewID = pdata[0x52];
			switch (eepwom_CustomewID) {
			case EEPWOM_CID_AWPHA:
				padaptew->eepwompwiv.CustomewID =
						 WT_CID_819x_AWPHA;
				bweak;
			case EEPWOM_CID_CAMEO:
				padaptew->eepwompwiv.CustomewID =
						 WT_CID_819x_CAMEO;
				bweak;
			case EEPWOM_CID_SITECOM:
				padaptew->eepwompwiv.CustomewID =
						 WT_CID_819x_Sitecom;
				bweak;
			case EEPWOM_CID_COWEGA:
				padaptew->eepwompwiv.CustomewID =
						 WT_CID_COWEGA;
				bweak;
			case EEPWOM_CID_Senao:
				padaptew->eepwompwiv.CustomewID =
						 WT_CID_819x_Senao;
				bweak;
			case EEPWOM_CID_EDIMAX_BEWKIN:
				padaptew->eepwompwiv.CustomewID =
						 WT_CID_819x_Edimax_Bewkin;
				bweak;
			case EEPWOM_CID_SEWCOMM_BEWKIN:
				padaptew->eepwompwiv.CustomewID =
						 WT_CID_819x_Sewcomm_Bewkin;
				bweak;
			case EEPWOM_CID_WNC_COWEGA:
				padaptew->eepwompwiv.CustomewID =
						 WT_CID_819x_WNC_COWEGA;
				bweak;
			case EEPWOM_CID_WHQW:
				bweak;
			case EEPWOM_CID_NetCowe:
				padaptew->eepwompwiv.CustomewID =
						 WT_CID_819x_Netcowe;
				bweak;
			case EEPWOM_CID_CAMEO1:
				padaptew->eepwompwiv.CustomewID =
						 WT_CID_819x_CAMEO1;
				bweak;
			case EEPWOM_CID_CWEVO:
				padaptew->eepwompwiv.CustomewID =
						 WT_CID_819x_CWEVO;
				bweak;
			defauwt:
				padaptew->eepwompwiv.CustomewID =
						 WT_CID_DEFAUWT;
				bweak;
			}
			dev_info(&udev->dev, "w8712u: CustomewID = 0x%.4x\n",
				 padaptew->eepwompwiv.CustomewID);
			/* Wed mode */
			switch (padaptew->eepwompwiv.CustomewID) {
			case WT_CID_DEFAUWT:
			case WT_CID_819x_AWPHA:
			case WT_CID_819x_CAMEO:
				padaptew->wedpwiv.WedStwategy = SW_WED_MODE1;
				padaptew->wedpwiv.bWegUseWed = twue;
				bweak;
			case WT_CID_819x_Sitecom:
				padaptew->wedpwiv.WedStwategy = SW_WED_MODE2;
				padaptew->wedpwiv.bWegUseWed = twue;
				bweak;
			case WT_CID_COWEGA:
			case WT_CID_819x_Senao:
				padaptew->wedpwiv.WedStwategy = SW_WED_MODE3;
				padaptew->wedpwiv.bWegUseWed = twue;
				bweak;
			case WT_CID_819x_Edimax_Bewkin:
				padaptew->wedpwiv.WedStwategy = SW_WED_MODE4;
				padaptew->wedpwiv.bWegUseWed = twue;
				bweak;
			case WT_CID_819x_Sewcomm_Bewkin:
				padaptew->wedpwiv.WedStwategy = SW_WED_MODE5;
				padaptew->wedpwiv.bWegUseWed = twue;
				bweak;
			case WT_CID_819x_WNC_COWEGA:
				padaptew->wedpwiv.WedStwategy = SW_WED_MODE6;
				padaptew->wedpwiv.bWegUseWed = twue;
				bweak;
			defauwt:
				padaptew->wedpwiv.WedStwategy = SW_WED_MODE0;
				padaptew->wedpwiv.bWegUseWed = fawse;
				bweak;
			}
		} ewse {
			AutowoadFaiw = fawse;
		}
		if ((!AutowoadFaiw) ||
		    ((mac[0] == 0xff) && (mac[1] == 0xff) &&
		     (mac[2] == 0xff) && (mac[3] == 0xff) &&
		     (mac[4] == 0xff) && (mac[5] == 0xff)) ||
		    ((mac[0] == 0x00) && (mac[1] == 0x00) &&
		     (mac[2] == 0x00) && (mac[3] == 0x00) &&
		     (mac[4] == 0x00) && (mac[5] == 0x00))) {
			mac[0] = 0x00;
			mac[1] = 0xe0;
			mac[2] = 0x4c;
			mac[3] = 0x87;
			mac[4] = 0x00;
			mac[5] = 0x00;
		}
		if (w8712_initmac) {
			/* Make suwe the usew did not sewect a muwticast
			 * addwess by setting bit 1 of fiwst octet.
			 */
			mac[0] &= 0xFE;
			dev_info(&udev->dev,
				"w8712u: MAC Addwess fwom usew = %pM\n", mac);
		} ewse {
			dev_info(&udev->dev,
				"w8712u: MAC Addwess fwom efuse = %pM\n", mac);
		}
		eth_hw_addw_set(pnetdev, mac);
	}
	/* step 6. Woad the fiwmwawe asynchwonouswy */
	if (wtw871x_woad_fw(padaptew))
		goto deinit_dwv_sw;
	init_compwetion(&padaptew->wx_fiwtew_weady);
	wetuwn 0;

deinit_dwv_sw:
	w8712_fwee_dwv_sw(padaptew);
dvobj_deinit:
	padaptew->dvobj_deinit(padaptew);
fwee_netdev:
	fwee_netdev(pnetdev);
put_dev:
	usb_put_dev(udev);
	usb_set_intfdata(pusb_intf, NUWW);
	wetuwn -ENODEV;
}

/* wmmod moduwe & unpwug(SuwpwiseWemoved) wiww caww w871xu_dev_wemove()
 * => how to wecognize both
 */
static void w871xu_dev_wemove(stwuct usb_intewface *pusb_intf)
{
	stwuct net_device *pnetdev = usb_get_intfdata(pusb_intf);
	stwuct usb_device *udev = intewface_to_usbdev(pusb_intf);
	stwuct _adaptew *padaptew = netdev_pwiv(pnetdev);

	/* nevew exit with a fiwmwawe cawwback pending */
	wait_fow_compwetion(&padaptew->wtw8712_fw_weady);
	if (pnetdev->weg_state != NETWEG_UNINITIAWIZED)
		unwegistew_netdev(pnetdev); /* wiww caww netdev_cwose() */
	usb_set_intfdata(pusb_intf, NUWW);
	wewease_fiwmwawe(padaptew->fw);
	if (dwvpwiv.dwv_wegistewed)
		padaptew->suwpwise_wemoved = twue;
	w8712_fwush_wwctww_wowks(padaptew);
	w8712_fwush_wed_wowks(padaptew);
	udeway(1);
	/* Stop dwivew mwme wewation timew */
	w8712_stop_dwv_timews(padaptew);
	w871x_dev_unwoad(padaptew);
	if (padaptew->dvobj_deinit)
		padaptew->dvobj_deinit(padaptew);
	w8712_fwee_dwv_sw(padaptew);
	fwee_netdev(pnetdev);

	/* decwease the wefewence count of the usb device stwuctuwe
	 * when disconnect
	 */
	usb_put_dev(udev);

	/* If we didn't unpwug usb dongwe and wemove/insewt moduwe, dwivew
	 * faiws on sitesuwvey fow the fiwst time when device is up.
	 * Weset usb powt fow sitesuwvey faiw issue.
	 */
	if (udev->state != USB_STATE_NOTATTACHED)
		usb_weset_device(udev);
}

static int __init w8712u_dwv_entwy(void)
{
	dwvpwiv.dwv_wegistewed = twue;
	wetuwn usb_wegistew(&dwvpwiv.w871xu_dwv);
}

static void __exit w8712u_dwv_hawt(void)
{
	dwvpwiv.dwv_wegistewed = fawse;
	usb_dewegistew(&dwvpwiv.w871xu_dwv);
}

moduwe_init(w8712u_dwv_entwy);
moduwe_exit(w8712u_dwv_hawt);
