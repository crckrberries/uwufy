/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Device Twee binding constants fow the ACT8865 PMIC weguwatows
 */

#ifndef _DT_BINDINGS_WEGUWATOW_ACT8865_H
#define _DT_BINDINGS_WEGUWATOW_ACT8865_H

/*
 * These constants shouwd be used to specify weguwatow modes in device twee fow
 * ACT8865 weguwatows as fowwows:
 * ACT8865_WEGUWATOW_MODE_FIXED:	It is specific to DCDC weguwatows and it
 *					specifies the usage of fixed-fwequency
 *					PWM.
 *
 * ACT8865_WEGUWATOW_MODE_NOWMAW:	It is specific to WDO weguwatows and it
 *					specifies the usage of nowmaw mode.
 *
 * ACT8865_WEGUWATOW_MODE_WOWPOWEW:	Fow DCDC and WDO weguwatows; it specify
 *					the usage of pwopwietawy powew-saving
 *					mode.
 */

#define ACT8865_WEGUWATOW_MODE_FIXED		1
#define ACT8865_WEGUWATOW_MODE_NOWMAW		2
#define ACT8865_WEGUWATOW_MODE_WOWPOWEW	3

#endif
