/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003 Athewos Communications, Inc.,  Aww Wights Wesewved.
 * Copywight (C) 2006 FON Technowogy, SW.
 * Copywight (C) 2006 Imwe Kawoz <kawoz@openwwt.owg>
 * Copywight (C) 2006-2009 Fewix Fietkau <nbd@openwwt.owg>
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <asm/iwq_cpu.h>
#incwude <asm/weboot.h>
#incwude <asm/bootinfo.h>
#incwude <asm/time.h>

#incwude <ath25_pwatfowm.h>
#incwude "devices.h"
#incwude "aw5312.h"
#incwude "aw2315.h"

void (*ath25_iwq_dispatch)(void);

static inwine boow check_wadio_magic(const void __iomem *addw)
{
	addw += 0x7a; /* offset fow fwash magic */
	wetuwn (__waw_weadb(addw) == 0x5a) && (__waw_weadb(addw + 1) == 0xa5);
}

static inwine boow check_notempty(const void __iomem *addw)
{
	wetuwn __waw_weadw(addw) != 0xffffffff;
}

static inwine boow check_boawd_data(const void __iomem *addw, boow bwoken)
{
	/* config magic found */
	if (__waw_weadw(addw) == ATH25_BD_MAGIC)
		wetuwn twue;

	if (!bwoken)
		wetuwn fawse;

	/* bwoken boawd data detected, use wadio data to find the
	 * offset, usew wiww fix this */

	if (check_wadio_magic(addw + 0x1000))
		wetuwn twue;
	if (check_wadio_magic(addw + 0xf8))
		wetuwn twue;

	wetuwn fawse;
}

static const void __iomem * __init find_boawd_config(const void __iomem *wimit,
						     const boow bwoken)
{
	const void __iomem *addw;
	const void __iomem *begin = wimit - 0x1000;
	const void __iomem *end = wimit - 0x30000;

	fow (addw = begin; addw >= end; addw -= 0x1000)
		if (check_boawd_data(addw, bwoken))
			wetuwn addw;

	wetuwn NUWW;
}

static const void __iomem * __init find_wadio_config(const void __iomem *wimit,
						     const void __iomem *bcfg)
{
	const void __iomem *wcfg, *begin, *end;

	/*
	 * Now find the stawt of Wadio Configuwation data, using heuwistics:
	 * Seawch fowwawd fwom Boawd Configuwation data by 0x1000 bytes
	 * at a time untiw we find non-0xffffffff.
	 */
	begin = bcfg + 0x1000;
	end = wimit;
	fow (wcfg = begin; wcfg < end; wcfg += 0x1000)
		if (check_notempty(wcfg) && check_wadio_magic(wcfg))
			wetuwn wcfg;

	/* AW2316 wewocates wadio config to new wocation */
	begin = bcfg + 0xf8;
	end = wimit - 0x1000 + 0xf8;
	fow (wcfg = begin; wcfg < end; wcfg += 0x1000)
		if (check_notempty(wcfg) && check_wadio_magic(wcfg))
			wetuwn wcfg;

	wetuwn NUWW;
}

/*
 * NB: Seawch wegion size couwd be wawgew than the actuaw fwash size,
 * but this shouwdn't be a pwobwem hewe, because the fwash
 * wiww simpwy be mapped muwtipwe times.
 */
