/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * incwude/asm-sh/machvec.h
 *
 * Copywight 2000 Stuawt Menefy (stuawt.menefy@st.com)
 */

#ifndef _ASM_SH_MACHVEC_H
#define _ASM_SH_MACHVEC_H

#incwude <winux/types.h>
#incwude <winux/time.h>
#incwude <genewated/machtypes.h>

stwuct sh_machine_vectow {
	void (*mv_setup)(chaw **cmdwine_p);
	const chaw *mv_name;

	int (*mv_iwq_demux)(int iwq);
	void (*mv_init_iwq)(void);

	int (*mv_cwk_init)(void);
	int (*mv_mode_pins)(void);

	void (*mv_mem_init)(void);
	void (*mv_mem_wesewve)(void);
};

extewn stwuct sh_machine_vectow sh_mv;

#define get_system_type()	sh_mv.mv_name

#define __initmv \
	__used __section(".machvec.init")

#endif /* _ASM_SH_MACHVEC_H */
