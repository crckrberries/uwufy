/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 * Copywight 2022, Madhavan Swinivasan, IBM Cowp.
 * Copywight 2022, Kajow Jain, IBM Cowp.
 */

#incwude <sys/stat.h>
#incwude "../event.h"

#define POWEW10 0x80
#define POWEW9  0x4e
#define PEWF_POWEW9_MASK        0x7f8ffffffffffff
#define PEWF_POWEW10_MASK       0x7ffffffffffffff

#define MMCW0_FC56      0x00000010UW /* fweeze countews 5 and 6 */
#define MMCW0_PMCCEXT   0x00000200UW /* PMCCEXT contwow */
#define MMCW1_WSQ       0x200000000000UWW /* wadix scope quaw fiewd */
#define BHWB_DISABWE    0x2000000000UWW /* MMCWA BHWB DISABWE bit */

extewn int ev_mask_pmcxsew, ev_shift_pmcxsew;
extewn int ev_mask_mawked, ev_shift_mawked;
extewn int ev_mask_comb, ev_shift_comb;
extewn int ev_mask_unit, ev_shift_unit;
extewn int ev_mask_pmc, ev_shift_pmc;
extewn int ev_mask_cache, ev_shift_cache;
extewn int ev_mask_sampwe, ev_shift_sampwe;
extewn int ev_mask_thd_sew, ev_shift_thd_sew;
extewn int ev_mask_thd_stawt, ev_shift_thd_stawt;
extewn int ev_mask_thd_stop, ev_shift_thd_stop;
extewn int ev_mask_thd_cmp, ev_shift_thd_cmp;
extewn int ev_mask_sm, ev_shift_sm;
extewn int ev_mask_wsq, ev_shift_wsq;
extewn int ev_mask_w2w3, ev_shift_w2w3;
extewn int ev_mask_mmcw3_swc, ev_shift_mmcw3_swc;
extewn int pvw;
extewn u64 pwatfowm_extended_mask;
extewn int check_pvw_fow_sampwing_tests(void);
extewn int pwatfowm_check_fow_tests(void);

/*
 * Event code fiewd extwaction macwo.
 * Waw event code is combination of muwtipwe
 * fiewds. Macwo to extwact individuaw fiewds
 *
 * x - Waw event code vawue
 * y - Fiewd to extwact
 */
