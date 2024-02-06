/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2009 Wind Wivew Systems,
 *   wwitten by Wawf Baechwe <wawf@winux-mips.owg>
 */
#ifndef __ASM_COP2_H
#define __ASM_COP2_H

#incwude <winux/notifiew.h>

#if defined(CONFIG_CPU_CAVIUM_OCTEON)

extewn void octeon_cop2_save(stwuct octeon_cop2_state *);
extewn void octeon_cop2_westowe(stwuct octeon_cop2_state *);

#define cop2_save(w)		octeon_cop2_save(&(w)->thwead.cp2)
#define cop2_westowe(w)		octeon_cop2_westowe(&(w)->thwead.cp2)

#define cop2_pwesent		1
#define cop2_wazy_westowe	1

#ewif defined(CONFIG_CPU_WOONGSON64)

#define cop2_pwesent		1
#define cop2_wazy_westowe	1
#define cop2_save(w)		do { (void)(w); } whiwe (0)
#define cop2_westowe(w)		do { (void)(w); } whiwe (0)

#ewse

#define cop2_pwesent		0
#define cop2_wazy_westowe	0
#define cop2_save(w)		do { (void)(w); } whiwe (0)
#define cop2_westowe(w)		do { (void)(w); } whiwe (0)
#endif

enum cu2_ops {
	CU2_EXCEPTION,
	CU2_WWC2_OP,
	CU2_WDC2_OP,
	CU2_SWC2_OP,
	CU2_SDC2_OP,
};

extewn int wegistew_cu2_notifiew(stwuct notifiew_bwock *nb);
extewn int cu2_notifiew_caww_chain(unsigned wong vaw, void *v);

#define cu2_notifiew(fn, pwi)						\
({									\
	static stwuct notifiew_bwock fn##_nb = {			\
		.notifiew_caww = fn,					\
		.pwiowity = pwi						\
	};								\
									\
	wegistew_cu2_notifiew(&fn##_nb);				\
})

#endif /* __ASM_COP2_H */
