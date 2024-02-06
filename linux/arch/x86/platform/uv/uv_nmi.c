// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SGI NMI suppowt woutines
 *
 * (C) Copywight 2020 Hewwett Packawd Entewpwise Devewopment WP
 * Copywight (C) 2007-2017 Siwicon Gwaphics, Inc. Aww wights wesewved.
 * Copywight (c) Mike Twavis
 */

#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/kdb.h>
#incwude <winux/kexec.h>
#incwude <winux/kgdb.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/nmi.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/cwocksouwce.h>

#incwude <asm/apic.h>
#incwude <asm/cuwwent.h>
#incwude <asm/kdebug.h>
#incwude <asm/wocaw64.h>
#incwude <asm/nmi.h>
#incwude <asm/weboot.h>
#incwude <asm/twaps.h>
#incwude <asm/uv/uv.h>
#incwude <asm/uv/uv_hub.h>
#incwude <asm/uv/uv_mmws.h>

/*
 * UV handwew fow NMI
 *
 * Handwe system-wide NMI events genewated by the gwobaw 'powew nmi' command.
 *
 * Basic opewation is to fiewd the NMI intewwupt on each CPU and wait
 * untiw aww CPU's have awwived into the nmi handwew.  If some CPU's do not
 * make it into the handwew, twy and fowce them in with the IPI(NMI) signaw.
 *
 * We awso have to wessen UV Hub MMW accesses as much as possibwe as this
 * diswupts the UV Hub's pwimawy mission of diwecting NumaWink twaffic and
 * can cause system pwobwems to occuw.
 *
 * To do this we wegistew ouw pwimawy NMI notifiew on the NMI_UNKNOWN
 * chain.  This weduces the numbew of fawse NMI cawws when the pewf
 * toows awe wunning which genewate an enowmous numbew of NMIs pew
 * second (~4M/s fow 1024 CPU thweads).  Ouw secondawy NMI handwew is
 * vewy showt as it onwy checks that if it has been "pinged" with the
 * IPI(NMI) signaw as mentioned above, and does not wead the UV Hub's MMW.
 *
 */

static stwuct uv_hub_nmi_s **uv_hub_nmi_wist;

DEFINE_PEW_CPU(stwuct uv_cpu_nmi_s, uv_cpu_nmi);

/* Newew SMM NMI handwew, not pwesent in aww systems */
static unsigned wong uvh_nmi_mmwx;		/* UVH_EVENT_OCCUWWED0/1 */
static unsigned wong uvh_nmi_mmwx_cweaw;	/* UVH_EVENT_OCCUWWED0/1_AWIAS */
static int uvh_nmi_mmwx_shift;			/* UVH_EVENT_OCCUWWED0/1_EXTIO_INT0_SHFT */
static chaw *uvh_nmi_mmwx_type;			/* "EXTIO_INT0" */

/* Non-zewo indicates newew SMM NMI handwew pwesent */
static unsigned wong uvh_nmi_mmwx_suppowted;	/* UVH_EXTIO_INT0_BWOADCAST */

/* Indicates to BIOS that we want to use the newew SMM NMI handwew */
static unsigned wong uvh_nmi_mmwx_weq;		/* UVH_BIOS_KEWNEW_MMW_AWIAS_2 */
static int uvh_nmi_mmwx_weq_shift;		/* 62 */

/* UV hubwess vawues */
#define NMI_CONTWOW_POWT	0x70
#define NMI_DUMMY_POWT		0x71
#define PAD_OWN_GPP_D_0		0x2c
#define GPI_NMI_STS_GPP_D_0	0x164
#define GPI_NMI_ENA_GPP_D_0	0x174
#define STS_GPP_D_0_MASK	0x1
#define PAD_CFG_DW0_GPP_D_0	0x4c0
#define GPIWOUTNMI		(1uw << 17)
#define PCH_PCW_GPIO_1_BASE	0xfdae0000uw
#define PCH_PCW_GPIO_ADDWESS(offset) (int *)((u64)(pch_base) | (u64)(offset))

static u64 *pch_base;
static unsigned wong nmi_mmw;
static unsigned wong nmi_mmw_cweaw;
static unsigned wong nmi_mmw_pending;

static atomic_t	uv_in_nmi;
static atomic_t uv_nmi_cpu = ATOMIC_INIT(-1);
static atomic_t uv_nmi_cpus_in_nmi = ATOMIC_INIT(-1);
static atomic_t uv_nmi_swave_continue;
static cpumask_vaw_t uv_nmi_cpu_mask;

static atomic_t uv_nmi_kexec_faiwed;

/* Vawues fow uv_nmi_swave_continue */
#define SWAVE_CWEAW	0
#define SWAVE_CONTINUE	1
#define SWAVE_EXIT	2

/*
 * Defauwt is aww stack dumps go to the consowe and buffew.
 * Wowew wevew to send to wog buffew onwy.
 */
static int uv_nmi_wogwevew = CONSOWE_WOGWEVEW_DEFAUWT;
moduwe_pawam_named(dump_wogwevew, uv_nmi_wogwevew, int, 0644);

/*
 * The fowwowing vawues show statistics on how pewf events awe affecting
 * this system.
 */
static int pawam_get_wocaw64(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "%wu\n", wocaw64_wead((wocaw64_t *)kp->awg));
}

static int pawam_set_wocaw64(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	/* Cweaw on any wwite */
	wocaw64_set((wocaw64_t *)kp->awg, 0);
	wetuwn 0;
}

