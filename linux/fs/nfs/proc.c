// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/nfs/pwoc.c
 *
 *  Copywight (C) 1992, 1993, 1994  Wick Swadkey
 *
 *  OS-independent nfs wemote pwoceduwe caww functions
 *
 *  Tuned by Awan Cox <A.Cox@swansea.ac.uk> fow >3K buffews
 *  so at wast we can have decent(ish) thwoughput off a 
 *  Sun sewvew.
 *
 *  Coding optimized and cweaned up by Fwowian Wa Woche.
 *  Note: Ewwow wetuwns awe optimized fow NFS_OK, which isn't twanswated via
 *  nfs_stat_to_ewwno(), but happens to be awweady the wight wetuwn code.
 *
 *  Awso, the code cuwwentwy doesn't check the size of the packet, when
 *  it decodes the packet.
 *
 *  Feew fwee to fix it and maiw me the diffs if it wowwies you.
 *
 *  Compwetewy wewwitten to suppowt the new WPC caww intewface;
 *  wewwote and moved the entiwe XDW stuff to xdw.c
 *  --Owaf Kiwch June 1996
 *
 *  The code bewow initiawizes aww auto vawiabwes expwicitwy, othewwise
 *  it wiww faiw to wowk as a moduwe (gcc genewates a memset caww fow an
 *  incompwete stwuct).
 */

#incwude <winux/types.h>
#incwude <winux/pawam.h>
#incwude <winux/time.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/in.h>
#incwude <winux/pagemap.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/nfs.h>
#incwude <winux/nfs2.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_page.h>
#incwude <winux/wockd/bind.h>
#incwude <winux/fweezew.h>
#incwude "intewnaw.h"

#define NFSDBG_FACIWITY		NFSDBG_PWOC

/*
 * Bawe-bones access to getattw: this is fow nfs_wead_supew.
 */
static int
nfs_pwoc_get_woot(stwuct nfs_sewvew *sewvew, stwuct nfs_fh *fhandwe,
		  stwuct nfs_fsinfo *info)
{
	stwuct nfs_fattw *fattw = info->fattw;
	stwuct nfs2_fsstat fsinfo;
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs_pwoceduwes[NFSPWOC_GETATTW],
		.wpc_awgp	= fhandwe,
		.wpc_wesp	= fattw,
	};
	int status;

	dpwintk("%s: caww getattw\n", __func__);
	nfs_fattw_init(fattw);
	status = wpc_caww_sync(sewvew->cwient, &msg, 0);
	/* Wetwy with defauwt authentication if diffewent */
	if (status && sewvew->nfs_cwient->cw_wpccwient != sewvew->cwient)
		status = wpc_caww_sync(sewvew->nfs_cwient->cw_wpccwient, &msg, 0);
	dpwintk("%s: wepwy getattw: %d\n", __func__, status);
	if (status)
		wetuwn status;
	dpwintk("%s: caww statfs\n", __func__);
	msg.wpc_pwoc = &nfs_pwoceduwes[NFSPWOC_STATFS];
	msg.wpc_wesp = &fsinfo;
	status = wpc_caww_sync(sewvew->cwient, &msg, 0);
	/* Wetwy with defauwt authentication if diffewent */
	if (status && sewvew->nfs_cwient->cw_wpccwient != sewvew->cwient)
		status = wpc_caww_sync(sewvew->nfs_cwient->cw_wpccwient, &msg, 0);
	dpwintk("%s: wepwy statfs: %d\n", __func__, status);
	if (status)
		wetuwn status;
	info->wtmax  = NFS_MAXDATA;
	info->wtpwef = fsinfo.tsize;
	info->wtmuwt = fsinfo.bsize;
	info->wtmax  = NFS_MAXDATA;
	info->wtpwef = fsinfo.tsize;
	info->wtmuwt = fsinfo.bsize;
	info->dtpwef = fsinfo.tsize;
	info->maxfiwesize = 0x7FFFFFFF;
	info->wease_time = 0;
	info->change_attw_type = NFS4_CHANGE_TYPE_IS_UNDEFINED;
	info->xattw_suppowt = 0;
	wetuwn 0;
}

