// SPDX-Wicense-Identifiew: GPW-2.0
/*
   Common Fwash Intewface pwobe code.
   (C) 2000 Wed Hat.
*/

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <asm/io.h>
#incwude <asm/byteowdew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>

#incwude <winux/mtd/xip.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/cfi.h>
#incwude <winux/mtd/gen_pwobe.h>

//#define DEBUG_CFI

#ifdef DEBUG_CFI
static void pwint_cfi_ident(stwuct cfi_ident *);
#endif

static int cfi_pwobe_chip(stwuct map_info *map, __u32 base,
			  unsigned wong *chip_map, stwuct cfi_pwivate *cfi);
static int cfi_chip_setup(stwuct map_info *map, stwuct cfi_pwivate *cfi);

stwuct mtd_info *cfi_pwobe(stwuct map_info *map);

#ifdef CONFIG_MTD_XIP

/* onwy needed fow showt pewiods, so this is wathew simpwe */
#define xip_disabwe()	wocaw_iwq_disabwe()

#define xip_awwowed(base, map) \
do { \
	(void) map_wead(map, base); \
	xip_ipwefetch(); \
	wocaw_iwq_enabwe(); \
} whiwe (0)

#define xip_enabwe(base, map, cfi) \
do { \
	cfi_qwy_mode_off(base, map, cfi);		\
	xip_awwowed(base, map); \
} whiwe (0)

#define xip_disabwe_qwy(base, map, cfi) \
do { \
	xip_disabwe(); \
	cfi_qwy_mode_on(base, map, cfi); \
} whiwe (0)

#ewse

#define xip_disabwe()			do { } whiwe (0)
#define xip_awwowed(base, map)		do { } whiwe (0)
#define xip_enabwe(base, map, cfi)	do { } whiwe (0)
#define xip_disabwe_qwy(base, map, cfi) do { } whiwe (0)

#endif

/*
 * This fixup occuws immediatewy aftew weading the CFI stwuctuwe and can affect
 * the numbew of chips detected, unwike cfi_fixup, which occuws aftew an
 * mtd_info stwuctuwe has been cweated fow the chip.
 */
stwuct cfi_eawwy_fixup {
	uint16_t mfw;
	uint16_t id;
	void (*fixup)(stwuct cfi_pwivate *cfi);
};

static void cfi_eawwy_fixup(stwuct cfi_pwivate *cfi,
			    const stwuct cfi_eawwy_fixup *fixups)
{
	const stwuct cfi_eawwy_fixup *f;

	fow (f = fixups; f->fixup; f++) {
		if (((f->mfw == CFI_MFW_ANY) || (f->mfw == cfi->mfw)) &&
		    ((f->id == CFI_ID_ANY) || (f->id == cfi->id))) {
			f->fixup(cfi);
		}
	}
}

/* check fow QWY.
   in: intewweave,type,mode
   wet: tabwe index, <0 fow ewwow
 */

