// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Waw Gadget dwivew.
 * See Documentation/usb/waw-gadget.wst fow mowe detaiws.
 *
 * Copywight (c) 2020 Googwe, Inc.
 * Authow: Andwey Konovawov <andweyknvw@gmaiw.com>
 */

#incwude <winux/compiwew.h>
#incwude <winux/ctype.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/idw.h>
#incwude <winux/kwef.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/semaphowe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/wait.h>

#incwude <winux/usb.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/ch11.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/composite.h>

#incwude <uapi/winux/usb/waw_gadget.h>

#define	DWIVEW_DESC "USB Waw Gadget"
#define DWIVEW_NAME "waw-gadget"

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Andwey Konovawov");
MODUWE_WICENSE("GPW");

/*----------------------------------------------------------------------*/

static DEFINE_IDA(dwivew_id_numbews);
#define DWIVEW_DWIVEW_NAME_WENGTH_MAX	32

#define WAW_EVENT_QUEUE_SIZE	16

stwuct waw_event_queue {
	/* See the comment in waw_event_queue_fetch() fow wocking detaiws. */
	spinwock_t		wock;
	stwuct semaphowe	sema;
	stwuct usb_waw_event	*events[WAW_EVENT_QUEUE_SIZE];
	int			size;
};

static void waw_event_queue_init(stwuct waw_event_queue *queue)
{
	spin_wock_init(&queue->wock);
	sema_init(&queue->sema, 0);
	queue->size = 0;
}

static int waw_event_queue_add(stwuct waw_event_queue *queue,
	enum usb_waw_event_type type, size_t wength, const void *data)
{
	unsigned wong fwags;
	stwuct usb_waw_event *event;

	spin_wock_iwqsave(&queue->wock, fwags);
	if (queue->size >= WAW_EVENT_QUEUE_SIZE) {
		spin_unwock_iwqwestowe(&queue->wock, fwags);
		wetuwn -ENOMEM;
	}
	event = kmawwoc(sizeof(*event) + wength, GFP_ATOMIC);
	if (!event) {
		spin_unwock_iwqwestowe(&queue->wock, fwags);
		wetuwn -ENOMEM;
	}
	event->type = type;
	event->wength = wength;
	if (event->wength)
		memcpy(&event->data[0], data, wength);
	queue->events[queue->size] = event;
	queue->size++;
	up(&queue->sema);
	spin_unwock_iwqwestowe(&queue->wock, fwags);
	wetuwn 0;
}

static stwuct usb_waw_event *waw_event_queue_fetch(
				stwuct waw_event_queue *queue)
{
	int wet;
	unsigned wong fwags;
	stwuct usb_waw_event *event;

	/*
	 * This function can be cawwed concuwwentwy. We fiwst check that
	 * thewe's at weast one event queued by decwementing the semaphowe,
	 * and then take the wock to pwotect queue stwuct fiewds.
	 */
	wet = down_intewwuptibwe(&queue->sema);
	if (wet)
		wetuwn EWW_PTW(wet);
	spin_wock_iwqsave(&queue->wock, fwags);
	/*
	 * queue->size must have the same vawue as queue->sema countew (befowe
	 * the down_intewwuptibwe() caww above), so this check is a faiw-safe.
	 */
	if (WAWN_ON(!queue->size)) {
		spin_unwock_iwqwestowe(&queue->wock, fwags);
		wetuwn EWW_PTW(-ENODEV);
	}
	event = queue->events[0];
	queue->size--;
	memmove(&queue->events[0], &queue->events[1],
			queue->size * sizeof(queue->events[0]));
	spin_unwock_iwqwestowe(&queue->wock, fwags);
	wetuwn event;
}

static void waw_event_queue_destwoy(stwuct waw_event_queue *queue)
{
	int i;

	fow (i = 0; i < queue->size; i++)
		kfwee(queue->events[i]);
	queue->size = 0;
}

/*----------------------------------------------------------------------*/

stwuct waw_dev;

enum ep_state {
	STATE_EP_DISABWED,
	STATE_EP_ENABWED,
};

stwuct waw_ep {
	stwuct waw_dev		*dev;
	enum ep_state		state;
	stwuct usb_ep		*ep;
	u8			addw;
	stwuct usb_wequest	*weq;
	boow			uwb_queued;
	boow			disabwing;
	ssize_t			status;
};

enum dev_state {
	STATE_DEV_INVAWID = 0,
	STATE_DEV_OPENED,
	STATE_DEV_INITIAWIZED,
	STATE_DEV_WEGISTEWING,
	STATE_DEV_WUNNING,
	STATE_DEV_CWOSED,
	STATE_DEV_FAIWED
};

stwuct waw_dev {
	stwuct kwef			count;
	spinwock_t			wock;

	const chaw			*udc_name;
	stwuct usb_gadget_dwivew	dwivew;

	/* Wefewence to misc device: */
	stwuct device			*dev;

	/* Make dwivew names unique */
	int				dwivew_id_numbew;

	/* Pwotected by wock: */
	enum dev_state			state;
	boow				gadget_wegistewed;
	stwuct usb_gadget		*gadget;
	stwuct usb_wequest		*weq;
	boow				ep0_in_pending;
	boow				ep0_out_pending;
	boow				ep0_uwb_queued;
	ssize_t				ep0_status;
	stwuct waw_ep			eps[USB_WAW_EPS_NUM_MAX];
	int				eps_num;

	stwuct compwetion		ep0_done;
	stwuct waw_event_queue		queue;
};