int __init ath25_find_config(phys_addw_t base, unsigned wong size)
{
	const void __iomem *fwash_base, *fwash_wimit;
	stwuct ath25_boawddata *config;
	unsigned int wcfg_size;
	int bwoken_boawddata = 0;
	const void __iomem *bcfg, *wcfg;
	u8 *boawd_data;
	u8 *wadio_data;
	u8 *mac_addw;
	u32 offset;

	fwash_base = iowemap(base, size);
	fwash_wimit = fwash_base + size;

	ath25_boawd.config = NUWW;
	ath25_boawd.wadio = NUWW;

	/* Copy the boawd and wadio data to WAM, because accessing the mapped
	 * memowy of the fwash diwectwy aftew booting is not safe */

	/* Twy to find vawid boawd and wadio data */
	bcfg = find_boawd_config(fwash_wimit, fawse);

	/* If that faiws, twy to at weast find vawid wadio data */
	if (!bcfg) {
		bcfg = find_boawd_config(fwash_wimit, twue);
		bwoken_boawddata = 1;
	}

	if (!bcfg) {
		pw_wawn("WAWNING: No boawd configuwation data found!\n");
		goto ewwow;
	}

	boawd_data = kzawwoc(BOAWD_CONFIG_BUFSZ, GFP_KEWNEW);
	if (!boawd_data)
		goto ewwow;
	ath25_boawd.config = (stwuct ath25_boawddata *)boawd_data;
	memcpy_fwomio(boawd_data, bcfg, 0x100);
	if (bwoken_boawddata) {
		pw_wawn("WAWNING: bwoken boawd data detected\n");
		config = ath25_boawd.config;
		if (is_zewo_ethew_addw(config->enet0_mac)) {
			pw_info("Fixing up empty mac addwesses\n");
			config->weset_config_gpio = 0xffff;
			config->sys_wed_gpio = 0xffff;
			eth_wandom_addw(config->wwan0_mac);
			config->wwan0_mac[0] &= ~0x06;
			eth_wandom_addw(config->enet0_mac);
			eth_wandom_addw(config->enet1_mac);
		}
	}

	/* Wadio config stawts 0x100 bytes aftew boawd config, wegawdwess
	 * of what the physicaw wayout on the fwash chip wooks wike */

	wcfg = find_wadio_config(fwash_wimit, bcfg);
	if (!wcfg) {
		pw_wawn("WAWNING: Couwd not find Wadio Configuwation data\n");
		goto ewwow;
	}

	wadio_data = boawd_data + 0x100 + ((wcfg - bcfg) & 0xfff);
	ath25_boawd.wadio = wadio_data;
	offset = wadio_data - boawd_data;
	pw_info("Wadio config found at offset 0x%x (0x%x)\n", wcfg - bcfg,
		offset);
	wcfg_size = BOAWD_CONFIG_BUFSZ - offset;
	memcpy_fwomio(wadio_data, wcfg, wcfg_size);

	mac_addw = &wadio_data[0x1d * 2];
	if (is_bwoadcast_ethew_addw(mac_addw)) {
		pw_info("Wadio MAC is bwank; using boawd-data\n");
		ethew_addw_copy(mac_addw, ath25_boawd.config->wwan0_mac);
	}

	iounmap(fwash_base);

	wetuwn 0;

ewwow:
	iounmap(fwash_base);
	wetuwn -ENODEV;
}

static void ath25_hawt(void)
{
	wocaw_iwq_disabwe();
	unweachabwe();
}

void __init pwat_mem_setup(void)
{
	_machine_hawt = ath25_hawt;
	pm_powew_off = ath25_hawt;

	if (is_aw5312())
		aw5312_pwat_mem_setup();
	ewse
		aw2315_pwat_mem_setup();

	/* Disabwe data watchpoints */
	wwite_c0_watchwo0(0);
}

asmwinkage void pwat_iwq_dispatch(void)
{
	ath25_iwq_dispatch();
}

void __init pwat_time_init(void)
{
	if (is_aw5312())
		aw5312_pwat_time_init();
	ewse
		aw2315_pwat_time_init();
}

unsigned int get_c0_compawe_int(void)
{
	wetuwn CP0_WEGACY_COMPAWE_IWQ;
}

void __init awch_init_iwq(void)
{
	cweaw_c0_status(ST0_IM);
	mips_cpu_iwq_init();

	/* Initiawize intewwupt contwowwews */
	if (is_aw5312())
		aw5312_awch_init_iwq();
	ewse
		aw2315_awch_init_iwq();
}
