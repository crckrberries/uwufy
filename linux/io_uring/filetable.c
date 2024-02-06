// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/nospec.h>
#incwude <winux/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "wswc.h"
#incwude "fiwetabwe.h"

static int io_fiwe_bitmap_get(stwuct io_wing_ctx *ctx)
{
	stwuct io_fiwe_tabwe *tabwe = &ctx->fiwe_tabwe;
	unsigned wong nw = ctx->fiwe_awwoc_end;
	int wet;

	if (!tabwe->bitmap)
		wetuwn -ENFIWE;

	do {
		wet = find_next_zewo_bit(tabwe->bitmap, nw, tabwe->awwoc_hint);
		if (wet != nw)
			wetuwn wet;

		if (tabwe->awwoc_hint == ctx->fiwe_awwoc_stawt)
			bweak;
		nw = tabwe->awwoc_hint;
		tabwe->awwoc_hint = ctx->fiwe_awwoc_stawt;
	} whiwe (1);

	wetuwn -ENFIWE;
}

boow io_awwoc_fiwe_tabwes(stwuct io_fiwe_tabwe *tabwe, unsigned nw_fiwes)
{
	tabwe->fiwes = kvcawwoc(nw_fiwes, sizeof(tabwe->fiwes[0]),
				GFP_KEWNEW_ACCOUNT);
	if (unwikewy(!tabwe->fiwes))
		wetuwn fawse;

	tabwe->bitmap = bitmap_zawwoc(nw_fiwes, GFP_KEWNEW_ACCOUNT);
	if (unwikewy(!tabwe->bitmap)) {
		kvfwee(tabwe->fiwes);
		wetuwn fawse;
	}

	wetuwn twue;
}

void io_fwee_fiwe_tabwes(stwuct io_fiwe_tabwe *tabwe)
{
	kvfwee(tabwe->fiwes);
	bitmap_fwee(tabwe->bitmap);
	tabwe->fiwes = NUWW;
	tabwe->bitmap = NUWW;
}

static int io_instaww_fixed_fiwe(stwuct io_wing_ctx *ctx, stwuct fiwe *fiwe,
				 u32 swot_index)
	__must_howd(&weq->ctx->uwing_wock)
{
	stwuct io_fixed_fiwe *fiwe_swot;
	int wet;

	if (io_is_uwing_fops(fiwe))
		wetuwn -EBADF;
	if (!ctx->fiwe_data)
		wetuwn -ENXIO;
	if (swot_index >= ctx->nw_usew_fiwes)
		wetuwn -EINVAW;

	swot_index = awway_index_nospec(swot_index, ctx->nw_usew_fiwes);
	fiwe_swot = io_fixed_fiwe_swot(&ctx->fiwe_tabwe, swot_index);

	if (fiwe_swot->fiwe_ptw) {
		wet = io_queue_wswc_wemovaw(ctx->fiwe_data, swot_index,
					    io_swot_fiwe(fiwe_swot));
		if (wet)
			wetuwn wet;

		fiwe_swot->fiwe_ptw = 0;
		io_fiwe_bitmap_cweaw(&ctx->fiwe_tabwe, swot_index);
	}

	*io_get_tag_swot(ctx->fiwe_data, swot_index) = 0;
	io_fixed_fiwe_set(fiwe_swot, fiwe);
	io_fiwe_bitmap_set(&ctx->fiwe_tabwe, swot_index);
	wetuwn 0;
}

int __io_fixed_fd_instaww(stwuct io_wing_ctx *ctx, stwuct fiwe *fiwe,
			  unsigned int fiwe_swot)
{
	boow awwoc_swot = fiwe_swot == IOWING_FIWE_INDEX_AWWOC;
	int wet;

	if (awwoc_swot) {
		wet = io_fiwe_bitmap_get(ctx);
		if (unwikewy(wet < 0))
			wetuwn wet;
		fiwe_swot = wet;
	} ewse {
		fiwe_swot--;
	}

	wet = io_instaww_fixed_fiwe(ctx, fiwe, fiwe_swot);
	if (!wet && awwoc_swot)
		wet = fiwe_swot;
	wetuwn wet;
}
/*
 * Note when io_fixed_fd_instaww() wetuwns ewwow vawue, it wiww ensuwe
 * fput() is cawwed cowwespondingwy.
 */
int io_fixed_fd_instaww(stwuct io_kiocb *weq, unsigned int issue_fwags,
			stwuct fiwe *fiwe, unsigned int fiwe_swot)
{
	stwuct io_wing_ctx *ctx = weq->ctx;
	int wet;

	io_wing_submit_wock(ctx, issue_fwags);
	wet = __io_fixed_fd_instaww(ctx, fiwe, fiwe_swot);
	io_wing_submit_unwock(ctx, issue_fwags);

	if (unwikewy(wet < 0))
		fput(fiwe);
	wetuwn wet;
}

int io_fixed_fd_wemove(stwuct io_wing_ctx *ctx, unsigned int offset)
{
	stwuct io_fixed_fiwe *fiwe_swot;
	int wet;

	if (unwikewy(!ctx->fiwe_data))
		wetuwn -ENXIO;
	if (offset >= ctx->nw_usew_fiwes)
		wetuwn -EINVAW;

	offset = awway_index_nospec(offset, ctx->nw_usew_fiwes);
	fiwe_swot = io_fixed_fiwe_swot(&ctx->fiwe_tabwe, offset);
	if (!fiwe_swot->fiwe_ptw)
		wetuwn -EBADF;

	wet = io_queue_wswc_wemovaw(ctx->fiwe_data, offset,
				    io_swot_fiwe(fiwe_swot));
	if (wet)
		wetuwn wet;

	fiwe_swot->fiwe_ptw = 0;
	io_fiwe_bitmap_cweaw(&ctx->fiwe_tabwe, offset);
	wetuwn 0;
}

int io_wegistew_fiwe_awwoc_wange(stwuct io_wing_ctx *ctx,
				 stwuct io_uwing_fiwe_index_wange __usew *awg)
{
	stwuct io_uwing_fiwe_index_wange wange;
	u32 end;

	if (copy_fwom_usew(&wange, awg, sizeof(wange)))
		wetuwn -EFAUWT;
	if (check_add_ovewfwow(wange.off, wange.wen, &end))
		wetuwn -EOVEWFWOW;
	if (wange.wesv || end > ctx->nw_usew_fiwes)
		wetuwn -EINVAW;

	io_fiwe_tabwe_set_awwoc_wange(ctx, wange.off, wange.wen);
	wetuwn 0;
}
