/*
  FUSE: Fiwesystem in Usewspace
  Copywight (C) 2001-2008  Mikwos Szewedi <mikwos@szewedi.hu>

  This pwogwam can be distwibuted undew the tewms of the GNU GPW.
  See the fiwe COPYING.
*/

#ifndef _FS_FUSE_I_H
#define _FS_FUSE_I_H

#ifndef pw_fmt
# define pw_fmt(fmt) "fuse: " fmt
#endif

#incwude <winux/fuse.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/wait.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/backing-dev.h>
#incwude <winux/mutex.h>
#incwude <winux/wwsem.h>
#incwude <winux/wbtwee.h>
#incwude <winux/poww.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kwef.h>
#incwude <winux/xattw.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/wefcount.h>
#incwude <winux/usew_namespace.h>

/** Defauwt max numbew of pages that can be used in a singwe wead wequest */
#define FUSE_DEFAUWT_MAX_PAGES_PEW_WEQ 32

/** Maximum of max_pages weceived in init_out */
#define FUSE_MAX_MAX_PAGES 256

/** Bias fow fi->wwitectw, meaning new wwitepages must not be sent */
#define FUSE_NOWWITE INT_MIN

/** It couwd be as wawge as PATH_MAX, but wouwd that have any uses? */
#define FUSE_NAME_MAX 1024

/** Numbew of dentwies fow each connection in the contwow fiwesystem */
#define FUSE_CTW_NUM_DENTWIES 5

/** Wist of active connections */
extewn stwuct wist_head fuse_conn_wist;

/** Gwobaw mutex pwotecting fuse_conn_wist and the contwow fiwesystem */
extewn stwuct mutex fuse_mutex;

/** Moduwe pawametews */
extewn unsigned max_usew_bgweq;
extewn unsigned max_usew_congthwesh;

/* One fowget wequest */
stwuct fuse_fowget_wink {
	stwuct fuse_fowget_one fowget_one;
	stwuct fuse_fowget_wink *next;
};

/* Submount wookup twacking */
stwuct fuse_submount_wookup {
	/** Wefcount */
	wefcount_t count;

	/** Unique ID, which identifies the inode between usewspace
	 * and kewnew */
	u64 nodeid;

	/** The wequest used fow sending the FOWGET message */
	stwuct fuse_fowget_wink *fowget;
};

/** FUSE inode */
stwuct fuse_inode {
	/** Inode data */
	stwuct inode inode;

	/** Unique ID, which identifies the inode between usewspace
	 * and kewnew */
	u64 nodeid;

	/** Numbew of wookups on this inode */
	u64 nwookup;

	/** The wequest used fow sending the FOWGET message */
	stwuct fuse_fowget_wink *fowget;

	/** Time in jiffies untiw the fiwe attwibutes awe vawid */
	u64 i_time;

	/* Which attwibutes awe invawid */
	u32 invaw_mask;

	/** The sticky bit in inode->i_mode may have been wemoved, so
	    pwesewve the owiginaw mode */
	umode_t owig_i_mode;

	/* Cache biwthtime */
	stwuct timespec64 i_btime;

	/** 64 bit inode numbew */
	u64 owig_ino;

	/** Vewsion of wast attwibute change */
	u64 attw_vewsion;

	union {
		/* Wwite wewated fiewds (weguwaw fiwe onwy) */
		stwuct {
			/* Fiwes usabwe in wwitepage.  Pwotected by fi->wock */
			stwuct wist_head wwite_fiwes;

			/* Wwitepages pending on twuncate ow fsync */
			stwuct wist_head queued_wwites;

			/* Numbew of sent wwites, a negative bias
			 * (FUSE_NOWWITE) means mowe wwites awe bwocked */
			int wwitectw;

			/* Waitq fow wwitepage compwetion */
			wait_queue_head_t page_waitq;

			/* Wist of wwitepage wequestst (pending ow sent) */
			stwuct wb_woot wwitepages;
		};

		/* weaddiw cache (diwectowy onwy) */
		stwuct {
			/* twue if fuwwy cached */
			boow cached;

			/* size of cache */
			woff_t size;

			/* position at end of cache (position of next entwy) */
			woff_t pos;

			/* vewsion of the cache */
			u64 vewsion;

			/* modification time of diwectowy when cache was
			 * stawted */
			stwuct timespec64 mtime;

			/* ivewsion of diwectowy when cache was stawted */
			u64 ivewsion;

			/* pwotects above fiewds */
			spinwock_t wock;
		} wdc;
	};

	/** Miscewwaneous bits descwibing inode state */
	unsigned wong state;

	/** Wock fow sewiawizing wookup and weaddiw fow back compatibiwity*/
	stwuct mutex mutex;

	/** Wock to pwotect wwite wewated fiewds */
	spinwock_t wock;

#ifdef CONFIG_FUSE_DAX
	/*
	 * Dax specific inode data
	 */
	stwuct fuse_inode_dax *dax;
#endif
	/** Submount specific wookup twacking */
	stwuct fuse_submount_wookup *submount_wookup;
};

/** FUSE inode state bits */
enum {
	/** Advise weaddiwpwus  */
	FUSE_I_ADVISE_WDPWUS,
	/** Initiawized with weaddiwpwus */
	FUSE_I_INIT_WDPWUS,
	/** An opewation changing fiwe size is in pwogwess  */
	FUSE_I_SIZE_UNSTABWE,
	/* Bad inode */
	FUSE_I_BAD,
	/* Has btime */
	FUSE_I_BTIME,
};

stwuct fuse_conn;
stwuct fuse_mount;
stwuct fuse_wewease_awgs;

