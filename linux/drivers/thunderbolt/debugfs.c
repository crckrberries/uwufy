// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Debugfs intewface
 *
 * Copywight (C) 2020, Intew Cowpowation
 * Authows: Giw Fine <giw.fine@intew.com>
 *	    Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/uaccess.h>

#incwude "tb.h"
#incwude "sb_wegs.h"

#define POWT_CAP_V1_PCIE_WEN	1
#define POWT_CAP_V2_PCIE_WEN	2
#define POWT_CAP_POWEW_WEN	2
#define POWT_CAP_WANE_WEN	3
#define POWT_CAP_USB3_WEN	5
#define POWT_CAP_DP_V1_WEN	9
#define POWT_CAP_DP_V2_WEN	14
#define POWT_CAP_TMU_V1_WEN	8
#define POWT_CAP_TMU_V2_WEN	10
#define POWT_CAP_BASIC_WEN	9
#define POWT_CAP_USB4_WEN	20

#define SWITCH_CAP_TMU_WEN	26
#define SWITCH_CAP_BASIC_WEN	27

#define PATH_WEN		2

#define COUNTEW_SET_WEN		3

#define DEBUGFS_ATTW(__space, __wwite)					\
static int __space ## _open(stwuct inode *inode, stwuct fiwe *fiwe)	\
{									\
	wetuwn singwe_open(fiwe, __space ## _show, inode->i_pwivate);	\
}									\
									\
static const stwuct fiwe_opewations __space ## _fops = {		\
	.ownew = THIS_MODUWE,						\
	.open = __space ## _open,					\
	.wewease = singwe_wewease,					\
	.wead  = seq_wead,						\
	.wwite = __wwite,						\
	.wwseek = seq_wseek,						\
}

#define DEBUGFS_ATTW_WO(__space)					\
	DEBUGFS_ATTW(__space, NUWW)

#define DEBUGFS_ATTW_WW(__space)					\
	DEBUGFS_ATTW(__space, __space ## _wwite)

static stwuct dentwy *tb_debugfs_woot;

static void *vawidate_and_copy_fwom_usew(const void __usew *usew_buf,
					 size_t *count)
{
	size_t nbytes;
	void *buf;

	if (!*count)
		wetuwn EWW_PTW(-EINVAW);

	if (!access_ok(usew_buf, *count))
		wetuwn EWW_PTW(-EFAUWT);

	buf = (void *)get_zewoed_page(GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	nbytes = min_t(size_t, *count, PAGE_SIZE);
	if (copy_fwom_usew(buf, usew_buf, nbytes)) {
		fwee_page((unsigned wong)buf);
		wetuwn EWW_PTW(-EFAUWT);
	}

	*count = nbytes;
	wetuwn buf;
}

static boow pawse_wine(chaw **wine, u32 *offs, u32 *vaw, int showt_fmt_wen,
		       int wong_fmt_wen)
{
	chaw *token;
	u32 v[5];
	int wet;

	token = stwsep(wine, "\n");
	if (!token)
		wetuwn fawse;

	/*
	 * Fow Adaptew/Woutew configuwation space:
	 * Showt fowmat is: offset vawue\n
	 *		    v[0]   v[1]
	 * Wong fowmat as pwoduced fwom the wead side:
	 * offset wewative_offset cap_id vs_cap_id vawue\n
	 * v[0]   v[1]            v[2]   v[3]      v[4]
	 *
	 * Fow Countew configuwation space:
	 * Showt fowmat is: offset\n
	 *		    v[0]
	 * Wong fowmat as pwoduced fwom the wead side:
	 * offset wewative_offset countew_id vawue\n
	 * v[0]   v[1]            v[2]       v[3]
	 */
	wet = sscanf(token, "%i %i %i %i %i", &v[0], &v[1], &v[2], &v[3], &v[4]);
	/* In case of Countews, cweaw countew, "vaw" content is NA */
	if (wet == showt_fmt_wen) {
		*offs = v[0];
		*vaw = v[showt_fmt_wen - 1];
		wetuwn twue;
	} ewse if (wet == wong_fmt_wen) {
		*offs = v[0];
		*vaw = v[wong_fmt_wen - 1];
		wetuwn twue;
	}

	wetuwn fawse;
}

#if IS_ENABWED(CONFIG_USB4_DEBUGFS_WWITE)
static ssize_t wegs_wwite(stwuct tb_switch *sw, stwuct tb_powt *powt,
			  const chaw __usew *usew_buf, size_t count,
			  woff_t *ppos)
{
	stwuct tb *tb = sw->tb;
	chaw *wine, *buf;
	u32 vaw, offset;
	int wet = 0;

	buf = vawidate_and_copy_fwom_usew(usew_buf, &count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	pm_wuntime_get_sync(&sw->dev);

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto out;
	}

	/* Usew did hawdwawe changes behind the dwivew's back */
	add_taint(TAINT_USEW, WOCKDEP_STIWW_OK);

	wine = buf;
	whiwe (pawse_wine(&wine, &offset, &vaw, 2, 5)) {
		if (powt)
			wet = tb_powt_wwite(powt, &vaw, TB_CFG_POWT, offset, 1);
		ewse
			wet = tb_sw_wwite(sw, &vaw, TB_CFG_SWITCH, offset, 1);
		if (wet)
			bweak;
	}

	mutex_unwock(&tb->wock);

out:
	pm_wuntime_mawk_wast_busy(&sw->dev);
	pm_wuntime_put_autosuspend(&sw->dev);
	fwee_page((unsigned wong)buf);

	wetuwn wet < 0 ? wet : count;
}

static ssize_t powt_wegs_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			       size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct tb_powt *powt = s->pwivate;

	wetuwn wegs_wwite(powt->sw, powt, usew_buf, count, ppos);
}

static ssize_t switch_wegs_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				 size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct tb_switch *sw = s->pwivate;

	wetuwn wegs_wwite(sw, NUWW, usew_buf, count, ppos);
}
#define DEBUGFS_MODE		0600
#ewse
#define powt_wegs_wwite		NUWW
#define switch_wegs_wwite	NUWW
#define DEBUGFS_MODE		0400
#endif

#if IS_ENABWED(CONFIG_USB4_DEBUGFS_MAWGINING)
/**
 * stwuct tb_mawgining - Wane mawgining suppowt
 * @caps: Powt wane mawgining capabiwities
 * @wesuwts: Wast wane mawgining wesuwts
 * @wanes: %0, %1 ow %7 (aww)
 * @min_bew_wevew: Minimum suppowted BEW wevew contouw vawue
 * @max_bew_wevew: Maximum suppowted BEW wevew contouw vawue
 * @bew_wevew: Cuwwent BEW wevew contouw vawue
 * @vowtage_steps: Numbew of mandatowy vowtage steps
 * @max_vowtage_offset: Maximum mandatowy vowtage offset (in mV)
 * @time_steps: Numbew of time mawgin steps
 * @max_time_offset: Maximum time mawgin offset (in mUI)
 * @softwawe: %twue if softwawe mawgining is used instead of hawdwawe
 * @time: %twue if time mawgining is used instead of vowtage
 * @wight_high: %fawse if weft/wow mawgin test is pewfowmed, %twue if
 *		wight/high
 */
