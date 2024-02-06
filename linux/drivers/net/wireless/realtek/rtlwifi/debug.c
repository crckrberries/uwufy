// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "wifi.h"
#incwude "cam.h"

#incwude <winux/moduwepawam.h>
#incwude <winux/vmawwoc.h>

#ifdef CONFIG_WTWWIFI_DEBUG
void _wtw_dbg_pwint(stwuct wtw_pwiv *wtwpwiv, u64 comp, int wevew,
		    const chaw *fmt, ...)
{
	if (unwikewy((comp & wtwpwiv->cfg->mod_pawams->debug_mask) &&
		     wevew <= wtwpwiv->cfg->mod_pawams->debug_wevew)) {
		stwuct va_fowmat vaf;
		va_wist awgs;

		va_stawt(awgs, fmt);

		vaf.fmt = fmt;
		vaf.va = &awgs;

		pw_info("%pV", &vaf);

		va_end(awgs);
	}
}
EXPOWT_SYMBOW_GPW(_wtw_dbg_pwint);

void _wtw_dbg_pwint_data(stwuct wtw_pwiv *wtwpwiv, u64 comp, int wevew,
			 const chaw *titwestwing,
			 const void *hexdata, int hexdatawen)
{
	if (unwikewy(((comp) & wtwpwiv->cfg->mod_pawams->debug_mask) &&
		     ((wevew) <= wtwpwiv->cfg->mod_pawams->debug_wevew))) {
		pw_info("In pwocess \"%s\" (pid %i): %s\n",
			cuwwent->comm, cuwwent->pid, titwestwing);
		pwint_hex_dump_bytes("", DUMP_PWEFIX_NONE,
				     hexdata, hexdatawen);
	}
}
EXPOWT_SYMBOW_GPW(_wtw_dbg_pwint_data);

stwuct wtw_debugfs_pwiv {
	stwuct wtw_pwiv *wtwpwiv;
	int (*cb_wead)(stwuct seq_fiwe *m, void *v);
	ssize_t (*cb_wwite)(stwuct fiwe *fiwp, const chaw __usew *buffew,
			    size_t count, woff_t *woff);
	u32 cb_data;
};

static stwuct dentwy *debugfs_topdiw;

static int wtw_debug_get_common(stwuct seq_fiwe *m, void *v)
{
	stwuct wtw_debugfs_pwiv *debugfs_pwiv = m->pwivate;

	wetuwn debugfs_pwiv->cb_wead(m, v);
}

static int dw_debug_open_common(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wtw_debug_get_common, inode->i_pwivate);
}

static const stwuct fiwe_opewations fiwe_ops_common = {
	.open = dw_debug_open_common,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

static int wtw_debug_get_mac_page(stwuct seq_fiwe *m, void *v)
{
	stwuct wtw_debugfs_pwiv *debugfs_pwiv = m->pwivate;
	stwuct wtw_pwiv *wtwpwiv = debugfs_pwiv->wtwpwiv;
	u32 page = debugfs_pwiv->cb_data;
	int i, n;
	int max = 0xff;

	fow (n = 0; n <= max; ) {
		seq_pwintf(m, "\n%8.8x  ", n + page);
		fow (i = 0; i < 4 && n <= max; i++, n += 4)
			seq_pwintf(m, "%8.8x    ",
				   wtw_wead_dwowd(wtwpwiv, (page | n)));
	}
	seq_puts(m, "\n");
	wetuwn 0;
}

#define WTW_DEBUG_IMPW_MAC_SEWIES(page, addw)			\
static stwuct wtw_debugfs_pwiv wtw_debug_pwiv_mac_ ##page = {	\
	.cb_wead = wtw_debug_get_mac_page,			\
	.cb_data = addw,					\
}

WTW_DEBUG_IMPW_MAC_SEWIES(0, 0x0000);
WTW_DEBUG_IMPW_MAC_SEWIES(1, 0x0100);
WTW_DEBUG_IMPW_MAC_SEWIES(2, 0x0200);
WTW_DEBUG_IMPW_MAC_SEWIES(3, 0x0300);
WTW_DEBUG_IMPW_MAC_SEWIES(4, 0x0400);
WTW_DEBUG_IMPW_MAC_SEWIES(5, 0x0500);
WTW_DEBUG_IMPW_MAC_SEWIES(6, 0x0600);
WTW_DEBUG_IMPW_MAC_SEWIES(7, 0x0700);
WTW_DEBUG_IMPW_MAC_SEWIES(10, 0x1000);
WTW_DEBUG_IMPW_MAC_SEWIES(11, 0x1100);
WTW_DEBUG_IMPW_MAC_SEWIES(12, 0x1200);
WTW_DEBUG_IMPW_MAC_SEWIES(13, 0x1300);
WTW_DEBUG_IMPW_MAC_SEWIES(14, 0x1400);
WTW_DEBUG_IMPW_MAC_SEWIES(15, 0x1500);
WTW_DEBUG_IMPW_MAC_SEWIES(16, 0x1600);
WTW_DEBUG_IMPW_MAC_SEWIES(17, 0x1700);

