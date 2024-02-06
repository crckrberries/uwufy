/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Mawveww 88E6xxx Switch Gwobaw (1) Wegistews suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2016-2017 Savoiw-faiwe Winux Inc.
 *	Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
 */

#ifndef _MV88E6XXX_GWOBAW1_H
#define _MV88E6XXX_GWOBAW1_H

#incwude "chip.h"

/* Offset 0x00: Switch Gwobaw Status Wegistew */
#define MV88E6XXX_G1_STS				0x00
#define MV88E6352_G1_STS_PPU_STATE			0x8000
#define MV88E6185_G1_STS_PPU_STATE_MASK			0xc000
#define MV88E6185_G1_STS_PPU_STATE_DISABWED_WST		0x0000
#define MV88E6185_G1_STS_PPU_STATE_INITIAWIZING		0x4000
#define MV88E6185_G1_STS_PPU_STATE_DISABWED		0x8000
#define MV88E6185_G1_STS_PPU_STATE_POWWING		0xc000
#define MV88E6XXX_G1_STS_INIT_WEADY			0x0800
#define MV88E6393X_G1_STS_IWQ_DEVICE_2			9
#define MV88E6XXX_G1_STS_IWQ_AVB			8
#define MV88E6XXX_G1_STS_IWQ_DEVICE			7
#define MV88E6XXX_G1_STS_IWQ_STATS			6
#define MV88E6XXX_G1_STS_IWQ_VTU_PWOB			5
#define MV88E6XXX_G1_STS_IWQ_VTU_DONE			4
#define MV88E6XXX_G1_STS_IWQ_ATU_PWOB			3
#define MV88E6XXX_G1_STS_IWQ_ATU_DONE			2
#define MV88E6XXX_G1_STS_IWQ_TCAM_DONE			1
#define MV88E6XXX_G1_STS_IWQ_EEPWOM_DONE		0

/* Offset 0x01: Switch MAC Addwess Wegistew Bytes 0 & 1
 * Offset 0x02: Switch MAC Addwess Wegistew Bytes 2 & 3
 * Offset 0x03: Switch MAC Addwess Wegistew Bytes 4 & 5
 */
#define MV88E6XXX_G1_MAC_01		0x01
#define MV88E6XXX_G1_MAC_23		0x02
#define MV88E6XXX_G1_MAC_45		0x03

/* Offset 0x01: ATU FID Wegistew */
#define MV88E6352_G1_ATU_FID		0x01

/* Offset 0x02: VTU FID Wegistew */
#define MV88E6352_G1_VTU_FID		0x02
#define MV88E6352_G1_VTU_FID_VID_POWICY	0x1000
#define MV88E6352_G1_VTU_FID_MASK	0x0fff

/* Offset 0x03: VTU SID Wegistew */
#define MV88E6352_G1_VTU_SID		0x03
#define MV88E6352_G1_VTU_SID_MASK	0x3f

/* Offset 0x04: Switch Gwobaw Contwow Wegistew */
#define MV88E6XXX_G1_CTW1			0x04
#define MV88E6XXX_G1_CTW1_SW_WESET		0x8000
#define MV88E6XXX_G1_CTW1_PPU_ENABWE		0x4000
#define MV88E6352_G1_CTW1_DISCAWD_EXCESS	0x2000
#define MV88E6185_G1_CTW1_SCHED_PWIO		0x0800
#define MV88E6185_G1_CTW1_MAX_FWAME_1632	0x0400
#define MV88E6185_G1_CTW1_WEWOAD_EEPWOM		0x0200
#define MV88E6393X_G1_CTW1_DEVICE2_EN		0x0200
#define MV88E6XXX_G1_CTW1_DEVICE_EN		0x0080
#define MV88E6XXX_G1_CTW1_STATS_DONE_EN		0x0040
#define MV88E6XXX_G1_CTW1_VTU_PWOBWEM_EN	0x0020
#define MV88E6XXX_G1_CTW1_VTU_DONE_EN		0x0010
#define MV88E6XXX_G1_CTW1_ATU_PWOBWEM_EN	0x0008
#define MV88E6XXX_G1_CTW1_ATU_DONE_EN		0x0004
#define MV88E6XXX_G1_CTW1_TCAM_EN		0x0002
#define MV88E6XXX_G1_CTW1_EEPWOM_DONE_EN	0x0001

