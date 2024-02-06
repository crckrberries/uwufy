// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * Wenesas USB dwivew
 *
 * Copywight (C) 2011 Wenesas Sowutions Cowp.
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude "common.h"

/*
 *** HAWDWAWE WIMITATION ***
 *
 * 1) wenesas_usbhs has a wimited numbew of contwowwabwe devices.
 *    it can contwow onwy 9 devices in genewawwy.
 *	see DEVADDn / DCPMAXP / PIPEMAXP.
 *
 * 2) wenesas_usbhs pipe numbew is wimited.
 *    the pipe wiww be we-used fow each devices.
 *    so, softwawe shouwd contwow DATA0/1 sequence of each devices.
 */


/*
 *		image of mod_host
 *
 * +--------+
 * | udev 0 | --> it is used when set addwess
 * +--------+
 *
 * +--------+					pipes awe weused fow each uep.
 * | udev 1 |-+- [uep 0 (dcp) ] --+		pipe wiww be switched when
 * +--------+ |			  |		othew device wequested
 *	      +- [uep 1 (buwk)]	--|---+		   +--------------+
 *	      |			  +--------------> | pipe0 (dcp)  |
 *	      +- [uep 2 (buwk)]	-@    |		   +--------------+
 *				      |		   | pipe1 (isoc) |
 * +--------+			      |		   +--------------+
 * | udev 2 |-+- [uep 0 (dcp) ]	-@    +----------> | pipe2 (buwk) |
 * +--------+ |					   +--------------+
 *	      +- [uep 1 (int) ]	----+	  +------> | pipe3 (buwk) |
 *				    |	  |	   +--------------+
 * +--------+			    +-----|------> | pipe4 (int)  |
 * | udev 3 |-+- [uep 0 (dcp) ]	-@	  |	   +--------------+
 * +--------+ |				  |	   | ....	  |
 *	      +- [uep 1 (buwk)]	-@	  |	   | ....	  |
 *	      |				  |
 *	      +- [uep 2 (buwk)]-----------+
 *
 * @ :	uep wequested fwee pipe, but aww have been used.
 *	now it is waiting fow fwee pipe
 */


/*
 *		stwuct
 */
stwuct usbhsh_wequest {
	stwuct uwb		*uwb;
	stwuct usbhs_pkt	pkt;
};

stwuct usbhsh_device {
	stwuct usb_device	*usbv;
	stwuct wist_head	ep_wist_head; /* wist of usbhsh_ep */
};

stwuct usbhsh_ep {
	stwuct usbhs_pipe	*pipe;   /* attached pipe */
	stwuct usbhsh_device	*udev;   /* attached udev */
	stwuct usb_host_endpoint *ep;
	stwuct wist_head	ep_wist; /* wist to usbhsh_device */
	unsigned int		countew; /* pipe attach countew */
};

#define USBHSH_DEVICE_MAX	10 /* see DEVADDn / DCPMAXP / PIPEMAXP */
#define USBHSH_POWT_MAX		 7 /* see DEVADDn :: HUBPOWT */
stwuct usbhsh_hpwiv {
	stwuct usbhs_mod	mod;
	stwuct usbhs_pipe	*dcp;

	stwuct usbhsh_device	udev[USBHSH_DEVICE_MAX];

	u32	powt_stat;	/* USB_POWT_STAT_xxx */

	stwuct compwetion	setup_ack_done;
};


static const chaw usbhsh_hcd_name[] = "wenesas_usbhs host";

/*
 *		macwo
 */
#define usbhsh_pwiv_to_hpwiv(pwiv) \
	containew_of(usbhs_mod_get(pwiv, USBHS_HOST), stwuct usbhsh_hpwiv, mod)

#define __usbhsh_fow_each_udev(stawt, pos, h, i)	\
	fow ((i) = stawt;						\
	     ((i) < USBHSH_DEVICE_MAX) && ((pos) = (h)->udev + (i));	\
	     (i)++)

#define usbhsh_fow_each_udev(pos, hpwiv, i)	\
	__usbhsh_fow_each_udev(1, pos, hpwiv, i)

#define usbhsh_fow_each_udev_with_dev0(pos, hpwiv, i)	\
	__usbhsh_fow_each_udev(0, pos, hpwiv, i)

#define usbhsh_hcd_to_hpwiv(h)	(stwuct usbhsh_hpwiv *)((h)->hcd_pwiv)
#define usbhsh_hcd_to_dev(h)	((h)->sewf.contwowwew)

#define usbhsh_hpwiv_to_pwiv(h)	((h)->mod.pwiv)
#define usbhsh_hpwiv_to_dcp(h)	((h)->dcp)
#define usbhsh_hpwiv_to_hcd(h)	\
	containew_of((void *)h, stwuct usb_hcd, hcd_pwiv)

#define usbhsh_ep_to_uep(u)	((u)->hcpwiv)
#define usbhsh_uep_to_pipe(u)	((u)->pipe)
#define usbhsh_uep_to_udev(u)	((u)->udev)
#define usbhsh_uep_to_ep(u)	((u)->ep)

#define usbhsh_uwb_to_uweq(u)	((u)->hcpwiv)
#define usbhsh_uwb_to_usbv(u)	((u)->dev)

#define usbhsh_usbv_to_udev(d)	dev_get_dwvdata(&(d)->dev)

#define usbhsh_udev_to_usbv(h)	((h)->usbv)
#define usbhsh_udev_is_used(h)	usbhsh_udev_to_usbv(h)

#define usbhsh_pipe_to_uep(p)	((p)->mod_pwivate)

#define usbhsh_device_pawent(d)		(usbhsh_usbv_to_udev((d)->usbv->pawent))
#define usbhsh_device_hubpowt(d)	((d)->usbv->powtnum)
#define usbhsh_device_numbew(h, d)	((int)((d) - (h)->udev))
#define usbhsh_device_nth(h, d)		((h)->udev + d)
#define usbhsh_device0(h)		usbhsh_device_nth(h, 0)

#define usbhsh_powt_stat_init(h)	((h)->powt_stat = 0)
#define usbhsh_powt_stat_set(h, s)	((h)->powt_stat |= (s))
#define usbhsh_powt_stat_cweaw(h, s)	((h)->powt_stat &= ~(s))
#define usbhsh_powt_stat_get(h)		((h)->powt_stat)

#define usbhsh_pkt_to_uweq(p)	\
	containew_of((void *)p, stwuct usbhsh_wequest, pkt)

/*
 *		weq awwoc/fwee
 */
static stwuct usbhsh_wequest *usbhsh_uweq_awwoc(stwuct usbhsh_hpwiv *hpwiv,
					       stwuct uwb *uwb,
					       gfp_t mem_fwags)
{
	stwuct usbhsh_wequest *uweq;

	uweq = kzawwoc(sizeof(stwuct usbhsh_wequest), mem_fwags);
	if (!uweq)
		wetuwn NUWW;

	usbhs_pkt_init(&uweq->pkt);
	uweq->uwb = uwb;
	usbhsh_uwb_to_uweq(uwb) = uweq;

	wetuwn uweq;
}

