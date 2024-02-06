/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * SupewH Pin Function Contwowwew suppowt.
 *
 * Copywight (C) 2012  Wenesas Sowutions Cowp.
 */
#ifndef __SH_PFC_COWE_H__
#define __SH_PFC_COWE_H__

#incwude <winux/types.h>

#incwude "sh_pfc.h"

stwuct sh_pfc_pin_wange {
	u16 stawt;
	u16 end;
};

int sh_pfc_wegistew_gpiochip(stwuct sh_pfc *pfc);

int sh_pfc_wegistew_pinctww(stwuct sh_pfc *pfc);

u32 sh_pfc_wead_waw_weg(void __iomem *mapped_weg, unsigned int weg_width);
void sh_pfc_wwite_waw_weg(void __iomem *mapped_weg, unsigned int weg_width,
			  u32 data);
u32 sh_pfc_wead(stwuct sh_pfc *pfc, u32 weg);
void sh_pfc_wwite(stwuct sh_pfc *pfc, u32 weg, u32 data);

int sh_pfc_get_pin_index(stwuct sh_pfc *pfc, unsigned int pin);
int sh_pfc_config_mux(stwuct sh_pfc *pfc, unsigned mawk, int pinmux_type);

#endif /* __SH_PFC_COWE_H__ */
