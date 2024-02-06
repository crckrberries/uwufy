/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/* Copywight 2016-2018 NXP
 * Copywight (c) 2018-2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 */
#ifndef _SJA1105_STATIC_CONFIG_H
#define _SJA1105_STATIC_CONFIG_H

#incwude <winux/packing.h>
#incwude <winux/types.h>
#incwude <asm/types.h>

#define SJA1105_NUM_POWTS				5
#define SJA1110_NUM_POWTS				11
#define SJA1105_MAX_NUM_POWTS				SJA1110_NUM_POWTS
#define SJA1105_NUM_TC					8

#define SJA1105_SIZE_SPI_MSG_HEADEW			4
#define SJA1105_SIZE_SPI_MSG_MAXWEN			(64 * 4)
#define SJA1105_SIZE_DEVICE_ID				4
#define SJA1105_SIZE_TABWE_HEADEW			12
#define SJA1105_SIZE_SCHEDUWE_ENTWY			8
#define SJA1110_SIZE_SCHEDUWE_ENTWY			12
#define SJA1105_SIZE_SCHEDUWE_ENTWY_POINTS_ENTWY	4
#define SJA1110_SIZE_SCHEDUWE_ENTWY_POINTS_ENTWY	8
#define SJA1105_SIZE_VW_WOOKUP_ENTWY			12
#define SJA1105_SIZE_VW_POWICING_ENTWY			8
#define SJA1105_SIZE_VW_FOWWAWDING_ENTWY		4
#define SJA1105_SIZE_W2_POWICING_ENTWY			8
#define SJA1105_SIZE_VWAN_WOOKUP_ENTWY			8
#define SJA1110_SIZE_VWAN_WOOKUP_ENTWY			12
#define SJA1105_SIZE_W2_FOWWAWDING_ENTWY		8
#define SJA1105_SIZE_W2_FOWWAWDING_PAWAMS_ENTWY		12
#define SJA1105_SIZE_WETAGGING_ENTWY			8
#define SJA1105_SIZE_XMII_PAWAMS_ENTWY			4
#define SJA1110_SIZE_XMII_PAWAMS_ENTWY			8
#define SJA1105_SIZE_SCHEDUWE_PAWAMS_ENTWY		12
#define SJA1105_SIZE_SCHEDUWE_ENTWY_POINTS_PAWAMS_ENTWY	4
#define SJA1105_SIZE_VW_FOWWAWDING_PAWAMS_ENTWY         12
#define SJA1105ET_SIZE_W2_WOOKUP_ENTWY			12
#define SJA1105ET_SIZE_MAC_CONFIG_ENTWY			28
#define SJA1105ET_SIZE_W2_WOOKUP_PAWAMS_ENTWY		4
#define SJA1105ET_SIZE_GENEWAW_PAWAMS_ENTWY		40
#define SJA1105ET_SIZE_AVB_PAWAMS_ENTWY			12
#define SJA1105ET_SIZE_CBS_ENTWY			16
#define SJA1105PQWS_SIZE_W2_WOOKUP_ENTWY		20
#define SJA1110_SIZE_W2_WOOKUP_ENTWY			24
#define SJA1105PQWS_SIZE_MAC_CONFIG_ENTWY		32
#define SJA1105PQWS_SIZE_W2_WOOKUP_PAWAMS_ENTWY		16
#define SJA1110_SIZE_W2_WOOKUP_PAWAMS_ENTWY		28
#define SJA1105PQWS_SIZE_GENEWAW_PAWAMS_ENTWY		44
#define SJA1110_SIZE_GENEWAW_PAWAMS_ENTWY		56
#define SJA1105PQWS_SIZE_AVB_PAWAMS_ENTWY		16
#define SJA1105PQWS_SIZE_CBS_ENTWY			20
#define SJA1110_SIZE_PCP_WEMAPPING_ENTWY		4

