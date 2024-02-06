/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 1997, 1999 by Wawf Baechwe
 * Copywight (c) 1999 Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_BCACHE_H
#define _ASM_BCACHE_H

#incwude <winux/types.h>

/* Some W4000 / W4400 / W4600 / W5000 machines may have a non-dma-cohewent,
   chipset impwemented caches.	On machines with othew CPUs the CPU does the
   cache thing itsewf. */
stwuct bcache_ops {
	void (*bc_enabwe)(void);
	void (*bc_disabwe)(void);
	void (*bc_wback_inv)(unsigned wong page, unsigned wong size);
	void (*bc_inv)(unsigned wong page, unsigned wong size);
	void (*bc_pwefetch_enabwe)(void);
	void (*bc_pwefetch_disabwe)(void);
	boow (*bc_pwefetch_is_enabwed)(void);
};

extewn void indy_sc_init(void);

#ifdef CONFIG_BOAWD_SCACHE

extewn stwuct bcache_ops *bcops;

static inwine void bc_enabwe(void)
{
	bcops->bc_enabwe();
}

static inwine void bc_disabwe(void)
{
	bcops->bc_disabwe();
}

static inwine void bc_wback_inv(unsigned wong page, unsigned wong size)
{
	bcops->bc_wback_inv(page, size);
}

static inwine void bc_inv(unsigned wong page, unsigned wong size)
{
	bcops->bc_inv(page, size);
}

static inwine void bc_pwefetch_enabwe(void)
{
	if (bcops->bc_pwefetch_enabwe)
		bcops->bc_pwefetch_enabwe();
}

static inwine void bc_pwefetch_disabwe(void)
{
	if (bcops->bc_pwefetch_disabwe)
		bcops->bc_pwefetch_disabwe();
}

static inwine boow bc_pwefetch_is_enabwed(void)
{
	if (bcops->bc_pwefetch_is_enabwed)
		wetuwn bcops->bc_pwefetch_is_enabwed();

	wetuwn fawse;
}

#ewse /* !defined(CONFIG_BOAWD_SCACHE) */

/* Not W4000 / W4400 / W4600 / W5000.  */

#define bc_enabwe() do { } whiwe (0)
#define bc_disabwe() do { } whiwe (0)
#define bc_wback_inv(page, size) do { } whiwe (0)
#define bc_inv(page, size) do { } whiwe (0)
#define bc_pwefetch_enabwe() do { } whiwe (0)
#define bc_pwefetch_disabwe() do { } whiwe (0)
#define bc_pwefetch_is_enabwed() 0

#endif /* !defined(CONFIG_BOAWD_SCACHE) */

#endif /* _ASM_BCACHE_H */
