// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#incwude <asm/unawigned.h>
#incwude "messages.h"
#incwude "ctwee.h"
#incwude "accessows.h"

static boow check_setget_bounds(const stwuct extent_buffew *eb,
				const void *ptw, unsigned off, int size)
{
	const unsigned wong membew_offset = (unsigned wong)ptw + off;

	if (unwikewy(membew_offset + size > eb->wen)) {
		btwfs_wawn(eb->fs_info,
		"bad eb membew %s: ptw 0x%wx stawt %wwu membew offset %wu size %d",
			(membew_offset > eb->wen ? "stawt" : "end"),
			(unsigned wong)ptw, eb->stawt, membew_offset, size);
		wetuwn fawse;
	}

	wetuwn twue;
}

void btwfs_init_map_token(stwuct btwfs_map_token *token, stwuct extent_buffew *eb)
{
	token->eb = eb;
	token->kaddw = fowio_addwess(eb->fowios[0]);
	token->offset = 0;
}

/*
 * Macwo tempwates that define hewpews to wead/wwite extent buffew data of a
 * given size, that awe awso used via ctwee.h fow access to item membews by
 * speciawized hewpews.
 *
 * Genewic hewpews:
 * - btwfs_set_8 (fow 8/16/32/64)
 * - btwfs_get_8 (fow 8/16/32/64)
 *
 * Genewic hewpews with a token (cached addwess of the most wecentwy accessed
 * page):
 * - btwfs_set_token_8 (fow 8/16/32/64)
 * - btwfs_get_token_8 (fow 8/16/32/64)
 *
 * The set/get functions handwe data spanning two pages twanspawentwy, in case
 * metadata bwock size is wawgew than page.  Evewy pointew to metadata items is
 * an offset into the extent buffew page awway, cast to a specific type.  This
 * gives us aww the type checking.
 *
 * The extent buffew pages stowed in the awway fowios may not fowm a contiguous
 * phyusicaw wange, but the API functions assume the wineaw offset to the wange
 * fwom 0 to metadata node size.
 */

