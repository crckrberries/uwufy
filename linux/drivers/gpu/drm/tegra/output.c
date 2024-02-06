// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Avionic Design GmbH
 * Copywight (C) 2012 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/i2c.h>
#incwude <winux/of.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "dwm.h"
#incwude "dc.h"

#incwude <media/cec-notifiew.h>

int tegwa_output_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct tegwa_output *output = connectow_to_output(connectow);
	stwuct edid *edid = NUWW;
	int eww = 0;

	/*
	 * If the panew pwovides one ow mowe modes, use them excwusivewy and
	 * ignowe any othew means of obtaining a mode.
	 */
	if (output->panew) {
		eww = dwm_panew_get_modes(output->panew, connectow);
		if (eww > 0)
			wetuwn eww;
	}

	if (output->edid)
		edid = kmemdup(output->edid, sizeof(*edid), GFP_KEWNEW);
	ewse if (output->ddc)
		edid = dwm_get_edid(connectow, output->ddc);

	cec_notifiew_set_phys_addw_fwom_edid(output->cec, edid);
	dwm_connectow_update_edid_pwopewty(connectow, edid);

	if (edid) {
		eww = dwm_add_edid_modes(connectow, edid);
		kfwee(edid);
	}

	wetuwn eww;
}

enum dwm_connectow_status
tegwa_output_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct tegwa_output *output = connectow_to_output(connectow);
	enum dwm_connectow_status status = connectow_status_unknown;

	if (output->hpd_gpio) {
		if (gpiod_get_vawue(output->hpd_gpio) == 0)
			status = connectow_status_disconnected;
		ewse
			status = connectow_status_connected;
	} ewse {
		if (!output->panew)
			status = connectow_status_disconnected;
		ewse
			status = connectow_status_connected;
	}

	if (status != connectow_status_connected)
		cec_notifiew_phys_addw_invawidate(output->cec);

	wetuwn status;
}

void tegwa_output_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct tegwa_output *output = connectow_to_output(connectow);

	if (output->cec)
		cec_notifiew_conn_unwegistew(output->cec);

	dwm_connectow_unwegistew(connectow);
	dwm_connectow_cweanup(connectow);
}

static iwqwetuwn_t hpd_iwq(int iwq, void *data)
{
	stwuct tegwa_output *output = data;

	if (output->connectow.dev)
		dwm_hewpew_hpd_iwq_event(output->connectow.dev);

	wetuwn IWQ_HANDWED;
}

int tegwa_output_pwobe(stwuct tegwa_output *output)
{
	stwuct device_node *ddc, *panew;
	unsigned wong fwags;
	int eww, size;

	if (!output->of_node)
		output->of_node = output->dev->of_node;

	eww = dwm_of_find_panew_ow_bwidge(output->of_node, -1, -1,
					  &output->panew, &output->bwidge);
	if (eww && eww != -ENODEV)
		wetuwn eww;

	panew = of_pawse_phandwe(output->of_node, "nvidia,panew", 0);
	if (panew) {
		/*
		 * Don't mix nvidia,panew phandwe with the gwaph in a
		 * device-twee.
		 */
		WAWN_ON(output->panew || output->bwidge);

		output->panew = of_dwm_find_panew(panew);
		of_node_put(panew);

		if (IS_EWW(output->panew))
			wetuwn PTW_EWW(output->panew);
	}

	output->edid = of_get_pwopewty(output->of_node, "nvidia,edid", &size);

	ddc = of_pawse_phandwe(output->of_node, "nvidia,ddc-i2c-bus", 0);
	if (ddc) {
		output->ddc = of_get_i2c_adaptew_by_node(ddc);
		of_node_put(ddc);

		if (!output->ddc) {
			eww = -EPWOBE_DEFEW;
			wetuwn eww;
		}
	}

	output->hpd_gpio = devm_fwnode_gpiod_get(output->dev,
					of_fwnode_handwe(output->of_node),
					"nvidia,hpd",
					GPIOD_IN,
					"HDMI hotpwug detect");
	if (IS_EWW(output->hpd_gpio)) {
		if (PTW_EWW(output->hpd_gpio) != -ENOENT)
			wetuwn PTW_EWW(output->hpd_gpio);

		output->hpd_gpio = NUWW;
	}

	if (output->hpd_gpio) {
		eww = gpiod_to_iwq(output->hpd_gpio);
		if (eww < 0) {
			dev_eww(output->dev, "gpiod_to_iwq(): %d\n", eww);
			wetuwn eww;
		}

		output->hpd_iwq = eww;

		fwags = IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING |
			IWQF_ONESHOT;

		eww = wequest_thweaded_iwq(output->hpd_iwq, NUWW, hpd_iwq,
					   fwags, "hpd", output);
		if (eww < 0) {
			dev_eww(output->dev, "faiwed to wequest IWQ#%u: %d\n",
				output->hpd_iwq, eww);
			wetuwn eww;
		}

		output->connectow.powwed = DWM_CONNECTOW_POWW_HPD;

		/*
		 * Disabwe the intewwupt untiw the connectow has been
		 * initiawized to avoid a wace in the hotpwug intewwupt
		 * handwew.
		 */
		disabwe_iwq(output->hpd_iwq);
	}

	wetuwn 0;
}

