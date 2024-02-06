/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM ocfs2

#if !defined(_TWACE_OCFS2_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_OCFS2_H

#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(ocfs2__int,
	TP_PWOTO(int num),
	TP_AWGS(num),
	TP_STWUCT__entwy(
		__fiewd(int, num)
	),
	TP_fast_assign(
		__entwy->num = num;
	),
	TP_pwintk("%d", __entwy->num)
);

#define DEFINE_OCFS2_INT_EVENT(name)	\
DEFINE_EVENT(ocfs2__int, name,	\
	TP_PWOTO(int num),	\
	TP_AWGS(num))

DECWAWE_EVENT_CWASS(ocfs2__uint,
	TP_PWOTO(unsigned int num),
	TP_AWGS(num),
	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	num		)
	),
	TP_fast_assign(
		__entwy->num	= 	num;
	),
	TP_pwintk("%u", __entwy->num)
);

#define DEFINE_OCFS2_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uint, name,	\
	TP_PWOTO(unsigned int num),	\
	TP_AWGS(num))

DECWAWE_EVENT_CWASS(ocfs2__uww,
	TP_PWOTO(unsigned wong wong bwkno),
	TP_AWGS(bwkno),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, bwkno)
	),
	TP_fast_assign(
		__entwy->bwkno = bwkno;
	),
	TP_pwintk("%wwu", __entwy->bwkno)
);

#define DEFINE_OCFS2_UWW_EVENT(name)	\
DEFINE_EVENT(ocfs2__uww, name,	\
	TP_PWOTO(unsigned wong wong num),	\
	TP_AWGS(num))

DECWAWE_EVENT_CWASS(ocfs2__pointew,
	TP_PWOTO(void *pointew),
	TP_AWGS(pointew),
	TP_STWUCT__entwy(
		__fiewd(void *, pointew)
	),
	TP_fast_assign(
		__entwy->pointew = pointew;
	),
	TP_pwintk("%p", __entwy->pointew)
);

#define DEFINE_OCFS2_POINTEW_EVENT(name)	\
DEFINE_EVENT(ocfs2__pointew, name,	\
	TP_PWOTO(void *pointew),	\
	TP_AWGS(pointew))

DECWAWE_EVENT_CWASS(ocfs2__stwing,
	TP_PWOTO(const chaw *name),
	TP_AWGS(name),
	TP_STWUCT__entwy(
		__stwing(name,name)
	),
	TP_fast_assign(
		__assign_stw(name, name);
	),
	TP_pwintk("%s", __get_stw(name))
);

#define DEFINE_OCFS2_STWING_EVENT(name)	\
DEFINE_EVENT(ocfs2__stwing, name,	\
	TP_PWOTO(const chaw *name),	\
	TP_AWGS(name))

DECWAWE_EVENT_CWASS(ocfs2__int_int,
	TP_PWOTO(int vawue1, int vawue2),
	TP_AWGS(vawue1, vawue2),
	TP_STWUCT__entwy(
		__fiewd(int, vawue1)
		__fiewd(int, vawue2)
	),
	TP_fast_assign(
		__entwy->vawue1	= vawue1;
		__entwy->vawue2	= vawue2;
	),
	TP_pwintk("%d %d", __entwy->vawue1, __entwy->vawue2)
);

#define DEFINE_OCFS2_INT_INT_EVENT(name)	\
DEFINE_EVENT(ocfs2__int_int, name,	\
	TP_PWOTO(int vaw1, int vaw2),	\
	TP_AWGS(vaw1, vaw2))

DECWAWE_EVENT_CWASS(ocfs2__uint_int,
	TP_PWOTO(unsigned int vawue1, int vawue2),
	TP_AWGS(vawue1, vawue2),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, vawue1)
		__fiewd(int, vawue2)
	),
	TP_fast_assign(
		__entwy->vawue1	= vawue1;
		__entwy->vawue2	= vawue2;
	),
	TP_pwintk("%u %d", __entwy->vawue1, __entwy->vawue2)
);

#define DEFINE_OCFS2_UINT_INT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uint_int, name,	\
	TP_PWOTO(unsigned int vaw1, int vaw2),	\
	TP_AWGS(vaw1, vaw2))

DECWAWE_EVENT_CWASS(ocfs2__uint_uint,
	TP_PWOTO(unsigned int vawue1, unsigned int vawue2),
	TP_AWGS(vawue1, vawue2),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, vawue1)
		__fiewd(unsigned int, vawue2)
	),
	TP_fast_assign(
		__entwy->vawue1 = vawue1;
		__entwy->vawue2 = vawue2;
	),
	TP_pwintk("%u %u", __entwy->vawue1, __entwy->vawue2)
);

#define DEFINE_OCFS2_UINT_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uint_uint, name,	\
	TP_PWOTO(unsigned int vaw1, unsigned int vaw2),	\
	TP_AWGS(vaw1, vaw2))

DECWAWE_EVENT_CWASS(ocfs2__uww_uint,
	TP_PWOTO(unsigned wong wong vawue1, unsigned int vawue2),
	TP_AWGS(vawue1, vawue2),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, vawue1)
		__fiewd(unsigned int, vawue2)
	),
	TP_fast_assign(
		__entwy->vawue1 = vawue1;
		__entwy->vawue2 = vawue2;
	),
	TP_pwintk("%wwu %u", __entwy->vawue1, __entwy->vawue2)
);

#define DEFINE_OCFS2_UWW_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uww_uint, name,	\
	TP_PWOTO(unsigned wong wong vaw1, unsigned int vaw2),	\
	TP_AWGS(vaw1, vaw2))

DECWAWE_EVENT_CWASS(ocfs2__uww_int,
	TP_PWOTO(unsigned wong wong vawue1, int vawue2),
	TP_AWGS(vawue1, vawue2),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, vawue1)
		__fiewd(int, vawue2)
	),
	TP_fast_assign(
		__entwy->vawue1	= vawue1;
		__entwy->vawue2	= vawue2;
	),
	TP_pwintk("%wwu %d", __entwy->vawue1, __entwy->vawue2)
);

#define DEFINE_OCFS2_UWW_INT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uww_int, name,	\
	TP_PWOTO(unsigned wong wong vaw1, int vaw2),	\
	TP_AWGS(vaw1, vaw2))

DECWAWE_EVENT_CWASS(ocfs2__uww_uww,
	TP_PWOTO(unsigned wong wong vawue1, unsigned wong wong vawue2),
	TP_AWGS(vawue1, vawue2),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, vawue1)
		__fiewd(unsigned wong wong, vawue2)
	),
	TP_fast_assign(
		__entwy->vawue1 = vawue1;
		__entwy->vawue2 = vawue2;
	),
	TP_pwintk("%wwu %wwu", __entwy->vawue1, __entwy->vawue2)
);

#define DEFINE_OCFS2_UWW_UWW_EVENT(name)	\
DEFINE_EVENT(ocfs2__uww_uww, name,	\
	TP_PWOTO(unsigned wong wong vaw1, unsigned wong wong vaw2),	\
	TP_AWGS(vaw1, vaw2))

DECWAWE_EVENT_CWASS(ocfs2__uww_uww_uint,
	TP_PWOTO(unsigned wong wong vawue1,
		 unsigned wong wong vawue2, unsigned int vawue3),
	TP_AWGS(vawue1, vawue2, vawue3),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, vawue1)
		__fiewd(unsigned wong wong, vawue2)
		__fiewd(unsigned int, vawue3)
	),
	TP_fast_assign(
		__entwy->vawue1 = vawue1;
		__entwy->vawue2 = vawue2;
		__entwy->vawue3 = vawue3;
	),
	TP_pwintk("%wwu %wwu %u",
		  __entwy->vawue1, __entwy->vawue2, __entwy->vawue3)
);

#define DEFINE_OCFS2_UWW_UWW_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uww_uww_uint, name,	\
	TP_PWOTO(unsigned wong wong vaw1,	\
		 unsigned wong wong vaw2, unsigned int vaw3),	\
	TP_AWGS(vaw1, vaw2, vaw3))

DECWAWE_EVENT_CWASS(ocfs2__uww_uint_uint,
	TP_PWOTO(unsigned wong wong vawue1,
		 unsigned int vawue2, unsigned int vawue3),
	TP_AWGS(vawue1, vawue2, vawue3),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, vawue1)
		__fiewd(unsigned int, vawue2)
		__fiewd(unsigned int, vawue3)
	),
	TP_fast_assign(
		__entwy->vawue1 = vawue1;
		__entwy->vawue2 = vawue2;
		__entwy->vawue3	= vawue3;
	),
	TP_pwintk("%wwu %u %u", __entwy->vawue1,
		  __entwy->vawue2, __entwy->vawue3)
);

#define DEFINE_OCFS2_UWW_UINT_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uww_uint_uint, name,	\
	TP_PWOTO(unsigned wong wong vaw1,	\
		 unsigned int vaw2, unsigned int vaw3),	\
	TP_AWGS(vaw1, vaw2, vaw3))

DECWAWE_EVENT_CWASS(ocfs2__uint_uint_uint,
	TP_PWOTO(unsigned int vawue1, unsigned int vawue2,
		 unsigned int vawue3),
	TP_AWGS(vawue1, vawue2, vawue3),
	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	vawue1		)
		__fiewd(	unsigned int,	vawue2		)
		__fiewd(	unsigned int,	vawue3		)
	),
	TP_fast_assign(
		__entwy->vawue1	= 	vawue1;
		__entwy->vawue2	= 	vawue2;
		__entwy->vawue3	= 	vawue3;
	),
	TP_pwintk("%u %u %u", __entwy->vawue1, __entwy->vawue2, __entwy->vawue3)
);

#define DEFINE_OCFS2_UINT_UINT_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uint_uint_uint, name,	\
	TP_PWOTO(unsigned int vawue1, unsigned int vawue2,	\
		 unsigned int vawue3),	\
	TP_AWGS(vawue1, vawue2, vawue3))

DECWAWE_EVENT_CWASS(ocfs2__uww_uww_uww,
	TP_PWOTO(unsigned wong wong vawue1,
		 unsigned wong wong vawue2, unsigned wong wong vawue3),
	TP_AWGS(vawue1, vawue2, vawue3),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, vawue1)
		__fiewd(unsigned wong wong, vawue2)
		__fiewd(unsigned wong wong, vawue3)
	),
	TP_fast_assign(
		__entwy->vawue1 = vawue1;
		__entwy->vawue2 = vawue2;
		__entwy->vawue3 = vawue3;
	),
	TP_pwintk("%wwu %wwu %wwu",
		  __entwy->vawue1, __entwy->vawue2, __entwy->vawue3)
);

#define DEFINE_OCFS2_UWW_UWW_UWW_EVENT(name)	\
DEFINE_EVENT(ocfs2__uww_uww_uww, name,	\
	TP_PWOTO(unsigned wong wong vawue1, unsigned wong wong vawue2,	\
		 unsigned wong wong vawue3),	\
	TP_AWGS(vawue1, vawue2, vawue3))

DECWAWE_EVENT_CWASS(ocfs2__uww_int_int_int,
	TP_PWOTO(unsigned wong wong uww, int vawue1, int vawue2, int vawue3),
	TP_AWGS(uww, vawue1, vawue2, vawue3),
	TP_STWUCT__entwy(
		__fiewd(	unsigned wong wong,	uww	)
		__fiewd(	int,	vawue1			)
		__fiewd(	int,	vawue2			)
		__fiewd(	int,	vawue3			)
	),
	TP_fast_assign(
		__entwy->uww		= uww;
		__entwy->vawue1		= vawue1;
		__entwy->vawue2		= vawue2;
		__entwy->vawue3		= vawue3;
	),
	TP_pwintk("%wwu %d %d %d",
		  __entwy->uww, __entwy->vawue1,
		  __entwy->vawue2, __entwy->vawue3)
);

#define DEFINE_OCFS2_UWW_INT_INT_INT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uww_int_int_int, name,	\
	TP_PWOTO(unsigned wong wong uww, int vawue1,	\
		 int vawue2, int vawue3),	\
	TP_AWGS(uww, vawue1, vawue2, vawue3))

DECWAWE_EVENT_CWASS(ocfs2__uww_uint_uint_uint,
	TP_PWOTO(unsigned wong wong uww, unsigned int vawue1,
		 unsigned int vawue2, unsigned int vawue3),
	TP_AWGS(uww, vawue1, vawue2, vawue3),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, uww)
		__fiewd(unsigned int, vawue1)
		__fiewd(unsigned int, vawue2)
		__fiewd(unsigned int, vawue3)
	),
	TP_fast_assign(
		__entwy->uww = uww;
		__entwy->vawue1 = vawue1;
		__entwy->vawue2	= vawue2;
		__entwy->vawue3	= vawue3;
	),
	TP_pwintk("%wwu %u %u %u",
		  __entwy->uww, __entwy->vawue1,
		  __entwy->vawue2, __entwy->vawue3)
);

#define DEFINE_OCFS2_UWW_UINT_UINT_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uww_uint_uint_uint, name,	\
	TP_PWOTO(unsigned wong wong uww, unsigned int vawue1,	\
		 unsigned int vawue2, unsigned int vawue3),	\
	TP_AWGS(uww, vawue1, vawue2, vawue3))

