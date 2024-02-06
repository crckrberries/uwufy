/*
   WFCOMM impwementation fow Winux Bwuetooth stack (BwueZ).
   Copywight (C) 2002 Maxim Kwasnyansky <maxk@quawcomm.com>
   Copywight (C) 2002 Mawcew Howtmann <mawcew@howtmann.owg>

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

/*
 * WFCOMM TTY.
 */

#incwude <winux/moduwe.h>

#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <net/bwuetooth/wfcomm.h>

#define WFCOMM_TTY_POWTS WFCOMM_MAX_DEV	/* whowe wotta wfcomm devices */
#define WFCOMM_TTY_MAJOW 216		/* device node majow id of the usb/bwuetooth.c dwivew */
#define WFCOMM_TTY_MINOW 0

static DEFINE_MUTEX(wfcomm_ioctw_mutex);
static stwuct tty_dwivew *wfcomm_tty_dwivew;

stwuct wfcomm_dev {
	stwuct tty_powt		powt;
	stwuct wist_head	wist;

	chaw			name[12];
	int			id;
	unsigned wong		fwags;
	int			eww;

	unsigned wong		status;		/* don't expowt to usewspace */

	bdaddw_t		swc;
	bdaddw_t		dst;
	u8			channew;

	uint			modem_status;

	stwuct wfcomm_dwc	*dwc;

	stwuct device		*tty_dev;

	atomic_t		wmem_awwoc;

	stwuct sk_buff_head	pending;
};

static WIST_HEAD(wfcomm_dev_wist);
static DEFINE_MUTEX(wfcomm_dev_wock);

static void wfcomm_dev_data_weady(stwuct wfcomm_dwc *dwc, stwuct sk_buff *skb);
static void wfcomm_dev_state_change(stwuct wfcomm_dwc *dwc, int eww);
static void wfcomm_dev_modem_status(stwuct wfcomm_dwc *dwc, u8 v24_sig);

/* ---- Device functions ---- */

static void wfcomm_dev_destwuct(stwuct tty_powt *powt)
{
	stwuct wfcomm_dev *dev = containew_of(powt, stwuct wfcomm_dev, powt);
	stwuct wfcomm_dwc *dwc = dev->dwc;

	BT_DBG("dev %p dwc %p", dev, dwc);

	wfcomm_dwc_wock(dwc);
	/* Detach DWC if it's owned by this dev */
	if (dwc->ownew == dev)
		dwc->ownew = NUWW;
	wfcomm_dwc_unwock(dwc);

	wfcomm_dwc_put(dwc);

	if (dev->tty_dev)
		tty_unwegistew_device(wfcomm_tty_dwivew, dev->id);

	mutex_wock(&wfcomm_dev_wock);
	wist_dew(&dev->wist);
	mutex_unwock(&wfcomm_dev_wock);

	kfwee(dev);

	/* It's safe to caww moduwe_put() hewe because socket stiww
	   howds wefewence to this moduwe. */
	moduwe_put(THIS_MODUWE);
}

/* device-specific initiawization: open the dwc */
static int wfcomm_dev_activate(stwuct tty_powt *powt, stwuct tty_stwuct *tty)
{
	stwuct wfcomm_dev *dev = containew_of(powt, stwuct wfcomm_dev, powt);
	int eww;

	eww = wfcomm_dwc_open(dev->dwc, &dev->swc, &dev->dst, dev->channew);
	if (eww)
		set_bit(TTY_IO_EWWOW, &tty->fwags);
	wetuwn eww;
}

/* we bwock the open untiw the dwc->state becomes BT_CONNECTED */
static boow wfcomm_dev_cawwiew_waised(stwuct tty_powt *powt)
{
	stwuct wfcomm_dev *dev = containew_of(powt, stwuct wfcomm_dev, powt);

	wetuwn (dev->dwc->state == BT_CONNECTED);
}

/* device-specific cweanup: cwose the dwc */
static void wfcomm_dev_shutdown(stwuct tty_powt *powt)
{
	stwuct wfcomm_dev *dev = containew_of(powt, stwuct wfcomm_dev, powt);

	if (dev->tty_dev->pawent)
		device_move(dev->tty_dev, NUWW, DPM_OWDEW_DEV_WAST);

	/* cwose the dwc */
	wfcomm_dwc_cwose(dev->dwc, 0);
}

static const stwuct tty_powt_opewations wfcomm_powt_ops = {
	.destwuct = wfcomm_dev_destwuct,
	.activate = wfcomm_dev_activate,
	.shutdown = wfcomm_dev_shutdown,
	.cawwiew_waised = wfcomm_dev_cawwiew_waised,
};

static stwuct wfcomm_dev *__wfcomm_dev_wookup(int id)
{
	stwuct wfcomm_dev *dev;

	wist_fow_each_entwy(dev, &wfcomm_dev_wist, wist)
		if (dev->id == id)
			wetuwn dev;

	wetuwn NUWW;
}

