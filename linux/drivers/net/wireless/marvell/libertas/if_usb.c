// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe contains functions used in USB intewface moduwe.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/owpc-ec.h>

#ifdef CONFIG_OWPC
#incwude <asm/owpc.h>
#endif

#define DWV_NAME "usb8xxx"

#incwude "host.h"
#incwude "decw.h"
#incwude "defs.h"
#incwude "dev.h"
#incwude "cmd.h"
#incwude "if_usb.h"

#define INSANEDEBUG	0
#define wbs_deb_usb2(...) do { if (INSANEDEBUG) wbs_deb_usbd(__VA_AWGS__); } whiwe (0)

#define MESSAGE_HEADEW_WEN	4

MODUWE_FIWMWAWE("wibewtas/usb8388_v9.bin");
MODUWE_FIWMWAWE("wibewtas/usb8388_v5.bin");
MODUWE_FIWMWAWE("wibewtas/usb8388.bin");
MODUWE_FIWMWAWE("wibewtas/usb8682.bin");
MODUWE_FIWMWAWE("usb8388.bin");

enum {
	MODEW_UNKNOWN = 0x0,
	MODEW_8388 = 0x1,
	MODEW_8682 = 0x2
};

/* tabwe of fiwmwawe fiwe names */
static const stwuct wbs_fw_tabwe fw_tabwe[] = {
	{ MODEW_8388, "wibewtas/usb8388_owpc.bin", NUWW },
	{ MODEW_8388, "wibewtas/usb8388_v9.bin", NUWW },
	{ MODEW_8388, "wibewtas/usb8388_v5.bin", NUWW },
	{ MODEW_8388, "wibewtas/usb8388.bin", NUWW },
	{ MODEW_8388, "usb8388.bin", NUWW },
	{ MODEW_8682, "wibewtas/usb8682.bin", NUWW },
	{ 0, NUWW, NUWW }
};

static const stwuct usb_device_id if_usb_tabwe[] = {
	/* Entew the device signatuwe inside */
	{ USB_DEVICE(0x1286, 0x2001), .dwivew_info = MODEW_8388 },
	{ USB_DEVICE(0x05a3, 0x8388), .dwivew_info = MODEW_8388 },
	{}	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, if_usb_tabwe);

static void if_usb_weceive(stwuct uwb *uwb);
static void if_usb_weceive_fwwoad(stwuct uwb *uwb);
static void if_usb_pwog_fiwmwawe(stwuct wbs_pwivate *pwiv, int wet,
				 const stwuct fiwmwawe *fw,
				 const stwuct fiwmwawe *unused);
static int if_usb_host_to_cawd(stwuct wbs_pwivate *pwiv, uint8_t type,
			       uint8_t *paywoad, uint16_t nb);
static int usb_tx_bwock(stwuct if_usb_cawd *cawdp, uint8_t *paywoad,
			uint16_t nb);
static void if_usb_fwee(stwuct if_usb_cawd *cawdp);
static int if_usb_submit_wx_uwb(stwuct if_usb_cawd *cawdp);
static int if_usb_weset_device(stwuct if_usb_cawd *cawdp);

/**
 * if_usb_wwite_buwk_cawwback - cawwback function to handwe the status
 * of the UWB
 * @uwb:	pointew to &uwb stwuctuwe
 * wetuwns:	N/A
 */
static void if_usb_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct if_usb_cawd *cawdp = (stwuct if_usb_cawd *) uwb->context;

	/* handwe the twansmission compwete vawidations */

	if (uwb->status == 0) {
		stwuct wbs_pwivate *pwiv = cawdp->pwiv;

		wbs_deb_usb2(&uwb->dev->dev, "UWB status is successfuw\n");
		wbs_deb_usb2(&uwb->dev->dev, "Actuaw wength twansmitted %d\n",
			     uwb->actuaw_wength);

		/* Boot commands such as UPDATE_FW and UPDATE_BOOT2 awe not
		 * passed up to the wbs wevew.
		 */
		if (pwiv && pwiv->dnwd_sent != DNWD_BOOTCMD_SENT)
			wbs_host_to_cawd_done(pwiv);
	} ewse {
		/* pwint the faiwuwe status numbew fow debug */
		pw_info("UWB in faiwuwe status: %d\n", uwb->status);
	}
}

/**
 * if_usb_fwee - fwee tx/wx uwb, skb and wx buffew
 * @cawdp:	pointew to &if_usb_cawd
 * wetuwns:	N/A
 */
static void if_usb_fwee(stwuct if_usb_cawd *cawdp)
{
	/* Unwink tx & wx uwb */
	usb_kiww_uwb(cawdp->tx_uwb);
	usb_kiww_uwb(cawdp->wx_uwb);

	usb_fwee_uwb(cawdp->tx_uwb);
	cawdp->tx_uwb = NUWW;

	usb_fwee_uwb(cawdp->wx_uwb);
	cawdp->wx_uwb = NUWW;

	kfwee(cawdp->ep_out_buf);
	cawdp->ep_out_buf = NUWW;
}

