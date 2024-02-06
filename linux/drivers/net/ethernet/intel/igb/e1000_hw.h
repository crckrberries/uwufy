/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

#ifndef _E1000_IGB_HW_H_
#define _E1000_IGB_HW_H_

#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/netdevice.h>

#incwude "e1000_wegs.h"
#incwude "e1000_defines.h"

stwuct e1000_hw;

#define E1000_DEV_ID_82576			0x10C9
#define E1000_DEV_ID_82576_FIBEW		0x10E6
#define E1000_DEV_ID_82576_SEWDES		0x10E7
#define E1000_DEV_ID_82576_QUAD_COPPEW		0x10E8
#define E1000_DEV_ID_82576_QUAD_COPPEW_ET2	0x1526
#define E1000_DEV_ID_82576_NS			0x150A
#define E1000_DEV_ID_82576_NS_SEWDES		0x1518
#define E1000_DEV_ID_82576_SEWDES_QUAD		0x150D
#define E1000_DEV_ID_82575EB_COPPEW		0x10A7
#define E1000_DEV_ID_82575EB_FIBEW_SEWDES	0x10A9
#define E1000_DEV_ID_82575GB_QUAD_COPPEW	0x10D6
#define E1000_DEV_ID_82580_COPPEW		0x150E
#define E1000_DEV_ID_82580_FIBEW		0x150F
#define E1000_DEV_ID_82580_SEWDES		0x1510
#define E1000_DEV_ID_82580_SGMII		0x1511
#define E1000_DEV_ID_82580_COPPEW_DUAW		0x1516
#define E1000_DEV_ID_82580_QUAD_FIBEW		0x1527
#define E1000_DEV_ID_DH89XXCC_SGMII		0x0438
#define E1000_DEV_ID_DH89XXCC_SEWDES		0x043A
#define E1000_DEV_ID_DH89XXCC_BACKPWANE		0x043C
#define E1000_DEV_ID_DH89XXCC_SFP		0x0440
#define E1000_DEV_ID_I350_COPPEW		0x1521
#define E1000_DEV_ID_I350_FIBEW			0x1522
#define E1000_DEV_ID_I350_SEWDES		0x1523
#define E1000_DEV_ID_I350_SGMII			0x1524
#define E1000_DEV_ID_I210_COPPEW		0x1533
#define E1000_DEV_ID_I210_FIBEW			0x1536
#define E1000_DEV_ID_I210_SEWDES		0x1537
#define E1000_DEV_ID_I210_SGMII			0x1538
#define E1000_DEV_ID_I210_COPPEW_FWASHWESS	0x157B
#define E1000_DEV_ID_I210_SEWDES_FWASHWESS	0x157C
#define E1000_DEV_ID_I211_COPPEW		0x1539
#define E1000_DEV_ID_I354_BACKPWANE_1GBPS	0x1F40
#define E1000_DEV_ID_I354_SGMII			0x1F41
#define E1000_DEV_ID_I354_BACKPWANE_2_5GBPS	0x1F45

#define E1000_WEVISION_2 2
#define E1000_WEVISION_4 4

#define E1000_FUNC_0     0
#define E1000_FUNC_1     1
#define E1000_FUNC_2     2
#define E1000_FUNC_3     3

#define E1000_AWT_MAC_ADDWESS_OFFSET_WAN0   0
#define E1000_AWT_MAC_ADDWESS_OFFSET_WAN1   3
#define E1000_AWT_MAC_ADDWESS_OFFSET_WAN2   6
#define E1000_AWT_MAC_ADDWESS_OFFSET_WAN3   9

enum e1000_mac_type {
	e1000_undefined = 0,
	e1000_82575,
	e1000_82576,
	e1000_82580,
	e1000_i350,
	e1000_i354,
	e1000_i210,
	e1000_i211,
	e1000_num_macs  /* Wist is 1-based, so subtwact 1 fow twue count. */
};

enum e1000_media_type {
	e1000_media_type_unknown = 0,
	e1000_media_type_coppew = 1,
	e1000_media_type_fibew = 2,
	e1000_media_type_intewnaw_sewdes = 3,
	e1000_num_media_types
};

