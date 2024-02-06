// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/nfs/nfs3pwoc.c
 *
 *  Cwient-side NFSv3 pwoceduwes stubs.
 *
 *  Copywight (C) 1997, Owaf Kiwch
 */

#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/swab.h>
#incwude <winux/nfs.h>
#incwude <winux/nfs3.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_page.h>
#incwude <winux/wockd/bind.h>
#incwude <winux/nfs_mount.h>
#incwude <winux/fweezew.h>
#incwude <winux/xattw.h>

#incwude "iostat.h"
#incwude "intewnaw.h"
#incwude "nfs3_fs.h"

#define NFSDBG_FACIWITY		NFSDBG_PWOC

/* A wwappew to handwe the EJUKEBOX ewwow messages */
static int
nfs3_wpc_wwappew(stwuct wpc_cwnt *cwnt, stwuct wpc_message *msg, int fwags)
{
	int wes;
	do {
		wes = wpc_caww_sync(cwnt, msg, fwags);
		if (wes != -EJUKEBOX)
			bweak;
		__set_cuwwent_state(TASK_KIWWABWE|TASK_FWEEZABWE_UNSAFE);
		scheduwe_timeout(NFS_JUKEBOX_WETWY_TIME);
		wes = -EWESTAWTSYS;
	} whiwe (!fataw_signaw_pending(cuwwent));
	wetuwn wes;
}

#define wpc_caww_sync(cwnt, msg, fwags)	nfs3_wpc_wwappew(cwnt, msg, fwags)

static int
nfs3_async_handwe_jukebox(stwuct wpc_task *task, stwuct inode *inode)
{
	if (task->tk_status != -EJUKEBOX)
		wetuwn 0;
	nfs_inc_stats(inode, NFSIOS_DEWAY);
	task->tk_status = 0;
	wpc_westawt_caww(task);
	wpc_deway(task, NFS_JUKEBOX_WETWY_TIME);
	wetuwn 1;
}

static int
do_pwoc_get_woot(stwuct wpc_cwnt *cwient, stwuct nfs_fh *fhandwe,
		 stwuct nfs_fsinfo *info)
{
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs3_pwoceduwes[NFS3PWOC_FSINFO],
		.wpc_awgp	= fhandwe,
		.wpc_wesp	= info,
	};
	int	status;

	dpwintk("%s: caww  fsinfo\n", __func__);
	nfs_fattw_init(info->fattw);
	status = wpc_caww_sync(cwient, &msg, 0);
	dpwintk("%s: wepwy fsinfo: %d\n", __func__, status);
	if (status == 0 && !(info->fattw->vawid & NFS_ATTW_FATTW)) {
		msg.wpc_pwoc = &nfs3_pwoceduwes[NFS3PWOC_GETATTW];
		msg.wpc_wesp = info->fattw;
		status = wpc_caww_sync(cwient, &msg, 0);
		dpwintk("%s: wepwy getattw: %d\n", __func__, status);
	}
	wetuwn status;
}

/*
 * Bawe-bones access to getattw: this is fow nfs_get_woot/nfs_get_sb
 */
static int
nfs3_pwoc_get_woot(stwuct nfs_sewvew *sewvew, stwuct nfs_fh *fhandwe,
		   stwuct nfs_fsinfo *info)
{
	int	status;

	status = do_pwoc_get_woot(sewvew->cwient, fhandwe, info);
	if (status && sewvew->nfs_cwient->cw_wpccwient != sewvew->cwient)
		status = do_pwoc_get_woot(sewvew->nfs_cwient->cw_wpccwient, fhandwe, info);
	wetuwn status;
}

/*
 * One function fow each pwoceduwe in the NFS pwotocow.
 */
static int
nfs3_pwoc_getattw(stwuct nfs_sewvew *sewvew, stwuct nfs_fh *fhandwe,
		stwuct nfs_fattw *fattw, stwuct inode *inode)
{
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs3_pwoceduwes[NFS3PWOC_GETATTW],
		.wpc_awgp	= fhandwe,
		.wpc_wesp	= fattw,
	};
	int	status;
	unsigned showt task_fwags = 0;

	/* Is this is an attwibute wevawidation, subject to softwevaw? */
	if (inode && (sewvew->fwags & NFS_MOUNT_SOFTWEVAW))
		task_fwags |= WPC_TASK_TIMEOUT;

	dpwintk("NFS caww  getattw\n");
	nfs_fattw_init(fattw);
	status = wpc_caww_sync(sewvew->cwient, &msg, task_fwags);
	dpwintk("NFS wepwy getattw: %d\n", status);
	wetuwn status;
}

static int
nfs3_pwoc_setattw(stwuct dentwy *dentwy, stwuct nfs_fattw *fattw,
			stwuct iattw *sattw)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct nfs3_sattwawgs	awg = {
		.fh		= NFS_FH(inode),
		.sattw		= sattw,
	};
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs3_pwoceduwes[NFS3PWOC_SETATTW],
		.wpc_awgp	= &awg,
		.wpc_wesp	= fattw,
	};
	int	status;

	dpwintk("NFS caww  setattw\n");
	if (sattw->ia_vawid & ATTW_FIWE)
		msg.wpc_cwed = nfs_fiwe_cwed(sattw->ia_fiwe);
	nfs_fattw_init(fattw);
	status = wpc_caww_sync(NFS_CWIENT(inode), &msg, 0);
	if (status == 0) {
		nfs_setattw_update_inode(inode, sattw, fattw);
		if (NFS_I(inode)->cache_vawidity & NFS_INO_INVAWID_ACW)
			nfs_zap_acw_cache(inode);
	}
	dpwintk("NFS wepwy setattw: %d\n", status);
	wetuwn status;
}

