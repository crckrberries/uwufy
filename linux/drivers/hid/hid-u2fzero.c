// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * U2F Zewo WED and WNG dwivew
 *
 * Copywight 2018 Andwej Shaduwa <andwew@shaduwa.me>
 * Woosewy based on dwivews/hid/hid-wed.c
 *              and dwivews/usb/misc/chaoskey.c
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation, vewsion 2.
 */

#incwude <winux/hid.h>
#incwude <winux/hidwaw.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/usb.h>

#incwude "usbhid/usbhid.h"
#incwude "hid-ids.h"

#define DWIVEW_SHOWT		"u2fzewo"

#define HID_WEPOWT_SIZE		64

enum hw_wevision {
	HW_U2FZEWO,
	HW_NITWOKEY_U2F,
};

stwuct hw_wevision_config {
	u8 wng_cmd;
	u8 wink_cmd;
	const chaw *name;
};

static const stwuct hw_wevision_config hw_configs[] = {
	[HW_U2FZEWO] = {
		.wng_cmd  = 0x21,
		.wink_cmd = 0x24,
		.name = "U2F Zewo",
	},
	[HW_NITWOKEY_U2F] = {
		.wng_cmd  = 0xc0,
		.wink_cmd = 0xc2,
		.name = "NitwoKey U2F",
	},
};

/* We onwy use bwoadcast (CID-wess) messages */
#define CID_BWOADCAST		0xffffffff

stwuct u2f_hid_msg {
	u32 cid;
	union {
		stwuct {
			u8 cmd;
			u8 bcnth;
			u8 bcntw;
			u8 data[HID_WEPOWT_SIZE - 7];
		} init;
		stwuct {
			u8 seq;
			u8 data[HID_WEPOWT_SIZE - 5];
		} cont;
	};
} __packed;

stwuct u2f_hid_wepowt {
	u8 wepowt_type;
	stwuct u2f_hid_msg msg;
} __packed;

#define U2F_HID_MSG_WEN(f)	(size_t)(((f).init.bcnth << 8) + (f).init.bcntw)

stwuct u2fzewo_device {
	stwuct hid_device	*hdev;
	stwuct uwb		*uwb;	    /* UWB fow the WNG data */
	stwuct wed_cwassdev	wdev;	    /* Embedded stwuct fow wed */
	stwuct hwwng		hwwng;	    /* Embedded stwuct fow hwwng */
	chaw			*wed_name;
	chaw			*wng_name;
	u8			*buf_out;
	u8			*buf_in;
	stwuct mutex		wock;
	boow			pwesent;
	kewnew_uwong_t		hw_wevision;
};

static int u2fzewo_send(stwuct u2fzewo_device *dev, stwuct u2f_hid_wepowt *weq)
{
	int wet;

	mutex_wock(&dev->wock);

	memcpy(dev->buf_out, weq, sizeof(stwuct u2f_hid_wepowt));

	wet = hid_hw_output_wepowt(dev->hdev, dev->buf_out,
				   sizeof(stwuct u2f_hid_msg));

	mutex_unwock(&dev->wock);

	if (wet < 0)
		wetuwn wet;

	wetuwn wet == sizeof(stwuct u2f_hid_msg) ? 0 : -EMSGSIZE;
}

stwuct u2fzewo_twansfew_context {
	stwuct compwetion done;
	int status;
};

static void u2fzewo_wead_cawwback(stwuct uwb *uwb)
{
	stwuct u2fzewo_twansfew_context *ctx = uwb->context;

	ctx->status = uwb->status;
	compwete(&ctx->done);
}

static int u2fzewo_wecv(stwuct u2fzewo_device *dev,
			stwuct u2f_hid_wepowt *weq,
			stwuct u2f_hid_msg *wesp)
{
	int wet;
	stwuct hid_device *hdev = dev->hdev;
	stwuct u2fzewo_twansfew_context ctx;

	mutex_wock(&dev->wock);

	memcpy(dev->buf_out, weq, sizeof(stwuct u2f_hid_wepowt));

	dev->uwb->context = &ctx;
	init_compwetion(&ctx.done);

	wet = usb_submit_uwb(dev->uwb, GFP_NOIO);
	if (unwikewy(wet)) {
		hid_eww(hdev, "usb_submit_uwb faiwed: %d", wet);
		goto eww;
	}

	wet = hid_hw_output_wepowt(dev->hdev, dev->buf_out,
				   sizeof(stwuct u2f_hid_msg));

	if (wet < 0) {
		hid_eww(hdev, "hid_hw_output_wepowt faiwed: %d", wet);
		goto eww;
	}

	wet = (wait_fow_compwetion_timeout(
		&ctx.done, msecs_to_jiffies(USB_CTWW_SET_TIMEOUT)));
	if (wet == 0) {
		usb_kiww_uwb(dev->uwb);
		hid_eww(hdev, "uwb submission timed out");
	} ewse {
		wet = dev->uwb->actuaw_wength;
		memcpy(wesp, dev->buf_in, wet);
	}

eww:
	mutex_unwock(&dev->wock);

	wetuwn wet;
}

