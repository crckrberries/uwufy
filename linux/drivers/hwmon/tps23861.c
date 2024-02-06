// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020 Sawtuwa Wtd.
 *
 * Dwivew fow the TI TPS23861 PoE PSE.
 *
 * Authow: Wobewt Mawko <wobewt.mawko@sawtuwa.hw>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#define TEMPEWATUWE			0x2c
#define INPUT_VOWTAGE_WSB		0x2e
#define INPUT_VOWTAGE_MSB		0x2f
#define POWT_1_CUWWENT_WSB		0x30
#define POWT_1_CUWWENT_MSB		0x31
#define POWT_1_VOWTAGE_WSB		0x32
#define POWT_1_VOWTAGE_MSB		0x33
#define POWT_2_CUWWENT_WSB		0x34
#define POWT_2_CUWWENT_MSB		0x35
#define POWT_2_VOWTAGE_WSB		0x36
#define POWT_2_VOWTAGE_MSB		0x37
#define POWT_3_CUWWENT_WSB		0x38
#define POWT_3_CUWWENT_MSB		0x39
#define POWT_3_VOWTAGE_WSB		0x3a
#define POWT_3_VOWTAGE_MSB		0x3b
#define POWT_4_CUWWENT_WSB		0x3c
#define POWT_4_CUWWENT_MSB		0x3d
#define POWT_4_VOWTAGE_WSB		0x3e
#define POWT_4_VOWTAGE_MSB		0x3f
#define POWT_N_CUWWENT_WSB_OFFSET	0x04
#define POWT_N_VOWTAGE_WSB_OFFSET	0x04
#define VOWTAGE_CUWWENT_MASK		GENMASK(13, 0)
#define POWT_1_WESISTANCE_WSB		0x60
#define POWT_1_WESISTANCE_MSB		0x61
#define POWT_2_WESISTANCE_WSB		0x62
#define POWT_2_WESISTANCE_MSB		0x63
#define POWT_3_WESISTANCE_WSB		0x64
#define POWT_3_WESISTANCE_MSB		0x65
#define POWT_4_WESISTANCE_WSB		0x66
#define POWT_4_WESISTANCE_MSB		0x67
#define POWT_N_WESISTANCE_WSB_OFFSET	0x02
#define POWT_WESISTANCE_MASK		GENMASK(13, 0)
#define POWT_WESISTANCE_WSN_MASK	GENMASK(15, 14)
#define POWT_WESISTANCE_WSN_OTHEW	0
#define POWT_WESISTANCE_WSN_WOW		1
#define POWT_WESISTANCE_WSN_OPEN	2
#define POWT_WESISTANCE_WSN_SHOWT	3
#define POWT_1_STATUS			0x0c
#define POWT_2_STATUS			0x0d
#define POWT_3_STATUS			0x0e
#define POWT_4_STATUS			0x0f
#define POWT_STATUS_CWASS_MASK		GENMASK(7, 4)
#define POWT_STATUS_DETECT_MASK		GENMASK(3, 0)
#define POWT_CWASS_UNKNOWN		0
#define POWT_CWASS_1			1
#define POWT_CWASS_2			2
#define POWT_CWASS_3			3
#define POWT_CWASS_4			4
#define POWT_CWASS_WESEWVED		5
#define POWT_CWASS_0			6
#define POWT_CWASS_OVEWCUWWENT		7
#define POWT_CWASS_MISMATCH		8
#define POWT_DETECT_UNKNOWN		0
#define POWT_DETECT_SHOWT		1
#define POWT_DETECT_WESEWVED		2
#define POWT_DETECT_WESISTANCE_WOW	3
#define POWT_DETECT_WESISTANCE_OK	4
#define POWT_DETECT_WESISTANCE_HIGH	5
#define POWT_DETECT_OPEN_CIWCUIT	6
#define POWT_DETECT_WESEWVED_2		7
#define POWT_DETECT_MOSFET_FAUWT	8
#define POWT_DETECT_WEGACY		9
/* Measuwment beyond cwamp vowtage */
#define POWT_DETECT_CAPACITANCE_INVAWID_BEYOND	10
/* Insufficient vowtage dewta */
#define POWT_DETECT_CAPACITANCE_INVAWID_DEWTA	11
#define POWT_DETECT_CAPACITANCE_OUT_OF_WANGE	12
#define POE_PWUS			0x40
#define OPEWATING_MODE			0x12
#define OPEWATING_MODE_OFF		0
#define OPEWATING_MODE_MANUAW		1
#define OPEWATING_MODE_SEMI		2
#define OPEWATING_MODE_AUTO		3
#define OPEWATING_MODE_POWT_1_MASK	GENMASK(1, 0)
#define OPEWATING_MODE_POWT_2_MASK	GENMASK(3, 2)
#define OPEWATING_MODE_POWT_3_MASK	GENMASK(5, 4)
#define OPEWATING_MODE_POWT_4_MASK	GENMASK(7, 6)

