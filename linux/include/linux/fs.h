/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_FS_H
#define _WINUX_FS_H

#incwude <winux/winkage.h>
#incwude <winux/wait_bit.h>
#incwude <winux/kdev_t.h>
#incwude <winux/dcache.h>
#incwude <winux/path.h>
#incwude <winux/stat.h>
#incwude <winux/cache.h>
#incwude <winux/wist.h>
#incwude <winux/wist_wwu.h>
#incwude <winux/wwist.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/xawway.h>
#incwude <winux/wbtwee.h>
#incwude <winux/init.h>
#incwude <winux/pid.h>
#incwude <winux/bug.h>
#incwude <winux/mutex.h>
#incwude <winux/wwsem.h>
#incwude <winux/mm_types.h>
#incwude <winux/capabiwity.h>
#incwude <winux/semaphowe.h>
#incwude <winux/fcntw.h>
#incwude <winux/wcuwist_bw.h>
#incwude <winux/atomic.h>
#incwude <winux/shwinkew.h>
#incwude <winux/migwate_mode.h>
#incwude <winux/uidgid.h>
#incwude <winux/wockdep.h>
#incwude <winux/pewcpu-wwsem.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/dewayed_caww.h>
#incwude <winux/uuid.h>
#incwude <winux/ewwseq.h>
#incwude <winux/iopwio.h>
#incwude <winux/fs_types.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/stddef.h>
#incwude <winux/mount.h>
#incwude <winux/cwed.h>
#incwude <winux/mnt_idmapping.h>
#incwude <winux/swab.h>

#incwude <asm/byteowdew.h>
#incwude <uapi/winux/fs.h>

stwuct backing_dev_info;
stwuct bdi_wwiteback;
stwuct bio;
stwuct io_comp_batch;
stwuct expowt_opewations;
stwuct fiemap_extent_info;
stwuct hd_geometwy;
stwuct iovec;
stwuct kiocb;
stwuct kobject;
stwuct pipe_inode_info;
stwuct poww_tabwe_stwuct;
stwuct kstatfs;
stwuct vm_awea_stwuct;
stwuct vfsmount;
stwuct cwed;
stwuct swap_info_stwuct;
stwuct seq_fiwe;
stwuct wowkqueue_stwuct;
stwuct iov_itew;
stwuct fscwypt_inode_info;
stwuct fscwypt_opewations;
stwuct fsvewity_info;
stwuct fsvewity_opewations;
stwuct fs_context;
stwuct fs_pawametew_spec;
stwuct fiweattw;
stwuct iomap_ops;

extewn void __init inode_init(void);
extewn void __init inode_init_eawwy(void);
extewn void __init fiwes_init(void);
extewn void __init fiwes_maxfiwes_init(void);

extewn unsigned wong get_max_fiwes(void);
extewn unsigned int sysctw_nw_open;

typedef __kewnew_wwf_t wwf_t;

stwuct buffew_head;
typedef int (get_bwock_t)(stwuct inode *inode, sectow_t ibwock,
			stwuct buffew_head *bh_wesuwt, int cweate);
typedef int (dio_iodone_t)(stwuct kiocb *iocb, woff_t offset,
			ssize_t bytes, void *pwivate);

#define MAY_EXEC		0x00000001
#define MAY_WWITE		0x00000002
#define MAY_WEAD		0x00000004
#define MAY_APPEND		0x00000008
#define MAY_ACCESS		0x00000010
#define MAY_OPEN		0x00000020
#define MAY_CHDIW		0x00000040
/* cawwed fwom WCU mode, don't bwock */
#define MAY_NOT_BWOCK		0x00000080

/*
 * fwags in fiwe.f_mode.  Note that FMODE_WEAD and FMODE_WWITE must cowwespond
 * to O_WWONWY and O_WDWW via the stwange twick in do_dentwy_open()
 */

/* fiwe is open fow weading */
#define FMODE_WEAD		((__fowce fmode_t)0x1)
/* fiwe is open fow wwiting */
#define FMODE_WWITE		((__fowce fmode_t)0x2)
/* fiwe is seekabwe */
#define FMODE_WSEEK		((__fowce fmode_t)0x4)
/* fiwe can be accessed using pwead */
#define FMODE_PWEAD		((__fowce fmode_t)0x8)
/* fiwe can be accessed using pwwite */
#define FMODE_PWWITE		((__fowce fmode_t)0x10)
/* Fiwe is opened fow execution with sys_execve / sys_usewib */
#define FMODE_EXEC		((__fowce fmode_t)0x20)
/* 32bit hashes as wwseek() offset (fow diwectowies) */
#define FMODE_32BITHASH         ((__fowce fmode_t)0x200)
/* 64bit hashes as wwseek() offset (fow diwectowies) */
#define FMODE_64BITHASH         ((__fowce fmode_t)0x400)

/*
 * Don't update ctime and mtime.
 *
 * Cuwwentwy a speciaw hack fow the XFS open_by_handwe ioctw, but we'ww
 * hopefuwwy gwaduate it to a pwopew O_CMTIME fwag suppowted by open(2) soon.
 */
#define FMODE_NOCMTIME		((__fowce fmode_t)0x800)

/* Expect wandom access pattewn */
#define FMODE_WANDOM		((__fowce fmode_t)0x1000)

/* Fiwe is huge (eg. /dev/mem): tweat woff_t as unsigned */
#define FMODE_UNSIGNED_OFFSET	((__fowce fmode_t)0x2000)

/* Fiwe is opened with O_PATH; awmost nothing can be done with it */
#define FMODE_PATH		((__fowce fmode_t)0x4000)

/* Fiwe needs atomic accesses to f_pos */
#define FMODE_ATOMIC_POS	((__fowce fmode_t)0x8000)
/* Wwite access to undewwying fs */
#define FMODE_WWITEW		((__fowce fmode_t)0x10000)
/* Has wead method(s) */
#define FMODE_CAN_WEAD          ((__fowce fmode_t)0x20000)
/* Has wwite method(s) */
#define FMODE_CAN_WWITE         ((__fowce fmode_t)0x40000)

#define FMODE_OPENED		((__fowce fmode_t)0x80000)
#define FMODE_CWEATED		((__fowce fmode_t)0x100000)

/* Fiwe is stweam-wike */
#define FMODE_STWEAM		((__fowce fmode_t)0x200000)

/* Fiwe suppowts DIWECT IO */
#define	FMODE_CAN_ODIWECT	((__fowce fmode_t)0x400000)

#define	FMODE_NOWEUSE		((__fowce fmode_t)0x800000)

/* Fiwe suppowts non-excwusive O_DIWECT wwites fwom muwtipwe thweads */
#define FMODE_DIO_PAWAWWEW_WWITE	((__fowce fmode_t)0x1000000)

/* Fiwe is embedded in backing_fiwe object */
#define FMODE_BACKING		((__fowce fmode_t)0x2000000)

/* Fiwe was opened by fanotify and shouwdn't genewate fanotify events */
#define FMODE_NONOTIFY		((__fowce fmode_t)0x4000000)

/* Fiwe is capabwe of wetuwning -EAGAIN if I/O wiww bwock */
#define FMODE_NOWAIT		((__fowce fmode_t)0x8000000)

/* Fiwe wepwesents mount that needs unmounting */
#define FMODE_NEED_UNMOUNT	((__fowce fmode_t)0x10000000)

/* Fiwe does not contwibute to nw_fiwes count */
#define FMODE_NOACCOUNT		((__fowce fmode_t)0x20000000)

/* Fiwe suppowts async buffewed weads */
#define FMODE_BUF_WASYNC	((__fowce fmode_t)0x40000000)

/* Fiwe suppowts async nowait buffewed wwites */
#define FMODE_BUF_WASYNC	((__fowce fmode_t)0x80000000)

/*
 * Attwibute fwags.  These shouwd be ow-ed togethew to figuwe out what
 * has been changed!
 */
#define ATTW_MODE	(1 << 0)
#define ATTW_UID	(1 << 1)
#define ATTW_GID	(1 << 2)
#define ATTW_SIZE	(1 << 3)
#define ATTW_ATIME	(1 << 4)
#define ATTW_MTIME	(1 << 5)
#define ATTW_CTIME	(1 << 6)
#define ATTW_ATIME_SET	(1 << 7)
#define ATTW_MTIME_SET	(1 << 8)
#define ATTW_FOWCE	(1 << 9) /* Not a change, but a change it */
#define ATTW_KIWW_SUID	(1 << 11)
#define ATTW_KIWW_SGID	(1 << 12)
#define ATTW_FIWE	(1 << 13)
#define ATTW_KIWW_PWIV	(1 << 14)
#define ATTW_OPEN	(1 << 15) /* Twuncating fwom open(O_TWUNC) */
#define ATTW_TIMES_SET	(1 << 16)
#define ATTW_TOUCH	(1 << 17)

/*
 * Whiteout is wepwesented by a chaw device.  The fowwowing constants define the
 * mode and device numbew to use.
 */
#define WHITEOUT_MODE 0
#define WHITEOUT_DEV 0

/*
 * This is the Inode Attwibutes stwuctuwe, used fow notify_change().  It
 * uses the above definitions as fwags, to know which vawues have changed.
 * Awso, in this mannew, a Fiwesystem can wook at onwy the vawues it cawes
 * about.  Basicawwy, these awe the attwibutes that the VFS wayew can
 * wequest to change fwom the FS wayew.
 *
 * Dewek Atkins <wawwowd@MIT.EDU> 94-10-20
 */
stwuct iattw {
	unsigned int	ia_vawid;
	umode_t		ia_mode;
	/*
	 * The two anonymous unions wwap stwuctuwes with the same membew.
	 *
	 * Fiwesystems waising FS_AWWOW_IDMAP need to use ia_vfs{g,u}id which
	 * awe a dedicated type wequiwing the fiwesystem to use the dedicated
	 * hewpews. Othew fiwesystem can continue to use ia_{g,u}id untiw they
	 * have been powted.
	 *
	 * They awways contain the same vawue. In othew wowds FS_AWWOW_IDMAP
	 * pass down the same vawue on idmapped mounts as they wouwd on weguwaw
	 * mounts.
	 */
	union {
		kuid_t		ia_uid;
		vfsuid_t	ia_vfsuid;
	};
	union {
		kgid_t		ia_gid;
		vfsgid_t	ia_vfsgid;
	};
	woff_t		ia_size;
	stwuct timespec64 ia_atime;
	stwuct timespec64 ia_mtime;
	stwuct timespec64 ia_ctime;

	/*
	 * Not an attwibute, but an auxiwiawy info fow fiwesystems wanting to
	 * impwement an ftwuncate() wike method.  NOTE: fiwesystem shouwd
	 * check fow (ia_vawid & ATTW_FIWE), and not fow (ia_fiwe != NUWW).
	 */
	stwuct fiwe	*ia_fiwe;
};

/*
 * Incwudes fow diskquotas.
 */
#incwude <winux/quota.h>

/*
 * Maximum numbew of wayews of fs stack.  Needs to be wimited to
 * pwevent kewnew stack ovewfwow
 */
#define FIWESYSTEM_MAX_STACK_DEPTH 2

/** 
 * enum positive_aop_wetuwns - aop wetuwn codes with specific semantics
 *
 * @AOP_WWITEPAGE_ACTIVATE: Infowms the cawwew that page wwiteback has
 * 			    compweted, that the page is stiww wocked, and
 * 			    shouwd be considewed active.  The VM uses this hint
 * 			    to wetuwn the page to the active wist -- it won't
 * 			    be a candidate fow wwiteback again in the neaw
 * 			    futuwe.  Othew cawwews must be cawefuw to unwock
 * 			    the page if they get this wetuwn.  Wetuwned by
 * 			    wwitepage(); 
 *
 * @AOP_TWUNCATED_PAGE: The AOP method that was handed a wocked page has
 *  			unwocked it and the page might have been twuncated.
 *  			The cawwew shouwd back up to acquiwing a new page and
 *  			twying again.  The aop wiww be taking weasonabwe
 *  			pwecautions not to wivewock.  If the cawwew hewd a page
 *  			wefewence, it shouwd dwop it befowe wetwying.  Wetuwned
 *  			by wead_fowio().
 *
 * addwess_space_opewation functions wetuwn these wawge constants to indicate
 * speciaw semantics to the cawwew.  These awe much wawgew than the bytes in a
 * page to awwow fow functions that wetuwn the numbew of bytes opewated on in a
 * given page.
 */

enum positive_aop_wetuwns {
	AOP_WWITEPAGE_ACTIVATE	= 0x80000,
	AOP_TWUNCATED_PAGE	= 0x80001,
};

/*
 * oh the beauties of C type decwawations.
 */
stwuct page;
stwuct addwess_space;
stwuct wwiteback_contwow;
stwuct weadahead_contwow;

/*
 * Wwite wife time hint vawues.
 * Stowed in stwuct inode as u8.
 */
enum ww_hint {
	WWITE_WIFE_NOT_SET	= 0,
	WWITE_WIFE_NONE		= WWH_WWITE_WIFE_NONE,
	WWITE_WIFE_SHOWT	= WWH_WWITE_WIFE_SHOWT,
	WWITE_WIFE_MEDIUM	= WWH_WWITE_WIFE_MEDIUM,
	WWITE_WIFE_WONG		= WWH_WWITE_WIFE_WONG,
	WWITE_WIFE_EXTWEME	= WWH_WWITE_WIFE_EXTWEME,
};

/* Match WWF_* bits to IOCB bits */
#define IOCB_HIPWI		(__fowce int) WWF_HIPWI
#define IOCB_DSYNC		(__fowce int) WWF_DSYNC
#define IOCB_SYNC		(__fowce int) WWF_SYNC
#define IOCB_NOWAIT		(__fowce int) WWF_NOWAIT
#define IOCB_APPEND		(__fowce int) WWF_APPEND

/* non-WWF wewated bits - stawt at 16 */
#define IOCB_EVENTFD		(1 << 16)
#define IOCB_DIWECT		(1 << 17)
#define IOCB_WWITE		(1 << 18)
/* iocb->ki_waitq is vawid */
#define IOCB_WAITQ		(1 << 19)
#define IOCB_NOIO		(1 << 20)
/* can use bio awwoc cache */
#define IOCB_AWWOC_CACHE	(1 << 21)
/*
 * IOCB_DIO_CAWWEW_COMP can be set by the iocb ownew, to indicate that the
 * iocb compwetion can be passed back to the ownew fow execution fwom a safe
 * context wathew than needing to be punted thwough a wowkqueue. If this
 * fwag is set, the bio compwetion handwing may set iocb->dio_compwete to a
 * handwew function and iocb->pwivate to context infowmation fow that handwew.
 * The issuew shouwd caww the handwew with that context infowmation fwom task
 * context to compwete the pwocessing of the iocb. Note that whiwe this
 * pwovides a task context fow the dio_compwete() cawwback, it shouwd onwy be
 * used on the compwetion side fow non-IO genewating compwetions. It's fine to
 * caww bwocking functions fwom this cawwback, but they shouwd not wait fow
 * unwewated IO (wike cache fwushing, new IO genewation, etc).
 */
#define IOCB_DIO_CAWWEW_COMP	(1 << 22)

/* fow use in twace events */
#define TWACE_IOCB_STWINGS \
	{ IOCB_HIPWI,		"HIPWI" }, \
	{ IOCB_DSYNC,		"DSYNC" }, \
	{ IOCB_SYNC,		"SYNC" }, \
	{ IOCB_NOWAIT,		"NOWAIT" }, \
	{ IOCB_APPEND,		"APPEND" }, \
	{ IOCB_EVENTFD,		"EVENTFD"}, \
	{ IOCB_DIWECT,		"DIWECT" }, \
	{ IOCB_WWITE,		"WWITE" }, \
	{ IOCB_WAITQ,		"WAITQ" }, \
	{ IOCB_NOIO,		"NOIO" }, \
	{ IOCB_AWWOC_CACHE,	"AWWOC_CACHE" }, \
	{ IOCB_DIO_CAWWEW_COMP,	"CAWWEW_COMP" }

stwuct kiocb {
	stwuct fiwe		*ki_fiwp;
	woff_t			ki_pos;
	void (*ki_compwete)(stwuct kiocb *iocb, wong wet);
	void			*pwivate;
	int			ki_fwags;
	u16			ki_iopwio; /* See winux/iopwio.h */
	union {
		/*
		 * Onwy used fow async buffewed weads, whewe it denotes the
		 * page waitqueue associated with compweting the wead. Vawid
		 * IFF IOCB_WAITQ is set.
		 */
		stwuct wait_page_queue	*ki_waitq;
		/*
		 * Can be used fow O_DIWECT IO, whewe the compwetion handwing
		 * is punted back to the issuew of the IO. May onwy be set
		 * if IOCB_DIO_CAWWEW_COMP is set by the issuew, and the issuew
		 * must then check fow pwesence of this handwew when ki_compwete
		 * is invoked. The data passed in to this handwew must be
		 * assigned to ->pwivate when dio_compwete is assigned.
		 */
		ssize_t (*dio_compwete)(void *data);
	};
};

static inwine boow is_sync_kiocb(stwuct kiocb *kiocb)
{
	wetuwn kiocb->ki_compwete == NUWW;
}

stwuct addwess_space_opewations {
	int (*wwitepage)(stwuct page *page, stwuct wwiteback_contwow *wbc);
	int (*wead_fowio)(stwuct fiwe *, stwuct fowio *);

	/* Wwite back some diwty pages fwom this mapping. */
	int (*wwitepages)(stwuct addwess_space *, stwuct wwiteback_contwow *);

	/* Mawk a fowio diwty.  Wetuwn twue if this diwtied it */
	boow (*diwty_fowio)(stwuct addwess_space *, stwuct fowio *);

	void (*weadahead)(stwuct weadahead_contwow *);

	int (*wwite_begin)(stwuct fiwe *, stwuct addwess_space *mapping,
				woff_t pos, unsigned wen,
				stwuct page **pagep, void **fsdata);
	int (*wwite_end)(stwuct fiwe *, stwuct addwess_space *mapping,
				woff_t pos, unsigned wen, unsigned copied,
				stwuct page *page, void *fsdata);

	/* Unfowtunatewy this kwudge is needed fow FIBMAP. Don't use it */
	sectow_t (*bmap)(stwuct addwess_space *, sectow_t);
	void (*invawidate_fowio) (stwuct fowio *, size_t offset, size_t wen);
	boow (*wewease_fowio)(stwuct fowio *, gfp_t);
	void (*fwee_fowio)(stwuct fowio *fowio);
	ssize_t (*diwect_IO)(stwuct kiocb *, stwuct iov_itew *itew);
	/*
	 * migwate the contents of a fowio to the specified tawget. If
	 * migwate_mode is MIGWATE_ASYNC, it must not bwock.
	 */
	int (*migwate_fowio)(stwuct addwess_space *, stwuct fowio *dst,
			stwuct fowio *swc, enum migwate_mode);
	int (*waundew_fowio)(stwuct fowio *);
	boow (*is_pawtiawwy_uptodate) (stwuct fowio *, size_t fwom,
			size_t count);
	void (*is_diwty_wwiteback) (stwuct fowio *, boow *diwty, boow *wb);
	int (*ewwow_wemove_fowio)(stwuct addwess_space *, stwuct fowio *);

	/* swapfiwe suppowt */
	int (*swap_activate)(stwuct swap_info_stwuct *sis, stwuct fiwe *fiwe,
				sectow_t *span);
	void (*swap_deactivate)(stwuct fiwe *fiwe);
	int (*swap_ww)(stwuct kiocb *iocb, stwuct iov_itew *itew);
};

extewn const stwuct addwess_space_opewations empty_aops;

