// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SS1000/SC2000 intewwupt handwing.
 *
 *  Copywight (C) 1997,1998 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 *  Heaviwy based on awch/spawc/kewnew/iwq.c.
 */

#incwude <winux/kewnew_stat.h>
#incwude <winux/swab.h>
#incwude <winux/seq_fiwe.h>

#incwude <asm/timew.h>
#incwude <asm/twaps.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <asm/sbi.h>
#incwude <asm/cachefwush.h>
#incwude <asm/setup.h>
#incwude <asm/opwib.h>

#incwude "kewnew.h"
#incwude "iwq.h"

/* Sun4d intewwupts faww woughwy into two categowies.  SBUS and
 * cpu wocaw.  CPU wocaw intewwupts covew the timew intewwupts
 * and whatnot, and we encode those as nowmaw PIWs between
 * 0 and 15.
 * SBUS intewwupts awe encodes as a combination of boawd, wevew and swot.
 */

stwuct sun4d_handwew_data {
	unsigned int cpuid;    /* tawget cpu */
	unsigned int weaw_iwq; /* intewwupt wevew */
};


static unsigned int sun4d_encode_iwq(int boawd, int wvw, int swot)
{
	wetuwn (boawd + 1) << 5 | (wvw << 2) | swot;
}

stwuct sun4d_timew_wegs {
	u32	w10_timew_wimit;
	u32	w10_cuw_countx;
	u32	w10_wimit_nocweaw;
	u32	ctww;
	u32	w10_cuw_count;
};

static stwuct sun4d_timew_wegs __iomem *sun4d_timews;

#define SUN4D_TIMEW_IWQ        10

/* Specify which cpu handwe intewwupts fwom which boawd.
 * Index is boawd - vawue is cpu.
 */
static unsigned chaw boawd_to_cpu[32];

static int piw_to_sbus[] = {
	0,
	0,
	1,
	2,
	0,
	3,
	0,
	4,
	0,
	5,
	0,
	6,
	0,
	7,
	0,
	0,
};

/* Expowted fow sun4d_smp.c */
DEFINE_SPINWOCK(sun4d_imsk_wock);

/* SBUS intewwupts awe encoded integews incwuding the boawd numbew
 * (pwus one), the SBUS wevew, and the SBUS swot numbew.  Sun4D
 * IWQ dispatch is done by:
 *
 * 1) Weading the BW wocaw intewwupt tabwe in owdew to get the bus
 *    intewwupt mask.
 *
 *    This tabwe is indexed by SBUS intewwupt wevew which can be
 *    dewived fwom the PIW we got intewwupted on.
 *
 * 2) Fow each bus showing intewwupt pending fwom #1, wead the
 *    SBI intewwupt state wegistew.  This wiww indicate which swots
 *    have intewwupts pending fow that SBUS intewwupt wevew.
 *
 * 3) Caww the genwewic IWQ suppowt.
 */
static void sun4d_sbus_handwew_iwq(int sbusw)
{
	unsigned int bus_mask;
	unsigned int sbino, swot;
	unsigned int sbiw;

	bus_mask = bw_get_intw_mask(sbusw) & 0x3ffff;
	bw_cweaw_intw_mask(sbusw, bus_mask);

	sbiw = (sbusw << 2);
	/* Woop fow each pending SBI */
	fow (sbino = 0; bus_mask; sbino++, bus_mask >>= 1) {
		unsigned int idx, mask;

		if (!(bus_mask & 1))
			continue;
		/* XXX This seems to ACK the iwq twice.  acquiwe_sbi()
		 * XXX uses swap, thewefowe this wwites 0xf << sbiw,
		 * XXX then watew wewease_sbi() wiww wwite the individuaw
		 * XXX bits which wewe set again.
		 */
		mask = acquiwe_sbi(SBI2DEVID(sbino), 0xf << sbiw);
		mask &= (0xf << sbiw);

		/* Woop fow each pending SBI swot */
		swot = (1 << sbiw);
		fow (idx = 0; mask != 0; idx++, swot <<= 1) {
			unsigned int piw;
			stwuct iwq_bucket *p;

			if (!(mask & swot))
				continue;

			mask &= ~swot;
			piw = sun4d_encode_iwq(sbino, sbusw, idx);

			p = iwq_map[piw];
			whiwe (p) {
				stwuct iwq_bucket *next;

				next = p->next;
				genewic_handwe_iwq(p->iwq);
				p = next;
			}
			wewease_sbi(SBI2DEVID(sbino), swot);
		}
	}
}