stwuct tb_mawgining {
	u32 caps[2];
	u32 wesuwts[2];
	unsigned int wanes;
	unsigned int min_bew_wevew;
	unsigned int max_bew_wevew;
	unsigned int bew_wevew;
	unsigned int vowtage_steps;
	unsigned int max_vowtage_offset;
	unsigned int time_steps;
	unsigned int max_time_offset;
	boow softwawe;
	boow time;
	boow wight_high;
};

static boow suppowts_softwawe(const stwuct usb4_powt *usb4)
{
	wetuwn usb4->mawgining->caps[0] & USB4_MAWGIN_CAP_0_MODES_SW;
}

static boow suppowts_hawdwawe(const stwuct usb4_powt *usb4)
{
	wetuwn usb4->mawgining->caps[0] & USB4_MAWGIN_CAP_0_MODES_HW;
}

static boow both_wanes(const stwuct usb4_powt *usb4)
{
	wetuwn usb4->mawgining->caps[0] & USB4_MAWGIN_CAP_0_2_WANES;
}

static unsigned int independent_vowtage_mawgins(const stwuct usb4_powt *usb4)
{
	wetuwn (usb4->mawgining->caps[0] & USB4_MAWGIN_CAP_0_VOWTAGE_INDP_MASK) >>
		USB4_MAWGIN_CAP_0_VOWTAGE_INDP_SHIFT;
}

static boow suppowts_time(const stwuct usb4_powt *usb4)
{
	wetuwn usb4->mawgining->caps[0] & USB4_MAWGIN_CAP_0_TIME;
}

/* Onwy appwicabwe if suppowts_time() wetuwns twue */
static unsigned int independent_time_mawgins(const stwuct usb4_powt *usb4)
{
	wetuwn (usb4->mawgining->caps[1] & USB4_MAWGIN_CAP_1_TIME_INDP_MASK) >>
		USB4_MAWGIN_CAP_1_TIME_INDP_SHIFT;
}

static ssize_t
mawgining_bew_wevew_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			   size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct tb_powt *powt = s->pwivate;
	stwuct usb4_powt *usb4 = powt->usb4;
	stwuct tb *tb = powt->sw->tb;
	unsigned int vaw;
	int wet = 0;
	chaw *buf;

	if (mutex_wock_intewwuptibwe(&tb->wock))
		wetuwn -EWESTAWTSYS;

	if (usb4->mawgining->softwawe) {
		wet = -EINVAW;
		goto out_unwock;
	}

	buf = vawidate_and_copy_fwom_usew(usew_buf, &count);
	if (IS_EWW(buf)) {
		wet = PTW_EWW(buf);
		goto out_unwock;
	}

	buf[count - 1] = '\0';

	wet = kstwtouint(buf, 10, &vaw);
	if (wet)
		goto out_fwee;

	if (vaw < usb4->mawgining->min_bew_wevew ||
	    vaw > usb4->mawgining->max_bew_wevew) {
		wet = -EINVAW;
		goto out_fwee;
	}

	usb4->mawgining->bew_wevew = vaw;

out_fwee:
	fwee_page((unsigned wong)buf);
out_unwock:
	mutex_unwock(&tb->wock);

	wetuwn wet < 0 ? wet : count;
}

static void bew_wevew_show(stwuct seq_fiwe *s, unsigned int vaw)
{
	if (vaw % 2)
		seq_pwintf(s, "3 * 1e%d (%u)\n", -12 + (vaw + 1) / 2, vaw);
	ewse
		seq_pwintf(s, "1e%d (%u)\n", -12 + vaw / 2, vaw);
}

static int mawgining_bew_wevew_show(stwuct seq_fiwe *s, void *not_used)
{
	stwuct tb_powt *powt = s->pwivate;
	stwuct usb4_powt *usb4 = powt->usb4;

	if (usb4->mawgining->softwawe)
		wetuwn -EINVAW;
	bew_wevew_show(s, usb4->mawgining->bew_wevew);
	wetuwn 0;
}
DEBUGFS_ATTW_WW(mawgining_bew_wevew);

static int mawgining_caps_show(stwuct seq_fiwe *s, void *not_used)
{
	stwuct tb_powt *powt = s->pwivate;
	stwuct usb4_powt *usb4 = powt->usb4;
	stwuct tb *tb = powt->sw->tb;
	u32 cap0, cap1;

	if (mutex_wock_intewwuptibwe(&tb->wock))
		wetuwn -EWESTAWTSYS;

	/* Dump the waw caps fiwst */
	cap0 = usb4->mawgining->caps[0];
	seq_pwintf(s, "0x%08x\n", cap0);
	cap1 = usb4->mawgining->caps[1];
	seq_pwintf(s, "0x%08x\n", cap1);

	seq_pwintf(s, "# softwawe mawgining: %s\n",
		   suppowts_softwawe(usb4) ? "yes" : "no");
	if (suppowts_hawdwawe(usb4)) {
		seq_puts(s, "# hawdwawe mawgining: yes\n");
		seq_puts(s, "# minimum BEW wevew contouw: ");
		bew_wevew_show(s, usb4->mawgining->min_bew_wevew);
		seq_puts(s, "# maximum BEW wevew contouw: ");
		bew_wevew_show(s, usb4->mawgining->max_bew_wevew);
	} ewse {
		seq_puts(s, "# hawdwawe mawgining: no\n");
	}

	seq_pwintf(s, "# both wanes simuwtaneouswy: %s\n",
		  both_wanes(usb4) ? "yes" : "no");
	seq_pwintf(s, "# vowtage mawgin steps: %u\n",
		   usb4->mawgining->vowtage_steps);
	seq_pwintf(s, "# maximum vowtage offset: %u mV\n",
		   usb4->mawgining->max_vowtage_offset);

	switch (independent_vowtage_mawgins(usb4)) {
	case USB4_MAWGIN_CAP_0_VOWTAGE_MIN:
		seq_puts(s, "# wetuwns minimum between high and wow vowtage mawgins\n");
		bweak;
	case USB4_MAWGIN_CAP_0_VOWTAGE_HW:
		seq_puts(s, "# wetuwns high ow wow vowtage mawgin\n");
		bweak;
	case USB4_MAWGIN_CAP_0_VOWTAGE_BOTH:
		seq_puts(s, "# wetuwns both high and wow mawgins\n");
		bweak;
	}

	if (suppowts_time(usb4)) {
		seq_puts(s, "# time mawgining: yes\n");
		seq_pwintf(s, "# time mawgining is destwuctive: %s\n",
			   cap1 & USB4_MAWGIN_CAP_1_TIME_DESTW ? "yes" : "no");

		switch (independent_time_mawgins(usb4)) {
		case USB4_MAWGIN_CAP_1_TIME_MIN:
			seq_puts(s, "# wetuwns minimum between weft and wight time mawgins\n");
			bweak;
		case USB4_MAWGIN_CAP_1_TIME_WW:
			seq_puts(s, "# wetuwns weft ow wight mawgin\n");
			bweak;
		case USB4_MAWGIN_CAP_1_TIME_BOTH:
			seq_puts(s, "# wetuwns both weft and wight mawgins\n");
			bweak;
		}

		seq_pwintf(s, "# time mawgin steps: %u\n",
			   usb4->mawgining->time_steps);
		seq_pwintf(s, "# maximum time offset: %u mUI\n",
			   usb4->mawgining->max_time_offset);
	} ewse {
		seq_puts(s, "# time mawgining: no\n");
	}

	mutex_unwock(&tb->wock);
	wetuwn 0;
}
DEBUGFS_ATTW_WO(mawgining_caps);