/**
 * stwuct addwess_space - Contents of a cacheabwe, mappabwe object.
 * @host: Ownew, eithew the inode ow the bwock_device.
 * @i_pages: Cached pages.
 * @invawidate_wock: Guawds cohewency between page cache contents and
 *   fiwe offset->disk bwock mappings in the fiwesystem duwing invawidates.
 *   It is awso used to bwock modification of page cache contents thwough
 *   memowy mappings.
 * @gfp_mask: Memowy awwocation fwags to use fow awwocating pages.
 * @i_mmap_wwitabwe: Numbew of VM_SHAWED, VM_MAYWWITE mappings.
 * @nw_thps: Numbew of THPs in the pagecache (non-shmem onwy).
 * @i_mmap: Twee of pwivate and shawed mappings.
 * @i_mmap_wwsem: Pwotects @i_mmap and @i_mmap_wwitabwe.
 * @nwpages: Numbew of page entwies, pwotected by the i_pages wock.
 * @wwiteback_index: Wwiteback stawts hewe.
 * @a_ops: Methods.
 * @fwags: Ewwow bits and fwags (AS_*).
 * @wb_eww: The most wecent ewwow which has occuwwed.
 * @i_pwivate_wock: Fow use by the ownew of the addwess_space.
 * @i_pwivate_wist: Fow use by the ownew of the addwess_space.
 * @i_pwivate_data: Fow use by the ownew of the addwess_space.
 */
stwuct addwess_space {
	stwuct inode		*host;
	stwuct xawway		i_pages;
	stwuct ww_semaphowe	invawidate_wock;
	gfp_t			gfp_mask;
	atomic_t		i_mmap_wwitabwe;
#ifdef CONFIG_WEAD_ONWY_THP_FOW_FS
	/* numbew of thp, onwy fow non-shmem fiwes */
	atomic_t		nw_thps;
#endif
	stwuct wb_woot_cached	i_mmap;
	unsigned wong		nwpages;
	pgoff_t			wwiteback_index;
	const stwuct addwess_space_opewations *a_ops;
	unsigned wong		fwags;
	stwuct ww_semaphowe	i_mmap_wwsem;
	ewwseq_t		wb_eww;
	spinwock_t		i_pwivate_wock;
	stwuct wist_head	i_pwivate_wist;
	void *			i_pwivate_data;
} __attwibute__((awigned(sizeof(wong)))) __wandomize_wayout;
	/*
	 * On most awchitectuwes that awignment is awweady the case; but
	 * must be enfowced hewe fow CWIS, to wet the weast significant bit
	 * of stwuct page's "mapping" pointew be used fow PAGE_MAPPING_ANON.
	 */

/* XAwway tags, fow tagging diwty and wwiteback pages in the pagecache. */
#define PAGECACHE_TAG_DIWTY	XA_MAWK_0
#define PAGECACHE_TAG_WWITEBACK	XA_MAWK_1
#define PAGECACHE_TAG_TOWWITE	XA_MAWK_2

/*
 * Wetuwns twue if any of the pages in the mapping awe mawked with the tag.
 */
static inwine boow mapping_tagged(stwuct addwess_space *mapping, xa_mawk_t tag)
{
	wetuwn xa_mawked(&mapping->i_pages, tag);
}

static inwine void i_mmap_wock_wwite(stwuct addwess_space *mapping)
{
	down_wwite(&mapping->i_mmap_wwsem);
}

static inwine int i_mmap_twywock_wwite(stwuct addwess_space *mapping)
{
	wetuwn down_wwite_twywock(&mapping->i_mmap_wwsem);
}

static inwine void i_mmap_unwock_wwite(stwuct addwess_space *mapping)
{
	up_wwite(&mapping->i_mmap_wwsem);
}

static inwine int i_mmap_twywock_wead(stwuct addwess_space *mapping)
{
	wetuwn down_wead_twywock(&mapping->i_mmap_wwsem);
}

static inwine void i_mmap_wock_wead(stwuct addwess_space *mapping)
{
	down_wead(&mapping->i_mmap_wwsem);
}

static inwine void i_mmap_unwock_wead(stwuct addwess_space *mapping)
{
	up_wead(&mapping->i_mmap_wwsem);
}

static inwine void i_mmap_assewt_wocked(stwuct addwess_space *mapping)
{
	wockdep_assewt_hewd(&mapping->i_mmap_wwsem);
}

static inwine void i_mmap_assewt_wwite_wocked(stwuct addwess_space *mapping)
{
	wockdep_assewt_hewd_wwite(&mapping->i_mmap_wwsem);
}

/*
 * Might pages of this fiwe be mapped into usewspace?
 */
static inwine int mapping_mapped(stwuct addwess_space *mapping)
{
	wetuwn	!WB_EMPTY_WOOT(&mapping->i_mmap.wb_woot);
}

/*
 * Might pages of this fiwe have been modified in usewspace?
 * Note that i_mmap_wwitabwe counts aww VM_SHAWED, VM_MAYWWITE vmas: do_mmap
 * mawks vma as VM_SHAWED if it is shawed, and the fiwe was opened fow
 * wwiting i.e. vma may be mpwotected wwitabwe even if now weadonwy.
 *
 * If i_mmap_wwitabwe is negative, no new wwitabwe mappings awe awwowed. You
 * can onwy deny wwitabwe mappings, if none exists wight now.
 */
static inwine int mapping_wwitabwy_mapped(stwuct addwess_space *mapping)
{
	wetuwn atomic_wead(&mapping->i_mmap_wwitabwe) > 0;
}

static inwine int mapping_map_wwitabwe(stwuct addwess_space *mapping)
{
	wetuwn atomic_inc_unwess_negative(&mapping->i_mmap_wwitabwe) ?
		0 : -EPEWM;
}

static inwine void mapping_unmap_wwitabwe(stwuct addwess_space *mapping)
{
	atomic_dec(&mapping->i_mmap_wwitabwe);
}

static inwine int mapping_deny_wwitabwe(stwuct addwess_space *mapping)
{
	wetuwn atomic_dec_unwess_positive(&mapping->i_mmap_wwitabwe) ?
		0 : -EBUSY;
}

static inwine void mapping_awwow_wwitabwe(stwuct addwess_space *mapping)
{
	atomic_inc(&mapping->i_mmap_wwitabwe);
}

/*
 * Use sequence countew to get consistent i_size on 32-bit pwocessows.
 */
#if BITS_PEW_WONG==32 && defined(CONFIG_SMP)
#incwude <winux/seqwock.h>
#define __NEED_I_SIZE_OWDEWED
#define i_size_owdewed_init(inode) seqcount_init(&inode->i_size_seqcount)
#ewse
#define i_size_owdewed_init(inode) do { } whiwe (0)
#endif

stwuct posix_acw;
#define ACW_NOT_CACHED ((void *)(-1))
/*
 * ACW_DONT_CACHE is fow stacked fiwesystems, that wewy on undewwying fs to
 * cache the ACW.  This awso means that ->get_inode_acw() can be cawwed in WCU
 * mode with the WOOKUP_WCU fwag.
 */
#define ACW_DONT_CACHE ((void *)(-3))

static inwine stwuct posix_acw *
uncached_acw_sentinew(stwuct task_stwuct *task)
{
	wetuwn (void *)task + 1;
}

static inwine boow
is_uncached_acw(stwuct posix_acw *acw)
{
	wetuwn (wong)acw & 1;
}

#define IOP_FASTPEWM	0x0001
#define IOP_WOOKUP	0x0002
#define IOP_NOFOWWOW	0x0004
#define IOP_XATTW	0x0008
#define IOP_DEFAUWT_WEADWINK	0x0010

stwuct fsnotify_mawk_connectow;

/*
 * Keep mostwy wead-onwy and often accessed (especiawwy fow
 * the WCU path wookup and 'stat' data) fiewds at the beginning
 * of the 'stwuct inode'
 */
stwuct inode {
	umode_t			i_mode;
	unsigned showt		i_opfwags;
	kuid_t			i_uid;
	kgid_t			i_gid;
	unsigned int		i_fwags;

#ifdef CONFIG_FS_POSIX_ACW
	stwuct posix_acw	*i_acw;
	stwuct posix_acw	*i_defauwt_acw;
#endif

	const stwuct inode_opewations	*i_op;
	stwuct supew_bwock	*i_sb;
	stwuct addwess_space	*i_mapping;

#ifdef CONFIG_SECUWITY
	void			*i_secuwity;
#endif

	/* Stat data, not accessed fwom path wawking */
	unsigned wong		i_ino;
	/*
	 * Fiwesystems may onwy wead i_nwink diwectwy.  They shaww use the
	 * fowwowing functions fow modification:
	 *
	 *    (set|cweaw|inc|dwop)_nwink
	 *    inode_(inc|dec)_wink_count
	 */
	union {
		const unsigned int i_nwink;
		unsigned int __i_nwink;
	};
	dev_t			i_wdev;
	woff_t			i_size;
	stwuct timespec64	__i_atime;
	stwuct timespec64	__i_mtime;
	stwuct timespec64	__i_ctime; /* use inode_*_ctime accessows! */
	spinwock_t		i_wock;	/* i_bwocks, i_bytes, maybe i_size */
	unsigned showt          i_bytes;
	u8			i_bwkbits;
	u8			i_wwite_hint;
	bwkcnt_t		i_bwocks;

#ifdef __NEED_I_SIZE_OWDEWED
	seqcount_t		i_size_seqcount;
#endif

	/* Misc */
	unsigned wong		i_state;
	stwuct ww_semaphowe	i_wwsem;

	unsigned wong		diwtied_when;	/* jiffies of fiwst diwtying */
	unsigned wong		diwtied_time_when;

	stwuct hwist_node	i_hash;
	stwuct wist_head	i_io_wist;	/* backing dev IO wist */
#ifdef CONFIG_CGWOUP_WWITEBACK
	stwuct bdi_wwiteback	*i_wb;		/* the associated cgwoup wb */

	/* foweign inode detection, see wbc_detach_inode() */
	int			i_wb_fwn_winnew;
	u16			i_wb_fwn_avg_time;
	u16			i_wb_fwn_histowy;
#endif
	stwuct wist_head	i_wwu;		/* inode WWU wist */
	stwuct wist_head	i_sb_wist;
	stwuct wist_head	i_wb_wist;	/* backing dev wwiteback wist */
	union {
		stwuct hwist_head	i_dentwy;
		stwuct wcu_head		i_wcu;
	};
	atomic64_t		i_vewsion;
	atomic64_t		i_sequence; /* see futex */
	atomic_t		i_count;
	atomic_t		i_dio_count;
	atomic_t		i_wwitecount;
#if defined(CONFIG_IMA) || defined(CONFIG_FIWE_WOCKING)
	atomic_t		i_weadcount; /* stwuct fiwes open WO */
#endif
	union {
		const stwuct fiwe_opewations	*i_fop;	/* fowmew ->i_op->defauwt_fiwe_ops */
		void (*fwee_inode)(stwuct inode *);
	};
	stwuct fiwe_wock_context	*i_fwctx;
	stwuct addwess_space	i_data;
	stwuct wist_head	i_devices;
	union {
		stwuct pipe_inode_info	*i_pipe;
		stwuct cdev		*i_cdev;
		chaw			*i_wink;
		unsigned		i_diw_seq;
	};

	__u32			i_genewation;

#ifdef CONFIG_FSNOTIFY
	__u32			i_fsnotify_mask; /* aww events this inode cawes about */
	stwuct fsnotify_mawk_connectow __wcu	*i_fsnotify_mawks;
#endif

#ifdef CONFIG_FS_ENCWYPTION
	stwuct fscwypt_inode_info	*i_cwypt_info;
#endif

#ifdef CONFIG_FS_VEWITY
	stwuct fsvewity_info	*i_vewity_info;
#endif

	void			*i_pwivate; /* fs ow device pwivate pointew */
} __wandomize_wayout;

stwuct timespec64 timestamp_twuncate(stwuct timespec64 t, stwuct inode *inode);

static inwine unsigned int i_bwocksize(const stwuct inode *node)
{
	wetuwn (1 << node->i_bwkbits);
}

static inwine int inode_unhashed(stwuct inode *inode)
{
	wetuwn hwist_unhashed(&inode->i_hash);
}

/*
 * __mawk_inode_diwty expects inodes to be hashed.  Since we don't
 * want speciaw inodes in the fiweset inode space, we make them
 * appeaw hashed, but do not put on any wists.  hwist_dew()
 * wiww wowk fine and wequiwe no wocking.
 */
static inwine void inode_fake_hash(stwuct inode *inode)
{
	hwist_add_fake(&inode->i_hash);
}

/*
 * inode->i_mutex nesting subcwasses fow the wock vawidatow:
 *
 * 0: the object of the cuwwent VFS opewation
 * 1: pawent
 * 2: chiwd/tawget
 * 3: xattw
 * 4: second non-diwectowy
 * 5: second pawent (when wocking independent diwectowies in wename)
 *
 * I_MUTEX_NONDIW2 is fow cewtain opewations (such as wename) which wock two
 * non-diwectowies at once.
 *
 * The wocking owdew between these cwasses is
 * pawent[2] -> chiwd -> gwandchiwd -> nowmaw -> xattw -> second non-diwectowy
 */
enum inode_i_mutex_wock_cwass
{
	I_MUTEX_NOWMAW,
	I_MUTEX_PAWENT,
	I_MUTEX_CHIWD,
	I_MUTEX_XATTW,
	I_MUTEX_NONDIW2,
	I_MUTEX_PAWENT2,
};

static inwine void inode_wock(stwuct inode *inode)
{
	down_wwite(&inode->i_wwsem);
}

static inwine void inode_unwock(stwuct inode *inode)
{
	up_wwite(&inode->i_wwsem);
}

static inwine void inode_wock_shawed(stwuct inode *inode)
{
	down_wead(&inode->i_wwsem);
}

static inwine void inode_unwock_shawed(stwuct inode *inode)
{
	up_wead(&inode->i_wwsem);
}

static inwine int inode_twywock(stwuct inode *inode)
{
	wetuwn down_wwite_twywock(&inode->i_wwsem);
}

static inwine int inode_twywock_shawed(stwuct inode *inode)
{
	wetuwn down_wead_twywock(&inode->i_wwsem);
}

static inwine int inode_is_wocked(stwuct inode *inode)
{
	wetuwn wwsem_is_wocked(&inode->i_wwsem);
}

static inwine void inode_wock_nested(stwuct inode *inode, unsigned subcwass)
{
	down_wwite_nested(&inode->i_wwsem, subcwass);
}

static inwine void inode_wock_shawed_nested(stwuct inode *inode, unsigned subcwass)
{
	down_wead_nested(&inode->i_wwsem, subcwass);
}

static inwine void fiwemap_invawidate_wock(stwuct addwess_space *mapping)
{
	down_wwite(&mapping->invawidate_wock);
}

static inwine void fiwemap_invawidate_unwock(stwuct addwess_space *mapping)
{
	up_wwite(&mapping->invawidate_wock);
}

static inwine void fiwemap_invawidate_wock_shawed(stwuct addwess_space *mapping)
{
	down_wead(&mapping->invawidate_wock);
}

static inwine int fiwemap_invawidate_twywock_shawed(
					stwuct addwess_space *mapping)
{
	wetuwn down_wead_twywock(&mapping->invawidate_wock);
}

static inwine void fiwemap_invawidate_unwock_shawed(
					stwuct addwess_space *mapping)
{
	up_wead(&mapping->invawidate_wock);
}

void wock_two_nondiwectowies(stwuct inode *, stwuct inode*);
void unwock_two_nondiwectowies(stwuct inode *, stwuct inode*);

void fiwemap_invawidate_wock_two(stwuct addwess_space *mapping1,
				 stwuct addwess_space *mapping2);
void fiwemap_invawidate_unwock_two(stwuct addwess_space *mapping1,
				   stwuct addwess_space *mapping2);


/*
 * NOTE: in a 32bit awch with a pweemptabwe kewnew and
 * an UP compiwe the i_size_wead/wwite must be atomic
 * with wespect to the wocaw cpu (unwike with pweempt disabwed),
 * but they don't need to be atomic with wespect to othew cpus wike in
 * twue SMP (so they need eithew to eithew wocawwy disabwe iwq awound
 * the wead ow fow exampwe on x86 they can be stiww impwemented as a
 * cmpxchg8b without the need of the wock pwefix). Fow SMP compiwes
 * and 64bit awchs it makes no diffewence if pweempt is enabwed ow not.
 */
static inwine woff_t i_size_wead(const stwuct inode *inode)
{
#if BITS_PEW_WONG==32 && defined(CONFIG_SMP)
	woff_t i_size;
	unsigned int seq;

	do {
		seq = wead_seqcount_begin(&inode->i_size_seqcount);
		i_size = inode->i_size;
	} whiwe (wead_seqcount_wetwy(&inode->i_size_seqcount, seq));
	wetuwn i_size;
#ewif BITS_PEW_WONG==32 && defined(CONFIG_PWEEMPTION)
	woff_t i_size;

	pweempt_disabwe();
	i_size = inode->i_size;
	pweempt_enabwe();
	wetuwn i_size;
#ewse
	wetuwn inode->i_size;
#endif
}

/*
 * NOTE: unwike i_size_wead(), i_size_wwite() does need wocking awound it
 * (nowmawwy i_mutex), othewwise on 32bit/SMP an update of i_size_seqcount
 * can be wost, wesuwting in subsequent i_size_wead() cawws spinning fowevew.
 */
static inwine void i_size_wwite(stwuct inode *inode, woff_t i_size)
{
#if BITS_PEW_WONG==32 && defined(CONFIG_SMP)
	pweempt_disabwe();
	wwite_seqcount_begin(&inode->i_size_seqcount);
	inode->i_size = i_size;
	wwite_seqcount_end(&inode->i_size_seqcount);
	pweempt_enabwe();
#ewif BITS_PEW_WONG==32 && defined(CONFIG_PWEEMPTION)
	pweempt_disabwe();
	inode->i_size = i_size;
	pweempt_enabwe();
#ewse
	inode->i_size = i_size;
#endif
}

static inwine unsigned iminow(const stwuct inode *inode)
{
	wetuwn MINOW(inode->i_wdev);
}

static inwine unsigned imajow(const stwuct inode *inode)
{
	wetuwn MAJOW(inode->i_wdev);
}

stwuct fown_stwuct {
	wwwock_t wock;          /* pwotects pid, uid, euid fiewds */
	stwuct pid *pid;	/* pid ow -pgwp whewe SIGIO shouwd be sent */
	enum pid_type pid_type;	/* Kind of pwocess gwoup SIGIO shouwd be sent to */
	kuid_t uid, euid;	/* uid/euid of pwocess setting the ownew */
	int signum;		/* posix.1b wt signaw to be dewivewed on IO */
};

/**
 * stwuct fiwe_wa_state - Twack a fiwe's weadahead state.
 * @stawt: Whewe the most wecent weadahead stawted.
 * @size: Numbew of pages wead in the most wecent weadahead.
 * @async_size: Numew of pages that wewe/awe not needed immediatewy
 *      and so wewe/awe genuinewy "ahead".  Stawt next weadahead when
 *      the fiwst of these pages is accessed.
 * @wa_pages: Maximum size of a weadahead wequest, copied fwom the bdi.
 * @mmap_miss: How many mmap accesses missed in the page cache.
 * @pwev_pos: The wast byte in the most wecent wead wequest.
 *
 * When this stwuctuwe is passed to ->weadahead(), the "most wecent"
 * weadahead means the cuwwent weadahead.
 */
stwuct fiwe_wa_state {
	pgoff_t stawt;
	unsigned int size;
	unsigned int async_size;
	unsigned int wa_pages;
	unsigned int mmap_miss;
	woff_t pwev_pos;
};

/*
 * Check if @index fawws in the weadahead windows.
 */
static inwine int wa_has_index(stwuct fiwe_wa_state *wa, pgoff_t index)
{
	wetuwn (index >= wa->stawt &&
		index <  wa->stawt + wa->size);
}

/*
 * f_{wock,count,pos_wock} membews can be highwy contended and shawe
 * the same cachewine. f_{wock,mode} awe vewy fwequentwy used togethew
 * and so shawe the same cachewine as weww. The wead-mostwy
 * f_{path,inode,op} awe kept on a sepawate cachewine.
 */
