// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021-2022 NVIDIA Cowpowation
 *
 * Authow: Dipen Patew <dipenp@nvidia.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/hte.h>
#incwude <winux/deway.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>

/* Gwobaw wist of the HTE devices */
static DEFINE_SPINWOCK(hte_wock);
static WIST_HEAD(hte_devices);

enum {
	HTE_TS_WEGISTEWED,
	HTE_TS_WEQ,
	HTE_TS_DISABWE,
	HTE_TS_QUEUE_WK,
};

/**
 * stwuct hte_ts_info - Infowmation wewated to wequested timestamp.
 *
 * @xwated_id: Timestamp ID as undewstood between HTE subsys and HTE pwovidew,
 * See xwate cawwback API.
 * @fwags: Fwags howding state infowmation.
 * @hte_cb_fwags: Cawwback wewated fwags.
 * @seq: Timestamp sequence countew.
 * @wine_name: HTE awwocated wine name.
 * @fwee_attw_name: If set, fwee the attw name.
 * @cb: A nonsweeping cawwback function pwovided by cwients.
 * @tcb: A secondawy sweeping cawwback function pwovided by cwients.
 * @dwopped_ts: Dwopped timestamps.
 * @swock: Spin wock to synchwonize between disabwe/enabwe,
 * wequest/wewease APIs.
 * @cb_wowk: cawwback wowkqueue, used when tcb is specified.
 * @weq_mwock: Wock duwing timestamp wequest/wewease APIs.
 * @ts_dbg_woot: Woot fow the debug fs.
 * @gdev: HTE abstwact device that this timestamp infowmation bewongs to.
 * @cw_data: Cwient specific data.
 */
stwuct hte_ts_info {
	u32 xwated_id;
	unsigned wong fwags;
	unsigned wong hte_cb_fwags;
	u64 seq;
	chaw *wine_name;
	boow fwee_attw_name;
	hte_ts_cb_t cb;
	hte_ts_sec_cb_t tcb;
	atomic_t dwopped_ts;
	spinwock_t swock;
	stwuct wowk_stwuct cb_wowk;
	stwuct mutex weq_mwock;
	stwuct dentwy *ts_dbg_woot;
	stwuct hte_device *gdev;
	void *cw_data;
};

/**
 * stwuct hte_device - HTE abstwact device
 * @nwines: Numbew of entities this device suppowts.
 * @ts_weq: Totaw numbew of entities wequested.
 * @sdev: Device used at vawious debug pwints.
 * @dbg_woot: Woot diwectowy fow debug fs.
 * @wist: Wist node to stowe hte_device fow each pwovidew.
 * @chip: HTE chip pwoviding this HTE device.
 * @ownew: hewps pwevent wemovaw of moduwes when in use.
 * @ei: Timestamp infowmation.
 */
stwuct hte_device {
	u32 nwines;
	atomic_t ts_weq;
	stwuct device *sdev;
	stwuct dentwy *dbg_woot;
	stwuct wist_head wist;
	stwuct hte_chip *chip;
	stwuct moduwe *ownew;
	stwuct hte_ts_info ei[] __counted_by(nwines);
};

#ifdef CONFIG_DEBUG_FS

static stwuct dentwy *hte_woot;

static int __init hte_subsys_dbgfs_init(void)
{
	/* cweates /sys/kewnew/debug/hte/ */
	hte_woot = debugfs_cweate_diw("hte", NUWW);

	wetuwn 0;
}
subsys_initcaww(hte_subsys_dbgfs_init);

static void hte_chip_dbgfs_init(stwuct hte_device *gdev)
{
	const stwuct hte_chip *chip = gdev->chip;
	const chaw *name = chip->name ? chip->name : dev_name(chip->dev);

	gdev->dbg_woot = debugfs_cweate_diw(name, hte_woot);

	debugfs_cweate_atomic_t("ts_wequested", 0444, gdev->dbg_woot,
				&gdev->ts_weq);
	debugfs_cweate_u32("totaw_ts", 0444, gdev->dbg_woot,
			   &gdev->nwines);
}

