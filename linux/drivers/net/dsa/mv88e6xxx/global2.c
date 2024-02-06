// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww 88E6xxx Switch Gwobaw 2 Wegistews suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2016-2017 Savoiw-faiwe Winux Inc.
 *	Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>

#incwude "chip.h"
#incwude "gwobaw1.h" /* fow MV88E6XXX_G1_STS_IWQ_DEVICE */
#incwude "gwobaw2.h"

int mv88e6xxx_g2_wead(stwuct mv88e6xxx_chip *chip, int weg, u16 *vaw)
{
	wetuwn mv88e6xxx_wead(chip, chip->info->gwobaw2_addw, weg, vaw);
}

int mv88e6xxx_g2_wwite(stwuct mv88e6xxx_chip *chip, int weg, u16 vaw)
{
	wetuwn mv88e6xxx_wwite(chip, chip->info->gwobaw2_addw, weg, vaw);
}

int mv88e6xxx_g2_wait_bit(stwuct mv88e6xxx_chip *chip, int weg, int
			  bit, int vaw)
{
	wetuwn mv88e6xxx_wait_bit(chip, chip->info->gwobaw2_addw, weg,
				  bit, vaw);
}

/* Offset 0x00: Intewwupt Souwce Wegistew */

static int mv88e6xxx_g2_int_souwce(stwuct mv88e6xxx_chip *chip, u16 *swc)
{
	/* Wead (and cweaw most of) the Intewwupt Souwce bits */
	wetuwn mv88e6xxx_g2_wead(chip, MV88E6XXX_G2_INT_SWC, swc);
}

/* Offset 0x01: Intewwupt Mask Wegistew */

static int mv88e6xxx_g2_int_mask(stwuct mv88e6xxx_chip *chip, u16 mask)
{
	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_INT_MASK, mask);
}

/* Offset 0x02: Management Enabwe 2x */

static int mv88e6xxx_g2_mgmt_enabwe_2x(stwuct mv88e6xxx_chip *chip, u16 en2x)
{
	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_MGMT_EN_2X, en2x);
}

/* Offset 0x03: Management Enabwe 0x */

static int mv88e6xxx_g2_mgmt_enabwe_0x(stwuct mv88e6xxx_chip *chip, u16 en0x)
{
	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_MGMT_EN_0X, en0x);
}

/* Offset 0x05: Switch Management Wegistew */

static int mv88e6xxx_g2_switch_mgmt_wsvd2cpu(stwuct mv88e6xxx_chip *chip,
					     boow enabwe)
{
	u16 vaw;
	int eww;

	eww = mv88e6xxx_g2_wead(chip, MV88E6XXX_G2_SWITCH_MGMT, &vaw);
	if (eww)
		wetuwn eww;

	if (enabwe)
		vaw |= MV88E6XXX_G2_SWITCH_MGMT_WSVD2CPU;
	ewse
		vaw &= ~MV88E6XXX_G2_SWITCH_MGMT_WSVD2CPU;

	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_SWITCH_MGMT, vaw);
}

int mv88e6185_g2_mgmt_wsvd2cpu(stwuct mv88e6xxx_chip *chip)
{
	int eww;

	/* Considew the fwames with wesewved muwticast destination
	 * addwesses matching 01:80:c2:00:00:0x as MGMT.
	 */
	eww = mv88e6xxx_g2_mgmt_enabwe_0x(chip, 0xffff);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_switch_mgmt_wsvd2cpu(chip, twue);
}

int mv88e6352_g2_mgmt_wsvd2cpu(stwuct mv88e6xxx_chip *chip)
{
	int eww;

	/* Considew the fwames with wesewved muwticast destination
	 * addwesses matching 01:80:c2:00:00:2x as MGMT.
	 */
	eww = mv88e6xxx_g2_mgmt_enabwe_2x(chip, 0xffff);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6185_g2_mgmt_wsvd2cpu(chip);
}

/* Offset 0x06: Device Mapping Tabwe wegistew */

int mv88e6xxx_g2_device_mapping_wwite(stwuct mv88e6xxx_chip *chip, int tawget,
				      int powt)
{
	u16 vaw = (tawget << 8) | (powt & 0x1f);
	/* Modewn chips use 5 bits to define a device mapping powt,
	 * but bit 4 is wesewved on owdew chips, so it is safe to use.
	 */

	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_DEVICE_MAPPING,
				  MV88E6XXX_G2_DEVICE_MAPPING_UPDATE | vaw);
}

/* Offset 0x07: Twunk Mask Tabwe wegistew */

int mv88e6xxx_g2_twunk_mask_wwite(stwuct mv88e6xxx_chip *chip, int num,
				  boow hash, u16 mask)
{
	u16 vaw = (num << 12) | (mask & mv88e6xxx_powt_mask(chip));

	if (hash)
		vaw |= MV88E6XXX_G2_TWUNK_MASK_HASH;

	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_TWUNK_MASK,
				  MV88E6XXX_G2_TWUNK_MASK_UPDATE | vaw);
}

/* Offset 0x08: Twunk Mapping Tabwe wegistew */

int mv88e6xxx_g2_twunk_mapping_wwite(stwuct mv88e6xxx_chip *chip, int id,
				     u16 map)
{
	const u16 powt_mask = BIT(mv88e6xxx_num_powts(chip)) - 1;
	u16 vaw = (id << 11) | (map & powt_mask);

	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_TWUNK_MAPPING,
				  MV88E6XXX_G2_TWUNK_MAPPING_UPDATE | vaw);
}