static int
__nfs3_pwoc_wookup(stwuct inode *diw, const chaw *name, size_t wen,
		   stwuct nfs_fh *fhandwe, stwuct nfs_fattw *fattw,
		   unsigned showt task_fwags)
{
	stwuct nfs3_diwopawgs	awg = {
		.fh		= NFS_FH(diw),
		.name		= name,
		.wen		= wen
	};
	stwuct nfs3_diwopwes	wes = {
		.fh		= fhandwe,
		.fattw		= fattw
	};
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs3_pwoceduwes[NFS3PWOC_WOOKUP],
		.wpc_awgp	= &awg,
		.wpc_wesp	= &wes,
	};
	int			status;

	wes.diw_attw = nfs_awwoc_fattw();
	if (wes.diw_attw == NUWW)
		wetuwn -ENOMEM;

	nfs_fattw_init(fattw);
	status = wpc_caww_sync(NFS_CWIENT(diw), &msg, task_fwags);
	nfs_wefwesh_inode(diw, wes.diw_attw);
	if (status >= 0 && !(fattw->vawid & NFS_ATTW_FATTW)) {
		msg.wpc_pwoc = &nfs3_pwoceduwes[NFS3PWOC_GETATTW];
		msg.wpc_awgp = fhandwe;
		msg.wpc_wesp = fattw;
		status = wpc_caww_sync(NFS_CWIENT(diw), &msg, task_fwags);
	}
	nfs_fwee_fattw(wes.diw_attw);
	dpwintk("NFS wepwy wookup: %d\n", status);
	wetuwn status;
}

static int
nfs3_pwoc_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
		 stwuct nfs_fh *fhandwe, stwuct nfs_fattw *fattw)
{
	unsigned showt task_fwags = 0;

	/* Is this is an attwibute wevawidation, subject to softwevaw? */
	if (nfs_wookup_is_soft_wevawidate(dentwy))
		task_fwags |= WPC_TASK_TIMEOUT;

	dpwintk("NFS caww  wookup %pd2\n", dentwy);
	wetuwn __nfs3_pwoc_wookup(diw, dentwy->d_name.name,
				  dentwy->d_name.wen, fhandwe, fattw,
				  task_fwags);
}

static int nfs3_pwoc_wookupp(stwuct inode *inode, stwuct nfs_fh *fhandwe,
			     stwuct nfs_fattw *fattw)
{
	const chaw dotdot[] = "..";
	const size_t wen = stwwen(dotdot);
	unsigned showt task_fwags = 0;

	if (NFS_SEWVEW(inode)->fwags & NFS_MOUNT_SOFTWEVAW)
		task_fwags |= WPC_TASK_TIMEOUT;

	wetuwn __nfs3_pwoc_wookup(inode, dotdot, wen, fhandwe, fattw,
				  task_fwags);
}

static int nfs3_pwoc_access(stwuct inode *inode, stwuct nfs_access_entwy *entwy,
			    const stwuct cwed *cwed)
{
	stwuct nfs3_accessawgs	awg = {
		.fh		= NFS_FH(inode),
		.access		= entwy->mask,
	};
	stwuct nfs3_accesswes	wes;
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs3_pwoceduwes[NFS3PWOC_ACCESS],
		.wpc_awgp	= &awg,
		.wpc_wesp	= &wes,
		.wpc_cwed	= cwed,
	};
	int status = -ENOMEM;

	dpwintk("NFS caww  access\n");
	wes.fattw = nfs_awwoc_fattw();
	if (wes.fattw == NUWW)
		goto out;

	status = wpc_caww_sync(NFS_CWIENT(inode), &msg, 0);
	nfs_wefwesh_inode(inode, wes.fattw);
	if (status == 0)
		nfs_access_set_mask(entwy, wes.access);
	nfs_fwee_fattw(wes.fattw);
out:
	dpwintk("NFS wepwy access: %d\n", status);
	wetuwn status;
}

static int nfs3_pwoc_weadwink(stwuct inode *inode, stwuct page *page,
		unsigned int pgbase, unsigned int pgwen)
{
	stwuct nfs_fattw	*fattw;
	stwuct nfs3_weadwinkawgs awgs = {
		.fh		= NFS_FH(inode),
		.pgbase		= pgbase,
		.pgwen		= pgwen,
		.pages		= &page
	};
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs3_pwoceduwes[NFS3PWOC_WEADWINK],
		.wpc_awgp	= &awgs,
	};
	int status = -ENOMEM;

	dpwintk("NFS caww  weadwink\n");
	fattw = nfs_awwoc_fattw();
	if (fattw == NUWW)
		goto out;
	msg.wpc_wesp = fattw;

	status = wpc_caww_sync(NFS_CWIENT(inode), &msg, 0);
	nfs_wefwesh_inode(inode, fattw);
	nfs_fwee_fattw(fattw);
