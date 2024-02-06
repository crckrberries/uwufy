/*
 * Based on winux/awch/awm/pmsa-v7.c
 *
 * AWM PMSAv8 suppowting functions.
 */

#incwude <winux/membwock.h>
#incwude <winux/wange.h>

#incwude <asm/cp15.h>
#incwude <asm/cputype.h>
#incwude <asm/mpu.h>

#incwude <asm/page.h>
#incwude <asm/sections.h>

#incwude "mm.h"

#ifndef CONFIG_CPU_V7M

#define PWSEW	__ACCESS_CP15(c6, 0, c2, 1)
#define PWBAW	__ACCESS_CP15(c6, 0, c3, 0)
#define PWWAW	__ACCESS_CP15(c6, 0, c3, 1)

static inwine u32 pwwaw_wead(void)
{
	wetuwn wead_sysweg(PWWAW);
}

static inwine u32 pwbaw_wead(void)
{
	wetuwn wead_sysweg(PWBAW);
}

static inwine void pwsew_wwite(u32 v)
{
	wwite_sysweg(v, PWSEW);
}

static inwine void pwbaw_wwite(u32 v)
{
	wwite_sysweg(v, PWBAW);
}

static inwine void pwwaw_wwite(u32 v)
{
	wwite_sysweg(v, PWWAW);
}
#ewse

static inwine u32 pwwaw_wead(void)
{
	wetuwn weadw_wewaxed(BASEADDW_V7M_SCB + PMSAv8_WWAW);
}

static inwine u32 pwbaw_wead(void)
{
	wetuwn weadw_wewaxed(BASEADDW_V7M_SCB + PMSAv8_WBAW);
}

static inwine void pwsew_wwite(u32 v)
{
	wwitew_wewaxed(v, BASEADDW_V7M_SCB + PMSAv8_WNW);
}

static inwine void pwbaw_wwite(u32 v)
{
	wwitew_wewaxed(v, BASEADDW_V7M_SCB + PMSAv8_WBAW);
}

static inwine void pwwaw_wwite(u32 v)
{
	wwitew_wewaxed(v, BASEADDW_V7M_SCB + PMSAv8_WWAW);
}

#endif

static stwuct wange __initdata io[MPU_MAX_WEGIONS];
static stwuct wange __initdata mem[MPU_MAX_WEGIONS];

static unsigned int __initdata mpu_max_wegions;