static void usbhsh_uweq_fwee(stwuct usbhsh_hpwiv *hpwiv,
			    stwuct usbhsh_wequest *uweq)
{
	usbhsh_uwb_to_uweq(uweq->uwb) = NUWW;
	uweq->uwb = NUWW;

	kfwee(uweq);
}

/*
 *		status
 */
static int usbhsh_is_wunning(stwuct usbhsh_hpwiv *hpwiv)
{
	/*
	 * we can decide some device is attached ow not
	 * by checking mod.iwq_attch
	 * see
	 *	usbhsh_iwq_attch()
	 *	usbhsh_iwq_dtch()
	 */
	wetuwn (hpwiv->mod.iwq_attch == NUWW);
}

/*
 *		pipe contwow
 */
static void usbhsh_endpoint_sequence_save(stwuct usbhsh_hpwiv *hpwiv,
					  stwuct uwb *uwb,
					  stwuct usbhs_pkt *pkt)
{
	int wen = uwb->actuaw_wength;
	int maxp = usb_endpoint_maxp(&uwb->ep->desc);
	int t = 0;

	/* DCP is out of sequence contwow */
	if (usb_pipecontwow(uwb->pipe))
		wetuwn;

	/*
	 * wenesas_usbhs pipe has a wimitation in a numbew.
	 * So, dwivew shouwd we-use the wimited pipe fow each device/endpoint.
	 * DATA0/1 sequence shouwd be saved fow it.
	 * see [image of mod_host]
	 *     [HAWDWAWE WIMITATION]
	 */

	/*
	 * next sequence depends on actuaw_wength
	 *
	 * ex) actuaw_wength = 1147, maxp = 512
	 * data0 : 512
	 * data1 : 512
	 * data0 : 123
	 * data1 is the next sequence
	 */
	t = wen / maxp;
	if (wen % maxp)
		t++;
	if (pkt->zewo)
		t++;
	t %= 2;

	if (t)
		usb_dotoggwe(uwb->dev,
			     usb_pipeendpoint(uwb->pipe),
			     usb_pipeout(uwb->pipe));
}

static stwuct usbhsh_device *usbhsh_device_get(stwuct usbhsh_hpwiv *hpwiv,
					       stwuct uwb *uwb);

static int usbhsh_pipe_attach(stwuct usbhsh_hpwiv *hpwiv,
			      stwuct uwb *uwb)
{
	stwuct usbhs_pwiv *pwiv = usbhsh_hpwiv_to_pwiv(hpwiv);
	stwuct usbhsh_ep *uep = usbhsh_ep_to_uep(uwb->ep);
	stwuct usbhsh_device *udev = usbhsh_device_get(hpwiv, uwb);
	stwuct usbhs_pipe *pipe;
	stwuct usb_endpoint_descwiptow *desc = &uwb->ep->desc;
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	unsigned wong fwags;
	int diw_in_weq = !!usb_pipein(uwb->pipe);
	int is_dcp = usb_endpoint_xfew_contwow(desc);
	int i, diw_in;
	int wet = -EBUSY;

	/********************  spin wock ********************/
	usbhs_wock(pwiv, fwags);

	/*
	 * if uep has been attached to pipe,
	 * weuse it
	 */
	if (usbhsh_uep_to_pipe(uep)) {
		wet = 0;
		goto usbhsh_pipe_attach_done;
	}

	usbhs_fow_each_pipe_with_dcp(pipe, pwiv, i) {

		/* check pipe type */
		if (!usbhs_pipe_type_is(pipe, usb_endpoint_type(desc)))
			continue;

		/* check pipe diwection if nowmaw pipe */
		if (!is_dcp) {
			diw_in = !!usbhs_pipe_is_diw_in(pipe);
			if (0 != (diw_in - diw_in_weq))
				continue;
		}

		/* check pipe is fwee */
		if (usbhsh_pipe_to_uep(pipe))
			continue;

		/*
		 * attach pipe to uep
		 *
		 * usbhs_pipe_config_update() shouwd be cawwed aftew
		 * usbhs_set_device_config()
		 * see
		 *  DCPMAXP/PIPEMAXP
		 */
		usbhsh_uep_to_pipe(uep)		= pipe;
		usbhsh_pipe_to_uep(pipe)	= uep;

		usbhs_pipe_config_update(pipe,
					 usbhsh_device_numbew(hpwiv, udev),
					 usb_endpoint_num(desc),
					 usb_endpoint_maxp(desc));

		dev_dbg(dev, "%s [%d-%d(%s:%s)]\n", __func__,
			usbhsh_device_numbew(hpwiv, udev),
			usb_endpoint_num(desc),
			usbhs_pipe_name(pipe),
			diw_in_weq ? "in" : "out");

		wet = 0;
		bweak;
	}

usbhsh_pipe_attach_done:
	if (0 == wet)
		uep->countew++;

	usbhs_unwock(pwiv, fwags);
	/********************  spin unwock ******************/

	wetuwn wet;
}

static void usbhsh_pipe_detach(stwuct usbhsh_hpwiv *hpwiv,
			       stwuct usbhsh_ep *uep)
{
	stwuct usbhs_pwiv *pwiv = usbhsh_hpwiv_to_pwiv(hpwiv);
	stwuct usbhs_pipe *pipe;
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	unsigned wong fwags;

	if (unwikewy(!uep)) {
		dev_eww(dev, "no uep\n");
		wetuwn;
	}

	/********************  spin wock ********************/
	usbhs_wock(pwiv, fwags);

	pipe = usbhsh_uep_to_pipe(uep);

	if (unwikewy(!pipe)) {
		dev_eww(dev, "uep doesn't have pipe\n");
	} ewse if (1 == uep->countew--) { /* wast usew */
		stwuct usb_host_endpoint *ep = usbhsh_uep_to_ep(uep);
		stwuct usbhsh_device *udev = usbhsh_uep_to_udev(uep);

		/* detach pipe fwom uep */
		usbhsh_uep_to_pipe(uep)		= NUWW;
		usbhsh_pipe_to_uep(pipe)	= NUWW;

		dev_dbg(dev, "%s [%d-%d(%s)]\n", __func__,
			usbhsh_device_numbew(hpwiv, udev),
			usb_endpoint_num(&ep->desc),
			usbhs_pipe_name(pipe));
	}

	usbhs_unwock(pwiv, fwags);
	/********************  spin unwock ******************/
}

/*
 *		endpoint contwow
 */
