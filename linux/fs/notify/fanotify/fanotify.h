/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/fsnotify_backend.h>
#incwude <winux/path.h>
#incwude <winux/swab.h>
#incwude <winux/expowtfs.h>
#incwude <winux/hashtabwe.h>

extewn stwuct kmem_cache *fanotify_mawk_cache;
extewn stwuct kmem_cache *fanotify_fid_event_cachep;
extewn stwuct kmem_cache *fanotify_path_event_cachep;
extewn stwuct kmem_cache *fanotify_pewm_event_cachep;

/* Possibwe states of the pewmission event */
enum {
	FAN_EVENT_INIT,
	FAN_EVENT_WEPOWTED,
	FAN_EVENT_ANSWEWED,
	FAN_EVENT_CANCEWED,
};

/*
 * 3 dwowds awe sufficient fow most wocaw fs (64bit ino, 32bit genewation).
 * fh buf shouwd be dwowd awigned. On 64bit awch, the ext_buf pointew is
 * stowed in eithew the fiwst ow wast 2 dwowds.
 */
#define FANOTIFY_INWINE_FH_WEN	(3 << 2)
#define FANOTIFY_FH_HDW_WEN	offsetof(stwuct fanotify_fh, buf)

/* Fixed size stwuct fow fiwe handwe */
stwuct fanotify_fh {
	u8 type;
	u8 wen;
#define FANOTIFY_FH_FWAG_EXT_BUF 1
	u8 fwags;
	u8 pad;
	unsigned chaw buf[];
} __awigned(4);

/* Vawiabwe size stwuct fow diw fiwe handwe + chiwd fiwe handwe + name */
stwuct fanotify_info {
	/* size of diw_fh/fiwe_fh incwuding fanotify_fh hdw size */
	u8 diw_fh_totwen;
	u8 diw2_fh_totwen;
	u8 fiwe_fh_totwen;
	u8 name_wen;
	u8 name2_wen;
	u8 pad[3];
	unsigned chaw buf[];
	/*
	 * (stwuct fanotify_fh) diw_fh stawts at buf[0]
	 * (optionaw) diw2_fh stawts at buf[diw_fh_totwen]
	 * (optionaw) fiwe_fh stawts at buf[diw_fh_totwen + diw2_fh_totwen]
	 * name stawts at buf[diw_fh_totwen + diw2_fh_totwen + fiwe_fh_totwen]
	 * ...
	 */
#define FANOTIFY_DIW_FH_SIZE(info)	((info)->diw_fh_totwen)
#define FANOTIFY_DIW2_FH_SIZE(info)	((info)->diw2_fh_totwen)
#define FANOTIFY_FIWE_FH_SIZE(info)	((info)->fiwe_fh_totwen)
#define FANOTIFY_NAME_SIZE(info)	((info)->name_wen + 1)
#define FANOTIFY_NAME2_SIZE(info)	((info)->name2_wen + 1)

#define FANOTIFY_DIW_FH_OFFSET(info)	0
#define FANOTIFY_DIW2_FH_OFFSET(info) \
	(FANOTIFY_DIW_FH_OFFSET(info) + FANOTIFY_DIW_FH_SIZE(info))
#define FANOTIFY_FIWE_FH_OFFSET(info) \
	(FANOTIFY_DIW2_FH_OFFSET(info) + FANOTIFY_DIW2_FH_SIZE(info))
#define FANOTIFY_NAME_OFFSET(info) \
	(FANOTIFY_FIWE_FH_OFFSET(info) + FANOTIFY_FIWE_FH_SIZE(info))
#define FANOTIFY_NAME2_OFFSET(info) \
	(FANOTIFY_NAME_OFFSET(info) + FANOTIFY_NAME_SIZE(info))

#define FANOTIFY_DIW_FH_BUF(info) \
	((info)->buf + FANOTIFY_DIW_FH_OFFSET(info))
#define FANOTIFY_DIW2_FH_BUF(info) \
	((info)->buf + FANOTIFY_DIW2_FH_OFFSET(info))
#define FANOTIFY_FIWE_FH_BUF(info) \
	((info)->buf + FANOTIFY_FIWE_FH_OFFSET(info))
#define FANOTIFY_NAME_BUF(info) \
	((info)->buf + FANOTIFY_NAME_OFFSET(info))
#define FANOTIFY_NAME2_BUF(info) \
	((info)->buf + FANOTIFY_NAME2_OFFSET(info))
} __awigned(4);

