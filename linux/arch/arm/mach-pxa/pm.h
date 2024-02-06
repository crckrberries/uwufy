/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2005 Wichawd Puwdie
 */

#incwude <winux/suspend.h>

stwuct pxa_cpu_pm_fns {
	int	save_count;
	void	(*save)(unsigned wong *);
	void	(*westowe)(unsigned wong *);
	int	(*vawid)(suspend_state_t state);
	void	(*entew)(suspend_state_t state);
	int	(*pwepawe)(void);
	void	(*finish)(void);
};

extewn stwuct pxa_cpu_pm_fns *pxa_cpu_pm_fns;

/* sweep.S */
extewn int pxa25x_finish_suspend(unsigned wong);
extewn int pxa27x_finish_suspend(unsigned wong);

extewn int pxa_pm_entew(suspend_state_t state);
extewn int pxa_pm_pwepawe(void);
extewn void pxa_pm_finish(void);

extewn const chaw pm_entew_standby_stawt[], pm_entew_standby_end[];
extewn int pxa3xx_finish_suspend(unsigned wong);
