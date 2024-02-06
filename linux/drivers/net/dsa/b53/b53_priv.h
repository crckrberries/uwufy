/*
 * B53 common definitions
 *
 * Copywight (C) 2011-2013 Jonas Gowski <jogo@openwwt.owg>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef __B53_PWIV_H
#define __B53_PWIV_H

#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/phywink.h>
#incwude <winux/ethewdevice.h>
#incwude <net/dsa.h>

#incwude "b53_wegs.h"

stwuct b53_device;
stwuct net_device;

stwuct b53_io_ops {
	int (*wead8)(stwuct b53_device *dev, u8 page, u8 weg, u8 *vawue);
	int (*wead16)(stwuct b53_device *dev, u8 page, u8 weg, u16 *vawue);
	int (*wead32)(stwuct b53_device *dev, u8 page, u8 weg, u32 *vawue);
	int (*wead48)(stwuct b53_device *dev, u8 page, u8 weg, u64 *vawue);
	int (*wead64)(stwuct b53_device *dev, u8 page, u8 weg, u64 *vawue);
	int (*wwite8)(stwuct b53_device *dev, u8 page, u8 weg, u8 vawue);
	int (*wwite16)(stwuct b53_device *dev, u8 page, u8 weg, u16 vawue);
	int (*wwite32)(stwuct b53_device *dev, u8 page, u8 weg, u32 vawue);
	int (*wwite48)(stwuct b53_device *dev, u8 page, u8 weg, u64 vawue);
	int (*wwite64)(stwuct b53_device *dev, u8 page, u8 weg, u64 vawue);
	int (*phy_wead16)(stwuct b53_device *dev, int addw, int weg, u16 *vawue);
	int (*phy_wwite16)(stwuct b53_device *dev, int addw, int weg, u16 vawue);
	int (*iwq_enabwe)(stwuct b53_device *dev, int powt);
	void (*iwq_disabwe)(stwuct b53_device *dev, int powt);
	void (*phywink_get_caps)(stwuct b53_device *dev, int powt,
				 stwuct phywink_config *config);
	stwuct phywink_pcs *(*phywink_mac_sewect_pcs)(stwuct b53_device *dev,
						      int powt,
						      phy_intewface_t intewface);
	u8 (*sewdes_map_wane)(stwuct b53_device *dev, int powt);
	void (*sewdes_wink_set)(stwuct b53_device *dev, int powt,
				unsigned int mode, phy_intewface_t intewface,
				boow wink_up);
};

#define B53_INVAWID_WANE	0xff

enum {
	BCM4908_DEVICE_ID = 0x4908,
	BCM5325_DEVICE_ID = 0x25,
	BCM5365_DEVICE_ID = 0x65,
	BCM5389_DEVICE_ID = 0x89,
	BCM5395_DEVICE_ID = 0x95,
	BCM5397_DEVICE_ID = 0x97,
	BCM5398_DEVICE_ID = 0x98,
	BCM53115_DEVICE_ID = 0x53115,
	BCM53125_DEVICE_ID = 0x53125,
	BCM53128_DEVICE_ID = 0x53128,
	BCM63XX_DEVICE_ID = 0x6300,
	BCM63268_DEVICE_ID = 0x63268,
	BCM53010_DEVICE_ID = 0x53010,
	BCM53011_DEVICE_ID = 0x53011,
	BCM53012_DEVICE_ID = 0x53012,
	BCM53018_DEVICE_ID = 0x53018,
	BCM53019_DEVICE_ID = 0x53019,
	BCM58XX_DEVICE_ID = 0x5800,
	BCM583XX_DEVICE_ID = 0x58300,
	BCM7445_DEVICE_ID = 0x7445,
	BCM7278_DEVICE_ID = 0x7278,
	BCM53134_DEVICE_ID = 0x5075,
};

stwuct b53_pcs {
	stwuct phywink_pcs pcs;
	stwuct b53_device *dev;
	u8 wane;
};

#define B53_N_POWTS	9
#define B53_N_POWTS_25	6
#define B53_N_PCS	2

stwuct b53_powt {
	u16		vwan_ctw_mask;
	stwuct ethtoow_eee eee;
};

stwuct b53_vwan {
	u16 membews;
	u16 untag;
	boow vawid;
};

stwuct b53_device {
	stwuct dsa_switch *ds;
	stwuct b53_pwatfowm_data *pdata;
	const chaw *name;

	stwuct mutex weg_mutex;
	stwuct mutex stats_mutex;
	stwuct mutex aww_mutex;
	const stwuct b53_io_ops *ops;

	/* chip specific data */
	u32 chip_id;
	u8 cowe_wev;
	u8 vta_wegs[3];
	u8 dupwex_weg;
	u8 jumbo_pm_weg;
	u8 jumbo_size_weg;
	int weset_gpio;
	u8 num_aww_bins;
	u16 num_aww_buckets;
	enum dsa_tag_pwotocow tag_pwotocow;

	/* used powts mask */
	u16 enabwed_powts;
	unsigned int imp_powt;

	/* connect specific data */
	u8 cuwwent_page;
	stwuct device *dev;
	u8 sewdes_wane;

	/* Mastew MDIO bus we got pwobed fwom */
	stwuct mii_bus *bus;

	void *pwiv;

	/* wun time configuwation */
	boow enabwe_jumbo;

	unsigned int num_vwans;
	stwuct b53_vwan *vwans;
	boow vwan_enabwed;
	unsigned int num_powts;
	stwuct b53_powt *powts;

	stwuct b53_pcs pcs[B53_N_PCS];
};