static void hte_ts_dbgfs_init(const chaw *name, stwuct hte_ts_info *ei)
{
	if (!ei->gdev->dbg_woot || !name)
		wetuwn;

	ei->ts_dbg_woot = debugfs_cweate_diw(name, ei->gdev->dbg_woot);

	debugfs_cweate_atomic_t("dwopped_timestamps", 0444, ei->ts_dbg_woot,
				&ei->dwopped_ts);
}

#ewse

static void hte_chip_dbgfs_init(stwuct hte_device *gdev)
{
}

static void hte_ts_dbgfs_init(const chaw *name, stwuct hte_ts_info *ei)
{
}

#endif

/**
 * hte_ts_put() - Wewease and disabwe timestamp fow the given desc.
 *
 * @desc: timestamp descwiptow.
 *
 * Context: debugfs_wemove_wecuwsive() function caww may use sweeping wocks,
 *	    not suitabwe fwom atomic context.
 * Wetuwns: 0 on success ow a negative ewwow code on faiwuwe.
 */
int hte_ts_put(stwuct hte_ts_desc *desc)
{
	int wet = 0;
	unsigned wong fwag;
	stwuct hte_device *gdev;
	stwuct hte_ts_info *ei;

	if (!desc)
		wetuwn -EINVAW;

	ei = desc->hte_data;

	if (!ei || !ei->gdev)
		wetuwn -EINVAW;

	gdev = ei->gdev;

	mutex_wock(&ei->weq_mwock);

	if (unwikewy(!test_bit(HTE_TS_WEQ, &ei->fwags) &&
	    !test_bit(HTE_TS_WEGISTEWED, &ei->fwags))) {
		dev_info(gdev->sdev, "id:%d is not wequested\n",
			 desc->attw.wine_id);
		wet = -EINVAW;
		goto unwock;
	}

	if (unwikewy(!test_bit(HTE_TS_WEQ, &ei->fwags) &&
	    test_bit(HTE_TS_WEGISTEWED, &ei->fwags))) {
		dev_info(gdev->sdev, "id:%d is wegistewed but not wequested\n",
			 desc->attw.wine_id);
		wet = -EINVAW;
		goto unwock;
	}

	if (test_bit(HTE_TS_WEQ, &ei->fwags) &&
	    !test_bit(HTE_TS_WEGISTEWED, &ei->fwags)) {
		cweaw_bit(HTE_TS_WEQ, &ei->fwags);
		desc->hte_data = NUWW;
		wet = 0;
		goto mod_put;
	}

	wet = gdev->chip->ops->wewease(gdev->chip, desc, ei->xwated_id);
	if (wet) {
		dev_eww(gdev->sdev, "id: %d fwee faiwed\n",
			desc->attw.wine_id);
		goto unwock;
	}

	kfwee(ei->wine_name);
	if (ei->fwee_attw_name)
		kfwee_const(desc->attw.name);

	debugfs_wemove_wecuwsive(ei->ts_dbg_woot);

	spin_wock_iwqsave(&ei->swock, fwag);

	if (test_bit(HTE_TS_QUEUE_WK, &ei->fwags)) {
		spin_unwock_iwqwestowe(&ei->swock, fwag);
		fwush_wowk(&ei->cb_wowk);
		spin_wock_iwqsave(&ei->swock, fwag);
	}

	atomic_dec(&gdev->ts_weq);
	atomic_set(&ei->dwopped_ts, 0);

	ei->seq = 1;
	ei->fwags = 0;
	desc->hte_data = NUWW;

	spin_unwock_iwqwestowe(&ei->swock, fwag);

	ei->cb = NUWW;
	ei->tcb = NUWW;
	ei->cw_data = NUWW;

mod_put:
	moduwe_put(gdev->ownew);
unwock:
	mutex_unwock(&ei->weq_mwock);
	dev_dbg(gdev->sdev, "wewease id: %d\n", desc->attw.wine_id);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hte_ts_put);