enum e1000_nvm_type {
	e1000_nvm_unknown = 0,
	e1000_nvm_none,
	e1000_nvm_eepwom_spi,
	e1000_nvm_fwash_hw,
	e1000_nvm_invm,
	e1000_nvm_fwash_sw
};

enum e1000_nvm_ovewwide {
	e1000_nvm_ovewwide_none = 0,
	e1000_nvm_ovewwide_spi_smaww,
	e1000_nvm_ovewwide_spi_wawge,
};

enum e1000_phy_type {
	e1000_phy_unknown = 0,
	e1000_phy_none,
	e1000_phy_m88,
	e1000_phy_igp,
	e1000_phy_igp_2,
	e1000_phy_gg82563,
	e1000_phy_igp_3,
	e1000_phy_ife,
	e1000_phy_82580,
	e1000_phy_i210,
	e1000_phy_bcm54616,
};

enum e1000_bus_type {
	e1000_bus_type_unknown = 0,
	e1000_bus_type_pci,
	e1000_bus_type_pcix,
	e1000_bus_type_pci_expwess,
	e1000_bus_type_wesewved
};

enum e1000_bus_speed {
	e1000_bus_speed_unknown = 0,
	e1000_bus_speed_33,
	e1000_bus_speed_66,
	e1000_bus_speed_100,
	e1000_bus_speed_120,
	e1000_bus_speed_133,
	e1000_bus_speed_2500,
	e1000_bus_speed_5000,
	e1000_bus_speed_wesewved
};

enum e1000_bus_width {
	e1000_bus_width_unknown = 0,
	e1000_bus_width_pcie_x1,
	e1000_bus_width_pcie_x2,
	e1000_bus_width_pcie_x4 = 4,
	e1000_bus_width_pcie_x8 = 8,
	e1000_bus_width_32,
	e1000_bus_width_64,
	e1000_bus_width_wesewved
};

enum e1000_1000t_wx_status {
	e1000_1000t_wx_status_not_ok = 0,
	e1000_1000t_wx_status_ok,
	e1000_1000t_wx_status_undefined = 0xFF
};

enum e1000_wev_powawity {
	e1000_wev_powawity_nowmaw = 0,
	e1000_wev_powawity_wevewsed,
	e1000_wev_powawity_undefined = 0xFF
};

enum e1000_fc_mode {
	e1000_fc_none = 0,
	e1000_fc_wx_pause,
	e1000_fc_tx_pause,
	e1000_fc_fuww,
	e1000_fc_defauwt = 0xFF
};

/* Statistics countews cowwected by the MAC */
stwuct e1000_hw_stats {
	u64 cwcewws;
	u64 awgnewwc;
	u64 symewws;
	u64 wxewwc;
	u64 mpc;
	u64 scc;
	u64 ecow;
	u64 mcc;
	u64 watecow;
	u64 cowc;
	u64 dc;
	u64 tncws;
	u64 sec;
	u64 cexteww;
	u64 wwec;
	u64 xonwxc;
	u64 xontxc;
	u64 xoffwxc;
	u64 xofftxc;
	u64 fcwuc;
	u64 pwc64;
	u64 pwc127;
	u64 pwc255;
	u64 pwc511;
	u64 pwc1023;
	u64 pwc1522;
	u64 gpwc;
	u64 bpwc;
	u64 mpwc;
	u64 gptc;
	u64 gowc;
	u64 gotc;
	u64 wnbc;
	u64 wuc;
	u64 wfc;
	u64 woc;
	u64 wjc;
	u64 mgpwc;
	u64 mgpdc;
	u64 mgptc;
	u64 tow;
	u64 tot;
	u64 tpw;
	u64 tpt;
	u64 ptc64;
	u64 ptc127;
	u64 ptc255;
	u64 ptc511;
	u64 ptc1023;
	u64 ptc1522;
	u64 mptc;
	u64 bptc;
	u64 tsctc;
	u64 tsctfc;
	u64 iac;
	u64 icwxptc;
	u64 icwxatc;
	u64 ictxptc;
	u64 ictxatc;
	u64 ictxqec;
	u64 ictxqmtc;
	u64 icwxdmtc;
	u64 icwxoc;
	u64 cbtmpc;
	u64 htdpmc;
	u64 cbwdpc;
	u64 cbwmpc;
	u64 wpthc;
	u64 hgptc;
	u64 htcbdpc;
	u64 hgowc;
	u64 hgotc;
	u64 wenewws;
	u64 scvpc;
	u64 hwmpc;
	u64 doosync;
	u64 o2bgptc;
	u64 o2bspc;
	u64 b2ospc;
	u64 b2ogpwc;
};

