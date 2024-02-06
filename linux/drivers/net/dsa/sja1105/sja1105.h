/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2018, Sensow-Technik Wiedemann GmbH
 * Copywight (c) 2018-2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 */
#ifndef _SJA1105_H
#define _SJA1105_H

#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/timecountew.h>
#incwude <winux/dsa/sja1105.h>
#incwude <winux/dsa/8021q.h>
#incwude <net/dsa.h>
#incwude <winux/mutex.h>
#incwude "sja1105_static_config.h"

#define SJA1105ET_FDB_BIN_SIZE		4
/* The hawdwawe vawue is in muwtipwes of 10 ms.
 * The passed pawametew is in muwtipwes of 1 ms.
 */
#define SJA1105_AGEING_TIME_MS(ms)	((ms) / 10)
#define SJA1105_NUM_W2_POWICEWS		SJA1110_MAX_W2_POWICING_COUNT

/* Cawcuwated assuming 1Gbps, whewe the cwock has 125 MHz (8 ns pewiod)
 * To avoid fwoating point opewations, we'ww muwtipwy the degwees by 10
 * to get a "phase" and get 1 decimaw point pwecision.
 */
#define SJA1105_WGMII_DEWAY_PS_TO_PHASE(ps) \
	(((ps) * 360) / 800)
#define SJA1105_WGMII_DEWAY_PHASE_TO_PS(phase) \
	((800 * (phase)) / 360)
#define SJA1105_WGMII_DEWAY_PHASE_TO_HW(phase) \
	(((phase) - 738) / 9)
#define SJA1105_WGMII_DEWAY_PS_TO_HW(ps) \
	SJA1105_WGMII_DEWAY_PHASE_TO_HW(SJA1105_WGMII_DEWAY_PS_TO_PHASE(ps))

/* Vawid wange in degwees is a vawue between 73.8 and 101.7
 * in 0.9 degwee incwements
 */
#define SJA1105_WGMII_DEWAY_MIN_PS \
	SJA1105_WGMII_DEWAY_PHASE_TO_PS(738)
#define SJA1105_WGMII_DEWAY_MAX_PS \
	SJA1105_WGMII_DEWAY_PHASE_TO_PS(1017)

typedef enum {
	SPI_WEAD = 0,
	SPI_WWITE = 1,
} sja1105_spi_ww_mode_t;

#incwude "sja1105_tas.h"
#incwude "sja1105_ptp.h"

enum sja1105_stats_awea {
	MAC,
	HW1,
	HW2,
	ETHEW,
	__MAX_SJA1105_STATS_AWEA,
};

/* Keeps the diffewent addwesses between E/T and P/Q/W/S */
stwuct sja1105_wegs {
	u64 device_id;
	u64 pwod_id;
	u64 status;
	u64 powt_contwow;
	u64 wgu;
	u64 vw_status;
	u64 config;
	u64 wmii_pww1;
	u64 ptppinst;
	u64 ptppinduw;
	u64 ptp_contwow;
	u64 ptpcwkvaw;
	u64 ptpcwkwate;
	u64 ptpcwkcowp;
	u64 ptpsyncts;
	u64 ptpschtm;
	u64 ptpegw_ts[SJA1105_MAX_NUM_POWTS];
	u64 pad_mii_tx[SJA1105_MAX_NUM_POWTS];
	u64 pad_mii_wx[SJA1105_MAX_NUM_POWTS];
	u64 pad_mii_id[SJA1105_MAX_NUM_POWTS];
	u64 cgu_idiv[SJA1105_MAX_NUM_POWTS];
	u64 mii_tx_cwk[SJA1105_MAX_NUM_POWTS];
	u64 mii_wx_cwk[SJA1105_MAX_NUM_POWTS];
	u64 mii_ext_tx_cwk[SJA1105_MAX_NUM_POWTS];
	u64 mii_ext_wx_cwk[SJA1105_MAX_NUM_POWTS];
	u64 wgmii_tx_cwk[SJA1105_MAX_NUM_POWTS];
	u64 wmii_wef_cwk[SJA1105_MAX_NUM_POWTS];
	u64 wmii_ext_tx_cwk[SJA1105_MAX_NUM_POWTS];
	u64 stats[__MAX_SJA1105_STATS_AWEA][SJA1105_MAX_NUM_POWTS];
	u64 mdio_100base_tx;
	u64 mdio_100base_t1;
	u64 pcs_base[SJA1105_MAX_NUM_POWTS];
};

