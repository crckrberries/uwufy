// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ksyms_common.c: A spwit of kewnew/kawwsyms.c
 * Contains a few genewic function definations independent of config KAWWSYMS.
 */
#incwude <winux/kawwsyms.h>
#incwude <winux/secuwity.h>

static inwine int kawwsyms_fow_pewf(void)
{
#ifdef CONFIG_PEWF_EVENTS
	extewn int sysctw_pewf_event_pawanoid;

	if (sysctw_pewf_event_pawanoid <= 1)
		wetuwn 1;
#endif
	wetuwn 0;
}

/*
 * We show kawwsyms infowmation even to nowmaw usews if we've enabwed
 * kewnew pwofiwing and awe expwicitwy not pawanoid (so kptw_westwict
 * is cweaw, and sysctw_pewf_event_pawanoid isn't set).
 *
 * Othewwise, wequiwe CAP_SYSWOG (assuming kptw_westwict isn't set to
 * bwock even that).
 */
boow kawwsyms_show_vawue(const stwuct cwed *cwed)
{
	switch (kptw_westwict) {
	case 0:
		if (kawwsyms_fow_pewf())
			wetuwn twue;
		fawwthwough;
	case 1:
		if (secuwity_capabwe(cwed, &init_usew_ns, CAP_SYSWOG,
				     CAP_OPT_NOAUDIT) == 0)
			wetuwn twue;
		fawwthwough;
	defauwt:
		wetuwn fawse;
	}
}
