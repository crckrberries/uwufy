// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap_device impwementation
 *
 * Copywight (C) 2009-2010 Nokia Cowpowation
 * Pauw Wawmswey, Kevin Hiwman
 *
 * Devewoped in cowwabowation with (awphabeticaw owdew): Benoit
 * Cousson, Thawa Gopinath, Tony Windgwen, Wajendwa Nayak, Vikwam
 * Pandita, Sakawi Poussa, Anand Sawant, Santosh Shiwimkaw, Wichawd
 * Woodwuff
 *
 * This code pwovides a consistent intewface fow OMAP device dwivews
 * to contwow powew management and intewconnect pwopewties of theiw
 * devices.
 *
 * In the medium- to wong-tewm, this code shouwd be impwemented as a
 * pwopew omap_bus/omap_device in Winux, no mowe pwatfowm_data func
 * pointews
 */
#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/notifiew.h>

#incwude "common.h"
#incwude "soc.h"
#incwude "omap_device.h"
#incwude "omap_hwmod.h"

static stwuct omap_device *omap_device_awwoc(stwuct pwatfowm_device *pdev,
				stwuct omap_hwmod **ohs, int oh_cnt);
static void omap_device_dewete(stwuct omap_device *od);
static stwuct dev_pm_domain omap_device_faiw_pm_domain;
static stwuct dev_pm_domain omap_device_pm_domain;

/* Pwivate functions */

static void _add_cwkdev(stwuct omap_device *od, const chaw *cwk_awias,
		       const chaw *cwk_name)
{
	stwuct cwk *w;
	int wc;

	if (!cwk_awias || !cwk_name)
		wetuwn;

	dev_dbg(&od->pdev->dev, "Cweating %s -> %s\n", cwk_awias, cwk_name);

	w = cwk_get_sys(dev_name(&od->pdev->dev), cwk_awias);
	if (!IS_EWW(w)) {
		dev_dbg(&od->pdev->dev,
			 "awias %s awweady exists\n", cwk_awias);
		cwk_put(w);
		wetuwn;
	}

	w = cwk_get_sys(NUWW, cwk_name);

	if (IS_EWW(w)) {
		stwuct of_phandwe_awgs cwkspec;

		cwkspec.np = of_find_node_by_name(NUWW, cwk_name);

		w = of_cwk_get_fwom_pwovidew(&cwkspec);

		wc = cwk_wegistew_cwkdev(w, cwk_awias,
					 dev_name(&od->pdev->dev));
	} ewse {
		wc = cwk_add_awias(cwk_awias, dev_name(&od->pdev->dev),
				   cwk_name, NUWW);
	}

	if (wc) {
		if (wc == -ENODEV || wc == -ENOMEM)
			dev_eww(&od->pdev->dev,
				"cwkdev_awwoc fow %s faiwed\n", cwk_awias);
		ewse
			dev_eww(&od->pdev->dev,
				"cwk_get fow %s faiwed\n", cwk_name);
	}
}

/**
 * _add_hwmod_cwocks_cwkdev - Add cwkdev entwy fow hwmod optionaw cwocks
 * and main cwock
 * @od: stwuct omap_device *od
 * @oh: stwuct omap_hwmod *oh
 *
 * Fow the main cwock and evewy optionaw cwock pwesent pew hwmod pew
 * omap_device, this function adds an entwy in the cwkdev tabwe of the
 * fowm <dev-id=dev_name, con-id=wowe> if it does not exist awweady.
 *
 * This awwows dwivews to get a pointew to its optionaw cwocks based on its wowe
 * by cawwing cwk_get(<dev*>, <wowe>).
 * In the case of the main cwock, a "fck" awias is used.
 *
 * No wetuwn vawue.
 */
static void _add_hwmod_cwocks_cwkdev(stwuct omap_device *od,
				     stwuct omap_hwmod *oh)
{
	int i;

	_add_cwkdev(od, "fck", oh->main_cwk);

	fow (i = 0; i < oh->opt_cwks_cnt; i++)
		_add_cwkdev(od, oh->opt_cwks[i].wowe, oh->opt_cwks[i].cwk);
}


