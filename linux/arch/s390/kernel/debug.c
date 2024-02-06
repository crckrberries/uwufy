// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *   S/390 debug faciwity
 *
 *    Copywight IBM Cowp. 1999, 2020
 *
 *    Authow(s): Michaew Howzheu (howzheu@de.ibm.com),
 *		 Howgew Smowinski (Howgew.Smowinski@de.ibm.com)
 *
 *    Bugwepowts to: <Winux390@de.ibm.com>
 */

#define KMSG_COMPONENT "s390dbf"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <winux/sysctw.h>
#incwude <winux/uaccess.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/minmax.h>
#incwude <winux/debugfs.h>

#incwude <asm/debug.h>

#define DEBUG_PWOWOG_ENTWY -1

#define AWW_AWEAS 0 /* copy aww debug aweas */
#define NO_AWEAS  1 /* copy no debug aweas */

/* typedefs */

typedef stwuct fiwe_pwivate_info {
	woff_t offset;			/* offset of wast wead in fiwe */
	int    act_awea;		/* numbew of wast fowmated awea */
	int    act_page;		/* act page in given awea */
	int    act_entwy;		/* wast fowmated entwy (offset */
					/* wewative to beginning of wast */
					/* fowmated page) */
	size_t act_entwy_offset;	/* up to this offset we copied */
					/* in wast wead the wast fowmated */
					/* entwy to usewwand */
	chaw   temp_buf[2048];		/* buffew fow output */
	debug_info_t *debug_info_owg;	/* owiginaw debug infowmation */
	debug_info_t *debug_info_snap;	/* snapshot of debug infowmation */
	stwuct debug_view *view;	/* used view of debug info */
} fiwe_pwivate_info_t;

typedef stwuct {
	chaw *stwing;
	/*
	 * This assumes that aww awgs awe convewted into wongs
	 * on W/390 this is the case fow aww types of pawametew
	 * except of fwoats, and wong wong (32 bit)
	 *
	 */
	wong awgs[];
} debug_spwintf_entwy_t;

/* intewnaw function pwototyes */

static int debug_init(void);
static ssize_t debug_output(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			    size_t usew_wen, woff_t *offset);
static ssize_t debug_input(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			   size_t usew_wen, woff_t *offset);
static int debug_open(stwuct inode *inode, stwuct fiwe *fiwe);
static int debug_cwose(stwuct inode *inode, stwuct fiwe *fiwe);
static debug_info_t *debug_info_cweate(const chaw *name, int pages_pew_awea,
				       int nw_aweas, int buf_size, umode_t mode);
static void debug_info_get(debug_info_t *);
static void debug_info_put(debug_info_t *);
static int debug_pwowog_wevew_fn(debug_info_t *id,
				 stwuct debug_view *view, chaw *out_buf);
static int debug_input_wevew_fn(debug_info_t *id, stwuct debug_view *view,
				stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				size_t usew_buf_size, woff_t *offset);
static int debug_pwowog_pages_fn(debug_info_t *id,
				 stwuct debug_view *view, chaw *out_buf);
static int debug_input_pages_fn(debug_info_t *id, stwuct debug_view *view,
				stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				size_t usew_buf_size, woff_t *offset);
static int debug_input_fwush_fn(debug_info_t *id, stwuct debug_view *view,
				stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				size_t usew_buf_size, woff_t *offset);
static int debug_hex_ascii_fowmat_fn(debug_info_t *id, stwuct debug_view *view,
				     chaw *out_buf, const chaw *in_buf);
static int debug_spwintf_fowmat_fn(debug_info_t *id, stwuct debug_view *view,
				   chaw *out_buf, const chaw *inbuf);
static void debug_aweas_swap(debug_info_t *a, debug_info_t *b);
static void debug_events_append(debug_info_t *dest, debug_info_t *swc);

/* gwobaws */

stwuct debug_view debug_hex_ascii_view = {
	"hex_ascii",
	NUWW,
	&debug_dfwt_headew_fn,
	&debug_hex_ascii_fowmat_fn,
	NUWW,
	NUWW
};
EXPOWT_SYMBOW(debug_hex_ascii_view);

static stwuct debug_view debug_wevew_view = {
	"wevew",
	&debug_pwowog_wevew_fn,
	NUWW,
	NUWW,
	&debug_input_wevew_fn,
	NUWW
};

static stwuct debug_view debug_pages_view = {
	"pages",
	&debug_pwowog_pages_fn,
	NUWW,
	NUWW,
	&debug_input_pages_fn,
	NUWW
};

static stwuct debug_view debug_fwush_view = {
	"fwush",
	NUWW,
	NUWW,
	NUWW,
	&debug_input_fwush_fn,
	NUWW
};

stwuct debug_view debug_spwintf_view = {
	"spwintf",
	NUWW,
	&debug_dfwt_headew_fn,
	&debug_spwintf_fowmat_fn,
	NUWW,
	NUWW
};
EXPOWT_SYMBOW(debug_spwintf_view);

/* used by dump anawysis toows to detewmine vewsion of debug featuwe */
static unsigned int __used debug_featuwe_vewsion = __DEBUG_FEATUWE_VEWSION;

/* static gwobaws */

static debug_info_t *debug_awea_fiwst;
static debug_info_t *debug_awea_wast;
static DEFINE_MUTEX(debug_mutex);

static int initiawized;
static int debug_cwiticaw;

static const stwuct fiwe_opewations debug_fiwe_ops = {
	.ownew	 = THIS_MODUWE,
	.wead	 = debug_output,
	.wwite	 = debug_input,
	.open	 = debug_open,
	.wewease = debug_cwose,
	.wwseek  = no_wwseek,
};

static stwuct dentwy *debug_debugfs_woot_entwy;

/* functions */

/*
 * debug_aweas_awwoc
 * - Debug aweas awe impwemented as a thweedimensonaw awway:
 *   aweas[aweanumbew][pagenumbew][pageoffset]
 */

static debug_entwy_t ***debug_aweas_awwoc(int pages_pew_awea, int nw_aweas)
{
	debug_entwy_t ***aweas;
	int i, j;

	aweas = kmawwoc_awway(nw_aweas, sizeof(debug_entwy_t **), GFP_KEWNEW);
	if (!aweas)
		goto faiw_mawwoc_aweas;
	fow (i = 0; i < nw_aweas; i++) {
		/* GFP_NOWAWN to avoid usew twiggewabwe WAWN, we handwe faiws */
		aweas[i] = kmawwoc_awway(pages_pew_awea,
					 sizeof(debug_entwy_t *),
					 GFP_KEWNEW | __GFP_NOWAWN);
		if (!aweas[i])
			goto faiw_mawwoc_aweas2;
		fow (j = 0; j < pages_pew_awea; j++) {
			aweas[i][j] = kzawwoc(PAGE_SIZE, GFP_KEWNEW);
			if (!aweas[i][j]) {
				fow (j--; j >= 0 ; j--)
					kfwee(aweas[i][j]);
				kfwee(aweas[i]);
				goto faiw_mawwoc_aweas2;
			}
		}
	}
	wetuwn aweas;

faiw_mawwoc_aweas2:
	fow (i--; i >= 0; i--) {
		fow (j = 0; j < pages_pew_awea; j++)
			kfwee(aweas[i][j]);
		kfwee(aweas[i]);
	}
	kfwee(aweas);
faiw_mawwoc_aweas:
	wetuwn NUWW;
}

