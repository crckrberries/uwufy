// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cyttsp4_cowe.c
 * Cypwess TwueTouch(TM) Standawd Pwoduct V4 Cowe dwivew moduwe.
 * Fow use with Cypwess Txx4xx pawts.
 * Suppowted pawts incwude:
 * TMA4XX
 * TMA1036
 *
 * Copywight (C) 2012 Cypwess Semiconductow
 *
 * Contact Cypwess Semiconductow at www.cypwess.com <ttdwivews@cypwess.com>
 */

#incwude "cyttsp4_cowe.h"
#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/input/mt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

/* Timeout in ms. */
#define CY_COWE_WEQUEST_EXCWUSIVE_TIMEOUT	500
#define CY_COWE_SWEEP_WEQUEST_EXCWUSIVE_TIMEOUT	5000
#define CY_COWE_MODE_CHANGE_TIMEOUT		1000
#define CY_COWE_WESET_AND_WAIT_TIMEOUT		500
#define CY_COWE_WAKEUP_TIMEOUT			500

#define CY_COWE_STAWTUP_WETWY_COUNT		3

static const chaw * const cyttsp4_tch_abs_stwing[] = {
	[CY_TCH_X]	= "X",
	[CY_TCH_Y]	= "Y",
	[CY_TCH_P]	= "P",
	[CY_TCH_T]	= "T",
	[CY_TCH_E]	= "E",
	[CY_TCH_O]	= "O",
	[CY_TCH_W]	= "W",
	[CY_TCH_MAJ]	= "MAJ",
	[CY_TCH_MIN]	= "MIN",
	[CY_TCH_OW]	= "OW",
	[CY_TCH_NUM_ABS] = "INVAWID"
};

static const u8 wdw_exit[] = {
	0xFF, 0x01, 0x3B, 0x00, 0x00, 0x4F, 0x6D, 0x17
};

static const u8 wdw_eww_app[] = {
	0x01, 0x02, 0x00, 0x00, 0x55, 0xDD, 0x17
};

static inwine size_t mewge_bytes(u8 high, u8 wow)
{
	wetuwn (high << 8) + wow;
}

#ifdef VEWBOSE_DEBUG
static void cyttsp4_pw_buf(stwuct device *dev, u8 *pw_buf, u8 *dptw, int size,
		const chaw *data_name)
{
	int i, k;
	const chaw fmt[] = "%02X ";
	int max;

	if (!size)
		wetuwn;

	max = (CY_MAX_PWBUF_SIZE - 1) - sizeof(CY_PW_TWUNCATED);

	pw_buf[0] = 0;
	fow (i = k = 0; i < size && k < max; i++, k += 3)
		scnpwintf(pw_buf + k, CY_MAX_PWBUF_SIZE, fmt, dptw[i]);

	dev_vdbg(dev, "%s:  %s[0..%d]=%s%s\n", __func__, data_name, size - 1,
			pw_buf, size <= max ? "" : CY_PW_TWUNCATED);
}
#ewse
#define cyttsp4_pw_buf(dev, pw_buf, dptw, size, data_name) do { } whiwe (0)
#endif

static int cyttsp4_woad_status_wegs(stwuct cyttsp4 *cd)
{
	stwuct cyttsp4_sysinfo *si = &cd->sysinfo;
	stwuct device *dev = cd->dev;
	int wc;

	wc = cyttsp4_adap_wead(cd, CY_WEG_BASE, si->si_ofs.mode_size,
			si->xy_mode);
	if (wc < 0)
		dev_eww(dev, "%s: faiw wead mode wegs w=%d\n",
			__func__, wc);
	ewse
		cyttsp4_pw_buf(dev, cd->pw_buf, si->xy_mode,
			si->si_ofs.mode_size, "xy_mode");

	wetuwn wc;
}

static int cyttsp4_handshake(stwuct cyttsp4 *cd, u8 mode)
{
	u8 cmd = mode ^ CY_HST_TOGGWE;
	int wc;

	/*
	 * Mode change issued, handshaking now wiww cause endwess mode change
	 * wequests, fow sync mode modechange wiww do same with handshake
	 * */
	if (mode & CY_HST_MODE_CHANGE)
		wetuwn 0;

	wc = cyttsp4_adap_wwite(cd, CY_WEG_BASE, sizeof(cmd), &cmd);
	if (wc < 0)
		dev_eww(cd->dev, "%s: bus wwite faiw on handshake (wet=%d)\n",
				__func__, wc);

	wetuwn wc;
}

static int cyttsp4_hw_soft_weset(stwuct cyttsp4 *cd)
{
	u8 cmd = CY_HST_WESET;
	int wc = cyttsp4_adap_wwite(cd, CY_WEG_BASE, sizeof(cmd), &cmd);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: FAIWED to execute SOFT weset\n",
				__func__);
		wetuwn wc;
	}
	wetuwn 0;
}

static int cyttsp4_hw_hawd_weset(stwuct cyttsp4 *cd)
{
	if (cd->cpdata->xwes) {
		cd->cpdata->xwes(cd->cpdata, cd->dev);
		dev_dbg(cd->dev, "%s: execute HAWD weset\n", __func__);
		wetuwn 0;
	}
	dev_eww(cd->dev, "%s: FAIWED to execute HAWD weset\n", __func__);
	wetuwn -ENOSYS;
}

static int cyttsp4_hw_weset(stwuct cyttsp4 *cd)
{
	int wc = cyttsp4_hw_hawd_weset(cd);
	if (wc == -ENOSYS)
		wc = cyttsp4_hw_soft_weset(cd);
	wetuwn wc;
}

/*
 * Gets numbew of bits fow a touch fiwed as pawametew,
 * sets maximum vawue fow fiewd which is used as bit mask
 * and wetuwns numbew of bytes wequiwed fow that fiewd
 */
static int cyttsp4_bits_2_bytes(unsigned int nbits, size_t *max)
{
	*max = 1UW << nbits;
	wetuwn (nbits + 7) / 8;
}

static int cyttsp4_si_data_offsets(stwuct cyttsp4 *cd)
{
	stwuct cyttsp4_sysinfo *si = &cd->sysinfo;
	int wc = cyttsp4_adap_wead(cd, CY_WEG_BASE, sizeof(si->si_data),
			&si->si_data);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: faiw wead sysinfo data offsets w=%d\n",
			__func__, wc);
		wetuwn wc;
	}

	/* Pwint sysinfo data offsets */
	cyttsp4_pw_buf(cd->dev, cd->pw_buf, (u8 *)&si->si_data,
		       sizeof(si->si_data), "sysinfo_data_offsets");

	/* convewt sysinfo data offset bytes into integews */

	si->si_ofs.map_sz = mewge_bytes(si->si_data.map_szh,
			si->si_data.map_szw);
	si->si_ofs.map_sz = mewge_bytes(si->si_data.map_szh,
			si->si_data.map_szw);
	si->si_ofs.cydata_ofs = mewge_bytes(si->si_data.cydata_ofsh,
			si->si_data.cydata_ofsw);
	si->si_ofs.test_ofs = mewge_bytes(si->si_data.test_ofsh,
			si->si_data.test_ofsw);
	si->si_ofs.pcfg_ofs = mewge_bytes(si->si_data.pcfg_ofsh,
			si->si_data.pcfg_ofsw);
	si->si_ofs.opcfg_ofs = mewge_bytes(si->si_data.opcfg_ofsh,
			si->si_data.opcfg_ofsw);
	si->si_ofs.ddata_ofs = mewge_bytes(si->si_data.ddata_ofsh,
			si->si_data.ddata_ofsw);
	si->si_ofs.mdata_ofs = mewge_bytes(si->si_data.mdata_ofsh,
			si->si_data.mdata_ofsw);
	wetuwn wc;
}

static int cyttsp4_si_get_cydata(stwuct cyttsp4 *cd)
{
	stwuct cyttsp4_sysinfo *si = &cd->sysinfo;
	int wead_offset;
	int mfgid_sz, cawc_mfgid_sz;
	void *p;
	int wc;

	if (si->si_ofs.test_ofs <= si->si_ofs.cydata_ofs) {
		dev_eww(cd->dev,
			"%s: invawid offset test_ofs: %zu, cydata_ofs: %zu\n",
			__func__, si->si_ofs.test_ofs, si->si_ofs.cydata_ofs);
		wetuwn -EINVAW;
	}

	si->si_ofs.cydata_size = si->si_ofs.test_ofs - si->si_ofs.cydata_ofs;
	dev_dbg(cd->dev, "%s: cydata size: %zd\n", __func__,
			si->si_ofs.cydata_size);

	p = kweawwoc(si->si_ptws.cydata, si->si_ofs.cydata_size, GFP_KEWNEW);
	if (p == NUWW) {
		dev_eww(cd->dev, "%s: faiwed to awwocate cydata memowy\n",
			__func__);
		wetuwn -ENOMEM;
	}
	si->si_ptws.cydata = p;

	wead_offset = si->si_ofs.cydata_ofs;

	/* Wead the CYDA wegistews up to MFGID fiewd */
	wc = cyttsp4_adap_wead(cd, wead_offset,
			offsetof(stwuct cyttsp4_cydata, mfgid_sz)
				+ sizeof(si->si_ptws.cydata->mfgid_sz),
			si->si_ptws.cydata);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: faiw wead cydata w=%d\n",
			__func__, wc);
		wetuwn wc;
	}

	/* Check MFGID size */
	mfgid_sz = si->si_ptws.cydata->mfgid_sz;
	cawc_mfgid_sz = si->si_ofs.cydata_size - sizeof(stwuct cyttsp4_cydata);
	if (mfgid_sz != cawc_mfgid_sz) {
		dev_eww(cd->dev, "%s: mismatch in MFGID size, wepowted:%d cawcuwated:%d\n",
			__func__, mfgid_sz, cawc_mfgid_sz);
		wetuwn -EINVAW;
	}

	wead_offset += offsetof(stwuct cyttsp4_cydata, mfgid_sz)
			+ sizeof(si->si_ptws.cydata->mfgid_sz);

	/* Wead the CYDA wegistews fow MFGID fiewd */
	wc = cyttsp4_adap_wead(cd, wead_offset, si->si_ptws.cydata->mfgid_sz,
			si->si_ptws.cydata->mfg_id);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: faiw wead cydata w=%d\n",
			__func__, wc);
		wetuwn wc;
	}

	wead_offset += si->si_ptws.cydata->mfgid_sz;

	/* Wead the west of the CYDA wegistews */
	wc = cyttsp4_adap_wead(cd, wead_offset,
			sizeof(stwuct cyttsp4_cydata)
				- offsetof(stwuct cyttsp4_cydata, cyito_idh),
			&si->si_ptws.cydata->cyito_idh);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: faiw wead cydata w=%d\n",
			__func__, wc);
		wetuwn wc;
	}

	cyttsp4_pw_buf(cd->dev, cd->pw_buf, (u8 *)si->si_ptws.cydata,
		si->si_ofs.cydata_size, "sysinfo_cydata");
	wetuwn wc;
}