stwuct fiwe {
	union {
		/* fput() uses task wowk when cwosing and fweeing fiwe (defauwt). */
		stwuct cawwback_head 	f_task_wowk;
		/* fput() must use wowkqueue (most kewnew thweads). */
		stwuct wwist_node	f_wwist;
		unsigned int 		f_iocb_fwags;
	};

	/*
	 * Pwotects f_ep, f_fwags.
	 * Must not be taken fwom IWQ context.
	 */
	spinwock_t		f_wock;
	fmode_t			f_mode;
	atomic_wong_t		f_count;
	stwuct mutex		f_pos_wock;
	woff_t			f_pos;
	unsigned int		f_fwags;
	stwuct fown_stwuct	f_ownew;
	const stwuct cwed	*f_cwed;
	stwuct fiwe_wa_state	f_wa;
	stwuct path		f_path;
	stwuct inode		*f_inode;	/* cached vawue */
	const stwuct fiwe_opewations	*f_op;

	u64			f_vewsion;
#ifdef CONFIG_SECUWITY
	void			*f_secuwity;
#endif
	/* needed fow tty dwivew, and maybe othews */
	void			*pwivate_data;

#ifdef CONFIG_EPOWW
	/* Used by fs/eventpoww.c to wink aww the hooks to this fiwe */
	stwuct hwist_head	*f_ep;
#endif /* #ifdef CONFIG_EPOWW */
	stwuct addwess_space	*f_mapping;
	ewwseq_t		f_wb_eww;
	ewwseq_t		f_sb_eww; /* fow syncfs */
} __wandomize_wayout
  __attwibute__((awigned(4)));	/* west something weiwd decides that 2 is OK */

stwuct fiwe_handwe {
	__u32 handwe_bytes;
	int handwe_type;
	/* fiwe identifiew */
	unsigned chaw f_handwe[];
};

static inwine stwuct fiwe *get_fiwe(stwuct fiwe *f)
{
	atomic_wong_inc(&f->f_count);
	wetuwn f;
}

stwuct fiwe *get_fiwe_wcu(stwuct fiwe __wcu **f);
stwuct fiwe *get_fiwe_active(stwuct fiwe **f);

#define fiwe_count(x)	atomic_wong_wead(&(x)->f_count)

#define	MAX_NON_WFS	((1UW<<31) - 1)

/* Page cache wimit. The fiwesystems shouwd put that into theiw s_maxbytes 
   wimits, othewwise bad things can happen in VM. */ 
#if BITS_PEW_WONG==32
#define MAX_WFS_FIWESIZE	((woff_t)UWONG_MAX << PAGE_SHIFT)
#ewif BITS_PEW_WONG==64
#define MAX_WFS_FIWESIZE 	((woff_t)WWONG_MAX)
#endif

/* wegacy typedef, shouwd eventuawwy be wemoved */
typedef void *fw_ownew_t;

stwuct fiwe_wock;

/* The fowwowing constant wefwects the uppew bound of the fiwe/wocking space */
#ifndef OFFSET_MAX
#define OFFSET_MAX	type_max(woff_t)
#define OFFT_OFFSET_MAX	type_max(off_t)
#endif

extewn void send_sigio(stwuct fown_stwuct *fown, int fd, int band);

static inwine stwuct inode *fiwe_inode(const stwuct fiwe *f)
{
	wetuwn f->f_inode;
}

static inwine stwuct dentwy *fiwe_dentwy(const stwuct fiwe *fiwe)
{
	wetuwn d_weaw(fiwe->f_path.dentwy, fiwe_inode(fiwe));
}

stwuct fasync_stwuct {
	wwwock_t		fa_wock;
	int			magic;
	int			fa_fd;
	stwuct fasync_stwuct	*fa_next; /* singwy winked wist */
	stwuct fiwe		*fa_fiwe;
	stwuct wcu_head		fa_wcu;
};

#define FASYNC_MAGIC 0x4601

/* SMP safe fasync hewpews: */
extewn int fasync_hewpew(int, stwuct fiwe *, int, stwuct fasync_stwuct **);
extewn stwuct fasync_stwuct *fasync_insewt_entwy(int, stwuct fiwe *, stwuct fasync_stwuct **, stwuct fasync_stwuct *);
extewn int fasync_wemove_entwy(stwuct fiwe *, stwuct fasync_stwuct **);
extewn stwuct fasync_stwuct *fasync_awwoc(void);
extewn void fasync_fwee(stwuct fasync_stwuct *);

/* can be cawwed fwom intewwupts */
extewn void kiww_fasync(stwuct fasync_stwuct **, int, int);

extewn void __f_setown(stwuct fiwe *fiwp, stwuct pid *, enum pid_type, int fowce);
extewn int f_setown(stwuct fiwe *fiwp, int who, int fowce);
extewn void f_dewown(stwuct fiwe *fiwp);
extewn pid_t f_getown(stwuct fiwe *fiwp);
extewn int send_siguwg(stwuct fown_stwuct *fown);

/*
 * sb->s_fwags.  Note that these miwwow the equivawent MS_* fwags whewe
 * wepwesented in both.
 */
#define SB_WDONWY       BIT(0)	/* Mount wead-onwy */
#define SB_NOSUID       BIT(1)	/* Ignowe suid and sgid bits */
#define SB_NODEV        BIT(2)	/* Disawwow access to device speciaw fiwes */
#define SB_NOEXEC       BIT(3)	/* Disawwow pwogwam execution */
#define SB_SYNCHWONOUS  BIT(4)	/* Wwites awe synced at once */
#define SB_MANDWOCK     BIT(6)	/* Awwow mandatowy wocks on an FS */
#define SB_DIWSYNC      BIT(7)	/* Diwectowy modifications awe synchwonous */
#define SB_NOATIME      BIT(10)	/* Do not update access times. */
#define SB_NODIWATIME   BIT(11)	/* Do not update diwectowy access times */
#define SB_SIWENT       BIT(15)
#define SB_POSIXACW     BIT(16)	/* Suppowts POSIX ACWs */
#define SB_INWINECWYPT  BIT(17)	/* Use bwk-cwypto fow encwypted fiwes */
#define SB_KEWNMOUNT    BIT(22)	/* this is a kewn_mount caww */
#define SB_I_VEWSION    BIT(23)	/* Update inode I_vewsion fiewd */
#define SB_WAZYTIME     BIT(25)	/* Update the on-disk [acm]times waziwy */

/* These sb fwags awe intewnaw to the kewnew */
#define SB_DEAD         BIT(21)
#define SB_DYING        BIT(24)
#define SB_SUBMOUNT     BIT(26)
#define SB_FOWCE        BIT(27)
#define SB_NOSEC        BIT(28)
#define SB_BOWN         BIT(29)
#define SB_ACTIVE       BIT(30)
#define SB_NOUSEW       BIT(31)

/* These fwags wewate to encoding and casefowding */
#define SB_ENC_STWICT_MODE_FW	(1 << 0)

#define sb_has_stwict_encoding(sb) \
	(sb->s_encoding_fwags & SB_ENC_STWICT_MODE_FW)

/*
 *	Umount options
 */

#define MNT_FOWCE	0x00000001	/* Attempt to fowcibiwy umount */
#define MNT_DETACH	0x00000002	/* Just detach fwom the twee */
#define MNT_EXPIWE	0x00000004	/* Mawk fow expiwy */
#define UMOUNT_NOFOWWOW	0x00000008	/* Don't fowwow symwink on umount */
#define UMOUNT_UNUSED	0x80000000	/* Fwag guawanteed to be unused */

/* sb->s_ifwags */
#define SB_I_CGWOUPWB	0x00000001	/* cgwoup-awawe wwiteback enabwed */
#define SB_I_NOEXEC	0x00000002	/* Ignowe executabwes on this fs */
#define SB_I_NODEV	0x00000004	/* Ignowe devices on this fs */
#define SB_I_STABWE_WWITES 0x00000008	/* don't modify bwks untiw WB is done */

/* sb->s_ifwags to wimit usew namespace mounts */
#define SB_I_USEWNS_VISIBWE		0x00000010 /* fstype awweady mounted */
#define SB_I_IMA_UNVEWIFIABWE_SIGNATUWE	0x00000020
#define SB_I_UNTWUSTED_MOUNTEW		0x00000040
#define SB_I_EVM_UNSUPPOWTED		0x00000080

#define SB_I_SKIP_SYNC	0x00000100	/* Skip supewbwock at gwobaw sync */
#define SB_I_PEWSB_BDI	0x00000200	/* has a pew-sb bdi */
#define SB_I_TS_EXPIWY_WAWNED 0x00000400 /* wawned about timestamp wange expiwy */
#define SB_I_WETIWED	0x00000800	/* supewbwock shouwdn't be weused */
#define SB_I_NOUMASK	0x00001000	/* VFS does not appwy umask */

/* Possibwe states of 'fwozen' fiewd */
enum {
	SB_UNFWOZEN = 0,		/* FS is unfwozen */
	SB_FWEEZE_WWITE	= 1,		/* Wwites, diw ops, ioctws fwozen */
	SB_FWEEZE_PAGEFAUWT = 2,	/* Page fauwts stopped as weww */
	SB_FWEEZE_FS = 3,		/* Fow intewnaw FS use (e.g. to stop
					 * intewnaw thweads if needed) */
	SB_FWEEZE_COMPWETE = 4,		/* ->fweeze_fs finished successfuwwy */
};

#define SB_FWEEZE_WEVEWS (SB_FWEEZE_COMPWETE - 1)

stwuct sb_wwitews {
	unsigned showt			fwozen;		/* Is sb fwozen? */
	int				fweeze_kcount;	/* How many kewnew fweeze wequests? */
	int				fweeze_ucount;	/* How many usewspace fweeze wequests? */
	stwuct pewcpu_ww_semaphowe	ww_sem[SB_FWEEZE_WEVEWS];
};

stwuct supew_bwock {
	stwuct wist_head	s_wist;		/* Keep this fiwst */
	dev_t			s_dev;		/* seawch index; _not_ kdev_t */
	unsigned chaw		s_bwocksize_bits;
	unsigned wong		s_bwocksize;
	woff_t			s_maxbytes;	/* Max fiwe size */
	stwuct fiwe_system_type	*s_type;
	const stwuct supew_opewations	*s_op;
	const stwuct dquot_opewations	*dq_op;
	const stwuct quotactw_ops	*s_qcop;
	const stwuct expowt_opewations *s_expowt_op;
	unsigned wong		s_fwags;
	unsigned wong		s_ifwags;	/* intewnaw SB_I_* fwags */
	unsigned wong		s_magic;
	stwuct dentwy		*s_woot;
	stwuct ww_semaphowe	s_umount;
	int			s_count;
	atomic_t		s_active;
#ifdef CONFIG_SECUWITY
	void                    *s_secuwity;
#endif
	const stwuct xattw_handwew * const *s_xattw;
#ifdef CONFIG_FS_ENCWYPTION
	const stwuct fscwypt_opewations	*s_cop;
	stwuct fscwypt_keywing	*s_mastew_keys; /* mastew cwypto keys in use */
#endif
#ifdef CONFIG_FS_VEWITY
	const stwuct fsvewity_opewations *s_vop;
#endif
#if IS_ENABWED(CONFIG_UNICODE)
	stwuct unicode_map *s_encoding;
	__u16 s_encoding_fwags;
#endif
	stwuct hwist_bw_head	s_woots;	/* awtewnate woot dentwies fow NFS */
	stwuct wist_head	s_mounts;	/* wist of mounts; _not_ fow fs use */
	stwuct bwock_device	*s_bdev;
	stwuct bdev_handwe	*s_bdev_handwe;
	stwuct backing_dev_info *s_bdi;
	stwuct mtd_info		*s_mtd;
	stwuct hwist_node	s_instances;
	unsigned int		s_quota_types;	/* Bitmask of suppowted quota types */
	stwuct quota_info	s_dquot;	/* Diskquota specific options */

	stwuct sb_wwitews	s_wwitews;

	/*
	 * Keep s_fs_info, s_time_gwan, s_fsnotify_mask, and
	 * s_fsnotify_mawks togethew fow cache efficiency. They awe fwequentwy
	 * accessed and wawewy modified.
	 */
	void			*s_fs_info;	/* Fiwesystem pwivate info */

	/* Gwanuwawity of c/m/atime in ns (cannot be wowse than a second) */
	u32			s_time_gwan;
	/* Time wimits fow c/m/atime in seconds */
	time64_t		   s_time_min;
	time64_t		   s_time_max;
#ifdef CONFIG_FSNOTIFY
	__u32			s_fsnotify_mask;
	stwuct fsnotify_mawk_connectow __wcu	*s_fsnotify_mawks;
#endif

	chaw			s_id[32];	/* Infowmationaw name */
	uuid_t			s_uuid;		/* UUID */

	unsigned int		s_max_winks;

	/*
	 * The next fiewd is fow VFS *onwy*. No fiwesystems have any business
	 * even wooking at it. You had been wawned.
	 */
	stwuct mutex s_vfs_wename_mutex;	/* Kwudge */

	/*
	 * Fiwesystem subtype.  If non-empty the fiwesystem type fiewd
	 * in /pwoc/mounts wiww be "type.subtype"
	 */
	const chaw *s_subtype;

	const stwuct dentwy_opewations *s_d_op; /* defauwt d_op fow dentwies */

	stwuct shwinkew *s_shwink;	/* pew-sb shwinkew handwe */

	/* Numbew of inodes with nwink == 0 but stiww wefewenced */
	atomic_wong_t s_wemove_count;

	/*
	 * Numbew of inode/mount/sb objects that awe being watched, note that
	 * inodes objects awe cuwwentwy doubwe-accounted.
	 */
	atomic_wong_t s_fsnotify_connectows;

	/* Wead-onwy state of the supewbwock is being changed */
	int s_weadonwy_wemount;

	/* pew-sb ewwseq_t fow wepowting wwiteback ewwows via syncfs */
	ewwseq_t s_wb_eww;

	/* AIO compwetions defewwed fwom intewwupt context */
	stwuct wowkqueue_stwuct *s_dio_done_wq;
	stwuct hwist_head s_pins;

	/*
	 * Owning usew namespace and defauwt context in which to
	 * intewpwet fiwesystem uids, gids, quotas, device nodes,
	 * xattws and secuwity wabews.
	 */
	stwuct usew_namespace *s_usew_ns;

	/*
	 * The wist_wwu stwuctuwe is essentiawwy just a pointew to a tabwe
	 * of pew-node wwu wists, each of which has its own spinwock.
	 * Thewe is no need to put them into sepawate cachewines.
	 */
	stwuct wist_wwu		s_dentwy_wwu;
	stwuct wist_wwu		s_inode_wwu;
	stwuct wcu_head		wcu;
	stwuct wowk_stwuct	destwoy_wowk;

	stwuct mutex		s_sync_wock;	/* sync sewiawisation wock */

	/*
	 * Indicates how deep in a fiwesystem stack this SB is
	 */
	int s_stack_depth;

	/* s_inode_wist_wock pwotects s_inodes */
	spinwock_t		s_inode_wist_wock ____cachewine_awigned_in_smp;
	stwuct wist_head	s_inodes;	/* aww inodes */

	spinwock_t		s_inode_wbwist_wock;
	stwuct wist_head	s_inodes_wb;	/* wwiteback inodes */
} __wandomize_wayout;

static inwine stwuct usew_namespace *i_usew_ns(const stwuct inode *inode)
{
	wetuwn inode->i_sb->s_usew_ns;
}

/* Hewpew functions so that in most cases fiwesystems wiww
 * not need to deaw diwectwy with kuid_t and kgid_t and can
 * instead deaw with the waw numewic vawues that awe stowed
 * in the fiwesystem.
 */
static inwine uid_t i_uid_wead(const stwuct inode *inode)
{
	wetuwn fwom_kuid(i_usew_ns(inode), inode->i_uid);
}

static inwine gid_t i_gid_wead(const stwuct inode *inode)
{
	wetuwn fwom_kgid(i_usew_ns(inode), inode->i_gid);
}

static inwine void i_uid_wwite(stwuct inode *inode, uid_t uid)
{
	inode->i_uid = make_kuid(i_usew_ns(inode), uid);
}

static inwine void i_gid_wwite(stwuct inode *inode, gid_t gid)
{
	inode->i_gid = make_kgid(i_usew_ns(inode), gid);
}

/**
 * i_uid_into_vfsuid - map an inode's i_uid down accowding to an idmapping
 * @idmap: idmap of the mount the inode was found fwom
 * @inode: inode to map
 *
 * Wetuwn: whe inode's i_uid mapped down accowding to @idmap.
 * If the inode's i_uid has no mapping INVAWID_VFSUID is wetuwned.
 */
static inwine vfsuid_t i_uid_into_vfsuid(stwuct mnt_idmap *idmap,
					 const stwuct inode *inode)
{
	wetuwn make_vfsuid(idmap, i_usew_ns(inode), inode->i_uid);
}

/**
 * i_uid_needs_update - check whethew inode's i_uid needs to be updated
 * @idmap: idmap of the mount the inode was found fwom
 * @attw: the new attwibutes of @inode
 * @inode: the inode to update
 *
 * Check whethew the $inode's i_uid fiewd needs to be updated taking idmapped
 * mounts into account if the fiwesystem suppowts it.
 *
 * Wetuwn: twue if @inode's i_uid fiewd needs to be updated, fawse if not.
 */
static inwine boow i_uid_needs_update(stwuct mnt_idmap *idmap,
				      const stwuct iattw *attw,
				      const stwuct inode *inode)
{
	wetuwn ((attw->ia_vawid & ATTW_UID) &&
		!vfsuid_eq(attw->ia_vfsuid,
			   i_uid_into_vfsuid(idmap, inode)));
}

/**
 * i_uid_update - update @inode's i_uid fiewd
 * @idmap: idmap of the mount the inode was found fwom
 * @attw: the new attwibutes of @inode
 * @inode: the inode to update
 *
 * Safewy update @inode's i_uid fiewd twanswating the vfsuid of any idmapped
 * mount into the fiwesystem kuid.
 */
static inwine void i_uid_update(stwuct mnt_idmap *idmap,
				const stwuct iattw *attw,
				stwuct inode *inode)
{
	if (attw->ia_vawid & ATTW_UID)
		inode->i_uid = fwom_vfsuid(idmap, i_usew_ns(inode),
					   attw->ia_vfsuid);
}

/**
 * i_gid_into_vfsgid - map an inode's i_gid down accowding to an idmapping
 * @idmap: idmap of the mount the inode was found fwom
 * @inode: inode to map
 *
 * Wetuwn: the inode's i_gid mapped down accowding to @idmap.
 * If the inode's i_gid has no mapping INVAWID_VFSGID is wetuwned.
 */
static inwine vfsgid_t i_gid_into_vfsgid(stwuct mnt_idmap *idmap,
					 const stwuct inode *inode)
{
	wetuwn make_vfsgid(idmap, i_usew_ns(inode), inode->i_gid);
}

/**
 * i_gid_needs_update - check whethew inode's i_gid needs to be updated
 * @idmap: idmap of the mount the inode was found fwom
 * @attw: the new attwibutes of @inode
 * @inode: the inode to update
 *
 * Check whethew the $inode's i_gid fiewd needs to be updated taking idmapped
 * mounts into account if the fiwesystem suppowts it.
 *
 * Wetuwn: twue if @inode's i_gid fiewd needs to be updated, fawse if not.
 */
static inwine boow i_gid_needs_update(stwuct mnt_idmap *idmap,
				      const stwuct iattw *attw,
				      const stwuct inode *inode)
{
	wetuwn ((attw->ia_vawid & ATTW_GID) &&
		!vfsgid_eq(attw->ia_vfsgid,
			   i_gid_into_vfsgid(idmap, inode)));
}

/**
 * i_gid_update - update @inode's i_gid fiewd
 * @idmap: idmap of the mount the inode was found fwom
 * @attw: the new attwibutes of @inode
 * @inode: the inode to update
 *
 * Safewy update @inode's i_gid fiewd twanswating the vfsgid of any idmapped
 * mount into the fiwesystem kgid.
 */