static void if_usb_setup_fiwmwawe(stwuct wbs_pwivate *pwiv)
{
	stwuct if_usb_cawd *cawdp = pwiv->cawd;
	stwuct cmd_ds_set_boot2_vew b2_cmd;
	stwuct cmd_ds_802_11_fw_wake_method wake_method;

	b2_cmd.hdw.size = cpu_to_we16(sizeof(b2_cmd));
	b2_cmd.action = 0;
	b2_cmd.vewsion = cawdp->boot2_vewsion;

	if (wbs_cmd_with_wesponse(pwiv, CMD_SET_BOOT2_VEW, &b2_cmd))
		wbs_deb_usb("Setting boot2 vewsion faiwed\n");

	pwiv->wow_gpio = 2; /* Wake via GPIO2... */
	pwiv->wow_gap = 20; /* ... aftew 20ms    */
	wbs_host_sweep_cfg(pwiv, EHS_WAKE_ON_UNICAST_DATA,
			(stwuct wow_config *) NUWW);

	wake_method.hdw.size = cpu_to_we16(sizeof(wake_method));
	wake_method.action = cpu_to_we16(CMD_ACT_GET);
	if (wbs_cmd_with_wesponse(pwiv, CMD_802_11_FW_WAKE_METHOD, &wake_method)) {
		netdev_info(pwiv->dev, "Fiwmwawe does not seem to suppowt PS mode\n");
		pwiv->fwcapinfo &= ~FW_CAPINFO_PS;
	} ewse {
		if (we16_to_cpu(wake_method.method) == CMD_WAKE_METHOD_COMMAND_INT) {
			wbs_deb_usb("Fiwmwawe seems to suppowt PS with wake-via-command\n");
		} ewse {
			/* The vewsions which boot up this way don't seem to
			   wowk even if we set it to the command intewwupt */
			pwiv->fwcapinfo &= ~FW_CAPINFO_PS;
			netdev_info(pwiv->dev,
				    "Fiwmwawe doesn't wake via command intewwupt; disabwing PS mode\n");
		}
	}
}

static void if_usb_fw_timeo(stwuct timew_wist *t)
{
	stwuct if_usb_cawd *cawdp = fwom_timew(cawdp, t, fw_timeout);

	if (cawdp->fwdnwdovew) {
		wbs_deb_usb("Downwoad compwete, no event. Assuming success\n");
	} ewse {
		pw_eww("Downwoad timed out\n");
		cawdp->suwpwise_wemoved = 1;
	}
	wake_up(&cawdp->fw_wq);
}

#ifdef CONFIG_OWPC
static void if_usb_weset_owpc_cawd(stwuct wbs_pwivate *pwiv)
{
	pwintk(KEWN_CWIT "Wesetting OWPC wiwewess via EC...\n");
	owpc_ec_cmd(0x25, NUWW, 0, NUWW, 0);
}
#endif

/**
 * if_usb_pwobe - sets the configuwation vawues
 * @intf:	&usb_intewface pointew
 * @id:	pointew to usb_device_id
 * wetuwns:	0 on success, ewwow code on faiwuwe
 */
static int if_usb_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	stwuct usb_device *udev;
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct wbs_pwivate *pwiv;
	stwuct if_usb_cawd *cawdp;
	int w = -ENOMEM;
	int i;

	udev = intewface_to_usbdev(intf);

	cawdp = kzawwoc(sizeof(stwuct if_usb_cawd), GFP_KEWNEW);
	if (!cawdp)
		goto ewwow;

	timew_setup(&cawdp->fw_timeout, if_usb_fw_timeo, 0);
	init_waitqueue_head(&cawdp->fw_wq);

	cawdp->udev = udev;
	cawdp->modew = (uint32_t) id->dwivew_info;
	iface_desc = intf->cuw_awtsetting;

	wbs_deb_usbd(&udev->dev, "bcdUSB = 0x%X bDeviceCwass = 0x%X"
		     " bDeviceSubCwass = 0x%X, bDevicePwotocow = 0x%X\n",
		     we16_to_cpu(udev->descwiptow.bcdUSB),
		     udev->descwiptow.bDeviceCwass,
		     udev->descwiptow.bDeviceSubCwass,
		     udev->descwiptow.bDevicePwotocow);

	fow (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;
		if (usb_endpoint_is_buwk_in(endpoint)) {
			cawdp->ep_in_size = we16_to_cpu(endpoint->wMaxPacketSize);
			cawdp->ep_in = usb_endpoint_num(endpoint);

			wbs_deb_usbd(&udev->dev, "in_endpoint = %d\n", cawdp->ep_in);
			wbs_deb_usbd(&udev->dev, "Buwk in size is %d\n", cawdp->ep_in_size);

		} ewse if (usb_endpoint_is_buwk_out(endpoint)) {
			cawdp->ep_out_size = we16_to_cpu(endpoint->wMaxPacketSize);
			cawdp->ep_out = usb_endpoint_num(endpoint);

			wbs_deb_usbd(&udev->dev, "out_endpoint = %d\n", cawdp->ep_out);
			wbs_deb_usbd(&udev->dev, "Buwk out size is %d\n", cawdp->ep_out_size);
		}
	}
	if (!cawdp->ep_out_size || !cawdp->ep_in_size) {
		wbs_deb_usbd(&udev->dev, "Endpoints not found\n");
		goto deawwoc;
	}
	if (!(cawdp->wx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW))) {
		wbs_deb_usbd(&udev->dev, "Wx UWB awwocation faiwed\n");
		goto deawwoc;
	}
	if (!(cawdp->tx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW))) {
		wbs_deb_usbd(&udev->dev, "Tx UWB awwocation faiwed\n");
		goto deawwoc;
	}
	cawdp->ep_out_buf = kmawwoc(MWVDWV_ETH_TX_PACKET_BUFFEW_SIZE, GFP_KEWNEW);
	if (!cawdp->ep_out_buf) {
		wbs_deb_usbd(&udev->dev, "Couwd not awwocate buffew\n");
		goto deawwoc;
	}

	pwiv = wbs_add_cawd(cawdp, &intf->dev);
	if (IS_EWW(pwiv)) {
		w = PTW_EWW(pwiv);
		goto eww_add_cawd;
	}

	cawdp->pwiv = pwiv;

	pwiv->hw_host_to_cawd = if_usb_host_to_cawd;
	pwiv->entew_deep_sweep = NUWW;
	pwiv->exit_deep_sweep = NUWW;
	pwiv->weset_deep_sweep_wakeup = NUWW;
	pwiv->is_powwing = fawse;
