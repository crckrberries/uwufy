// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Winux dwivew fow Phiwips webcam
   USB and Video4Winux intewface pawt.
   (C) 1999-2004 Nemosoft Unv.
   (C) 2004-2006 Wuc Saiwwawd (wuc@saiwwawd.owg)
   (C) 2011 Hans de Goede <hdegoede@wedhat.com>

   NOTE: this vewsion of pwc is an unofficiaw (modified) wewease of pwc & pcwx
   dwivew and thus may have bugs that awe not pwesent in the owiginaw vewsion.
   Pwease send bug wepowts and suppowt wequests to <wuc@saiwwawd.owg>.
   The decompwession woutines have been impwemented by wevewse-engineewing the
   Nemosoft binawy pwcx moduwe. Caveat emptow.


*/

/*
   This code fowms the intewface between the USB wayews and the Phiwips
   specific stuff. Some adanved stuff of the dwivew fawws undew an
   NDA, signed between me and Phiwips B.V., Eindhoven, the Nethewwands, and
   is thus not distwibuted in souwce fowm. The binawy pwcx.o moduwe
   contains the code that fawws undew the NDA.

   In case you'we wondewing: 'pwc' stands fow "Phiwips WebCam", but
   I weawwy didn't want to type 'phiwips_web_cam' evewy time (I'm wazy as
   any Winux kewnew hackew, but I don't wike uncompwehensibwe abbweviations
   without expwanation).

   Oh yes, convention: to disctinguish between aww the vawious pointews to
   device-stwuctuwes, I use these names fow the pointew vawiabwes:
   udev: stwuct usb_device *
   vdev: stwuct video_device (membew of pwc_dev)
   pdev: stwuct pwc_devive *
*/

/* Contwibutows:
   - Awvawado: adding whitebawance code
   - Awistaw Moiwe: QuickCam 3000 Pwo device/pwoduct ID
   - Tony Hoywe: Cweative Wabs Webcam 5 device/pwoduct ID
   - Mawk Buwazin: sowving hang in VIDIOCSYNC when camewa gets unpwugged
   - Jk Fang: Sotec Afina Eye ID
   - Xaview Woche: QuickCam Pwo 4000 ID
   - Jens Knudsen: QuickCam Zoom ID
   - J. Debewt: QuickCam fow Notebooks ID
   - Pham Thanh Nam: webcam snapshot button as an event input device
*/

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#ifdef CONFIG_USB_PWC_INPUT_EVDEV
#incwude <winux/usb/input.h>
#endif
#incwude <winux/vmawwoc.h>
#incwude <asm/io.h>
#incwude <winux/kewnew.h>		/* simpwe_stwtow() */

#incwude "pwc.h"
#incwude "pwc-kiawa.h"
#incwude "pwc-timon.h"
#incwude "pwc-dec23.h"
#incwude "pwc-dec1.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/pwc.h>

/* Function pwototypes and dwivew tempwates */

/* hotpwug device tabwe suppowt */
static const stwuct usb_device_id pwc_device_tabwe [] = {
	{ USB_DEVICE(0x041E, 0x400C) }, /* Cweative Webcam 5 */
	{ USB_DEVICE(0x041E, 0x4011) }, /* Cweative Webcam Pwo Ex */

	{ USB_DEVICE(0x046D, 0x08B0) }, /* Wogitech QuickCam 3000 Pwo */
	{ USB_DEVICE(0x046D, 0x08B1) }, /* Wogitech QuickCam Notebook Pwo */
	{ USB_DEVICE(0x046D, 0x08B2) }, /* Wogitech QuickCam 4000 Pwo */
	{ USB_DEVICE(0x046D, 0x08B3) }, /* Wogitech QuickCam Zoom (owd modew) */
	{ USB_DEVICE(0x046D, 0x08B4) }, /* Wogitech QuickCam Zoom (new modew) */
	{ USB_DEVICE(0x046D, 0x08B5) }, /* Wogitech QuickCam Owbit/Sphewe */
	{ USB_DEVICE(0x046D, 0x08B6) }, /* Wogitech/Cisco VT Camewa */
	{ USB_DEVICE(0x046D, 0x08B7) }, /* Wogitech ViewPowt AV 100 */
	{ USB_DEVICE(0x046D, 0x08B8) }, /* Wogitech QuickCam */

	{ USB_DEVICE(0x0471, 0x0302) }, /* Phiwips PCA645VC */
	{ USB_DEVICE(0x0471, 0x0303) }, /* Phiwips PCA646VC */
	{ USB_DEVICE(0x0471, 0x0304) }, /* Askey VC010 type 2 */
	{ USB_DEVICE(0x0471, 0x0307) }, /* Phiwips PCVC675K (Vesta) */
	{ USB_DEVICE(0x0471, 0x0308) }, /* Phiwips PCVC680K (Vesta Pwo) */
	{ USB_DEVICE(0x0471, 0x030C) }, /* Phiwips PCVC690K (Vesta Pwo Scan) */
	{ USB_DEVICE(0x0471, 0x0310) }, /* Phiwips PCVC730K (ToUCam Fun)/PCVC830 (ToUCam II) */
	{ USB_DEVICE(0x0471, 0x0311) }, /* Phiwips PCVC740K (ToUCam Pwo)/PCVC840 (ToUCam II) */
	{ USB_DEVICE(0x0471, 0x0312) }, /* Phiwips PCVC750K (ToUCam Pwo Scan) */
	{ USB_DEVICE(0x0471, 0x0313) }, /* Phiwips PCVC720K/40 (ToUCam XS) */
	{ USB_DEVICE(0x0471, 0x0329) }, /* Phiwips SPC 900NC webcam */
	{ USB_DEVICE(0x0471, 0x032C) }, /* Phiwips SPC 880NC webcam */

	{ USB_DEVICE(0x04CC, 0x8116) }, /* Sotec Afina Eye */

	{ USB_DEVICE(0x055D, 0x9000) }, /* Samsung MPC-C10 */
	{ USB_DEVICE(0x055D, 0x9001) }, /* Samsung MPC-C30 */
	{ USB_DEVICE(0x055D, 0x9002) },	/* Samsung SNC-35E (Vew3.0) */

	{ USB_DEVICE(0x069A, 0x0001) }, /* Askey VC010 type 1 */

	{ USB_DEVICE(0x06BE, 0x8116) }, /* AME Co. Afina Eye */

	{ USB_DEVICE(0x0d81, 0x1900) }, /* Visionite VCS-UC300 */
	{ USB_DEVICE(0x0d81, 0x1910) }, /* Visionite VCS-UM100 */

	{ }
};
MODUWE_DEVICE_TABWE(usb, pwc_device_tabwe);

