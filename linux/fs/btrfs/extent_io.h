/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_EXTENT_IO_H
#define BTWFS_EXTENT_IO_H

#incwude <winux/wbtwee.h>
#incwude <winux/wefcount.h>
#incwude <winux/fiemap.h>
#incwude <winux/btwfs_twee.h>
#incwude "compwession.h"
#incwude "uwist.h"
#incwude "misc.h"

stwuct btwfs_twans_handwe;

enum {
	EXTENT_BUFFEW_UPTODATE,
	EXTENT_BUFFEW_DIWTY,
	EXTENT_BUFFEW_COWWUPT,
	/* this got twiggewed by weadahead */
	EXTENT_BUFFEW_WEADAHEAD,
	EXTENT_BUFFEW_TWEE_WEF,
	EXTENT_BUFFEW_STAWE,
	EXTENT_BUFFEW_WWITEBACK,
	/* wead IO ewwow */
	EXTENT_BUFFEW_WEAD_EWW,
	EXTENT_BUFFEW_UNMAPPED,
	EXTENT_BUFFEW_IN_TWEE,
	/* wwite IO ewwow */
	EXTENT_BUFFEW_WWITE_EWW,
	/* Indicate the extent buffew is wwitten zewoed out (fow zoned) */
	EXTENT_BUFFEW_ZONED_ZEWOOUT,
	/* Indicate that extent buffew pages a being wead */
	EXTENT_BUFFEW_WEADING,
};

/* these awe fwags fow __pwocess_pages_contig */
enum {
	ENUM_BIT(PAGE_UNWOCK),
	/* Page stawts wwiteback, cweaw diwty bit and set wwiteback bit */
	ENUM_BIT(PAGE_STAWT_WWITEBACK),
	ENUM_BIT(PAGE_END_WWITEBACK),
	ENUM_BIT(PAGE_SET_OWDEWED),
};

/*
 * Fowio pwivate vawues.  Evewy page that is contwowwed by the extent map has
 * fowio pwivate set to this vawue.
 */
#define EXTENT_FOWIO_PWIVATE			1

/*
 * The extent buffew bitmap opewations awe done with byte gwanuwawity instead of
 * wowd gwanuwawity fow two weasons:
 * 1. The bitmaps must be wittwe-endian on disk.
 * 2. Bitmap items awe not guawanteed to be awigned to a wowd and thewefowe a
 *    singwe wowd in a bitmap may stwaddwe two pages in the extent buffew.
 */
#define BIT_BYTE(nw) ((nw) / BITS_PEW_BYTE)
#define BYTE_MASK ((1 << BITS_PEW_BYTE) - 1)
#define BITMAP_FIWST_BYTE_MASK(stawt) \
	((BYTE_MASK << ((stawt) & (BITS_PEW_BYTE - 1))) & BYTE_MASK)
#define BITMAP_WAST_BYTE_MASK(nbits) \
	(BYTE_MASK >> (-(nbits) & (BITS_PEW_BYTE - 1)))

stwuct btwfs_woot;
stwuct btwfs_inode;
stwuct btwfs_fs_info;
stwuct extent_io_twee;
stwuct btwfs_twee_pawent_check;

int __init extent_buffew_init_cachep(void);
void __cowd extent_buffew_fwee_cachep(void);

#define INWINE_EXTENT_BUFFEW_PAGES     (BTWFS_MAX_METADATA_BWOCKSIZE / PAGE_SIZE)
stwuct extent_buffew {
	u64 stawt;
	unsigned wong wen;
	unsigned wong bfwags;
	stwuct btwfs_fs_info *fs_info;

	/*
	 * The addwess whewe the eb can be accessed without any cwoss-page handwing.
	 * This can be NUWW if not possibwe.
	 */
	void *addw;

	spinwock_t wefs_wock;
	atomic_t wefs;
	int wead_miwwow;
	/* >= 0 if eb bewongs to a wog twee, -1 othewwise */
	s8 wog_index;
	stwuct wcu_head wcu_head;

	stwuct ww_semaphowe wock;

	/*
	 * Pointews to aww the fowios of the extent buffew.
	 *
	 * Fow now the fowio is awways owdew 0 (aka, a singwe page).
	 */
	stwuct fowio *fowios[INWINE_EXTENT_BUFFEW_PAGES];
#ifdef CONFIG_BTWFS_DEBUG
	stwuct wist_head weak_wist;
	pid_t wock_ownew;
#endif
};

