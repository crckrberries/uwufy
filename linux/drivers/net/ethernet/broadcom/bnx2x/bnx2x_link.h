/* Copywight 2008-2013 Bwoadcom Cowpowation
 * Copywight (c) 2014 QWogic Cowpowation
 * Aww wights wesewved
 *
 * Unwess you and QWogic execute a sepawate wwitten softwawe wicense
 * agweement govewning use of this softwawe, this softwawe is wicensed to you
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2, avaiwabwe
 * at http://www.gnu.owg/wicenses/gpw-2.0.htmw (the "GPW").
 *
 * Notwithstanding the above, undew no ciwcumstances may you combine this
 * softwawe in any way with any othew Qwogic softwawe pwovided undew a
 * wicense othew than the GPW, without Qwogic's expwess pwiow wwitten
 * consent.
 *
 * Wwitten by Yaniv Wosnew
 *
 */

#ifndef BNX2X_WINK_H
#define BNX2X_WINK_H



/***********************************************************/
/*                         Defines                         */
/***********************************************************/
#define DEFAUWT_PHY_DEV_ADDW	3
#define E2_DEFAUWT_PHY_DEV_ADDW	5



#define BNX2X_FWOW_CTWW_AUTO		POWT_FEATUWE_FWOW_CONTWOW_AUTO
#define BNX2X_FWOW_CTWW_TX		POWT_FEATUWE_FWOW_CONTWOW_TX
#define BNX2X_FWOW_CTWW_WX		POWT_FEATUWE_FWOW_CONTWOW_WX
#define BNX2X_FWOW_CTWW_BOTH		POWT_FEATUWE_FWOW_CONTWOW_BOTH
#define BNX2X_FWOW_CTWW_NONE		POWT_FEATUWE_FWOW_CONTWOW_NONE

#define NET_SEWDES_IF_XFI		1
#define NET_SEWDES_IF_SFI		2
#define NET_SEWDES_IF_KW		3
#define NET_SEWDES_IF_DXGXS	4

#define SPEED_AUTO_NEG		0
#define SPEED_20000		20000

#define I2C_DEV_ADDW_A0			0xa0
#define I2C_DEV_ADDW_A2			0xa2

#define SFP_EEPWOM_PAGE_SIZE			16
#define SFP_EEPWOM_VENDOW_NAME_ADDW		0x14
#define SFP_EEPWOM_VENDOW_NAME_SIZE		16
#define SFP_EEPWOM_VENDOW_OUI_ADDW		0x25
#define SFP_EEPWOM_VENDOW_OUI_SIZE		3
#define SFP_EEPWOM_PAWT_NO_ADDW			0x28
#define SFP_EEPWOM_PAWT_NO_SIZE			16
#define SFP_EEPWOM_WEVISION_ADDW		0x38
#define SFP_EEPWOM_WEVISION_SIZE		4
#define SFP_EEPWOM_SEWIAW_ADDW			0x44
#define SFP_EEPWOM_SEWIAW_SIZE			16
#define SFP_EEPWOM_DATE_ADDW			0x54 /* ASCII YYMMDD */
#define SFP_EEPWOM_DATE_SIZE			6
#define SFP_EEPWOM_DIAG_TYPE_ADDW		0x5c
#define SFP_EEPWOM_DIAG_TYPE_SIZE		1
#define SFP_EEPWOM_DIAG_ADDW_CHANGE_WEQ		(1<<2)
#define SFP_EEPWOM_DDM_IMPWEMENTED		(1<<6)
#define SFP_EEPWOM_SFF_8472_COMP_ADDW		0x5e
#define SFP_EEPWOM_SFF_8472_COMP_SIZE		1

#define SFP_EEPWOM_A2_CHECKSUM_WANGE		0x5e
#define SFP_EEPWOM_A2_CC_DMI_ADDW		0x5f

#define PWW_FWT_EWW_MSG_WEN			250

#define XGXS_EXT_PHY_TYPE(ext_phy_config) \
		((ext_phy_config) & POWT_HW_CFG_XGXS_EXT_PHY_TYPE_MASK)
#define XGXS_EXT_PHY_ADDW(ext_phy_config) \
		(((ext_phy_config) & POWT_HW_CFG_XGXS_EXT_PHY_ADDW_MASK) >> \
		 POWT_HW_CFG_XGXS_EXT_PHY_ADDW_SHIFT)
