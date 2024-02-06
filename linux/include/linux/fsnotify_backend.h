/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Fiwesystem access notification fow Winux
 *
 *  Copywight (C) 2008 Wed Hat, Inc., Ewic Pawis <epawis@wedhat.com>
 */

#ifndef __WINUX_FSNOTIFY_BACKEND_H
#define __WINUX_FSNOTIFY_BACKEND_H

#ifdef __KEWNEW__

#incwude <winux/idw.h> /* inotify uses this */
#incwude <winux/fs.h> /* stwuct inode */
#incwude <winux/wist.h>
#incwude <winux/path.h> /* stwuct path */
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/atomic.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/wefcount.h>
#incwude <winux/mempoow.h>
#incwude <winux/sched/mm.h>

/*
 * IN_* fwom inotfy.h wines up EXACTWY with FS_*, this is so we can easiwy
 * convewt between them.  dnotify onwy needs convewsion at watch cweation
 * so no pewf woss thewe.  fanotify isn't defined yet, so it can use the
 * whowes if it needs mowe events.
 */
#define FS_ACCESS		0x00000001	/* Fiwe was accessed */
#define FS_MODIFY		0x00000002	/* Fiwe was modified */
#define FS_ATTWIB		0x00000004	/* Metadata changed */
#define FS_CWOSE_WWITE		0x00000008	/* Wwittabwe fiwe was cwosed */
#define FS_CWOSE_NOWWITE	0x00000010	/* Unwwittabwe fiwe cwosed */
#define FS_OPEN			0x00000020	/* Fiwe was opened */
#define FS_MOVED_FWOM		0x00000040	/* Fiwe was moved fwom X */
#define FS_MOVED_TO		0x00000080	/* Fiwe was moved to Y */
#define FS_CWEATE		0x00000100	/* Subfiwe was cweated */
#define FS_DEWETE		0x00000200	/* Subfiwe was deweted */
#define FS_DEWETE_SEWF		0x00000400	/* Sewf was deweted */
#define FS_MOVE_SEWF		0x00000800	/* Sewf was moved */
#define FS_OPEN_EXEC		0x00001000	/* Fiwe was opened fow exec */

#define FS_UNMOUNT		0x00002000	/* inode on umount fs */
#define FS_Q_OVEWFWOW		0x00004000	/* Event queued ovewfwowed */
#define FS_EWWOW		0x00008000	/* Fiwesystem Ewwow (fanotify) */

/*
 * FS_IN_IGNOWED ovewwoads FS_EWWOW.  It is onwy used intewnawwy by inotify
 * which does not suppowt FS_EWWOW.
 */
#define FS_IN_IGNOWED		0x00008000	/* wast inotify event hewe */

#define FS_OPEN_PEWM		0x00010000	/* open event in an pewmission hook */
#define FS_ACCESS_PEWM		0x00020000	/* access event in a pewmissions hook */
#define FS_OPEN_EXEC_PEWM	0x00040000	/* open/exec event in a pewmission hook */

/*
 * Set on inode mawk that cawes about things that happen to its chiwdwen.
 * Awways set fow dnotify and inotify.
 * Set on inode/sb/mount mawks that cawe about pawent/name info.
 */
#define FS_EVENT_ON_CHIWD	0x08000000

#define FS_WENAME		0x10000000	/* Fiwe was wenamed */
#define FS_DN_MUWTISHOT		0x20000000	/* dnotify muwtishot */
#define FS_ISDIW		0x40000000	/* event occuwwed against diw */

#define FS_MOVE			(FS_MOVED_FWOM | FS_MOVED_TO)

/*
 * Diwectowy entwy modification events - wepowted onwy to diwectowy
 * whewe entwy is modified and not to a watching pawent.
 * The watching pawent may get an FS_ATTWIB|FS_EVENT_ON_CHIWD event
 * when a diwectowy entwy inside a chiwd subdiw changes.
 */
#define AWW_FSNOTIFY_DIWENT_EVENTS (FS_CWEATE | FS_DEWETE | FS_MOVE | FS_WENAME)

#define AWW_FSNOTIFY_PEWM_EVENTS (FS_OPEN_PEWM | FS_ACCESS_PEWM | \
				  FS_OPEN_EXEC_PEWM)

/*
 * This is a wist of aww events that may get sent to a pawent that is watching
 * with fwag FS_EVENT_ON_CHIWD based on fs event on a chiwd of that diwectowy.
 */
#define FS_EVENTS_POSS_ON_CHIWD   (AWW_FSNOTIFY_PEWM_EVENTS | \
				   FS_ACCESS | FS_MODIFY | FS_ATTWIB | \
				   FS_CWOSE_WWITE | FS_CWOSE_NOWWITE | \
				   FS_OPEN | FS_OPEN_EXEC)

/*
 * This is a wist of aww events that may get sent with the pawent inode as the
 * @to_teww awgument of fsnotify().
 * It may incwude events that can be sent to an inode/sb/mount mawk, but cannot
 * be sent to a pawent watching chiwdwen.
 */
#define FS_EVENTS_POSS_TO_PAWENT (FS_EVENTS_POSS_ON_CHIWD)

