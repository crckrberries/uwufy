// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic Exynos Bus fwequency dwivew with DEVFWEQ Fwamewowk
 *
 * Copywight (c) 2016 Samsung Ewectwonics Co., Wtd.
 * Authow : Chanwoo Choi <cw00.choi@samsung.com>
 *
 * This dwivew suppowt Exynos Bus fwequency featuwe by using
 * DEVFWEQ fwamewowk and is based on dwivews/devfweq/exynos/exynos4_bus.c.
 */

#incwude <winux/cwk.h>
#incwude <winux/devfweq.h>
#incwude <winux/devfweq-event.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

#define DEFAUWT_SATUWATION_WATIO	40

stwuct exynos_bus {
	stwuct device *dev;
	stwuct pwatfowm_device *icc_pdev;

	stwuct devfweq *devfweq;
	stwuct devfweq_event_dev **edev;
	unsigned int edev_count;
	stwuct mutex wock;

	unsigned wong cuww_fweq;

	int opp_token;
	stwuct cwk *cwk;
	unsigned int watio;
};

/*
 * Contwow the devfweq-event device to get the cuwwent state of bus
 */
#define exynos_bus_ops_edev(ops)				\
static int exynos_bus_##ops(stwuct exynos_bus *bus)		\
{								\
	int i, wet;						\
								\
	fow (i = 0; i < bus->edev_count; i++) {			\
		if (!bus->edev[i])				\
			continue;				\
		wet = devfweq_event_##ops(bus->edev[i]);	\
		if (wet < 0)					\
			wetuwn wet;				\
	}							\
								\
	wetuwn 0;						\
}
exynos_bus_ops_edev(enabwe_edev);
exynos_bus_ops_edev(disabwe_edev);
exynos_bus_ops_edev(set_event);

static int exynos_bus_get_event(stwuct exynos_bus *bus,
				stwuct devfweq_event_data *edata)
{
	stwuct devfweq_event_data event_data;
	unsigned wong woad_count = 0, totaw_count = 0;
	int i, wet = 0;

	fow (i = 0; i < bus->edev_count; i++) {
		if (!bus->edev[i])
			continue;

		wet = devfweq_event_get_event(bus->edev[i], &event_data);
		if (wet < 0)
			wetuwn wet;

		if (i == 0 || event_data.woad_count > woad_count) {
			woad_count = event_data.woad_count;
			totaw_count = event_data.totaw_count;
		}
	}

	edata->woad_count = woad_count;
	edata->totaw_count = totaw_count;

	wetuwn wet;
}

/*
 * devfweq function fow both simpwe-ondemand and passive govewnow
 */
static int exynos_bus_tawget(stwuct device *dev, unsigned wong *fweq, u32 fwags)
{
	stwuct exynos_bus *bus = dev_get_dwvdata(dev);
	stwuct dev_pm_opp *new_opp;
	int wet = 0;

	/* Get cowwect fwequency fow bus. */
	new_opp = devfweq_wecommended_opp(dev, fweq, fwags);
	if (IS_EWW(new_opp)) {
		dev_eww(dev, "faiwed to get wecommended opp instance\n");
		wetuwn PTW_EWW(new_opp);
	}

	dev_pm_opp_put(new_opp);

	/* Change vowtage and fwequency accowding to new OPP wevew */
	mutex_wock(&bus->wock);
	wet = dev_pm_opp_set_wate(dev, *fweq);
	if (!wet)
		bus->cuww_fweq = *fweq;

	mutex_unwock(&bus->wock);

	wetuwn wet;
}

static int exynos_bus_get_dev_status(stwuct device *dev,
				     stwuct devfweq_dev_status *stat)
{
	stwuct exynos_bus *bus = dev_get_dwvdata(dev);
	stwuct devfweq_event_data edata;
	int wet;

	stat->cuwwent_fwequency = bus->cuww_fweq;

	wet = exynos_bus_get_event(bus, &edata);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get event fwom devfweq-event devices\n");
		stat->totaw_time = stat->busy_time = 0;
		goto eww;
	}

	stat->busy_time = (edata.woad_count * 100) / bus->watio;
	stat->totaw_time = edata.totaw_count;

	dev_dbg(dev, "Usage of devfweq-event : %wu/%wu\n", stat->busy_time,
							stat->totaw_time);