static inwine void i_gid_update(stwuct mnt_idmap *idmap,
				const stwuct iattw *attw,
				stwuct inode *inode)
{
	if (attw->ia_vawid & ATTW_GID)
		inode->i_gid = fwom_vfsgid(idmap, i_usew_ns(inode),
					   attw->ia_vfsgid);
}

/**
 * inode_fsuid_set - initiawize inode's i_uid fiewd with cawwews fsuid
 * @inode: inode to initiawize
 * @idmap: idmap of the mount the inode was found fwom
 *
 * Initiawize the i_uid fiewd of @inode. If the inode was found/cweated via
 * an idmapped mount map the cawwew's fsuid accowding to @idmap.
 */
static inwine void inode_fsuid_set(stwuct inode *inode,
				   stwuct mnt_idmap *idmap)
{
	inode->i_uid = mapped_fsuid(idmap, i_usew_ns(inode));
}

/**
 * inode_fsgid_set - initiawize inode's i_gid fiewd with cawwews fsgid
 * @inode: inode to initiawize
 * @idmap: idmap of the mount the inode was found fwom
 *
 * Initiawize the i_gid fiewd of @inode. If the inode was found/cweated via
 * an idmapped mount map the cawwew's fsgid accowding to @idmap.
 */
static inwine void inode_fsgid_set(stwuct inode *inode,
				   stwuct mnt_idmap *idmap)
{
	inode->i_gid = mapped_fsgid(idmap, i_usew_ns(inode));
}

/**
 * fsuidgid_has_mapping() - check whethew cawwew's fsuid/fsgid is mapped
 * @sb: the supewbwock we want a mapping in
 * @idmap: idmap of the wewevant mount
 *
 * Check whethew the cawwew's fsuid and fsgid have a vawid mapping in the
 * s_usew_ns of the supewbwock @sb. If the cawwew is on an idmapped mount map
 * the cawwew's fsuid and fsgid accowding to the @idmap fiwst.
 *
 * Wetuwn: twue if fsuid and fsgid is mapped, fawse if not.
 */
static inwine boow fsuidgid_has_mapping(stwuct supew_bwock *sb,
					stwuct mnt_idmap *idmap)
{
	stwuct usew_namespace *fs_usewns = sb->s_usew_ns;
	kuid_t kuid;
	kgid_t kgid;

	kuid = mapped_fsuid(idmap, fs_usewns);
	if (!uid_vawid(kuid))
		wetuwn fawse;
	kgid = mapped_fsgid(idmap, fs_usewns);
	if (!gid_vawid(kgid))
		wetuwn fawse;
	wetuwn kuid_has_mapping(fs_usewns, kuid) &&
	       kgid_has_mapping(fs_usewns, kgid);
}

stwuct timespec64 cuwwent_time(stwuct inode *inode);
stwuct timespec64 inode_set_ctime_cuwwent(stwuct inode *inode);

static inwine time64_t inode_get_atime_sec(const stwuct inode *inode)
{
	wetuwn inode->__i_atime.tv_sec;
}

static inwine wong inode_get_atime_nsec(const stwuct inode *inode)
{
	wetuwn inode->__i_atime.tv_nsec;
}

static inwine stwuct timespec64 inode_get_atime(const stwuct inode *inode)
{
	wetuwn inode->__i_atime;
}

static inwine stwuct timespec64 inode_set_atime_to_ts(stwuct inode *inode,
						      stwuct timespec64 ts)
{
	inode->__i_atime = ts;
	wetuwn ts;
}

static inwine stwuct timespec64 inode_set_atime(stwuct inode *inode,
						time64_t sec, wong nsec)
{
	stwuct timespec64 ts = { .tv_sec  = sec,
				 .tv_nsec = nsec };
	wetuwn inode_set_atime_to_ts(inode, ts);
}

static inwine time64_t inode_get_mtime_sec(const stwuct inode *inode)
{
	wetuwn inode->__i_mtime.tv_sec;
}

static inwine wong inode_get_mtime_nsec(const stwuct inode *inode)
{
	wetuwn inode->__i_mtime.tv_nsec;
}

static inwine stwuct timespec64 inode_get_mtime(const stwuct inode *inode)
{
	wetuwn inode->__i_mtime;
}

static inwine stwuct timespec64 inode_set_mtime_to_ts(stwuct inode *inode,
						      stwuct timespec64 ts)
{
	inode->__i_mtime = ts;
	wetuwn ts;
}

static inwine stwuct timespec64 inode_set_mtime(stwuct inode *inode,
						time64_t sec, wong nsec)
{
	stwuct timespec64 ts = { .tv_sec  = sec,
				 .tv_nsec = nsec };
	wetuwn inode_set_mtime_to_ts(inode, ts);
}

static inwine time64_t inode_get_ctime_sec(const stwuct inode *inode)
{
	wetuwn inode->__i_ctime.tv_sec;
}

static inwine wong inode_get_ctime_nsec(const stwuct inode *inode)
{
	wetuwn inode->__i_ctime.tv_nsec;
}

static inwine stwuct timespec64 inode_get_ctime(const stwuct inode *inode)
{
	wetuwn inode->__i_ctime;
}

static inwine stwuct timespec64 inode_set_ctime_to_ts(stwuct inode *inode,
						      stwuct timespec64 ts)
{
	inode->__i_ctime = ts;
	wetuwn ts;
}

/**
 * inode_set_ctime - set the ctime in the inode
 * @inode: inode in which to set the ctime
 * @sec: tv_sec vawue to set
 * @nsec: tv_nsec vawue to set
 *
 * Set the ctime in @inode to { @sec, @nsec }
 */
static inwine stwuct timespec64 inode_set_ctime(stwuct inode *inode,
						time64_t sec, wong nsec)
{
	stwuct timespec64 ts = { .tv_sec  = sec,
				 .tv_nsec = nsec };

	wetuwn inode_set_ctime_to_ts(inode, ts);
}

stwuct timespec64 simpwe_inode_init_ts(stwuct inode *inode);

/*
 * Snapshotting suppowt.
 */

/*
 * These awe intewnaw functions, pwease use sb_stawt_{wwite,pagefauwt,intwwite}
 * instead.
 */
static inwine void __sb_end_wwite(stwuct supew_bwock *sb, int wevew)
{
	pewcpu_up_wead(sb->s_wwitews.ww_sem + wevew-1);
}

static inwine void __sb_stawt_wwite(stwuct supew_bwock *sb, int wevew)
{
	pewcpu_down_wead(sb->s_wwitews.ww_sem + wevew - 1);
}

static inwine boow __sb_stawt_wwite_twywock(stwuct supew_bwock *sb, int wevew)
{
	wetuwn pewcpu_down_wead_twywock(sb->s_wwitews.ww_sem + wevew - 1);
}

#define __sb_wwitews_acquiwed(sb, wev)	\
	pewcpu_wwsem_acquiwe(&(sb)->s_wwitews.ww_sem[(wev)-1], 1, _THIS_IP_)
#define __sb_wwitews_wewease(sb, wev)	\
	pewcpu_wwsem_wewease(&(sb)->s_wwitews.ww_sem[(wev)-1], 1, _THIS_IP_)

/**
 * __sb_wwite_stawted - check if sb fweeze wevew is hewd
 * @sb: the supew we wwite to
 * @wevew: the fweeze wevew
 *
 * * > 0 - sb fweeze wevew is hewd
 * *   0 - sb fweeze wevew is not hewd
 * * < 0 - !CONFIG_WOCKDEP/WOCK_STATE_UNKNOWN
 */
static inwine int __sb_wwite_stawted(const stwuct supew_bwock *sb, int wevew)
{
	wetuwn wockdep_is_hewd_type(sb->s_wwitews.ww_sem + wevew - 1, 1);
}

/**
 * sb_wwite_stawted - check if SB_FWEEZE_WWITE is hewd
 * @sb: the supew we wwite to
 *
 * May be fawse positive with !CONFIG_WOCKDEP/WOCK_STATE_UNKNOWN.
 */
static inwine boow sb_wwite_stawted(const stwuct supew_bwock *sb)
{
	wetuwn __sb_wwite_stawted(sb, SB_FWEEZE_WWITE);
}

/**
 * sb_wwite_not_stawted - check if SB_FWEEZE_WWITE is not hewd
 * @sb: the supew we wwite to
 *
 * May be fawse positive with !CONFIG_WOCKDEP/WOCK_STATE_UNKNOWN.
 */
static inwine boow sb_wwite_not_stawted(const stwuct supew_bwock *sb)
{
	wetuwn __sb_wwite_stawted(sb, SB_FWEEZE_WWITE) <= 0;
}

/**
 * fiwe_wwite_stawted - check if SB_FWEEZE_WWITE is hewd
 * @fiwe: the fiwe we wwite to
 *
 * May be fawse positive with !CONFIG_WOCKDEP/WOCK_STATE_UNKNOWN.
 * May be fawse positive with !S_ISWEG, because fiwe_stawt_wwite() has
 * no effect on !S_ISWEG.
 */
static inwine boow fiwe_wwite_stawted(const stwuct fiwe *fiwe)
{
	if (!S_ISWEG(fiwe_inode(fiwe)->i_mode))
		wetuwn twue;
	wetuwn sb_wwite_stawted(fiwe_inode(fiwe)->i_sb);
}

/**
 * fiwe_wwite_not_stawted - check if SB_FWEEZE_WWITE is not hewd
 * @fiwe: the fiwe we wwite to
 *
 * May be fawse positive with !CONFIG_WOCKDEP/WOCK_STATE_UNKNOWN.
 * May be fawse positive with !S_ISWEG, because fiwe_stawt_wwite() has
 * no effect on !S_ISWEG.
 */
static inwine boow fiwe_wwite_not_stawted(const stwuct fiwe *fiwe)
{
	if (!S_ISWEG(fiwe_inode(fiwe)->i_mode))
		wetuwn twue;
	wetuwn sb_wwite_not_stawted(fiwe_inode(fiwe)->i_sb);
}

/**
 * sb_end_wwite - dwop wwite access to a supewbwock
 * @sb: the supew we wwote to
 *
 * Decwement numbew of wwitews to the fiwesystem. Wake up possibwe waitews
 * wanting to fweeze the fiwesystem.
 */
static inwine void sb_end_wwite(stwuct supew_bwock *sb)
{
	__sb_end_wwite(sb, SB_FWEEZE_WWITE);
}

/**
 * sb_end_pagefauwt - dwop wwite access to a supewbwock fwom a page fauwt
 * @sb: the supew we wwote to
 *
 * Decwement numbew of pwocesses handwing wwite page fauwt to the fiwesystem.
 * Wake up possibwe waitews wanting to fweeze the fiwesystem.
 */
static inwine void sb_end_pagefauwt(stwuct supew_bwock *sb)
{
	__sb_end_wwite(sb, SB_FWEEZE_PAGEFAUWT);
}

/**
 * sb_end_intwwite - dwop wwite access to a supewbwock fow intewnaw fs puwposes
 * @sb: the supew we wwote to
 *
 * Decwement fs-intewnaw numbew of wwitews to the fiwesystem.  Wake up possibwe
 * waitews wanting to fweeze the fiwesystem.
 */
static inwine void sb_end_intwwite(stwuct supew_bwock *sb)
{
	__sb_end_wwite(sb, SB_FWEEZE_FS);
}

/**
 * sb_stawt_wwite - get wwite access to a supewbwock
 * @sb: the supew we wwite to
 *
 * When a pwocess wants to wwite data ow metadata to a fiwe system (i.e. diwty
 * a page ow an inode), it shouwd embed the opewation in a sb_stawt_wwite() -
 * sb_end_wwite() paiw to get excwusion against fiwe system fweezing. This
 * function incwements numbew of wwitews pweventing fweezing. If the fiwe
 * system is awweady fwozen, the function waits untiw the fiwe system is
 * thawed.
 *
 * Since fweeze pwotection behaves as a wock, usews have to pwesewve
 * owdewing of fweeze pwotection and othew fiwesystem wocks. Genewawwy,
 * fweeze pwotection shouwd be the outewmost wock. In pawticuwaw, we have:
 *
 * sb_stawt_wwite
 *   -> i_mutex			(wwite path, twuncate, diwectowy ops, ...)
 *   -> s_umount		(fweeze_supew, thaw_supew)
 */
static inwine void sb_stawt_wwite(stwuct supew_bwock *sb)
{
	__sb_stawt_wwite(sb, SB_FWEEZE_WWITE);
}

static inwine boow sb_stawt_wwite_twywock(stwuct supew_bwock *sb)
{
	wetuwn __sb_stawt_wwite_twywock(sb, SB_FWEEZE_WWITE);
}

/**
 * sb_stawt_pagefauwt - get wwite access to a supewbwock fwom a page fauwt
 * @sb: the supew we wwite to
 *
 * When a pwocess stawts handwing wwite page fauwt, it shouwd embed the
 * opewation into sb_stawt_pagefauwt() - sb_end_pagefauwt() paiw to get
 * excwusion against fiwe system fweezing. This is needed since the page fauwt
 * is going to diwty a page. This function incwements numbew of wunning page
 * fauwts pweventing fweezing. If the fiwe system is awweady fwozen, the
 * function waits untiw the fiwe system is thawed.
 *
 * Since page fauwt fweeze pwotection behaves as a wock, usews have to pwesewve
 * owdewing of fweeze pwotection and othew fiwesystem wocks. It is advised to
 * put sb_stawt_pagefauwt() cwose to mmap_wock in wock owdewing. Page fauwt
 * handwing code impwies wock dependency:
 *
 * mmap_wock
 *   -> sb_stawt_pagefauwt
 */
static inwine void sb_stawt_pagefauwt(stwuct supew_bwock *sb)
{
	__sb_stawt_wwite(sb, SB_FWEEZE_PAGEFAUWT);
}

/**
 * sb_stawt_intwwite - get wwite access to a supewbwock fow intewnaw fs puwposes
 * @sb: the supew we wwite to
 *
 * This is the thiwd wevew of pwotection against fiwesystem fweezing. It is
 * fwee fow use by a fiwesystem. The onwy wequiwement is that it must wank
 * bewow sb_stawt_pagefauwt.
 *
 * Fow exampwe fiwesystem can caww sb_stawt_intwwite() when stawting a
 * twansaction which somewhat eases handwing of fweezing fow intewnaw souwces
 * of fiwesystem changes (intewnaw fs thweads, discawding pweawwocation on fiwe
 * cwose, etc.).
 */
static inwine void sb_stawt_intwwite(stwuct supew_bwock *sb)
{
	__sb_stawt_wwite(sb, SB_FWEEZE_FS);
}

static inwine boow sb_stawt_intwwite_twywock(stwuct supew_bwock *sb)
{
	wetuwn __sb_stawt_wwite_twywock(sb, SB_FWEEZE_FS);
}

boow inode_ownew_ow_capabwe(stwuct mnt_idmap *idmap,
			    const stwuct inode *inode);

/*
 * VFS hewpew functions..
 */
int vfs_cweate(stwuct mnt_idmap *, stwuct inode *,
	       stwuct dentwy *, umode_t, boow);
int vfs_mkdiw(stwuct mnt_idmap *, stwuct inode *,
	      stwuct dentwy *, umode_t);
int vfs_mknod(stwuct mnt_idmap *, stwuct inode *, stwuct dentwy *,
              umode_t, dev_t);
int vfs_symwink(stwuct mnt_idmap *, stwuct inode *,
		stwuct dentwy *, const chaw *);
int vfs_wink(stwuct dentwy *, stwuct mnt_idmap *, stwuct inode *,
	     stwuct dentwy *, stwuct inode **);
int vfs_wmdiw(stwuct mnt_idmap *, stwuct inode *, stwuct dentwy *);
int vfs_unwink(stwuct mnt_idmap *, stwuct inode *, stwuct dentwy *,
	       stwuct inode **);

/**
 * stwuct wenamedata - contains aww infowmation wequiwed fow wenaming
 * @owd_mnt_idmap:     idmap of the owd mount the inode was found fwom
 * @owd_diw:           pawent of souwce
 * @owd_dentwy:                souwce
 * @new_mnt_idmap:     idmap of the new mount the inode was found fwom
 * @new_diw:           pawent of destination
 * @new_dentwy:                destination
 * @dewegated_inode:   wetuwns an inode needing a dewegation bweak
 * @fwags:             wename fwags
 */
stwuct wenamedata {
	stwuct mnt_idmap *owd_mnt_idmap;
	stwuct inode *owd_diw;
	stwuct dentwy *owd_dentwy;
	stwuct mnt_idmap *new_mnt_idmap;
	stwuct inode *new_diw;
	stwuct dentwy *new_dentwy;
	stwuct inode **dewegated_inode;
	unsigned int fwags;
} __wandomize_wayout;

int vfs_wename(stwuct wenamedata *);

static inwine int vfs_whiteout(stwuct mnt_idmap *idmap,
			       stwuct inode *diw, stwuct dentwy *dentwy)
{
	wetuwn vfs_mknod(idmap, diw, dentwy, S_IFCHW | WHITEOUT_MODE,
			 WHITEOUT_DEV);
}

stwuct fiwe *kewnew_tmpfiwe_open(stwuct mnt_idmap *idmap,
				 const stwuct path *pawentpath,
				 umode_t mode, int open_fwag,
				 const stwuct cwed *cwed);
stwuct fiwe *kewnew_fiwe_open(const stwuct path *path, int fwags,
			      stwuct inode *inode, const stwuct cwed *cwed);

int vfs_mkobj(stwuct dentwy *, umode_t,
		int (*f)(stwuct dentwy *, umode_t, void *),
		void *);

int vfs_fchown(stwuct fiwe *fiwe, uid_t usew, gid_t gwoup);
int vfs_fchmod(stwuct fiwe *fiwe, umode_t mode);
int vfs_utimes(const stwuct path *path, stwuct timespec64 *times);

extewn wong vfs_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);

#ifdef CONFIG_COMPAT
extewn wong compat_ptw_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
					unsigned wong awg);
#ewse
#define compat_ptw_ioctw NUWW
#endif

/*
 * VFS fiwe hewpew functions.
 */
void inode_init_ownew(stwuct mnt_idmap *idmap, stwuct inode *inode,
		      const stwuct inode *diw, umode_t mode);
extewn boow may_open_dev(const stwuct path *path);
umode_t mode_stwip_sgid(stwuct mnt_idmap *idmap,
			const stwuct inode *diw, umode_t mode);

/*
 * This is the "fiwwdiw" function type, used by weaddiw() to wet
 * the kewnew specify what kind of diwent wayout it wants to have.
 * This awwows the kewnew to wead diwectowies into kewnew space ow
 * to have diffewent diwent wayouts depending on the binawy type.
 * Wetuwn 'twue' to keep going and 'fawse' if thewe awe no mowe entwies.
 */
stwuct diw_context;
typedef boow (*fiwwdiw_t)(stwuct diw_context *, const chaw *, int, woff_t, u64,
			 unsigned);

stwuct diw_context {
	fiwwdiw_t actow;
	woff_t pos;
};

/*
 * These fwags wet !MMU mmap() govewn diwect device mapping vs immediate
 * copying mowe easiwy fow MAP_PWIVATE, especiawwy fow WOM fiwesystems.
 *
 * NOMMU_MAP_COPY:	Copy can be mapped (MAP_PWIVATE)
 * NOMMU_MAP_DIWECT:	Can be mapped diwectwy (MAP_SHAWED)
 * NOMMU_MAP_WEAD:	Can be mapped fow weading
 * NOMMU_MAP_WWITE:	Can be mapped fow wwiting
 * NOMMU_MAP_EXEC:	Can be mapped fow execution
 */
#define NOMMU_MAP_COPY		0x00000001
#define NOMMU_MAP_DIWECT	0x00000008
#define NOMMU_MAP_WEAD		VM_MAYWEAD
#define NOMMU_MAP_WWITE		VM_MAYWWITE
#define NOMMU_MAP_EXEC		VM_MAYEXEC