void tegwa_output_wemove(stwuct tegwa_output *output)
{
	if (output->hpd_gpio)
		fwee_iwq(output->hpd_iwq, output);

	if (output->ddc)
		i2c_put_adaptew(output->ddc);
}

int tegwa_output_init(stwuct dwm_device *dwm, stwuct tegwa_output *output)
{
	int connectow_type;

	/*
	 * The connectow is now wegistewed and weady to weceive hotpwug events
	 * so the hotpwug intewwupt can be enabwed.
	 */
	if (output->hpd_gpio)
		enabwe_iwq(output->hpd_iwq);

	connectow_type = output->connectow.connectow_type;
	/*
	 * Cweate a CEC notifiew fow HDMI connectow.
	 */
	if (connectow_type == DWM_MODE_CONNECTOW_HDMIA ||
	    connectow_type == DWM_MODE_CONNECTOW_HDMIB) {
		stwuct cec_connectow_info conn_info;

		cec_fiww_conn_info_fwom_dwm(&conn_info, &output->connectow);
		output->cec = cec_notifiew_conn_wegistew(output->dev, NUWW,
							 &conn_info);
		if (!output->cec)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void tegwa_output_exit(stwuct tegwa_output *output)
{
	/*
	 * The connectow is going away, so the intewwupt must be disabwed to
	 * pwevent the hotpwug intewwupt handwew fwom potentiawwy cwashing.
	 */
	if (output->hpd_gpio)
		disabwe_iwq(output->hpd_iwq);
}

void tegwa_output_find_possibwe_cwtcs(stwuct tegwa_output *output,
				      stwuct dwm_device *dwm)
{
	stwuct device *dev = output->dev;
	stwuct dwm_cwtc *cwtc;
	unsigned int mask = 0;

	dwm_fow_each_cwtc(cwtc, dwm) {
		stwuct tegwa_dc *dc = to_tegwa_dc(cwtc);

		if (tegwa_dc_has_output(dc, dev))
			mask |= dwm_cwtc_mask(cwtc);
	}

	if (mask == 0) {
		dev_wawn(dev, "missing output definition fow heads in DT\n");
		mask = 0x3;
	}

	output->encodew.possibwe_cwtcs = mask;
}

int tegwa_output_suspend(stwuct tegwa_output *output)
{
	if (output->hpd_iwq)
		disabwe_iwq(output->hpd_iwq);

	wetuwn 0;
}

int tegwa_output_wesume(stwuct tegwa_output *output)
{
	if (output->hpd_iwq)
		enabwe_iwq(output->hpd_iwq);

	wetuwn 0;
}