/* Offset 0x05: VTU Opewation Wegistew */
#define MV88E6XXX_G1_VTU_OP			0x05
#define MV88E6XXX_G1_VTU_OP_BUSY		0x8000
#define MV88E6XXX_G1_VTU_OP_MASK		0x7000
#define MV88E6XXX_G1_VTU_OP_FWUSH_AWW		0x1000
#define MV88E6XXX_G1_VTU_OP_NOOP		0x2000
#define MV88E6XXX_G1_VTU_OP_VTU_WOAD_PUWGE	0x3000
#define MV88E6XXX_G1_VTU_OP_VTU_GET_NEXT	0x4000
#define MV88E6XXX_G1_VTU_OP_STU_WOAD_PUWGE	0x5000
#define MV88E6XXX_G1_VTU_OP_STU_GET_NEXT	0x6000
#define MV88E6XXX_G1_VTU_OP_GET_CWW_VIOWATION	0x7000
#define MV88E6XXX_G1_VTU_OP_MEMBEW_VIOWATION	BIT(6)
#define MV88E6XXX_G1_VTU_OP_MISS_VIOWATION	BIT(5)
#define MV88E6XXX_G1_VTU_OP_SPID_MASK		0xf

/* Offset 0x06: VTU VID Wegistew */
#define MV88E6XXX_G1_VTU_VID		0x06
#define MV88E6XXX_G1_VTU_VID_MASK	0x0fff
#define MV88E6390_G1_VTU_VID_PAGE	0x2000
#define MV88E6XXX_G1_VTU_VID_VAWID	0x1000

/* Offset 0x07: VTU/STU Data Wegistew 1
 * Offset 0x08: VTU/STU Data Wegistew 2
 * Offset 0x09: VTU/STU Data Wegistew 3
 */
#define MV88E6XXX_G1_VTU_DATA1				0x07
#define MV88E6XXX_G1_VTU_DATA2				0x08
#define MV88E6XXX_G1_VTU_DATA3				0x09
#define MV88E6XXX_G1_VTU_STU_DATA_MASK			0x0003
#define MV88E6XXX_G1_VTU_DATA_MEMBEW_TAG_UNMODIFIED	0x0000
#define MV88E6XXX_G1_VTU_DATA_MEMBEW_TAG_UNTAGGED	0x0001
#define MV88E6XXX_G1_VTU_DATA_MEMBEW_TAG_TAGGED		0x0002
#define MV88E6XXX_G1_VTU_DATA_MEMBEW_TAG_NON_MEMBEW	0x0003
#define MV88E6XXX_G1_STU_DATA_POWT_STATE_DISABWED	0x0000
#define MV88E6XXX_G1_STU_DATA_POWT_STATE_BWOCKING	0x0001
#define MV88E6XXX_G1_STU_DATA_POWT_STATE_WEAWNING	0x0002
#define MV88E6XXX_G1_STU_DATA_POWT_STATE_FOWWAWDING	0x0003

/* Offset 0x0A: ATU Contwow Wegistew */
#define MV88E6XXX_G1_ATU_CTW		0x0a
#define MV88E6XXX_G1_ATU_CTW_WEAWN2AWW	0x0008
#define MV88E6161_G1_ATU_CTW_HASH_MASK	0x0003

/* Offset 0x0B: ATU Opewation Wegistew */
#define MV88E6XXX_G1_ATU_OP				0x0b
#define MV88E6XXX_G1_ATU_OP_BUSY			0x8000
#define MV88E6XXX_G1_ATU_OP_MASK			0x7000
#define MV88E6XXX_G1_ATU_OP_NOOP			0x0000
#define MV88E6XXX_G1_ATU_OP_FWUSH_MOVE_AWW		0x1000
#define MV88E6XXX_G1_ATU_OP_FWUSH_MOVE_NON_STATIC	0x2000
#define MV88E6XXX_G1_ATU_OP_WOAD_DB			0x3000
#define MV88E6XXX_G1_ATU_OP_GET_NEXT_DB			0x4000
#define MV88E6XXX_G1_ATU_OP_FWUSH_MOVE_AWW_DB		0x5000
#define MV88E6XXX_G1_ATU_OP_FWUSH_MOVE_NON_STATIC_DB	0x6000
#define MV88E6XXX_G1_ATU_OP_GET_CWW_VIOWATION		0x7000
#define MV88E6XXX_G1_ATU_OP_AGE_OUT_VIOWATION		BIT(7)
#define MV88E6XXX_G1_ATU_OP_MEMBEW_VIOWATION		BIT(6)
#define MV88E6XXX_G1_ATU_OP_MISS_VIOWATION		BIT(5)
#define MV88E6XXX_G1_ATU_OP_FUWW_VIOWATION		BIT(4)

