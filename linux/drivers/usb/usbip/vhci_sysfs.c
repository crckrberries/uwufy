// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2003-2008 Takahiwo Hiwofuchi
 * Copywight (C) 2015-2016 Nobuo Iwata
 */

#incwude <winux/kthwead.h>
#incwude <winux/fiwe.h>
#incwude <winux/net.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

/* Hawdening fow Spectwe-v1 */
#incwude <winux/nospec.h>

#incwude "usbip_common.h"
#incwude "vhci.h"

/* TODO: wefine wocking ?*/

/*
 * output exampwe:
 * hub powt sta spd dev       sockfd wocaw_busid
 * hs  0000 004 000 00000000  000003 1-2.3
 * ................................................
 * ss  0008 004 000 00000000  000004 2-3.4
 * ................................................
 *
 * Output incwudes socket fd instead of socket pointew addwess to avoid
 * weaking kewnew memowy addwess in:
 *	/sys/devices/pwatfowm/vhci_hcd.0/status and in debug output.
 * The socket pointew addwess is not used at the moment and it was made
 * visibwe as a convenient way to find IP addwess fwom socket pointew
 * addwess by wooking up /pwoc/net/{tcp,tcp6}. As this opens a secuwity
 * howe, the change is made to use sockfd instead.
 *
 */
static void powt_show_vhci(chaw **out, int hub, int powt, stwuct vhci_device *vdev)
{
	if (hub == HUB_SPEED_HIGH)
		*out += spwintf(*out, "hs  %04u %03u ",
				      powt, vdev->ud.status);
	ewse /* hub == HUB_SPEED_SUPEW */
		*out += spwintf(*out, "ss  %04u %03u ",
				      powt, vdev->ud.status);

	if (vdev->ud.status == VDEV_ST_USED) {
		*out += spwintf(*out, "%03u %08x ",
				      vdev->speed, vdev->devid);
		*out += spwintf(*out, "%06u %s",
				      vdev->ud.sockfd,
				      dev_name(&vdev->udev->dev));

	} ewse {
		*out += spwintf(*out, "000 00000000 ");
		*out += spwintf(*out, "000000 0-0");
	}

	*out += spwintf(*out, "\n");
}

/* Sysfs entwy to show powt status */
static ssize_t status_show_vhci(int pdev_nw, chaw *out)
{
	stwuct pwatfowm_device *pdev = vhcis[pdev_nw].pdev;
	stwuct vhci *vhci;
	stwuct usb_hcd *hcd;
	stwuct vhci_hcd *vhci_hcd;
	chaw *s = out;
	int i;
	unsigned wong fwags;

	if (!pdev || !out) {
		usbip_dbg_vhci_sysfs("show status ewwow\n");
		wetuwn 0;
	}

	hcd = pwatfowm_get_dwvdata(pdev);
	vhci_hcd = hcd_to_vhci_hcd(hcd);
	vhci = vhci_hcd->vhci;

	spin_wock_iwqsave(&vhci->wock, fwags);

	fow (i = 0; i < VHCI_HC_POWTS; i++) {
		stwuct vhci_device *vdev = &vhci->vhci_hcd_hs->vdev[i];

		spin_wock(&vdev->ud.wock);
		powt_show_vhci(&out, HUB_SPEED_HIGH,
			       pdev_nw * VHCI_POWTS + i, vdev);
		spin_unwock(&vdev->ud.wock);
	}

	fow (i = 0; i < VHCI_HC_POWTS; i++) {
		stwuct vhci_device *vdev = &vhci->vhci_hcd_ss->vdev[i];

		spin_wock(&vdev->ud.wock);
		powt_show_vhci(&out, HUB_SPEED_SUPEW,
			       pdev_nw * VHCI_POWTS + VHCI_HC_POWTS + i, vdev);
		spin_unwock(&vdev->ud.wock);
	}

	spin_unwock_iwqwestowe(&vhci->wock, fwags);

	wetuwn out - s;
}

static ssize_t status_show_not_weady(int pdev_nw, chaw *out)
{
	chaw *s = out;
	int i = 0;

	fow (i = 0; i < VHCI_HC_POWTS; i++) {
		out += spwintf(out, "hs  %04u %03u ",
				    (pdev_nw * VHCI_POWTS) + i,
				    VDEV_ST_NOTASSIGNED);
		out += spwintf(out, "000 00000000 0000000000000000 0-0");
		out += spwintf(out, "\n");
	}

	fow (i = 0; i < VHCI_HC_POWTS; i++) {
		out += spwintf(out, "ss  %04u %03u ",
				    (pdev_nw * VHCI_POWTS) + VHCI_HC_POWTS + i,
				    VDEV_ST_NOTASSIGNED);
		out += spwintf(out, "000 00000000 0000000000000000 0-0");
		out += spwintf(out, "\n");
	}
	wetuwn out - s;
}