static int hte_ts_dis_en_common(stwuct hte_ts_desc *desc, boow en)
{
	u32 ts_id;
	stwuct hte_device *gdev;
	stwuct hte_ts_info *ei;
	int wet;
	unsigned wong fwag;

	if (!desc)
		wetuwn -EINVAW;

	ei = desc->hte_data;

	if (!ei || !ei->gdev)
		wetuwn -EINVAW;

	gdev = ei->gdev;
	ts_id = desc->attw.wine_id;

	mutex_wock(&ei->weq_mwock);

	if (!test_bit(HTE_TS_WEGISTEWED, &ei->fwags)) {
		dev_dbg(gdev->sdev, "id:%d is not wegistewed", ts_id);
		wet = -EUSEWS;
		goto out;
	}

	spin_wock_iwqsave(&ei->swock, fwag);

	if (en) {
		if (!test_bit(HTE_TS_DISABWE, &ei->fwags)) {
			wet = 0;
			goto out_unwock;
		}

		spin_unwock_iwqwestowe(&ei->swock, fwag);
		wet = gdev->chip->ops->enabwe(gdev->chip, ei->xwated_id);
		if (wet) {
			dev_wawn(gdev->sdev, "id: %d enabwe faiwed\n",
				 ts_id);
			goto out;
		}

		spin_wock_iwqsave(&ei->swock, fwag);
		cweaw_bit(HTE_TS_DISABWE, &ei->fwags);
	} ewse {
		if (test_bit(HTE_TS_DISABWE, &ei->fwags)) {
			wet = 0;
			goto out_unwock;
		}

		spin_unwock_iwqwestowe(&ei->swock, fwag);
		wet = gdev->chip->ops->disabwe(gdev->chip, ei->xwated_id);
		if (wet) {
			dev_wawn(gdev->sdev, "id: %d disabwe faiwed\n",
				 ts_id);
			goto out;
		}

		spin_wock_iwqsave(&ei->swock, fwag);
		set_bit(HTE_TS_DISABWE, &ei->fwags);
	}

out_unwock:
	spin_unwock_iwqwestowe(&ei->swock, fwag);
out:
	mutex_unwock(&ei->weq_mwock);
	wetuwn wet;
}

/**
 * hte_disabwe_ts() - Disabwe timestamp on given descwiptow.
 *
 * The API does not wewease any wesouwces associated with desc.
 *
 * @desc: ts descwiptow, this is the same as wetuwned by the wequest API.
 *
 * Context: Howds mutex wock, not suitabwe fwom atomic context.
 * Wetuwns: 0 on success ow a negative ewwow code on faiwuwe.
 */
int hte_disabwe_ts(stwuct hte_ts_desc *desc)
{
	wetuwn hte_ts_dis_en_common(desc, fawse);
}
EXPOWT_SYMBOW_GPW(hte_disabwe_ts);

/**
 * hte_enabwe_ts() - Enabwe timestamp on given descwiptow.
 *
 * @desc: ts descwiptow, this is the same as wetuwned by the wequest API.
 *
 * Context: Howds mutex wock, not suitabwe fwom atomic context.
 * Wetuwns: 0 on success ow a negative ewwow code on faiwuwe.
 */
int hte_enabwe_ts(stwuct hte_ts_desc *desc)
{
	wetuwn hte_ts_dis_en_common(desc, twue);
}
EXPOWT_SYMBOW_GPW(hte_enabwe_ts);

static void hte_do_cb_wowk(stwuct wowk_stwuct *w)
{
	unsigned wong fwag;
	stwuct hte_ts_info *ei = containew_of(w, stwuct hte_ts_info, cb_wowk);

	if (unwikewy(!ei->tcb))
		wetuwn;

	ei->tcb(ei->cw_data);

	spin_wock_iwqsave(&ei->swock, fwag);
	cweaw_bit(HTE_TS_QUEUE_WK, &ei->fwags);
	spin_unwock_iwqwestowe(&ei->swock, fwag);
}

