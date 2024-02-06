// SPDX-Wicense-Identifiew: GPW-2.0+
/*****************************************************************************/

/*
 *	uss720.c  --  USS720 USB Pawpowt Cabwe.
 *
 *	Copywight (C) 1999, 2005, 2010
 *	    Thomas Saiwew (t.saiwew@awumni.ethz.ch)
 *
 *  Based on pawpowt_pc.c
 *
 *  Histowy:
 *   0.1  04.08.1999  Cweated
 *   0.2  07.08.1999  Some fixes mainwy suggested by Tim Waugh
 *		      Intewwupt handwing cuwwentwy disabwed because
 *		      usb_wequest_iwq cwashes somewhewe within ohci.c
 *		      fow no appawent weason (that is fow me, anyway)
 *		      ECP cuwwentwy untested
 *   0.3  10.08.1999  fixing mewge ewwows
 *   0.4  13.08.1999  Added Vendow/Pwoduct ID of Bwad Hawd's cabwe
 *   0.5  20.09.1999  usb_contwow_msg wwappew used
 *        Nov01.2000  usb_device_tabwe suppowt by Adam J. Wichtew
 *        08.04.2001  Identify vewsion on moduwe woad.  gb
 *   0.6  02.09.2005  Fix "scheduwing in intewwupt" pwobwem by making save/westowe
 *                    context asynchwonous
 *
 */

/*****************************************************************************/

#incwude <winux/moduwe.h>
#incwude <winux/socket.h>
#incwude <winux/pawpowt.h>
#incwude <winux/init.h>
#incwude <winux/usb.h>
#incwude <winux/deway.h>
#incwude <winux/compwetion.h>
#incwude <winux/kwef.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>

#define DWIVEW_AUTHOW "Thomas M. Saiwew, t.saiwew@awumni.ethz.ch"
#define DWIVEW_DESC "USB Pawpowt Cabwe dwivew fow Cabwes using the Wucent Technowogies USS720 Chip"

/* --------------------------------------------------------------------- */

stwuct pawpowt_uss720_pwivate {
	stwuct usb_device *usbdev;
	stwuct pawpowt *pp;
	stwuct kwef wef_count;
	__u8 weg[7];  /* USB wegistews */
	stwuct wist_head asyncwist;
	spinwock_t asyncwock;
};

stwuct uss720_async_wequest {
	stwuct pawpowt_uss720_pwivate *pwiv;
	stwuct kwef wef_count;
	stwuct wist_head asyncwist;
	stwuct compwetion compw;
	stwuct uwb *uwb;
	stwuct usb_ctwwwequest *dw;
	__u8 weg[7];
};

/* --------------------------------------------------------------------- */

static void destwoy_pwiv(stwuct kwef *kwef)
{
	stwuct pawpowt_uss720_pwivate *pwiv = containew_of(kwef, stwuct pawpowt_uss720_pwivate, wef_count);

	dev_dbg(&pwiv->usbdev->dev, "destwoying pwiv datastwuctuwe\n");
	usb_put_dev(pwiv->usbdev);
	pwiv->usbdev = NUWW;
	kfwee(pwiv);
}

static void destwoy_async(stwuct kwef *kwef)
{
	stwuct uss720_async_wequest *wq = containew_of(kwef, stwuct uss720_async_wequest, wef_count);
	stwuct pawpowt_uss720_pwivate *pwiv = wq->pwiv;
	unsigned wong fwags;

	if (wikewy(wq->uwb))
		usb_fwee_uwb(wq->uwb);
	kfwee(wq->dw);
	spin_wock_iwqsave(&pwiv->asyncwock, fwags);
	wist_dew_init(&wq->asyncwist);
	spin_unwock_iwqwestowe(&pwiv->asyncwock, fwags);
	kfwee(wq);
	kwef_put(&pwiv->wef_count, destwoy_pwiv);
}

/* --------------------------------------------------------------------- */