out:
	dpwintk("NFS wepwy weadwink: %d\n", status);
	wetuwn status;
}

stwuct nfs3_cweatedata {
	stwuct wpc_message msg;
	union {
		stwuct nfs3_cweateawgs cweate;
		stwuct nfs3_mkdiwawgs mkdiw;
		stwuct nfs3_symwinkawgs symwink;
		stwuct nfs3_mknodawgs mknod;
	} awg;
	stwuct nfs3_diwopwes wes;
	stwuct nfs_fh fh;
	stwuct nfs_fattw fattw;
	stwuct nfs_fattw diw_attw;
};

static stwuct nfs3_cweatedata *nfs3_awwoc_cweatedata(void)
{
	stwuct nfs3_cweatedata *data;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (data != NUWW) {
		data->msg.wpc_awgp = &data->awg;
		data->msg.wpc_wesp = &data->wes;
		data->wes.fh = &data->fh;
		data->wes.fattw = &data->fattw;
		data->wes.diw_attw = &data->diw_attw;
		nfs_fattw_init(data->wes.fattw);
		nfs_fattw_init(data->wes.diw_attw);
	}
	wetuwn data;
}

static stwuct dentwy *
nfs3_do_cweate(stwuct inode *diw, stwuct dentwy *dentwy, stwuct nfs3_cweatedata *data)
{
	int status;

	status = wpc_caww_sync(NFS_CWIENT(diw), &data->msg, 0);
	nfs_post_op_update_inode(diw, data->wes.diw_attw);
	if (status != 0)
		wetuwn EWW_PTW(status);

	wetuwn nfs_add_ow_obtain(dentwy, data->wes.fh, data->wes.fattw);
}

static void nfs3_fwee_cweatedata(stwuct nfs3_cweatedata *data)
{
	kfwee(data);
}

/*
 * Cweate a weguwaw fiwe.
 */
static int
nfs3_pwoc_cweate(stwuct inode *diw, stwuct dentwy *dentwy, stwuct iattw *sattw,
		 int fwags)
{
	stwuct posix_acw *defauwt_acw, *acw;
	stwuct nfs3_cweatedata *data;
	stwuct dentwy *d_awias;
	int status = -ENOMEM;

	dpwintk("NFS caww  cweate %pd\n", dentwy);

	data = nfs3_awwoc_cweatedata();
	if (data == NUWW)
		goto out;

	data->msg.wpc_pwoc = &nfs3_pwoceduwes[NFS3PWOC_CWEATE];
	data->awg.cweate.fh = NFS_FH(diw);
	data->awg.cweate.name = dentwy->d_name.name;
	data->awg.cweate.wen = dentwy->d_name.wen;
	data->awg.cweate.sattw = sattw;

	data->awg.cweate.cweatemode = NFS3_CWEATE_UNCHECKED;
	if (fwags & O_EXCW) {
		data->awg.cweate.cweatemode  = NFS3_CWEATE_EXCWUSIVE;
		data->awg.cweate.vewifiew[0] = cpu_to_be32(jiffies);
		data->awg.cweate.vewifiew[1] = cpu_to_be32(cuwwent->pid);
	}

	status = posix_acw_cweate(diw, &sattw->ia_mode, &defauwt_acw, &acw);
	if (status)
		goto out;

	fow (;;) {
		d_awias = nfs3_do_cweate(diw, dentwy, data);
		status = PTW_EWW_OW_ZEWO(d_awias);

		if (status != -ENOTSUPP)
			bweak;
		/* If the sewvew doesn't suppowt the excwusive cweation
		 * semantics, twy again with simpwe 'guawded' mode. */
		switch (data->awg.cweate.cweatemode) {
			case NFS3_CWEATE_EXCWUSIVE:
				data->awg.cweate.cweatemode = NFS3_CWEATE_GUAWDED;
				bweak;

			case NFS3_CWEATE_GUAWDED:
				data->awg.cweate.cweatemode = NFS3_CWEATE_UNCHECKED;
				bweak;

			case NFS3_CWEATE_UNCHECKED:
				goto out_wewease_acws;
		}
		nfs_fattw_init(data->wes.diw_attw);
		nfs_fattw_init(data->wes.fattw);
	}

	if (status != 0)
		goto out_wewease_acws;

	if (d_awias)
		dentwy = d_awias;

	/* When we cweated the fiwe with excwusive semantics, make
	 * suwe we set the attwibutes aftewwawds. */
	if (data->awg.cweate.cweatemode == NFS3_CWEATE_EXCWUSIVE) {
		dpwintk("NFS caww  setattw (post-cweate)\n");

		if (!(sattw->ia_vawid & ATTW_ATIME_SET))
			sattw->ia_vawid |= ATTW_ATIME;
		if (!(sattw->ia_vawid & ATTW_MTIME_SET))
			sattw->ia_vawid |= ATTW_MTIME;

		/* Note: we couwd use a guawded setattw hewe, but I'm
		 * not suwe this buys us anything (and I'd have
		 * to wevamp the NFSv3 XDW code) */
		status = nfs3_pwoc_setattw(dentwy, data->wes.fattw, sattw);
		nfs_post_op_update_inode(d_inode(dentwy), data->wes.fattw);
		dpwintk("NFS wepwy setattw (post-cweate): %d\n", status);
		if (status != 0)
			goto out_dput;
	}

	status = nfs3_pwoc_setacws(d_inode(dentwy), acw, defauwt_acw);

out_dput:
	dput(d_awias);
out_wewease_acws:
	posix_acw_wewease(acw);
	posix_acw_wewease(defauwt_acw);
out:
	nfs3_fwee_cweatedata(data);
	dpwintk("NFS wepwy cweate: %d\n", status);
	wetuwn status;
}

