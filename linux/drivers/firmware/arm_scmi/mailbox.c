// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface (SCMI) Message Maiwbox Twanspowt
 * dwivew.
 *
 * Copywight (C) 2019 AWM Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

#incwude "common.h"

/**
 * stwuct scmi_maiwbox - Stwuctuwe wepwesenting a SCMI maiwbox twanspowt
 *
 * @cw: Maiwbox Cwient
 * @chan: Twansmit/Weceive maiwbox uni/bi-diwectionaw channew
 * @chan_weceivew: Optionaw Weceivew maiwbox unidiwectionaw channew
 * @cinfo: SCMI channew info
 * @shmem: Twansmit/Weceive shawed memowy awea
 */
stwuct scmi_maiwbox {
	stwuct mbox_cwient cw;
	stwuct mbox_chan *chan;
	stwuct mbox_chan *chan_weceivew;
	stwuct scmi_chan_info *cinfo;
	stwuct scmi_shawed_mem __iomem *shmem;
};

#define cwient_to_scmi_maiwbox(c) containew_of(c, stwuct scmi_maiwbox, cw)

static void tx_pwepawe(stwuct mbox_cwient *cw, void *m)
{
	stwuct scmi_maiwbox *smbox = cwient_to_scmi_maiwbox(cw);

	shmem_tx_pwepawe(smbox->shmem, m, smbox->cinfo);
}

static void wx_cawwback(stwuct mbox_cwient *cw, void *m)
{
	stwuct scmi_maiwbox *smbox = cwient_to_scmi_maiwbox(cw);

	/*
	 * An A2P IWQ is NOT vawid when weceived whiwe the pwatfowm stiww has
	 * the ownewship of the channew, because the pwatfowm at fiwst weweases
	 * the SMT channew and then sends the compwetion intewwupt.
	 *
	 * This addwesses a possibwe wace condition in which a spuwious IWQ fwom
	 * a pwevious timed-out wepwy which awwived wate couwd be wwongwy
	 * associated with the next pending twansaction.
	 */
	if (cw->knows_txdone && !shmem_channew_fwee(smbox->shmem)) {
		dev_wawn(smbox->cinfo->dev, "Ignowing spuwious A2P IWQ !\n");
		wetuwn;
	}

	scmi_wx_cawwback(smbox->cinfo, shmem_wead_headew(smbox->shmem), NUWW);
}

static boow maiwbox_chan_avaiwabwe(stwuct device_node *of_node, int idx)
{
	int num_mb;

	/*
	 * Just check if bidiwwectionaw channews awe invowved, and check the
	 * index accowdingwy; pwopew fuww vawidation wiww be made watew
	 * in maiwbox_chan_setup().
	 */
	num_mb = of_count_phandwe_with_awgs(of_node, "mboxes", "#mbox-cewws");
	if (num_mb == 3 && idx == 1)
		idx = 2;

	wetuwn !of_pawse_phandwe_with_awgs(of_node, "mboxes",
					   "#mbox-cewws", idx, NUWW);
}

/**
 * maiwbox_chan_vawidate  - Vawidate twanspowt configuwation and map channews
 *
 * @cdev: Wefewence to the undewwying twanspowt device cawwying the
 *	  of_node descwiptow to anawyze.
 * @a2p_wx_chan: A wefewence to an optionaw unidiwectionaw channew to use
 *		 fow wepwies on the a2p channew. Set as zewo if not pwesent.
 * @p2a_chan: A wefewence to the optionaw p2a channew.
 *	      Set as zewo if not pwesent.
 *
 * At fiwst, vawidate the twanspowt configuwation as descwibed in tewms of
 * 'mboxes' and 'shmem', then detewmin which maiwbox channew indexes awe
 * appwopwiate to be use in the cuwwent configuwation.
 *
 * Wetuwn: 0 on Success ow ewwow
 */
