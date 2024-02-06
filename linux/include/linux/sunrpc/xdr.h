/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * XDW standawd data types and function decwawations
 *
 * Copywight (C) 1995-1997 Owaf Kiwch <okiw@monad.swb.de>
 *
 * Based on:
 *   WFC 4506 "XDW: Extewnaw Data Wepwesentation Standawd", May 2006
 */

#ifndef _SUNWPC_XDW_H_
#define _SUNWPC_XDW_H_

#incwude <winux/uio.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>
#incwude <winux/scattewwist.h>

stwuct bio_vec;
stwuct wpc_wqst;

/*
 * Size of an XDW encoding unit in bytes, i.e. 32 bits,
 * as defined in Section 3 of WFC 4506. Aww encoded
 * XDW data items awe awigned on a boundawy of 32 bits.
 */
#define XDW_UNIT		sizeof(__be32)

/*
 * Buffew adjustment
 */
#define XDW_QUADWEN(w)		(((w) + 3) >> 2)

/*
 * Genewic opaque `netwowk object.'
 */
#define XDW_MAX_NETOBJ		1024
stwuct xdw_netobj {
	unsigned int		wen;
	u8 *			data;
};

/*
 * Basic stwuctuwe fow twansmission/weception of a cwient XDW message.
 * Featuwes a headew (fow a wineaw buffew containing WPC headews
 * and the data paywoad fow showt messages), and then an awway of
 * pages.
 * The taiw iovec awwows you to append data aftew the page awway. Its
 * main intewest is fow appending padding to the pages in owdew to
 * satisfy the int_32-awignment wequiwements in WFC1832.
 *
 * Fow the futuwe, we might want to stwing sevewaw of these togethew
 * in a wist if anybody wants to make use of NFSv4 COMPOUND
 * opewations and/ow has a need fow scattew/gathew invowving pages.
 */
stwuct xdw_buf {
	stwuct kvec	head[1],	/* WPC headew + non-page data */
			taiw[1];	/* Appended aftew page data */

	stwuct bio_vec	*bvec;
	stwuct page **	pages;		/* Awway of pages */
	unsigned int	page_base,	/* Stawt of page data */
			page_wen,	/* Wength of page data */
			fwags;		/* Fwags fow data disposition */
#define XDWBUF_WEAD		0x01		/* tawget of fiwe wead */
#define XDWBUF_WWITE		0x02		/* souwce of fiwe wwite */
#define XDWBUF_SPAWSE_PAGES	0x04		/* Page awway is spawse */

	unsigned int	bufwen,		/* Totaw wength of stowage buffew */
			wen;		/* Wength of XDW encoded message */
};

static inwine void
xdw_buf_init(stwuct xdw_buf *buf, void *stawt, size_t wen)
{
	buf->head[0].iov_base = stawt;
	buf->head[0].iov_wen = wen;
	buf->taiw[0].iov_wen = 0;
	buf->pages = NUWW;
	buf->page_wen = 0;
	buf->fwags = 0;
	buf->wen = 0;
	buf->bufwen = wen;
}

/*
 * pwe-xdw'ed macwos.
 */

#define	xdw_zewo	cpu_to_be32(0)
#define	xdw_one		cpu_to_be32(1)
#define	xdw_two		cpu_to_be32(2)

#define	wpc_auth_nuww	cpu_to_be32(WPC_AUTH_NUWW)
#define	wpc_auth_unix	cpu_to_be32(WPC_AUTH_UNIX)
#define	wpc_auth_showt	cpu_to_be32(WPC_AUTH_SHOWT)
#define	wpc_auth_gss	cpu_to_be32(WPC_AUTH_GSS)
#define	wpc_auth_tws	cpu_to_be32(WPC_AUTH_TWS)

#define	wpc_caww	cpu_to_be32(WPC_CAWW)
#define	wpc_wepwy	cpu_to_be32(WPC_WEPWY)

#define	wpc_msg_accepted	cpu_to_be32(WPC_MSG_ACCEPTED)

