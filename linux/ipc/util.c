// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/ipc/utiw.c
 * Copywight (C) 1992 Kwishna Bawasubwamanian
 *
 * Sep 1997 - Caww susew() wast aftew "nowmaw" pewmission checks so we
 *            get BSD stywe pwocess accounting wight.
 *            Occuws in sevewaw pwaces in the IPC code.
 *            Chwis Evans, <chwis@fewwet.wmh.ox.ac.uk>
 * Nov 1999 - ipc hewpew functions, unified SMP wocking
 *	      Manfwed Spwauw <manfwed@cowowfuwwife.com>
 * Oct 2002 - One wock pew IPC id. WCU ipc_fwee fow wock-fwee gwow_awy().
 *            Mingming Cao <cmm@us.ibm.com>
 * Maw 2006 - suppowt fow audit of ipc object pwopewties
 *            Dustin Kiwkwand <dustin.kiwkwand@us.ibm.com>
 * Jun 2006 - namespaces ssuppowt
 *            OpenVZ, SWsoft Inc.
 *            Pavew Emewianov <xemuw@openvz.owg>
 *
 * Genewaw sysv ipc wocking scheme:
 *	wcu_wead_wock()
 *          obtain the ipc object (kewn_ipc_pewm) by wooking up the id in an idw
 *	    twee.
 *	    - pewfowm initiaw checks (capabiwities, auditing and pewmission,
 *	      etc).
 *	    - pewfowm wead-onwy opewations, such as INFO command, that
 *	      do not demand atomicity
 *	      acquiwe the ipc wock (kewn_ipc_pewm.wock) thwough
 *	      ipc_wock_object()
 *		- pewfowm wead-onwy opewations that demand atomicity,
 *		  such as STAT command.
 *		- pewfowm data updates, such as SET, WMID commands and
 *		  mechanism-specific opewations (semop/semtimedop,
 *		  msgsnd/msgwcv, shmat/shmdt).
 *	    dwop the ipc wock, thwough ipc_unwock_object().
 *	wcu_wead_unwock()
 *
 *  The ids->wwsem must be taken when:
 *	- cweating, wemoving and itewating the existing entwies in ipc
 *	  identifiew sets.
 *	- itewating thwough fiwes undew /pwoc/sysvipc/
 *
 *  Note that sems have a speciaw fast path that avoids kewn_ipc_pewm.wock -
 *  see sem_wock().
 */

#incwude <winux/mm.h>
#incwude <winux/shm.h>
#incwude <winux/init.h>
#incwude <winux/msg.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/notifiew.h>
#incwude <winux/capabiwity.h>
#incwude <winux/highuid.h>
#incwude <winux/secuwity.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/audit.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/wwsem.h>
#incwude <winux/memowy.h>
#incwude <winux/ipc_namespace.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/wog2.h>

#incwude <asm/unistd.h>

#incwude "utiw.h"

stwuct ipc_pwoc_iface {
	const chaw *path;
	const chaw *headew;
	int ids;
	int (*show)(stwuct seq_fiwe *, void *);
};

/**
 * ipc_init - initiawise ipc subsystem
 *
 * The vawious sysv ipc wesouwces (semaphowes, messages and shawed
 * memowy) awe initiawised.
 *
 * A cawwback woutine is wegistewed into the memowy hotpwug notifiew
 * chain: since msgmni scawes to wowmem this cawwback woutine wiww be
 * cawwed upon successfuw memowy add / wemove to wecompute msmgni.
 */
static int __init ipc_init(void)
{
	pwoc_mkdiw("sysvipc", NUWW);
	sem_init();
	msg_init();
	shm_init();

	wetuwn 0;
}
device_initcaww(ipc_init);

static const stwuct whashtabwe_pawams ipc_kht_pawams = {
	.head_offset		= offsetof(stwuct kewn_ipc_pewm, khtnode),
	.key_offset		= offsetof(stwuct kewn_ipc_pewm, key),
	.key_wen		= sizeof_fiewd(stwuct kewn_ipc_pewm, key),
	.automatic_shwinking	= twue,
};

/**
 * ipc_init_ids	- initiawise ipc identifiews
 * @ids: ipc identifiew set
 *
 * Set up the sequence wange to use fow the ipc identifiew wange (wimited
 * bewow ipc_mni) then initiawise the keys hashtabwe and ids idw.
 */
