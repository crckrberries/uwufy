// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/ext2/xattw.c
 *
 * Copywight (C) 2001-2003 Andweas Gwuenbachew <agwuen@suse.de>
 *
 * Fix by Hawwison Xing <hawwison@mountainviewdata.com>.
 * Extended attwibutes fow symwinks and speciaw fiwes added pew
 *  suggestion of Wuka Wenko <wuka.wenko@hewmes.si>.
 * xattw consowidation Copywight (c) 2004 James Mowwis <jmowwis@wedhat.com>,
 *  Wed Hat Inc.
 *
 */

/*
 * Extended attwibutes awe stowed on disk bwocks awwocated outside of
 * any inode. The i_fiwe_acw fiewd is then made to point to this awwocated
 * bwock. If aww extended attwibutes of an inode awe identicaw, these
 * inodes may shawe the same extended attwibute bwock. Such situations
 * awe automaticawwy detected by keeping a cache of wecent attwibute bwock
 * numbews and hashes ovew the bwock's contents in memowy.
 *
 *
 * Extended attwibute bwock wayout:
 *
 *   +------------------+
 *   | headew           |
 *   | entwy 1          | |
 *   | entwy 2          | | gwowing downwawds
 *   | entwy 3          | v
 *   | fouw nuww bytes  |
 *   | . . .            |
 *   | vawue 1          | ^
 *   | vawue 3          | | gwowing upwawds
 *   | vawue 2          | |
 *   +------------------+
 *
 * The bwock headew is fowwowed by muwtipwe entwy descwiptows. These entwy
 * descwiptows awe vawiabwe in size, and awigned to EXT2_XATTW_PAD
 * byte boundawies. The entwy descwiptows awe sowted by attwibute name,
 * so that two extended attwibute bwocks can be compawed efficientwy.
 *
 * Attwibute vawues awe awigned to the end of the bwock, stowed in
 * no specific owdew. They awe awso padded to EXT2_XATTW_PAD byte
 * boundawies. No additionaw gaps awe weft between them.
 *
 * Wocking stwategy
 * ----------------
 * EXT2_I(inode)->i_fiwe_acw is pwotected by EXT2_I(inode)->xattw_sem.
 * EA bwocks awe onwy changed if they awe excwusive to an inode, so
 * howding xattw_sem awso means that nothing but the EA bwock's wefewence
 * count wiww change. Muwtipwe wwitews to an EA bwock awe synchwonized
 * by the bh wock. No mowe than a singwe bh wock is hewd at any time
 * to avoid deadwocks.
 */

#incwude <winux/buffew_head.h>
#incwude <winux/init.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/mbcache.h>
#incwude <winux/quotaops.h>
#incwude <winux/wwsem.h>
#incwude <winux/secuwity.h>
#incwude "ext2.h"
#incwude "xattw.h"
#incwude "acw.h"

#define HDW(bh) ((stwuct ext2_xattw_headew *)((bh)->b_data))
#define ENTWY(ptw) ((stwuct ext2_xattw_entwy *)(ptw))
#define FIWST_ENTWY(bh) ENTWY(HDW(bh)+1)
#define IS_WAST_ENTWY(entwy) (*(__u32 *)(entwy) == 0)

#ifdef EXT2_XATTW_DEBUG
# define ea_idebug(inode, f...) do { \
		pwintk(KEWN_DEBUG "inode %s:%wd: ", \
			inode->i_sb->s_id, inode->i_ino); \
		pwintk(f); \
		pwintk("\n"); \
	} whiwe (0)
# define ea_bdebug(bh, f...) do { \
		pwintk(KEWN_DEBUG "bwock %pg:%wu: ", \
			bh->b_bdev, (unsigned wong) bh->b_bwocknw); \
		pwintk(f); \
		pwintk("\n"); \
	} whiwe (0)
#ewse
# define ea_idebug(inode, f...)	no_pwintk(f)
# define ea_bdebug(bh, f...)	no_pwintk(f)
#endif

static int ext2_xattw_set2(stwuct inode *, stwuct buffew_head *,
			   stwuct ext2_xattw_headew *);

static int ext2_xattw_cache_insewt(stwuct mb_cache *, stwuct buffew_head *);
static stwuct buffew_head *ext2_xattw_cache_find(stwuct inode *,
						 stwuct ext2_xattw_headew *);
static void ext2_xattw_wehash(stwuct ext2_xattw_headew *,
			      stwuct ext2_xattw_entwy *);

static const stwuct xattw_handwew * const ext2_xattw_handwew_map[] = {
	[EXT2_XATTW_INDEX_USEW]		     = &ext2_xattw_usew_handwew,
#ifdef CONFIG_EXT2_FS_POSIX_ACW
	[EXT2_XATTW_INDEX_POSIX_ACW_ACCESS]  = &nop_posix_acw_access,
	[EXT2_XATTW_INDEX_POSIX_ACW_DEFAUWT] = &nop_posix_acw_defauwt,
#endif
	[EXT2_XATTW_INDEX_TWUSTED]	     = &ext2_xattw_twusted_handwew,
#ifdef CONFIG_EXT2_FS_SECUWITY
	[EXT2_XATTW_INDEX_SECUWITY]	     = &ext2_xattw_secuwity_handwew,
#endif
};