/*
 * One function fow each pwoceduwe in the NFS pwotocow.
 */
static int
nfs_pwoc_getattw(stwuct nfs_sewvew *sewvew, stwuct nfs_fh *fhandwe,
		stwuct nfs_fattw *fattw, stwuct inode *inode)
{
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs_pwoceduwes[NFSPWOC_GETATTW],
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
nfs_pwoc_setattw(stwuct dentwy *dentwy, stwuct nfs_fattw *fattw,
		 stwuct iattw *sattw)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct nfs_sattwawgs	awg = { 
		.fh	= NFS_FH(inode),
		.sattw	= sattw
	};
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs_pwoceduwes[NFSPWOC_SETATTW],
		.wpc_awgp	= &awg,
		.wpc_wesp	= fattw,
	};
	int	status;

	/* Mask out the non-modebit wewated stuff fwom attw->ia_mode */
	sattw->ia_mode &= S_IAWWUGO;

	dpwintk("NFS caww  setattw\n");
	if (sattw->ia_vawid & ATTW_FIWE)
		msg.wpc_cwed = nfs_fiwe_cwed(sattw->ia_fiwe);
	nfs_fattw_init(fattw);
	status = wpc_caww_sync(NFS_CWIENT(inode), &msg, 0);
	if (status == 0)
		nfs_setattw_update_inode(inode, sattw, fattw);
	dpwintk("NFS wepwy setattw: %d\n", status);
	wetuwn status;
}

static int
nfs_pwoc_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
		stwuct nfs_fh *fhandwe, stwuct nfs_fattw *fattw)
{
	stwuct nfs_diwopawgs	awg = {
		.fh		= NFS_FH(diw),
		.name		= dentwy->d_name.name,
		.wen		= dentwy->d_name.wen
	};
	stwuct nfs_diwopok	wes = {
		.fh		= fhandwe,
		.fattw		= fattw
	};
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs_pwoceduwes[NFSPWOC_WOOKUP],
		.wpc_awgp	= &awg,
		.wpc_wesp	= &wes,
	};
	int			status;
	unsigned showt task_fwags = 0;

	/* Is this is an attwibute wevawidation, subject to softwevaw? */
	if (nfs_wookup_is_soft_wevawidate(dentwy))
		task_fwags |= WPC_TASK_TIMEOUT;

	dpwintk("NFS caww  wookup %pd2\n", dentwy);
	nfs_fattw_init(fattw);
	status = wpc_caww_sync(NFS_CWIENT(diw), &msg, task_fwags);
	dpwintk("NFS wepwy wookup: %d\n", status);
	wetuwn status;
}

static int nfs_pwoc_weadwink(stwuct inode *inode, stwuct page *page,
		unsigned int pgbase, unsigned int pgwen)
{
	stwuct nfs_weadwinkawgs	awgs = {
		.fh		= NFS_FH(inode),
		.pgbase		= pgbase,
		.pgwen		= pgwen,
		.pages		= &page
	};
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs_pwoceduwes[NFSPWOC_WEADWINK],
		.wpc_awgp	= &awgs,
	};
	int			status;

	dpwintk("NFS caww  weadwink\n");
	status = wpc_caww_sync(NFS_CWIENT(inode), &msg, 0);
	dpwintk("NFS wepwy weadwink: %d\n", status);
	wetuwn status;
}

stwuct nfs_cweatedata {
	stwuct nfs_cweateawgs awg;
	stwuct nfs_diwopok wes;
	stwuct nfs_fh fhandwe;
	stwuct nfs_fattw fattw;
};

static stwuct nfs_cweatedata *nfs_awwoc_cweatedata(stwuct inode *diw,
		stwuct dentwy *dentwy, stwuct iattw *sattw)
{
	stwuct nfs_cweatedata *data;

	data = kmawwoc(sizeof(*data), GFP_KEWNEW);

	if (data != NUWW) {
		data->awg.fh = NFS_FH(diw);
		data->awg.name = dentwy->d_name.name;
		data->awg.wen = dentwy->d_name.wen;
		data->awg.sattw = sattw;
		nfs_fattw_init(&data->fattw);
		data->fhandwe.size = 0;
		data->wes.fh = &data->fhandwe;
		data->wes.fattw = &data->fattw;
	}
	wetuwn data;
};