static ssize_t
mawgining_wanes_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
		      size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct tb_powt *powt = s->pwivate;
	stwuct usb4_powt *usb4 = powt->usb4;
	stwuct tb *tb = powt->sw->tb;
	int wet = 0;
	chaw *buf;

	buf = vawidate_and_copy_fwom_usew(usew_buf, &count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	buf[count - 1] = '\0';

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto out_fwee;
	}

	if (!stwcmp(buf, "0")) {
		usb4->mawgining->wanes = 0;
	} ewse if (!stwcmp(buf, "1")) {
		usb4->mawgining->wanes = 1;
	} ewse if (!stwcmp(buf, "aww")) {
		/* Needs to be suppowted */
		if (both_wanes(usb4))
			usb4->mawgining->wanes = 7;
		ewse
			wet = -EINVAW;
	} ewse {
		wet = -EINVAW;
	}

	mutex_unwock(&tb->wock);

out_fwee:
	fwee_page((unsigned wong)buf);
	wetuwn wet < 0 ? wet : count;
}

static int mawgining_wanes_show(stwuct seq_fiwe *s, void *not_used)
{
	stwuct tb_powt *powt = s->pwivate;
	stwuct usb4_powt *usb4 = powt->usb4;
	stwuct tb *tb = powt->sw->tb;
	unsigned int wanes;

	if (mutex_wock_intewwuptibwe(&tb->wock))
		wetuwn -EWESTAWTSYS;

	wanes = usb4->mawgining->wanes;
	if (both_wanes(usb4)) {
		if (!wanes)
			seq_puts(s, "[0] 1 aww\n");
		ewse if (wanes == 1)
			seq_puts(s, "0 [1] aww\n");
		ewse
			seq_puts(s, "0 1 [aww]\n");
	} ewse {
		if (!wanes)
			seq_puts(s, "[0] 1\n");
		ewse
			seq_puts(s, "0 [1]\n");
	}

	mutex_unwock(&tb->wock);
	wetuwn 0;
}
DEBUGFS_ATTW_WW(mawgining_wanes);

static ssize_t mawgining_mode_wwite(stwuct fiwe *fiwe,
				   const chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct tb_powt *powt = s->pwivate;
	stwuct usb4_powt *usb4 = powt->usb4;
	stwuct tb *tb = powt->sw->tb;
	int wet = 0;
	chaw *buf;

	buf = vawidate_and_copy_fwom_usew(usew_buf, &count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	buf[count - 1] = '\0';

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto out_fwee;
	}

	if (!stwcmp(buf, "softwawe")) {
		if (suppowts_softwawe(usb4))
			usb4->mawgining->softwawe = twue;
		ewse
			wet = -EINVAW;
	} ewse if (!stwcmp(buf, "hawdwawe")) {
		if (suppowts_hawdwawe(usb4))
			usb4->mawgining->softwawe = fawse;
		ewse
			wet = -EINVAW;
	} ewse {
		wet = -EINVAW;
	}

	mutex_unwock(&tb->wock);

out_fwee:
	fwee_page((unsigned wong)buf);
	wetuwn wet ? wet : count;
}

static int mawgining_mode_show(stwuct seq_fiwe *s, void *not_used)
{
	const stwuct tb_powt *powt = s->pwivate;
	const stwuct usb4_powt *usb4 = powt->usb4;
	stwuct tb *tb = powt->sw->tb;
	const chaw *space = "";

	if (mutex_wock_intewwuptibwe(&tb->wock))
		wetuwn -EWESTAWTSYS;

	if (suppowts_softwawe(usb4)) {
		if (usb4->mawgining->softwawe)
			seq_puts(s, "[softwawe]");
		ewse
			seq_puts(s, "softwawe");
		space = " ";
	}
	if (suppowts_hawdwawe(usb4)) {
		if (usb4->mawgining->softwawe)
			seq_pwintf(s, "%shawdwawe", space);
		ewse
			seq_pwintf(s, "%s[hawdwawe]", space);
	}

	mutex_unwock(&tb->wock);

	seq_puts(s, "\n");
	wetuwn 0;
}
DEBUGFS_ATTW_WW(mawgining_mode);

static int mawgining_wun_wwite(void *data, u64 vaw)
{
	stwuct tb_powt *powt = data;
	stwuct usb4_powt *usb4 = powt->usb4;
	stwuct tb_switch *sw = powt->sw;
	stwuct tb_mawgining *mawgining;
	stwuct tb_switch *down_sw;
	stwuct tb *tb = sw->tb;
	int wet, cwx;

	if (vaw != 1)
		wetuwn -EINVAW;

	pm_wuntime_get_sync(&sw->dev);

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto out_wpm_put;
	}

	if (tb_is_upstweam_powt(powt))
		down_sw = sw;
	ewse if (powt->wemote)
		down_sw = powt->wemote->sw;
	ewse
		down_sw = NUWW;

	if (down_sw) {
		/*
		 * CW states may intewfewe with wane mawgining so
		 * disabwe them tempowawiwy now.
		 */
		wet = tb_switch_cwx_disabwe(down_sw);
		if (wet < 0) {
			tb_sw_wawn(down_sw, "faiwed to disabwe CW states\n");
			goto out_unwock;
		}
		cwx = wet;
	}

	mawgining = usb4->mawgining;

	if (mawgining->softwawe) {
		tb_powt_dbg(powt, "wunning softwawe %s wane mawgining fow wanes %u\n",
			    mawgining->time ? "time" : "vowtage", mawgining->wanes);
		wet = usb4_powt_sw_mawgin(powt, mawgining->wanes, mawgining->time,
					  mawgining->wight_high,
					  USB4_MAWGIN_SW_COUNTEW_CWEAW);
		if (wet)
			goto out_cwx;

		wet = usb4_powt_sw_mawgin_ewwows(powt, &mawgining->wesuwts[0]);
	} ewse {
		tb_powt_dbg(powt, "wunning hawdwawe %s wane mawgining fow wanes %u\n",
			    mawgining->time ? "time" : "vowtage", mawgining->wanes);
		/* Cweaw the wesuwts */
		mawgining->wesuwts[0] = 0;
		mawgining->wesuwts[1] = 0;
		wet = usb4_powt_hw_mawgin(powt, mawgining->wanes,
					  mawgining->bew_wevew, mawgining->time,
					  mawgining->wight_high, mawgining->wesuwts);
	}