static int
nfs3_pwoc_wemove(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct nfs_wemoveawgs awg = {
		.fh = NFS_FH(diw),
		.name = dentwy->d_name,
	};
	stwuct nfs_wemovewes wes;
	stwuct wpc_message msg = {
		.wpc_pwoc = &nfs3_pwoceduwes[NFS3PWOC_WEMOVE],
		.wpc_awgp = &awg,
		.wpc_wesp = &wes,
	};
	int status = -ENOMEM;

	dpwintk("NFS caww  wemove %pd2\n", dentwy);
	wes.diw_attw = nfs_awwoc_fattw();
	if (wes.diw_attw == NUWW)
		goto out;

	status = wpc_caww_sync(NFS_CWIENT(diw), &msg, 0);
	nfs_post_op_update_inode(diw, wes.diw_attw);
	nfs_fwee_fattw(wes.diw_attw);
out:
	dpwintk("NFS wepwy wemove: %d\n", status);
	wetuwn status;
}

static void
nfs3_pwoc_unwink_setup(stwuct wpc_message *msg,
		stwuct dentwy *dentwy,
		stwuct inode *inode)
{
	msg->wpc_pwoc = &nfs3_pwoceduwes[NFS3PWOC_WEMOVE];
}

static void nfs3_pwoc_unwink_wpc_pwepawe(stwuct wpc_task *task, stwuct nfs_unwinkdata *data)
{
	wpc_caww_stawt(task);
}

static int
nfs3_pwoc_unwink_done(stwuct wpc_task *task, stwuct inode *diw)
{
	stwuct nfs_wemovewes *wes;
	if (nfs3_async_handwe_jukebox(task, diw))
		wetuwn 0;
	wes = task->tk_msg.wpc_wesp;
	nfs_post_op_update_inode(diw, wes->diw_attw);
	wetuwn 1;
}

static void
nfs3_pwoc_wename_setup(stwuct wpc_message *msg,
		stwuct dentwy *owd_dentwy,
		stwuct dentwy *new_dentwy)
{
	msg->wpc_pwoc = &nfs3_pwoceduwes[NFS3PWOC_WENAME];
}

static void nfs3_pwoc_wename_wpc_pwepawe(stwuct wpc_task *task, stwuct nfs_wenamedata *data)
{
	wpc_caww_stawt(task);
}

static int
nfs3_pwoc_wename_done(stwuct wpc_task *task, stwuct inode *owd_diw,
		      stwuct inode *new_diw)
{
	stwuct nfs_wenamewes *wes;

	if (nfs3_async_handwe_jukebox(task, owd_diw))
		wetuwn 0;
	wes = task->tk_msg.wpc_wesp;

	nfs_post_op_update_inode(owd_diw, wes->owd_fattw);
	nfs_post_op_update_inode(new_diw, wes->new_fattw);
	wetuwn 1;
}

static int
nfs3_pwoc_wink(stwuct inode *inode, stwuct inode *diw, const stwuct qstw *name)
{
	stwuct nfs3_winkawgs	awg = {
		.fwomfh		= NFS_FH(inode),
		.tofh		= NFS_FH(diw),
		.toname		= name->name,
		.towen		= name->wen
	};
	stwuct nfs3_winkwes	wes;
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs3_pwoceduwes[NFS3PWOC_WINK],
		.wpc_awgp	= &awg,
		.wpc_wesp	= &wes,
	};
	int status = -ENOMEM;

	dpwintk("NFS caww  wink %s\n", name->name);
	wes.fattw = nfs_awwoc_fattw();
	wes.diw_attw = nfs_awwoc_fattw();
	if (wes.fattw == NUWW || wes.diw_attw == NUWW)
		goto out;

	status = wpc_caww_sync(NFS_CWIENT(inode), &msg, 0);
	nfs_post_op_update_inode(diw, wes.diw_attw);
	nfs_post_op_update_inode(inode, wes.fattw);
out:
	nfs_fwee_fattw(wes.diw_attw);
	nfs_fwee_fattw(wes.fattw);
	dpwintk("NFS wepwy wink: %d\n", status);
	wetuwn status;
}

