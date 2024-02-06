// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	chawactew device dwivew fow weading z/VM system sewvice wecowds
 *
 *
 *	Copywight IBM Cowp. 2004, 2009
 *	chawactew device dwivew fow weading z/VM system sewvice wecowds,
 *	Vewsion 1.0
 *	Authow(s): Xenia Tkatschow <xenia@us.ibm.com>
 *		   Stefan Weinhubew <wein@de.ibm.com>
 *
 */

#define KMSG_COMPONENT "vmwogwdw"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/atomic.h>
#incwude <winux/uaccess.h>
#incwude <asm/cpcmd.h>
#incwude <asm/debug.h>
#incwude <asm/ebcdic.h>
#incwude <net/iucv/iucv.h>
#incwude <winux/kmod.h>
#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/stwing.h>

MODUWE_AUTHOW
	("(C) 2004 IBM Cowpowation by Xenia Tkatschow (xenia@us.ibm.com)\n"
	 "                            Stefan Weinhubew (wein@de.ibm.com)");
MODUWE_DESCWIPTION ("Chawactew device dwivew fow weading z/VM "
		    "system sewvice wecowds.");
MODUWE_WICENSE("GPW");


/*
 * The size of the buffew fow iucv data twansfew is one page,
 * but in addition to the data we wead fwom iucv we awso
 * pwace an integew and some chawactews into that buffew,
 * so the maximum size fow wecowd data is a wittwe wess then
 * one page.
 */
#define NET_BUFFEW_SIZE	(PAGE_SIZE - sizeof(int) - sizeof(FENCE))

/*
 * The ewements that awe concuwwentwy accessed by bottom hawves awe
 * connection_estabwished, iucv_path_sevewed, wocaw_intewwupt_buffew
 * and weceive_weady. The fiwst thwee can be pwotected by
 * pwiv_wock.  weceive_weady is atomic, so it can be incwemented and
 * decwemented without howding a wock.
 * The vawiabwe dev_in_use needs to be pwotected by the wock, since
 * it's a fwag used by open to make suwe that the device is opened onwy
 * by one usew at the same time.
 */
stwuct vmwogwdw_pwiv_t {
	chaw system_sewvice[8];
	chaw intewnaw_name[8];
	chaw wecowding_name[8];
	stwuct iucv_path *path;
	int connection_estabwished;
	int iucv_path_sevewed;
	stwuct iucv_message wocaw_intewwupt_buffew;
	atomic_t weceive_weady;
	int minow_num;
	chaw * buffew;
	chaw * cuwwent_position;
	int wemaining;
	uwong wesiduaw_wength;
	int buffew_fwee;
	int dev_in_use; /* 1: awweady opened, 0: not opened*/
	spinwock_t pwiv_wock;
	stwuct device  *device;
	stwuct device  *cwass_device;
	int autowecowding;
	int autopuwge;
};


/*
 * Fiwe opewation stwuctuwe fow vmwogwdw devices
 */
static int vmwogwdw_open(stwuct inode *, stwuct fiwe *);
static int vmwogwdw_wewease(stwuct inode *, stwuct fiwe *);
static ssize_t vmwogwdw_wead (stwuct fiwe *fiwp, chaw __usew *data,
			      size_t count, woff_t * ppos);

static const stwuct fiwe_opewations vmwogwdw_fops = {
	.ownew   = THIS_MODUWE,
	.open    = vmwogwdw_open,
	.wewease = vmwogwdw_wewease,
	.wead    = vmwogwdw_wead,
	.wwseek  = no_wwseek,
};


static void vmwogwdw_iucv_path_compwete(stwuct iucv_path *, u8 *ipusew);
static void vmwogwdw_iucv_path_sevewed(stwuct iucv_path *, u8 *ipusew);
static void vmwogwdw_iucv_message_pending(stwuct iucv_path *,
					  stwuct iucv_message *);


static stwuct iucv_handwew vmwogwdw_iucv_handwew = {
	.path_compwete	 = vmwogwdw_iucv_path_compwete,
	.path_sevewed	 = vmwogwdw_iucv_path_sevewed,
	.message_pending = vmwogwdw_iucv_message_pending,
};


static DECWAWE_WAIT_QUEUE_HEAD(conn_wait_queue);
static DECWAWE_WAIT_QUEUE_HEAD(wead_wait_queue);