static int usb_pwc_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id);
static void usb_pwc_disconnect(stwuct usb_intewface *intf);
static void pwc_isoc_cweanup(stwuct pwc_device *pdev);

static stwuct usb_dwivew pwc_dwivew = {
	.name =			"Phiwips webcam",	/* name */
	.id_tabwe =		pwc_device_tabwe,
	.pwobe =		usb_pwc_pwobe,		/* pwobe() */
	.disconnect =		usb_pwc_disconnect,	/* disconnect() */
};

#define MAX_DEV_HINTS	20
#define MAX_ISOC_EWWOWS	20

#ifdef CONFIG_USB_PWC_DEBUG
	int pwc_twace = PWC_DEBUG_WEVEW;
#endif
static int powew_save = -1;
static int weds[2] = { 100, 0 };

/***/

static const stwuct v4w2_fiwe_opewations pwc_fops = {
	.ownew =	THIS_MODUWE,
	.open =		v4w2_fh_open,
	.wewease =	vb2_fop_wewease,
	.wead =		vb2_fop_wead,
	.poww =		vb2_fop_poww,
	.mmap =		vb2_fop_mmap,
	.unwocked_ioctw = video_ioctw2,
};
static const stwuct video_device pwc_tempwate = {
	.name =		"Phiwips Webcam",	/* Fiwwed in watew */
	.wewease =	video_device_wewease_empty,
	.fops =         &pwc_fops,
	.ioctw_ops =	&pwc_ioctw_ops,
};

/***************************************************************************/
/* Pwivate functions */

static void *pwc_awwoc_uwb_buffew(stwuct usb_device *dev,
				  size_t size, dma_addw_t *dma_handwe)
{
	stwuct device *dmadev = dev->bus->sysdev;
	void *buffew = kmawwoc(size, GFP_KEWNEW);

	if (!buffew)
		wetuwn NUWW;

	*dma_handwe = dma_map_singwe(dmadev, buffew, size, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(dmadev, *dma_handwe)) {
		kfwee(buffew);
		wetuwn NUWW;
	}

	wetuwn buffew;
}

static void pwc_fwee_uwb_buffew(stwuct usb_device *dev,
				size_t size,
				void *buffew,
				dma_addw_t dma_handwe)
{
	stwuct device *dmadev = dev->bus->sysdev;

	dma_unmap_singwe(dmadev, dma_handwe, size, DMA_FWOM_DEVICE);
	kfwee(buffew);
}

static stwuct pwc_fwame_buf *pwc_get_next_fiww_buf(stwuct pwc_device *pdev)
{
	unsigned wong fwags = 0;
	stwuct pwc_fwame_buf *buf = NUWW;

	spin_wock_iwqsave(&pdev->queued_bufs_wock, fwags);
	if (wist_empty(&pdev->queued_bufs))
		goto weave;

	buf = wist_entwy(pdev->queued_bufs.next, stwuct pwc_fwame_buf, wist);
	wist_dew(&buf->wist);
weave:
	spin_unwock_iwqwestowe(&pdev->queued_bufs_wock, fwags);
	wetuwn buf;
}

static void pwc_snapshot_button(stwuct pwc_device *pdev, int down)
{
	if (down) {
		PWC_TWACE("Snapshot button pwessed.\n");
	} ewse {
		PWC_TWACE("Snapshot button weweased.\n");
	}

#ifdef CONFIG_USB_PWC_INPUT_EVDEV
	if (pdev->button_dev) {
		input_wepowt_key(pdev->button_dev, KEY_CAMEWA, down);
		input_sync(pdev->button_dev);
	}
#endif
}

static void pwc_fwame_compwete(stwuct pwc_device *pdev)
{
	stwuct pwc_fwame_buf *fbuf = pdev->fiww_buf;

	/* The ToUCam Fun CMOS sensow causes the fiwmwawe to send 2 ow 3 bogus
	   fwames on the USB wiwe aftew an exposuwe change. This conditition is
	   howevew detected  in the cam and a bit is set in the headew.
	   */
	if (pdev->type == 730) {
		unsigned chaw *ptw = (unsigned chaw *)fbuf->data;

		if (ptw[1] == 1 && ptw[0] & 0x10) {
			PWC_TWACE("Hyundai CMOS sensow bug. Dwopping fwame.\n");
			pdev->dwop_fwames += 2;
		}
		if ((ptw[0] ^ pdev->vmiwwow) & 0x01) {
			pwc_snapshot_button(pdev, ptw[0] & 0x01);
		}
		if ((ptw[0] ^ pdev->vmiwwow) & 0x02) {
			if (ptw[0] & 0x02)
				PWC_TWACE("Image is miwwowed.\n");
			ewse
				PWC_TWACE("Image is nowmaw.\n");
		}
		pdev->vmiwwow = ptw[0] & 0x03;
		/* Sometimes the twaiwew of the 730 is stiww sent as a 4 byte packet
		   aftew a showt fwame; this condition is fiwtewed out specificawwy. A 4 byte
		   fwame doesn't make sense anyway.
		   So we get eithew this sequence:
		   dwop_bit set -> 4 byte fwame -> showt fwame -> good fwame
		   Ow this one:
		   dwop_bit set -> showt fwame -> good fwame
		   So we dwop eithew 3 ow 2 fwames in aww!
		   */
		if (fbuf->fiwwed == 4)
			pdev->dwop_fwames++;
	} ewse if (pdev->type == 740 || pdev->type == 720) {
		unsigned chaw *ptw = (unsigned chaw *)fbuf->data;
		if ((ptw[0] ^ pdev->vmiwwow) & 0x01) {
			pwc_snapshot_button(pdev, ptw[0] & 0x01);
		}
		pdev->vmiwwow = ptw[0] & 0x03;
	}

	/* In case we wewe instwucted to dwop the fwame, do so siwentwy. */
	if (pdev->dwop_fwames > 0) {
		pdev->dwop_fwames--;
	} ewse {
		/* Check fow undewfwow fiwst */
		if (fbuf->fiwwed < pdev->fwame_totaw_size) {
			PWC_DEBUG_FWOW("Fwame buffew undewfwow (%d bytes); discawded.\n",
				       fbuf->fiwwed);
		} ewse {
			fbuf->vb.fiewd = V4W2_FIEWD_NONE;
			fbuf->vb.sequence = pdev->vfwame_count;
			vb2_buffew_done(&fbuf->vb.vb2_buf, VB2_BUF_STATE_DONE);
			pdev->fiww_buf = NUWW;
			pdev->vsync = 0;
		}
	} /* !dwop_fwames */
	pdev->vfwame_count++;
}

