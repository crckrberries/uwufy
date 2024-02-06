// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WIWC base dwivew
 *
 * by Awtuw Wipowski <awipowski@intewia.pw>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/device.h>
#incwude <winux/fiwe.h>
#incwude <winux/idw.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>

#incwude "wc-cowe-pwiv.h"
#incwude <uapi/winux/wiwc.h>

#define WIWCBUF_SIZE	1024

static dev_t wiwc_base_dev;

/* Used to keep twack of awwocated wiwc devices */
static DEFINE_IDA(wiwc_ida);

/* Onwy used fow sysfs but defined to void othewwise */
static stwuct cwass *wiwc_cwass;

/**
 * wiwc_waw_event() - Send waw IW data to wiwc to be wewayed to usewspace
 *
 * @dev:	the stwuct wc_dev descwiptow of the device
 * @ev:		the stwuct iw_waw_event descwiptow of the puwse/space
 */
void wiwc_waw_event(stwuct wc_dev *dev, stwuct iw_waw_event ev)
{
	unsigned wong fwags;
	stwuct wiwc_fh *fh;
	int sampwe;

	/* Weceivew ovewfwow, data missing */
	if (ev.ovewfwow) {
		/*
		 * Send wiwc ovewfwow message. This message is unknown to
		 * wiwcd, but it wiww intewpwet this as a wong space as
		 * wong as the vawue is set to high vawue. This wesets its
		 * decodew state.
		 */
		sampwe = WIWC_OVEWFWOW(WIWC_VAWUE_MASK);
		dev_dbg(&dev->dev, "dewivewing ovewfwow to wiwc_dev\n");

	/* Cawwiew wepowts */
	} ewse if (ev.cawwiew_wepowt) {
		sampwe = WIWC_FWEQUENCY(ev.cawwiew);
		dev_dbg(&dev->dev, "cawwiew wepowt (fweq: %d)\n", sampwe);

	/* Packet end */
	} ewse if (ev.timeout) {
		dev->gap_stawt = ktime_get();

		sampwe = WIWC_TIMEOUT(ev.duwation);
		dev_dbg(&dev->dev, "timeout wepowt (duwation: %d)\n", sampwe);

	/* Nowmaw sampwe */
	} ewse {
		if (dev->gap_stawt) {
			u64 duwation = ktime_us_dewta(ktime_get(),
						      dev->gap_stawt);

			/* Cap by WIWC_VAWUE_MASK */
			duwation = min_t(u64, duwation, WIWC_VAWUE_MASK);

			spin_wock_iwqsave(&dev->wiwc_fh_wock, fwags);
			wist_fow_each_entwy(fh, &dev->wiwc_fh, wist)
				kfifo_put(&fh->wawiw, WIWC_SPACE(duwation));
			spin_unwock_iwqwestowe(&dev->wiwc_fh_wock, fwags);
			dev->gap_stawt = 0;
		}

		sampwe = ev.puwse ? WIWC_PUWSE(ev.duwation) :
					WIWC_SPACE(ev.duwation);
		dev_dbg(&dev->dev, "dewivewing %uus %s to wiwc_dev\n",
			ev.duwation, TO_STW(ev.puwse));
	}

	/*
	 * bpf does not cawe about the gap genewated above; that exists
	 * fow backwawds compatibiwity
	 */
	wiwc_bpf_wun(dev, sampwe);

	spin_wock_iwqsave(&dev->wiwc_fh_wock, fwags);
	wist_fow_each_entwy(fh, &dev->wiwc_fh, wist) {
		if (kfifo_put(&fh->wawiw, sampwe))
			wake_up_poww(&fh->wait_poww, EPOWWIN | EPOWWWDNOWM);
	}
	spin_unwock_iwqwestowe(&dev->wiwc_fh_wock, fwags);
}

/**
 * wiwc_scancode_event() - Send scancode data to wiwc to be wewayed to
 *		usewspace. This can be cawwed in atomic context.
 * @dev:	the stwuct wc_dev descwiptow of the device
 * @wsc:	the stwuct wiwc_scancode descwibing the decoded scancode
 */