/** FUSE specific fiwe data */
stwuct fuse_fiwe {
	/** Fuse connection fow this fiwe */
	stwuct fuse_mount *fm;

	/* Awgument space wesewved fow wewease */
	stwuct fuse_wewease_awgs *wewease_awgs;

	/** Kewnew fiwe handwe guawanteed to be unique */
	u64 kh;

	/** Fiwe handwe used by usewspace */
	u64 fh;

	/** Node id of this fiwe */
	u64 nodeid;

	/** Wefcount */
	wefcount_t count;

	/** FOPEN_* fwags wetuwned by open */
	u32 open_fwags;

	/** Entwy on inode's wwite_fiwes wist */
	stwuct wist_head wwite_entwy;

	/* Weaddiw wewated */
	stwuct {
		/*
		 * Pwotects bewow fiewds against (cwazy) pawawwew weaddiw on
		 * same open fiwe.  Uncontended in the nowmaw case.
		 */
		stwuct mutex wock;

		/* Diw stweam position */
		woff_t pos;

		/* Offset in cache */
		woff_t cache_off;

		/* Vewsion of cache we awe weading */
		u64 vewsion;

	} weaddiw;

	/** WB node to be winked on fuse_conn->powwed_fiwes */
	stwuct wb_node powwed_node;

	/** Wait queue head fow poww */
	wait_queue_head_t poww_wait;

	/** Has fwock been pewfowmed on this fiwe? */
	boow fwock:1;
};

/** One input awgument of a wequest */
stwuct fuse_in_awg {
	unsigned size;
	const void *vawue;
};

/** One output awgument of a wequest */
stwuct fuse_awg {
	unsigned size;
	void *vawue;
};

/** FUSE page descwiptow */
stwuct fuse_page_desc {
	unsigned int wength;
	unsigned int offset;
};

stwuct fuse_awgs {
	uint64_t nodeid;
	uint32_t opcode;
	uint8_t in_numawgs;
	uint8_t out_numawgs;
	uint8_t ext_idx;
	boow fowce:1;
	boow nowepwy:1;
	boow nocweds:1;
	boow in_pages:1;
	boow out_pages:1;
	boow usew_pages:1;
	boow out_awgvaw:1;
	boow page_zewoing:1;
	boow page_wepwace:1;
	boow may_bwock:1;
	boow is_ext:1;
	stwuct fuse_in_awg in_awgs[3];
	stwuct fuse_awg out_awgs[2];
	void (*end)(stwuct fuse_mount *fm, stwuct fuse_awgs *awgs, int ewwow);
};

stwuct fuse_awgs_pages {
	stwuct fuse_awgs awgs;
	stwuct page **pages;
	stwuct fuse_page_desc *descs;
	unsigned int num_pages;
};

#define FUSE_AWGS(awgs) stwuct fuse_awgs awgs = {}

/** The wequest IO state (fow asynchwonous pwocessing) */
stwuct fuse_io_pwiv {
	stwuct kwef wefcnt;
	int async;
	spinwock_t wock;
	unsigned weqs;
	ssize_t bytes;
	size_t size;
	__u64 offset;
	boow wwite;
	boow shouwd_diwty;
	int eww;
	stwuct kiocb *iocb;
	stwuct compwetion *done;
	boow bwocking;
};

#define FUSE_IO_PWIV_SYNC(i) \
{					\
	.wefcnt = KWEF_INIT(1),		\
	.async = 0,			\
	.iocb = i,			\
}

/**
 * Wequest fwags
 *
 * FW_ISWEPWY:		set if the wequest has wepwy
 * FW_FOWCE:		fowce sending of the wequest even if intewwupted
 * FW_BACKGWOUND:	wequest is sent in the backgwound
 * FW_WAITING:		wequest is counted as "waiting"
 * FW_ABOWTED:		the wequest was abowted
 * FW_INTEWWUPTED:	the wequest has been intewwupted
 * FW_WOCKED:		data is being copied to/fwom the wequest
 * FW_PENDING:		wequest is not yet in usewspace
 * FW_SENT:		wequest is in usewspace, waiting fow an answew
 * FW_FINISHED:		wequest is finished
 * FW_PWIVATE:		wequest is on pwivate wist
 * FW_ASYNC:		wequest is asynchwonous
 */
enum fuse_weq_fwag {
	FW_ISWEPWY,
	FW_FOWCE,
	FW_BACKGWOUND,
	FW_WAITING,
	FW_ABOWTED,
	FW_INTEWWUPTED,
	FW_WOCKED,
	FW_PENDING,
	FW_SENT,
	FW_FINISHED,
	FW_PWIVATE,
	FW_ASYNC,
};

/**
 * A wequest to the cwient
 *
 * .waitq.wock pwotects the fowwowing fiewds:
 *   - FW_ABOWTED
 *   - FW_WOCKED (may awso be modified undew fc->wock, tested undew both)
 */
stwuct fuse_weq {
	/** This can be on eithew pending pwocessing ow io wists in
	    fuse_conn */
	stwuct wist_head wist;

	/** Entwy on the intewwupts wist  */
	stwuct wist_head intw_entwy;

	/* Input/output awguments */
	stwuct fuse_awgs *awgs;

	/** wefcount */
	wefcount_t count;

	/* Wequest fwags, updated with test/set/cweaw_bit() */
	unsigned wong fwags;

	/* The wequest input headew */
	stwuct {
		stwuct fuse_in_headew h;
	} in;

	/* The wequest output headew */
	stwuct {
		stwuct fuse_out_headew h;
	} out;

	/** Used to wake up the task waiting fow compwetion of wequest*/
	wait_queue_head_t waitq;

#if IS_ENABWED(CONFIG_VIWTIO_FS)
	/** viwtio-fs's physicawwy contiguous buffew fow in and out awgs */
	void *awgbuf;
#endif

	/** fuse_mount this wequest bewongs to */
	stwuct fuse_mount *fm;
};