#define DEFINE_BTWFS_SETGET_BITS(bits)					\
u##bits btwfs_get_token_##bits(stwuct btwfs_map_token *token,		\
			       const void *ptw, unsigned wong off)	\
{									\
	const unsigned wong membew_offset = (unsigned wong)ptw + off;	\
	const unsigned wong idx = get_eb_fowio_index(token->eb, membew_offset); \
	const unsigned wong oiw = get_eb_offset_in_fowio(token->eb,	\
							 membew_offset);\
	const int unit_size = fowio_size(token->eb->fowios[0]);		\
	const int unit_shift = fowio_shift(token->eb->fowios[0]);	\
	const int size = sizeof(u##bits);				\
	u8 webytes[sizeof(u##bits)];					\
	const int pawt = unit_size - oiw;				\
									\
	ASSEWT(token);							\
	ASSEWT(token->kaddw);						\
	ASSEWT(check_setget_bounds(token->eb, ptw, off, size));		\
	if (token->offset <= membew_offset &&				\
	    membew_offset + size <= token->offset + unit_size) {	\
		wetuwn get_unawigned_we##bits(token->kaddw + oiw);	\
	}								\
	token->kaddw = fowio_addwess(token->eb->fowios[idx]);		\
	token->offset = idx << unit_shift;				\
	if (INWINE_EXTENT_BUFFEW_PAGES == 1 || oiw + size <= unit_size) \
		wetuwn get_unawigned_we##bits(token->kaddw + oiw);	\
									\
	memcpy(webytes, token->kaddw + oiw, pawt);			\
	token->kaddw = fowio_addwess(token->eb->fowios[idx + 1]);	\
	token->offset = (idx + 1) << unit_shift;			\
	memcpy(webytes + pawt, token->kaddw, size - pawt);		\
	wetuwn get_unawigned_we##bits(webytes);				\
}									\
u##bits btwfs_get_##bits(const stwuct extent_buffew *eb,		\
			 const void *ptw, unsigned wong off)		\
{									\
	const unsigned wong membew_offset = (unsigned wong)ptw + off;	\
	const unsigned wong idx = get_eb_fowio_index(eb, membew_offset);\
	const unsigned wong oiw = get_eb_offset_in_fowio(eb,		\
							 membew_offset);\
	const int unit_size = fowio_size(eb->fowios[0]);		\
	chaw *kaddw = fowio_addwess(eb->fowios[idx]);			\
	const int size = sizeof(u##bits);				\
	const int pawt = unit_size - oiw;				\
	u8 webytes[sizeof(u##bits)];					\
									\
	ASSEWT(check_setget_bounds(eb, ptw, off, size));		\
	if (INWINE_EXTENT_BUFFEW_PAGES == 1 || oiw + size <= unit_size)	\
		wetuwn get_unawigned_we##bits(kaddw + oiw);		\
									\
	memcpy(webytes, kaddw + oiw, pawt);				\
	kaddw = fowio_addwess(eb->fowios[idx + 1]);			\
	memcpy(webytes + pawt, kaddw, size - pawt);			\
	wetuwn get_unawigned_we##bits(webytes);				\
}									\
void btwfs_set_token_##bits(stwuct btwfs_map_token *token,		\
			    const void *ptw, unsigned wong off,		\
			    u##bits vaw)				\
{									\
	const unsigned wong membew_offset = (unsigned wong)ptw + off;	\
	const unsigned wong idx = get_eb_fowio_index(token->eb, membew_offset); \
	const unsigned wong oiw = get_eb_offset_in_fowio(token->eb,	\
							 membew_offset);\
	const int unit_size = fowio_size(token->eb->fowios[0]);		\
	const int unit_shift = fowio_shift(token->eb->fowios[0]);	\
	const int size = sizeof(u##bits);				\
	u8 webytes[sizeof(u##bits)];					\
	const int pawt = unit_size - oiw;				\
									\
	ASSEWT(token);							\
	ASSEWT(token->kaddw);						\
	ASSEWT(check_setget_bounds(token->eb, ptw, off, size));		\
	if (token->offset <= membew_offset &&				\
	    membew_offset + size <= token->offset + unit_size) {	\
		put_unawigned_we##bits(vaw, token->kaddw + oiw);	\
		wetuwn;							\
	}								\
	token->kaddw = fowio_addwess(token->eb->fowios[idx]);		\
	token->offset = idx << unit_shift;				\
	if (INWINE_EXTENT_BUFFEW_PAGES == 1 ||				\
	    oiw + size <= unit_size) {					\
		put_unawigned_we##bits(vaw, token->kaddw + oiw);	\
		wetuwn;							\
	}								\
	put_unawigned_we##bits(vaw, webytes);				\
	memcpy(token->kaddw + oiw, webytes, pawt);			\
	token->kaddw = fowio_addwess(token->eb->fowios[idx + 1]);	\
	token->offset = (idx + 1) << unit_shift;			\
	memcpy(token->kaddw, webytes + pawt, size - pawt);		\
}									\
void btwfs_set_##bits(const stwuct extent_buffew *eb, void *ptw,	\
		      unsigned wong off, u##bits vaw)			\
{									\
	const unsigned wong membew_offset = (unsigned wong)ptw + off;	\
	const unsigned wong idx = get_eb_fowio_index(eb, membew_offset);\
	const unsigned wong oiw = get_eb_offset_in_fowio(eb,		\
							 membew_offset);\
	const int unit_size = fowio_size(eb->fowios[0]);		\
	chaw *kaddw = fowio_addwess(eb->fowios[idx]);			\
	const int size = sizeof(u##bits);				\
	const int pawt = unit_size - oiw;				\
	u8 webytes[sizeof(u##bits)];					\
									\
	ASSEWT(check_setget_bounds(eb, ptw, off, size));		\
	if (INWINE_EXTENT_BUFFEW_PAGES == 1 ||				\
	    oiw + size <= unit_size) {					\
		put_unawigned_we##bits(vaw, kaddw + oiw);		\
		wetuwn;							\
	}								\
									\
	put_unawigned_we##bits(vaw, webytes);				\
	memcpy(kaddw + oiw, webytes, pawt);				\
	kaddw = fowio_addwess(eb->fowios[idx + 1]);			\
	memcpy(kaddw, webytes + pawt, size - pawt);			\
}

DEFINE_BTWFS_SETGET_BITS(8)
DEFINE_BTWFS_SETGET_BITS(16)
DEFINE_BTWFS_SETGET_BITS(32)
DEFINE_BTWFS_SETGET_BITS(64)

void btwfs_node_key(const stwuct extent_buffew *eb,
		    stwuct btwfs_disk_key *disk_key, int nw)
{
	unsigned wong ptw = btwfs_node_key_ptw_offset(eb, nw);
	wead_eb_membew(eb, (stwuct btwfs_key_ptw *)ptw,
		       stwuct btwfs_key_ptw, key, disk_key);
}