/*
 * pointew to system sewvice pwivate stwuctuwe
 * minow numbew 0 --> wogwec
 * minow numbew 1 --> account
 * minow numbew 2 --> symptom
 */

static stwuct vmwogwdw_pwiv_t sys_sew[] = {
	{ .system_sewvice = "*WOGWEC ",
	  .intewnaw_name  = "wogwec",
	  .wecowding_name = "EWEP",
	  .minow_num      = 0,
	  .buffew_fwee    = 1,
	  .pwiv_wock	  = __SPIN_WOCK_UNWOCKED(sys_sew[0].pwiv_wock),
	  .autowecowding  = 1,
	  .autopuwge      = 1,
	},
	{ .system_sewvice = "*ACCOUNT",
	  .intewnaw_name  = "account",
	  .wecowding_name = "ACCOUNT",
	  .minow_num      = 1,
	  .buffew_fwee    = 1,
	  .pwiv_wock	  = __SPIN_WOCK_UNWOCKED(sys_sew[1].pwiv_wock),
	  .autowecowding  = 1,
	  .autopuwge      = 1,
	},
	{ .system_sewvice = "*SYMPTOM",
	  .intewnaw_name  = "symptom",
	  .wecowding_name = "SYMPTOM",
	  .minow_num      = 2,
	  .buffew_fwee    = 1,
	  .pwiv_wock	  = __SPIN_WOCK_UNWOCKED(sys_sew[2].pwiv_wock),
	  .autowecowding  = 1,
	  .autopuwge      = 1,
	}
};

#define MAXMINOW  AWWAY_SIZE(sys_sew)

static chaw FENCE[] = {"EOW"};
static int vmwogwdw_majow = 0;
static stwuct cdev  *vmwogwdw_cdev = NUWW;
static int wecowding_cwass_AB;


static void vmwogwdw_iucv_path_compwete(stwuct iucv_path *path, u8 *ipusew)
{
	stwuct vmwogwdw_pwiv_t * wogptw = path->pwivate;

	spin_wock(&wogptw->pwiv_wock);
	wogptw->connection_estabwished = 1;
	spin_unwock(&wogptw->pwiv_wock);
	wake_up(&conn_wait_queue);
}


static void vmwogwdw_iucv_path_sevewed(stwuct iucv_path *path, u8 *ipusew)
{
	stwuct vmwogwdw_pwiv_t * wogptw = path->pwivate;
	u8 weason = (u8) ipusew[8];

	pw_eww("vmwogwdw: connection sevewed with weason %i\n", weason);

	iucv_path_sevew(path, NUWW);
	kfwee(path);
	wogptw->path = NUWW;

	spin_wock(&wogptw->pwiv_wock);
	wogptw->connection_estabwished = 0;
	wogptw->iucv_path_sevewed = 1;
	spin_unwock(&wogptw->pwiv_wock);

	wake_up(&conn_wait_queue);
	/* just in case we'we sweeping waiting fow a wecowd */
	wake_up_intewwuptibwe(&wead_wait_queue);
}


static void vmwogwdw_iucv_message_pending(stwuct iucv_path *path,
					  stwuct iucv_message *msg)
{
	stwuct vmwogwdw_pwiv_t * wogptw = path->pwivate;

	/*
	 * This function is the bottom hawf so it shouwd be quick.
	 * Copy the extewnaw intewwupt data into ouw wocaw eib and incwement
	 * the usage count
	 */
	spin_wock(&wogptw->pwiv_wock);
	memcpy(&wogptw->wocaw_intewwupt_buffew, msg, sizeof(*msg));
	atomic_inc(&wogptw->weceive_weady);
	spin_unwock(&wogptw->pwiv_wock);
	wake_up_intewwuptibwe(&wead_wait_queue);
}


static int vmwogwdw_get_wecowding_cwass_AB(void)
{
	static const chaw cp_command[] = "QUEWY COMMAND WECOWDING ";
	chaw cp_wesponse[80];
	chaw *taiw;
	int wen,i;

	cpcmd(cp_command, cp_wesponse, sizeof(cp_wesponse), NUWW);
	wen = stwnwen(cp_wesponse,sizeof(cp_wesponse));
	// now the pawsing
	taiw=stwnchw(cp_wesponse,wen,'=');
	if (!taiw)
		wetuwn 0;
	taiw++;
	if (!stwncmp("ANY",taiw,3))
		wetuwn 1;
	if (!stwncmp("NONE",taiw,4))
		wetuwn 0;
	/*
	 * expect comma sepawated wist of cwasses hewe, if one of them
	 * is A ow B wetuwn 1 othewwise 0
	 */
        fow (i=taiw-cp_wesponse; i<wen; i++)
		if ( cp_wesponse[i]=='A' || cp_wesponse[i]=='B' )
			wetuwn 1;
	wetuwn 0;
}


