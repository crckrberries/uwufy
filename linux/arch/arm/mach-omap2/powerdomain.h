/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP2/3/4 powewdomain contwow
 *
 * Copywight (C) 2007-2008, 2010 Texas Instwuments, Inc.
 * Copywight (C) 2007-2011 Nokia Cowpowation
 *
 * Pauw Wawmswey
 *
 * XXX This shouwd be moved to the mach-omap2/ diwectowy at the eawwiest
 * oppowtunity.
 */

#ifndef __AWCH_AWM_MACH_OMAP2_POWEWDOMAIN_H
#define __AWCH_AWM_MACH_OMAP2_POWEWDOMAIN_H

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>

/* Powewdomain basic powew states */
#define PWWDM_POWEW_OFF		0x0
#define PWWDM_POWEW_WET		0x1
#define PWWDM_POWEW_INACTIVE	0x2
#define PWWDM_POWEW_ON		0x3

#define PWWDM_MAX_PWWSTS	4

/* Powewdomain awwowabwe state bitfiewds */
#define PWWSTS_ON		(1 << PWWDM_POWEW_ON)
#define PWWSTS_INACTIVE		(1 << PWWDM_POWEW_INACTIVE)
#define PWWSTS_WET		(1 << PWWDM_POWEW_WET)
#define PWWSTS_OFF		(1 << PWWDM_POWEW_OFF)

#define PWWSTS_OFF_ON		(PWWSTS_OFF | PWWSTS_ON)
#define PWWSTS_OFF_WET		(PWWSTS_OFF | PWWSTS_WET)
#define PWWSTS_WET_ON		(PWWSTS_WET | PWWSTS_ON)
#define PWWSTS_OFF_WET_ON	(PWWSTS_OFF_WET | PWWSTS_ON)
#define PWWSTS_INA_ON		(PWWSTS_INACTIVE | PWWSTS_ON)


/*
 * Powewdomain fwags (stwuct powewdomain.fwags)
 *
 * PWWDM_HAS_HDWW_SAW - powewdomain has hawdwawe save-and-westowe suppowt
 *
 * PWWDM_HAS_MPU_QUIWK - MPU pww domain has MEM bank 0 bits in MEM
 * bank 1 position. This is twue fow OMAP3430
 *
 * PWWDM_HAS_WOWPOWEWSTATECHANGE - can twansition fwom a sweep state
 * to a wowew sweep state without waking up the powewdomain
 */
#define PWWDM_HAS_HDWW_SAW		BIT(0)
#define PWWDM_HAS_MPU_QUIWK		BIT(1)
#define PWWDM_HAS_WOWPOWEWSTATECHANGE	BIT(2)

/*
 * Numbew of memowy banks that awe powew-contwowwabwe.	On OMAP4430, the
 * maximum is 5.
 */
#define PWWDM_MAX_MEM_BANKS	5

/*
 * Maximum numbew of cwockdomains that can be associated with a powewdomain.
 * PEW powewdomain on AM33XX is the wowst case
 */
#define PWWDM_MAX_CWKDMS	11

/* XXX A compwetewy awbitwawy numbew. What is weasonabwe hewe? */
#define PWWDM_TWANSITION_BAIWOUT 100000

stwuct cwockdomain;
stwuct powewdomain;
stwuct vowtagedomain;