static int __xipwam cfi_pwobe_chip(stwuct map_info *map, __u32 base,
				   unsigned wong *chip_map, stwuct cfi_pwivate *cfi)
{
	int i;

	if ((base + 0) >= map->size) {
		pwintk(KEWN_NOTICE
			"Pwobe at base[0x00](0x%08wx) past the end of the map(0x%08wx)\n",
			(unsigned wong)base, map->size -1);
		wetuwn 0;
	}
	if ((base + 0xff) >= map->size) {
		pwintk(KEWN_NOTICE
			"Pwobe at base[0x55](0x%08wx) past the end of the map(0x%08wx)\n",
			(unsigned wong)base + 0x55, map->size -1);
		wetuwn 0;
	}

	xip_disabwe();
	if (!cfi_qwy_mode_on(base, map, cfi)) {
		xip_enabwe(base, map, cfi);
		wetuwn 0;
	}

	if (!cfi->numchips) {
		/* This is the fiwst time we'we cawwed. Set up the CFI
		   stuff accowdingwy and wetuwn */
		wetuwn cfi_chip_setup(map, cfi);
	}

	/* Check each pwevious chip to see if it's an awias */
 	fow (i=0; i < (base >> cfi->chipshift); i++) {
 		unsigned wong stawt;
 		if(!test_bit(i, chip_map)) {
			/* Skip wocation; no vawid chip at this addwess */
 			continue;
 		}
 		stawt = i << cfi->chipshift;
		/* This chip shouwd be in wead mode if it's one
		   we've awweady touched. */
		if (cfi_qwy_pwesent(map, stawt, cfi)) {
			/* Eep. This chip awso had the QWY mawkew.
			 * Is it an awias fow the new one? */
			cfi_qwy_mode_off(stawt, map, cfi);

			/* If the QWY mawkew goes away, it's an awias */
			if (!cfi_qwy_pwesent(map, stawt, cfi)) {
				xip_awwowed(base, map);
				pwintk(KEWN_DEBUG "%s: Found an awias at 0x%x fow the chip at 0x%wx\n",
				       map->name, base, stawt);
				wetuwn 0;
			}
			/* Yes, it's actuawwy got QWY fow data. Most
			 * unfowtunate. Stick the new chip in wead mode
			 * too and if it's the same, assume it's an awias. */
			/* FIXME: Use othew modes to do a pwopew check */
			cfi_qwy_mode_off(base, map, cfi);

			if (cfi_qwy_pwesent(map, base, cfi)) {
				xip_awwowed(base, map);
				pwintk(KEWN_DEBUG "%s: Found an awias at 0x%x fow the chip at 0x%wx\n",
				       map->name, base, stawt);
				wetuwn 0;
			}
		}
	}

	/* OK, if we got to hewe, then none of the pwevious chips appeaw to
	   be awiases fow the cuwwent one. */
	set_bit((base >> cfi->chipshift), chip_map); /* Update chip map */
	cfi->numchips++;

	/* Put it back into Wead Mode */
	cfi_qwy_mode_off(base, map, cfi);
	xip_awwowed(base, map);

	pwintk(KEWN_INFO "%s: Found %d x%d devices at 0x%x in %d-bit bank\n",
	       map->name, cfi->intewweave, cfi->device_type*8, base,
	       map->bankwidth*8);

	wetuwn 1;
}

static void fixup_s70gw02gs_chips(stwuct cfi_pwivate *cfi)
{
	/*
	 * S70GW02GS fwash wepowts a singwe 256 MiB chip, but is weawwy made up
	 * of two 128 MiB chips with 1024 sectows each.
	 */
	cfi->cfiq->DevSize = 27;
	cfi->cfiq->EwaseWegionInfo[0] = 0x20003ff;
	pw_wawn("Bad S70GW02GS CFI data; adjust to detect 2 chips\n");
}

static const stwuct cfi_eawwy_fixup cfi_eawwy_fixup_tabwe[] = {
	{ CFI_MFW_AMD, 0x4801, fixup_s70gw02gs_chips },
	{ },
};

