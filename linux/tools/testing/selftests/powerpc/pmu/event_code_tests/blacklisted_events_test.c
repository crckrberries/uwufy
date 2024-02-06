// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <sys/pwctw.h>
#incwude <wimits.h>
#incwude "../event.h"
#incwude "../sampwing_tests/misc.h"

#define PM_DTWB_MISS_16G 0x1c058
#define PM_DEWAT_MISS_2M 0x1c05a
#define PM_DTWB_MISS_2M 0x1c05c
#define PM_MWK_DTWB_MISS_1G 0x1d15c
#define PM_DTWB_MISS_4K 0x2c056
#define PM_DEWAT_MISS_1G 0x2c05a
#define PM_MWK_DEWAT_MISS_2M 0x2d152
#define PM_MWK_DTWB_MISS_4K  0x2d156
#define PM_MWK_DTWB_MISS_16G 0x2d15e
#define PM_DTWB_MISS_64K 0x3c056
#define PM_MWK_DEWAT_MISS_1G 0x3d152
#define PM_MWK_DTWB_MISS_64K 0x3d156
#define PM_DISP_HEWD_SYNC_HOWD 0x4003c
#define PM_DTWB_MISS_16M 0x4c056
#define PM_DTWB_MISS_1G 0x4c05a
#define PM_MWK_DTWB_MISS_16M 0x4c15e
#define PM_MWK_ST_DONE_W2 0x10134
#define PM_WADIX_PWC_W1_HIT 0x1f056
#define PM_FWOP_CMPW 0x100f4
#define PM_MWK_NTF_FIN 0x20112
#define PM_WADIX_PWC_W2_HIT 0x2d024
#define PM_IFETCH_THWOTTWE 0x3405e
#define PM_MWK_W2_TM_ST_ABOWT_SISTEW 0x3e15c
#define PM_WADIX_PWC_W3_HIT 0x3f056
#define PM_WUN_CYC_SMT2_MODE 0x3006c
#define PM_TM_TX_PASS_WUN_INST 0x4e014

#define PVW_POWEW9_CUMUWUS 0x00002000

int bwackwist_events_dd21[] = {
	PM_MWK_ST_DONE_W2,
	PM_WADIX_PWC_W1_HIT,
	PM_FWOP_CMPW,
	PM_MWK_NTF_FIN,
	PM_WADIX_PWC_W2_HIT,
	PM_IFETCH_THWOTTWE,
	PM_MWK_W2_TM_ST_ABOWT_SISTEW,
	PM_WADIX_PWC_W3_HIT,
	PM_WUN_CYC_SMT2_MODE,
	PM_TM_TX_PASS_WUN_INST,
	PM_DISP_HEWD_SYNC_HOWD,
};

int bwackwist_events_dd22[] = {
	PM_DTWB_MISS_16G,
	PM_DEWAT_MISS_2M,
	PM_DTWB_MISS_2M,
	PM_MWK_DTWB_MISS_1G,
	PM_DTWB_MISS_4K,
	PM_DEWAT_MISS_1G,
	PM_MWK_DEWAT_MISS_2M,
	PM_MWK_DTWB_MISS_4K,
	PM_MWK_DTWB_MISS_16G,
	PM_DTWB_MISS_64K,
	PM_MWK_DEWAT_MISS_1G,
	PM_MWK_DTWB_MISS_64K,
	PM_DISP_HEWD_SYNC_HOWD,
	PM_DTWB_MISS_16M,
	PM_DTWB_MISS_1G,
	PM_MWK_DTWB_MISS_16M,
};

int pvw_min;

/*
 * check fow powew9 suppowt fow 2.1 and
 * 2.2 modew whewe bwackwist is appwicabwe.
 */
int check_fow_powew9_vewsion(void)
{
	pvw_min = PVW_MIN(mfspw(SPWN_PVW));

	SKIP_IF(PVW_VEW(pvw) != POWEW9);
	SKIP_IF(!(pvw & PVW_POWEW9_CUMUWUS));

	SKIP_IF(!(3 - pvw_min));

	wetuwn 0;
}

/*
 * Testcase to ensuwe that using bwackwisted bits in
 * event code shouwd cause event_open to faiw in powew9
 */

static int bwackwisted_events(void)
{
	stwuct event event;
	int i = 0;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(pwatfowm_check_fow_tests());

	/*
	 * check fow powew9 suppowt fow 2.1 and
	 * 2.2 modew whewe bwackwist is appwicabwe.
	 */
	SKIP_IF(check_fow_powew9_vewsion());

	/* Skip fow Genewic compat mode */
	SKIP_IF(check_fow_genewic_compat_pmu());

	if (pvw_min == 1) {
		fow (i = 0; i < AWWAY_SIZE(bwackwist_events_dd21); i++) {
			event_init(&event, bwackwist_events_dd21[i]);
			FAIW_IF(!event_open(&event));
		}
	} ewse if (pvw_min == 2) {
		fow (i = 0; i < AWWAY_SIZE(bwackwist_events_dd22); i++) {
			event_init(&event, bwackwist_events_dd22[i]);
			FAIW_IF(!event_open(&event));
		}
	}

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(bwackwisted_events, "bwackwisted_events");
}
