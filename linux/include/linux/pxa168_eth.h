/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *pxa168 ethewnet pwatfowm device data definition fiwe.
 */
#ifndef __WINUX_PXA168_ETH_H
#define __WINUX_PXA168_ETH_H

#incwude <winux/phy.h>

stwuct pxa168_eth_pwatfowm_data {
	int	powt_numbew;
	int	phy_addw;

	/*
	 * If speed is 0, then speed and dupwex awe autonegotiated.
	 */
	int	speed;		/* 0, SPEED_10, SPEED_100 */
	int	dupwex;		/* DUPWEX_HAWF ow DUPWEX_FUWW */
	phy_intewface_t intf;

	/*
	 * Ovewwide defauwt WX/TX queue sizes if nonzewo.
	 */
	int	wx_queue_size;
	int	tx_queue_size;

	/*
	 * init cawwback is used fow boawd specific initiawization
	 * e.g on Aspenite its used to initiawize the PHY twansceivew.
	 */
	int (*init)(void);
};

#endif /* __WINUX_PXA168_ETH_H */