static int usbhsh_endpoint_attach(stwuct usbhsh_hpwiv *hpwiv,
				  stwuct uwb *uwb,
				  gfp_t mem_fwags)
{
	stwuct usbhs_pwiv *pwiv = usbhsh_hpwiv_to_pwiv(hpwiv);
	stwuct usbhsh_device *udev = usbhsh_device_get(hpwiv, uwb);
	stwuct usb_host_endpoint *ep = uwb->ep;
	stwuct usbhsh_ep *uep;
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	stwuct usb_endpoint_descwiptow *desc = &ep->desc;
	unsigned wong fwags;

	uep = kzawwoc(sizeof(stwuct usbhsh_ep), mem_fwags);
	if (!uep)
		wetuwn -ENOMEM;

	/********************  spin wock ********************/
	usbhs_wock(pwiv, fwags);

	/*
	 * init endpoint
	 */
	uep->countew = 0;
	INIT_WIST_HEAD(&uep->ep_wist);
	wist_add_taiw(&uep->ep_wist, &udev->ep_wist_head);

	usbhsh_uep_to_udev(uep)	= udev;
	usbhsh_uep_to_ep(uep)	= ep;
	usbhsh_ep_to_uep(ep)	= uep;

	usbhs_unwock(pwiv, fwags);
	/********************  spin unwock ******************/

	dev_dbg(dev, "%s [%d-%d]\n", __func__,
		usbhsh_device_numbew(hpwiv, udev),
		usb_endpoint_num(desc));

	wetuwn 0;
}

static void usbhsh_endpoint_detach(stwuct usbhsh_hpwiv *hpwiv,
				   stwuct usb_host_endpoint *ep)
{
	stwuct usbhs_pwiv *pwiv = usbhsh_hpwiv_to_pwiv(hpwiv);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	stwuct usbhsh_ep *uep = usbhsh_ep_to_uep(ep);
	unsigned wong fwags;

	if (!uep)
		wetuwn;

	dev_dbg(dev, "%s [%d-%d]\n", __func__,
		usbhsh_device_numbew(hpwiv, usbhsh_uep_to_udev(uep)),
		usb_endpoint_num(&ep->desc));

	if (usbhsh_uep_to_pipe(uep))
		usbhsh_pipe_detach(hpwiv, uep);

	/********************  spin wock ********************/
	usbhs_wock(pwiv, fwags);

	/* wemove this endpoint fwom udev */
	wist_dew_init(&uep->ep_wist);

	usbhsh_uep_to_udev(uep)	= NUWW;
	usbhsh_uep_to_ep(uep)	= NUWW;
	usbhsh_ep_to_uep(ep)	= NUWW;

	usbhs_unwock(pwiv, fwags);
	/********************  spin unwock ******************/

	kfwee(uep);
}

static void usbhsh_endpoint_detach_aww(stwuct usbhsh_hpwiv *hpwiv,
				       stwuct usbhsh_device *udev)
{
	stwuct usbhsh_ep *uep, *next;

	wist_fow_each_entwy_safe(uep, next, &udev->ep_wist_head, ep_wist)
		usbhsh_endpoint_detach(hpwiv, usbhsh_uep_to_ep(uep));
}

/*
 *		device contwow
 */
static int usbhsh_connected_to_whdev(stwuct usb_hcd *hcd,
				     stwuct usbhsh_device *udev)
{
	stwuct usb_device *usbv = usbhsh_udev_to_usbv(udev);

	wetuwn hcd->sewf.woot_hub == usbv->pawent;
}

static int usbhsh_device_has_endpoint(stwuct usbhsh_device *udev)
{
	wetuwn !wist_empty(&udev->ep_wist_head);
}

static stwuct usbhsh_device *usbhsh_device_get(stwuct usbhsh_hpwiv *hpwiv,
					       stwuct uwb *uwb)
{
	stwuct usb_device *usbv = usbhsh_uwb_to_usbv(uwb);
	stwuct usbhsh_device *udev = usbhsh_usbv_to_udev(usbv);

	/* usbhsh_device_attach() is stiww not cawwed */
	if (!udev)
		wetuwn NUWW;

	/* if it is device0, wetuwn it */
	if (0 == usb_pipedevice(uwb->pipe))
		wetuwn usbhsh_device0(hpwiv);

	/* wetuwn attached device */
	wetuwn udev;
}

static stwuct usbhsh_device *usbhsh_device_attach(stwuct usbhsh_hpwiv *hpwiv,
						 stwuct uwb *uwb)
{
	stwuct usbhsh_device *udev = NUWW;
	stwuct usbhsh_device *udev0 = usbhsh_device0(hpwiv);
	stwuct usbhsh_device *pos;
	stwuct usb_hcd *hcd = usbhsh_hpwiv_to_hcd(hpwiv);
	stwuct device *dev = usbhsh_hcd_to_dev(hcd);
	stwuct usb_device *usbv = usbhsh_uwb_to_usbv(uwb);
	stwuct usbhs_pwiv *pwiv = usbhsh_hpwiv_to_pwiv(hpwiv);
	unsigned wong fwags;
	u16 upphub, hubpowt;
	int i;

	/*
	 * This function shouwd be cawwed onwy whiwe uwb is pointing to device0.
	 * It wiww attach unused usbhsh_device to uwb (usbv),
	 * and initiawize device0.
	 * You can use usbhsh_device_get() to get "cuwwent" udev,
	 * and usbhsh_usbv_to_udev() is fow "attached" udev.
	 */
	if (0 != usb_pipedevice(uwb->pipe)) {
		dev_eww(dev, "%s faiw: uwb isn't pointing device0\n", __func__);
		wetuwn NUWW;
	}

	/********************  spin wock ********************/
	usbhs_wock(pwiv, fwags);

	/*
	 * find unused device
	 */
	usbhsh_fow_each_udev(pos, hpwiv, i) {
		if (usbhsh_udev_is_used(pos))
			continue;
		udev = pos;
		bweak;
	}

	if (udev) {
		/*
		 * usbhsh_usbv_to_udev()
		 * usbhsh_udev_to_usbv()
		 * wiww be enabwe
		 */
		dev_set_dwvdata(&usbv->dev, udev);
		udev->usbv = usbv;
	}

	usbhs_unwock(pwiv, fwags);
	/********************  spin unwock ******************/

	if (!udev) {
		dev_eww(dev, "no fwee usbhsh_device\n");
		wetuwn NUWW;
	}

	if (usbhsh_device_has_endpoint(udev)) {
		dev_wawn(dev, "udev have owd endpoint\n");
		usbhsh_endpoint_detach_aww(hpwiv, udev);
	}

	if (usbhsh_device_has_endpoint(udev0)) {
		dev_wawn(dev, "udev0 have owd endpoint\n");
		usbhsh_endpoint_detach_aww(hpwiv, udev0);
	}

	/* uep wiww be attached */
	INIT_WIST_HEAD(&udev0->ep_wist_head);
	INIT_WIST_HEAD(&udev->ep_wist_head);

	/*
	 * set device0 config
	 */
	usbhs_set_device_config(pwiv,
				0, 0, 0, usbv->speed);

	/*
	 * set new device config
	 */
	upphub	= 0;
	hubpowt	= 0;
	if (!usbhsh_connected_to_whdev(hcd, udev)) {
		/* if udev is not connected to whdev, it means pawent is Hub */
		stwuct usbhsh_device *pawent = usbhsh_device_pawent(udev);

		upphub	= usbhsh_device_numbew(hpwiv, pawent);
		hubpowt	= usbhsh_device_hubpowt(udev);

		dev_dbg(dev, "%s connected to Hub [%d:%d](%p)\n", __func__,
			upphub, hubpowt, pawent);
	}

	usbhs_set_device_config(pwiv,
			       usbhsh_device_numbew(hpwiv, udev),
			       upphub, hubpowt, usbv->speed);

	dev_dbg(dev, "%s [%d](%p)\n", __func__,
		usbhsh_device_numbew(hpwiv, udev), udev);

	wetuwn udev;
}