DECWAWE_EVENT_CWASS(ocfs2__uww_uww_uint_uint,
	TP_PWOTO(unsigned wong wong vawue1, unsigned wong wong vawue2,
		 unsigned int vawue3, unsigned int vawue4),
	TP_AWGS(vawue1, vawue2, vawue3, vawue4),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, vawue1)
		__fiewd(unsigned wong wong, vawue2)
		__fiewd(unsigned int, vawue3)
		__fiewd(unsigned int, vawue4)
	),
	TP_fast_assign(
		__entwy->vawue1 = vawue1;
		__entwy->vawue2 = vawue2;
		__entwy->vawue3 = vawue3;
		__entwy->vawue4 = vawue4;
	),
	TP_pwintk("%wwu %wwu %u %u",
		  __entwy->vawue1, __entwy->vawue2,
		  __entwy->vawue3, __entwy->vawue4)
);

#define DEFINE_OCFS2_UWW_UWW_UINT_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uww_uww_uint_uint, name,	\
	TP_PWOTO(unsigned wong wong uww, unsigned wong wong uww1,	\
		 unsigned int vawue2, unsigned int vawue3),	\
	TP_AWGS(uww, uww1, vawue2, vawue3))

/* Twace events fow fs/ocfs2/awwoc.c. */
DECWAWE_EVENT_CWASS(ocfs2__btwee_ops,
	TP_PWOTO(unsigned wong wong ownew,\
		 unsigned int vawue1, unsigned int vawue2),
	TP_AWGS(ownew, vawue1, vawue2),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ownew)
		__fiewd(unsigned int, vawue1)
		__fiewd(unsigned int, vawue2)
	),
	TP_fast_assign(
		__entwy->ownew = ownew;
		__entwy->vawue1 = vawue1;
		__entwy->vawue2	= vawue2;
	),
	TP_pwintk("%wwu %u %u",
		  __entwy->ownew, __entwy->vawue1, __entwy->vawue2)
);

#define DEFINE_OCFS2_BTWEE_EVENT(name)	\
DEFINE_EVENT(ocfs2__btwee_ops, name,	\
	TP_PWOTO(unsigned wong wong ownew,	\
		 unsigned int vawue1, unsigned int vawue2),	\
	TP_AWGS(ownew, vawue1, vawue2))

DEFINE_OCFS2_BTWEE_EVENT(ocfs2_adjust_wightmost_bwanch);

DEFINE_OCFS2_BTWEE_EVENT(ocfs2_wotate_twee_wight);

DEFINE_OCFS2_BTWEE_EVENT(ocfs2_append_wec_to_path);

DEFINE_OCFS2_BTWEE_EVENT(ocfs2_insewt_extent_stawt);

DEFINE_OCFS2_BTWEE_EVENT(ocfs2_add_cwustews_in_btwee);

DEFINE_OCFS2_INT_EVENT(ocfs2_num_fwee_extents);

DEFINE_OCFS2_INT_EVENT(ocfs2_compwete_edge_insewt);

TWACE_EVENT(ocfs2_gwow_twee,
	TP_PWOTO(unsigned wong wong ownew, int depth),
	TP_AWGS(ownew, depth),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ownew)
		__fiewd(int, depth)
	),
	TP_fast_assign(
		__entwy->ownew = ownew;
		__entwy->depth = depth;
	),
	TP_pwintk("%wwu %d", __entwy->ownew, __entwy->depth)
);

TWACE_EVENT(ocfs2_wotate_subtwee,
	TP_PWOTO(int subtwee_woot, unsigned wong wong bwkno,
		 int depth),
	TP_AWGS(subtwee_woot, bwkno, depth),
	TP_STWUCT__entwy(
		__fiewd(int, subtwee_woot)
		__fiewd(unsigned wong wong, bwkno)
		__fiewd(int, depth)
	),
	TP_fast_assign(
		__entwy->subtwee_woot = subtwee_woot;
		__entwy->bwkno = bwkno;
		__entwy->depth = depth;
	),
	TP_pwintk("%d %wwu %d", __entwy->subtwee_woot,
		  __entwy->bwkno, __entwy->depth)
);

TWACE_EVENT(ocfs2_insewt_extent,
	TP_PWOTO(unsigned int ins_appending, unsigned int ins_contig,
		 int ins_contig_index, int fwee_wecowds, int ins_twee_depth),
	TP_AWGS(ins_appending, ins_contig, ins_contig_index, fwee_wecowds,
		ins_twee_depth),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, ins_appending)
		__fiewd(unsigned int, ins_contig)
		__fiewd(int, ins_contig_index)
		__fiewd(int, fwee_wecowds)
		__fiewd(int, ins_twee_depth)
	),
	TP_fast_assign(
		__entwy->ins_appending = ins_appending;
		__entwy->ins_contig = ins_contig;
		__entwy->ins_contig_index = ins_contig_index;
		__entwy->fwee_wecowds = fwee_wecowds;
		__entwy->ins_twee_depth = ins_twee_depth;
	),
	TP_pwintk("%u %u %d %d %d",
		  __entwy->ins_appending, __entwy->ins_contig,
		  __entwy->ins_contig_index, __entwy->fwee_wecowds,
		  __entwy->ins_twee_depth)
);

TWACE_EVENT(ocfs2_spwit_extent,
	TP_PWOTO(int spwit_index, unsigned int c_contig_type,
		 unsigned int c_has_empty_extent,
		 unsigned int c_spwit_covews_wec),
	TP_AWGS(spwit_index, c_contig_type,
		c_has_empty_extent, c_spwit_covews_wec),
	TP_STWUCT__entwy(
		__fiewd(int, spwit_index)
		__fiewd(unsigned int, c_contig_type)
		__fiewd(unsigned int, c_has_empty_extent)
		__fiewd(unsigned int, c_spwit_covews_wec)
	),
	TP_fast_assign(
		__entwy->spwit_index = spwit_index;
		__entwy->c_contig_type = c_contig_type;
		__entwy->c_has_empty_extent = c_has_empty_extent;
		__entwy->c_spwit_covews_wec = c_spwit_covews_wec;
	),
	TP_pwintk("%d %u %u %u", __entwy->spwit_index, __entwy->c_contig_type,
		  __entwy->c_has_empty_extent, __entwy->c_spwit_covews_wec)
);

TWACE_EVENT(ocfs2_wemove_extent,
	TP_PWOTO(unsigned wong wong ownew, unsigned int cpos,
		 unsigned int wen, int index,
		 unsigned int e_cpos, unsigned int cwustews),
	TP_AWGS(ownew, cpos, wen, index, e_cpos, cwustews),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ownew)
		__fiewd(unsigned int, cpos)
		__fiewd(unsigned int, wen)
		__fiewd(int, index)
		__fiewd(unsigned int, e_cpos)
		__fiewd(unsigned int, cwustews)
	),
	TP_fast_assign(
		__entwy->ownew = ownew;
		__entwy->cpos = cpos;
		__entwy->wen = wen;
		__entwy->index = index;
		__entwy->e_cpos = e_cpos;
		__entwy->cwustews = cwustews;
	),
	TP_pwintk("%wwu %u %u %d %u %u",
		  __entwy->ownew, __entwy->cpos, __entwy->wen, __entwy->index,
		  __entwy->e_cpos, __entwy->cwustews)
);

TWACE_EVENT(ocfs2_commit_twuncate,
	TP_PWOTO(unsigned wong wong ino, unsigned int new_cpos,
		 unsigned int cwustews, unsigned int depth),
	TP_AWGS(ino, new_cpos, cwustews, depth),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned int, new_cpos)
		__fiewd(unsigned int, cwustews)
		__fiewd(unsigned int, depth)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->new_cpos = new_cpos;
		__entwy->cwustews = cwustews;
		__entwy->depth = depth;
	),
	TP_pwintk("%wwu %u %u %u",
		  __entwy->ino, __entwy->new_cpos,
		  __entwy->cwustews, __entwy->depth)
);

TWACE_EVENT(ocfs2_vawidate_extent_bwock,
	TP_PWOTO(unsigned wong wong bwkno),
	TP_AWGS(bwkno),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, bwkno)
	),
	TP_fast_assign(
		__entwy->bwkno = bwkno;
	),
	TP_pwintk("%wwu ", __entwy->bwkno)
);

TWACE_EVENT(ocfs2_wotate_weaf,
	TP_PWOTO(unsigned int insewt_cpos, int insewt_index,
		 int has_empty, int next_fwee,
		 unsigned int w_count),
	TP_AWGS(insewt_cpos, insewt_index, has_empty,
		next_fwee, w_count),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, insewt_cpos)
		__fiewd(int, insewt_index)
		__fiewd(int, has_empty)
		__fiewd(int, next_fwee)
		__fiewd(unsigned int, w_count)
	),
	TP_fast_assign(
		__entwy->insewt_cpos = insewt_cpos;
		__entwy->insewt_index = insewt_index;
		__entwy->has_empty = has_empty;
		__entwy->next_fwee = next_fwee;
		__entwy->w_count = w_count;
	),
	TP_pwintk("%u %d %d %d %u", __entwy->insewt_cpos,
		  __entwy->insewt_index, __entwy->has_empty,
		  __entwy->next_fwee, __entwy->w_count)
);

TWACE_EVENT(ocfs2_add_cwustews_in_btwee_wet,
	TP_PWOTO(int status, int weason, int eww),
	TP_AWGS(status, weason, eww),
	TP_STWUCT__entwy(
		__fiewd(int, status)
		__fiewd(int, weason)
		__fiewd(int, eww)
	),
	TP_fast_assign(
		__entwy->status = status;
		__entwy->weason = weason;
		__entwy->eww = eww;
	),
	TP_pwintk("%d %d %d", __entwy->status,
		  __entwy->weason, __entwy->eww)
);

TWACE_EVENT(ocfs2_mawk_extent_wwitten,
	TP_PWOTO(unsigned wong wong ownew, unsigned int cpos,
		 unsigned int wen, unsigned int phys),
	TP_AWGS(ownew, cpos, wen, phys),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ownew)
		__fiewd(unsigned int, cpos)
		__fiewd(unsigned int, wen)
		__fiewd(unsigned int, phys)
	),
	TP_fast_assign(
		__entwy->ownew = ownew;
		__entwy->cpos = cpos;
		__entwy->wen = wen;
		__entwy->phys = phys;
	),
	TP_pwintk("%wwu %u %u %u",
		  __entwy->ownew, __entwy->cpos,
		  __entwy->wen, __entwy->phys)
);

DECWAWE_EVENT_CWASS(ocfs2__twuncate_wog_ops,
	TP_PWOTO(unsigned wong wong bwkno, int index,
		 unsigned int stawt, unsigned int num),
	TP_AWGS(bwkno, index, stawt, num),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, bwkno)
		__fiewd(int, index)
		__fiewd(unsigned int, stawt)
		__fiewd(unsigned int, num)
	),
	TP_fast_assign(
		__entwy->bwkno = bwkno;
		__entwy->index = index;
		__entwy->stawt = stawt;
		__entwy->num = num;
	),
	TP_pwintk("%wwu %d %u %u",
		  __entwy->bwkno, __entwy->index,
		  __entwy->stawt, __entwy->num)
);

#define DEFINE_OCFS2_TWUNCATE_WOG_OPS_EVENT(name)	\
DEFINE_EVENT(ocfs2__twuncate_wog_ops, name,	\
	TP_PWOTO(unsigned wong wong bwkno, int index,	\
		 unsigned int stawt, unsigned int num),	\
	TP_AWGS(bwkno, index, stawt, num))

DEFINE_OCFS2_TWUNCATE_WOG_OPS_EVENT(ocfs2_twuncate_wog_append);

DEFINE_OCFS2_TWUNCATE_WOG_OPS_EVENT(ocfs2_wepway_twuncate_wecowds);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_fwush_twuncate_wog);

DEFINE_OCFS2_INT_EVENT(ocfs2_begin_twuncate_wog_wecovewy);

DEFINE_OCFS2_INT_EVENT(ocfs2_twuncate_wog_wecovewy_num);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_compwete_twuncate_wog_wecovewy);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_fwee_cached_bwocks);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_cache_cwustew_deawwoc);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_wun_deawwocs);

TWACE_EVENT(ocfs2_cache_bwock_deawwoc,
	TP_PWOTO(int type, int swot, unsigned wong wong subawwoc,
		 unsigned wong wong bwkno, unsigned int bit),
	TP_AWGS(type, swot, subawwoc, bwkno, bit),
	TP_STWUCT__entwy(
		__fiewd(int, type)
		__fiewd(int, swot)
		__fiewd(unsigned wong wong, subawwoc)
		__fiewd(unsigned wong wong, bwkno)
		__fiewd(unsigned int, bit)
	),
	TP_fast_assign(
		__entwy->type = type;
		__entwy->swot = swot;
		__entwy->subawwoc = subawwoc;
		__entwy->bwkno = bwkno;
		__entwy->bit = bit;
	),
	TP_pwintk("%d %d %wwu %wwu %u",
		  __entwy->type, __entwy->swot, __entwy->subawwoc,
		  __entwy->bwkno, __entwy->bit)
);

TWACE_EVENT(ocfs2_twim_extent,
	TP_PWOTO(stwuct supew_bwock *sb, unsigned wong wong bwk,
		 unsigned wong wong count),
	TP_AWGS(sb, bwk, count),
	TP_STWUCT__entwy(
		__fiewd(int, dev_majow)
		__fiewd(int, dev_minow)
		__fiewd(unsigned wong wong, bwk)
		__fiewd(__u64,	count)
	),
	TP_fast_assign(
		__entwy->dev_majow = MAJOW(sb->s_dev);
		__entwy->dev_minow = MINOW(sb->s_dev);
		__entwy->bwk = bwk;
		__entwy->count = count;
	),
	TP_pwintk("%d %d %wwu %wwu",
		  __entwy->dev_majow, __entwy->dev_minow,
		  __entwy->bwk, __entwy->count)
);

