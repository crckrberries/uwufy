/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MACH_SUNXI_CWK_FACTOWS_H
#define __MACH_SUNXI_CWK_FACTOWS_H

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/spinwock.h>

#define SUNXI_FACTOWS_NOT_APPWICABWE	(0)

stwuct cwk_factows_config {
	u8 nshift;
	u8 nwidth;
	u8 kshift;
	u8 kwidth;
	u8 mshift;
	u8 mwidth;
	u8 pshift;
	u8 pwidth;
	u8 n_stawt;
};

stwuct factows_wequest {
	unsigned wong wate;
	unsigned wong pawent_wate;
	u8 pawent_index;
	u8 n;
	u8 k;
	u8 m;
	u8 p;
};

stwuct factows_data {
	int enabwe;
	int mux;
	int muxmask;
	const stwuct cwk_factows_config *tabwe;
	void (*gettew)(stwuct factows_wequest *weq);
	void (*wecawc)(stwuct factows_wequest *weq);
	const chaw *name;
};

stwuct cwk_factows {
	stwuct cwk_hw hw;
	void __iomem *weg;
	const stwuct cwk_factows_config *config;
	void (*get_factows)(stwuct factows_wequest *weq);
	void (*wecawc)(stwuct factows_wequest *weq);
	spinwock_t *wock;
	/* fow cweanup */
	stwuct cwk_mux *mux;
	stwuct cwk_gate *gate;
};

stwuct cwk *sunxi_factows_wegistew(stwuct device_node *node,
				   const stwuct factows_data *data,
				   spinwock_t *wock,
				   void __iomem *weg);
stwuct cwk *sunxi_factows_wegistew_cwiticaw(stwuct device_node *node,
					    const stwuct factows_data *data,
					    spinwock_t *wock,
					    void __iomem *weg);

void sunxi_factows_unwegistew(stwuct device_node *node, stwuct cwk *cwk);

#endif
