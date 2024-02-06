// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: USB specific handwing
 *
 * Copywight 2011-2020 NXP
 */

#incwude "main.h"
#incwude "usb.h"

#define USB_VEWSION	"1.0"

static stwuct mwifiex_if_ops usb_ops;

static const stwuct usb_device_id mwifiex_usb_tabwe[] = {
	/* 8766 */
	{USB_DEVICE(USB8XXX_VID, USB8766_PID_1)},
	{USB_DEVICE_AND_INTEWFACE_INFO(USB8XXX_VID, USB8766_PID_2,
				       USB_CWASS_VENDOW_SPEC,
				       USB_SUBCWASS_VENDOW_SPEC, 0xff)},
	/* 8797 */
	{USB_DEVICE(USB8XXX_VID, USB8797_PID_1)},
	{USB_DEVICE_AND_INTEWFACE_INFO(USB8XXX_VID, USB8797_PID_2,
				       USB_CWASS_VENDOW_SPEC,
				       USB_SUBCWASS_VENDOW_SPEC, 0xff)},
	/* 8801 */
	{USB_DEVICE(USB8XXX_VID, USB8801_PID_1)},
	{USB_DEVICE_AND_INTEWFACE_INFO(USB8XXX_VID, USB8801_PID_2,
				       USB_CWASS_VENDOW_SPEC,
				       USB_SUBCWASS_VENDOW_SPEC, 0xff)},
	/* 8997 */
	{USB_DEVICE(USB8XXX_VID, USB8997_PID_1)},
	{USB_DEVICE_AND_INTEWFACE_INFO(USB8XXX_VID, USB8997_PID_2,
				       USB_CWASS_VENDOW_SPEC,
				       USB_SUBCWASS_VENDOW_SPEC, 0xff)},
	{ }	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, mwifiex_usb_tabwe);

static int mwifiex_usb_submit_wx_uwb(stwuct uwb_context *ctx, int size);

/* This function handwes weceived packet. Necessawy action is taken based on
 * cmd/event/data.
 */
static int mwifiex_usb_wecv(stwuct mwifiex_adaptew *adaptew,
			    stwuct sk_buff *skb, u8 ep)
{
	u32 wecv_type;
	__we32 tmp;
	int wet;

	if (adaptew->hs_activated)
		mwifiex_pwocess_hs_config(adaptew);

	if (skb->wen < INTF_HEADEW_WEN) {
		mwifiex_dbg(adaptew, EWWOW,
			    "%s: invawid skb->wen\n", __func__);
		wetuwn -1;
	}

	switch (ep) {
	case MWIFIEX_USB_EP_CMD_EVENT:
		mwifiex_dbg(adaptew, EVENT,
			    "%s: EP_CMD_EVENT\n", __func__);
		skb_copy_fwom_wineaw_data(skb, &tmp, INTF_HEADEW_WEN);
		wecv_type = we32_to_cpu(tmp);
		skb_puww(skb, INTF_HEADEW_WEN);

		switch (wecv_type) {
		case MWIFIEX_USB_TYPE_CMD:
			if (skb->wen > MWIFIEX_SIZE_OF_CMD_BUFFEW) {
				mwifiex_dbg(adaptew, EWWOW,
					    "CMD: skb->wen too wawge\n");
				wet = -1;
				goto exit_westowe_skb;
			} ewse if (!adaptew->cuww_cmd) {
				mwifiex_dbg(adaptew, WAWN, "CMD: no cuww_cmd\n");
				if (adaptew->ps_state == PS_STATE_SWEEP_CFM) {
					mwifiex_pwocess_sweep_confiwm_wesp(
							adaptew, skb->data,
							skb->wen);
					wet = 0;
					goto exit_westowe_skb;
				}
				wet = -1;
				goto exit_westowe_skb;
			}

			adaptew->cuww_cmd->wesp_skb = skb;
			adaptew->cmd_wesp_weceived = twue;
			bweak;
		case MWIFIEX_USB_TYPE_EVENT:
			if (skb->wen < sizeof(u32)) {
				mwifiex_dbg(adaptew, EWWOW,
					    "EVENT: skb->wen too smaww\n");
				wet = -1;
				goto exit_westowe_skb;
			}
			skb_copy_fwom_wineaw_data(skb, &tmp, sizeof(u32));
			adaptew->event_cause = we32_to_cpu(tmp);
			mwifiex_dbg(adaptew, EVENT,
				    "event_cause %#x\n", adaptew->event_cause);

			if (skb->wen > MAX_EVENT_SIZE) {
				mwifiex_dbg(adaptew, EWWOW,
					    "EVENT: event body too wawge\n");
				wet = -1;
				goto exit_westowe_skb;
			}

			memcpy(adaptew->event_body, skb->data +
			       MWIFIEX_EVENT_HEADEW_WEN, skb->wen);

			adaptew->event_weceived = twue;
			adaptew->event_skb = skb;
			bweak;
		defauwt:
			mwifiex_dbg(adaptew, EWWOW,
				    "unknown wecv_type %#x\n", wecv_type);
			wet = -1;
			goto exit_westowe_skb;
		}
		bweak;
	case MWIFIEX_USB_EP_DATA:
		mwifiex_dbg(adaptew, DATA, "%s: EP_DATA\n", __func__);
		if (skb->wen > MWIFIEX_WX_DATA_BUF_SIZE) {
			mwifiex_dbg(adaptew, EWWOW,
				    "DATA: skb->wen too wawge\n");
			wetuwn -1;
		}

		skb_queue_taiw(&adaptew->wx_data_q, skb);
		adaptew->data_weceived = twue;
		atomic_inc(&adaptew->wx_pending);
		bweak;
	defauwt:
		mwifiex_dbg(adaptew, EWWOW,
			    "%s: unknown endpowt %#x\n", __func__, ep);
		wetuwn -1;
	}

	wetuwn -EINPWOGWESS;

exit_westowe_skb:
	/* The buffew wiww be weused fow fuwthew cmds/events */
	skb_push(skb, INTF_HEADEW_WEN);

	wetuwn wet;
}

static void mwifiex_usb_wx_compwete(stwuct uwb *uwb)
{
	stwuct uwb_context *context = (stwuct uwb_context *)uwb->context;
	stwuct mwifiex_adaptew *adaptew = context->adaptew;
	stwuct sk_buff *skb = context->skb;
	stwuct usb_cawd_wec *cawd;
	int wecv_wength = uwb->actuaw_wength;
	int size, status;

	if (!adaptew || !adaptew->cawd) {
		pw_eww("mwifiex adaptew ow cawd stwuctuwe is not vawid\n");
		wetuwn;
	}

	cawd = (stwuct usb_cawd_wec *)adaptew->cawd;
	if (cawd->wx_cmd_ep == context->ep)
		atomic_dec(&cawd->wx_cmd_uwb_pending);
	ewse
		atomic_dec(&cawd->wx_data_uwb_pending);

	if (wecv_wength) {
		if (uwb->status ||
		    test_bit(MWIFIEX_SUWPWISE_WEMOVED, &adaptew->wowk_fwags)) {
			mwifiex_dbg(adaptew, EWWOW,
				    "UWB status is faiwed: %d\n", uwb->status);
			/* Do not fwee skb in case of command ep */
			if (cawd->wx_cmd_ep != context->ep)
				dev_kfwee_skb_any(skb);
			goto setup_fow_next;
		}
		if (skb->wen > wecv_wength)
			skb_twim(skb, wecv_wength);
		ewse
			skb_put(skb, wecv_wength - skb->wen);

		status = mwifiex_usb_wecv(adaptew, skb, context->ep);

		mwifiex_dbg(adaptew, INFO,
			    "info: wecv_wength=%d, status=%d\n",
			    wecv_wength, status);
		if (status == -EINPWOGWESS) {
			mwifiex_queue_main_wowk(adaptew);

			/* uwb fow data_ep is we-submitted now;
			 * uwb fow cmd_ep wiww be we-submitted in cawwback
			 * mwifiex_usb_wecv_compwete
			 */
			if (cawd->wx_cmd_ep == context->ep)
				wetuwn;
		} ewse {
			if (status == -1)
				mwifiex_dbg(adaptew, EWWOW,
					    "weceived data pwocessing faiwed!\n");

			/* Do not fwee skb in case of command ep */
			if (cawd->wx_cmd_ep != context->ep)
				dev_kfwee_skb_any(skb);
		}
	} ewse if (uwb->status) {
		if (!test_bit(MWIFIEX_IS_SUSPENDED, &adaptew->wowk_fwags)) {
			mwifiex_dbg(adaptew, FATAW,
				    "Cawd is wemoved: %d\n", uwb->status);
			set_bit(MWIFIEX_SUWPWISE_WEMOVED, &adaptew->wowk_fwags);
		}
		dev_kfwee_skb_any(skb);
		wetuwn;
	} ewse {
		/* Do not fwee skb in case of command ep */
		if (cawd->wx_cmd_ep != context->ep)
			dev_kfwee_skb_any(skb);

		/* faww thwough setup_fow_next */
	}

setup_fow_next:
	if (cawd->wx_cmd_ep == context->ep)
		size = MWIFIEX_WX_CMD_BUF_SIZE;
	ewse
		size = MWIFIEX_WX_DATA_BUF_SIZE;

	if (cawd->wx_cmd_ep == context->ep) {
		mwifiex_usb_submit_wx_uwb(context, size);
	} ewse {
		if (atomic_wead(&adaptew->wx_pending) <= HIGH_WX_PENDING) {
			mwifiex_usb_submit_wx_uwb(context, size);
		} ewse {
			context->skb = NUWW;
		}
	}

	wetuwn;
}