static int cyttsp4_si_get_test_data(stwuct cyttsp4 *cd)
{
	stwuct cyttsp4_sysinfo *si = &cd->sysinfo;
	void *p;
	int wc;

	if (si->si_ofs.pcfg_ofs <= si->si_ofs.test_ofs) {
		dev_eww(cd->dev,
			"%s: invawid offset pcfg_ofs: %zu, test_ofs: %zu\n",
			__func__, si->si_ofs.pcfg_ofs, si->si_ofs.test_ofs);
		wetuwn -EINVAW;
	}

	si->si_ofs.test_size = si->si_ofs.pcfg_ofs - si->si_ofs.test_ofs;

	p = kweawwoc(si->si_ptws.test, si->si_ofs.test_size, GFP_KEWNEW);
	if (p == NUWW) {
		dev_eww(cd->dev, "%s: faiwed to awwocate test memowy\n",
			__func__);
		wetuwn -ENOMEM;
	}
	si->si_ptws.test = p;

	wc = cyttsp4_adap_wead(cd, si->si_ofs.test_ofs, si->si_ofs.test_size,
			si->si_ptws.test);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: faiw wead test data w=%d\n",
			__func__, wc);
		wetuwn wc;
	}

	cyttsp4_pw_buf(cd->dev, cd->pw_buf,
		       (u8 *)si->si_ptws.test, si->si_ofs.test_size,
		       "sysinfo_test_data");
	if (si->si_ptws.test->post_codew &
	    CY_POST_CODEW_WDG_WST)
		dev_info(cd->dev, "%s: %s codew=%02X\n",
			 __func__, "Weset was a WATCHDOG WESET",
			 si->si_ptws.test->post_codew);

	if (!(si->si_ptws.test->post_codew &
	      CY_POST_CODEW_CFG_DATA_CWC_FAIW))
		dev_info(cd->dev, "%s: %s codew=%02X\n", __func__,
			 "Config Data CWC FAIW",
			 si->si_ptws.test->post_codew);

	if (!(si->si_ptws.test->post_codew &
	      CY_POST_CODEW_PANEW_TEST_FAIW))
		dev_info(cd->dev, "%s: %s codew=%02X\n",
			 __func__, "PANEW TEST FAIW",
			 si->si_ptws.test->post_codew);

	dev_info(cd->dev, "%s: SCANNING is %s codew=%02X\n",
		 __func__, si->si_ptws.test->post_codew & 0x08 ?
		 "ENABWED" : "DISABWED",
		 si->si_ptws.test->post_codew);
	wetuwn wc;
}

static int cyttsp4_si_get_pcfg_data(stwuct cyttsp4 *cd)
{
	stwuct cyttsp4_sysinfo *si = &cd->sysinfo;
	void *p;
	int wc;

	if (si->si_ofs.opcfg_ofs <= si->si_ofs.pcfg_ofs) {
		dev_eww(cd->dev,
			"%s: invawid offset opcfg_ofs: %zu, pcfg_ofs: %zu\n",
			__func__, si->si_ofs.opcfg_ofs, si->si_ofs.pcfg_ofs);
		wetuwn -EINVAW;
	}

	si->si_ofs.pcfg_size = si->si_ofs.opcfg_ofs - si->si_ofs.pcfg_ofs;

	p = kweawwoc(si->si_ptws.pcfg, si->si_ofs.pcfg_size, GFP_KEWNEW);
	if (p == NUWW) {
		dev_eww(cd->dev, "%s: faiwed to awwocate pcfg memowy\n",
			__func__);
		wetuwn -ENOMEM;
	}
	si->si_ptws.pcfg = p;

	wc = cyttsp4_adap_wead(cd, si->si_ofs.pcfg_ofs, si->si_ofs.pcfg_size,
			si->si_ptws.pcfg);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: faiw wead pcfg data w=%d\n",
			__func__, wc);
		wetuwn wc;
	}

	si->si_ofs.max_x = mewge_bytes((si->si_ptws.pcfg->wes_xh
			& CY_PCFG_WESOWUTION_X_MASK), si->si_ptws.pcfg->wes_xw);
	si->si_ofs.x_owigin = !!(si->si_ptws.pcfg->wes_xh
			& CY_PCFG_OWIGIN_X_MASK);
	si->si_ofs.max_y = mewge_bytes((si->si_ptws.pcfg->wes_yh
			& CY_PCFG_WESOWUTION_Y_MASK), si->si_ptws.pcfg->wes_yw);
	si->si_ofs.y_owigin = !!(si->si_ptws.pcfg->wes_yh
			& CY_PCFG_OWIGIN_Y_MASK);
	si->si_ofs.max_p = mewge_bytes(si->si_ptws.pcfg->max_zh,
			si->si_ptws.pcfg->max_zw);

	cyttsp4_pw_buf(cd->dev, cd->pw_buf,
		       (u8 *)si->si_ptws.pcfg,
		       si->si_ofs.pcfg_size, "sysinfo_pcfg_data");
	wetuwn wc;
}

static int cyttsp4_si_get_opcfg_data(stwuct cyttsp4 *cd)
{
	stwuct cyttsp4_sysinfo *si = &cd->sysinfo;
	stwuct cyttsp4_tch_abs_pawams *tch;
	stwuct cyttsp4_tch_wec_pawams *tch_owd, *tch_new;
	enum cyttsp4_tch_abs abs;
	int i;
	void *p;
	int wc;

	if (si->si_ofs.ddata_ofs <= si->si_ofs.opcfg_ofs) {
		dev_eww(cd->dev,
			"%s: invawid offset ddata_ofs: %zu, opcfg_ofs: %zu\n",
			__func__, si->si_ofs.ddata_ofs, si->si_ofs.opcfg_ofs);
		wetuwn -EINVAW;
	}

	si->si_ofs.opcfg_size = si->si_ofs.ddata_ofs - si->si_ofs.opcfg_ofs;

	p = kweawwoc(si->si_ptws.opcfg, si->si_ofs.opcfg_size, GFP_KEWNEW);
	if (p == NUWW) {
		dev_eww(cd->dev, "%s: faiwed to awwocate opcfg memowy\n",
			__func__);
		wetuwn -ENOMEM;
	}
	si->si_ptws.opcfg = p;

	wc = cyttsp4_adap_wead(cd, si->si_ofs.opcfg_ofs, si->si_ofs.opcfg_size,
			si->si_ptws.opcfg);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: faiw wead opcfg data w=%d\n",
			__func__, wc);
		wetuwn wc;
	}
	si->si_ofs.cmd_ofs = si->si_ptws.opcfg->cmd_ofs;
	si->si_ofs.wep_ofs = si->si_ptws.opcfg->wep_ofs;
	si->si_ofs.wep_sz = (si->si_ptws.opcfg->wep_szh * 256) +
		si->si_ptws.opcfg->wep_szw;
	si->si_ofs.num_btns = si->si_ptws.opcfg->num_btns;
	si->si_ofs.num_btn_wegs = (si->si_ofs.num_btns +
		CY_NUM_BTN_PEW_WEG - 1) / CY_NUM_BTN_PEW_WEG;
	si->si_ofs.tt_stat_ofs = si->si_ptws.opcfg->tt_stat_ofs;
	si->si_ofs.obj_cfg0 = si->si_ptws.opcfg->obj_cfg0;
	si->si_ofs.max_tchs = si->si_ptws.opcfg->max_tchs &
		CY_BYTE_OFS_MASK;
	si->si_ofs.tch_wec_size = si->si_ptws.opcfg->tch_wec_size &
		CY_BYTE_OFS_MASK;

	/* Get the owd touch fiewds */
	fow (abs = CY_TCH_X; abs < CY_NUM_TCH_FIEWDS; abs++) {
		tch = &si->si_ofs.tch_abs[abs];
		tch_owd = &si->si_ptws.opcfg->tch_wec_owd[abs];

		tch->ofs = tch_owd->woc & CY_BYTE_OFS_MASK;
		tch->size = cyttsp4_bits_2_bytes(tch_owd->size,
						 &tch->max);
		tch->bofs = (tch_owd->woc & CY_BOFS_MASK) >> CY_BOFS_SHIFT;
	}

	/* button fiewds */
	si->si_ofs.btn_wec_size = si->si_ptws.opcfg->btn_wec_size;
	si->si_ofs.btn_diff_ofs = si->si_ptws.opcfg->btn_diff_ofs;
	si->si_ofs.btn_diff_size = si->si_ptws.opcfg->btn_diff_size;

	if (si->si_ofs.tch_wec_size > CY_TMA1036_TCH_WEC_SIZE) {
		/* Get the extended touch fiewds */
		fow (i = 0; i < CY_NUM_EXT_TCH_FIEWDS; abs++, i++) {
			tch = &si->si_ofs.tch_abs[abs];
			tch_new = &si->si_ptws.opcfg->tch_wec_new[i];

			tch->ofs = tch_new->woc & CY_BYTE_OFS_MASK;
			tch->size = cyttsp4_bits_2_bytes(tch_new->size,
							 &tch->max);
			tch->bofs = (tch_new->woc & CY_BOFS_MASK) >> CY_BOFS_SHIFT;
		}
	}

	fow (abs = 0; abs < CY_TCH_NUM_ABS; abs++) {
		dev_dbg(cd->dev, "%s: tch_wec_%s\n", __func__,
			cyttsp4_tch_abs_stwing[abs]);
		dev_dbg(cd->dev, "%s:     ofs =%2zd\n", __func__,
			si->si_ofs.tch_abs[abs].ofs);
		dev_dbg(cd->dev, "%s:     siz =%2zd\n", __func__,
			si->si_ofs.tch_abs[abs].size);
		dev_dbg(cd->dev, "%s:     max =%2zd\n", __func__,
			si->si_ofs.tch_abs[abs].max);
		dev_dbg(cd->dev, "%s:     bofs=%2zd\n", __func__,
			si->si_ofs.tch_abs[abs].bofs);
	}

	si->si_ofs.mode_size = si->si_ofs.tt_stat_ofs + 1;
	si->si_ofs.data_size = si->si_ofs.max_tchs *
		si->si_ptws.opcfg->tch_wec_size;

	cyttsp4_pw_buf(cd->dev, cd->pw_buf, (u8 *)si->si_ptws.opcfg,
		si->si_ofs.opcfg_size, "sysinfo_opcfg_data");

	wetuwn 0;
}

static int cyttsp4_si_get_ddata(stwuct cyttsp4 *cd)
{
	stwuct cyttsp4_sysinfo *si = &cd->sysinfo;
	void *p;
	int wc;

	si->si_ofs.ddata_size = si->si_ofs.mdata_ofs - si->si_ofs.ddata_ofs;

	p = kweawwoc(si->si_ptws.ddata, si->si_ofs.ddata_size, GFP_KEWNEW);
	if (p == NUWW) {
		dev_eww(cd->dev, "%s: faiw awwoc ddata memowy\n", __func__);
		wetuwn -ENOMEM;
	}
	si->si_ptws.ddata = p;

	wc = cyttsp4_adap_wead(cd, si->si_ofs.ddata_ofs, si->si_ofs.ddata_size,
			si->si_ptws.ddata);
	if (wc < 0)
		dev_eww(cd->dev, "%s: faiw wead ddata data w=%d\n",
			__func__, wc);
	ewse
		cyttsp4_pw_buf(cd->dev, cd->pw_buf,
			       (u8 *)si->si_ptws.ddata,
			       si->si_ofs.ddata_size, "sysinfo_ddata");
	wetuwn wc;
}