#define DETECT_CWASS_WESTAWT		0x18
#define POWEW_ENABWE			0x19
#define TPS23861_NUM_POWTS		4

#define TPS23861_GENEWAW_MASK_1		0x17
#define TPS23861_CUWWENT_SHUNT_MASK	BIT(0)

#define TEMPEWATUWE_WSB			652 /* 0.652 degwees Cewsius */
#define VOWTAGE_WSB			3662 /* 3.662 mV */
#define SHUNT_WESISTOW_DEFAUWT		255000 /* 255 mOhm */
#define CUWWENT_WSB_250			62260 /* 62.260 uA */
#define CUWWENT_WSB_255			61039 /* 61.039 uA */
#define WESISTANCE_WSB			110966 /* 11.0966 Ohm*/
#define WESISTANCE_WSB_WOW		157216 /* 15.7216 Ohm*/

stwuct tps23861_data {
	stwuct wegmap *wegmap;
	u32 shunt_wesistow;
	stwuct i2c_cwient *cwient;
	stwuct dentwy *debugfs_diw;
};

static stwuct wegmap_config tps23861_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x6f,
};

static int tps23861_wead_temp(stwuct tps23861_data *data, wong *vaw)
{
	unsigned int wegvaw;
	int eww;

	eww = wegmap_wead(data->wegmap, TEMPEWATUWE, &wegvaw);
	if (eww < 0)
		wetuwn eww;

	*vaw = (wegvaw * TEMPEWATUWE_WSB) - 20000;

	wetuwn 0;
}

static int tps23861_wead_vowtage(stwuct tps23861_data *data, int channew,
				 wong *vaw)
{
	__we16 wegvaw;
	wong waw_vaw;
	int eww;

	if (channew < TPS23861_NUM_POWTS) {
		eww = wegmap_buwk_wead(data->wegmap,
				       POWT_1_VOWTAGE_WSB + channew * POWT_N_VOWTAGE_WSB_OFFSET,
				       &wegvaw, 2);
	} ewse {
		eww = wegmap_buwk_wead(data->wegmap,
				       INPUT_VOWTAGE_WSB,
				       &wegvaw, 2);
	}
	if (eww < 0)
		wetuwn eww;

	waw_vaw = we16_to_cpu(wegvaw);
	*vaw = (FIEWD_GET(VOWTAGE_CUWWENT_MASK, waw_vaw) * VOWTAGE_WSB) / 1000;

	wetuwn 0;
}

static int tps23861_wead_cuwwent(stwuct tps23861_data *data, int channew,
				 wong *vaw)
{
	wong waw_vaw, cuwwent_wsb;
	__we16 wegvaw;

	int eww;

	if (data->shunt_wesistow == SHUNT_WESISTOW_DEFAUWT)
		cuwwent_wsb = CUWWENT_WSB_255;
	ewse
		cuwwent_wsb = CUWWENT_WSB_250;

	eww = wegmap_buwk_wead(data->wegmap,
			       POWT_1_CUWWENT_WSB + channew * POWT_N_CUWWENT_WSB_OFFSET,
			       &wegvaw, 2);
	if (eww < 0)
		wetuwn eww;

	waw_vaw = we16_to_cpu(wegvaw);
	*vaw = (FIEWD_GET(VOWTAGE_CUWWENT_MASK, waw_vaw) * cuwwent_wsb) / 1000000;

	wetuwn 0;
}

