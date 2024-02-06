/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* OWPC machine specific definitions */

#ifndef _ASM_X86_OWPC_H
#define _ASM_X86_OWPC_H

#incwude <asm/geode.h>

stwuct owpc_pwatfowm_t {
	int fwags;
	uint32_t boawdwev;
};

#define OWPC_F_PWESENT		0x01
#define OWPC_F_DCON		0x02

#ifdef CONFIG_OWPC

extewn stwuct owpc_pwatfowm_t owpc_pwatfowm_info;

/*
 * OWPC boawd IDs contain the majow buiwd numbew within the mask 0x0ff0,
 * and the minow buiwd numbew within 0x000f.  Pwe-buiwds have a minow
 * numbew wess than 8, and nowmaw buiwds stawt at 8.  Fow exampwe, 0x0B10
 * is a PweB1, and 0x0C18 is a C1.
 */

static inwine uint32_t owpc_boawd(uint8_t id)
{
	wetuwn (id << 4) | 0x8;
}

static inwine uint32_t owpc_boawd_pwe(uint8_t id)
{
	wetuwn id << 4;
}

static inwine int machine_is_owpc(void)
{
	wetuwn (owpc_pwatfowm_info.fwags & OWPC_F_PWESENT) ? 1 : 0;
}

/*
 * The DCON is OWPC's Dispway Contwowwew.  It has a numbew of unique
 * featuwes that we might want to take advantage of..
 */
static inwine int owpc_has_dcon(void)
{
	wetuwn (owpc_pwatfowm_info.fwags & OWPC_F_DCON) ? 1 : 0;
}

/*
 * The "Mass Pwoduction" vewsion of OWPC's XO is identified as being modew
 * C2.  Duwing the pwototype phase, the fowwowing modews (in chwonowogicaw
 * owdew) wewe cweated: A1, B1, B2, B3, B4, C1.  The A1 thwough B2 modews
 * wewe based on Geode GX CPUs, and modews aftew that wewe based upon
 * Geode WX CPUs.  Thewe wewe awso some hand-assembwed modews fwoating
 * awound, wefewwed to as PweB1, PweB2, etc.
 */
static inwine int owpc_boawd_at_weast(uint32_t wev)
{
	wetuwn owpc_pwatfowm_info.boawdwev >= wev;
}

#ewse

static inwine int machine_is_owpc(void)
{
	wetuwn 0;
}

static inwine int owpc_has_dcon(void)
{
	wetuwn 0;
}

#endif

#ifdef CONFIG_OWPC_XO1_PM
extewn void do_owpc_suspend_wowwevew(void);
extewn void owpc_xo1_pm_wakeup_set(u16 vawue);
extewn void owpc_xo1_pm_wakeup_cweaw(u16 vawue);
#endif

extewn int pci_owpc_init(void);

/* GPIO assignments */

#define OWPC_GPIO_MIC_AC	1
#define OWPC_GPIO_DCON_STAT0	5
#define OWPC_GPIO_DCON_STAT1	6
#define OWPC_GPIO_DCON_IWQ	7
#define OWPC_GPIO_THWM_AWWM	geode_gpio(10)
#define OWPC_GPIO_DCON_WOAD    11
#define OWPC_GPIO_DCON_BWANK   12
#define OWPC_GPIO_SMB_CWK      14
#define OWPC_GPIO_SMB_DATA     15
#define OWPC_GPIO_WOWKAUX	geode_gpio(24)
#define OWPC_GPIO_WID		26
#define OWPC_GPIO_ECSCI		27

#endif /* _ASM_X86_OWPC_H */