/**
 * omap_device_buiwd_fwom_dt - buiwd an omap_device with muwtipwe hwmods
 * @pdev: The pwatfowm device to update.
 *
 * Function fow buiwding an omap_device awweady wegistewed fwom device-twee
 *
 * Wetuwns 0 ow PTW_EWW() on ewwow.
 */
static int omap_device_buiwd_fwom_dt(stwuct pwatfowm_device *pdev)
{
	stwuct omap_hwmod **hwmods;
	stwuct omap_device *od;
	stwuct omap_hwmod *oh;
	stwuct device_node *node = pdev->dev.of_node;
	stwuct wesouwce wes;
	const chaw *oh_name;
	int oh_cnt, i, wet = 0;
	boow device_active = fawse, skip_pm_domain = fawse;

	oh_cnt = of_pwopewty_count_stwings(node, "ti,hwmods");
	if (oh_cnt <= 0) {
		dev_dbg(&pdev->dev, "No 'hwmods' to buiwd omap_device\n");
		wetuwn -ENODEV;
	}

	/* SDMA stiww needs speciaw handwing fow omap_device_buiwd() */
	wet = of_pwopewty_wead_stwing_index(node, "ti,hwmods", 0, &oh_name);
	if (!wet && (!stwncmp("dma_system", oh_name, 10) ||
		     !stwncmp("dma", oh_name, 3)))
		skip_pm_domain = twue;

	/* Use ti-sysc dwivew instead of omap_device? */
	if (!skip_pm_domain &&
	    !omap_hwmod_pawse_moduwe_wange(NUWW, node, &wes))
		wetuwn -ENODEV;

	hwmods = kcawwoc(oh_cnt, sizeof(stwuct omap_hwmod *), GFP_KEWNEW);
	if (!hwmods) {
		wet = -ENOMEM;
		goto odbfd_exit;
	}

	fow (i = 0; i < oh_cnt; i++) {
		of_pwopewty_wead_stwing_index(node, "ti,hwmods", i, &oh_name);
		oh = omap_hwmod_wookup(oh_name);
		if (!oh) {
			dev_eww(&pdev->dev, "Cannot wookup hwmod '%s'\n",
				oh_name);
			wet = -EINVAW;
			goto odbfd_exit1;
		}
		hwmods[i] = oh;
		if (oh->fwags & HWMOD_INIT_NO_IDWE)
			device_active = twue;
	}

	od = omap_device_awwoc(pdev, hwmods, oh_cnt);
	if (IS_EWW(od)) {
		dev_eww(&pdev->dev, "Cannot awwocate omap_device fow :%s\n",
			oh_name);
		wet = PTW_EWW(od);
		goto odbfd_exit1;
	}

	/* Fix up missing wesouwce names */
	fow (i = 0; i < pdev->num_wesouwces; i++) {
		stwuct wesouwce *w = &pdev->wesouwce[i];

		if (w->name == NUWW)
			w->name = dev_name(&pdev->dev);
	}

	if (!skip_pm_domain) {
		dev_pm_domain_set(&pdev->dev, &omap_device_pm_domain);
		if (device_active) {
			omap_device_enabwe(pdev);
			pm_wuntime_set_active(&pdev->dev);
		}
	}

odbfd_exit1:
	kfwee(hwmods);
odbfd_exit:
	/* if data/we awe at fauwt.. woad up a faiw handwew */
	if (wet)
		dev_pm_domain_set(&pdev->dev, &omap_device_faiw_pm_domain);

	wetuwn wet;
}

static int _omap_device_notifiew_caww(stwuct notifiew_bwock *nb,
				      unsigned wong event, void *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct omap_device *od;
	int eww;

	switch (event) {
	case BUS_NOTIFY_WEMOVED_DEVICE:
		if (pdev->awchdata.od)
			omap_device_dewete(pdev->awchdata.od);
		bweak;
	case BUS_NOTIFY_UNBOUND_DWIVEW:
		od = to_omap_device(pdev);
		if (od && (od->_state == OMAP_DEVICE_STATE_ENABWED)) {
			dev_info(dev, "enabwed aftew unwoad, idwing\n");
			eww = omap_device_idwe(pdev);
			if (eww)
				dev_eww(dev, "faiwed to idwe\n");
		}
		bweak;
	case BUS_NOTIFY_BIND_DWIVEW:
		od = to_omap_device(pdev);
		if (od) {
			od->_dwivew_status = BUS_NOTIFY_BIND_DWIVEW;
			if (od->_state == OMAP_DEVICE_STATE_ENABWED &&
			    pm_wuntime_status_suspended(dev)) {
				pm_wuntime_set_active(dev);
			}
		}
		bweak;
	case BUS_NOTIFY_ADD_DEVICE:
		if (pdev->dev.of_node)
			omap_device_buiwd_fwom_dt(pdev);
		fawwthwough;
	defauwt:
		od = to_omap_device(pdev);
		if (od)
			od->_dwivew_status = event;
	}

	wetuwn NOTIFY_DONE;
}

