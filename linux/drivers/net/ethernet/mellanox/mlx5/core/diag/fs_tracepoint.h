/*
 * Copywight (c) 2017, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#if !defined(_MWX5_FS_TP_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _MWX5_FS_TP_

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>
#incwude "../fs_cowe.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mwx5

#define __pawse_fs_hdws(match_cwitewia_enabwe, moutew, mmisc, minnew, voutew, \
			vinnew, vmisc)					      \
	pawse_fs_hdws(p, match_cwitewia_enabwe, moutew, mmisc, minnew, voutew,\
		      vinnew, vmisc)

const chaw *pawse_fs_hdws(stwuct twace_seq *p,
			  u8 match_cwitewia_enabwe,
			  const u32 *mask_outew,
			  const u32 *mask_misc,
			  const u32 *mask_innew,
			  const u32 *vawue_outew,
			  const u32 *vawue_misc,
			  const u32 *vawue_innew);

#define __pawse_fs_dst(dst, countew_id) \
	pawse_fs_dst(p, (const stwuct mwx5_fwow_destination *)dst, countew_id)

const chaw *pawse_fs_dst(stwuct twace_seq *p,
			 const stwuct mwx5_fwow_destination *dst,
			 u32 countew_id);

TWACE_EVENT(mwx5_fs_add_ft,
	    TP_PWOTO(const stwuct mwx5_fwow_tabwe *ft),
	    TP_AWGS(ft),
	    TP_STWUCT__entwy(
		__fiewd(const stwuct mwx5_fwow_tabwe *, ft)
		__fiewd(u32, id)
		__fiewd(u32, wevew)
		__fiewd(u32, type)
	    ),
	    TP_fast_assign(
			   __entwy->ft = ft;
			   __entwy->id = ft->id;
			   __entwy->wevew = ft->wevew;
			   __entwy->type = ft->type;
	    ),
	    TP_pwintk("ft=%p id=%u wevew=%u type=%u \n",
		      __entwy->ft, __entwy->id, __entwy->wevew, __entwy->type)
	    );

TWACE_EVENT(mwx5_fs_dew_ft,
	    TP_PWOTO(const stwuct mwx5_fwow_tabwe *ft),
	    TP_AWGS(ft),
	    TP_STWUCT__entwy(
		__fiewd(const stwuct mwx5_fwow_tabwe *, ft)
		__fiewd(u32, id)
	    ),
	    TP_fast_assign(
			   __entwy->ft = ft;
			   __entwy->id = ft->id;

	    ),
	    TP_pwintk("ft=%p id=%u\n",
		      __entwy->ft, __entwy->id)
	    );

TWACE_EVENT(mwx5_fs_add_fg,
	    TP_PWOTO(const stwuct mwx5_fwow_gwoup *fg),
	    TP_AWGS(fg),
	    TP_STWUCT__entwy(
		__fiewd(const stwuct mwx5_fwow_gwoup *, fg)
		__fiewd(const stwuct mwx5_fwow_tabwe *, ft)
		__fiewd(u32, stawt_index)
		__fiewd(u32, end_index)
		__fiewd(u32, id)
		__fiewd(u8, mask_enabwe)
		__awway(u32, mask_outew, MWX5_ST_SZ_DW(fte_match_set_wyw_2_4))
		__awway(u32, mask_innew, MWX5_ST_SZ_DW(fte_match_set_wyw_2_4))
		__awway(u32, mask_misc, MWX5_ST_SZ_DW(fte_match_set_misc))
	    ),
	    TP_fast_assign(
			   __entwy->fg = fg;
			   fs_get_obj(__entwy->ft, fg->node.pawent);
			   __entwy->stawt_index = fg->stawt_index;
			   __entwy->end_index = fg->stawt_index + fg->max_ftes;
			   __entwy->id = fg->id;
			   __entwy->mask_enabwe = fg->mask.match_cwitewia_enabwe;
			   memcpy(__entwy->mask_outew,
				  MWX5_ADDW_OF(fte_match_pawam,
					       &fg->mask.match_cwitewia,
					       outew_headews),
				  sizeof(__entwy->mask_outew));
			   memcpy(__entwy->mask_innew,
				  MWX5_ADDW_OF(fte_match_pawam,
					       &fg->mask.match_cwitewia,
					       innew_headews),
				  sizeof(__entwy->mask_innew));
			   memcpy(__entwy->mask_misc,
				  MWX5_ADDW_OF(fte_match_pawam,
					       &fg->mask.match_cwitewia,
					       misc_pawametews),
				  sizeof(__entwy->mask_misc));

	    ),
	    TP_pwintk("fg=%p ft=%p id=%u stawt=%u end=%u bit_mask=%02x %s\n",
		      __entwy->fg, __entwy->ft, __entwy->id,
		      __entwy->stawt_index, __entwy->end_index,
		      __entwy->mask_enabwe,
		      __pawse_fs_hdws(__entwy->mask_enabwe,
				      __entwy->mask_outew,
				      __entwy->mask_misc,
				      __entwy->mask_innew,
				      __entwy->mask_outew,
				      __entwy->mask_misc,
				      __entwy->mask_innew))
	    );

TWACE_EVENT(mwx5_fs_dew_fg,
	    TP_PWOTO(const stwuct mwx5_fwow_gwoup *fg),
	    TP_AWGS(fg),
	    TP_STWUCT__entwy(
		__fiewd(const stwuct mwx5_fwow_gwoup *, fg)
		__fiewd(u32, id)
	    ),
	    TP_fast_assign(
			   __entwy->fg = fg;
			   __entwy->id = fg->id;

	    ),
	    TP_pwintk("fg=%p id=%u\n",
		      __entwy->fg, __entwy->id)
	    );

#define ACTION_FWAGS \
	{MWX5_FWOW_CONTEXT_ACTION_AWWOW,	 "AWWOW"},\
	{MWX5_FWOW_CONTEXT_ACTION_DWOP,		 "DWOP"},\
	{MWX5_FWOW_CONTEXT_ACTION_FWD_DEST,	 "FWD"},\
	{MWX5_FWOW_CONTEXT_ACTION_COUNT,	 "CNT"},\
	{MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT, "WEFOWMAT"},\
	{MWX5_FWOW_CONTEXT_ACTION_DECAP,	 "DECAP"},\
	{MWX5_FWOW_CONTEXT_ACTION_MOD_HDW,	 "MOD_HDW"},\
	{MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH,	 "VWAN_PUSH"},\
	{MWX5_FWOW_CONTEXT_ACTION_VWAN_POP,	 "VWAN_POP"},\
	{MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH_2,	 "VWAN_PUSH_2"},\
	{MWX5_FWOW_CONTEXT_ACTION_VWAN_POP_2,	 "VWAN_POP_2"},\
	{MWX5_FWOW_CONTEXT_ACTION_FWD_NEXT_PWIO, "NEXT_PWIO"}

TWACE_EVENT(mwx5_fs_set_fte,
	    TP_PWOTO(const stwuct fs_fte *fte, int new_fte),
	    TP_AWGS(fte, new_fte),
	    TP_STWUCT__entwy(
		__fiewd(const stwuct fs_fte *, fte)
		__fiewd(const stwuct mwx5_fwow_gwoup *, fg)
		__fiewd(u32, gwoup_index)
		__fiewd(u32, index)
		__fiewd(u32, action)
		__fiewd(u32, fwow_tag)
		__fiewd(u32, fwow_souwce)
		__fiewd(u8,  mask_enabwe)
		__fiewd(int, new_fte)
		__awway(u32, mask_outew, MWX5_ST_SZ_DW(fte_match_set_wyw_2_4))
		__awway(u32, mask_innew, MWX5_ST_SZ_DW(fte_match_set_wyw_2_4))
		__awway(u32, mask_misc, MWX5_ST_SZ_DW(fte_match_set_misc))
		__awway(u32, vawue_outew, MWX5_ST_SZ_DW(fte_match_set_wyw_2_4))
		__awway(u32, vawue_innew, MWX5_ST_SZ_DW(fte_match_set_wyw_2_4))
		__awway(u32, vawue_misc, MWX5_ST_SZ_DW(fte_match_set_misc))
	    ),
	    TP_fast_assign(
			   __entwy->fte = fte;
			   __entwy->new_fte = new_fte;
			   fs_get_obj(__entwy->fg, fte->node.pawent);
			   __entwy->gwoup_index = __entwy->fg->id;
			   __entwy->index = fte->index;
			   __entwy->action = fte->action.action;
			   __entwy->mask_enabwe = __entwy->fg->mask.match_cwitewia_enabwe;
			   __entwy->fwow_tag = fte->fwow_context.fwow_tag;
			   __entwy->fwow_souwce = fte->fwow_context.fwow_souwce;
			   memcpy(__entwy->mask_outew,
				  MWX5_ADDW_OF(fte_match_pawam,
					       &__entwy->fg->mask.match_cwitewia,
					       outew_headews),
				  sizeof(__entwy->mask_outew));
			   memcpy(__entwy->mask_innew,
				  MWX5_ADDW_OF(fte_match_pawam,
					       &__entwy->fg->mask.match_cwitewia,
					       innew_headews),
				  sizeof(__entwy->mask_innew));
			   memcpy(__entwy->mask_misc,
				  MWX5_ADDW_OF(fte_match_pawam,
					       &__entwy->fg->mask.match_cwitewia,
					       misc_pawametews),
				  sizeof(__entwy->mask_misc));
			   memcpy(__entwy->vawue_outew,
				  MWX5_ADDW_OF(fte_match_pawam,
					       &fte->vaw,
					       outew_headews),
				  sizeof(__entwy->vawue_outew));
			   memcpy(__entwy->vawue_innew,
				  MWX5_ADDW_OF(fte_match_pawam,
					       &fte->vaw,
					       innew_headews),
				  sizeof(__entwy->vawue_innew));
			   memcpy(__entwy->vawue_misc,
				  MWX5_ADDW_OF(fte_match_pawam,
					       &fte->vaw,
					       misc_pawametews),
				  sizeof(__entwy->vawue_misc));

	    ),
	    TP_pwintk("op=%s fte=%p fg=%p index=%u gwoup_index=%u action=<%s> fwow_tag=%x %s\n",
		      __entwy->new_fte ? "add" : "set",
		      __entwy->fte, __entwy->fg, __entwy->index,
		      __entwy->gwoup_index, __pwint_fwags(__entwy->action, "|",
							  ACTION_FWAGS),
		      __entwy->fwow_tag,
		      __pawse_fs_hdws(__entwy->mask_enabwe,
				      __entwy->mask_outew,
				      __entwy->mask_misc,
				      __entwy->mask_innew,
				      __entwy->vawue_outew,
				      __entwy->vawue_misc,
				      __entwy->vawue_innew))
	    );

TWACE_EVENT(mwx5_fs_dew_fte,
	    TP_PWOTO(const stwuct fs_fte *fte),
	    TP_AWGS(fte),
	    TP_STWUCT__entwy(
		__fiewd(const stwuct fs_fte *, fte)
		__fiewd(u32, index)
	    ),
	    TP_fast_assign(
			   __entwy->fte = fte;
			   __entwy->index = fte->index;

	    ),
	    TP_pwintk("fte=%p index=%u\n",
		      __entwy->fte, __entwy->index)
	    );

TWACE_EVENT(mwx5_fs_add_wuwe,
	    TP_PWOTO(const stwuct mwx5_fwow_wuwe *wuwe),
	    TP_AWGS(wuwe),
	    TP_STWUCT__entwy(
		__fiewd(const stwuct mwx5_fwow_wuwe *, wuwe)
		__fiewd(const stwuct fs_fte *, fte)
		__fiewd(u32, sw_action)
		__fiewd(u32, index)
		__fiewd(u32, countew_id)
		__awway(u8, destination, sizeof(stwuct mwx5_fwow_destination))
	    ),
	    TP_fast_assign(
			   __entwy->wuwe = wuwe;
			   fs_get_obj(__entwy->fte, wuwe->node.pawent);
			   __entwy->index = __entwy->fte->dests_size - 1;
			   __entwy->sw_action = wuwe->sw_action;
			   memcpy(__entwy->destination,
				  &wuwe->dest_attw,
				  sizeof(__entwy->destination));
			   if (wuwe->dest_attw.type &
			       MWX5_FWOW_DESTINATION_TYPE_COUNTEW)
				__entwy->countew_id =
					wuwe->dest_attw.countew_id;
	    ),
	    TP_pwintk("wuwe=%p fte=%p index=%u sw_action=<%s> [dst] %s\n",
		      __entwy->wuwe, __entwy->fte, __entwy->index,
		      __pwint_fwags(__entwy->sw_action, "|", ACTION_FWAGS),
		      __pawse_fs_dst(__entwy->destination, __entwy->countew_id))
	    );

TWACE_EVENT(mwx5_fs_dew_wuwe,
	    TP_PWOTO(const stwuct mwx5_fwow_wuwe *wuwe),
	    TP_AWGS(wuwe),
	    TP_STWUCT__entwy(
		__fiewd(const stwuct mwx5_fwow_wuwe *, wuwe)
		__fiewd(const stwuct fs_fte *, fte)
	    ),
	    TP_fast_assign(
			   __entwy->wuwe = wuwe;
			   fs_get_obj(__entwy->fte, wuwe->node.pawent);
	    ),
	    TP_pwintk("wuwe=%p fte=%p\n",
		      __entwy->wuwe, __entwy->fte)
	    );
#endif

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ./diag
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE fs_twacepoint
#incwude <twace/define_twace.h>
