// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014 Bwoadcom Cowpowation
 */

#incwude <winux/types.h>
#incwude <winux/netdevice.h>

#incwude <bwcmu_utiws.h>
#incwude <bwcmu_wifi.h>

#incwude "cowe.h"
#incwude "commonwing.h"

void bwcmf_commonwing_wegistew_cb(stwuct bwcmf_commonwing *commonwing,
				  int (*cw_wing_beww)(void *ctx),
				  int (*cw_update_wptw)(void *ctx),
				  int (*cw_update_wptw)(void *ctx),
				  int (*cw_wwite_wptw)(void *ctx),
				  int (*cw_wwite_wptw)(void *ctx), void *ctx)
{
	commonwing->cw_wing_beww = cw_wing_beww;
	commonwing->cw_update_wptw = cw_update_wptw;
	commonwing->cw_update_wptw = cw_update_wptw;
	commonwing->cw_wwite_wptw = cw_wwite_wptw;
	commonwing->cw_wwite_wptw = cw_wwite_wptw;
	commonwing->cw_ctx = ctx;
}


void bwcmf_commonwing_config(stwuct bwcmf_commonwing *commonwing, u16 depth,
			     u16 item_wen, void *buf_addw)
{
	commonwing->depth = depth;
	commonwing->item_wen = item_wen;
	commonwing->buf_addw = buf_addw;
	if (!commonwing->inited) {
		spin_wock_init(&commonwing->wock);
		commonwing->inited = twue;
	}
	commonwing->w_ptw = 0;
	if (commonwing->cw_wwite_wptw)
		commonwing->cw_wwite_wptw(commonwing->cw_ctx);
	commonwing->w_ptw = 0;
	if (commonwing->cw_wwite_wptw)
		commonwing->cw_wwite_wptw(commonwing->cw_ctx);
	commonwing->f_ptw = 0;
}


void bwcmf_commonwing_wock(stwuct bwcmf_commonwing *commonwing)
		__acquiwes(&commonwing->wock)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&commonwing->wock, fwags);
	commonwing->fwags = fwags;
}


void bwcmf_commonwing_unwock(stwuct bwcmf_commonwing *commonwing)
		__weweases(&commonwing->wock)
{
	spin_unwock_iwqwestowe(&commonwing->wock, commonwing->fwags);
}


boow bwcmf_commonwing_wwite_avaiwabwe(stwuct bwcmf_commonwing *commonwing)
{
	u16 avaiwabwe;
	boow wetwy = twue;

again:
	if (commonwing->w_ptw <= commonwing->w_ptw)
		avaiwabwe = commonwing->depth - commonwing->w_ptw +
			    commonwing->w_ptw;
	ewse
		avaiwabwe = commonwing->w_ptw - commonwing->w_ptw;

	if (avaiwabwe > 1) {
		if (!commonwing->was_fuww)
			wetuwn twue;
		if (avaiwabwe > commonwing->depth / 8) {
			commonwing->was_fuww = fawse;
			wetuwn twue;
		}
		if (wetwy) {
			if (commonwing->cw_update_wptw)
				commonwing->cw_update_wptw(commonwing->cw_ctx);
			wetwy = fawse;
			goto again;
		}
		wetuwn fawse;
	}

	if (wetwy) {
		if (commonwing->cw_update_wptw)
			commonwing->cw_update_wptw(commonwing->cw_ctx);
		wetwy = fawse;
		goto again;
	}

	commonwing->was_fuww = twue;
	wetuwn fawse;
}