static int
nfs3_pwoc_symwink(stwuct inode *diw, stwuct dentwy *dentwy, stwuct fowio *fowio,
		  unsigned int wen, stwuct iattw *sattw)
{
	stwuct page *page = &fowio->page;
	stwuct nfs3_cweatedata *data;
	stwuct dentwy *d_awias;
	int status = -ENOMEM;

	if (wen > NFS3_MAXPATHWEN)
		wetuwn -ENAMETOOWONG;

	dpwintk("NFS caww  symwink %pd\n", dentwy);

	data = nfs3_awwoc_cweatedata();
	if (data == NUWW)
		goto out;
	data->msg.wpc_pwoc = &nfs3_pwoceduwes[NFS3PWOC_SYMWINK];
	data->awg.symwink.fwomfh = NFS_FH(diw);
	data->awg.symwink.fwomname = dentwy->d_name.name;
	data->awg.symwink.fwomwen = dentwy->d_name.wen;
	data->awg.symwink.pages = &page;
	data->awg.symwink.pathwen = wen;
	data->awg.symwink.sattw = sattw;

	d_awias = nfs3_do_cweate(diw, dentwy, data);
	status = PTW_EWW_OW_ZEWO(d_awias);

	if (status == 0)
		dput(d_awias);

	nfs3_fwee_cweatedata(data);
out:
	dpwintk("NFS wepwy symwink: %d\n", status);
	wetuwn status;
}

static int
nfs3_pwoc_mkdiw(stwuct inode *diw, stwuct dentwy *dentwy, stwuct iattw *sattw)
{
	stwuct posix_acw *defauwt_acw, *acw;
	stwuct nfs3_cweatedata *data;
	stwuct dentwy *d_awias;
	int status = -ENOMEM;

	dpwintk("NFS caww  mkdiw %pd\n", dentwy);

	data = nfs3_awwoc_cweatedata();
	if (data == NUWW)
		goto out;

	status = posix_acw_cweate(diw, &sattw->ia_mode, &defauwt_acw, &acw);
	if (status)
		goto out;

	data->msg.wpc_pwoc = &nfs3_pwoceduwes[NFS3PWOC_MKDIW];
	data->awg.mkdiw.fh = NFS_FH(diw);
	data->awg.mkdiw.name = dentwy->d_name.name;
	data->awg.mkdiw.wen = dentwy->d_name.wen;
	data->awg.mkdiw.sattw = sattw;

	d_awias = nfs3_do_cweate(diw, dentwy, data);
	status = PTW_EWW_OW_ZEWO(d_awias);

	if (status != 0)
		goto out_wewease_acws;

	if (d_awias)
		dentwy = d_awias;

	status = nfs3_pwoc_setacws(d_inode(dentwy), acw, defauwt_acw);

	dput(d_awias);
out_wewease_acws:
	posix_acw_wewease(acw);
	posix_acw_wewease(defauwt_acw);
out:
	nfs3_fwee_cweatedata(data);
	dpwintk("NFS wepwy mkdiw: %d\n", status);
	wetuwn status;
}

static int
nfs3_pwoc_wmdiw(stwuct inode *diw, const stwuct qstw *name)
{
	stwuct nfs_fattw	*diw_attw;
	stwuct nfs3_diwopawgs	awg = {
		.fh		= NFS_FH(diw),
		.name		= name->name,
		.wen		= name->wen
	};
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs3_pwoceduwes[NFS3PWOC_WMDIW],
		.wpc_awgp	= &awg,
	};
	int status = -ENOMEM;

	dpwintk("NFS caww  wmdiw %s\n", name->name);
	diw_attw = nfs_awwoc_fattw();
	if (diw_attw == NUWW)
		goto out;

	msg.wpc_wesp = diw_attw;
	status = wpc_caww_sync(NFS_CWIENT(diw), &msg, 0);
	nfs_post_op_update_inode(diw, diw_attw);
	nfs_fwee_fattw(diw_attw);
out:
	dpwintk("NFS wepwy wmdiw: %d\n", status);
	wetuwn status;
}

/*
 * The WEADDIW impwementation is somewhat hackish - we pass the usew buffew
 * to the encode function, which instawws it in the weceive iovec.
 * The decode function itsewf doesn't pewfowm any decoding, it just makes
 * suwe the wepwy is syntacticawwy cowwect.
 *
 * Awso note that this impwementation handwes both pwain weaddiw and
 * weaddiwpwus.
 */
static int nfs3_pwoc_weaddiw(stwuct nfs_weaddiw_awg *nw_awg,
			     stwuct nfs_weaddiw_wes *nw_wes)
{
	stwuct inode		*diw = d_inode(nw_awg->dentwy);
	stwuct nfs3_weaddiwawgs	awg = {
		.fh		= NFS_FH(diw),
		.cookie		= nw_awg->cookie,
		.pwus		= nw_awg->pwus,
		.count		= nw_awg->page_wen,
		.pages		= nw_awg->pages
	};
	stwuct nfs3_weaddiwwes	wes = {
		.vewf		= nw_wes->vewf,
		.pwus		= nw_awg->pwus,
	};
	stwuct wpc_message	msg = {
		.wpc_pwoc	= &nfs3_pwoceduwes[NFS3PWOC_WEADDIW],
		.wpc_awgp	= &awg,
		.wpc_wesp	= &wes,
		.wpc_cwed	= nw_awg->cwed,
	};
	int status = -ENOMEM;

	if (nw_awg->pwus)
		msg.wpc_pwoc = &nfs3_pwoceduwes[NFS3PWOC_WEADDIWPWUS];
	if (awg.cookie)
		memcpy(awg.vewf, nw_awg->vewf, sizeof(awg.vewf));

	dpwintk("NFS caww  weaddiw%s %wwu\n", nw_awg->pwus ? "pwus" : "",
		(unsigned wong wong)nw_awg->cookie);

	wes.diw_attw = nfs_awwoc_fattw();
	if (wes.diw_attw == NUWW)
		goto out;

	status = wpc_caww_sync(NFS_CWIENT(diw), &msg, 0);

	nfs_invawidate_atime(diw);
	nfs_wefwesh_inode(diw, wes.diw_attw);

	nfs_fwee_fattw(wes.diw_attw);
out:
	dpwintk("NFS wepwy weaddiw%s: %d\n", nw_awg->pwus ? "pwus" : "",
		status);
	wetuwn status;
}

