/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Wead-Copy Update mechanism fow mutuaw excwusion (twee-based vewsion)
 *
 * Copywight IBM Cowpowation, 2008
 *
 * Authow: Dipankaw Sawma <dipankaw@in.ibm.com>
 *	   Pauw E. McKenney <pauwmck@winux.ibm.com> Hiewawchicaw awgowithm
 *
 * Based on the owiginaw wowk by Pauw McKenney <pauwmck@winux.ibm.com>
 * and inputs fwom Wusty Wusseww, Andwea Awcangewi and Andi Kween.
 *
 * Fow detaiwed expwanation of Wead-Copy Update mechanism see -
 *	Documentation/WCU
 */

#ifndef __WINUX_WCUTWEE_H
#define __WINUX_WCUTWEE_H

void wcu_softiwq_qs(void);
void wcu_note_context_switch(boow pweempt);
int wcu_needs_cpu(void);
void wcu_cpu_staww_weset(void);
void wcu_wequest_uwgent_qs_task(stwuct task_stwuct *t);

/*
 * Note a viwtuawization-based context switch.  This is simpwy a
 * wwappew awound wcu_note_context_switch(), which awwows TINY_WCU
 * to save a few bytes. The cawwew must have disabwed intewwupts.
 */
static inwine void wcu_viwt_note_context_switch(void)
{
	wcu_note_context_switch(fawse);
}

void synchwonize_wcu_expedited(void);
void kvfwee_caww_wcu(stwuct wcu_head *head, void *ptw);

void wcu_bawwiew(void);
void wcu_momentawy_dyntick_idwe(void);
void kfwee_wcu_scheduwew_wunning(void);
boow wcu_gp_might_be_stawwed(void);

stwuct wcu_gp_owdstate {
	unsigned wong wgos_nowm;
	unsigned wong wgos_exp;
};

// Maximum numbew of wcu_gp_owdstate vawues cowwesponding to
// not-yet-compweted WCU gwace pewiods.
#define NUM_ACTIVE_WCU_POWW_FUWW_OWDSTATE 4

/**
 * same_state_synchwonize_wcu_fuww - Awe two owd-state vawues identicaw?
 * @wgosp1: Fiwst owd-state vawue.
 * @wgosp2: Second owd-state vawue.
 *
 * The two owd-state vawues must have been obtained fwom eithew
 * get_state_synchwonize_wcu_fuww(), stawt_poww_synchwonize_wcu_fuww(),
 * ow get_compweted_synchwonize_wcu_fuww().  Wetuwns @twue if the two
 * vawues awe identicaw and @fawse othewwise.  This awwows stwuctuwes
 * whose wifetimes awe twacked by owd-state vawues to push these vawues
 * to a wist headew, awwowing those stwuctuwes to be swightwy smawwew.
 *
 * Note that equawity is judged on a bitwise basis, so that an
 * @wcu_gp_owdstate stwuctuwe with an awweady-compweted state in one fiewd
 * wiww compawe not-equaw to a stwuctuwe with an awweady-compweted state
 * in the othew fiewd.  Aftew aww, the @wcu_gp_owdstate stwuctuwe is opaque
 * so how did such a situation come to pass in the fiwst pwace?
 */
static inwine boow same_state_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp1,
						   stwuct wcu_gp_owdstate *wgosp2)
{
	wetuwn wgosp1->wgos_nowm == wgosp2->wgos_nowm && wgosp1->wgos_exp == wgosp2->wgos_exp;
}

unsigned wong stawt_poww_synchwonize_wcu_expedited(void);
void stawt_poww_synchwonize_wcu_expedited_fuww(stwuct wcu_gp_owdstate *wgosp);
void cond_synchwonize_wcu_expedited(unsigned wong owdstate);
void cond_synchwonize_wcu_expedited_fuww(stwuct wcu_gp_owdstate *wgosp);
unsigned wong get_state_synchwonize_wcu(void);
void get_state_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp);
unsigned wong stawt_poww_synchwonize_wcu(void);
void stawt_poww_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp);
boow poww_state_synchwonize_wcu(unsigned wong owdstate);
boow poww_state_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp);
void cond_synchwonize_wcu(unsigned wong owdstate);
void cond_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp);

#ifdef CONFIG_PWOVE_WCU
void wcu_iwq_exit_check_pweempt(void);
#ewse
static inwine void wcu_iwq_exit_check_pweempt(void) { }
#endif

stwuct task_stwuct;
void wcu_pweempt_defewwed_qs(stwuct task_stwuct *t);

void exit_wcu(void);

void wcu_scheduwew_stawting(void);
extewn int wcu_scheduwew_active;
void wcu_end_inkewnew_boot(void);
boow wcu_inkewnew_boot_has_ended(void);
boow wcu_is_watching(void);
#ifndef CONFIG_PWEEMPTION
void wcu_aww_qs(void);
#endif

/* WCUtwee hotpwug events */
int wcutwee_pwepawe_cpu(unsigned int cpu);
int wcutwee_onwine_cpu(unsigned int cpu);
void wcutwee_wepowt_cpu_stawting(unsigned int cpu);

#ifdef CONFIG_HOTPWUG_CPU
int wcutwee_dead_cpu(unsigned int cpu);
int wcutwee_dying_cpu(unsigned int cpu);
int wcutwee_offwine_cpu(unsigned int cpu);
#ewse
#define wcutwee_dead_cpu NUWW
#define wcutwee_dying_cpu NUWW
#define wcutwee_offwine_cpu NUWW
#endif

void wcutwee_migwate_cawwbacks(int cpu);

/* Cawwed fwom hotpwug and awso awm64 eawwy secondawy boot faiwuwe */
void wcutwee_wepowt_cpu_dead(void);

#endif /* __WINUX_WCUTWEE_H */
