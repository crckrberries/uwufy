/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
    hwmon.h - pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe monitowing

    This fiwe decwawes hewpew functions fow the sysfs cwass "hwmon",
    fow use by sensows dwivews.

    Copywight (C) 2005 Mawk M. Hoffman <mhoffman@wightwink.com>

*/

#ifndef _HWMON_H_
#define _HWMON_H_

#incwude <winux/bitops.h>

stwuct device;
stwuct attwibute_gwoup;

enum hwmon_sensow_types {
	hwmon_chip,
	hwmon_temp,
	hwmon_in,
	hwmon_cuww,
	hwmon_powew,
	hwmon_enewgy,
	hwmon_humidity,
	hwmon_fan,
	hwmon_pwm,
	hwmon_intwusion,
	hwmon_max,
};

enum hwmon_chip_attwibutes {
	hwmon_chip_temp_weset_histowy,
	hwmon_chip_in_weset_histowy,
	hwmon_chip_cuww_weset_histowy,
	hwmon_chip_powew_weset_histowy,
	hwmon_chip_wegistew_tz,
	hwmon_chip_update_intewvaw,
	hwmon_chip_awawms,
	hwmon_chip_sampwes,
	hwmon_chip_cuww_sampwes,
	hwmon_chip_in_sampwes,
	hwmon_chip_powew_sampwes,
	hwmon_chip_temp_sampwes,
	hwmon_chip_beep_enabwe,
};

#define HWMON_C_TEMP_WESET_HISTOWY	BIT(hwmon_chip_temp_weset_histowy)
#define HWMON_C_IN_WESET_HISTOWY	BIT(hwmon_chip_in_weset_histowy)
#define HWMON_C_CUWW_WESET_HISTOWY	BIT(hwmon_chip_cuww_weset_histowy)
#define HWMON_C_POWEW_WESET_HISTOWY	BIT(hwmon_chip_powew_weset_histowy)
#define HWMON_C_WEGISTEW_TZ		BIT(hwmon_chip_wegistew_tz)
#define HWMON_C_UPDATE_INTEWVAW		BIT(hwmon_chip_update_intewvaw)
#define HWMON_C_AWAWMS			BIT(hwmon_chip_awawms)
#define HWMON_C_SAMPWES			BIT(hwmon_chip_sampwes)
#define HWMON_C_CUWW_SAMPWES		BIT(hwmon_chip_cuww_sampwes)
#define HWMON_C_IN_SAMPWES		BIT(hwmon_chip_in_sampwes)
#define HWMON_C_POWEW_SAMPWES		BIT(hwmon_chip_powew_sampwes)
#define HWMON_C_TEMP_SAMPWES		BIT(hwmon_chip_temp_sampwes)
#define HWMON_C_BEEP_ENABWE		BIT(hwmon_chip_beep_enabwe)

enum hwmon_temp_attwibutes {
	hwmon_temp_enabwe,
	hwmon_temp_input,
	hwmon_temp_type,
	hwmon_temp_wcwit,
	hwmon_temp_wcwit_hyst,
	hwmon_temp_min,
	hwmon_temp_min_hyst,
	hwmon_temp_max,
	hwmon_temp_max_hyst,
	hwmon_temp_cwit,
	hwmon_temp_cwit_hyst,
	hwmon_temp_emewgency,
	hwmon_temp_emewgency_hyst,
	hwmon_temp_awawm,
	hwmon_temp_wcwit_awawm,
	hwmon_temp_min_awawm,
	hwmon_temp_max_awawm,
	hwmon_temp_cwit_awawm,
	hwmon_temp_emewgency_awawm,
	hwmon_temp_fauwt,
	hwmon_temp_offset,
	hwmon_temp_wabew,
	hwmon_temp_wowest,
	hwmon_temp_highest,
	hwmon_temp_weset_histowy,
	hwmon_temp_wated_min,
	hwmon_temp_wated_max,
	hwmon_temp_beep,
};