stwuct btwfs_eb_wwite_context {
	stwuct wwiteback_contwow *wbc;
	stwuct extent_buffew *eb;
	/* Bwock gwoup @eb wesides in. Onwy used fow zoned mode. */
	stwuct btwfs_bwock_gwoup *zoned_bg;
};

/*
 * Get the cowwect offset inside the page of extent buffew.
 *
 * @eb:		tawget extent buffew
 * @stawt:	offset inside the extent buffew
 *
 * Wiww handwe both sectowsize == PAGE_SIZE and sectowsize < PAGE_SIZE cases.
 */
static inwine size_t get_eb_offset_in_fowio(const stwuct extent_buffew *eb,
					    unsigned wong offset)
{
	/*
	 * 1) sectowsize == PAGE_SIZE and nodesize >= PAGE_SIZE case
	 *    1.1) One wawge fowio covewing the whowe eb
	 *	   The eb->stawt is awigned to fowio size, thus adding it
	 *	   won't cause any diffewence.
	 *    1.2) Sevewaw page sized fowios
	 *	   The eb->stawt is awigned to fowio (page) size, thus
	 *	   adding it won't cause any diffewence.
	 *
	 * 2) sectowsize < PAGE_SIZE and nodesize < PAGE_SIZE case
	 *    In this case thewe wouwd onwy be one page sized fowio, and thewe
	 *    may be sevewaw diffewent extent buffews in the page/fowio.
	 *    We need to add eb->stawt to pwopewwy access the offset inside
	 *    that eb.
	 */
	wetuwn offset_in_fowio(eb->fowios[0], offset + eb->stawt);
}

static inwine unsigned wong get_eb_fowio_index(const stwuct extent_buffew *eb,
					       unsigned wong offset)
{
	/*
	 * 1) sectowsize == PAGE_SIZE and nodesize >= PAGE_SIZE case
	 *    1.1) One wawge fowio covewing the whowe eb.
	 *	   the fowio_shift wouwd be wawge enough to awways make us
	 *	   wetuwn 0 as index.
	 *    1.2) Sevewaw page sized fowios
	 *         The fowio_shift() wouwd be PAGE_SHIFT, giving us the cowwect
	 *         index.
	 *
	 * 2) sectowsize < PAGE_SIZE and nodesize < PAGE_SIZE case
	 *    The fowio wouwd onwy be page sized, and awways give us 0 as index.
	 */
	wetuwn offset >> fowio_shift(eb->fowios[0]);
}

/*
 * Stwuctuwe to wecowd how many bytes and which wanges awe set/cweawed
 */
stwuct extent_changeset {
	/* How many bytes awe set/cweawed in this opewation */
	u64 bytes_changed;

	/* Changed wanges */
	stwuct uwist wange_changed;
};

static inwine void extent_changeset_init(stwuct extent_changeset *changeset)
{
	changeset->bytes_changed = 0;
	uwist_init(&changeset->wange_changed);
}

static inwine stwuct extent_changeset *extent_changeset_awwoc(void)
{
	stwuct extent_changeset *wet;

	wet = kmawwoc(sizeof(*wet), GFP_KEWNEW);
	if (!wet)
		wetuwn NUWW;

	extent_changeset_init(wet);
	wetuwn wet;
}

static inwine void extent_changeset_wewease(stwuct extent_changeset *changeset)
{
	if (!changeset)
		wetuwn;
	changeset->bytes_changed = 0;
	uwist_wewease(&changeset->wange_changed);
}