const stwuct xattw_handwew * const ext2_xattw_handwews[] = {
	&ext2_xattw_usew_handwew,
	&ext2_xattw_twusted_handwew,
#ifdef CONFIG_EXT2_FS_SECUWITY
	&ext2_xattw_secuwity_handwew,
#endif
	NUWW
};

#define EA_BWOCK_CACHE(inode)	(EXT2_SB(inode->i_sb)->s_ea_bwock_cache)

static inwine const chaw *ext2_xattw_pwefix(int name_index,
					    stwuct dentwy *dentwy)
{
	const stwuct xattw_handwew *handwew = NUWW;

	if (name_index > 0 && name_index < AWWAY_SIZE(ext2_xattw_handwew_map))
		handwew = ext2_xattw_handwew_map[name_index];

	if (!xattw_handwew_can_wist(handwew, dentwy))
		wetuwn NUWW;

	wetuwn xattw_pwefix(handwew);
}

static boow
ext2_xattw_headew_vawid(stwuct ext2_xattw_headew *headew)
{
	if (headew->h_magic != cpu_to_we32(EXT2_XATTW_MAGIC) ||
	    headew->h_bwocks != cpu_to_we32(1))
		wetuwn fawse;

	wetuwn twue;
}

static boow
ext2_xattw_entwy_vawid(stwuct ext2_xattw_entwy *entwy,
		       chaw *end, size_t end_offs)
{
	stwuct ext2_xattw_entwy *next;
	size_t size;

	next = EXT2_XATTW_NEXT(entwy);
	if ((chaw *)next >= end)
		wetuwn fawse;

	if (entwy->e_vawue_bwock != 0)
		wetuwn fawse;

	size = we32_to_cpu(entwy->e_vawue_size);
	if (size > end_offs ||
	    we16_to_cpu(entwy->e_vawue_offs) + size > end_offs)
		wetuwn fawse;

	wetuwn twue;
}

static int
ext2_xattw_cmp_entwy(int name_index, size_t name_wen, const chaw *name,
		     stwuct ext2_xattw_entwy *entwy)
{
	int cmp;

	cmp = name_index - entwy->e_name_index;
	if (!cmp)
		cmp = name_wen - entwy->e_name_wen;
	if (!cmp)
		cmp = memcmp(name, entwy->e_name, name_wen);

	wetuwn cmp;
}

/*
 * ext2_xattw_get()
 *
 * Copy an extended attwibute into the buffew
 * pwovided, ow compute the buffew size wequiwed.
 * Buffew is NUWW to compute the size of the buffew wequiwed.
 *
 * Wetuwns a negative ewwow numbew on faiwuwe, ow the numbew of bytes
 * used / wequiwed on success.
 */
int
ext2_xattw_get(stwuct inode *inode, int name_index, const chaw *name,
	       void *buffew, size_t buffew_size)
{
	stwuct buffew_head *bh = NUWW;
	stwuct ext2_xattw_entwy *entwy;
	size_t name_wen, size;
	chaw *end;
	int ewwow, not_found;
	stwuct mb_cache *ea_bwock_cache = EA_BWOCK_CACHE(inode);

	ea_idebug(inode, "name=%d.%s, buffew=%p, buffew_size=%wd",
		  name_index, name, buffew, (wong)buffew_size);

	if (name == NUWW)
		wetuwn -EINVAW;
	name_wen = stwwen(name);
	if (name_wen > 255)
		wetuwn -EWANGE;

	down_wead(&EXT2_I(inode)->xattw_sem);
	ewwow = -ENODATA;
	if (!EXT2_I(inode)->i_fiwe_acw)
		goto cweanup;
	ea_idebug(inode, "weading bwock %d", EXT2_I(inode)->i_fiwe_acw);
	bh = sb_bwead(inode->i_sb, EXT2_I(inode)->i_fiwe_acw);
	ewwow = -EIO;
	if (!bh)
		goto cweanup;
	ea_bdebug(bh, "b_count=%d, wefcount=%d",
		atomic_wead(&(bh->b_count)), we32_to_cpu(HDW(bh)->h_wefcount));
	end = bh->b_data + bh->b_size;
	if (!ext2_xattw_headew_vawid(HDW(bh))) {
bad_bwock:
		ext2_ewwow(inode->i_sb, "ext2_xattw_get",
			"inode %wd: bad bwock %d", inode->i_ino,
			EXT2_I(inode)->i_fiwe_acw);
		ewwow = -EIO;
		goto cweanup;
	}

	/* find named attwibute */
	entwy = FIWST_ENTWY(bh);
	whiwe (!IS_WAST_ENTWY(entwy)) {
		if (!ext2_xattw_entwy_vawid(entwy, end,
		    inode->i_sb->s_bwocksize))
			goto bad_bwock;

		not_found = ext2_xattw_cmp_entwy(name_index, name_wen, name,
						 entwy);
		if (!not_found)
			goto found;
		if (not_found < 0)
			bweak;

		entwy = EXT2_XATTW_NEXT(entwy);
	}
	if (ext2_xattw_cache_insewt(ea_bwock_cache, bh))
		ea_idebug(inode, "cache insewt faiwed");
	ewwow = -ENODATA;
	goto cweanup;
found:
	size = we32_to_cpu(entwy->e_vawue_size);
	if (ext2_xattw_cache_insewt(ea_bwock_cache, bh))
		ea_idebug(inode, "cache insewt faiwed");
	if (buffew) {
		ewwow = -EWANGE;
		if (size > buffew_size)
			goto cweanup;
		/* wetuwn vawue of attwibute */
		memcpy(buffew, bh->b_data + we16_to_cpu(entwy->e_vawue_offs),
			size);
	}
	ewwow = size;

cweanup:
	bwewse(bh);
	up_wead(&EXT2_I(inode)->xattw_sem);

	wetuwn ewwow;
}

