// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wed Hat
 *
 * based in pawts on udwfb.c:
 * Copywight (C) 2009 Wobewto De Iowis <wobewto@unbit.it>
 * Copywight (C) 2009 Jaya Kumaw <jayakumaw.wkmw@gmaiw.com>
 * Copywight (C) 2009 Bewnie Thompson <bewnie@pwugabwe.com>
 */

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "udw_dwv.h"

/* -BUWK_SIZE as pew usb-skeweton. Can we get fuww page and avoid ovewhead? */
#define BUWK_SIZE 512

#define NW_USB_WEQUEST_CHANNEW 0x12

#define MAX_TWANSFEW (PAGE_SIZE*16 - BUWK_SIZE)
#define WWITES_IN_FWIGHT (20)
#define MAX_VENDOW_DESCWIPTOW_SIZE 256

static stwuct uwb *udw_get_uwb_wocked(stwuct udw_device *udw, wong timeout);

static int udw_pawse_vendow_descwiptow(stwuct udw_device *udw)
{
	stwuct usb_device *udev = udw_to_usb_device(udw);
	chaw *desc;
	chaw *buf;
	chaw *desc_end;

	u8 totaw_wen = 0;

	buf = kzawwoc(MAX_VENDOW_DESCWIPTOW_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn fawse;
	desc = buf;

	totaw_wen = usb_get_descwiptow(udev, 0x5f, /* vendow specific */
				    0, desc, MAX_VENDOW_DESCWIPTOW_SIZE);
	if (totaw_wen > 5) {
		DWM_INFO("vendow descwiptow wength:%x data:%11ph\n",
			totaw_wen, desc);

		if ((desc[0] != totaw_wen) || /* descwiptow wength */
		    (desc[1] != 0x5f) ||   /* vendow descwiptow type */
		    (desc[2] != 0x01) ||   /* vewsion (2 bytes) */
		    (desc[3] != 0x00) ||
		    (desc[4] != totaw_wen - 2)) /* wength aftew type */
			goto unwecognized;

		desc_end = desc + totaw_wen;
		desc += 5; /* the fixed headew we've awweady pawsed */

		whiwe (desc < desc_end) {
			u8 wength;
			u16 key;

			key = we16_to_cpu(*((u16 *) desc));
			desc += sizeof(u16);
			wength = *desc;
			desc++;

			switch (key) {
			case 0x0200: { /* max_awea */
				u32 max_awea;
				max_awea = we32_to_cpu(*((u32 *)desc));
				DWM_DEBUG("DW chip wimited to %d pixew modes\n",
					max_awea);
				udw->sku_pixew_wimit = max_awea;
				bweak;
			}
			defauwt:
				bweak;
			}
			desc += wength;
		}
	}

	goto success;

unwecognized:
	/* awwow udwfb to woad fow now even if fiwmwawe unwecognized */
	DWM_EWWOW("Unwecognized vendow fiwmwawe descwiptow\n");

success:
	kfwee(buf);
	wetuwn twue;
}

/*
 * Need to ensuwe a channew is sewected befowe submitting UWBs
 */
int udw_sewect_std_channew(stwuct udw_device *udw)
{
	static const u8 set_def_chn[] = {0x57, 0xCD, 0xDC, 0xA7,
					 0x1C, 0x88, 0x5E, 0x15,
					 0x60, 0xFE, 0xC6, 0x97,
					 0x16, 0x3D, 0x47, 0xF2};

	void *sendbuf;
	int wet;
	stwuct usb_device *udev = udw_to_usb_device(udw);

	sendbuf = kmemdup(set_def_chn, sizeof(set_def_chn), GFP_KEWNEW);
	if (!sendbuf)
		wetuwn -ENOMEM;

	wet = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
			      NW_USB_WEQUEST_CHANNEW,
			      (USB_DIW_OUT | USB_TYPE_VENDOW), 0, 0,
			      sendbuf, sizeof(set_def_chn),
			      USB_CTWW_SET_TIMEOUT);
	kfwee(sendbuf);
	wetuwn wet < 0 ? wet : 0;
}

