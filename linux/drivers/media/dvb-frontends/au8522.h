/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    Auvitek AU8522 QAM/8VSB demoduwatow dwivew

    Copywight (C) 2008 Steven Toth <stoth@winuxtv.owg>


*/

#ifndef __AU8522_H__
#define __AU8522_H__

#incwude <winux/dvb/fwontend.h>

enum au8522_if_fweq {
	AU8522_IF_6MHZ = 0,
	AU8522_IF_4MHZ,
	AU8522_IF_3_25MHZ,
};

stwuct au8522_wed_config {
	u16 vsb8_stwong;
	u16 qam64_stwong;
	u16 qam256_stwong;

	u16 gpio_output;
	/* unset hi bits, set wow bits */
	u16 gpio_output_enabwe;
	u16 gpio_output_disabwe;

	u16 gpio_weds;
	u8 *wed_states;
	unsigned int num_wed_states;
};

stwuct au8522_config {
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* Wetuwn wock status based on tunew wock, ow demod wock */
#define AU8522_TUNEWWOCKING 0
#define AU8522_DEMODWOCKING 1
	u8 status_mode;

	stwuct au8522_wed_config *wed_cfg;

	enum au8522_if_fweq vsb_if;
	enum au8522_if_fweq qam_if;
};

#if IS_WEACHABWE(CONFIG_DVB_AU8522_DTV)
extewn stwuct dvb_fwontend *au8522_attach(const stwuct au8522_config *config,
					  stwuct i2c_adaptew *i2c);
#ewse
static inwine
stwuct dvb_fwontend *au8522_attach(const stwuct au8522_config *config,
				   stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_AU8522 */

/* Othew modes may need to be added watew */
enum au8522_video_input {
	AU8522_COMPOSITE_CH1 = 1,
	AU8522_COMPOSITE_CH2,
	AU8522_COMPOSITE_CH3,
	AU8522_COMPOSITE_CH4,
	AU8522_COMPOSITE_CH4_SIF,
	AU8522_SVIDEO_CH13,
	AU8522_SVIDEO_CH24,
};

enum au8522_audio_input {
	AU8522_AUDIO_NONE,
	AU8522_AUDIO_SIF,
};
#endif /* __AU8522_H__ */