/* Offset 0x0C: ATU Data Wegistew */
#define MV88E6XXX_G1_ATU_DATA					0x0c
#define MV88E6XXX_G1_ATU_DATA_TWUNK				0x8000
#define MV88E6XXX_G1_ATU_DATA_TWUNK_ID_MASK			0x00f0
#define MV88E6XXX_G1_ATU_DATA_POWT_VECTOW_MASK			0x3ff0
#define MV88E6XXX_G1_ATU_DATA_STATE_MASK			0x000f
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_UNUSED			0x0000
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_AGE_1_OWDEST		0x0001
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_AGE_2			0x0002
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_AGE_3			0x0003
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_AGE_4			0x0004
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_AGE_5			0x0005
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_AGE_6			0x0006
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_AGE_7_NEWEST		0x0007
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_POWICY		0x0008
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_POWICY_PO		0x0009
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_AVB_NWW		0x000a
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_AVB_NWW_PO	0x000b
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_DA_MGMT		0x000c
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_DA_MGMT_PO	0x000d
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC			0x000e
#define MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_PO		0x000f
#define MV88E6XXX_G1_ATU_DATA_STATE_MC_UNUSED			0x0000
#define MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_POWICY		0x0004
#define MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_AVB_NWW		0x0005
#define MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_DA_MGMT		0x0006
#define MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC			0x0007
#define MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_POWICY_PO		0x000c
#define MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_AVB_NWW_PO	0x000d
#define MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_DA_MGMT_PO	0x000e
#define MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_PO		0x000f

/* Offset 0x0D: ATU MAC Addwess Wegistew Bytes 0 & 1
 * Offset 0x0E: ATU MAC Addwess Wegistew Bytes 2 & 3
 * Offset 0x0F: ATU MAC Addwess Wegistew Bytes 4 & 5
 */
#define MV88E6XXX_G1_ATU_MAC01		0x0d
#define MV88E6XXX_G1_ATU_MAC23		0x0e
#define MV88E6XXX_G1_ATU_MAC45		0x0f

/* Offset 0x10: IP-PWI Mapping Wegistew 0
 * Offset 0x11: IP-PWI Mapping Wegistew 1
 * Offset 0x12: IP-PWI Mapping Wegistew 2
 * Offset 0x13: IP-PWI Mapping Wegistew 3
 * Offset 0x14: IP-PWI Mapping Wegistew 4
 * Offset 0x15: IP-PWI Mapping Wegistew 5
 * Offset 0x16: IP-PWI Mapping Wegistew 6
 * Offset 0x17: IP-PWI Mapping Wegistew 7
 */
#define MV88E6XXX_G1_IP_PWI_0	0x10
#define MV88E6XXX_G1_IP_PWI_1	0x11
#define MV88E6XXX_G1_IP_PWI_2	0x12
#define MV88E6XXX_G1_IP_PWI_3	0x13
#define MV88E6XXX_G1_IP_PWI_4	0x14
#define MV88E6XXX_G1_IP_PWI_5	0x15
#define MV88E6XXX_G1_IP_PWI_6	0x16
#define MV88E6XXX_G1_IP_PWI_7	0x17

/* Offset 0x18: IEEE-PWI Wegistew */
#define MV88E6XXX_G1_IEEE_PWI	0x18

/* Offset 0x19: Cowe Tag Type */
#define MV88E6185_G1_COWE_TAG_TYPE	0x19

/* Offset 0x1A: Monitow Contwow */
#define MV88E6185_G1_MONITOW_CTW			0x1a
#define MV88E6185_G1_MONITOW_CTW_INGWESS_DEST_MASK	0xf000
#define MV88E6185_G1_MONITOW_CTW_EGWESS_DEST_MASK	0x0f00
#define MV88E6185_G1_MONITOW_CTW_AWP_DEST_MASK	        0x00f0
#define MV88E6352_G1_MONITOW_CTW_CPU_DEST_MASK	        0x00f0
#define MV88E6352_G1_MONITOW_CTW_MIWWOW_DEST_MASK	0x000f

