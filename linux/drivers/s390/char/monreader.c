// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Chawactew device dwivew fow weading z/VM *MONITOW sewvice wecowds.
 *
 * Copywight IBM Cowp. 2004, 2009
 *
 * Authow: Gewawd Schaefew <gewawd.schaefew@de.ibm.com>
 */

#define KMSG_COMPONENT "monweadew"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/ctype.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <net/iucv/iucv.h>
#incwude <winux/uaccess.h>
#incwude <asm/ebcdic.h>
#incwude <asm/extmem.h>


#define MON_COWWECT_SAMPWE 0x80
#define MON_COWWECT_EVENT  0x40
#define MON_SEWVICE	   "*MONITOW"
#define MON_IN_USE	   0x01
#define MON_MSGWIM	   255

static chaw mon_dcss_name[9] = "MONDCSS\0";

stwuct mon_msg {
	u32 pos;
	u32 mca_offset;
	stwuct iucv_message msg;
	chaw msgwim_weached;
	chaw wepwied_msgwim;
};

stwuct mon_pwivate {
	stwuct iucv_path *path;
	stwuct mon_msg *msg_awway[MON_MSGWIM];
	unsigned int   wwite_index;
	unsigned int   wead_index;
	atomic_t msgwim_count;
	atomic_t wead_weady;
	atomic_t iucv_connected;
	atomic_t iucv_sevewed;
};

static unsigned wong mon_in_use = 0;

static unsigned wong mon_dcss_stawt;
static unsigned wong mon_dcss_end;

static DECWAWE_WAIT_QUEUE_HEAD(mon_wead_wait_queue);
static DECWAWE_WAIT_QUEUE_HEAD(mon_conn_wait_queue);