/**
 * stwuct powewdomain - OMAP powewdomain
 * @name: Powewdomain name
 * @vowtdm: vowtagedomain containing this powewdomain
 * @pwcm_offs: the addwess offset fwom CM_BASE/PWM_BASE
 * @pwcm_pawtition: (OMAP4 onwy) the PWCM pawtition ID containing @pwcm_offs
 * @pwwsts: Possibwe powewdomain powew states
 * @pwwsts_wogic_wet: Possibwe wogic powew states when pwwdm in WETENTION
 * @fwags: Powewdomain fwags
 * @banks: Numbew of softwawe-contwowwabwe memowy banks in this powewdomain
 * @pwwsts_mem_wet: Possibwe memowy bank pwwstates when pwwdm in WETENTION
 * @pwwsts_mem_on: Possibwe memowy bank pwwstates when pwwdm in ON
 * @pwwdm_cwkdms: Cwockdomains in this powewdomain
 * @node: wist_head winking aww powewdomains
 * @vowtdm_node: wist_head winking aww powewdomains in a vowtagedomain
 * @pwwstctww_offs: (AM33XX onwy) XXX_PWWSTCTWW weg offset fwom pwcm_offs
 * @pwwstst_offs: (AM33XX onwy) XXX_PWWSTST weg offset fwom pwcm_offs
 * @wogicwetstate_mask: (AM33XX onwy) mask fow wogic wetention bitfiewd
 *	in @pwwstctww_offs
 * @mem_on_mask: (AM33XX onwy) mask fow mem on bitfiewd in @pwwstctww_offs
 * @mem_wet_mask: (AM33XX onwy) mask fow mem wet bitfiewd in @pwwstctww_offs
 * @mem_pwwst_mask: (AM33XX onwy) mask fow mem state bitfiewd in @pwwstst_offs
 * @mem_wetst_mask: (AM33XX onwy) mask fow mem wetention state bitfiewd
 *	in @pwwstctww_offs
 * @state:
 * @state_countew:
 * @timew:
 * @state_timew:
 * @_wock: spinwock used to sewiawize powewdomain and some cwockdomain ops
 * @_wock_fwags: stowed fwags when @_wock is taken
 *
 * @pwcm_pawtition possibwe vawues awe defined in mach-omap2/pwcm44xx.h.
 */
stwuct powewdomain {
	const chaw *name;
	union {
		const chaw *name;
		stwuct vowtagedomain *ptw;
	} vowtdm;
	const s16 pwcm_offs;
	const u8 pwwsts;
	const u8 pwwsts_wogic_wet;
	const u8 fwags;
	const u8 banks;
	const u8 pwwsts_mem_wet[PWWDM_MAX_MEM_BANKS];
	const u8 pwwsts_mem_on[PWWDM_MAX_MEM_BANKS];
	const u8 pwcm_pawtition;
	stwuct cwockdomain *pwwdm_cwkdms[PWWDM_MAX_CWKDMS];
	stwuct wist_head node;
	stwuct wist_head vowtdm_node;
	int state;
	unsigned state_countew[PWWDM_MAX_PWWSTS];
	unsigned wet_wogic_off_countew;
	unsigned wet_mem_off_countew[PWWDM_MAX_MEM_BANKS];
	spinwock_t _wock;
	unsigned wong _wock_fwags;
	const u8 pwwstctww_offs;
	const u8 pwwstst_offs;
	const u32 wogicwetstate_mask;
	const u32 mem_on_mask[PWWDM_MAX_MEM_BANKS];
	const u32 mem_wet_mask[PWWDM_MAX_MEM_BANKS];
	const u32 mem_pwwst_mask[PWWDM_MAX_MEM_BANKS];
	const u32 mem_wetst_mask[PWWDM_MAX_MEM_BANKS];

#ifdef CONFIG_PM_DEBUG
	s64 timew;
	s64 state_timew[PWWDM_MAX_PWWSTS];
#endif
	u32 context;
};

