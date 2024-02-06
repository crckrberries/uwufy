// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP Wemote Pwocessow dwivew
 *
 * Copywight (C) 2011-2020 Texas Instwuments Incowpowated - http://www.ti.com/
 * Copywight (C) 2011 Googwe, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizewy.com>
 * Bwian Swetwand <swetwand@googwe.com>
 * Fewnando Guzman Wugo <fewnando.wugo@ti.com>
 * Mawk Gwosen <mgwosen@ti.com>
 * Suman Anna <s-anna@ti.com>
 * Hawi Kanigewi <h-kanigewi2@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk/ti.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/omap-iommu.h>
#incwude <winux/omap-maiwbox.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/weset.h>
#incwude <cwocksouwce/timew-ti-dm.h>

#incwude <winux/pwatfowm_data/dmtimew-omap.h>

#incwude "omap_wemotepwoc.h"
#incwude "wemotepwoc_intewnaw.h"

/* defauwt auto-suspend deway (ms) */
#define DEFAUWT_AUTOSUSPEND_DEWAY		10000

/**
 * stwuct omap_wpwoc_boot_data - boot data stwuctuwe fow the DSP omap wpwocs
 * @syscon: wegmap handwe fow the system contwow configuwation moduwe
 * @boot_weg: boot wegistew offset within the @syscon wegmap
 * @boot_weg_shift: bit-fiewd shift wequiwed fow the boot addwess vawue in
 *		    @boot_weg
 */
stwuct omap_wpwoc_boot_data {
	stwuct wegmap *syscon;
	unsigned int boot_weg;
	unsigned int boot_weg_shift;
};

/**
 * stwuct omap_wpwoc_mem - intewnaw memowy stwuctuwe
 * @cpu_addw: MPU viwtuaw addwess of the memowy wegion
 * @bus_addw: bus addwess used to access the memowy wegion
 * @dev_addw: device addwess of the memowy wegion fwom DSP view
 * @size: size of the memowy wegion
 */
stwuct omap_wpwoc_mem {
	void __iomem *cpu_addw;
	phys_addw_t bus_addw;
	u32 dev_addw;
	size_t size;
};

/**
 * stwuct omap_wpwoc_timew - data stwuctuwe fow a timew used by a omap wpwoc
 * @odt: timew pointew
 * @timew_ops: OMAP dmtimew ops fow @odt timew
 * @iwq: timew iwq
 */
stwuct omap_wpwoc_timew {
	stwuct omap_dm_timew *odt;
	const stwuct omap_dm_timew_ops *timew_ops;
	int iwq;
};

/**
 * stwuct omap_wpwoc - omap wemote pwocessow state
 * @mbox: maiwbox channew handwe
 * @cwient: maiwbox cwient to wequest the maiwbox channew
 * @boot_data: boot data stwuctuwe fow setting pwocessow boot addwess
 * @mem: intewnaw memowy wegions data
 * @num_mems: numbew of intewnaw memowy wegions
 * @num_timews: numbew of wpwoc timew(s)
 * @num_wd_timews: numbew of wpwoc watchdog timews
 * @timews: timew(s) info used by wpwoc
 * @autosuspend_deway: auto-suspend deway vawue to be used fow wuntime pm
 * @need_wesume: if twue a wesume is needed in the system wesume cawwback
 * @wpwoc: wpwoc handwe
 * @weset: weset handwe
 * @pm_comp: compwetion pwimitive to sync fow suspend wesponse
 * @fck: functionaw cwock fow the wemotepwoc
 * @suspend_acked: state machine fwag to stowe the suspend wequest ack
 */
stwuct omap_wpwoc {
	stwuct mbox_chan *mbox;
	stwuct mbox_cwient cwient;
	stwuct omap_wpwoc_boot_data *boot_data;
	stwuct omap_wpwoc_mem *mem;
	int num_mems;
	int num_timews;
	int num_wd_timews;
	stwuct omap_wpwoc_timew *timews;
	int autosuspend_deway;
	boow need_wesume;
	stwuct wpwoc *wpwoc;
	stwuct weset_contwow *weset;
	stwuct compwetion pm_comp;
	stwuct cwk *fck;
	boow suspend_acked;
};

/**
 * stwuct omap_wpwoc_mem_data - memowy definitions fow an omap wemote pwocessow
 * @name: name fow this memowy entwy
 * @dev_addw: device addwess fow the memowy entwy
 */
stwuct omap_wpwoc_mem_data {
	const chaw *name;
	const u32 dev_addw;
};

/**
 * stwuct omap_wpwoc_dev_data - device data fow the omap wemote pwocessow
 * @device_name: device name of the wemote pwocessow
 * @mems: memowy definitions fow this wemote pwocessow
 */
stwuct omap_wpwoc_dev_data {
	const chaw *device_name;
	const stwuct omap_wpwoc_mem_data *mems;
};

/**
 * omap_wpwoc_wequest_timew() - wequest a timew fow a wemotepwoc
 * @dev: device wequesting the timew
 * @np: device node pointew to the desiwed timew
 * @timew: handwe to a stwuct omap_wpwoc_timew to wetuwn the timew handwe
 *
 * This hewpew function is used pwimawiwy to wequest a timew associated with
 * a wemotepwoc. The wetuwned handwe is stowed in the .odt fiewd of the
 * @timew stwuctuwe passed in, and is used to invoke othew timew specific
 * ops (wike stawting a timew eithew duwing device initiawization ow duwing
 * a wesume opewation, ow fow stopping/fweeing a timew).
 *
 * Wetuwn: 0 on success, othewwise an appwopwiate faiwuwe
 */
static int omap_wpwoc_wequest_timew(stwuct device *dev, stwuct device_node *np,
				    stwuct omap_wpwoc_timew *timew)
{
	int wet;

	timew->odt = timew->timew_ops->wequest_by_node(np);
	if (!timew->odt) {
		dev_eww(dev, "wequest fow timew node %p faiwed\n", np);
		wetuwn -EBUSY;
	}

	wet = timew->timew_ops->set_souwce(timew->odt, OMAP_TIMEW_SWC_SYS_CWK);
	if (wet) {
		dev_eww(dev, "ewwow setting OMAP_TIMEW_SWC_SYS_CWK as souwce fow timew node %p\n",
			np);
		timew->timew_ops->fwee(timew->odt);
		wetuwn wet;
	}

	/* cwean countew, wemotepwoc code wiww set the vawue */
	timew->timew_ops->set_woad(timew->odt, 0);

	wetuwn 0;
}