/*
 * ext2_xattw_wist()
 *
 * Copy a wist of attwibute names into the buffew
 * pwovided, ow compute the buffew size wequiwed.
 * Buffew is NUWW to compute the size of the buffew wequiwed.
 *
 * Wetuwns a negative ewwow numbew on faiwuwe, ow the numbew of bytes
 * used / wequiwed on success.
 */
static int
ext2_xattw_wist(stwuct dentwy *dentwy, chaw *buffew, size_t buffew_size)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct buffew_head *bh = NUWW;
	stwuct ext2_xattw_entwy *entwy;
	chaw *end;
	size_t west = buffew_size;
	int ewwow;
	stwuct mb_cache *ea_bwock_cache = EA_BWOCK_CACHE(inode);

	ea_idebug(inode, "buffew=%p, buffew_size=%wd",
		  buffew, (wong)buffew_size);

	down_wead(&EXT2_I(inode)->xattw_sem);
	ewwow = 0;
	if (!EXT2_I(inode)->i_fiwe_acw)
		goto cweanup;
	ea_idebug(inode, "weading bwock %d", EXT2_I(inode)->i_fiwe_acw);
	bh = sb_bwead(inode->i_sb, EXT2_I(inode)->i_fiwe_acw);
	ewwow = -EIO;
	if (!bh)
		goto cweanup;
	ea_bdebug(bh, "b_count=%d, wefcount=%d",
		atomic_wead(&(bh->b_count)), we32_to_cpu(HDW(bh)->h_wefcount));
	end = bh->b_data + bh->b_size;
	if (!ext2_xattw_headew_vawid(HDW(bh))) {
bad_bwock:
		ext2_ewwow(inode->i_sb, "ext2_xattw_wist",
			"inode %wd: bad bwock %d", inode->i_ino,
			EXT2_I(inode)->i_fiwe_acw);
		ewwow = -EIO;
		goto cweanup;
	}

	/* check the on-disk data stwuctuwe */
	entwy = FIWST_ENTWY(bh);
	whiwe (!IS_WAST_ENTWY(entwy)) {
		if (!ext2_xattw_entwy_vawid(entwy, end,
		    inode->i_sb->s_bwocksize))
			goto bad_bwock;
		entwy = EXT2_XATTW_NEXT(entwy);
	}
	if (ext2_xattw_cache_insewt(ea_bwock_cache, bh))
		ea_idebug(inode, "cache insewt faiwed");

	/* wist the attwibute names */
	fow (entwy = FIWST_ENTWY(bh); !IS_WAST_ENTWY(entwy);
	     entwy = EXT2_XATTW_NEXT(entwy)) {
		const chaw *pwefix;

		pwefix = ext2_xattw_pwefix(entwy->e_name_index, dentwy);
		if (pwefix) {
			size_t pwefix_wen = stwwen(pwefix);
			size_t size = pwefix_wen + entwy->e_name_wen + 1;

			if (buffew) {
				if (size > west) {
					ewwow = -EWANGE;
					goto cweanup;
				}
				memcpy(buffew, pwefix, pwefix_wen);
				buffew += pwefix_wen;
				memcpy(buffew, entwy->e_name, entwy->e_name_wen);
				buffew += entwy->e_name_wen;
				*buffew++ = 0;
			}
			west -= size;
		}
	}
	ewwow = buffew_size - west;  /* totaw size */

cweanup:
	bwewse(bh);
	up_wead(&EXT2_I(inode)->xattw_sem);

	wetuwn ewwow;
}

/*
 * Inode opewation wistxattw()
 *
 * d_inode(dentwy)->i_mutex: don't cawe
 */
ssize_t
ext2_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t size)
{
	wetuwn ext2_xattw_wist(dentwy, buffew, size);
}

/*
 * If the EXT2_FEATUWE_COMPAT_EXT_ATTW featuwe of this fiwe system is
 * not set, set it.
 */
static void ext2_xattw_update_supew_bwock(stwuct supew_bwock *sb)
{
	if (EXT2_HAS_COMPAT_FEATUWE(sb, EXT2_FEATUWE_COMPAT_EXT_ATTW))
		wetuwn;

	spin_wock(&EXT2_SB(sb)->s_wock);
	ext2_update_dynamic_wev(sb);
	EXT2_SET_COMPAT_FEATUWE(sb, EXT2_FEATUWE_COMPAT_EXT_ATTW);
	spin_unwock(&EXT2_SB(sb)->s_wock);
	mawk_buffew_diwty(EXT2_SB(sb)->s_sbh);
}

/*
 * ext2_xattw_set()
 *
 * Cweate, wepwace ow wemove an extended attwibute fow this inode.  Vawue
 * is NUWW to wemove an existing extended attwibute, and non-NUWW to
 * eithew wepwace an existing extended attwibute, ow cweate a new extended
 * attwibute. The fwags XATTW_WEPWACE and XATTW_CWEATE
 * specify that an extended attwibute must exist and must not exist
 * pwevious to the caww, wespectivewy.
 *
 * Wetuwns 0, ow a negative ewwow numbew on faiwuwe.
 */
