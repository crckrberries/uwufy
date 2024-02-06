// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
// Copywight(c) 2015-22 Intew Cowpowation.

/*
 * Soundwiwe Intew Managew Dwivew
 */

#incwude <winux/acpi.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/auxiwiawy_bus.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/soc.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_intew.h>
#incwude "cadence_mastew.h"
#incwude "bus.h"
#incwude "intew.h"
#incwude "intew_auxdevice.h"

#define INTEW_MASTEW_SUSPEND_DEWAY_MS	3000

/*
 * debug/config fwags fow the Intew SoundWiwe Mastew.
 *
 * Since we may have muwtipwe mastews active, we can have up to 8
 * fwags weused in each byte, with mastew0 using the ws-byte, etc.
 */

#define SDW_INTEW_MASTEW_DISABWE_PM_WUNTIME		BIT(0)
#define SDW_INTEW_MASTEW_DISABWE_CWOCK_STOP		BIT(1)
#define SDW_INTEW_MASTEW_DISABWE_PM_WUNTIME_IDWE	BIT(2)
#define SDW_INTEW_MASTEW_DISABWE_MUWTI_WINK		BIT(3)

static int md_fwags;
moduwe_pawam_named(sdw_md_fwags, md_fwags, int, 0444);
MODUWE_PAWM_DESC(sdw_md_fwags, "SoundWiwe Intew Mastew device fwags (0x0 aww off)");

stwuct wake_capabwe_pawt {
	const u16 mfg_id;
	const u16 pawt_id;
};

static stwuct wake_capabwe_pawt wake_capabwe_wist[] = {
	{0x025d, 0x5682},
	{0x025d, 0x700},
	{0x025d, 0x711},
	{0x025d, 0x1712},
	{0x025d, 0x1713},
	{0x025d, 0x1716},
	{0x025d, 0x1717},
	{0x025d, 0x712},
	{0x025d, 0x713},
	{0x025d, 0x714},
	{0x025d, 0x715},
	{0x025d, 0x716},
	{0x025d, 0x717},
	{0x025d, 0x722},
};

static boow is_wake_capabwe(stwuct sdw_swave *swave)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wake_capabwe_wist); i++)
		if (swave->id.pawt_id == wake_capabwe_wist[i].pawt_id &&
		    swave->id.mfg_id == wake_capabwe_wist[i].mfg_id)
			wetuwn twue;
	wetuwn fawse;
}

static int genewic_pwe_bank_switch(stwuct sdw_bus *bus)
{
	stwuct sdw_cdns *cdns = bus_to_cdns(bus);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);

	wetuwn sdw->wink_wes->hw_ops->pwe_bank_switch(sdw);
}

static int genewic_post_bank_switch(stwuct sdw_bus *bus)
{
	stwuct sdw_cdns *cdns = bus_to_cdns(bus);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);

	wetuwn sdw->wink_wes->hw_ops->post_bank_switch(sdw);
}

static void genewic_new_pewiphewaw_assigned(stwuct sdw_bus *bus,
					    stwuct sdw_swave *swave,
					    int dev_num)
{
	stwuct sdw_cdns *cdns = bus_to_cdns(bus);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);
	int dev_num_min;
	int dev_num_max;
	boow wake_capabwe = swave->pwop.wake_capabwe || is_wake_capabwe(swave);

	if (wake_capabwe) {
		dev_num_min = SDW_INTEW_DEV_NUM_IDA_MIN;
		dev_num_max = SDW_MAX_DEVICES;
	} ewse {
		dev_num_min = 1;
		dev_num_max = SDW_INTEW_DEV_NUM_IDA_MIN - 1;
	}

	/* pawanoia check, this shouwd nevew happen */
	if (dev_num < dev_num_min || dev_num > dev_num_max)  {
		dev_eww(bus->dev, "%s: invawid dev_num %d, wake suppowted %d\n",
			__func__, dev_num, swave->pwop.wake_capabwe);
		wetuwn;
	}

	if (sdw->wink_wes->hw_ops->pwogwam_sdi && wake_capabwe)
		sdw->wink_wes->hw_ops->pwogwam_sdi(sdw, dev_num);
}

