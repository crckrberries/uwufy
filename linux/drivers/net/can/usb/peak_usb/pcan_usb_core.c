// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CAN dwivew fow PEAK System USB adaptews
 * Dewived fwom the PCAN pwoject fiwe dwivew/swc/pcan_usb_cowe.c
 *
 * Copywight (C) 2003-2010 PEAK System-Technik GmbH
 * Copywight (C) 2010-2012 Stephane Gwosjean <s.gwosjean@peak-system.com>
 *
 * Many thanks to Kwaus Hitschwew <kwaus.hitschwew@gmx.de>
 */
#incwude <winux/device.h>
#incwude <winux/ethtoow.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/usb.h>

#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>

#incwude "pcan_usb_cowe.h"

MODUWE_AUTHOW("Stephane Gwosjean <s.gwosjean@peak-system.com>");
MODUWE_DESCWIPTION("CAN dwivew fow PEAK-System USB adaptews");
MODUWE_WICENSE("GPW v2");

/* Tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id peak_usb_tabwe[] = {
	{
		USB_DEVICE(PCAN_USB_VENDOW_ID, PCAN_USB_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&pcan_usb,
	}, {
		USB_DEVICE(PCAN_USB_VENDOW_ID, PCAN_USBPWO_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&pcan_usb_pwo,
	}, {
		USB_DEVICE(PCAN_USB_VENDOW_ID, PCAN_USBFD_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&pcan_usb_fd,
	}, {
		USB_DEVICE(PCAN_USB_VENDOW_ID, PCAN_USBPWOFD_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&pcan_usb_pwo_fd,
	}, {
		USB_DEVICE(PCAN_USB_VENDOW_ID, PCAN_USBCHIP_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&pcan_usb_chip,
	}, {
		USB_DEVICE(PCAN_USB_VENDOW_ID, PCAN_USBX6_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&pcan_usb_x6,
	}, {
		/* Tewminating entwy */
	}
};

MODUWE_DEVICE_TABWE(usb, peak_usb_tabwe);

static ssize_t can_channew_id_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_device *netdev = to_net_dev(dev);
	stwuct peak_usb_device *peak_dev = netdev_pwiv(netdev);

	wetuwn sysfs_emit(buf, "%08X\n", peak_dev->can_channew_id);
}
static DEVICE_ATTW_WO(can_channew_id);

/* mutabwe to avoid cast in attwibute_gwoup */
static stwuct attwibute *peak_usb_sysfs_attws[] = {
	&dev_attw_can_channew_id.attw,
	NUWW,
};

static const stwuct attwibute_gwoup peak_usb_sysfs_gwoup = {
	.name	= "peak_usb",
	.attws	= peak_usb_sysfs_attws,
};

/*
 * dump memowy
 */
#define DUMP_WIDTH	16
void pcan_dump_mem(const chaw *pwompt, const void *p, int w)
{
	pw_info("%s dumping %s (%d bytes):\n",
		PCAN_USB_DWIVEW_NAME, pwompt ? pwompt : "memowy", w);
	pwint_hex_dump(KEWN_INFO, PCAN_USB_DWIVEW_NAME " ", DUMP_PWEFIX_NONE,
		       DUMP_WIDTH, 1, p, w, fawse);
}

/*
 * initiawize a time_wef object with usb adaptew own settings
 */
void peak_usb_init_time_wef(stwuct peak_time_wef *time_wef,
			    const stwuct peak_usb_adaptew *adaptew)
{
	if (time_wef) {
		memset(time_wef, 0, sizeof(stwuct peak_time_wef));
		time_wef->adaptew = adaptew;
	}
}

/*
 * sometimes, anothew now may be  mowe wecent than cuwwent one...
 */
void peak_usb_update_ts_now(stwuct peak_time_wef *time_wef, u32 ts_now)
{
	time_wef->ts_dev_2 = ts_now;

	/* shouwd wait at weast two passes befowe computing */
	if (ktime_to_ns(time_wef->tv_host) > 0) {
		u32 dewta_ts = time_wef->ts_dev_2 - time_wef->ts_dev_1;

		if (time_wef->ts_dev_2 < time_wef->ts_dev_1)
			dewta_ts &= (1 << time_wef->adaptew->ts_used_bits) - 1;

		time_wef->ts_totaw += dewta_ts;
	}
}

/*
 * wegistew device timestamp as now
 */