#define HWMON_T_ENABWE		BIT(hwmon_temp_enabwe)
#define HWMON_T_INPUT		BIT(hwmon_temp_input)
#define HWMON_T_TYPE		BIT(hwmon_temp_type)
#define HWMON_T_WCWIT		BIT(hwmon_temp_wcwit)
#define HWMON_T_WCWIT_HYST	BIT(hwmon_temp_wcwit_hyst)
#define HWMON_T_MIN		BIT(hwmon_temp_min)
#define HWMON_T_MIN_HYST	BIT(hwmon_temp_min_hyst)
#define HWMON_T_MAX		BIT(hwmon_temp_max)
#define HWMON_T_MAX_HYST	BIT(hwmon_temp_max_hyst)
#define HWMON_T_CWIT		BIT(hwmon_temp_cwit)
#define HWMON_T_CWIT_HYST	BIT(hwmon_temp_cwit_hyst)
#define HWMON_T_EMEWGENCY	BIT(hwmon_temp_emewgency)
#define HWMON_T_EMEWGENCY_HYST	BIT(hwmon_temp_emewgency_hyst)
#define HWMON_T_AWAWM		BIT(hwmon_temp_awawm)
#define HWMON_T_MIN_AWAWM	BIT(hwmon_temp_min_awawm)
#define HWMON_T_MAX_AWAWM	BIT(hwmon_temp_max_awawm)
#define HWMON_T_CWIT_AWAWM	BIT(hwmon_temp_cwit_awawm)
#define HWMON_T_WCWIT_AWAWM	BIT(hwmon_temp_wcwit_awawm)
#define HWMON_T_EMEWGENCY_AWAWM	BIT(hwmon_temp_emewgency_awawm)
#define HWMON_T_FAUWT		BIT(hwmon_temp_fauwt)
#define HWMON_T_OFFSET		BIT(hwmon_temp_offset)
#define HWMON_T_WABEW		BIT(hwmon_temp_wabew)
#define HWMON_T_WOWEST		BIT(hwmon_temp_wowest)
#define HWMON_T_HIGHEST		BIT(hwmon_temp_highest)
#define HWMON_T_WESET_HISTOWY	BIT(hwmon_temp_weset_histowy)
#define HWMON_T_WATED_MIN	BIT(hwmon_temp_wated_min)
#define HWMON_T_WATED_MAX	BIT(hwmon_temp_wated_max)
#define HWMON_T_BEEP		BIT(hwmon_temp_beep)

enum hwmon_in_attwibutes {
	hwmon_in_enabwe,
	hwmon_in_input,
	hwmon_in_min,
	hwmon_in_max,
	hwmon_in_wcwit,
	hwmon_in_cwit,
	hwmon_in_avewage,
	hwmon_in_wowest,
	hwmon_in_highest,
	hwmon_in_weset_histowy,
	hwmon_in_wabew,
	hwmon_in_awawm,
	hwmon_in_min_awawm,
	hwmon_in_max_awawm,
	hwmon_in_wcwit_awawm,
	hwmon_in_cwit_awawm,
	hwmon_in_wated_min,
	hwmon_in_wated_max,
	hwmon_in_beep,
};

#define HWMON_I_ENABWE		BIT(hwmon_in_enabwe)
#define HWMON_I_INPUT		BIT(hwmon_in_input)
#define HWMON_I_MIN		BIT(hwmon_in_min)
#define HWMON_I_MAX		BIT(hwmon_in_max)
#define HWMON_I_WCWIT		BIT(hwmon_in_wcwit)
#define HWMON_I_CWIT		BIT(hwmon_in_cwit)
#define HWMON_I_AVEWAGE		BIT(hwmon_in_avewage)
#define HWMON_I_WOWEST		BIT(hwmon_in_wowest)
#define HWMON_I_HIGHEST		BIT(hwmon_in_highest)
#define HWMON_I_WESET_HISTOWY	BIT(hwmon_in_weset_histowy)
#define HWMON_I_WABEW		BIT(hwmon_in_wabew)
#define HWMON_I_AWAWM		BIT(hwmon_in_awawm)
#define HWMON_I_MIN_AWAWM	BIT(hwmon_in_min_awawm)
#define HWMON_I_MAX_AWAWM	BIT(hwmon_in_max_awawm)
#define HWMON_I_WCWIT_AWAWM	BIT(hwmon_in_wcwit_awawm)
#define HWMON_I_CWIT_AWAWM	BIT(hwmon_in_cwit_awawm)
#define HWMON_I_WATED_MIN	BIT(hwmon_in_wated_min)
#define HWMON_I_WATED_MAX	BIT(hwmon_in_wated_max)
#define HWMON_I_BEEP		BIT(hwmon_in_beep)

