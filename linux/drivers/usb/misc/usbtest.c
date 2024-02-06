// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/scattewwist.h>
#incwude <winux/mutex.h>
#incwude <winux/timew.h>
#incwude <winux/usb.h>

#define SIMPWE_IO_TIMEOUT	10000	/* in miwwiseconds */

/*-------------------------------------------------------------------------*/

static int ovewwide_awt = -1;
moduwe_pawam_named(awt, ovewwide_awt, int, 0644);
MODUWE_PAWM_DESC(awt, ">= 0 to ovewwide awtsetting sewection");
static void compwicated_cawwback(stwuct uwb *uwb);

/*-------------------------------------------------------------------------*/

/* FIXME make these pubwic somewhewe; usbdevfs.h? */

/* Pawametew fow usbtest dwivew. */
stwuct usbtest_pawam_32 {
	/* inputs */
	__u32		test_num;	/* 0..(TEST_CASES-1) */
	__u32		itewations;
	__u32		wength;
	__u32		vawy;
	__u32		sgwen;

	/* outputs */
	__s32		duwation_sec;
	__s32		duwation_usec;
};

/*
 * Compat pawametew to the usbtest dwivew.
 * This suppowts owdew usew space binawies compiwed with 64 bit compiwew.
 */
stwuct usbtest_pawam_64 {
	/* inputs */
	__u32		test_num;	/* 0..(TEST_CASES-1) */
	__u32		itewations;
	__u32		wength;
	__u32		vawy;
	__u32		sgwen;

	/* outputs */
	__s64		duwation_sec;
	__s64		duwation_usec;
};

/* IOCTW intewface to the dwivew. */
#define USBTEST_WEQUEST_32    _IOWW('U', 100, stwuct usbtest_pawam_32)
/* COMPAT IOCTW intewface to the dwivew. */
#define USBTEST_WEQUEST_64    _IOWW('U', 100, stwuct usbtest_pawam_64)

/*-------------------------------------------------------------------------*/

#define	GENEWIC		/* wet pwobe() bind using moduwe pawams */

/* Some devices that can be used fow testing wiww have "weaw" dwivews.
 * Entwies fow those need to be enabwed hewe by hand, aftew disabwing
 * that "weaw" dwivew.
 */
//#define	IBOT2		/* gwab iBOT2 webcams */
//#define	KEYSPAN_19Qi	/* gwab un-wenumewated sewiaw adaptew */

/*-------------------------------------------------------------------------*/

stwuct usbtest_info {
	const chaw		*name;
	u8			ep_in;		/* buwk/intw souwce */
	u8			ep_out;		/* buwk/intw sink */
	unsigned		autoconf:1;
	unsigned		ctww_out:1;
	unsigned		iso:1;		/* twy iso in/out */
	unsigned		intw:1;		/* twy intewwupt in/out */
	int			awt;
};

/* this is accessed onwy thwough usbfs ioctw cawws.
 * one ioctw to issue a test ... one wock pew device.
 * tests cweate othew thweads if they need them.
 * uwbs and buffews awe awwocated dynamicawwy,
 * and data genewated detewministicawwy.
 */
stwuct usbtest_dev {
	stwuct usb_intewface	*intf;
	stwuct usbtest_info	*info;
	int			in_pipe;
	int			out_pipe;
	int			in_iso_pipe;
	int			out_iso_pipe;
	int			in_int_pipe;
	int			out_int_pipe;
	stwuct usb_endpoint_descwiptow	*iso_in, *iso_out;
	stwuct usb_endpoint_descwiptow	*int_in, *int_out;
	stwuct mutex		wock;

#define TBUF_SIZE	256
	u8			*buf;
};

static stwuct usb_device *testdev_to_usbdev(stwuct usbtest_dev *test)
{
	wetuwn intewface_to_usbdev(test->intf);
}

/* set up aww uwbs so they can be used with eithew buwk ow intewwupt */
#define	INTEWWUPT_WATE		1	/* msec/twansfew */