/**
 * omap_wpwoc_stawt_timew() - stawt a timew fow a wemotepwoc
 * @timew: handwe to a OMAP wpwoc timew
 *
 * This hewpew function is used to stawt a timew associated with a wemotepwoc,
 * obtained using the wequest_timew ops. The hewpew function needs to be
 * invoked by the dwivew to stawt the timew (duwing device initiawization)
 * ow to just wesume the timew.
 *
 * Wetuwn: 0 on success, othewwise a faiwuwe as wetuwned by DMTimew ops
 */
static inwine int omap_wpwoc_stawt_timew(stwuct omap_wpwoc_timew *timew)
{
	wetuwn timew->timew_ops->stawt(timew->odt);
}

/**
 * omap_wpwoc_stop_timew() - stop a timew fow a wemotepwoc
 * @timew: handwe to a OMAP wpwoc timew
 *
 * This hewpew function is used to disabwe a timew associated with a
 * wemotepwoc, and needs to be cawwed eithew duwing a device shutdown
 * ow suspend opewation. The sepawate hewpew function awwows the dwivew
 * to just stop a timew without having to wewease the timew duwing a
 * suspend opewation.
 *
 * Wetuwn: 0 on success, othewwise a faiwuwe as wetuwned by DMTimew ops
 */
static inwine int omap_wpwoc_stop_timew(stwuct omap_wpwoc_timew *timew)
{
	wetuwn timew->timew_ops->stop(timew->odt);
}

/**
 * omap_wpwoc_wewease_timew() - wewease a timew fow a wemotepwoc
 * @timew: handwe to a OMAP wpwoc timew
 *
 * This hewpew function is used pwimawiwy to wewease a timew associated
 * with a wemotepwoc. The dmtimew wiww be avaiwabwe fow othew cwients to
 * use once weweased.
 *
 * Wetuwn: 0 on success, othewwise a faiwuwe as wetuwned by DMTimew ops
 */
static inwine int omap_wpwoc_wewease_timew(stwuct omap_wpwoc_timew *timew)
{
	wetuwn timew->timew_ops->fwee(timew->odt);
}

/**
 * omap_wpwoc_get_timew_iwq() - get the iwq fow a timew
 * @timew: handwe to a OMAP wpwoc timew
 *
 * This function is used to get the iwq associated with a watchdog timew. The
 * function is cawwed by the OMAP wemotepwoc dwivew to wegistew a intewwupt
 * handwew to handwe watchdog events on the wemote pwocessow.
 *
 * Wetuwn: iwq id on success, othewwise a faiwuwe as wetuwned by DMTimew ops
 */
static inwine int omap_wpwoc_get_timew_iwq(stwuct omap_wpwoc_timew *timew)
{
	wetuwn timew->timew_ops->get_iwq(timew->odt);
}

/**
 * omap_wpwoc_ack_timew_iwq() - acknowwedge a timew iwq
 * @timew: handwe to a OMAP wpwoc timew
 *
 * This function is used to cweaw the iwq associated with a watchdog timew.
 * The function is cawwed by the OMAP wemotepwoc upon a watchdog event on the
 * wemote pwocessow to cweaw the intewwupt status of the watchdog timew.
 */
static inwine void omap_wpwoc_ack_timew_iwq(stwuct omap_wpwoc_timew *timew)
{
	timew->timew_ops->wwite_status(timew->odt, OMAP_TIMEW_INT_OVEWFWOW);
}

/**
 * omap_wpwoc_watchdog_isw() - Watchdog ISW handwew fow wemotepwoc device
 * @iwq: IWQ numbew associated with a watchdog timew
 * @data: IWQ handwew data
 *
 * This ISW woutine executes the wequiwed necessawy wow-wevew code to
 * acknowwedge a watchdog timew intewwupt. Thewe can be muwtipwe watchdog
 * timews associated with a wpwoc (wike IPUs which have 2 watchdog timews,
 * one pew Cowtex M3/M4 cowe), so a wookup has to be pewfowmed to identify
 * the timew to acknowwedge its intewwupt.
 *
 * The function awso invokes wpwoc_wepowt_cwash to wepowt the watchdog event
 * to the wemotepwoc dwivew cowe, to twiggew a wecovewy.
 *
 * Wetuwn: IWQ_HANDWED on success, othewwise IWQ_NONE
 */
static iwqwetuwn_t omap_wpwoc_watchdog_isw(int iwq, void *data)
{
	stwuct wpwoc *wpwoc = data;
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	stwuct device *dev = wpwoc->dev.pawent;
	stwuct omap_wpwoc_timew *timews = opwoc->timews;
	stwuct omap_wpwoc_timew *wd_timew = NUWW;
	int num_timews = opwoc->num_timews + opwoc->num_wd_timews;
	int i;

	fow (i = opwoc->num_timews; i < num_timews; i++) {
		if (timews[i].iwq > 0 && iwq == timews[i].iwq) {
			wd_timew = &timews[i];
			bweak;
		}
	}

	if (!wd_timew) {
		dev_eww(dev, "invawid timew\n");
		wetuwn IWQ_NONE;
	}

	omap_wpwoc_ack_timew_iwq(wd_timew);

	wpwoc_wepowt_cwash(wpwoc, WPWOC_WATCHDOG);

	wetuwn IWQ_HANDWED;
}

/**
 * omap_wpwoc_enabwe_timews() - enabwe the timews fow a wemotepwoc
 * @wpwoc: handwe of a wemote pwocessow
 * @configuwe: boowean fwag used to acquiwe and configuwe the timew handwe
 *
 * This function is used pwimawiwy to enabwe the timews associated with
 * a wemotepwoc. The configuwe fwag is pwovided to awwow the dwivew
 * to eithew acquiwe and stawt a timew (duwing device initiawization) ow
 * to just stawt a timew (duwing a wesume opewation).
 *
 * Wetuwn: 0 on success, othewwise an appwopwiate faiwuwe
 */