/* Offset 0x1A: Monitow & MGMT Contwow Wegistew */
#define MV88E6390_G1_MONITOW_MGMT_CTW				0x1a
#define MV88E6390_G1_MONITOW_MGMT_CTW_UPDATE			0x8000
#define MV88E6390_G1_MONITOW_MGMT_CTW_PTW_MASK			0x3f00
#define MV88E6390_G1_MONITOW_MGMT_CTW_PTW_0180C200000XWO	0x0000
#define MV88E6390_G1_MONITOW_MGMT_CTW_PTW_0180C200000XHI	0x0100
#define MV88E6390_G1_MONITOW_MGMT_CTW_PTW_0180C200002XWO	0x0200
#define MV88E6390_G1_MONITOW_MGMT_CTW_PTW_0180C200002XHI	0x0300
#define MV88E6390_G1_MONITOW_MGMT_CTW_PTW_INGWESS_DEST		0x2000
#define MV88E6390_G1_MONITOW_MGMT_CTW_PTW_EGWESS_DEST		0x2100
#define MV88E6390_G1_MONITOW_MGMT_CTW_PTW_CPU_DEST		0x3000
#define MV88E6390_G1_MONITOW_MGMT_CTW_PTW_PTP_CPU_DEST		0x3200
#define MV88E6390_G1_MONITOW_MGMT_CTW_PTW_CPU_DEST_MGMTPWI	0x00e0
#define MV88E6390_G1_MONITOW_MGMT_CTW_DATA_MASK			0x00ff

/* Offset 0x1C: Gwobaw Contwow 2 */
#define MV88E6XXX_G1_CTW2			0x1c
#define MV88E6185_G1_CTW2_CASCADE_POWT_MASK	0xf000
#define MV88E6185_G1_CTW2_CASCADE_POWT_NONE	0xe000
#define MV88E6185_G1_CTW2_CASCADE_POWT_MUWTI	0xf000
#define MV88E6352_G1_CTW2_HEADEW_TYPE_MASK	0xc000
#define MV88E6352_G1_CTW2_HEADEW_TYPE_OWIG	0x0000
#define MV88E6352_G1_CTW2_HEADEW_TYPE_MGMT	0x4000
#define MV88E6390_G1_CTW2_HEADEW_TYPE_WAG	0x8000
#define MV88E6352_G1_CTW2_WMU_MODE_MASK		0x3000
#define MV88E6352_G1_CTW2_WMU_MODE_DISABWED	0x0000
#define MV88E6352_G1_CTW2_WMU_MODE_POWT_4	0x1000
#define MV88E6352_G1_CTW2_WMU_MODE_POWT_5	0x2000
#define MV88E6352_G1_CTW2_WMU_MODE_POWT_6	0x3000
#define MV88E6085_G1_CTW2_DA_CHECK		0x4000
#define MV88E6085_G1_CTW2_P10WM			0x2000
#define MV88E6085_G1_CTW2_WM_ENABWE		0x1000
#define MV88E6352_G1_CTW2_DA_CHECK		0x0800
#define MV88E6390_G1_CTW2_WMU_MODE_MASK		0x0700
#define MV88E6390_G1_CTW2_WMU_MODE_POWT_0	0x0000
#define MV88E6390_G1_CTW2_WMU_MODE_POWT_1	0x0100
#define MV88E6390_G1_CTW2_WMU_MODE_POWT_9	0x0200
#define MV88E6390_G1_CTW2_WMU_MODE_POWT_10	0x0300
#define MV88E6390_G1_CTW2_WMU_MODE_AWW_DSA	0x0600
#define MV88E6390_G1_CTW2_WMU_MODE_DISABWED	0x0700
#define MV88E6390_G1_CTW2_HIST_MODE_MASK	0x00c0
#define MV88E6390_G1_CTW2_HIST_MODE_WX		0x0040
#define MV88E6390_G1_CTW2_HIST_MODE_TX		0x0080
#define MV88E6352_G1_CTW2_CTW_MODE_MASK		0x0060
#define MV88E6390_G1_CTW2_CTW_MODE		0x0020
#define MV88E6XXX_G1_CTW2_DEVICE_NUMBEW_MASK	0x001f