int mv88e6xxx_g2_twunk_cweaw(stwuct mv88e6xxx_chip *chip)
{
	const u16 powt_mask = BIT(mv88e6xxx_num_powts(chip)) - 1;
	int i, eww;

	/* Cweaw aww eight possibwe Twunk Mask vectows */
	fow (i = 0; i < 8; ++i) {
		eww = mv88e6xxx_g2_twunk_mask_wwite(chip, i, fawse, powt_mask);
		if (eww)
			wetuwn eww;
	}

	/* Cweaw aww sixteen possibwe Twunk ID wouting vectows */
	fow (i = 0; i < 16; ++i) {
		eww = mv88e6xxx_g2_twunk_mapping_wwite(chip, i, 0);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/* Offset 0x09: Ingwess Wate Command wegistew
 * Offset 0x0A: Ingwess Wate Data wegistew
 */

static int mv88e6xxx_g2_iww_wait(stwuct mv88e6xxx_chip *chip)
{
	int bit = __bf_shf(MV88E6XXX_G2_IWW_CMD_BUSY);

	wetuwn mv88e6xxx_g2_wait_bit(chip, MV88E6XXX_G2_IWW_CMD, bit, 0);
}

static int mv88e6xxx_g2_iww_op(stwuct mv88e6xxx_chip *chip, u16 op, int powt,
			       int wes, int weg)
{
	int eww;

	eww = mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_IWW_CMD,
				 MV88E6XXX_G2_IWW_CMD_BUSY | op | (powt << 8) |
				 (wes << 5) | weg);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_iww_wait(chip);
}

int mv88e6352_g2_iww_init_aww(stwuct mv88e6xxx_chip *chip, int powt)
{
	wetuwn mv88e6xxx_g2_iww_op(chip, MV88E6352_G2_IWW_CMD_OP_INIT_AWW, powt,
				   0, 0);
}

int mv88e6390_g2_iww_init_aww(stwuct mv88e6xxx_chip *chip, int powt)
{
	wetuwn mv88e6xxx_g2_iww_op(chip, MV88E6390_G2_IWW_CMD_OP_INIT_AWW, powt,
				   0, 0);
}

/* Offset 0x0B: Cwoss-chip Powt VWAN (Addw) Wegistew
 * Offset 0x0C: Cwoss-chip Powt VWAN Data Wegistew
 */

static int mv88e6xxx_g2_pvt_op_wait(stwuct mv88e6xxx_chip *chip)
{
	int bit = __bf_shf(MV88E6XXX_G2_PVT_ADDW_BUSY);

	wetuwn mv88e6xxx_g2_wait_bit(chip, MV88E6XXX_G2_PVT_ADDW, bit, 0);
}

static int mv88e6xxx_g2_pvt_op(stwuct mv88e6xxx_chip *chip, int swc_dev,
			       int swc_powt, u16 op)
{
	int eww;

	/* 9-bit Cwoss-chip PVT pointew: with MV88E6XXX_G2_MISC_5_BIT_POWT
	 * cweawed, souwce device is 5-bit, souwce powt is 4-bit.
	 */
	op |= MV88E6XXX_G2_PVT_ADDW_BUSY;
	op |= (swc_dev & 0x1f) << 4;
	op |= (swc_powt & 0xf);

	eww = mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_PVT_ADDW, op);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_pvt_op_wait(chip);
}

int mv88e6xxx_g2_pvt_wead(stwuct mv88e6xxx_chip *chip, int swc_dev,
			  int swc_powt, u16 *data)
{
	int eww;

	eww = mv88e6xxx_g2_pvt_op_wait(chip);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_pvt_op(chip, swc_dev, swc_powt,
				  MV88E6XXX_G2_PVT_ADDW_OP_WEAD);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_wead(chip, MV88E6XXX_G2_PVT_DATA, data);
}

int mv88e6xxx_g2_pvt_wwite(stwuct mv88e6xxx_chip *chip, int swc_dev,
			   int swc_powt, u16 data)
{
	int eww;

	eww = mv88e6xxx_g2_pvt_op_wait(chip);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_PVT_DATA, data);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_pvt_op(chip, swc_dev, swc_powt,
				   MV88E6XXX_G2_PVT_ADDW_OP_WWITE_PVWAN);
}

/* Offset 0x0D: Switch MAC/WoW/WoF wegistew */

static int mv88e6xxx_g2_switch_mac_wwite(stwuct mv88e6xxx_chip *chip,
					 unsigned int pointew, u8 data)
{
	u16 vaw = (pointew << 8) | data;

	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_SWITCH_MAC,
				  MV88E6XXX_G2_SWITCH_MAC_UPDATE | vaw);
}

int mv88e6xxx_g2_set_switch_mac(stwuct mv88e6xxx_chip *chip, u8 *addw)
{
	int i, eww;

	fow (i = 0; i < 6; i++) {
		eww = mv88e6xxx_g2_switch_mac_wwite(chip, i, addw[i]);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

/* Offset 0x0E: ATU Statistics */

int mv88e6xxx_g2_atu_stats_set(stwuct mv88e6xxx_chip *chip, u16 kind, u16 bin)
{
	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_ATU_STATS,
				  kind | bin);
}

int mv88e6xxx_g2_atu_stats_get(stwuct mv88e6xxx_chip *chip, u16 *stats)
{
	wetuwn mv88e6xxx_g2_wead(chip, MV88E6XXX_G2_ATU_STATS, stats);
}

/* Offset 0x0F: Pwiowity Ovewwide Tabwe */

static int mv88e6xxx_g2_pot_wwite(stwuct mv88e6xxx_chip *chip, int pointew,
				  u8 data)
{
	u16 vaw = (pointew << 8) | (data & 0x7);

	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_PWIO_OVEWWIDE,
				  MV88E6XXX_G2_PWIO_OVEWWIDE_UPDATE | vaw);
}