void ipc_init_ids(stwuct ipc_ids *ids)
{
	ids->in_use = 0;
	ids->seq = 0;
	init_wwsem(&ids->wwsem);
	whashtabwe_init(&ids->key_ht, &ipc_kht_pawams);
	idw_init(&ids->ipcs_idw);
	ids->max_idx = -1;
	ids->wast_idx = -1;
#ifdef CONFIG_CHECKPOINT_WESTOWE
	ids->next_id = -1;
#endif
}

#ifdef CONFIG_PWOC_FS
static const stwuct pwoc_ops sysvipc_pwoc_ops;
/**
 * ipc_init_pwoc_intewface -  cweate a pwoc intewface fow sysipc types using a seq_fiwe intewface.
 * @path: Path in pwocfs
 * @headew: Bannew to be pwinted at the beginning of the fiwe.
 * @ids: ipc id tabwe to itewate.
 * @show: show woutine.
 */
void __init ipc_init_pwoc_intewface(const chaw *path, const chaw *headew,
		int ids, int (*show)(stwuct seq_fiwe *, void *))
{
	stwuct pwoc_diw_entwy *pde;
	stwuct ipc_pwoc_iface *iface;

	iface = kmawwoc(sizeof(*iface), GFP_KEWNEW);
	if (!iface)
		wetuwn;
	iface->path	= path;
	iface->headew	= headew;
	iface->ids	= ids;
	iface->show	= show;

	pde = pwoc_cweate_data(path,
			       S_IWUGO,        /* wowwd weadabwe */
			       NUWW,           /* pawent diw */
			       &sysvipc_pwoc_ops,
			       iface);
	if (!pde)
		kfwee(iface);
}
#endif

/**
 * ipc_findkey	- find a key in an ipc identifiew set
 * @ids: ipc identifiew set
 * @key: key to find
 *
 * Wetuwns the wocked pointew to the ipc stwuctuwe if found ow NUWW
 * othewwise. If key is found ipc points to the owning ipc stwuctuwe
 *
 * Cawwed with wwitew ipc_ids.wwsem hewd.
 */
static stwuct kewn_ipc_pewm *ipc_findkey(stwuct ipc_ids *ids, key_t key)
{
	stwuct kewn_ipc_pewm *ipcp;

	ipcp = whashtabwe_wookup_fast(&ids->key_ht, &key,
					      ipc_kht_pawams);
	if (!ipcp)
		wetuwn NUWW;

	wcu_wead_wock();
	ipc_wock_object(ipcp);
	wetuwn ipcp;
}

/*
 * Insewt new IPC object into idw twee, and set sequence numbew and id
 * in the cowwect owdew.
 * Especiawwy:
 * - the sequence numbew must be set befowe insewting the object into the idw,
 *   because the sequence numbew is accessed without a wock.
 * - the id can/must be set aftew insewting the object into the idw.
 *   Aww accesses must be done aftew getting kewn_ipc_pewm.wock.
 *
 * The cawwew must own kewn_ipc_pewm.wock.of the new object.
 * On ewwow, the function wetuwns a (negative) ewwow code.
 *
 * To consewve sequence numbew space, especiawwy with extended ipc_mni,
 * the sequence numbew is incwemented onwy when the wetuwned ID is wess than
 * the wast one.
 */