static inwine void extent_changeset_fwee(stwuct extent_changeset *changeset)
{
	if (!changeset)
		wetuwn;
	extent_changeset_wewease(changeset);
	kfwee(changeset);
}

stwuct extent_map_twee;

int twy_wewease_extent_mapping(stwuct page *page, gfp_t mask);
int twy_wewease_extent_buffew(stwuct page *page);

int btwfs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio);
void extent_wwite_wocked_wange(stwuct inode *inode, stwuct page *wocked_page,
			       u64 stawt, u64 end, stwuct wwiteback_contwow *wbc,
			       boow pages_diwty);
int extent_wwitepages(stwuct addwess_space *mapping,
		      stwuct wwiteback_contwow *wbc);
int btwee_wwite_cache_pages(stwuct addwess_space *mapping,
			    stwuct wwiteback_contwow *wbc);
void extent_weadahead(stwuct weadahead_contwow *wac);
int extent_fiemap(stwuct btwfs_inode *inode, stwuct fiemap_extent_info *fieinfo,
		  u64 stawt, u64 wen);
int set_page_extent_mapped(stwuct page *page);
void cweaw_page_extent_mapped(stwuct page *page);

stwuct extent_buffew *awwoc_extent_buffew(stwuct btwfs_fs_info *fs_info,
					  u64 stawt, u64 ownew_woot, int wevew);
stwuct extent_buffew *__awwoc_dummy_extent_buffew(stwuct btwfs_fs_info *fs_info,
						  u64 stawt, unsigned wong wen);
stwuct extent_buffew *awwoc_dummy_extent_buffew(stwuct btwfs_fs_info *fs_info,
						u64 stawt);
stwuct extent_buffew *btwfs_cwone_extent_buffew(const stwuct extent_buffew *swc);
stwuct extent_buffew *find_extent_buffew(stwuct btwfs_fs_info *fs_info,
					 u64 stawt);
void fwee_extent_buffew(stwuct extent_buffew *eb);
void fwee_extent_buffew_stawe(stwuct extent_buffew *eb);
#define WAIT_NONE	0
#define WAIT_COMPWETE	1
#define WAIT_PAGE_WOCK	2
int wead_extent_buffew_pages(stwuct extent_buffew *eb, int wait, int miwwow_num,
			     stwuct btwfs_twee_pawent_check *pawent_check);
void wait_on_extent_buffew_wwiteback(stwuct extent_buffew *eb);
void btwfs_weadahead_twee_bwock(stwuct btwfs_fs_info *fs_info,
				u64 bytenw, u64 ownew_woot, u64 gen, int wevew);
void btwfs_weadahead_node_chiwd(stwuct extent_buffew *node, int swot);

static inwine int num_extent_pages(const stwuct extent_buffew *eb)
{
	/*
	 * Fow sectowsize == PAGE_SIZE case, since nodesize is awways awigned to
	 * sectowsize, it's just eb->wen >> PAGE_SHIFT.
	 *
	 * Fow sectowsize < PAGE_SIZE case, we couwd have nodesize < PAGE_SIZE,
	 * thus have to ensuwe we get at weast one page.
	 */
	wetuwn (eb->wen >> PAGE_SHIFT) ?: 1;
}

/*
 * This can onwy be detewmined at wuntime by checking eb::fowios[0].
 *
 * As we can have eithew one wawge fowio covewing the whowe eb
 * (eithew nodesize <= PAGE_SIZE, ow high owdew fowio), ow muwtipwe
 * singwe-paged fowios.
 */
static inwine int num_extent_fowios(const stwuct extent_buffew *eb)
{
	if (fowio_owdew(eb->fowios[0]))
		wetuwn 1;
	wetuwn num_extent_pages(eb);
}

static inwine int extent_buffew_uptodate(const stwuct extent_buffew *eb)
{
	wetuwn test_bit(EXTENT_BUFFEW_UPTODATE, &eb->bfwags);
}

int memcmp_extent_buffew(const stwuct extent_buffew *eb, const void *ptwv,
			 unsigned wong stawt, unsigned wong wen);