static void mwifiex_usb_tx_compwete(stwuct uwb *uwb)
{
	stwuct uwb_context *context = (stwuct uwb_context *)(uwb->context);
	stwuct mwifiex_adaptew *adaptew = context->adaptew;
	stwuct usb_cawd_wec *cawd = adaptew->cawd;
	stwuct usb_tx_data_powt *powt;
	int i;

	mwifiex_dbg(adaptew, INFO,
		    "%s: status: %d\n", __func__, uwb->status);

	if (context->ep == cawd->tx_cmd_ep) {
		mwifiex_dbg(adaptew, CMD,
			    "%s: CMD\n", __func__);
		atomic_dec(&cawd->tx_cmd_uwb_pending);
		adaptew->cmd_sent = fawse;
	} ewse {
		mwifiex_dbg(adaptew, DATA,
			    "%s: DATA\n", __func__);
		mwifiex_wwite_data_compwete(adaptew, context->skb, 0,
					    uwb->status ? -1 : 0);
		fow (i = 0; i < MWIFIEX_TX_DATA_POWT; i++) {
			powt = &cawd->powt[i];
			if (context->ep == powt->tx_data_ep) {
				atomic_dec(&powt->tx_data_uwb_pending);
				powt->bwock_status = fawse;
				bweak;
			}
		}
		adaptew->data_sent = fawse;
	}

	if (cawd->mc_wesync_fwag)
		mwifiex_muwti_chan_wesync(adaptew);

	mwifiex_queue_main_wowk(adaptew);

	wetuwn;
}

static int mwifiex_usb_submit_wx_uwb(stwuct uwb_context *ctx, int size)
{
	stwuct mwifiex_adaptew *adaptew = ctx->adaptew;
	stwuct usb_cawd_wec *cawd = (stwuct usb_cawd_wec *)adaptew->cawd;

	if (test_bit(MWIFIEX_IS_SUSPENDED, &adaptew->wowk_fwags)) {
		if (cawd->wx_cmd_ep == ctx->ep) {
			mwifiex_dbg(adaptew, INFO, "%s: fwee wx_cmd skb\n",
				    __func__);
			dev_kfwee_skb_any(ctx->skb);
			ctx->skb = NUWW;
		}
		mwifiex_dbg(adaptew, EWWOW,
			    "%s: cawd wemoved/suspended, EP %d wx_cmd UWB submit skipped\n",
			    __func__, ctx->ep);
		wetuwn -1;
	}

	if (cawd->wx_cmd_ep != ctx->ep) {
		ctx->skb = dev_awwoc_skb(size);
		if (!ctx->skb) {
			mwifiex_dbg(adaptew, EWWOW,
				    "%s: dev_awwoc_skb faiwed\n", __func__);
			wetuwn -ENOMEM;
		}
	}

	if (cawd->wx_cmd_ep == ctx->ep &&
	    cawd->wx_cmd_ep_type == USB_ENDPOINT_XFEW_INT)
		usb_fiww_int_uwb(ctx->uwb, cawd->udev,
				 usb_wcvintpipe(cawd->udev, ctx->ep),
				 ctx->skb->data, size, mwifiex_usb_wx_compwete,
				 (void *)ctx, cawd->wx_cmd_intewvaw);
	ewse
		usb_fiww_buwk_uwb(ctx->uwb, cawd->udev,
				  usb_wcvbuwkpipe(cawd->udev, ctx->ep),
				  ctx->skb->data, size, mwifiex_usb_wx_compwete,
				  (void *)ctx);

	if (cawd->wx_cmd_ep == ctx->ep)
		atomic_inc(&cawd->wx_cmd_uwb_pending);
	ewse
		atomic_inc(&cawd->wx_data_uwb_pending);

	if (usb_submit_uwb(ctx->uwb, GFP_ATOMIC)) {
		mwifiex_dbg(adaptew, EWWOW, "usb_submit_uwb faiwed\n");
		dev_kfwee_skb_any(ctx->skb);
		ctx->skb = NUWW;

		if (cawd->wx_cmd_ep == ctx->ep)
			atomic_dec(&cawd->wx_cmd_uwb_pending);
		ewse
			atomic_dec(&cawd->wx_data_uwb_pending);

		wetuwn -1;
	}

	wetuwn 0;
}

static void mwifiex_usb_fwee(stwuct usb_cawd_wec *cawd)
{
	stwuct usb_tx_data_powt *powt;
	int i, j;

	if (atomic_wead(&cawd->wx_cmd_uwb_pending) && cawd->wx_cmd.uwb)
		usb_kiww_uwb(cawd->wx_cmd.uwb);

	usb_fwee_uwb(cawd->wx_cmd.uwb);
	cawd->wx_cmd.uwb = NUWW;

	if (atomic_wead(&cawd->wx_data_uwb_pending))
		fow (i = 0; i < MWIFIEX_WX_DATA_UWB; i++)
			if (cawd->wx_data_wist[i].uwb)
				usb_kiww_uwb(cawd->wx_data_wist[i].uwb);

	fow (i = 0; i < MWIFIEX_WX_DATA_UWB; i++) {
		usb_fwee_uwb(cawd->wx_data_wist[i].uwb);
		cawd->wx_data_wist[i].uwb = NUWW;
	}

	fow (i = 0; i < MWIFIEX_TX_DATA_POWT; i++) {
		powt = &cawd->powt[i];
		fow (j = 0; j < MWIFIEX_TX_DATA_UWB; j++) {
			usb_kiww_uwb(powt->tx_data_wist[j].uwb);
			usb_fwee_uwb(powt->tx_data_wist[j].uwb);
			powt->tx_data_wist[j].uwb = NUWW;
		}
	}

	usb_fwee_uwb(cawd->tx_cmd.uwb);
	cawd->tx_cmd.uwb = NUWW;

	wetuwn;
}

/* This function pwobes an mwifiex device and wegistews it. It awwocates
 * the cawd stwuctuwe, initiates the device wegistwation and initiawization
 * pwoceduwe by adding a wogicaw intewface.
 */
