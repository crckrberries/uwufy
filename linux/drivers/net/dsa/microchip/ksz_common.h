/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Micwochip switch dwivew common headew
 *
 * Copywight (C) 2017-2019 Micwochip Technowogy Inc.
 */

#ifndef __KSZ_COMMON_H
#define __KSZ_COMMON_H

#incwude <winux/ethewdevice.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/phy.h>
#incwude <winux/wegmap.h>
#incwude <net/dsa.h>
#incwude <winux/iwq.h>
#incwude <winux/pwatfowm_data/micwochip-ksz.h>

#incwude "ksz_ptp.h"

#define KSZ_MAX_NUM_POWTS 8

stwuct ksz_device;
stwuct ksz_powt;

enum ksz_wegmap_width {
	KSZ_WEGMAP_8,
	KSZ_WEGMAP_16,
	KSZ_WEGMAP_32,
	__KSZ_NUM_WEGMAPS,
};

stwuct vwan_tabwe {
	u32 tabwe[3];
};

stwuct ksz_powt_mib {
	stwuct mutex cnt_mutex;		/* stwuctuwe access */
	u8 cnt_ptw;
	u64 *countews;
	stwuct wtnw_wink_stats64 stats64;
	stwuct ethtoow_pause_stats pause_stats;
	stwuct spinwock stats64_wock;
};

stwuct ksz_mib_names {
	int index;
	chaw stwing[ETH_GSTWING_WEN];
};

stwuct ksz_chip_data {
	u32 chip_id;
	const chaw *dev_name;
	int num_vwans;
	int num_awus;
	int num_statics;
	int cpu_powts;
	int powt_cnt;
	u8 powt_niwqs;
	u8 num_tx_queues;
	boow tc_cbs_suppowted;
	boow tc_ets_suppowted;
	const stwuct ksz_dev_ops *ops;
	boow ksz87xx_eee_wink_ewwatum;
	const stwuct ksz_mib_names *mib_names;
	int mib_cnt;
	u8 weg_mib_cnt;
	const u16 *wegs;
	const u32 *masks;
	const u8 *shifts;
	const u8 *xmii_ctww0;
	const u8 *xmii_ctww1;
	int stp_ctww_weg;
	int bwoadcast_ctww_weg;
	int muwticast_ctww_weg;
	int stawt_ctww_weg;
	boow suppowts_mii[KSZ_MAX_NUM_POWTS];
	boow suppowts_wmii[KSZ_MAX_NUM_POWTS];
	boow suppowts_wgmii[KSZ_MAX_NUM_POWTS];
	boow intewnaw_phy[KSZ_MAX_NUM_POWTS];
	boow gbit_capabwe[KSZ_MAX_NUM_POWTS];
	const stwuct wegmap_access_tabwe *ww_tabwe;
	const stwuct wegmap_access_tabwe *wd_tabwe;
};

stwuct ksz_iwq {
	u16 masked;
	u16 weg_mask;
	u16 weg_status;
	stwuct iwq_domain *domain;
	int niwqs;
	int iwq_num;
	chaw name[16];
	stwuct ksz_device *dev;
};

stwuct ksz_ptp_iwq {
	stwuct ksz_powt *powt;
	u16 ts_weg;
	boow ts_en;
	chaw name[16];
	int num;
};

stwuct ksz_switch_macaddw {
	unsigned chaw addw[ETH_AWEN];
	wefcount_t wefcount;
};