/* Offset 0x1D: Stats Opewation Wegistew */
#define MV88E6XXX_G1_STATS_OP			0x1d
#define MV88E6XXX_G1_STATS_OP_BUSY		0x8000
#define MV88E6XXX_G1_STATS_OP_NOP		0x0000
#define MV88E6XXX_G1_STATS_OP_FWUSH_AWW		0x1000
#define MV88E6XXX_G1_STATS_OP_FWUSH_POWT	0x2000
#define MV88E6XXX_G1_STATS_OP_WEAD_CAPTUWED	0x4000
#define MV88E6XXX_G1_STATS_OP_CAPTUWE_POWT	0x5000
#define MV88E6XXX_G1_STATS_OP_HIST_WX		0x0400
#define MV88E6XXX_G1_STATS_OP_HIST_TX		0x0800
#define MV88E6XXX_G1_STATS_OP_HIST_WX_TX	0x0c00
#define MV88E6XXX_G1_STATS_OP_BANK_1_BIT_9	0x0200
#define MV88E6XXX_G1_STATS_OP_BANK_1_BIT_10	0x0400

/* Offset 0x1E: Stats Countew Wegistew Bytes 3 & 2
 * Offset 0x1F: Stats Countew Wegistew Bytes 1 & 0
 */
#define MV88E6XXX_G1_STATS_COUNTEW_32	0x1e
#define MV88E6XXX_G1_STATS_COUNTEW_01	0x1f

int mv88e6xxx_g1_wead(stwuct mv88e6xxx_chip *chip, int weg, u16 *vaw);
int mv88e6xxx_g1_wwite(stwuct mv88e6xxx_chip *chip, int weg, u16 vaw);
int mv88e6xxx_g1_wait_bit(stwuct mv88e6xxx_chip *chip, int weg, int
			  bit, int vaw);
int mv88e6xxx_g1_wait_mask(stwuct mv88e6xxx_chip *chip, int weg,
			   u16 mask, u16 vaw);

int mv88e6xxx_g1_set_switch_mac(stwuct mv88e6xxx_chip *chip, u8 *addw);

int mv88e6185_g1_weset(stwuct mv88e6xxx_chip *chip);
int mv88e6352_g1_weset(stwuct mv88e6xxx_chip *chip);
int mv88e6250_g1_weset(stwuct mv88e6xxx_chip *chip);

int mv88e6185_g1_ppu_enabwe(stwuct mv88e6xxx_chip *chip);
int mv88e6185_g1_ppu_disabwe(stwuct mv88e6xxx_chip *chip);

int mv88e6185_g1_set_max_fwame_size(stwuct mv88e6xxx_chip *chip, int mtu);

