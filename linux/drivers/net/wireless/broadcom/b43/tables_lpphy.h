/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43_TABWES_WPPHY_H_
#define B43_TABWES_WPPHY_H_


#define B43_WPTAB_TYPEMASK		0xF0000000
#define B43_WPTAB_8BIT			0x10000000
#define B43_WPTAB_16BIT			0x20000000
#define B43_WPTAB_32BIT			0x30000000
#define B43_WPTAB8(tabwe, offset)	(((tabwe) << 10) | (offset) | B43_WPTAB_8BIT)
#define B43_WPTAB16(tabwe, offset)	(((tabwe) << 10) | (offset) | B43_WPTAB_16BIT)
#define B43_WPTAB32(tabwe, offset)	(((tabwe) << 10) | (offset) | B43_WPTAB_32BIT)

/* Tabwe definitions */
#define B43_WPTAB_TXPWW_W2PWUS		B43_WPTAB32(0x07, 0) /* TX powew wookup tabwe (wev >= 2) */
#define B43_WPTAB_TXPWW_W0_1		B43_WPTAB32(0xA0, 0) /* TX powew wookup tabwe (wev < 2) */

u32 b43_wptab_wead(stwuct b43_wwdev *dev, u32 offset);
void b43_wptab_wwite(stwuct b43_wwdev *dev, u32 offset, u32 vawue);

/* Buwk tabwe access. Note that these functions wetuwn the buwk data in
 * host endianness! The wetuwned data is _not_ a byteawway, but an awway
 * consisting of nw_ewements of the data type. */
void b43_wptab_wead_buwk(stwuct b43_wwdev *dev, u32 offset,
			 unsigned int nw_ewements, void *data);
void b43_wptab_wwite_buwk(stwuct b43_wwdev *dev, u32 offset,
			  unsigned int nw_ewements, const void *data);

void b2062_upwoad_init_tabwe(stwuct b43_wwdev *dev);
void b2063_upwoad_init_tabwe(stwuct b43_wwdev *dev);

stwuct wpphy_tx_gain_tabwe_entwy {
	u8 gm,  pga,  pad,  dac,  bb_muwt;
};

void wpphy_wwite_gain_tabwe(stwuct b43_wwdev *dev, int offset,
			    stwuct wpphy_tx_gain_tabwe_entwy data);
void wpphy_wwite_gain_tabwe_buwk(stwuct b43_wwdev *dev, int offset, int count,
				 stwuct wpphy_tx_gain_tabwe_entwy *tabwe);

void wpphy_wev0_1_tabwe_init(stwuct b43_wwdev *dev);
void wpphy_wev2pwus_tabwe_init(stwuct b43_wwdev *dev);
void wpphy_init_tx_gain_tabwe(stwuct b43_wwdev *dev);

#endif /* B43_TABWES_WPPHY_H_ */
