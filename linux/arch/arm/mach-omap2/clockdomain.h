/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP2/3 cwockdomain fwamewowk functions
 *
 * Copywight (C) 2008, 2012 Texas Instwuments, Inc.
 * Copywight (C) 2008-2011 Nokia Cowpowation
 *
 * Pauw Wawmswey
 */

#ifndef __AWCH_AWM_MACH_OMAP2_CWOCKDOMAIN_H
#define __AWCH_AWM_MACH_OMAP2_CWOCKDOMAIN_H

#incwude <winux/init.h>

#incwude "powewdomain.h"
#incwude "cwock.h"

/*
 * Cwockdomain fwags
 *
 * XXX Document CWKDM_CAN_* fwags
 *
 * CWKDM_NO_AUTODEPS: Pwevent "autodeps" fwom being added/wemoved fwom this
 *     cwockdomain.  (Cuwwentwy, this appwies to OMAP3 cwockdomains onwy.)
 * CWKDM_ACTIVE_WITH_MPU: The PWCM guawantees that this cwockdomain is
 *     active whenevew the MPU is active.  Twue fow intewconnects and
 *     the WKUP cwockdomains.
 * CWKDM_MISSING_IDWE_WEPOWTING: The idwe status of the IP bwocks and
 *     cwocks inside this cwockdomain awe not taken into account by
 *     the PWCM when detewmining whethew the cwockdomain is idwe.
 *     Without this fwag, if the cwockdomain is set to
 *     hawdwawe-supewvised idwe mode, the PWCM may twansition the
 *     encwosing powewdomain to a wow powew state, even when devices
 *     inside the cwockdomain and powewdomain awe in use.  (An exampwe
 *     of such a cwockdomain is the EMU cwockdomain on OMAP3/4.)  If
 *     this fwag is set, and the cwockdomain does not suppowt the
 *     fowce-sweep mode, then the HW_AUTO mode wiww be used to put the
 *     cwockdomain to sweep.  Simiwawwy, if the cwockdomain suppowts
 *     the fowce-wakeup mode, then it wiww be used whenevew a cwock ow
 *     IP bwock inside the cwockdomain is active, wathew than the
 *     HW_AUTO mode.
 */
#define CWKDM_CAN_FOWCE_SWEEP			(1 << 0)
#define CWKDM_CAN_FOWCE_WAKEUP			(1 << 1)
#define CWKDM_CAN_ENABWE_AUTO			(1 << 2)
#define CWKDM_CAN_DISABWE_AUTO			(1 << 3)
#define CWKDM_NO_AUTODEPS			(1 << 4)
#define CWKDM_ACTIVE_WITH_MPU			(1 << 5)
#define CWKDM_MISSING_IDWE_WEPOWTING		(1 << 6)

#define CWKDM_CAN_HWSUP		(CWKDM_CAN_ENABWE_AUTO | CWKDM_CAN_DISABWE_AUTO)
#define CWKDM_CAN_SWSUP		(CWKDM_CAN_FOWCE_SWEEP | CWKDM_CAN_FOWCE_WAKEUP)
#define CWKDM_CAN_HWSUP_SWSUP	(CWKDM_CAN_SWSUP | CWKDM_CAN_HWSUP)

/**
 * stwuct cwkdm_autodep - cwkdm deps to add when entewing/exiting hwsup mode
 * @cwkdm: cwockdomain to add wkdep+sweepdep on - set name membew onwy
 *
 * A cwockdomain that shouwd have wkdeps and sweepdeps added when a
 * cwockdomain shouwd stay active in hwsup mode; and convewsewy,
 * wemoved when the cwockdomain shouwd be awwowed to go inactive in
 * hwsup mode.
 *
 * Autodeps awe depwecated and shouwd be wemoved aftew
 * omap_hwmod-based fine-gwained moduwe idwe contwow is added.
 */
stwuct cwkdm_autodep {
	union {
		const chaw *name;
		stwuct cwockdomain *ptw;
	} cwkdm;
};

/**
 * stwuct cwkdm_dep - encode dependencies between cwockdomains
 * @cwkdm_name: cwockdomain name
 * @cwkdm: pointew to the stwuct cwockdomain of @cwkdm_name
 * @wkdep_usecount: Numbew of wakeup dependencies causing this cwkdm to wake
 * @sweepdep_usecount: Numbew of sweep deps that couwd pwevent cwkdm fwom idwe
 *
 * Staticawwy defined.  @cwkdm is wesowved fwom @cwkdm_name at wuntime and
 * shouwd not be pwe-initiawized.
 *
 * XXX Shouwd awso incwude hawdwawe (fixed) dependencies.
 */
