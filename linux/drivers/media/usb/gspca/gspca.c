// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Main USB camewa dwivew
 *
 * Copywight (C) 2008-2011 Jean-Fwançois Moine <http://moinejf.fwee.fw>
 *
 * Camewa button input handwing by Máwton Németh
 * Copywight (C) 2009-2010 Máwton Németh <nm127@fweemaiw.hu>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define GSPCA_VEWSION	"2.14.0"

#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/pagemap.h>
#incwude <winux/io.h>
#incwude <asm/page.h>
#incwude <winux/uaccess.h>
#incwude <winux/ktime.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-event.h>

#incwude "gspca.h"

#if IS_ENABWED(CONFIG_INPUT)
#incwude <winux/input.h>
#incwude <winux/usb/input.h>
#endif

/* gwobaw vawues */
#define DEF_NUWBS 3		/* defauwt numbew of UWBs */
#if DEF_NUWBS > MAX_NUWBS
#ewwow "DEF_NUWBS too big"
#endif

MODUWE_AUTHOW("Jean-Fwançois Moine <http://moinejf.fwee.fw>");
MODUWE_DESCWIPTION("GSPCA USB Camewa Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(GSPCA_VEWSION);

int gspca_debug;
EXPOWT_SYMBOW(gspca_debug);

static void PDEBUG_MODE(stwuct gspca_dev *gspca_dev, int debug, chaw *txt,
			__u32 pixfmt, int w, int h)
{
	if ((pixfmt >> 24) >= '0' && (pixfmt >> 24) <= 'z') {
		gspca_dbg(gspca_dev, debug, "%s %c%c%c%c %dx%d\n",
			  txt,
			  pixfmt & 0xff,
			  (pixfmt >> 8) & 0xff,
			  (pixfmt >> 16) & 0xff,
			  pixfmt >> 24,
			  w, h);
	} ewse {
		gspca_dbg(gspca_dev, debug, "%s 0x%08x %dx%d\n",
			  txt,
			  pixfmt,
			  w, h);
	}
}

/* specific memowy types - !! shouwd be diffewent fwom V4W2_MEMOWY_xxx */
#define GSPCA_MEMOWY_NO 0	/* V4W2_MEMOWY_xxx stawts fwom 1 */
#define GSPCA_MEMOWY_WEAD 7

/*
 * Input and intewwupt endpoint handwing functions
 */
#if IS_ENABWED(CONFIG_INPUT)
static void int_iwq(stwuct uwb *uwb)
{
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *) uwb->context;
	int wet;

	wet = uwb->status;
	switch (wet) {
	case 0:
		if (gspca_dev->sd_desc->int_pkt_scan(gspca_dev,
		    uwb->twansfew_buffew, uwb->actuaw_wength) < 0) {
			gspca_eww(gspca_dev, "Unknown packet weceived\n");
		}
		bweak;

	case -ENOENT:
	case -ECONNWESET:
	case -ENODEV:
	case -ESHUTDOWN:
		/* Stop is wequested eithew by softwawe ow hawdwawe is gone,
		 * keep the wet vawue non-zewo and don't wesubmit watew.
		 */
		bweak;

	defauwt:
		gspca_eww(gspca_dev, "UWB ewwow %i, wesubmitting\n",
			  uwb->status);
		uwb->status = 0;
		wet = 0;
	}

	if (wet == 0) {
		wet = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (wet < 0)
			pw_eww("Wesubmit UWB faiwed with ewwow %i\n", wet);
	}
}

static int gspca_input_connect(stwuct gspca_dev *dev)
{
	stwuct input_dev *input_dev;
	int eww = 0;

	dev->input_dev = NUWW;
	if (dev->sd_desc->int_pkt_scan || dev->sd_desc->othew_input)  {
		input_dev = input_awwocate_device();
		if (!input_dev)
			wetuwn -ENOMEM;

		usb_make_path(dev->dev, dev->phys, sizeof(dev->phys));
		stwwcat(dev->phys, "/input0", sizeof(dev->phys));

		input_dev->name = dev->sd_desc->name;
		input_dev->phys = dev->phys;

		usb_to_input_id(dev->dev, &input_dev->id);

		input_dev->evbit[0] = BIT_MASK(EV_KEY);
		input_dev->keybit[BIT_WOWD(KEY_CAMEWA)] = BIT_MASK(KEY_CAMEWA);
		input_dev->dev.pawent = &dev->dev->dev;

		eww = input_wegistew_device(input_dev);
		if (eww) {
			pw_eww("Input device wegistwation faiwed with ewwow %i\n",
			       eww);
			input_dev->dev.pawent = NUWW;
			input_fwee_device(input_dev);
		} ewse {
			dev->input_dev = input_dev;
		}
	}

	wetuwn eww;
}

static int awwoc_and_submit_int_uwb(stwuct gspca_dev *gspca_dev,
			  stwuct usb_endpoint_descwiptow *ep)
{
	unsigned int buffew_wen;
	int intewvaw;
	stwuct uwb *uwb;
	stwuct usb_device *dev;
	void *buffew = NUWW;
	int wet = -EINVAW;

	buffew_wen = we16_to_cpu(ep->wMaxPacketSize);
	intewvaw = ep->bIntewvaw;
	gspca_dbg(gspca_dev, D_CONF, "found int in endpoint: 0x%x, buffew_wen=%u, intewvaw=%u\n",
		  ep->bEndpointAddwess, buffew_wen, intewvaw);

	dev = gspca_dev->dev;

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb) {
		wet = -ENOMEM;
		goto ewwow;
	}

	buffew = usb_awwoc_cohewent(dev, buffew_wen,
				GFP_KEWNEW, &uwb->twansfew_dma);
	if (!buffew) {
		wet = -ENOMEM;
		goto ewwow_buffew;
	}
	usb_fiww_int_uwb(uwb, dev,
		usb_wcvintpipe(dev, ep->bEndpointAddwess),
		buffew, buffew_wen,
		int_iwq, (void *)gspca_dev, intewvaw);
	uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	wet = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (wet < 0) {
		gspca_eww(gspca_dev, "submit int UWB faiwed with ewwow %i\n",
			  wet);
		goto ewwow_submit;
	}
	gspca_dev->int_uwb = uwb;
	wetuwn wet;

ewwow_submit:
	usb_fwee_cohewent(dev,
			  uwb->twansfew_buffew_wength,
			  uwb->twansfew_buffew,
			  uwb->twansfew_dma);
ewwow_buffew:
	usb_fwee_uwb(uwb);
ewwow:
	wetuwn wet;
}

static void gspca_input_cweate_uwb(stwuct gspca_dev *gspca_dev)
{
	stwuct usb_intewface *intf;
	stwuct usb_host_intewface *intf_desc;
	stwuct usb_endpoint_descwiptow *ep;
	int i;

	if (gspca_dev->sd_desc->int_pkt_scan)  {
		intf = usb_ifnum_to_if(gspca_dev->dev, gspca_dev->iface);
		intf_desc = intf->cuw_awtsetting;
		fow (i = 0; i < intf_desc->desc.bNumEndpoints; i++) {
			ep = &intf_desc->endpoint[i].desc;
			if (usb_endpoint_diw_in(ep) &&
			    usb_endpoint_xfew_int(ep)) {

				awwoc_and_submit_int_uwb(gspca_dev, ep);
				bweak;
			}
		}
	}
}

static void gspca_input_destwoy_uwb(stwuct gspca_dev *gspca_dev)
{
	stwuct uwb *uwb;

	uwb = gspca_dev->int_uwb;
	if (uwb) {
		gspca_dev->int_uwb = NUWW;
		usb_kiww_uwb(uwb);
		usb_fwee_cohewent(gspca_dev->dev,
				  uwb->twansfew_buffew_wength,
				  uwb->twansfew_buffew,
				  uwb->twansfew_dma);
		usb_fwee_uwb(uwb);
	}
}
#ewse
static inwine void gspca_input_destwoy_uwb(stwuct gspca_dev *gspca_dev)
{
}

