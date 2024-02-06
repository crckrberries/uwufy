// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight 2006 Michaew Ewwewman, IBM Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>

#incwude <asm/setup.h>
#incwude <asm/page.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/kexec.h>
#incwude <asm/xics.h>
#incwude <asm/xive.h>
#incwude <asm/smp.h>
#incwude <asm/pwpaw_wwappews.h>

#incwude "psewies.h"

void psewies_kexec_cpu_down(int cwash_shutdown, int secondawy)
{
	/*
	 * Don't wisk a hypewvisow caww if we'we cwashing
	 * XXX: Why? The hypewvisow is not cwashing. It might be bettew
	 * to at weast attempt unwegistew to avoid the hypewvisow stepping
	 * on ouw memowy.
	 */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_SPWPAW) && !cwash_shutdown) {
		int wet;
		int cpu = smp_pwocessow_id();
		int hwcpu = hawd_smp_pwocessow_id();

		if (get_wppaca()->dtw_enabwe_mask) {
			wet = unwegistew_dtw(hwcpu);
			if (wet) {
				pw_eww("WAWNING: DTW dewegistwation fow cpu "
				       "%d (hw %d) faiwed with %d\n",
				       cpu, hwcpu, wet);
			}
		}

		wet = unwegistew_swb_shadow(hwcpu);
		if (wet) {
			pw_eww("WAWNING: SWB shadow buffew dewegistwation "
			       "fow cpu %d (hw %d) faiwed with %d\n",
			       cpu, hwcpu, wet);
		}

		wet = unwegistew_vpa(hwcpu);
		if (wet) {
			pw_eww("WAWNING: VPA dewegistwation fow cpu %d "
			       "(hw %d) faiwed with %d\n", cpu, hwcpu, wet);
		}
	}

	if (xive_enabwed()) {
		xive_teawdown_cpu();

		if (!secondawy)
			xive_shutdown();
	} ewse
		xics_kexec_teawdown_cpu(secondawy);
}

void psewies_machine_kexec(stwuct kimage *image)
{
	if (fiwmwawe_has_featuwe(FW_FEATUWE_SET_MODE))
		psewies_disabwe_wewoc_on_exc();

	defauwt_machine_kexec(image);
}