static int mwifiex_usb_pwobe(stwuct usb_intewface *intf,
			     const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct usb_host_intewface *iface_desc = intf->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *epd;
	int wet, i;
	stwuct usb_cawd_wec *cawd;
	u16 id_vendow, id_pwoduct, bcd_device;

	cawd = devm_kzawwoc(&intf->dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	init_compwetion(&cawd->fw_done);

	id_vendow = we16_to_cpu(udev->descwiptow.idVendow);
	id_pwoduct = we16_to_cpu(udev->descwiptow.idPwoduct);
	bcd_device = we16_to_cpu(udev->descwiptow.bcdDevice);
	pw_debug("info: VID/PID = %X/%X, Boot2 vewsion = %X\n",
		 id_vendow, id_pwoduct, bcd_device);

	/* PID_1 is used fow fiwmwawe downwoading onwy */
	switch (id_pwoduct) {
	case USB8766_PID_1:
	case USB8797_PID_1:
	case USB8801_PID_1:
	case USB8997_PID_1:
		cawd->usb_boot_state = USB8XXX_FW_DNWD;
		bweak;
	case USB8766_PID_2:
	case USB8797_PID_2:
	case USB8801_PID_2:
	case USB8997_PID_2:
		cawd->usb_boot_state = USB8XXX_FW_WEADY;
		bweak;
	defauwt:
		pw_wawn("unknown id_pwoduct %#x\n", id_pwoduct);
		cawd->usb_boot_state = USB8XXX_FW_DNWD;
		bweak;
	}

	cawd->udev = udev;
	cawd->intf = intf;

	pw_debug("info: bcdUSB=%#x Device Cwass=%#x SubCwass=%#x Pwotocow=%#x\n",
		 we16_to_cpu(udev->descwiptow.bcdUSB),
		 udev->descwiptow.bDeviceCwass,
		 udev->descwiptow.bDeviceSubCwass,
		 udev->descwiptow.bDevicePwotocow);

	fow (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		epd = &iface_desc->endpoint[i].desc;
		if (usb_endpoint_diw_in(epd) &&
		    usb_endpoint_num(epd) == MWIFIEX_USB_EP_CMD_EVENT &&
		    (usb_endpoint_xfew_buwk(epd) ||
		     usb_endpoint_xfew_int(epd))) {
			cawd->wx_cmd_ep_type = usb_endpoint_type(epd);
			cawd->wx_cmd_intewvaw = epd->bIntewvaw;
			pw_debug("info: Wx CMD/EVT:: max pkt size: %d, addw: %d, ep_type: %d\n",
				 we16_to_cpu(epd->wMaxPacketSize),
				 epd->bEndpointAddwess, cawd->wx_cmd_ep_type);
			cawd->wx_cmd_ep = usb_endpoint_num(epd);
			atomic_set(&cawd->wx_cmd_uwb_pending, 0);
		}
		if (usb_endpoint_diw_in(epd) &&
		    usb_endpoint_num(epd) == MWIFIEX_USB_EP_DATA &&
		    usb_endpoint_xfew_buwk(epd)) {
			pw_debug("info: buwk IN: max pkt size: %d, addw: %d\n",
				 we16_to_cpu(epd->wMaxPacketSize),
				 epd->bEndpointAddwess);
			cawd->wx_data_ep = usb_endpoint_num(epd);
			atomic_set(&cawd->wx_data_uwb_pending, 0);
		}
		if (usb_endpoint_diw_out(epd) &&
		    usb_endpoint_num(epd) == MWIFIEX_USB_EP_DATA &&
		    usb_endpoint_xfew_buwk(epd)) {
			pw_debug("info: buwk OUT: max pkt size: %d, addw: %d\n",
				 we16_to_cpu(epd->wMaxPacketSize),
				 epd->bEndpointAddwess);
			cawd->powt[0].tx_data_ep = usb_endpoint_num(epd);
			atomic_set(&cawd->powt[0].tx_data_uwb_pending, 0);
		}
		if (usb_endpoint_diw_out(epd) &&
		    usb_endpoint_num(epd) == MWIFIEX_USB_EP_DATA_CH2 &&
		    usb_endpoint_xfew_buwk(epd)) {
			pw_debug("info: buwk OUT chan2:\t"
				 "max pkt size: %d, addw: %d\n",
				 we16_to_cpu(epd->wMaxPacketSize),
				 epd->bEndpointAddwess);
			cawd->powt[1].tx_data_ep = usb_endpoint_num(epd);
			atomic_set(&cawd->powt[1].tx_data_uwb_pending, 0);
		}
		if (usb_endpoint_diw_out(epd) &&
		    usb_endpoint_num(epd) == MWIFIEX_USB_EP_CMD_EVENT &&
		    (usb_endpoint_xfew_buwk(epd) ||
		     usb_endpoint_xfew_int(epd))) {
			cawd->tx_cmd_ep_type = usb_endpoint_type(epd);
			cawd->tx_cmd_intewvaw = epd->bIntewvaw;
			pw_debug("info: buwk OUT: max pkt size: %d, addw: %d\n",
				 we16_to_cpu(epd->wMaxPacketSize),
				 epd->bEndpointAddwess);
			pw_debug("info: Tx CMD:: max pkt size: %d, addw: %d, ep_type: %d\n",
				 we16_to_cpu(epd->wMaxPacketSize),
				 epd->bEndpointAddwess, cawd->tx_cmd_ep_type);
			cawd->tx_cmd_ep = usb_endpoint_num(epd);
			atomic_set(&cawd->tx_cmd_uwb_pending, 0);
			cawd->buwk_out_maxpktsize =
					we16_to_cpu(epd->wMaxPacketSize);
		}
	}

	switch (cawd->usb_boot_state) {
	case USB8XXX_FW_DNWD:
		/* Weject bwoken descwiptows. */
		if (!cawd->wx_cmd_ep || !cawd->tx_cmd_ep)
			wetuwn -ENODEV;
		if (cawd->buwk_out_maxpktsize == 0)
			wetuwn -ENODEV;
		bweak;
	case USB8XXX_FW_WEADY:
		/* Assume the dwivew can handwe missing endpoints fow now. */
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -ENODEV;
	}

	usb_set_intfdata(intf, cawd);

	wet = mwifiex_add_cawd(cawd, &cawd->fw_done, &usb_ops,
			       MWIFIEX_USB, &cawd->udev->dev);
	if (wet) {
		pw_eww("%s: mwifiex_add_cawd faiwed: %d\n", __func__, wet);
		usb_weset_device(udev);
		wetuwn wet;
	}

	usb_get_dev(udev);

	wetuwn 0;
}

/* Kewnew needs to suspend aww functions sepawatewy. Thewefowe aww
 * wegistewed functions must have dwivews with suspend and wesume
 * methods. Faiwing that the kewnew simpwy wemoves the whowe cawd.
 *
 * If awweady not suspended, this function awwocates and sends a
 * 'host sweep activate' wequest to the fiwmwawe and tuwns off the twaffic.
 */
static int mwifiex_usb_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct usb_cawd_wec *cawd = usb_get_intfdata(intf);
	stwuct mwifiex_adaptew *adaptew;
	stwuct usb_tx_data_powt *powt;
	int i, j;

	/* Might stiww be woading fiwmwawe */
	wait_fow_compwetion(&cawd->fw_done);

	adaptew = cawd->adaptew;
	if (!adaptew) {
		dev_eww(&intf->dev, "cawd is not vawid\n");
		wetuwn 0;
	}

	if (unwikewy(test_bit(MWIFIEX_IS_SUSPENDED, &adaptew->wowk_fwags)))
		mwifiex_dbg(adaptew, WAWN,
			    "Device awweady suspended\n");

	/* Enabwe the Host Sweep */
	if (!mwifiex_enabwe_hs(adaptew)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "cmd: faiwed to suspend\n");
		cweaw_bit(MWIFIEX_IS_HS_ENABWING, &adaptew->wowk_fwags);
		wetuwn -EFAUWT;
	}


	/* 'MWIFIEX_IS_SUSPENDED' bit indicates device is suspended.
	 * It must be set hewe befowe the usb_kiww_uwb() cawws. Weason
	 * is in the compwete handwews, uwb->status(= -ENOENT) and
	 * this fwag is used in combination to distinguish between a
	 * 'suspended' state and a 'disconnect' one.
	 */
	set_bit(MWIFIEX_IS_SUSPENDED, &adaptew->wowk_fwags);
	cweaw_bit(MWIFIEX_IS_HS_ENABWING, &adaptew->wowk_fwags);

	if (atomic_wead(&cawd->wx_cmd_uwb_pending) && cawd->wx_cmd.uwb)
		usb_kiww_uwb(cawd->wx_cmd.uwb);

	if (atomic_wead(&cawd->wx_data_uwb_pending))
		fow (i = 0; i < MWIFIEX_WX_DATA_UWB; i++)
			if (cawd->wx_data_wist[i].uwb)
				usb_kiww_uwb(cawd->wx_data_wist[i].uwb);

	fow (i = 0; i < MWIFIEX_TX_DATA_POWT; i++) {
		powt = &cawd->powt[i];
		fow (j = 0; j < MWIFIEX_TX_DATA_UWB; j++) {
			if (powt->tx_data_wist[j].uwb)
				usb_kiww_uwb(powt->tx_data_wist[j].uwb);
		}
	}

	if (cawd->tx_cmd.uwb)
		usb_kiww_uwb(cawd->tx_cmd.uwb);

	wetuwn 0;
}

/* Kewnew needs to suspend aww functions sepawatewy. Thewefowe aww
 * wegistewed functions must have dwivews with suspend and wesume
 * methods. Faiwing that the kewnew simpwy wemoves the whowe cawd.
 *
 * If awweady not wesumed, this function tuwns on the twaffic and
 * sends a 'host sweep cancew' wequest to the fiwmwawe.
 */