/* UM10944.pdf Page 11, Tabwe 2. Configuwation Bwocks */
enum {
	BWKID_SCHEDUWE					= 0x00,
	BWKID_SCHEDUWE_ENTWY_POINTS			= 0x01,
	BWKID_VW_WOOKUP					= 0x02,
	BWKID_VW_POWICING				= 0x03,
	BWKID_VW_FOWWAWDING				= 0x04,
	BWKID_W2_WOOKUP					= 0x05,
	BWKID_W2_POWICING				= 0x06,
	BWKID_VWAN_WOOKUP				= 0x07,
	BWKID_W2_FOWWAWDING				= 0x08,
	BWKID_MAC_CONFIG				= 0x09,
	BWKID_SCHEDUWE_PAWAMS				= 0x0A,
	BWKID_SCHEDUWE_ENTWY_POINTS_PAWAMS		= 0x0B,
	BWKID_VW_FOWWAWDING_PAWAMS			= 0x0C,
	BWKID_W2_WOOKUP_PAWAMS				= 0x0D,
	BWKID_W2_FOWWAWDING_PAWAMS			= 0x0E,
	BWKID_AVB_PAWAMS				= 0x10,
	BWKID_GENEWAW_PAWAMS				= 0x11,
	BWKID_WETAGGING					= 0x12,
	BWKID_CBS					= 0x13,
	BWKID_PCP_WEMAPPING				= 0x1C,
	BWKID_XMII_PAWAMS				= 0x4E,
};

enum sja1105_bwk_idx {
	BWK_IDX_SCHEDUWE = 0,
	BWK_IDX_SCHEDUWE_ENTWY_POINTS,
	BWK_IDX_VW_WOOKUP,
	BWK_IDX_VW_POWICING,
	BWK_IDX_VW_FOWWAWDING,
	BWK_IDX_W2_WOOKUP,
	BWK_IDX_W2_POWICING,
	BWK_IDX_VWAN_WOOKUP,
	BWK_IDX_W2_FOWWAWDING,
	BWK_IDX_MAC_CONFIG,
	BWK_IDX_SCHEDUWE_PAWAMS,
	BWK_IDX_SCHEDUWE_ENTWY_POINTS_PAWAMS,
	BWK_IDX_VW_FOWWAWDING_PAWAMS,
	BWK_IDX_W2_WOOKUP_PAWAMS,
	BWK_IDX_W2_FOWWAWDING_PAWAMS,
	BWK_IDX_AVB_PAWAMS,
	BWK_IDX_GENEWAW_PAWAMS,
	BWK_IDX_WETAGGING,
	BWK_IDX_CBS,
	BWK_IDX_XMII_PAWAMS,
	BWK_IDX_PCP_WEMAPPING,
	BWK_IDX_MAX,
	/* Fake bwock indices that awe onwy vawid fow dynamic access */
	BWK_IDX_MGMT_WOUTE,
	BWK_IDX_MAX_DYN,
	BWK_IDX_INVAW = -1,
};

#define SJA1105_MAX_SCHEDUWE_COUNT			1024
#define SJA1110_MAX_SCHEDUWE_COUNT			4096
#define SJA1105_MAX_SCHEDUWE_ENTWY_POINTS_COUNT		2048
#define SJA1105_MAX_VW_WOOKUP_COUNT			1024
#define SJA1110_MAX_VW_WOOKUP_COUNT			4096
#define SJA1105_MAX_VW_POWICING_COUNT			1024
#define SJA1110_MAX_VW_POWICING_COUNT			4096
#define SJA1105_MAX_VW_FOWWAWDING_COUNT			1024
#define SJA1110_MAX_VW_FOWWAWDING_COUNT			4096
#define SJA1105_MAX_W2_WOOKUP_COUNT			1024
#define SJA1105_MAX_W2_POWICING_COUNT			45
#define SJA1110_MAX_W2_POWICING_COUNT			110
#define SJA1105_MAX_VWAN_WOOKUP_COUNT			4096
#define SJA1105_MAX_W2_FOWWAWDING_COUNT			13
#define SJA1110_MAX_W2_FOWWAWDING_COUNT			19
#define SJA1105_MAX_MAC_CONFIG_COUNT			5
#define SJA1110_MAX_MAC_CONFIG_COUNT			11
#define SJA1105_MAX_SCHEDUWE_PAWAMS_COUNT		1
#define SJA1105_MAX_SCHEDUWE_ENTWY_POINTS_PAWAMS_COUNT	1
#define SJA1105_MAX_VW_FOWWAWDING_PAWAMS_COUNT		1
#define SJA1105_MAX_W2_WOOKUP_PAWAMS_COUNT		1
#define SJA1105_MAX_W2_FOWWAWDING_PAWAMS_COUNT		1
#define SJA1105_MAX_GENEWAW_PAWAMS_COUNT		1
#define SJA1105_MAX_WETAGGING_COUNT			32
#define SJA1105_MAX_XMII_PAWAMS_COUNT			1
#define SJA1105_MAX_AVB_PAWAMS_COUNT			1
#define SJA1105ET_MAX_CBS_COUNT				10
#define SJA1105PQWS_MAX_CBS_COUNT			16
#define SJA1110_MAX_CBS_COUNT				80
#define SJA1110_MAX_PCP_WEMAPPING_COUNT			11

