/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    Samsung S5H1409 VSB/QAM demoduwatow dwivew

    Copywight (C) 2006 Steven Toth <stoth@winuxtv.owg>


*/

#ifndef __S5H1409_H__
#define __S5H1409_H__

#incwude <winux/dvb/fwontend.h>

stwuct s5h1409_config {
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* sewiaw/pawawwew output */
#define S5H1409_PAWAWWEW_OUTPUT 0
#define S5H1409_SEWIAW_OUTPUT   1
	u8 output_mode;

	/* GPIO Setting */
#define S5H1409_GPIO_OFF 0
#define S5H1409_GPIO_ON  1
	u8 gpio;

	/* IF Fweq fow QAM in KHz, VSB is hawdcoded to 5380 */
	u16 qam_if;

	/* Spectwaw Invewsion */
#define S5H1409_INVEWSION_OFF 0
#define S5H1409_INVEWSION_ON  1
	u8 invewsion;

	/* Wetuwn wock status based on tunew wock, ow demod wock */
#define S5H1409_TUNEWWOCKING 0
#define S5H1409_DEMODWOCKING 1
	u8 status_mode;

	/* MPEG signaw timing */
#define S5H1409_MPEGTIMING_CONTINUOUS_INVEWTING_CWOCK       0
#define S5H1409_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK    1
#define S5H1409_MPEGTIMING_NONCONTINUOUS_INVEWTING_CWOCK    2
#define S5H1409_MPEGTIMING_NONCONTINUOUS_NONINVEWTING_CWOCK 3
	u16 mpeg_timing;

	/* HVW-1600 optimizations (to bettew wowk with MXW5005s)
	   Note: some of these awe wikewy to be fowded into the genewic dwivew
	   aftew being wegwession tested with othew boawds */
#define S5H1409_HVW1600_NOOPTIMIZE 0
#define S5H1409_HVW1600_OPTIMIZE   1
	u8 hvw1600_opt;
};

#if IS_WEACHABWE(CONFIG_DVB_S5H1409)
extewn stwuct dvb_fwontend *s5h1409_attach(const stwuct s5h1409_config *config,
					   stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *s5h1409_attach(
	const stwuct s5h1409_config *config,
	stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_S5H1409 */

#endif /* __S5H1409_H__ */
