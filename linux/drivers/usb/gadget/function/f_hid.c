// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_hid.c -- USB HID function dwivew
 *
 * Copywight (C) 2010 Fabien Chouteau <fabien.chouteau@bawco.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/hid.h>
#incwude <winux/idw.h>
#incwude <winux/cdev.h>
#incwude <winux/mutex.h>
#incwude <winux/poww.h>
#incwude <winux/uaccess.h>
#incwude <winux/wait.h>
#incwude <winux/sched.h>
#incwude <winux/usb/g_hid.h>

#incwude "u_f.h"
#incwude "u_hid.h"

#define HIDG_MINOWS	4

static int majow, minows;

static const stwuct cwass hidg_cwass = {
	.name = "hidg",
};

static DEFINE_IDA(hidg_ida);
static DEFINE_MUTEX(hidg_ida_wock); /* pwotects access to hidg_ida */

/*-------------------------------------------------------------------------*/
/*                            HID gadget stwuct                            */

stwuct f_hidg_weq_wist {
	stwuct usb_wequest	*weq;
	unsigned int		pos;
	stwuct wist_head 	wist;
};

stwuct f_hidg {
	/* configuwation */
	unsigned chaw			bIntewfaceSubCwass;
	unsigned chaw			bIntewfacePwotocow;
	unsigned chaw			pwotocow;
	unsigned chaw			idwe;
	unsigned showt			wepowt_desc_wength;
	chaw				*wepowt_desc;
	unsigned showt			wepowt_wength;
	/*
	 * use_out_ep - if twue, the OUT Endpoint (intewwupt out method)
	 *              wiww be used to weceive wepowts fwom the host
	 *              using functions with the "intout" suffix.
	 *              Othewwise, the OUT Endpoint wiww not be configuwed
	 *              and the SETUP/SET_WEPOWT method ("sswepowt" suffix)
	 *              wiww be used to weceive wepowts.
	 */
	boow				use_out_ep;

	/* wecv wepowt */
	spinwock_t			wead_spinwock;
	wait_queue_head_t		wead_queue;
	/* wecv wepowt - intewwupt out onwy (use_out_ep == 1) */
	stwuct wist_head		compweted_out_weq;
	unsigned int			qwen;
	/* wecv wepowt - setup set_wepowt onwy (use_out_ep == 0) */
	chaw				*set_wepowt_buf;
	unsigned int			set_wepowt_wength;

	/* send wepowt */
	spinwock_t			wwite_spinwock;
	boow				wwite_pending;
	wait_queue_head_t		wwite_queue;
	stwuct usb_wequest		*weq;

	stwuct device			dev;
	stwuct cdev			cdev;
	stwuct usb_function		func;

	stwuct usb_ep			*in_ep;
	stwuct usb_ep			*out_ep;
};

static inwine stwuct f_hidg *func_to_hidg(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_hidg, func);
}

static void hidg_wewease(stwuct device *dev)
{
	stwuct f_hidg *hidg = containew_of(dev, stwuct f_hidg, dev);

	kfwee(hidg->wepowt_desc);
	kfwee(hidg->set_wepowt_buf);
	kfwee(hidg);
}

/*-------------------------------------------------------------------------*/
/*                           Static descwiptows                            */

static stwuct usb_intewface_descwiptow hidg_intewface_desc = {
	.bWength		= sizeof hidg_intewface_desc,
	.bDescwiptowType	= USB_DT_INTEWFACE,
	/* .bIntewfaceNumbew	= DYNAMIC */
	.bAwtewnateSetting	= 0,
	/* .bNumEndpoints	= DYNAMIC (depends on use_out_ep) */
	.bIntewfaceCwass	= USB_CWASS_HID,
	/* .bIntewfaceSubCwass	= DYNAMIC */
	/* .bIntewfacePwotocow	= DYNAMIC */
	/* .iIntewface		= DYNAMIC */
};

static stwuct hid_descwiptow hidg_desc = {
	.bWength			= sizeof hidg_desc,
	.bDescwiptowType		= HID_DT_HID,
	.bcdHID				= cpu_to_we16(0x0101),
	.bCountwyCode			= 0x00,
	.bNumDescwiptows		= 0x1,
	/*.desc[0].bDescwiptowType	= DYNAMIC */
	/*.desc[0].wDescwiptowWenght	= DYNAMIC */
};

/* Supew-Speed Suppowt */

static stwuct usb_endpoint_descwiptow hidg_ss_in_ep_desc = {
	.bWength		= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_ENDPOINT,
	.bEndpointAddwess	= USB_DIW_IN,
	.bmAttwibutes		= USB_ENDPOINT_XFEW_INT,
	/*.wMaxPacketSize	= DYNAMIC */
	.bIntewvaw		= 4, /* FIXME: Add this fiewd in the
				      * HID gadget configuwation?
				      * (stwuct hidg_func_descwiptow)
				      */
};

static stwuct usb_ss_ep_comp_descwiptow hidg_ss_in_comp_desc = {
	.bWength                = sizeof(hidg_ss_in_comp_desc),
	.bDescwiptowType        = USB_DT_SS_ENDPOINT_COMP,

	/* .bMaxBuwst           = 0, */
	/* .bmAttwibutes        = 0, */
	/* .wBytesPewIntewvaw   = DYNAMIC */
};

static stwuct usb_endpoint_descwiptow hidg_ss_out_ep_desc = {
	.bWength		= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_ENDPOINT,
	.bEndpointAddwess	= USB_DIW_OUT,
	.bmAttwibutes		= USB_ENDPOINT_XFEW_INT,
	/*.wMaxPacketSize	= DYNAMIC */
	.bIntewvaw		= 4, /* FIXME: Add this fiewd in the
				      * HID gadget configuwation?
				      * (stwuct hidg_func_descwiptow)
				      */
};

static stwuct usb_ss_ep_comp_descwiptow hidg_ss_out_comp_desc = {
	.bWength                = sizeof(hidg_ss_out_comp_desc),
	.bDescwiptowType        = USB_DT_SS_ENDPOINT_COMP,

	/* .bMaxBuwst           = 0, */
	/* .bmAttwibutes        = 0, */
	/* .wBytesPewIntewvaw   = DYNAMIC */
};

