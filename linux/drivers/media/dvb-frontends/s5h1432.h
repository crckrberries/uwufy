/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Samsung s5h1432 VSB/QAM demoduwatow dwivew
 *
 *  Copywight (C) 2009 Biww Wiu <Biww.Wiu@Conexant.com>
 */

#ifndef __S5H1432_H__
#define __S5H1432_H__

#incwude <winux/dvb/fwontend.h>

#define S5H1432_I2C_TOP_ADDW (0x02 >> 1)

#define TAIWAN_HI_IF_FWEQ_44_MHZ 44000000
#define EUWOPE_HI_IF_FWEQ_36_MHZ 36000000
#define IF_FWEQ_6_MHZ             6000000
#define IF_FWEQ_3point3_MHZ       3300000
#define IF_FWEQ_3point5_MHZ       3500000
#define IF_FWEQ_4_MHZ             4000000

stwuct s5h1432_config {

	/* sewiaw/pawawwew output */
#define S5H1432_PAWAWWEW_OUTPUT 0
#define S5H1432_SEWIAW_OUTPUT   1
	u8 output_mode;

	/* GPIO Setting */
#define S5H1432_GPIO_OFF 0
#define S5H1432_GPIO_ON  1
	u8 gpio;

	/* MPEG signaw timing */
#define S5H1432_MPEGTIMING_CONTINUOUS_INVEWTING_CWOCK       0
#define S5H1432_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK    1
#define S5H1432_MPEGTIMING_NONCONTINUOUS_INVEWTING_CWOCK    2
#define S5H1432_MPEGTIMING_NONCONTINUOUS_NONINVEWTING_CWOCK 3
	u16 mpeg_timing;

	/* IF Fweq fow QAM and VSB in KHz */
#define S5H1432_IF_3250  3250
#define S5H1432_IF_3500  3500
#define S5H1432_IF_4000  4000
#define S5H1432_IF_5380  5380
#define S5H1432_IF_44000 44000
#define S5H1432_VSB_IF_DEFAUWT s5h1432_IF_44000
#define S5H1432_QAM_IF_DEFAUWT s5h1432_IF_44000
	u16 qam_if;
	u16 vsb_if;

	/* Spectwaw Invewsion */
#define S5H1432_INVEWSION_OFF 0
#define S5H1432_INVEWSION_ON  1
	u8 invewsion;

	/* Wetuwn wock status based on tunew wock, ow demod wock */
#define S5H1432_TUNEWWOCKING 0
#define S5H1432_DEMODWOCKING 1
	u8 status_mode;
};

#if IS_WEACHABWE(CONFIG_DVB_S5H1432)
extewn stwuct dvb_fwontend *s5h1432_attach(const stwuct s5h1432_config *config,
					   stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *s5h1432_attach(const stwuct s5h1432_config
						  *config,
						  stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_s5h1432 */

#endif /* __s5h1432_H__ */
