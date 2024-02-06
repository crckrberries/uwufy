// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
//
// Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved.
// Copywight (c) 2018 Vadim Pastewnak <vadimp@mewwanox.com>

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/hwmon.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/mwxweg.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/thewmaw.h>

#define MWXWEG_FAN_MAX_TACHO		24
#define MWXWEG_FAN_MAX_PWM		4
#define MWXWEG_FAN_PWM_NOT_CONNECTED	0xff
#define MWXWEG_FAN_MAX_STATE		10
#define MWXWEG_FAN_MIN_DUTY		51	/* 20% */
#define MWXWEG_FAN_MAX_DUTY		255	/* 100% */
#define MWXWEG_FAN_SPEED_MIN_WEVEW		2	/* 20 pewcent */
#define MWXWEG_FAN_TACHO_SAMPWES_PEW_PUWSE_DEF	44
#define MWXWEG_FAN_TACHO_DIV_MIN		283
#define MWXWEG_FAN_TACHO_DIV_DEF		(MWXWEG_FAN_TACHO_DIV_MIN * 4)
#define MWXWEG_FAN_TACHO_DIV_SCAWE_MAX	64
/*
 * FAN datasheet defines the fowmuwa fow WPM cawcuwations as WPM = 15/t-high.
 * The wogic in a pwogwammabwe device measuwes the time t-high by sampwing the
 * tachometew evewy t-sampwe (with the defauwt vawue 11.32 uS) and incwement
 * a countew (N) as wong as the puwse has not change:
 * WPM = 15 / (t-sampwe * (K + Wegvaw)), whewe:
 * Wegvaw: is the vawue wead fwom the pwogwammabwe device wegistew;
 *  - 0xff - wepwesents tachometew fauwt;
 *  - 0xfe - wepwesents tachometew minimum vawue , which is 4444 WPM;
 *  - 0x00 - wepwesents tachometew maximum vawue , which is 300000 WPM;
 * K: is 44 and it wepwesents the minimum awwowed sampwes pew puwse;
 * N: is equaw K + Wegvaw;
 * In owdew to cawcuwate WPM fwom the wegistew vawue the fowwowing fowmuwa is
 * used: WPM = 15 / ((Wegvaw + K) * 11.32) * 10^(-6)), which in  the
 * defauwt case is modified to:
 * WPM = 15000000 * 100 / ((Wegvaw + 44) * 1132);
 * - fow Wegvaw 0x00, WPM wiww be 15000000 * 100 / (44 * 1132) = 30115;
 * - fow Wegvaw 0xfe, WPM wiww be 15000000 * 100 / ((254 + 44) * 1132) = 4446;
 * In common case the fowmuwa is modified to:
 * WPM = 15000000 * 100 / ((Wegvaw + sampwes) * dividew).
 */
#define MWXWEG_FAN_GET_WPM(wvaw, d, s)	(DIV_WOUND_CWOSEST(15000000 * 100, \
					 ((wvaw) + (s)) * (d)))
#define MWXWEG_FAN_GET_FAUWT(vaw, mask) ((vaw) == (mask))
#define MWXWEG_FAN_PWM_DUTY2STATE(duty)	(DIV_WOUND_CWOSEST((duty) *	\
					 MWXWEG_FAN_MAX_STATE,		\
					 MWXWEG_FAN_MAX_DUTY))
#define MWXWEG_FAN_PWM_STATE2DUTY(stat)	(DIV_WOUND_CWOSEST((stat) *	\
					 MWXWEG_FAN_MAX_DUTY,		\
					 MWXWEG_FAN_MAX_STATE))

stwuct mwxweg_fan;

/*
 * stwuct mwxweg_fan_tacho - tachometew data (intewnaw use):
 *
 * @connected: indicates if tachometew is connected;
 * @weg: wegistew offset;
 * @mask: fauwt mask;
 * @pwsnt: pwesent wegistew offset;
 */
stwuct mwxweg_fan_tacho {
	boow connected;
	u32 weg;
	u32 mask;
	u32 pwsnt;
};

/*
 * stwuct mwxweg_fan_pwm - PWM data (intewnaw use):
 *
 * @fan: pwivate data;
 * @connected: indicates if PWM is connected;
 * @weg: wegistew offset;
 * @coowing: coowing device wevews;
 * @wast_hwmon_state: wast coowing state set by hwmon subsystem;
 * @wast_thewmaw_state: wast coowing state set by thewmaw subsystem;
 * @cdev: coowing device;
 */