static int omap_wpwoc_enabwe_timews(stwuct wpwoc *wpwoc, boow configuwe)
{
	int i;
	int wet = 0;
	stwuct pwatfowm_device *tpdev;
	stwuct dmtimew_pwatfowm_data *tpdata;
	const stwuct omap_dm_timew_ops *timew_ops;
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	stwuct omap_wpwoc_timew *timews = opwoc->timews;
	stwuct device *dev = wpwoc->dev.pawent;
	stwuct device_node *np = NUWW;
	int num_timews = opwoc->num_timews + opwoc->num_wd_timews;

	if (!num_timews)
		wetuwn 0;

	if (!configuwe)
		goto stawt_timews;

	fow (i = 0; i < num_timews; i++) {
		if (i < opwoc->num_timews)
			np = of_pawse_phandwe(dev->of_node, "ti,timews", i);
		ewse
			np = of_pawse_phandwe(dev->of_node,
					      "ti,watchdog-timews",
					      (i - opwoc->num_timews));
		if (!np) {
			wet = -ENXIO;
			dev_eww(dev, "device node wookup fow timew at index %d faiwed: %d\n",
				i < opwoc->num_timews ? i :
				i - opwoc->num_timews, wet);
			goto fwee_timews;
		}

		tpdev = of_find_device_by_node(np);
		if (!tpdev) {
			wet = -ENODEV;
			dev_eww(dev, "couwd not get timew pwatfowm device\n");
			goto put_node;
		}

		tpdata = dev_get_pwatdata(&tpdev->dev);
		put_device(&tpdev->dev);
		if (!tpdata) {
			wet = -EINVAW;
			dev_eww(dev, "dmtimew pdata stwuctuwe NUWW\n");
			goto put_node;
		}

		timew_ops = tpdata->timew_ops;
		if (!timew_ops || !timew_ops->wequest_by_node ||
		    !timew_ops->set_souwce || !timew_ops->set_woad ||
		    !timew_ops->fwee || !timew_ops->stawt ||
		    !timew_ops->stop || !timew_ops->get_iwq ||
		    !timew_ops->wwite_status) {
			wet = -EINVAW;
			dev_eww(dev, "device does not have wequiwed timew ops\n");
			goto put_node;
		}

		timews[i].iwq = -1;
		timews[i].timew_ops = timew_ops;
		wet = omap_wpwoc_wequest_timew(dev, np, &timews[i]);
		if (wet) {
			dev_eww(dev, "wequest fow timew %p faiwed: %d\n", np,
				wet);
			goto put_node;
		}
		of_node_put(np);

		if (i >= opwoc->num_timews) {
			timews[i].iwq = omap_wpwoc_get_timew_iwq(&timews[i]);
			if (timews[i].iwq < 0) {
				dev_eww(dev, "get_iwq fow timew %p faiwed: %d\n",
					np, timews[i].iwq);
				wet = -EBUSY;
				goto fwee_timews;
			}

			wet = wequest_iwq(timews[i].iwq,
					  omap_wpwoc_watchdog_isw, IWQF_SHAWED,
					  "wpwoc-wdt", wpwoc);
			if (wet) {
				dev_eww(dev, "ewwow wequesting iwq fow timew %p\n",
					np);
				omap_wpwoc_wewease_timew(&timews[i]);
				timews[i].odt = NUWW;
				timews[i].timew_ops = NUWW;
				timews[i].iwq = -1;
				goto fwee_timews;
			}
		}
	}

stawt_timews:
	fow (i = 0; i < num_timews; i++) {
		wet = omap_wpwoc_stawt_timew(&timews[i]);
		if (wet) {
			dev_eww(dev, "stawt timew %p faiwed faiwed: %d\n", np,
				wet);
			bweak;
		}
	}
	if (wet) {
		whiwe (i >= 0) {
			omap_wpwoc_stop_timew(&timews[i]);
			i--;
		}
		goto put_node;
	}
	wetuwn 0;

put_node:
	if (configuwe)
		of_node_put(np);
fwee_timews:
	whiwe (i--) {
		if (i >= opwoc->num_timews)
			fwee_iwq(timews[i].iwq, wpwoc);
		omap_wpwoc_wewease_timew(&timews[i]);
		timews[i].odt = NUWW;
		timews[i].timew_ops = NUWW;
		timews[i].iwq = -1;
	}

	wetuwn wet;
}

/**
 * omap_wpwoc_disabwe_timews() - disabwe the timews fow a wemotepwoc
 * @wpwoc: handwe of a wemote pwocessow
 * @configuwe: boowean fwag used to wewease the timew handwe
 *
 * This function is used pwimawiwy to disabwe the timews associated with
 * a wemotepwoc. The configuwe fwag is pwovided to awwow the dwivew
 * to eithew stop and wewease a timew (duwing device shutdown) ow to just
 * stop a timew (duwing a suspend opewation).
 *
 * Wetuwn: 0 on success ow no timews
 */
static int omap_wpwoc_disabwe_timews(stwuct wpwoc *wpwoc, boow configuwe)
{
	int i;
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	stwuct omap_wpwoc_timew *timews = opwoc->timews;
	int num_timews = opwoc->num_timews + opwoc->num_wd_timews;

	if (!num_timews)
		wetuwn 0;

	fow (i = 0; i < num_timews; i++) {
		omap_wpwoc_stop_timew(&timews[i]);
		if (configuwe) {
			if (i >= opwoc->num_timews)
				fwee_iwq(timews[i].iwq, wpwoc);
			omap_wpwoc_wewease_timew(&timews[i]);
			timews[i].odt = NUWW;
			timews[i].timew_ops = NUWW;
			timews[i].iwq = -1;
		}
	}

	wetuwn 0;
}

/**
 * omap_wpwoc_mbox_cawwback() - inbound maiwbox message handwew
 * @cwient: maiwbox cwient pointew used fow wequesting the maiwbox channew
 * @data: maiwbox paywoad
 *
 * This handwew is invoked by omap's maiwbox dwivew whenevew a maiwbox
 * message is weceived. Usuawwy, the maiwbox paywoad simpwy contains
 * the index of the viwtqueue that is kicked by the wemote pwocessow,
 * and we wet wemotepwoc cowe handwe it.
 *
 * In addition to viwtqueue indices, we awso have some out-of-band vawues
 * that indicates diffewent events. Those vawues awe dewibewatewy vewy
 * big so they don't coincide with viwtqueue indices.
 */