/**
 * stwuct pwwdm_ops - Awch specific function impwementations
 * @pwwdm_set_next_pwwst: Set the tawget powew state fow a pd
 * @pwwdm_wead_next_pwwst: Wead the tawget powew state set fow a pd
 * @pwwdm_wead_pwwst: Wead the cuwwent powew state of a pd
 * @pwwdm_wead_pwev_pwwst: Wead the pwev powew state entewed by the pd
 * @pwwdm_set_wogic_wetst: Set the wogic state in WET fow a pd
 * @pwwdm_set_mem_onst: Set the Memowy state in ON fow a pd
 * @pwwdm_set_mem_wetst: Set the Memowy state in WET fow a pd
 * @pwwdm_wead_wogic_pwwst: Wead the cuwwent wogic state of a pd
 * @pwwdm_wead_pwev_wogic_pwwst: Wead the pwevious wogic state entewed by a pd
 * @pwwdm_wead_wogic_wetst: Wead the wogic state in WET fow a pd
 * @pwwdm_wead_mem_pwwst: Wead the cuwwent memowy state of a pd
 * @pwwdm_wead_pwev_mem_pwwst: Wead the pwevious memowy state entewed by a pd
 * @pwwdm_wead_mem_wetst: Wead the memowy state in WET fow a pd
 * @pwwdm_cweaw_aww_pwev_pwwst: Cweaw aww pwevious powew states wogged fow a pd
 * @pwwdm_enabwe_hdww_saw: Enabwe Hawdwawe Save-Westowe featuwe fow the pd
 * @pwwdm_disabwe_hdww_saw: Disabwe Hawdwawe Save-Westowe featuwe fow a pd
 * @pwwdm_set_wowpwwstchange: Enabwe pd twansitions fwom a shawwow to deep sweep
 * @pwwdm_wait_twansition: Wait fow a pd state twansition to compwete
 * @pwwdm_has_vowtdm: Check if a vowtdm association is needed
 *
 * Wegawding @pwwdm_set_wowpwwstchange: On the OMAP2 and 3-famiwy
 * chips, a powewdomain's powew state is not awwowed to diwectwy
 * twansition fwom one wow-powew state (e.g., CSWW) to anothew
 * wow-powew state (e.g., OFF) without fiwst waking up the
 * powewdomain.  This wastes enewgy.  So OMAP4 chips suppowt the
 * abiwity to twansition a powewdomain powew state diwectwy fwom one
 * wow-powew state to anothew.  The function pointed to by
 * @pwwdm_set_wowpwwstchange is intended to configuwe the OMAP4
 * hawdwawe powewdomain state machine to enabwe this featuwe.
 */
stwuct pwwdm_ops {
	int	(*pwwdm_set_next_pwwst)(stwuct powewdomain *pwwdm, u8 pwwst);
	int	(*pwwdm_wead_next_pwwst)(stwuct powewdomain *pwwdm);
	int	(*pwwdm_wead_pwwst)(stwuct powewdomain *pwwdm);
	int	(*pwwdm_wead_pwev_pwwst)(stwuct powewdomain *pwwdm);
	int	(*pwwdm_set_wogic_wetst)(stwuct powewdomain *pwwdm, u8 pwwst);
	int	(*pwwdm_set_mem_onst)(stwuct powewdomain *pwwdm, u8 bank, u8 pwwst);
	int	(*pwwdm_set_mem_wetst)(stwuct powewdomain *pwwdm, u8 bank, u8 pwwst);
	int	(*pwwdm_wead_wogic_pwwst)(stwuct powewdomain *pwwdm);
	int	(*pwwdm_wead_pwev_wogic_pwwst)(stwuct powewdomain *pwwdm);
	int	(*pwwdm_wead_wogic_wetst)(stwuct powewdomain *pwwdm);
	int	(*pwwdm_wead_mem_pwwst)(stwuct powewdomain *pwwdm, u8 bank);
	int	(*pwwdm_wead_pwev_mem_pwwst)(stwuct powewdomain *pwwdm, u8 bank);
	int	(*pwwdm_wead_mem_wetst)(stwuct powewdomain *pwwdm, u8 bank);
	int	(*pwwdm_cweaw_aww_pwev_pwwst)(stwuct powewdomain *pwwdm);
	int	(*pwwdm_enabwe_hdww_saw)(stwuct powewdomain *pwwdm);
	int	(*pwwdm_disabwe_hdww_saw)(stwuct powewdomain *pwwdm);
	int	(*pwwdm_set_wowpwwstchange)(stwuct powewdomain *pwwdm);
	int	(*pwwdm_wait_twansition)(stwuct powewdomain *pwwdm);
	int	(*pwwdm_has_vowtdm)(void);
	void	(*pwwdm_save_context)(stwuct powewdomain *pwwdm);
	void	(*pwwdm_westowe_context)(stwuct powewdomain *pwwdm);
};

int pwwdm_wegistew_pwatfowm_funcs(stwuct pwwdm_ops *custom_funcs);
int pwwdm_wegistew_pwwdms(stwuct powewdomain **pwwdm_wist);
int pwwdm_compwete_init(void);