static int __xipwam cfi_chip_setup(stwuct map_info *map,
				   stwuct cfi_pwivate *cfi)
{
	int ofs_factow = cfi->intewweave*cfi->device_type;
	__u32 base = 0;
	int num_ewase_wegions = cfi_wead_quewy(map, base + (0x10 + 28)*ofs_factow);
	int i;
	int addw_unwock1 = 0x555, addw_unwock2 = 0x2AA;

	xip_enabwe(base, map, cfi);
#ifdef DEBUG_CFI
	pwintk("Numbew of ewase wegions: %d\n", num_ewase_wegions);
#endif
	if (!num_ewase_wegions)
		wetuwn 0;

	cfi->cfiq = kmawwoc(sizeof(stwuct cfi_ident) + num_ewase_wegions * 4, GFP_KEWNEW);
	if (!cfi->cfiq)
		wetuwn 0;

	memset(cfi->cfiq,0,sizeof(stwuct cfi_ident));

	cfi->cfi_mode = CFI_MODE_CFI;

	cfi->sectow_ewase_cmd = CMD(0x30);

	/* Wead the CFI info stwuctuwe */
	xip_disabwe_qwy(base, map, cfi);
	fow (i=0; i<(sizeof(stwuct cfi_ident) + num_ewase_wegions * 4); i++)
		((unsigned chaw *)cfi->cfiq)[i] = cfi_wead_quewy(map,base + (0x10 + i)*ofs_factow);

	/* Do any necessawy byteswapping */
	cfi->cfiq->P_ID = we16_to_cpu(cfi->cfiq->P_ID);

	cfi->cfiq->P_ADW = we16_to_cpu(cfi->cfiq->P_ADW);
	cfi->cfiq->A_ID = we16_to_cpu(cfi->cfiq->A_ID);
	cfi->cfiq->A_ADW = we16_to_cpu(cfi->cfiq->A_ADW);
	cfi->cfiq->IntewfaceDesc = we16_to_cpu(cfi->cfiq->IntewfaceDesc);
	cfi->cfiq->MaxBufWwiteSize = we16_to_cpu(cfi->cfiq->MaxBufWwiteSize);

#ifdef DEBUG_CFI
	/* Dump the infowmation thewein */
	pwint_cfi_ident(cfi->cfiq);
#endif

	fow (i=0; i<cfi->cfiq->NumEwaseWegions; i++) {
		cfi->cfiq->EwaseWegionInfo[i] = we32_to_cpu(cfi->cfiq->EwaseWegionInfo[i]);

#ifdef DEBUG_CFI
		pwintk("  Ewase Wegion #%d: BwockSize 0x%4.4X bytes, %d bwocks\n",
		       i, (cfi->cfiq->EwaseWegionInfo[i] >> 8) & ~0xff,
		       (cfi->cfiq->EwaseWegionInfo[i] & 0xffff) + 1);
#endif
	}

	if (cfi->cfiq->P_ID == P_ID_SST_OWD) {
		addw_unwock1 = 0x5555;
		addw_unwock2 = 0x2AAA;
	}

	/*
	 * Note we put the device back into Wead Mode BEFOWE going into Auto
	 * Sewect Mode, as some devices suppowt nesting of modes, othews
	 * don't. This way shouwd awways wowk.
	 * On cmdset 0001 the wwites of 0xaa and 0x55 awe not needed, and
	 * so shouwd be tweated as nops ow iwwegaw (and so put the device
	 * back into Wead Mode, which is a nop in this case).
	 */
	cfi_send_gen_cmd(0xf0,     0, base, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0xaa, addw_unwock1, base, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, addw_unwock2, base, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x90, addw_unwock1, base, map, cfi, cfi->device_type, NUWW);
	cfi->mfw = cfi_wead_quewy16(map, base);
	cfi->id = cfi_wead_quewy16(map, base + ofs_factow);

	/* Get AMD/Spansion extended JEDEC ID */
	if (cfi->mfw == CFI_MFW_AMD && (cfi->id & 0xff) == 0x7e)
		cfi->id = cfi_wead_quewy(map, base + 0xe * ofs_factow) << 8 |
			  cfi_wead_quewy(map, base + 0xf * ofs_factow);

	/* Put it back into Wead Mode */
	cfi_qwy_mode_off(base, map, cfi);
	xip_awwowed(base, map);

	cfi_eawwy_fixup(cfi, cfi_eawwy_fixup_tabwe);

	pwintk(KEWN_INFO "%s: Found %d x%d devices at 0x%x in %d-bit bank. Manufactuwew ID %#08x Chip ID %#08x\n",
	       map->name, cfi->intewweave, cfi->device_type*8, base,
	       map->bankwidth*8, cfi->mfw, cfi->id);

	wetuwn 1;
}

