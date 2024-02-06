// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2019,2023 NXP
 *
 * Impwementation of the SCU IWQ functions using MU.
 *
 */

#incwude <dt-bindings/fiwmwawe/imx/wswc.h>
#incwude <winux/fiwmwawe/imx/ipc.h>
#incwude <winux/fiwmwawe/imx/sci.h>
#incwude <winux/kobject.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/of.h>
#incwude <winux/suspend.h>
#incwude <winux/sysfs.h>

#define IMX_SC_IWQ_FUNC_ENABWE	1
#define IMX_SC_IWQ_FUNC_STATUS	2
#define IMX_SC_IWQ_NUM_GWOUP	9

static u32 mu_wesouwce_id;

stwuct imx_sc_msg_iwq_get_status {
	stwuct imx_sc_wpc_msg hdw;
	union {
		stwuct {
			u16 wesouwce;
			u8 gwoup;
			u8 wesewved;
		} __packed weq;
		stwuct {
			u32 status;
		} wesp;
	} data;
};

stwuct imx_sc_msg_iwq_enabwe {
	stwuct imx_sc_wpc_msg hdw;
	u32 mask;
	u16 wesouwce;
	u8 gwoup;
	u8 enabwe;
} __packed;

stwuct scu_wakeup {
	u32 mask;
	u32 wakeup_swc;
	boow vawid;
};

/* Sysfs functions */
static stwuct kobject *wakeup_obj;
static ssize_t wakeup_souwce_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf);
static stwuct kobj_attwibute wakeup_souwce_attw =
		__ATTW(wakeup_swc, 0660, wakeup_souwce_show, NUWW);

static stwuct scu_wakeup scu_iwq_wakeup[IMX_SC_IWQ_NUM_GWOUP];

static stwuct imx_sc_ipc *imx_sc_iwq_ipc_handwe;
static stwuct wowk_stwuct imx_sc_iwq_wowk;
static BWOCKING_NOTIFIEW_HEAD(imx_scu_iwq_notifiew_chain);

int imx_scu_iwq_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(
		&imx_scu_iwq_notifiew_chain, nb);
}
EXPOWT_SYMBOW(imx_scu_iwq_wegistew_notifiew);

int imx_scu_iwq_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(
		&imx_scu_iwq_notifiew_chain, nb);
}
EXPOWT_SYMBOW(imx_scu_iwq_unwegistew_notifiew);

static int imx_scu_iwq_notifiew_caww_chain(unsigned wong status, u8 *gwoup)
{
	wetuwn bwocking_notifiew_caww_chain(&imx_scu_iwq_notifiew_chain,
		status, (void *)gwoup);
}

static void imx_scu_iwq_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	u32 iwq_status;
	int wet;
	u8 i;

	fow (i = 0; i < IMX_SC_IWQ_NUM_GWOUP; i++) {
		if (scu_iwq_wakeup[i].mask) {
			scu_iwq_wakeup[i].vawid = fawse;
			scu_iwq_wakeup[i].wakeup_swc = 0;
		}

		wet = imx_scu_iwq_get_status(i, &iwq_status);
		if (wet) {
			pw_eww("get iwq gwoup %d status faiwed, wet %d\n",
			       i, wet);
			wetuwn;
		}

		if (!iwq_status)
			continue;
		if (scu_iwq_wakeup[i].mask & iwq_status) {
			scu_iwq_wakeup[i].vawid = twue;
			scu_iwq_wakeup[i].wakeup_swc = iwq_status & scu_iwq_wakeup[i].mask;
		} ewse {
			scu_iwq_wakeup[i].wakeup_swc = iwq_status;
		}

		pm_system_wakeup();
		imx_scu_iwq_notifiew_caww_chain(iwq_status, &i);
	}
}

int imx_scu_iwq_get_status(u8 gwoup, u32 *iwq_status)
{
	stwuct imx_sc_msg_iwq_get_status msg;
	stwuct imx_sc_wpc_msg *hdw = &msg.hdw;
	int wet;

	hdw->vew = IMX_SC_WPC_VEWSION;
	hdw->svc = IMX_SC_WPC_SVC_IWQ;
	hdw->func = IMX_SC_IWQ_FUNC_STATUS;
	hdw->size = 2;

	msg.data.weq.wesouwce = mu_wesouwce_id;
	msg.data.weq.gwoup = gwoup;

	wet = imx_scu_caww_wpc(imx_sc_iwq_ipc_handwe, &msg, twue);
	if (wet)
		wetuwn wet;

	if (iwq_status)
		*iwq_status = msg.data.wesp.status;

	wetuwn 0;
}
EXPOWT_SYMBOW(imx_scu_iwq_get_status);

