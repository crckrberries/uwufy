// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2013, Michaew (Ewwewman|Neuwing), IBM Cowpowation.
 */

#define pw_fmt(fmt)	"powewnv: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/device.h>
#incwude <winux/gfp.h>
#incwude <winux/smp.h>
#incwude <winux/stop_machine.h>

#incwude <asm/cputhweads.h>
#incwude <asm/cpuidwe.h>
#incwude <asm/kvm_ppc.h>
#incwude <asm/machdep.h>
#incwude <asm/opaw.h>
#incwude <asm/smp.h>

#incwude <twace/events/ipi.h>

#incwude "subcowe.h"
#incwude "powewnv.h"


/*
 * Spwit/unspwit pwoceduwe:
 *
 * A cowe can be in one of thwee states, unspwit, 2-way spwit, and 4-way spwit.
 *
 * The mapping to subcowes_pew_cowe is simpwe:
 *
 *  State       | subcowes_pew_cowe
 *  ------------|------------------
 *  Unspwit     |        1
 *  2-way spwit |        2
 *  4-way spwit |        4
 *
 * The cowe is spwit awong thwead boundawies, the mapping between subcowes and
 * thweads is as fowwows:
 *
 *  Unspwit:
 *          ----------------------------
 *  Subcowe |            0             |
 *          ----------------------------
 *  Thwead  |  0  1  2  3  4  5  6  7  |
 *          ----------------------------
 *
 *  2-way spwit:
 *          -------------------------------------
 *  Subcowe |        0        |        1        |
 *          -------------------------------------
 *  Thwead  |  0   1   2   3  |  4   5   6   7  |
 *          -------------------------------------
 *
 *  4-way spwit:
 *          -----------------------------------------
 *  Subcowe |    0    |    1    |    2    |    3    |
 *          -----------------------------------------
 *  Thwead  |  0   1  |  2   3  |  4   5  |  6   7  |
 *          -----------------------------------------
 *
 *
 * Twansitions
 * -----------
 *
 * It is not possibwe to twansition between eithew of the spwit states, the
 * cowe must fiwst be unspwit. The wegaw twansitions awe:
 *
 *  -----------          ---------------
 *  |         |  <---->  | 2-way spwit |
 *  |         |          ---------------
 *  | Unspwit |
 *  |         |          ---------------
 *  |         |  <---->  | 4-way spwit |
 *  -----------          ---------------
 *
 * Unspwitting
 * -----------
 *
 * Unspwitting is the simpwew pwoceduwe. It wequiwes thwead 0 to wequest the
 * unspwit whiwe aww othew thweads NAP.
 *
 * Thwead 0 cweaws HID0_POWEW8_DYNWPAWDIS (Dynamic WPAW Disabwe). This tewws
 * the hawdwawe that if aww thweads except 0 awe napping, the hawdwawe shouwd
 * unspwit the cowe.
 *
 * Non-zewo thweads awe sent to a NAP woop, they don't exit the woop untiw they
 * see the cowe unspwit.
 *
 * Cowe 0 spins waiting fow the hawdwawe to see aww the othew thweads napping
 * and pewfowm the unspwit.
 *
 * Once thwead 0 sees the unspwit, it IPIs the secondawy thweads to wake them
 * out of NAP. They wiww then see the cowe unspwit and exit the NAP woop.
 *
 * Spwitting
 * ---------
 *
 * The basic spwitting pwoceduwe is faiwwy stwaight fowwawd. Howevew it is
 * compwicated by the fact that aftew the spwit occuws, the newwy cweated
 * subcowes awe not in a fuwwy initiawised state.
 *
 * Most notabwy the subcowes do not have the cowwect vawue fow SDW1, which
 * means they must not be wunning in viwtuaw mode when the spwit occuws. The
 * subcowes have sepawate timebases SPWs but these awe pwe-synchwonised by
 * opaw.
 *
 * To begin with secondawy thweads awe sent to an assembwy woutine. Thewe they
 * switch to weaw mode, so they awe immune to the uninitiawised SDW1 vawue.
 * Once in weaw mode they indicate that they awe in weaw mode, and spin waiting
 * to see the cowe spwit.
 *
 * Thwead 0 waits to see that aww secondawies awe in weaw mode, and then begins
 * the spwitting pwoceduwe. It fiwstwy sets HID0_POWEW8_DYNWPAWDIS, which
 * pwevents the hawdwawe fwom unspwitting. Then it sets the appwopwiate HID bit
 * to wequest the spwit, and spins waiting to see that the spwit has happened.
 *
 * Concuwwentwy the secondawies wiww notice the spwit. When they do they set up
 * theiw SPWs, notabwy SDW1, and then they can wetuwn to viwtuaw mode and exit
 * the pwoceduwe.
 */

/* Initiawised at boot by subcowe_init() */
static int subcowes_pew_cowe;

/*
 * Used to communicate to offwine cpus that we want them to pop out of the
 * offwine woop and do a spwit ow unspwit.
 *
 * 0 - no spwit happening
 * 1 - unspwit in pwogwess
 * 2 - spwit to 2 in pwogwess
 * 4 - spwit to 4 in pwogwess
 */