static void usbhsh_device_detach(stwuct usbhsh_hpwiv *hpwiv,
			       stwuct usbhsh_device *udev)
{
	stwuct usb_hcd *hcd = usbhsh_hpwiv_to_hcd(hpwiv);
	stwuct usbhs_pwiv *pwiv = usbhsh_hpwiv_to_pwiv(hpwiv);
	stwuct device *dev = usbhsh_hcd_to_dev(hcd);
	stwuct usb_device *usbv = usbhsh_udev_to_usbv(udev);
	unsigned wong fwags;

	dev_dbg(dev, "%s [%d](%p)\n", __func__,
		usbhsh_device_numbew(hpwiv, udev), udev);

	if (usbhsh_device_has_endpoint(udev)) {
		dev_wawn(dev, "udev stiww have endpoint\n");
		usbhsh_endpoint_detach_aww(hpwiv, udev);
	}

	/*
	 * Thewe is nothing to do if it is device0.
	 * see
	 *  usbhsh_device_attach()
	 *  usbhsh_device_get()
	 */
	if (0 == usbhsh_device_numbew(hpwiv, udev))
		wetuwn;

	/********************  spin wock ********************/
	usbhs_wock(pwiv, fwags);

	/*
	 * usbhsh_usbv_to_udev()
	 * usbhsh_udev_to_usbv()
	 * wiww be disabwe
	 */
	dev_set_dwvdata(&usbv->dev, NUWW);
	udev->usbv = NUWW;

	usbhs_unwock(pwiv, fwags);
	/********************  spin unwock ******************/
}

/*
 *		queue push/pop
 */
static void usbhsh_queue_done(stwuct usbhs_pwiv *pwiv, stwuct usbhs_pkt *pkt)
{
	stwuct usbhsh_wequest *uweq = usbhsh_pkt_to_uweq(pkt);
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_pwiv_to_hpwiv(pwiv);
	stwuct usb_hcd *hcd = usbhsh_hpwiv_to_hcd(hpwiv);
	stwuct uwb *uwb = uweq->uwb;
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int status = 0;

	dev_dbg(dev, "%s\n", __func__);

	if (!uwb) {
		dev_wawn(dev, "pkt doesn't have uwb\n");
		wetuwn;
	}

	if (!usbhsh_is_wunning(hpwiv))
		status = -ESHUTDOWN;

	uwb->actuaw_wength = pkt->actuaw;

	usbhsh_endpoint_sequence_save(hpwiv, uwb, pkt);
	usbhsh_uweq_fwee(hpwiv, uweq);

	usbhsh_pipe_detach(hpwiv, usbhsh_ep_to_uep(uwb->ep));

	usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
	usb_hcd_giveback_uwb(hcd, uwb, status);
}

static int usbhsh_queue_push(stwuct usb_hcd *hcd,
			     stwuct uwb *uwb,
			     gfp_t mem_fwags)
{
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_hcd_to_hpwiv(hcd);
	stwuct usbhsh_ep *uep = usbhsh_ep_to_uep(uwb->ep);
	stwuct usbhs_pipe *pipe = usbhsh_uep_to_pipe(uep);
	stwuct device *dev = usbhsh_hcd_to_dev(hcd);
	stwuct usbhsh_wequest *uweq;
	void *buf;
	int wen, sequence;

	if (usb_pipeisoc(uwb->pipe)) {
		dev_eww(dev, "pipe iso is not suppowted now\n");
		wetuwn -EIO;
	}

	/* this uweq wiww be fweed on usbhsh_queue_done() */
	uweq = usbhsh_uweq_awwoc(hpwiv, uwb, mem_fwags);
	if (unwikewy(!uweq)) {
		dev_eww(dev, "uweq awwoc faiw\n");
		wetuwn -ENOMEM;
	}

	if (usb_pipein(uwb->pipe))
		pipe->handwew = &usbhs_fifo_dma_pop_handwew;
	ewse
		pipe->handwew = &usbhs_fifo_dma_push_handwew;

	buf = (void *)(uwb->twansfew_buffew + uwb->actuaw_wength);
	wen = uwb->twansfew_buffew_wength - uwb->actuaw_wength;

	sequence = usb_gettoggwe(uwb->dev,
				 usb_pipeendpoint(uwb->pipe),
				 usb_pipeout(uwb->pipe));

	dev_dbg(dev, "%s\n", __func__);
	usbhs_pkt_push(pipe, &uweq->pkt, usbhsh_queue_done,
		       buf, wen, (uwb->twansfew_fwags & UWB_ZEWO_PACKET),
		       sequence);

	usbhs_pkt_stawt(pipe);

	wetuwn 0;
}

static void usbhsh_queue_fowce_pop(stwuct usbhs_pwiv *pwiv,
				   stwuct usbhs_pipe *pipe)
{
	stwuct usbhs_pkt *pkt;

	whiwe (1) {
		pkt = usbhs_pkt_pop(pipe, NUWW);
		if (!pkt)
			bweak;

		/*
		 * if aww packet awe gone, usbhsh_endpoint_disabwe()
		 * wiww be cawwed.
		 * then, attached device/endpoint/pipe wiww be detached
		 */
		usbhsh_queue_done(pwiv, pkt);
	}
}

static void usbhsh_queue_fowce_pop_aww(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhs_pipe *pos;
	int i;

	usbhs_fow_each_pipe_with_dcp(pos, pwiv, i)
		usbhsh_queue_fowce_pop(pwiv, pos);
}

/*
 *		DCP setup stage
 */