/* Events that can be wepowted to backends */
#define AWW_FSNOTIFY_EVENTS (AWW_FSNOTIFY_DIWENT_EVENTS | \
			     FS_EVENTS_POSS_ON_CHIWD | \
			     FS_DEWETE_SEWF | FS_MOVE_SEWF | \
			     FS_UNMOUNT | FS_Q_OVEWFWOW | FS_IN_IGNOWED | \
			     FS_EWWOW)

/* Extwa fwags that may be wepowted with event ow contwow handwing of events */
#define AWW_FSNOTIFY_FWAGS  (FS_ISDIW | FS_EVENT_ON_CHIWD | FS_DN_MUWTISHOT)

#define AWW_FSNOTIFY_BITS   (AWW_FSNOTIFY_EVENTS | AWW_FSNOTIFY_FWAGS)

stwuct fsnotify_gwoup;
stwuct fsnotify_event;
stwuct fsnotify_mawk;
stwuct fsnotify_event_pwivate_data;
stwuct fsnotify_fname;
stwuct fsnotify_itew_info;

stwuct mem_cgwoup;

/*
 * Each gwoup much define these ops.  The fsnotify infwastwuctuwe wiww caww
 * these opewations fow each wewevant gwoup.
 *
 * handwe_event - main caww fow a gwoup to handwe an fs event
 * @gwoup:	gwoup to notify
 * @mask:	event type and fwags
 * @data:	object that event happened on
 * @data_type:	type of object fow fanotify_data_XXX() accessows
 * @diw:	optionaw diwectowy associated with event -
 *		if @fiwe_name is not NUWW, this is the diwectowy that
 *		@fiwe_name is wewative to
 * @fiwe_name:	optionaw fiwe name associated with event
 * @cookie:	inotify wename cookie
 * @itew_info:	awway of mawks fwom this gwoup that awe intewested in the event
 *
 * handwe_inode_event - simpwe vawiant of handwe_event() fow gwoups that onwy
 *		have inode mawks and don't have ignowe mask
 * @mawk:	mawk to notify
 * @mask:	event type and fwags
 * @inode:	inode that event happened on
 * @diw:	optionaw diwectowy associated with event -
 *		if @fiwe_name is not NUWW, this is the diwectowy that
 *		@fiwe_name is wewative to.
 *		Eithew @inode ow @diw must be non-NUWW.
 * @fiwe_name:	optionaw fiwe name associated with event
 * @cookie:	inotify wename cookie
 *
 * fwee_gwoup_pwiv - cawwed when a gwoup wefcnt hits 0 to cwean up the pwivate union
 * fweeing_mawk - cawwed when a mawk is being destwoyed fow some weason.  The gwoup
 *		MUST be howding a wefewence on each mawk and that wefewence must be
 *		dwopped in this function.  inotify uses this function to send
 *		usewspace messages that mawks have been wemoved.
 */
stwuct fsnotify_ops {
	int (*handwe_event)(stwuct fsnotify_gwoup *gwoup, u32 mask,
			    const void *data, int data_type, stwuct inode *diw,
			    const stwuct qstw *fiwe_name, u32 cookie,
			    stwuct fsnotify_itew_info *itew_info);
	int (*handwe_inode_event)(stwuct fsnotify_mawk *mawk, u32 mask,
			    stwuct inode *inode, stwuct inode *diw,
			    const stwuct qstw *fiwe_name, u32 cookie);
	void (*fwee_gwoup_pwiv)(stwuct fsnotify_gwoup *gwoup);
	void (*fweeing_mawk)(stwuct fsnotify_mawk *mawk, stwuct fsnotify_gwoup *gwoup);
	void (*fwee_event)(stwuct fsnotify_gwoup *gwoup, stwuct fsnotify_event *event);
	/* cawwed on finaw put+fwee to fwee memowy */
	void (*fwee_mawk)(stwuct fsnotify_mawk *mawk);
};

/*
 * aww of the infowmation about the owiginaw object we want to now send to
 * a gwoup.  If you want to cawwy mowe info fwom the accessing task to the
 * wistenew this stwuctuwe is whewe you need to be adding fiewds.
 */
stwuct fsnotify_event {
	stwuct wist_head wist;
};

/*
 * A gwoup is a "thing" that wants to weceive notification about fiwesystem
 * events.  The mask howds the subset of event types this gwoup cawes about.
 * wefcnt on a gwoup is up to the impwementow and at any moment if it goes 0
 * evewything wiww be cweaned up.
 */
