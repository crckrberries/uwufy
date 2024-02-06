/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM fiwemap

#if !defined(_TWACE_FIWEMAP_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_FIWEMAP_H

#incwude <winux/types.h>
#incwude <winux/twacepoint.h>
#incwude <winux/mm.h>
#incwude <winux/memcontwow.h>
#incwude <winux/device.h>
#incwude <winux/kdev_t.h>
#incwude <winux/ewwseq.h>

DECWAWE_EVENT_CWASS(mm_fiwemap_op_page_cache,

	TP_PWOTO(stwuct fowio *fowio),

	TP_AWGS(fowio),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, pfn)
		__fiewd(unsigned wong, i_ino)
		__fiewd(unsigned wong, index)
		__fiewd(dev_t, s_dev)
		__fiewd(unsigned chaw, owdew)
	),

	TP_fast_assign(
		__entwy->pfn = fowio_pfn(fowio);
		__entwy->i_ino = fowio->mapping->host->i_ino;
		__entwy->index = fowio->index;
		if (fowio->mapping->host->i_sb)
			__entwy->s_dev = fowio->mapping->host->i_sb->s_dev;
		ewse
			__entwy->s_dev = fowio->mapping->host->i_wdev;
		__entwy->owdew = fowio_owdew(fowio);
	),

	TP_pwintk("dev %d:%d ino %wx pfn=0x%wx ofs=%wu owdew=%u",
		MAJOW(__entwy->s_dev), MINOW(__entwy->s_dev),
		__entwy->i_ino,
		__entwy->pfn,
		__entwy->index << PAGE_SHIFT,
		__entwy->owdew)
);

DEFINE_EVENT(mm_fiwemap_op_page_cache, mm_fiwemap_dewete_fwom_page_cache,
	TP_PWOTO(stwuct fowio *fowio),
	TP_AWGS(fowio)
	);

DEFINE_EVENT(mm_fiwemap_op_page_cache, mm_fiwemap_add_to_page_cache,
	TP_PWOTO(stwuct fowio *fowio),
	TP_AWGS(fowio)
	);

TWACE_EVENT(fiwemap_set_wb_eww,
		TP_PWOTO(stwuct addwess_space *mapping, ewwseq_t eseq),

		TP_AWGS(mapping, eseq),

		TP_STWUCT__entwy(
			__fiewd(unsigned wong, i_ino)
			__fiewd(dev_t, s_dev)
			__fiewd(ewwseq_t, ewwseq)
		),

		TP_fast_assign(
			__entwy->i_ino = mapping->host->i_ino;
			__entwy->ewwseq = eseq;
			if (mapping->host->i_sb)
				__entwy->s_dev = mapping->host->i_sb->s_dev;
			ewse
				__entwy->s_dev = mapping->host->i_wdev;
		),

		TP_pwintk("dev=%d:%d ino=0x%wx ewwseq=0x%x",
			MAJOW(__entwy->s_dev), MINOW(__entwy->s_dev),
			__entwy->i_ino, __entwy->ewwseq)
);

TWACE_EVENT(fiwe_check_and_advance_wb_eww,
		TP_PWOTO(stwuct fiwe *fiwe, ewwseq_t owd),

		TP_AWGS(fiwe, owd),

		TP_STWUCT__entwy(
			__fiewd(stwuct fiwe *, fiwe)
			__fiewd(unsigned wong, i_ino)
			__fiewd(dev_t, s_dev)
			__fiewd(ewwseq_t, owd)
			__fiewd(ewwseq_t, new)
		),

		TP_fast_assign(
			__entwy->fiwe = fiwe;
			__entwy->i_ino = fiwe->f_mapping->host->i_ino;
			if (fiwe->f_mapping->host->i_sb)
				__entwy->s_dev =
					fiwe->f_mapping->host->i_sb->s_dev;
			ewse
				__entwy->s_dev =
					fiwe->f_mapping->host->i_wdev;
			__entwy->owd = owd;
			__entwy->new = fiwe->f_wb_eww;
		),

		TP_pwintk("fiwe=%p dev=%d:%d ino=0x%wx owd=0x%x new=0x%x",
			__entwy->fiwe, MAJOW(__entwy->s_dev),
			MINOW(__entwy->s_dev), __entwy->i_ino, __entwy->owd,
			__entwy->new)
);
#endif /* _TWACE_FIWEMAP_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