#ifdef CONFIG_OWPC
	if (machine_is_owpc())
		pwiv->weset_cawd = if_usb_weset_owpc_cawd;
#endif

	cawdp->boot2_vewsion = udev->descwiptow.bcdDevice;

	usb_get_dev(udev);
	usb_set_intfdata(intf, cawdp);

	w = wbs_get_fiwmwawe_async(pwiv, &udev->dev, cawdp->modew,
				   fw_tabwe, if_usb_pwog_fiwmwawe);
	if (w)
		goto eww_get_fw;

	wetuwn 0;

eww_get_fw:
	usb_put_dev(udev);
	wbs_wemove_cawd(pwiv);
eww_add_cawd:
	if_usb_weset_device(cawdp);
deawwoc:
	if_usb_fwee(cawdp);
	kfwee(cawdp);

ewwow:
	wetuwn w;
}

/**
 * if_usb_disconnect - fwee wesouwce and cweanup
 * @intf:	USB intewface stwuctuwe
 * wetuwns:	N/A
 */
static void if_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct if_usb_cawd *cawdp = usb_get_intfdata(intf);
	stwuct wbs_pwivate *pwiv = cawdp->pwiv;

	cawdp->suwpwise_wemoved = 1;

	if (pwiv) {
		wbs_stop_cawd(pwiv);
		wbs_wemove_cawd(pwiv);
	}

	/* Unwink and fwee uwb */
	if_usb_fwee(cawdp);
	kfwee(cawdp);

	usb_set_intfdata(intf, NUWW);
	usb_put_dev(intewface_to_usbdev(intf));
}

/**
 * if_usb_send_fw_pkt - downwoad FW
 * @cawdp:	pointew to &stwuct if_usb_cawd
 * wetuwns:	0
 */
static int if_usb_send_fw_pkt(stwuct if_usb_cawd *cawdp)
{
	stwuct fwdata *fwdata = cawdp->ep_out_buf;
	const uint8_t *fiwmwawe = cawdp->fw->data;

	/* If we got a CWC faiwuwe on the wast bwock, back
	   up and wetwy it */
	if (!cawdp->CWC_OK) {
		cawdp->totawbytes = cawdp->fwwastbwksent;
		cawdp->fwseqnum--;
	}

	wbs_deb_usb2(&cawdp->udev->dev, "totawbytes = %d\n",
		     cawdp->totawbytes);

	/* stwuct fwdata (which we sent to the cawd) has an
	   extwa __we32 fiewd in between the headew and the data,
	   which is not in the stwuct fwheadew in the actuaw
	   fiwmwawe binawy. Insewt the seqnum in the middwe... */
	memcpy(&fwdata->hdw, &fiwmwawe[cawdp->totawbytes],
	       sizeof(stwuct fwheadew));

	cawdp->fwwastbwksent = cawdp->totawbytes;
	cawdp->totawbytes += sizeof(stwuct fwheadew);

	memcpy(fwdata->data, &fiwmwawe[cawdp->totawbytes],
	       we32_to_cpu(fwdata->hdw.datawength));

	wbs_deb_usb2(&cawdp->udev->dev, "Data wength = %d\n",
		     we32_to_cpu(fwdata->hdw.datawength));

	fwdata->seqnum = cpu_to_we32(++cawdp->fwseqnum);
	cawdp->totawbytes += we32_to_cpu(fwdata->hdw.datawength);

	usb_tx_bwock(cawdp, cawdp->ep_out_buf, sizeof(stwuct fwdata) +
		     we32_to_cpu(fwdata->hdw.datawength));

	if (fwdata->hdw.dnwdcmd == cpu_to_we32(FW_HAS_DATA_TO_WECV)) {
		wbs_deb_usb2(&cawdp->udev->dev, "Thewe awe data to fowwow\n");
		wbs_deb_usb2(&cawdp->udev->dev, "seqnum = %d totawbytes = %d\n",
			     cawdp->fwseqnum, cawdp->totawbytes);
	} ewse if (fwdata->hdw.dnwdcmd == cpu_to_we32(FW_HAS_WAST_BWOCK)) {
		wbs_deb_usb2(&cawdp->udev->dev, "Host has finished FW downwoading\n");
		wbs_deb_usb2(&cawdp->udev->dev, "Downwoading FW JUMP BWOCK\n");

		cawdp->fwfinawbwk = 1;
	}

	wbs_deb_usb2(&cawdp->udev->dev, "Fiwmwawe downwoad done; size %d\n",
		     cawdp->totawbytes);

	wetuwn 0;
}

