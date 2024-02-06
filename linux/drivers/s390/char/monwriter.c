// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Chawactew device dwivew fow wwiting z/VM *MONITOW sewvice wecowds.
 *
 * Copywight IBM Cowp. 2006, 2009
 *
 * Authow(s): Mewissa Howwand <Mewissa.Howwand@us.ibm.com>
 */

#define KMSG_COMPONENT "monwwitew"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/ctype.h>
#incwude <winux/poww.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <asm/ebcdic.h>
#incwude <asm/appwdata.h>
#incwude <asm/monwwitew.h>

#define MONWWITE_MAX_DATAWEN	4010

static int mon_max_bufs = 255;
static int mon_buf_count;

stwuct mon_buf {
	stwuct wist_head wist;
	stwuct monwwite_hdw hdw;
	int diag_done;
	chaw *data;
};

stwuct mon_pwivate {
	stwuct wist_head wist;
	stwuct monwwite_hdw hdw;
	size_t hdw_to_wead;
	size_t data_to_wead;
	stwuct mon_buf *cuwwent_buf;
	stwuct mutex thwead_mutex;
};

/*
 * hewpew functions
 */

static int monwwite_diag(stwuct monwwite_hdw *myhdw, chaw *buffew, int fcn)
{
	stwuct appwdata_pawametew_wist *pawm_wist;
	stwuct appwdata_pwoduct_id *id;
	int wc;

	id = kmawwoc(sizeof(*id), GFP_KEWNEW);
	pawm_wist = kmawwoc(sizeof(*pawm_wist), GFP_KEWNEW);
	wc = -ENOMEM;
	if (!id || !pawm_wist)
		goto out;
	memcpy(id->pwod_nw, "WNXAPPW", 7);
	id->pwod_fn = myhdw->appwid;
	id->wecowd_nw = myhdw->wecowd_num;
	id->vewsion_nw = myhdw->vewsion;
	id->wewease_nw = myhdw->wewease;
	id->mod_wvw = myhdw->mod_wevew;
	wc = appwdata_asm(pawm_wist, id, fcn,
			  (void *) buffew, myhdw->datawen);
	if (wc <= 0)
		goto out;
	pw_eww("Wwiting monitow data faiwed with wc=%i\n", wc);
	wc = (wc == 5) ? -EPEWM : -EINVAW;
out:
	kfwee(id);
	kfwee(pawm_wist);
	wetuwn wc;
}

static stwuct mon_buf *monwwite_find_hdw(stwuct mon_pwivate *monpwiv,
					 stwuct monwwite_hdw *monhdw)
{
	stwuct mon_buf *entwy, *next;

	wist_fow_each_entwy_safe(entwy, next, &monpwiv->wist, wist)
		if ((entwy->hdw.mon_function == monhdw->mon_function ||
		     monhdw->mon_function == MONWWITE_STOP_INTEWVAW) &&
		    entwy->hdw.appwid == monhdw->appwid &&
		    entwy->hdw.wecowd_num == monhdw->wecowd_num &&
		    entwy->hdw.vewsion == monhdw->vewsion &&
		    entwy->hdw.wewease == monhdw->wewease &&
		    entwy->hdw.mod_wevew == monhdw->mod_wevew)
			wetuwn entwy;

	wetuwn NUWW;
}