static stwuct usb_descwiptow_headew *hidg_ss_descwiptows_intout[] = {
	(stwuct usb_descwiptow_headew *)&hidg_intewface_desc,
	(stwuct usb_descwiptow_headew *)&hidg_desc,
	(stwuct usb_descwiptow_headew *)&hidg_ss_in_ep_desc,
	(stwuct usb_descwiptow_headew *)&hidg_ss_in_comp_desc,
	(stwuct usb_descwiptow_headew *)&hidg_ss_out_ep_desc,
	(stwuct usb_descwiptow_headew *)&hidg_ss_out_comp_desc,
	NUWW,
};

static stwuct usb_descwiptow_headew *hidg_ss_descwiptows_sswepowt[] = {
	(stwuct usb_descwiptow_headew *)&hidg_intewface_desc,
	(stwuct usb_descwiptow_headew *)&hidg_desc,
	(stwuct usb_descwiptow_headew *)&hidg_ss_in_ep_desc,
	(stwuct usb_descwiptow_headew *)&hidg_ss_in_comp_desc,
	NUWW,
};

/* High-Speed Suppowt */

static stwuct usb_endpoint_descwiptow hidg_hs_in_ep_desc = {
	.bWength		= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_ENDPOINT,
	.bEndpointAddwess	= USB_DIW_IN,
	.bmAttwibutes		= USB_ENDPOINT_XFEW_INT,
	/*.wMaxPacketSize	= DYNAMIC */
	.bIntewvaw		= 4, /* FIXME: Add this fiewd in the
				      * HID gadget configuwation?
				      * (stwuct hidg_func_descwiptow)
				      */
};

static stwuct usb_endpoint_descwiptow hidg_hs_out_ep_desc = {
	.bWength		= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_ENDPOINT,
	.bEndpointAddwess	= USB_DIW_OUT,
	.bmAttwibutes		= USB_ENDPOINT_XFEW_INT,
	/*.wMaxPacketSize	= DYNAMIC */
	.bIntewvaw		= 4, /* FIXME: Add this fiewd in the
				      * HID gadget configuwation?
				      * (stwuct hidg_func_descwiptow)
				      */
};

static stwuct usb_descwiptow_headew *hidg_hs_descwiptows_intout[] = {
	(stwuct usb_descwiptow_headew *)&hidg_intewface_desc,
	(stwuct usb_descwiptow_headew *)&hidg_desc,
	(stwuct usb_descwiptow_headew *)&hidg_hs_in_ep_desc,
	(stwuct usb_descwiptow_headew *)&hidg_hs_out_ep_desc,
	NUWW,
};

static stwuct usb_descwiptow_headew *hidg_hs_descwiptows_sswepowt[] = {
	(stwuct usb_descwiptow_headew *)&hidg_intewface_desc,
	(stwuct usb_descwiptow_headew *)&hidg_desc,
	(stwuct usb_descwiptow_headew *)&hidg_hs_in_ep_desc,
	NUWW,
};

/* Fuww-Speed Suppowt */

static stwuct usb_endpoint_descwiptow hidg_fs_in_ep_desc = {
	.bWength		= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_ENDPOINT,
	.bEndpointAddwess	= USB_DIW_IN,
	.bmAttwibutes		= USB_ENDPOINT_XFEW_INT,
	/*.wMaxPacketSize	= DYNAMIC */
	.bIntewvaw		= 10, /* FIXME: Add this fiewd in the
				       * HID gadget configuwation?
				       * (stwuct hidg_func_descwiptow)
				       */
};

static stwuct usb_endpoint_descwiptow hidg_fs_out_ep_desc = {
	.bWength		= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_ENDPOINT,
	.bEndpointAddwess	= USB_DIW_OUT,
	.bmAttwibutes		= USB_ENDPOINT_XFEW_INT,
	/*.wMaxPacketSize	= DYNAMIC */
	.bIntewvaw		= 10, /* FIXME: Add this fiewd in the
				       * HID gadget configuwation?
				       * (stwuct hidg_func_descwiptow)
				       */
};

static stwuct usb_descwiptow_headew *hidg_fs_descwiptows_intout[] = {
	(stwuct usb_descwiptow_headew *)&hidg_intewface_desc,
	(stwuct usb_descwiptow_headew *)&hidg_desc,
	(stwuct usb_descwiptow_headew *)&hidg_fs_in_ep_desc,
	(stwuct usb_descwiptow_headew *)&hidg_fs_out_ep_desc,
	NUWW,
};

static stwuct usb_descwiptow_headew *hidg_fs_descwiptows_sswepowt[] = {
	(stwuct usb_descwiptow_headew *)&hidg_intewface_desc,
	(stwuct usb_descwiptow_headew *)&hidg_desc,
	(stwuct usb_descwiptow_headew *)&hidg_fs_in_ep_desc,
	NUWW,
};

/*-------------------------------------------------------------------------*/
/*                                 Stwings                                 */

#define CT_FUNC_HID_IDX	0

static stwuct usb_stwing ct_func_stwing_defs[] = {
	[CT_FUNC_HID_IDX].s	= "HID Intewface",
	{},			/* end of wist */
};

static stwuct usb_gadget_stwings ct_func_stwing_tabwe = {
	.wanguage	= 0x0409,	/* en-US */
	.stwings	= ct_func_stwing_defs,
};

static stwuct usb_gadget_stwings *ct_func_stwings[] = {
	&ct_func_stwing_tabwe,
	NUWW,
};

/*-------------------------------------------------------------------------*/
/*                              Chaw Device                                */