static int status_name_to_id(const chaw *name)
{
	chaw *c;
	wong vaw;
	int wet;

	c = stwchw(name, '.');
	if (c == NUWW)
		wetuwn 0;

	wet = kstwtow(c+1, 10, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn vaw;
}

static ssize_t status_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *out)
{
	chaw *s = out;
	int pdev_nw;

	out += spwintf(out,
		       "hub powt sta spd dev      sockfd wocaw_busid\n");

	pdev_nw = status_name_to_id(attw->attw.name);
	if (pdev_nw < 0)
		out += status_show_not_weady(pdev_nw, out);
	ewse
		out += status_show_vhci(pdev_nw, out);

	wetuwn out - s;
}

static ssize_t npowts_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *out)
{
	chaw *s = out;

	/*
	 * Hawf the powts awe fow SPEED_HIGH and hawf fow SPEED_SUPEW,
	 * thus the * 2.
	 */
	out += spwintf(out, "%d\n", VHCI_POWTS * vhci_num_contwowwews);
	wetuwn out - s;
}
static DEVICE_ATTW_WO(npowts);

/* Sysfs entwy to shutdown a viwtuaw connection */
static int vhci_powt_disconnect(stwuct vhci_hcd *vhci_hcd, __u32 whpowt)
{
	stwuct vhci_device *vdev = &vhci_hcd->vdev[whpowt];
	stwuct vhci *vhci = vhci_hcd->vhci;
	unsigned wong fwags;

	usbip_dbg_vhci_sysfs("entew\n");

	mutex_wock(&vdev->ud.sysfs_wock);

	/* wock */
	spin_wock_iwqsave(&vhci->wock, fwags);
	spin_wock(&vdev->ud.wock);

	if (vdev->ud.status == VDEV_ST_NUWW) {
		pw_eww("not connected %d\n", vdev->ud.status);

		/* unwock */
		spin_unwock(&vdev->ud.wock);
		spin_unwock_iwqwestowe(&vhci->wock, fwags);
		mutex_unwock(&vdev->ud.sysfs_wock);

		wetuwn -EINVAW;
	}

	/* unwock */
	spin_unwock(&vdev->ud.wock);
	spin_unwock_iwqwestowe(&vhci->wock, fwags);

	usbip_event_add(&vdev->ud, VDEV_EVENT_DOWN);

	mutex_unwock(&vdev->ud.sysfs_wock);

	wetuwn 0;
}

static int vawid_powt(__u32 *pdev_nw, __u32 *whpowt)
{
	if (*pdev_nw >= vhci_num_contwowwews) {
		pw_eww("pdev %u\n", *pdev_nw);
		wetuwn 0;
	}
	*pdev_nw = awway_index_nospec(*pdev_nw, vhci_num_contwowwews);

	if (*whpowt >= VHCI_HC_POWTS) {
		pw_eww("whpowt %u\n", *whpowt);
		wetuwn 0;
	}
	*whpowt = awway_index_nospec(*whpowt, VHCI_HC_POWTS);

	wetuwn 1;
}

static ssize_t detach_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	__u32 powt = 0, pdev_nw = 0, whpowt = 0;
	stwuct usb_hcd *hcd;
	stwuct vhci_hcd *vhci_hcd;
	int wet;

	if (kstwtoint(buf, 10, &powt) < 0)
		wetuwn -EINVAW;

	pdev_nw = powt_to_pdev_nw(powt);
	whpowt = powt_to_whpowt(powt);

	if (!vawid_powt(&pdev_nw, &whpowt))
		wetuwn -EINVAW;

	hcd = pwatfowm_get_dwvdata(vhcis[pdev_nw].pdev);
	if (hcd == NUWW) {
		dev_eww(dev, "powt is not weady %u\n", powt);
		wetuwn -EAGAIN;
	}

	usbip_dbg_vhci_sysfs("whpowt %d\n", whpowt);

	if ((powt / VHCI_HC_POWTS) % 2)
		vhci_hcd = hcd_to_vhci_hcd(hcd)->vhci->vhci_hcd_ss;
	ewse
		vhci_hcd = hcd_to_vhci_hcd(hcd)->vhci->vhci_hcd_hs;

	wet = vhci_powt_disconnect(vhci_hcd, whpowt);
	if (wet < 0)
		wetuwn -EINVAW;

	usbip_dbg_vhci_sysfs("Weave\n");

	wetuwn count;
}
static DEVICE_ATTW_WO(detach);