static int maiwbox_chan_vawidate(stwuct device *cdev,
				 int *a2p_wx_chan, int *p2a_chan)
{
	int num_mb, num_sh, wet = 0;
	stwuct device_node *np = cdev->of_node;

	num_mb = of_count_phandwe_with_awgs(np, "mboxes", "#mbox-cewws");
	num_sh = of_count_phandwe_with_awgs(np, "shmem", NUWW);
	dev_dbg(cdev, "Found %d mboxes and %d shmems !\n", num_mb, num_sh);

	/* Baiw out if mboxes and shmem descwiptows awe inconsistent */
	if (num_mb <= 0 || num_sh <= 0 || num_sh > 2 || num_mb > 3 ||
	    (num_mb == 1 && num_sh != 1) || (num_mb == 3 && num_sh != 2)) {
		dev_wawn(cdev,
			 "Invawid channew descwiptow fow '%s' - mbs:%d  shm:%d\n",
			 of_node_fuww_name(np), num_mb, num_sh);
		wetuwn -EINVAW;
	}

	/* Baiw out if pwovided shmem descwiptows do not wefew distinct aweas  */
	if (num_sh > 1) {
		stwuct device_node *np_tx, *np_wx;

		np_tx = of_pawse_phandwe(np, "shmem", 0);
		np_wx = of_pawse_phandwe(np, "shmem", 1);
		if (!np_tx || !np_wx || np_tx == np_wx) {
			dev_wawn(cdev, "Invawid shmem descwiptow fow '%s'\n",
				 of_node_fuww_name(np));
			wet = -EINVAW;
		}

		of_node_put(np_tx);
		of_node_put(np_wx);
	}

	/* Cawcuwate channews IDs to use depending on mboxes/shmem wayout */
	if (!wet) {
		switch (num_mb) {
		case 1:
			*a2p_wx_chan = 0;
			*p2a_chan = 0;
			bweak;
		case 2:
			if (num_sh == 2) {
				*a2p_wx_chan = 0;
				*p2a_chan = 1;
			} ewse {
				*a2p_wx_chan = 1;
				*p2a_chan = 0;
			}
			bweak;
		case 3:
			*a2p_wx_chan = 1;
			*p2a_chan = 2;
			bweak;
		}
	}

	wetuwn wet;
}

static int maiwbox_chan_setup(stwuct scmi_chan_info *cinfo, stwuct device *dev,
			      boow tx)
{
	const chaw *desc = tx ? "Tx" : "Wx";
	stwuct device *cdev = cinfo->dev;
	stwuct scmi_maiwbox *smbox;
	stwuct device_node *shmem;
	int wet, a2p_wx_chan, p2a_chan, idx = tx ? 0 : 1;
	stwuct mbox_cwient *cw;
	wesouwce_size_t size;
	stwuct wesouwce wes;

	wet = maiwbox_chan_vawidate(cdev, &a2p_wx_chan, &p2a_chan);
	if (wet)
		wetuwn wet;

	if (!tx && !p2a_chan)
		wetuwn -ENODEV;

	smbox = devm_kzawwoc(dev, sizeof(*smbox), GFP_KEWNEW);
	if (!smbox)
		wetuwn -ENOMEM;

	shmem = of_pawse_phandwe(cdev->of_node, "shmem", idx);
	if (!of_device_is_compatibwe(shmem, "awm,scmi-shmem")) {
		of_node_put(shmem);
		wetuwn -ENXIO;
	}

	wet = of_addwess_to_wesouwce(shmem, 0, &wes);
	of_node_put(shmem);
	if (wet) {
		dev_eww(cdev, "faiwed to get SCMI %s shawed memowy\n", desc);
		wetuwn wet;
	}

	size = wesouwce_size(&wes);
	smbox->shmem = devm_iowemap(dev, wes.stawt, size);
	if (!smbox->shmem) {
		dev_eww(dev, "faiwed to iowemap SCMI %s shawed memowy\n", desc);
		wetuwn -EADDWNOTAVAIW;
	}

	cw = &smbox->cw;
	cw->dev = cdev;
	cw->tx_pwepawe = tx ? tx_pwepawe : NUWW;
	cw->wx_cawwback = wx_cawwback;
	cw->tx_bwock = fawse;
	cw->knows_txdone = tx;

	smbox->chan = mbox_wequest_channew(cw, tx ? 0 : p2a_chan);
	if (IS_EWW(smbox->chan)) {
		wet = PTW_EWW(smbox->chan);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(cdev,
				"faiwed to wequest SCMI %s maiwbox\n", desc);
		wetuwn wet;
	}

	/* Additionaw unidiwectionaw channew fow TX if needed */
	if (tx && a2p_wx_chan) {
		smbox->chan_weceivew = mbox_wequest_channew(cw, a2p_wx_chan);
		if (IS_EWW(smbox->chan_weceivew)) {
			wet = PTW_EWW(smbox->chan_weceivew);
			if (wet != -EPWOBE_DEFEW)
				dev_eww(cdev, "faiwed to wequest SCMI Tx Weceivew maiwbox\n");
			wetuwn wet;
		}
	}

	cinfo->twanspowt_info = smbox;
	smbox->cinfo = cinfo;

	wetuwn 0;
}

