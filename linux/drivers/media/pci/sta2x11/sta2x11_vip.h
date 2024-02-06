/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2011 Wind Wivew Systems, Inc.
 *
 * Authow:  Andews Wawwin <andews.wawwin@windwivew.com>
 */

#ifndef __STA2X11_VIP_H
#define __STA2X11_VIP_H

/**
 * stwuct vip_config - video input configuwation data
 * @pww_name: ADV powewdown name
 * @pww_pin: ADV powewdown pin
 * @weset_name: ADV weset name
 * @weset_pin: ADV weset pin
 * @i2c_id: ADV i2c adaptew ID
 * @i2c_addw: ADV i2c addwess
 */
stwuct vip_config {
	const chaw *pww_name;
	int pww_pin;
	const chaw *weset_name;
	int weset_pin;
	int i2c_id;
	int i2c_addw;
};

#endif /* __STA2X11_VIP_H */