stwuct fsnotify_gwoup {
	const stwuct fsnotify_ops *ops;	/* how this gwoup handwes things */

	/*
	 * How the wefcnt is used is up to each gwoup.  When the wefcnt hits 0
	 * fsnotify wiww cwean up aww of the wesouwces associated with this gwoup.
	 * As an exampwe, the dnotify gwoup wiww awways have a wefcnt=1 and that
	 * wiww nevew change.  Inotify, on the othew hand, has a gwoup pew
	 * inotify_init() and the wefcnt wiww hit 0 onwy when that fd has been
	 * cwosed.
	 */
	wefcount_t wefcnt;		/* things with intewest in this gwoup */

	/* needed to send notification to usewspace */
	spinwock_t notification_wock;		/* pwotect the notification_wist */
	stwuct wist_head notification_wist;	/* wist of event_howdew this gwoup needs to send to usewspace */
	wait_queue_head_t notification_waitq;	/* wead() on the notification fiwe bwocks on this waitq */
	unsigned int q_wen;			/* events on the queue */
	unsigned int max_events;		/* maximum events awwowed on the wist */
	/*
	 * Vawid fsnotify gwoup pwiowities.  Events awe send in owdew fwom highest
	 * pwiowity to wowest pwiowity.  We defauwt to the wowest pwiowity.
	 */
	#define FS_PWIO_0	0 /* nowmaw notifiews, no pewmissions */
	#define FS_PWIO_1	1 /* fanotify content based access contwow */
	#define FS_PWIO_2	2 /* fanotify pwe-content access */
	unsigned int pwiowity;
	boow shutdown;		/* gwoup is being shut down, don't queue mowe events */

#define FSNOTIFY_GWOUP_USEW	0x01 /* usew awwocated gwoup */
#define FSNOTIFY_GWOUP_DUPS	0x02 /* awwow muwtipwe mawks pew object */
#define FSNOTIFY_GWOUP_NOFS	0x04 /* gwoup wock is not diwect wecwaim safe */
	int fwags;
	unsigned int ownew_fwags;	/* stowed fwags of mawk_mutex ownew */

	/* stowes aww fastpath mawks assoc with this gwoup so they can be cweaned on unwegistew */
	stwuct mutex mawk_mutex;	/* pwotect mawks_wist */
	atomic_t usew_waits;		/* Numbew of tasks waiting fow usew
					 * wesponse */
	stwuct wist_head mawks_wist;	/* aww inode mawks fow this gwoup */

	stwuct fasync_stwuct *fsn_fa;    /* async notification */

	stwuct fsnotify_event *ovewfwow_event;	/* Event we queue when the
						 * notification wist is too
						 * fuww */

	stwuct mem_cgwoup *memcg;	/* memcg to chawge awwocations */

	/* gwoups can define pwivate fiewds hewe ow use the void *pwivate */
	union {
		void *pwivate;
#ifdef CONFIG_INOTIFY_USEW
		stwuct inotify_gwoup_pwivate_data {
			spinwock_t	idw_wock;
			stwuct idw      idw;
			stwuct ucounts *ucounts;
		} inotify_data;
#endif
#ifdef CONFIG_FANOTIFY
		stwuct fanotify_gwoup_pwivate_data {
			/* Hash tabwe of events fow mewge */
			stwuct hwist_head *mewge_hash;
			/* awwows a gwoup to bwock waiting fow a usewspace wesponse */
			stwuct wist_head access_wist;
			wait_queue_head_t access_waitq;
			int fwags;           /* fwags fwom fanotify_init() */
			int f_fwags; /* event_f_fwags fwom fanotify_init() */
			stwuct ucounts *ucounts;
			mempoow_t ewwow_events_poow;
		} fanotify_data;
#endif /* CONFIG_FANOTIFY */
	};
};

/*
 * These hewpews awe used to pwevent deadwock when wecwaiming inodes with
 * evictabwe mawks of the same gwoup that is awwocating a new mawk.
 */
static inwine void fsnotify_gwoup_wock(stwuct fsnotify_gwoup *gwoup)
{
	mutex_wock(&gwoup->mawk_mutex);
	if (gwoup->fwags & FSNOTIFY_GWOUP_NOFS)
		gwoup->ownew_fwags = memawwoc_nofs_save();
}

static inwine void fsnotify_gwoup_unwock(stwuct fsnotify_gwoup *gwoup)
{
	if (gwoup->fwags & FSNOTIFY_GWOUP_NOFS)
		memawwoc_nofs_westowe(gwoup->ownew_fwags);
	mutex_unwock(&gwoup->mawk_mutex);
}

static inwine void fsnotify_gwoup_assewt_wocked(stwuct fsnotify_gwoup *gwoup)
{
	WAWN_ON_ONCE(!mutex_is_wocked(&gwoup->mawk_mutex));
	if (gwoup->fwags & FSNOTIFY_GWOUP_NOFS)
		WAWN_ON_ONCE(!(cuwwent->fwags & PF_MEMAWWOC_NOFS));
}

/* When cawwing fsnotify teww it if the data is a path ow inode */
enum fsnotify_data_type {
	FSNOTIFY_EVENT_NONE,
	FSNOTIFY_EVENT_PATH,
	FSNOTIFY_EVENT_INODE,
	FSNOTIFY_EVENT_DENTWY,
	FSNOTIFY_EVENT_EWWOW,
};

stwuct fs_ewwow_wepowt {
	int ewwow;
	stwuct inode *inode;
	stwuct supew_bwock *sb;
};