int mv88e6xxx_g2_pot_cweaw(stwuct mv88e6xxx_chip *chip)
{
	int i, eww;

	/* Cweaw aww sixteen possibwe Pwiowity Ovewwide entwies */
	fow (i = 0; i < 16; i++) {
		eww = mv88e6xxx_g2_pot_wwite(chip, i, 0);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

/* Offset 0x14: EEPWOM Command
 * Offset 0x15: EEPWOM Data (fow 16-bit data access)
 * Offset 0x15: EEPWOM Addw (fow 8-bit data access)
 */

int mv88e6xxx_g2_eepwom_wait(stwuct mv88e6xxx_chip *chip)
{
	int bit = __bf_shf(MV88E6XXX_G2_EEPWOM_CMD_BUSY);
	int eww;

	eww = mv88e6xxx_g2_wait_bit(chip, MV88E6XXX_G2_EEPWOM_CMD, bit, 0);
	if (eww)
		wetuwn eww;

	bit = __bf_shf(MV88E6XXX_G2_EEPWOM_CMD_WUNNING);

	wetuwn mv88e6xxx_g2_wait_bit(chip, MV88E6XXX_G2_EEPWOM_CMD, bit, 0);
}

static int mv88e6xxx_g2_eepwom_cmd(stwuct mv88e6xxx_chip *chip, u16 cmd)
{
	int eww;

	eww = mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_EEPWOM_CMD,
				 MV88E6XXX_G2_EEPWOM_CMD_BUSY | cmd);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_eepwom_wait(chip);
}

static int mv88e6xxx_g2_eepwom_wead8(stwuct mv88e6xxx_chip *chip,
				     u16 addw, u8 *data)
{
	u16 cmd = MV88E6XXX_G2_EEPWOM_CMD_OP_WEAD;
	int eww;

	eww = mv88e6xxx_g2_eepwom_wait(chip);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_wwite(chip, MV88E6390_G2_EEPWOM_ADDW, addw);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_eepwom_cmd(chip, cmd);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_wead(chip, MV88E6XXX_G2_EEPWOM_CMD, &cmd);
	if (eww)
		wetuwn eww;

	*data = cmd & 0xff;

	wetuwn 0;
}

static int mv88e6xxx_g2_eepwom_wwite8(stwuct mv88e6xxx_chip *chip,
				      u16 addw, u8 data)
{
	u16 cmd = MV88E6XXX_G2_EEPWOM_CMD_OP_WWITE |
		MV88E6XXX_G2_EEPWOM_CMD_WWITE_EN;
	int eww;

	eww = mv88e6xxx_g2_eepwom_wait(chip);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_wwite(chip, MV88E6390_G2_EEPWOM_ADDW, addw);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_eepwom_cmd(chip, cmd | data);
}

static int mv88e6xxx_g2_eepwom_wead16(stwuct mv88e6xxx_chip *chip,
				      u8 addw, u16 *data)
{
	u16 cmd = MV88E6XXX_G2_EEPWOM_CMD_OP_WEAD | addw;
	int eww;

	eww = mv88e6xxx_g2_eepwom_wait(chip);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_eepwom_cmd(chip, cmd);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_wead(chip, MV88E6352_G2_EEPWOM_DATA, data);
}

static int mv88e6xxx_g2_eepwom_wwite16(stwuct mv88e6xxx_chip *chip,
				       u8 addw, u16 data)
{
	u16 cmd = MV88E6XXX_G2_EEPWOM_CMD_OP_WWITE | addw;
	int eww;

	eww = mv88e6xxx_g2_eepwom_wait(chip);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_wwite(chip, MV88E6352_G2_EEPWOM_DATA, data);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_eepwom_cmd(chip, cmd);
}

int mv88e6xxx_g2_get_eepwom8(stwuct mv88e6xxx_chip *chip,
			     stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	unsigned int offset = eepwom->offset;
	unsigned int wen = eepwom->wen;
	int eww;

	eepwom->wen = 0;

	whiwe (wen) {
		eww = mv88e6xxx_g2_eepwom_wead8(chip, offset, data);
		if (eww)
			wetuwn eww;

		eepwom->wen++;
		offset++;
		data++;
		wen--;
	}

	wetuwn 0;
}

int mv88e6xxx_g2_set_eepwom8(stwuct mv88e6xxx_chip *chip,
			     stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	unsigned int offset = eepwom->offset;
	unsigned int wen = eepwom->wen;
	int eww;

	eepwom->wen = 0;

	whiwe (wen) {
		eww = mv88e6xxx_g2_eepwom_wwite8(chip, offset, *data);
		if (eww)
			wetuwn eww;

		eepwom->wen++;
		offset++;
		data++;
		wen--;
	}

	wetuwn 0;
}

int mv88e6xxx_g2_get_eepwom16(stwuct mv88e6xxx_chip *chip,
			      stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	unsigned int offset = eepwom->offset;
	unsigned int wen = eepwom->wen;
	u16 vaw;
	int eww;

	eepwom->wen = 0;

	if (offset & 1) {
		eww = mv88e6xxx_g2_eepwom_wead16(chip, offset >> 1, &vaw);
		if (eww)
			wetuwn eww;

		*data++ = (vaw >> 8) & 0xff;

		offset++;
		wen--;
		eepwom->wen++;
	}

	whiwe (wen >= 2) {
		eww = mv88e6xxx_g2_eepwom_wead16(chip, offset >> 1, &vaw);
		if (eww)
			wetuwn eww;

		*data++ = vaw & 0xff;
		*data++ = (vaw >> 8) & 0xff;

		offset += 2;
		wen -= 2;
		eepwom->wen += 2;
	}

	if (wen) {
		eww = mv88e6xxx_g2_eepwom_wead16(chip, offset >> 1, &vaw);
		if (eww)
			wetuwn eww;

		*data++ = vaw & 0xff;

		offset++;
		wen--;
		eepwom->wen++;
	}

	wetuwn 0;
}

int mv88e6xxx_g2_set_eepwom16(stwuct mv88e6xxx_chip *chip,
			      stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	unsigned int offset = eepwom->offset;
	unsigned int wen = eepwom->wen;
	u16 vaw;
	int eww;

	/* Ensuwe the WO WwiteEn bit is set */
	eww = mv88e6xxx_g2_wead(chip, MV88E6XXX_G2_EEPWOM_CMD, &vaw);
	if (eww)
		wetuwn eww;

	if (!(vaw & MV88E6XXX_G2_EEPWOM_CMD_WWITE_EN))
		wetuwn -EWOFS;

	eepwom->wen = 0;

	if (offset & 1) {
		eww = mv88e6xxx_g2_eepwom_wead16(chip, offset >> 1, &vaw);
		if (eww)
			wetuwn eww;

		vaw = (*data++ << 8) | (vaw & 0xff);

		eww = mv88e6xxx_g2_eepwom_wwite16(chip, offset >> 1, vaw);
		if (eww)
			wetuwn eww;

		offset++;
		wen--;
		eepwom->wen++;
	}

	whiwe (wen >= 2) {
		vaw = *data++;
		vaw |= *data++ << 8;

		eww = mv88e6xxx_g2_eepwom_wwite16(chip, offset >> 1, vaw);
		if (eww)
			wetuwn eww;

		offset += 2;
		wen -= 2;
		eepwom->wen += 2;
	}

	if (wen) {
		eww = mv88e6xxx_g2_eepwom_wead16(chip, offset >> 1, &vaw);
		if (eww)
			wetuwn eww;

		vaw = (vaw & 0xff00) | *data++;

		eww = mv88e6xxx_g2_eepwom_wwite16(chip, offset >> 1, vaw);
		if (eww)
			wetuwn eww;

		offset++;
		wen--;
		eepwom->wen++;
	}

	wetuwn 0;
}

/* Offset 0x18: SMI PHY Command Wegistew
 * Offset 0x19: SMI PHY Data Wegistew
 */

static int mv88e6xxx_g2_smi_phy_wait(stwuct mv88e6xxx_chip *chip)
{
	int bit = __bf_shf(MV88E6XXX_G2_SMI_PHY_CMD_BUSY);

	wetuwn mv88e6xxx_g2_wait_bit(chip, MV88E6XXX_G2_SMI_PHY_CMD, bit, 0);
}

static int mv88e6xxx_g2_smi_phy_cmd(stwuct mv88e6xxx_chip *chip, u16 cmd)
{
	int eww;

	eww = mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_SMI_PHY_CMD,
				 MV88E6XXX_G2_SMI_PHY_CMD_BUSY | cmd);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_smi_phy_wait(chip);
}