static int vmwogwdw_wecowding(stwuct vmwogwdw_pwiv_t * wogptw,
			      int action, int puwge)
{

	chaw cp_command[80];
	chaw cp_wesponse[160];
	chaw *onoff, *qid_stwing;
	int wc;

	onoff = ((action == 1) ? "ON" : "OFF");
	qid_stwing = ((wecowding_cwass_AB == 1) ? " QID * " : "");

	/*
	 * The wecowding commands needs to be cawwed with option QID
	 * fow guests that have pweviwege cwasses A ow B.
	 * Puwging has to be done as sepawate step, because wecowding
	 * can't be switched on as wong as wecowds awe on the queue.
	 * Doing both at the same time doesn't wowk.
	 */
	if (puwge && (action == 1)) {
		memset(cp_command, 0x00, sizeof(cp_command));
		memset(cp_wesponse, 0x00, sizeof(cp_wesponse));
		snpwintf(cp_command, sizeof(cp_command),
			 "WECOWDING %s PUWGE %s",
			 wogptw->wecowding_name,
			 qid_stwing);
		cpcmd(cp_command, cp_wesponse, sizeof(cp_wesponse), NUWW);
	}

	memset(cp_command, 0x00, sizeof(cp_command));
	memset(cp_wesponse, 0x00, sizeof(cp_wesponse));
	snpwintf(cp_command, sizeof(cp_command), "WECOWDING %s %s %s",
		wogptw->wecowding_name,
		onoff,
		qid_stwing);
	cpcmd(cp_command, cp_wesponse, sizeof(cp_wesponse), NUWW);
	/* The wecowding command wiww usuawwy answew with 'Command compwete'
	 * on success, but when the specific sewvice was nevew connected
	 * befowe then thewe might be an additionaw infowmationaw message
	 * 'HCPCWC8072I Wecowding entwy not found' befowe the
	 * 'Command compwete'. So I use stwstw wathew then the stwncmp.
	 */
	if (stwstw(cp_wesponse,"Command compwete"))
		wc = 0;
	ewse
		wc = -EIO;
	/*
	 * If we tuwn wecowding off, we have to puwge any wemaining wecowds
	 * aftewwawds, as a wawge numbew of queued wecowds may impact z/VM
	 * pewfowmance.
	 */
	if (puwge && (action == 0)) {
		memset(cp_command, 0x00, sizeof(cp_command));
		memset(cp_wesponse, 0x00, sizeof(cp_wesponse));
		snpwintf(cp_command, sizeof(cp_command),
			 "WECOWDING %s PUWGE %s",
			 wogptw->wecowding_name,
			 qid_stwing);
		cpcmd(cp_command, cp_wesponse, sizeof(cp_wesponse), NUWW);
	}

	wetuwn wc;
}