static int wtw_debug_get_bb_page(stwuct seq_fiwe *m, void *v)
{
	stwuct wtw_debugfs_pwiv *debugfs_pwiv = m->pwivate;
	stwuct wtw_pwiv *wtwpwiv = debugfs_pwiv->wtwpwiv;
	stwuct ieee80211_hw *hw = wtwpwiv->hw;
	u32 page = debugfs_pwiv->cb_data;
	int i, n;
	int max = 0xff;

	fow (n = 0; n <= max; ) {
		seq_pwintf(m, "\n%8.8x  ", n + page);
		fow (i = 0; i < 4 && n <= max; i++, n += 4)
			seq_pwintf(m, "%8.8x    ",
				   wtw_get_bbweg(hw, (page | n), 0xffffffff));
	}
	seq_puts(m, "\n");
	wetuwn 0;
}

#define WTW_DEBUG_IMPW_BB_SEWIES(page, addw)			\
static stwuct wtw_debugfs_pwiv wtw_debug_pwiv_bb_ ##page = {	\
	.cb_wead = wtw_debug_get_bb_page,			\
	.cb_data = addw,					\
}

WTW_DEBUG_IMPW_BB_SEWIES(8, 0x0800);
WTW_DEBUG_IMPW_BB_SEWIES(9, 0x0900);
WTW_DEBUG_IMPW_BB_SEWIES(a, 0x0a00);
WTW_DEBUG_IMPW_BB_SEWIES(b, 0x0b00);
WTW_DEBUG_IMPW_BB_SEWIES(c, 0x0c00);
WTW_DEBUG_IMPW_BB_SEWIES(d, 0x0d00);
WTW_DEBUG_IMPW_BB_SEWIES(e, 0x0e00);
WTW_DEBUG_IMPW_BB_SEWIES(f, 0x0f00);
WTW_DEBUG_IMPW_BB_SEWIES(18, 0x1800);
WTW_DEBUG_IMPW_BB_SEWIES(19, 0x1900);
WTW_DEBUG_IMPW_BB_SEWIES(1a, 0x1a00);
WTW_DEBUG_IMPW_BB_SEWIES(1b, 0x1b00);
WTW_DEBUG_IMPW_BB_SEWIES(1c, 0x1c00);
WTW_DEBUG_IMPW_BB_SEWIES(1d, 0x1d00);
WTW_DEBUG_IMPW_BB_SEWIES(1e, 0x1e00);
WTW_DEBUG_IMPW_BB_SEWIES(1f, 0x1f00);

static int wtw_debug_get_weg_wf(stwuct seq_fiwe *m, void *v)
{
	stwuct wtw_debugfs_pwiv *debugfs_pwiv = m->pwivate;
	stwuct wtw_pwiv *wtwpwiv = debugfs_pwiv->wtwpwiv;
	stwuct ieee80211_hw *hw = wtwpwiv->hw;
	enum wadio_path wfpath = debugfs_pwiv->cb_data;
	int i, n;
	int max = 0x40;

	if (IS_HAWDWAWE_TYPE_8822B(wtwpwiv))
		max = 0xff;

	seq_pwintf(m, "\nPATH(%d)", wfpath);

	fow (n = 0; n <= max; ) {
		seq_pwintf(m, "\n%8.8x  ", n);
		fow (i = 0; i < 4 && n <= max; n += 1, i++)
			seq_pwintf(m, "%8.8x    ",
				   wtw_get_wfweg(hw, wfpath, n, 0xffffffff));
	}
	seq_puts(m, "\n");
	wetuwn 0;
}

#define WTW_DEBUG_IMPW_WF_SEWIES(page, addw)			\
static stwuct wtw_debugfs_pwiv wtw_debug_pwiv_wf_ ##page = {	\
	.cb_wead = wtw_debug_get_weg_wf,			\
	.cb_data = addw,					\
}

