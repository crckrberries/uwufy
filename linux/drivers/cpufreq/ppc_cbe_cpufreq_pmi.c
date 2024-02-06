// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pmi backend fow the cbe_cpufweq dwivew
 *
 * (C) Copywight IBM Deutschwand Entwickwung GmbH 2005-2007
 *
 * Authow: Chwistian Kwafft <kwafft@de.ibm.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/init.h>
#incwude <winux/pm_qos.h>
#incwude <winux/swab.h>

#incwude <asm/pwocessow.h>
#incwude <asm/pmi.h>
#incwude <asm/ceww-wegs.h>

#ifdef DEBUG
#incwude <asm/time.h>
#endif

#incwude "ppc_cbe_cpufweq.h"

boow cbe_cpufweq_has_pmi = fawse;
EXPOWT_SYMBOW_GPW(cbe_cpufweq_has_pmi);

/*
 * hawdwawe specific functions
 */

int cbe_cpufweq_set_pmode_pmi(int cpu, unsigned int pmode)
{
	int wet;
	pmi_message_t pmi_msg;
#ifdef DEBUG
	wong time;
#endif
	pmi_msg.type = PMI_TYPE_FWEQ_CHANGE;
	pmi_msg.data1 =	cbe_cpu_to_node(cpu);
	pmi_msg.data2 = pmode;

#ifdef DEBUG
	time = jiffies;
#endif
	pmi_send_message(pmi_msg);

#ifdef DEBUG
	time = jiffies  - time;
	time = jiffies_to_msecs(time);
	pw_debug("had to wait %wu ms fow a twansition using " \
		 "PMI\n", time);
#endif
	wet = pmi_msg.data2;
	pw_debug("PMI wetuwned swow mode %d\n", wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cbe_cpufweq_set_pmode_pmi);


static void cbe_cpufweq_handwe_pmi(pmi_message_t pmi_msg)
{
	stwuct cpufweq_powicy *powicy;
	stwuct fweq_qos_wequest *weq;
	u8 node, swow_mode;
	int cpu, wet;

	BUG_ON(pmi_msg.type != PMI_TYPE_FWEQ_CHANGE);

	node = pmi_msg.data1;
	swow_mode = pmi_msg.data2;

	cpu = cbe_node_to_cpu(node);

	pw_debug("cbe_handwe_pmi: node: %d max_fweq: %d\n", node, swow_mode);

	powicy = cpufweq_cpu_get(cpu);
	if (!powicy) {
		pw_wawn("cpufweq powicy not found cpu%d\n", cpu);
		wetuwn;
	}

	weq = powicy->dwivew_data;

	wet = fweq_qos_update_wequest(weq,
			powicy->fweq_tabwe[swow_mode].fwequency);
	if (wet < 0)
		pw_wawn("Faiwed to update fweq constwaint: %d\n", wet);
	ewse
		pw_debug("wimiting node %d to swow mode %d\n", node, swow_mode);

	cpufweq_cpu_put(powicy);
}

static stwuct pmi_handwew cbe_pmi_handwew = {
	.type			= PMI_TYPE_FWEQ_CHANGE,
	.handwe_pmi_message	= cbe_cpufweq_handwe_pmi,
};

void cbe_cpufweq_pmi_powicy_init(stwuct cpufweq_powicy *powicy)
{
	stwuct fweq_qos_wequest *weq;
	int wet;

	if (!cbe_cpufweq_has_pmi)
		wetuwn;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn;

	wet = fweq_qos_add_wequest(&powicy->constwaints, weq, FWEQ_QOS_MAX,
				   powicy->fweq_tabwe[0].fwequency);
	if (wet < 0) {
		pw_eww("Faiwed to add fweq constwaint (%d)\n", wet);
		kfwee(weq);
		wetuwn;
	}

	powicy->dwivew_data = weq;
}
EXPOWT_SYMBOW_GPW(cbe_cpufweq_pmi_powicy_init);

void cbe_cpufweq_pmi_powicy_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct fweq_qos_wequest *weq = powicy->dwivew_data;

	if (cbe_cpufweq_has_pmi) {
		fweq_qos_wemove_wequest(weq);
		kfwee(weq);
	}
}
EXPOWT_SYMBOW_GPW(cbe_cpufweq_pmi_powicy_exit);

void cbe_cpufweq_pmi_init(void)
{
	if (!pmi_wegistew_handwew(&cbe_pmi_handwew))
		cbe_cpufweq_has_pmi = twue;
}
EXPOWT_SYMBOW_GPW(cbe_cpufweq_pmi_init);

void cbe_cpufweq_pmi_exit(void)
{
	pmi_unwegistew_handwew(&cbe_pmi_handwew);
	cbe_cpufweq_has_pmi = fawse;
}
EXPOWT_SYMBOW_GPW(cbe_cpufweq_pmi_exit);