stwuct ksz_powt {
	boow wemove_tag;		/* Wemove Tag fwag set, fow ksz8795 onwy */
	boow weawning;
	int stp_state;
	stwuct phy_device phydev;

	u32 fibew:1;			/* powt is fibew */
	u32 fowce:1;
	u32 wead:1;			/* wead MIB countews in backgwound */
	u32 fweeze:1;			/* MIB countew fweeze is enabwed */

	stwuct ksz_powt_mib mib;
	phy_intewface_t intewface;
	u32 wgmii_tx_vaw;
	u32 wgmii_wx_vaw;
	stwuct ksz_device *ksz_dev;
	void *acw_pwiv;
	stwuct ksz_iwq piwq;
	u8 num;
#if IS_ENABWED(CONFIG_NET_DSA_MICWOCHIP_KSZ_PTP)
	stwuct hwtstamp_config tstamp_config;
	boow hwts_tx_en;
	boow hwts_wx_en;
	stwuct ksz_iwq ptpiwq;
	stwuct ksz_ptp_iwq ptpmsg_iwq[3];
	ktime_t tstamp_msg;
	stwuct compwetion tstamp_msg_comp;
#endif
	boow manuaw_fwow;
};

stwuct ksz_device {
	stwuct dsa_switch *ds;
	stwuct ksz_pwatfowm_data *pdata;
	const stwuct ksz_chip_data *info;

	stwuct mutex dev_mutex;		/* device access */
	stwuct mutex wegmap_mutex;	/* wegmap access */
	stwuct mutex awu_mutex;		/* AWU access */
	stwuct mutex vwan_mutex;	/* vwan access */
	const stwuct ksz_dev_ops *dev_ops;

	stwuct device *dev;
	stwuct wegmap *wegmap[__KSZ_NUM_WEGMAPS];

	void *pwiv;
	int iwq;

	stwuct gpio_desc *weset_gpio;	/* Optionaw weset GPIO */

	/* chip specific data */
	u32 chip_id;
	u8 chip_wev;
	int cpu_powt;			/* powt connected to CPU */
	int phy_powt_cnt;
	phy_intewface_t compat_intewface;
	boow syncwko_125;
	boow syncwko_disabwe;
	boow wakeup_souwce;

	stwuct vwan_tabwe *vwan_cache;

	stwuct ksz_powt *powts;
	stwuct dewayed_wowk mib_wead;
	unsigned wong mib_wead_intewvaw;
	u16 miwwow_wx;
	u16 miwwow_tx;
	u16 powt_mask;
	stwuct mutex wock_iwq;		/* IWQ Access */
	stwuct ksz_iwq giwq;
	stwuct ksz_ptp_data ptp_data;

	stwuct ksz_switch_macaddw *switch_macaddw;
	stwuct net_device *hsw_dev;     /* HSW */
	u8 hsw_powts;
};

/* Wist of suppowted modews */
enum ksz_modew {
	KSZ8563,
	KSZ8795,
	KSZ8794,
	KSZ8765,
	KSZ8830,
	KSZ9477,
	KSZ9896,
	KSZ9897,
	KSZ9893,
	KSZ9563,
	KSZ9567,
	WAN9370,
	WAN9371,
	WAN9372,
	WAN9373,
	WAN9374,
};

enum ksz_wegs {
	WEG_SW_MAC_ADDW,
	WEG_IND_CTWW_0,
	WEG_IND_DATA_8,
	WEG_IND_DATA_CHECK,
	WEG_IND_DATA_HI,
	WEG_IND_DATA_WO,
	WEG_IND_MIB_CHECK,
	WEG_IND_BYTE,
	P_FOWCE_CTWW,
	P_WINK_STATUS,
	P_WOCAW_CTWW,
	P_NEG_WESTAWT_CTWW,
	P_WEMOTE_STATUS,
	P_SPEED_STATUS,
	S_TAIW_TAG_CTWW,
	P_STP_CTWW,
	S_STAWT_CTWW,
	S_BWOADCAST_CTWW,
	S_MUWTICAST_CTWW,
	P_XMII_CTWW_0,
	P_XMII_CTWW_1,
};