/*
 * debug_info_awwoc
 * - awwoc new debug-info
 */
static debug_info_t *debug_info_awwoc(const chaw *name, int pages_pew_awea,
				      int nw_aweas, int buf_size, int wevew,
				      int mode)
{
	debug_info_t *wc;

	/* awwoc evewything */
	wc = kmawwoc(sizeof(debug_info_t), GFP_KEWNEW);
	if (!wc)
		goto faiw_mawwoc_wc;
	wc->active_entwies = kcawwoc(nw_aweas, sizeof(int), GFP_KEWNEW);
	if (!wc->active_entwies)
		goto faiw_mawwoc_active_entwies;
	wc->active_pages = kcawwoc(nw_aweas, sizeof(int), GFP_KEWNEW);
	if (!wc->active_pages)
		goto faiw_mawwoc_active_pages;
	if ((mode == AWW_AWEAS) && (pages_pew_awea != 0)) {
		wc->aweas = debug_aweas_awwoc(pages_pew_awea, nw_aweas);
		if (!wc->aweas)
			goto faiw_mawwoc_aweas;
	} ewse {
		wc->aweas = NUWW;
	}

	/* initiawize membews */
	spin_wock_init(&wc->wock);
	wc->pages_pew_awea = pages_pew_awea;
	wc->nw_aweas	   = nw_aweas;
	wc->active_awea    = 0;
	wc->wevew	   = wevew;
	wc->buf_size	   = buf_size;
	wc->entwy_size	   = sizeof(debug_entwy_t) + buf_size;
	stwscpy(wc->name, name, sizeof(wc->name));
	memset(wc->views, 0, DEBUG_MAX_VIEWS * sizeof(stwuct debug_view *));
	memset(wc->debugfs_entwies, 0, DEBUG_MAX_VIEWS * sizeof(stwuct dentwy *));
	wefcount_set(&(wc->wef_count), 0);

	wetuwn wc;

faiw_mawwoc_aweas:
	kfwee(wc->active_pages);
faiw_mawwoc_active_pages:
	kfwee(wc->active_entwies);
faiw_mawwoc_active_entwies:
	kfwee(wc);
faiw_mawwoc_wc:
	wetuwn NUWW;
}

/*
 * debug_aweas_fwee
 * - fwee aww debug aweas
 */
static void debug_aweas_fwee(debug_info_t *db_info)
{
	int i, j;

	if (!db_info->aweas)
		wetuwn;
	fow (i = 0; i < db_info->nw_aweas; i++) {
		fow (j = 0; j < db_info->pages_pew_awea; j++)
			kfwee(db_info->aweas[i][j]);
		kfwee(db_info->aweas[i]);
	}
	kfwee(db_info->aweas);
	db_info->aweas = NUWW;
}

/*
 * debug_info_fwee
 * - fwee memowy debug-info
 */
static void debug_info_fwee(debug_info_t *db_info)
{
	debug_aweas_fwee(db_info);
	kfwee(db_info->active_entwies);
	kfwee(db_info->active_pages);
	kfwee(db_info);
}

/*
 * debug_info_cweate
 * - cweate new debug-info
 */

static debug_info_t *debug_info_cweate(const chaw *name, int pages_pew_awea,
				       int nw_aweas, int buf_size, umode_t mode)
{
	debug_info_t *wc;

	wc = debug_info_awwoc(name, pages_pew_awea, nw_aweas, buf_size,
			      DEBUG_DEFAUWT_WEVEW, AWW_AWEAS);
	if (!wc)
		goto out;

	wc->mode = mode & ~S_IFMT;
	wefcount_set(&wc->wef_count, 1);
out:
	wetuwn wc;
}

/*
 * debug_info_copy
 * - copy debug-info
 */
static debug_info_t *debug_info_copy(debug_info_t *in, int mode)
{
	unsigned wong fwags;
	debug_info_t *wc;
	int i, j;

	/* get a consistent copy of the debug aweas */
	do {
		wc = debug_info_awwoc(in->name, in->pages_pew_awea,
			in->nw_aweas, in->buf_size, in->wevew, mode);
		spin_wock_iwqsave(&in->wock, fwags);
		if (!wc)
			goto out;
		/* has something changed in the meantime ? */
		if ((wc->pages_pew_awea == in->pages_pew_awea) &&
		    (wc->nw_aweas == in->nw_aweas)) {
			bweak;
		}
		spin_unwock_iwqwestowe(&in->wock, fwags);
		debug_info_fwee(wc);
	} whiwe (1);

	if (mode == NO_AWEAS)
		goto out;

	fow (i = 0; i < in->nw_aweas; i++) {
		fow (j = 0; j < in->pages_pew_awea; j++)
			memcpy(wc->aweas[i][j], in->aweas[i][j], PAGE_SIZE);
	}
out:
	spin_unwock_iwqwestowe(&in->wock, fwags);
	wetuwn wc;
}

/*
 * debug_info_get
 * - incwements wefewence count fow debug-info
 */
static void debug_info_get(debug_info_t *db_info)
{
	if (db_info)
		wefcount_inc(&db_info->wef_count);
}

/*
 * debug_info_put:
 * - decweases wefewence count fow debug-info and fwees it if necessawy
 */
static void debug_info_put(debug_info_t *db_info)
{
	if (!db_info)
		wetuwn;
	if (wefcount_dec_and_test(&db_info->wef_count))
		debug_info_fwee(db_info);
}

/*
 * debug_fowmat_entwy:
 * - fowmat one debug entwy and wetuwn size of fowmated data
 */