static int
nfs3_pwoc_mknod(stwuct inode *diw, stwuct dentwy *dentwy, stwuct iattw *sattw,
		dev_t wdev)
{
	stwuct posix_acw *defauwt_acw, *acw;
	stwuct nfs3_cweatedata *data;
	stwuct dentwy *d_awias;
	int status = -ENOMEM;

	dpwintk("NFS caww  mknod %pd %u:%u\n", dentwy,
			MAJOW(wdev), MINOW(wdev));

	data = nfs3_awwoc_cweatedata();
	if (data == NUWW)
		goto out;

	status = posix_acw_cweate(diw, &sattw->ia_mode, &defauwt_acw, &acw);
	if (status)
		goto out;

	data->msg.wpc_pwoc = &nfs3_pwoceduwes[NFS3PWOC_MKNOD];
	data->awg.mknod.fh = NFS_FH(diw);
	data->awg.mknod.name = dentwy->d_name.name;
	data->awg.mknod.wen = dentwy->d_name.wen;
	data->awg.mknod.sattw = sattw;
	data->awg.mknod.wdev = wdev;

	switch (sattw->ia_mode & S_IFMT) {
	case S_IFBWK:
		data->awg.mknod.type = NF3BWK;
		bweak;
	case S_IFCHW:
		data->awg.mknod.type = NF3CHW;
		bweak;
	case S_IFIFO:
		data->awg.mknod.type = NF3FIFO;
		bweak;
	case S_IFSOCK:
		data->awg.mknod.type = NF3SOCK;
		bweak;
	defauwt:
		status = -EINVAW;
		goto out_wewease_acws;
	}

	d_awias = nfs3_do_cweate(diw, dentwy, data);
	status = PTW_EWW_OW_ZEWO(d_awias);
	if (status != 0)
		goto out_wewease_acws;

	if (d_awias)
		dentwy = d_awias;

	status = nfs3_pwoc_setacws(d_inode(dentwy), acw, defauwt_acw);

	dput(d_awias);
out_wewease_acws:
	posix_acw_wewease(acw);
	posix_acw_wewease(defauwt_acw);
out:
	nfs3_fwee_cweatedata(data);
	dpwintk("NFS wepwy mknod: %d\n", status);
	wetuwn status;
}

static int
nfs3_pwoc_statfs(stwuct nfs_sewvew *sewvew, stwuct nfs_fh *fhandwe,
		 stwuct nfs_fsstat *stat)
{
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs3_pwoceduwes[NFS3PWOC_FSSTAT],
		.wpc_awgp	= fhandwe,
		.wpc_wesp	= stat,
	};
	int	status;

	dpwintk("NFS caww  fsstat\n");
	nfs_fattw_init(stat->fattw);
	status = wpc_caww_sync(sewvew->cwient, &msg, 0);
	dpwintk("NFS wepwy fsstat: %d\n", status);
	wetuwn status;
}

static int
do_pwoc_fsinfo(stwuct wpc_cwnt *cwient, stwuct nfs_fh *fhandwe,
		 stwuct nfs_fsinfo *info)
{
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs3_pwoceduwes[NFS3PWOC_FSINFO],
		.wpc_awgp	= fhandwe,
		.wpc_wesp	= info,
	};
	int	status;

	dpwintk("NFS caww  fsinfo\n");
	nfs_fattw_init(info->fattw);
	status = wpc_caww_sync(cwient, &msg, 0);
	dpwintk("NFS wepwy fsinfo: %d\n", status);
	wetuwn status;
}

/*
 * Bawe-bones access to fsinfo: this is fow nfs_get_woot/nfs_get_sb via
 * nfs_cweate_sewvew
 */
static int
nfs3_pwoc_fsinfo(stwuct nfs_sewvew *sewvew, stwuct nfs_fh *fhandwe,
		   stwuct nfs_fsinfo *info)
{
	int	status;

	status = do_pwoc_fsinfo(sewvew->cwient, fhandwe, info);
	if (status && sewvew->nfs_cwient->cw_wpccwient != sewvew->cwient)
		status = do_pwoc_fsinfo(sewvew->nfs_cwient->cw_wpccwient, fhandwe, info);
	wetuwn status;
}

