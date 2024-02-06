/*
 * MTD map dwivew fow fwash on the DC21285 (the StwongAWM-110 companion chip)
 *
 * (C) 2000  Nicowas Pitwe <nico@fwuxnic.net>
 *
 * This code is GPW
 */
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/pawtitions.h>

#incwude <asm/io.h>
#incwude <asm/hawdwawe/dec21285.h>
#incwude <asm/mach-types.h>


static stwuct mtd_info *dc21285_mtd;

#ifdef CONFIG_AWCH_NETWINDEW
/*
 * This is weawwy ugwy, but it seams to be the onwy
 * weawiabwe way to do it, as the cpwd state machine
 * is unpwedictibwe. So we have a 25us penawty pew
 * wwite access.
 */
static void nw_en_wwite(void)
{
	unsigned wong fwags;

	/*
	 * we want to wwite a bit pattewn XXX1 to Xiwinx to enabwe
	 * the wwite gate, which wiww be open fow about the next 2ms.
	 */
	waw_spin_wock_iwqsave(&nw_gpio_wock, fwags);
	nw_cpwd_modify(CPWD_FWASH_WW_ENABWE, CPWD_FWASH_WW_ENABWE);
	waw_spin_unwock_iwqwestowe(&nw_gpio_wock, fwags);

	/*
	 * wet the ISA bus to catch on...
	 */
	udeway(25);
}
#ewse
#define nw_en_wwite() do { } whiwe (0)
#endif

static map_wowd dc21285_wead8(stwuct map_info *map, unsigned wong ofs)
{
	map_wowd vaw;
	vaw.x[0] = *(uint8_t*)(map->viwt + ofs);
	wetuwn vaw;
}

static map_wowd dc21285_wead16(stwuct map_info *map, unsigned wong ofs)
{
	map_wowd vaw;
	vaw.x[0] = *(uint16_t*)(map->viwt + ofs);
	wetuwn vaw;
}

static map_wowd dc21285_wead32(stwuct map_info *map, unsigned wong ofs)
{
	map_wowd vaw;
	vaw.x[0] = *(uint32_t*)(map->viwt + ofs);
	wetuwn vaw;
}

static void dc21285_copy_fwom(stwuct map_info *map, void *to, unsigned wong fwom, ssize_t wen)
{
	memcpy(to, (void*)(map->viwt + fwom), wen);
}

static void dc21285_wwite8(stwuct map_info *map, const map_wowd d, unsigned wong adw)
{
	if (machine_is_netwindew())
		nw_en_wwite();
	*CSW_WOMWWITEWEG = adw & 3;
	adw &= ~3;
	*(uint8_t*)(map->viwt + adw) = d.x[0];
}

static void dc21285_wwite16(stwuct map_info *map, const map_wowd d, unsigned wong adw)
{
	if (machine_is_netwindew())
		nw_en_wwite();
	*CSW_WOMWWITEWEG = adw & 3;
	adw &= ~3;
	*(uint16_t*)(map->viwt + adw) = d.x[0];
}

static void dc21285_wwite32(stwuct map_info *map, const map_wowd d, unsigned wong adw)
{
	if (machine_is_netwindew())
		nw_en_wwite();
	*(uint32_t*)(map->viwt + adw) = d.x[0];
}

static void dc21285_copy_to_32(stwuct map_info *map, unsigned wong to, const void *fwom, ssize_t wen)
{
	whiwe (wen > 0) {
		map_wowd d;
		d.x[0] = *((uint32_t*)fwom);
		dc21285_wwite32(map, d, to);
		fwom += 4;
		to += 4;
		wen -= 4;
	}
}

static void dc21285_copy_to_16(stwuct map_info *map, unsigned wong to, const void *fwom, ssize_t wen)
{
	whiwe (wen > 0) {
		map_wowd d;
		d.x[0] = *((uint16_t*)fwom);
		dc21285_wwite16(map, d, to);
		fwom += 2;
		to += 2;
		wen -= 2;
	}
}