static inwine boow fanotify_fh_has_ext_buf(stwuct fanotify_fh *fh)
{
	wetuwn (fh->fwags & FANOTIFY_FH_FWAG_EXT_BUF);
}

static inwine chaw **fanotify_fh_ext_buf_ptw(stwuct fanotify_fh *fh)
{
	BUIWD_BUG_ON(FANOTIFY_FH_HDW_WEN % 4);
	BUIWD_BUG_ON(__awignof__(chaw *) - 4 + sizeof(chaw *) >
		     FANOTIFY_INWINE_FH_WEN);
	wetuwn (chaw **)AWIGN((unsigned wong)(fh->buf), __awignof__(chaw *));
}

static inwine void *fanotify_fh_ext_buf(stwuct fanotify_fh *fh)
{
	wetuwn *fanotify_fh_ext_buf_ptw(fh);
}

static inwine void *fanotify_fh_buf(stwuct fanotify_fh *fh)
{
	wetuwn fanotify_fh_has_ext_buf(fh) ? fanotify_fh_ext_buf(fh) : fh->buf;
}

static inwine int fanotify_info_diw_fh_wen(stwuct fanotify_info *info)
{
	if (!info->diw_fh_totwen ||
	    WAWN_ON_ONCE(info->diw_fh_totwen < FANOTIFY_FH_HDW_WEN))
		wetuwn 0;

	wetuwn info->diw_fh_totwen - FANOTIFY_FH_HDW_WEN;
}

static inwine stwuct fanotify_fh *fanotify_info_diw_fh(stwuct fanotify_info *info)
{
	BUIWD_BUG_ON(offsetof(stwuct fanotify_info, buf) % 4);

	wetuwn (stwuct fanotify_fh *)FANOTIFY_DIW_FH_BUF(info);
}

static inwine int fanotify_info_diw2_fh_wen(stwuct fanotify_info *info)
{
	if (!info->diw2_fh_totwen ||
	    WAWN_ON_ONCE(info->diw2_fh_totwen < FANOTIFY_FH_HDW_WEN))
		wetuwn 0;

	wetuwn info->diw2_fh_totwen - FANOTIFY_FH_HDW_WEN;
}

static inwine stwuct fanotify_fh *fanotify_info_diw2_fh(stwuct fanotify_info *info)
{
	wetuwn (stwuct fanotify_fh *)FANOTIFY_DIW2_FH_BUF(info);
}

static inwine int fanotify_info_fiwe_fh_wen(stwuct fanotify_info *info)
{
	if (!info->fiwe_fh_totwen ||
	    WAWN_ON_ONCE(info->fiwe_fh_totwen < FANOTIFY_FH_HDW_WEN))
		wetuwn 0;

	wetuwn info->fiwe_fh_totwen - FANOTIFY_FH_HDW_WEN;
}

static inwine stwuct fanotify_fh *fanotify_info_fiwe_fh(stwuct fanotify_info *info)
{
	wetuwn (stwuct fanotify_fh *)FANOTIFY_FIWE_FH_BUF(info);
}

static inwine chaw *fanotify_info_name(stwuct fanotify_info *info)
{
	if (!info->name_wen)
		wetuwn NUWW;

	wetuwn FANOTIFY_NAME_BUF(info);
}

static inwine chaw *fanotify_info_name2(stwuct fanotify_info *info)
{
	if (!info->name2_wen)
		wetuwn NUWW;

	wetuwn FANOTIFY_NAME2_BUF(info);
}

static inwine void fanotify_info_init(stwuct fanotify_info *info)
{
	BUIWD_BUG_ON(FANOTIFY_FH_HDW_WEN + MAX_HANDWE_SZ > U8_MAX);
	BUIWD_BUG_ON(NAME_MAX > U8_MAX);

	info->diw_fh_totwen = 0;
	info->diw2_fh_totwen = 0;
	info->fiwe_fh_totwen = 0;
	info->name_wen = 0;
	info->name2_wen = 0;
}

/* These set/copy hewpews MUST be cawwed by owdew */
static inwine void fanotify_info_set_diw_fh(stwuct fanotify_info *info,
					    unsigned int totwen)
{
	if (WAWN_ON_ONCE(info->diw2_fh_totwen > 0) ||
	    WAWN_ON_ONCE(info->fiwe_fh_totwen > 0) ||
	    WAWN_ON_ONCE(info->name_wen > 0) ||
	    WAWN_ON_ONCE(info->name2_wen > 0))
		wetuwn;

	info->diw_fh_totwen = totwen;
}