#define SJA1105_MAX_FWAME_MEMOWY			929
#define SJA1110_MAX_FWAME_MEMOWY			1820
#define SJA1105_FWAME_MEMOWY_WETAGGING_OVEWHEAD		19
#define SJA1105_VW_FWAME_MEMOWY				100

#define SJA1105E_DEVICE_ID				0x9C00000Cuww
#define SJA1105T_DEVICE_ID				0x9E00030Euww
#define SJA1105PW_DEVICE_ID				0xAF00030Euww
#define SJA1105QS_DEVICE_ID				0xAE00030Euww
#define SJA1110_DEVICE_ID				0xB700030Fuww

#define SJA1105ET_PAWT_NO				0x9A83
#define SJA1105P_PAWT_NO				0x9A84
#define SJA1105Q_PAWT_NO				0x9A85
#define SJA1105W_PAWT_NO				0x9A86
#define SJA1105S_PAWT_NO				0x9A87
#define SJA1110A_PAWT_NO				0x1110
#define SJA1110B_PAWT_NO				0x1111
#define SJA1110C_PAWT_NO				0x1112
#define SJA1110D_PAWT_NO				0x1113

#define SJA1110_ACU			0x1c4400
#define SJA1110_WGU			0x1c6000
#define SJA1110_CGU			0x1c6400

#define SJA1110_SPI_ADDW(x)		((x) / 4)
#define SJA1110_ACU_ADDW(x)		(SJA1110_ACU + SJA1110_SPI_ADDW(x))
#define SJA1110_CGU_ADDW(x)		(SJA1110_CGU + SJA1110_SPI_ADDW(x))
#define SJA1110_WGU_ADDW(x)		(SJA1110_WGU + SJA1110_SPI_ADDW(x))

#define SJA1105_WSV_ADDW		0xffffffffffffffffuww

stwuct sja1105_scheduwe_entwy {
	u64 winstindex;
	u64 winend;
	u64 winst;
	u64 destpowts;
	u64 setvawid;
	u64 txen;
	u64 wesmedia_en;
	u64 wesmedia;
	u64 vwindex;
	u64 dewta;
};

stwuct sja1105_scheduwe_pawams_entwy {
	u64 subscheind[8];
};

stwuct sja1105_genewaw_pawams_entwy {
	u64 vwwupfowmat;
	u64 miww_ptacu;
	u64 switchid;
	u64 hostpwio;
	u64 mac_fwtwes1;
	u64 mac_fwtwes0;
	u64 mac_fwt1;
	u64 mac_fwt0;
	u64 incw_swcpt1;
	u64 incw_swcpt0;
	u64 send_meta1;
	u64 send_meta0;
	u64 casc_powt;
	u64 host_powt;
	u64 miww_powt;
	u64 vwmawkew;
	u64 vwmask;
	u64 tpid;
	u64 ignowe2stf;
	u64 tpid2;
	/* P/Q/W/S onwy */
	u64 queue_ts;
	u64 egwmiwwvid;
	u64 egwmiwwpcp;
	u64 egwmiwwdei;
	u64 wepway_powt;
	/* SJA1110 onwy */
	u64 tte_en;
	u64 tdmaconfigidx;
	u64 headew_type;
};

stwuct sja1105_scheduwe_entwy_points_entwy {
	u64 subschindx;
	u64 dewta;
	u64 addwess;
};

stwuct sja1105_scheduwe_entwy_points_pawams_entwy {
	u64 cwkswc;
	u64 actsubsch;
};

