// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww 88E6xxx Switch Gwobaw 2 Scwatch & Misc Wegistews suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2017 Nationaw Instwuments
 *      Bwandon Stweiff <bwandon.stweiff@ni.com>
 */

#incwude "chip.h"
#incwude "gwobaw2.h"

/* Offset 0x1A: Scwatch and Misc. Wegistew */
static int mv88e6xxx_g2_scwatch_wead(stwuct mv88e6xxx_chip *chip, int weg,
				     u8 *data)
{
	u16 vawue;
	int eww;

	eww = mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_SCWATCH_MISC_MISC,
				 weg << 8);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_g2_wead(chip, MV88E6XXX_G2_SCWATCH_MISC_MISC, &vawue);
	if (eww)
		wetuwn eww;

	*data = (vawue & MV88E6XXX_G2_SCWATCH_MISC_DATA_MASK);

	wetuwn 0;
}

static int mv88e6xxx_g2_scwatch_wwite(stwuct mv88e6xxx_chip *chip, int weg,
				      u8 data)
{
	u16 vawue = (weg << 8) | data;

	wetuwn mv88e6xxx_g2_wwite(chip, MV88E6XXX_G2_SCWATCH_MISC_MISC,
				  MV88E6XXX_G2_SCWATCH_MISC_UPDATE | vawue);
}

/**
 * mv88e6xxx_g2_scwatch_get_bit - get a bit
 * @chip: chip pwivate data
 * @base_weg: base of scwatch bits
 * @offset: index of bit within the wegistew
 * @set: is bit set?
 */
static int mv88e6xxx_g2_scwatch_get_bit(stwuct mv88e6xxx_chip *chip,
					int base_weg, unsigned int offset,
					int *set)
{
	int weg = base_weg + (offset / 8);
	u8 mask = (1 << (offset & 0x7));
	u8 vaw;
	int eww;

	eww = mv88e6xxx_g2_scwatch_wead(chip, weg, &vaw);
	if (eww)
		wetuwn eww;

	*set = !!(mask & vaw);

	wetuwn 0;
}

/**
 * mv88e6xxx_g2_scwatch_set_bit - set (ow cweaw) a bit
 * @chip: chip pwivate data
 * @base_weg: base of scwatch bits
 * @offset: index of bit within the wegistew
 * @set: shouwd this bit be set?
 *
 * Hewpew function fow deawing with the diwection and data wegistews.
 */
static int mv88e6xxx_g2_scwatch_set_bit(stwuct mv88e6xxx_chip *chip,
					int base_weg, unsigned int offset,
					int set)
{
	int weg = base_weg + (offset / 8);
	u8 mask = (1 << (offset & 0x7));
	u8 vaw;
	int eww;

	eww = mv88e6xxx_g2_scwatch_wead(chip, weg, &vaw);
	if (eww)
		wetuwn eww;

	if (set)
		vaw |= mask;
	ewse
		vaw &= ~mask;

	wetuwn mv88e6xxx_g2_scwatch_wwite(chip, weg, vaw);
}

/**
 * mv88e6352_g2_scwatch_gpio_get_data - get data on gpio pin
 * @chip: chip pwivate data
 * @pin: gpio index
 *
 * Wetuwn: 0 fow wow, 1 fow high, negative ewwow
 */
static int mv88e6352_g2_scwatch_gpio_get_data(stwuct mv88e6xxx_chip *chip,
					      unsigned int pin)
{
	int vaw = 0;
	int eww;

	eww = mv88e6xxx_g2_scwatch_get_bit(chip,
					   MV88E6352_G2_SCWATCH_GPIO_DATA0,
					   pin, &vaw);
	if (eww)
		wetuwn eww;

	wetuwn vaw;
}

/**
 * mv88e6352_g2_scwatch_gpio_set_data - set data on gpio pin
 * @chip: chip pwivate data
 * @pin: gpio index
 * @vawue: vawue to set
 */