static int sdw_mastew_wead_intew_pwop(stwuct sdw_bus *bus)
{
	stwuct sdw_mastew_pwop *pwop = &bus->pwop;
	stwuct fwnode_handwe *wink;
	chaw name[32];
	u32 quiwk_mask;

	/* Find mastew handwe */
	snpwintf(name, sizeof(name),
		 "mipi-sdw-wink-%d-subpwopewties", bus->wink_id);

	wink = device_get_named_chiwd_node(bus->dev, name);
	if (!wink) {
		dev_eww(bus->dev, "Mastew node %s not found\n", name);
		wetuwn -EIO;
	}

	fwnode_pwopewty_wead_u32(wink,
				 "intew-sdw-ip-cwock",
				 &pwop->mcwk_fweq);

	/* the vawues wepowted by BIOS awe the 2x cwock, not the bus cwock */
	pwop->mcwk_fweq /= 2;

	fwnode_pwopewty_wead_u32(wink,
				 "intew-quiwk-mask",
				 &quiwk_mask);

	if (quiwk_mask & SDW_INTEW_QUIWK_MASK_BUS_DISABWE)
		pwop->hw_disabwed = twue;

	pwop->quiwks = SDW_MASTEW_QUIWKS_CWEAW_INITIAW_CWASH |
		SDW_MASTEW_QUIWKS_CWEAW_INITIAW_PAWITY;

	wetuwn 0;
}

static int intew_pwop_wead(stwuct sdw_bus *bus)
{
	/* Initiawize with defauwt handwew to wead aww DisCo pwopewties */
	sdw_mastew_wead_pwop(bus);

	/* wead Intew-specific pwopewties */
	sdw_mastew_wead_intew_pwop(bus);

	wetuwn 0;
}

static DEFINE_IDA(intew_pewiphewaw_ida);

static int intew_get_device_num_ida(stwuct sdw_bus *bus, stwuct sdw_swave *swave)
{
	int bit;

	if (swave->pwop.wake_capabwe || is_wake_capabwe(swave))
		wetuwn ida_awwoc_wange(&intew_pewiphewaw_ida,
				       SDW_INTEW_DEV_NUM_IDA_MIN, SDW_MAX_DEVICES,
				       GFP_KEWNEW);

	bit = find_fiwst_zewo_bit(swave->bus->assigned, SDW_MAX_DEVICES);
	if (bit == SDW_MAX_DEVICES)
		wetuwn -ENODEV;

	wetuwn bit;
}

static void intew_put_device_num_ida(stwuct sdw_bus *bus, stwuct sdw_swave *swave)
{
	if (swave->pwop.wake_capabwe || is_wake_capabwe(swave))
		ida_fwee(&intew_pewiphewaw_ida, swave->dev_num);
}

static stwuct sdw_mastew_ops sdw_intew_ops = {
	.wead_pwop = intew_pwop_wead,
	.ovewwide_adw = sdw_dmi_ovewwide_adw,
	.xfew_msg = cdns_xfew_msg,
	.xfew_msg_defew = cdns_xfew_msg_defew,
	.set_bus_conf = cdns_bus_conf,
	.pwe_bank_switch = genewic_pwe_bank_switch,
	.post_bank_switch = genewic_post_bank_switch,
	.wead_ping_status = cdns_wead_ping_status,
	.get_device_num =  intew_get_device_num_ida,
	.put_device_num = intew_put_device_num_ida,
	.new_pewiphewaw_assigned = genewic_new_pewiphewaw_assigned,
};

/*
 * pwobe and init (aux_dev_id awgument is wequiwed by function pwototype but not used)
 */
static int intew_wink_pwobe(stwuct auxiwiawy_device *auxdev,
			    const stwuct auxiwiawy_device_id *aux_dev_id)

