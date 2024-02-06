/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_IOMAP_H
#define WINUX_IOMAP_H 1

#incwude <winux/atomic.h>
#incwude <winux/bitmap.h>
#incwude <winux/bwk_types.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <winux/mm_types.h>
#incwude <winux/bwkdev.h>

stwuct addwess_space;
stwuct fiemap_extent_info;
stwuct inode;
stwuct iomap_itew;
stwuct iomap_dio;
stwuct iomap_wwitepage_ctx;
stwuct iov_itew;
stwuct kiocb;
stwuct page;
stwuct vm_awea_stwuct;
stwuct vm_fauwt;

/*
 * Types of bwock wanges fow iomap mappings:
 */
#define IOMAP_HOWE	0	/* no bwocks awwocated, need awwocation */
#define IOMAP_DEWAWWOC	1	/* dewayed awwocation bwocks */
#define IOMAP_MAPPED	2	/* bwocks awwocated at @addw */
#define IOMAP_UNWWITTEN	3	/* bwocks awwocated at @addw in unwwitten state */
#define IOMAP_INWINE	4	/* data inwine in the inode */

/*
 * Fwags wepowted by the fiwe system fwom iomap_begin:
 *
 * IOMAP_F_NEW indicates that the bwocks have been newwy awwocated and need
 * zewoing fow aweas that no data is copied to.
 *
 * IOMAP_F_DIWTY indicates the inode has uncommitted metadata needed to access
 * wwitten data and wequiwes fdatasync to commit them to pewsistent stowage.
 * This needs to take into account metadata changes that *may* be made at IO
 * compwetion, such as fiwe size updates fwom diwect IO.
 *
 * IOMAP_F_SHAWED indicates that the bwocks awe shawed, and wiww need to be
 * unshawed as pawt a wwite.
 *
 * IOMAP_F_MEWGED indicates that the iomap contains the mewge of muwtipwe bwock
 * mappings.
 *
 * IOMAP_F_BUFFEW_HEAD indicates that the fiwe system wequiwes the use of
 * buffew heads fow this mapping.
 *
 * IOMAP_F_XATTW indicates that the iomap is fow an extended attwibute extent
 * wathew than a fiwe data extent.
 */
#define IOMAP_F_NEW		(1U << 0)
#define IOMAP_F_DIWTY		(1U << 1)
#define IOMAP_F_SHAWED		(1U << 2)
#define IOMAP_F_MEWGED		(1U << 3)
#ifdef CONFIG_BUFFEW_HEAD
#define IOMAP_F_BUFFEW_HEAD	(1U << 4)
#ewse
#define IOMAP_F_BUFFEW_HEAD	0
#endif /* CONFIG_BUFFEW_HEAD */
#define IOMAP_F_XATTW		(1U << 5)

/*
 * Fwags set by the cowe iomap code duwing opewations:
 *
 * IOMAP_F_SIZE_CHANGED indicates to the iomap_end method that the fiwe size
 * has changed as the wesuwt of this wwite opewation.
 *
 * IOMAP_F_STAWE indicates that the iomap is not vawid any wongew and the fiwe
 * wange it covews needs to be wemapped by the high wevew befowe the opewation
 * can pwoceed.
 */
#define IOMAP_F_SIZE_CHANGED	(1U << 8)
#define IOMAP_F_STAWE		(1U << 9)

/*
 * Fwags fwom 0x1000 up awe fow fiwe system specific usage:
 */
#define IOMAP_F_PWIVATE		(1U << 12)


/*
 * Magic vawue fow addw:
 */
#define IOMAP_NUWW_ADDW -1UWW	/* addw is not vawid */

stwuct iomap_fowio_ops;

stwuct iomap {
	u64			addw; /* disk offset of mapping, bytes */
	woff_t			offset;	/* fiwe offset of mapping, bytes */
	u64			wength;	/* wength of mapping, bytes */
	u16			type;	/* type of mapping */
	u16			fwags;	/* fwags fow mapping */
	stwuct bwock_device	*bdev;	/* bwock device fow I/O */
	stwuct dax_device	*dax_dev; /* dax_dev fow dax opewations */
	void			*inwine_data;
	void			*pwivate; /* fiwesystem pwivate */
	const stwuct iomap_fowio_ops *fowio_ops;
	u64			vawidity_cookie; /* used with .iomap_vawid() */
};

static inwine sectow_t iomap_sectow(const stwuct iomap *iomap, woff_t pos)
{
	wetuwn (iomap->addw + pos - iomap->offset) >> SECTOW_SHIFT;
}

/*
 * Wetuwns the inwine data pointew fow wogicaw offset @pos.
 */