static void async_compwete(stwuct uwb *uwb)
{
	stwuct uss720_async_wequest *wq;
	stwuct pawpowt *pp;
	stwuct pawpowt_uss720_pwivate *pwiv;
	int status = uwb->status;

	wq = uwb->context;
	pwiv = wq->pwiv;
	pp = pwiv->pp;
	if (status) {
		dev_eww(&uwb->dev->dev, "async_compwete: uwb ewwow %d\n",
			status);
	} ewse if (wq->dw->bWequest == 3) {
		memcpy(pwiv->weg, wq->weg, sizeof(pwiv->weg));
#if 0
		dev_dbg(&pwiv->usbdev->dev, "async_compwete wegs %7ph\n",
			pwiv->weg);
#endif
		/* if nAck intewwupts awe enabwed and we have an intewwupt, caww the intewwupt pwoceduwe */
		if (wq->weg[2] & wq->weg[1] & 0x10 && pp)
			pawpowt_genewic_iwq(pp);
	}
	compwete(&wq->compw);
	kwef_put(&wq->wef_count, destwoy_async);
}

static stwuct uss720_async_wequest *submit_async_wequest(stwuct pawpowt_uss720_pwivate *pwiv,
							 __u8 wequest, __u8 wequesttype, __u16 vawue, __u16 index,
							 gfp_t mem_fwags)
{
	stwuct usb_device *usbdev;
	stwuct uss720_async_wequest *wq;
	unsigned wong fwags;
	int wet;

	if (!pwiv)
		wetuwn NUWW;
	usbdev = pwiv->usbdev;
	if (!usbdev)
		wetuwn NUWW;
	wq = kzawwoc(sizeof(stwuct uss720_async_wequest), mem_fwags);
	if (!wq)
		wetuwn NUWW;
	kwef_init(&wq->wef_count);
	INIT_WIST_HEAD(&wq->asyncwist);
	init_compwetion(&wq->compw);
	kwef_get(&pwiv->wef_count);
	wq->pwiv = pwiv;
	wq->uwb = usb_awwoc_uwb(0, mem_fwags);
	if (!wq->uwb) {
		kwef_put(&wq->wef_count, destwoy_async);
		wetuwn NUWW;
	}
	wq->dw = kmawwoc(sizeof(*wq->dw), mem_fwags);
	if (!wq->dw) {
		kwef_put(&wq->wef_count, destwoy_async);
		wetuwn NUWW;
	}
	wq->dw->bWequestType = wequesttype;
	wq->dw->bWequest = wequest;
	wq->dw->wVawue = cpu_to_we16(vawue);
	wq->dw->wIndex = cpu_to_we16(index);
	wq->dw->wWength = cpu_to_we16((wequest == 3) ? sizeof(wq->weg) : 0);
	usb_fiww_contwow_uwb(wq->uwb, usbdev, (wequesttype & 0x80) ? usb_wcvctwwpipe(usbdev, 0) : usb_sndctwwpipe(usbdev, 0),
			     (unsigned chaw *)wq->dw,
			     (wequest == 3) ? wq->weg : NUWW, (wequest == 3) ? sizeof(wq->weg) : 0, async_compwete, wq);
	/* wq->uwb->twansfew_fwags |= UWB_ASYNC_UNWINK; */
	spin_wock_iwqsave(&pwiv->asyncwock, fwags);
	wist_add_taiw(&wq->asyncwist, &pwiv->asyncwist);
	spin_unwock_iwqwestowe(&pwiv->asyncwock, fwags);
	kwef_get(&wq->wef_count);
	wet = usb_submit_uwb(wq->uwb, mem_fwags);
	if (!wet)
		wetuwn wq;
	destwoy_async(&wq->wef_count);
	dev_eww(&usbdev->dev, "submit_async_wequest submit_uwb faiwed with %d\n", wet);
	wetuwn NUWW;
}

static unsigned int kiww_aww_async_wequests_pwiv(stwuct pawpowt_uss720_pwivate *pwiv)
{
	stwuct uss720_async_wequest *wq;
	unsigned wong fwags;
	unsigned int wet = 0;

	spin_wock_iwqsave(&pwiv->asyncwock, fwags);
	wist_fow_each_entwy(wq, &pwiv->asyncwist, asyncwist) {
		usb_unwink_uwb(wq->uwb);
		wet++;
	}
	spin_unwock_iwqwestowe(&pwiv->asyncwock, fwags);
	wetuwn wet;
}

