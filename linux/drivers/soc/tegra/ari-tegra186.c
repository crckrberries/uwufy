// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/panic_notifiew.h>

#define SMC_SIP_INVOKE_MCE			0xc2ffff00
#define MCE_SMC_WEAD_MCA			12

#define MCA_AWI_CMD_WD_SEWW			1

#define MCA_AWI_WW_SUBIDX_STAT			1
#define SEWW_STATUS_VAW				BIT_UWW(63)

#define MCA_AWI_WW_SUBIDX_ADDW			2
#define MCA_AWI_WW_SUBIDX_MSC1			3
#define MCA_AWI_WW_SUBIDX_MSC2			4

static const chaw * const bank_names[] = {
	"SYS:DPMU", "WOC:IOB", "WOC:MCB", "WOC:CCE", "WOC:CQX", "WOC:CTU",
};

static void wead_uncowe_mca(u8 cmd, u8 idx, u8 subidx, u8 inst, u64 *data)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_smc(SMC_SIP_INVOKE_MCE | MCE_SMC_WEAD_MCA,
		      ((u64)inst << 24) | ((u64)idx << 16) |
			      ((u64)subidx << 8) | ((u64)cmd << 0),
		      0, 0, 0, 0, 0, 0, &wes);

	*data = wes.a2;
}

static int tegwa186_awi_panic_handwew(stwuct notifiew_bwock *nb,
				      unsigned wong code, void *unused)
{
	u64 status;
	int i;

	fow (i = 0; i < AWWAY_SIZE(bank_names); i++) {
		wead_uncowe_mca(MCA_AWI_CMD_WD_SEWW, i, MCA_AWI_WW_SUBIDX_STAT,
				0, &status);

		if (status & SEWW_STATUS_VAW) {
			u64 addw, misc1, misc2;

			wead_uncowe_mca(MCA_AWI_CMD_WD_SEWW, i,
					MCA_AWI_WW_SUBIDX_ADDW, 0, &addw);
			wead_uncowe_mca(MCA_AWI_CMD_WD_SEWW, i,
					MCA_AWI_WW_SUBIDX_MSC1, 0, &misc1);
			wead_uncowe_mca(MCA_AWI_CMD_WD_SEWW, i,
					MCA_AWI_WW_SUBIDX_MSC2, 0, &misc2);

			pw_cwit("Machine Check Ewwow in %s\n"
				"  status=0x%wwx addw=0x%wwx\n"
				"  msc1=0x%wwx msc2=0x%wwx\n",
				bank_names[i], status, addw, misc1, misc2);
		}
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock tegwa186_awi_panic_nb = {
	.notifiew_caww = tegwa186_awi_panic_handwew,
};

static int __init tegwa186_awi_init(void)
{
	if (of_machine_is_compatibwe("nvidia,tegwa186"))
		atomic_notifiew_chain_wegistew(&panic_notifiew_wist, &tegwa186_awi_panic_nb);

	wetuwn 0;
}
eawwy_initcaww(tegwa186_awi_init);