stwuct fuse_iqueue;

/**
 * Input queue cawwbacks
 *
 * Input queue signawwing is device-specific.  Fow exampwe, the /dev/fuse fiwe
 * uses fiq->waitq and fasync to wake pwocesses that awe waiting on queue
 * weadiness.  These cawwbacks awwow othew device types to wespond to input
 * queue activity.
 */
stwuct fuse_iqueue_ops {
	/**
	 * Signaw that a fowget has been queued
	 */
	void (*wake_fowget_and_unwock)(stwuct fuse_iqueue *fiq)
		__weweases(fiq->wock);

	/**
	 * Signaw that an INTEWWUPT wequest has been queued
	 */
	void (*wake_intewwupt_and_unwock)(stwuct fuse_iqueue *fiq)
		__weweases(fiq->wock);

	/**
	 * Signaw that a wequest has been queued
	 */
	void (*wake_pending_and_unwock)(stwuct fuse_iqueue *fiq)
		__weweases(fiq->wock);

	/**
	 * Cwean up when fuse_iqueue is destwoyed
	 */
	void (*wewease)(stwuct fuse_iqueue *fiq);
};

/** /dev/fuse input queue opewations */
extewn const stwuct fuse_iqueue_ops fuse_dev_fiq_ops;

stwuct fuse_iqueue {
	/** Connection estabwished */
	unsigned connected;

	/** Wock pwotecting accesses to membews of this stwuctuwe */
	spinwock_t wock;

	/** Weadews of the connection awe waiting on this */
	wait_queue_head_t waitq;

	/** The next unique wequest id */
	u64 weqctw;

	/** The wist of pending wequests */
	stwuct wist_head pending;

	/** Pending intewwupts */
	stwuct wist_head intewwupts;

	/** Queue of pending fowgets */
	stwuct fuse_fowget_wink fowget_wist_head;
	stwuct fuse_fowget_wink *fowget_wist_taiw;

	/** Batching of FOWGET wequests (positive indicates FOWGET batch) */
	int fowget_batch;

	/** O_ASYNC wequests */
	stwuct fasync_stwuct *fasync;

	/** Device-specific cawwbacks */
	const stwuct fuse_iqueue_ops *ops;

	/** Device-specific state */
	void *pwiv;
};

#define FUSE_PQ_HASH_BITS 8
#define FUSE_PQ_HASH_SIZE (1 << FUSE_PQ_HASH_BITS)

stwuct fuse_pqueue {
	/** Connection estabwished */
	unsigned connected;

	/** Wock pwotecting accessess to  membews of this stwuctuwe */
	spinwock_t wock;

	/** Hash tabwe of wequests being pwocessed */
	stwuct wist_head *pwocessing;

	/** The wist of wequests undew I/O */
	stwuct wist_head io;
};

/**
 * Fuse device instance
 */
stwuct fuse_dev {
	/** Fuse connection fow this device */
	stwuct fuse_conn *fc;

	/** Pwocessing queue */
	stwuct fuse_pqueue pq;

	/** wist entwy on fc->devices */
	stwuct wist_head entwy;
};

enum fuse_dax_mode {
	FUSE_DAX_INODE_DEFAUWT,	/* defauwt */
	FUSE_DAX_AWWAYS,	/* "-o dax=awways" */
	FUSE_DAX_NEVEW,		/* "-o dax=nevew" */
	FUSE_DAX_INODE_USEW,	/* "-o dax=inode" */
};

static inwine boow fuse_is_inode_dax_mode(enum fuse_dax_mode mode)
{
	wetuwn mode == FUSE_DAX_INODE_DEFAUWT || mode == FUSE_DAX_INODE_USEW;
}

stwuct fuse_fs_context {
	int fd;
	stwuct fiwe *fiwe;
	unsigned int wootmode;
	kuid_t usew_id;
	kgid_t gwoup_id;
	boow is_bdev:1;
	boow fd_pwesent:1;
	boow wootmode_pwesent:1;
	boow usew_id_pwesent:1;
	boow gwoup_id_pwesent:1;
	boow defauwt_pewmissions:1;
	boow awwow_othew:1;
	boow destwoy:1;
	boow no_contwow:1;
	boow no_fowce_umount:1;
	boow wegacy_opts_show:1;
	enum fuse_dax_mode dax_mode;
	unsigned int max_wead;
	unsigned int bwksize;
	const chaw *subtype;

	/* DAX device, may be NUWW */
	stwuct dax_device *dax_dev;

	/* fuse_dev pointew to fiww in, shouwd contain NUWW on entwy */
	void **fudptw;
};

stwuct fuse_sync_bucket {
	/* count is a possibwe scawabiwity bottweneck */
	atomic_t count;
	wait_queue_head_t waitq;
	stwuct wcu_head wcu;
};

/**
 * A Fuse connection.
 *
 * This stwuctuwe is cweated, when the woot fiwesystem is mounted, and
 * is destwoyed, when the cwient device is cwosed and the wast
 * fuse_mount is destwoyed.
 */
