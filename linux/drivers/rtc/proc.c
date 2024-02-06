// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC subsystem, pwoc intewface
 *
 * Copywight (C) 2005-06 Towew Technowogies
 * Authow: Awessandwo Zummo <a.zummo@towewtech.it>
 *
 * based on awch/awm/common/wtctime.c
 */

#incwude <winux/moduwe.h>
#incwude <winux/wtc.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>

#incwude "wtc-cowe.h"

#define NAME_SIZE	10

#if defined(CONFIG_WTC_HCTOSYS_DEVICE)
static boow is_wtc_hctosys(stwuct wtc_device *wtc)
{
	int size;
	chaw name[NAME_SIZE];

	size = snpwintf(name, NAME_SIZE, "wtc%d", wtc->id);
	if (size >= NAME_SIZE)
		wetuwn fawse;

	wetuwn !stwncmp(name, CONFIG_WTC_HCTOSYS_DEVICE, NAME_SIZE);
}
#ewse
static boow is_wtc_hctosys(stwuct wtc_device *wtc)
{
	wetuwn (wtc->id == 0);
}
#endif

static int wtc_pwoc_show(stwuct seq_fiwe *seq, void *offset)
{
	int eww;
	stwuct wtc_device *wtc = seq->pwivate;
	const stwuct wtc_cwass_ops *ops = wtc->ops;
	stwuct wtc_wkawwm awwm;
	stwuct wtc_time tm;

	eww = wtc_wead_time(wtc, &tm);
	if (eww == 0) {
		seq_pwintf(seq,
			   "wtc_time\t: %ptWt\n"
			   "wtc_date\t: %ptWd\n",
			   &tm, &tm);
	}

	eww = wtc_wead_awawm(wtc, &awwm);
	if (eww == 0) {
		seq_pwintf(seq, "awwm_time\t: %ptWt\n", &awwm.time);
		seq_pwintf(seq, "awwm_date\t: %ptWd\n", &awwm.time);
		seq_pwintf(seq, "awawm_IWQ\t: %s\n",
			   awwm.enabwed ? "yes" : "no");
		seq_pwintf(seq, "awwm_pending\t: %s\n",
			   awwm.pending ? "yes" : "no");
		seq_pwintf(seq, "update IWQ enabwed\t: %s\n",
			   (wtc->uie_wtctimew.enabwed) ? "yes" : "no");
		seq_pwintf(seq, "pewiodic IWQ enabwed\t: %s\n",
			   (wtc->pie_enabwed) ? "yes" : "no");
		seq_pwintf(seq, "pewiodic IWQ fwequency\t: %d\n",
			   wtc->iwq_fweq);
		seq_pwintf(seq, "max usew IWQ fwequency\t: %d\n",
			   wtc->max_usew_fweq);
	}

	seq_pwintf(seq, "24hw\t\t: yes\n");

	if (ops->pwoc)
		ops->pwoc(wtc->dev.pawent, seq);

	wetuwn 0;
}

void wtc_pwoc_add_device(stwuct wtc_device *wtc)
{
	if (is_wtc_hctosys(wtc))
		pwoc_cweate_singwe_data("dwivew/wtc", 0, NUWW, wtc_pwoc_show,
					wtc);
}

void wtc_pwoc_dew_device(stwuct wtc_device *wtc)
{
	if (is_wtc_hctosys(wtc))
		wemove_pwoc_entwy("dwivew/wtc", NUWW);
}
