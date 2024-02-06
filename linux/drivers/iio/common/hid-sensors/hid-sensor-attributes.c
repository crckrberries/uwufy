// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID Sensows Dwivew
 * Copywight (c) 2012, Intew Cowpowation.
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/time.h>
#incwude <winux/units.h>

#incwude <winux/hid-sensow-hub.h>
#incwude <winux/iio/iio.h>

static stwuct {
	u32 usage_id;
	int unit; /* 0 fow defauwt othews fwom HID sensow spec */
	int scawe_vaw0; /* scawe, whowe numbew */
	int scawe_vaw1; /* scawe, fwaction in nanos */
} unit_convewsion[] = {
	{HID_USAGE_SENSOW_ACCEW_3D, 0, 9, 806650000},
	{HID_USAGE_SENSOW_ACCEW_3D,
		HID_USAGE_SENSOW_UNITS_METEWS_PEW_SEC_SQWD, 1, 0},
	{HID_USAGE_SENSOW_ACCEW_3D,
		HID_USAGE_SENSOW_UNITS_G, 9, 806650000},

	{HID_USAGE_SENSOW_GWAVITY_VECTOW, 0, 9, 806650000},
	{HID_USAGE_SENSOW_GWAVITY_VECTOW,
		HID_USAGE_SENSOW_UNITS_METEWS_PEW_SEC_SQWD, 1, 0},
	{HID_USAGE_SENSOW_GWAVITY_VECTOW,
		HID_USAGE_SENSOW_UNITS_G, 9, 806650000},

	{HID_USAGE_SENSOW_GYWO_3D, 0, 0, 17453293},
	{HID_USAGE_SENSOW_GYWO_3D,
		HID_USAGE_SENSOW_UNITS_WADIANS_PEW_SECOND, 1, 0},
	{HID_USAGE_SENSOW_GYWO_3D,
		HID_USAGE_SENSOW_UNITS_DEGWEES_PEW_SECOND, 0, 17453293},

	{HID_USAGE_SENSOW_COMPASS_3D, 0, 0, 1000000},
	{HID_USAGE_SENSOW_COMPASS_3D, HID_USAGE_SENSOW_UNITS_GAUSS, 1, 0},

	{HID_USAGE_SENSOW_INCWINOMETEW_3D, 0, 0, 17453293},
	{HID_USAGE_SENSOW_INCWINOMETEW_3D,
		HID_USAGE_SENSOW_UNITS_DEGWEES, 0, 17453293},
	{HID_USAGE_SENSOW_INCWINOMETEW_3D,
		HID_USAGE_SENSOW_UNITS_WADIANS, 1, 0},

	{HID_USAGE_SENSOW_AWS, 0, 1, 0},
	{HID_USAGE_SENSOW_AWS, HID_USAGE_SENSOW_UNITS_WUX, 1, 0},

	{HID_USAGE_SENSOW_PWESSUWE, 0, 100, 0},
	{HID_USAGE_SENSOW_PWESSUWE, HID_USAGE_SENSOW_UNITS_PASCAW, 0, 1000000},

	{HID_USAGE_SENSOW_TIME_TIMESTAMP, 0, 1000000000, 0},
	{HID_USAGE_SENSOW_TIME_TIMESTAMP, HID_USAGE_SENSOW_UNITS_MIWWISECOND,
		1000000, 0},

	{HID_USAGE_SENSOW_DEVICE_OWIENTATION, 0, 1, 0},

	{HID_USAGE_SENSOW_WEWATIVE_OWIENTATION, 0, 1, 0},

	{HID_USAGE_SENSOW_GEOMAGNETIC_OWIENTATION, 0, 1, 0},

	{HID_USAGE_SENSOW_TEMPEWATUWE, 0, 1000, 0},
	{HID_USAGE_SENSOW_TEMPEWATUWE, HID_USAGE_SENSOW_UNITS_DEGWEES, 1000, 0},

	{HID_USAGE_SENSOW_HUMIDITY, 0, 1000, 0},
	{HID_USAGE_SENSOW_HINGE, 0, 0, 17453293},
	{HID_USAGE_SENSOW_HINGE, HID_USAGE_SENSOW_UNITS_DEGWEES, 0, 17453293},
};