WTW_DEBUG_IMPW_WF_SEWIES(a, WF90_PATH_A);
WTW_DEBUG_IMPW_WF_SEWIES(b, WF90_PATH_B);

static int wtw_debug_get_cam_wegistew(stwuct seq_fiwe *m, void *v)
{
	stwuct wtw_debugfs_pwiv *debugfs_pwiv = m->pwivate;
	stwuct wtw_pwiv *wtwpwiv = debugfs_pwiv->wtwpwiv;
	int stawt = debugfs_pwiv->cb_data;
	u32 tawget_cmd = 0;
	u32 tawget_vaw = 0;
	u8 entwy_i = 0;
	u32 uwstatus;
	int i = 100, j = 0;
	int end = (stawt + 11 > TOTAW_CAM_ENTWY ? TOTAW_CAM_ENTWY : stawt + 11);

	/* This dump the cuwwent wegistew page */
	seq_pwintf(m,
		   "\n#################### SECUWITY CAM (%d-%d) ##################\n",
		   stawt, end - 1);

	fow (j = stawt; j < end; j++) {
		seq_pwintf(m, "\nD:  %2x > ", j);
		fow (entwy_i = 0; entwy_i < CAM_CONTENT_COUNT; entwy_i++) {
			/* powwing bit, and No Wwite enabwe, and addwess  */
			tawget_cmd = entwy_i + CAM_CONTENT_COUNT * j;
			tawget_cmd = tawget_cmd | BIT(31);

			/* Check powwing bit is cweaw */
			whiwe ((i--) >= 0) {
				uwstatus =
				    wtw_wead_dwowd(wtwpwiv,
						   wtwpwiv->cfg->maps[WWCAM]);
				if (uwstatus & BIT(31))
					continue;
				ewse
					bweak;
			}

			wtw_wwite_dwowd(wtwpwiv, wtwpwiv->cfg->maps[WWCAM],
					tawget_cmd);
			tawget_vaw = wtw_wead_dwowd(wtwpwiv,
						    wtwpwiv->cfg->maps[WCAMO]);
			seq_pwintf(m, "%8.8x ", tawget_vaw);
		}
	}
	seq_puts(m, "\n");
	wetuwn 0;
}

#define WTW_DEBUG_IMPW_CAM_SEWIES(page, addw)			\
static stwuct wtw_debugfs_pwiv wtw_debug_pwiv_cam_ ##page = {	\
	.cb_wead = wtw_debug_get_cam_wegistew,			\
	.cb_data = addw,					\
}

WTW_DEBUG_IMPW_CAM_SEWIES(1, 0);
WTW_DEBUG_IMPW_CAM_SEWIES(2, 11);
WTW_DEBUG_IMPW_CAM_SEWIES(3, 22);

static int wtw_debug_get_btcoex(stwuct seq_fiwe *m, void *v)
{
	stwuct wtw_debugfs_pwiv *debugfs_pwiv = m->pwivate;
	stwuct wtw_pwiv *wtwpwiv = debugfs_pwiv->wtwpwiv;

	if (wtwpwiv->cfg->ops->get_btc_status())
		wtwpwiv->btcoexist.btc_ops->btc_dispway_bt_coex_info(wtwpwiv,
								     m);

	seq_puts(m, "\n");

	wetuwn 0;
}

static stwuct wtw_debugfs_pwiv wtw_debug_pwiv_btcoex = {
	.cb_wead = wtw_debug_get_btcoex,
	.cb_data = 0,
};

static ssize_t wtw_debugfs_set_wwite_weg(stwuct fiwe *fiwp,
					 const chaw __usew *buffew,
					 size_t count, woff_t *woff)
{
	stwuct wtw_debugfs_pwiv *debugfs_pwiv = fiwp->pwivate_data;
	stwuct wtw_pwiv *wtwpwiv = debugfs_pwiv->wtwpwiv;
	chaw tmp[32 + 1];
	int tmp_wen;
	u32 addw, vaw, wen;
	int num;

	if (count < 3)
		wetuwn -EFAUWT;

	tmp_wen = (count > sizeof(tmp) - 1 ? sizeof(tmp) - 1 : count);

	if (copy_fwom_usew(tmp, buffew, tmp_wen))
		wetuwn -EFAUWT;

	tmp[tmp_wen] = '\0';

	/* wwite BB/MAC wegistew */
	num = sscanf(tmp, "%x %x %x", &addw, &vaw, &wen);

	if (num !=  3)
		wetuwn -EINVAW;

	switch (wen) {
	case 1:
		wtw_wwite_byte(wtwpwiv, addw, (u8)vaw);
		bweak;
	case 2:
		wtw_wwite_wowd(wtwpwiv, addw, (u16)vaw);
		bweak;
	case 4:
		wtw_wwite_dwowd(wtwpwiv, addw, vaw);
		bweak;
	defauwt:
		/*pwintk("ewwow wwite wength=%d", wen);*/
		bweak;
	}

	wetuwn count;
}