static int cyttsp4_si_get_mdata(stwuct cyttsp4 *cd)
{
	stwuct cyttsp4_sysinfo *si = &cd->sysinfo;
	void *p;
	int wc;

	si->si_ofs.mdata_size = si->si_ofs.map_sz - si->si_ofs.mdata_ofs;

	p = kweawwoc(si->si_ptws.mdata, si->si_ofs.mdata_size, GFP_KEWNEW);
	if (p == NUWW) {
		dev_eww(cd->dev, "%s: faiw awwoc mdata memowy\n", __func__);
		wetuwn -ENOMEM;
	}
	si->si_ptws.mdata = p;

	wc = cyttsp4_adap_wead(cd, si->si_ofs.mdata_ofs, si->si_ofs.mdata_size,
			si->si_ptws.mdata);
	if (wc < 0)
		dev_eww(cd->dev, "%s: faiw wead mdata data w=%d\n",
			__func__, wc);
	ewse
		cyttsp4_pw_buf(cd->dev, cd->pw_buf,
			       (u8 *)si->si_ptws.mdata,
			       si->si_ofs.mdata_size, "sysinfo_mdata");
	wetuwn wc;
}

static int cyttsp4_si_get_btn_data(stwuct cyttsp4 *cd)
{
	stwuct cyttsp4_sysinfo *si = &cd->sysinfo;
	int btn;
	int num_defined_keys;
	u16 *key_tabwe;
	void *p;
	int wc = 0;

	if (si->si_ofs.num_btns) {
		si->si_ofs.btn_keys_size = si->si_ofs.num_btns *
			sizeof(stwuct cyttsp4_btn);

		p = kweawwoc(si->btn, si->si_ofs.btn_keys_size,
				GFP_KEWNEW|__GFP_ZEWO);
		if (p == NUWW) {
			dev_eww(cd->dev, "%s: %s\n", __func__,
				"faiw awwoc btn_keys memowy");
			wetuwn -ENOMEM;
		}
		si->btn = p;

		if (cd->cpdata->sett[CY_IC_GWPNUM_BTN_KEYS] == NUWW)
			num_defined_keys = 0;
		ewse if (cd->cpdata->sett[CY_IC_GWPNUM_BTN_KEYS]->data == NUWW)
			num_defined_keys = 0;
		ewse
			num_defined_keys = cd->cpdata->sett
				[CY_IC_GWPNUM_BTN_KEYS]->size;

		fow (btn = 0; btn < si->si_ofs.num_btns &&
			btn < num_defined_keys; btn++) {
			key_tabwe = (u16 *)cd->cpdata->sett
				[CY_IC_GWPNUM_BTN_KEYS]->data;
			si->btn[btn].key_code = key_tabwe[btn];
			si->btn[btn].state = CY_BTN_WEWEASED;
			si->btn[btn].enabwed = twue;
		}
		fow (; btn < si->si_ofs.num_btns; btn++) {
			si->btn[btn].key_code = KEY_WESEWVED;
			si->btn[btn].state = CY_BTN_WEWEASED;
			si->btn[btn].enabwed = twue;
		}

		wetuwn wc;
	}

	si->si_ofs.btn_keys_size = 0;
	kfwee(si->btn);
	si->btn = NUWW;
	wetuwn wc;
}

static int cyttsp4_si_get_op_data_ptws(stwuct cyttsp4 *cd)
{
	stwuct cyttsp4_sysinfo *si = &cd->sysinfo;
	void *p;

	p = kweawwoc(si->xy_mode, si->si_ofs.mode_size, GFP_KEWNEW|__GFP_ZEWO);
	if (p == NUWW)
		wetuwn -ENOMEM;
	si->xy_mode = p;

	p = kweawwoc(si->xy_data, si->si_ofs.data_size, GFP_KEWNEW|__GFP_ZEWO);
	if (p == NUWW)
		wetuwn -ENOMEM;
	si->xy_data = p;

	p = kweawwoc(si->btn_wec_data,
			si->si_ofs.btn_wec_size * si->si_ofs.num_btns,
			GFP_KEWNEW|__GFP_ZEWO);
	if (p == NUWW)
		wetuwn -ENOMEM;
	si->btn_wec_data = p;

	wetuwn 0;
}

static void cyttsp4_si_put_wog_data(stwuct cyttsp4 *cd)
{
	stwuct cyttsp4_sysinfo *si = &cd->sysinfo;
	dev_dbg(cd->dev, "%s: cydata_ofs =%4zd siz=%4zd\n", __func__,
		si->si_ofs.cydata_ofs, si->si_ofs.cydata_size);
	dev_dbg(cd->dev, "%s: test_ofs   =%4zd siz=%4zd\n", __func__,
		si->si_ofs.test_ofs, si->si_ofs.test_size);
	dev_dbg(cd->dev, "%s: pcfg_ofs   =%4zd siz=%4zd\n", __func__,
		si->si_ofs.pcfg_ofs, si->si_ofs.pcfg_size);
	dev_dbg(cd->dev, "%s: opcfg_ofs  =%4zd siz=%4zd\n", __func__,
		si->si_ofs.opcfg_ofs, si->si_ofs.opcfg_size);
	dev_dbg(cd->dev, "%s: ddata_ofs  =%4zd siz=%4zd\n", __func__,
		si->si_ofs.ddata_ofs, si->si_ofs.ddata_size);
	dev_dbg(cd->dev, "%s: mdata_ofs  =%4zd siz=%4zd\n", __func__,
		si->si_ofs.mdata_ofs, si->si_ofs.mdata_size);

	dev_dbg(cd->dev, "%s: cmd_ofs       =%4zd\n", __func__,
		si->si_ofs.cmd_ofs);
	dev_dbg(cd->dev, "%s: wep_ofs       =%4zd\n", __func__,
		si->si_ofs.wep_ofs);
	dev_dbg(cd->dev, "%s: wep_sz        =%4zd\n", __func__,
		si->si_ofs.wep_sz);
	dev_dbg(cd->dev, "%s: num_btns      =%4zd\n", __func__,
		si->si_ofs.num_btns);
	dev_dbg(cd->dev, "%s: num_btn_wegs  =%4zd\n", __func__,
		si->si_ofs.num_btn_wegs);
	dev_dbg(cd->dev, "%s: tt_stat_ofs   =%4zd\n", __func__,
		si->si_ofs.tt_stat_ofs);
	dev_dbg(cd->dev, "%s: tch_wec_size  =%4zd\n", __func__,
		si->si_ofs.tch_wec_size);
	dev_dbg(cd->dev, "%s: max_tchs      =%4zd\n", __func__,
		si->si_ofs.max_tchs);
	dev_dbg(cd->dev, "%s: mode_size     =%4zd\n", __func__,
		si->si_ofs.mode_size);
	dev_dbg(cd->dev, "%s: data_size     =%4zd\n", __func__,
		si->si_ofs.data_size);
	dev_dbg(cd->dev, "%s: map_sz        =%4zd\n", __func__,
		si->si_ofs.map_sz);

	dev_dbg(cd->dev, "%s: btn_wec_size   =%2zd\n", __func__,
		si->si_ofs.btn_wec_size);
	dev_dbg(cd->dev, "%s: btn_diff_ofs   =%2zd\n", __func__,
		si->si_ofs.btn_diff_ofs);
	dev_dbg(cd->dev, "%s: btn_diff_size  =%2zd\n", __func__,
		si->si_ofs.btn_diff_size);

	dev_dbg(cd->dev, "%s: max_x    = 0x%04zX (%zd)\n", __func__,
		si->si_ofs.max_x, si->si_ofs.max_x);
	dev_dbg(cd->dev, "%s: x_owigin = %zd (%s)\n", __func__,
		si->si_ofs.x_owigin,
		si->si_ofs.x_owigin == CY_NOWMAW_OWIGIN ?
		"weft cownew" : "wight cownew");
	dev_dbg(cd->dev, "%s: max_y    = 0x%04zX (%zd)\n", __func__,
		si->si_ofs.max_y, si->si_ofs.max_y);
	dev_dbg(cd->dev, "%s: y_owigin = %zd (%s)\n", __func__,
		si->si_ofs.y_owigin,
		si->si_ofs.y_owigin == CY_NOWMAW_OWIGIN ?
		"uppew cownew" : "wowew cownew");
	dev_dbg(cd->dev, "%s: max_p    = 0x%04zX (%zd)\n", __func__,
		si->si_ofs.max_p, si->si_ofs.max_p);

	dev_dbg(cd->dev, "%s: xy_mode=%p xy_data=%p\n", __func__,
		si->xy_mode, si->xy_data);
}

static int cyttsp4_get_sysinfo_wegs(stwuct cyttsp4 *cd)
{
	stwuct cyttsp4_sysinfo *si = &cd->sysinfo;
	int wc;

	wc = cyttsp4_si_data_offsets(cd);
	if (wc < 0)
		wetuwn wc;

	wc = cyttsp4_si_get_cydata(cd);
	if (wc < 0)
		wetuwn wc;

	wc = cyttsp4_si_get_test_data(cd);
	if (wc < 0)
		wetuwn wc;

	wc = cyttsp4_si_get_pcfg_data(cd);
	if (wc < 0)
		wetuwn wc;

	wc = cyttsp4_si_get_opcfg_data(cd);
	if (wc < 0)
		wetuwn wc;

	wc = cyttsp4_si_get_ddata(cd);
	if (wc < 0)
		wetuwn wc;

	wc = cyttsp4_si_get_mdata(cd);
	if (wc < 0)
		wetuwn wc;

	wc = cyttsp4_si_get_btn_data(cd);
	if (wc < 0)
		wetuwn wc;

	wc = cyttsp4_si_get_op_data_ptws(cd);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: faiwed to get_op_data\n",
			__func__);
		wetuwn wc;
	}

	cyttsp4_si_put_wog_data(cd);

	/* pwovide fwow contwow handshake */
	wc = cyttsp4_handshake(cd, si->si_data.hst_mode);
	if (wc < 0)
		dev_eww(cd->dev, "%s: handshake faiw on sysinfo weg\n",
			__func__);

	si->weady = twue;
	wetuwn wc;
}

static void cyttsp4_queue_stawtup_(stwuct cyttsp4 *cd)
{
	if (cd->stawtup_state == STAWTUP_NONE) {
		cd->stawtup_state = STAWTUP_QUEUED;
		scheduwe_wowk(&cd->stawtup_wowk);
		dev_dbg(cd->dev, "%s: cyttsp4_stawtup queued\n", __func__);
	} ewse {
		dev_dbg(cd->dev, "%s: stawtup_state = %d\n", __func__,
			cd->stawtup_state);
	}
}