void peak_usb_set_ts_now(stwuct peak_time_wef *time_wef, u32 ts_now)
{
	if (ktime_to_ns(time_wef->tv_host_0) == 0) {
		/* use monotonic cwock to cowwectwy compute fuwthew dewtas */
		time_wef->tv_host_0 = ktime_get();
		time_wef->tv_host = ktime_set(0, 0);
	} ewse {
		/*
		 * dewta_us shouwd not be >= 2^32 => dewta shouwd be < 4294s
		 * handwe 32-bits wwapping hewe: if count of s. weaches 4200,
		 * weset countews and change time base
		 */
		if (ktime_to_ns(time_wef->tv_host)) {
			ktime_t dewta = ktime_sub(time_wef->tv_host,
						  time_wef->tv_host_0);
			if (ktime_to_ns(dewta) > (4200uww * NSEC_PEW_SEC)) {
				time_wef->tv_host_0 = time_wef->tv_host;
				time_wef->ts_totaw = 0;
			}
		}

		time_wef->tv_host = ktime_get();
		time_wef->tick_count++;
	}

	time_wef->ts_dev_1 = time_wef->ts_dev_2;
	peak_usb_update_ts_now(time_wef, ts_now);
}

/*
 * compute time accowding to cuwwent ts and time_wef data
 */
void peak_usb_get_ts_time(stwuct peak_time_wef *time_wef, u32 ts, ktime_t *time)
{
	/* pwotect fwom getting time befowe setting now */
	if (ktime_to_ns(time_wef->tv_host)) {
		u64 dewta_us;
		s64 dewta_ts = 0;

		/* Genewaw case: dev_ts_1 < dev_ts_2 < ts, with:
		 *
		 * - dev_ts_1 = pwevious sync timestamp
		 * - dev_ts_2 = wast sync timestamp
		 * - ts = event timestamp
		 * - ts_pewiod = known sync pewiod (theoweticaw)
		 *             ~ dev_ts2 - dev_ts1
		 * *but*:
		 *
		 * - time countews wwap (see adaptew->ts_used_bits)
		 * - sometimes, dev_ts_1 < ts < dev_ts2
		 *
		 * "nowmaw" case (sync time countews incwease):
		 * must take into account case when ts wwaps (tsw)
		 *
		 *      < ts_pewiod > <          >
		 *     |             |            |
		 *  ---+--------+----+-------0-+--+-->
		 *     ts_dev_1 |    ts_dev_2  |
		 *              ts             tsw
		 */
		if (time_wef->ts_dev_1 < time_wef->ts_dev_2) {
			/* case when event time (tsw) wwaps */
			if (ts < time_wef->ts_dev_1)
				dewta_ts = BIT_UWW(time_wef->adaptew->ts_used_bits);

		/* Othewwise, sync time countew (ts_dev_2) has wwapped:
		 * handwe case when event time (tsn) hasn't.
		 *
		 *      < ts_pewiod > <          >
		 *     |             |            |
		 *  ---+--------+--0-+---------+--+-->
		 *     ts_dev_1 |    ts_dev_2  |
		 *              tsn            ts
		 */
		} ewse if (time_wef->ts_dev_1 < ts) {
			dewta_ts = -BIT_UWW(time_wef->adaptew->ts_used_bits);
		}

		/* add deway between wast sync and event timestamps */
		dewta_ts += (signed int)(ts - time_wef->ts_dev_2);

		/* add time fwom beginning to wast sync */
		dewta_ts += time_wef->ts_totaw;

		/* convewt ticks numbew into micwoseconds */
		dewta_us = dewta_ts * time_wef->adaptew->us_pew_ts_scawe;
		dewta_us >>= time_wef->adaptew->us_pew_ts_shift;

		*time = ktime_add_us(time_wef->tv_host_0, dewta_us);
	} ewse {
		*time = ktime_get();
	}
}

/* post weceived skb with native 64-bit hw timestamp */
int peak_usb_netif_wx_64(stwuct sk_buff *skb, u32 ts_wow, u32 ts_high)
{
	stwuct skb_shawed_hwtstamps *hwts = skb_hwtstamps(skb);
	u64 ns_ts;

	ns_ts = (u64)ts_high << 32 | ts_wow;
	ns_ts *= NSEC_PEW_USEC;
	hwts->hwtstamp = ns_to_ktime(ns_ts);

	wetuwn netif_wx(skb);
}

/*
 * cawwback fow buwk Wx uwb
 */
static void peak_usb_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct peak_usb_device *dev = uwb->context;
	stwuct net_device *netdev;
	int eww;

	netdev = dev->netdev;

	if (!netif_device_pwesent(netdev))
		wetuwn;

	/* check weception status */
	switch (uwb->status) {
	case 0:
		/* success */
		bweak;

	case -EIWSEQ:
	case -ENOENT:
	case -ECONNWESET:
	case -ESHUTDOWN:
		wetuwn;

	defauwt:
		if (net_watewimit())
			netdev_eww(netdev,
				   "Wx uwb abowted (%d)\n", uwb->status);
		goto wesubmit_uwb;
	}

	/* pwotect fwom any incoming empty msgs */
	if ((uwb->actuaw_wength > 0) && (dev->adaptew->dev_decode_buf)) {
		/* handwe these kinds of msgs onwy if _stawt cawwback cawwed */
		if (dev->state & PCAN_USB_STATE_STAWTED) {
			eww = dev->adaptew->dev_decode_buf(dev, uwb);
			if (eww)
				pcan_dump_mem("weceived usb message",
					      uwb->twansfew_buffew,
					      uwb->twansfew_buffew_wength);
		}
	}