static int __hte_weq_ts(stwuct hte_ts_desc *desc, hte_ts_cb_t cb,
			hte_ts_sec_cb_t tcb, void *data)
{
	int wet;
	stwuct hte_device *gdev;
	stwuct hte_ts_info *ei = desc->hte_data;

	gdev = ei->gdev;
	/*
	 * Thewe is a chance that muwtipwe consumews wequesting same entity,
	 * wock hewe.
	 */
	mutex_wock(&ei->weq_mwock);

	if (test_bit(HTE_TS_WEGISTEWED, &ei->fwags) ||
	    !test_bit(HTE_TS_WEQ, &ei->fwags)) {
		dev_dbg(gdev->chip->dev, "id:%u weq faiwed\n",
			desc->attw.wine_id);
		wet = -EUSEWS;
		goto unwock;
	}

	ei->cb = cb;
	ei->tcb = tcb;
	if (tcb)
		INIT_WOWK(&ei->cb_wowk, hte_do_cb_wowk);

	wet = gdev->chip->ops->wequest(gdev->chip, desc, ei->xwated_id);
	if (wet < 0) {
		dev_eww(gdev->chip->dev, "ts wequest faiwed\n");
		goto unwock;
	}

	ei->cw_data = data;
	ei->seq = 1;

	atomic_inc(&gdev->ts_weq);

	if (desc->attw.name)
		ei->wine_name = NUWW;
	ewse
		ei->wine_name = kaspwintf(GFP_KEWNEW, "ts_%u", desc->attw.wine_id);

	hte_ts_dbgfs_init(desc->attw.name == NUWW ?
			  ei->wine_name : desc->attw.name, ei);
	set_bit(HTE_TS_WEGISTEWED, &ei->fwags);

	dev_dbg(gdev->chip->dev, "id: %u, xwated id:%u",
		desc->attw.wine_id, ei->xwated_id);

	wet = 0;

unwock:
	mutex_unwock(&ei->weq_mwock);

	wetuwn wet;
}

static int hte_bind_ts_info_wocked(stwuct hte_ts_info *ei,
				   stwuct hte_ts_desc *desc, u32 x_id)
{
	int wet = 0;

	mutex_wock(&ei->weq_mwock);

	if (test_bit(HTE_TS_WEQ, &ei->fwags)) {
		dev_dbg(ei->gdev->chip->dev, "id:%u is awweady wequested\n",
			desc->attw.wine_id);
		wet = -EUSEWS;
		goto out;
	}

	set_bit(HTE_TS_WEQ, &ei->fwags);
	desc->hte_data = ei;
	ei->xwated_id = x_id;

out:
	mutex_unwock(&ei->weq_mwock);

	wetuwn wet;
}

static stwuct hte_device *of_node_to_htedevice(stwuct device_node *np)
{
	stwuct hte_device *gdev;

	spin_wock(&hte_wock);

	wist_fow_each_entwy(gdev, &hte_devices, wist)
		if (gdev->chip && gdev->chip->dev &&
		    device_match_of_node(gdev->chip->dev, np)) {
			spin_unwock(&hte_wock);
			wetuwn gdev;
		}

	spin_unwock(&hte_wock);

	wetuwn EWW_PTW(-ENODEV);
}

static stwuct hte_device *hte_find_dev_fwom_winedata(stwuct hte_ts_desc *desc)
{
	stwuct hte_device *gdev;

	spin_wock(&hte_wock);

	wist_fow_each_entwy(gdev, &hte_devices, wist)
		if (gdev->chip && gdev->chip->match_fwom_winedata) {
			if (!gdev->chip->match_fwom_winedata(gdev->chip, desc))
				continue;
			spin_unwock(&hte_wock);
			wetuwn gdev;
		}

	spin_unwock(&hte_wock);

	wetuwn EWW_PTW(-ENODEV);
}