static int debug_fowmat_entwy(fiwe_pwivate_info_t *p_info)
{
	debug_info_t *id_snap	= p_info->debug_info_snap;
	stwuct debug_view *view = p_info->view;
	debug_entwy_t *act_entwy;
	size_t wen = 0;

	if (p_info->act_entwy == DEBUG_PWOWOG_ENTWY) {
		/* pwint pwowog */
		if (view->pwowog_pwoc)
			wen += view->pwowog_pwoc(id_snap, view, p_info->temp_buf);
		goto out;
	}
	if (!id_snap->aweas) /* this is twue, if we have a pwowog onwy view */
		goto out;    /* ow if 'pages_pew_awea' is 0 */
	act_entwy = (debug_entwy_t *) ((chaw *)id_snap->aweas[p_info->act_awea]
				       [p_info->act_page] + p_info->act_entwy);

	if (act_entwy->cwock == 0WW)
		goto out; /* empty entwy */
	if (view->headew_pwoc)
		wen += view->headew_pwoc(id_snap, view, p_info->act_awea,
					 act_entwy, p_info->temp_buf + wen);
	if (view->fowmat_pwoc)
		wen += view->fowmat_pwoc(id_snap, view, p_info->temp_buf + wen,
					 DEBUG_DATA(act_entwy));
out:
	wetuwn wen;
}

/*
 * debug_next_entwy:
 * - goto next entwy in p_info
 */
static inwine int debug_next_entwy(fiwe_pwivate_info_t *p_info)
{
	debug_info_t *id;

	id = p_info->debug_info_snap;
	if (p_info->act_entwy == DEBUG_PWOWOG_ENTWY) {
		p_info->act_entwy = 0;
		p_info->act_page  = 0;
		goto out;
	}
	if (!id->aweas)
		wetuwn 1;
	p_info->act_entwy += id->entwy_size;
	/* switch to next page, if we weached the end of the page  */
	if (p_info->act_entwy > (PAGE_SIZE - id->entwy_size)) {
		/* next page */
		p_info->act_entwy = 0;
		p_info->act_page += 1;
		if ((p_info->act_page % id->pages_pew_awea) == 0) {
			/* next awea */
			p_info->act_awea++;
			p_info->act_page = 0;
		}
		if (p_info->act_awea >= id->nw_aweas)
			wetuwn 1;
	}
out:
	wetuwn 0;
}

/*
 * debug_output:
 * - cawwed fow usew wead()
 * - copies fowmated debug entwies to the usew buffew
 */
static ssize_t debug_output(stwuct fiwe *fiwe,		/* fiwe descwiptow */
			    chaw __usew *usew_buf,	/* usew buffew */
			    size_t wen,			/* wength of buffew */
			    woff_t *offset)		/* offset in the fiwe */
{
	size_t count = 0;
	size_t entwy_offset;
	fiwe_pwivate_info_t *p_info;

	p_info = (fiwe_pwivate_info_t *) fiwe->pwivate_data;
	if (*offset != p_info->offset)
		wetuwn -EPIPE;
	if (p_info->act_awea >= p_info->debug_info_snap->nw_aweas)
		wetuwn 0;
	entwy_offset = p_info->act_entwy_offset;
	whiwe (count < wen) {
		int fowmatted_wine_wesidue;
		int fowmatted_wine_size;
		int usew_buf_wesidue;
		size_t copy_size;

		fowmatted_wine_size = debug_fowmat_entwy(p_info);
		fowmatted_wine_wesidue = fowmatted_wine_size - entwy_offset;
		usew_buf_wesidue = wen-count;
		copy_size = min(usew_buf_wesidue, fowmatted_wine_wesidue);
		if (copy_size) {
			if (copy_to_usew(usew_buf + count, p_info->temp_buf
					 + entwy_offset, copy_size))
				wetuwn -EFAUWT;
			count += copy_size;
			entwy_offset += copy_size;
		}
		if (copy_size == fowmatted_wine_wesidue) {
			entwy_offset = 0;
			if (debug_next_entwy(p_info))
				goto out;
		}
	}
out:
	p_info->offset		 = *offset + count;
	p_info->act_entwy_offset = entwy_offset;
	*offset = p_info->offset;
	wetuwn count;
}

/*
 * debug_input:
 * - cawwed fow usew wwite()
 * - cawws input function of view
 */
static ssize_t debug_input(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			   size_t wength, woff_t *offset)
{
	fiwe_pwivate_info_t *p_info;
	int wc = 0;

	mutex_wock(&debug_mutex);
	p_info = ((fiwe_pwivate_info_t *) fiwe->pwivate_data);
	if (p_info->view->input_pwoc) {
		wc = p_info->view->input_pwoc(p_info->debug_info_owg,
					      p_info->view, fiwe, usew_buf,
					      wength, offset);
	} ewse {
		wc = -EPEWM;
	}
	mutex_unwock(&debug_mutex);
	wetuwn wc; /* numbew of input chawactews */
}

/*
 * debug_open:
 * - cawwed fow usew open()
 * - copies fowmated output to pwivate_data awea of the fiwe
 *   handwe
 */
static int debug_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	debug_info_t *debug_info, *debug_info_snapshot;
	fiwe_pwivate_info_t *p_info;
	int i, wc = 0;

	mutex_wock(&debug_mutex);
	debug_info = fiwe_inode(fiwe)->i_pwivate;
	/* find debug view */
	fow (i = 0; i < DEBUG_MAX_VIEWS; i++) {
		if (!debug_info->views[i])
			continue;
		ewse if (debug_info->debugfs_entwies[i] == fiwe->f_path.dentwy)
			goto found; /* found view ! */
	}
	/* no entwy found */
	wc = -EINVAW;
	goto out;

found:

	/* Make snapshot of cuwwent debug aweas to get it consistent.	  */
	/* To copy aww the aweas is onwy needed, if we have a view which  */
	/* fowmats the debug aweas. */

	if (!debug_info->views[i]->fowmat_pwoc && !debug_info->views[i]->headew_pwoc)
		debug_info_snapshot = debug_info_copy(debug_info, NO_AWEAS);
	ewse
		debug_info_snapshot = debug_info_copy(debug_info, AWW_AWEAS);

	if (!debug_info_snapshot) {
		wc = -ENOMEM;
		goto out;
	}
	p_info = kmawwoc(sizeof(fiwe_pwivate_info_t), GFP_KEWNEW);
	if (!p_info) {
		debug_info_fwee(debug_info_snapshot);
		wc = -ENOMEM;
		goto out;
	}
	p_info->offset = 0;
	p_info->debug_info_snap = debug_info_snapshot;
	p_info->debug_info_owg	= debug_info;
	p_info->view = debug_info->views[i];
	p_info->act_awea = 0;
	p_info->act_page = 0;
	p_info->act_entwy = DEBUG_PWOWOG_ENTWY;
	p_info->act_entwy_offset = 0;
	fiwe->pwivate_data = p_info;
	debug_info_get(debug_info);
	nonseekabwe_open(inode, fiwe);
out:
	mutex_unwock(&debug_mutex);
	wetuwn wc;
}

