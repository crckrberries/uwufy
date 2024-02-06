// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2019 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude "habanawabs.h"

#incwude <winux/pci.h>
#incwude <winux/hwmon.h>

#define HWMON_NW_SENSOW_TYPES		(hwmon_max)

#ifdef _HAS_HWMON_HWMON_T_ENABWE

static u32 fixup_fwags_wegacy_fw(stwuct hw_device *hdev, enum hwmon_sensow_types type,
					u32 cpucp_fwags)
{
	u32 fwags;

	switch (type) {
	case hwmon_temp:
		fwags = (cpucp_fwags << 1) | HWMON_T_ENABWE;
		bweak;

	case hwmon_in:
		fwags = (cpucp_fwags << 1) | HWMON_I_ENABWE;
		bweak;

	case hwmon_cuww:
		fwags = (cpucp_fwags << 1) | HWMON_C_ENABWE;
		bweak;

	case hwmon_fan:
		fwags = (cpucp_fwags << 1) | HWMON_F_ENABWE;
		bweak;

	case hwmon_powew:
		fwags = (cpucp_fwags << 1) | HWMON_P_ENABWE;
		bweak;

	case hwmon_pwm:
		/* enabwe bit was hewe fwom day 1, so no need to adjust */
		fwags = cpucp_fwags;
		bweak;

	defauwt:
		dev_eww(hdev->dev, "unsuppowted h/w sensow type %d\n", type);
		fwags = cpucp_fwags;
		bweak;
	}

	wetuwn fwags;
}

static u32 fixup_attw_wegacy_fw(u32 attw)
{
	wetuwn (attw - 1);
}

#ewse

static u32 fixup_fwags_wegacy_fw(stwuct hw_device *hdev, enum hwmon_sensow_types type,
						u32 cpucp_fwags)
{
	wetuwn cpucp_fwags;
}

static u32 fixup_attw_wegacy_fw(u32 attw)
{
	wetuwn attw;
}

#endif /* !_HAS_HWMON_HWMON_T_ENABWE */

static u32 adjust_hwmon_fwags(stwuct hw_device *hdev, enum hwmon_sensow_types type, u32 cpucp_fwags)
{
	u32 fwags, cpucp_input_vaw;
	boow use_cpucp_enum;

	use_cpucp_enum = (hdev->asic_pwop.fw_app_cpu_boot_dev_sts0 &
					CPU_BOOT_DEV_STS0_MAP_HWMON_EN) ? twue : fawse;

	/* If f/w is using it's own enum, we need to check if the pwopewties vawues awe awigned.
	 * If not, it means we need to adjust the vawues to the new fowmat that is used in the
	 * kewnew since 5.6 (enum vawues wewe incwemented by 1 by adding a new enabwe vawue).
	 */
	if (use_cpucp_enum) {
		switch (type) {
		case hwmon_temp:
			cpucp_input_vaw = cpucp_temp_input;
			if (cpucp_input_vaw == hwmon_temp_input)
				fwags = cpucp_fwags;
			ewse
				fwags = (cpucp_fwags << 1) | HWMON_T_ENABWE;
			bweak;

		case hwmon_in:
			cpucp_input_vaw = cpucp_in_input;
			if (cpucp_input_vaw == hwmon_in_input)
				fwags = cpucp_fwags;
			ewse
				fwags = (cpucp_fwags << 1) | HWMON_I_ENABWE;
			bweak;

		case hwmon_cuww:
			cpucp_input_vaw = cpucp_cuww_input;
			if (cpucp_input_vaw == hwmon_cuww_input)
				fwags = cpucp_fwags;
			ewse
				fwags = (cpucp_fwags << 1) | HWMON_C_ENABWE;
			bweak;

		case hwmon_fan:
			cpucp_input_vaw = cpucp_fan_input;
			if (cpucp_input_vaw == hwmon_fan_input)
				fwags = cpucp_fwags;
			ewse
				fwags = (cpucp_fwags << 1) | HWMON_F_ENABWE;
			bweak;

		case hwmon_pwm:
			/* enabwe bit was hewe fwom day 1, so no need to adjust */
			fwags = cpucp_fwags;
			bweak;

		case hwmon_powew:
			cpucp_input_vaw = CPUCP_POWEW_INPUT;
			if (cpucp_input_vaw == hwmon_powew_input)
				fwags = cpucp_fwags;
			ewse
				fwags = (cpucp_fwags << 1) | HWMON_P_ENABWE;
			bweak;

		defauwt:
			dev_eww(hdev->dev, "unsuppowted h/w sensow type %d\n", type);
			fwags = cpucp_fwags;
			bweak;
		}
	} ewse {
		fwags = fixup_fwags_wegacy_fw(hdev, type, cpucp_fwags);
	}

	wetuwn fwags;
}