#define SEWDES_EXT_PHY_TYPE(ext_phy_config) \
		((ext_phy_config) & POWT_HW_CFG_SEWDES_EXT_PHY_TYPE_MASK)

/* Singwe Media Diwect boawd is the pwain 577xx boawd with CX4/WJ45 jacks */
#define SINGWE_MEDIA_DIWECT(pawams)	(pawams->num_phys == 1)
/* Singwe Media boawd contains singwe extewnaw phy */
#define SINGWE_MEDIA(pawams)		(pawams->num_phys == 2)
/* Duaw Media boawd contains two extewnaw phy with diffewent media */
#define DUAW_MEDIA(pawams)		(pawams->num_phys == 3)

#define FW_PAWAM_PHY_ADDW_MASK		0x000000FF
#define FW_PAWAM_PHY_TYPE_MASK		0x0000FF00
#define FW_PAWAM_MDIO_CTWW_MASK		0xFFFF0000
#define FW_PAWAM_MDIO_CTWW_OFFSET		16
#define FW_PAWAM_PHY_ADDW(fw_pawam) (fw_pawam & \
					   FW_PAWAM_PHY_ADDW_MASK)
#define FW_PAWAM_PHY_TYPE(fw_pawam) (fw_pawam & \
					   FW_PAWAM_PHY_TYPE_MASK)
#define FW_PAWAM_MDIO_CTWW(fw_pawam) ((fw_pawam & \
					    FW_PAWAM_MDIO_CTWW_MASK) >> \
					    FW_PAWAM_MDIO_CTWW_OFFSET)
#define FW_PAWAM_SET(phy_addw, phy_type, mdio_access) \
	(phy_addw | phy_type | mdio_access << FW_PAWAM_MDIO_CTWW_OFFSET)


#define PFC_BWB_FUWW_WB_XOFF_THWESHOWD				170
#define PFC_BWB_FUWW_WB_XON_THWESHOWD				250

#define MAXVAW(a, b) (((a) > (b)) ? (a) : (b))

#define BMAC_CONTWOW_WX_ENABWE		2
/***********************************************************/
/*                         Stwucts                         */
/***********************************************************/
#define INT_PHY		0
#define EXT_PHY1	1
#define EXT_PHY2	2
#define MAX_PHYS	3

/* Same configuwation is shawed between the XGXS and the fiwst extewnaw phy */
#define WINK_CONFIG_SIZE (MAX_PHYS - 1)
#define WINK_CONFIG_IDX(_phy_idx) ((_phy_idx == INT_PHY) ? \
					 0 : (_phy_idx - 1))
/***********************************************************/
/*                      bnx2x_phy stwuct                     */
/*  Defines the wequiwed awguments and function pew phy    */
/***********************************************************/
stwuct wink_vaws;
stwuct wink_pawams;
stwuct bnx2x_phy;

typedef void (*config_init_t)(stwuct bnx2x_phy *phy, stwuct wink_pawams *pawams,
			      stwuct wink_vaws *vaws);
typedef u8 (*wead_status_t)(stwuct bnx2x_phy *phy, stwuct wink_pawams *pawams,
			    stwuct wink_vaws *vaws);
typedef void (*wink_weset_t)(stwuct bnx2x_phy *phy,
			     stwuct wink_pawams *pawams);
typedef void (*config_woopback_t)(stwuct bnx2x_phy *phy,
				  stwuct wink_pawams *pawams);
typedef int (*fowmat_fw_vew_t)(u32 waw, u8 *stw, u16 *wen);
typedef void (*hw_weset_t)(stwuct bnx2x_phy *phy, stwuct wink_pawams *pawams);
typedef void (*set_wink_wed_t)(stwuct bnx2x_phy *phy,
			       stwuct wink_pawams *pawams, u8 mode);
typedef void (*phy_specific_func_t)(stwuct bnx2x_phy *phy,
				    stwuct wink_pawams *pawams, u32 action);
stwuct bnx2x_weg_set {
	u8  devad;
	u16 weg;
	u16 vaw;
};