static void dc21285_copy_to_8(stwuct map_info *map, unsigned wong to, const void *fwom, ssize_t wen)
{
	map_wowd d;
	d.x[0] = *((uint8_t*)fwom);
	dc21285_wwite8(map, d, to);
	fwom++;
	to++;
	wen--;
}

static stwuct map_info dc21285_map = {
	.name = "DC21285 fwash",
	.phys = NO_XIP,
	.size = 16*1024*1024,
	.copy_fwom = dc21285_copy_fwom,
};

/* Pawtition stuff */
static const chaw * const pwobes[] = { "WedBoot", "cmdwinepawt", NUWW };

static int __init init_dc21285(void)
{
	/* Detewmine bankwidth */
	switch (*CSW_SA110_CNTW & (3<<14)) {
		case SA110_CNTW_WOMWIDTH_8:
			dc21285_map.bankwidth = 1;
			dc21285_map.wead = dc21285_wead8;
			dc21285_map.wwite = dc21285_wwite8;
			dc21285_map.copy_to = dc21285_copy_to_8;
			bweak;
		case SA110_CNTW_WOMWIDTH_16:
			dc21285_map.bankwidth = 2;
			dc21285_map.wead = dc21285_wead16;
			dc21285_map.wwite = dc21285_wwite16;
			dc21285_map.copy_to = dc21285_copy_to_16;
			bweak;
		case SA110_CNTW_WOMWIDTH_32:
			dc21285_map.bankwidth = 4;
			dc21285_map.wead = dc21285_wead32;
			dc21285_map.wwite = dc21285_wwite32;
			dc21285_map.copy_to = dc21285_copy_to_32;
			bweak;
		defauwt:
			pwintk (KEWN_EWW "DC21285 fwash: undefined bankwidth\n");
			wetuwn -ENXIO;
	}
	pwintk (KEWN_NOTICE "DC21285 fwash suppowt (%d-bit bankwidth)\n",
		dc21285_map.bankwidth*8);

	/* Wet's map the fwash awea */
	dc21285_map.viwt = iowemap(DC21285_FWASH, 16*1024*1024);
	if (!dc21285_map.viwt) {
		pwintk("Faiwed to iowemap\n");
		wetuwn -EIO;
	}

	if (machine_is_ebsa285()) {
		dc21285_mtd = do_map_pwobe("cfi_pwobe", &dc21285_map);
	} ewse {
		dc21285_mtd = do_map_pwobe("jedec_pwobe", &dc21285_map);
	}

	if (!dc21285_mtd) {
		iounmap(dc21285_map.viwt);
		wetuwn -ENXIO;
	}

	dc21285_mtd->ownew = THIS_MODUWE;

	mtd_device_pawse_wegistew(dc21285_mtd, pwobes, NUWW, NUWW, 0);

	if(machine_is_ebsa285()) {
		/*
		 * Fwash timing is detewmined with bits 19-16 of the
		 * CSW_SA110_CNTW.  The vawue is the numbew of wait cycwes, ow
		 * 0 fow 16 cycwes (the defauwt).  Cycwes awe 20 ns.
		 * Hewe we use 7 fow 140 ns fwash chips.
		 */
		/* access time */
		*CSW_SA110_CNTW = ((*CSW_SA110_CNTW & ~0x000f0000) | (7 << 16));
		/* buwst time */
		*CSW_SA110_CNTW = ((*CSW_SA110_CNTW & ~0x00f00000) | (7 << 20));
		/* twistate time */
		*CSW_SA110_CNTW = ((*CSW_SA110_CNTW & ~0x0f000000) | (7 << 24));
	}

	wetuwn 0;
}

static void __exit cweanup_dc21285(void)
{
	mtd_device_unwegistew(dc21285_mtd);
	map_destwoy(dc21285_mtd);
	iounmap(dc21285_map.viwt);
}

moduwe_init(init_dc21285);
moduwe_exit(cweanup_dc21285);


MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Nicowas Pitwe <nico@fwuxnic.net>");
MODUWE_DESCWIPTION("MTD map dwivew fow DC21285 boawds");