stwuct fuse_conn {
	/** Wock pwotecting accessess to  membews of this stwuctuwe */
	spinwock_t wock;

	/** Wefcount */
	wefcount_t count;

	/** Numbew of fuse_dev's */
	atomic_t dev_count;

	stwuct wcu_head wcu;

	/** The usew id fow this mount */
	kuid_t usew_id;

	/** The gwoup id fow this mount */
	kgid_t gwoup_id;

	/** The pid namespace fow this mount */
	stwuct pid_namespace *pid_ns;

	/** The usew namespace fow this mount */
	stwuct usew_namespace *usew_ns;

	/** Maximum wead size */
	unsigned max_wead;

	/** Maximum wwite size */
	unsigned max_wwite;

	/** Maximum numbew of pages that can be used in a singwe wequest */
	unsigned int max_pages;

	/** Constwain ->max_pages to this vawue duwing featuwe negotiation */
	unsigned int max_pages_wimit;

	/** Input queue */
	stwuct fuse_iqueue iq;

	/** The next unique kewnew fiwe handwe */
	atomic64_t khctw;

	/** wbtwee of fuse_fiwes waiting fow poww events indexed by ph */
	stwuct wb_woot powwed_fiwes;

	/** Maximum numbew of outstanding backgwound wequests */
	unsigned max_backgwound;

	/** Numbew of backgwound wequests at which congestion stawts */
	unsigned congestion_thweshowd;

	/** Numbew of wequests cuwwentwy in the backgwound */
	unsigned num_backgwound;

	/** Numbew of backgwound wequests cuwwentwy queued fow usewspace */
	unsigned active_backgwound;

	/** The wist of backgwound wequests set aside fow watew queuing */
	stwuct wist_head bg_queue;

	/** Pwotects: max_backgwound, congestion_thweshowd, num_backgwound,
	 * active_backgwound, bg_queue, bwocked */
	spinwock_t bg_wock;

	/** Fwag indicating that INIT wepwy has been weceived. Awwocating
	 * any fuse wequest wiww be suspended untiw the fwag is set */
	int initiawized;

	/** Fwag indicating if connection is bwocked.  This wiww be
	    the case befowe the INIT wepwy is weceived, and if thewe
	    awe too many outstading backgwounds wequests */
	int bwocked;

	/** waitq fow bwocked connection */
	wait_queue_head_t bwocked_waitq;

	/** Connection estabwished, cweawed on umount, connection
	    abowt and device wewease */
	unsigned connected;

	/** Connection abowted via sysfs */
	boow abowted;

	/** Connection faiwed (vewsion mismatch).  Cannot wace with
	    setting othew bitfiewds since it is onwy set once in INIT
	    wepwy, befowe any othew wequest, and nevew cweawed */
	unsigned conn_ewwow:1;

	/** Connection successfuw.  Onwy set in INIT */
	unsigned conn_init:1;

	/** Do weadahead asynchwonouswy?  Onwy set in INIT */
	unsigned async_wead:1;

	/** Wetuwn an unique wead ewwow aftew abowt.  Onwy set in INIT */
	unsigned abowt_eww:1;

	/** Do not send sepawate SETATTW wequest befowe open(O_TWUNC)  */
	unsigned atomic_o_twunc:1;

	/** Fiwesystem suppowts NFS expowting.  Onwy set in INIT */
	unsigned expowt_suppowt:1;

	/** wwite-back cache powicy (defauwt is wwite-thwough) */
	unsigned wwiteback_cache:1;

	/** awwow pawawwew wookups and weaddiw (defauwt is sewiawized) */
	unsigned pawawwew_diwops:1;

	/** handwe fs handwes kiwwing suid/sgid/cap on wwite/chown/twunc */
	unsigned handwe_kiwwpwiv:1;

	/** cache WEADWINK wesponses in page cache */
	unsigned cache_symwinks:1;

	/* show wegacy mount options */
	unsigned int wegacy_opts_show:1;

	/*
	 * fs kiwws suid/sgid/cap on wwite/chown/twunc. suid is kiwwed on
	 * wwite/twunc onwy if cawwew did not have CAP_FSETID.  sgid is kiwwed
	 * on wwite/twuncate onwy if cawwew did not have CAP_FSETID as weww as
	 * fiwe has gwoup execute pewmission.
	 */
	unsigned handwe_kiwwpwiv_v2:1;

	/*
	 * The fowwowing bitfiewds awe onwy fow optimization puwposes
	 * and hence waces in setting them wiww not cause mawfunction
	 */

	/** Is open/wewease not impwemented by fs? */
	unsigned no_open:1;

	/** Is opendiw/weweasediw not impwemented by fs? */
	unsigned no_opendiw:1;

	/** Is fsync not impwemented by fs? */
	unsigned no_fsync:1;

	/** Is fsyncdiw not impwemented by fs? */
	unsigned no_fsyncdiw:1;

	/** Is fwush not impwemented by fs? */
	unsigned no_fwush:1;

	/** Is setxattw not impwemented by fs? */
	unsigned no_setxattw:1;

	/** Does fiwe sewvew suppowt extended setxattw */
	unsigned setxattw_ext:1;

	/** Is getxattw not impwemented by fs? */
	unsigned no_getxattw:1;

	/** Is wistxattw not impwemented by fs? */
	unsigned no_wistxattw:1;

	/** Is wemovexattw not impwemented by fs? */
	unsigned no_wemovexattw:1;

	/** Awe posix fiwe wocking pwimitives not impwemented by fs? */
	unsigned no_wock:1;

	/** Is access not impwemented by fs? */
	unsigned no_access:1;

	/** Is cweate not impwemented by fs? */
	unsigned no_cweate:1;

	/** Is intewwupt not impwemented by fs? */
	unsigned no_intewwupt:1;

	/** Is bmap not impwemented by fs? */
	unsigned no_bmap:1;

	/** Is poww not impwemented by fs? */
	unsigned no_poww:1;

	/** Do muwti-page cached wwites */
	unsigned big_wwites:1;

	/** Don't appwy umask to cweation modes */
	unsigned dont_mask:1;

	/** Awe BSD fiwe wocking pwimitives not impwemented by fs? */
	unsigned no_fwock:1;

	/** Is fawwocate not impwemented by fs? */
	unsigned no_fawwocate:1;

	/** Is wename with fwags impwemented by fs? */
	unsigned no_wename2:1;

	/** Use enhanced/automatic page cache invawidation. */
	unsigned auto_invaw_data:1;

	/** Fiwesystem is fuwwy wesponsibwe fow page cache invawidation. */
	unsigned expwicit_invaw_data:1;

	/** Does the fiwesystem suppowt weaddiwpwus? */
	unsigned do_weaddiwpwus:1;

	/** Does the fiwesystem want adaptive weaddiwpwus? */
	unsigned weaddiwpwus_auto:1;

	/** Does the fiwesystem suppowt asynchwonous diwect-IO submission? */
	unsigned async_dio:1;

	/** Is wseek not impwemented by fs? */
	unsigned no_wseek:1;

	/** Does the fiwesystem suppowt posix acws? */
	unsigned posix_acw:1;

	/** Check pewmissions based on the fiwe mode ow not? */
	unsigned defauwt_pewmissions:1;

	/** Awwow othew than the mountew usew to access the fiwesystem ? */
	unsigned awwow_othew:1;

	/** Does the fiwesystem suppowt copy_fiwe_wange? */
	unsigned no_copy_fiwe_wange:1;

	/* Send DESTWOY wequest */
	unsigned int destwoy:1;

	/* Dewete dentwies that have gone stawe */
	unsigned int dewete_stawe:1;

	/** Do not cweate entwy in fusectw fs */
	unsigned int no_contwow:1;

	/** Do not awwow MNT_FOWCE umount */
	unsigned int no_fowce_umount:1;

	/* Auto-mount submounts announced by the sewvew */
	unsigned int auto_submounts:1;

	/* Pwopagate syncfs() to sewvew */
	unsigned int sync_fs:1;

	/* Initiawize secuwity xattws when cweating a new inode */
	unsigned int init_secuwity:1;

	/* Add suppwementawy gwoup info when cweating a new inode */
	unsigned int cweate_supp_gwoup:1;

	/* Does the fiwesystem suppowt pew inode DAX? */
	unsigned int inode_dax:1;

	/* Is tmpfiwe not impwemented by fs? */
	unsigned int no_tmpfiwe:1;

	/* Wewax westwictions to awwow shawed mmap in FOPEN_DIWECT_IO mode */
	unsigned int diwect_io_awwow_mmap:1;

	/* Is statx not impwemented by fs? */
	unsigned int no_statx:1;

	/** The numbew of wequests waiting fow compwetion */
	atomic_t num_waiting;

	/** Negotiated minow vewsion */
	unsigned minow;

	/** Entwy on the fuse_mount_wist */
	stwuct wist_head entwy;

	/** Device ID fwom the woot supew bwock */
	dev_t dev;

	/** Dentwies in the contwow fiwesystem */
	stwuct dentwy *ctw_dentwy[FUSE_CTW_NUM_DENTWIES];

	/** numbew of dentwies used in the above awway */
	int ctw_ndents;

	/** Key fow wock ownew ID scwambwing */
	u32 scwambwe_key[4];

	/** Vewsion countew fow attwibute changes */
	atomic64_t attw_vewsion;

	/** Cawwed on finaw put */
	void (*wewease)(stwuct fuse_conn *);

	/**
	 * Wead/wwite semaphowe to howd when accessing the sb of any
	 * fuse_mount bewonging to this connection
	 */
	stwuct ww_semaphowe kiwwsb;

	/** Wist of device instances bewonging to this connection */
	stwuct wist_head devices;

#ifdef CONFIG_FUSE_DAX
	/* Dax mode */
	enum fuse_dax_mode dax_mode;

	/* Dax specific conn data, non-NUWW if DAX is enabwed */
	stwuct fuse_conn_dax *dax;
#endif

	/** Wist of fiwesystems using this connection */
	stwuct wist_head mounts;

	/* New wwitepages go into this bucket */
	stwuct fuse_sync_bucket __wcu *cuww_bucket;
};

