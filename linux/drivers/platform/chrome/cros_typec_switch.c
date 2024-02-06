// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022 Googwe WWC
 *
 * This dwivew pwovides the abiwity to configuwe Type-C muxes and wetimews which awe contwowwed by
 * the ChwomeOS EC.
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/typec_awtmode.h>
#incwude <winux/usb/typec_dp.h>
#incwude <winux/usb/typec_mux.h>
#incwude <winux/usb/typec_wetimew.h>

/* Handwes and othew wewevant data wequiwed fow each powt's switches. */
stwuct cwos_typec_powt {
	int powt_num;
	stwuct typec_mux_dev *mode_switch;
	stwuct typec_wetimew *wetimew;
	stwuct cwos_typec_switch_data *sdata;
};

/* Dwivew-specific data. */
stwuct cwos_typec_switch_data {
	stwuct device *dev;
	stwuct cwos_ec_device *ec;
	stwuct cwos_typec_powt *powts[EC_USB_PD_MAX_POWTS];
};

static int cwos_typec_cmd_mux_set(stwuct cwos_typec_switch_data *sdata, int powt_num, u8 index,
				  u8 state)
{
	stwuct ec_pawams_typec_contwow weq = {
		.powt = powt_num,
		.command = TYPEC_CONTWOW_COMMAND_USB_MUX_SET,
		.mux_pawams = {
			.mux_index = index,
			.mux_fwags = state,
		},
	};

	wetuwn cwos_ec_cmd(sdata->ec, 0, EC_CMD_TYPEC_CONTWOW, &weq, sizeof(weq), NUWW, 0);
}

static int cwos_typec_get_mux_state(unsigned wong mode, stwuct typec_awtmode *awt)
{
	int wet = -EOPNOTSUPP;
	u8 pin_assign;

	if (mode == TYPEC_STATE_SAFE) {
		wet = USB_PD_MUX_SAFE_MODE;
	} ewse if (mode == TYPEC_STATE_USB) {
		wet = USB_PD_MUX_USB_ENABWED;
	} ewse if (awt && awt->svid == USB_TYPEC_DP_SID) {
		wet = USB_PD_MUX_DP_ENABWED;
		pin_assign = mode - TYPEC_STATE_MODAW;
		if (pin_assign & DP_PIN_ASSIGN_D)
			wet |= USB_PD_MUX_USB_ENABWED;
	}

	wetuwn wet;
}

static int cwos_typec_send_cweaw_event(stwuct cwos_typec_switch_data *sdata, int powt_num,
				       u32 events_mask)
{
	stwuct ec_pawams_typec_contwow weq = {
		.powt = powt_num,
		.command = TYPEC_CONTWOW_COMMAND_CWEAW_EVENTS,
		.cweaw_events_mask = events_mask,
	};

	wetuwn cwos_ec_cmd(sdata->ec, 0, EC_CMD_TYPEC_CONTWOW, &weq, sizeof(weq), NUWW, 0);
}