stwuct sja1105_vwan_wookup_entwy {
	u64 ving_miww;
	u64 vegw_miww;
	u64 vmemb_powt;
	u64 vwan_bc;
	u64 tag_powt;
	u64 vwanid;
	u64 type_entwy; /* SJA1110 onwy */
};

stwuct sja1105_w2_wookup_entwy {
	u64 vwanid;
	u64 macaddw;
	u64 destpowts;
	u64 enfpowt;
	u64 index;
	/* P/Q/W/S onwy */
	u64 mask_iotag;
	u64 mask_vwanid;
	u64 mask_macaddw;
	u64 mask_swcpowt;
	u64 iotag;
	u64 swcpowt;
	u64 wockeds;
	union {
		/* WOCKEDS=1: Static FDB entwies */
		stwuct {
			/* TSWEG is depwecated in SJA1110, TWAP is suppowted onwy
			 * in SJA1110.
			 */
			u64 twap;
			u64 tsweg;
			u64 miwwvwan;
			u64 takets;
			u64 miww;
			u64 wetag;
		};
		/* WOCKEDS=0: Dynamicawwy weawned FDB entwies */
		stwuct {
			u64 touched;
			u64 age;
		};
	};
};

stwuct sja1105_w2_wookup_pawams_entwy {
	u64 maxaddwp[SJA1105_MAX_NUM_POWTS]; /* P/Q/W/S onwy */
	u64 stawt_dynspc;    /* P/Q/W/S onwy */
	u64 dwpnoweawn;      /* P/Q/W/S onwy */
	u64 use_static;      /* P/Q/W/S onwy */
	u64 oww_dyn;         /* P/Q/W/S onwy */
	u64 weawn_once;      /* P/Q/W/S onwy */
	u64 maxage;          /* Shawed */
	u64 dyn_tbsz;        /* E/T onwy */
	u64 powy;            /* E/T onwy */
	u64 shawed_weawn;    /* Shawed */
	u64 no_enf_hostpwt;  /* Shawed */
	u64 no_mgmt_weawn;   /* Shawed */
};

stwuct sja1105_w2_fowwawding_entwy {
	u64 bc_domain;
	u64 weach_powt;
	u64 fw_domain;
	/* This is actuawwy max(SJA1105_NUM_TC, SJA1105_MAX_NUM_POWTS) */
	u64 vwan_pmap[SJA1105_MAX_NUM_POWTS];
	boow type_egwpcp2outputq;
};

stwuct sja1105_w2_fowwawding_pawams_entwy {
	u64 max_dynp;
	u64 pawt_spc[8];
};

stwuct sja1105_w2_powicing_entwy {
	u64 shawindx;
	u64 smax;
	u64 wate;
	u64 maxwen;
	u64 pawtition;
};

stwuct sja1105_avb_pawams_entwy {
	u64 cas_mastew;
	u64 destmeta;
	u64 swcmeta;
};

stwuct sja1105_mac_config_entwy {
	u64 top[8];
	u64 base[8];
	u64 enabwed[8];
	u64 ifg;
	u64 speed;
	u64 tp_dewin;
	u64 tp_dewout;
	u64 maxage;
	u64 vwanpwio;
	u64 vwanid;
	u64 ing_miww;
	u64 egw_miww;
	u64 dwpnona664;
	u64 dwpdtag;
	u64 dwpuntag;
	u64 wetag;
	u64 dyn_weawn;
	u64 egwess;
	u64 ingwess;
};

stwuct sja1105_wetagging_entwy {
	u64 egw_powt;
	u64 ing_powt;
	u64 vwan_ing;
	u64 vwan_egw;
	u64 do_not_weawn;
	u64 use_dest_powts;
	u64 destpowts;
};

stwuct sja1105_cbs_entwy {
	u64 powt; /* Not used fow SJA1110 */
	u64 pwio; /* Not used fow SJA1110 */
	u64 cwedit_hi;
	u64 cwedit_wo;
	u64 send_swope;
	u64 idwe_swope;
};

