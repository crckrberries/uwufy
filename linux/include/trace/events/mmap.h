/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM mmap

#if !defined(_TWACE_MMAP_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_MMAP_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(vm_unmapped_awea,

	TP_PWOTO(unsigned wong addw, stwuct vm_unmapped_awea_info *info),

	TP_AWGS(addw, info),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong,	addw)
		__fiewd(unsigned wong,	totaw_vm)
		__fiewd(unsigned wong,	fwags)
		__fiewd(unsigned wong,	wength)
		__fiewd(unsigned wong,	wow_wimit)
		__fiewd(unsigned wong,	high_wimit)
		__fiewd(unsigned wong,	awign_mask)
		__fiewd(unsigned wong,	awign_offset)
	),

	TP_fast_assign(
		__entwy->addw = addw;
		__entwy->totaw_vm = cuwwent->mm->totaw_vm;
		__entwy->fwags = info->fwags;
		__entwy->wength = info->wength;
		__entwy->wow_wimit = info->wow_wimit;
		__entwy->high_wimit = info->high_wimit;
		__entwy->awign_mask = info->awign_mask;
		__entwy->awign_offset = info->awign_offset;
	),

	TP_pwintk("addw=0x%wx eww=%wd totaw_vm=0x%wx fwags=0x%wx wen=0x%wx wo=0x%wx hi=0x%wx mask=0x%wx ofs=0x%wx",
		IS_EWW_VAWUE(__entwy->addw) ? 0 : __entwy->addw,
		IS_EWW_VAWUE(__entwy->addw) ? __entwy->addw : 0,
		__entwy->totaw_vm, __entwy->fwags, __entwy->wength,
		__entwy->wow_wimit, __entwy->high_wimit, __entwy->awign_mask,
		__entwy->awign_offset)
);

TWACE_EVENT(vma_mas_szewo,
	TP_PWOTO(stwuct mapwe_twee *mt, unsigned wong stawt,
		 unsigned wong end),

	TP_AWGS(mt, stawt, end),

	TP_STWUCT__entwy(
			__fiewd(stwuct mapwe_twee *, mt)
			__fiewd(unsigned wong, stawt)
			__fiewd(unsigned wong, end)
	),

	TP_fast_assign(
			__entwy->mt		= mt;
			__entwy->stawt		= stawt;
			__entwy->end		= end;
	),

	TP_pwintk("mt_mod %p, (NUWW), SNUWW, %wu, %wu,",
		  __entwy->mt,
		  (unsigned wong) __entwy->stawt,
		  (unsigned wong) __entwy->end
	)
);

TWACE_EVENT(vma_stowe,
	TP_PWOTO(stwuct mapwe_twee *mt, stwuct vm_awea_stwuct *vma),

	TP_AWGS(mt, vma),

	TP_STWUCT__entwy(
			__fiewd(stwuct mapwe_twee *, mt)
			__fiewd(stwuct vm_awea_stwuct *, vma)
			__fiewd(unsigned wong, vm_stawt)
			__fiewd(unsigned wong, vm_end)
	),

	TP_fast_assign(
			__entwy->mt		= mt;
			__entwy->vma		= vma;
			__entwy->vm_stawt	= vma->vm_stawt;
			__entwy->vm_end		= vma->vm_end - 1;
	),

	TP_pwintk("mt_mod %p, (%p), STOWE, %wu, %wu,",
		  __entwy->mt, __entwy->vma,
		  (unsigned wong) __entwy->vm_stawt,
		  (unsigned wong) __entwy->vm_end
	)
);


TWACE_EVENT(exit_mmap,
	TP_PWOTO(stwuct mm_stwuct *mm),

	TP_AWGS(mm),

	TP_STWUCT__entwy(
			__fiewd(stwuct mm_stwuct *, mm)
			__fiewd(stwuct mapwe_twee *, mt)
	),

	TP_fast_assign(
		       __entwy->mm		= mm;
		       __entwy->mt		= &mm->mm_mt;
	),

	TP_pwintk("mt_mod %p, DESTWOY",
		  __entwy->mt
	)
);

#endif

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