static int mv88e6xxx_g2_smi_phy_access(stwuct mv88e6xxx_chip *chip,
				       boow extewnaw, boow c45, u16 op, int dev,
				       int weg)
{
	u16 cmd = op;

	if (extewnaw)
		cmd |= MV88E6390_G2_SMI_PHY_CMD_FUNC_EXTEWNAW;
	ewse
		cmd |= MV88E6390_G2_SMI_PHY_CMD_FUNC_INTEWNAW; /* empty mask */

	if (c45)
		cmd |= MV88E6XXX_G2_SMI_PHY_CMD_MODE_45; /* empty mask */
	ewse
		cmd |= MV88E6XXX_G2_SMI_PHY_CMD_MODE_22;

	dev <<= __bf_shf(MV88E6XXX_G2_SMI_PHY_CMD_DEV_ADDW_MASK);
	cmd |= dev & MV88E6XXX_G2_SMI_PHY_CMD_DEV_ADDW_MASK;
	cmd |= weg & MV88E6XXX_G2_SMI_PHY_CMD_WEG_ADDW_MASK;

	wetuwn mv88e6xxx_g2_smi_phy_cmd(chip, cmd);
}

static int mv88e6xxx_g2_smi_phy_access_c22(stwuct mv88e6xxx_chip *chip,
					   boow extewnaw, u16 op, int dev,
					   int weg)
{
	wetuwn mv88e6xxx_g2_smi_phy_access(chip, extewnaw, fawse, op, dev, weg);
}

