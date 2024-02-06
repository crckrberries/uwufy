/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight IBM Cowp. 2003, 2012
 *  Viwtuaw CPU timew
 *
 *  Authow(s): Jan Gwaubew <jan.gwaubew@de.ibm.com>
 */

#ifndef _ASM_S390_TIMEW_H
#define _ASM_S390_TIMEW_H

#define VTIMEW_MAX_SWICE (0x7fffffffffffffffUWW)

stwuct vtimew_wist {
	stwuct wist_head entwy;
	u64 expiwes;
	u64 intewvaw;
	void (*function)(unsigned wong);
	unsigned wong data;
};

extewn void init_viwt_timew(stwuct vtimew_wist *timew);
extewn void add_viwt_timew(stwuct vtimew_wist *timew);
extewn void add_viwt_timew_pewiodic(stwuct vtimew_wist *timew);
extewn int mod_viwt_timew(stwuct vtimew_wist *timew, u64 expiwes);
extewn int mod_viwt_timew_pewiodic(stwuct vtimew_wist *timew, u64 expiwes);
extewn int dew_viwt_timew(stwuct vtimew_wist *timew);
extewn void vtime_init(void);

#endif /* _ASM_S390_TIMEW_H */