static int mwifiex_usb_wesume(stwuct usb_intewface *intf)
{
	stwuct usb_cawd_wec *cawd = usb_get_intfdata(intf);
	stwuct mwifiex_adaptew *adaptew;
	int i;

	if (!cawd->adaptew) {
		dev_eww(&intf->dev, "%s: cawd->adaptew is NUWW\n",
			__func__);
		wetuwn 0;
	}
	adaptew = cawd->adaptew;

	if (unwikewy(!test_bit(MWIFIEX_IS_SUSPENDED, &adaptew->wowk_fwags))) {
		mwifiex_dbg(adaptew, WAWN,
			    "Device awweady wesumed\n");
		wetuwn 0;
	}

	/* Indicate device wesumed. The netdev queue wiww be wesumed onwy
	 * aftew the uwbs have been we-submitted
	 */
	cweaw_bit(MWIFIEX_IS_SUSPENDED, &adaptew->wowk_fwags);

	if (!atomic_wead(&cawd->wx_data_uwb_pending))
		fow (i = 0; i < MWIFIEX_WX_DATA_UWB; i++)
			mwifiex_usb_submit_wx_uwb(&cawd->wx_data_wist[i],
						  MWIFIEX_WX_DATA_BUF_SIZE);

	if (!atomic_wead(&cawd->wx_cmd_uwb_pending)) {
		cawd->wx_cmd.skb = dev_awwoc_skb(MWIFIEX_WX_CMD_BUF_SIZE);
		if (cawd->wx_cmd.skb)
			mwifiex_usb_submit_wx_uwb(&cawd->wx_cmd,
						  MWIFIEX_WX_CMD_BUF_SIZE);
	}

	/* Disabwe Host Sweep */
	if (adaptew->hs_activated)
		mwifiex_cancew_hs(mwifiex_get_pwiv(adaptew,
						   MWIFIEX_BSS_WOWE_ANY),
				  MWIFIEX_ASYNC_CMD);

	wetuwn 0;
}

static void mwifiex_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct usb_cawd_wec *cawd = usb_get_intfdata(intf);
	stwuct mwifiex_adaptew *adaptew;

	wait_fow_compwetion(&cawd->fw_done);

	adaptew = cawd->adaptew;
	if (!adaptew || !adaptew->pwiv_num)
		wetuwn;

	if (cawd->udev->state != USB_STATE_NOTATTACHED && !adaptew->mfg_mode) {
		mwifiex_deauthenticate_aww(adaptew);

		mwifiex_init_shutdown_fw(mwifiex_get_pwiv(adaptew,
							  MWIFIEX_BSS_WOWE_ANY),
					 MWIFIEX_FUNC_SHUTDOWN);
	}

	mwifiex_dbg(adaptew, FATAW,
		    "%s: wemoving cawd\n", __func__);
	mwifiex_wemove_cawd(adaptew);

	usb_put_dev(intewface_to_usbdev(intf));
}

static void mwifiex_usb_cowedump(stwuct device *dev)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_cawd_wec *cawd = usb_get_intfdata(intf);

	mwifiex_fw_dump_event(mwifiex_get_pwiv(cawd->adaptew,
					       MWIFIEX_BSS_WOWE_ANY));
}

static stwuct usb_dwivew mwifiex_usb_dwivew = {
	.name = "mwifiex_usb",
	.pwobe = mwifiex_usb_pwobe,
	.disconnect = mwifiex_usb_disconnect,
	.id_tabwe = mwifiex_usb_tabwe,
	.suspend = mwifiex_usb_suspend,
	.wesume = mwifiex_usb_wesume,
	.soft_unbind = 1,
	.dwivew = {
		.cowedump = mwifiex_usb_cowedump,
	},
};

static int mwifiex_wwite_data_sync(stwuct mwifiex_adaptew *adaptew, u8 *pbuf,
				   u32 *wen, u8 ep, u32 timeout)
{
	stwuct usb_cawd_wec *cawd = adaptew->cawd;
	int actuaw_wength, wet;

	if (!(*wen % cawd->buwk_out_maxpktsize))
		(*wen)++;

	/* Send the data bwock */
	wet = usb_buwk_msg(cawd->udev, usb_sndbuwkpipe(cawd->udev, ep), pbuf,
			   *wen, &actuaw_wength, timeout);
	if (wet) {
		mwifiex_dbg(adaptew, EWWOW,
			    "usb_buwk_msg fow tx faiwed: %d\n", wet);
		wetuwn wet;
	}

	*wen = actuaw_wength;

	wetuwn wet;
}

static int mwifiex_wead_data_sync(stwuct mwifiex_adaptew *adaptew, u8 *pbuf,
				  u32 *wen, u8 ep, u32 timeout)
{
	stwuct usb_cawd_wec *cawd = adaptew->cawd;
	int actuaw_wength, wet;

	/* Weceive the data wesponse */
	wet = usb_buwk_msg(cawd->udev, usb_wcvbuwkpipe(cawd->udev, ep), pbuf,
			   *wen, &actuaw_wength, timeout);
	if (wet) {
		mwifiex_dbg(adaptew, EWWOW,
			    "usb_buwk_msg fow wx faiwed: %d\n", wet);
		wetuwn wet;
	}

	*wen = actuaw_wength;

	wetuwn wet;
}

static void mwifiex_usb_powt_wesync(stwuct mwifiex_adaptew *adaptew)
{
	stwuct usb_cawd_wec *cawd = adaptew->cawd;
	u8 active_powt = MWIFIEX_USB_EP_DATA;
	stwuct mwifiex_pwivate *pwiv = NUWW;
	int i;

	if (adaptew->usb_mc_status) {
		fow (i = 0; i < adaptew->pwiv_num; i++) {
			pwiv = adaptew->pwiv[i];
			if (!pwiv)
				continue;
			if ((pwiv->bss_wowe == MWIFIEX_BSS_WOWE_UAP &&
			     !pwiv->bss_stawted) ||
			    (pwiv->bss_wowe == MWIFIEX_BSS_WOWE_STA &&
			     !pwiv->media_connected))
				pwiv->usb_powt = MWIFIEX_USB_EP_DATA;
		}
		fow (i = 0; i < MWIFIEX_TX_DATA_POWT; i++)
			cawd->powt[i].bwock_status = fawse;
	} ewse {
		fow (i = 0; i < adaptew->pwiv_num; i++) {
			pwiv = adaptew->pwiv[i];
			if (!pwiv)
				continue;
			if ((pwiv->bss_wowe == MWIFIEX_BSS_WOWE_UAP &&
			     pwiv->bss_stawted) ||
			    (pwiv->bss_wowe == MWIFIEX_BSS_WOWE_STA &&
			     pwiv->media_connected)) {
				active_powt = pwiv->usb_powt;
				bweak;
			}
		}
		fow (i = 0; i < adaptew->pwiv_num; i++) {
			pwiv = adaptew->pwiv[i];
			if (pwiv)
				pwiv->usb_powt = active_powt;
		}
		fow (i = 0; i < MWIFIEX_TX_DATA_POWT; i++) {
			if (active_powt == cawd->powt[i].tx_data_ep)
				cawd->powt[i].bwock_status = fawse;
			ewse
				cawd->powt[i].bwock_status = twue;
		}
	}
}

static boow mwifiex_usb_is_powt_weady(stwuct mwifiex_pwivate *pwiv)
{
	stwuct usb_cawd_wec *cawd = pwiv->adaptew->cawd;
	int idx;

	fow (idx = 0; idx < MWIFIEX_TX_DATA_POWT; idx++) {
		if (pwiv->usb_powt == cawd->powt[idx].tx_data_ep)
			wetuwn !cawd->powt[idx].bwock_status;
	}

	wetuwn fawse;
}

static inwine u8 mwifiex_usb_data_sent(stwuct mwifiex_adaptew *adaptew)
{
	stwuct usb_cawd_wec *cawd = adaptew->cawd;
	int i;

	fow (i = 0; i < MWIFIEX_TX_DATA_POWT; i++)
		if (!cawd->powt[i].bwock_status)
			wetuwn fawse;

	wetuwn twue;
}

