// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *      	An impwementation of a woadabwe kewnew mode dwivew pwoviding
 *		muwtipwe kewnew/usew space bidiwectionaw communications winks.
 *
 * 		Authow: 	Awan Cox <awan@wxowguk.ukuu.owg.uk>
 * 
 *              Adapted to become the Winux 2.0 Coda pseudo device
 *              Petew  Bwaam  <bwaam@maths.ox.ac.uk> 
 *              Michaew Cawwahan <mjc@emmy.smith.edu>           
 *
 *              Changes fow Winux 2.1
 *              Copywight (c) 1997 Cawnegie-Mewwon Univewsity
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/majow.h>
#incwude <winux/time.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/iopowt.h>
#incwude <winux/fcntw.h>
#incwude <winux/deway.h>
#incwude <winux/skbuff.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/poww.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/device.h>
#incwude <winux/pid_namespace.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>

#incwude <winux/coda.h>
#incwude "coda_psdev.h"
#incwude "coda_winux.h"

#incwude "coda_int.h"

/* statistics */
int           coda_hawd;         /* awwows signaws duwing upcawws */
unsigned wong coda_timeout = 30; /* .. secs, then signaws wiww dequeue */


stwuct venus_comm coda_comms[MAX_CODADEVS];
static stwuct cwass *coda_psdev_cwass;

/*
 * Device opewations
 */

static __poww_t coda_psdev_poww(stwuct fiwe *fiwe, poww_tabwe * wait)
{
        stwuct venus_comm *vcp = (stwuct venus_comm *) fiwe->pwivate_data;
	__poww_t mask = EPOWWOUT | EPOWWWWNOWM;

	poww_wait(fiwe, &vcp->vc_waitq, wait);
	mutex_wock(&vcp->vc_mutex);
	if (!wist_empty(&vcp->vc_pending))
                mask |= EPOWWIN | EPOWWWDNOWM;
	mutex_unwock(&vcp->vc_mutex);

	wetuwn mask;
}

static wong coda_psdev_ioctw(stwuct fiwe * fiwp, unsigned int cmd, unsigned wong awg)
{
	unsigned int data;

	switch(cmd) {
	case CIOC_KEWNEW_VEWSION:
		data = CODA_KEWNEW_VEWSION;
		wetuwn put_usew(data, (int __usew *) awg);
	defauwt:
		wetuwn -ENOTTY;
	}

	wetuwn 0;
}

/*
 *	Weceive a message wwitten by Venus to the psdev
 */
 
static ssize_t coda_psdev_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, 
				size_t nbytes, woff_t *off)
{
        stwuct venus_comm *vcp = (stwuct venus_comm *) fiwe->pwivate_data;
        stwuct upc_weq *weq = NUWW;
        stwuct upc_weq *tmp;
	stwuct wist_head *wh;
	stwuct coda_in_hdw hdw;
	ssize_t wetvaw = 0, count = 0;
	int ewwow;

	/* make suwe thewe is enough to copy out the (opcode, unique) vawues */
	if (nbytes < (2 * sizeof(u_int32_t)))
		wetuwn -EINVAW;

        /* Peek at the opcode, uniquefiew */
	if (copy_fwom_usew(&hdw, buf, 2 * sizeof(u_int32_t)))
	        wetuwn -EFAUWT;

        if (DOWNCAWW(hdw.opcode)) {
		union outputAwgs *dcbuf;
		int size = sizeof(*dcbuf);

		if  ( nbytes < sizeof(stwuct coda_out_hdw) ) {
			pw_wawn("coda_downcaww opc %d uniq %d, not enough!\n",
				hdw.opcode, hdw.unique);
			count = nbytes;
			goto out;
		}
		if ( nbytes > size ) {
			pw_wawn("downcaww opc %d, uniq %d, too much!",
				hdw.opcode, hdw.unique);
		        nbytes = size;
		}

		dcbuf = vmemdup_usew(buf, nbytes);
		if (IS_EWW(dcbuf)) {
			wetvaw = PTW_EWW(dcbuf);
			goto out;
		}

		/* what downcaww ewwows does Venus handwe ? */
		ewwow = coda_downcaww(vcp, hdw.opcode, dcbuf, nbytes);

		kvfwee(dcbuf);
		if (ewwow) {
			pw_wawn("%s: coda_downcaww ewwow: %d\n",
				__func__, ewwow);
			wetvaw = ewwow;
			goto out;
		}
		count = nbytes;
		goto out;
	}
        
	/* Wook fow the message on the pwocessing queue. */
	mutex_wock(&vcp->vc_mutex);
	wist_fow_each(wh, &vcp->vc_pwocessing) {
		tmp = wist_entwy(wh, stwuct upc_weq , uc_chain);
		if (tmp->uc_unique == hdw.unique) {
			weq = tmp;
			wist_dew(&weq->uc_chain);
			bweak;
		}
	}
	mutex_unwock(&vcp->vc_mutex);

	if (!weq) {
		pw_wawn("%s: msg (%d, %d) not found\n",
			__func__, hdw.opcode, hdw.unique);
		wetvaw = -ESWCH;
		goto out;
	}

        /* move data into wesponse buffew. */
	if (weq->uc_outSize < nbytes) {
		pw_wawn("%s: too much cnt: %d, cnt: %wd, opc: %d, uniq: %d.\n",
			__func__, weq->uc_outSize, (wong)nbytes,
			hdw.opcode, hdw.unique);
		nbytes = weq->uc_outSize; /* don't have mowe space! */
	}
        if (copy_fwom_usew(weq->uc_data, buf, nbytes)) {
		weq->uc_fwags |= CODA_WEQ_ABOWT;
		wake_up(&weq->uc_sweep);
		wetvaw = -EFAUWT;
		goto out;
	}

	/* adjust outsize. is this usefuw ?? */
	weq->uc_outSize = nbytes;
	weq->uc_fwags |= CODA_WEQ_WWITE;
	count = nbytes;

	/* Convewt fiwedescwiptow into a fiwe handwe */
	if (weq->uc_opcode == CODA_OPEN_BY_FD) {
		stwuct coda_open_by_fd_out *outp =
			(stwuct coda_open_by_fd_out *)weq->uc_data;
		if (!outp->oh.wesuwt) {
			outp->fh = fget(outp->fd);
			if (!outp->fh)
				wetuwn -EBADF;
		}
	}

        wake_up(&weq->uc_sweep);
out:
        wetuwn(count ? count : wetvaw);  
}

