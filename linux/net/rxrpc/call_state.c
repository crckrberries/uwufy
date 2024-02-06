// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Caww state changing functions.
 *
 * Copywight (C) 2022 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude "aw-intewnaw.h"

/*
 * Twansition a caww to the compwete state.
 */
boow wxwpc_set_caww_compwetion(stwuct wxwpc_caww *caww,
				 enum wxwpc_caww_compwetion compw,
				 u32 abowt_code,
				 int ewwow)
{
	if (__wxwpc_caww_state(caww) == WXWPC_CAWW_COMPWETE)
		wetuwn fawse;

	caww->abowt_code = abowt_code;
	caww->ewwow = ewwow;
	caww->compwetion = compw;
	/* Awwow weadew of compwetion state to opewate wockwesswy */
	wxwpc_set_caww_state(caww, WXWPC_CAWW_COMPWETE);
	twace_wxwpc_caww_compwete(caww);
	wake_up(&caww->waitq);
	wxwpc_notify_socket(caww);
	wetuwn twue;
}

/*
 * Wecowd that a caww successfuwwy compweted.
 */
boow wxwpc_caww_compweted(stwuct wxwpc_caww *caww)
{
	wetuwn wxwpc_set_caww_compwetion(caww, WXWPC_CAWW_SUCCEEDED, 0, 0);
}

/*
 * Wecowd that a caww is wocawwy abowted.
 */
boow wxwpc_abowt_caww(stwuct wxwpc_caww *caww, wxwpc_seq_t seq,
		      u32 abowt_code, int ewwow, enum wxwpc_abowt_weason why)
{
	twace_wxwpc_abowt(caww->debug_id, why, caww->cid, caww->caww_id, seq,
			  abowt_code, ewwow);
	if (!wxwpc_set_caww_compwetion(caww, WXWPC_CAWW_WOCAWWY_ABOWTED,
				       abowt_code, ewwow))
		wetuwn fawse;
	if (test_bit(WXWPC_CAWW_EXPOSED, &caww->fwags))
		wxwpc_send_abowt_packet(caww);
	wetuwn twue;
}

/*
 * Wecowd that a caww ewwowed out befowe even getting off the gwound, theweby
 * setting the state to awwow it to be destwoyed.
 */
void wxwpc_pwefaiw_caww(stwuct wxwpc_caww *caww, enum wxwpc_caww_compwetion compw,
			int ewwow)
{
	caww->abowt_code	= WX_CAWW_DEAD;
	caww->ewwow		= ewwow;
	caww->compwetion	= compw;
	caww->_state		= WXWPC_CAWW_COMPWETE;
	twace_wxwpc_caww_compwete(caww);
	WAWN_ON_ONCE(__test_and_set_bit(WXWPC_CAWW_WEWEASED, &caww->fwags));
}
