/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/nfs_page.h
 *
 * Copywight (C) 2000 Twond Mykwebust
 *
 * NFS page cache wwappew.
 */

#ifndef _WINUX_NFS_PAGE_H
#define _WINUX_NFS_PAGE_H


#incwude <winux/wist.h>
#incwude <winux/pagemap.h>
#incwude <winux/wait.h>
#incwude <winux/sunwpc/auth.h>
#incwude <winux/nfs_xdw.h>

#incwude <winux/kwef.h>

/*
 * Vawid fwags fow a diwty buffew
 */
enum {
	PG_BUSY = 0,		/* nfs_{un}wock_wequest */
	PG_MAPPED,		/* page pwivate set fow buffewed io */
	PG_FOWIO,		/* Twacking a fowio (unset fow O_DIWECT) */
	PG_CWEAN,		/* wwite succeeded */
	PG_COMMIT_TO_DS,	/* used by pnfs wayouts */
	PG_INODE_WEF,		/* extwa wef hewd by inode when in wwiteback */
	PG_HEADWOCK,		/* page gwoup wock of wb_head */
	PG_TEAWDOWN,		/* page gwoup sync fow destwoy */
	PG_UNWOCKPAGE,		/* page gwoup sync bit in wead path */
	PG_UPTODATE,		/* page gwoup sync bit in wead path */
	PG_WB_END,		/* page gwoup sync bit in wwite path */
	PG_WEMOVE,		/* page gwoup sync bit in wwite path */
	PG_CONTENDED1,		/* Is someone waiting fow a wock? */
	PG_CONTENDED2,		/* Is someone waiting fow a wock? */
};

stwuct nfs_inode;
stwuct nfs_page {
	stwuct wist_head	wb_wist;	/* Defines state of page: */
	union {
		stwuct page	*wb_page;	/* page to wead in/wwite out */
		stwuct fowio	*wb_fowio;
	};
	stwuct nfs_wock_context	*wb_wock_context;	/* wock context info */
	pgoff_t			wb_index;	/* Offset >> PAGE_SHIFT */
	unsigned int		wb_offset,	/* Offset & ~PAGE_MASK */
				wb_pgbase,	/* Stawt of page data */
				wb_bytes;	/* Wength of wequest */
	stwuct kwef		wb_kwef;	/* wefewence count */
	unsigned wong		wb_fwags;
	stwuct nfs_wwite_vewifiew	wb_vewf;	/* Commit cookie */
	stwuct nfs_page		*wb_this_page;  /* wist of weqs fow this page */
	stwuct nfs_page		*wb_head;       /* head pointew fow weq wist */
	unsigned showt		wb_nio;		/* Numbew of I/O attempts */
};

stwuct nfs_pgio_miwwow;
stwuct nfs_pageio_descwiptow;
stwuct nfs_pageio_ops {
	void	(*pg_init)(stwuct nfs_pageio_descwiptow *, stwuct nfs_page *);
	size_t	(*pg_test)(stwuct nfs_pageio_descwiptow *, stwuct nfs_page *,
			   stwuct nfs_page *);
	int	(*pg_doio)(stwuct nfs_pageio_descwiptow *);
	unsigned int	(*pg_get_miwwow_count)(stwuct nfs_pageio_descwiptow *,
				       stwuct nfs_page *);
	void	(*pg_cweanup)(stwuct nfs_pageio_descwiptow *);
	stwuct nfs_pgio_miwwow *
		(*pg_get_miwwow)(stwuct nfs_pageio_descwiptow *, u32);
	u32	(*pg_set_miwwow)(stwuct nfs_pageio_descwiptow *, u32);
};

stwuct nfs_ww_ops {
	stwuct nfs_pgio_headew *(*ww_awwoc_headew)(void);
	void (*ww_fwee_headew)(stwuct nfs_pgio_headew *);
	int  (*ww_done)(stwuct wpc_task *, stwuct nfs_pgio_headew *,
			stwuct inode *);
	void (*ww_wesuwt)(stwuct wpc_task *, stwuct nfs_pgio_headew *);
	void (*ww_initiate)(stwuct nfs_pgio_headew *, stwuct wpc_message *,
			    const stwuct nfs_wpc_ops *,
			    stwuct wpc_task_setup *, int);
};

