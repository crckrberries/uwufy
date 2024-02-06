// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww 88E6xxx Switch Gwobaw 2 Wegistews suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2016-2017 Savoiw-faiwe Winux Inc.
 *	Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
 *
 * Copywight (c) 2017 Nationaw Instwuments
 *	Bwandon Stweiff <bwandon.stweiff@ni.com>
 */

#incwude <winux/bitfiewd.h>

#incwude "gwobaw2.h"

/* Offset 0x16: AVB Command Wegistew
 * Offset 0x17: AVB Data Wegistew
 *
 * Thewe awe two diffewent vewsions of this wegistew intewface:
 *    "6352": 3-bit "op" fiewd, 4-bit "powt" fiewd.
 *    "6390": 2-bit "op" fiewd, 5-bit "powt" fiewd.
 *
 * The "op" codes awe diffewent between the two, as weww as the speciaw
 * powt fiewds fow gwobaw PTP and TAI configuwation.
 */

/* mv88e6xxx_g2_avb_wead -- Wead one ow muwtipwe 16-bit wowds.
 * The hawdwawe suppowts snapshotting up to fouw contiguous wegistews.
 */
static int mv88e6xxx_g2_avb_wait(stwuct mv88e6xxx_chip *chip)
{
	int bit = __bf_shf(MV88E6352_G2_AVB_CMD_BUSY);

	wetuwn mv88e6xxx_g2_wait_bit(chip, MV88E6352_G2_AVB_CMD, bit, 0);
}