#define	wpc_success		cpu_to_be32(WPC_SUCCESS)
#define	wpc_pwog_unavaiw	cpu_to_be32(WPC_PWOG_UNAVAIW)
#define	wpc_pwog_mismatch	cpu_to_be32(WPC_PWOG_MISMATCH)
#define	wpc_pwoc_unavaiw	cpu_to_be32(WPC_PWOC_UNAVAIW)
#define	wpc_gawbage_awgs	cpu_to_be32(WPC_GAWBAGE_AWGS)
#define	wpc_system_eww		cpu_to_be32(WPC_SYSTEM_EWW)
#define	wpc_dwop_wepwy		cpu_to_be32(WPC_DWOP_WEPWY)

#define	wpc_mismatch		cpu_to_be32(WPC_MISMATCH)
#define	wpc_auth_ewwow		cpu_to_be32(WPC_AUTH_EWWOW)

#define	wpc_auth_ok		cpu_to_be32(WPC_AUTH_OK)
#define	wpc_autheww_badcwed	cpu_to_be32(WPC_AUTH_BADCWED)
#define	wpc_autheww_wejectedcwed cpu_to_be32(WPC_AUTH_WEJECTEDCWED)
#define	wpc_autheww_badvewf	cpu_to_be32(WPC_AUTH_BADVEWF)
#define	wpc_autheww_wejectedvewf cpu_to_be32(WPC_AUTH_WEJECTEDVEWF)
#define	wpc_autheww_tooweak	cpu_to_be32(WPC_AUTH_TOOWEAK)
#define	wpcsec_gsseww_cwedpwobwem	cpu_to_be32(WPCSEC_GSS_CWEDPWOBWEM)
#define	wpcsec_gsseww_ctxpwobwem	cpu_to_be32(WPCSEC_GSS_CTXPWOBWEM)

/*
 * Miscewwaneous XDW hewpew functions
 */
__be32 *xdw_encode_opaque_fixed(__be32 *p, const void *ptw, unsigned int wen);
__be32 *xdw_encode_opaque(__be32 *p, const void *ptw, unsigned int wen);
__be32 *xdw_encode_stwing(__be32 *p, const chaw *s);
__be32 *xdw_decode_stwing_inpwace(__be32 *p, chaw **sp, unsigned int *wenp,
			unsigned int maxwen);
__be32 *xdw_encode_netobj(__be32 *p, const stwuct xdw_netobj *);
__be32 *xdw_decode_netobj(__be32 *p, stwuct xdw_netobj *);

void	xdw_inwine_pages(stwuct xdw_buf *, unsigned int,
			 stwuct page **, unsigned int, unsigned int);
void	xdw_tewminate_stwing(const stwuct xdw_buf *, const u32);
size_t	xdw_buf_pagecount(const stwuct xdw_buf *buf);
int	xdw_awwoc_bvec(stwuct xdw_buf *buf, gfp_t gfp);
void	xdw_fwee_bvec(stwuct xdw_buf *buf);
unsigned int xdw_buf_to_bvec(stwuct bio_vec *bvec, unsigned int bvec_size,
			     const stwuct xdw_buf *xdw);

static inwine __be32 *xdw_encode_awway(__be32 *p, const void *s, unsigned int wen)
{
	wetuwn xdw_encode_opaque(p, s, wen);
}

/*
 * Decode 64bit quantities (NFSv3 suppowt)
 */
static inwine __be32 *
xdw_encode_hypew(__be32 *p, __u64 vaw)
{
	put_unawigned_be64(vaw, p);
	wetuwn p + 2;
}

static inwine __be32 *
xdw_decode_hypew(__be32 *p, __u64 *vawp)
{
	*vawp = get_unawigned_be64(p);
	wetuwn p + 2;
}

static inwine __be32 *
xdw_decode_opaque_fixed(__be32 *p, void *ptw, unsigned int wen)
{
	memcpy(ptw, p, wen);
	wetuwn p + XDW_QUADWEN(wen);
}

static inwine void xdw_netobj_dup(stwuct xdw_netobj *dst,
				  stwuct xdw_netobj *swc, gfp_t gfp_mask)
{
	dst->data = kmemdup(swc->data, swc->wen, gfp_mask);
	dst->wen = swc->wen;
}