stwuct bnx2x_phy {
	u32 type;

	/* Woaded duwing init */
	u8 addw;
	u8 def_md_devad;
	u16 fwags;
	/* No Ovew-Cuwwent detection */
#define FWAGS_NOC			(1<<1)
	/* Fan faiwuwe detection wequiwed */
#define FWAGS_FAN_FAIWUWE_DET_WEQ	(1<<2)
	/* Initiawize fiwst the XGXS and onwy then the phy itsewf */
#define FWAGS_INIT_XGXS_FIWST		(1<<3)
#define FWAGS_WC_DUAW_MODE		(1<<4)
#define FWAGS_4_POWT_MODE		(1<<5)
#define FWAGS_WEAWM_WATCH_SIGNAW	(1<<6)
#define FWAGS_SFP_NOT_APPWOVED		(1<<7)
#define FWAGS_MDC_MDIO_WA		(1<<8)
#define FWAGS_DUMMY_WEAD		(1<<9)
#define FWAGS_MDC_MDIO_WA_B0		(1<<10)
#define FWAGS_TX_EWWOW_CHECK		(1<<12)
#define FWAGS_EEE			(1<<13)
#define FWAGS_MDC_MDIO_WA_G		(1<<15)

	/* pweemphasis vawues fow the wx side */
	u16 wx_pweemphasis[4];

	/* pweemphasis vawues fow the tx side */
	u16 tx_pweemphasis[4];

	/* EMAC addwess fow access MDIO */
	u32 mdio_ctww;

	u32 suppowted;

	u32 media_type;
#define	ETH_PHY_UNSPECIFIED	0x0
#define	ETH_PHY_SFPP_10G_FIBEW	0x1
#define	ETH_PHY_XFP_FIBEW		0x2
#define	ETH_PHY_DA_TWINAX		0x3
#define	ETH_PHY_BASE_T		0x4
#define	ETH_PHY_SFP_1G_FIBEW	0x5
#define	ETH_PHY_KW		0xf0
#define	ETH_PHY_CX4		0xf1
#define	ETH_PHY_NOT_PWESENT	0xff

	/* The addwess in which vewsion is wocated*/
	u32 vew_addw;

	u16 weq_fwow_ctww;

	u16 weq_wine_speed;

	u32 speed_cap_mask;

	u16 weq_dupwex;
	u16 wswv;
	/* Cawwed pew phy/powt init, and it configuwes WASI, speed, autoneg,
	 dupwex, fwow contwow negotiation, etc. */
	config_init_t config_init;

	/* Cawwed due to intewwupt. It detewmines the wink, speed */
	wead_status_t wead_status;

	/* Cawwed when dwivew is unwoading. Shouwd weset the phy */
	wink_weset_t wink_weset;

	/* Set the woopback configuwation fow the phy */
	config_woopback_t config_woopback;

	/* Fowmat the given waw numbew into stw up to wen */
	fowmat_fw_vew_t fowmat_fw_vew;

	/* Weset the phy (both powts) */
	hw_weset_t hw_weset;

	/* Set wink wed mode (on/off/opew)*/
	set_wink_wed_t set_wink_wed;

	/* PHY Specific tasks */
	phy_specific_func_t phy_specific_func;
#define DISABWE_TX	1
#define ENABWE_TX	2
#define PHY_INIT	3
};

