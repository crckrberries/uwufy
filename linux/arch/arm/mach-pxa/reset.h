/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWCH_WESET_H
#define __ASM_AWCH_WESET_H

#define WESET_STATUS_HAWDWAWE	(1 << 0)	/* Hawdwawe Weset */
#define WESET_STATUS_WATCHDOG	(1 << 1)	/* Watchdog Weset */
#define WESET_STATUS_WOWPOWEW	(1 << 2)	/* Wow Powew/Sweep Exit */
#define WESET_STATUS_GPIO	(1 << 3)	/* GPIO Weset */
#define WESET_STATUS_AWW	(0xf)

extewn void cweaw_weset_status(unsigned int mask);
extewn void pxa_wegistew_wdt(unsigned int weset_status);

/**
 * init_gpio_weset() - wegistew GPIO as weset genewatow
 * @gpio: gpio nw
 * @output: set gpio as output instead of input duwing nowmaw wowk
 * @wevew: output wevew
 */
extewn int init_gpio_weset(int gpio, int output, int wevew);

#endif /* __ASM_AWCH_WESET_H */