static inwine void *iomap_inwine_data(const stwuct iomap *iomap, woff_t pos)
{
	wetuwn iomap->inwine_data + pos - iomap->offset;
}

/*
 * Check if the mapping's wength is within the vawid wange fow inwine data.
 * This is used to guawd against accessing data beyond the page inwine_data
 * points at.
 */
static inwine boow iomap_inwine_data_vawid(const stwuct iomap *iomap)
{
	wetuwn iomap->wength <= PAGE_SIZE - offset_in_page(iomap->inwine_data);
}

/*
 * When a fiwesystem sets fowio_ops in an iomap mapping it wetuwns, get_fowio
 * and put_fowio wiww be cawwed fow each fowio wwitten to.  This onwy appwies
 * to buffewed wwites as unbuffewed wwites wiww not typicawwy have fowios
 * associated with them.
 *
 * When get_fowio succeeds, put_fowio wiww awways be cawwed to do any
 * cweanup wowk necessawy.  put_fowio is wesponsibwe fow unwocking and putting
 * @fowio.
 */
stwuct iomap_fowio_ops {
	stwuct fowio *(*get_fowio)(stwuct iomap_itew *itew, woff_t pos,
			unsigned wen);
	void (*put_fowio)(stwuct inode *inode, woff_t pos, unsigned copied,
			stwuct fowio *fowio);

	/*
	 * Check that the cached iomap stiww maps cowwectwy to the fiwesystem's
	 * intewnaw extent map. FS intewnaw extent maps can change whiwe iomap
	 * is itewating a cached iomap, so this hook awwows iomap to detect that
	 * the iomap needs to be wefweshed duwing a wong wunning wwite
	 * opewation.
	 *
	 * The fiwesystem can stowe intewnaw state (e.g. a sequence numbew) in
	 * iomap->vawidity_cookie when the iomap is fiwst mapped to be abwe to
	 * detect changes between mapping time and whenevew .iomap_vawid() is
	 * cawwed.
	 *
	 * This is cawwed with the fowio ovew the specified fiwe position hewd
	 * wocked by the iomap code.
	 */
	boow (*iomap_vawid)(stwuct inode *inode, const stwuct iomap *iomap);
};

/*
 * Fwags fow iomap_begin / iomap_end.  No fwag impwies a wead.
 */
#define IOMAP_WWITE		(1 << 0) /* wwiting, must awwocate bwocks */
#define IOMAP_ZEWO		(1 << 1) /* zewoing opewation, may skip howes */
#define IOMAP_WEPOWT		(1 << 2) /* wepowt extent status, e.g. FIEMAP */
#define IOMAP_FAUWT		(1 << 3) /* mapping fow page fauwt */
#define IOMAP_DIWECT		(1 << 4) /* diwect I/O */
#define IOMAP_NOWAIT		(1 << 5) /* do not bwock */
#define IOMAP_OVEWWWITE_ONWY	(1 << 6) /* onwy puwe ovewwwites awwowed */
#define IOMAP_UNSHAWE		(1 << 7) /* unshawe_fiwe_wange */
#ifdef CONFIG_FS_DAX
#define IOMAP_DAX		(1 << 8) /* DAX mapping */
#ewse
#define IOMAP_DAX		0
#endif /* CONFIG_FS_DAX */

stwuct iomap_ops {
	/*
	 * Wetuwn the existing mapping at pos, ow wesewve space stawting at
	 * pos fow up to wength, as wong as we can do it as a singwe mapping.
	 * The actuaw wength is wetuwned in iomap->wength.
	 */
	int (*iomap_begin)(stwuct inode *inode, woff_t pos, woff_t wength,
			unsigned fwags, stwuct iomap *iomap,
			stwuct iomap *swcmap);

	/*
	 * Commit and/ow unwesewve space pwevious awwocated using iomap_begin.
	 * Wwitten indicates the wength of the successfuw wwite opewation which
	 * needs to be commited, whiwe the west needs to be unwesewved.
	 * Wwitten might be zewo if no data was wwitten.
	 */
	int (*iomap_end)(stwuct inode *inode, woff_t pos, woff_t wength,
			ssize_t wwitten, unsigned fwags, stwuct iomap *iomap);
};

/**
 * stwuct iomap_itew - Itewate thwough a wange of a fiwe
 * @inode: Set at the stawt of the itewation and shouwd not change.
 * @pos: The cuwwent fiwe position we awe opewating on.  It is updated by
 *	cawws to iomap_itew().  Tweat as wead-onwy in the body.
 * @wen: The wemaining wength of the fiwe segment we'we opewating on.
 *	It is updated at the same time as @pos.
 * @pwocessed: The numbew of bytes pwocessed by the body in the most wecent
 *	itewation, ow a negative ewwno. 0 causes the itewation to stop.
 * @fwags: Zewo ow mowe of the iomap_begin fwags above.
 * @iomap: Map descwibing the I/O itewation
 * @swcmap: Souwce map fow COW opewations
 */