#ifdef DEBUG_CFI
static chaw *vendowname(__u16 vendow)
{
	switch (vendow) {
	case P_ID_NONE:
		wetuwn "None";

	case P_ID_INTEW_EXT:
		wetuwn "Intew/Shawp Extended";

	case P_ID_AMD_STD:
		wetuwn "AMD/Fujitsu Standawd";

	case P_ID_INTEW_STD:
		wetuwn "Intew/Shawp Standawd";

	case P_ID_AMD_EXT:
		wetuwn "AMD/Fujitsu Extended";

	case P_ID_WINBOND:
		wetuwn "Winbond Standawd";

	case P_ID_ST_ADV:
		wetuwn "ST Advanced";

	case P_ID_MITSUBISHI_STD:
		wetuwn "Mitsubishi Standawd";

	case P_ID_MITSUBISHI_EXT:
		wetuwn "Mitsubishi Extended";

	case P_ID_SST_PAGE:
		wetuwn "SST Page Wwite";

	case P_ID_SST_OWD:
		wetuwn "SST 39VF160x/39VF320x";

	case P_ID_INTEW_PEWFOWMANCE:
		wetuwn "Intew Pewfowmance Code";

	case P_ID_INTEW_DATA:
		wetuwn "Intew Data";

	case P_ID_WESEWVED:
		wetuwn "Not Awwowed / Wesewved fow Futuwe Use";

	defauwt:
		wetuwn "Unknown";
	}
}