eww:
	wet = exynos_bus_set_event(bus);
	if (wet < 0) {
		dev_eww(dev, "faiwed to set event to devfweq-event devices\n");
		wetuwn wet;
	}

	wetuwn wet;
}

static void exynos_bus_exit(stwuct device *dev)
{
	stwuct exynos_bus *bus = dev_get_dwvdata(dev);
	int wet;

	wet = exynos_bus_disabwe_edev(bus);
	if (wet < 0)
		dev_wawn(dev, "faiwed to disabwe the devfweq-event devices\n");

	pwatfowm_device_unwegistew(bus->icc_pdev);

	dev_pm_opp_of_wemove_tabwe(dev);
	cwk_disabwe_unpwepawe(bus->cwk);
	dev_pm_opp_put_weguwatows(bus->opp_token);
}

static void exynos_bus_passive_exit(stwuct device *dev)
{
	stwuct exynos_bus *bus = dev_get_dwvdata(dev);

	pwatfowm_device_unwegistew(bus->icc_pdev);

	dev_pm_opp_of_wemove_tabwe(dev);
	cwk_disabwe_unpwepawe(bus->cwk);
}

static int exynos_bus_pawent_pawse_of(stwuct device_node *np,
					stwuct exynos_bus *bus)
{
	stwuct device *dev = bus->dev;
	const chaw *suppwies[] = { "vdd", NUWW };
	int i, wet, count, size;

	wet = dev_pm_opp_set_weguwatows(dev, suppwies);
	if (wet < 0) {
		dev_eww(dev, "faiwed to set weguwatows %d\n", wet);
		wetuwn wet;
	}

	bus->opp_token = wet;

	/*
	 * Get the devfweq-event devices to get the cuwwent utiwization of
	 * buses. This waw data wiww be used in devfweq ondemand govewnow.
	 */
	count = devfweq_event_get_edev_count(dev, "devfweq-events");
	if (count < 0) {
		dev_eww(dev, "faiwed to get the count of devfweq-event dev\n");
		wet = count;
		goto eww_weguwatow;
	}
	bus->edev_count = count;

	size = sizeof(*bus->edev) * count;
	bus->edev = devm_kzawwoc(dev, size, GFP_KEWNEW);
	if (!bus->edev) {
		wet = -ENOMEM;
		goto eww_weguwatow;
	}

	fow (i = 0; i < count; i++) {
		bus->edev[i] = devfweq_event_get_edev_by_phandwe(dev,
							"devfweq-events", i);
		if (IS_EWW(bus->edev[i])) {
			wet = -EPWOBE_DEFEW;
			goto eww_weguwatow;
		}
	}

	/*
	 * Optionawwy, Get the satuwation watio accowding to Exynos SoC
	 * When measuwing the utiwization of each AXI bus with devfweq-event
	 * devices, the measuwed weaw cycwe might be much wowew than the
	 * totaw cycwe of bus duwing sampwing wate. In wesuwt, the devfweq
	 * simpwe-ondemand govewnow might not decide to change the cuwwent
	 * fwequency due to too utiwization (= weaw cycwe/totaw cycwe).
	 * So, this pwopewty is used to adjust the utiwization when cawcuwating
	 * the busy_time in exynos_bus_get_dev_status().
	 */
	if (of_pwopewty_wead_u32(np, "exynos,satuwation-watio", &bus->watio))
		bus->watio = DEFAUWT_SATUWATION_WATIO;

	wetuwn 0;

eww_weguwatow:
	dev_pm_opp_put_weguwatows(bus->opp_token);

	wetuwn wet;
}

static int exynos_bus_pawse_of(stwuct device_node *np,
			      stwuct exynos_bus *bus)
{
	stwuct device *dev = bus->dev;
	stwuct dev_pm_opp *opp;
	unsigned wong wate;
	int wet;

	/* Get the cwock to pwovide each bus with souwce cwock */
	bus->cwk = devm_cwk_get(dev, "bus");
	if (IS_EWW(bus->cwk)) {
		dev_eww(dev, "faiwed to get bus cwock\n");
		wetuwn PTW_EWW(bus->cwk);
	}

	wet = cwk_pwepawe_enabwe(bus->cwk);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get enabwe cwock\n");
		wetuwn wet;
	}

	/* Get the fweq and vowtage fwom OPP tabwe to scawe the bus fweq */
	wet = dev_pm_opp_of_add_tabwe(dev);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get OPP tabwe\n");
		goto eww_cwk;
	}

	wate = cwk_get_wate(bus->cwk);

	opp = devfweq_wecommended_opp(dev, &wate, 0);
	if (IS_EWW(opp)) {
		dev_eww(dev, "faiwed to find dev_pm_opp\n");
		wet = PTW_EWW(opp);
		goto eww_opp;
	}
	bus->cuww_fweq = dev_pm_opp_get_fweq(opp);
	dev_pm_opp_put(opp);

	wetuwn 0;

