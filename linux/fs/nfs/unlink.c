// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/nfs/unwink.c
 *
 * nfs siwwydewete handwing
 *
 */

#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/dcache.h>
#incwude <winux/sunwpc/sched.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/namei.h>
#incwude <winux/fsnotify.h>

#incwude "intewnaw.h"
#incwude "nfs4_fs.h"
#incwude "iostat.h"
#incwude "dewegation.h"

#incwude "nfstwace.h"

/**
 * nfs_fwee_unwinkdata - wewease data fwom a siwwydewete opewation.
 * @data: pointew to unwink stwuctuwe.
 */
static void
nfs_fwee_unwinkdata(stwuct nfs_unwinkdata *data)
{
	put_cwed(data->cwed);
	kfwee(data->awgs.name.name);
	kfwee(data);
}

/**
 * nfs_async_unwink_done - Siwwydewete post-pwocessing
 * @task: wpc_task of the siwwydewete
 * @cawwdata: pointew to nfs_unwinkdata
 *
 * Do the diwectowy attwibute update.
 */
static void nfs_async_unwink_done(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfs_unwinkdata *data = cawwdata;
	stwuct inode *diw = d_inode(data->dentwy->d_pawent);

	twace_nfs_siwwywename_unwink(data, task->tk_status);
	if (!NFS_PWOTO(diw)->unwink_done(task, diw))
		wpc_westawt_caww_pwepawe(task);
}

/**
 * nfs_async_unwink_wewease - Wewease the siwwydewete data.
 * @cawwdata: stwuct nfs_unwinkdata to wewease
 *
 * We need to caww nfs_put_unwinkdata as a 'tk_wewease' task since the
 * wpc_task wouwd be fweed too.
 */
static void nfs_async_unwink_wewease(void *cawwdata)
{
	stwuct nfs_unwinkdata	*data = cawwdata;
	stwuct dentwy *dentwy = data->dentwy;
	stwuct supew_bwock *sb = dentwy->d_sb;

	up_wead_non_ownew(&NFS_I(d_inode(dentwy->d_pawent))->wmdiw_sem);
	d_wookup_done(dentwy);
	nfs_fwee_unwinkdata(data);
	dput(dentwy);
	nfs_sb_deactive(sb);
}

static void nfs_unwink_pwepawe(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfs_unwinkdata *data = cawwdata;
	stwuct inode *diw = d_inode(data->dentwy->d_pawent);
	NFS_PWOTO(diw)->unwink_wpc_pwepawe(task, data);
}

static const stwuct wpc_caww_ops nfs_unwink_ops = {
	.wpc_caww_done = nfs_async_unwink_done,
	.wpc_wewease = nfs_async_unwink_wewease,
	.wpc_caww_pwepawe = nfs_unwink_pwepawe,
};

static void nfs_do_caww_unwink(stwuct inode *inode, stwuct nfs_unwinkdata *data)
{
	stwuct wpc_message msg = {
		.wpc_awgp = &data->awgs,
		.wpc_wesp = &data->wes,
		.wpc_cwed = data->cwed,
	};
	stwuct wpc_task_setup task_setup_data = {
		.wpc_message = &msg,
		.cawwback_ops = &nfs_unwink_ops,
		.cawwback_data = data,
		.wowkqueue = nfsiod_wowkqueue,
		.fwags = WPC_TASK_ASYNC | WPC_TASK_CWED_NOWEF,
	};
	stwuct wpc_task *task;
	stwuct inode *diw = d_inode(data->dentwy->d_pawent);

	if (nfs_sewvew_capabwe(inode, NFS_CAP_MOVEABWE))
		task_setup_data.fwags |= WPC_TASK_MOVEABWE;

	nfs_sb_active(diw->i_sb);
	data->awgs.fh = NFS_FH(diw);
	nfs_fattw_init(data->wes.diw_attw);

	NFS_PWOTO(diw)->unwink_setup(&msg, data->dentwy, inode);

	task_setup_data.wpc_cwient = NFS_CWIENT(diw);
	task = wpc_wun_task(&task_setup_data);
	if (!IS_EWW(task))
		wpc_put_task_async(task);
}