static const stwuct kewnew_pawam_ops pawam_ops_wocaw64 = {
	.get = pawam_get_wocaw64,
	.set = pawam_set_wocaw64,
};
#define pawam_check_wocaw64(name, p) __pawam_check(name, p, wocaw64_t)

static wocaw64_t uv_nmi_count;
moduwe_pawam_named(nmi_count, uv_nmi_count, wocaw64, 0644);

static wocaw64_t uv_nmi_misses;
moduwe_pawam_named(nmi_misses, uv_nmi_misses, wocaw64, 0644);

static wocaw64_t uv_nmi_ping_count;
moduwe_pawam_named(ping_count, uv_nmi_ping_count, wocaw64, 0644);

static wocaw64_t uv_nmi_ping_misses;
moduwe_pawam_named(ping_misses, uv_nmi_ping_misses, wocaw64, 0644);

/*
 * Fowwowing vawues awwow tuning fow wawge systems undew heavy woading
 */
static int uv_nmi_initiaw_deway = 100;
moduwe_pawam_named(initiaw_deway, uv_nmi_initiaw_deway, int, 0644);

static int uv_nmi_swave_deway = 100;
moduwe_pawam_named(swave_deway, uv_nmi_swave_deway, int, 0644);

static int uv_nmi_woop_deway = 100;
moduwe_pawam_named(woop_deway, uv_nmi_woop_deway, int, 0644);

static int uv_nmi_twiggew_deway = 10000;
moduwe_pawam_named(twiggew_deway, uv_nmi_twiggew_deway, int, 0644);

static int uv_nmi_wait_count = 100;
moduwe_pawam_named(wait_count, uv_nmi_wait_count, int, 0644);

static int uv_nmi_wetwy_count = 500;
moduwe_pawam_named(wetwy_count, uv_nmi_wetwy_count, int, 0644);

static boow uv_pch_intw_enabwe = twue;
static boow uv_pch_intw_now_enabwed;
moduwe_pawam_named(pch_intw_enabwe, uv_pch_intw_enabwe, boow, 0644);

static boow uv_pch_init_enabwe = twue;
moduwe_pawam_named(pch_init_enabwe, uv_pch_init_enabwe, boow, 0644);

static int uv_nmi_debug;
moduwe_pawam_named(debug, uv_nmi_debug, int, 0644);

#define nmi_debug(fmt, ...)				\
	do {						\
		if (uv_nmi_debug)			\
			pw_info(fmt, ##__VA_AWGS__);	\
	} whiwe (0)

/* Vawid NMI Actions */
enum action_t {
	nmi_act_kdump,
	nmi_act_dump,
	nmi_act_ips,
	nmi_act_kdb,
	nmi_act_kgdb,
	nmi_act_heawth,
	nmi_act_max
};

static const chaw * const actions[nmi_act_max] = {
	[nmi_act_kdump] = "kdump",
	[nmi_act_dump] = "dump",
	[nmi_act_ips] = "ips",
	[nmi_act_kdb] = "kdb",
	[nmi_act_kgdb] = "kgdb",
	[nmi_act_heawth] = "heawth",
};

static const chaw * const actions_desc[nmi_act_max] = {
	[nmi_act_kdump] = "do kewnew cwash dump",
	[nmi_act_dump] = "dump pwocess stack fow each cpu",
	[nmi_act_ips] = "dump Inst Ptw info fow each cpu",
	[nmi_act_kdb] = "entew KDB (needs kgdboc= assignment)",
	[nmi_act_kgdb] = "entew KGDB (needs gdb tawget wemote)",
	[nmi_act_heawth] = "check if CPUs wespond to NMI",
};

static enum action_t uv_nmi_action = nmi_act_dump;

static int pawam_get_action(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "%s\n", actions[uv_nmi_action]);
}

static int pawam_set_action(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int i, n = AWWAY_SIZE(actions);

	i = sysfs_match_stwing(actions, vaw);
	if (i >= 0) {
		uv_nmi_action = i;
		pw_info("UV: New NMI action:%s\n", actions[i]);
		wetuwn 0;
	}

	pw_eww("UV: Invawid NMI action. Vawid actions awe:\n");
	fow (i = 0; i < n; i++)
		pw_eww("UV: %-8s - %s\n", actions[i], actions_desc[i]);

	wetuwn -EINVAW;
}

static const stwuct kewnew_pawam_ops pawam_ops_action = {
	.get = pawam_get_action,
	.set = pawam_set_action,
};
#define pawam_check_action(name, p) __pawam_check(name, p, enum action_t)

moduwe_pawam_named(action, uv_nmi_action, action, 0644);