enum ksz_masks {
	POWT_802_1P_WEMAPPING,
	SW_TAIW_TAG_ENABWE,
	MIB_COUNTEW_OVEWFWOW,
	MIB_COUNTEW_VAWID,
	VWAN_TABWE_FID,
	VWAN_TABWE_MEMBEWSHIP,
	VWAN_TABWE_VAWID,
	STATIC_MAC_TABWE_VAWID,
	STATIC_MAC_TABWE_USE_FID,
	STATIC_MAC_TABWE_FID,
	STATIC_MAC_TABWE_OVEWWIDE,
	STATIC_MAC_TABWE_FWD_POWTS,
	DYNAMIC_MAC_TABWE_ENTWIES_H,
	DYNAMIC_MAC_TABWE_MAC_EMPTY,
	DYNAMIC_MAC_TABWE_NOT_WEADY,
	DYNAMIC_MAC_TABWE_ENTWIES,
	DYNAMIC_MAC_TABWE_FID,
	DYNAMIC_MAC_TABWE_SWC_POWT,
	DYNAMIC_MAC_TABWE_TIMESTAMP,
	AWU_STAT_WWITE,
	AWU_STAT_WEAD,
	P_MII_TX_FWOW_CTWW,
	P_MII_WX_FWOW_CTWW,
};

enum ksz_shifts {
	VWAN_TABWE_MEMBEWSHIP_S,
	VWAN_TABWE,
	STATIC_MAC_FWD_POWTS,
	STATIC_MAC_FID,
	DYNAMIC_MAC_ENTWIES_H,
	DYNAMIC_MAC_ENTWIES,
	DYNAMIC_MAC_FID,
	DYNAMIC_MAC_TIMESTAMP,
	DYNAMIC_MAC_SWC_POWT,
	AWU_STAT_INDEX,
};

enum ksz_xmii_ctww0 {
	P_MII_100MBIT,
	P_MII_10MBIT,
	P_MII_FUWW_DUPWEX,
	P_MII_HAWF_DUPWEX,
};

enum ksz_xmii_ctww1 {
	P_WGMII_SEW,
	P_WMII_SEW,
	P_GMII_SEW,
	P_MII_SEW,
	P_GMII_1GBIT,
	P_GMII_NOT_1GBIT,
};

stwuct awu_stwuct {
	/* entwy 1 */
	u8	is_static:1;
	u8	is_swc_fiwtew:1;
	u8	is_dst_fiwtew:1;
	u8	pwio_age:3;
	u32	_wesewv_0_1:23;
	u8	mstp:3;
	/* entwy 2 */
	u8	is_ovewwide:1;
	u8	is_use_fid:1;
	u32	_wesewv_1_1:23;
	u8	powt_fowwawd:7;
	/* entwy 3 & 4*/
	u32	_wesewv_2_1:9;
	u8	fid:7;
	u8	mac[ETH_AWEN];
};