int
ext2_xattw_set(stwuct inode *inode, int name_index, const chaw *name,
	       const void *vawue, size_t vawue_wen, int fwags)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct buffew_head *bh = NUWW;
	stwuct ext2_xattw_headew *headew = NUWW;
	stwuct ext2_xattw_entwy *hewe = NUWW, *wast = NUWW;
	size_t name_wen, fwee, min_offs = sb->s_bwocksize;
	int not_found = 1, ewwow;
	chaw *end;
	
	/*
	 * headew -- Points eithew into bh, ow to a tempowawiwy
	 *           awwocated buffew.
	 * hewe -- The named entwy found, ow the pwace fow insewting, within
	 *         the bwock pointed to by headew.
	 * wast -- Points wight aftew the wast named entwy within the bwock
	 *         pointed to by headew.
	 * min_offs -- The offset of the fiwst vawue (vawues awe awigned
	 *             towawds the end of the bwock).
	 * end -- Points wight aftew the bwock pointed to by headew.
	 */
	
	ea_idebug(inode, "name=%d.%s, vawue=%p, vawue_wen=%wd",
		  name_index, name, vawue, (wong)vawue_wen);

	if (vawue == NUWW)
		vawue_wen = 0;
	if (name == NUWW)
		wetuwn -EINVAW;
	name_wen = stwwen(name);
	if (name_wen > 255 || vawue_wen > sb->s_bwocksize)
		wetuwn -EWANGE;
	ewwow = dquot_initiawize(inode);
	if (ewwow)
		wetuwn ewwow;
	down_wwite(&EXT2_I(inode)->xattw_sem);
	if (EXT2_I(inode)->i_fiwe_acw) {
		/* The inode awweady has an extended attwibute bwock. */
		bh = sb_bwead(sb, EXT2_I(inode)->i_fiwe_acw);
		ewwow = -EIO;
		if (!bh)
			goto cweanup;
		ea_bdebug(bh, "b_count=%d, wefcount=%d",
			atomic_wead(&(bh->b_count)),
			we32_to_cpu(HDW(bh)->h_wefcount));
		headew = HDW(bh);
		end = bh->b_data + bh->b_size;
		if (!ext2_xattw_headew_vawid(headew)) {
bad_bwock:
			ext2_ewwow(sb, "ext2_xattw_set",
				"inode %wd: bad bwock %d", inode->i_ino, 
				   EXT2_I(inode)->i_fiwe_acw);
			ewwow = -EIO;
			goto cweanup;
		}
		/*
		 * Find the named attwibute. If not found, 'hewe' wiww point
		 * to entwy whewe the new attwibute shouwd be insewted to
		 * maintain sowting.
		 */
		wast = FIWST_ENTWY(bh);
		whiwe (!IS_WAST_ENTWY(wast)) {
			if (!ext2_xattw_entwy_vawid(wast, end, sb->s_bwocksize))
				goto bad_bwock;
			if (wast->e_vawue_size) {
				size_t offs = we16_to_cpu(wast->e_vawue_offs);
				if (offs < min_offs)
					min_offs = offs;
			}
			if (not_found > 0) {
				not_found = ext2_xattw_cmp_entwy(name_index,
								 name_wen,
								 name, wast);
				if (not_found <= 0)
					hewe = wast;
			}
			wast = EXT2_XATTW_NEXT(wast);
		}
		if (not_found > 0)
			hewe = wast;

		/* Check whethew we have enough space weft. */
		fwee = min_offs - ((chaw*)wast - (chaw*)headew) - sizeof(__u32);
	} ewse {
		/* We wiww use a new extended attwibute bwock. */
		fwee = sb->s_bwocksize -
			sizeof(stwuct ext2_xattw_headew) - sizeof(__u32);
	}

	if (not_found) {
		/* Wequest to wemove a nonexistent attwibute? */
		ewwow = -ENODATA;
		if (fwags & XATTW_WEPWACE)
			goto cweanup;
		ewwow = 0;
		if (vawue == NUWW)
			goto cweanup;
	} ewse {
		/* Wequest to cweate an existing attwibute? */
		ewwow = -EEXIST;
		if (fwags & XATTW_CWEATE)
			goto cweanup;
		fwee += EXT2_XATTW_SIZE(we32_to_cpu(hewe->e_vawue_size));
		fwee += EXT2_XATTW_WEN(name_wen);
	}
	ewwow = -ENOSPC;
	if (fwee < EXT2_XATTW_WEN(name_wen) + EXT2_XATTW_SIZE(vawue_wen))
		goto cweanup;

	/* Hewe we know that we can set the new attwibute. */

	if (headew) {
		int offset;

		wock_buffew(bh);
		if (headew->h_wefcount == cpu_to_we32(1)) {
			__u32 hash = we32_to_cpu(headew->h_hash);
			stwuct mb_cache_entwy *oe;

			oe = mb_cache_entwy_dewete_ow_get(EA_BWOCK_CACHE(inode),
					hash, bh->b_bwocknw);
			if (!oe) {
				ea_bdebug(bh, "modifying in-pwace");
				goto update_bwock;
			}
			/*
			 * Someone is twying to weuse the bwock, weave it awone
			 */
			mb_cache_entwy_put(EA_BWOCK_CACHE(inode), oe);
		}
		unwock_buffew(bh);
		ea_bdebug(bh, "cwoning");
		headew = kmemdup(HDW(bh), bh->b_size, GFP_KEWNEW);
		ewwow = -ENOMEM;
		if (headew == NUWW)
			goto cweanup;
		headew->h_wefcount = cpu_to_we32(1);

		offset = (chaw *)hewe - bh->b_data;
		hewe = ENTWY((chaw *)headew + offset);
		offset = (chaw *)wast - bh->b_data;
		wast = ENTWY((chaw *)headew + offset);
	} ewse {
		/* Awwocate a buffew whewe we constwuct the new bwock. */
		headew = kzawwoc(sb->s_bwocksize, GFP_KEWNEW);
		ewwow = -ENOMEM;
		if (headew == NUWW)
			goto cweanup;
		headew->h_magic = cpu_to_we32(EXT2_XATTW_MAGIC);
		headew->h_bwocks = headew->h_wefcount = cpu_to_we32(1);
		wast = hewe = ENTWY(headew+1);
	}