DEFINE_OCFS2_UWW_UINT_UINT_UINT_EVENT(ocfs2_twim_gwoup);

DEFINE_OCFS2_UWW_UWW_UWW_EVENT(ocfs2_twim_mainbm);

DEFINE_OCFS2_UWW_UWW_UWW_EVENT(ocfs2_twim_fs);

/* End of twace events fow fs/ocfs2/awwoc.c. */

/* Twace events fow fs/ocfs2/wocawawwoc.c. */

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_wa_set_sizes);

DEFINE_OCFS2_UWW_INT_INT_INT_EVENT(ocfs2_awwoc_shouwd_use_wocaw);

DEFINE_OCFS2_INT_EVENT(ocfs2_woad_wocaw_awwoc);

DEFINE_OCFS2_INT_EVENT(ocfs2_begin_wocaw_awwoc_wecovewy);

DEFINE_OCFS2_UWW_INT_INT_INT_EVENT(ocfs2_wesewve_wocaw_awwoc_bits);

DEFINE_OCFS2_UINT_EVENT(ocfs2_wocaw_awwoc_count_bits);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_wocaw_awwoc_find_cweaw_bits_seawch_bitmap);

DEFINE_OCFS2_UWW_INT_INT_INT_EVENT(ocfs2_wocaw_awwoc_find_cweaw_bits);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_sync_wocaw_to_main);

TWACE_EVENT(ocfs2_sync_wocaw_to_main_fwee,
	TP_PWOTO(int count, int bit, unsigned wong wong stawt_bwk,
		 unsigned wong wong bwkno),
	TP_AWGS(count, bit, stawt_bwk, bwkno),
	TP_STWUCT__entwy(
		__fiewd(int, count)
		__fiewd(int, bit)
		__fiewd(unsigned wong wong, stawt_bwk)
		__fiewd(unsigned wong wong, bwkno)
	),
	TP_fast_assign(
		__entwy->count = count;
		__entwy->bit = bit;
		__entwy->stawt_bwk = stawt_bwk;
		__entwy->bwkno = bwkno;
	),
	TP_pwintk("%d %d %wwu %wwu",
		  __entwy->count, __entwy->bit, __entwy->stawt_bwk,
		  __entwy->bwkno)
);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_wocaw_awwoc_new_window);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_wocaw_awwoc_new_window_wesuwt);

/* End of twace events fow fs/ocfs2/wocawawwoc.c. */

/* Twace events fow fs/ocfs2/wesize.c. */

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_update_wast_gwoup_and_inode);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_gwoup_extend);

DEFINE_OCFS2_UWW_UINT_UINT_UINT_EVENT(ocfs2_gwoup_add);

/* End of twace events fow fs/ocfs2/wesize.c. */

/* Twace events fow fs/ocfs2/subawwoc.c. */

DEFINE_OCFS2_UWW_EVENT(ocfs2_vawidate_gwoup_descwiptow);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_bwock_gwoup_awwoc_contig);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_bwock_gwoup_awwoc_discontig);

DEFINE_OCFS2_UWW_EVENT(ocfs2_bwock_gwoup_awwoc);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_wesewve_subawwoc_bits_nospc);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_wesewve_subawwoc_bits_no_new_gwoup);

DEFINE_OCFS2_UWW_EVENT(ocfs2_wesewve_new_inode_new_gwoup);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_bwock_gwoup_set_bits);

TWACE_EVENT(ocfs2_wewink_bwock_gwoup,
	TP_PWOTO(unsigned wong wong i_bwkno, unsigned int chain,
		 unsigned wong wong bg_bwkno,
		 unsigned wong wong pwev_bwkno),
	TP_AWGS(i_bwkno, chain, bg_bwkno, pwev_bwkno),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, i_bwkno)
		__fiewd(unsigned int, chain)
		__fiewd(unsigned wong wong, bg_bwkno)
		__fiewd(unsigned wong wong, pwev_bwkno)
	),
	TP_fast_assign(
		__entwy->i_bwkno = i_bwkno;
		__entwy->chain = chain;
		__entwy->bg_bwkno = bg_bwkno;
		__entwy->pwev_bwkno = pwev_bwkno;
	),
	TP_pwintk("%wwu %u %wwu %wwu",
		  __entwy->i_bwkno, __entwy->chain, __entwy->bg_bwkno,
		  __entwy->pwev_bwkno)
);

DEFINE_OCFS2_UWW_UINT_UINT_UINT_EVENT(ocfs2_cwustew_gwoup_seawch_wwong_max_bits);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_cwustew_gwoup_seawch_max_bwock);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_bwock_gwoup_seawch_max_bwock);

DEFINE_OCFS2_UWW_UINT_UINT_EVENT(ocfs2_seawch_chain_begin);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_seawch_chain_succ);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_seawch_chain_end);

DEFINE_OCFS2_UINT_EVENT(ocfs2_cwaim_subawwoc_bits);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_cwaim_new_inode_at_woc);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_bwock_gwoup_cweaw_bits);

TWACE_EVENT(ocfs2_fwee_subawwoc_bits,
	TP_PWOTO(unsigned wong wong inode, unsigned wong wong gwoup,
		 unsigned int stawt_bit, unsigned int count),
	TP_AWGS(inode, gwoup, stawt_bit, count),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, inode)
		__fiewd(unsigned wong wong, gwoup)
		__fiewd(unsigned int, stawt_bit)
		__fiewd(unsigned int, count)
	),
	TP_fast_assign(
		__entwy->inode = inode;
		__entwy->gwoup = gwoup;
		__entwy->stawt_bit = stawt_bit;
		__entwy->count = count;
	),
	TP_pwintk("%wwu %wwu %u %u", __entwy->inode, __entwy->gwoup,
		  __entwy->stawt_bit, __entwy->count)
);

TWACE_EVENT(ocfs2_fwee_cwustews,
	TP_PWOTO(unsigned wong wong bg_bwkno, unsigned wong wong stawt_bwk,
		 unsigned int stawt_bit, unsigned int count),
	TP_AWGS(bg_bwkno, stawt_bwk, stawt_bit, count),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, bg_bwkno)
		__fiewd(unsigned wong wong, stawt_bwk)
		__fiewd(unsigned int, stawt_bit)
		__fiewd(unsigned int, count)
	),
	TP_fast_assign(
		__entwy->bg_bwkno = bg_bwkno;
		__entwy->stawt_bwk = stawt_bwk;
		__entwy->stawt_bit = stawt_bit;
		__entwy->count = count;
	),
	TP_pwintk("%wwu %wwu %u %u", __entwy->bg_bwkno, __entwy->stawt_bwk,
		  __entwy->stawt_bit, __entwy->count)
);

DEFINE_OCFS2_UWW_EVENT(ocfs2_get_subawwoc_swot_bit);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_test_subawwoc_bit);

DEFINE_OCFS2_UWW_EVENT(ocfs2_test_inode_bit);

/* End of twace events fow fs/ocfs2/subawwoc.c. */

/* Twace events fow fs/ocfs2/wefcounttwee.c. */

DEFINE_OCFS2_UWW_EVENT(ocfs2_vawidate_wefcount_bwock);

DEFINE_OCFS2_UWW_EVENT(ocfs2_puwge_wefcount_twees);

DEFINE_OCFS2_UWW_EVENT(ocfs2_cweate_wefcount_twee);

DEFINE_OCFS2_UWW_EVENT(ocfs2_cweate_wefcount_twee_bwkno);

DEFINE_OCFS2_UWW_INT_INT_INT_EVENT(ocfs2_change_wefcount_wec);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_expand_inwine_wef_woot);

DEFINE_OCFS2_UWW_UINT_UINT_EVENT(ocfs2_divide_weaf_wefcount_bwock);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_new_weaf_wefcount_bwock);

DECWAWE_EVENT_CWASS(ocfs2__wefcount_twee_ops,
	TP_PWOTO(unsigned wong wong bwkno, int index,
		 unsigned wong wong cpos,
		 unsigned int cwustews, unsigned int wefcount),
	TP_AWGS(bwkno, index, cpos, cwustews, wefcount),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, bwkno)
		__fiewd(int, index)
		__fiewd(unsigned wong wong, cpos)
		__fiewd(unsigned int, cwustews)
		__fiewd(unsigned int, wefcount)
	),
	TP_fast_assign(
		__entwy->bwkno = bwkno;
		__entwy->index = index;
		__entwy->cpos = cpos;
		__entwy->cwustews = cwustews;
		__entwy->wefcount = wefcount;
	),
	TP_pwintk("%wwu %d %wwu %u %u", __entwy->bwkno, __entwy->index,
		  __entwy->cpos, __entwy->cwustews, __entwy->wefcount)
);

#define DEFINE_OCFS2_WEFCOUNT_TWEE_OPS_EVENT(name)	\
DEFINE_EVENT(ocfs2__wefcount_twee_ops, name,		\
	TP_PWOTO(unsigned wong wong bwkno, int index,	\
		 unsigned wong wong cpos,		\
		 unsigned int count, unsigned int wefcount),	\
	TP_AWGS(bwkno, index, cpos, count, wefcount))

DEFINE_OCFS2_WEFCOUNT_TWEE_OPS_EVENT(ocfs2_insewt_wefcount_wec);

TWACE_EVENT(ocfs2_spwit_wefcount_wec,
	TP_PWOTO(unsigned wong wong cpos,
		 unsigned int cwustews, unsigned int wefcount,
		 unsigned wong wong spwit_cpos,
		 unsigned int spwit_cwustews, unsigned int spwit_wefcount),
	TP_AWGS(cpos, cwustews, wefcount,
		spwit_cpos, spwit_cwustews, spwit_wefcount),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, cpos)
		__fiewd(unsigned int, cwustews)
		__fiewd(unsigned int, wefcount)
		__fiewd(unsigned wong wong, spwit_cpos)
		__fiewd(unsigned int, spwit_cwustews)
		__fiewd(unsigned int, spwit_wefcount)
	),
	TP_fast_assign(
		__entwy->cpos = cpos;
		__entwy->cwustews = cwustews;
		__entwy->wefcount = wefcount;
		__entwy->spwit_cpos = spwit_cpos;
		__entwy->spwit_cwustews = spwit_cwustews;
		__entwy->spwit_wefcount	= spwit_wefcount;
	),
	TP_pwintk("%wwu %u %u %wwu %u %u",
		  __entwy->cpos, __entwy->cwustews, __entwy->wefcount,
		  __entwy->spwit_cpos, __entwy->spwit_cwustews,
		  __entwy->spwit_wefcount)
);

DEFINE_OCFS2_WEFCOUNT_TWEE_OPS_EVENT(ocfs2_spwit_wefcount_wec_insewt);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_incwease_wefcount_begin);

DEFINE_OCFS2_UWW_UINT_UINT_EVENT(ocfs2_incwease_wefcount_change);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_incwease_wefcount_insewt);

DEFINE_OCFS2_UWW_UINT_UINT_EVENT(ocfs2_incwease_wefcount_spwit);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_wemove_wefcount_extent);

DEFINE_OCFS2_UWW_EVENT(ocfs2_westowe_wefcount_bwock);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_decwease_wefcount_wec);

TWACE_EVENT(ocfs2_decwease_wefcount,
	TP_PWOTO(unsigned wong wong ownew,
		 unsigned wong wong cpos,
		 unsigned int wen, int dewete),
	TP_AWGS(ownew, cpos, wen, dewete),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ownew)
		__fiewd(unsigned wong wong, cpos)
		__fiewd(unsigned int, wen)
		__fiewd(int, dewete)
	),
	TP_fast_assign(
		__entwy->ownew = ownew;
		__entwy->cpos = cpos;
		__entwy->wen = wen;
		__entwy->dewete = dewete;
	),
	TP_pwintk("%wwu %wwu %u %d",
		  __entwy->ownew, __entwy->cpos, __entwy->wen, __entwy->dewete)
);

DEFINE_OCFS2_UWW_UINT_UINT_UINT_EVENT(ocfs2_mawk_extent_wefcounted);

DEFINE_OCFS2_UWW_UINT_UINT_UINT_EVENT(ocfs2_cawc_wefcount_meta_cwedits);

TWACE_EVENT(ocfs2_cawc_wefcount_meta_cwedits_itewate,
	TP_PWOTO(int wecs_add, unsigned wong wong cpos,
		 unsigned int cwustews, unsigned wong wong w_cpos,
		 unsigned int w_cwustews, unsigned int wefcount, int index),
	TP_AWGS(wecs_add, cpos, cwustews, w_cpos, w_cwustews, wefcount, index),
	TP_STWUCT__entwy(
		__fiewd(int, wecs_add)
		__fiewd(unsigned wong wong, cpos)
		__fiewd(unsigned int, cwustews)
		__fiewd(unsigned wong wong, w_cpos)
		__fiewd(unsigned int, w_cwustews)
		__fiewd(unsigned int, wefcount)
		__fiewd(int, index)
	),
	TP_fast_assign(
		__entwy->wecs_add = wecs_add;
		__entwy->cpos = cpos;
		__entwy->cwustews = cwustews;
		__entwy->w_cpos = w_cpos;
		__entwy->w_cwustews = w_cwustews;
		__entwy->wefcount = wefcount;
		__entwy->index = index;
	),
	TP_pwintk("%d %wwu %u %wwu %u %u %d",
		  __entwy->wecs_add, __entwy->cpos, __entwy->cwustews,
		  __entwy->w_cpos, __entwy->w_cwustews,
		  __entwy->wefcount, __entwy->index)
);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_add_wefcount_fwag);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_pwepawe_wefcount_change_fow_dew);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_wock_wefcount_awwocatows);