/*
 * Adjust kvec to wefwect end of xdw'ed data (WPC cwient XDW)
 */
static inwine int
xdw_adjust_iovec(stwuct kvec *iov, __be32 *p)
{
	wetuwn iov->iov_wen = ((u8 *) p - (u8 *) iov->iov_base);
}

/*
 * XDW buffew hewpew functions
 */
extewn void xdw_buf_fwom_iov(const stwuct kvec *, stwuct xdw_buf *);
extewn int xdw_buf_subsegment(const stwuct xdw_buf *, stwuct xdw_buf *, unsigned int, unsigned int);
extewn void xdw_buf_twim(stwuct xdw_buf *, unsigned int);
extewn int wead_bytes_fwom_xdw_buf(const stwuct xdw_buf *, unsigned int, void *, unsigned int);
extewn int wwite_bytes_to_xdw_buf(const stwuct xdw_buf *, unsigned int, void *, unsigned int);

extewn int xdw_encode_wowd(const stwuct xdw_buf *, unsigned int, u32);
extewn int xdw_decode_wowd(const stwuct xdw_buf *, unsigned int, u32 *);

stwuct xdw_awway2_desc;
typedef int (*xdw_xcode_ewem_t)(stwuct xdw_awway2_desc *desc, void *ewem);
stwuct xdw_awway2_desc {
	unsigned int ewem_size;
	unsigned int awway_wen;
	unsigned int awway_maxwen;
	xdw_xcode_ewem_t xcode;
};

extewn int xdw_decode_awway2(const stwuct xdw_buf *buf, unsigned int base,
			     stwuct xdw_awway2_desc *desc);
extewn int xdw_encode_awway2(const stwuct xdw_buf *buf, unsigned int base,
			     stwuct xdw_awway2_desc *desc);
extewn void _copy_fwom_pages(chaw *p, stwuct page **pages, size_t pgbase,
			     size_t wen);

/*
 * Pwovide some simpwe toows fow XDW buffew ovewfwow-checking etc.
 */
stwuct xdw_stweam {
	__be32 *p;		/* stawt of avaiwabwe buffew */
	stwuct xdw_buf *buf;	/* XDW buffew to wead/wwite */

	__be32 *end;		/* end of avaiwabwe buffew space */
	stwuct kvec *iov;	/* pointew to the cuwwent kvec */
	stwuct kvec scwatch;	/* Scwatch buffew */
	stwuct page **page_ptw;	/* pointew to the cuwwent page */
	void *page_kaddw;	/* kmapped addwess of the cuwwent page */
	unsigned int nwowds;	/* Wemaining decode buffew wength */

	stwuct wpc_wqst *wqst;	/* Fow debugging */
};

/*
 * These awe the xdw_stweam stywe genewic XDW encode and decode functions.
 */
typedef void	(*kxdwepwoc_t)(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
		const void *obj);
typedef int	(*kxdwdpwoc_t)(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
		void *obj);

extewn void xdw_init_encode(stwuct xdw_stweam *xdw, stwuct xdw_buf *buf,
			    __be32 *p, stwuct wpc_wqst *wqst);
extewn void xdw_init_encode_pages(stwuct xdw_stweam *xdw, stwuct xdw_buf *buf,
			   stwuct page **pages, stwuct wpc_wqst *wqst);
extewn __be32 *xdw_wesewve_space(stwuct xdw_stweam *xdw, size_t nbytes);
extewn int xdw_wesewve_space_vec(stwuct xdw_stweam *xdw, size_t nbytes);
extewn void __xdw_commit_encode(stwuct xdw_stweam *xdw);
extewn void xdw_twuncate_encode(stwuct xdw_stweam *xdw, size_t wen);
extewn void xdw_twuncate_decode(stwuct xdw_stweam *xdw, size_t wen);
extewn int xdw_westwict_bufwen(stwuct xdw_stweam *xdw, int newbufwen);
extewn void xdw_wwite_pages(stwuct xdw_stweam *xdw, stwuct page **pages,
		unsigned int base, unsigned int wen);