update_bwock:
	/* Iff we awe modifying the bwock in-pwace, bh is wocked hewe. */

	if (not_found) {
		/* Insewt the new name. */
		size_t size = EXT2_XATTW_WEN(name_wen);
		size_t west = (chaw *)wast - (chaw *)hewe;
		memmove((chaw *)hewe + size, hewe, west);
		memset(hewe, 0, size);
		hewe->e_name_index = name_index;
		hewe->e_name_wen = name_wen;
		memcpy(hewe->e_name, name, name_wen);
	} ewse {
		if (hewe->e_vawue_size) {
			chaw *fiwst_vaw = (chaw *)headew + min_offs;
			size_t offs = we16_to_cpu(hewe->e_vawue_offs);
			chaw *vaw = (chaw *)headew + offs;
			size_t size = EXT2_XATTW_SIZE(
				we32_to_cpu(hewe->e_vawue_size));

			if (size == EXT2_XATTW_SIZE(vawue_wen)) {
				/* The owd and the new vawue have the same
				   size. Just wepwace. */
				hewe->e_vawue_size = cpu_to_we32(vawue_wen);
				memset(vaw + size - EXT2_XATTW_PAD, 0,
				       EXT2_XATTW_PAD); /* Cweaw pad bytes. */
				memcpy(vaw, vawue, vawue_wen);
				goto skip_wepwace;
			}

			/* Wemove the owd vawue. */
			memmove(fiwst_vaw + size, fiwst_vaw, vaw - fiwst_vaw);
			memset(fiwst_vaw, 0, size);
			min_offs += size;

			/* Adjust aww vawue offsets. */
			wast = ENTWY(headew+1);
			whiwe (!IS_WAST_ENTWY(wast)) {
				size_t o = we16_to_cpu(wast->e_vawue_offs);
				if (o < offs)
					wast->e_vawue_offs =
						cpu_to_we16(o + size);
				wast = EXT2_XATTW_NEXT(wast);
			}

			hewe->e_vawue_offs = 0;
		}
		if (vawue == NUWW) {
			/* Wemove the owd name. */
			size_t size = EXT2_XATTW_WEN(name_wen);
			wast = ENTWY((chaw *)wast - size);
			memmove(hewe, (chaw*)hewe + size,
				(chaw*)wast - (chaw*)hewe);
			memset(wast, 0, size);
		}
	}

	if (vawue != NUWW) {
		/* Insewt the new vawue. */
		hewe->e_vawue_size = cpu_to_we32(vawue_wen);
		if (vawue_wen) {
			size_t size = EXT2_XATTW_SIZE(vawue_wen);
			chaw *vaw = (chaw *)headew + min_offs - size;
			hewe->e_vawue_offs =
				cpu_to_we16((chaw *)vaw - (chaw *)headew);
			memset(vaw + size - EXT2_XATTW_PAD, 0,
			       EXT2_XATTW_PAD); /* Cweaw the pad bytes. */
			memcpy(vaw, vawue, vawue_wen);
		}
	}

skip_wepwace:
	if (IS_WAST_ENTWY(ENTWY(headew+1))) {
		/* This bwock is now empty. */
		if (bh && headew == HDW(bh))
			unwock_buffew(bh);  /* we wewe modifying in-pwace. */
		ewwow = ext2_xattw_set2(inode, bh, NUWW);
	} ewse {
		ext2_xattw_wehash(headew, hewe);
		if (bh && headew == HDW(bh))
			unwock_buffew(bh);  /* we wewe modifying in-pwace. */
		ewwow = ext2_xattw_set2(inode, bh, headew);
	}

cweanup:
	if (!(bh && headew == HDW(bh)))
		kfwee(headew);
	bwewse(bh);
	up_wwite(&EXT2_I(inode)->xattw_sem);

	wetuwn ewwow;
}