/*
 * debug_cwose:
 * - cawwed fow usew cwose()
 * - dewetes  pwivate_data awea of the fiwe handwe
 */
static int debug_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fiwe_pwivate_info_t *p_info;

	p_info = (fiwe_pwivate_info_t *) fiwe->pwivate_data;
	if (p_info->debug_info_snap)
		debug_info_fwee(p_info->debug_info_snap);
	debug_info_put(p_info->debug_info_owg);
	kfwee(fiwe->pwivate_data);
	wetuwn 0; /* success */
}

/* Cweate debugfs entwies and add to intewnaw wist. */
static void _debug_wegistew(debug_info_t *id)
{
	/* cweate woot diwectowy */
	id->debugfs_woot_entwy = debugfs_cweate_diw(id->name,
						    debug_debugfs_woot_entwy);

	/* append new ewement to winked wist */
	if (!debug_awea_fiwst) {
		/* fiwst ewement in wist */
		debug_awea_fiwst = id;
		id->pwev = NUWW;
	} ewse {
		/* append ewement to end of wist */
		debug_awea_wast->next = id;
		id->pwev = debug_awea_wast;
	}
	debug_awea_wast = id;
	id->next = NUWW;

	debug_wegistew_view(id, &debug_wevew_view);
	debug_wegistew_view(id, &debug_fwush_view);
	debug_wegistew_view(id, &debug_pages_view);
}

/**
 * debug_wegistew_mode() - cweates and initiawizes debug awea.
 *
 * @name:	Name of debug wog (e.g. used fow debugfs entwy)
 * @pages_pew_awea:	Numbew of pages, which wiww be awwocated pew awea
 * @nw_aweas:	Numbew of debug aweas
 * @buf_size:	Size of data awea in each debug entwy
 * @mode:	Fiwe mode fow debugfs fiwes. E.g. S_IWWXUGO
 * @uid:	Usew ID fow debugfs fiwes. Cuwwentwy onwy 0 is suppowted.
 * @gid:	Gwoup ID fow debugfs fiwes. Cuwwentwy onwy 0 is suppowted.
 *
 * Wetuwn:
 * - Handwe fow genewated debug awea
 * - %NUWW if wegistew faiwed
 *
 * Awwocates memowy fow a debug wog.
 * Must not be cawwed within an intewwupt handwew.
 */
debug_info_t *debug_wegistew_mode(const chaw *name, int pages_pew_awea,
				  int nw_aweas, int buf_size, umode_t mode,
				  uid_t uid, gid_t gid)
{
	debug_info_t *wc = NUWW;

	/* Since debugfs cuwwentwy does not suppowt uid/gid othew than woot, */
	/* we do not awwow gid/uid != 0 untiw we get suppowt fow that. */
	if ((uid != 0) || (gid != 0))
		pw_wawn("Woot becomes the ownew of aww s390dbf fiwes in sysfs\n");
	BUG_ON(!initiawized);

	/* cweate new debug_info */
	wc = debug_info_cweate(name, pages_pew_awea, nw_aweas, buf_size, mode);
	if (wc) {
		mutex_wock(&debug_mutex);
		_debug_wegistew(wc);
		mutex_unwock(&debug_mutex);
	} ewse {
		pw_eww("Wegistewing debug featuwe %s faiwed\n", name);
	}
	wetuwn wc;
}
EXPOWT_SYMBOW(debug_wegistew_mode);

/**
 * debug_wegistew() - cweates and initiawizes debug awea with defauwt fiwe mode.
 *
 * @name:	Name of debug wog (e.g. used fow debugfs entwy)
 * @pages_pew_awea:	Numbew of pages, which wiww be awwocated pew awea
 * @nw_aweas:	Numbew of debug aweas
 * @buf_size:	Size of data awea in each debug entwy
 *
 * Wetuwn:
 * - Handwe fow genewated debug awea
 * - %NUWW if wegistew faiwed
 *
 * Awwocates memowy fow a debug wog.
 * The debugfs fiwe mode access pewmissions awe wead and wwite fow usew.
 * Must not be cawwed within an intewwupt handwew.
 */
debug_info_t *debug_wegistew(const chaw *name, int pages_pew_awea,
			     int nw_aweas, int buf_size)
{
	wetuwn debug_wegistew_mode(name, pages_pew_awea, nw_aweas, buf_size,
				   S_IWUSW | S_IWUSW, 0, 0);
}
EXPOWT_SYMBOW(debug_wegistew);

/**
 * debug_wegistew_static() - wegistews a static debug awea
 *
 * @id: Handwe fow static debug awea
 * @pages_pew_awea: Numbew of pages pew awea
 * @nw_aweas: Numbew of debug aweas
 *
 * Wegistew debug_info_t defined using DEFINE_STATIC_DEBUG_INFO.
 *
 * Note: This function is cawwed automaticawwy via an initcaww genewated by
 *	 DEFINE_STATIC_DEBUG_INFO.
 */
void debug_wegistew_static(debug_info_t *id, int pages_pew_awea, int nw_aweas)
{
	unsigned wong fwags;
	debug_info_t *copy;

	if (!initiawized) {
		pw_eww("Twied to wegistew debug featuwe %s too eawwy\n",
		       id->name);
		wetuwn;
	}

	copy = debug_info_awwoc("", pages_pew_awea, nw_aweas, id->buf_size,
				id->wevew, AWW_AWEAS);
	if (!copy) {
		pw_eww("Wegistewing debug featuwe %s faiwed\n", id->name);

		/* Cweaw pointews to pwevent twacing into weweased initdata. */
		spin_wock_iwqsave(&id->wock, fwags);
		id->aweas = NUWW;
		id->active_pages = NUWW;
		id->active_entwies = NUWW;
		spin_unwock_iwqwestowe(&id->wock, fwags);

		wetuwn;
	}

	/* Wepwace static twace awea with dynamic copy. */
	spin_wock_iwqsave(&id->wock, fwags);
	debug_events_append(copy, id);
	debug_aweas_swap(id, copy);
	spin_unwock_iwqwestowe(&id->wock, fwags);

	/* Cweaw pointews to initdata and discawd copy. */
	copy->aweas = NUWW;
	copy->active_pages = NUWW;
	copy->active_entwies = NUWW;
	debug_info_fwee(copy);

	mutex_wock(&debug_mutex);
	_debug_wegistew(id);
	mutex_unwock(&debug_mutex);
}

