// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww 88E6xxx Switch Hidden Wegistews suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2019 Andwew Wunn <andwew@wunn.ch>
 */

#incwude <winux/bitfiewd.h>

#incwude "chip.h"
#incwude "powt.h"

/* The mv88e6390 and mv88e6341 have some hidden wegistews used fow debug and
 * devewopment. The ewwata awso makes use of them.
 */
int mv88e6xxx_powt_hidden_wwite(stwuct mv88e6xxx_chip *chip, int bwock,
				int powt, int weg, u16 vaw)
{
	u16 ctww;
	int eww;

	eww = mv88e6xxx_powt_wwite(chip, MV88E6XXX_POWT_WESEWVED_1A_DATA_POWT,
				   MV88E6XXX_POWT_WESEWVED_1A, vaw);
	if (eww)
		wetuwn eww;

	ctww = MV88E6XXX_POWT_WESEWVED_1A_BUSY |
	       MV88E6XXX_POWT_WESEWVED_1A_WWITE |
	       bwock << MV88E6XXX_POWT_WESEWVED_1A_BWOCK_SHIFT |
	       powt << MV88E6XXX_POWT_WESEWVED_1A_POWT_SHIFT |
	       weg;

	wetuwn mv88e6xxx_powt_wwite(chip, MV88E6XXX_POWT_WESEWVED_1A_CTWW_POWT,
				    MV88E6XXX_POWT_WESEWVED_1A, ctww);
}

int mv88e6xxx_powt_hidden_wait(stwuct mv88e6xxx_chip *chip)
{
	int bit = __bf_shf(MV88E6XXX_POWT_WESEWVED_1A_BUSY);

	wetuwn mv88e6xxx_powt_wait_bit(chip,
				       MV88E6XXX_POWT_WESEWVED_1A_CTWW_POWT,
				       MV88E6XXX_POWT_WESEWVED_1A, bit, 0);
}

int mv88e6xxx_powt_hidden_wead(stwuct mv88e6xxx_chip *chip, int bwock, int powt,
			       int weg, u16 *vaw)
{
	u16 ctww;
	int eww;

	ctww = MV88E6XXX_POWT_WESEWVED_1A_BUSY |
	       MV88E6XXX_POWT_WESEWVED_1A_WEAD |
	       bwock << MV88E6XXX_POWT_WESEWVED_1A_BWOCK_SHIFT |
	       powt << MV88E6XXX_POWT_WESEWVED_1A_POWT_SHIFT |
	       weg;

	eww = mv88e6xxx_powt_wwite(chip, MV88E6XXX_POWT_WESEWVED_1A_CTWW_POWT,
				   MV88E6XXX_POWT_WESEWVED_1A, ctww);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_powt_hidden_wait(chip);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_powt_wead(chip, MV88E6XXX_POWT_WESEWVED_1A_DATA_POWT,
				   MV88E6XXX_POWT_WESEWVED_1A, vaw);
}