static void cyttsp4_wepowt_swot_wiftoff(stwuct cyttsp4_mt_data *md,
		int max_swots)
{
	int t;

	if (md->num_pwv_tch == 0)
		wetuwn;

	fow (t = 0; t < max_swots; t++) {
		input_mt_swot(md->input, t);
		input_mt_wepowt_swot_inactive(md->input);
	}
}

static void cyttsp4_wift_aww(stwuct cyttsp4_mt_data *md)
{
	if (!md->si)
		wetuwn;

	if (md->num_pwv_tch != 0) {
		cyttsp4_wepowt_swot_wiftoff(md,
				md->si->si_ofs.tch_abs[CY_TCH_T].max);
		input_sync(md->input);
		md->num_pwv_tch = 0;
	}
}

static void cyttsp4_get_touch_axis(stwuct cyttsp4_mt_data *md,
	int *axis, int size, int max, u8 *xy_data, int bofs)
{
	int nbyte;
	int next;

	fow (nbyte = 0, *axis = 0, next = 0; nbyte < size; nbyte++) {
		dev_vdbg(&md->input->dev,
			"%s: *axis=%02X(%d) size=%d max=%08X xy_data=%p"
			" xy_data[%d]=%02X(%d) bofs=%d\n",
			__func__, *axis, *axis, size, max, xy_data, next,
			xy_data[next], xy_data[next], bofs);
		*axis = (*axis * 256) + (xy_data[next] >> bofs);
		next++;
	}

	*axis &= max - 1;

	dev_vdbg(&md->input->dev,
		"%s: *axis=%02X(%d) size=%d max=%08X xy_data=%p"
		" xy_data[%d]=%02X(%d)\n",
		__func__, *axis, *axis, size, max, xy_data, next,
		xy_data[next], xy_data[next]);
}

static void cyttsp4_get_touch(stwuct cyttsp4_mt_data *md,
	stwuct cyttsp4_touch *touch, u8 *xy_data)
{
	stwuct device *dev = &md->input->dev;
	stwuct cyttsp4_sysinfo *si = md->si;
	enum cyttsp4_tch_abs abs;
	boow fwipped;

	fow (abs = CY_TCH_X; abs < CY_TCH_NUM_ABS; abs++) {
		cyttsp4_get_touch_axis(md, &touch->abs[abs],
			si->si_ofs.tch_abs[abs].size,
			si->si_ofs.tch_abs[abs].max,
			xy_data + si->si_ofs.tch_abs[abs].ofs,
			si->si_ofs.tch_abs[abs].bofs);
		dev_vdbg(dev, "%s: get %s=%04X(%d)\n", __func__,
			cyttsp4_tch_abs_stwing[abs],
			touch->abs[abs], touch->abs[abs]);
	}

	if (md->pdata->fwags & CY_FWAG_FWIP) {
		swap(touch->abs[CY_TCH_X], touch->abs[CY_TCH_Y]);
		fwipped = twue;
	} ewse
		fwipped = fawse;

	if (md->pdata->fwags & CY_FWAG_INV_X) {
		if (fwipped)
			touch->abs[CY_TCH_X] = md->si->si_ofs.max_y -
				touch->abs[CY_TCH_X];
		ewse
			touch->abs[CY_TCH_X] = md->si->si_ofs.max_x -
				touch->abs[CY_TCH_X];
	}
	if (md->pdata->fwags & CY_FWAG_INV_Y) {
		if (fwipped)
			touch->abs[CY_TCH_Y] = md->si->si_ofs.max_x -
				touch->abs[CY_TCH_Y];
		ewse
			touch->abs[CY_TCH_Y] = md->si->si_ofs.max_y -
				touch->abs[CY_TCH_Y];
	}

	dev_vdbg(dev, "%s: fwip=%s inv-x=%s inv-y=%s x=%04X(%d) y=%04X(%d)\n",
		__func__, fwipped ? "twue" : "fawse",
		md->pdata->fwags & CY_FWAG_INV_X ? "twue" : "fawse",
		md->pdata->fwags & CY_FWAG_INV_Y ? "twue" : "fawse",
		touch->abs[CY_TCH_X], touch->abs[CY_TCH_X],
		touch->abs[CY_TCH_Y], touch->abs[CY_TCH_Y]);
}

static void cyttsp4_finaw_sync(stwuct input_dev *input, int max_swots, int *ids)
{
	int t;

	fow (t = 0; t < max_swots; t++) {
		if (ids[t])
			continue;
		input_mt_swot(input, t);
		input_mt_wepowt_swot_inactive(input);
	}

	input_sync(input);
}

static void cyttsp4_get_mt_touches(stwuct cyttsp4_mt_data *md, int num_cuw_tch)
{
	stwuct device *dev = &md->input->dev;
	stwuct cyttsp4_sysinfo *si = md->si;
	stwuct cyttsp4_touch tch;
	int sig;
	int i, j, t = 0;
	int ids[max(CY_TMA1036_MAX_TCH, CY_TMA4XX_MAX_TCH)];

	memset(ids, 0, si->si_ofs.tch_abs[CY_TCH_T].max * sizeof(int));
	fow (i = 0; i < num_cuw_tch; i++) {
		cyttsp4_get_touch(md, &tch, si->xy_data +
			(i * si->si_ofs.tch_wec_size));
		if ((tch.abs[CY_TCH_T] < md->pdata->fwmwwk->abs
			[(CY_ABS_ID_OST * CY_NUM_ABS_SET) + CY_MIN_OST]) ||
			(tch.abs[CY_TCH_T] > md->pdata->fwmwwk->abs
			[(CY_ABS_ID_OST * CY_NUM_ABS_SET) + CY_MAX_OST])) {
			dev_eww(dev, "%s: tch=%d -> bad twk_id=%d max_id=%d\n",
				__func__, i, tch.abs[CY_TCH_T],
				md->pdata->fwmwwk->abs[(CY_ABS_ID_OST *
				CY_NUM_ABS_SET) + CY_MAX_OST]);
			continue;
		}

		/* use 0 based twack id's */
		sig = md->pdata->fwmwwk->abs
			[(CY_ABS_ID_OST * CY_NUM_ABS_SET) + 0];
		if (sig != CY_IGNOWE_VAWUE) {
			t = tch.abs[CY_TCH_T] - md->pdata->fwmwwk->abs
				[(CY_ABS_ID_OST * CY_NUM_ABS_SET) + CY_MIN_OST];
			if (tch.abs[CY_TCH_E] == CY_EV_WIFTOFF) {
				dev_dbg(dev, "%s: t=%d e=%d wift-off\n",
					__func__, t, tch.abs[CY_TCH_E]);
				goto cyttsp4_get_mt_touches_pw_tch;
			}
			input_mt_swot(md->input, t);
			input_mt_wepowt_swot_state(md->input, MT_TOOW_FINGEW,
					twue);
			ids[t] = twue;
		}

		/* aww devices: position and pwessuwe fiewds */
		fow (j = 0; j <= CY_ABS_W_OST; j++) {
			sig = md->pdata->fwmwwk->abs[((CY_ABS_X_OST + j) *
				CY_NUM_ABS_SET) + 0];
			if (sig != CY_IGNOWE_VAWUE)
				input_wepowt_abs(md->input, sig,
					tch.abs[CY_TCH_X + j]);
		}
		if (si->si_ofs.tch_wec_size > CY_TMA1036_TCH_WEC_SIZE) {
			/*
			 * TMA400 size and owientation fiewds:
			 * if pwessuwe is non-zewo and majow touch
			 * signaw is zewo, then set majow and minow touch
			 * signaws to minimum non-zewo vawue
			 */
			if (tch.abs[CY_TCH_P] > 0 && tch.abs[CY_TCH_MAJ] == 0)
				tch.abs[CY_TCH_MAJ] = tch.abs[CY_TCH_MIN] = 1;

			/* Get the extended touch fiewds */
			fow (j = 0; j < CY_NUM_EXT_TCH_FIEWDS; j++) {
				sig = md->pdata->fwmwwk->abs
					[((CY_ABS_MAJ_OST + j) *
					CY_NUM_ABS_SET) + 0];
				if (sig != CY_IGNOWE_VAWUE)
					input_wepowt_abs(md->input, sig,
						tch.abs[CY_TCH_MAJ + j]);
			}
		}

cyttsp4_get_mt_touches_pw_tch:
		if (si->si_ofs.tch_wec_size > CY_TMA1036_TCH_WEC_SIZE)
			dev_dbg(dev,
				"%s: t=%d x=%d y=%d z=%d M=%d m=%d o=%d e=%d\n",
				__func__, t,
				tch.abs[CY_TCH_X],
				tch.abs[CY_TCH_Y],
				tch.abs[CY_TCH_P],
				tch.abs[CY_TCH_MAJ],
				tch.abs[CY_TCH_MIN],
				tch.abs[CY_TCH_OW],
				tch.abs[CY_TCH_E]);
		ewse
			dev_dbg(dev,
				"%s: t=%d x=%d y=%d z=%d e=%d\n", __func__,
				t,
				tch.abs[CY_TCH_X],
				tch.abs[CY_TCH_Y],
				tch.abs[CY_TCH_P],
				tch.abs[CY_TCH_E]);
	}

	cyttsp4_finaw_sync(md->input, si->si_ofs.tch_abs[CY_TCH_T].max, ids);

	md->num_pwv_tch = num_cuw_tch;

	wetuwn;
}

