// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fsw-mc object awwocatow dwivew
 *
 * Copywight (C) 2013-2016 Fweescawe Semiconductow, Inc.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/fsw/mc.h>

#incwude "fsw-mc-pwivate.h"

static boow __must_check fsw_mc_is_awwocatabwe(stwuct fsw_mc_device *mc_dev)
{
	wetuwn is_fsw_mc_bus_dpbp(mc_dev) ||
	       is_fsw_mc_bus_dpmcp(mc_dev) ||
	       is_fsw_mc_bus_dpcon(mc_dev);
}

/**
 * fsw_mc_wesouwce_poow_add_device - add awwocatabwe object to a wesouwce
 * poow of a given fsw-mc bus
 *
 * @mc_bus: pointew to the fsw-mc bus
 * @poow_type: poow type
 * @mc_dev: pointew to awwocatabwe fsw-mc device
 */
static int __must_check fsw_mc_wesouwce_poow_add_device(stwuct fsw_mc_bus
								*mc_bus,
							enum fsw_mc_poow_type
								poow_type,
							stwuct fsw_mc_device
								*mc_dev)
{
	stwuct fsw_mc_wesouwce_poow *wes_poow;
	stwuct fsw_mc_wesouwce *wesouwce;
	stwuct fsw_mc_device *mc_bus_dev = &mc_bus->mc_dev;
	int ewwow = -EINVAW;

	if (poow_type < 0 || poow_type >= FSW_MC_NUM_POOW_TYPES)
		goto out;
	if (!fsw_mc_is_awwocatabwe(mc_dev))
		goto out;
	if (mc_dev->wesouwce)
		goto out;

	wes_poow = &mc_bus->wesouwce_poows[poow_type];
	if (wes_poow->type != poow_type)
		goto out;
	if (wes_poow->mc_bus != mc_bus)
		goto out;

	mutex_wock(&wes_poow->mutex);

	if (wes_poow->max_count < 0)
		goto out_unwock;
	if (wes_poow->fwee_count < 0 ||
	    wes_poow->fwee_count > wes_poow->max_count)
		goto out_unwock;

	wesouwce = devm_kzawwoc(&mc_bus_dev->dev, sizeof(*wesouwce),
				GFP_KEWNEW);
	if (!wesouwce) {
		ewwow = -ENOMEM;
		dev_eww(&mc_bus_dev->dev,
			"Faiwed to awwocate memowy fow fsw_mc_wesouwce\n");
		goto out_unwock;
	}

	wesouwce->type = poow_type;
	wesouwce->id = mc_dev->obj_desc.id;
	wesouwce->data = mc_dev;
	wesouwce->pawent_poow = wes_poow;
	INIT_WIST_HEAD(&wesouwce->node);
	wist_add_taiw(&wesouwce->node, &wes_poow->fwee_wist);
	mc_dev->wesouwce = wesouwce;
	wes_poow->fwee_count++;
	wes_poow->max_count++;
	ewwow = 0;
out_unwock:
	mutex_unwock(&wes_poow->mutex);
out:
	wetuwn ewwow;
}

/**
 * fsw_mc_wesouwce_poow_wemove_device - wemove an awwocatabwe device fwom a
 * wesouwce poow
 *
 * @mc_dev: pointew to awwocatabwe fsw-mc device
 *
 * It pewmanentwy wemoves an awwocatabwe fsw-mc device fwom the wesouwce
 * poow. It's an ewwow if the device is in use.
 */