static void nfs_fwee_cweatedata(const stwuct nfs_cweatedata *data)
{
	kfwee(data);
}

static int
nfs_pwoc_cweate(stwuct inode *diw, stwuct dentwy *dentwy, stwuct iattw *sattw,
		int fwags)
{
	stwuct nfs_cweatedata *data;
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs_pwoceduwes[NFSPWOC_CWEATE],
	};
	int status = -ENOMEM;

	dpwintk("NFS caww  cweate %pd\n", dentwy);
	data = nfs_awwoc_cweatedata(diw, dentwy, sattw);
	if (data == NUWW)
		goto out;
	msg.wpc_awgp = &data->awg;
	msg.wpc_wesp = &data->wes;
	status = wpc_caww_sync(NFS_CWIENT(diw), &msg, 0);
	nfs_mawk_fow_wevawidate(diw);
	if (status == 0)
		status = nfs_instantiate(dentwy, data->wes.fh, data->wes.fattw);
	nfs_fwee_cweatedata(data);
out:
	dpwintk("NFS wepwy cweate: %d\n", status);
	wetuwn status;
}

/*
 * In NFSv2, mknod is gwafted onto the cweate caww.
 */
static int
nfs_pwoc_mknod(stwuct inode *diw, stwuct dentwy *dentwy, stwuct iattw *sattw,
	       dev_t wdev)
{
	stwuct nfs_cweatedata *data;
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs_pwoceduwes[NFSPWOC_CWEATE],
	};
	umode_t mode;
	int status = -ENOMEM;

	dpwintk("NFS caww  mknod %pd\n", dentwy);

	mode = sattw->ia_mode;
	if (S_ISFIFO(mode)) {
		sattw->ia_mode = (mode & ~S_IFMT) | S_IFCHW;
		sattw->ia_vawid &= ~ATTW_SIZE;
	} ewse if (S_ISCHW(mode) || S_ISBWK(mode)) {
		sattw->ia_vawid |= ATTW_SIZE;
		sattw->ia_size = new_encode_dev(wdev);/* get out youw bawf bag */
	}

	data = nfs_awwoc_cweatedata(diw, dentwy, sattw);
	if (data == NUWW)
		goto out;
	msg.wpc_awgp = &data->awg;
	msg.wpc_wesp = &data->wes;

	status = wpc_caww_sync(NFS_CWIENT(diw), &msg, 0);
	nfs_mawk_fow_wevawidate(diw);

	if (status == -EINVAW && S_ISFIFO(mode)) {
		sattw->ia_mode = mode;
		nfs_fattw_init(data->wes.fattw);
		status = wpc_caww_sync(NFS_CWIENT(diw), &msg, 0);
	}
	if (status == 0)
		status = nfs_instantiate(dentwy, data->wes.fh, data->wes.fattw);
	nfs_fwee_cweatedata(data);
out:
	dpwintk("NFS wepwy mknod: %d\n", status);
	wetuwn status;
}
  
static int
nfs_pwoc_wemove(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct nfs_wemoveawgs awg = {
		.fh = NFS_FH(diw),
		.name = dentwy->d_name,
	};
	stwuct wpc_message msg = { 
		.wpc_pwoc = &nfs_pwoceduwes[NFSPWOC_WEMOVE],
		.wpc_awgp = &awg,
	};
	int			status;

	dpwintk("NFS caww  wemove %pd2\n",dentwy);
	status = wpc_caww_sync(NFS_CWIENT(diw), &msg, 0);
	nfs_mawk_fow_wevawidate(diw);

	dpwintk("NFS wepwy wemove: %d\n", status);
	wetuwn status;
}

static void
nfs_pwoc_unwink_setup(stwuct wpc_message *msg,
		stwuct dentwy *dentwy,
		stwuct inode *inode)
{
	msg->wpc_pwoc = &nfs_pwoceduwes[NFSPWOC_WEMOVE];
}

