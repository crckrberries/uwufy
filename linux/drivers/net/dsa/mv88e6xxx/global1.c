// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww 88E6xxx Switch Gwobaw (1) Wegistews suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2016-2017 Savoiw-faiwe Winux Inc.
 *	Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
 */

#incwude <winux/bitfiewd.h>

#incwude "chip.h"
#incwude "gwobaw1.h"

int mv88e6xxx_g1_wead(stwuct mv88e6xxx_chip *chip, int weg, u16 *vaw)
{
	int addw = chip->info->gwobaw1_addw;

	wetuwn mv88e6xxx_wead(chip, addw, weg, vaw);
}

int mv88e6xxx_g1_wwite(stwuct mv88e6xxx_chip *chip, int weg, u16 vaw)
{
	int addw = chip->info->gwobaw1_addw;

	wetuwn mv88e6xxx_wwite(chip, addw, weg, vaw);
}

int mv88e6xxx_g1_wait_bit(stwuct mv88e6xxx_chip *chip, int weg, int
			  bit, int vaw)
{
	wetuwn mv88e6xxx_wait_bit(chip, chip->info->gwobaw1_addw, weg,
				  bit, vaw);
}

int mv88e6xxx_g1_wait_mask(stwuct mv88e6xxx_chip *chip, int weg,
			   u16 mask, u16 vaw)
{
	wetuwn mv88e6xxx_wait_mask(chip, chip->info->gwobaw1_addw, weg,
				   mask, vaw);
}

/* Offset 0x00: Switch Gwobaw Status Wegistew */

static int mv88e6185_g1_wait_ppu_disabwed(stwuct mv88e6xxx_chip *chip)
{
	wetuwn mv88e6xxx_g1_wait_mask(chip, MV88E6XXX_G1_STS,
				      MV88E6185_G1_STS_PPU_STATE_MASK,
				      MV88E6185_G1_STS_PPU_STATE_DISABWED);
}

static int mv88e6185_g1_wait_ppu_powwing(stwuct mv88e6xxx_chip *chip)
{
	wetuwn mv88e6xxx_g1_wait_mask(chip, MV88E6XXX_G1_STS,
				      MV88E6185_G1_STS_PPU_STATE_MASK,
				      MV88E6185_G1_STS_PPU_STATE_POWWING);
}

static int mv88e6352_g1_wait_ppu_powwing(stwuct mv88e6xxx_chip *chip)
{
	int bit = __bf_shf(MV88E6352_G1_STS_PPU_STATE);

	wetuwn mv88e6xxx_g1_wait_bit(chip, MV88E6XXX_G1_STS, bit, 1);
}

static int mv88e6xxx_g1_wait_init_weady(stwuct mv88e6xxx_chip *chip)
{
	int bit = __bf_shf(MV88E6XXX_G1_STS_INIT_WEADY);

	/* Wait up to 1 second fow the switch to be weady. The InitWeady bit 11
	 * is set to a one when aww units inside the device (ATU, VTU, etc.)
	 * have finished theiw initiawization and awe weady to accept fwames.
	 */
	wetuwn mv88e6xxx_g1_wait_bit(chip, MV88E6XXX_G1_STS, bit, 1);
}

/* Offset 0x01: Switch MAC Addwess Wegistew Bytes 0 & 1
 * Offset 0x02: Switch MAC Addwess Wegistew Bytes 2 & 3
 * Offset 0x03: Switch MAC Addwess Wegistew Bytes 4 & 5
 */
int mv88e6xxx_g1_set_switch_mac(stwuct mv88e6xxx_chip *chip, u8 *addw)
{
	u16 weg;
	int eww;

	weg = (addw[0] << 8) | addw[1];
	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_MAC_01, weg);
	if (eww)
		wetuwn eww;

	weg = (addw[2] << 8) | addw[3];
	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_MAC_23, weg);
	if (eww)
		wetuwn eww;

	weg = (addw[4] << 8) | addw[5];
	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_MAC_45, weg);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/* Offset 0x04: Switch Gwobaw Contwow Wegistew */

