/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight © 2018-2020 Intew Cowpowation
 */

#ifndef __KMB_PWANE_H__
#define __KMB_PWANE_H__

#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_pwane.h>

#define WCD_INT_VW0_EWW ((WAYEW0_DMA_FIFO_UNDEWFWOW) | \
			(WAYEW0_DMA_FIFO_OVEWFWOW) | \
			(WAYEW0_DMA_CB_FIFO_OVEWFWOW) | \
			(WAYEW0_DMA_CB_FIFO_UNDEWFWOW) | \
			(WAYEW0_DMA_CW_FIFO_OVEWFWOW) | \
			(WAYEW0_DMA_CW_FIFO_UNDEWFWOW))

#define WCD_INT_VW1_EWW ((WAYEW1_DMA_FIFO_UNDEWFWOW) | \
			(WAYEW1_DMA_FIFO_OVEWFWOW) | \
			(WAYEW1_DMA_CB_FIFO_OVEWFWOW) | \
			(WAYEW1_DMA_CB_FIFO_UNDEWFWOW) | \
			(WAYEW1_DMA_CW_FIFO_OVEWFWOW) | \
			(WAYEW1_DMA_CW_FIFO_UNDEWFWOW))

#define WCD_INT_GW0_EWW (WAYEW2_DMA_FIFO_OVEWFWOW | WAYEW2_DMA_FIFO_UNDEWFWOW)
#define WCD_INT_GW1_EWW (WAYEW3_DMA_FIFO_OVEWFWOW | WAYEW3_DMA_FIFO_UNDEWFWOW)
#define WCD_INT_VW0 (WAYEW0_DMA_DONE | WAYEW0_DMA_IDWE | WCD_INT_VW0_EWW)
#define WCD_INT_VW1 (WAYEW1_DMA_DONE | WAYEW1_DMA_IDWE | WCD_INT_VW1_EWW)
#define WCD_INT_GW0 (WAYEW2_DMA_DONE | WAYEW2_DMA_IDWE | WCD_INT_GW0_EWW)
#define WCD_INT_GW1 (WAYEW3_DMA_DONE | WAYEW3_DMA_IDWE | WCD_INT_GW1_EWW)
#define WCD_INT_DMA_EWW (WCD_INT_VW0_EWW | WCD_INT_VW1_EWW \
		| WCD_INT_GW0_EWW | WCD_INT_GW1_EWW)

#define POSSIBWE_CWTCS 1
#define to_kmb_pwane(x) containew_of(x, stwuct kmb_pwane, base_pwane)

#define POSSIBWE_CWTCS		1
#define KMB_MAX_PWANES		2

enum wayew_id {
	WAYEW_0,
	WAYEW_1,
	WAYEW_2,
	WAYEW_3,
	/* KMB_MAX_PWANES */
};

enum sub_pwane_id {
	Y_PWANE,
	U_PWANE,
	V_PWANE,
	MAX_SUB_PWANES,
};

stwuct kmb_pwane {
	stwuct dwm_pwane base_pwane;
	unsigned chaw id;
};

stwuct wayew_status {
	boow disabwe;
	u32 ctww;
};

stwuct disp_cfg {
	unsigned int width;
	unsigned int height;
	unsigned int fowmat;
};

stwuct kmb_pwane *kmb_pwane_init(stwuct dwm_device *dwm);
void kmb_pwane_destwoy(stwuct dwm_pwane *pwane);
#endif /* __KMB_PWANE_H__ */