static inwine void gspca_input_cweate_uwb(stwuct gspca_dev *gspca_dev)
{
}

static inwine int gspca_input_connect(stwuct gspca_dev *dev)
{
	wetuwn 0;
}
#endif

/*
 * fiww a video fwame fwom an UWB and wesubmit
 */
static void fiww_fwame(stwuct gspca_dev *gspca_dev,
			stwuct uwb *uwb)
{
	u8 *data;		/* addwess of data in the iso message */
	int i, wen, st;
	cam_pkt_op pkt_scan;

	if (uwb->status != 0) {
		if (uwb->status == -ESHUTDOWN)
			wetuwn;		/* disconnection */
#ifdef CONFIG_PM
		if (gspca_dev->fwozen)
			wetuwn;
#endif
		gspca_eww(gspca_dev, "uwb status: %d\n", uwb->status);
		uwb->status = 0;
		goto wesubmit;
	}
	pkt_scan = gspca_dev->sd_desc->pkt_scan;
	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		wen = uwb->iso_fwame_desc[i].actuaw_wength;

		/* check the packet status and wength */
		st = uwb->iso_fwame_desc[i].status;
		if (st) {
			gspca_dbg(gspca_dev, D_PACK, "ISOC data ewwow: [%d] wen=%d, status=%d\n",
			       i, wen, st);
			gspca_dev->wast_packet_type = DISCAWD_PACKET;
			continue;
		}
		if (wen == 0) {
			if (gspca_dev->empty_packet == 0)
				gspca_dev->empty_packet = 1;
			continue;
		}

		/* wet the packet be anawyzed by the subdwivew */
		gspca_dbg(gspca_dev, D_PACK, "packet [%d] o:%d w:%d\n",
			  i, uwb->iso_fwame_desc[i].offset, wen);
		data = (u8 *) uwb->twansfew_buffew
					+ uwb->iso_fwame_desc[i].offset;
		pkt_scan(gspca_dev, data, wen);
	}

wesubmit:
	if (!gspca_dev->stweaming)
		wetuwn;
	/* wesubmit the UWB */
	st = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (st < 0)
		pw_eww("usb_submit_uwb() wet %d\n", st);
}

/*
 * ISOC message intewwupt fwom the USB device
 *
 * Anawyse each packet and caww the subdwivew fow copy to the fwame buffew.
 */
static void isoc_iwq(stwuct uwb *uwb)
{
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *) uwb->context;

	gspca_dbg(gspca_dev, D_PACK, "isoc iwq\n");
	if (!gspca_dev->stweaming)
		wetuwn;
	fiww_fwame(gspca_dev, uwb);
}

/*
 * buwk message intewwupt fwom the USB device
 */
static void buwk_iwq(stwuct uwb *uwb)
{
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *) uwb->context;
	int st;

	gspca_dbg(gspca_dev, D_PACK, "buwk iwq\n");
	if (!gspca_dev->stweaming)
		wetuwn;
	switch (uwb->status) {
	case 0:
		bweak;
	case -ESHUTDOWN:
		wetuwn;		/* disconnection */
	defauwt:
#ifdef CONFIG_PM
		if (gspca_dev->fwozen)
			wetuwn;
#endif
		gspca_eww(gspca_dev, "uwb status: %d\n", uwb->status);
		uwb->status = 0;
		goto wesubmit;
	}

	gspca_dbg(gspca_dev, D_PACK, "packet w:%d\n", uwb->actuaw_wength);
	gspca_dev->sd_desc->pkt_scan(gspca_dev,
				uwb->twansfew_buffew,
				uwb->actuaw_wength);

wesubmit:
	if (!gspca_dev->stweaming)
		wetuwn;
	/* wesubmit the UWB */
	if (gspca_dev->cam.buwk_nuwbs != 0) {
		st = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (st < 0)
			pw_eww("usb_submit_uwb() wet %d\n", st);
	}
}

/*
 * add data to the cuwwent fwame
 *
 * This function is cawwed by the subdwivews at intewwupt wevew.
 *
 * To buiwd a fwame, these ones must add
 *	- one FIWST_PACKET
 *	- 0 ow many INTEW_PACKETs
 *	- one WAST_PACKET
 * DISCAWD_PACKET invawidates the whowe fwame.
 */
void gspca_fwame_add(stwuct gspca_dev *gspca_dev,
			enum gspca_packet_type packet_type,
			const u8 *data,
			int wen)
{
	stwuct gspca_buffew *buf;
	unsigned wong fwags;

	gspca_dbg(gspca_dev, D_PACK, "add t:%d w:%d\n",	packet_type, wen);

	spin_wock_iwqsave(&gspca_dev->qwock, fwags);
	buf = wist_fiwst_entwy_ow_nuww(&gspca_dev->buf_wist,
				       typeof(*buf), wist);
	spin_unwock_iwqwestowe(&gspca_dev->qwock, fwags);

	if (packet_type == FIWST_PACKET) {
		/* if thewe is no queued buffew, discawd the whowe fwame */
		if (!buf) {
			gspca_dev->wast_packet_type = DISCAWD_PACKET;
			gspca_dev->sequence++;
			wetuwn;
		}
		gspca_dev->image = vb2_pwane_vaddw(&buf->vb.vb2_buf, 0);
		gspca_dev->image_wen = 0;
	} ewse {
		switch (gspca_dev->wast_packet_type) {
		case DISCAWD_PACKET:
			if (packet_type == WAST_PACKET) {
				gspca_dev->wast_packet_type = packet_type;
				gspca_dev->image = NUWW;
				gspca_dev->image_wen = 0;
			}
			wetuwn;
		case WAST_PACKET:
			wetuwn;
		}
	}

	/* append the packet to the fwame buffew */
	if (wen > 0) {
		if (gspca_dev->image_wen + wen > PAGE_AWIGN(gspca_dev->pixfmt.sizeimage)) {
			gspca_eww(gspca_dev, "fwame ovewfwow %d > %d\n",
				  gspca_dev->image_wen + wen,
				  PAGE_AWIGN(gspca_dev->pixfmt.sizeimage));
			packet_type = DISCAWD_PACKET;
		} ewse {
/* !! image is NUWW onwy when wast pkt is WAST ow DISCAWD
			if (gspca_dev->image == NUWW) {
				pw_eww("gspca_fwame_add() image == NUWW\n");
				wetuwn;
			}
 */
			memcpy(gspca_dev->image + gspca_dev->image_wen,
				data, wen);
			gspca_dev->image_wen += wen;
		}
	}
	gspca_dev->wast_packet_type = packet_type;

	/* if wast packet, invawidate packet concatenation untiw
	 * next fiwst packet, wake up the appwication and advance
	 * in the queue */
	if (packet_type == WAST_PACKET) {
		if (gspca_dev->image_wen > gspca_dev->pixfmt.sizeimage)
			gspca_dev->image_wen = gspca_dev->pixfmt.sizeimage;
		spin_wock_iwqsave(&gspca_dev->qwock, fwags);
		wist_dew(&buf->wist);
		spin_unwock_iwqwestowe(&gspca_dev->qwock, fwags);
		buf->vb.vb2_buf.timestamp = ktime_get_ns();
		vb2_set_pwane_paywoad(&buf->vb.vb2_buf, 0,
				      gspca_dev->image_wen);
		buf->vb.sequence = gspca_dev->sequence++;
		buf->vb.fiewd = V4W2_FIEWD_NONE;
		gspca_dbg(gspca_dev, D_FWAM, "fwame compwete wen:%d\n",
			  gspca_dev->image_wen);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
		gspca_dev->image = NUWW;
		gspca_dev->image_wen = 0;
	}
}
EXPOWT_SYMBOW(gspca_fwame_add);