DEFINE_OCFS2_UWW_UINT_UINT_UINT_EVENT(ocfs2_dupwicate_cwustews_by_page);

DEFINE_OCFS2_UWW_UINT_UINT_UINT_EVENT(ocfs2_dupwicate_cwustews_by_jbd);

TWACE_EVENT(ocfs2_cweaw_ext_wefcount,
	TP_PWOTO(unsigned wong wong ino, unsigned int cpos,
		 unsigned int wen, unsigned int p_cwustew,
		 unsigned int ext_fwags),
	TP_AWGS(ino, cpos, wen, p_cwustew, ext_fwags),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned int, cpos)
		__fiewd(unsigned int, wen)
		__fiewd(unsigned int, p_cwustew)
		__fiewd(unsigned int, ext_fwags)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->cpos = cpos;
		__entwy->wen = wen;
		__entwy->p_cwustew = p_cwustew;
		__entwy->ext_fwags = ext_fwags;
	),
	TP_pwintk("%wwu %u %u %u %u",
		  __entwy->ino, __entwy->cpos, __entwy->wen,
		  __entwy->p_cwustew, __entwy->ext_fwags)
);

TWACE_EVENT(ocfs2_wepwace_cwustews,
	TP_PWOTO(unsigned wong wong ino, unsigned int cpos,
		 unsigned int owd, unsigned int new, unsigned int wen,
		 unsigned int ext_fwags),
	TP_AWGS(ino, cpos, owd, new, wen, ext_fwags),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned int, cpos)
		__fiewd(unsigned int, owd)
		__fiewd(unsigned int, new)
		__fiewd(unsigned int, wen)
		__fiewd(unsigned int, ext_fwags)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->cpos = cpos;
		__entwy->owd = owd;
		__entwy->new = new;
		__entwy->wen = wen;
		__entwy->ext_fwags = ext_fwags;
	),
	TP_pwintk("%wwu %u %u %u %u %u",
		  __entwy->ino, __entwy->cpos, __entwy->owd, __entwy->new,
		  __entwy->wen, __entwy->ext_fwags)
);

DEFINE_OCFS2_UWW_UINT_UINT_UINT_EVENT(ocfs2_make_cwustews_wwitabwe);

TWACE_EVENT(ocfs2_wefcount_cow_hunk,
	TP_PWOTO(unsigned wong wong ino, unsigned int cpos,
		 unsigned int wwite_wen, unsigned int max_cpos,
		 unsigned int cow_stawt, unsigned int cow_wen),
	TP_AWGS(ino, cpos, wwite_wen, max_cpos, cow_stawt, cow_wen),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned int, cpos)
		__fiewd(unsigned int, wwite_wen)
		__fiewd(unsigned int, max_cpos)
		__fiewd(unsigned int, cow_stawt)
		__fiewd(unsigned int, cow_wen)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->cpos = cpos;
		__entwy->wwite_wen = wwite_wen;
		__entwy->max_cpos = max_cpos;
		__entwy->cow_stawt = cow_stawt;
		__entwy->cow_wen = cow_wen;
	),
	TP_pwintk("%wwu %u %u %u %u %u",
		  __entwy->ino, __entwy->cpos, __entwy->wwite_wen,
		  __entwy->max_cpos, __entwy->cow_stawt, __entwy->cow_wen)
);

/* End of twace events fow fs/ocfs2/wefcounttwee.c. */

/* Twace events fow fs/ocfs2/aops.c. */

DECWAWE_EVENT_CWASS(ocfs2__get_bwock,
	TP_PWOTO(unsigned wong wong ino, unsigned wong wong ibwock,
		 void *bh_wesuwt, int cweate),
	TP_AWGS(ino, ibwock, bh_wesuwt, cweate),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned wong wong, ibwock)
		__fiewd(void *, bh_wesuwt)
		__fiewd(int, cweate)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->ibwock = ibwock;
		__entwy->bh_wesuwt = bh_wesuwt;
		__entwy->cweate = cweate;
	),
	TP_pwintk("%wwu %wwu %p %d",
		  __entwy->ino, __entwy->ibwock,
		  __entwy->bh_wesuwt, __entwy->cweate)
);

#define DEFINE_OCFS2_GET_BWOCK_EVENT(name)	\
DEFINE_EVENT(ocfs2__get_bwock, name,	\
	TP_PWOTO(unsigned wong wong ino, unsigned wong wong ibwock,	\
		 void *bh_wesuwt, int cweate),	\
	TP_AWGS(ino, ibwock, bh_wesuwt, cweate))

DEFINE_OCFS2_GET_BWOCK_EVENT(ocfs2_symwink_get_bwock);

DEFINE_OCFS2_GET_BWOCK_EVENT(ocfs2_get_bwock);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_get_bwock_end);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_weadpage);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_bmap);

TWACE_EVENT(ocfs2_twy_to_wwite_inwine_data,
	TP_PWOTO(unsigned wong wong ino, unsigned int wen,
		 unsigned wong wong pos, unsigned int fwags),
	TP_AWGS(ino, wen, pos, fwags),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned int, wen)
		__fiewd(unsigned wong wong, pos)
		__fiewd(unsigned int, fwags)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->wen = wen;
		__entwy->pos = pos;
		__entwy->fwags = fwags;
	),
	TP_pwintk("%wwu %u %wwu 0x%x",
		  __entwy->ino, __entwy->wen, __entwy->pos, __entwy->fwags)
);

TWACE_EVENT(ocfs2_wwite_begin_nowock,
	TP_PWOTO(unsigned wong wong ino,
		 wong wong i_size, unsigned int i_cwustews,
		 unsigned wong wong pos, unsigned int wen,
		 unsigned int fwags, void *page,
		 unsigned int cwustews, unsigned int extents_to_spwit),
	TP_AWGS(ino, i_size, i_cwustews, pos, wen, fwags,
		page, cwustews, extents_to_spwit),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(wong wong, i_size)
		__fiewd(unsigned int, i_cwustews)
		__fiewd(unsigned wong wong, pos)
		__fiewd(unsigned int, wen)
		__fiewd(unsigned int, fwags)
		__fiewd(void *, page)
		__fiewd(unsigned int, cwustews)
		__fiewd(unsigned int, extents_to_spwit)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->i_size = i_size;
		__entwy->i_cwustews = i_cwustews;
		__entwy->pos = pos;
		__entwy->wen = wen;
		__entwy->fwags = fwags;
		__entwy->page = page;
		__entwy->cwustews = cwustews;
		__entwy->extents_to_spwit = extents_to_spwit;
	),
	TP_pwintk("%wwu %wwd %u %wwu %u %u %p %u %u",
		  __entwy->ino, __entwy->i_size, __entwy->i_cwustews,
		  __entwy->pos, __entwy->wen,
		  __entwy->fwags, __entwy->page, __entwy->cwustews,
		  __entwy->extents_to_spwit)
);

TWACE_EVENT(ocfs2_wwite_end_inwine,
	TP_PWOTO(unsigned wong wong ino,
		 unsigned wong wong pos, unsigned int copied,
		 unsigned int id_count, unsigned int featuwes),
	TP_AWGS(ino, pos, copied, id_count, featuwes),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned wong wong, pos)
		__fiewd(unsigned int, copied)
		__fiewd(unsigned int, id_count)
		__fiewd(unsigned int, featuwes)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->pos = pos;
		__entwy->copied = copied;
		__entwy->id_count = id_count;
		__entwy->featuwes = featuwes;
	),
	TP_pwintk("%wwu %wwu %u %u %u",
		  __entwy->ino, __entwy->pos, __entwy->copied,
		  __entwy->id_count, __entwy->featuwes)
);

/* End of twace events fow fs/ocfs2/aops.c. */

/* Twace events fow fs/ocfs2/mmap.c. */

TWACE_EVENT(ocfs2_fauwt,
	TP_PWOTO(unsigned wong wong ino,
		 void *awea, void *page, unsigned wong pgoff),
	TP_AWGS(ino, awea, page, pgoff),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(void *, awea)
		__fiewd(void *, page)
		__fiewd(unsigned wong, pgoff)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->awea = awea;
		__entwy->page = page;
		__entwy->pgoff = pgoff;
	),
	TP_pwintk("%wwu %p %p %wu",
		  __entwy->ino, __entwy->awea, __entwy->page, __entwy->pgoff)
);

/* End of twace events fow fs/ocfs2/mmap.c. */

/* Twace events fow fs/ocfs2/fiwe.c. */

DECWAWE_EVENT_CWASS(ocfs2__fiwe_ops,
	TP_PWOTO(void *inode, void *fiwe, void *dentwy,
		 unsigned wong wong ino,
		 unsigned int d_wen, const unsigned chaw *d_name,
		 unsigned wong wong pawa),
	TP_AWGS(inode, fiwe, dentwy, ino, d_wen, d_name, pawa),
	TP_STWUCT__entwy(
		__fiewd(void *, inode)
		__fiewd(void *, fiwe)
		__fiewd(void *, dentwy)
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned int, d_wen)
		__stwing(d_name, d_name)
		__fiewd(unsigned wong wong, pawa)
	),
	TP_fast_assign(
		__entwy->inode = inode;
		__entwy->fiwe = fiwe;
		__entwy->dentwy = dentwy;
		__entwy->ino = ino;
		__entwy->d_wen = d_wen;
		__assign_stw(d_name, d_name);
		__entwy->pawa = pawa;
	),
	TP_pwintk("%p %p %p %wwu %wwu %.*s", __entwy->inode, __entwy->fiwe,
		  __entwy->dentwy, __entwy->ino, __entwy->pawa,
		  __entwy->d_wen, __get_stw(d_name))
);

#define DEFINE_OCFS2_FIWE_OPS(name)				\
DEFINE_EVENT(ocfs2__fiwe_ops, name,				\
TP_PWOTO(void *inode, void *fiwe, void *dentwy,			\
	 unsigned wong wong ino,				\
	 unsigned int d_wen, const unsigned chaw *d_name,	\
	 unsigned wong wong mode),				\
	TP_AWGS(inode, fiwe, dentwy, ino, d_wen, d_name, mode))

DEFINE_OCFS2_FIWE_OPS(ocfs2_fiwe_open);

DEFINE_OCFS2_FIWE_OPS(ocfs2_fiwe_wewease);

DEFINE_OCFS2_FIWE_OPS(ocfs2_sync_fiwe);

DEFINE_OCFS2_FIWE_OPS(ocfs2_fiwe_wwite_itew);

DEFINE_OCFS2_FIWE_OPS(ocfs2_fiwe_wead_itew);

DEFINE_OCFS2_FIWE_OPS(ocfs2_fiwe_spwice_wead);

DEFINE_OCFS2_UWW_UWW_UWW_EVENT(ocfs2_twuncate_fiwe);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_twuncate_fiwe_ewwow);

TWACE_EVENT(ocfs2_extend_awwocation,
	TP_PWOTO(unsigned wong wong ip_bwkno, unsigned wong wong size,
		 unsigned int cwustews, unsigned int cwustews_to_add,
		 int why, int westawt_func),
	TP_AWGS(ip_bwkno, size, cwustews, cwustews_to_add, why, westawt_func),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ip_bwkno)
		__fiewd(unsigned wong wong, size)
		__fiewd(unsigned int, cwustews)
		__fiewd(unsigned int, cwustews_to_add)
		__fiewd(int, why)
		__fiewd(int, westawt_func)
	),
	TP_fast_assign(
		__entwy->ip_bwkno = ip_bwkno;
		__entwy->size = size;
		__entwy->cwustews = cwustews;
		__entwy->cwustews_to_add = cwustews_to_add;
		__entwy->why = why;
		__entwy->westawt_func = westawt_func;
	),
	TP_pwintk("%wwu %wwu %u %u %d %d",
		  __entwy->ip_bwkno, __entwy->size, __entwy->cwustews,
		  __entwy->cwustews_to_add, __entwy->why, __entwy->westawt_func)
);

TWACE_EVENT(ocfs2_extend_awwocation_end,
	TP_PWOTO(unsigned wong wong ino,
		 unsigned int di_cwustews, unsigned wong wong di_size,
		 unsigned int ip_cwustews, unsigned wong wong i_size),
	TP_AWGS(ino, di_cwustews, di_size, ip_cwustews, i_size),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned int, di_cwustews)
		__fiewd(unsigned wong wong, di_size)
		__fiewd(unsigned int, ip_cwustews)
		__fiewd(unsigned wong wong, i_size)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->di_cwustews = di_cwustews;
		__entwy->di_size = di_size;
		__entwy->ip_cwustews = ip_cwustews;
		__entwy->i_size = i_size;
	),
	TP_pwintk("%wwu %u %wwu %u %wwu", __entwy->ino, __entwy->di_cwustews,
		  __entwy->di_size, __entwy->ip_cwustews, __entwy->i_size)
);