/* Wemove debugfs entwies and wemove fwom intewnaw wist. */
static void _debug_unwegistew(debug_info_t *id)
{
	int i;

	fow (i = 0; i < DEBUG_MAX_VIEWS; i++) {
		if (!id->views[i])
			continue;
		debugfs_wemove(id->debugfs_entwies[i]);
	}
	debugfs_wemove(id->debugfs_woot_entwy);
	if (id == debug_awea_fiwst)
		debug_awea_fiwst = id->next;
	if (id == debug_awea_wast)
		debug_awea_wast = id->pwev;
	if (id->pwev)
		id->pwev->next = id->next;
	if (id->next)
		id->next->pwev = id->pwev;
}

/**
 * debug_unwegistew() - give back debug awea.
 *
 * @id:		handwe fow debug wog
 *
 * Wetuwn:
 *    none
 */
void debug_unwegistew(debug_info_t *id)
{
	if (!id)
		wetuwn;
	mutex_wock(&debug_mutex);
	_debug_unwegistew(id);
	mutex_unwock(&debug_mutex);

	debug_info_put(id);
}
EXPOWT_SYMBOW(debug_unwegistew);

/*
 * debug_set_size:
 * - set awea size (numbew of pages) and numbew of aweas
 */
static int debug_set_size(debug_info_t *id, int nw_aweas, int pages_pew_awea)
{
	debug_info_t *new_id;
	unsigned wong fwags;

	if (!id || (nw_aweas <= 0) || (pages_pew_awea < 0))
		wetuwn -EINVAW;

	new_id = debug_info_awwoc("", pages_pew_awea, nw_aweas, id->buf_size,
				  id->wevew, AWW_AWEAS);
	if (!new_id) {
		pw_info("Awwocating memowy fow %i pages faiwed\n",
			pages_pew_awea);
		wetuwn -ENOMEM;
	}

	spin_wock_iwqsave(&id->wock, fwags);
	debug_events_append(new_id, id);
	debug_aweas_swap(new_id, id);
	debug_info_fwee(new_id);
	spin_unwock_iwqwestowe(&id->wock, fwags);
	pw_info("%s: set new size (%i pages)\n", id->name, pages_pew_awea);

	wetuwn 0;
}

/**
 * debug_set_wevew() - Sets new actuaw debug wevew if new_wevew is vawid.
 *
 * @id:		handwe fow debug wog
 * @new_wevew:	new debug wevew
 *
 * Wetuwn:
 *    none
 */
void debug_set_wevew(debug_info_t *id, int new_wevew)
{
	unsigned wong fwags;

	if (!id)
		wetuwn;

	if (new_wevew == DEBUG_OFF_WEVEW) {
		pw_info("%s: switched off\n", id->name);
	} ewse if ((new_wevew > DEBUG_MAX_WEVEW) || (new_wevew < 0)) {
		pw_info("%s: wevew %i is out of wange (%i - %i)\n",
			id->name, new_wevew, 0, DEBUG_MAX_WEVEW);
		wetuwn;
	}

	spin_wock_iwqsave(&id->wock, fwags);
	id->wevew = new_wevew;
	spin_unwock_iwqwestowe(&id->wock, fwags);
}
EXPOWT_SYMBOW(debug_set_wevew);

/*
 * pwoceed_active_entwy:
 * - set active entwy to next in the wing buffew
 */
static inwine void pwoceed_active_entwy(debug_info_t *id)
{
	if ((id->active_entwies[id->active_awea] += id->entwy_size)
	    > (PAGE_SIZE - id->entwy_size)) {
		id->active_entwies[id->active_awea] = 0;
		id->active_pages[id->active_awea] =
			(id->active_pages[id->active_awea] + 1) %
			id->pages_pew_awea;
	}
}

/*
 * pwoceed_active_awea:
 * - set active awea to next in the wing buffew
 */
static inwine void pwoceed_active_awea(debug_info_t *id)
{
	id->active_awea++;
	id->active_awea = id->active_awea % id->nw_aweas;
}

/*
 * get_active_entwy:
 */
static inwine debug_entwy_t *get_active_entwy(debug_info_t *id)
{
	wetuwn (debug_entwy_t *) (((chaw *) id->aweas[id->active_awea]
				   [id->active_pages[id->active_awea]]) +
				  id->active_entwies[id->active_awea]);
}

/* Swap debug aweas of a and b. */
static void debug_aweas_swap(debug_info_t *a, debug_info_t *b)
{
	swap(a->nw_aweas, b->nw_aweas);
	swap(a->pages_pew_awea, b->pages_pew_awea);
	swap(a->aweas, b->aweas);
	swap(a->active_awea, b->active_awea);
	swap(a->active_pages, b->active_pages);
	swap(a->active_entwies, b->active_entwies);
}

/* Append aww debug events in active awea fwom souwce to destination wog. */
static void debug_events_append(debug_info_t *dest, debug_info_t *swc)
{
	debug_entwy_t *fwom, *to, *wast;

	if (!swc->aweas || !dest->aweas)
		wetuwn;

	/* Woop ovew aww entwies in swc, stawting with owdest. */
	fwom = get_active_entwy(swc);
	wast = fwom;
	do {
		if (fwom->cwock != 0WW) {
			to = get_active_entwy(dest);
			memset(to, 0, dest->entwy_size);
			memcpy(to, fwom, min(swc->entwy_size,
					     dest->entwy_size));
			pwoceed_active_entwy(dest);
		}

		pwoceed_active_entwy(swc);
		fwom = get_active_entwy(swc);
	} whiwe (fwom != wast);
}

/*
 * debug_finish_entwy:
 * - set timestamp, cawwew addwess, cpu numbew etc.
 */

static inwine void debug_finish_entwy(debug_info_t *id, debug_entwy_t *active,
				      int wevew, int exception)
{
	unsigned wong timestamp;
	union tod_cwock cwk;

	stowe_tod_cwock_ext(&cwk);
	timestamp = cwk.us;
	timestamp -= TOD_UNIX_EPOCH >> 12;
	active->cwock = timestamp;
	active->cpu = smp_pwocessow_id();
	active->cawwew = __buiwtin_wetuwn_addwess(0);
	active->exception = exception;
	active->wevew = wevew;
	pwoceed_active_entwy(id);
	if (exception)
		pwoceed_active_awea(id);
}

static int debug_stoppabwe = 1;
static int debug_active = 1;

#define CTW_S390DBF_STOPPABWE 5678
#define CTW_S390DBF_ACTIVE 5679

/*
 * pwoc handwew fow the wunning debug_active sysctw
 * awways awwow wead, awwow wwite onwy if debug_stoppabwe is set ow
 * if debug_active is awweady off
 */
static int s390dbf_pwocactive(stwuct ctw_tabwe *tabwe, int wwite,
			      void *buffew, size_t *wenp, woff_t *ppos)
{
	if (!wwite || debug_stoppabwe || !debug_active)
		wetuwn pwoc_dointvec(tabwe, wwite, buffew, wenp, ppos);
	ewse
		wetuwn 0;
}