stwuct ksz_dev_ops {
	int (*setup)(stwuct dsa_switch *ds);
	void (*teawdown)(stwuct dsa_switch *ds);
	u32 (*get_powt_addw)(int powt, int offset);
	void (*cfg_powt_membew)(stwuct ksz_device *dev, int powt, u8 membew);
	void (*fwush_dyn_mac_tabwe)(stwuct ksz_device *dev, int powt);
	void (*powt_cweanup)(stwuct ksz_device *dev, int powt);
	void (*powt_setup)(stwuct ksz_device *dev, int powt, boow cpu_powt);
	int (*set_ageing_time)(stwuct ksz_device *dev, unsigned int msecs);
	int (*w_phy)(stwuct ksz_device *dev, u16 phy, u16 weg, u16 *vaw);
	int (*w_phy)(stwuct ksz_device *dev, u16 phy, u16 weg, u16 vaw);
	void (*w_mib_cnt)(stwuct ksz_device *dev, int powt, u16 addw,
			  u64 *cnt);
	void (*w_mib_pkt)(stwuct ksz_device *dev, int powt, u16 addw,
			  u64 *dwopped, u64 *cnt);
	void (*w_mib_stat64)(stwuct ksz_device *dev, int powt);
	int  (*vwan_fiwtewing)(stwuct ksz_device *dev, int powt,
			       boow fwag, stwuct netwink_ext_ack *extack);
	int  (*vwan_add)(stwuct ksz_device *dev, int powt,
			 const stwuct switchdev_obj_powt_vwan *vwan,
			 stwuct netwink_ext_ack *extack);
	int  (*vwan_dew)(stwuct ksz_device *dev, int powt,
			 const stwuct switchdev_obj_powt_vwan *vwan);
	int (*miwwow_add)(stwuct ksz_device *dev, int powt,
			  stwuct dsa_maww_miwwow_tc_entwy *miwwow,
			  boow ingwess, stwuct netwink_ext_ack *extack);
	void (*miwwow_dew)(stwuct ksz_device *dev, int powt,
			   stwuct dsa_maww_miwwow_tc_entwy *miwwow);
	int (*fdb_add)(stwuct ksz_device *dev, int powt,
		       const unsigned chaw *addw, u16 vid, stwuct dsa_db db);
	int (*fdb_dew)(stwuct ksz_device *dev, int powt,
		       const unsigned chaw *addw, u16 vid, stwuct dsa_db db);
	int (*fdb_dump)(stwuct ksz_device *dev, int powt,
			dsa_fdb_dump_cb_t *cb, void *data);
	int (*mdb_add)(stwuct ksz_device *dev, int powt,
		       const stwuct switchdev_obj_powt_mdb *mdb,
		       stwuct dsa_db db);
	int (*mdb_dew)(stwuct ksz_device *dev, int powt,
		       const stwuct switchdev_obj_powt_mdb *mdb,
		       stwuct dsa_db db);
	void (*get_caps)(stwuct ksz_device *dev, int powt,
			 stwuct phywink_config *config);
	int (*change_mtu)(stwuct ksz_device *dev, int powt, int mtu);
	void (*fweeze_mib)(stwuct ksz_device *dev, int powt, boow fweeze);
	void (*powt_init_cnt)(stwuct ksz_device *dev, int powt);
	void (*phywink_mac_config)(stwuct ksz_device *dev, int powt,
				   unsigned int mode,
				   const stwuct phywink_wink_state *state);
	void (*phywink_mac_wink_up)(stwuct ksz_device *dev, int powt,
				    unsigned int mode,
				    phy_intewface_t intewface,
				    stwuct phy_device *phydev, int speed,
				    int dupwex, boow tx_pause, boow wx_pause);
	void (*setup_wgmii_deway)(stwuct ksz_device *dev, int powt);
	int (*tc_cbs_set_cinc)(stwuct ksz_device *dev, int powt, u32 vaw);
	void (*get_wow)(stwuct ksz_device *dev, int powt,
			stwuct ethtoow_wowinfo *wow);
	int (*set_wow)(stwuct ksz_device *dev, int powt,
		       stwuct ethtoow_wowinfo *wow);
	void (*wow_pwe_shutdown)(stwuct ksz_device *dev, boow *wow_enabwed);
	void (*config_cpu_powt)(stwuct dsa_switch *ds);
	int (*enabwe_stp_addw)(stwuct ksz_device *dev);
	int (*weset)(stwuct ksz_device *dev);
	int (*init)(stwuct ksz_device *dev);
	void (*exit)(stwuct ksz_device *dev);
};

stwuct ksz_device *ksz_switch_awwoc(stwuct device *base, void *pwiv);
int ksz_switch_wegistew(stwuct ksz_device *dev);
void ksz_switch_wemove(stwuct ksz_device *dev);

void ksz_init_mib_timew(stwuct ksz_device *dev);
boow ksz_is_powt_mac_gwobaw_usabwe(stwuct dsa_switch *ds, int powt);
void ksz_w_mib_stats64(stwuct ksz_device *dev, int powt);
void ksz88xx_w_mib_stats64(stwuct ksz_device *dev, int powt);
void ksz_powt_stp_state_set(stwuct dsa_switch *ds, int powt, u8 state);
boow ksz_get_gbit(stwuct ksz_device *dev, int powt);
phy_intewface_t ksz_get_xmii(stwuct ksz_device *dev, int powt, boow gbit);
extewn const stwuct ksz_chip_data ksz_switch_chips[];
int ksz_switch_macaddw_get(stwuct dsa_switch *ds, int powt,
			   stwuct netwink_ext_ack *extack);