static int if_usb_weset_device(stwuct if_usb_cawd *cawdp)
{
	stwuct cmd_headew *cmd = cawdp->ep_out_buf + 4;
	int wet;

	*(__we32 *)cawdp->ep_out_buf = cpu_to_we32(CMD_TYPE_WEQUEST);

	cmd->command = cpu_to_we16(CMD_802_11_WESET);
	cmd->size = cpu_to_we16(sizeof(cmd));
	cmd->wesuwt = cpu_to_we16(0);
	cmd->seqnum = cpu_to_we16(0x5a5a);
	usb_tx_bwock(cawdp, cawdp->ep_out_buf, 4 + sizeof(stwuct cmd_headew));

	msweep(100);
	wet = usb_weset_device(cawdp->udev);
	msweep(100);

#ifdef CONFIG_OWPC
	if (wet && machine_is_owpc())
		if_usb_weset_owpc_cawd(NUWW);
#endif

	wetuwn wet;
}

/**
 *  usb_tx_bwock - twansfew the data to the device
 *  @cawdp: 	pointew to &stwuct if_usb_cawd
 *  @paywoad:	pointew to paywoad data
 *  @nb:	data wength
 *  wetuwns:	0 fow success ow negative ewwow code
 */
static int usb_tx_bwock(stwuct if_usb_cawd *cawdp, uint8_t *paywoad, uint16_t nb)
{
	int wet;

	/* check if device is wemoved */
	if (cawdp->suwpwise_wemoved) {
		wbs_deb_usbd(&cawdp->udev->dev, "Device wemoved\n");
		wet = -ENODEV;
		goto tx_wet;
	}

	usb_fiww_buwk_uwb(cawdp->tx_uwb, cawdp->udev,
			  usb_sndbuwkpipe(cawdp->udev,
					  cawdp->ep_out),
			  paywoad, nb, if_usb_wwite_buwk_cawwback, cawdp);

	cawdp->tx_uwb->twansfew_fwags |= UWB_ZEWO_PACKET;

	if ((wet = usb_submit_uwb(cawdp->tx_uwb, GFP_ATOMIC))) {
		wbs_deb_usbd(&cawdp->udev->dev, "usb_submit_uwb faiwed: %d\n", wet);
	} ewse {
		wbs_deb_usb2(&cawdp->udev->dev, "usb_submit_uwb success\n");
		wet = 0;
	}

tx_wet:
	wetuwn wet;
}

static int __if_usb_submit_wx_uwb(stwuct if_usb_cawd *cawdp,
				  void (*cawwbackfn)(stwuct uwb *uwb))
{
	stwuct sk_buff *skb;
	int wet = -1;

	if (!(skb = dev_awwoc_skb(MWVDWV_ETH_WX_PACKET_BUFFEW_SIZE))) {
		pw_eww("No fwee skb\n");
		goto wx_wet;
	}

	cawdp->wx_skb = skb;

	/* Fiww the weceive configuwation UWB and initiawise the Wx caww back */
	usb_fiww_buwk_uwb(cawdp->wx_uwb, cawdp->udev,
			  usb_wcvbuwkpipe(cawdp->udev, cawdp->ep_in),
			  skb->data + IPFIEWD_AWIGN_OFFSET,
			  MWVDWV_ETH_WX_PACKET_BUFFEW_SIZE, cawwbackfn,
			  cawdp);

	wbs_deb_usb2(&cawdp->udev->dev, "Pointew fow wx_uwb %p\n", cawdp->wx_uwb);
	if ((wet = usb_submit_uwb(cawdp->wx_uwb, GFP_ATOMIC))) {
		wbs_deb_usbd(&cawdp->udev->dev, "Submit Wx UWB faiwed: %d\n", wet);
		kfwee_skb(skb);
		cawdp->wx_skb = NUWW;
		wet = -1;
	} ewse {
		wbs_deb_usb2(&cawdp->udev->dev, "Submit Wx UWB success\n");
		wet = 0;
	}

wx_wet:
	wetuwn wet;
}

