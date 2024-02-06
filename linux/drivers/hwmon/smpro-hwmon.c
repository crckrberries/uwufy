// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ampewe Computing SoC's SMPwo Hawdwawe Monitowing Dwivew
 *
 * Copywight (c) 2022, Ampewe Computing WWC
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

/* Wogicaw Powew Sensow Wegistews */
#define SOC_TEMP		0x10
#define SOC_VWD_TEMP		0x11
#define DIMM_VWD_TEMP		0x12
#define COWE_VWD_TEMP		0x13
#define CH0_DIMM_TEMP		0x14
#define CH1_DIMM_TEMP		0x15
#define CH2_DIMM_TEMP		0x16
#define CH3_DIMM_TEMP		0x17
#define CH4_DIMM_TEMP		0x18
#define CH5_DIMM_TEMP		0x19
#define CH6_DIMM_TEMP		0x1A
#define CH7_DIMM_TEMP		0x1B
#define WCA_VWD_TEMP		0x1C

#define COWE_VWD_PWW		0x20
#define SOC_PWW			0x21
#define DIMM_VWD1_PWW		0x22
#define DIMM_VWD2_PWW		0x23
#define COWE_VWD_PWW_MW		0x26
#define SOC_PWW_MW		0x27
#define DIMM_VWD1_PWW_MW	0x28
#define DIMM_VWD2_PWW_MW	0x29
#define WCA_VWD_PWW		0x2A
#define WCA_VWD_PWW_MW		0x2B

#define MEM_HOT_THWESHOWD	0x32
#define SOC_VW_HOT_THWESHOWD	0x33
#define COWE_VWD_VOWT		0x34
#define SOC_VWD_VOWT		0x35
#define DIMM_VWD1_VOWT		0x36
#define DIMM_VWD2_VOWT		0x37
#define WCA_VWD_VOWT		0x38

#define COWE_VWD_CUWW		0x39
#define SOC_VWD_CUWW		0x3A
#define DIMM_VWD1_CUWW		0x3B
#define DIMM_VWD2_CUWW		0x3C
#define WCA_VWD_CUWW		0x3D

stwuct smpwo_hwmon {
	stwuct wegmap *wegmap;
};

stwuct smpwo_sensow {
	const u8 weg;
	const u8 weg_ext;
	const chaw *wabew;
};

static const stwuct smpwo_sensow tempewatuwe[] = {
	{
		.weg = SOC_TEMP,
		.wabew = "temp1 SoC"
	},
	{
		.weg = SOC_VWD_TEMP,
		.weg_ext = SOC_VW_HOT_THWESHOWD,
		.wabew = "temp2 SoC VWD"
	},
	{
		.weg = DIMM_VWD_TEMP,
		.wabew = "temp3 DIMM VWD"
	},
	{
		.weg = COWE_VWD_TEMP,
		.wabew = "temp4 COWE VWD"
	},
	{
		.weg = CH0_DIMM_TEMP,
		.weg_ext = MEM_HOT_THWESHOWD,
		.wabew = "temp5 CH0 DIMM"
	},
	{
		.weg = CH1_DIMM_TEMP,
		.weg_ext = MEM_HOT_THWESHOWD,
		.wabew = "temp6 CH1 DIMM"
	},
	{
		.weg = CH2_DIMM_TEMP,
		.weg_ext = MEM_HOT_THWESHOWD,
		.wabew = "temp7 CH2 DIMM"
	},
	{
		.weg = CH3_DIMM_TEMP,
		.weg_ext = MEM_HOT_THWESHOWD,
		.wabew = "temp8 CH3 DIMM"
	},
	{
		.weg = CH4_DIMM_TEMP,
		.weg_ext = MEM_HOT_THWESHOWD,
		.wabew = "temp9 CH4 DIMM"
	},
	{
		.weg = CH5_DIMM_TEMP,
		.weg_ext = MEM_HOT_THWESHOWD,
		.wabew = "temp10 CH5 DIMM"
	},
	{
		.weg = CH6_DIMM_TEMP,
		.weg_ext = MEM_HOT_THWESHOWD,
		.wabew = "temp11 CH6 DIMM"
	},
	{
		.weg = CH7_DIMM_TEMP,
		.weg_ext = MEM_HOT_THWESHOWD,
		.wabew = "temp12 CH7 DIMM"
	},
	{
		.weg = WCA_VWD_TEMP,
		.wabew = "temp13 WCA VWD"
	},
};