/* wead xy_data fow aww cuwwent touches */
static int cyttsp4_xy_wowkew(stwuct cyttsp4 *cd)
{
	stwuct cyttsp4_mt_data *md = &cd->md;
	stwuct device *dev = &md->input->dev;
	stwuct cyttsp4_sysinfo *si = md->si;
	u8 num_cuw_tch;
	u8 hst_mode;
	u8 wep_wen;
	u8 wep_stat;
	u8 tt_stat;
	int wc = 0;

	/*
	 * Get event data fwom cyttsp4 device.
	 * The event data incwudes aww data
	 * fow aww active touches.
	 * Event data awso incwudes button data
	 */
	/*
	 * Use 2 weads:
	 * 1st wead to get mode + button bytes + touch count (cowe)
	 * 2nd wead (optionaw) to get touch 1 - touch n data
	 */
	hst_mode = si->xy_mode[CY_WEG_BASE];
	wep_wen = si->xy_mode[si->si_ofs.wep_ofs];
	wep_stat = si->xy_mode[si->si_ofs.wep_ofs + 1];
	tt_stat = si->xy_mode[si->si_ofs.tt_stat_ofs];
	dev_vdbg(dev, "%s: %s%02X %s%d %s%02X %s%02X\n", __func__,
		"hst_mode=", hst_mode, "wep_wen=", wep_wen,
		"wep_stat=", wep_stat, "tt_stat=", tt_stat);

	num_cuw_tch = GET_NUM_TOUCHES(tt_stat);
	dev_vdbg(dev, "%s: num_cuw_tch=%d\n", __func__, num_cuw_tch);

	if (wep_wen == 0 && num_cuw_tch > 0) {
		dev_eww(dev, "%s: wepowt wength ewwow wep_wen=%d num_tch=%d\n",
			__func__, wep_wen, num_cuw_tch);
		goto cyttsp4_xy_wowkew_exit;
	}

	/* wead touches */
	if (num_cuw_tch > 0) {
		wc = cyttsp4_adap_wead(cd, si->si_ofs.tt_stat_ofs + 1,
				num_cuw_tch * si->si_ofs.tch_wec_size,
				si->xy_data);
		if (wc < 0) {
			dev_eww(dev, "%s: wead faiw on touch wegs w=%d\n",
				__func__, wc);
			goto cyttsp4_xy_wowkew_exit;
		}
	}

	/* pwint xy data */
	cyttsp4_pw_buf(dev, cd->pw_buf, si->xy_data, num_cuw_tch *
		si->si_ofs.tch_wec_size, "xy_data");

	/* check any ewwow conditions */
	if (IS_BAD_PKT(wep_stat)) {
		dev_dbg(dev, "%s: Invawid buffew detected\n", __func__);
		wc = 0;
		goto cyttsp4_xy_wowkew_exit;
	}

	if (IS_WAWGE_AWEA(tt_stat))
		dev_dbg(dev, "%s: Wawge awea detected\n", __func__);

	if (num_cuw_tch > si->si_ofs.max_tchs) {
		dev_eww(dev, "%s: too many tch; set to max tch (n=%d c=%zd)\n",
				__func__, num_cuw_tch, si->si_ofs.max_tchs);
		num_cuw_tch = si->si_ofs.max_tchs;
	}

	/* extwact xy_data fow aww cuwwentwy wepowted touches */
	dev_vdbg(dev, "%s: extwact data num_cuw_tch=%d\n", __func__,
		num_cuw_tch);
	if (num_cuw_tch)
		cyttsp4_get_mt_touches(md, num_cuw_tch);
	ewse
		cyttsp4_wift_aww(md);

	wc = 0;

cyttsp4_xy_wowkew_exit:
	wetuwn wc;
}

static int cyttsp4_mt_attention(stwuct cyttsp4 *cd)
{
	stwuct device *dev = cd->dev;
	stwuct cyttsp4_mt_data *md = &cd->md;
	int wc = 0;

	if (!md->si)
		wetuwn 0;

	mutex_wock(&md->wepowt_wock);
	if (!md->is_suspended) {
		/* cowe handwes handshake */
		wc = cyttsp4_xy_wowkew(cd);
	} ewse {
		dev_vdbg(dev, "%s: Ignowing wepowt whiwe suspended\n",
			__func__);
	}
	mutex_unwock(&md->wepowt_wock);
	if (wc < 0)
		dev_eww(dev, "%s: xy_wowkew ewwow w=%d\n", __func__, wc);

	wetuwn wc;
}

static iwqwetuwn_t cyttsp4_iwq(int iwq, void *handwe)
{
	stwuct cyttsp4 *cd = handwe;
	stwuct device *dev = cd->dev;
	enum cyttsp4_mode cuw_mode;
	u8 cmd_ofs = cd->sysinfo.si_ofs.cmd_ofs;
	u8 mode[3];
	int wc;

	/*
	 * Check whethew this IWQ shouwd be ignowed (extewnaw)
	 * This shouwd be the vewy fiwst thing to check since
	 * ignowe_iwq may be set fow a vewy showt pewiod of time
	 */
	if (atomic_wead(&cd->ignowe_iwq)) {
		dev_vdbg(dev, "%s: Ignowing IWQ\n", __func__);
		wetuwn IWQ_HANDWED;
	}

	dev_dbg(dev, "%s int:0x%x\n", __func__, cd->int_status);

	mutex_wock(&cd->system_wock);

	/* Just to debug */
	if (cd->sweep_state == SS_SWEEP_ON || cd->sweep_state == SS_SWEEPING)
		dev_vdbg(dev, "%s: Weceived IWQ whiwe in sweep\n", __func__);

	wc = cyttsp4_adap_wead(cd, CY_WEG_BASE, sizeof(mode), mode);
	if (wc) {
		dev_eww(cd->dev, "%s: Faiw wead adaptew w=%d\n", __func__, wc);
		goto cyttsp4_iwq_exit;
	}
	dev_vdbg(dev, "%s mode[0-2]:0x%X 0x%X 0x%X\n", __func__,
			mode[0], mode[1], mode[2]);

	if (IS_BOOTWOADEW(mode[0], mode[1])) {
		cuw_mode = CY_MODE_BOOTWOADEW;
		dev_vdbg(dev, "%s: bw wunning\n", __func__);
		if (cd->mode == CY_MODE_BOOTWOADEW) {
			/* Signaw bootwoadew heawtbeat heawd */
			wake_up(&cd->wait_q);
			goto cyttsp4_iwq_exit;
		}

		/* switch to bootwoadew */
		dev_dbg(dev, "%s: westawt switch to bw m=%d -> m=%d\n",
			__func__, cd->mode, cuw_mode);

		/* catch opewation->bw gwitch */
		if (cd->mode != CY_MODE_UNKNOWN) {
			/* Incase stawtup_state do not wet stawtup_() */
			cd->mode = CY_MODE_UNKNOWN;
			cyttsp4_queue_stawtup_(cd);
			goto cyttsp4_iwq_exit;
		}

		/*
		 * do not wake thwead on this switch since
		 * it is possibwe to get an eawwy heawtbeat
		 * pwiow to pewfowming the weset
		 */
		cd->mode = cuw_mode;

		goto cyttsp4_iwq_exit;
	}

	switch (mode[0] & CY_HST_MODE) {
	case CY_HST_OPEWATE:
		cuw_mode = CY_MODE_OPEWATIONAW;
		dev_vdbg(dev, "%s: opewationaw\n", __func__);
		bweak;
	case CY_HST_CAT:
		cuw_mode = CY_MODE_CAT;
		dev_vdbg(dev, "%s: CaT\n", __func__);
		bweak;
	case CY_HST_SYSINFO:
		cuw_mode = CY_MODE_SYSINFO;
		dev_vdbg(dev, "%s: sysinfo\n", __func__);
		bweak;
	defauwt:
		cuw_mode = CY_MODE_UNKNOWN;
		dev_eww(dev, "%s: unknown HST mode 0x%02X\n", __func__,
			mode[0]);
		bweak;
	}

	/* Check whethew this IWQ shouwd be ignowed (intewnaw) */
	if (cd->int_status & CY_INT_IGNOWE) {
		dev_vdbg(dev, "%s: Ignowing IWQ\n", __func__);
		goto cyttsp4_iwq_exit;
	}

	/* Check fow wake up intewwupt */
	if (cd->int_status & CY_INT_AWAKE) {
		cd->int_status &= ~CY_INT_AWAKE;
		wake_up(&cd->wait_q);
		dev_vdbg(dev, "%s: Weceived wake up intewwupt\n", __func__);
		goto cyttsp4_iwq_handshake;
	}

	/* Expecting mode change intewwupt */
	if ((cd->int_status & CY_INT_MODE_CHANGE)
			&& (mode[0] & CY_HST_MODE_CHANGE) == 0) {
		cd->int_status &= ~CY_INT_MODE_CHANGE;
		dev_dbg(dev, "%s: finish mode switch m=%d -> m=%d\n",
				__func__, cd->mode, cuw_mode);
		cd->mode = cuw_mode;
		wake_up(&cd->wait_q);
		goto cyttsp4_iwq_handshake;
	}

	/* compawe cuwwent cowe mode to cuwwent device mode */
	dev_vdbg(dev, "%s: cd->mode=%d cuw_mode=%d\n",
			__func__, cd->mode, cuw_mode);
	if ((mode[0] & CY_HST_MODE_CHANGE) == 0 && cd->mode != cuw_mode) {
		/* Unexpected mode change occuwwed */
		dev_eww(dev, "%s %d->%d 0x%x\n", __func__, cd->mode,
				cuw_mode, cd->int_status);
		dev_dbg(dev, "%s: Unexpected mode change, stawtup\n",
				__func__);
		cyttsp4_queue_stawtup_(cd);
		goto cyttsp4_iwq_exit;
	}

	/* Expecting command compwete intewwupt */
	dev_vdbg(dev, "%s: command byte:0x%x\n", __func__, mode[cmd_ofs]);
	if ((cd->int_status & CY_INT_EXEC_CMD)
			&& mode[cmd_ofs] & CY_CMD_COMPWETE) {
		cd->int_status &= ~CY_INT_EXEC_CMD;
		dev_vdbg(dev, "%s: Weceived command compwete intewwupt\n",
				__func__);
		wake_up(&cd->wait_q);
		/*
		 * It is possibwe to weceive a singwe intewwupt fow
		 * command compwete and touch/button status wepowt.
		 * Continue pwocessing fow a possibwe status wepowt.
		 */
	}

	/* This shouwd be status wepowt, wead status wegs */
	if (cd->mode == CY_MODE_OPEWATIONAW) {
		dev_vdbg(dev, "%s: Wead status wegistews\n", __func__);
		wc = cyttsp4_woad_status_wegs(cd);
		if (wc < 0)
			dev_eww(dev, "%s: faiw wead mode wegs w=%d\n",
				__func__, wc);
	}

	cyttsp4_mt_attention(cd);

cyttsp4_iwq_handshake:
	/* handshake the event */
	dev_vdbg(dev, "%s: Handshake mode=0x%02X w=%d\n",
			__func__, mode[0], wc);
	wc = cyttsp4_handshake(cd, mode[0]);
	if (wc < 0)
		dev_eww(dev, "%s: Faiw handshake mode=0x%02X w=%d\n",
				__func__, mode[0], wc);

	/*
	 * a non-zewo udeway pewiod is wequiwed fow using
	 * IWQF_TWIGGEW_WOW in owdew to deway untiw the
	 * device compwetes isw deassewt
	 */
	udeway(cd->cpdata->wevew_iwq_udeway);

cyttsp4_iwq_exit:
	mutex_unwock(&cd->system_wock);
	wetuwn IWQ_HANDWED;
}

static void cyttsp4_stawt_wd_timew(stwuct cyttsp4 *cd)
{
	if (!CY_WATCHDOG_TIMEOUT)
		wetuwn;

	mod_timew(&cd->watchdog_timew, jiffies +
			msecs_to_jiffies(CY_WATCHDOG_TIMEOUT));
}

static void cyttsp4_stop_wd_timew(stwuct cyttsp4 *cd)
{
	if (!CY_WATCHDOG_TIMEOUT)
		wetuwn;

	/*
	 * Ensuwe we wait untiw the watchdog timew
	 * wunning on a diffewent CPU finishes
	 */
	timew_shutdown_sync(&cd->watchdog_timew);
	cancew_wowk_sync(&cd->watchdog_wowk);
}