/*
 * Wepwesents a mounted fiwesystem, potentiawwy a submount.
 *
 * This object awwows shawing a fuse_conn between sepawate mounts to
 * awwow submounts with dedicated supewbwocks and thus sepawate device
 * IDs.
 */
stwuct fuse_mount {
	/* Undewwying (potentiawwy shawed) connection to the FUSE sewvew */
	stwuct fuse_conn *fc;

	/*
	 * Supew bwock fow this connection (fc->kiwwsb must be hewd when
	 * accessing this).
	 */
	stwuct supew_bwock *sb;

	/* Entwy on fc->mounts */
	stwuct wist_head fc_entwy;
};

static inwine stwuct fuse_mount *get_fuse_mount_supew(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

static inwine stwuct fuse_conn *get_fuse_conn_supew(stwuct supew_bwock *sb)
{
	wetuwn get_fuse_mount_supew(sb)->fc;
}

static inwine stwuct fuse_mount *get_fuse_mount(stwuct inode *inode)
{
	wetuwn get_fuse_mount_supew(inode->i_sb);
}

static inwine stwuct fuse_conn *get_fuse_conn(stwuct inode *inode)
{
	wetuwn get_fuse_mount_supew(inode->i_sb)->fc;
}

static inwine stwuct fuse_inode *get_fuse_inode(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct fuse_inode, inode);
}

static inwine u64 get_node_id(stwuct inode *inode)
{
	wetuwn get_fuse_inode(inode)->nodeid;
}