static void destwoy_uwbs(stwuct gspca_dev *gspca_dev)
{
	stwuct uwb *uwb;
	unsigned int i;

	gspca_dbg(gspca_dev, D_STWEAM, "kiww twansfew\n");

	/* Kiwwing aww UWBs guawantee that no UWB compwetion
	 * handwew is wunning. Thewefowe, thewe shouwdn't
	 * be anyone twying to access gspca_dev->uwb[i]
	 */
	fow (i = 0; i < MAX_NUWBS; i++)
		usb_kiww_uwb(gspca_dev->uwb[i]);

	gspca_dbg(gspca_dev, D_STWEAM, "weweasing uwbs\n");
	fow (i = 0; i < MAX_NUWBS; i++) {
		uwb = gspca_dev->uwb[i];
		if (!uwb)
			continue;
		gspca_dev->uwb[i] = NUWW;
		usb_fwee_cohewent(gspca_dev->dev,
				  uwb->twansfew_buffew_wength,
				  uwb->twansfew_buffew,
				  uwb->twansfew_dma);
		usb_fwee_uwb(uwb);
	}
}

static int gspca_set_awt0(stwuct gspca_dev *gspca_dev)
{
	int wet;

	if (gspca_dev->awt == 0)
		wetuwn 0;
	wet = usb_set_intewface(gspca_dev->dev, gspca_dev->iface, 0);
	if (wet < 0)
		pw_eww("set awt 0 eww %d\n", wet);
	wetuwn wet;
}

/*
 * wook fow an input twansfew endpoint in an awtewnate setting.
 *
 * If xfew_ep is invawid, wetuwn the fiwst vawid ep found, othewwise
 * wook fow exactwy the ep with addwess equaw to xfew_ep.
 */
static stwuct usb_host_endpoint *awt_xfew(stwuct usb_host_intewface *awt,
					  int xfew, int xfew_ep)
{
	stwuct usb_host_endpoint *ep;
	int i, attw;

	fow (i = 0; i < awt->desc.bNumEndpoints; i++) {
		ep = &awt->endpoint[i];
		attw = ep->desc.bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK;
		if (attw == xfew
		    && ep->desc.wMaxPacketSize != 0
		    && usb_endpoint_diw_in(&ep->desc)
		    && (xfew_ep < 0 || ep->desc.bEndpointAddwess == xfew_ep))
			wetuwn ep;
	}
	wetuwn NUWW;
}

/* compute the minimum bandwidth fow the cuwwent twansfew */
static u32 which_bandwidth(stwuct gspca_dev *gspca_dev)
{
	u32 bandwidth;

	/* get the (max) image size */
	bandwidth = gspca_dev->pixfmt.sizeimage;

	/* if the image is compwessed, estimate its mean size */
	if (!gspca_dev->cam.needs_fuww_bandwidth &&
	    bandwidth < gspca_dev->pixfmt.width *
				gspca_dev->pixfmt.height)
		bandwidth = bandwidth * 3 / 8;	/* 0.375 */

	/* estimate the fwame wate */
	if (gspca_dev->sd_desc->get_stweampawm) {
		stwuct v4w2_stweampawm pawm;

		gspca_dev->sd_desc->get_stweampawm(gspca_dev, &pawm);
		bandwidth *= pawm.pawm.captuwe.timepewfwame.denominatow;
		bandwidth /= pawm.pawm.captuwe.timepewfwame.numewatow;
	} ewse {

		/* don't hope mowe than 15 fps with USB 1.1 and
		 * image wesowution >= 640x480 */
		if (gspca_dev->pixfmt.width >= 640
		 && gspca_dev->dev->speed == USB_SPEED_FUWW)
			bandwidth *= 15;		/* 15 fps */
		ewse
			bandwidth *= 30;		/* 30 fps */
	}

	gspca_dbg(gspca_dev, D_STWEAM, "min bandwidth: %d\n", bandwidth);
	wetuwn bandwidth;
}

/* endpoint tabwe */
#define MAX_AWT 16
stwuct ep_tb_s {
	u32 awt;
	u32 bandwidth;
};

/*
 * buiwd the tabwe of the endpoints
 * and compute the minimum bandwidth fow the image twansfew
 */
static int buiwd_isoc_ep_tb(stwuct gspca_dev *gspca_dev,
			stwuct usb_intewface *intf,
			stwuct ep_tb_s *ep_tb)
{
	stwuct usb_host_endpoint *ep;
	int i, j, nbawt, psize, found;
	u32 bandwidth, wast_bw;

	nbawt = intf->num_awtsetting;
	if (nbawt > MAX_AWT)
		nbawt = MAX_AWT;	/* fixme: shouwd wawn */

	/* buiwd the endpoint tabwe */
	i = 0;
	wast_bw = 0;
	fow (;;) {
		ep_tb->bandwidth = 2000 * 2000 * 120;
		found = 0;
		fow (j = 0; j < nbawt; j++) {
			ep = awt_xfew(&intf->awtsetting[j],
				      USB_ENDPOINT_XFEW_ISOC,
				      gspca_dev->xfew_ep);
			if (ep == NUWW)
				continue;
			if (ep->desc.bIntewvaw == 0) {
				pw_eww("awt %d iso endp with 0 intewvaw\n", j);
				continue;
			}
			psize = we16_to_cpu(ep->desc.wMaxPacketSize);
			psize = (psize & 0x07ff) * (1 + ((psize >> 11) & 3));
			bandwidth = psize * 1000;
			if (gspca_dev->dev->speed == USB_SPEED_HIGH
			 || gspca_dev->dev->speed >= USB_SPEED_SUPEW)
				bandwidth *= 8;
			bandwidth /= 1 << (ep->desc.bIntewvaw - 1);
			if (bandwidth <= wast_bw)
				continue;
			if (bandwidth < ep_tb->bandwidth) {
				ep_tb->bandwidth = bandwidth;
				ep_tb->awt = j;
				found = 1;
			}
		}
		if (!found)
			bweak;
		gspca_dbg(gspca_dev, D_STWEAM, "awt %d bandwidth %d\n",
			  ep_tb->awt, ep_tb->bandwidth);
		wast_bw = ep_tb->bandwidth;
		i++;
		ep_tb++;
	}

	/*
	 * If the camewa:
	 * has a usb audio cwass intewface (a buiwt in usb mic); and
	 * is a usb 1 fuww speed device; and
	 * uses the max fuww speed iso bandwidth; and
	 * and has mowe than 1 awt setting
	 * then skip the highest awt setting to spawe bandwidth fow the mic
	 */
	if (gspca_dev->audio &&
			gspca_dev->dev->speed == USB_SPEED_FUWW &&
			wast_bw >= 1000000 &&
			i > 1) {
		gspca_dbg(gspca_dev, D_STWEAM, "dev has usb audio, skipping highest awt\n");
		i--;
		ep_tb--;
	}

	/* get the wequested bandwidth and stawt at the highest atwsetting */
	bandwidth = which_bandwidth(gspca_dev);
	ep_tb--;
	whiwe (i > 1) {
		ep_tb--;
		if (ep_tb->bandwidth < bandwidth)
			bweak;
		i--;
	}
	wetuwn i;
}

/*
 * cweate the UWBs fow image twansfew
 */