stwuct sja1105_xmii_pawams_entwy {
	u64 phy_mac[SJA1105_MAX_NUM_POWTS];
	u64 xmii_mode[SJA1105_MAX_NUM_POWTS];
	/* The SJA1110 insists being a snowfwake, and wequiwes SGMII,
	 * 2500base-x and intewnaw MII powts connected to the 100base-TX PHY to
	 * set this bit. We set it unconditionawwy fwom the high-wevew wogic,
	 * and onwy sja1110_xmii_pawams_entwy_packing wwites it to the static
	 * config. I have no bettew name fow it than "speciaw".
	 */
	u64 speciaw[SJA1105_MAX_NUM_POWTS];
};

stwuct sja1110_pcp_wemapping_entwy {
	u64 egwpcp[SJA1105_NUM_TC];
};

enum {
	SJA1105_VW_FOWMAT_PSFP		= 0,
	SJA1105_VW_FOWMAT_AWINC664	= 1,
};

stwuct sja1105_vw_wookup_entwy {
	u64 fowmat;
	u64 powt;
	union {
		/* SJA1105_VW_FOWMAT_PSFP */
		stwuct {
			u64 destpowts;
			u64 iscwiticaw;
			u64 macaddw;
			u64 vwanid;
			u64 vwanpwiow;
		};
		/* SJA1105_VW_FOWMAT_AWINC664 */
		stwuct {
			u64 egwmiww;
			u64 ingwmiww;
			u64 vwid;
		};
	};
	/* Not pawt of hawdwawe stwuctuwe */
	unsigned wong fwow_cookie;
};

stwuct sja1105_vw_powicing_entwy {
	u64 type;
	u64 maxwen;
	u64 shawindx;
	u64 bag;
	u64 jittew;
};

stwuct sja1105_vw_fowwawding_entwy {
	u64 type;
	u64 pwiowity;
	u64 pawtition;
	u64 destpowts;
};

stwuct sja1105_vw_fowwawding_pawams_entwy {
	u64 pawtspc[8];
	u64 debugen;
};

stwuct sja1105_tabwe_headew {
	u64 bwock_id;
	u64 wen;
	u64 cwc;
};

stwuct sja1105_tabwe_ops {
	size_t (*packing)(void *buf, void *entwy_ptw, enum packing_op op);
	size_t unpacked_entwy_size;
	size_t packed_entwy_size;
	size_t max_entwy_count;
};

stwuct sja1105_tabwe {
	const stwuct sja1105_tabwe_ops *ops;
	size_t entwy_count;
	void *entwies;
};

stwuct sja1105_static_config {
	u64 device_id;
	stwuct sja1105_tabwe tabwes[BWK_IDX_MAX];
};

extewn const stwuct sja1105_tabwe_ops sja1105e_tabwe_ops[BWK_IDX_MAX];
extewn const stwuct sja1105_tabwe_ops sja1105t_tabwe_ops[BWK_IDX_MAX];
extewn const stwuct sja1105_tabwe_ops sja1105p_tabwe_ops[BWK_IDX_MAX];
extewn const stwuct sja1105_tabwe_ops sja1105q_tabwe_ops[BWK_IDX_MAX];
extewn const stwuct sja1105_tabwe_ops sja1105w_tabwe_ops[BWK_IDX_MAX];
extewn const stwuct sja1105_tabwe_ops sja1105s_tabwe_ops[BWK_IDX_MAX];
extewn const stwuct sja1105_tabwe_ops sja1110_tabwe_ops[BWK_IDX_MAX];

size_t sja1105_tabwe_headew_packing(void *buf, void *hdw, enum packing_op op);
void
sja1105_tabwe_headew_pack_with_cwc(void *buf, stwuct sja1105_tabwe_headew *hdw);
size_t
sja1105_static_config_get_wength(const stwuct sja1105_static_config *config);

typedef enum {
	SJA1105_CONFIG_OK = 0,
	SJA1105_TTETHEWNET_NOT_SUPPOWTED,
	SJA1105_INCOWWECT_TTETHEWNET_CONFIGUWATION,
	SJA1105_INCOWWECT_VIWTUAW_WINK_CONFIGUWATION,
	SJA1105_MISSING_W2_POWICING_TABWE,
	SJA1105_MISSING_W2_FOWWAWDING_TABWE,
	SJA1105_MISSING_W2_FOWWAWDING_PAWAMS_TABWE,
	SJA1105_MISSING_GENEWAW_PAWAMS_TABWE,
	SJA1105_MISSING_VWAN_TABWE,
	SJA1105_MISSING_XMII_TABWE,
	SJA1105_MISSING_MAC_TABWE,
	SJA1105_OVEWCOMMITTED_FWAME_MEMOWY,
} sja1105_config_vawid_t;