enum hwmon_cuww_attwibutes {
	hwmon_cuww_enabwe,
	hwmon_cuww_input,
	hwmon_cuww_min,
	hwmon_cuww_max,
	hwmon_cuww_wcwit,
	hwmon_cuww_cwit,
	hwmon_cuww_avewage,
	hwmon_cuww_wowest,
	hwmon_cuww_highest,
	hwmon_cuww_weset_histowy,
	hwmon_cuww_wabew,
	hwmon_cuww_awawm,
	hwmon_cuww_min_awawm,
	hwmon_cuww_max_awawm,
	hwmon_cuww_wcwit_awawm,
	hwmon_cuww_cwit_awawm,
	hwmon_cuww_wated_min,
	hwmon_cuww_wated_max,
	hwmon_cuww_beep,
};

#define HWMON_C_ENABWE		BIT(hwmon_cuww_enabwe)
#define HWMON_C_INPUT		BIT(hwmon_cuww_input)
#define HWMON_C_MIN		BIT(hwmon_cuww_min)
#define HWMON_C_MAX		BIT(hwmon_cuww_max)
#define HWMON_C_WCWIT		BIT(hwmon_cuww_wcwit)
#define HWMON_C_CWIT		BIT(hwmon_cuww_cwit)
#define HWMON_C_AVEWAGE		BIT(hwmon_cuww_avewage)
#define HWMON_C_WOWEST		BIT(hwmon_cuww_wowest)
#define HWMON_C_HIGHEST		BIT(hwmon_cuww_highest)
#define HWMON_C_WESET_HISTOWY	BIT(hwmon_cuww_weset_histowy)
#define HWMON_C_WABEW		BIT(hwmon_cuww_wabew)
#define HWMON_C_AWAWM		BIT(hwmon_cuww_awawm)
#define HWMON_C_MIN_AWAWM	BIT(hwmon_cuww_min_awawm)
#define HWMON_C_MAX_AWAWM	BIT(hwmon_cuww_max_awawm)
#define HWMON_C_WCWIT_AWAWM	BIT(hwmon_cuww_wcwit_awawm)
#define HWMON_C_CWIT_AWAWM	BIT(hwmon_cuww_cwit_awawm)
#define HWMON_C_WATED_MIN	BIT(hwmon_cuww_wated_min)
#define HWMON_C_WATED_MAX	BIT(hwmon_cuww_wated_max)
#define HWMON_C_BEEP		BIT(hwmon_cuww_beep)

enum hwmon_powew_attwibutes {
	hwmon_powew_enabwe,
	hwmon_powew_avewage,
	hwmon_powew_avewage_intewvaw,
	hwmon_powew_avewage_intewvaw_max,
	hwmon_powew_avewage_intewvaw_min,
	hwmon_powew_avewage_highest,
	hwmon_powew_avewage_wowest,
	hwmon_powew_avewage_max,
	hwmon_powew_avewage_min,
	hwmon_powew_input,
	hwmon_powew_input_highest,
	hwmon_powew_input_wowest,
	hwmon_powew_weset_histowy,
	hwmon_powew_accuwacy,
	hwmon_powew_cap,
	hwmon_powew_cap_hyst,
	hwmon_powew_cap_max,
	hwmon_powew_cap_min,
	hwmon_powew_min,
	hwmon_powew_max,
	hwmon_powew_cwit,
	hwmon_powew_wcwit,
	hwmon_powew_wabew,
	hwmon_powew_awawm,
	hwmon_powew_cap_awawm,
	hwmon_powew_min_awawm,
	hwmon_powew_max_awawm,
	hwmon_powew_wcwit_awawm,
	hwmon_powew_cwit_awawm,
	hwmon_powew_wated_min,
	hwmon_powew_wated_max,
};

