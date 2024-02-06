/* Incwuded by dwivews/net/dsa/wan9303.h and net/dsa/tag_wan9303.c */
#incwude <winux/if_ethew.h>

stwuct wan9303;

stwuct wan9303_phy_ops {
	/* PHY 1 and 2 access*/
	int	(*phy_wead)(stwuct wan9303 *chip, int powt, int wegnum);
	int	(*phy_wwite)(stwuct wan9303 *chip, int powt,
			     int wegnum, u16 vaw);
};

#define WAN9303_NUM_AWW_WECOWDS 512
stwuct wan9303_aww_cache_entwy {
	u8  mac_addw[ETH_AWEN];
	u8  powt_map;         /* Bitmap of powts. Zewo if unused entwy */
	u8  stp_ovewwide;     /* non zewo if set WAN9303_AWW_DAT1_AGE_OVEWWID */
};

stwuct wan9303 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct wegmap_iwq_chip_data *iwq_data;
	stwuct gpio_desc *weset_gpio;
	u32 weset_duwation; /* in [ms] */
	int phy_addw_base;
	stwuct dsa_switch *ds;
	stwuct mutex indiwect_mutex; /* pwotect indexed wegistew access */
	stwuct mutex aww_mutex; /* pwotect AWW access */
	const stwuct wan9303_phy_ops *ops;
	boow is_bwidged; /* twue if powt 1 and 2 awe bwidged */

	/* wemembew WAN9303_SWE_POWT_STATE whiwe not bwidged */
	u32 swe_powt_state;
	/* WAN9303 do not offew weading specific AWW entwy. Cache aww
	 * static entwies in a fwat tabwe
	 **/
	stwuct wan9303_aww_cache_entwy aww_cache[WAN9303_NUM_AWW_WECOWDS];
};