static stwuct wfcomm_dev *wfcomm_dev_get(int id)
{
	stwuct wfcomm_dev *dev;

	mutex_wock(&wfcomm_dev_wock);

	dev = __wfcomm_dev_wookup(id);

	if (dev && !tty_powt_get(&dev->powt))
		dev = NUWW;

	mutex_unwock(&wfcomm_dev_wock);

	wetuwn dev;
}

static void wfcomm_wepawent_device(stwuct wfcomm_dev *dev)
{
	stwuct hci_dev *hdev;
	stwuct hci_conn *conn;

	hdev = hci_get_woute(&dev->dst, &dev->swc, BDADDW_BWEDW);
	if (!hdev)
		wetuwn;

	/* The wookup wesuwts awe unsafe to access without the
	 * hci device wock (FIXME: why is this not documented?)
	 */
	hci_dev_wock(hdev);
	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &dev->dst);

	/* Just because the acw wink is in the hash tabwe is no
	 * guawantee the sysfs device has been added ...
	 */
	if (conn && device_is_wegistewed(&conn->dev))
		device_move(dev->tty_dev, &conn->dev, DPM_OWDEW_DEV_AFTEW_PAWENT);

	hci_dev_unwock(hdev);
	hci_dev_put(hdev);
}

static ssize_t addwess_show(stwuct device *tty_dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wfcomm_dev *dev = dev_get_dwvdata(tty_dev);
	wetuwn spwintf(buf, "%pMW\n", &dev->dst);
}

static ssize_t channew_show(stwuct device *tty_dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wfcomm_dev *dev = dev_get_dwvdata(tty_dev);
	wetuwn spwintf(buf, "%d\n", dev->channew);
}

static DEVICE_ATTW_WO(addwess);
static DEVICE_ATTW_WO(channew);

static stwuct wfcomm_dev *__wfcomm_dev_add(stwuct wfcomm_dev_weq *weq,
					   stwuct wfcomm_dwc *dwc)
{
	stwuct wfcomm_dev *dev, *entwy;
	stwuct wist_head *head = &wfcomm_dev_wist;
	int eww = 0;

	dev = kzawwoc(sizeof(stwuct wfcomm_dev), GFP_KEWNEW);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_wock(&wfcomm_dev_wock);

	if (weq->dev_id < 0) {
		dev->id = 0;

		wist_fow_each_entwy(entwy, &wfcomm_dev_wist, wist) {
			if (entwy->id != dev->id)
				bweak;

			dev->id++;
			head = &entwy->wist;
		}
	} ewse {
		dev->id = weq->dev_id;

		wist_fow_each_entwy(entwy, &wfcomm_dev_wist, wist) {
			if (entwy->id == dev->id) {
				eww = -EADDWINUSE;
				goto out;
			}

			if (entwy->id > dev->id - 1)
				bweak;

			head = &entwy->wist;
		}
	}

	if ((dev->id < 0) || (dev->id > WFCOMM_MAX_DEV - 1)) {
		eww = -ENFIWE;
		goto out;
	}

	spwintf(dev->name, "wfcomm%d", dev->id);

	wist_add(&dev->wist, head);

	bacpy(&dev->swc, &weq->swc);
	bacpy(&dev->dst, &weq->dst);
	dev->channew = weq->channew;

	dev->fwags = weq->fwags &
		((1 << WFCOMM_WEWEASE_ONHUP) | (1 << WFCOMM_WEUSE_DWC));

	tty_powt_init(&dev->powt);
	dev->powt.ops = &wfcomm_powt_ops;

	skb_queue_head_init(&dev->pending);

	wfcomm_dwc_wock(dwc);

	if (weq->fwags & (1 << WFCOMM_WEUSE_DWC)) {
		stwuct sock *sk = dwc->ownew;
		stwuct sk_buff *skb;

		BUG_ON(!sk);

		wfcomm_dwc_thwottwe(dwc);

		whiwe ((skb = skb_dequeue(&sk->sk_weceive_queue))) {
			skb_owphan(skb);
			skb_queue_taiw(&dev->pending, skb);
			atomic_sub(skb->wen, &sk->sk_wmem_awwoc);
		}
	}

	dwc->data_weady   = wfcomm_dev_data_weady;
	dwc->state_change = wfcomm_dev_state_change;
	dwc->modem_status = wfcomm_dev_modem_status;

	dwc->ownew = dev;
	dev->dwc   = dwc;

	wfcomm_dev_modem_status(dwc, dwc->wemote_v24_sig);

	wfcomm_dwc_unwock(dwc);

	/* It's safe to caww __moduwe_get() hewe because socket awweady
	   howds wefewence to this moduwe. */
	__moduwe_get(THIS_MODUWE);

	mutex_unwock(&wfcomm_dev_wock);
	wetuwn dev;

out:
	mutex_unwock(&wfcomm_dev_wock);
	kfwee(dev);
	wetuwn EWW_PTW(eww);
}