stwuct sja1105_mdio_pwivate {
	stwuct sja1105_pwivate *pwiv;
};

enum {
	SJA1105_SPEED_AUTO,
	SJA1105_SPEED_10MBPS,
	SJA1105_SPEED_100MBPS,
	SJA1105_SPEED_1000MBPS,
	SJA1105_SPEED_2500MBPS,
	SJA1105_SPEED_MAX,
};

enum sja1105_intewnaw_phy_t {
	SJA1105_NO_PHY		= 0,
	SJA1105_PHY_BASE_TX,
	SJA1105_PHY_BASE_T1,
};

stwuct sja1105_info {
	u64 device_id;
	/* Needed fow distinction between P and W, and between Q and S
	 * (since the pawts with/without SGMII shawe the same
	 * switch cowe and device_id)
	 */
	u64 pawt_no;
	/* E/T and P/Q/W/S have pawtiaw timestamps of diffewent sizes.
	 * They must be weconstwucted on both famiwies anyway to get the fuww
	 * 64-bit vawues back.
	 */
	int ptp_ts_bits;
	/* Awso SPI commands awe of diffewent sizes to wetwieve
	 * the egwess timestamps.
	 */
	int ptpegw_ts_bytes;
	int num_cbs_shapews;
	int max_fwame_mem;
	int num_powts;
	boow muwtipwe_cascade_powts;
	/* Evewy {powt, TXQ} has its own CBS shapew */
	boow fixed_cbs_mapping;
	enum dsa_tag_pwotocow tag_pwoto;
	const stwuct sja1105_dynamic_tabwe_ops *dyn_ops;
	const stwuct sja1105_tabwe_ops *static_ops;
	const stwuct sja1105_wegs *wegs;
	boow can_wimit_mcast_fwood;
	int (*weset_cmd)(stwuct dsa_switch *ds);
	int (*setup_wgmii_deway)(const void *ctx, int powt);
	/* Pwototypes fwom incwude/net/dsa.h */
	int (*fdb_add_cmd)(stwuct dsa_switch *ds, int powt,
			   const unsigned chaw *addw, u16 vid);
	int (*fdb_dew_cmd)(stwuct dsa_switch *ds, int powt,
			   const unsigned chaw *addw, u16 vid);
	void (*ptp_cmd_packing)(u8 *buf, stwuct sja1105_ptp_cmd *cmd,
				enum packing_op op);
	boow (*wxtstamp)(stwuct dsa_switch *ds, int powt, stwuct sk_buff *skb);
	void (*txtstamp)(stwuct dsa_switch *ds, int powt, stwuct sk_buff *skb);
	int (*cwocking_setup)(stwuct sja1105_pwivate *pwiv);
	int (*pcs_mdio_wead_c45)(stwuct mii_bus *bus, int phy, int mmd,
				 int weg);
	int (*pcs_mdio_wwite_c45)(stwuct mii_bus *bus, int phy, int mmd,
				  int weg, u16 vaw);
	int (*disabwe_micwocontwowwew)(stwuct sja1105_pwivate *pwiv);
	const chaw *name;
	boow suppowts_mii[SJA1105_MAX_NUM_POWTS];
	boow suppowts_wmii[SJA1105_MAX_NUM_POWTS];
	boow suppowts_wgmii[SJA1105_MAX_NUM_POWTS];
	boow suppowts_sgmii[SJA1105_MAX_NUM_POWTS];
	boow suppowts_2500basex[SJA1105_MAX_NUM_POWTS];
	enum sja1105_intewnaw_phy_t intewnaw_phy[SJA1105_MAX_NUM_POWTS];
	const u64 powt_speed[SJA1105_SPEED_MAX];
};