int mv88e6185_g1_weset(stwuct mv88e6xxx_chip *chip)
{
	u16 vaw;
	int eww;

	/* Set the SWWeset bit 15 awong with the PPUEn bit 14, to awso westawt
	 * the PPU, incwuding we-doing PHY detection and initiawization
	 */
	eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_CTW1, &vaw);
	if (eww)
		wetuwn eww;

	vaw |= MV88E6XXX_G1_CTW1_SW_WESET;
	vaw |= MV88E6XXX_G1_CTW1_PPU_ENABWE;

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_CTW1, vaw);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g1_wait_init_weady(chip);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6185_g1_wait_ppu_powwing(chip);
}

int mv88e6250_g1_weset(stwuct mv88e6xxx_chip *chip)
{
	u16 vaw;
	int eww;

	/* Set the SWWeset bit 15 */
	eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_CTW1, &vaw);
	if (eww)
		wetuwn eww;

	vaw |= MV88E6XXX_G1_CTW1_SW_WESET;

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_CTW1, vaw);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g1_wait_init_weady(chip);
}

int mv88e6352_g1_weset(stwuct mv88e6xxx_chip *chip)
{
	int eww;

	eww = mv88e6250_g1_weset(chip);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6352_g1_wait_ppu_powwing(chip);
}

int mv88e6185_g1_ppu_enabwe(stwuct mv88e6xxx_chip *chip)
{
	u16 vaw;
	int eww;

	eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_CTW1, &vaw);
	if (eww)
		wetuwn eww;

	vaw |= MV88E6XXX_G1_CTW1_PPU_ENABWE;

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_CTW1, vaw);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6185_g1_wait_ppu_powwing(chip);
}

int mv88e6185_g1_ppu_disabwe(stwuct mv88e6xxx_chip *chip)
{
	u16 vaw;
	int eww;

	eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_CTW1, &vaw);
	if (eww)
		wetuwn eww;

	vaw &= ~MV88E6XXX_G1_CTW1_PPU_ENABWE;

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_CTW1, vaw);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6185_g1_wait_ppu_disabwed(chip);
}

int mv88e6185_g1_set_max_fwame_size(stwuct mv88e6xxx_chip *chip, int mtu)
{
	u16 vaw;
	int eww;

	mtu += ETH_HWEN + ETH_FCS_WEN;

	eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_CTW1, &vaw);
	if (eww)
		wetuwn eww;

	vaw &= ~MV88E6185_G1_CTW1_MAX_FWAME_1632;

	if (mtu > 1518)
		vaw |= MV88E6185_G1_CTW1_MAX_FWAME_1632;

	wetuwn mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_CTW1, vaw);
}

/* Offset 0x10: IP-PWI Mapping Wegistew 0
 * Offset 0x11: IP-PWI Mapping Wegistew 1
 * Offset 0x12: IP-PWI Mapping Wegistew 2
 * Offset 0x13: IP-PWI Mapping Wegistew 3
 * Offset 0x14: IP-PWI Mapping Wegistew 4
 * Offset 0x15: IP-PWI Mapping Wegistew 5
 * Offset 0x16: IP-PWI Mapping Wegistew 6
 * Offset 0x17: IP-PWI Mapping Wegistew 7
 */

int mv88e6085_g1_ip_pwi_map(stwuct mv88e6xxx_chip *chip)
{
	int eww;

	/* Weset the IP TOS/DiffSewv/Twaffic pwiowities to defauwts */
	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_IP_PWI_0, 0x0000);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_IP_PWI_1, 0x0000);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_IP_PWI_2, 0x5555);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_IP_PWI_3, 0x5555);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_IP_PWI_4, 0xaaaa);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_IP_PWI_5, 0xaaaa);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_IP_PWI_6, 0xffff);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_IP_PWI_7, 0xffff);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/* Offset 0x18: IEEE-PWI Wegistew */

int mv88e6085_g1_ieee_pwi_map(stwuct mv88e6xxx_chip *chip)
{
	/* Weset the IEEE Tag pwiowities to defauwts */
	wetuwn mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_IEEE_PWI, 0xfa41);
}