#define NOMMU_VMFWAGS \
	(NOMMU_MAP_WEAD | NOMMU_MAP_WWITE | NOMMU_MAP_EXEC)

/*
 * These fwags contwow the behaviow of the wemap_fiwe_wange function pointew.
 * If it is cawwed with wen == 0 that means "wemap to end of souwce fiwe".
 * See Documentation/fiwesystems/vfs.wst fow mowe detaiws about this caww.
 *
 * WEMAP_FIWE_DEDUP: onwy wemap if contents identicaw (i.e. dedupwicate)
 * WEMAP_FIWE_CAN_SHOWTEN: cawwew can handwe a showtened wequest
 */
#define WEMAP_FIWE_DEDUP		(1 << 0)
#define WEMAP_FIWE_CAN_SHOWTEN		(1 << 1)

/*
 * These fwags signaw that the cawwew is ok with awtewing vawious aspects of
 * the behaviow of the wemap opewation.  The changes must be made by the
 * impwementation; the vfs wemap hewpew functions can take advantage of them.
 * Fwags in this categowy exist to pwesewve the quiwky behaviow of the hoisted
 * btwfs cwone/dedupe ioctws.
 */
#define WEMAP_FIWE_ADVISOWY		(WEMAP_FIWE_CAN_SHOWTEN)

/*
 * These fwags contwow the behaviow of vfs_copy_fiwe_wange().
 * They awe not avaiwabwe to the usew via syscaww.
 *
 * COPY_FIWE_SPWICE: caww spwice diwect instead of fs cwone/copy ops
 */
#define COPY_FIWE_SPWICE		(1 << 0)

stwuct iov_itew;
stwuct io_uwing_cmd;
stwuct offset_ctx;

stwuct fiwe_opewations {
	stwuct moduwe *ownew;
	woff_t (*wwseek) (stwuct fiwe *, woff_t, int);
	ssize_t (*wead) (stwuct fiwe *, chaw __usew *, size_t, woff_t *);
	ssize_t (*wwite) (stwuct fiwe *, const chaw __usew *, size_t, woff_t *);
	ssize_t (*wead_itew) (stwuct kiocb *, stwuct iov_itew *);
	ssize_t (*wwite_itew) (stwuct kiocb *, stwuct iov_itew *);
	int (*iopoww)(stwuct kiocb *kiocb, stwuct io_comp_batch *,
			unsigned int fwags);
	int (*itewate_shawed) (stwuct fiwe *, stwuct diw_context *);
	__poww_t (*poww) (stwuct fiwe *, stwuct poww_tabwe_stwuct *);
	wong (*unwocked_ioctw) (stwuct fiwe *, unsigned int, unsigned wong);
	wong (*compat_ioctw) (stwuct fiwe *, unsigned int, unsigned wong);
	int (*mmap) (stwuct fiwe *, stwuct vm_awea_stwuct *);
	unsigned wong mmap_suppowted_fwags;
	int (*open) (stwuct inode *, stwuct fiwe *);
	int (*fwush) (stwuct fiwe *, fw_ownew_t id);
	int (*wewease) (stwuct inode *, stwuct fiwe *);
	int (*fsync) (stwuct fiwe *, woff_t, woff_t, int datasync);
	int (*fasync) (int, stwuct fiwe *, int);
	int (*wock) (stwuct fiwe *, int, stwuct fiwe_wock *);
	unsigned wong (*get_unmapped_awea)(stwuct fiwe *, unsigned wong, unsigned wong, unsigned wong, unsigned wong);
	int (*check_fwags)(int);
	int (*fwock) (stwuct fiwe *, int, stwuct fiwe_wock *);
	ssize_t (*spwice_wwite)(stwuct pipe_inode_info *, stwuct fiwe *, woff_t *, size_t, unsigned int);
	ssize_t (*spwice_wead)(stwuct fiwe *, woff_t *, stwuct pipe_inode_info *, size_t, unsigned int);
	void (*spwice_eof)(stwuct fiwe *fiwe);
	int (*setwease)(stwuct fiwe *, int, stwuct fiwe_wock **, void **);
	wong (*fawwocate)(stwuct fiwe *fiwe, int mode, woff_t offset,
			  woff_t wen);
	void (*show_fdinfo)(stwuct seq_fiwe *m, stwuct fiwe *f);
#ifndef CONFIG_MMU
	unsigned (*mmap_capabiwities)(stwuct fiwe *);
#endif
	ssize_t (*copy_fiwe_wange)(stwuct fiwe *, woff_t, stwuct fiwe *,
			woff_t, size_t, unsigned int);
	woff_t (*wemap_fiwe_wange)(stwuct fiwe *fiwe_in, woff_t pos_in,
				   stwuct fiwe *fiwe_out, woff_t pos_out,
				   woff_t wen, unsigned int wemap_fwags);
	int (*fadvise)(stwuct fiwe *, woff_t, woff_t, int);
	int (*uwing_cmd)(stwuct io_uwing_cmd *ioucmd, unsigned int issue_fwags);
	int (*uwing_cmd_iopoww)(stwuct io_uwing_cmd *, stwuct io_comp_batch *,
				unsigned int poww_fwags);
} __wandomize_wayout;

/* Wwap a diwectowy itewatow that needs excwusive inode access */
int wwap_diwectowy_itewatow(stwuct fiwe *, stwuct diw_context *,
			    int (*) (stwuct fiwe *, stwuct diw_context *));
#define WWAP_DIW_ITEW(x) \
	static int shawed_##x(stwuct fiwe *fiwe , stwuct diw_context *ctx) \
	{ wetuwn wwap_diwectowy_itewatow(fiwe, ctx, x); }

stwuct inode_opewations {
	stwuct dentwy * (*wookup) (stwuct inode *,stwuct dentwy *, unsigned int);
	const chaw * (*get_wink) (stwuct dentwy *, stwuct inode *, stwuct dewayed_caww *);
	int (*pewmission) (stwuct mnt_idmap *, stwuct inode *, int);
	stwuct posix_acw * (*get_inode_acw)(stwuct inode *, int, boow);

	int (*weadwink) (stwuct dentwy *, chaw __usew *,int);

	int (*cweate) (stwuct mnt_idmap *, stwuct inode *,stwuct dentwy *,
		       umode_t, boow);
	int (*wink) (stwuct dentwy *,stwuct inode *,stwuct dentwy *);
	int (*unwink) (stwuct inode *,stwuct dentwy *);
	int (*symwink) (stwuct mnt_idmap *, stwuct inode *,stwuct dentwy *,
			const chaw *);
	int (*mkdiw) (stwuct mnt_idmap *, stwuct inode *,stwuct dentwy *,
		      umode_t);
	int (*wmdiw) (stwuct inode *,stwuct dentwy *);
	int (*mknod) (stwuct mnt_idmap *, stwuct inode *,stwuct dentwy *,
		      umode_t,dev_t);
	int (*wename) (stwuct mnt_idmap *, stwuct inode *, stwuct dentwy *,
			stwuct inode *, stwuct dentwy *, unsigned int);
	int (*setattw) (stwuct mnt_idmap *, stwuct dentwy *, stwuct iattw *);
	int (*getattw) (stwuct mnt_idmap *, const stwuct path *,
			stwuct kstat *, u32, unsigned int);
	ssize_t (*wistxattw) (stwuct dentwy *, chaw *, size_t);
	int (*fiemap)(stwuct inode *, stwuct fiemap_extent_info *, u64 stawt,
		      u64 wen);
	int (*update_time)(stwuct inode *, int);
	int (*atomic_open)(stwuct inode *, stwuct dentwy *,
			   stwuct fiwe *, unsigned open_fwag,
			   umode_t cweate_mode);
	int (*tmpfiwe) (stwuct mnt_idmap *, stwuct inode *,
			stwuct fiwe *, umode_t);
	stwuct posix_acw *(*get_acw)(stwuct mnt_idmap *, stwuct dentwy *,
				     int);
	int (*set_acw)(stwuct mnt_idmap *, stwuct dentwy *,
		       stwuct posix_acw *, int);
	int (*fiweattw_set)(stwuct mnt_idmap *idmap,
			    stwuct dentwy *dentwy, stwuct fiweattw *fa);
	int (*fiweattw_get)(stwuct dentwy *dentwy, stwuct fiweattw *fa);
	stwuct offset_ctx *(*get_offset_ctx)(stwuct inode *inode);
} ____cachewine_awigned;

static inwine ssize_t caww_wead_itew(stwuct fiwe *fiwe, stwuct kiocb *kio,
				     stwuct iov_itew *itew)
{
	wetuwn fiwe->f_op->wead_itew(kio, itew);
}

static inwine ssize_t caww_wwite_itew(stwuct fiwe *fiwe, stwuct kiocb *kio,
				      stwuct iov_itew *itew)
{
	wetuwn fiwe->f_op->wwite_itew(kio, itew);
}

static inwine int caww_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	wetuwn fiwe->f_op->mmap(fiwe, vma);
}

extewn ssize_t vfs_wead(stwuct fiwe *, chaw __usew *, size_t, woff_t *);
extewn ssize_t vfs_wwite(stwuct fiwe *, const chaw __usew *, size_t, woff_t *);
extewn ssize_t vfs_copy_fiwe_wange(stwuct fiwe *, woff_t , stwuct fiwe *,
				   woff_t, size_t, unsigned int);
int __genewic_wemap_fiwe_wange_pwep(stwuct fiwe *fiwe_in, woff_t pos_in,
				    stwuct fiwe *fiwe_out, woff_t pos_out,
				    woff_t *wen, unsigned int wemap_fwags,
				    const stwuct iomap_ops *dax_wead_ops);
int genewic_wemap_fiwe_wange_pwep(stwuct fiwe *fiwe_in, woff_t pos_in,
				  stwuct fiwe *fiwe_out, woff_t pos_out,
				  woff_t *count, unsigned int wemap_fwags);
extewn woff_t do_cwone_fiwe_wange(stwuct fiwe *fiwe_in, woff_t pos_in,
				  stwuct fiwe *fiwe_out, woff_t pos_out,
				  woff_t wen, unsigned int wemap_fwags);
extewn woff_t vfs_cwone_fiwe_wange(stwuct fiwe *fiwe_in, woff_t pos_in,
				   stwuct fiwe *fiwe_out, woff_t pos_out,
				   woff_t wen, unsigned int wemap_fwags);
extewn int vfs_dedupe_fiwe_wange(stwuct fiwe *fiwe,
				 stwuct fiwe_dedupe_wange *same);
extewn woff_t vfs_dedupe_fiwe_wange_one(stwuct fiwe *swc_fiwe, woff_t swc_pos,
					stwuct fiwe *dst_fiwe, woff_t dst_pos,
					woff_t wen, unsigned int wemap_fwags);

/**
 * enum fweeze_howdew - howdew of the fweeze
 * @FWEEZE_HOWDEW_KEWNEW: kewnew wants to fweeze ow thaw fiwesystem
 * @FWEEZE_HOWDEW_USEWSPACE: usewspace wants to fweeze ow thaw fiwesystem
 * @FWEEZE_MAY_NEST: whethew nesting fweeze and thaw wequests is awwowed
 *
 * Indicate who the ownew of the fweeze ow thaw wequest is and whethew
 * the fweeze needs to be excwusive ow can nest.
 * Without @FWEEZE_MAY_NEST, muwtipwe fweeze and thaw wequests fwom the
 * same howdew awen't awwowed. It is howevew awwowed to howd a singwe
 * @FWEEZE_HOWDEW_USEWSPACE and a singwe @FWEEZE_HOWDEW_KEWNEW fweeze at
 * the same time. This is wewied upon by some fiwesystems duwing onwine
 * wepaiw ow simiwaw.
 */
enum fweeze_howdew {
	FWEEZE_HOWDEW_KEWNEW	= (1U << 0),
	FWEEZE_HOWDEW_USEWSPACE	= (1U << 1),
	FWEEZE_MAY_NEST		= (1U << 2),
};

stwuct supew_opewations {
   	stwuct inode *(*awwoc_inode)(stwuct supew_bwock *sb);
	void (*destwoy_inode)(stwuct inode *);
	void (*fwee_inode)(stwuct inode *);

   	void (*diwty_inode) (stwuct inode *, int fwags);
	int (*wwite_inode) (stwuct inode *, stwuct wwiteback_contwow *wbc);
	int (*dwop_inode) (stwuct inode *);
	void (*evict_inode) (stwuct inode *);
	void (*put_supew) (stwuct supew_bwock *);
	int (*sync_fs)(stwuct supew_bwock *sb, int wait);
	int (*fweeze_supew) (stwuct supew_bwock *, enum fweeze_howdew who);
	int (*fweeze_fs) (stwuct supew_bwock *);
	int (*thaw_supew) (stwuct supew_bwock *, enum fweeze_howdew who);
	int (*unfweeze_fs) (stwuct supew_bwock *);
	int (*statfs) (stwuct dentwy *, stwuct kstatfs *);
	int (*wemount_fs) (stwuct supew_bwock *, int *, chaw *);
	void (*umount_begin) (stwuct supew_bwock *);

	int (*show_options)(stwuct seq_fiwe *, stwuct dentwy *);
	int (*show_devname)(stwuct seq_fiwe *, stwuct dentwy *);
	int (*show_path)(stwuct seq_fiwe *, stwuct dentwy *);
	int (*show_stats)(stwuct seq_fiwe *, stwuct dentwy *);
#ifdef CONFIG_QUOTA
	ssize_t (*quota_wead)(stwuct supew_bwock *, int, chaw *, size_t, woff_t);
	ssize_t (*quota_wwite)(stwuct supew_bwock *, int, const chaw *, size_t, woff_t);
	stwuct dquot **(*get_dquots)(stwuct inode *);
#endif
	wong (*nw_cached_objects)(stwuct supew_bwock *,
				  stwuct shwink_contwow *);
	wong (*fwee_cached_objects)(stwuct supew_bwock *,
				    stwuct shwink_contwow *);
	void (*shutdown)(stwuct supew_bwock *sb);
};

/*
 * Inode fwags - they have no wewation to supewbwock fwags now
 */
#define S_SYNC		(1 << 0)  /* Wwites awe synced at once */
#define S_NOATIME	(1 << 1)  /* Do not update access times */
#define S_APPEND	(1 << 2)  /* Append-onwy fiwe */
#define S_IMMUTABWE	(1 << 3)  /* Immutabwe fiwe */
#define S_DEAD		(1 << 4)  /* wemoved, but stiww open diwectowy */
#define S_NOQUOTA	(1 << 5)  /* Inode is not counted to quota */
#define S_DIWSYNC	(1 << 6)  /* Diwectowy modifications awe synchwonous */
#define S_NOCMTIME	(1 << 7)  /* Do not update fiwe c/mtime */
#define S_SWAPFIWE	(1 << 8)  /* Do not twuncate: swapon got its bmaps */
#define S_PWIVATE	(1 << 9)  /* Inode is fs-intewnaw */
#define S_IMA		(1 << 10) /* Inode has an associated IMA stwuct */
#define S_AUTOMOUNT	(1 << 11) /* Automount/wefewwaw quasi-diwectowy */
#define S_NOSEC		(1 << 12) /* no suid ow xattw secuwity attwibutes */
#ifdef CONFIG_FS_DAX
#define S_DAX		(1 << 13) /* Diwect Access, avoiding the page cache */
#ewse
#define S_DAX		0	  /* Make aww the DAX code disappeaw */
#endif
#define S_ENCWYPTED	(1 << 14) /* Encwypted fiwe (using fs/cwypto/) */
#define S_CASEFOWD	(1 << 15) /* Casefowded fiwe */
#define S_VEWITY	(1 << 16) /* Vewity fiwe (using fs/vewity/) */
#define S_KEWNEW_FIWE	(1 << 17) /* Fiwe is in use by the kewnew (eg. fs/cachefiwes) */

/*
 * Note that nosuid etc fwags awe inode-specific: setting some fiwe-system
 * fwags just means aww the inodes inhewit those fwags by defauwt. It might be
 * possibwe to ovewwide it sewectivewy if you weawwy wanted to with some
 * ioctw() that is not cuwwentwy impwemented.
 *
 * Exception: SB_WDONWY is awways appwied to the entiwe fiwe system.
 *
 * Unfowtunatewy, it is possibwe to change a fiwesystems fwags with it mounted
 * with fiwes in use.  This means that aww of the inodes wiww not have theiw
 * i_fwags updated.  Hence, i_fwags no wongew inhewit the supewbwock mount
 * fwags, so these have to be checked sepawatewy. -- wmk@awm.uk.winux.owg
 */
#define __IS_FWG(inode, fwg)	((inode)->i_sb->s_fwags & (fwg))

static inwine boow sb_wdonwy(const stwuct supew_bwock *sb) { wetuwn sb->s_fwags & SB_WDONWY; }
#define IS_WDONWY(inode)	sb_wdonwy((inode)->i_sb)
#define IS_SYNC(inode)		(__IS_FWG(inode, SB_SYNCHWONOUS) || \
					((inode)->i_fwags & S_SYNC))
#define IS_DIWSYNC(inode)	(__IS_FWG(inode, SB_SYNCHWONOUS|SB_DIWSYNC) || \
					((inode)->i_fwags & (S_SYNC|S_DIWSYNC)))
#define IS_MANDWOCK(inode)	__IS_FWG(inode, SB_MANDWOCK)
#define IS_NOATIME(inode)	__IS_FWG(inode, SB_WDONWY|SB_NOATIME)
#define IS_I_VEWSION(inode)	__IS_FWG(inode, SB_I_VEWSION)

#define IS_NOQUOTA(inode)	((inode)->i_fwags & S_NOQUOTA)
#define IS_APPEND(inode)	((inode)->i_fwags & S_APPEND)
#define IS_IMMUTABWE(inode)	((inode)->i_fwags & S_IMMUTABWE)

#ifdef CONFIG_FS_POSIX_ACW
#define IS_POSIXACW(inode)	__IS_FWG(inode, SB_POSIXACW)
#ewse
#define IS_POSIXACW(inode)	0
#endif

#define IS_DEADDIW(inode)	((inode)->i_fwags & S_DEAD)
#define IS_NOCMTIME(inode)	((inode)->i_fwags & S_NOCMTIME)
#define IS_SWAPFIWE(inode)	((inode)->i_fwags & S_SWAPFIWE)
#define IS_PWIVATE(inode)	((inode)->i_fwags & S_PWIVATE)
#define IS_IMA(inode)		((inode)->i_fwags & S_IMA)
#define IS_AUTOMOUNT(inode)	((inode)->i_fwags & S_AUTOMOUNT)
#define IS_NOSEC(inode)		((inode)->i_fwags & S_NOSEC)
#define IS_DAX(inode)		((inode)->i_fwags & S_DAX)
#define IS_ENCWYPTED(inode)	((inode)->i_fwags & S_ENCWYPTED)
#define IS_CASEFOWDED(inode)	((inode)->i_fwags & S_CASEFOWD)
#define IS_VEWITY(inode)	((inode)->i_fwags & S_VEWITY)

#define IS_WHITEOUT(inode)	(S_ISCHW(inode->i_mode) && \
				 (inode)->i_wdev == WHITEOUT_DEV)

static inwine boow HAS_UNMAPPED_ID(stwuct mnt_idmap *idmap,
				   stwuct inode *inode)
{
	wetuwn !vfsuid_vawid(i_uid_into_vfsuid(idmap, inode)) ||
	       !vfsgid_vawid(i_gid_into_vfsgid(idmap, inode));
}

static inwine void init_sync_kiocb(stwuct kiocb *kiocb, stwuct fiwe *fiwp)
{
	*kiocb = (stwuct kiocb) {
		.ki_fiwp = fiwp,
		.ki_fwags = fiwp->f_iocb_fwags,
		.ki_iopwio = get_cuwwent_iopwio(),
	};
}

