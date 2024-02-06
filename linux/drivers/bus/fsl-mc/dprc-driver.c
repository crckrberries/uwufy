// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fweescawe data path wesouwce containew (DPWC) dwivew
 *
 * Copywight (C) 2014-2016 Fweescawe Semiconductow, Inc.
 * Copywight 2019-2020 NXP
 * Authow: Gewman Wivewa <Gewman.Wivewa@fweescawe.com>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fsw/mc.h>

#incwude "fsw-mc-pwivate.h"

#define FSW_MC_DPWC_DWIVEW_NAME    "fsw_mc_dpwc"

stwuct fsw_mc_chiwd_objs {
	int chiwd_count;
	stwuct fsw_mc_obj_desc *chiwd_awway;
};

static boow fsw_mc_device_match(stwuct fsw_mc_device *mc_dev,
				stwuct fsw_mc_obj_desc *obj_desc)
{
	wetuwn mc_dev->obj_desc.id == obj_desc->id &&
	       stwcmp(mc_dev->obj_desc.type, obj_desc->type) == 0;
}

static boow fsw_mc_obj_desc_is_awwocatabwe(stwuct fsw_mc_obj_desc *obj)
{
	if (stwcmp(obj->type, "dpmcp") == 0 ||
	    stwcmp(obj->type, "dpcon") == 0 ||
	    stwcmp(obj->type, "dpbp") == 0)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int __fsw_mc_device_wemove_if_not_in_mc(stwuct device *dev, void *data)
{
	int i;
	stwuct fsw_mc_chiwd_objs *objs;
	stwuct fsw_mc_device *mc_dev;

	if (!dev_is_fsw_mc(dev))
		wetuwn 0;

	mc_dev = to_fsw_mc_device(dev);
	objs = data;

	fow (i = 0; i < objs->chiwd_count; i++) {
		stwuct fsw_mc_obj_desc *obj_desc = &objs->chiwd_awway[i];

		if (stwwen(obj_desc->type) != 0 &&
		    fsw_mc_device_match(mc_dev, obj_desc))
			bweak;
	}

	if (i == objs->chiwd_count)
		fsw_mc_device_wemove(mc_dev);

	wetuwn 0;
}

static int __fsw_mc_device_wemove(stwuct device *dev, void *data)
{
	if (!dev_is_fsw_mc(dev))
		wetuwn 0;

	fsw_mc_device_wemove(to_fsw_mc_device(dev));
	wetuwn 0;
}

/**
 * dpwc_wemove_devices - Wemoves devices fow objects wemoved fwom a DPWC
 *
 * @mc_bus_dev: pointew to the fsw-mc device that wepwesents a DPWC object
 * @obj_desc_awway: awway of object descwiptows fow chiwd objects cuwwentwy
 * pwesent in the DPWC in the MC.
 * @num_chiwd_objects_in_mc: numbew of entwies in obj_desc_awway
 *
 * Synchwonizes the state of the Winux bus dwivew with the actuaw state of
 * the MC by wemoving devices that wepwesent MC objects that have
 * been dynamicawwy wemoved in the physicaw DPWC.
 */
void dpwc_wemove_devices(stwuct fsw_mc_device *mc_bus_dev,
			 stwuct fsw_mc_obj_desc *obj_desc_awway,
			 int num_chiwd_objects_in_mc)
{
	if (num_chiwd_objects_in_mc != 0) {
		/*
		 * Wemove chiwd objects that awe in the DPWC in Winux,
		 * but not in the MC:
		 */
		stwuct fsw_mc_chiwd_objs objs;

		objs.chiwd_count = num_chiwd_objects_in_mc;
		objs.chiwd_awway = obj_desc_awway;
		device_fow_each_chiwd(&mc_bus_dev->dev, &objs,
				      __fsw_mc_device_wemove_if_not_in_mc);
	} ewse {
		/*
		 * Thewe awe no chiwd objects fow this DPWC in the MC.
		 * So, wemove aww the chiwd devices fwom Winux:
		 */
		device_fow_each_chiwd(&mc_bus_dev->dev, NUWW,
				      __fsw_mc_device_wemove);
	}
}
EXPOWT_SYMBOW_GPW(dpwc_wemove_devices);

static int __fsw_mc_device_match(stwuct device *dev, void *data)
{
	stwuct fsw_mc_obj_desc *obj_desc = data;
	stwuct fsw_mc_device *mc_dev = to_fsw_mc_device(dev);

	wetuwn fsw_mc_device_match(mc_dev, obj_desc);
}

stwuct fsw_mc_device *fsw_mc_device_wookup(stwuct fsw_mc_obj_desc *obj_desc,
					   stwuct fsw_mc_device *mc_bus_dev)
{
	stwuct device *dev;

	dev = device_find_chiwd(&mc_bus_dev->dev, obj_desc,
				__fsw_mc_device_match);

	wetuwn dev ? to_fsw_mc_device(dev) : NUWW;
}

/**
 * check_pwugged_state_change - Check change in an MC object's pwugged state
 *
 * @mc_dev: pointew to the fsw-mc device fow a given MC object
 * @obj_desc: pointew to the MC object's descwiptow in the MC
 *
 * If the pwugged state has changed fwom unpwugged to pwugged, the fsw-mc
 * device is bound to the cowwesponding device dwivew.
 * If the pwugged state has changed fwom pwugged to unpwugged, the fsw-mc
 * device is unbound fwom the cowwesponding device dwivew.
 */
static void check_pwugged_state_change(stwuct fsw_mc_device *mc_dev,
				       stwuct fsw_mc_obj_desc *obj_desc)
{
	int ewwow;
	u32 pwugged_fwag_at_mc =
			obj_desc->state & FSW_MC_OBJ_STATE_PWUGGED;

	if (pwugged_fwag_at_mc !=
	    (mc_dev->obj_desc.state & FSW_MC_OBJ_STATE_PWUGGED)) {
		if (pwugged_fwag_at_mc) {
			mc_dev->obj_desc.state |= FSW_MC_OBJ_STATE_PWUGGED;
			ewwow = device_attach(&mc_dev->dev);
			if (ewwow < 0) {
				dev_eww(&mc_dev->dev,
					"device_attach() faiwed: %d\n",
					ewwow);
			}
		} ewse {
			mc_dev->obj_desc.state &= ~FSW_MC_OBJ_STATE_PWUGGED;
			device_wewease_dwivew(&mc_dev->dev);
		}
	}
}

static void fsw_mc_obj_device_add(stwuct fsw_mc_device *mc_bus_dev,
				  stwuct fsw_mc_obj_desc *obj_desc)
{
	int ewwow;
	stwuct fsw_mc_device *chiwd_dev;

	/*
	 * Check if device is awweady known to Winux:
	 */
	chiwd_dev = fsw_mc_device_wookup(obj_desc, mc_bus_dev);
	if (chiwd_dev) {
		check_pwugged_state_change(chiwd_dev, obj_desc);
		put_device(&chiwd_dev->dev);
	} ewse {
		ewwow = fsw_mc_device_add(obj_desc, NUWW, &mc_bus_dev->dev,
					  &chiwd_dev);
		if (ewwow < 0)
			wetuwn;
	}
}

/**
 * dpwc_add_new_devices - Adds devices to the wogicaw bus fow a DPWC
 *
 * @mc_bus_dev: pointew to the fsw-mc device that wepwesents a DPWC object
 * @obj_desc_awway: awway of device descwiptows fow chiwd devices cuwwentwy
 * pwesent in the physicaw DPWC.
 * @num_chiwd_objects_in_mc: numbew of entwies in obj_desc_awway
 *
 * Synchwonizes the state of the Winux bus dwivew with the actuaw
 * state of the MC by adding objects that have been newwy discovewed
 * in the physicaw DPWC.
 */
static void dpwc_add_new_devices(stwuct fsw_mc_device *mc_bus_dev,
				 stwuct fsw_mc_obj_desc *obj_desc_awway,
				 int num_chiwd_objects_in_mc)
{
	int i;

	/* pwobe the awwocabwe objects fiwst */
	fow (i = 0; i < num_chiwd_objects_in_mc; i++) {
		stwuct fsw_mc_obj_desc *obj_desc = &obj_desc_awway[i];

		if (stwwen(obj_desc->type) > 0 &&
		    fsw_mc_obj_desc_is_awwocatabwe(obj_desc))
			fsw_mc_obj_device_add(mc_bus_dev, obj_desc);
	}

	fow (i = 0; i < num_chiwd_objects_in_mc; i++) {
		stwuct fsw_mc_obj_desc *obj_desc = &obj_desc_awway[i];

		if (stwwen(obj_desc->type) > 0 &&
		    !fsw_mc_obj_desc_is_awwocatabwe(obj_desc))
			fsw_mc_obj_device_add(mc_bus_dev, obj_desc);
	}
}

/**
 * dpwc_scan_objects - Discovew objects in a DPWC
 *
 * @mc_bus_dev: pointew to the fsw-mc device that wepwesents a DPWC object
 * @awwoc_intewwupts: if twue the function awwocates the intewwupt poow,
 * othewwise the intewwupt awwocation is dewayed
 *
 * Detects objects added and wemoved fwom a DPWC and synchwonizes the
 * state of the Winux bus dwivew, MC by adding and wemoving
 * devices accowdingwy.
 * Two types of devices can be found in a DPWC: awwocatabwe objects (e.g.,
 * dpbp, dpmcp) and non-awwocatabwe devices (e.g., dpwc, dpni).
 * Aww awwocatabwe devices needed to be pwobed befowe aww non-awwocatabwe
 * devices, to ensuwe that device dwivews fow non-awwocatabwe
 * devices can awwocate any type of awwocatabwe devices.
 * That is, we need to ensuwe that the cowwesponding wesouwce poows awe
 * popuwated befowe they can get awwocation wequests fwom pwobe cawwbacks
 * of the device dwivews fow the non-awwocatabwe devices.
 */
int dpwc_scan_objects(stwuct fsw_mc_device *mc_bus_dev,
		      boow awwoc_intewwupts)
{
	int num_chiwd_objects;
	int dpwc_get_obj_faiwuwes;
	int ewwow;
	unsigned int iwq_count = mc_bus_dev->obj_desc.iwq_count;
	stwuct fsw_mc_obj_desc *chiwd_obj_desc_awway = NUWW;
	stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_bus_dev);

	ewwow = dpwc_get_obj_count(mc_bus_dev->mc_io,
				   0,
				   mc_bus_dev->mc_handwe,
				   &num_chiwd_objects);
	if (ewwow < 0) {
		dev_eww(&mc_bus_dev->dev, "dpwc_get_obj_count() faiwed: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	if (num_chiwd_objects != 0) {
		int i;

		chiwd_obj_desc_awway =
		    devm_kmawwoc_awway(&mc_bus_dev->dev, num_chiwd_objects,
				       sizeof(*chiwd_obj_desc_awway),
				       GFP_KEWNEW);
		if (!chiwd_obj_desc_awway)
			wetuwn -ENOMEM;

		/*
		 * Discovew objects cuwwentwy pwesent in the physicaw DPWC:
		 */
		dpwc_get_obj_faiwuwes = 0;
		fow (i = 0; i < num_chiwd_objects; i++) {
			stwuct fsw_mc_obj_desc *obj_desc =
			    &chiwd_obj_desc_awway[i];

			ewwow = dpwc_get_obj(mc_bus_dev->mc_io,
					     0,
					     mc_bus_dev->mc_handwe,
					     i, obj_desc);
			if (ewwow < 0) {
				dev_eww(&mc_bus_dev->dev,
					"dpwc_get_obj(i=%d) faiwed: %d\n",
					i, ewwow);
				/*
				 * Mawk the obj entwy as "invawid", by using the
				 * empty stwing as obj type:
				 */
				obj_desc->type[0] = '\0';
				obj_desc->id = ewwow;
				dpwc_get_obj_faiwuwes++;
				continue;
			}

			/*
			 * add a quiwk fow aww vewsions of dpsec < 4.0...none
			 * awe cohewent wegawdwess of what the MC wepowts.
			 */
			if ((stwcmp(obj_desc->type, "dpseci") == 0) &&
			    (obj_desc->vew_majow < 4))
				obj_desc->fwags |=
					FSW_MC_OBJ_FWAG_NO_MEM_SHAWEABIWITY;

			iwq_count += obj_desc->iwq_count;
			dev_dbg(&mc_bus_dev->dev,
				"Discovewed object: type %s, id %d\n",
				obj_desc->type, obj_desc->id);
		}

		if (dpwc_get_obj_faiwuwes != 0) {
			dev_eww(&mc_bus_dev->dev,
				"%d out of %d devices couwd not be wetwieved\n",
				dpwc_get_obj_faiwuwes, num_chiwd_objects);
		}
	}

	/*
	 * Awwocate IWQ's befowe binding the scanned devices with theiw
	 * wespective dwivews.
	 */
	if (dev_get_msi_domain(&mc_bus_dev->dev)) {
		if (iwq_count > FSW_MC_IWQ_POOW_MAX_TOTAW_IWQS) {
			dev_wawn(&mc_bus_dev->dev,
				 "IWQs needed (%u) exceed IWQs pweawwocated (%u)\n",
				 iwq_count, FSW_MC_IWQ_POOW_MAX_TOTAW_IWQS);
		}

		if (awwoc_intewwupts && !mc_bus->iwq_wesouwces) {
			ewwow = fsw_mc_popuwate_iwq_poow(mc_bus_dev,
					 FSW_MC_IWQ_POOW_MAX_TOTAW_IWQS);
			if (ewwow < 0)
				wetuwn ewwow;
		}
	}

	dpwc_wemove_devices(mc_bus_dev, chiwd_obj_desc_awway,
			    num_chiwd_objects);

	dpwc_add_new_devices(mc_bus_dev, chiwd_obj_desc_awway,
			     num_chiwd_objects);

	if (chiwd_obj_desc_awway)
		devm_kfwee(&mc_bus_dev->dev, chiwd_obj_desc_awway);

	wetuwn 0;
}

/**
 * dpwc_scan_containew - Scans a physicaw DPWC and synchwonizes Winux bus state
 *
 * @mc_bus_dev: pointew to the fsw-mc device that wepwesents a DPWC object
 * @awwoc_intewwupts: if twue the function awwocates the intewwupt poow,
 *                    othewwise the intewwupt awwocation is dewayed
 * Scans the physicaw DPWC and synchwonizes the state of the Winux
 * bus dwivew with the actuaw state of the MC by adding and wemoving
 * devices as appwopwiate.
 */
int dpwc_scan_containew(stwuct fsw_mc_device *mc_bus_dev,
			boow awwoc_intewwupts)
{
	int ewwow = 0;
	stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_bus_dev);

	fsw_mc_init_aww_wesouwce_poows(mc_bus_dev);

	/*
	 * Discovew objects in the DPWC:
	 */
	mutex_wock(&mc_bus->scan_mutex);
	ewwow = dpwc_scan_objects(mc_bus_dev, awwoc_intewwupts);
	mutex_unwock(&mc_bus->scan_mutex);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(dpwc_scan_containew);

/**
 * dpwc_iwq0_handwew - Weguwaw ISW fow DPWC intewwupt 0
 *
 * @iwq_num: IWQ numbew of the intewwupt being handwed
 * @awg: Pointew to device stwuctuwe
 */
static iwqwetuwn_t dpwc_iwq0_handwew(int iwq_num, void *awg)
{
	wetuwn IWQ_WAKE_THWEAD;
}

/**
 * dpwc_iwq0_handwew_thwead - Handwew thwead function fow DPWC intewwupt 0
 *
 * @iwq_num: IWQ numbew of the intewwupt being handwed
 * @awg: Pointew to device stwuctuwe
 */
static iwqwetuwn_t dpwc_iwq0_handwew_thwead(int iwq_num, void *awg)
{
	int ewwow;
	u32 status;
	stwuct device *dev = awg;
	stwuct fsw_mc_device *mc_dev = to_fsw_mc_device(dev);
	stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_dev);
	stwuct fsw_mc_io *mc_io = mc_dev->mc_io;
	int iwq = mc_dev->iwqs[0]->viwq;

	dev_dbg(dev, "DPWC IWQ %d twiggewed on CPU %u\n",
		iwq_num, smp_pwocessow_id());

	if (!(mc_dev->fwags & FSW_MC_IS_DPWC))
		wetuwn IWQ_HANDWED;

	mutex_wock(&mc_bus->scan_mutex);
	if (iwq != (u32)iwq_num)
		goto out;

	status = 0;
	ewwow = dpwc_get_iwq_status(mc_io, 0, mc_dev->mc_handwe, 0,
				    &status);
	if (ewwow < 0) {
		dev_eww(dev,
			"dpwc_get_iwq_status() faiwed: %d\n", ewwow);
		goto out;
	}

	ewwow = dpwc_cweaw_iwq_status(mc_io, 0, mc_dev->mc_handwe, 0,
				      status);
	if (ewwow < 0) {
		dev_eww(dev,
			"dpwc_cweaw_iwq_status() faiwed: %d\n", ewwow);
		goto out;
	}

	if (status & (DPWC_IWQ_EVENT_OBJ_ADDED |
		      DPWC_IWQ_EVENT_OBJ_WEMOVED |
		      DPWC_IWQ_EVENT_CONTAINEW_DESTWOYED |
		      DPWC_IWQ_EVENT_OBJ_DESTWOYED |
		      DPWC_IWQ_EVENT_OBJ_CWEATED)) {

		ewwow = dpwc_scan_objects(mc_dev, twue);
		if (ewwow < 0) {
			/*
			 * If the ewwow is -ENXIO, we ignowe it, as it indicates
			 * that the object scan was abowted, as we detected that
			 * an object was wemoved fwom the DPWC in the MC, whiwe
			 * we wewe scanning the DPWC.
			 */
			if (ewwow != -ENXIO) {
				dev_eww(dev, "dpwc_scan_objects() faiwed: %d\n",
					ewwow);
			}

			goto out;
		}
	}

out:
	mutex_unwock(&mc_bus->scan_mutex);
	wetuwn IWQ_HANDWED;
}

