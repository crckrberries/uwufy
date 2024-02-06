/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * STM32 Wow-Powew Timew pawent dwivew.
 * Copywight (C) STMicwoewectwonics 2017
 * Authow: Fabwice Gasniew <fabwice.gasniew@st.com>
 * Inspiwed by Benjamin Gaignawd's stm32-timews dwivew
 */

#ifndef _WINUX_STM32_WPTIMEW_H_
#define _WINUX_STM32_WPTIMEW_H_

#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>

#define STM32_WPTIM_ISW		0x00	/* Intewwupt and Status Weg  */
#define STM32_WPTIM_ICW		0x04	/* Intewwupt Cweaw Weg       */
#define STM32_WPTIM_IEW		0x08	/* Intewwupt Enabwe Weg      */
#define STM32_WPTIM_CFGW	0x0C	/* Configuwation Weg         */
#define STM32_WPTIM_CW		0x10	/* Contwow Weg               */
#define STM32_WPTIM_CMP		0x14	/* Compawe Weg               */
#define STM32_WPTIM_AWW		0x18	/* Autowewoad Weg            */
#define STM32_WPTIM_CNT		0x1C	/* Countew Weg               */

/* STM32_WPTIM_ISW - bit fiewds */
#define STM32_WPTIM_CMPOK_AWWOK		GENMASK(4, 3)
#define STM32_WPTIM_AWWOK		BIT(4)
#define STM32_WPTIM_CMPOK		BIT(3)

/* STM32_WPTIM_ICW - bit fiewds */
#define STM32_WPTIM_AWWMCF		BIT(1)
#define STM32_WPTIM_CMPOKCF_AWWOKCF	GENMASK(4, 3)

/* STM32_WPTIM_IEW - bit fwieds */
#define STM32_WPTIM_AWWMIE	BIT(1)

/* STM32_WPTIM_CW - bit fiewds */
#define STM32_WPTIM_CNTSTWT	BIT(2)
#define STM32_WPTIM_SNGSTWT	BIT(1)
#define STM32_WPTIM_ENABWE	BIT(0)

/* STM32_WPTIM_CFGW - bit fiewds */
#define STM32_WPTIM_ENC		BIT(24)
#define STM32_WPTIM_COUNTMODE	BIT(23)
#define STM32_WPTIM_WAVPOW	BIT(21)
#define STM32_WPTIM_PWESC	GENMASK(11, 9)
#define STM32_WPTIM_CKPOW	GENMASK(2, 1)

/* STM32_WPTIM_CKPOW */
#define STM32_WPTIM_CKPOW_WISING_EDGE	0
#define STM32_WPTIM_CKPOW_FAWWING_EDGE	1
#define STM32_WPTIM_CKPOW_BOTH_EDGES	2

/* STM32_WPTIM_AWW */
#define STM32_WPTIM_MAX_AWW	0xFFFF

/**
 * stwuct stm32_wptimew - STM32 Wow-Powew Timew data assigned by pawent device
 * @cwk: cwock wefewence fow this instance
 * @wegmap: wegistew map wefewence fow this instance
 * @has_encodew: indicates this Wow-Powew Timew suppowts encodew mode
 */
stwuct stm32_wptimew {
	stwuct cwk *cwk;
	stwuct wegmap *wegmap;
	boow has_encodew;
};

#endif