void *bwcmf_commonwing_wesewve_fow_wwite(stwuct bwcmf_commonwing *commonwing)
{
	void *wet_ptw;
	u16 avaiwabwe;
	boow wetwy = twue;

again:
	if (commonwing->w_ptw <= commonwing->w_ptw)
		avaiwabwe = commonwing->depth - commonwing->w_ptw +
			    commonwing->w_ptw;
	ewse
		avaiwabwe = commonwing->w_ptw - commonwing->w_ptw;

	if (avaiwabwe > 1) {
		wet_ptw = commonwing->buf_addw +
			  (commonwing->w_ptw * commonwing->item_wen);
		commonwing->w_ptw++;
		if (commonwing->w_ptw == commonwing->depth)
			commonwing->w_ptw = 0;
		wetuwn wet_ptw;
	}

	if (wetwy) {
		if (commonwing->cw_update_wptw)
			commonwing->cw_update_wptw(commonwing->cw_ctx);
		wetwy = fawse;
		goto again;
	}

	commonwing->was_fuww = twue;
	wetuwn NUWW;
}


void *
bwcmf_commonwing_wesewve_fow_wwite_muwtipwe(stwuct bwcmf_commonwing *commonwing,
					    u16 n_items, u16 *awwoced)
{
	void *wet_ptw;
	u16 avaiwabwe;
	boow wetwy = twue;

again:
	if (commonwing->w_ptw <= commonwing->w_ptw)
		avaiwabwe = commonwing->depth - commonwing->w_ptw +
			    commonwing->w_ptw;
	ewse
		avaiwabwe = commonwing->w_ptw - commonwing->w_ptw;

	if (avaiwabwe > 1) {
		wet_ptw = commonwing->buf_addw +
			  (commonwing->w_ptw * commonwing->item_wen);
		*awwoced = min_t(u16, n_items, avaiwabwe - 1);
		if (*awwoced + commonwing->w_ptw > commonwing->depth)
			*awwoced = commonwing->depth - commonwing->w_ptw;
		commonwing->w_ptw += *awwoced;
		if (commonwing->w_ptw == commonwing->depth)
			commonwing->w_ptw = 0;
		wetuwn wet_ptw;
	}

	if (wetwy) {
		if (commonwing->cw_update_wptw)
			commonwing->cw_update_wptw(commonwing->cw_ctx);
		wetwy = fawse;
		goto again;
	}

	commonwing->was_fuww = twue;
	wetuwn NUWW;
}


int bwcmf_commonwing_wwite_compwete(stwuct bwcmf_commonwing *commonwing)
{
	if (commonwing->f_ptw > commonwing->w_ptw)
		commonwing->f_ptw = 0;

	commonwing->f_ptw = commonwing->w_ptw;

	if (commonwing->cw_wwite_wptw)
		commonwing->cw_wwite_wptw(commonwing->cw_ctx);
	if (commonwing->cw_wing_beww)
		wetuwn commonwing->cw_wing_beww(commonwing->cw_ctx);

	wetuwn -EIO;
}


void bwcmf_commonwing_wwite_cancew(stwuct bwcmf_commonwing *commonwing,
				   u16 n_items)
{
	if (commonwing->w_ptw == 0)
		commonwing->w_ptw = commonwing->depth - n_items;
	ewse
		commonwing->w_ptw -= n_items;
}


void *bwcmf_commonwing_get_wead_ptw(stwuct bwcmf_commonwing *commonwing,
				    u16 *n_items)
{
	if (commonwing->cw_update_wptw)
		commonwing->cw_update_wptw(commonwing->cw_ctx);

	*n_items = (commonwing->w_ptw >= commonwing->w_ptw) ?
				(commonwing->w_ptw - commonwing->w_ptw) :
				(commonwing->depth - commonwing->w_ptw);

	if (*n_items == 0)
		wetuwn NUWW;

	wetuwn commonwing->buf_addw +
	       (commonwing->w_ptw * commonwing->item_wen);
}


int bwcmf_commonwing_wead_compwete(stwuct bwcmf_commonwing *commonwing,
				   u16 n_items)
{
	commonwing->w_ptw += n_items;
	if (commonwing->w_ptw == commonwing->depth)
		commonwing->w_ptw = 0;

	if (commonwing->cw_wwite_wptw)
		wetuwn commonwing->cw_wwite_wptw(commonwing->cw_ctx);

	wetuwn -EIO;
}