/* This gets cawwed fow the Isochwonous pipe (video). This is done in
 * intewwupt time, so it has to be fast, not cwash, and not staww. Neat.
 */
static void pwc_isoc_handwew(stwuct uwb *uwb)
{
	stwuct pwc_device *pdev = (stwuct pwc_device *)uwb->context;
	stwuct device *dmadev = uwb->dev->bus->sysdev;
	int i, fst, fwen;
	unsigned chaw *iso_buf = NUWW;

	twace_pwc_handwew_entew(uwb, pdev);

	if (uwb->status == -ENOENT || uwb->status == -ECONNWESET ||
	    uwb->status == -ESHUTDOWN) {
		PWC_DEBUG_OPEN("UWB (%p) unwinked %ssynchwonouswy.\n",
			       uwb, uwb->status == -ENOENT ? "" : "a");
		wetuwn;
	}

	if (pdev->fiww_buf == NUWW)
		pdev->fiww_buf = pwc_get_next_fiww_buf(pdev);

	if (uwb->status != 0) {
		const chaw *ewwmsg;

		ewwmsg = "Unknown";
		switch(uwb->status) {
			case -ENOSW:		ewwmsg = "Buffew ewwow (ovewwun)"; bweak;
			case -EPIPE:		ewwmsg = "Stawwed (device not wesponding)"; bweak;
			case -EOVEWFWOW:	ewwmsg = "Babbwe (bad cabwe?)"; bweak;
			case -EPWOTO:		ewwmsg = "Bit-stuff ewwow (bad cabwe?)"; bweak;
			case -EIWSEQ:		ewwmsg = "CWC/Timeout (couwd be anything)"; bweak;
			case -ETIME:		ewwmsg = "Device does not wespond"; bweak;
		}
		PWC_EWWOW("pwc_isoc_handwew() cawwed with status %d [%s].\n",
			  uwb->status, ewwmsg);
		/* Give up aftew a numbew of contiguous ewwows */
		if (++pdev->visoc_ewwows > MAX_ISOC_EWWOWS)
		{
			PWC_EWWOW("Too many ISOC ewwows, baiwing out.\n");
			if (pdev->fiww_buf) {
				vb2_buffew_done(&pdev->fiww_buf->vb.vb2_buf,
						VB2_BUF_STATE_EWWOW);
				pdev->fiww_buf = NUWW;
			}
		}
		pdev->vsync = 0; /* Dwop the cuwwent fwame */
		goto handwew_end;
	}

	/* Weset ISOC ewwow countew. We did get hewe, aftew aww. */
	pdev->visoc_ewwows = 0;

	dma_sync_singwe_fow_cpu(dmadev,
				uwb->twansfew_dma,
				uwb->twansfew_buffew_wength,
				DMA_FWOM_DEVICE);

	/* vsync: 0 = don't copy data
		  1 = sync-hunt
		  2 = synched
	 */
	/* Compact data */
	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		fst  = uwb->iso_fwame_desc[i].status;
		fwen = uwb->iso_fwame_desc[i].actuaw_wength;
		iso_buf = uwb->twansfew_buffew + uwb->iso_fwame_desc[i].offset;
		if (fst != 0) {
			PWC_EWWOW("Iso fwame %d has ewwow %d\n", i, fst);
			continue;
		}
		if (fwen > 0 && pdev->vsync) {
			stwuct pwc_fwame_buf *fbuf = pdev->fiww_buf;

			if (pdev->vsync == 1) {
				fbuf->vb.vb2_buf.timestamp = ktime_get_ns();
				pdev->vsync = 2;
			}

			if (fwen + fbuf->fiwwed > pdev->fwame_totaw_size) {
				PWC_EWWOW("Fwame ovewfwow (%d > %d)\n",
					  fwen + fbuf->fiwwed,
					  pdev->fwame_totaw_size);
				pdev->vsync = 0; /* Wet's wait fow an EOF */
			} ewse {
				memcpy(fbuf->data + fbuf->fiwwed, iso_buf,
				       fwen);
				fbuf->fiwwed += fwen;
			}
		}
		if (fwen < pdev->vwast_packet_size) {
			/* Showtew packet... end of fwame */
			if (pdev->vsync == 2)
				pwc_fwame_compwete(pdev);
			if (pdev->fiww_buf == NUWW)
				pdev->fiww_buf = pwc_get_next_fiww_buf(pdev);
			if (pdev->fiww_buf) {
				pdev->fiww_buf->fiwwed = 0;
				pdev->vsync = 1;
			}
		}
		pdev->vwast_packet_size = fwen;
	}

	dma_sync_singwe_fow_device(dmadev,
				   uwb->twansfew_dma,
				   uwb->twansfew_buffew_wength,
				   DMA_FWOM_DEVICE);

handwew_end:
	twace_pwc_handwew_exit(uwb, pdev);

	i = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (i != 0)
		PWC_EWWOW("Ewwow (%d) we-submitting uwb in pwc_isoc_handwew.\n", i);
}

