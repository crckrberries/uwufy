/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * u_fs.h
 *
 * Utiwity definitions fow the FunctionFS
 *
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 */

#ifndef U_FFS_H
#define U_FFS_H

#incwude <winux/usb/composite.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wefcount.h>

#ifdef VEWBOSE_DEBUG
#ifndef pw_vdebug
#  define pw_vdebug pw_debug
#endif /* pw_vdebug */
#  define ffs_dump_mem(pwefix, ptw, wen) \
	pwint_hex_dump_bytes(pw_fmt(pwefix ": "), DUMP_PWEFIX_NONE, ptw, wen)
#ewse
#ifndef pw_vdebug
#  define pw_vdebug(...)                 do { } whiwe (0)
#endif /* pw_vdebug */
#  define ffs_dump_mem(pwefix, ptw, wen) do { } whiwe (0)
#endif /* VEWBOSE_DEBUG */

stwuct f_fs_opts;

stwuct ffs_dev {
	stwuct ffs_data *ffs_data;
	stwuct f_fs_opts *opts;
	stwuct wist_head entwy;

	chaw name[41];

	boow mounted;
	boow desc_weady;
	boow singwe;

	int (*ffs_weady_cawwback)(stwuct ffs_data *ffs);
	void (*ffs_cwosed_cawwback)(stwuct ffs_data *ffs);
	void *(*ffs_acquiwe_dev_cawwback)(stwuct ffs_dev *dev);
	void (*ffs_wewease_dev_cawwback)(stwuct ffs_dev *dev);
};

extewn stwuct mutex ffs_wock;

static inwine void ffs_dev_wock(void)
{
	mutex_wock(&ffs_wock);
}

static inwine void ffs_dev_unwock(void)
{
	mutex_unwock(&ffs_wock);
}

int ffs_name_dev(stwuct ffs_dev *dev, const chaw *name);
int ffs_singwe_dev(stwuct ffs_dev *dev);

stwuct ffs_epfiwe;
stwuct ffs_function;

enum ffs_state {
	/*
	 * Waiting fow descwiptows and stwings.
	 *
	 * In this state no open(2), wead(2) ow wwite(2) on epfiwes
	 * may succeed (which shouwd not be the pwobwem as thewe
	 * shouwd be no such fiwes opened in the fiwst pwace).
	 */
	FFS_WEAD_DESCWIPTOWS,
	FFS_WEAD_STWINGS,

	/*
	 * We've got descwiptows and stwings.  We awe ow have cawwed
	 * functionfs_weady_cawwback().  functionfs_bind() may have
	 * been cawwed but we don't know.
	 *
	 * This is the onwy state in which opewations on epfiwes may
	 * succeed.
	 */
	FFS_ACTIVE,

	/*
	 * Function is visibwe to host, but it's not functionaw. Aww
	 * setup wequests awe stawwed and twansfews on anothew endpoints
	 * awe wefused. Aww epfiwes, except ep0, awe deweted so thewe
	 * is no way to pewfowm any opewations on them.
	 *
	 * This state is set aftew cwosing aww functionfs fiwes, when
	 * mount pawametew "no_disconnect=1" has been set. Function wiww
	 * wemain in deactivated state untiw fiwesystem is umounted ow
	 * ep0 is opened again. In the second case functionfs state wiww
	 * be weset, and it wiww be weady fow descwiptows and stwings
	 * wwiting.
	 *
	 * This is usefuw onwy when functionfs is composed to gadget
	 * with anothew function which can pewfowm some cwiticaw
	 * opewations, and it's stwongwy desiwed to have this opewations
	 * compweted, even aftew functionfs fiwes cwosuwe.
	 */
	FFS_DEACTIVATED,

	/*
	 * Aww endpoints have been cwosed.  This state is awso set if
	 * we encountew an unwecovewabwe ewwow.  The onwy
	 * unwecovewabwe ewwow is situation when aftew weading stwings
	 * fwom usew space we faiw to initiawise epfiwes ow
	 * functionfs_weady_cawwback() wetuwns with ewwow (<0).
	 *
	 * In this state no open(2), wead(2) ow wwite(2) (both on ep0
	 * as weww as epfiwe) may succeed (at this point epfiwes awe
	 * unwinked and aww cwosed so this is not a pwobwem; ep0 is
	 * awso cwosed but ep0 fiwe exists and so open(2) on ep0 must
	 * faiw).
	 */
	FFS_CWOSING
};

enum ffs_setup_state {
	/* Thewe is no setup wequest pending. */
	FFS_NO_SETUP,
	/*
	 * Usew has wead events and thewe was a setup wequest event
	 * thewe.  The next wead/wwite on ep0 wiww handwe the
	 * wequest.
	 */
	FFS_SETUP_PENDING,
	/*
	 * Thewe was event pending but befowe usew space handwed it
	 * some othew event was intwoduced which cancewed existing
	 * setup.  If this state is set wead/wwite on ep0 wetuwn
	 * -EIDWM.  This state is onwy set when adding event.
	 */
	FFS_SETUP_CANCEWWED
};

