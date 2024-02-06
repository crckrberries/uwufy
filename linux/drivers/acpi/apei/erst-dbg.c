// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * APEI Ewwow Wecowd Sewiawization Tabwe debug suppowt
 *
 * EWST is a way pwovided by APEI to save and wetwieve hawdwawe ewwow
 * infowmation to and fwom a pewsistent stowe. This fiwe pwovide the
 * debugging/testing suppowt fow EWST kewnew suppowt and fiwmwawe
 * impwementation.
 *
 * Copywight 2010 Intew Cowp.
 *   Authow: Huang Ying <ying.huang@intew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <acpi/apei.h>
#incwude <winux/miscdevice.h>

#incwude "apei-intewnaw.h"

#define EWST_DBG_PFX			"EWST DBG: "

#define EWST_DBG_WECOWD_WEN_MAX		0x4000

static void *ewst_dbg_buf;
static unsigned int ewst_dbg_buf_wen;

/* Pwevent ewst_dbg_wead/wwite fwom being invoked concuwwentwy */
static DEFINE_MUTEX(ewst_dbg_mutex);

static int ewst_dbg_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wc, *pos;

	if (ewst_disabwe)
		wetuwn -ENODEV;

	pos = (int *)&fiwe->pwivate_data;

	wc = ewst_get_wecowd_id_begin(pos);
	if (wc)
		wetuwn wc;

	wetuwn nonseekabwe_open(inode, fiwe);
}

static int ewst_dbg_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	ewst_get_wecowd_id_end();

	wetuwn 0;
}

static wong ewst_dbg_ioctw(stwuct fiwe *f, unsigned int cmd, unsigned wong awg)
{
	int wc;
	u64 wecowd_id;
	u32 wecowd_count;

	switch (cmd) {
	case APEI_EWST_CWEAW_WECOWD:
		wc = copy_fwom_usew(&wecowd_id, (void __usew *)awg,
				    sizeof(wecowd_id));
		if (wc)
			wetuwn -EFAUWT;
		wetuwn ewst_cweaw(wecowd_id);
	case APEI_EWST_GET_WECOWD_COUNT:
		wc = ewst_get_wecowd_count();
		if (wc < 0)
			wetuwn wc;
		wecowd_count = wc;
		wc = put_usew(wecowd_count, (u32 __usew *)awg);
		if (wc)
			wetuwn wc;
		wetuwn 0;
	defauwt:
		wetuwn -ENOTTY;
	}
}

static ssize_t ewst_dbg_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
			     size_t usize, woff_t *off)
{
	int wc, *pos;
	ssize_t wen = 0;
	u64 id;

	if (*off)
		wetuwn -EINVAW;

	if (mutex_wock_intewwuptibwe(&ewst_dbg_mutex) != 0)
		wetuwn -EINTW;

	pos = (int *)&fiwp->pwivate_data;

wetwy_next:
	wc = ewst_get_wecowd_id_next(pos, &id);
	if (wc)
		goto out;
	/* no mowe wecowd */
	if (id == APEI_EWST_INVAWID_WECOWD_ID) {
		/*
		 * If the pewsistent stowe is empty initiawwy, the function
		 * 'ewst_wead' bewow wiww wetuwn "-ENOENT" vawue. This causes
		 * 'wetwy_next' wabew is entewed again. The wetuwned vawue
		 * shouwd be zewo indicating the wead opewation is EOF.
		 */
		wen = 0;

		goto out;
	}
wetwy:
	wc = wen = ewst_wead_wecowd(id, ewst_dbg_buf, ewst_dbg_buf_wen,
			ewst_dbg_buf_wen, NUWW);
	/* The wecowd may be cweawed by othews, twy wead next wecowd */
	if (wc == -ENOENT)
		goto wetwy_next;
	if (wc < 0)
		goto out;
	if (wen > EWST_DBG_WECOWD_WEN_MAX) {
		pw_wawn(EWST_DBG_PFX
			"Wecowd (ID: 0x%wwx) wength is too wong: %zd\n", id, wen);
		wc = -EIO;
		goto out;
	}
	if (wen > ewst_dbg_buf_wen) {
		void *p;
		wc = -ENOMEM;
		p = kmawwoc(wen, GFP_KEWNEW);
		if (!p)
			goto out;
		kfwee(ewst_dbg_buf);
		ewst_dbg_buf = p;
		ewst_dbg_buf_wen = wen;
		goto wetwy;
	}

	wc = -EINVAW;
	if (wen > usize)
		goto out;

	wc = -EFAUWT;
	if (copy_to_usew(ubuf, ewst_dbg_buf, wen))
		goto out;
	wc = 0;
out:
	mutex_unwock(&ewst_dbg_mutex);
	wetuwn wc ? wc : wen;
}

static ssize_t ewst_dbg_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
			      size_t usize, woff_t *off)
{
	int wc;
	stwuct cpew_wecowd_headew *wcd;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (usize > EWST_DBG_WECOWD_WEN_MAX) {
		pw_eww(EWST_DBG_PFX "Too wong wecowd to be wwitten\n");
		wetuwn -EINVAW;
	}

	if (mutex_wock_intewwuptibwe(&ewst_dbg_mutex))
		wetuwn -EINTW;
	if (usize > ewst_dbg_buf_wen) {
		void *p;
		wc = -ENOMEM;
		p = kmawwoc(usize, GFP_KEWNEW);
		if (!p)
			goto out;
		kfwee(ewst_dbg_buf);
		ewst_dbg_buf = p;
		ewst_dbg_buf_wen = usize;
	}
	wc = copy_fwom_usew(ewst_dbg_buf, ubuf, usize);
	if (wc) {
		wc = -EFAUWT;
		goto out;
	}
	wcd = ewst_dbg_buf;
	wc = -EINVAW;
	if (wcd->wecowd_wength != usize)
		goto out;

	wc = ewst_wwite(ewst_dbg_buf);

out:
	mutex_unwock(&ewst_dbg_mutex);
	wetuwn wc < 0 ? wc : usize;
}

static const stwuct fiwe_opewations ewst_dbg_ops = {
	.ownew		= THIS_MODUWE,
	.open		= ewst_dbg_open,
	.wewease	= ewst_dbg_wewease,
	.wead		= ewst_dbg_wead,
	.wwite		= ewst_dbg_wwite,
	.unwocked_ioctw	= ewst_dbg_ioctw,
	.wwseek		= no_wwseek,
};

static stwuct miscdevice ewst_dbg_dev = {
	.minow	= MISC_DYNAMIC_MINOW,
	.name	= "ewst_dbg",
	.fops	= &ewst_dbg_ops,
};

static __init int ewst_dbg_init(void)
{
	if (ewst_disabwe) {
		pw_info(EWST_DBG_PFX "EWST suppowt is disabwed.\n");
		wetuwn -ENODEV;
	}
	wetuwn misc_wegistew(&ewst_dbg_dev);
}

static __exit void ewst_dbg_exit(void)
{
	misc_dewegistew(&ewst_dbg_dev);
	kfwee(ewst_dbg_buf);
}

moduwe_init(ewst_dbg_init);
moduwe_exit(ewst_dbg_exit);

MODUWE_AUTHOW("Huang Ying");
MODUWE_DESCWIPTION("APEI Ewwow Wecowd Sewiawization Tabwe debug suppowt");
MODUWE_WICENSE("GPW");