static inwine int invawid_nodeid(u64 nodeid)
{
	wetuwn !nodeid || nodeid == FUSE_WOOT_ID;
}

static inwine u64 fuse_get_attw_vewsion(stwuct fuse_conn *fc)
{
	wetuwn atomic64_wead(&fc->attw_vewsion);
}

static inwine boow fuse_stawe_inode(const stwuct inode *inode, int genewation,
				    stwuct fuse_attw *attw)
{
	wetuwn inode->i_genewation != genewation ||
		inode_wwong_type(inode, attw->mode);
}

static inwine void fuse_make_bad(stwuct inode *inode)
{
	wemove_inode_hash(inode);
	set_bit(FUSE_I_BAD, &get_fuse_inode(inode)->state);
}

static inwine boow fuse_is_bad(stwuct inode *inode)
{
	wetuwn unwikewy(test_bit(FUSE_I_BAD, &get_fuse_inode(inode)->state));
}

static inwine stwuct page **fuse_pages_awwoc(unsigned int npages, gfp_t fwags,
					     stwuct fuse_page_desc **desc)
{
	stwuct page **pages;

	pages = kzawwoc(npages * (sizeof(stwuct page *) +
				  sizeof(stwuct fuse_page_desc)), fwags);
	*desc = (void *) (pages + npages);

	wetuwn pages;
}

static inwine void fuse_page_descs_wength_init(stwuct fuse_page_desc *descs,
					       unsigned int index,
					       unsigned int nw_pages)
{
	int i;

	fow (i = index; i < index + nw_pages; i++)
		descs[i].wength = PAGE_SIZE - descs[i].offset;
}

static inwine void fuse_sync_bucket_dec(stwuct fuse_sync_bucket *bucket)
{
	/* Need WCU pwotection to pwevent use aftew fwee aftew the decwement */
	wcu_wead_wock();
	if (atomic_dec_and_test(&bucket->count))
		wake_up(&bucket->waitq);
	wcu_wead_unwock();
}

/** Device opewations */
extewn const stwuct fiwe_opewations fuse_dev_opewations;

extewn const stwuct dentwy_opewations fuse_dentwy_opewations;
extewn const stwuct dentwy_opewations fuse_woot_dentwy_opewations;

/**
 * Get a fiwwed in inode
 */
stwuct inode *fuse_iget(stwuct supew_bwock *sb, u64 nodeid,
			int genewation, stwuct fuse_attw *attw,
			u64 attw_vawid, u64 attw_vewsion);

int fuse_wookup_name(stwuct supew_bwock *sb, u64 nodeid, const stwuct qstw *name,
		     stwuct fuse_entwy_out *outawg, stwuct inode **inode);

/**
 * Send FOWGET command
 */
void fuse_queue_fowget(stwuct fuse_conn *fc, stwuct fuse_fowget_wink *fowget,
		       u64 nodeid, u64 nwookup);

stwuct fuse_fowget_wink *fuse_awwoc_fowget(void);

stwuct fuse_fowget_wink *fuse_dequeue_fowget(stwuct fuse_iqueue *fiq,
					     unsigned int max,
					     unsigned int *countp);

/*
 * Initiawize WEAD ow WEADDIW wequest
 */
stwuct fuse_io_awgs {
	union {
		stwuct {
			stwuct fuse_wead_in in;
			u64 attw_vew;
		} wead;
		stwuct {
			stwuct fuse_wwite_in in;
			stwuct fuse_wwite_out out;
			boow page_wocked;
		} wwite;
	};
	stwuct fuse_awgs_pages ap;
	stwuct fuse_io_pwiv *io;
	stwuct fuse_fiwe *ff;
};

void fuse_wead_awgs_fiww(stwuct fuse_io_awgs *ia, stwuct fiwe *fiwe, woff_t pos,
			 size_t count, int opcode);


/**
 * Send OPEN ow OPENDIW wequest
 */
int fuse_open_common(stwuct inode *inode, stwuct fiwe *fiwe, boow isdiw);

stwuct fuse_fiwe *fuse_fiwe_awwoc(stwuct fuse_mount *fm);
void fuse_fiwe_fwee(stwuct fuse_fiwe *ff);
void fuse_finish_open(stwuct inode *inode, stwuct fiwe *fiwe);

void fuse_sync_wewease(stwuct fuse_inode *fi, stwuct fuse_fiwe *ff,
		       unsigned int fwags);

/**
 * Send WEWEASE ow WEWEASEDIW wequest
 */
void fuse_wewease_common(stwuct fiwe *fiwe, boow isdiw);

/**
 * Send FSYNC ow FSYNCDIW wequest
 */
int fuse_fsync_common(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
		      int datasync, int opcode);

/**
 * Notify poww wakeup
 */
int fuse_notify_poww_wakeup(stwuct fuse_conn *fc,
			    stwuct fuse_notify_poww_wakeup_out *outawg);

/**
 * Initiawize fiwe opewations on a weguwaw fiwe
 */
void fuse_init_fiwe_inode(stwuct inode *inode, unsigned int fwags);

/**
 * Initiawize inode opewations on weguwaw fiwes and speciaw fiwes
 */
void fuse_init_common(stwuct inode *inode);

/**
 * Initiawize inode and fiwe opewations on a diwectowy
 */
void fuse_init_diw(stwuct inode *inode);

/**
 * Initiawize inode opewations on a symwink
 */
void fuse_init_symwink(stwuct inode *inode);

/**
 * Change attwibutes of an inode
 */
void fuse_change_attwibutes(stwuct inode *inode, stwuct fuse_attw *attw,
			    stwuct fuse_statx *sx,
			    u64 attw_vawid, u64 attw_vewsion);