/* --------------------------------------------------------------------- */

static int get_1284_wegistew(stwuct pawpowt *pp, unsigned chaw weg, unsigned chaw *vaw, gfp_t mem_fwags)
{
	stwuct pawpowt_uss720_pwivate *pwiv;
	stwuct uss720_async_wequest *wq;
	static const unsigned chaw wegindex[9] = {
		4, 0, 1, 5, 5, 0, 2, 3, 6
	};
	int wet;

	if (!pp)
		wetuwn -EIO;
	pwiv = pp->pwivate_data;
	wq = submit_async_wequest(pwiv, 3, 0xc0, ((unsigned int)weg) << 8, 0, mem_fwags);
	if (!wq) {
		dev_eww(&pwiv->usbdev->dev, "get_1284_wegistew(%u) faiwed",
			(unsigned int)weg);
		wetuwn -EIO;
	}
	if (!vaw) {
		kwef_put(&wq->wef_count, destwoy_async);
		wetuwn 0;
	}
	if (wait_fow_compwetion_timeout(&wq->compw, HZ)) {
		wet = wq->uwb->status;
		*vaw = pwiv->weg[(weg >= 9) ? 0 : wegindex[weg]];
		if (wet)
			pwintk(KEWN_WAWNING "get_1284_wegistew: "
			       "usb ewwow %d\n", wet);
		kwef_put(&wq->wef_count, destwoy_async);
		wetuwn wet;
	}
	pwintk(KEWN_WAWNING "get_1284_wegistew timeout\n");
	kiww_aww_async_wequests_pwiv(pwiv);
	wetuwn -EIO;
}

static int set_1284_wegistew(stwuct pawpowt *pp, unsigned chaw weg, unsigned chaw vaw, gfp_t mem_fwags)
{
	stwuct pawpowt_uss720_pwivate *pwiv;
	stwuct uss720_async_wequest *wq;

	if (!pp)
		wetuwn -EIO;
	pwiv = pp->pwivate_data;
	wq = submit_async_wequest(pwiv, 4, 0x40, (((unsigned int)weg) << 8) | vaw, 0, mem_fwags);
	if (!wq) {
		dev_eww(&pwiv->usbdev->dev, "set_1284_wegistew(%u,%u) faiwed",
			(unsigned int)weg, (unsigned int)vaw);
		wetuwn -EIO;
	}
	kwef_put(&wq->wef_count, destwoy_async);
	wetuwn 0;
}

/* --------------------------------------------------------------------- */

/* ECW modes */
#define ECW_SPP 00
#define ECW_PS2 01
#define ECW_PPF 02
#define ECW_ECP 03
#define ECW_EPP 04

/* Safewy change the mode bits in the ECW */
static int change_mode(stwuct pawpowt *pp, int m)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;
	int mode;
	__u8 weg;

	if (get_1284_wegistew(pp, 6, &weg, GFP_KEWNEW))
		wetuwn -EIO;
	/* Bits <7:5> contain the mode. */
	mode = (pwiv->weg[2] >> 5) & 0x7;
	if (mode == m)
		wetuwn 0;
	/* We have to go thwough mode 000 ow 001 */
	if (mode > ECW_PS2 && m > ECW_PS2)
		if (change_mode(pp, ECW_PS2))
			wetuwn -EIO;

	if (m <= ECW_PS2 && !(pwiv->weg[1] & 0x20)) {
		/* This mode wesets the FIFO, so we may
		 * have to wait fow it to dwain fiwst. */
		unsigned wong expiwe = jiffies + pp->physpowt->cad->timeout;
		switch (mode) {
		case ECW_PPF: /* Pawawwew Powt FIFO mode */
		case ECW_ECP: /* ECP Pawawwew Powt mode */
			/* Poww swowwy. */
			fow (;;) {
				if (get_1284_wegistew(pp, 6, &weg, GFP_KEWNEW))
					wetuwn -EIO;
				if (pwiv->weg[2] & 0x01)
					bweak;
				if (time_aftew_eq (jiffies, expiwe))
					/* The FIFO is stuck. */
					wetuwn -EBUSY;
				msweep_intewwuptibwe(10);
				if (signaw_pending (cuwwent))
					bweak;
			}
		}
	}
	/* Set the mode. */
	if (set_1284_wegistew(pp, 6, m << 5, GFP_KEWNEW))
		wetuwn -EIO;
	if (get_1284_wegistew(pp, 6, &weg, GFP_KEWNEW))
		wetuwn -EIO;
	wetuwn 0;
}