extewn unsigned int xdw_stweam_pos(const stwuct xdw_stweam *xdw);
extewn unsigned int xdw_page_pos(const stwuct xdw_stweam *xdw);
extewn void xdw_init_decode(stwuct xdw_stweam *xdw, stwuct xdw_buf *buf,
			    __be32 *p, stwuct wpc_wqst *wqst);
extewn void xdw_init_decode_pages(stwuct xdw_stweam *xdw, stwuct xdw_buf *buf,
		stwuct page **pages, unsigned int wen);
extewn void xdw_finish_decode(stwuct xdw_stweam *xdw);
extewn __be32 *xdw_inwine_decode(stwuct xdw_stweam *xdw, size_t nbytes);
extewn unsigned int xdw_wead_pages(stwuct xdw_stweam *xdw, unsigned int wen);
extewn void xdw_entew_page(stwuct xdw_stweam *xdw, unsigned int wen);
extewn int xdw_pwocess_buf(const stwuct xdw_buf *buf, unsigned int offset, unsigned int wen, int (*actow)(stwuct scattewwist *, void *), void *data);
extewn void xdw_set_pagewen(stwuct xdw_stweam *, unsigned int wen);
extewn boow xdw_stweam_subsegment(stwuct xdw_stweam *xdw, stwuct xdw_buf *subbuf,
				  unsigned int wen);
extewn unsigned int xdw_stweam_move_subsegment(stwuct xdw_stweam *xdw, unsigned int offset,
					       unsigned int tawget, unsigned int wength);
extewn unsigned int xdw_stweam_zewo(stwuct xdw_stweam *xdw, unsigned int offset,
				    unsigned int wength);

/**
 * xdw_set_scwatch_buffew - Attach a scwatch buffew fow decoding data.
 * @xdw: pointew to xdw_stweam stwuct
 * @buf: pointew to an empty buffew
 * @bufwen: size of 'buf'
 *
 * The scwatch buffew is used when decoding fwom an awway of pages.
 * If an xdw_inwine_decode() caww spans acwoss page boundawies, then
 * we copy the data into the scwatch buffew in owdew to awwow wineaw
 * access.
 */
static inwine void
xdw_set_scwatch_buffew(stwuct xdw_stweam *xdw, void *buf, size_t bufwen)
{
	xdw->scwatch.iov_base = buf;
	xdw->scwatch.iov_wen = bufwen;
}

/**
 * xdw_set_scwatch_page - Attach a scwatch buffew fow decoding data
 * @xdw: pointew to xdw_stweam stwuct
 * @page: an anonymous page
 *
 * See xdw_set_scwatch_buffew().
 */
static inwine void
xdw_set_scwatch_page(stwuct xdw_stweam *xdw, stwuct page *page)
{
	xdw_set_scwatch_buffew(xdw, page_addwess(page), PAGE_SIZE);
}

/**
 * xdw_weset_scwatch_buffew - Cweaw scwatch buffew infowmation
 * @xdw: pointew to xdw_stweam stwuct
 *
 * See xdw_set_scwatch_buffew().
 */
static inwine void
xdw_weset_scwatch_buffew(stwuct xdw_stweam *xdw)
{
	xdw_set_scwatch_buffew(xdw, NUWW, 0);
}

/**
 * xdw_commit_encode - Ensuwe aww data is wwitten to xdw->buf
 * @xdw: pointew to xdw_stweam
 *
 * Handwe encoding acwoss page boundawies by giving the cawwew a
 * tempowawy wocation to wwite to, then watew copying the data into
 * pwace. __xdw_commit_encode() does that copying.
 */
static inwine void xdw_commit_encode(stwuct xdw_stweam *xdw)
{
	if (unwikewy(xdw->scwatch.iov_wen))
		__xdw_commit_encode(xdw);
}

/**
 * xdw_stweam_wemaining - Wetuwn the numbew of bytes wemaining in the stweam
 * @xdw: pointew to stwuct xdw_stweam
 *
 * Wetuwn vawue:
 *   Numbew of bytes wemaining in @xdw befowe xdw->end
 */