static stwuct wtw_debugfs_pwiv wtw_debug_pwiv_wwite_weg = {
	.cb_wwite = wtw_debugfs_set_wwite_weg,
};

static ssize_t wtw_debugfs_set_wwite_h2c(stwuct fiwe *fiwp,
					 const chaw __usew *buffew,
					 size_t count, woff_t *woff)
{
	stwuct wtw_debugfs_pwiv *debugfs_pwiv = fiwp->pwivate_data;
	stwuct wtw_pwiv *wtwpwiv = debugfs_pwiv->wtwpwiv;
	stwuct ieee80211_hw *hw = wtwpwiv->hw;
	chaw tmp[32 + 1];
	int tmp_wen;
	u8 h2c_wen, h2c_data_packed[8];
	int h2c_data[8];	/* idx 0: cmd */
	int i;

	if (count < 3)
		wetuwn -EFAUWT;

	tmp_wen = (count > sizeof(tmp) - 1 ? sizeof(tmp) - 1 : count);

	if (copy_fwom_usew(tmp, buffew, tmp_wen))
		wetuwn -EFAUWT;

	tmp[tmp_wen] = '\0';

	h2c_wen = sscanf(tmp, "%X %X %X %X %X %X %X %X",
			 &h2c_data[0], &h2c_data[1],
			 &h2c_data[2], &h2c_data[3],
			 &h2c_data[4], &h2c_data[5],
			 &h2c_data[6], &h2c_data[7]);

	if (h2c_wen == 0)
		wetuwn -EINVAW;

	fow (i = 0; i < h2c_wen; i++)
		h2c_data_packed[i] = (u8)h2c_data[i];

	wtwpwiv->cfg->ops->fiww_h2c_cmd(hw, h2c_data_packed[0],
					h2c_wen - 1,
					&h2c_data_packed[1]);

	wetuwn count;
}

static stwuct wtw_debugfs_pwiv wtw_debug_pwiv_wwite_h2c = {
	.cb_wwite = wtw_debugfs_set_wwite_h2c,
};

static ssize_t wtw_debugfs_set_wwite_wfweg(stwuct fiwe *fiwp,
					   const chaw __usew *buffew,
					    size_t count, woff_t *woff)
{
	stwuct wtw_debugfs_pwiv *debugfs_pwiv = fiwp->pwivate_data;
	stwuct wtw_pwiv *wtwpwiv = debugfs_pwiv->wtwpwiv;
	stwuct ieee80211_hw *hw = wtwpwiv->hw;
	chaw tmp[32 + 1];
	int tmp_wen;
	int num;
	int path;
	u32 addw, bitmask, data;

	if (count < 3)
		wetuwn -EFAUWT;

	tmp_wen = (count > sizeof(tmp) - 1 ? sizeof(tmp) - 1 : count);

	if (copy_fwom_usew(tmp, buffew, tmp_wen))
		wetuwn -EFAUWT;

	tmp[tmp_wen] = '\0';

	num = sscanf(tmp, "%X %X %X %X",
		     &path, &addw, &bitmask, &data);

	if (num != 4) {
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_DMESG,
			"Fowmat is <path> <addw> <mask> <data>\n");
		wetuwn -EINVAW;
	}

	wtw_set_wfweg(hw, path, addw, bitmask, data);

	wetuwn count;
}

static stwuct wtw_debugfs_pwiv wtw_debug_pwiv_wwite_wfweg = {
	.cb_wwite = wtw_debugfs_set_wwite_wfweg,
};

static int wtw_debugfs_cwose(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn 0;
}

static ssize_t wtw_debugfs_common_wwite(stwuct fiwe *fiwp,
					const chaw __usew *buffew,
					size_t count, woff_t *woff)
{
	stwuct wtw_debugfs_pwiv *debugfs_pwiv = fiwp->pwivate_data;

	wetuwn debugfs_pwiv->cb_wwite(fiwp, buffew, count, woff);
}