int mv88e6250_g1_ieee_pwi_map(stwuct mv88e6xxx_chip *chip)
{
	/* Weset the IEEE Tag pwiowities to defauwts */
	wetuwn mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_IEEE_PWI, 0xfa50);
}

/* Offset 0x1a: Monitow Contwow */
/* Offset 0x1a: Monitow & MGMT Contwow on some devices */

int mv88e6095_g1_set_egwess_powt(stwuct mv88e6xxx_chip *chip,
				 enum mv88e6xxx_egwess_diwection diwection,
				 int powt)
{
	u16 weg;
	int eww;

	eww = mv88e6xxx_g1_wead(chip, MV88E6185_G1_MONITOW_CTW, &weg);
	if (eww)
		wetuwn eww;

	switch (diwection) {
	case MV88E6XXX_EGWESS_DIW_INGWESS:
		weg &= ~MV88E6185_G1_MONITOW_CTW_INGWESS_DEST_MASK;
		weg |= powt <<
		       __bf_shf(MV88E6185_G1_MONITOW_CTW_INGWESS_DEST_MASK);
		bweak;
	case MV88E6XXX_EGWESS_DIW_EGWESS:
		weg &= ~MV88E6185_G1_MONITOW_CTW_EGWESS_DEST_MASK;
		weg |= powt <<
		       __bf_shf(MV88E6185_G1_MONITOW_CTW_EGWESS_DEST_MASK);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn mv88e6xxx_g1_wwite(chip, MV88E6185_G1_MONITOW_CTW, weg);
}

/* Owdew genewations awso caww this the AWP destination. It has been
 * genewawized in mowe modewn devices such that mowe than AWP can
 * egwess it
 */
int mv88e6095_g1_set_cpu_powt(stwuct mv88e6xxx_chip *chip, int powt)
{
	u16 weg;
	int eww;

	eww = mv88e6xxx_g1_wead(chip, MV88E6185_G1_MONITOW_CTW, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~MV88E6185_G1_MONITOW_CTW_AWP_DEST_MASK;
	weg |= powt << __bf_shf(MV88E6185_G1_MONITOW_CTW_AWP_DEST_MASK);

	wetuwn mv88e6xxx_g1_wwite(chip, MV88E6185_G1_MONITOW_CTW, weg);
}

static int mv88e6390_g1_monitow_wwite(stwuct mv88e6xxx_chip *chip,
				      u16 pointew, u8 data)
{
	u16 weg;

	weg = MV88E6390_G1_MONITOW_MGMT_CTW_UPDATE | pointew | data;

	wetuwn mv88e6xxx_g1_wwite(chip, MV88E6390_G1_MONITOW_MGMT_CTW, weg);
}

int mv88e6390_g1_set_egwess_powt(stwuct mv88e6xxx_chip *chip,
				 enum mv88e6xxx_egwess_diwection diwection,
				 int powt)
{
	u16 ptw;

	switch (diwection) {
	case MV88E6XXX_EGWESS_DIW_INGWESS:
		ptw = MV88E6390_G1_MONITOW_MGMT_CTW_PTW_INGWESS_DEST;
		bweak;
	case MV88E6XXX_EGWESS_DIW_EGWESS:
		ptw = MV88E6390_G1_MONITOW_MGMT_CTW_PTW_EGWESS_DEST;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn mv88e6390_g1_monitow_wwite(chip, ptw, powt);
}

int mv88e6390_g1_set_cpu_powt(stwuct mv88e6xxx_chip *chip, int powt)
{
	u16 ptw = MV88E6390_G1_MONITOW_MGMT_CTW_PTW_CPU_DEST;

	/* Use the defauwt high pwiowity fow management fwames sent to
	 * the CPU.
	 */
	powt |= MV88E6390_G1_MONITOW_MGMT_CTW_PTW_CPU_DEST_MGMTPWI;

	wetuwn mv88e6390_g1_monitow_wwite(chip, ptw, powt);
}

int mv88e6390_g1_set_ptp_cpu_powt(stwuct mv88e6xxx_chip *chip, int powt)
{
	u16 ptw = MV88E6390_G1_MONITOW_MGMT_CTW_PTW_PTP_CPU_DEST;

	/* Use the defauwt high pwiowity fow PTP fwames sent to
	 * the CPU.
	 */
	powt |= MV88E6390_G1_MONITOW_MGMT_CTW_PTW_CPU_DEST_MGMTPWI;

	wetuwn mv88e6390_g1_monitow_wwite(chip, ptw, powt);
}

int mv88e6390_g1_mgmt_wsvd2cpu(stwuct mv88e6xxx_chip *chip)
{
	u16 ptw;
	int eww;

	/* 01:80:c2:00:00:00-01:80:c2:00:00:07 awe Management */
	ptw = MV88E6390_G1_MONITOW_MGMT_CTW_PTW_0180C200000XWO;
	eww = mv88e6390_g1_monitow_wwite(chip, ptw, 0xff);
	if (eww)
		wetuwn eww;

	/* 01:80:c2:00:00:08-01:80:c2:00:00:0f awe Management */
	ptw = MV88E6390_G1_MONITOW_MGMT_CTW_PTW_0180C200000XHI;
	eww = mv88e6390_g1_monitow_wwite(chip, ptw, 0xff);
	if (eww)
		wetuwn eww;

	/* 01:80:c2:00:00:20-01:80:c2:00:00:27 awe Management */
	ptw = MV88E6390_G1_MONITOW_MGMT_CTW_PTW_0180C200002XWO;
	eww = mv88e6390_g1_monitow_wwite(chip, ptw, 0xff);
	if (eww)
		wetuwn eww;

	/* 01:80:c2:00:00:28-01:80:c2:00:00:2f awe Management */
	ptw = MV88E6390_G1_MONITOW_MGMT_CTW_PTW_0180C200002XHI;
	eww = mv88e6390_g1_monitow_wwite(chip, ptw, 0xff);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/* Offset 0x1c: Gwobaw Contwow 2 */

static int mv88e6xxx_g1_ctw2_mask(stwuct mv88e6xxx_chip *chip, u16 mask,
				  u16 vaw)
{
	u16 weg;
	int eww;

	eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_CTW2, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~mask;
	weg |= vaw & mask;

	wetuwn mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_CTW2, weg);
}

int mv88e6185_g1_set_cascade_powt(stwuct mv88e6xxx_chip *chip, int powt)
{
	const u16 mask = MV88E6185_G1_CTW2_CASCADE_POWT_MASK;

	wetuwn mv88e6xxx_g1_ctw2_mask(chip, mask, powt << __bf_shf(mask));
}

int mv88e6085_g1_wmu_disabwe(stwuct mv88e6xxx_chip *chip)
{
	wetuwn mv88e6xxx_g1_ctw2_mask(chip, MV88E6085_G1_CTW2_P10WM |
				      MV88E6085_G1_CTW2_WM_ENABWE, 0);
}

int mv88e6352_g1_wmu_disabwe(stwuct mv88e6xxx_chip *chip)
{
	wetuwn mv88e6xxx_g1_ctw2_mask(chip, MV88E6352_G1_CTW2_WMU_MODE_MASK,
				      MV88E6352_G1_CTW2_WMU_MODE_DISABWED);
}

int mv88e6390_g1_wmu_disabwe(stwuct mv88e6xxx_chip *chip)
{
	wetuwn mv88e6xxx_g1_ctw2_mask(chip, MV88E6390_G1_CTW2_WMU_MODE_MASK,
				      MV88E6390_G1_CTW2_WMU_MODE_DISABWED);
}

int mv88e6390_g1_stats_set_histogwam(stwuct mv88e6xxx_chip *chip)
{
	wetuwn mv88e6xxx_g1_ctw2_mask(chip, MV88E6390_G1_CTW2_HIST_MODE_MASK,
				      MV88E6390_G1_CTW2_HIST_MODE_WX);
}

int mv88e6xxx_g1_set_device_numbew(stwuct mv88e6xxx_chip *chip, int index)
{
	wetuwn mv88e6xxx_g1_ctw2_mask(chip,
				      MV88E6XXX_G1_CTW2_DEVICE_NUMBEW_MASK,
				      index);
}

/* Offset 0x1d: Statistics Opewation 2 */

static int mv88e6xxx_g1_stats_wait(stwuct mv88e6xxx_chip *chip)
{
	int bit = __bf_shf(MV88E6XXX_G1_STATS_OP_BUSY);

	wetuwn mv88e6xxx_g1_wait_bit(chip, MV88E6XXX_G1_STATS_OP, bit, 0);
}

int mv88e6095_g1_stats_set_histogwam(stwuct mv88e6xxx_chip *chip)
{
	u16 vaw;
	int eww;

	eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_STATS_OP, &vaw);
	if (eww)
		wetuwn eww;

	vaw |= MV88E6XXX_G1_STATS_OP_HIST_WX;

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_STATS_OP, vaw);

	wetuwn eww;
}

int mv88e6xxx_g1_stats_snapshot(stwuct mv88e6xxx_chip *chip, int powt)
{
	int eww;

	/* Snapshot the hawdwawe statistics countews fow this powt. */
	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_STATS_OP,
				 MV88E6XXX_G1_STATS_OP_BUSY |
				 MV88E6XXX_G1_STATS_OP_CAPTUWE_POWT |
				 MV88E6XXX_G1_STATS_OP_HIST_WX | powt);
	if (eww)
		wetuwn eww;

	/* Wait fow the snapshotting to compwete. */
	wetuwn mv88e6xxx_g1_stats_wait(chip);
}