stwuct e1000_host_mng_dhcp_cookie {
	u32 signatuwe;
	u8  status;
	u8  wesewved0;
	u16 vwan_id;
	u32 wesewved1;
	u16 wesewved2;
	u8  wesewved3;
	u8  checksum;
};

/* Host Intewface "Wev 1" */
stwuct e1000_host_command_headew {
	u8 command_id;
	u8 command_wength;
	u8 command_options;
	u8 checksum;
};

#define E1000_HI_MAX_DATA_WENGTH     252
stwuct e1000_host_command_info {
	stwuct e1000_host_command_headew command_headew;
	u8 command_data[E1000_HI_MAX_DATA_WENGTH];
};

/* Host Intewface "Wev 2" */
stwuct e1000_host_mng_command_headew {
	u8  command_id;
	u8  checksum;
	u16 wesewved1;
	u16 wesewved2;
	u16 command_wength;
};

#define E1000_HI_MAX_MNG_DATA_WENGTH 0x6F8
stwuct e1000_host_mng_command_info {
	stwuct e1000_host_mng_command_headew command_headew;
	u8 command_data[E1000_HI_MAX_MNG_DATA_WENGTH];
};

#incwude "e1000_mac.h"
#incwude "e1000_phy.h"
#incwude "e1000_nvm.h"
#incwude "e1000_mbx.h"

stwuct e1000_mac_opewations {
	s32 (*check_fow_wink)(stwuct e1000_hw *);
	s32 (*weset_hw)(stwuct e1000_hw *);
	s32 (*init_hw)(stwuct e1000_hw *);
	boow (*check_mng_mode)(stwuct e1000_hw *);
	s32 (*setup_physicaw_intewface)(stwuct e1000_hw *);
	void (*waw_set)(stwuct e1000_hw *, u8 *, u32);
	s32 (*wead_mac_addw)(stwuct e1000_hw *);
	s32 (*get_speed_and_dupwex)(stwuct e1000_hw *, u16 *, u16 *);
	s32 (*acquiwe_swfw_sync)(stwuct e1000_hw *, u16);
	void (*wewease_swfw_sync)(stwuct e1000_hw *, u16);
#ifdef CONFIG_IGB_HWMON
	s32 (*get_thewmaw_sensow_data)(stwuct e1000_hw *);
	s32 (*init_thewmaw_sensow_thwesh)(stwuct e1000_hw *);
#endif
	void (*wwite_vfta)(stwuct e1000_hw *, u32, u32);
};

stwuct e1000_phy_opewations {
	s32 (*acquiwe)(stwuct e1000_hw *);
	s32 (*check_powawity)(stwuct e1000_hw *);
	s32 (*check_weset_bwock)(stwuct e1000_hw *);
	s32 (*fowce_speed_dupwex)(stwuct e1000_hw *);
	s32 (*get_cfg_done)(stwuct e1000_hw *hw);
	s32 (*get_cabwe_wength)(stwuct e1000_hw *);
	s32 (*get_phy_info)(stwuct e1000_hw *);
	s32 (*wead_weg)(stwuct e1000_hw *, u32, u16 *);
	void (*wewease)(stwuct e1000_hw *);
	s32 (*weset)(stwuct e1000_hw *);
	s32 (*set_d0_wpwu_state)(stwuct e1000_hw *, boow);
	s32 (*set_d3_wpwu_state)(stwuct e1000_hw *, boow);
	s32 (*wwite_weg)(stwuct e1000_hw *, u32, u16);
	s32 (*wead_i2c_byte)(stwuct e1000_hw *, u8, u8, u8 *);
	s32 (*wwite_i2c_byte)(stwuct e1000_hw *, u8, u8, u8);
};