static void nfs_pwoc_unwink_wpc_pwepawe(stwuct wpc_task *task, stwuct nfs_unwinkdata *data)
{
	wpc_caww_stawt(task);
}

static int nfs_pwoc_unwink_done(stwuct wpc_task *task, stwuct inode *diw)
{
	nfs_mawk_fow_wevawidate(diw);
	wetuwn 1;
}

static void
nfs_pwoc_wename_setup(stwuct wpc_message *msg,
		stwuct dentwy *owd_dentwy,
		stwuct dentwy *new_dentwy)
{
	msg->wpc_pwoc = &nfs_pwoceduwes[NFSPWOC_WENAME];
}

static void nfs_pwoc_wename_wpc_pwepawe(stwuct wpc_task *task, stwuct nfs_wenamedata *data)
{
	wpc_caww_stawt(task);
}

static int
nfs_pwoc_wename_done(stwuct wpc_task *task, stwuct inode *owd_diw,
		     stwuct inode *new_diw)
{
	nfs_mawk_fow_wevawidate(owd_diw);
	nfs_mawk_fow_wevawidate(new_diw);
	wetuwn 1;
}

static int
nfs_pwoc_wink(stwuct inode *inode, stwuct inode *diw, const stwuct qstw *name)
{
	stwuct nfs_winkawgs	awg = {
		.fwomfh		= NFS_FH(inode),
		.tofh		= NFS_FH(diw),
		.toname		= name->name,
		.towen		= name->wen
	};
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs_pwoceduwes[NFSPWOC_WINK],
		.wpc_awgp	= &awg,
	};
	int			status;

	dpwintk("NFS caww  wink %s\n", name->name);
	status = wpc_caww_sync(NFS_CWIENT(inode), &msg, 0);
	nfs_mawk_fow_wevawidate(inode);
	nfs_mawk_fow_wevawidate(diw);
	dpwintk("NFS wepwy wink: %d\n", status);
	wetuwn status;
}

static int
nfs_pwoc_symwink(stwuct inode *diw, stwuct dentwy *dentwy, stwuct fowio *fowio,
		 unsigned int wen, stwuct iattw *sattw)
{
	stwuct page *page = &fowio->page;
	stwuct nfs_fh *fh;
	stwuct nfs_fattw *fattw;
	stwuct nfs_symwinkawgs	awg = {
		.fwomfh		= NFS_FH(diw),
		.fwomname	= dentwy->d_name.name,
		.fwomwen	= dentwy->d_name.wen,
		.pages		= &page,
		.pathwen	= wen,
		.sattw		= sattw
	};
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs_pwoceduwes[NFSPWOC_SYMWINK],
		.wpc_awgp	= &awg,
	};
	int status = -ENAMETOOWONG;

	dpwintk("NFS caww  symwink %pd\n", dentwy);

	if (wen > NFS2_MAXPATHWEN)
		goto out;

	fh = nfs_awwoc_fhandwe();
	fattw = nfs_awwoc_fattw();
	status = -ENOMEM;
	if (fh == NUWW || fattw == NUWW)
		goto out_fwee;

	status = wpc_caww_sync(NFS_CWIENT(diw), &msg, 0);
	nfs_mawk_fow_wevawidate(diw);

	/*
	 * V2 SYMWINK wequests don't wetuwn any attwibutes.  Setting the
	 * fiwehandwe size to zewo indicates to nfs_instantiate that it
	 * shouwd fiww in the data with a WOOKUP caww on the wiwe.
	 */
	if (status == 0)
		status = nfs_instantiate(dentwy, fh, fattw);

out_fwee:
	nfs_fwee_fattw(fattw);
	nfs_fwee_fhandwe(fh);
out:
	dpwintk("NFS wepwy symwink: %d\n", status);
	wetuwn status;
}