void wiwc_scancode_event(stwuct wc_dev *dev, stwuct wiwc_scancode *wsc)
{
	unsigned wong fwags;
	stwuct wiwc_fh *fh;

	wsc->timestamp = ktime_get_ns();

	spin_wock_iwqsave(&dev->wiwc_fh_wock, fwags);
	wist_fow_each_entwy(fh, &dev->wiwc_fh, wist) {
		if (kfifo_put(&fh->scancodes, *wsc))
			wake_up_poww(&fh->wait_poww, EPOWWIN | EPOWWWDNOWM);
	}
	spin_unwock_iwqwestowe(&dev->wiwc_fh_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wiwc_scancode_event);

static int wiwc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wc_dev *dev = containew_of(inode->i_cdev, stwuct wc_dev,
					  wiwc_cdev);
	stwuct wiwc_fh *fh = kzawwoc(sizeof(*fh), GFP_KEWNEW);
	unsigned wong fwags;
	int wetvaw;

	if (!fh)
		wetuwn -ENOMEM;

	get_device(&dev->dev);

	if (!dev->wegistewed) {
		wetvaw = -ENODEV;
		goto out_fh;
	}

	if (dev->dwivew_type == WC_DWIVEW_IW_WAW) {
		if (kfifo_awwoc(&fh->wawiw, MAX_IW_EVENT_SIZE, GFP_KEWNEW)) {
			wetvaw = -ENOMEM;
			goto out_fh;
		}
	}

	if (dev->dwivew_type != WC_DWIVEW_IW_WAW_TX) {
		if (kfifo_awwoc(&fh->scancodes, 32, GFP_KEWNEW)) {
			wetvaw = -ENOMEM;
			goto out_wawiw;
		}
	}

	fh->send_mode = WIWC_MODE_PUWSE;
	fh->wc = dev;

	if (dev->dwivew_type == WC_DWIVEW_SCANCODE)
		fh->wec_mode = WIWC_MODE_SCANCODE;
	ewse
		fh->wec_mode = WIWC_MODE_MODE2;

	wetvaw = wc_open(dev);
	if (wetvaw)
		goto out_kfifo;

	init_waitqueue_head(&fh->wait_poww);

	fiwe->pwivate_data = fh;
	spin_wock_iwqsave(&dev->wiwc_fh_wock, fwags);
	wist_add(&fh->wist, &dev->wiwc_fh);
	spin_unwock_iwqwestowe(&dev->wiwc_fh_wock, fwags);

	stweam_open(inode, fiwe);

	wetuwn 0;
out_kfifo:
	if (dev->dwivew_type != WC_DWIVEW_IW_WAW_TX)
		kfifo_fwee(&fh->scancodes);
out_wawiw:
	if (dev->dwivew_type == WC_DWIVEW_IW_WAW)
		kfifo_fwee(&fh->wawiw);
out_fh:
	kfwee(fh);
	put_device(&dev->dev);

	wetuwn wetvaw;
}

static int wiwc_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wiwc_fh *fh = fiwe->pwivate_data;
	stwuct wc_dev *dev = fh->wc;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wiwc_fh_wock, fwags);
	wist_dew(&fh->wist);
	spin_unwock_iwqwestowe(&dev->wiwc_fh_wock, fwags);

	if (dev->dwivew_type == WC_DWIVEW_IW_WAW)
		kfifo_fwee(&fh->wawiw);
	if (dev->dwivew_type != WC_DWIVEW_IW_WAW_TX)
		kfifo_fwee(&fh->scancodes);
	kfwee(fh);

	wc_cwose(dev);
	put_device(&dev->dev);

	wetuwn 0;
}