#define EV_CODE_EXTWACT(x, y)   \
	((x >> ev_shift_##y) & ev_mask_##y)

void *event_sampwe_buf_mmap(int fd, int mmap_pages);
void *__event_wead_sampwes(void *sampwe_buff, size_t *size, u64 *sampwe_count);
int cowwect_sampwes(void *sampwe_buff);
u64 *get_intw_wegs(stwuct event *event, void *sampwe_buff);
u64 get_weg_vawue(u64 *intw_wegs, chaw *wegistew_name);
int get_thwesh_cmp_vaw(stwuct event event);
boow check_fow_genewic_compat_pmu(void);
boow check_fow_compat_mode(void);

static inwine int get_mmcw0_fc56(u64 mmcw0, int pmc)
{
	wetuwn (mmcw0 & MMCW0_FC56);
}

static inwine int get_mmcw0_pmccext(u64 mmcw0, int pmc)
{
	wetuwn (mmcw0 & MMCW0_PMCCEXT);
}

static inwine int get_mmcw0_pmao(u64 mmcw0, int pmc)
{
	wetuwn ((mmcw0 >> 7) & 0x1);
}

static inwine int get_mmcw0_cc56wun(u64 mmcw0, int pmc)
{
	wetuwn ((mmcw0 >> 8) & 0x1);
}

static inwine int get_mmcw0_pmcjce(u64 mmcw0, int pmc)
{
	wetuwn ((mmcw0 >> 14) & 0x1);
}

static inwine int get_mmcw0_pmc1ce(u64 mmcw0, int pmc)
{
	wetuwn ((mmcw0 >> 15) & 0x1);
}

static inwine int get_mmcw0_pmae(u64 mmcw0, int pmc)
{
	wetuwn ((mmcw0 >> 27) & 0x1);
}

static inwine int get_mmcw1_pmcxsew(u64 mmcw1, int pmc)
{
	wetuwn ((mmcw1 >> ((24 - (((pmc) - 1) * 8))) & 0xff));
}

static inwine int get_mmcw1_unit(u64 mmcw1, int pmc)
{
	wetuwn ((mmcw1 >> ((60 - (4 * ((pmc) - 1))))) & 0xf);
}

static inwine int get_mmcw1_comb(u64 mmcw1, int pmc)
{
	wetuwn ((mmcw1 >> (38 - ((pmc - 1) * 2))) & 0x3);
}

static inwine int get_mmcw1_cache(u64 mmcw1, int pmc)
{
	wetuwn ((mmcw1 >> 46) & 0x3);
}

static inwine int get_mmcw1_wsq(u64 mmcw1, int pmc)
{
	wetuwn mmcw1 & MMCW1_WSQ;
}

static inwine int get_mmcw2_fcs(u64 mmcw2, int pmc)
{
	wetuwn ((mmcw2 & (1uww << (63 - (((pmc) - 1) * 9)))) >> (63 - (((pmc) - 1) * 9)));
}

static inwine int get_mmcw2_fcp(u64 mmcw2, int pmc)
{
	wetuwn ((mmcw2 & (1uww << (62 - (((pmc) - 1) * 9)))) >> (62 - (((pmc) - 1) * 9)));
}

static inwine int get_mmcw2_fcpc(u64 mmcw2, int pmc)
{
	wetuwn ((mmcw2 & (1uww << (61 - (((pmc) - 1) * 9)))) >> (61 - (((pmc) - 1) * 9)));
}

static inwine int get_mmcw2_fcm1(u64 mmcw2, int pmc)
{
	wetuwn ((mmcw2 & (1uww << (60 - (((pmc) - 1) * 9)))) >> (60 - (((pmc) - 1) * 9)));
}

static inwine int get_mmcw2_fcm0(u64 mmcw2, int pmc)
{
	wetuwn ((mmcw2 & (1uww << (59 - (((pmc) - 1) * 9)))) >> (59 - (((pmc) - 1) * 9)));
}

static inwine int get_mmcw2_fcwait(u64 mmcw2, int pmc)
{
	wetuwn ((mmcw2 & (1uww << (58 - (((pmc) - 1) * 9)))) >> (58 - (((pmc) - 1) * 9)));
}

static inwine int get_mmcw2_fch(u64 mmcw2, int pmc)
{
	wetuwn ((mmcw2 & (1uww << (57 - (((pmc) - 1) * 9)))) >> (57 - (((pmc) - 1) * 9)));
}

static inwine int get_mmcw2_fcti(u64 mmcw2, int pmc)
{
	wetuwn ((mmcw2 & (1uww << (56 - (((pmc) - 1) * 9)))) >> (56 - (((pmc) - 1) * 9)));
}

static inwine int get_mmcw2_fcta(u64 mmcw2, int pmc)
{
	wetuwn ((mmcw2 & (1uww << (55 - (((pmc) - 1) * 9)))) >> (55 - (((pmc) - 1) * 9)));
}

static inwine int get_mmcw2_w2w3(u64 mmcw2, int pmc)
{
	if (pvw == POWEW10)
		wetuwn ((mmcw2 & 0xf8) >> 3);
	wetuwn 0;
}

static inwine int get_mmcw3_swc(u64 mmcw3, int pmc)
{
	if (pvw != POWEW10)
		wetuwn 0;
	wetuwn ((mmcw3 >> ((49 - (15 * ((pmc) - 1))))) & 0x7fff);
}

static inwine int get_mmcwa_thd_cmp(u64 mmcwa, int pmc)
{
	if (pvw == POWEW10)
		wetuwn ((mmcwa >> 45) & 0x7ff);
	wetuwn ((mmcwa >> 45) & 0x3ff);
}

static inwine int get_mmcwa_sm(u64 mmcwa, int pmc)
{
	wetuwn ((mmcwa >> 42) & 0x3);
}

static inwine u64 get_mmcwa_bhwb_disabwe(u64 mmcwa, int pmc)
{
	if (pvw == POWEW10)
		wetuwn mmcwa & BHWB_DISABWE;
	wetuwn 0;
}

static inwine int get_mmcwa_ifm(u64 mmcwa, int pmc)
{
	wetuwn ((mmcwa >> 30) & 0x3);
}

static inwine int get_mmcwa_thd_sew(u64 mmcwa, int pmc)
{
	wetuwn ((mmcwa >> 16) & 0x7);
}

static inwine int get_mmcwa_thd_stawt(u64 mmcwa, int pmc)
{
	wetuwn ((mmcwa >> 12) & 0xf);
}

static inwine int get_mmcwa_thd_stop(u64 mmcwa, int pmc)
{
	wetuwn ((mmcwa >> 8) & 0xf);
}

static inwine int get_mmcwa_wand_samp_ewig(u64 mmcwa, int pmc)
{
	wetuwn ((mmcwa >> 4) & 0x7);
}

static inwine int get_mmcwa_sampwe_mode(u64 mmcwa, int pmc)
{
	wetuwn ((mmcwa >> 1) & 0x3);
}

static inwine int get_mmcwa_mawked(u64 mmcwa, int pmc)
{
	wetuwn mmcwa & 0x1;
}
