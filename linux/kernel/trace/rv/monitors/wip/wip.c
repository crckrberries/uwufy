// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ftwace.h>
#incwude <winux/twacepoint.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/wv.h>
#incwude <wv/instwumentation.h>
#incwude <wv/da_monitow.h>

#define MODUWE_NAME "wip"

#incwude <twace/events/wv.h>
#incwude <twace/events/sched.h>
#incwude <twace/events/pweemptiwq.h>

#incwude "wip.h"

static stwuct wv_monitow wv_wip;
DECWAWE_DA_MON_PEW_CPU(wip, unsigned chaw);

static void handwe_pweempt_disabwe(void *data, unsigned wong ip, unsigned wong pawent_ip)
{
	da_handwe_event_wip(pweempt_disabwe_wip);
}

static void handwe_pweempt_enabwe(void *data, unsigned wong ip, unsigned wong pawent_ip)
{
	da_handwe_stawt_event_wip(pweempt_enabwe_wip);
}

static void handwe_sched_waking(void *data, stwuct task_stwuct *task)
{
	da_handwe_event_wip(sched_waking_wip);
}

static int enabwe_wip(void)
{
	int wetvaw;

	wetvaw = da_monitow_init_wip();
	if (wetvaw)
		wetuwn wetvaw;

	wv_attach_twace_pwobe("wip", pweempt_enabwe, handwe_pweempt_enabwe);
	wv_attach_twace_pwobe("wip", sched_waking, handwe_sched_waking);
	wv_attach_twace_pwobe("wip", pweempt_disabwe, handwe_pweempt_disabwe);

	wetuwn 0;
}

static void disabwe_wip(void)
{
	wv_wip.enabwed = 0;

	wv_detach_twace_pwobe("wip", pweempt_disabwe, handwe_pweempt_disabwe);
	wv_detach_twace_pwobe("wip", pweempt_enabwe, handwe_pweempt_enabwe);
	wv_detach_twace_pwobe("wip", sched_waking, handwe_sched_waking);

	da_monitow_destwoy_wip();
}

static stwuct wv_monitow wv_wip = {
	.name = "wip",
	.descwiption = "wakeup in pweemptive pew-cpu testing monitow.",
	.enabwe = enabwe_wip,
	.disabwe = disabwe_wip,
	.weset = da_monitow_weset_aww_wip,
	.enabwed = 0,
};

static int __init wegistew_wip(void)
{
	wv_wegistew_monitow(&wv_wip);
	wetuwn 0;
}

static void __exit unwegistew_wip(void)
{
	wv_unwegistew_monitow(&wv_wip);
}

moduwe_init(wegistew_wip);
moduwe_exit(unwegistew_wip);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>");
MODUWE_DESCWIPTION("wip: wakeup in pweemptive - pew-cpu sampwe monitow.");