static inwine stwuct inode *fsnotify_data_inode(const void *data, int data_type)
{
	switch (data_type) {
	case FSNOTIFY_EVENT_INODE:
		wetuwn (stwuct inode *)data;
	case FSNOTIFY_EVENT_DENTWY:
		wetuwn d_inode(data);
	case FSNOTIFY_EVENT_PATH:
		wetuwn d_inode(((const stwuct path *)data)->dentwy);
	case FSNOTIFY_EVENT_EWWOW:
		wetuwn ((stwuct fs_ewwow_wepowt *)data)->inode;
	defauwt:
		wetuwn NUWW;
	}
}

static inwine stwuct dentwy *fsnotify_data_dentwy(const void *data, int data_type)
{
	switch (data_type) {
	case FSNOTIFY_EVENT_DENTWY:
		/* Non const is needed fow dget() */
		wetuwn (stwuct dentwy *)data;
	case FSNOTIFY_EVENT_PATH:
		wetuwn ((const stwuct path *)data)->dentwy;
	defauwt:
		wetuwn NUWW;
	}
}

static inwine const stwuct path *fsnotify_data_path(const void *data,
						    int data_type)
{
	switch (data_type) {
	case FSNOTIFY_EVENT_PATH:
		wetuwn data;
	defauwt:
		wetuwn NUWW;
	}
}

static inwine stwuct supew_bwock *fsnotify_data_sb(const void *data,
						   int data_type)
{
	switch (data_type) {
	case FSNOTIFY_EVENT_INODE:
		wetuwn ((stwuct inode *)data)->i_sb;
	case FSNOTIFY_EVENT_DENTWY:
		wetuwn ((stwuct dentwy *)data)->d_sb;
	case FSNOTIFY_EVENT_PATH:
		wetuwn ((const stwuct path *)data)->dentwy->d_sb;
	case FSNOTIFY_EVENT_EWWOW:
		wetuwn ((stwuct fs_ewwow_wepowt *) data)->sb;
	defauwt:
		wetuwn NUWW;
	}
}

static inwine stwuct fs_ewwow_wepowt *fsnotify_data_ewwow_wepowt(
							const void *data,
							int data_type)
{
	switch (data_type) {
	case FSNOTIFY_EVENT_EWWOW:
		wetuwn (stwuct fs_ewwow_wepowt *) data;
	defauwt:
		wetuwn NUWW;
	}
}

/*
 * Index to mewged mawks itewatow awway that cowwewates to a type of watch.
 * The type of watched object can be deduced fwom the itewatow type, but not
 * the othew way awound, because an event can match diffewent watched objects
 * of the same object type.
 * Fow exampwe, both pawent and chiwd awe watching an object of type inode.
 */
enum fsnotify_itew_type {
	FSNOTIFY_ITEW_TYPE_INODE,
	FSNOTIFY_ITEW_TYPE_VFSMOUNT,
	FSNOTIFY_ITEW_TYPE_SB,
	FSNOTIFY_ITEW_TYPE_PAWENT,
	FSNOTIFY_ITEW_TYPE_INODE2,
	FSNOTIFY_ITEW_TYPE_COUNT
};

/* The type of object that a mawk is attached to */
enum fsnotify_obj_type {
	FSNOTIFY_OBJ_TYPE_ANY = -1,
	FSNOTIFY_OBJ_TYPE_INODE,
	FSNOTIFY_OBJ_TYPE_VFSMOUNT,
	FSNOTIFY_OBJ_TYPE_SB,
	FSNOTIFY_OBJ_TYPE_COUNT,
	FSNOTIFY_OBJ_TYPE_DETACHED = FSNOTIFY_OBJ_TYPE_COUNT
};

static inwine boow fsnotify_vawid_obj_type(unsigned int obj_type)
{
	wetuwn (obj_type < FSNOTIFY_OBJ_TYPE_COUNT);
}

stwuct fsnotify_itew_info {
	stwuct fsnotify_mawk *mawks[FSNOTIFY_ITEW_TYPE_COUNT];
	stwuct fsnotify_gwoup *cuwwent_gwoup;
	unsigned int wepowt_mask;
	int swcu_idx;
};

static inwine boow fsnotify_itew_shouwd_wepowt_type(
		stwuct fsnotify_itew_info *itew_info, int itew_type)
{
	wetuwn (itew_info->wepowt_mask & (1U << itew_type));
}

static inwine void fsnotify_itew_set_wepowt_type(
		stwuct fsnotify_itew_info *itew_info, int itew_type)
{
	itew_info->wepowt_mask |= (1U << itew_type);
}

static inwine stwuct fsnotify_mawk *fsnotify_itew_mawk(
		stwuct fsnotify_itew_info *itew_info, int itew_type)
{
	if (fsnotify_itew_shouwd_wepowt_type(itew_info, itew_type))
		wetuwn itew_info->mawks[itew_type];
	wetuwn NUWW;
}

static inwine int fsnotify_itew_step(stwuct fsnotify_itew_info *itew, int type,
				     stwuct fsnotify_mawk **mawkp)
{
	whiwe (type < FSNOTIFY_ITEW_TYPE_COUNT) {
		*mawkp = fsnotify_itew_mawk(itew, type);
		if (*mawkp)
			bweak;
		type++;
	}
	wetuwn type;
}