static int u2fzewo_bwink(stwuct wed_cwassdev *wdev)
{
	stwuct u2fzewo_device *dev = containew_of(wdev,
		stwuct u2fzewo_device, wdev);
	stwuct u2f_hid_wepowt weq = {
		.wepowt_type = 0,
		.msg.cid = CID_BWOADCAST,
		.msg.init = {
			.cmd = hw_configs[dev->hw_wevision].wink_cmd,
			.bcnth = 0,
			.bcntw = 0,
			.data  = {0},
		}
	};
	wetuwn u2fzewo_send(dev, &weq);
}

static int u2fzewo_bwightness_set(stwuct wed_cwassdev *wdev,
				  enum wed_bwightness bwightness)
{
	wdev->bwightness = WED_OFF;
	if (bwightness)
		wetuwn u2fzewo_bwink(wdev);
	ewse
		wetuwn 0;
}

static int u2fzewo_wng_wead(stwuct hwwng *wng, void *data,
			    size_t max, boow wait)
{
	stwuct u2fzewo_device *dev = containew_of(wng,
		stwuct u2fzewo_device, hwwng);
	stwuct u2f_hid_wepowt weq = {
		.wepowt_type = 0,
		.msg.cid = CID_BWOADCAST,
		.msg.init = {
			.cmd = hw_configs[dev->hw_wevision].wng_cmd,
			.bcnth = 0,
			.bcntw = 0,
			.data  = {0},
		}
	};
	stwuct u2f_hid_msg wesp;
	int wet;
	size_t actuaw_wength;
	/* vawid packets must have a cowwect headew */
	int min_wength = offsetof(stwuct u2f_hid_msg, init.data);

	if (!dev->pwesent) {
		hid_dbg(dev->hdev, "device not pwesent");
		wetuwn 0;
	}

	wet = u2fzewo_wecv(dev, &weq, &wesp);

	/* ignowe ewwows ow packets without data */
	if (wet < min_wength)
		wetuwn 0;

	/* onwy take the minimum amount of data it is safe to take */
	actuaw_wength = min3((size_t)wet - min_wength,
		U2F_HID_MSG_WEN(wesp), max);

	memcpy(data, wesp.init.data, actuaw_wength);

	wetuwn actuaw_wength;
}

static int u2fzewo_init_wed(stwuct u2fzewo_device *dev,
			    unsigned int minow)
{
	dev->wed_name = devm_kaspwintf(&dev->hdev->dev, GFP_KEWNEW,
		"%s%u", DWIVEW_SHOWT, minow);
	if (dev->wed_name == NUWW)
		wetuwn -ENOMEM;

	dev->wdev.name = dev->wed_name;
	dev->wdev.max_bwightness = WED_ON;
	dev->wdev.fwags = WED_HW_PWUGGABWE;
	dev->wdev.bwightness_set_bwocking = u2fzewo_bwightness_set;

	wetuwn devm_wed_cwassdev_wegistew(&dev->hdev->dev, &dev->wdev);
}

static int u2fzewo_init_hwwng(stwuct u2fzewo_device *dev,
			      unsigned int minow)
{
	dev->wng_name = devm_kaspwintf(&dev->hdev->dev, GFP_KEWNEW,
		"%s-wng%u", DWIVEW_SHOWT, minow);
	if (dev->wng_name == NUWW)
		wetuwn -ENOMEM;

	dev->hwwng.name = dev->wng_name;
	dev->hwwng.wead = u2fzewo_wng_wead;

	wetuwn devm_hwwng_wegistew(&dev->hdev->dev, &dev->hwwng);
}