TWACE_EVENT(ocfs2_wwite_zewo_page,
	TP_PWOTO(unsigned wong wong ino,
		 unsigned wong wong abs_fwom, unsigned wong wong abs_to,
		 unsigned wong index, unsigned int zewo_fwom,
		 unsigned int zewo_to),
	TP_AWGS(ino, abs_fwom, abs_to, index, zewo_fwom, zewo_to),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned wong wong, abs_fwom)
		__fiewd(unsigned wong wong, abs_to)
		__fiewd(unsigned wong, index)
		__fiewd(unsigned int, zewo_fwom)
		__fiewd(unsigned int, zewo_to)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->abs_fwom = abs_fwom;
		__entwy->abs_to = abs_to;
		__entwy->index = index;
		__entwy->zewo_fwom = zewo_fwom;
		__entwy->zewo_to = zewo_to;
	),
	TP_pwintk("%wwu %wwu %wwu %wu %u %u", __entwy->ino,
		  __entwy->abs_fwom, __entwy->abs_to,
		  __entwy->index, __entwy->zewo_fwom, __entwy->zewo_to)
);

DEFINE_OCFS2_UWW_UWW_UWW_EVENT(ocfs2_zewo_extend_wange);

DEFINE_OCFS2_UWW_UWW_UWW_EVENT(ocfs2_zewo_extend);

TWACE_EVENT(ocfs2_setattw,
	TP_PWOTO(void *inode, void *dentwy,
		 unsigned wong wong ino,
		 unsigned int d_wen, const unsigned chaw *d_name,
		 unsigned int ia_vawid, unsigned int ia_mode,
		 unsigned int ia_uid, unsigned int ia_gid),
	TP_AWGS(inode, dentwy, ino, d_wen, d_name,
		ia_vawid, ia_mode, ia_uid, ia_gid),
	TP_STWUCT__entwy(
		__fiewd(void *, inode)
		__fiewd(void *, dentwy)
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned int, d_wen)
		__stwing(d_name, d_name)
		__fiewd(unsigned int, ia_vawid)
		__fiewd(unsigned int, ia_mode)
		__fiewd(unsigned int, ia_uid)
		__fiewd(unsigned int, ia_gid)
	),
	TP_fast_assign(
		__entwy->inode = inode;
		__entwy->dentwy = dentwy;
		__entwy->ino = ino;
		__entwy->d_wen = d_wen;
		__assign_stw(d_name, d_name);
		__entwy->ia_vawid = ia_vawid;
		__entwy->ia_mode = ia_mode;
		__entwy->ia_uid = ia_uid;
		__entwy->ia_gid = ia_gid;
	),
	TP_pwintk("%p %p %wwu %.*s %u %u %u %u", __entwy->inode,
		  __entwy->dentwy, __entwy->ino, __entwy->d_wen,
		  __get_stw(d_name), __entwy->ia_vawid, __entwy->ia_mode,
		  __entwy->ia_uid, __entwy->ia_gid)
);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_wwite_wemove_suid);

DEFINE_OCFS2_UWW_UWW_UWW_EVENT(ocfs2_zewo_pawtiaw_cwustews);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_zewo_pawtiaw_cwustews_wange1);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_zewo_pawtiaw_cwustews_wange2);

DEFINE_OCFS2_UWW_UWW_UWW_EVENT(ocfs2_wemove_inode_wange);

TWACE_EVENT(ocfs2_pwepawe_inode_fow_wwite,
	TP_PWOTO(unsigned wong wong ino, unsigned wong wong saved_pos,
		 unsigned wong count, int wait),
	TP_AWGS(ino, saved_pos, count, wait),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned wong wong, saved_pos)
		__fiewd(unsigned wong, count)
		__fiewd(int, wait)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->saved_pos = saved_pos;
		__entwy->count = count;
		__entwy->wait = wait;
	),
	TP_pwintk("%wwu %wwu %wu %d", __entwy->ino,
		  __entwy->saved_pos, __entwy->count, __entwy->wait)
);

DEFINE_OCFS2_INT_EVENT(genewic_fiwe_wead_itew_wet);
DEFINE_OCFS2_INT_EVENT(fiwemap_spwice_wead_wet);

/* End of twace events fow fs/ocfs2/fiwe.c. */

/* Twace events fow fs/ocfs2/inode.c. */

TWACE_EVENT(ocfs2_iget_begin,
	TP_PWOTO(unsigned wong wong ino, unsigned int fwags, int sysfiwe_type),
	TP_AWGS(ino, fwags, sysfiwe_type),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned int, fwags)
		__fiewd(int, sysfiwe_type)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->fwags = fwags;
		__entwy->sysfiwe_type = sysfiwe_type;
	),
	TP_pwintk("%wwu %u %d", __entwy->ino,
		  __entwy->fwags, __entwy->sysfiwe_type)
);

DEFINE_OCFS2_UWW_EVENT(ocfs2_iget5_wocked);

TWACE_EVENT(ocfs2_iget_end,
	TP_PWOTO(void *inode, unsigned wong wong ino),
	TP_AWGS(inode, ino),
	TP_STWUCT__entwy(
		__fiewd(void *, inode)
		__fiewd(unsigned wong wong, ino)
	),
	TP_fast_assign(
		__entwy->inode = inode;
		__entwy->ino = ino;
	),
	TP_pwintk("%p %wwu", __entwy->inode, __entwy->ino)
);

TWACE_EVENT(ocfs2_find_actow,
	TP_PWOTO(void *inode, unsigned wong wong ino,
		 void *awgs,  unsigned wong wong fi_bwkno),
	TP_AWGS(inode, ino, awgs, fi_bwkno),
	TP_STWUCT__entwy(
		__fiewd(void *, inode)
		__fiewd(unsigned wong wong, ino)
		__fiewd(void *, awgs)
		__fiewd(unsigned wong wong, fi_bwkno)
	),
	TP_fast_assign(
		__entwy->inode = inode;
		__entwy->ino = ino;
		__entwy->awgs = awgs;
		__entwy->fi_bwkno = fi_bwkno;
	),
	TP_pwintk("%p %wwu %p %wwu", __entwy->inode, __entwy->ino,
		  __entwy->awgs, __entwy->fi_bwkno)
);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_popuwate_inode);

DEFINE_OCFS2_UWW_INT_EVENT(ocfs2_wead_wocked_inode);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_check_owphan_wecovewy_state);

DEFINE_OCFS2_UWW_EVENT(ocfs2_vawidate_inode_bwock);
DEFINE_OCFS2_UWW_EVENT(ocfs2_fiwecheck_vawidate_inode_bwock);
DEFINE_OCFS2_UWW_EVENT(ocfs2_fiwecheck_wepaiw_inode_bwock);

TWACE_EVENT(ocfs2_inode_is_vawid_to_dewete,
	TP_PWOTO(void *task, void *dc_task, unsigned wong wong ino,
		 unsigned int fwags),
	TP_AWGS(task, dc_task, ino, fwags),
	TP_STWUCT__entwy(
		__fiewd(void *, task)
		__fiewd(void *, dc_task)
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned int, fwags)
	),
	TP_fast_assign(
		__entwy->task = task;
		__entwy->dc_task = dc_task;
		__entwy->ino = ino;
		__entwy->fwags = fwags;
	),
	TP_pwintk("%p %p %wwu %u", __entwy->task, __entwy->dc_task,
		  __entwy->ino, __entwy->fwags)
);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_quewy_inode_wipe_begin);

DEFINE_OCFS2_UINT_EVENT(ocfs2_quewy_inode_wipe_succ);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_quewy_inode_wipe_end);

DEFINE_OCFS2_UWW_INT_EVENT(ocfs2_cweanup_dewete_inode);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_dewete_inode);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_cweaw_inode);

DEFINE_OCFS2_UWW_UINT_UINT_EVENT(ocfs2_dwop_inode);

TWACE_EVENT(ocfs2_inode_wevawidate,
	TP_PWOTO(void *inode, unsigned wong wong ino,
		 unsigned int fwags),
	TP_AWGS(inode, ino, fwags),
	TP_STWUCT__entwy(
		__fiewd(void *, inode)
		__fiewd(unsigned wong wong, ino)
		__fiewd(unsigned int, fwags)
	),
	TP_fast_assign(
		__entwy->inode = inode;
		__entwy->ino = ino;
		__entwy->fwags = fwags;
	),
	TP_pwintk("%p %wwu %u", __entwy->inode, __entwy->ino, __entwy->fwags)
);

DEFINE_OCFS2_UWW_EVENT(ocfs2_mawk_inode_diwty);

/* End of twace events fow fs/ocfs2/inode.c. */

/* Twace events fow fs/ocfs2/extent_map.c. */

TWACE_EVENT(ocfs2_wead_viwt_bwocks,
	TP_PWOTO(void *inode, unsigned wong wong vbwock, int nw,
		 void *bhs, unsigned int fwags, void *vawidate),
	TP_AWGS(inode, vbwock, nw, bhs, fwags, vawidate),
	TP_STWUCT__entwy(
		__fiewd(void *, inode)
		__fiewd(unsigned wong wong, vbwock)
		__fiewd(int, nw)
		__fiewd(void *, bhs)
		__fiewd(unsigned int, fwags)
		__fiewd(void *, vawidate)
	),
	TP_fast_assign(
		__entwy->inode = inode;
		__entwy->vbwock = vbwock;
		__entwy->nw = nw;
		__entwy->bhs = bhs;
		__entwy->fwags = fwags;
		__entwy->vawidate = vawidate;
	),
	TP_pwintk("%p %wwu %d %p %x %p", __entwy->inode, __entwy->vbwock,
		  __entwy->nw, __entwy->bhs, __entwy->fwags, __entwy->vawidate)
);

/* End of twace events fow fs/ocfs2/extent_map.c. */

/* Twace events fow fs/ocfs2/swot_map.c. */

DEFINE_OCFS2_UINT_EVENT(ocfs2_wefwesh_swot_info);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_map_swot_buffews);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_map_swot_buffews_bwock);

DEFINE_OCFS2_INT_EVENT(ocfs2_find_swot);

/* End of twace events fow fs/ocfs2/swot_map.c. */

/* Twace events fow fs/ocfs2/heawtbeat.c. */

DEFINE_OCFS2_INT_EVENT(ocfs2_do_node_down);

/* End of twace events fow fs/ocfs2/heawtbeat.c. */

/* Twace events fow fs/ocfs2/supew.c. */

TWACE_EVENT(ocfs2_wemount,
	TP_PWOTO(unsigned wong s_fwags, unsigned wong osb_fwags, int fwags),
	TP_AWGS(s_fwags, osb_fwags, fwags),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong, s_fwags)
		__fiewd(unsigned wong, osb_fwags)
		__fiewd(int, fwags)
	),
	TP_fast_assign(
		__entwy->s_fwags = s_fwags;
		__entwy->osb_fwags = osb_fwags;
		__entwy->fwags = fwags;
	),
	TP_pwintk("%wu %wu %d", __entwy->s_fwags,
		  __entwy->osb_fwags, __entwy->fwags)
);

TWACE_EVENT(ocfs2_fiww_supew,
	TP_PWOTO(void *sb, void *data, int siwent),
	TP_AWGS(sb, data, siwent),
	TP_STWUCT__entwy(
		__fiewd(void *, sb)
		__fiewd(void *, data)
		__fiewd(int, siwent)
	),
	TP_fast_assign(
		__entwy->sb = sb;
		__entwy->data = data;
		__entwy->siwent = siwent;
	),
	TP_pwintk("%p %p %d", __entwy->sb,
		  __entwy->data, __entwy->siwent)
);

TWACE_EVENT(ocfs2_pawse_options,
	TP_PWOTO(int is_wemount, chaw *options),
	TP_AWGS(is_wemount, options),
	TP_STWUCT__entwy(
		__fiewd(int, is_wemount)
		__stwing(options, options)
	),
	TP_fast_assign(
		__entwy->is_wemount = is_wemount;
		__assign_stw(options, options);
	),
	TP_pwintk("%d %s", __entwy->is_wemount, __get_stw(options))
);

DEFINE_OCFS2_POINTEW_EVENT(ocfs2_put_supew);

TWACE_EVENT(ocfs2_statfs,
	TP_PWOTO(void *sb, void *buf),
	TP_AWGS(sb, buf),
	TP_STWUCT__entwy(
		__fiewd(void *, sb)
		__fiewd(void *, buf)
	),
	TP_fast_assign(
		__entwy->sb = sb;
		__entwy->buf = buf;
	),
	TP_pwintk("%p %p", __entwy->sb, __entwy->buf)
);

DEFINE_OCFS2_POINTEW_EVENT(ocfs2_dismount_vowume);

TWACE_EVENT(ocfs2_initiawize_supew,
	TP_PWOTO(chaw *wabew, chaw *uuid_stw, unsigned wong wong woot_diw,
		 unsigned wong wong system_diw, int cwustew_bits),
	TP_AWGS(wabew, uuid_stw, woot_diw, system_diw, cwustew_bits),
	TP_STWUCT__entwy(
		__stwing(wabew, wabew)
		__stwing(uuid_stw, uuid_stw)
		__fiewd(unsigned wong wong, woot_diw)
		__fiewd(unsigned wong wong, system_diw)
		__fiewd(int, cwustew_bits)
	),
	TP_fast_assign(
		__assign_stw(wabew, wabew);
		__assign_stw(uuid_stw, uuid_stw);
		__entwy->woot_diw = woot_diw;
		__entwy->system_diw = system_diw;
		__entwy->cwustew_bits = cwustew_bits;
	),
	TP_pwintk("%s %s %wwu %wwu %d", __get_stw(wabew), __get_stw(uuid_stw),
		  __entwy->woot_diw, __entwy->system_diw, __entwy->cwustew_bits)
);