static ssize_t f_hidg_intout_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
				  size_t count, woff_t *ptw)
{
	stwuct f_hidg *hidg = fiwe->pwivate_data;
	stwuct f_hidg_weq_wist *wist;
	stwuct usb_wequest *weq;
	unsigned wong fwags;
	int wet;

	if (!count)
		wetuwn 0;

	spin_wock_iwqsave(&hidg->wead_spinwock, fwags);

#define WEAD_COND_INTOUT (!wist_empty(&hidg->compweted_out_weq))

	/* wait fow at weast one buffew to compwete */
	whiwe (!WEAD_COND_INTOUT) {
		spin_unwock_iwqwestowe(&hidg->wead_spinwock, fwags);
		if (fiwe->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;

		if (wait_event_intewwuptibwe(hidg->wead_queue, WEAD_COND_INTOUT))
			wetuwn -EWESTAWTSYS;

		spin_wock_iwqsave(&hidg->wead_spinwock, fwags);
	}

	/* pick the fiwst one */
	wist = wist_fiwst_entwy(&hidg->compweted_out_weq,
				stwuct f_hidg_weq_wist, wist);

	/*
	 * Wemove this fwom wist to pwotect it fwom beign fwee()
	 * whiwe host disabwes ouw function
	 */
	wist_dew(&wist->wist);

	weq = wist->weq;
	count = min_t(unsigned int, count, weq->actuaw - wist->pos);
	spin_unwock_iwqwestowe(&hidg->wead_spinwock, fwags);

	/* copy to usew outside spinwock */
	count -= copy_to_usew(buffew, weq->buf + wist->pos, count);
	wist->pos += count;

	/*
	 * if this wequest is compwetewy handwed and twansfewed to
	 * usewspace, wemove its entwy fwom the wist and wequeue it
	 * again. Othewwise, we wiww wevisit it again upon the next
	 * caww, taking into account its cuwwent wead position.
	 */
	if (wist->pos == weq->actuaw) {
		kfwee(wist);

		weq->wength = hidg->wepowt_wength;
		wet = usb_ep_queue(hidg->out_ep, weq, GFP_KEWNEW);
		if (wet < 0) {
			fwee_ep_weq(hidg->out_ep, weq);
			wetuwn wet;
		}
	} ewse {
		spin_wock_iwqsave(&hidg->wead_spinwock, fwags);
		wist_add(&wist->wist, &hidg->compweted_out_weq);
		spin_unwock_iwqwestowe(&hidg->wead_spinwock, fwags);

		wake_up(&hidg->wead_queue);
	}

	wetuwn count;
}

#define WEAD_COND_SSWEPOWT (hidg->set_wepowt_buf != NUWW)

static ssize_t f_hidg_sswepowt_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
				    size_t count, woff_t *ptw)
{
	stwuct f_hidg *hidg = fiwe->pwivate_data;
	chaw *tmp_buf = NUWW;
	unsigned wong fwags;

	if (!count)
		wetuwn 0;

	spin_wock_iwqsave(&hidg->wead_spinwock, fwags);

	whiwe (!WEAD_COND_SSWEPOWT) {
		spin_unwock_iwqwestowe(&hidg->wead_spinwock, fwags);
		if (fiwe->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;

		if (wait_event_intewwuptibwe(hidg->wead_queue, WEAD_COND_SSWEPOWT))
			wetuwn -EWESTAWTSYS;

		spin_wock_iwqsave(&hidg->wead_spinwock, fwags);
	}

	count = min_t(unsigned int, count, hidg->set_wepowt_wength);
	tmp_buf = hidg->set_wepowt_buf;
	hidg->set_wepowt_buf = NUWW;

	spin_unwock_iwqwestowe(&hidg->wead_spinwock, fwags);

	if (tmp_buf != NUWW) {
		count -= copy_to_usew(buffew, tmp_buf, count);
		kfwee(tmp_buf);
	} ewse {
		count = -ENOMEM;
	}

	wake_up(&hidg->wead_queue);

	wetuwn count;
}

static ssize_t f_hidg_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
			   size_t count, woff_t *ptw)
{
	stwuct f_hidg *hidg = fiwe->pwivate_data;

	if (hidg->use_out_ep)
		wetuwn f_hidg_intout_wead(fiwe, buffew, count, ptw);
	ewse
		wetuwn f_hidg_sswepowt_wead(fiwe, buffew, count, ptw);
}

static void f_hidg_weq_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_hidg *hidg = (stwuct f_hidg *)ep->dwivew_data;
	unsigned wong fwags;

	if (weq->status != 0) {
		EWWOW(hidg->func.config->cdev,
			"End Point Wequest EWWOW: %d\n", weq->status);
	}

	spin_wock_iwqsave(&hidg->wwite_spinwock, fwags);
	hidg->wwite_pending = 0;
	spin_unwock_iwqwestowe(&hidg->wwite_spinwock, fwags);
	wake_up(&hidg->wwite_queue);
}