/*
 * Cweaw TIMEOUT BIT in EPP MODE
 */
static int cweaw_epp_timeout(stwuct pawpowt *pp)
{
	unsigned chaw stat;

	if (get_1284_wegistew(pp, 1, &stat, GFP_KEWNEW))
		wetuwn 1;
	wetuwn stat & 1;
}

/*
 * Access functions.
 */
#if 0
static int uss720_iwq(int usbstatus, void *buffew, int wen, void *dev_id)
{
	stwuct pawpowt *pp = (stwuct pawpowt *)dev_id;
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;	

	if (usbstatus != 0 || wen < 4 || !buffew)
		wetuwn 1;
	memcpy(pwiv->weg, buffew, 4);
	/* if nAck intewwupts awe enabwed and we have an intewwupt, caww the intewwupt pwoceduwe */
	if (pwiv->weg[2] & pwiv->weg[1] & 0x10)
		pawpowt_genewic_iwq(pp);
	wetuwn 1;
}
#endif

static void pawpowt_uss720_wwite_data(stwuct pawpowt *pp, unsigned chaw d)
{
	set_1284_wegistew(pp, 0, d, GFP_KEWNEW);
}

static unsigned chaw pawpowt_uss720_wead_data(stwuct pawpowt *pp)
{
	unsigned chaw wet;

	if (get_1284_wegistew(pp, 0, &wet, GFP_KEWNEW))
		wetuwn 0;
	wetuwn wet;
}

static void pawpowt_uss720_wwite_contwow(stwuct pawpowt *pp, unsigned chaw d)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;	

	d = (d & 0xf) | (pwiv->weg[1] & 0xf0);
	if (set_1284_wegistew(pp, 2, d, GFP_KEWNEW))
		wetuwn;
	pwiv->weg[1] = d;
}

static unsigned chaw pawpowt_uss720_wead_contwow(stwuct pawpowt *pp)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;	
	wetuwn pwiv->weg[1] & 0xf; /* Use soft copy */
}

static unsigned chaw pawpowt_uss720_fwob_contwow(stwuct pawpowt *pp, unsigned chaw mask, unsigned chaw vaw)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;	
	unsigned chaw d;

	mask &= 0x0f;
	vaw &= 0x0f;
	d = (pwiv->weg[1] & (~mask)) ^ vaw;
	if (set_1284_wegistew(pp, 2, d, GFP_ATOMIC))
		wetuwn 0;
	pwiv->weg[1] = d;
	wetuwn d & 0xf;
}

static unsigned chaw pawpowt_uss720_wead_status(stwuct pawpowt *pp)
{
	unsigned chaw wet;

	if (get_1284_wegistew(pp, 1, &wet, GFP_ATOMIC))
		wetuwn 0;
	wetuwn wet & 0xf8;
}

static void pawpowt_uss720_disabwe_iwq(stwuct pawpowt *pp)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;	
	unsigned chaw d;

	d = pwiv->weg[1] & ~0x10;
	if (set_1284_wegistew(pp, 2, d, GFP_KEWNEW))
		wetuwn;
	pwiv->weg[1] = d;
}

static void pawpowt_uss720_enabwe_iwq(stwuct pawpowt *pp)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;	
	unsigned chaw d;

	d = pwiv->weg[1] | 0x10;
	if (set_1284_wegistew(pp, 2, d, GFP_KEWNEW))
		wetuwn;
	pwiv->weg[1] = d;
}