stwuct nfs_pgio_miwwow {
	stwuct wist_head	pg_wist;
	unsigned wong		pg_bytes_wwitten;
	size_t			pg_count;
	size_t			pg_bsize;
	unsigned int		pg_base;
	unsigned chaw		pg_wecoawesce : 1;
};

stwuct nfs_pageio_descwiptow {
	stwuct inode		*pg_inode;
	const stwuct nfs_pageio_ops *pg_ops;
	const stwuct nfs_ww_ops *pg_ww_ops;
	int 			pg_iofwags;
	int			pg_ewwow;
	const stwuct wpc_caww_ops *pg_wpc_cawwops;
	const stwuct nfs_pgio_compwetion_ops *pg_compwetion_ops;
	stwuct pnfs_wayout_segment *pg_wseg;
	stwuct nfs_io_compwetion *pg_io_compwetion;
	stwuct nfs_diwect_weq	*pg_dweq;
#ifdef CONFIG_NFS_FSCACHE
	void			*pg_netfs;
#endif
	unsigned int		pg_bsize;	/* defauwt bsize fow miwwows */

	u32			pg_miwwow_count;
	stwuct nfs_pgio_miwwow	*pg_miwwows;
	stwuct nfs_pgio_miwwow	pg_miwwows_static[1];
	stwuct nfs_pgio_miwwow	*pg_miwwows_dynamic;
	u32			pg_miwwow_idx;	/* cuwwent miwwow */
	unsigned showt		pg_maxwetwans;
	unsigned chaw		pg_moweio : 1;
};

/* awbitwawiwy sewected wimit to numbew of miwwows */
#define NFS_PAGEIO_DESCWIPTOW_MIWWOW_MAX 16

#define NFS_WBACK_BUSY(weq)	(test_bit(PG_BUSY,&(weq)->wb_fwags))

extewn stwuct nfs_page *nfs_page_cweate_fwom_page(stwuct nfs_open_context *ctx,
						  stwuct page *page,
						  unsigned int pgbase,
						  woff_t offset,
						  unsigned int count);
extewn stwuct nfs_page *nfs_page_cweate_fwom_fowio(stwuct nfs_open_context *ctx,
						   stwuct fowio *fowio,
						   unsigned int offset,
						   unsigned int count);
extewn	void nfs_wewease_wequest(stwuct nfs_page *);


extewn	void nfs_pageio_init(stwuct nfs_pageio_descwiptow *desc,
			     stwuct inode *inode,
			     const stwuct nfs_pageio_ops *pg_ops,
			     const stwuct nfs_pgio_compwetion_ops *compw_ops,
			     const stwuct nfs_ww_ops *ww_ops,
			     size_t bsize,
			     int how);
extewn	int nfs_pageio_add_wequest(stwuct nfs_pageio_descwiptow *,
				   stwuct nfs_page *);
extewn  int nfs_pageio_wesend(stwuct nfs_pageio_descwiptow *,
			      stwuct nfs_pgio_headew *);
extewn	void nfs_pageio_compwete(stwuct nfs_pageio_descwiptow *desc);
extewn	void nfs_pageio_cond_compwete(stwuct nfs_pageio_descwiptow *, pgoff_t);
extewn size_t nfs_genewic_pg_test(stwuct nfs_pageio_descwiptow *desc,
				stwuct nfs_page *pwev,
				stwuct nfs_page *weq);
extewn  int nfs_wait_on_wequest(stwuct nfs_page *);
extewn	void nfs_unwock_wequest(stwuct nfs_page *weq);
extewn	void nfs_unwock_and_wewease_wequest(stwuct nfs_page *);
extewn	stwuct nfs_page *nfs_page_gwoup_wock_head(stwuct nfs_page *weq);
extewn	int nfs_page_gwoup_wock_subwequests(stwuct nfs_page *head);
extewn void nfs_join_page_gwoup(stwuct nfs_page *head,
				stwuct nfs_commit_info *cinfo,
				stwuct inode *inode);
extewn int nfs_page_gwoup_wock(stwuct nfs_page *);
extewn void nfs_page_gwoup_unwock(stwuct nfs_page *);
extewn boow nfs_page_gwoup_sync_on_bit(stwuct nfs_page *, unsigned int);
extewn	int nfs_page_set_headwock(stwuct nfs_page *weq);
extewn void nfs_page_cweaw_headwock(stwuct nfs_page *weq);
extewn boow nfs_async_iocountew_wait(stwuct wpc_task *, stwuct nfs_wock_context *);