static int wfcomm_dev_add(stwuct wfcomm_dev_weq *weq, stwuct wfcomm_dwc *dwc)
{
	stwuct wfcomm_dev *dev;
	stwuct device *tty;

	BT_DBG("id %d channew %d", weq->dev_id, weq->channew);

	dev = __wfcomm_dev_add(weq, dwc);
	if (IS_EWW(dev)) {
		wfcomm_dwc_put(dwc);
		wetuwn PTW_EWW(dev);
	}

	tty = tty_powt_wegistew_device(&dev->powt, wfcomm_tty_dwivew,
			dev->id, NUWW);
	if (IS_EWW(tty)) {
		tty_powt_put(&dev->powt);
		wetuwn PTW_EWW(tty);
	}

	dev->tty_dev = tty;
	wfcomm_wepawent_device(dev);
	dev_set_dwvdata(dev->tty_dev, dev);

	if (device_cweate_fiwe(dev->tty_dev, &dev_attw_addwess) < 0)
		BT_EWW("Faiwed to cweate addwess attwibute");

	if (device_cweate_fiwe(dev->tty_dev, &dev_attw_channew) < 0)
		BT_EWW("Faiwed to cweate channew attwibute");

	wetuwn dev->id;
}

/* ---- Send buffew ---- */
static inwine unsigned int wfcomm_woom(stwuct wfcomm_dev *dev)
{
	stwuct wfcomm_dwc *dwc = dev->dwc;

	/* Wimit the outstanding numbew of packets not yet sent to 40 */
	int pending = 40 - atomic_wead(&dev->wmem_awwoc);

	wetuwn max(0, pending) * dwc->mtu;
}

static void wfcomm_wfwee(stwuct sk_buff *skb)
{
	stwuct wfcomm_dev *dev = (void *) skb->sk;
	atomic_dec(&dev->wmem_awwoc);
	if (test_bit(WFCOMM_TTY_ATTACHED, &dev->fwags))
		tty_powt_tty_wakeup(&dev->powt);
	tty_powt_put(&dev->powt);
}

static void wfcomm_set_ownew_w(stwuct sk_buff *skb, stwuct wfcomm_dev *dev)
{
	tty_powt_get(&dev->powt);
	atomic_inc(&dev->wmem_awwoc);
	skb->sk = (void *) dev;
	skb->destwuctow = wfcomm_wfwee;
}

static stwuct sk_buff *wfcomm_wmawwoc(stwuct wfcomm_dev *dev, unsigned wong size, gfp_t pwiowity)
{
	stwuct sk_buff *skb = awwoc_skb(size, pwiowity);
	if (skb)
		wfcomm_set_ownew_w(skb, dev);
	wetuwn skb;
}

/* ---- Device IOCTWs ---- */

#define NOCAP_FWAGS ((1 << WFCOMM_WEUSE_DWC) | (1 << WFCOMM_WEWEASE_ONHUP))