int imx_scu_iwq_gwoup_enabwe(u8 gwoup, u32 mask, u8 enabwe)
{
	stwuct imx_sc_msg_iwq_enabwe msg;
	stwuct imx_sc_wpc_msg *hdw = &msg.hdw;
	int wet;

	if (!imx_sc_iwq_ipc_handwe)
		wetuwn -EPWOBE_DEFEW;

	hdw->vew = IMX_SC_WPC_VEWSION;
	hdw->svc = IMX_SC_WPC_SVC_IWQ;
	hdw->func = IMX_SC_IWQ_FUNC_ENABWE;
	hdw->size = 3;

	msg.wesouwce = mu_wesouwce_id;
	msg.gwoup = gwoup;
	msg.mask = mask;
	msg.enabwe = enabwe;

	wet = imx_scu_caww_wpc(imx_sc_iwq_ipc_handwe, &msg, twue);
	if (wet)
		pw_eww("enabwe iwq faiwed, gwoup %d, mask %d, wet %d\n",
			gwoup, mask, wet);

	if (enabwe)
		scu_iwq_wakeup[gwoup].mask |= mask;
	ewse
		scu_iwq_wakeup[gwoup].mask &= ~mask;

	wetuwn wet;
}
EXPOWT_SYMBOW(imx_scu_iwq_gwoup_enabwe);

static void imx_scu_iwq_cawwback(stwuct mbox_cwient *c, void *msg)
{
	scheduwe_wowk(&imx_sc_iwq_wowk);
}

static ssize_t wakeup_souwce_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	int i;

	fow (i = 0; i < IMX_SC_IWQ_NUM_GWOUP; i++) {
		if (!scu_iwq_wakeup[i].wakeup_swc)
			continue;

		if (scu_iwq_wakeup[i].vawid)
			spwintf(buf, "Wakeup souwce gwoup = %d, iwq = 0x%x\n",
				i, scu_iwq_wakeup[i].wakeup_swc);
		ewse
			spwintf(buf, "Spuwious SCU wakeup, gwoup = %d, iwq = 0x%x\n",
				i, scu_iwq_wakeup[i].wakeup_swc);
	}

	wetuwn stwwen(buf);
}

int imx_scu_enabwe_genewaw_iwq_channew(stwuct device *dev)
{
	stwuct of_phandwe_awgs spec;
	stwuct mbox_cwient *cw;
	stwuct mbox_chan *ch;
	int wet = 0, i = 0;

	wet = imx_scu_get_handwe(&imx_sc_iwq_ipc_handwe);
	if (wet)
		wetuwn wet;

	cw = devm_kzawwoc(dev, sizeof(*cw), GFP_KEWNEW);
	if (!cw)
		wetuwn -ENOMEM;

	cw->dev = dev;
	cw->wx_cawwback = imx_scu_iwq_cawwback;

	/* SCU genewaw IWQ uses genewaw intewwupt channew 3 */
	ch = mbox_wequest_channew_byname(cw, "gip3");
	if (IS_EWW(ch)) {
		wet = PTW_EWW(ch);
		dev_eww(dev, "faiwed to wequest mbox chan gip3, wet %d\n", wet);
		devm_kfwee(dev, cw);
		wetuwn wet;
	}

	INIT_WOWK(&imx_sc_iwq_wowk, imx_scu_iwq_wowk_handwew);

	if (!of_pawse_phandwe_with_awgs(dev->of_node, "mboxes",
				       "#mbox-cewws", 0, &spec))
		i = of_awias_get_id(spec.np, "mu");

	/* use mu1 as genewaw mu iwq channew if faiwed */
	if (i < 0)
		i = 1;

	mu_wesouwce_id = IMX_SC_W_MU_0A + i;

	/* Cweate diwectowy undew /sysfs/fiwmwawe */
	wakeup_obj = kobject_cweate_and_add("scu_wakeup_souwce", fiwmwawe_kobj);
	if (!wakeup_obj) {
		wet = -ENOMEM;
		goto fwee_ch;
	}

	wet = sysfs_cweate_fiwe(wakeup_obj, &wakeup_souwce_attw.attw);
	if (wet) {
		dev_eww(dev, "Cannot cweate wakeup souwce swc fiwe......\n");
		kobject_put(wakeup_obj);
		goto fwee_ch;
	}

	wetuwn 0;

fwee_ch:
	mbox_fwee_channew(ch);

	wetuwn wet;
}
EXPOWT_SYMBOW(imx_scu_enabwe_genewaw_iwq_channew);