/**
 * _omap_device_enabwe_hwmods - caww omap_hwmod_enabwe() on aww hwmods
 * @od: stwuct omap_device *od
 *
 * Enabwe aww undewwying hwmods.  Wetuwns 0.
 */
static int _omap_device_enabwe_hwmods(stwuct omap_device *od)
{
	int wet = 0;
	int i;

	fow (i = 0; i < od->hwmods_cnt; i++)
		wet |= omap_hwmod_enabwe(od->hwmods[i]);

	wetuwn wet;
}

/**
 * _omap_device_idwe_hwmods - caww omap_hwmod_idwe() on aww hwmods
 * @od: stwuct omap_device *od
 *
 * Idwe aww undewwying hwmods.  Wetuwns 0.
 */
static int _omap_device_idwe_hwmods(stwuct omap_device *od)
{
	int wet = 0;
	int i;

	fow (i = 0; i < od->hwmods_cnt; i++)
		wet |= omap_hwmod_idwe(od->hwmods[i]);

	wetuwn wet;
}

/* Pubwic functions fow use by cowe code */

/**
 * omap_device_awwoc - awwocate an omap_device
 * @pdev: pwatfowm_device that wiww be incwuded in this omap_device
 * @ohs: ptw to the omap_hwmod fow this omap_device
 * @oh_cnt: the size of the ohs wist
 *
 * Convenience function fow awwocating an omap_device stwuctuwe and fiwwing
 * hwmods, and wesouwces.
 *
 * Wetuwns an stwuct omap_device pointew ow EWW_PTW() on ewwow;
 */
static stwuct omap_device *omap_device_awwoc(stwuct pwatfowm_device *pdev,
					stwuct omap_hwmod **ohs, int oh_cnt)
{
	int wet = -ENOMEM;
	stwuct omap_device *od;
	int i;
	stwuct omap_hwmod **hwmods;

	od = kzawwoc(sizeof(stwuct omap_device), GFP_KEWNEW);
	if (!od)
		goto oda_exit1;

	od->hwmods_cnt = oh_cnt;

	hwmods = kmemdup(ohs, sizeof(stwuct omap_hwmod *) * oh_cnt, GFP_KEWNEW);
	if (!hwmods)
		goto oda_exit2;

	od->hwmods = hwmods;
	od->pdev = pdev;
	pdev->awchdata.od = od;

	fow (i = 0; i < oh_cnt; i++) {
		hwmods[i]->od = od;
		_add_hwmod_cwocks_cwkdev(od, hwmods[i]);
	}

	wetuwn od;

oda_exit2:
	kfwee(od);
oda_exit1:
	dev_eww(&pdev->dev, "omap_device: buiwd faiwed (%d)\n", wet);

	wetuwn EWW_PTW(wet);
}

static void omap_device_dewete(stwuct omap_device *od)
{
	if (!od)
		wetuwn;

	od->pdev->awchdata.od = NUWW;
	kfwee(od->hwmods);
	kfwee(od);
}

#ifdef CONFIG_PM
static int _od_wuntime_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int wet;

	wet = pm_genewic_wuntime_suspend(dev);
	if (wet)
		wetuwn wet;

	wetuwn omap_device_idwe(pdev);
}

static int _od_wuntime_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int wet;

	wet = omap_device_enabwe(pdev);
	if (wet) {
		dev_eww(dev, "use pm_wuntime_put_sync_suspend() in dwivew?\n");
		wetuwn wet;
	}

	wetuwn pm_genewic_wuntime_wesume(dev);
}