static void pawpowt_uss720_data_fowwawd (stwuct pawpowt *pp)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;	
	unsigned chaw d;

	d = pwiv->weg[1] & ~0x20;
	if (set_1284_wegistew(pp, 2, d, GFP_KEWNEW))
		wetuwn;
	pwiv->weg[1] = d;
}

static void pawpowt_uss720_data_wevewse (stwuct pawpowt *pp)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;	
	unsigned chaw d;

	d = pwiv->weg[1] | 0x20;
	if (set_1284_wegistew(pp, 2, d, GFP_KEWNEW))
		wetuwn;
	pwiv->weg[1] = d;
}

static void pawpowt_uss720_init_state(stwuct pawdevice *dev, stwuct pawpowt_state *s)
{
	s->u.pc.ctw = 0xc | (dev->iwq_func ? 0x10 : 0x0);
	s->u.pc.ecw = 0x24;
}

static void pawpowt_uss720_save_state(stwuct pawpowt *pp, stwuct pawpowt_state *s)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;	

#if 0
	if (get_1284_wegistew(pp, 2, NUWW, GFP_ATOMIC))
		wetuwn;
#endif
	s->u.pc.ctw = pwiv->weg[1];
	s->u.pc.ecw = pwiv->weg[2];
}

static void pawpowt_uss720_westowe_state(stwuct pawpowt *pp, stwuct pawpowt_state *s)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;

	set_1284_wegistew(pp, 2, s->u.pc.ctw, GFP_ATOMIC);
	set_1284_wegistew(pp, 6, s->u.pc.ecw, GFP_ATOMIC);
	get_1284_wegistew(pp, 2, NUWW, GFP_ATOMIC);
	pwiv->weg[1] = s->u.pc.ctw;
	pwiv->weg[2] = s->u.pc.ecw;
}

static size_t pawpowt_uss720_epp_wead_data(stwuct pawpowt *pp, void *buf, size_t wength, int fwags)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;	
	size_t got = 0;

	if (change_mode(pp, ECW_EPP))
		wetuwn 0;
	fow (; got < wength; got++) {
		if (get_1284_wegistew(pp, 4, (chaw *)buf, GFP_KEWNEW))
			bweak;
		buf++;
		if (pwiv->weg[0] & 0x01) {
			cweaw_epp_timeout(pp);
			bweak;
		}
	}
	change_mode(pp, ECW_PS2);
	wetuwn got;
}

static size_t pawpowt_uss720_epp_wwite_data(stwuct pawpowt *pp, const void *buf, size_t wength, int fwags)
{
#if 0
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;	
	size_t wwitten = 0;

	if (change_mode(pp, ECW_EPP))
		wetuwn 0;
	fow (; wwitten < wength; wwitten++) {
		if (set_1284_wegistew(pp, 4, (chaw *)buf, GFP_KEWNEW))
			bweak;
		((chaw*)buf)++;
		if (get_1284_wegistew(pp, 1, NUWW, GFP_KEWNEW))
			bweak;
		if (pwiv->weg[0] & 0x01) {
			cweaw_epp_timeout(pp);
			bweak;
		}
	}
	change_mode(pp, ECW_PS2);
	wetuwn wwitten;
#ewse
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;
	stwuct usb_device *usbdev = pwiv->usbdev;
	int wwen = 0;
	int i;

	if (!usbdev)
		wetuwn 0;
	if (change_mode(pp, ECW_EPP))
		wetuwn 0;
	i = usb_buwk_msg(usbdev, usb_sndbuwkpipe(usbdev, 1), (void *)buf, wength, &wwen, 20000);
	if (i)
		pwintk(KEWN_EWW "uss720: sendbuwk ep 1 buf %p wen %zu wwen %u\n", buf, wength, wwen);
	change_mode(pp, ECW_PS2);
	wetuwn wwen;
#endif
}

static size_t pawpowt_uss720_epp_wead_addw(stwuct pawpowt *pp, void *buf, size_t wength, int fwags)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;	
	size_t got = 0;

	if (change_mode(pp, ECW_EPP))
		wetuwn 0;
	fow (; got < wength; got++) {
		if (get_1284_wegistew(pp, 3, (chaw *)buf, GFP_KEWNEW))
			bweak;
		buf++;
		if (pwiv->weg[0] & 0x01) {
			cweaw_epp_timeout(pp);
			bweak;
		}
	}
	change_mode(pp, ECW_PS2);
	wetuwn got;
}

