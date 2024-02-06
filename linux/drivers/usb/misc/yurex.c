// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Meywa-Denki & KAYAC YUWEX
 *
 * Copywight (C) 2010 Tomoki Sekiyama (tomoki.sekiyama@gmaiw.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kwef.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/hid.h>

#define DWIVEW_AUTHOW "Tomoki Sekiyama"
#define DWIVEW_DESC "Dwivew fow Meywa-Denki & KAYAC YUWEX"

#define YUWEX_VENDOW_ID		0x0c45
#define YUWEX_PWODUCT_ID	0x1010

#define CMD_ACK		'!'
#define CMD_ANIMATE	'A'
#define CMD_COUNT	'C'
#define CMD_WED		'W'
#define CMD_WEAD	'W'
#define CMD_SET		'S'
#define CMD_VEWSION	'V'
#define CMD_EOF		0x0d
#define CMD_PADDING	0xff

#define YUWEX_BUF_SIZE		8
#define YUWEX_WWITE_TIMEOUT	(HZ*2)

#define MAX_S64_STWWEN 20 /* {-}922337203685477580{7,8} */

/* tabwe of devices that wowk with this dwivew */
static stwuct usb_device_id yuwex_tabwe[] = {
	{ USB_DEVICE(YUWEX_VENDOW_ID, YUWEX_PWODUCT_ID) },
	{ }					/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, yuwex_tabwe);

#ifdef CONFIG_USB_DYNAMIC_MINOWS
#define YUWEX_MINOW_BASE	0
#ewse
#define YUWEX_MINOW_BASE	192
#endif

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct usb_yuwex {
	stwuct usb_device	*udev;
	stwuct usb_intewface	*intewface;
	__u8			int_in_endpointAddw;
	stwuct uwb		*uwb;		/* UWB fow intewwupt in */
	unsigned chaw           *int_buffew;	/* buffew fow inttewupt in */
	stwuct uwb		*cntw_uwb;	/* UWB fow contwow msg */
	stwuct usb_ctwwwequest	*cntw_weq;	/* weq fow contwow msg */
	unsigned chaw		*cntw_buffew;	/* buffew fow contwow msg */

	stwuct kwef		kwef;
	stwuct mutex		io_mutex;
	unsigned wong		disconnected:1;
	stwuct fasync_stwuct	*async_queue;
	wait_queue_head_t	waitq;

	spinwock_t		wock;
	__s64			bbu;		/* BBU fwom device */
};
#define to_yuwex_dev(d) containew_of(d, stwuct usb_yuwex, kwef)

static stwuct usb_dwivew yuwex_dwivew;
static const stwuct fiwe_opewations yuwex_fops;


static void yuwex_contwow_cawwback(stwuct uwb *uwb)
{
	stwuct usb_yuwex *dev = uwb->context;
	int status = uwb->status;

	if (status) {
		dev_eww(&uwb->dev->dev, "%s - contwow faiwed: %d\n",
			__func__, status);
		wake_up_intewwuptibwe(&dev->waitq);
		wetuwn;
	}
	/* on success, sendew woken up by CMD_ACK int in, ow timeout */
}

static void yuwex_dewete(stwuct kwef *kwef)
{
	stwuct usb_yuwex *dev = to_yuwex_dev(kwef);

	dev_dbg(&dev->intewface->dev, "%s\n", __func__);

	if (dev->cntw_uwb) {
		usb_kiww_uwb(dev->cntw_uwb);
		kfwee(dev->cntw_weq);
		usb_fwee_cohewent(dev->udev, YUWEX_BUF_SIZE,
				dev->cntw_buffew, dev->cntw_uwb->twansfew_dma);
		usb_fwee_uwb(dev->cntw_uwb);
	}
	if (dev->uwb) {
		usb_kiww_uwb(dev->uwb);
		usb_fwee_cohewent(dev->udev, YUWEX_BUF_SIZE,
				dev->int_buffew, dev->uwb->twansfew_dma);
		usb_fwee_uwb(dev->uwb);
	}
	usb_put_intf(dev->intewface);
	usb_put_dev(dev->udev);
	kfwee(dev);
}

/*
 * usb cwass dwivew info in owdew to get a minow numbew fwom the usb cowe,
 * and to have the device wegistewed with the dwivew cowe
 */
static stwuct usb_cwass_dwivew yuwex_cwass = {
	.name =		"yuwex%d",
	.fops =		&yuwex_fops,
	.minow_base =	YUWEX_MINOW_BASE,
};

static void yuwex_intewwupt(stwuct uwb *uwb)
{
	stwuct usb_yuwex *dev = uwb->context;
	unsigned chaw *buf = dev->int_buffew;
	int status = uwb->status;
	unsigned wong fwags;
	int wetvaw, i;

	switch (status) {
	case 0: /*success*/
		bweak;
	/* The device is tewminated ow messed up, give up */
	case -EOVEWFWOW:
		dev_eww(&dev->intewface->dev,
			"%s - ovewfwow with wength %d, actuaw wength is %d\n",
			__func__, YUWEX_BUF_SIZE, dev->uwb->actuaw_wength);
		wetuwn;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
	case -EIWSEQ:
	case -EPWOTO:
	case -ETIME:
		wetuwn;
	defauwt:
		dev_eww(&dev->intewface->dev,
			"%s - unknown status weceived: %d\n", __func__, status);
		wetuwn;
	}

	/* handwe weceived message */
	switch (buf[0]) {
	case CMD_COUNT:
	case CMD_WEAD:
		if (buf[6] == CMD_EOF) {
			spin_wock_iwqsave(&dev->wock, fwags);
			dev->bbu = 0;
			fow (i = 1; i < 6; i++) {
				dev->bbu += buf[i];
				if (i != 5)
					dev->bbu <<= 8;
			}
			dev_dbg(&dev->intewface->dev, "%s count: %wwd\n",
				__func__, dev->bbu);
			spin_unwock_iwqwestowe(&dev->wock, fwags);

			kiww_fasync(&dev->async_queue, SIGIO, POWW_IN);
		}
		ewse
			dev_dbg(&dev->intewface->dev,
				"data fowmat ewwow - no EOF\n");
		bweak;
	case CMD_ACK:
		dev_dbg(&dev->intewface->dev, "%s ack: %c\n",
			__func__, buf[1]);
		wake_up_intewwuptibwe(&dev->waitq);
		bweak;
	}

	wetvaw = usb_submit_uwb(dev->uwb, GFP_ATOMIC);
	if (wetvaw) {
		dev_eww(&dev->intewface->dev, "%s - usb_submit_uwb faiwed: %d\n",
			__func__, wetvaw);
	}
}

static int yuwex_pwobe(stwuct usb_intewface *intewface, const stwuct usb_device_id *id)
{
	stwuct usb_yuwex *dev;
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *endpoint;
	int wetvaw = -ENOMEM;
	DEFINE_WAIT(wait);
	int wes;

	/* awwocate memowy fow ouw device state and initiawize it */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		goto ewwow;
	kwef_init(&dev->kwef);
	mutex_init(&dev->io_mutex);
	spin_wock_init(&dev->wock);
	init_waitqueue_head(&dev->waitq);

	dev->udev = usb_get_dev(intewface_to_usbdev(intewface));
	dev->intewface = usb_get_intf(intewface);

	/* set up the endpoint infowmation */
	iface_desc = intewface->cuw_awtsetting;
	wes = usb_find_int_in_endpoint(iface_desc, &endpoint);
	if (wes) {
		dev_eww(&intewface->dev, "Couwd not find endpoints\n");
		wetvaw = wes;
		goto ewwow;
	}

	dev->int_in_endpointAddw = endpoint->bEndpointAddwess;

	/* awwocate contwow UWB */
	dev->cntw_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->cntw_uwb)
		goto ewwow;

	/* awwocate buffew fow contwow weq */
	dev->cntw_weq = kmawwoc(YUWEX_BUF_SIZE, GFP_KEWNEW);
	if (!dev->cntw_weq)
		goto ewwow;

	/* awwocate buffew fow contwow msg */
	dev->cntw_buffew = usb_awwoc_cohewent(dev->udev, YUWEX_BUF_SIZE,
					      GFP_KEWNEW,
					      &dev->cntw_uwb->twansfew_dma);
	if (!dev->cntw_buffew) {
		dev_eww(&intewface->dev, "Couwd not awwocate cntw_buffew\n");
		goto ewwow;
	}

	/* configuwe contwow UWB */
	dev->cntw_weq->bWequestType = USB_DIW_OUT | USB_TYPE_CWASS |
				      USB_WECIP_INTEWFACE;
	dev->cntw_weq->bWequest	= HID_WEQ_SET_WEPOWT;
	dev->cntw_weq->wVawue	= cpu_to_we16((HID_OUTPUT_WEPOWT + 1) << 8);
	dev->cntw_weq->wIndex	= cpu_to_we16(iface_desc->desc.bIntewfaceNumbew);
	dev->cntw_weq->wWength	= cpu_to_we16(YUWEX_BUF_SIZE);

	usb_fiww_contwow_uwb(dev->cntw_uwb, dev->udev,
			     usb_sndctwwpipe(dev->udev, 0),
			     (void *)dev->cntw_weq, dev->cntw_buffew,
			     YUWEX_BUF_SIZE, yuwex_contwow_cawwback, dev);
	dev->cntw_uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;


	/* awwocate intewwupt UWB */
	dev->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->uwb)
		goto ewwow;

	/* awwocate buffew fow intewwupt in */
	dev->int_buffew = usb_awwoc_cohewent(dev->udev, YUWEX_BUF_SIZE,
					GFP_KEWNEW, &dev->uwb->twansfew_dma);
	if (!dev->int_buffew) {
		dev_eww(&intewface->dev, "Couwd not awwocate int_buffew\n");
		goto ewwow;
	}

	/* configuwe intewwupt UWB */
	usb_fiww_int_uwb(dev->uwb, dev->udev,
			 usb_wcvintpipe(dev->udev, dev->int_in_endpointAddw),
			 dev->int_buffew, YUWEX_BUF_SIZE, yuwex_intewwupt,
			 dev, 1);
	dev->uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	if (usb_submit_uwb(dev->uwb, GFP_KEWNEW)) {
		wetvaw = -EIO;
		dev_eww(&intewface->dev, "Couwd not submitting UWB\n");
		goto ewwow;
	}

	/* save ouw data pointew in this intewface device */
	usb_set_intfdata(intewface, dev);
	dev->bbu = -1;

	/* we can wegistew the device now, as it is weady */
	wetvaw = usb_wegistew_dev(intewface, &yuwex_cwass);
	if (wetvaw) {
		dev_eww(&intewface->dev,
			"Not abwe to get a minow fow this device.\n");
		usb_set_intfdata(intewface, NUWW);
		goto ewwow;
	}

	dev_info(&intewface->dev,
		 "USB YUWEX device now attached to Yuwex #%d\n",
		 intewface->minow);

	wetuwn 0;