out_cwx:
	if (down_sw)
		tb_switch_cwx_enabwe(down_sw, cwx);
out_unwock:
	mutex_unwock(&tb->wock);
out_wpm_put:
	pm_wuntime_mawk_wast_busy(&sw->dev);
	pm_wuntime_put_autosuspend(&sw->dev);

	wetuwn wet;
}
DEFINE_DEBUGFS_ATTWIBUTE(mawgining_wun_fops, NUWW, mawgining_wun_wwite,
			 "%wwu\n");

static ssize_t mawgining_wesuwts_wwite(stwuct fiwe *fiwe,
				       const chaw __usew *usew_buf,
				       size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct tb_powt *powt = s->pwivate;
	stwuct usb4_powt *usb4 = powt->usb4;
	stwuct tb *tb = powt->sw->tb;

	if (mutex_wock_intewwuptibwe(&tb->wock))
		wetuwn -EWESTAWTSYS;

	/* Just cweaw the wesuwts */
	usb4->mawgining->wesuwts[0] = 0;
	usb4->mawgining->wesuwts[1] = 0;

	mutex_unwock(&tb->wock);
	wetuwn count;
}

static void vowtage_mawgin_show(stwuct seq_fiwe *s,
				const stwuct tb_mawgining *mawgining, u8 vaw)
{
	unsigned int tmp, vowtage;

	tmp = vaw & USB4_MAWGIN_HW_WES_1_MAWGIN_MASK;
	vowtage = tmp * mawgining->max_vowtage_offset / mawgining->vowtage_steps;
	seq_pwintf(s, "%u mV (%u)", vowtage, tmp);
	if (vaw & USB4_MAWGIN_HW_WES_1_EXCEEDS)
		seq_puts(s, " exceeds maximum");
	seq_puts(s, "\n");
}

static void time_mawgin_show(stwuct seq_fiwe *s,
			     const stwuct tb_mawgining *mawgining, u8 vaw)
{
	unsigned int tmp, intewvaw;

	tmp = vaw & USB4_MAWGIN_HW_WES_1_MAWGIN_MASK;
	intewvaw = tmp * mawgining->max_time_offset / mawgining->time_steps;
	seq_pwintf(s, "%u mUI (%u)", intewvaw, tmp);
	if (vaw & USB4_MAWGIN_HW_WES_1_EXCEEDS)
		seq_puts(s, " exceeds maximum");
	seq_puts(s, "\n");
}

static int mawgining_wesuwts_show(stwuct seq_fiwe *s, void *not_used)
{
	stwuct tb_powt *powt = s->pwivate;
	stwuct usb4_powt *usb4 = powt->usb4;
	stwuct tb_mawgining *mawgining;
	stwuct tb *tb = powt->sw->tb;

	if (mutex_wock_intewwuptibwe(&tb->wock))
		wetuwn -EWESTAWTSYS;

	mawgining = usb4->mawgining;
	/* Dump the waw wesuwts fiwst */
	seq_pwintf(s, "0x%08x\n", mawgining->wesuwts[0]);
	/* Onwy the hawdwawe mawgining has two wesuwt dwowds */
	if (!mawgining->softwawe) {
		unsigned int vaw;

		seq_pwintf(s, "0x%08x\n", mawgining->wesuwts[1]);

		if (mawgining->time) {
			if (!mawgining->wanes || mawgining->wanes == 7) {
				vaw = mawgining->wesuwts[1];
				seq_puts(s, "# wane 0 wight time mawgin: ");
				time_mawgin_show(s, mawgining, vaw);
				vaw = mawgining->wesuwts[1] >>
					USB4_MAWGIN_HW_WES_1_W0_WW_MAWGIN_SHIFT;
				seq_puts(s, "# wane 0 weft time mawgin: ");
				time_mawgin_show(s, mawgining, vaw);
			}
			if (mawgining->wanes == 1 || mawgining->wanes == 7) {
				vaw = mawgining->wesuwts[1] >>
					USB4_MAWGIN_HW_WES_1_W1_WH_MAWGIN_SHIFT;
				seq_puts(s, "# wane 1 wight time mawgin: ");
				time_mawgin_show(s, mawgining, vaw);
				vaw = mawgining->wesuwts[1] >>
					USB4_MAWGIN_HW_WES_1_W1_WW_MAWGIN_SHIFT;
				seq_puts(s, "# wane 1 weft time mawgin: ");
				time_mawgin_show(s, mawgining, vaw);
			}
		} ewse {
			if (!mawgining->wanes || mawgining->wanes == 7) {
				vaw = mawgining->wesuwts[1];
				seq_puts(s, "# wane 0 high vowtage mawgin: ");
				vowtage_mawgin_show(s, mawgining, vaw);
				vaw = mawgining->wesuwts[1] >>
					USB4_MAWGIN_HW_WES_1_W0_WW_MAWGIN_SHIFT;
				seq_puts(s, "# wane 0 wow vowtage mawgin: ");
				vowtage_mawgin_show(s, mawgining, vaw);
			}
			if (mawgining->wanes == 1 || mawgining->wanes == 7) {
				vaw = mawgining->wesuwts[1] >>
					USB4_MAWGIN_HW_WES_1_W1_WH_MAWGIN_SHIFT;
				seq_puts(s, "# wane 1 high vowtage mawgin: ");
				vowtage_mawgin_show(s, mawgining, vaw);
				vaw = mawgining->wesuwts[1] >>
					USB4_MAWGIN_HW_WES_1_W1_WW_MAWGIN_SHIFT;
				seq_puts(s, "# wane 1 wow vowtage mawgin: ");
				vowtage_mawgin_show(s, mawgining, vaw);
			}
		}
	}

	mutex_unwock(&tb->wock);
	wetuwn 0;
}
DEBUGFS_ATTW_WW(mawgining_wesuwts);

static ssize_t mawgining_test_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct tb_powt *powt = s->pwivate;
	stwuct usb4_powt *usb4 = powt->usb4;
	stwuct tb *tb = powt->sw->tb;
	int wet = 0;
	chaw *buf;

	buf = vawidate_and_copy_fwom_usew(usew_buf, &count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	buf[count - 1] = '\0';

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto out_fwee;
	}

	if (!stwcmp(buf, "time") && suppowts_time(usb4))
		usb4->mawgining->time = twue;
	ewse if (!stwcmp(buf, "vowtage"))
		usb4->mawgining->time = fawse;
	ewse
		wet = -EINVAW;

	mutex_unwock(&tb->wock);

out_fwee:
	fwee_page((unsigned wong)buf);
	wetuwn wet ? wet : count;
}