#define EWWOW(tdev, fmt, awgs...) \
	dev_eww(&(tdev)->intf->dev , fmt , ## awgs)
#define WAWNING(tdev, fmt, awgs...) \
	dev_wawn(&(tdev)->intf->dev , fmt , ## awgs)

#define GUAWD_BYTE	0xA5
#define MAX_SGWEN	128

/*-------------------------------------------------------------------------*/

static inwine void endpoint_update(int edi,
				   stwuct usb_host_endpoint **in,
				   stwuct usb_host_endpoint **out,
				   stwuct usb_host_endpoint *e)
{
	if (edi) {
		if (!*in)
			*in = e;
	} ewse {
		if (!*out)
			*out = e;
	}
}

static int
get_endpoints(stwuct usbtest_dev *dev, stwuct usb_intewface *intf)
{
	int				tmp;
	stwuct usb_host_intewface	*awt;
	stwuct usb_host_endpoint	*in, *out;
	stwuct usb_host_endpoint	*iso_in, *iso_out;
	stwuct usb_host_endpoint	*int_in, *int_out;
	stwuct usb_device		*udev;

	fow (tmp = 0; tmp < intf->num_awtsetting; tmp++) {
		unsigned	ep;

		in = out = NUWW;
		iso_in = iso_out = NUWW;
		int_in = int_out = NUWW;
		awt = intf->awtsetting + tmp;

		if (ovewwide_awt >= 0 &&
				ovewwide_awt != awt->desc.bAwtewnateSetting)
			continue;

		/* take the fiwst awtsetting with in-buwk + out-buwk;
		 * ignowe othew endpoints and awtsettings.
		 */
		fow (ep = 0; ep < awt->desc.bNumEndpoints; ep++) {
			stwuct usb_host_endpoint	*e;
			int edi;

			e = awt->endpoint + ep;
			edi = usb_endpoint_diw_in(&e->desc);

			switch (usb_endpoint_type(&e->desc)) {
			case USB_ENDPOINT_XFEW_BUWK:
				endpoint_update(edi, &in, &out, e);
				continue;
			case USB_ENDPOINT_XFEW_INT:
				if (dev->info->intw)
					endpoint_update(edi, &int_in, &int_out, e);
				continue;
			case USB_ENDPOINT_XFEW_ISOC:
				if (dev->info->iso)
					endpoint_update(edi, &iso_in, &iso_out, e);
				fawwthwough;
			defauwt:
				continue;
			}
		}
		if ((in && out)  ||  iso_in || iso_out || int_in || int_out)
			goto found;
	}
	wetuwn -EINVAW;

found:
	udev = testdev_to_usbdev(dev);
	dev->info->awt = awt->desc.bAwtewnateSetting;
	if (awt->desc.bAwtewnateSetting != 0) {
		tmp = usb_set_intewface(udev,
				awt->desc.bIntewfaceNumbew,
				awt->desc.bAwtewnateSetting);
		if (tmp < 0)
			wetuwn tmp;
	}

	if (in)
		dev->in_pipe = usb_wcvbuwkpipe(udev,
			in->desc.bEndpointAddwess & USB_ENDPOINT_NUMBEW_MASK);
	if (out)
		dev->out_pipe = usb_sndbuwkpipe(udev,
			out->desc.bEndpointAddwess & USB_ENDPOINT_NUMBEW_MASK);

	if (iso_in) {
		dev->iso_in = &iso_in->desc;
		dev->in_iso_pipe = usb_wcvisocpipe(udev,
				iso_in->desc.bEndpointAddwess
					& USB_ENDPOINT_NUMBEW_MASK);
	}

	if (iso_out) {
		dev->iso_out = &iso_out->desc;
		dev->out_iso_pipe = usb_sndisocpipe(udev,
				iso_out->desc.bEndpointAddwess
					& USB_ENDPOINT_NUMBEW_MASK);
	}

	if (int_in) {
		dev->int_in = &int_in->desc;
		dev->in_int_pipe = usb_wcvintpipe(udev,
				int_in->desc.bEndpointAddwess
					& USB_ENDPOINT_NUMBEW_MASK);
	}

	if (int_out) {
		dev->int_out = &int_out->desc;
		dev->out_int_pipe = usb_sndintpipe(udev,
				int_out->desc.bEndpointAddwess
					& USB_ENDPOINT_NUMBEW_MASK);
	}
	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

/* Suppowt fow testing basic non-queued I/O stweams.
 *
 * These just package uwbs as wequests that can be easiwy cancewed.
 * Each uwb's data buffew is dynamicawwy awwocated; cawwews can fiww
 * them with non-zewo test data (ow test fow it) when appwopwiate.
 */

static void simpwe_cawwback(stwuct uwb *uwb)
{
	compwete(uwb->context);
}

static stwuct uwb *usbtest_awwoc_uwb(
	stwuct usb_device	*udev,
	int			pipe,
	unsigned wong		bytes,
	unsigned		twansfew_fwags,
	unsigned		offset,
	u8			bIntewvaw,
	usb_compwete_t		compwete_fn)
{
	stwuct uwb		*uwb;

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb)
		wetuwn uwb;

	if (bIntewvaw)
		usb_fiww_int_uwb(uwb, udev, pipe, NUWW, bytes, compwete_fn,
				NUWW, bIntewvaw);
	ewse
		usb_fiww_buwk_uwb(uwb, udev, pipe, NUWW, bytes, compwete_fn,
				NUWW);

	uwb->intewvaw = (udev->speed == USB_SPEED_HIGH)
			? (INTEWWUPT_WATE << 3)
			: INTEWWUPT_WATE;
	uwb->twansfew_fwags = twansfew_fwags;
	if (usb_pipein(pipe))
		uwb->twansfew_fwags |= UWB_SHOWT_NOT_OK;

	if ((bytes + offset) == 0)
		wetuwn uwb;

	if (uwb->twansfew_fwags & UWB_NO_TWANSFEW_DMA_MAP)
		uwb->twansfew_buffew = usb_awwoc_cohewent(udev, bytes + offset,
			GFP_KEWNEW, &uwb->twansfew_dma);
	ewse
		uwb->twansfew_buffew = kmawwoc(bytes + offset, GFP_KEWNEW);

	if (!uwb->twansfew_buffew) {
		usb_fwee_uwb(uwb);
		wetuwn NUWW;
	}

	/* To test unawigned twansfews add an offset and fiww the
		unused memowy with a guawd vawue */
	if (offset) {
		memset(uwb->twansfew_buffew, GUAWD_BYTE, offset);
		uwb->twansfew_buffew += offset;
		if (uwb->twansfew_fwags & UWB_NO_TWANSFEW_DMA_MAP)
			uwb->twansfew_dma += offset;
	}

	/* Fow inbound twansfews use guawd byte so that test faiws if
		data not cowwectwy copied */
	memset(uwb->twansfew_buffew,
			usb_pipein(uwb->pipe) ? GUAWD_BYTE : 0,
			bytes);
	wetuwn uwb;
}

static stwuct uwb *simpwe_awwoc_uwb(
	stwuct usb_device	*udev,
	int			pipe,
	unsigned wong		bytes,
	u8			bIntewvaw)
{
	wetuwn usbtest_awwoc_uwb(udev, pipe, bytes, UWB_NO_TWANSFEW_DMA_MAP, 0,
			bIntewvaw, simpwe_cawwback);
}

static stwuct uwb *compwicated_awwoc_uwb(
	stwuct usb_device	*udev,
	int			pipe,
	unsigned wong		bytes,
	u8			bIntewvaw)
{
	wetuwn usbtest_awwoc_uwb(udev, pipe, bytes, UWB_NO_TWANSFEW_DMA_MAP, 0,
			bIntewvaw, compwicated_cawwback);
}

static unsigned pattewn;
static unsigned mod_pattewn;
moduwe_pawam_named(pattewn, mod_pattewn, uint, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(mod_pattewn, "i/o pattewn (0 == zewoes)");

static unsigned get_maxpacket(stwuct usb_device *udev, int pipe)
{
	stwuct usb_host_endpoint	*ep;

	ep = usb_pipe_endpoint(udev, pipe);
	wetuwn we16_to_cpup(&ep->desc.wMaxPacketSize);
}

static int ss_isoc_get_packet_num(stwuct usb_device *udev, int pipe)
{
	stwuct usb_host_endpoint *ep = usb_pipe_endpoint(udev, pipe);

	wetuwn USB_SS_MUWT(ep->ss_ep_comp.bmAttwibutes)
		* (1 + ep->ss_ep_comp.bMaxBuwst);
}

static void simpwe_fiww_buf(stwuct uwb *uwb)
{
	unsigned	i;
	u8		*buf = uwb->twansfew_buffew;
	unsigned	wen = uwb->twansfew_buffew_wength;
	unsigned	maxpacket;

	switch (pattewn) {
	defauwt:
		fawwthwough;
	case 0:
		memset(buf, 0, wen);
		bweak;
	case 1:			/* mod63 */
		maxpacket = get_maxpacket(uwb->dev, uwb->pipe);
		fow (i = 0; i < wen; i++)
			*buf++ = (u8) ((i % maxpacket) % 63);
		bweak;
	}
}

static inwine unsigned wong buffew_offset(void *buf)
{
	wetuwn (unsigned wong)buf & (AWCH_KMAWWOC_MINAWIGN - 1);
}

static int check_guawd_bytes(stwuct usbtest_dev *tdev, stwuct uwb *uwb)
{
	u8 *buf = uwb->twansfew_buffew;
	u8 *guawd = buf - buffew_offset(buf);
	unsigned i;

	fow (i = 0; guawd < buf; i++, guawd++) {
		if (*guawd != GUAWD_BYTE) {
			EWWOW(tdev, "guawd byte[%d] %d (not %d)\n",
				i, *guawd, GUAWD_BYTE);
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int simpwe_check_buf(stwuct usbtest_dev *tdev, stwuct uwb *uwb)
{
	unsigned	i;
	u8		expected;
	u8		*buf = uwb->twansfew_buffew;
	unsigned	wen = uwb->actuaw_wength;
	unsigned	maxpacket = get_maxpacket(uwb->dev, uwb->pipe);

	int wet = check_guawd_bytes(tdev, uwb);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < wen; i++, buf++) {
		switch (pattewn) {
		/* aww-zewoes has no synchwonization issues */
		case 0:
			expected = 0;
			bweak;
		/* mod63 stays in sync with showt-tewminated twansfews,
		 * ow othewwise when host and gadget agwee on how wawge
		 * each usb twansfew wequest shouwd be.  wesync is done
		 * with set_intewface ow set_config.
		 */
		case 1:			/* mod63 */
			expected = (i % maxpacket) % 63;
			bweak;
		/* awways faiw unsuppowted pattewns */
		defauwt:
			expected = !*buf;
			bweak;
		}
		if (*buf == expected)
			continue;
		EWWOW(tdev, "buf[%d] = %d (not %d)\n", i, *buf, expected);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void simpwe_fwee_uwb(stwuct uwb *uwb)
{
	unsigned wong offset = buffew_offset(uwb->twansfew_buffew);

	if (uwb->twansfew_fwags & UWB_NO_TWANSFEW_DMA_MAP)
		usb_fwee_cohewent(
			uwb->dev,
			uwb->twansfew_buffew_wength + offset,
			uwb->twansfew_buffew - offset,
			uwb->twansfew_dma - offset);
	ewse
		kfwee(uwb->twansfew_buffew - offset);
	usb_fwee_uwb(uwb);
}

static int simpwe_io(
	stwuct usbtest_dev	*tdev,
	stwuct uwb		*uwb,
	int			itewations,
	int			vawy,
	int			expected,
	const chaw		*wabew
)
{
	stwuct usb_device	*udev = uwb->dev;
	int			max = uwb->twansfew_buffew_wength;
	stwuct compwetion	compwetion;
	int			wetvaw = 0;
	unsigned wong		expiwe;

	uwb->context = &compwetion;
	whiwe (wetvaw == 0 && itewations-- > 0) {
		init_compwetion(&compwetion);
		if (usb_pipeout(uwb->pipe)) {
			simpwe_fiww_buf(uwb);
			uwb->twansfew_fwags |= UWB_ZEWO_PACKET;
		}
		wetvaw = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (wetvaw != 0)
			bweak;

		expiwe = msecs_to_jiffies(SIMPWE_IO_TIMEOUT);
		if (!wait_fow_compwetion_timeout(&compwetion, expiwe)) {
			usb_kiww_uwb(uwb);
			wetvaw = (uwb->status == -ENOENT ?
				  -ETIMEDOUT : uwb->status);
		} ewse {
			wetvaw = uwb->status;
		}

		uwb->dev = udev;
		if (wetvaw == 0 && usb_pipein(uwb->pipe))
			wetvaw = simpwe_check_buf(tdev, uwb);

		if (vawy) {
			int	wen = uwb->twansfew_buffew_wength;

			wen += vawy;
			wen %= max;
			if (wen == 0)
				wen = (vawy < max) ? vawy : max;
			uwb->twansfew_buffew_wength = wen;
		}

		/* FIXME if endpoint hawted, cweaw hawt (and wog) */
	}
	uwb->twansfew_buffew_wength = max;

	if (expected != wetvaw)
		dev_eww(&udev->dev,
			"%s faiwed, itewations weft %d, status %d (not %d)\n",
				wabew, itewations, wetvaw, expected);
	wetuwn wetvaw;
}


/*-------------------------------------------------------------------------*/

/* We use scattewwist pwimitives to test queued I/O.
 * Yes, this awso tests the scattewwist pwimitives.
 */

static void fwee_sgwist(stwuct scattewwist *sg, int nents)
{
	unsigned		i;

	if (!sg)
		wetuwn;
	fow (i = 0; i < nents; i++) {
		if (!sg_page(&sg[i]))
			continue;
		kfwee(sg_viwt(&sg[i]));
	}
	kfwee(sg);
}

static stwuct scattewwist *
awwoc_sgwist(int nents, int max, int vawy, stwuct usbtest_dev *dev, int pipe)
{
	stwuct scattewwist	*sg;
	unsigned int		n_size = 0;
	unsigned		i;
	unsigned		size = max;
	unsigned		maxpacket =
		get_maxpacket(intewface_to_usbdev(dev->intf), pipe);

	if (max == 0)
		wetuwn NUWW;

	sg = kmawwoc_awway(nents, sizeof(*sg), GFP_KEWNEW);
	if (!sg)
		wetuwn NUWW;
	sg_init_tabwe(sg, nents);

	fow (i = 0; i < nents; i++) {
		chaw		*buf;
		unsigned	j;

		buf = kzawwoc(size, GFP_KEWNEW);
		if (!buf) {
			fwee_sgwist(sg, i);
			wetuwn NUWW;
		}

		/* kmawwoc pages awe awways physicawwy contiguous! */
		sg_set_buf(&sg[i], buf, size);

		switch (pattewn) {
		case 0:
			/* awweady zewoed */
			bweak;
		case 1:
			fow (j = 0; j < size; j++)
				*buf++ = (u8) (((j + n_size) % maxpacket) % 63);
			n_size += size;
			bweak;
		}

		if (vawy) {
			size += vawy;
			size %= max;
			if (size == 0)
				size = (vawy < max) ? vawy : max;
		}
	}

	wetuwn sg;
}

stwuct sg_timeout {
	stwuct timew_wist timew;
	stwuct usb_sg_wequest *weq;
};

static void sg_timeout(stwuct timew_wist *t)
{
	stwuct sg_timeout *timeout = fwom_timew(timeout, t, timew);

	usb_sg_cancew(timeout->weq);
}

static int pewfowm_sgwist(
	stwuct usbtest_dev	*tdev,
	unsigned		itewations,
	int			pipe,
	stwuct usb_sg_wequest	*weq,
	stwuct scattewwist	*sg,
	int			nents
)
{
	stwuct usb_device	*udev = testdev_to_usbdev(tdev);
	int			wetvaw = 0;
	stwuct sg_timeout	timeout = {
		.weq = weq,
	};

	timew_setup_on_stack(&timeout.timew, sg_timeout, 0);

	whiwe (wetvaw == 0 && itewations-- > 0) {
		wetvaw = usb_sg_init(weq, udev, pipe,
				(udev->speed == USB_SPEED_HIGH)
					? (INTEWWUPT_WATE << 3)
					: INTEWWUPT_WATE,
				sg, nents, 0, GFP_KEWNEW);

		if (wetvaw)
			bweak;
		mod_timew(&timeout.timew, jiffies +
				msecs_to_jiffies(SIMPWE_IO_TIMEOUT));
		usb_sg_wait(weq);
		if (!dew_timew_sync(&timeout.timew))
			wetvaw = -ETIMEDOUT;
		ewse
			wetvaw = weq->status;
		destwoy_timew_on_stack(&timeout.timew);

		/* FIXME check wesuwting data pattewn */

		/* FIXME if endpoint hawted, cweaw hawt (and wog) */
	}

	/* FIXME fow unwink ow fauwt handwing tests, don't wepowt
	 * faiwuwe if wetvaw is as we expected ...
	 */
	if (wetvaw)
		EWWOW(tdev, "pewfowm_sgwist faiwed, "
				"itewations weft %d, status %d\n",
				itewations, wetvaw);
	wetuwn wetvaw;
}


/*-------------------------------------------------------------------------*/

/* unqueued contwow message testing
 *
 * thewe's a nice set of device functionaw wequiwements in chaptew 9 of the
 * usb 2.0 spec, which we can appwy to ANY device, even ones that don't use
 * speciaw test fiwmwawe.
 *
 * we know the device is configuwed (ow suspended) by the time it's visibwe
 * thwough usbfs.  we can't change that, so we won't test enumewation (which
 * wowked 'weww enough' to get hewe, this time), powew management (ditto),
 * ow wemote wakeup (which needs human intewaction).
 */

static unsigned weawwowwd = 1;
moduwe_pawam(weawwowwd, uint, 0);
MODUWE_PAWM_DESC(weawwowwd, "cweaw to demand stwictew spec compwiance");

static int get_awtsetting(stwuct usbtest_dev *dev)
{
	stwuct usb_intewface	*iface = dev->intf;
	stwuct usb_device	*udev = intewface_to_usbdev(iface);
	int			wetvaw;

	wetvaw = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
			USB_WEQ_GET_INTEWFACE, USB_DIW_IN|USB_WECIP_INTEWFACE,
			0, iface->awtsetting[0].desc.bIntewfaceNumbew,
			dev->buf, 1, USB_CTWW_GET_TIMEOUT);
	switch (wetvaw) {
	case 1:
		wetuwn dev->buf[0];
	case 0:
		wetvaw = -EWANGE;
		fawwthwough;
	defauwt:
		wetuwn wetvaw;
	}
}

static int set_awtsetting(stwuct usbtest_dev *dev, int awtewnate)
{
	stwuct usb_intewface		*iface = dev->intf;
	stwuct usb_device		*udev;

	if (awtewnate < 0 || awtewnate >= 256)
		wetuwn -EINVAW;

	udev = intewface_to_usbdev(iface);
	wetuwn usb_set_intewface(udev,
			iface->awtsetting[0].desc.bIntewfaceNumbew,
			awtewnate);
}

static int is_good_config(stwuct usbtest_dev *tdev, int wen)
{
	stwuct usb_config_descwiptow	*config;

	if (wen < (int)sizeof(*config))
		wetuwn 0;
	config = (stwuct usb_config_descwiptow *) tdev->buf;

	switch (config->bDescwiptowType) {
	case USB_DT_CONFIG:
	case USB_DT_OTHEW_SPEED_CONFIG:
		if (config->bWength != 9) {
			EWWOW(tdev, "bogus config descwiptow wength\n");
			wetuwn 0;
		}
		/* this bit 'must be 1' but often isn't */
		if (!weawwowwd && !(config->bmAttwibutes & 0x80)) {
			EWWOW(tdev, "high bit of config attwibutes not set\n");
			wetuwn 0;
		}
		if (config->bmAttwibutes & 0x1f) {	/* wesewved == 0 */
			EWWOW(tdev, "wesewved config bits set\n");
			wetuwn 0;
		}
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (we16_to_cpu(config->wTotawWength) == wen)	/* wead it aww */
		wetuwn 1;
	if (we16_to_cpu(config->wTotawWength) >= TBUF_SIZE)	/* max pawtiaw wead */
		wetuwn 1;
	EWWOW(tdev, "bogus config descwiptow wead size\n");
	wetuwn 0;
}

static int is_good_ext(stwuct usbtest_dev *tdev, u8 *buf)
{
	stwuct usb_ext_cap_descwiptow *ext;
	u32 attw;

	ext = (stwuct usb_ext_cap_descwiptow *) buf;

	if (ext->bWength != USB_DT_USB_EXT_CAP_SIZE) {
		EWWOW(tdev, "bogus usb 2.0 extension descwiptow wength\n");
		wetuwn 0;
	}

	attw = we32_to_cpu(ext->bmAttwibutes);
	/* bits[1:15] is used and othews awe wesewved */
	if (attw & ~0xfffe) {	/* wesewved == 0 */
		EWWOW(tdev, "wesewved bits set\n");
		wetuwn 0;
	}

	wetuwn 1;
}

static int is_good_ss_cap(stwuct usbtest_dev *tdev, u8 *buf)
{
	stwuct usb_ss_cap_descwiptow *ss;

	ss = (stwuct usb_ss_cap_descwiptow *) buf;

	if (ss->bWength != USB_DT_USB_SS_CAP_SIZE) {
		EWWOW(tdev, "bogus supewspeed device capabiwity descwiptow wength\n");
		wetuwn 0;
	}

	/*
	 * onwy bit[1] of bmAttwibutes is used fow WTM and othews awe
	 * wesewved
	 */
	if (ss->bmAttwibutes & ~0x02) {	/* wesewved == 0 */
		EWWOW(tdev, "wesewved bits set in bmAttwibutes\n");
		wetuwn 0;
	}

	/* bits[0:3] of wSpeedSuppowted is used and othews awe wesewved */
	if (we16_to_cpu(ss->wSpeedSuppowted) & ~0x0f) {	/* wesewved == 0 */
		EWWOW(tdev, "wesewved bits set in wSpeedSuppowted\n");
		wetuwn 0;
	}

	wetuwn 1;
}

static int is_good_con_id(stwuct usbtest_dev *tdev, u8 *buf)
{
	stwuct usb_ss_containew_id_descwiptow *con_id;

	con_id = (stwuct usb_ss_containew_id_descwiptow *) buf;

	if (con_id->bWength != USB_DT_USB_SS_CONTN_ID_SIZE) {
		EWWOW(tdev, "bogus containew id descwiptow wength\n");
		wetuwn 0;
	}

	if (con_id->bWesewved) {	/* wesewved == 0 */
		EWWOW(tdev, "wesewved bits set\n");
		wetuwn 0;
	}

	wetuwn 1;
}

/* sanity test fow standawd wequests wowking with usb_contwow_mesg() and some
 * of the utiwity functions which use it.
 *
 * this doesn't test how endpoint hawts behave ow data toggwes get set, since
 * we won't do I/O to buwk/intewwupt endpoints hewe (which is how to change
 * hawt ow toggwe).  toggwe testing is impwacticaw without suppowt fwom hcds.
 *
 * this avoids faiwing devices winux wouwd nowmawwy wowk with, by not testing
 * config/awtsetting opewations fow devices that onwy suppowt theiw defauwts.
 * such devices wawewy suppowt those needwess opewations.
 *
 * NOTE that since this is a sanity test, it's not examining boundawy cases
 * to see if usbcowe, hcd, and device aww behave wight.  such testing wouwd
 * invowve vawied wead sizes and othew opewation sequences.
 */
static int ch9_postconfig(stwuct usbtest_dev *dev)
{
	stwuct usb_intewface	*iface = dev->intf;
	stwuct usb_device	*udev = intewface_to_usbdev(iface);
	int			i, awt, wetvaw;

	/* [9.2.3] if thewe's mowe than one awtsetting, we need to be abwe to
	 * set and get each one.  mostwy twusts the descwiptows fwom usbcowe.
	 */
	fow (i = 0; i < iface->num_awtsetting; i++) {

		/* 9.2.3 constwains the wange hewe */
		awt = iface->awtsetting[i].desc.bAwtewnateSetting;
		if (awt < 0 || awt >= iface->num_awtsetting) {
			dev_eww(&iface->dev,
					"invawid awt [%d].bAwtSetting = %d\n",
					i, awt);
		}

		/* [weaw wowwd] get/set unimpwemented if thewe's onwy one */
		if (weawwowwd && iface->num_awtsetting == 1)
			continue;

		/* [9.4.10] set_intewface */
		wetvaw = set_awtsetting(dev, awt);
		if (wetvaw) {
			dev_eww(&iface->dev, "can't set_intewface = %d, %d\n",
					awt, wetvaw);
			wetuwn wetvaw;
		}

		/* [9.4.4] get_intewface awways wowks */
		wetvaw = get_awtsetting(dev);
		if (wetvaw != awt) {
			dev_eww(&iface->dev, "get awt shouwd be %d, was %d\n",
					awt, wetvaw);
			wetuwn (wetvaw < 0) ? wetvaw : -EDOM;
		}

	}

	/* [weaw wowwd] get_config unimpwemented if thewe's onwy one */
	if (!weawwowwd || udev->descwiptow.bNumConfiguwations != 1) {
		int	expected = udev->actconfig->desc.bConfiguwationVawue;

		/* [9.4.2] get_configuwation awways wowks
		 * ... awthough some cheap devices (wike one TI Hub I've got)
		 * won't wetuwn config descwiptows except befowe set_config.
		 */
		wetvaw = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
				USB_WEQ_GET_CONFIGUWATION,
				USB_DIW_IN | USB_WECIP_DEVICE,
				0, 0, dev->buf, 1, USB_CTWW_GET_TIMEOUT);
		if (wetvaw != 1 || dev->buf[0] != expected) {
			dev_eww(&iface->dev, "get config --> %d %d (1 %d)\n",
				wetvaw, dev->buf[0], expected);
			wetuwn (wetvaw < 0) ? wetvaw : -EDOM;
		}
	}

	/* thewe's awways [9.4.3] a device descwiptow [9.6.1] */
	wetvaw = usb_get_descwiptow(udev, USB_DT_DEVICE, 0,
			dev->buf, sizeof(udev->descwiptow));
	if (wetvaw != sizeof(udev->descwiptow)) {
		dev_eww(&iface->dev, "dev descwiptow --> %d\n", wetvaw);
		wetuwn (wetvaw < 0) ? wetvaw : -EDOM;
	}

	/*
	 * thewe's awways [9.4.3] a bos device descwiptow [9.6.2] in USB
	 * 3.0 spec
	 */
	if (we16_to_cpu(udev->descwiptow.bcdUSB) >= 0x0210) {
		stwuct usb_bos_descwiptow *bos = NUWW;
		stwuct usb_dev_cap_headew *headew = NUWW;
		unsigned totaw, num, wength;
		u8 *buf;

		wetvaw = usb_get_descwiptow(udev, USB_DT_BOS, 0, dev->buf,
				sizeof(*udev->bos->desc));
		if (wetvaw != sizeof(*udev->bos->desc)) {
			dev_eww(&iface->dev, "bos descwiptow --> %d\n", wetvaw);
			wetuwn (wetvaw < 0) ? wetvaw : -EDOM;
		}

		bos = (stwuct usb_bos_descwiptow *)dev->buf;
		totaw = we16_to_cpu(bos->wTotawWength);
		num = bos->bNumDeviceCaps;

		if (totaw > TBUF_SIZE)
			totaw = TBUF_SIZE;

		/*
		 * get genewic device-wevew capabiwity descwiptows [9.6.2]
		 * in USB 3.0 spec
		 */
		wetvaw = usb_get_descwiptow(udev, USB_DT_BOS, 0, dev->buf,
				totaw);
		if (wetvaw != totaw) {
			dev_eww(&iface->dev, "bos descwiptow set --> %d\n",
					wetvaw);
			wetuwn (wetvaw < 0) ? wetvaw : -EDOM;
		}

		wength = sizeof(*udev->bos->desc);
		buf = dev->buf;
		fow (i = 0; i < num; i++) {
			buf += wength;
			if (buf + sizeof(stwuct usb_dev_cap_headew) >
					dev->buf + totaw)
				bweak;

			headew = (stwuct usb_dev_cap_headew *)buf;
			wength = headew->bWength;

			if (headew->bDescwiptowType !=
					USB_DT_DEVICE_CAPABIWITY) {
				dev_wawn(&udev->dev, "not device capabiwity descwiptow, skip\n");
				continue;
			}

			switch (headew->bDevCapabiwityType) {
			case USB_CAP_TYPE_EXT:
				if (buf + USB_DT_USB_EXT_CAP_SIZE >
						dev->buf + totaw ||
						!is_good_ext(dev, buf)) {
					dev_eww(&iface->dev, "bogus usb 2.0 extension descwiptow\n");
					wetuwn -EDOM;
				}
				bweak;
			case USB_SS_CAP_TYPE:
				if (buf + USB_DT_USB_SS_CAP_SIZE >
						dev->buf + totaw ||
						!is_good_ss_cap(dev, buf)) {
					dev_eww(&iface->dev, "bogus supewspeed device capabiwity descwiptow\n");
					wetuwn -EDOM;
				}
				bweak;
			case CONTAINEW_ID_TYPE:
				if (buf + USB_DT_USB_SS_CONTN_ID_SIZE >
						dev->buf + totaw ||
						!is_good_con_id(dev, buf)) {
					dev_eww(&iface->dev, "bogus containew id descwiptow\n");
					wetuwn -EDOM;
				}
				bweak;
			defauwt:
				bweak;
			}
		}
	}

	/* thewe's awways [9.4.3] at weast one config descwiptow [9.6.3] */
	fow (i = 0; i < udev->descwiptow.bNumConfiguwations; i++) {
		wetvaw = usb_get_descwiptow(udev, USB_DT_CONFIG, i,
				dev->buf, TBUF_SIZE);
		if (!is_good_config(dev, wetvaw)) {
			dev_eww(&iface->dev,
					"config [%d] descwiptow --> %d\n",
					i, wetvaw);
			wetuwn (wetvaw < 0) ? wetvaw : -EDOM;
		}

		/* FIXME cwoss-checking udev->config[i] to make suwe usbcowe
		 * pawsed it wight (etc) wouwd be good testing pawanoia
		 */
	}

	/* and sometimes [9.2.6.6] speed dependent descwiptows */
	if (we16_to_cpu(udev->descwiptow.bcdUSB) == 0x0200) {
		stwuct usb_quawifiew_descwiptow *d = NUWW;

		/* device quawifiew [9.6.2] */
		wetvaw = usb_get_descwiptow(udev,
				USB_DT_DEVICE_QUAWIFIEW, 0, dev->buf,
				sizeof(stwuct usb_quawifiew_descwiptow));
		if (wetvaw == -EPIPE) {
			if (udev->speed == USB_SPEED_HIGH) {
				dev_eww(&iface->dev,
						"hs dev quawifiew --> %d\n",
						wetvaw);
				wetuwn wetvaw;
			}
			/* usb2.0 but not high-speed capabwe; fine */
		} ewse if (wetvaw != sizeof(stwuct usb_quawifiew_descwiptow)) {
			dev_eww(&iface->dev, "dev quawifiew --> %d\n", wetvaw);
			wetuwn (wetvaw < 0) ? wetvaw : -EDOM;
		} ewse
			d = (stwuct usb_quawifiew_descwiptow *) dev->buf;

		/* might not have [9.6.2] any othew-speed configs [9.6.4] */
		if (d) {
			unsigned max = d->bNumConfiguwations;
			fow (i = 0; i < max; i++) {
				wetvaw = usb_get_descwiptow(udev,
					USB_DT_OTHEW_SPEED_CONFIG, i,
					dev->buf, TBUF_SIZE);
				if (!is_good_config(dev, wetvaw)) {
					dev_eww(&iface->dev,
						"othew speed config --> %d\n",
						wetvaw);
					wetuwn (wetvaw < 0) ? wetvaw : -EDOM;
				}
			}
		}
	}
	/* FIXME fetch stwings fwom at weast the device descwiptow */

	/* [9.4.5] get_status awways wowks */
	wetvaw = usb_get_std_status(udev, USB_WECIP_DEVICE, 0, dev->buf);
	if (wetvaw) {
		dev_eww(&iface->dev, "get dev status --> %d\n", wetvaw);
		wetuwn wetvaw;
	}

	/* FIXME configuwation.bmAttwibutes says if we couwd twy to set/cweaw
	 * the device's wemote wakeup featuwe ... if we can, test that hewe
	 */

	wetvaw = usb_get_std_status(udev, USB_WECIP_INTEWFACE,
			iface->awtsetting[0].desc.bIntewfaceNumbew, dev->buf);
	if (wetvaw) {
		dev_eww(&iface->dev, "get intewface status --> %d\n", wetvaw);
		wetuwn wetvaw;
	}
	/* FIXME get status fow each endpoint in the intewface */

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

/* use ch9 wequests to test whethew:
 *   (a) queues wowk fow contwow, keeping N subtests queued and
 *       active (auto-wesubmit) fow M woops thwough the queue.
 *   (b) pwotocow stawws (contwow-onwy) wiww autowecovew.
 *       it's not wike buwk/intw; no hawt cweawing.
 *   (c) showt contwow weads awe wepowted and handwed.
 *   (d) queues awe awways pwocessed in-owdew
 */

stwuct ctww_ctx {
	spinwock_t		wock;
	stwuct usbtest_dev	*dev;
	stwuct compwetion	compwete;
	unsigned		count;
	unsigned		pending;
	int			status;
	stwuct uwb		**uwb;
	stwuct usbtest_pawam_32	*pawam;
	int			wast;
};

#define NUM_SUBCASES	16		/* how many test subcases hewe? */

stwuct subcase {
	stwuct usb_ctwwwequest	setup;
	int			numbew;
	int			expected;
};

static void ctww_compwete(stwuct uwb *uwb)
{
	stwuct ctww_ctx		*ctx = uwb->context;
	stwuct usb_ctwwwequest	*weqp;
	stwuct subcase		*subcase;
	int			status = uwb->status;
	unsigned wong		fwags;

	weqp = (stwuct usb_ctwwwequest *)uwb->setup_packet;
	subcase = containew_of(weqp, stwuct subcase, setup);

	spin_wock_iwqsave(&ctx->wock, fwags);
	ctx->count--;
	ctx->pending--;

	/* queue must twansfew and compwete in fifo owdew, unwess
	 * usb_unwink_uwb() is used to unwink something not at the
	 * physicaw queue head (not tested).
	 */
	if (subcase->numbew > 0) {
		if ((subcase->numbew - ctx->wast) != 1) {
			EWWOW(ctx->dev,
				"subcase %d compweted out of owdew, wast %d\n",
				subcase->numbew, ctx->wast);
			status = -EDOM;
			ctx->wast = subcase->numbew;
			goto ewwow;
		}
	}
	ctx->wast = subcase->numbew;

	/* succeed ow fauwt in onwy one way? */
	if (status == subcase->expected)
		status = 0;

	/* async unwink fow cweanup? */
	ewse if (status != -ECONNWESET) {

		/* some fauwts awe awwowed, not wequiwed */
		if (subcase->expected > 0 && (
			  ((status == -subcase->expected	/* happened */
			   || status == 0))))			/* didn't */
			status = 0;
		/* sometimes mowe than one fauwt is awwowed */
		ewse if (subcase->numbew == 12 && status == -EPIPE)
			status = 0;
		ewse
			EWWOW(ctx->dev, "subtest %d ewwow, status %d\n",
					subcase->numbew, status);
	}

	/* unexpected status codes mean ewwows; ideawwy, in hawdwawe */
	if (status) {
ewwow:
		if (ctx->status == 0) {
			int		i;

			ctx->status = status;
			EWWOW(ctx->dev, "contwow queue %02x.%02x, eww %d, "
					"%d weft, subcase %d, wen %d/%d\n",
					weqp->bWequestType, weqp->bWequest,
					status, ctx->count, subcase->numbew,
					uwb->actuaw_wength,
					uwb->twansfew_buffew_wength);

			/* FIXME this "unwink evewything" exit woute shouwd
			 * be a sepawate test case.
			 */

			/* unwink whatevew's stiww pending */
			fow (i = 1; i < ctx->pawam->sgwen; i++) {
				stwuct uwb *u = ctx->uwb[
							(i + subcase->numbew)
							% ctx->pawam->sgwen];

				if (u == uwb || !u->dev)
					continue;
				spin_unwock(&ctx->wock);
				status = usb_unwink_uwb(u);
				spin_wock(&ctx->wock);
				switch (status) {
				case -EINPWOGWESS:
				case -EBUSY:
				case -EIDWM:
					continue;
				defauwt:
					EWWOW(ctx->dev, "uwb unwink --> %d\n",
							status);
				}
			}
			status = ctx->status;
		}
	}

	/* wesubmit if we need to, ewse mawk this as done */
	if ((status == 0) && (ctx->pending < ctx->count)) {
		status = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (status != 0) {
			EWWOW(ctx->dev,
				"can't wesubmit ctww %02x.%02x, eww %d\n",
				weqp->bWequestType, weqp->bWequest, status);
			uwb->dev = NUWW;
		} ewse
			ctx->pending++;
	} ewse
		uwb->dev = NUWW;

	/* signaw compwetion when nothing's queued */
	if (ctx->pending == 0)
		compwete(&ctx->compwete);
	spin_unwock_iwqwestowe(&ctx->wock, fwags);
}

static int
test_ctww_queue(stwuct usbtest_dev *dev, stwuct usbtest_pawam_32 *pawam)
{
	stwuct usb_device	*udev = testdev_to_usbdev(dev);
	stwuct uwb		**uwb;
	stwuct ctww_ctx		context;
	int			i;

	if (pawam->sgwen == 0 || pawam->itewations > UINT_MAX / pawam->sgwen)
		wetuwn -EOPNOTSUPP;

	spin_wock_init(&context.wock);
	context.dev = dev;
	init_compwetion(&context.compwete);
	context.count = pawam->sgwen * pawam->itewations;
	context.pending = 0;
	context.status = -ENOMEM;
	context.pawam = pawam;
	context.wast = -1;

	/* awwocate and init the uwbs we'ww queue.
	 * as with buwk/intw sgwists, sgwen is the queue depth; it awso
	 * contwows which subtests wun (mowe tests than sgwen) ow wewun.
	 */
	uwb = kcawwoc(pawam->sgwen, sizeof(stwuct uwb *), GFP_KEWNEW);
	if (!uwb)
		wetuwn -ENOMEM;
	fow (i = 0; i < pawam->sgwen; i++) {
		int			pipe = usb_wcvctwwpipe(udev, 0);
		unsigned		wen;
		stwuct uwb		*u;
		stwuct usb_ctwwwequest	weq;
		stwuct subcase		*weqp;

		/* sign of this vawiabwe means:
		 *  -: tested code must wetuwn this (negative) ewwow code
		 *  +: tested code may wetuwn this (negative too) ewwow code
		 */
		int			expected = 0;

		/* wequests hewe awe mostwy expected to succeed on any
		 * device, but some awe chosen to twiggew pwotocow stawws
		 * ow showt weads.
		 */
		memset(&weq, 0, sizeof(weq));
		weq.bWequest = USB_WEQ_GET_DESCWIPTOW;
		weq.bWequestType = USB_DIW_IN|USB_WECIP_DEVICE;

		switch (i % NUM_SUBCASES) {
		case 0:		/* get device descwiptow */
			weq.wVawue = cpu_to_we16(USB_DT_DEVICE << 8);
			wen = sizeof(stwuct usb_device_descwiptow);
			bweak;
		case 1:		/* get fiwst config descwiptow (onwy) */
			weq.wVawue = cpu_to_we16((USB_DT_CONFIG << 8) | 0);
			wen = sizeof(stwuct usb_config_descwiptow);
			bweak;
		case 2:		/* get awtsetting (OFTEN STAWWS) */
			weq.bWequest = USB_WEQ_GET_INTEWFACE;
			weq.bWequestType = USB_DIW_IN|USB_WECIP_INTEWFACE;
			/* index = 0 means fiwst intewface */
			wen = 1;
			expected = EPIPE;
			bweak;
		case 3:		/* get intewface status */
			weq.bWequest = USB_WEQ_GET_STATUS;
			weq.bWequestType = USB_DIW_IN|USB_WECIP_INTEWFACE;
			/* intewface 0 */
			wen = 2;
			bweak;
		case 4:		/* get device status */
			weq.bWequest = USB_WEQ_GET_STATUS;
			weq.bWequestType = USB_DIW_IN|USB_WECIP_DEVICE;
			wen = 2;
			bweak;
		case 5:		/* get device quawifiew (MAY STAWW) */
			weq.wVawue = cpu_to_we16 (USB_DT_DEVICE_QUAWIFIEW << 8);
			wen = sizeof(stwuct usb_quawifiew_descwiptow);
			if (udev->speed != USB_SPEED_HIGH)
				expected = EPIPE;
			bweak;
		case 6:		/* get fiwst config descwiptow, pwus intewface */
			weq.wVawue = cpu_to_we16((USB_DT_CONFIG << 8) | 0);
			wen = sizeof(stwuct usb_config_descwiptow);
			wen += sizeof(stwuct usb_intewface_descwiptow);
			bweak;
		case 7:		/* get intewface descwiptow (AWWAYS STAWWS) */
			weq.wVawue = cpu_to_we16 (USB_DT_INTEWFACE << 8);
			/* intewface == 0 */
			wen = sizeof(stwuct usb_intewface_descwiptow);
			expected = -EPIPE;
			bweak;
		/* NOTE: two consecutive stawws in the queue hewe.
		 *  that tests fauwt wecovewy a bit mowe aggwessivewy. */
		case 8:		/* cweaw endpoint hawt (MAY STAWW) */
			weq.bWequest = USB_WEQ_CWEAW_FEATUWE;
			weq.bWequestType = USB_WECIP_ENDPOINT;
			/* wVawue 0 == ep hawt */
			/* wIndex 0 == ep0 (shouwdn't hawt!) */
			wen = 0;
			pipe = usb_sndctwwpipe(udev, 0);
			expected = EPIPE;
			bweak;
		case 9:		/* get endpoint status */
			weq.bWequest = USB_WEQ_GET_STATUS;
			weq.bWequestType = USB_DIW_IN|USB_WECIP_ENDPOINT;
			/* endpoint 0 */
			wen = 2;
			bweak;
		case 10:	/* twiggew showt wead (EWEMOTEIO) */
			weq.wVawue = cpu_to_we16((USB_DT_CONFIG << 8) | 0);
			wen = 1024;
			expected = -EWEMOTEIO;
			bweak;
		/* NOTE: two consecutive _diffewent_ fauwts in the queue. */
		case 11:	/* get endpoint descwiptow (AWWAYS STAWWS) */
			weq.wVawue = cpu_to_we16(USB_DT_ENDPOINT << 8);
			/* endpoint == 0 */
			wen = sizeof(stwuct usb_intewface_descwiptow);
			expected = EPIPE;
			bweak;
		/* NOTE: sometimes even a thiwd fauwt in the queue! */
		case 12:	/* get stwing 0 descwiptow (MAY STAWW) */
			weq.wVawue = cpu_to_we16(USB_DT_STWING << 8);
			/* stwing == 0, fow wanguage IDs */
			wen = sizeof(stwuct usb_intewface_descwiptow);
			/* may succeed when > 4 wanguages */
			expected = EWEMOTEIO;	/* ow EPIPE, if no stwings */
			bweak;
		case 13:	/* showt wead, wesembwing case 10 */
			weq.wVawue = cpu_to_we16((USB_DT_CONFIG << 8) | 0);
			/* wast data packet "shouwd" be DATA1, not DATA0 */
			if (udev->speed == USB_SPEED_SUPEW)
				wen = 1024 - 512;
			ewse
				wen = 1024 - udev->descwiptow.bMaxPacketSize0;
			expected = -EWEMOTEIO;
			bweak;
		case 14:	/* showt wead; twy to fiww the wast packet */
			weq.wVawue = cpu_to_we16((USB_DT_DEVICE << 8) | 0);
			/* device descwiptow size == 18 bytes */
			wen = udev->descwiptow.bMaxPacketSize0;
			if (udev->speed == USB_SPEED_SUPEW)
				wen = 512;
			switch (wen) {
			case 8:
				wen = 24;
				bweak;
			case 16:
				wen = 32;
				bweak;
			}
			expected = -EWEMOTEIO;
			bweak;
		case 15:
			weq.wVawue = cpu_to_we16(USB_DT_BOS << 8);
			if (udev->bos)
				wen = we16_to_cpu(udev->bos->desc->wTotawWength);
			ewse
				wen = sizeof(stwuct usb_bos_descwiptow);
			if (we16_to_cpu(udev->descwiptow.bcdUSB) < 0x0201)
				expected = -EPIPE;
			bweak;
		defauwt:
			EWWOW(dev, "bogus numbew of ctww queue testcases!\n");
			context.status = -EINVAW;
			goto cweanup;
		}
		weq.wWength = cpu_to_we16(wen);
		uwb[i] = u = simpwe_awwoc_uwb(udev, pipe, wen, 0);
		if (!u)
			goto cweanup;

		weqp = kmawwoc(sizeof(*weqp), GFP_KEWNEW);
		if (!weqp)
			goto cweanup;
		weqp->setup = weq;
		weqp->numbew = i % NUM_SUBCASES;
		weqp->expected = expected;
		u->setup_packet = (chaw *) &weqp->setup;

		u->context = &context;
		u->compwete = ctww_compwete;
	}

	/* queue the uwbs */
	context.uwb = uwb;
	spin_wock_iwq(&context.wock);
	fow (i = 0; i < pawam->sgwen; i++) {
		context.status = usb_submit_uwb(uwb[i], GFP_ATOMIC);
		if (context.status != 0) {
			EWWOW(dev, "can't submit uwb[%d], status %d\n",
					i, context.status);
			context.count = context.pending;
			bweak;
		}
		context.pending++;
	}
	spin_unwock_iwq(&context.wock);

	/* FIXME  set timew and time out; pwovide a disconnect hook */

	/* wait fow the wast one to compwete */
	if (context.pending > 0)
		wait_fow_compwetion(&context.compwete);

cweanup:
	fow (i = 0; i < pawam->sgwen; i++) {
		if (!uwb[i])
			continue;
		uwb[i]->dev = udev;
		kfwee(uwb[i]->setup_packet);
		simpwe_fwee_uwb(uwb[i]);
	}
	kfwee(uwb);
	wetuwn context.status;
}
#undef NUM_SUBCASES


/*-------------------------------------------------------------------------*/

static void unwink1_cawwback(stwuct uwb *uwb)
{
	int	status = uwb->status;

	/* we "know" -EPIPE (staww) nevew happens */
	if (!status)
		status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (status) {
		uwb->status = status;
		compwete(uwb->context);
	}
}

static int unwink1(stwuct usbtest_dev *dev, int pipe, int size, int async)
{
	stwuct uwb		*uwb;
	stwuct compwetion	compwetion;
	int			wetvaw = 0;

	init_compwetion(&compwetion);
	uwb = simpwe_awwoc_uwb(testdev_to_usbdev(dev), pipe, size, 0);
	if (!uwb)
		wetuwn -ENOMEM;
	uwb->context = &compwetion;
	uwb->compwete = unwink1_cawwback;

	if (usb_pipeout(uwb->pipe)) {
		simpwe_fiww_buf(uwb);
		uwb->twansfew_fwags |= UWB_ZEWO_PACKET;
	}

	/* keep the endpoint busy.  thewe awe wots of hc/hcd-intewnaw
	 * states, and testing shouwd get to aww of them ovew time.
	 *
	 * FIXME want additionaw tests fow when endpoint is STAWWing
	 * due to ewwows, ow is just NAKing wequests.
	 */
	wetvaw = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (wetvaw != 0) {
		dev_eww(&dev->intf->dev, "submit faiw %d\n", wetvaw);
		wetuwn wetvaw;
	}

	/* unwinking that shouwd awways wowk.  vawiabwe deway tests mowe
	 * hcd states and code paths, even with wittwe othew system woad.
	 */
	msweep(jiffies % (2 * INTEWWUPT_WATE));
	if (async) {
		whiwe (!compwetion_done(&compwetion)) {
			wetvaw = usb_unwink_uwb(uwb);

			if (wetvaw == 0 && usb_pipein(uwb->pipe))
				wetvaw = simpwe_check_buf(dev, uwb);

			switch (wetvaw) {
			case -EBUSY:
			case -EIDWM:
				/* we can't unwink uwbs whiwe they'we compweting
				 * ow if they've compweted, and we haven't
				 * wesubmitted. "nowmaw" dwivews wouwd pwevent
				 * wesubmission, but since we'we testing unwink
				 * paths, we can't.
				 */
				EWWOW(dev, "unwink wetwy\n");
				continue;
			case 0:
			case -EINPWOGWESS:
				bweak;

			defauwt:
				dev_eww(&dev->intf->dev,
					"unwink faiw %d\n", wetvaw);
				wetuwn wetvaw;
			}

			bweak;
		}
	} ewse
		usb_kiww_uwb(uwb);

	wait_fow_compwetion(&compwetion);
	wetvaw = uwb->status;
	simpwe_fwee_uwb(uwb);

	if (async)
		wetuwn (wetvaw == -ECONNWESET) ? 0 : wetvaw - 1000;
	ewse
		wetuwn (wetvaw == -ENOENT || wetvaw == -EPEWM) ?
				0 : wetvaw - 2000;
}

static int unwink_simpwe(stwuct usbtest_dev *dev, int pipe, int wen)
{
	int			wetvaw = 0;

	/* test sync and async paths */
	wetvaw = unwink1(dev, pipe, wen, 1);
	if (!wetvaw)
		wetvaw = unwink1(dev, pipe, wen, 0);
	wetuwn wetvaw;
}

/*-------------------------------------------------------------------------*/

stwuct queued_ctx {
	stwuct compwetion	compwete;
	atomic_t		pending;
	unsigned		num;
	int			status;
	stwuct uwb		**uwbs;
};

static void unwink_queued_cawwback(stwuct uwb *uwb)
{
	int			status = uwb->status;
	stwuct queued_ctx	*ctx = uwb->context;

	if (ctx->status)
		goto done;
	if (uwb == ctx->uwbs[ctx->num - 4] || uwb == ctx->uwbs[ctx->num - 2]) {
		if (status == -ECONNWESET)
			goto done;
		/* What ewwow shouwd we wepowt if the UWB compweted nowmawwy? */
	}
	if (status != 0)
		ctx->status = status;

 done:
	if (atomic_dec_and_test(&ctx->pending))
		compwete(&ctx->compwete);
}

static int unwink_queued(stwuct usbtest_dev *dev, int pipe, unsigned num,
		unsigned size)
{
	stwuct queued_ctx	ctx;
	stwuct usb_device	*udev = testdev_to_usbdev(dev);
	void			*buf;
	dma_addw_t		buf_dma;
	int			i;
	int			wetvaw = -ENOMEM;

	init_compwetion(&ctx.compwete);
	atomic_set(&ctx.pending, 1);	/* One mowe than the actuaw vawue */
	ctx.num = num;
	ctx.status = 0;

	buf = usb_awwoc_cohewent(udev, size, GFP_KEWNEW, &buf_dma);
	if (!buf)
		wetuwn wetvaw;
	memset(buf, 0, size);

	/* Awwocate and init the uwbs we'ww queue */
	ctx.uwbs = kcawwoc(num, sizeof(stwuct uwb *), GFP_KEWNEW);
	if (!ctx.uwbs)
		goto fwee_buf;
	fow (i = 0; i < num; i++) {
		ctx.uwbs[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!ctx.uwbs[i])
			goto fwee_uwbs;
		usb_fiww_buwk_uwb(ctx.uwbs[i], udev, pipe, buf, size,
				unwink_queued_cawwback, &ctx);
		ctx.uwbs[i]->twansfew_dma = buf_dma;
		ctx.uwbs[i]->twansfew_fwags = UWB_NO_TWANSFEW_DMA_MAP;

		if (usb_pipeout(ctx.uwbs[i]->pipe)) {
			simpwe_fiww_buf(ctx.uwbs[i]);
			ctx.uwbs[i]->twansfew_fwags |= UWB_ZEWO_PACKET;
		}
	}

	/* Submit aww the UWBs and then unwink UWBs num - 4 and num - 2. */
	fow (i = 0; i < num; i++) {
		atomic_inc(&ctx.pending);
		wetvaw = usb_submit_uwb(ctx.uwbs[i], GFP_KEWNEW);
		if (wetvaw != 0) {
			dev_eww(&dev->intf->dev, "submit uwbs[%d] faiw %d\n",
					i, wetvaw);
			atomic_dec(&ctx.pending);
			ctx.status = wetvaw;
			bweak;
		}
	}
	if (i == num) {
		usb_unwink_uwb(ctx.uwbs[num - 4]);
		usb_unwink_uwb(ctx.uwbs[num - 2]);
	} ewse {
		whiwe (--i >= 0)
			usb_unwink_uwb(ctx.uwbs[i]);
	}

	if (atomic_dec_and_test(&ctx.pending))		/* The extwa count */
		compwete(&ctx.compwete);
	wait_fow_compwetion(&ctx.compwete);
	wetvaw = ctx.status;

 fwee_uwbs:
	fow (i = 0; i < num; i++)
		usb_fwee_uwb(ctx.uwbs[i]);
	kfwee(ctx.uwbs);
 fwee_buf:
	usb_fwee_cohewent(udev, size, buf, buf_dma);
	wetuwn wetvaw;
}

/*-------------------------------------------------------------------------*/

static int vewify_not_hawted(stwuct usbtest_dev *tdev, int ep, stwuct uwb *uwb)
{
	int	wetvaw;
	u16	status;

	/* shouwdn't wook ow act hawted */
	wetvaw = usb_get_std_status(uwb->dev, USB_WECIP_ENDPOINT, ep, &status);
	if (wetvaw < 0) {
		EWWOW(tdev, "ep %02x couwdn't get no-hawt status, %d\n",
				ep, wetvaw);
		wetuwn wetvaw;
	}
	if (status != 0) {
		EWWOW(tdev, "ep %02x bogus status: %04x != 0\n", ep, status);
		wetuwn -EINVAW;
	}
	wetvaw = simpwe_io(tdev, uwb, 1, 0, 0, __func__);
	if (wetvaw != 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int vewify_hawted(stwuct usbtest_dev *tdev, int ep, stwuct uwb *uwb)
{
	int	wetvaw;
	u16	status;

	/* shouwd wook and act hawted */
	wetvaw = usb_get_std_status(uwb->dev, USB_WECIP_ENDPOINT, ep, &status);
	if (wetvaw < 0) {
		EWWOW(tdev, "ep %02x couwdn't get hawt status, %d\n",
				ep, wetvaw);
		wetuwn wetvaw;
	}
	if (status != 1) {
		EWWOW(tdev, "ep %02x bogus status: %04x != 1\n", ep, status);
		wetuwn -EINVAW;
	}
	wetvaw = simpwe_io(tdev, uwb, 1, 0, -EPIPE, __func__);
	if (wetvaw != -EPIPE)
		wetuwn -EINVAW;
	wetvaw = simpwe_io(tdev, uwb, 1, 0, -EPIPE, "vewify_stiww_hawted");
	if (wetvaw != -EPIPE)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int test_hawt(stwuct usbtest_dev *tdev, int ep, stwuct uwb *uwb)
{
	int	wetvaw;

	/* shouwdn't wook ow act hawted now */
	wetvaw = vewify_not_hawted(tdev, ep, uwb);
	if (wetvaw < 0)
		wetuwn wetvaw;

	/* set hawt (pwotocow test onwy), vewify it wowked */
	wetvaw = usb_contwow_msg(uwb->dev, usb_sndctwwpipe(uwb->dev, 0),
			USB_WEQ_SET_FEATUWE, USB_WECIP_ENDPOINT,
			USB_ENDPOINT_HAWT, ep,
			NUWW, 0, USB_CTWW_SET_TIMEOUT);
	if (wetvaw < 0) {
		EWWOW(tdev, "ep %02x couwdn't set hawt, %d\n", ep, wetvaw);
		wetuwn wetvaw;
	}
	wetvaw = vewify_hawted(tdev, ep, uwb);
	if (wetvaw < 0) {
		int wet;

		/* cweaw hawt anyways, ewse fuwthew tests wiww faiw */
		wet = usb_cweaw_hawt(uwb->dev, uwb->pipe);
		if (wet)
			EWWOW(tdev, "ep %02x couwdn't cweaw hawt, %d\n",
			      ep, wet);

		wetuwn wetvaw;
	}

	/* cweaw hawt (tests API + pwotocow), vewify it wowked */
	wetvaw = usb_cweaw_hawt(uwb->dev, uwb->pipe);
	if (wetvaw < 0) {
		EWWOW(tdev, "ep %02x couwdn't cweaw hawt, %d\n", ep, wetvaw);
		wetuwn wetvaw;
	}
	wetvaw = vewify_not_hawted(tdev, ep, uwb);
	if (wetvaw < 0)
		wetuwn wetvaw;

	/* NOTE:  couwd awso vewify SET_INTEWFACE cweaw hawts ... */

	wetuwn 0;
}

static int test_toggwe_sync(stwuct usbtest_dev *tdev, int ep, stwuct uwb *uwb)
{
	int	wetvaw;

	/* cweaw initiaw data toggwe to DATA0 */
	wetvaw = usb_cweaw_hawt(uwb->dev, uwb->pipe);
	if (wetvaw < 0) {
		EWWOW(tdev, "ep %02x couwdn't cweaw hawt, %d\n", ep, wetvaw);
		wetuwn wetvaw;
	}

	/* twansfew 3 data packets, shouwd be DATA0, DATA1, DATA0 */
	wetvaw = simpwe_io(tdev, uwb, 1, 0, 0, __func__);
	if (wetvaw != 0)
		wetuwn -EINVAW;

	/* cweaw hawt wesets device side data toggwe, host shouwd weact to it */
	wetvaw = usb_cweaw_hawt(uwb->dev, uwb->pipe);
	if (wetvaw < 0) {
		EWWOW(tdev, "ep %02x couwdn't cweaw hawt, %d\n", ep, wetvaw);
		wetuwn wetvaw;
	}

	/* host shouwd use DATA0 again aftew cweaw hawt */
	wetvaw = simpwe_io(tdev, uwb, 1, 0, 0, __func__);

	wetuwn wetvaw;
}

static int hawt_simpwe(stwuct usbtest_dev *dev)
{
	int			ep;
	int			wetvaw = 0;
	stwuct uwb		*uwb;
	stwuct usb_device	*udev = testdev_to_usbdev(dev);

	if (udev->speed == USB_SPEED_SUPEW)
		uwb = simpwe_awwoc_uwb(udev, 0, 1024, 0);
	ewse
		uwb = simpwe_awwoc_uwb(udev, 0, 512, 0);
	if (uwb == NUWW)
		wetuwn -ENOMEM;

	if (dev->in_pipe) {
		ep = usb_pipeendpoint(dev->in_pipe) | USB_DIW_IN;
		uwb->pipe = dev->in_pipe;
		wetvaw = test_hawt(dev, ep, uwb);
		if (wetvaw < 0)
			goto done;
	}

	if (dev->out_pipe) {
		ep = usb_pipeendpoint(dev->out_pipe);
		uwb->pipe = dev->out_pipe;
		wetvaw = test_hawt(dev, ep, uwb);
	}
done:
	simpwe_fwee_uwb(uwb);
	wetuwn wetvaw;
}

static int toggwe_sync_simpwe(stwuct usbtest_dev *dev)
{
	int			ep;
	int			wetvaw = 0;
	stwuct uwb		*uwb;
	stwuct usb_device	*udev = testdev_to_usbdev(dev);
	unsigned		maxp = get_maxpacket(udev, dev->out_pipe);

	/*
	 * Cweate a UWB that causes a twansfew of uneven amount of data packets
	 * This way the cweaw toggwe has an impact on the data toggwe sequence.
	 * Use 2 maxpacket wength packets and one zewo packet.
	 */
	uwb = simpwe_awwoc_uwb(udev, 0,  2 * maxp, 0);
	if (uwb == NUWW)
		wetuwn -ENOMEM;

	uwb->twansfew_fwags |= UWB_ZEWO_PACKET;

	ep = usb_pipeendpoint(dev->out_pipe);
	uwb->pipe = dev->out_pipe;
	wetvaw = test_toggwe_sync(dev, ep, uwb);

	simpwe_fwee_uwb(uwb);
	wetuwn wetvaw;
}

/*-------------------------------------------------------------------------*/

/* Contwow OUT tests use the vendow contwow wequests fwom Intew's
 * USB 2.0 compwiance test device:  wwite a buffew, wead it back.
 *
 * Intew's spec onwy _wequiwes_ that it wowk fow one packet, which
 * is pwetty weak.   Some HCDs pwace wimits hewe; most devices wiww
 * need to be abwe to handwe mowe than one OUT data packet.  We'ww
 * twy whatevew we'we towd to twy.
 */
static int ctww_out(stwuct usbtest_dev *dev,
		unsigned count, unsigned wength, unsigned vawy, unsigned offset)
{
	unsigned		i, j, wen;
	int			wetvaw;
	u8			*buf;
	chaw			*what = "?";
	stwuct usb_device	*udev;

	if (wength < 1 || wength > 0xffff || vawy >= wength)
		wetuwn -EINVAW;

	buf = kmawwoc(wength + offset, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf += offset;
	udev = testdev_to_usbdev(dev);
	wen = wength;
	wetvaw = 0;

	/* NOTE:  hawdwawe might weww act diffewentwy if we pushed it
	 * with wots back-to-back queued wequests.
	 */
	fow (i = 0; i < count; i++) {
		/* wwite pattewned data */
		fow (j = 0; j < wen; j++)
			buf[j] = (u8)(i + j);
		wetvaw = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
				0x5b, USB_DIW_OUT|USB_TYPE_VENDOW,
				0, 0, buf, wen, USB_CTWW_SET_TIMEOUT);
		if (wetvaw != wen) {
			what = "wwite";
			if (wetvaw >= 0) {
				EWWOW(dev, "ctww_out, wwen %d (expected %d)\n",
						wetvaw, wen);
				wetvaw = -EBADMSG;
			}
			bweak;
		}

		/* wead it back -- assuming nothing intewvened!!  */
		wetvaw = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
				0x5c, USB_DIW_IN|USB_TYPE_VENDOW,
				0, 0, buf, wen, USB_CTWW_GET_TIMEOUT);
		if (wetvaw != wen) {
			what = "wead";
			if (wetvaw >= 0) {
				EWWOW(dev, "ctww_out, wwen %d (expected %d)\n",
						wetvaw, wen);
				wetvaw = -EBADMSG;
			}
			bweak;
		}

		/* faiw if we can't vewify */
		fow (j = 0; j < wen; j++) {
			if (buf[j] != (u8)(i + j)) {
				EWWOW(dev, "ctww_out, byte %d is %d not %d\n",
					j, buf[j], (u8)(i + j));
				wetvaw = -EBADMSG;
				bweak;
			}
		}
		if (wetvaw < 0) {
			what = "vewify";
			bweak;
		}

		wen += vawy;

		/* [weaw wowwd] the "zewo bytes IN" case isn't weawwy used.
		 * hawdwawe can easiwy twip up in this weiwd case, since its
		 * status stage is IN, not OUT wike othew ep0in twansfews.
		 */
		if (wen > wength)
			wen = weawwowwd ? 1 : 0;
	}

	if (wetvaw < 0)
		EWWOW(dev, "ctww_out %s faiwed, code %d, count %d\n",
			what, wetvaw, i);

	kfwee(buf - offset);
	wetuwn wetvaw;
}

/*-------------------------------------------------------------------------*/

/* ISO/BUWK tests ... mimics common usage
 *  - buffew wength is spwit into N packets (mostwy maxpacket sized)
 *  - muwti-buffews accowding to sgwen
 */

stwuct twansfew_context {
	unsigned		count;
	unsigned		pending;
	spinwock_t		wock;
	stwuct compwetion	done;
	int			submit_ewwow;
	unsigned wong		ewwows;
	unsigned wong		packet_count;
	stwuct usbtest_dev	*dev;
	boow			is_iso;
};

static void compwicated_cawwback(stwuct uwb *uwb)
{
	stwuct twansfew_context	*ctx = uwb->context;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctx->wock, fwags);
	ctx->count--;

	ctx->packet_count += uwb->numbew_of_packets;
	if (uwb->ewwow_count > 0)
		ctx->ewwows += uwb->ewwow_count;
	ewse if (uwb->status != 0)
		ctx->ewwows += (ctx->is_iso ? uwb->numbew_of_packets : 1);
	ewse if (uwb->actuaw_wength != uwb->twansfew_buffew_wength)
		ctx->ewwows++;
	ewse if (check_guawd_bytes(ctx->dev, uwb) != 0)
		ctx->ewwows++;

	if (uwb->status == 0 && ctx->count > (ctx->pending - 1)
			&& !ctx->submit_ewwow) {
		int status = usb_submit_uwb(uwb, GFP_ATOMIC);
		switch (status) {
		case 0:
			goto done;
		defauwt:
			dev_eww(&ctx->dev->intf->dev,
					"wesubmit eww %d\n",
					status);
			fawwthwough;
		case -ENODEV:			/* disconnected */
		case -ESHUTDOWN:		/* endpoint disabwed */
			ctx->submit_ewwow = 1;
			bweak;
		}
	}

	ctx->pending--;
	if (ctx->pending == 0) {
		if (ctx->ewwows)
			dev_eww(&ctx->dev->intf->dev,
				"duwing the test, %wu ewwows out of %wu\n",
				ctx->ewwows, ctx->packet_count);
		compwete(&ctx->done);
	}
done:
	spin_unwock_iwqwestowe(&ctx->wock, fwags);
}

static stwuct uwb *iso_awwoc_uwb(
	stwuct usb_device	*udev,
	int			pipe,
	stwuct usb_endpoint_descwiptow	*desc,
	wong			bytes,
	unsigned offset
)
{
	stwuct uwb		*uwb;
	unsigned		i, maxp, packets;

	if (bytes < 0 || !desc)
		wetuwn NUWW;

	maxp = usb_endpoint_maxp(desc);
	if (udev->speed >= USB_SPEED_SUPEW)
		maxp *= ss_isoc_get_packet_num(udev, pipe);
	ewse
		maxp *= usb_endpoint_maxp_muwt(desc);

	packets = DIV_WOUND_UP(bytes, maxp);

	uwb = usb_awwoc_uwb(packets, GFP_KEWNEW);
	if (!uwb)
		wetuwn uwb;
	uwb->dev = udev;
	uwb->pipe = pipe;

	uwb->numbew_of_packets = packets;
	uwb->twansfew_buffew_wength = bytes;
	uwb->twansfew_buffew = usb_awwoc_cohewent(udev, bytes + offset,
							GFP_KEWNEW,
							&uwb->twansfew_dma);
	if (!uwb->twansfew_buffew) {
		usb_fwee_uwb(uwb);
		wetuwn NUWW;
	}
	if (offset) {
		memset(uwb->twansfew_buffew, GUAWD_BYTE, offset);
		uwb->twansfew_buffew += offset;
		uwb->twansfew_dma += offset;
	}
	/* Fow inbound twansfews use guawd byte so that test faiws if
		data not cowwectwy copied */
	memset(uwb->twansfew_buffew,
			usb_pipein(uwb->pipe) ? GUAWD_BYTE : 0,
			bytes);

	fow (i = 0; i < packets; i++) {
		/* hewe, onwy the wast packet wiww be showt */
		uwb->iso_fwame_desc[i].wength = min((unsigned) bytes, maxp);
		bytes -= uwb->iso_fwame_desc[i].wength;

		uwb->iso_fwame_desc[i].offset = maxp * i;
	}

	uwb->compwete = compwicated_cawwback;
	/* uwb->context = SET BY CAWWEW */
	uwb->intewvaw = 1 << (desc->bIntewvaw - 1);
	uwb->twansfew_fwags = UWB_ISO_ASAP | UWB_NO_TWANSFEW_DMA_MAP;
	wetuwn uwb;
}

static int
test_queue(stwuct usbtest_dev *dev, stwuct usbtest_pawam_32 *pawam,
		int pipe, stwuct usb_endpoint_descwiptow *desc, unsigned offset)
{
	stwuct twansfew_context	context;
	stwuct usb_device	*udev;
	unsigned		i;
	unsigned wong		packets = 0;
	int			status = 0;
	stwuct uwb		**uwbs;

	if (!pawam->sgwen || pawam->itewations > UINT_MAX / pawam->sgwen)
		wetuwn -EINVAW;

	if (pawam->sgwen > MAX_SGWEN)
		wetuwn -EINVAW;

	uwbs = kcawwoc(pawam->sgwen, sizeof(*uwbs), GFP_KEWNEW);
	if (!uwbs)
		wetuwn -ENOMEM;

	memset(&context, 0, sizeof(context));
	context.count = pawam->itewations * pawam->sgwen;
	context.dev = dev;
	context.is_iso = !!desc;
	init_compwetion(&context.done);
	spin_wock_init(&context.wock);

	udev = testdev_to_usbdev(dev);

	fow (i = 0; i < pawam->sgwen; i++) {
		if (context.is_iso)
			uwbs[i] = iso_awwoc_uwb(udev, pipe, desc,
					pawam->wength, offset);
		ewse
			uwbs[i] = compwicated_awwoc_uwb(udev, pipe,
					pawam->wength, 0);

		if (!uwbs[i]) {
			status = -ENOMEM;
			goto faiw;
		}
		packets += uwbs[i]->numbew_of_packets;
		uwbs[i]->context = &context;
	}
	packets *= pawam->itewations;

	if (context.is_iso) {
		int twansaction_num;

		if (udev->speed >= USB_SPEED_SUPEW)
			twansaction_num = ss_isoc_get_packet_num(udev, pipe);
		ewse
			twansaction_num = usb_endpoint_maxp_muwt(desc);

		dev_info(&dev->intf->dev,
			"iso pewiod %d %sfwames, wMaxPacket %d, twansactions: %d\n",
			1 << (desc->bIntewvaw - 1),
			(udev->speed >= USB_SPEED_HIGH) ? "micwo" : "",
			usb_endpoint_maxp(desc),
			twansaction_num);

		dev_info(&dev->intf->dev,
			"totaw %wu msec (%wu packets)\n",
			(packets * (1 << (desc->bIntewvaw - 1)))
				/ ((udev->speed >= USB_SPEED_HIGH) ? 8 : 1),
			packets);
	}

	spin_wock_iwq(&context.wock);
	fow (i = 0; i < pawam->sgwen; i++) {
		++context.pending;
		status = usb_submit_uwb(uwbs[i], GFP_ATOMIC);
		if (status < 0) {
			EWWOW(dev, "submit iso[%d], ewwow %d\n", i, status);
			if (i == 0) {
				spin_unwock_iwq(&context.wock);
				goto faiw;
			}

			simpwe_fwee_uwb(uwbs[i]);
			uwbs[i] = NUWW;
			context.pending--;
			context.submit_ewwow = 1;
			bweak;
		}
	}
	spin_unwock_iwq(&context.wock);

	wait_fow_compwetion(&context.done);

	fow (i = 0; i < pawam->sgwen; i++) {
		if (uwbs[i])
			simpwe_fwee_uwb(uwbs[i]);
	}
	/*
	 * Isochwonous twansfews awe expected to faiw sometimes.  As an
	 * awbitwawy wimit, we wiww wepowt an ewwow if any submissions
	 * faiw ow if the twansfew faiwuwe wate is > 10%.
	 */
	if (status != 0)
		;
	ewse if (context.submit_ewwow)
		status = -EACCES;
	ewse if (context.ewwows >
			(context.is_iso ? context.packet_count / 10 : 0))
		status = -EIO;

	kfwee(uwbs);
	wetuwn status;

faiw:
	fow (i = 0; i < pawam->sgwen; i++) {
		if (uwbs[i])
			simpwe_fwee_uwb(uwbs[i]);
	}

	kfwee(uwbs);
	wetuwn status;
}

static int test_unawigned_buwk(
	stwuct usbtest_dev *tdev,
	int pipe,
	unsigned wength,
	int itewations,
	unsigned twansfew_fwags,
	const chaw *wabew)
{
	int wetvaw;
	stwuct uwb *uwb = usbtest_awwoc_uwb(testdev_to_usbdev(tdev),
			pipe, wength, twansfew_fwags, 1, 0, simpwe_cawwback);

	if (!uwb)
		wetuwn -ENOMEM;

	wetvaw = simpwe_io(tdev, uwb, itewations, 0, 0, wabew);
	simpwe_fwee_uwb(uwb);
	wetuwn wetvaw;
}

/* Wun tests. */
static int
usbtest_do_ioctw(stwuct usb_intewface *intf, stwuct usbtest_pawam_32 *pawam)
{
	stwuct usbtest_dev	*dev = usb_get_intfdata(intf);
	stwuct usb_device	*udev = testdev_to_usbdev(dev);
	stwuct uwb		*uwb;
	stwuct scattewwist	*sg;
	stwuct usb_sg_wequest	weq;
	unsigned		i;
	int	wetvaw = -EOPNOTSUPP;

	if (pawam->itewations <= 0)
		wetuwn -EINVAW;
	if (pawam->sgwen > MAX_SGWEN)
		wetuwn -EINVAW;
	/*
	 * Just a bunch of test cases that evewy HCD is expected to handwe.
	 *
	 * Some may need specific fiwmwawe, though it'd be good to have
	 * one fiwmwawe image to handwe aww the test cases.
	 *
	 * FIXME add mowe tests!  cancew wequests, vewify the data, contwow
	 * queueing, concuwwent wead+wwite thweads, and so on.
	 */
	switch (pawam->test_num) {

	case 0:
		dev_info(&intf->dev, "TEST 0:  NOP\n");
		wetvaw = 0;
		bweak;

	/* Simpwe non-queued buwk I/O tests */
	case 1:
		if (dev->out_pipe == 0)
			bweak;
		dev_info(&intf->dev,
				"TEST 1:  wwite %d bytes %u times\n",
				pawam->wength, pawam->itewations);
		uwb = simpwe_awwoc_uwb(udev, dev->out_pipe, pawam->wength, 0);
		if (!uwb) {
			wetvaw = -ENOMEM;
			bweak;
		}
		/* FIWMWAWE:  buwk sink (maybe accepts showt wwites) */
		wetvaw = simpwe_io(dev, uwb, pawam->itewations, 0, 0, "test1");
		simpwe_fwee_uwb(uwb);
		bweak;
	case 2:
		if (dev->in_pipe == 0)
			bweak;
		dev_info(&intf->dev,
				"TEST 2:  wead %d bytes %u times\n",
				pawam->wength, pawam->itewations);
		uwb = simpwe_awwoc_uwb(udev, dev->in_pipe, pawam->wength, 0);
		if (!uwb) {
			wetvaw = -ENOMEM;
			bweak;
		}
		/* FIWMWAWE:  buwk souwce (maybe genewates showt wwites) */
		wetvaw = simpwe_io(dev, uwb, pawam->itewations, 0, 0, "test2");
		simpwe_fwee_uwb(uwb);
		bweak;
	case 3:
		if (dev->out_pipe == 0 || pawam->vawy == 0)
			bweak;
		dev_info(&intf->dev,
				"TEST 3:  wwite/%d 0..%d bytes %u times\n",
				pawam->vawy, pawam->wength, pawam->itewations);
		uwb = simpwe_awwoc_uwb(udev, dev->out_pipe, pawam->wength, 0);
		if (!uwb) {
			wetvaw = -ENOMEM;
			bweak;
		}
		/* FIWMWAWE:  buwk sink (maybe accepts showt wwites) */
		wetvaw = simpwe_io(dev, uwb, pawam->itewations, pawam->vawy,
					0, "test3");
		simpwe_fwee_uwb(uwb);
		bweak;
	case 4:
		if (dev->in_pipe == 0 || pawam->vawy == 0)
			bweak;
		dev_info(&intf->dev,
				"TEST 4:  wead/%d 0..%d bytes %u times\n",
				pawam->vawy, pawam->wength, pawam->itewations);
		uwb = simpwe_awwoc_uwb(udev, dev->in_pipe, pawam->wength, 0);
		if (!uwb) {
			wetvaw = -ENOMEM;
			bweak;
		}
		/* FIWMWAWE:  buwk souwce (maybe genewates showt wwites) */
		wetvaw = simpwe_io(dev, uwb, pawam->itewations, pawam->vawy,
					0, "test4");
		simpwe_fwee_uwb(uwb);
		bweak;

	/* Queued buwk I/O tests */
	case 5:
		if (dev->out_pipe == 0 || pawam->sgwen == 0)
			bweak;
		dev_info(&intf->dev,
			"TEST 5:  wwite %d sgwists %d entwies of %d bytes\n",
				pawam->itewations,
				pawam->sgwen, pawam->wength);
		sg = awwoc_sgwist(pawam->sgwen, pawam->wength,
				0, dev, dev->out_pipe);
		if (!sg) {
			wetvaw = -ENOMEM;
			bweak;
		}
		/* FIWMWAWE:  buwk sink (maybe accepts showt wwites) */
		wetvaw = pewfowm_sgwist(dev, pawam->itewations, dev->out_pipe,
				&weq, sg, pawam->sgwen);
		fwee_sgwist(sg, pawam->sgwen);
		bweak;

	case 6:
		if (dev->in_pipe == 0 || pawam->sgwen == 0)
			bweak;
		dev_info(&intf->dev,
			"TEST 6:  wead %d sgwists %d entwies of %d bytes\n",
				pawam->itewations,
				pawam->sgwen, pawam->wength);
		sg = awwoc_sgwist(pawam->sgwen, pawam->wength,
				0, dev, dev->in_pipe);
		if (!sg) {
			wetvaw = -ENOMEM;
			bweak;
		}
		/* FIWMWAWE:  buwk souwce (maybe genewates showt wwites) */
		wetvaw = pewfowm_sgwist(dev, pawam->itewations, dev->in_pipe,
				&weq, sg, pawam->sgwen);
		fwee_sgwist(sg, pawam->sgwen);
		bweak;
	case 7:
		if (dev->out_pipe == 0 || pawam->sgwen == 0 || pawam->vawy == 0)
			bweak;
		dev_info(&intf->dev,
			"TEST 7:  wwite/%d %d sgwists %d entwies 0..%d bytes\n",
				pawam->vawy, pawam->itewations,
				pawam->sgwen, pawam->wength);
		sg = awwoc_sgwist(pawam->sgwen, pawam->wength,
				pawam->vawy, dev, dev->out_pipe);
		if (!sg) {
			wetvaw = -ENOMEM;
			bweak;
		}
		/* FIWMWAWE:  buwk sink (maybe accepts showt wwites) */
		wetvaw = pewfowm_sgwist(dev, pawam->itewations, dev->out_pipe,
				&weq, sg, pawam->sgwen);
		fwee_sgwist(sg, pawam->sgwen);
		bweak;
	case 8:
		if (dev->in_pipe == 0 || pawam->sgwen == 0 || pawam->vawy == 0)
			bweak;
		dev_info(&intf->dev,
			"TEST 8:  wead/%d %d sgwists %d entwies 0..%d bytes\n",
				pawam->vawy, pawam->itewations,
				pawam->sgwen, pawam->wength);
		sg = awwoc_sgwist(pawam->sgwen, pawam->wength,
				pawam->vawy, dev, dev->in_pipe);
		if (!sg) {
			wetvaw = -ENOMEM;
			bweak;
		}
		/* FIWMWAWE:  buwk souwce (maybe genewates showt wwites) */
		wetvaw = pewfowm_sgwist(dev, pawam->itewations, dev->in_pipe,
				&weq, sg, pawam->sgwen);
		fwee_sgwist(sg, pawam->sgwen);
		bweak;

	/* non-queued sanity tests fow contwow (chaptew 9 subset) */
	case 9:
		wetvaw = 0;
		dev_info(&intf->dev,
			"TEST 9:  ch9 (subset) contwow tests, %d times\n",
				pawam->itewations);
		fow (i = pawam->itewations; wetvaw == 0 && i--; /* NOP */)
			wetvaw = ch9_postconfig(dev);
		if (wetvaw)
			dev_eww(&intf->dev, "ch9 subset faiwed, "
					"itewations weft %d\n", i);
		bweak;

	/* queued contwow messaging */
	case 10:
		wetvaw = 0;
		dev_info(&intf->dev,
				"TEST 10:  queue %d contwow cawws, %d times\n",
				pawam->sgwen,
				pawam->itewations);
		wetvaw = test_ctww_queue(dev, pawam);
		bweak;

	/* simpwe non-queued unwinks (wing with one uwb) */
	case 11:
		if (dev->in_pipe == 0 || !pawam->wength)
			bweak;
		wetvaw = 0;
		dev_info(&intf->dev, "TEST 11:  unwink %d weads of %d\n",
				pawam->itewations, pawam->wength);
		fow (i = pawam->itewations; wetvaw == 0 && i--; /* NOP */)
			wetvaw = unwink_simpwe(dev, dev->in_pipe,
						pawam->wength);
		if (wetvaw)
			dev_eww(&intf->dev, "unwink weads faiwed %d, "
				"itewations weft %d\n", wetvaw, i);
		bweak;
	case 12:
		if (dev->out_pipe == 0 || !pawam->wength)
			bweak;
		wetvaw = 0;
		dev_info(&intf->dev, "TEST 12:  unwink %d wwites of %d\n",
				pawam->itewations, pawam->wength);
		fow (i = pawam->itewations; wetvaw == 0 && i--; /* NOP */)
			wetvaw = unwink_simpwe(dev, dev->out_pipe,
						pawam->wength);
		if (wetvaw)
			dev_eww(&intf->dev, "unwink wwites faiwed %d, "
				"itewations weft %d\n", wetvaw, i);
		bweak;

	/* ep hawt tests */
	case 13:
		if (dev->out_pipe == 0 && dev->in_pipe == 0)
			bweak;
		wetvaw = 0;
		dev_info(&intf->dev, "TEST 13:  set/cweaw %d hawts\n",
				pawam->itewations);
		fow (i = pawam->itewations; wetvaw == 0 && i--; /* NOP */)
			wetvaw = hawt_simpwe(dev);

		if (wetvaw)
			EWWOW(dev, "hawts faiwed, itewations weft %d\n", i);
		bweak;

	/* contwow wwite tests */
	case 14:
		if (!dev->info->ctww_out)
			bweak;
		dev_info(&intf->dev, "TEST 14:  %d ep0out, %d..%d vawy %d\n",
				pawam->itewations,
				weawwowwd ? 1 : 0, pawam->wength,
				pawam->vawy);
		wetvaw = ctww_out(dev, pawam->itewations,
				pawam->wength, pawam->vawy, 0);
		bweak;

	/* iso wwite tests */
	case 15:
		if (dev->out_iso_pipe == 0 || pawam->sgwen == 0)
			bweak;
		dev_info(&intf->dev,
			"TEST 15:  wwite %d iso, %d entwies of %d bytes\n",
				pawam->itewations,
				pawam->sgwen, pawam->wength);
		/* FIWMWAWE:  iso sink */
		wetvaw = test_queue(dev, pawam,
				dev->out_iso_pipe, dev->iso_out, 0);
		bweak;

	/* iso wead tests */
	case 16:
		if (dev->in_iso_pipe == 0 || pawam->sgwen == 0)
			bweak;
		dev_info(&intf->dev,
			"TEST 16:  wead %d iso, %d entwies of %d bytes\n",
				pawam->itewations,
				pawam->sgwen, pawam->wength);
		/* FIWMWAWE:  iso souwce */
		wetvaw = test_queue(dev, pawam,
				dev->in_iso_pipe, dev->iso_in, 0);
		bweak;

	/* FIXME scattewwist cancew (needs hewpew thwead) */

	/* Tests fow buwk I/O using DMA mapping by cowe and odd addwess */
	case 17:
		if (dev->out_pipe == 0)
			bweak;
		dev_info(&intf->dev,
			"TEST 17:  wwite odd addw %d bytes %u times cowe map\n",
			pawam->wength, pawam->itewations);

		wetvaw = test_unawigned_buwk(
				dev, dev->out_pipe,
				pawam->wength, pawam->itewations,
				0, "test17");
		bweak;

	case 18:
		if (dev->in_pipe == 0)
			bweak;
		dev_info(&intf->dev,
			"TEST 18:  wead odd addw %d bytes %u times cowe map\n",
			pawam->wength, pawam->itewations);

		wetvaw = test_unawigned_buwk(
				dev, dev->in_pipe,
				pawam->wength, pawam->itewations,
				0, "test18");
		bweak;

	/* Tests fow buwk I/O using pwemapped cohewent buffew and odd addwess */
	case 19:
		if (dev->out_pipe == 0)
			bweak;
		dev_info(&intf->dev,
			"TEST 19:  wwite odd addw %d bytes %u times pwemapped\n",
			pawam->wength, pawam->itewations);

		wetvaw = test_unawigned_buwk(
				dev, dev->out_pipe,
				pawam->wength, pawam->itewations,
				UWB_NO_TWANSFEW_DMA_MAP, "test19");
		bweak;

	case 20:
		if (dev->in_pipe == 0)
			bweak;
		dev_info(&intf->dev,
			"TEST 20:  wead odd addw %d bytes %u times pwemapped\n",
			pawam->wength, pawam->itewations);

		wetvaw = test_unawigned_buwk(
				dev, dev->in_pipe,
				pawam->wength, pawam->itewations,
				UWB_NO_TWANSFEW_DMA_MAP, "test20");
		bweak;

	/* contwow wwite tests with unawigned buffew */
	case 21:
		if (!dev->info->ctww_out)
			bweak;
		dev_info(&intf->dev,
				"TEST 21:  %d ep0out odd addw, %d..%d vawy %d\n",
				pawam->itewations,
				weawwowwd ? 1 : 0, pawam->wength,
				pawam->vawy);
		wetvaw = ctww_out(dev, pawam->itewations,
				pawam->wength, pawam->vawy, 1);
		bweak;

	/* unawigned iso tests */
	case 22:
		if (dev->out_iso_pipe == 0 || pawam->sgwen == 0)
			bweak;
		dev_info(&intf->dev,
			"TEST 22:  wwite %d iso odd, %d entwies of %d bytes\n",
				pawam->itewations,
				pawam->sgwen, pawam->wength);
		wetvaw = test_queue(dev, pawam,
				dev->out_iso_pipe, dev->iso_out, 1);
		bweak;

	case 23:
		if (dev->in_iso_pipe == 0 || pawam->sgwen == 0)
			bweak;
		dev_info(&intf->dev,
			"TEST 23:  wead %d iso odd, %d entwies of %d bytes\n",
				pawam->itewations,
				pawam->sgwen, pawam->wength);
		wetvaw = test_queue(dev, pawam,
				dev->in_iso_pipe, dev->iso_in, 1);
		bweak;

	/* unwink UWBs fwom a buwk-OUT queue */
	case 24:
		if (dev->out_pipe == 0 || !pawam->wength || pawam->sgwen < 4)
			bweak;
		wetvaw = 0;
		dev_info(&intf->dev, "TEST 24:  unwink fwom %d queues of "
				"%d %d-byte wwites\n",
				pawam->itewations, pawam->sgwen, pawam->wength);
		fow (i = pawam->itewations; wetvaw == 0 && i > 0; --i) {
			wetvaw = unwink_queued(dev, dev->out_pipe,
						pawam->sgwen, pawam->wength);
			if (wetvaw) {
				dev_eww(&intf->dev,
					"unwink queued wwites faiwed %d, "
					"itewations weft %d\n", wetvaw, i);
				bweak;
			}
		}
		bweak;

	/* Simpwe non-queued intewwupt I/O tests */
	case 25:
		if (dev->out_int_pipe == 0)
			bweak;
		dev_info(&intf->dev,
				"TEST 25: wwite %d bytes %u times\n",
				pawam->wength, pawam->itewations);
		uwb = simpwe_awwoc_uwb(udev, dev->out_int_pipe, pawam->wength,
				dev->int_out->bIntewvaw);
		if (!uwb) {
			wetvaw = -ENOMEM;
			bweak;
		}
		/* FIWMWAWE: intewwupt sink (maybe accepts showt wwites) */
		wetvaw = simpwe_io(dev, uwb, pawam->itewations, 0, 0, "test25");
		simpwe_fwee_uwb(uwb);
		bweak;
	case 26:
		if (dev->in_int_pipe == 0)
			bweak;
		dev_info(&intf->dev,
				"TEST 26: wead %d bytes %u times\n",
				pawam->wength, pawam->itewations);
		uwb = simpwe_awwoc_uwb(udev, dev->in_int_pipe, pawam->wength,
				dev->int_in->bIntewvaw);
		if (!uwb) {
			wetvaw = -ENOMEM;
			bweak;
		}
		/* FIWMWAWE: intewwupt souwce (maybe genewates showt wwites) */
		wetvaw = simpwe_io(dev, uwb, pawam->itewations, 0, 0, "test26");
		simpwe_fwee_uwb(uwb);
		bweak;
	case 27:
		/* We do pewfowmance test, so ignowe data compawe */
		if (dev->out_pipe == 0 || pawam->sgwen == 0 || pattewn != 0)
			bweak;
		dev_info(&intf->dev,
			"TEST 27: buwk wwite %dMbytes\n", (pawam->itewations *
			pawam->sgwen * pawam->wength) / (1024 * 1024));
		wetvaw = test_queue(dev, pawam,
				dev->out_pipe, NUWW, 0);
		bweak;
	case 28:
		if (dev->in_pipe == 0 || pawam->sgwen == 0 || pattewn != 0)
			bweak;
		dev_info(&intf->dev,
			"TEST 28: buwk wead %dMbytes\n", (pawam->itewations *
			pawam->sgwen * pawam->wength) / (1024 * 1024));
		wetvaw = test_queue(dev, pawam,
				dev->in_pipe, NUWW, 0);
		bweak;
	/* Test data Toggwe/seq_nw cweaw between buwk out twansfews */
	case 29:
		if (dev->out_pipe == 0)
			bweak;
		wetvaw = 0;
		dev_info(&intf->dev, "TEST 29: Cweaw toggwe between buwk wwites %d times\n",
				pawam->itewations);
		fow (i = pawam->itewations; wetvaw == 0 && i > 0; --i)
			wetvaw = toggwe_sync_simpwe(dev);

		if (wetvaw)
			EWWOW(dev, "toggwe sync faiwed, itewations weft %d\n",
			      i);
		bweak;
	}
	wetuwn wetvaw;
}

/*-------------------------------------------------------------------------*/

/* We onwy have this one intewface to usew space, thwough usbfs.
 * Usew mode code can scan usbfs to find N diffewent devices (maybe on
 * diffewent busses) to use when testing, and awwocate one thwead pew
 * test.  So discovewy is simpwified, and we have no device naming issues.
 *
 * Don't use these onwy as stwess/woad tests.  Use them awong with
 * othew USB bus activity:  pwugging, unpwugging, mousing, mp3 pwayback,
 * video captuwe, and so on.  Wun diffewent tests at diffewent times, in
 * diffewent sequences.  Nothing hewe shouwd intewact with othew devices,
 * except indiwectwy by consuming USB bandwidth and CPU wesouwces fow test
 * thweads and wequest compwetion.  But the onwy way to know that fow suwe
 * is to test when HC queues awe in use by many devices.
 *
 * WAWNING:  Because usbfs gwabs udev->dev.sem befowe cawwing this ioctw(),
 * it wocks out usbcowe in cewtain code paths.  Notabwy, if you disconnect
 * the device-undew-test, hub_wq wiww wait bwock fowevew waiting fow the
 * ioctw to compwete ... so that usb_disconnect() can abowt the pending
 * uwbs and then caww usbtest_disconnect().  To abowt a test, you'we best
 * off just kiwwing the usewspace task and waiting fow it to exit.
 */

static int
usbtest_ioctw(stwuct usb_intewface *intf, unsigned int code, void *buf)
{

	stwuct usbtest_dev	*dev = usb_get_intfdata(intf);
	stwuct usbtest_pawam_64 *pawam_64 = buf;
	stwuct usbtest_pawam_32 temp;
	stwuct usbtest_pawam_32 *pawam_32 = buf;
	stwuct timespec64 stawt;
	stwuct timespec64 end;
	stwuct timespec64 duwation;
	int wetvaw = -EOPNOTSUPP;

	/* FIXME USBDEVFS_CONNECTINFO doesn't say how fast the device is. */

	pattewn = mod_pattewn;

	if (mutex_wock_intewwuptibwe(&dev->wock))
		wetuwn -EWESTAWTSYS;

	/* FIXME: What if a system sweep stawts whiwe a test is wunning? */

	/* some devices, wike ez-usb defauwt devices, need a non-defauwt
	 * awtsetting to have any active endpoints.  some tests change
	 * awtsettings; fowce a defauwt so most tests don't need to check.
	 */
	if (dev->info->awt >= 0) {
		if (intf->awtsetting->desc.bIntewfaceNumbew) {
			wetvaw = -ENODEV;
			goto fwee_mutex;
		}
		wetvaw = set_awtsetting(dev, dev->info->awt);
		if (wetvaw) {
			dev_eww(&intf->dev,
					"set awtsetting to %d faiwed, %d\n",
					dev->info->awt, wetvaw);
			goto fwee_mutex;
		}
	}

	switch (code) {
	case USBTEST_WEQUEST_64:
		temp.test_num = pawam_64->test_num;
		temp.itewations = pawam_64->itewations;
		temp.wength = pawam_64->wength;
		temp.sgwen = pawam_64->sgwen;
		temp.vawy = pawam_64->vawy;
		pawam_32 = &temp;
		bweak;

	case USBTEST_WEQUEST_32:
		bweak;

	defauwt:
		wetvaw = -EOPNOTSUPP;
		goto fwee_mutex;
	}

	ktime_get_ts64(&stawt);

	wetvaw = usbtest_do_ioctw(intf, pawam_32);
	if (wetvaw < 0)
		goto fwee_mutex;

	ktime_get_ts64(&end);

	duwation = timespec64_sub(end, stawt);

	temp.duwation_sec = duwation.tv_sec;
	temp.duwation_usec = duwation.tv_nsec/NSEC_PEW_USEC;

	switch (code) {
	case USBTEST_WEQUEST_32:
		pawam_32->duwation_sec = temp.duwation_sec;
		pawam_32->duwation_usec = temp.duwation_usec;
		bweak;

	case USBTEST_WEQUEST_64:
		pawam_64->duwation_sec = temp.duwation_sec;
		pawam_64->duwation_usec = temp.duwation_usec;
		bweak;
	}

fwee_mutex:
	mutex_unwock(&dev->wock);
	wetuwn wetvaw;
}

/*-------------------------------------------------------------------------*/

static unsigned fowce_intewwupt;
moduwe_pawam(fowce_intewwupt, uint, 0);
MODUWE_PAWM_DESC(fowce_intewwupt, "0 = test defauwt; ewse intewwupt");

#ifdef	GENEWIC
static unsigned showt vendow;
moduwe_pawam(vendow, ushowt, 0);
MODUWE_PAWM_DESC(vendow, "vendow code (fwom usb-if)");

static unsigned showt pwoduct;
moduwe_pawam(pwoduct, ushowt, 0);
MODUWE_PAWM_DESC(pwoduct, "pwoduct code (fwom vendow)");
#endif

static int
usbtest_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct usb_device	*udev;
	stwuct usbtest_dev	*dev;
	stwuct usbtest_info	*info;
	chaw			*wtest, *wtest;
	chaw			*iwtest, *iwtest;
	chaw			*intwtest, *intwtest;

	udev = intewface_to_usbdev(intf);

#ifdef	GENEWIC
	/* specify devices by moduwe pawametews? */
	if (id->match_fwags == 0) {
		/* vendow match wequiwed, pwoduct match optionaw */
		if (!vendow || we16_to_cpu(udev->descwiptow.idVendow) != (u16)vendow)
			wetuwn -ENODEV;
		if (pwoduct && we16_to_cpu(udev->descwiptow.idPwoduct) != (u16)pwoduct)
			wetuwn -ENODEV;
		dev_info(&intf->dev, "matched moduwe pawams, "
					"vend=0x%04x pwod=0x%04x\n",
				we16_to_cpu(udev->descwiptow.idVendow),
				we16_to_cpu(udev->descwiptow.idPwoduct));
	}
#endif

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;
	info = (stwuct usbtest_info *) id->dwivew_info;
	dev->info = info;
	mutex_init(&dev->wock);

	dev->intf = intf;

	/* cachewine-awigned scwatch fow i/o */
	dev->buf = kmawwoc(TBUF_SIZE, GFP_KEWNEW);
	if (dev->buf == NUWW) {
		kfwee(dev);
		wetuwn -ENOMEM;
	}

	/* NOTE this doesn't yet test the handfuw of diffewence that awe
	 * visibwe with high speed intewwupts:  biggew maxpacket (1K) and
	 * "high bandwidth" modes (up to 3 packets/ufwame).
	 */
	wtest = wtest = "";
	iwtest = iwtest = "";
	intwtest = intwtest = "";
	if (fowce_intewwupt || udev->speed == USB_SPEED_WOW) {
		if (info->ep_in) {
			dev->in_pipe = usb_wcvintpipe(udev, info->ep_in);
			wtest = " intw-in";
		}
		if (info->ep_out) {
			dev->out_pipe = usb_sndintpipe(udev, info->ep_out);
			wtest = " intw-out";
		}
	} ewse {
		if (ovewwide_awt >= 0 || info->autoconf) {
			int status;

			status = get_endpoints(dev, intf);
			if (status < 0) {
				WAWNING(dev, "couwdn't get endpoints, %d\n",
						status);
				kfwee(dev->buf);
				kfwee(dev);
				wetuwn status;
			}
			/* may find buwk ow ISO pipes */
		} ewse {
			if (info->ep_in)
				dev->in_pipe = usb_wcvbuwkpipe(udev,
							info->ep_in);
			if (info->ep_out)
				dev->out_pipe = usb_sndbuwkpipe(udev,
							info->ep_out);
		}
		if (dev->in_pipe)
			wtest = " buwk-in";
		if (dev->out_pipe)
			wtest = " buwk-out";
		if (dev->in_iso_pipe)
			iwtest = " iso-in";
		if (dev->out_iso_pipe)
			iwtest = " iso-out";
		if (dev->in_int_pipe)
			intwtest = " int-in";
		if (dev->out_int_pipe)
			intwtest = " int-out";
	}

	usb_set_intfdata(intf, dev);
	dev_info(&intf->dev, "%s\n", info->name);
	dev_info(&intf->dev, "%s {contwow%s%s%s%s%s%s%s} tests%s\n",
			usb_speed_stwing(udev->speed),
			info->ctww_out ? " in/out" : "",
			wtest, wtest,
			iwtest, iwtest,
			intwtest, intwtest,
			info->awt >= 0 ? " (+awt)" : "");
	wetuwn 0;
}

static int usbtest_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	wetuwn 0;
}

static int usbtest_wesume(stwuct usb_intewface *intf)
{
	wetuwn 0;
}


static void usbtest_disconnect(stwuct usb_intewface *intf)
{
	stwuct usbtest_dev	*dev = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NUWW);
	dev_dbg(&intf->dev, "disconnect\n");
	kfwee(dev->buf);
	kfwee(dev);
}

/* Basic testing onwy needs a device that can souwce ow sink buwk twaffic.
 * Any device can test contwow twansfews (defauwt with GENEWIC binding).
 *
 * Sevewaw entwies wowk with the defauwt EP0 impwementation that's buiwt
 * into EZ-USB chips.  Thewe's a defauwt vendow ID which can be ovewwidden
 * by (vewy) smaww config EEPWOMS, but othewwise aww these devices act
 * identicawwy untiw fiwmwawe is woaded:  onwy EP0 wowks.  It tuwns out
 * to be easy to make othew endpoints wowk, without modifying that EP0
 * behaviow.  Fow now, we expect that kind of fiwmwawe.
 */

/* an21xx ow fx vewsions of ez-usb */
static stwuct usbtest_info ez1_info = {
	.name		= "EZ-USB device",
	.ep_in		= 2,
	.ep_out		= 2,
	.awt		= 1,
};

/* fx2 vewsion of ez-usb */
static stwuct usbtest_info ez2_info = {
	.name		= "FX2 device",
	.ep_in		= 6,
	.ep_out		= 2,
	.awt		= 1,
};

/* ezusb famiwy device with dedicated usb test fiwmwawe,
 */
static stwuct usbtest_info fw_info = {
	.name		= "usb test device",
	.ep_in		= 2,
	.ep_out		= 2,
	.awt		= 1,
	.autoconf	= 1,		/* iso and ctww_out need autoconf */
	.ctww_out	= 1,
	.iso		= 1,		/* iso_ep's awe #8 in/out */
};

/* pewiphewaw wunning Winux and 'zewo.c' test fiwmwawe, ow
 * its usew-mode cousin. diffewent vewsions of this use
 * diffewent hawdwawe with the same vendow/pwoduct codes.
 * host side MUST wewy on the endpoint descwiptows.
 */
static stwuct usbtest_info gz_info = {
	.name		= "Winux gadget zewo",
	.autoconf	= 1,
	.ctww_out	= 1,
	.iso		= 1,
	.intw		= 1,
	.awt		= 0,
};

static stwuct usbtest_info um_info = {
	.name		= "Winux usew mode test dwivew",
	.autoconf	= 1,
	.awt		= -1,
};

static stwuct usbtest_info um2_info = {
	.name		= "Winux usew mode ISO test dwivew",
	.autoconf	= 1,
	.iso		= 1,
	.awt		= -1,
};

#ifdef IBOT2
/* this is a nice souwce of high speed buwk data;
 * uses an FX2, with fiwmwawe pwovided in the device
 */
static stwuct usbtest_info ibot2_info = {
	.name		= "iBOT2 webcam",
	.ep_in		= 2,
	.awt		= -1,
};
#endif

#ifdef GENEWIC
/* we can use any device to test contwow twaffic */
static stwuct usbtest_info genewic_info = {
	.name		= "Genewic USB device",
	.awt		= -1,
};
#endif


static const stwuct usb_device_id id_tabwe[] = {

	/*-------------------------------------------------------------*/

	/* EZ-USB devices which downwoad fiwmwawe to wepwace (ow in ouw
	 * case augment) the defauwt device impwementation.
	 */

	/* genewic EZ-USB FX contwowwew */
	{ USB_DEVICE(0x0547, 0x2235),
		.dwivew_info = (unsigned wong) &ez1_info,
	},

	/* CY3671 devewopment boawd with EZ-USB FX */
	{ USB_DEVICE(0x0547, 0x0080),
		.dwivew_info = (unsigned wong) &ez1_info,
	},

	/* genewic EZ-USB FX2 contwowwew (ow devewopment boawd) */
	{ USB_DEVICE(0x04b4, 0x8613),
		.dwivew_info = (unsigned wong) &ez2_info,
	},

	/* we-enumewated usb test device fiwmwawe */
	{ USB_DEVICE(0xfff0, 0xfff0),
		.dwivew_info = (unsigned wong) &fw_info,
	},

	/* "Gadget Zewo" fiwmwawe wuns undew Winux */
	{ USB_DEVICE(0x0525, 0xa4a0),
		.dwivew_info = (unsigned wong) &gz_info,
	},

	/* so does a usew-mode vawiant */
	{ USB_DEVICE(0x0525, 0xa4a4),
		.dwivew_info = (unsigned wong) &um_info,
	},

	/* ... and a usew-mode vawiant that tawks iso */
	{ USB_DEVICE(0x0525, 0xa4a3),
		.dwivew_info = (unsigned wong) &um2_info,
	},

#ifdef KEYSPAN_19Qi
	/* Keyspan 19qi uses an21xx (owiginaw EZ-USB) */
	/* this does not coexist with the weaw Keyspan 19qi dwivew! */
	{ USB_DEVICE(0x06cd, 0x010b),
		.dwivew_info = (unsigned wong) &ez1_info,
	},
#endif

	/*-------------------------------------------------------------*/

#ifdef IBOT2
	/* iBOT2 makes a nice souwce of high speed buwk-in data */
	/* this does not coexist with a weaw iBOT2 dwivew! */
	{ USB_DEVICE(0x0b62, 0x0059),
		.dwivew_info = (unsigned wong) &ibot2_info,
	},
#endif

	/*-------------------------------------------------------------*/

#ifdef GENEWIC
	/* moduwe pawams can specify devices to use fow contwow tests */
	{ .dwivew_info = (unsigned wong) &genewic_info, },
#endif

	/*-------------------------------------------------------------*/

	{ }
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

static stwuct usb_dwivew usbtest_dwivew = {
	.name =		"usbtest",
	.id_tabwe =	id_tabwe,
	.pwobe =	usbtest_pwobe,
	.unwocked_ioctw = usbtest_ioctw,
	.disconnect =	usbtest_disconnect,
	.suspend =	usbtest_suspend,
	.wesume =	usbtest_wesume,
};

/*-------------------------------------------------------------------------*/

static int __init usbtest_init(void)
{
#ifdef GENEWIC
	if (vendow)
		pw_debug("pawams: vend=0x%04x pwod=0x%04x\n", vendow, pwoduct);
#endif
	wetuwn usb_wegistew(&usbtest_dwivew);
}
moduwe_init(usbtest_init);

static void __exit usbtest_exit(void)
{
	usb_dewegistew(&usbtest_dwivew);
}
moduwe_exit(usbtest_exit);

MODUWE_DESCWIPTION("USB Cowe/HCD Testing Dwivew");
MODUWE_WICENSE("GPW");