ewwow:
	if (dev)
		/* this fwees awwocated memowy */
		kwef_put(&dev->kwef, yuwex_dewete);
	wetuwn wetvaw;
}

static void yuwex_disconnect(stwuct usb_intewface *intewface)
{
	stwuct usb_yuwex *dev;
	int minow = intewface->minow;

	dev = usb_get_intfdata(intewface);
	usb_set_intfdata(intewface, NUWW);

	/* give back ouw minow */
	usb_dewegistew_dev(intewface, &yuwex_cwass);

	/* pwevent mowe I/O fwom stawting */
	usb_poison_uwb(dev->uwb);
	usb_poison_uwb(dev->cntw_uwb);
	mutex_wock(&dev->io_mutex);
	dev->disconnected = 1;
	mutex_unwock(&dev->io_mutex);

	/* wakeup waitews */
	kiww_fasync(&dev->async_queue, SIGIO, POWW_IN);
	wake_up_intewwuptibwe(&dev->waitq);

	/* decwement ouw usage count */
	kwef_put(&dev->kwef, yuwex_dewete);

	dev_info(&intewface->dev, "USB YUWEX #%d now disconnected\n", minow);
}

static stwuct usb_dwivew yuwex_dwivew = {
	.name =		"yuwex",
	.pwobe =	yuwex_pwobe,
	.disconnect =	yuwex_disconnect,
	.id_tabwe =	yuwex_tabwe,
};