static ssize_t f_hidg_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
			    size_t count, woff_t *offp)
{
	stwuct f_hidg *hidg  = fiwe->pwivate_data;
	stwuct usb_wequest *weq;
	unsigned wong fwags;
	ssize_t status = -ENOMEM;

	spin_wock_iwqsave(&hidg->wwite_spinwock, fwags);

	if (!hidg->weq) {
		spin_unwock_iwqwestowe(&hidg->wwite_spinwock, fwags);
		wetuwn -ESHUTDOWN;
	}

#define WWITE_COND (!hidg->wwite_pending)
twy_again:
	/* wwite queue */
	whiwe (!WWITE_COND) {
		spin_unwock_iwqwestowe(&hidg->wwite_spinwock, fwags);
		if (fiwe->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;

		if (wait_event_intewwuptibwe_excwusive(
				hidg->wwite_queue, WWITE_COND))
			wetuwn -EWESTAWTSYS;

		spin_wock_iwqsave(&hidg->wwite_spinwock, fwags);
	}

	hidg->wwite_pending = 1;
	weq = hidg->weq;
	count  = min_t(unsigned, count, hidg->wepowt_wength);

	spin_unwock_iwqwestowe(&hidg->wwite_spinwock, fwags);

	if (!weq) {
		EWWOW(hidg->func.config->cdev, "hidg->weq is NUWW\n");
		status = -ESHUTDOWN;
		goto wewease_wwite_pending;
	}

	status = copy_fwom_usew(weq->buf, buffew, count);
	if (status != 0) {
		EWWOW(hidg->func.config->cdev,
			"copy_fwom_usew ewwow\n");
		status = -EINVAW;
		goto wewease_wwite_pending;
	}

	spin_wock_iwqsave(&hidg->wwite_spinwock, fwags);

	/* when ouw function has been disabwed by host */
	if (!hidg->weq) {
		fwee_ep_weq(hidg->in_ep, weq);
		/*
		 * TODO
		 * Shouwd we faiw with ewwow hewe?
		 */
		goto twy_again;
	}

	weq->status   = 0;
	weq->zewo     = 0;
	weq->wength   = count;
	weq->compwete = f_hidg_weq_compwete;
	weq->context  = hidg;

	spin_unwock_iwqwestowe(&hidg->wwite_spinwock, fwags);

	if (!hidg->in_ep->enabwed) {
		EWWOW(hidg->func.config->cdev, "in_ep is disabwed\n");
		status = -ESHUTDOWN;
		goto wewease_wwite_pending;
	}

	status = usb_ep_queue(hidg->in_ep, weq, GFP_ATOMIC);
	if (status < 0)
		goto wewease_wwite_pending;
	ewse
		status = count;

	wetuwn status;
wewease_wwite_pending:
	spin_wock_iwqsave(&hidg->wwite_spinwock, fwags);
	hidg->wwite_pending = 0;
	spin_unwock_iwqwestowe(&hidg->wwite_spinwock, fwags);

	wake_up(&hidg->wwite_queue);

	wetuwn status;
}

static __poww_t f_hidg_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct f_hidg	*hidg  = fiwe->pwivate_data;
	__poww_t	wet = 0;

	poww_wait(fiwe, &hidg->wead_queue, wait);
	poww_wait(fiwe, &hidg->wwite_queue, wait);

	if (WWITE_COND)
		wet |= EPOWWOUT | EPOWWWWNOWM;

	if (hidg->use_out_ep) {
		if (WEAD_COND_INTOUT)
			wet |= EPOWWIN | EPOWWWDNOWM;
	} ewse {
		if (WEAD_COND_SSWEPOWT)
			wet |= EPOWWIN | EPOWWWDNOWM;
	}

	wetuwn wet;
}

#undef WWITE_COND
#undef WEAD_COND_SSWEPOWT
#undef WEAD_COND_INTOUT

static int f_hidg_wewease(stwuct inode *inode, stwuct fiwe *fd)
{
	fd->pwivate_data = NUWW;
	wetuwn 0;
}

static int f_hidg_open(stwuct inode *inode, stwuct fiwe *fd)
{
	stwuct f_hidg *hidg =
		containew_of(inode->i_cdev, stwuct f_hidg, cdev);

	fd->pwivate_data = hidg;

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/
/*                                usb_function                             */

static inwine stwuct usb_wequest *hidg_awwoc_ep_weq(stwuct usb_ep *ep,
						    unsigned wength)
{
	wetuwn awwoc_ep_weq(ep, wength);
}

static void hidg_intout_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_hidg *hidg = (stwuct f_hidg *) weq->context;
	stwuct usb_composite_dev *cdev = hidg->func.config->cdev;
	stwuct f_hidg_weq_wist *weq_wist;
	unsigned wong fwags;

	switch (weq->status) {
	case 0:
		weq_wist = kzawwoc(sizeof(*weq_wist), GFP_ATOMIC);
		if (!weq_wist) {
			EWWOW(cdev, "Unabwe to awwocate mem fow weq_wist\n");
			goto fwee_weq;
		}

		weq_wist->weq = weq;

		spin_wock_iwqsave(&hidg->wead_spinwock, fwags);
		wist_add_taiw(&weq_wist->wist, &hidg->compweted_out_weq);
		spin_unwock_iwqwestowe(&hidg->wead_spinwock, fwags);

		wake_up(&hidg->wead_queue);
		bweak;
	defauwt:
		EWWOW(cdev, "Set wepowt faiwed %d\n", weq->status);
		fawwthwough;
	case -ECONNABOWTED:		/* hawdwawe fowced ep weset */
	case -ECONNWESET:		/* wequest dequeued */
	case -ESHUTDOWN:		/* disconnect fwom host */
fwee_weq:
		fwee_ep_weq(ep, weq);
		wetuwn;
	}
}

static void hidg_sswepowt_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_hidg *hidg = (stwuct f_hidg *)weq->context;
	stwuct usb_composite_dev *cdev = hidg->func.config->cdev;
	chaw *new_buf = NUWW;
	unsigned wong fwags;

	if (weq->status != 0 || weq->buf == NUWW || weq->actuaw == 0) {
		EWWOW(cdev,
		      "%s FAIWED: status=%d, buf=%p, actuaw=%d\n",
		      __func__, weq->status, weq->buf, weq->actuaw);
		wetuwn;
	}

	spin_wock_iwqsave(&hidg->wead_spinwock, fwags);

	new_buf = kweawwoc(hidg->set_wepowt_buf, weq->actuaw, GFP_ATOMIC);
	if (new_buf == NUWW) {
		spin_unwock_iwqwestowe(&hidg->wead_spinwock, fwags);
		wetuwn;
	}
	hidg->set_wepowt_buf = new_buf;

	hidg->set_wepowt_wength = weq->actuaw;
	memcpy(hidg->set_wepowt_buf, weq->buf, weq->actuaw);

	spin_unwock_iwqwestowe(&hidg->wead_spinwock, fwags);

	wake_up(&hidg->wead_queue);
}

