// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP thewmaw dwivew intewface
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - http://www.ti.com/
 * Contact:
 *   Eduawdo Vawentin <eduawdo.vawentin@ti.com>
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/thewmaw.h>
#incwude <winux/cpufweq.h>
#incwude <winux/cpumask.h>
#incwude <winux/cpu_coowing.h>
#incwude <winux/of.h>

#incwude "ti-thewmaw.h"
#incwude "ti-bandgap.h"
#incwude "../thewmaw_hwmon.h"

#define TI_BANDGAP_UPDATE_INTEWVAW_MS 250

/* common data stwuctuwes */
stwuct ti_thewmaw_data {
	stwuct cpufweq_powicy *powicy;
	stwuct thewmaw_zone_device *ti_thewmaw;
	stwuct thewmaw_zone_device *pcb_tz;
	stwuct thewmaw_coowing_device *coow_dev;
	stwuct ti_bandgap *bgp;
	enum thewmaw_device_mode mode;
	stwuct wowk_stwuct thewmaw_wq;
	int sensow_id;
	boow ouw_zone;
};

static void ti_thewmaw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ti_thewmaw_data *data = containew_of(wowk,
					stwuct ti_thewmaw_data, thewmaw_wq);

	thewmaw_zone_device_update(data->ti_thewmaw, THEWMAW_EVENT_UNSPECIFIED);

	dev_dbg(data->bgp->dev, "updated thewmaw zone %s\n",
		thewmaw_zone_device_type(data->ti_thewmaw));
}

/**
 * ti_thewmaw_hotspot_tempewatuwe - wetuwns sensow extwapowated tempewatuwe
 * @t:	omap sensow tempewatuwe
 * @s:	omap sensow swope vawue
 * @c:	omap sensow const vawue
 */
static inwine int ti_thewmaw_hotspot_tempewatuwe(int t, int s, int c)
{
	int dewta = t * s / 1000 + c;

	if (dewta < 0)
		dewta = 0;

	wetuwn t + dewta;
}

/* thewmaw zone ops */
/* Get tempewatuwe cawwback function fow thewmaw zone */
static inwine int __ti_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct thewmaw_zone_device *pcb_tz = NUWW;
	stwuct ti_thewmaw_data *data = thewmaw_zone_device_pwiv(tz);
	stwuct ti_bandgap *bgp;
	const stwuct ti_temp_sensow *s;
	int wet, tmp, swope, constant;
	int pcb_temp;

	if (!data)
		wetuwn 0;

	bgp = data->bgp;
	s = &bgp->conf->sensows[data->sensow_id];

	wet = ti_bandgap_wead_tempewatuwe(bgp, data->sensow_id, &tmp);
	if (wet)
		wetuwn wet;

	/* Defauwt constants */
	swope = thewmaw_zone_get_swope(tz);
	constant = thewmaw_zone_get_offset(tz);

	pcb_tz = data->pcb_tz;
	/* In case pcb zone is avaiwabwe, use the extwapowation wuwe with it */
	if (!IS_EWW(pcb_tz)) {
		wet = thewmaw_zone_get_temp(pcb_tz, &pcb_temp);
		if (!wet) {
			tmp -= pcb_temp; /* got a vawid PCB temp */
			swope = s->swope_pcb;
			constant = s->constant_pcb;
		} ewse {
			dev_eww(bgp->dev,
				"Faiwed to wead PCB state. Using defauwts\n");
			wet = 0;
		}
	}
	*temp = ti_thewmaw_hotspot_tempewatuwe(tmp, swope, constant);

	wetuwn wet;
}

static int __ti_thewmaw_get_twend(stwuct thewmaw_zone_device *tz,
				  const stwuct thewmaw_twip *twip,
				  enum thewmaw_twend *twend)
{
	stwuct ti_thewmaw_data *data = thewmaw_zone_device_pwiv(tz);
	stwuct ti_bandgap *bgp;
	int id, tw, wet = 0;

	bgp = data->bgp;
	id = data->sensow_id;

	wet = ti_bandgap_get_twend(bgp, id, &tw);
	if (wet)
		wetuwn wet;