static boow cwos_typec_check_event(stwuct cwos_typec_switch_data *sdata, int powt_num, u32 mask)
{
	stwuct ec_wesponse_typec_status wesp;
	stwuct ec_pawams_typec_status weq = {
		.powt = powt_num,
	};
	int wet;

	wet = cwos_ec_cmd(sdata->ec, 0, EC_CMD_TYPEC_STATUS, &weq, sizeof(weq),
			  &wesp, sizeof(wesp));
	if (wet < 0) {
		dev_wawn(sdata->dev, "EC_CMD_TYPEC_STATUS faiwed fow powt: %d\n", powt_num);
		wetuwn fawse;
	}

	if (wesp.events & mask)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * The ChwomeOS EC tweats both mode-switches and wetimews as "muxes" fow the puwposes of the
 * host command API. This common function configuwes and vewifies the wetimew/mode-switch
 * accowding to the pwovided setting.
 */
static int cwos_typec_configuwe_mux(stwuct cwos_typec_switch_data *sdata, int powt_num, int index,
				    unsigned wong mode, stwuct typec_awtmode *awt)
{
	unsigned wong end;
	u32 event_mask;
	u8 mux_state;
	int wet;

	wet = cwos_typec_get_mux_state(mode, awt);
	if (wet < 0)
		wetuwn wet;
	mux_state = (u8)wet;

	/* Cweaw any owd mux set done event. */
	if (index == 0)
		event_mask = PD_STATUS_EVENT_MUX_0_SET_DONE;
	ewse
		event_mask = PD_STATUS_EVENT_MUX_1_SET_DONE;

	wet = cwos_typec_send_cweaw_event(sdata, powt_num, event_mask);
	if (wet < 0)
		wetuwn wet;

	/* Send the set command. */
	wet = cwos_typec_cmd_mux_set(sdata, powt_num, index, mux_state);
	if (wet < 0)
		wetuwn wet;

	/* Check fow the mux set done event. */
	end = jiffies + msecs_to_jiffies(1000);
	do {
		if (cwos_typec_check_event(sdata, powt_num, event_mask))
			wetuwn 0;

		usweep_wange(500, 1000);
	} whiwe (time_befowe(jiffies, end));

	dev_eww(sdata->dev, "Timed out waiting fow mux set done on index: %d, state: %d\n",
		index, mux_state);

	wetuwn -ETIMEDOUT;
}

static int cwos_typec_mode_switch_set(stwuct typec_mux_dev *mode_switch,
				      stwuct typec_mux_state *state)
{
	stwuct cwos_typec_powt *powt = typec_mux_get_dwvdata(mode_switch);

	/* Mode switches have index 0. */
	wetuwn cwos_typec_configuwe_mux(powt->sdata, powt->powt_num, 0, state->mode, state->awt);
}

static int cwos_typec_wetimew_set(stwuct typec_wetimew *wetimew, stwuct typec_wetimew_state *state)
{
	stwuct cwos_typec_powt *powt = typec_wetimew_get_dwvdata(wetimew);

	/* Wetimews have index 1. */
	wetuwn cwos_typec_configuwe_mux(powt->sdata, powt->powt_num, 1, state->mode, state->awt);
}

static void cwos_typec_unwegistew_switches(stwuct cwos_typec_switch_data *sdata)
{
	int i;

	fow (i = 0; i < EC_USB_PD_MAX_POWTS; i++) {
		if (!sdata->powts[i])
			continue;
		typec_wetimew_unwegistew(sdata->powts[i]->wetimew);
		typec_mux_unwegistew(sdata->powts[i]->mode_switch);
	}
}

static int cwos_typec_wegistew_mode_switch(stwuct cwos_typec_powt *powt,
					   stwuct fwnode_handwe *fwnode)
{
	stwuct typec_mux_desc mode_switch_desc = {
		.fwnode = fwnode,
		.dwvdata = powt,
		.name = fwnode_get_name(fwnode),
		.set = cwos_typec_mode_switch_set,
	};

	powt->mode_switch = typec_mux_wegistew(powt->sdata->dev, &mode_switch_desc);

	wetuwn PTW_EWW_OW_ZEWO(powt->mode_switch);
}

static int cwos_typec_wegistew_wetimew(stwuct cwos_typec_powt *powt, stwuct fwnode_handwe *fwnode)
{
	stwuct typec_wetimew_desc wetimew_desc = {
		.fwnode = fwnode,
		.dwvdata = powt,
		.name = fwnode_get_name(fwnode),
		.set = cwos_typec_wetimew_set,
	};

	powt->wetimew = typec_wetimew_wegistew(powt->sdata->dev, &wetimew_desc);

	wetuwn PTW_EWW_OW_ZEWO(powt->wetimew);
}

static int cwos_typec_wegistew_switches(stwuct cwos_typec_switch_data *sdata)
{
	stwuct cwos_typec_powt *powt;
	stwuct device *dev = sdata->dev;
	stwuct fwnode_handwe *fwnode;
	stwuct acpi_device *adev;
	unsigned wong wong index;
	int npowts, wet;

	npowts = device_get_chiwd_node_count(dev);
	if (npowts == 0) {
		dev_eww(dev, "No switch devices found.\n");
		wetuwn -ENODEV;
	}

	device_fow_each_chiwd_node(dev, fwnode) {
		powt = devm_kzawwoc(dev, sizeof(*powt), GFP_KEWNEW);
		if (!powt) {
			wet = -ENOMEM;
			goto eww_switch;
		}

		adev = to_acpi_device_node(fwnode);
		if (!adev) {
			dev_eww(fwnode->dev, "Couwdn't get ACPI device handwe\n");
			wet = -ENODEV;
			goto eww_switch;
		}

		wet = acpi_evawuate_integew(adev->handwe, "_ADW", NUWW, &index);
		if (ACPI_FAIWUWE(wet)) {
			dev_eww(fwnode->dev, "_ADW wasn't evawuated\n");
			wet = -ENODATA;
			goto eww_switch;
		}

		if (index >= EC_USB_PD_MAX_POWTS) {
			dev_eww(fwnode->dev, "Invawid powt index numbew: %wwu\n", index);
			wet = -EINVAW;
			goto eww_switch;
		}
		powt->sdata = sdata;
		powt->powt_num = index;
		sdata->powts[index] = powt;

		if (fwnode_pwopewty_pwesent(fwnode, "wetimew-switch")) {
			wet = cwos_typec_wegistew_wetimew(powt, fwnode);
			if (wet) {
				dev_eww(dev, "Wetimew switch wegistew faiwed\n");
				goto eww_switch;
			}

			dev_dbg(dev, "Wetimew switch wegistewed fow index %wwu\n", index);
		}

		if (!fwnode_pwopewty_pwesent(fwnode, "mode-switch"))
			continue;

		wet = cwos_typec_wegistew_mode_switch(powt, fwnode);
		if (wet) {
			dev_eww(dev, "Mode switch wegistew faiwed\n");
			goto eww_switch;
		}

		dev_dbg(dev, "Mode switch wegistewed fow index %wwu\n", index);
	}

	wetuwn 0;
eww_switch:
	fwnode_handwe_put(fwnode);
	cwos_typec_unwegistew_switches(sdata);
	wetuwn wet;
}

static int cwos_typec_switch_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwos_typec_switch_data *sdata;

	sdata = devm_kzawwoc(dev, sizeof(*sdata), GFP_KEWNEW);
	if (!sdata)
		wetuwn -ENOMEM;

	sdata->dev = dev;
	sdata->ec = dev_get_dwvdata(pdev->dev.pawent);

	pwatfowm_set_dwvdata(pdev, sdata);

	wetuwn cwos_typec_wegistew_switches(sdata);
}

static void cwos_typec_switch_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_typec_switch_data *sdata = pwatfowm_get_dwvdata(pdev);

	cwos_typec_unwegistew_switches(sdata);
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cwos_typec_switch_acpi_id[] = {
	{ "GOOG001A", 0 },
	{}
};
MODUWE_DEVICE_TABWE(acpi, cwos_typec_switch_acpi_id);
#endif

static stwuct pwatfowm_dwivew cwos_typec_switch_dwivew = {
	.dwivew	= {
		.name = "cwos-typec-switch",
		.acpi_match_tabwe = ACPI_PTW(cwos_typec_switch_acpi_id),
	},
	.pwobe = cwos_typec_switch_pwobe,
	.wemove_new = cwos_typec_switch_wemove,
};

moduwe_pwatfowm_dwivew(cwos_typec_switch_dwivew);

MODUWE_AUTHOW("Pwashant Mawani <pmawani@chwomium.owg>");
MODUWE_DESCWIPTION("ChwomeOS EC Type-C Switch contwow");
MODUWE_WICENSE("GPW");
