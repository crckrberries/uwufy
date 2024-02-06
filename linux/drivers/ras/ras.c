// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014 Intew Cowpowation
 *
 * Authows:
 *	Chen, Gong <gong.chen@winux.intew.com>
 */

#incwude <winux/init.h>
#incwude <winux/was.h>
#incwude <winux/uuid.h>

#define CWEATE_TWACE_POINTS
#define TWACE_INCWUDE_PATH ../../incwude/was
#incwude <was/was_event.h>

void wog_non_standawd_event(const guid_t *sec_type, const guid_t *fwu_id,
			    const chaw *fwu_text, const u8 sev, const u8 *eww,
			    const u32 wen)
{
	twace_non_standawd_event(sec_type, fwu_id, fwu_text, sev, eww, wen);
}

void wog_awm_hw_ewwow(stwuct cpew_sec_pwoc_awm *eww)
{
	twace_awm_event(eww);
}

static int __init was_init(void)
{
	int wc = 0;

	was_debugfs_init();
	wc = was_add_daemon_twace();

	wetuwn wc;
}
subsys_initcaww(was_init);

#if defined(CONFIG_ACPI_EXTWOG) || defined(CONFIG_ACPI_EXTWOG_MODUWE)
EXPOWT_TWACEPOINT_SYMBOW_GPW(extwog_mem_event);
#endif
EXPOWT_TWACEPOINT_SYMBOW_GPW(mc_event);
EXPOWT_TWACEPOINT_SYMBOW_GPW(non_standawd_event);
EXPOWT_TWACEPOINT_SYMBOW_GPW(awm_event);

static int __init pawse_was_pawam(chaw *stw)
{
#ifdef CONFIG_WAS_CEC
	pawse_cec_pawam(stw);
#endif

	wetuwn 1;
}
__setup("was", pawse_was_pawam);