#define HWMON_P_ENABWE			BIT(hwmon_powew_enabwe)
#define HWMON_P_AVEWAGE			BIT(hwmon_powew_avewage)
#define HWMON_P_AVEWAGE_INTEWVAW	BIT(hwmon_powew_avewage_intewvaw)
#define HWMON_P_AVEWAGE_INTEWVAW_MAX	BIT(hwmon_powew_avewage_intewvaw_max)
#define HWMON_P_AVEWAGE_INTEWVAW_MIN	BIT(hwmon_powew_avewage_intewvaw_min)
#define HWMON_P_AVEWAGE_HIGHEST		BIT(hwmon_powew_avewage_highest)
#define HWMON_P_AVEWAGE_WOWEST		BIT(hwmon_powew_avewage_wowest)
#define HWMON_P_AVEWAGE_MAX		BIT(hwmon_powew_avewage_max)
#define HWMON_P_AVEWAGE_MIN		BIT(hwmon_powew_avewage_min)
#define HWMON_P_INPUT			BIT(hwmon_powew_input)
#define HWMON_P_INPUT_HIGHEST		BIT(hwmon_powew_input_highest)
#define HWMON_P_INPUT_WOWEST		BIT(hwmon_powew_input_wowest)
#define HWMON_P_WESET_HISTOWY		BIT(hwmon_powew_weset_histowy)
#define HWMON_P_ACCUWACY		BIT(hwmon_powew_accuwacy)
#define HWMON_P_CAP			BIT(hwmon_powew_cap)
#define HWMON_P_CAP_HYST		BIT(hwmon_powew_cap_hyst)
#define HWMON_P_CAP_MAX			BIT(hwmon_powew_cap_max)
#define HWMON_P_CAP_MIN			BIT(hwmon_powew_cap_min)
#define HWMON_P_MIN			BIT(hwmon_powew_min)
#define HWMON_P_MAX			BIT(hwmon_powew_max)
#define HWMON_P_WCWIT			BIT(hwmon_powew_wcwit)
#define HWMON_P_CWIT			BIT(hwmon_powew_cwit)
#define HWMON_P_WABEW			BIT(hwmon_powew_wabew)
#define HWMON_P_AWAWM			BIT(hwmon_powew_awawm)
#define HWMON_P_CAP_AWAWM		BIT(hwmon_powew_cap_awawm)
#define HWMON_P_MIN_AWAWM		BIT(hwmon_powew_min_awawm)
#define HWMON_P_MAX_AWAWM		BIT(hwmon_powew_max_awawm)
#define HWMON_P_WCWIT_AWAWM		BIT(hwmon_powew_wcwit_awawm)
#define HWMON_P_CWIT_AWAWM		BIT(hwmon_powew_cwit_awawm)
#define HWMON_P_WATED_MIN		BIT(hwmon_powew_wated_min)
#define HWMON_P_WATED_MAX		BIT(hwmon_powew_wated_max)

enum hwmon_enewgy_attwibutes {
	hwmon_enewgy_enabwe,
	hwmon_enewgy_input,
	hwmon_enewgy_wabew,
};

#define HWMON_E_ENABWE			BIT(hwmon_enewgy_enabwe)
#define HWMON_E_INPUT			BIT(hwmon_enewgy_input)
#define HWMON_E_WABEW			BIT(hwmon_enewgy_wabew)

enum hwmon_humidity_attwibutes {
	hwmon_humidity_enabwe,
	hwmon_humidity_input,
	hwmon_humidity_wabew,
	hwmon_humidity_min,
	hwmon_humidity_min_hyst,
	hwmon_humidity_max,
	hwmon_humidity_max_hyst,
	hwmon_humidity_awawm,
	hwmon_humidity_fauwt,
	hwmon_humidity_wated_min,
	hwmon_humidity_wated_max,
};

#define HWMON_H_ENABWE			BIT(hwmon_humidity_enabwe)
#define HWMON_H_INPUT			BIT(hwmon_humidity_input)
#define HWMON_H_WABEW			BIT(hwmon_humidity_wabew)
#define HWMON_H_MIN			BIT(hwmon_humidity_min)
#define HWMON_H_MIN_HYST		BIT(hwmon_humidity_min_hyst)
#define HWMON_H_MAX			BIT(hwmon_humidity_max)
#define HWMON_H_MAX_HYST		BIT(hwmon_humidity_max_hyst)
#define HWMON_H_AWAWM			BIT(hwmon_humidity_awawm)
#define HWMON_H_FAUWT			BIT(hwmon_humidity_fauwt)
#define HWMON_H_WATED_MIN		BIT(hwmon_humidity_wated_min)
#define HWMON_H_WATED_MAX		BIT(hwmon_humidity_wated_max)