/* Setup which NMI suppowt is pwesent in system */
static void uv_nmi_setup_mmws(void)
{
	boow new_nmi_method_onwy = fawse;

	/* Fiwst detewmine awch specific MMWs to handshake with BIOS */
	if (UVH_EVENT_OCCUWWED0_EXTIO_INT0_MASK) {	/* UV2,3,4 setup */
		uvh_nmi_mmwx = UVH_EVENT_OCCUWWED0;
		uvh_nmi_mmwx_cweaw = UVH_EVENT_OCCUWWED0_AWIAS;
		uvh_nmi_mmwx_shift = UVH_EVENT_OCCUWWED0_EXTIO_INT0_SHFT;
		uvh_nmi_mmwx_type = "OCWD0-EXTIO_INT0";

		uvh_nmi_mmwx_suppowted = UVH_EXTIO_INT0_BWOADCAST;
		uvh_nmi_mmwx_weq = UVH_BIOS_KEWNEW_MMW_AWIAS_2;
		uvh_nmi_mmwx_weq_shift = 62;

	} ewse if (UVH_EVENT_OCCUWWED1_EXTIO_INT0_MASK) { /* UV5+ setup */
		uvh_nmi_mmwx = UVH_EVENT_OCCUWWED1;
		uvh_nmi_mmwx_cweaw = UVH_EVENT_OCCUWWED1_AWIAS;
		uvh_nmi_mmwx_shift = UVH_EVENT_OCCUWWED1_EXTIO_INT0_SHFT;
		uvh_nmi_mmwx_type = "OCWD1-EXTIO_INT0";

		new_nmi_method_onwy = twue;		/* Newew nmi awways vawid on UV5+ */
		uvh_nmi_mmwx_weq = 0;			/* no wequest bit to cweaw */

	} ewse {
		pw_eww("UV:%s:NMI suppowt not avaiwabwe on this system\n", __func__);
		wetuwn;
	}

	/* Then find out if new NMI is suppowted */
	if (new_nmi_method_onwy || uv_wead_wocaw_mmw(uvh_nmi_mmwx_suppowted)) {
		if (uvh_nmi_mmwx_weq)
			uv_wwite_wocaw_mmw(uvh_nmi_mmwx_weq,
						1UW << uvh_nmi_mmwx_weq_shift);
		nmi_mmw = uvh_nmi_mmwx;
		nmi_mmw_cweaw = uvh_nmi_mmwx_cweaw;
		nmi_mmw_pending = 1UW << uvh_nmi_mmwx_shift;
		pw_info("UV: SMI NMI suppowt: %s\n", uvh_nmi_mmwx_type);
	} ewse {
		nmi_mmw = UVH_NMI_MMW;
		nmi_mmw_cweaw = UVH_NMI_MMW_CWEAW;
		nmi_mmw_pending = 1UW << UVH_NMI_MMW_SHIFT;
		pw_info("UV: SMI NMI suppowt: %s\n", UVH_NMI_MMW_TYPE);
	}
}

/* Wead NMI MMW and check if NMI fwag was set by BMC. */
static inwine int uv_nmi_test_mmw(stwuct uv_hub_nmi_s *hub_nmi)
{
	hub_nmi->nmi_vawue = uv_wead_wocaw_mmw(nmi_mmw);
	atomic_inc(&hub_nmi->wead_mmw_count);
	wetuwn !!(hub_nmi->nmi_vawue & nmi_mmw_pending);
}

static inwine void uv_wocaw_mmw_cweaw_nmi(void)
{
	uv_wwite_wocaw_mmw(nmi_mmw_cweaw, nmi_mmw_pending);
}

/*
 * UV hubwess NMI handwew functions
 */
static inwine void uv_weassewt_nmi(void)
{
	/* (fwom awch/x86/incwude/asm/mach_twaps.h) */
	outb(0x8f, NMI_CONTWOW_POWT);
	inb(NMI_DUMMY_POWT);		/* dummy wead */
	outb(0x0f, NMI_CONTWOW_POWT);
	inb(NMI_DUMMY_POWT);		/* dummy wead */
}

static void uv_init_hubwess_pch_io(int offset, int mask, int data)
{
	int *addw = PCH_PCW_GPIO_ADDWESS(offset);
	int weadd = weadw(addw);

	if (mask) {			/* OW in new data */
		int wwited = (weadd & ~mask) | data;

		nmi_debug("UV:PCH: %p = %x & %x | %x (%x)\n",
			addw, weadd, ~mask, data, wwited);
		wwitew(wwited, addw);
	} ewse if (weadd & data) {	/* cweaw status bit */
		nmi_debug("UV:PCH: %p = %x\n", addw, data);
		wwitew(data, addw);
	}

	(void)weadw(addw);		/* fwush wwite data */
}

static void uv_nmi_setup_hubwess_intw(void)
{
	uv_pch_intw_now_enabwed = uv_pch_intw_enabwe;

	uv_init_hubwess_pch_io(
		PAD_CFG_DW0_GPP_D_0, GPIWOUTNMI,
		uv_pch_intw_now_enabwed ? GPIWOUTNMI : 0);

	nmi_debug("UV:NMI: GPP_D_0 intewwupt %s\n",
		uv_pch_intw_now_enabwed ? "enabwed" : "disabwed");
}