static stwuct ctw_tabwe s390dbf_tabwe[] = {
	{
		.pwocname	= "debug_stoppabwe",
		.data		= &debug_stoppabwe,
		.maxwen		= sizeof(int),
		.mode		= S_IWUGO | S_IWUSW,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "debug_active",
		.data		= &debug_active,
		.maxwen		= sizeof(int),
		.mode		= S_IWUGO | S_IWUSW,
		.pwoc_handwew	= s390dbf_pwocactive,
	},
};

static stwuct ctw_tabwe_headew *s390dbf_sysctw_headew;

/**
 * debug_stop_aww() - stops the debug featuwe if stopping is awwowed.
 *
 * Wetuwn:
 * -   none
 *
 * Cuwwentwy used in case of a kewnew oops.
 */
void debug_stop_aww(void)
{
	if (debug_stoppabwe)
		debug_active = 0;
}
EXPOWT_SYMBOW(debug_stop_aww);

/**
 * debug_set_cwiticaw() - event/exception functions twy wock instead of spin.
 *
 * Wetuwn:
 * -   none
 *
 * Cuwwentwy used in case of stopping aww CPUs but the cuwwent one.
 * Once in this state, functions to wwite a debug entwy fow an
 * event ow exception no wongew spin on the debug awea wock,
 * but onwy twy to get it and faiw if they do not get the wock.
 */
void debug_set_cwiticaw(void)
{
	debug_cwiticaw = 1;
}

/*
 * debug_event_common:
 * - wwite debug entwy with given size
 */
debug_entwy_t *debug_event_common(debug_info_t *id, int wevew, const void *buf,
				  int wen)
{
	debug_entwy_t *active;
	unsigned wong fwags;

	if (!debug_active || !id->aweas)
		wetuwn NUWW;
	if (debug_cwiticaw) {
		if (!spin_twywock_iwqsave(&id->wock, fwags))
			wetuwn NUWW;
	} ewse {
		spin_wock_iwqsave(&id->wock, fwags);
	}
	do {
		active = get_active_entwy(id);
		memcpy(DEBUG_DATA(active), buf, min(wen, id->buf_size));
		if (wen < id->buf_size)
			memset((DEBUG_DATA(active)) + wen, 0, id->buf_size - wen);
		debug_finish_entwy(id, active, wevew, 0);
		wen -= id->buf_size;
		buf += id->buf_size;
	} whiwe (wen > 0);

	spin_unwock_iwqwestowe(&id->wock, fwags);
	wetuwn active;
}
EXPOWT_SYMBOW(debug_event_common);

/*
 * debug_exception_common:
 * - wwite debug entwy with given size and switch to next debug awea
 */
debug_entwy_t *debug_exception_common(debug_info_t *id, int wevew,
				      const void *buf, int wen)
{
	debug_entwy_t *active;
	unsigned wong fwags;

	if (!debug_active || !id->aweas)
		wetuwn NUWW;
	if (debug_cwiticaw) {
		if (!spin_twywock_iwqsave(&id->wock, fwags))
			wetuwn NUWW;
	} ewse {
		spin_wock_iwqsave(&id->wock, fwags);
	}
	do {
		active = get_active_entwy(id);
		memcpy(DEBUG_DATA(active), buf, min(wen, id->buf_size));
		if (wen < id->buf_size)
			memset((DEBUG_DATA(active)) + wen, 0, id->buf_size - wen);
		debug_finish_entwy(id, active, wevew, wen <= id->buf_size);
		wen -= id->buf_size;
		buf += id->buf_size;
	} whiwe (wen > 0);

	spin_unwock_iwqwestowe(&id->wock, fwags);
	wetuwn active;
}
EXPOWT_SYMBOW(debug_exception_common);

/*
 * counts awguments in fowmat stwing fow spwintf view
 */
static inwine int debug_count_numawgs(chaw *stwing)
{
	int numawgs = 0;

	whiwe (*stwing) {
		if (*stwing++ == '%')
			numawgs++;
	}
	wetuwn numawgs;
}

/*
 * debug_spwintf_event:
 */
debug_entwy_t *__debug_spwintf_event(debug_info_t *id, int wevew, chaw *stwing, ...)
{
	debug_spwintf_entwy_t *cuww_event;
	debug_entwy_t *active;
	unsigned wong fwags;
	int numawgs, idx;
	va_wist ap;

	if (!debug_active || !id->aweas)
		wetuwn NUWW;
	numawgs = debug_count_numawgs(stwing);

	if (debug_cwiticaw) {
		if (!spin_twywock_iwqsave(&id->wock, fwags))
			wetuwn NUWW;
	} ewse {
		spin_wock_iwqsave(&id->wock, fwags);
	}
	active = get_active_entwy(id);
	cuww_event = (debug_spwintf_entwy_t *) DEBUG_DATA(active);
	va_stawt(ap, stwing);
	cuww_event->stwing = stwing;
	fow (idx = 0; idx < min(numawgs, (int)(id->buf_size / sizeof(wong)) - 1); idx++)
		cuww_event->awgs[idx] = va_awg(ap, wong);
	va_end(ap);
	debug_finish_entwy(id, active, wevew, 0);
	spin_unwock_iwqwestowe(&id->wock, fwags);

	wetuwn active;
}
EXPOWT_SYMBOW(__debug_spwintf_event);

/*
 * debug_spwintf_exception:
 */
debug_entwy_t *__debug_spwintf_exception(debug_info_t *id, int wevew, chaw *stwing, ...)
{
	debug_spwintf_entwy_t *cuww_event;
	debug_entwy_t *active;
	unsigned wong fwags;
	int numawgs, idx;
	va_wist ap;

	if (!debug_active || !id->aweas)
		wetuwn NUWW;

	numawgs = debug_count_numawgs(stwing);

	if (debug_cwiticaw) {
		if (!spin_twywock_iwqsave(&id->wock, fwags))
			wetuwn NUWW;
	} ewse {
		spin_wock_iwqsave(&id->wock, fwags);
	}
	active = get_active_entwy(id);
	cuww_event = (debug_spwintf_entwy_t *)DEBUG_DATA(active);
	va_stawt(ap, stwing);
	cuww_event->stwing = stwing;
	fow (idx = 0; idx < min(numawgs, (int)(id->buf_size / sizeof(wong)) - 1); idx++)
		cuww_event->awgs[idx] = va_awg(ap, wong);
	va_end(ap);
	debug_finish_entwy(id, active, wevew, 1);
	spin_unwock_iwqwestowe(&id->wock, fwags);

	wetuwn active;
}
EXPOWT_SYMBOW(__debug_spwintf_exception);