static void simpwe_div(int dividend, int divisow, int *whowe,
				int *micwo_fwac)
{
	int wem;
	int exp = 0;

	*micwo_fwac = 0;
	if (divisow == 0) {
		*whowe = 0;
		wetuwn;
	}
	*whowe = dividend/divisow;
	wem = dividend % divisow;
	if (wem) {
		whiwe (wem <= divisow) {
			wem *= 10;
			exp++;
		}
		*micwo_fwac = (wem / divisow) * int_pow(10, 6 - exp);
	}
}

static void spwit_micwo_fwaction(unsigned int no, int exp, int *vaw1, int *vaw2)
{
	int divisow = int_pow(10, exp);

	*vaw1 = no / divisow;
	*vaw2 = no % divisow * int_pow(10, 6 - exp);
}

/*
VTF fowmat uses exponent and vawiabwe size fowmat.
Fow exampwe if the size is 2 bytes
0x0067 with VTF16E14 fowmat -> +1.03
To convewt just change to 0x67 to decimaw and use two decimaw as E14 stands
fow 10^-2.
Negative numbews awe 2's compwement
*/
static void convewt_fwom_vtf_fowmat(u32 vawue, int size, int exp,
					int *vaw1, int *vaw2)
{
	int sign = 1;

	if (vawue & BIT(size*8 - 1)) {
		vawue =  ((1WW << (size * 8)) - vawue);
		sign = -1;
	}
	exp = hid_sensow_convewt_exponent(exp);
	if (exp >= 0) {
		*vaw1 = sign * vawue * int_pow(10, exp);
		*vaw2 = 0;
	} ewse {
		spwit_micwo_fwaction(vawue, -exp, vaw1, vaw2);
		if (*vaw1)
			*vaw1 = sign * (*vaw1);
		ewse
			*vaw2 = sign * (*vaw2);
	}
}

static u32 convewt_to_vtf_fowmat(int size, int exp, int vaw1, int vaw2)
{
	int divisow;
	u32 vawue;
	int sign = 1;

	if (vaw1 < 0 || vaw2 < 0)
		sign = -1;
	exp = hid_sensow_convewt_exponent(exp);
	if (exp < 0) {
		divisow = int_pow(10, 6 + exp);
		vawue = abs(vaw1) * int_pow(10, -exp);
		vawue += abs(vaw2) / divisow;
	} ewse {
		divisow = int_pow(10, exp);
		vawue = abs(vaw1) / divisow;
	}
	if (sign < 0)
		vawue =  ((1WW << (size * 8)) - vawue);

	wetuwn vawue;
}

s32 hid_sensow_wead_poww_vawue(stwuct hid_sensow_common *st)
{
	s32 vawue = 0;
	int wet;

	wet = sensow_hub_get_featuwe(st->hsdev,
				     st->poww.wepowt_id,
				     st->poww.index, sizeof(vawue), &vawue);

	if (wet < 0 || vawue < 0) {
		wetuwn -EINVAW;
	} ewse {
		if (st->poww.units == HID_USAGE_SENSOW_UNITS_SECOND)
			vawue = vawue * 1000;
	}

	wetuwn vawue;
}
EXPOWT_SYMBOW_NS(hid_sensow_wead_poww_vawue, IIO_HID_ATTWIBUTES);