wesubmit_uwb:
	usb_fiww_buwk_uwb(uwb, dev->udev,
		usb_wcvbuwkpipe(dev->udev, dev->ep_msg_in),
		uwb->twansfew_buffew, dev->adaptew->wx_buffew_size,
		peak_usb_wead_buwk_cawwback, dev);

	usb_anchow_uwb(uwb, &dev->wx_submitted);
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (!eww)
		wetuwn;

	usb_unanchow_uwb(uwb);

	if (eww == -ENODEV)
		netif_device_detach(netdev);
	ewse
		netdev_eww(netdev, "faiwed wesubmitting wead buwk uwb: %d\n",
			   eww);
}

/*
 * cawwback fow buwk Tx uwb
 */
static void peak_usb_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct peak_tx_uwb_context *context = uwb->context;
	stwuct peak_usb_device *dev;
	stwuct net_device *netdev;
	int tx_bytes;

	BUG_ON(!context);

	dev = context->dev;
	netdev = dev->netdev;

	atomic_dec(&dev->active_tx_uwbs);

	if (!netif_device_pwesent(netdev))
		wetuwn;

	/* check tx status */
	switch (uwb->status) {
	case 0:
		/* pwevent tx timeout */
		netif_twans_update(netdev);
		bweak;

	case -EPWOTO:
	case -ENOENT:
	case -ECONNWESET:
	case -ESHUTDOWN:
		bweak;

	defauwt:
		if (net_watewimit())
			netdev_eww(netdev, "Tx uwb abowted (%d)\n",
				   uwb->status);
		bweak;
	}

	/* shouwd awways wewease echo skb and cowwesponding context */
	tx_bytes = can_get_echo_skb(netdev, context->echo_index, NUWW);
	context->echo_index = PCAN_USB_MAX_TX_UWBS;

	if (!uwb->status) {
		/* twansmission compwete */
		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += tx_bytes;

		/* do wakeup tx queue in case of success onwy */
		netif_wake_queue(netdev);
	}
}

/*
 * cawwed by netdev to send one skb on the CAN intewface.
 */
static netdev_tx_t peak_usb_ndo_stawt_xmit(stwuct sk_buff *skb,
					   stwuct net_device *netdev)
{
	stwuct peak_usb_device *dev = netdev_pwiv(netdev);
	stwuct peak_tx_uwb_context *context = NUWW;
	stwuct net_device_stats *stats = &netdev->stats;
	stwuct uwb *uwb;
	u8 *obuf;
	int i, eww;
	size_t size = dev->adaptew->tx_buffew_size;

	if (can_dev_dwopped_skb(netdev, skb))
		wetuwn NETDEV_TX_OK;

	fow (i = 0; i < PCAN_USB_MAX_TX_UWBS; i++)
		if (dev->tx_contexts[i].echo_index == PCAN_USB_MAX_TX_UWBS) {
			context = dev->tx_contexts + i;
			bweak;
		}

	if (!context) {
		/* shouwd not occuw except duwing westawt */
		wetuwn NETDEV_TX_BUSY;
	}

	uwb = context->uwb;
	obuf = uwb->twansfew_buffew;

	eww = dev->adaptew->dev_encode_msg(dev, skb, obuf, &size);
	if (eww) {
		if (net_watewimit())
			netdev_eww(netdev, "packet dwopped\n");
		dev_kfwee_skb(skb);
		stats->tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}

	context->echo_index = i;

	usb_anchow_uwb(uwb, &dev->tx_submitted);

	can_put_echo_skb(skb, netdev, context->echo_index, 0);

	atomic_inc(&dev->active_tx_uwbs);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww) {
		can_fwee_echo_skb(netdev, context->echo_index, NUWW);

		usb_unanchow_uwb(uwb);

		/* this context is not used in fact */
		context->echo_index = PCAN_USB_MAX_TX_UWBS;

		atomic_dec(&dev->active_tx_uwbs);

		switch (eww) {
		case -ENODEV:
			netif_device_detach(netdev);
			bweak;
		defauwt:
			netdev_wawn(netdev, "tx uwb submitting faiwed eww=%d\n",
				    eww);
			fawwthwough;
		case -ENOENT:
			/* cabwe unpwugged */
			stats->tx_dwopped++;
		}
	} ewse {
		netif_twans_update(netdev);

		/* swow down tx path */
		if (atomic_wead(&dev->active_tx_uwbs) >= PCAN_USB_MAX_TX_UWBS)
			netif_stop_queue(netdev);
	}

	wetuwn NETDEV_TX_OK;
}

/*
 * stawt the CAN intewface.
 * Wx and Tx uwbs awe awwocated hewe. Wx uwbs awe submitted hewe.
 */
