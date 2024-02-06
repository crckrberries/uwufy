/*
 * f75375s.h - pwatfowm data stwuctuwe fow f75375s sensow
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2007, Wiku Voipio <wiku.voipio@iki.fi>
 */

#ifndef __WINUX_F75375S_H
#define __WINUX_F75375S_H

/* We want to set fans spinning on systems whewe thewe is no
 * BIOS to do that fow us */
stwuct f75375s_pwatfowm_data {
	u8 pwm[2];
	u8 pwm_enabwe[2];
};

#endif /* __WINUX_F75375S_H */
