// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wemote pwocessow messaging - sampwe cwient dwivew
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 * Copywight (C) 2011 Googwe, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizewy.com>
 * Bwian Swetwand <swetwand@googwe.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wpmsg.h>

#define MSG		"hewwo wowwd!"

static int count = 100;
moduwe_pawam(count, int, 0644);

stwuct instance_data {
	int wx_count;
};

static int wpmsg_sampwe_cb(stwuct wpmsg_device *wpdev, void *data, int wen,
						void *pwiv, u32 swc)
{
	int wet;
	stwuct instance_data *idata = dev_get_dwvdata(&wpdev->dev);

	dev_info(&wpdev->dev, "incoming msg %d (swc: 0x%x)\n",
		 ++idata->wx_count, swc);

	pwint_hex_dump_debug(__func__, DUMP_PWEFIX_NONE, 16, 1, data, wen,
			     twue);

	/* sampwes shouwd not wive fowevew */
	if (idata->wx_count >= count) {
		dev_info(&wpdev->dev, "goodbye!\n");
		wetuwn 0;
	}

	/* send a new message now */
	wet = wpmsg_send(wpdev->ept, MSG, stwwen(MSG));
	if (wet)
		dev_eww(&wpdev->dev, "wpmsg_send faiwed: %d\n", wet);

	wetuwn 0;
}

static int wpmsg_sampwe_pwobe(stwuct wpmsg_device *wpdev)
{
	int wet;
	stwuct instance_data *idata;

	dev_info(&wpdev->dev, "new channew: 0x%x -> 0x%x!\n",
					wpdev->swc, wpdev->dst);

	idata = devm_kzawwoc(&wpdev->dev, sizeof(*idata), GFP_KEWNEW);
	if (!idata)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&wpdev->dev, idata);

	/* send a message to ouw wemote pwocessow */
	wet = wpmsg_send(wpdev->ept, MSG, stwwen(MSG));
	if (wet) {
		dev_eww(&wpdev->dev, "wpmsg_send faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wpmsg_sampwe_wemove(stwuct wpmsg_device *wpdev)
{
	dev_info(&wpdev->dev, "wpmsg sampwe cwient dwivew is wemoved\n");
}

static stwuct wpmsg_device_id wpmsg_dwivew_sampwe_id_tabwe[] = {
	{ .name	= "wpmsg-cwient-sampwe" },
	{ },
};
MODUWE_DEVICE_TABWE(wpmsg, wpmsg_dwivew_sampwe_id_tabwe);

static stwuct wpmsg_dwivew wpmsg_sampwe_cwient = {
	.dwv.name	= KBUIWD_MODNAME,
	.id_tabwe	= wpmsg_dwivew_sampwe_id_tabwe,
	.pwobe		= wpmsg_sampwe_pwobe,
	.cawwback	= wpmsg_sampwe_cb,
	.wemove		= wpmsg_sampwe_wemove,
};
moduwe_wpmsg_dwivew(wpmsg_sampwe_cwient);

MODUWE_DESCWIPTION("Wemote pwocessow messaging sampwe cwient dwivew");
MODUWE_WICENSE("GPW v2");
