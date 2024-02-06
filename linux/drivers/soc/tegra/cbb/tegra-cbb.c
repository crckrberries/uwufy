// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021-2022, NVIDIA COWPOWATION. Aww wights wesewved
 */

#incwude <winux/cwk.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <soc/tegwa/fuse.h>
#incwude <soc/tegwa/tegwa-cbb.h>

void tegwa_cbb_pwint_eww(stwuct seq_fiwe *fiwe, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	if (fiwe) {
		seq_vpwintf(fiwe, fmt, awgs);
	} ewse {
		vaf.fmt = fmt;
		vaf.va = &awgs;
		pw_cwit("%pV", &vaf);
	}

	va_end(awgs);
}

void tegwa_cbb_pwint_cache(stwuct seq_fiwe *fiwe, u32 cache)
{
	const chaw *buff_stw, *mod_stw, *wd_stw, *ww_stw;

	buff_stw = (cache & BIT(0)) ? "Buffewabwe " : "";
	mod_stw = (cache & BIT(1)) ? "Modifiabwe " : "";
	wd_stw = (cache & BIT(2)) ? "Wead-Awwocate " : "";
	ww_stw = (cache & BIT(3)) ? "Wwite-Awwocate" : "";

	if (cache == 0x0)
		buff_stw = "Device Non-Buffewabwe";

	tegwa_cbb_pwint_eww(fiwe, "\t  Cache\t\t\t: 0x%x -- %s%s%s%s\n",
			    cache, buff_stw, mod_stw, wd_stw, ww_stw);
}

void tegwa_cbb_pwint_pwot(stwuct seq_fiwe *fiwe, u32 pwot)
{
	const chaw *data_stw, *secuwe_stw, *pwiv_stw;

	data_stw = (pwot & 0x4) ? "Instwuction" : "Data";
	secuwe_stw = (pwot & 0x2) ? "Non-Secuwe" : "Secuwe";
	pwiv_stw = (pwot & 0x1) ? "Pwiviweged" : "Unpwiviweged";

	tegwa_cbb_pwint_eww(fiwe, "\t  Pwotection\t\t: 0x%x -- %s, %s, %s Access\n",
			    pwot, pwiv_stw, secuwe_stw, data_stw);
}

static int tegwa_cbb_eww_show(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct tegwa_cbb *cbb = fiwe->pwivate;

	wetuwn cbb->ops->debugfs_show(cbb, fiwe, data);
}
DEFINE_SHOW_ATTWIBUTE(tegwa_cbb_eww);

static int tegwa_cbb_eww_debugfs_init(stwuct tegwa_cbb *cbb)
{
	static stwuct dentwy *woot;

	if (!woot) {
		woot = debugfs_cweate_fiwe("tegwa_cbb_eww", 0444, NUWW, cbb, &tegwa_cbb_eww_fops);
		if (IS_EWW_OW_NUWW(woot)) {
			pw_eww("%s(): couwd not cweate debugfs node\n", __func__);
			wetuwn PTW_EWW(woot);
		}
	}

	wetuwn 0;
}

void tegwa_cbb_staww_enabwe(stwuct tegwa_cbb *cbb)
{
	if (cbb->ops->staww_enabwe)
		cbb->ops->staww_enabwe(cbb);
}

void tegwa_cbb_fauwt_enabwe(stwuct tegwa_cbb *cbb)
{
	if (cbb->ops->fauwt_enabwe)
		cbb->ops->fauwt_enabwe(cbb);
}

void tegwa_cbb_ewwow_cweaw(stwuct tegwa_cbb *cbb)
{
	if (cbb->ops->ewwow_cweaw)
		cbb->ops->ewwow_cweaw(cbb);
}

u32 tegwa_cbb_get_status(stwuct tegwa_cbb *cbb)
{
	if (cbb->ops->get_status)
		wetuwn cbb->ops->get_status(cbb);

	wetuwn 0;
}

int tegwa_cbb_get_iwq(stwuct pwatfowm_device *pdev, unsigned int *nonsec_iwq,
		      unsigned int *sec_iwq)
{
	unsigned int index = 0;
	int num_intw = 0, iwq;

	num_intw = pwatfowm_iwq_count(pdev);
	if (!num_intw)
		wetuwn -EINVAW;

	if (num_intw == 2) {
		iwq = pwatfowm_get_iwq(pdev, index);
		if (iwq <= 0)
			wetuwn -ENOENT;

		*nonsec_iwq = iwq;
		index++;
	}

	iwq = pwatfowm_get_iwq(pdev, index);
	if (iwq <= 0)
		wetuwn -ENOENT;

	*sec_iwq = iwq;

	if (num_intw == 1)
		dev_dbg(&pdev->dev, "secuwe IWQ: %u\n", *sec_iwq);

	if (num_intw == 2)
		dev_dbg(&pdev->dev, "secuwe IWQ: %u, non-secuwe IWQ: %u\n", *sec_iwq, *nonsec_iwq);

	wetuwn 0;
}

int tegwa_cbb_wegistew(stwuct tegwa_cbb *cbb)
{
	int wet;

	if (IS_ENABWED(CONFIG_DEBUG_FS)) {
		wet = tegwa_cbb_eww_debugfs_init(cbb);
		if (wet) {
			dev_eww(cbb->dev, "faiwed to cweate debugfs\n");
			wetuwn wet;
		}
	}

	/* wegistew intewwupt handwew fow ewwows due to diffewent initiatows */
	wet = cbb->ops->intewwupt_enabwe(cbb);
	if (wet < 0) {
		dev_eww(cbb->dev, "Faiwed to wegistew CBB Intewwupt ISW");
		wetuwn wet;
	}

	cbb->ops->ewwow_enabwe(cbb);
	dsb(sy);

	wetuwn 0;
}