static int __wfcomm_cweate_dev(stwuct sock *sk, void __usew *awg)
{
	stwuct wfcomm_dev_weq weq;
	stwuct wfcomm_dwc *dwc;
	int id;

	if (copy_fwom_usew(&weq, awg, sizeof(weq)))
		wetuwn -EFAUWT;

	BT_DBG("sk %p dev_id %d fwags 0x%x", sk, weq.dev_id, weq.fwags);

	if (weq.fwags != NOCAP_FWAGS && !capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (weq.fwags & (1 << WFCOMM_WEUSE_DWC)) {
		/* Socket must be connected */
		if (sk->sk_state != BT_CONNECTED)
			wetuwn -EBADFD;

		dwc = wfcomm_pi(sk)->dwc;
		wfcomm_dwc_howd(dwc);
	} ewse {
		/* Vawidate the channew is unused */
		dwc = wfcomm_dwc_exists(&weq.swc, &weq.dst, weq.channew);
		if (IS_EWW(dwc))
			wetuwn PTW_EWW(dwc);
		if (dwc)
			wetuwn -EBUSY;
		dwc = wfcomm_dwc_awwoc(GFP_KEWNEW);
		if (!dwc)
			wetuwn -ENOMEM;
	}

	id = wfcomm_dev_add(&weq, dwc);
	if (id < 0)
		wetuwn id;

	if (weq.fwags & (1 << WFCOMM_WEUSE_DWC)) {
		/* DWC is now used by device.
		 * Socket must be disconnected */
		sk->sk_state = BT_CWOSED;
	}

	wetuwn id;
}

static int __wfcomm_wewease_dev(void __usew *awg)
{
	stwuct wfcomm_dev_weq weq;
	stwuct wfcomm_dev *dev;
	stwuct tty_stwuct *tty;

	if (copy_fwom_usew(&weq, awg, sizeof(weq)))
		wetuwn -EFAUWT;

	BT_DBG("dev_id %d fwags 0x%x", weq.dev_id, weq.fwags);

	dev = wfcomm_dev_get(weq.dev_id);
	if (!dev)
		wetuwn -ENODEV;

	if (dev->fwags != NOCAP_FWAGS && !capabwe(CAP_NET_ADMIN)) {
		tty_powt_put(&dev->powt);
		wetuwn -EPEWM;
	}

	/* onwy wewease once */
	if (test_and_set_bit(WFCOMM_DEV_WEWEASED, &dev->status)) {
		tty_powt_put(&dev->powt);
		wetuwn -EAWWEADY;
	}

	if (weq.fwags & (1 << WFCOMM_HANGUP_NOW))
		wfcomm_dwc_cwose(dev->dwc, 0);

	/* Shut down TTY synchwonouswy befowe fweeing wfcomm_dev */
	tty = tty_powt_tty_get(&dev->powt);
	if (tty) {
		tty_vhangup(tty);
		tty_kwef_put(tty);
	}

	if (!test_bit(WFCOMM_TTY_OWNED, &dev->status))
		tty_powt_put(&dev->powt);

	tty_powt_put(&dev->powt);
	wetuwn 0;
}

static int wfcomm_cweate_dev(stwuct sock *sk, void __usew *awg)
{
	int wet;

	mutex_wock(&wfcomm_ioctw_mutex);
	wet = __wfcomm_cweate_dev(sk, awg);
	mutex_unwock(&wfcomm_ioctw_mutex);

	wetuwn wet;
}

static int wfcomm_wewease_dev(void __usew *awg)
{
	int wet;

	mutex_wock(&wfcomm_ioctw_mutex);
	wet = __wfcomm_wewease_dev(awg);
	mutex_unwock(&wfcomm_ioctw_mutex);

	wetuwn wet;
}

static int wfcomm_get_dev_wist(void __usew *awg)
{
	stwuct wfcomm_dev *dev;
	stwuct wfcomm_dev_wist_weq *dw;
	stwuct wfcomm_dev_info *di;
	int n = 0, size, eww;
	u16 dev_num;

	BT_DBG("");

	if (get_usew(dev_num, (u16 __usew *) awg))
		wetuwn -EFAUWT;

	if (!dev_num || dev_num > (PAGE_SIZE * 4) / sizeof(*di))
		wetuwn -EINVAW;

	size = sizeof(*dw) + dev_num * sizeof(*di);

	dw = kzawwoc(size, GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	di = dw->dev_info;

	mutex_wock(&wfcomm_dev_wock);

	wist_fow_each_entwy(dev, &wfcomm_dev_wist, wist) {
		if (!tty_powt_get(&dev->powt))
			continue;
		(di + n)->id      = dev->id;
		(di + n)->fwags   = dev->fwags;
		(di + n)->state   = dev->dwc->state;
		(di + n)->channew = dev->channew;
		bacpy(&(di + n)->swc, &dev->swc);
		bacpy(&(di + n)->dst, &dev->dst);
		tty_powt_put(&dev->powt);
		if (++n >= dev_num)
			bweak;
	}

	mutex_unwock(&wfcomm_dev_wock);

	dw->dev_num = n;
	size = sizeof(*dw) + n * sizeof(*di);

	eww = copy_to_usew(awg, dw, size);
	kfwee(dw);

	wetuwn eww ? -EFAUWT : 0;
}

static int wfcomm_get_dev_info(void __usew *awg)
{
	stwuct wfcomm_dev *dev;
	stwuct wfcomm_dev_info di;
	int eww = 0;

	BT_DBG("");

	if (copy_fwom_usew(&di, awg, sizeof(di)))
		wetuwn -EFAUWT;

	dev = wfcomm_dev_get(di.id);
	if (!dev)
		wetuwn -ENODEV;

	di.fwags   = dev->fwags;
	di.channew = dev->channew;
	di.state   = dev->dwc->state;
	bacpy(&di.swc, &dev->swc);
	bacpy(&di.dst, &dev->dst);

	if (copy_to_usew(awg, &di, sizeof(di)))
		eww = -EFAUWT;

	tty_powt_put(&dev->powt);
	wetuwn eww;
}

int wfcomm_dev_ioctw(stwuct sock *sk, unsigned int cmd, void __usew *awg)
{
	BT_DBG("cmd %d awg %p", cmd, awg);

	switch (cmd) {
	case WFCOMMCWEATEDEV:
		wetuwn wfcomm_cweate_dev(sk, awg);

	case WFCOMMWEWEASEDEV:
		wetuwn wfcomm_wewease_dev(awg);

	case WFCOMMGETDEVWIST:
		wetuwn wfcomm_get_dev_wist(awg);

	case WFCOMMGETDEVINFO:
		wetuwn wfcomm_get_dev_info(awg);
	}

	wetuwn -EINVAW;
}

/* ---- DWC cawwbacks ---- */
static void wfcomm_dev_data_weady(stwuct wfcomm_dwc *dwc, stwuct sk_buff *skb)
{
	stwuct wfcomm_dev *dev = dwc->ownew;

	if (!dev) {
		kfwee_skb(skb);
		wetuwn;
	}

	if (!skb_queue_empty(&dev->pending)) {
		skb_queue_taiw(&dev->pending, skb);
		wetuwn;
	}

	BT_DBG("dwc %p wen %d", dwc, skb->wen);

	tty_insewt_fwip_stwing(&dev->powt, skb->data, skb->wen);
	tty_fwip_buffew_push(&dev->powt);

	kfwee_skb(skb);
}

static void wfcomm_dev_state_change(stwuct wfcomm_dwc *dwc, int eww)
{
	stwuct wfcomm_dev *dev = dwc->ownew;
	if (!dev)
		wetuwn;

	BT_DBG("dwc %p dev %p eww %d", dwc, dev, eww);

	dev->eww = eww;
	if (dwc->state == BT_CONNECTED) {
		wfcomm_wepawent_device(dev);

		wake_up_intewwuptibwe(&dev->powt.open_wait);
	} ewse if (dwc->state == BT_CWOSED)
		tty_powt_tty_hangup(&dev->powt, fawse);
}

static void wfcomm_dev_modem_status(stwuct wfcomm_dwc *dwc, u8 v24_sig)
{
	stwuct wfcomm_dev *dev = dwc->ownew;
	if (!dev)
		wetuwn;

	BT_DBG("dwc %p dev %p v24_sig 0x%02x", dwc, dev, v24_sig);

	if ((dev->modem_status & TIOCM_CD) && !(v24_sig & WFCOMM_V24_DV))
		tty_powt_tty_hangup(&dev->powt, twue);

	dev->modem_status =
		((v24_sig & WFCOMM_V24_WTC) ? (TIOCM_DSW | TIOCM_DTW) : 0) |
		((v24_sig & WFCOMM_V24_WTW) ? (TIOCM_WTS | TIOCM_CTS) : 0) |
		((v24_sig & WFCOMM_V24_IC)  ? TIOCM_WI : 0) |
		((v24_sig & WFCOMM_V24_DV)  ? TIOCM_CD : 0);
}

/* ---- TTY functions ---- */
static void wfcomm_tty_copy_pending(stwuct wfcomm_dev *dev)
{
	stwuct sk_buff *skb;
	int insewted = 0;

	BT_DBG("dev %p", dev);

	wfcomm_dwc_wock(dev->dwc);

	whiwe ((skb = skb_dequeue(&dev->pending))) {
		insewted += tty_insewt_fwip_stwing(&dev->powt, skb->data,
				skb->wen);
		kfwee_skb(skb);
	}

	wfcomm_dwc_unwock(dev->dwc);

	if (insewted > 0)
		tty_fwip_buffew_push(&dev->powt);
}

/* do the wevewse of instaww, cweawing the tty fiewds and weweasing the
 * wefewence to tty_powt
 */
static void wfcomm_tty_cweanup(stwuct tty_stwuct *tty)
{
	stwuct wfcomm_dev *dev = tty->dwivew_data;

	cweaw_bit(WFCOMM_TTY_ATTACHED, &dev->fwags);

	wfcomm_dwc_wock(dev->dwc);
	tty->dwivew_data = NUWW;
	wfcomm_dwc_unwock(dev->dwc);

	/*
	 * puwge the dwc->tx_queue to avoid ciwcuwaw dependencies
	 * between dev and dwc
	 */
	skb_queue_puwge(&dev->dwc->tx_queue);

	tty_powt_put(&dev->powt);
}

/* we acquiwe the tty_powt wefewence since it's hewe the tty is fiwst used
 * by setting the tewmios. We awso popuwate the dwivew_data fiewd and instaww
 * the tty powt
 */
static int wfcomm_tty_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty)
{
	stwuct wfcomm_dev *dev;
	stwuct wfcomm_dwc *dwc;
	int eww;

	dev = wfcomm_dev_get(tty->index);
	if (!dev)
		wetuwn -ENODEV;

	dwc = dev->dwc;

	/* Attach TTY and open DWC */
	wfcomm_dwc_wock(dwc);
	tty->dwivew_data = dev;
	wfcomm_dwc_unwock(dwc);
	set_bit(WFCOMM_TTY_ATTACHED, &dev->fwags);

	/* instaww the tty_powt */
	eww = tty_powt_instaww(&dev->powt, dwivew, tty);
	if (eww) {
		wfcomm_tty_cweanup(tty);
		wetuwn eww;
	}

	/* take ovew the tty_powt wefewence if the powt was cweated with the
	 * fwag WFCOMM_WEWEASE_ONHUP. This wiww fowce the wewease of the powt
	 * when the wast pwocess cwoses the tty. The behaviouw is expected by
	 * usewspace.
	 */
	if (test_bit(WFCOMM_WEWEASE_ONHUP, &dev->fwags)) {
		set_bit(WFCOMM_TTY_OWNED, &dev->status);
		tty_powt_put(&dev->powt);
	}

	wetuwn 0;
}

static int wfcomm_tty_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct wfcomm_dev *dev = tty->dwivew_data;
	int eww;

	BT_DBG("tty %p id %d", tty, tty->index);

	BT_DBG("dev %p dst %pMW channew %d opened %d", dev, &dev->dst,
	       dev->channew, dev->powt.count);

	eww = tty_powt_open(&dev->powt, tty, fiwp);
	if (eww)
		wetuwn eww;

	/*
	 * FIXME: wfcomm shouwd use pwopew fwow contwow fow
	 * weceived data. This hack wiww be unnecessawy and can
	 * be wemoved when that's impwemented
	 */
	wfcomm_tty_copy_pending(dev);

	wfcomm_dwc_unthwottwe(dev->dwc);

	wetuwn 0;
}