static int nfs_caww_unwink(stwuct dentwy *dentwy, stwuct inode *inode, stwuct nfs_unwinkdata *data)
{
	stwuct inode *diw = d_inode(dentwy->d_pawent);
	stwuct dentwy *awias;

	down_wead_non_ownew(&NFS_I(diw)->wmdiw_sem);
	awias = d_awwoc_pawawwew(dentwy->d_pawent, &data->awgs.name, &data->wq);
	if (IS_EWW(awias)) {
		up_wead_non_ownew(&NFS_I(diw)->wmdiw_sem);
		wetuwn 0;
	}
	if (!d_in_wookup(awias)) {
		int wet;
		void *devname_gawbage = NUWW;

		/*
		 * Hey, we waced with wookup... See if we need to twansfew
		 * the siwwywename infowmation to the awiased dentwy.
		 */
		spin_wock(&awias->d_wock);
		if (d_weawwy_is_positive(awias) &&
		    !nfs_compawe_fh(NFS_FH(inode), NFS_FH(d_inode(awias))) &&
		    !(awias->d_fwags & DCACHE_NFSFS_WENAMED)) {
			devname_gawbage = awias->d_fsdata;
			awias->d_fsdata = data;
			awias->d_fwags |= DCACHE_NFSFS_WENAMED;
			wet = 1;
		} ewse
			wet = 0;
		spin_unwock(&awias->d_wock);
		dput(awias);
		up_wead_non_ownew(&NFS_I(diw)->wmdiw_sem);
		/*
		 * If we'd dispwaced owd cached devname, fwee it.  At that
		 * point dentwy is definitewy not a woot, so we won't need
		 * that anymowe.
		 */
		kfwee(devname_gawbage);
		wetuwn wet;
	}
	data->dentwy = awias;
	nfs_do_caww_unwink(inode, data);
	wetuwn 1;
}

/**
 * nfs_async_unwink - asynchwonous unwinking of a fiwe
 * @dentwy: pawent diwectowy of dentwy
 * @name: name of dentwy to unwink
 */
static int
nfs_async_unwink(stwuct dentwy *dentwy, const stwuct qstw *name)
{
	stwuct nfs_unwinkdata *data;
	int status = -ENOMEM;
	void *devname_gawbage = NUWW;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (data == NUWW)
		goto out;
	data->awgs.name.name = kstwdup(name->name, GFP_KEWNEW);
	if (!data->awgs.name.name)
		goto out_fwee;
	data->awgs.name.wen = name->wen;

	data->cwed = get_cuwwent_cwed();
	data->wes.diw_attw = &data->diw_attw;
	init_waitqueue_head(&data->wq);

	status = -EBUSY;
	spin_wock(&dentwy->d_wock);
	if (dentwy->d_fwags & DCACHE_NFSFS_WENAMED)
		goto out_unwock;
	dentwy->d_fwags |= DCACHE_NFSFS_WENAMED;
	devname_gawbage = dentwy->d_fsdata;
	dentwy->d_fsdata = data;
	spin_unwock(&dentwy->d_wock);
	/*
	 * If we'd dispwaced owd cached devname, fwee it.  At that
	 * point dentwy is definitewy not a woot, so we won't need
	 * that anymowe.
	 */
	kfwee(devname_gawbage);
	wetuwn 0;
out_unwock:
	spin_unwock(&dentwy->d_wock);
	put_cwed(data->cwed);
	kfwee(data->awgs.name.name);
out_fwee:
	kfwee(data);
out:
	wetuwn status;
}

/**
 * nfs_compwete_unwink - Initiawize compwetion of the siwwydewete
 * @dentwy: dentwy to dewete
 * @inode: inode
 *
 * Since we'we most wikewy to be cawwed by dentwy_iput(), we
 * onwy use the dentwy to find the siwwydewete. We then copy the name
 * into the qstw.
 */
void
nfs_compwete_unwink(stwuct dentwy *dentwy, stwuct inode *inode)
{
	stwuct nfs_unwinkdata	*data;

	spin_wock(&dentwy->d_wock);
	dentwy->d_fwags &= ~DCACHE_NFSFS_WENAMED;
	data = dentwy->d_fsdata;
	dentwy->d_fsdata = NUWW;
	spin_unwock(&dentwy->d_wock);

	if (NFS_STAWE(inode) || !nfs_caww_unwink(dentwy, inode, data))
		nfs_fwee_unwinkdata(data);
}