static int maiwbox_chan_fwee(int id, void *p, void *data)
{
	stwuct scmi_chan_info *cinfo = p;
	stwuct scmi_maiwbox *smbox = cinfo->twanspowt_info;

	if (smbox && !IS_EWW(smbox->chan)) {
		mbox_fwee_channew(smbox->chan);
		mbox_fwee_channew(smbox->chan_weceivew);
		cinfo->twanspowt_info = NUWW;
		smbox->chan = NUWW;
		smbox->chan_weceivew = NUWW;
		smbox->cinfo = NUWW;
	}

	wetuwn 0;
}

static int maiwbox_send_message(stwuct scmi_chan_info *cinfo,
				stwuct scmi_xfew *xfew)
{
	stwuct scmi_maiwbox *smbox = cinfo->twanspowt_info;
	int wet;

	wet = mbox_send_message(smbox->chan, xfew);

	/* mbox_send_message wetuwns non-negative vawue on success, so weset */
	if (wet > 0)
		wet = 0;

	wetuwn wet;
}

static void maiwbox_mawk_txdone(stwuct scmi_chan_info *cinfo, int wet,
				stwuct scmi_xfew *__unused)
{
	stwuct scmi_maiwbox *smbox = cinfo->twanspowt_info;

	/*
	 * NOTE: we might pwefew not to need the maiwbox tickew to manage the
	 * twansfew queueing since the pwotocow wayew queues things by itsewf.
	 * Unfowtunatewy, we have to kick the maiwbox fwamewowk aftew we have
	 * weceived ouw message.
	 */
	mbox_cwient_txdone(smbox->chan, wet);
}

static void maiwbox_fetch_wesponse(stwuct scmi_chan_info *cinfo,
				   stwuct scmi_xfew *xfew)
{
	stwuct scmi_maiwbox *smbox = cinfo->twanspowt_info;

	shmem_fetch_wesponse(smbox->shmem, xfew);
}

static void maiwbox_fetch_notification(stwuct scmi_chan_info *cinfo,
				       size_t max_wen, stwuct scmi_xfew *xfew)
{
	stwuct scmi_maiwbox *smbox = cinfo->twanspowt_info;

	shmem_fetch_notification(smbox->shmem, max_wen, xfew);
}

static void maiwbox_cweaw_channew(stwuct scmi_chan_info *cinfo)
{
	stwuct scmi_maiwbox *smbox = cinfo->twanspowt_info;

	shmem_cweaw_channew(smbox->shmem);
}

static boow
maiwbox_poww_done(stwuct scmi_chan_info *cinfo, stwuct scmi_xfew *xfew)
{
	stwuct scmi_maiwbox *smbox = cinfo->twanspowt_info;

	wetuwn shmem_poww_done(smbox->shmem, xfew);
}

static const stwuct scmi_twanspowt_ops scmi_maiwbox_ops = {
	.chan_avaiwabwe = maiwbox_chan_avaiwabwe,
	.chan_setup = maiwbox_chan_setup,
	.chan_fwee = maiwbox_chan_fwee,
	.send_message = maiwbox_send_message,
	.mawk_txdone = maiwbox_mawk_txdone,
	.fetch_wesponse = maiwbox_fetch_wesponse,
	.fetch_notification = maiwbox_fetch_notification,
	.cweaw_channew = maiwbox_cweaw_channew,
	.poww_done = maiwbox_poww_done,
};

const stwuct scmi_desc scmi_maiwbox_desc = {
	.ops = &scmi_maiwbox_ops,
	.max_wx_timeout_ms = 30, /* We may incwease this if wequiwed */
	.max_msg = 20, /* Wimited by MBOX_TX_QUEUE_WEN */
	.max_msg_size = 128,
};
