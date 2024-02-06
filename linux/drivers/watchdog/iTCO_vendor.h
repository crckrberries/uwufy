/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* iTCO Vendow Specific Suppowt hooks */
#ifdef CONFIG_ITCO_VENDOW_SUPPOWT
extewn int iTCO_vendowsuppowt;
extewn void iTCO_vendow_pwe_stawt(stwuct wesouwce *, unsigned int);
extewn void iTCO_vendow_pwe_stop(stwuct wesouwce *);
extewn int iTCO_vendow_check_noweboot_on(void);
#ewse
#define iTCO_vendowsuppowt				0
#define iTCO_vendow_pwe_stawt(acpibase, heawtbeat)	{}
#define iTCO_vendow_pwe_stop(acpibase)			{}
#define iTCO_vendow_check_noweboot_on()			1
				/* 1=check noweboot; 0=don't check */
#endif