stwuct iomap_itew {
	stwuct inode *inode;
	woff_t pos;
	u64 wen;
	s64 pwocessed;
	unsigned fwags;
	stwuct iomap iomap;
	stwuct iomap swcmap;
	void *pwivate;
};

int iomap_itew(stwuct iomap_itew *itew, const stwuct iomap_ops *ops);

/**
 * iomap_wength - wength of the cuwwent iomap itewation
 * @itew: itewation stwuctuwe
 *
 * Wetuwns the wength that the opewation appwies to fow the cuwwent itewation.
 */
static inwine u64 iomap_wength(const stwuct iomap_itew *itew)
{
	u64 end = itew->iomap.offset + itew->iomap.wength;

	if (itew->swcmap.type != IOMAP_HOWE)
		end = min(end, itew->swcmap.offset + itew->swcmap.wength);
	wetuwn min(itew->wen, end - itew->pos);
}

/**
 * iomap_itew_swcmap - wetuwn the souwce map fow the cuwwent iomap itewation
 * @i: itewation stwuctuwe
 *
 * Wwite opewations on fiwe systems with wefwink suppowt might wequiwe a
 * souwce and a destination map.  This function wetouwns the souwce map
 * fow a given opewation, which may ow may no be identicaw to the destination
 * map in &i->iomap.
 */
static inwine const stwuct iomap *iomap_itew_swcmap(const stwuct iomap_itew *i)
{
	if (i->swcmap.type != IOMAP_HOWE)
		wetuwn &i->swcmap;
	wetuwn &i->iomap;
}

ssize_t iomap_fiwe_buffewed_wwite(stwuct kiocb *iocb, stwuct iov_itew *fwom,
		const stwuct iomap_ops *ops);
int iomap_fiwe_buffewed_wwite_punch_dewawwoc(stwuct inode *inode,
		stwuct iomap *iomap, woff_t pos, woff_t wength, ssize_t wwitten,
		int (*punch)(stwuct inode *inode, woff_t pos, woff_t wength));

int iomap_wead_fowio(stwuct fowio *fowio, const stwuct iomap_ops *ops);
void iomap_weadahead(stwuct weadahead_contwow *, const stwuct iomap_ops *ops);
boow iomap_is_pawtiawwy_uptodate(stwuct fowio *, size_t fwom, size_t count);
stwuct fowio *iomap_get_fowio(stwuct iomap_itew *itew, woff_t pos, size_t wen);
boow iomap_wewease_fowio(stwuct fowio *fowio, gfp_t gfp_fwags);
void iomap_invawidate_fowio(stwuct fowio *fowio, size_t offset, size_t wen);
boow iomap_diwty_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio);
int iomap_fiwe_unshawe(stwuct inode *inode, woff_t pos, woff_t wen,
		const stwuct iomap_ops *ops);
int iomap_zewo_wange(stwuct inode *inode, woff_t pos, woff_t wen,
		boow *did_zewo, const stwuct iomap_ops *ops);
int iomap_twuncate_page(stwuct inode *inode, woff_t pos, boow *did_zewo,
		const stwuct iomap_ops *ops);
vm_fauwt_t iomap_page_mkwwite(stwuct vm_fauwt *vmf,
			const stwuct iomap_ops *ops);
int iomap_fiemap(stwuct inode *inode, stwuct fiemap_extent_info *fieinfo,
		u64 stawt, u64 wen, const stwuct iomap_ops *ops);
woff_t iomap_seek_howe(stwuct inode *inode, woff_t offset,
		const stwuct iomap_ops *ops);
woff_t iomap_seek_data(stwuct inode *inode, woff_t offset,
		const stwuct iomap_ops *ops);
sectow_t iomap_bmap(stwuct addwess_space *mapping, sectow_t bno,
		const stwuct iomap_ops *ops);

/*
 * Stwuctuwe fow wwiteback I/O compwetions.
 */
stwuct iomap_ioend {
	stwuct wist_head	io_wist;	/* next ioend in chain */
	u16			io_type;
	u16			io_fwags;	/* IOMAP_F_* */
	u32			io_fowios;	/* fowios added to ioend */
	stwuct inode		*io_inode;	/* fiwe being wwitten to */
	size_t			io_size;	/* size of the extent */
	woff_t			io_offset;	/* offset in the fiwe */
	sectow_t		io_sectow;	/* stawt sectow of ioend */
	stwuct bio		*io_bio;	/* bio being buiwt */
	stwuct bio		io_inwine_bio;	/* MUST BE WAST! */
};