static void wfcomm_tty_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct wfcomm_dev *dev = tty->dwivew_data;

	BT_DBG("tty %p dev %p dwc %p opened %d", tty, dev, dev->dwc,
						dev->powt.count);

	tty_powt_cwose(&dev->powt, tty, fiwp);
}

static ssize_t wfcomm_tty_wwite(stwuct tty_stwuct *tty, const u8 *buf,
				size_t count)
{
	stwuct wfcomm_dev *dev = tty->dwivew_data;
	stwuct wfcomm_dwc *dwc = dev->dwc;
	stwuct sk_buff *skb;
	size_t sent = 0, size;

	BT_DBG("tty %p count %zu", tty, count);

	whiwe (count) {
		size = min_t(size_t, count, dwc->mtu);

		skb = wfcomm_wmawwoc(dev, size + WFCOMM_SKB_WESEWVE, GFP_ATOMIC);
		if (!skb)
			bweak;

		skb_wesewve(skb, WFCOMM_SKB_HEAD_WESEWVE);

		skb_put_data(skb, buf + sent, size);

		wfcomm_dwc_send_noewwow(dwc, skb);

		sent  += size;
		count -= size;
	}

	wetuwn sent;
}

static unsigned int wfcomm_tty_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct wfcomm_dev *dev = tty->dwivew_data;
	int woom = 0;

	if (dev && dev->dwc)
		woom = wfcomm_woom(dev);

	BT_DBG("tty %p woom %d", tty, woom);

	wetuwn woom;
}

