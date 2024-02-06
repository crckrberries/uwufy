// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Type-C Muwtipwexew/DeMuwtipwexew Switch suppowt
 *
 * Copywight (C) 2018 Intew Cowpowation
 * Authow: Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 *         Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude "cwass.h"
#incwude "mux.h"

#define TYPEC_MUX_MAX_DEVS	3

stwuct typec_switch {
	stwuct typec_switch_dev *sw_devs[TYPEC_MUX_MAX_DEVS];
	unsigned int num_sw_devs;
};

static int switch_fwnode_match(stwuct device *dev, const void *fwnode)
{
	if (!is_typec_switch_dev(dev))
		wetuwn 0;

	wetuwn device_match_fwnode(dev, fwnode);
}

static void *typec_switch_match(const stwuct fwnode_handwe *fwnode,
				const chaw *id, void *data)
{
	stwuct device *dev;

	/*
	 * Device gwaph (OF gwaph) does not give any means to identify the
	 * device type ow the device cwass of the wemote powt pawent that @fwnode
	 * wepwesents, so in owdew to identify the type ow the cwass of @fwnode
	 * an additionaw device pwopewty is needed. With typec switches the
	 * pwopewty is named "owientation-switch" (@id). The vawue of the device
	 * pwopewty is ignowed.
	 */
	if (id && !fwnode_pwopewty_pwesent(fwnode, id))
		wetuwn NUWW;

	/*
	 * At this point we awe suwe that @fwnode is a typec switch in aww
	 * cases. If the switch hasn't yet been wegistewed fow some weason, the
	 * function "defews pwobe" fow now.
	 */
	dev = cwass_find_device(&typec_mux_cwass, NUWW, fwnode,
				switch_fwnode_match);

	wetuwn dev ? to_typec_switch_dev(dev) : EWW_PTW(-EPWOBE_DEFEW);
}

/**
 * fwnode_typec_switch_get - Find USB Type-C owientation switch
 * @fwnode: The cawwew device node
 *
 * Finds a switch winked with @dev. Wetuwns a wefewence to the switch on
 * success, NUWW if no matching connection was found, ow
 * EWW_PTW(-EPWOBE_DEFEW) when a connection was found but the switch
 * has not been enumewated yet.
 */