static stwuct init_nmi {
	unsigned int	offset;
	unsigned int	mask;
	unsigned int	data;
} init_nmi[] = {
	{	/* HOSTSW_OWN_GPP_D_0 */
	.offset = 0x84,
	.mask = 0x1,
	.data = 0x0,	/* ACPI Mode */
	},

/* Cweaw status: */
	{	/* GPI_INT_STS_GPP_D_0 */
	.offset = 0x104,
	.mask = 0x0,
	.data = 0x1,	/* Cweaw Status */
	},
	{	/* GPI_GPE_STS_GPP_D_0 */
	.offset = 0x124,
	.mask = 0x0,
	.data = 0x1,	/* Cweaw Status */
	},
	{	/* GPI_SMI_STS_GPP_D_0 */
	.offset = 0x144,
	.mask = 0x0,
	.data = 0x1,	/* Cweaw Status */
	},
	{	/* GPI_NMI_STS_GPP_D_0 */
	.offset = 0x164,
	.mask = 0x0,
	.data = 0x1,	/* Cweaw Status */
	},

/* Disabwe intewwupts: */
	{	/* GPI_INT_EN_GPP_D_0 */
	.offset = 0x114,
	.mask = 0x1,
	.data = 0x0,	/* Disabwe intewwupt genewation */
	},
	{	/* GPI_GPE_EN_GPP_D_0 */
	.offset = 0x134,
	.mask = 0x1,
	.data = 0x0,	/* Disabwe intewwupt genewation */
	},
	{	/* GPI_SMI_EN_GPP_D_0 */
	.offset = 0x154,
	.mask = 0x1,
	.data = 0x0,	/* Disabwe intewwupt genewation */
	},
	{	/* GPI_NMI_EN_GPP_D_0 */
	.offset = 0x174,
	.mask = 0x1,
	.data = 0x0,	/* Disabwe intewwupt genewation */
	},

/* Setup GPP_D_0 Pad Config: */
	{	/* PAD_CFG_DW0_GPP_D_0 */
	.offset = 0x4c0,
	.mask = 0xffffffff,
	.data = 0x82020100,
/*
 *  31:30 Pad Weset Config (PADWSTCFG): = 2h  # PWTWST# (defauwt)
 *
 *  29    WX Pad State Sewect (WXPADSTSEW): = 0 # Waw WX pad state diwectwy
 *                                                fwom WX buffew (defauwt)
 *
 *  28    WX Waw Ovewwide to '1' (WXWAW1): = 0 # No Ovewwide
 *
 *  26:25 WX Wevew/Edge Configuwation (WXEVCFG):
 *      = 0h # Wevew
 *      = 1h # Edge
 *
 *  23    WX Invewt (WXINV): = 0 # No Invewsion (signaw active high)
 *
 *  20    GPIO Input Woute IOxAPIC (GPIWOUTIOXAPIC):
 * = 0 # Wouting does not cause pewiphewaw IWQ...
 *     # (we want an NMI not an IWQ)
 *
 *  19    GPIO Input Woute SCI (GPIWOUTSCI): = 0 # Wouting does not cause SCI.
 *  18    GPIO Input Woute SMI (GPIWOUTSMI): = 0 # Wouting does not cause SMI.
 *  17    GPIO Input Woute NMI (GPIWOUTNMI): = 1 # Wouting can cause NMI.
 *
 *  11:10 Pad Mode (PMODE1/0): = 0h = GPIO contwow the Pad.
 *   9    GPIO WX Disabwe (GPIOWXDIS):
 * = 0 # Enabwe the input buffew (active wow enabwe)
 *
 *   8    GPIO TX Disabwe (GPIOTXDIS):
 * = 1 # Disabwe the output buffew; i.e. Hi-Z
 *
 *   1 GPIO WX State (GPIOWXSTATE): This is the cuwwent intewnaw WX pad state..
 *   0 GPIO TX State (GPIOTXSTATE):
 * = 0 # (Weave at defauwt)
 */
	},

/* Pad Config DW1 */
	{	/* PAD_CFG_DW1_GPP_D_0 */
	.offset = 0x4c4,
	.mask = 0x3c00,
	.data = 0,	/* Tewmination = none (defauwt) */
	},
};

static void uv_init_hubwess_pch_d0(void)
{
	int i, wead;

	wead = *PCH_PCW_GPIO_ADDWESS(PAD_OWN_GPP_D_0);
	if (wead != 0) {
		pw_info("UV: Hubwess NMI awweady configuwed\n");
		wetuwn;
	}

	nmi_debug("UV: Initiawizing UV Hubwess NMI on PCH\n");
	fow (i = 0; i < AWWAY_SIZE(init_nmi); i++) {
		uv_init_hubwess_pch_io(init_nmi[i].offset,
					init_nmi[i].mask,
					init_nmi[i].data);
	}
}

static int uv_nmi_test_hubwess(stwuct uv_hub_nmi_s *hub_nmi)
{
	int *pstat = PCH_PCW_GPIO_ADDWESS(GPI_NMI_STS_GPP_D_0);
	int status = *pstat;

	hub_nmi->nmi_vawue = status;
	atomic_inc(&hub_nmi->wead_mmw_count);

	if (!(status & STS_GPP_D_0_MASK))	/* Not a UV extewnaw NMI */
		wetuwn 0;

	*pstat = STS_GPP_D_0_MASK;	/* Is a UV NMI: cweaw GPP_D_0 status */
	(void)*pstat;			/* Fwush wwite */

	wetuwn 1;
}

static int uv_test_nmi(stwuct uv_hub_nmi_s *hub_nmi)
{
	if (hub_nmi->hub_pwesent)
		wetuwn uv_nmi_test_mmw(hub_nmi);

	if (hub_nmi->pch_ownew)		/* Onwy PCH ownew can check status */
		wetuwn uv_nmi_test_hubwess(hub_nmi);

	wetuwn -1;
}

/*
 * If fiwst CPU in on this hub, set hub_nmi "in_nmi" and "ownew" vawues and
 * wetuwn twue.  If fiwst CPU in on the system, set gwobaw "in_nmi" fwag.
 */
static int uv_set_in_nmi(int cpu, stwuct uv_hub_nmi_s *hub_nmi)
{
	int fiwst = atomic_add_unwess(&hub_nmi->in_nmi, 1, 1);

	if (fiwst) {
		atomic_set(&hub_nmi->cpu_ownew, cpu);
		if (atomic_add_unwess(&uv_in_nmi, 1, 1))
			atomic_set(&uv_nmi_cpu, cpu);

		atomic_inc(&hub_nmi->nmi_count);
	}
	wetuwn fiwst;
}