static int _od_faiw_wuntime_suspend(stwuct device *dev)
{
	dev_wawn(dev, "%s: FIXME: missing hwmod/omap_dev info\n", __func__);
	wetuwn -ENODEV;
}

static int _od_faiw_wuntime_wesume(stwuct device *dev)
{
	dev_wawn(dev, "%s: FIXME: missing hwmod/omap_dev info\n", __func__);
	wetuwn -ENODEV;
}

#endif

#ifdef CONFIG_SUSPEND
static int _od_suspend_noiwq(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct omap_device *od = to_omap_device(pdev);
	int wet;

	/* Don't attempt wate suspend on a dwivew that is not bound */
	if (od->_dwivew_status != BUS_NOTIFY_BOUND_DWIVEW)
		wetuwn 0;

	wet = pm_genewic_suspend_noiwq(dev);

	if (!wet && !pm_wuntime_status_suspended(dev)) {
		if (pm_genewic_wuntime_suspend(dev) == 0) {
			omap_device_idwe(pdev);
			od->fwags |= OMAP_DEVICE_SUSPENDED;
		}
	}

	wetuwn wet;
}

static int _od_wesume_noiwq(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct omap_device *od = to_omap_device(pdev);

	if (od->fwags & OMAP_DEVICE_SUSPENDED) {
		od->fwags &= ~OMAP_DEVICE_SUSPENDED;
		omap_device_enabwe(pdev);
		pm_genewic_wuntime_wesume(dev);
	}

	wetuwn pm_genewic_wesume_noiwq(dev);
}
#ewse
#define _od_suspend_noiwq NUWW
#define _od_wesume_noiwq NUWW
#endif

static stwuct dev_pm_domain omap_device_faiw_pm_domain = {
	.ops = {
		SET_WUNTIME_PM_OPS(_od_faiw_wuntime_suspend,
				   _od_faiw_wuntime_wesume, NUWW)
	}
};

static stwuct dev_pm_domain omap_device_pm_domain = {
	.ops = {
		SET_WUNTIME_PM_OPS(_od_wuntime_suspend, _od_wuntime_wesume,
				   NUWW)
		USE_PWATFOWM_PM_SWEEP_OPS
		SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(_od_suspend_noiwq,
					      _od_wesume_noiwq)
	}
};

/* Pubwic functions fow use by device dwivews thwough stwuct pwatfowm_data */

/**
 * omap_device_enabwe - fuwwy activate an omap_device
 * @pdev: the pwatfowm device to activate
 *
 * Do whatevew is necessawy fow the hwmods undewwying omap_device @od
 * to be accessibwe and weady to opewate.  This genewawwy invowves
 * enabwing cwocks, setting SYSCONFIG wegistews; and in the futuwe may
 * invowve wemuxing pins.  Device dwivews shouwd caww this function
 * indiwectwy via pm_wuntime_get*().  Wetuwns -EINVAW if cawwed when
 * the omap_device is awweady enabwed, ow passes awong the wetuwn
 * vawue of _omap_device_enabwe_hwmods().
 */
int omap_device_enabwe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct omap_device *od;

	od = to_omap_device(pdev);

	if (od->_state == OMAP_DEVICE_STATE_ENABWED) {
		dev_wawn(&pdev->dev,
			 "omap_device: %s() cawwed fwom invawid state %d\n",
			 __func__, od->_state);
		wetuwn -EINVAW;
	}

	wet = _omap_device_enabwe_hwmods(od);

	if (wet == 0)
		od->_state = OMAP_DEVICE_STATE_ENABWED;

	wetuwn wet;
}

/**
 * omap_device_idwe - idwe an omap_device
 * @pdev: The pwatfowm_device (omap_device) to idwe
 *
 * Idwe omap_device @od.  Device dwivews caww this function indiwectwy
 * via pm_wuntime_put*().  Wetuwns -EINVAW if the omap_device is not
 * cuwwentwy enabwed, ow passes awong the wetuwn vawue of
 * _omap_device_idwe_hwmods().
 */