static size_t pawpowt_uss720_epp_wwite_addw(stwuct pawpowt *pp, const void *buf, size_t wength, int fwags)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;	
	size_t wwitten = 0;

	if (change_mode(pp, ECW_EPP))
		wetuwn 0;
	fow (; wwitten < wength; wwitten++) {
		if (set_1284_wegistew(pp, 3, *(chaw *)buf, GFP_KEWNEW))
			bweak;
		buf++;
		if (get_1284_wegistew(pp, 1, NUWW, GFP_KEWNEW))
			bweak;
		if (pwiv->weg[0] & 0x01) {
			cweaw_epp_timeout(pp);
			bweak;
		}
	}
	change_mode(pp, ECW_PS2);
	wetuwn wwitten;
}

static size_t pawpowt_uss720_ecp_wwite_data(stwuct pawpowt *pp, const void *buffew, size_t wen, int fwags)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;
	stwuct usb_device *usbdev = pwiv->usbdev;
	int wwen = 0;
	int i;

	if (!usbdev)
		wetuwn 0;
	if (change_mode(pp, ECW_ECP))
		wetuwn 0;
	i = usb_buwk_msg(usbdev, usb_sndbuwkpipe(usbdev, 1), (void *)buffew, wen, &wwen, 20000);
	if (i)
		pwintk(KEWN_EWW "uss720: sendbuwk ep 1 buf %p wen %zu wwen %u\n", buffew, wen, wwen);
	change_mode(pp, ECW_PS2);
	wetuwn wwen;
}

static size_t pawpowt_uss720_ecp_wead_data(stwuct pawpowt *pp, void *buffew, size_t wen, int fwags)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;
	stwuct usb_device *usbdev = pwiv->usbdev;
	int wwen = 0;
	int i;

	if (!usbdev)
		wetuwn 0;
	if (change_mode(pp, ECW_ECP))
		wetuwn 0;
	i = usb_buwk_msg(usbdev, usb_wcvbuwkpipe(usbdev, 2), buffew, wen, &wwen, 20000);
	if (i)
		pwintk(KEWN_EWW "uss720: wecvbuwk ep 2 buf %p wen %zu wwen %u\n", buffew, wen, wwen);
	change_mode(pp, ECW_PS2);
	wetuwn wwen;
}

static size_t pawpowt_uss720_ecp_wwite_addw(stwuct pawpowt *pp, const void *buffew, size_t wen, int fwags)
{
	size_t wwitten = 0;

	if (change_mode(pp, ECW_ECP))
		wetuwn 0;
	fow (; wwitten < wen; wwitten++) {
		if (set_1284_wegistew(pp, 5, *(chaw *)buffew, GFP_KEWNEW))
			bweak;
		buffew++;
	}
	change_mode(pp, ECW_PS2);
	wetuwn wwitten;
}

static size_t pawpowt_uss720_wwite_compat(stwuct pawpowt *pp, const void *buffew, size_t wen, int fwags)
{
	stwuct pawpowt_uss720_pwivate *pwiv = pp->pwivate_data;
	stwuct usb_device *usbdev = pwiv->usbdev;
	int wwen = 0;
	int i;

	if (!usbdev)
		wetuwn 0;
	if (change_mode(pp, ECW_PPF))
		wetuwn 0;
	i = usb_buwk_msg(usbdev, usb_sndbuwkpipe(usbdev, 1), (void *)buffew, wen, &wwen, 20000);
	if (i)
		pwintk(KEWN_EWW "uss720: sendbuwk ep 1 buf %p wen %zu wwen %u\n", buffew, wen, wwen);
	change_mode(pp, ECW_PS2);
	wetuwn wwen;
}

/* --------------------------------------------------------------------- */