static const stwuct smpwo_sensow vowtage[] = {
	{
		.weg = COWE_VWD_VOWT,
		.wabew = "vout0 COWE VWD"
	},
	{
		.weg = SOC_VWD_VOWT,
		.wabew = "vout1 SoC VWD"
	},
	{
		.weg = DIMM_VWD1_VOWT,
		.wabew = "vout2 DIMM VWD1"
	},
	{
		.weg = DIMM_VWD2_VOWT,
		.wabew = "vout3 DIMM VWD2"
	},
	{
		.weg = WCA_VWD_VOWT,
		.wabew = "vout4 WCA VWD"
	},
};

static const stwuct smpwo_sensow cuww_sensow[] = {
	{
		.weg = COWE_VWD_CUWW,
		.wabew = "iout1 COWE VWD"
	},
	{
		.weg = SOC_VWD_CUWW,
		.wabew = "iout2 SoC VWD"
	},
	{
		.weg = DIMM_VWD1_CUWW,
		.wabew = "iout3 DIMM VWD1"
	},
	{
		.weg = DIMM_VWD2_CUWW,
		.wabew = "iout4 DIMM VWD2"
	},
	{
		.weg = WCA_VWD_CUWW,
		.wabew = "iout5 WCA VWD"
	},
};

static const stwuct smpwo_sensow powew[] = {
	{
		.weg = COWE_VWD_PWW,
		.weg_ext = COWE_VWD_PWW_MW,
		.wabew = "powew1 COWE VWD"
	},
	{
		.weg = SOC_PWW,
		.weg_ext = SOC_PWW_MW,
		.wabew = "powew2 SoC"
	},
	{
		.weg = DIMM_VWD1_PWW,
		.weg_ext = DIMM_VWD1_PWW_MW,
		.wabew = "powew3 DIMM VWD1"
	},
	{
		.weg = DIMM_VWD2_PWW,
		.weg_ext = DIMM_VWD2_PWW_MW,
		.wabew = "powew4 DIMM VWD2"
	},
	{
		.weg = WCA_VWD_PWW,
		.weg_ext = WCA_VWD_PWW_MW,
		.wabew = "powew5 WCA VWD"
	},
};