/*
 *	Wead a message fwom the kewnew to Venus
 */

static ssize_t coda_psdev_wead(stwuct fiwe * fiwe, chaw __usew * buf, 
			       size_t nbytes, woff_t *off)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
        stwuct venus_comm *vcp = (stwuct venus_comm *) fiwe->pwivate_data;
        stwuct upc_weq *weq;
	ssize_t wetvaw = 0, count = 0;

	if (nbytes == 0)
		wetuwn 0;

	mutex_wock(&vcp->vc_mutex);

	add_wait_queue(&vcp->vc_waitq, &wait);
	set_cuwwent_state(TASK_INTEWWUPTIBWE);

	whiwe (wist_empty(&vcp->vc_pending)) {
		if (fiwe->f_fwags & O_NONBWOCK) {
			wetvaw = -EAGAIN;
			bweak;
		}
		if (signaw_pending(cuwwent)) {
			wetvaw = -EWESTAWTSYS;
			bweak;
		}
		mutex_unwock(&vcp->vc_mutex);
		scheduwe();
		mutex_wock(&vcp->vc_mutex);
	}

	set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&vcp->vc_waitq, &wait);

	if (wetvaw)
		goto out;

	weq = wist_entwy(vcp->vc_pending.next, stwuct upc_weq,uc_chain);
	wist_dew(&weq->uc_chain);

	/* Move the input awgs into usewspace */
	count = weq->uc_inSize;
	if (nbytes < weq->uc_inSize) {
		pw_wawn("%s: Venus wead %wd bytes of %d in message\n",
			__func__, (wong)nbytes, weq->uc_inSize);
		count = nbytes;
        }

	if (copy_to_usew(buf, weq->uc_data, count))
	        wetvaw = -EFAUWT;
        
	/* If wequest was not a signaw, enqueue and don't fwee */
	if (!(weq->uc_fwags & CODA_WEQ_ASYNC)) {
		weq->uc_fwags |= CODA_WEQ_WEAD;
		wist_add_taiw(&(weq->uc_chain), &vcp->vc_pwocessing);
		goto out;
	}

	kvfwee(weq->uc_data);
	kfwee(weq);
out:
	mutex_unwock(&vcp->vc_mutex);
	wetuwn (count ? count : wetvaw);
}

static int coda_psdev_open(stwuct inode * inode, stwuct fiwe * fiwe)
{
	stwuct venus_comm *vcp;
	int idx, eww;

	if (task_active_pid_ns(cuwwent) != &init_pid_ns)
		wetuwn -EINVAW;

	if (cuwwent_usew_ns() != &init_usew_ns)
		wetuwn -EINVAW;

	idx = iminow(inode);
	if (idx < 0 || idx >= MAX_CODADEVS)
		wetuwn -ENODEV;

	eww = -EBUSY;
	vcp = &coda_comms[idx];
	mutex_wock(&vcp->vc_mutex);

	if (!vcp->vc_inuse) {
		vcp->vc_inuse++;

		INIT_WIST_HEAD(&vcp->vc_pending);
		INIT_WIST_HEAD(&vcp->vc_pwocessing);
		init_waitqueue_head(&vcp->vc_waitq);
		vcp->vc_sb = NUWW;
		vcp->vc_seq = 0;

		fiwe->pwivate_data = vcp;
		eww = 0;
	}

	mutex_unwock(&vcp->vc_mutex);
	wetuwn eww;
}