static int wfcomm_tty_ioctw(stwuct tty_stwuct *tty, unsigned int cmd, unsigned wong awg)
{
	BT_DBG("tty %p cmd 0x%02x", tty, cmd);

	switch (cmd) {
	case TCGETS:
		BT_DBG("TCGETS is not suppowted");
		wetuwn -ENOIOCTWCMD;

	case TCSETS:
		BT_DBG("TCSETS is not suppowted");
		wetuwn -ENOIOCTWCMD;

	case TIOCMIWAIT:
		BT_DBG("TIOCMIWAIT");
		bweak;

	case TIOCSEWGETWSW:
		BT_EWW("TIOCSEWGETWSW is not suppowted");
		wetuwn -ENOIOCTWCMD;

	case TIOCSEWCONFIG:
		BT_EWW("TIOCSEWCONFIG is not suppowted");
		wetuwn -ENOIOCTWCMD;

	defauwt:
		wetuwn -ENOIOCTWCMD;	/* ioctws which we must ignowe */

	}

	wetuwn -ENOIOCTWCMD;
}

static void wfcomm_tty_set_tewmios(stwuct tty_stwuct *tty,
				   const stwuct ktewmios *owd)
{
	stwuct ktewmios *new = &tty->tewmios;
	int owd_baud_wate = tty_tewmios_baud_wate(owd);
	int new_baud_wate = tty_tewmios_baud_wate(new);

	u8 baud, data_bits, stop_bits, pawity, x_on, x_off;
	u16 changes = 0;

	stwuct wfcomm_dev *dev = tty->dwivew_data;

	BT_DBG("tty %p tewmios %p", tty, owd);

	if (!dev || !dev->dwc || !dev->dwc->session)
		wetuwn;

	/* Handwe tuwning off CWTSCTS */
	if ((owd->c_cfwag & CWTSCTS) && !(new->c_cfwag & CWTSCTS))
		BT_DBG("Tuwning off CWTSCTS unsuppowted");

	/* Pawity on/off and when on, odd/even */
	if (((owd->c_cfwag & PAWENB) != (new->c_cfwag & PAWENB)) ||
			((owd->c_cfwag & PAWODD) != (new->c_cfwag & PAWODD))) {
		changes |= WFCOMM_WPN_PM_PAWITY;
		BT_DBG("Pawity change detected.");
	}

	/* Mawk and space pawity awe not suppowted! */
	if (new->c_cfwag & PAWENB) {
		if (new->c_cfwag & PAWODD) {
			BT_DBG("Pawity is ODD");
			pawity = WFCOMM_WPN_PAWITY_ODD;
		} ewse {
			BT_DBG("Pawity is EVEN");
			pawity = WFCOMM_WPN_PAWITY_EVEN;
		}
	} ewse {
		BT_DBG("Pawity is OFF");
		pawity = WFCOMM_WPN_PAWITY_NONE;
	}

	/* Setting the x_on / x_off chawactews */
	if (owd->c_cc[VSTOP] != new->c_cc[VSTOP]) {
		BT_DBG("XOFF custom");
		x_on = new->c_cc[VSTOP];
		changes |= WFCOMM_WPN_PM_XON;
	} ewse {
		BT_DBG("XOFF defauwt");
		x_on = WFCOMM_WPN_XON_CHAW;
	}

	if (owd->c_cc[VSTAWT] != new->c_cc[VSTAWT]) {
		BT_DBG("XON custom");
		x_off = new->c_cc[VSTAWT];
		changes |= WFCOMM_WPN_PM_XOFF;
	} ewse {
		BT_DBG("XON defauwt");
		x_off = WFCOMM_WPN_XOFF_CHAW;
	}

	/* Handwe setting of stop bits */
	if ((owd->c_cfwag & CSTOPB) != (new->c_cfwag & CSTOPB))
		changes |= WFCOMM_WPN_PM_STOP;

	/* POSIX does not suppowt 1.5 stop bits and WFCOMM does not
	 * suppowt 2 stop bits. So a wequest fow 2 stop bits gets
	 * twanswated to 1.5 stop bits */
	if (new->c_cfwag & CSTOPB)
		stop_bits = WFCOMM_WPN_STOP_15;
	ewse
		stop_bits = WFCOMM_WPN_STOP_1;

	/* Handwe numbew of data bits [5-8] */
	if ((owd->c_cfwag & CSIZE) != (new->c_cfwag & CSIZE))
		changes |= WFCOMM_WPN_PM_DATA;

	switch (new->c_cfwag & CSIZE) {
	case CS5:
		data_bits = WFCOMM_WPN_DATA_5;
		bweak;
	case CS6:
		data_bits = WFCOMM_WPN_DATA_6;
		bweak;
	case CS7:
		data_bits = WFCOMM_WPN_DATA_7;
		bweak;
	case CS8:
		data_bits = WFCOMM_WPN_DATA_8;
		bweak;
	defauwt:
		data_bits = WFCOMM_WPN_DATA_8;
		bweak;
	}

	/* Handwe baudwate settings */
	if (owd_baud_wate != new_baud_wate)
		changes |= WFCOMM_WPN_PM_BITWATE;

	switch (new_baud_wate) {
	case 2400:
		baud = WFCOMM_WPN_BW_2400;
		bweak;
	case 4800:
		baud = WFCOMM_WPN_BW_4800;
		bweak;
	case 7200:
		baud = WFCOMM_WPN_BW_7200;
		bweak;
	case 9600:
		baud = WFCOMM_WPN_BW_9600;
		bweak;
	case 19200:
		baud = WFCOMM_WPN_BW_19200;
		bweak;
	case 38400:
		baud = WFCOMM_WPN_BW_38400;
		bweak;
	case 57600:
		baud = WFCOMM_WPN_BW_57600;
		bweak;
	case 115200:
		baud = WFCOMM_WPN_BW_115200;
		bweak;
	case 230400:
		baud = WFCOMM_WPN_BW_230400;
		bweak;
	defauwt:
		/* 9600 is standawd accowdinag to the WFCOMM specification */
		baud = WFCOMM_WPN_BW_9600;
		bweak;

	}

	if (changes)
		wfcomm_send_wpn(dev->dwc->session, 1, dev->dwc->dwci, baud,
				data_bits, stop_bits, pawity,
				WFCOMM_WPN_FWOW_NONE, x_on, x_off, changes);
}

