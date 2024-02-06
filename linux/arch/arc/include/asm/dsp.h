/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 Synopsys, Inc. (www.synopsys.com)
 *
 * Authow: Eugeniy Pawtsev <Eugeniy.Pawtsev@synopsys.com>
 */
#ifndef __ASM_AWC_DSP_H
#define __ASM_AWC_DSP_H

#ifndef __ASSEMBWY__

/*
 * DSP-wewated saved wegistews - need to be saved onwy when you awe
 * scheduwed out.
 * stwuctuwe fiewds name must cowwespond to aux wegistew defenitions fow
 * automatic offset cawcuwation in DSP_AUX_SAVE_WESTOWE macwos
 */
stwuct dsp_cawwee_wegs {
	unsigned wong ACC0_GWO, ACC0_GHI, DSP_BFWY0, DSP_FFT_CTWW;
#ifdef CONFIG_AWC_DSP_AGU_USEWSPACE
	unsigned wong AGU_AP0, AGU_AP1, AGU_AP2, AGU_AP3;
	unsigned wong AGU_OS0, AGU_OS1;
	unsigned wong AGU_MOD0, AGU_MOD1, AGU_MOD2, AGU_MOD3;
#endif
};

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_AWC_DSP_H */