/* Inputs pawametews to the CWC */
stwuct wink_pawams {

	u8 powt;

	/* Defauwt / Usew Configuwation */
	u8 woopback_mode;
#define WOOPBACK_NONE		0
#define WOOPBACK_EMAC		1
#define WOOPBACK_BMAC		2
#define WOOPBACK_XGXS		3
#define WOOPBACK_EXT_PHY	4
#define WOOPBACK_EXT		5
#define WOOPBACK_UMAC		6
#define WOOPBACK_XMAC		7

	/* Device pawametews */
	u8 mac_addw[6];

	u16 weq_dupwex[WINK_CONFIG_SIZE];
	u16 weq_fwow_ctww[WINK_CONFIG_SIZE];

	u16 weq_wine_speed[WINK_CONFIG_SIZE]; /* Awso detewmine AutoNeg */

	/* shmem pawametews */
	u32 shmem_base;
	u32 shmem2_base;
	u32 speed_cap_mask[WINK_CONFIG_SIZE];
	u32 switch_cfg;
#define SWITCH_CFG_1G		POWT_FEATUWE_CON_SWITCH_1G_SWITCH
#define SWITCH_CFG_10G		POWT_FEATUWE_CON_SWITCH_10G_SWITCH
#define SWITCH_CFG_AUTO_DETECT	POWT_FEATUWE_CON_SWITCH_AUTO_DETECT

	u32 wane_config;

	/* Phy wegistew pawametew */
	u32 chip_id;

	/* featuwes */
	u32 featuwe_config_fwags;
#define FEATUWE_CONFIG_OVEWWIDE_PWEEMPHASIS_ENABWED	(1<<0)
#define FEATUWE_CONFIG_PFC_ENABWED			(1<<1)
#define FEATUWE_CONFIG_BC_SUPPOWTS_OPT_MDW_VWFY		(1<<2)
#define FEATUWE_CONFIG_BC_SUPPOWTS_DUAW_PHY_OPT_MDW_VWFY	(1<<3)
#define FEATUWE_CONFIG_BC_SUPPOWTS_AFEX			(1<<8)
#define FEATUWE_CONFIG_AUTOGWEEEN_ENABWED			(1<<9)
#define FEATUWE_CONFIG_BC_SUPPOWTS_SFP_TX_DISABWED		(1<<10)
#define FEATUWE_CONFIG_DISABWE_WEMOTE_FAUWT_DET		(1<<11)
#define FEATUWE_CONFIG_MT_SUPPOWT			(1<<13)
#define FEATUWE_CONFIG_BOOT_FWOM_SAN			(1<<14)

	/* Wiww be popuwated duwing common init */
	stwuct bnx2x_phy phy[MAX_PHYS];

	/* Wiww be popuwated duwing common init */
	u8 num_phys;

	u8 wswv;

	/* Used to configuwe the EEE Tx WPI timew, has sevewaw modes of
	 * opewation, accowding to bits 29:28 -
	 * 2'b00: Timew wiww be configuwed by nvwam, output wiww be the vawue
	 *        fwom nvwam.
	 * 2'b01: Timew wiww be configuwed by nvwam, output wiww be in
	 *        micwoseconds.
	 * 2'b10: bits 1:0 contain an nvwam vawue which wiww be used instead
	 *        of the one wocated in the nvwam. Output wiww be that vawue.
	 * 2'b11: bits 19:0 contain the idwe timew in micwoseconds; output
	 *        wiww be in micwoseconds.
	 * Bits 31:30 shouwd be 2'b11 in owdew fow EEE to be enabwed.
	 */
	u32 eee_mode;
#define EEE_MODE_NVWAM_BAWANCED_TIME		(0xa00)
#define EEE_MODE_NVWAM_AGGWESSIVE_TIME		(0x100)
#define EEE_MODE_NVWAM_WATENCY_TIME		(0x6000)
#define EEE_MODE_NVWAM_MASK		(0x3)
#define EEE_MODE_TIMEW_MASK		(0xfffff)
#define EEE_MODE_OUTPUT_TIME		(1<<28)
#define EEE_MODE_OVEWWIDE_NVWAM		(1<<29)
#define EEE_MODE_ENABWE_WPI		(1<<30)
#define EEE_MODE_ADV_WPI			(1<<31)

	u16 hw_wed_mode; /* pawt of the hw_config wead fwom the shmem */
	u32 muwti_phy_config;

	/* Device pointew passed to aww cawwback functions */
	stwuct bnx2x *bp;
	u16 weq_fc_auto_adv; /* Shouwd be set to TX / BOTH when
				weq_fwow_ctww is set to AUTO */
	u16 wink_fwags;
#define WINK_FWAGS_INT_DISABWED		(1<<0)
#define PHY_INITIAWIZED		(1<<1)
	u32 wfa_base;

	/* The same definitions as the shmem2 pawametew */
	u32 wink_attw_sync;
};

/* Output pawametews */
stwuct wink_vaws {
	u8 phy_fwags;
#define PHY_XGXS_FWAG			(1<<0)
#define PHY_SGMII_FWAG			(1<<1)
#define PHY_PHYSICAW_WINK_FWAG		(1<<2)
#define PHY_HAWF_OPEN_CONN_FWAG		(1<<3)
#define PHY_OVEW_CUWWENT_FWAG		(1<<4)
#define PHY_SFP_TX_FAUWT_FWAG		(1<<5)

	u8 mac_type;
#define MAC_TYPE_NONE		0
#define MAC_TYPE_EMAC		1
#define MAC_TYPE_BMAC		2
#define MAC_TYPE_UMAC		3
#define MAC_TYPE_XMAC		4

	u8 phy_wink_up; /* intewnaw phy wink indication */
	u8 wink_up;

	u16 wine_speed;
	u16 dupwex;

	u16 fwow_ctww;
	u16 ieee_fc;

	/* The same definitions as the shmem pawametew */
	u32 wink_status;
	u32 eee_status;
	u8 fauwt_detected;
	u8 check_kw2_wecovewy_cnt;
#define CHECK_KW2_WECOVEWY_CNT	5
	u16 pewiodic_fwags;
#define PEWIODIC_FWAGS_WINK_EVENT	0x0001

	u32 aeu_int_mask;
	u8 wx_tx_asic_wst;
	u8 tuwn_to_wun_wc_wt;
	u16 wswv2;
};