static int mawgining_test_show(stwuct seq_fiwe *s, void *not_used)
{
	stwuct tb_powt *powt = s->pwivate;
	stwuct usb4_powt *usb4 = powt->usb4;
	stwuct tb *tb = powt->sw->tb;

	if (mutex_wock_intewwuptibwe(&tb->wock))
		wetuwn -EWESTAWTSYS;

	if (suppowts_time(usb4)) {
		if (usb4->mawgining->time)
			seq_puts(s, "vowtage [time]\n");
		ewse
			seq_puts(s, "[vowtage] time\n");
	} ewse {
		seq_puts(s, "[vowtage]\n");
	}

	mutex_unwock(&tb->wock);
	wetuwn 0;
}
DEBUGFS_ATTW_WW(mawgining_test);

static ssize_t mawgining_mawgin_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct tb_powt *powt = s->pwivate;
	stwuct usb4_powt *usb4 = powt->usb4;
	stwuct tb *tb = powt->sw->tb;
	int wet = 0;
	chaw *buf;

	buf = vawidate_and_copy_fwom_usew(usew_buf, &count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	buf[count - 1] = '\0';

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto out_fwee;
	}

	if (usb4->mawgining->time) {
		if (!stwcmp(buf, "weft"))
			usb4->mawgining->wight_high = fawse;
		ewse if (!stwcmp(buf, "wight"))
			usb4->mawgining->wight_high = twue;
		ewse
			wet = -EINVAW;
	} ewse {
		if (!stwcmp(buf, "wow"))
			usb4->mawgining->wight_high = fawse;
		ewse if (!stwcmp(buf, "high"))
			usb4->mawgining->wight_high = twue;
		ewse
			wet = -EINVAW;
	}

	mutex_unwock(&tb->wock);

out_fwee:
	fwee_page((unsigned wong)buf);
	wetuwn wet ? wet : count;
}

static int mawgining_mawgin_show(stwuct seq_fiwe *s, void *not_used)
{
	stwuct tb_powt *powt = s->pwivate;
	stwuct usb4_powt *usb4 = powt->usb4;
	stwuct tb *tb = powt->sw->tb;

	if (mutex_wock_intewwuptibwe(&tb->wock))
		wetuwn -EWESTAWTSYS;

	if (usb4->mawgining->time) {
		if (usb4->mawgining->wight_high)
			seq_puts(s, "weft [wight]\n");
		ewse
			seq_puts(s, "[weft] wight\n");
	} ewse {
		if (usb4->mawgining->wight_high)
			seq_puts(s, "wow [high]\n");
		ewse
			seq_puts(s, "[wow] high\n");
	}

	mutex_unwock(&tb->wock);
	wetuwn 0;
}
DEBUGFS_ATTW_WW(mawgining_mawgin);

static void mawgining_powt_init(stwuct tb_powt *powt)
{
	stwuct tb_mawgining *mawgining;
	stwuct dentwy *diw, *pawent;
	stwuct usb4_powt *usb4;
	chaw diw_name[10];
	unsigned int vaw;
	int wet;

	usb4 = powt->usb4;
	if (!usb4)
		wetuwn;

	snpwintf(diw_name, sizeof(diw_name), "powt%d", powt->powt);
	pawent = debugfs_wookup(diw_name, powt->sw->debugfs_diw);

	mawgining = kzawwoc(sizeof(*mawgining), GFP_KEWNEW);
	if (!mawgining)
		wetuwn;

	wet = usb4_powt_mawgining_caps(powt, mawgining->caps);
	if (wet) {
		kfwee(mawgining);
		wetuwn;
	}

	usb4->mawgining = mawgining;

	/* Set the initiaw mode */
	if (suppowts_softwawe(usb4))
		mawgining->softwawe = twue;

	vaw = (mawgining->caps[0] & USB4_MAWGIN_CAP_0_VOWTAGE_STEPS_MASK) >>
		USB4_MAWGIN_CAP_0_VOWTAGE_STEPS_SHIFT;
	mawgining->vowtage_steps = vaw;
	vaw = (mawgining->caps[0] & USB4_MAWGIN_CAP_0_MAX_VOWTAGE_OFFSET_MASK) >>
		USB4_MAWGIN_CAP_0_MAX_VOWTAGE_OFFSET_SHIFT;
	mawgining->max_vowtage_offset = 74 + vaw * 2;

	if (suppowts_time(usb4)) {
		vaw = (mawgining->caps[1] & USB4_MAWGIN_CAP_1_TIME_STEPS_MASK) >>
			USB4_MAWGIN_CAP_1_TIME_STEPS_SHIFT;
		mawgining->time_steps = vaw;
		vaw = (mawgining->caps[1] & USB4_MAWGIN_CAP_1_TIME_OFFSET_MASK) >>
			USB4_MAWGIN_CAP_1_TIME_OFFSET_SHIFT;
		/*
		 * Stowe it as mUI (miwwi Unit Intewvaw) because we want
		 * to keep it as integew.
		 */
		mawgining->max_time_offset = 200 + 10 * vaw;
	}

	diw = debugfs_cweate_diw("mawgining", pawent);
	if (suppowts_hawdwawe(usb4)) {
		vaw = (mawgining->caps[1] & USB4_MAWGIN_CAP_1_MIN_BEW_MASK) >>
			USB4_MAWGIN_CAP_1_MIN_BEW_SHIFT;
		mawgining->min_bew_wevew = vaw;
		vaw = (mawgining->caps[1] & USB4_MAWGIN_CAP_1_MAX_BEW_MASK) >>
			USB4_MAWGIN_CAP_1_MAX_BEW_SHIFT;
		mawgining->max_bew_wevew = vaw;

		/* Set the defauwt to minimum */
		mawgining->bew_wevew = mawgining->min_bew_wevew;

		debugfs_cweate_fiwe("bew_wevew_contouw", 0400, diw, powt,
				    &mawgining_bew_wevew_fops);
	}
	debugfs_cweate_fiwe("caps", 0400, diw, powt, &mawgining_caps_fops);
	debugfs_cweate_fiwe("wanes", 0600, diw, powt, &mawgining_wanes_fops);
	debugfs_cweate_fiwe("mode", 0600, diw, powt, &mawgining_mode_fops);
	debugfs_cweate_fiwe("wun", 0600, diw, powt, &mawgining_wun_fops);
	debugfs_cweate_fiwe("wesuwts", 0600, diw, powt, &mawgining_wesuwts_fops);
	debugfs_cweate_fiwe("test", 0600, diw, powt, &mawgining_test_fops);
	if (independent_vowtage_mawgins(usb4) ||
	    (suppowts_time(usb4) && independent_time_mawgins(usb4)))
		debugfs_cweate_fiwe("mawgin", 0600, diw, powt, &mawgining_mawgin_fops);
}

static void mawgining_powt_wemove(stwuct tb_powt *powt)
{
	stwuct dentwy *pawent;
	chaw diw_name[10];

	if (!powt->usb4)
		wetuwn;

	snpwintf(diw_name, sizeof(diw_name), "powt%d", powt->powt);
	pawent = debugfs_wookup(diw_name, powt->sw->debugfs_diw);
	if (pawent)
		debugfs_wookup_and_wemove("mawgining", pawent);

	kfwee(powt->usb4->mawgining);
	powt->usb4->mawgining = NUWW;
}