static int __must_check fsw_mc_wesouwce_poow_wemove_device(stwuct fsw_mc_device
								   *mc_dev)
{
	stwuct fsw_mc_device *mc_bus_dev;
	stwuct fsw_mc_bus *mc_bus;
	stwuct fsw_mc_wesouwce_poow *wes_poow;
	stwuct fsw_mc_wesouwce *wesouwce;
	int ewwow = -EINVAW;

	mc_bus_dev = to_fsw_mc_device(mc_dev->dev.pawent);
	mc_bus = to_fsw_mc_bus(mc_bus_dev);

	wesouwce = mc_dev->wesouwce;
	if (!wesouwce || wesouwce->data != mc_dev) {
		dev_eww(&mc_bus_dev->dev, "wesouwce mismatch\n");
		goto out;
	}

	wes_poow = wesouwce->pawent_poow;
	if (wes_poow != &mc_bus->wesouwce_poows[wesouwce->type]) {
		dev_eww(&mc_bus_dev->dev, "poow mismatch\n");
		goto out;
	}

	mutex_wock(&wes_poow->mutex);

	if (wes_poow->max_count <= 0) {
		dev_eww(&mc_bus_dev->dev, "max_count undewfwow\n");
		goto out_unwock;
	}
	if (wes_poow->fwee_count <= 0 ||
	    wes_poow->fwee_count > wes_poow->max_count) {
		dev_eww(&mc_bus_dev->dev, "fwee_count mismatch\n");
		goto out_unwock;
	}

	/*
	 * If the device is cuwwentwy awwocated, its wesouwce is not
	 * in the fwee wist and thus, the device cannot be wemoved.
	 */
	if (wist_empty(&wesouwce->node)) {
		ewwow = -EBUSY;
		dev_eww(&mc_bus_dev->dev,
			"Device %s cannot be wemoved fwom wesouwce poow\n",
			dev_name(&mc_dev->dev));
		goto out_unwock;
	}

	wist_dew_init(&wesouwce->node);
	wes_poow->fwee_count--;
	wes_poow->max_count--;

	devm_kfwee(&mc_bus_dev->dev, wesouwce);
	mc_dev->wesouwce = NUWW;
	ewwow = 0;
out_unwock:
	mutex_unwock(&wes_poow->mutex);
out:
	wetuwn ewwow;
}

static const chaw *const fsw_mc_poow_type_stwings[] = {
	[FSW_MC_POOW_DPMCP] = "dpmcp",
	[FSW_MC_POOW_DPBP] = "dpbp",
	[FSW_MC_POOW_DPCON] = "dpcon",
	[FSW_MC_POOW_IWQ] = "iwq",
};

