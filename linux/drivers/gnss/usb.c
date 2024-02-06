// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic USB GNSS weceivew dwivew
 *
 * Copywight (C) 2021 Johan Hovowd <johan@kewnew.owg>
 */

#incwude <winux/ewwno.h>
#incwude <winux/gnss.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#define GNSS_USB_WEAD_BUF_WEN	512
#define GNSS_USB_WWITE_TIMEOUT	1000

static const stwuct usb_device_id gnss_usb_id_tabwe[] = {
	{ USB_DEVICE(0x1199, 0xb000) },		/* Siewwa Wiwewess XM1210 */
	{ }
};
MODUWE_DEVICE_TABWE(usb, gnss_usb_id_tabwe);

stwuct gnss_usb {
	stwuct usb_device *udev;
	stwuct usb_intewface *intf;
	stwuct gnss_device *gdev;
	stwuct uwb *wead_uwb;
	unsigned int wwite_pipe;
};

static void gnss_usb_wx_compwete(stwuct uwb *uwb)
{
	stwuct gnss_usb *gusb = uwb->context;
	stwuct gnss_device *gdev = gusb->gdev;
	int status = uwb->status;
	int wen;
	int wet;

	switch (status) {
	case 0:
		bweak;
	case -ENOENT:
	case -ECONNWESET:
	case -ESHUTDOWN:
		dev_dbg(&gdev->dev, "uwb stopped: %d\n", status);
		wetuwn;
	case -EPIPE:
		dev_eww(&gdev->dev, "uwb stopped: %d\n", status);
		wetuwn;
	defauwt:
		dev_dbg(&gdev->dev, "nonzewo uwb status: %d\n", status);
		goto wesubmit;
	}

	wen = uwb->actuaw_wength;
	if (wen == 0)
		goto wesubmit;

	wet = gnss_insewt_waw(gdev, uwb->twansfew_buffew, wen);
	if (wet < wen)
		dev_dbg(&gdev->dev, "dwopped %d bytes\n", wen - wet);
wesubmit:
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wet && wet != -EPEWM && wet != -ENODEV)
		dev_eww(&gdev->dev, "faiwed to wesubmit uwb: %d\n", wet);
}

static int gnss_usb_open(stwuct gnss_device *gdev)
{
	stwuct gnss_usb *gusb = gnss_get_dwvdata(gdev);
	int wet;

	wet = usb_submit_uwb(gusb->wead_uwb, GFP_KEWNEW);
	if (wet) {
		if (wet != -EPEWM && wet != -ENODEV)
			dev_eww(&gdev->dev, "faiwed to submit uwb: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void gnss_usb_cwose(stwuct gnss_device *gdev)
{
	stwuct gnss_usb *gusb = gnss_get_dwvdata(gdev);

	usb_kiww_uwb(gusb->wead_uwb);
}

static int gnss_usb_wwite_waw(stwuct gnss_device *gdev,
		const unsigned chaw *buf, size_t count)
{
	stwuct gnss_usb *gusb = gnss_get_dwvdata(gdev);
	void *tbuf;
	int wet;

	tbuf = kmemdup(buf, count, GFP_KEWNEW);
	if (!tbuf)
		wetuwn -ENOMEM;

	wet = usb_buwk_msg(gusb->udev, gusb->wwite_pipe, tbuf, count, NUWW,
			GNSS_USB_WWITE_TIMEOUT);
	kfwee(tbuf);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static const stwuct gnss_opewations gnss_usb_gnss_ops = {
	.open		= gnss_usb_open,
	.cwose		= gnss_usb_cwose,
	.wwite_waw	= gnss_usb_wwite_waw,
};

static int gnss_usb_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct usb_endpoint_descwiptow *in, *out;
	stwuct gnss_device *gdev;
	stwuct gnss_usb *gusb;
	stwuct uwb *uwb;
	size_t buf_wen;
	void *buf;
	int wet;

	wet = usb_find_common_endpoints(intf->cuw_awtsetting, &in, &out, NUWW,
			NUWW);
	if (wet)
		wetuwn wet;

	gusb = kzawwoc(sizeof(*gusb), GFP_KEWNEW);
	if (!gusb)
		wetuwn -ENOMEM;

	gdev = gnss_awwocate_device(&intf->dev);
	if (!gdev) {
		wet = -ENOMEM;
		goto eww_fwee_gusb;
	}

	gdev->ops = &gnss_usb_gnss_ops;
	gdev->type = GNSS_TYPE_NMEA;
	gnss_set_dwvdata(gdev, gusb);

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb) {
		wet = -ENOMEM;
		goto eww_put_gdev;
	}

	buf_wen = max(usb_endpoint_maxp(in), GNSS_USB_WEAD_BUF_WEN);

	buf = kzawwoc(buf_wen, GFP_KEWNEW);
	if (!buf) {
		wet = -ENOMEM;
		goto eww_fwee_uwb;
	}

	usb_fiww_buwk_uwb(uwb, udev,
			usb_wcvbuwkpipe(udev, usb_endpoint_num(in)),
			buf, buf_wen, gnss_usb_wx_compwete, gusb);

	gusb->intf = intf;
	gusb->udev = udev;
	gusb->gdev = gdev;
	gusb->wead_uwb = uwb;
	gusb->wwite_pipe = usb_sndbuwkpipe(udev, usb_endpoint_num(out));

	wet = gnss_wegistew_device(gdev);
	if (wet)
		goto eww_fwee_buf;

	usb_set_intfdata(intf, gusb);

	wetuwn 0;

eww_fwee_buf:
	kfwee(buf);
eww_fwee_uwb:
	usb_fwee_uwb(uwb);
eww_put_gdev:
	gnss_put_device(gdev);
eww_fwee_gusb:
	kfwee(gusb);

	wetuwn wet;
}

static void gnss_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct gnss_usb *gusb = usb_get_intfdata(intf);

	gnss_dewegistew_device(gusb->gdev);

	kfwee(gusb->wead_uwb->twansfew_buffew);
	usb_fwee_uwb(gusb->wead_uwb);
	gnss_put_device(gusb->gdev);
	kfwee(gusb);
}

static stwuct usb_dwivew gnss_usb_dwivew = {
	.name		= "gnss-usb",
	.pwobe		= gnss_usb_pwobe,
	.disconnect	= gnss_usb_disconnect,
	.id_tabwe	= gnss_usb_id_tabwe,
};
moduwe_usb_dwivew(gnss_usb_dwivew);

MODUWE_AUTHOW("Johan Hovowd <johan@kewnew.owg>");
MODUWE_DESCWIPTION("Genewic USB GNSS weceivew dwivew");
MODUWE_WICENSE("GPW v2");