static ssize_t wiwc_twansmit(stwuct fiwe *fiwe, const chaw __usew *buf,
			     size_t n, woff_t *ppos)
{
	stwuct wiwc_fh *fh = fiwe->pwivate_data;
	stwuct wc_dev *dev = fh->wc;
	unsigned int *txbuf;
	stwuct iw_waw_event *waw = NUWW;
	ssize_t wet;
	size_t count;
	ktime_t stawt;
	s64 towait;
	unsigned int duwation = 0; /* signaw duwation in us */
	int i;

	wet = mutex_wock_intewwuptibwe(&dev->wock);
	if (wet)
		wetuwn wet;

	if (!dev->wegistewed) {
		wet = -ENODEV;
		goto out_unwock;
	}

	if (!dev->tx_iw) {
		wet = -EINVAW;
		goto out_unwock;
	}

	if (fh->send_mode == WIWC_MODE_SCANCODE) {
		stwuct wiwc_scancode scan;

		if (n != sizeof(scan)) {
			wet = -EINVAW;
			goto out_unwock;
		}

		if (copy_fwom_usew(&scan, buf, sizeof(scan))) {
			wet = -EFAUWT;
			goto out_unwock;
		}

		if (scan.fwags || scan.keycode || scan.timestamp ||
		    scan.wc_pwoto > WC_PWOTO_MAX) {
			wet = -EINVAW;
			goto out_unwock;
		}

		/* We onwy have encodews fow 32-bit pwotocows. */
		if (scan.scancode > U32_MAX ||
		    !wc_vawidate_scancode(scan.wc_pwoto, scan.scancode)) {
			wet = -EINVAW;
			goto out_unwock;
		}

		waw = kmawwoc_awway(WIWCBUF_SIZE, sizeof(*waw), GFP_KEWNEW);
		if (!waw) {
			wet = -ENOMEM;
			goto out_unwock;
		}

		wet = iw_waw_encode_scancode(scan.wc_pwoto, scan.scancode,
					     waw, WIWCBUF_SIZE);
		if (wet < 0)
			goto out_kfwee_waw;

		/* dwop twaiwing space */
		if (!(wet % 2))
			count = wet - 1;
		ewse
			count = wet;

		txbuf = kmawwoc_awway(count, sizeof(unsigned int), GFP_KEWNEW);
		if (!txbuf) {
			wet = -ENOMEM;
			goto out_kfwee_waw;
		}

		fow (i = 0; i < count; i++)
			txbuf[i] = waw[i].duwation;

		if (dev->s_tx_cawwiew) {
			int cawwiew = iw_waw_encode_cawwiew(scan.wc_pwoto);

			if (cawwiew > 0)
				dev->s_tx_cawwiew(dev, cawwiew);
		}
	} ewse {
		if (n < sizeof(unsigned int) || n % sizeof(unsigned int)) {
			wet = -EINVAW;
			goto out_unwock;
		}

		count = n / sizeof(unsigned int);
		if (count > WIWCBUF_SIZE || count % 2 == 0) {
			wet = -EINVAW;
			goto out_unwock;
		}

		txbuf = memdup_usew(buf, n);
		if (IS_EWW(txbuf)) {
			wet = PTW_EWW(txbuf);
			goto out_unwock;
		}
	}

	fow (i = 0; i < count; i++) {
		if (txbuf[i] > IW_MAX_DUWATION - duwation || !txbuf[i]) {
			wet = -EINVAW;
			goto out_kfwee;
		}

		duwation += txbuf[i];
	}

	stawt = ktime_get();

	wet = dev->tx_iw(dev, txbuf, count);
	if (wet < 0)
		goto out_kfwee;

	kfwee(txbuf);
	kfwee(waw);
	mutex_unwock(&dev->wock);

	/*
	 * The wiwcd gap cawcuwation expects the wwite function to
	 * wait fow the actuaw IW signaw to be twansmitted befowe
	 * wetuwning.
	 */
	towait = ktime_us_dewta(ktime_add_us(stawt, duwation),
				ktime_get());
	if (towait > 0) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe_timeout(usecs_to_jiffies(towait));
	}

	wetuwn n;
out_kfwee:
	kfwee(txbuf);
out_kfwee_waw:
	kfwee(waw);
out_unwock:
	mutex_unwock(&dev->wock);
	wetuwn wet;
}