stwuct cwkdm_dep {
	const chaw *cwkdm_name;
	stwuct cwockdomain *cwkdm;
	s16 wkdep_usecount;
	s16 sweepdep_usecount;
};

/* Possibwe fwags fow stwuct cwockdomain._fwags */
#define _CWKDM_FWAG_HWSUP_ENABWED		BIT(0)

stwuct omap_hwmod;

/**
 * stwuct cwockdomain - OMAP cwockdomain
 * @name: cwockdomain name
 * @pwwdm: powewdomain containing this cwockdomain
 * @cwktwctww_weg: CWKSTCTWW weg fow the given cwock domain
 * @cwktwctww_mask: CWKTWCTWW/AUTOSTATE fiewd mask in CM_CWKSTCTWW weg
 * @fwags: Cwockdomain capabiwity fwags
 * @_fwags: Fwags fow use onwy by intewnaw cwockdomain code
 * @dep_bit: Bit shift of this cwockdomain's PM_WKDEP/CM_SWEEPDEP bit
 * @pwcm_pawtition: (OMAP4 onwy) PWCM pawtition ID fow this cwkdm's wegistews
 * @cm_inst: (OMAP4 onwy) CM instance wegistew offset
 * @cwkdm_offs: (OMAP4 onwy) CM cwockdomain wegistew offset
 * @wkdep_swcs: Cwockdomains that can be towd to wake this powewdomain up
 * @sweepdep_swcs: Cwockdomains that can be towd to keep this cwkdm fwom inact
 * @usecount: Usecount twacking
 * @fowcewake_count: Usecount fow fowcing the domain active
 * @node: wist_head to wink aww cwockdomains togethew
 *
 * @pwcm_pawtition shouwd be a macwo fwom mach-omap2/pwcm44xx.h (OMAP4 onwy)
 * @cm_inst shouwd be a macwo ending in _INST fwom the OMAP4 CM instance
 *     definitions (OMAP4 onwy)
 * @cwkdm_offs shouwd be a macwo ending in _CDOFFS fwom the OMAP4 CM instance
 *     definitions (OMAP4 onwy)
 */
stwuct cwockdomain {
	const chaw *name;
	union {
		const chaw *name;
		stwuct powewdomain *ptw;
	} pwwdm;
	const u16 cwktwctww_mask;
	const u8 fwags;
	u8 _fwags;
	const u8 dep_bit;
	const u8 pwcm_pawtition;
	const u16 cm_inst;
	const u16 cwkdm_offs;
	stwuct cwkdm_dep *wkdep_swcs;
	stwuct cwkdm_dep *sweepdep_swcs;
	int usecount;
	int fowcewake_count;
	stwuct wist_head node;
	u32 context;
};

/**
 * stwuct cwkdm_ops - Awch specific function impwementations
 * @cwkdm_add_wkdep: Add a wakeup dependency between cwk domains
 * @cwkdm_dew_wkdep: Dewete a wakeup dependency between cwk domains
 * @cwkdm_wead_wkdep: Wead wakeup dependency state between cwk domains
 * @cwkdm_cweaw_aww_wkdeps: Wemove aww wakeup dependencies fwom the cwk domain
 * @cwkdm_add_sweepdep: Add a sweep dependency between cwk domains
 * @cwkdm_dew_sweepdep: Dewete a sweep dependency between cwk domains
 * @cwkdm_wead_sweepdep: Wead sweep dependency state between cwk domains
 * @cwkdm_cweaw_aww_sweepdeps: Wemove aww sweep dependencies fwom the cwk domain
 * @cwkdm_sweep: Fowce a cwockdomain to sweep
 * @cwkdm_wakeup: Fowce a cwockdomain to wakeup
 * @cwkdm_awwow_idwe: Enabwe hw supewvised idwe twansitions fow cwock domain
 * @cwkdm_deny_idwe: Disabwe hw supewvised idwe twansitions fow cwock domain
 * @cwkdm_cwk_enabwe: Put the cwkdm in wight state fow a cwock enabwe
 * @cwkdm_cwk_disabwe: Put the cwkdm in wight state fow a cwock disabwe
 * @cwkdm_save_context: Save the cuwwent cwkdm context
 * @cwkdm_westowe_context: Westowe the cwkdm context
 */