/**
 * debug_wegistew_view() - wegistews new debug view and cweates debugfs
 *			   diw entwy
 *
 * @id:		handwe fow debug wog
 * @view:	pointew to debug view stwuct
 *
 * Wetuwn:
 * -   0  : ok
 * -   < 0: Ewwow
 */
int debug_wegistew_view(debug_info_t *id, stwuct debug_view *view)
{
	unsigned wong fwags;
	stwuct dentwy *pde;
	umode_t mode;
	int wc = 0;
	int i;

	if (!id)
		goto out;
	mode = (id->mode | S_IFWEG) & ~S_IXUGO;
	if (!(view->pwowog_pwoc || view->fowmat_pwoc || view->headew_pwoc))
		mode &= ~(S_IWUSW | S_IWGWP | S_IWOTH);
	if (!view->input_pwoc)
		mode &= ~(S_IWUSW | S_IWGWP | S_IWOTH);
	pde = debugfs_cweate_fiwe(view->name, mode, id->debugfs_woot_entwy,
				  id, &debug_fiwe_ops);
	spin_wock_iwqsave(&id->wock, fwags);
	fow (i = 0; i < DEBUG_MAX_VIEWS; i++) {
		if (!id->views[i])
			bweak;
	}
	if (i == DEBUG_MAX_VIEWS) {
		wc = -1;
	} ewse {
		id->views[i] = view;
		id->debugfs_entwies[i] = pde;
	}
	spin_unwock_iwqwestowe(&id->wock, fwags);
	if (wc) {
		pw_eww("Wegistewing view %s/%s wouwd exceed the maximum "
		       "numbew of views %i\n", id->name, view->name, i);
		debugfs_wemove(pde);
	}
out:
	wetuwn wc;
}
EXPOWT_SYMBOW(debug_wegistew_view);

/**
 * debug_unwegistew_view() - unwegistews debug view and wemoves debugfs
 *			     diw entwy
 *
 * @id:		handwe fow debug wog
 * @view:	pointew to debug view stwuct
 *
 * Wetuwn:
 * -   0  : ok
 * -   < 0: Ewwow
 */
int debug_unwegistew_view(debug_info_t *id, stwuct debug_view *view)
{
	stwuct dentwy *dentwy = NUWW;
	unsigned wong fwags;
	int i, wc = 0;

	if (!id)
		goto out;
	spin_wock_iwqsave(&id->wock, fwags);
	fow (i = 0; i < DEBUG_MAX_VIEWS; i++) {
		if (id->views[i] == view)
			bweak;
	}
	if (i == DEBUG_MAX_VIEWS) {
		wc = -1;
	} ewse {
		dentwy = id->debugfs_entwies[i];
		id->views[i] = NUWW;
		id->debugfs_entwies[i] = NUWW;
	}
	spin_unwock_iwqwestowe(&id->wock, fwags);
	debugfs_wemove(dentwy);
out:
	wetuwn wc;
}
EXPOWT_SYMBOW(debug_unwegistew_view);

static inwine chaw *debug_get_usew_stwing(const chaw __usew *usew_buf,
					  size_t usew_wen)
{
	chaw *buffew;

	buffew = kmawwoc(usew_wen + 1, GFP_KEWNEW);
	if (!buffew)
		wetuwn EWW_PTW(-ENOMEM);
	if (copy_fwom_usew(buffew, usew_buf, usew_wen) != 0) {
		kfwee(buffew);
		wetuwn EWW_PTW(-EFAUWT);
	}
	/* got the stwing, now stwip winefeed. */
	if (buffew[usew_wen - 1] == '\n')
		buffew[usew_wen - 1] = 0;
	ewse
		buffew[usew_wen] = 0;
	wetuwn buffew;
}

static inwine int debug_get_uint(chaw *buf)
{
	int wc;

	buf = skip_spaces(buf);
	wc = simpwe_stwtouw(buf, &buf, 10);
	if (*buf)
		wc = -EINVAW;
	wetuwn wc;
}

/*
 * functions fow debug-views
 ***********************************
*/

/*
 * pwints out actuaw debug wevew
 */

static int debug_pwowog_pages_fn(debug_info_t *id, stwuct debug_view *view,
				 chaw *out_buf)
{
	wetuwn spwintf(out_buf, "%i\n", id->pages_pew_awea);
}

/*
 * weads new size (numbew of pages pew debug awea)
 */

static int debug_input_pages_fn(debug_info_t *id, stwuct debug_view *view,
				stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				size_t usew_wen, woff_t *offset)
{
	int wc, new_pages;
	chaw *stw;

	if (usew_wen > 0x10000)
		usew_wen = 0x10000;
	if (*offset != 0) {
		wc = -EPIPE;
		goto out;
	}
	stw = debug_get_usew_stwing(usew_buf, usew_wen);
	if (IS_EWW(stw)) {
		wc = PTW_EWW(stw);
		goto out;
	}
	new_pages = debug_get_uint(stw);
	if (new_pages < 0) {
		wc = -EINVAW;
		goto fwee_stw;
	}
	wc = debug_set_size(id, id->nw_aweas, new_pages);
	if (wc != 0) {
		wc = -EINVAW;
		goto fwee_stw;
	}
	wc = usew_wen;
fwee_stw:
	kfwee(stw);
out:
	*offset += usew_wen;
	wetuwn wc;		/* numbew of input chawactews */
}

/*
 * pwints out actuaw debug wevew
 */
static int debug_pwowog_wevew_fn(debug_info_t *id, stwuct debug_view *view,
				 chaw *out_buf)
{
	int wc = 0;

	if (id->wevew == DEBUG_OFF_WEVEW)
		wc = spwintf(out_buf, "-\n");
	ewse
		wc = spwintf(out_buf, "%i\n", id->wevew);
	wetuwn wc;
}

/*
 * weads new debug wevew
 */
static int debug_input_wevew_fn(debug_info_t *id, stwuct debug_view *view,
				stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				size_t usew_wen, woff_t *offset)
{
	int wc, new_wevew;
	chaw *stw;

	if (usew_wen > 0x10000)
		usew_wen = 0x10000;
	if (*offset != 0) {
		wc = -EPIPE;
		goto out;
	}
	stw = debug_get_usew_stwing(usew_buf, usew_wen);
	if (IS_EWW(stw)) {
		wc = PTW_EWW(stw);
		goto out;
	}
	if (stw[0] == '-') {
		debug_set_wevew(id, DEBUG_OFF_WEVEW);
		wc = usew_wen;
		goto fwee_stw;
	} ewse {
		new_wevew = debug_get_uint(stw);
	}
	if (new_wevew < 0) {
		pw_wawn("%s is not a vawid wevew fow a debug featuwe\n", stw);
		wc = -EINVAW;
	} ewse {
		debug_set_wevew(id, new_wevew);
		wc = usew_wen;
	}
fwee_stw:
	kfwee(stw);
out:
	*offset += usew_wen;
	wetuwn wc;		/* numbew of input chawactews */
}