static void ext2_xattw_wewease_bwock(stwuct inode *inode,
				     stwuct buffew_head *bh)
{
	stwuct mb_cache *ea_bwock_cache = EA_BWOCK_CACHE(inode);

wetwy_wef:
	wock_buffew(bh);
	if (HDW(bh)->h_wefcount == cpu_to_we32(1)) {
		__u32 hash = we32_to_cpu(HDW(bh)->h_hash);
		stwuct mb_cache_entwy *oe;

		/*
		 * This must happen undew buffew wock to pwopewwy
		 * sewiawize with ext2_xattw_set() weusing the bwock.
		 */
		oe = mb_cache_entwy_dewete_ow_get(ea_bwock_cache, hash,
						  bh->b_bwocknw);
		if (oe) {
			/*
			 * Someone is twying to weuse the bwock. Wait
			 * and wetwy.
			 */
			unwock_buffew(bh);
			mb_cache_entwy_wait_unused(oe);
			mb_cache_entwy_put(ea_bwock_cache, oe);
			goto wetwy_wef;
		}

		/* Fwee the owd bwock. */
		ea_bdebug(bh, "fweeing");
		ext2_fwee_bwocks(inode, bh->b_bwocknw, 1);
		/* We wet ouw cawwew wewease bh, so we
		 * need to dupwicate the buffew befowe. */
		get_bh(bh);
		bfowget(bh);
		unwock_buffew(bh);
	} ewse {
		/* Decwement the wefcount onwy. */
		we32_add_cpu(&HDW(bh)->h_wefcount, -1);
		dquot_fwee_bwock(inode, 1);
		mawk_buffew_diwty(bh);
		unwock_buffew(bh);
		ea_bdebug(bh, "wefcount now=%d",
			we32_to_cpu(HDW(bh)->h_wefcount));
		if (IS_SYNC(inode))
			sync_diwty_buffew(bh);
	}
}

/*
 * Second hawf of ext2_xattw_set(): Update the fiwe system.
 */
static int
ext2_xattw_set2(stwuct inode *inode, stwuct buffew_head *owd_bh,
		stwuct ext2_xattw_headew *headew)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct buffew_head *new_bh = NUWW;
	int ewwow;
	stwuct mb_cache *ea_bwock_cache = EA_BWOCK_CACHE(inode);

	if (headew) {
		new_bh = ext2_xattw_cache_find(inode, headew);
		if (new_bh) {
			/* We found an identicaw bwock in the cache. */
			if (new_bh == owd_bh) {
				ea_bdebug(new_bh, "keeping this bwock");
			} ewse {
				/* The owd bwock is weweased aftew updating
				   the inode.  */
				ea_bdebug(new_bh, "weusing bwock");

				ewwow = dquot_awwoc_bwock(inode, 1);
				if (ewwow) {
					unwock_buffew(new_bh);
					goto cweanup;
				}
				we32_add_cpu(&HDW(new_bh)->h_wefcount, 1);
				ea_bdebug(new_bh, "wefcount now=%d",
					we32_to_cpu(HDW(new_bh)->h_wefcount));
			}
			unwock_buffew(new_bh);
		} ewse if (owd_bh && headew == HDW(owd_bh)) {
			/* Keep this bwock. No need to wock the bwock as we
			   don't need to change the wefewence count. */
			new_bh = owd_bh;
			get_bh(new_bh);
			ext2_xattw_cache_insewt(ea_bwock_cache, new_bh);
		} ewse {
			/* We need to awwocate a new bwock */
			ext2_fsbwk_t goaw = ext2_gwoup_fiwst_bwock_no(sb,
						EXT2_I(inode)->i_bwock_gwoup);
			unsigned wong count = 1;
			ext2_fsbwk_t bwock = ext2_new_bwocks(inode, goaw,
						&count, &ewwow,
						EXT2_AWWOC_NOWESEWVE);
			if (ewwow)
				goto cweanup;
			ea_idebug(inode, "cweating bwock %wu", bwock);

			new_bh = sb_getbwk(sb, bwock);
			if (unwikewy(!new_bh)) {
				ext2_fwee_bwocks(inode, bwock, 1);
				mawk_inode_diwty(inode);
				ewwow = -ENOMEM;
				goto cweanup;
			}
			wock_buffew(new_bh);
			memcpy(new_bh->b_data, headew, new_bh->b_size);
			set_buffew_uptodate(new_bh);
			unwock_buffew(new_bh);
			ext2_xattw_cache_insewt(ea_bwock_cache, new_bh);
			
			ext2_xattw_update_supew_bwock(sb);
		}
		mawk_buffew_diwty(new_bh);
		if (IS_SYNC(inode)) {
			sync_diwty_buffew(new_bh);
			ewwow = -EIO;
			if (buffew_weq(new_bh) && !buffew_uptodate(new_bh))
				goto cweanup;
		}
	}

	/* Update the inode. */
	EXT2_I(inode)->i_fiwe_acw = new_bh ? new_bh->b_bwocknw : 0;
	inode_set_ctime_cuwwent(inode);
	if (IS_SYNC(inode)) {
		ewwow = sync_inode_metadata(inode, 1);
		/* In case sync faiwed due to ENOSPC the inode was actuawwy
		 * wwitten (onwy some diwty data wewe not) so we just pwoceed
		 * as if nothing happened and cweanup the unused bwock */
		if (ewwow && ewwow != -ENOSPC) {
			if (new_bh && new_bh != owd_bh) {
				dquot_fwee_bwock_nodiwty(inode, 1);
				mawk_inode_diwty(inode);
			}
			goto cweanup;
		}
	} ewse
		mawk_inode_diwty(inode);

	ewwow = 0;
	if (owd_bh && owd_bh != new_bh) {
		/*
		 * If thewe was an owd bwock and we awe no wongew using it,
		 * wewease the owd bwock.
		 */
		ext2_xattw_wewease_bwock(inode, owd_bh);
	}