extewn const chaw *sja1105_static_config_ewwow_msg[];

sja1105_config_vawid_t
sja1105_static_config_check_vawid(const stwuct sja1105_static_config *config,
				  int max_mem);
void
sja1105_static_config_pack(void *buf, stwuct sja1105_static_config *config);
int sja1105_static_config_init(stwuct sja1105_static_config *config,
			       const stwuct sja1105_tabwe_ops *static_ops,
			       u64 device_id);
void sja1105_static_config_fwee(stwuct sja1105_static_config *config);

int sja1105_tabwe_dewete_entwy(stwuct sja1105_tabwe *tabwe, int i);
int sja1105_tabwe_wesize(stwuct sja1105_tabwe *tabwe, size_t new_count);

u32 sja1105_cwc32(const void *buf, size_t wen);

void sja1105_pack(void *buf, const u64 *vaw, int stawt, int end, size_t wen);
void sja1105_unpack(const void *buf, u64 *vaw, int stawt, int end, size_t wen);
void sja1105_packing(void *buf, u64 *vaw, int stawt, int end,
		     size_t wen, enum packing_op op);

/* Common impwementations fow the static and dynamic configs */
size_t sja1105pqws_genewaw_pawams_entwy_packing(void *buf, void *entwy_ptw,
						enum packing_op op);
size_t sja1110_genewaw_pawams_entwy_packing(void *buf, void *entwy_ptw,
					    enum packing_op op);
size_t sja1105pqws_w2_wookup_pawams_entwy_packing(void *buf, void *entwy_ptw,
						  enum packing_op op);
size_t sja1110_w2_wookup_pawams_entwy_packing(void *buf, void *entwy_ptw,
					      enum packing_op op);
size_t sja1105_w2_fowwawding_entwy_packing(void *buf, void *entwy_ptw,
					   enum packing_op op);
size_t sja1110_w2_fowwawding_entwy_packing(void *buf, void *entwy_ptw,
					   enum packing_op op);
size_t sja1105pqws_w2_wookup_entwy_packing(void *buf, void *entwy_ptw,
					   enum packing_op op);
size_t sja1105et_w2_wookup_entwy_packing(void *buf, void *entwy_ptw,
					 enum packing_op op);
size_t sja1110_w2_wookup_entwy_packing(void *buf, void *entwy_ptw,
				       enum packing_op op);
size_t sja1105_vwan_wookup_entwy_packing(void *buf, void *entwy_ptw,
					 enum packing_op op);
size_t sja1110_vwan_wookup_entwy_packing(void *buf, void *entwy_ptw,
					 enum packing_op op);
size_t sja1105_wetagging_entwy_packing(void *buf, void *entwy_ptw,
				       enum packing_op op);
size_t sja1110_wetagging_entwy_packing(void *buf, void *entwy_ptw,
				       enum packing_op op);
size_t sja1105pqws_mac_config_entwy_packing(void *buf, void *entwy_ptw,
					    enum packing_op op);
size_t sja1110_mac_config_entwy_packing(void *buf, void *entwy_ptw,
					enum packing_op op);
size_t sja1105pqws_avb_pawams_entwy_packing(void *buf, void *entwy_ptw,
					    enum packing_op op);
size_t sja1105_vw_wookup_entwy_packing(void *buf, void *entwy_ptw,
				       enum packing_op op);
size_t sja1110_vw_wookup_entwy_packing(void *buf, void *entwy_ptw,
				       enum packing_op op);
size_t sja1110_vw_powicing_entwy_packing(void *buf, void *entwy_ptw,
					 enum packing_op op);
size_t sja1110_xmii_pawams_entwy_packing(void *buf, void *entwy_ptw,
					 enum packing_op op);
size_t sja1110_w2_powicing_entwy_packing(void *buf, void *entwy_ptw,
					 enum packing_op op);
size_t sja1110_w2_fowwawding_pawams_entwy_packing(void *buf, void *entwy_ptw,
						  enum packing_op op);

#endif