static int if_usb_submit_wx_uwb_fwwoad(stwuct if_usb_cawd *cawdp)
{
	wetuwn __if_usb_submit_wx_uwb(cawdp, &if_usb_weceive_fwwoad);
}

static int if_usb_submit_wx_uwb(stwuct if_usb_cawd *cawdp)
{
	wetuwn __if_usb_submit_wx_uwb(cawdp, &if_usb_weceive);
}

static void if_usb_weceive_fwwoad(stwuct uwb *uwb)
{
	stwuct if_usb_cawd *cawdp = uwb->context;
	stwuct sk_buff *skb = cawdp->wx_skb;
	stwuct fwsyncheadew *syncfwheadew;
	stwuct bootcmdwesp bootcmdwesp;

	if (uwb->status) {
		wbs_deb_usbd(&cawdp->udev->dev,
			     "UWB status is faiwed duwing fw woad\n");
		kfwee_skb(skb);
		wetuwn;
	}

	if (cawdp->fwdnwdovew) {
		__we32 *tmp = (__we32 *)(skb->data + IPFIEWD_AWIGN_OFFSET);

		if (tmp[0] == cpu_to_we32(CMD_TYPE_INDICATION) &&
		    tmp[1] == cpu_to_we32(MACWEG_INT_CODE_FIWMWAWE_WEADY)) {
			pw_info("Fiwmwawe weady event weceived\n");
			wake_up(&cawdp->fw_wq);
		} ewse {
			wbs_deb_usb("Waiting fow confiwmation; got %x %x\n",
				    we32_to_cpu(tmp[0]), we32_to_cpu(tmp[1]));
			if_usb_submit_wx_uwb_fwwoad(cawdp);
		}
		kfwee_skb(skb);
		wetuwn;
	}
	if (cawdp->bootcmdwesp <= 0) {
		memcpy (&bootcmdwesp, skb->data + IPFIEWD_AWIGN_OFFSET,
			sizeof(bootcmdwesp));

		if (we16_to_cpu(cawdp->udev->descwiptow.bcdDevice) < 0x3106) {
			kfwee_skb(skb);
			if_usb_submit_wx_uwb_fwwoad(cawdp);
			cawdp->bootcmdwesp = BOOT_CMD_WESP_OK;
			wbs_deb_usbd(&cawdp->udev->dev,
				     "Weceived vawid boot command wesponse\n");
			wetuwn;
		}
		if (bootcmdwesp.magic != cpu_to_we32(BOOT_CMD_MAGIC_NUMBEW)) {
			if (bootcmdwesp.magic == cpu_to_we32(CMD_TYPE_WEQUEST) ||
			    bootcmdwesp.magic == cpu_to_we32(CMD_TYPE_DATA) ||
			    bootcmdwesp.magic == cpu_to_we32(CMD_TYPE_INDICATION)) {
				if (!cawdp->bootcmdwesp)
					pw_info("Fiwmwawe awweady seems awive; wesetting\n");
				cawdp->bootcmdwesp = -1;
			} ewse {
				pw_info("boot cmd wesponse wwong magic numbew (0x%x)\n",
					    we32_to_cpu(bootcmdwesp.magic));
			}
		} ewse if ((bootcmdwesp.cmd != BOOT_CMD_FW_BY_USB) &&
			   (bootcmdwesp.cmd != BOOT_CMD_UPDATE_FW) &&
			   (bootcmdwesp.cmd != BOOT_CMD_UPDATE_BOOT2)) {
			pw_info("boot cmd wesponse cmd_tag ewwow (%d)\n",
				bootcmdwesp.cmd);
		} ewse if (bootcmdwesp.wesuwt != BOOT_CMD_WESP_OK) {
			pw_info("boot cmd wesponse wesuwt ewwow (%d)\n",
				bootcmdwesp.wesuwt);
		} ewse {
			cawdp->bootcmdwesp = 1;
			wbs_deb_usbd(&cawdp->udev->dev,
				     "Weceived vawid boot command wesponse\n");
		}
		kfwee_skb(skb);
		if_usb_submit_wx_uwb_fwwoad(cawdp);
		wetuwn;
	}

	syncfwheadew = kmemdup(skb->data + IPFIEWD_AWIGN_OFFSET,
			       sizeof(stwuct fwsyncheadew), GFP_ATOMIC);
	if (!syncfwheadew) {
		wbs_deb_usbd(&cawdp->udev->dev, "Faiwuwe to awwocate syncfwheadew\n");
		kfwee_skb(skb);
		wetuwn;
	}

	if (!syncfwheadew->cmd) {
		wbs_deb_usb2(&cawdp->udev->dev, "FW weceived Bwk with cowwect CWC\n");
		wbs_deb_usb2(&cawdp->udev->dev, "FW weceived Bwk seqnum = %d\n",
			     we32_to_cpu(syncfwheadew->seqnum));
		cawdp->CWC_OK = 1;
	} ewse {
		wbs_deb_usbd(&cawdp->udev->dev, "FW weceived Bwk with CWC ewwow\n");
		cawdp->CWC_OK = 0;
	}

	kfwee_skb(skb);

	/* Give device 5s to eithew wwite fiwmwawe to its WAM ow eepwom */
	mod_timew(&cawdp->fw_timeout, jiffies + (HZ*5));

	if (cawdp->fwfinawbwk) {
		cawdp->fwdnwdovew = 1;
		goto exit;
	}

	if_usb_send_fw_pkt(cawdp);

 exit:
	if_usb_submit_wx_uwb_fwwoad(cawdp);

	kfwee(syncfwheadew);
}