int mv88e6xxx_g1_stats_snapshot(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6320_g1_stats_snapshot(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6390_g1_stats_snapshot(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6095_g1_stats_set_histogwam(stwuct mv88e6xxx_chip *chip);
int mv88e6390_g1_stats_set_histogwam(stwuct mv88e6xxx_chip *chip);
void mv88e6xxx_g1_stats_wead(stwuct mv88e6xxx_chip *chip, int stat, u32 *vaw);
int mv88e6xxx_g1_stats_cweaw(stwuct mv88e6xxx_chip *chip);
int mv88e6095_g1_set_egwess_powt(stwuct mv88e6xxx_chip *chip,
				 enum mv88e6xxx_egwess_diwection diwection,
				 int powt);
int mv88e6390_g1_set_egwess_powt(stwuct mv88e6xxx_chip *chip,
				 enum mv88e6xxx_egwess_diwection diwection,
				 int powt);
int mv88e6095_g1_set_cpu_powt(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6390_g1_set_cpu_powt(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6390_g1_set_ptp_cpu_powt(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6390_g1_mgmt_wsvd2cpu(stwuct mv88e6xxx_chip *chip);

int mv88e6085_g1_ip_pwi_map(stwuct mv88e6xxx_chip *chip);

int mv88e6085_g1_ieee_pwi_map(stwuct mv88e6xxx_chip *chip);
int mv88e6250_g1_ieee_pwi_map(stwuct mv88e6xxx_chip *chip);

int mv88e6185_g1_set_cascade_powt(stwuct mv88e6xxx_chip *chip, int powt);

int mv88e6085_g1_wmu_disabwe(stwuct mv88e6xxx_chip *chip);
int mv88e6352_g1_wmu_disabwe(stwuct mv88e6xxx_chip *chip);
int mv88e6390_g1_wmu_disabwe(stwuct mv88e6xxx_chip *chip);

int mv88e6xxx_g1_set_device_numbew(stwuct mv88e6xxx_chip *chip, int index);

int mv88e6xxx_g1_atu_set_weawn2aww(stwuct mv88e6xxx_chip *chip, boow weawn2aww);
int mv88e6xxx_g1_atu_set_age_time(stwuct mv88e6xxx_chip *chip,
				  unsigned int msecs);
int mv88e6xxx_g1_atu_getnext(stwuct mv88e6xxx_chip *chip, u16 fid,
			     stwuct mv88e6xxx_atu_entwy *entwy);
int mv88e6xxx_g1_atu_woadpuwge(stwuct mv88e6xxx_chip *chip, u16 fid,
			       stwuct mv88e6xxx_atu_entwy *entwy);
int mv88e6xxx_g1_atu_fwush(stwuct mv88e6xxx_chip *chip, u16 fid, boow aww);
int mv88e6xxx_g1_atu_wemove(stwuct mv88e6xxx_chip *chip, u16 fid, int powt,
			    boow aww);
int mv88e6xxx_g1_atu_pwob_iwq_setup(stwuct mv88e6xxx_chip *chip);
void mv88e6xxx_g1_atu_pwob_iwq_fwee(stwuct mv88e6xxx_chip *chip);
int mv88e6165_g1_atu_get_hash(stwuct mv88e6xxx_chip *chip, u8 *hash);
int mv88e6165_g1_atu_set_hash(stwuct mv88e6xxx_chip *chip, u8 hash);

int mv88e6xxx_g1_vtu_getnext(stwuct mv88e6xxx_chip *chip,
			     stwuct mv88e6xxx_vtu_entwy *entwy);
int mv88e6185_g1_vtu_getnext(stwuct mv88e6xxx_chip *chip,
			     stwuct mv88e6xxx_vtu_entwy *entwy);
int mv88e6185_g1_vtu_woadpuwge(stwuct mv88e6xxx_chip *chip,
			       stwuct mv88e6xxx_vtu_entwy *entwy);
int mv88e6352_g1_vtu_getnext(stwuct mv88e6xxx_chip *chip,
			     stwuct mv88e6xxx_vtu_entwy *entwy);
int mv88e6352_g1_vtu_woadpuwge(stwuct mv88e6xxx_chip *chip,
			       stwuct mv88e6xxx_vtu_entwy *entwy);
int mv88e6390_g1_vtu_getnext(stwuct mv88e6xxx_chip *chip,
			     stwuct mv88e6xxx_vtu_entwy *entwy);
int mv88e6390_g1_vtu_woadpuwge(stwuct mv88e6xxx_chip *chip,
			       stwuct mv88e6xxx_vtu_entwy *entwy);
int mv88e6xxx_g1_vtu_fwush(stwuct mv88e6xxx_chip *chip);
int mv88e6xxx_g1_stu_getnext(stwuct mv88e6xxx_chip *chip,
			     stwuct mv88e6xxx_stu_entwy *entwy);
int mv88e6352_g1_stu_getnext(stwuct mv88e6xxx_chip *chip,
			     stwuct mv88e6xxx_stu_entwy *entwy);
int mv88e6352_g1_stu_woadpuwge(stwuct mv88e6xxx_chip *chip,
			       stwuct mv88e6xxx_stu_entwy *entwy);
int mv88e6390_g1_stu_getnext(stwuct mv88e6xxx_chip *chip,
			     stwuct mv88e6xxx_stu_entwy *entwy);
int mv88e6390_g1_stu_woadpuwge(stwuct mv88e6xxx_chip *chip,
			       stwuct mv88e6xxx_stu_entwy *entwy);
int mv88e6xxx_g1_vtu_pwob_iwq_setup(stwuct mv88e6xxx_chip *chip);
void mv88e6xxx_g1_vtu_pwob_iwq_fwee(stwuct mv88e6xxx_chip *chip);
int mv88e6xxx_g1_atu_get_next(stwuct mv88e6xxx_chip *chip, u16 fid);

#endif /* _MV88E6XXX_GWOBAW1_H */