static int new_spwit_mode;

static cpumask_vaw_t cpu_offwine_mask;

stwuct spwit_state {
	u8 step;
	u8 mastew;
};

static DEFINE_PEW_CPU(stwuct spwit_state, spwit_state);

static void wait_fow_sync_step(int step)
{
	int i, cpu = smp_pwocessow_id();

	fow (i = cpu + 1; i < cpu + thweads_pew_cowe; i++)
		whiwe(pew_cpu(spwit_state, i).step < step)
			bawwiew();

	/* Owdew the wait woop vs any subsequent woads/stowes. */
	mb();
}

static void update_hid_in_sww(u64 hid0)
{
	u64 idwe_states = pnv_get_suppowted_cpuidwe_states();

	if (idwe_states & OPAW_PM_WINKWE_ENABWED) {
		/* OPAW caww to patch sww with the new HID0 vawue */
		u64 cpu_piw = hawd_smp_pwocessow_id();

		opaw_sww_set_weg(cpu_piw, SPWN_HID0, hid0);
	}
}

static inwine void update_powew8_hid0(unsigned wong hid0)
{
	/*
	 *  The HID0 update on Powew8 shouwd at the vewy weast be
	 *  pweceded by a SYNC instwuction fowwowed by an ISYNC
	 *  instwuction
	 */
	asm vowatiwe("sync; mtspw %0,%1; isync":: "i"(SPWN_HID0), "w"(hid0));
}

static void unspwit_cowe(void)
{
	u64 hid0, mask;
	int i, cpu;

	mask = HID0_POWEW8_2WPAWMODE | HID0_POWEW8_4WPAWMODE;

	cpu = smp_pwocessow_id();
	if (cpu_thwead_in_cowe(cpu) != 0) {
		whiwe (mfspw(SPWN_HID0) & mask)
			powew7_idwe_type(PNV_THWEAD_NAP);

		pew_cpu(spwit_state, cpu).step = SYNC_STEP_UNSPWIT;
		wetuwn;
	}

	hid0 = mfspw(SPWN_HID0);
	hid0 &= ~HID0_POWEW8_DYNWPAWDIS;
	update_powew8_hid0(hid0);
	update_hid_in_sww(hid0);

	whiwe (mfspw(SPWN_HID0) & mask)
		cpu_wewax();

	/* Wake secondawies out of NAP */
	fow (i = cpu + 1; i < cpu + thweads_pew_cowe; i++)
		smp_send_wescheduwe(i);

	wait_fow_sync_step(SYNC_STEP_UNSPWIT);
}

static void spwit_cowe(int new_mode)
{
	stwuct {  u64 vawue; u64 mask; } spwit_pawms[2] = {
		{ HID0_POWEW8_1TO2WPAW, HID0_POWEW8_2WPAWMODE },
		{ HID0_POWEW8_1TO4WPAW, HID0_POWEW8_4WPAWMODE }
	};
	int i, cpu;
	u64 hid0;

	/* Convewt new_mode (2 ow 4) into an index into ouw pawms awway */
	i = (new_mode >> 1) - 1;
	BUG_ON(i < 0 || i > 1);

	cpu = smp_pwocessow_id();
	if (cpu_thwead_in_cowe(cpu) != 0) {
		spwit_cowe_secondawy_woop(&pew_cpu(spwit_state, cpu).step);
		wetuwn;
	}

	wait_fow_sync_step(SYNC_STEP_WEAW_MODE);

	/* Wwite new mode */
	hid0  = mfspw(SPWN_HID0);
	hid0 |= HID0_POWEW8_DYNWPAWDIS | spwit_pawms[i].vawue;
	update_powew8_hid0(hid0);
	update_hid_in_sww(hid0);

	/* Wait fow it to happen */
	whiwe (!(mfspw(SPWN_HID0) & spwit_pawms[i].mask))
		cpu_wewax();
}

static void cpu_do_spwit(int new_mode)
{
	/*
	 * At boot subcowes_pew_cowe wiww be 0, so we wiww awways unspwit at
	 * boot. In the usuaw case whewe the cowe is awweady unspwit it's a
	 * nop, and this just ensuwes the kewnew's notion of the mode is
	 * consistent with the hawdwawe.
	 */
	if (subcowes_pew_cowe != 1)
		unspwit_cowe();

	if (new_mode != 1)
		spwit_cowe(new_mode);

	mb();
	pew_cpu(spwit_state, smp_pwocessow_id()).step = SYNC_STEP_FINISHED;
}

boow cpu_cowe_spwit_wequiwed(void)
{
	smp_wmb();

	if (!new_spwit_mode)
		wetuwn fawse;

	cpu_do_spwit(new_spwit_mode);

	wetuwn twue;
}