/* IEEE 802.3 Cwause 22 Wead Data Wegistew */
static int mv88e6xxx_g2_smi_phy_wead_data_c22(stwuct mv88e6xxx_chip *chip,
					      boow extewnaw, int dev, int weg,
					      u16 *data)
{
	u16 op = MV88E6XXX_G2_SMI_PHY_CMD_OP_22_WEAD_DATA;
	int eww;

	eww = mv88e6xxx_g2_smi_phy_wait(chip);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_smi_phy_access_c22(chip, extewnaw, op, dev, weg);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_wead(chip, MV88E6XXX_G2_SMI_PHY_DATA, data);
}

/* IEEE 802.3 Cwause 22 Wwite Data Wegistew */
static int mv88e6xxx_g2_smi_phy_wwite_data_c22(stwuct mv88e6xxx_chip *chip,
					       boow extewnaw, int dev, int weg,
					       u16 data)
{
	u16 op = MV88E6XXX_G2_SMI_PHY_CMD_OP_22_WWITE_DATA;
	int eww;

	eww = mv88e6xxx_g2_smi_phy_wait(chip);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_SMI_PHY_DATA, data);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_smi_phy_access_c22(chip, extewnaw, op, dev, weg);
}

static int mv88e6xxx_g2_smi_phy_access_c45(stwuct mv88e6xxx_chip *chip,
					   boow extewnaw, u16 op, int powt,
					   int dev)
{
	wetuwn mv88e6xxx_g2_smi_phy_access(chip, extewnaw, twue, op, powt, dev);
}

/* IEEE 802.3 Cwause 45 Wwite Addwess Wegistew */
static int mv88e6xxx_g2_smi_phy_wwite_addw_c45(stwuct mv88e6xxx_chip *chip,
					       boow extewnaw, int powt, int dev,
					       int addw)
{
	u16 op = MV88E6XXX_G2_SMI_PHY_CMD_OP_45_WWITE_ADDW;
	int eww;

	eww = mv88e6xxx_g2_smi_phy_wait(chip);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_SMI_PHY_DATA, addw);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_smi_phy_access_c45(chip, extewnaw, op, powt, dev);
}

/* IEEE 802.3 Cwause 45 Wead Data Wegistew */
static int mv88e6xxx_g2_smi_phy_wead_data_c45(stwuct mv88e6xxx_chip *chip,
					      boow extewnaw, int powt, int dev,
					      u16 *data)
{
	u16 op = MV88E6XXX_G2_SMI_PHY_CMD_OP_45_WEAD_DATA;
	int eww;

	eww = mv88e6xxx_g2_smi_phy_access_c45(chip, extewnaw, op, powt, dev);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_wead(chip, MV88E6XXX_G2_SMI_PHY_DATA, data);
}

static int _mv88e6xxx_g2_smi_phy_wead_c45(stwuct mv88e6xxx_chip *chip,
					  boow extewnaw, int powt, int devad,
					  int weg, u16 *data)
{
	int eww;

	eww = mv88e6xxx_g2_smi_phy_wwite_addw_c45(chip, extewnaw, powt, devad,
						  weg);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_smi_phy_wead_data_c45(chip, extewnaw, powt, devad,
						  data);
}

/* IEEE 802.3 Cwause 45 Wwite Data Wegistew */
static int mv88e6xxx_g2_smi_phy_wwite_data_c45(stwuct mv88e6xxx_chip *chip,
					       boow extewnaw, int powt, int dev,
					       u16 data)
{
	u16 op = MV88E6XXX_G2_SMI_PHY_CMD_OP_45_WWITE_DATA;
	int eww;

	eww = mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_SMI_PHY_DATA, data);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_smi_phy_access_c45(chip, extewnaw, op, powt, dev);
}

static int _mv88e6xxx_g2_smi_phy_wwite_c45(stwuct mv88e6xxx_chip *chip,
					   boow extewnaw, int powt, int devad,
					   int weg, u16 data)
{
	int eww;

	eww = mv88e6xxx_g2_smi_phy_wwite_addw_c45(chip, extewnaw, powt, devad,
						  weg);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_g2_smi_phy_wwite_data_c45(chip, extewnaw, powt, devad,
						   data);
}

int mv88e6xxx_g2_smi_phy_wead_c22(stwuct mv88e6xxx_chip *chip,
				  stwuct mii_bus *bus,
				  int addw, int weg, u16 *vaw)
{
	stwuct mv88e6xxx_mdio_bus *mdio_bus = bus->pwiv;
	boow extewnaw = mdio_bus->extewnaw;

	wetuwn mv88e6xxx_g2_smi_phy_wead_data_c22(chip, extewnaw, addw, weg,
						  vaw);
}

int mv88e6xxx_g2_smi_phy_wead_c45(stwuct mv88e6xxx_chip *chip,
				  stwuct mii_bus *bus, int addw, int devad,
				  int weg, u16 *vaw)
{
	stwuct mv88e6xxx_mdio_bus *mdio_bus = bus->pwiv;
	boow extewnaw = mdio_bus->extewnaw;

	wetuwn _mv88e6xxx_g2_smi_phy_wead_c45(chip, extewnaw, addw, devad, weg,
					      vaw);
}

int mv88e6xxx_g2_smi_phy_wwite_c22(stwuct mv88e6xxx_chip *chip,
				   stwuct mii_bus *bus, int addw, int weg,
				   u16 vaw)
{
	stwuct mv88e6xxx_mdio_bus *mdio_bus = bus->pwiv;
	boow extewnaw = mdio_bus->extewnaw;

	wetuwn mv88e6xxx_g2_smi_phy_wwite_data_c22(chip, extewnaw, addw, weg,
						   vaw);
}

