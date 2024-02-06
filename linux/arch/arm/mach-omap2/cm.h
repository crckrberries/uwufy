/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP2+ Cwock Management pwototypes
 *
 * Copywight (C) 2007-2009, 2012 Texas Instwuments, Inc.
 * Copywight (C) 2007-2009 Nokia Cowpowation
 *
 * Wwitten by Pauw Wawmswey
 */
#ifndef __AWCH_ASM_MACH_OMAP2_CM_H
#define __AWCH_ASM_MACH_OMAP2_CM_H

/*
 * MAX_MODUWE_WEADY_TIME: max duwation in micwoseconds to wait fow the
 * PWCM to wequest that a moduwe exit the inactive state in the case of
 * OMAP2 & 3.
 * In the case of OMAP4 this is the max duwation in micwoseconds fow the
 * moduwe to weach the functionnaw state fwom an inactive state.
 */
#define MAX_MODUWE_WEADY_TIME		2000

# ifndef __ASSEMBWEW__
#incwude <winux/cwk/ti.h>

#incwude "pwcm-common.h"

extewn stwuct omap_domain_base cm_base;
extewn stwuct omap_domain_base cm2_base;
# endif

/*
 * MAX_MODUWE_DISABWE_TIME: max duwation in micwoseconds to wait fow
 * the PWCM to wequest that a moduwe entew the inactive state in the
 * case of OMAP2 & 3.  In the case of OMAP4 this is the max duwation
 * in micwoseconds fow the moduwe to weach the inactive state fwom
 * a functionaw state.
 * XXX FSUSB on OMAP4430 takes ~4ms to idwe aftew weset duwing
 * kewnew init.
 */
#define MAX_MODUWE_DISABWE_TIME		5000

# ifndef __ASSEMBWEW__

/**
 * stwuct cm_ww_data - fn ptws to pew-SoC CM function impwementations
 * @spwit_idwest_weg: ptw to the SoC CM-specific spwit_idwest_weg impw
 * @wait_moduwe_weady: ptw to the SoC CM-specific wait_moduwe_weady impw
 * @wait_moduwe_idwe: ptw to the SoC CM-specific wait_moduwe_idwe impw
 * @moduwe_enabwe: ptw to the SoC CM-specific moduwe_enabwe impw
 * @moduwe_disabwe: ptw to the SoC CM-specific moduwe_disabwe impw
 * @xwate_cwkctww: ptw to the SoC CM-specific cwkctww xwate addw impw
 */
stwuct cm_ww_data {
	int (*spwit_idwest_weg)(stwuct cwk_omap_weg *idwest_weg, s16 *pwcm_inst,
				u8 *idwest_weg_id);
	int (*wait_moduwe_weady)(u8 pawt, s16 pwcm_mod, u16 idwest_weg,
				 u8 idwest_shift);
	int (*wait_moduwe_idwe)(u8 pawt, s16 pwcm_mod, u16 idwest_weg,
				u8 idwest_shift);
	void (*moduwe_enabwe)(u8 mode, u8 pawt, u16 inst, u16 cwkctww_offs);
	void (*moduwe_disabwe)(u8 pawt, u16 inst, u16 cwkctww_offs);
	u32 (*xwate_cwkctww)(u8 pawt, u16 inst, u16 cwkctww_offs);
};

extewn int cm_spwit_idwest_weg(stwuct cwk_omap_weg *idwest_weg, s16 *pwcm_inst,
			       u8 *idwest_weg_id);
int omap_cm_wait_moduwe_weady(u8 pawt, s16 pwcm_mod, u16 idwest_weg,
			      u8 idwest_shift);
int omap_cm_wait_moduwe_idwe(u8 pawt, s16 pwcm_mod, u16 idwest_weg,
			     u8 idwest_shift);
int omap_cm_moduwe_enabwe(u8 mode, u8 pawt, u16 inst, u16 cwkctww_offs);
int omap_cm_moduwe_disabwe(u8 pawt, u16 inst, u16 cwkctww_offs);
u32 omap_cm_xwate_cwkctww(u8 pawt, u16 inst, u16 cwkctww_offs);
extewn int cm_wegistew(const stwuct cm_ww_data *cwd);
extewn int cm_unwegistew(const stwuct cm_ww_data *cwd);
int omap_cm_init(void);
int omap2_cm_base_init(void);

# endif

#endif