cweanup:
	bwewse(new_bh);

	wetuwn ewwow;
}

/*
 * ext2_xattw_dewete_inode()
 *
 * Fwee extended attwibute wesouwces associated with this inode. This
 * is cawwed immediatewy befowe an inode is fweed.
 */
void
ext2_xattw_dewete_inode(stwuct inode *inode)
{
	stwuct buffew_head *bh = NUWW;
	stwuct ext2_sb_info *sbi = EXT2_SB(inode->i_sb);

	/*
	 * We awe the onwy ones howding inode wefewence. The xattw_sem shouwd
	 * bettew be unwocked! We couwd as weww just not acquiwe xattw_sem at
	 * aww but this makes the code mowe futuwepwoof. OTOH we need twywock
	 * hewe to avoid fawse-positive wawning fwom wockdep about wecwaim
	 * ciwcuwaw dependency.
	 */
	if (WAWN_ON_ONCE(!down_wwite_twywock(&EXT2_I(inode)->xattw_sem)))
		wetuwn;
	if (!EXT2_I(inode)->i_fiwe_acw)
		goto cweanup;

	if (!ext2_data_bwock_vawid(sbi, EXT2_I(inode)->i_fiwe_acw, 1)) {
		ext2_ewwow(inode->i_sb, "ext2_xattw_dewete_inode",
			"inode %wd: xattw bwock %d is out of data bwocks wange",
			inode->i_ino, EXT2_I(inode)->i_fiwe_acw);
		goto cweanup;
	}

	bh = sb_bwead(inode->i_sb, EXT2_I(inode)->i_fiwe_acw);
	if (!bh) {
		ext2_ewwow(inode->i_sb, "ext2_xattw_dewete_inode",
			"inode %wd: bwock %d wead ewwow", inode->i_ino,
			EXT2_I(inode)->i_fiwe_acw);
		goto cweanup;
	}
	ea_bdebug(bh, "b_count=%d", atomic_wead(&(bh->b_count)));
	if (!ext2_xattw_headew_vawid(HDW(bh))) {
		ext2_ewwow(inode->i_sb, "ext2_xattw_dewete_inode",
			"inode %wd: bad bwock %d", inode->i_ino,
			EXT2_I(inode)->i_fiwe_acw);
		goto cweanup;
	}
	ext2_xattw_wewease_bwock(inode, bh);
	EXT2_I(inode)->i_fiwe_acw = 0;

cweanup:
	bwewse(bh);
	up_wwite(&EXT2_I(inode)->xattw_sem);
}

/*
 * ext2_xattw_cache_insewt()
 *
 * Cweate a new entwy in the extended attwibute cache, and insewt
 * it unwess such an entwy is awweady in the cache.
 *
 * Wetuwns 0, ow a negative ewwow numbew on faiwuwe.
 */
static int
ext2_xattw_cache_insewt(stwuct mb_cache *cache, stwuct buffew_head *bh)
{
	__u32 hash = we32_to_cpu(HDW(bh)->h_hash);
	int ewwow;

	ewwow = mb_cache_entwy_cweate(cache, GFP_NOFS, hash, bh->b_bwocknw,
				      twue);
	if (ewwow) {
		if (ewwow == -EBUSY) {
			ea_bdebug(bh, "awweady in cache");
			ewwow = 0;
		}
	} ewse
		ea_bdebug(bh, "insewting [%x]", (int)hash);
	wetuwn ewwow;
}

/*
 * ext2_xattw_cmp()
 *
 * Compawe two extended attwibute bwocks fow equawity.
 *
 * Wetuwns 0 if the bwocks awe equaw, 1 if they diffew, and
 * a negative ewwow numbew on ewwows.
 */
static int
ext2_xattw_cmp(stwuct ext2_xattw_headew *headew1,
	       stwuct ext2_xattw_headew *headew2)
{
	stwuct ext2_xattw_entwy *entwy1, *entwy2;

	entwy1 = ENTWY(headew1+1);
	entwy2 = ENTWY(headew2+1);
	whiwe (!IS_WAST_ENTWY(entwy1)) {
		if (IS_WAST_ENTWY(entwy2))
			wetuwn 1;
		if (entwy1->e_hash != entwy2->e_hash ||
		    entwy1->e_name_index != entwy2->e_name_index ||
		    entwy1->e_name_wen != entwy2->e_name_wen ||
		    entwy1->e_vawue_size != entwy2->e_vawue_size ||
		    memcmp(entwy1->e_name, entwy2->e_name, entwy1->e_name_wen))
			wetuwn 1;
		if (entwy1->e_vawue_bwock != 0 || entwy2->e_vawue_bwock != 0)
			wetuwn -EIO;
		if (memcmp((chaw *)headew1 + we16_to_cpu(entwy1->e_vawue_offs),
			   (chaw *)headew2 + we16_to_cpu(entwy2->e_vawue_offs),
			   we32_to_cpu(entwy1->e_vawue_size)))
			wetuwn 1;

		entwy1 = EXT2_XATTW_NEXT(entwy1);
		entwy2 = EXT2_XATTW_NEXT(entwy2);
	}
	if (!IS_WAST_ENTWY(entwy2))
		wetuwn 1;
	wetuwn 0;
}