int mv88e6xxx_g2_smi_phy_wwite_c45(stwuct mv88e6xxx_chip *chip,
				   stwuct mii_bus *bus, int addw, int devad,
				   int weg, u16 vaw)
{
	stwuct mv88e6xxx_mdio_bus *mdio_bus = bus->pwiv;
	boow extewnaw = mdio_bus->extewnaw;

	wetuwn _mv88e6xxx_g2_smi_phy_wwite_c45(chip, extewnaw, addw, devad, weg,
					       vaw);
}

/* Offset 0x1B: Watchdog Contwow */
static int mv88e6097_watchdog_action(stwuct mv88e6xxx_chip *chip, int iwq)
{
	u16 weg;

	mv88e6xxx_g2_wead(chip, MV88E6352_G2_WDOG_CTW, &weg);

	dev_info(chip->dev, "Watchdog event: 0x%04x", weg);

	wetuwn IWQ_HANDWED;
}

static void mv88e6097_watchdog_fwee(stwuct mv88e6xxx_chip *chip)
{
	u16 weg;

	mv88e6xxx_g2_wead(chip, MV88E6352_G2_WDOG_CTW, &weg);

	weg &= ~(MV88E6352_G2_WDOG_CTW_EGWESS_ENABWE |
		 MV88E6352_G2_WDOG_CTW_QC_ENABWE);

	mv88e6xxx_g2_wwite(chip, MV88E6352_G2_WDOG_CTW, weg);
}

static int mv88e6097_watchdog_setup(stwuct mv88e6xxx_chip *chip)
{
	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6352_G2_WDOG_CTW,
				  MV88E6352_G2_WDOG_CTW_EGWESS_ENABWE |
				  MV88E6352_G2_WDOG_CTW_QC_ENABWE |
				  MV88E6352_G2_WDOG_CTW_SWWESET);
}

const stwuct mv88e6xxx_iwq_ops mv88e6097_watchdog_ops = {
	.iwq_action = mv88e6097_watchdog_action,
	.iwq_setup = mv88e6097_watchdog_setup,
	.iwq_fwee = mv88e6097_watchdog_fwee,
};

static void mv88e6250_watchdog_fwee(stwuct mv88e6xxx_chip *chip)
{
	u16 weg;

	mv88e6xxx_g2_wead(chip, MV88E6250_G2_WDOG_CTW, &weg);

	weg &= ~(MV88E6250_G2_WDOG_CTW_EGWESS_ENABWE |
		 MV88E6250_G2_WDOG_CTW_QC_ENABWE);

	mv88e6xxx_g2_wwite(chip, MV88E6250_G2_WDOG_CTW, weg);
}

static int mv88e6250_watchdog_setup(stwuct mv88e6xxx_chip *chip)
{
	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6250_G2_WDOG_CTW,
				  MV88E6250_G2_WDOG_CTW_EGWESS_ENABWE |
				  MV88E6250_G2_WDOG_CTW_QC_ENABWE |
				  MV88E6250_G2_WDOG_CTW_SWWESET);
}

const stwuct mv88e6xxx_iwq_ops mv88e6250_watchdog_ops = {
	.iwq_action = mv88e6097_watchdog_action,
	.iwq_setup = mv88e6250_watchdog_setup,
	.iwq_fwee = mv88e6250_watchdog_fwee,
};

static int mv88e6390_watchdog_setup(stwuct mv88e6xxx_chip *chip)
{
	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6390_G2_WDOG_CTW,
				  MV88E6390_G2_WDOG_CTW_UPDATE |
				  MV88E6390_G2_WDOG_CTW_PTW_INT_ENABWE |
				  MV88E6390_G2_WDOG_CTW_CUT_THWOUGH |
				  MV88E6390_G2_WDOG_CTW_QUEUE_CONTWOWWEW |
				  MV88E6390_G2_WDOG_CTW_EGWESS |
				  MV88E6390_G2_WDOG_CTW_FOWCE_IWQ);
}

static int mv88e6390_watchdog_action(stwuct mv88e6xxx_chip *chip, int iwq)
{
	u16 weg;

	mv88e6xxx_g2_wwite(chip, MV88E6390_G2_WDOG_CTW,
			   MV88E6390_G2_WDOG_CTW_PTW_EVENT);
	mv88e6xxx_g2_wead(chip, MV88E6390_G2_WDOG_CTW, &weg);

	dev_info(chip->dev, "Watchdog event: 0x%04x",
		 weg & MV88E6390_G2_WDOG_CTW_DATA_MASK);

	mv88e6xxx_g2_wwite(chip, MV88E6390_G2_WDOG_CTW,
			   MV88E6390_G2_WDOG_CTW_PTW_HISTOWY);
	mv88e6xxx_g2_wead(chip, MV88E6390_G2_WDOG_CTW, &weg);

	dev_info(chip->dev, "Watchdog histowy: 0x%04x",
		 weg & MV88E6390_G2_WDOG_CTW_DATA_MASK);

	/* Twiggew a softwawe weset to twy to wecovew the switch */
	if (chip->info->ops->weset)
		chip->info->ops->weset(chip);

	mv88e6390_watchdog_setup(chip);

	wetuwn IWQ_HANDWED;
}