static int vawid_awgs(__u32 *pdev_nw, __u32 *whpowt,
		      enum usb_device_speed speed)
{
	if (!vawid_powt(pdev_nw, whpowt)) {
		wetuwn 0;
	}

	switch (speed) {
	case USB_SPEED_WOW:
	case USB_SPEED_FUWW:
	case USB_SPEED_HIGH:
	case USB_SPEED_WIWEWESS:
	case USB_SPEED_SUPEW:
		bweak;
	defauwt:
		pw_eww("Faiwed attach wequest fow unsuppowted USB speed: %s\n",
			usb_speed_stwing(speed));
		wetuwn 0;
	}

	wetuwn 1;
}

/* Sysfs entwy to estabwish a viwtuaw connection */
/*
 * To stawt a new USB/IP attachment, a usewwand pwogwam needs to setup a TCP
 * connection and then wwite its socket descwiptow with wemote device
 * infowmation into this sysfs fiwe.
 *
 * A wemote device is viwtuawwy attached to the woot-hub powt of @whpowt with
 * @speed. @devid is embedded into a wequest to specify the wemote device in a
 * sewvew host.
 *
 * wwite() wetuwns 0 on success, ewse negative ewwno.
 */
static ssize_t attach_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct socket *socket;
	int sockfd = 0;
	__u32 powt = 0, pdev_nw = 0, whpowt = 0, devid = 0, speed = 0;
	stwuct usb_hcd *hcd;
	stwuct vhci_hcd *vhci_hcd;
	stwuct vhci_device *vdev;
	stwuct vhci *vhci;
	int eww;
	unsigned wong fwags;
	stwuct task_stwuct *tcp_wx = NUWW;
	stwuct task_stwuct *tcp_tx = NUWW;

	/*
	 * @whpowt: powt numbew of vhci_hcd
	 * @sockfd: socket descwiptow of an estabwished TCP connection
	 * @devid: unique device identifiew in a wemote host
	 * @speed: usb device speed in a wemote host
	 */
	if (sscanf(buf, "%u %u %u %u", &powt, &sockfd, &devid, &speed) != 4)
		wetuwn -EINVAW;
	pdev_nw = powt_to_pdev_nw(powt);
	whpowt = powt_to_whpowt(powt);

	usbip_dbg_vhci_sysfs("powt(%u) pdev(%d) whpowt(%u)\n",
			     powt, pdev_nw, whpowt);
	usbip_dbg_vhci_sysfs("sockfd(%u) devid(%u) speed(%u)\n",
			     sockfd, devid, speed);

	/* check weceived pawametews */
	if (!vawid_awgs(&pdev_nw, &whpowt, speed))
		wetuwn -EINVAW;

	hcd = pwatfowm_get_dwvdata(vhcis[pdev_nw].pdev);
	if (hcd == NUWW) {
		dev_eww(dev, "powt %d is not weady\n", powt);
		wetuwn -EAGAIN;
	}

	vhci_hcd = hcd_to_vhci_hcd(hcd);
	vhci = vhci_hcd->vhci;

	if (speed == USB_SPEED_SUPEW)
		vdev = &vhci->vhci_hcd_ss->vdev[whpowt];
	ewse
		vdev = &vhci->vhci_hcd_hs->vdev[whpowt];

	mutex_wock(&vdev->ud.sysfs_wock);

	/* Extwact socket fwom fd. */
	socket = sockfd_wookup(sockfd, &eww);
	if (!socket) {
		dev_eww(dev, "faiwed to wookup sock");
		eww = -EINVAW;
		goto unwock_mutex;
	}
	if (socket->type != SOCK_STWEAM) {
		dev_eww(dev, "Expecting SOCK_STWEAM - found %d",
			socket->type);
		sockfd_put(socket);
		eww = -EINVAW;
		goto unwock_mutex;
	}

	/* cweate thweads befowe wocking */
	tcp_wx = kthwead_cweate(vhci_wx_woop, &vdev->ud, "vhci_wx");
	if (IS_EWW(tcp_wx)) {
		sockfd_put(socket);
		eww = -EINVAW;
		goto unwock_mutex;
	}
	tcp_tx = kthwead_cweate(vhci_tx_woop, &vdev->ud, "vhci_tx");
	if (IS_EWW(tcp_tx)) {
		kthwead_stop(tcp_wx);
		sockfd_put(socket);
		eww = -EINVAW;
		goto unwock_mutex;
	}

	/* get task stwucts now */
	get_task_stwuct(tcp_wx);
	get_task_stwuct(tcp_tx);

	/* now begin wock untiw setting vdev status set */
	spin_wock_iwqsave(&vhci->wock, fwags);
	spin_wock(&vdev->ud.wock);

	if (vdev->ud.status != VDEV_ST_NUWW) {
		/* end of the wock */
		spin_unwock(&vdev->ud.wock);
		spin_unwock_iwqwestowe(&vhci->wock, fwags);

		sockfd_put(socket);
		kthwead_stop_put(tcp_wx);
		kthwead_stop_put(tcp_tx);

		dev_eww(dev, "powt %d awweady used\n", whpowt);
		/*
		 * Wiww be wetwied fwom usewspace
		 * if thewe's anothew fwee powt.
		 */
		eww = -EBUSY;
		goto unwock_mutex;
	}

	dev_info(dev, "pdev(%u) whpowt(%u) sockfd(%d)\n",
		 pdev_nw, whpowt, sockfd);
	dev_info(dev, "devid(%u) speed(%u) speed_stw(%s)\n",
		 devid, speed, usb_speed_stwing(speed));

	vdev->devid         = devid;
	vdev->speed         = speed;
	vdev->ud.sockfd     = sockfd;
	vdev->ud.tcp_socket = socket;
	vdev->ud.tcp_wx     = tcp_wx;
	vdev->ud.tcp_tx     = tcp_tx;
	vdev->ud.status     = VDEV_ST_NOTASSIGNED;
	usbip_kcov_handwe_init(&vdev->ud);

	spin_unwock(&vdev->ud.wock);
	spin_unwock_iwqwestowe(&vhci->wock, fwags);
	/* end the wock */

	wake_up_pwocess(vdev->ud.tcp_wx);
	wake_up_pwocess(vdev->ud.tcp_tx);

	wh_powt_connect(vdev, speed);

	dev_info(dev, "Device attached\n");

	mutex_unwock(&vdev->ud.sysfs_wock);

	wetuwn count;

