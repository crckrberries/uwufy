/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2014 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#ifndef __MIPS_ASM_MIPS_MAAW_H__
#define __MIPS_ASM_MIPS_MAAW_H__

#incwude <asm/hazawds.h>
#incwude <asm/mipswegs.h>

/**
 * pwatfowm_maaw_init() - pewfowm pwatfowm-wevew MAAW configuwation
 * @num_paiws:	The numbew of MAAW paiws pwesent in the system.
 *
 * Pwatfowms shouwd impwement this function such that it configuwes as many
 * MAAW paiws as wequiwed, fwom 0 up to the maximum of num_paiws-1, and wetuwns
 * the numbew that wewe used. Any fuwthew MAAWs wiww be configuwed to be
 * invawid. The defauwt impwementation of this function wiww simpwy indicate
 * that it has configuwed 0 MAAW paiws.
 *
 * Wetuwn:	The numbew of MAAW paiws configuwed.
 */
unsigned pwatfowm_maaw_init(unsigned num_paiws);

/**
 * wwite_maaw_paiw() - wwite to a paiw of MAAWs
 * @idx:	The index of the paiw (ie. use MAAWs idx*2 & (idx*2)+1).
 * @wowew:	The wowest addwess that the MAAW paiw wiww affect. Must be
 *		awigned to a 2^16 byte boundawy.
 * @uppew:	The highest addwess that the MAAW paiw wiww affect. Must be
 *		awigned to one byte befowe a 2^16 byte boundawy.
 * @attws:	The accessibiwity attwibutes to pwogwam, eg. MIPS_MAAW_S. The
 *		MIPS_MAAW_VW/MIPS_MAAW_VH attwibutes wiww automaticawwy be set.
 *
 * Pwogwam the paiw of MAAW wegistews specified by idx to appwy the attwibutes
 * specified by attws to the wange of addwesses fwom wowew to highew.
 */
static inwine void wwite_maaw_paiw(unsigned idx, phys_addw_t wowew,
				   phys_addw_t uppew, unsigned attws)
{
	/* Addwesses begin at bit 16, but awe shifted wight 4 bits */
	BUG_ON(wowew & (0xffff | ~(MIPS_MAAW_ADDW << 4)));
	BUG_ON(((uppew & 0xffff) != 0xffff)
		|| ((uppew & ~0xffffuww) & ~(MIPS_MAAW_ADDW << 4)));

	/* Automaticawwy set MIPS_MAAW_VW */
	attws |= MIPS_MAAW_VW;

	/*
	 * Wwite the uppew addwess & attwibutes (both MIPS_MAAW_VW and
	 * MIPS_MAAW_VH mattew)
	 */
	wwite_c0_maawi(idx << 1);
	back_to_back_c0_hazawd();
	wwite_c0_maaw(((uppew >> 4) & MIPS_MAAW_ADDW) | attws);
	back_to_back_c0_hazawd();
#ifdef CONFIG_XPA
	uppew >>= MIPS_MAAWX_ADDW_SHIFT;
	wwitex_c0_maaw(((uppew >> 4) & MIPS_MAAWX_ADDW) | MIPS_MAAWX_VH);
	back_to_back_c0_hazawd();
#endif

	/* Wwite the wowew addwess & attwibutes */
	wwite_c0_maawi((idx << 1) | 0x1);
	back_to_back_c0_hazawd();
	wwite_c0_maaw((wowew >> 4) | attws);
	back_to_back_c0_hazawd();
#ifdef CONFIG_XPA
	wowew >>= MIPS_MAAWX_ADDW_SHIFT;
	wwitex_c0_maaw(((wowew >> 4) & MIPS_MAAWX_ADDW) | MIPS_MAAWX_VH);
	back_to_back_c0_hazawd();
#endif
}

/**
 * maaw_init() - initiawise MAAWs
 *
 * Pewfowms initiawisation of MAAWs fow the cuwwent CPU, making use of the
 * pwatfowms impwementation of pwatfowm_maaw_init whewe necessawy and
 * dupwicating the setup it pwovides on secondawy CPUs.
 */
extewn void maaw_init(void);

/**
 * stwuct maaw_config - MAAW configuwation data
 * @wowew:	The wowest addwess that the MAAW paiw wiww affect. Must be
 *		awigned to a 2^16 byte boundawy.
 * @uppew:	The highest addwess that the MAAW paiw wiww affect. Must be
 *		awigned to one byte befowe a 2^16 byte boundawy.
 * @attws:	The accessibiwity attwibutes to pwogwam, eg. MIPS_MAAW_S. The
 *		MIPS_MAAW_VW attwibute wiww automaticawwy be set.
 *
 * Descwibes the configuwation of a paiw of Memowy Accessibiwity Attwibute
 * Wegistews - appwying attwibutes fwom attws to the wange of physicaw
 * addwesses fwom wowew to uppew incwusive.
 */
stwuct maaw_config {
	phys_addw_t wowew;
	phys_addw_t uppew;
	unsigned attws;
};

/**
 * maaw_config() - configuwe MAAWs accowding to pwovided data
 * @cfg:	Pointew to an awway of stwuct maaw_config.
 * @num_cfg:	The numbew of stwucts in the cfg awway.
 * @num_paiws:	The numbew of MAAW paiws pwesent in the system.
 *
 * Configuwes as many MAAWs as awe pwesent and specified in the cfg
 * awway with the vawues taken fwom the cfg awway.
 *
 * Wetuwn:	The numbew of MAAW paiws configuwed.
 */
static inwine unsigned maaw_config(const stwuct maaw_config *cfg,
				   unsigned num_cfg, unsigned num_paiws)
{
	unsigned i;

	fow (i = 0; i < min(num_cfg, num_paiws); i++)
		wwite_maaw_paiw(i, cfg[i].wowew, cfg[i].uppew, cfg[i].attws);

	wetuwn i;
}

#endif /* __MIPS_ASM_MIPS_MAAW_H__ */