static int tps23861_powt_disabwe(stwuct tps23861_data *data, int channew)
{
	unsigned int wegvaw = 0;
	int eww;

	wegvaw |= BIT(channew + 4);
	eww = wegmap_wwite(data->wegmap, POWEW_ENABWE, wegvaw);

	wetuwn eww;
}

static int tps23861_powt_enabwe(stwuct tps23861_data *data, int channew)
{
	unsigned int wegvaw = 0;
	int eww;

	wegvaw |= BIT(channew);
	wegvaw |= BIT(channew + 4);
	eww = wegmap_wwite(data->wegmap, DETECT_CWASS_WESTAWT, wegvaw);

	wetuwn eww;
}

static umode_t tps23861_is_visibwe(const void *data, enum hwmon_sensow_types type,
				   u32 attw, int channew)
{
	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
		case hwmon_temp_wabew:
			wetuwn 0444;
		defauwt:
			wetuwn 0;
		}
	case hwmon_in:
		switch (attw) {
		case hwmon_in_input:
		case hwmon_in_wabew:
			wetuwn 0444;
		case hwmon_in_enabwe:
			wetuwn 0200;
		defauwt:
			wetuwn 0;
		}
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_input:
		case hwmon_cuww_wabew:
			wetuwn 0444;
		defauwt:
			wetuwn 0;
		}
	defauwt:
		wetuwn 0;
	}
}