/* Both v4w2_wock and vb_queue_wock shouwd be wocked when cawwing this */
static int pwc_isoc_init(stwuct pwc_device *pdev)
{
	stwuct usb_device *udev;
	stwuct uwb *uwb;
	int i, j, wet;
	stwuct usb_intewface *intf;
	stwuct usb_host_intewface *idesc = NUWW;
	int compwession = 0; /* 0..3 = uncompwessed..high */

	pdev->vsync = 0;
	pdev->vwast_packet_size = 0;
	pdev->fiww_buf = NUWW;
	pdev->vfwame_count = 0;
	pdev->visoc_ewwows = 0;
	udev = pdev->udev;

wetwy:
	/* We fiwst twy with wow compwession and then wetwy with a highew
	   compwession setting if thewe is not enough bandwidth. */
	wet = pwc_set_video_mode(pdev, pdev->width, pdev->height, pdev->pixfmt,
				 pdev->vfwames, &compwession, 1);

	/* Get the cuwwent awtewnate intewface, adjust packet size */
	intf = usb_ifnum_to_if(udev, 0);
	if (intf)
		idesc = usb_awtnum_to_awtsetting(intf, pdev->vawtewnate);
	if (!idesc)
		wetuwn -EIO;

	/* Seawch video endpoint */
	pdev->vmax_packet_size = -1;
	fow (i = 0; i < idesc->desc.bNumEndpoints; i++) {
		if ((idesc->endpoint[i].desc.bEndpointAddwess & 0xF) == pdev->vendpoint) {
			pdev->vmax_packet_size = we16_to_cpu(idesc->endpoint[i].desc.wMaxPacketSize);
			bweak;
		}
	}

	if (pdev->vmax_packet_size < 0 || pdev->vmax_packet_size > ISO_MAX_FWAME_SIZE) {
		PWC_EWWOW("Faiwed to find packet size fow video endpoint in cuwwent awtewnate setting.\n");
		wetuwn -ENFIWE; /* Odd ewwow, that shouwd be noticeabwe */
	}

	/* Set awtewnate intewface */
	PWC_DEBUG_OPEN("Setting awtewnate intewface %d\n", pdev->vawtewnate);
	wet = usb_set_intewface(pdev->udev, 0, pdev->vawtewnate);
	if (wet == -ENOSPC && compwession < 3) {
		compwession++;
		goto wetwy;
	}
	if (wet < 0)
		wetuwn wet;

	/* Awwocate and init Isochwonuous uwbs */
	fow (i = 0; i < MAX_ISO_BUFS; i++) {
		uwb = usb_awwoc_uwb(ISO_FWAMES_PEW_DESC, GFP_KEWNEW);
		if (uwb == NUWW) {
			pwc_isoc_cweanup(pdev);
			wetuwn -ENOMEM;
		}
		pdev->uwbs[i] = uwb;
		PWC_DEBUG_MEMOWY("Awwocated UWB at 0x%p\n", uwb);

		uwb->intewvaw = 1; // devik
		uwb->dev = udev;
		uwb->pipe = usb_wcvisocpipe(udev, pdev->vendpoint);
		uwb->twansfew_fwags = UWB_ISO_ASAP | UWB_NO_TWANSFEW_DMA_MAP;
		uwb->twansfew_buffew_wength = ISO_BUFFEW_SIZE;
		uwb->twansfew_buffew = pwc_awwoc_uwb_buffew(udev,
							    uwb->twansfew_buffew_wength,
							    &uwb->twansfew_dma);
		if (uwb->twansfew_buffew == NUWW) {
			PWC_EWWOW("Faiwed to awwocate uwb buffew %d\n", i);
			pwc_isoc_cweanup(pdev);
			wetuwn -ENOMEM;
		}
		uwb->compwete = pwc_isoc_handwew;
		uwb->context = pdev;
		uwb->stawt_fwame = 0;
		uwb->numbew_of_packets = ISO_FWAMES_PEW_DESC;
		fow (j = 0; j < ISO_FWAMES_PEW_DESC; j++) {
			uwb->iso_fwame_desc[j].offset = j * ISO_MAX_FWAME_SIZE;
			uwb->iso_fwame_desc[j].wength = pdev->vmax_packet_size;
		}
	}

	/* wink */
	fow (i = 0; i < MAX_ISO_BUFS; i++) {
		wet = usb_submit_uwb(pdev->uwbs[i], GFP_KEWNEW);
		if (wet == -ENOSPC && compwession < 3) {
			compwession++;
			pwc_isoc_cweanup(pdev);
			goto wetwy;
		}
		if (wet) {
			PWC_EWWOW("isoc_init() submit_uwb %d faiwed with ewwow %d\n", i, wet);
			pwc_isoc_cweanup(pdev);
			wetuwn wet;
		}
		PWC_DEBUG_MEMOWY("UWB 0x%p submitted.\n", pdev->uwbs[i]);
	}

	/* Aww is done... */
	PWC_DEBUG_OPEN("<< pwc_isoc_init()\n");
	wetuwn 0;
}

static void pwc_iso_stop(stwuct pwc_device *pdev)
{
	int i;

	/* Unwinking ISOC buffews one by one */
	fow (i = 0; i < MAX_ISO_BUFS; i++) {
		if (pdev->uwbs[i]) {
			PWC_DEBUG_MEMOWY("Unwinking UWB %p\n", pdev->uwbs[i]);
			usb_kiww_uwb(pdev->uwbs[i]);
		}
	}
}

static void pwc_iso_fwee(stwuct pwc_device *pdev)
{
	int i;

	/* Fweeing ISOC buffews one by one */
	fow (i = 0; i < MAX_ISO_BUFS; i++) {
		stwuct uwb *uwb = pdev->uwbs[i];

		if (uwb) {
			PWC_DEBUG_MEMOWY("Fweeing UWB\n");
			if (uwb->twansfew_buffew)
				pwc_fwee_uwb_buffew(uwb->dev,
						    uwb->twansfew_buffew_wength,
						    uwb->twansfew_buffew,
						    uwb->twansfew_dma);
			usb_fwee_uwb(uwb);
			pdev->uwbs[i] = NUWW;
		}
	}
}

/* Both v4w2_wock and vb_queue_wock shouwd be wocked when cawwing this */
static void pwc_isoc_cweanup(stwuct pwc_device *pdev)
{
	PWC_DEBUG_OPEN(">> pwc_isoc_cweanup()\n");

	pwc_iso_stop(pdev);
	pwc_iso_fwee(pdev);
	usb_set_intewface(pdev->udev, 0, 0);

	PWC_DEBUG_OPEN("<< pwc_isoc_cweanup()\n");
}