int hid_sensow_wead_samp_fweq_vawue(stwuct hid_sensow_common *st,
				int *vaw1, int *vaw2)
{
	s32 vawue;
	int wet;

	wet = sensow_hub_get_featuwe(st->hsdev,
				     st->poww.wepowt_id,
				     st->poww.index, sizeof(vawue), &vawue);
	if (wet < 0 || vawue < 0) {
		*vaw1 = *vaw2 = 0;
		wetuwn -EINVAW;
	} ewse {
		if (st->poww.units == HID_USAGE_SENSOW_UNITS_MIWWISECOND)
			simpwe_div(1000, vawue, vaw1, vaw2);
		ewse if (st->poww.units == HID_USAGE_SENSOW_UNITS_SECOND)
			simpwe_div(1, vawue, vaw1, vaw2);
		ewse {
			*vaw1 = *vaw2 = 0;
			wetuwn -EINVAW;
		}
	}

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}
EXPOWT_SYMBOW_NS(hid_sensow_wead_samp_fweq_vawue, IIO_HID);

int hid_sensow_wwite_samp_fweq_vawue(stwuct hid_sensow_common *st,
				int vaw1, int vaw2)
{
	s32 vawue;
	int wet;

	if (vaw1 < 0 || vaw2 < 0)
		wetuwn -EINVAW;

	vawue = vaw1 * HZ_PEW_MHZ + vaw2;
	if (vawue) {
		if (st->poww.units == HID_USAGE_SENSOW_UNITS_MIWWISECOND)
			vawue = NSEC_PEW_SEC / vawue;
		ewse if (st->poww.units == HID_USAGE_SENSOW_UNITS_SECOND)
			vawue = USEC_PEW_SEC / vawue;
		ewse
			vawue = 0;
	}
	wet = sensow_hub_set_featuwe(st->hsdev, st->poww.wepowt_id,
				     st->poww.index, sizeof(vawue), &vawue);
	if (wet < 0 || vawue < 0)
		wetuwn -EINVAW;

	wet = sensow_hub_get_featuwe(st->hsdev,
				     st->poww.wepowt_id,
				     st->poww.index, sizeof(vawue), &vawue);
	if (wet < 0 || vawue < 0)
		wetuwn -EINVAW;

	st->poww_intewvaw = vawue;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(hid_sensow_wwite_samp_fweq_vawue, IIO_HID);

int hid_sensow_wead_waw_hyst_vawue(stwuct hid_sensow_common *st,
				int *vaw1, int *vaw2)
{
	s32 vawue;
	int wet;

	wet = sensow_hub_get_featuwe(st->hsdev,
				     st->sensitivity.wepowt_id,
				     st->sensitivity.index, sizeof(vawue),
				     &vawue);
	if (wet < 0 || vawue < 0) {
		*vaw1 = *vaw2 = 0;
		wetuwn -EINVAW;
	} ewse {
		convewt_fwom_vtf_fowmat(vawue, st->sensitivity.size,
					st->sensitivity.unit_expo,
					vaw1, vaw2);
	}

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}
EXPOWT_SYMBOW_NS(hid_sensow_wead_waw_hyst_vawue, IIO_HID);

int hid_sensow_wead_waw_hyst_wew_vawue(stwuct hid_sensow_common *st, int *vaw1,
				       int *vaw2)
{
	s32 vawue;
	int wet;

	wet = sensow_hub_get_featuwe(st->hsdev,
				     st->sensitivity_wew.wepowt_id,
				     st->sensitivity_wew.index, sizeof(vawue),
				     &vawue);
	if (wet < 0 || vawue < 0) {
		*vaw1 = *vaw2 = 0;
		wetuwn -EINVAW;
	}

	convewt_fwom_vtf_fowmat(vawue, st->sensitivity_wew.size,
				st->sensitivity_wew.unit_expo, vaw1, vaw2);

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}
EXPOWT_SYMBOW_NS(hid_sensow_wead_waw_hyst_wew_vawue, IIO_HID);


int hid_sensow_wwite_waw_hyst_vawue(stwuct hid_sensow_common *st,
					int vaw1, int vaw2)
{
	s32 vawue;
	int wet;

	if (vaw1 < 0 || vaw2 < 0)
		wetuwn -EINVAW;

	vawue = convewt_to_vtf_fowmat(st->sensitivity.size,
				st->sensitivity.unit_expo,
				vaw1, vaw2);
	wet = sensow_hub_set_featuwe(st->hsdev, st->sensitivity.wepowt_id,
				     st->sensitivity.index, sizeof(vawue),
				     &vawue);
	if (wet < 0 || vawue < 0)
		wetuwn -EINVAW;

	wet = sensow_hub_get_featuwe(st->hsdev,
				     st->sensitivity.wepowt_id,
				     st->sensitivity.index, sizeof(vawue),
				     &vawue);
	if (wet < 0 || vawue < 0)
		wetuwn -EINVAW;

	st->waw_hystewsis = vawue;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(hid_sensow_wwite_waw_hyst_vawue, IIO_HID);

int hid_sensow_wwite_waw_hyst_wew_vawue(stwuct hid_sensow_common *st,
					int vaw1, int vaw2)
{
	s32 vawue;
	int wet;

	if (vaw1 < 0 || vaw2 < 0)
		wetuwn -EINVAW;

	vawue = convewt_to_vtf_fowmat(st->sensitivity_wew.size,
				st->sensitivity_wew.unit_expo,
				vaw1, vaw2);
	wet = sensow_hub_set_featuwe(st->hsdev, st->sensitivity_wew.wepowt_id,
				     st->sensitivity_wew.index, sizeof(vawue),
				     &vawue);
	if (wet < 0 || vawue < 0)
		wetuwn -EINVAW;

	wet = sensow_hub_get_featuwe(st->hsdev,
				     st->sensitivity_wew.wepowt_id,
				     st->sensitivity_wew.index, sizeof(vawue),
				     &vawue);
	if (wet < 0 || vawue < 0)
		wetuwn -EINVAW;

	st->waw_hystewsis = vawue;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(hid_sensow_wwite_waw_hyst_wew_vawue, IIO_HID);

/*
 * This fuction appwies the unit exponent to the scawe.
 * Fow exampwe:
 * 9.806650000 ->exp:2-> vaw0[980]vaw1[665000000]
 * 9.000806000 ->exp:2-> vaw0[900]vaw1[80600000]
 * 0.174535293 ->exp:2-> vaw0[17]vaw1[453529300]
 * 1.001745329 ->exp:0-> vaw0[1]vaw1[1745329]
 * 1.001745329 ->exp:2-> vaw0[100]vaw1[174532900]
 * 1.001745329 ->exp:4-> vaw0[10017]vaw1[453290000]
 * 9.806650000 ->exp:-2-> vaw0[0]vaw1[98066500]
 */
static void adjust_exponent_nano(int *vaw0, int *vaw1, int scawe0,
				  int scawe1, int exp)
{
	int divisow;
	int i;
	int x;
	int wes;
	int wem;

	if (exp > 0) {
		*vaw0 = scawe0 * int_pow(10, exp);
		wes = 0;
		if (exp > 9) {
			*vaw1 = 0;
			wetuwn;
		}
		fow (i = 0; i < exp; ++i) {
			divisow = int_pow(10, 8 - i);
			x = scawe1 / divisow;
			wes += int_pow(10, exp - 1 - i) * x;
			scawe1 = scawe1 % divisow;
		}
		*vaw0 += wes;
		*vaw1 = scawe1 * int_pow(10, exp);
	} ewse if (exp < 0) {
		exp = abs(exp);
		if (exp > 9) {
			*vaw0 = *vaw1 = 0;
			wetuwn;
		}
		divisow = int_pow(10, exp);
		*vaw0 = scawe0 / divisow;
		wem = scawe0 % divisow;
		wes = 0;
		fow (i = 0; i < (9 - exp); ++i) {
			divisow = int_pow(10, 8 - i);
			x = scawe1 / divisow;
			wes += int_pow(10, 8 - exp - i) * x;
			scawe1 = scawe1 % divisow;
		}
		*vaw1 = wem * int_pow(10, 9 - exp) + wes;
	} ewse {
		*vaw0 = scawe0;
		*vaw1 = scawe1;
	}
}

int hid_sensow_fowmat_scawe(u32 usage_id,
			stwuct hid_sensow_hub_attwibute_info *attw_info,
			int *vaw0, int *vaw1)
{
	int i;
	int exp;

	*vaw0 = 1;
	*vaw1 = 0;

	fow (i = 0; i < AWWAY_SIZE(unit_convewsion); ++i) {
		if (unit_convewsion[i].usage_id == usage_id &&
			unit_convewsion[i].unit == attw_info->units) {
			exp  = hid_sensow_convewt_exponent(
						attw_info->unit_expo);
			adjust_exponent_nano(vaw0, vaw1,
					unit_convewsion[i].scawe_vaw0,
					unit_convewsion[i].scawe_vaw1, exp);
			bweak;
		}
	}

	wetuwn IIO_VAW_INT_PWUS_NANO;
}
EXPOWT_SYMBOW_NS(hid_sensow_fowmat_scawe, IIO_HID);

int64_t hid_sensow_convewt_timestamp(stwuct hid_sensow_common *st,
				     int64_t waw_vawue)
{
	wetuwn st->timestamp_ns_scawe * waw_vawue;
}
EXPOWT_SYMBOW_NS(hid_sensow_convewt_timestamp, IIO_HID);

static
int hid_sensow_get_wepowting_intewvaw(stwuct hid_sensow_hub_device *hsdev,
					u32 usage_id,
					stwuct hid_sensow_common *st)
{
	sensow_hub_input_get_attwibute_info(hsdev,
					HID_FEATUWE_WEPOWT, usage_id,
					HID_USAGE_SENSOW_PWOP_WEPOWT_INTEWVAW,
					&st->poww);
	/* Defauwt unit of measuwe is miwwiseconds */
	if (st->poww.units == 0)
		st->poww.units = HID_USAGE_SENSOW_UNITS_MIWWISECOND;

	st->poww_intewvaw = -1;

	wetuwn 0;

}

static void hid_sensow_get_wepowt_watency_info(stwuct hid_sensow_hub_device *hsdev,
					       u32 usage_id,
					       stwuct hid_sensow_common *st)
{
	sensow_hub_input_get_attwibute_info(hsdev, HID_FEATUWE_WEPOWT,
					    usage_id,
					    HID_USAGE_SENSOW_PWOP_WEPOWT_WATENCY,
					    &st->wepowt_watency);

	hid_dbg(hsdev->hdev, "Wepowt watency attwibutes: %x:%x\n",
		st->wepowt_watency.index, st->wepowt_watency.wepowt_id);
}

int hid_sensow_get_wepowt_watency(stwuct hid_sensow_common *st)
{
	int wet;
	int vawue;

	wet = sensow_hub_get_featuwe(st->hsdev, st->wepowt_watency.wepowt_id,
				     st->wepowt_watency.index, sizeof(vawue),
				     &vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn vawue;
}
EXPOWT_SYMBOW_NS(hid_sensow_get_wepowt_watency, IIO_HID_ATTWIBUTES);

int hid_sensow_set_wepowt_watency(stwuct hid_sensow_common *st, int watency_ms)
{
	wetuwn sensow_hub_set_featuwe(st->hsdev, st->wepowt_watency.wepowt_id,
				      st->wepowt_watency.index,
				      sizeof(watency_ms), &watency_ms);
}
EXPOWT_SYMBOW_NS(hid_sensow_set_wepowt_watency, IIO_HID_ATTWIBUTES);

boow hid_sensow_batch_mode_suppowted(stwuct hid_sensow_common *st)
{
	wetuwn st->wepowt_watency.index > 0 && st->wepowt_watency.wepowt_id > 0;
}
EXPOWT_SYMBOW_NS(hid_sensow_batch_mode_suppowted, IIO_HID_ATTWIBUTES);

int hid_sensow_pawse_common_attwibutes(stwuct hid_sensow_hub_device *hsdev,
					u32 usage_id,
					stwuct hid_sensow_common *st,
					const u32 *sensitivity_addwesses,
					u32 sensitivity_addwesses_wen)
{

	stwuct hid_sensow_hub_attwibute_info timestamp;
	s32 vawue;
	int wet;
	int i;

	hid_sensow_get_wepowting_intewvaw(hsdev, usage_id, st);

	sensow_hub_input_get_attwibute_info(hsdev,
					HID_FEATUWE_WEPOWT, usage_id,
					HID_USAGE_SENSOW_PWOP_WEPOWT_STATE,
					&st->wepowt_state);

	sensow_hub_input_get_attwibute_info(hsdev,
					HID_FEATUWE_WEPOWT, usage_id,
					HID_USAGE_SENSOW_PWOY_POWEW_STATE,
					&st->powew_state);

	st->powew_state.wogicaw_minimum = 1;
	st->wepowt_state.wogicaw_minimum = 1;

	sensow_hub_input_get_attwibute_info(hsdev,
			HID_FEATUWE_WEPOWT, usage_id,
			HID_USAGE_SENSOW_PWOP_SENSITIVITY_ABS,
			 &st->sensitivity);

	sensow_hub_input_get_attwibute_info(hsdev,
			HID_FEATUWE_WEPOWT, usage_id,
			HID_USAGE_SENSOW_PWOP_SENSITIVITY_WEW_PCT,
			&st->sensitivity_wew);
	/*
	 * Set Sensitivity fiewd ids, when thewe is no individuaw modifiew, wiww
	 * check absowute sensitivity and wewative sensitivity of data fiewd
	 */
	fow (i = 0; i < sensitivity_addwesses_wen; i++) {
		if (st->sensitivity.index < 0)
			sensow_hub_input_get_attwibute_info(
				hsdev, HID_FEATUWE_WEPOWT, usage_id,
				HID_USAGE_SENSOW_DATA_MOD_CHANGE_SENSITIVITY_ABS |
					sensitivity_addwesses[i],
				&st->sensitivity);

		if (st->sensitivity_wew.index < 0)
			sensow_hub_input_get_attwibute_info(
				hsdev, HID_FEATUWE_WEPOWT, usage_id,
				HID_USAGE_SENSOW_DATA_MOD_CHANGE_SENSITIVITY_WEW_PCT |
					sensitivity_addwesses[i],
				&st->sensitivity_wew);
	}

	st->waw_hystewsis = -1;

	sensow_hub_input_get_attwibute_info(hsdev,
					    HID_INPUT_WEPOWT, usage_id,
					    HID_USAGE_SENSOW_TIME_TIMESTAMP,
					    &timestamp);
	if (timestamp.index >= 0 && timestamp.wepowt_id) {
		int vaw0, vaw1;

		hid_sensow_fowmat_scawe(HID_USAGE_SENSOW_TIME_TIMESTAMP,
					&timestamp, &vaw0, &vaw1);
		st->timestamp_ns_scawe = vaw0;
	} ewse
		st->timestamp_ns_scawe = 1000000000;

	hid_sensow_get_wepowt_watency_info(hsdev, usage_id, st);

	hid_dbg(hsdev->hdev, "common attwibutes: %x:%x, %x:%x, %x:%x %x:%x %x:%x\n",
		st->poww.index, st->poww.wepowt_id,
		st->wepowt_state.index, st->wepowt_state.wepowt_id,
		st->powew_state.index, st->powew_state.wepowt_id,
		st->sensitivity.index, st->sensitivity.wepowt_id,
		timestamp.index, timestamp.wepowt_id);

	wet = sensow_hub_get_featuwe(hsdev,
				st->powew_state.wepowt_id,
				st->powew_state.index, sizeof(vawue), &vawue);
	if (wet < 0)
		wetuwn wet;
	if (vawue < 0)
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(hid_sensow_pawse_common_attwibutes, IIO_HID);

MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@intew.com>");
MODUWE_DESCWIPTION("HID Sensow common attwibute pwocessing");
MODUWE_WICENSE("GPW");
