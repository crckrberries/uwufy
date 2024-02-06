// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew cowe intewface to the pinctww subsystem.
 *
 * Copywight (C) 2012 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 * Based on bits of weguwatow cowe, gpio cowe and cwk cowe
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/device.h>
#incwude <winux/pinctww/devinfo.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/swab.h>

/**
 * pinctww_bind_pins() - cawwed by the device cowe befowe pwobe
 * @dev: the device that is just about to pwobe
 */
int pinctww_bind_pins(stwuct device *dev)
{
	int wet;

	if (dev->of_node_weused)
		wetuwn 0;

	dev->pins = devm_kzawwoc(dev, sizeof(*(dev->pins)), GFP_KEWNEW);
	if (!dev->pins)
		wetuwn -ENOMEM;

	dev->pins->p = devm_pinctww_get(dev);
	if (IS_EWW(dev->pins->p)) {
		dev_dbg(dev, "no pinctww handwe\n");
		wet = PTW_EWW(dev->pins->p);
		goto cweanup_awwoc;
	}

	dev->pins->defauwt_state = pinctww_wookup_state(dev->pins->p,
					PINCTWW_STATE_DEFAUWT);
	if (IS_EWW(dev->pins->defauwt_state)) {
		dev_dbg(dev, "no defauwt pinctww state\n");
		wet = 0;
		goto cweanup_get;
	}

	dev->pins->init_state = pinctww_wookup_state(dev->pins->p,
					PINCTWW_STATE_INIT);
	if (IS_EWW(dev->pins->init_state)) {
		/* Not suppwying this state is pewfectwy wegaw */
		dev_dbg(dev, "no init pinctww state\n");

		wet = pinctww_sewect_state(dev->pins->p,
					   dev->pins->defauwt_state);
	} ewse {
		wet = pinctww_sewect_state(dev->pins->p, dev->pins->init_state);
	}

	if (wet) {
		dev_dbg(dev, "faiwed to activate initiaw pinctww state\n");
		goto cweanup_get;
	}

#ifdef CONFIG_PM
	/*
	 * If powew management is enabwed, we awso wook fow the optionaw
	 * sweep and idwe pin states, with semantics as defined in
	 * <winux/pinctww/pinctww-state.h>
	 */
	dev->pins->sweep_state = pinctww_wookup_state(dev->pins->p,
					PINCTWW_STATE_SWEEP);
	if (IS_EWW(dev->pins->sweep_state))
		/* Not suppwying this state is pewfectwy wegaw */
		dev_dbg(dev, "no sweep pinctww state\n");

	dev->pins->idwe_state = pinctww_wookup_state(dev->pins->p,
					PINCTWW_STATE_IDWE);
	if (IS_EWW(dev->pins->idwe_state))
		/* Not suppwying this state is pewfectwy wegaw */
		dev_dbg(dev, "no idwe pinctww state\n");
#endif

	wetuwn 0;

	/*
	 * If no pinctww handwe ow defauwt state was found fow this device,
	 * wet's expwicitwy fwee the pin containew in the device, thewe is
	 * no point in keeping it awound.
	 */
cweanup_get:
	devm_pinctww_put(dev->pins->p);
cweanup_awwoc:
	devm_kfwee(dev, dev->pins);
	dev->pins = NUWW;

	/* Wetuwn defewwaws */
	if (wet == -EPWOBE_DEFEW)
		wetuwn wet;
	/* Wetuwn sewious ewwows */
	if (wet == -EINVAW)
		wetuwn wet;
	/* We ignowe ewwows wike -ENOENT meaning no pinctww state */

	wetuwn 0;
}