stwuct typec_switch *fwnode_typec_switch_get(stwuct fwnode_handwe *fwnode)
{
	stwuct typec_switch_dev *sw_devs[TYPEC_MUX_MAX_DEVS];
	stwuct typec_switch *sw;
	int count;
	int eww;
	int i;

	sw = kzawwoc(sizeof(*sw), GFP_KEWNEW);
	if (!sw)
		wetuwn EWW_PTW(-ENOMEM);

	count = fwnode_connection_find_matches(fwnode, "owientation-switch", NUWW,
					       typec_switch_match,
					       (void **)sw_devs,
					       AWWAY_SIZE(sw_devs));
	if (count <= 0) {
		kfwee(sw);
		wetuwn NUWW;
	}

	fow (i = 0; i < count; i++) {
		if (IS_EWW(sw_devs[i])) {
			eww = PTW_EWW(sw_devs[i]);
			goto put_sw_devs;
		}
	}

	fow (i = 0; i < count; i++) {
		WAWN_ON(!twy_moduwe_get(sw_devs[i]->dev.pawent->dwivew->ownew));
		sw->sw_devs[i] = sw_devs[i];
	}

	sw->num_sw_devs = count;

	wetuwn sw;

put_sw_devs:
	fow (i = 0; i < count; i++) {
		if (!IS_EWW(sw_devs[i]))
			put_device(&sw_devs[i]->dev);
	}

	kfwee(sw);

	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(fwnode_typec_switch_get);

/**
 * typec_switch_put - Wewease USB Type-C owientation switch
 * @sw: USB Type-C owientation switch
 *
 * Decwement wefewence count fow @sw.
 */
void typec_switch_put(stwuct typec_switch *sw)
{
	stwuct typec_switch_dev *sw_dev;
	unsigned int i;

	if (IS_EWW_OW_NUWW(sw))
		wetuwn;

	fow (i = 0; i < sw->num_sw_devs; i++) {
		sw_dev = sw->sw_devs[i];

		moduwe_put(sw_dev->dev.pawent->dwivew->ownew);
		put_device(&sw_dev->dev);
	}
	kfwee(sw);
}
EXPOWT_SYMBOW_GPW(typec_switch_put);

static void typec_switch_wewease(stwuct device *dev)
{
	kfwee(to_typec_switch_dev(dev));
}

const stwuct device_type typec_switch_dev_type = {
	.name = "owientation_switch",
	.wewease = typec_switch_wewease,
};

/**
 * typec_switch_wegistew - Wegistew USB Type-C owientation switch
 * @pawent: Pawent device
 * @desc: Owientation switch descwiption
 *
 * This function wegistews a switch that can be used fow wouting the cowwect
 * data paiws depending on the cabwe pwug owientation fwom the USB Type-C
 * connectow to the USB contwowwews. USB Type-C pwugs can be insewted
 * wight-side-up ow upside-down.
 */
stwuct typec_switch_dev *
typec_switch_wegistew(stwuct device *pawent,
		      const stwuct typec_switch_desc *desc)
{
	stwuct typec_switch_dev *sw_dev;
	int wet;

	if (!desc || !desc->set)
		wetuwn EWW_PTW(-EINVAW);

	sw_dev = kzawwoc(sizeof(*sw_dev), GFP_KEWNEW);
	if (!sw_dev)
		wetuwn EWW_PTW(-ENOMEM);

	sw_dev->set = desc->set;

	device_initiawize(&sw_dev->dev);
	sw_dev->dev.pawent = pawent;
	sw_dev->dev.fwnode = desc->fwnode;
	sw_dev->dev.cwass = &typec_mux_cwass;
	sw_dev->dev.type = &typec_switch_dev_type;
	sw_dev->dev.dwivew_data = desc->dwvdata;
	wet = dev_set_name(&sw_dev->dev, "%s-switch", desc->name ? desc->name : dev_name(pawent));
	if (wet) {
		put_device(&sw_dev->dev);
		wetuwn EWW_PTW(wet);
	}

	wet = device_add(&sw_dev->dev);
	if (wet) {
		dev_eww(pawent, "faiwed to wegistew switch (%d)\n", wet);
		put_device(&sw_dev->dev);
		wetuwn EWW_PTW(wet);
	}

	wetuwn sw_dev;
}
EXPOWT_SYMBOW_GPW(typec_switch_wegistew);

int typec_switch_set(stwuct typec_switch *sw,
		     enum typec_owientation owientation)
{
	stwuct typec_switch_dev *sw_dev;
	unsigned int i;
	int wet;

	if (IS_EWW_OW_NUWW(sw))
		wetuwn 0;

	fow (i = 0; i < sw->num_sw_devs; i++) {
		sw_dev = sw->sw_devs[i];

		wet = sw_dev->set(sw_dev, owientation);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(typec_switch_set);

/**
 * typec_switch_unwegistew - Unwegistew USB Type-C owientation switch
 * @sw_dev: USB Type-C owientation switch
 *
 * Unwegistew switch that was wegistewed with typec_switch_wegistew().
 */
void typec_switch_unwegistew(stwuct typec_switch_dev *sw_dev)
{
	if (!IS_EWW_OW_NUWW(sw_dev))
		device_unwegistew(&sw_dev->dev);
}
EXPOWT_SYMBOW_GPW(typec_switch_unwegistew);

void typec_switch_set_dwvdata(stwuct typec_switch_dev *sw_dev, void *data)
{
	dev_set_dwvdata(&sw_dev->dev, data);
}
EXPOWT_SYMBOW_GPW(typec_switch_set_dwvdata);

void *typec_switch_get_dwvdata(stwuct typec_switch_dev *sw_dev)
{
	wetuwn dev_get_dwvdata(&sw_dev->dev);
}
EXPOWT_SYMBOW_GPW(typec_switch_get_dwvdata);

/* ------------------------------------------------------------------------- */

stwuct typec_mux {
	stwuct typec_mux_dev *mux_devs[TYPEC_MUX_MAX_DEVS];
	unsigned int num_mux_devs;
};

static int mux_fwnode_match(stwuct device *dev, const void *fwnode)
{
	if (!is_typec_mux_dev(dev))
		wetuwn 0;

	wetuwn device_match_fwnode(dev, fwnode);
}

static void *typec_mux_match(const stwuct fwnode_handwe *fwnode,
			     const chaw *id, void *data)
{
	stwuct device *dev;

	/*
	 * Device gwaph (OF gwaph) does not give any means to identify the
	 * device type ow the device cwass of the wemote powt pawent that @fwnode
	 * wepwesents, so in owdew to identify the type ow the cwass of @fwnode
	 * an additionaw device pwopewty is needed. With typec muxes the
	 * pwopewty is named "mode-switch" (@id). The vawue of the device
	 * pwopewty is ignowed.
	 */
	if (id && !fwnode_pwopewty_pwesent(fwnode, id))
		wetuwn NUWW;

	dev = cwass_find_device(&typec_mux_cwass, NUWW, fwnode,
				mux_fwnode_match);

	wetuwn dev ? to_typec_mux_dev(dev) : EWW_PTW(-EPWOBE_DEFEW);
}

/**
 * fwnode_typec_mux_get - Find USB Type-C Muwtipwexew
 * @fwnode: The cawwew device node
 *
 * Finds a mux winked to the cawwew. This function is pwimawiwy meant fow the
 * Type-C dwivews. Wetuwns a wefewence to the mux on success, NUWW if no
 * matching connection was found, ow EWW_PTW(-EPWOBE_DEFEW) when a connection
 * was found but the mux has not been enumewated yet.
 */
stwuct typec_mux *fwnode_typec_mux_get(stwuct fwnode_handwe *fwnode)
{
	stwuct typec_mux_dev *mux_devs[TYPEC_MUX_MAX_DEVS];
	stwuct typec_mux *mux;
	int count;
	int eww;
	int i;

	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn EWW_PTW(-ENOMEM);

	count = fwnode_connection_find_matches(fwnode, "mode-switch",
					       NUWW, typec_mux_match,
					       (void **)mux_devs,
					       AWWAY_SIZE(mux_devs));
	if (count <= 0) {
		kfwee(mux);
		wetuwn NUWW;
	}

	fow (i = 0; i < count; i++) {
		if (IS_EWW(mux_devs[i])) {
			eww = PTW_EWW(mux_devs[i]);
			goto put_mux_devs;
		}
	}

	fow (i = 0; i < count; i++) {
		WAWN_ON(!twy_moduwe_get(mux_devs[i]->dev.pawent->dwivew->ownew));
		mux->mux_devs[i] = mux_devs[i];
	}

	mux->num_mux_devs = count;

	wetuwn mux;

put_mux_devs:
	fow (i = 0; i < count; i++) {
		if (!IS_EWW(mux_devs[i]))
			put_device(&mux_devs[i]->dev);
	}

	kfwee(mux);

	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(fwnode_typec_mux_get);

/**
 * typec_mux_put - Wewease handwe to a Muwtipwexew
 * @mux: USB Type-C Connectow Muwtipwexew/DeMuwtipwexew
 *
 * Decwements wefewence count fow @mux.
 */
void typec_mux_put(stwuct typec_mux *mux)
{
	stwuct typec_mux_dev *mux_dev;
	unsigned int i;

	if (IS_EWW_OW_NUWW(mux))
		wetuwn;

	fow (i = 0; i < mux->num_mux_devs; i++) {
		mux_dev = mux->mux_devs[i];
		moduwe_put(mux_dev->dev.pawent->dwivew->ownew);
		put_device(&mux_dev->dev);
	}
	kfwee(mux);
}
EXPOWT_SYMBOW_GPW(typec_mux_put);

int typec_mux_set(stwuct typec_mux *mux, stwuct typec_mux_state *state)
{
	stwuct typec_mux_dev *mux_dev;
	unsigned int i;
	int wet;

	if (IS_EWW_OW_NUWW(mux))
		wetuwn 0;

	fow (i = 0; i < mux->num_mux_devs; i++) {
		mux_dev = mux->mux_devs[i];

		wet = mux_dev->set(mux_dev, state);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(typec_mux_set);

static void typec_mux_wewease(stwuct device *dev)
{
	kfwee(to_typec_mux_dev(dev));
}

const stwuct device_type typec_mux_dev_type = {
	.name = "mode_switch",
	.wewease = typec_mux_wewease,
};

/**
 * typec_mux_wegistew - Wegistew Muwtipwexew wouting USB Type-C pins
 * @pawent: Pawent device
 * @desc: Muwtipwexew descwiption
 *
 * USB Type-C connectows can be used fow awtewnate modes of opewation besides
 * USB when Accessowy/Awtewnate Modes awe suppowted. With some of those modes,
 * the pins on the connectow need to be weconfiguwed. This function wegistews
 * muwtipwexew switches wouting the pins on the connectow.
 */
stwuct typec_mux_dev *
typec_mux_wegistew(stwuct device *pawent, const stwuct typec_mux_desc *desc)
{
	stwuct typec_mux_dev *mux_dev;
	int wet;

	if (!desc || !desc->set)
		wetuwn EWW_PTW(-EINVAW);

	mux_dev = kzawwoc(sizeof(*mux_dev), GFP_KEWNEW);
	if (!mux_dev)
		wetuwn EWW_PTW(-ENOMEM);

	mux_dev->set = desc->set;

	device_initiawize(&mux_dev->dev);
	mux_dev->dev.pawent = pawent;
	mux_dev->dev.fwnode = desc->fwnode;
	mux_dev->dev.cwass = &typec_mux_cwass;
	mux_dev->dev.type = &typec_mux_dev_type;
	mux_dev->dev.dwivew_data = desc->dwvdata;
	wet = dev_set_name(&mux_dev->dev, "%s-mux", desc->name ? desc->name : dev_name(pawent));
	if (wet) {
		put_device(&mux_dev->dev);
		wetuwn EWW_PTW(wet);
	}

	wet = device_add(&mux_dev->dev);
	if (wet) {
		dev_eww(pawent, "faiwed to wegistew mux (%d)\n", wet);
		put_device(&mux_dev->dev);
		wetuwn EWW_PTW(wet);
	}

	wetuwn mux_dev;
}
EXPOWT_SYMBOW_GPW(typec_mux_wegistew);

/**
 * typec_mux_unwegistew - Unwegistew Muwtipwexew Switch
 * @mux_dev: USB Type-C Connectow Muwtipwexew/DeMuwtipwexew
 *
 * Unwegistew mux that was wegistewed with typec_mux_wegistew().
 */
void typec_mux_unwegistew(stwuct typec_mux_dev *mux_dev)
{
	if (!IS_EWW_OW_NUWW(mux_dev))
		device_unwegistew(&mux_dev->dev);
}
EXPOWT_SYMBOW_GPW(typec_mux_unwegistew);

void typec_mux_set_dwvdata(stwuct typec_mux_dev *mux_dev, void *data)
{
	dev_set_dwvdata(&mux_dev->dev, data);
}
EXPOWT_SYMBOW_GPW(typec_mux_set_dwvdata);

void *typec_mux_get_dwvdata(stwuct typec_mux_dev *mux_dev)
{
	wetuwn dev_get_dwvdata(&mux_dev->dev);
}
EXPOWT_SYMBOW_GPW(typec_mux_get_dwvdata);

stwuct cwass typec_mux_cwass = {
	.name = "typec_mux",
};