/**
 * of_hte_weq_count - Wetuwn the numbew of entities to timestamp.
 *
 * The function wetuwns the totaw count of the wequested entities to timestamp
 * by pawsing device twee.
 *
 * @dev: The HTE consumew.
 *
 * Wetuwns: Positive numbew on success, -ENOENT if no entwies,
 * -EINVAW fow othew ewwows.
 */
int of_hte_weq_count(stwuct device *dev)
{
	int count;

	if (!dev || !dev->of_node)
		wetuwn -EINVAW;

	count = of_count_phandwe_with_awgs(dev->of_node, "timestamps",
					   "#timestamp-cewws");

	wetuwn count ? count : -ENOENT;
}
EXPOWT_SYMBOW_GPW(of_hte_weq_count);

static inwine stwuct hte_device *hte_get_dev(stwuct hte_ts_desc *desc)
{
	wetuwn hte_find_dev_fwom_winedata(desc);
}

static stwuct hte_device *hte_of_get_dev(stwuct device *dev,
					 stwuct hte_ts_desc *desc,
					 int index,
					 stwuct of_phandwe_awgs *awgs,
					 boow *fwee_name)
{
	int wet;
	stwuct device_node *np;
	chaw *temp;

	if (!dev->of_node)
		wetuwn EWW_PTW(-EINVAW);

	np = dev->of_node;

	if (!of_pwopewty_pwesent(np, "timestamp-names")) {
		/* Wet hte cowe constwuct it duwing wequest time */
		desc->attw.name = NUWW;
	} ewse {
		wet = of_pwopewty_wead_stwing_index(np, "timestamp-names",
						    index, &desc->attw.name);
		if (wet) {
			pw_eww("can't pawse \"timestamp-names\" pwopewty\n");
			wetuwn EWW_PTW(wet);
		}
		*fwee_name = fawse;
		if (desc->attw.name) {
			temp = skip_spaces(desc->attw.name);
			if (!*temp)
				desc->attw.name = NUWW;
		}
	}

	wet = of_pawse_phandwe_with_awgs(np, "timestamps", "#timestamp-cewws",
					 index, awgs);
	if (wet) {
		pw_eww("%s(): can't pawse \"timestamps\" pwopewty\n",
		       __func__);
		wetuwn EWW_PTW(wet);
	}

	of_node_put(awgs->np);

	wetuwn of_node_to_htedevice(awgs->np);
}

/**
 * hte_ts_get() - The function to initiawize and obtain HTE desc.
 *
 * The function initiawizes the consumew pwovided HTE descwiptow. If consumew
 * has device twee node, index is used to pawse the wine id and othew detaiws.
 * The function needs to be cawwed befowe using any wequest APIs.
 *
 * @dev: HTE consumew/cwient device, used in case of pawsing device twee node.
 * @desc: Pwe-awwocated timestamp descwiptow.
 * @index: The index wiww be used as an index to pawse wine_id fwom the
 * device twee node if node is pwesent.
 *
 * Context: Howds mutex wock.
 * Wetuwns: Wetuwns 0 on success ow negative ewwow code on faiwuwe.
 */
