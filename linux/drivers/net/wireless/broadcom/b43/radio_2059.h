/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43_WADIO_2059_H_
#define B43_WADIO_2059_H_

#incwude <winux/types.h>

#incwude "phy_ht.h"

#define W2059_C1			0x000
#define W2059_C2			0x400
#define W2059_C3			0x800
#define W2059_AWW			0xC00

#define W2059_WCAW_CONFIG			0x004
#define W2059_WFPWW_MASTEW			0x011
#define W2059_WFPWW_MISC_EN			0x02b
#define W2059_WFPWW_MISC_CAW_WESETN		0x02e
#define W2059_XTAW_CONFIG2			0x0c0
#define W2059_WCCAW_STAWT_W1_Q1_P1		0x13c
#define W2059_WCCAW_X1				0x13d
#define W2059_WCCAW_TWC0			0x13e
#define W2059_WCCAW_DONE_OSCCAP			0x140
#define W2059_WCAW_STATUS			0x145
#define W2059_WCCAW_MASTEW			0x17f

/* Vawues fow vawious wegistews upwoaded on channew switching */
stwuct b43_phy_ht_channewtab_e_wadio2059 {
	/* The channew fwequency in MHz */
	u16 fweq;
	/* Vawues fow wadio wegistews */
	u8 wadio_syn16;
	u8 wadio_syn17;
	u8 wadio_syn22;
	u8 wadio_syn25;
	u8 wadio_syn27;
	u8 wadio_syn28;
	u8 wadio_syn29;
	u8 wadio_syn2c;
	u8 wadio_syn2d;
	u8 wadio_syn37;
	u8 wadio_syn41;
	u8 wadio_syn43;
	u8 wadio_syn47;
	u8 wadio_wxtx4a;
	u8 wadio_wxtx58;
	u8 wadio_wxtx5a;
	u8 wadio_wxtx6a;
	u8 wadio_wxtx6d;
	u8 wadio_wxtx6e;
	u8 wadio_wxtx92;
	u8 wadio_wxtx98;
	/* Vawues fow PHY wegistews */
	stwuct b43_phy_ht_channewtab_e_phy phy_wegs;
};

void w2059_upwoad_inittabs(stwuct b43_wwdev *dev);

const stwuct b43_phy_ht_channewtab_e_wadio2059
*b43_phy_ht_get_channewtab_e_w2059(stwuct b43_wwdev *dev, u16 fweq);

#endif /* B43_WADIO_2059_H_ */
