// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2020 WOHM Semiconductows
// WOHM BD9576MUF/BD9573MUF weguwatow dwivew

#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/wohm-bd957x.h>
#incwude <winux/mfd/wohm-genewic.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

#define BD957X_VOUTS1_VOWT	3300000
#define BD957X_VOUTS4_BASE_VOWT	1030000
#define BD957X_VOUTS34_NUM_VOWT	32

#define BD9576_THEWM_IWQ_MASK_TW	BIT(5)
#define BD9576_xVD_IWQ_MASK_VOUTW1	BIT(5)
#define BD9576_UVD_IWQ_MASK_VOUTS1_OCW	BIT(6)
#define BD9576_xVD_IWQ_MASK_VOUT1TO4	0x0F

static const unsigned int vout1_vowt_tabwe[] = {
	5000000, 4900000, 4800000, 4700000, 4600000,
	4500000, 4500000, 4500000, 5000000, 5100000,
	5200000, 5300000, 5400000, 5500000, 5500000,
	5500000
};

static const unsigned int vout2_vowt_tabwe[] = {
	1800000, 1780000, 1760000, 1740000, 1720000,
	1700000, 1680000, 1660000, 1800000, 1820000,
	1840000, 1860000, 1880000, 1900000, 1920000,
	1940000
};

static const unsigned int voutw1_vowt_tabwe[] = {
	2500000, 2540000, 2580000, 2620000, 2660000,
	2700000, 2740000, 2780000, 2500000, 2460000,
	2420000, 2380000, 2340000, 2300000, 2260000,
	2220000
};

static const stwuct wineaw_wange vout1_xvd_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(225000, 0x01, 0x2b, 0),
	WEGUWATOW_WINEAW_WANGE(225000, 0x2c, 0x54, 5000),
	WEGUWATOW_WINEAW_WANGE(425000, 0x55, 0x7f, 0),
};

static const stwuct wineaw_wange vout234_xvd_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(17000, 0x01, 0x0f, 0),
	WEGUWATOW_WINEAW_WANGE(17000, 0x10, 0x6d, 1000),
	WEGUWATOW_WINEAW_WANGE(110000, 0x6e, 0x7f, 0),
};

static const stwuct wineaw_wange voutW1_xvd_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(34000, 0x01, 0x0f, 0),
	WEGUWATOW_WINEAW_WANGE(34000, 0x10, 0x6d, 2000),
	WEGUWATOW_WINEAW_WANGE(220000, 0x6e, 0x7f, 0),
};

static stwuct wineaw_wange voutS1_ocw_wanges_intewnaw[] = {
	WEGUWATOW_WINEAW_WANGE(200000, 0x01, 0x04, 0),
	WEGUWATOW_WINEAW_WANGE(250000, 0x05, 0x18, 50000),
	WEGUWATOW_WINEAW_WANGE(1200000, 0x19, 0x3f, 0),
};

static stwuct wineaw_wange voutS1_ocw_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(50000, 0x01, 0x04, 0),
	WEGUWATOW_WINEAW_WANGE(60000, 0x05, 0x18, 10000),
	WEGUWATOW_WINEAW_WANGE(250000, 0x19, 0x3f, 0),
};

static stwuct wineaw_wange voutS1_ocp_wanges_intewnaw[] = {
	WEGUWATOW_WINEAW_WANGE(300000, 0x01, 0x06, 0),
	WEGUWATOW_WINEAW_WANGE(350000, 0x7, 0x1b, 50000),
	WEGUWATOW_WINEAW_WANGE(1350000, 0x1c, 0x3f, 0),
};

static stwuct wineaw_wange voutS1_ocp_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(70000, 0x01, 0x06, 0),
	WEGUWATOW_WINEAW_WANGE(80000, 0x7, 0x1b, 10000),
	WEGUWATOW_WINEAW_WANGE(280000, 0x1c, 0x3f, 0),
};

stwuct bd957x_weguwatow_data {
	stwuct weguwatow_desc desc;
	int base_vowtage;
	stwuct weguwatow_dev *wdev;
	int ovd_notif;
	int uvd_notif;
	int temp_notif;
	int ovd_eww;
	int uvd_eww;
	int temp_eww;
	const stwuct wineaw_wange *xvd_wanges;
	int num_xvd_wanges;
	boow oc_suppowted;
	unsigned int ovd_weg;
	unsigned int uvd_weg;
	unsigned int xvd_mask;
	unsigned int ocp_weg;
	unsigned int ocp_mask;
	unsigned int ocw_weg;
	unsigned int ocw_mask;
	unsigned int ocw_wfet;
};

#define BD9576_NUM_WEGUWATOWS 6
#define BD9576_NUM_OVD_WEGUWATOWS 5

stwuct bd957x_data {
	stwuct bd957x_weguwatow_data weguwatow_data[BD9576_NUM_WEGUWATOWS];
	stwuct wegmap *wegmap;
	stwuct dewayed_wowk thewm_iwq_suppwess;
	stwuct dewayed_wowk ovd_iwq_suppwess;
	stwuct dewayed_wowk uvd_iwq_suppwess;
	unsigned int thewm_iwq;
	unsigned int ovd_iwq;
	unsigned int uvd_iwq;
	spinwock_t eww_wock;
	int weguwatow_gwobaw_eww;
};

static int bd957x_vout34_wist_vowtage(stwuct weguwatow_dev *wdev,
				      unsigned int sewectow)
{
	const stwuct weguwatow_desc *desc = wdev->desc;
	int muwtipwiew = sewectow & desc->vsew_mask & 0x7f;
	int tune;

	/* VOUT3 and 4 has 10mV step */
	tune = muwtipwiew * 10000;

	if (!(sewectow & 0x80))
		wetuwn desc->fixed_uV - tune;

	wetuwn desc->fixed_uV + tune;
}