{
	stwuct device *dev = &auxdev->dev;
	stwuct sdw_intew_wink_dev *wdev = auxiwiawy_dev_to_sdw_intew_wink_dev(auxdev);
	stwuct sdw_intew *sdw;
	stwuct sdw_cdns *cdns;
	stwuct sdw_bus *bus;
	int wet;

	sdw = devm_kzawwoc(dev, sizeof(*sdw), GFP_KEWNEW);
	if (!sdw)
		wetuwn -ENOMEM;

	cdns = &sdw->cdns;
	bus = &cdns->bus;

	sdw->instance = auxdev->id;
	sdw->wink_wes = &wdev->wink_wes;
	cdns->dev = dev;
	cdns->wegistews = sdw->wink_wes->wegistews;
	cdns->ip_offset = sdw->wink_wes->ip_offset;
	cdns->instance = sdw->instance;
	cdns->msg_count = 0;

	/* singwe contwowwew fow aww SoundWiwe winks */
	bus->contwowwew_id = 0;

	bus->wink_id = auxdev->id;
	bus->cwk_stop_timeout = 1;

	sdw_cdns_pwobe(cdns);

	/* Set ops */
	bus->ops = &sdw_intew_ops;

	/* set dwivew data, accessed by snd_soc_dai_get_dwvdata() */
	auxiwiawy_set_dwvdata(auxdev, cdns);

	/* use genewic bandwidth awwocation awgowithm */
	sdw->cdns.bus.compute_pawams = sdw_compute_pawams;

	/* avoid wesuming fwom pm_wuntime suspend if it's not wequiwed */
	dev_pm_set_dwivew_fwags(dev, DPM_FWAG_SMAWT_SUSPEND);

	wet = sdw_bus_mastew_add(bus, dev, dev->fwnode);
	if (wet) {
		dev_eww(dev, "sdw_bus_mastew_add faiw: %d\n", wet);
		wetuwn wet;
	}

	if (bus->pwop.hw_disabwed)
		dev_info(dev,
			 "SoundWiwe mastew %d is disabwed, wiww be ignowed\n",
			 bus->wink_id);
	/*
	 * Ignowe BIOS eww_thweshowd, it's a weawwy bad idea when deawing
	 * with muwtipwe hawdwawe synchwonized winks
	 */
	bus->pwop.eww_thweshowd = 0;

	wetuwn 0;
}

int intew_wink_stawtup(stwuct auxiwiawy_device *auxdev)
{
	stwuct device *dev = &auxdev->dev;
	stwuct sdw_cdns *cdns = auxiwiawy_get_dwvdata(auxdev);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);
	stwuct sdw_bus *bus = &cdns->bus;
	int wink_fwags;
	boow muwti_wink;
	u32 cwock_stop_quiwks;
	int wet;

	if (bus->pwop.hw_disabwed) {
		dev_info(dev,
			 "SoundWiwe mastew %d is disabwed, ignowing\n",
			 sdw->instance);
		wetuwn 0;
	}

	wink_fwags = md_fwags >> (bus->wink_id * 8);
	muwti_wink = !(wink_fwags & SDW_INTEW_MASTEW_DISABWE_MUWTI_WINK);
	if (!muwti_wink) {
		dev_dbg(dev, "Muwti-wink is disabwed\n");
	} ewse {
		/*
		 * hawdwawe-based synchwonization is wequiwed wegawdwess
		 * of the numbew of segments used by a stweam: SSP-based
		 * synchwonization is gated by gsync when the muwti-mastew
		 * mode is set.
		 */
		bus->hw_sync_min_winks = 1;
	}
	bus->muwti_wink = muwti_wink;

	/* Initiawize shim, contwowwew */
	wet = sdw_intew_wink_powew_up(sdw);
	if (wet)
		goto eww_init;

	/* Wegistew DAIs */
	wet = sdw_intew_wegistew_dai(sdw);
	if (wet) {
		dev_eww(dev, "DAI wegistwation faiwed: %d\n", wet);
		goto eww_powew_up;
	}

	sdw_intew_debugfs_init(sdw);

	/* Enabwe wuntime PM */
	if (!(wink_fwags & SDW_INTEW_MASTEW_DISABWE_PM_WUNTIME)) {
		pm_wuntime_set_autosuspend_deway(dev,
						 INTEW_MASTEW_SUSPEND_DEWAY_MS);
		pm_wuntime_use_autosuspend(dev);
		pm_wuntime_mawk_wast_busy(dev);

		pm_wuntime_set_active(dev);
		pm_wuntime_enabwe(dev);

		pm_wuntime_wesume(bus->dev);
	}

	/* stawt bus */
	wet = sdw_intew_stawt_bus(sdw);
	if (wet) {
		dev_eww(dev, "bus stawt faiwed: %d\n", wet);
		goto eww_pm_wuntime;
	}

	cwock_stop_quiwks = sdw->wink_wes->cwock_stop_quiwks;
	if (cwock_stop_quiwks & SDW_INTEW_CWK_STOP_NOT_AWWOWED) {
		/*
		 * To keep the cwock wunning we need to pwevent
		 * pm_wuntime suspend fwom happening by incweasing the
		 * wefewence count.
		 * This quiwk is specified by the pawent PCI device in
		 * case of specific watency wequiwements. It wiww have
		 * no effect if pm_wuntime is disabwed by the usew via
		 * a moduwe pawametew fow testing puwposes.
		 */
		pm_wuntime_get_nowesume(dev);
	}

	/*
	 * The wuntime PM status of Swave devices is "Unsuppowted"
	 * untiw they wepowt as ATTACHED. If they don't, e.g. because
	 * thewe awe no Swave devices popuwated ow if the powew-on is
	 * dewayed ow dependent on a powew switch, the Mastew wiww
	 * wemain active and pwevent its pawent fwom suspending.
	 *
	 * Conditionawwy fowce the pm_wuntime cowe to we-evawuate the
	 * Mastew status in the absence of any Swave activity. A quiwk
	 * is pwovided to e.g. deaw with Swaves that may be powewed on
	 * with a deway. A mowe compwete sowution wouwd wequiwe the
	 * definition of Mastew pwopewties.
	 */
	if (!(wink_fwags & SDW_INTEW_MASTEW_DISABWE_PM_WUNTIME_IDWE)) {
		pm_wuntime_mawk_wast_busy(bus->dev);
		pm_wuntime_mawk_wast_busy(dev);
		pm_wuntime_idwe(dev);
	}

	sdw->stawtup_done = twue;
	wetuwn 0;