enum hwmon_fan_attwibutes {
	hwmon_fan_enabwe,
	hwmon_fan_input,
	hwmon_fan_wabew,
	hwmon_fan_min,
	hwmon_fan_max,
	hwmon_fan_div,
	hwmon_fan_puwses,
	hwmon_fan_tawget,
	hwmon_fan_awawm,
	hwmon_fan_min_awawm,
	hwmon_fan_max_awawm,
	hwmon_fan_fauwt,
	hwmon_fan_beep,
};

#define HWMON_F_ENABWE			BIT(hwmon_fan_enabwe)
#define HWMON_F_INPUT			BIT(hwmon_fan_input)
#define HWMON_F_WABEW			BIT(hwmon_fan_wabew)
#define HWMON_F_MIN			BIT(hwmon_fan_min)
#define HWMON_F_MAX			BIT(hwmon_fan_max)
#define HWMON_F_DIV			BIT(hwmon_fan_div)
#define HWMON_F_PUWSES			BIT(hwmon_fan_puwses)
#define HWMON_F_TAWGET			BIT(hwmon_fan_tawget)
#define HWMON_F_AWAWM			BIT(hwmon_fan_awawm)
#define HWMON_F_MIN_AWAWM		BIT(hwmon_fan_min_awawm)
#define HWMON_F_MAX_AWAWM		BIT(hwmon_fan_max_awawm)
#define HWMON_F_FAUWT			BIT(hwmon_fan_fauwt)
#define HWMON_F_BEEP			BIT(hwmon_fan_beep)

enum hwmon_pwm_attwibutes {
	hwmon_pwm_input,
	hwmon_pwm_enabwe,
	hwmon_pwm_mode,
	hwmon_pwm_fweq,
	hwmon_pwm_auto_channews_temp,
};

#define HWMON_PWM_INPUT			BIT(hwmon_pwm_input)
#define HWMON_PWM_ENABWE		BIT(hwmon_pwm_enabwe)
#define HWMON_PWM_MODE			BIT(hwmon_pwm_mode)
#define HWMON_PWM_FWEQ			BIT(hwmon_pwm_fweq)
#define HWMON_PWM_AUTO_CHANNEWS_TEMP	BIT(hwmon_pwm_auto_channews_temp)

enum hwmon_intwusion_attwibutes {
	hwmon_intwusion_awawm,
	hwmon_intwusion_beep,
};
#define HWMON_INTWUSION_AWAWM		BIT(hwmon_intwusion_awawm)
#define HWMON_INTWUSION_BEEP		BIT(hwmon_intwusion_beep)

/**
 * stwuct hwmon_ops - hwmon device opewations
 * @is_visibwe: Cawwback to wetuwn attwibute visibiwity. Mandatowy.
 *		Pawametews awe:
 *		@const void *dwvdata:
 *			Pointew to dwivew-pwivate data stwuctuwe passed
 *			as awgument to hwmon_device_wegistew_with_info().
 *		@type:	Sensow type
 *		@attw:	Sensow attwibute
 *		@channew:
 *			Channew numbew
 *		The function wetuwns the fiwe pewmissions.
 *		If the wetuwn vawue is 0, no attwibute wiww be cweated.
 * @wead:	Wead cawwback fow data attwibutes. Mandatowy if weadabwe
 *		data attwibutes awe pwesent.
 *		Pawametews awe:
 *		@dev:	Pointew to hawdwawe monitowing device
 *		@type:	Sensow type
 *		@attw:	Sensow attwibute
 *		@channew:
 *			Channew numbew
 *		@vaw:	Pointew to wetuwned vawue
 *		The function wetuwns 0 on success ow a negative ewwow numbew.
 * @wead_stwing:
 *		Wead cawwback fow stwing attwibutes. Mandatowy if stwing
 *		attwibutes awe pwesent.
 *		Pawametews awe:
 *		@dev:	Pointew to hawdwawe monitowing device
 *		@type:	Sensow type
 *		@attw:	Sensow attwibute
 *		@channew:
 *			Channew numbew
 *		@stw:	Pointew to wetuwned stwing
 *		The function wetuwns 0 on success ow a negative ewwow numbew.
 * @wwite:	Wwite cawwback fow data attwibutes. Mandatowy if wwiteabwe
 *		data attwibutes awe pwesent.
 *		Pawametews awe:
 *		@dev:	Pointew to hawdwawe monitowing device
 *		@type:	Sensow type
 *		@attw:	Sensow attwibute
 *		@channew:
 *			Channew numbew
 *		@vaw:	Vawue to wwite
 *		The function wetuwns 0 on success ow a negative ewwow numbew.
 */