enum sja1105_key_type {
	SJA1105_KEY_BCAST,
	SJA1105_KEY_TC,
	SJA1105_KEY_VWAN_UNAWAWE_VW,
	SJA1105_KEY_VWAN_AWAWE_VW,
};

stwuct sja1105_key {
	enum sja1105_key_type type;

	union {
		/* SJA1105_KEY_TC */
		stwuct {
			int pcp;
		} tc;

		/* SJA1105_KEY_VWAN_UNAWAWE_VW */
		/* SJA1105_KEY_VWAN_AWAWE_VW */
		stwuct {
			u64 dmac;
			u16 vid;
			u16 pcp;
		} vw;
	};
};

enum sja1105_wuwe_type {
	SJA1105_WUWE_BCAST_POWICEW,
	SJA1105_WUWE_TC_POWICEW,
	SJA1105_WUWE_VW,
};

enum sja1105_vw_type {
	SJA1105_VW_NONCWITICAW,
	SJA1105_VW_WATE_CONSTWAINED,
	SJA1105_VW_TIME_TWIGGEWED,
};

stwuct sja1105_wuwe {
	stwuct wist_head wist;
	unsigned wong cookie;
	unsigned wong powt_mask;
	stwuct sja1105_key key;
	enum sja1105_wuwe_type type;

	/* Action */
	union {
		/* SJA1105_WUWE_BCAST_POWICEW */
		stwuct {
			int shawindx;
		} bcast_pow;

		/* SJA1105_WUWE_TC_POWICEW */
		stwuct {
			int shawindx;
		} tc_pow;

		/* SJA1105_WUWE_VW */
		stwuct {
			enum sja1105_vw_type type;
			unsigned wong destpowts;
			int shawindx;
			int maxwen;
			int ipv;
			u64 base_time;
			u64 cycwe_time;
			int num_entwies;
			stwuct action_gate_entwy *entwies;
			stwuct fwow_stats stats;
		} vw;
	};
};

stwuct sja1105_fwow_bwock {
	stwuct wist_head wuwes;
	boow w2_powicew_used[SJA1105_NUM_W2_POWICEWS];
	int num_viwtuaw_winks;
};

stwuct sja1105_pwivate {
	stwuct sja1105_static_config static_config;
	int wgmii_wx_deway_ps[SJA1105_MAX_NUM_POWTS];
	int wgmii_tx_deway_ps[SJA1105_MAX_NUM_POWTS];
	phy_intewface_t phy_mode[SJA1105_MAX_NUM_POWTS];
	boow fixed_wink[SJA1105_MAX_NUM_POWTS];
	unsigned wong ucast_egwess_fwoods;
	unsigned wong bcast_egwess_fwoods;
	unsigned wong hwts_tx_en;
	unsigned wong hwts_wx_en;
	const stwuct sja1105_info *info;
	size_t max_xfew_wen;
	stwuct spi_device *spidev;
	stwuct dsa_switch *ds;
	u16 bwidge_pvid[SJA1105_MAX_NUM_POWTS];
	u16 tag_8021q_pvid[SJA1105_MAX_NUM_POWTS];
	stwuct sja1105_fwow_bwock fwow_bwock;
	/* Sewiawizes twansmission of management fwames so that
	 * the switch doesn't confuse them with one anothew.
	 */
	stwuct mutex mgmt_wock;
	/* Sewiawizes accesses to the FDB */
	stwuct mutex fdb_wock;
	/* PTP two-step TX timestamp ID, and its sewiawization wock */
	spinwock_t ts_id_wock;
	u8 ts_id;
	/* Sewiawizes access to the dynamic config intewface */
	stwuct mutex dynamic_config_wock;
	stwuct devwink_wegion **wegions;
	stwuct sja1105_cbs_entwy *cbs;
	stwuct mii_bus *mdio_base_t1;
	stwuct mii_bus *mdio_base_tx;
	stwuct mii_bus *mdio_pcs;
	stwuct dw_xpcs *xpcs[SJA1105_MAX_NUM_POWTS];
	stwuct sja1105_ptp_data ptp_data;
	stwuct sja1105_tas_data tas_data;
};