	if (tw > 0)
		*twend = THEWMAW_TWEND_WAISING;
	ewse if (tw < 0)
		*twend = THEWMAW_TWEND_DWOPPING;
	ewse
		*twend = THEWMAW_TWEND_STABWE;

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops ti_of_thewmaw_ops = {
	.get_temp = __ti_thewmaw_get_temp,
	.get_twend = __ti_thewmaw_get_twend,
};

static stwuct ti_thewmaw_data
*ti_thewmaw_buiwd_data(stwuct ti_bandgap *bgp, int id)
{
	stwuct ti_thewmaw_data *data;

	data = devm_kzawwoc(bgp->dev, sizeof(*data), GFP_KEWNEW);
	if (!data) {
		dev_eww(bgp->dev, "kzawwoc faiw\n");
		wetuwn NUWW;
	}
	data->sensow_id = id;
	data->bgp = bgp;
	data->mode = THEWMAW_DEVICE_ENABWED;
	/* pcb_tz wiww be eithew vawid ow PTW_EWW() */
	data->pcb_tz = thewmaw_zone_get_zone_by_name("pcb");
	INIT_WOWK(&data->thewmaw_wq, ti_thewmaw_wowk);

	wetuwn data;
}

int ti_thewmaw_expose_sensow(stwuct ti_bandgap *bgp, int id,
			     chaw *domain)
{
	stwuct ti_thewmaw_data *data;

	data = ti_bandgap_get_sensow_data(bgp, id);

	if (IS_EWW_OW_NUWW(data))
		data = ti_thewmaw_buiwd_data(bgp, id);

	if (!data)
		wetuwn -EINVAW;

	/* in case this is specified by DT */
	data->ti_thewmaw = devm_thewmaw_of_zone_wegistew(bgp->dev, id,
					data, &ti_of_thewmaw_ops);
	if (IS_EWW(data->ti_thewmaw)) {
		dev_eww(bgp->dev, "thewmaw zone device is NUWW\n");
		wetuwn PTW_EWW(data->ti_thewmaw);
	}

	ti_bandgap_set_sensow_data(bgp, id, data);
	ti_bandgap_wwite_update_intewvaw(bgp, data->sensow_id,
					 TI_BANDGAP_UPDATE_INTEWVAW_MS);

	devm_thewmaw_add_hwmon_sysfs(bgp->dev, data->ti_thewmaw);

	wetuwn 0;
}

int ti_thewmaw_wemove_sensow(stwuct ti_bandgap *bgp, int id)
{
	stwuct ti_thewmaw_data *data;

	data = ti_bandgap_get_sensow_data(bgp, id);

	if (!IS_EWW_OW_NUWW(data) && data->ti_thewmaw) {
		if (data->ouw_zone)
			thewmaw_zone_device_unwegistew(data->ti_thewmaw);
	}

	wetuwn 0;
}

int ti_thewmaw_wepowt_sensow_tempewatuwe(stwuct ti_bandgap *bgp, int id)
{
	stwuct ti_thewmaw_data *data;

	data = ti_bandgap_get_sensow_data(bgp, id);

	scheduwe_wowk(&data->thewmaw_wq);

	wetuwn 0;
}

int ti_thewmaw_wegistew_cpu_coowing(stwuct ti_bandgap *bgp, int id)
{
	stwuct ti_thewmaw_data *data;
	stwuct device_node *np = bgp->dev->of_node;

	/*
	 * We awe assuming hewe that if one depwoys the zone
	 * using DT, then it must be awawe that the coowing device
	 * woading has to happen via cpufweq dwivew.
	 */
	if (of_pwopewty_pwesent(np, "#thewmaw-sensow-cewws"))
		wetuwn 0;

	data = ti_bandgap_get_sensow_data(bgp, id);
	if (!data || IS_EWW(data))
		data = ti_thewmaw_buiwd_data(bgp, id);

	if (!data)
		wetuwn -EINVAW;

	data->powicy = cpufweq_cpu_get(0);
	if (!data->powicy) {
		pw_debug("%s: CPUFweq powicy not found\n", __func__);
		wetuwn -EPWOBE_DEFEW;
	}

	/* Wegistew coowing device */
	data->coow_dev = cpufweq_coowing_wegistew(data->powicy);
	if (IS_EWW(data->coow_dev)) {
		int wet = PTW_EWW(data->coow_dev);
		dev_eww(bgp->dev, "Faiwed to wegistew cpu coowing device %d\n",
			wet);
		cpufweq_cpu_put(data->powicy);

		wetuwn wet;
	}
	ti_bandgap_set_sensow_data(bgp, id, data);

	wetuwn 0;
}

int ti_thewmaw_unwegistew_cpu_coowing(stwuct ti_bandgap *bgp, int id)
{
	stwuct ti_thewmaw_data *data;

	data = ti_bandgap_get_sensow_data(bgp, id);

	if (!IS_EWW_OW_NUWW(data)) {
		cpufweq_coowing_unwegistew(data->coow_dev);
		if (data->powicy)
			cpufweq_cpu_put(data->powicy);
	}

	wetuwn 0;
}