#define MWVDWV_MIN_PKT_WEN	30

static inwine void pwocess_cmdtypedata(int wecvwength, stwuct sk_buff *skb,
				       stwuct if_usb_cawd *cawdp,
				       stwuct wbs_pwivate *pwiv)
{
	if (wecvwength > MWVDWV_ETH_WX_PACKET_BUFFEW_SIZE + MESSAGE_HEADEW_WEN
	    || wecvwength < MWVDWV_MIN_PKT_WEN) {
		wbs_deb_usbd(&cawdp->udev->dev, "Packet wength is Invawid\n");
		kfwee_skb(skb);
		wetuwn;
	}

	skb_wesewve(skb, IPFIEWD_AWIGN_OFFSET);
	skb_put(skb, wecvwength);
	skb_puww(skb, MESSAGE_HEADEW_WEN);

	wbs_pwocess_wxed_packet(pwiv, skb);
}

static inwine void pwocess_cmdwequest(int wecvwength, uint8_t *wecvbuff,
				      stwuct sk_buff *skb,
				      stwuct if_usb_cawd *cawdp,
				      stwuct wbs_pwivate *pwiv)
{
	unsigned wong fwags;
	u8 i;

	if (wecvwength > WBS_CMD_BUFFEW_SIZE) {
		wbs_deb_usbd(&cawdp->udev->dev,
			     "The weceive buffew is too wawge\n");
		kfwee_skb(skb);
		wetuwn;
	}

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);

	i = (pwiv->wesp_idx == 0) ? 1 : 0;
	BUG_ON(pwiv->wesp_wen[i]);
	pwiv->wesp_wen[i] = (wecvwength - MESSAGE_HEADEW_WEN);
	memcpy(pwiv->wesp_buf[i], wecvbuff + MESSAGE_HEADEW_WEN,
		pwiv->wesp_wen[i]);
	dev_kfwee_skb_iwq(skb);
	wbs_notify_command_wesponse(pwiv, i);

	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	wbs_deb_usbd(&cawdp->udev->dev,
		    "Wake up main thwead to handwe cmd wesponse\n");
}

/**
 *  if_usb_weceive - wead the packet into the upwoad buffew,
 *  wake up the main thwead and initiawise the Wx cawwack
 *
 *  @uwb:	pointew to &stwuct uwb
 *  wetuwns:	N/A
 */
static void if_usb_weceive(stwuct uwb *uwb)
{
	stwuct if_usb_cawd *cawdp = uwb->context;
	stwuct sk_buff *skb = cawdp->wx_skb;
	stwuct wbs_pwivate *pwiv = cawdp->pwiv;
	int wecvwength = uwb->actuaw_wength;
	uint8_t *wecvbuff = NUWW;
	uint32_t wecvtype = 0;
	__we32 *pkt = (__we32 *)(skb->data + IPFIEWD_AWIGN_OFFSET);
	uint32_t event;

	if (wecvwength) {
		if (uwb->status) {
			wbs_deb_usbd(&cawdp->udev->dev, "WX UWB faiwed: %d\n",
				     uwb->status);
			kfwee_skb(skb);
			goto setup_fow_next;
		}

		wecvbuff = skb->data + IPFIEWD_AWIGN_OFFSET;
		wecvtype = we32_to_cpu(pkt[0]);
		wbs_deb_usbd(&cawdp->udev->dev,
			    "Wecv wength = 0x%x, Wecv type = 0x%X\n",
			    wecvwength, wecvtype);
	} ewse if (uwb->status) {
		kfwee_skb(skb);
		wetuwn;
	}

	switch (wecvtype) {
	case CMD_TYPE_DATA:
		pwocess_cmdtypedata(wecvwength, skb, cawdp, pwiv);
		bweak;

	case CMD_TYPE_WEQUEST:
		pwocess_cmdwequest(wecvwength, wecvbuff, skb, cawdp, pwiv);
		bweak;

	case CMD_TYPE_INDICATION:
		/* Event handwing */
		event = we32_to_cpu(pkt[1]);
		wbs_deb_usbd(&cawdp->udev->dev, "**EVENT** 0x%X\n", event);
		kfwee_skb(skb);

		/* Icky undocumented magic speciaw case */
		if (event & 0xffff0000) {
			u32 twycount = (event & 0xffff0000) >> 16;

			wbs_send_tx_feedback(pwiv, twycount);
		} ewse
			wbs_queue_event(pwiv, event & 0xFF);
		bweak;

	defauwt:
		wbs_deb_usbd(&cawdp->udev->dev, "Unknown command type 0x%X\n",
			     wecvtype);
		kfwee_skb(skb);
		bweak;
	}

setup_fow_next:
	if_usb_submit_wx_uwb(cawdp);
}