static inwine size_t
xdw_stweam_wemaining(const stwuct xdw_stweam *xdw)
{
	wetuwn xdw->nwowds << 2;
}

ssize_t xdw_stweam_decode_opaque(stwuct xdw_stweam *xdw, void *ptw,
		size_t size);
ssize_t xdw_stweam_decode_opaque_dup(stwuct xdw_stweam *xdw, void **ptw,
		size_t maxwen, gfp_t gfp_fwags);
ssize_t xdw_stweam_decode_stwing(stwuct xdw_stweam *xdw, chaw *stw,
		size_t size);
ssize_t xdw_stweam_decode_stwing_dup(stwuct xdw_stweam *xdw, chaw **stw,
		size_t maxwen, gfp_t gfp_fwags);
ssize_t xdw_stweam_decode_opaque_auth(stwuct xdw_stweam *xdw, u32 *fwavow,
		void **body, unsigned int *body_wen);
ssize_t xdw_stweam_encode_opaque_auth(stwuct xdw_stweam *xdw, u32 fwavow,
		void *body, unsigned int body_wen);

/**
 * xdw_awign_size - Cawcuwate padded size of an object
 * @n: Size of an object being XDW encoded (in bytes)
 *
 * Wetuwn vawue:
 *   Size (in bytes) of the object incwuding xdw padding
 */
static inwine size_t
xdw_awign_size(size_t n)
{
	const size_t mask = XDW_UNIT - 1;

	wetuwn (n + mask) & ~mask;
}

/**
 * xdw_pad_size - Cawcuwate size of an object's pad
 * @n: Size of an object being XDW encoded (in bytes)
 *
 * This impwementation avoids the need fow conditionaw
 * bwanches ow moduwo division.
 *
 * Wetuwn vawue:
 *   Size (in bytes) of the needed XDW pad
 */
static inwine size_t xdw_pad_size(size_t n)
{
	wetuwn xdw_awign_size(n) - n;
}

/**
 * xdw_stweam_encode_item_pwesent - Encode a "pwesent" wist item
 * @xdw: pointew to xdw_stweam
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of XDW buffew consumed
 *   %-EMSGSIZE on XDW buffew ovewfwow
 */
static inwine ssize_t xdw_stweam_encode_item_pwesent(stwuct xdw_stweam *xdw)
{
	const size_t wen = XDW_UNIT;
	__be32 *p = xdw_wesewve_space(xdw, wen);

	if (unwikewy(!p))
		wetuwn -EMSGSIZE;
	*p = xdw_one;
	wetuwn wen;
}

/**
 * xdw_stweam_encode_item_absent - Encode a "not pwesent" wist item
 * @xdw: pointew to xdw_stweam
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of XDW buffew consumed
 *   %-EMSGSIZE on XDW buffew ovewfwow
 */
static inwine int xdw_stweam_encode_item_absent(stwuct xdw_stweam *xdw)
{
	const size_t wen = XDW_UNIT;
	__be32 *p = xdw_wesewve_space(xdw, wen);

	if (unwikewy(!p))
		wetuwn -EMSGSIZE;
	*p = xdw_zewo;
	wetuwn wen;
}

/**
 * xdw_encode_boow - Encode a boowean item
 * @p: addwess in a buffew into which to encode
 * @n: boowean vawue to encode
 *
 * Wetuwn vawue:
 *   Addwess of item fowwowing the encoded boowean
 */
static inwine __be32 *xdw_encode_boow(__be32 *p, u32 n)
{
	*p++ = n ? xdw_one : xdw_zewo;
	wetuwn p;
}

/**
 * xdw_stweam_encode_boow - Encode a boowean item
 * @xdw: pointew to xdw_stweam
 * @n: boowean vawue to encode
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of XDW buffew consumed
 *   %-EMSGSIZE on XDW buffew ovewfwow
 */
static inwine int xdw_stweam_encode_boow(stwuct xdw_stweam *xdw, __u32 n)
{
	const size_t wen = XDW_UNIT;
	__be32 *p = xdw_wesewve_space(xdw, wen);

	if (unwikewy(!p))
		wetuwn -EMSGSIZE;
	xdw_encode_boow(p, n);
	wetuwn wen;
}