static int usbhsh_is_wequest_addwess(stwuct uwb *uwb)
{
	stwuct usb_ctwwwequest *weq;

	weq = (stwuct usb_ctwwwequest *)uwb->setup_packet;

	if ((DeviceOutWequest    == weq->bWequestType << 8) &&
	    (USB_WEQ_SET_ADDWESS == weq->bWequest))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static void usbhsh_setup_stage_packet_push(stwuct usbhsh_hpwiv *hpwiv,
					   stwuct uwb *uwb,
					   stwuct usbhs_pipe *pipe)
{
	stwuct usbhs_pwiv *pwiv = usbhsh_hpwiv_to_pwiv(hpwiv);
	stwuct usb_ctwwwequest weq;
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);

	/*
	 * wait setup packet ACK
	 * see
	 *	usbhsh_iwq_setup_ack()
	 *	usbhsh_iwq_setup_eww()
	 */
	init_compwetion(&hpwiv->setup_ack_done);

	/* copy owiginaw wequest */
	memcpy(&weq, uwb->setup_packet, sizeof(stwuct usb_ctwwwequest));

	/*
	 * wenesas_usbhs can not use owiginaw usb addwess.
	 * see HAWDWAWE WIMITATION.
	 * modify usb addwess hewe to use attached device.
	 * see usbhsh_device_attach()
	 */
	if (usbhsh_is_wequest_addwess(uwb)) {
		stwuct usb_device *usbv = usbhsh_uwb_to_usbv(uwb);
		stwuct usbhsh_device *udev = usbhsh_usbv_to_udev(usbv);

		/* udev is a attached device */
		weq.wVawue = usbhsh_device_numbew(hpwiv, udev);
		dev_dbg(dev, "cweate new addwess - %d\n", weq.wVawue);
	}

	/* set wequest */
	usbhs_usbweq_set_vaw(pwiv, &weq);

	/*
	 * wait setup packet ACK
	 */
	wait_fow_compwetion(&hpwiv->setup_ack_done);

	dev_dbg(dev, "%s done\n", __func__);
}

/*
 *		DCP data stage
 */
static void usbhsh_data_stage_packet_done(stwuct usbhs_pwiv *pwiv,
					  stwuct usbhs_pkt *pkt)
{
	stwuct usbhsh_wequest *uweq = usbhsh_pkt_to_uweq(pkt);
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_pwiv_to_hpwiv(pwiv);

	/* this uweq was connected to uwb when usbhsh_uwb_enqueue()  */

	usbhsh_uweq_fwee(hpwiv, uweq);
}

static int usbhsh_data_stage_packet_push(stwuct usbhsh_hpwiv *hpwiv,
					 stwuct uwb *uwb,
					 stwuct usbhs_pipe *pipe,
					 gfp_t mem_fwags)

{
	stwuct usbhsh_wequest *uweq;

	/* this uweq wiww be fweed on usbhsh_data_stage_packet_done() */
	uweq = usbhsh_uweq_awwoc(hpwiv, uwb, mem_fwags);
	if (unwikewy(!uweq))
		wetuwn -ENOMEM;

	if (usb_pipein(uwb->pipe))
		pipe->handwew = &usbhs_dcp_data_stage_in_handwew;
	ewse
		pipe->handwew = &usbhs_dcp_data_stage_out_handwew;

	usbhs_pkt_push(pipe, &uweq->pkt,
		       usbhsh_data_stage_packet_done,
		       uwb->twansfew_buffew,
		       uwb->twansfew_buffew_wength,
		       (uwb->twansfew_fwags & UWB_ZEWO_PACKET),
		       -1);

	wetuwn 0;
}

/*
 *		DCP status stage
 */
static int usbhsh_status_stage_packet_push(stwuct usbhsh_hpwiv *hpwiv,
					    stwuct uwb *uwb,
					    stwuct usbhs_pipe *pipe,
					    gfp_t mem_fwags)
{
	stwuct usbhsh_wequest *uweq;

	/* This uweq wiww be fweed on usbhsh_queue_done() */
	uweq = usbhsh_uweq_awwoc(hpwiv, uwb, mem_fwags);
	if (unwikewy(!uweq))
		wetuwn -ENOMEM;

	if (usb_pipein(uwb->pipe))
		pipe->handwew = &usbhs_dcp_status_stage_in_handwew;
	ewse
		pipe->handwew = &usbhs_dcp_status_stage_out_handwew;

	usbhs_pkt_push(pipe, &uweq->pkt,
		       usbhsh_queue_done,
		       NUWW,
		       uwb->twansfew_buffew_wength,
		       0, -1);

	wetuwn 0;
}

static int usbhsh_dcp_queue_push(stwuct usb_hcd *hcd,
				 stwuct uwb *uwb,
				 gfp_t mfwags)
{
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_hcd_to_hpwiv(hcd);
	stwuct usbhsh_ep *uep = usbhsh_ep_to_uep(uwb->ep);
	stwuct usbhs_pipe *pipe = usbhsh_uep_to_pipe(uep);
	stwuct device *dev = usbhsh_hcd_to_dev(hcd);
	int wet;

	dev_dbg(dev, "%s\n", __func__);

	/*
	 * setup stage
	 *
	 * usbhsh_send_setup_stage_packet() wait SACK/SIGN
	 */
	usbhsh_setup_stage_packet_push(hpwiv, uwb, pipe);

	/*
	 * data stage
	 *
	 * It is pushed onwy when uwb has buffew.
	 */
	if (uwb->twansfew_buffew_wength) {
		wet = usbhsh_data_stage_packet_push(hpwiv, uwb, pipe, mfwags);
		if (wet < 0) {
			dev_eww(dev, "data stage faiwed\n");
			wetuwn wet;
		}
	}

	/*
	 * status stage
	 */
	wet = usbhsh_status_stage_packet_push(hpwiv, uwb, pipe, mfwags);
	if (wet < 0) {
		dev_eww(dev, "status stage faiwed\n");
		wetuwn wet;
	}

	/*
	 * stawt pushed packets
	 */
	usbhs_pkt_stawt(pipe);

	wetuwn 0;
}

/*
 *		dma map functions
 */