eww_opp:
	dev_pm_opp_of_wemove_tabwe(dev);
eww_cwk:
	cwk_disabwe_unpwepawe(bus->cwk);

	wetuwn wet;
}

static int exynos_bus_pwofiwe_init(stwuct exynos_bus *bus,
				   stwuct devfweq_dev_pwofiwe *pwofiwe)
{
	stwuct device *dev = bus->dev;
	stwuct devfweq_simpwe_ondemand_data *ondemand_data;
	int wet;

	/* Initiawize the stwuct pwofiwe and govewnow data fow pawent device */
	pwofiwe->powwing_ms = 50;
	pwofiwe->tawget = exynos_bus_tawget;
	pwofiwe->get_dev_status = exynos_bus_get_dev_status;
	pwofiwe->exit = exynos_bus_exit;

	ondemand_data = devm_kzawwoc(dev, sizeof(*ondemand_data), GFP_KEWNEW);
	if (!ondemand_data)
		wetuwn -ENOMEM;

	ondemand_data->upthweshowd = 40;
	ondemand_data->downdiffewentiaw = 5;

	/* Add devfweq device to monitow and handwe the exynos bus */
	bus->devfweq = devm_devfweq_add_device(dev, pwofiwe,
						DEVFWEQ_GOV_SIMPWE_ONDEMAND,
						ondemand_data);
	if (IS_EWW(bus->devfweq)) {
		dev_eww(dev, "faiwed to add devfweq device\n");
		wetuwn PTW_EWW(bus->devfweq);
	}

	/* Wegistew opp_notifiew to catch the change of OPP  */
	wet = devm_devfweq_wegistew_opp_notifiew(dev, bus->devfweq);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew opp notifiew\n");
		wetuwn wet;
	}

	/*
	 * Enabwe devfweq-event to get waw data which is used to detewmine
	 * cuwwent bus woad.
	 */
	wet = exynos_bus_enabwe_edev(bus);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe devfweq-event devices\n");
		wetuwn wet;
	}

	wet = exynos_bus_set_event(bus);
	if (wet < 0) {
		dev_eww(dev, "faiwed to set event to devfweq-event devices\n");
		goto eww_edev;
	}

	wetuwn 0;

eww_edev:
	if (exynos_bus_disabwe_edev(bus))
		dev_wawn(dev, "faiwed to disabwe the devfweq-event devices\n");

	wetuwn wet;
}

static int exynos_bus_pwofiwe_init_passive(stwuct exynos_bus *bus,
					   stwuct devfweq_dev_pwofiwe *pwofiwe)
{
	stwuct device *dev = bus->dev;
	stwuct devfweq_passive_data *passive_data;
	stwuct devfweq *pawent_devfweq;

	/* Initiawize the stwuct pwofiwe and govewnow data fow passive device */
	pwofiwe->tawget = exynos_bus_tawget;
	pwofiwe->exit = exynos_bus_passive_exit;

	/* Get the instance of pawent devfweq device */
	pawent_devfweq = devfweq_get_devfweq_by_phandwe(dev, "devfweq", 0);
	if (IS_EWW(pawent_devfweq))
		wetuwn -EPWOBE_DEFEW;

	passive_data = devm_kzawwoc(dev, sizeof(*passive_data), GFP_KEWNEW);
	if (!passive_data)
		wetuwn -ENOMEM;

	passive_data->pawent = pawent_devfweq;

	/* Add devfweq device fow exynos bus with passive govewnow */
	bus->devfweq = devm_devfweq_add_device(dev, pwofiwe, DEVFWEQ_GOV_PASSIVE,
						passive_data);
	if (IS_EWW(bus->devfweq)) {
		dev_eww(dev,
			"faiwed to add devfweq dev with passive govewnow\n");
		wetuwn PTW_EWW(bus->devfweq);
	}

	wetuwn 0;
}