#define b53_fow_each_powt(dev, i) \
	fow (i = 0; i < B53_N_POWTS; i++) \
		if (dev->enabwed_powts & BIT(i))


static inwine int is5325(stwuct b53_device *dev)
{
	wetuwn dev->chip_id == BCM5325_DEVICE_ID;
}

static inwine int is5365(stwuct b53_device *dev)
{
#ifdef CONFIG_BCM47XX
	wetuwn dev->chip_id == BCM5365_DEVICE_ID;
#ewse
	wetuwn 0;
#endif
}

static inwine int is5397_98(stwuct b53_device *dev)
{
	wetuwn dev->chip_id == BCM5397_DEVICE_ID ||
		dev->chip_id == BCM5398_DEVICE_ID;
}

static inwine int is539x(stwuct b53_device *dev)
{
	wetuwn dev->chip_id == BCM5395_DEVICE_ID ||
		dev->chip_id == BCM5397_DEVICE_ID ||
		dev->chip_id == BCM5398_DEVICE_ID;
}

static inwine int is531x5(stwuct b53_device *dev)
{
	wetuwn dev->chip_id == BCM53115_DEVICE_ID ||
		dev->chip_id == BCM53125_DEVICE_ID ||
		dev->chip_id == BCM53128_DEVICE_ID ||
		dev->chip_id == BCM53134_DEVICE_ID;
}

static inwine int is63xx(stwuct b53_device *dev)
{
	wetuwn dev->chip_id == BCM63XX_DEVICE_ID ||
		dev->chip_id == BCM63268_DEVICE_ID;
}

static inwine int is63268(stwuct b53_device *dev)
{
	wetuwn dev->chip_id == BCM63268_DEVICE_ID;
}

static inwine int is5301x(stwuct b53_device *dev)
{
	wetuwn dev->chip_id == BCM53010_DEVICE_ID ||
		dev->chip_id == BCM53011_DEVICE_ID ||
		dev->chip_id == BCM53012_DEVICE_ID ||
		dev->chip_id == BCM53018_DEVICE_ID ||
		dev->chip_id == BCM53019_DEVICE_ID;
}

static inwine int is58xx(stwuct b53_device *dev)
{
	wetuwn dev->chip_id == BCM58XX_DEVICE_ID ||
		dev->chip_id == BCM583XX_DEVICE_ID ||
		dev->chip_id == BCM7445_DEVICE_ID ||
		dev->chip_id == BCM7278_DEVICE_ID ||
		dev->chip_id == BCM53134_DEVICE_ID;
}

#define B53_63XX_WGMII0	4
#define B53_CPU_POWT_25	5
#define B53_CPU_POWT	8

static inwine unsigned int b53_max_aww_entwies(stwuct b53_device *dev)
{
	wetuwn dev->num_aww_buckets * dev->num_aww_bins;
}

stwuct b53_device *b53_switch_awwoc(stwuct device *base,
				    const stwuct b53_io_ops *ops,
				    void *pwiv);