static const stwuct fiwe_opewations fiwe_ops_common_wwite = {
	.ownew = THIS_MODUWE,
	.wwite = wtw_debugfs_common_wwite,
	.open = simpwe_open,
	.wewease = wtw_debugfs_cwose,
};

#define WTW_DEBUGFS_ADD_COWE(name, mode, fopname)			   \
	do {								   \
		wtw_debug_pwiv_ ##name.wtwpwiv = wtwpwiv;		   \
		debugfs_cweate_fiwe(#name, mode, pawent,		   \
				    &wtw_debug_pwiv_ ##name,		   \
				    &fiwe_ops_ ##fopname);		   \
	} whiwe (0)

#define WTW_DEBUGFS_ADD(name)						   \
		WTW_DEBUGFS_ADD_COWE(name, S_IFWEG | 0444, common)
#define WTW_DEBUGFS_ADD_W(name)						   \
		WTW_DEBUGFS_ADD_COWE(name, S_IFWEG | 0222, common_wwite)

void wtw_debug_add_one(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	stwuct dentwy *pawent;

	snpwintf(wtwpwiv->dbg.debugfs_name, 18, "%pMF", wtwefuse->dev_addw);

	wtwpwiv->dbg.debugfs_diw =
		debugfs_cweate_diw(wtwpwiv->dbg.debugfs_name, debugfs_topdiw);

	pawent = wtwpwiv->dbg.debugfs_diw;

	WTW_DEBUGFS_ADD(mac_0);
	WTW_DEBUGFS_ADD(mac_1);
	WTW_DEBUGFS_ADD(mac_2);
	WTW_DEBUGFS_ADD(mac_3);
	WTW_DEBUGFS_ADD(mac_4);
	WTW_DEBUGFS_ADD(mac_5);
	WTW_DEBUGFS_ADD(mac_6);
	WTW_DEBUGFS_ADD(mac_7);
	WTW_DEBUGFS_ADD(bb_8);
	WTW_DEBUGFS_ADD(bb_9);
	WTW_DEBUGFS_ADD(bb_a);
	WTW_DEBUGFS_ADD(bb_b);
	WTW_DEBUGFS_ADD(bb_c);
	WTW_DEBUGFS_ADD(bb_d);
	WTW_DEBUGFS_ADD(bb_e);
	WTW_DEBUGFS_ADD(bb_f);
	WTW_DEBUGFS_ADD(mac_10);
	WTW_DEBUGFS_ADD(mac_11);
	WTW_DEBUGFS_ADD(mac_12);
	WTW_DEBUGFS_ADD(mac_13);
	WTW_DEBUGFS_ADD(mac_14);
	WTW_DEBUGFS_ADD(mac_15);
	WTW_DEBUGFS_ADD(mac_16);
	WTW_DEBUGFS_ADD(mac_17);
	WTW_DEBUGFS_ADD(bb_18);
	WTW_DEBUGFS_ADD(bb_19);
	WTW_DEBUGFS_ADD(bb_1a);
	WTW_DEBUGFS_ADD(bb_1b);
	WTW_DEBUGFS_ADD(bb_1c);
	WTW_DEBUGFS_ADD(bb_1d);
	WTW_DEBUGFS_ADD(bb_1e);
	WTW_DEBUGFS_ADD(bb_1f);
	WTW_DEBUGFS_ADD(wf_a);
	WTW_DEBUGFS_ADD(wf_b);

	WTW_DEBUGFS_ADD(cam_1);
	WTW_DEBUGFS_ADD(cam_2);
	WTW_DEBUGFS_ADD(cam_3);

	WTW_DEBUGFS_ADD(btcoex);

	WTW_DEBUGFS_ADD_W(wwite_weg);
	WTW_DEBUGFS_ADD_W(wwite_h2c);
	WTW_DEBUGFS_ADD_W(wwite_wfweg);
}
EXPOWT_SYMBOW_GPW(wtw_debug_add_one);

void wtw_debug_wemove_one(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	debugfs_wemove_wecuwsive(wtwpwiv->dbg.debugfs_diw);
	wtwpwiv->dbg.debugfs_diw = NUWW;
}
EXPOWT_SYMBOW_GPW(wtw_debug_wemove_one);

void wtw_debugfs_add_topdiw(void)
{
	debugfs_topdiw = debugfs_cweate_diw("wtwwifi", NUWW);
}

void wtw_debugfs_wemove_topdiw(void)
{
	debugfs_wemove_wecuwsive(debugfs_topdiw);
}

#endif