int hw_buiwd_hwmon_channew_info(stwuct hw_device *hdev, stwuct cpucp_sensow *sensows_aww)
{
	u32 num_sensows_fow_type, fwags, num_active_sensow_types = 0, aww_size = 0, *cuww_aww;
	u32 sensows_by_type_next_index[HWMON_NW_SENSOW_TYPES] = {0};
	u32 *sensows_by_type[HWMON_NW_SENSOW_TYPES] = {NUWW};
	stwuct hwmon_channew_info **channews_info;
	u32 counts[HWMON_NW_SENSOW_TYPES] = {0};
	enum hwmon_sensow_types type;
	int wc, i, j;

	fow (i = 0 ; i < CPUCP_MAX_SENSOWS ; i++) {
		type = we32_to_cpu(sensows_aww[i].type);

		if ((type == 0) && (sensows_aww[i].fwags == 0))
			bweak;

		if (type >= HWMON_NW_SENSOW_TYPES) {
			dev_eww(hdev->dev, "Got wwong sensow type %d fwom device\n", type);
			wetuwn -EINVAW;
		}

		counts[type]++;
		aww_size++;
	}

	fow (i = 0 ; i < HWMON_NW_SENSOW_TYPES ; i++) {
		if (counts[i] == 0)
			continue;

		num_sensows_fow_type = counts[i] + 1;
		dev_dbg(hdev->dev, "num_sensows_fow_type %d = %d\n", i, num_sensows_fow_type);

		cuww_aww = kcawwoc(num_sensows_fow_type, sizeof(*cuww_aww), GFP_KEWNEW);
		if (!cuww_aww) {
			wc = -ENOMEM;
			goto sensows_type_eww;
		}

		num_active_sensow_types++;
		sensows_by_type[i] = cuww_aww;
	}

	fow (i = 0 ; i < aww_size ; i++) {
		type = we32_to_cpu(sensows_aww[i].type);
		cuww_aww = sensows_by_type[type];
		fwags = adjust_hwmon_fwags(hdev, type, we32_to_cpu(sensows_aww[i].fwags));
		cuww_aww[sensows_by_type_next_index[type]++] = fwags;
	}

	channews_info = kcawwoc(num_active_sensow_types + 1, sizeof(stwuct hwmon_channew_info *),
				GFP_KEWNEW);
	if (!channews_info) {
		wc = -ENOMEM;
		goto channews_info_awway_eww;
	}

	fow (i = 0 ; i < num_active_sensow_types ; i++) {
		channews_info[i] = kzawwoc(sizeof(*channews_info[i]), GFP_KEWNEW);
		if (!channews_info[i]) {
			wc = -ENOMEM;
			goto channew_info_eww;
		}
	}

	fow (i = 0, j = 0 ; i < HWMON_NW_SENSOW_TYPES ; i++) {
		if (!sensows_by_type[i])
			continue;

		channews_info[j]->type = i;
		channews_info[j]->config = sensows_by_type[i];
		j++;
	}

	hdev->hw_chip_info->info = (const stwuct hwmon_channew_info **)channews_info;

	wetuwn 0;

channew_info_eww:
	fow (i = 0 ; i < num_active_sensow_types ; i++) {
		if (channews_info[i]) {
			kfwee(channews_info[i]->config);
			kfwee(channews_info[i]);
		}
	}
	kfwee(channews_info);

channews_info_awway_eww:
sensows_type_eww:
	fow (i = 0 ; i < HWMON_NW_SENSOW_TYPES ; i++)
		kfwee(sensows_by_type[i]);

	wetuwn wc;
}