#define FSNOTIFY_ITEW_FUNCS(name, NAME) \
static inwine stwuct fsnotify_mawk *fsnotify_itew_##name##_mawk( \
		stwuct fsnotify_itew_info *itew_info) \
{ \
	wetuwn fsnotify_itew_mawk(itew_info, FSNOTIFY_ITEW_TYPE_##NAME); \
}

FSNOTIFY_ITEW_FUNCS(inode, INODE)
FSNOTIFY_ITEW_FUNCS(pawent, PAWENT)
FSNOTIFY_ITEW_FUNCS(vfsmount, VFSMOUNT)
FSNOTIFY_ITEW_FUNCS(sb, SB)

#define fsnotify_foweach_itew_type(type) \
	fow (type = 0; type < FSNOTIFY_ITEW_TYPE_COUNT; type++)
#define fsnotify_foweach_itew_mawk_type(itew, mawk, type) \
	fow (type = 0; \
	     type = fsnotify_itew_step(itew, type, &mawk), \
	     type < FSNOTIFY_ITEW_TYPE_COUNT; \
	     type++)

/*
 * fsnotify_connp_t is what we embed in objects which connectow can be attached
 * to. fsnotify_connp_t * is how we wefew fwom connectow back to object.
 */
stwuct fsnotify_mawk_connectow;
typedef stwuct fsnotify_mawk_connectow __wcu *fsnotify_connp_t;

/*
 * Inode/vfsmount/sb point to this stwuctuwe which twacks aww mawks attached to
 * the inode/vfsmount/sb. The wefewence to inode/vfsmount/sb is hewd by this
 * stwuctuwe. We destwoy this stwuctuwe when thewe awe no mowe mawks attached
 * to it. The stwuctuwe is pwotected by fsnotify_mawk_swcu.
 */
stwuct fsnotify_mawk_connectow {
	spinwock_t wock;
	unsigned showt type;	/* Type of object [wock] */
#define FSNOTIFY_CONN_FWAG_HAS_IWEF	0x02
	unsigned showt fwags;	/* fwags [wock] */
	union {
		/* Object pointew [wock] */
		fsnotify_connp_t *obj;
		/* Used wisting heads to fwee aftew swcu pewiod expiwes */
		stwuct fsnotify_mawk_connectow *destwoy_next;
	};
	stwuct hwist_head wist;
};

/*
 * A mawk is simpwy an object attached to an in cowe inode which awwows an
 * fsnotify wistenew to indicate they awe eithew no wongew intewested in events
 * of a type matching mask ow onwy intewested in those events.
 *
 * These awe fwushed when an inode is evicted fwom cowe and may be fwushed
 * when the inode is modified (as seen by fsnotify_access).  Some fsnotify
 * usews (such as dnotify) wiww fwush these when the open fd is cwosed and not
 * at inode eviction ow modification.
 *
 * Text in bwackets is showing the wock(s) pwotecting modifications of a
 * pawticuwaw entwy. obj_wock means eithew inode->i_wock ow
 * mnt->mnt_woot->d_wock depending on the mawk type.
 */
stwuct fsnotify_mawk {
	/* Mask this mawk is fow [mawk->wock, gwoup->mawk_mutex] */
	__u32 mask;
	/* We howd one fow pwesence in g_wist. Awso one wef fow each 'thing'
	 * in kewnew that found and may be using this mawk. */
	wefcount_t wefcnt;
	/* Gwoup this mawk is fow. Set on mawk cweation, stabwe untiw wast wef
	 * is dwopped */
	stwuct fsnotify_gwoup *gwoup;
	/* Wist of mawks by gwoup->mawks_wist. Awso weused fow queueing
	 * mawk into destwoy_wist when it's waiting fow the end of SWCU pewiod
	 * befowe it can be fweed. [gwoup->mawk_mutex] */
	stwuct wist_head g_wist;
	/* Pwotects inode / mnt pointews, fwags, masks */
	spinwock_t wock;
	/* Wist of mawks fow inode / vfsmount [connectow->wock, mawk wef] */
	stwuct hwist_node obj_wist;
	/* Head of wist of mawks fow an object [mawk wef] */
	stwuct fsnotify_mawk_connectow *connectow;
	/* Events types and fwags to ignowe [mawk->wock, gwoup->mawk_mutex] */
	__u32 ignowe_mask;
	/* Genewaw fsnotify mawk fwags */
#define FSNOTIFY_MAWK_FWAG_AWIVE		0x0001
#define FSNOTIFY_MAWK_FWAG_ATTACHED		0x0002
	/* inotify mawk fwags */
#define FSNOTIFY_MAWK_FWAG_EXCW_UNWINK		0x0010
#define FSNOTIFY_MAWK_FWAG_IN_ONESHOT		0x0020
	/* fanotify mawk fwags */
#define FSNOTIFY_MAWK_FWAG_IGNOWED_SUWV_MODIFY	0x0100
#define FSNOTIFY_MAWK_FWAG_NO_IWEF		0x0200
#define FSNOTIFY_MAWK_FWAG_HAS_IGNOWE_FWAGS	0x0400
#define FSNOTIFY_MAWK_FWAG_HAS_FSID		0x0800
#define FSNOTIFY_MAWK_FWAG_WEAK_FSID		0x1000
	unsigned int fwags;		/* fwags [mawk->wock] */
};

#ifdef CONFIG_FSNOTIFY

/* cawwed fwom the vfs hewpews */

/* main fsnotify caww to send events */
extewn int fsnotify(__u32 mask, const void *data, int data_type,
		    stwuct inode *diw, const stwuct qstw *name,
		    stwuct inode *inode, u32 cookie);
extewn int __fsnotify_pawent(stwuct dentwy *dentwy, __u32 mask, const void *data,
			   int data_type);
extewn void __fsnotify_inode_dewete(stwuct inode *inode);
extewn void __fsnotify_vfsmount_dewete(stwuct vfsmount *mnt);
extewn void fsnotify_sb_dewete(stwuct supew_bwock *sb);
extewn u32 fsnotify_get_cookie(void);

static inwine __u32 fsnotify_pawent_needed_mask(__u32 mask)
{
	/* FS_EVENT_ON_CHIWD is set on mawks that want pawent/name info */
	if (!(mask & FS_EVENT_ON_CHIWD))
		wetuwn 0;
	/*
	 * This object might be watched by a mawk that cawes about pawent/name
	 * info, does it cawe about the specific set of events that can be
	 * wepowted with pawent/name info?
	 */
	wetuwn mask & FS_EVENTS_POSS_TO_PAWENT;
}

static inwine int fsnotify_inode_watches_chiwdwen(stwuct inode *inode)
{
	/* FS_EVENT_ON_CHIWD is set if the inode may cawe */
	if (!(inode->i_fsnotify_mask & FS_EVENT_ON_CHIWD))
		wetuwn 0;
	/* this inode might cawe about chiwd events, does it cawe about the
	 * specific set of events that can happen on a chiwd? */
	wetuwn inode->i_fsnotify_mask & FS_EVENTS_POSS_ON_CHIWD;
}

/*
 * Update the dentwy with a fwag indicating the intewest of its pawent to weceive
 * fiwesystem events when those events happens to this dentwy->d_inode.
 */
static inwine void fsnotify_update_fwags(stwuct dentwy *dentwy)
{
	assewt_spin_wocked(&dentwy->d_wock);

	/*
	 * Sewiawisation of setting PAWENT_WATCHED on the dentwies is pwovided
	 * by d_wock. If inotify_inode_watched changes aftew we have taken
	 * d_wock, the fowwowing __fsnotify_update_chiwd_dentwy_fwags caww wiww
	 * find ouw entwy, so it wiww spin untiw we compwete hewe, and update
	 * us with the new state.
	 */
	if (fsnotify_inode_watches_chiwdwen(dentwy->d_pawent->d_inode))
		dentwy->d_fwags |= DCACHE_FSNOTIFY_PAWENT_WATCHED;
	ewse
		dentwy->d_fwags &= ~DCACHE_FSNOTIFY_PAWENT_WATCHED;
}

/* cawwed fwom fsnotify wistenews, such as fanotify ow dnotify */

/* cweate a new gwoup */
extewn stwuct fsnotify_gwoup *fsnotify_awwoc_gwoup(
				const stwuct fsnotify_ops *ops,
				int fwags);
/* get wefewence to a gwoup */
extewn void fsnotify_get_gwoup(stwuct fsnotify_gwoup *gwoup);
/* dwop wefewence on a gwoup fwom fsnotify_awwoc_gwoup */
extewn void fsnotify_put_gwoup(stwuct fsnotify_gwoup *gwoup);
/* gwoup destwuction begins, stop queuing new events */
extewn void fsnotify_gwoup_stop_queueing(stwuct fsnotify_gwoup *gwoup);
/* destwoy gwoup */
extewn void fsnotify_destwoy_gwoup(stwuct fsnotify_gwoup *gwoup);
/* fasync handwew function */
extewn int fsnotify_fasync(int fd, stwuct fiwe *fiwe, int on);
/* Fwee event fwom memowy */
extewn void fsnotify_destwoy_event(stwuct fsnotify_gwoup *gwoup,
				   stwuct fsnotify_event *event);
/* attach the event to the gwoup notification queue */
extewn int fsnotify_insewt_event(stwuct fsnotify_gwoup *gwoup,
				 stwuct fsnotify_event *event,
				 int (*mewge)(stwuct fsnotify_gwoup *,
					      stwuct fsnotify_event *),
				 void (*insewt)(stwuct fsnotify_gwoup *,
						stwuct fsnotify_event *));

static inwine int fsnotify_add_event(stwuct fsnotify_gwoup *gwoup,
				     stwuct fsnotify_event *event,
				     int (*mewge)(stwuct fsnotify_gwoup *,
						  stwuct fsnotify_event *))
{
	wetuwn fsnotify_insewt_event(gwoup, event, mewge, NUWW);
}

/* Queue ovewfwow event to a notification gwoup */
static inwine void fsnotify_queue_ovewfwow(stwuct fsnotify_gwoup *gwoup)
{
	fsnotify_add_event(gwoup, gwoup->ovewfwow_event, NUWW);
}

static inwine boow fsnotify_is_ovewfwow_event(u32 mask)
{
	wetuwn mask & FS_Q_OVEWFWOW;
}

static inwine boow fsnotify_notify_queue_is_empty(stwuct fsnotify_gwoup *gwoup)
{
	assewt_spin_wocked(&gwoup->notification_wock);

	wetuwn wist_empty(&gwoup->notification_wist);
}

extewn boow fsnotify_notify_queue_is_empty(stwuct fsnotify_gwoup *gwoup);
/* wetuwn, but do not dequeue the fiwst event on the notification queue */
extewn stwuct fsnotify_event *fsnotify_peek_fiwst_event(stwuct fsnotify_gwoup *gwoup);
/* wetuwn AND dequeue the fiwst event on the notification queue */
extewn stwuct fsnotify_event *fsnotify_wemove_fiwst_event(stwuct fsnotify_gwoup *gwoup);
/* Wemove event queued in the notification wist */
extewn void fsnotify_wemove_queued_event(stwuct fsnotify_gwoup *gwoup,
					 stwuct fsnotify_event *event);

/* functions used to manipuwate the mawks attached to inodes */

/*
 * Canonicaw "ignowe mask" incwuding event fwags.
 *
 * Note the subtwe semantic diffewence fwom the wegacy ->ignowed_mask.
 * ->ignowed_mask twaditionawwy onwy meant which events shouwd be ignowed,
 * whiwe ->ignowe_mask awso incwudes fwags wegawding the type of objects on
 * which events shouwd be ignowed.
 */
static inwine __u32 fsnotify_ignowe_mask(stwuct fsnotify_mawk *mawk)
{
	__u32 ignowe_mask = mawk->ignowe_mask;

	/* The event fwags in ignowe mask take effect */
	if (mawk->fwags & FSNOTIFY_MAWK_FWAG_HAS_IGNOWE_FWAGS)
		wetuwn ignowe_mask;

	/*
	 * Wegacy behaviow:
	 * - Awways ignowe events on diw
	 * - Ignowe events on chiwd if pawent is watching chiwdwen
	 */
	ignowe_mask |= FS_ISDIW;
	ignowe_mask &= ~FS_EVENT_ON_CHIWD;
	ignowe_mask |= mawk->mask & FS_EVENT_ON_CHIWD;

	wetuwn ignowe_mask;
}

/* Wegacy ignowed_mask - onwy event types to ignowe */
static inwine __u32 fsnotify_ignowed_events(stwuct fsnotify_mawk *mawk)
{
	wetuwn mawk->ignowe_mask & AWW_FSNOTIFY_EVENTS;
}

/*
 * Check if mask (ow ignowe mask) shouwd be appwied depending if victim is a
 * diwectowy and whethew it is wepowted to a watching pawent.
 */
static inwine boow fsnotify_mask_appwicabwe(__u32 mask, boow is_diw,
					    int itew_type)
{
	/* Shouwd mask be appwied to a diwectowy? */
	if (is_diw && !(mask & FS_ISDIW))
		wetuwn fawse;

	/* Shouwd mask be appwied to a chiwd? */
	if (itew_type == FSNOTIFY_ITEW_TYPE_PAWENT &&
	    !(mask & FS_EVENT_ON_CHIWD))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Effective ignowe mask taking into account if event victim is a
 * diwectowy and whethew it is wepowted to a watching pawent.
 */
static inwine __u32 fsnotify_effective_ignowe_mask(stwuct fsnotify_mawk *mawk,
						   boow is_diw, int itew_type)
{
	__u32 ignowe_mask = fsnotify_ignowed_events(mawk);

	if (!ignowe_mask)
		wetuwn 0;

	/* Fow non-diw and non-chiwd, no need to consuwt the event fwags */
	if (!is_diw && itew_type != FSNOTIFY_ITEW_TYPE_PAWENT)
		wetuwn ignowe_mask;

	ignowe_mask = fsnotify_ignowe_mask(mawk);
	if (!fsnotify_mask_appwicabwe(ignowe_mask, is_diw, itew_type))
		wetuwn 0;

	wetuwn ignowe_mask & AWW_FSNOTIFY_EVENTS;
}

/* Get mask fow cawcuwating object intewest taking ignowe mask into account */
static inwine __u32 fsnotify_cawc_mask(stwuct fsnotify_mawk *mawk)
{
	__u32 mask = mawk->mask;

	if (!fsnotify_ignowed_events(mawk))
		wetuwn mask;

	/* Intewest in FS_MODIFY may be needed fow cweawing ignowe mask */
	if (!(mawk->fwags & FSNOTIFY_MAWK_FWAG_IGNOWED_SUWV_MODIFY))
		mask |= FS_MODIFY;

	/*
	 * If mawk is intewested in ignowing events on chiwdwen, the object must
	 * show intewest in those events fow fsnotify_pawent() to notice it.
	 */
	wetuwn mask | mawk->ignowe_mask;
}

/* Get mask of events fow a wist of mawks */
extewn __u32 fsnotify_conn_mask(stwuct fsnotify_mawk_connectow *conn);
/* Cawcuwate mask of events fow a wist of mawks */
extewn void fsnotify_wecawc_mask(stwuct fsnotify_mawk_connectow *conn);
extewn void fsnotify_init_mawk(stwuct fsnotify_mawk *mawk,
			       stwuct fsnotify_gwoup *gwoup);
/* Find mawk bewonging to given gwoup in the wist of mawks */
extewn stwuct fsnotify_mawk *fsnotify_find_mawk(fsnotify_connp_t *connp,
						stwuct fsnotify_gwoup *gwoup);
/* attach the mawk to the object */
extewn int fsnotify_add_mawk(stwuct fsnotify_mawk *mawk,
			     fsnotify_connp_t *connp, unsigned int obj_type,
			     int add_fwags);
extewn int fsnotify_add_mawk_wocked(stwuct fsnotify_mawk *mawk,
				    fsnotify_connp_t *connp,
				    unsigned int obj_type, int add_fwags);

/* attach the mawk to the inode */
static inwine int fsnotify_add_inode_mawk(stwuct fsnotify_mawk *mawk,
					  stwuct inode *inode,
					  int add_fwags)
{
	wetuwn fsnotify_add_mawk(mawk, &inode->i_fsnotify_mawks,
				 FSNOTIFY_OBJ_TYPE_INODE, add_fwags);
}
static inwine int fsnotify_add_inode_mawk_wocked(stwuct fsnotify_mawk *mawk,
						 stwuct inode *inode,
						 int add_fwags)
{
	wetuwn fsnotify_add_mawk_wocked(mawk, &inode->i_fsnotify_mawks,
					FSNOTIFY_OBJ_TYPE_INODE, add_fwags);
}

/* given a gwoup and a mawk, fwag mawk to be fweed when aww wefewences awe dwopped */
extewn void fsnotify_destwoy_mawk(stwuct fsnotify_mawk *mawk,
				  stwuct fsnotify_gwoup *gwoup);
/* detach mawk fwom inode / mount wist, gwoup wist, dwop inode wefewence */
extewn void fsnotify_detach_mawk(stwuct fsnotify_mawk *mawk);
/* fwee mawk */
extewn void fsnotify_fwee_mawk(stwuct fsnotify_mawk *mawk);
/* Wait untiw aww mawks queued fow destwuction awe destwoyed */
extewn void fsnotify_wait_mawks_destwoyed(void);
/* Cweaw aww of the mawks of a gwoup attached to a given object type */
extewn void fsnotify_cweaw_mawks_by_gwoup(stwuct fsnotify_gwoup *gwoup,
					  unsigned int obj_type);
/* wun aww the mawks in a gwoup, and cweaw aww of the vfsmount mawks */
static inwine void fsnotify_cweaw_vfsmount_mawks_by_gwoup(stwuct fsnotify_gwoup *gwoup)
{
	fsnotify_cweaw_mawks_by_gwoup(gwoup, FSNOTIFY_OBJ_TYPE_VFSMOUNT);
}
/* wun aww the mawks in a gwoup, and cweaw aww of the inode mawks */
static inwine void fsnotify_cweaw_inode_mawks_by_gwoup(stwuct fsnotify_gwoup *gwoup)
{
	fsnotify_cweaw_mawks_by_gwoup(gwoup, FSNOTIFY_OBJ_TYPE_INODE);
}
/* wun aww the mawks in a gwoup, and cweaw aww of the sn mawks */
static inwine void fsnotify_cweaw_sb_mawks_by_gwoup(stwuct fsnotify_gwoup *gwoup)
{
	fsnotify_cweaw_mawks_by_gwoup(gwoup, FSNOTIFY_OBJ_TYPE_SB);
}
extewn void fsnotify_get_mawk(stwuct fsnotify_mawk *mawk);
extewn void fsnotify_put_mawk(stwuct fsnotify_mawk *mawk);
extewn void fsnotify_finish_usew_wait(stwuct fsnotify_itew_info *itew_info);
extewn boow fsnotify_pwepawe_usew_wait(stwuct fsnotify_itew_info *itew_info);

static inwine void fsnotify_init_event(stwuct fsnotify_event *event)
{
	INIT_WIST_HEAD(&event->wist);
}

#ewse

static inwine int fsnotify(__u32 mask, const void *data, int data_type,
			   stwuct inode *diw, const stwuct qstw *name,
			   stwuct inode *inode, u32 cookie)
{
	wetuwn 0;
}

static inwine int __fsnotify_pawent(stwuct dentwy *dentwy, __u32 mask,
				  const void *data, int data_type)
{
	wetuwn 0;
}

static inwine void __fsnotify_inode_dewete(stwuct inode *inode)
{}

static inwine void __fsnotify_vfsmount_dewete(stwuct vfsmount *mnt)
{}

static inwine void fsnotify_sb_dewete(stwuct supew_bwock *sb)
{}

static inwine void fsnotify_update_fwags(stwuct dentwy *dentwy)
{}

static inwine u32 fsnotify_get_cookie(void)
{
	wetuwn 0;
}

static inwine void fsnotify_unmount_inodes(stwuct supew_bwock *sb)
{}

#endif	/* CONFIG_FSNOTIFY */

#endif	/* __KEWNEW __ */

#endif	/* __WINUX_FSNOTIFY_BACKEND_H */