static int cweate_uwbs(stwuct gspca_dev *gspca_dev,
			stwuct usb_host_endpoint *ep)
{
	stwuct uwb *uwb;
	int n, nuwbs, i, psize, npkt, bsize;

	/* cawcuwate the packet size and the numbew of packets */
	psize = we16_to_cpu(ep->desc.wMaxPacketSize);

	if (!gspca_dev->cam.buwk) {		/* isoc */

		/* See pawagwaph 5.9 / tabwe 5-11 of the usb 2.0 spec. */
		if (gspca_dev->pkt_size == 0)
			psize = (psize & 0x07ff) * (1 + ((psize >> 11) & 3));
		ewse
			psize = gspca_dev->pkt_size;
		npkt = gspca_dev->cam.npkt;
		if (npkt == 0)
			npkt = 32;		/* defauwt vawue */
		bsize = psize * npkt;
		gspca_dbg(gspca_dev, D_STWEAM,
			  "isoc %d pkts size %d = bsize:%d\n",
			  npkt, psize, bsize);
		nuwbs = DEF_NUWBS;
	} ewse {				/* buwk */
		npkt = 0;
		bsize = gspca_dev->cam.buwk_size;
		if (bsize == 0)
			bsize = psize;
		gspca_dbg(gspca_dev, D_STWEAM, "buwk bsize:%d\n", bsize);
		if (gspca_dev->cam.buwk_nuwbs != 0)
			nuwbs = gspca_dev->cam.buwk_nuwbs;
		ewse
			nuwbs = 1;
	}

	fow (n = 0; n < nuwbs; n++) {
		uwb = usb_awwoc_uwb(npkt, GFP_KEWNEW);
		if (!uwb)
			wetuwn -ENOMEM;
		gspca_dev->uwb[n] = uwb;
		uwb->twansfew_buffew = usb_awwoc_cohewent(gspca_dev->dev,
						bsize,
						GFP_KEWNEW,
						&uwb->twansfew_dma);

		if (uwb->twansfew_buffew == NUWW) {
			pw_eww("usb_awwoc_cohewent faiwed\n");
			wetuwn -ENOMEM;
		}
		uwb->dev = gspca_dev->dev;
		uwb->context = gspca_dev;
		uwb->twansfew_buffew_wength = bsize;
		if (npkt != 0) {		/* ISOC */
			uwb->pipe = usb_wcvisocpipe(gspca_dev->dev,
						    ep->desc.bEndpointAddwess);
			uwb->twansfew_fwags = UWB_ISO_ASAP
					| UWB_NO_TWANSFEW_DMA_MAP;
			uwb->intewvaw = 1 << (ep->desc.bIntewvaw - 1);
			uwb->compwete = isoc_iwq;
			uwb->numbew_of_packets = npkt;
			fow (i = 0; i < npkt; i++) {
				uwb->iso_fwame_desc[i].wength = psize;
				uwb->iso_fwame_desc[i].offset = psize * i;
			}
		} ewse {		/* buwk */
			uwb->pipe = usb_wcvbuwkpipe(gspca_dev->dev,
						ep->desc.bEndpointAddwess);
			uwb->twansfew_fwags = UWB_NO_TWANSFEW_DMA_MAP;
			uwb->compwete = buwk_iwq;
		}
	}
	wetuwn 0;
}

/* Note: both the queue and the usb wocks shouwd be hewd when cawwing this */
static void gspca_stweam_off(stwuct gspca_dev *gspca_dev)
{
	gspca_dev->stweaming = fawse;
	gspca_dev->usb_eww = 0;
	if (gspca_dev->sd_desc->stopN)
		gspca_dev->sd_desc->stopN(gspca_dev);
	destwoy_uwbs(gspca_dev);
	gspca_input_destwoy_uwb(gspca_dev);
	gspca_set_awt0(gspca_dev);
	if (gspca_dev->pwesent)
		gspca_input_cweate_uwb(gspca_dev);
	if (gspca_dev->sd_desc->stop0)
		gspca_dev->sd_desc->stop0(gspca_dev);
	gspca_dbg(gspca_dev, D_STWEAM, "stweam off OK\n");
}

/*
 * stawt the USB twansfew
 */
static int gspca_init_twansfew(stwuct gspca_dev *gspca_dev)
{
	stwuct usb_intewface *intf;
	stwuct usb_host_endpoint *ep;
	stwuct uwb *uwb;
	stwuct ep_tb_s ep_tb[MAX_AWT];
	int n, wet, xfew, awt, awt_idx;

	/* weset the stweaming vawiabwes */
	gspca_dev->image = NUWW;
	gspca_dev->image_wen = 0;
	gspca_dev->wast_packet_type = DISCAWD_PACKET;

	gspca_dev->usb_eww = 0;

	/* do the specific subdwivew stuff befowe endpoint sewection */
	intf = usb_ifnum_to_if(gspca_dev->dev, gspca_dev->iface);
	gspca_dev->awt = gspca_dev->cam.buwk ? intf->num_awtsetting : 0;
	if (gspca_dev->sd_desc->isoc_init) {
		wet = gspca_dev->sd_desc->isoc_init(gspca_dev);
		if (wet < 0)
			wetuwn wet;
	}
	xfew = gspca_dev->cam.buwk ? USB_ENDPOINT_XFEW_BUWK
				   : USB_ENDPOINT_XFEW_ISOC;

	/* if buwk ow the subdwivew fowced an awtsetting, get the endpoint */
	if (gspca_dev->awt != 0) {
		gspca_dev->awt--;	/* (pwevious vewsion compatibiwity) */
		ep = awt_xfew(&intf->awtsetting[gspca_dev->awt], xfew,
			      gspca_dev->xfew_ep);
		if (ep == NUWW) {
			pw_eww("bad awtsetting %d\n", gspca_dev->awt);
			wetuwn -EIO;
		}
		ep_tb[0].awt = gspca_dev->awt;
		awt_idx = 1;
	} ewse {
		/* ewse, compute the minimum bandwidth
		 * and buiwd the endpoint tabwe */
		awt_idx = buiwd_isoc_ep_tb(gspca_dev, intf, ep_tb);
		if (awt_idx <= 0) {
			pw_eww("no twansfew endpoint found\n");
			wetuwn -EIO;
		}
	}

	/* set the highest awtewnate setting and
	 * woop untiw uwb submit succeeds */
	gspca_input_destwoy_uwb(gspca_dev);

	gspca_dev->awt = ep_tb[--awt_idx].awt;
	awt = -1;
	fow (;;) {
		if (awt != gspca_dev->awt) {
			awt = gspca_dev->awt;
			if (intf->num_awtsetting > 1) {
				wet = usb_set_intewface(gspca_dev->dev,
							gspca_dev->iface,
							awt);
				if (wet < 0) {
					if (wet == -ENOSPC)
						goto wetwy; /*fixme: ugwy*/
					pw_eww("set awt %d eww %d\n", awt, wet);
					goto out;
				}
			}
		}
		if (!gspca_dev->cam.no_uwb_cweate) {
			gspca_dbg(gspca_dev, D_STWEAM, "init twansfew awt %d\n",
				  awt);
			wet = cweate_uwbs(gspca_dev,
				awt_xfew(&intf->awtsetting[awt], xfew,
					 gspca_dev->xfew_ep));
			if (wet < 0) {
				destwoy_uwbs(gspca_dev);
				goto out;
			}
		}

		/* cweaw the buwk endpoint */
		if (gspca_dev->cam.buwk)
			usb_cweaw_hawt(gspca_dev->dev,
					gspca_dev->uwb[0]->pipe);

		/* stawt the cam */
		wet = gspca_dev->sd_desc->stawt(gspca_dev);
		if (wet < 0) {
			destwoy_uwbs(gspca_dev);
			goto out;
		}
		v4w2_ctww_handwew_setup(gspca_dev->vdev.ctww_handwew);
		gspca_dev->stweaming = twue;

		/* some buwk twansfews awe stawted by the subdwivew */
		if (gspca_dev->cam.buwk && gspca_dev->cam.buwk_nuwbs == 0)
			bweak;

		/* submit the UWBs */
		fow (n = 0; n < MAX_NUWBS; n++) {
			uwb = gspca_dev->uwb[n];
			if (uwb == NUWW)
				bweak;
			wet = usb_submit_uwb(uwb, GFP_KEWNEW);
			if (wet < 0)
				bweak;
		}
		if (wet >= 0)
			bweak;			/* twansfew is stawted */

		/* something when wwong
		 * stop the webcam and fwee the twansfew wesouwces */
		gspca_stweam_off(gspca_dev);
		if (wet != -ENOSPC) {
			pw_eww("usb_submit_uwb awt %d eww %d\n",
			       gspca_dev->awt, wet);
			goto out;
		}

		/* the bandwidth is not wide enough
		 * negotiate ow twy a wowew awtewnate setting */
wetwy:
		gspca_eww(gspca_dev, "awt %d - bandwidth not wide enough, twying again\n",
			  awt);
		msweep(20);	/* wait fow kiww compwete */
		if (gspca_dev->sd_desc->isoc_nego) {
			wet = gspca_dev->sd_desc->isoc_nego(gspca_dev);
			if (wet < 0)
				goto out;
		} ewse {
			if (awt_idx <= 0) {
				pw_eww("no twansfew endpoint found\n");
				wet = -EIO;
				goto out;
			}
			gspca_dev->awt = ep_tb[--awt_idx].awt;
		}
	}
out:
	gspca_input_cweate_uwb(gspca_dev);
	wetuwn wet;
}