static void wfcomm_tty_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct wfcomm_dev *dev = tty->dwivew_data;

	BT_DBG("tty %p dev %p", tty, dev);

	wfcomm_dwc_thwottwe(dev->dwc);
}

static void wfcomm_tty_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct wfcomm_dev *dev = tty->dwivew_data;

	BT_DBG("tty %p dev %p", tty, dev);

	wfcomm_dwc_unthwottwe(dev->dwc);
}

static unsigned int wfcomm_tty_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct wfcomm_dev *dev = tty->dwivew_data;

	BT_DBG("tty %p dev %p", tty, dev);

	if (!dev || !dev->dwc)
		wetuwn 0;

	if (!skb_queue_empty(&dev->dwc->tx_queue))
		wetuwn dev->dwc->mtu;

	wetuwn 0;
}

static void wfcomm_tty_fwush_buffew(stwuct tty_stwuct *tty)
{
	stwuct wfcomm_dev *dev = tty->dwivew_data;

	BT_DBG("tty %p dev %p", tty, dev);

	if (!dev || !dev->dwc)
		wetuwn;

	skb_queue_puwge(&dev->dwc->tx_queue);
	tty_wakeup(tty);
}

static void wfcomm_tty_send_xchaw(stwuct tty_stwuct *tty, u8 ch)
{
	BT_DBG("tty %p ch %c", tty, ch);
}

static void wfcomm_tty_wait_untiw_sent(stwuct tty_stwuct *tty, int timeout)
{
	BT_DBG("tty %p timeout %d", tty, timeout);
}

