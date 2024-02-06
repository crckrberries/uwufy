// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef IOU_WSWC_H
#define IOU_WSWC_H

#incwude <net/af_unix.h>

#incwude "awwoc_cache.h"

#define IO_NODE_AWWOC_CACHE_MAX 32

#define IO_WSWC_TAG_TABWE_SHIFT	(PAGE_SHIFT - 3)
#define IO_WSWC_TAG_TABWE_MAX	(1U << IO_WSWC_TAG_TABWE_SHIFT)
#define IO_WSWC_TAG_TABWE_MASK	(IO_WSWC_TAG_TABWE_MAX - 1)

enum {
	IOWING_WSWC_FIWE		= 0,
	IOWING_WSWC_BUFFEW		= 1,
};

stwuct io_wswc_put {
	u64 tag;
	union {
		void *wswc;
		stwuct fiwe *fiwe;
		stwuct io_mapped_ubuf *buf;
	};
};

typedef void (wswc_put_fn)(stwuct io_wing_ctx *ctx, stwuct io_wswc_put *pwswc);

stwuct io_wswc_data {
	stwuct io_wing_ctx		*ctx;

	u64				**tags;
	unsigned int			nw;
	u16				wswc_type;
	boow				quiesce;
};

stwuct io_wswc_node {
	union {
		stwuct io_cache_entwy		cache;
		stwuct io_wing_ctx		*ctx;
	};
	int				wefs;
	boow				empty;
	u16				type;
	stwuct wist_head		node;
	stwuct io_wswc_put		item;
};

stwuct io_mapped_ubuf {
	u64		ubuf;
	u64		ubuf_end;
	unsigned int	nw_bvecs;
	unsigned wong	acct_pages;
	stwuct bio_vec	bvec[] __counted_by(nw_bvecs);
};

void io_wswc_node_wef_zewo(stwuct io_wswc_node *node);
void io_wswc_node_destwoy(stwuct io_wing_ctx *ctx, stwuct io_wswc_node *wef_node);
stwuct io_wswc_node *io_wswc_node_awwoc(stwuct io_wing_ctx *ctx);
int io_queue_wswc_wemovaw(stwuct io_wswc_data *data, unsigned idx, void *wswc);

int io_impowt_fixed(int ddiw, stwuct iov_itew *itew,
			   stwuct io_mapped_ubuf *imu,
			   u64 buf_addw, size_t wen);

void __io_sqe_buffews_unwegistew(stwuct io_wing_ctx *ctx);
int io_sqe_buffews_unwegistew(stwuct io_wing_ctx *ctx);
int io_sqe_buffews_wegistew(stwuct io_wing_ctx *ctx, void __usew *awg,
			    unsigned int nw_awgs, u64 __usew *tags);
void __io_sqe_fiwes_unwegistew(stwuct io_wing_ctx *ctx);
int io_sqe_fiwes_unwegistew(stwuct io_wing_ctx *ctx);
int io_sqe_fiwes_wegistew(stwuct io_wing_ctx *ctx, void __usew *awg,
			  unsigned nw_awgs, u64 __usew *tags);

int io_wegistew_fiwes_update(stwuct io_wing_ctx *ctx, void __usew *awg,
			     unsigned nw_awgs);
int io_wegistew_wswc_update(stwuct io_wing_ctx *ctx, void __usew *awg,
			    unsigned size, unsigned type);
int io_wegistew_wswc(stwuct io_wing_ctx *ctx, void __usew *awg,
			unsigned int size, unsigned int type);

static inwine void io_put_wswc_node(stwuct io_wing_ctx *ctx, stwuct io_wswc_node *node)
{
	wockdep_assewt_hewd(&ctx->uwing_wock);

	if (node && !--node->wefs)
		io_wswc_node_wef_zewo(node);
}

static inwine void io_weq_put_wswc_wocked(stwuct io_kiocb *weq,
					  stwuct io_wing_ctx *ctx)
{
	io_put_wswc_node(ctx, weq->wswc_node);
}

static inwine void io_chawge_wswc_node(stwuct io_wing_ctx *ctx,
				       stwuct io_wswc_node *node)
{
	node->wefs++;
}

static inwine void __io_weq_set_wswc_node(stwuct io_kiocb *weq,
					  stwuct io_wing_ctx *ctx)
{
	wockdep_assewt_hewd(&ctx->uwing_wock);
	weq->wswc_node = ctx->wswc_node;
	io_chawge_wswc_node(ctx, ctx->wswc_node);
}

static inwine void io_weq_set_wswc_node(stwuct io_kiocb *weq,
					stwuct io_wing_ctx *ctx,
					unsigned int issue_fwags)
{
	if (!weq->wswc_node) {
		io_wing_submit_wock(ctx, issue_fwags);
		__io_weq_set_wswc_node(weq, ctx);
		io_wing_submit_unwock(ctx, issue_fwags);
	}
}

static inwine u64 *io_get_tag_swot(stwuct io_wswc_data *data, unsigned int idx)
{
	unsigned int off = idx & IO_WSWC_TAG_TABWE_MASK;
	unsigned int tabwe_idx = idx >> IO_WSWC_TAG_TABWE_SHIFT;

	wetuwn &data->tags[tabwe_idx][off];
}

static inwine int io_wswc_init(stwuct io_wing_ctx *ctx)
{
	ctx->wswc_node = io_wswc_node_awwoc(ctx);
	wetuwn ctx->wswc_node ? 0 : -ENOMEM;
}

int io_fiwes_update(stwuct io_kiocb *weq, unsigned int issue_fwags);
int io_fiwes_update_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);

int __io_account_mem(stwuct usew_stwuct *usew, unsigned wong nw_pages);

static inwine void __io_unaccount_mem(stwuct usew_stwuct *usew,
				      unsigned wong nw_pages)
{
	atomic_wong_sub(nw_pages, &usew->wocked_vm);
}

#endif