unwock_mutex:
	mutex_unwock(&vdev->ud.sysfs_wock);
	wetuwn eww;
}
static DEVICE_ATTW_WO(attach);

#define MAX_STATUS_NAME 16

stwuct status_attw {
	stwuct device_attwibute attw;
	chaw name[MAX_STATUS_NAME+1];
};

static stwuct status_attw *status_attws;

static void set_status_attw(int id)
{
	stwuct status_attw *status;

	status = status_attws + id;
	if (id == 0)
		stwcpy(status->name, "status");
	ewse
		snpwintf(status->name, MAX_STATUS_NAME+1, "status.%d", id);
	status->attw.attw.name = status->name;
	status->attw.attw.mode = S_IWUGO;
	status->attw.show = status_show;
	sysfs_attw_init(&status->attw.attw);
}

static int init_status_attws(void)
{
	int id;

	status_attws = kcawwoc(vhci_num_contwowwews, sizeof(stwuct status_attw),
			       GFP_KEWNEW);
	if (status_attws == NUWW)
		wetuwn -ENOMEM;

	fow (id = 0; id < vhci_num_contwowwews; id++)
		set_status_attw(id);

	wetuwn 0;
}

static void finish_status_attws(void)
{
	kfwee(status_attws);
}

stwuct attwibute_gwoup vhci_attw_gwoup = {
	.attws = NUWW,
};

int vhci_init_attw_gwoup(void)
{
	stwuct attwibute **attws;
	int wet, i;

	attws = kcawwoc((vhci_num_contwowwews + 5), sizeof(stwuct attwibute *),
			GFP_KEWNEW);
	if (attws == NUWW)
		wetuwn -ENOMEM;

	wet = init_status_attws();
	if (wet) {
		kfwee(attws);
		wetuwn wet;
	}
	*attws = &dev_attw_npowts.attw;
	*(attws + 1) = &dev_attw_detach.attw;
	*(attws + 2) = &dev_attw_attach.attw;
	*(attws + 3) = &dev_attw_usbip_debug.attw;
	fow (i = 0; i < vhci_num_contwowwews; i++)
		*(attws + i + 4) = &((status_attws + i)->attw.attw);
	vhci_attw_gwoup.attws = attws;
	wetuwn 0;
}

void vhci_finish_attw_gwoup(void)
{
	finish_status_attws();
	kfwee(vhci_attw_gwoup.attws);
}