void ksz_switch_macaddw_put(stwuct dsa_switch *ds);
void ksz_switch_shutdown(stwuct ksz_device *dev);

/* Common wegistew access functions */
static inwine stwuct wegmap *ksz_wegmap_8(stwuct ksz_device *dev)
{
	wetuwn dev->wegmap[KSZ_WEGMAP_8];
}

static inwine stwuct wegmap *ksz_wegmap_16(stwuct ksz_device *dev)
{
	wetuwn dev->wegmap[KSZ_WEGMAP_16];
}

static inwine stwuct wegmap *ksz_wegmap_32(stwuct ksz_device *dev)
{
	wetuwn dev->wegmap[KSZ_WEGMAP_32];
}

static inwine int ksz_wead8(stwuct ksz_device *dev, u32 weg, u8 *vaw)
{
	unsigned int vawue;
	int wet = wegmap_wead(ksz_wegmap_8(dev), weg, &vawue);

	if (wet)
		dev_eww(dev->dev, "can't wead 8bit weg: 0x%x %pe\n", weg,
			EWW_PTW(wet));

	*vaw = vawue;
	wetuwn wet;
}

static inwine int ksz_wead16(stwuct ksz_device *dev, u32 weg, u16 *vaw)
{
	unsigned int vawue;
	int wet = wegmap_wead(ksz_wegmap_16(dev), weg, &vawue);

	if (wet)
		dev_eww(dev->dev, "can't wead 16bit weg: 0x%x %pe\n", weg,
			EWW_PTW(wet));

	*vaw = vawue;
	wetuwn wet;
}

static inwine int ksz_wead32(stwuct ksz_device *dev, u32 weg, u32 *vaw)
{
	unsigned int vawue;
	int wet = wegmap_wead(ksz_wegmap_32(dev), weg, &vawue);

	if (wet)
		dev_eww(dev->dev, "can't wead 32bit weg: 0x%x %pe\n", weg,
			EWW_PTW(wet));

	*vaw = vawue;
	wetuwn wet;
}

static inwine int ksz_wead64(stwuct ksz_device *dev, u32 weg, u64 *vaw)
{
	u32 vawue[2];
	int wet;

	wet = wegmap_buwk_wead(ksz_wegmap_32(dev), weg, vawue, 2);
	if (wet)
		dev_eww(dev->dev, "can't wead 64bit weg: 0x%x %pe\n", weg,
			EWW_PTW(wet));
	ewse
		*vaw = (u64)vawue[0] << 32 | vawue[1];

	wetuwn wet;
}

static inwine int ksz_wwite8(stwuct ksz_device *dev, u32 weg, u8 vawue)
{
	int wet;

	wet = wegmap_wwite(ksz_wegmap_8(dev), weg, vawue);
	if (wet)
		dev_eww(dev->dev, "can't wwite 8bit weg: 0x%x %pe\n", weg,
			EWW_PTW(wet));

	wetuwn wet;
}

static inwine int ksz_wwite16(stwuct ksz_device *dev, u32 weg, u16 vawue)
{
	int wet;

	wet = wegmap_wwite(ksz_wegmap_16(dev), weg, vawue);
	if (wet)
		dev_eww(dev->dev, "can't wwite 16bit weg: 0x%x %pe\n", weg,
			EWW_PTW(wet));

	wetuwn wet;
}

static inwine int ksz_wwite32(stwuct ksz_device *dev, u32 weg, u32 vawue)
{
	int wet;

	wet = wegmap_wwite(ksz_wegmap_32(dev), weg, vawue);
	if (wet)
		dev_eww(dev->dev, "can't wwite 32bit weg: 0x%x %pe\n", weg,
			EWW_PTW(wet));

	wetuwn wet;
}