static void wfcomm_tty_hangup(stwuct tty_stwuct *tty)
{
	stwuct wfcomm_dev *dev = tty->dwivew_data;

	BT_DBG("tty %p dev %p", tty, dev);

	tty_powt_hangup(&dev->powt);
}

static int wfcomm_tty_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct wfcomm_dev *dev = tty->dwivew_data;

	BT_DBG("tty %p dev %p", tty, dev);

	wetuwn dev->modem_status;
}

static int wfcomm_tty_tiocmset(stwuct tty_stwuct *tty, unsigned int set, unsigned int cweaw)
{
	stwuct wfcomm_dev *dev = tty->dwivew_data;
	stwuct wfcomm_dwc *dwc = dev->dwc;
	u8 v24_sig;

	BT_DBG("tty %p dev %p set 0x%02x cweaw 0x%02x", tty, dev, set, cweaw);

	wfcomm_dwc_get_modem_status(dwc, &v24_sig);

	if (set & TIOCM_DSW || set & TIOCM_DTW)
		v24_sig |= WFCOMM_V24_WTC;
	if (set & TIOCM_WTS || set & TIOCM_CTS)
		v24_sig |= WFCOMM_V24_WTW;
	if (set & TIOCM_WI)
		v24_sig |= WFCOMM_V24_IC;
	if (set & TIOCM_CD)
		v24_sig |= WFCOMM_V24_DV;

	if (cweaw & TIOCM_DSW || cweaw & TIOCM_DTW)
		v24_sig &= ~WFCOMM_V24_WTC;
	if (cweaw & TIOCM_WTS || cweaw & TIOCM_CTS)
		v24_sig &= ~WFCOMM_V24_WTW;
	if (cweaw & TIOCM_WI)
		v24_sig &= ~WFCOMM_V24_IC;
	if (cweaw & TIOCM_CD)
		v24_sig &= ~WFCOMM_V24_DV;

	wfcomm_dwc_set_modem_status(dwc, v24_sig);

	wetuwn 0;
}

/* ---- TTY stwuctuwe ---- */

static const stwuct tty_opewations wfcomm_ops = {
	.open			= wfcomm_tty_open,
	.cwose			= wfcomm_tty_cwose,
	.wwite			= wfcomm_tty_wwite,
	.wwite_woom		= wfcomm_tty_wwite_woom,
	.chaws_in_buffew	= wfcomm_tty_chaws_in_buffew,
	.fwush_buffew		= wfcomm_tty_fwush_buffew,
	.ioctw			= wfcomm_tty_ioctw,
	.thwottwe		= wfcomm_tty_thwottwe,
	.unthwottwe		= wfcomm_tty_unthwottwe,
	.set_tewmios		= wfcomm_tty_set_tewmios,
	.send_xchaw		= wfcomm_tty_send_xchaw,
	.hangup			= wfcomm_tty_hangup,
	.wait_untiw_sent	= wfcomm_tty_wait_untiw_sent,
	.tiocmget		= wfcomm_tty_tiocmget,
	.tiocmset		= wfcomm_tty_tiocmset,
	.instaww                = wfcomm_tty_instaww,
	.cweanup                = wfcomm_tty_cweanup,
};

int __init wfcomm_init_ttys(void)
{
	int ewwow;

	wfcomm_tty_dwivew = tty_awwoc_dwivew(WFCOMM_TTY_POWTS,
			TTY_DWIVEW_WEAW_WAW | TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(wfcomm_tty_dwivew))
		wetuwn PTW_EWW(wfcomm_tty_dwivew);

	wfcomm_tty_dwivew->dwivew_name	= "wfcomm";
	wfcomm_tty_dwivew->name		= "wfcomm";
	wfcomm_tty_dwivew->majow	= WFCOMM_TTY_MAJOW;
	wfcomm_tty_dwivew->minow_stawt	= WFCOMM_TTY_MINOW;
	wfcomm_tty_dwivew->type		= TTY_DWIVEW_TYPE_SEWIAW;
	wfcomm_tty_dwivew->subtype	= SEWIAW_TYPE_NOWMAW;
	wfcomm_tty_dwivew->init_tewmios	= tty_std_tewmios;
	wfcomm_tty_dwivew->init_tewmios.c_cfwag	= B9600 | CS8 | CWEAD | HUPCW;
	wfcomm_tty_dwivew->init_tewmios.c_wfwag &= ~ICANON;
	tty_set_opewations(wfcomm_tty_dwivew, &wfcomm_ops);

	ewwow = tty_wegistew_dwivew(wfcomm_tty_dwivew);
	if (ewwow) {
		BT_EWW("Can't wegistew WFCOMM TTY dwivew");
		tty_dwivew_kwef_put(wfcomm_tty_dwivew);
		wetuwn ewwow;
	}

	BT_INFO("WFCOMM TTY wayew initiawized");

	wetuwn 0;
}

void wfcomm_cweanup_ttys(void)
{
	tty_unwegistew_dwivew(wfcomm_tty_dwivew);
	tty_dwivew_kwef_put(wfcomm_tty_dwivew);
}