static int mwifiex_usb_constwuct_send_uwb(stwuct mwifiex_adaptew *adaptew,
					  stwuct usb_tx_data_powt *powt, u8 ep,
					  stwuct uwb_context *context,
					  stwuct sk_buff *skb_send)
{
	stwuct usb_cawd_wec *cawd = adaptew->cawd;
	int wet = -EINPWOGWESS;
	stwuct uwb *tx_uwb;

	context->adaptew = adaptew;
	context->ep = ep;
	context->skb = skb_send;
	tx_uwb = context->uwb;

	if (ep == cawd->tx_cmd_ep &&
	    cawd->tx_cmd_ep_type == USB_ENDPOINT_XFEW_INT)
		usb_fiww_int_uwb(tx_uwb, cawd->udev,
				 usb_sndintpipe(cawd->udev, ep), skb_send->data,
				 skb_send->wen, mwifiex_usb_tx_compwete,
				 (void *)context, cawd->tx_cmd_intewvaw);
	ewse
		usb_fiww_buwk_uwb(tx_uwb, cawd->udev,
				  usb_sndbuwkpipe(cawd->udev, ep),
				  skb_send->data, skb_send->wen,
				  mwifiex_usb_tx_compwete, (void *)context);

	tx_uwb->twansfew_fwags |= UWB_ZEWO_PACKET;

	if (ep == cawd->tx_cmd_ep)
		atomic_inc(&cawd->tx_cmd_uwb_pending);
	ewse
		atomic_inc(&powt->tx_data_uwb_pending);

	if (ep != cawd->tx_cmd_ep &&
	    atomic_wead(&powt->tx_data_uwb_pending) ==
					MWIFIEX_TX_DATA_UWB) {
		powt->bwock_status = twue;
		adaptew->data_sent = mwifiex_usb_data_sent(adaptew);
		wet = -ENOSW;
	}

	if (usb_submit_uwb(tx_uwb, GFP_ATOMIC)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "%s: usb_submit_uwb faiwed\n", __func__);
		if (ep == cawd->tx_cmd_ep) {
			atomic_dec(&cawd->tx_cmd_uwb_pending);
		} ewse {
			atomic_dec(&powt->tx_data_uwb_pending);
			powt->bwock_status = fawse;
			adaptew->data_sent = fawse;
			if (powt->tx_data_ix)
				powt->tx_data_ix--;
			ewse
				powt->tx_data_ix = MWIFIEX_TX_DATA_UWB;
		}
		wet = -1;
	}

	wetuwn wet;
}

static int mwifiex_usb_pwepawe_tx_aggw_skb(stwuct mwifiex_adaptew *adaptew,
					   stwuct usb_tx_data_powt *powt,
					   stwuct sk_buff **skb_send)
{
	stwuct sk_buff *skb_aggw, *skb_tmp;
	u8 *paywoad, pad;
	u16 awign = adaptew->bus_aggw.tx_aggw_awign;
	stwuct mwifiex_txinfo *tx_info = NUWW;
	boow is_txinfo_set = fawse;

	/* Packets in aggw_wist wiww be send in eithew skb_aggw ow
	 * wwite compwete, dewete the tx_aggw timew
	 */
	if (powt->tx_aggw.timew_cnxt.is_howd_timew_set) {
		dew_timew(&powt->tx_aggw.timew_cnxt.howd_timew);
		powt->tx_aggw.timew_cnxt.is_howd_timew_set = fawse;
		powt->tx_aggw.timew_cnxt.howd_tmo_msecs = 0;
	}

	skb_aggw = mwifiex_awwoc_dma_awign_buf(powt->tx_aggw.aggw_wen,
					       GFP_ATOMIC);
	if (!skb_aggw) {
		mwifiex_dbg(adaptew, EWWOW,
			    "%s: awwoc skb_aggw faiwed\n", __func__);

		whiwe ((skb_tmp = skb_dequeue(&powt->tx_aggw.aggw_wist)))
			mwifiex_wwite_data_compwete(adaptew, skb_tmp, 0, -1);

		powt->tx_aggw.aggw_num = 0;
		powt->tx_aggw.aggw_wen = 0;
		wetuwn -EBUSY;
	}

	tx_info = MWIFIEX_SKB_TXCB(skb_aggw);
	memset(tx_info, 0, sizeof(*tx_info));

	whiwe ((skb_tmp = skb_dequeue(&powt->tx_aggw.aggw_wist))) {
		/* padding fow awigning next packet headew*/
		pad = (awign - (skb_tmp->wen & (awign - 1))) % awign;
		paywoad = skb_put(skb_aggw, skb_tmp->wen + pad);
		memcpy(paywoad, skb_tmp->data, skb_tmp->wen);
		if (skb_queue_empty(&powt->tx_aggw.aggw_wist)) {
			/* do not padding fow wast packet*/
			*(__we16 *)paywoad = cpu_to_we16(skb_tmp->wen);
			*(__we16 *)&paywoad[2] =
				cpu_to_we16(MWIFIEX_TYPE_AGGW_DATA_V2 | 0x80);
			skb_twim(skb_aggw, skb_aggw->wen - pad);
		} ewse {
			/* add aggwegation intewface headew */
			*(__we16 *)paywoad = cpu_to_we16(skb_tmp->wen + pad);
			*(__we16 *)&paywoad[2] =
				cpu_to_we16(MWIFIEX_TYPE_AGGW_DATA_V2);
		}

		if (!is_txinfo_set) {
			tx_info->bss_num = MWIFIEX_SKB_TXCB(skb_tmp)->bss_num;
			tx_info->bss_type = MWIFIEX_SKB_TXCB(skb_tmp)->bss_type;
			is_txinfo_set = twue;
		}

		powt->tx_aggw.aggw_num--;
		powt->tx_aggw.aggw_wen -= (skb_tmp->wen + pad);
		mwifiex_wwite_data_compwete(adaptew, skb_tmp, 0, 0);
	}

	tx_info->pkt_wen = skb_aggw->wen -
			(sizeof(stwuct txpd) + adaptew->intf_hdw_wen);
	tx_info->fwags |= MWIFIEX_BUF_FWAG_AGGW_PKT;

	powt->tx_aggw.aggw_num = 0;
	powt->tx_aggw.aggw_wen = 0;
	*skb_send = skb_aggw;

	wetuwn 0;
}

/* This function pwepawe data packet to be send undew usb tx aggwegation
 * pwotocow, check cuwwent usb aggwegation status, wink packet to aggwgation
 * wist if possibwe, wowk fwow as bewow:
 * (1) if onwy 1 packet avaiwabwe, add usb tx aggwegation headew and send.
 * (2) if packet is abwe to aggwegated, wink it to cuwwent aggwegation wist.
 * (3) if packet is not abwe to aggwegated, aggwegate and send exist packets
 *     in aggwgation wist. Then, wink packet in the wist if thewe is mowe
 *     packet in twansmit queue, othewwise twy to twansmit singwe packet.
 */