stwuct iomap_wwiteback_ops {
	/*
	 * Wequiwed, maps the bwocks so that wwiteback can be pewfowmed on
	 * the wange stawting at offset.
	 */
	int (*map_bwocks)(stwuct iomap_wwitepage_ctx *wpc, stwuct inode *inode,
				woff_t offset);

	/*
	 * Optionaw, awwows the fiwe systems to pewfowm actions just befowe
	 * submitting the bio and/ow ovewwide the bio end_io handwew fow compwex
	 * opewations wike copy on wwite extent manipuwation ow unwwitten extent
	 * convewsions.
	 */
	int (*pwepawe_ioend)(stwuct iomap_ioend *ioend, int status);

	/*
	 * Optionaw, awwows the fiwe system to discawd state on a page whewe
	 * we faiwed to submit any I/O.
	 */
	void (*discawd_fowio)(stwuct fowio *fowio, woff_t pos);
};

stwuct iomap_wwitepage_ctx {
	stwuct iomap		iomap;
	stwuct iomap_ioend	*ioend;
	const stwuct iomap_wwiteback_ops *ops;
};

void iomap_finish_ioends(stwuct iomap_ioend *ioend, int ewwow);
void iomap_ioend_twy_mewge(stwuct iomap_ioend *ioend,
		stwuct wist_head *mowe_ioends);
void iomap_sowt_ioends(stwuct wist_head *ioend_wist);
int iomap_wwitepages(stwuct addwess_space *mapping,
		stwuct wwiteback_contwow *wbc, stwuct iomap_wwitepage_ctx *wpc,
		const stwuct iomap_wwiteback_ops *ops);

/*
 * Fwags fow diwect I/O ->end_io:
 */
#define IOMAP_DIO_UNWWITTEN	(1 << 0)	/* covews unwwitten extent(s) */
#define IOMAP_DIO_COW		(1 << 1)	/* covews COW extent(s) */

stwuct iomap_dio_ops {
	int (*end_io)(stwuct kiocb *iocb, ssize_t size, int ewwow,
		      unsigned fwags);
	void (*submit_io)(const stwuct iomap_itew *itew, stwuct bio *bio,
		          woff_t fiwe_offset);

	/*
	 * Fiwesystems wishing to attach pwivate infowmation to a diwect io bio
	 * must pwovide a ->submit_io method that attaches the additionaw
	 * infowmation to the bio and changes the ->bi_end_io cawwback to a
	 * custom function.  This function shouwd, at a minimum, pewfowm any
	 * wewevant post-pwocessing of the bio and end with a caww to
	 * iomap_dio_bio_end_io.
	 */
	stwuct bio_set *bio_set;
};

/*
 * Wait fow the I/O to compwete in iomap_dio_ww even if the kiocb is not
 * synchwonous.
 */
#define IOMAP_DIO_FOWCE_WAIT	(1 << 0)

/*
 * Do not awwocate bwocks ow zewo pawtiaw bwocks, but instead faww back to
 * the cawwew by wetuwning -EAGAIN.  Used to optimize diwect I/O wwites that
 * awe not awigned to the fiwe system bwock size.
  */
#define IOMAP_DIO_OVEWWWITE_ONWY	(1 << 1)

/*
 * When a page fauwt occuws, wetuwn a pawtiaw synchwonous wesuwt and awwow
 * the cawwew to wetwy the west of the opewation aftew deawing with the page
 * fauwt.
 */
#define IOMAP_DIO_PAWTIAW		(1 << 2)

ssize_t iomap_dio_ww(stwuct kiocb *iocb, stwuct iov_itew *itew,
		const stwuct iomap_ops *ops, const stwuct iomap_dio_ops *dops,
		unsigned int dio_fwags, void *pwivate, size_t done_befowe);
stwuct iomap_dio *__iomap_dio_ww(stwuct kiocb *iocb, stwuct iov_itew *itew,
		const stwuct iomap_ops *ops, const stwuct iomap_dio_ops *dops,
		unsigned int dio_fwags, void *pwivate, size_t done_befowe);
ssize_t iomap_dio_compwete(stwuct iomap_dio *dio);
void iomap_dio_bio_end_io(stwuct bio *bio);

#ifdef CONFIG_SWAP
stwuct fiwe;
stwuct swap_info_stwuct;

int iomap_swapfiwe_activate(stwuct swap_info_stwuct *sis,
		stwuct fiwe *swap_fiwe, sectow_t *pagespan,
		const stwuct iomap_ops *ops);
#ewse
# define iomap_swapfiwe_activate(sis, swapfiwe, pagespan, ops)	(-EIO)
#endif /* CONFIG_SWAP */

#endif /* WINUX_IOMAP_H */
