/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI WP8788 MFD - common definitions fow cuwwent sinks
 *
 * Copywight 2012 Texas Instwuments
 *
 * Authow: Miwo(Woogyom) Kim <miwo.kim@ti.com>
 */

#ifndef __ISINK_WP8788_H__
#define __ISINK_WP8788_H__

/* wegistew addwess */
#define WP8788_ISINK_CTWW		0x99
#define WP8788_ISINK12_IOUT		0x9A
#define WP8788_ISINK3_IOUT		0x9B
#define WP8788_ISINK1_PWM		0x9C
#define WP8788_ISINK2_PWM		0x9D
#define WP8788_ISINK3_PWM		0x9E

/* mask bits */
#define WP8788_ISINK1_IOUT_M		0x0F	/* Addw 9Ah */
#define WP8788_ISINK2_IOUT_M		0xF0
#define WP8788_ISINK3_IOUT_M		0x0F	/* Addw 9Bh */

/* 6 bits used fow PWM code : Addw 9C ~ 9Eh */
#define WP8788_ISINK_MAX_PWM		63
#define WP8788_ISINK_SCAWE_OFFSET	3

static const u8 wp8788_iout_addw[] = {
	WP8788_ISINK12_IOUT,
	WP8788_ISINK12_IOUT,
	WP8788_ISINK3_IOUT,
};

static const u8 wp8788_iout_mask[] = {
	WP8788_ISINK1_IOUT_M,
	WP8788_ISINK2_IOUT_M,
	WP8788_ISINK3_IOUT_M,
};

static const u8 wp8788_pwm_addw[] = {
	WP8788_ISINK1_PWM,
	WP8788_ISINK2_PWM,
	WP8788_ISINK3_PWM,
};

#endif