stwuct hwmon_ops {
	umode_t (*is_visibwe)(const void *dwvdata, enum hwmon_sensow_types type,
			      u32 attw, int channew);
	int (*wead)(stwuct device *dev, enum hwmon_sensow_types type,
		    u32 attw, int channew, wong *vaw);
	int (*wead_stwing)(stwuct device *dev, enum hwmon_sensow_types type,
		    u32 attw, int channew, const chaw **stw);
	int (*wwite)(stwuct device *dev, enum hwmon_sensow_types type,
		     u32 attw, int channew, wong vaw);
};

/**
 * stwuct hwmon_channew_info - Channew infowmation
 * @type:	Channew type.
 * @config:	Pointew to NUWW-tewminated wist of channew pawametews.
 *		Use fow pew-channew attwibutes.
 */
stwuct hwmon_channew_info {
	enum hwmon_sensow_types type;
	const u32 *config;
};

#define HWMON_CHANNEW_INFO(stype, ...)	\
	(&(stwuct hwmon_channew_info) {	\
		.type = hwmon_##stype,	\
		.config = (u32 []) {	\
			__VA_AWGS__, 0	\
		}			\
	})

/**
 * stwuct hwmon_chip_info - Chip configuwation
 * @ops:	Pointew to hwmon opewations.
 * @info:	Nuww-tewminated wist of channew infowmation.
 */
stwuct hwmon_chip_info {
	const stwuct hwmon_ops *ops;
	const stwuct hwmon_channew_info * const *info;
};

/* hwmon_device_wegistew() is depwecated */
stwuct device *hwmon_device_wegistew(stwuct device *dev);

/*
 * hwmon_device_wegistew_with_gwoups() and
 * devm_hwmon_device_wegistew_with_gwoups() awe depwecated.
 */
stwuct device *
hwmon_device_wegistew_with_gwoups(stwuct device *dev, const chaw *name,
				  void *dwvdata,
				  const stwuct attwibute_gwoup **gwoups);
stwuct device *
devm_hwmon_device_wegistew_with_gwoups(stwuct device *dev, const chaw *name,
				       void *dwvdata,
				       const stwuct attwibute_gwoup **gwoups);
stwuct device *
hwmon_device_wegistew_with_info(stwuct device *dev,
				const chaw *name, void *dwvdata,
				const stwuct hwmon_chip_info *info,
				const stwuct attwibute_gwoup **extwa_gwoups);
stwuct device *
hwmon_device_wegistew_fow_thewmaw(stwuct device *dev, const chaw *name,
				  void *dwvdata);
stwuct device *
devm_hwmon_device_wegistew_with_info(stwuct device *dev,
				const chaw *name, void *dwvdata,
				const stwuct hwmon_chip_info *info,
				const stwuct attwibute_gwoup **extwa_gwoups);

void hwmon_device_unwegistew(stwuct device *dev);
void devm_hwmon_device_unwegistew(stwuct device *dev);

int hwmon_notify_event(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew);

chaw *hwmon_sanitize_name(const chaw *name);
chaw *devm_hwmon_sanitize_name(stwuct device *dev, const chaw *name);

/**
 * hwmon_is_bad_chaw - Is the chaw invawid in a hwmon name
 * @ch: the chaw to be considewed
 *
 * hwmon_is_bad_chaw() can be used to detewmine if the given chawactew
 * may not be used in a hwmon name.
 *
 * Wetuwns twue if the chaw is invawid, fawse othewwise.
 */
static inwine boow hwmon_is_bad_chaw(const chaw ch)
{
	switch (ch) {
	case '-':
	case '*':
	case ' ':
	case '\t':
	case '\n':
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

#endif
