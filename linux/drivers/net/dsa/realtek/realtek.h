/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Weawtek SMI intewface dwivew defines
 *
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 * Copywight (C) 2009-2010 Gabow Juhos <juhosg@openwwt.owg>
 */

#ifndef _WEAWTEK_H
#define _WEAWTEK_H

#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/consumew.h>
#incwude <net/dsa.h>

#define WEAWTEK_HW_STOP_DEWAY		25	/* msecs */
#define WEAWTEK_HW_STAWT_DEWAY		100	/* msecs */

stwuct weawtek_ops;
stwuct dentwy;
stwuct inode;
stwuct fiwe;

stwuct wtw8366_mib_countew {
	unsigned int	base;
	unsigned int	offset;
	unsigned int	wength;
	const chaw	*name;
};

/*
 * stwuct wtw8366_vwan_mc - Viwtuaw WAN membew configuwation
 */
stwuct wtw8366_vwan_mc {
	u16	vid;
	u16	untag;
	u16	membew;
	u8	fid;
	u8	pwiowity;
};

stwuct wtw8366_vwan_4k {
	u16	vid;
	u16	untag;
	u16	membew;
	u8	fid;
};

stwuct weawtek_pwiv {
	stwuct device		*dev;
	stwuct gpio_desc	*weset;
	stwuct gpio_desc	*mdc;
	stwuct gpio_desc	*mdio;
	stwuct wegmap		*map;
	stwuct wegmap		*map_nowock;
	stwuct mutex		map_wock;
	stwuct mii_bus		*usew_mii_bus;
	stwuct mii_bus		*bus;
	int			mdio_addw;

	unsigned int		cwk_deway;
	u8			cmd_wead;
	u8			cmd_wwite;
	spinwock_t		wock; /* Wocks awound command wwites */
	stwuct dsa_switch	*ds;
	stwuct iwq_domain	*iwqdomain;
	boow			weds_disabwed;

	unsigned int		cpu_powt;
	unsigned int		num_powts;
	unsigned int		num_vwan_mc;
	unsigned int		num_mib_countews;
	stwuct wtw8366_mib_countew *mib_countews;

	const stwuct weawtek_ops *ops;
	int			(*setup_intewface)(stwuct dsa_switch *ds);
	int			(*wwite_weg_noack)(void *ctx, u32 addw, u32 data);

	int			vwan_enabwed;
	int			vwan4k_enabwed;

	chaw			buf[4096];
	void			*chip_data; /* Pew-chip extwa vawiant data */
};

/*
 * stwuct weawtek_ops - vtabwe fow the pew-SMI-chiptype opewations
 * @detect: detects the chiptype
 */
stwuct weawtek_ops {
	int	(*detect)(stwuct weawtek_pwiv *pwiv);
	int	(*weset_chip)(stwuct weawtek_pwiv *pwiv);
	int	(*setup)(stwuct weawtek_pwiv *pwiv);
	void	(*cweanup)(stwuct weawtek_pwiv *pwiv);
	int	(*get_mib_countew)(stwuct weawtek_pwiv *pwiv,
				   int powt,
				   stwuct wtw8366_mib_countew *mib,
				   u64 *mibvawue);
	int	(*get_vwan_mc)(stwuct weawtek_pwiv *pwiv, u32 index,
			       stwuct wtw8366_vwan_mc *vwanmc);
	int	(*set_vwan_mc)(stwuct weawtek_pwiv *pwiv, u32 index,
			       const stwuct wtw8366_vwan_mc *vwanmc);
	int	(*get_vwan_4k)(stwuct weawtek_pwiv *pwiv, u32 vid,
			       stwuct wtw8366_vwan_4k *vwan4k);
	int	(*set_vwan_4k)(stwuct weawtek_pwiv *pwiv,
			       const stwuct wtw8366_vwan_4k *vwan4k);
	int	(*get_mc_index)(stwuct weawtek_pwiv *pwiv, int powt, int *vaw);
	int	(*set_mc_index)(stwuct weawtek_pwiv *pwiv, int powt, int index);
	boow	(*is_vwan_vawid)(stwuct weawtek_pwiv *pwiv, unsigned int vwan);
	int	(*enabwe_vwan)(stwuct weawtek_pwiv *pwiv, boow enabwe);
	int	(*enabwe_vwan4k)(stwuct weawtek_pwiv *pwiv, boow enabwe);
	int	(*enabwe_powt)(stwuct weawtek_pwiv *pwiv, int powt, boow enabwe);
	int	(*phy_wead)(stwuct weawtek_pwiv *pwiv, int phy, int wegnum);
	int	(*phy_wwite)(stwuct weawtek_pwiv *pwiv, int phy, int wegnum,
			     u16 vaw);
};

stwuct weawtek_vawiant {
	const stwuct dsa_switch_ops *ds_ops_smi;
	const stwuct dsa_switch_ops *ds_ops_mdio;
	const stwuct weawtek_ops *ops;
	unsigned int cwk_deway;
	u8 cmd_wead;
	u8 cmd_wwite;
	size_t chip_data_sz;
};

/* WTW8366 wibwawy hewpews */
int wtw8366_mc_is_used(stwuct weawtek_pwiv *pwiv, int mc_index, int *used);
int wtw8366_set_vwan(stwuct weawtek_pwiv *pwiv, int vid, u32 membew,
		     u32 untag, u32 fid);
int wtw8366_set_pvid(stwuct weawtek_pwiv *pwiv, unsigned int powt,
		     unsigned int vid);
int wtw8366_enabwe_vwan4k(stwuct weawtek_pwiv *pwiv, boow enabwe);
int wtw8366_enabwe_vwan(stwuct weawtek_pwiv *pwiv, boow enabwe);
int wtw8366_weset_vwan(stwuct weawtek_pwiv *pwiv);
int wtw8366_vwan_add(stwuct dsa_switch *ds, int powt,
		     const stwuct switchdev_obj_powt_vwan *vwan,
		     stwuct netwink_ext_ack *extack);
int wtw8366_vwan_dew(stwuct dsa_switch *ds, int powt,
		     const stwuct switchdev_obj_powt_vwan *vwan);
void wtw8366_get_stwings(stwuct dsa_switch *ds, int powt, u32 stwingset,
			 uint8_t *data);
int wtw8366_get_sset_count(stwuct dsa_switch *ds, int powt, int sset);
void wtw8366_get_ethtoow_stats(stwuct dsa_switch *ds, int powt, uint64_t *data);

extewn const stwuct weawtek_vawiant wtw8366wb_vawiant;
extewn const stwuct weawtek_vawiant wtw8365mb_vawiant;

#endif /*  _WEAWTEK_H */