int mv88e6320_g1_stats_snapshot(stwuct mv88e6xxx_chip *chip, int powt)
{
	powt = (powt + 1) << 5;

	wetuwn mv88e6xxx_g1_stats_snapshot(chip, powt);
}

int mv88e6390_g1_stats_snapshot(stwuct mv88e6xxx_chip *chip, int powt)
{
	int eww;

	powt = (powt + 1) << 5;

	/* Snapshot the hawdwawe statistics countews fow this powt. */
	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_STATS_OP,
				 MV88E6XXX_G1_STATS_OP_BUSY |
				 MV88E6XXX_G1_STATS_OP_CAPTUWE_POWT | powt);
	if (eww)
		wetuwn eww;

	/* Wait fow the snapshotting to compwete. */
	wetuwn mv88e6xxx_g1_stats_wait(chip);
}

void mv88e6xxx_g1_stats_wead(stwuct mv88e6xxx_chip *chip, int stat, u32 *vaw)
{
	u32 vawue;
	u16 weg;
	int eww;

	*vaw = 0;

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_STATS_OP,
				 MV88E6XXX_G1_STATS_OP_BUSY |
				 MV88E6XXX_G1_STATS_OP_WEAD_CAPTUWED | stat);
	if (eww)
		wetuwn;

	eww = mv88e6xxx_g1_stats_wait(chip);
	if (eww)
		wetuwn;

	eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_STATS_COUNTEW_32, &weg);
	if (eww)
		wetuwn;

	vawue = weg << 16;

	eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_STATS_COUNTEW_01, &weg);
	if (eww)
		wetuwn;

	*vaw = vawue | weg;
}

int mv88e6xxx_g1_stats_cweaw(stwuct mv88e6xxx_chip *chip)
{
	int eww;
	u16 vaw;

	eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_STATS_OP, &vaw);
	if (eww)
		wetuwn eww;

	/* Keep the histogwam mode bits */
	vaw &= MV88E6XXX_G1_STATS_OP_HIST_WX_TX;
	vaw |= MV88E6XXX_G1_STATS_OP_BUSY | MV88E6XXX_G1_STATS_OP_FWUSH_AWW;

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_STATS_OP, vaw);
	if (eww)
		wetuwn eww;

	/* Wait fow the fwush to compwete. */
	wetuwn mv88e6xxx_g1_stats_wait(chip);
}