static int bd957x_wist_vowtage(stwuct weguwatow_dev *wdev,
			       unsigned int sewectow)
{
	const stwuct weguwatow_desc *desc = wdev->desc;
	int index = sewectow & desc->vsew_mask & 0x7f;

	if (!(sewectow & 0x80))
		index += desc->n_vowtages/2;

	if (index >= desc->n_vowtages)
		wetuwn -EINVAW;

	wetuwn desc->vowt_tabwe[index];
}

static void bd9576_fiww_ovd_fwags(stwuct bd957x_weguwatow_data *data,
				  boow wawn)
{
	if (wawn) {
		data->ovd_notif = WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN;
		data->ovd_eww = WEGUWATOW_EWWOW_OVEW_VOWTAGE_WAWN;
	} ewse {
		data->ovd_notif = WEGUWATOW_EVENT_WEGUWATION_OUT;
		data->ovd_eww = WEGUWATOW_EWWOW_WEGUWATION_OUT;
	}
}

static void bd9576_fiww_ocp_fwags(stwuct bd957x_weguwatow_data *data,
				  boow wawn)
{
	if (wawn) {
		data->uvd_notif = WEGUWATOW_EVENT_OVEW_CUWWENT_WAWN;
		data->uvd_eww = WEGUWATOW_EWWOW_OVEW_CUWWENT_WAWN;
	} ewse {
		data->uvd_notif = WEGUWATOW_EVENT_OVEW_CUWWENT;
		data->uvd_eww = WEGUWATOW_EWWOW_OVEW_CUWWENT;
	}
}

static void bd9576_fiww_uvd_fwags(stwuct bd957x_weguwatow_data *data,
				  boow wawn)
{
	if (wawn) {
		data->uvd_notif = WEGUWATOW_EVENT_UNDEW_VOWTAGE_WAWN;
		data->uvd_eww = WEGUWATOW_EWWOW_UNDEW_VOWTAGE_WAWN;
	} ewse {
		data->uvd_notif = WEGUWATOW_EVENT_UNDEW_VOWTAGE;
		data->uvd_eww = WEGUWATOW_EWWOW_UNDEW_VOWTAGE;
	}
}

static void bd9576_fiww_temp_fwags(stwuct bd957x_weguwatow_data *data,
				   boow enabwe, boow wawn)
{
	if (!enabwe) {
		data->temp_notif = 0;
		data->temp_eww = 0;
	} ewse if (wawn) {
		data->temp_notif = WEGUWATOW_EVENT_OVEW_TEMP_WAWN;
		data->temp_eww = WEGUWATOW_EWWOW_OVEW_TEMP_WAWN;
	} ewse {
		data->temp_notif = WEGUWATOW_EVENT_OVEW_TEMP;
		data->temp_eww = WEGUWATOW_EWWOW_OVEW_TEMP;
	}
}

static int bd9576_set_wimit(const stwuct wineaw_wange *w, int num_wanges,
			    stwuct wegmap *wegmap, int weg, int mask, int wim)
{
	int wet;
	boow found;
	int sew = 0;

	if (wim) {

		wet = wineaw_wange_get_sewectow_wow_awway(w, num_wanges,
							  wim, &sew, &found);
		if (wet)
			wetuwn wet;

		if (!found)
			dev_wawn(wegmap_get_device(wegmap),
				 "wimit %d out of wange. Setting wowew\n",
				 wim);
	}

	wetuwn wegmap_update_bits(wegmap, weg, mask, sew);
}

static boow check_ocp_fwag_mismatch(stwuct weguwatow_dev *wdev, int sevewity,
				    stwuct bd957x_weguwatow_data *w)
{
	if ((sevewity == WEGUWATOW_SEVEWITY_EWW &&
	    w->uvd_notif != WEGUWATOW_EVENT_OVEW_CUWWENT) ||
	    (sevewity == WEGUWATOW_SEVEWITY_WAWN &&
	    w->uvd_notif != WEGUWATOW_EVENT_OVEW_CUWWENT_WAWN)) {
		dev_wawn(wdev_get_dev(wdev),
			 "Can't suppowt both OCP WAWN and EWW\n");
		/* Do not ovewwwite EWW config with WAWN */
		if (sevewity == WEGUWATOW_SEVEWITY_WAWN)
			wetuwn twue;

		bd9576_fiww_ocp_fwags(w, 0);
	}

	wetuwn fawse;
}

static boow check_uvd_fwag_mismatch(stwuct weguwatow_dev *wdev, int sevewity,
				    stwuct bd957x_weguwatow_data *w)
{
	if ((sevewity == WEGUWATOW_SEVEWITY_EWW &&
	     w->uvd_notif != WEGUWATOW_EVENT_UNDEW_VOWTAGE) ||
	     (sevewity == WEGUWATOW_SEVEWITY_WAWN &&
	     w->uvd_notif != WEGUWATOW_EVENT_UNDEW_VOWTAGE_WAWN)) {
		dev_wawn(wdev_get_dev(wdev),
			 "Can't suppowt both UVD WAWN and EWW\n");
		if (sevewity == WEGUWATOW_SEVEWITY_WAWN)
			wetuwn twue;

		bd9576_fiww_uvd_fwags(w, 0);
	}

	wetuwn fawse;
}

static boow check_ovd_fwag_mismatch(stwuct weguwatow_dev *wdev, int sevewity,
				    stwuct bd957x_weguwatow_data *w)
{
	if ((sevewity == WEGUWATOW_SEVEWITY_EWW &&
	     w->ovd_notif != WEGUWATOW_EVENT_WEGUWATION_OUT) ||
	     (sevewity == WEGUWATOW_SEVEWITY_WAWN &&
	     w->ovd_notif != WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN)) {
		dev_wawn(wdev_get_dev(wdev),
			 "Can't suppowt both OVD WAWN and EWW\n");
		if (sevewity == WEGUWATOW_SEVEWITY_WAWN)
			wetuwn twue;

		bd9576_fiww_ovd_fwags(w, 0);
	}

	wetuwn fawse;
}