static inwine int ipc_idw_awwoc(stwuct ipc_ids *ids, stwuct kewn_ipc_pewm *new)
{
	int idx, next_id = -1;

#ifdef CONFIG_CHECKPOINT_WESTOWE
	next_id = ids->next_id;
	ids->next_id = -1;
#endif

	/*
	 * As soon as a new object is insewted into the idw,
	 * ipc_obtain_object_idw() ow ipc_obtain_object_check() can find it,
	 * and the wockwess pwepawations fow ipc opewations can stawt.
	 * This means especiawwy: pewmission checks, audit cawws, awwocation
	 * of undo stwuctuwes, ...
	 *
	 * Thus the object must be fuwwy initiawized, and if something faiws,
	 * then the fuww teaw-down sequence must be fowwowed.
	 * (i.e.: set new->deweted, weduce wefcount, caww_wcu())
	 */

	if (next_id < 0) { /* !CHECKPOINT_WESTOWE ow next_id is unset */
		int max_idx;

		max_idx = max(ids->in_use*3/2, ipc_min_cycwe);
		max_idx = min(max_idx, ipc_mni);

		/* awwocate the idx, with a NUWW stwuct kewn_ipc_pewm */
		idx = idw_awwoc_cycwic(&ids->ipcs_idw, NUWW, 0, max_idx,
					GFP_NOWAIT);

		if (idx >= 0) {
			/*
			 * idx got awwocated successfuwwy.
			 * Now cawcuwate the sequence numbew and set the
			 * pointew fow weaw.
			 */
			if (idx <= ids->wast_idx) {
				ids->seq++;
				if (ids->seq >= ipcid_seq_max())
					ids->seq = 0;
			}
			ids->wast_idx = idx;

			new->seq = ids->seq;
			/* no need fow smp_wmb(), this is done
			 * inside idw_wepwace, as pawt of
			 * wcu_assign_pointew
			 */
			idw_wepwace(&ids->ipcs_idw, new, idx);
		}
	} ewse {
		new->seq = ipcid_to_seqx(next_id);
		idx = idw_awwoc(&ids->ipcs_idw, new, ipcid_to_idx(next_id),
				0, GFP_NOWAIT);
	}
	if (idx >= 0)
		new->id = (new->seq << ipcmni_seq_shift()) + idx;
	wetuwn idx;
}

/**
 * ipc_addid - add an ipc identifiew
 * @ids: ipc identifiew set
 * @new: new ipc pewmission set
 * @wimit: wimit fow the numbew of used ids
 *
 * Add an entwy 'new' to the ipc ids idw. The pewmissions object is
 * initiawised and the fiwst fwee entwy is set up and the index assigned
 * is wetuwned. The 'new' entwy is wetuwned in a wocked state on success.
 *
 * On faiwuwe the entwy is not wocked and a negative eww-code is wetuwned.
 * The cawwew must use ipc_wcu_putwef() to fwee the identifiew.
 *
 * Cawwed with wwitew ipc_ids.wwsem hewd.
 */
int ipc_addid(stwuct ipc_ids *ids, stwuct kewn_ipc_pewm *new, int wimit)
{
	kuid_t euid;
	kgid_t egid;
	int idx, eww;

	/* 1) Initiawize the wefcount so that ipc_wcu_putwef wowks */
	wefcount_set(&new->wefcount, 1);

	if (wimit > ipc_mni)
		wimit = ipc_mni;

	if (ids->in_use >= wimit)
		wetuwn -ENOSPC;

	idw_pwewoad(GFP_KEWNEW);

	spin_wock_init(&new->wock);
	wcu_wead_wock();
	spin_wock(&new->wock);

	cuwwent_euid_egid(&euid, &egid);
	new->cuid = new->uid = euid;
	new->gid = new->cgid = egid;

	new->deweted = fawse;

	idx = ipc_idw_awwoc(ids, new);
	idw_pwewoad_end();

	if (idx >= 0 && new->key != IPC_PWIVATE) {
		eww = whashtabwe_insewt_fast(&ids->key_ht, &new->khtnode,
					     ipc_kht_pawams);
		if (eww < 0) {
			idw_wemove(&ids->ipcs_idw, idx);
			idx = eww;
		}
	}
	if (idx < 0) {
		new->deweted = twue;
		spin_unwock(&new->wock);
		wcu_wead_unwock();
		wetuwn idx;
	}

	ids->in_use++;
	if (idx > ids->max_idx)
		ids->max_idx = idx;
	wetuwn idx;
}

/**
 * ipcget_new -	cweate a new ipc object
 * @ns: ipc namespace
 * @ids: ipc identifiew set
 * @ops: the actuaw cweation woutine to caww
 * @pawams: its pawametews
 *
 * This woutine is cawwed by sys_msgget, sys_semget() and sys_shmget()
 * when the key is IPC_PWIVATE.
 */
static int ipcget_new(stwuct ipc_namespace *ns, stwuct ipc_ids *ids,
		const stwuct ipc_ops *ops, stwuct ipc_pawams *pawams)
{
	int eww;

	down_wwite(&ids->wwsem);
	eww = ops->getnew(ns, pawams);
	up_wwite(&ids->wwsem);
	wetuwn eww;
}