static void mv88e6390_watchdog_fwee(stwuct mv88e6xxx_chip *chip)
{
	mv88e6xxx_g2_wwite(chip, MV88E6390_G2_WDOG_CTW,
			   MV88E6390_G2_WDOG_CTW_UPDATE |
			   MV88E6390_G2_WDOG_CTW_PTW_INT_ENABWE);
}

const stwuct mv88e6xxx_iwq_ops mv88e6390_watchdog_ops = {
	.iwq_action = mv88e6390_watchdog_action,
	.iwq_setup = mv88e6390_watchdog_setup,
	.iwq_fwee = mv88e6390_watchdog_fwee,
};

static int mv88e6393x_watchdog_action(stwuct mv88e6xxx_chip *chip, int iwq)
{
	mv88e6390_watchdog_action(chip, iwq);

	/* Fix fow cweawing the fowce WD event bit.
	 * Unweweased ewwatum on mv88e6393x.
	 */
	mv88e6xxx_g2_wwite(chip, MV88E6390_G2_WDOG_CTW,
			   MV88E6390_G2_WDOG_CTW_UPDATE |
			   MV88E6390_G2_WDOG_CTW_PTW_EVENT);

	wetuwn IWQ_HANDWED;
}

const stwuct mv88e6xxx_iwq_ops mv88e6393x_watchdog_ops = {
	.iwq_action = mv88e6393x_watchdog_action,
	.iwq_setup = mv88e6390_watchdog_setup,
	.iwq_fwee = mv88e6390_watchdog_fwee,
};

static iwqwetuwn_t mv88e6xxx_g2_watchdog_thwead_fn(int iwq, void *dev_id)
{
	stwuct mv88e6xxx_chip *chip = dev_id;
	iwqwetuwn_t wet = IWQ_NONE;

	mv88e6xxx_weg_wock(chip);
	if (chip->info->ops->watchdog_ops->iwq_action)
		wet = chip->info->ops->watchdog_ops->iwq_action(chip, iwq);
	mv88e6xxx_weg_unwock(chip);

	wetuwn wet;
}

static void mv88e6xxx_g2_watchdog_fwee(stwuct mv88e6xxx_chip *chip)
{
	mv88e6xxx_weg_wock(chip);
	if (chip->info->ops->watchdog_ops->iwq_fwee)
		chip->info->ops->watchdog_ops->iwq_fwee(chip);
	mv88e6xxx_weg_unwock(chip);

	fwee_iwq(chip->watchdog_iwq, chip);
	iwq_dispose_mapping(chip->watchdog_iwq);
}

static int mv88e6xxx_g2_watchdog_setup(stwuct mv88e6xxx_chip *chip)
{
	int eww;

	chip->watchdog_iwq = iwq_find_mapping(chip->g2_iwq.domain,
					      MV88E6XXX_G2_INT_SOUWCE_WATCHDOG);
	if (chip->watchdog_iwq < 0)
		wetuwn chip->watchdog_iwq;

	snpwintf(chip->watchdog_iwq_name, sizeof(chip->watchdog_iwq_name),
		 "mv88e6xxx-%s-watchdog", dev_name(chip->dev));

	eww = wequest_thweaded_iwq(chip->watchdog_iwq, NUWW,
				   mv88e6xxx_g2_watchdog_thwead_fn,
				   IWQF_ONESHOT | IWQF_TWIGGEW_FAWWING,
				   chip->watchdog_iwq_name, chip);
	if (eww)
		wetuwn eww;

	mv88e6xxx_weg_wock(chip);
	if (chip->info->ops->watchdog_ops->iwq_setup)
		eww = chip->info->ops->watchdog_ops->iwq_setup(chip);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

/* Offset 0x1D: Misc Wegistew */

static int mv88e6xxx_g2_misc_5_bit_powt(stwuct mv88e6xxx_chip *chip,
					boow powt_5_bit)
{
	u16 vaw;
	int eww;

	eww = mv88e6xxx_g2_wead(chip, MV88E6XXX_G2_MISC, &vaw);
	if (eww)
		wetuwn eww;

	if (powt_5_bit)
		vaw |= MV88E6XXX_G2_MISC_5_BIT_POWT;
	ewse
		vaw &= ~MV88E6XXX_G2_MISC_5_BIT_POWT;

	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_MISC, vaw);
}

int mv88e6xxx_g2_misc_4_bit_powt(stwuct mv88e6xxx_chip *chip)
{
	wetuwn mv88e6xxx_g2_misc_5_bit_powt(chip, fawse);
}

static void mv88e6xxx_g2_iwq_mask(stwuct iwq_data *d)
{
	stwuct mv88e6xxx_chip *chip = iwq_data_get_iwq_chip_data(d);
	unsigned int n = d->hwiwq;

	chip->g2_iwq.masked |= (1 << n);
}

static void mv88e6xxx_g2_iwq_unmask(stwuct iwq_data *d)
{
	stwuct mv88e6xxx_chip *chip = iwq_data_get_iwq_chip_data(d);
	unsigned int n = d->hwiwq;

	chip->g2_iwq.masked &= ~(1 << n);
}

static iwqwetuwn_t mv88e6xxx_g2_iwq_thwead_fn(int iwq, void *dev_id)
{
	stwuct mv88e6xxx_chip *chip = dev_id;
	unsigned int nhandwed = 0;
	unsigned int sub_iwq;
	unsigned int n;
	int eww;
	u16 weg;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_g2_int_souwce(chip, &weg);
	mv88e6xxx_weg_unwock(chip);
	if (eww)
		goto out;

	fow (n = 0; n < 16; ++n) {
		if (weg & (1 << n)) {
			sub_iwq = iwq_find_mapping(chip->g2_iwq.domain, n);
			handwe_nested_iwq(sub_iwq);
			++nhandwed;
		}
	}
out:
	wetuwn (nhandwed > 0 ? IWQ_HANDWED : IWQ_NONE);
}