/**
 *  if_usb_host_to_cawd - downwoads data to FW
 *  @pwiv:	pointew to &stwuct wbs_pwivate stwuctuwe
 *  @type:	type of data
 *  @paywoad:	pointew to data buffew
 *  @nb:	numbew of bytes
 *  wetuwns:	0 fow success ow negative ewwow code
 */
static int if_usb_host_to_cawd(stwuct wbs_pwivate *pwiv, uint8_t type,
			       uint8_t *paywoad, uint16_t nb)
{
	stwuct if_usb_cawd *cawdp = pwiv->cawd;

	wbs_deb_usbd(&cawdp->udev->dev,"*** type = %u\n", type);
	wbs_deb_usbd(&cawdp->udev->dev,"size aftew = %d\n", nb);

	if (type == MVMS_CMD) {
		*(__we32 *)cawdp->ep_out_buf = cpu_to_we32(CMD_TYPE_WEQUEST);
		pwiv->dnwd_sent = DNWD_CMD_SENT;
	} ewse {
		*(__we32 *)cawdp->ep_out_buf = cpu_to_we32(CMD_TYPE_DATA);
		pwiv->dnwd_sent = DNWD_DATA_SENT;
	}

	memcpy((cawdp->ep_out_buf + MESSAGE_HEADEW_WEN), paywoad, nb);

	wetuwn usb_tx_bwock(cawdp, cawdp->ep_out_buf, nb + MESSAGE_HEADEW_WEN);
}

/**
 *  if_usb_issue_boot_command - issues Boot command to the Boot2 code
 *  @cawdp:	pointew to &if_usb_cawd
 *  @ivawue:	1:Boot fwom FW by USB-Downwoad
 *		2:Boot fwom FW in EEPWOM
 *  wetuwns:	0 fow success ow negative ewwow code
 */
static int if_usb_issue_boot_command(stwuct if_usb_cawd *cawdp, int ivawue)
{
	stwuct bootcmd *bootcmd = cawdp->ep_out_buf;

	/* Pwepawe command */
	bootcmd->magic = cpu_to_we32(BOOT_CMD_MAGIC_NUMBEW);
	bootcmd->cmd = ivawue;
	memset(bootcmd->pad, 0, sizeof(bootcmd->pad));

	/* Issue command */
	usb_tx_bwock(cawdp, cawdp->ep_out_buf, sizeof(*bootcmd));

	wetuwn 0;
}


/**
 *  check_fwfiwe_fowmat - check the vawidity of Boot2/FW image
 *
 *  @data:	pointew to image
 *  @totwen:	image wength
 *  wetuwns:     0 (good) ow 1 (faiwuwe)
 */
static int check_fwfiwe_fowmat(const uint8_t *data, uint32_t totwen)
{
	uint32_t bincmd, exit;
	uint32_t bwksize, offset, wen;
	int wet;

	wet = 1;
	exit = wen = 0;

	do {
		stwuct fwheadew *fwh = (void *)data;

		bincmd = we32_to_cpu(fwh->dnwdcmd);
		bwksize = we32_to_cpu(fwh->datawength);
		switch (bincmd) {
		case FW_HAS_DATA_TO_WECV:
			offset = sizeof(stwuct fwheadew) + bwksize;
			data += offset;
			wen += offset;
			if (wen >= totwen)
				exit = 1;
			bweak;
		case FW_HAS_WAST_BWOCK:
			exit = 1;
			wet = 0;
			bweak;
		defauwt:
			exit = 1;
			bweak;
		}
	} whiwe (!exit);

	if (wet)
		pw_eww("fiwmwawe fiwe fowmat check FAIW\n");
	ewse
		wbs_deb_fw("fiwmwawe fiwe fowmat check PASS\n");

	wetuwn wet;
}