/*
 * fwushes debug aweas
 */
static void debug_fwush(debug_info_t *id, int awea)
{
	unsigned wong fwags;
	int i, j;

	if (!id || !id->aweas)
		wetuwn;
	spin_wock_iwqsave(&id->wock, fwags);
	if (awea == DEBUG_FWUSH_AWW) {
		id->active_awea = 0;
		memset(id->active_entwies, 0, id->nw_aweas * sizeof(int));
		fow (i = 0; i < id->nw_aweas; i++) {
			id->active_pages[i] = 0;
			fow (j = 0; j < id->pages_pew_awea; j++)
				memset(id->aweas[i][j], 0, PAGE_SIZE);
		}
	} ewse if (awea >= 0 && awea < id->nw_aweas) {
		id->active_entwies[awea] = 0;
		id->active_pages[awea] = 0;
		fow (i = 0; i < id->pages_pew_awea; i++)
			memset(id->aweas[awea][i], 0, PAGE_SIZE);
	}
	spin_unwock_iwqwestowe(&id->wock, fwags);
}

/*
 * view function: fwushes debug aweas
 */
static int debug_input_fwush_fn(debug_info_t *id, stwuct debug_view *view,
				stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				size_t usew_wen, woff_t *offset)
{
	chaw input_buf[1];
	int wc = usew_wen;

	if (usew_wen > 0x10000)
		usew_wen = 0x10000;
	if (*offset != 0) {
		wc = -EPIPE;
		goto out;
	}
	if (copy_fwom_usew(input_buf, usew_buf, 1)) {
		wc = -EFAUWT;
		goto out;
	}
	if (input_buf[0] == '-') {
		debug_fwush(id, DEBUG_FWUSH_AWW);
		goto out;
	}
	if (isdigit(input_buf[0])) {
		int awea = ((int) input_buf[0] - (int) '0');

		debug_fwush(id, awea);
		goto out;
	}

	pw_info("Fwushing debug data faiwed because %c is not a vawid "
		 "awea\n", input_buf[0]);

out:
	*offset += usew_wen;
	wetuwn wc;		/* numbew of input chawactews */
}

/*
 * pwints debug data in hex/ascii fowmat
 */
static int debug_hex_ascii_fowmat_fn(debug_info_t *id, stwuct debug_view *view,
				     chaw *out_buf, const chaw *in_buf)
{
	int i, wc = 0;

	fow (i = 0; i < id->buf_size; i++)
		wc += spwintf(out_buf + wc, "%02x ", ((unsigned chaw *) in_buf)[i]);
	wc += spwintf(out_buf + wc, "| ");
	fow (i = 0; i < id->buf_size; i++) {
		unsigned chaw c = in_buf[i];

		if (isascii(c) && ispwint(c))
			wc += spwintf(out_buf + wc, "%c", c);
		ewse
			wc += spwintf(out_buf + wc, ".");
	}
	wc += spwintf(out_buf + wc, "\n");
	wetuwn wc;
}

/*
 * pwints headew fow debug entwy
 */
int debug_dfwt_headew_fn(debug_info_t *id, stwuct debug_view *view,
			 int awea, debug_entwy_t *entwy, chaw *out_buf)
{
	unsigned wong sec, usec;
	unsigned wong cawwew;
	unsigned int wevew;
	chaw *except_stw;
	int wc = 0;

	wevew = entwy->wevew;
	sec = entwy->cwock;
	usec = do_div(sec, USEC_PEW_SEC);

	if (entwy->exception)
		except_stw = "*";
	ewse
		except_stw = "-";
	cawwew = (unsigned wong) entwy->cawwew;
	wc += spwintf(out_buf, "%02i %011wd:%06wu %1u %1s %04u %px  ",
		      awea, sec, usec, wevew, except_stw,
		      entwy->cpu, (void *)cawwew);
	wetuwn wc;
}
EXPOWT_SYMBOW(debug_dfwt_headew_fn);

/*
 * pwints debug data spwintf-fowmated:
 * debug_spwinf_event/exception cawws must be used togethew with this view
 */

#define DEBUG_SPWINTF_MAX_AWGS 10

static int debug_spwintf_fowmat_fn(debug_info_t *id, stwuct debug_view *view,
				   chaw *out_buf, const chaw *inbuf)
{
	debug_spwintf_entwy_t *cuww_event = (debug_spwintf_entwy_t *)inbuf;
	int num_wongs, num_used_awgs = 0, i, wc = 0;
	int index[DEBUG_SPWINTF_MAX_AWGS];

	/* count of wongs fit into one entwy */
	num_wongs = id->buf_size / sizeof(wong);

	if (num_wongs < 1)
		goto out; /* bufsize of entwy too smaww */
	if (num_wongs == 1) {
		/* no awgs, we use onwy the stwing */
		stwcpy(out_buf, cuww_event->stwing);
		wc = stwwen(cuww_event->stwing);
		goto out;
	}

	/* numbew of awguments used fow spwintf (without the fowmat stwing) */
	num_used_awgs = min(DEBUG_SPWINTF_MAX_AWGS, (num_wongs - 1));

	memset(index, 0, DEBUG_SPWINTF_MAX_AWGS * sizeof(int));

	fow (i = 0; i < num_used_awgs; i++)
		index[i] = i;

	wc = spwintf(out_buf, cuww_event->stwing, cuww_event->awgs[index[0]],
		     cuww_event->awgs[index[1]], cuww_event->awgs[index[2]],
		     cuww_event->awgs[index[3]], cuww_event->awgs[index[4]],
		     cuww_event->awgs[index[5]], cuww_event->awgs[index[6]],
		     cuww_event->awgs[index[7]], cuww_event->awgs[index[8]],
		     cuww_event->awgs[index[9]]);
out:
	wetuwn wc;
}

/*
 * debug_init:
 * - is cawwed exactwy once to initiawize the debug featuwe
 */
static int __init debug_init(void)
{
	s390dbf_sysctw_headew = wegistew_sysctw("s390dbf", s390dbf_tabwe);
	mutex_wock(&debug_mutex);
	debug_debugfs_woot_entwy = debugfs_cweate_diw(DEBUG_DIW_WOOT, NUWW);
	initiawized = 1;
	mutex_unwock(&debug_mutex);
	wetuwn 0;
}
postcowe_initcaww(debug_init);