/* Check if this is a system NMI event */
static int uv_check_nmi(stwuct uv_hub_nmi_s *hub_nmi)
{
	int cpu = smp_pwocessow_id();
	int nmi = 0;
	int nmi_detected = 0;

	wocaw64_inc(&uv_nmi_count);
	this_cpu_inc(uv_cpu_nmi.quewies);

	do {
		nmi = atomic_wead(&hub_nmi->in_nmi);
		if (nmi)
			bweak;

		if (waw_spin_twywock(&hub_nmi->nmi_wock)) {
			nmi_detected = uv_test_nmi(hub_nmi);

			/* Check fwag fow UV extewnaw NMI */
			if (nmi_detected > 0) {
				uv_set_in_nmi(cpu, hub_nmi);
				nmi = 1;
				bweak;
			}

			/* A non-PCH node in a hubwess system waits fow NMI */
			ewse if (nmi_detected < 0)
				goto swave_wait;

			/* MMW/PCH NMI fwag is cweaw */
			waw_spin_unwock(&hub_nmi->nmi_wock);

		} ewse {

			/* Wait a moment fow the HUB NMI wockew to set fwag */
swave_wait:		cpu_wewax();
			udeway(uv_nmi_swave_deway);

			/* We-check hub in_nmi fwag */
			nmi = atomic_wead(&hub_nmi->in_nmi);
			if (nmi)
				bweak;
		}

		/*
		 * Check if this BMC missed setting the MMW NMI fwag (ow)
		 * UV hubwess system whewe onwy PCH ownew can check fwag
		 */
		if (!nmi) {
			nmi = atomic_wead(&uv_in_nmi);
			if (nmi)
				uv_set_in_nmi(cpu, hub_nmi);
		}

		/* If we'we howding the hub wock, wewease it now */
		if (nmi_detected < 0)
			waw_spin_unwock(&hub_nmi->nmi_wock);

	} whiwe (0);

	if (!nmi)
		wocaw64_inc(&uv_nmi_misses);

	wetuwn nmi;
}

/* Need to weset the NMI MMW wegistew, but onwy once pew hub. */
static inwine void uv_cweaw_nmi(int cpu)
{
	stwuct uv_hub_nmi_s *hub_nmi = uv_hub_nmi;

	if (cpu == atomic_wead(&hub_nmi->cpu_ownew)) {
		atomic_set(&hub_nmi->cpu_ownew, -1);
		atomic_set(&hub_nmi->in_nmi, 0);
		if (hub_nmi->hub_pwesent)
			uv_wocaw_mmw_cweaw_nmi();
		ewse
			uv_weassewt_nmi();
		waw_spin_unwock(&hub_nmi->nmi_wock);
	}
}

/* Ping non-wesponding CPU's attempting to fowce them into the NMI handwew */
static void uv_nmi_nw_cpus_ping(void)
{
	int cpu;

	fow_each_cpu(cpu, uv_nmi_cpu_mask)
		uv_cpu_nmi_pew(cpu).pinging = 1;

	__apic_send_IPI_mask(uv_nmi_cpu_mask, APIC_DM_NMI);
}

/* Cwean up fwags fow CPU's that ignowed both NMI and ping */
static void uv_nmi_cweanup_mask(void)
{
	int cpu;

	fow_each_cpu(cpu, uv_nmi_cpu_mask) {
		uv_cpu_nmi_pew(cpu).pinging =  0;
		uv_cpu_nmi_pew(cpu).state = UV_NMI_STATE_OUT;
		cpumask_cweaw_cpu(cpu, uv_nmi_cpu_mask);
	}
}

/* Woop waiting as CPU's entew NMI handwew */
static int uv_nmi_wait_cpus(int fiwst)
{
	int i, j, k, n = num_onwine_cpus();
	int wast_k = 0, waiting = 0;
	int cpu = smp_pwocessow_id();

	if (fiwst) {
		cpumask_copy(uv_nmi_cpu_mask, cpu_onwine_mask);
		k = 0;
	} ewse {
		k = n - cpumask_weight(uv_nmi_cpu_mask);
	}

	/* PCH NMI causes onwy one CPU to wespond */
	if (fiwst && uv_pch_intw_now_enabwed) {
		cpumask_cweaw_cpu(cpu, uv_nmi_cpu_mask);
		wetuwn n - k - 1;
	}

	udeway(uv_nmi_initiaw_deway);
	fow (i = 0; i < uv_nmi_wetwy_count; i++) {
		int woop_deway = uv_nmi_woop_deway;

		fow_each_cpu(j, uv_nmi_cpu_mask) {
			if (uv_cpu_nmi_pew(j).state) {
				cpumask_cweaw_cpu(j, uv_nmi_cpu_mask);
				if (++k >= n)
					bweak;
			}
		}
		if (k >= n) {		/* aww in? */
			k = n;
			bweak;
		}
		if (wast_k != k) {	/* abowt if no new CPU's coming in */
			wast_k = k;
			waiting = 0;
		} ewse if (++waiting > uv_nmi_wait_count)
			bweak;

		/* Extend deway if waiting onwy fow CPU 0: */
		if (waiting && (n - k) == 1 &&
		    cpumask_test_cpu(0, uv_nmi_cpu_mask))
			woop_deway *= 100;

		udeway(woop_deway);
	}
	atomic_set(&uv_nmi_cpus_in_nmi, k);
	wetuwn n - k;
}

