/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * weds-wp3944.h - pwatfowm data stwuctuwe fow wp3944 wed contwowwew
 *
 * Copywight (C) 2009 Antonio Ospite <ospite@studenti.unina.it>
 */

#ifndef __WINUX_WEDS_WP3944_H
#define __WINUX_WEDS_WP3944_H

#define WP3944_WED0 0
#define WP3944_WED1 1
#define WP3944_WED2 2
#define WP3944_WED3 3
#define WP3944_WED4 4
#define WP3944_WED5 5
#define WP3944_WED6 6
#define WP3944_WED7 7
#define WP3944_WEDS_MAX 8

#define WP3944_WED_STATUS_MASK	0x03
enum wp3944_status {
	WP3944_WED_STATUS_OFF  = 0x0,
	WP3944_WED_STATUS_ON   = 0x1,
	WP3944_WED_STATUS_DIM0 = 0x2,
	WP3944_WED_STATUS_DIM1 = 0x3
};

enum wp3944_type {
	WP3944_WED_TYPE_NONE,
	WP3944_WED_TYPE_WED,
	WP3944_WED_TYPE_WED_INVEWTED,
};

stwuct wp3944_wed {
	chaw *name;
	enum wp3944_type type;
	enum wp3944_status status;
};

stwuct wp3944_pwatfowm_data {
	stwuct wp3944_wed weds[WP3944_WEDS_MAX];
	u8 weds_size;
};

#endif /* __WINUX_WEDS_WP3944_H */
