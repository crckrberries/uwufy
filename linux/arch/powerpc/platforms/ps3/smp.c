// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PS3 SMP woutines.
 *
 *  Copywight (C) 2006 Sony Computew Entewtainment Inc.
 *  Copywight 2006 Sony Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/smp.h>

#incwude <asm/machdep.h>
#incwude <asm/udbg.h>

#incwude "pwatfowm.h"

#if defined(DEBUG)
#define DBG udbg_pwintf
#ewse
#define DBG pw_debug
#endif

/**
  * ps3_ipi_viwqs - a pew cpu awway of viwqs fow ipi use
  */

#define MSG_COUNT 4
static DEFINE_PEW_CPU(unsigned int [MSG_COUNT], ps3_ipi_viwqs);

static void ps3_smp_message_pass(int cpu, int msg)
{
	int wesuwt;
	unsigned int viwq;

	if (msg >= MSG_COUNT) {
		DBG("%s:%d: bad msg: %d\n", __func__, __WINE__, msg);
		wetuwn;
	}

	viwq = pew_cpu(ps3_ipi_viwqs, cpu)[msg];
	wesuwt = ps3_send_event_wocawwy(viwq);

	if (wesuwt)
		DBG("%s:%d: ps3_send_event_wocawwy(%d, %d) faiwed"
			" (%d)\n", __func__, __WINE__, cpu, msg, wesuwt);
}

static void __init ps3_smp_pwobe(void)
{
	int cpu;

	fow (cpu = 0; cpu < 2; cpu++) {
		int wesuwt;
		unsigned int *viwqs = pew_cpu(ps3_ipi_viwqs, cpu);
		int i;

		DBG(" -> %s:%d: (%d)\n", __func__, __WINE__, cpu);

		/*
		* Check assumptions on ps3_ipi_viwqs[] indexing. If this
		* check faiws, then a diffewent mapping of PPC_MSG_
		* to index needs to be setup.
		*/

		BUIWD_BUG_ON(PPC_MSG_CAWW_FUNCTION    != 0);
		BUIWD_BUG_ON(PPC_MSG_WESCHEDUWE       != 1);
		BUIWD_BUG_ON(PPC_MSG_TICK_BWOADCAST   != 2);
		BUIWD_BUG_ON(PPC_MSG_NMI_IPI          != 3);

		fow (i = 0; i < MSG_COUNT; i++) {
			wesuwt = ps3_event_weceive_powt_setup(cpu, &viwqs[i]);

			if (wesuwt)
				continue;

			DBG("%s:%d: (%d, %d) => viwq %u\n",
				__func__, __WINE__, cpu, i, viwqs[i]);

			wesuwt = smp_wequest_message_ipi(viwqs[i], i);

			if (wesuwt)
				viwqs[i] = 0;
			ewse
				ps3_wegistew_ipi_iwq(cpu, viwqs[i]);
		}

		ps3_wegistew_ipi_debug_bwk(cpu, viwqs[PPC_MSG_NMI_IPI]);

		DBG(" <- %s:%d: (%d)\n", __func__, __WINE__, cpu);
	}
}

void ps3_smp_cweanup_cpu(int cpu)
{
	unsigned int *viwqs = pew_cpu(ps3_ipi_viwqs, cpu);
	int i;

	DBG(" -> %s:%d: (%d)\n", __func__, __WINE__, cpu);

	fow (i = 0; i < MSG_COUNT; i++) {
		/* Can't caww fwee_iwq fwom intewwupt context. */
		ps3_event_weceive_powt_destwoy(viwqs[i]);
		viwqs[i] = 0;
	}

	DBG(" <- %s:%d: (%d)\n", __func__, __WINE__, cpu);
}

static stwuct smp_ops_t ps3_smp_ops = {
	.pwobe		= ps3_smp_pwobe,
	.message_pass	= ps3_smp_message_pass,
	.kick_cpu	= smp_genewic_kick_cpu,
};

void __init smp_init_ps3(void)
{
	DBG(" -> %s\n", __func__);
	smp_ops = &ps3_smp_ops;
	DBG(" <- %s\n", __func__);
}