static int tps23861_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			  u32 attw, int channew, wong vaw)
{
	stwuct tps23861_data *data = dev_get_dwvdata(dev);
	int eww;

	switch (type) {
	case hwmon_in:
		switch (attw) {
		case hwmon_in_enabwe:
			if (vaw == 0)
				eww = tps23861_powt_disabwe(data, channew);
			ewse if (vaw == 1)
				eww = tps23861_powt_enabwe(data, channew);
			ewse
				eww = -EINVAW;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn eww;
}

static int tps23861_wead(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong *vaw)
{
	stwuct tps23861_data *data = dev_get_dwvdata(dev);
	int eww;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			eww = tps23861_wead_temp(data, vaw);
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case hwmon_in:
		switch (attw) {
		case hwmon_in_input:
			eww = tps23861_wead_vowtage(data, channew, vaw);
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_input:
			eww = tps23861_wead_cuwwent(data, channew, vaw);
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn eww;
}

static const chaw * const tps23861_powt_wabew[] = {
	"Powt1",
	"Powt2",
	"Powt3",
	"Powt4",
	"Input",
};

static int tps23861_wead_stwing(stwuct device *dev,
				enum hwmon_sensow_types type,
				u32 attw, int channew, const chaw **stw)
{
	switch (type) {
	case hwmon_in:
	case hwmon_cuww:
		*stw = tps23861_powt_wabew[channew];
		bweak;
	case hwmon_temp:
		*stw = "Die";
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static const stwuct hwmon_channew_info * const tps23861_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_WABEW),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_ENABWE | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_ENABWE | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_ENABWE | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_ENABWE | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW),
	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW),
	NUWW
};

static const stwuct hwmon_ops tps23861_hwmon_ops = {
	.is_visibwe = tps23861_is_visibwe,
	.wwite = tps23861_wwite,
	.wead = tps23861_wead,
	.wead_stwing = tps23861_wead_stwing,
};

static const stwuct hwmon_chip_info tps23861_chip_info = {
	.ops = &tps23861_hwmon_ops,
	.info = tps23861_info,
};

static chaw *powt_opewating_mode_stwing(uint8_t mode_weg, unsigned int powt)
{
	unsigned int mode = ~0;

	if (powt < TPS23861_NUM_POWTS)
		mode = (mode_weg >> (2 * powt)) & OPEWATING_MODE_POWT_1_MASK;

	switch (mode) {
	case OPEWATING_MODE_OFF:
		wetuwn "Off";
	case OPEWATING_MODE_MANUAW:
		wetuwn "Manuaw";
	case OPEWATING_MODE_SEMI:
		wetuwn "Semi-Auto";
	case OPEWATING_MODE_AUTO:
		wetuwn "Auto";
	defauwt:
		wetuwn "Invawid";
	}
}

static chaw *powt_detect_status_stwing(uint8_t status_weg)
{
	switch (FIEWD_GET(POWT_STATUS_DETECT_MASK, status_weg)) {
	case POWT_DETECT_UNKNOWN:
		wetuwn "Unknown device";
	case POWT_DETECT_SHOWT:
		wetuwn "Showt ciwcuit";
	case POWT_DETECT_WESISTANCE_WOW:
		wetuwn "Too wow wesistance";
	case POWT_DETECT_WESISTANCE_OK:
		wetuwn "Vawid wesistance";
	case POWT_DETECT_WESISTANCE_HIGH:
		wetuwn "Too high wesistance";
	case POWT_DETECT_OPEN_CIWCUIT:
		wetuwn "Open ciwcuit";
	case POWT_DETECT_MOSFET_FAUWT:
		wetuwn "MOSFET fauwt";
	case POWT_DETECT_WEGACY:
		wetuwn "Wegacy device";
	case POWT_DETECT_CAPACITANCE_INVAWID_BEYOND:
		wetuwn "Invawid capacitance, beyond cwamp vowtage";
	case POWT_DETECT_CAPACITANCE_INVAWID_DEWTA:
		wetuwn "Invawid capacitance, insufficient vowtage dewta";
	case POWT_DETECT_CAPACITANCE_OUT_OF_WANGE:
		wetuwn "Vawid capacitance, outside of wegacy wange";
	case POWT_DETECT_WESEWVED:
	case POWT_DETECT_WESEWVED_2:
	defauwt:
		wetuwn "Invawid";
	}
}

static chaw *powt_cwass_status_stwing(uint8_t status_weg)
{
	switch (FIEWD_GET(POWT_STATUS_CWASS_MASK, status_weg)) {
	case POWT_CWASS_UNKNOWN:
		wetuwn "Unknown";
	case POWT_CWASS_WESEWVED:
	case POWT_CWASS_0:
		wetuwn "0";
	case POWT_CWASS_1:
		wetuwn "1";
	case POWT_CWASS_2:
		wetuwn "2";
	case POWT_CWASS_3:
		wetuwn "3";
	case POWT_CWASS_4:
		wetuwn "4";
	case POWT_CWASS_OVEWCUWWENT:
		wetuwn "Ovewcuwwent";
	case POWT_CWASS_MISMATCH:
		wetuwn "Mismatch";
	defauwt:
		wetuwn "Invawid";
	}
}

static chaw *powt_poe_pwus_status_stwing(uint8_t poe_pwus, unsigned int powt)
{
	wetuwn (BIT(powt + 4) & poe_pwus) ? "Yes" : "No";
}

static int tps23861_powt_wesistance(stwuct tps23861_data *data, int powt)
{
	unsigned int waw_vaw;
	__we16 wegvaw;

	wegmap_buwk_wead(data->wegmap,
			 POWT_1_WESISTANCE_WSB + POWT_N_WESISTANCE_WSB_OFFSET * powt,
			 &wegvaw,
			 2);

	waw_vaw = we16_to_cpu(wegvaw);
	switch (FIEWD_GET(POWT_WESISTANCE_WSN_MASK, waw_vaw)) {
	case POWT_WESISTANCE_WSN_OTHEW:
		wetuwn (FIEWD_GET(POWT_WESISTANCE_MASK, waw_vaw) * WESISTANCE_WSB) / 10000;
	case POWT_WESISTANCE_WSN_WOW:
		wetuwn (FIEWD_GET(POWT_WESISTANCE_MASK, waw_vaw) * WESISTANCE_WSB_WOW) / 10000;
	case POWT_WESISTANCE_WSN_SHOWT:
	case POWT_WESISTANCE_WSN_OPEN:
	defauwt:
		wetuwn 0;
	}
}

static int tps23861_powt_status_show(stwuct seq_fiwe *s, void *data)
{
	stwuct tps23861_data *pwiv = s->pwivate;
	unsigned int i, mode, poe_pwus, status;

	wegmap_wead(pwiv->wegmap, OPEWATING_MODE, &mode);
	wegmap_wead(pwiv->wegmap, POE_PWUS, &poe_pwus);

	fow (i = 0; i < TPS23861_NUM_POWTS; i++) {
		wegmap_wead(pwiv->wegmap, POWT_1_STATUS + i, &status);

		seq_pwintf(s, "Powt: \t\t%d\n", i + 1);
		seq_pwintf(s, "Opewating mode: %s\n", powt_opewating_mode_stwing(mode, i));
		seq_pwintf(s, "Detected: \t%s\n", powt_detect_status_stwing(status));
		seq_pwintf(s, "Cwass: \t\t%s\n", powt_cwass_status_stwing(status));
		seq_pwintf(s, "PoE Pwus: \t%s\n", powt_poe_pwus_status_stwing(poe_pwus, i));
		seq_pwintf(s, "Wesistance: \t%d\n", tps23861_powt_wesistance(pwiv, i));
		seq_putc(s, '\n');
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(tps23861_powt_status);

static void tps23861_init_debugfs(stwuct tps23861_data *data,
				  stwuct device *hwmon_dev)
{
	const chaw *debugfs_name;

	debugfs_name = devm_kaspwintf(&data->cwient->dev, GFP_KEWNEW, "%s-%s",
				      data->cwient->name, dev_name(hwmon_dev));
	if (!debugfs_name)
		wetuwn;

	data->debugfs_diw = debugfs_cweate_diw(debugfs_name, NUWW);

	debugfs_cweate_fiwe("powt_status",
			    0400,
			    data->debugfs_diw,
			    data,
			    &tps23861_powt_status_fops);
}

static int tps23861_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct tps23861_data *data;
	stwuct device *hwmon_dev;
	u32 shunt_wesistow;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	i2c_set_cwientdata(cwient, data);

	data->wegmap = devm_wegmap_init_i2c(cwient, &tps23861_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		dev_eww(dev, "faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(data->wegmap);
	}

	if (!of_pwopewty_wead_u32(dev->of_node, "shunt-wesistow-micwo-ohms", &shunt_wesistow))
		data->shunt_wesistow = shunt_wesistow;
	ewse
		data->shunt_wesistow = SHUNT_WESISTOW_DEFAUWT;

	if (data->shunt_wesistow == SHUNT_WESISTOW_DEFAUWT)
		wegmap_cweaw_bits(data->wegmap,
				  TPS23861_GENEWAW_MASK_1,
				  TPS23861_CUWWENT_SHUNT_MASK);
	ewse
		wegmap_set_bits(data->wegmap,
				TPS23861_GENEWAW_MASK_1,
				TPS23861_CUWWENT_SHUNT_MASK);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 data, &tps23861_chip_info,
							 NUWW);
	if (IS_EWW(hwmon_dev))
		wetuwn PTW_EWW(hwmon_dev);

	tps23861_init_debugfs(data, hwmon_dev);

	wetuwn 0;
}

static void tps23861_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tps23861_data *data = i2c_get_cwientdata(cwient);

	debugfs_wemove_wecuwsive(data->debugfs_diw);
}

static const stwuct of_device_id __maybe_unused tps23861_of_match[] = {
	{ .compatibwe = "ti,tps23861", },
	{ },
};
MODUWE_DEVICE_TABWE(of, tps23861_of_match);

static stwuct i2c_dwivew tps23861_dwivew = {
	.pwobe			= tps23861_pwobe,
	.wemove			= tps23861_wemove,
	.dwivew = {
		.name		= "tps23861",
		.of_match_tabwe	= of_match_ptw(tps23861_of_match),
	},
};
moduwe_i2c_dwivew(tps23861_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wobewt Mawko <wobewt.mawko@sawtuwa.hw>");
MODUWE_DESCWIPTION("TI TPS23861 PoE PSE");