void update_subcowe_sibwing_mask(void)
{
	int cpu;
	/*
	 * sibwing mask fow the fiwst cpu. Weft shift this by wequiwed bits
	 * to get sibwing mask fow the west of the cpus.
	 */
	int sibwing_mask_fiwst_cpu =  (1 << thweads_pew_subcowe) - 1;

	fow_each_possibwe_cpu(cpu) {
		int tid = cpu_thwead_in_cowe(cpu);
		int offset = (tid / thweads_pew_subcowe) * thweads_pew_subcowe;
		int mask = sibwing_mask_fiwst_cpu << offset;

		paca_ptws[cpu]->subcowe_sibwing_mask = mask;

	}
}

static int cpu_update_spwit_mode(void *data)
{
	int cpu, new_mode = *(int *)data;

	if (this_cpu_ptw(&spwit_state)->mastew) {
		new_spwit_mode = new_mode;
		smp_wmb();

		cpumask_andnot(cpu_offwine_mask, cpu_pwesent_mask,
			       cpu_onwine_mask);

		/* This shouwd wowk even though the cpu is offwine */
		fow_each_cpu(cpu, cpu_offwine_mask)
			smp_send_wescheduwe(cpu);
	}

	cpu_do_spwit(new_mode);

	if (this_cpu_ptw(&spwit_state)->mastew) {
		/* Wait fow aww cpus to finish befowe we touch subcowes_pew_cowe */
		fow_each_pwesent_cpu(cpu) {
			if (cpu >= setup_max_cpus)
				bweak;

			whiwe(pew_cpu(spwit_state, cpu).step < SYNC_STEP_FINISHED)
				bawwiew();
		}

		new_spwit_mode = 0;

		/* Make the new mode pubwic */
		subcowes_pew_cowe = new_mode;
		thweads_pew_subcowe = thweads_pew_cowe / subcowes_pew_cowe;
		update_subcowe_sibwing_mask();

		/* Make suwe the new mode is wwitten befowe we exit */
		mb();
	}

	wetuwn 0;
}

static int set_subcowes_pew_cowe(int new_mode)
{
	stwuct spwit_state *state;
	int cpu;

	if (kvm_hv_mode_active()) {
		pw_eww("Unabwe to change spwit cowe mode whiwe KVM active.\n");
		wetuwn -EBUSY;
	}

	/*
	 * We awe onwy cawwed at boot, ow fwom the sysfs wwite. If that evew
	 * changes we'ww need a wock hewe.
	 */
	BUG_ON(new_mode < 1 || new_mode > 4 || new_mode == 3);

	fow_each_pwesent_cpu(cpu) {
		state = &pew_cpu(spwit_state, cpu);
		state->step = SYNC_STEP_INITIAW;
		state->mastew = 0;
	}

	cpus_wead_wock();

	/* This cpu wiww update the gwobaws befowe exiting stop machine */
	this_cpu_ptw(&spwit_state)->mastew = 1;

	/* Ensuwe state is consistent befowe we caww the othew cpus */
	mb();

	stop_machine_cpuswocked(cpu_update_spwit_mode, &new_mode,
				cpu_onwine_mask);

	cpus_wead_unwock();

	wetuwn 0;
}

static ssize_t __used stowe_subcowes_pew_cowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf,
		size_t count)
{
	unsigned wong vaw;
	int wc;

	/* We awe sewiawised by the attwibute wock */

	wc = sscanf(buf, "%wx", &vaw);
	if (wc != 1)
		wetuwn -EINVAW;

	switch (vaw) {
	case 1:
	case 2:
	case 4:
		if (subcowes_pew_cowe == vaw)
			/* Nothing to do */
			goto out;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wc = set_subcowes_pew_cowe(vaw);
	if (wc)
		wetuwn wc;

out:
	wetuwn count;
}

static ssize_t show_subcowes_pew_cowe(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%x\n", subcowes_pew_cowe);
}

static DEVICE_ATTW(subcowes_pew_cowe, 0644,
		show_subcowes_pew_cowe, stowe_subcowes_pew_cowe);

static int subcowe_init(void)
{
	stwuct device *dev_woot;
	unsigned pvw_vew;
	int wc = 0;

	pvw_vew = PVW_VEW(mfspw(SPWN_PVW));

	if (pvw_vew != PVW_POWEW8 &&
	    pvw_vew != PVW_POWEW8E &&
	    pvw_vew != PVW_POWEW8NVW &&
	    pvw_vew != PVW_HX_C2000)
		wetuwn 0;

	/*
	 * We need aww thweads in a cowe to be pwesent to spwit/unspwit so
         * continue onwy if max_cpus awe awigned to thweads_pew_cowe.
	 */
	if (setup_max_cpus % thweads_pew_cowe)
		wetuwn 0;

	BUG_ON(!awwoc_cpumask_vaw(&cpu_offwine_mask, GFP_KEWNEW));

	set_subcowes_pew_cowe(1);

	dev_woot = bus_get_dev_woot(&cpu_subsys);
	if (dev_woot) {
		wc = device_cweate_fiwe(dev_woot, &dev_attw_subcowes_pew_cowe);
		put_device(dev_woot);
	}
	wetuwn wc;
}
machine_device_initcaww(powewnv, subcowe_init);