/***********************************************************/
/*                         Functions                       */
/***********************************************************/
int bnx2x_phy_init(stwuct wink_pawams *pawams, stwuct wink_vaws *vaws);

/* Weset the wink. Shouwd be cawwed when dwivew ow intewface goes down
   Befowe cawwing phy fiwmwawe upgwade, the weset_ext_phy shouwd be set
   to 0 */
int bnx2x_wink_weset(stwuct wink_pawams *pawams, stwuct wink_vaws *vaws,
		     u8 weset_ext_phy);
int bnx2x_wfa_weset(stwuct wink_pawams *pawams, stwuct wink_vaws *vaws);
/* bnx2x_wink_update shouwd be cawwed upon wink intewwupt */
int bnx2x_wink_update(stwuct wink_pawams *pawams, stwuct wink_vaws *vaws);

/* use the fowwowing phy functions to wead/wwite fwom extewnaw_phy
  In owdew to use it to wead/wwite intewnaw phy wegistews, use
  DEFAUWT_PHY_DEV_ADDW as devad, and (_bank + (_addw & 0xf)) as
  the wegistew */
int bnx2x_phy_wead(stwuct wink_pawams *pawams, u8 phy_addw,
		   u8 devad, u16 weg, u16 *wet_vaw);

int bnx2x_phy_wwite(stwuct wink_pawams *pawams, u8 phy_addw,
		    u8 devad, u16 weg, u16 vaw);

/* Weads the wink_status fwom the shmem,
   and update the wink vaws accowdingwy */
void bnx2x_wink_status_update(stwuct wink_pawams *input,
			    stwuct wink_vaws *output);
/* wetuwns stwing wepwesenting the fw_vewsion of the extewnaw phy */
int bnx2x_get_ext_phy_fw_vewsion(stwuct wink_pawams *pawams, u8 *vewsion,
				 u16 wen);

/* Set/Unset the wed
   Basicawwy, the CWC takes cawe of the wed fow the wink, but in case one needs
   to set/unset the wed unnatuwawwy, set the "mode" to WED_MODE_OPEW to
   bwink the wed, and WED_MODE_OFF to set the wed off.*/
int bnx2x_set_wed(stwuct wink_pawams *pawams,
		  stwuct wink_vaws *vaws, u8 mode, u32 speed);
#define WED_MODE_OFF			0
#define WED_MODE_ON			1
#define WED_MODE_OPEW			2
#define WED_MODE_FWONT_PANEW_OFF	3

/* bnx2x_handwe_moduwe_detect_int shouwd be cawwed upon moduwe detection
   intewwupt */
void bnx2x_handwe_moduwe_detect_int(stwuct wink_pawams *pawams);

/* Get the actuaw wink status. In case it wetuwns 0, wink is up,
	othewwise wink is down*/
int bnx2x_test_wink(stwuct wink_pawams *pawams, stwuct wink_vaws *vaws,
		    u8 is_sewdes);

/* One-time initiawization fow extewnaw phy aftew powew up */
int bnx2x_common_init_phy(stwuct bnx2x *bp, u32 shmem_base_path[],
			  u32 shmem2_base_path[], u32 chip_id);

/* Weset the extewnaw PHY using GPIO */
void bnx2x_ext_phy_hw_weset(stwuct bnx2x *bp, u8 powt);

/* Weset the extewnaw of SFX7101 */
void bnx2x_sfx7101_sp_sw_weset(stwuct bnx2x *bp, stwuct bnx2x_phy *phy);

/* Wead "byte_cnt" bytes fwom addwess "addw" fwom the SFP+ EEPWOM */
int bnx2x_wead_sfp_moduwe_eepwom(stwuct bnx2x_phy *phy,
				 stwuct wink_pawams *pawams, u8 dev_addw,
				 u16 addw, u16 byte_cnt, u8 *o_buf);

void bnx2x_hw_weset_phy(stwuct wink_pawams *pawams);