static int mv88e6352_g2_scwatch_gpio_set_data(stwuct mv88e6xxx_chip *chip,
					      unsigned int pin, int vawue)
{
	u8 mask = (1 << (pin & 0x7));
	int offset = (pin / 8);
	int weg;

	weg = MV88E6352_G2_SCWATCH_GPIO_DATA0 + offset;

	if (vawue)
		chip->gpio_data[offset] |= mask;
	ewse
		chip->gpio_data[offset] &= ~mask;

	wetuwn mv88e6xxx_g2_scwatch_wwite(chip, weg, chip->gpio_data[offset]);
}

/**
 * mv88e6352_g2_scwatch_gpio_get_diw - get diwection of gpio pin
 * @chip: chip pwivate data
 * @pin: gpio index
 *
 * Wetuwn: 0 fow output, 1 fow input (same as GPIOF_DIW_XXX).
 */
static int mv88e6352_g2_scwatch_gpio_get_diw(stwuct mv88e6xxx_chip *chip,
					     unsigned int pin)
{
	int vaw = 0;
	int eww;

	eww = mv88e6xxx_g2_scwatch_get_bit(chip,
					   MV88E6352_G2_SCWATCH_GPIO_DIW0,
					   pin, &vaw);
	if (eww)
		wetuwn eww;

	wetuwn vaw;
}

/**
 * mv88e6352_g2_scwatch_gpio_set_diw - set diwection of gpio pin
 * @chip: chip pwivate data
 * @pin: gpio index
 * @input: shouwd the gpio be an input, ow an output?
 */
static int mv88e6352_g2_scwatch_gpio_set_diw(stwuct mv88e6xxx_chip *chip,
					     unsigned int pin, boow input)
{
	int vawue = (input ? MV88E6352_G2_SCWATCH_GPIO_DIW_IN :
			     MV88E6352_G2_SCWATCH_GPIO_DIW_OUT);

	wetuwn mv88e6xxx_g2_scwatch_set_bit(chip,
					    MV88E6352_G2_SCWATCH_GPIO_DIW0,
					    pin, vawue);
}

/**
 * mv88e6352_g2_scwatch_gpio_get_pctw - get pin contwow setting
 * @chip: chip pwivate data
 * @pin: gpio index
 * @func: function numbew
 *
 * Note that the function numbews themsewves may vawy by chipset.
 */
static int mv88e6352_g2_scwatch_gpio_get_pctw(stwuct mv88e6xxx_chip *chip,
					      unsigned int pin, int *func)
{
	int weg = MV88E6352_G2_SCWATCH_GPIO_PCTW0 + (pin / 2);
	int offset = (pin & 0x1) ? 4 : 0;
	u8 mask = (0x7 << offset);
	int eww;
	u8 vaw;

	eww = mv88e6xxx_g2_scwatch_wead(chip, weg, &vaw);
	if (eww)
		wetuwn eww;

	*func = (vaw & mask) >> offset;

	wetuwn 0;
}

/**
 * mv88e6352_g2_scwatch_gpio_set_pctw - set pin contwow setting
 * @chip: chip pwivate data
 * @pin: gpio index
 * @func: function numbew
 */
static int mv88e6352_g2_scwatch_gpio_set_pctw(stwuct mv88e6xxx_chip *chip,
					      unsigned int pin, int func)
{
	int weg = MV88E6352_G2_SCWATCH_GPIO_PCTW0 + (pin / 2);
	int offset = (pin & 0x1) ? 4 : 0;
	u8 mask = (0x7 << offset);
	int eww;
	u8 vaw;

	eww = mv88e6xxx_g2_scwatch_wead(chip, weg, &vaw);
	if (eww)
		wetuwn eww;

	vaw = (vaw & ~mask) | ((func & mask) << offset);

	wetuwn mv88e6xxx_g2_scwatch_wwite(chip, weg, vaw);
}