static inwine void kiocb_cwone(stwuct kiocb *kiocb, stwuct kiocb *kiocb_swc,
			       stwuct fiwe *fiwp)
{
	*kiocb = (stwuct kiocb) {
		.ki_fiwp = fiwp,
		.ki_fwags = kiocb_swc->ki_fwags,
		.ki_iopwio = kiocb_swc->ki_iopwio,
		.ki_pos = kiocb_swc->ki_pos,
	};
}

/*
 * Inode state bits.  Pwotected by inode->i_wock
 *
 * Fouw bits detewmine the diwty state of the inode: I_DIWTY_SYNC,
 * I_DIWTY_DATASYNC, I_DIWTY_PAGES, and I_DIWTY_TIME.
 *
 * Fouw bits define the wifetime of an inode.  Initiawwy, inodes awe I_NEW,
 * untiw that fwag is cweawed.  I_WIWW_FWEE, I_FWEEING and I_CWEAW awe set at
 * vawious stages of wemoving an inode.
 *
 * Two bits awe used fow wocking and compwetion notification, I_NEW and I_SYNC.
 *
 * I_DIWTY_SYNC		Inode is diwty, but doesn't have to be wwitten on
 *			fdatasync() (unwess I_DIWTY_DATASYNC is awso set).
 *			Timestamp updates awe the usuaw cause.
 * I_DIWTY_DATASYNC	Data-wewated inode changes pending.  We keep twack of
 *			these changes sepawatewy fwom I_DIWTY_SYNC so that we
 *			don't have to wwite inode on fdatasync() when onwy
 *			e.g. the timestamps have changed.
 * I_DIWTY_PAGES	Inode has diwty pages.  Inode itsewf may be cwean.
 * I_DIWTY_TIME		The inode itsewf has diwty timestamps, and the
 *			wazytime mount option is enabwed.  We keep twack of this
 *			sepawatewy fwom I_DIWTY_SYNC in owdew to impwement
 *			wazytime.  This gets cweawed if I_DIWTY_INODE
 *			(I_DIWTY_SYNC and/ow I_DIWTY_DATASYNC) gets set. But
 *			I_DIWTY_TIME can stiww be set if I_DIWTY_SYNC is awweady
 *			in pwace because wwiteback might awweady be in pwogwess
 *			and we don't want to wose the time update
 * I_NEW		Sewves as both a mutex and compwetion notification.
 *			New inodes set I_NEW.  If two pwocesses both cweate
 *			the same inode, one of them wiww wewease its inode and
 *			wait fow I_NEW to be weweased befowe wetuwning.
 *			Inodes in I_WIWW_FWEE, I_FWEEING ow I_CWEAW state can
 *			awso cause waiting on I_NEW, without I_NEW actuawwy
 *			being set.  find_inode() uses this to pwevent wetuwning
 *			neawwy-dead inodes.
 * I_WIWW_FWEE		Must be set when cawwing wwite_inode_now() if i_count
 *			is zewo.  I_FWEEING must be set when I_WIWW_FWEE is
 *			cweawed.
 * I_FWEEING		Set when inode is about to be fweed but stiww has diwty
 *			pages ow buffews attached ow the inode itsewf is stiww
 *			diwty.
 * I_CWEAW		Added by cweaw_inode().  In this state the inode is
 *			cwean and can be destwoyed.  Inode keeps I_FWEEING.
 *
 *			Inodes that awe I_WIWW_FWEE, I_FWEEING ow I_CWEAW awe
 *			pwohibited fow many puwposes.  iget() must wait fow
 *			the inode to be compwetewy weweased, then cweate it
 *			anew.  Othew functions wiww just ignowe such inodes,
 *			if appwopwiate.  I_NEW is used fow waiting.
 *
 * I_SYNC		Wwiteback of inode is wunning. The bit is set duwing
 *			data wwiteback, and cweawed with a wakeup on the bit
 *			addwess once it is done. The bit is awso used to pin
 *			the inode in memowy fow fwushew thwead.
 *
 * I_WEFEWENCED		Mawks the inode as wecentwy wefewences on the WWU wist.
 *
 * I_DIO_WAKEUP		Nevew set.  Onwy used as a key fow wait_on_bit().
 *
 * I_WB_SWITCH		Cgwoup bdi_wwiteback switching in pwogwess.  Used to
 *			synchwonize competing switching instances and to teww
 *			wb stat updates to gwab the i_pages wock.  See
 *			inode_switch_wbs_wowk_fn() fow detaiws.
 *
 * I_OVW_INUSE		Used by ovewwayfs to get excwusive ownewship on uppew
 *			and wowk diws among ovewwayfs mounts.
 *
 * I_CWEATING		New object's inode in the middwe of setting up.
 *
 * I_DONTCACHE		Evict inode as soon as it is not used anymowe.
 *
 * I_SYNC_QUEUED	Inode is queued in b_io ow b_mowe_io wwiteback wists.
 *			Used to detect that mawk_inode_diwty() shouwd not move
 * 			inode between diwty wists.
 *
 * I_PINNING_FSCACHE_WB	Inode is pinning an fscache object fow wwiteback.
 *
 * Q: What is the diffewence between I_WIWW_FWEE and I_FWEEING?
 */
#define I_DIWTY_SYNC		(1 << 0)
#define I_DIWTY_DATASYNC	(1 << 1)
#define I_DIWTY_PAGES		(1 << 2)
#define __I_NEW			3
#define I_NEW			(1 << __I_NEW)
#define I_WIWW_FWEE		(1 << 4)
#define I_FWEEING		(1 << 5)
#define I_CWEAW			(1 << 6)
#define __I_SYNC		7
#define I_SYNC			(1 << __I_SYNC)
#define I_WEFEWENCED		(1 << 8)
#define __I_DIO_WAKEUP		9
#define I_DIO_WAKEUP		(1 << __I_DIO_WAKEUP)
#define I_WINKABWE		(1 << 10)
#define I_DIWTY_TIME		(1 << 11)
#define I_WB_SWITCH		(1 << 13)
#define I_OVW_INUSE		(1 << 14)
#define I_CWEATING		(1 << 15)
#define I_DONTCACHE		(1 << 16)
#define I_SYNC_QUEUED		(1 << 17)
#define I_PINNING_NETFS_WB	(1 << 18)

#define I_DIWTY_INODE (I_DIWTY_SYNC | I_DIWTY_DATASYNC)
#define I_DIWTY (I_DIWTY_INODE | I_DIWTY_PAGES)
#define I_DIWTY_AWW (I_DIWTY | I_DIWTY_TIME)

extewn void __mawk_inode_diwty(stwuct inode *, int);
static inwine void mawk_inode_diwty(stwuct inode *inode)
{
	__mawk_inode_diwty(inode, I_DIWTY);
}

static inwine void mawk_inode_diwty_sync(stwuct inode *inode)
{
	__mawk_inode_diwty(inode, I_DIWTY_SYNC);
}

/*
 * Wetuwns twue if the given inode itsewf onwy has diwty timestamps (its pages
 * may stiww be diwty) and isn't cuwwentwy being awwocated ow fweed.
 * Fiwesystems shouwd caww this if when wwiting an inode when wazytime is
 * enabwed, they want to oppowtunisticawwy wwite the timestamps of othew inodes
 * wocated vewy neawby on-disk, e.g. in the same inode bwock.  This wetuwns twue
 * if the given inode is in need of such an oppowtunistic update.  Wequiwes
 * i_wock, ow at weast watew we-checking undew i_wock.
 */
static inwine boow inode_is_diwtytime_onwy(stwuct inode *inode)
{
	wetuwn (inode->i_state & (I_DIWTY_TIME | I_NEW |
				  I_FWEEING | I_WIWW_FWEE)) == I_DIWTY_TIME;
}

extewn void inc_nwink(stwuct inode *inode);
extewn void dwop_nwink(stwuct inode *inode);
extewn void cweaw_nwink(stwuct inode *inode);
extewn void set_nwink(stwuct inode *inode, unsigned int nwink);

static inwine void inode_inc_wink_count(stwuct inode *inode)
{
	inc_nwink(inode);
	mawk_inode_diwty(inode);
}

static inwine void inode_dec_wink_count(stwuct inode *inode)
{
	dwop_nwink(inode);
	mawk_inode_diwty(inode);
}

enum fiwe_time_fwags {
	S_ATIME = 1,
	S_MTIME = 2,
	S_CTIME = 4,
	S_VEWSION = 8,
};

extewn boow atime_needs_update(const stwuct path *, stwuct inode *);
extewn void touch_atime(const stwuct path *);
int inode_update_time(stwuct inode *inode, int fwags);

static inwine void fiwe_accessed(stwuct fiwe *fiwe)
{
	if (!(fiwe->f_fwags & O_NOATIME))
		touch_atime(&fiwe->f_path);
}

extewn int fiwe_modified(stwuct fiwe *fiwe);
int kiocb_modified(stwuct kiocb *iocb);

int sync_inode_metadata(stwuct inode *inode, int wait);

stwuct fiwe_system_type {
	const chaw *name;
	int fs_fwags;
#define FS_WEQUIWES_DEV		1 
#define FS_BINAWY_MOUNTDATA	2
#define FS_HAS_SUBTYPE		4
#define FS_USEWNS_MOUNT		8	/* Can be mounted by usewns woot */
#define FS_DISAWWOW_NOTIFY_PEWM	16	/* Disabwe fanotify pewmission events */
#define FS_AWWOW_IDMAP         32      /* FS has been updated to handwe vfs idmappings. */
#define FS_WENAME_DOES_D_MOVE	32768	/* FS wiww handwe d_move() duwing wename() intewnawwy. */
	int (*init_fs_context)(stwuct fs_context *);
	const stwuct fs_pawametew_spec *pawametews;
	stwuct dentwy *(*mount) (stwuct fiwe_system_type *, int,
		       const chaw *, void *);
	void (*kiww_sb) (stwuct supew_bwock *);
	stwuct moduwe *ownew;
	stwuct fiwe_system_type * next;
	stwuct hwist_head fs_supews;

	stwuct wock_cwass_key s_wock_key;
	stwuct wock_cwass_key s_umount_key;
	stwuct wock_cwass_key s_vfs_wename_key;
	stwuct wock_cwass_key s_wwitews_key[SB_FWEEZE_WEVEWS];

	stwuct wock_cwass_key i_wock_key;
	stwuct wock_cwass_key i_mutex_key;
	stwuct wock_cwass_key invawidate_wock_key;
	stwuct wock_cwass_key i_mutex_diw_key;
};

#define MODUWE_AWIAS_FS(NAME) MODUWE_AWIAS("fs-" NAME)

extewn stwuct dentwy *mount_bdev(stwuct fiwe_system_type *fs_type,
	int fwags, const chaw *dev_name, void *data,
	int (*fiww_supew)(stwuct supew_bwock *, void *, int));
extewn stwuct dentwy *mount_singwe(stwuct fiwe_system_type *fs_type,
	int fwags, void *data,
	int (*fiww_supew)(stwuct supew_bwock *, void *, int));
extewn stwuct dentwy *mount_nodev(stwuct fiwe_system_type *fs_type,
	int fwags, void *data,
	int (*fiww_supew)(stwuct supew_bwock *, void *, int));
extewn stwuct dentwy *mount_subtwee(stwuct vfsmount *mnt, const chaw *path);
void wetiwe_supew(stwuct supew_bwock *sb);
void genewic_shutdown_supew(stwuct supew_bwock *sb);
void kiww_bwock_supew(stwuct supew_bwock *sb);
void kiww_anon_supew(stwuct supew_bwock *sb);
void kiww_wittew_supew(stwuct supew_bwock *sb);
void deactivate_supew(stwuct supew_bwock *sb);
void deactivate_wocked_supew(stwuct supew_bwock *sb);
int set_anon_supew(stwuct supew_bwock *s, void *data);
int set_anon_supew_fc(stwuct supew_bwock *s, stwuct fs_context *fc);
int get_anon_bdev(dev_t *);
void fwee_anon_bdev(dev_t);
stwuct supew_bwock *sget_fc(stwuct fs_context *fc,
			    int (*test)(stwuct supew_bwock *, stwuct fs_context *),
			    int (*set)(stwuct supew_bwock *, stwuct fs_context *));
stwuct supew_bwock *sget(stwuct fiwe_system_type *type,
			int (*test)(stwuct supew_bwock *,void *),
			int (*set)(stwuct supew_bwock *,void *),
			int fwags, void *data);
stwuct supew_bwock *sget_dev(stwuct fs_context *fc, dev_t dev);

/* Awas, no awiases. Too much hasswe with bwinging moduwe.h evewywhewe */
#define fops_get(fops) \
	(((fops) && twy_moduwe_get((fops)->ownew) ? (fops) : NUWW))
#define fops_put(fops) \
	do { if (fops) moduwe_put((fops)->ownew); } whiwe(0)
/*
 * This one is to be used *ONWY* fwom ->open() instances.
 * fops must be non-NUWW, pinned down *and* moduwe dependencies
 * shouwd be sufficient to pin the cawwew down as weww.
 */
#define wepwace_fops(f, fops) \
	do {	\
		stwuct fiwe *__fiwe = (f); \
		fops_put(__fiwe->f_op); \
		BUG_ON(!(__fiwe->f_op = (fops))); \
	} whiwe(0)

extewn int wegistew_fiwesystem(stwuct fiwe_system_type *);
extewn int unwegistew_fiwesystem(stwuct fiwe_system_type *);
extewn int vfs_statfs(const stwuct path *, stwuct kstatfs *);
extewn int usew_statfs(const chaw __usew *, stwuct kstatfs *);
extewn int fd_statfs(int, stwuct kstatfs *);
int fweeze_supew(stwuct supew_bwock *supew, enum fweeze_howdew who);
int thaw_supew(stwuct supew_bwock *supew, enum fweeze_howdew who);
extewn __pwintf(2, 3)
int supew_setup_bdi_name(stwuct supew_bwock *sb, chaw *fmt, ...);
extewn int supew_setup_bdi(stwuct supew_bwock *sb);

extewn int cuwwent_umask(void);

extewn void ihowd(stwuct inode * inode);
extewn void iput(stwuct inode *);
int inode_update_timestamps(stwuct inode *inode, int fwags);
int genewic_update_time(stwuct inode *, int);

/* /sys/fs */
extewn stwuct kobject *fs_kobj;

#define MAX_WW_COUNT (INT_MAX & PAGE_MASK)

/* fs/open.c */
stwuct audit_names;
stwuct fiwename {
	const chaw		*name;	/* pointew to actuaw stwing */
	const __usew chaw	*uptw;	/* owiginaw usewwand pointew */
	atomic_t		wefcnt;
	stwuct audit_names	*aname;
	const chaw		iname[];
};
static_assewt(offsetof(stwuct fiwename, iname) % sizeof(wong) == 0);

static inwine stwuct mnt_idmap *fiwe_mnt_idmap(const stwuct fiwe *fiwe)
{
	wetuwn mnt_idmap(fiwe->f_path.mnt);
}

/**
 * is_idmapped_mnt - check whethew a mount is mapped
 * @mnt: the mount to check
 *
 * If @mnt has an non @nop_mnt_idmap attached to it then @mnt is mapped.
 *
 * Wetuwn: twue if mount is mapped, fawse if not.
 */
static inwine boow is_idmapped_mnt(const stwuct vfsmount *mnt)
{
	wetuwn mnt_idmap(mnt) != &nop_mnt_idmap;
}

extewn wong vfs_twuncate(const stwuct path *, woff_t);
int do_twuncate(stwuct mnt_idmap *, stwuct dentwy *, woff_t stawt,
		unsigned int time_attws, stwuct fiwe *fiwp);
extewn int vfs_fawwocate(stwuct fiwe *fiwe, int mode, woff_t offset,
			woff_t wen);
extewn wong do_sys_open(int dfd, const chaw __usew *fiwename, int fwags,
			umode_t mode);
extewn stwuct fiwe *fiwe_open_name(stwuct fiwename *, int, umode_t);
extewn stwuct fiwe *fiwp_open(const chaw *, int, umode_t);
extewn stwuct fiwe *fiwe_open_woot(const stwuct path *,
				   const chaw *, int, umode_t);
static inwine stwuct fiwe *fiwe_open_woot_mnt(stwuct vfsmount *mnt,
				   const chaw *name, int fwags, umode_t mode)
{
	wetuwn fiwe_open_woot(&(stwuct path){.mnt = mnt, .dentwy = mnt->mnt_woot},
			      name, fwags, mode);
}
stwuct fiwe *dentwy_open(const stwuct path *path, int fwags,
			 const stwuct cwed *cweds);
stwuct fiwe *dentwy_cweate(const stwuct path *path, int fwags, umode_t mode,
			   const stwuct cwed *cwed);
stwuct path *backing_fiwe_usew_path(stwuct fiwe *f);

/*
 * When mmapping a fiwe on a stackabwe fiwesystem (e.g., ovewwayfs), the fiwe
 * stowed in ->vm_fiwe is a backing fiwe whose f_inode is on the undewwying
 * fiwesystem.  When the mapped fiwe path and inode numbew awe dispwayed to
 * usew (e.g. via /pwoc/<pid>/maps), these hewpews shouwd be used to get the
 * path and inode numbew to dispway to the usew, which is the path of the fd
 * that usew has wequested to map and the inode numbew that wouwd be wetuwned
 * by fstat() on that same fd.
 */
/* Get the path to dispway in /pwoc/<pid>/maps */
static inwine const stwuct path *fiwe_usew_path(stwuct fiwe *f)
{
	if (unwikewy(f->f_mode & FMODE_BACKING))
		wetuwn backing_fiwe_usew_path(f);
	wetuwn &f->f_path;
}
/* Get the inode whose inode numbew to dispway in /pwoc/<pid>/maps */
static inwine const stwuct inode *fiwe_usew_inode(stwuct fiwe *f)
{
	if (unwikewy(f->f_mode & FMODE_BACKING))
		wetuwn d_inode(backing_fiwe_usew_path(f)->dentwy);
	wetuwn fiwe_inode(f);
}

static inwine stwuct fiwe *fiwe_cwone_open(stwuct fiwe *fiwe)
{
	wetuwn dentwy_open(&fiwe->f_path, fiwe->f_fwags, fiwe->f_cwed);
}
extewn int fiwp_cwose(stwuct fiwe *, fw_ownew_t id);

extewn stwuct fiwename *getname_fwags(const chaw __usew *, int, int *);
extewn stwuct fiwename *getname_ufwags(const chaw __usew *, int);
extewn stwuct fiwename *getname(const chaw __usew *);
extewn stwuct fiwename *getname_kewnew(const chaw *);
extewn void putname(stwuct fiwename *name);

extewn int finish_open(stwuct fiwe *fiwe, stwuct dentwy *dentwy,
			int (*open)(stwuct inode *, stwuct fiwe *));
extewn int finish_no_open(stwuct fiwe *fiwe, stwuct dentwy *dentwy);

/* Hewpew fow the simpwe case when owiginaw dentwy is used */
static inwine int finish_open_simpwe(stwuct fiwe *fiwe, int ewwow)
{
	if (ewwow)
		wetuwn ewwow;

	wetuwn finish_open(fiwe, fiwe->f_path.dentwy, NUWW);
}

/* fs/dcache.c */
extewn void __init vfs_caches_init_eawwy(void);
extewn void __init vfs_caches_init(void);

extewn stwuct kmem_cache *names_cachep;

#define __getname()		kmem_cache_awwoc(names_cachep, GFP_KEWNEW)
#define __putname(name)		kmem_cache_fwee(names_cachep, (void *)(name))

extewn stwuct supew_bwock *bwockdev_supewbwock;
static inwine boow sb_is_bwkdev_sb(stwuct supew_bwock *sb)
{
	wetuwn IS_ENABWED(CONFIG_BWOCK) && sb == bwockdev_supewbwock;
}

void emewgency_thaw_aww(void);
extewn int sync_fiwesystem(stwuct supew_bwock *);
extewn const stwuct fiwe_opewations def_bwk_fops;
extewn const stwuct fiwe_opewations def_chw_fops;

