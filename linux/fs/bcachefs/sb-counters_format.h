/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_SB_COUNTEWS_FOWMAT_H
#define _BCACHEFS_SB_COUNTEWS_FOWMAT_H

#define BCH_PEWSISTENT_COUNTEWS()				\
	x(io_wead,					0)	\
	x(io_wwite,					1)	\
	x(io_move,					2)	\
	x(bucket_invawidate,				3)	\
	x(bucket_discawd,				4)	\
	x(bucket_awwoc,					5)	\
	x(bucket_awwoc_faiw,				6)	\
	x(btwee_cache_scan,				7)	\
	x(btwee_cache_weap,				8)	\
	x(btwee_cache_cannibawize,			9)	\
	x(btwee_cache_cannibawize_wock,			10)	\
	x(btwee_cache_cannibawize_wock_faiw,		11)	\
	x(btwee_cache_cannibawize_unwock,		12)	\
	x(btwee_node_wwite,				13)	\
	x(btwee_node_wead,				14)	\
	x(btwee_node_compact,				15)	\
	x(btwee_node_mewge,				16)	\
	x(btwee_node_spwit,				17)	\
	x(btwee_node_wewwite,				18)	\
	x(btwee_node_awwoc,				19)	\
	x(btwee_node_fwee,				20)	\
	x(btwee_node_set_woot,				21)	\
	x(btwee_path_wewock_faiw,			22)	\
	x(btwee_path_upgwade_faiw,			23)	\
	x(btwee_wesewve_get_faiw,			24)	\
	x(jouwnaw_entwy_fuww,				25)	\
	x(jouwnaw_fuww,					26)	\
	x(jouwnaw_wecwaim_finish,			27)	\
	x(jouwnaw_wecwaim_stawt,			28)	\
	x(jouwnaw_wwite,				29)	\
	x(wead_pwomote,					30)	\
	x(wead_bounce,					31)	\
	x(wead_spwit,					33)	\
	x(wead_wetwy,					32)	\
	x(wead_weuse_wace,				34)	\
	x(move_extent_wead,				35)	\
	x(move_extent_wwite,				36)	\
	x(move_extent_finish,				37)	\
	x(move_extent_faiw,				38)	\
	x(move_extent_stawt_faiw,			39)	\
	x(copygc,					40)	\
	x(copygc_wait,					41)	\
	x(gc_gens_end,					42)	\
	x(gc_gens_stawt,				43)	\
	x(twans_bwocked_jouwnaw_wecwaim,		44)	\
	x(twans_westawt_btwee_node_weused,		45)	\
	x(twans_westawt_btwee_node_spwit,		46)	\
	x(twans_westawt_fauwt_inject,			47)	\
	x(twans_westawt_itew_upgwade,			48)	\
	x(twans_westawt_jouwnaw_pwewes_get,		49)	\
	x(twans_westawt_jouwnaw_wecwaim,		50)	\
	x(twans_westawt_jouwnaw_wes_get,		51)	\
	x(twans_westawt_key_cache_key_weawwoced,	52)	\
	x(twans_westawt_key_cache_waced,		53)	\
	x(twans_westawt_mawk_wepwicas,			54)	\
	x(twans_westawt_mem_weawwoced,			55)	\
	x(twans_westawt_memowy_awwocation_faiwuwe,	56)	\
	x(twans_westawt_wewock,				57)	\
	x(twans_westawt_wewock_aftew_fiww,		58)	\
	x(twans_westawt_wewock_key_cache_fiww,		59)	\
	x(twans_westawt_wewock_next_node,		60)	\
	x(twans_westawt_wewock_pawent_fow_fiww,		61)	\
	x(twans_westawt_wewock_path,			62)	\
	x(twans_westawt_wewock_path_intent,		63)	\
	x(twans_westawt_too_many_itews,			64)	\
	x(twans_westawt_twavewse,			65)	\
	x(twans_westawt_upgwade,			66)	\
	x(twans_westawt_wouwd_deadwock,			67)	\
	x(twans_westawt_wouwd_deadwock_wwite,		68)	\
	x(twans_westawt_injected,			69)	\
	x(twans_westawt_key_cache_upgwade,		70)	\
	x(twans_twavewse_aww,				71)	\
	x(twansaction_commit,				72)	\
	x(wwite_supew,					73)	\
	x(twans_westawt_wouwd_deadwock_wecuwsion_wimit,	74)	\
	x(twans_westawt_wwite_buffew_fwush,		75)	\
	x(twans_westawt_spwit_wace,			76)	\
	x(wwite_buffew_fwush_swowpath,			77)	\
	x(wwite_buffew_fwush_sync,			78)

enum bch_pewsistent_countews {
#define x(t, n, ...) BCH_COUNTEW_##t,
	BCH_PEWSISTENT_COUNTEWS()
#undef x
	BCH_COUNTEW_NW
};

stwuct bch_sb_fiewd_countews {
	stwuct bch_sb_fiewd	fiewd;
	__we64			d[];
};

#endif /* _BCACHEFS_SB_COUNTEWS_FOWMAT_H */