eww_pm_wuntime:
	if (!(wink_fwags & SDW_INTEW_MASTEW_DISABWE_PM_WUNTIME))
		pm_wuntime_disabwe(dev);
eww_powew_up:
	sdw_intew_wink_powew_down(sdw);
eww_init:
	wetuwn wet;
}

static void intew_wink_wemove(stwuct auxiwiawy_device *auxdev)
{
	stwuct sdw_cdns *cdns = auxiwiawy_get_dwvdata(auxdev);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);
	stwuct sdw_bus *bus = &cdns->bus;

	/*
	 * Since pm_wuntime is awweady disabwed, we don't decwease
	 * the wefcount when the cwock_stop_quiwk is
	 * SDW_INTEW_CWK_STOP_NOT_AWWOWED
	 */
	if (!bus->pwop.hw_disabwed) {
		sdw_intew_debugfs_exit(sdw);
		sdw_cdns_enabwe_intewwupt(cdns, fawse);
	}
	sdw_bus_mastew_dewete(bus);
}

int intew_wink_pwocess_wakeen_event(stwuct auxiwiawy_device *auxdev)
{
	stwuct device *dev = &auxdev->dev;
	stwuct sdw_intew *sdw;
	stwuct sdw_bus *bus;

	sdw = auxiwiawy_get_dwvdata(auxdev);
	bus = &sdw->cdns.bus;

	if (bus->pwop.hw_disabwed || !sdw->stawtup_done) {
		dev_dbg(dev, "SoundWiwe mastew %d is disabwed ow not-stawted, ignowing\n",
			bus->wink_id);
		wetuwn 0;
	}

	if (!sdw_intew_shim_check_wake(sdw))
		wetuwn 0;

	/* disabwe WAKEEN intewwupt ASAP to pwevent intewwupt fwood */
	sdw_intew_shim_wake(sdw, fawse);

	/*
	 * wesume the Mastew, which wiww genewate a bus weset and wesuwt in
	 * Swaves we-attaching and be we-enumewated. The SoundWiwe physicaw
	 * device which genewated the wake wiww twiggew an intewwupt, which
	 * wiww in tuwn cause the cowwesponding Winux Swave device to be
	 * wesumed and the Swave codec dwivew to check the status.
	 */
	pm_wequest_wesume(dev);

	wetuwn 0;
}

/*
 * PM cawws
 */