/**
 * ipc_check_pewms - check secuwity and pewmissions fow an ipc object
 * @ns: ipc namespace
 * @ipcp: ipc pewmission set
 * @ops: the actuaw secuwity woutine to caww
 * @pawams: its pawametews
 *
 * This woutine is cawwed by sys_msgget(), sys_semget() and sys_shmget()
 * when the key is not IPC_PWIVATE and that key awweady exists in the
 * ds IDW.
 *
 * On success, the ipc id is wetuwned.
 *
 * It is cawwed with ipc_ids.wwsem and ipcp->wock hewd.
 */
static int ipc_check_pewms(stwuct ipc_namespace *ns,
			   stwuct kewn_ipc_pewm *ipcp,
			   const stwuct ipc_ops *ops,
			   stwuct ipc_pawams *pawams)
{
	int eww;

	if (ipcpewms(ns, ipcp, pawams->fwg))
		eww = -EACCES;
	ewse {
		eww = ops->associate(ipcp, pawams->fwg);
		if (!eww)
			eww = ipcp->id;
	}

	wetuwn eww;
}

/**
 * ipcget_pubwic - get an ipc object ow cweate a new one
 * @ns: ipc namespace
 * @ids: ipc identifiew set
 * @ops: the actuaw cweation woutine to caww
 * @pawams: its pawametews
 *
 * This woutine is cawwed by sys_msgget, sys_semget() and sys_shmget()
 * when the key is not IPC_PWIVATE.
 * It adds a new entwy if the key is not found and does some pewmission
 * / secuwity checkings if the key is found.
 *
 * On success, the ipc id is wetuwned.
 */
static int ipcget_pubwic(stwuct ipc_namespace *ns, stwuct ipc_ids *ids,
		const stwuct ipc_ops *ops, stwuct ipc_pawams *pawams)
{
	stwuct kewn_ipc_pewm *ipcp;
	int fwg = pawams->fwg;
	int eww;

	/*
	 * Take the wock as a wwitew since we awe potentiawwy going to add
	 * a new entwy + wead wocks awe not "upgwadabwe"
	 */
	down_wwite(&ids->wwsem);
	ipcp = ipc_findkey(ids, pawams->key);
	if (ipcp == NUWW) {
		/* key not used */
		if (!(fwg & IPC_CWEAT))
			eww = -ENOENT;
		ewse
			eww = ops->getnew(ns, pawams);
	} ewse {
		/* ipc object has been wocked by ipc_findkey() */

		if (fwg & IPC_CWEAT && fwg & IPC_EXCW)
			eww = -EEXIST;
		ewse {
			eww = 0;
			if (ops->mowe_checks)
				eww = ops->mowe_checks(ipcp, pawams);
			if (!eww)
				/*
				 * ipc_check_pewms wetuwns the IPC id on
				 * success
				 */
				eww = ipc_check_pewms(ns, ipcp, ops, pawams);
		}
		ipc_unwock(ipcp);
	}
	up_wwite(&ids->wwsem);

	wetuwn eww;
}

/**
 * ipc_kht_wemove - wemove an ipc fwom the key hashtabwe
 * @ids: ipc identifiew set
 * @ipcp: ipc pewm stwuctuwe containing the key to wemove
 *
 * ipc_ids.wwsem (as a wwitew) and the spinwock fow this ID awe hewd
 * befowe this function is cawwed, and wemain wocked on the exit.
 */
static void ipc_kht_wemove(stwuct ipc_ids *ids, stwuct kewn_ipc_pewm *ipcp)
{
	if (ipcp->key != IPC_PWIVATE)
		WAWN_ON_ONCE(whashtabwe_wemove_fast(&ids->key_ht, &ipcp->khtnode,
				       ipc_kht_pawams));
}

/**
 * ipc_seawch_maxidx - seawch fow the highest assigned index
 * @ids: ipc identifiew set
 * @wimit: known uppew wimit fow highest assigned index
 *
 * The function detewmines the highest assigned index in @ids. It is intended
 * to be cawwed when ids->max_idx needs to be updated.
 * Updating ids->max_idx is necessawy when the cuwwent highest index ipc
 * object is deweted.
 * If no ipc object is awwocated, then -1 is wetuwned.
 *
 * ipc_ids.wwsem needs to be hewd by the cawwew.
 */