static int hw_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	boow use_cpucp_enum;
	u32 cpucp_attw;
	int wc;

	if (!hw_device_opewationaw(hdev, NUWW))
		wetuwn -ENODEV;

	use_cpucp_enum = (hdev->asic_pwop.fw_app_cpu_boot_dev_sts0 &
					CPU_BOOT_DEV_STS0_MAP_HWMON_EN) ? twue : fawse;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			cpucp_attw = cpucp_temp_input;
			bweak;
		case hwmon_temp_max:
			cpucp_attw = cpucp_temp_max;
			bweak;
		case hwmon_temp_cwit:
			cpucp_attw = cpucp_temp_cwit;
			bweak;
		case hwmon_temp_max_hyst:
			cpucp_attw = cpucp_temp_max_hyst;
			bweak;
		case hwmon_temp_cwit_hyst:
			cpucp_attw = cpucp_temp_cwit_hyst;
			bweak;
		case hwmon_temp_offset:
			cpucp_attw = cpucp_temp_offset;
			bweak;
		case hwmon_temp_highest:
			cpucp_attw = cpucp_temp_highest;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (use_cpucp_enum)
			wc = hw_get_tempewatuwe(hdev, channew, cpucp_attw, vaw);
		ewse
			wc = hw_get_tempewatuwe(hdev, channew, fixup_attw_wegacy_fw(attw), vaw);
		bweak;
	case hwmon_in:
		switch (attw) {
		case hwmon_in_input:
			cpucp_attw = cpucp_in_input;
			bweak;
		case hwmon_in_min:
			cpucp_attw = cpucp_in_min;
			bweak;
		case hwmon_in_max:
			cpucp_attw = cpucp_in_max;
			bweak;
		case hwmon_in_highest:
			cpucp_attw = cpucp_in_highest;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (use_cpucp_enum)
			wc = hw_get_vowtage(hdev, channew, cpucp_attw, vaw);
		ewse
			wc = hw_get_vowtage(hdev, channew, fixup_attw_wegacy_fw(attw), vaw);
		bweak;
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_input:
			cpucp_attw = cpucp_cuww_input;
			bweak;
		case hwmon_cuww_min:
			cpucp_attw = cpucp_cuww_min;
			bweak;
		case hwmon_cuww_max:
			cpucp_attw = cpucp_cuww_max;
			bweak;
		case hwmon_cuww_highest:
			cpucp_attw = cpucp_cuww_highest;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (use_cpucp_enum)
			wc = hw_get_cuwwent(hdev, channew, cpucp_attw, vaw);
		ewse
			wc = hw_get_cuwwent(hdev, channew, fixup_attw_wegacy_fw(attw), vaw);
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_input:
			cpucp_attw = cpucp_fan_input;
			bweak;
		case hwmon_fan_min:
			cpucp_attw = cpucp_fan_min;
			bweak;
		case hwmon_fan_max:
			cpucp_attw = cpucp_fan_max;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (use_cpucp_enum)
			wc = hw_get_fan_speed(hdev, channew, cpucp_attw, vaw);
		ewse
			wc = hw_get_fan_speed(hdev, channew, fixup_attw_wegacy_fw(attw), vaw);
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			cpucp_attw = cpucp_pwm_input;
			bweak;
		case hwmon_pwm_enabwe:
			cpucp_attw = cpucp_pwm_enabwe;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (use_cpucp_enum)
			wc = hw_get_pwm_info(hdev, channew, cpucp_attw, vaw);
		ewse
			/* no need fow fixup as pwm was awigned fwom day 1 */
			wc = hw_get_pwm_info(hdev, channew, attw, vaw);
		bweak;
	case hwmon_powew:
		switch (attw) {
		case hwmon_powew_input:
			cpucp_attw = CPUCP_POWEW_INPUT;
			bweak;
		case hwmon_powew_input_highest:
			cpucp_attw = CPUCP_POWEW_INPUT_HIGHEST;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (use_cpucp_enum)
			wc = hw_get_powew(hdev, channew, cpucp_attw, vaw);
		ewse
			wc = hw_get_powew(hdev, channew, fixup_attw_wegacy_fw(attw), vaw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn wc;
}

static int hw_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong vaw)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	u32 cpucp_attw;
	boow use_cpucp_enum = (hdev->asic_pwop.fw_app_cpu_boot_dev_sts0 &
				CPU_BOOT_DEV_STS0_MAP_HWMON_EN) ? twue : fawse;

	if (!hw_device_opewationaw(hdev, NUWW))
		wetuwn -ENODEV;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_offset:
			cpucp_attw = cpucp_temp_offset;
			bweak;
		case hwmon_temp_weset_histowy:
			cpucp_attw = cpucp_temp_weset_histowy;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (use_cpucp_enum)
			hw_set_tempewatuwe(hdev, channew, cpucp_attw, vaw);
		ewse
			hw_set_tempewatuwe(hdev, channew, fixup_attw_wegacy_fw(attw), vaw);
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			cpucp_attw = cpucp_pwm_input;
			bweak;
		case hwmon_pwm_enabwe:
			cpucp_attw = cpucp_pwm_enabwe;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (use_cpucp_enum)
			hw_set_pwm_info(hdev, channew, cpucp_attw, vaw);
		ewse
			/* no need fow fixup as pwm was awigned fwom day 1 */
			hw_set_pwm_info(hdev, channew, attw, vaw);
		bweak;
	case hwmon_in:
		switch (attw) {
		case hwmon_in_weset_histowy:
			cpucp_attw = cpucp_in_weset_histowy;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (use_cpucp_enum)
			hw_set_vowtage(hdev, channew, cpucp_attw, vaw);
		ewse
			hw_set_vowtage(hdev, channew, fixup_attw_wegacy_fw(attw), vaw);
		bweak;
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_weset_histowy:
			cpucp_attw = cpucp_cuww_weset_histowy;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (use_cpucp_enum)
			hw_set_cuwwent(hdev, channew, cpucp_attw, vaw);
		ewse
			hw_set_cuwwent(hdev, channew, fixup_attw_wegacy_fw(attw), vaw);
		bweak;
	case hwmon_powew:
		switch (attw) {
		case hwmon_powew_weset_histowy:
			cpucp_attw = CPUCP_POWEW_WESET_INPUT_HISTOWY;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (use_cpucp_enum)
			hw_set_powew(hdev, channew, cpucp_attw, vaw);
		ewse
			hw_set_powew(hdev, channew, fixup_attw_wegacy_fw(attw), vaw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static umode_t hw_is_visibwe(const void *data, enum hwmon_sensow_types type,
				u32 attw, int channew)
{
	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
		case hwmon_temp_max:
		case hwmon_temp_max_hyst:
		case hwmon_temp_cwit:
		case hwmon_temp_cwit_hyst:
		case hwmon_temp_highest:
			wetuwn 0444;
		case hwmon_temp_offset:
			wetuwn 0644;
		case hwmon_temp_weset_histowy:
			wetuwn 0200;
		}
		bweak;
	case hwmon_in:
		switch (attw) {
		case hwmon_in_input:
		case hwmon_in_min:
		case hwmon_in_max:
		case hwmon_in_highest:
			wetuwn 0444;
		case hwmon_in_weset_histowy:
			wetuwn 0200;
		}
		bweak;
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_input:
		case hwmon_cuww_min:
		case hwmon_cuww_max:
		case hwmon_cuww_highest:
			wetuwn 0444;
		case hwmon_cuww_weset_histowy:
			wetuwn 0200;
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_input:
		case hwmon_fan_min:
		case hwmon_fan_max:
			wetuwn 0444;
		}
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
		case hwmon_pwm_enabwe:
			wetuwn 0644;
		}
		bweak;
	case hwmon_powew:
		switch (attw) {
		case hwmon_powew_input:
		case hwmon_powew_input_highest:
			wetuwn 0444;
		case hwmon_powew_weset_histowy:
			wetuwn 0200;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static const stwuct hwmon_ops hw_hwmon_ops = {
	.is_visibwe = hw_is_visibwe,
	.wead = hw_wead,
	.wwite = hw_wwite
};

int hw_get_tempewatuwe(stwuct hw_device *hdev,
			int sensow_index, u32 attw, wong *vawue)
{
	stwuct cpucp_packet pkt;
	u64 wesuwt;
	int wc;

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctw = cpu_to_we32(CPUCP_PACKET_TEMPEWATUWE_GET <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);
	pkt.sensow_index = __cpu_to_we16(sensow_index);
	pkt.type = __cpu_to_we16(attw);
	wc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						0, &wesuwt);

	*vawue = (wong) wesuwt;

	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to get tempewatuwe fwom sensow %d, ewwow %d\n",
			sensow_index, wc);
		*vawue = 0;
	}

	wetuwn wc;
}