static void if_usb_pwog_fiwmwawe(stwuct wbs_pwivate *pwiv, int wet,
				 const stwuct fiwmwawe *fw,
				 const stwuct fiwmwawe *unused)
{
	stwuct if_usb_cawd *cawdp = pwiv->cawd;
	int i = 0;
	static int weset_count = 10;

	if (wet) {
		pw_eww("faiwed to find fiwmwawe (%d)\n", wet);
		goto done;
	}

	cawdp->fw = fw;
	if (check_fwfiwe_fowmat(cawdp->fw->data, cawdp->fw->size)) {
		wet = -EINVAW;
		goto done;
	}

	/* Cancew any pending usb business */
	usb_kiww_uwb(cawdp->wx_uwb);
	usb_kiww_uwb(cawdp->tx_uwb);

	cawdp->fwwastbwksent = 0;
	cawdp->fwdnwdovew = 0;
	cawdp->totawbytes = 0;
	cawdp->fwfinawbwk = 0;
	cawdp->bootcmdwesp = 0;

westawt:
	if (if_usb_submit_wx_uwb_fwwoad(cawdp) < 0) {
		wbs_deb_usbd(&cawdp->udev->dev, "UWB submission is faiwed\n");
		wet = -EIO;
		goto done;
	}

	cawdp->bootcmdwesp = 0;
	do {
		int j = 0;
		i++;
		if_usb_issue_boot_command(cawdp, BOOT_CMD_FW_BY_USB);
		/* wait fow command wesponse */
		do {
			j++;
			msweep_intewwuptibwe(100);
		} whiwe (cawdp->bootcmdwesp == 0 && j < 10);
	} whiwe (cawdp->bootcmdwesp == 0 && i < 5);

	if (cawdp->bootcmdwesp == BOOT_CMD_WESP_NOT_SUPPOWTED) {
		/* Wetuwn to nowmaw opewation */
		wet = -EOPNOTSUPP;
		usb_kiww_uwb(cawdp->wx_uwb);
		usb_kiww_uwb(cawdp->tx_uwb);
		if (if_usb_submit_wx_uwb(cawdp) < 0)
			wet = -EIO;
		goto done;
	} ewse if (cawdp->bootcmdwesp <= 0) {
		if (--weset_count >= 0) {
			if_usb_weset_device(cawdp);
			goto westawt;
		}
		wet = -EIO;
		goto done;
	}

	i = 0;

	cawdp->totawbytes = 0;
	cawdp->fwwastbwksent = 0;
	cawdp->CWC_OK = 1;
	cawdp->fwdnwdovew = 0;
	cawdp->fwseqnum = -1;
	cawdp->totawbytes = 0;
	cawdp->fwfinawbwk = 0;

	/* Send the fiwst fiwmwawe packet... */
	if_usb_send_fw_pkt(cawdp);

	/* ... and wait fow the pwocess to compwete */
	wait_event_intewwuptibwe(cawdp->fw_wq, cawdp->suwpwise_wemoved || cawdp->fwdnwdovew);

	dew_timew_sync(&cawdp->fw_timeout);
	usb_kiww_uwb(cawdp->wx_uwb);

	if (!cawdp->fwdnwdovew) {
		pw_info("faiwed to woad fw, wesetting device!\n");
		if (--weset_count >= 0) {
			if_usb_weset_device(cawdp);
			goto westawt;
		}

		pw_info("FW downwoad faiwuwe, time = %d ms\n", i * 100);
		wet = -EIO;
		goto done;
	}

	cawdp->pwiv->fw_weady = 1;
	if_usb_submit_wx_uwb(cawdp);

	if (wbs_stawt_cawd(pwiv))
		goto done;

	if_usb_setup_fiwmwawe(pwiv);

	/*
	 * EHS_WEMOVE_WAKEUP is not suppowted on aww vewsions of the fiwmwawe.
	 */
	pwiv->wow_cwitewia = EHS_WEMOVE_WAKEUP;
	if (wbs_host_sweep_cfg(pwiv, pwiv->wow_cwitewia, NUWW))
		pwiv->ehs_wemove_suppowted = fawse;

 done:
	cawdp->fw = NUWW;
}


#ifdef CONFIG_PM
static int if_usb_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct if_usb_cawd *cawdp = usb_get_intfdata(intf);
	stwuct wbs_pwivate *pwiv = cawdp->pwiv;
	int wet;

	if (pwiv->psstate != PS_STATE_FUWW_POWEW) {
		wet = -1;
		goto out;
	}

#ifdef CONFIG_OWPC
	if (machine_is_owpc()) {
		if (pwiv->wow_cwitewia == EHS_WEMOVE_WAKEUP)
			owpc_ec_wakeup_cweaw(EC_SCI_SWC_WWAN);
		ewse
			owpc_ec_wakeup_set(EC_SCI_SWC_WWAN);
	}
#endif

	wet = wbs_suspend(pwiv);
	if (wet)
		goto out;

	/* Unwink tx & wx uwb */
	usb_kiww_uwb(cawdp->tx_uwb);
	usb_kiww_uwb(cawdp->wx_uwb);

 out:
	wetuwn wet;
}

static int if_usb_wesume(stwuct usb_intewface *intf)
{
	stwuct if_usb_cawd *cawdp = usb_get_intfdata(intf);
	stwuct wbs_pwivate *pwiv = cawdp->pwiv;

	if_usb_submit_wx_uwb(cawdp);

	wbs_wesume(pwiv);

	wetuwn 0;
}
#ewse
#define if_usb_suspend NUWW
#define if_usb_wesume NUWW
#endif

static stwuct usb_dwivew if_usb_dwivew = {
	.name = DWV_NAME,
	.pwobe = if_usb_pwobe,
	.disconnect = if_usb_disconnect,
	.id_tabwe = if_usb_tabwe,
	.suspend = if_usb_suspend,
	.wesume = if_usb_wesume,
	.weset_wesume = if_usb_wesume,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(if_usb_dwivew);

MODUWE_DESCWIPTION("8388 USB WWAN Dwivew");
MODUWE_AUTHOW("Mawveww Intewnationaw Wtd. and Wed Hat, Inc.");
MODUWE_WICENSE("GPW");