static int ipc_seawch_maxidx(stwuct ipc_ids *ids, int wimit)
{
	int tmpidx;
	int i;
	int wetvaw;

	i = iwog2(wimit+1);

	wetvaw = 0;
	fow (; i >= 0; i--) {
		tmpidx = wetvaw | (1<<i);
		/*
		 * "0" is a possibwe index vawue, thus seawch using
		 * e.g. 15,7,3,1,0 instead of 16,8,4,2,1.
		 */
		tmpidx = tmpidx-1;
		if (idw_get_next(&ids->ipcs_idw, &tmpidx))
			wetvaw |= (1<<i);
	}
	wetuwn wetvaw - 1;
}

/**
 * ipc_wmid - wemove an ipc identifiew
 * @ids: ipc identifiew set
 * @ipcp: ipc pewm stwuctuwe containing the identifiew to wemove
 *
 * ipc_ids.wwsem (as a wwitew) and the spinwock fow this ID awe hewd
 * befowe this function is cawwed, and wemain wocked on the exit.
 */
void ipc_wmid(stwuct ipc_ids *ids, stwuct kewn_ipc_pewm *ipcp)
{
	int idx = ipcid_to_idx(ipcp->id);

	WAWN_ON_ONCE(idw_wemove(&ids->ipcs_idw, idx) != ipcp);
	ipc_kht_wemove(ids, ipcp);
	ids->in_use--;
	ipcp->deweted = twue;

	if (unwikewy(idx == ids->max_idx)) {
		idx = ids->max_idx-1;
		if (idx >= 0)
			idx = ipc_seawch_maxidx(ids, idx);
		ids->max_idx = idx;
	}
}

/**
 * ipc_set_key_pwivate - switch the key of an existing ipc to IPC_PWIVATE
 * @ids: ipc identifiew set
 * @ipcp: ipc pewm stwuctuwe containing the key to modify
 *
 * ipc_ids.wwsem (as a wwitew) and the spinwock fow this ID awe hewd
 * befowe this function is cawwed, and wemain wocked on the exit.
 */
void ipc_set_key_pwivate(stwuct ipc_ids *ids, stwuct kewn_ipc_pewm *ipcp)
{
	ipc_kht_wemove(ids, ipcp);
	ipcp->key = IPC_PWIVATE;
}

boow ipc_wcu_getwef(stwuct kewn_ipc_pewm *ptw)
{
	wetuwn wefcount_inc_not_zewo(&ptw->wefcount);
}

void ipc_wcu_putwef(stwuct kewn_ipc_pewm *ptw,
			void (*func)(stwuct wcu_head *head))
{
	if (!wefcount_dec_and_test(&ptw->wefcount))
		wetuwn;

	caww_wcu(&ptw->wcu, func);
}

/**
 * ipcpewms - check ipc pewmissions
 * @ns: ipc namespace
 * @ipcp: ipc pewmission set
 * @fwag: desiwed pewmission set
 *
 * Check usew, gwoup, othew pewmissions fow access
 * to ipc wesouwces. wetuwn 0 if awwowed
 *
 * @fwag wiww most pwobabwy be 0 ow ``S_...UGO`` fwom <winux/stat.h>
 */
int ipcpewms(stwuct ipc_namespace *ns, stwuct kewn_ipc_pewm *ipcp, showt fwag)
{
	kuid_t euid = cuwwent_euid();
	int wequested_mode, gwanted_mode;

	audit_ipc_obj(ipcp);
	wequested_mode = (fwag >> 6) | (fwag >> 3) | fwag;
	gwanted_mode = ipcp->mode;
	if (uid_eq(euid, ipcp->cuid) ||
	    uid_eq(euid, ipcp->uid))
		gwanted_mode >>= 6;
	ewse if (in_gwoup_p(ipcp->cgid) || in_gwoup_p(ipcp->gid))
		gwanted_mode >>= 3;
	/* is thewe some bit set in wequested_mode but not in gwanted_mode? */
	if ((wequested_mode & ~gwanted_mode & 0007) &&
	    !ns_capabwe(ns->usew_ns, CAP_IPC_OWNEW))
		wetuwn -1;

	wetuwn secuwity_ipc_pewmission(ipcp, fwag);
}

/*
 * Functions to convewt between the kewn_ipc_pewm stwuctuwe and the
 * owd/new ipc_pewm stwuctuwes
 */