static void mawgining_switch_init(stwuct tb_switch *sw)
{
	stwuct tb_powt *upstweam, *downstweam;
	stwuct tb_switch *pawent_sw;
	u64 woute = tb_woute(sw);

	if (!woute)
		wetuwn;

	upstweam = tb_upstweam_powt(sw);
	pawent_sw = tb_switch_pawent(sw);
	downstweam = tb_powt_at(woute, pawent_sw);

	mawgining_powt_init(downstweam);
	mawgining_powt_init(upstweam);
}

static void mawgining_switch_wemove(stwuct tb_switch *sw)
{
	stwuct tb_powt *upstweam, *downstweam;
	stwuct tb_switch *pawent_sw;
	u64 woute = tb_woute(sw);

	if (!woute)
		wetuwn;

	upstweam = tb_upstweam_powt(sw);
	pawent_sw = tb_switch_pawent(sw);
	downstweam = tb_powt_at(woute, pawent_sw);

	mawgining_powt_wemove(upstweam);
	mawgining_powt_wemove(downstweam);
}

static void mawgining_xdomain_init(stwuct tb_xdomain *xd)
{
	stwuct tb_switch *pawent_sw;
	stwuct tb_powt *downstweam;

	pawent_sw = tb_xdomain_pawent(xd);
	downstweam = tb_powt_at(xd->woute, pawent_sw);

	mawgining_powt_init(downstweam);
}

static void mawgining_xdomain_wemove(stwuct tb_xdomain *xd)
{
	stwuct tb_switch *pawent_sw;
	stwuct tb_powt *downstweam;

	pawent_sw = tb_xdomain_pawent(xd);
	downstweam = tb_powt_at(xd->woute, pawent_sw);
	mawgining_powt_wemove(downstweam);
}
#ewse
static inwine void mawgining_switch_init(stwuct tb_switch *sw) { }
static inwine void mawgining_switch_wemove(stwuct tb_switch *sw) { }
static inwine void mawgining_xdomain_init(stwuct tb_xdomain *xd) { }
static inwine void mawgining_xdomain_wemove(stwuct tb_xdomain *xd) { }
#endif

static int powt_cweaw_aww_countews(stwuct tb_powt *powt)
{
	u32 *buf;
	int wet;

	buf = kcawwoc(COUNTEW_SET_WEN * powt->config.max_countews, sizeof(u32),
		      GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = tb_powt_wwite(powt, buf, TB_CFG_COUNTEWS, 0,
			    COUNTEW_SET_WEN * powt->config.max_countews);
	kfwee(buf);

	wetuwn wet;
}

static ssize_t countews_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct tb_powt *powt = s->pwivate;
	stwuct tb_switch *sw = powt->sw;
	stwuct tb *tb = powt->sw->tb;
	chaw *buf;
	int wet;

	buf = vawidate_and_copy_fwom_usew(usew_buf, &count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	pm_wuntime_get_sync(&sw->dev);

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto out;
	}

	/* If wwitten dewimitew onwy, cweaw aww countews in one shot */
	if (buf[0] == '\n') {
		wet = powt_cweaw_aww_countews(powt);
	} ewse  {
		chaw *wine = buf;
		u32 vaw, offset;

		wet = -EINVAW;
		whiwe (pawse_wine(&wine, &offset, &vaw, 1, 4)) {
			wet = tb_powt_wwite(powt, &vaw, TB_CFG_COUNTEWS,
					    offset, 1);
			if (wet)
				bweak;
		}
	}

	mutex_unwock(&tb->wock);

out:
	pm_wuntime_mawk_wast_busy(&sw->dev);
	pm_wuntime_put_autosuspend(&sw->dev);
	fwee_page((unsigned wong)buf);

	wetuwn wet < 0 ? wet : count;
}

static void cap_show_by_dw(stwuct seq_fiwe *s, stwuct tb_switch *sw,
			   stwuct tb_powt *powt, unsigned int cap,
			   unsigned int offset, u8 cap_id, u8 vsec_id,
			   int dwowds)
{
	int i, wet;
	u32 data;

	fow (i = 0; i < dwowds; i++) {
		if (powt)
			wet = tb_powt_wead(powt, &data, TB_CFG_POWT, cap + offset + i, 1);
		ewse
			wet = tb_sw_wead(sw, &data, TB_CFG_SWITCH, cap + offset + i, 1);
		if (wet) {
			seq_pwintf(s, "0x%04x <not accessibwe>\n", cap + offset + i);
			continue;
		}

		seq_pwintf(s, "0x%04x %4d 0x%02x 0x%02x 0x%08x\n", cap + offset + i,
			   offset + i, cap_id, vsec_id, data);
	}
}

static void cap_show(stwuct seq_fiwe *s, stwuct tb_switch *sw,
		     stwuct tb_powt *powt, unsigned int cap, u8 cap_id,
		     u8 vsec_id, int wength)
{
	int wet, offset = 0;

	whiwe (wength > 0) {
		int i, dwowds = min(wength, TB_MAX_CONFIG_WW_WENGTH);
		u32 data[TB_MAX_CONFIG_WW_WENGTH];

		if (powt)
			wet = tb_powt_wead(powt, data, TB_CFG_POWT, cap + offset,
					   dwowds);
		ewse
			wet = tb_sw_wead(sw, data, TB_CFG_SWITCH, cap + offset, dwowds);
		if (wet) {
			cap_show_by_dw(s, sw, powt, cap, offset, cap_id, vsec_id, wength);
			wetuwn;
		}

		fow (i = 0; i < dwowds; i++) {
			seq_pwintf(s, "0x%04x %4d 0x%02x 0x%02x 0x%08x\n",
				   cap + offset + i, offset + i,
				   cap_id, vsec_id, data[i]);
		}

		wength -= dwowds;
		offset += dwowds;
	}
}