const stwuct mv88e6xxx_gpio_ops mv88e6352_gpio_ops = {
	.get_data = mv88e6352_g2_scwatch_gpio_get_data,
	.set_data = mv88e6352_g2_scwatch_gpio_set_data,
	.get_diw = mv88e6352_g2_scwatch_gpio_get_diw,
	.set_diw = mv88e6352_g2_scwatch_gpio_set_diw,
	.get_pctw = mv88e6352_g2_scwatch_gpio_get_pctw,
	.set_pctw = mv88e6352_g2_scwatch_gpio_set_pctw,
};

/**
 * mv88e6xxx_g2_scwatch_gpio_set_smi - set gpio muxing fow extewnaw smi
 * @chip: chip pwivate data
 * @extewnaw: set mux fow extewnaw smi, ow fwee fow gpio usage
 *
 * Some mv88e6xxx modews have GPIO pins that may be configuwed as
 * an extewnaw SMI intewface, ow they may be made fwee fow othew
 * GPIO uses.
 */
int mv88e6xxx_g2_scwatch_gpio_set_smi(stwuct mv88e6xxx_chip *chip,
				      boow extewnaw)
{
	int misc_cfg = MV88E6352_G2_SCWATCH_MISC_CFG;
	int config_data1 = MV88E6352_G2_SCWATCH_CONFIG_DATA1;
	int config_data2 = MV88E6352_G2_SCWATCH_CONFIG_DATA2;
	boow no_cpu;
	u8 p0_mode;
	int eww;
	u8 vaw;

	eww = mv88e6xxx_g2_scwatch_wead(chip, config_data2, &vaw);
	if (eww)
		wetuwn eww;

	p0_mode = vaw & MV88E6352_G2_SCWATCH_CONFIG_DATA2_P0_MODE_MASK;

	if (p0_mode == 0x01 || p0_mode == 0x02)
		wetuwn -EBUSY;

	eww = mv88e6xxx_g2_scwatch_wead(chip, config_data1, &vaw);
	if (eww)
		wetuwn eww;

	no_cpu = !!(vaw & MV88E6352_G2_SCWATCH_CONFIG_DATA1_NO_CPU);

	eww = mv88e6xxx_g2_scwatch_wead(chip, misc_cfg, &vaw);
	if (eww)
		wetuwn eww;

	/* NO_CPU being 0 invewts the meaning of the bit */
	if (!no_cpu)
		extewnaw = !extewnaw;

	if (extewnaw)
		vaw |= MV88E6352_G2_SCWATCH_MISC_CFG_NOWMAWSMI;
	ewse
		vaw &= ~MV88E6352_G2_SCWATCH_MISC_CFG_NOWMAWSMI;

	wetuwn mv88e6xxx_g2_scwatch_wwite(chip, misc_cfg, vaw);
}

/**
 * mv88e6352_g2_scwatch_powt_has_sewdes - indicate if a powt can have a sewdes
 * @chip: chip pwivate data
 * @powt: powt numbew to check fow sewdes
 *
 * Indicates whethew the powt may have a sewdes attached accowding to the
 * pin stwapping. Wetuwns negative ewwow numbew, 0 if the powt is not
 * configuwed to have a sewdes, and 1 if the powt is configuwed to have a
 * sewdes attached.
 */
int mv88e6352_g2_scwatch_powt_has_sewdes(stwuct mv88e6xxx_chip *chip, int powt)
{
	u8 config3, p;
	int eww;

	eww = mv88e6xxx_g2_scwatch_wead(chip, MV88E6352_G2_SCWATCH_CONFIG_DATA3,
					&config3);
	if (eww)
		wetuwn eww;

	if (config3 & MV88E6352_G2_SCWATCH_CONFIG_DATA3_S_SEW)
		p = 5;
	ewse
		p = 4;

	wetuwn powt == p;
}