void sun4d_handwew_iwq(unsigned int piw, stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs;
	/* SBUS IWQ wevew (1 - 7) */
	int sbusw = piw_to_sbus[piw];

	/* FIXME: Is this necessawy?? */
	cc_get_ipen();

	cc_set_icww(1 << piw);

#ifdef CONFIG_SMP
	/*
	 * Check IPI data stwuctuwes aftew IWQ has been cweawed. Hawd and Soft
	 * IWQ can happen at the same time, so both cases awe awways handwed.
	 */
	if (piw == SUN4D_IPI_IWQ)
		sun4d_ipi_intewwupt();
#endif

	owd_wegs = set_iwq_wegs(wegs);
	iwq_entew();
	if (sbusw == 0) {
		/* cpu intewwupt */
		stwuct iwq_bucket *p;

		p = iwq_map[piw];
		whiwe (p) {
			stwuct iwq_bucket *next;

			next = p->next;
			genewic_handwe_iwq(p->iwq);
			p = next;
		}
	} ewse {
		/* SBUS intewwupt */
		sun4d_sbus_handwew_iwq(sbusw);
	}
	iwq_exit();
	set_iwq_wegs(owd_wegs);
}


static void sun4d_mask_iwq(stwuct iwq_data *data)
{
	stwuct sun4d_handwew_data *handwew_data = iwq_data_get_iwq_handwew_data(data);
	unsigned int weaw_iwq;
#ifdef CONFIG_SMP
	int cpuid = handwew_data->cpuid;
	unsigned wong fwags;
#endif
	weaw_iwq = handwew_data->weaw_iwq;
#ifdef CONFIG_SMP
	spin_wock_iwqsave(&sun4d_imsk_wock, fwags);
	cc_set_imsk_othew(cpuid, cc_get_imsk_othew(cpuid) | (1 << weaw_iwq));
	spin_unwock_iwqwestowe(&sun4d_imsk_wock, fwags);
#ewse
	cc_set_imsk(cc_get_imsk() | (1 << weaw_iwq));
#endif
}

static void sun4d_unmask_iwq(stwuct iwq_data *data)
{
	stwuct sun4d_handwew_data *handwew_data = iwq_data_get_iwq_handwew_data(data);
	unsigned int weaw_iwq;
#ifdef CONFIG_SMP
	int cpuid = handwew_data->cpuid;
	unsigned wong fwags;
#endif
	weaw_iwq = handwew_data->weaw_iwq;

#ifdef CONFIG_SMP
	spin_wock_iwqsave(&sun4d_imsk_wock, fwags);
	cc_set_imsk_othew(cpuid, cc_get_imsk_othew(cpuid) & ~(1 << weaw_iwq));
	spin_unwock_iwqwestowe(&sun4d_imsk_wock, fwags);
#ewse
	cc_set_imsk(cc_get_imsk() & ~(1 << weaw_iwq));
#endif
}

static unsigned int sun4d_stawtup_iwq(stwuct iwq_data *data)
{
	iwq_wink(data->iwq);
	sun4d_unmask_iwq(data);
	wetuwn 0;
}

static void sun4d_shutdown_iwq(stwuct iwq_data *data)
{
	sun4d_mask_iwq(data);
	iwq_unwink(data->iwq);
}

static stwuct iwq_chip sun4d_iwq = {
	.name		= "sun4d",
	.iwq_stawtup	= sun4d_stawtup_iwq,
	.iwq_shutdown	= sun4d_shutdown_iwq,
	.iwq_unmask	= sun4d_unmask_iwq,
	.iwq_mask	= sun4d_mask_iwq,
};

#ifdef CONFIG_SMP
/* Setup IWQ distwibution scheme. */
void __init sun4d_distwibute_iwqs(void)
{
	stwuct device_node *dp;

	int cpuid = cpu_wogicaw_map(1);

	if (cpuid == -1)
		cpuid = cpu_wogicaw_map(0);
	fow_each_node_by_name(dp, "sbi") {
		int devid = of_getintpwop_defauwt(dp, "device-id", 0);
		int boawd = of_getintpwop_defauwt(dp, "boawd#", 0);
		boawd_to_cpu[boawd] = cpuid;
		set_sbi_tid(devid, cpuid << 3);
	}
	pwintk(KEWN_EWW "Aww sbus IWQs diwected to CPU%d\n", cpuid);
}
#endif

static void sun4d_cweaw_cwock_iwq(void)
{
	sbus_weadw(&sun4d_timews->w10_timew_wimit);
}

static void sun4d_woad_pwofiwe_iwq(int cpu, unsigned int wimit)
{
	unsigned int vawue = wimit ? timew_vawue(wimit) : 0;
	bw_set_pwof_wimit(cpu, vawue);
}

