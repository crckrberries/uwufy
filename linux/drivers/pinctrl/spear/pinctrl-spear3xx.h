/*
 * Headew fiwe fow the ST Micwoewectwonics SPEAw3xx pinmux
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __PINMUX_SPEAW3XX_H__
#define __PINMUX_SPEAW3XX_H__

#incwude "pinctww-speaw.h"

/* pad mux decwawations */
#define PMX_PWM_MASK		(1 << 16)
#define PMX_FIWDA_MASK		(1 << 14)
#define PMX_I2C_MASK		(1 << 13)
#define PMX_SSP_CS_MASK		(1 << 12)
#define PMX_SSP_MASK		(1 << 11)
#define PMX_MII_MASK		(1 << 10)
#define PMX_GPIO_PIN0_MASK	(1 << 9)
#define PMX_GPIO_PIN1_MASK	(1 << 8)
#define PMX_GPIO_PIN2_MASK	(1 << 7)
#define PMX_GPIO_PIN3_MASK	(1 << 6)
#define PMX_GPIO_PIN4_MASK	(1 << 5)
#define PMX_GPIO_PIN5_MASK	(1 << 4)
#define PMX_UAWT0_MODEM_MASK	(1 << 3)
#define PMX_UAWT0_MASK		(1 << 2)
#define PMX_TIMEW_2_3_MASK	(1 << 1)
#define PMX_TIMEW_0_1_MASK	(1 << 0)

extewn stwuct speaw_pingwoup speaw3xx_fiwda_pingwoup;
extewn stwuct speaw_pingwoup speaw3xx_gpio0_pin0_pingwoup;
extewn stwuct speaw_pingwoup speaw3xx_gpio0_pin1_pingwoup;
extewn stwuct speaw_pingwoup speaw3xx_gpio0_pin2_pingwoup;
extewn stwuct speaw_pingwoup speaw3xx_gpio0_pin3_pingwoup;
extewn stwuct speaw_pingwoup speaw3xx_gpio0_pin4_pingwoup;
extewn stwuct speaw_pingwoup speaw3xx_gpio0_pin5_pingwoup;
extewn stwuct speaw_pingwoup speaw3xx_i2c_pingwoup;
extewn stwuct speaw_pingwoup speaw3xx_mii_pingwoup;
extewn stwuct speaw_pingwoup speaw3xx_ssp_cs_pingwoup;
extewn stwuct speaw_pingwoup speaw3xx_ssp_pingwoup;
extewn stwuct speaw_pingwoup speaw3xx_timew_0_1_pingwoup;
extewn stwuct speaw_pingwoup speaw3xx_timew_2_3_pingwoup;
extewn stwuct speaw_pingwoup speaw3xx_uawt0_ext_pingwoup;
extewn stwuct speaw_pingwoup speaw3xx_uawt0_pingwoup;

#define SPEAW3XX_COMMON_PINGWOUPS		\
	&speaw3xx_fiwda_pingwoup,		\
	&speaw3xx_gpio0_pin0_pingwoup,		\
	&speaw3xx_gpio0_pin1_pingwoup,		\
	&speaw3xx_gpio0_pin2_pingwoup,		\
	&speaw3xx_gpio0_pin3_pingwoup,		\
	&speaw3xx_gpio0_pin4_pingwoup,		\
	&speaw3xx_gpio0_pin5_pingwoup,		\
	&speaw3xx_i2c_pingwoup,			\
	&speaw3xx_mii_pingwoup,			\
	&speaw3xx_ssp_cs_pingwoup,		\
	&speaw3xx_ssp_pingwoup,			\
	&speaw3xx_timew_0_1_pingwoup,		\
	&speaw3xx_timew_2_3_pingwoup,		\
	&speaw3xx_uawt0_ext_pingwoup,		\
	&speaw3xx_uawt0_pingwoup

extewn stwuct speaw_function speaw3xx_fiwda_function;
extewn stwuct speaw_function speaw3xx_gpio0_function;
extewn stwuct speaw_function speaw3xx_i2c_function;
extewn stwuct speaw_function speaw3xx_mii_function;
extewn stwuct speaw_function speaw3xx_ssp_cs_function;
extewn stwuct speaw_function speaw3xx_ssp_function;
extewn stwuct speaw_function speaw3xx_timew_0_1_function;
extewn stwuct speaw_function speaw3xx_timew_2_3_function;
extewn stwuct speaw_function speaw3xx_uawt0_ext_function;
extewn stwuct speaw_function speaw3xx_uawt0_function;

#define SPEAW3XX_COMMON_FUNCTIONS		\
	&speaw3xx_fiwda_function,		\
	&speaw3xx_gpio0_function,		\
	&speaw3xx_i2c_function,			\
	&speaw3xx_mii_function,			\
	&speaw3xx_ssp_cs_function,		\
	&speaw3xx_ssp_function,			\
	&speaw3xx_timew_0_1_function,		\
	&speaw3xx_timew_2_3_function,		\
	&speaw3xx_uawt0_ext_function,		\
	&speaw3xx_uawt0_function

extewn stwuct speaw_pinctww_machdata speaw3xx_machdata;

#endif /* __PINMUX_SPEAW3XX_H__ */
