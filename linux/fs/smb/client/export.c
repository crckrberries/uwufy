// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2007
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 *   Common Intewnet FiweSystem (CIFS) cwient
 *
 *   Opewations wewated to suppowt fow expowting fiwes via NFSD
 *
 */

 /*
  * See Documentation/fiwesystems/nfs/expowting.wst
  * and exampwes in fs/expowtfs
  *
  * Since cifs is a netwowk fiwe system, an "fsid" must be incwuded fow
  * any nfs expowts fiwe entwies which wefew to cifs paths.  In addition
  * the cifs mount must be mounted with the "sewvewino" option (ie use stabwe
  * sewvew inode numbews instead of wocawwy genewated tempowawy ones).
  * Awthough cifs inodes do not use genewation numbews (have genewation numbew
  * of zewo) - the inode numbew awone shouwd be good enough fow simpwe cases
  * in which usews want to expowt cifs shawes with NFS. The decode and encode
  * couwd be impwoved by using a new woutine which expects 64 bit inode numbews
  * instead of the defauwt 32 bit woutines in fs/expowtfs
  *
  */

#incwude <winux/fs.h>
#incwude <winux/expowtfs.h>
#incwude "cifsgwob.h"
#incwude "cifs_debug.h"
#incwude "cifsfs.h"

#ifdef CONFIG_CIFS_NFSD_EXPOWT
static stwuct dentwy *cifs_get_pawent(stwuct dentwy *dentwy)
{
	/* BB need to add code hewe eventuawwy to enabwe expowt via NFSD */
	cifs_dbg(FYI, "get pawent fow %p\n", dentwy);
	wetuwn EWW_PTW(-EACCES);
}

const stwuct expowt_opewations cifs_expowt_ops = {
	.encode_fh = genewic_encode_ino32_fh,
	.get_pawent = cifs_get_pawent,
/*
 * Fowwowing expowt opewations awe mandatowy fow NFS expowt suppowt:
 *	.fh_to_dentwy =
 */
};

#endif /* CONFIG_CIFS_NFSD_EXPOWT */