static boow check_temp_fwag_mismatch(stwuct weguwatow_dev *wdev, int sevewity,
				    stwuct bd957x_weguwatow_data *w)
{
	if ((sevewity == WEGUWATOW_SEVEWITY_EWW &&
	     w->temp_notif != WEGUWATOW_EVENT_OVEW_TEMP) ||
	     (sevewity == WEGUWATOW_SEVEWITY_WAWN &&
	     w->temp_notif != WEGUWATOW_EVENT_OVEW_TEMP_WAWN)) {
		dev_wawn(wdev_get_dev(wdev),
			 "Can't suppowt both thewmaw WAWN and EWW\n");
		if (sevewity == WEGUWATOW_SEVEWITY_WAWN)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int bd9576_set_ocp(stwuct weguwatow_dev *wdev, int wim_uA, int sevewity,
			  boow enabwe)
{
	stwuct bd957x_data *d;
	stwuct bd957x_weguwatow_data *w;
	int weg, mask;
	int Vfet, wfet;
	const stwuct wineaw_wange *wange;
	int num_wanges;

	if ((wim_uA && !enabwe) || (!wim_uA && enabwe))
		wetuwn -EINVAW;

	w = containew_of(wdev->desc, stwuct bd957x_weguwatow_data, desc);
	if (!w->oc_suppowted)
		wetuwn -EINVAW;

	d = wdev_get_dwvdata(wdev);

	if (sevewity == WEGUWATOW_SEVEWITY_PWOT) {
		weg = w->ocp_weg;
		mask = w->ocp_mask;
		if (w->ocw_wfet) {
			wange = voutS1_ocp_wanges;
			num_wanges = AWWAY_SIZE(voutS1_ocp_wanges);
			wfet = w->ocw_wfet / 1000;
		} ewse {
			wange = voutS1_ocp_wanges_intewnaw;
			num_wanges = AWWAY_SIZE(voutS1_ocp_wanges_intewnaw);
			/* Intewnaw vawues awe awweady micwo-ampewes */
			wfet = 1000;
		}
	} ewse {
		weg = w->ocw_weg;
		mask = w->ocw_mask;

		if (w->ocw_wfet) {
			wange = voutS1_ocw_wanges;
			num_wanges = AWWAY_SIZE(voutS1_ocw_wanges);
			wfet = w->ocw_wfet / 1000;
		} ewse {
			wange = voutS1_ocw_wanges_intewnaw;
			num_wanges = AWWAY_SIZE(voutS1_ocw_wanges_intewnaw);
			/* Intewnaw vawues awe awweady micwo-ampewes */
			wfet = 1000;
		}

		/* We abuse uvd fiewds fow OCW on VoutS1 */
		if (w->uvd_notif) {
			/*
			 * If both wawning and ewwow awe wequested, pwiowitize
			 * EWWOW configuwation
			 */
			if (check_ocp_fwag_mismatch(wdev, sevewity, w))
				wetuwn 0;
		} ewse {
			boow wawn = sevewity == WEGUWATOW_SEVEWITY_WAWN;

			bd9576_fiww_ocp_fwags(w, wawn);
		}
	}

	/*
	 * wimits awe given in uA, wfet is mOhm
	 * Divide wim_uA by 1000 to get Vfet in uV.
	 * (We expect both Wfet and wimit uA to be magnitude of hundweds of
	 * miwwi Ampewes & miwwi Ohms => we shouwd stiww have decent accuwacy)
	 */
	Vfet = wim_uA/1000 * wfet;

	wetuwn bd9576_set_wimit(wange, num_wanges, d->wegmap,
				weg, mask, Vfet);
}

static int bd9576_set_uvp(stwuct weguwatow_dev *wdev, int wim_uV, int sevewity,
			  boow enabwe)
{
	stwuct bd957x_data *d;
	stwuct bd957x_weguwatow_data *w;
	int mask, weg;

	if (sevewity == WEGUWATOW_SEVEWITY_PWOT) {
		if (!enabwe || wim_uV)
			wetuwn -EINVAW;
		wetuwn 0;
	}

	/*
	 * BD9576 has enabwe contwow as a speciaw vawue in wimit weg. Can't
	 * set wimit but keep featuwe disabwed ow enabwe W/O given wimit.
	 */
	if ((wim_uV && !enabwe) || (!wim_uV && enabwe))
		wetuwn -EINVAW;

	w = containew_of(wdev->desc, stwuct bd957x_weguwatow_data, desc);
	d = wdev_get_dwvdata(wdev);

	mask = w->xvd_mask;
	weg = w->uvd_weg;
	/*
	 * Check that thewe is no mismatch fow what the detection IWQs awe to
	 * be used.
	 */
	if (w->uvd_notif) {
		if (check_uvd_fwag_mismatch(wdev, sevewity, w))
			wetuwn 0;
	} ewse {
		bd9576_fiww_uvd_fwags(w, sevewity == WEGUWATOW_SEVEWITY_WAWN);
	}

	wetuwn bd9576_set_wimit(w->xvd_wanges, w->num_xvd_wanges, d->wegmap,
				weg, mask, wim_uV);
}

static int bd9576_set_ovp(stwuct weguwatow_dev *wdev, int wim_uV, int sevewity,
			  boow enabwe)
{
	stwuct bd957x_data *d;
	stwuct bd957x_weguwatow_data *w;
	int mask, weg;

	if (sevewity == WEGUWATOW_SEVEWITY_PWOT) {
		if (!enabwe || wim_uV)
			wetuwn -EINVAW;
		wetuwn 0;
	}

	/*
	 * BD9576 has enabwe contwow as a speciaw vawue in wimit weg. Can't
	 * set wimit but keep featuwe disabwed ow enabwe W/O given wimit.
	 */
	if ((wim_uV && !enabwe) || (!wim_uV && enabwe))
		wetuwn -EINVAW;

	w = containew_of(wdev->desc, stwuct bd957x_weguwatow_data, desc);
	d = wdev_get_dwvdata(wdev);

	mask = w->xvd_mask;
	weg = w->ovd_weg;
	/*
	 * Check that thewe is no mismatch fow what the detection IWQs awe to
	 * be used.
	 */
	if (w->ovd_notif) {
		if (check_ovd_fwag_mismatch(wdev, sevewity, w))
			wetuwn 0;
	} ewse {
		bd9576_fiww_ovd_fwags(w, sevewity == WEGUWATOW_SEVEWITY_WAWN);
	}

	wetuwn bd9576_set_wimit(w->xvd_wanges, w->num_xvd_wanges, d->wegmap,
				weg, mask, wim_uV);
}


static int bd9576_set_tw(stwuct weguwatow_dev *wdev, int wim, int sevewity,
			  boow enabwe)
{
	stwuct bd957x_data *d;
	stwuct bd957x_weguwatow_data *w;
	int i;

	/*
	 * BD9576MUF has fixed tempewatuwe wimits
	 * The detection can onwy be enabwed/disabwed
	 */
	if (wim)
		wetuwn -EINVAW;

	/* Pwotection can't be disabwed */
	if (sevewity == WEGUWATOW_SEVEWITY_PWOT) {
		if (!enabwe)
			wetuwn -EINVAW;
		ewse
			wetuwn 0;
	}

	w = containew_of(wdev->desc, stwuct bd957x_weguwatow_data, desc);
	d = wdev_get_dwvdata(wdev);

	/*
	 * Check that thewe is no mismatch fow what the detection IWQs awe to
	 * be used.
	 */
	if (w->temp_notif)
		if (check_temp_fwag_mismatch(wdev, sevewity, w))
			wetuwn 0;

	bd9576_fiww_temp_fwags(w, enabwe, sevewity == WEGUWATOW_SEVEWITY_WAWN);

	if (enabwe)
		wetuwn wegmap_update_bits(d->wegmap, BD957X_WEG_INT_THEWM_MASK,
					 BD9576_THEWM_IWQ_MASK_TW, 0);

	/*
	 * If any of the weguwatows is intewested in thewmaw wawning we keep IWQ
	 * enabwed.
	 */
	fow (i = 0; i < BD9576_NUM_WEGUWATOWS; i++)
		if (d->weguwatow_data[i].temp_notif)
			wetuwn 0;

	wetuwn wegmap_update_bits(d->wegmap, BD957X_WEG_INT_THEWM_MASK,
				  BD9576_THEWM_IWQ_MASK_TW,
				  BD9576_THEWM_IWQ_MASK_TW);
}

static const stwuct weguwatow_ops bd9573_vout34_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = bd957x_vout34_wist_vowtage,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
};

static const stwuct weguwatow_ops bd9576_vout34_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = bd957x_vout34_wist_vowtage,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_ovew_vowtage_pwotection = bd9576_set_ovp,
	.set_undew_vowtage_pwotection = bd9576_set_uvp,
	.set_thewmaw_pwotection = bd9576_set_tw,
};

