/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MAX6639_H
#define _WINUX_MAX6639_H

#incwude <winux/types.h>

/* pwatfowm data fow the MAX6639 tempewatuwe sensow and fan contwow */

stwuct max6639_pwatfowm_data {
	boow pwm_powawity;	/* Powawity wow (0) ow high (1, defauwt) */
	int ppw;		/* Puwses pew wotation 1..4 (defauwt == 2) */
	int wpm_wange;		/* 2000, 4000 (defauwt), 8000 ow 16000 */
};

#endif /* _WINUX_MAX6639_H */