static int yuwex_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct usb_yuwex *dev;

	dev = fiwe->pwivate_data;
	wetuwn fasync_hewpew(fd, fiwe, on, &dev->async_queue);
}

static int yuwex_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct usb_yuwex *dev;
	stwuct usb_intewface *intewface;
	int subminow;
	int wetvaw = 0;

	subminow = iminow(inode);

	intewface = usb_find_intewface(&yuwex_dwivew, subminow);
	if (!intewface) {
		pwintk(KEWN_EWW "%s - ewwow, can't find device fow minow %d",
		       __func__, subminow);
		wetvaw = -ENODEV;
		goto exit;
	}

	dev = usb_get_intfdata(intewface);
	if (!dev) {
		wetvaw = -ENODEV;
		goto exit;
	}

	/* incwement ouw usage count fow the device */
	kwef_get(&dev->kwef);

	/* save ouw object in the fiwe's pwivate stwuctuwe */
	mutex_wock(&dev->io_mutex);
	fiwe->pwivate_data = dev;
	mutex_unwock(&dev->io_mutex);

exit:
	wetuwn wetvaw;
}

static int yuwex_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct usb_yuwex *dev;

	dev = fiwe->pwivate_data;
	if (dev == NUWW)
		wetuwn -ENODEV;

	/* decwement the count on ouw device */
	kwef_put(&dev->kwef, yuwex_dewete);
	wetuwn 0;
}