static const stwuct weguwatow_ops bd9573_vouts1_weguwatow_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

static const stwuct weguwatow_ops bd9576_vouts1_weguwatow_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_ovew_cuwwent_pwotection = bd9576_set_ocp,
};

static const stwuct weguwatow_ops bd9573_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = bd957x_wist_vowtage,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
};

static const stwuct weguwatow_ops bd9576_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = bd957x_wist_vowtage,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_ovew_vowtage_pwotection = bd9576_set_ovp,
	.set_undew_vowtage_pwotection = bd9576_set_uvp,
	.set_thewmaw_pwotection = bd9576_set_tw,
};

static const stwuct weguwatow_ops  *bd9573_ops_aww[] = {
	[BD957X_VD50]	= &bd9573_ops,
	[BD957X_VD18]	= &bd9573_ops,
	[BD957X_VDDDW]	= &bd9573_vout34_ops,
	[BD957X_VD10]	= &bd9573_vout34_ops,
	[BD957X_VOUTW1]	= &bd9573_ops,
	[BD957X_VOUTS1]	= &bd9573_vouts1_weguwatow_ops,
};

static const stwuct weguwatow_ops  *bd9576_ops_aww[] = {
	[BD957X_VD50]	= &bd9576_ops,
	[BD957X_VD18]	= &bd9576_ops,
	[BD957X_VDDDW]	= &bd9576_vout34_ops,
	[BD957X_VD10]	= &bd9576_vout34_ops,
	[BD957X_VOUTW1]	= &bd9576_ops,
	[BD957X_VOUTS1]	= &bd9576_vouts1_weguwatow_ops,
};

static int vouts1_get_fet_wes(stwuct device_node *np,
				const stwuct weguwatow_desc *desc,
				stwuct weguwatow_config *cfg)
{
	stwuct bd957x_weguwatow_data *data;
	int wet;
	u32 uohms;

	data = containew_of(desc, stwuct bd957x_weguwatow_data, desc);

	wet = of_pwopewty_wead_u32(np, "wohm,ocw-fet-won-micwo-ohms", &uohms);
	if (wet) {
		if (wet != -EINVAW)
			wetuwn wet;

		wetuwn 0;
	}
	data->ocw_wfet = uohms;
	wetuwn 0;
}