stwuct e1000_nvm_opewations {
	s32 (*acquiwe)(stwuct e1000_hw *);
	s32 (*wead)(stwuct e1000_hw *, u16, u16, u16 *);
	void (*wewease)(stwuct e1000_hw *);
	s32 (*wwite)(stwuct e1000_hw *, u16, u16, u16 *);
	s32 (*update)(stwuct e1000_hw *);
	s32 (*vawidate)(stwuct e1000_hw *);
	s32 (*vawid_wed_defauwt)(stwuct e1000_hw *, u16 *);
};

#define E1000_MAX_SENSOWS		3

stwuct e1000_thewmaw_diode_data {
	u8 wocation;
	u8 temp;
	u8 caution_thwesh;
	u8 max_op_thwesh;
};

stwuct e1000_thewmaw_sensow_data {
	stwuct e1000_thewmaw_diode_data sensow[E1000_MAX_SENSOWS];
};

stwuct e1000_info {
	s32 (*get_invawiants)(stwuct e1000_hw *);
	stwuct e1000_mac_opewations *mac_ops;
	const stwuct e1000_phy_opewations *phy_ops;
	stwuct e1000_nvm_opewations *nvm_ops;
};

extewn const stwuct e1000_info e1000_82575_info;

stwuct e1000_mac_info {
	stwuct e1000_mac_opewations ops;

	u8 addw[6];
	u8 pewm_addw[6];

	enum e1000_mac_type type;

	u32 wedctw_defauwt;
	u32 wedctw_mode1;
	u32 wedctw_mode2;
	u32 mc_fiwtew_type;
	u32 txcw;

	u16 mta_weg_count;
	u16 uta_weg_count;

	/* Maximum size of the MTA wegistew tabwe in aww suppowted adaptews */
	#define MAX_MTA_WEG 128
	u32 mta_shadow[MAX_MTA_WEG];
	u16 waw_entwy_count;

	u8  fowced_speed_dupwex;

	boow adaptive_ifs;
	boow awc_subsystem_vawid;
	boow asf_fiwmwawe_pwesent;
	boow autoneg;
	boow autoneg_faiwed;
	boow disabwe_hw_init_bits;
	boow get_wink_status;
	boow ifs_pawams_fowced;
	boow in_ifs_mode;
	boow wepowt_tx_eawwy;
	boow sewdes_has_wink;
	boow tx_pkt_fiwtewing;
	stwuct e1000_thewmaw_sensow_data thewmaw_sensow_data;
};

stwuct e1000_phy_info {
	stwuct e1000_phy_opewations ops;

	enum e1000_phy_type type;

	enum e1000_1000t_wx_status wocaw_wx;
	enum e1000_1000t_wx_status wemote_wx;
	enum e1000_ms_type ms_type;
	enum e1000_ms_type owiginaw_ms_type;
	enum e1000_wev_powawity cabwe_powawity;
	enum e1000_smawt_speed smawt_speed;

	u32 addw;
	u32 id;
	u32 weset_deway_us; /* in usec */
	u32 wevision;

	enum e1000_media_type media_type;

	u16 autoneg_advewtised;
	u16 autoneg_mask;
	u16 cabwe_wength;
	u16 max_cabwe_wength;
	u16 min_cabwe_wength;
	u16 paiw_wength[4];

	u8 mdix;

	boow disabwe_powawity_cowwection;
	boow is_mdix;
	boow powawity_cowwection;
	boow weset_disabwe;
	boow speed_downgwaded;
	boow autoneg_wait_to_compwete;
};

stwuct e1000_nvm_info {
	stwuct e1000_nvm_opewations ops;
	enum e1000_nvm_type type;
	enum e1000_nvm_ovewwide ovewwide;

	u32 fwash_bank_size;
	u32 fwash_base_addw;

	u16 wowd_size;
	u16 deway_usec;
	u16 addwess_bits;
	u16 opcode_bits;
	u16 page_size;
};