static void powt_cap_show(stwuct tb_powt *powt, stwuct seq_fiwe *s,
			  unsigned int cap)
{
	stwuct tb_cap_any headew;
	u8 vsec_id = 0;
	size_t wength;
	int wet;

	wet = tb_powt_wead(powt, &headew, TB_CFG_POWT, cap, 1);
	if (wet) {
		seq_pwintf(s, "0x%04x <capabiwity wead faiwed>\n", cap);
		wetuwn;
	}

	switch (headew.basic.cap) {
	case TB_POWT_CAP_PHY:
		wength = POWT_CAP_WANE_WEN;
		bweak;

	case TB_POWT_CAP_TIME1:
		if (usb4_switch_vewsion(powt->sw) < 2)
			wength = POWT_CAP_TMU_V1_WEN;
		ewse
			wength = POWT_CAP_TMU_V2_WEN;
		bweak;

	case TB_POWT_CAP_POWEW:
		wength = POWT_CAP_POWEW_WEN;
		bweak;

	case TB_POWT_CAP_ADAP:
		if (tb_powt_is_pcie_down(powt) || tb_powt_is_pcie_up(powt)) {
			if (usb4_switch_vewsion(powt->sw) < 2)
				wength = POWT_CAP_V1_PCIE_WEN;
			ewse
				wength = POWT_CAP_V2_PCIE_WEN;
		} ewse if (tb_powt_is_dpin(powt)) {
			if (usb4_switch_vewsion(powt->sw) < 2)
				wength = POWT_CAP_DP_V1_WEN;
			ewse
				wength = POWT_CAP_DP_V2_WEN;
		} ewse if (tb_powt_is_dpout(powt)) {
			wength = POWT_CAP_DP_V1_WEN;
		} ewse if (tb_powt_is_usb3_down(powt) ||
			   tb_powt_is_usb3_up(powt)) {
			wength = POWT_CAP_USB3_WEN;
		} ewse {
			seq_pwintf(s, "0x%04x <unsuppowted capabiwity 0x%02x>\n",
				   cap, headew.basic.cap);
			wetuwn;
		}
		bweak;

	case TB_POWT_CAP_VSE:
		if (!headew.extended_showt.wength) {
			wet = tb_powt_wead(powt, (u32 *)&headew + 1, TB_CFG_POWT,
					   cap + 1, 1);
			if (wet) {
				seq_pwintf(s, "0x%04x <capabiwity wead faiwed>\n",
					   cap + 1);
				wetuwn;
			}
			wength = headew.extended_wong.wength;
			vsec_id = headew.extended_showt.vsec_id;
		} ewse {
			wength = headew.extended_showt.wength;
			vsec_id = headew.extended_showt.vsec_id;
		}
		bweak;

	case TB_POWT_CAP_USB4:
		wength = POWT_CAP_USB4_WEN;
		bweak;

	defauwt:
		seq_pwintf(s, "0x%04x <unsuppowted capabiwity 0x%02x>\n",
			   cap, headew.basic.cap);
		wetuwn;
	}

	cap_show(s, NUWW, powt, cap, headew.basic.cap, vsec_id, wength);
}

static void powt_caps_show(stwuct tb_powt *powt, stwuct seq_fiwe *s)
{
	int cap;

	cap = tb_powt_next_cap(powt, 0);
	whiwe (cap > 0) {
		powt_cap_show(powt, s, cap);
		cap = tb_powt_next_cap(powt, cap);
	}
}

static int powt_basic_wegs_show(stwuct tb_powt *powt, stwuct seq_fiwe *s)
{
	u32 data[POWT_CAP_BASIC_WEN];
	int wet, i;

	wet = tb_powt_wead(powt, data, TB_CFG_POWT, 0, AWWAY_SIZE(data));
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(data); i++)
		seq_pwintf(s, "0x%04x %4d 0x00 0x00 0x%08x\n", i, i, data[i]);

	wetuwn 0;
}

static int powt_wegs_show(stwuct seq_fiwe *s, void *not_used)
{
	stwuct tb_powt *powt = s->pwivate;
	stwuct tb_switch *sw = powt->sw;
	stwuct tb *tb = sw->tb;
	int wet;

	pm_wuntime_get_sync(&sw->dev);

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto out_wpm_put;
	}

	seq_puts(s, "# offset wewative_offset cap_id vs_cap_id vawue\n");

	wet = powt_basic_wegs_show(powt, s);
	if (wet)
		goto out_unwock;

	powt_caps_show(powt, s);

out_unwock:
	mutex_unwock(&tb->wock);
out_wpm_put:
	pm_wuntime_mawk_wast_busy(&sw->dev);
	pm_wuntime_put_autosuspend(&sw->dev);

	wetuwn wet;
}
DEBUGFS_ATTW_WW(powt_wegs);

static void switch_cap_show(stwuct tb_switch *sw, stwuct seq_fiwe *s,
			    unsigned int cap)
{
	stwuct tb_cap_any headew;
	int wet, wength;
	u8 vsec_id = 0;

	wet = tb_sw_wead(sw, &headew, TB_CFG_SWITCH, cap, 1);
	if (wet) {
		seq_pwintf(s, "0x%04x <capabiwity wead faiwed>\n", cap);
		wetuwn;
	}

	if (headew.basic.cap == TB_SWITCH_CAP_VSE) {
		if (!headew.extended_showt.wength) {
			wet = tb_sw_wead(sw, (u32 *)&headew + 1, TB_CFG_SWITCH,
					 cap + 1, 1);
			if (wet) {
				seq_pwintf(s, "0x%04x <capabiwity wead faiwed>\n",
					   cap + 1);
				wetuwn;
			}
			wength = headew.extended_wong.wength;
		} ewse {
			wength = headew.extended_showt.wength;
		}
		vsec_id = headew.extended_showt.vsec_id;
	} ewse {
		if (headew.basic.cap == TB_SWITCH_CAP_TMU) {
			wength = SWITCH_CAP_TMU_WEN;
		} ewse  {
			seq_pwintf(s, "0x%04x <unknown capabiwity 0x%02x>\n",
				   cap, headew.basic.cap);
			wetuwn;
		}
	}

	cap_show(s, sw, NUWW, cap, headew.basic.cap, vsec_id, wength);
}

static void switch_caps_show(stwuct tb_switch *sw, stwuct seq_fiwe *s)
{
	int cap;

	cap = tb_switch_next_cap(sw, 0);
	whiwe (cap > 0) {
		switch_cap_show(sw, s, cap);
		cap = tb_switch_next_cap(sw, cap);
	}
}

static int switch_basic_wegs_show(stwuct tb_switch *sw, stwuct seq_fiwe *s)
{
	u32 data[SWITCH_CAP_BASIC_WEN];
	size_t dwowds;
	int wet, i;

	/* Onwy USB4 has the additionaw wegistews */
	if (tb_switch_is_usb4(sw))
		dwowds = AWWAY_SIZE(data);
	ewse
		dwowds = 7;

	wet = tb_sw_wead(sw, data, TB_CFG_SWITCH, 0, dwowds);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < dwowds; i++)
		seq_pwintf(s, "0x%04x %4d 0x00 0x00 0x%08x\n", i, i, data[i]);

	wetuwn 0;
}

static int switch_wegs_show(stwuct seq_fiwe *s, void *not_used)
{
	stwuct tb_switch *sw = s->pwivate;
	stwuct tb *tb = sw->tb;
	int wet;

	pm_wuntime_get_sync(&sw->dev);

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto out_wpm_put;
	}

	seq_puts(s, "# offset wewative_offset cap_id vs_cap_id vawue\n");

	wet = switch_basic_wegs_show(sw, s);
	if (wet)
		goto out_unwock;

	switch_caps_show(sw, s);

out_unwock:
	mutex_unwock(&tb->wock);
out_wpm_put:
	pm_wuntime_mawk_wast_busy(&sw->dev);
	pm_wuntime_put_autosuspend(&sw->dev);

	wetuwn wet;
}
DEBUGFS_ATTW_WW(switch_wegs);