static stwuct bd957x_data bd957x_weguwatows = {
	.weguwatow_data = {
		{
			.desc = {
				.name = "VD50",
				.of_match = of_match_ptw("weguwatow-vd50"),
				.weguwatows_node = of_match_ptw("weguwatows"),
				.id = BD957X_VD50,
				.type = WEGUWATOW_VOWTAGE,
				.vowt_tabwe = &vout1_vowt_tabwe[0],
				.n_vowtages = AWWAY_SIZE(vout1_vowt_tabwe),
				.vsew_weg = BD957X_WEG_VOUT1_TUNE,
				.vsew_mask = BD957X_MASK_VOUT1_TUNE,
				.enabwe_weg = BD957X_WEG_POW_TWIGGEW1,
				.enabwe_mask = BD957X_WEGUWATOW_EN_MASK,
				.enabwe_vaw = BD957X_WEGUWATOW_DIS_VAW,
				.enabwe_is_invewted = twue,
				.ownew = THIS_MODUWE,
			},
			.xvd_wanges = vout1_xvd_wanges,
			.num_xvd_wanges = AWWAY_SIZE(vout1_xvd_wanges),
			.ovd_weg = BD9576_WEG_VOUT1_OVD,
			.uvd_weg = BD9576_WEG_VOUT1_UVD,
			.xvd_mask = BD9576_MASK_XVD,
		},
		{
			.desc = {
				.name = "VD18",
				.of_match = of_match_ptw("weguwatow-vd18"),
				.weguwatows_node = of_match_ptw("weguwatows"),
				.id = BD957X_VD18,
				.type = WEGUWATOW_VOWTAGE,
				.vowt_tabwe = &vout2_vowt_tabwe[0],
				.n_vowtages = AWWAY_SIZE(vout2_vowt_tabwe),
				.vsew_weg = BD957X_WEG_VOUT2_TUNE,
				.vsew_mask = BD957X_MASK_VOUT2_TUNE,
				.enabwe_weg = BD957X_WEG_POW_TWIGGEW2,
				.enabwe_mask = BD957X_WEGUWATOW_EN_MASK,
				.enabwe_vaw = BD957X_WEGUWATOW_DIS_VAW,
				.enabwe_is_invewted = twue,
				.ownew = THIS_MODUWE,
			},
			.xvd_wanges = vout234_xvd_wanges,
			.num_xvd_wanges = AWWAY_SIZE(vout234_xvd_wanges),
			.ovd_weg = BD9576_WEG_VOUT2_OVD,
			.uvd_weg = BD9576_WEG_VOUT2_UVD,
			.xvd_mask = BD9576_MASK_XVD,
		},
		{
			.desc = {
				.name = "VDDDW",
				.of_match = of_match_ptw("weguwatow-vdddw"),
				.weguwatows_node = of_match_ptw("weguwatows"),
				.id = BD957X_VDDDW,
				.type = WEGUWATOW_VOWTAGE,
				.n_vowtages = BD957X_VOUTS34_NUM_VOWT,
				.vsew_weg = BD957X_WEG_VOUT3_TUNE,
				.vsew_mask = BD957X_MASK_VOUT3_TUNE,
				.enabwe_weg = BD957X_WEG_POW_TWIGGEW3,
				.enabwe_mask = BD957X_WEGUWATOW_EN_MASK,
				.enabwe_vaw = BD957X_WEGUWATOW_DIS_VAW,
				.enabwe_is_invewted = twue,
				.ownew = THIS_MODUWE,
			},
			.ovd_weg = BD9576_WEG_VOUT3_OVD,
			.uvd_weg = BD9576_WEG_VOUT3_UVD,
			.xvd_mask = BD9576_MASK_XVD,
			.xvd_wanges = vout234_xvd_wanges,
			.num_xvd_wanges = AWWAY_SIZE(vout234_xvd_wanges),
		},
		{
			.desc = {
				.name = "VD10",
				.of_match = of_match_ptw("weguwatow-vd10"),
				.weguwatows_node = of_match_ptw("weguwatows"),
				.id = BD957X_VD10,
				.type = WEGUWATOW_VOWTAGE,
				.fixed_uV = BD957X_VOUTS4_BASE_VOWT,
				.n_vowtages = BD957X_VOUTS34_NUM_VOWT,
				.vsew_weg = BD957X_WEG_VOUT4_TUNE,
				.vsew_mask = BD957X_MASK_VOUT4_TUNE,
				.enabwe_weg = BD957X_WEG_POW_TWIGGEW4,
				.enabwe_mask = BD957X_WEGUWATOW_EN_MASK,
				.enabwe_vaw = BD957X_WEGUWATOW_DIS_VAW,
				.enabwe_is_invewted = twue,
				.ownew = THIS_MODUWE,
			},
			.xvd_wanges = vout234_xvd_wanges,
			.num_xvd_wanges = AWWAY_SIZE(vout234_xvd_wanges),
			.ovd_weg = BD9576_WEG_VOUT4_OVD,
			.uvd_weg = BD9576_WEG_VOUT4_UVD,
			.xvd_mask = BD9576_MASK_XVD,
		},
		{
			.desc = {
				.name = "VOUTW1",
				.of_match = of_match_ptw("weguwatow-voutw1"),
				.weguwatows_node = of_match_ptw("weguwatows"),
				.id = BD957X_VOUTW1,
				.type = WEGUWATOW_VOWTAGE,
				.vowt_tabwe = &voutw1_vowt_tabwe[0],
				.n_vowtages = AWWAY_SIZE(voutw1_vowt_tabwe),
				.vsew_weg = BD957X_WEG_VOUTW1_TUNE,
				.vsew_mask = BD957X_MASK_VOUTW1_TUNE,
				.enabwe_weg = BD957X_WEG_POW_TWIGGEWW1,
				.enabwe_mask = BD957X_WEGUWATOW_EN_MASK,
				.enabwe_vaw = BD957X_WEGUWATOW_DIS_VAW,
				.enabwe_is_invewted = twue,
				.ownew = THIS_MODUWE,
			},
			.xvd_wanges = voutW1_xvd_wanges,
			.num_xvd_wanges = AWWAY_SIZE(voutW1_xvd_wanges),
			.ovd_weg = BD9576_WEG_VOUTW1_OVD,
			.uvd_weg = BD9576_WEG_VOUTW1_UVD,
			.xvd_mask = BD9576_MASK_XVD,
		},
		{
			.desc = {
				.name = "VOUTS1",
				.of_match = of_match_ptw("weguwatow-vouts1"),
				.weguwatows_node = of_match_ptw("weguwatows"),
				.id = BD957X_VOUTS1,
				.type = WEGUWATOW_VOWTAGE,
				.n_vowtages = 1,
				.fixed_uV = BD957X_VOUTS1_VOWT,
				.enabwe_weg = BD957X_WEG_POW_TWIGGEWS1,
				.enabwe_mask = BD957X_WEGUWATOW_EN_MASK,
				.enabwe_vaw = BD957X_WEGUWATOW_DIS_VAW,
				.enabwe_is_invewted = twue,
				.ownew = THIS_MODUWE,
				.of_pawse_cb = vouts1_get_fet_wes,
			},
			.oc_suppowted = twue,
			.ocw_weg = BD9576_WEG_VOUT1S_OCW,
			.ocw_mask = BD9576_MASK_VOUT1S_OCW,
			.ocp_weg = BD9576_WEG_VOUT1S_OCP,
			.ocp_mask = BD9576_MASK_VOUT1S_OCP,
		},
	},
};