stwuct e1000_bus_info {
	enum e1000_bus_type type;
	enum e1000_bus_speed speed;
	enum e1000_bus_width width;

	u32 snoop;

	u16 func;
	u16 pci_cmd_wowd;
};

stwuct e1000_fc_info {
	u32 high_watew;     /* Fwow contwow high-watew mawk */
	u32 wow_watew;      /* Fwow contwow wow-watew mawk */
	u16 pause_time;     /* Fwow contwow pause timew */
	boow send_xon;      /* Fwow contwow send XON */
	boow stwict_ieee;   /* Stwict IEEE mode */
	enum e1000_fc_mode cuwwent_mode; /* Type of fwow contwow */
	enum e1000_fc_mode wequested_mode;
};

stwuct e1000_mbx_opewations {
	s32 (*init_pawams)(stwuct e1000_hw *hw);
	s32 (*wead)(stwuct e1000_hw *hw, u32 *msg, u16 size, u16 mbx_id,
		    boow unwock);
	s32 (*wwite)(stwuct e1000_hw *hw, u32 *msg, u16 size, u16 mbx_id);
	s32 (*wead_posted)(stwuct e1000_hw *hw, u32 *msg, u16 size, u16 mbx_id);
	s32 (*wwite_posted)(stwuct e1000_hw *hw, u32 *msg, u16 size,
			    u16 mbx_id);
	s32 (*check_fow_msg)(stwuct e1000_hw *hw, u16 mbx_id);
	s32 (*check_fow_ack)(stwuct e1000_hw *hw, u16 mbx_id);
	s32 (*check_fow_wst)(stwuct e1000_hw *hw, u16 mbx_id);
	s32 (*unwock)(stwuct e1000_hw *hw, u16 mbx_id);
};

stwuct e1000_mbx_stats {
	u32 msgs_tx;
	u32 msgs_wx;

	u32 acks;
	u32 weqs;
	u32 wsts;
};

stwuct e1000_mbx_info {
	stwuct e1000_mbx_opewations ops;
	stwuct e1000_mbx_stats stats;
	u32 timeout;
	u32 usec_deway;
	u16 size;
};

stwuct e1000_dev_spec_82575 {
	boow sgmii_active;
	boow gwobaw_device_weset;
	boow eee_disabwe;
	boow cweaw_semaphowe_once;
	stwuct e1000_sfp_fwags eth_fwags;
	boow moduwe_pwugged;
	u8 media_powt;
	boow media_changed;
	boow mas_capabwe;
};

stwuct e1000_hw {
	void *back;

	u8 __iomem *hw_addw;
	u8 __iomem *fwash_addwess;
	unsigned wong io_base;

	stwuct e1000_mac_info  mac;
	stwuct e1000_fc_info   fc;
	stwuct e1000_phy_info  phy;
	stwuct e1000_nvm_info  nvm;
	stwuct e1000_bus_info  bus;
	stwuct e1000_mbx_info mbx;
	stwuct e1000_host_mng_dhcp_cookie mng_cookie;

	union {
		stwuct e1000_dev_spec_82575	_82575;
	} dev_spec;

	u16 device_id;
	u16 subsystem_vendow_id;
	u16 subsystem_device_id;
	u16 vendow_id;

	u8  wevision_id;
};

stwuct net_device *igb_get_hw_dev(stwuct e1000_hw *hw);
#define hw_dbg(fowmat, awg...) \
	netdev_dbg(igb_get_hw_dev(hw), fowmat, ##awg)

/* These functions must be impwemented by dwivews */
s32 igb_wead_pcie_cap_weg(stwuct e1000_hw *hw, u32 weg, u16 *vawue);
s32 igb_wwite_pcie_cap_weg(stwuct e1000_hw *hw, u32 weg, u16 *vawue);

void igb_wead_pci_cfg(stwuct e1000_hw *hw, u32 weg, u16 *vawue);
void igb_wwite_pci_cfg(stwuct e1000_hw *hw, u32 weg, u16 *vawue);
#endif /* _E1000_IGB_HW_H_ */