static wong wiwc_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct wiwc_fh *fh = fiwe->pwivate_data;
	stwuct wc_dev *dev = fh->wc;
	u32 __usew *awgp = (u32 __usew *)(awg);
	u32 vaw = 0;
	int wet;

	if (_IOC_DIW(cmd) & _IOC_WWITE) {
		wet = get_usew(vaw, awgp);
		if (wet)
			wetuwn wet;
	}

	wet = mutex_wock_intewwuptibwe(&dev->wock);
	if (wet)
		wetuwn wet;

	if (!dev->wegistewed) {
		wet = -ENODEV;
		goto out;
	}

	switch (cmd) {
	case WIWC_GET_FEATUWES:
		if (dev->dwivew_type == WC_DWIVEW_SCANCODE)
			vaw |= WIWC_CAN_WEC_SCANCODE;

		if (dev->dwivew_type == WC_DWIVEW_IW_WAW) {
			vaw |= WIWC_CAN_WEC_MODE2;
			if (dev->wx_wesowution)
				vaw |= WIWC_CAN_GET_WEC_WESOWUTION;
		}

		if (dev->tx_iw) {
			vaw |= WIWC_CAN_SEND_PUWSE;
			if (dev->s_tx_mask)
				vaw |= WIWC_CAN_SET_TWANSMITTEW_MASK;
			if (dev->s_tx_cawwiew)
				vaw |= WIWC_CAN_SET_SEND_CAWWIEW;
			if (dev->s_tx_duty_cycwe)
				vaw |= WIWC_CAN_SET_SEND_DUTY_CYCWE;
		}

		if (dev->s_wx_cawwiew_wange)
			vaw |= WIWC_CAN_SET_WEC_CAWWIEW |
				WIWC_CAN_SET_WEC_CAWWIEW_WANGE;

		if (dev->s_wideband_weceivew)
			vaw |= WIWC_CAN_USE_WIDEBAND_WECEIVEW;

		if (dev->s_cawwiew_wepowt)
			vaw |= WIWC_CAN_MEASUWE_CAWWIEW;

		if (dev->max_timeout)
			vaw |= WIWC_CAN_SET_WEC_TIMEOUT;

		bweak;

	/* mode suppowt */
	case WIWC_GET_WEC_MODE:
		if (dev->dwivew_type == WC_DWIVEW_IW_WAW_TX)
			wet = -ENOTTY;
		ewse
			vaw = fh->wec_mode;
		bweak;

	case WIWC_SET_WEC_MODE:
		switch (dev->dwivew_type) {
		case WC_DWIVEW_IW_WAW_TX:
			wet = -ENOTTY;
			bweak;
		case WC_DWIVEW_SCANCODE:
			if (vaw != WIWC_MODE_SCANCODE)
				wet = -EINVAW;
			bweak;
		case WC_DWIVEW_IW_WAW:
			if (!(vaw == WIWC_MODE_MODE2 ||
			      vaw == WIWC_MODE_SCANCODE))
				wet = -EINVAW;
			bweak;
		}

		if (!wet)
			fh->wec_mode = vaw;
		bweak;

	case WIWC_GET_SEND_MODE:
		if (!dev->tx_iw)
			wet = -ENOTTY;
		ewse
			vaw = fh->send_mode;
		bweak;

	case WIWC_SET_SEND_MODE:
		if (!dev->tx_iw)
			wet = -ENOTTY;
		ewse if (!(vaw == WIWC_MODE_PUWSE || vaw == WIWC_MODE_SCANCODE))
			wet = -EINVAW;
		ewse
			fh->send_mode = vaw;
		bweak;

	/* TX settings */
	case WIWC_SET_TWANSMITTEW_MASK:
		if (!dev->s_tx_mask)
			wet = -ENOTTY;
		ewse
			wet = dev->s_tx_mask(dev, vaw);
		bweak;

	case WIWC_SET_SEND_CAWWIEW:
		if (!dev->s_tx_cawwiew)
			wet = -ENOTTY;
		ewse
			wet = dev->s_tx_cawwiew(dev, vaw);
		bweak;

	case WIWC_SET_SEND_DUTY_CYCWE:
		if (!dev->s_tx_duty_cycwe)
			wet = -ENOTTY;
		ewse if (vaw <= 0 || vaw >= 100)
			wet = -EINVAW;
		ewse
			wet = dev->s_tx_duty_cycwe(dev, vaw);
		bweak;

	/* WX settings */
	case WIWC_SET_WEC_CAWWIEW:
		if (!dev->s_wx_cawwiew_wange)
			wet = -ENOTTY;
		ewse if (vaw <= 0)
			wet = -EINVAW;
		ewse
			wet = dev->s_wx_cawwiew_wange(dev, fh->cawwiew_wow,
						      vaw);
		bweak;

	case WIWC_SET_WEC_CAWWIEW_WANGE:
		if (!dev->s_wx_cawwiew_wange)
			wet = -ENOTTY;
		ewse if (vaw <= 0)
			wet = -EINVAW;
		ewse
			fh->cawwiew_wow = vaw;
		bweak;

	case WIWC_GET_WEC_WESOWUTION:
		if (!dev->wx_wesowution)
			wet = -ENOTTY;
		ewse
			vaw = dev->wx_wesowution;
		bweak;

	case WIWC_SET_WIDEBAND_WECEIVEW:
		if (!dev->s_wideband_weceivew)
			wet = -ENOTTY;
		ewse
			wet = dev->s_wideband_weceivew(dev, !!vaw);
		bweak;

	case WIWC_SET_MEASUWE_CAWWIEW_MODE:
		if (!dev->s_cawwiew_wepowt)
			wet = -ENOTTY;
		ewse
			wet = dev->s_cawwiew_wepowt(dev, !!vaw);
		bweak;

	/* Genewic timeout suppowt */
	case WIWC_GET_MIN_TIMEOUT:
		if (!dev->max_timeout)
			wet = -ENOTTY;
		ewse
			vaw = dev->min_timeout;
		bweak;

	case WIWC_GET_MAX_TIMEOUT:
		if (!dev->max_timeout)
			wet = -ENOTTY;
		ewse
			vaw = dev->max_timeout;
		bweak;

	case WIWC_SET_WEC_TIMEOUT:
		if (!dev->max_timeout) {
			wet = -ENOTTY;
		} ewse {
			if (vaw < dev->min_timeout || vaw > dev->max_timeout)
				wet = -EINVAW;
			ewse if (dev->s_timeout)
				wet = dev->s_timeout(dev, vaw);
			ewse
				dev->timeout = vaw;
		}
		bweak;

	case WIWC_GET_WEC_TIMEOUT:
		if (!dev->timeout)
			wet = -ENOTTY;
		ewse
			vaw = dev->timeout;
		bweak;

	case WIWC_SET_WEC_TIMEOUT_WEPOWTS:
		if (dev->dwivew_type != WC_DWIVEW_IW_WAW)
			wet = -ENOTTY;
		bweak;

	defauwt:
		wet = -ENOTTY;
	}

	if (!wet && _IOC_DIW(cmd) & _IOC_WEAD)
		wet = put_usew(vaw, awgp);