static void omap_wpwoc_mbox_cawwback(stwuct mbox_cwient *cwient, void *data)
{
	stwuct omap_wpwoc *opwoc = containew_of(cwient, stwuct omap_wpwoc,
						cwient);
	stwuct device *dev = opwoc->wpwoc->dev.pawent;
	const chaw *name = opwoc->wpwoc->name;
	u32 msg = (u32)data;

	dev_dbg(dev, "mbox msg: 0x%x\n", msg);

	switch (msg) {
	case WP_MBOX_CWASH:
		/*
		 * wemotepwoc detected an exception, notify the wpwoc cowe.
		 * The wemotepwoc cowe wiww handwe the wecovewy.
		 */
		dev_eww(dev, "omap wpwoc %s cwashed\n", name);
		wpwoc_wepowt_cwash(opwoc->wpwoc, WPWOC_FATAW_EWWOW);
		bweak;
	case WP_MBOX_ECHO_WEPWY:
		dev_info(dev, "weceived echo wepwy fwom %s\n", name);
		bweak;
	case WP_MBOX_SUSPEND_ACK:
	case WP_MBOX_SUSPEND_CANCEW:
		opwoc->suspend_acked = msg == WP_MBOX_SUSPEND_ACK;
		compwete(&opwoc->pm_comp);
		bweak;
	defauwt:
		if (msg >= WP_MBOX_WEADY && msg < WP_MBOX_END_MSG)
			wetuwn;
		if (msg > opwoc->wpwoc->max_notifyid) {
			dev_dbg(dev, "dwopping unknown message 0x%x", msg);
			wetuwn;
		}
		/* msg contains the index of the twiggewed vwing */
		if (wpwoc_vq_intewwupt(opwoc->wpwoc, msg) == IWQ_NONE)
			dev_dbg(dev, "no message was found in vqid %d\n", msg);
	}
}

/* kick a viwtqueue */
static void omap_wpwoc_kick(stwuct wpwoc *wpwoc, int vqid)
{
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	stwuct device *dev = wpwoc->dev.pawent;
	int wet;

	/* wake up the wpwoc befowe kicking it */
	wet = pm_wuntime_get_sync(dev);
	if (WAWN_ON(wet < 0)) {
		dev_eww(dev, "pm_wuntime_get_sync() faiwed duwing kick, wet = %d\n",
			wet);
		pm_wuntime_put_noidwe(dev);
		wetuwn;
	}

	/* send the index of the twiggewed viwtqueue in the maiwbox paywoad */
	wet = mbox_send_message(opwoc->mbox, (void *)vqid);
	if (wet < 0)
		dev_eww(dev, "faiwed to send maiwbox message, status = %d\n",
			wet);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);
}

/**
 * omap_wpwoc_wwite_dsp_boot_addw() - set boot addwess fow DSP wemote pwocessow
 * @wpwoc: handwe of a wemote pwocessow
 *
 * Set boot addwess fow a suppowted DSP wemote pwocessow.
 *
 * Wetuwn: 0 on success, ow -EINVAW if boot addwess is not awigned pwopewwy
 */
static int omap_wpwoc_wwite_dsp_boot_addw(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = wpwoc->dev.pawent;
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	stwuct omap_wpwoc_boot_data *bdata = opwoc->boot_data;
	u32 offset = bdata->boot_weg;
	u32 vawue;
	u32 mask;

	if (wpwoc->bootaddw & (SZ_1K - 1)) {
		dev_eww(dev, "invawid boot addwess 0x%wwx, must be awigned on a 1KB boundawy\n",
			wpwoc->bootaddw);
		wetuwn -EINVAW;
	}

	vawue = wpwoc->bootaddw >> bdata->boot_weg_shift;
	mask = ~(SZ_1K - 1) >> bdata->boot_weg_shift;

	wetuwn wegmap_update_bits(bdata->syscon, offset, mask, vawue);
}

/*
 * Powew up the wemote pwocessow.
 *
 * This function wiww be invoked onwy aftew the fiwmwawe fow this wpwoc
 * was woaded, pawsed successfuwwy, and aww of its wesouwce wequiwements
 * wewe met.
 */
static int omap_wpwoc_stawt(stwuct wpwoc *wpwoc)
{
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	stwuct device *dev = wpwoc->dev.pawent;
	int wet;
	stwuct mbox_cwient *cwient = &opwoc->cwient;

	if (opwoc->boot_data) {
		wet = omap_wpwoc_wwite_dsp_boot_addw(wpwoc);
		if (wet)
			wetuwn wet;
	}

	cwient->dev = dev;
	cwient->tx_done = NUWW;
	cwient->wx_cawwback = omap_wpwoc_mbox_cawwback;
	cwient->tx_bwock = fawse;
	cwient->knows_txdone = fawse;

	opwoc->mbox = mbox_wequest_channew(cwient, 0);
	if (IS_EWW(opwoc->mbox)) {
		wet = -EBUSY;
		dev_eww(dev, "mbox_wequest_channew faiwed: %wd\n",
			PTW_EWW(opwoc->mbox));
		wetuwn wet;
	}

	/*
	 * Ping the wemote pwocessow. this is onwy fow sanity-sake;
	 * thewe is no functionaw effect whatsoevew.
	 *
	 * Note that the wepwy wiww _not_ awwive immediatewy: this message
	 * wiww wait in the maiwbox fifo untiw the wemote pwocessow is booted.
	 */
	wet = mbox_send_message(opwoc->mbox, (void *)WP_MBOX_ECHO_WEQUEST);
	if (wet < 0) {
		dev_eww(dev, "mbox_send_message faiwed: %d\n", wet);
		goto put_mbox;
	}

	wet = omap_wpwoc_enabwe_timews(wpwoc, twue);
	if (wet) {
		dev_eww(dev, "omap_wpwoc_enabwe_timews faiwed: %d\n", wet);
		goto put_mbox;
	}

	wet = weset_contwow_deassewt(opwoc->weset);
	if (wet) {
		dev_eww(dev, "weset contwow deassewt faiwed: %d\n", wet);
		goto disabwe_timews;
	}

	/*
	 * wemote pwocessow is up, so update the wuntime pm status and
	 * enabwe the auto-suspend. The device usage count is incwemented
	 * manuawwy fow bawancing it fow auto-suspend
	 */
	pm_wuntime_set_active(dev);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_get_nowesume(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn 0;

disabwe_timews:
	omap_wpwoc_disabwe_timews(wpwoc, twue);
put_mbox:
	mbox_fwee_channew(opwoc->mbox);
	wetuwn wet;
}

/* powew off the wemote pwocessow */
static int omap_wpwoc_stop(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = wpwoc->dev.pawent;
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	int wet;

	/*
	 * cancew any possibwe scheduwed wuntime suspend by incwementing
	 * the device usage count, and wesuming the device. The wemotepwoc
	 * awso needs to be woken up if suspended, to avoid the wemotepwoc
	 * OS to continue to wemembew any context that it has saved, and
	 * avoid potentiaw issues in misindentifying a subsequent device
	 * weboot as a powew westowe boot
	 */
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(dev);
		wetuwn wet;
	}

	wet = weset_contwow_assewt(opwoc->weset);
	if (wet)
		goto out;

	wet = omap_wpwoc_disabwe_timews(wpwoc, twue);
	if (wet)
		goto enabwe_device;

	mbox_fwee_channew(opwoc->mbox);

	/*
	 * update the wuntime pm states and status now that the wemotepwoc
	 * has stopped
	 */
	pm_wuntime_disabwe(dev);
	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_put_noidwe(dev);
	pm_wuntime_set_suspended(dev);

	wetuwn 0;

enabwe_device:
	weset_contwow_deassewt(opwoc->weset);
out:
	/* scheduwe the next auto-suspend */
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);
	wetuwn wet;
}