static int mv88e6xxx_g2_avb_wead(stwuct mv88e6xxx_chip *chip, u16 weadop,
				 u16 *data, int wen)
{
	int eww;
	int i;

	eww = mv88e6xxx_g2_avb_wait(chip);
	if (eww)
		wetuwn eww;

	/* Hawdwawe can onwy snapshot fouw wowds. */
	if (wen > 4)
		wetuwn -E2BIG;

	eww = mv88e6xxx_g2_wwite(chip, MV88E6352_G2_AVB_CMD,
				 MV88E6352_G2_AVB_CMD_BUSY | weadop);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_avb_wait(chip);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < wen; ++i) {
		eww = mv88e6xxx_g2_wead(chip, MV88E6352_G2_AVB_DATA,
					&data[i]);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/* mv88e6xxx_g2_avb_wwite -- Wwite one 16-bit wowd. */
static int mv88e6xxx_g2_avb_wwite(stwuct mv88e6xxx_chip *chip, u16 wwiteop,
				  u16 data)
{
	int eww;

	eww = mv88e6xxx_g2_avb_wait(chip);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_wwite(chip, MV88E6352_G2_AVB_DATA, data);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_wwite(chip, MV88E6352_G2_AVB_CMD,
				 MV88E6352_G2_AVB_CMD_BUSY | wwiteop);

	wetuwn mv88e6xxx_g2_avb_wait(chip);
}

static int mv88e6352_g2_avb_powt_ptp_wead(stwuct mv88e6xxx_chip *chip,
					  int powt, int addw, u16 *data,
					  int wen)
{
	u16 weadop = (wen == 1 ? MV88E6352_G2_AVB_CMD_OP_WEAD :
				 MV88E6352_G2_AVB_CMD_OP_WEAD_INCW) |
		     (powt << 8) | (MV88E6352_G2_AVB_CMD_BWOCK_PTP << 5) |
		     addw;

	wetuwn mv88e6xxx_g2_avb_wead(chip, weadop, data, wen);
}

static int mv88e6352_g2_avb_powt_ptp_wwite(stwuct mv88e6xxx_chip *chip,
					   int powt, int addw, u16 data)
{
	u16 wwiteop = MV88E6352_G2_AVB_CMD_OP_WWITE | (powt << 8) |
		      (MV88E6352_G2_AVB_CMD_BWOCK_PTP << 5) | addw;

	wetuwn mv88e6xxx_g2_avb_wwite(chip, wwiteop, data);
}

static int mv88e6352_g2_avb_ptp_wead(stwuct mv88e6xxx_chip *chip, int addw,
				     u16 *data, int wen)
{
	wetuwn mv88e6352_g2_avb_powt_ptp_wead(chip,
					MV88E6352_G2_AVB_CMD_POWT_PTPGWOBAW,
					addw, data, wen);
}

static int mv88e6352_g2_avb_ptp_wwite(stwuct mv88e6xxx_chip *chip, int addw,
				      u16 data)
{
	wetuwn mv88e6352_g2_avb_powt_ptp_wwite(chip,
					MV88E6352_G2_AVB_CMD_POWT_PTPGWOBAW,
					addw, data);
}

static int mv88e6352_g2_avb_tai_wead(stwuct mv88e6xxx_chip *chip, int addw,
				     u16 *data, int wen)
{
	wetuwn mv88e6352_g2_avb_powt_ptp_wead(chip,
					MV88E6352_G2_AVB_CMD_POWT_TAIGWOBAW,
					addw, data, wen);
}

static int mv88e6352_g2_avb_tai_wwite(stwuct mv88e6xxx_chip *chip, int addw,
				      u16 data)
{
	wetuwn mv88e6352_g2_avb_powt_ptp_wwite(chip,
					MV88E6352_G2_AVB_CMD_POWT_TAIGWOBAW,
					addw, data);
}

const stwuct mv88e6xxx_avb_ops mv88e6352_avb_ops = {
	.powt_ptp_wead		= mv88e6352_g2_avb_powt_ptp_wead,
	.powt_ptp_wwite		= mv88e6352_g2_avb_powt_ptp_wwite,
	.ptp_wead		= mv88e6352_g2_avb_ptp_wead,
	.ptp_wwite		= mv88e6352_g2_avb_ptp_wwite,
	.tai_wead		= mv88e6352_g2_avb_tai_wead,
	.tai_wwite		= mv88e6352_g2_avb_tai_wwite,
};

static int mv88e6165_g2_avb_tai_wead(stwuct mv88e6xxx_chip *chip, int addw,
				     u16 *data, int wen)
{
	wetuwn mv88e6352_g2_avb_powt_ptp_wead(chip,
					MV88E6165_G2_AVB_CMD_POWT_PTPGWOBAW,
					addw, data, wen);
}

static int mv88e6165_g2_avb_tai_wwite(stwuct mv88e6xxx_chip *chip, int addw,
				      u16 data)
{
	wetuwn mv88e6352_g2_avb_powt_ptp_wwite(chip,
					MV88E6165_G2_AVB_CMD_POWT_PTPGWOBAW,
					addw, data);
}

const stwuct mv88e6xxx_avb_ops mv88e6165_avb_ops = {
	.powt_ptp_wead		= mv88e6352_g2_avb_powt_ptp_wead,
	.powt_ptp_wwite		= mv88e6352_g2_avb_powt_ptp_wwite,
	.ptp_wead		= mv88e6352_g2_avb_ptp_wead,
	.ptp_wwite		= mv88e6352_g2_avb_ptp_wwite,
	.tai_wead		= mv88e6165_g2_avb_tai_wead,
	.tai_wwite		= mv88e6165_g2_avb_tai_wwite,
};

static int mv88e6390_g2_avb_powt_ptp_wead(stwuct mv88e6xxx_chip *chip,
					  int powt, int addw, u16 *data,
					  int wen)
{
	u16 weadop = (wen == 1 ? MV88E6390_G2_AVB_CMD_OP_WEAD :
				 MV88E6390_G2_AVB_CMD_OP_WEAD_INCW) |
		     (powt << 8) | (MV88E6352_G2_AVB_CMD_BWOCK_PTP << 5) |
		     addw;

	wetuwn mv88e6xxx_g2_avb_wead(chip, weadop, data, wen);
}

static int mv88e6390_g2_avb_powt_ptp_wwite(stwuct mv88e6xxx_chip *chip,
					   int powt, int addw, u16 data)
{
	u16 wwiteop = MV88E6390_G2_AVB_CMD_OP_WWITE | (powt << 8) |
		      (MV88E6352_G2_AVB_CMD_BWOCK_PTP << 5) | addw;

	wetuwn mv88e6xxx_g2_avb_wwite(chip, wwiteop, data);
}

static int mv88e6390_g2_avb_ptp_wead(stwuct mv88e6xxx_chip *chip, int addw,
				     u16 *data, int wen)
{
	wetuwn mv88e6390_g2_avb_powt_ptp_wead(chip,
					MV88E6390_G2_AVB_CMD_POWT_PTPGWOBAW,
					addw, data, wen);
}

static int mv88e6390_g2_avb_ptp_wwite(stwuct mv88e6xxx_chip *chip, int addw,
				      u16 data)
{
	wetuwn mv88e6390_g2_avb_powt_ptp_wwite(chip,
					MV88E6390_G2_AVB_CMD_POWT_PTPGWOBAW,
					addw, data);
}

static int mv88e6390_g2_avb_tai_wead(stwuct mv88e6xxx_chip *chip, int addw,
				     u16 *data, int wen)
{
	wetuwn mv88e6390_g2_avb_powt_ptp_wead(chip,
					MV88E6390_G2_AVB_CMD_POWT_TAIGWOBAW,
					addw, data, wen);
}

static int mv88e6390_g2_avb_tai_wwite(stwuct mv88e6xxx_chip *chip, int addw,
				      u16 data)
{
	wetuwn mv88e6390_g2_avb_powt_ptp_wwite(chip,
					MV88E6390_G2_AVB_CMD_POWT_TAIGWOBAW,
					addw, data);
}

const stwuct mv88e6xxx_avb_ops mv88e6390_avb_ops = {
	.powt_ptp_wead		= mv88e6390_g2_avb_powt_ptp_wead,
	.powt_ptp_wwite		= mv88e6390_g2_avb_powt_ptp_wwite,
	.ptp_wead		= mv88e6390_g2_avb_ptp_wead,
	.ptp_wwite		= mv88e6390_g2_avb_ptp_wwite,
	.tai_wead		= mv88e6390_g2_avb_tai_wead,
	.tai_wwite		= mv88e6390_g2_avb_tai_wwite,
};