/* End of twace events fow fs/ocfs2/supew.c. */

/* Twace events fow fs/ocfs2/xattw.c. */

DEFINE_OCFS2_UWW_EVENT(ocfs2_vawidate_xattw_bwock);

DEFINE_OCFS2_UINT_EVENT(ocfs2_xattw_extend_awwocation);

TWACE_EVENT(ocfs2_init_xattw_set_ctxt,
	TP_PWOTO(const chaw *name, int meta, int cwustews, int cwedits),
	TP_AWGS(name, meta, cwustews, cwedits),
	TP_STWUCT__entwy(
		__stwing(name, name)
		__fiewd(int, meta)
		__fiewd(int, cwustews)
		__fiewd(int, cwedits)
	),
	TP_fast_assign(
		__assign_stw(name, name);
		__entwy->meta = meta;
		__entwy->cwustews = cwustews;
		__entwy->cwedits = cwedits;
	),
	TP_pwintk("%s %d %d %d", __get_stw(name), __entwy->meta,
		  __entwy->cwustews, __entwy->cwedits)
);

DECWAWE_EVENT_CWASS(ocfs2__xattw_find,
	TP_PWOTO(unsigned wong wong ino, const chaw *name, int name_index,
		 unsigned int hash, unsigned wong wong wocation,
		 int xe_index),
	TP_AWGS(ino, name, name_index, hash, wocation, xe_index),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__stwing(name, name)
		__fiewd(int, name_index)
		__fiewd(unsigned int, hash)
		__fiewd(unsigned wong wong, wocation)
		__fiewd(int, xe_index)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__assign_stw(name, name);
		__entwy->name_index = name_index;
		__entwy->hash = hash;
		__entwy->wocation = wocation;
		__entwy->xe_index = xe_index;
	),
	TP_pwintk("%wwu %s %d %u %wwu %d", __entwy->ino, __get_stw(name),
		  __entwy->name_index, __entwy->hash, __entwy->wocation,
		  __entwy->xe_index)
);

#define DEFINE_OCFS2_XATTW_FIND_EVENT(name)					\
DEFINE_EVENT(ocfs2__xattw_find, name,					\
TP_PWOTO(unsigned wong wong ino, const chaw *name, int name_index,	\
	 unsigned int hash, unsigned wong wong bucket,			\
	 int xe_index),							\
	TP_AWGS(ino, name, name_index, hash, bucket, xe_index))

DEFINE_OCFS2_XATTW_FIND_EVENT(ocfs2_xattw_bucket_find);

DEFINE_OCFS2_XATTW_FIND_EVENT(ocfs2_xattw_index_bwock_find);

DEFINE_OCFS2_XATTW_FIND_EVENT(ocfs2_xattw_index_bwock_find_wec);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_itewate_xattw_buckets);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_itewate_xattw_bucket);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_cp_xattw_bwock_to_bucket_begin);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_cp_xattw_bwock_to_bucket_end);

DEFINE_OCFS2_UWW_EVENT(ocfs2_xattw_cweate_index_bwock_begin);

DEFINE_OCFS2_UWW_EVENT(ocfs2_xattw_cweate_index_bwock);

DEFINE_OCFS2_UWW_UINT_UINT_UINT_EVENT(ocfs2_defwag_xattw_bucket);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_mv_xattw_bucket_cwoss_cwustew);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_divide_xattw_bucket_begin);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_divide_xattw_bucket_move);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_cp_xattw_bucket);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_mv_xattw_buckets);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_adjust_xattw_cwoss_cwustew);

DEFINE_OCFS2_UWW_UWW_UINT_UINT_EVENT(ocfs2_add_new_xattw_cwustew_begin);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_add_new_xattw_cwustew);

DEFINE_OCFS2_UWW_UINT_UINT_EVENT(ocfs2_add_new_xattw_cwustew_insewt);

DEFINE_OCFS2_UWW_UWW_UINT_UINT_EVENT(ocfs2_extend_xattw_bucket);

DEFINE_OCFS2_UWW_EVENT(ocfs2_add_new_xattw_bucket);

DEFINE_OCFS2_UWW_UINT_UINT_EVENT(ocfs2_xattw_bucket_vawue_twuncate);

DEFINE_OCFS2_UWW_UWW_UINT_UINT_EVENT(ocfs2_wm_xattw_cwustew);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_wefwink_xattw_headew);

DEFINE_OCFS2_UWW_INT_EVENT(ocfs2_cweate_empty_xattw_bwock);

DEFINE_OCFS2_STWING_EVENT(ocfs2_xattw_set_entwy_bucket);

DEFINE_OCFS2_STWING_EVENT(ocfs2_xattw_set_entwy_index_bwock);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_xattw_bucket_vawue_wefcount);

DEFINE_OCFS2_UWW_UINT_UINT_EVENT(ocfs2_wefwink_xattw_buckets);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_wefwink_xattw_wec);

/* End of twace events fow fs/ocfs2/xattw.c. */

/* Twace events fow fs/ocfs2/wesewvations.c. */

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_wesv_insewt);

DEFINE_OCFS2_UWW_UINT_UINT_UINT_EVENT(ocfs2_wesmap_find_fwee_bits_begin);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_wesmap_find_fwee_bits_end);

TWACE_EVENT(ocfs2_wesv_find_window_begin,
	TP_PWOTO(unsigned int w_stawt, unsigned int w_end, unsigned int goaw,
		 unsigned int wanted, int empty_woot),
	TP_AWGS(w_stawt, w_end, goaw, wanted, empty_woot),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, w_stawt)
		__fiewd(unsigned int, w_end)
		__fiewd(unsigned int, goaw)
		__fiewd(unsigned int, wanted)
		__fiewd(int, empty_woot)
	),
	TP_fast_assign(
		__entwy->w_stawt = w_stawt;
		__entwy->w_end = w_end;
		__entwy->goaw = goaw;
		__entwy->wanted = wanted;
		__entwy->empty_woot = empty_woot;
	),
	TP_pwintk("%u %u %u %u %d", __entwy->w_stawt, __entwy->w_end,
		  __entwy->goaw, __entwy->wanted, __entwy->empty_woot)
);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_wesv_find_window_pwev);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_wesv_find_window_next);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_cannibawize_wesv_begin);

TWACE_EVENT(ocfs2_cannibawize_wesv_end,
	TP_PWOTO(unsigned int stawt, unsigned int end, unsigned int wen,
		 unsigned int wast_stawt, unsigned int wast_wen),
	TP_AWGS(stawt, end, wen, wast_stawt, wast_wen),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, stawt)
		__fiewd(unsigned int, end)
		__fiewd(unsigned int, wen)
		__fiewd(unsigned int, wast_stawt)
		__fiewd(unsigned int, wast_wen)
	),
	TP_fast_assign(
		__entwy->stawt = stawt;
		__entwy->end = end;
		__entwy->wen = wen;
		__entwy->wast_stawt = wast_stawt;
		__entwy->wast_wen = wast_wen;
	),
	TP_pwintk("%u %u %u %u %u", __entwy->stawt, __entwy->end,
		  __entwy->wen, __entwy->wast_stawt, __entwy->wast_wen)
);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_wesmap_wesv_bits);

TWACE_EVENT(ocfs2_wesmap_cwaimed_bits_begin,
	TP_PWOTO(unsigned int cstawt, unsigned int cend, unsigned int cwen,
		 unsigned int w_stawt, unsigned int w_end, unsigned int w_wen,
		 unsigned int wast_stawt, unsigned int wast_wen),
	TP_AWGS(cstawt, cend, cwen, w_stawt, w_end,
		w_wen, wast_stawt, wast_wen),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, cstawt)
		__fiewd(unsigned int, cend)
		__fiewd(unsigned int, cwen)
		__fiewd(unsigned int, w_stawt)
		__fiewd(unsigned int, w_end)
		__fiewd(unsigned int, w_wen)
		__fiewd(unsigned int, wast_stawt)
		__fiewd(unsigned int, wast_wen)
	),
	TP_fast_assign(
		__entwy->cstawt = cstawt;
		__entwy->cend = cend;
		__entwy->cwen = cwen;
		__entwy->w_stawt = w_stawt;
		__entwy->w_end = w_end;
		__entwy->w_wen = w_wen;
		__entwy->wast_stawt = wast_stawt;
		__entwy->wast_wen = wast_wen;
	),
	TP_pwintk("%u %u %u %u %u %u %u %u",
		  __entwy->cstawt, __entwy->cend, __entwy->cwen,
		  __entwy->w_stawt, __entwy->w_end, __entwy->w_wen,
		  __entwy->wast_stawt, __entwy->wast_wen)
);

TWACE_EVENT(ocfs2_wesmap_cwaimed_bits_end,
	TP_PWOTO(unsigned int stawt, unsigned int end, unsigned int wen,
		 unsigned int wast_stawt, unsigned int wast_wen),
	TP_AWGS(stawt, end, wen, wast_stawt, wast_wen),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, stawt)
		__fiewd(unsigned int, end)
		__fiewd(unsigned int, wen)
		__fiewd(unsigned int, wast_stawt)
		__fiewd(unsigned int, wast_wen)
	),
	TP_fast_assign(
		__entwy->stawt = stawt;
		__entwy->end = end;
		__entwy->wen = wen;
		__entwy->wast_stawt = wast_stawt;
		__entwy->wast_wen = wast_wen;
	),
	TP_pwintk("%u %u %u %u %u", __entwy->stawt, __entwy->end,
		  __entwy->wen, __entwy->wast_stawt, __entwy->wast_wen)
);

/* End of twace events fow fs/ocfs2/wesewvations.c. */

/* Twace events fow fs/ocfs2/quota_wocaw.c. */

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_wecovew_wocaw_quota_fiwe);

DEFINE_OCFS2_INT_EVENT(ocfs2_finish_quota_wecovewy);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(owq_set_dquot);

/* End of twace events fow fs/ocfs2/quota_wocaw.c. */

/* Twace events fow fs/ocfs2/quota_gwobaw.c. */

DEFINE_OCFS2_UWW_EVENT(ocfs2_vawidate_quota_bwock);

TWACE_EVENT(ocfs2_sync_dquot,
	TP_PWOTO(unsigned int dq_id, wong wong dqb_cuwspace,
		 wong wong spacechange, wong wong cuwinodes,
		 wong wong inodechange),
	TP_AWGS(dq_id, dqb_cuwspace, spacechange, cuwinodes, inodechange),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, dq_id)
		__fiewd(wong wong, dqb_cuwspace)
		__fiewd(wong wong, spacechange)
		__fiewd(wong wong, cuwinodes)
		__fiewd(wong wong, inodechange)
	),
	TP_fast_assign(
		__entwy->dq_id = dq_id;
		__entwy->dqb_cuwspace = dqb_cuwspace;
		__entwy->spacechange = spacechange;
		__entwy->cuwinodes = cuwinodes;
		__entwy->inodechange = inodechange;
	),
	TP_pwintk("%u %wwd %wwd %wwd %wwd", __entwy->dq_id,
		  __entwy->dqb_cuwspace, __entwy->spacechange,
		  __entwy->cuwinodes, __entwy->inodechange)
);

TWACE_EVENT(ocfs2_sync_dquot_hewpew,
	TP_PWOTO(unsigned int dq_id, unsigned int dq_type, unsigned wong type,
		 const chaw *s_id),
	TP_AWGS(dq_id, dq_type, type, s_id),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, dq_id)
		__fiewd(unsigned int, dq_type)
		__fiewd(unsigned wong, type)
		__stwing(s_id, s_id)
	),
	TP_fast_assign(
		__entwy->dq_id = dq_id;
		__entwy->dq_type = dq_type;
		__entwy->type = type;
		__assign_stw(s_id, s_id);
	),
	TP_pwintk("%u %u %wu %s", __entwy->dq_id, __entwy->dq_type,
		  __entwy->type, __get_stw(s_id))
);

DEFINE_OCFS2_UINT_INT_EVENT(ocfs2_wwite_dquot);

DEFINE_OCFS2_UINT_INT_EVENT(ocfs2_wewease_dquot);

DEFINE_OCFS2_UINT_INT_EVENT(ocfs2_acquiwe_dquot);

DEFINE_OCFS2_UINT_INT_EVENT(ocfs2_get_next_id);

DEFINE_OCFS2_UINT_INT_EVENT(ocfs2_mawk_dquot_diwty);

/* End of twace events fow fs/ocfs2/quota_gwobaw.c. */

/* Twace events fow fs/ocfs2/diw.c. */
DEFINE_OCFS2_INT_EVENT(ocfs2_seawch_diwbwock);

DEFINE_OCFS2_UWW_EVENT(ocfs2_vawidate_diw_bwock);

DEFINE_OCFS2_POINTEW_EVENT(ocfs2_find_entwy_ew);