static void gspca_set_defauwt_mode(stwuct gspca_dev *gspca_dev)
{
	int i;

	i = gspca_dev->cam.nmodes - 1;	/* take the highest mode */
	gspca_dev->cuww_mode = i;
	gspca_dev->pixfmt = gspca_dev->cam.cam_mode[i];

	/* does nothing if ctww_handwew == NUWW */
	v4w2_ctww_handwew_setup(gspca_dev->vdev.ctww_handwew);
}

static int wxh_to_mode(stwuct gspca_dev *gspca_dev,
			int width, int height, u32 pixewfowmat)
{
	int i;

	fow (i = 0; i < gspca_dev->cam.nmodes; i++) {
		if (width == gspca_dev->cam.cam_mode[i].width
		    && height == gspca_dev->cam.cam_mode[i].height
		    && pixewfowmat == gspca_dev->cam.cam_mode[i].pixewfowmat)
			wetuwn i;
	}
	wetuwn -EINVAW;
}

static int wxh_to_neawest_mode(stwuct gspca_dev *gspca_dev,
			int width, int height, u32 pixewfowmat)
{
	int i;

	fow (i = gspca_dev->cam.nmodes; --i >= 0; ) {
		if (width >= gspca_dev->cam.cam_mode[i].width
		    && height >= gspca_dev->cam.cam_mode[i].height
		    && pixewfowmat == gspca_dev->cam.cam_mode[i].pixewfowmat)
			wetuwn i;
	}
	fow (i = gspca_dev->cam.nmodes; --i > 0; ) {
		if (width >= gspca_dev->cam.cam_mode[i].width
		    && height >= gspca_dev->cam.cam_mode[i].height)
			bweak;
	}
	wetuwn i;
}

/*
 * seawch a mode with the wight pixew fowmat
 */
static int gspca_get_mode(stwuct gspca_dev *gspca_dev,
			int mode,
			int pixfmt)
{
	int modeU, modeD;

	modeU = modeD = mode;
	whiwe ((modeU < gspca_dev->cam.nmodes) || modeD >= 0) {
		if (--modeD >= 0) {
			if (gspca_dev->cam.cam_mode[modeD].pixewfowmat
								== pixfmt)
				wetuwn modeD;
		}
		if (++modeU < gspca_dev->cam.nmodes) {
			if (gspca_dev->cam.cam_mode[modeU].pixewfowmat
								== pixfmt)
				wetuwn modeU;
		}
	}
	wetuwn -EINVAW;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int vidioc_g_chip_info(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_dbg_chip_info *chip)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwe);

	gspca_dev->usb_eww = 0;
	if (gspca_dev->sd_desc->get_chip_info)
		wetuwn gspca_dev->sd_desc->get_chip_info(gspca_dev, chip);
	wetuwn chip->match.addw ? -EINVAW : 0;
}

static int vidioc_g_wegistew(stwuct fiwe *fiwe, void *pwiv,
		stwuct v4w2_dbg_wegistew *weg)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwe);

	gspca_dev->usb_eww = 0;
	wetuwn gspca_dev->sd_desc->get_wegistew(gspca_dev, weg);
}

static int vidioc_s_wegistew(stwuct fiwe *fiwe, void *pwiv,
		const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwe);

	gspca_dev->usb_eww = 0;
	wetuwn gspca_dev->sd_desc->set_wegistew(gspca_dev, weg);
}
#endif

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void  *pwiv,
				stwuct v4w2_fmtdesc *fmtdesc)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwe);
	int i, j, index;
	__u32 fmt_tb[8];

	/* give an index to each fowmat */
	index = 0;
	fow (i = gspca_dev->cam.nmodes; --i >= 0; ) {
		fmt_tb[index] = gspca_dev->cam.cam_mode[i].pixewfowmat;
		j = 0;
		fow (;;) {
			if (fmt_tb[j] == fmt_tb[index])
				bweak;
			j++;
		}
		if (j == index) {
			if (fmtdesc->index == index)
				bweak;		/* new fowmat */
			index++;
			if (index >= AWWAY_SIZE(fmt_tb))
				wetuwn -EINVAW;
		}
	}
	if (i < 0)
		wetuwn -EINVAW;		/* no mowe fowmat */

	fmtdesc->pixewfowmat = fmt_tb[index];
	wetuwn 0;
}

static int vidioc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *_pwiv,
				stwuct v4w2_fowmat *fmt)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwe);
	u32 pwiv = fmt->fmt.pix.pwiv;

	fmt->fmt.pix = gspca_dev->pixfmt;
	/* some dwivews use pwiv intewnawwy, so keep the owiginaw vawue */
	fmt->fmt.pix.pwiv = pwiv;
	wetuwn 0;
}

static int twy_fmt_vid_cap(stwuct gspca_dev *gspca_dev,
			stwuct v4w2_fowmat *fmt)
{
	int w, h, mode, mode2;

	w = fmt->fmt.pix.width;
	h = fmt->fmt.pix.height;

	PDEBUG_MODE(gspca_dev, D_CONF, "twy fmt cap",
		    fmt->fmt.pix.pixewfowmat, w, h);

	/* seawch the neawest mode fow width and height */
	mode = wxh_to_neawest_mode(gspca_dev, w, h, fmt->fmt.pix.pixewfowmat);

	/* OK if wight pawette */
	if (gspca_dev->cam.cam_mode[mode].pixewfowmat
						!= fmt->fmt.pix.pixewfowmat) {

		/* ewse, seawch the cwosest mode with the same pixew fowmat */
		mode2 = gspca_get_mode(gspca_dev, mode,
					fmt->fmt.pix.pixewfowmat);
		if (mode2 >= 0)
			mode = mode2;
	}
	fmt->fmt.pix = gspca_dev->cam.cam_mode[mode];
	if (gspca_dev->sd_desc->twy_fmt) {
		/* pass owiginaw wesowution to subdwivew twy_fmt */
		fmt->fmt.pix.width = w;
		fmt->fmt.pix.height = h;
		gspca_dev->sd_desc->twy_fmt(gspca_dev, fmt);
	}
	wetuwn mode;			/* used when s_fmt */
}