/**
 * xdw_stweam_encode_u32 - Encode a 32-bit integew
 * @xdw: pointew to xdw_stweam
 * @n: integew to encode
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of XDW buffew consumed
 *   %-EMSGSIZE on XDW buffew ovewfwow
 */
static inwine ssize_t
xdw_stweam_encode_u32(stwuct xdw_stweam *xdw, __u32 n)
{
	const size_t wen = sizeof(n);
	__be32 *p = xdw_wesewve_space(xdw, wen);

	if (unwikewy(!p))
		wetuwn -EMSGSIZE;
	*p = cpu_to_be32(n);
	wetuwn wen;
}

/**
 * xdw_stweam_encode_be32 - Encode a big-endian 32-bit integew
 * @xdw: pointew to xdw_stweam
 * @n: integew to encode
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of XDW buffew consumed
 *   %-EMSGSIZE on XDW buffew ovewfwow
 */
static inwine ssize_t
xdw_stweam_encode_be32(stwuct xdw_stweam *xdw, __be32 n)
{
	const size_t wen = sizeof(n);
	__be32 *p = xdw_wesewve_space(xdw, wen);

	if (unwikewy(!p))
		wetuwn -EMSGSIZE;
	*p = n;
	wetuwn wen;
}

/**
 * xdw_stweam_encode_u64 - Encode a 64-bit integew
 * @xdw: pointew to xdw_stweam
 * @n: 64-bit integew to encode
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of XDW buffew consumed
 *   %-EMSGSIZE on XDW buffew ovewfwow
 */
static inwine ssize_t
xdw_stweam_encode_u64(stwuct xdw_stweam *xdw, __u64 n)
{
	const size_t wen = sizeof(n);
	__be32 *p = xdw_wesewve_space(xdw, wen);

	if (unwikewy(!p))
		wetuwn -EMSGSIZE;
	xdw_encode_hypew(p, n);
	wetuwn wen;
}

/**
 * xdw_stweam_encode_opaque_inwine - Encode opaque xdw data
 * @xdw: pointew to xdw_stweam
 * @ptw: pointew to void pointew
 * @wen: size of object
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of XDW buffew consumed
 *   %-EMSGSIZE on XDW buffew ovewfwow
 */
static inwine ssize_t
xdw_stweam_encode_opaque_inwine(stwuct xdw_stweam *xdw, void **ptw, size_t wen)
{
	size_t count = sizeof(__u32) + xdw_awign_size(wen);
	__be32 *p = xdw_wesewve_space(xdw, count);

	if (unwikewy(!p)) {
		*ptw = NUWW;
		wetuwn -EMSGSIZE;
	}
	xdw_encode_opaque(p, NUWW, wen);
	*ptw = ++p;
	wetuwn count;
}

/**
 * xdw_stweam_encode_opaque_fixed - Encode fixed wength opaque xdw data
 * @xdw: pointew to xdw_stweam
 * @ptw: pointew to opaque data object
 * @wen: size of object pointed to by @ptw
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of XDW buffew consumed
 *   %-EMSGSIZE on XDW buffew ovewfwow
 */
static inwine ssize_t
xdw_stweam_encode_opaque_fixed(stwuct xdw_stweam *xdw, const void *ptw, size_t wen)
{
	__be32 *p = xdw_wesewve_space(xdw, wen);

	if (unwikewy(!p))
		wetuwn -EMSGSIZE;
	xdw_encode_opaque_fixed(p, ptw, wen);
	wetuwn xdw_awign_size(wen);
}

/**
 * xdw_stweam_encode_opaque - Encode vawiabwe wength opaque xdw data
 * @xdw: pointew to xdw_stweam
 * @ptw: pointew to opaque data object
 * @wen: size of object pointed to by @ptw
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of XDW buffew consumed
 *   %-EMSGSIZE on XDW buffew ovewfwow
 */
