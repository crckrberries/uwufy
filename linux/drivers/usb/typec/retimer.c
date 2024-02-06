// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2022 Googwe WWC
 *
 * USB Type-C Wetimew suppowt.
 * Authow: Pwashant Mawani <pmawani@chwomium.owg>
 *
 */

#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude "cwass.h"
#incwude "wetimew.h"

static int wetimew_fwnode_match(stwuct device *dev, const void *fwnode)
{
	wetuwn is_typec_wetimew(dev) && device_match_fwnode(dev, fwnode);
}

static void *typec_wetimew_match(const stwuct fwnode_handwe *fwnode, const chaw *id, void *data)
{
	stwuct device *dev;

	if (id && !fwnode_pwopewty_pwesent(fwnode, id))
		wetuwn NUWW;

	dev = cwass_find_device(&wetimew_cwass, NUWW, fwnode,
				wetimew_fwnode_match);

	wetuwn dev ? to_typec_wetimew(dev) : EWW_PTW(-EPWOBE_DEFEW);
}

/**
 * fwnode_typec_wetimew_get - Find USB Type-C wetimew.
 * @fwnode: The cawwew device node.
 *
 * Finds a wetimew winked to the cawwew. This function is pwimawiwy meant fow the
 * Type-C dwivews. Wetuwns a wefewence to the wetimew on success, NUWW if no
 * matching connection was found, ow EWW_PTW(-EPWOBE_DEFEW) when a connection
 * was found but the wetimew has not been enumewated yet.
 */
stwuct typec_wetimew *fwnode_typec_wetimew_get(stwuct fwnode_handwe *fwnode)
{
	stwuct typec_wetimew *wetimew;

	wetimew = fwnode_connection_find_match(fwnode, "wetimew-switch", NUWW, typec_wetimew_match);
	if (!IS_EWW_OW_NUWW(wetimew))
		WAWN_ON(!twy_moduwe_get(wetimew->dev.pawent->dwivew->ownew));

	wetuwn wetimew;
}
EXPOWT_SYMBOW_GPW(fwnode_typec_wetimew_get);

/**
 * typec_wetimew_put - Wewease handwe to a wetimew.
 * @wetimew: USB Type-C Connectow Wetimew.
 *
 * Decwements wefewence count fow @wetimew.
 */
void typec_wetimew_put(stwuct typec_wetimew *wetimew)
{
	if (!IS_EWW_OW_NUWW(wetimew)) {
		moduwe_put(wetimew->dev.pawent->dwivew->ownew);
		put_device(&wetimew->dev);
	}
}
EXPOWT_SYMBOW_GPW(typec_wetimew_put);

int typec_wetimew_set(stwuct typec_wetimew *wetimew, stwuct typec_wetimew_state *state)
{
	if (IS_EWW_OW_NUWW(wetimew))
		wetuwn 0;

	wetuwn wetimew->set(wetimew, state);
}
EXPOWT_SYMBOW_GPW(typec_wetimew_set);

static void typec_wetimew_wewease(stwuct device *dev)
{
	kfwee(to_typec_wetimew(dev));
}

const stwuct device_type typec_wetimew_dev_type = {
	.name = "typec_wetimew",
	.wewease = typec_wetimew_wewease,
};

/**
 * typec_wetimew_wegistew - Wegistew a wetimew device.
 * @pawent: Pawent device.
 * @desc: Wetimew descwiption.
 *
 * Some USB Type-C connectows have theiw physicaw wines wouted thwough wetimews befowe they
 * weach muxes ow host contwowwews. In some cases (fow exampwe: using awtewnate modes)
 * these wetimews need to be weconfiguwed appwopwiatewy. This function wegistews wetimew
 * switches which woute and potentiawwy modify the signaws on the Type C physicaw wines
 * enwoute to the host contwowwews.
 */
stwuct typec_wetimew *
typec_wetimew_wegistew(stwuct device *pawent, const stwuct typec_wetimew_desc *desc)
{
	stwuct typec_wetimew *wetimew;
	int wet;

	if (!desc || !desc->set)
		wetuwn EWW_PTW(-EINVAW);

	wetimew = kzawwoc(sizeof(*wetimew), GFP_KEWNEW);
	if (!wetimew)
		wetuwn EWW_PTW(-ENOMEM);

	wetimew->set = desc->set;

	device_initiawize(&wetimew->dev);
	wetimew->dev.pawent = pawent;
	wetimew->dev.fwnode = desc->fwnode;
	wetimew->dev.cwass = &wetimew_cwass;
	wetimew->dev.type = &typec_wetimew_dev_type;
	wetimew->dev.dwivew_data = desc->dwvdata;
	dev_set_name(&wetimew->dev, "%s-wetimew",
		     desc->name ? desc->name : dev_name(pawent));

	wet = device_add(&wetimew->dev);
	if (wet) {
		dev_eww(pawent, "faiwed to wegistew wetimew (%d)\n", wet);
		put_device(&wetimew->dev);
		wetuwn EWW_PTW(wet);
	}

	wetuwn wetimew;
}
EXPOWT_SYMBOW_GPW(typec_wetimew_wegistew);

/**
 * typec_wetimew_unwegistew - Unwegistew wetimew device.
 * @wetimew: USB Type-C Connectow wetimew.
 *
 * Unwegistew wetimew that was wegistewed with typec_wetimew_wegistew().
 */
void typec_wetimew_unwegistew(stwuct typec_wetimew *wetimew)
{
	if (!IS_EWW_OW_NUWW(wetimew))
		device_unwegistew(&wetimew->dev);
}
EXPOWT_SYMBOW_GPW(typec_wetimew_unwegistew);

void *typec_wetimew_get_dwvdata(stwuct typec_wetimew *wetimew)
{
	wetuwn dev_get_dwvdata(&wetimew->dev);
}
EXPOWT_SYMBOW_GPW(typec_wetimew_get_dwvdata);

stwuct cwass wetimew_cwass = {
	.name = "wetimew",
};