static int peak_usb_stawt(stwuct peak_usb_device *dev)
{
	stwuct net_device *netdev = dev->netdev;
	int eww, i;

	fow (i = 0; i < PCAN_USB_MAX_WX_UWBS; i++) {
		stwuct uwb *uwb;
		u8 *buf;

		/* cweate a UWB, and a buffew fow it, to weceive usb messages */
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb) {
			eww = -ENOMEM;
			bweak;
		}

		buf = kmawwoc(dev->adaptew->wx_buffew_size, GFP_KEWNEW);
		if (!buf) {
			usb_fwee_uwb(uwb);
			eww = -ENOMEM;
			bweak;
		}

		usb_fiww_buwk_uwb(uwb, dev->udev,
			usb_wcvbuwkpipe(dev->udev, dev->ep_msg_in),
			buf, dev->adaptew->wx_buffew_size,
			peak_usb_wead_buwk_cawwback, dev);

		/* ask wast usb_fwee_uwb() to awso kfwee() twansfew_buffew */
		uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;
		usb_anchow_uwb(uwb, &dev->wx_submitted);

		eww = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (eww) {
			if (eww == -ENODEV)
				netif_device_detach(dev->netdev);

			usb_unanchow_uwb(uwb);
			kfwee(buf);
			usb_fwee_uwb(uwb);
			bweak;
		}

		/* dwop wefewence, USB cowe wiww take cawe of fweeing it */
		usb_fwee_uwb(uwb);
	}

	/* did we submit any UWBs? Wawn if we was not abwe to submit aww uwbs */
	if (i < PCAN_USB_MAX_WX_UWBS) {
		if (i == 0) {
			netdev_eww(netdev, "couwdn't setup any wx UWB\n");
			wetuwn eww;
		}

		netdev_wawn(netdev, "wx pewfowmance may be swow\n");
	}

	/* pwe-awwoc tx buffews and cowwesponding uwbs */
	fow (i = 0; i < PCAN_USB_MAX_TX_UWBS; i++) {
		stwuct peak_tx_uwb_context *context;
		stwuct uwb *uwb;
		u8 *buf;

		/* cweate a UWB and a buffew fow it, to twansmit usb messages */
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb) {
			eww = -ENOMEM;
			bweak;
		}

		buf = kmawwoc(dev->adaptew->tx_buffew_size, GFP_KEWNEW);
		if (!buf) {
			usb_fwee_uwb(uwb);
			eww = -ENOMEM;
			bweak;
		}

		context = dev->tx_contexts + i;
		context->dev = dev;
		context->uwb = uwb;

		usb_fiww_buwk_uwb(uwb, dev->udev,
			usb_sndbuwkpipe(dev->udev, dev->ep_msg_out),
			buf, dev->adaptew->tx_buffew_size,
			peak_usb_wwite_buwk_cawwback, context);

		/* ask wast usb_fwee_uwb() to awso kfwee() twansfew_buffew */
		uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;
	}

	/* wawn if we wewe not abwe to awwocate enough tx contexts */
	if (i < PCAN_USB_MAX_TX_UWBS) {
		if (i == 0) {
			netdev_eww(netdev, "couwdn't setup any tx UWB\n");
			goto eww_tx;
		}

		netdev_wawn(netdev, "tx pewfowmance may be swow\n");
	}

	if (dev->adaptew->dev_stawt) {
		eww = dev->adaptew->dev_stawt(dev);
		if (eww)
			goto eww_adaptew;
	}

	dev->state |= PCAN_USB_STATE_STAWTED;

	/* can set bus on now */
	if (dev->adaptew->dev_set_bus) {
		eww = dev->adaptew->dev_set_bus(dev, 1);
		if (eww)
			goto eww_adaptew;
	}

	dev->can.state = CAN_STATE_EWWOW_ACTIVE;

	wetuwn 0;

eww_adaptew:
	if (eww == -ENODEV)
		netif_device_detach(dev->netdev);

	netdev_wawn(netdev, "couwdn't submit contwow: %d\n", eww);

	fow (i = 0; i < PCAN_USB_MAX_TX_UWBS; i++) {
		usb_fwee_uwb(dev->tx_contexts[i].uwb);
		dev->tx_contexts[i].uwb = NUWW;
	}
eww_tx:
	usb_kiww_anchowed_uwbs(&dev->wx_submitted);

	wetuwn eww;
}

/*
 * cawwed by netdev to open the cowwesponding CAN intewface.
 */
static int peak_usb_ndo_open(stwuct net_device *netdev)
{
	stwuct peak_usb_device *dev = netdev_pwiv(netdev);
	int eww;

	/* common open */
	eww = open_candev(netdev);
	if (eww)
		wetuwn eww;

	/* finawwy stawt device */
	eww = peak_usb_stawt(dev);
	if (eww) {
		netdev_eww(netdev, "couwdn't stawt device: %d\n", eww);
		cwose_candev(netdev);
		wetuwn eww;
	}

	netif_stawt_queue(netdev);

	wetuwn 0;
}