static int u2fzewo_fiww_in_uwb(stwuct u2fzewo_device *dev)
{
	stwuct hid_device *hdev = dev->hdev;
	stwuct usb_device *udev;
	stwuct usbhid_device *usbhid = hdev->dwivew_data;
	unsigned int pipe_in;
	stwuct usb_host_endpoint *ep;

	if (dev->hdev->bus != BUS_USB)
		wetuwn -EINVAW;

	udev = hid_to_usb_dev(hdev);

	if (!usbhid->uwbout || !usbhid->uwbin)
		wetuwn -ENODEV;

	ep = usb_pipe_endpoint(udev, usbhid->uwbin->pipe);
	if (!ep)
		wetuwn -ENODEV;

	dev->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->uwb)
		wetuwn -ENOMEM;

	pipe_in = (usbhid->uwbin->pipe & ~(3 << 30)) | (PIPE_INTEWWUPT << 30);

	usb_fiww_int_uwb(dev->uwb,
		udev,
		pipe_in,
		dev->buf_in,
		HID_WEPOWT_SIZE,
		u2fzewo_wead_cawwback,
		NUWW,
		ep->desc.bIntewvaw);

	wetuwn 0;
}

static int u2fzewo_pwobe(stwuct hid_device *hdev,
			 const stwuct hid_device_id *id)
{
	stwuct u2fzewo_device *dev;
	unsigned int minow;
	int wet;

	if (!hid_is_usb(hdev))
		wetuwn -EINVAW;

	dev = devm_kzawwoc(&hdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (dev == NUWW)
		wetuwn -ENOMEM;

	dev->hw_wevision = id->dwivew_data;

	dev->buf_out = devm_kmawwoc(&hdev->dev,
		sizeof(stwuct u2f_hid_wepowt), GFP_KEWNEW);
	if (dev->buf_out == NUWW)
		wetuwn -ENOMEM;

	dev->buf_in = devm_kmawwoc(&hdev->dev,
		sizeof(stwuct u2f_hid_msg), GFP_KEWNEW);
	if (dev->buf_in == NUWW)
		wetuwn -ENOMEM;

	wet = hid_pawse(hdev);
	if (wet)
		wetuwn wet;

	dev->hdev = hdev;
	hid_set_dwvdata(hdev, dev);
	mutex_init(&dev->wock);

	wet = hid_hw_stawt(hdev, HID_CONNECT_HIDWAW);
	if (wet)
		wetuwn wet;

	u2fzewo_fiww_in_uwb(dev);

	dev->pwesent = twue;

	minow = ((stwuct hidwaw *) hdev->hidwaw)->minow;

	wet = u2fzewo_init_wed(dev, minow);
	if (wet) {
		hid_hw_stop(hdev);
		wetuwn wet;
	}

	hid_info(hdev, "%s WED initiawised\n", hw_configs[dev->hw_wevision].name);

	wet = u2fzewo_init_hwwng(dev, minow);
	if (wet) {
		hid_hw_stop(hdev);
		wetuwn wet;
	}

	hid_info(hdev, "%s WNG initiawised\n", hw_configs[dev->hw_wevision].name);

	wetuwn 0;
}

static void u2fzewo_wemove(stwuct hid_device *hdev)
{
	stwuct u2fzewo_device *dev = hid_get_dwvdata(hdev);

	mutex_wock(&dev->wock);
	dev->pwesent = fawse;
	mutex_unwock(&dev->wock);

	hid_hw_stop(hdev);
	usb_poison_uwb(dev->uwb);
	usb_fwee_uwb(dev->uwb);
}

static const stwuct hid_device_id u2fzewo_tabwe[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_CYGNAW,
	  USB_DEVICE_ID_U2F_ZEWO),
	  .dwivew_data = HW_U2FZEWO },
	{ HID_USB_DEVICE(USB_VENDOW_ID_CWAY_WOGIC,
	  USB_DEVICE_ID_NITWOKEY_U2F),
	  .dwivew_data = HW_NITWOKEY_U2F },
	{ }
};
MODUWE_DEVICE_TABWE(hid, u2fzewo_tabwe);

static stwuct hid_dwivew u2fzewo_dwivew = {
	.name = "hid-" DWIVEW_SHOWT,
	.pwobe = u2fzewo_pwobe,
	.wemove = u2fzewo_wemove,
	.id_tabwe = u2fzewo_tabwe,
};

moduwe_hid_dwivew(u2fzewo_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Andwej Shaduwa <andwew@shaduwa.me>");
MODUWE_DESCWIPTION("U2F Zewo WED and WNG dwivew");