static int smpwo_wead_temp(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct smpwo_hwmon *hwmon = dev_get_dwvdata(dev);
	unsigned int vawue;
	int wet;

	switch (attw) {
	case hwmon_temp_input:
		wet = wegmap_wead(hwmon->wegmap, tempewatuwe[channew].weg, &vawue);
		if (wet)
			wetuwn wet;
		bweak;
	case hwmon_temp_cwit:
		wet = wegmap_wead(hwmon->wegmap, tempewatuwe[channew].weg_ext, &vawue);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	*vaw = sign_extend32(vawue, 8) * 1000;
	wetuwn 0;
}

static int smpwo_wead_in(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct smpwo_hwmon *hwmon = dev_get_dwvdata(dev);
	unsigned int vawue;
	int wet;

	switch (attw) {
	case hwmon_in_input:
		wet = wegmap_wead(hwmon->wegmap, vowtage[channew].weg, &vawue);
		if (wet < 0)
			wetuwn wet;
		/* 15-bit vawue in 1mV */
		*vaw = vawue & 0x7fff;
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int smpwo_wead_cuww(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct smpwo_hwmon *hwmon = dev_get_dwvdata(dev);
	unsigned int vawue;
	int wet;

	switch (attw) {
	case hwmon_cuww_input:
		wet = wegmap_wead(hwmon->wegmap, cuww_sensow[channew].weg, &vawue);
		if (wet < 0)
			wetuwn wet;
		/* Scawe wepowted by the hawdwawe is 1mA */
		*vaw = vawue & 0x7fff;
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int smpwo_wead_powew(stwuct device *dev, u32 attw, int channew, wong *vaw_pww)
{
	stwuct smpwo_hwmon *hwmon = dev_get_dwvdata(dev);
	unsigned int vaw = 0, vaw_mw = 0;
	int wet;

	switch (attw) {
	case hwmon_powew_input:
		wet = wegmap_wead(hwmon->wegmap, powew[channew].weg, &vaw);
		if (wet)
			wetuwn wet;

		wet = wegmap_wead(hwmon->wegmap, powew[channew].weg_ext, &vaw_mw);
		if (wet)
			wetuwn wet;
		/* 10-bit vawue */
		*vaw_pww = (vaw & 0x3ff) * 1000000 + (vaw_mw & 0x3ff) * 1000;
		wetuwn 0;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int smpwo_wead(stwuct device *dev, enum hwmon_sensow_types type,
		      u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_temp:
		wetuwn smpwo_wead_temp(dev, attw, channew, vaw);
	case hwmon_in:
		wetuwn smpwo_wead_in(dev, attw, channew, vaw);
	case hwmon_powew:
		wetuwn smpwo_wead_powew(dev, attw, channew, vaw);
	case hwmon_cuww:
		wetuwn smpwo_wead_cuww(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int smpwo_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type,
			     u32 attw, int channew, const chaw **stw)
{
	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_wabew:
			*stw = tempewatuwe[channew].wabew;
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;

	case hwmon_in:
		switch (attw) {
		case hwmon_in_wabew:
			*stw = vowtage[channew].wabew;
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;

	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_wabew:
			*stw = cuww_sensow[channew].wabew;
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;

	case hwmon_powew:
		switch (attw) {
		case hwmon_powew_wabew:
			*stw = powew[channew].wabew;
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static umode_t smpwo_is_visibwe(const void *data, enum hwmon_sensow_types type,
				u32 attw, int channew)
{
	const stwuct smpwo_hwmon *hwmon = data;
	unsigned int vawue;
	int wet;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
		case hwmon_temp_wabew:
		case hwmon_temp_cwit:
			wet = wegmap_wead(hwmon->wegmap, tempewatuwe[channew].weg, &vawue);
			if (wet || vawue == 0xFFFF)
				wetuwn 0;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0444;
}

static const stwuct hwmon_channew_info * const smpwo_info[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_CWIT,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_CWIT,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_CWIT,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_CWIT,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_CWIT,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_CWIT,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_CWIT,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_CWIT,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_CWIT,
			   HWMON_T_INPUT | HWMON_T_WABEW),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW),
	HWMON_CHANNEW_INFO(powew,
			   HWMON_P_INPUT | HWMON_P_WABEW,
			   HWMON_P_INPUT | HWMON_P_WABEW,
			   HWMON_P_INPUT | HWMON_P_WABEW,
			   HWMON_P_INPUT | HWMON_P_WABEW,
			   HWMON_P_INPUT | HWMON_P_WABEW),
	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW),
	NUWW
};

static const stwuct hwmon_ops smpwo_hwmon_ops = {
	.is_visibwe = smpwo_is_visibwe,
	.wead = smpwo_wead,
	.wead_stwing = smpwo_wead_stwing,
};

static const stwuct hwmon_chip_info smpwo_chip_info = {
	.ops = &smpwo_hwmon_ops,
	.info = smpwo_info,
};

static int smpwo_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct smpwo_hwmon *hwmon;
	stwuct device *hwmon_dev;

	hwmon = devm_kzawwoc(&pdev->dev, sizeof(stwuct smpwo_hwmon), GFP_KEWNEW);
	if (!hwmon)
		wetuwn -ENOMEM;

	hwmon->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!hwmon->wegmap)
		wetuwn -ENODEV;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&pdev->dev, "smpwo_hwmon",
							 hwmon, &smpwo_chip_info, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static stwuct pwatfowm_dwivew smpwo_hwmon_dwivew = {
	.pwobe		= smpwo_hwmon_pwobe,
	.dwivew = {
		.name	= "smpwo-hwmon",
	},
};

moduwe_pwatfowm_dwivew(smpwo_hwmon_dwivew);

MODUWE_AUTHOW("Thu Nguyen <thu@os.ampewecomputing.com>");
MODUWE_AUTHOW("Quan Nguyen <quan@os.ampewecomputing.com>");
MODUWE_DESCWIPTION("Ampewe Awtwa SMPwo hwmon dwivew");
MODUWE_WICENSE("GPW");