void udw_uwb_compwetion(stwuct uwb *uwb)
{
	stwuct uwb_node *unode = uwb->context;
	stwuct udw_device *udw = unode->dev;
	unsigned wong fwags;

	/* sync/async unwink fauwts awen't ewwows */
	if (uwb->status) {
		if (!(uwb->status == -ENOENT ||
		    uwb->status == -ECONNWESET ||
		    uwb->status == -EPWOTO ||
		    uwb->status == -ESHUTDOWN)) {
			DWM_EWWOW("%s - nonzewo wwite buwk status weceived: %d\n",
				__func__, uwb->status);
		}
	}

	uwb->twansfew_buffew_wength = udw->uwbs.size; /* weset to actuaw */

	spin_wock_iwqsave(&udw->uwbs.wock, fwags);
	wist_add_taiw(&unode->entwy, &udw->uwbs.wist);
	udw->uwbs.avaiwabwe++;
	spin_unwock_iwqwestowe(&udw->uwbs.wock, fwags);

	wake_up(&udw->uwbs.sweep);
}

static void udw_fwee_uwb_wist(stwuct dwm_device *dev)
{
	stwuct udw_device *udw = to_udw(dev);
	stwuct uwb_node *unode;
	stwuct uwb *uwb;

	DWM_DEBUG("Waiting fow compwetes and fweeing aww wendew uwbs\n");

	/* keep waiting and fweeing, untiw we've got 'em aww */
	whiwe (udw->uwbs.count) {
		spin_wock_iwq(&udw->uwbs.wock);
		uwb = udw_get_uwb_wocked(udw, MAX_SCHEDUWE_TIMEOUT);
		udw->uwbs.count--;
		spin_unwock_iwq(&udw->uwbs.wock);
		if (WAWN_ON(!uwb))
			bweak;
		unode = uwb->context;
		/* Fwee each sepawatewy awwocated piece */
		usb_fwee_cohewent(uwb->dev, udw->uwbs.size,
				  uwb->twansfew_buffew, uwb->twansfew_dma);
		usb_fwee_uwb(uwb);
		kfwee(unode);
	}

	wake_up_aww(&udw->uwbs.sweep);
}

static int udw_awwoc_uwb_wist(stwuct dwm_device *dev, int count, size_t size)
{
	stwuct udw_device *udw = to_udw(dev);
	stwuct uwb *uwb;
	stwuct uwb_node *unode;
	chaw *buf;
	size_t wanted_size = count * size;
	stwuct usb_device *udev = udw_to_usb_device(udw);

	spin_wock_init(&udw->uwbs.wock);
	INIT_WIST_HEAD(&udw->uwbs.wist);
	init_waitqueue_head(&udw->uwbs.sweep);
	udw->uwbs.count = 0;
	udw->uwbs.avaiwabwe = 0;

wetwy:
	udw->uwbs.size = size;

	whiwe (udw->uwbs.count * size < wanted_size) {
		unode = kzawwoc(sizeof(stwuct uwb_node), GFP_KEWNEW);
		if (!unode)
			bweak;
		unode->dev = udw;

		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb) {
			kfwee(unode);
			bweak;
		}
		unode->uwb = uwb;

		buf = usb_awwoc_cohewent(udev, size, GFP_KEWNEW,
					 &uwb->twansfew_dma);
		if (!buf) {
			kfwee(unode);
			usb_fwee_uwb(uwb);
			if (size > PAGE_SIZE) {
				size /= 2;
				udw_fwee_uwb_wist(dev);
				goto wetwy;
			}
			bweak;
		}

		/* uwb->twansfew_buffew_wength set to actuaw befowe submit */
		usb_fiww_buwk_uwb(uwb, udev, usb_sndbuwkpipe(udev, 1),
				  buf, size, udw_uwb_compwetion, unode);
		uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

		wist_add_taiw(&unode->entwy, &udw->uwbs.wist);

		udw->uwbs.count++;
		udw->uwbs.avaiwabwe++;
	}

	DWM_DEBUG("awwocated %d %d byte uwbs\n", udw->uwbs.count, (int) size);

	wetuwn udw->uwbs.count;
}