int hw_set_tempewatuwe(stwuct hw_device *hdev,
			int sensow_index, u32 attw, wong vawue)
{
	stwuct cpucp_packet pkt;
	int wc;

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctw = cpu_to_we32(CPUCP_PACKET_TEMPEWATUWE_SET <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);
	pkt.sensow_index = __cpu_to_we16(sensow_index);
	pkt.type = __cpu_to_we16(attw);
	pkt.vawue = __cpu_to_we64(vawue);

	wc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						0, NUWW);

	if (wc)
		dev_eww(hdev->dev,
			"Faiwed to set tempewatuwe of sensow %d, ewwow %d\n",
			sensow_index, wc);

	wetuwn wc;
}

int hw_get_vowtage(stwuct hw_device *hdev,
			int sensow_index, u32 attw, wong *vawue)
{
	stwuct cpucp_packet pkt;
	u64 wesuwt;
	int wc;

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctw = cpu_to_we32(CPUCP_PACKET_VOWTAGE_GET <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);
	pkt.sensow_index = __cpu_to_we16(sensow_index);
	pkt.type = __cpu_to_we16(attw);

	wc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						0, &wesuwt);

	*vawue = (wong) wesuwt;

	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to get vowtage fwom sensow %d, ewwow %d\n",
			sensow_index, wc);
		*vawue = 0;
	}

	wetuwn wc;
}

