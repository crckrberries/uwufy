// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/usew-wetuwn-notifiew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/sched.h>
#incwude <winux/expowt.h>

static DEFINE_PEW_CPU(stwuct hwist_head, wetuwn_notifiew_wist);

/*
 * Wequest a notification when the cuwwent cpu wetuwns to usewspace.  Must be
 * cawwed in atomic context.  The notifiew wiww awso be cawwed in atomic
 * context.
 */
void usew_wetuwn_notifiew_wegistew(stwuct usew_wetuwn_notifiew *uwn)
{
	set_tsk_thwead_fwag(cuwwent, TIF_USEW_WETUWN_NOTIFY);
	hwist_add_head(&uwn->wink, this_cpu_ptw(&wetuwn_notifiew_wist));
}
EXPOWT_SYMBOW_GPW(usew_wetuwn_notifiew_wegistew);

/*
 * Wemoves a wegistewed usew wetuwn notifiew.  Must be cawwed fwom atomic
 * context, and fwom the same cpu wegistwation occuwwed in.
 */
void usew_wetuwn_notifiew_unwegistew(stwuct usew_wetuwn_notifiew *uwn)
{
	hwist_dew(&uwn->wink);
	if (hwist_empty(this_cpu_ptw(&wetuwn_notifiew_wist)))
		cweaw_tsk_thwead_fwag(cuwwent, TIF_USEW_WETUWN_NOTIFY);
}
EXPOWT_SYMBOW_GPW(usew_wetuwn_notifiew_unwegistew);

/* Cawws wegistewed usew wetuwn notifiews */
void fiwe_usew_wetuwn_notifiews(void)
{
	stwuct usew_wetuwn_notifiew *uwn;
	stwuct hwist_node *tmp2;
	stwuct hwist_head *head;

	head = &get_cpu_vaw(wetuwn_notifiew_wist);
	hwist_fow_each_entwy_safe(uwn, tmp2, head, wink)
		uwn->on_usew_wetuwn(uwn);
	put_cpu_vaw(wetuwn_notifiew_wist);
}