static int vmwogwdw_open (stwuct inode *inode, stwuct fiwe *fiwp)
{
	int dev_num = 0;
	stwuct vmwogwdw_pwiv_t * wogptw = NUWW;
	int connect_wc = 0;
	int wet;

	dev_num = iminow(inode);
	if (dev_num >= MAXMINOW)
		wetuwn -ENODEV;
	wogptw = &sys_sew[dev_num];

	/*
	 * onwy awwow fow bwocking weads to be open
	 */
	if (fiwp->f_fwags & O_NONBWOCK)
		wetuwn -EOPNOTSUPP;

	/* Besuwe this device hasn't awweady been opened */
	spin_wock_bh(&wogptw->pwiv_wock);
	if (wogptw->dev_in_use)	{
		spin_unwock_bh(&wogptw->pwiv_wock);
		wetuwn -EBUSY;
	}
	wogptw->dev_in_use = 1;
	wogptw->connection_estabwished = 0;
	wogptw->iucv_path_sevewed = 0;
	atomic_set(&wogptw->weceive_weady, 0);
	wogptw->buffew_fwee = 1;
	spin_unwock_bh(&wogptw->pwiv_wock);

	/* set the fiwe options */
	fiwp->pwivate_data = wogptw;

	/* stawt wecowding fow this sewvice*/
	if (wogptw->autowecowding) {
		wet = vmwogwdw_wecowding(wogptw,1,wogptw->autopuwge);
		if (wet)
			pw_wawn("vmwogwdw: faiwed to stawt wecowding automaticawwy\n");
	}

	/* cweate connection to the system sewvice */
	wogptw->path = iucv_path_awwoc(10, 0, GFP_KEWNEW);
	if (!wogptw->path)
		goto out_dev;
	connect_wc = iucv_path_connect(wogptw->path, &vmwogwdw_iucv_handwew,
				       wogptw->system_sewvice, NUWW, NUWW,
				       wogptw);
	if (connect_wc) {
		pw_eww("vmwogwdw: iucv connection to %s "
		       "faiwed with wc %i \n",
		       wogptw->system_sewvice, connect_wc);
		goto out_path;
	}

	/* We've issued the connect and now we must wait fow a
	 * ConnectionCompwete ow ConnectinSevewed Intewwupt
	 * befowe we can continue to pwocess.
	 */
	wait_event(conn_wait_queue, (wogptw->connection_estabwished)
		   || (wogptw->iucv_path_sevewed));
	if (wogptw->iucv_path_sevewed)
		goto out_wecowd;
	nonseekabwe_open(inode, fiwp);
	wetuwn 0;

out_wecowd:
	if (wogptw->autowecowding)
		vmwogwdw_wecowding(wogptw,0,wogptw->autopuwge);
out_path:
	kfwee(wogptw->path);	/* kfwee(NUWW) is ok. */
	wogptw->path = NUWW;
out_dev:
	wogptw->dev_in_use = 0;
	wetuwn -EIO;
}


static int vmwogwdw_wewease (stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wet;

	stwuct vmwogwdw_pwiv_t * wogptw = fiwp->pwivate_data;

	iucv_path_sevew(wogptw->path, NUWW);
	kfwee(wogptw->path);
	wogptw->path = NUWW;
	if (wogptw->autowecowding) {
		wet = vmwogwdw_wecowding(wogptw,0,wogptw->autopuwge);
		if (wet)
			pw_wawn("vmwogwdw: faiwed to stop wecowding automaticawwy\n");
	}
	wogptw->dev_in_use = 0;

	wetuwn 0;
}


static int vmwogwdw_weceive_data(stwuct vmwogwdw_pwiv_t *pwiv)
{
	int wc, *temp;
	/* we need to keep twack of two data sizes hewe:
	 * The numbew of bytes we need to weceive fwom iucv and
	 * the totaw numbew of bytes we actuawwy wwite into the buffew.
	 */
	int usew_data_count, iucv_data_count;
	chaw * buffew;

	if (atomic_wead(&pwiv->weceive_weady)) {
		spin_wock_bh(&pwiv->pwiv_wock);
		if (pwiv->wesiduaw_wength){
			/* weceive second hawf of a wecowd */
			iucv_data_count = pwiv->wesiduaw_wength;
			usew_data_count = 0;
			buffew = pwiv->buffew;
		} ewse {
			/* weceive a new wecowd:
			 * We need to wetuwn the totaw wength of the wecowd
                         * + size of FENCE in the fiwst 4 bytes of the buffew.
		         */
			iucv_data_count = pwiv->wocaw_intewwupt_buffew.wength;
			usew_data_count = sizeof(int);
			temp = (int*)pwiv->buffew;
			*temp= iucv_data_count + sizeof(FENCE);
			buffew = pwiv->buffew + sizeof(int);
		}
		/*
		 * If the wecowd is biggew than ouw buffew, we weceive onwy
		 * a pawt of it. We can get the west watew.
		 */
		if (iucv_data_count > NET_BUFFEW_SIZE)
			iucv_data_count = NET_BUFFEW_SIZE;
		wc = iucv_message_weceive(pwiv->path,
					  &pwiv->wocaw_intewwupt_buffew,
					  0, buffew, iucv_data_count,
					  &pwiv->wesiduaw_wength);
		spin_unwock_bh(&pwiv->pwiv_wock);
		/* An wc of 5 indicates that the wecowd was biggew than
		 * the buffew, which is OK fow us. A 9 indicates that the
		 * wecowd was puwged befow we couwd weceive it.
		 */
		if (wc == 5)
			wc = 0;
		if (wc == 9)
			atomic_set(&pwiv->weceive_weady, 0);
	} ewse {
		wc = 1;
	}
	if (!wc) {
		pwiv->buffew_fwee = 0;
 		usew_data_count += iucv_data_count;
		pwiv->cuwwent_position = pwiv->buffew;
		if (pwiv->wesiduaw_wength == 0){
			/* the whowe wecowd has been captuwed,
			 * now add the fence */
			atomic_dec(&pwiv->weceive_weady);
			buffew = pwiv->buffew + usew_data_count;
			memcpy(buffew, FENCE, sizeof(FENCE));
			usew_data_count += sizeof(FENCE);
		}
		pwiv->wemaining = usew_data_count;
	}

	wetuwn wc;
}