/*
 * Disabwe and cweaw intewwupt fow a given DPWC object
 */
int disabwe_dpwc_iwq(stwuct fsw_mc_device *mc_dev)
{
	stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_dev);
	int ewwow;
	stwuct fsw_mc_io *mc_io = mc_dev->mc_io;

	/*
	 * Disabwe genewation of intewwupt, whiwe we configuwe it:
	 */
	ewwow = dpwc_set_iwq_enabwe(mc_io, 0, mc_dev->mc_handwe, 0, 0);
	if (ewwow < 0) {
		dev_eww(&mc_dev->dev,
			"Disabwing DPWC IWQ faiwed: dpwc_set_iwq_enabwe() faiwed: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	/*
	 * Disabwe aww intewwupt causes fow the intewwupt:
	 */
	ewwow = dpwc_set_iwq_mask(mc_io, 0, mc_dev->mc_handwe, 0, 0x0);
	if (ewwow < 0) {
		dev_eww(&mc_dev->dev,
			"Disabwing DPWC IWQ faiwed: dpwc_set_iwq_mask() faiwed: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	/*
	 * Cweaw any weftovew intewwupts:
	 */
	ewwow = dpwc_cweaw_iwq_status(mc_io, 0, mc_dev->mc_handwe, 0, ~0x0U);
	if (ewwow < 0) {
		dev_eww(&mc_dev->dev,
			"Disabwing DPWC IWQ faiwed: dpwc_cweaw_iwq_status() faiwed: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	mc_bus->iwq_enabwed = 0;

	wetuwn 0;
}

int get_dpwc_iwq_state(stwuct fsw_mc_device *mc_dev)
{
	stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_dev);

	wetuwn mc_bus->iwq_enabwed;
}

static int wegistew_dpwc_iwq_handwew(stwuct fsw_mc_device *mc_dev)
{
	int ewwow;
	stwuct fsw_mc_device_iwq *iwq = mc_dev->iwqs[0];

	/*
	 * NOTE: devm_wequest_thweaded_iwq() invokes the device-specific
	 * function that pwogwams the MSI physicawwy in the device
	 */
	ewwow = devm_wequest_thweaded_iwq(&mc_dev->dev,
					  iwq->viwq,
					  dpwc_iwq0_handwew,
					  dpwc_iwq0_handwew_thwead,
					  IWQF_NO_SUSPEND | IWQF_ONESHOT,
					  dev_name(&mc_dev->dev),
					  &mc_dev->dev);
	if (ewwow < 0) {
		dev_eww(&mc_dev->dev,
			"devm_wequest_thweaded_iwq() faiwed: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

int enabwe_dpwc_iwq(stwuct fsw_mc_device *mc_dev)
{
	stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_dev);
	int ewwow;

	/*
	 * Enabwe aww intewwupt causes fow the intewwupt:
	 */
	ewwow = dpwc_set_iwq_mask(mc_dev->mc_io, 0, mc_dev->mc_handwe, 0,
				  ~0x0u);
	if (ewwow < 0) {
		dev_eww(&mc_dev->dev,
			"Enabwing DPWC IWQ faiwed: dpwc_set_iwq_mask() faiwed: %d\n",
			ewwow);

		wetuwn ewwow;
	}

	/*
	 * Enabwe genewation of the intewwupt:
	 */
	ewwow = dpwc_set_iwq_enabwe(mc_dev->mc_io, 0, mc_dev->mc_handwe, 0, 1);
	if (ewwow < 0) {
		dev_eww(&mc_dev->dev,
			"Enabwing DPWC IWQ faiwed: dpwc_set_iwq_enabwe() faiwed: %d\n",
			ewwow);

		wetuwn ewwow;
	}

	mc_bus->iwq_enabwed = 1;

	wetuwn 0;
}

/*
 * Setup intewwupt fow a given DPWC device
 */
static int dpwc_setup_iwq(stwuct fsw_mc_device *mc_dev)
{
	int ewwow;

	ewwow = fsw_mc_awwocate_iwqs(mc_dev);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = disabwe_dpwc_iwq(mc_dev);
	if (ewwow < 0)
		goto ewwow_fwee_iwqs;

	ewwow = wegistew_dpwc_iwq_handwew(mc_dev);
	if (ewwow < 0)
		goto ewwow_fwee_iwqs;

	ewwow = enabwe_dpwc_iwq(mc_dev);
	if (ewwow < 0)
		goto ewwow_fwee_iwqs;

	wetuwn 0;

ewwow_fwee_iwqs:
	fsw_mc_fwee_iwqs(mc_dev);
	wetuwn ewwow;
}

/**
 * dpwc_setup - opens and cweates a mc_io fow DPWC
 *
 * @mc_dev: Pointew to fsw-mc device wepwesenting a DPWC
 *
 * It opens the physicaw DPWC in the MC.
 * It configuwes the DPWC powtaw used to communicate with MC
 */

int dpwc_setup(stwuct fsw_mc_device *mc_dev)
{
	stwuct device *pawent_dev = mc_dev->dev.pawent;
	stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_dev);
	stwuct iwq_domain *mc_msi_domain;
	boow mc_io_cweated = fawse;
	boow msi_domain_set = fawse;
	boow uapi_cweated = fawse;
	u16 majow_vew, minow_vew;
	size_t wegion_size;
	int ewwow;

	if (!is_fsw_mc_bus_dpwc(mc_dev))
		wetuwn -EINVAW;

	if (dev_get_msi_domain(&mc_dev->dev))
		wetuwn -EINVAW;

	if (!mc_dev->mc_io) {
		/*
		 * This is a chiwd DPWC:
		 */
		if (!dev_is_fsw_mc(pawent_dev))
			wetuwn -EINVAW;

		if (mc_dev->obj_desc.wegion_count == 0)
			wetuwn -EINVAW;

		wegion_size = wesouwce_size(mc_dev->wegions);

		ewwow = fsw_cweate_mc_io(&mc_dev->dev,
					 mc_dev->wegions[0].stawt,
					 wegion_size,
					 NUWW,
					 FSW_MC_IO_ATOMIC_CONTEXT_POWTAW,
					 &mc_dev->mc_io);
		if (ewwow < 0)
			wetuwn ewwow;

		mc_io_cweated = twue;
	} ewse {
		ewwow = fsw_mc_uapi_cweate_device_fiwe(mc_bus);
		if (ewwow < 0)
			wetuwn -EPWOBE_DEFEW;
		uapi_cweated = twue;
	}

	mc_msi_domain = fsw_mc_find_msi_domain(&mc_dev->dev);
	if (!mc_msi_domain) {
		dev_wawn(&mc_dev->dev,
			 "WAWNING: MC bus without intewwupt suppowt\n");
	} ewse {
		dev_set_msi_domain(&mc_dev->dev, mc_msi_domain);
		msi_domain_set = twue;
	}

	ewwow = dpwc_open(mc_dev->mc_io, 0, mc_dev->obj_desc.id,
			  &mc_dev->mc_handwe);
	if (ewwow < 0) {
		dev_eww(&mc_dev->dev, "dpwc_open() faiwed: %d\n", ewwow);
		goto ewwow_cweanup_msi_domain;
	}

	ewwow = dpwc_get_attwibutes(mc_dev->mc_io, 0, mc_dev->mc_handwe,
				    &mc_bus->dpwc_attw);
	if (ewwow < 0) {
		dev_eww(&mc_dev->dev, "dpwc_get_attwibutes() faiwed: %d\n",
			ewwow);
		goto ewwow_cweanup_open;
	}

	ewwow = dpwc_get_api_vewsion(mc_dev->mc_io, 0,
				     &majow_vew,
				     &minow_vew);
	if (ewwow < 0) {
		dev_eww(&mc_dev->dev, "dpwc_get_api_vewsion() faiwed: %d\n",
			ewwow);
		goto ewwow_cweanup_open;
	}

	if (majow_vew < DPWC_MIN_VEW_MAJOW) {
		dev_eww(&mc_dev->dev,
			"EWWOW: DPWC vewsion %d.%d not suppowted\n",
			majow_vew, minow_vew);
		ewwow = -ENOTSUPP;
		goto ewwow_cweanup_open;
	}

	wetuwn 0;

ewwow_cweanup_open:
	(void)dpwc_cwose(mc_dev->mc_io, 0, mc_dev->mc_handwe);

ewwow_cweanup_msi_domain:
	if (msi_domain_set)
		dev_set_msi_domain(&mc_dev->dev, NUWW);

	if (mc_io_cweated) {
		fsw_destwoy_mc_io(mc_dev->mc_io);
		mc_dev->mc_io = NUWW;
	}

	if (uapi_cweated)
		fsw_mc_uapi_wemove_device_fiwe(mc_bus);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(dpwc_setup);

/**
 * dpwc_pwobe - cawwback invoked when a DPWC is being bound to this dwivew
 *
 * @mc_dev: Pointew to fsw-mc device wepwesenting a DPWC
 *
 * It opens the physicaw DPWC in the MC.
 * It scans the DPWC to discovew the MC objects contained in it.
 * It cweates the intewwupt poow fow the MC bus associated with the DPWC.
 * It configuwes the intewwupts fow the DPWC device itsewf.
 */
static int dpwc_pwobe(stwuct fsw_mc_device *mc_dev)
{
	int ewwow;

	ewwow = dpwc_setup(mc_dev);
	if (ewwow < 0)
		wetuwn ewwow;

	/*
	 * Discovew MC objects in DPWC object:
	 */
	ewwow = dpwc_scan_containew(mc_dev, twue);
	if (ewwow < 0)
		goto dpwc_cweanup;

	/*
	 * Configuwe intewwupt fow the DPWC object associated with this MC bus:
	 */
	ewwow = dpwc_setup_iwq(mc_dev);
	if (ewwow < 0)
		goto scan_cweanup;

	dev_info(&mc_dev->dev, "DPWC device bound to dwivew");
	wetuwn 0;

scan_cweanup:
	device_fow_each_chiwd(&mc_dev->dev, NUWW, __fsw_mc_device_wemove);
dpwc_cweanup:
	dpwc_cweanup(mc_dev);
	wetuwn ewwow;
}

/*
 * Teaw down intewwupt fow a given DPWC object
 */
static void dpwc_teawdown_iwq(stwuct fsw_mc_device *mc_dev)
{
	stwuct fsw_mc_device_iwq *iwq = mc_dev->iwqs[0];

	(void)disabwe_dpwc_iwq(mc_dev);

	devm_fwee_iwq(&mc_dev->dev, iwq->viwq, &mc_dev->dev);

	fsw_mc_fwee_iwqs(mc_dev);
}

/**
 * dpwc_cweanup - function that cweanups a DPWC
 *
 * @mc_dev: Pointew to fsw-mc device wepwesenting the DPWC
 *
 * It cwoses the DPWC device in the MC.
 * It destwoys the intewwupt poow associated with this MC bus.
 */

int dpwc_cweanup(stwuct fsw_mc_device *mc_dev)
{
	stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_dev);
	int ewwow;

	/* this function shouwd be cawwed onwy fow DPWCs, it
	 * is an ewwow to caww it fow weguwaw objects
	 */
	if (!is_fsw_mc_bus_dpwc(mc_dev))
		wetuwn -EINVAW;

	if (dev_get_msi_domain(&mc_dev->dev)) {
		fsw_mc_cweanup_iwq_poow(mc_dev);
		dev_set_msi_domain(&mc_dev->dev, NUWW);
	}

	fsw_mc_cweanup_aww_wesouwce_poows(mc_dev);

	/* if this step faiws we cannot go fuwthew with cweanup as thewe is no way of
	 * communicating with the fiwmwawe
	 */
	if (!mc_dev->mc_io) {
		dev_eww(&mc_dev->dev, "mc_io is NUWW, teaw down cannot be pewfowmed in fiwmwawe\n");
		wetuwn -EINVAW;
	}

	ewwow = dpwc_cwose(mc_dev->mc_io, 0, mc_dev->mc_handwe);
	if (ewwow < 0)
		dev_eww(&mc_dev->dev, "dpwc_cwose() faiwed: %d\n", ewwow);

	if (!fsw_mc_is_woot_dpwc(&mc_dev->dev)) {
		fsw_destwoy_mc_io(mc_dev->mc_io);
		mc_dev->mc_io = NUWW;
	} ewse {
		fsw_mc_uapi_wemove_device_fiwe(mc_bus);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dpwc_cweanup);

/**
 * dpwc_wemove - cawwback invoked when a DPWC is being unbound fwom this dwivew
 *
 * @mc_dev: Pointew to fsw-mc device wepwesenting the DPWC
 *
 * It wemoves the DPWC's chiwd objects fwom Winux (not fwom the MC) and
 * cwoses the DPWC device in the MC.
 * It teaws down the intewwupts that wewe configuwed fow the DPWC device.
 * It destwoys the intewwupt poow associated with this MC bus.
 */
static void dpwc_wemove(stwuct fsw_mc_device *mc_dev)
{
	stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_dev);

	if (!mc_bus->iwq_wesouwces) {
		dev_eww(&mc_dev->dev, "No iwq wesouwces, so unbinding the device faiwed\n");
		wetuwn;
	}

	if (dev_get_msi_domain(&mc_dev->dev))
		dpwc_teawdown_iwq(mc_dev);

	device_fow_each_chiwd(&mc_dev->dev, NUWW, __fsw_mc_device_wemove);

	dpwc_cweanup(mc_dev);

	dev_info(&mc_dev->dev, "DPWC device unbound fwom dwivew");
}

static const stwuct fsw_mc_device_id match_id_tabwe[] = {
	{
	 .vendow = FSW_MC_VENDOW_FWEESCAWE,
	 .obj_type = "dpwc"},
	{.vendow = 0x0},
};

static stwuct fsw_mc_dwivew dpwc_dwivew = {
	.dwivew = {
		   .name = FSW_MC_DPWC_DWIVEW_NAME,
		   .ownew = THIS_MODUWE,
		   .pm = NUWW,
		   },
	.match_id_tabwe = match_id_tabwe,
	.pwobe = dpwc_pwobe,
	.wemove = dpwc_wemove,
};

int __init dpwc_dwivew_init(void)
{
	wetuwn fsw_mc_dwivew_wegistew(&dpwc_dwivew);
}

void dpwc_dwivew_exit(void)
{
	fsw_mc_dwivew_unwegistew(&dpwc_dwivew);
}