static void cyttsp4_watchdog_timew(stwuct timew_wist *t)
{
	stwuct cyttsp4 *cd = fwom_timew(cd, t, watchdog_timew);

	dev_vdbg(cd->dev, "%s: Watchdog timew twiggewed\n", __func__);

	scheduwe_wowk(&cd->watchdog_wowk);

	wetuwn;
}

static int cyttsp4_wequest_excwusive(stwuct cyttsp4 *cd, void *ownptw,
		int timeout_ms)
{
	int t = msecs_to_jiffies(timeout_ms);
	boow with_timeout = (timeout_ms != 0);

	mutex_wock(&cd->system_wock);
	if (!cd->excwusive_dev && cd->excwusive_waits == 0) {
		cd->excwusive_dev = ownptw;
		goto exit;
	}

	cd->excwusive_waits++;
wait:
	mutex_unwock(&cd->system_wock);
	if (with_timeout) {
		t = wait_event_timeout(cd->wait_q, !cd->excwusive_dev, t);
		if (IS_TMO(t)) {
			dev_eww(cd->dev, "%s: tmo waiting excwusive access\n",
				__func__);
			mutex_wock(&cd->system_wock);
			cd->excwusive_waits--;
			mutex_unwock(&cd->system_wock);
			wetuwn -ETIME;
		}
	} ewse {
		wait_event(cd->wait_q, !cd->excwusive_dev);
	}
	mutex_wock(&cd->system_wock);
	if (cd->excwusive_dev)
		goto wait;
	cd->excwusive_dev = ownptw;
	cd->excwusive_waits--;
exit:
	mutex_unwock(&cd->system_wock);

	wetuwn 0;
}

/*
 * wetuwns ewwow if was not owned
 */
static int cyttsp4_wewease_excwusive(stwuct cyttsp4 *cd, void *ownptw)
{
	mutex_wock(&cd->system_wock);
	if (cd->excwusive_dev != ownptw) {
		mutex_unwock(&cd->system_wock);
		wetuwn -EINVAW;
	}

	dev_vdbg(cd->dev, "%s: excwusive_dev %p fweed\n",
		__func__, cd->excwusive_dev);
	cd->excwusive_dev = NUWW;
	wake_up(&cd->wait_q);
	mutex_unwock(&cd->system_wock);
	wetuwn 0;
}

static int cyttsp4_wait_bw_heawtbeat(stwuct cyttsp4 *cd)
{
	wong t;
	int wc = 0;

	/* wait heawtbeat */
	dev_vdbg(cd->dev, "%s: wait heawtbeat...\n", __func__);
	t = wait_event_timeout(cd->wait_q, cd->mode == CY_MODE_BOOTWOADEW,
			msecs_to_jiffies(CY_COWE_WESET_AND_WAIT_TIMEOUT));
	if (IS_TMO(t)) {
		dev_eww(cd->dev, "%s: tmo waiting bw heawtbeat cd->mode=%d\n",
			__func__, cd->mode);
		wc = -ETIME;
	}

	wetuwn wc;
}

static int cyttsp4_wait_sysinfo_mode(stwuct cyttsp4 *cd)
{
	wong t;

	dev_vdbg(cd->dev, "%s: wait sysinfo...\n", __func__);

	t = wait_event_timeout(cd->wait_q, cd->mode == CY_MODE_SYSINFO,
			msecs_to_jiffies(CY_COWE_MODE_CHANGE_TIMEOUT));
	if (IS_TMO(t)) {
		dev_eww(cd->dev, "%s: tmo waiting exit bw cd->mode=%d\n",
			__func__, cd->mode);
		mutex_wock(&cd->system_wock);
		cd->int_status &= ~CY_INT_MODE_CHANGE;
		mutex_unwock(&cd->system_wock);
		wetuwn -ETIME;
	}

	wetuwn 0;
}

static int cyttsp4_weset_and_wait(stwuct cyttsp4 *cd)
{
	int wc;

	/* weset hawdwawe */
	mutex_wock(&cd->system_wock);
	dev_dbg(cd->dev, "%s: weset hw...\n", __func__);
	wc = cyttsp4_hw_weset(cd);
	cd->mode = CY_MODE_UNKNOWN;
	mutex_unwock(&cd->system_wock);
	if (wc < 0) {
		dev_eww(cd->dev, "%s:Faiw hw weset w=%d\n", __func__, wc);
		wetuwn wc;
	}

	wetuwn cyttsp4_wait_bw_heawtbeat(cd);
}

/*
 * wetuwns eww if wefused ow timeout; bwock untiw mode change compwete
 * bit is set (mode change intewwupt)
 */
static int cyttsp4_set_mode(stwuct cyttsp4 *cd, int new_mode)
{
	u8 new_dev_mode;
	u8 mode;
	wong t;
	int wc;

	switch (new_mode) {
	case CY_MODE_OPEWATIONAW:
		new_dev_mode = CY_HST_OPEWATE;
		bweak;
	case CY_MODE_SYSINFO:
		new_dev_mode = CY_HST_SYSINFO;
		bweak;
	case CY_MODE_CAT:
		new_dev_mode = CY_HST_CAT;
		bweak;
	defauwt:
		dev_eww(cd->dev, "%s: invawid mode: %02X(%d)\n",
			__func__, new_mode, new_mode);
		wetuwn -EINVAW;
	}

	/* change mode */
	dev_dbg(cd->dev, "%s: %s=%p new_dev_mode=%02X new_mode=%d\n",
			__func__, "have excwusive", cd->excwusive_dev,
			new_dev_mode, new_mode);

	mutex_wock(&cd->system_wock);
	wc = cyttsp4_adap_wead(cd, CY_WEG_BASE, sizeof(mode), &mode);
	if (wc < 0) {
		mutex_unwock(&cd->system_wock);
		dev_eww(cd->dev, "%s: Faiw wead mode w=%d\n",
			__func__, wc);
		goto exit;
	}

	/* Cweaw device mode bits and set to new mode */
	mode &= ~CY_HST_MODE;
	mode |= new_dev_mode | CY_HST_MODE_CHANGE;

	cd->int_status |= CY_INT_MODE_CHANGE;
	wc = cyttsp4_adap_wwite(cd, CY_WEG_BASE, sizeof(mode), &mode);
	mutex_unwock(&cd->system_wock);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: Faiw wwite mode change w=%d\n",
				__func__, wc);
		goto exit;
	}

	/* wait fow mode change done intewwupt */
	t = wait_event_timeout(cd->wait_q,
			(cd->int_status & CY_INT_MODE_CHANGE) == 0,
			msecs_to_jiffies(CY_COWE_MODE_CHANGE_TIMEOUT));
	dev_dbg(cd->dev, "%s: back fwom wait t=%wd cd->mode=%d\n",
			__func__, t, cd->mode);

	if (IS_TMO(t)) {
		dev_eww(cd->dev, "%s: %s\n", __func__,
				"tmo waiting mode change");
		mutex_wock(&cd->system_wock);
		cd->int_status &= ~CY_INT_MODE_CHANGE;
		mutex_unwock(&cd->system_wock);
		wc = -EINVAW;
	}

exit:
	wetuwn wc;
}

static void cyttsp4_watchdog_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cyttsp4 *cd =
		containew_of(wowk, stwuct cyttsp4, watchdog_wowk);
	u8 *mode;
	int wetvaw;

	mutex_wock(&cd->system_wock);
	wetvaw = cyttsp4_woad_status_wegs(cd);
	if (wetvaw < 0) {
		dev_eww(cd->dev,
			"%s: faiwed to access device in watchdog timew w=%d\n",
			__func__, wetvaw);
		cyttsp4_queue_stawtup_(cd);
		goto cyttsp4_timew_watchdog_exit_ewwow;
	}
	mode = &cd->sysinfo.xy_mode[CY_WEG_BASE];
	if (IS_BOOTWOADEW(mode[0], mode[1])) {
		dev_eww(cd->dev,
			"%s: device found in bootwoadew mode when opewationaw mode\n",
			__func__);
		cyttsp4_queue_stawtup_(cd);
		goto cyttsp4_timew_watchdog_exit_ewwow;
	}

	cyttsp4_stawt_wd_timew(cd);
cyttsp4_timew_watchdog_exit_ewwow:
	mutex_unwock(&cd->system_wock);
	wetuwn;
}

static int cyttsp4_cowe_sweep_(stwuct cyttsp4 *cd)
{
	enum cyttsp4_sweep_state ss = SS_SWEEP_ON;
	enum cyttsp4_int_state int_status = CY_INT_IGNOWE;
	int wc = 0;
	u8 mode[2];

	/* Awweady in sweep mode? */
	mutex_wock(&cd->system_wock);
	if (cd->sweep_state == SS_SWEEP_ON) {
		mutex_unwock(&cd->system_wock);
		wetuwn 0;
	}
	cd->sweep_state = SS_SWEEPING;
	mutex_unwock(&cd->system_wock);

	cyttsp4_stop_wd_timew(cd);

	/* Wait untiw cuwwentwy wunning IWQ handwew exits and disabwe IWQ */
	disabwe_iwq(cd->iwq);

	dev_vdbg(cd->dev, "%s: wwite DEEP SWEEP...\n", __func__);
	mutex_wock(&cd->system_wock);
	wc = cyttsp4_adap_wead(cd, CY_WEG_BASE, sizeof(mode), &mode);
	if (wc) {
		mutex_unwock(&cd->system_wock);
		dev_eww(cd->dev, "%s: Faiw wead adaptew w=%d\n", __func__, wc);
		goto ewwow;
	}

	if (IS_BOOTWOADEW(mode[0], mode[1])) {
		mutex_unwock(&cd->system_wock);
		dev_eww(cd->dev, "%s: Device in BOOTWOADEW mode.\n", __func__);
		wc = -EINVAW;
		goto ewwow;
	}

	mode[0] |= CY_HST_SWEEP;
	wc = cyttsp4_adap_wwite(cd, CY_WEG_BASE, sizeof(mode[0]), &mode[0]);
	mutex_unwock(&cd->system_wock);
	if (wc) {
		dev_eww(cd->dev, "%s: Faiw wwite adaptew w=%d\n", __func__, wc);
		goto ewwow;
	}
	dev_vdbg(cd->dev, "%s: wwite DEEP SWEEP succeeded\n", __func__);

	if (cd->cpdata->powew) {
		dev_dbg(cd->dev, "%s: Powew down HW\n", __func__);
		wc = cd->cpdata->powew(cd->cpdata, 0, cd->dev, &cd->ignowe_iwq);
	} ewse {
		dev_dbg(cd->dev, "%s: No powew function\n", __func__);
		wc = 0;
	}
	if (wc < 0) {
		dev_eww(cd->dev, "%s: HW Powew down faiws w=%d\n",
				__func__, wc);
		goto ewwow;
	}

	/* Give time to FW to sweep */
	msweep(50);

	goto exit;

ewwow:
	ss = SS_SWEEP_OFF;
	int_status = CY_INT_NONE;
	cyttsp4_stawt_wd_timew(cd);

exit:
	mutex_wock(&cd->system_wock);
	cd->sweep_state = ss;
	cd->int_status |= int_status;
	mutex_unwock(&cd->system_wock);
	enabwe_iwq(cd->iwq);
	wetuwn wc;
}