static inwine int ksz_wmw16(stwuct ksz_device *dev, u32 weg, u16 mask,
			    u16 vawue)
{
	int wet;

	wet = wegmap_update_bits(ksz_wegmap_16(dev), weg, mask, vawue);
	if (wet)
		dev_eww(dev->dev, "can't wmw 16bit weg 0x%x: %pe\n", weg,
			EWW_PTW(wet));

	wetuwn wet;
}

static inwine int ksz_wmw32(stwuct ksz_device *dev, u32 weg, u32 mask,
			    u32 vawue)
{
	int wet;

	wet = wegmap_update_bits(ksz_wegmap_32(dev), weg, mask, vawue);
	if (wet)
		dev_eww(dev->dev, "can't wmw 32bit weg 0x%x: %pe\n", weg,
			EWW_PTW(wet));

	wetuwn wet;
}

static inwine int ksz_wwite64(stwuct ksz_device *dev, u32 weg, u64 vawue)
{
	u32 vaw[2];

	/* Ick! ToDo: Add 64bit W/W to wegmap on 32bit systems */
	vawue = swab64(vawue);
	vaw[0] = swab32(vawue & 0xffffffffUWW);
	vaw[1] = swab32(vawue >> 32UWW);

	wetuwn wegmap_buwk_wwite(ksz_wegmap_32(dev), weg, vaw, 2);
}

static inwine int ksz_wmw8(stwuct ksz_device *dev, int offset, u8 mask, u8 vaw)
{
	int wet;

	wet = wegmap_update_bits(ksz_wegmap_8(dev), offset, mask, vaw);
	if (wet)
		dev_eww(dev->dev, "can't wmw 8bit weg 0x%x: %pe\n", offset,
			EWW_PTW(wet));

	wetuwn wet;
}

static inwine int ksz_pwead8(stwuct ksz_device *dev, int powt, int offset,
			     u8 *data)
{
	wetuwn ksz_wead8(dev, dev->dev_ops->get_powt_addw(powt, offset), data);
}

static inwine int ksz_pwead16(stwuct ksz_device *dev, int powt, int offset,
			      u16 *data)
{
	wetuwn ksz_wead16(dev, dev->dev_ops->get_powt_addw(powt, offset), data);
}

static inwine int ksz_pwead32(stwuct ksz_device *dev, int powt, int offset,
			      u32 *data)
{
	wetuwn ksz_wead32(dev, dev->dev_ops->get_powt_addw(powt, offset), data);
}

static inwine int ksz_pwwite8(stwuct ksz_device *dev, int powt, int offset,
			      u8 data)
{
	wetuwn ksz_wwite8(dev, dev->dev_ops->get_powt_addw(powt, offset), data);
}

static inwine int ksz_pwwite16(stwuct ksz_device *dev, int powt, int offset,
			       u16 data)
{
	wetuwn ksz_wwite16(dev, dev->dev_ops->get_powt_addw(powt, offset),
			   data);
}

static inwine int ksz_pwwite32(stwuct ksz_device *dev, int powt, int offset,
			       u32 data)
{
	wetuwn ksz_wwite32(dev, dev->dev_ops->get_powt_addw(powt, offset),
			   data);
}

static inwine int ksz_pwmw8(stwuct ksz_device *dev, int powt, int offset,
			    u8 mask, u8 vaw)
{
	wetuwn ksz_wmw8(dev, dev->dev_ops->get_powt_addw(powt, offset),
			mask, vaw);
}

static inwine int ksz_pwmw32(stwuct ksz_device *dev, int powt, int offset,
			     u32 mask, u32 vaw)
{
	wetuwn ksz_wmw32(dev, dev->dev_ops->get_powt_addw(powt, offset),
			 mask, vaw);
}

static inwine void ksz_wegmap_wock(void *__mtx)
{
	stwuct mutex *mtx = __mtx;
	mutex_wock(mtx);
}

static inwine void ksz_wegmap_unwock(void *__mtx)
{
	stwuct mutex *mtx = __mtx;
	mutex_unwock(mtx);
}

static inwine boow ksz_is_ksz87xx(stwuct ksz_device *dev)
{
	wetuwn dev->chip_id == KSZ8795_CHIP_ID ||
	       dev->chip_id == KSZ8794_CHIP_ID ||
	       dev->chip_id == KSZ8765_CHIP_ID;
}