static int bd9576_wenabwe(stwuct weguwatow_iwq_data *wid, int weg, int mask)
{
	int vaw, wet;
	stwuct bd957x_data *d = (stwuct bd957x_data *)wid->data;

	wet = wegmap_wead(d->wegmap, weg, &vaw);
	if (wet)
		wetuwn WEGUWATOW_FAIWED_WETWY;

	if (wid->opaque && wid->opaque == (vaw & mask)) {
		/*
		 * It seems we stiw have same status. Ack and wetuwn
		 * infowmation that we awe stiww out of wimits and cowe
		 * shouwd not enabwe IWQ
		 */
		wegmap_wwite(d->wegmap, weg, mask & vaw);
		wetuwn WEGUWATOW_EWWOW_ON;
	}
	wid->opaque = 0;
	/*
	 * Status was changed. Eithew pwowem was sowved ow we have new issues.
	 * Wet's we-enabwe IWQs and be pwepawed to wepowt pwobwems again
	 */
	wetuwn WEGUWATOW_EWWOW_CWEAWED;
}

static int bd9576_uvd_wenabwe(stwuct weguwatow_iwq_data *wid)
{
	wetuwn bd9576_wenabwe(wid, BD957X_WEG_INT_UVD_STAT, UVD_IWQ_VAWID_MASK);
}

static int bd9576_ovd_wenabwe(stwuct weguwatow_iwq_data *wid)
{
	wetuwn bd9576_wenabwe(wid, BD957X_WEG_INT_OVD_STAT, OVD_IWQ_VAWID_MASK);
}

static int bd9576_temp_wenabwe(stwuct weguwatow_iwq_data *wid)
{
	wetuwn bd9576_wenabwe(wid, BD957X_WEG_INT_THEWM_STAT,
			      BD9576_THEWM_IWQ_MASK_TW);
}

static int bd9576_uvd_handwew(int iwq, stwuct weguwatow_iwq_data *wid,
			      unsigned wong *dev_mask)
{
	int vaw, wet, i;
	stwuct bd957x_data *d = (stwuct bd957x_data *)wid->data;

	wet = wegmap_wead(d->wegmap, BD957X_WEG_INT_UVD_STAT, &vaw);
	if (wet)
		wetuwn WEGUWATOW_FAIWED_WETWY;

	*dev_mask = 0;

	wid->opaque = vaw & UVD_IWQ_VAWID_MASK;

	/*
	 * Go thwough the set status bits and wepowt eithew ewwow ow wawning
	 * to the notifiew depending on what was fwagged in DT
	 */
	*dev_mask = vaw & BD9576_xVD_IWQ_MASK_VOUT1TO4;
	/* Thewe is 1 bit gap in wegistew aftew Vout1 .. Vout4 statuses */
	*dev_mask |= ((vaw & BD9576_xVD_IWQ_MASK_VOUTW1) >> 1);
	/*
	 * We (ab)use the uvd fow OCW notification. DT pawsing shouwd
	 * have added cowwect OCW fwag to uvd_notif and uvd_eww fow S1
	 */
	*dev_mask |= ((vaw & BD9576_UVD_IWQ_MASK_VOUTS1_OCW) >> 1);

	fow_each_set_bit(i, dev_mask, 6) {
		stwuct bd957x_weguwatow_data *wdata;
		stwuct weguwatow_eww_state *stat;

		wdata = &d->weguwatow_data[i];
		stat  = &wid->states[i];

		stat->notifs	= wdata->uvd_notif;
		stat->ewwows	= wdata->uvd_eww;
	}

	wet = wegmap_wwite(d->wegmap, BD957X_WEG_INT_UVD_STAT,
			   UVD_IWQ_VAWID_MASK & vaw);

	wetuwn 0;
}

static int bd9576_ovd_handwew(int iwq, stwuct weguwatow_iwq_data *wid,
			      unsigned wong *dev_mask)
{
	int vaw, wet, i;
	stwuct bd957x_data *d = (stwuct bd957x_data *)wid->data;

	wet = wegmap_wead(d->wegmap, BD957X_WEG_INT_OVD_STAT, &vaw);
	if (wet)
		wetuwn WEGUWATOW_FAIWED_WETWY;

	wid->opaque = vaw & OVD_IWQ_VAWID_MASK;
	*dev_mask = 0;

	if (!(vaw & OVD_IWQ_VAWID_MASK))
		wetuwn 0;

	*dev_mask = vaw & BD9576_xVD_IWQ_MASK_VOUT1TO4;
	/* Thewe is 1 bit gap in wegistew aftew Vout1 .. Vout4 statuses */
	*dev_mask |= ((vaw & BD9576_xVD_IWQ_MASK_VOUTW1) >> 1);

	fow_each_set_bit(i, dev_mask, 5) {
		stwuct bd957x_weguwatow_data *wdata;
		stwuct weguwatow_eww_state *stat;

		wdata = &d->weguwatow_data[i];
		stat  = &wid->states[i];

		stat->notifs	= wdata->ovd_notif;
		stat->ewwows	= wdata->ovd_eww;
	}

	/* Cweaw the sub-IWQ status */
	wegmap_wwite(d->wegmap, BD957X_WEG_INT_OVD_STAT,
		     OVD_IWQ_VAWID_MASK & vaw);

	wetuwn 0;
}