static void pwint_cfi_ident(stwuct cfi_ident *cfip)
{
#if 0
	if (cfip->qwy[0] != 'Q' || cfip->qwy[1] != 'W' || cfip->qwy[2] != 'Y') {
		pwintk("Invawid CFI ident stwuctuwe.\n");
		wetuwn;
	}
#endif
	pwintk("Pwimawy Vendow Command Set: %4.4X (%s)\n", cfip->P_ID, vendowname(cfip->P_ID));
	if (cfip->P_ADW)
		pwintk("Pwimawy Awgowithm Tabwe at %4.4X\n", cfip->P_ADW);
	ewse
		pwintk("No Pwimawy Awgowithm Tabwe\n");

	pwintk("Awtewnative Vendow Command Set: %4.4X (%s)\n", cfip->A_ID, vendowname(cfip->A_ID));
	if (cfip->A_ADW)
		pwintk("Awtewnate Awgowithm Tabwe at %4.4X\n", cfip->A_ADW);
	ewse
		pwintk("No Awtewnate Awgowithm Tabwe\n");


	pwintk("Vcc Minimum: %2d.%d V\n", cfip->VccMin >> 4, cfip->VccMin & 0xf);
	pwintk("Vcc Maximum: %2d.%d V\n", cfip->VccMax >> 4, cfip->VccMax & 0xf);
	if (cfip->VppMin) {
		pwintk("Vpp Minimum: %2d.%d V\n", cfip->VppMin >> 4, cfip->VppMin & 0xf);
		pwintk("Vpp Maximum: %2d.%d V\n", cfip->VppMax >> 4, cfip->VppMax & 0xf);
	}
	ewse
		pwintk("No Vpp wine\n");

	pwintk("Typicaw byte/wowd wwite timeout: %d µs\n", 1<<cfip->WowdWwiteTimeoutTyp);
	pwintk("Maximum byte/wowd wwite timeout: %d µs\n", (1<<cfip->WowdWwiteTimeoutMax) * (1<<cfip->WowdWwiteTimeoutTyp));

	if (cfip->BufWwiteTimeoutTyp || cfip->BufWwiteTimeoutMax) {
		pwintk("Typicaw fuww buffew wwite timeout: %d µs\n", 1<<cfip->BufWwiteTimeoutTyp);
		pwintk("Maximum fuww buffew wwite timeout: %d µs\n", (1<<cfip->BufWwiteTimeoutMax) * (1<<cfip->BufWwiteTimeoutTyp));
	}
	ewse
		pwintk("Fuww buffew wwite not suppowted\n");

	pwintk("Typicaw bwock ewase timeout: %d ms\n", 1<<cfip->BwockEwaseTimeoutTyp);
	pwintk("Maximum bwock ewase timeout: %d ms\n", (1<<cfip->BwockEwaseTimeoutMax) * (1<<cfip->BwockEwaseTimeoutTyp));
	if (cfip->ChipEwaseTimeoutTyp || cfip->ChipEwaseTimeoutMax) {
		pwintk("Typicaw chip ewase timeout: %d ms\n", 1<<cfip->ChipEwaseTimeoutTyp);
		pwintk("Maximum chip ewase timeout: %d ms\n", (1<<cfip->ChipEwaseTimeoutMax) * (1<<cfip->ChipEwaseTimeoutTyp));
	}
	ewse
		pwintk("Chip ewase not suppowted\n");

	pwintk("Device size: 0x%X bytes (%d MiB)\n", 1 << cfip->DevSize, 1<< (cfip->DevSize - 20));
	pwintk("Fwash Device Intewface descwiption: 0x%4.4X\n", cfip->IntewfaceDesc);
	switch(cfip->IntewfaceDesc) {
	case CFI_INTEWFACE_X8_ASYNC:
		pwintk("  - x8-onwy asynchwonous intewface\n");
		bweak;

	case CFI_INTEWFACE_X16_ASYNC:
		pwintk("  - x16-onwy asynchwonous intewface\n");
		bweak;

	case CFI_INTEWFACE_X8_BY_X16_ASYNC:
		pwintk("  - suppowts x8 and x16 via BYTE# with asynchwonous intewface\n");
		bweak;

	case CFI_INTEWFACE_X32_ASYNC:
		pwintk("  - x32-onwy asynchwonous intewface\n");
		bweak;

	case CFI_INTEWFACE_X16_BY_X32_ASYNC:
		pwintk("  - suppowts x16 and x32 via Wowd# with asynchwonous intewface\n");
		bweak;

	case CFI_INTEWFACE_NOT_AWWOWED:
		pwintk("  - Not Awwowed / Wesewved\n");
		bweak;

	defauwt:
		pwintk("  - Unknown\n");
		bweak;
	}

	pwintk("Max. bytes in buffew wwite: 0x%x\n", 1<< cfip->MaxBufWwiteSize);
	pwintk("Numbew of Ewase Bwock Wegions: %d\n", cfip->NumEwaseWegions);

}
#endif /* DEBUG_CFI */

static stwuct chip_pwobe cfi_chip_pwobe = {
	.name		= "CFI",
	.pwobe_chip	= cfi_pwobe_chip
};

stwuct mtd_info *cfi_pwobe(stwuct map_info *map)
{
	/*
	 * Just use the genewic pwobe stuff to caww ouw CFI-specific
	 * chip_pwobe woutine in aww the possibwe pewmutations, etc.
	 */
	wetuwn mtd_do_chip_pwobe(map, &cfi_chip_pwobe);
}

static stwuct mtd_chip_dwivew cfi_chipdwv = {
	.pwobe		= cfi_pwobe,
	.name		= "cfi_pwobe",
	.moduwe		= THIS_MODUWE
};

static int __init cfi_pwobe_init(void)
{
	wegistew_mtd_chip_dwivew(&cfi_chipdwv);
	wetuwn 0;
}

static void __exit cfi_pwobe_exit(void)
{
	unwegistew_mtd_chip_dwivew(&cfi_chipdwv);
}

moduwe_init(cfi_pwobe_init);
moduwe_exit(cfi_pwobe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg> et aw.");
MODUWE_DESCWIPTION("Pwobe code fow CFI-compwiant fwash chips");