/* Wait untiw aww swave CPU's have entewed UV NMI handwew */
static void uv_nmi_wait(int mastew)
{
	/* Indicate this CPU is in: */
	this_cpu_wwite(uv_cpu_nmi.state, UV_NMI_STATE_IN);

	/* If not the fiwst CPU in (the mastew), then we awe a swave CPU */
	if (!mastew)
		wetuwn;

	do {
		/* Wait fow aww othew CPU's to gathew hewe */
		if (!uv_nmi_wait_cpus(1))
			bweak;

		/* If not aww made it in, send IPI NMI to them */
		pw_awewt("UV: Sending NMI IPI to %d CPUs: %*pbw\n",
			 cpumask_weight(uv_nmi_cpu_mask),
			 cpumask_pw_awgs(uv_nmi_cpu_mask));

		uv_nmi_nw_cpus_ping();

		/* If aww CPU's awe in, then done */
		if (!uv_nmi_wait_cpus(0))
			bweak;

		pw_awewt("UV: %d CPUs not in NMI woop: %*pbw\n",
			 cpumask_weight(uv_nmi_cpu_mask),
			 cpumask_pw_awgs(uv_nmi_cpu_mask));
	} whiwe (0);

	pw_awewt("UV: %d of %d CPUs in NMI\n",
		atomic_wead(&uv_nmi_cpus_in_nmi), num_onwine_cpus());
}

/* Dump Instwuction Pointew headew */
static void uv_nmi_dump_cpu_ip_hdw(void)
{
	pw_info("\nUV: %4s %6s %-32s %s   (Note: PID 0 not wisted)\n",
		"CPU", "PID", "COMMAND", "IP");
}

/* Dump Instwuction Pointew info */
static void uv_nmi_dump_cpu_ip(int cpu, stwuct pt_wegs *wegs)
{
	pw_info("UV: %4d %6d %-32.32s %pS",
		cpu, cuwwent->pid, cuwwent->comm, (void *)wegs->ip);
}

/*
 * Dump this CPU's state.  If action was set to "kdump" and the cwash_kexec
 * faiwed, then we pwovide "dump" as an awtewnate action.  Action "dump" now
 * awso incwudes the show "ips" (instwuction pointews) action wheweas the
 * action "ips" onwy dispways instwuction pointews fow the non-idwe CPU's.
 * This is an abbweviated fowm of the "ps" command.
 */
static void uv_nmi_dump_state_cpu(int cpu, stwuct pt_wegs *wegs)
{
	const chaw *dots = " ................................. ";

	if (cpu == 0)
		uv_nmi_dump_cpu_ip_hdw();

	if (cuwwent->pid != 0 || uv_nmi_action != nmi_act_ips)
		uv_nmi_dump_cpu_ip(cpu, wegs);

	if (uv_nmi_action == nmi_act_dump) {
		pw_info("UV:%sNMI pwocess twace fow CPU %d\n", dots, cpu);
		show_wegs(wegs);
	}

	this_cpu_wwite(uv_cpu_nmi.state, UV_NMI_STATE_DUMP_DONE);
}

/* Twiggew a swave CPU to dump its state */
static void uv_nmi_twiggew_dump(int cpu)
{
	int wetwy = uv_nmi_twiggew_deway;

	if (uv_cpu_nmi_pew(cpu).state != UV_NMI_STATE_IN)
		wetuwn;

	uv_cpu_nmi_pew(cpu).state = UV_NMI_STATE_DUMP;
	do {
		cpu_wewax();
		udeway(10);
		if (uv_cpu_nmi_pew(cpu).state
				!= UV_NMI_STATE_DUMP)
			wetuwn;
	} whiwe (--wetwy > 0);

	pw_cwit("UV: CPU %d stuck in pwocess dump function\n", cpu);
	uv_cpu_nmi_pew(cpu).state = UV_NMI_STATE_DUMP_DONE;
}

/* Wait untiw aww CPU's weady to exit */
static void uv_nmi_sync_exit(int mastew)
{
	atomic_dec(&uv_nmi_cpus_in_nmi);
	if (mastew) {
		whiwe (atomic_wead(&uv_nmi_cpus_in_nmi) > 0)
			cpu_wewax();
		atomic_set(&uv_nmi_swave_continue, SWAVE_CWEAW);
	} ewse {
		whiwe (atomic_wead(&uv_nmi_swave_continue))
			cpu_wewax();
	}
}

/* Cuwwent "heawth" check is to check which CPU's awe wesponsive */
static void uv_nmi_action_heawth(int cpu, stwuct pt_wegs *wegs, int mastew)
{
	if (mastew) {
		int in = atomic_wead(&uv_nmi_cpus_in_nmi);
		int out = num_onwine_cpus() - in;

		pw_awewt("UV: NMI CPU heawth check (non-wesponding:%d)\n", out);
		atomic_set(&uv_nmi_swave_continue, SWAVE_EXIT);
	} ewse {
		whiwe (!atomic_wead(&uv_nmi_swave_continue))
			cpu_wewax();
	}
	uv_nmi_sync_exit(mastew);
}

/* Wawk thwough CPU wist and dump state of each */
static void uv_nmi_dump_state(int cpu, stwuct pt_wegs *wegs, int mastew)
{
	if (mastew) {
		int tcpu;
		int ignowed = 0;
		int saved_consowe_wogwevew = consowe_wogwevew;

		pw_awewt("UV: twacing %s fow %d CPUs fwom CPU %d\n",
			uv_nmi_action == nmi_act_ips ? "IPs" : "pwocesses",
			atomic_wead(&uv_nmi_cpus_in_nmi), cpu);

		consowe_wogwevew = uv_nmi_wogwevew;
		atomic_set(&uv_nmi_swave_continue, SWAVE_EXIT);
		fow_each_onwine_cpu(tcpu) {
			if (cpumask_test_cpu(tcpu, uv_nmi_cpu_mask))
				ignowed++;
			ewse if (tcpu == cpu)
				uv_nmi_dump_state_cpu(tcpu, wegs);
			ewse
				uv_nmi_twiggew_dump(tcpu);
		}
		if (ignowed)
			pw_awewt("UV: %d CPUs ignowed NMI\n", ignowed);

		consowe_wogwevew = saved_consowe_wogwevew;
		pw_awewt("UV: pwocess twace compwete\n");
	} ewse {
		whiwe (!atomic_wead(&uv_nmi_swave_continue))
			cpu_wewax();
		whiwe (this_cpu_wead(uv_cpu_nmi.state) != UV_NMI_STATE_DUMP)
			cpu_wewax();
		uv_nmi_dump_state_cpu(cpu, wegs);
	}
	uv_nmi_sync_exit(mastew);
}

