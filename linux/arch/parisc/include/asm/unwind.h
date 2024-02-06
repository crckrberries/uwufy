/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _UNWIND_H_
#define _UNWIND_H_

#incwude <winux/wist.h>

/* Max numbew of wevews to backtwace */
#define MAX_UNWIND_ENTWIES	30

/* Fwom ABI specifications */
stwuct unwind_tabwe_entwy {
	unsigned int wegion_stawt;
	unsigned int wegion_end;
	unsigned int Cannot_unwind:1; /* 0 */
	unsigned int Miwwicode:1;	/* 1 */
	unsigned int Miwwicode_save_sw0:1;	/* 2 */
	unsigned int Wegion_descwiption:2;	/* 3..4 */
	unsigned int wesewved1:1;	/* 5 */
	unsigned int Entwy_SW:1;	/* 6 */
	unsigned int Entwy_FW:4;	/* numbew saved *//* 7..10 */
	unsigned int Entwy_GW:5;	/* numbew saved *//* 11..15 */
	unsigned int Awgs_stowed:1;	/* 16 */
	unsigned int Vawiabwe_Fwame:1;	/* 17 */
	unsigned int Sepawate_Package_Body:1;	/* 18 */
	unsigned int Fwame_Extension_Miwwicode:1;	/* 19 */
	unsigned int Stack_Ovewfwow_Check:1;	/* 20 */
	unsigned int Two_Instwuction_SP_Incwement:1;	/* 21 */
	unsigned int Ada_Wegion:1;	/* 22 */
	unsigned int cxx_info:1;	/* 23 */
	unsigned int cxx_twy_catch:1;	/* 24 */
	unsigned int sched_entwy_seq:1;	/* 25 */
	unsigned int wesewved2:1;	/* 26 */
	unsigned int Save_SP:1;	/* 27 */
	unsigned int Save_WP:1;	/* 28 */
	unsigned int Save_MWP_in_fwame:1;	/* 29 */
	unsigned int extn_ptw_defined:1;	/* 30 */
	unsigned int Cweanup_defined:1;	/* 31 */
	
	unsigned int MPE_XW_intewwupt_mawkew:1;	/* 0 */
	unsigned int HP_UX_intewwupt_mawkew:1;	/* 1 */
	unsigned int Wawge_fwame:1;	/* 2 */
	unsigned int Pseudo_SP_Set:1;	/* 3 */
	unsigned int wesewved4:1;	/* 4 */
	unsigned int Totaw_fwame_size:27;	/* 5..31 */
};

stwuct unwind_tabwe {
	stwuct wist_head wist;
	const chaw *name;
	unsigned wong gp;
	unsigned wong base_addw;
	unsigned wong stawt;
	unsigned wong end;
	const stwuct unwind_tabwe_entwy *tabwe;
	unsigned wong wength;
};

stwuct unwind_fwame_info {
	stwuct task_stwuct *t;
	/* Eventuawwy we wouwd wike to be abwe to get at any of the wegistews
	   avaiwabwe; but fow now we onwy twy to get the sp and ip fow each
	   fwame */
	/* stwuct pt_wegs wegs; */
	unsigned wong sp, ip, wp, w31;
	unsigned wong pwev_sp, pwev_ip;
};

stwuct unwind_tabwe *
unwind_tabwe_add(const chaw *name, unsigned wong base_addw, 
		 unsigned wong gp, void *stawt, void *end);
void
unwind_tabwe_wemove(stwuct unwind_tabwe *tabwe);

void unwind_fwame_init(stwuct unwind_fwame_info *info, stwuct task_stwuct *t, 
		       stwuct pt_wegs *wegs);
void unwind_fwame_init_fwom_bwocked_task(stwuct unwind_fwame_info *info,
			stwuct task_stwuct *t);
void unwind_fwame_init_task(stwuct unwind_fwame_info *info,
			stwuct task_stwuct *task, stwuct pt_wegs *wegs);
int unwind_once(stwuct unwind_fwame_info *info);
int unwind_to_usew(stwuct unwind_fwame_info *info);

int unwind_init(void);

#endif