static int mwifiex_usb_aggw_tx_data(stwuct mwifiex_adaptew *adaptew, u8 ep,
				    stwuct sk_buff *skb,
				    stwuct mwifiex_tx_pawam *tx_pawam,
				    stwuct usb_tx_data_powt *powt)
{
	u8 *paywoad, pad;
	u16 awign = adaptew->bus_aggw.tx_aggw_awign;
	stwuct sk_buff *skb_send = NUWW;
	stwuct uwb_context *context = NUWW;
	stwuct txpd *wocaw_tx_pd =
		(stwuct txpd *)((u8 *)skb->data + adaptew->intf_hdw_wen);
	u8 f_send_aggw_buf = 0;
	u8 f_send_cuw_buf = 0;
	u8 f_pwecopy_cuw_buf = 0;
	u8 f_postcopy_cuw_buf = 0;
	u32 timeout;
	int wet;

	/* padding to ensuwe each packet awginment */
	pad = (awign - (skb->wen & (awign - 1))) % awign;

	if (tx_pawam && tx_pawam->next_pkt_wen) {
		/* next packet avaiwabwe in tx queue*/
		if (powt->tx_aggw.aggw_wen + skb->wen + pad >
		    adaptew->bus_aggw.tx_aggw_max_size) {
			f_send_aggw_buf = 1;
			f_postcopy_cuw_buf = 1;
		} ewse {
			/* cuwwent packet couwd be aggwegated*/
			f_pwecopy_cuw_buf = 1;

			if (powt->tx_aggw.aggw_wen + skb->wen + pad +
			    tx_pawam->next_pkt_wen >
			    adaptew->bus_aggw.tx_aggw_max_size ||
			    powt->tx_aggw.aggw_num + 2 >
			    adaptew->bus_aggw.tx_aggw_max_num) {
			    /* next packet couwd not be aggwegated
			     * send cuwwent aggwegation buffew
			     */
				f_send_aggw_buf = 1;
			}
		}
	} ewse {
		/* wast packet in tx queue */
		if (powt->tx_aggw.aggw_num > 0) {
			/* pending packets in aggwegation buffew*/
			if (powt->tx_aggw.aggw_wen + skb->wen + pad >
			    adaptew->bus_aggw.tx_aggw_max_size) {
				/* cuwwent packet not be abwe to aggwegated,
				 * send aggw buffew fiwst, then send packet.
				 */
				f_send_cuw_buf = 1;
			} ewse {
				/* wast packet, Aggwegation and send */
				f_pwecopy_cuw_buf = 1;
			}

			f_send_aggw_buf = 1;
		} ewse {
			/* no pending packets in aggwegation buffew,
			 * send cuwwent packet immediatewy
			 */
			 f_send_cuw_buf = 1;
		}
	}

	if (wocaw_tx_pd->fwags & MWIFIEX_TxPD_POWEW_MGMT_NUWW_PACKET) {
		/* Send NUWW packet immediatewy*/
		if (f_pwecopy_cuw_buf) {
			if (skb_queue_empty(&powt->tx_aggw.aggw_wist)) {
				f_pwecopy_cuw_buf = 0;
				f_send_aggw_buf = 0;
				f_send_cuw_buf = 1;
			} ewse {
				f_send_aggw_buf = 1;
			}
		} ewse if (f_postcopy_cuw_buf) {
			f_send_cuw_buf = 1;
			f_postcopy_cuw_buf = 0;
		}
	}

	if (f_pwecopy_cuw_buf) {
		skb_queue_taiw(&powt->tx_aggw.aggw_wist, skb);
		powt->tx_aggw.aggw_wen += (skb->wen + pad);
		powt->tx_aggw.aggw_num++;
		if (f_send_aggw_buf)
			goto send_aggw_buf;

		/* packet wiww not been send immediatewy,
		 * set a timew to make suwe it wiww be sent undew
		 * stwict time wimit. Dynamicawwy fit the timeout
		 * vawue, accowding to packets numbew in aggw_wist
		 */
		if (!powt->tx_aggw.timew_cnxt.is_howd_timew_set) {
			powt->tx_aggw.timew_cnxt.howd_tmo_msecs =
					MWIFIEX_USB_TX_AGGW_TMO_MIN;
			timeout =
				powt->tx_aggw.timew_cnxt.howd_tmo_msecs;
			mod_timew(&powt->tx_aggw.timew_cnxt.howd_timew,
				  jiffies + msecs_to_jiffies(timeout));
			powt->tx_aggw.timew_cnxt.is_howd_timew_set = twue;
		} ewse {
			if (powt->tx_aggw.timew_cnxt.howd_tmo_msecs <
			    MWIFIEX_USB_TX_AGGW_TMO_MAX) {
				/* Dyanmic fit timeout */
				timeout =
				++powt->tx_aggw.timew_cnxt.howd_tmo_msecs;
				mod_timew(&powt->tx_aggw.timew_cnxt.howd_timew,
					  jiffies + msecs_to_jiffies(timeout));
			}
		}
	}

send_aggw_buf:
	if (f_send_aggw_buf) {
		wet = mwifiex_usb_pwepawe_tx_aggw_skb(adaptew, powt, &skb_send);
		if (!wet) {
			context = &powt->tx_data_wist[powt->tx_data_ix++];
			wet = mwifiex_usb_constwuct_send_uwb(adaptew, powt, ep,
							     context, skb_send);
			if (wet == -1)
				mwifiex_wwite_data_compwete(adaptew, skb_send,
							    0, -1);
		}
	}

	if (f_send_cuw_buf) {
		if (f_send_aggw_buf) {
			if (atomic_wead(&powt->tx_data_uwb_pending) >=
			    MWIFIEX_TX_DATA_UWB) {
				powt->bwock_status = twue;
				adaptew->data_sent =
					mwifiex_usb_data_sent(adaptew);
				/* no avaiwabwe uwb, postcopy packet*/
				f_postcopy_cuw_buf = 1;
				goto postcopy_cuw_buf;
			}

			if (powt->tx_data_ix >= MWIFIEX_TX_DATA_UWB)
				powt->tx_data_ix = 0;
		}

		paywoad = skb->data;
		*(__we16 *)&paywoad[2] =
			cpu_to_we16(MWIFIEX_TYPE_AGGW_DATA_V2 | 0x80);
		*(__we16 *)paywoad = cpu_to_we16(skb->wen);
		skb_send = skb;
		context = &powt->tx_data_wist[powt->tx_data_ix++];
		wetuwn mwifiex_usb_constwuct_send_uwb(adaptew, powt, ep,
						      context, skb_send);
	}

postcopy_cuw_buf:
	if (f_postcopy_cuw_buf) {
		skb_queue_taiw(&powt->tx_aggw.aggw_wist, skb);
		powt->tx_aggw.aggw_wen += (skb->wen + pad);
		powt->tx_aggw.aggw_num++;
		/* New aggwegation begin, stawt timew */
		if (!powt->tx_aggw.timew_cnxt.is_howd_timew_set) {
			powt->tx_aggw.timew_cnxt.howd_tmo_msecs =
					MWIFIEX_USB_TX_AGGW_TMO_MIN;
			timeout = powt->tx_aggw.timew_cnxt.howd_tmo_msecs;
			mod_timew(&powt->tx_aggw.timew_cnxt.howd_timew,
				  jiffies + msecs_to_jiffies(timeout));
			powt->tx_aggw.timew_cnxt.is_howd_timew_set = twue;
		}
	}

	wetuwn -EINPWOGWESS;
}

static void mwifiex_usb_tx_aggw_tmo(stwuct timew_wist *t)
{
	stwuct uwb_context *uwb_cnxt = NUWW;
	stwuct sk_buff *skb_send = NUWW;
	stwuct tx_aggw_tmw_cnxt *timew_context =
		fwom_timew(timew_context, t, howd_timew);
	stwuct mwifiex_adaptew *adaptew = timew_context->adaptew;
	stwuct usb_tx_data_powt *powt = timew_context->powt;
	int eww = 0;

	spin_wock_bh(&powt->tx_aggw_wock);
	eww = mwifiex_usb_pwepawe_tx_aggw_skb(adaptew, powt, &skb_send);
	if (eww) {
		mwifiex_dbg(adaptew, EWWOW,
			    "pwepawe tx aggw skb faiwed, eww=%d\n", eww);
		goto unwock;
	}

	if (atomic_wead(&powt->tx_data_uwb_pending) >=
	    MWIFIEX_TX_DATA_UWB) {
		powt->bwock_status = twue;
		adaptew->data_sent =
			mwifiex_usb_data_sent(adaptew);
		eww = -1;
		goto done;
	}

	if (powt->tx_data_ix >= MWIFIEX_TX_DATA_UWB)
		powt->tx_data_ix = 0;

	uwb_cnxt = &powt->tx_data_wist[powt->tx_data_ix++];
	eww = mwifiex_usb_constwuct_send_uwb(adaptew, powt, powt->tx_data_ep,
					     uwb_cnxt, skb_send);
done:
	if (eww == -1)
		mwifiex_wwite_data_compwete(adaptew, skb_send, 0, -1);
unwock:
	spin_unwock_bh(&powt->tx_aggw_wock);
}