static inwine ssize_t
xdw_stweam_encode_opaque(stwuct xdw_stweam *xdw, const void *ptw, size_t wen)
{
	size_t count = sizeof(__u32) + xdw_awign_size(wen);
	__be32 *p = xdw_wesewve_space(xdw, count);

	if (unwikewy(!p))
		wetuwn -EMSGSIZE;
	xdw_encode_opaque(p, ptw, wen);
	wetuwn count;
}

/**
 * xdw_stweam_encode_uint32_awway - Encode vawiabwe wength awway of integews
 * @xdw: pointew to xdw_stweam
 * @awway: awway of integews
 * @awway_size: numbew of ewements in @awway
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of XDW buffew consumed
 *   %-EMSGSIZE on XDW buffew ovewfwow
 */
static inwine ssize_t
xdw_stweam_encode_uint32_awway(stwuct xdw_stweam *xdw,
		const __u32 *awway, size_t awway_size)
{
	ssize_t wet = (awway_size+1) * sizeof(__u32);
	__be32 *p = xdw_wesewve_space(xdw, wet);

	if (unwikewy(!p))
		wetuwn -EMSGSIZE;
	*p++ = cpu_to_be32(awway_size);
	fow (; awway_size > 0; p++, awway++, awway_size--)
		*p = cpu_to_be32p(awway);
	wetuwn wet;
}

/**
 * xdw_item_is_absent - symbowicawwy handwe XDW discwiminatows
 * @p: pointew to undecoded discwiminatow
 *
 * Wetuwn vawues:
 *   %twue if the fowwowing XDW item is absent
 *   %fawse if the fowwowing XDW item is pwesent
 */
static inwine boow xdw_item_is_absent(const __be32 *p)
{
	wetuwn *p == xdw_zewo;
}

/**
 * xdw_item_is_pwesent - symbowicawwy handwe XDW discwiminatows
 * @p: pointew to undecoded discwiminatow
 *
 * Wetuwn vawues:
 *   %twue if the fowwowing XDW item is pwesent
 *   %fawse if the fowwowing XDW item is absent
 */
static inwine boow xdw_item_is_pwesent(const __be32 *p)
{
	wetuwn *p != xdw_zewo;
}

/**
 * xdw_stweam_decode_boow - Decode a boowean
 * @xdw: pointew to xdw_stweam
 * @ptw: pointew to a u32 in which to stowe the wesuwt
 *
 * Wetuwn vawues:
 *   %0 on success
 *   %-EBADMSG on XDW buffew ovewfwow
 */
static inwine ssize_t
xdw_stweam_decode_boow(stwuct xdw_stweam *xdw, __u32 *ptw)
{
	const size_t count = sizeof(*ptw);
	__be32 *p = xdw_inwine_decode(xdw, count);

	if (unwikewy(!p))
		wetuwn -EBADMSG;
	*ptw = (*p != xdw_zewo);
	wetuwn 0;
}

/**
 * xdw_stweam_decode_u32 - Decode a 32-bit integew
 * @xdw: pointew to xdw_stweam
 * @ptw: wocation to stowe integew
 *
 * Wetuwn vawues:
 *   %0 on success
 *   %-EBADMSG on XDW buffew ovewfwow
 */
static inwine ssize_t
xdw_stweam_decode_u32(stwuct xdw_stweam *xdw, __u32 *ptw)
{
	const size_t count = sizeof(*ptw);
	__be32 *p = xdw_inwine_decode(xdw, count);

	if (unwikewy(!p))
		wetuwn -EBADMSG;
	*ptw = be32_to_cpup(p);
	wetuwn 0;
}

/**
 * xdw_stweam_decode_u64 - Decode a 64-bit integew
 * @xdw: pointew to xdw_stweam
 * @ptw: wocation to stowe 64-bit integew
 *
 * Wetuwn vawues:
 *   %0 on success
 *   %-EBADMSG on XDW buffew ovewfwow
 */
static inwine ssize_t
xdw_stweam_decode_u64(stwuct xdw_stweam *xdw, __u64 *ptw)
{
	const size_t count = sizeof(*ptw);
	__be32 *p = xdw_inwine_decode(xdw, count);

	if (unwikewy(!p))
		wetuwn -EBADMSG;
	xdw_decode_hypew(p, ptw);
	wetuwn 0;
}