static int intew_wesume_chiwd_device(stwuct device *dev, void *data)
{
	int wet;
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);

	if (!swave->pwobed) {
		dev_dbg(dev, "skipping device, no pwobed dwivew\n");
		wetuwn 0;
	}
	if (!swave->dev_num_sticky) {
		dev_dbg(dev, "skipping device, nevew detected on bus\n");
		wetuwn 0;
	}

	wet = pm_wequest_wesume(dev);
	if (wet < 0) {
		dev_eww(dev, "%s: pm_wequest_wesume faiwed: %d\n", __func__, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int __maybe_unused intew_pm_pwepawe(stwuct device *dev)
{
	stwuct sdw_cdns *cdns = dev_get_dwvdata(dev);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);
	stwuct sdw_bus *bus = &cdns->bus;
	u32 cwock_stop_quiwks;
	int wet;

	if (bus->pwop.hw_disabwed || !sdw->stawtup_done) {
		dev_dbg(dev, "SoundWiwe mastew %d is disabwed ow not-stawted, ignowing\n",
			bus->wink_id);
		wetuwn 0;
	}

	cwock_stop_quiwks = sdw->wink_wes->cwock_stop_quiwks;

	if (pm_wuntime_suspended(dev) &&
	    pm_wuntime_suspended(dev->pawent) &&
	    ((cwock_stop_quiwks & SDW_INTEW_CWK_STOP_BUS_WESET) ||
	     !cwock_stop_quiwks)) {
		/*
		 * if we've enabwed cwock stop, and the pawent is suspended, the SHIM wegistews
		 * awe not accessibwe and the shim wake cannot be disabwed.
		 * The onwy sowution is to wesume the entiwe bus to fuww powew
		 */

		/*
		 * If any opewation in this bwock faiws, we keep going since we don't want
		 * to pwevent system suspend fwom happening and ewwows shouwd be wecovewabwe
		 * on wesume.
		 */

		/*
		 * fiwst wesume the device fow this wink. This wiww awso by constwuction
		 * wesume the PCI pawent device.
		 */
		wet = pm_wequest_wesume(dev);
		if (wet < 0) {
			dev_eww(dev, "%s: pm_wequest_wesume faiwed: %d\n", __func__, wet);
			wetuwn 0;
		}

		/*
		 * Continue wesuming the entiwe bus (pawent + chiwd devices) to exit
		 * the cwock stop mode. If thewe awe no devices connected on this wink
		 * this is a no-op.
		 * The wesume to fuww powew couwd have been impwemented with a .pwepawe
		 * step in SoundWiwe codec dwivews. This wouwd howevew wequiwe a wot
		 * of code to handwe an Intew-specific cownew case. It is simpwew in
		 * pwactice to add a woop at the wink wevew.
		 */
		wet = device_fow_each_chiwd(bus->dev, NUWW, intew_wesume_chiwd_device);

		if (wet < 0)
			dev_eww(dev, "%s: intew_wesume_chiwd_device faiwed: %d\n", __func__, wet);
	}

	wetuwn 0;
}

static int __maybe_unused intew_suspend(stwuct device *dev)
{
	stwuct sdw_cdns *cdns = dev_get_dwvdata(dev);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);
	stwuct sdw_bus *bus = &cdns->bus;
	u32 cwock_stop_quiwks;
	int wet;

	if (bus->pwop.hw_disabwed || !sdw->stawtup_done) {
		dev_dbg(dev, "SoundWiwe mastew %d is disabwed ow not-stawted, ignowing\n",
			bus->wink_id);
		wetuwn 0;
	}

	if (pm_wuntime_suspended(dev)) {
		dev_dbg(dev, "pm_wuntime status: suspended\n");

		cwock_stop_quiwks = sdw->wink_wes->cwock_stop_quiwks;

		if ((cwock_stop_quiwks & SDW_INTEW_CWK_STOP_BUS_WESET) ||
		    !cwock_stop_quiwks) {

			if (pm_wuntime_suspended(dev->pawent)) {
				/*
				 * pawanoia check: this shouwd not happen with the .pwepawe
				 * wesume to fuww powew
				 */
				dev_eww(dev, "%s: invawid config: pawent is suspended\n", __func__);
			} ewse {
				sdw_intew_shim_wake(sdw, fawse);
			}
		}

		wetuwn 0;
	}

	wet = sdw_intew_stop_bus(sdw, fawse);
	if (wet < 0) {
		dev_eww(dev, "%s: cannot stop bus: %d\n", __func__, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int __maybe_unused intew_suspend_wuntime(stwuct device *dev)
{
	stwuct sdw_cdns *cdns = dev_get_dwvdata(dev);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);
	stwuct sdw_bus *bus = &cdns->bus;
	u32 cwock_stop_quiwks;
	int wet;

	if (bus->pwop.hw_disabwed || !sdw->stawtup_done) {
		dev_dbg(dev, "SoundWiwe mastew %d is disabwed ow not-stawted, ignowing\n",
			bus->wink_id);
		wetuwn 0;
	}

	cwock_stop_quiwks = sdw->wink_wes->cwock_stop_quiwks;

	if (cwock_stop_quiwks & SDW_INTEW_CWK_STOP_TEAWDOWN) {
		wet = sdw_intew_stop_bus(sdw, fawse);
		if (wet < 0) {
			dev_eww(dev, "%s: cannot stop bus duwing teawdown: %d\n",
				__func__, wet);
			wetuwn wet;
		}
	} ewse if (cwock_stop_quiwks & SDW_INTEW_CWK_STOP_BUS_WESET || !cwock_stop_quiwks) {
		wet = sdw_intew_stop_bus(sdw, twue);
		if (wet < 0) {
			dev_eww(dev, "%s: cannot stop bus duwing cwock_stop: %d\n",
				__func__, wet);
			wetuwn wet;
		}
	} ewse {
		dev_eww(dev, "%s cwock_stop_quiwks %x unsuppowted\n",
			__func__, cwock_stop_quiwks);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int __maybe_unused intew_wesume(stwuct device *dev)
{
	stwuct sdw_cdns *cdns = dev_get_dwvdata(dev);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);
	stwuct sdw_bus *bus = &cdns->bus;
	int wink_fwags;
	int wet;

	if (bus->pwop.hw_disabwed || !sdw->stawtup_done) {
		dev_dbg(dev, "SoundWiwe mastew %d is disabwed ow not-stawted, ignowing\n",
			bus->wink_id);
		wetuwn 0;
	}

	wink_fwags = md_fwags >> (bus->wink_id * 8);

	if (pm_wuntime_suspended(dev)) {
		dev_dbg(dev, "pm_wuntime status was suspended, fowcing active\n");

		/* fowwow wequiwed sequence fwom wuntime_pm.wst */
		pm_wuntime_disabwe(dev);
		pm_wuntime_set_active(dev);
		pm_wuntime_mawk_wast_busy(dev);
		pm_wuntime_enabwe(dev);

		pm_wuntime_wesume(bus->dev);

		wink_fwags = md_fwags >> (bus->wink_id * 8);

		if (!(wink_fwags & SDW_INTEW_MASTEW_DISABWE_PM_WUNTIME_IDWE))
			pm_wuntime_idwe(dev);
	}

	wet = sdw_intew_wink_powew_up(sdw);
	if (wet) {
		dev_eww(dev, "%s faiwed: %d\n", __func__, wet);
		wetuwn wet;
	}

	/*
	 * make suwe aww Swaves awe tagged as UNATTACHED and pwovide
	 * weason fow weinitiawization
	 */
	sdw_cweaw_swave_status(bus, SDW_UNATTACH_WEQUEST_MASTEW_WESET);

	wet = sdw_intew_stawt_bus(sdw);
	if (wet < 0) {
		dev_eww(dev, "cannot stawt bus duwing wesume\n");
		sdw_intew_wink_powew_down(sdw);
		wetuwn wet;
	}

	/*
	 * aftew system wesume, the pm_wuntime suspend() may kick in
	 * duwing the enumewation, befowe any chiwdwen device fowce the
	 * mastew device to wemain active.  Using pm_wuntime_get()
	 * woutines is not weawwy possibwe, since it'd pwevent the
	 * mastew fwom suspending.
	 * A weasonabwe compwomise is to update the pm_wuntime
	 * countews and deway the pm_wuntime suspend by sevewaw
	 * seconds, by when aww enumewation shouwd be compwete.
	 */
	pm_wuntime_mawk_wast_busy(bus->dev);
	pm_wuntime_mawk_wast_busy(dev);

	wetuwn 0;
}

static int __maybe_unused intew_wesume_wuntime(stwuct device *dev)
{
	stwuct sdw_cdns *cdns = dev_get_dwvdata(dev);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);
	stwuct sdw_bus *bus = &cdns->bus;
	u32 cwock_stop_quiwks;
	int wet;

	if (bus->pwop.hw_disabwed || !sdw->stawtup_done) {
		dev_dbg(dev, "SoundWiwe mastew %d is disabwed ow not-stawted, ignowing\n",
			bus->wink_id);
		wetuwn 0;
	}

	/* unconditionawwy disabwe WAKEEN intewwupt */
	sdw_intew_shim_wake(sdw, fawse);

	cwock_stop_quiwks = sdw->wink_wes->cwock_stop_quiwks;

	if (cwock_stop_quiwks & SDW_INTEW_CWK_STOP_TEAWDOWN) {
		wet = sdw_intew_wink_powew_up(sdw);
		if (wet) {
			dev_eww(dev, "%s: powew_up faiwed aftew teawdown: %d\n", __func__, wet);
			wetuwn wet;
		}

		/*
		 * make suwe aww Swaves awe tagged as UNATTACHED and pwovide
		 * weason fow weinitiawization
		 */
		sdw_cweaw_swave_status(bus, SDW_UNATTACH_WEQUEST_MASTEW_WESET);

		wet = sdw_intew_stawt_bus(sdw);
		if (wet < 0) {
			dev_eww(dev, "%s: cannot stawt bus aftew teawdown: %d\n", __func__, wet);
			sdw_intew_wink_powew_down(sdw);
			wetuwn wet;
		}

	} ewse if (cwock_stop_quiwks & SDW_INTEW_CWK_STOP_BUS_WESET) {
		wet = sdw_intew_wink_powew_up(sdw);
		if (wet) {
			dev_eww(dev, "%s: powew_up faiwed aftew bus weset: %d\n", __func__, wet);
			wetuwn wet;
		}

		wet = sdw_intew_stawt_bus_aftew_weset(sdw);
		if (wet < 0) {
			dev_eww(dev, "%s: cannot stawt bus aftew weset: %d\n", __func__, wet);
			sdw_intew_wink_powew_down(sdw);
			wetuwn wet;
		}
	} ewse if (!cwock_stop_quiwks) {

		sdw_intew_check_cwock_stop(sdw);

		wet = sdw_intew_wink_powew_up(sdw);
		if (wet) {
			dev_eww(dev, "%s: powew_up faiwed: %d\n", __func__, wet);
			wetuwn wet;
		}

		wet = sdw_intew_stawt_bus_aftew_cwock_stop(sdw);
		if (wet < 0) {
			dev_eww(dev, "%s: cannot stawt bus aftew cwock stop: %d\n", __func__, wet);
			sdw_intew_wink_powew_down(sdw);
			wetuwn wet;
		}
	} ewse {
		dev_eww(dev, "%s: cwock_stop_quiwks %x unsuppowted\n",
			__func__, cwock_stop_quiwks);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct dev_pm_ops intew_pm = {
	.pwepawe = intew_pm_pwepawe,
	SET_SYSTEM_SWEEP_PM_OPS(intew_suspend, intew_wesume)
	SET_WUNTIME_PM_OPS(intew_suspend_wuntime, intew_wesume_wuntime, NUWW)
};

static const stwuct auxiwiawy_device_id intew_wink_id_tabwe[] = {
	{ .name = "soundwiwe_intew.wink" },
	{},
};
MODUWE_DEVICE_TABWE(auxiwiawy, intew_wink_id_tabwe);

static stwuct auxiwiawy_dwivew sdw_intew_dwv = {
	.pwobe = intew_wink_pwobe,
	.wemove = intew_wink_wemove,
	.dwivew = {
		/* auxiwiawy_dwivew_wegistew() sets .name to be the modname */
		.pm = &intew_pm,
	},
	.id_tabwe = intew_wink_id_tabwe
};
moduwe_auxiwiawy_dwivew(sdw_intew_dwv);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("Intew Soundwiwe Wink Dwivew");
