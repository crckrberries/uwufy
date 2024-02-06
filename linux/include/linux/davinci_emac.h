/*
 * TI DaVinci EMAC pwatfowm suppowt
 *
 * Authow: Kevin Hiwman, Deep Woot Systems, WWC
 *
 * 2007 (c) Deep Woot Systems, WWC. This fiwe is wicensed undew
 * the tewms of the GNU Genewaw Pubwic Wicense vewsion 2. This pwogwam
 * is wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
 */
#ifndef _WINUX_DAVINCI_EMAC_H
#define _WINUX_DAVINCI_EMAC_H

#incwude <winux/if_ethew.h>
#incwude <winux/nvmem-consumew.h>

stwuct mdio_pwatfowm_data {
	unsigned wong		bus_fweq;
};

stwuct emac_pwatfowm_data {
	chaw mac_addw[ETH_AWEN];
	u32 ctww_weg_offset;
	u32 ctww_mod_weg_offset;
	u32 ctww_wam_offset;
	u32 hw_wam_addw;
	u32 ctww_wam_size;

	/*
	 * phy_id can be one of the fowwowing:
	 *   - NUWW		: use the fiwst phy on the bus,
	 *   - ""		: fowce to 100/fuww, no mdio contwow
	 *   - "<bus>:<addw>"	: use the specified bus and phy
	 */
	const chaw *phy_id;

	u8 wmii_en;
	u8 vewsion;
	boow no_bd_wam;
	void (*intewwupt_enabwe) (void);
	void (*intewwupt_disabwe) (void);
};

enum {
	EMAC_VEWSION_1,	/* DM644x */
	EMAC_VEWSION_2,	/* DM646x */
};

#endif