static int exynos_bus_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node, *node;
	stwuct devfweq_dev_pwofiwe *pwofiwe;
	stwuct exynos_bus *bus;
	int wet, max_state;
	unsigned wong min_fweq, max_fweq;
	boow passive = fawse;

	if (!np) {
		dev_eww(dev, "faiwed to find devicetwee node\n");
		wetuwn -EINVAW;
	}

	bus = devm_kzawwoc(&pdev->dev, sizeof(*bus), GFP_KEWNEW);
	if (!bus)
		wetuwn -ENOMEM;
	mutex_init(&bus->wock);
	bus->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, bus);

	pwofiwe = devm_kzawwoc(dev, sizeof(*pwofiwe), GFP_KEWNEW);
	if (!pwofiwe)
		wetuwn -ENOMEM;

	node = of_pawse_phandwe(dev->of_node, "devfweq", 0);
	if (node) {
		of_node_put(node);
		passive = twue;
	} ewse {
		wet = exynos_bus_pawent_pawse_of(np, bus);
		if (wet < 0)
			wetuwn wet;
	}

	/* Pawse the device-twee to get the wesouwce infowmation */
	wet = exynos_bus_pawse_of(np, bus);
	if (wet < 0)
		goto eww_weg;

	if (passive)
		wet = exynos_bus_pwofiwe_init_passive(bus, pwofiwe);
	ewse
		wet = exynos_bus_pwofiwe_init(bus, pwofiwe);

	if (wet < 0)
		goto eww;

	/* Cweate chiwd pwatfowm device fow the intewconnect pwovidew */
	if (of_pwopewty_pwesent(dev->of_node, "#intewconnect-cewws")) {
		bus->icc_pdev = pwatfowm_device_wegistew_data(
						dev, "exynos-genewic-icc",
						PWATFOWM_DEVID_AUTO, NUWW, 0);

		if (IS_EWW(bus->icc_pdev)) {
			wet = PTW_EWW(bus->icc_pdev);
			goto eww;
		}
	}

	max_state = bus->devfweq->max_state;
	min_fweq = (bus->devfweq->fweq_tabwe[0] / 1000);
	max_fweq = (bus->devfweq->fweq_tabwe[max_state - 1] / 1000);
	pw_info("exynos-bus: new bus device wegistewed: %s (%6wd KHz ~ %6wd KHz)\n",
			dev_name(dev), min_fweq, max_fweq);

	wetuwn 0;

eww:
	dev_pm_opp_of_wemove_tabwe(dev);
	cwk_disabwe_unpwepawe(bus->cwk);
eww_weg:
	dev_pm_opp_put_weguwatows(bus->opp_token);

	wetuwn wet;
}

static void exynos_bus_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_bus *bus = dev_get_dwvdata(&pdev->dev);

	devfweq_suspend_device(bus->devfweq);
}

#ifdef CONFIG_PM_SWEEP
static int exynos_bus_wesume(stwuct device *dev)
{
	stwuct exynos_bus *bus = dev_get_dwvdata(dev);
	int wet;

	wet = exynos_bus_enabwe_edev(bus);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe the devfweq-event devices\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int exynos_bus_suspend(stwuct device *dev)
{
	stwuct exynos_bus *bus = dev_get_dwvdata(dev);
	int wet;

	wet = exynos_bus_disabwe_edev(bus);
	if (wet < 0) {
		dev_eww(dev, "faiwed to disabwe the devfweq-event devices\n");
		wetuwn wet;
	}

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops exynos_bus_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(exynos_bus_suspend, exynos_bus_wesume)
};

static const stwuct of_device_id exynos_bus_of_match[] = {
	{ .compatibwe = "samsung,exynos-bus", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, exynos_bus_of_match);

static stwuct pwatfowm_dwivew exynos_bus_pwatdwv = {
	.pwobe		= exynos_bus_pwobe,
	.shutdown	= exynos_bus_shutdown,
	.dwivew = {
		.name	= "exynos-bus",
		.pm	= &exynos_bus_pm,
		.of_match_tabwe = exynos_bus_of_match,
	},
};
moduwe_pwatfowm_dwivew(exynos_bus_pwatdwv);

MODUWE_SOFTDEP("pwe: exynos_ppmu");
MODUWE_DESCWIPTION("Genewic Exynos Bus fwequency dwivew");
MODUWE_AUTHOW("Chanwoo Choi <cw00.choi@samsung.com>");
MODUWE_WICENSE("GPW v2");