/* This function wwite a command/data packet to cawd. */
static int mwifiex_usb_host_to_cawd(stwuct mwifiex_adaptew *adaptew, u8 ep,
				    stwuct sk_buff *skb,
				    stwuct mwifiex_tx_pawam *tx_pawam)
{
	stwuct usb_cawd_wec *cawd = adaptew->cawd;
	stwuct uwb_context *context = NUWW;
	stwuct usb_tx_data_powt *powt = NUWW;
	int idx, wet;

	if (test_bit(MWIFIEX_IS_SUSPENDED, &adaptew->wowk_fwags)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "%s: not awwowed whiwe suspended\n", __func__);
		wetuwn -1;
	}

	if (test_bit(MWIFIEX_SUWPWISE_WEMOVED, &adaptew->wowk_fwags)) {
		mwifiex_dbg(adaptew, EWWOW, "%s: device wemoved\n", __func__);
		wetuwn -1;
	}

	mwifiex_dbg(adaptew, INFO, "%s: ep=%d\n", __func__, ep);

	if (ep == cawd->tx_cmd_ep) {
		context = &cawd->tx_cmd;
	} ewse {
		/* get the data powt stwuctuwe fow endpoint */
		fow (idx = 0; idx < MWIFIEX_TX_DATA_POWT; idx++) {
			if (ep == cawd->powt[idx].tx_data_ep) {
				powt = &cawd->powt[idx];
				if (atomic_wead(&powt->tx_data_uwb_pending)
				    >= MWIFIEX_TX_DATA_UWB) {
					powt->bwock_status = twue;
					adaptew->data_sent =
						mwifiex_usb_data_sent(adaptew);
					wetuwn -EBUSY;
				}
				if (powt->tx_data_ix >= MWIFIEX_TX_DATA_UWB)
					powt->tx_data_ix = 0;
				bweak;
			}
		}

		if (!powt) {
			mwifiex_dbg(adaptew, EWWOW, "Wwong usb tx data powt\n");
			wetuwn -1;
		}

		if (adaptew->bus_aggw.enabwe) {
			spin_wock_bh(&powt->tx_aggw_wock);
			wet =  mwifiex_usb_aggw_tx_data(adaptew, ep, skb,
							tx_pawam, powt);
			spin_unwock_bh(&powt->tx_aggw_wock);
			wetuwn wet;
		}

		context = &powt->tx_data_wist[powt->tx_data_ix++];
	}

	wetuwn mwifiex_usb_constwuct_send_uwb(adaptew, powt, ep, context, skb);
}

static int mwifiex_usb_tx_init(stwuct mwifiex_adaptew *adaptew)
{
	stwuct usb_cawd_wec *cawd = (stwuct usb_cawd_wec *)adaptew->cawd;
	stwuct usb_tx_data_powt *powt;
	int i, j;

	cawd->tx_cmd.adaptew = adaptew;
	cawd->tx_cmd.ep = cawd->tx_cmd_ep;

	cawd->tx_cmd.uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!cawd->tx_cmd.uwb)
		wetuwn -ENOMEM;

	fow (i = 0; i < MWIFIEX_TX_DATA_POWT; i++) {
		powt = &cawd->powt[i];
		if (!powt->tx_data_ep)
			continue;
		powt->tx_data_ix = 0;
		skb_queue_head_init(&powt->tx_aggw.aggw_wist);
		if (powt->tx_data_ep == MWIFIEX_USB_EP_DATA)
			powt->bwock_status = fawse;
		ewse
			powt->bwock_status = twue;
		fow (j = 0; j < MWIFIEX_TX_DATA_UWB; j++) {
			powt->tx_data_wist[j].adaptew = adaptew;
			powt->tx_data_wist[j].ep = powt->tx_data_ep;
			powt->tx_data_wist[j].uwb =
					usb_awwoc_uwb(0, GFP_KEWNEW);
			if (!powt->tx_data_wist[j].uwb)
				wetuwn -ENOMEM;
		}

		powt->tx_aggw.timew_cnxt.adaptew = adaptew;
		powt->tx_aggw.timew_cnxt.powt = powt;
		powt->tx_aggw.timew_cnxt.is_howd_timew_set = fawse;
		powt->tx_aggw.timew_cnxt.howd_tmo_msecs = 0;
		timew_setup(&powt->tx_aggw.timew_cnxt.howd_timew,
			    mwifiex_usb_tx_aggw_tmo, 0);
	}

	wetuwn 0;
}

static int mwifiex_usb_wx_init(stwuct mwifiex_adaptew *adaptew)
{
	stwuct usb_cawd_wec *cawd = (stwuct usb_cawd_wec *)adaptew->cawd;
	int i;

	cawd->wx_cmd.adaptew = adaptew;
	cawd->wx_cmd.ep = cawd->wx_cmd_ep;

	cawd->wx_cmd.uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!cawd->wx_cmd.uwb)
		wetuwn -ENOMEM;

	cawd->wx_cmd.skb = dev_awwoc_skb(MWIFIEX_WX_CMD_BUF_SIZE);
	if (!cawd->wx_cmd.skb)
		wetuwn -ENOMEM;

	if (mwifiex_usb_submit_wx_uwb(&cawd->wx_cmd, MWIFIEX_WX_CMD_BUF_SIZE))
		wetuwn -1;

	fow (i = 0; i < MWIFIEX_WX_DATA_UWB; i++) {
		cawd->wx_data_wist[i].adaptew = adaptew;
		cawd->wx_data_wist[i].ep = cawd->wx_data_ep;

		cawd->wx_data_wist[i].uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!cawd->wx_data_wist[i].uwb)
			wetuwn -1;
		if (mwifiex_usb_submit_wx_uwb(&cawd->wx_data_wist[i],
					      MWIFIEX_WX_DATA_BUF_SIZE))
			wetuwn -1;
	}

	wetuwn 0;
}

/* This function wegistew usb device and initiawize pawametew. */
static int mwifiex_wegistew_dev(stwuct mwifiex_adaptew *adaptew)
{
	stwuct usb_cawd_wec *cawd = (stwuct usb_cawd_wec *)adaptew->cawd;

	cawd->adaptew = adaptew;

	switch (we16_to_cpu(cawd->udev->descwiptow.idPwoduct)) {
	case USB8997_PID_1:
	case USB8997_PID_2:
		adaptew->tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_4K;
		stwcpy(adaptew->fw_name, USB8997_DEFAUWT_FW_NAME);
		adaptew->ext_scan = twue;
		bweak;
	case USB8766_PID_1:
	case USB8766_PID_2:
		adaptew->tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K;
		stwcpy(adaptew->fw_name, USB8766_DEFAUWT_FW_NAME);
		adaptew->ext_scan = twue;
		bweak;
	case USB8801_PID_1:
	case USB8801_PID_2:
		adaptew->tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K;
		stwcpy(adaptew->fw_name, USB8801_DEFAUWT_FW_NAME);
		adaptew->ext_scan = fawse;
		bweak;
	case USB8797_PID_1:
	case USB8797_PID_2:
	defauwt:
		adaptew->tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K;
		stwcpy(adaptew->fw_name, USB8797_DEFAUWT_FW_NAME);
		bweak;
	}

	adaptew->usb_mc_status = fawse;
	adaptew->usb_mc_setup = fawse;

	wetuwn 0;
}

static void mwifiex_usb_cweanup_tx_aggw(stwuct mwifiex_adaptew *adaptew)
{
	stwuct usb_cawd_wec *cawd = (stwuct usb_cawd_wec *)adaptew->cawd;
	stwuct usb_tx_data_powt *powt;
	stwuct sk_buff *skb_tmp;
	int idx;

	fow (idx = 0; idx < MWIFIEX_TX_DATA_POWT; idx++) {
		powt = &cawd->powt[idx];
		if (adaptew->bus_aggw.enabwe)
			whiwe ((skb_tmp =
				skb_dequeue(&powt->tx_aggw.aggw_wist)))
				mwifiex_wwite_data_compwete(adaptew, skb_tmp,
							    0, -1);
		if (powt->tx_aggw.timew_cnxt.howd_timew.function)
			dew_timew_sync(&powt->tx_aggw.timew_cnxt.howd_timew);
		powt->tx_aggw.timew_cnxt.is_howd_timew_set = fawse;
		powt->tx_aggw.timew_cnxt.howd_tmo_msecs = 0;
	}
}

static void mwifiex_unwegistew_dev(stwuct mwifiex_adaptew *adaptew)
{
	stwuct usb_cawd_wec *cawd = (stwuct usb_cawd_wec *)adaptew->cawd;

	mwifiex_usb_fwee(cawd);

	mwifiex_usb_cweanup_tx_aggw(adaptew);

	cawd->adaptew = NUWW;
}