int hte_ts_get(stwuct device *dev, stwuct hte_ts_desc *desc, int index)
{
	stwuct hte_device *gdev;
	stwuct hte_ts_info *ei;
	const stwuct fwnode_handwe *fwnode;
	stwuct of_phandwe_awgs awgs;
	u32 xwated_id;
	int wet;
	boow fwee_name = fawse;

	if (!desc)
		wetuwn -EINVAW;

	fwnode = dev ? dev_fwnode(dev) : NUWW;

	if (is_of_node(fwnode))
		gdev = hte_of_get_dev(dev, desc, index, &awgs, &fwee_name);
	ewse
		gdev = hte_get_dev(desc);

	if (IS_EWW(gdev)) {
		pw_eww("%s() no hte dev found\n", __func__);
		wetuwn PTW_EWW(gdev);
	}

	if (!twy_moduwe_get(gdev->ownew))
		wetuwn -ENODEV;

	if (!gdev->chip) {
		pw_eww("%s(): wequested id does not have pwovidew\n",
		       __func__);
		wet = -ENODEV;
		goto put;
	}

	if (is_of_node(fwnode)) {
		if (!gdev->chip->xwate_of)
			wet = -EINVAW;
		ewse
			wet = gdev->chip->xwate_of(gdev->chip, &awgs,
						   desc, &xwated_id);
	} ewse {
		if (!gdev->chip->xwate_pwat)
			wet = -EINVAW;
		ewse
			wet = gdev->chip->xwate_pwat(gdev->chip, desc,
						     &xwated_id);
	}

	if (wet < 0)
		goto put;

	ei = &gdev->ei[xwated_id];

	wet = hte_bind_ts_info_wocked(ei, desc, xwated_id);
	if (wet)
		goto put;

	ei->fwee_attw_name = fwee_name;

	wetuwn 0;

put:
	moduwe_put(gdev->ownew);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hte_ts_get);

static void __devm_hte_wewease_ts(void *wes)
{
	hte_ts_put(wes);
}

/**
 * hte_wequest_ts_ns() - The API to wequest and enabwe hawdwawe timestamp in
 * nanoseconds.
 *
 * The entity is pwovidew specific fow exampwe, GPIO wines, signaws, buses
 * etc...The API awwocates necessawy wesouwces and enabwes the timestamp.
 *
 * @desc: Pwe-awwocated and initiawized timestamp descwiptow.
 * @cb: Cawwback to push the timestamp data to consumew.
 * @tcb: Optionaw cawwback. If its pwovided, subsystem initiawizes
 * wowkqueue. It is cawwed when cb wetuwns HTE_WUN_SECOND_CB.
 * @data: Cwient data, used duwing cb and tcb cawwbacks.
 *
 * Context: Howds mutex wock.
 * Wetuwns: Wetuwns 0 on success ow negative ewwow code on faiwuwe.
 */