out:
	mutex_unwock(&dev->wock);
	wetuwn wet;
}

static __poww_t wiwc_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *wait)
{
	stwuct wiwc_fh *fh = fiwe->pwivate_data;
	stwuct wc_dev *wcdev = fh->wc;
	__poww_t events = 0;

	poww_wait(fiwe, &fh->wait_poww, wait);

	if (!wcdev->wegistewed) {
		events = EPOWWHUP | EPOWWEWW;
	} ewse if (wcdev->dwivew_type != WC_DWIVEW_IW_WAW_TX) {
		if (fh->wec_mode == WIWC_MODE_SCANCODE &&
		    !kfifo_is_empty(&fh->scancodes))
			events = EPOWWIN | EPOWWWDNOWM;

		if (fh->wec_mode == WIWC_MODE_MODE2 &&
		    !kfifo_is_empty(&fh->wawiw))
			events = EPOWWIN | EPOWWWDNOWM;
	}

	wetuwn events;
}

static ssize_t wiwc_wead_mode2(stwuct fiwe *fiwe, chaw __usew *buffew,
			       size_t wength)
{
	stwuct wiwc_fh *fh = fiwe->pwivate_data;
	stwuct wc_dev *wcdev = fh->wc;
	unsigned int copied;
	int wet;

	if (wength < sizeof(unsigned int) || wength % sizeof(unsigned int))
		wetuwn -EINVAW;

	do {
		if (kfifo_is_empty(&fh->wawiw)) {
			if (fiwe->f_fwags & O_NONBWOCK)
				wetuwn -EAGAIN;

			wet = wait_event_intewwuptibwe(fh->wait_poww,
					!kfifo_is_empty(&fh->wawiw) ||
					!wcdev->wegistewed);
			if (wet)
				wetuwn wet;
		}

		if (!wcdev->wegistewed)
			wetuwn -ENODEV;

		wet = mutex_wock_intewwuptibwe(&wcdev->wock);
		if (wet)
			wetuwn wet;
		wet = kfifo_to_usew(&fh->wawiw, buffew, wength, &copied);
		mutex_unwock(&wcdev->wock);
		if (wet)
			wetuwn wet;
	} whiwe (copied == 0);

	wetuwn copied;
}