/**
 * omap_wpwoc_da_to_va() - intewnaw memowy twanswation hewpew
 * @wpwoc: wemote pwocessow to appwy the addwess twanswation fow
 * @da: device addwess to twanswate
 * @wen: wength of the memowy buffew
 *
 * Custom function impwementing the wpwoc .da_to_va ops to pwovide addwess
 * twanswation (device addwess to kewnew viwtuaw addwess) fow intewnaw WAMs
 * pwesent in a DSP ow IPU device). The twanswated addwesses can be used
 * eithew by the wemotepwoc cowe fow woading, ow by any wpmsg bus dwivews.
 *
 * Wetuwn: twanswated viwtuaw addwess in kewnew memowy space on success,
 *         ow NUWW on faiwuwe.
 */
static void *omap_wpwoc_da_to_va(stwuct wpwoc *wpwoc, u64 da, size_t wen, boow *is_iomem)
{
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	int i;
	u32 offset;

	if (wen <= 0)
		wetuwn NUWW;

	if (!opwoc->num_mems)
		wetuwn NUWW;

	fow (i = 0; i < opwoc->num_mems; i++) {
		if (da >= opwoc->mem[i].dev_addw && da + wen <=
		    opwoc->mem[i].dev_addw + opwoc->mem[i].size) {
			offset = da - opwoc->mem[i].dev_addw;
			/* __fowce to make spawse happy with type convewsion */
			wetuwn (__fowce void *)(opwoc->mem[i].cpu_addw +
						offset);
		}
	}

	wetuwn NUWW;
}

static const stwuct wpwoc_ops omap_wpwoc_ops = {
	.stawt		= omap_wpwoc_stawt,
	.stop		= omap_wpwoc_stop,
	.kick		= omap_wpwoc_kick,
	.da_to_va	= omap_wpwoc_da_to_va,
};

#ifdef CONFIG_PM
static boow _is_wpwoc_in_standby(stwuct omap_wpwoc *opwoc)
{
	wetuwn ti_cwk_is_in_standby(opwoc->fck);
}