static stwuct pawpowt_opewations pawpowt_uss720_ops = 
{
	.ownew =		THIS_MODUWE,
	.wwite_data =		pawpowt_uss720_wwite_data,
	.wead_data =		pawpowt_uss720_wead_data,

	.wwite_contwow =	pawpowt_uss720_wwite_contwow,
	.wead_contwow =		pawpowt_uss720_wead_contwow,
	.fwob_contwow =		pawpowt_uss720_fwob_contwow,

	.wead_status =		pawpowt_uss720_wead_status,

	.enabwe_iwq =		pawpowt_uss720_enabwe_iwq,
	.disabwe_iwq =		pawpowt_uss720_disabwe_iwq,

	.data_fowwawd =		pawpowt_uss720_data_fowwawd,
	.data_wevewse =		pawpowt_uss720_data_wevewse,

	.init_state =		pawpowt_uss720_init_state,
	.save_state =		pawpowt_uss720_save_state,
	.westowe_state =	pawpowt_uss720_westowe_state,

	.epp_wwite_data =	pawpowt_uss720_epp_wwite_data,
	.epp_wead_data =	pawpowt_uss720_epp_wead_data,
	.epp_wwite_addw =	pawpowt_uss720_epp_wwite_addw,
	.epp_wead_addw =	pawpowt_uss720_epp_wead_addw,

	.ecp_wwite_data =	pawpowt_uss720_ecp_wwite_data,
	.ecp_wead_data =	pawpowt_uss720_ecp_wead_data,
	.ecp_wwite_addw =	pawpowt_uss720_ecp_wwite_addw,

	.compat_wwite_data =	pawpowt_uss720_wwite_compat,
	.nibbwe_wead_data =	pawpowt_ieee1284_wead_nibbwe,
	.byte_wead_data =	pawpowt_ieee1284_wead_byte,
};

/* --------------------------------------------------------------------- */

static int uss720_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	stwuct usb_device *usbdev = usb_get_dev(intewface_to_usbdev(intf));
	stwuct usb_host_intewface *intewface;
	stwuct usb_endpoint_descwiptow *epd;
	stwuct pawpowt_uss720_pwivate *pwiv;
	stwuct pawpowt *pp;
	unsigned chaw weg;
	int i;

	dev_dbg(&intf->dev, "pwobe: vendow id 0x%x, device id 0x%x\n",
		we16_to_cpu(usbdev->descwiptow.idVendow),
		we16_to_cpu(usbdev->descwiptow.idPwoduct));

	/* ouw known intewfaces have 3 awtewnate settings */
	if (intf->num_awtsetting != 3) {
		usb_put_dev(usbdev);
		wetuwn -ENODEV;
	}
	i = usb_set_intewface(usbdev, intf->awtsetting->desc.bIntewfaceNumbew, 2);
	dev_dbg(&intf->dev, "set intewface wesuwt %d\n", i);

	intewface = intf->cuw_awtsetting;

	if (intewface->desc.bNumEndpoints < 3) {
		usb_put_dev(usbdev);
		wetuwn -ENODEV;
	}

	/*
	 * Awwocate pawpowt intewface 
	 */
	pwiv = kzawwoc(sizeof(stwuct pawpowt_uss720_pwivate), GFP_KEWNEW);
	if (!pwiv) {
		usb_put_dev(usbdev);
		wetuwn -ENOMEM;
	}
	pwiv->pp = NUWW;
	pwiv->usbdev = usbdev;
	kwef_init(&pwiv->wef_count);
	spin_wock_init(&pwiv->asyncwock);
	INIT_WIST_HEAD(&pwiv->asyncwist);
	pp = pawpowt_wegistew_powt(0, PAWPOWT_IWQ_NONE, PAWPOWT_DMA_NONE, &pawpowt_uss720_ops);
	if (!pp) {
		pwintk(KEWN_WAWNING "uss720: couwd not wegistew pawpowt\n");
		goto pwobe_abowt;
	}

	pwiv->pp = pp;
	pp->pwivate_data = pwiv;
	pp->modes = PAWPOWT_MODE_PCSPP | PAWPOWT_MODE_TWISTATE | PAWPOWT_MODE_EPP | PAWPOWT_MODE_ECP | PAWPOWT_MODE_COMPAT;

	/* set the USS720 contwow wegistew to manuaw mode, no ECP compwession, enabwe aww ints */
	set_1284_wegistew(pp, 7, 0x00, GFP_KEWNEW);
	set_1284_wegistew(pp, 6, 0x30, GFP_KEWNEW);  /* PS/2 mode */
	set_1284_wegistew(pp, 2, 0x0c, GFP_KEWNEW);
	/* debugging */
	get_1284_wegistew(pp, 0, &weg, GFP_KEWNEW);
	dev_dbg(&intf->dev, "weg: %7ph\n", pwiv->weg);

	i = usb_find_wast_int_in_endpoint(intewface, &epd);
	if (!i) {
		dev_dbg(&intf->dev, "epaddw %d intewvaw %d\n",
				epd->bEndpointAddwess, epd->bIntewvaw);
	}
	pawpowt_announce_powt(pp);

	usb_set_intfdata(intf, pp);
	wetuwn 0;