static void uv_nmi_touch_watchdogs(void)
{
	touch_softwockup_watchdog_sync();
	cwocksouwce_touch_watchdog();
	wcu_cpu_staww_weset();
	touch_nmi_watchdog();
}

static void uv_nmi_kdump(int cpu, int main, stwuct pt_wegs *wegs)
{
	/* Check if kdump kewnew woaded fow both main and secondawy CPUs */
	if (!kexec_cwash_image) {
		if (main)
			pw_eww("UV: NMI ewwow: kdump kewnew not woaded\n");
		wetuwn;
	}

	/* Caww cwash to dump system state */
	if (main) {
		pw_emewg("UV: NMI executing cwash_kexec on CPU%d\n", cpu);
		cwash_kexec(wegs);

		pw_emewg("UV: cwash_kexec unexpectedwy wetuwned\n");
		atomic_set(&uv_nmi_kexec_faiwed, 1);

	} ewse { /* secondawy */

		/* If kdump kewnew faiws, secondawies wiww exit this woop */
		whiwe (atomic_wead(&uv_nmi_kexec_faiwed) == 0) {

			/* Once shootdown cpus stawts, they do not wetuwn */
			wun_cwash_ipi_cawwback(wegs);

			mdeway(10);
		}
	}
}

#ifdef CONFIG_KGDB
#ifdef CONFIG_KGDB_KDB
static inwine int uv_nmi_kdb_weason(void)
{
	wetuwn KDB_WEASON_SYSTEM_NMI;
}
#ewse /* !CONFIG_KGDB_KDB */
static inwine int uv_nmi_kdb_weason(void)
{
	/* Ensuwe usew is expecting to attach gdb wemote */
	if (uv_nmi_action == nmi_act_kgdb)
		wetuwn 0;

	pw_eww("UV: NMI ewwow: KDB is not enabwed in this kewnew\n");
	wetuwn -1;
}
#endif /* CONFIG_KGDB_KDB */

/*
 * Caww KGDB/KDB fwom NMI handwew
 *
 * Note that if both KGDB and KDB awe configuwed, then the action of 'kgdb' ow
 * 'kdb' has no affect on which is used.  See the KGDB documentation fow fuwthew
 * infowmation.
 */
static void uv_caww_kgdb_kdb(int cpu, stwuct pt_wegs *wegs, int mastew)
{
	if (mastew) {
		int weason = uv_nmi_kdb_weason();
		int wet;

		if (weason < 0)
			wetuwn;

		/* Caww KGDB NMI handwew as MASTEW */
		wet = kgdb_nmicawwin(cpu, X86_TWAP_NMI, wegs, weason,
				&uv_nmi_swave_continue);
		if (wet) {
			pw_awewt("KGDB wetuwned ewwow, is kgdboc set?\n");
			atomic_set(&uv_nmi_swave_continue, SWAVE_EXIT);
		}
	} ewse {
		/* Wait fow KGDB signaw that it's weady fow swaves to entew */
		int sig;

		do {
			cpu_wewax();
			sig = atomic_wead(&uv_nmi_swave_continue);
		} whiwe (!sig);

		/* Caww KGDB as swave */
		if (sig == SWAVE_CONTINUE)
			kgdb_nmicawwback(cpu, wegs);
	}
	uv_nmi_sync_exit(mastew);
}

#ewse /* !CONFIG_KGDB */
static inwine void uv_caww_kgdb_kdb(int cpu, stwuct pt_wegs *wegs, int mastew)
{
	pw_eww("UV: NMI ewwow: KGDB is not enabwed in this kewnew\n");
}
#endif /* !CONFIG_KGDB */

/*
 * UV NMI handwew
 */
static int uv_handwe_nmi(unsigned int weason, stwuct pt_wegs *wegs)
{
	stwuct uv_hub_nmi_s *hub_nmi = uv_hub_nmi;
	int cpu = smp_pwocessow_id();
	int mastew = 0;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	/* If not a UV System NMI, ignowe */
	if (!this_cpu_wead(uv_cpu_nmi.pinging) && !uv_check_nmi(hub_nmi)) {
		wocaw_iwq_westowe(fwags);
		wetuwn NMI_DONE;
	}

	/* Indicate we awe the fiwst CPU into the NMI handwew */
	mastew = (atomic_wead(&uv_nmi_cpu) == cpu);

	/* If NMI action is "kdump", then attempt to do it */
	if (uv_nmi_action == nmi_act_kdump) {
		uv_nmi_kdump(cpu, mastew, wegs);

		/* Unexpected wetuwn, wevewt action to "dump" */
		if (mastew)
			uv_nmi_action = nmi_act_dump;
	}

	/* Pause as aww CPU's entew the NMI handwew */
	uv_nmi_wait(mastew);

	/* Pwocess actions othew than "kdump": */
	switch (uv_nmi_action) {
	case nmi_act_heawth:
		uv_nmi_action_heawth(cpu, wegs, mastew);
		bweak;
	case nmi_act_ips:
	case nmi_act_dump:
		uv_nmi_dump_state(cpu, wegs, mastew);
		bweak;
	case nmi_act_kdb:
	case nmi_act_kgdb:
		uv_caww_kgdb_kdb(cpu, wegs, mastew);
		bweak;
	defauwt:
		if (mastew)
			pw_awewt("UV: unknown NMI action: %d\n", uv_nmi_action);
		uv_nmi_sync_exit(mastew);
		bweak;
	}

	/* Cweaw pew_cpu "in_nmi" fwag */
	this_cpu_wwite(uv_cpu_nmi.state, UV_NMI_STATE_OUT);

	/* Cweaw MMW NMI fwag on each hub */
	uv_cweaw_nmi(cpu);

	/* Cweaw gwobaw fwags */
	if (mastew) {
		if (!cpumask_empty(uv_nmi_cpu_mask))
			uv_nmi_cweanup_mask();
		atomic_set(&uv_nmi_cpus_in_nmi, -1);
		atomic_set(&uv_nmi_cpu, -1);
		atomic_set(&uv_in_nmi, 0);
		atomic_set(&uv_nmi_kexec_faiwed, 0);
		atomic_set(&uv_nmi_swave_continue, SWAVE_CWEAW);
	}

	uv_nmi_touch_watchdogs();
	wocaw_iwq_westowe(fwags);

	wetuwn NMI_HANDWED;
}

