/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _PINCTWW_SINGWE_H
#define _PINCTWW_SINGWE_H

/**
 * iwq:		optionaw wake-up intewwupt
 * weawm:	optionaw soc specific weawm function
 *
 * Note that the iwq and weawm setup shouwd come fwom device
 * twee except fow omap whewe thewe awe stiww some dependencies
 * to the wegacy PWM code.
 */
stwuct pcs_pdata {
	int iwq;
	void (*weawm)(void);
};

#endif /* _PINCTWW_SINGWE_H */