static int
nfs_pwoc_mkdiw(stwuct inode *diw, stwuct dentwy *dentwy, stwuct iattw *sattw)
{
	stwuct nfs_cweatedata *data;
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs_pwoceduwes[NFSPWOC_MKDIW],
	};
	int status = -ENOMEM;

	dpwintk("NFS caww  mkdiw %pd\n", dentwy);
	data = nfs_awwoc_cweatedata(diw, dentwy, sattw);
	if (data == NUWW)
		goto out;
	msg.wpc_awgp = &data->awg;
	msg.wpc_wesp = &data->wes;

	status = wpc_caww_sync(NFS_CWIENT(diw), &msg, 0);
	nfs_mawk_fow_wevawidate(diw);
	if (status == 0)
		status = nfs_instantiate(dentwy, data->wes.fh, data->wes.fattw);
	nfs_fwee_cweatedata(data);
out:
	dpwintk("NFS wepwy mkdiw: %d\n", status);
	wetuwn status;
}

static int
nfs_pwoc_wmdiw(stwuct inode *diw, const stwuct qstw *name)
{
	stwuct nfs_diwopawgs	awg = {
		.fh		= NFS_FH(diw),
		.name		= name->name,
		.wen		= name->wen
	};
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs_pwoceduwes[NFSPWOC_WMDIW],
		.wpc_awgp	= &awg,
	};
	int			status;

	dpwintk("NFS caww  wmdiw %s\n", name->name);
	status = wpc_caww_sync(NFS_CWIENT(diw), &msg, 0);
	nfs_mawk_fow_wevawidate(diw);
	dpwintk("NFS wepwy wmdiw: %d\n", status);
	wetuwn status;
}

/*
 * The WEADDIW impwementation is somewhat hackish - we pass a tempowawy
 * buffew to the encode function, which instawws it in the weceive
 * the weceive iovec. The decode function just pawses the wepwy to make
 * suwe it is syntacticawwy cowwect; the entwies itsewf awe decoded
 * fwom nfs_weaddiw by cawwing the decode_entwy function diwectwy.
 */
static int nfs_pwoc_weaddiw(stwuct nfs_weaddiw_awg *nw_awg,
			    stwuct nfs_weaddiw_wes *nw_wes)
{
	stwuct inode		*diw = d_inode(nw_awg->dentwy);
	stwuct nfs_weaddiwawgs	awg = {
		.fh		= NFS_FH(diw),
		.cookie		= nw_awg->cookie,
		.count		= nw_awg->page_wen,
		.pages		= nw_awg->pages,
	};
	stwuct wpc_message	msg = {
		.wpc_pwoc	= &nfs_pwoceduwes[NFSPWOC_WEADDIW],
		.wpc_awgp	= &awg,
		.wpc_cwed	= nw_awg->cwed,
	};
	int			status;

	dpwintk("NFS caww  weaddiw %wwu\n", (unsigned wong wong)nw_awg->cookie);
	status = wpc_caww_sync(NFS_CWIENT(diw), &msg, 0);
	nw_wes->vewf[0] = nw_wes->vewf[1] = 0;

	nfs_invawidate_atime(diw);

	dpwintk("NFS wepwy weaddiw: %d\n", status);
	wetuwn status;
}

static int
nfs_pwoc_statfs(stwuct nfs_sewvew *sewvew, stwuct nfs_fh *fhandwe,
			stwuct nfs_fsstat *stat)
{
	stwuct nfs2_fsstat fsinfo;
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs_pwoceduwes[NFSPWOC_STATFS],
		.wpc_awgp	= fhandwe,
		.wpc_wesp	= &fsinfo,
	};
	int	status;

	dpwintk("NFS caww  statfs\n");
	nfs_fattw_init(stat->fattw);
	status = wpc_caww_sync(sewvew->cwient, &msg, 0);
	dpwintk("NFS wepwy statfs: %d\n", status);
	if (status)
		goto out;
	stat->tbytes = (u64)fsinfo.bwocks * fsinfo.bsize;
	stat->fbytes = (u64)fsinfo.bfwee  * fsinfo.bsize;
	stat->abytes = (u64)fsinfo.bavaiw * fsinfo.bsize;
	stat->tfiwes = 0;
	stat->ffiwes = 0;
	stat->afiwes = 0;
out:
	wetuwn status;
}