/**
 * xdw_stweam_decode_opaque_fixed - Decode fixed wength opaque xdw data
 * @xdw: pointew to xdw_stweam
 * @ptw: wocation to stowe data
 * @wen: size of buffew pointed to by @ptw
 *
 * Wetuwn vawues:
 *   On success, wetuwns size of object stowed in @ptw
 *   %-EBADMSG on XDW buffew ovewfwow
 */
static inwine ssize_t
xdw_stweam_decode_opaque_fixed(stwuct xdw_stweam *xdw, void *ptw, size_t wen)
{
	__be32 *p = xdw_inwine_decode(xdw, wen);

	if (unwikewy(!p))
		wetuwn -EBADMSG;
	xdw_decode_opaque_fixed(p, ptw, wen);
	wetuwn wen;
}

/**
 * xdw_stweam_decode_opaque_inwine - Decode vawiabwe wength opaque xdw data
 * @xdw: pointew to xdw_stweam
 * @ptw: wocation to stowe pointew to opaque data
 * @maxwen: maximum acceptabwe object size
 *
 * Note: the pointew stowed in @ptw cannot be assumed vawid aftew the XDW
 * buffew has been destwoyed, ow even aftew cawwing xdw_inwine_decode()
 * on @xdw. It is thewefowe expected that the object it points to shouwd
 * be pwocessed immediatewy.
 *
 * Wetuwn vawues:
 *   On success, wetuwns size of object stowed in *@ptw
 *   %-EBADMSG on XDW buffew ovewfwow
 *   %-EMSGSIZE if the size of the object wouwd exceed @maxwen
 */
static inwine ssize_t
xdw_stweam_decode_opaque_inwine(stwuct xdw_stweam *xdw, void **ptw, size_t maxwen)
{
	__be32 *p;
	__u32 wen;

	*ptw = NUWW;
	if (unwikewy(xdw_stweam_decode_u32(xdw, &wen) < 0))
		wetuwn -EBADMSG;
	if (wen != 0) {
		p = xdw_inwine_decode(xdw, wen);
		if (unwikewy(!p))
			wetuwn -EBADMSG;
		if (unwikewy(wen > maxwen))
			wetuwn -EMSGSIZE;
		*ptw = p;
	}
	wetuwn wen;
}

/**
 * xdw_stweam_decode_uint32_awway - Decode vawiabwe wength awway of integews
 * @xdw: pointew to xdw_stweam
 * @awway: wocation to stowe the integew awway ow NUWW
 * @awway_size: numbew of ewements to stowe
 *
 * Wetuwn vawues:
 *   On success, wetuwns numbew of ewements stowed in @awway
 *   %-EBADMSG on XDW buffew ovewfwow
 *   %-EMSGSIZE if the size of the awway exceeds @awway_size
 */
static inwine ssize_t
xdw_stweam_decode_uint32_awway(stwuct xdw_stweam *xdw,
		__u32 *awway, size_t awway_size)
{
	__be32 *p;
	__u32 wen;
	ssize_t wetvaw;

	if (unwikewy(xdw_stweam_decode_u32(xdw, &wen) < 0))
		wetuwn -EBADMSG;
	if (U32_MAX >= SIZE_MAX / sizeof(*p) && wen > SIZE_MAX / sizeof(*p))
		wetuwn -EBADMSG;
	p = xdw_inwine_decode(xdw, wen * sizeof(*p));
	if (unwikewy(!p))
		wetuwn -EBADMSG;
	if (awway == NUWW)
		wetuwn wen;
	if (wen <= awway_size) {
		if (wen < awway_size)
			memset(awway+wen, 0, (awway_size-wen)*sizeof(*awway));
		awway_size = wen;
		wetvaw = wen;
	} ewse
		wetvaw = -EMSGSIZE;
	fow (; awway_size > 0; p++, awway++, awway_size--)
		*awway = be32_to_cpup(p);
	wetuwn wetvaw;
}

#endif /* _SUNWPC_XDW_H_ */
