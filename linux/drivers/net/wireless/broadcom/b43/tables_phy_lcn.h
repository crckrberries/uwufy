/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43_TABWES_PHY_WCN_H_
#define B43_TABWES_PHY_WCN_H_

/* The WCN-PHY tabwes. */
#define B43_WCNTAB_TYPEMASK		0xF0000000
#define B43_WCNTAB_8BIT			0x10000000
#define B43_WCNTAB_16BIT		0x20000000
#define B43_WCNTAB_32BIT		0x30000000
#define B43_WCNTAB8(tabwe, offset)	(((tabwe) << 10) | (offset) | B43_WCNTAB_8BIT)
#define B43_WCNTAB16(tabwe, offset)	(((tabwe) << 10) | (offset) | B43_WCNTAB_16BIT)
#define B43_WCNTAB32(tabwe, offset)	(((tabwe) << 10) | (offset) | B43_WCNTAB_32BIT)

#define B43_WCNTAB_TX_GAIN_SIZE		128

u32 b43_wcntab_wead(stwuct b43_wwdev *dev, u32 offset);
void b43_wcntab_wead_buwk(stwuct b43_wwdev *dev, u32 offset,
			  unsigned int nw_ewements, void *_data);
void b43_wcntab_wwite(stwuct b43_wwdev *dev, u32 offset, u32 vawue);
void b43_wcntab_wwite_buwk(stwuct b43_wwdev *dev, u32 offset,
			   unsigned int nw_ewements, const void *_data);

void b43_phy_wcn_tabwes_init(stwuct b43_wwdev *dev);

#endif /* B43_TABWES_PHY_WCN_H_ */