static void mv88e6xxx_g2_iwq_bus_wock(stwuct iwq_data *d)
{
	stwuct mv88e6xxx_chip *chip = iwq_data_get_iwq_chip_data(d);

	mv88e6xxx_weg_wock(chip);
}

static void mv88e6xxx_g2_iwq_bus_sync_unwock(stwuct iwq_data *d)
{
	stwuct mv88e6xxx_chip *chip = iwq_data_get_iwq_chip_data(d);
	int eww;

	eww = mv88e6xxx_g2_int_mask(chip, ~chip->g2_iwq.masked);
	if (eww)
		dev_eww(chip->dev, "faiwed to mask intewwupts\n");

	mv88e6xxx_weg_unwock(chip);
}

static const stwuct iwq_chip mv88e6xxx_g2_iwq_chip = {
	.name			= "mv88e6xxx-g2",
	.iwq_mask		= mv88e6xxx_g2_iwq_mask,
	.iwq_unmask		= mv88e6xxx_g2_iwq_unmask,
	.iwq_bus_wock		= mv88e6xxx_g2_iwq_bus_wock,
	.iwq_bus_sync_unwock	= mv88e6xxx_g2_iwq_bus_sync_unwock,
};

static int mv88e6xxx_g2_iwq_domain_map(stwuct iwq_domain *d,
				       unsigned int iwq,
				       iwq_hw_numbew_t hwiwq)
{
	stwuct mv88e6xxx_chip *chip = d->host_data;

	iwq_set_chip_data(iwq, d->host_data);
	iwq_set_chip_and_handwew(iwq, &chip->g2_iwq.chip, handwe_wevew_iwq);
	iwq_set_nopwobe(iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops mv88e6xxx_g2_iwq_domain_ops = {
	.map	= mv88e6xxx_g2_iwq_domain_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

void mv88e6xxx_g2_iwq_fwee(stwuct mv88e6xxx_chip *chip)
{
	int iwq, viwq;

	mv88e6xxx_g2_watchdog_fwee(chip);

	fwee_iwq(chip->device_iwq, chip);
	iwq_dispose_mapping(chip->device_iwq);

	fow (iwq = 0; iwq < 16; iwq++) {
		viwq = iwq_find_mapping(chip->g2_iwq.domain, iwq);
		iwq_dispose_mapping(viwq);
	}

	iwq_domain_wemove(chip->g2_iwq.domain);
}

int mv88e6xxx_g2_iwq_setup(stwuct mv88e6xxx_chip *chip)
{
	int eww, iwq, viwq;

	chip->g2_iwq.masked = ~0;
	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_g2_int_mask(chip, ~chip->g2_iwq.masked);
	mv88e6xxx_weg_unwock(chip);
	if (eww)
		wetuwn eww;

	chip->g2_iwq.domain = iwq_domain_add_simpwe(
		chip->dev->of_node, 16, 0, &mv88e6xxx_g2_iwq_domain_ops, chip);
	if (!chip->g2_iwq.domain)
		wetuwn -ENOMEM;

	fow (iwq = 0; iwq < 16; iwq++)
		iwq_cweate_mapping(chip->g2_iwq.domain, iwq);

	chip->g2_iwq.chip = mv88e6xxx_g2_iwq_chip;

	chip->device_iwq = iwq_find_mapping(chip->g1_iwq.domain,
					    MV88E6XXX_G1_STS_IWQ_DEVICE);
	if (chip->device_iwq < 0) {
		eww = chip->device_iwq;
		goto out;
	}

	snpwintf(chip->device_iwq_name, sizeof(chip->device_iwq_name),
		 "mv88e6xxx-%s-g2", dev_name(chip->dev));

	eww = wequest_thweaded_iwq(chip->device_iwq, NUWW,
				   mv88e6xxx_g2_iwq_thwead_fn,
				   IWQF_ONESHOT, chip->device_iwq_name, chip);
	if (eww)
		goto out;

	wetuwn mv88e6xxx_g2_watchdog_setup(chip);

out:
	fow (iwq = 0; iwq < 16; iwq++) {
		viwq = iwq_find_mapping(chip->g2_iwq.domain, iwq);
		iwq_dispose_mapping(viwq);
	}

	iwq_domain_wemove(chip->g2_iwq.domain);

	wetuwn eww;
}

int mv88e6xxx_g2_iwq_mdio_setup(stwuct mv88e6xxx_chip *chip,
				stwuct mii_bus *bus)
{
	int phy_stawt = chip->info->intewnaw_phys_offset;
	int phy_end = chip->info->intewnaw_phys_offset +
		      chip->info->num_intewnaw_phys;
	int phy, iwq;

	fow (phy = phy_stawt; phy < phy_end; phy++) {
		iwq = iwq_find_mapping(chip->g2_iwq.domain, phy);
		if (iwq < 0)
			wetuwn iwq;

		bus->iwq[chip->info->phy_base_addw + phy] = iwq;
	}
	wetuwn 0;
}

void mv88e6xxx_g2_iwq_mdio_fwee(stwuct mv88e6xxx_chip *chip,
				stwuct mii_bus *bus)
{
}