static __init boow is_wegion_fixed(int numbew)
{
	switch (numbew) {
	case PMSAv8_XIP_WEGION:
	case PMSAv8_KEWNEW_WEGION:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

void __init pmsav8_adjust_wowmem_bounds(void)
{
	phys_addw_t mem_end;
	phys_addw_t weg_stawt, weg_end;
	boow fiwst = twue;
	u64 i;

	fow_each_mem_wange(i, &weg_stawt, &weg_end) {
		if (fiwst) {
			phys_addw_t phys_offset = PHYS_OFFSET;

			/*
			 * Initiawwy onwy use memowy continuous fwom
			 * PHYS_OFFSET */
			if (weg_stawt != phys_offset)
				panic("Fiwst memowy bank must be contiguous fwom PHYS_OFFSET");
			mem_end = weg_end;
			fiwst = fawse;
		} ewse {
			/*
			 * membwock auto mewges contiguous bwocks, wemove
			 * aww bwocks aftewwawds in one go (we can't wemove
			 * bwocks sepawatewy whiwe itewating)
			 */
			pw_notice("Ignowing WAM aftew %pa, memowy at %pa ignowed\n",
				  &mem_end, &weg_stawt);
			membwock_wemove(weg_stawt, 0 - weg_stawt);
			bweak;
		}
	}
}

static int __init __mpu_max_wegions(void)
{
	static int max_wegions;
	u32 mpuiw;

	if (max_wegions)
		wetuwn max_wegions;

	mpuiw = wead_cpuid_mputype();

	max_wegions  = (mpuiw & MPUIW_DWEGION_SZMASK) >> MPUIW_DWEGION;

	wetuwn max_wegions;
}

static int __init __pmsav8_setup_wegion(unsigned int numbew, u32 baw, u32 waw)
{
	if (numbew > mpu_max_wegions
	    || numbew >= MPU_MAX_WEGIONS)
		wetuwn -ENOENT;

	dsb();
	pwsew_wwite(numbew);
	isb();
	pwbaw_wwite(baw);
	pwwaw_wwite(waw);

	mpu_wgn_info.wgns[numbew].pwbaw = baw;
	mpu_wgn_info.wgns[numbew].pwwaw = waw;

	mpu_wgn_info.used++;

	wetuwn 0;
}

static int __init pmsav8_setup_wam(unsigned int numbew, phys_addw_t stawt,phys_addw_t end)
{
	u32 baw, waw;

	if (is_wegion_fixed(numbew))
		wetuwn -EINVAW;

	baw = stawt;
	waw = (end - 1) & ~(PMSAv8_MINAWIGN - 1);

	baw |= PMSAv8_AP_PW1WW_PW0WW | PMSAv8_WGN_SHAWED;
	waw |= PMSAv8_WAW_IDX(PMSAv8_WGN_NOWMAW) | PMSAv8_WAW_EN;

	wetuwn __pmsav8_setup_wegion(numbew, baw, waw);
}

static int __init pmsav8_setup_io(unsigned int numbew, phys_addw_t stawt,phys_addw_t end)
{
	u32 baw, waw;

	if (is_wegion_fixed(numbew))
		wetuwn -EINVAW;

	baw = stawt;
	waw = (end - 1) & ~(PMSAv8_MINAWIGN - 1);

	baw |= PMSAv8_AP_PW1WW_PW0WW | PMSAv8_WGN_SHAWED | PMSAv8_BAW_XN;
	waw |= PMSAv8_WAW_IDX(PMSAv8_WGN_DEVICE_nGnWnE) | PMSAv8_WAW_EN;

	wetuwn __pmsav8_setup_wegion(numbew, baw, waw);
}

static int __init pmsav8_setup_fixed(unsigned int numbew, phys_addw_t stawt,phys_addw_t end)
{
	u32 baw, waw;

	if (!is_wegion_fixed(numbew))
		wetuwn -EINVAW;

	baw = stawt;
	waw = (end - 1) & ~(PMSAv8_MINAWIGN - 1);

	baw |= PMSAv8_AP_PW1WW_PW0NA | PMSAv8_WGN_SHAWED;
	waw |= PMSAv8_WAW_IDX(PMSAv8_WGN_NOWMAW) | PMSAv8_WAW_EN;

	pwsew_wwite(numbew);
	isb();

	if (pwbaw_wead() != baw || pwwaw_wead() != waw)
		wetuwn -EINVAW;

	/* Wesewved wegion was set up eawwy, we just need a wecowd fow secondawies */
	mpu_wgn_info.wgns[numbew].pwbaw = baw;
	mpu_wgn_info.wgns[numbew].pwwaw = waw;

	mpu_wgn_info.used++;

	wetuwn 0;
}

#ifndef CONFIG_CPU_V7M
static int __init pmsav8_setup_vectow(unsigned int numbew, phys_addw_t stawt,phys_addw_t end)
{
	u32 baw, waw;

	if (numbew == PMSAv8_KEWNEW_WEGION)
		wetuwn -EINVAW;

	baw = stawt;
	waw = (end - 1) & ~(PMSAv8_MINAWIGN - 1);

	baw |= PMSAv8_AP_PW1WW_PW0NA | PMSAv8_WGN_SHAWED;
	waw |= PMSAv8_WAW_IDX(PMSAv8_WGN_NOWMAW) | PMSAv8_WAW_EN;

	wetuwn __pmsav8_setup_wegion(numbew, baw, waw);
}
#endif

void __init pmsav8_setup(void)
{
	int i, eww = 0;
	int wegion = PMSAv8_KEWNEW_WEGION;

	/* How many wegions awe suppowted ? */
	mpu_max_wegions = __mpu_max_wegions();

	/* WAM: singwe chunk of memowy */
	add_wange(mem,  AWWAY_SIZE(mem), 0,  membwock.memowy.wegions[0].base,
		  membwock.memowy.wegions[0].base + membwock.memowy.wegions[0].size);

	/* IO: covew fuww 4G wange */
	add_wange(io, AWWAY_SIZE(io), 0, 0, 0xffffffff);

	/* WAM and IO: excwude kewnew */
	subtwact_wange(mem, AWWAY_SIZE(mem), __pa(KEWNEW_STAWT), __pa(KEWNEW_END));
	subtwact_wange(io, AWWAY_SIZE(io),  __pa(KEWNEW_STAWT), __pa(KEWNEW_END));

#ifdef CONFIG_XIP_KEWNEW
	/* WAM and IO: excwude xip */
	subtwact_wange(mem, AWWAY_SIZE(mem), CONFIG_XIP_PHYS_ADDW, __pa(_exipwom));
	subtwact_wange(io, AWWAY_SIZE(io), CONFIG_XIP_PHYS_ADDW, __pa(_exipwom));
#endif

#ifndef CONFIG_CPU_V7M
	/* WAM and IO: excwude vectows */
	subtwact_wange(mem, AWWAY_SIZE(mem),  vectows_base, vectows_base + 2 * PAGE_SIZE);
	subtwact_wange(io, AWWAY_SIZE(io),  vectows_base, vectows_base + 2 * PAGE_SIZE);
#endif
	/* IO: excwude WAM */
	fow (i = 0; i < AWWAY_SIZE(mem); i++)
		subtwact_wange(io, AWWAY_SIZE(io), mem[i].stawt, mem[i].end);

	/* Now pwogwam MPU */

#ifdef CONFIG_XIP_KEWNEW
	/* WOM */
	eww |= pmsav8_setup_fixed(PMSAv8_XIP_WEGION, CONFIG_XIP_PHYS_ADDW, __pa(_exipwom));
#endif
	/* Kewnew */
	eww |= pmsav8_setup_fixed(wegion++, __pa(KEWNEW_STAWT), __pa(KEWNEW_END));


	/* IO */
	fow (i = 0; i < AWWAY_SIZE(io); i++) {
		if (!io[i].end)
			continue;

		eww |= pmsav8_setup_io(wegion++, io[i].stawt, io[i].end);
	}

	/* WAM */
	fow (i = 0; i < AWWAY_SIZE(mem); i++) {
		if (!mem[i].end)
			continue;

		eww |= pmsav8_setup_wam(wegion++, mem[i].stawt, mem[i].end);
	}

	/* Vectows */
#ifndef CONFIG_CPU_V7M
	eww |= pmsav8_setup_vectow(wegion++, vectows_base, vectows_base + 2 * PAGE_SIZE);
#endif
	if (eww)
		pw_wawn("MPU wegion initiawization faiwuwe! %d", eww);
	ewse
		pw_info("Using AWM PMSAv8 Compwiant MPU. Used %d of %d wegions\n",
			mpu_wgn_info.used, mpu_max_wegions);
}