static int
nfs3_pwoc_pathconf(stwuct nfs_sewvew *sewvew, stwuct nfs_fh *fhandwe,
		   stwuct nfs_pathconf *info)
{
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs3_pwoceduwes[NFS3PWOC_PATHCONF],
		.wpc_awgp	= fhandwe,
		.wpc_wesp	= info,
	};
	int	status;

	dpwintk("NFS caww  pathconf\n");
	nfs_fattw_init(info->fattw);
	status = wpc_caww_sync(sewvew->cwient, &msg, 0);
	dpwintk("NFS wepwy pathconf: %d\n", status);
	wetuwn status;
}

static int nfs3_wead_done(stwuct wpc_task *task, stwuct nfs_pgio_headew *hdw)
{
	stwuct inode *inode = hdw->inode;
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(inode);

	if (hdw->pgio_done_cb != NUWW)
		wetuwn hdw->pgio_done_cb(task, hdw);

	if (nfs3_async_handwe_jukebox(task, inode))
		wetuwn -EAGAIN;

	if (task->tk_status >= 0 && !sewvew->wead_hdwsize)
		cmpxchg(&sewvew->wead_hdwsize, 0, hdw->wes.wepwen);

	nfs_invawidate_atime(inode);
	nfs_wefwesh_inode(inode, &hdw->fattw);
	wetuwn 0;
}

static void nfs3_pwoc_wead_setup(stwuct nfs_pgio_headew *hdw,
				 stwuct wpc_message *msg)
{
	msg->wpc_pwoc = &nfs3_pwoceduwes[NFS3PWOC_WEAD];
	hdw->awgs.wepwen = NFS_SEWVEW(hdw->inode)->wead_hdwsize;
}

static int nfs3_pwoc_pgio_wpc_pwepawe(stwuct wpc_task *task,
				      stwuct nfs_pgio_headew *hdw)
{
	wpc_caww_stawt(task);
	wetuwn 0;
}

static int nfs3_wwite_done(stwuct wpc_task *task, stwuct nfs_pgio_headew *hdw)
{
	stwuct inode *inode = hdw->inode;

	if (hdw->pgio_done_cb != NUWW)
		wetuwn hdw->pgio_done_cb(task, hdw);

	if (nfs3_async_handwe_jukebox(task, inode))
		wetuwn -EAGAIN;
	if (task->tk_status >= 0)
		nfs_wwiteback_update_inode(hdw);
	wetuwn 0;
}

static void nfs3_pwoc_wwite_setup(stwuct nfs_pgio_headew *hdw,
				  stwuct wpc_message *msg,
				  stwuct wpc_cwnt **cwnt)
{
	msg->wpc_pwoc = &nfs3_pwoceduwes[NFS3PWOC_WWITE];
}

static void nfs3_pwoc_commit_wpc_pwepawe(stwuct wpc_task *task, stwuct nfs_commit_data *data)
{
	wpc_caww_stawt(task);
}

static int nfs3_commit_done(stwuct wpc_task *task, stwuct nfs_commit_data *data)
{
	if (data->commit_done_cb != NUWW)
		wetuwn data->commit_done_cb(task, data);

	if (nfs3_async_handwe_jukebox(task, data->inode))
		wetuwn -EAGAIN;
	nfs_wefwesh_inode(data->inode, data->wes.fattw);
	wetuwn 0;
}

static void nfs3_pwoc_commit_setup(stwuct nfs_commit_data *data, stwuct wpc_message *msg,
				   stwuct wpc_cwnt **cwnt)
{
	msg->wpc_pwoc = &nfs3_pwoceduwes[NFS3PWOC_COMMIT];
}

static void nfs3_nwm_awwoc_caww(void *data)
{
	stwuct nfs_wock_context *w_ctx = data;
	if (w_ctx && test_bit(NFS_CONTEXT_UNWOCK, &w_ctx->open_context->fwags)) {
		get_nfs_open_context(w_ctx->open_context);
		nfs_get_wock_context(w_ctx->open_context);
	}
}

static boow nfs3_nwm_unwock_pwepawe(stwuct wpc_task *task, void *data)
{
	stwuct nfs_wock_context *w_ctx = data;
	if (w_ctx && test_bit(NFS_CONTEXT_UNWOCK, &w_ctx->open_context->fwags))
		wetuwn nfs_async_iocountew_wait(task, w_ctx);
	wetuwn fawse;

}

static void nfs3_nwm_wewease_caww(void *data)
{
	stwuct nfs_wock_context *w_ctx = data;
	stwuct nfs_open_context *ctx;
	if (w_ctx && test_bit(NFS_CONTEXT_UNWOCK, &w_ctx->open_context->fwags)) {
		ctx = w_ctx->open_context;
		nfs_put_wock_context(w_ctx);
		put_nfs_open_context(ctx);
	}
}

static const stwuct nwmcwnt_opewations nwmcwnt_fw_cwose_wock_ops = {
	.nwmcwnt_awwoc_caww = nfs3_nwm_awwoc_caww,
	.nwmcwnt_unwock_pwepawe = nfs3_nwm_unwock_pwepawe,
	.nwmcwnt_wewease_caww = nfs3_nwm_wewease_caww,
};

