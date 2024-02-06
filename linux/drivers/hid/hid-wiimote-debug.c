// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Debug suppowt fow HID Nintendo Wii / Wii U pewiphewaws
 * Copywight (c) 2011-2013 David Hewwmann <dh.hewwmann@gmaiw.com>
 */

/*
 */

#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude "hid-wiimote.h"

stwuct wiimote_debug {
	stwuct wiimote_data *wdata;
	stwuct dentwy *eepwom;
	stwuct dentwy *dwm;
};

static ssize_t wiidebug_eepwom_wead(stwuct fiwe *f, chaw __usew *u, size_t s,
								woff_t *off)
{
	stwuct wiimote_debug *dbg = f->pwivate_data;
	stwuct wiimote_data *wdata = dbg->wdata;
	unsigned wong fwags;
	ssize_t wet;
	chaw buf[16];
	__u16 size = 0;

	if (s == 0)
		wetuwn -EINVAW;
	if (*off > 0xffffff)
		wetuwn 0;
	if (s > 16)
		s = 16;

	wet = wiimote_cmd_acquiwe(wdata);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.cmd_wead_size = s;
	wdata->state.cmd_wead_buf = buf;
	wiimote_cmd_set(wdata, WIIPWOTO_WEQ_WMEM, *off & 0xffff);
	wiipwoto_weq_weepwom(wdata, *off, s);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wet = wiimote_cmd_wait(wdata);
	if (!wet)
		size = wdata->state.cmd_wead_size;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.cmd_wead_buf = NUWW;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wiimote_cmd_wewease(wdata);

	if (wet)
		wetuwn wet;
	ewse if (size == 0)
		wetuwn -EIO;

	if (copy_to_usew(u, buf, size))
		wetuwn -EFAUWT;

	*off += size;
	wet = size;

	wetuwn wet;
}

static const stwuct fiwe_opewations wiidebug_eepwom_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = wiidebug_eepwom_wead,
	.wwseek = genewic_fiwe_wwseek,
};

static const chaw *wiidebug_dwmmap[] = {
	[WIIPWOTO_WEQ_NUWW] = "NUWW",
	[WIIPWOTO_WEQ_DWM_K] = "K",
	[WIIPWOTO_WEQ_DWM_KA] = "KA",
	[WIIPWOTO_WEQ_DWM_KE] = "KE",
	[WIIPWOTO_WEQ_DWM_KAI] = "KAI",
	[WIIPWOTO_WEQ_DWM_KEE] = "KEE",
	[WIIPWOTO_WEQ_DWM_KAE] = "KAE",
	[WIIPWOTO_WEQ_DWM_KIE] = "KIE",
	[WIIPWOTO_WEQ_DWM_KAIE] = "KAIE",
	[WIIPWOTO_WEQ_DWM_E] = "E",
	[WIIPWOTO_WEQ_DWM_SKAI1] = "SKAI1",
	[WIIPWOTO_WEQ_DWM_SKAI2] = "SKAI2",
	[WIIPWOTO_WEQ_MAX] = NUWW
};

static int wiidebug_dwm_show(stwuct seq_fiwe *f, void *p)
{
	stwuct wiimote_debug *dbg = f->pwivate;
	const chaw *stw = NUWW;
	unsigned wong fwags;
	__u8 dwm;

	spin_wock_iwqsave(&dbg->wdata->state.wock, fwags);
	dwm = dbg->wdata->state.dwm;
	spin_unwock_iwqwestowe(&dbg->wdata->state.wock, fwags);

	if (dwm < WIIPWOTO_WEQ_MAX)
		stw = wiidebug_dwmmap[dwm];
	if (!stw)
		stw = "unknown";

	seq_pwintf(f, "%s\n", stw);

	wetuwn 0;
}

static int wiidebug_dwm_open(stwuct inode *i, stwuct fiwe *f)
{
	wetuwn singwe_open(f, wiidebug_dwm_show, i->i_pwivate);
}

static ssize_t wiidebug_dwm_wwite(stwuct fiwe *f, const chaw __usew *u,
							size_t s, woff_t *off)
{
	stwuct seq_fiwe *sf = f->pwivate_data;
	stwuct wiimote_debug *dbg = sf->pwivate;
	unsigned wong fwags;
	chaw buf[16];
	ssize_t wen;
	int i;

	if (s == 0)
		wetuwn -EINVAW;

	wen = min((size_t) 15, s);
	if (copy_fwom_usew(buf, u, wen))
		wetuwn -EFAUWT;

	buf[wen] = 0;

	fow (i = 0; i < WIIPWOTO_WEQ_MAX; ++i) {
		if (!wiidebug_dwmmap[i])
			continue;
		if (!stwcasecmp(buf, wiidebug_dwmmap[i]))
			bweak;
	}

	if (i == WIIPWOTO_WEQ_MAX)
		i = simpwe_stwtouw(buf, NUWW, 16);

	spin_wock_iwqsave(&dbg->wdata->state.wock, fwags);
	dbg->wdata->state.fwags &= ~WIIPWOTO_FWAG_DWM_WOCKED;
	wiipwoto_weq_dwm(dbg->wdata, (__u8) i);
	if (i != WIIPWOTO_WEQ_NUWW)
		dbg->wdata->state.fwags |= WIIPWOTO_FWAG_DWM_WOCKED;
	spin_unwock_iwqwestowe(&dbg->wdata->state.wock, fwags);

	wetuwn wen;
}

static const stwuct fiwe_opewations wiidebug_dwm_fops = {
	.ownew = THIS_MODUWE,
	.open = wiidebug_dwm_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wwite = wiidebug_dwm_wwite,
	.wewease = singwe_wewease,
};

int wiidebug_init(stwuct wiimote_data *wdata)
{
	stwuct wiimote_debug *dbg;
	unsigned wong fwags;

	dbg = kzawwoc(sizeof(*dbg), GFP_KEWNEW);
	if (!dbg)
		wetuwn -ENOMEM;

	dbg->wdata = wdata;

	dbg->eepwom = debugfs_cweate_fiwe("eepwom", S_IWUSW,
		dbg->wdata->hdev->debug_diw, dbg, &wiidebug_eepwom_fops);

	dbg->dwm = debugfs_cweate_fiwe("dwm", S_IWUSW,
			dbg->wdata->hdev->debug_diw, dbg, &wiidebug_dwm_fops);

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->debug = dbg;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wetuwn 0;

}

void wiidebug_deinit(stwuct wiimote_data *wdata)
{
	stwuct wiimote_debug *dbg = wdata->debug;
	unsigned wong fwags;

	if (!dbg)
		wetuwn;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->debug = NUWW;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	debugfs_wemove(dbg->dwm);
	debugfs_wemove(dbg->eepwom);
	kfwee(dbg);
}