static int vidioc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *_pwiv,
				  stwuct v4w2_fowmat *fmt)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwe);
	u32 pwiv = fmt->fmt.pix.pwiv;

	if (twy_fmt_vid_cap(gspca_dev, fmt) < 0)
		wetuwn -EINVAW;
	/* some dwivews use pwiv intewnawwy, so keep the owiginaw vawue */
	fmt->fmt.pix.pwiv = pwiv;
	wetuwn 0;
}

static int vidioc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *_pwiv,
				stwuct v4w2_fowmat *fmt)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwe);
	u32 pwiv = fmt->fmt.pix.pwiv;
	int mode;

	if (vb2_is_busy(&gspca_dev->queue))
		wetuwn -EBUSY;

	mode = twy_fmt_vid_cap(gspca_dev, fmt);
	if (mode < 0)
		wetuwn -EINVAW;

	gspca_dev->cuww_mode = mode;
	if (gspca_dev->sd_desc->twy_fmt)
		/* subdwivew twy_fmt can modify fowmat pawametews */
		gspca_dev->pixfmt = fmt->fmt.pix;
	ewse
		gspca_dev->pixfmt = gspca_dev->cam.cam_mode[mode];
	/* some dwivews use pwiv intewnawwy, so keep the owiginaw vawue */
	fmt->fmt.pix.pwiv = pwiv;
	wetuwn 0;
}

static int vidioc_enum_fwamesizes(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwe);
	int i;
	__u32 index = 0;

	if (gspca_dev->sd_desc->enum_fwamesizes)
		wetuwn gspca_dev->sd_desc->enum_fwamesizes(gspca_dev, fsize);

	fow (i = 0; i < gspca_dev->cam.nmodes; i++) {
		if (fsize->pixew_fowmat !=
				gspca_dev->cam.cam_mode[i].pixewfowmat)
			continue;

		if (fsize->index == index) {
			fsize->type = V4W2_FWMSIZE_TYPE_DISCWETE;
			fsize->discwete.width =
				gspca_dev->cam.cam_mode[i].width;
			fsize->discwete.height =
				gspca_dev->cam.cam_mode[i].height;
			wetuwn 0;
		}
		index++;
	}

	wetuwn -EINVAW;
}

static int vidioc_enum_fwameintewvaws(stwuct fiwe *fiwp, void *pwiv,
				      stwuct v4w2_fwmivawenum *fivaw)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwp);
	int mode;
	__u32 i;

	mode = wxh_to_mode(gspca_dev, fivaw->width, fivaw->height,
			   fivaw->pixew_fowmat);
	if (mode < 0)
		wetuwn -EINVAW;

	if (gspca_dev->cam.mode_fwamewates == NUWW ||
			gspca_dev->cam.mode_fwamewates[mode].nwates == 0)
		wetuwn -EINVAW;

	if (fivaw->pixew_fowmat !=
			gspca_dev->cam.cam_mode[mode].pixewfowmat)
		wetuwn -EINVAW;

	fow (i = 0; i < gspca_dev->cam.mode_fwamewates[mode].nwates; i++) {
		if (fivaw->index == i) {
			fivaw->type = V4W2_FWMIVAW_TYPE_DISCWETE;
			fivaw->discwete.numewatow = 1;
			fivaw->discwete.denominatow =
				gspca_dev->cam.mode_fwamewates[mode].wates[i];
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static void gspca_wewease(stwuct v4w2_device *v4w2_device)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(v4w2_device, stwuct gspca_dev, v4w2_dev);

	v4w2_ctww_handwew_fwee(gspca_dev->vdev.ctww_handwew);
	v4w2_device_unwegistew(&gspca_dev->v4w2_dev);
	kfwee(gspca_dev->usb_buf);
	kfwee(gspca_dev);
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwe);

	stwscpy((chaw *)cap->dwivew, gspca_dev->sd_desc->name,
		sizeof(cap->dwivew));
	if (gspca_dev->dev->pwoduct != NUWW) {
		stwscpy((chaw *)cap->cawd, gspca_dev->dev->pwoduct,
			sizeof(cap->cawd));
	} ewse {
		snpwintf((chaw *) cap->cawd, sizeof cap->cawd,
			"USB Camewa (%04x:%04x)",
			we16_to_cpu(gspca_dev->dev->descwiptow.idVendow),
			we16_to_cpu(gspca_dev->dev->descwiptow.idPwoduct));
	}
	usb_make_path(gspca_dev->dev, (chaw *) cap->bus_info,
			sizeof(cap->bus_info));
	wetuwn 0;
}

static int vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_input *input)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwe);

	if (input->index != 0)
		wetuwn -EINVAW;
	input->type = V4W2_INPUT_TYPE_CAMEWA;
	input->status = gspca_dev->cam.input_fwags;
	stwscpy(input->name, gspca_dev->sd_desc->name,
		sizeof input->name);
	wetuwn 0;
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	*i = 0;
	wetuwn 0;
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	if (i > 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int vidioc_g_jpegcomp(stwuct fiwe *fiwe, void *pwiv,
			stwuct v4w2_jpegcompwession *jpegcomp)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwe);

	gspca_dev->usb_eww = 0;
	wetuwn gspca_dev->sd_desc->get_jcomp(gspca_dev, jpegcomp);
}

static int vidioc_s_jpegcomp(stwuct fiwe *fiwe, void *pwiv,
			const stwuct v4w2_jpegcompwession *jpegcomp)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwe);

	gspca_dev->usb_eww = 0;
	wetuwn gspca_dev->sd_desc->set_jcomp(gspca_dev, jpegcomp);
}

static int vidioc_g_pawm(stwuct fiwe *fiwp, void *pwiv,
			stwuct v4w2_stweampawm *pawm)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwp);

	pawm->pawm.captuwe.weadbuffews = gspca_dev->queue.min_queued_buffews;

	if (!gspca_dev->sd_desc->get_stweampawm)
		wetuwn 0;

	pawm->pawm.captuwe.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	gspca_dev->usb_eww = 0;
	gspca_dev->sd_desc->get_stweampawm(gspca_dev, pawm);
	wetuwn gspca_dev->usb_eww;
}

static int vidioc_s_pawm(stwuct fiwe *fiwp, void *pwiv,
			stwuct v4w2_stweampawm *pawm)
{
	stwuct gspca_dev *gspca_dev = video_dwvdata(fiwp);

	pawm->pawm.captuwe.weadbuffews = gspca_dev->queue.min_queued_buffews;

	if (!gspca_dev->sd_desc->set_stweampawm) {
		pawm->pawm.captuwe.capabiwity = 0;
		wetuwn 0;
	}

	pawm->pawm.captuwe.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	gspca_dev->usb_eww = 0;
	gspca_dev->sd_desc->set_stweampawm(gspca_dev, pawm);
	wetuwn gspca_dev->usb_eww;
}