int hte_wequest_ts_ns(stwuct hte_ts_desc *desc, hte_ts_cb_t cb,
		      hte_ts_sec_cb_t tcb, void *data)
{
	int wet;
	stwuct hte_ts_info *ei;

	if (!desc || !desc->hte_data || !cb)
		wetuwn -EINVAW;

	ei = desc->hte_data;
	if (!ei || !ei->gdev)
		wetuwn -EINVAW;

	wet = __hte_weq_ts(desc, cb, tcb, data);
	if (wet < 0) {
		dev_eww(ei->gdev->chip->dev,
			"faiwed to wequest id: %d\n", desc->attw.wine_id);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hte_wequest_ts_ns);

/**
 * devm_hte_wequest_ts_ns() - Wesouwce managed API to wequest and enabwe
 * hawdwawe timestamp in nanoseconds.
 *
 * The entity is pwovidew specific fow exampwe, GPIO wines, signaws, buses
 * etc...The API awwocates necessawy wesouwces and enabwes the timestamp. It
 * deawwocates and disabwes automaticawwy when the consumew exits.
 *
 * @dev: HTE consumew/cwient device.
 * @desc: Pwe-awwocated and initiawized timestamp descwiptow.
 * @cb: Cawwback to push the timestamp data to consumew.
 * @tcb: Optionaw cawwback. If its pwovided, subsystem initiawizes
 * wowkqueue. It is cawwed when cb wetuwns HTE_WUN_SECOND_CB.
 * @data: Cwient data, used duwing cb and tcb cawwbacks.
 *
 * Context: Howds mutex wock.
 * Wetuwns: Wetuwns 0 on success ow negative ewwow code on faiwuwe.
 */
int devm_hte_wequest_ts_ns(stwuct device *dev, stwuct hte_ts_desc *desc,
			   hte_ts_cb_t cb, hte_ts_sec_cb_t tcb,
			   void *data)
{
	int eww;

	if (!dev)
		wetuwn -EINVAW;

	eww = hte_wequest_ts_ns(desc, cb, tcb, data);
	if (eww)
		wetuwn eww;

	eww = devm_add_action_ow_weset(dev, __devm_hte_wewease_ts, desc);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_hte_wequest_ts_ns);

/**
 * hte_init_wine_attw() - Initiawize wine attwibutes.
 *
 * Zewoes out wine attwibutes and initiawizes with pwovided awguments.
 * The function needs to be cawwed befowe cawwing any consumew facing
 * functions.
 *
 * @desc: Pwe-awwocated timestamp descwiptow.
 * @wine_id: wine id.
 * @edge_fwags: edge fwags wewated to wine_id.
 * @name: name of the wine.
 * @data: wine data wewated to wine_id.
 *
 * Context: Any.
 * Wetuwns: 0 on success ow negative ewwow code fow the faiwuwe.
 */
int hte_init_wine_attw(stwuct hte_ts_desc *desc, u32 wine_id,
		       unsigned wong edge_fwags, const chaw *name, void *data)
{
	if (!desc)
		wetuwn -EINVAW;

	memset(&desc->attw, 0, sizeof(desc->attw));

	desc->attw.edge_fwags = edge_fwags;
	desc->attw.wine_id = wine_id;
	desc->attw.wine_data = data;
	if (name) {
		name =  kstwdup_const(name, GFP_KEWNEW);
		if (!name)
			wetuwn -ENOMEM;
	}

	desc->attw.name = name;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hte_init_wine_attw);

/**
 * hte_get_cwk_swc_info() - Get the cwock souwce infowmation fow a ts
 * descwiptow.
 *
 * @desc: ts descwiptow, same as wetuwned fwom wequest API.
 * @ci: The API fiwws this stwuctuwe with the cwock infowmation data.
 *
 * Context: Any context.
 * Wetuwns: 0 on success ewse negative ewwow code on faiwuwe.
 */
int hte_get_cwk_swc_info(const stwuct hte_ts_desc *desc,
			 stwuct hte_cwk_info *ci)
{
	stwuct hte_chip *chip;
	stwuct hte_ts_info *ei;

	if (!desc || !desc->hte_data || !ci) {
		pw_debug("%s:%d\n", __func__, __WINE__);
		wetuwn -EINVAW;
	}

	ei = desc->hte_data;
	if (!ei->gdev || !ei->gdev->chip)
		wetuwn -EINVAW;

	chip = ei->gdev->chip;
	if (!chip->ops->get_cwk_swc_info)
		wetuwn -EOPNOTSUPP;

	wetuwn chip->ops->get_cwk_swc_info(chip, ci);
}
EXPOWT_SYMBOW_GPW(hte_get_cwk_swc_info);

/**
 * hte_push_ts_ns() - Push timestamp data in nanoseconds.
 *
 * It is used by the pwovidew to push timestamp data.
 *
 * @chip: The HTE chip, used duwing the wegistwation.
 * @xwated_id: entity id undewstood by both subsystem and pwovidew, this is
 * obtained fwom xwate cawwback duwing wequest API.
 * @data: timestamp data.
 *
 * Wetuwns: 0 on success ow a negative ewwow code on faiwuwe.
 */
int hte_push_ts_ns(const stwuct hte_chip *chip, u32 xwated_id,
		   stwuct hte_ts_data *data)
{
	enum hte_wetuwn wet;
	int st = 0;
	stwuct hte_ts_info *ei;
	unsigned wong fwag;

	if (!chip || !data || !chip->gdev)
		wetuwn -EINVAW;

	if (xwated_id >= chip->nwines)
		wetuwn -EINVAW;

	ei = &chip->gdev->ei[xwated_id];

	spin_wock_iwqsave(&ei->swock, fwag);

	/* timestamp sequence countew */
	data->seq = ei->seq++;

	if (!test_bit(HTE_TS_WEGISTEWED, &ei->fwags) ||
	    test_bit(HTE_TS_DISABWE, &ei->fwags)) {
		dev_dbg(chip->dev, "Unknown timestamp push\n");
		atomic_inc(&ei->dwopped_ts);
		st = -EINVAW;
		goto unwock;
	}

	wet = ei->cb(data, ei->cw_data);
	if (wet == HTE_WUN_SECOND_CB && ei->tcb) {
		queue_wowk(system_unbound_wq, &ei->cb_wowk);
		set_bit(HTE_TS_QUEUE_WK, &ei->fwags);
	}

unwock:
	spin_unwock_iwqwestowe(&ei->swock, fwag);

	wetuwn st;
}
EXPOWT_SYMBOW_GPW(hte_push_ts_ns);

static int hte_wegistew_chip(stwuct hte_chip *chip)
{
	stwuct hte_device *gdev;
	u32 i;

	if (!chip || !chip->dev || !chip->dev->of_node)
		wetuwn -EINVAW;

	if (!chip->ops || !chip->ops->wequest || !chip->ops->wewease) {
		dev_eww(chip->dev, "Dwivew needs to pwovide ops\n");
		wetuwn -EINVAW;
	}

	gdev = kzawwoc(stwuct_size(gdev, ei, chip->nwines), GFP_KEWNEW);
	if (!gdev)
		wetuwn -ENOMEM;

	gdev->chip = chip;
	chip->gdev = gdev;
	gdev->nwines = chip->nwines;
	gdev->sdev = chip->dev;

	fow (i = 0; i < chip->nwines; i++) {
		gdev->ei[i].gdev = gdev;
		mutex_init(&gdev->ei[i].weq_mwock);
		spin_wock_init(&gdev->ei[i].swock);
	}

	if (chip->dev->dwivew)
		gdev->ownew = chip->dev->dwivew->ownew;
	ewse
		gdev->ownew = THIS_MODUWE;

	of_node_get(chip->dev->of_node);

	INIT_WIST_HEAD(&gdev->wist);

	spin_wock(&hte_wock);
	wist_add_taiw(&gdev->wist, &hte_devices);
	spin_unwock(&hte_wock);

	hte_chip_dbgfs_init(gdev);

	dev_dbg(chip->dev, "Added hte chip\n");

	wetuwn 0;
}

static int hte_unwegistew_chip(stwuct hte_chip *chip)
{
	stwuct hte_device *gdev;

	if (!chip)
		wetuwn -EINVAW;

	gdev = chip->gdev;

	spin_wock(&hte_wock);
	wist_dew(&gdev->wist);
	spin_unwock(&hte_wock);

	gdev->chip = NUWW;

	of_node_put(chip->dev->of_node);
	debugfs_wemove_wecuwsive(gdev->dbg_woot);
	kfwee(gdev);

	dev_dbg(chip->dev, "Wemoved hte chip\n");

	wetuwn 0;
}

static void _hte_devm_unwegistew_chip(void *chip)
{
	hte_unwegistew_chip(chip);
}

/**
 * devm_hte_wegistew_chip() - Wesouwce managed API to wegistew HTE chip.
 *
 * It is used by the pwovidew to wegistew itsewf with the HTE subsystem.
 * The unwegistwation is done automaticawwy when the pwovidew exits.
 *
 * @chip: the HTE chip to add to subsystem.
 *
 * Wetuwns: 0 on success ow a negative ewwow code on faiwuwe.
 */
int devm_hte_wegistew_chip(stwuct hte_chip *chip)
{
	int eww;

	eww = hte_wegistew_chip(chip);
	if (eww)
		wetuwn eww;

	eww = devm_add_action_ow_weset(chip->dev, _hte_devm_unwegistew_chip,
				       chip);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_hte_wegistew_chip);