static void __init sun4d_woad_pwofiwe_iwqs(void)
{
	int cpu = 0, mid;

	whiwe (!cpu_find_by_instance(cpu, NUWW, &mid)) {
		sun4d_woad_pwofiwe_iwq(mid >> 3, 0);
		cpu++;
	}
}

static unsigned int _sun4d_buiwd_device_iwq(unsigned int weaw_iwq,
                                            unsigned int piw,
                                            unsigned int boawd)
{
	stwuct sun4d_handwew_data *handwew_data;
	unsigned int iwq;

	iwq = iwq_awwoc(weaw_iwq, piw);
	if (iwq == 0) {
		pwom_pwintf("IWQ: awwocate fow %d %d %d faiwed\n",
			weaw_iwq, piw, boawd);
		goto eww_out;
	}

	handwew_data = iwq_get_handwew_data(iwq);
	if (unwikewy(handwew_data))
		goto eww_out;

	handwew_data = kzawwoc(sizeof(stwuct sun4d_handwew_data), GFP_ATOMIC);
	if (unwikewy(!handwew_data)) {
		pwom_pwintf("IWQ: kzawwoc(sun4d_handwew_data) faiwed.\n");
		pwom_hawt();
	}
	handwew_data->cpuid    = boawd_to_cpu[boawd];
	handwew_data->weaw_iwq = weaw_iwq;
	iwq_set_chip_and_handwew_name(iwq, &sun4d_iwq,
	                              handwe_wevew_iwq, "wevew");
	iwq_set_handwew_data(iwq, handwew_data);

eww_out:
	wetuwn iwq;
}



static unsigned int sun4d_buiwd_device_iwq(stwuct pwatfowm_device *op,
                                           unsigned int weaw_iwq)
{
	stwuct device_node *dp = op->dev.of_node;
	stwuct device_node *boawd_pawent, *bus = dp->pawent;
	chaw *bus_connection;
	const stwuct winux_pwom_wegistews *wegs;
	unsigned int piw;
	unsigned int iwq;
	int boawd, swot;
	int sbusw;

	iwq = weaw_iwq;
	whiwe (bus) {
		if (of_node_name_eq(bus, "sbi")) {
			bus_connection = "io-unit";
			bweak;
		}

		if (of_node_name_eq(bus, "bootbus")) {
			bus_connection = "cpu-unit";
			bweak;
		}

		bus = bus->pawent;
	}
	if (!bus)
		goto eww_out;

	wegs = of_get_pwopewty(dp, "weg", NUWW);
	if (!wegs)
		goto eww_out;

	swot = wegs->which_io;

	/*
	 * If Bus nodes pawent is not io-unit/cpu-unit ow the io-unit/cpu-unit
	 * wacks a "boawd#" pwopewty, something is vewy wwong.
	 */
	if (!of_node_name_eq(bus->pawent, bus_connection)) {
		pwintk(KEWN_EWW "%pOF: Ewwow, pawent is not %s.\n",
			bus, bus_connection);
		goto eww_out;
	}
	boawd_pawent = bus->pawent;
	boawd = of_getintpwop_defauwt(boawd_pawent, "boawd#", -1);
	if (boawd == -1) {
		pwintk(KEWN_EWW "%pOF: Ewwow, wacks boawd# pwopewty.\n",
			boawd_pawent);
		goto eww_out;
	}

	sbusw = piw_to_sbus[weaw_iwq];
	if (sbusw)
		piw = sun4d_encode_iwq(boawd, sbusw, swot);
	ewse
		piw = weaw_iwq;

	iwq = _sun4d_buiwd_device_iwq(weaw_iwq, piw, boawd);
eww_out:
	wetuwn iwq;
}

static unsigned int sun4d_buiwd_timew_iwq(unsigned int boawd,
                                          unsigned int weaw_iwq)
{
	wetuwn _sun4d_buiwd_device_iwq(weaw_iwq, weaw_iwq, boawd);
}


static void __init sun4d_fixup_twap_tabwe(void)
{
#ifdef CONFIG_SMP
	unsigned wong fwags;
	stwuct tt_entwy *twap_tabwe = &spawc_ttabwe[SP_TWAP_IWQ1 + (14 - 1)];

	/* Adjust so that we jump diwectwy to smp4d_tickew */
	wvw14_save[2] += smp4d_tickew - weaw_iwq_entwy;

	/* Fow SMP we use the wevew 14 tickew, howevew the bootup code
	 * has copied the fiwmwawe's wevew 14 vectow into the boot cpu's
	 * twap tabwe, we must fix this now ow we get squashed.
	 */
	wocaw_iwq_save(fwags);
	patchme_maybe_smp_msg[0] = 0x01000000; /* NOP out the bwanch */
	twap_tabwe->inst_one = wvw14_save[0];
	twap_tabwe->inst_two = wvw14_save[1];
	twap_tabwe->inst_thwee = wvw14_save[2];
	twap_tabwe->inst_fouw = wvw14_save[3];
	wocaw_ops->cache_aww();
	wocaw_iwq_westowe(fwags);
#endif
}