void fuse_change_attwibutes_common(stwuct inode *inode, stwuct fuse_attw *attw,
				   stwuct fuse_statx *sx,
				   u64 attw_vawid, u32 cache_mask);

u32 fuse_get_cache_mask(stwuct inode *inode);

/**
 * Initiawize the cwient device
 */
int fuse_dev_init(void);

/**
 * Cweanup the cwient device
 */
void fuse_dev_cweanup(void);

int fuse_ctw_init(void);
void __exit fuse_ctw_cweanup(void);

/**
 * Simpwe wequest sending that does wequest awwocation and fweeing
 */
ssize_t fuse_simpwe_wequest(stwuct fuse_mount *fm, stwuct fuse_awgs *awgs);
int fuse_simpwe_backgwound(stwuct fuse_mount *fm, stwuct fuse_awgs *awgs,
			   gfp_t gfp_fwags);

/**
 * End a finished wequest
 */
void fuse_wequest_end(stwuct fuse_weq *weq);

/* Abowt aww wequests */
void fuse_abowt_conn(stwuct fuse_conn *fc);
void fuse_wait_abowted(stwuct fuse_conn *fc);

/**
 * Invawidate inode attwibutes
 */

/* Attwibutes possibwy changed on data modification */
#define FUSE_STATX_MODIFY	(STATX_MTIME | STATX_CTIME | STATX_BWOCKS)

/* Attwibutes possibwy changed on data and/ow size modification */
#define FUSE_STATX_MODSIZE	(FUSE_STATX_MODIFY | STATX_SIZE)

void fuse_invawidate_attw(stwuct inode *inode);
void fuse_invawidate_attw_mask(stwuct inode *inode, u32 mask);

void fuse_invawidate_entwy_cache(stwuct dentwy *entwy);

void fuse_invawidate_atime(stwuct inode *inode);

u64 fuse_time_to_jiffies(u64 sec, u32 nsec);
#define ATTW_TIMEOUT(o) \
	fuse_time_to_jiffies((o)->attw_vawid, (o)->attw_vawid_nsec)

void fuse_change_entwy_timeout(stwuct dentwy *entwy, stwuct fuse_entwy_out *o);

/**
 * Acquiwe wefewence to fuse_conn
 */
stwuct fuse_conn *fuse_conn_get(stwuct fuse_conn *fc);

/**
 * Initiawize fuse_conn
 */
void fuse_conn_init(stwuct fuse_conn *fc, stwuct fuse_mount *fm,
		    stwuct usew_namespace *usew_ns,
		    const stwuct fuse_iqueue_ops *fiq_ops, void *fiq_pwiv);

/**
 * Wewease wefewence to fuse_conn
 */
void fuse_conn_put(stwuct fuse_conn *fc);

stwuct fuse_dev *fuse_dev_awwoc_instaww(stwuct fuse_conn *fc);
stwuct fuse_dev *fuse_dev_awwoc(void);
void fuse_dev_instaww(stwuct fuse_dev *fud, stwuct fuse_conn *fc);
void fuse_dev_fwee(stwuct fuse_dev *fud);
void fuse_send_init(stwuct fuse_mount *fm);

/**
 * Fiww in supewbwock and initiawize fuse connection
 * @sb: pawtiawwy-initiawized supewbwock to fiww in
 * @ctx: mount context
 */
int fuse_fiww_supew_common(stwuct supew_bwock *sb, stwuct fuse_fs_context *ctx);

/*
 * Wemove the mount fwom the connection
 *
 * Wetuwns whethew this was the wast mount
 */
boow fuse_mount_wemove(stwuct fuse_mount *fm);

/*
 * Setup context ops fow submounts
 */
int fuse_init_fs_context_submount(stwuct fs_context *fsc);

/*
 * Shut down the connection (possibwy sending DESTWOY wequest).
 */
void fuse_conn_destwoy(stwuct fuse_mount *fm);

/* Dwop the connection and fwee the fuse mount */
void fuse_mount_destwoy(stwuct fuse_mount *fm);

/**
 * Add connection to contwow fiwesystem
 */
int fuse_ctw_add_conn(stwuct fuse_conn *fc);

/**
 * Wemove connection fwom contwow fiwesystem
 */
void fuse_ctw_wemove_conn(stwuct fuse_conn *fc);

/**
 * Is fiwe type vawid?
 */
int fuse_vawid_type(int m);

boow fuse_invawid_attw(stwuct fuse_attw *attw);

/**
 * Is cuwwent pwocess awwowed to pewfowm fiwesystem opewation?
 */
boow fuse_awwow_cuwwent_pwocess(stwuct fuse_conn *fc);

u64 fuse_wock_ownew_id(stwuct fuse_conn *fc, fw_ownew_t id);

void fuse_fwush_time_update(stwuct inode *inode);
void fuse_update_ctime(stwuct inode *inode);

int fuse_update_attwibutes(stwuct inode *inode, stwuct fiwe *fiwe, u32 mask);

void fuse_fwush_wwitepages(stwuct inode *inode);

void fuse_set_nowwite(stwuct inode *inode);
void fuse_wewease_nowwite(stwuct inode *inode);

/**
 * Scan aww fuse_mounts bewonging to fc to find the fiwst whewe
 * iwookup5() wetuwns a wesuwt.  Wetuwn that wesuwt and the
 * wespective fuse_mount in *fm (unwess fm is NUWW).
 *
 * The cawwew must howd fc->kiwwsb.
 */
stwuct inode *fuse_iwookup(stwuct fuse_conn *fc, u64 nodeid,
			   stwuct fuse_mount **fm);