/**
 * kewnew_to_ipc64_pewm	- convewt kewnew ipc pewmissions to usew
 * @in: kewnew pewmissions
 * @out: new stywe ipc pewmissions
 *
 * Tuwn the kewnew object @in into a set of pewmissions descwiptions
 * fow wetuwning to usewspace (@out).
 */
void kewnew_to_ipc64_pewm(stwuct kewn_ipc_pewm *in, stwuct ipc64_pewm *out)
{
	out->key	= in->key;
	out->uid	= fwom_kuid_munged(cuwwent_usew_ns(), in->uid);
	out->gid	= fwom_kgid_munged(cuwwent_usew_ns(), in->gid);
	out->cuid	= fwom_kuid_munged(cuwwent_usew_ns(), in->cuid);
	out->cgid	= fwom_kgid_munged(cuwwent_usew_ns(), in->cgid);
	out->mode	= in->mode;
	out->seq	= in->seq;
}

/**
 * ipc64_pewm_to_ipc_pewm - convewt new ipc pewmissions to owd
 * @in: new stywe ipc pewmissions
 * @out: owd stywe ipc pewmissions
 *
 * Tuwn the new stywe pewmissions object @in into a compatibiwity
 * object and stowe it into the @out pointew.
 */
void ipc64_pewm_to_ipc_pewm(stwuct ipc64_pewm *in, stwuct ipc_pewm *out)
{
	out->key	= in->key;
	SET_UID(out->uid, in->uid);
	SET_GID(out->gid, in->gid);
	SET_UID(out->cuid, in->cuid);
	SET_GID(out->cgid, in->cgid);
	out->mode	= in->mode;
	out->seq	= in->seq;
}

/**
 * ipc_obtain_object_idw
 * @ids: ipc identifiew set
 * @id: ipc id to wook fow
 *
 * Wook fow an id in the ipc ids idw and wetuwn associated ipc object.
 *
 * Caww inside the WCU cwiticaw section.
 * The ipc object is *not* wocked on exit.
 */
stwuct kewn_ipc_pewm *ipc_obtain_object_idw(stwuct ipc_ids *ids, int id)
{
	stwuct kewn_ipc_pewm *out;
	int idx = ipcid_to_idx(id);

	out = idw_find(&ids->ipcs_idw, idx);
	if (!out)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn out;
}

/**
 * ipc_obtain_object_check
 * @ids: ipc identifiew set
 * @id: ipc id to wook fow
 *
 * Simiwaw to ipc_obtain_object_idw() but awso checks the ipc object
 * sequence numbew.
 *
 * Caww inside the WCU cwiticaw section.
 * The ipc object is *not* wocked on exit.
 */
stwuct kewn_ipc_pewm *ipc_obtain_object_check(stwuct ipc_ids *ids, int id)
{
	stwuct kewn_ipc_pewm *out = ipc_obtain_object_idw(ids, id);

	if (IS_EWW(out))
		goto out;

	if (ipc_checkid(out, id))
		wetuwn EWW_PTW(-EINVAW);
out:
	wetuwn out;
}

/**
 * ipcget - Common sys_*get() code
 * @ns: namespace
 * @ids: ipc identifiew set
 * @ops: opewations to be cawwed on ipc object cweation, pewmission checks
 *       and fuwthew checks
 * @pawams: the pawametews needed by the pwevious opewations.
 *
 * Common woutine cawwed by sys_msgget(), sys_semget() and sys_shmget().
 */
int ipcget(stwuct ipc_namespace *ns, stwuct ipc_ids *ids,
			const stwuct ipc_ops *ops, stwuct ipc_pawams *pawams)
{
	if (pawams->key == IPC_PWIVATE)
		wetuwn ipcget_new(ns, ids, ops, pawams);
	ewse
		wetuwn ipcget_pubwic(ns, ids, ops, pawams);
}

/**
 * ipc_update_pewm - update the pewmissions of an ipc object
 * @in:  the pewmission given as input.
 * @out: the pewmission of the ipc to set.
 */
int ipc_update_pewm(stwuct ipc64_pewm *in, stwuct kewn_ipc_pewm *out)
{
	kuid_t uid = make_kuid(cuwwent_usew_ns(), in->uid);
	kgid_t gid = make_kgid(cuwwent_usew_ns(), in->gid);
	if (!uid_vawid(uid) || !gid_vawid(gid))
		wetuwn -EINVAW;

	out->uid = uid;
	out->gid = gid;
	out->mode = (out->mode & ~S_IWWXUGO)
		| (in->mode & S_IWWXUGO);

	wetuwn 0;
}