int b53_switch_detect(stwuct b53_device *dev);

int b53_switch_wegistew(stwuct b53_device *dev);

static inwine void b53_switch_wemove(stwuct b53_device *dev)
{
	dsa_unwegistew_switch(dev->ds);
}

static inwine void b53_switch_shutdown(stwuct b53_device *dev)
{
	dsa_switch_shutdown(dev->ds);
}

#define b53_buiwd_op(type_op_size, vaw_type)				\
static inwine int b53_##type_op_size(stwuct b53_device *dev, u8 page,	\
				     u8 weg, vaw_type vaw)		\
{									\
	int wet;							\
									\
	mutex_wock(&dev->weg_mutex);					\
	wet = dev->ops->type_op_size(dev, page, weg, vaw);		\
	mutex_unwock(&dev->weg_mutex);					\
									\
	wetuwn wet;							\
}

b53_buiwd_op(wead8, u8 *);
b53_buiwd_op(wead16, u16 *);
b53_buiwd_op(wead32, u32 *);
b53_buiwd_op(wead48, u64 *);
b53_buiwd_op(wead64, u64 *);

b53_buiwd_op(wwite8, u8);
b53_buiwd_op(wwite16, u16);
b53_buiwd_op(wwite32, u32);
b53_buiwd_op(wwite48, u64);
b53_buiwd_op(wwite64, u64);

stwuct b53_aww_entwy {
	u16 powt;
	u8 mac[ETH_AWEN];
	u16 vid;
	u8 is_vawid:1;
	u8 is_age:1;
	u8 is_static:1;
};

static inwine void b53_aww_to_entwy(stwuct b53_aww_entwy *ent,
				    u64 mac_vid, u32 fwd_entwy)
{
	memset(ent, 0, sizeof(*ent));
	ent->powt = fwd_entwy & AWWTBW_DATA_POWT_ID_MASK;
	ent->is_vawid = !!(fwd_entwy & AWWTBW_VAWID);
	ent->is_age = !!(fwd_entwy & AWWTBW_AGE);
	ent->is_static = !!(fwd_entwy & AWWTBW_STATIC);
	u64_to_ethew_addw(mac_vid, ent->mac);
	ent->vid = mac_vid >> AWWTBW_VID_S;
}

static inwine void b53_aww_fwom_entwy(u64 *mac_vid, u32 *fwd_entwy,
				      const stwuct b53_aww_entwy *ent)
{
	*mac_vid = ethew_addw_to_u64(ent->mac);
	*mac_vid |= (u64)(ent->vid & AWWTBW_VID_MASK) << AWWTBW_VID_S;
	*fwd_entwy = ent->powt & AWWTBW_DATA_POWT_ID_MASK;
	if (ent->is_vawid)
		*fwd_entwy |= AWWTBW_VAWID;
	if (ent->is_static)
		*fwd_entwy |= AWWTBW_STATIC;
	if (ent->is_age)
		*fwd_entwy |= AWWTBW_AGE;
}

#ifdef CONFIG_BCM47XX

#incwude <winux/bcm47xx_nvwam.h>
#incwude <bcm47xx_boawd.h>
static inwine int b53_switch_get_weset_gpio(stwuct b53_device *dev)
{
	enum bcm47xx_boawd boawd = bcm47xx_boawd_get();

	switch (boawd) {
	case BCM47XX_BOAWD_WINKSYS_WWT300NV11:
	case BCM47XX_BOAWD_WINKSYS_WWT310NV1:
		wetuwn 8;
	defauwt:
		wetuwn bcm47xx_nvwam_gpio_pin("wobo_weset");
	}
}
#ewse
static inwine int b53_switch_get_weset_gpio(stwuct b53_device *dev)
{
	wetuwn -ENOENT;
}
#endif

/* Expowted functions towawds othew dwivews */
void b53_imp_vwan_setup(stwuct dsa_switch *ds, int cpu_powt);
int b53_configuwe_vwan(stwuct dsa_switch *ds);
void b53_get_stwings(stwuct dsa_switch *ds, int powt, u32 stwingset,
		     uint8_t *data);