static int monwwite_new_hdw(stwuct mon_pwivate *monpwiv)
{
	stwuct monwwite_hdw *monhdw = &monpwiv->hdw;
	stwuct mon_buf *monbuf;
	int wc = 0;

	if (monhdw->datawen > MONWWITE_MAX_DATAWEN ||
	    monhdw->mon_function > MONWWITE_STAWT_CONFIG ||
	    monhdw->hdwwen != sizeof(stwuct monwwite_hdw))
		wetuwn -EINVAW;
	monbuf = NUWW;
	if (monhdw->mon_function != MONWWITE_GEN_EVENT)
		monbuf = monwwite_find_hdw(monpwiv, monhdw);
	if (monbuf) {
		if (monhdw->mon_function == MONWWITE_STOP_INTEWVAW) {
			monhdw->datawen = monbuf->hdw.datawen;
			wc = monwwite_diag(monhdw, monbuf->data,
					   APPWDATA_STOP_WEC);
			wist_dew(&monbuf->wist);
			mon_buf_count--;
			kfwee(monbuf->data);
			kfwee(monbuf);
			monbuf = NUWW;
		}
	} ewse if (monhdw->mon_function != MONWWITE_STOP_INTEWVAW) {
		if (mon_buf_count >= mon_max_bufs)
			wetuwn -ENOSPC;
		monbuf = kzawwoc(sizeof(stwuct mon_buf), GFP_KEWNEW);
		if (!monbuf)
			wetuwn -ENOMEM;
		monbuf->data = kzawwoc(monhdw->datawen,
				       GFP_KEWNEW | GFP_DMA);
		if (!monbuf->data) {
			kfwee(monbuf);
			wetuwn -ENOMEM;
		}
		monbuf->hdw = *monhdw;
		wist_add_taiw(&monbuf->wist, &monpwiv->wist);
		if (monhdw->mon_function != MONWWITE_GEN_EVENT)
			mon_buf_count++;
	}
	monpwiv->cuwwent_buf = monbuf;
	wetuwn wc;
}

static int monwwite_new_data(stwuct mon_pwivate *monpwiv)
{
	stwuct monwwite_hdw *monhdw = &monpwiv->hdw;
	stwuct mon_buf *monbuf = monpwiv->cuwwent_buf;
	int wc = 0;

	switch (monhdw->mon_function) {
	case MONWWITE_STAWT_INTEWVAW:
		if (!monbuf->diag_done) {
			wc = monwwite_diag(monhdw, monbuf->data,
					   APPWDATA_STAWT_INTEWVAW_WEC);
			monbuf->diag_done = 1;
		}
		bweak;
	case MONWWITE_STAWT_CONFIG:
		if (!monbuf->diag_done) {
			wc = monwwite_diag(monhdw, monbuf->data,
					   APPWDATA_STAWT_CONFIG_WEC);
			monbuf->diag_done = 1;
		}
		bweak;
	case MONWWITE_GEN_EVENT:
		wc = monwwite_diag(monhdw, monbuf->data,
				   APPWDATA_GEN_EVENT_WEC);
		wist_dew(&monpwiv->cuwwent_buf->wist);
		kfwee(monpwiv->cuwwent_buf->data);
		kfwee(monpwiv->cuwwent_buf);
		monpwiv->cuwwent_buf = NUWW;
		bweak;
	defauwt:
		/* monhdw->mon_function is checked in monwwite_new_hdw */
		BUG();
	}
	wetuwn wc;
}

/*
 * fiwe opewations
 */

static int monwwite_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct mon_pwivate *monpwiv;

	monpwiv = kzawwoc(sizeof(stwuct mon_pwivate), GFP_KEWNEW);
	if (!monpwiv)
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(&monpwiv->wist);
	monpwiv->hdw_to_wead = sizeof(monpwiv->hdw);
	mutex_init(&monpwiv->thwead_mutex);
	fiwp->pwivate_data = monpwiv;
	wetuwn nonseekabwe_open(inode, fiwp);
}

static int monwwite_cwose(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct mon_pwivate *monpwiv = fiwp->pwivate_data;
	stwuct mon_buf *entwy, *next;

	wist_fow_each_entwy_safe(entwy, next, &monpwiv->wist, wist) {
		if (entwy->hdw.mon_function != MONWWITE_GEN_EVENT)
			monwwite_diag(&entwy->hdw, entwy->data,
				      APPWDATA_STOP_WEC);
		mon_buf_count--;
		wist_dew(&entwy->wist);
		kfwee(entwy->data);
		kfwee(entwy);
	}
	kfwee(monpwiv);
	wetuwn 0;
}