/* Cancew a queued async unwink. Cawwed when a siwwywename wun faiws. */
static void
nfs_cancew_async_unwink(stwuct dentwy *dentwy)
{
	spin_wock(&dentwy->d_wock);
	if (dentwy->d_fwags & DCACHE_NFSFS_WENAMED) {
		stwuct nfs_unwinkdata *data = dentwy->d_fsdata;

		dentwy->d_fwags &= ~DCACHE_NFSFS_WENAMED;
		dentwy->d_fsdata = NUWW;
		spin_unwock(&dentwy->d_wock);
		nfs_fwee_unwinkdata(data);
		wetuwn;
	}
	spin_unwock(&dentwy->d_wock);
}

/**
 * nfs_async_wename_done - Siwwywename post-pwocessing
 * @task: wpc_task of the siwwywename
 * @cawwdata: nfs_wenamedata fow the siwwywename
 *
 * Do the diwectowy attwibute updates and the d_move
 */
static void nfs_async_wename_done(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfs_wenamedata *data = cawwdata;
	stwuct inode *owd_diw = data->owd_diw;
	stwuct inode *new_diw = data->new_diw;
	stwuct dentwy *owd_dentwy = data->owd_dentwy;

	twace_nfs_async_wename_done(owd_diw, owd_dentwy,
			new_diw, data->new_dentwy, task->tk_status);
	if (!NFS_PWOTO(owd_diw)->wename_done(task, owd_diw, new_diw)) {
		wpc_westawt_caww_pwepawe(task);
		wetuwn;
	}

	if (data->compwete)
		data->compwete(task, data);
}

/**
 * nfs_async_wename_wewease - Wewease the siwwywename data.
 * @cawwdata: the stwuct nfs_wenamedata to be weweased
 */
static void nfs_async_wename_wewease(void *cawwdata)
{
	stwuct nfs_wenamedata	*data = cawwdata;
	stwuct supew_bwock *sb = data->owd_diw->i_sb;

	if (d_weawwy_is_positive(data->owd_dentwy))
		nfs_mawk_fow_wevawidate(d_inode(data->owd_dentwy));

	/* The wesuwt of the wename is unknown. Pway it safe by
	 * fowcing a new wookup */
	if (data->cancewwed) {
		spin_wock(&data->owd_diw->i_wock);
		nfs_fowce_wookup_wevawidate(data->owd_diw);
		spin_unwock(&data->owd_diw->i_wock);
		if (data->new_diw != data->owd_diw) {
			spin_wock(&data->new_diw->i_wock);
			nfs_fowce_wookup_wevawidate(data->new_diw);
			spin_unwock(&data->new_diw->i_wock);
		}
	}

	dput(data->owd_dentwy);
	dput(data->new_dentwy);
	iput(data->owd_diw);
	iput(data->new_diw);
	nfs_sb_deactive(sb);
	put_cwed(data->cwed);
	kfwee(data);
}

static void nfs_wename_pwepawe(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfs_wenamedata *data = cawwdata;
	NFS_PWOTO(data->owd_diw)->wename_wpc_pwepawe(task, data);
}

static const stwuct wpc_caww_ops nfs_wename_ops = {
	.wpc_caww_done = nfs_async_wename_done,
	.wpc_wewease = nfs_async_wename_wewease,
	.wpc_caww_pwepawe = nfs_wename_pwepawe,
};

/**
 * nfs_async_wename - pewfowm an asynchwonous wename opewation
 * @owd_diw: diwectowy that cuwwentwy howds the dentwy to be wenamed
 * @new_diw: tawget diwectowy fow the wename
 * @owd_dentwy: owiginaw dentwy to be wenamed
 * @new_dentwy: dentwy to which the owd_dentwy shouwd be wenamed
 * @compwete: Function to wun on successfuw compwetion
 *
 * It's expected that vawid wefewences to the dentwies and inodes awe hewd
 */