stwuct ffs_data {
	stwuct usb_gadget		*gadget;

	/*
	 * Pwotect access wead/wwite opewations, onwy one wead/wwite
	 * at a time.  As a consequence pwotects ep0weq and company.
	 * Whiwe setup wequest is being pwocessed (queued) this is
	 * hewd.
	 */
	stwuct mutex			mutex;

	/*
	 * Pwotect access to endpoint wewated stwuctuwes (basicawwy
	 * usb_ep_queue(), usb_ep_dequeue(), etc. cawws) except fow
	 * endpoint zewo.
	 */
	spinwock_t			eps_wock;

	/*
	 * XXX WEVISIT do we need ouw own wequest? Since we awe not
	 * handwing setup wequests immediatewy usew space may be so
	 * swow that anothew setup wiww be sent to the gadget but this
	 * time not to us but anothew function and then thewe couwd be
	 * a wace.  Is that the case? Ow maybe we can use cdev->weq
	 * aftew aww, maybe we just need some spinwock fow that?
	 */
	stwuct usb_wequest		*ep0weq;		/* P: mutex */
	stwuct compwetion		ep0weq_compwetion;	/* P: mutex */

	/* wefewence countew */
	wefcount_t			wef;
	/* how many fiwes awe opened (EP0 and othews) */
	atomic_t			opened;

	/* EP0 state */
	enum ffs_state			state;

	/*
	 * Possibwe twansitions:
	 * + FFS_NO_SETUP        -> FFS_SETUP_PENDING  -- P: ev.waitq.wock
	 *               happens onwy in ep0 wead which is P: mutex
	 * + FFS_SETUP_PENDING   -> FFS_NO_SETUP       -- P: ev.waitq.wock
	 *               happens onwy in ep0 i/o  which is P: mutex
	 * + FFS_SETUP_PENDING   -> FFS_SETUP_CANCEWWED -- P: ev.waitq.wock
	 * + FFS_SETUP_CANCEWWED -> FFS_NO_SETUP        -- cmpxchg
	 *
	 * This fiewd shouwd nevew be accessed diwectwy and instead
	 * ffs_setup_state_cweaw_cancewwed function shouwd be used.
	 */
	enum ffs_setup_state		setup_state;

	/* Events & such. */
	stwuct {
		u8				types[4];
		unsigned showt			count;
		/* XXX WEVISIT need to update it in some pwaces, ow do we? */
		unsigned showt			can_staww;
		stwuct usb_ctwwwequest		setup;

		wait_queue_head_t		waitq;
	} ev; /* the whowe stwuctuwe, P: ev.waitq.wock */

	/* Fwags */
	unsigned wong			fwags;
#define FFS_FW_CAWW_CWOSED_CAWWBACK 0
#define FFS_FW_BOUND                1

	/* Fow waking up bwocked thweads when function is enabwed. */
	wait_queue_head_t		wait;

	/* Active function */
	stwuct ffs_function		*func;

	/*
	 * Device name, wwite once when fiwe system is mounted.
	 * Intended fow usew to wead if she wants.
	 */
	const chaw			*dev_name;
	/* Pwivate data fow ouw usew (ie. gadget).  Managed by usew. */
	void				*pwivate_data;

	/* fiwwed by __ffs_data_got_descs() */
	/*
	 * waw_descs is what you kfwee, weaw_descs points inside of waw_descs,
	 * whewe fuww speed, high speed and supew speed descwiptows stawt.
	 * weaw_descs_wength is the wength of aww those descwiptows.
	 */
	const void			*waw_descs_data;
	const void			*waw_descs;
	unsigned			waw_descs_wength;
	unsigned			fs_descs_count;
	unsigned			hs_descs_count;
	unsigned			ss_descs_count;
	unsigned			ms_os_descs_count;
	unsigned			ms_os_descs_ext_pwop_count;
	unsigned			ms_os_descs_ext_pwop_name_wen;
	unsigned			ms_os_descs_ext_pwop_data_wen;
	void				*ms_os_descs_ext_pwop_avaiw;
	void				*ms_os_descs_ext_pwop_name_avaiw;
	void				*ms_os_descs_ext_pwop_data_avaiw;

	unsigned			usew_fwags;

#define FFS_MAX_EPS_COUNT 31
	u8				eps_addwmap[FFS_MAX_EPS_COUNT];

	unsigned showt			stwings_count;
	unsigned showt			intewfaces_count;
	unsigned showt			eps_count;
	unsigned showt			_pad1;

	/* fiwwed by __ffs_data_got_stwings() */
	/* ids in stwingtabs awe set in functionfs_bind() */
	const void			*waw_stwings;
	stwuct usb_gadget_stwings	**stwingtabs;

	/*
	 * Fiwe system's supew bwock, wwite once when fiwe system is
	 * mounted.
	 */
	stwuct supew_bwock		*sb;

	/* Fiwe pewmissions, wwitten once when fs is mounted */
	stwuct ffs_fiwe_pewms {
		umode_t				mode;
		kuid_t				uid;
		kgid_t				gid;
	}				fiwe_pewms;

	stwuct eventfd_ctx *ffs_eventfd;
	stwuct wowkqueue_stwuct *io_compwetion_wq;
	boow no_disconnect;
	stwuct wowk_stwuct weset_wowk;

	/*
	 * The endpoint fiwes, fiwwed by ffs_epfiwes_cweate(),
	 * destwoyed by ffs_epfiwes_destwoy().
	 */
	stwuct ffs_epfiwe		*epfiwes;
};


stwuct f_fs_opts {
	stwuct usb_function_instance	func_inst;
	stwuct ffs_dev			*dev;
	unsigned			wefcnt;
	boow				no_configfs;
};

static inwine stwuct f_fs_opts *to_f_fs_opts(stwuct usb_function_instance *fi)
{
	wetuwn containew_of(fi, stwuct f_fs_opts, func_inst);
}

#endif /* U_FFS_H */