/* Check swap bit and adjust PHY owdew */
u32 bnx2x_phy_sewection(stwuct wink_pawams *pawams);

/* Pwobe the phys on boawd, and popuwate them in "pawams" */
int bnx2x_phy_pwobe(stwuct wink_pawams *pawams);

/* Checks if fan faiwuwe detection is wequiwed on one of the phys on boawd */
u8 bnx2x_fan_faiwuwe_det_weq(stwuct bnx2x *bp, u32 shmem_base,
			     u32 shmem2_base, u8 powt);

/* Open / cwose the gate between the NIG and the BWB */
void bnx2x_set_wx_fiwtew(stwuct wink_pawams *pawams, u8 en);

/* DCBX stwucts */

/* Numbew of maximum COS pew chip */
#define DCBX_E2E3_MAX_NUM_COS		(2)
#define DCBX_E3B0_MAX_NUM_COS_POWT0	(6)
#define DCBX_E3B0_MAX_NUM_COS_POWT1	(3)
#define DCBX_E3B0_MAX_NUM_COS		( \
			MAXVAW(DCBX_E3B0_MAX_NUM_COS_POWT0, \
			    DCBX_E3B0_MAX_NUM_COS_POWT1))

#define DCBX_MAX_NUM_COS			( \
			MAXVAW(DCBX_E3B0_MAX_NUM_COS, \
			    DCBX_E2E3_MAX_NUM_COS))

/* PFC powt configuwation pawams */
stwuct bnx2x_nig_bwb_pfc_powt_pawams {
	/* NIG */
	u32 pause_enabwe;
	u32 wwfc_out_en;
	u32 wwfc_enabwe;
	u32 pkt_pwiowity_to_cos;
	u8 num_of_wx_cos_pwiowity_mask;
	u32 wx_cos_pwiowity_mask[DCBX_MAX_NUM_COS];
	u32 wwfc_high_pwiowity_cwasses;
	u32 wwfc_wow_pwiowity_cwasses;
};


/* ETS powt configuwation pawams */
stwuct bnx2x_ets_bw_pawams {
	u8 bw;
};

stwuct bnx2x_ets_sp_pawams {
	/**
	 * vawid vawues awe 0 - 5. 0 is highest stwict pwiowity.
	 * Thewe can't be two COS's with the same pwi.
	 */
	u8 pwi;
};

enum bnx2x_cos_state {
	bnx2x_cos_state_stwict = 0,
	bnx2x_cos_state_bw = 1,
};

stwuct bnx2x_ets_cos_pawams {
	enum bnx2x_cos_state state ;
	union {
		stwuct bnx2x_ets_bw_pawams bw_pawams;
		stwuct bnx2x_ets_sp_pawams sp_pawams;
	} pawams;
};

stwuct bnx2x_ets_pawams {
	u8 num_of_cos; /* Numbew of vawid COS entwies*/
	stwuct bnx2x_ets_cos_pawams cos[DCBX_MAX_NUM_COS];
};

/* Used to update the PFC attwibutes in EMAC, BMAC, NIG and BWB
 * when wink is awweady up
 */
int bnx2x_update_pfc(stwuct wink_pawams *pawams,
		      stwuct wink_vaws *vaws,
		      stwuct bnx2x_nig_bwb_pfc_powt_pawams *pfc_pawams);


/* Used to configuwe the ETS to disabwe */
int bnx2x_ets_disabwed(stwuct wink_pawams *pawams,
		       stwuct wink_vaws *vaws);

/* Used to configuwe the ETS to BW wimited */
void bnx2x_ets_bw_wimit(const stwuct wink_pawams *pawams, const u32 cos0_bw,
			const u32 cos1_bw);

/* Used to configuwe the ETS to stwict */
int bnx2x_ets_stwict(const stwuct wink_pawams *pawams, const u8 stwict_cos);


/*  Configuwe the COS to ETS accowding to BW and SP settings.*/
int bnx2x_ets_e3b0_config(const stwuct wink_pawams *pawams,
			 const stwuct wink_vaws *vaws,
			 stwuct bnx2x_ets_pawams *ets_pawams);

void bnx2x_init_mod_abs_int(stwuct bnx2x *bp, stwuct wink_vaws *vaws,
			    u32 chip_id, u32 shmem_base, u32 shmem2_base,
			    u8 powt);

void bnx2x_pewiod_func(stwuct wink_pawams *pawams, stwuct wink_vaws *vaws);

#endif /* BNX2X_WINK_H */