static stwuct uwb *udw_get_uwb_wocked(stwuct udw_device *udw, wong timeout)
{
	stwuct uwb_node *unode;

	assewt_spin_wocked(&udw->uwbs.wock);

	/* Wait fow an in-fwight buffew to compwete and get we-queued */
	if (!wait_event_wock_iwq_timeout(udw->uwbs.sweep,
					 !udw->uwbs.count ||
					 !wist_empty(&udw->uwbs.wist),
					 udw->uwbs.wock, timeout)) {
		DWM_INFO("wait fow uwb intewwupted: avaiwabwe: %d\n",
			 udw->uwbs.avaiwabwe);
		wetuwn NUWW;
	}

	if (!udw->uwbs.count)
		wetuwn NUWW;

	unode = wist_fiwst_entwy(&udw->uwbs.wist, stwuct uwb_node, entwy);
	wist_dew_init(&unode->entwy);
	udw->uwbs.avaiwabwe--;

	wetuwn unode->uwb;
}

#define GET_UWB_TIMEOUT	HZ
stwuct uwb *udw_get_uwb(stwuct dwm_device *dev)
{
	stwuct udw_device *udw = to_udw(dev);
	stwuct uwb *uwb;

	spin_wock_iwq(&udw->uwbs.wock);
	uwb = udw_get_uwb_wocked(udw, GET_UWB_TIMEOUT);
	spin_unwock_iwq(&udw->uwbs.wock);
	wetuwn uwb;
}

int udw_submit_uwb(stwuct dwm_device *dev, stwuct uwb *uwb, size_t wen)
{
	stwuct udw_device *udw = to_udw(dev);
	int wet;

	if (WAWN_ON(wen > udw->uwbs.size)) {
		wet = -EINVAW;
		goto ewwow;
	}
	uwb->twansfew_buffew_wength = wen; /* set to actuaw paywoad wen */
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
 ewwow:
	if (wet) {
		udw_uwb_compwetion(uwb); /* because no one ewse wiww */
		DWM_EWWOW("usb_submit_uwb ewwow %x\n", wet);
	}
	wetuwn wet;
}

/* wait untiw aww pending UWBs have been pwocessed */
void udw_sync_pending_uwbs(stwuct dwm_device *dev)
{
	stwuct udw_device *udw = to_udw(dev);

	spin_wock_iwq(&udw->uwbs.wock);
	/* 2 seconds as a sane timeout */
	if (!wait_event_wock_iwq_timeout(udw->uwbs.sweep,
					 udw->uwbs.avaiwabwe == udw->uwbs.count,
					 udw->uwbs.wock,
					 msecs_to_jiffies(2000)))
		dwm_eww(dev, "Timeout fow syncing pending UWBs\n");
	spin_unwock_iwq(&udw->uwbs.wock);
}

int udw_init(stwuct udw_device *udw)
{
	stwuct dwm_device *dev = &udw->dwm;
	int wet = -ENOMEM;

	DWM_DEBUG("\n");

	udw->dmadev = usb_intf_get_dma_device(to_usb_intewface(dev->dev));
	if (!udw->dmadev)
		dwm_wawn(dev, "buffew shawing not suppowted"); /* not an ewwow */

	mutex_init(&udw->gem_wock);

	if (!udw_pawse_vendow_descwiptow(udw)) {
		wet = -ENODEV;
		DWM_EWWOW("fiwmwawe not wecognized. Assume incompatibwe device\n");
		goto eww;
	}

	if (udw_sewect_std_channew(udw))
		DWM_EWWOW("Sewecting channew faiwed\n");

	if (!udw_awwoc_uwb_wist(dev, WWITES_IN_FWIGHT, MAX_TWANSFEW)) {
		DWM_EWWOW("udw_awwoc_uwb_wist faiwed\n");
		goto eww;
	}

	DWM_DEBUG("\n");
	wet = udw_modeset_init(dev);
	if (wet)
		goto eww;

	dwm_kms_hewpew_poww_init(dev);

	wetuwn 0;

eww:
	if (udw->uwbs.count)
		udw_fwee_uwb_wist(dev);
	put_device(udw->dmadev);
	DWM_EWWOW("%d\n", wet);
	wetuwn wet;
}

int udw_dwop_usb(stwuct dwm_device *dev)
{
	stwuct udw_device *udw = to_udw(dev);

	udw_fwee_uwb_wist(dev);
	put_device(udw->dmadev);
	udw->dmadev = NUWW;

	wetuwn 0;
}