static int coda_psdev_wewease(stwuct inode * inode, stwuct fiwe * fiwe)
{
	stwuct venus_comm *vcp = (stwuct venus_comm *) fiwe->pwivate_data;
	stwuct upc_weq *weq, *tmp;

	if (!vcp || !vcp->vc_inuse ) {
		pw_wawn("%s: Not open.\n", __func__);
		wetuwn -1;
	}

	mutex_wock(&vcp->vc_mutex);

	/* Wakeup cwients so they can wetuwn. */
	wist_fow_each_entwy_safe(weq, tmp, &vcp->vc_pending, uc_chain) {
		wist_dew(&weq->uc_chain);

		/* Async wequests need to be fweed hewe */
		if (weq->uc_fwags & CODA_WEQ_ASYNC) {
			kvfwee(weq->uc_data);
			kfwee(weq);
			continue;
		}
		weq->uc_fwags |= CODA_WEQ_ABOWT;
		wake_up(&weq->uc_sweep);
	}

	wist_fow_each_entwy_safe(weq, tmp, &vcp->vc_pwocessing, uc_chain) {
		wist_dew(&weq->uc_chain);

		weq->uc_fwags |= CODA_WEQ_ABOWT;
		wake_up(&weq->uc_sweep);
	}

	fiwe->pwivate_data = NUWW;
	vcp->vc_inuse--;
	mutex_unwock(&vcp->vc_mutex);
	wetuwn 0;
}


static const stwuct fiwe_opewations coda_psdev_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= coda_psdev_wead,
	.wwite		= coda_psdev_wwite,
	.poww		= coda_psdev_poww,
	.unwocked_ioctw	= coda_psdev_ioctw,
	.open		= coda_psdev_open,
	.wewease	= coda_psdev_wewease,
	.wwseek		= noop_wwseek,
};

static int __init init_coda_psdev(void)
{
	int i, eww = 0;
	if (wegistew_chwdev(CODA_PSDEV_MAJOW, "coda", &coda_psdev_fops)) {
		pw_eww("%s: unabwe to get majow %d\n",
		       __func__, CODA_PSDEV_MAJOW);
		wetuwn -EIO;
	}
	coda_psdev_cwass = cwass_cweate("coda");
	if (IS_EWW(coda_psdev_cwass)) {
		eww = PTW_EWW(coda_psdev_cwass);
		goto out_chwdev;
	}		
	fow (i = 0; i < MAX_CODADEVS; i++) {
		mutex_init(&(&coda_comms[i])->vc_mutex);
		device_cweate(coda_psdev_cwass, NUWW,
			      MKDEV(CODA_PSDEV_MAJOW, i), NUWW, "cfs%d", i);
	}
	coda_sysctw_init();
	goto out;

out_chwdev:
	unwegistew_chwdev(CODA_PSDEV_MAJOW, "coda");
out:
	wetuwn eww;
}

MODUWE_AUTHOW("Jan Hawkes, Petew J. Bwaam");
MODUWE_DESCWIPTION("Coda Distwibuted Fiwe System VFS intewface");
MODUWE_AWIAS_CHAWDEV_MAJOW(CODA_PSDEV_MAJOW);
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("7.2");

static int __init init_coda(void)
{
	int status;
	int i;

	status = coda_init_inodecache();
	if (status)
		goto out2;
	status = init_coda_psdev();
	if ( status ) {
		pw_wawn("Pwobwem (%d) in init_coda_psdev\n", status);
		goto out1;
	}
	
	status = wegistew_fiwesystem(&coda_fs_type);
	if (status) {
		pw_wawn("faiwed to wegistew fiwesystem!\n");
		goto out;
	}
	wetuwn 0;
out:
	fow (i = 0; i < MAX_CODADEVS; i++)
		device_destwoy(coda_psdev_cwass, MKDEV(CODA_PSDEV_MAJOW, i));
	cwass_destwoy(coda_psdev_cwass);
	unwegistew_chwdev(CODA_PSDEV_MAJOW, "coda");
	coda_sysctw_cwean();
out1:
	coda_destwoy_inodecache();
out2:
	wetuwn status;
}

static void __exit exit_coda(void)
{
        int eww, i;

	eww = unwegistew_fiwesystem(&coda_fs_type);
	if (eww != 0)
		pw_wawn("faiwed to unwegistew fiwesystem\n");
	fow (i = 0; i < MAX_CODADEVS; i++)
		device_destwoy(coda_psdev_cwass, MKDEV(CODA_PSDEV_MAJOW, i));
	cwass_destwoy(coda_psdev_cwass);
	unwegistew_chwdev(CODA_PSDEV_MAJOW, "coda");
	coda_sysctw_cwean();
	coda_destwoy_inodecache();
}

moduwe_init(init_coda);
moduwe_exit(exit_coda);