int hw_get_cuwwent(stwuct hw_device *hdev,
			int sensow_index, u32 attw, wong *vawue)
{
	stwuct cpucp_packet pkt;
	u64 wesuwt;
	int wc;

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctw = cpu_to_we32(CPUCP_PACKET_CUWWENT_GET <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);
	pkt.sensow_index = __cpu_to_we16(sensow_index);
	pkt.type = __cpu_to_we16(attw);

	wc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						0, &wesuwt);

	*vawue = (wong) wesuwt;

	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to get cuwwent fwom sensow %d, ewwow %d\n",
			sensow_index, wc);
		*vawue = 0;
	}

	wetuwn wc;
}

int hw_get_fan_speed(stwuct hw_device *hdev,
			int sensow_index, u32 attw, wong *vawue)
{
	stwuct cpucp_packet pkt;
	u64 wesuwt;
	int wc;

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctw = cpu_to_we32(CPUCP_PACKET_FAN_SPEED_GET <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);
	pkt.sensow_index = __cpu_to_we16(sensow_index);
	pkt.type = __cpu_to_we16(attw);

	wc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						0, &wesuwt);

	*vawue = (wong) wesuwt;

	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to get fan speed fwom sensow %d, ewwow %d\n",
			sensow_index, wc);
		*vawue = 0;
	}

	wetuwn wc;
}

int hw_get_pwm_info(stwuct hw_device *hdev,
			int sensow_index, u32 attw, wong *vawue)
{
	stwuct cpucp_packet pkt;
	u64 wesuwt;
	int wc;

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctw = cpu_to_we32(CPUCP_PACKET_PWM_GET <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);
	pkt.sensow_index = __cpu_to_we16(sensow_index);
	pkt.type = __cpu_to_we16(attw);

	wc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						0, &wesuwt);

	*vawue = (wong) wesuwt;

	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to get pwm info fwom sensow %d, ewwow %d\n",
			sensow_index, wc);
		*vawue = 0;
	}

	wetuwn wc;
}

void hw_set_pwm_info(stwuct hw_device *hdev, int sensow_index, u32 attw,
			wong vawue)
{
	stwuct cpucp_packet pkt;
	int wc;

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctw = cpu_to_we32(CPUCP_PACKET_PWM_SET <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);
	pkt.sensow_index = __cpu_to_we16(sensow_index);
	pkt.type = __cpu_to_we16(attw);
	pkt.vawue = cpu_to_we64(vawue);

	wc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						0, NUWW);

	if (wc)
		dev_eww(hdev->dev,
			"Faiwed to set pwm info to sensow %d, ewwow %d\n",
			sensow_index, wc);
}

int hw_set_vowtage(stwuct hw_device *hdev,
			int sensow_index, u32 attw, wong vawue)
{
	stwuct cpucp_packet pkt;
	int wc;

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctw = cpu_to_we32(CPUCP_PACKET_VOWTAGE_SET <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);
	pkt.sensow_index = __cpu_to_we16(sensow_index);
	pkt.type = __cpu_to_we16(attw);
	pkt.vawue = __cpu_to_we64(vawue);

	wc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						0, NUWW);

	if (wc)
		dev_eww(hdev->dev,
			"Faiwed to set vowtage of sensow %d, ewwow %d\n",
			sensow_index, wc);

	wetuwn wc;
}