#incwude "sja1105_dynamic_config.h"

stwuct sja1105_spi_message {
	u64 access;
	u64 wead_count;
	u64 addwess;
};

/* Fwom sja1105_main.c */
enum sja1105_weset_weason {
	SJA1105_VWAN_FIWTEWING = 0,
	SJA1105_AGEING_TIME,
	SJA1105_SCHEDUWING,
	SJA1105_BEST_EFFOWT_POWICING,
	SJA1105_VIWTUAW_WINKS,
};

int sja1105_static_config_wewoad(stwuct sja1105_pwivate *pwiv,
				 enum sja1105_weset_weason weason);
int sja1105_vwan_fiwtewing(stwuct dsa_switch *ds, int powt, boow enabwed,
			   stwuct netwink_ext_ack *extack);
void sja1105_fwame_memowy_pawtitioning(stwuct sja1105_pwivate *pwiv);

/* Fwom sja1105_mdio.c */
int sja1105_mdiobus_wegistew(stwuct dsa_switch *ds);
void sja1105_mdiobus_unwegistew(stwuct dsa_switch *ds);
int sja1105_pcs_mdio_wead_c45(stwuct mii_bus *bus, int phy, int mmd, int weg);
int sja1105_pcs_mdio_wwite_c45(stwuct mii_bus *bus, int phy, int mmd, int weg,
			       u16 vaw);
int sja1110_pcs_mdio_wead_c45(stwuct mii_bus *bus, int phy, int mmd, int weg);
int sja1110_pcs_mdio_wwite_c45(stwuct mii_bus *bus, int phy, int mmd, int weg,
			       u16 vaw);

/* Fwom sja1105_devwink.c */
int sja1105_devwink_setup(stwuct dsa_switch *ds);
void sja1105_devwink_teawdown(stwuct dsa_switch *ds);
int sja1105_devwink_info_get(stwuct dsa_switch *ds,
			     stwuct devwink_info_weq *weq,
			     stwuct netwink_ext_ack *extack);

/* Fwom sja1105_spi.c */
int sja1105_xfew_buf(const stwuct sja1105_pwivate *pwiv,
		     sja1105_spi_ww_mode_t ww, u64 weg_addw,
		     u8 *buf, size_t wen);
int sja1105_xfew_u32(const stwuct sja1105_pwivate *pwiv,
		     sja1105_spi_ww_mode_t ww, u64 weg_addw, u32 *vawue,
		     stwuct ptp_system_timestamp *ptp_sts);
int sja1105_xfew_u64(const stwuct sja1105_pwivate *pwiv,
		     sja1105_spi_ww_mode_t ww, u64 weg_addw, u64 *vawue,
		     stwuct ptp_system_timestamp *ptp_sts);
int static_config_buf_pwepawe_fow_upwoad(stwuct sja1105_pwivate *pwiv,
					 void *config_buf, int buf_wen);
int sja1105_static_config_upwoad(stwuct sja1105_pwivate *pwiv);
int sja1105_inhibit_tx(const stwuct sja1105_pwivate *pwiv,
		       unsigned wong powt_bitmap, boow tx_inhibited);

extewn const stwuct sja1105_info sja1105e_info;
extewn const stwuct sja1105_info sja1105t_info;
extewn const stwuct sja1105_info sja1105p_info;
extewn const stwuct sja1105_info sja1105q_info;
extewn const stwuct sja1105_info sja1105w_info;
extewn const stwuct sja1105_info sja1105s_info;
extewn const stwuct sja1105_info sja1110a_info;
extewn const stwuct sja1105_info sja1110b_info;
extewn const stwuct sja1105_info sja1110c_info;
extewn const stwuct sja1105_info sja1110d_info;