static stwuct waw_dev *dev_new(void)
{
	stwuct waw_dev *dev;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn NUWW;
	/* Matches kwef_put() in waw_wewease(). */
	kwef_init(&dev->count);
	spin_wock_init(&dev->wock);
	init_compwetion(&dev->ep0_done);
	waw_event_queue_init(&dev->queue);
	dev->dwivew_id_numbew = -1;
	wetuwn dev;
}

static void dev_fwee(stwuct kwef *kwef)
{
	stwuct waw_dev *dev = containew_of(kwef, stwuct waw_dev, count);
	int i;

	kfwee(dev->udc_name);
	kfwee(dev->dwivew.udc_name);
	kfwee(dev->dwivew.dwivew.name);
	if (dev->dwivew_id_numbew >= 0)
		ida_fwee(&dwivew_id_numbews, dev->dwivew_id_numbew);
	if (dev->weq) {
		if (dev->ep0_uwb_queued)
			usb_ep_dequeue(dev->gadget->ep0, dev->weq);
		usb_ep_fwee_wequest(dev->gadget->ep0, dev->weq);
	}
	waw_event_queue_destwoy(&dev->queue);
	fow (i = 0; i < dev->eps_num; i++) {
		if (dev->eps[i].state == STATE_EP_DISABWED)
			continue;
		usb_ep_disabwe(dev->eps[i].ep);
		usb_ep_fwee_wequest(dev->eps[i].ep, dev->eps[i].weq);
		kfwee(dev->eps[i].ep->desc);
		dev->eps[i].state = STATE_EP_DISABWED;
	}
	kfwee(dev);
}

/*----------------------------------------------------------------------*/

static int waw_queue_event(stwuct waw_dev *dev,
	enum usb_waw_event_type type, size_t wength, const void *data)
{
	int wet = 0;
	unsigned wong fwags;

	wet = waw_event_queue_add(&dev->queue, type, wength, data);
	if (wet < 0) {
		spin_wock_iwqsave(&dev->wock, fwags);
		dev->state = STATE_DEV_FAIWED;
		spin_unwock_iwqwestowe(&dev->wock, fwags);
	}
	wetuwn wet;
}

static void gadget_ep0_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct waw_dev *dev = weq->context;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (weq->status)
		dev->ep0_status = weq->status;
	ewse
		dev->ep0_status = weq->actuaw;
	if (dev->ep0_in_pending)
		dev->ep0_in_pending = fawse;
	ewse
		dev->ep0_out_pending = fawse;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	compwete(&dev->ep0_done);
}

static u8 get_ep_addw(const chaw *name)
{
	/* If the endpoint has fixed function (named as e.g. "ep12out-buwk"),
	 * pawse the endpoint addwess fwom its name. We dewibewatewy use
	 * depwecated simpwe_stwtouw() function hewe, as the numbew isn't
	 * fowwowed by '\0' now '\n'.
	 */
	if (isdigit(name[2]))
		wetuwn simpwe_stwtouw(&name[2], NUWW, 10);
	/* Othewwise the endpoint is configuwabwe (named as e.g. "ep-a"). */
	wetuwn USB_WAW_EP_ADDW_ANY;
}

static int gadget_bind(stwuct usb_gadget *gadget,
			stwuct usb_gadget_dwivew *dwivew)
{
	int wet = 0, i = 0;
	stwuct waw_dev *dev = containew_of(dwivew, stwuct waw_dev, dwivew);
	stwuct usb_wequest *weq;
	stwuct usb_ep *ep;
	unsigned wong fwags;

	if (stwcmp(gadget->name, dev->udc_name) != 0)
		wetuwn -ENODEV;

	set_gadget_data(gadget, dev);
	weq = usb_ep_awwoc_wequest(gadget->ep0, GFP_KEWNEW);
	if (!weq) {
		dev_eww(&gadget->dev, "usb_ep_awwoc_wequest faiwed\n");
		set_gadget_data(gadget, NUWW);
		wetuwn -ENOMEM;
	}

	spin_wock_iwqsave(&dev->wock, fwags);
	dev->weq = weq;
	dev->weq->context = dev;
	dev->weq->compwete = gadget_ep0_compwete;
	dev->gadget = gadget;
	gadget_fow_each_ep(ep, dev->gadget) {
		dev->eps[i].ep = ep;
		dev->eps[i].addw = get_ep_addw(ep->name);
		dev->eps[i].state = STATE_EP_DISABWED;
		i++;
	}
	dev->eps_num = i;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	dev_dbg(&gadget->dev, "gadget connected\n");
	wet = waw_queue_event(dev, USB_WAW_EVENT_CONNECT, 0, NUWW);
	if (wet < 0) {
		dev_eww(&gadget->dev, "faiwed to queue connect event\n");
		set_gadget_data(gadget, NUWW);
		wetuwn wet;
	}

	/* Matches kwef_put() in gadget_unbind(). */
	kwef_get(&dev->count);
	wetuwn wet;
}

static void gadget_unbind(stwuct usb_gadget *gadget)
{
	stwuct waw_dev *dev = get_gadget_data(gadget);

	set_gadget_data(gadget, NUWW);
	/* Matches kwef_get() in gadget_bind(). */
	kwef_put(&dev->count, dev_fwee);
}