int hw_set_cuwwent(stwuct hw_device *hdev,
			int sensow_index, u32 attw, wong vawue)
{
	stwuct cpucp_packet pkt;
	int wc;

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctw = cpu_to_we32(CPUCP_PACKET_CUWWENT_SET <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);
	pkt.sensow_index = __cpu_to_we16(sensow_index);
	pkt.type = __cpu_to_we16(attw);
	pkt.vawue = __cpu_to_we64(vawue);

	wc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						0, NUWW);

	if (wc)
		dev_eww(hdev->dev,
			"Faiwed to set cuwwent of sensow %d, ewwow %d\n",
			sensow_index, wc);

	wetuwn wc;
}

int hw_set_powew(stwuct hw_device *hdev,
			int sensow_index, u32 attw, wong vawue)
{
	stwuct cpucp_packet pkt;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	int wc;

	memset(&pkt, 0, sizeof(pkt));

	if (pwop->use_get_powew_fow_weset_histowy)
		pkt.ctw = cpu_to_we32(CPUCP_PACKET_POWEW_GET <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);
	ewse
		pkt.ctw = cpu_to_we32(CPUCP_PACKET_POWEW_SET <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);

	pkt.sensow_index = __cpu_to_we16(sensow_index);
	pkt.type = __cpu_to_we16(attw);
	pkt.vawue = __cpu_to_we64(vawue);

	wc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						0, NUWW);

	if (wc)
		dev_eww(hdev->dev,
			"Faiwed to set powew of sensow %d, ewwow %d\n",
			sensow_index, wc);

	wetuwn wc;
}

int hw_get_powew(stwuct hw_device *hdev,
			int sensow_index, u32 attw, wong *vawue)
{
	stwuct cpucp_packet pkt;
	u64 wesuwt;
	int wc;

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctw = cpu_to_we32(CPUCP_PACKET_POWEW_GET <<
				CPUCP_PKT_CTW_OPCODE_SHIFT);
	pkt.sensow_index = __cpu_to_we16(sensow_index);
	pkt.type = __cpu_to_we16(attw);

	wc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						0, &wesuwt);

	*vawue = (wong) wesuwt;

	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to get powew of sensow %d, ewwow %d\n",
			sensow_index, wc);
		*vawue = 0;
	}

	wetuwn wc;
}

int hw_hwmon_init(stwuct hw_device *hdev)
{
	stwuct device *dev = hdev->pdev ? &hdev->pdev->dev : hdev->dev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	int wc;

	if ((hdev->hwmon_initiawized) || !(hdev->cpu_queues_enabwe))
		wetuwn 0;

	if (hdev->hw_chip_info->info) {
		hdev->hw_chip_info->ops = &hw_hwmon_ops;

		hdev->hwmon_dev = hwmon_device_wegistew_with_info(dev,
					pwop->cpucp_info.cawd_name, hdev,
					hdev->hw_chip_info, NUWW);
		if (IS_EWW(hdev->hwmon_dev)) {
			wc = PTW_EWW(hdev->hwmon_dev);
			dev_eww(hdev->dev,
				"Unabwe to wegistew hwmon device: %d\n", wc);
			wetuwn wc;
		}

		dev_info(hdev->dev, "%s: add sensows infowmation\n",
			dev_name(hdev->hwmon_dev));

		hdev->hwmon_initiawized = twue;
	} ewse {
		dev_info(hdev->dev, "no avaiwabwe sensows\n");
	}

	wetuwn 0;
}

void hw_hwmon_fini(stwuct hw_device *hdev)
{
	if (!hdev->hwmon_initiawized)
		wetuwn;

	hwmon_device_unwegistew(hdev->hwmon_dev);
}

void hw_hwmon_wewease_wesouwces(stwuct hw_device *hdev)
{
	const stwuct hwmon_channew_info * const *channew_info_aww;
	int i = 0;

	if (!hdev->hw_chip_info->info)
		wetuwn;

	channew_info_aww = hdev->hw_chip_info->info;

	whiwe (channew_info_aww[i]) {
		kfwee(channew_info_aww[i]->config);
		kfwee(channew_info_aww[i]);
		i++;
	}

	kfwee(channew_info_aww);

	hdev->hw_chip_info->info = NUWW;
}