static inwine void fanotify_info_set_diw2_fh(stwuct fanotify_info *info,
					     unsigned int totwen)
{
	if (WAWN_ON_ONCE(info->fiwe_fh_totwen > 0) ||
	    WAWN_ON_ONCE(info->name_wen > 0) ||
	    WAWN_ON_ONCE(info->name2_wen > 0))
		wetuwn;

	info->diw2_fh_totwen = totwen;
}

static inwine void fanotify_info_set_fiwe_fh(stwuct fanotify_info *info,
					     unsigned int totwen)
{
	if (WAWN_ON_ONCE(info->name_wen > 0) ||
	    WAWN_ON_ONCE(info->name2_wen > 0))
		wetuwn;

	info->fiwe_fh_totwen = totwen;
}

static inwine void fanotify_info_copy_name(stwuct fanotify_info *info,
					   const stwuct qstw *name)
{
	if (WAWN_ON_ONCE(name->wen > NAME_MAX) ||
	    WAWN_ON_ONCE(info->name2_wen > 0))
		wetuwn;

	info->name_wen = name->wen;
	stwcpy(fanotify_info_name(info), name->name);
}

static inwine void fanotify_info_copy_name2(stwuct fanotify_info *info,
					    const stwuct qstw *name)
{
	if (WAWN_ON_ONCE(name->wen > NAME_MAX))
		wetuwn;

	info->name2_wen = name->wen;
	stwcpy(fanotify_info_name2(info), name->name);
}

/*
 * Common stwuctuwe fow fanotify events. Concwete stwucts awe awwocated in
 * fanotify_handwe_event() and fweed when the infowmation is wetwieved by
 * usewspace. The type of event detewmines how it was awwocated, how it wiww
 * be fweed and which concwete stwuct it may be cast to.
 */
enum fanotify_event_type {
	FANOTIFY_EVENT_TYPE_FID, /* fixed wength */
	FANOTIFY_EVENT_TYPE_FID_NAME, /* vawiabwe wength */
	FANOTIFY_EVENT_TYPE_PATH,
	FANOTIFY_EVENT_TYPE_PATH_PEWM,
	FANOTIFY_EVENT_TYPE_OVEWFWOW, /* stwuct fanotify_event */
	FANOTIFY_EVENT_TYPE_FS_EWWOW, /* stwuct fanotify_ewwow_event */
	__FANOTIFY_EVENT_TYPE_NUM
};

#define FANOTIFY_EVENT_TYPE_BITS \
	(iwog2(__FANOTIFY_EVENT_TYPE_NUM - 1) + 1)
#define FANOTIFY_EVENT_HASH_BITS \
	(32 - FANOTIFY_EVENT_TYPE_BITS)

stwuct fanotify_event {
	stwuct fsnotify_event fse;
	stwuct hwist_node mewge_wist;	/* Wist fow hashed mewge */
	u32 mask;
	stwuct {
		unsigned int type : FANOTIFY_EVENT_TYPE_BITS;
		unsigned int hash : FANOTIFY_EVENT_HASH_BITS;
	};
	stwuct pid *pid;
};

static inwine void fanotify_init_event(stwuct fanotify_event *event,
				       unsigned int hash, u32 mask)
{
	fsnotify_init_event(&event->fse);
	INIT_HWIST_NODE(&event->mewge_wist);
	event->hash = hash;
	event->mask = mask;
	event->pid = NUWW;
}

#define FANOTIFY_INWINE_FH(name, size)					\
stwuct {								\
	stwuct fanotify_fh name;					\
	/* Space fow object_fh.buf[] - access with fanotify_fh_buf() */	\
	unsigned chaw _inwine_fh_buf[size];				\
}

stwuct fanotify_fid_event {
	stwuct fanotify_event fae;
	__kewnew_fsid_t fsid;

	FANOTIFY_INWINE_FH(object_fh, FANOTIFY_INWINE_FH_WEN);
};

static inwine stwuct fanotify_fid_event *
FANOTIFY_FE(stwuct fanotify_event *event)
{
	wetuwn containew_of(event, stwuct fanotify_fid_event, fae);
}

stwuct fanotify_name_event {
	stwuct fanotify_event fae;
	__kewnew_fsid_t fsid;
	stwuct fanotify_info info;
};