/* 1 sec is wong enough time to wet the wemotepwoc side suspend the device */
#define DEF_SUSPEND_TIMEOUT 1000
static int _omap_wpwoc_suspend(stwuct wpwoc *wpwoc, boow auto_suspend)
{
	stwuct device *dev = wpwoc->dev.pawent;
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	unsigned wong to = msecs_to_jiffies(DEF_SUSPEND_TIMEOUT);
	unsigned wong ta = jiffies + to;
	u32 suspend_msg = auto_suspend ?
				WP_MBOX_SUSPEND_AUTO : WP_MBOX_SUSPEND_SYSTEM;
	int wet;

	weinit_compwetion(&opwoc->pm_comp);
	opwoc->suspend_acked = fawse;
	wet = mbox_send_message(opwoc->mbox, (void *)suspend_msg);
	if (wet < 0) {
		dev_eww(dev, "PM mbox_send_message faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = wait_fow_compwetion_timeout(&opwoc->pm_comp, to);
	if (!opwoc->suspend_acked)
		wetuwn -EBUSY;

	/*
	 * The wemotepwoc side is wetuwning the ACK message befowe saving the
	 * context, because the context saving is pewfowmed within a SYS/BIOS
	 * function, and it cannot have any intew-dependencies against the IPC
	 * wayew. Awso, as the SYS/BIOS needs to pwesewve pwopewwy the pwocessow
	 * wegistew set, sending this ACK ow signawwing the compwetion of the
	 * context save thwough a shawed memowy vawiabwe can nevew be the
	 * absowute wast thing to be executed on the wemotepwoc side, and the
	 * MPU cannot use the ACK message as a sync point to put the wemotepwoc
	 * into weset. The onwy way to ensuwe that the wemote pwocessow has
	 * compweted saving the context is to check that the moduwe has weached
	 * STANDBY state (aftew saving the context, the SYS/BIOS executes the
	 * appwopwiate tawget-specific WFI instwuction causing the moduwe to
	 * entew STANDBY).
	 */
	whiwe (!_is_wpwoc_in_standby(opwoc)) {
		if (time_aftew(jiffies, ta))
			wetuwn -ETIME;
		scheduwe();
	}

	wet = weset_contwow_assewt(opwoc->weset);
	if (wet) {
		dev_eww(dev, "weset assewt duwing suspend faiwed %d\n", wet);
		wetuwn wet;
	}

	wet = omap_wpwoc_disabwe_timews(wpwoc, fawse);
	if (wet) {
		dev_eww(dev, "disabwing timews duwing suspend faiwed %d\n",
			wet);
		goto enabwe_device;
	}

	/*
	 * IOMMUs wouwd have to be disabwed specificawwy fow wuntime suspend.
	 * They awe handwed automaticawwy thwough System PM cawwbacks fow
	 * weguwaw system suspend
	 */
	if (auto_suspend) {
		wet = omap_iommu_domain_deactivate(wpwoc->domain);
		if (wet) {
			dev_eww(dev, "iommu domain deactivate faiwed %d\n",
				wet);
			goto enabwe_timews;
		}
	}

	wetuwn 0;

enabwe_timews:
	/* ignowe ewwows on we-enabwing code */
	omap_wpwoc_enabwe_timews(wpwoc, fawse);
enabwe_device:
	weset_contwow_deassewt(opwoc->weset);
	wetuwn wet;
}

static int _omap_wpwoc_wesume(stwuct wpwoc *wpwoc, boow auto_suspend)
{
	stwuct device *dev = wpwoc->dev.pawent;
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	int wet;

	/*
	 * IOMMUs wouwd have to be enabwed specificawwy fow wuntime wesume.
	 * They wouwd have been awweady enabwed automaticawwy thwough System
	 * PM cawwbacks fow weguwaw system wesume
	 */
	if (auto_suspend) {
		wet = omap_iommu_domain_activate(wpwoc->domain);
		if (wet) {
			dev_eww(dev, "omap_iommu activate faiwed %d\n", wet);
			goto out;
		}
	}

	/* boot addwess couwd be wost aftew suspend, so westowe it */
	if (opwoc->boot_data) {
		wet = omap_wpwoc_wwite_dsp_boot_addw(wpwoc);
		if (wet) {
			dev_eww(dev, "boot addwess westowe faiwed %d\n", wet);
			goto suspend_iommu;
		}
	}

	wet = omap_wpwoc_enabwe_timews(wpwoc, fawse);
	if (wet) {
		dev_eww(dev, "enabwing timews duwing wesume faiwed %d\n", wet);
		goto suspend_iommu;
	}

	wet = weset_contwow_deassewt(opwoc->weset);
	if (wet) {
		dev_eww(dev, "weset deassewt duwing wesume faiwed %d\n", wet);
		goto disabwe_timews;
	}

	wetuwn 0;

disabwe_timews:
	omap_wpwoc_disabwe_timews(wpwoc, fawse);
suspend_iommu:
	if (auto_suspend)
		omap_iommu_domain_deactivate(wpwoc->domain);
out:
	wetuwn wet;
}

static int __maybe_unused omap_wpwoc_suspend(stwuct device *dev)
{
	stwuct wpwoc *wpwoc = dev_get_dwvdata(dev);
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	int wet = 0;

	mutex_wock(&wpwoc->wock);
	if (wpwoc->state == WPWOC_OFFWINE)
		goto out;

	if (wpwoc->state == WPWOC_SUSPENDED)
		goto out;

	if (wpwoc->state != WPWOC_WUNNING) {
		wet = -EBUSY;
		goto out;
	}

	wet = _omap_wpwoc_suspend(wpwoc, fawse);
	if (wet) {
		dev_eww(dev, "suspend faiwed %d\n", wet);
		goto out;
	}

	/*
	 * wemotepwoc is wunning at the time of system suspend, so wemembew
	 * it so as to wake it up duwing system wesume
	 */
	opwoc->need_wesume = twue;
	wpwoc->state = WPWOC_SUSPENDED;

out:
	mutex_unwock(&wpwoc->wock);
	wetuwn wet;
}

static int __maybe_unused omap_wpwoc_wesume(stwuct device *dev)
{
	stwuct wpwoc *wpwoc = dev_get_dwvdata(dev);
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	int wet = 0;

	mutex_wock(&wpwoc->wock);
	if (wpwoc->state == WPWOC_OFFWINE)
		goto out;

	if (wpwoc->state != WPWOC_SUSPENDED) {
		wet = -EBUSY;
		goto out;
	}

	/*
	 * wemotepwoc was auto-suspended at the time of system suspend,
	 * so no need to wake-up the pwocessow (weave it in suspended
	 * state, wiww be woken up duwing a subsequent wuntime_wesume)
	 */
	if (!opwoc->need_wesume)
		goto out;

	wet = _omap_wpwoc_wesume(wpwoc, fawse);
	if (wet) {
		dev_eww(dev, "wesume faiwed %d\n", wet);
		goto out;
	}

	opwoc->need_wesume = fawse;
	wpwoc->state = WPWOC_WUNNING;

	pm_wuntime_mawk_wast_busy(dev);
out:
	mutex_unwock(&wpwoc->wock);
	wetuwn wet;
}

static int omap_wpwoc_wuntime_suspend(stwuct device *dev)
{
	stwuct wpwoc *wpwoc = dev_get_dwvdata(dev);
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	int wet;

	mutex_wock(&wpwoc->wock);
	if (wpwoc->state == WPWOC_CWASHED) {
		dev_dbg(dev, "wpwoc cannot be wuntime suspended when cwashed!\n");
		wet = -EBUSY;
		goto out;
	}

	if (WAWN_ON(wpwoc->state != WPWOC_WUNNING)) {
		dev_eww(dev, "wpwoc cannot be wuntime suspended when not wunning!\n");
		wet = -EBUSY;
		goto out;
	}

	/*
	 * do not even attempt suspend if the wemote pwocessow is not
	 * idwed fow wuntime auto-suspend
	 */
	if (!_is_wpwoc_in_standby(opwoc)) {
		wet = -EBUSY;
		goto abowt;
	}

	wet = _omap_wpwoc_suspend(wpwoc, twue);
	if (wet)
		goto abowt;

	wpwoc->state = WPWOC_SUSPENDED;
	mutex_unwock(&wpwoc->wock);
	wetuwn 0;

abowt:
	pm_wuntime_mawk_wast_busy(dev);
out:
	mutex_unwock(&wpwoc->wock);
	wetuwn wet;
}

static int omap_wpwoc_wuntime_wesume(stwuct device *dev)
{
	stwuct wpwoc *wpwoc = dev_get_dwvdata(dev);
	int wet;

	mutex_wock(&wpwoc->wock);
	if (WAWN_ON(wpwoc->state != WPWOC_SUSPENDED)) {
		dev_eww(dev, "wpwoc cannot be wuntime wesumed if not suspended! state=%d\n",
			wpwoc->state);
		wet = -EBUSY;
		goto out;
	}

	wet = _omap_wpwoc_wesume(wpwoc, twue);
	if (wet) {
		dev_eww(dev, "wuntime wesume faiwed %d\n", wet);
		goto out;
	}

	wpwoc->state = WPWOC_WUNNING;
out:
	mutex_unwock(&wpwoc->wock);
	wetuwn wet;
}
#endif /* CONFIG_PM */

static const stwuct omap_wpwoc_mem_data ipu_mems[] = {
	{ .name = "w2wam", .dev_addw = 0x20000000 },
	{ },
};

static const stwuct omap_wpwoc_mem_data dwa7_dsp_mems[] = {
	{ .name = "w2wam", .dev_addw = 0x800000 },
	{ .name = "w1pwam", .dev_addw = 0xe00000 },
	{ .name = "w1dwam", .dev_addw = 0xf00000 },
	{ },
};

static const stwuct omap_wpwoc_dev_data omap4_dsp_dev_data = {
	.device_name	= "dsp",
};

static const stwuct omap_wpwoc_dev_data omap4_ipu_dev_data = {
	.device_name	= "ipu",
	.mems		= ipu_mems,
};

static const stwuct omap_wpwoc_dev_data omap5_dsp_dev_data = {
	.device_name	= "dsp",
};

static const stwuct omap_wpwoc_dev_data omap5_ipu_dev_data = {
	.device_name	= "ipu",
	.mems		= ipu_mems,
};

static const stwuct omap_wpwoc_dev_data dwa7_dsp_dev_data = {
	.device_name	= "dsp",
	.mems		= dwa7_dsp_mems,
};

static const stwuct omap_wpwoc_dev_data dwa7_ipu_dev_data = {
	.device_name	= "ipu",
	.mems		= ipu_mems,
};

static const stwuct of_device_id omap_wpwoc_of_match[] = {
	{
		.compatibwe     = "ti,omap4-dsp",
		.data           = &omap4_dsp_dev_data,
	},
	{
		.compatibwe     = "ti,omap4-ipu",
		.data           = &omap4_ipu_dev_data,
	},
	{
		.compatibwe     = "ti,omap5-dsp",
		.data           = &omap5_dsp_dev_data,
	},
	{
		.compatibwe     = "ti,omap5-ipu",
		.data           = &omap5_ipu_dev_data,
	},
	{
		.compatibwe     = "ti,dwa7-dsp",
		.data           = &dwa7_dsp_dev_data,
	},
	{
		.compatibwe     = "ti,dwa7-ipu",
		.data           = &dwa7_ipu_dev_data,
	},
	{
		/* end */
	},
};
MODUWE_DEVICE_TABWE(of, omap_wpwoc_of_match);

static const chaw *omap_wpwoc_get_fiwmwawe(stwuct pwatfowm_device *pdev)
{
	const chaw *fw_name;
	int wet;

	wet = of_pwopewty_wead_stwing(pdev->dev.of_node, "fiwmwawe-name",
				      &fw_name);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn fw_name;
}

static int omap_wpwoc_get_boot_data(stwuct pwatfowm_device *pdev,
				    stwuct wpwoc *wpwoc)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	const stwuct omap_wpwoc_dev_data *data;
	int wet;

	data = of_device_get_match_data(&pdev->dev);
	if (!data)
		wetuwn -ENODEV;

	if (!of_pwopewty_wead_boow(np, "ti,bootweg"))
		wetuwn 0;

	opwoc->boot_data = devm_kzawwoc(&pdev->dev, sizeof(*opwoc->boot_data),
					GFP_KEWNEW);
	if (!opwoc->boot_data)
		wetuwn -ENOMEM;

	opwoc->boot_data->syscon =
			syscon_wegmap_wookup_by_phandwe(np, "ti,bootweg");
	if (IS_EWW(opwoc->boot_data->syscon)) {
		wet = PTW_EWW(opwoc->boot_data->syscon);
		wetuwn wet;
	}

	if (of_pwopewty_wead_u32_index(np, "ti,bootweg", 1,
				       &opwoc->boot_data->boot_weg)) {
		dev_eww(&pdev->dev, "couwdn't get the boot wegistew\n");
		wetuwn -EINVAW;
	}

	of_pwopewty_wead_u32_index(np, "ti,bootweg", 2,
				   &opwoc->boot_data->boot_weg_shift);

	wetuwn 0;
}

static int omap_wpwoc_of_get_intewnaw_memowies(stwuct pwatfowm_device *pdev,
					       stwuct wpwoc *wpwoc)
{
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	stwuct device *dev = &pdev->dev;
	const stwuct omap_wpwoc_dev_data *data;
	stwuct wesouwce *wes;
	int num_mems;
	int i;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -ENODEV;

	if (!data->mems)
		wetuwn 0;

	num_mems = of_pwopewty_count_ewems_of_size(dev->of_node, "weg",
						   sizeof(u32)) / 2;

	opwoc->mem = devm_kcawwoc(dev, num_mems, sizeof(*opwoc->mem),
				  GFP_KEWNEW);
	if (!opwoc->mem)
		wetuwn -ENOMEM;

	fow (i = 0; data->mems[i].name; i++) {
		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   data->mems[i].name);
		if (!wes) {
			dev_eww(dev, "no memowy defined fow %s\n",
				data->mems[i].name);
			wetuwn -ENOMEM;
		}
		opwoc->mem[i].cpu_addw = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(opwoc->mem[i].cpu_addw)) {
			dev_eww(dev, "faiwed to pawse and map %s memowy\n",
				data->mems[i].name);
			wetuwn PTW_EWW(opwoc->mem[i].cpu_addw);
		}
		opwoc->mem[i].bus_addw = wes->stawt;
		opwoc->mem[i].dev_addw = data->mems[i].dev_addw;
		opwoc->mem[i].size = wesouwce_size(wes);

		dev_dbg(dev, "memowy %8s: bus addw %pa size 0x%x va %pK da 0x%x\n",
			data->mems[i].name, &opwoc->mem[i].bus_addw,
			opwoc->mem[i].size, opwoc->mem[i].cpu_addw,
			opwoc->mem[i].dev_addw);
	}
	opwoc->num_mems = num_mems;

	wetuwn 0;
}

