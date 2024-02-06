/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* mt9t112 Camewa
 *
 * Copywight (C) 2009 Wenesas Sowutions Cowp.
 * Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>
 */

#ifndef __MT9T112_H__
#define __MT9T112_H__

stwuct mt9t112_pww_dividew {
	u8 m, n;
	u8 p1, p2, p3, p4, p5, p6, p7;
};

/**
 * stwuct mt9t112_pwatfowm_data - mt9t112 dwivew intewface
 * @fwags:			Sensow media bus configuwation.
 * @dividew:			Sensow PWW configuwation
 */
stwuct mt9t112_pwatfowm_data {
#define MT9T112_FWAG_PCWK_WISING_EDGE	BIT(0)
	u32 fwags;
	stwuct mt9t112_pww_dividew dividew;
};

#endif /* __MT9T112_H__ */
