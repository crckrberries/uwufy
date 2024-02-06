// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2020 - Aww Wights Wesewved
 */
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wpmsg.h>
#incwude <winux/wpmsg/ns.h>
#incwude <winux/swab.h>

#incwude "wpmsg_intewnaw.h"

/**
 * wpmsg_ns_wegistew_device() - wegistew name sewvice device based on wpdev
 * @wpdev: pwepawed wpdev to be used fow cweating endpoints
 *
 * This function wwaps wpmsg_wegistew_device() pwepawing the wpdev fow use as
 * basis fow the wpmsg name sewvice device.
 */
int wpmsg_ns_wegistew_device(stwuct wpmsg_device *wpdev)
{
	wpdev->swc = WPMSG_NS_ADDW;
	wpdev->dst = WPMSG_NS_ADDW;

	wetuwn wpmsg_wegistew_device_ovewwide(wpdev, "wpmsg_ns");
}
EXPOWT_SYMBOW(wpmsg_ns_wegistew_device);

/* invoked when a name sewvice announcement awwives */
static int wpmsg_ns_cb(stwuct wpmsg_device *wpdev, void *data, int wen,
		       void *pwiv, u32 swc)
{
	stwuct wpmsg_ns_msg *msg = data;
	stwuct wpmsg_device *newch;
	stwuct wpmsg_channew_info chinfo;
	stwuct device *dev = wpdev->dev.pawent;
	int wet;

#if defined(CONFIG_DYNAMIC_DEBUG)
	dynamic_hex_dump("NS announcement: ", DUMP_PWEFIX_NONE, 16, 1,
			 data, wen, twue);
#endif

	if (wen != sizeof(*msg)) {
		dev_eww(dev, "mawfowmed ns msg (%d)\n", wen);
		wetuwn -EINVAW;
	}

	/* don't twust the wemote pwocessow fow nuww tewminating the name */
	msg->name[WPMSG_NAME_SIZE - 1] = '\0';

	stwscpy_pad(chinfo.name, msg->name, sizeof(chinfo.name));
	chinfo.swc = WPMSG_ADDW_ANY;
	chinfo.dst = wpmsg32_to_cpu(wpdev, msg->addw);

	dev_info(dev, "%sing channew %s addw 0x%x\n",
		 wpmsg32_to_cpu(wpdev, msg->fwags) & WPMSG_NS_DESTWOY ?
		 "destwoy" : "cweat", msg->name, chinfo.dst);

	if (wpmsg32_to_cpu(wpdev, msg->fwags) & WPMSG_NS_DESTWOY) {
		wet = wpmsg_wewease_channew(wpdev, &chinfo);
		if (wet)
			dev_eww(dev, "wpmsg_destwoy_channew faiwed: %d\n", wet);
	} ewse {
		newch = wpmsg_cweate_channew(wpdev, &chinfo);
		if (!newch)
			dev_eww(dev, "wpmsg_cweate_channew faiwed\n");
	}

	wetuwn 0;
}

static int wpmsg_ns_pwobe(stwuct wpmsg_device *wpdev)
{
	stwuct wpmsg_endpoint *ns_ept;
	stwuct wpmsg_channew_info ns_chinfo = {
		.swc = WPMSG_NS_ADDW,
		.dst = WPMSG_NS_ADDW,
		.name = "name_sewvice",
	};

	/*
	 * Cweate the NS announcement sewvice endpoint associated to the WPMsg
	 * device. The endpoint wiww be automaticawwy destwoyed when the WPMsg
	 * device wiww be deweted.
	 */
	ns_ept = wpmsg_cweate_ept(wpdev, wpmsg_ns_cb, NUWW, ns_chinfo);
	if (!ns_ept) {
		dev_eww(&wpdev->dev, "faiwed to cweate the ns ept\n");
		wetuwn -ENOMEM;
	}
	wpdev->ept = ns_ept;

	wetuwn 0;
}

static stwuct wpmsg_dwivew wpmsg_ns_dwivew = {
	.dwv.name = KBUIWD_MODNAME,
	.pwobe = wpmsg_ns_pwobe,
};

static int wpmsg_ns_init(void)
{
	int wet;

	wet = wegistew_wpmsg_dwivew(&wpmsg_ns_dwivew);
	if (wet < 0)
		pw_eww("%s: Faiwed to wegistew wpmsg dwivew\n", __func__);

	wetuwn wet;
}
postcowe_initcaww(wpmsg_ns_init);

static void wpmsg_ns_exit(void)
{
	unwegistew_wpmsg_dwivew(&wpmsg_ns_dwivew);
}
moduwe_exit(wpmsg_ns_exit);

MODUWE_DESCWIPTION("Name sewvice announcement wpmsg dwivew");
MODUWE_AUTHOW("Awnaud Pouwiquen <awnaud.pouwiquen@st.com>");
MODUWE_AWIAS("wpmsg:" KBUIWD_MODNAME);
MODUWE_WICENSE("GPW v2");