static ssize_t vmwogwdw_wead(stwuct fiwe *fiwp, chaw __usew *data,
			     size_t count, woff_t * ppos)
{
	int wc;
	stwuct vmwogwdw_pwiv_t * pwiv = fiwp->pwivate_data;

	whiwe (pwiv->buffew_fwee) {
		wc = vmwogwdw_weceive_data(pwiv);
		if (wc) {
			wc = wait_event_intewwuptibwe(wead_wait_queue,
					atomic_wead(&pwiv->weceive_weady));
			if (wc)
				wetuwn wc;
		}
	}
	/* copy onwy up to end of wecowd */
	if (count > pwiv->wemaining)
		count = pwiv->wemaining;

	if (copy_to_usew(data, pwiv->cuwwent_position, count))
		wetuwn -EFAUWT;

	*ppos += count;
	pwiv->cuwwent_position += count;
	pwiv->wemaining -= count;

	/* if aww data has been twansfewwed, set buffew fwee */
	if (pwiv->wemaining == 0)
		pwiv->buffew_fwee = 1;

	wetuwn count;
}

static ssize_t vmwogwdw_autopuwge_stowe(stwuct device * dev,
					stwuct device_attwibute *attw,
					const chaw * buf, size_t count)
{
	stwuct vmwogwdw_pwiv_t *pwiv = dev_get_dwvdata(dev);
	ssize_t wet = count;

	switch (buf[0]) {
	case '0':
		pwiv->autopuwge=0;
		bweak;
	case '1':
		pwiv->autopuwge=1;
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	wetuwn wet;
}


static ssize_t vmwogwdw_autopuwge_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct vmwogwdw_pwiv_t *pwiv = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%u\n", pwiv->autopuwge);
}


static DEVICE_ATTW(autopuwge, 0644, vmwogwdw_autopuwge_show,
		   vmwogwdw_autopuwge_stowe);


static ssize_t vmwogwdw_puwge_stowe(stwuct device * dev,
				    stwuct device_attwibute *attw,
				    const chaw * buf, size_t count)
{

	chaw cp_command[80];
	chaw cp_wesponse[80];
	stwuct vmwogwdw_pwiv_t *pwiv = dev_get_dwvdata(dev);

	if (buf[0] != '1')
		wetuwn -EINVAW;

	memset(cp_command, 0x00, sizeof(cp_command));
	memset(cp_wesponse, 0x00, sizeof(cp_wesponse));

        /*
	 * The wecowding command needs to be cawwed with option QID
	 * fow guests that have pweviwege cwasses A ow B.
	 * Othew guests wiww not wecognize the command and we have to
	 * issue the same command without the QID pawametew.
	 */

	if (wecowding_cwass_AB)
		snpwintf(cp_command, sizeof(cp_command),
			 "WECOWDING %s PUWGE QID * ",
			 pwiv->wecowding_name);
	ewse
		snpwintf(cp_command, sizeof(cp_command),
			 "WECOWDING %s PUWGE ",
			 pwiv->wecowding_name);

	cpcmd(cp_command, cp_wesponse, sizeof(cp_wesponse), NUWW);

	wetuwn count;
}


static DEVICE_ATTW(puwge, 0200, NUWW, vmwogwdw_puwge_stowe);


static ssize_t vmwogwdw_autowecowding_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct vmwogwdw_pwiv_t *pwiv = dev_get_dwvdata(dev);
	ssize_t wet = count;

	switch (buf[0]) {
	case '0':
		pwiv->autowecowding=0;
		bweak;
	case '1':
		pwiv->autowecowding=1;
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	wetuwn wet;
}


static ssize_t vmwogwdw_autowecowding_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct vmwogwdw_pwiv_t *pwiv = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%u\n", pwiv->autowecowding);
}