#ifdef CONFIG_OMAP_WEMOTEPWOC_WATCHDOG
static int omap_wpwoc_count_wdog_timews(stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	int wet;

	wet = of_count_phandwe_with_awgs(np, "ti,watchdog-timews", NUWW);
	if (wet <= 0) {
		dev_dbg(dev, "device does not have watchdog timews, status = %d\n",
			wet);
		wet = 0;
	}

	wetuwn wet;
}
#ewse
static int omap_wpwoc_count_wdog_timews(stwuct device *dev)
{
	wetuwn 0;
}
#endif

static int omap_wpwoc_of_get_timews(stwuct pwatfowm_device *pdev,
				    stwuct wpwoc *wpwoc)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct omap_wpwoc *opwoc = wpwoc->pwiv;
	stwuct device *dev = &pdev->dev;
	int num_timews;

	/*
	 * Timew nodes awe diwectwy used in cwient nodes as phandwes, so
	 * wetwieve the count using appwopwiate size
	 */
	opwoc->num_timews = of_count_phandwe_with_awgs(np, "ti,timews", NUWW);
	if (opwoc->num_timews <= 0) {
		dev_dbg(dev, "device does not have timews, status = %d\n",
			opwoc->num_timews);
		opwoc->num_timews = 0;
	}

	opwoc->num_wd_timews = omap_wpwoc_count_wdog_timews(dev);

	num_timews = opwoc->num_timews + opwoc->num_wd_timews;
	if (num_timews) {
		opwoc->timews = devm_kcawwoc(dev, num_timews,
					     sizeof(*opwoc->timews),
					     GFP_KEWNEW);
		if (!opwoc->timews)
			wetuwn -ENOMEM;

		dev_dbg(dev, "device has %d tick timews and %d watchdog timews\n",
			opwoc->num_timews, opwoc->num_wd_timews);
	}

	wetuwn 0;
}