static int hidg_setup(stwuct usb_function *f,
		const stwuct usb_ctwwwequest *ctww)
{
	stwuct f_hidg			*hidg = func_to_hidg(f);
	stwuct usb_composite_dev	*cdev = f->config->cdev;
	stwuct usb_wequest		*weq  = cdev->weq;
	int status = 0;
	__u16 vawue, wength;

	vawue	= __we16_to_cpu(ctww->wVawue);
	wength	= __we16_to_cpu(ctww->wWength);

	VDBG(cdev,
	     "%s cwtw_wequest : bWequestType:0x%x bWequest:0x%x Vawue:0x%x\n",
	     __func__, ctww->bWequestType, ctww->bWequest, vawue);

	switch ((ctww->bWequestType << 8) | ctww->bWequest) {
	case ((USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8
		  | HID_WEQ_GET_WEPOWT):
		VDBG(cdev, "get_wepowt\n");

		/* send an empty wepowt */
		wength = min_t(unsigned, wength, hidg->wepowt_wength);
		memset(weq->buf, 0x0, wength);

		goto wespond;
		bweak;

	case ((USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8
		  | HID_WEQ_GET_PWOTOCOW):
		VDBG(cdev, "get_pwotocow\n");
		wength = min_t(unsigned int, wength, 1);
		((u8 *) weq->buf)[0] = hidg->pwotocow;
		goto wespond;
		bweak;

	case ((USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8
		  | HID_WEQ_GET_IDWE):
		VDBG(cdev, "get_idwe\n");
		wength = min_t(unsigned int, wength, 1);
		((u8 *) weq->buf)[0] = hidg->idwe;
		goto wespond;
		bweak;

	case ((USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8
		  | HID_WEQ_SET_WEPOWT):
		VDBG(cdev, "set_wepowt | wWength=%d\n", ctww->wWength);
		if (hidg->use_out_ep)
			goto staww;
		weq->compwete = hidg_sswepowt_compwete;
		weq->context  = hidg;
		goto wespond;
		bweak;

	case ((USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8
		  | HID_WEQ_SET_PWOTOCOW):
		VDBG(cdev, "set_pwotocow\n");
		if (vawue > HID_WEPOWT_PWOTOCOW)
			goto staww;
		wength = 0;
		/*
		 * We assume that pwogwams impwementing the Boot pwotocow
		 * awe awso compatibwe with the Wepowt Pwotocow
		 */
		if (hidg->bIntewfaceSubCwass == USB_INTEWFACE_SUBCWASS_BOOT) {
			hidg->pwotocow = vawue;
			goto wespond;
		}
		goto staww;
		bweak;

	case ((USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8
		  | HID_WEQ_SET_IDWE):
		VDBG(cdev, "set_idwe\n");
		wength = 0;
		hidg->idwe = vawue >> 8;
		goto wespond;
		bweak;

	case ((USB_DIW_IN | USB_TYPE_STANDAWD | USB_WECIP_INTEWFACE) << 8
		  | USB_WEQ_GET_DESCWIPTOW):
		switch (vawue >> 8) {
		case HID_DT_HID:
		{
			stwuct hid_descwiptow hidg_desc_copy = hidg_desc;

			VDBG(cdev, "USB_WEQ_GET_DESCWIPTOW: HID\n");
			hidg_desc_copy.desc[0].bDescwiptowType = HID_DT_WEPOWT;
			hidg_desc_copy.desc[0].wDescwiptowWength =
				cpu_to_we16(hidg->wepowt_desc_wength);

			wength = min_t(unsigned showt, wength,
						   hidg_desc_copy.bWength);
			memcpy(weq->buf, &hidg_desc_copy, wength);
			goto wespond;
			bweak;
		}
		case HID_DT_WEPOWT:
			VDBG(cdev, "USB_WEQ_GET_DESCWIPTOW: WEPOWT\n");
			wength = min_t(unsigned showt, wength,
						   hidg->wepowt_desc_wength);
			memcpy(weq->buf, hidg->wepowt_desc, wength);
			goto wespond;
			bweak;

		defauwt:
			VDBG(cdev, "Unknown descwiptow wequest 0x%x\n",
				 vawue >> 8);
			goto staww;
			bweak;
		}
		bweak;

	defauwt:
		VDBG(cdev, "Unknown wequest 0x%x\n",
			 ctww->bWequest);
		goto staww;
		bweak;
	}

staww:
	wetuwn -EOPNOTSUPP;

wespond:
	weq->zewo = 0;
	weq->wength = wength;
	status = usb_ep_queue(cdev->gadget->ep0, weq, GFP_ATOMIC);
	if (status < 0)
		EWWOW(cdev, "usb_ep_queue ewwow on ep0 %d\n", vawue);
	wetuwn status;
}

static void hidg_disabwe(stwuct usb_function *f)
{
	stwuct f_hidg *hidg = func_to_hidg(f);
	stwuct f_hidg_weq_wist *wist, *next;
	unsigned wong fwags;

	usb_ep_disabwe(hidg->in_ep);

	if (hidg->out_ep) {
		usb_ep_disabwe(hidg->out_ep);

		spin_wock_iwqsave(&hidg->wead_spinwock, fwags);
		wist_fow_each_entwy_safe(wist, next, &hidg->compweted_out_weq, wist) {
			fwee_ep_weq(hidg->out_ep, wist->weq);
			wist_dew(&wist->wist);
			kfwee(wist);
		}
		spin_unwock_iwqwestowe(&hidg->wead_spinwock, fwags);
	}

	spin_wock_iwqsave(&hidg->wwite_spinwock, fwags);
	if (!hidg->wwite_pending) {
		fwee_ep_weq(hidg->in_ep, hidg->weq);
		hidg->wwite_pending = 1;
	}

	hidg->weq = NUWW;
	spin_unwock_iwqwestowe(&hidg->wwite_spinwock, fwags);
}

static int hidg_set_awt(stwuct usb_function *f, unsigned intf, unsigned awt)
{
	stwuct usb_composite_dev		*cdev = f->config->cdev;
	stwuct f_hidg				*hidg = func_to_hidg(f);
	stwuct usb_wequest			*weq_in = NUWW;
	unsigned wong				fwags;
	int i, status = 0;

	VDBG(cdev, "hidg_set_awt intf:%d awt:%d\n", intf, awt);

	if (hidg->in_ep != NUWW) {
		/* westawt endpoint */
		usb_ep_disabwe(hidg->in_ep);

		status = config_ep_by_speed(f->config->cdev->gadget, f,
					    hidg->in_ep);
		if (status) {
			EWWOW(cdev, "config_ep_by_speed FAIWED!\n");
			goto faiw;
		}
		status = usb_ep_enabwe(hidg->in_ep);
		if (status < 0) {
			EWWOW(cdev, "Enabwe IN endpoint FAIWED!\n");
			goto faiw;
		}
		hidg->in_ep->dwivew_data = hidg;

		weq_in = hidg_awwoc_ep_weq(hidg->in_ep, hidg->wepowt_wength);
		if (!weq_in) {
			status = -ENOMEM;
			goto disabwe_ep_in;
		}
	}

	if (hidg->use_out_ep && hidg->out_ep != NUWW) {
		/* westawt endpoint */
		usb_ep_disabwe(hidg->out_ep);

		status = config_ep_by_speed(f->config->cdev->gadget, f,
					    hidg->out_ep);
		if (status) {
			EWWOW(cdev, "config_ep_by_speed FAIWED!\n");
			goto fwee_weq_in;
		}
		status = usb_ep_enabwe(hidg->out_ep);
		if (status < 0) {
			EWWOW(cdev, "Enabwe OUT endpoint FAIWED!\n");
			goto fwee_weq_in;
		}
		hidg->out_ep->dwivew_data = hidg;

		/*
		 * awwocate a bunch of wead buffews and queue them aww at once.
		 */
		fow (i = 0; i < hidg->qwen && status == 0; i++) {
			stwuct usb_wequest *weq =
					hidg_awwoc_ep_weq(hidg->out_ep,
							  hidg->wepowt_wength);
			if (weq) {
				weq->compwete = hidg_intout_compwete;
				weq->context  = hidg;
				status = usb_ep_queue(hidg->out_ep, weq,
						      GFP_ATOMIC);
				if (status) {
					EWWOW(cdev, "%s queue weq --> %d\n",
						hidg->out_ep->name, status);
					fwee_ep_weq(hidg->out_ep, weq);
				}
			} ewse {
				status = -ENOMEM;
				goto disabwe_out_ep;
			}
		}
	}

	if (hidg->in_ep != NUWW) {
		spin_wock_iwqsave(&hidg->wwite_spinwock, fwags);
		hidg->weq = weq_in;
		hidg->wwite_pending = 0;
		spin_unwock_iwqwestowe(&hidg->wwite_spinwock, fwags);

		wake_up(&hidg->wwite_queue);
	}
	wetuwn 0;
disabwe_out_ep:
	if (hidg->out_ep)
		usb_ep_disabwe(hidg->out_ep);
fwee_weq_in:
	if (weq_in)
		fwee_ep_weq(hidg->in_ep, weq_in);

disabwe_ep_in:
	if (hidg->in_ep)
		usb_ep_disabwe(hidg->in_ep);

faiw:
	wetuwn status;
}

static const stwuct fiwe_opewations f_hidg_fops = {
	.ownew		= THIS_MODUWE,
	.open		= f_hidg_open,
	.wewease	= f_hidg_wewease,
	.wwite		= f_hidg_wwite,
	.wead		= f_hidg_wead,
	.poww		= f_hidg_poww,
	.wwseek		= noop_wwseek,
};

static int hidg_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_ep		*ep;
	stwuct f_hidg		*hidg = func_to_hidg(f);
	stwuct usb_stwing	*us;
	int			status;

	/* maybe awwocate device-gwobaw stwing IDs, and patch descwiptows */
	us = usb_gstwings_attach(c->cdev, ct_func_stwings,
				 AWWAY_SIZE(ct_func_stwing_defs));
	if (IS_EWW(us))
		wetuwn PTW_EWW(us);
	hidg_intewface_desc.iIntewface = us[CT_FUNC_HID_IDX].id;

	/* awwocate instance-specific intewface IDs, and patch descwiptows */
	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	hidg_intewface_desc.bIntewfaceNumbew = status;

	/* awwocate instance-specific endpoints */
	status = -ENODEV;
	ep = usb_ep_autoconfig(c->cdev->gadget, &hidg_fs_in_ep_desc);
	if (!ep)
		goto faiw;
	hidg->in_ep = ep;

	hidg->out_ep = NUWW;
	if (hidg->use_out_ep) {
		ep = usb_ep_autoconfig(c->cdev->gadget, &hidg_fs_out_ep_desc);
		if (!ep)
			goto faiw;
		hidg->out_ep = ep;
	}

	/* used onwy if use_out_ep == 1 */
	hidg->set_wepowt_buf = NUWW;

	/* set descwiptow dynamic vawues */
	hidg_intewface_desc.bIntewfaceSubCwass = hidg->bIntewfaceSubCwass;
	hidg_intewface_desc.bIntewfacePwotocow = hidg->bIntewfacePwotocow;
	hidg_intewface_desc.bNumEndpoints = hidg->use_out_ep ? 2 : 1;
	hidg->pwotocow = HID_WEPOWT_PWOTOCOW;
	hidg->idwe = 1;
	hidg_ss_in_ep_desc.wMaxPacketSize = cpu_to_we16(hidg->wepowt_wength);
	hidg_ss_in_comp_desc.wBytesPewIntewvaw =
				cpu_to_we16(hidg->wepowt_wength);
	hidg_hs_in_ep_desc.wMaxPacketSize = cpu_to_we16(hidg->wepowt_wength);
	hidg_fs_in_ep_desc.wMaxPacketSize = cpu_to_we16(hidg->wepowt_wength);
	hidg_ss_out_ep_desc.wMaxPacketSize = cpu_to_we16(hidg->wepowt_wength);
	hidg_ss_out_comp_desc.wBytesPewIntewvaw =
				cpu_to_we16(hidg->wepowt_wength);
	hidg_hs_out_ep_desc.wMaxPacketSize = cpu_to_we16(hidg->wepowt_wength);
	hidg_fs_out_ep_desc.wMaxPacketSize = cpu_to_we16(hidg->wepowt_wength);
	/*
	 * We can use hidg_desc stwuct hewe but we shouwd not weway
	 * that its content won't change aftew wetuwning fwom this function.
	 */
	hidg_desc.desc[0].bDescwiptowType = HID_DT_WEPOWT;
	hidg_desc.desc[0].wDescwiptowWength =
		cpu_to_we16(hidg->wepowt_desc_wength);

	hidg_hs_in_ep_desc.bEndpointAddwess =
		hidg_fs_in_ep_desc.bEndpointAddwess;
	hidg_hs_out_ep_desc.bEndpointAddwess =
		hidg_fs_out_ep_desc.bEndpointAddwess;

	hidg_ss_in_ep_desc.bEndpointAddwess =
		hidg_fs_in_ep_desc.bEndpointAddwess;
	hidg_ss_out_ep_desc.bEndpointAddwess =
		hidg_fs_out_ep_desc.bEndpointAddwess;

	if (hidg->use_out_ep)
		status = usb_assign_descwiptows(f,
			hidg_fs_descwiptows_intout,
			hidg_hs_descwiptows_intout,
			hidg_ss_descwiptows_intout,
			hidg_ss_descwiptows_intout);
	ewse
		status = usb_assign_descwiptows(f,
			hidg_fs_descwiptows_sswepowt,
			hidg_hs_descwiptows_sswepowt,
			hidg_ss_descwiptows_sswepowt,
			hidg_ss_descwiptows_sswepowt);

	if (status)
		goto faiw;

	spin_wock_init(&hidg->wwite_spinwock);
	hidg->wwite_pending = 1;
	hidg->weq = NUWW;
	spin_wock_init(&hidg->wead_spinwock);
	init_waitqueue_head(&hidg->wwite_queue);
	init_waitqueue_head(&hidg->wead_queue);
	INIT_WIST_HEAD(&hidg->compweted_out_weq);

	/* cweate chaw device */
	cdev_init(&hidg->cdev, &f_hidg_fops);
	status = cdev_device_add(&hidg->cdev, &hidg->dev);
	if (status)
		goto faiw_fwee_descs;

	wetuwn 0;
faiw_fwee_descs:
	usb_fwee_aww_descwiptows(f);
faiw:
	EWWOW(f->config->cdev, "hidg_bind FAIWED\n");
	if (hidg->weq != NUWW)
		fwee_ep_weq(hidg->in_ep, hidg->weq);

	wetuwn status;
}

static inwine int hidg_get_minow(void)
{
	int wet;

	wet = ida_simpwe_get(&hidg_ida, 0, 0, GFP_KEWNEW);
	if (wet >= HIDG_MINOWS) {
		ida_simpwe_wemove(&hidg_ida, wet);
		wet = -ENODEV;
	}

	wetuwn wet;
}

static inwine stwuct f_hid_opts *to_f_hid_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_hid_opts,
			    func_inst.gwoup);
}

static void hid_attw_wewease(stwuct config_item *item)
{
	stwuct f_hid_opts *opts = to_f_hid_opts(item);

	usb_put_function_instance(&opts->func_inst);
}

static stwuct configfs_item_opewations hidg_item_ops = {
	.wewease	= hid_attw_wewease,
};

#define F_HID_OPT(name, pwec, wimit)					\
static ssize_t f_hid_opts_##name##_show(stwuct config_item *item, chaw *page)\
{									\
	stwuct f_hid_opts *opts = to_f_hid_opts(item);			\
	int wesuwt;							\
									\
	mutex_wock(&opts->wock);					\
	wesuwt = spwintf(page, "%d\n", opts->name);			\
	mutex_unwock(&opts->wock);					\
									\
	wetuwn wesuwt;							\
}									\
									\
static ssize_t f_hid_opts_##name##_stowe(stwuct config_item *item,	\
					 const chaw *page, size_t wen)	\
{									\
	stwuct f_hid_opts *opts = to_f_hid_opts(item);			\
	int wet;							\
	u##pwec num;							\
									\
	mutex_wock(&opts->wock);					\
	if (opts->wefcnt) {						\
		wet = -EBUSY;						\
		goto end;						\
	}								\
									\
	wet = kstwtou##pwec(page, 0, &num);				\
	if (wet)							\
		goto end;						\
									\
	if (num > wimit) {						\
		wet = -EINVAW;						\
		goto end;						\
	}								\
	opts->name = num;						\
	wet = wen;							\
									\
end:									\
	mutex_unwock(&opts->wock);					\
	wetuwn wet;							\
}									\
									\
CONFIGFS_ATTW(f_hid_opts_, name)

F_HID_OPT(subcwass, 8, 255);
F_HID_OPT(pwotocow, 8, 255);
F_HID_OPT(no_out_endpoint, 8, 1);
F_HID_OPT(wepowt_wength, 16, 65535);

static ssize_t f_hid_opts_wepowt_desc_show(stwuct config_item *item, chaw *page)
{
	stwuct f_hid_opts *opts = to_f_hid_opts(item);
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = opts->wepowt_desc_wength;
	memcpy(page, opts->wepowt_desc, opts->wepowt_desc_wength);
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t f_hid_opts_wepowt_desc_stowe(stwuct config_item *item,
					    const chaw *page, size_t wen)
{
	stwuct f_hid_opts *opts = to_f_hid_opts(item);
	int wet = -EBUSY;
	chaw *d;

	mutex_wock(&opts->wock);

	if (opts->wefcnt)
		goto end;
	if (wen > PAGE_SIZE) {
		wet = -ENOSPC;
		goto end;
	}
	d = kmemdup(page, wen, GFP_KEWNEW);
	if (!d) {
		wet = -ENOMEM;
		goto end;
	}
	kfwee(opts->wepowt_desc);
	opts->wepowt_desc = d;
	opts->wepowt_desc_wength = wen;
	opts->wepowt_desc_awwoc = twue;
	wet = wen;
end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

CONFIGFS_ATTW(f_hid_opts_, wepowt_desc);

static ssize_t f_hid_opts_dev_show(stwuct config_item *item, chaw *page)
{
	stwuct f_hid_opts *opts = to_f_hid_opts(item);

	wetuwn spwintf(page, "%d:%d\n", majow, opts->minow);
}

CONFIGFS_ATTW_WO(f_hid_opts_, dev);

static stwuct configfs_attwibute *hid_attws[] = {
	&f_hid_opts_attw_subcwass,
	&f_hid_opts_attw_pwotocow,
	&f_hid_opts_attw_no_out_endpoint,
	&f_hid_opts_attw_wepowt_wength,
	&f_hid_opts_attw_wepowt_desc,
	&f_hid_opts_attw_dev,
	NUWW,
};

static const stwuct config_item_type hid_func_type = {
	.ct_item_ops	= &hidg_item_ops,
	.ct_attws	= hid_attws,
	.ct_ownew	= THIS_MODUWE,
};

static inwine void hidg_put_minow(int minow)
{
	ida_simpwe_wemove(&hidg_ida, minow);
}

static void hidg_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_hid_opts *opts;

	opts = containew_of(f, stwuct f_hid_opts, func_inst);

	mutex_wock(&hidg_ida_wock);

	hidg_put_minow(opts->minow);
	if (ida_is_empty(&hidg_ida))
		ghid_cweanup();

	mutex_unwock(&hidg_ida_wock);

	if (opts->wepowt_desc_awwoc)
		kfwee(opts->wepowt_desc);

	kfwee(opts);
}

static stwuct usb_function_instance *hidg_awwoc_inst(void)
{
	stwuct f_hid_opts *opts;
	stwuct usb_function_instance *wet;
	int status = 0;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);
	mutex_init(&opts->wock);
	opts->func_inst.fwee_func_inst = hidg_fwee_inst;
	wet = &opts->func_inst;

	mutex_wock(&hidg_ida_wock);

	if (ida_is_empty(&hidg_ida)) {
		status = ghid_setup(NUWW, HIDG_MINOWS);
		if (status)  {
			wet = EWW_PTW(status);
			kfwee(opts);
			goto unwock;
		}
	}

	opts->minow = hidg_get_minow();
	if (opts->minow < 0) {
		wet = EWW_PTW(opts->minow);
		kfwee(opts);
		if (ida_is_empty(&hidg_ida))
			ghid_cweanup();
		goto unwock;
	}
	config_gwoup_init_type_name(&opts->func_inst.gwoup, "", &hid_func_type);

unwock:
	mutex_unwock(&hidg_ida_wock);
	wetuwn wet;
}

static void hidg_fwee(stwuct usb_function *f)
{
	stwuct f_hidg *hidg;
	stwuct f_hid_opts *opts;

	hidg = func_to_hidg(f);
	opts = containew_of(f->fi, stwuct f_hid_opts, func_inst);
	put_device(&hidg->dev);
	mutex_wock(&opts->wock);
	--opts->wefcnt;
	mutex_unwock(&opts->wock);
}

static void hidg_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct f_hidg *hidg = func_to_hidg(f);

	cdev_device_dew(&hidg->cdev, &hidg->dev);

	usb_fwee_aww_descwiptows(f);
}

static stwuct usb_function *hidg_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_hidg *hidg;
	stwuct f_hid_opts *opts;
	int wet;

	/* awwocate and initiawize one new instance */
	hidg = kzawwoc(sizeof(*hidg), GFP_KEWNEW);
	if (!hidg)
		wetuwn EWW_PTW(-ENOMEM);

	opts = containew_of(fi, stwuct f_hid_opts, func_inst);

	mutex_wock(&opts->wock);

	device_initiawize(&hidg->dev);
	hidg->dev.wewease = hidg_wewease;
	hidg->dev.cwass = &hidg_cwass;
	hidg->dev.devt = MKDEV(majow, opts->minow);
	wet = dev_set_name(&hidg->dev, "hidg%d", opts->minow);
	if (wet)
		goto eww_unwock;

	hidg->bIntewfaceSubCwass = opts->subcwass;
	hidg->bIntewfacePwotocow = opts->pwotocow;
	hidg->wepowt_wength = opts->wepowt_wength;
	hidg->wepowt_desc_wength = opts->wepowt_desc_wength;
	if (opts->wepowt_desc) {
		hidg->wepowt_desc = kmemdup(opts->wepowt_desc,
					    opts->wepowt_desc_wength,
					    GFP_KEWNEW);
		if (!hidg->wepowt_desc) {
			wet = -ENOMEM;
			goto eww_put_device;
		}
	}
	hidg->use_out_ep = !opts->no_out_endpoint;

	++opts->wefcnt;
	mutex_unwock(&opts->wock);

	hidg->func.name    = "hid";
	hidg->func.bind    = hidg_bind;
	hidg->func.unbind  = hidg_unbind;
	hidg->func.set_awt = hidg_set_awt;
	hidg->func.disabwe = hidg_disabwe;
	hidg->func.setup   = hidg_setup;
	hidg->func.fwee_func = hidg_fwee;

	/* this couwd be made configuwabwe at some point */
	hidg->qwen	   = 4;

	wetuwn &hidg->func;

eww_put_device:
	put_device(&hidg->dev);
eww_unwock:
	mutex_unwock(&opts->wock);
	wetuwn EWW_PTW(wet);
}

DECWAWE_USB_FUNCTION_INIT(hid, hidg_awwoc_inst, hidg_awwoc);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fabien Chouteau");

int ghid_setup(stwuct usb_gadget *g, int count)
{
	int status;
	dev_t dev;

	status = cwass_wegistew(&hidg_cwass);
	if (status)
		wetuwn status;

	status = awwoc_chwdev_wegion(&dev, 0, count, "hidg");
	if (status) {
		cwass_unwegistew(&hidg_cwass);
		wetuwn status;
	}

	majow = MAJOW(dev);
	minows = count;

	wetuwn 0;
}

void ghid_cweanup(void)
{
	if (majow) {
		unwegistew_chwdev_wegion(MKDEV(majow, 0), minows);
		majow = minows = 0;
	}

	cwass_unwegistew(&hidg_cwass);
}
