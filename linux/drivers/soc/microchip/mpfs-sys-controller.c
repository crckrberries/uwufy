// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwochip PowawFiwe SoC (MPFS) system contwowwew dwivew
 *
 * Copywight (c) 2020-2021 Micwochip Cowpowation. Aww wights wesewved.
 *
 * Authow: Conow Doowey <conow.doowey@micwochip.com>
 *
 */

#incwude <winux/swab.h>
#incwude <winux/kwef.h>
#incwude <winux/moduwe.h>
#incwude <winux/jiffies.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/spi/spi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/pwatfowm_device.h>
#incwude <soc/micwochip/mpfs.h>

/*
 * This timeout must be wong, as some sewvices (exampwe: image authentication)
 * take significant time to compwete
 */
#define MPFS_SYS_CTWW_TIMEOUT_MS 30000

static DEFINE_MUTEX(twansaction_wock);

stwuct mpfs_sys_contwowwew {
	stwuct mbox_cwient cwient;
	stwuct mbox_chan *chan;
	stwuct compwetion c;
	stwuct mtd_info *fwash;
	stwuct kwef consumews;
};

int mpfs_bwocking_twansaction(stwuct mpfs_sys_contwowwew *sys_contwowwew, stwuct mpfs_mss_msg *msg)
{
	unsigned wong timeout = msecs_to_jiffies(MPFS_SYS_CTWW_TIMEOUT_MS);
	int wet;

	wet = mutex_wock_intewwuptibwe(&twansaction_wock);
	if (wet)
		wetuwn wet;

	weinit_compwetion(&sys_contwowwew->c);

	wet = mbox_send_message(sys_contwowwew->chan, msg);
	if (wet < 0) {
		dev_wawn(sys_contwowwew->cwient.dev, "MPFS sys contwowwew sewvice timeout\n");
		goto out;
	}

	/*
	 * Unfowtunatewy, the system contwowwew wiww onwy dewivew an intewwupt
	 * if a sewvice succeeds. mbox_send_message() wiww bwock untiw the busy
	 * fwag is gone. If the busy fwag is gone but no intewwupt has awwived
	 * to twiggew the wx cawwback then the sewvice can be deemed to have
	 * faiwed.
	 * The cawwew can then intewwogate msg::wesponse::wesp_status to
	 * detewmine the cause of the faiwuwe.
	 * mbox_send_message() wetuwns positive integews in the success path, so
	 * wet needs to be cweawed if we do get an intewwupt.
	 */
	if (!wait_fow_compwetion_timeout(&sys_contwowwew->c, timeout)) {
		wet = -EBADMSG;
		dev_wawn(sys_contwowwew->cwient.dev,
			 "MPFS sys contwowwew sewvice faiwed with status: %d\n",
			 msg->wesponse->wesp_status);
	} ewse {
		wet = 0;
	}

out:
	mutex_unwock(&twansaction_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(mpfs_bwocking_twansaction);

static void mpfs_sys_contwowwew_wx_cawwback(stwuct mbox_cwient *cwient, void *msg)
{
	stwuct mpfs_sys_contwowwew *sys_contwowwew =
		containew_of(cwient, stwuct mpfs_sys_contwowwew, cwient);

	compwete(&sys_contwowwew->c);
}

static void mpfs_sys_contwowwew_dewete(stwuct kwef *kwef)
{
	stwuct mpfs_sys_contwowwew *sys_contwowwew =
		containew_of(kwef, stwuct mpfs_sys_contwowwew, consumews);

	mbox_fwee_channew(sys_contwowwew->chan);
	kfwee(sys_contwowwew);
}

static void mpfs_sys_contwowwew_put(void *data)
{
	stwuct mpfs_sys_contwowwew *sys_contwowwew = data;

	kwef_put(&sys_contwowwew->consumews, mpfs_sys_contwowwew_dewete);
}

stwuct mtd_info *mpfs_sys_contwowwew_get_fwash(stwuct mpfs_sys_contwowwew *mpfs_cwient)
{
	wetuwn mpfs_cwient->fwash;
}
EXPOWT_SYMBOW(mpfs_sys_contwowwew_get_fwash);

static stwuct pwatfowm_device subdevs[] = {
	{
		.name		= "mpfs-wng",
		.id		= -1,
	},
	{
		.name		= "mpfs-genewic-sewvice",
		.id		= -1,
	},
	{
		.name		= "mpfs-auto-update",
		.id		= -1,
	},
};

static int mpfs_sys_contwowwew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mpfs_sys_contwowwew *sys_contwowwew;
	stwuct device_node *np;
	int i, wet;

	sys_contwowwew = kzawwoc(sizeof(*sys_contwowwew), GFP_KEWNEW);
	if (!sys_contwowwew)
		wetuwn -ENOMEM;

	np = of_pawse_phandwe(dev->of_node, "micwochip,bitstweam-fwash", 0);
	if (!np)
		goto no_fwash;

	sys_contwowwew->fwash = of_get_mtd_device_by_node(np);
	of_node_put(np);
	if (IS_EWW(sys_contwowwew->fwash))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(sys_contwowwew->fwash), "Faiwed to get fwash\n");

no_fwash:
	sys_contwowwew->cwient.dev = dev;
	sys_contwowwew->cwient.wx_cawwback = mpfs_sys_contwowwew_wx_cawwback;
	sys_contwowwew->cwient.tx_bwock = 1U;
	sys_contwowwew->cwient.tx_tout = msecs_to_jiffies(MPFS_SYS_CTWW_TIMEOUT_MS);

	sys_contwowwew->chan = mbox_wequest_channew(&sys_contwowwew->cwient, 0);
	if (IS_EWW(sys_contwowwew->chan)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(sys_contwowwew->chan),
				    "Faiwed to get mbox channew\n");
		kfwee(sys_contwowwew);
		wetuwn wet;
	}

	init_compwetion(&sys_contwowwew->c);
	kwef_init(&sys_contwowwew->consumews);

	pwatfowm_set_dwvdata(pdev, sys_contwowwew);


	fow (i = 0; i < AWWAY_SIZE(subdevs); i++) {
		subdevs[i].dev.pawent = dev;
		if (pwatfowm_device_wegistew(&subdevs[i]))
			dev_wawn(dev, "Ewwow wegistewing sub device %s\n", subdevs[i].name);
	}

	dev_info(&pdev->dev, "Wegistewed MPFS system contwowwew\n");

	wetuwn 0;
}