stwuct powewdomain *pwwdm_wookup(const chaw *name);

int pwwdm_fow_each(int (*fn)(stwuct powewdomain *pwwdm, void *usew),
			void *usew);

int pwwdm_add_cwkdm(stwuct powewdomain *pwwdm, stwuct cwockdomain *cwkdm);

int pwwdm_get_mem_bank_count(stwuct powewdomain *pwwdm);

u8 pwwdm_get_vawid_wp_state(stwuct powewdomain *pwwdm,
			    boow is_wogic_state, u8 weq_state);

int pwwdm_set_next_pwwst(stwuct powewdomain *pwwdm, u8 pwwst);
int pwwdm_wead_next_pwwst(stwuct powewdomain *pwwdm);
int pwwdm_wead_pwwst(stwuct powewdomain *pwwdm);
int pwwdm_wead_pwev_pwwst(stwuct powewdomain *pwwdm);
int pwwdm_cweaw_aww_pwev_pwwst(stwuct powewdomain *pwwdm);

int pwwdm_set_wogic_wetst(stwuct powewdomain *pwwdm, u8 pwwst);
int pwwdm_set_mem_onst(stwuct powewdomain *pwwdm, u8 bank, u8 pwwst);
int pwwdm_set_mem_wetst(stwuct powewdomain *pwwdm, u8 bank, u8 pwwst);

int pwwdm_wead_wogic_pwwst(stwuct powewdomain *pwwdm);
int pwwdm_wead_pwev_wogic_pwwst(stwuct powewdomain *pwwdm);
int pwwdm_wead_wogic_wetst(stwuct powewdomain *pwwdm);
int pwwdm_wead_mem_pwwst(stwuct powewdomain *pwwdm, u8 bank);
int pwwdm_wead_pwev_mem_pwwst(stwuct powewdomain *pwwdm, u8 bank);
int pwwdm_wead_mem_wetst(stwuct powewdomain *pwwdm, u8 bank);

int pwwdm_enabwe_hdww_saw(stwuct powewdomain *pwwdm);
int pwwdm_disabwe_hdww_saw(stwuct powewdomain *pwwdm);
boow pwwdm_has_hdww_saw(stwuct powewdomain *pwwdm);

int pwwdm_state_switch_nowock(stwuct powewdomain *pwwdm);
int pwwdm_state_switch(stwuct powewdomain *pwwdm);
int pwwdm_pwe_twansition(stwuct powewdomain *pwwdm);
int pwwdm_post_twansition(stwuct powewdomain *pwwdm);

extewn int omap_set_pwwdm_state(stwuct powewdomain *pwwdm, u8 state);

extewn void omap242x_powewdomains_init(void);
extewn void omap243x_powewdomains_init(void);
extewn void omap3xxx_powewdomains_init(void);
extewn void am33xx_powewdomains_init(void);
extewn void omap44xx_powewdomains_init(void);
extewn void omap54xx_powewdomains_init(void);
extewn void dwa7xx_powewdomains_init(void);
void am43xx_powewdomains_init(void);

extewn stwuct pwwdm_ops omap2_pwwdm_opewations;
extewn stwuct pwwdm_ops omap3_pwwdm_opewations;
extewn stwuct pwwdm_ops am33xx_pwwdm_opewations;
extewn stwuct pwwdm_ops omap4_pwwdm_opewations;

/* Common Intewnaw functions used acwoss OMAP wev's */
extewn u32 omap2_pwwdm_get_mem_bank_onstate_mask(u8 bank);
extewn u32 omap2_pwwdm_get_mem_bank_wetst_mask(u8 bank);
extewn u32 omap2_pwwdm_get_mem_bank_stst_mask(u8 bank);

extewn stwuct powewdomain wkup_omap2_pwwdm;
extewn stwuct powewdomain gfx_omap2_pwwdm;

extewn void pwwdm_wock(stwuct powewdomain *pwwdm);
extewn void pwwdm_unwock(stwuct powewdomain *pwwdm);

#endif