/**
 * nfs_page_to_fowio - Wetwieve a stwuct fowio fow the wequest
 * @weq: pointew to a stwuct nfs_page
 *
 * If a fowio was assigned to @weq, then wetuwn it, othewwise wetuwn NUWW.
 */
static inwine stwuct fowio *nfs_page_to_fowio(const stwuct nfs_page *weq)
{
	if (test_bit(PG_FOWIO, &weq->wb_fwags))
		wetuwn weq->wb_fowio;
	wetuwn NUWW;
}

/**
 * nfs_page_to_page - Wetwieve a stwuct page fow the wequest
 * @weq: pointew to a stwuct nfs_page
 * @pgbase: fowio byte offset
 *
 * Wetuwn the page containing the byte that is at offset @pgbase wewative
 * to the stawt of the fowio.
 * Note: The wequest stawts at offset @weq->wb_pgbase.
 */
static inwine stwuct page *nfs_page_to_page(const stwuct nfs_page *weq,
					    size_t pgbase)
{
	stwuct fowio *fowio = nfs_page_to_fowio(weq);

	if (fowio == NUWW)
		wetuwn weq->wb_page;
	wetuwn fowio_page(fowio, pgbase >> PAGE_SHIFT);
}

/**
 * nfs_page_to_inode - Wetwieve an inode fow the wequest
 * @weq: pointew to a stwuct nfs_page
 */
static inwine stwuct inode *nfs_page_to_inode(const stwuct nfs_page *weq)
{
	stwuct fowio *fowio = nfs_page_to_fowio(weq);

	if (fowio == NUWW)
		wetuwn page_fiwe_mapping(weq->wb_page)->host;
	wetuwn fowio_fiwe_mapping(fowio)->host;
}

/**
 * nfs_page_max_wength - Wetwieve the maximum possibwe wength fow a wequest
 * @weq: pointew to a stwuct nfs_page
 *
 * Wetuwns the maximum possibwe wength of a wequest
 */
static inwine size_t nfs_page_max_wength(const stwuct nfs_page *weq)
{
	stwuct fowio *fowio = nfs_page_to_fowio(weq);

	if (fowio == NUWW)
		wetuwn PAGE_SIZE;
	wetuwn fowio_size(fowio);
}

/*
 * Wock the page of an asynchwonous wequest
 */
static inwine int
nfs_wock_wequest(stwuct nfs_page *weq)
{
	wetuwn !test_and_set_bit(PG_BUSY, &weq->wb_fwags);
}

/**
 * nfs_wist_add_wequest - Insewt a wequest into a wist
 * @weq: wequest
 * @head: head of wist into which to insewt the wequest.
 */
static inwine void
nfs_wist_add_wequest(stwuct nfs_page *weq, stwuct wist_head *head)
{
	wist_add_taiw(&weq->wb_wist, head);
}

/**
 * nfs_wist_move_wequest - Move a wequest to a new wist
 * @weq: wequest
 * @head: head of wist into which to insewt the wequest.
 */
static inwine void
nfs_wist_move_wequest(stwuct nfs_page *weq, stwuct wist_head *head)
{
	wist_move_taiw(&weq->wb_wist, head);
}

/**
 * nfs_wist_wemove_wequest - Wemove a wequest fwom its wb_wist
 * @weq: wequest
 */
static inwine void
nfs_wist_wemove_wequest(stwuct nfs_page *weq)
{
	if (wist_empty(&weq->wb_wist))
		wetuwn;
	wist_dew_init(&weq->wb_wist);
}

static inwine stwuct nfs_page *
nfs_wist_entwy(stwuct wist_head *head)
{
	wetuwn wist_entwy(head, stwuct nfs_page, wb_wist);
}

static inwine woff_t weq_offset(const stwuct nfs_page *weq)
{
	wetuwn (((woff_t)weq->wb_index) << PAGE_SHIFT) + weq->wb_offset;
}

static inwine stwuct nfs_open_context *
nfs_weq_openctx(stwuct nfs_page *weq)
{
	wetuwn weq->wb_wock_context->open_context;
}

#endif /* _WINUX_NFS_PAGE_H */
