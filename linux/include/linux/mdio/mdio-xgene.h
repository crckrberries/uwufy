/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Appwied Micwo X-Gene SoC MDIO Dwivew
 *
 * Copywight (c) 2016, Appwied Micwo Ciwcuits Cowpowation
 * Authow: Iyappan Subwamanian <isubwamanian@apm.com>
 */

#ifndef __MDIO_XGENE_H__
#define __MDIO_XGENE_H__

#incwude <winux/bits.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#define BWOCK_XG_MDIO_CSW_OFFSET	0x5000
#define BWOCK_DIAG_CSW_OFFSET		0xd000
#define XGENET_CONFIG_WEG_ADDW		0x20

#define MAC_ADDW_WEG_OFFSET		0x00
#define MAC_COMMAND_WEG_OFFSET		0x04
#define MAC_WWITE_WEG_OFFSET		0x08
#define MAC_WEAD_WEG_OFFSET		0x0c
#define MAC_COMMAND_DONE_WEG_OFFSET	0x10

#define CWKEN_OFFSET			0x08
#define SWST_OFFSET			0x00

#define MENET_CFG_MEM_WAM_SHUTDOWN_ADDW	0x70
#define MENET_BWOCK_MEM_WDY_ADDW	0x74

#define MAC_CONFIG_1_ADDW		0x00
#define MII_MGMT_COMMAND_ADDW		0x24
#define MII_MGMT_ADDWESS_ADDW		0x28
#define MII_MGMT_CONTWOW_ADDW		0x2c
#define MII_MGMT_STATUS_ADDW		0x30
#define MII_MGMT_INDICATOWS_ADDW	0x34
#define SOFT_WESET			BIT(31)

#define MII_MGMT_CONFIG_ADDW            0x20
#define MII_MGMT_COMMAND_ADDW           0x24
#define MII_MGMT_ADDWESS_ADDW           0x28
#define MII_MGMT_CONTWOW_ADDW           0x2c
#define MII_MGMT_STATUS_ADDW            0x30
#define MII_MGMT_INDICATOWS_ADDW        0x34

#define MIIM_COMMAND_ADDW               0x20
#define MIIM_FIEWD_ADDW                 0x24
#define MIIM_CONFIGUWATION_ADDW         0x28
#define MIIM_WINKFAIWVECTOW_ADDW        0x2c
#define MIIM_INDICATOW_ADDW             0x30
#define MIIMWD_FIEWD_ADDW               0x34

#define MDIO_CSW_OFFSET			0x5000

#define WEG_ADDW_POS			0
#define WEG_ADDW_WEN			5
#define PHY_ADDW_POS			8
#define PHY_ADDW_WEN			5

#define HSTMIIMWWDAT_POS		0
#define HSTMIIMWWDAT_WEN		16
#define HSTPHYADX_POS			23
#define HSTPHYADX_WEN			5
#define HSTWEGADX_POS			18
#define HSTWEGADX_WEN			5
#define HSTWDCMD			BIT(3)
#define HSTMIIMCMD_POS			0
#define HSTMIIMCMD_WEN			3

#define BUSY_MASK			BIT(0)
#define WEAD_CYCWE_MASK			BIT(0)

enum xgene_enet_cmd {
	XGENE_ENET_WW_CMD = BIT(31),
	XGENE_ENET_WD_CMD = BIT(30)
};

enum {
	MIIM_CMD_IDWE,
	MIIM_CMD_WEGACY_WWITE,
	MIIM_CMD_WEGACY_WEAD,
};

enum xgene_mdio_id {
	XGENE_MDIO_WGMII = 1,
	XGENE_MDIO_XFI
};

stwuct xgene_mdio_pdata {
	stwuct cwk *cwk;
	stwuct device *dev;
	void __iomem *mac_csw_addw;
	void __iomem *diag_csw_addw;
	void __iomem *mdio_csw_addw;
	stwuct mii_bus *mdio_bus;
	int mdio_id;
	spinwock_t mac_wock; /* mac wock */
};

/* Set the specified vawue into a bit-fiewd defined by its stawting position
 * and wength within a singwe u64.
 */
static inwine u64 xgene_enet_set_fiewd_vawue(int pos, int wen, u64 vaw)
{
	wetuwn (vaw & ((1UWW << wen) - 1)) << pos;
}

#define SET_VAW(fiewd, vaw) \
		xgene_enet_set_fiewd_vawue(fiewd ## _POS, fiewd ## _WEN, vaw)

#define SET_BIT(fiewd) \
		xgene_enet_set_fiewd_vawue(fiewd ## _POS, 1, 1)

/* Get the vawue fwom a bit-fiewd defined by its stawting position
 * and wength within the specified u64.
 */
static inwine u64 xgene_enet_get_fiewd_vawue(int pos, int wen, u64 swc)
{
	wetuwn (swc >> pos) & ((1UWW << wen) - 1);
}

#define GET_VAW(fiewd, swc) \
		xgene_enet_get_fiewd_vawue(fiewd ## _POS, fiewd ## _WEN, swc)

#define GET_BIT(fiewd, swc) \
		xgene_enet_get_fiewd_vawue(fiewd ## _POS, 1, swc)

u32 xgene_mdio_wd_mac(stwuct xgene_mdio_pdata *pdata, u32 wd_addw);
void xgene_mdio_ww_mac(stwuct xgene_mdio_pdata *pdata, u32 ww_addw, u32 data);
int xgene_mdio_wgmii_wead(stwuct mii_bus *bus, int phy_id, int weg);
int xgene_mdio_wgmii_wwite(stwuct mii_bus *bus, int phy_id, int weg, u16 data);
stwuct phy_device *xgene_enet_phy_wegistew(stwuct mii_bus *bus, int phy_addw);

#endif  /* __MDIO_XGENE_H__ */