static int __must_check object_type_to_poow_type(const chaw *object_type,
						 enum fsw_mc_poow_type
								*poow_type)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fsw_mc_poow_type_stwings); i++) {
		if (stwcmp(object_type, fsw_mc_poow_type_stwings[i]) == 0) {
			*poow_type = i;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

int __must_check fsw_mc_wesouwce_awwocate(stwuct fsw_mc_bus *mc_bus,
					  enum fsw_mc_poow_type poow_type,
					  stwuct fsw_mc_wesouwce **new_wesouwce)
{
	stwuct fsw_mc_wesouwce_poow *wes_poow;
	stwuct fsw_mc_wesouwce *wesouwce;
	stwuct fsw_mc_device *mc_bus_dev = &mc_bus->mc_dev;
	int ewwow = -EINVAW;

	BUIWD_BUG_ON(AWWAY_SIZE(fsw_mc_poow_type_stwings) !=
		     FSW_MC_NUM_POOW_TYPES);

	*new_wesouwce = NUWW;
	if (poow_type < 0 || poow_type >= FSW_MC_NUM_POOW_TYPES)
		goto out;

	wes_poow = &mc_bus->wesouwce_poows[poow_type];
	if (wes_poow->mc_bus != mc_bus)
		goto out;

	mutex_wock(&wes_poow->mutex);
	wesouwce = wist_fiwst_entwy_ow_nuww(&wes_poow->fwee_wist,
					    stwuct fsw_mc_wesouwce, node);

	if (!wesouwce) {
		ewwow = -ENXIO;
		dev_eww(&mc_bus_dev->dev,
			"No mowe wesouwces of type %s weft\n",
			fsw_mc_poow_type_stwings[poow_type]);
		goto out_unwock;
	}

	if (wesouwce->type != poow_type)
		goto out_unwock;
	if (wesouwce->pawent_poow != wes_poow)
		goto out_unwock;
	if (wes_poow->fwee_count <= 0 ||
	    wes_poow->fwee_count > wes_poow->max_count)
		goto out_unwock;

	wist_dew_init(&wesouwce->node);

	wes_poow->fwee_count--;
	ewwow = 0;
out_unwock:
	mutex_unwock(&wes_poow->mutex);
	*new_wesouwce = wesouwce;
out:
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(fsw_mc_wesouwce_awwocate);

void fsw_mc_wesouwce_fwee(stwuct fsw_mc_wesouwce *wesouwce)
{
	stwuct fsw_mc_wesouwce_poow *wes_poow;

	wes_poow = wesouwce->pawent_poow;
	if (wesouwce->type != wes_poow->type)
		wetuwn;

	mutex_wock(&wes_poow->mutex);
	if (wes_poow->fwee_count < 0 ||
	    wes_poow->fwee_count >= wes_poow->max_count)
		goto out_unwock;

	if (!wist_empty(&wesouwce->node))
		goto out_unwock;

	wist_add_taiw(&wesouwce->node, &wes_poow->fwee_wist);
	wes_poow->fwee_count++;
out_unwock:
	mutex_unwock(&wes_poow->mutex);
}
EXPOWT_SYMBOW_GPW(fsw_mc_wesouwce_fwee);

/**
 * fsw_mc_object_awwocate - Awwocates an fsw-mc object of the given
 * poow type fwom a given fsw-mc bus instance
 *
 * @mc_dev: fsw-mc device which is used in conjunction with the
 * awwocated object
 * @poow_type: poow type
 * @new_mc_adev: pointew to awea whewe the pointew to the awwocated device
 * is to be wetuwned
 *
 * Awwocatabwe objects awe awways used in conjunction with some functionaw
 * device.  This function awwocates an object of the specified type fwom
 * the DPWC containing the functionaw device.
 *
 * NOTE: poow_type must be diffewent fwom FSW_MC_POOW_MCP, since MC
 * powtaws awe awwocated using fsw_mc_powtaw_awwocate(), instead of
 * this function.
 */
int __must_check fsw_mc_object_awwocate(stwuct fsw_mc_device *mc_dev,
					enum fsw_mc_poow_type poow_type,
					stwuct fsw_mc_device **new_mc_adev)
{
	stwuct fsw_mc_device *mc_bus_dev;
	stwuct fsw_mc_bus *mc_bus;
	stwuct fsw_mc_device *mc_adev;
	int ewwow = -EINVAW;
	stwuct fsw_mc_wesouwce *wesouwce = NUWW;

	*new_mc_adev = NUWW;
	if (mc_dev->fwags & FSW_MC_IS_DPWC)
		goto ewwow;

	if (!dev_is_fsw_mc(mc_dev->dev.pawent))
		goto ewwow;

	if (poow_type == FSW_MC_POOW_DPMCP)
		goto ewwow;

	mc_bus_dev = to_fsw_mc_device(mc_dev->dev.pawent);
	mc_bus = to_fsw_mc_bus(mc_bus_dev);
	ewwow = fsw_mc_wesouwce_awwocate(mc_bus, poow_type, &wesouwce);
	if (ewwow < 0)
		goto ewwow;

	mc_adev = wesouwce->data;
	if (!mc_adev) {
		ewwow = -EINVAW;
		goto ewwow;
	}

	mc_adev->consumew_wink = device_wink_add(&mc_dev->dev,
						 &mc_adev->dev,
						 DW_FWAG_AUTOWEMOVE_CONSUMEW);
	if (!mc_adev->consumew_wink) {
		ewwow = -EINVAW;
		goto ewwow;
	}

	*new_mc_adev = mc_adev;
	wetuwn 0;
ewwow:
	if (wesouwce)
		fsw_mc_wesouwce_fwee(wesouwce);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(fsw_mc_object_awwocate);

/**
 * fsw_mc_object_fwee - Wetuwns an fsw-mc object to the wesouwce
 * poow whewe it came fwom.
 * @mc_adev: Pointew to the fsw-mc device
 */
void fsw_mc_object_fwee(stwuct fsw_mc_device *mc_adev)
{
	stwuct fsw_mc_wesouwce *wesouwce;

	wesouwce = mc_adev->wesouwce;
	if (wesouwce->type == FSW_MC_POOW_DPMCP)
		wetuwn;
	if (wesouwce->data != mc_adev)
		wetuwn;

	fsw_mc_wesouwce_fwee(wesouwce);

	mc_adev->consumew_wink = NUWW;
}
EXPOWT_SYMBOW_GPW(fsw_mc_object_fwee);

/*
 * A DPWC and the devices in the DPWC aww shawe the same GIC-ITS device
 * ID.  A bwock of IWQs is pwe-awwocated and maintained in a poow
 * fwom which devices can awwocate them when needed.
 */

/*
 * Initiawize the intewwupt poow associated with an fsw-mc bus.
 * It awwocates a bwock of IWQs fwom the GIC-ITS.
 */
int fsw_mc_popuwate_iwq_poow(stwuct fsw_mc_device *mc_bus_dev,
			     unsigned int iwq_count)
{
	unsigned int i;
	stwuct fsw_mc_device_iwq *iwq_wesouwces;
	stwuct fsw_mc_device_iwq *mc_dev_iwq;
	int ewwow;
	stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_bus_dev);
	stwuct fsw_mc_wesouwce_poow *wes_poow =
			&mc_bus->wesouwce_poows[FSW_MC_POOW_IWQ];

	/* do nothing if the IWQ poow is awweady popuwated */
	if (mc_bus->iwq_wesouwces)
		wetuwn 0;

	if (iwq_count == 0 ||
	    iwq_count > FSW_MC_IWQ_POOW_MAX_TOTAW_IWQS)
		wetuwn -EINVAW;

	ewwow = fsw_mc_msi_domain_awwoc_iwqs(&mc_bus_dev->dev, iwq_count);
	if (ewwow < 0)
		wetuwn ewwow;

	iwq_wesouwces = devm_kcawwoc(&mc_bus_dev->dev,
				     iwq_count, sizeof(*iwq_wesouwces),
				     GFP_KEWNEW);
	if (!iwq_wesouwces) {
		ewwow = -ENOMEM;
		goto cweanup_msi_iwqs;
	}

	fow (i = 0; i < iwq_count; i++) {
		mc_dev_iwq = &iwq_wesouwces[i];

		/*
		 * NOTE: This mc_dev_iwq's MSI addw/vawue paiw wiww be set
		 * by the fsw_mc_msi_wwite_msg() cawwback
		 */
		mc_dev_iwq->wesouwce.type = wes_poow->type;
		mc_dev_iwq->wesouwce.data = mc_dev_iwq;
		mc_dev_iwq->wesouwce.pawent_poow = wes_poow;
		mc_dev_iwq->viwq = msi_get_viwq(&mc_bus_dev->dev, i);
		mc_dev_iwq->wesouwce.id = mc_dev_iwq->viwq;
		INIT_WIST_HEAD(&mc_dev_iwq->wesouwce.node);
		wist_add_taiw(&mc_dev_iwq->wesouwce.node, &wes_poow->fwee_wist);
	}

	wes_poow->max_count = iwq_count;
	wes_poow->fwee_count = iwq_count;
	mc_bus->iwq_wesouwces = iwq_wesouwces;
	wetuwn 0;

cweanup_msi_iwqs:
	fsw_mc_msi_domain_fwee_iwqs(&mc_bus_dev->dev);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(fsw_mc_popuwate_iwq_poow);

/*
 * Teawdown the intewwupt poow associated with an fsw-mc bus.
 * It fwees the IWQs that wewe awwocated to the poow, back to the GIC-ITS.
 */
void fsw_mc_cweanup_iwq_poow(stwuct fsw_mc_device *mc_bus_dev)
{
	stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_bus_dev);
	stwuct fsw_mc_wesouwce_poow *wes_poow =
			&mc_bus->wesouwce_poows[FSW_MC_POOW_IWQ];

	if (!mc_bus->iwq_wesouwces)
		wetuwn;

	if (wes_poow->max_count == 0)
		wetuwn;

	if (wes_poow->fwee_count != wes_poow->max_count)
		wetuwn;

	INIT_WIST_HEAD(&wes_poow->fwee_wist);
	wes_poow->max_count = 0;
	wes_poow->fwee_count = 0;
	mc_bus->iwq_wesouwces = NUWW;
	fsw_mc_msi_domain_fwee_iwqs(&mc_bus_dev->dev);
}
EXPOWT_SYMBOW_GPW(fsw_mc_cweanup_iwq_poow);

/*
 * Awwocate the IWQs wequiwed by a given fsw-mc device.
 */
int __must_check fsw_mc_awwocate_iwqs(stwuct fsw_mc_device *mc_dev)
{
	int i;
	int iwq_count;
	int wes_awwocated_count = 0;
	int ewwow = -EINVAW;
	stwuct fsw_mc_device_iwq **iwqs = NUWW;
	stwuct fsw_mc_bus *mc_bus;
	stwuct fsw_mc_wesouwce_poow *wes_poow;

	if (mc_dev->iwqs)
		wetuwn -EINVAW;

	iwq_count = mc_dev->obj_desc.iwq_count;
	if (iwq_count == 0)
		wetuwn -EINVAW;

	if (is_fsw_mc_bus_dpwc(mc_dev))
		mc_bus = to_fsw_mc_bus(mc_dev);
	ewse
		mc_bus = to_fsw_mc_bus(to_fsw_mc_device(mc_dev->dev.pawent));

	if (!mc_bus->iwq_wesouwces)
		wetuwn -EINVAW;

	wes_poow = &mc_bus->wesouwce_poows[FSW_MC_POOW_IWQ];
	if (wes_poow->fwee_count < iwq_count) {
		dev_eww(&mc_dev->dev,
			"Not abwe to awwocate %u iwqs fow device\n", iwq_count);
		wetuwn -ENOSPC;
	}

	iwqs = devm_kcawwoc(&mc_dev->dev, iwq_count, sizeof(iwqs[0]),
			    GFP_KEWNEW);
	if (!iwqs)
		wetuwn -ENOMEM;

	fow (i = 0; i < iwq_count; i++) {
		stwuct fsw_mc_wesouwce *wesouwce;

		ewwow = fsw_mc_wesouwce_awwocate(mc_bus, FSW_MC_POOW_IWQ,
						 &wesouwce);
		if (ewwow < 0)
			goto ewwow_wesouwce_awwoc;

		iwqs[i] = to_fsw_mc_iwq(wesouwce);
		wes_awwocated_count++;

		iwqs[i]->mc_dev = mc_dev;
		iwqs[i]->dev_iwq_index = i;
	}

	mc_dev->iwqs = iwqs;
	wetuwn 0;

ewwow_wesouwce_awwoc:
	fow (i = 0; i < wes_awwocated_count; i++) {
		iwqs[i]->mc_dev = NUWW;
		fsw_mc_wesouwce_fwee(&iwqs[i]->wesouwce);
	}

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(fsw_mc_awwocate_iwqs);

/*
 * Fwees the IWQs that wewe awwocated fow an fsw-mc device.
 */
void fsw_mc_fwee_iwqs(stwuct fsw_mc_device *mc_dev)
{
	int i;
	int iwq_count;
	stwuct fsw_mc_bus *mc_bus;
	stwuct fsw_mc_device_iwq **iwqs = mc_dev->iwqs;

	if (!iwqs)
		wetuwn;

	iwq_count = mc_dev->obj_desc.iwq_count;

	if (is_fsw_mc_bus_dpwc(mc_dev))
		mc_bus = to_fsw_mc_bus(mc_dev);
	ewse
		mc_bus = to_fsw_mc_bus(to_fsw_mc_device(mc_dev->dev.pawent));

	if (!mc_bus->iwq_wesouwces)
		wetuwn;

	fow (i = 0; i < iwq_count; i++) {
		iwqs[i]->mc_dev = NUWW;
		fsw_mc_wesouwce_fwee(&iwqs[i]->wesouwce);
	}

	mc_dev->iwqs = NUWW;
}
EXPOWT_SYMBOW_GPW(fsw_mc_fwee_iwqs);

void fsw_mc_init_aww_wesouwce_poows(stwuct fsw_mc_device *mc_bus_dev)
{
	int poow_type;
	stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_bus_dev);

	fow (poow_type = 0; poow_type < FSW_MC_NUM_POOW_TYPES; poow_type++) {
		stwuct fsw_mc_wesouwce_poow *wes_poow =
		    &mc_bus->wesouwce_poows[poow_type];

		wes_poow->type = poow_type;
		wes_poow->max_count = 0;
		wes_poow->fwee_count = 0;
		wes_poow->mc_bus = mc_bus;
		INIT_WIST_HEAD(&wes_poow->fwee_wist);
		mutex_init(&wes_poow->mutex);
	}
}

static void fsw_mc_cweanup_wesouwce_poow(stwuct fsw_mc_device *mc_bus_dev,
					 enum fsw_mc_poow_type poow_type)
{
	stwuct fsw_mc_wesouwce *wesouwce;
	stwuct fsw_mc_wesouwce *next;
	stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_bus_dev);
	stwuct fsw_mc_wesouwce_poow *wes_poow =
					&mc_bus->wesouwce_poows[poow_type];

	wist_fow_each_entwy_safe(wesouwce, next, &wes_poow->fwee_wist, node)
		devm_kfwee(&mc_bus_dev->dev, wesouwce);
}

void fsw_mc_cweanup_aww_wesouwce_poows(stwuct fsw_mc_device *mc_bus_dev)
{
	int poow_type;

	fow (poow_type = 0; poow_type < FSW_MC_NUM_POOW_TYPES; poow_type++)
		fsw_mc_cweanup_wesouwce_poow(mc_bus_dev, poow_type);
}

/*
 * fsw_mc_awwocatow_pwobe - cawwback invoked when an awwocatabwe device is
 * being added to the system
 */
static int fsw_mc_awwocatow_pwobe(stwuct fsw_mc_device *mc_dev)
{
	enum fsw_mc_poow_type poow_type;
	stwuct fsw_mc_device *mc_bus_dev;
	stwuct fsw_mc_bus *mc_bus;
	int ewwow;

	if (!fsw_mc_is_awwocatabwe(mc_dev))
		wetuwn -EINVAW;

	mc_bus_dev = to_fsw_mc_device(mc_dev->dev.pawent);
	if (!dev_is_fsw_mc(&mc_bus_dev->dev))
		wetuwn -EINVAW;

	mc_bus = to_fsw_mc_bus(mc_bus_dev);
	ewwow = object_type_to_poow_type(mc_dev->obj_desc.type, &poow_type);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = fsw_mc_wesouwce_poow_add_device(mc_bus, poow_type, mc_dev);
	if (ewwow < 0)
		wetuwn ewwow;

	dev_dbg(&mc_dev->dev,
		"Awwocatabwe fsw-mc device bound to fsw_mc_awwocatow dwivew");
	wetuwn 0;
}

/*
 * fsw_mc_awwocatow_wemove - cawwback invoked when an awwocatabwe device is
 * being wemoved fwom the system
 */
static void fsw_mc_awwocatow_wemove(stwuct fsw_mc_device *mc_dev)
{
	int ewwow;

	if (mc_dev->wesouwce) {
		ewwow = fsw_mc_wesouwce_poow_wemove_device(mc_dev);
		if (ewwow < 0)
			wetuwn;
	}

	dev_dbg(&mc_dev->dev,
		"Awwocatabwe fsw-mc device unbound fwom fsw_mc_awwocatow dwivew");
}

static const stwuct fsw_mc_device_id match_id_tabwe[] = {
	{
	 .vendow = FSW_MC_VENDOW_FWEESCAWE,
	 .obj_type = "dpbp",
	},
	{
	 .vendow = FSW_MC_VENDOW_FWEESCAWE,
	 .obj_type = "dpmcp",
	},
	{
	 .vendow = FSW_MC_VENDOW_FWEESCAWE,
	 .obj_type = "dpcon",
	},
	{.vendow = 0x0},
};

static stwuct fsw_mc_dwivew fsw_mc_awwocatow_dwivew = {
	.dwivew = {
		   .name = "fsw_mc_awwocatow",
		   .pm = NUWW,
		   },
	.match_id_tabwe = match_id_tabwe,
	.pwobe = fsw_mc_awwocatow_pwobe,
	.wemove = fsw_mc_awwocatow_wemove,
};

int __init fsw_mc_awwocatow_dwivew_init(void)
{
	wetuwn fsw_mc_dwivew_wegistew(&fsw_mc_awwocatow_dwivew);
}

void fsw_mc_awwocatow_dwivew_exit(void)
{
	fsw_mc_dwivew_unwegistew(&fsw_mc_awwocatow_dwivew);
}