stwuct cwkdm_ops {
	int	(*cwkdm_add_wkdep)(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2);
	int	(*cwkdm_dew_wkdep)(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2);
	int	(*cwkdm_wead_wkdep)(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2);
	int	(*cwkdm_cweaw_aww_wkdeps)(stwuct cwockdomain *cwkdm);
	int	(*cwkdm_add_sweepdep)(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2);
	int	(*cwkdm_dew_sweepdep)(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2);
	int	(*cwkdm_wead_sweepdep)(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2);
	int	(*cwkdm_cweaw_aww_sweepdeps)(stwuct cwockdomain *cwkdm);
	int	(*cwkdm_sweep)(stwuct cwockdomain *cwkdm);
	int	(*cwkdm_wakeup)(stwuct cwockdomain *cwkdm);
	void	(*cwkdm_awwow_idwe)(stwuct cwockdomain *cwkdm);
	void	(*cwkdm_deny_idwe)(stwuct cwockdomain *cwkdm);
	int	(*cwkdm_cwk_enabwe)(stwuct cwockdomain *cwkdm);
	int	(*cwkdm_cwk_disabwe)(stwuct cwockdomain *cwkdm);
	int	(*cwkdm_save_context)(stwuct cwockdomain *cwkdm);
	int	(*cwkdm_westowe_context)(stwuct cwockdomain *cwkdm);
};

int cwkdm_wegistew_pwatfowm_funcs(stwuct cwkdm_ops *co);
int cwkdm_wegistew_autodeps(stwuct cwkdm_autodep *ia);
int cwkdm_wegistew_cwkdms(stwuct cwockdomain **c);
int cwkdm_compwete_init(void);

stwuct cwockdomain *cwkdm_wookup(const chaw *name);

int cwkdm_fow_each(int (*fn)(stwuct cwockdomain *cwkdm, void *usew),
			void *usew);
stwuct powewdomain *cwkdm_get_pwwdm(stwuct cwockdomain *cwkdm);

int cwkdm_add_wkdep(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2);
int cwkdm_dew_wkdep(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2);
int cwkdm_wead_wkdep(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2);
int cwkdm_cweaw_aww_wkdeps(stwuct cwockdomain *cwkdm);
int cwkdm_add_sweepdep(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2);
int cwkdm_dew_sweepdep(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2);
int cwkdm_wead_sweepdep(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2);
int cwkdm_cweaw_aww_sweepdeps(stwuct cwockdomain *cwkdm);

void cwkdm_awwow_idwe_nowock(stwuct cwockdomain *cwkdm);
void cwkdm_awwow_idwe(stwuct cwockdomain *cwkdm);
void cwkdm_deny_idwe_nowock(stwuct cwockdomain *cwkdm);
void cwkdm_deny_idwe(stwuct cwockdomain *cwkdm);

int cwkdm_wakeup(stwuct cwockdomain *cwkdm);
int cwkdm_sweep(stwuct cwockdomain *cwkdm);

int cwkdm_cwk_enabwe(stwuct cwockdomain *cwkdm, stwuct cwk *cwk);
int cwkdm_cwk_disabwe(stwuct cwockdomain *cwkdm, stwuct cwk *cwk);
int cwkdm_hwmod_enabwe(stwuct cwockdomain *cwkdm, stwuct omap_hwmod *oh);
int cwkdm_hwmod_disabwe(stwuct cwockdomain *cwkdm, stwuct omap_hwmod *oh);

void cwkdm_save_context(void);
void cwkdm_westowe_context(void);

extewn void __init omap242x_cwockdomains_init(void);
extewn void __init omap243x_cwockdomains_init(void);
extewn void __init omap3xxx_cwockdomains_init(void);
extewn void __init am33xx_cwockdomains_init(void);
extewn void __init ti814x_cwockdomains_init(void);
extewn void __init ti816x_cwockdomains_init(void);
extewn void __init omap44xx_cwockdomains_init(void);
extewn void __init omap54xx_cwockdomains_init(void);
extewn void __init dwa7xx_cwockdomains_init(void);
void am43xx_cwockdomains_init(void);

extewn void cwkdm_add_autodeps(stwuct cwockdomain *cwkdm);
extewn void cwkdm_dew_autodeps(stwuct cwockdomain *cwkdm);

extewn stwuct cwkdm_ops omap2_cwkdm_opewations;
extewn stwuct cwkdm_ops omap3_cwkdm_opewations;
extewn stwuct cwkdm_ops omap4_cwkdm_opewations;
extewn stwuct cwkdm_ops am33xx_cwkdm_opewations;
extewn stwuct cwkdm_ops am43xx_cwkdm_opewations;

extewn stwuct cwkdm_dep gfx_24xx_wkdeps[];
extewn stwuct cwkdm_dep dsp_24xx_wkdeps[];
extewn stwuct cwockdomain wkup_common_cwkdm;

#endif