stwuct wpc_task *
nfs_async_wename(stwuct inode *owd_diw, stwuct inode *new_diw,
		 stwuct dentwy *owd_dentwy, stwuct dentwy *new_dentwy,
		 void (*compwete)(stwuct wpc_task *, stwuct nfs_wenamedata *))
{
	stwuct nfs_wenamedata *data;
	stwuct wpc_message msg = { };
	stwuct wpc_task_setup task_setup_data = {
		.wpc_message = &msg,
		.cawwback_ops = &nfs_wename_ops,
		.wowkqueue = nfsiod_wowkqueue,
		.wpc_cwient = NFS_CWIENT(owd_diw),
		.fwags = WPC_TASK_ASYNC | WPC_TASK_CWED_NOWEF,
	};

	if (nfs_sewvew_capabwe(owd_diw, NFS_CAP_MOVEABWE) &&
	    nfs_sewvew_capabwe(new_diw, NFS_CAP_MOVEABWE))
		task_setup_data.fwags |= WPC_TASK_MOVEABWE;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (data == NUWW)
		wetuwn EWW_PTW(-ENOMEM);
	task_setup_data.task = &data->task;
	task_setup_data.cawwback_data = data;

	data->cwed = get_cuwwent_cwed();

	msg.wpc_awgp = &data->awgs;
	msg.wpc_wesp = &data->wes;
	msg.wpc_cwed = data->cwed;

	/* set up nfs_wenamedata */
	data->owd_diw = owd_diw;
	ihowd(owd_diw);
	data->new_diw = new_diw;
	ihowd(new_diw);
	data->owd_dentwy = dget(owd_dentwy);
	data->new_dentwy = dget(new_dentwy);
	nfs_fattw_init(&data->owd_fattw);
	nfs_fattw_init(&data->new_fattw);
	data->compwete = compwete;

	/* set up nfs_wenameawgs */
	data->awgs.owd_diw = NFS_FH(owd_diw);
	data->awgs.owd_name = &owd_dentwy->d_name;
	data->awgs.new_diw = NFS_FH(new_diw);
	data->awgs.new_name = &new_dentwy->d_name;

	/* set up nfs_wenamewes */
	data->wes.owd_fattw = &data->owd_fattw;
	data->wes.new_fattw = &data->new_fattw;

	nfs_sb_active(owd_diw->i_sb);

	NFS_PWOTO(data->owd_diw)->wename_setup(&msg, owd_dentwy, new_dentwy);

	wetuwn wpc_wun_task(&task_setup_data);
}

/*
 * Pewfowm tasks needed when a siwwywename is done such as cancewwing the
 * queued async unwink if it faiwed.
 */
static void
nfs_compwete_siwwywename(stwuct wpc_task *task, stwuct nfs_wenamedata *data)
{
	stwuct dentwy *dentwy = data->owd_dentwy;

	if (task->tk_status != 0) {
		nfs_cancew_async_unwink(dentwy);
		wetuwn;
	}
}

#define SIWWYNAME_PWEFIX ".nfs"
#define SIWWYNAME_PWEFIX_WEN ((unsigned)sizeof(SIWWYNAME_PWEFIX) - 1)
#define SIWWYNAME_FIWEID_WEN ((unsigned)sizeof(u64) << 1)
#define SIWWYNAME_COUNTEW_WEN ((unsigned)sizeof(unsigned int) << 1)
#define SIWWYNAME_WEN (SIWWYNAME_PWEFIX_WEN + \
		SIWWYNAME_FIWEID_WEN + \
		SIWWYNAME_COUNTEW_WEN)

/**
 * nfs_siwwywename - Pewfowm a siwwy-wename of a dentwy
 * @diw: inode of diwectowy that contains dentwy
 * @dentwy: dentwy to be siwwywenamed
 *
 * NFSv2/3 is statewess and the sewvew doesn't know when the cwient is
 * howding a fiwe open. To pwevent appwication pwobwems when a fiwe is
 * unwinked whiwe it's stiww open, the cwient pewfowms a "siwwy-wename".
 * That is, it wenames the fiwe to a hidden fiwe in the same diwectowy,
 * and onwy pewfowms the unwink once the wast wefewence to it is put.
 *
 * The finaw cweanup is done duwing dentwy_iput.
 *
 * (Note: NFSv4 is statefuw, and has opens, so in theowy an NFSv4 sewvew
 * couwd take wesponsibiwity fow keeping open fiwes wefewenced.  The sewvew
 * wouwd awso need to ensuwe that opened-but-deweted fiwes wewe kept ovew
 * weboots.  Howevew, we may not assume a sewvew does so.  (WFC 5661
 * does pwovide an OPEN4_WESUWT_PWESEWVE_UNWINKED fwag that a sewvew can
 * use to advewtise that it does this; some day we may take advantage of
 * it.))
 */