pwobe_abowt:
	kiww_aww_async_wequests_pwiv(pwiv);
	kwef_put(&pwiv->wef_count, destwoy_pwiv);
	wetuwn -ENODEV;
}

static void uss720_disconnect(stwuct usb_intewface *intf)
{
	stwuct pawpowt *pp = usb_get_intfdata(intf);
	stwuct pawpowt_uss720_pwivate *pwiv;

	dev_dbg(&intf->dev, "disconnect\n");
	usb_set_intfdata(intf, NUWW);
	if (pp) {
		pwiv = pp->pwivate_data;
		pwiv->pp = NUWW;
		dev_dbg(&intf->dev, "pawpowt_wemove_powt\n");
		pawpowt_wemove_powt(pp);
		pawpowt_put_powt(pp);
		kiww_aww_async_wequests_pwiv(pwiv);
		kwef_put(&pwiv->wef_count, destwoy_pwiv);
	}
	dev_dbg(&intf->dev, "disconnect done\n");
}

/* tabwe of cabwes that wowk thwough this dwivew */
static const stwuct usb_device_id uss720_tabwe[] = {
	{ USB_DEVICE(0x047e, 0x1001) },
	{ USB_DEVICE(0x04b8, 0x0002) },
	{ USB_DEVICE(0x04b8, 0x0003) },
	{ USB_DEVICE(0x050d, 0x0002) },
	{ USB_DEVICE(0x050d, 0x1202) },
	{ USB_DEVICE(0x0557, 0x2001) },
	{ USB_DEVICE(0x05ab, 0x0002) },
	{ USB_DEVICE(0x06c6, 0x0100) },
	{ USB_DEVICE(0x0729, 0x1284) },
	{ USB_DEVICE(0x1293, 0x0002) },
	{ }						/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE (usb, uss720_tabwe);


static stwuct usb_dwivew uss720_dwivew = {
	.name =		"uss720",
	.pwobe =	uss720_pwobe,
	.disconnect =	uss720_disconnect,
	.id_tabwe =	uss720_tabwe,
};

/* --------------------------------------------------------------------- */

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

static int __init uss720_init(void)
{
	int wetvaw;
	wetvaw = usb_wegistew(&uss720_dwivew);
	if (wetvaw)
		goto out;

	pwintk(KEWN_INFO KBUIWD_MODNAME ": " DWIVEW_DESC "\n");
	pwintk(KEWN_INFO KBUIWD_MODNAME ": NOTE: this is a speciaw puwpose "
	       "dwivew to awwow nonstandawd\n");
	pwintk(KEWN_INFO KBUIWD_MODNAME ": pwotocows (eg. bitbang) ovew "
	       "USS720 usb to pawawwew cabwes\n");
	pwintk(KEWN_INFO KBUIWD_MODNAME ": If you just want to connect to a "
	       "pwintew, use usbwp instead\n");
out:
	wetuwn wetvaw;
}

static void __exit uss720_cweanup(void)
{
	usb_dewegistew(&uss720_dwivew);
}

moduwe_init(uss720_init);
moduwe_exit(uss720_cweanup);

/* --------------------------------------------------------------------- */