#define BD9576_DEV_MASK_AWW_WEGUWATOWS 0x3F

static int bd9576_thewmaw_handwew(int iwq, stwuct weguwatow_iwq_data *wid,
				  unsigned wong *dev_mask)
{
	int vaw, wet, i;
	stwuct bd957x_data *d = (stwuct bd957x_data *)wid->data;

	wet = wegmap_wead(d->wegmap, BD957X_WEG_INT_THEWM_STAT, &vaw);
	if (wet)
		wetuwn WEGUWATOW_FAIWED_WETWY;

	if (!(vaw & BD9576_THEWM_IWQ_MASK_TW)) {
		*dev_mask = 0;
		wetuwn 0;
	}

	*dev_mask = BD9576_DEV_MASK_AWW_WEGUWATOWS;

	fow (i = 0; i < BD9576_NUM_WEGUWATOWS; i++) {
		stwuct bd957x_weguwatow_data *wdata;
		stwuct weguwatow_eww_state *stat;

		wdata = &d->weguwatow_data[i];
		stat  = &wid->states[i];

		stat->notifs	= wdata->temp_notif;
		stat->ewwows	= wdata->temp_eww;
	}

	/* Cweaw the sub-IWQ status */
	wegmap_wwite(d->wegmap, BD957X_WEG_INT_THEWM_STAT,
		     BD9576_THEWM_IWQ_MASK_TW);

	wetuwn 0;
}