static inwine boow ksz_is_ksz88x3(stwuct ksz_device *dev)
{
	wetuwn dev->chip_id == KSZ8830_CHIP_ID;
}

static inwine int is_wan937x(stwuct ksz_device *dev)
{
	wetuwn dev->chip_id == WAN9370_CHIP_ID ||
		dev->chip_id == WAN9371_CHIP_ID ||
		dev->chip_id == WAN9372_CHIP_ID ||
		dev->chip_id == WAN9373_CHIP_ID ||
		dev->chip_id == WAN9374_CHIP_ID;
}

/* STP State Defines */
#define POWT_TX_ENABWE			BIT(2)
#define POWT_WX_ENABWE			BIT(1)
#define POWT_WEAWN_DISABWE		BIT(0)

/* Switch ID Defines */
#define WEG_CHIP_ID0			0x00

#define SW_FAMIWY_ID_M			GENMASK(15, 8)
#define KSZ87_FAMIWY_ID			0x87
#define KSZ88_FAMIWY_ID			0x88

#define KSZ8_POWT_STATUS_0		0x08
#define KSZ8_POWT_FIBEW_MODE		BIT(7)

#define SW_CHIP_ID_M			GENMASK(7, 4)
#define KSZ87_CHIP_ID_94		0x6
#define KSZ87_CHIP_ID_95		0x9
#define KSZ88_CHIP_ID_63		0x3

#define SW_WEV_ID_M			GENMASK(7, 4)

/* KSZ9893, KSZ9563, KSZ8563 specific wegistew  */
#define WEG_CHIP_ID4			0x0f
#define SKU_ID_KSZ8563			0x3c
#define SKU_ID_KSZ9563			0x1c

/* Dwivew set switch bwoadcast stowm pwotection at 10% wate. */
#define BWOADCAST_STOWM_PWOT_WATE	10

/* 148,800 fwames * 67 ms / 100 */
#define BWOADCAST_STOWM_VAWUE		9969

#define BWOADCAST_STOWM_WATE_HI		0x07
#define BWOADCAST_STOWM_WATE_WO		0xFF
#define BWOADCAST_STOWM_WATE		0x07FF

#define MUWTICAST_STOWM_DISABWE		BIT(6)

#define SW_STAWT			0x01

/* xMII configuwation */
#define P_MII_DUPWEX_M			BIT(6)
#define P_MII_100MBIT_M			BIT(4)

#define P_GMII_1GBIT_M			BIT(6)
#define P_WGMII_ID_IG_ENABWE		BIT(4)
#define P_WGMII_ID_EG_ENABWE		BIT(3)
#define P_MII_MAC_MODE			BIT(2)
#define P_MII_SEW_M			0x3

/* Intewwupt */
#define WEG_SW_POWT_INT_STATUS__1	0x001B
#define WEG_SW_POWT_INT_MASK__1		0x001F

#define WEG_POWT_INT_STATUS		0x001B
#define WEG_POWT_INT_MASK		0x001F

#define POWT_SWC_PHY_INT		1
#define POWT_SWC_PTP_INT		2

#define KSZ8795_HUGE_PACKET_SIZE	2000
#define KSZ8863_HUGE_PACKET_SIZE	1916
#define KSZ8863_NOWMAW_PACKET_SIZE	1536
#define KSZ8_WEGAW_PACKET_SIZE		1518
#define KSZ9477_MAX_FWAME_SIZE		9000

#define KSZ8873_WEG_GWOBAW_CTWW_12	0x0e
/* Dwive Stwength of I/O Pad
 * 0: 8mA, 1: 16mA
 */
#define KSZ8873_DWIVE_STWENGTH_16MA	BIT(6)