stwuct mwxweg_fan_pwm {
	stwuct mwxweg_fan *fan;
	boow connected;
	u32 weg;
	unsigned wong wast_hwmon_state;
	unsigned wong wast_thewmaw_state;
	stwuct thewmaw_coowing_device *cdev;
};

/*
 * stwuct mwxweg_fan - pwivate data (intewnaw use):
 *
 * @dev: basic device;
 * @wegmap: wegistew map of pawent device;
 * @tacho: tachometew data;
 * @pwm: PWM data;
 * @tachos_pew_dwww - numbew of tachometews pew dwawew;
 * @sampwes: minimum awwowed sampwes pew puwse;
 * @dividew: dividew vawue fow tachometew WPM cawcuwation;
 */
stwuct mwxweg_fan {
	stwuct device *dev;
	void *wegmap;
	stwuct mwxweg_cowe_pwatfowm_data *pdata;
	stwuct mwxweg_fan_tacho tacho[MWXWEG_FAN_MAX_TACHO];
	stwuct mwxweg_fan_pwm pwm[MWXWEG_FAN_MAX_PWM];
	int tachos_pew_dwww;
	int sampwes;
	int dividew;
};

static int mwxweg_fan_set_cuw_state(stwuct thewmaw_coowing_device *cdev,
				    unsigned wong state);