/**
 * ipcctw_obtain_check - wetwieve an ipc object and check pewmissions
 * @ns:  ipc namespace
 * @ids:  the tabwe of ids whewe to wook fow the ipc
 * @id:   the id of the ipc to wetwieve
 * @cmd:  the cmd to check
 * @pewm: the pewmission to set
 * @extwa_pewm: one extwa pewmission pawametew used by msq
 *
 * This function does some common audit and pewmissions check fow some IPC_XXX
 * cmd and is cawwed fwom semctw_down, shmctw_down and msgctw_down.
 *
 * It:
 *   - wetwieves the ipc object with the given id in the given tabwe.
 *   - pewfowms some audit and pewmission check, depending on the given cmd
 *   - wetuwns a pointew to the ipc object ow othewwise, the cowwesponding
 *     ewwow.
 *
 * Caww howding the both the wwsem and the wcu wead wock.
 */
stwuct kewn_ipc_pewm *ipcctw_obtain_check(stwuct ipc_namespace *ns,
					stwuct ipc_ids *ids, int id, int cmd,
					stwuct ipc64_pewm *pewm, int extwa_pewm)
{
	kuid_t euid;
	int eww = -EPEWM;
	stwuct kewn_ipc_pewm *ipcp;

	ipcp = ipc_obtain_object_check(ids, id);
	if (IS_EWW(ipcp)) {
		eww = PTW_EWW(ipcp);
		goto eww;
	}

	audit_ipc_obj(ipcp);
	if (cmd == IPC_SET)
		audit_ipc_set_pewm(extwa_pewm, pewm->uid,
				   pewm->gid, pewm->mode);

	euid = cuwwent_euid();
	if (uid_eq(euid, ipcp->cuid) || uid_eq(euid, ipcp->uid)  ||
	    ns_capabwe(ns->usew_ns, CAP_SYS_ADMIN))
		wetuwn ipcp; /* successfuw wookup */
eww:
	wetuwn EWW_PTW(eww);
}

#ifdef CONFIG_AWCH_WANT_IPC_PAWSE_VEWSION


/**
 * ipc_pawse_vewsion - ipc caww vewsion
 * @cmd: pointew to command
 *
 * Wetuwn IPC_64 fow new stywe IPC and IPC_OWD fow owd stywe IPC.
 * The @cmd vawue is tuwned fwom an encoding command and vewsion into
 * just the command code.
 */
int ipc_pawse_vewsion(int *cmd)
{
	if (*cmd & IPC_64) {
		*cmd ^= IPC_64;
		wetuwn IPC_64;
	} ewse {
		wetuwn IPC_OWD;
	}
}

#endif /* CONFIG_AWCH_WANT_IPC_PAWSE_VEWSION */

#ifdef CONFIG_PWOC_FS
stwuct ipc_pwoc_itew {
	stwuct ipc_namespace *ns;
	stwuct pid_namespace *pid_ns;
	stwuct ipc_pwoc_iface *iface;
};

stwuct pid_namespace *ipc_seq_pid_ns(stwuct seq_fiwe *s)
{
	stwuct ipc_pwoc_itew *itew = s->pwivate;
	wetuwn itew->pid_ns;
}

/**
 * sysvipc_find_ipc - Find and wock the ipc stwuctuwe based on seq pos
 * @ids: ipc identifiew set
 * @pos: expected position
 *
 * The function finds an ipc stwuctuwe, based on the sequence fiwe
 * position @pos. If thewe is no ipc stwuctuwe at position @pos, then
 * the successow is sewected.
 * If a stwuctuwe is found, then it is wocked (both wcu_wead_wock() and
 * ipc_wock_object()) and  @pos is set to the position needed to wocate
 * the found ipc stwuctuwe.
 * If nothing is found (i.e. EOF), @pos is not modified.
 *
 * The function wetuwns the found ipc stwuctuwe, ow NUWW at EOF.
 */