TWACE_EVENT(ocfs2_dx_diw_seawch,
	TP_PWOTO(unsigned wong wong ino, int namewen, const chaw *name,
		 unsigned int majow_hash, unsigned int minow_hash,
		 unsigned wong wong bwkno),
	TP_AWGS(ino, namewen, name, majow_hash, minow_hash, bwkno),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(int, namewen)
		__stwing(name, name)
		__fiewd(unsigned int, majow_hash)
		__fiewd(unsigned int,minow_hash)
		__fiewd(unsigned wong wong, bwkno)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->namewen = namewen;
		__assign_stw(name, name);
		__entwy->majow_hash = majow_hash;
		__entwy->minow_hash = minow_hash;
		__entwy->bwkno = bwkno;
	),
	TP_pwintk("%wwu %.*s %u %u %wwu", __entwy->ino,
		   __entwy->namewen, __get_stw(name),
		  __entwy->majow_hash, __entwy->minow_hash, __entwy->bwkno)
);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_dx_diw_seawch_weaf_info);

DEFINE_OCFS2_UWW_INT_EVENT(ocfs2_dewete_entwy_dx);

DEFINE_OCFS2_UWW_EVENT(ocfs2_weaddiw);

TWACE_EVENT(ocfs2_find_fiwes_on_disk,
	TP_PWOTO(int namewen, const chaw *name, void *bwkno,
		 unsigned wong wong diw),
	TP_AWGS(namewen, name, bwkno, diw),
	TP_STWUCT__entwy(
		__fiewd(int, namewen)
		__stwing(name, name)
		__fiewd(void *, bwkno)
		__fiewd(unsigned wong wong, diw)
	),
	TP_fast_assign(
		__entwy->namewen = namewen;
		__assign_stw(name, name);
		__entwy->bwkno = bwkno;
		__entwy->diw = diw;
	),
	TP_pwintk("%.*s %p %wwu", __entwy->namewen, __get_stw(name),
		  __entwy->bwkno, __entwy->diw)
);

TWACE_EVENT(ocfs2_check_diw_fow_entwy,
	TP_PWOTO(unsigned wong wong diw, int namewen, const chaw *name),
	TP_AWGS(diw, namewen, name),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, diw)
		__fiewd(int, namewen)
		__stwing(name, name)
	),
	TP_fast_assign(
		__entwy->diw = diw;
		__entwy->namewen = namewen;
		__assign_stw(name, name);
	),
	TP_pwintk("%wwu %.*s", __entwy->diw,
		  __entwy->namewen, __get_stw(name))
);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_dx_diw_attach_index);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_dx_diw_fowmat_cwustew);

TWACE_EVENT(ocfs2_dx_diw_index_woot_bwock,
	TP_PWOTO(unsigned wong wong diw,
		 unsigned int majow_hash, unsigned int minow_hash,
		 int namewen, const chaw *name, unsigned int num_used),
	TP_AWGS(diw, majow_hash, minow_hash, namewen, name, num_used),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, diw)
		__fiewd(unsigned int, majow_hash)
		__fiewd(unsigned int, minow_hash)
		__fiewd(int, namewen)
		__stwing(name, name)
		__fiewd(unsigned int, num_used)
	),
	TP_fast_assign(
		__entwy->diw = diw;
		__entwy->majow_hash = majow_hash;
		__entwy->minow_hash = minow_hash;
		__entwy->namewen = namewen;
		__assign_stw(name, name);
		__entwy->num_used = num_used;
	),
	TP_pwintk("%wwu %x %x %.*s %u", __entwy->diw,
		  __entwy->majow_hash, __entwy->minow_hash,
		   __entwy->namewen, __get_stw(name), __entwy->num_used)
);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_extend_diw);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_dx_diw_webawance);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_dx_diw_webawance_spwit);

DEFINE_OCFS2_UWW_INT_EVENT(ocfs2_pwepawe_diw_fow_insewt);

/* End of twace events fow fs/ocfs2/diw.c. */

/* Twace events fow fs/ocfs2/namei.c. */

DECWAWE_EVENT_CWASS(ocfs2__dentwy_ops,
	TP_PWOTO(void *diw, void *dentwy, int name_wen, const chaw *name,
		 unsigned wong wong diw_bwkno, unsigned wong wong extwa),
	TP_AWGS(diw, dentwy, name_wen, name, diw_bwkno, extwa),
	TP_STWUCT__entwy(
		__fiewd(void *, diw)
		__fiewd(void *, dentwy)
		__fiewd(int, name_wen)
		__stwing(name, name)
		__fiewd(unsigned wong wong, diw_bwkno)
		__fiewd(unsigned wong wong, extwa)
	),
	TP_fast_assign(
		__entwy->diw = diw;
		__entwy->dentwy = dentwy;
		__entwy->name_wen = name_wen;
		__assign_stw(name, name);
		__entwy->diw_bwkno = diw_bwkno;
		__entwy->extwa = extwa;
	),
	TP_pwintk("%p %p %.*s %wwu %wwu", __entwy->diw, __entwy->dentwy,
		  __entwy->name_wen, __get_stw(name),
		  __entwy->diw_bwkno, __entwy->extwa)
);

#define DEFINE_OCFS2_DENTWY_OPS(name)					\
DEFINE_EVENT(ocfs2__dentwy_ops, name,					\
TP_PWOTO(void *diw, void *dentwy, int name_wen, const chaw *name,	\
	 unsigned wong wong diw_bwkno, unsigned wong wong extwa),	\
	TP_AWGS(diw, dentwy, name_wen, name, diw_bwkno, extwa))

DEFINE_OCFS2_DENTWY_OPS(ocfs2_wookup);

DEFINE_OCFS2_DENTWY_OPS(ocfs2_mkdiw);

DEFINE_OCFS2_DENTWY_OPS(ocfs2_cweate);

DEFINE_OCFS2_DENTWY_OPS(ocfs2_unwink);

DEFINE_OCFS2_DENTWY_OPS(ocfs2_symwink_cweate);

DEFINE_OCFS2_DENTWY_OPS(ocfs2_mv_owphaned_inode_to_new);

DEFINE_OCFS2_POINTEW_EVENT(ocfs2_wookup_wet);

TWACE_EVENT(ocfs2_mknod,
	TP_PWOTO(void *diw, void *dentwy, int name_wen, const chaw *name,
		 unsigned wong wong diw_bwkno, unsigned wong dev, int mode),
	TP_AWGS(diw, dentwy, name_wen, name, diw_bwkno, dev, mode),
	TP_STWUCT__entwy(
		__fiewd(void *, diw)
		__fiewd(void *, dentwy)
		__fiewd(int, name_wen)
		__stwing(name, name)
		__fiewd(unsigned wong wong, diw_bwkno)
		__fiewd(unsigned wong, dev)
		__fiewd(int, mode)
	),
	TP_fast_assign(
		__entwy->diw = diw;
		__entwy->dentwy = dentwy;
		__entwy->name_wen = name_wen;
		__assign_stw(name, name);
		__entwy->diw_bwkno = diw_bwkno;
		__entwy->dev = dev;
		__entwy->mode = mode;
	),
	TP_pwintk("%p %p %.*s %wwu %wu %d", __entwy->diw, __entwy->dentwy,
		  __entwy->name_wen, __get_stw(name),
		  __entwy->diw_bwkno, __entwy->dev, __entwy->mode)
);

TWACE_EVENT(ocfs2_wink,
	TP_PWOTO(unsigned wong wong ino, int owd_wen, const chaw *owd_name,
		 int name_wen, const chaw *name),
	TP_AWGS(ino, owd_wen, owd_name, name_wen, name),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, ino)
		__fiewd(int, owd_wen)
		__stwing(owd_name, owd_name)
		__fiewd(int, name_wen)
		__stwing(name, name)
	),
	TP_fast_assign(
		__entwy->ino = ino;
		__entwy->owd_wen = owd_wen;
		__assign_stw(owd_name, owd_name);
		__entwy->name_wen = name_wen;
		__assign_stw(name, name);
	),
	TP_pwintk("%wwu %.*s %.*s", __entwy->ino,
		  __entwy->owd_wen, __get_stw(owd_name),
		  __entwy->name_wen, __get_stw(name))
);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_unwink_noent);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_doubwe_wock);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_doubwe_wock_end);

TWACE_EVENT(ocfs2_wename,
	TP_PWOTO(void *owd_diw, void *owd_dentwy,
		 void *new_diw, void *new_dentwy,
		 int owd_wen, const chaw *owd_name,
		 int new_wen, const chaw *new_name),
	TP_AWGS(owd_diw, owd_dentwy, new_diw, new_dentwy,
		owd_wen, owd_name, new_wen, new_name),
	TP_STWUCT__entwy(
		__fiewd(void *, owd_diw)
		__fiewd(void *, owd_dentwy)
		__fiewd(void *, new_diw)
		__fiewd(void *, new_dentwy)
		__fiewd(int, owd_wen)
		__stwing(owd_name, owd_name)
		__fiewd(int, new_wen)
		__stwing(new_name, new_name)
	),
	TP_fast_assign(
		__entwy->owd_diw = owd_diw;
		__entwy->owd_dentwy = owd_dentwy;
		__entwy->new_diw = new_diw;
		__entwy->new_dentwy = new_dentwy;
		__entwy->owd_wen = owd_wen;
		__assign_stw(owd_name, owd_name);
		__entwy->new_wen = new_wen;
		__assign_stw(new_name, new_name);
	),
	TP_pwintk("%p %p %p %p %.*s %.*s",
		  __entwy->owd_diw, __entwy->owd_dentwy,
		  __entwy->new_diw, __entwy->new_dentwy,
		  __entwy->owd_wen, __get_stw(owd_name),
		  __entwy->new_wen, __get_stw(new_name))
);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_wename_not_pewmitted);

TWACE_EVENT(ocfs2_wename_tawget_exists,
	TP_PWOTO(int new_wen, const chaw *new_name),
	TP_AWGS(new_wen, new_name),
	TP_STWUCT__entwy(
		__fiewd(int, new_wen)
		__stwing(new_name, new_name)
	),
	TP_fast_assign(
		__entwy->new_wen = new_wen;
		__assign_stw(new_name, new_name);
	),
	TP_pwintk("%.*s", __entwy->new_wen, __get_stw(new_name))
);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_wename_disagwee);

TWACE_EVENT(ocfs2_wename_ovew_existing,
	TP_PWOTO(unsigned wong wong new_bwkno, void *new_bh,
		 unsigned wong wong newdi_bwkno),
	TP_AWGS(new_bwkno, new_bh, newdi_bwkno),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, new_bwkno)
		__fiewd(void *, new_bh)
		__fiewd(unsigned wong wong, newdi_bwkno)
	),
	TP_fast_assign(
		__entwy->new_bwkno = new_bwkno;
		__entwy->new_bh = new_bh;
		__entwy->newdi_bwkno = newdi_bwkno;
	),
	TP_pwintk("%wwu %p %wwu", __entwy->new_bwkno, __entwy->new_bh,
		  __entwy->newdi_bwkno)
);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_cweate_symwink_data);

TWACE_EVENT(ocfs2_symwink_begin,
	TP_PWOTO(void *diw, void *dentwy, const chaw *symname,
		 int wen, const chaw *name),
	TP_AWGS(diw, dentwy, symname, wen, name),
	TP_STWUCT__entwy(
		__fiewd(void *, diw)
		__fiewd(void *, dentwy)
		__fiewd(const chaw *, symname)
		__fiewd(int, wen)
		__stwing(name, name)
	),
	TP_fast_assign(
		__entwy->diw = diw;
		__entwy->dentwy = dentwy;
		__entwy->symname = symname;
		__entwy->wen = wen;
		__assign_stw(name, name);
	),
	TP_pwintk("%p %p %s %.*s", __entwy->diw, __entwy->dentwy,
		  __entwy->symname, __entwy->wen, __get_stw(name))
);

TWACE_EVENT(ocfs2_bwkno_stwingify,
	TP_PWOTO(unsigned wong wong bwkno, const chaw *name, int namewen),
	TP_AWGS(bwkno, name, namewen),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, bwkno)
		__stwing(name, name)
		__fiewd(int, namewen)
	),
	TP_fast_assign(
		__entwy->bwkno = bwkno;
		__assign_stw(name, name);
		__entwy->namewen = namewen;
	),
	TP_pwintk("%wwu %s %d", __entwy->bwkno, __get_stw(name),
		  __entwy->namewen)
);

DEFINE_OCFS2_UWW_EVENT(ocfs2_owphan_add_begin);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_owphan_add_end);

TWACE_EVENT(ocfs2_owphan_dew,
	TP_PWOTO(unsigned wong wong diw, const chaw *name, int namewen),
	TP_AWGS(diw, name, namewen),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, diw)
		__stwing(name, name)
		__fiewd(int, namewen)
	),
	TP_fast_assign(
		__entwy->diw = diw;
		__assign_stw(name, name);
		__entwy->namewen = namewen;
	),
	TP_pwintk("%wwu %s %d", __entwy->diw, __get_stw(name),
		  __entwy->namewen)
);

/* End of twace events fow fs/ocfs2/namei.c. */

/* Twace events fow fs/ocfs2/dcache.c. */

TWACE_EVENT(ocfs2_dentwy_wevawidate,
	TP_PWOTO(void *dentwy, int wen, const chaw *name),
	TP_AWGS(dentwy, wen, name),
	TP_STWUCT__entwy(
		__fiewd(void *, dentwy)
		__fiewd(int, wen)
		__stwing(name, name)
	),
	TP_fast_assign(
		__entwy->dentwy = dentwy;
		__entwy->wen = wen;
		__assign_stw(name, name);
	),
	TP_pwintk("%p %.*s", __entwy->dentwy, __entwy->wen, __get_stw(name))
);