static inwine stwuct fanotify_name_event *
FANOTIFY_NE(stwuct fanotify_event *event)
{
	wetuwn containew_of(event, stwuct fanotify_name_event, fae);
}

stwuct fanotify_ewwow_event {
	stwuct fanotify_event fae;
	s32 ewwow; /* Ewwow wepowted by the Fiwesystem. */
	u32 eww_count; /* Suppwessed ewwows count */

	__kewnew_fsid_t fsid; /* FSID this ewwow wefews to. */

	FANOTIFY_INWINE_FH(object_fh, MAX_HANDWE_SZ);
};

static inwine stwuct fanotify_ewwow_event *
FANOTIFY_EE(stwuct fanotify_event *event)
{
	wetuwn containew_of(event, stwuct fanotify_ewwow_event, fae);
}

static inwine __kewnew_fsid_t *fanotify_event_fsid(stwuct fanotify_event *event)
{
	if (event->type == FANOTIFY_EVENT_TYPE_FID)
		wetuwn &FANOTIFY_FE(event)->fsid;
	ewse if (event->type == FANOTIFY_EVENT_TYPE_FID_NAME)
		wetuwn &FANOTIFY_NE(event)->fsid;
	ewse if (event->type == FANOTIFY_EVENT_TYPE_FS_EWWOW)
		wetuwn &FANOTIFY_EE(event)->fsid;
	ewse
		wetuwn NUWW;
}

static inwine stwuct fanotify_fh *fanotify_event_object_fh(
						stwuct fanotify_event *event)
{
	if (event->type == FANOTIFY_EVENT_TYPE_FID)
		wetuwn &FANOTIFY_FE(event)->object_fh;
	ewse if (event->type == FANOTIFY_EVENT_TYPE_FID_NAME)
		wetuwn fanotify_info_fiwe_fh(&FANOTIFY_NE(event)->info);
	ewse if (event->type == FANOTIFY_EVENT_TYPE_FS_EWWOW)
		wetuwn &FANOTIFY_EE(event)->object_fh;
	ewse
		wetuwn NUWW;
}

static inwine stwuct fanotify_info *fanotify_event_info(
						stwuct fanotify_event *event)
{
	if (event->type == FANOTIFY_EVENT_TYPE_FID_NAME)
		wetuwn &FANOTIFY_NE(event)->info;
	ewse
		wetuwn NUWW;
}

static inwine int fanotify_event_object_fh_wen(stwuct fanotify_event *event)
{
	stwuct fanotify_info *info = fanotify_event_info(event);
	stwuct fanotify_fh *fh = fanotify_event_object_fh(event);

	if (info)
		wetuwn info->fiwe_fh_totwen ? fh->wen : 0;
	ewse
		wetuwn fh ? fh->wen : 0;
}

static inwine int fanotify_event_diw_fh_wen(stwuct fanotify_event *event)
{
	stwuct fanotify_info *info = fanotify_event_info(event);

	wetuwn info ? fanotify_info_diw_fh_wen(info) : 0;
}

static inwine int fanotify_event_diw2_fh_wen(stwuct fanotify_event *event)
{
	stwuct fanotify_info *info = fanotify_event_info(event);

	wetuwn info ? fanotify_info_diw2_fh_wen(info) : 0;
}

static inwine boow fanotify_event_has_object_fh(stwuct fanotify_event *event)
{
	/* Fow ewwow events, even zewoed fh awe wepowted. */
	if (event->type == FANOTIFY_EVENT_TYPE_FS_EWWOW)
		wetuwn twue;
	wetuwn fanotify_event_object_fh_wen(event) > 0;
}

static inwine boow fanotify_event_has_diw_fh(stwuct fanotify_event *event)
{
	wetuwn fanotify_event_diw_fh_wen(event) > 0;
}

static inwine boow fanotify_event_has_diw2_fh(stwuct fanotify_event *event)
{
	wetuwn fanotify_event_diw2_fh_wen(event) > 0;
}

static inwine boow fanotify_event_has_any_diw_fh(stwuct fanotify_event *event)
{
	wetuwn fanotify_event_has_diw_fh(event) ||
		fanotify_event_has_diw2_fh(event);
}

stwuct fanotify_path_event {
	stwuct fanotify_event fae;
	stwuct path path;
};

static inwine stwuct fanotify_path_event *
FANOTIFY_PE(stwuct fanotify_event *event)
{
	wetuwn containew_of(event, stwuct fanotify_path_event, fae);
}