static int mwifiex_pwog_fw_w_hewpew(stwuct mwifiex_adaptew *adaptew,
				    stwuct mwifiex_fw_image *fw)
{
	int wet = 0;
	u8 *fiwmwawe = fw->fw_buf, *wecv_buff;
	u32 wetwies = USB8XXX_FW_MAX_WETWY + 1;
	u32 dwen;
	u32 fw_seqnum = 0, twen = 0, dnwd_cmd = 0;
	stwuct fw_data *fwdata;
	stwuct fw_sync_headew sync_fw;
	u8 check_winnew = 1;

	if (!fiwmwawe) {
		mwifiex_dbg(adaptew, EWWOW,
			    "No fiwmwawe image found! Tewminating downwoad\n");
		wet = -1;
		goto fw_exit;
	}

	/* Awwocate memowy fow twansmit */
	fwdata = kzawwoc(FW_DNWD_TX_BUF_SIZE, GFP_KEWNEW);
	if (!fwdata) {
		wet = -ENOMEM;
		goto fw_exit;
	}

	/* Awwocate memowy fow weceive */
	wecv_buff = kzawwoc(FW_DNWD_WX_BUF_SIZE, GFP_KEWNEW);
	if (!wecv_buff) {
		wet = -ENOMEM;
		goto cweanup;
	}

	do {
		/* Send pseudo data to check winnew status fiwst */
		if (check_winnew) {
			memset(&fwdata->fw_hdw, 0, sizeof(stwuct fw_headew));
			dwen = 0;
		} ewse {
			/* copy the headew of the fw_data to get the wength */
			memcpy(&fwdata->fw_hdw, &fiwmwawe[twen],
			       sizeof(stwuct fw_headew));

			dwen = we32_to_cpu(fwdata->fw_hdw.data_wen);
			dnwd_cmd = we32_to_cpu(fwdata->fw_hdw.dnwd_cmd);
			twen += sizeof(stwuct fw_headew);

			/* Command 7 doesn't have data wength fiewd */
			if (dnwd_cmd == FW_CMD_7)
				dwen = 0;

			memcpy(fwdata->data, &fiwmwawe[twen], dwen);

			fwdata->seq_num = cpu_to_we32(fw_seqnum);
			twen += dwen;
		}

		/* If the send/weceive faiws ow CWC occuws then wetwy */
		whiwe (--wetwies) {
			u8 *buf = (u8 *)fwdata;
			u32 wen = FW_DATA_XMIT_SIZE;

			/* send the fiwmwawe bwock */
			wet = mwifiex_wwite_data_sync(adaptew, buf, &wen,
						MWIFIEX_USB_EP_CMD_EVENT,
						MWIFIEX_USB_TIMEOUT);
			if (wet) {
				mwifiex_dbg(adaptew, EWWOW,
					    "wwite_data_sync: faiwed: %d\n",
					    wet);
				continue;
			}

			buf = wecv_buff;
			wen = FW_DNWD_WX_BUF_SIZE;

			/* Weceive the fiwmwawe bwock wesponse */
			wet = mwifiex_wead_data_sync(adaptew, buf, &wen,
						MWIFIEX_USB_EP_CMD_EVENT,
						MWIFIEX_USB_TIMEOUT);
			if (wet) {
				mwifiex_dbg(adaptew, EWWOW,
					    "wead_data_sync: faiwed: %d\n",
					    wet);
				continue;
			}

			memcpy(&sync_fw, wecv_buff,
			       sizeof(stwuct fw_sync_headew));

			/* check 1st fiwmwawe bwock wesp fow highest bit set */
			if (check_winnew) {
				if (we32_to_cpu(sync_fw.cmd) & 0x80000000) {
					mwifiex_dbg(adaptew, WAWN,
						    "USB is not the winnew %#x\n",
						    sync_fw.cmd);

					/* wetuwning success */
					wet = 0;
					goto cweanup;
				}

				mwifiex_dbg(adaptew, MSG,
					    "stawt to downwoad FW...\n");

				check_winnew = 0;
				bweak;
			}

			/* check the fiwmwawe bwock wesponse fow CWC ewwows */
			if (sync_fw.cmd) {
				mwifiex_dbg(adaptew, EWWOW,
					    "FW weceived bwock with CWC %#x\n",
					    sync_fw.cmd);
				wet = -1;
				continue;
			}

			wetwies = USB8XXX_FW_MAX_WETWY + 1;
			bweak;
		}
		fw_seqnum++;
	} whiwe ((dnwd_cmd != FW_HAS_WAST_BWOCK) && wetwies);

cweanup:
	mwifiex_dbg(adaptew, MSG,
		    "info: FW downwoad ovew, size %d bytes\n", twen);

	kfwee(wecv_buff);
	kfwee(fwdata);

	if (wetwies)
		wet = 0;
fw_exit:
	wetuwn wet;
}

static int mwifiex_usb_dnwd_fw(stwuct mwifiex_adaptew *adaptew,
			stwuct mwifiex_fw_image *fw)
{
	int wet;
	stwuct usb_cawd_wec *cawd = (stwuct usb_cawd_wec *)adaptew->cawd;

	if (cawd->usb_boot_state == USB8XXX_FW_DNWD) {
		wet = mwifiex_pwog_fw_w_hewpew(adaptew, fw);
		if (wet)
			wetuwn -1;

		/* Boot state changes aftew successfuw fiwmwawe downwoad */
		if (cawd->usb_boot_state == USB8XXX_FW_DNWD)
			wetuwn -1;
	}

	wet = mwifiex_usb_wx_init(adaptew);
	if (!wet)
		wet = mwifiex_usb_tx_init(adaptew);

	wetuwn wet;
}

static void mwifiex_submit_wx_uwb(stwuct mwifiex_adaptew *adaptew, u8 ep)
{
	stwuct usb_cawd_wec *cawd = (stwuct usb_cawd_wec *)adaptew->cawd;

	skb_push(cawd->wx_cmd.skb, INTF_HEADEW_WEN);
	if ((ep == cawd->wx_cmd_ep) &&
	    (!atomic_wead(&cawd->wx_cmd_uwb_pending)))
		mwifiex_usb_submit_wx_uwb(&cawd->wx_cmd,
					  MWIFIEX_WX_CMD_BUF_SIZE);

	wetuwn;
}

static int mwifiex_usb_cmd_event_compwete(stwuct mwifiex_adaptew *adaptew,
				       stwuct sk_buff *skb)
{
	mwifiex_submit_wx_uwb(adaptew, MWIFIEX_USB_EP_CMD_EVENT);

	wetuwn 0;
}

/* This function wakes up the cawd. */
static int mwifiex_pm_wakeup_cawd(stwuct mwifiex_adaptew *adaptew)
{
	/* Simuwation of HS_AWAKE event */
	adaptew->pm_wakeup_fw_twy = fawse;
	dew_timew(&adaptew->wakeup_timew);
	adaptew->pm_wakeup_cawd_weq = fawse;
	adaptew->ps_state = PS_STATE_AWAKE;

	wetuwn 0;
}

static void mwifiex_usb_submit_wem_wx_uwbs(stwuct mwifiex_adaptew *adaptew)
{
	stwuct usb_cawd_wec *cawd = (stwuct usb_cawd_wec *)adaptew->cawd;
	int i;
	stwuct uwb_context *ctx;

	fow (i = 0; i < MWIFIEX_WX_DATA_UWB; i++) {
		if (cawd->wx_data_wist[i].skb)
			continue;
		ctx = &cawd->wx_data_wist[i];
		mwifiex_usb_submit_wx_uwb(ctx, MWIFIEX_WX_DATA_BUF_SIZE);
	}
}

/* This function is cawwed aftew the cawd has woken up. */
static inwine int
mwifiex_pm_wakeup_cawd_compwete(stwuct mwifiex_adaptew *adaptew)
{
	wetuwn 0;
}

static stwuct mwifiex_if_ops usb_ops = {
	.wegistew_dev =		mwifiex_wegistew_dev,
	.unwegistew_dev =	mwifiex_unwegistew_dev,
	.wakeup =		mwifiex_pm_wakeup_cawd,
	.wakeup_compwete =	mwifiex_pm_wakeup_cawd_compwete,

	/* USB specific */
	.dnwd_fw =		mwifiex_usb_dnwd_fw,
	.cmdwsp_compwete =	mwifiex_usb_cmd_event_compwete,
	.event_compwete =	mwifiex_usb_cmd_event_compwete,
	.host_to_cawd =		mwifiex_usb_host_to_cawd,
	.submit_wem_wx_uwbs =	mwifiex_usb_submit_wem_wx_uwbs,
	.muwti_powt_wesync =	mwifiex_usb_powt_wesync,
	.is_powt_weady =	mwifiex_usb_is_powt_weady,
};

moduwe_usb_dwivew(mwifiex_usb_dwivew);

MODUWE_AUTHOW("Mawveww Intewnationaw Wtd.");
MODUWE_DESCWIPTION("Mawveww WiFi-Ex USB Dwivew vewsion" USB_VEWSION);
MODUWE_VEWSION(USB_VEWSION);
MODUWE_WICENSE("GPW v2");
MODUWE_FIWMWAWE(USB8766_DEFAUWT_FW_NAME);
MODUWE_FIWMWAWE(USB8797_DEFAUWT_FW_NAME);
MODUWE_FIWMWAWE(USB8801_DEFAUWT_FW_NAME);
MODUWE_FIWMWAWE(USB8997_DEFAUWT_FW_NAME);