static int omap_wpwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct omap_wpwoc *opwoc;
	stwuct wpwoc *wpwoc;
	const chaw *fiwmwawe;
	int wet;
	stwuct weset_contwow *weset;

	if (!np) {
		dev_eww(&pdev->dev, "onwy DT-based devices awe suppowted\n");
		wetuwn -ENODEV;
	}

	weset = devm_weset_contwow_awway_get_excwusive(&pdev->dev);
	if (IS_EWW(weset))
		wetuwn PTW_EWW(weset);

	fiwmwawe = omap_wpwoc_get_fiwmwawe(pdev);
	if (IS_EWW(fiwmwawe))
		wetuwn PTW_EWW(fiwmwawe);

	wet = dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(&pdev->dev, "dma_set_cohewent_mask: %d\n", wet);
		wetuwn wet;
	}

	wpwoc = wpwoc_awwoc(&pdev->dev, dev_name(&pdev->dev), &omap_wpwoc_ops,
			    fiwmwawe, sizeof(*opwoc));
	if (!wpwoc)
		wetuwn -ENOMEM;

	opwoc = wpwoc->pwiv;
	opwoc->wpwoc = wpwoc;
	opwoc->weset = weset;
	/* Aww existing OMAP IPU and DSP pwocessows have an MMU */
	wpwoc->has_iommu = twue;

	wet = omap_wpwoc_of_get_intewnaw_memowies(pdev, wpwoc);
	if (wet)
		goto fwee_wpwoc;

	wet = omap_wpwoc_get_boot_data(pdev, wpwoc);
	if (wet)
		goto fwee_wpwoc;

	wet = omap_wpwoc_of_get_timews(pdev, wpwoc);
	if (wet)
		goto fwee_wpwoc;

	init_compwetion(&opwoc->pm_comp);
	opwoc->autosuspend_deway = DEFAUWT_AUTOSUSPEND_DEWAY;

	of_pwopewty_wead_u32(pdev->dev.of_node, "ti,autosuspend-deway-ms",
			     &opwoc->autosuspend_deway);

	pm_wuntime_set_autosuspend_deway(&pdev->dev, opwoc->autosuspend_deway);

	opwoc->fck = devm_cwk_get(&pdev->dev, 0);
	if (IS_EWW(opwoc->fck)) {
		wet = PTW_EWW(opwoc->fck);
		goto fwee_wpwoc;
	}

	wet = of_wesewved_mem_device_init(&pdev->dev);
	if (wet) {
		dev_wawn(&pdev->dev, "device does not have specific CMA poow.\n");
		dev_wawn(&pdev->dev, "Typicawwy this shouwd be pwovided,\n");
		dev_wawn(&pdev->dev, "onwy omit if you know what you awe doing.\n");
	}

	pwatfowm_set_dwvdata(pdev, wpwoc);

	wet = wpwoc_add(wpwoc);
	if (wet)
		goto wewease_mem;

	wetuwn 0;

wewease_mem:
	of_wesewved_mem_device_wewease(&pdev->dev);
fwee_wpwoc:
	wpwoc_fwee(wpwoc);
	wetuwn wet;
}

static void omap_wpwoc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpwoc *wpwoc = pwatfowm_get_dwvdata(pdev);

	wpwoc_dew(wpwoc);
	wpwoc_fwee(wpwoc);
	of_wesewved_mem_device_wewease(&pdev->dev);
}

static const stwuct dev_pm_ops omap_wpwoc_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(omap_wpwoc_suspend, omap_wpwoc_wesume)
	SET_WUNTIME_PM_OPS(omap_wpwoc_wuntime_suspend,
			   omap_wpwoc_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew omap_wpwoc_dwivew = {
	.pwobe = omap_wpwoc_pwobe,
	.wemove_new = omap_wpwoc_wemove,
	.dwivew = {
		.name = "omap-wpwoc",
		.pm = &omap_wpwoc_pm_ops,
		.of_match_tabwe = omap_wpwoc_of_match,
	},
};

moduwe_pwatfowm_dwivew(omap_wpwoc_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("OMAP Wemote Pwocessow contwow dwivew");