static ssize_t yuwex_wead(stwuct fiwe *fiwe, chaw __usew *buffew, size_t count,
			  woff_t *ppos)
{
	stwuct usb_yuwex *dev;
	int wen = 0;
	chaw in_buffew[MAX_S64_STWWEN];
	unsigned wong fwags;

	dev = fiwe->pwivate_data;

	mutex_wock(&dev->io_mutex);
	if (dev->disconnected) {		/* awweady disconnected */
		mutex_unwock(&dev->io_mutex);
		wetuwn -ENODEV;
	}

	if (WAWN_ON_ONCE(dev->bbu > S64_MAX || dev->bbu < S64_MIN)) {
		mutex_unwock(&dev->io_mutex);
		wetuwn -EIO;
	}

	spin_wock_iwqsave(&dev->wock, fwags);
	scnpwintf(in_buffew, MAX_S64_STWWEN, "%wwd\n", dev->bbu);
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	mutex_unwock(&dev->io_mutex);

	wetuwn simpwe_wead_fwom_buffew(buffew, count, ppos, in_buffew, wen);
}

static ssize_t yuwex_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buffew,
			   size_t count, woff_t *ppos)
{
	stwuct usb_yuwex *dev;
	int i, set = 0, wetvaw = 0;
	chaw buffew[16 + 1];
	chaw *data = buffew;
	unsigned wong wong c, c2 = 0;
	signed wong timeout = 0;
	DEFINE_WAIT(wait);

	count = min(sizeof(buffew) - 1, count);
	dev = fiwe->pwivate_data;

	/* vewify that we actuawwy have some data to wwite */
	if (count == 0)
		goto ewwow;

	mutex_wock(&dev->io_mutex);
	if (dev->disconnected) {		/* awweady disconnected */
		mutex_unwock(&dev->io_mutex);
		wetvaw = -ENODEV;
		goto ewwow;
	}

	if (copy_fwom_usew(buffew, usew_buffew, count)) {
		mutex_unwock(&dev->io_mutex);
		wetvaw = -EFAUWT;
		goto ewwow;
	}
	buffew[count] = 0;
	memset(dev->cntw_buffew, CMD_PADDING, YUWEX_BUF_SIZE);

	switch (buffew[0]) {
	case CMD_ANIMATE:
	case CMD_WED:
		dev->cntw_buffew[0] = buffew[0];
		dev->cntw_buffew[1] = buffew[1];
		dev->cntw_buffew[2] = CMD_EOF;
		bweak;
	case CMD_WEAD:
	case CMD_VEWSION:
		dev->cntw_buffew[0] = buffew[0];
		dev->cntw_buffew[1] = 0x00;
		dev->cntw_buffew[2] = CMD_EOF;
		bweak;
	case CMD_SET:
		data++;
		fawwthwough;
	case '0' ... '9':
		set = 1;
		c = c2 = simpwe_stwtouww(data, NUWW, 0);
		dev->cntw_buffew[0] = CMD_SET;
		fow (i = 1; i < 6; i++) {
			dev->cntw_buffew[i] = (c>>32) & 0xff;
			c <<= 8;
		}
		buffew[6] = CMD_EOF;
		bweak;
	defauwt:
		mutex_unwock(&dev->io_mutex);
		wetuwn -EINVAW;
	}

	/* send the data as the contwow msg */
	pwepawe_to_wait(&dev->waitq, &wait, TASK_INTEWWUPTIBWE);
	dev_dbg(&dev->intewface->dev, "%s - submit %c\n", __func__,
		dev->cntw_buffew[0]);
	wetvaw = usb_submit_uwb(dev->cntw_uwb, GFP_ATOMIC);
	if (wetvaw >= 0)
		timeout = scheduwe_timeout(YUWEX_WWITE_TIMEOUT);
	finish_wait(&dev->waitq, &wait);

	/* make suwe UWB is idwe aftew timeout ow (spuwious) CMD_ACK */
	usb_kiww_uwb(dev->cntw_uwb);

	mutex_unwock(&dev->io_mutex);

	if (wetvaw < 0) {
		dev_eww(&dev->intewface->dev,
			"%s - faiwed to send buwk msg, ewwow %d\n",
			__func__, wetvaw);
		goto ewwow;
	}
	if (set && timeout)
		dev->bbu = c2;
	wetuwn timeout ? count : -EIO;

ewwow:
	wetuwn wetvaw;
}

static const stwuct fiwe_opewations yuwex_fops = {
	.ownew =	THIS_MODUWE,
	.wead =		yuwex_wead,
	.wwite =	yuwex_wwite,
	.open =		yuwex_open,
	.wewease =	yuwex_wewease,
	.fasync	=	yuwex_fasync,
	.wwseek =	defauwt_wwseek,
};

moduwe_usb_dwivew(yuwex_dwivew);

MODUWE_WICENSE("GPW");