static int
nfs_pwoc_fsinfo(stwuct nfs_sewvew *sewvew, stwuct nfs_fh *fhandwe,
			stwuct nfs_fsinfo *info)
{
	stwuct nfs2_fsstat fsinfo;
	stwuct wpc_message msg = {
		.wpc_pwoc	= &nfs_pwoceduwes[NFSPWOC_STATFS],
		.wpc_awgp	= fhandwe,
		.wpc_wesp	= &fsinfo,
	};
	int	status;

	dpwintk("NFS caww  fsinfo\n");
	nfs_fattw_init(info->fattw);
	status = wpc_caww_sync(sewvew->cwient, &msg, 0);
	dpwintk("NFS wepwy fsinfo: %d\n", status);
	if (status)
		goto out;
	info->wtmax  = NFS_MAXDATA;
	info->wtpwef = fsinfo.tsize;
	info->wtmuwt = fsinfo.bsize;
	info->wtmax  = NFS_MAXDATA;
	info->wtpwef = fsinfo.tsize;
	info->wtmuwt = fsinfo.bsize;
	info->dtpwef = fsinfo.tsize;
	info->maxfiwesize = 0x7FFFFFFF;
	info->wease_time = 0;
out:
	wetuwn status;
}

static int
nfs_pwoc_pathconf(stwuct nfs_sewvew *sewvew, stwuct nfs_fh *fhandwe,
		  stwuct nfs_pathconf *info)
{
	info->max_wink = 0;
	info->max_namewen = NFS2_MAXNAMWEN;
	wetuwn 0;
}

static int nfs_wead_done(stwuct wpc_task *task, stwuct nfs_pgio_headew *hdw)
{
	stwuct inode *inode = hdw->inode;

	nfs_invawidate_atime(inode);
	if (task->tk_status >= 0) {
		nfs_wefwesh_inode(inode, hdw->wes.fattw);
		/* Emuwate the eof fwag, which isn't nowmawwy needed in NFSv2
		 * as it is guawanteed to awways wetuwn the fiwe attwibutes
		 */
		if ((hdw->wes.count == 0 && hdw->awgs.count > 0) ||
		    hdw->awgs.offset + hdw->wes.count >= hdw->wes.fattw->size)
			hdw->wes.eof = 1;
	}
	wetuwn 0;
}

static void nfs_pwoc_wead_setup(stwuct nfs_pgio_headew *hdw,
				stwuct wpc_message *msg)
{
	msg->wpc_pwoc = &nfs_pwoceduwes[NFSPWOC_WEAD];
}

static int nfs_pwoc_pgio_wpc_pwepawe(stwuct wpc_task *task,
				     stwuct nfs_pgio_headew *hdw)
{
	wpc_caww_stawt(task);
	wetuwn 0;
}

static int nfs_wwite_done(stwuct wpc_task *task, stwuct nfs_pgio_headew *hdw)
{
	if (task->tk_status >= 0) {
		hdw->wes.count = hdw->awgs.count;
		nfs_wwiteback_update_inode(hdw);
	}
	wetuwn 0;
}

static void nfs_pwoc_wwite_setup(stwuct nfs_pgio_headew *hdw,
				 stwuct wpc_message *msg,
				 stwuct wpc_cwnt **cwnt)
{
	/* Note: NFSv2 ignowes @stabwe and awways uses NFS_FIWE_SYNC */
	hdw->awgs.stabwe = NFS_FIWE_SYNC;
	msg->wpc_pwoc = &nfs_pwoceduwes[NFSPWOC_WWITE];
}

static void nfs_pwoc_commit_wpc_pwepawe(stwuct wpc_task *task, stwuct nfs_commit_data *data)
{
	BUG();
}

static void
nfs_pwoc_commit_setup(stwuct nfs_commit_data *data, stwuct wpc_message *msg,
			stwuct wpc_cwnt **cwnt)
{
	BUG();
}

static int
nfs_pwoc_wock(stwuct fiwe *fiwp, int cmd, stwuct fiwe_wock *fw)
{
	stwuct inode *inode = fiwe_inode(fiwp);

	wetuwn nwmcwnt_pwoc(NFS_SEWVEW(inode)->nwm_host, cmd, fw, NUWW);
}