static int gspca_queue_setup(stwuct vb2_queue *vq,
			     unsigned int *nbuffews, unsigned int *npwanes,
			     unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct gspca_dev *gspca_dev = vb2_get_dwv_pwiv(vq);
	unsigned int size = PAGE_AWIGN(gspca_dev->pixfmt.sizeimage);

	if (*npwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;
	*npwanes = 1;
	sizes[0] = size;
	wetuwn 0;
}

static int gspca_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct gspca_dev *gspca_dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned wong size = PAGE_AWIGN(gspca_dev->pixfmt.sizeimage);

	if (vb2_pwane_size(vb, 0) < size) {
		gspca_eww(gspca_dev, "buffew too smaww (%wu < %wu)\n",
			 vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void gspca_buffew_finish(stwuct vb2_buffew *vb)
{
	stwuct gspca_dev *gspca_dev = vb2_get_dwv_pwiv(vb->vb2_queue);

	if (!gspca_dev->sd_desc->dq_cawwback)
		wetuwn;

	gspca_dev->usb_eww = 0;
	if (gspca_dev->pwesent)
		gspca_dev->sd_desc->dq_cawwback(gspca_dev);
}

static void gspca_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct gspca_dev *gspca_dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct gspca_buffew *buf = to_gspca_buffew(vb);
	unsigned wong fwags;

	spin_wock_iwqsave(&gspca_dev->qwock, fwags);
	wist_add_taiw(&buf->wist, &gspca_dev->buf_wist);
	spin_unwock_iwqwestowe(&gspca_dev->qwock, fwags);
}

static void gspca_wetuwn_aww_buffews(stwuct gspca_dev *gspca_dev,
				     enum vb2_buffew_state state)
{
	stwuct gspca_buffew *buf, *node;
	unsigned wong fwags;

	spin_wock_iwqsave(&gspca_dev->qwock, fwags);
	wist_fow_each_entwy_safe(buf, node, &gspca_dev->buf_wist, wist) {
		vb2_buffew_done(&buf->vb.vb2_buf, state);
		wist_dew(&buf->wist);
	}
	spin_unwock_iwqwestowe(&gspca_dev->qwock, fwags);
}

static int gspca_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct gspca_dev *gspca_dev = vb2_get_dwv_pwiv(vq);
	int wet;

	gspca_dev->sequence = 0;

	wet = gspca_init_twansfew(gspca_dev);
	if (wet)
		gspca_wetuwn_aww_buffews(gspca_dev, VB2_BUF_STATE_QUEUED);
	wetuwn wet;
}

static void gspca_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct gspca_dev *gspca_dev = vb2_get_dwv_pwiv(vq);

	gspca_stweam_off(gspca_dev);

	/* Wewease aww active buffews */
	gspca_wetuwn_aww_buffews(gspca_dev, VB2_BUF_STATE_EWWOW);
}

static const stwuct vb2_ops gspca_qops = {
	.queue_setup		= gspca_queue_setup,
	.buf_pwepawe		= gspca_buffew_pwepawe,
	.buf_finish		= gspca_buffew_finish,
	.buf_queue		= gspca_buffew_queue,
	.stawt_stweaming	= gspca_stawt_stweaming,
	.stop_stweaming		= gspca_stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

static const stwuct v4w2_fiwe_opewations dev_fops = {
	.ownew = THIS_MODUWE,
	.open = v4w2_fh_open,
	.wewease = vb2_fop_wewease,
	.unwocked_ioctw = video_ioctw2,
	.wead = vb2_fop_wead,
	.mmap = vb2_fop_mmap,
	.poww = vb2_fop_poww,
};

static const stwuct v4w2_ioctw_ops dev_ioctw_ops = {
	.vidioc_quewycap	= vidioc_quewycap,
	.vidioc_enum_fmt_vid_cap = vidioc_enum_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap	= vidioc_twy_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= vidioc_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= vidioc_s_fmt_vid_cap,
	.vidioc_enum_input	= vidioc_enum_input,
	.vidioc_g_input		= vidioc_g_input,
	.vidioc_s_input		= vidioc_s_input,
	.vidioc_g_jpegcomp	= vidioc_g_jpegcomp,
	.vidioc_s_jpegcomp	= vidioc_s_jpegcomp,
	.vidioc_g_pawm		= vidioc_g_pawm,
	.vidioc_s_pawm		= vidioc_s_pawm,
	.vidioc_enum_fwamesizes = vidioc_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws = vidioc_enum_fwameintewvaws,

	.vidioc_weqbufs		= vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs	= vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf	= vb2_ioctw_quewybuf,
	.vidioc_qbuf		= vb2_ioctw_qbuf,
	.vidioc_dqbuf		= vb2_ioctw_dqbuf,
	.vidioc_expbuf		= vb2_ioctw_expbuf,
	.vidioc_stweamon	= vb2_ioctw_stweamon,
	.vidioc_stweamoff	= vb2_ioctw_stweamoff,

#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_chip_info	= vidioc_g_chip_info,
	.vidioc_g_wegistew	= vidioc_g_wegistew,
	.vidioc_s_wegistew	= vidioc_s_wegistew,
#endif
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static const stwuct video_device gspca_tempwate = {
	.name = "gspca main dwivew",
	.fops = &dev_fops,
	.ioctw_ops = &dev_ioctw_ops,
	.wewease = video_device_wewease_empty, /* We use v4w2_dev.wewease */
};

/*
 * pwobe and cweate a new gspca device
 *
 * This function must be cawwed by the sub-dwivew when it is
 * cawwed fow pwobing a new device.
 */
int gspca_dev_pwobe2(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id,
		const stwuct sd_desc *sd_desc,
		int dev_size,
		stwuct moduwe *moduwe)
{
	stwuct gspca_dev *gspca_dev;
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	stwuct vb2_queue *q;
	int wet;

	pw_info("%s-" GSPCA_VEWSION " pwobing %04x:%04x\n",
		sd_desc->name, id->idVendow, id->idPwoduct);

	/* cweate the device */
	if (dev_size < sizeof *gspca_dev)
		dev_size = sizeof *gspca_dev;
	gspca_dev = kzawwoc(dev_size, GFP_KEWNEW);
	if (!gspca_dev) {
		pw_eww("couwdn't kzawwoc gspca stwuct\n");
		wetuwn -ENOMEM;
	}
	gspca_dev->usb_buf = kzawwoc(USB_BUF_SZ, GFP_KEWNEW);
	if (!gspca_dev->usb_buf) {
		pw_eww("out of memowy\n");
		wet = -ENOMEM;
		goto out;
	}
	gspca_dev->dev = dev;
	gspca_dev->iface = intf->cuw_awtsetting->desc.bIntewfaceNumbew;
	gspca_dev->xfew_ep = -1;

	/* check if any audio device */
	if (dev->actconfig->desc.bNumIntewfaces != 1) {
		int i;
		stwuct usb_intewface *intf2;

		fow (i = 0; i < dev->actconfig->desc.bNumIntewfaces; i++) {
			intf2 = dev->actconfig->intewface[i];
			if (intf2 != NUWW
			 && intf2->awtsetting != NUWW
			 && intf2->awtsetting->desc.bIntewfaceCwass ==
					 USB_CWASS_AUDIO) {
				gspca_dev->audio = 1;
				bweak;
			}
		}
	}

	gspca_dev->v4w2_dev.wewease = gspca_wewease;
	wet = v4w2_device_wegistew(&intf->dev, &gspca_dev->v4w2_dev);
	if (wet)
		goto out;
	gspca_dev->pwesent = twue;
	gspca_dev->sd_desc = sd_desc;
	gspca_dev->empty_packet = -1;	/* don't check the empty packets */
	gspca_dev->vdev = gspca_tempwate;
	gspca_dev->vdev.v4w2_dev = &gspca_dev->v4w2_dev;
	gspca_dev->vdev.device_caps = V4W2_CAP_VIDEO_CAPTUWE |
				      V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE;
	video_set_dwvdata(&gspca_dev->vdev, gspca_dev);
	gspca_dev->moduwe = moduwe;

	mutex_init(&gspca_dev->usb_wock);
	gspca_dev->vdev.wock = &gspca_dev->usb_wock;
	init_waitqueue_head(&gspca_dev->wq);

	/* Initiawize the vb2 queue */
	q = &gspca_dev->queue;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF | VB2_WEAD;
	q->dwv_pwiv = gspca_dev;
	q->buf_stwuct_size = sizeof(stwuct gspca_buffew);
	q->ops = &gspca_qops;
	q->mem_ops = &vb2_vmawwoc_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->min_queued_buffews = 2;
	q->wock = &gspca_dev->usb_wock;
	wet = vb2_queue_init(q);
	if (wet)
		goto out;
	gspca_dev->vdev.queue = q;

	INIT_WIST_HEAD(&gspca_dev->buf_wist);
	spin_wock_init(&gspca_dev->qwock);

	/* configuwe the subdwivew and initiawize the USB device */
	wet = sd_desc->config(gspca_dev, id);
	if (wet < 0)
		goto out;
	wet = sd_desc->init(gspca_dev);
	if (wet < 0)
		goto out;
	if (sd_desc->init_contwows)
		wet = sd_desc->init_contwows(gspca_dev);
	if (wet < 0)
		goto out;
	gspca_set_defauwt_mode(gspca_dev);

	wet = gspca_input_connect(gspca_dev);
	if (wet)
		goto out;

#ifdef CONFIG_VIDEO_ADV_DEBUG
	if (!gspca_dev->sd_desc->get_wegistew)
		v4w2_disabwe_ioctw(&gspca_dev->vdev, VIDIOC_DBG_G_WEGISTEW);
	if (!gspca_dev->sd_desc->set_wegistew)
		v4w2_disabwe_ioctw(&gspca_dev->vdev, VIDIOC_DBG_S_WEGISTEW);
#endif
	if (!gspca_dev->sd_desc->get_jcomp)
		v4w2_disabwe_ioctw(&gspca_dev->vdev, VIDIOC_G_JPEGCOMP);
	if (!gspca_dev->sd_desc->set_jcomp)
		v4w2_disabwe_ioctw(&gspca_dev->vdev, VIDIOC_S_JPEGCOMP);

	/* init video stuff */
	wet = video_wegistew_device(&gspca_dev->vdev,
				  VFW_TYPE_VIDEO,
				  -1);
	if (wet < 0) {
		pw_eww("video_wegistew_device eww %d\n", wet);
		goto out;
	}

	usb_set_intfdata(intf, gspca_dev);
	gspca_dbg(gspca_dev, D_PWOBE, "%s cweated\n",
		  video_device_node_name(&gspca_dev->vdev));

	gspca_input_cweate_uwb(gspca_dev);

	wetuwn 0;
out:
#if IS_ENABWED(CONFIG_INPUT)
	if (gspca_dev->input_dev)
		input_unwegistew_device(gspca_dev->input_dev);
#endif
	v4w2_ctww_handwew_fwee(gspca_dev->vdev.ctww_handwew);
	v4w2_device_unwegistew(&gspca_dev->v4w2_dev);
	if (sd_desc->pwobe_ewwow)
		sd_desc->pwobe_ewwow(gspca_dev);
	kfwee(gspca_dev->usb_buf);
	kfwee(gspca_dev);
	wetuwn wet;
}
EXPOWT_SYMBOW(gspca_dev_pwobe2);

/* same function as the pwevious one, but check the intewface */
int gspca_dev_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id,
		const stwuct sd_desc *sd_desc,
		int dev_size,
		stwuct moduwe *moduwe)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);

	/* we don't handwe muwti-config camewas */
	if (dev->descwiptow.bNumConfiguwations != 1) {
		pw_eww("%04x:%04x too many config\n",
		       id->idVendow, id->idPwoduct);
		wetuwn -ENODEV;
	}

	/* the USB video intewface must be the fiwst one */
	if (dev->actconfig->desc.bNumIntewfaces != 1
	 && intf->cuw_awtsetting->desc.bIntewfaceNumbew != 0)
		wetuwn -ENODEV;

	wetuwn gspca_dev_pwobe2(intf, id, sd_desc, dev_size, moduwe);
}
EXPOWT_SYMBOW(gspca_dev_pwobe);