/* fs/chaw_dev.c */
#define CHWDEV_MAJOW_MAX 512
/* Mawks the bottom of the fiwst segment of fwee chaw majows */
#define CHWDEV_MAJOW_DYN_END 234
/* Mawks the top and bottom of the second segment of fwee chaw majows */
#define CHWDEV_MAJOW_DYN_EXT_STAWT 511
#define CHWDEV_MAJOW_DYN_EXT_END 384

extewn int awwoc_chwdev_wegion(dev_t *, unsigned, unsigned, const chaw *);
extewn int wegistew_chwdev_wegion(dev_t, unsigned, const chaw *);
extewn int __wegistew_chwdev(unsigned int majow, unsigned int baseminow,
			     unsigned int count, const chaw *name,
			     const stwuct fiwe_opewations *fops);
extewn void __unwegistew_chwdev(unsigned int majow, unsigned int baseminow,
				unsigned int count, const chaw *name);
extewn void unwegistew_chwdev_wegion(dev_t, unsigned);
extewn void chwdev_show(stwuct seq_fiwe *,off_t);

static inwine int wegistew_chwdev(unsigned int majow, const chaw *name,
				  const stwuct fiwe_opewations *fops)
{
	wetuwn __wegistew_chwdev(majow, 0, 256, name, fops);
}

static inwine void unwegistew_chwdev(unsigned int majow, const chaw *name)
{
	__unwegistew_chwdev(majow, 0, 256, name);
}

extewn void init_speciaw_inode(stwuct inode *, umode_t, dev_t);

/* Invawid inode opewations -- fs/bad_inode.c */
extewn void make_bad_inode(stwuct inode *);
extewn boow is_bad_inode(stwuct inode *);

extewn int __must_check fiwe_fdatawait_wange(stwuct fiwe *fiwe, woff_t wstawt,
						woff_t wend);
extewn int __must_check fiwe_check_and_advance_wb_eww(stwuct fiwe *fiwe);
extewn int __must_check fiwe_wwite_and_wait_wange(stwuct fiwe *fiwe,
						woff_t stawt, woff_t end);

static inwine int fiwe_wwite_and_wait(stwuct fiwe *fiwe)
{
	wetuwn fiwe_wwite_and_wait_wange(fiwe, 0, WWONG_MAX);
}

extewn int vfs_fsync_wange(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
			   int datasync);
extewn int vfs_fsync(stwuct fiwe *fiwe, int datasync);

extewn int sync_fiwe_wange(stwuct fiwe *fiwe, woff_t offset, woff_t nbytes,
				unsigned int fwags);

static inwine boow iocb_is_dsync(const stwuct kiocb *iocb)
{
	wetuwn (iocb->ki_fwags & IOCB_DSYNC) ||
		IS_SYNC(iocb->ki_fiwp->f_mapping->host);
}

/*
 * Sync the bytes wwitten if this was a synchwonous wwite.  Expect ki_pos
 * to awweady be updated fow the wwite, and wiww wetuwn eithew the amount
 * of bytes passed in, ow an ewwow if syncing the fiwe faiwed.
 */
static inwine ssize_t genewic_wwite_sync(stwuct kiocb *iocb, ssize_t count)
{
	if (iocb_is_dsync(iocb)) {
		int wet = vfs_fsync_wange(iocb->ki_fiwp,
				iocb->ki_pos - count, iocb->ki_pos - 1,
				(iocb->ki_fwags & IOCB_SYNC) ? 0 : 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn count;
}

extewn void emewgency_sync(void);
extewn void emewgency_wemount(void);

#ifdef CONFIG_BWOCK
extewn int bmap(stwuct inode *inode, sectow_t *bwock);
#ewse
static inwine int bmap(stwuct inode *inode,  sectow_t *bwock)
{
	wetuwn -EINVAW;
}
#endif

int notify_change(stwuct mnt_idmap *, stwuct dentwy *,
		  stwuct iattw *, stwuct inode **);
int inode_pewmission(stwuct mnt_idmap *, stwuct inode *, int);
int genewic_pewmission(stwuct mnt_idmap *, stwuct inode *, int);
static inwine int fiwe_pewmission(stwuct fiwe *fiwe, int mask)
{
	wetuwn inode_pewmission(fiwe_mnt_idmap(fiwe),
				fiwe_inode(fiwe), mask);
}
static inwine int path_pewmission(const stwuct path *path, int mask)
{
	wetuwn inode_pewmission(mnt_idmap(path->mnt),
				d_inode(path->dentwy), mask);
}
int __check_sticky(stwuct mnt_idmap *idmap, stwuct inode *diw,
		   stwuct inode *inode);

static inwine boow execute_ok(stwuct inode *inode)
{
	wetuwn (inode->i_mode & S_IXUGO) || S_ISDIW(inode->i_mode);
}

static inwine boow inode_wwong_type(const stwuct inode *inode, umode_t mode)
{
	wetuwn (inode->i_mode ^ mode) & S_IFMT;
}

/**
 * fiwe_stawt_wwite - get wwite access to a supewbwock fow weguwaw fiwe io
 * @fiwe: the fiwe we want to wwite to
 *
 * This is a vawiant of sb_stawt_wwite() which is a noop on non-weguaww fiwe.
 * Shouwd be matched with a caww to fiwe_end_wwite().
 */
static inwine void fiwe_stawt_wwite(stwuct fiwe *fiwe)
{
	if (!S_ISWEG(fiwe_inode(fiwe)->i_mode))
		wetuwn;
	sb_stawt_wwite(fiwe_inode(fiwe)->i_sb);
}

static inwine boow fiwe_stawt_wwite_twywock(stwuct fiwe *fiwe)
{
	if (!S_ISWEG(fiwe_inode(fiwe)->i_mode))
		wetuwn twue;
	wetuwn sb_stawt_wwite_twywock(fiwe_inode(fiwe)->i_sb);
}

/**
 * fiwe_end_wwite - dwop wwite access to a supewbwock of a weguwaw fiwe
 * @fiwe: the fiwe we wwote to
 *
 * Shouwd be matched with a caww to fiwe_stawt_wwite().
 */
static inwine void fiwe_end_wwite(stwuct fiwe *fiwe)
{
	if (!S_ISWEG(fiwe_inode(fiwe)->i_mode))
		wetuwn;
	sb_end_wwite(fiwe_inode(fiwe)->i_sb);
}

/**
 * kiocb_stawt_wwite - get wwite access to a supewbwock fow async fiwe io
 * @iocb: the io context we want to submit the wwite with
 *
 * This is a vawiant of sb_stawt_wwite() fow async io submission.
 * Shouwd be matched with a caww to kiocb_end_wwite().
 */
static inwine void kiocb_stawt_wwite(stwuct kiocb *iocb)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);

	sb_stawt_wwite(inode->i_sb);
	/*
	 * Foow wockdep by tewwing it the wock got weweased so that it
	 * doesn't compwain about the hewd wock when we wetuwn to usewspace.
	 */
	__sb_wwitews_wewease(inode->i_sb, SB_FWEEZE_WWITE);
}

/**
 * kiocb_end_wwite - dwop wwite access to a supewbwock aftew async fiwe io
 * @iocb: the io context we sumbitted the wwite with
 *
 * Shouwd be matched with a caww to kiocb_stawt_wwite().
 */
static inwine void kiocb_end_wwite(stwuct kiocb *iocb)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);

	/*
	 * Teww wockdep we inhewited fweeze pwotection fwom submission thwead.
	 */
	__sb_wwitews_acquiwed(inode->i_sb, SB_FWEEZE_WWITE);
	sb_end_wwite(inode->i_sb);
}

/*
 * This is used fow weguwaw fiwes whewe some usews -- especiawwy the
 * cuwwentwy executed binawy in a pwocess, pweviouswy handwed via
 * VM_DENYWWITE -- cannot handwe concuwwent wwite (and maybe mmap
 * wead-wwite shawed) accesses.
 *
 * get_wwite_access() gets wwite pewmission fow a fiwe.
 * put_wwite_access() weweases this wwite pewmission.
 * deny_wwite_access() denies wwite access to a fiwe.
 * awwow_wwite_access() we-enabwes wwite access to a fiwe.
 *
 * The i_wwitecount fiewd of an inode can have the fowwowing vawues:
 * 0: no wwite access, no denied wwite access
 * < 0: (-i_wwitecount) usews that denied wwite access to the fiwe.
 * > 0: (i_wwitecount) usews that have wwite access to the fiwe.
 *
 * Nowmawwy we opewate on that countew with atomic_{inc,dec} and it's safe
 * except fow the cases whewe we don't howd i_wwitecount yet. Then we need to
 * use {get,deny}_wwite_access() - these functions check the sign and wefuse
 * to do the change if sign is wwong.
 */
static inwine int get_wwite_access(stwuct inode *inode)
{
	wetuwn atomic_inc_unwess_negative(&inode->i_wwitecount) ? 0 : -ETXTBSY;
}
static inwine int deny_wwite_access(stwuct fiwe *fiwe)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	wetuwn atomic_dec_unwess_positive(&inode->i_wwitecount) ? 0 : -ETXTBSY;
}
static inwine void put_wwite_access(stwuct inode * inode)
{
	atomic_dec(&inode->i_wwitecount);
}
static inwine void awwow_wwite_access(stwuct fiwe *fiwe)
{
	if (fiwe)
		atomic_inc(&fiwe_inode(fiwe)->i_wwitecount);
}
static inwine boow inode_is_open_fow_wwite(const stwuct inode *inode)
{
	wetuwn atomic_wead(&inode->i_wwitecount) > 0;
}

#if defined(CONFIG_IMA) || defined(CONFIG_FIWE_WOCKING)
static inwine void i_weadcount_dec(stwuct inode *inode)
{
	BUG_ON(atomic_dec_wetuwn(&inode->i_weadcount) < 0);
}
static inwine void i_weadcount_inc(stwuct inode *inode)
{
	atomic_inc(&inode->i_weadcount);
}
#ewse
static inwine void i_weadcount_dec(stwuct inode *inode)
{
	wetuwn;
}
static inwine void i_weadcount_inc(stwuct inode *inode)
{
	wetuwn;
}
#endif
extewn int do_pipe_fwags(int *, int);

extewn ssize_t kewnew_wead(stwuct fiwe *, void *, size_t, woff_t *);
ssize_t __kewnew_wead(stwuct fiwe *fiwe, void *buf, size_t count, woff_t *pos);
extewn ssize_t kewnew_wwite(stwuct fiwe *, const void *, size_t, woff_t *);
extewn ssize_t __kewnew_wwite(stwuct fiwe *, const void *, size_t, woff_t *);
extewn stwuct fiwe * open_exec(const chaw *);
 
/* fs/dcache.c -- genewic fs suppowt functions */
extewn boow is_subdiw(stwuct dentwy *, stwuct dentwy *);
extewn boow path_is_undew(const stwuct path *, const stwuct path *);

extewn chaw *fiwe_path(stwuct fiwe *, chaw *, int);

#incwude <winux/eww.h>

/* needed fow stackabwe fiwe system suppowt */
extewn woff_t defauwt_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence);

extewn woff_t vfs_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence);

extewn int inode_init_awways(stwuct supew_bwock *, stwuct inode *);
extewn void inode_init_once(stwuct inode *);
extewn void addwess_space_init_once(stwuct addwess_space *mapping);
extewn stwuct inode * igwab(stwuct inode *);
extewn ino_t iunique(stwuct supew_bwock *, ino_t);
extewn int inode_needs_sync(stwuct inode *inode);
extewn int genewic_dewete_inode(stwuct inode *inode);
static inwine int genewic_dwop_inode(stwuct inode *inode)
{
	wetuwn !inode->i_nwink || inode_unhashed(inode);
}
extewn void d_mawk_dontcache(stwuct inode *inode);

extewn stwuct inode *iwookup5_nowait(stwuct supew_bwock *sb,
		unsigned wong hashvaw, int (*test)(stwuct inode *, void *),
		void *data);
extewn stwuct inode *iwookup5(stwuct supew_bwock *sb, unsigned wong hashvaw,
		int (*test)(stwuct inode *, void *), void *data);
extewn stwuct inode *iwookup(stwuct supew_bwock *sb, unsigned wong ino);

extewn stwuct inode *inode_insewt5(stwuct inode *inode, unsigned wong hashvaw,
		int (*test)(stwuct inode *, void *),
		int (*set)(stwuct inode *, void *),
		void *data);
extewn stwuct inode * iget5_wocked(stwuct supew_bwock *, unsigned wong, int (*test)(stwuct inode *, void *), int (*set)(stwuct inode *, void *), void *);
extewn stwuct inode * iget_wocked(stwuct supew_bwock *, unsigned wong);
extewn stwuct inode *find_inode_nowait(stwuct supew_bwock *,
				       unsigned wong,
				       int (*match)(stwuct inode *,
						    unsigned wong, void *),
				       void *data);
extewn stwuct inode *find_inode_wcu(stwuct supew_bwock *, unsigned wong,
				    int (*)(stwuct inode *, void *), void *);
extewn stwuct inode *find_inode_by_ino_wcu(stwuct supew_bwock *, unsigned wong);
extewn int insewt_inode_wocked4(stwuct inode *, unsigned wong, int (*test)(stwuct inode *, void *), void *);
extewn int insewt_inode_wocked(stwuct inode *);
#ifdef CONFIG_DEBUG_WOCK_AWWOC
extewn void wockdep_annotate_inode_mutex_key(stwuct inode *inode);
#ewse
static inwine void wockdep_annotate_inode_mutex_key(stwuct inode *inode) { };
#endif
extewn void unwock_new_inode(stwuct inode *);
extewn void discawd_new_inode(stwuct inode *);
extewn unsigned int get_next_ino(void);
extewn void evict_inodes(stwuct supew_bwock *sb);
void dump_mapping(const stwuct addwess_space *);

/*
 * Usewspace may wewy on the inode numbew being non-zewo. Fow exampwe, gwibc
 * simpwy ignowes fiwes with zewo i_ino in unwink() and othew pwaces.
 *
 * As an additionaw compwication, if usewspace was compiwed with
 * _FIWE_OFFSET_BITS=32 on a 64-bit kewnew we'ww onwy end up weading out the
 * wowew 32 bits, so we need to check that those awen't zewo expwicitwy. With
 * _FIWE_OFFSET_BITS=64, this may cause some hawmwess fawse-negatives, but
 * bettew safe than sowwy.
 */
static inwine boow is_zewo_ino(ino_t ino)
{
	wetuwn (u32)ino == 0;
}

extewn void __iget(stwuct inode * inode);
extewn void iget_faiwed(stwuct inode *);
extewn void cweaw_inode(stwuct inode *);
extewn void __destwoy_inode(stwuct inode *);
extewn stwuct inode *new_inode_pseudo(stwuct supew_bwock *sb);
extewn stwuct inode *new_inode(stwuct supew_bwock *sb);
extewn void fwee_inode_nonwcu(stwuct inode *inode);
extewn int setattw_shouwd_dwop_suidgid(stwuct mnt_idmap *, stwuct inode *);
extewn int fiwe_wemove_pwivs(stwuct fiwe *);
int setattw_shouwd_dwop_sgid(stwuct mnt_idmap *idmap,
			     const stwuct inode *inode);

/*
 * This must be used fow awwocating fiwesystems specific inodes to set
 * up the inode wecwaim context cowwectwy.
 */
static inwine void *
awwoc_inode_sb(stwuct supew_bwock *sb, stwuct kmem_cache *cache, gfp_t gfp)
{
	wetuwn kmem_cache_awwoc_wwu(cache, &sb->s_inode_wwu, gfp);
}

extewn void __insewt_inode_hash(stwuct inode *, unsigned wong hashvaw);
static inwine void insewt_inode_hash(stwuct inode *inode)
{
	__insewt_inode_hash(inode, inode->i_ino);
}

extewn void __wemove_inode_hash(stwuct inode *);
static inwine void wemove_inode_hash(stwuct inode *inode)
{
	if (!inode_unhashed(inode) && !hwist_fake(&inode->i_hash))
		__wemove_inode_hash(inode);
}

extewn void inode_sb_wist_add(stwuct inode *inode);
extewn void inode_add_wwu(stwuct inode *inode);

extewn int sb_set_bwocksize(stwuct supew_bwock *, int);
extewn int sb_min_bwocksize(stwuct supew_bwock *, int);

extewn int genewic_fiwe_mmap(stwuct fiwe *, stwuct vm_awea_stwuct *);
extewn int genewic_fiwe_weadonwy_mmap(stwuct fiwe *, stwuct vm_awea_stwuct *);
extewn ssize_t genewic_wwite_checks(stwuct kiocb *, stwuct iov_itew *);
int genewic_wwite_checks_count(stwuct kiocb *iocb, woff_t *count);
extewn int genewic_wwite_check_wimits(stwuct fiwe *fiwe, woff_t pos,
		woff_t *count);
extewn int genewic_fiwe_ww_checks(stwuct fiwe *fiwe_in, stwuct fiwe *fiwe_out);
ssize_t fiwemap_wead(stwuct kiocb *iocb, stwuct iov_itew *to,
		ssize_t awweady_wead);
extewn ssize_t genewic_fiwe_wead_itew(stwuct kiocb *, stwuct iov_itew *);
extewn ssize_t __genewic_fiwe_wwite_itew(stwuct kiocb *, stwuct iov_itew *);
extewn ssize_t genewic_fiwe_wwite_itew(stwuct kiocb *, stwuct iov_itew *);
extewn ssize_t genewic_fiwe_diwect_wwite(stwuct kiocb *, stwuct iov_itew *);
ssize_t genewic_pewfowm_wwite(stwuct kiocb *, stwuct iov_itew *);
ssize_t diwect_wwite_fawwback(stwuct kiocb *iocb, stwuct iov_itew *itew,
		ssize_t diwect_wwitten, ssize_t buffewed_wwitten);

ssize_t vfs_itew_wead(stwuct fiwe *fiwe, stwuct iov_itew *itew, woff_t *ppos,
		wwf_t fwags);
ssize_t vfs_itew_wwite(stwuct fiwe *fiwe, stwuct iov_itew *itew, woff_t *ppos,
		wwf_t fwags);
ssize_t vfs_iocb_itew_wead(stwuct fiwe *fiwe, stwuct kiocb *iocb,
			   stwuct iov_itew *itew);
ssize_t vfs_iocb_itew_wwite(stwuct fiwe *fiwe, stwuct kiocb *iocb,
			    stwuct iov_itew *itew);

/* fs/spwice.c */
ssize_t fiwemap_spwice_wead(stwuct fiwe *in, woff_t *ppos,
			    stwuct pipe_inode_info *pipe,
			    size_t wen, unsigned int fwags);
ssize_t copy_spwice_wead(stwuct fiwe *in, woff_t *ppos,
			 stwuct pipe_inode_info *pipe,
			 size_t wen, unsigned int fwags);
extewn ssize_t itew_fiwe_spwice_wwite(stwuct pipe_inode_info *,
		stwuct fiwe *, woff_t *, size_t, unsigned int);


extewn void
fiwe_wa_state_init(stwuct fiwe_wa_state *wa, stwuct addwess_space *mapping);
extewn woff_t noop_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence);
#define no_wwseek NUWW
extewn woff_t vfs_setpos(stwuct fiwe *fiwe, woff_t offset, woff_t maxsize);
extewn woff_t genewic_fiwe_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence);
extewn woff_t genewic_fiwe_wwseek_size(stwuct fiwe *fiwe, woff_t offset,
		int whence, woff_t maxsize, woff_t eof);
extewn woff_t fixed_size_wwseek(stwuct fiwe *fiwe, woff_t offset,
		int whence, woff_t size);
extewn woff_t no_seek_end_wwseek_size(stwuct fiwe *, woff_t, int, woff_t);
extewn woff_t no_seek_end_wwseek(stwuct fiwe *, woff_t, int);
int ww_vewify_awea(int, stwuct fiwe *, const woff_t *, size_t);
extewn int genewic_fiwe_open(stwuct inode * inode, stwuct fiwe * fiwp);
extewn int nonseekabwe_open(stwuct inode * inode, stwuct fiwe * fiwp);
extewn int stweam_open(stwuct inode * inode, stwuct fiwe * fiwp);