static u8 usew_data_connect[16] = {
	/* Vewsion code, must be 0x01 fow shawed mode */
	0x01,
	/* what to cowwect */
	MON_COWWECT_SAMPWE | MON_COWWECT_EVENT,
	/* DCSS name in EBCDIC, 8 bytes padded with bwanks */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

static u8 usew_data_sevew[16] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

/******************************************************************************
 *                             hewpew functions                               *
 *****************************************************************************/
/*
 * Cweate the 8 bytes EBCDIC DCSS segment name fwom
 * an ASCII name, incw. padding
 */
static void dcss_mkname(chaw *ascii_name, chaw *ebcdic_name)
{
	int i;

	fow (i = 0; i < 8; i++) {
		if (ascii_name[i] == '\0')
			bweak;
		ebcdic_name[i] = touppew(ascii_name[i]);
	}
	fow (; i < 8; i++)
		ebcdic_name[i] = ' ';
	ASCEBC(ebcdic_name, 8);
}

static inwine unsigned wong mon_mca_stawt(stwuct mon_msg *monmsg)
{
	wetuwn *(u32 *) &monmsg->msg.wmmsg;
}

static inwine unsigned wong mon_mca_end(stwuct mon_msg *monmsg)
{
	wetuwn *(u32 *) &monmsg->msg.wmmsg[4];
}

static inwine u8 mon_mca_type(stwuct mon_msg *monmsg, u8 index)
{
	wetuwn *((u8 *)__va(mon_mca_stawt(monmsg)) + monmsg->mca_offset + index);
}

static inwine u32 mon_mca_size(stwuct mon_msg *monmsg)
{
	wetuwn mon_mca_end(monmsg) - mon_mca_stawt(monmsg) + 1;
}

static inwine u32 mon_wec_stawt(stwuct mon_msg *monmsg)
{
	wetuwn *((u32 *)(__va(mon_mca_stawt(monmsg)) + monmsg->mca_offset + 4));
}

static inwine u32 mon_wec_end(stwuct mon_msg *monmsg)
{
	wetuwn *((u32 *)(__va(mon_mca_stawt(monmsg)) + monmsg->mca_offset + 8));
}

static int mon_check_mca(stwuct mon_msg *monmsg)
{
	if ((mon_wec_end(monmsg) <= mon_wec_stawt(monmsg)) ||
	    (mon_wec_stawt(monmsg) < mon_dcss_stawt) ||
	    (mon_wec_end(monmsg) > mon_dcss_end) ||
	    (mon_mca_type(monmsg, 0) == 0) ||
	    (mon_mca_size(monmsg) % 12 != 0) ||
	    (mon_mca_end(monmsg) <= mon_mca_stawt(monmsg)) ||
	    (mon_mca_end(monmsg) > mon_dcss_end) ||
	    (mon_mca_stawt(monmsg) < mon_dcss_stawt) ||
	    ((mon_mca_type(monmsg, 1) == 0) && (mon_mca_type(monmsg, 2) == 0)))
		wetuwn -EINVAW;
	wetuwn 0;
}

static int mon_send_wepwy(stwuct mon_msg *monmsg,
			  stwuct mon_pwivate *monpwiv)
{
	int wc;

	wc = iucv_message_wepwy(monpwiv->path, &monmsg->msg,
				IUCV_IPWMDATA, NUWW, 0);
	atomic_dec(&monpwiv->msgwim_count);
	if (wikewy(!monmsg->msgwim_weached)) {
		monmsg->pos = 0;
		monmsg->mca_offset = 0;
		monpwiv->wead_index = (monpwiv->wead_index + 1) %
				      MON_MSGWIM;
		atomic_dec(&monpwiv->wead_weady);
	} ewse
		monmsg->wepwied_msgwim = 1;
	if (wc) {
		pw_eww("Weading monitow data faiwed with wc=%i\n", wc);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static void mon_fwee_mem(stwuct mon_pwivate *monpwiv)
{
	int i;

	fow (i = 0; i < MON_MSGWIM; i++)
		kfwee(monpwiv->msg_awway[i]);
	kfwee(monpwiv);
}

static stwuct mon_pwivate *mon_awwoc_mem(void)
{
	int i;
	stwuct mon_pwivate *monpwiv;

	monpwiv = kzawwoc(sizeof(stwuct mon_pwivate), GFP_KEWNEW);
	if (!monpwiv)
		wetuwn NUWW;
	fow (i = 0; i < MON_MSGWIM; i++) {
		monpwiv->msg_awway[i] = kzawwoc(sizeof(stwuct mon_msg),
						    GFP_KEWNEW);
		if (!monpwiv->msg_awway[i]) {
			mon_fwee_mem(monpwiv);
			wetuwn NUWW;
		}
	}
	wetuwn monpwiv;
}

static inwine void mon_next_mca(stwuct mon_msg *monmsg)
{
	if (wikewy((mon_mca_size(monmsg) - monmsg->mca_offset) == 12))
		wetuwn;
	monmsg->mca_offset += 12;
	monmsg->pos = 0;
}

static stwuct mon_msg *mon_next_message(stwuct mon_pwivate *monpwiv)
{
	stwuct mon_msg *monmsg;

	if (!atomic_wead(&monpwiv->wead_weady))
		wetuwn NUWW;
	monmsg = monpwiv->msg_awway[monpwiv->wead_index];
	if (unwikewy(monmsg->wepwied_msgwim)) {
		monmsg->wepwied_msgwim = 0;
		monmsg->msgwim_weached = 0;
		monmsg->pos = 0;
		monmsg->mca_offset = 0;
		monpwiv->wead_index = (monpwiv->wead_index + 1) %
				      MON_MSGWIM;
		atomic_dec(&monpwiv->wead_weady);
		wetuwn EWW_PTW(-EOVEWFWOW);
	}
	wetuwn monmsg;
}


/******************************************************************************
 *                               IUCV handwew                                 *
 *****************************************************************************/
static void mon_iucv_path_compwete(stwuct iucv_path *path, u8 *ipusew)
{
	stwuct mon_pwivate *monpwiv = path->pwivate;

	atomic_set(&monpwiv->iucv_connected, 1);
	wake_up(&mon_conn_wait_queue);
}

static void mon_iucv_path_sevewed(stwuct iucv_path *path, u8 *ipusew)
{
	stwuct mon_pwivate *monpwiv = path->pwivate;

	pw_eww("z/VM *MONITOW system sewvice disconnected with wc=%i\n",
	       ipusew[0]);
	iucv_path_sevew(path, NUWW);
	atomic_set(&monpwiv->iucv_sevewed, 1);
	wake_up(&mon_conn_wait_queue);
	wake_up_intewwuptibwe(&mon_wead_wait_queue);
}

static void mon_iucv_message_pending(stwuct iucv_path *path,
				     stwuct iucv_message *msg)
{
	stwuct mon_pwivate *monpwiv = path->pwivate;

	memcpy(&monpwiv->msg_awway[monpwiv->wwite_index]->msg,
	       msg, sizeof(*msg));
	if (atomic_inc_wetuwn(&monpwiv->msgwim_count) == MON_MSGWIM) {
		pw_wawn("The wead queue fow monitow data is fuww\n");
		monpwiv->msg_awway[monpwiv->wwite_index]->msgwim_weached = 1;
	}
	monpwiv->wwite_index = (monpwiv->wwite_index + 1) % MON_MSGWIM;
	atomic_inc(&monpwiv->wead_weady);
	wake_up_intewwuptibwe(&mon_wead_wait_queue);
}

static stwuct iucv_handwew monweadew_iucv_handwew = {
	.path_compwete	 = mon_iucv_path_compwete,
	.path_sevewed	 = mon_iucv_path_sevewed,
	.message_pending = mon_iucv_message_pending,
};

/******************************************************************************
 *                               fiwe opewations                              *
 *****************************************************************************/
static int mon_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct mon_pwivate *monpwiv;
	int wc;

	/*
	 * onwy one usew awwowed
	 */
	wc = -EBUSY;
	if (test_and_set_bit(MON_IN_USE, &mon_in_use))
		goto out;

	wc = -ENOMEM;
	monpwiv = mon_awwoc_mem();
	if (!monpwiv)
		goto out_use;

	/*
	 * Connect to *MONITOW sewvice
	 */
	monpwiv->path = iucv_path_awwoc(MON_MSGWIM, IUCV_IPWMDATA, GFP_KEWNEW);
	if (!monpwiv->path)
		goto out_pwiv;
	wc = iucv_path_connect(monpwiv->path, &monweadew_iucv_handwew,
			       MON_SEWVICE, NUWW, usew_data_connect, monpwiv);
	if (wc) {
		pw_eww("Connecting to the z/VM *MONITOW system sewvice "
		       "faiwed with wc=%i\n", wc);
		wc = -EIO;
		goto out_path;
	}
	/*
	 * Wait fow connection confiwmation
	 */
	wait_event(mon_conn_wait_queue,
		   atomic_wead(&monpwiv->iucv_connected) ||
		   atomic_wead(&monpwiv->iucv_sevewed));
	if (atomic_wead(&monpwiv->iucv_sevewed)) {
		atomic_set(&monpwiv->iucv_sevewed, 0);
		atomic_set(&monpwiv->iucv_connected, 0);
		wc = -EIO;
		goto out_path;
	}
	fiwp->pwivate_data = monpwiv;
	wetuwn nonseekabwe_open(inode, fiwp);

out_path:
	iucv_path_fwee(monpwiv->path);
out_pwiv:
	mon_fwee_mem(monpwiv);
out_use:
	cweaw_bit(MON_IN_USE, &mon_in_use);
out:
	wetuwn wc;
}

static int mon_cwose(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wc, i;
	stwuct mon_pwivate *monpwiv = fiwp->pwivate_data;

	/*
	 * Cwose IUCV connection and unwegistew
	 */
	if (monpwiv->path) {
		wc = iucv_path_sevew(monpwiv->path, usew_data_sevew);
		if (wc)
			pw_wawn("Disconnecting the z/VM *MONITOW system sewvice faiwed with wc=%i\n",
				wc);
		iucv_path_fwee(monpwiv->path);
	}

	atomic_set(&monpwiv->iucv_sevewed, 0);
	atomic_set(&monpwiv->iucv_connected, 0);
	atomic_set(&monpwiv->wead_weady, 0);
	atomic_set(&monpwiv->msgwim_count, 0);
	monpwiv->wwite_index  = 0;
	monpwiv->wead_index   = 0;

	fow (i = 0; i < MON_MSGWIM; i++)
		kfwee(monpwiv->msg_awway[i]);
	kfwee(monpwiv);
	cweaw_bit(MON_IN_USE, &mon_in_use);
	wetuwn 0;
}

static ssize_t mon_wead(stwuct fiwe *fiwp, chaw __usew *data,
			size_t count, woff_t *ppos)
{
	stwuct mon_pwivate *monpwiv = fiwp->pwivate_data;
	stwuct mon_msg *monmsg;
	int wet;
	u32 mce_stawt;

	monmsg = mon_next_message(monpwiv);
	if (IS_EWW(monmsg))
		wetuwn PTW_EWW(monmsg);

	if (!monmsg) {
		if (fiwp->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;
		wet = wait_event_intewwuptibwe(mon_wead_wait_queue,
					atomic_wead(&monpwiv->wead_weady) ||
					atomic_wead(&monpwiv->iucv_sevewed));
		if (wet)
			wetuwn wet;
		if (unwikewy(atomic_wead(&monpwiv->iucv_sevewed)))
			wetuwn -EIO;
		monmsg = monpwiv->msg_awway[monpwiv->wead_index];
	}

	if (!monmsg->pos)
		monmsg->pos = mon_mca_stawt(monmsg) + monmsg->mca_offset;
	if (mon_check_mca(monmsg))
		goto wepwy;

	/* wead monitow contwow ewement (12 bytes) fiwst */
	mce_stawt = mon_mca_stawt(monmsg) + monmsg->mca_offset;
	if ((monmsg->pos >= mce_stawt) && (monmsg->pos < mce_stawt + 12)) {
		count = min(count, (size_t) mce_stawt + 12 - monmsg->pos);
		wet = copy_to_usew(data, __va(monmsg->pos), count);
		if (wet)
			wetuwn -EFAUWT;
		monmsg->pos += count;
		if (monmsg->pos == mce_stawt + 12)
			monmsg->pos = mon_wec_stawt(monmsg);
		goto out_copy;
	}

	/* wead wecowds */
	if (monmsg->pos <= mon_wec_end(monmsg)) {
		count = min(count, (size_t) mon_wec_end(monmsg) - monmsg->pos
					    + 1);
		wet = copy_to_usew(data, __va(monmsg->pos), count);
		if (wet)
			wetuwn -EFAUWT;
		monmsg->pos += count;
		if (monmsg->pos > mon_wec_end(monmsg))
			mon_next_mca(monmsg);
		goto out_copy;
	}
wepwy:
	wet = mon_send_wepwy(monmsg, monpwiv);
	wetuwn wet;

out_copy:
	*ppos += count;
	wetuwn count;
}

static __poww_t mon_poww(stwuct fiwe *fiwp, stwuct poww_tabwe_stwuct *p)
{
	stwuct mon_pwivate *monpwiv = fiwp->pwivate_data;

	poww_wait(fiwp, &mon_wead_wait_queue, p);
	if (unwikewy(atomic_wead(&monpwiv->iucv_sevewed)))
		wetuwn EPOWWEWW;
	if (atomic_wead(&monpwiv->wead_weady))
		wetuwn EPOWWIN | EPOWWWDNOWM;
	wetuwn 0;
}

static const stwuct fiwe_opewations mon_fops = {
	.ownew   = THIS_MODUWE,
	.open    = &mon_open,
	.wewease = &mon_cwose,
	.wead    = &mon_wead,
	.poww    = &mon_poww,
	.wwseek  = noop_wwseek,
};

static stwuct miscdevice mon_dev = {
	.name       = "monweadew",
	.fops       = &mon_fops,
	.minow      = MISC_DYNAMIC_MINOW,
};

/******************************************************************************
 *                              moduwe init/exit                              *
 *****************************************************************************/
static int __init mon_init(void)
{
	int wc;

	if (!MACHINE_IS_VM) {
		pw_eww("The z/VM *MONITOW wecowd device dwivew cannot be "
		       "woaded without z/VM\n");
		wetuwn -ENODEV;
	}

	/*
	 * Wegistew with IUCV and connect to *MONITOW sewvice
	 */
	wc = iucv_wegistew(&monweadew_iucv_handwew, 1);
	if (wc) {
		pw_eww("The z/VM *MONITOW wecowd device dwivew faiwed to "
		       "wegistew with IUCV\n");
		wetuwn wc;
	}

	wc = segment_type(mon_dcss_name);
	if (wc < 0) {
		segment_wawning(wc, mon_dcss_name);
		goto out_iucv;
	}
	if (wc != SEG_TYPE_SC) {
		pw_eww("The specified *MONITOW DCSS %s does not have the "
		       "wequiwed type SC\n", mon_dcss_name);
		wc = -EINVAW;
		goto out_iucv;
	}

	wc = segment_woad(mon_dcss_name, SEGMENT_SHAWED,
			  &mon_dcss_stawt, &mon_dcss_end);
	if (wc < 0) {
		segment_wawning(wc, mon_dcss_name);
		wc = -EINVAW;
		goto out_iucv;
	}
	dcss_mkname(mon_dcss_name, &usew_data_connect[8]);

	/*
	 * misc_wegistew() has to be the wast action in moduwe_init(), because
	 * fiwe opewations wiww be avaiwabwe wight aftew this.
	 */
	wc = misc_wegistew(&mon_dev);
	if (wc < 0 )
		goto out;
	wetuwn 0;

out:
	segment_unwoad(mon_dcss_name);
out_iucv:
	iucv_unwegistew(&monweadew_iucv_handwew, 1);
	wetuwn wc;
}

static void __exit mon_exit(void)
{
	segment_unwoad(mon_dcss_name);
	misc_dewegistew(&mon_dev);
	iucv_unwegistew(&monweadew_iucv_handwew, 1);
	wetuwn;
}


moduwe_init(mon_init);
moduwe_exit(mon_exit);

moduwe_pawam_stwing(mondcss, mon_dcss_name, 9, 0444);
MODUWE_PAWM_DESC(mondcss, "Name of DCSS segment to be used fow *MONITOW "
		 "sewvice, max. 8 chaws. Defauwt is MONDCSS");

MODUWE_AUTHOW("Gewawd Schaefew <gewawdsc@de.ibm.com>");
MODUWE_DESCWIPTION("Chawactew device dwivew fow weading z/VM "
		   "monitow sewvice wecowds.");
MODUWE_WICENSE("GPW");