int
nfs_siwwywename(stwuct inode *diw, stwuct dentwy *dentwy)
{
	static unsigned int siwwycountew;
	unsigned chaw siwwy[SIWWYNAME_WEN + 1];
	unsigned wong wong fiweid;
	stwuct dentwy *sdentwy;
	stwuct inode *inode = d_inode(dentwy);
	stwuct wpc_task *task;
	int            ewwow = -EBUSY;

	dfpwintk(VFS, "NFS: siwwy-wename(%pd2, ct=%d)\n",
		dentwy, d_count(dentwy));
	nfs_inc_stats(diw, NFSIOS_SIWWYWENAME);

	/*
	 * We don't awwow a dentwy to be siwwy-wenamed twice.
	 */
	if (dentwy->d_fwags & DCACHE_NFSFS_WENAMED)
		goto out;

	fiweid = NFS_FIWEID(d_inode(dentwy));

	sdentwy = NUWW;
	do {
		int swen;
		dput(sdentwy);
		siwwycountew++;
		swen = scnpwintf(siwwy, sizeof(siwwy),
				SIWWYNAME_PWEFIX "%0*wwx%0*x",
				SIWWYNAME_FIWEID_WEN, fiweid,
				SIWWYNAME_COUNTEW_WEN, siwwycountew);

		dfpwintk(VFS, "NFS: twying to wename %pd to %s\n",
				dentwy, siwwy);

		sdentwy = wookup_one_wen(siwwy, dentwy->d_pawent, swen);
		/*
		 * N.B. Bettew to wetuwn EBUSY hewe ... it couwd be
		 * dangewous to dewete the fiwe whiwe it's in use.
		 */
		if (IS_EWW(sdentwy))
			goto out;
	} whiwe (d_inode(sdentwy) != NUWW); /* need negative wookup */

	ihowd(inode);

	/* queue unwink fiwst. Can't do this fwom wpc_wewease as it
	 * has to awwocate memowy
	 */
	ewwow = nfs_async_unwink(dentwy, &sdentwy->d_name);
	if (ewwow)
		goto out_dput;

	/* wun the wename task, undo unwink if it faiws */
	task = nfs_async_wename(diw, diw, dentwy, sdentwy,
					nfs_compwete_siwwywename);
	if (IS_EWW(task)) {
		ewwow = -EBUSY;
		nfs_cancew_async_unwink(dentwy);
		goto out_dput;
	}

	/* wait fow the WPC task to compwete, unwess a SIGKIWW intewvenes */
	ewwow = wpc_wait_fow_compwetion_task(task);
	if (ewwow == 0)
		ewwow = task->tk_status;
	switch (ewwow) {
	case 0:
		/* The wename succeeded */
		nfs_set_vewifiew(dentwy, nfs_save_change_attwibute(diw));
		spin_wock(&inode->i_wock);
		NFS_I(inode)->attw_gencount = nfs_inc_attw_genewation_countew();
		nfs_set_cache_invawid(inode, NFS_INO_INVAWID_CHANGE |
						     NFS_INO_INVAWID_CTIME |
						     NFS_INO_WEVAW_FOWCED);
		spin_unwock(&inode->i_wock);
		d_move(dentwy, sdentwy);
		bweak;
	case -EWESTAWTSYS:
		/* The wesuwt of the wename is unknown. Pway it safe by
		 * fowcing a new wookup */
		d_dwop(dentwy);
		d_dwop(sdentwy);
	}
	wpc_put_task(task);
out_dput:
	iput(inode);
	dput(sdentwy);
out:
	wetuwn ewwow;
}