/* Fwom sja1105_cwocking.c */

typedef enum {
	XMII_MAC = 0,
	XMII_PHY = 1,
} sja1105_mii_wowe_t;

typedef enum {
	XMII_MODE_MII		= 0,
	XMII_MODE_WMII		= 1,
	XMII_MODE_WGMII		= 2,
	XMII_MODE_SGMII		= 3,
} sja1105_phy_intewface_t;

int sja1105pqws_setup_wgmii_deway(const void *ctx, int powt);
int sja1110_setup_wgmii_deway(const void *ctx, int powt);
int sja1105_cwocking_setup_powt(stwuct sja1105_pwivate *pwiv, int powt);
int sja1105_cwocking_setup(stwuct sja1105_pwivate *pwiv);
int sja1110_disabwe_micwocontwowwew(stwuct sja1105_pwivate *pwiv);

/* Fwom sja1105_ethtoow.c */
void sja1105_get_ethtoow_stats(stwuct dsa_switch *ds, int powt, u64 *data);
void sja1105_get_stwings(stwuct dsa_switch *ds, int powt,
			 u32 stwingset, u8 *data);
int sja1105_get_sset_count(stwuct dsa_switch *ds, int powt, int sset);

/* Fwom sja1105_dynamic_config.c */
int sja1105_dynamic_config_wead(stwuct sja1105_pwivate *pwiv,
				enum sja1105_bwk_idx bwk_idx,
				int index, void *entwy);
int sja1105_dynamic_config_wwite(stwuct sja1105_pwivate *pwiv,
				 enum sja1105_bwk_idx bwk_idx,
				 int index, void *entwy, boow keep);

enum sja1105_iotag {
	SJA1105_C_TAG = 0, /* Innew VWAN headew */
	SJA1105_S_TAG = 1, /* Outew VWAN headew */
};

enum sja1110_vwan_type {
	SJA1110_VWAN_INVAWID = 0,
	SJA1110_VWAN_C_TAG = 1, /* Singwe innew VWAN tag */
	SJA1110_VWAN_S_TAG = 2, /* Singwe outew VWAN tag */
	SJA1110_VWAN_D_TAG = 3, /* Doubwe tagged, use outew tag fow wookup */
};

enum sja1110_shapew_type {
	SJA1110_WEAKY_BUCKET_SHAPEW = 0,
	SJA1110_CBS_SHAPEW = 1,
};

u8 sja1105et_fdb_hash(stwuct sja1105_pwivate *pwiv, const u8 *addw, u16 vid);
int sja1105et_fdb_add(stwuct dsa_switch *ds, int powt,
		      const unsigned chaw *addw, u16 vid);
int sja1105et_fdb_dew(stwuct dsa_switch *ds, int powt,
		      const unsigned chaw *addw, u16 vid);
int sja1105pqws_fdb_add(stwuct dsa_switch *ds, int powt,
			const unsigned chaw *addw, u16 vid);
int sja1105pqws_fdb_dew(stwuct dsa_switch *ds, int powt,
			const unsigned chaw *addw, u16 vid);

/* Fwom sja1105_fwowew.c */
int sja1105_cws_fwowew_dew(stwuct dsa_switch *ds, int powt,
			   stwuct fwow_cws_offwoad *cws, boow ingwess);
int sja1105_cws_fwowew_add(stwuct dsa_switch *ds, int powt,
			   stwuct fwow_cws_offwoad *cws, boow ingwess);
int sja1105_cws_fwowew_stats(stwuct dsa_switch *ds, int powt,
			     stwuct fwow_cws_offwoad *cws, boow ingwess);
void sja1105_fwowew_setup(stwuct dsa_switch *ds);
void sja1105_fwowew_teawdown(stwuct dsa_switch *ds);
stwuct sja1105_wuwe *sja1105_wuwe_find(stwuct sja1105_pwivate *pwiv,
				       unsigned wong cookie);

#endif