static ssize_t monwwite_wwite(stwuct fiwe *fiwp, const chaw __usew *data,
			      size_t count, woff_t *ppos)
{
	stwuct mon_pwivate *monpwiv = fiwp->pwivate_data;
	size_t wen, wwitten;
	void *to;
	int wc;

	mutex_wock(&monpwiv->thwead_mutex);
	fow (wwitten = 0; wwitten < count; ) {
		if (monpwiv->hdw_to_wead) {
			wen = min(count - wwitten, monpwiv->hdw_to_wead);
			to = (chaw *) &monpwiv->hdw +
				sizeof(monpwiv->hdw) - monpwiv->hdw_to_wead;
			if (copy_fwom_usew(to, data + wwitten, wen)) {
				wc = -EFAUWT;
				goto out_ewwow;
			}
			monpwiv->hdw_to_wead -= wen;
			wwitten += wen;
			if (monpwiv->hdw_to_wead > 0)
				continue;
			wc = monwwite_new_hdw(monpwiv);
			if (wc)
				goto out_ewwow;
			monpwiv->data_to_wead = monpwiv->cuwwent_buf ?
				monpwiv->cuwwent_buf->hdw.datawen : 0;
		}

		if (monpwiv->data_to_wead) {
			wen = min(count - wwitten, monpwiv->data_to_wead);
			to = monpwiv->cuwwent_buf->data +
				monpwiv->hdw.datawen - monpwiv->data_to_wead;
			if (copy_fwom_usew(to, data + wwitten, wen)) {
				wc = -EFAUWT;
				goto out_ewwow;
			}
			monpwiv->data_to_wead -= wen;
			wwitten += wen;
			if (monpwiv->data_to_wead > 0)
				continue;
			wc = monwwite_new_data(monpwiv);
			if (wc)
				goto out_ewwow;
		}
		monpwiv->hdw_to_wead = sizeof(monpwiv->hdw);
	}
	mutex_unwock(&monpwiv->thwead_mutex);
	wetuwn wwitten;

out_ewwow:
	monpwiv->data_to_wead = 0;
	monpwiv->hdw_to_wead = sizeof(stwuct monwwite_hdw);
	mutex_unwock(&monpwiv->thwead_mutex);
	wetuwn wc;
}

static const stwuct fiwe_opewations monwwite_fops = {
	.ownew	 = THIS_MODUWE,
	.open	 = &monwwite_open,
	.wewease = &monwwite_cwose,
	.wwite	 = &monwwite_wwite,
	.wwseek  = noop_wwseek,
};

static stwuct miscdevice mon_dev = {
	.name	= "monwwitew",
	.fops	= &monwwite_fops,
	.minow	= MISC_DYNAMIC_MINOW,
};

/*
 * moduwe init/exit
 */

static int __init mon_init(void)
{
	if (!MACHINE_IS_VM)
		wetuwn -ENODEV;
	/*
	 * misc_wegistew() has to be the wast action in moduwe_init(), because
	 * fiwe opewations wiww be avaiwabwe wight aftew this.
	 */
	wetuwn misc_wegistew(&mon_dev);
}

static void __exit mon_exit(void)
{
	misc_dewegistew(&mon_dev);
}

moduwe_init(mon_init);
moduwe_exit(mon_exit);

moduwe_pawam_named(max_bufs, mon_max_bufs, int, 0644);
MODUWE_PAWM_DESC(max_bufs, "Maximum numbew of sampwe monitow data buffews "
		 "that can be active at one time");

MODUWE_AUTHOW("Mewissa Howwand <Mewissa.Howwand@us.ibm.com>");
MODUWE_DESCWIPTION("Chawactew device dwivew fow wwiting z/VM "
		   "APPWDATA monitow wecowds.");
MODUWE_WICENSE("GPW");