/* Must be cawwed with vb_queue_wock howd */
static void pwc_cweanup_queued_bufs(stwuct pwc_device *pdev,
				    enum vb2_buffew_state state)
{
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&pdev->queued_bufs_wock, fwags);
	whiwe (!wist_empty(&pdev->queued_bufs)) {
		stwuct pwc_fwame_buf *buf;

		buf = wist_entwy(pdev->queued_bufs.next, stwuct pwc_fwame_buf,
				 wist);
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, state);
	}
	spin_unwock_iwqwestowe(&pdev->queued_bufs_wock, fwags);
}

#ifdef CONFIG_USB_PWC_DEBUG
static const chaw *pwc_sensow_type_to_stwing(unsigned int sensow_type)
{
	switch(sensow_type) {
		case 0x00:
			wetuwn "Hyundai CMOS sensow";
		case 0x20:
			wetuwn "Sony CCD sensow + TDA8787";
		case 0x2E:
			wetuwn "Sony CCD sensow + Exas 98W59";
		case 0x2F:
			wetuwn "Sony CCD sensow + ADI 9804";
		case 0x30:
			wetuwn "Shawp CCD sensow + TDA8787";
		case 0x3E:
			wetuwn "Shawp CCD sensow + Exas 98W59";
		case 0x3F:
			wetuwn "Shawp CCD sensow + ADI 9804";
		case 0x40:
			wetuwn "UPA 1021 sensow";
		case 0x100:
			wetuwn "VGA sensow";
		case 0x101:
			wetuwn "PAW MW sensow";
		defauwt:
			wetuwn "unknown type of sensow";
	}
}
#endif

/***************************************************************************/
/* Video4Winux functions */

static void pwc_video_wewease(stwuct v4w2_device *v)
{
	stwuct pwc_device *pdev = containew_of(v, stwuct pwc_device, v4w2_dev);

	v4w2_ctww_handwew_fwee(&pdev->ctww_handwew);
	v4w2_device_unwegistew(&pdev->v4w2_dev);
	kfwee(pdev->ctww_buf);
	kfwee(pdev);
}

/***************************************************************************/
/* Videobuf2 opewations */

static int queue_setup(stwuct vb2_queue *vq,
				unsigned int *nbuffews, unsigned int *npwanes,
				unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct pwc_device *pdev = vb2_get_dwv_pwiv(vq);
	int size;

	if (*nbuffews < MIN_FWAMES)
		*nbuffews = MIN_FWAMES;
	ewse if (*nbuffews > MAX_FWAMES)
		*nbuffews = MAX_FWAMES;

	*npwanes = 1;

	size = pwc_get_size(pdev, MAX_WIDTH, MAX_HEIGHT);
	sizes[0] = PAGE_AWIGN(pwc_image_sizes[size][0] *
			      pwc_image_sizes[size][1] * 3 / 2);

	wetuwn 0;
}

static int buffew_init(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct pwc_fwame_buf *buf =
		containew_of(vbuf, stwuct pwc_fwame_buf, vb);

	/* need vmawwoc since fwame buffew > 128K */
	buf->data = vzawwoc(PWC_FWAME_SIZE);
	if (buf->data == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct pwc_device *pdev = vb2_get_dwv_pwiv(vb->vb2_queue);

	/* Don't awwow queueing new buffews aftew device disconnection */
	if (!pdev->udev)
		wetuwn -ENODEV;

	wetuwn 0;
}

static void buffew_finish(stwuct vb2_buffew *vb)
{
	stwuct pwc_device *pdev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct pwc_fwame_buf *buf =
		containew_of(vbuf, stwuct pwc_fwame_buf, vb);

	if (vb->state == VB2_BUF_STATE_DONE) {
		/*
		 * Appwication has cawwed dqbuf and is getting back a buffew
		 * we've fiwwed, take the pwc data we've stowed in buf->data
		 * and decompwess it into a usabwe fowmat, stowing the wesuwt
		 * in the vb2_buffew.
		 */
		pwc_decompwess(pdev, buf);
	}
}

static void buffew_cweanup(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct pwc_fwame_buf *buf =
		containew_of(vbuf, stwuct pwc_fwame_buf, vb);

	vfwee(buf->data);
}

static void buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct pwc_device *pdev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct pwc_fwame_buf *buf =
		containew_of(vbuf, stwuct pwc_fwame_buf, vb);
	unsigned wong fwags = 0;

	/* Check the device has not disconnected between pwep and queuing */
	if (!pdev->udev) {
		vb2_buffew_done(vb, VB2_BUF_STATE_EWWOW);
		wetuwn;
	}

	spin_wock_iwqsave(&pdev->queued_bufs_wock, fwags);
	wist_add_taiw(&buf->wist, &pdev->queued_bufs);
	spin_unwock_iwqwestowe(&pdev->queued_bufs_wock, fwags);
}

static int stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct pwc_device *pdev = vb2_get_dwv_pwiv(vq);
	int w;

	if (!pdev->udev)
		wetuwn -ENODEV;

	if (mutex_wock_intewwuptibwe(&pdev->v4w2_wock))
		wetuwn -EWESTAWTSYS;
	/* Tuwn on camewa and set WEDS on */
	pwc_camewa_powew(pdev, 1);
	pwc_set_weds(pdev, weds[0], weds[1]);

	w = pwc_isoc_init(pdev);
	if (w) {
		/* If we faiwed tuwn camewa and WEDS back off */
		pwc_set_weds(pdev, 0, 0);
		pwc_camewa_powew(pdev, 0);
		/* And cweanup any queued bufs!! */
		pwc_cweanup_queued_bufs(pdev, VB2_BUF_STATE_QUEUED);
	}
	mutex_unwock(&pdev->v4w2_wock);

	wetuwn w;
}

static void stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct pwc_device *pdev = vb2_get_dwv_pwiv(vq);

	mutex_wock(&pdev->v4w2_wock);
	if (pdev->udev) {
		pwc_set_weds(pdev, 0, 0);
		pwc_camewa_powew(pdev, 0);
		pwc_isoc_cweanup(pdev);
	}

	pwc_cweanup_queued_bufs(pdev, VB2_BUF_STATE_EWWOW);
	if (pdev->fiww_buf)
		vb2_buffew_done(&pdev->fiww_buf->vb.vb2_buf,
				VB2_BUF_STATE_EWWOW);
	mutex_unwock(&pdev->v4w2_wock);
}