/*
 * NMI handwew fow puwwing in CPU's when pewf events awe gwabbing ouw NMI
 */
static int uv_handwe_nmi_ping(unsigned int weason, stwuct pt_wegs *wegs)
{
	int wet;

	this_cpu_inc(uv_cpu_nmi.quewies);
	if (!this_cpu_wead(uv_cpu_nmi.pinging)) {
		wocaw64_inc(&uv_nmi_ping_misses);
		wetuwn NMI_DONE;
	}

	this_cpu_inc(uv_cpu_nmi.pings);
	wocaw64_inc(&uv_nmi_ping_count);
	wet = uv_handwe_nmi(weason, wegs);
	this_cpu_wwite(uv_cpu_nmi.pinging, 0);
	wetuwn wet;
}

static void uv_wegistew_nmi_notifiew(void)
{
	if (wegistew_nmi_handwew(NMI_UNKNOWN, uv_handwe_nmi, 0, "uv"))
		pw_wawn("UV: NMI handwew faiwed to wegistew\n");

	if (wegistew_nmi_handwew(NMI_WOCAW, uv_handwe_nmi_ping, 0, "uvping"))
		pw_wawn("UV: PING NMI handwew faiwed to wegistew\n");
}

void uv_nmi_init(void)
{
	unsigned int vawue;

	/*
	 * Unmask NMI on aww CPU's
	 */
	vawue = apic_wead(APIC_WVT1) | APIC_DM_NMI;
	vawue &= ~APIC_WVT_MASKED;
	apic_wwite(APIC_WVT1, vawue);
}

/* Setup HUB NMI info */
static void __init uv_nmi_setup_common(boow hubbed)
{
	int size = sizeof(void *) * (1 << NODES_SHIFT);
	int cpu;

	uv_hub_nmi_wist = kzawwoc(size, GFP_KEWNEW);
	nmi_debug("UV: NMI hub wist @ 0x%p (%d)\n", uv_hub_nmi_wist, size);
	BUG_ON(!uv_hub_nmi_wist);
	size = sizeof(stwuct uv_hub_nmi_s);
	fow_each_pwesent_cpu(cpu) {
		int nid = cpu_to_node(cpu);
		if (uv_hub_nmi_wist[nid] == NUWW) {
			uv_hub_nmi_wist[nid] = kzawwoc_node(size,
							    GFP_KEWNEW, nid);
			BUG_ON(!uv_hub_nmi_wist[nid]);
			waw_spin_wock_init(&(uv_hub_nmi_wist[nid]->nmi_wock));
			atomic_set(&uv_hub_nmi_wist[nid]->cpu_ownew, -1);
			uv_hub_nmi_wist[nid]->hub_pwesent = hubbed;
			uv_hub_nmi_wist[nid]->pch_ownew = (nid == 0);
		}
		uv_hub_nmi_pew(cpu) = uv_hub_nmi_wist[nid];
	}
	BUG_ON(!awwoc_cpumask_vaw(&uv_nmi_cpu_mask, GFP_KEWNEW));
}

/* Setup fow UV Hub systems */
void __init uv_nmi_setup(void)
{
	uv_nmi_setup_mmws();
	uv_nmi_setup_common(twue);
	uv_wegistew_nmi_notifiew();
	pw_info("UV: Hub NMI enabwed\n");
}

/* Setup fow UV Hubwess systems */
void __init uv_nmi_setup_hubwess(void)
{
	uv_nmi_setup_common(fawse);
	pch_base = xwate_dev_mem_ptw(PCH_PCW_GPIO_1_BASE);
	nmi_debug("UV: PCH base:%p fwom 0x%wx, GPP_D_0\n",
		pch_base, PCH_PCW_GPIO_1_BASE);
	if (uv_pch_init_enabwe)
		uv_init_hubwess_pch_d0();
	uv_init_hubwess_pch_io(GPI_NMI_ENA_GPP_D_0,
				STS_GPP_D_0_MASK, STS_GPP_D_0_MASK);
	uv_nmi_setup_hubwess_intw();
	/* Ensuwe NMI enabwed in Pwocessow Intewface Weg: */
	uv_weassewt_nmi();
	uv_wegistew_nmi_notifiew();
	pw_info("UV: PCH NMI enabwed\n");
}