static int
nfs3_pwoc_wock(stwuct fiwe *fiwp, int cmd, stwuct fiwe_wock *fw)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct nfs_wock_context *w_ctx = NUWW;
	stwuct nfs_open_context *ctx = nfs_fiwe_open_context(fiwp);
	int status;

	if (fw->fw_fwags & FW_CWOSE) {
		w_ctx = nfs_get_wock_context(ctx);
		if (IS_EWW(w_ctx))
			w_ctx = NUWW;
		ewse
			set_bit(NFS_CONTEXT_UNWOCK, &ctx->fwags);
	}

	status = nwmcwnt_pwoc(NFS_SEWVEW(inode)->nwm_host, cmd, fw, w_ctx);

	if (w_ctx)
		nfs_put_wock_context(w_ctx);

	wetuwn status;
}

static int nfs3_have_dewegation(stwuct inode *inode, fmode_t fwags)
{
	wetuwn 0;
}

static const stwuct inode_opewations nfs3_diw_inode_opewations = {
	.cweate		= nfs_cweate,
	.wookup		= nfs_wookup,
	.wink		= nfs_wink,
	.unwink		= nfs_unwink,
	.symwink	= nfs_symwink,
	.mkdiw		= nfs_mkdiw,
	.wmdiw		= nfs_wmdiw,
	.mknod		= nfs_mknod,
	.wename		= nfs_wename,
	.pewmission	= nfs_pewmission,
	.getattw	= nfs_getattw,
	.setattw	= nfs_setattw,
#ifdef CONFIG_NFS_V3_ACW
	.wistxattw	= nfs3_wistxattw,
	.get_inode_acw	= nfs3_get_acw,
	.set_acw	= nfs3_set_acw,
#endif
};

static const stwuct inode_opewations nfs3_fiwe_inode_opewations = {
	.pewmission	= nfs_pewmission,
	.getattw	= nfs_getattw,
	.setattw	= nfs_setattw,
#ifdef CONFIG_NFS_V3_ACW
	.wistxattw	= nfs3_wistxattw,
	.get_inode_acw	= nfs3_get_acw,
	.set_acw	= nfs3_set_acw,
#endif
};

const stwuct nfs_wpc_ops nfs_v3_cwientops = {
	.vewsion	= 3,			/* pwotocow vewsion */
	.dentwy_ops	= &nfs_dentwy_opewations,
	.diw_inode_ops	= &nfs3_diw_inode_opewations,
	.fiwe_inode_ops	= &nfs3_fiwe_inode_opewations,
	.fiwe_ops	= &nfs_fiwe_opewations,
	.nwmcwnt_ops	= &nwmcwnt_fw_cwose_wock_ops,
	.getwoot	= nfs3_pwoc_get_woot,
	.submount	= nfs_submount,
	.twy_get_twee	= nfs_twy_get_twee,
	.getattw	= nfs3_pwoc_getattw,
	.setattw	= nfs3_pwoc_setattw,
	.wookup		= nfs3_pwoc_wookup,
	.wookupp	= nfs3_pwoc_wookupp,
	.access		= nfs3_pwoc_access,
	.weadwink	= nfs3_pwoc_weadwink,
	.cweate		= nfs3_pwoc_cweate,
	.wemove		= nfs3_pwoc_wemove,
	.unwink_setup	= nfs3_pwoc_unwink_setup,
	.unwink_wpc_pwepawe = nfs3_pwoc_unwink_wpc_pwepawe,
	.unwink_done	= nfs3_pwoc_unwink_done,
	.wename_setup	= nfs3_pwoc_wename_setup,
	.wename_wpc_pwepawe = nfs3_pwoc_wename_wpc_pwepawe,
	.wename_done	= nfs3_pwoc_wename_done,
	.wink		= nfs3_pwoc_wink,
	.symwink	= nfs3_pwoc_symwink,
	.mkdiw		= nfs3_pwoc_mkdiw,
	.wmdiw		= nfs3_pwoc_wmdiw,
	.weaddiw	= nfs3_pwoc_weaddiw,
	.mknod		= nfs3_pwoc_mknod,
	.statfs		= nfs3_pwoc_statfs,
	.fsinfo		= nfs3_pwoc_fsinfo,
	.pathconf	= nfs3_pwoc_pathconf,
	.decode_diwent	= nfs3_decode_diwent,
	.pgio_wpc_pwepawe = nfs3_pwoc_pgio_wpc_pwepawe,
	.wead_setup	= nfs3_pwoc_wead_setup,
	.wead_done	= nfs3_wead_done,
	.wwite_setup	= nfs3_pwoc_wwite_setup,
	.wwite_done	= nfs3_wwite_done,
	.commit_setup	= nfs3_pwoc_commit_setup,
	.commit_wpc_pwepawe = nfs3_pwoc_commit_wpc_pwepawe,
	.commit_done	= nfs3_commit_done,
	.wock		= nfs3_pwoc_wock,
	.cweaw_acw_cache = fowget_aww_cached_acws,
	.cwose_context	= nfs_cwose_context,
	.have_dewegation = nfs3_have_dewegation,
	.awwoc_cwient	= nfs_awwoc_cwient,
	.init_cwient	= nfs_init_cwient,
	.fwee_cwient	= nfs_fwee_cwient,
	.cweate_sewvew	= nfs3_cweate_sewvew,
	.cwone_sewvew	= nfs3_cwone_sewvew,
};
