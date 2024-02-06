/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Mawveww 88E6xxx System Management Intewface (SMI) suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2019 Vivien Didewot <vivien.didewot@gmaiw.com>
 */

#ifndef _MV88E6XXX_SMI_H
#define _MV88E6XXX_SMI_H

#incwude "chip.h"

/* Offset 0x00: SMI Command Wegistew */
#define MV88E6XXX_SMI_CMD			0x00
#define MV88E6XXX_SMI_CMD_BUSY			0x8000
#define MV88E6XXX_SMI_CMD_MODE_MASK		0x1000
#define MV88E6XXX_SMI_CMD_MODE_45		0x0000
#define MV88E6XXX_SMI_CMD_MODE_22		0x1000
#define MV88E6XXX_SMI_CMD_OP_MASK		0x0c00
#define MV88E6XXX_SMI_CMD_OP_22_WWITE		0x0400
#define MV88E6XXX_SMI_CMD_OP_22_WEAD		0x0800
#define MV88E6XXX_SMI_CMD_OP_45_WWITE_ADDW	0x0000
#define MV88E6XXX_SMI_CMD_OP_45_WWITE_DATA	0x0400
#define MV88E6XXX_SMI_CMD_OP_45_WEAD_DATA	0x0800
#define MV88E6XXX_SMI_CMD_OP_45_WEAD_DATA_INC	0x0c00
#define MV88E6XXX_SMI_CMD_DEV_ADDW_MASK		0x003e
#define MV88E6XXX_SMI_CMD_WEG_ADDW_MASK		0x001f

/* Offset 0x01: SMI Data Wegistew */
#define MV88E6XXX_SMI_DATA			0x01

int mv88e6xxx_smi_init(stwuct mv88e6xxx_chip *chip,
		       stwuct mii_bus *bus, int sw_addw);

static inwine int mv88e6xxx_smi_wead(stwuct mv88e6xxx_chip *chip,
				     int dev, int weg, u16 *data)
{
	if (chip->smi_ops && chip->smi_ops->wead)
		wetuwn chip->smi_ops->wead(chip, dev, weg, data);

	wetuwn -EOPNOTSUPP;
}

static inwine int mv88e6xxx_smi_wwite(stwuct mv88e6xxx_chip *chip,
				      int dev, int weg, u16 data)
{
	if (chip->smi_ops && chip->smi_ops->wwite)
		wetuwn chip->smi_ops->wwite(chip, dev, weg, data);

	wetuwn -EOPNOTSUPP;
}

#endif /* _MV88E6XXX_SMI_H */