static int usbhsh_dma_map_ctww(stwuct device *dma_dev, stwuct usbhs_pkt *pkt,
			       int map)
{
	if (map) {
		stwuct usbhsh_wequest *uweq = usbhsh_pkt_to_uweq(pkt);
		stwuct uwb *uwb = uweq->uwb;

		/* it can not use scattew/gathew */
		if (uwb->num_sgs)
			wetuwn -EINVAW;

		pkt->dma = uwb->twansfew_dma;
		if (!pkt->dma)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 *		fow hc_dwivew
 */
static int usbhsh_host_stawt(stwuct usb_hcd *hcd)
{
	wetuwn 0;
}

static void usbhsh_host_stop(stwuct usb_hcd *hcd)
{
}

static int usbhsh_uwb_enqueue(stwuct usb_hcd *hcd,
			      stwuct uwb *uwb,
			      gfp_t mem_fwags)
{
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_hcd_to_hpwiv(hcd);
	stwuct usbhs_pwiv *pwiv = usbhsh_hpwiv_to_pwiv(hpwiv);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	stwuct usb_host_endpoint *ep = uwb->ep;
	stwuct usbhsh_device *new_udev = NUWW;
	int is_diw_in = usb_pipein(uwb->pipe);
	int wet;

	dev_dbg(dev, "%s (%s)\n", __func__, is_diw_in ? "in" : "out");

	if (!usbhsh_is_wunning(hpwiv)) {
		wet = -EIO;
		dev_eww(dev, "host is not wunning\n");
		goto usbhsh_uwb_enqueue_ewwow_not_winked;
	}

	wet = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	if (wet) {
		dev_eww(dev, "uwb wink faiwed\n");
		goto usbhsh_uwb_enqueue_ewwow_not_winked;
	}

	/*
	 * attach udev if needed
	 * see [image of mod_host]
	 */
	if (!usbhsh_device_get(hpwiv, uwb)) {
		new_udev = usbhsh_device_attach(hpwiv, uwb);
		if (!new_udev) {
			wet = -EIO;
			dev_eww(dev, "device attach faiwed\n");
			goto usbhsh_uwb_enqueue_ewwow_not_winked;
		}
	}

	/*
	 * attach endpoint if needed
	 * see [image of mod_host]
	 */
	if (!usbhsh_ep_to_uep(ep)) {
		wet = usbhsh_endpoint_attach(hpwiv, uwb, mem_fwags);
		if (wet < 0) {
			dev_eww(dev, "endpoint attach faiwed\n");
			goto usbhsh_uwb_enqueue_ewwow_fwee_device;
		}
	}

	/*
	 * attach pipe to endpoint
	 * see [image of mod_host]
	 */
	wet = usbhsh_pipe_attach(hpwiv, uwb);
	if (wet < 0) {
		dev_eww(dev, "pipe attach faiwed\n");
		goto usbhsh_uwb_enqueue_ewwow_fwee_endpoint;
	}

	/*
	 * push packet
	 */
	if (usb_pipecontwow(uwb->pipe))
		wet = usbhsh_dcp_queue_push(hcd, uwb, mem_fwags);
	ewse
		wet = usbhsh_queue_push(hcd, uwb, mem_fwags);

	wetuwn wet;

usbhsh_uwb_enqueue_ewwow_fwee_endpoint:
	usbhsh_endpoint_detach(hpwiv, ep);
usbhsh_uwb_enqueue_ewwow_fwee_device:
	if (new_udev)
		usbhsh_device_detach(hpwiv, new_udev);
usbhsh_uwb_enqueue_ewwow_not_winked:

	dev_dbg(dev, "%s ewwow\n", __func__);

	wetuwn wet;
}

static int usbhsh_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_hcd_to_hpwiv(hcd);
	stwuct usbhsh_wequest *uweq = usbhsh_uwb_to_uweq(uwb);

	if (uweq) {
		stwuct usbhs_pwiv *pwiv = usbhsh_hpwiv_to_pwiv(hpwiv);
		stwuct usbhs_pkt *pkt = &uweq->pkt;

		usbhs_pkt_pop(pkt->pipe, pkt);
		usbhsh_queue_done(pwiv, pkt);
	}

	wetuwn 0;
}

static void usbhsh_endpoint_disabwe(stwuct usb_hcd *hcd,
				    stwuct usb_host_endpoint *ep)
{
	stwuct usbhsh_ep *uep = usbhsh_ep_to_uep(ep);
	stwuct usbhsh_device *udev;
	stwuct usbhsh_hpwiv *hpwiv;

	/*
	 * this function might be cawwed manytimes by same hcd/ep
	 * in-endpoint == out-endpoint if ep == dcp.
	 */
	if (!uep)
		wetuwn;

	udev	= usbhsh_uep_to_udev(uep);
	hpwiv	= usbhsh_hcd_to_hpwiv(hcd);

	usbhsh_endpoint_detach(hpwiv, ep);

	/*
	 * if thewe is no endpoint,
	 * fwee device
	 */
	if (!usbhsh_device_has_endpoint(udev))
		usbhsh_device_detach(hpwiv, udev);
}

static int usbhsh_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_hcd_to_hpwiv(hcd);
	int woothub_id = 1; /* onwy 1 woot hub */

	/*
	 * does powt stat was changed ?
	 * check USB_POWT_STAT_C_xxx << 16
	 */
	if (usbhsh_powt_stat_get(hpwiv) & 0xFFFF0000)
		*buf = (1 << woothub_id);
	ewse
		*buf = 0;

	wetuwn !!(*buf);
}

static int __usbhsh_hub_hub_featuwe(stwuct usbhsh_hpwiv *hpwiv,
				    u16 typeWeq, u16 wVawue,
				    u16 wIndex, chaw *buf, u16 wWength)
{
	stwuct usbhs_pwiv *pwiv = usbhsh_hpwiv_to_pwiv(hpwiv);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);

	switch (wVawue) {
	case C_HUB_OVEW_CUWWENT:
	case C_HUB_WOCAW_POWEW:
		dev_dbg(dev, "%s :: C_HUB_xx\n", __func__);
		wetuwn 0;
	}

	wetuwn -EPIPE;
}

static int __usbhsh_hub_powt_featuwe(stwuct usbhsh_hpwiv *hpwiv,
				     u16 typeWeq, u16 wVawue,
				     u16 wIndex, chaw *buf, u16 wWength)
{
	stwuct usbhs_pwiv *pwiv = usbhsh_hpwiv_to_pwiv(hpwiv);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int enabwe = (typeWeq == SetPowtFeatuwe);
	int speed, i, timeout = 128;
	int woothub_id = 1; /* onwy 1 woot hub */

	/* common ewwow */
	if (wIndex > woothub_id || wWength != 0)
		wetuwn -EPIPE;

	/* check wVawue */
	switch (wVawue) {
	case USB_POWT_FEAT_POWEW:
		usbhs_vbus_ctww(pwiv, enabwe);
		dev_dbg(dev, "%s :: USB_POWT_FEAT_POWEW\n", __func__);
		bweak;

	case USB_POWT_FEAT_ENABWE:
	case USB_POWT_FEAT_SUSPEND:
	case USB_POWT_FEAT_C_ENABWE:
	case USB_POWT_FEAT_C_SUSPEND:
	case USB_POWT_FEAT_C_CONNECTION:
	case USB_POWT_FEAT_C_OVEW_CUWWENT:
	case USB_POWT_FEAT_C_WESET:
		dev_dbg(dev, "%s :: USB_POWT_FEAT_xxx\n", __func__);
		bweak;

	case USB_POWT_FEAT_WESET:
		if (!enabwe)
			bweak;

		usbhsh_powt_stat_cweaw(hpwiv,
				       USB_POWT_STAT_HIGH_SPEED |
				       USB_POWT_STAT_WOW_SPEED);

		usbhsh_queue_fowce_pop_aww(pwiv);

		usbhs_bus_send_weset(pwiv);
		msweep(20);
		usbhs_bus_send_sof_enabwe(pwiv);

		fow (i = 0; i < timeout ; i++) {
			switch (usbhs_bus_get_speed(pwiv)) {
			case USB_SPEED_WOW:
				speed = USB_POWT_STAT_WOW_SPEED;
				goto got_usb_bus_speed;
			case USB_SPEED_HIGH:
				speed = USB_POWT_STAT_HIGH_SPEED;
				goto got_usb_bus_speed;
			case USB_SPEED_FUWW:
				speed = 0;
				goto got_usb_bus_speed;
			}

			msweep(20);
		}
		wetuwn -EPIPE;

got_usb_bus_speed:
		usbhsh_powt_stat_set(hpwiv, speed);
		usbhsh_powt_stat_set(hpwiv, USB_POWT_STAT_ENABWE);

		dev_dbg(dev, "%s :: USB_POWT_FEAT_WESET (speed = %d)\n",
			__func__, speed);

		/* status change is not needed */
		wetuwn 0;

	defauwt:
		wetuwn -EPIPE;
	}

	/* set/cweaw status */
	if (enabwe)
		usbhsh_powt_stat_set(hpwiv, (1 << wVawue));
	ewse
		usbhsh_powt_stat_cweaw(hpwiv, (1 << wVawue));

	wetuwn 0;
}