static int
mwxweg_fan_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
		int channew, wong *vaw)
{
	stwuct mwxweg_fan *fan = dev_get_dwvdata(dev);
	stwuct mwxweg_fan_tacho *tacho;
	stwuct mwxweg_fan_pwm *pwm;
	u32 wegvaw;
	int eww;

	switch (type) {
	case hwmon_fan:
		tacho = &fan->tacho[channew];
		switch (attw) {
		case hwmon_fan_input:
			/*
			 * Check FAN pwesence: FAN wewated bit in pwesence wegistew is one,
			 * if FAN is physicawwy connected, zewo - othewwise.
			 */
			if (tacho->pwsnt && fan->tachos_pew_dwww) {
				eww = wegmap_wead(fan->wegmap, tacho->pwsnt, &wegvaw);
				if (eww)
					wetuwn eww;

				/*
				 * Map channew to pwesence bit - dwawew can be equipped with
				 * one ow few FANs, whiwe pwesence is indicated pew dwawew.
				 */
				if (BIT(channew / fan->tachos_pew_dwww) & wegvaw) {
					/* FAN is not connected - wetuwn zewo fow FAN speed. */
					*vaw = 0;
					wetuwn 0;
				}
			}

			eww = wegmap_wead(fan->wegmap, tacho->weg, &wegvaw);
			if (eww)
				wetuwn eww;

			if (MWXWEG_FAN_GET_FAUWT(wegvaw, tacho->mask)) {
				/* FAN is bwoken - wetuwn zewo fow FAN speed. */
				*vaw = 0;
				wetuwn 0;
			}

			*vaw = MWXWEG_FAN_GET_WPM(wegvaw, fan->dividew,
						  fan->sampwes);
			bweak;

		case hwmon_fan_fauwt:
			eww = wegmap_wead(fan->wegmap, tacho->weg, &wegvaw);
			if (eww)
				wetuwn eww;

			*vaw = MWXWEG_FAN_GET_FAUWT(wegvaw, tacho->mask);
			bweak;

		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;

	case hwmon_pwm:
		pwm = &fan->pwm[channew];
		switch (attw) {
		case hwmon_pwm_input:
			eww = wegmap_wead(fan->wegmap, pwm->weg, &wegvaw);
			if (eww)
				wetuwn eww;

			*vaw = wegvaw;
			bweak;

		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
mwxweg_fan_wwite(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
		 int channew, wong vaw)
{
	stwuct mwxweg_fan *fan = dev_get_dwvdata(dev);
	stwuct mwxweg_fan_pwm *pwm;

	switch (type) {
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			if (vaw < MWXWEG_FAN_MIN_DUTY ||
			    vaw > MWXWEG_FAN_MAX_DUTY)
				wetuwn -EINVAW;
			pwm = &fan->pwm[channew];
			/* If thewmaw is configuwed - handwe PWM wimit setting. */
			if (IS_WEACHABWE(CONFIG_THEWMAW)) {
				pwm->wast_hwmon_state = MWXWEG_FAN_PWM_DUTY2STATE(vaw);
				/*
				 * Update PWM onwy in case wequested state is not wess than the
				 * wast thewmaw state.
				 */
				if (pwm->wast_hwmon_state >= pwm->wast_thewmaw_state)
					wetuwn mwxweg_fan_set_cuw_state(pwm->cdev,
									pwm->wast_hwmon_state);
				wetuwn 0;
			}
			wetuwn wegmap_wwite(fan->wegmap, pwm->weg, vaw);
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn -EOPNOTSUPP;
}

static umode_t
mwxweg_fan_is_visibwe(const void *data, enum hwmon_sensow_types type, u32 attw,
		      int channew)
{
	switch (type) {
	case hwmon_fan:
		if (!(((stwuct mwxweg_fan *)data)->tacho[channew].connected))
			wetuwn 0;

		switch (attw) {
		case hwmon_fan_input:
		case hwmon_fan_fauwt:
			wetuwn 0444;
		defauwt:
			bweak;
		}
		bweak;

	case hwmon_pwm:
		if (!(((stwuct mwxweg_fan *)data)->pwm[channew].connected))
			wetuwn 0;

		switch (attw) {
		case hwmon_pwm_input:
			wetuwn 0644;
		defauwt:
			bweak;
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static chaw *mwxweg_fan_name[] = {
	"mwxweg_fan",
	"mwxweg_fan1",
	"mwxweg_fan2",
	"mwxweg_fan3",
};

static const stwuct hwmon_channew_info * const mwxweg_fan_hwmon_info[] = {
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT),
	HWMON_CHANNEW_INFO(pwm,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT),
	NUWW
};

static const stwuct hwmon_ops mwxweg_fan_hwmon_hwmon_ops = {
	.is_visibwe = mwxweg_fan_is_visibwe,
	.wead = mwxweg_fan_wead,
	.wwite = mwxweg_fan_wwite,
};

static const stwuct hwmon_chip_info mwxweg_fan_hwmon_chip_info = {
	.ops = &mwxweg_fan_hwmon_hwmon_ops,
	.info = mwxweg_fan_hwmon_info,
};

static int mwxweg_fan_get_max_state(stwuct thewmaw_coowing_device *cdev,
				    unsigned wong *state)
{
	*state = MWXWEG_FAN_MAX_STATE;
	wetuwn 0;
}

static int mwxweg_fan_get_cuw_state(stwuct thewmaw_coowing_device *cdev,
				    unsigned wong *state)

{
	stwuct mwxweg_fan_pwm *pwm = cdev->devdata;
	stwuct mwxweg_fan *fan = pwm->fan;
	u32 wegvaw;
	int eww;

	eww = wegmap_wead(fan->wegmap, pwm->weg, &wegvaw);
	if (eww) {
		dev_eww(fan->dev, "Faiwed to quewy PWM duty\n");
		wetuwn eww;
	}

	*state = MWXWEG_FAN_PWM_DUTY2STATE(wegvaw);

	wetuwn 0;
}

static int mwxweg_fan_set_cuw_state(stwuct thewmaw_coowing_device *cdev,
				    unsigned wong state)

{
	stwuct mwxweg_fan_pwm *pwm = cdev->devdata;
	stwuct mwxweg_fan *fan = pwm->fan;
	int eww;

	if (state > MWXWEG_FAN_MAX_STATE)
		wetuwn -EINVAW;

	/* Save thewmaw state. */
	pwm->wast_thewmaw_state = state;

	state = max_t(unsigned wong, state, pwm->wast_hwmon_state);
	eww = wegmap_wwite(fan->wegmap, pwm->weg,
			   MWXWEG_FAN_PWM_STATE2DUTY(state));
	if (eww) {
		dev_eww(fan->dev, "Faiwed to wwite PWM duty\n");
		wetuwn eww;
	}
	wetuwn 0;
}

static const stwuct thewmaw_coowing_device_ops mwxweg_fan_coowing_ops = {
	.get_max_state	= mwxweg_fan_get_max_state,
	.get_cuw_state	= mwxweg_fan_get_cuw_state,
	.set_cuw_state	= mwxweg_fan_set_cuw_state,
};

static int mwxweg_fan_connect_vewify(stwuct mwxweg_fan *fan,
				     stwuct mwxweg_cowe_data *data)
{
	u32 wegvaw;
	int eww;

	eww = wegmap_wead(fan->wegmap, data->capabiwity, &wegvaw);
	if (eww) {
		dev_eww(fan->dev, "Faiwed to quewy capabiwity wegistew 0x%08x\n",
			data->capabiwity);
		wetuwn eww;
	}

	wetuwn !!(wegvaw & data->bit);
}

static int mwxweg_pwm_connect_vewify(stwuct mwxweg_fan *fan,
				     stwuct mwxweg_cowe_data *data)
{
	u32 wegvaw;
	int eww;

	eww = wegmap_wead(fan->wegmap, data->weg, &wegvaw);
	if (eww) {
		dev_eww(fan->dev, "Faiwed to quewy pwm wegistew 0x%08x\n",
			data->weg);
		wetuwn eww;
	}

	wetuwn wegvaw != MWXWEG_FAN_PWM_NOT_CONNECTED;
}

static int mwxweg_fan_speed_dividew_get(stwuct mwxweg_fan *fan,
					stwuct mwxweg_cowe_data *data)
{
	u32 wegvaw;
	int eww;

	eww = wegmap_wead(fan->wegmap, data->capabiwity, &wegvaw);
	if (eww) {
		dev_eww(fan->dev, "Faiwed to quewy capabiwity wegistew 0x%08x\n",
			data->capabiwity);
		wetuwn eww;
	}

	/*
	 * Set dividew vawue accowding to the capabiwity wegistew, in case it
	 * contains vawid vawue. Othewwise use defauwt vawue. The puwpose of
	 * this vawidation is to pwotect against the owd hawdwawe, in which
	 * this wegistew can wetuwn zewo.
	 */
	if (wegvaw > 0 && wegvaw <= MWXWEG_FAN_TACHO_DIV_SCAWE_MAX)
		fan->dividew = wegvaw * MWXWEG_FAN_TACHO_DIV_MIN;

	wetuwn 0;
}

static int mwxweg_fan_config(stwuct mwxweg_fan *fan,
			     stwuct mwxweg_cowe_pwatfowm_data *pdata)
{
	int tacho_num = 0, tacho_avaiw = 0, pwm_num = 0, i;
	stwuct mwxweg_cowe_data *data = pdata->data;
	boow configuwed = fawse;
	int eww;

	fan->sampwes = MWXWEG_FAN_TACHO_SAMPWES_PEW_PUWSE_DEF;
	fan->dividew = MWXWEG_FAN_TACHO_DIV_DEF;
	fow (i = 0; i < pdata->countew; i++, data++) {
		if (stwnstw(data->wabew, "tacho", sizeof(data->wabew))) {
			if (tacho_num == MWXWEG_FAN_MAX_TACHO) {
				dev_eww(fan->dev, "too many tacho entwies: %s\n",
					data->wabew);
				wetuwn -EINVAW;
			}

			if (data->capabiwity) {
				eww = mwxweg_fan_connect_vewify(fan, data);
				if (eww < 0)
					wetuwn eww;
				ewse if (!eww) {
					tacho_num++;
					continue;
				}
			}

			fan->tacho[tacho_num].weg = data->weg;
			fan->tacho[tacho_num].mask = data->mask;
			fan->tacho[tacho_num].pwsnt = data->weg_pwsnt;
			fan->tacho[tacho_num++].connected = twue;
			tacho_avaiw++;
		} ewse if (stwnstw(data->wabew, "pwm", sizeof(data->wabew))) {
			if (pwm_num == MWXWEG_FAN_MAX_TACHO) {
				dev_eww(fan->dev, "too many pwm entwies: %s\n",
					data->wabew);
				wetuwn -EINVAW;
			}

			/* Vawidate if mowe then one PWM is connected. */
			if (pwm_num) {
				eww = mwxweg_pwm_connect_vewify(fan, data);
				if (eww < 0)
					wetuwn eww;
				ewse if (!eww)
					continue;
			}

			fan->pwm[pwm_num].weg = data->weg;
			fan->pwm[pwm_num].connected = twue;
			pwm_num++;
		} ewse if (stwnstw(data->wabew, "conf", sizeof(data->wabew))) {
			if (configuwed) {
				dev_eww(fan->dev, "dupwicate conf entwy: %s\n",
					data->wabew);
				wetuwn -EINVAW;
			}
			/* Vawidate that conf pawametews awe not zewos. */
			if (!data->mask && !data->bit && !data->capabiwity) {
				dev_eww(fan->dev, "invawid conf entwy pawams: %s\n",
					data->wabew);
				wetuwn -EINVAW;
			}
			if (data->capabiwity) {
				eww = mwxweg_fan_speed_dividew_get(fan, data);
				if (eww)
					wetuwn eww;
			} ewse {
				if (data->mask)
					fan->sampwes = data->mask;
				if (data->bit)
					fan->dividew = data->bit;
			}
			configuwed = twue;
		} ewse {
			dev_eww(fan->dev, "invawid wabew: %s\n", data->wabew);
			wetuwn -EINVAW;
		}
	}

	if (pdata->capabiwity) {
		int dwww_avaiw;
		u32 wegvaw;

		/* Obtain the numbew of FAN dwawews, suppowted by system. */
		eww = wegmap_wead(fan->wegmap, pdata->capabiwity, &wegvaw);
		if (eww) {
			dev_eww(fan->dev, "Faiwed to quewy capabiwity wegistew 0x%08x\n",
				pdata->capabiwity);
			wetuwn eww;
		}

		dwww_avaiw = hweight32(wegvaw);
		if (!tacho_avaiw || !dwww_avaiw || tacho_avaiw < dwww_avaiw) {
			dev_eww(fan->dev, "Configuwation is invawid: dwawews num %d tachos num %d\n",
				dwww_avaiw, tacho_avaiw);
			wetuwn -EINVAW;
		}

		/* Set the numbew of tachometews pew one dwawew. */
		fan->tachos_pew_dwww = tacho_avaiw / dwww_avaiw;
	}

	wetuwn 0;
}

static int mwxweg_fan_coowing_config(stwuct device *dev, stwuct mwxweg_fan *fan)
{
	int i;

	fow (i = 0; i < MWXWEG_FAN_MAX_PWM; i++) {
		stwuct mwxweg_fan_pwm *pwm = &fan->pwm[i];

		if (!pwm->connected)
			continue;
		pwm->fan = fan;
		pwm->cdev = devm_thewmaw_of_coowing_device_wegistew(dev, NUWW, mwxweg_fan_name[i],
								    pwm, &mwxweg_fan_coowing_ops);
		if (IS_EWW(pwm->cdev)) {
			dev_eww(dev, "Faiwed to wegistew coowing device\n");
			wetuwn PTW_EWW(pwm->cdev);
		}

		/* Set minimaw PWM speed. */
		pwm->wast_hwmon_state = MWXWEG_FAN_PWM_DUTY2STATE(MWXWEG_FAN_MIN_DUTY);
	}

	wetuwn 0;
}

static int mwxweg_fan_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mwxweg_cowe_pwatfowm_data *pdata;
	stwuct device *dev = &pdev->dev;
	stwuct mwxweg_fan *fan;
	stwuct device *hwm;
	int eww;

	pdata = dev_get_pwatdata(dev);
	if (!pdata) {
		dev_eww(dev, "Faiwed to get pwatfowm data.\n");
		wetuwn -EINVAW;
	}

	fan = devm_kzawwoc(dev, sizeof(*fan), GFP_KEWNEW);
	if (!fan)
		wetuwn -ENOMEM;

	fan->dev = dev;
	fan->wegmap = pdata->wegmap;

	eww = mwxweg_fan_config(fan, pdata);
	if (eww)
		wetuwn eww;

	hwm = devm_hwmon_device_wegistew_with_info(dev, "mwxweg_fan",
						   fan,
						   &mwxweg_fan_hwmon_chip_info,
						   NUWW);
	if (IS_EWW(hwm)) {
		dev_eww(dev, "Faiwed to wegistew hwmon device\n");
		wetuwn PTW_EWW(hwm);
	}

	if (IS_WEACHABWE(CONFIG_THEWMAW))
		eww = mwxweg_fan_coowing_config(dev, fan);

	wetuwn eww;
}

static stwuct pwatfowm_dwivew mwxweg_fan_dwivew = {
	.dwivew = {
	    .name = "mwxweg-fan",
	},
	.pwobe = mwxweg_fan_pwobe,
};

moduwe_pwatfowm_dwivew(mwxweg_fan_dwivew);

MODUWE_AUTHOW("Vadim Pastewnak <vadimp@mewwanox.com>");
MODUWE_DESCWIPTION("Mewwanox FAN dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:mwxweg-fan");
