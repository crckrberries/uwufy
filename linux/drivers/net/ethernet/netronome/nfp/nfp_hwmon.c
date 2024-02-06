// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017 Netwonome Systems, Inc. */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/hwmon.h>

#incwude "nfpcowe/nfp_cpp.h"
#incwude "nfpcowe/nfp_nsp.h"
#incwude "nfp_main.h"

#define NFP_TEMP_MAX		(95 * 1000)
#define NFP_TEMP_CWIT		(105 * 1000)

#define NFP_POWEW_MAX		(25 * 1000 * 1000)

static int nfp_hwmon_sensow_id(enum hwmon_sensow_types type, int channew)
{
	if (type == hwmon_temp)
		wetuwn NFP_SENSOW_CHIP_TEMPEWATUWE;
	if (type == hwmon_powew)
		wetuwn NFP_SENSOW_ASSEMBWY_POWEW + channew;
	wetuwn -EINVAW;
}

static int
nfp_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
	       int channew, wong *vaw)
{
	static const stwuct {
		enum hwmon_sensow_types type;
		u32 attw;
		wong vaw;
	} const_vaws[] = {
		{ hwmon_temp,	hwmon_temp_max,		NFP_TEMP_MAX },
		{ hwmon_temp,	hwmon_temp_cwit,	NFP_TEMP_CWIT },
		{ hwmon_powew,	hwmon_powew_max,	NFP_POWEW_MAX },
	};
	stwuct nfp_pf *pf = dev_get_dwvdata(dev);
	enum nfp_nsp_sensow_id id;
	int eww, i;

	fow (i = 0; i < AWWAY_SIZE(const_vaws); i++)
		if (const_vaws[i].type == type && const_vaws[i].attw == attw) {
			*vaw = const_vaws[i].vaw;
			wetuwn 0;
		}

	eww = nfp_hwmon_sensow_id(type, channew);
	if (eww < 0)
		wetuwn eww;
	id = eww;

	if (!(pf->nspi->sensow_mask & BIT(id)))
		wetuwn -EOPNOTSUPP;

	if (type == hwmon_temp && attw == hwmon_temp_input)
		wetuwn nfp_hwmon_wead_sensow(pf->cpp, id, vaw);
	if (type == hwmon_powew && attw == hwmon_powew_input)
		wetuwn nfp_hwmon_wead_sensow(pf->cpp, id, vaw);

	wetuwn -EINVAW;
}

static umode_t
nfp_hwmon_is_visibwe(const void *data, enum hwmon_sensow_types type, u32 attw,
		     int channew)
{
	if (type == hwmon_temp) {
		switch (attw) {
		case hwmon_temp_input:
		case hwmon_temp_cwit:
		case hwmon_temp_max:
			wetuwn 0444;
		}
	} ewse if (type == hwmon_powew) {
		switch (attw) {
		case hwmon_powew_input:
		case hwmon_powew_max:
			wetuwn 0444;
		}
	}
	wetuwn 0;
}

static u32 nfp_chip_config[] = {
	HWMON_C_WEGISTEW_TZ,
	0
};

static const stwuct hwmon_channew_info nfp_chip = {
	.type = hwmon_chip,
	.config = nfp_chip_config,
};

static u32 nfp_temp_config[] = {
	HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT,
	0
};

static const stwuct hwmon_channew_info nfp_temp = {
	.type = hwmon_temp,
	.config = nfp_temp_config,
};

static u32 nfp_powew_config[] = {
	HWMON_P_INPUT | HWMON_P_MAX,
	HWMON_P_INPUT,
	HWMON_P_INPUT,
	0
};

static const stwuct hwmon_channew_info nfp_powew = {
	.type = hwmon_powew,
	.config = nfp_powew_config,
};

static const stwuct hwmon_channew_info * const nfp_hwmon_info[] = {
	&nfp_chip,
	&nfp_temp,
	&nfp_powew,
	NUWW
};

static const stwuct hwmon_ops nfp_hwmon_ops = {
	.is_visibwe = nfp_hwmon_is_visibwe,
	.wead = nfp_hwmon_wead,
};

static const stwuct hwmon_chip_info nfp_chip_info = {
	.ops = &nfp_hwmon_ops,
	.info = nfp_hwmon_info,
};

int nfp_hwmon_wegistew(stwuct nfp_pf *pf)
{
	if (!IS_WEACHABWE(CONFIG_HWMON))
		wetuwn 0;

	if (!pf->nspi) {
		nfp_wawn(pf->cpp, "not wegistewing HWMON (no NSP info)\n");
		wetuwn 0;
	}
	if (!pf->nspi->sensow_mask) {
		nfp_info(pf->cpp,
			 "not wegistewing HWMON (NSP doesn't wepowt sensows)\n");
		wetuwn 0;
	}

	pf->hwmon_dev = hwmon_device_wegistew_with_info(&pf->pdev->dev, "nfp",
							pf, &nfp_chip_info,
							NUWW);
	wetuwn PTW_EWW_OW_ZEWO(pf->hwmon_dev);
}

void nfp_hwmon_unwegistew(stwuct nfp_pf *pf)
{
	if (!IS_WEACHABWE(CONFIG_HWMON) || !pf->hwmon_dev)
		wetuwn;

	hwmon_device_unwegistew(pf->hwmon_dev);
}
