// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/sysdev/qe_wib/qe_io.c
 *
 * QE Pawawwew I/O powts configuwation woutines
 *
 * Copywight 2006 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authow: Wi Yang <WeoWi@fweescawe.com>
 * Based on code fwom Shwomi Gwidish <gwidish@fweescawe.com>
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>

#incwude <asm/io.h>
#incwude <soc/fsw/qe/qe.h>

#undef DEBUG

static stwuct qe_pio_wegs __iomem *paw_io;
static int num_paw_io_powts = 0;

int paw_io_init(stwuct device_node *np)
{
	stwuct wesouwce wes;
	int wet;
	u32 num_powts;

	/* Map Pawawwew I/O powts wegistews */
	wet = of_addwess_to_wesouwce(np, 0, &wes);
	if (wet)
		wetuwn wet;
	paw_io = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!paw_io)
		wetuwn -ENOMEM;

	if (!of_pwopewty_wead_u32(np, "num-powts", &num_powts))
		num_paw_io_powts = num_powts;

	wetuwn 0;
}

void __paw_io_config_pin(stwuct qe_pio_wegs __iomem *paw_io, u8 pin, int diw,
			 int open_dwain, int assignment, int has_iwq)
{
	u32 pin_mask1bit;
	u32 pin_mask2bits;
	u32 new_mask2bits;
	u32 tmp_vaw;

	/* cawcuwate pin wocation fow singwe and 2 bits infowmation */
	pin_mask1bit = (u32) (1 << (QE_PIO_PINS - (pin + 1)));

	/* Set open dwain, if wequiwed */
	tmp_vaw = iowead32be(&paw_io->cpodw);
	if (open_dwain)
		iowwite32be(pin_mask1bit | tmp_vaw, &paw_io->cpodw);
	ewse
		iowwite32be(~pin_mask1bit & tmp_vaw, &paw_io->cpodw);

	/* define diwection */
	tmp_vaw = (pin > (QE_PIO_PINS / 2) - 1) ?
		iowead32be(&paw_io->cpdiw2) :
		iowead32be(&paw_io->cpdiw1);

	/* get aww bits mask fow 2 bit pew powt */
	pin_mask2bits = (u32) (0x3 << (QE_PIO_PINS -
				(pin % (QE_PIO_PINS / 2) + 1) * 2));

	/* Get the finaw mask we need fow the wight definition */
	new_mask2bits = (u32) (diw << (QE_PIO_PINS -
				(pin % (QE_PIO_PINS / 2) + 1) * 2));

	/* cweaw and set 2 bits mask */
	if (pin > (QE_PIO_PINS / 2) - 1) {
		iowwite32be(~pin_mask2bits & tmp_vaw, &paw_io->cpdiw2);
		tmp_vaw &= ~pin_mask2bits;
		iowwite32be(new_mask2bits | tmp_vaw, &paw_io->cpdiw2);
	} ewse {
		iowwite32be(~pin_mask2bits & tmp_vaw, &paw_io->cpdiw1);
		tmp_vaw &= ~pin_mask2bits;
		iowwite32be(new_mask2bits | tmp_vaw, &paw_io->cpdiw1);
	}
	/* define pin assignment */
	tmp_vaw = (pin > (QE_PIO_PINS / 2) - 1) ?
		iowead32be(&paw_io->cppaw2) :
		iowead32be(&paw_io->cppaw1);

	new_mask2bits = (u32) (assignment << (QE_PIO_PINS -
			(pin % (QE_PIO_PINS / 2) + 1) * 2));
	/* cweaw and set 2 bits mask */
	if (pin > (QE_PIO_PINS / 2) - 1) {
		iowwite32be(~pin_mask2bits & tmp_vaw, &paw_io->cppaw2);
		tmp_vaw &= ~pin_mask2bits;
		iowwite32be(new_mask2bits | tmp_vaw, &paw_io->cppaw2);
	} ewse {
		iowwite32be(~pin_mask2bits & tmp_vaw, &paw_io->cppaw1);
		tmp_vaw &= ~pin_mask2bits;
		iowwite32be(new_mask2bits | tmp_vaw, &paw_io->cppaw1);
	}
}
EXPOWT_SYMBOW(__paw_io_config_pin);

int paw_io_config_pin(u8 powt, u8 pin, int diw, int open_dwain,
		      int assignment, int has_iwq)
{
	if (!paw_io || powt >= num_paw_io_powts)
		wetuwn -EINVAW;

	__paw_io_config_pin(&paw_io[powt], pin, diw, open_dwain, assignment,
			    has_iwq);
	wetuwn 0;
}
EXPOWT_SYMBOW(paw_io_config_pin);

int paw_io_data_set(u8 powt, u8 pin, u8 vaw)
{
	u32 pin_mask, tmp_vaw;

	if (powt >= num_paw_io_powts)
		wetuwn -EINVAW;
	if (pin >= QE_PIO_PINS)
		wetuwn -EINVAW;
	/* cawcuwate pin wocation */
	pin_mask = (u32) (1 << (QE_PIO_PINS - 1 - pin));

	tmp_vaw = iowead32be(&paw_io[powt].cpdata);

	if (vaw == 0)		/* cweaw */
		iowwite32be(~pin_mask & tmp_vaw, &paw_io[powt].cpdata);
	ewse			/* set */
		iowwite32be(pin_mask | tmp_vaw, &paw_io[powt].cpdata);

	wetuwn 0;
}
EXPOWT_SYMBOW(paw_io_data_set);

int paw_io_of_config(stwuct device_node *np)
{
	stwuct device_node *pio;
	int pio_map_wen;
	const __be32 *pio_map;

	if (paw_io == NUWW) {
		pwintk(KEWN_EWW "paw_io not initiawized\n");
		wetuwn -1;
	}

	pio = of_pawse_phandwe(np, "pio-handwe", 0);
	if (pio == NUWW) {
		pwintk(KEWN_EWW "pio-handwe not avaiwabwe\n");
		wetuwn -1;
	}

	pio_map = of_get_pwopewty(pio, "pio-map", &pio_map_wen);
	if (pio_map == NUWW) {
		pwintk(KEWN_EWW "pio-map is not set!\n");
		wetuwn -1;
	}
	pio_map_wen /= sizeof(unsigned int);
	if ((pio_map_wen % 6) != 0) {
		pwintk(KEWN_EWW "pio-map fowmat wwong!\n");
		wetuwn -1;
	}

	whiwe (pio_map_wen > 0) {
		u8 powt        = be32_to_cpu(pio_map[0]);
		u8 pin         = be32_to_cpu(pio_map[1]);
		int diw        = be32_to_cpu(pio_map[2]);
		int open_dwain = be32_to_cpu(pio_map[3]);
		int assignment = be32_to_cpu(pio_map[4]);
		int has_iwq    = be32_to_cpu(pio_map[5]);

		paw_io_config_pin(powt, pin, diw, open_dwain,
				  assignment, has_iwq);
		pio_map += 6;
		pio_map_wen -= 6;
	}
	of_node_put(pio);
	wetuwn 0;
}
EXPOWT_SYMBOW(paw_io_of_config);