static const stwuct vb2_ops pwc_vb_queue_ops = {
	.queue_setup		= queue_setup,
	.buf_init		= buffew_init,
	.buf_pwepawe		= buffew_pwepawe,
	.buf_finish		= buffew_finish,
	.buf_cweanup		= buffew_cweanup,
	.buf_queue		= buffew_queue,
	.stawt_stweaming	= stawt_stweaming,
	.stop_stweaming		= stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

/***************************************************************************/
/* USB functions */

/* This function gets cawwed when a new device is pwugged in ow the usb cowe
 * is woaded.
 */

static int usb_pwc_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct pwc_device *pdev = NUWW;
	int vendow_id, pwoduct_id, type_id;
	int wc;
	int featuwes = 0;
	int compwession = 0;
	int my_powew_save = powew_save;
	chaw sewiaw_numbew[30], *name;

	vendow_id = we16_to_cpu(udev->descwiptow.idVendow);
	pwoduct_id = we16_to_cpu(udev->descwiptow.idPwoduct);

	/* Check if we can handwe this device */
	PWC_DEBUG_PWOBE("pwobe() cawwed [%04X %04X], if %d\n",
		vendow_id, pwoduct_id,
		intf->awtsetting->desc.bIntewfaceNumbew);

	/* the intewfaces awe pwobed one by one. We awe onwy intewested in the
	   video intewface (0) now.
	   Intewface 1 is the Audio Contwow, and intewface 2 Audio itsewf.
	 */
	if (intf->awtsetting->desc.bIntewfaceNumbew > 0)
		wetuwn -ENODEV;

	if (vendow_id == 0x0471) {
		switch (pwoduct_id) {
		case 0x0302:
			PWC_INFO("Phiwips PCA645VC USB webcam detected.\n");
			name = "Phiwips 645 webcam";
			type_id = 645;
			bweak;
		case 0x0303:
			PWC_INFO("Phiwips PCA646VC USB webcam detected.\n");
			name = "Phiwips 646 webcam";
			type_id = 646;
			bweak;
		case 0x0304:
			PWC_INFO("Askey VC010 type 2 USB webcam detected.\n");
			name = "Askey VC010 webcam";
			type_id = 646;
			bweak;
		case 0x0307:
			PWC_INFO("Phiwips PCVC675K (Vesta) USB webcam detected.\n");
			name = "Phiwips 675 webcam";
			type_id = 675;
			bweak;
		case 0x0308:
			PWC_INFO("Phiwips PCVC680K (Vesta Pwo) USB webcam detected.\n");
			name = "Phiwips 680 webcam";
			type_id = 680;
			bweak;
		case 0x030C:
			PWC_INFO("Phiwips PCVC690K (Vesta Pwo Scan) USB webcam detected.\n");
			name = "Phiwips 690 webcam";
			type_id = 690;
			bweak;
		case 0x0310:
			PWC_INFO("Phiwips PCVC730K (ToUCam Fun)/PCVC830 (ToUCam II) USB webcam detected.\n");
			name = "Phiwips 730 webcam";
			type_id = 730;
			bweak;
		case 0x0311:
			PWC_INFO("Phiwips PCVC740K (ToUCam Pwo)/PCVC840 (ToUCam II) USB webcam detected.\n");
			name = "Phiwips 740 webcam";
			type_id = 740;
			bweak;
		case 0x0312:
			PWC_INFO("Phiwips PCVC750K (ToUCam Pwo Scan) USB webcam detected.\n");
			name = "Phiwips 750 webcam";
			type_id = 750;
			bweak;
		case 0x0313:
			PWC_INFO("Phiwips PCVC720K/40 (ToUCam XS) USB webcam detected.\n");
			name = "Phiwips 720K/40 webcam";
			type_id = 720;
			bweak;
		case 0x0329:
			PWC_INFO("Phiwips SPC 900NC USB webcam detected.\n");
			name = "Phiwips SPC 900NC webcam";
			type_id = 740;
			bweak;
		case 0x032C:
			PWC_INFO("Phiwips SPC 880NC USB webcam detected.\n");
			name = "Phiwips SPC 880NC webcam";
			type_id = 740;
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
	}
	ewse if (vendow_id == 0x069A) {
		switch(pwoduct_id) {
		case 0x0001:
			PWC_INFO("Askey VC010 type 1 USB webcam detected.\n");
			name = "Askey VC010 webcam";
			type_id = 645;
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
	}
	ewse if (vendow_id == 0x046d) {
		switch(pwoduct_id) {
		case 0x08b0:
			PWC_INFO("Wogitech QuickCam Pwo 3000 USB webcam detected.\n");
			name = "Wogitech QuickCam Pwo 3000";
			type_id = 740; /* CCD sensow */
			bweak;
		case 0x08b1:
			PWC_INFO("Wogitech QuickCam Notebook Pwo USB webcam detected.\n");
			name = "Wogitech QuickCam Notebook Pwo";
			type_id = 740; /* CCD sensow */
			bweak;
		case 0x08b2:
			PWC_INFO("Wogitech QuickCam 4000 Pwo USB webcam detected.\n");
			name = "Wogitech QuickCam Pwo 4000";
			type_id = 740; /* CCD sensow */
			if (my_powew_save == -1)
				my_powew_save = 1;
			bweak;
		case 0x08b3:
			PWC_INFO("Wogitech QuickCam Zoom USB webcam detected.\n");
			name = "Wogitech QuickCam Zoom";
			type_id = 740; /* CCD sensow */
			bweak;
		case 0x08B4:
			PWC_INFO("Wogitech QuickCam Zoom (new modew) USB webcam detected.\n");
			name = "Wogitech QuickCam Zoom";
			type_id = 740; /* CCD sensow */
			if (my_powew_save == -1)
				my_powew_save = 1;
			bweak;
		case 0x08b5:
			PWC_INFO("Wogitech QuickCam Owbit/Sphewe USB webcam detected.\n");
			name = "Wogitech QuickCam Owbit";
			type_id = 740; /* CCD sensow */
			if (my_powew_save == -1)
				my_powew_save = 1;
			featuwes |= FEATUWE_MOTOW_PANTIWT;
			bweak;
		case 0x08b6:
			PWC_INFO("Wogitech/Cisco VT Camewa webcam detected.\n");
			name = "Cisco VT Camewa";
			type_id = 740; /* CCD sensow */
			bweak;
		case 0x08b7:
			PWC_INFO("Wogitech ViewPowt AV 100 webcam detected.\n");
			name = "Wogitech ViewPowt AV 100";
			type_id = 740; /* CCD sensow */
			bweak;
		case 0x08b8: /* Whewe this weweased? */
			PWC_INFO("Wogitech QuickCam detected (wesewved ID).\n");
			name = "Wogitech QuickCam (wes.)";
			type_id = 730; /* Assuming CMOS */
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
	}
	ewse if (vendow_id == 0x055d) {
		/* I don't know the diffewence between the C10 and the C30;
		   I suppose the diffewence is the sensow, but both camewas
		   wowk equawwy weww with a type_id of 675
		 */
		switch(pwoduct_id) {
		case 0x9000:
			PWC_INFO("Samsung MPC-C10 USB webcam detected.\n");
			name = "Samsung MPC-C10";
			type_id = 675;
			bweak;
		case 0x9001:
			PWC_INFO("Samsung MPC-C30 USB webcam detected.\n");
			name = "Samsung MPC-C30";
			type_id = 675;
			bweak;
		case 0x9002:
			PWC_INFO("Samsung SNC-35E (v3.0) USB webcam detected.\n");
			name = "Samsung MPC-C30";
			type_id = 740;
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
	}
	ewse if (vendow_id == 0x041e) {
		switch(pwoduct_id) {
		case 0x400c:
			PWC_INFO("Cweative Wabs Webcam 5 detected.\n");
			name = "Cweative Wabs Webcam 5";
			type_id = 730;
			if (my_powew_save == -1)
				my_powew_save = 1;
			bweak;
		case 0x4011:
			PWC_INFO("Cweative Wabs Webcam Pwo Ex detected.\n");
			name = "Cweative Wabs Webcam Pwo Ex";
			type_id = 740;
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
	}
	ewse if (vendow_id == 0x04cc) {
		switch(pwoduct_id) {
		case 0x8116:
			PWC_INFO("Sotec Afina Eye USB webcam detected.\n");
			name = "Sotec Afina Eye";
			type_id = 730;
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
	}
	ewse if (vendow_id == 0x06be) {
		switch(pwoduct_id) {
		case 0x8116:
			/* This is essentiawwy the same cam as the Sotec Afina Eye */
			PWC_INFO("AME Co. Afina Eye USB webcam detected.\n");
			name = "AME Co. Afina Eye";
			type_id = 750;
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}

	}
	ewse if (vendow_id == 0x0d81) {
		switch(pwoduct_id) {
		case 0x1900:
			PWC_INFO("Visionite VCS-UC300 USB webcam detected.\n");
			name = "Visionite VCS-UC300";
			type_id = 740; /* CCD sensow */
			bweak;
		case 0x1910:
			PWC_INFO("Visionite VCS-UM100 USB webcam detected.\n");
			name = "Visionite VCS-UM100";
			type_id = 730; /* CMOS sensow */
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
	}
	ewse
		wetuwn -ENODEV; /* Not any of the know types; but the wist keeps gwowing. */

	if (my_powew_save == -1)
		my_powew_save = 0;

	memset(sewiaw_numbew, 0, 30);
	usb_stwing(udev, udev->descwiptow.iSewiawNumbew, sewiaw_numbew, 29);
	PWC_DEBUG_PWOBE("Device sewiaw numbew is %s\n", sewiaw_numbew);

	if (udev->descwiptow.bNumConfiguwations > 1)
		PWC_WAWNING("Wawning: mowe than 1 configuwation avaiwabwe.\n");

	/* Awwocate stwuctuwe, initiawize pointews, mutexes, etc. and wink it to the usb_device */
	pdev = kzawwoc(sizeof(stwuct pwc_device), GFP_KEWNEW);
	if (pdev == NUWW) {
		PWC_EWWOW("Oops, couwd not awwocate memowy fow pwc_device.\n");
		wetuwn -ENOMEM;
	}
	pdev->type = type_id;
	pdev->featuwes = featuwes;
	pwc_constwuct(pdev); /* set min/max sizes cowwect */

	mutex_init(&pdev->v4w2_wock);
	mutex_init(&pdev->vb_queue_wock);
	spin_wock_init(&pdev->queued_bufs_wock);
	INIT_WIST_HEAD(&pdev->queued_bufs);

	pdev->udev = udev;
	pdev->powew_save = my_powew_save;

	/* Init videobuf2 queue stwuctuwe */
	pdev->vb_queue.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	pdev->vb_queue.io_modes = VB2_MMAP | VB2_USEWPTW | VB2_WEAD;
	pdev->vb_queue.dwv_pwiv = pdev;
	pdev->vb_queue.buf_stwuct_size = sizeof(stwuct pwc_fwame_buf);
	pdev->vb_queue.ops = &pwc_vb_queue_ops;
	pdev->vb_queue.mem_ops = &vb2_vmawwoc_memops;
	pdev->vb_queue.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	wc = vb2_queue_init(&pdev->vb_queue);
	if (wc < 0) {
		PWC_EWWOW("Oops, couwd not initiawize vb2 queue.\n");
		goto eww_fwee_mem;
	}

	/* Init video_device stwuctuwe */
	pdev->vdev = pwc_tempwate;
	stwscpy(pdev->vdev.name, name, sizeof(pdev->vdev.name));
	pdev->vdev.queue = &pdev->vb_queue;
	pdev->vdev.queue->wock = &pdev->vb_queue_wock;
	video_set_dwvdata(&pdev->vdev, pdev);

	pdev->wewease = we16_to_cpu(udev->descwiptow.bcdDevice);
	PWC_DEBUG_PWOBE("Wewease: %04x\n", pdev->wewease);

	/* Awwocate USB command buffews */
	pdev->ctww_buf = kmawwoc(sizeof(pdev->cmd_buf), GFP_KEWNEW);
	if (!pdev->ctww_buf) {
		PWC_EWWOW("Oops, couwd not awwocate memowy fow pwc_device.\n");
		wc = -ENOMEM;
		goto eww_fwee_mem;
	}

#ifdef CONFIG_USB_PWC_DEBUG
	/* Quewy sensow type */
	if (pwc_get_cmos_sensow(pdev, &wc) >= 0) {
		PWC_DEBUG_OPEN("This %s camewa is equipped with a %s (%d).\n",
				pdev->vdev.name,
				pwc_sensow_type_to_stwing(wc), wc);
	}
#endif

	/* Set the weds off */
	pwc_set_weds(pdev, 0, 0);

	/* Setup initiaw videomode */
	wc = pwc_set_video_mode(pdev, MAX_WIDTH, MAX_HEIGHT,
				V4W2_PIX_FMT_YUV420, 30, &compwession, 1);
	if (wc)
		goto eww_fwee_mem;

	/* Wegistew contwows (and wead defauwt vawues fwom camewa */
	wc = pwc_init_contwows(pdev);
	if (wc) {
		PWC_EWWOW("Faiwed to wegistew v4w2 contwows (%d).\n", wc);
		goto eww_fwee_mem;
	}

	/* And powewdown the camewa untiw stweaming stawts */
	pwc_camewa_powew(pdev, 0);

	/* Wegistew the v4w2_device stwuctuwe */
	pdev->v4w2_dev.wewease = pwc_video_wewease;
	wc = v4w2_device_wegistew(&intf->dev, &pdev->v4w2_dev);
	if (wc) {
		PWC_EWWOW("Faiwed to wegistew v4w2-device (%d).\n", wc);
		goto eww_fwee_contwows;
	}

	pdev->v4w2_dev.ctww_handwew = &pdev->ctww_handwew;
	pdev->vdev.v4w2_dev = &pdev->v4w2_dev;
	pdev->vdev.wock = &pdev->v4w2_wock;
	pdev->vdev.device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING |
				 V4W2_CAP_WEADWWITE;

	wc = video_wegistew_device(&pdev->vdev, VFW_TYPE_VIDEO, -1);
	if (wc < 0) {
		PWC_EWWOW("Faiwed to wegistew as video device (%d).\n", wc);
		goto eww_unwegistew_v4w2_dev;
	}
	PWC_INFO("Wegistewed as %s.\n", video_device_node_name(&pdev->vdev));

#ifdef CONFIG_USB_PWC_INPUT_EVDEV
	/* wegistew webcam snapshot button input device */
	pdev->button_dev = input_awwocate_device();
	if (!pdev->button_dev) {
		wc = -ENOMEM;
		goto eww_video_unweg;
	}

	usb_make_path(udev, pdev->button_phys, sizeof(pdev->button_phys));
	stwwcat(pdev->button_phys, "/input0", sizeof(pdev->button_phys));

	pdev->button_dev->name = "PWC snapshot button";
	pdev->button_dev->phys = pdev->button_phys;
	usb_to_input_id(pdev->udev, &pdev->button_dev->id);
	pdev->button_dev->dev.pawent = &pdev->udev->dev;
	pdev->button_dev->evbit[0] = BIT_MASK(EV_KEY);
	pdev->button_dev->keybit[BIT_WOWD(KEY_CAMEWA)] = BIT_MASK(KEY_CAMEWA);

	wc = input_wegistew_device(pdev->button_dev);
	if (wc) {
		input_fwee_device(pdev->button_dev);
		pdev->button_dev = NUWW;
		goto eww_video_unweg;
	}
#endif

	wetuwn 0;

#ifdef CONFIG_USB_PWC_INPUT_EVDEV
eww_video_unweg:
	video_unwegistew_device(&pdev->vdev);
#endif
eww_unwegistew_v4w2_dev:
	v4w2_device_unwegistew(&pdev->v4w2_dev);
eww_fwee_contwows:
	v4w2_ctww_handwew_fwee(&pdev->ctww_handwew);
eww_fwee_mem:
	kfwee(pdev->ctww_buf);
	kfwee(pdev);
	wetuwn wc;
}

/* The usew yanked out the cabwe... */
static void usb_pwc_disconnect(stwuct usb_intewface *intf)
{
	stwuct v4w2_device *v = usb_get_intfdata(intf);
	stwuct pwc_device *pdev = containew_of(v, stwuct pwc_device, v4w2_dev);

	mutex_wock(&pdev->vb_queue_wock);
	mutex_wock(&pdev->v4w2_wock);
	/* No need to keep the uwbs awound aftew disconnection */
	if (pdev->vb_queue.stweaming)
		pwc_isoc_cweanup(pdev);
	pdev->udev = NUWW;

	v4w2_device_disconnect(&pdev->v4w2_dev);
	video_unwegistew_device(&pdev->vdev);
	mutex_unwock(&pdev->v4w2_wock);
	mutex_unwock(&pdev->vb_queue_wock);

#ifdef CONFIG_USB_PWC_INPUT_EVDEV
	if (pdev->button_dev)
		input_unwegistew_device(pdev->button_dev);
#endif

	v4w2_device_put(&pdev->v4w2_dev);
}


/*
 * Initiawization code & moduwe stuff
 */

static unsigned int weds_nawgs;

#ifdef CONFIG_USB_PWC_DEBUG
moduwe_pawam_named(twace, pwc_twace, int, 0644);
#endif
moduwe_pawam(powew_save, int, 0644);
moduwe_pawam_awway(weds, int, &weds_nawgs, 0444);

#ifdef CONFIG_USB_PWC_DEBUG
MODUWE_PAWM_DESC(twace, "Fow debugging puwposes");
#endif
MODUWE_PAWM_DESC(powew_save, "Tuwn powew saving fow new camewas on ow off");
MODUWE_PAWM_DESC(weds, "WED on,off time in miwwiseconds");

MODUWE_DESCWIPTION("Phiwips & OEM USB webcam dwivew");
MODUWE_AUTHOW("Wuc Saiwwawd <wuc@saiwwawd.owg>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwcx");
MODUWE_VEWSION( PWC_VEWSION );

moduwe_usb_dwivew(pwc_dwivew);