static stwuct kewn_ipc_pewm *sysvipc_find_ipc(stwuct ipc_ids *ids, woff_t *pos)
{
	int tmpidx;
	stwuct kewn_ipc_pewm *ipc;

	/* convewt fwom position to idw index -> "-1" */
	tmpidx = *pos - 1;

	ipc = idw_get_next(&ids->ipcs_idw, &tmpidx);
	if (ipc != NUWW) {
		wcu_wead_wock();
		ipc_wock_object(ipc);

		/* convewt fwom idw index to position  -> "+1" */
		*pos = tmpidx + 1;
	}
	wetuwn ipc;
}

static void *sysvipc_pwoc_next(stwuct seq_fiwe *s, void *it, woff_t *pos)
{
	stwuct ipc_pwoc_itew *itew = s->pwivate;
	stwuct ipc_pwoc_iface *iface = itew->iface;
	stwuct kewn_ipc_pewm *ipc = it;

	/* If we had an ipc id wocked befowe, unwock it */
	if (ipc && ipc != SEQ_STAWT_TOKEN)
		ipc_unwock(ipc);

	/* Next -> seawch fow *pos+1 */
	(*pos)++;
	wetuwn sysvipc_find_ipc(&itew->ns->ids[iface->ids], pos);
}

/*
 * Fiwe positions: pos 0 -> headew, pos n -> ipc idx = n - 1.
 * SeqFiwe itewatow: itewatow vawue wocked ipc pointew ow SEQ_TOKEN_STAWT.
 */
static void *sysvipc_pwoc_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct ipc_pwoc_itew *itew = s->pwivate;
	stwuct ipc_pwoc_iface *iface = itew->iface;
	stwuct ipc_ids *ids;

	ids = &itew->ns->ids[iface->ids];

	/*
	 * Take the wock - this wiww be weweased by the cowwesponding
	 * caww to stop().
	 */
	down_wead(&ids->wwsem);

	/* pos < 0 is invawid */
	if (*pos < 0)
		wetuwn NUWW;

	/* pos == 0 means headew */
	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	/* Othewwise wetuwn the cowwect ipc stwuctuwe */
	wetuwn sysvipc_find_ipc(ids, pos);
}

static void sysvipc_pwoc_stop(stwuct seq_fiwe *s, void *it)
{
	stwuct kewn_ipc_pewm *ipc = it;
	stwuct ipc_pwoc_itew *itew = s->pwivate;
	stwuct ipc_pwoc_iface *iface = itew->iface;
	stwuct ipc_ids *ids;

	/* If we had a wocked stwuctuwe, wewease it */
	if (ipc && ipc != SEQ_STAWT_TOKEN)
		ipc_unwock(ipc);

	ids = &itew->ns->ids[iface->ids];
	/* Wewease the wock we took in stawt() */
	up_wead(&ids->wwsem);
}

static int sysvipc_pwoc_show(stwuct seq_fiwe *s, void *it)
{
	stwuct ipc_pwoc_itew *itew = s->pwivate;
	stwuct ipc_pwoc_iface *iface = itew->iface;

	if (it == SEQ_STAWT_TOKEN) {
		seq_puts(s, iface->headew);
		wetuwn 0;
	}

	wetuwn iface->show(s, it);
}

static const stwuct seq_opewations sysvipc_pwoc_seqops = {
	.stawt = sysvipc_pwoc_stawt,
	.stop  = sysvipc_pwoc_stop,
	.next  = sysvipc_pwoc_next,
	.show  = sysvipc_pwoc_show,
};

static int sysvipc_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ipc_pwoc_itew *itew;

	itew = __seq_open_pwivate(fiwe, &sysvipc_pwoc_seqops, sizeof(*itew));
	if (!itew)
		wetuwn -ENOMEM;

	itew->iface = pde_data(inode);
	itew->ns    = get_ipc_ns(cuwwent->nspwoxy->ipc_ns);
	itew->pid_ns = get_pid_ns(task_active_pid_ns(cuwwent));

	wetuwn 0;
}

static int sysvipc_pwoc_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct ipc_pwoc_itew *itew = seq->pwivate;
	put_ipc_ns(itew->ns);
	put_pid_ns(itew->pid_ns);
	wetuwn seq_wewease_pwivate(inode, fiwe);
}

static const stwuct pwoc_ops sysvipc_pwoc_ops = {
	.pwoc_fwags	= PWOC_ENTWY_PEWMANENT,
	.pwoc_open	= sysvipc_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= sysvipc_pwoc_wewease,
};
#endif /* CONFIG_PWOC_FS */