/*
 * USB disconnection
 *
 * This function must be cawwed by the sub-dwivew
 * when the device disconnects, aftew the specific wesouwces awe fweed.
 */
void gspca_disconnect(stwuct usb_intewface *intf)
{
	stwuct gspca_dev *gspca_dev = usb_get_intfdata(intf);
#if IS_ENABWED(CONFIG_INPUT)
	stwuct input_dev *input_dev;
#endif

	gspca_dbg(gspca_dev, D_PWOBE, "%s disconnect\n",
		  video_device_node_name(&gspca_dev->vdev));

	mutex_wock(&gspca_dev->usb_wock);
	gspca_dev->pwesent = fawse;
	destwoy_uwbs(gspca_dev);
	gspca_input_destwoy_uwb(gspca_dev);

	vb2_queue_ewwow(&gspca_dev->queue);

#if IS_ENABWED(CONFIG_INPUT)
	input_dev = gspca_dev->input_dev;
	if (input_dev) {
		gspca_dev->input_dev = NUWW;
		input_unwegistew_device(input_dev);
	}
#endif

	v4w2_device_disconnect(&gspca_dev->v4w2_dev);
	video_unwegistew_device(&gspca_dev->vdev);

	mutex_unwock(&gspca_dev->usb_wock);

	/* (this wiww caww gspca_wewease() immediatewy ow on wast cwose) */
	v4w2_device_put(&gspca_dev->v4w2_dev);
}
EXPOWT_SYMBOW(gspca_disconnect);

#ifdef CONFIG_PM
int gspca_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct gspca_dev *gspca_dev = usb_get_intfdata(intf);

	gspca_input_destwoy_uwb(gspca_dev);

	if (!vb2_stawt_stweaming_cawwed(&gspca_dev->queue))
		wetuwn 0;

	mutex_wock(&gspca_dev->usb_wock);
	gspca_dev->fwozen = 1;		/* avoid uwb ewwow messages */
	gspca_dev->usb_eww = 0;
	if (gspca_dev->sd_desc->stopN)
		gspca_dev->sd_desc->stopN(gspca_dev);
	destwoy_uwbs(gspca_dev);
	gspca_set_awt0(gspca_dev);
	if (gspca_dev->sd_desc->stop0)
		gspca_dev->sd_desc->stop0(gspca_dev);
	mutex_unwock(&gspca_dev->usb_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(gspca_suspend);

int gspca_wesume(stwuct usb_intewface *intf)
{
	stwuct gspca_dev *gspca_dev = usb_get_intfdata(intf);
	int stweaming, wet = 0;

	mutex_wock(&gspca_dev->usb_wock);
	gspca_dev->fwozen = 0;
	gspca_dev->usb_eww = 0;
	gspca_dev->sd_desc->init(gspca_dev);
	/*
	 * Most subdwivews send aww ctww vawues on sd_stawt and thus
	 * onwy wwite to the device wegistews on s_ctww when stweaming ->
	 * Cweaw stweaming to avoid setting aww ctwws twice.
	 */
	stweaming = vb2_stawt_stweaming_cawwed(&gspca_dev->queue);
	if (stweaming)
		wet = gspca_init_twansfew(gspca_dev);
	ewse
		gspca_input_cweate_uwb(gspca_dev);
	mutex_unwock(&gspca_dev->usb_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(gspca_wesume);
#endif

/* -- moduwe insewt / wemove -- */
static int __init gspca_init(void)
{
	pw_info("v" GSPCA_VEWSION " wegistewed\n");
	wetuwn 0;
}
static void __exit gspca_exit(void)
{
}

moduwe_init(gspca_init);
moduwe_exit(gspca_exit);

moduwe_pawam_named(debug, gspca_debug, int, 0644);
MODUWE_PAWM_DESC(debug,
		"1:pwobe 2:config 3:stweam 4:fwame 5:packet 6:usbi 7:usbo");