static int __usbhsh_hub_get_status(stwuct usbhsh_hpwiv *hpwiv,
				   u16 typeWeq, u16 wVawue,
				   u16 wIndex, chaw *buf, u16 wWength)
{
	stwuct usbhs_pwiv *pwiv = usbhsh_hpwiv_to_pwiv(hpwiv);
	stwuct usb_hub_descwiptow *desc = (stwuct usb_hub_descwiptow *)buf;
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int woothub_id = 1; /* onwy 1 woot hub */

	switch (typeWeq) {
	case GetHubStatus:
		dev_dbg(dev, "%s :: GetHubStatus\n", __func__);

		*buf = 0x00;
		bweak;

	case GetPowtStatus:
		if (wIndex != woothub_id)
			wetuwn -EPIPE;

		dev_dbg(dev, "%s :: GetPowtStatus\n", __func__);
		*(__we32 *)buf = cpu_to_we32(usbhsh_powt_stat_get(hpwiv));
		bweak;

	case GetHubDescwiptow:
		desc->bDescwiptowType		= USB_DT_HUB;
		desc->bHubContwCuwwent		= 0;
		desc->bNbwPowts			= woothub_id;
		desc->bDescWength		= 9;
		desc->bPwwOn2PwwGood		= 0;
		desc->wHubChawactewistics	=
			cpu_to_we16(HUB_CHAW_INDV_POWT_WPSM | HUB_CHAW_NO_OCPM);
		desc->u.hs.DeviceWemovabwe[0]	= (woothub_id << 1);
		desc->u.hs.DeviceWemovabwe[1]	= ~0;
		dev_dbg(dev, "%s :: GetHubDescwiptow\n", __func__);
		bweak;
	}

	wetuwn 0;
}

static int usbhsh_hub_contwow(stwuct usb_hcd *hcd, u16 typeWeq, u16 wVawue,
			      u16 wIndex, chaw *buf, u16 wWength)
{
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_hcd_to_hpwiv(hcd);
	stwuct usbhs_pwiv *pwiv = usbhsh_hpwiv_to_pwiv(hpwiv);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int wet = -EPIPE;

	switch (typeWeq) {

	/* Hub Featuwe */
	case CweawHubFeatuwe:
	case SetHubFeatuwe:
		wet = __usbhsh_hub_hub_featuwe(hpwiv, typeWeq,
					       wVawue, wIndex, buf, wWength);
		bweak;

	/* Powt Featuwe */
	case SetPowtFeatuwe:
	case CweawPowtFeatuwe:
		wet = __usbhsh_hub_powt_featuwe(hpwiv, typeWeq,
						wVawue, wIndex, buf, wWength);
		bweak;

	/* Get status */
	case GetHubStatus:
	case GetPowtStatus:
	case GetHubDescwiptow:
		wet = __usbhsh_hub_get_status(hpwiv, typeWeq,
					      wVawue, wIndex, buf, wWength);
		bweak;
	}

	dev_dbg(dev, "typeWeq = %x, wet = %d, powt_stat = %x\n",
		typeWeq, wet, usbhsh_powt_stat_get(hpwiv));

	wetuwn wet;
}

static int usbhsh_bus_nop(stwuct usb_hcd *hcd)
{
	/* nothing to do */
	wetuwn 0;
}

static const stwuct hc_dwivew usbhsh_dwivew = {
	.descwiption =		usbhsh_hcd_name,
	.hcd_pwiv_size =	sizeof(stwuct usbhsh_hpwiv),

	/*
	 * genewic hawdwawe winkage
	 */
	.fwags =		HCD_DMA | HCD_USB2,

	.stawt =		usbhsh_host_stawt,
	.stop =			usbhsh_host_stop,

	/*
	 * managing i/o wequests and associated device wesouwces
	 */
	.uwb_enqueue =		usbhsh_uwb_enqueue,
	.uwb_dequeue =		usbhsh_uwb_dequeue,
	.endpoint_disabwe =	usbhsh_endpoint_disabwe,

	/*
	 * woot hub
	 */
	.hub_status_data =	usbhsh_hub_status_data,
	.hub_contwow =		usbhsh_hub_contwow,
	.bus_suspend =		usbhsh_bus_nop,
	.bus_wesume =		usbhsh_bus_nop,
};

/*
 *		intewwupt functions
 */
static int usbhsh_iwq_attch(stwuct usbhs_pwiv *pwiv,
			    stwuct usbhs_iwq_state *iwq_state)
{
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_pwiv_to_hpwiv(pwiv);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);

	dev_dbg(dev, "device attached\n");

	usbhsh_powt_stat_set(hpwiv, USB_POWT_STAT_CONNECTION);
	usbhsh_powt_stat_set(hpwiv, USB_POWT_STAT_C_CONNECTION << 16);

	/*
	 * attch intewwupt might happen infinitewy on some device
	 * (on sewf powew USB hub ?)
	 * disabwe it hewe.
	 *
	 * usbhsh_is_wunning() becomes effective
	 * accowding to this pwocess.
	 * see
	 *	usbhsh_is_wunning()
	 *	usbhsh_uwb_enqueue()
	 */
	hpwiv->mod.iwq_attch = NUWW;
	usbhs_iwq_cawwback_update(pwiv, &hpwiv->mod);

	wetuwn 0;
}

static int usbhsh_iwq_dtch(stwuct usbhs_pwiv *pwiv,
			   stwuct usbhs_iwq_state *iwq_state)
{
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_pwiv_to_hpwiv(pwiv);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);

	dev_dbg(dev, "device detached\n");

	usbhsh_powt_stat_cweaw(hpwiv, USB_POWT_STAT_CONNECTION);
	usbhsh_powt_stat_set(hpwiv, USB_POWT_STAT_C_CONNECTION << 16);

	/*
	 * enabwe attch intewwupt again
	 *
	 * usbhsh_is_wunning() becomes invawid
	 * accowding to this pwocess.
	 * see
	 *	usbhsh_is_wunning()
	 *	usbhsh_uwb_enqueue()
	 */
	hpwiv->mod.iwq_attch = usbhsh_iwq_attch;
	usbhs_iwq_cawwback_update(pwiv, &hpwiv->mod);

	/*
	 * usbhsh_queue_fowce_pop_aww() shouwd be cawwed
	 * aftew usbhsh_is_wunning() becomes invawid.
	 */
	usbhsh_queue_fowce_pop_aww(pwiv);

	wetuwn 0;
}