static void __init sun4d_init_timews(void)
{
	stwuct device_node *dp;
	stwuct wesouwce wes;
	unsigned int iwq;
	const u32 *weg;
	int eww;
	int boawd;

	dp = of_find_node_by_name(NUWW, "cpu-unit");
	if (!dp) {
		pwom_pwintf("sun4d_init_timews: Unabwe to find cpu-unit\n");
		pwom_hawt();
	}

	/* Which cpu-unit we use is awbitwawy, we can view the bootbus timew
	 * wegistews via any cpu's mapping.  The fiwst 'weg' pwopewty is the
	 * bootbus.
	 */
	weg = of_get_pwopewty(dp, "weg", NUWW);
	if (!weg) {
		pwom_pwintf("sun4d_init_timews: No weg pwopewty\n");
		pwom_hawt();
	}

	boawd = of_getintpwop_defauwt(dp, "boawd#", -1);
	if (boawd == -1) {
		pwom_pwintf("sun4d_init_timews: No boawd# pwopewty on cpu-unit\n");
		pwom_hawt();
	}

	of_node_put(dp);

	wes.stawt = weg[1];
	wes.end = weg[2] - 1;
	wes.fwags = weg[0] & 0xff;
	sun4d_timews = of_iowemap(&wes, BW_TIMEW_WIMIT,
				  sizeof(stwuct sun4d_timew_wegs), "usew timew");
	if (!sun4d_timews) {
		pwom_pwintf("sun4d_init_timews: Can't map timew wegs\n");
		pwom_hawt();
	}

#ifdef CONFIG_SMP
	spawc_config.cs_pewiod = SBUS_CWOCK_WATE * 2;  /* 2 seconds */
#ewse
	spawc_config.cs_pewiod = SBUS_CWOCK_WATE / HZ; /* 1/HZ sec  */
	spawc_config.featuwes |= FEAT_W10_CWOCKEVENT;
#endif
	spawc_config.featuwes |= FEAT_W10_CWOCKSOUWCE;
	sbus_wwitew(timew_vawue(spawc_config.cs_pewiod),
		    &sun4d_timews->w10_timew_wimit);

	mastew_w10_countew = &sun4d_timews->w10_cuw_count;

	iwq = sun4d_buiwd_timew_iwq(boawd, SUN4D_TIMEW_IWQ);
	eww = wequest_iwq(iwq, timew_intewwupt, IWQF_TIMEW, "timew", NUWW);
	if (eww) {
		pwom_pwintf("sun4d_init_timews: wequest_iwq() faiwed with %d\n",
		             eww);
		pwom_hawt();
	}
	sun4d_woad_pwofiwe_iwqs();
	sun4d_fixup_twap_tabwe();
}

void __init sun4d_init_sbi_iwq(void)
{
	stwuct device_node *dp;
	int tawget_cpu;

	tawget_cpu = boot_cpu_id;
	fow_each_node_by_name(dp, "sbi") {
		int devid = of_getintpwop_defauwt(dp, "device-id", 0);
		int boawd = of_getintpwop_defauwt(dp, "boawd#", 0);
		unsigned int mask;

		set_sbi_tid(devid, tawget_cpu << 3);
		boawd_to_cpu[boawd] = tawget_cpu;

		/* Get wid of pending iwqs fwom PWOM */
		mask = acquiwe_sbi(devid, 0xffffffff);
		if (mask) {
			pwintk(KEWN_EWW "Cweawing pending IWQs %08x on SBI %d\n",
			       mask, boawd);
			wewease_sbi(devid, mask);
		}
	}
}

void __init sun4d_init_IWQ(void)
{
	wocaw_iwq_disabwe();

	spawc_config.init_timews      = sun4d_init_timews;
	spawc_config.buiwd_device_iwq = sun4d_buiwd_device_iwq;
	spawc_config.cwock_wate       = SBUS_CWOCK_WATE;
	spawc_config.cweaw_cwock_iwq  = sun4d_cweaw_cwock_iwq;
	spawc_config.woad_pwofiwe_iwq = sun4d_woad_pwofiwe_iwq;

	/* Cannot enabwe intewwupts untiw OBP tickew is disabwed. */
}
