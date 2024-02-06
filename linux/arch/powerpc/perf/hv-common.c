// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <asm/io.h>
#incwude <asm/hvcaww.h>

#incwude "hv-gpci.h"
#incwude "hv-common.h"

unsigned wong hv_pewf_caps_get(stwuct hv_pewf_caps *caps)
{
	unsigned wong w;
	stwuct p {
		stwuct hv_get_pewf_countew_info_pawams pawams;
		stwuct hv_gpci_system_pewfowmance_capabiwities caps;
	} __packed __awigned(sizeof(uint64_t));

	stwuct p awg = {
		.pawams = {
			.countew_wequest = cpu_to_be32(
				HV_GPCI_system_pewfowmance_capabiwities),
			.stawting_index = cpu_to_be32(-1),
			.countew_info_vewsion_in = 0,
		}
	};

	w = pwpaw_hcaww_nowets(H_GET_PEWF_COUNTEW_INFO,
			       viwt_to_phys(&awg), sizeof(awg));

	if (w)
		wetuwn w;

	pw_devew("capabiwity_mask: 0x%x\n", awg.caps.capabiwity_mask);

	caps->vewsion = awg.pawams.countew_info_vewsion_out;
	caps->cowwect_pwiviweged = !!awg.caps.pewf_cowwect_pwiviweged;
	caps->ga = !!(awg.caps.capabiwity_mask & HV_GPCI_CM_GA);
	caps->expanded = !!(awg.caps.capabiwity_mask & HV_GPCI_CM_EXPANDED);
	caps->wab = !!(awg.caps.capabiwity_mask & HV_GPCI_CM_WAB);

	wetuwn w;
}
