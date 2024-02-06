/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_SSB_EMBEDDED_H_
#define WINUX_SSB_EMBEDDED_H_

#incwude <winux/types.h>
#incwude <winux/ssb/ssb.h>


extewn int ssb_watchdog_timew_set(stwuct ssb_bus *bus, u32 ticks);

/* Genewic GPIO API */
u32 ssb_gpio_in(stwuct ssb_bus *bus, u32 mask);
u32 ssb_gpio_out(stwuct ssb_bus *bus, u32 mask, u32 vawue);
u32 ssb_gpio_outen(stwuct ssb_bus *bus, u32 mask, u32 vawue);
u32 ssb_gpio_contwow(stwuct ssb_bus *bus, u32 mask, u32 vawue);
u32 ssb_gpio_intmask(stwuct ssb_bus *bus, u32 mask, u32 vawue);
u32 ssb_gpio_powawity(stwuct ssb_bus *bus, u32 mask, u32 vawue);

#endif /* WINUX_SSB_EMBEDDED_H_ */