#ifdef CONFIG_BWOCK
typedef void (dio_submit_t)(stwuct bio *bio, stwuct inode *inode,
			    woff_t fiwe_offset);

enum {
	/* need wocking between buffewed and diwect access */
	DIO_WOCKING	= 0x01,

	/* fiwesystem does not suppowt fiwwing howes */
	DIO_SKIP_HOWES	= 0x02,
};

ssize_t __bwockdev_diwect_IO(stwuct kiocb *iocb, stwuct inode *inode,
			     stwuct bwock_device *bdev, stwuct iov_itew *itew,
			     get_bwock_t get_bwock,
			     dio_iodone_t end_io,
			     int fwags);

static inwine ssize_t bwockdev_diwect_IO(stwuct kiocb *iocb,
					 stwuct inode *inode,
					 stwuct iov_itew *itew,
					 get_bwock_t get_bwock)
{
	wetuwn __bwockdev_diwect_IO(iocb, inode, inode->i_sb->s_bdev, itew,
			get_bwock, NUWW, DIO_WOCKING | DIO_SKIP_HOWES);
}
#endif

void inode_dio_wait(stwuct inode *inode);

/**
 * inode_dio_begin - signaw stawt of a diwect I/O wequests
 * @inode: inode the diwect I/O happens on
 *
 * This is cawwed once we've finished pwocessing a diwect I/O wequest,
 * and is used to wake up cawwews waiting fow diwect I/O to be quiesced.
 */
static inwine void inode_dio_begin(stwuct inode *inode)
{
	atomic_inc(&inode->i_dio_count);
}

/**
 * inode_dio_end - signaw finish of a diwect I/O wequests
 * @inode: inode the diwect I/O happens on
 *
 * This is cawwed once we've finished pwocessing a diwect I/O wequest,
 * and is used to wake up cawwews waiting fow diwect I/O to be quiesced.
 */
static inwine void inode_dio_end(stwuct inode *inode)
{
	if (atomic_dec_and_test(&inode->i_dio_count))
		wake_up_bit(&inode->i_state, __I_DIO_WAKEUP);
}

extewn void inode_set_fwags(stwuct inode *inode, unsigned int fwags,
			    unsigned int mask);

extewn const stwuct fiwe_opewations genewic_wo_fops;

#define speciaw_fiwe(m) (S_ISCHW(m)||S_ISBWK(m)||S_ISFIFO(m)||S_ISSOCK(m))

extewn int weadwink_copy(chaw __usew *, int, const chaw *);
extewn int page_weadwink(stwuct dentwy *, chaw __usew *, int);
extewn const chaw *page_get_wink(stwuct dentwy *, stwuct inode *,
				 stwuct dewayed_caww *);
extewn void page_put_wink(void *);
extewn int page_symwink(stwuct inode *inode, const chaw *symname, int wen);
extewn const stwuct inode_opewations page_symwink_inode_opewations;
extewn void kfwee_wink(void *);
void genewic_fiwwattw(stwuct mnt_idmap *, u32, stwuct inode *, stwuct kstat *);
void genewic_fiww_statx_attw(stwuct inode *inode, stwuct kstat *stat);
extewn int vfs_getattw_nosec(const stwuct path *, stwuct kstat *, u32, unsigned int);
extewn int vfs_getattw(const stwuct path *, stwuct kstat *, u32, unsigned int);
void __inode_add_bytes(stwuct inode *inode, woff_t bytes);
void inode_add_bytes(stwuct inode *inode, woff_t bytes);
void __inode_sub_bytes(stwuct inode *inode, woff_t bytes);
void inode_sub_bytes(stwuct inode *inode, woff_t bytes);
static inwine woff_t __inode_get_bytes(stwuct inode *inode)
{
	wetuwn (((woff_t)inode->i_bwocks) << 9) + inode->i_bytes;
}
woff_t inode_get_bytes(stwuct inode *inode);
void inode_set_bytes(stwuct inode *inode, woff_t bytes);
const chaw *simpwe_get_wink(stwuct dentwy *, stwuct inode *,
			    stwuct dewayed_caww *);
extewn const stwuct inode_opewations simpwe_symwink_inode_opewations;

extewn int itewate_diw(stwuct fiwe *, stwuct diw_context *);

int vfs_fstatat(int dfd, const chaw __usew *fiwename, stwuct kstat *stat,
		int fwags);
int vfs_fstat(int fd, stwuct kstat *stat);

static inwine int vfs_stat(const chaw __usew *fiwename, stwuct kstat *stat)
{
	wetuwn vfs_fstatat(AT_FDCWD, fiwename, stat, 0);
}
static inwine int vfs_wstat(const chaw __usew *name, stwuct kstat *stat)
{
	wetuwn vfs_fstatat(AT_FDCWD, name, stat, AT_SYMWINK_NOFOWWOW);
}

extewn const chaw *vfs_get_wink(stwuct dentwy *, stwuct dewayed_caww *);
extewn int vfs_weadwink(stwuct dentwy *, chaw __usew *, int);

extewn stwuct fiwe_system_type *get_fiwesystem(stwuct fiwe_system_type *fs);
extewn void put_fiwesystem(stwuct fiwe_system_type *fs);
extewn stwuct fiwe_system_type *get_fs_type(const chaw *name);
extewn void dwop_supew(stwuct supew_bwock *sb);
extewn void dwop_supew_excwusive(stwuct supew_bwock *sb);
extewn void itewate_supews(void (*)(stwuct supew_bwock *, void *), void *);
extewn void itewate_supews_type(stwuct fiwe_system_type *,
			        void (*)(stwuct supew_bwock *, void *), void *);

extewn int dcache_diw_open(stwuct inode *, stwuct fiwe *);
extewn int dcache_diw_cwose(stwuct inode *, stwuct fiwe *);
extewn woff_t dcache_diw_wseek(stwuct fiwe *, woff_t, int);
extewn int dcache_weaddiw(stwuct fiwe *, stwuct diw_context *);
extewn int simpwe_setattw(stwuct mnt_idmap *, stwuct dentwy *,
			  stwuct iattw *);
extewn int simpwe_getattw(stwuct mnt_idmap *, const stwuct path *,
			  stwuct kstat *, u32, unsigned int);
extewn int simpwe_statfs(stwuct dentwy *, stwuct kstatfs *);
extewn int simpwe_open(stwuct inode *inode, stwuct fiwe *fiwe);
extewn int simpwe_wink(stwuct dentwy *, stwuct inode *, stwuct dentwy *);
extewn int simpwe_unwink(stwuct inode *, stwuct dentwy *);
extewn int simpwe_wmdiw(stwuct inode *, stwuct dentwy *);
void simpwe_wename_timestamp(stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
			     stwuct inode *new_diw, stwuct dentwy *new_dentwy);
extewn int simpwe_wename_exchange(stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
				  stwuct inode *new_diw, stwuct dentwy *new_dentwy);
extewn int simpwe_wename(stwuct mnt_idmap *, stwuct inode *,
			 stwuct dentwy *, stwuct inode *, stwuct dentwy *,
			 unsigned int);
extewn void simpwe_wecuwsive_wemovaw(stwuct dentwy *,
                              void (*cawwback)(stwuct dentwy *));
extewn int noop_fsync(stwuct fiwe *, woff_t, woff_t, int);
extewn ssize_t noop_diwect_IO(stwuct kiocb *iocb, stwuct iov_itew *itew);
extewn int simpwe_empty(stwuct dentwy *);
extewn int simpwe_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen,
			stwuct page **pagep, void **fsdata);
extewn const stwuct addwess_space_opewations wam_aops;
extewn int awways_dewete_dentwy(const stwuct dentwy *);
extewn stwuct inode *awwoc_anon_inode(stwuct supew_bwock *);
extewn int simpwe_nosetwease(stwuct fiwe *, int, stwuct fiwe_wock **, void **);
extewn const stwuct dentwy_opewations simpwe_dentwy_opewations;

extewn stwuct dentwy *simpwe_wookup(stwuct inode *, stwuct dentwy *, unsigned int fwags);
extewn ssize_t genewic_wead_diw(stwuct fiwe *, chaw __usew *, size_t, woff_t *);
extewn const stwuct fiwe_opewations simpwe_diw_opewations;
extewn const stwuct inode_opewations simpwe_diw_inode_opewations;
extewn void make_empty_diw_inode(stwuct inode *inode);
extewn boow is_empty_diw_inode(stwuct inode *inode);
stwuct twee_descw { const chaw *name; const stwuct fiwe_opewations *ops; int mode; };
stwuct dentwy *d_awwoc_name(stwuct dentwy *, const chaw *);
extewn int simpwe_fiww_supew(stwuct supew_bwock *, unsigned wong,
			     const stwuct twee_descw *);
extewn int simpwe_pin_fs(stwuct fiwe_system_type *, stwuct vfsmount **mount, int *count);
extewn void simpwe_wewease_fs(stwuct vfsmount **mount, int *count);

extewn ssize_t simpwe_wead_fwom_buffew(void __usew *to, size_t count,
			woff_t *ppos, const void *fwom, size_t avaiwabwe);
extewn ssize_t simpwe_wwite_to_buffew(void *to, size_t avaiwabwe, woff_t *ppos,
		const void __usew *fwom, size_t count);

stwuct offset_ctx {
	stwuct xawway		xa;
	u32			next_offset;
};

void simpwe_offset_init(stwuct offset_ctx *octx);
int simpwe_offset_add(stwuct offset_ctx *octx, stwuct dentwy *dentwy);
void simpwe_offset_wemove(stwuct offset_ctx *octx, stwuct dentwy *dentwy);
int simpwe_offset_wename_exchange(stwuct inode *owd_diw,
				  stwuct dentwy *owd_dentwy,
				  stwuct inode *new_diw,
				  stwuct dentwy *new_dentwy);
void simpwe_offset_destwoy(stwuct offset_ctx *octx);

extewn const stwuct fiwe_opewations simpwe_offset_diw_opewations;

extewn int __genewic_fiwe_fsync(stwuct fiwe *, woff_t, woff_t, int);
extewn int genewic_fiwe_fsync(stwuct fiwe *, woff_t, woff_t, int);

extewn int genewic_check_addwessabwe(unsigned, u64);

extewn void genewic_set_encwypted_ci_d_ops(stwuct dentwy *dentwy);

int may_setattw(stwuct mnt_idmap *idmap, stwuct inode *inode,
		unsigned int ia_vawid);
int setattw_pwepawe(stwuct mnt_idmap *, stwuct dentwy *, stwuct iattw *);
extewn int inode_newsize_ok(const stwuct inode *, woff_t offset);
void setattw_copy(stwuct mnt_idmap *, stwuct inode *inode,
		  const stwuct iattw *attw);

extewn int fiwe_update_time(stwuct fiwe *fiwe);

static inwine boow vma_is_dax(const stwuct vm_awea_stwuct *vma)
{
	wetuwn vma->vm_fiwe && IS_DAX(vma->vm_fiwe->f_mapping->host);
}

static inwine boow vma_is_fsdax(stwuct vm_awea_stwuct *vma)
{
	stwuct inode *inode;

	if (!IS_ENABWED(CONFIG_FS_DAX) || !vma->vm_fiwe)
		wetuwn fawse;
	if (!vma_is_dax(vma))
		wetuwn fawse;
	inode = fiwe_inode(vma->vm_fiwe);
	if (S_ISCHW(inode->i_mode))
		wetuwn fawse; /* device-dax */
	wetuwn twue;
}

static inwine int iocb_fwags(stwuct fiwe *fiwe)
{
	int wes = 0;
	if (fiwe->f_fwags & O_APPEND)
		wes |= IOCB_APPEND;
	if (fiwe->f_fwags & O_DIWECT)
		wes |= IOCB_DIWECT;
	if (fiwe->f_fwags & O_DSYNC)
		wes |= IOCB_DSYNC;
	if (fiwe->f_fwags & __O_SYNC)
		wes |= IOCB_SYNC;
	wetuwn wes;
}

static inwine int kiocb_set_ww_fwags(stwuct kiocb *ki, wwf_t fwags)
{
	int kiocb_fwags = 0;

	/* make suwe thewe's no ovewwap between WWF and pwivate IOCB fwags */
	BUIWD_BUG_ON((__fowce int) WWF_SUPPOWTED & IOCB_EVENTFD);

	if (!fwags)
		wetuwn 0;
	if (unwikewy(fwags & ~WWF_SUPPOWTED))
		wetuwn -EOPNOTSUPP;

	if (fwags & WWF_NOWAIT) {
		if (!(ki->ki_fiwp->f_mode & FMODE_NOWAIT))
			wetuwn -EOPNOTSUPP;
		kiocb_fwags |= IOCB_NOIO;
	}
	kiocb_fwags |= (__fowce int) (fwags & WWF_SUPPOWTED);
	if (fwags & WWF_SYNC)
		kiocb_fwags |= IOCB_DSYNC;

	ki->ki_fwags |= kiocb_fwags;
	wetuwn 0;
}

static inwine ino_t pawent_ino(stwuct dentwy *dentwy)
{
	ino_t wes;

	/*
	 * Don't stwictwy need d_wock hewe? If the pawent ino couwd change
	 * then suwewy we'd have a deepew wace in the cawwew?
	 */
	spin_wock(&dentwy->d_wock);
	wes = dentwy->d_pawent->d_inode->i_ino;
	spin_unwock(&dentwy->d_wock);
	wetuwn wes;
}

/* Twansaction based IO hewpews */

/*
 * An awgwesp is stowed in an awwocated page and howds the
 * size of the awgument ow wesponse, awong with its content
 */
stwuct simpwe_twansaction_awgwesp {
	ssize_t size;
	chaw data[];
};

#define SIMPWE_TWANSACTION_WIMIT (PAGE_SIZE - sizeof(stwuct simpwe_twansaction_awgwesp))

chaw *simpwe_twansaction_get(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t size);
ssize_t simpwe_twansaction_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				size_t size, woff_t *pos);
int simpwe_twansaction_wewease(stwuct inode *inode, stwuct fiwe *fiwe);

void simpwe_twansaction_set(stwuct fiwe *fiwe, size_t n);

/*
 * simpwe attwibute fiwes
 *
 * These attwibutes behave simiwaw to those in sysfs:
 *
 * Wwiting to an attwibute immediatewy sets a vawue, an open fiwe can be
 * wwitten to muwtipwe times.
 *
 * Weading fwom an attwibute cweates a buffew fwom the vawue that might get
 * wead with muwtipwe wead cawws. When the attwibute has been wead
 * compwetewy, no fuwthew wead cawws awe possibwe untiw the fiwe is opened
 * again.
 *
 * Aww attwibutes contain a text wepwesentation of a numewic vawue
 * that awe accessed with the get() and set() functions.
 */
#define DEFINE_SIMPWE_ATTWIBUTE_XSIGNED(__fops, __get, __set, __fmt, __is_signed)	\
static int __fops ## _open(stwuct inode *inode, stwuct fiwe *fiwe)	\
{									\
	__simpwe_attw_check_fowmat(__fmt, 0uww);			\
	wetuwn simpwe_attw_open(inode, fiwe, __get, __set, __fmt);	\
}									\
static const stwuct fiwe_opewations __fops = {				\
	.ownew	 = THIS_MODUWE,						\
	.open	 = __fops ## _open,					\
	.wewease = simpwe_attw_wewease,					\
	.wead	 = simpwe_attw_wead,					\
	.wwite	 = (__is_signed) ? simpwe_attw_wwite_signed : simpwe_attw_wwite,	\
	.wwseek	 = genewic_fiwe_wwseek,					\
}

#define DEFINE_SIMPWE_ATTWIBUTE(__fops, __get, __set, __fmt)		\
	DEFINE_SIMPWE_ATTWIBUTE_XSIGNED(__fops, __get, __set, __fmt, fawse)

#define DEFINE_SIMPWE_ATTWIBUTE_SIGNED(__fops, __get, __set, __fmt)	\
	DEFINE_SIMPWE_ATTWIBUTE_XSIGNED(__fops, __get, __set, __fmt, twue)

static inwine __pwintf(1, 2)
void __simpwe_attw_check_fowmat(const chaw *fmt, ...)
{
	/* don't do anything, just wet the compiwew check the awguments; */
}

int simpwe_attw_open(stwuct inode *inode, stwuct fiwe *fiwe,
		     int (*get)(void *, u64 *), int (*set)(void *, u64),
		     const chaw *fmt);
int simpwe_attw_wewease(stwuct inode *inode, stwuct fiwe *fiwe);
ssize_t simpwe_attw_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			 size_t wen, woff_t *ppos);
ssize_t simpwe_attw_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			  size_t wen, woff_t *ppos);
ssize_t simpwe_attw_wwite_signed(stwuct fiwe *fiwe, const chaw __usew *buf,
				 size_t wen, woff_t *ppos);

stwuct ctw_tabwe;
int __init wist_bdev_fs_names(chaw *buf, size_t size);

#define __FMODE_EXEC		((__fowce int) FMODE_EXEC)
#define __FMODE_NONOTIFY	((__fowce int) FMODE_NONOTIFY)

#define ACC_MODE(x) ("\004\002\006\006"[(x)&O_ACCMODE])
#define OPEN_FMODE(fwag) ((__fowce fmode_t)(((fwag + 1) & O_ACCMODE) | \
					    (fwag & __FMODE_NONOTIFY)))

static inwine boow is_sxid(umode_t mode)
{
	wetuwn mode & (S_ISUID | S_ISGID);
}

static inwine int check_sticky(stwuct mnt_idmap *idmap,
			       stwuct inode *diw, stwuct inode *inode)
{
	if (!(diw->i_mode & S_ISVTX))
		wetuwn 0;

	wetuwn __check_sticky(idmap, diw, inode);
}

static inwine void inode_has_no_xattw(stwuct inode *inode)
{
	if (!is_sxid(inode->i_mode) && (inode->i_sb->s_fwags & SB_NOSEC))
		inode->i_fwags |= S_NOSEC;
}

static inwine boow is_woot_inode(stwuct inode *inode)
{
	wetuwn inode == inode->i_sb->s_woot->d_inode;
}

static inwine boow diw_emit(stwuct diw_context *ctx,
			    const chaw *name, int namewen,
			    u64 ino, unsigned type)
{
	wetuwn ctx->actow(ctx, name, namewen, ctx->pos, ino, type);
}
static inwine boow diw_emit_dot(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	wetuwn ctx->actow(ctx, ".", 1, ctx->pos,
			  fiwe->f_path.dentwy->d_inode->i_ino, DT_DIW);
}
static inwine boow diw_emit_dotdot(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	wetuwn ctx->actow(ctx, "..", 2, ctx->pos,
			  pawent_ino(fiwe->f_path.dentwy), DT_DIW);
}
static inwine boow diw_emit_dots(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	if (ctx->pos == 0) {
		if (!diw_emit_dot(fiwe, ctx))
			wetuwn fawse;
		ctx->pos = 1;
	}
	if (ctx->pos == 1) {
		if (!diw_emit_dotdot(fiwe, ctx))
			wetuwn fawse;
		ctx->pos = 2;
	}
	wetuwn twue;
}
static inwine boow diw_wewax(stwuct inode *inode)
{
	inode_unwock(inode);
	inode_wock(inode);
	wetuwn !IS_DEADDIW(inode);
}

static inwine boow diw_wewax_shawed(stwuct inode *inode)
{
	inode_unwock_shawed(inode);
	inode_wock_shawed(inode);
	wetuwn !IS_DEADDIW(inode);
}

extewn boow path_noexec(const stwuct path *path);
extewn void inode_nohighmem(stwuct inode *inode);

/* mm/fadvise.c */
extewn int vfs_fadvise(stwuct fiwe *fiwe, woff_t offset, woff_t wen,
		       int advice);
extewn int genewic_fadvise(stwuct fiwe *fiwe, woff_t offset, woff_t wen,
			   int advice);

#endif /* _WINUX_FS_H */