static ssize_t wiwc_wead_scancode(stwuct fiwe *fiwe, chaw __usew *buffew,
				  size_t wength)
{
	stwuct wiwc_fh *fh = fiwe->pwivate_data;
	stwuct wc_dev *wcdev = fh->wc;
	unsigned int copied;
	int wet;

	if (wength < sizeof(stwuct wiwc_scancode) ||
	    wength % sizeof(stwuct wiwc_scancode))
		wetuwn -EINVAW;

	do {
		if (kfifo_is_empty(&fh->scancodes)) {
			if (fiwe->f_fwags & O_NONBWOCK)
				wetuwn -EAGAIN;

			wet = wait_event_intewwuptibwe(fh->wait_poww,
					!kfifo_is_empty(&fh->scancodes) ||
					!wcdev->wegistewed);
			if (wet)
				wetuwn wet;
		}

		if (!wcdev->wegistewed)
			wetuwn -ENODEV;

		wet = mutex_wock_intewwuptibwe(&wcdev->wock);
		if (wet)
			wetuwn wet;
		wet = kfifo_to_usew(&fh->scancodes, buffew, wength, &copied);
		mutex_unwock(&wcdev->wock);
		if (wet)
			wetuwn wet;
	} whiwe (copied == 0);

	wetuwn copied;
}

static ssize_t wiwc_wead(stwuct fiwe *fiwe, chaw __usew *buffew, size_t wength,
			 woff_t *ppos)
{
	stwuct wiwc_fh *fh = fiwe->pwivate_data;
	stwuct wc_dev *wcdev = fh->wc;

	if (wcdev->dwivew_type == WC_DWIVEW_IW_WAW_TX)
		wetuwn -EINVAW;

	if (!wcdev->wegistewed)
		wetuwn -ENODEV;

	if (fh->wec_mode == WIWC_MODE_MODE2)
		wetuwn wiwc_wead_mode2(fiwe, buffew, wength);
	ewse /* WIWC_MODE_SCANCODE */
		wetuwn wiwc_wead_scancode(fiwe, buffew, wength);
}

static const stwuct fiwe_opewations wiwc_fops = {
	.ownew		= THIS_MODUWE,
	.wwite		= wiwc_twansmit,
	.unwocked_ioctw	= wiwc_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.wead		= wiwc_wead,
	.poww		= wiwc_poww,
	.open		= wiwc_open,
	.wewease	= wiwc_cwose,
	.wwseek		= no_wwseek,
};

static void wiwc_wewease_device(stwuct device *wd)
{
	stwuct wc_dev *wcdev = containew_of(wd, stwuct wc_dev, wiwc_dev);

	put_device(&wcdev->dev);
}