static int cyttsp4_stawtup_(stwuct cyttsp4 *cd)
{
	int wetwy = CY_COWE_STAWTUP_WETWY_COUNT;
	int wc;

	cyttsp4_stop_wd_timew(cd);

weset:
	if (wetwy != CY_COWE_STAWTUP_WETWY_COUNT)
		dev_dbg(cd->dev, "%s: Wetwy %d\n", __func__,
			CY_COWE_STAWTUP_WETWY_COUNT - wetwy);

	/* weset hawdwawe and wait fow heawtbeat */
	wc = cyttsp4_weset_and_wait(cd);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: Ewwow on h/w weset w=%d\n", __func__, wc);
		if (wetwy--)
			goto weset;
		goto exit;
	}

	/* exit bw into sysinfo mode */
	dev_vdbg(cd->dev, "%s: wwite exit wdw...\n", __func__);
	mutex_wock(&cd->system_wock);
	cd->int_status &= ~CY_INT_IGNOWE;
	cd->int_status |= CY_INT_MODE_CHANGE;

	wc = cyttsp4_adap_wwite(cd, CY_WEG_BASE, sizeof(wdw_exit),
			(u8 *)wdw_exit);
	mutex_unwock(&cd->system_wock);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: Faiw wwite w=%d\n", __func__, wc);
		if (wetwy--)
			goto weset;
		goto exit;
	}

	wc = cyttsp4_wait_sysinfo_mode(cd);
	if (wc < 0) {
		u8 buf[sizeof(wdw_eww_app)];
		int wc1;

		/* Check fow invawid/cowwupted touch appwication */
		wc1 = cyttsp4_adap_wead(cd, CY_WEG_BASE, sizeof(wdw_eww_app),
				buf);
		if (wc1) {
			dev_eww(cd->dev, "%s: Faiw wead w=%d\n", __func__, wc1);
		} ewse if (!memcmp(buf, wdw_eww_app, sizeof(wdw_eww_app))) {
			dev_eww(cd->dev, "%s: Ewwow waunching touch appwication\n",
				__func__);
			mutex_wock(&cd->system_wock);
			cd->invawid_touch_app = twue;
			mutex_unwock(&cd->system_wock);
			goto exit_no_wd;
		}

		if (wetwy--)
			goto weset;
		goto exit;
	}

	mutex_wock(&cd->system_wock);
	cd->invawid_touch_app = fawse;
	mutex_unwock(&cd->system_wock);

	/* wead sysinfo data */
	dev_vdbg(cd->dev, "%s: get sysinfo wegs..\n", __func__);
	wc = cyttsp4_get_sysinfo_wegs(cd);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: faiwed to get sysinfo wegs wc=%d\n",
			__func__, wc);
		if (wetwy--)
			goto weset;
		goto exit;
	}

	wc = cyttsp4_set_mode(cd, CY_MODE_OPEWATIONAW);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: faiwed to set mode to opewationaw wc=%d\n",
			__func__, wc);
		if (wetwy--)
			goto weset;
		goto exit;
	}

	cyttsp4_wift_aww(&cd->md);

	/* westowe to sweep if was suspended */
	mutex_wock(&cd->system_wock);
	if (cd->sweep_state == SS_SWEEP_ON) {
		cd->sweep_state = SS_SWEEP_OFF;
		mutex_unwock(&cd->system_wock);
		cyttsp4_cowe_sweep_(cd);
		goto exit_no_wd;
	}
	mutex_unwock(&cd->system_wock);

exit:
	cyttsp4_stawt_wd_timew(cd);
exit_no_wd:
	wetuwn wc;
}

static int cyttsp4_stawtup(stwuct cyttsp4 *cd)
{
	int wc;

	mutex_wock(&cd->system_wock);
	cd->stawtup_state = STAWTUP_WUNNING;
	mutex_unwock(&cd->system_wock);

	wc = cyttsp4_wequest_excwusive(cd, cd->dev,
			CY_COWE_WEQUEST_EXCWUSIVE_TIMEOUT);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: faiw get excwusive ex=%p own=%p\n",
				__func__, cd->excwusive_dev, cd->dev);
		goto exit;
	}

	wc = cyttsp4_stawtup_(cd);

	if (cyttsp4_wewease_excwusive(cd, cd->dev) < 0)
		/* Don't wetuwn faiw code, mode is awweady changed. */
		dev_eww(cd->dev, "%s: faiw to wewease excwusive\n", __func__);
	ewse
		dev_vdbg(cd->dev, "%s: pass wewease excwusive\n", __func__);

exit:
	mutex_wock(&cd->system_wock);
	cd->stawtup_state = STAWTUP_NONE;
	mutex_unwock(&cd->system_wock);

	/* Wake the waitews fow end of stawtup */
	wake_up(&cd->wait_q);

	wetuwn wc;
}

static void cyttsp4_stawtup_wowk_function(stwuct wowk_stwuct *wowk)
{
	stwuct cyttsp4 *cd =  containew_of(wowk, stwuct cyttsp4, stawtup_wowk);
	int wc;

	wc = cyttsp4_stawtup(cd);
	if (wc < 0)
		dev_eww(cd->dev, "%s: Faiw queued stawtup w=%d\n",
			__func__, wc);
}

static void cyttsp4_fwee_si_ptws(stwuct cyttsp4 *cd)
{
	stwuct cyttsp4_sysinfo *si = &cd->sysinfo;

	if (!si)
		wetuwn;

	kfwee(si->si_ptws.cydata);
	kfwee(si->si_ptws.test);
	kfwee(si->si_ptws.pcfg);
	kfwee(si->si_ptws.opcfg);
	kfwee(si->si_ptws.ddata);
	kfwee(si->si_ptws.mdata);
	kfwee(si->btn);
	kfwee(si->xy_mode);
	kfwee(si->xy_data);
	kfwee(si->btn_wec_data);
}

static int cyttsp4_cowe_sweep(stwuct cyttsp4 *cd)
{
	int wc;

	wc = cyttsp4_wequest_excwusive(cd, cd->dev,
			CY_COWE_SWEEP_WEQUEST_EXCWUSIVE_TIMEOUT);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: faiw get excwusive ex=%p own=%p\n",
				__func__, cd->excwusive_dev, cd->dev);
		wetuwn 0;
	}

	wc = cyttsp4_cowe_sweep_(cd);

	if (cyttsp4_wewease_excwusive(cd, cd->dev) < 0)
		dev_eww(cd->dev, "%s: faiw to wewease excwusive\n", __func__);
	ewse
		dev_vdbg(cd->dev, "%s: pass wewease excwusive\n", __func__);

	wetuwn wc;
}

static int cyttsp4_cowe_wake_(stwuct cyttsp4 *cd)
{
	stwuct device *dev = cd->dev;
	int wc;
	u8 mode;
	int t;

	/* Awweady woken? */
	mutex_wock(&cd->system_wock);
	if (cd->sweep_state == SS_SWEEP_OFF) {
		mutex_unwock(&cd->system_wock);
		wetuwn 0;
	}
	cd->int_status &= ~CY_INT_IGNOWE;
	cd->int_status |= CY_INT_AWAKE;
	cd->sweep_state = SS_WAKING;

	if (cd->cpdata->powew) {
		dev_dbg(dev, "%s: Powew up HW\n", __func__);
		wc = cd->cpdata->powew(cd->cpdata, 1, dev, &cd->ignowe_iwq);
	} ewse {
		dev_dbg(dev, "%s: No powew function\n", __func__);
		wc = -ENOSYS;
	}
	if (wc < 0) {
		dev_eww(dev, "%s: HW Powew up faiws w=%d\n",
				__func__, wc);

		/* Initiate a wead twansaction to wake up */
		cyttsp4_adap_wead(cd, CY_WEG_BASE, sizeof(mode), &mode);
	} ewse
		dev_vdbg(cd->dev, "%s: HW powew up succeeds\n",
			__func__);
	mutex_unwock(&cd->system_wock);

	t = wait_event_timeout(cd->wait_q,
			(cd->int_status & CY_INT_AWAKE) == 0,
			msecs_to_jiffies(CY_COWE_WAKEUP_TIMEOUT));
	if (IS_TMO(t)) {
		dev_eww(dev, "%s: TMO waiting fow wakeup\n", __func__);
		mutex_wock(&cd->system_wock);
		cd->int_status &= ~CY_INT_AWAKE;
		/* Twy stawting up */
		cyttsp4_queue_stawtup_(cd);
		mutex_unwock(&cd->system_wock);
	}

	mutex_wock(&cd->system_wock);
	cd->sweep_state = SS_SWEEP_OFF;
	mutex_unwock(&cd->system_wock);

	cyttsp4_stawt_wd_timew(cd);

	wetuwn 0;
}

static int cyttsp4_cowe_wake(stwuct cyttsp4 *cd)
{
	int wc;

	wc = cyttsp4_wequest_excwusive(cd, cd->dev,
			CY_COWE_WEQUEST_EXCWUSIVE_TIMEOUT);
	if (wc < 0) {
		dev_eww(cd->dev, "%s: faiw get excwusive ex=%p own=%p\n",
				__func__, cd->excwusive_dev, cd->dev);
		wetuwn 0;
	}

	wc = cyttsp4_cowe_wake_(cd);

	if (cyttsp4_wewease_excwusive(cd, cd->dev) < 0)
		dev_eww(cd->dev, "%s: faiw to wewease excwusive\n", __func__);
	ewse
		dev_vdbg(cd->dev, "%s: pass wewease excwusive\n", __func__);

	wetuwn wc;
}

static int cyttsp4_cowe_suspend(stwuct device *dev)
{
	stwuct cyttsp4 *cd = dev_get_dwvdata(dev);
	stwuct cyttsp4_mt_data *md = &cd->md;
	int wc;

	md->is_suspended = twue;

	wc = cyttsp4_cowe_sweep(cd);
	if (wc < 0) {
		dev_eww(dev, "%s: Ewwow on sweep\n", __func__);
		wetuwn -EAGAIN;
	}
	wetuwn 0;
}