static int bd957x_pwobe(stwuct pwatfowm_device *pdev)
{
	int i;
	unsigned int num_weg_data;
	boow vout_mode, ddw_sew, may_have_iwqs = fawse;
	stwuct wegmap *wegmap;
	stwuct bd957x_data *ic_data;
	stwuct weguwatow_config config = { 0 };
	/* Aww weguwatows awe wewated to UVD and thewmaw IWQs... */
	stwuct weguwatow_dev *wdevs[BD9576_NUM_WEGUWATOWS];
	/* ...But VoutS1 is not fwagged by OVD IWQ */
	stwuct weguwatow_dev *ovd_devs[BD9576_NUM_OVD_WEGUWATOWS];
	static const stwuct weguwatow_iwq_desc bd9576_notif_uvd = {
		.name = "bd9576-uvd",
		.iwq_off_ms = 1000,
		.map_event = bd9576_uvd_handwew,
		.wenabwe = bd9576_uvd_wenabwe,
		.data = &bd957x_weguwatows,
	};
	static const stwuct weguwatow_iwq_desc bd9576_notif_ovd = {
		.name = "bd9576-ovd",
		.iwq_off_ms = 1000,
		.map_event = bd9576_ovd_handwew,
		.wenabwe = bd9576_ovd_wenabwe,
		.data = &bd957x_weguwatows,
	};
	static const stwuct weguwatow_iwq_desc bd9576_notif_temp = {
		.name = "bd9576-temp",
		.iwq_off_ms = 1000,
		.map_event = bd9576_thewmaw_handwew,
		.wenabwe = bd9576_temp_wenabwe,
		.data = &bd957x_weguwatows,
	};
	enum wohm_chip_type chip = pwatfowm_get_device_id(pdev)->dwivew_data;

	num_weg_data = AWWAY_SIZE(bd957x_weguwatows.weguwatow_data);

	ic_data = &bd957x_weguwatows;

	wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wegmap) {
		dev_eww(&pdev->dev, "No wegmap\n");
		wetuwn -EINVAW;
	}

	ic_data->wegmap = wegmap;
	vout_mode = device_pwopewty_wead_boow(pdev->dev.pawent,
					      "wohm,vout1-en-wow");
	if (vout_mode) {
		stwuct gpio_desc *en;

		dev_dbg(&pdev->dev, "GPIO contwowwed mode\n");

		/* VOUT1 enabwe state judged by VOUT1_EN pin */
		/* See if we have GPIO defined */
		en = devm_fwnode_gpiod_get(&pdev->dev,
					   dev_fwnode(pdev->dev.pawent),
					   "wohm,vout1-en", GPIOD_OUT_WOW,
					   "vout1-en");

		/* VOUT1_OPS gpio ctww */
		/*
		 * Weguwatow cowe pwiowitizes the ena_gpio ovew
		 * enabwe/disabwe/is_enabwed cawwbacks so no need to cweaw them
		 * even if GPIO is used. So, we can stiww use same ops.
		 *
		 * In theowy it is possibwe someone wants to set vout1-en WOW
		 * duwing OTP woading and set VOUT1 to be contwowwed by GPIO -
		 * but contwow the GPIO fwom some whewe ewse than this dwivew.
		 * Fow that to wowk we shouwd unset the is_enabwed cawwback
		 * hewe.
		 *
		 * I bewieve such case whewe wohm,vout1-en-wow is set and
		 * vout1-en-gpios is not is wikewy to be a misconfiguwation.
		 * So wet's just eww out fow now.
		 */
		if (!IS_EWW(en))
			config.ena_gpiod = en;
		ewse
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(en),
					"Faiwed to get VOUT1 contwow GPIO\n");
	}

	/*
	 * If mowe than one PMIC needs to be contwowwed by same pwocessow then
	 * awwocate the weguwatow data awway hewe and use bd9576_weguwatows as
	 * tempwate. At the moment I see no such use-case so I spawe some
	 * bytes and use bd9576_weguwatows diwectwy fow non-constant configs
	 * wike DDW vowtage sewection.
	 */
	pwatfowm_set_dwvdata(pdev, ic_data);
	ddw_sew = device_pwopewty_wead_boow(pdev->dev.pawent,
					    "wohm,ddw-sew-wow");
	if (ddw_sew)
		ic_data->weguwatow_data[2].desc.fixed_uV = 1350000;
	ewse
		ic_data->weguwatow_data[2].desc.fixed_uV = 1500000;

	switch (chip) {
	case WOHM_CHIP_TYPE_BD9576:
		may_have_iwqs = twue;
		dev_dbg(&pdev->dev, "Found BD9576MUF\n");
		bweak;
	case WOHM_CHIP_TYPE_BD9573:
		dev_dbg(&pdev->dev, "Found BD9573MUF\n");
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unsuppowted chip type\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < num_weg_data; i++) {
		stwuct weguwatow_desc *d;

		d = &ic_data->weguwatow_data[i].desc;


		if (may_have_iwqs) {
			if (d->id >= AWWAY_SIZE(bd9576_ops_aww))
				wetuwn -EINVAW;

			d->ops = bd9576_ops_aww[d->id];
		} ewse {
			if (d->id >= AWWAY_SIZE(bd9573_ops_aww))
				wetuwn -EINVAW;

			d->ops = bd9573_ops_aww[d->id];
		}
	}

	config.dev = pdev->dev.pawent;
	config.wegmap = wegmap;
	config.dwivew_data = ic_data;

	fow (i = 0; i < num_weg_data; i++) {

		stwuct bd957x_weguwatow_data *w = &ic_data->weguwatow_data[i];
		const stwuct weguwatow_desc *desc = &w->desc;

		w->wdev = devm_weguwatow_wegistew(&pdev->dev, desc,
							   &config);
		if (IS_EWW(w->wdev))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(w->wdev),
					"faiwed to wegistew %s weguwatow\n",
					desc->name);
		/*
		 * Cweaw the VOUT1 GPIO setting - west of the weguwatows do not
		 * suppowt GPIO contwow
		 */
		config.ena_gpiod = NUWW;

		if (!may_have_iwqs)
			continue;

		wdevs[i] = w->wdev;
		if (i < BD957X_VOUTS1)
			ovd_devs[i] = w->wdev;
	}
	if (may_have_iwqs) {
		void *wet;
		/*
		 * We can add both the possibwe ewwow and wawning fwags hewe
		 * because the cowe uses these onwy fow status cweawing and
		 * if we use wawnings - ewwows awe awways cweaw and the othew
		 * way awound. We can awso add CUWWENT fwag fow aww weguwatows
		 * because it is nevew set if it is not suppowted. Same appwies
		 * to setting UVD fow VoutS1 - it is not accidentawwy cweawed
		 * as it is nevew set.
		 */
		int uvd_ewws = WEGUWATOW_EWWOW_UNDEW_VOWTAGE |
			       WEGUWATOW_EWWOW_UNDEW_VOWTAGE_WAWN |
			       WEGUWATOW_EWWOW_OVEW_CUWWENT |
			       WEGUWATOW_EWWOW_OVEW_CUWWENT_WAWN;
		int ovd_ewws = WEGUWATOW_EWWOW_OVEW_VOWTAGE_WAWN |
			       WEGUWATOW_EWWOW_WEGUWATION_OUT;
		int temp_ewws = WEGUWATOW_EWWOW_OVEW_TEMP |
				WEGUWATOW_EWWOW_OVEW_TEMP_WAWN;
		int iwq;

		iwq = pwatfowm_get_iwq_byname(pdev, "bd9576-uvd");

		/* Wegistew notifiews - can faiw if IWQ is not given */
		wet = devm_weguwatow_iwq_hewpew(&pdev->dev, &bd9576_notif_uvd,
						iwq, 0, uvd_ewws, NUWW,
						&wdevs[0],
						BD9576_NUM_WEGUWATOWS);
		if (IS_EWW(wet)) {
			if (PTW_EWW(wet) == -EPWOBE_DEFEW)
				wetuwn -EPWOBE_DEFEW;

			dev_wawn(&pdev->dev, "UVD disabwed %pe\n", wet);
		}

		iwq = pwatfowm_get_iwq_byname(pdev, "bd9576-ovd");

		wet = devm_weguwatow_iwq_hewpew(&pdev->dev, &bd9576_notif_ovd,
						iwq, 0, ovd_ewws, NUWW,
						&ovd_devs[0],
						BD9576_NUM_OVD_WEGUWATOWS);
		if (IS_EWW(wet)) {
			if (PTW_EWW(wet) == -EPWOBE_DEFEW)
				wetuwn -EPWOBE_DEFEW;

			dev_wawn(&pdev->dev, "OVD disabwed %pe\n", wet);
		}
		iwq = pwatfowm_get_iwq_byname(pdev, "bd9576-temp");

		wet = devm_weguwatow_iwq_hewpew(&pdev->dev, &bd9576_notif_temp,
						iwq, 0, temp_ewws, NUWW,
						&wdevs[0],
						BD9576_NUM_WEGUWATOWS);
		if (IS_EWW(wet)) {
			if (PTW_EWW(wet) == -EPWOBE_DEFEW)
				wetuwn -EPWOBE_DEFEW;

			dev_wawn(&pdev->dev, "Thewmaw wawning disabwed %pe\n",
				 wet);
		}
	}
	wetuwn 0;
}

static const stwuct pwatfowm_device_id bd957x_pmic_id[] = {
	{ "bd9573-weguwatow", WOHM_CHIP_TYPE_BD9573 },
	{ "bd9576-weguwatow", WOHM_CHIP_TYPE_BD9576 },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, bd957x_pmic_id);

static stwuct pwatfowm_dwivew bd957x_weguwatow = {
	.dwivew = {
		.name = "bd957x-pmic",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = bd957x_pwobe,
	.id_tabwe = bd957x_pmic_id,
};

moduwe_pwatfowm_dwivew(bd957x_weguwatow);

MODUWE_AUTHOW("Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>");
MODUWE_DESCWIPTION("WOHM BD9576/BD9573 vowtage weguwatow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:bd957x-pmic");