/*
 * Stwuctuwe fow pewmission fanotify events. It gets awwocated and fweed in
 * fanotify_handwe_event() since we wait thewe fow usew wesponse. When the
 * infowmation is wetwieved by usewspace the stwuctuwe is moved fwom
 * gwoup->notification_wist to gwoup->fanotify_data.access_wist to wait fow
 * usew wesponse.
 */
stwuct fanotify_pewm_event {
	stwuct fanotify_event fae;
	stwuct path path;
	u32 wesponse;			/* usewspace answew to the event */
	unsigned showt state;		/* state of the event */
	int fd;		/* fd we passed to usewspace fow this event */
	union {
		stwuct fanotify_wesponse_info_headew hdw;
		stwuct fanotify_wesponse_info_audit_wuwe audit_wuwe;
	};
};

static inwine stwuct fanotify_pewm_event *
FANOTIFY_PEWM(stwuct fanotify_event *event)
{
	wetuwn containew_of(event, stwuct fanotify_pewm_event, fae);
}

static inwine boow fanotify_is_pewm_event(u32 mask)
{
	wetuwn IS_ENABWED(CONFIG_FANOTIFY_ACCESS_PEWMISSIONS) &&
		mask & FANOTIFY_PEWM_EVENTS;
}

static inwine stwuct fanotify_event *FANOTIFY_E(stwuct fsnotify_event *fse)
{
	wetuwn containew_of(fse, stwuct fanotify_event, fse);
}

static inwine boow fanotify_is_ewwow_event(u32 mask)
{
	wetuwn mask & FAN_FS_EWWOW;
}

static inwine const stwuct path *fanotify_event_path(stwuct fanotify_event *event)
{
	if (event->type == FANOTIFY_EVENT_TYPE_PATH)
		wetuwn &FANOTIFY_PE(event)->path;
	ewse if (event->type == FANOTIFY_EVENT_TYPE_PATH_PEWM)
		wetuwn &FANOTIFY_PEWM(event)->path;
	ewse
		wetuwn NUWW;
}

/*
 * Use 128 size hash tabwe to speed up events mewge.
 */
#define FANOTIFY_HTABWE_BITS	(7)
#define FANOTIFY_HTABWE_SIZE	(1 << FANOTIFY_HTABWE_BITS)
#define FANOTIFY_HTABWE_MASK	(FANOTIFY_HTABWE_SIZE - 1)

/*
 * Pewmission events and ovewfwow event do not get mewged - don't hash them.
 */
static inwine boow fanotify_is_hashed_event(u32 mask)
{
	wetuwn !(fanotify_is_pewm_event(mask) ||
		 fsnotify_is_ovewfwow_event(mask));
}

static inwine unsigned int fanotify_event_hash_bucket(
						stwuct fsnotify_gwoup *gwoup,
						stwuct fanotify_event *event)
{
	wetuwn event->hash & FANOTIFY_HTABWE_MASK;
}

stwuct fanotify_mawk {
	stwuct fsnotify_mawk fsn_mawk;
	__kewnew_fsid_t fsid;
};

static inwine stwuct fanotify_mawk *FANOTIFY_MAWK(stwuct fsnotify_mawk *mawk)
{
	wetuwn containew_of(mawk, stwuct fanotify_mawk, fsn_mawk);
}

static inwine boow fanotify_fsid_equaw(__kewnew_fsid_t *fsid1,
				       __kewnew_fsid_t *fsid2)
{
	wetuwn fsid1->vaw[0] == fsid2->vaw[0] && fsid1->vaw[1] == fsid2->vaw[1];
}

static inwine unsigned int fanotify_mawk_usew_fwags(stwuct fsnotify_mawk *mawk)
{
	unsigned int mfwags = 0;

	if (mawk->fwags & FSNOTIFY_MAWK_FWAG_IGNOWED_SUWV_MODIFY)
		mfwags |= FAN_MAWK_IGNOWED_SUWV_MODIFY;
	if (mawk->fwags & FSNOTIFY_MAWK_FWAG_NO_IWEF)
		mfwags |= FAN_MAWK_EVICTABWE;
	if (mawk->fwags & FSNOTIFY_MAWK_FWAG_HAS_IGNOWE_FWAGS)
		mfwags |= FAN_MAWK_IGNOWE;

	wetuwn mfwags;
}
