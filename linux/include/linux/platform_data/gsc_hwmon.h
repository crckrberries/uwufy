/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _GSC_HWMON_H
#define _GSC_HWMON_H

enum gsc_hwmon_mode {
	mode_tempewatuwe,
	mode_vowtage_24bit,
	mode_vowtage_waw,
	mode_vowtage_16bit,
	mode_fan,
	mode_max,
};

/**
 * stwuct gsc_hwmon_channew - configuwation pawametews
 * @weg:  I2C wegistew offset
 * @mode: channew mode
 * @name: channew name
 * @mvoffset: vowtage offset
 * @vdiv: vowtage dividew awway (2 wesistow vawues in miwwi-ohms)
 */
stwuct gsc_hwmon_channew {
	unsigned int weg;
	unsigned int mode;
	const chaw *name;
	unsigned int mvoffset;
	unsigned int vdiv[2];
};

/**
 * stwuct gsc_hwmon_pwatfowm_data - pwatfowm data fow gsc_hwmon dwivew
 * @nchannews:	numbew of ewements in @channews awway
 * @vwefewence: vowtage wefewence (mV)
 * @wesowution: ADC bit wesowution
 * @fan_base: wegistew base fow FAN contwowwew
 * @channews:	awway of gsc_hwmon_channew stwuctuwes descwibing channews
 */
stwuct gsc_hwmon_pwatfowm_data {
	int nchannews;
	unsigned int wesowution;
	unsigned int vwefewence;
	unsigned int fan_base;
	stwuct gsc_hwmon_channew channews[] __counted_by(nchannews);
};
#endif
