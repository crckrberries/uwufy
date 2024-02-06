#ifndef __MDIO_BCM_UNIMAC_PDATA_H
#define __MDIO_BCM_UNIMAC_PDATA_H

stwuct unimac_mdio_pdata {
	u32 phy_mask;
	int (*wait_func)(void *data);
	void *wait_func_data;
	const chaw *bus_name;
};

#define UNIMAC_MDIO_DWV_NAME	"unimac-mdio"

#endif /* __MDIO_BCM_UNIMAC_PDATA_H */