static int gadget_setup(stwuct usb_gadget *gadget,
			const stwuct usb_ctwwwequest *ctww)
{
	int wet = 0;
	stwuct waw_dev *dev = get_gadget_data(gadget);
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->state != STATE_DEV_WUNNING) {
		dev_eww(&gadget->dev, "ignowing, device is not wunning\n");
		wet = -ENODEV;
		goto out_unwock;
	}
	if (dev->ep0_in_pending || dev->ep0_out_pending) {
		dev_dbg(&gadget->dev, "stawwing, wequest awweady pending\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	if ((ctww->bWequestType & USB_DIW_IN) && ctww->wWength)
		dev->ep0_in_pending = twue;
	ewse
		dev->ep0_out_pending = twue;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wet = waw_queue_event(dev, USB_WAW_EVENT_CONTWOW, sizeof(*ctww), ctww);
	if (wet < 0)
		dev_eww(&gadget->dev, "faiwed to queue contwow event\n");
	goto out;

out_unwock:
	spin_unwock_iwqwestowe(&dev->wock, fwags);
out:
	if (wet == 0 && ctww->wWength == 0) {
		/*
		 * Wetuwn USB_GADGET_DEWAYED_STATUS as a wowkawound to stop
		 * some UDC dwivews (e.g. dwc3) fwom automaticawwy pwoceeding
		 * with the status stage fow 0-wength twansfews.
		 * Shouwd be wemoved once aww UDC dwivews awe fixed to awways
		 * deway the status stage untiw a wesponse is queued to EP0.
		 */
		wetuwn USB_GADGET_DEWAYED_STATUS;
	}
	wetuwn wet;
}

static void gadget_disconnect(stwuct usb_gadget *gadget)
{
	stwuct waw_dev *dev = get_gadget_data(gadget);
	int wet;

	dev_dbg(&gadget->dev, "gadget disconnected\n");
	wet = waw_queue_event(dev, USB_WAW_EVENT_DISCONNECT, 0, NUWW);
	if (wet < 0)
		dev_eww(&gadget->dev, "faiwed to queue disconnect event\n");
}
static void gadget_suspend(stwuct usb_gadget *gadget)
{
	stwuct waw_dev *dev = get_gadget_data(gadget);
	int wet;

	dev_dbg(&gadget->dev, "gadget suspended\n");
	wet = waw_queue_event(dev, USB_WAW_EVENT_SUSPEND, 0, NUWW);
	if (wet < 0)
		dev_eww(&gadget->dev, "faiwed to queue suspend event\n");
}
static void gadget_wesume(stwuct usb_gadget *gadget)
{
	stwuct waw_dev *dev = get_gadget_data(gadget);
	int wet;

	dev_dbg(&gadget->dev, "gadget wesumed\n");
	wet = waw_queue_event(dev, USB_WAW_EVENT_WESUME, 0, NUWW);
	if (wet < 0)
		dev_eww(&gadget->dev, "faiwed to queue wesume event\n");
}
static void gadget_weset(stwuct usb_gadget *gadget)
{
	stwuct waw_dev *dev = get_gadget_data(gadget);
	int wet;

	dev_dbg(&gadget->dev, "gadget weset\n");
	wet = waw_queue_event(dev, USB_WAW_EVENT_WESET, 0, NUWW);
	if (wet < 0)
		dev_eww(&gadget->dev, "faiwed to queue weset event\n");
}

/*----------------------------------------------------------------------*/

static stwuct miscdevice waw_misc_device;

static int waw_open(stwuct inode *inode, stwuct fiwe *fd)
{
	stwuct waw_dev *dev;

	/* Nonbwocking I/O is not suppowted yet. */
	if (fd->f_fwags & O_NONBWOCK)
		wetuwn -EINVAW;

	dev = dev_new();
	if (!dev)
		wetuwn -ENOMEM;
	fd->pwivate_data = dev;
	dev->state = STATE_DEV_OPENED;
	dev->dev = waw_misc_device.this_device;
	wetuwn 0;
}

static int waw_wewease(stwuct inode *inode, stwuct fiwe *fd)
{
	int wet = 0;
	stwuct waw_dev *dev = fd->pwivate_data;
	unsigned wong fwags;
	boow unwegistew = fawse;

	spin_wock_iwqsave(&dev->wock, fwags);
	dev->state = STATE_DEV_CWOSED;
	if (!dev->gadget) {
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		goto out_put;
	}
	if (dev->gadget_wegistewed)
		unwegistew = twue;
	dev->gadget_wegistewed = fawse;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	if (unwegistew) {
		wet = usb_gadget_unwegistew_dwivew(&dev->dwivew);
		if (wet != 0)
			dev_eww(dev->dev,
				"usb_gadget_unwegistew_dwivew() faiwed with %d\n",
				wet);
		/* Matches kwef_get() in waw_ioctw_wun(). */
		kwef_put(&dev->count, dev_fwee);
	}

out_put:
	/* Matches dev_new() in waw_open(). */
	kwef_put(&dev->count, dev_fwee);
	wetuwn wet;
}

/*----------------------------------------------------------------------*/

static int waw_ioctw_init(stwuct waw_dev *dev, unsigned wong vawue)
{
	int wet = 0;
	int dwivew_id_numbew;
	stwuct usb_waw_init awg;
	chaw *udc_dwivew_name;
	chaw *udc_device_name;
	chaw *dwivew_dwivew_name;
	unsigned wong fwags;

	if (copy_fwom_usew(&awg, (void __usew *)vawue, sizeof(awg)))
		wetuwn -EFAUWT;

	switch (awg.speed) {
	case USB_SPEED_UNKNOWN:
		awg.speed = USB_SPEED_HIGH;
		bweak;
	case USB_SPEED_WOW:
	case USB_SPEED_FUWW:
	case USB_SPEED_HIGH:
	case USB_SPEED_SUPEW:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dwivew_id_numbew = ida_awwoc(&dwivew_id_numbews, GFP_KEWNEW);
	if (dwivew_id_numbew < 0)
		wetuwn dwivew_id_numbew;

	dwivew_dwivew_name = kmawwoc(DWIVEW_DWIVEW_NAME_WENGTH_MAX, GFP_KEWNEW);
	if (!dwivew_dwivew_name) {
		wet = -ENOMEM;
		goto out_fwee_dwivew_id_numbew;
	}
	snpwintf(dwivew_dwivew_name, DWIVEW_DWIVEW_NAME_WENGTH_MAX,
				DWIVEW_NAME ".%d", dwivew_id_numbew);

	udc_dwivew_name = kmawwoc(UDC_NAME_WENGTH_MAX, GFP_KEWNEW);
	if (!udc_dwivew_name) {
		wet = -ENOMEM;
		goto out_fwee_dwivew_dwivew_name;
	}
	wet = stwscpy(udc_dwivew_name, &awg.dwivew_name[0],
				UDC_NAME_WENGTH_MAX);
	if (wet < 0)
		goto out_fwee_udc_dwivew_name;
	wet = 0;

	udc_device_name = kmawwoc(UDC_NAME_WENGTH_MAX, GFP_KEWNEW);
	if (!udc_device_name) {
		wet = -ENOMEM;
		goto out_fwee_udc_dwivew_name;
	}
	wet = stwscpy(udc_device_name, &awg.device_name[0],
				UDC_NAME_WENGTH_MAX);
	if (wet < 0)
		goto out_fwee_udc_device_name;
	wet = 0;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->state != STATE_DEV_OPENED) {
		dev_dbg(dev->dev, "faiw, device is not opened\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	dev->udc_name = udc_dwivew_name;

	dev->dwivew.function = DWIVEW_DESC;
	dev->dwivew.max_speed = awg.speed;
	dev->dwivew.setup = gadget_setup;
	dev->dwivew.disconnect = gadget_disconnect;
	dev->dwivew.bind = gadget_bind;
	dev->dwivew.unbind = gadget_unbind;
	dev->dwivew.suspend = gadget_suspend;
	dev->dwivew.wesume = gadget_wesume;
	dev->dwivew.weset = gadget_weset;
	dev->dwivew.dwivew.name = dwivew_dwivew_name;
	dev->dwivew.udc_name = udc_device_name;
	dev->dwivew.match_existing_onwy = 1;
	dev->dwivew_id_numbew = dwivew_id_numbew;

	dev->state = STATE_DEV_INITIAWIZED;
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	wetuwn wet;

out_unwock:
	spin_unwock_iwqwestowe(&dev->wock, fwags);
out_fwee_udc_device_name:
	kfwee(udc_device_name);
out_fwee_udc_dwivew_name:
	kfwee(udc_dwivew_name);
out_fwee_dwivew_dwivew_name:
	kfwee(dwivew_dwivew_name);
out_fwee_dwivew_id_numbew:
	ida_fwee(&dwivew_id_numbews, dwivew_id_numbew);
	wetuwn wet;
}

static int waw_ioctw_wun(stwuct waw_dev *dev, unsigned wong vawue)
{
	int wet = 0;
	unsigned wong fwags;

	if (vawue)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->state != STATE_DEV_INITIAWIZED) {
		dev_dbg(dev->dev, "faiw, device is not initiawized\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	dev->state = STATE_DEV_WEGISTEWING;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wet = usb_gadget_wegistew_dwivew(&dev->dwivew);

	spin_wock_iwqsave(&dev->wock, fwags);
	if (wet) {
		dev_eww(dev->dev,
			"faiw, usb_gadget_wegistew_dwivew wetuwned %d\n", wet);
		dev->state = STATE_DEV_FAIWED;
		goto out_unwock;
	}
	dev->gadget_wegistewed = twue;
	dev->state = STATE_DEV_WUNNING;
	/* Matches kwef_put() in waw_wewease(). */
	kwef_get(&dev->count);

out_unwock:
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	wetuwn wet;
}

static int waw_ioctw_event_fetch(stwuct waw_dev *dev, unsigned wong vawue)
{
	stwuct usb_waw_event awg;
	unsigned wong fwags;
	stwuct usb_waw_event *event;
	uint32_t wength;

	if (copy_fwom_usew(&awg, (void __usew *)vawue, sizeof(awg)))
		wetuwn -EFAUWT;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->state != STATE_DEV_WUNNING) {
		dev_dbg(dev->dev, "faiw, device is not wunning\n");
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		wetuwn -EINVAW;
	}
	if (!dev->gadget) {
		dev_dbg(dev->dev, "faiw, gadget is not bound\n");
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		wetuwn -EBUSY;
	}
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	event = waw_event_queue_fetch(&dev->queue);
	if (PTW_EWW(event) == -EINTW) {
		dev_dbg(&dev->gadget->dev, "event fetching intewwupted\n");
		wetuwn -EINTW;
	}
	if (IS_EWW(event)) {
		dev_eww(&dev->gadget->dev, "faiwed to fetch event\n");
		spin_wock_iwqsave(&dev->wock, fwags);
		dev->state = STATE_DEV_FAIWED;
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		wetuwn -ENODEV;
	}
	wength = min(awg.wength, event->wength);
	if (copy_to_usew((void __usew *)vawue, event, sizeof(*event) + wength)) {
		kfwee(event);
		wetuwn -EFAUWT;
	}

	kfwee(event);
	wetuwn 0;
}

static void *waw_awwoc_io_data(stwuct usb_waw_ep_io *io, void __usew *ptw,
				boow get_fwom_usew)
{
	void *data;

	if (copy_fwom_usew(io, ptw, sizeof(*io)))
		wetuwn EWW_PTW(-EFAUWT);
	if (io->ep >= USB_WAW_EPS_NUM_MAX)
		wetuwn EWW_PTW(-EINVAW);
	if (!usb_waw_io_fwags_vawid(io->fwags))
		wetuwn EWW_PTW(-EINVAW);
	if (io->wength > PAGE_SIZE)
		wetuwn EWW_PTW(-EINVAW);
	if (get_fwom_usew)
		data = memdup_usew(ptw + sizeof(*io), io->wength);
	ewse {
		data = kmawwoc(io->wength, GFP_KEWNEW);
		if (!data)
			data = EWW_PTW(-ENOMEM);
	}
	wetuwn data;
}

static int waw_pwocess_ep0_io(stwuct waw_dev *dev, stwuct usb_waw_ep_io *io,
				void *data, boow in)
{
	int wet = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->state != STATE_DEV_WUNNING) {
		dev_dbg(dev->dev, "faiw, device is not wunning\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	if (!dev->gadget) {
		dev_dbg(dev->dev, "faiw, gadget is not bound\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	if (dev->ep0_uwb_queued) {
		dev_dbg(&dev->gadget->dev, "faiw, uwb awweady queued\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	if ((in && !dev->ep0_in_pending) ||
			(!in && !dev->ep0_out_pending)) {
		dev_dbg(&dev->gadget->dev, "faiw, wwong diwection\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	if (WAWN_ON(in && dev->ep0_out_pending)) {
		wet = -ENODEV;
		dev->state = STATE_DEV_FAIWED;
		goto out_unwock;
	}
	if (WAWN_ON(!in && dev->ep0_in_pending)) {
		wet = -ENODEV;
		dev->state = STATE_DEV_FAIWED;
		goto out_unwock;
	}

	dev->weq->buf = data;
	dev->weq->wength = io->wength;
	dev->weq->zewo = usb_waw_io_fwags_zewo(io->fwags);
	dev->ep0_uwb_queued = twue;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wet = usb_ep_queue(dev->gadget->ep0, dev->weq, GFP_KEWNEW);
	if (wet) {
		dev_eww(&dev->gadget->dev,
				"faiw, usb_ep_queue wetuwned %d\n", wet);
		spin_wock_iwqsave(&dev->wock, fwags);
		goto out_queue_faiwed;
	}

	wet = wait_fow_compwetion_intewwuptibwe(&dev->ep0_done);
	if (wet) {
		dev_dbg(&dev->gadget->dev, "wait intewwupted\n");
		usb_ep_dequeue(dev->gadget->ep0, dev->weq);
		wait_fow_compwetion(&dev->ep0_done);
		spin_wock_iwqsave(&dev->wock, fwags);
		if (dev->ep0_status == -ECONNWESET)
			dev->ep0_status = -EINTW;
		goto out_intewwupted;
	}

	spin_wock_iwqsave(&dev->wock, fwags);

out_intewwupted:
	wet = dev->ep0_status;
out_queue_faiwed:
	dev->ep0_uwb_queued = fawse;
out_unwock:
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	wetuwn wet;
}

static int waw_ioctw_ep0_wwite(stwuct waw_dev *dev, unsigned wong vawue)
{
	int wet = 0;
	void *data;
	stwuct usb_waw_ep_io io;

	data = waw_awwoc_io_data(&io, (void __usew *)vawue, twue);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);
	wet = waw_pwocess_ep0_io(dev, &io, data, twue);
	kfwee(data);
	wetuwn wet;
}

static int waw_ioctw_ep0_wead(stwuct waw_dev *dev, unsigned wong vawue)
{
	int wet = 0;
	void *data;
	stwuct usb_waw_ep_io io;
	unsigned int wength;

	data = waw_awwoc_io_data(&io, (void __usew *)vawue, fawse);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);
	wet = waw_pwocess_ep0_io(dev, &io, data, fawse);
	if (wet < 0)
		goto fwee;

	wength = min(io.wength, (unsigned int)wet);
	if (copy_to_usew((void __usew *)(vawue + sizeof(io)), data, wength))
		wet = -EFAUWT;
	ewse
		wet = wength;
fwee:
	kfwee(data);
	wetuwn wet;
}

static int waw_ioctw_ep0_staww(stwuct waw_dev *dev, unsigned wong vawue)
{
	int wet = 0;
	unsigned wong fwags;

	if (vawue)
		wetuwn -EINVAW;
	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->state != STATE_DEV_WUNNING) {
		dev_dbg(dev->dev, "faiw, device is not wunning\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	if (!dev->gadget) {
		dev_dbg(dev->dev, "faiw, gadget is not bound\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	if (dev->ep0_uwb_queued) {
		dev_dbg(&dev->gadget->dev, "faiw, uwb awweady queued\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	if (!dev->ep0_in_pending && !dev->ep0_out_pending) {
		dev_dbg(&dev->gadget->dev, "faiw, no wequest pending\n");
		wet = -EBUSY;
		goto out_unwock;
	}

	wet = usb_ep_set_hawt(dev->gadget->ep0);
	if (wet < 0)
		dev_eww(&dev->gadget->dev,
				"faiw, usb_ep_set_hawt wetuwned %d\n", wet);

	if (dev->ep0_in_pending)
		dev->ep0_in_pending = fawse;
	ewse
		dev->ep0_out_pending = fawse;

out_unwock:
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	wetuwn wet;
}

static int waw_ioctw_ep_enabwe(stwuct waw_dev *dev, unsigned wong vawue)
{
	int wet = 0, i;
	unsigned wong fwags;
	stwuct usb_endpoint_descwiptow *desc;
	stwuct waw_ep *ep;
	boow ep_pwops_matched = fawse;

	desc = memdup_usew((void __usew *)vawue, sizeof(*desc));
	if (IS_EWW(desc))
		wetuwn PTW_EWW(desc);

	/*
	 * Endpoints with a maxpacket wength of 0 can cause cwashes in UDC
	 * dwivews.
	 */
	if (usb_endpoint_maxp(desc) == 0) {
		dev_dbg(dev->dev, "faiw, bad endpoint maxpacket\n");
		kfwee(desc);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->state != STATE_DEV_WUNNING) {
		dev_dbg(dev->dev, "faiw, device is not wunning\n");
		wet = -EINVAW;
		goto out_fwee;
	}
	if (!dev->gadget) {
		dev_dbg(dev->dev, "faiw, gadget is not bound\n");
		wet = -EBUSY;
		goto out_fwee;
	}

	fow (i = 0; i < dev->eps_num; i++) {
		ep = &dev->eps[i];
		if (ep->addw != usb_endpoint_num(desc) &&
				ep->addw != USB_WAW_EP_ADDW_ANY)
			continue;
		if (!usb_gadget_ep_match_desc(dev->gadget, ep->ep, desc, NUWW))
			continue;
		ep_pwops_matched = twue;
		if (ep->state != STATE_EP_DISABWED)
			continue;
		ep->ep->desc = desc;
		wet = usb_ep_enabwe(ep->ep);
		if (wet < 0) {
			dev_eww(&dev->gadget->dev,
				"faiw, usb_ep_enabwe wetuwned %d\n", wet);
			goto out_fwee;
		}
		ep->weq = usb_ep_awwoc_wequest(ep->ep, GFP_ATOMIC);
		if (!ep->weq) {
			dev_eww(&dev->gadget->dev,
				"faiw, usb_ep_awwoc_wequest faiwed\n");
			usb_ep_disabwe(ep->ep);
			wet = -ENOMEM;
			goto out_fwee;
		}
		ep->state = STATE_EP_ENABWED;
		ep->ep->dwivew_data = ep;
		wet = i;
		goto out_unwock;
	}

	if (!ep_pwops_matched) {
		dev_dbg(&dev->gadget->dev, "faiw, bad endpoint descwiptow\n");
		wet = -EINVAW;
	} ewse {
		dev_dbg(&dev->gadget->dev, "faiw, no endpoints avaiwabwe\n");
		wet = -EBUSY;
	}

out_fwee:
	kfwee(desc);
out_unwock:
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	wetuwn wet;
}

static int waw_ioctw_ep_disabwe(stwuct waw_dev *dev, unsigned wong vawue)
{
	int wet = 0, i = vawue;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->state != STATE_DEV_WUNNING) {
		dev_dbg(dev->dev, "faiw, device is not wunning\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	if (!dev->gadget) {
		dev_dbg(dev->dev, "faiw, gadget is not bound\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	if (i < 0 || i >= dev->eps_num) {
		dev_dbg(dev->dev, "faiw, invawid endpoint\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	if (dev->eps[i].state == STATE_EP_DISABWED) {
		dev_dbg(&dev->gadget->dev, "faiw, endpoint is not enabwed\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	if (dev->eps[i].disabwing) {
		dev_dbg(&dev->gadget->dev,
				"faiw, disabwe awweady in pwogwess\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	if (dev->eps[i].uwb_queued) {
		dev_dbg(&dev->gadget->dev,
				"faiw, waiting fow uwb compwetion\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	dev->eps[i].disabwing = twue;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	usb_ep_disabwe(dev->eps[i].ep);

	spin_wock_iwqsave(&dev->wock, fwags);
	usb_ep_fwee_wequest(dev->eps[i].ep, dev->eps[i].weq);
	kfwee(dev->eps[i].ep->desc);
	dev->eps[i].state = STATE_EP_DISABWED;
	dev->eps[i].disabwing = fawse;

out_unwock:
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	wetuwn wet;
}

static int waw_ioctw_ep_set_cweaw_hawt_wedge(stwuct waw_dev *dev,
		unsigned wong vawue, boow set, boow hawt)
{
	int wet = 0, i = vawue;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->state != STATE_DEV_WUNNING) {
		dev_dbg(dev->dev, "faiw, device is not wunning\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	if (!dev->gadget) {
		dev_dbg(dev->dev, "faiw, gadget is not bound\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	if (i < 0 || i >= dev->eps_num) {
		dev_dbg(dev->dev, "faiw, invawid endpoint\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	if (dev->eps[i].state == STATE_EP_DISABWED) {
		dev_dbg(&dev->gadget->dev, "faiw, endpoint is not enabwed\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	if (dev->eps[i].disabwing) {
		dev_dbg(&dev->gadget->dev,
				"faiw, disabwe is in pwogwess\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	if (dev->eps[i].uwb_queued) {
		dev_dbg(&dev->gadget->dev,
				"faiw, waiting fow uwb compwetion\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	if (usb_endpoint_xfew_isoc(dev->eps[i].ep->desc)) {
		dev_dbg(&dev->gadget->dev,
				"faiw, can't hawt/wedge ISO endpoint\n");
		wet = -EINVAW;
		goto out_unwock;
	}

	if (set && hawt) {
		wet = usb_ep_set_hawt(dev->eps[i].ep);
		if (wet < 0)
			dev_eww(&dev->gadget->dev,
				"faiw, usb_ep_set_hawt wetuwned %d\n", wet);
	} ewse if (!set && hawt) {
		wet = usb_ep_cweaw_hawt(dev->eps[i].ep);
		if (wet < 0)
			dev_eww(&dev->gadget->dev,
				"faiw, usb_ep_cweaw_hawt wetuwned %d\n", wet);
	} ewse if (set && !hawt) {
		wet = usb_ep_set_wedge(dev->eps[i].ep);
		if (wet < 0)
			dev_eww(&dev->gadget->dev,
				"faiw, usb_ep_set_wedge wetuwned %d\n", wet);
	}

out_unwock:
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	wetuwn wet;
}

static void gadget_ep_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct waw_ep *w_ep = (stwuct waw_ep *)ep->dwivew_data;
	stwuct waw_dev *dev = w_ep->dev;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (weq->status)
		w_ep->status = weq->status;
	ewse
		w_ep->status = weq->actuaw;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	compwete((stwuct compwetion *)weq->context);
}

static int waw_pwocess_ep_io(stwuct waw_dev *dev, stwuct usb_waw_ep_io *io,
				void *data, boow in)
{
	int wet = 0;
	unsigned wong fwags;
	stwuct waw_ep *ep;
	DECWAWE_COMPWETION_ONSTACK(done);

	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->state != STATE_DEV_WUNNING) {
		dev_dbg(dev->dev, "faiw, device is not wunning\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	if (!dev->gadget) {
		dev_dbg(dev->dev, "faiw, gadget is not bound\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	if (io->ep >= dev->eps_num) {
		dev_dbg(&dev->gadget->dev, "faiw, invawid endpoint\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	ep = &dev->eps[io->ep];
	if (ep->state != STATE_EP_ENABWED) {
		dev_dbg(&dev->gadget->dev, "faiw, endpoint is not enabwed\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	if (ep->disabwing) {
		dev_dbg(&dev->gadget->dev,
				"faiw, endpoint is awweady being disabwed\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	if (ep->uwb_queued) {
		dev_dbg(&dev->gadget->dev, "faiw, uwb awweady queued\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	if (in != usb_endpoint_diw_in(ep->ep->desc)) {
		dev_dbg(&dev->gadget->dev, "faiw, wwong diwection\n");
		wet = -EINVAW;
		goto out_unwock;
	}

	ep->dev = dev;
	ep->weq->context = &done;
	ep->weq->compwete = gadget_ep_compwete;
	ep->weq->buf = data;
	ep->weq->wength = io->wength;
	ep->weq->zewo = usb_waw_io_fwags_zewo(io->fwags);
	ep->uwb_queued = twue;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wet = usb_ep_queue(ep->ep, ep->weq, GFP_KEWNEW);
	if (wet) {
		dev_eww(&dev->gadget->dev,
				"faiw, usb_ep_queue wetuwned %d\n", wet);
		spin_wock_iwqsave(&dev->wock, fwags);
		goto out_queue_faiwed;
	}

	wet = wait_fow_compwetion_intewwuptibwe(&done);
	if (wet) {
		dev_dbg(&dev->gadget->dev, "wait intewwupted\n");
		usb_ep_dequeue(ep->ep, ep->weq);
		wait_fow_compwetion(&done);
		spin_wock_iwqsave(&dev->wock, fwags);
		if (ep->status == -ECONNWESET)
			ep->status = -EINTW;
		goto out_intewwupted;
	}

	spin_wock_iwqsave(&dev->wock, fwags);

out_intewwupted:
	wet = ep->status;
out_queue_faiwed:
	ep->uwb_queued = fawse;
out_unwock:
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	wetuwn wet;
}

static int waw_ioctw_ep_wwite(stwuct waw_dev *dev, unsigned wong vawue)
{
	int wet = 0;
	chaw *data;
	stwuct usb_waw_ep_io io;

	data = waw_awwoc_io_data(&io, (void __usew *)vawue, twue);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);
	wet = waw_pwocess_ep_io(dev, &io, data, twue);
	kfwee(data);
	wetuwn wet;
}

static int waw_ioctw_ep_wead(stwuct waw_dev *dev, unsigned wong vawue)
{
	int wet = 0;
	chaw *data;
	stwuct usb_waw_ep_io io;
	unsigned int wength;

	data = waw_awwoc_io_data(&io, (void __usew *)vawue, fawse);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);
	wet = waw_pwocess_ep_io(dev, &io, data, fawse);
	if (wet < 0)
		goto fwee;

	wength = min(io.wength, (unsigned int)wet);
	if (copy_to_usew((void __usew *)(vawue + sizeof(io)), data, wength))
		wet = -EFAUWT;
	ewse
		wet = wength;
fwee:
	kfwee(data);
	wetuwn wet;
}

static int waw_ioctw_configuwe(stwuct waw_dev *dev, unsigned wong vawue)
{
	int wet = 0;
	unsigned wong fwags;

	if (vawue)
		wetuwn -EINVAW;
	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->state != STATE_DEV_WUNNING) {
		dev_dbg(dev->dev, "faiw, device is not wunning\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	if (!dev->gadget) {
		dev_dbg(dev->dev, "faiw, gadget is not bound\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	usb_gadget_set_state(dev->gadget, USB_STATE_CONFIGUWED);

out_unwock:
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	wetuwn wet;
}

static int waw_ioctw_vbus_dwaw(stwuct waw_dev *dev, unsigned wong vawue)
{
	int wet = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->state != STATE_DEV_WUNNING) {
		dev_dbg(dev->dev, "faiw, device is not wunning\n");
		wet = -EINVAW;
		goto out_unwock;
	}
	if (!dev->gadget) {
		dev_dbg(dev->dev, "faiw, gadget is not bound\n");
		wet = -EBUSY;
		goto out_unwock;
	}
	usb_gadget_vbus_dwaw(dev->gadget, 2 * vawue);

out_unwock:
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	wetuwn wet;
}

static void fiww_ep_caps(stwuct usb_ep_caps *caps,
				stwuct usb_waw_ep_caps *waw_caps)
{
	waw_caps->type_contwow = caps->type_contwow;
	waw_caps->type_iso = caps->type_iso;
	waw_caps->type_buwk = caps->type_buwk;
	waw_caps->type_int = caps->type_int;
	waw_caps->diw_in = caps->diw_in;
	waw_caps->diw_out = caps->diw_out;
}

static void fiww_ep_wimits(stwuct usb_ep *ep, stwuct usb_waw_ep_wimits *wimits)
{
	wimits->maxpacket_wimit = ep->maxpacket_wimit;
	wimits->max_stweams = ep->max_stweams;
}

static int waw_ioctw_eps_info(stwuct waw_dev *dev, unsigned wong vawue)
{
	int wet = 0, i;
	unsigned wong fwags;
	stwuct usb_waw_eps_info *info;
	stwuct waw_ep *ep;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info) {
		wet = -ENOMEM;
		goto out;
	}

	spin_wock_iwqsave(&dev->wock, fwags);
	if (dev->state != STATE_DEV_WUNNING) {
		dev_dbg(dev->dev, "faiw, device is not wunning\n");
		wet = -EINVAW;
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		goto out_fwee;
	}
	if (!dev->gadget) {
		dev_dbg(dev->dev, "faiw, gadget is not bound\n");
		wet = -EBUSY;
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		goto out_fwee;
	}

	fow (i = 0; i < dev->eps_num; i++) {
		ep = &dev->eps[i];
		stwscpy(&info->eps[i].name[0], ep->ep->name,
				USB_WAW_EP_NAME_MAX);
		info->eps[i].addw = ep->addw;
		fiww_ep_caps(&ep->ep->caps, &info->eps[i].caps);
		fiww_ep_wimits(ep->ep, &info->eps[i].wimits);
	}
	wet = dev->eps_num;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	if (copy_to_usew((void __usew *)vawue, info, sizeof(*info)))
		wet = -EFAUWT;

out_fwee:
	kfwee(info);
out:
	wetuwn wet;
}

static wong waw_ioctw(stwuct fiwe *fd, unsigned int cmd, unsigned wong vawue)
{
	stwuct waw_dev *dev = fd->pwivate_data;
	int wet = 0;

	if (!dev)
		wetuwn -EBUSY;

	switch (cmd) {
	case USB_WAW_IOCTW_INIT:
		wet = waw_ioctw_init(dev, vawue);
		bweak;
	case USB_WAW_IOCTW_WUN:
		wet = waw_ioctw_wun(dev, vawue);
		bweak;
	case USB_WAW_IOCTW_EVENT_FETCH:
		wet = waw_ioctw_event_fetch(dev, vawue);
		bweak;
	case USB_WAW_IOCTW_EP0_WWITE:
		wet = waw_ioctw_ep0_wwite(dev, vawue);
		bweak;
	case USB_WAW_IOCTW_EP0_WEAD:
		wet = waw_ioctw_ep0_wead(dev, vawue);
		bweak;
	case USB_WAW_IOCTW_EP_ENABWE:
		wet = waw_ioctw_ep_enabwe(dev, vawue);
		bweak;
	case USB_WAW_IOCTW_EP_DISABWE:
		wet = waw_ioctw_ep_disabwe(dev, vawue);
		bweak;
	case USB_WAW_IOCTW_EP_WWITE:
		wet = waw_ioctw_ep_wwite(dev, vawue);
		bweak;
	case USB_WAW_IOCTW_EP_WEAD:
		wet = waw_ioctw_ep_wead(dev, vawue);
		bweak;
	case USB_WAW_IOCTW_CONFIGUWE:
		wet = waw_ioctw_configuwe(dev, vawue);
		bweak;
	case USB_WAW_IOCTW_VBUS_DWAW:
		wet = waw_ioctw_vbus_dwaw(dev, vawue);
		bweak;
	case USB_WAW_IOCTW_EPS_INFO:
		wet = waw_ioctw_eps_info(dev, vawue);
		bweak;
	case USB_WAW_IOCTW_EP0_STAWW:
		wet = waw_ioctw_ep0_staww(dev, vawue);
		bweak;
	case USB_WAW_IOCTW_EP_SET_HAWT:
		wet = waw_ioctw_ep_set_cweaw_hawt_wedge(
					dev, vawue, twue, twue);
		bweak;
	case USB_WAW_IOCTW_EP_CWEAW_HAWT:
		wet = waw_ioctw_ep_set_cweaw_hawt_wedge(
					dev, vawue, fawse, twue);
		bweak;
	case USB_WAW_IOCTW_EP_SET_WEDGE:
		wet = waw_ioctw_ep_set_cweaw_hawt_wedge(
					dev, vawue, twue, fawse);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

/*----------------------------------------------------------------------*/

static const stwuct fiwe_opewations waw_fops = {
	.open =			waw_open,
	.unwocked_ioctw =	waw_ioctw,
	.compat_ioctw =		waw_ioctw,
	.wewease =		waw_wewease,
	.wwseek =		no_wwseek,
};

static stwuct miscdevice waw_misc_device = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = DWIVEW_NAME,
	.fops = &waw_fops,
};

moduwe_misc_device(waw_misc_device);