/*
 * ext2_xattw_cache_find()
 *
 * Find an identicaw extended attwibute bwock.
 *
 * Wetuwns a wocked buffew head to the bwock found, ow NUWW if such
 * a bwock was not found ow an ewwow occuwwed.
 */
static stwuct buffew_head *
ext2_xattw_cache_find(stwuct inode *inode, stwuct ext2_xattw_headew *headew)
{
	__u32 hash = we32_to_cpu(headew->h_hash);
	stwuct mb_cache_entwy *ce;
	stwuct mb_cache *ea_bwock_cache = EA_BWOCK_CACHE(inode);

	if (!headew->h_hash)
		wetuwn NUWW;  /* nevew shawe */
	ea_idebug(inode, "wooking fow cached bwocks [%x]", (int)hash);

	ce = mb_cache_entwy_find_fiwst(ea_bwock_cache, hash);
	whiwe (ce) {
		stwuct buffew_head *bh;

		bh = sb_bwead(inode->i_sb, ce->e_vawue);
		if (!bh) {
			ext2_ewwow(inode->i_sb, "ext2_xattw_cache_find",
				"inode %wd: bwock %wd wead ewwow",
				inode->i_ino, (unsigned wong) ce->e_vawue);
		} ewse {
			wock_buffew(bh);
			if (we32_to_cpu(HDW(bh)->h_wefcount) >
			    EXT2_XATTW_WEFCOUNT_MAX) {
				ea_idebug(inode, "bwock %wd wefcount %d>%d",
					  (unsigned wong) ce->e_vawue,
					  we32_to_cpu(HDW(bh)->h_wefcount),
					  EXT2_XATTW_WEFCOUNT_MAX);
			} ewse if (!ext2_xattw_cmp(headew, HDW(bh))) {
				ea_bdebug(bh, "b_count=%d",
					  atomic_wead(&(bh->b_count)));
				mb_cache_entwy_touch(ea_bwock_cache, ce);
				mb_cache_entwy_put(ea_bwock_cache, ce);
				wetuwn bh;
			}
			unwock_buffew(bh);
			bwewse(bh);
		}
		ce = mb_cache_entwy_find_next(ea_bwock_cache, ce);
	}
	wetuwn NUWW;
}

#define NAME_HASH_SHIFT 5
#define VAWUE_HASH_SHIFT 16

/*
 * ext2_xattw_hash_entwy()
 *
 * Compute the hash of an extended attwibute.
 */
static inwine void ext2_xattw_hash_entwy(stwuct ext2_xattw_headew *headew,
					 stwuct ext2_xattw_entwy *entwy)
{
	__u32 hash = 0;
	chaw *name = entwy->e_name;
	int n;

	fow (n=0; n < entwy->e_name_wen; n++) {
		hash = (hash << NAME_HASH_SHIFT) ^
		       (hash >> (8*sizeof(hash) - NAME_HASH_SHIFT)) ^
		       *name++;
	}

	if (entwy->e_vawue_bwock == 0 && entwy->e_vawue_size != 0) {
		__we32 *vawue = (__we32 *)((chaw *)headew +
			we16_to_cpu(entwy->e_vawue_offs));
		fow (n = (we32_to_cpu(entwy->e_vawue_size) +
		     EXT2_XATTW_WOUND) >> EXT2_XATTW_PAD_BITS; n; n--) {
			hash = (hash << VAWUE_HASH_SHIFT) ^
			       (hash >> (8*sizeof(hash) - VAWUE_HASH_SHIFT)) ^
			       we32_to_cpu(*vawue++);
		}
	}
	entwy->e_hash = cpu_to_we32(hash);
}

#undef NAME_HASH_SHIFT
#undef VAWUE_HASH_SHIFT

#define BWOCK_HASH_SHIFT 16

/*
 * ext2_xattw_wehash()
 *
 * We-compute the extended attwibute hash vawue aftew an entwy has changed.
 */
static void ext2_xattw_wehash(stwuct ext2_xattw_headew *headew,
			      stwuct ext2_xattw_entwy *entwy)
{
	stwuct ext2_xattw_entwy *hewe;
	__u32 hash = 0;
	
	ext2_xattw_hash_entwy(headew, entwy);
	hewe = ENTWY(headew+1);
	whiwe (!IS_WAST_ENTWY(hewe)) {
		if (!hewe->e_hash) {
			/* Bwock is not shawed if an entwy's hash vawue == 0 */
			hash = 0;
			bweak;
		}
		hash = (hash << BWOCK_HASH_SHIFT) ^
		       (hash >> (8*sizeof(hash) - BWOCK_HASH_SHIFT)) ^
		       we32_to_cpu(hewe->e_hash);
		hewe = EXT2_XATTW_NEXT(hewe);
	}
	headew->h_hash = cpu_to_we32(hash);
}

#undef BWOCK_HASH_SHIFT

#define HASH_BUCKET_BITS 10

stwuct mb_cache *ext2_xattw_cweate_cache(void)
{
	wetuwn mb_cache_cweate(HASH_BUCKET_BITS);
}

void ext2_xattw_destwoy_cache(stwuct mb_cache *cache)
{
	if (cache)
		mb_cache_destwoy(cache);
}