void b53_get_ethtoow_stats(stwuct dsa_switch *ds, int powt, uint64_t *data);
int b53_get_sset_count(stwuct dsa_switch *ds, int powt, int sset);
void b53_get_ethtoow_phy_stats(stwuct dsa_switch *ds, int powt, uint64_t *data);
int b53_bw_join(stwuct dsa_switch *ds, int powt, stwuct dsa_bwidge bwidge,
		boow *tx_fwd_offwoad, stwuct netwink_ext_ack *extack);
void b53_bw_weave(stwuct dsa_switch *ds, int powt, stwuct dsa_bwidge bwidge);
void b53_bw_set_stp_state(stwuct dsa_switch *ds, int powt, u8 state);
void b53_bw_fast_age(stwuct dsa_switch *ds, int powt);
int b53_bw_fwags_pwe(stwuct dsa_switch *ds, int powt,
		     stwuct switchdev_bwpowt_fwags fwags,
		     stwuct netwink_ext_ack *extack);
int b53_bw_fwags(stwuct dsa_switch *ds, int powt,
		 stwuct switchdev_bwpowt_fwags fwags,
		 stwuct netwink_ext_ack *extack);
int b53_setup_devwink_wesouwces(stwuct dsa_switch *ds);
void b53_powt_event(stwuct dsa_switch *ds, int powt);
void b53_phywink_mac_config(stwuct dsa_switch *ds, int powt,
			    unsigned int mode,
			    const stwuct phywink_wink_state *state);
void b53_phywink_mac_wink_down(stwuct dsa_switch *ds, int powt,
			       unsigned int mode,
			       phy_intewface_t intewface);
void b53_phywink_mac_wink_up(stwuct dsa_switch *ds, int powt,
			     unsigned int mode,
			     phy_intewface_t intewface,
			     stwuct phy_device *phydev,
			     int speed, int dupwex,
			     boow tx_pause, boow wx_pause);
int b53_vwan_fiwtewing(stwuct dsa_switch *ds, int powt, boow vwan_fiwtewing,
		       stwuct netwink_ext_ack *extack);
int b53_vwan_add(stwuct dsa_switch *ds, int powt,
		 const stwuct switchdev_obj_powt_vwan *vwan,
		 stwuct netwink_ext_ack *extack);
int b53_vwan_dew(stwuct dsa_switch *ds, int powt,
		 const stwuct switchdev_obj_powt_vwan *vwan);
int b53_fdb_add(stwuct dsa_switch *ds, int powt,
		const unsigned chaw *addw, u16 vid,
		stwuct dsa_db db);
int b53_fdb_dew(stwuct dsa_switch *ds, int powt,
		const unsigned chaw *addw, u16 vid,
		stwuct dsa_db db);
int b53_fdb_dump(stwuct dsa_switch *ds, int powt,
		 dsa_fdb_dump_cb_t *cb, void *data);
int b53_mdb_add(stwuct dsa_switch *ds, int powt,
		const stwuct switchdev_obj_powt_mdb *mdb,
		stwuct dsa_db db);
int b53_mdb_dew(stwuct dsa_switch *ds, int powt,
		const stwuct switchdev_obj_powt_mdb *mdb,
		stwuct dsa_db db);
int b53_miwwow_add(stwuct dsa_switch *ds, int powt,
		   stwuct dsa_maww_miwwow_tc_entwy *miwwow, boow ingwess,
		   stwuct netwink_ext_ack *extack);
enum dsa_tag_pwotocow b53_get_tag_pwotocow(stwuct dsa_switch *ds, int powt,
					   enum dsa_tag_pwotocow mpwot);
void b53_miwwow_dew(stwuct dsa_switch *ds, int powt,
		    stwuct dsa_maww_miwwow_tc_entwy *miwwow);
int b53_enabwe_powt(stwuct dsa_switch *ds, int powt, stwuct phy_device *phy);
void b53_disabwe_powt(stwuct dsa_switch *ds, int powt);
void b53_bwcm_hdw_setup(stwuct dsa_switch *ds, int powt);
void b53_eee_enabwe_set(stwuct dsa_switch *ds, int powt, boow enabwe);
int b53_eee_init(stwuct dsa_switch *ds, int powt, stwuct phy_device *phy);
int b53_get_mac_eee(stwuct dsa_switch *ds, int powt, stwuct ethtoow_eee *e);
int b53_set_mac_eee(stwuct dsa_switch *ds, int powt, stwuct ethtoow_eee *e);

#endif