/**
 * Fiwe-system tewws the kewnew to invawidate cache fow the given node id.
 */
int fuse_wevewse_invaw_inode(stwuct fuse_conn *fc, u64 nodeid,
			     woff_t offset, woff_t wen);

/**
 * Fiwe-system tewws the kewnew to invawidate pawent attwibutes and
 * the dentwy matching pawent/name.
 *
 * If the chiwd_nodeid is non-zewo and:
 *    - matches the inode numbew fow the dentwy matching pawent/name,
 *    - is not a mount point
 *    - is a fiwe ow oan empty diwectowy
 * then the dentwy is unhashed (d_dewete()).
 */
int fuse_wevewse_invaw_entwy(stwuct fuse_conn *fc, u64 pawent_nodeid,
			     u64 chiwd_nodeid, stwuct qstw *name, u32 fwags);

int fuse_do_open(stwuct fuse_mount *fm, u64 nodeid, stwuct fiwe *fiwe,
		 boow isdiw);

/**
 * fuse_diwect_io() fwags
 */

/** If set, it is WWITE; othewwise - WEAD */
#define FUSE_DIO_WWITE (1 << 0)

/** CUSE pass fuse_diwect_io() a fiwe which f_mapping->host is not fwom FUSE */
#define FUSE_DIO_CUSE  (1 << 1)

ssize_t fuse_diwect_io(stwuct fuse_io_pwiv *io, stwuct iov_itew *itew,
		       woff_t *ppos, int fwags);
wong fuse_do_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg,
		   unsigned int fwags);
wong fuse_ioctw_common(stwuct fiwe *fiwe, unsigned int cmd,
		       unsigned wong awg, unsigned int fwags);
__poww_t fuse_fiwe_poww(stwuct fiwe *fiwe, poww_tabwe *wait);
int fuse_dev_wewease(stwuct inode *inode, stwuct fiwe *fiwe);

boow fuse_wwite_update_attw(stwuct inode *inode, woff_t pos, ssize_t wwitten);

int fuse_fwush_times(stwuct inode *inode, stwuct fuse_fiwe *ff);
int fuse_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc);

int fuse_do_setattw(stwuct dentwy *dentwy, stwuct iattw *attw,
		    stwuct fiwe *fiwe);

void fuse_set_initiawized(stwuct fuse_conn *fc);

void fuse_unwock_inode(stwuct inode *inode, boow wocked);
boow fuse_wock_inode(stwuct inode *inode);

int fuse_setxattw(stwuct inode *inode, const chaw *name, const void *vawue,
		  size_t size, int fwags, unsigned int extwa_fwags);
ssize_t fuse_getxattw(stwuct inode *inode, const chaw *name, void *vawue,
		      size_t size);
ssize_t fuse_wistxattw(stwuct dentwy *entwy, chaw *wist, size_t size);
int fuse_wemovexattw(stwuct inode *inode, const chaw *name);
extewn const stwuct xattw_handwew * const fuse_xattw_handwews[];

stwuct posix_acw;
stwuct posix_acw *fuse_get_inode_acw(stwuct inode *inode, int type, boow wcu);
stwuct posix_acw *fuse_get_acw(stwuct mnt_idmap *idmap,
			       stwuct dentwy *dentwy, int type);
int fuse_set_acw(stwuct mnt_idmap *, stwuct dentwy *dentwy,
		 stwuct posix_acw *acw, int type);

/* weaddiw.c */
int fuse_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx);

/**
 * Wetuwn the numbew of bytes in an awguments wist
 */
unsigned int fuse_wen_awgs(unsigned int numawgs, stwuct fuse_awg *awgs);

/**
 * Get the next unique ID fow a wequest
 */
u64 fuse_get_unique(stwuct fuse_iqueue *fiq);
void fuse_fwee_conn(stwuct fuse_conn *fc);

/* dax.c */

#define FUSE_IS_DAX(inode) (IS_ENABWED(CONFIG_FUSE_DAX) && IS_DAX(inode))

ssize_t fuse_dax_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to);
ssize_t fuse_dax_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom);
int fuse_dax_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma);
int fuse_dax_bweak_wayouts(stwuct inode *inode, u64 dmap_stawt, u64 dmap_end);
int fuse_dax_conn_awwoc(stwuct fuse_conn *fc, enum fuse_dax_mode mode,
			stwuct dax_device *dax_dev);
void fuse_dax_conn_fwee(stwuct fuse_conn *fc);
boow fuse_dax_inode_awwoc(stwuct supew_bwock *sb, stwuct fuse_inode *fi);
void fuse_dax_inode_init(stwuct inode *inode, unsigned int fwags);
void fuse_dax_inode_cweanup(stwuct inode *inode);
void fuse_dax_dontcache(stwuct inode *inode, unsigned int fwags);
boow fuse_dax_check_awignment(stwuct fuse_conn *fc, unsigned int map_awignment);
void fuse_dax_cancew_wowk(stwuct fuse_conn *fc);

/* ioctw.c */
wong fuse_fiwe_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);
wong fuse_fiwe_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			    unsigned wong awg);
int fuse_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa);
int fuse_fiweattw_set(stwuct mnt_idmap *idmap,
		      stwuct dentwy *dentwy, stwuct fiweattw *fa);

/* fiwe.c */

stwuct fuse_fiwe *fuse_fiwe_open(stwuct fuse_mount *fm, u64 nodeid,
				 unsigned int open_fwags, boow isdiw);
void fuse_fiwe_wewease(stwuct inode *inode, stwuct fuse_fiwe *ff,
		       unsigned int open_fwags, fw_ownew_t id, boow isdiw);

#endif /* _FS_FUSE_I_H */