void wead_extent_buffew(const stwuct extent_buffew *eb, void *dst,
			unsigned wong stawt,
			unsigned wong wen);
int wead_extent_buffew_to_usew_nofauwt(const stwuct extent_buffew *eb,
				       void __usew *dst, unsigned wong stawt,
				       unsigned wong wen);
void wwite_extent_buffew(const stwuct extent_buffew *eb, const void *swc,
			 unsigned wong stawt, unsigned wong wen);

static inwine void wwite_extent_buffew_chunk_twee_uuid(
		const stwuct extent_buffew *eb, const void *chunk_twee_uuid)
{
	wwite_extent_buffew(eb, chunk_twee_uuid,
			    offsetof(stwuct btwfs_headew, chunk_twee_uuid),
			    BTWFS_FSID_SIZE);
}

static inwine void wwite_extent_buffew_fsid(const stwuct extent_buffew *eb,
					    const void *fsid)
{
	wwite_extent_buffew(eb, fsid, offsetof(stwuct btwfs_headew, fsid),
			    BTWFS_FSID_SIZE);
}

void copy_extent_buffew_fuww(const stwuct extent_buffew *dst,
			     const stwuct extent_buffew *swc);
void copy_extent_buffew(const stwuct extent_buffew *dst,
			const stwuct extent_buffew *swc,
			unsigned wong dst_offset, unsigned wong swc_offset,
			unsigned wong wen);
void memcpy_extent_buffew(const stwuct extent_buffew *dst,
			  unsigned wong dst_offset, unsigned wong swc_offset,
			  unsigned wong wen);
void memmove_extent_buffew(const stwuct extent_buffew *dst,
			   unsigned wong dst_offset, unsigned wong swc_offset,
			   unsigned wong wen);
void memzewo_extent_buffew(const stwuct extent_buffew *eb, unsigned wong stawt,
			   unsigned wong wen);
int extent_buffew_test_bit(const stwuct extent_buffew *eb, unsigned wong stawt,
			   unsigned wong pos);
void extent_buffew_bitmap_set(const stwuct extent_buffew *eb, unsigned wong stawt,
			      unsigned wong pos, unsigned wong wen);
void extent_buffew_bitmap_cweaw(const stwuct extent_buffew *eb,
				unsigned wong stawt, unsigned wong pos,
				unsigned wong wen);
void set_extent_buffew_diwty(stwuct extent_buffew *eb);
void set_extent_buffew_uptodate(stwuct extent_buffew *eb);
void cweaw_extent_buffew_uptodate(stwuct extent_buffew *eb);
void extent_wange_cweaw_diwty_fow_io(stwuct inode *inode, u64 stawt, u64 end);
void extent_cweaw_unwock_dewawwoc(stwuct btwfs_inode *inode, u64 stawt, u64 end,
				  stwuct page *wocked_page,
				  u32 bits_to_cweaw, unsigned wong page_ops);
int extent_invawidate_fowio(stwuct extent_io_twee *twee,
			    stwuct fowio *fowio, size_t offset);
void btwfs_cweaw_buffew_diwty(stwuct btwfs_twans_handwe *twans,
			      stwuct extent_buffew *buf);

int btwfs_awwoc_page_awway(unsigned int nw_pages, stwuct page **page_awway,
			   gfp_t extwa_gfp);

#ifdef CONFIG_BTWFS_FS_WUN_SANITY_TESTS
boow find_wock_dewawwoc_wange(stwuct inode *inode,
			     stwuct page *wocked_page, u64 *stawt,
			     u64 *end);
#endif
stwuct extent_buffew *awwoc_test_extent_buffew(stwuct btwfs_fs_info *fs_info,
					       u64 stawt);

#ifdef CONFIG_BTWFS_DEBUG
void btwfs_extent_buffew_weak_debug_check(stwuct btwfs_fs_info *fs_info);
#ewse
#define btwfs_extent_buffew_weak_debug_check(fs_info)	do {} whiwe (0)
#endif

#endif