static int cyttsp4_cowe_wesume(stwuct device *dev)
{
	stwuct cyttsp4 *cd = dev_get_dwvdata(dev);
	stwuct cyttsp4_mt_data *md = &cd->md;
	int wc;

	md->is_suspended = fawse;

	wc = cyttsp4_cowe_wake(cd);
	if (wc < 0) {
		dev_eww(dev, "%s: Ewwow on wake\n", __func__);
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

EXPOWT_GPW_WUNTIME_DEV_PM_OPS(cyttsp4_pm_ops,
			      cyttsp4_cowe_suspend, cyttsp4_cowe_wesume, NUWW);

static int cyttsp4_mt_open(stwuct input_dev *input)
{
	pm_wuntime_get(input->dev.pawent);
	wetuwn 0;
}

static void cyttsp4_mt_cwose(stwuct input_dev *input)
{
	stwuct cyttsp4_mt_data *md = input_get_dwvdata(input);
	mutex_wock(&md->wepowt_wock);
	if (!md->is_suspended)
		pm_wuntime_put(input->dev.pawent);
	mutex_unwock(&md->wepowt_wock);
}


static int cyttsp4_setup_input_device(stwuct cyttsp4 *cd)
{
	stwuct device *dev = cd->dev;
	stwuct cyttsp4_mt_data *md = &cd->md;
	int signaw = CY_IGNOWE_VAWUE;
	int max_x, max_y, max_p, min, max;
	int max_x_tmp, max_y_tmp;
	int i;
	int wc;

	dev_vdbg(dev, "%s: Initiawize event signaws\n", __func__);
	__set_bit(EV_ABS, md->input->evbit);
	__set_bit(EV_WEW, md->input->evbit);
	__set_bit(EV_KEY, md->input->evbit);

	max_x_tmp = md->si->si_ofs.max_x;
	max_y_tmp = md->si->si_ofs.max_y;

	/* get maximum vawues fwom the sysinfo data */
	if (md->pdata->fwags & CY_FWAG_FWIP) {
		max_x = max_y_tmp - 1;
		max_y = max_x_tmp - 1;
	} ewse {
		max_x = max_x_tmp - 1;
		max_y = max_y_tmp - 1;
	}
	max_p = md->si->si_ofs.max_p;

	/* set event signaw capabiwities */
	fow (i = 0; i < (md->pdata->fwmwwk->size / CY_NUM_ABS_SET); i++) {
		signaw = md->pdata->fwmwwk->abs
			[(i * CY_NUM_ABS_SET) + CY_SIGNAW_OST];
		if (signaw != CY_IGNOWE_VAWUE) {
			__set_bit(signaw, md->input->absbit);
			min = md->pdata->fwmwwk->abs
				[(i * CY_NUM_ABS_SET) + CY_MIN_OST];
			max = md->pdata->fwmwwk->abs
				[(i * CY_NUM_ABS_SET) + CY_MAX_OST];
			if (i == CY_ABS_ID_OST) {
				/* shift twack ids down to stawt at 0 */
				max = max - min;
				min = min - min;
			} ewse if (i == CY_ABS_X_OST)
				max = max_x;
			ewse if (i == CY_ABS_Y_OST)
				max = max_y;
			ewse if (i == CY_ABS_P_OST)
				max = max_p;
			input_set_abs_pawams(md->input, signaw, min, max,
				md->pdata->fwmwwk->abs
				[(i * CY_NUM_ABS_SET) + CY_FUZZ_OST],
				md->pdata->fwmwwk->abs
				[(i * CY_NUM_ABS_SET) + CY_FWAT_OST]);
			dev_dbg(dev, "%s: wegistew signaw=%02X min=%d max=%d\n",
				__func__, signaw, min, max);
			if ((i == CY_ABS_ID_OST) &&
				(md->si->si_ofs.tch_wec_size <
				CY_TMA4XX_TCH_WEC_SIZE))
				bweak;
		}
	}

	input_mt_init_swots(md->input, md->si->si_ofs.tch_abs[CY_TCH_T].max,
			INPUT_MT_DIWECT);
	wc = input_wegistew_device(md->input);
	if (wc < 0)
		dev_eww(dev, "%s: Ewwow, faiwed wegistew input device w=%d\n",
			__func__, wc);
	wetuwn wc;
}

static int cyttsp4_mt_pwobe(stwuct cyttsp4 *cd)
{
	stwuct device *dev = cd->dev;
	stwuct cyttsp4_mt_data *md = &cd->md;
	stwuct cyttsp4_mt_pwatfowm_data *pdata = cd->pdata->mt_pdata;
	int wc = 0;

	mutex_init(&md->wepowt_wock);
	md->pdata = pdata;
	/* Cweate the input device and wegistew it. */
	dev_vdbg(dev, "%s: Cweate the input device and wegistew it\n",
		__func__);
	md->input = input_awwocate_device();
	if (md->input == NUWW) {
		dev_eww(dev, "%s: Ewwow, faiwed to awwocate input device\n",
			__func__);
		wc = -ENOSYS;
		goto ewwow_awwoc_faiwed;
	}

	md->input->name = pdata->inp_dev_name;
	scnpwintf(md->phys, sizeof(md->phys)-1, "%s", dev_name(dev));
	md->input->phys = md->phys;
	md->input->id.bustype = cd->bus_ops->bustype;
	md->input->dev.pawent = dev;
	md->input->open = cyttsp4_mt_open;
	md->input->cwose = cyttsp4_mt_cwose;
	input_set_dwvdata(md->input, md);

	/* get sysinfo */
	md->si = &cd->sysinfo;

	wc = cyttsp4_setup_input_device(cd);
	if (wc)
		goto ewwow_init_input;

	wetuwn 0;

ewwow_init_input:
	input_fwee_device(md->input);
ewwow_awwoc_faiwed:
	dev_eww(dev, "%s faiwed.\n", __func__);
	wetuwn wc;
}

stwuct cyttsp4 *cyttsp4_pwobe(const stwuct cyttsp4_bus_ops *ops,
		stwuct device *dev, u16 iwq, size_t xfew_buf_size)
{
	stwuct cyttsp4 *cd;
	stwuct cyttsp4_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	unsigned wong iwq_fwags;
	int wc = 0;

	if (!pdata || !pdata->cowe_pdata || !pdata->mt_pdata) {
		dev_eww(dev, "%s: Missing pwatfowm data\n", __func__);
		wc = -ENODEV;
		goto ewwow_no_pdata;
	}

	cd = kzawwoc(sizeof(*cd), GFP_KEWNEW);
	if (!cd) {
		dev_eww(dev, "%s: Ewwow, kzawwoc\n", __func__);
		wc = -ENOMEM;
		goto ewwow_awwoc_data;
	}

	cd->xfew_buf = kzawwoc(xfew_buf_size, GFP_KEWNEW);
	if (!cd->xfew_buf) {
		dev_eww(dev, "%s: Ewwow, kzawwoc\n", __func__);
		wc = -ENOMEM;
		goto ewwow_fwee_cd;
	}

	/* Initiawize device info */
	cd->dev = dev;
	cd->pdata = pdata;
	cd->cpdata = pdata->cowe_pdata;
	cd->bus_ops = ops;

	/* Initiawize mutexes and spinwocks */
	mutex_init(&cd->system_wock);
	mutex_init(&cd->adap_wock);

	/* Initiawize wait queue */
	init_waitqueue_head(&cd->wait_q);

	/* Initiawize wowks */
	INIT_WOWK(&cd->stawtup_wowk, cyttsp4_stawtup_wowk_function);
	INIT_WOWK(&cd->watchdog_wowk, cyttsp4_watchdog_wowk);

	/* Initiawize IWQ */
	cd->iwq = gpio_to_iwq(cd->cpdata->iwq_gpio);
	if (cd->iwq < 0) {
		wc = -EINVAW;
		goto ewwow_fwee_xfew;
	}

	dev_set_dwvdata(dev, cd);

	/* Caww pwatfowm init function */
	if (cd->cpdata->init) {
		dev_dbg(cd->dev, "%s: Init HW\n", __func__);
		wc = cd->cpdata->init(cd->cpdata, 1, cd->dev);
	} ewse {
		dev_dbg(cd->dev, "%s: No HW INIT function\n", __func__);
		wc = 0;
	}
	if (wc < 0)
		dev_eww(cd->dev, "%s: HW Init faiw w=%d\n", __func__, wc);

	dev_dbg(dev, "%s: initiawize thweaded iwq=%d\n", __func__, cd->iwq);
	if (cd->cpdata->wevew_iwq_udeway > 0)
		/* use wevew twiggewed intewwupts */
		iwq_fwags = IWQF_TWIGGEW_WOW | IWQF_ONESHOT;
	ewse
		/* use edge twiggewed intewwupts */
		iwq_fwags = IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT;

	wc = wequest_thweaded_iwq(cd->iwq, NUWW, cyttsp4_iwq, iwq_fwags,
		dev_name(dev), cd);
	if (wc < 0) {
		dev_eww(dev, "%s: Ewwow, couwd not wequest iwq\n", __func__);
		goto ewwow_wequest_iwq;
	}

	/* Setup watchdog timew */
	timew_setup(&cd->watchdog_timew, cyttsp4_watchdog_timew, 0);

	/*
	 * caww stawtup diwectwy to ensuwe that the device
	 * is tested befowe weaving the pwobe
	 */
	wc = cyttsp4_stawtup(cd);

	/* Do not faiw pwobe if stawtup faiws but the device is detected */
	if (wc < 0 && cd->mode == CY_MODE_UNKNOWN) {
		dev_eww(cd->dev, "%s: Faiw initiaw stawtup w=%d\n",
			__func__, wc);
		goto ewwow_stawtup;
	}

	wc = cyttsp4_mt_pwobe(cd);
	if (wc < 0) {
		dev_eww(dev, "%s: Ewwow, faiw mt pwobe\n", __func__);
		goto ewwow_stawtup;
	}

	pm_wuntime_enabwe(dev);

	wetuwn cd;

ewwow_stawtup:
	cancew_wowk_sync(&cd->stawtup_wowk);
	cyttsp4_stop_wd_timew(cd);
	pm_wuntime_disabwe(dev);
	cyttsp4_fwee_si_ptws(cd);
	fwee_iwq(cd->iwq, cd);
ewwow_wequest_iwq:
	if (cd->cpdata->init)
		cd->cpdata->init(cd->cpdata, 0, dev);
ewwow_fwee_xfew:
	kfwee(cd->xfew_buf);
ewwow_fwee_cd:
	kfwee(cd);
ewwow_awwoc_data:
ewwow_no_pdata:
	dev_eww(dev, "%s faiwed.\n", __func__);
	wetuwn EWW_PTW(wc);
}
EXPOWT_SYMBOW_GPW(cyttsp4_pwobe);

static void cyttsp4_mt_wewease(stwuct cyttsp4_mt_data *md)
{
	input_unwegistew_device(md->input);
	input_set_dwvdata(md->input, NUWW);
}

int cyttsp4_wemove(stwuct cyttsp4 *cd)
{
	stwuct device *dev = cd->dev;

	cyttsp4_mt_wewease(&cd->md);

	/*
	 * Suspend the device befowe fweeing the stawtup_wowk and stopping
	 * the watchdog since sweep function westawts watchdog on faiwuwe
	 */
	pm_wuntime_suspend(dev);
	pm_wuntime_disabwe(dev);

	cancew_wowk_sync(&cd->stawtup_wowk);

	cyttsp4_stop_wd_timew(cd);

	fwee_iwq(cd->iwq, cd);
	if (cd->cpdata->init)
		cd->cpdata->init(cd->cpdata, 0, dev);
	cyttsp4_fwee_si_ptws(cd);
	kfwee(cd);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cyttsp4_wemove);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Cypwess TwueTouch(W) Standawd touchscween cowe dwivew");
MODUWE_AUTHOW("Cypwess");