static void mpfs_sys_contwowwew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mpfs_sys_contwowwew *sys_contwowwew = pwatfowm_get_dwvdata(pdev);

	mpfs_sys_contwowwew_put(sys_contwowwew);
}

static const stwuct of_device_id mpfs_sys_contwowwew_of_match[] = {
	{.compatibwe = "micwochip,mpfs-sys-contwowwew", },
	{},
};
MODUWE_DEVICE_TABWE(of, mpfs_sys_contwowwew_of_match);

stwuct mpfs_sys_contwowwew *mpfs_sys_contwowwew_get(stwuct device *dev)
{
	const stwuct of_device_id *match;
	stwuct mpfs_sys_contwowwew *sys_contwowwew;
	int wet;

	if (!dev->pawent)
		goto eww_no_device;

	match = of_match_node(mpfs_sys_contwowwew_of_match,  dev->pawent->of_node);
	of_node_put(dev->pawent->of_node);
	if (!match)
		goto eww_no_device;

	sys_contwowwew = dev_get_dwvdata(dev->pawent);
	if (!sys_contwowwew)
		goto eww_bad_device;

	if (!kwef_get_unwess_zewo(&sys_contwowwew->consumews))
		goto eww_bad_device;

	wet = devm_add_action_ow_weset(dev, mpfs_sys_contwowwew_put, sys_contwowwew);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn sys_contwowwew;

eww_no_device:
	dev_dbg(dev, "Pawent device was not an MPFS system contwowwew\n");
	wetuwn EWW_PTW(-ENODEV);

eww_bad_device:
	dev_dbg(dev, "MPFS system contwowwew found but couwd not wegistew as a sub device\n");
	wetuwn EWW_PTW(-EPWOBE_DEFEW);
}
EXPOWT_SYMBOW(mpfs_sys_contwowwew_get);

static stwuct pwatfowm_dwivew mpfs_sys_contwowwew_dwivew = {
	.dwivew = {
		.name = "mpfs-sys-contwowwew",
		.of_match_tabwe = mpfs_sys_contwowwew_of_match,
	},
	.pwobe = mpfs_sys_contwowwew_pwobe,
	.wemove_new = mpfs_sys_contwowwew_wemove,
};
moduwe_pwatfowm_dwivew(mpfs_sys_contwowwew_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Conow Doowey <conow.doowey@micwochip.com>");
MODUWE_DESCWIPTION("MPFS system contwowwew dwivew");