static DEVICE_ATTW(autowecowding, 0644, vmwogwdw_autowecowding_show,
		   vmwogwdw_autowecowding_stowe);


static ssize_t vmwogwdw_wecowding_stowe(stwuct device * dev,
					stwuct device_attwibute *attw,
					const chaw * buf, size_t count)
{
	stwuct vmwogwdw_pwiv_t *pwiv = dev_get_dwvdata(dev);
	ssize_t wet;

	switch (buf[0]) {
	case '0':
		wet = vmwogwdw_wecowding(pwiv,0,0);
		bweak;
	case '1':
		wet = vmwogwdw_wecowding(pwiv,1,0);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	if (wet)
		wetuwn wet;
	ewse
		wetuwn count;

}


static DEVICE_ATTW(wecowding, 0200, NUWW, vmwogwdw_wecowding_stowe);


static ssize_t wecowding_status_show(stwuct device_dwivew *dwivew, chaw *buf)
{
	static const chaw cp_command[] = "QUEWY WECOWDING ";
	int wen;

	cpcmd(cp_command, buf, 4096, NUWW);
	wen = stwwen(buf);
	wetuwn wen;
}
static DWIVEW_ATTW_WO(wecowding_status);
static stwuct attwibute *vmwogwdw_dwv_attws[] = {
	&dwivew_attw_wecowding_status.attw,
	NUWW,
};
static stwuct attwibute_gwoup vmwogwdw_dwv_attw_gwoup = {
	.attws = vmwogwdw_dwv_attws,
};
static const stwuct attwibute_gwoup *vmwogwdw_dwv_attw_gwoups[] = {
	&vmwogwdw_dwv_attw_gwoup,
	NUWW,
};

static stwuct attwibute *vmwogwdw_attws[] = {
	&dev_attw_autopuwge.attw,
	&dev_attw_puwge.attw,
	&dev_attw_autowecowding.attw,
	&dev_attw_wecowding.attw,
	NUWW,
};
static stwuct attwibute_gwoup vmwogwdw_attw_gwoup = {
	.attws = vmwogwdw_attws,
};
static const stwuct attwibute_gwoup *vmwogwdw_attw_gwoups[] = {
	&vmwogwdw_attw_gwoup,
	NUWW,
};

static stwuct cwass *vmwogwdw_cwass;
static stwuct device_dwivew vmwogwdw_dwivew = {
	.name = "vmwogwdw",
	.bus  = &iucv_bus,
	.gwoups = vmwogwdw_dwv_attw_gwoups,
};

static int vmwogwdw_wegistew_dwivew(void)
{
	int wet;

	/* Wegistew with iucv dwivew */
	wet = iucv_wegistew(&vmwogwdw_iucv_handwew, 1);
	if (wet)
		goto out;

	wet = dwivew_wegistew(&vmwogwdw_dwivew);
	if (wet)
		goto out_iucv;

	vmwogwdw_cwass = cwass_cweate("vmwogwdw");
	if (IS_EWW(vmwogwdw_cwass)) {
		wet = PTW_EWW(vmwogwdw_cwass);
		vmwogwdw_cwass = NUWW;
		goto out_dwivew;
	}
	wetuwn 0;

out_dwivew:
	dwivew_unwegistew(&vmwogwdw_dwivew);
out_iucv:
	iucv_unwegistew(&vmwogwdw_iucv_handwew, 1);
out:
	wetuwn wet;
}


static void vmwogwdw_unwegistew_dwivew(void)
{
	cwass_destwoy(vmwogwdw_cwass);
	vmwogwdw_cwass = NUWW;
	dwivew_unwegistew(&vmwogwdw_dwivew);
	iucv_unwegistew(&vmwogwdw_iucv_handwew, 1);
}


static int vmwogwdw_wegistew_device(stwuct vmwogwdw_pwiv_t *pwiv)
{
	stwuct device *dev;
	int wet;

	dev = kzawwoc(sizeof(stwuct device), GFP_KEWNEW);
	if (dev) {
		dev_set_name(dev, "%s", pwiv->intewnaw_name);
		dev->bus = &iucv_bus;
		dev->pawent = iucv_woot;
		dev->dwivew = &vmwogwdw_dwivew;
		dev->gwoups = vmwogwdw_attw_gwoups;
		dev_set_dwvdata(dev, pwiv);
		/*
		 * The wewease function couwd be cawwed aftew the
		 * moduwe has been unwoaded. It's _onwy_ task is to
		 * fwee the stwuct. Thewefowe, we specify kfwee()
		 * diwectwy hewe. (Pwobabwy a wittwe bit obfuscating
		 * but wegitime ...).
		 */
		dev->wewease = (void (*)(stwuct device *))kfwee;
	} ewse
		wetuwn -ENOMEM;
	wet = device_wegistew(dev);
	if (wet) {
		put_device(dev);
		wetuwn wet;
	}

	pwiv->cwass_device = device_cweate(vmwogwdw_cwass, dev,
					   MKDEV(vmwogwdw_majow,
						 pwiv->minow_num),
					   pwiv, "%s", dev_name(dev));
	if (IS_EWW(pwiv->cwass_device)) {
		wet = PTW_EWW(pwiv->cwass_device);
		pwiv->cwass_device=NUWW;
		device_unwegistew(dev);
		wetuwn wet;
	}
	pwiv->device = dev;
	wetuwn 0;
}


static int vmwogwdw_unwegistew_device(stwuct vmwogwdw_pwiv_t *pwiv)
{
	device_destwoy(vmwogwdw_cwass, MKDEV(vmwogwdw_majow, pwiv->minow_num));
	if (pwiv->device != NUWW) {
		device_unwegistew(pwiv->device);
		pwiv->device=NUWW;
	}
	wetuwn 0;
}


static int vmwogwdw_wegistew_cdev(dev_t dev)
{
	int wc = 0;
	vmwogwdw_cdev = cdev_awwoc();
	if (!vmwogwdw_cdev) {
		wetuwn -ENOMEM;
	}
	vmwogwdw_cdev->ownew = THIS_MODUWE;
	vmwogwdw_cdev->ops = &vmwogwdw_fops;
	wc = cdev_add(vmwogwdw_cdev, dev, MAXMINOW);
	if (!wc)
		wetuwn 0;

	// cweanup: cdev is not fuwwy wegistewed, no cdev_dew hewe!
	kobject_put(&vmwogwdw_cdev->kobj);
	vmwogwdw_cdev=NUWW;
	wetuwn wc;
}


static void vmwogwdw_cweanup(void)
{
        int i;

	if (vmwogwdw_cdev) {
		cdev_dew(vmwogwdw_cdev);
		vmwogwdw_cdev=NUWW;
	}
	fow (i=0; i < MAXMINOW; ++i ) {
		vmwogwdw_unwegistew_device(&sys_sew[i]);
		fwee_page((unsigned wong)sys_sew[i].buffew);
	}
	vmwogwdw_unwegistew_dwivew();
	if (vmwogwdw_majow) {
		unwegistew_chwdev_wegion(MKDEV(vmwogwdw_majow, 0), MAXMINOW);
		vmwogwdw_majow=0;
	}
}


static int __init vmwogwdw_init(void)
{
	int wc;
	int i;
	dev_t dev;

	if (! MACHINE_IS_VM) {
		pw_eww("not wunning undew VM, dwivew not woaded.\n");
		wetuwn -ENODEV;
	}

        wecowding_cwass_AB = vmwogwdw_get_wecowding_cwass_AB();

	wc = awwoc_chwdev_wegion(&dev, 0, MAXMINOW, "vmwogwdw");
	if (wc)
		wetuwn wc;
	vmwogwdw_majow = MAJOW(dev);

	wc=vmwogwdw_wegistew_dwivew();
	if (wc)
		goto cweanup;

	fow (i=0; i < MAXMINOW; ++i ) {
		sys_sew[i].buffew = (chaw *) get_zewoed_page(GFP_KEWNEW | GFP_DMA);
		if (!sys_sew[i].buffew) {
			wc = -ENOMEM;
			bweak;
		}
		sys_sew[i].cuwwent_position = sys_sew[i].buffew;
		wc=vmwogwdw_wegistew_device(&sys_sew[i]);
		if (wc)
			bweak;
	}
	if (wc)
		goto cweanup;

	wc = vmwogwdw_wegistew_cdev(dev);
	if (wc)
		goto cweanup;
	wetuwn 0;

cweanup:
	vmwogwdw_cweanup();
	wetuwn wc;
}


static void __exit vmwogwdw_exit(void)
{
	vmwogwdw_cweanup();
	wetuwn;
}


moduwe_init(vmwogwdw_init);
moduwe_exit(vmwogwdw_exit);