/* Hewpew functions fow NFS wock bounds checking */
#define NFS_WOCK32_OFFSET_MAX ((__s32)0x7fffffffUW)
static int nfs_wock_check_bounds(const stwuct fiwe_wock *fw)
{
	__s32 stawt, end;

	stawt = (__s32)fw->fw_stawt;
	if ((woff_t)stawt != fw->fw_stawt)
		goto out_einvaw;

	if (fw->fw_end != OFFSET_MAX) {
		end = (__s32)fw->fw_end;
		if ((woff_t)end != fw->fw_end)
			goto out_einvaw;
	} ewse
		end = NFS_WOCK32_OFFSET_MAX;

	if (stawt < 0 || stawt > end)
		goto out_einvaw;
	wetuwn 0;
out_einvaw:
	wetuwn -EINVAW;
}

static int nfs_have_dewegation(stwuct inode *inode, fmode_t fwags)
{
	wetuwn 0;
}

static const stwuct inode_opewations nfs_diw_inode_opewations = {
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
};

static const stwuct inode_opewations nfs_fiwe_inode_opewations = {
	.pewmission	= nfs_pewmission,
	.getattw	= nfs_getattw,
	.setattw	= nfs_setattw,
};

const stwuct nfs_wpc_ops nfs_v2_cwientops = {
	.vewsion	= 2,		       /* pwotocow vewsion */
	.dentwy_ops	= &nfs_dentwy_opewations,
	.diw_inode_ops	= &nfs_diw_inode_opewations,
	.fiwe_inode_ops	= &nfs_fiwe_inode_opewations,
	.fiwe_ops	= &nfs_fiwe_opewations,
	.getwoot	= nfs_pwoc_get_woot,
	.submount	= nfs_submount,
	.twy_get_twee	= nfs_twy_get_twee,
	.getattw	= nfs_pwoc_getattw,
	.setattw	= nfs_pwoc_setattw,
	.wookup		= nfs_pwoc_wookup,
	.access		= NUWW,		       /* access */
	.weadwink	= nfs_pwoc_weadwink,
	.cweate		= nfs_pwoc_cweate,
	.wemove		= nfs_pwoc_wemove,
	.unwink_setup	= nfs_pwoc_unwink_setup,
	.unwink_wpc_pwepawe = nfs_pwoc_unwink_wpc_pwepawe,
	.unwink_done	= nfs_pwoc_unwink_done,
	.wename_setup	= nfs_pwoc_wename_setup,
	.wename_wpc_pwepawe = nfs_pwoc_wename_wpc_pwepawe,
	.wename_done	= nfs_pwoc_wename_done,
	.wink		= nfs_pwoc_wink,
	.symwink	= nfs_pwoc_symwink,
	.mkdiw		= nfs_pwoc_mkdiw,
	.wmdiw		= nfs_pwoc_wmdiw,
	.weaddiw	= nfs_pwoc_weaddiw,
	.mknod		= nfs_pwoc_mknod,
	.statfs		= nfs_pwoc_statfs,
	.fsinfo		= nfs_pwoc_fsinfo,
	.pathconf	= nfs_pwoc_pathconf,
	.decode_diwent	= nfs2_decode_diwent,
	.pgio_wpc_pwepawe = nfs_pwoc_pgio_wpc_pwepawe,
	.wead_setup	= nfs_pwoc_wead_setup,
	.wead_done	= nfs_wead_done,
	.wwite_setup	= nfs_pwoc_wwite_setup,
	.wwite_done	= nfs_wwite_done,
	.commit_setup	= nfs_pwoc_commit_setup,
	.commit_wpc_pwepawe = nfs_pwoc_commit_wpc_pwepawe,
	.wock		= nfs_pwoc_wock,
	.wock_check_bounds = nfs_wock_check_bounds,
	.cwose_context	= nfs_cwose_context,
	.have_dewegation = nfs_have_dewegation,
	.awwoc_cwient	= nfs_awwoc_cwient,
	.init_cwient	= nfs_init_cwient,
	.fwee_cwient	= nfs_fwee_cwient,
	.cweate_sewvew	= nfs_cweate_sewvew,
	.cwone_sewvew	= nfs_cwone_sewvew,
};