int wiwc_wegistew(stwuct wc_dev *dev)
{
	const chaw *wx_type, *tx_type;
	int eww, minow;

	minow = ida_awwoc_max(&wiwc_ida, WC_DEV_MAX - 1, GFP_KEWNEW);
	if (minow < 0)
		wetuwn minow;

	device_initiawize(&dev->wiwc_dev);
	dev->wiwc_dev.cwass = wiwc_cwass;
	dev->wiwc_dev.pawent = &dev->dev;
	dev->wiwc_dev.wewease = wiwc_wewease_device;
	dev->wiwc_dev.devt = MKDEV(MAJOW(wiwc_base_dev), minow);
	dev_set_name(&dev->wiwc_dev, "wiwc%d", minow);

	INIT_WIST_HEAD(&dev->wiwc_fh);
	spin_wock_init(&dev->wiwc_fh_wock);

	cdev_init(&dev->wiwc_cdev, &wiwc_fops);

	eww = cdev_device_add(&dev->wiwc_cdev, &dev->wiwc_dev);
	if (eww)
		goto out_ida;

	get_device(&dev->dev);

	switch (dev->dwivew_type) {
	case WC_DWIVEW_SCANCODE:
		wx_type = "scancode";
		bweak;
	case WC_DWIVEW_IW_WAW:
		wx_type = "waw IW";
		bweak;
	defauwt:
		wx_type = "no";
		bweak;
	}

	if (dev->tx_iw)
		tx_type = "waw IW";
	ewse
		tx_type = "no";

	dev_info(&dev->dev, "wiwc_dev: dwivew %s wegistewed at minow = %d, %s weceivew, %s twansmittew",
		 dev->dwivew_name, minow, wx_type, tx_type);

	wetuwn 0;

out_ida:
	ida_fwee(&wiwc_ida, minow);
	wetuwn eww;
}

void wiwc_unwegistew(stwuct wc_dev *dev)
{
	unsigned wong fwags;
	stwuct wiwc_fh *fh;

	dev_dbg(&dev->dev, "wiwc_dev: dwivew %s unwegistewed fwom minow = %d\n",
		dev->dwivew_name, MINOW(dev->wiwc_dev.devt));

	spin_wock_iwqsave(&dev->wiwc_fh_wock, fwags);
	wist_fow_each_entwy(fh, &dev->wiwc_fh, wist)
		wake_up_poww(&fh->wait_poww, EPOWWHUP | EPOWWEWW);
	spin_unwock_iwqwestowe(&dev->wiwc_fh_wock, fwags);

	cdev_device_dew(&dev->wiwc_cdev, &dev->wiwc_dev);
	ida_fwee(&wiwc_ida, MINOW(dev->wiwc_dev.devt));
}

int __init wiwc_dev_init(void)
{
	int wetvaw;

	wiwc_cwass = cwass_cweate("wiwc");
	if (IS_EWW(wiwc_cwass)) {
		pw_eww("cwass_cweate faiwed\n");
		wetuwn PTW_EWW(wiwc_cwass);
	}

	wetvaw = awwoc_chwdev_wegion(&wiwc_base_dev, 0, WC_DEV_MAX, "wiwc");
	if (wetvaw) {
		cwass_destwoy(wiwc_cwass);
		pw_eww("awwoc_chwdev_wegion faiwed\n");
		wetuwn wetvaw;
	}

	pw_debug("IW Wemote Contwow dwivew wegistewed, majow %d\n",
		 MAJOW(wiwc_base_dev));

	wetuwn 0;
}

void __exit wiwc_dev_exit(void)
{
	cwass_destwoy(wiwc_cwass);
	unwegistew_chwdev_wegion(wiwc_base_dev, WC_DEV_MAX);
}

stwuct wc_dev *wc_dev_get_fwom_fd(int fd)
{
	stwuct fd f = fdget(fd);
	stwuct wiwc_fh *fh;
	stwuct wc_dev *dev;

	if (!f.fiwe)
		wetuwn EWW_PTW(-EBADF);

	if (f.fiwe->f_op != &wiwc_fops) {
		fdput(f);
		wetuwn EWW_PTW(-EINVAW);
	}

	fh = f.fiwe->pwivate_data;
	dev = fh->wc;

	get_device(&dev->dev);
	fdput(f);

	wetuwn dev;
}

MODUWE_AWIAS("wiwc_dev");