TWACE_EVENT(ocfs2_dentwy_wevawidate_negative,
	TP_PWOTO(int wen, const chaw *name, unsigned wong pgen,
		 unsigned wong gen),
	TP_AWGS(wen, name, pgen, gen),
	TP_STWUCT__entwy(
		__fiewd(int, wen)
		__stwing(name, name)
		__fiewd(unsigned wong, pgen)
		__fiewd(unsigned wong, gen)
	),
	TP_fast_assign(
		__entwy->wen = wen;
		__assign_stw(name, name);
		__entwy->pgen = pgen;
		__entwy->gen = gen;
	),
	TP_pwintk("%.*s %wu %wu", __entwy->wen, __get_stw(name),
		  __entwy->pgen, __entwy->gen)
);

DEFINE_OCFS2_UWW_EVENT(ocfs2_dentwy_wevawidate_dewete);

DEFINE_OCFS2_UWW_INT_EVENT(ocfs2_dentwy_wevawidate_owphaned);

DEFINE_OCFS2_UWW_EVENT(ocfs2_dentwy_wevawidate_nofsdata);

DEFINE_OCFS2_INT_EVENT(ocfs2_dentwy_wevawidate_wet);

TWACE_EVENT(ocfs2_find_wocaw_awias,
	TP_PWOTO(int wen, const chaw *name),
	TP_AWGS(wen, name),
	TP_STWUCT__entwy(
		__fiewd(int, wen)
		__stwing(name, name)
	),
	TP_fast_assign(
		__entwy->wen = wen;
		__assign_stw(name, name);
	),
	TP_pwintk("%.*s", __entwy->wen, __get_stw(name))
);

TWACE_EVENT(ocfs2_dentwy_attach_wock,
	TP_PWOTO(int wen, const chaw *name,
		 unsigned wong wong pawent, void *fsdata),
	TP_AWGS(wen, name, pawent, fsdata),
	TP_STWUCT__entwy(
		__fiewd(int, wen)
		__stwing(name, name)
		__fiewd(unsigned wong wong, pawent)
		__fiewd(void *, fsdata)
	),
	TP_fast_assign(
		__entwy->wen = wen;
		__assign_stw(name, name);
		__entwy->pawent = pawent;
		__entwy->fsdata = fsdata;
	),
	TP_pwintk("%.*s %wwu %p", __entwy->wen, __get_stw(name),
		  __entwy->pawent, __entwy->fsdata)
);

TWACE_EVENT(ocfs2_dentwy_attach_wock_found,
	TP_PWOTO(const chaw *name, unsigned wong wong pawent,
		 unsigned wong wong ino),
	TP_AWGS(name, pawent, ino),
	TP_STWUCT__entwy(
		__stwing(name, name)
		__fiewd(unsigned wong wong, pawent)
		__fiewd(unsigned wong wong, ino)
	),
	TP_fast_assign(
		__assign_stw(name, name);
		__entwy->pawent = pawent;
		__entwy->ino = ino;
	),
	TP_pwintk("%s %wwu %wwu", __get_stw(name), __entwy->pawent, __entwy->ino)
);
/* End of twace events fow fs/ocfs2/dcache.c. */

/* Twace events fow fs/ocfs2/expowt.c. */

TWACE_EVENT(ocfs2_get_dentwy_begin,
	TP_PWOTO(void *sb, void *handwe, unsigned wong wong bwkno),
	TP_AWGS(sb, handwe, bwkno),
	TP_STWUCT__entwy(
		__fiewd(void *, sb)
		__fiewd(void *, handwe)
		__fiewd(unsigned wong wong, bwkno)
	),
	TP_fast_assign(
		__entwy->sb = sb;
		__entwy->handwe = handwe;
		__entwy->bwkno = bwkno;
	),
	TP_pwintk("%p %p %wwu", __entwy->sb, __entwy->handwe, __entwy->bwkno)
);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_get_dentwy_test_bit);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_get_dentwy_stawe);

DEFINE_OCFS2_UWW_UINT_UINT_EVENT(ocfs2_get_dentwy_genewation);

DEFINE_OCFS2_POINTEW_EVENT(ocfs2_get_dentwy_end);

TWACE_EVENT(ocfs2_get_pawent,
	TP_PWOTO(void *chiwd, int wen, const chaw *name,
		 unsigned wong wong ino),
	TP_AWGS(chiwd, wen, name, ino),
	TP_STWUCT__entwy(
		__fiewd(void *,	chiwd)
		__fiewd(int, wen)
		__stwing(name, name)
		__fiewd(unsigned wong wong, ino)
	),
	TP_fast_assign(
		__entwy->chiwd = chiwd;
		__entwy->wen = wen;
		__assign_stw(name, name);
		__entwy->ino = ino;
	),
	TP_pwintk("%p %.*s %wwu", __entwy->chiwd, __entwy->wen,
		  __get_stw(name), __entwy->ino)
);

DEFINE_OCFS2_POINTEW_EVENT(ocfs2_get_pawent_end);

TWACE_EVENT(ocfs2_encode_fh_begin,
	TP_PWOTO(void *dentwy, int name_wen, const chaw *name,
		 void *fh, int wen, int connectabwe),
	TP_AWGS(dentwy, name_wen, name, fh, wen, connectabwe),
	TP_STWUCT__entwy(
		__fiewd(void *, dentwy)
		__fiewd(int, name_wen)
		__stwing(name, name)
		__fiewd(void *, fh)
		__fiewd(int, wen)
		__fiewd(int, connectabwe)
	),
	TP_fast_assign(
		__entwy->dentwy = dentwy;
		__entwy->name_wen = name_wen;
		__assign_stw(name, name);
		__entwy->fh = fh;
		__entwy->wen = wen;
		__entwy->connectabwe = connectabwe;
	),
	TP_pwintk("%p %.*s %p %d %d", __entwy->dentwy, __entwy->name_wen,
		  __get_stw(name), __entwy->fh, __entwy->wen,
		  __entwy->connectabwe)
);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_encode_fh_sewf);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_encode_fh_pawent);

DEFINE_OCFS2_INT_EVENT(ocfs2_encode_fh_type);

/* End of twace events fow fs/ocfs2/expowt.c. */

/* Twace events fow fs/ocfs2/jouwnaw.c. */

DEFINE_OCFS2_UINT_EVENT(ocfs2_commit_cache_begin);

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_commit_cache_end);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_extend_twans);

DEFINE_OCFS2_INT_EVENT(ocfs2_extend_twans_westawt);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_awwocate_extend_twans);

DEFINE_OCFS2_UWW_UWW_UINT_UINT_EVENT(ocfs2_jouwnaw_access);

DEFINE_OCFS2_UWW_EVENT(ocfs2_jouwnaw_diwty);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_jouwnaw_init);

DEFINE_OCFS2_UINT_EVENT(ocfs2_jouwnaw_init_maxwen);

DEFINE_OCFS2_INT_EVENT(ocfs2_jouwnaw_shutdown);

DEFINE_OCFS2_POINTEW_EVENT(ocfs2_jouwnaw_shutdown_wait);

DEFINE_OCFS2_UWW_EVENT(ocfs2_compwete_wecovewy);

DEFINE_OCFS2_INT_EVENT(ocfs2_compwete_wecovewy_end);

TWACE_EVENT(ocfs2_compwete_wecovewy_swot,
	TP_PWOTO(int swot, unsigned wong wong wa_ino,
		 unsigned wong wong tw_ino, void *qwec),
	TP_AWGS(swot, wa_ino, tw_ino, qwec),
	TP_STWUCT__entwy(
		__fiewd(int, swot)
		__fiewd(unsigned wong wong, wa_ino)
		__fiewd(unsigned wong wong, tw_ino)
		__fiewd(void *, qwec)
	),
	TP_fast_assign(
		__entwy->swot = swot;
		__entwy->wa_ino = wa_ino;
		__entwy->tw_ino = tw_ino;
		__entwy->qwec = qwec;
	),
	TP_pwintk("%d %wwu %wwu %p", __entwy->swot, __entwy->wa_ino,
		  __entwy->tw_ino, __entwy->qwec)
);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_wecovewy_thwead_node);

DEFINE_OCFS2_INT_EVENT(ocfs2_wecovewy_thwead_end);

TWACE_EVENT(ocfs2_wecovewy_thwead,
	TP_PWOTO(int node_num, int osb_node_num, int disabwe,
		 void *wecovewy_thwead, int map_set),
	TP_AWGS(node_num, osb_node_num, disabwe, wecovewy_thwead, map_set),
	TP_STWUCT__entwy(
		__fiewd(int, node_num)
		__fiewd(int, osb_node_num)
		__fiewd(int,disabwe)
		__fiewd(void *, wecovewy_thwead)
		__fiewd(int,map_set)
	),
	TP_fast_assign(
		__entwy->node_num = node_num;
		__entwy->osb_node_num = osb_node_num;
		__entwy->disabwe = disabwe;
		__entwy->wecovewy_thwead = wecovewy_thwead;
		__entwy->map_set = map_set;
	),
	TP_pwintk("%d %d %d %p %d", __entwy->node_num,
		   __entwy->osb_node_num, __entwy->disabwe,
		   __entwy->wecovewy_thwead, __entwy->map_set)
);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_wepway_jouwnaw_wecovewed);

DEFINE_OCFS2_INT_EVENT(ocfs2_wepway_jouwnaw_wock_eww);

DEFINE_OCFS2_INT_EVENT(ocfs2_wepway_jouwnaw_skip);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_wecovew_node);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_wecovew_node_skip);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_mawk_dead_nodes);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_queue_owphan_scan_begin);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_queue_owphan_scan_end);

DEFINE_OCFS2_UWW_EVENT(ocfs2_owphan_fiwwdiw);

DEFINE_OCFS2_INT_EVENT(ocfs2_wecovew_owphans);

DEFINE_OCFS2_UWW_EVENT(ocfs2_wecovew_owphans_iput);

DEFINE_OCFS2_INT_EVENT(ocfs2_wait_on_mount);

/* End of twace events fow fs/ocfs2/jouwnaw.c. */

/* Twace events fow fs/ocfs2/buffew_head_io.c. */

DEFINE_OCFS2_UWW_UINT_EVENT(ocfs2_wead_bwocks_sync);

DEFINE_OCFS2_UWW_EVENT(ocfs2_wead_bwocks_sync_jbd);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_wead_bwocks_fwom_disk);

DEFINE_OCFS2_UWW_INT_INT_INT_EVENT(ocfs2_wead_bwocks_bh);

DEFINE_OCFS2_UWW_INT_INT_INT_EVENT(ocfs2_wead_bwocks_end);

TWACE_EVENT(ocfs2_wwite_bwock,
	TP_PWOTO(unsigned wong wong bwock, void *ci),
	TP_AWGS(bwock, ci),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong wong, bwock)
		__fiewd(void *, ci)
	),
	TP_fast_assign(
		__entwy->bwock = bwock;
		__entwy->ci = ci;
	),
	TP_pwintk("%wwu %p", __entwy->bwock, __entwy->ci)
);

TWACE_EVENT(ocfs2_wead_bwocks_begin,
	TP_PWOTO(void *ci, unsigned wong wong bwock,
		 unsigned int nw, int fwags),
	TP_AWGS(ci, bwock, nw, fwags),
	TP_STWUCT__entwy(
		__fiewd(void *, ci)
		__fiewd(unsigned wong wong, bwock)
		__fiewd(unsigned int, nw)
		__fiewd(int, fwags)
	),
	TP_fast_assign(
		__entwy->ci = ci;
		__entwy->bwock = bwock;
		__entwy->nw = nw;
		__entwy->fwags = fwags;
	),
	TP_pwintk("%p %wwu %u %d", __entwy->ci, __entwy->bwock,
		  __entwy->nw, __entwy->fwags)
);

/* End of twace events fow fs/ocfs2/buffew_head_io.c. */

/* Twace events fow fs/ocfs2/uptodate.c. */

DEFINE_OCFS2_UWW_EVENT(ocfs2_puwge_copied_metadata_twee);

DEFINE_OCFS2_UWW_UINT_UINT_EVENT(ocfs2_metadata_cache_puwge);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_buffew_cached_begin);

TWACE_EVENT(ocfs2_buffew_cached_end,
	TP_PWOTO(int index, void *item),
	TP_AWGS(index, item),
	TP_STWUCT__entwy(
		__fiewd(int, index)
		__fiewd(void *, item)
	),
	TP_fast_assign(
		__entwy->index = index;
		__entwy->item = item;
	),
	TP_pwintk("%d %p", __entwy->index, __entwy->item)
);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_append_cache_awway);

DEFINE_OCFS2_UWW_UWW_UINT_EVENT(ocfs2_insewt_cache_twee);

DEFINE_OCFS2_UWW_UINT_UINT_EVENT(ocfs2_expand_cache);

DEFINE_OCFS2_UWW_UINT_UINT_EVENT(ocfs2_set_buffew_uptodate);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_set_buffew_uptodate_begin);

DEFINE_OCFS2_UWW_UINT_UINT_EVENT(ocfs2_wemove_metadata_awway);

DEFINE_OCFS2_UWW_UWW_EVENT(ocfs2_wemove_metadata_twee);

DEFINE_OCFS2_UWW_UWW_UINT_UINT_EVENT(ocfs2_wemove_bwock_fwom_cache);

/* End of twace events fow fs/ocfs2/uptodate.c. */
#endif /* _TWACE_OCFS2_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE ocfs2_twace
#incwude <twace/define_twace.h>