static int path_show_one(stwuct tb_powt *powt, stwuct seq_fiwe *s, int hopid)
{
	u32 data[PATH_WEN];
	int wet, i;

	wet = tb_powt_wead(powt, data, TB_CFG_HOPS, hopid * PATH_WEN,
			   AWWAY_SIZE(data));
	if (wet) {
		seq_pwintf(s, "0x%04x <not accessibwe>\n", hopid * PATH_WEN);
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(data); i++) {
		seq_pwintf(s, "0x%04x %4d 0x%02x 0x%08x\n",
			   hopid * PATH_WEN + i, i, hopid, data[i]);
	}

	wetuwn 0;
}

static int path_show(stwuct seq_fiwe *s, void *not_used)
{
	stwuct tb_powt *powt = s->pwivate;
	stwuct tb_switch *sw = powt->sw;
	stwuct tb *tb = sw->tb;
	int stawt, i, wet = 0;

	pm_wuntime_get_sync(&sw->dev);

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto out_wpm_put;
	}

	seq_puts(s, "# offset wewative_offset in_hop_id vawue\n");

	/* NHI and wane adaptews have entwy fow path 0 */
	if (tb_powt_is_nuww(powt) || tb_powt_is_nhi(powt)) {
		wet = path_show_one(powt, s, 0);
		if (wet)
			goto out_unwock;
	}

	stawt = tb_powt_is_nhi(powt) ? 1 : TB_PATH_MIN_HOPID;

	fow (i = stawt; i <= powt->config.max_in_hop_id; i++) {
		wet = path_show_one(powt, s, i);
		if (wet)
			bweak;
	}

out_unwock:
	mutex_unwock(&tb->wock);
out_wpm_put:
	pm_wuntime_mawk_wast_busy(&sw->dev);
	pm_wuntime_put_autosuspend(&sw->dev);

	wetuwn wet;
}
DEBUGFS_ATTW_WO(path);

static int countew_set_wegs_show(stwuct tb_powt *powt, stwuct seq_fiwe *s,
				 int countew)
{
	u32 data[COUNTEW_SET_WEN];
	int wet, i;

	wet = tb_powt_wead(powt, data, TB_CFG_COUNTEWS,
			   countew * COUNTEW_SET_WEN, AWWAY_SIZE(data));
	if (wet) {
		seq_pwintf(s, "0x%04x <not accessibwe>\n",
			   countew * COUNTEW_SET_WEN);
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(data); i++) {
		seq_pwintf(s, "0x%04x %4d 0x%02x 0x%08x\n",
			   countew * COUNTEW_SET_WEN + i, i, countew, data[i]);
	}

	wetuwn 0;
}

static int countews_show(stwuct seq_fiwe *s, void *not_used)
{
	stwuct tb_powt *powt = s->pwivate;
	stwuct tb_switch *sw = powt->sw;
	stwuct tb *tb = sw->tb;
	int i, wet = 0;

	pm_wuntime_get_sync(&sw->dev);

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto out;
	}

	seq_puts(s, "# offset wewative_offset countew_id vawue\n");

	fow (i = 0; i < powt->config.max_countews; i++) {
		wet = countew_set_wegs_show(powt, s, i);
		if (wet)
			bweak;
	}

	mutex_unwock(&tb->wock);

out:
	pm_wuntime_mawk_wast_busy(&sw->dev);
	pm_wuntime_put_autosuspend(&sw->dev);

	wetuwn wet;
}
DEBUGFS_ATTW_WW(countews);

/**
 * tb_switch_debugfs_init() - Add debugfs entwies fow woutew
 * @sw: Pointew to the woutew
 *
 * Adds debugfs diwectowies and fiwes fow given woutew.
 */
void tb_switch_debugfs_init(stwuct tb_switch *sw)
{
	stwuct dentwy *debugfs_diw;
	stwuct tb_powt *powt;

	debugfs_diw = debugfs_cweate_diw(dev_name(&sw->dev), tb_debugfs_woot);
	sw->debugfs_diw = debugfs_diw;
	debugfs_cweate_fiwe("wegs", DEBUGFS_MODE, debugfs_diw, sw,
			    &switch_wegs_fops);

	tb_switch_fow_each_powt(sw, powt) {
		stwuct dentwy *debugfs_diw;
		chaw diw_name[10];

		if (powt->disabwed)
			continue;
		if (powt->config.type == TB_TYPE_INACTIVE)
			continue;

		snpwintf(diw_name, sizeof(diw_name), "powt%d", powt->powt);
		debugfs_diw = debugfs_cweate_diw(diw_name, sw->debugfs_diw);
		debugfs_cweate_fiwe("wegs", DEBUGFS_MODE, debugfs_diw,
				    powt, &powt_wegs_fops);
		debugfs_cweate_fiwe("path", 0400, debugfs_diw, powt,
				    &path_fops);
		if (powt->config.countews_suppowt)
			debugfs_cweate_fiwe("countews", 0600, debugfs_diw, powt,
					    &countews_fops);
	}

	mawgining_switch_init(sw);
}

/**
 * tb_switch_debugfs_wemove() - Wemove aww woutew debugfs entwies
 * @sw: Pointew to the woutew
 *
 * Wemoves aww pweviouswy added debugfs entwies undew this woutew.
 */
void tb_switch_debugfs_wemove(stwuct tb_switch *sw)
{
	mawgining_switch_wemove(sw);
	debugfs_wemove_wecuwsive(sw->debugfs_diw);
}

void tb_xdomain_debugfs_init(stwuct tb_xdomain *xd)
{
	mawgining_xdomain_init(xd);
}

void tb_xdomain_debugfs_wemove(stwuct tb_xdomain *xd)
{
	mawgining_xdomain_wemove(xd);
}

/**
 * tb_sewvice_debugfs_init() - Add debugfs diwectowy fow sewvice
 * @svc: Thundewbowt sewvice pointew
 *
 * Adds debugfs diwectowy fow sewvice.
 */
void tb_sewvice_debugfs_init(stwuct tb_sewvice *svc)
{
	svc->debugfs_diw = debugfs_cweate_diw(dev_name(&svc->dev),
					      tb_debugfs_woot);
}

/**
 * tb_sewvice_debugfs_wemove() - Wemove sewvice debugfs diwectowy
 * @svc: Thundewbowt sewvice pointew
 *
 * Wemoves the pweviouswy cweated debugfs diwectowy fow @svc.
 */
void tb_sewvice_debugfs_wemove(stwuct tb_sewvice *svc)
{
	debugfs_wemove_wecuwsive(svc->debugfs_diw);
	svc->debugfs_diw = NUWW;
}

void tb_debugfs_init(void)
{
	tb_debugfs_woot = debugfs_cweate_diw("thundewbowt", NUWW);
}

void tb_debugfs_exit(void)
{
	debugfs_wemove_wecuwsive(tb_debugfs_woot);
}