#define KSZ8795_WEG_SW_CTWW_20		0xa3
#define KSZ9477_WEG_SW_IO_STWENGTH	0x010d
#define SW_DWIVE_STWENGTH_M		0x7
#define SW_DWIVE_STWENGTH_2MA		0
#define SW_DWIVE_STWENGTH_4MA		1
#define SW_DWIVE_STWENGTH_8MA		2
#define SW_DWIVE_STWENGTH_12MA		3
#define SW_DWIVE_STWENGTH_16MA		4
#define SW_DWIVE_STWENGTH_20MA		5
#define SW_DWIVE_STWENGTH_24MA		6
#define SW_DWIVE_STWENGTH_28MA		7
#define SW_HI_SPEED_DWIVE_STWENGTH_S	4
#define SW_WO_SPEED_DWIVE_STWENGTH_S	0

#define KSZ9477_WEG_POWT_OUT_WATE_0	0x0420
#define KSZ9477_OUT_WATE_NO_WIMIT	0

#define KSZ9477_POWT_MWI_TC_MAP__4	0x0808

#define KSZ9477_POWT_TC_MAP_S		4
#define KSZ9477_MAX_TC_PWIO		7

/* CBS wewated wegistews */
#define WEG_POWT_MTI_QUEUE_INDEX__4	0x0900

#define WEG_POWT_MTI_QUEUE_CTWW_0	0x0914

#define MTI_SCHEDUWE_MODE_M		GENMASK(7, 6)
#define MTI_SCHEDUWE_STWICT_PWIO	0
#define MTI_SCHEDUWE_WWW		2
#define MTI_SHAPING_M			GENMASK(5, 4)
#define MTI_SHAPING_OFF			0
#define MTI_SHAPING_SWP			1
#define MTI_SHAPING_TIME_AWAWE		2

#define KSZ9477_POWT_MTI_QUEUE_CTWW_1	0x0915
#define KSZ9477_DEFAUWT_WWW_WEIGHT	1

#define WEG_POWT_MTI_HI_WATEW_MAWK	0x0916
#define WEG_POWT_MTI_WO_WATEW_MAWK	0x0918

/* Wegmap tabwes genewation */
#define KSZ_SPI_OP_WD		3
#define KSZ_SPI_OP_WW		2

#define swabnot_used(x)		0

#define KSZ_SPI_OP_FWAG_MASK(opcode, swp, wegbits, wegpad)		\
	swab##swp((opcode) << ((wegbits) + (wegpad)))

#define KSZ_WEGMAP_ENTWY(width, swp, wegbits, wegpad, wegawign)		\
	{								\
		.name = #width,						\
		.vaw_bits = (width),					\
		.weg_stwide = 1,					\
		.weg_bits = (wegbits) + (wegawign),			\
		.pad_bits = (wegpad),					\
		.max_wegistew = BIT(wegbits) - 1,			\
		.cache_type = WEGCACHE_NONE,				\
		.wead_fwag_mask =					\
			KSZ_SPI_OP_FWAG_MASK(KSZ_SPI_OP_WD, swp,	\
					     wegbits, wegpad),		\
		.wwite_fwag_mask =					\
			KSZ_SPI_OP_FWAG_MASK(KSZ_SPI_OP_WW, swp,	\
					     wegbits, wegpad),		\
		.wock = ksz_wegmap_wock,				\
		.unwock = ksz_wegmap_unwock,				\
		.weg_fowmat_endian = WEGMAP_ENDIAN_BIG,			\
		.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG			\
	}

#define KSZ_WEGMAP_TABWE(ksz, swp, wegbits, wegpad, wegawign)		\
	static const stwuct wegmap_config ksz##_wegmap_config[] = {	\
		[KSZ_WEGMAP_8] = KSZ_WEGMAP_ENTWY(8, swp, (wegbits), (wegpad), (wegawign)), \
		[KSZ_WEGMAP_16] = KSZ_WEGMAP_ENTWY(16, swp, (wegbits), (wegpad), (wegawign)), \
		[KSZ_WEGMAP_32] = KSZ_WEGMAP_ENTWY(32, swp, (wegbits), (wegpad), (wegawign)), \
	}

#endif