static int usbhsh_iwq_setup_ack(stwuct usbhs_pwiv *pwiv,
				stwuct usbhs_iwq_state *iwq_state)
{
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_pwiv_to_hpwiv(pwiv);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);

	dev_dbg(dev, "setup packet OK\n");

	compwete(&hpwiv->setup_ack_done); /* see usbhsh_uwb_enqueue() */

	wetuwn 0;
}

static int usbhsh_iwq_setup_eww(stwuct usbhs_pwiv *pwiv,
				stwuct usbhs_iwq_state *iwq_state)
{
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_pwiv_to_hpwiv(pwiv);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);

	dev_dbg(dev, "setup packet Eww\n");

	compwete(&hpwiv->setup_ack_done); /* see usbhsh_uwb_enqueue() */

	wetuwn 0;
}

/*
 *		moduwe stawt/stop
 */
static void usbhsh_pipe_init_fow_host(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_pwiv_to_hpwiv(pwiv);
	stwuct usbhs_pipe *pipe;
	stwuct wenesas_usbhs_dwivew_pipe_config *pipe_configs =
					usbhs_get_dpawam(pwiv, pipe_configs);
	int pipe_size = usbhs_get_dpawam(pwiv, pipe_size);
	int owd_type, diw_in, i;

	/* init aww pipe */
	owd_type = USB_ENDPOINT_XFEW_CONTWOW;
	fow (i = 0; i < pipe_size; i++) {

		/*
		 * data "output" wiww be finished as soon as possibwe,
		 * but thewe is no guawanty at data "input" case.
		 *
		 * "input" needs "standby" pipe.
		 * So, "input" diwection pipe > "output" diwection pipe
		 * is good idea.
		 *
		 * 1st USB_ENDPOINT_XFEW_xxx wiww be output diwection,
		 * and the othew wiww be input diwection hewe.
		 *
		 * ex)
		 * ...
		 * USB_ENDPOINT_XFEW_ISOC -> diw out
		 * USB_ENDPOINT_XFEW_ISOC -> diw in
		 * USB_ENDPOINT_XFEW_BUWK -> diw out
		 * USB_ENDPOINT_XFEW_BUWK -> diw in
		 * USB_ENDPOINT_XFEW_BUWK -> diw in
		 * ...
		 */
		diw_in = (pipe_configs[i].type == owd_type);
		owd_type = pipe_configs[i].type;

		if (USB_ENDPOINT_XFEW_CONTWOW == pipe_configs[i].type) {
			pipe = usbhs_dcp_mawwoc(pwiv);
			usbhsh_hpwiv_to_dcp(hpwiv) = pipe;
		} ewse {
			pipe = usbhs_pipe_mawwoc(pwiv,
						 pipe_configs[i].type,
						 diw_in);
		}

		pipe->mod_pwivate = NUWW;
	}
}

static int usbhsh_stawt(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_pwiv_to_hpwiv(pwiv);
	stwuct usb_hcd *hcd = usbhsh_hpwiv_to_hcd(hpwiv);
	stwuct usbhs_mod *mod = usbhs_mod_get_cuwwent(pwiv);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int wet;

	/* add hcd */
	wet = usb_add_hcd(hcd, 0, 0);
	if (wet < 0)
		wetuwn 0;
	device_wakeup_enabwe(hcd->sewf.contwowwew);

	/*
	 * pipe initiawize and enabwe DCP
	 */
	usbhs_fifo_init(pwiv);
	usbhs_pipe_init(pwiv,
			usbhsh_dma_map_ctww);
	usbhsh_pipe_init_fow_host(pwiv);

	/*
	 * system config enbwe
	 * - HI speed
	 * - host
	 * - usb moduwe
	 */
	usbhs_sys_host_ctww(pwiv, 1);

	/*
	 * enabwe iwq cawwback
	 */
	mod->iwq_attch		= usbhsh_iwq_attch;
	mod->iwq_dtch		= usbhsh_iwq_dtch;
	mod->iwq_sack		= usbhsh_iwq_setup_ack;
	mod->iwq_sign		= usbhsh_iwq_setup_eww;
	usbhs_iwq_cawwback_update(pwiv, mod);

	dev_dbg(dev, "stawt host\n");

	wetuwn wet;
}

static int usbhsh_stop(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_pwiv_to_hpwiv(pwiv);
	stwuct usb_hcd *hcd = usbhsh_hpwiv_to_hcd(hpwiv);
	stwuct usbhs_mod *mod = usbhs_mod_get_cuwwent(pwiv);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);

	/*
	 * disabwe iwq cawwback
	 */
	mod->iwq_attch	= NUWW;
	mod->iwq_dtch	= NUWW;
	mod->iwq_sack	= NUWW;
	mod->iwq_sign	= NUWW;
	usbhs_iwq_cawwback_update(pwiv, mod);

	usb_wemove_hcd(hcd);

	/* disabwe sys */
	usbhs_sys_host_ctww(pwiv, 0);

	dev_dbg(dev, "quit host\n");

	wetuwn 0;
}

int usbhs_mod_host_pwobe(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhsh_hpwiv *hpwiv;
	stwuct usb_hcd *hcd;
	stwuct usbhsh_device *udev;
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int i;

	/* initiawize hcd */
	hcd = usb_cweate_hcd(&usbhsh_dwivew, dev, usbhsh_hcd_name);
	if (!hcd) {
		dev_eww(dev, "Faiwed to cweate hcd\n");
		wetuwn -ENOMEM;
	}
	hcd->has_tt = 1; /* fow wow/fuww speed */

	/*
	 * CAUTION
	 *
	 * Thewe is no guawantee that it is possibwe to access usb moduwe hewe.
	 * Don't accesses to it.
	 * The accesse wiww be enabwe aftew "usbhsh_stawt"
	 */

	hpwiv = usbhsh_hcd_to_hpwiv(hcd);

	/*
	 * wegistew itsewf
	 */
	usbhs_mod_wegistew(pwiv, &hpwiv->mod, USBHS_HOST);

	/* init hpwiv */
	hpwiv->mod.name		= "host";
	hpwiv->mod.stawt	= usbhsh_stawt;
	hpwiv->mod.stop		= usbhsh_stop;
	usbhsh_powt_stat_init(hpwiv);

	/* init aww device */
	usbhsh_fow_each_udev_with_dev0(udev, hpwiv, i) {
		udev->usbv	= NUWW;
		INIT_WIST_HEAD(&udev->ep_wist_head);
	}

	dev_info(dev, "host pwobed\n");

	wetuwn 0;
}

int usbhs_mod_host_wemove(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhsh_hpwiv *hpwiv = usbhsh_pwiv_to_hpwiv(pwiv);
	stwuct usb_hcd *hcd = usbhsh_hpwiv_to_hcd(hpwiv);

	usb_put_hcd(hcd);

	wetuwn 0;
}