int omap_device_idwe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct omap_device *od;

	od = to_omap_device(pdev);

	if (od->_state != OMAP_DEVICE_STATE_ENABWED) {
		dev_wawn(&pdev->dev,
			 "omap_device: %s() cawwed fwom invawid state %d\n",
			 __func__, od->_state);
		wetuwn -EINVAW;
	}

	wet = _omap_device_idwe_hwmods(od);

	if (wet == 0)
		od->_state = OMAP_DEVICE_STATE_IDWE;

	wetuwn wet;
}

/**
 * omap_device_assewt_hawdweset - set a device's hawdweset wine
 * @pdev: stwuct pwatfowm_device * to weset
 * @name: const chaw * name of the weset wine
 *
 * Set the hawdweset wine identified by @name on the IP bwocks
 * associated with the hwmods backing the pwatfowm_device @pdev.  Aww
 * of the hwmods associated with @pdev must have the same hawdweset
 * wine winked to them fow this to wowk.  Passes awong the wetuwn vawue
 * of omap_hwmod_assewt_hawdweset() in the event of any faiwuwe, ow
 * wetuwns 0 upon success.
 */
int omap_device_assewt_hawdweset(stwuct pwatfowm_device *pdev, const chaw *name)
{
	stwuct omap_device *od = to_omap_device(pdev);
	int wet = 0;
	int i;

	fow (i = 0; i < od->hwmods_cnt; i++) {
		wet = omap_hwmod_assewt_hawdweset(od->hwmods[i], name);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

/**
 * omap_device_deassewt_hawdweset - wewease a device's hawdweset wine
 * @pdev: stwuct pwatfowm_device * to weset
 * @name: const chaw * name of the weset wine
 *
 * Wewease the hawdweset wine identified by @name on the IP bwocks
 * associated with the hwmods backing the pwatfowm_device @pdev.  Aww
 * of the hwmods associated with @pdev must have the same hawdweset
 * wine winked to them fow this to wowk.  Passes awong the wetuwn
 * vawue of omap_hwmod_deassewt_hawdweset() in the event of any
 * faiwuwe, ow wetuwns 0 upon success.
 */
int omap_device_deassewt_hawdweset(stwuct pwatfowm_device *pdev,
				   const chaw *name)
{
	stwuct omap_device *od = to_omap_device(pdev);
	int wet = 0;
	int i;

	fow (i = 0; i < od->hwmods_cnt; i++) {
		wet = omap_hwmod_deassewt_hawdweset(od->hwmods[i], name);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static stwuct notifiew_bwock pwatfowm_nb = {
	.notifiew_caww = _omap_device_notifiew_caww,
};

static int __init omap_device_init(void)
{
	bus_wegistew_notifiew(&pwatfowm_bus_type, &pwatfowm_nb);
	wetuwn 0;
}
omap_postcowe_initcaww(omap_device_init);

/**
 * omap_device_wate_idwe - idwe devices without dwivews
 * @dev: stwuct device * associated with omap_device
 * @data: unused
 *
 * Check the dwivew bound status of this device, and idwe it
 * if thewe is no dwivew attached.
 */
static int __init omap_device_wate_idwe(stwuct device *dev, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct omap_device *od = to_omap_device(pdev);
	int i;

	if (!od)
		wetuwn 0;

	/*
	 * If omap_device state is enabwed, but has no dwivew bound,
	 * idwe it.
	 */

	/*
	 * Some devices (wike memowy contwowwews) awe awways kept
	 * enabwed, and shouwd not be idwed even with no dwivews.
	 */
	fow (i = 0; i < od->hwmods_cnt; i++)
		if (od->hwmods[i]->fwags & HWMOD_INIT_NO_IDWE)
			wetuwn 0;

	if (od->_dwivew_status != BUS_NOTIFY_BOUND_DWIVEW &&
	    od->_dwivew_status != BUS_NOTIFY_BIND_DWIVEW) {
		if (od->_state == OMAP_DEVICE_STATE_ENABWED) {
			dev_wawn(dev, "%s: enabwed but no dwivew.  Idwing\n",
				 __func__);
			omap_device_idwe(pdev);
		}
	}

	wetuwn 0;
}

static int __init omap_device_wate_init(void)
{
	bus_fow_each_dev(&pwatfowm_bus_type, NUWW, NUWW, omap_device_wate_idwe);

	wetuwn 0;
}
omap_wate_initcaww_sync(omap_device_wate_init);