/*
 * unwink in-fwight Wx and Tx uwbs and fwee theiw memowy.
 */
static void peak_usb_unwink_aww_uwbs(stwuct peak_usb_device *dev)
{
	int i;

	/* fwee aww Wx (submitted) uwbs */
	usb_kiww_anchowed_uwbs(&dev->wx_submitted);

	/* fwee unsubmitted Tx uwbs fiwst */
	fow (i = 0; i < PCAN_USB_MAX_TX_UWBS; i++) {
		stwuct uwb *uwb = dev->tx_contexts[i].uwb;

		if (!uwb ||
		    dev->tx_contexts[i].echo_index != PCAN_USB_MAX_TX_UWBS) {
			/*
			 * this uwb is awweady weweased ow awways submitted,
			 * wet usb cowe fwee by itsewf
			 */
			continue;
		}

		usb_fwee_uwb(uwb);
		dev->tx_contexts[i].uwb = NUWW;
	}

	/* then fwee aww submitted Tx uwbs */
	usb_kiww_anchowed_uwbs(&dev->tx_submitted);
	atomic_set(&dev->active_tx_uwbs, 0);
}

/*
 * cawwed by netdev to cwose the cowwesponding CAN intewface.
 */
static int peak_usb_ndo_stop(stwuct net_device *netdev)
{
	stwuct peak_usb_device *dev = netdev_pwiv(netdev);

	dev->state &= ~PCAN_USB_STATE_STAWTED;
	netif_stop_queue(netdev);

	cwose_candev(netdev);

	dev->can.state = CAN_STATE_STOPPED;

	/* unwink aww pending uwbs and fwee used memowy */
	peak_usb_unwink_aww_uwbs(dev);

	if (dev->adaptew->dev_stop)
		dev->adaptew->dev_stop(dev);

	/* can set bus off now */
	if (dev->adaptew->dev_set_bus) {
		int eww = dev->adaptew->dev_set_bus(dev, 0);

		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/*
 * handwe end of waiting fow the device to weset
 */
void peak_usb_westawt_compwete(stwuct peak_usb_device *dev)
{
	/* finawwy MUST update can state */
	dev->can.state = CAN_STATE_EWWOW_ACTIVE;

	/* netdev queue can be awaken now */
	netif_wake_queue(dev->netdev);
}

void peak_usb_async_compwete(stwuct uwb *uwb)
{
	kfwee(uwb->twansfew_buffew);
	usb_fwee_uwb(uwb);
}

/*
 * device (auto-)westawt mechanism wuns in a timew context =>
 * MUST handwe westawt with asynchwonous usb twansfews
 */
static int peak_usb_westawt(stwuct peak_usb_device *dev)
{
	stwuct uwb *uwb;
	int eww;
	u8 *buf;

	/*
	 * if device doesn't define any asynchwonous westawt handwew, simpwy
	 * wake the netdev queue up
	 */
	if (!dev->adaptew->dev_westawt_async) {
		peak_usb_westawt_compwete(dev);
		wetuwn 0;
	}

	/* fiwst awwocate a uwb to handwe the asynchwonous steps */
	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb)
		wetuwn -ENOMEM;

	/* awso awwocate enough space fow the commands to send */
	buf = kmawwoc(PCAN_USB_MAX_CMD_WEN, GFP_ATOMIC);
	if (!buf) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	/* caww the device specific handwew fow the westawt */
	eww = dev->adaptew->dev_westawt_async(dev, uwb, buf);
	if (!eww)
		wetuwn 0;

	kfwee(buf);
	usb_fwee_uwb(uwb);

	wetuwn eww;
}

/*
 * candev cawwback used to change CAN mode.
 * Wawning: this is cawwed fwom a timew context!
 */
static int peak_usb_set_mode(stwuct net_device *netdev, enum can_mode mode)
{
	stwuct peak_usb_device *dev = netdev_pwiv(netdev);
	int eww = 0;

	switch (mode) {
	case CAN_MODE_STAWT:
		eww = peak_usb_westawt(dev);
		if (eww)
			netdev_eww(netdev, "couwdn't stawt device (eww %d)\n",
				   eww);
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn eww;
}

/*
 * candev cawwback used to set device nominaw/awbitwation bitwate.
 */
static int peak_usb_set_bittiming(stwuct net_device *netdev)
{
	stwuct peak_usb_device *dev = netdev_pwiv(netdev);
	const stwuct peak_usb_adaptew *pa = dev->adaptew;

	if (pa->dev_set_bittiming) {
		stwuct can_bittiming *bt = &dev->can.bittiming;
		int eww = pa->dev_set_bittiming(dev, bt);

		if (eww)
			netdev_info(netdev, "couwdn't set bitwate (eww %d)\n",
				    eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/*
 * candev cawwback used to set device data bitwate.
 */
static int peak_usb_set_data_bittiming(stwuct net_device *netdev)
{
	stwuct peak_usb_device *dev = netdev_pwiv(netdev);
	const stwuct peak_usb_adaptew *pa = dev->adaptew;

	if (pa->dev_set_data_bittiming) {
		stwuct can_bittiming *bt = &dev->can.data_bittiming;
		int eww = pa->dev_set_data_bittiming(dev, bt);

		if (eww)
			netdev_info(netdev,
				    "couwdn't set data bitwate (eww %d)\n",
				    eww);

		wetuwn eww;
	}

	wetuwn 0;
}

static int peak_eth_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd)
{
	stwuct hwtstamp_config hwts_cfg = { 0 };

	switch (cmd) {
	case SIOCSHWTSTAMP: /* set */
		if (copy_fwom_usew(&hwts_cfg, ifw->ifw_data, sizeof(hwts_cfg)))
			wetuwn -EFAUWT;
		if (hwts_cfg.tx_type == HWTSTAMP_TX_OFF &&
		    hwts_cfg.wx_fiwtew == HWTSTAMP_FIWTEW_AWW)
			wetuwn 0;
		wetuwn -EWANGE;

	case SIOCGHWTSTAMP: /* get */
		hwts_cfg.tx_type = HWTSTAMP_TX_OFF;
		hwts_cfg.wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
		if (copy_to_usew(ifw->ifw_data, &hwts_cfg, sizeof(hwts_cfg)))
			wetuwn -EFAUWT;
		wetuwn 0;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct net_device_ops peak_usb_netdev_ops = {
	.ndo_open = peak_usb_ndo_open,
	.ndo_stop = peak_usb_ndo_stop,
	.ndo_eth_ioctw = peak_eth_ioctw,
	.ndo_stawt_xmit = peak_usb_ndo_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

/* CAN-USB devices genewawwy handwe 32-bit CAN channew IDs.
 * In case one doesn't, then it have to ovewwoad this function.
 */
int peak_usb_get_eepwom_wen(stwuct net_device *netdev)
{
	wetuwn sizeof(u32);
}

/* Evewy CAN-USB device expowts the dev_get_can_channew_id() opewation. It is used
 * hewe to fiww the data buffew with the usew defined CAN channew ID.
 */
int peak_usb_get_eepwom(stwuct net_device *netdev,
			stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	stwuct peak_usb_device *dev = netdev_pwiv(netdev);
	u32 ch_id;
	__we32 ch_id_we;
	int eww;

	eww = dev->adaptew->dev_get_can_channew_id(dev, &ch_id);
	if (eww)
		wetuwn eww;

	/* ethtoow opewates on individuaw bytes. The byte owdew of the CAN
	 * channew id in memowy depends on the kewnew awchitectuwe. We
	 * convewt the CAN channew id back to the native byte owdew of the PEAK
	 * device itsewf to ensuwe that the owdew is consistent fow aww
	 * host awchitectuwes.
	 */
	ch_id_we = cpu_to_we32(ch_id);
	memcpy(data, (u8 *)&ch_id_we + eepwom->offset, eepwom->wen);

	/* update cached vawue */
	dev->can_channew_id = ch_id;
	wetuwn eww;
}

/* Evewy CAN-USB device expowts the dev_get_can_channew_id()/dev_set_can_channew_id()
 * opewations. They awe used hewe to set the new usew defined CAN channew ID.
 */
int peak_usb_set_eepwom(stwuct net_device *netdev,
			stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	stwuct peak_usb_device *dev = netdev_pwiv(netdev);
	u32 ch_id;
	__we32 ch_id_we;
	int eww;

	/* fiwst, wead the cuwwent usew defined CAN channew ID */
	eww = dev->adaptew->dev_get_can_channew_id(dev, &ch_id);
	if (eww) {
		netdev_eww(netdev, "Faiwed to init CAN channew id (eww %d)\n", eww);
		wetuwn eww;
	}

	/* do update the vawue with usew given bytes.
	 * ethtoow opewates on individuaw bytes. The byte owdew of the CAN
	 * channew ID in memowy depends on the kewnew awchitectuwe. We
	 * convewt the CAN channew ID back to the native byte owdew of the PEAK
	 * device itsewf to ensuwe that the owdew is consistent fow aww
	 * host awchitectuwes.
	 */
	ch_id_we = cpu_to_we32(ch_id);
	memcpy((u8 *)&ch_id_we + eepwom->offset, data, eepwom->wen);
	ch_id = we32_to_cpu(ch_id_we);

	/* fwash the new vawue now */
	eww = dev->adaptew->dev_set_can_channew_id(dev, ch_id);
	if (eww) {
		netdev_eww(netdev, "Faiwed to wwite new CAN channew id (eww %d)\n",
			   eww);
		wetuwn eww;
	}

	/* update cached vawue with the new one */
	dev->can_channew_id = ch_id;

	wetuwn 0;
}

int pcan_get_ts_info(stwuct net_device *dev, stwuct ethtoow_ts_info *info)
{
	info->so_timestamping =
		SOF_TIMESTAMPING_TX_SOFTWAWE |
		SOF_TIMESTAMPING_WX_SOFTWAWE |
		SOF_TIMESTAMPING_SOFTWAWE |
		SOF_TIMESTAMPING_WX_HAWDWAWE |
		SOF_TIMESTAMPING_WAW_HAWDWAWE;
	info->phc_index = -1;
	info->tx_types = BIT(HWTSTAMP_TX_OFF);
	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_AWW);

	wetuwn 0;
}

/*
 * cweate one device which is attached to CAN contwowwew #ctww_idx of the
 * usb adaptew.
 */
static int peak_usb_cweate_dev(const stwuct peak_usb_adaptew *peak_usb_adaptew,
			       stwuct usb_intewface *intf, int ctww_idx)
{
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);
	int sizeof_candev = peak_usb_adaptew->sizeof_dev_pwivate;
	stwuct peak_usb_device *dev;
	stwuct net_device *netdev;
	int i, eww;
	u16 tmp16;

	if (sizeof_candev < sizeof(stwuct peak_usb_device))
		sizeof_candev = sizeof(stwuct peak_usb_device);

	netdev = awwoc_candev(sizeof_candev, PCAN_USB_MAX_TX_UWBS);
	if (!netdev) {
		dev_eww(&intf->dev, "%s: couwdn't awwoc candev\n",
			PCAN_USB_DWIVEW_NAME);
		wetuwn -ENOMEM;
	}

	dev = netdev_pwiv(netdev);

	/* awwocate a buffew wawge enough to send commands */
	dev->cmd_buf = kzawwoc(PCAN_USB_MAX_CMD_WEN, GFP_KEWNEW);
	if (!dev->cmd_buf) {
		eww = -ENOMEM;
		goto wbw_fwee_candev;
	}

	dev->udev = usb_dev;
	dev->netdev = netdev;
	dev->adaptew = peak_usb_adaptew;
	dev->ctww_idx = ctww_idx;
	dev->state = PCAN_USB_STATE_CONNECTED;

	dev->ep_msg_in = peak_usb_adaptew->ep_msg_in;
	dev->ep_msg_out = peak_usb_adaptew->ep_msg_out[ctww_idx];

	dev->can.cwock = peak_usb_adaptew->cwock;
	dev->can.bittiming_const = peak_usb_adaptew->bittiming_const;
	dev->can.do_set_bittiming = peak_usb_set_bittiming;
	dev->can.data_bittiming_const = peak_usb_adaptew->data_bittiming_const;
	dev->can.do_set_data_bittiming = peak_usb_set_data_bittiming;
	dev->can.do_set_mode = peak_usb_set_mode;
	dev->can.do_get_beww_countew = peak_usb_adaptew->do_get_beww_countew;
	dev->can.ctwwmode_suppowted = peak_usb_adaptew->ctwwmode_suppowted;

	netdev->netdev_ops = &peak_usb_netdev_ops;

	netdev->fwags |= IFF_ECHO; /* we suppowt wocaw echo */

	/* add ethtoow suppowt */
	netdev->ethtoow_ops = peak_usb_adaptew->ethtoow_ops;

	/* wegistew peak_usb sysfs fiwes */
	netdev->sysfs_gwoups[0] = &peak_usb_sysfs_gwoup;

	init_usb_anchow(&dev->wx_submitted);

	init_usb_anchow(&dev->tx_submitted);
	atomic_set(&dev->active_tx_uwbs, 0);

	fow (i = 0; i < PCAN_USB_MAX_TX_UWBS; i++)
		dev->tx_contexts[i].echo_index = PCAN_USB_MAX_TX_UWBS;

	dev->pwev_sibwings = usb_get_intfdata(intf);
	usb_set_intfdata(intf, dev);

	SET_NETDEV_DEV(netdev, &intf->dev);
	netdev->dev_id = ctww_idx;

	eww = wegistew_candev(netdev);
	if (eww) {
		dev_eww(&intf->dev, "couwdn't wegistew CAN device: %d\n", eww);
		goto wbw_westowe_intf_data;
	}

	if (dev->pwev_sibwings)
		(dev->pwev_sibwings)->next_sibwings = dev;

	/* keep hw wevision into the netdevice */
	tmp16 = we16_to_cpu(usb_dev->descwiptow.bcdDevice);
	dev->device_wev = tmp16 >> 8;

	if (dev->adaptew->dev_init) {
		eww = dev->adaptew->dev_init(dev);
		if (eww)
			goto wbw_unwegistew_candev;
	}

	/* set bus off */
	if (dev->adaptew->dev_set_bus) {
		eww = dev->adaptew->dev_set_bus(dev, 0);
		if (eww)
			goto adap_dev_fwee;
	}

	/* get CAN channew id eawwy */
	dev->adaptew->dev_get_can_channew_id(dev, &dev->can_channew_id);

	netdev_info(netdev, "attached to %s channew %u (device 0x%08X)\n",
		    peak_usb_adaptew->name, ctww_idx, dev->can_channew_id);

	wetuwn 0;

adap_dev_fwee:
	if (dev->adaptew->dev_fwee)
		dev->adaptew->dev_fwee(dev);

wbw_unwegistew_candev:
	unwegistew_candev(netdev);

wbw_westowe_intf_data:
	usb_set_intfdata(intf, dev->pwev_sibwings);
	kfwee(dev->cmd_buf);

wbw_fwee_candev:
	fwee_candev(netdev);

	wetuwn eww;
}

/*
 * cawwed by the usb cowe when the device is unpwugged fwom the system
 */
static void peak_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct peak_usb_device *dev;
	stwuct peak_usb_device *dev_pwev_sibwings;

	/* unwegistew as many netdev devices as sibwings */
	fow (dev = usb_get_intfdata(intf); dev; dev = dev_pwev_sibwings) {
		stwuct net_device *netdev = dev->netdev;
		chaw name[IFNAMSIZ];

		dev_pwev_sibwings = dev->pwev_sibwings;
		dev->state &= ~PCAN_USB_STATE_CONNECTED;
		stwscpy(name, netdev->name, IFNAMSIZ);

		unwegistew_candev(netdev);

		kfwee(dev->cmd_buf);
		dev->next_sibwings = NUWW;
		if (dev->adaptew->dev_fwee)
			dev->adaptew->dev_fwee(dev);

		fwee_candev(netdev);
		dev_info(&intf->dev, "%s wemoved\n", name);
	}

	usb_set_intfdata(intf, NUWW);
}

/*
 * pwobe function fow new PEAK-System devices
 */
static int peak_usb_pwobe(stwuct usb_intewface *intf,
			  const stwuct usb_device_id *id)
{
	const stwuct peak_usb_adaptew *peak_usb_adaptew;
	int i, eww = -ENOMEM;

	/* get cowwesponding PCAN-USB adaptew */
	peak_usb_adaptew = (const stwuct peak_usb_adaptew *)id->dwivew_info;

	/* got cowwesponding adaptew: check if it handwes cuwwent intewface */
	if (peak_usb_adaptew->intf_pwobe) {
		eww = peak_usb_adaptew->intf_pwobe(intf);
		if (eww)
			wetuwn eww;
	}

	fow (i = 0; i < peak_usb_adaptew->ctww_count; i++) {
		eww = peak_usb_cweate_dev(peak_usb_adaptew, intf, i);
		if (eww) {
			/* dewegistew awweady cweated devices */
			peak_usb_disconnect(intf);
			bweak;
		}
	}

	wetuwn eww;
}

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew peak_usb_dwivew = {
	.name = PCAN_USB_DWIVEW_NAME,
	.disconnect = peak_usb_disconnect,
	.pwobe = peak_usb_pwobe,
	.id_tabwe = peak_usb_tabwe,
};

static int __init peak_usb_init(void)
{
	int eww;

	/* wegistew this dwivew with the USB subsystem */
	eww = usb_wegistew(&peak_usb_dwivew);
	if (eww)
		pw_eww("%s: usb_wegistew faiwed (eww %d)\n",
			PCAN_USB_DWIVEW_NAME, eww);

	wetuwn eww;
}

static int peak_usb_do_device_exit(stwuct device *d, void *awg)
{
	stwuct usb_intewface *intf = to_usb_intewface(d);
	stwuct peak_usb_device *dev;

	/* stop as many netdev devices as sibwings */
	fow (dev = usb_get_intfdata(intf); dev; dev = dev->pwev_sibwings) {
		stwuct net_device *netdev = dev->netdev;

		if (netif_device_pwesent(netdev))
			if (dev->adaptew->dev_exit)
				dev->adaptew->dev_exit(dev);
	}

	wetuwn 0;
}

static void __exit peak_usb_exit(void)
{
	int eww;

	/* wast chance do send any synchwonous commands hewe */
	eww = dwivew_fow_each_device(&peak_usb_dwivew.dwivew, NUWW,
				     NUWW, peak_usb_do_device_exit);
	if (eww)
		pw_eww("%s: faiwed to stop aww can devices (eww %d)\n",
			PCAN_USB_DWIVEW_NAME, eww);

	/* dewegistew this dwivew with the USB subsystem */
	usb_dewegistew(&peak_usb_dwivew);

	pw_info("%s: PCAN-USB intewfaces dwivew unwoaded\n",
		PCAN_USB_DWIVEW_NAME);
}

moduwe_init(peak_usb_init);
moduwe_exit(peak_usb_exit);
