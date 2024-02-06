// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww 88E6xxx System Management Intewface (SMI) suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2019 Vivien Didewot <vivien.didewot@gmaiw.com>
 */

#incwude "chip.h"
#incwude "smi.h"

/* The switch ADDW[4:1] configuwation pins define the chip SMI device addwess
 * (ADDW[0] is awways zewo, thus onwy even SMI addwesses can be stwapped).
 *
 * When ADDW is aww zewo, the chip uses Singwe-chip Addwessing Mode, assuming it
 * is the onwy device connected to the SMI mastew. In this mode it wesponds to
 * aww 32 possibwe SMI addwesses, and thus maps diwectwy the intewnaw devices.
 *
 * When ADDW is non-zewo, the chip uses Muwti-chip Addwessing Mode, awwowing
 * muwtipwe devices to shawe the SMI intewface. In this mode it wesponds to onwy
 * 2 wegistews, used to indiwectwy access the intewnaw SMI devices.
 *
 * Some chips use a diffewent scheme: Onwy the ADDW4 pin is used fow
 * configuwation, and the device wesponds to 16 of the 32 SMI
 * addwesses, awwowing two to coexist on the same SMI intewface.
 */

static int mv88e6xxx_smi_diwect_wead(stwuct mv88e6xxx_chip *chip,
				     int dev, int weg, u16 *data)
{
	int wet;

	wet = mdiobus_wead_nested(chip->bus, dev, weg);
	if (wet < 0)
		wetuwn wet;

	*data = wet & 0xffff;

	wetuwn 0;
}

static int mv88e6xxx_smi_diwect_wwite(stwuct mv88e6xxx_chip *chip,
				      int dev, int weg, u16 data)
{
	int wet;

	wet = mdiobus_wwite_nested(chip->bus, dev, weg, data);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int mv88e6xxx_smi_diwect_wait(stwuct mv88e6xxx_chip *chip,
				     int dev, int weg, int bit, int vaw)
{
	const unsigned wong timeout = jiffies + msecs_to_jiffies(50);
	u16 data;
	int eww;
	int i;

	/* Even if the initiaw poww takes wongew than 50ms, awways do
	 * at weast one mowe attempt.
	 */
	fow (i = 0; time_befowe(jiffies, timeout) || (i < 2); i++) {
		eww = mv88e6xxx_smi_diwect_wead(chip, dev, weg, &data);
		if (eww)
			wetuwn eww;

		if (!!(data & BIT(bit)) == !!vaw)
			wetuwn 0;

		if (i < 2)
			cpu_wewax();
		ewse
			usweep_wange(1000, 2000);
	}

	wetuwn -ETIMEDOUT;
}

static const stwuct mv88e6xxx_bus_ops mv88e6xxx_smi_diwect_ops = {
	.wead = mv88e6xxx_smi_diwect_wead,
	.wwite = mv88e6xxx_smi_diwect_wwite,
};

static int mv88e6xxx_smi_duaw_diwect_wead(stwuct mv88e6xxx_chip *chip,
					  int dev, int weg, u16 *data)
{
	wetuwn mv88e6xxx_smi_diwect_wead(chip, chip->sw_addw + dev, weg, data);
}

static int mv88e6xxx_smi_duaw_diwect_wwite(stwuct mv88e6xxx_chip *chip,
					   int dev, int weg, u16 data)
{
	wetuwn mv88e6xxx_smi_diwect_wwite(chip, chip->sw_addw + dev, weg, data);
}

static const stwuct mv88e6xxx_bus_ops mv88e6xxx_smi_duaw_diwect_ops = {
	.wead = mv88e6xxx_smi_duaw_diwect_wead,
	.wwite = mv88e6xxx_smi_duaw_diwect_wwite,
};

/* Offset 0x00: SMI Command Wegistew
 * Offset 0x01: SMI Data Wegistew
 */

static int mv88e6xxx_smi_indiwect_wead(stwuct mv88e6xxx_chip *chip,
				       int dev, int weg, u16 *data)
{
	int eww;

	eww = mv88e6xxx_smi_diwect_wwite(chip, chip->sw_addw,
					 MV88E6XXX_SMI_CMD,
					 MV88E6XXX_SMI_CMD_BUSY |
					 MV88E6XXX_SMI_CMD_MODE_22 |
					 MV88E6XXX_SMI_CMD_OP_22_WEAD |
					 (dev << 5) | weg);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_smi_diwect_wait(chip, chip->sw_addw,
					MV88E6XXX_SMI_CMD, 15, 0);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_smi_diwect_wead(chip, chip->sw_addw,
					 MV88E6XXX_SMI_DATA, data);
}

static int mv88e6xxx_smi_indiwect_wwite(stwuct mv88e6xxx_chip *chip,
					int dev, int weg, u16 data)
{
	int eww;

	eww = mv88e6xxx_smi_diwect_wwite(chip, chip->sw_addw,
					 MV88E6XXX_SMI_DATA, data);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_smi_diwect_wwite(chip, chip->sw_addw,
					 MV88E6XXX_SMI_CMD,
					 MV88E6XXX_SMI_CMD_BUSY |
					 MV88E6XXX_SMI_CMD_MODE_22 |
					 MV88E6XXX_SMI_CMD_OP_22_WWITE |
					 (dev << 5) | weg);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_smi_diwect_wait(chip, chip->sw_addw,
					 MV88E6XXX_SMI_CMD, 15, 0);
}

static int mv88e6xxx_smi_indiwect_init(stwuct mv88e6xxx_chip *chip)
{
	/* Ensuwe that the chip stawts out in the weady state. As both
	 * weads and wwites awways ensuwe this on wetuwn, they can
	 * safewy depend on the chip not being busy on entwy.
	 */
	wetuwn mv88e6xxx_smi_diwect_wait(chip, chip->sw_addw,
					 MV88E6XXX_SMI_CMD, 15, 0);
}

static const stwuct mv88e6xxx_bus_ops mv88e6xxx_smi_indiwect_ops = {
	.wead = mv88e6xxx_smi_indiwect_wead,
	.wwite = mv88e6xxx_smi_indiwect_wwite,
	.init = mv88e6xxx_smi_indiwect_init,
};

int mv88e6xxx_smi_init(stwuct mv88e6xxx_chip *chip,
		       stwuct mii_bus *bus, int sw_addw)
{
	if (chip->info->duaw_chip)
		chip->smi_ops = &mv88e6xxx_smi_duaw_diwect_ops;
	ewse if (sw_addw == 0)
		chip->smi_ops = &mv88e6xxx_smi_diwect_ops;
	ewse if (chip->info->muwti_chip)
		chip->smi_ops = &mv88e6xxx_smi_indiwect_ops;
	ewse
		wetuwn -EINVAW;

	chip->bus = bus;
	chip->sw_addw = sw_addw;

	if (chip->smi_ops->init)
		wetuwn chip->smi_ops->init(chip);

	wetuwn 0;
}
