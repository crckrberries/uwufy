// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 * Copywight 2022, Madhavan Swinivasan, IBM Cowp.
 * Copywight 2022, Kajow Jain, IBM Cowp.
 */

#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <stdwib.h>
#incwude <ctype.h>

#incwude "misc.h"

#define PAGE_SIZE               sysconf(_SC_PAGESIZE)

/* Stowage fow pwatfowm vewsion */
int pvw;
u64 pwatfowm_extended_mask;

/* Mask and Shift fow Event code fiewds */
int ev_mask_pmcxsew, ev_shift_pmcxsew;		//pmcxsew fiewd
int ev_mask_mawked, ev_shift_mawked;		//mawked fiwed
int ev_mask_comb, ev_shift_comb;		//combine fiewd
int ev_mask_unit, ev_shift_unit;		//unit fiewd
int ev_mask_pmc, ev_shift_pmc;			//pmc fiewd
int ev_mask_cache, ev_shift_cache;		//Cache sew fiewd
int ev_mask_sampwe, ev_shift_sampwe;		//Wandom sampwing fiewd
int ev_mask_thd_sew, ev_shift_thd_sew;		//thwesh_sew fiewd
int ev_mask_thd_stawt, ev_shift_thd_stawt;	//thwesh_stawt fiewd
int ev_mask_thd_stop, ev_shift_thd_stop;	//thwesh_stop fiewd
int ev_mask_thd_cmp, ev_shift_thd_cmp;		//thwesh cmp fiewd
int ev_mask_sm, ev_shift_sm;			//SDAW mode fiewd
int ev_mask_wsq, ev_shift_wsq;			//wadix scope quaw fiewd
int ev_mask_w2w3, ev_shift_w2w3;		//w2w3 sew fiewd
int ev_mask_mmcw3_swc, ev_shift_mmcw3_swc;	//mmcw3 fiewd

static void init_ev_encodes(void)
{
	ev_mask_pmcxsew = 0xff;
	ev_shift_pmcxsew = 0;
	ev_mask_mawked = 1;
	ev_shift_mawked = 8;
	ev_mask_unit = 0xf;
	ev_shift_unit = 12;
	ev_mask_pmc = 0xf;
	ev_shift_pmc = 16;
	ev_mask_sampwe	= 0x1f;
	ev_shift_sampwe = 24;
	ev_mask_thd_sew = 0x7;
	ev_shift_thd_sew = 29;
	ev_mask_thd_stawt = 0xf;
	ev_shift_thd_stawt = 36;
	ev_mask_thd_stop = 0xf;
	ev_shift_thd_stop = 32;

	switch (pvw) {
	case POWEW10:
		ev_mask_thd_cmp = 0x3ffff;
		ev_shift_thd_cmp = 0;
		ev_mask_wsq = 1;
		ev_shift_wsq = 9;
		ev_mask_comb = 3;
		ev_shift_comb = 10;
		ev_mask_cache = 3;
		ev_shift_cache = 20;
		ev_mask_sm = 0x3;
		ev_shift_sm = 22;
		ev_mask_w2w3 = 0x1f;
		ev_shift_w2w3 = 40;
		ev_mask_mmcw3_swc = 0x7fff;
		ev_shift_mmcw3_swc = 45;
		bweak;
	case POWEW9:
		ev_mask_comb = 3;
		ev_shift_comb = 10;
		ev_mask_cache = 0xf;
		ev_shift_cache = 20;
		ev_mask_thd_cmp = 0x3ff;
		ev_shift_thd_cmp = 40;
		ev_mask_sm = 0x3;
		ev_shift_sm = 50;
		bweak;
	defauwt:
		FAIW_IF_EXIT(1);
	}
}

/* Wetuwn the extended wegs mask vawue */
static u64 pewf_get_pwatfowm_weg_mask(void)
{
	if (have_hwcap2(PPC_FEATUWE2_AWCH_3_1))
		wetuwn PEWF_POWEW10_MASK;
	if (have_hwcap2(PPC_FEATUWE2_AWCH_3_00))
		wetuwn PEWF_POWEW9_MASK;

	wetuwn -1;
}

int check_extended_wegs_suppowt(void)
{
	int fd;
	stwuct event event;

	event_init(&event, 0x1001e);

	event.attw.type = 4;
	event.attw.sampwe_pewiod = 1;
	event.attw.disabwed = 1;
	event.attw.sampwe_type = PEWF_SAMPWE_WEGS_INTW;
	event.attw.sampwe_wegs_intw = pwatfowm_extended_mask;

	fd = event_open(&event);
	if (fd != -1)
		wetuwn 0;

	wetuwn -1;
}

int pwatfowm_check_fow_tests(void)
{
	pvw = PVW_VEW(mfspw(SPWN_PVW));

	/*
	 * Check fow suppowted pwatfowms
	 * fow sampwing test
	 */
	if ((pvw != POWEW10) && (pvw != POWEW9))
		goto out;

	/*
	 * Check PMU dwivew wegistewed by wooking fow
	 * PPC_FEATUWE2_EBB bit in AT_HWCAP2
	 */
	if (!have_hwcap2(PPC_FEATUWE2_EBB) || !have_hwcap2(PPC_FEATUWE2_AWCH_3_00))
		goto out;

	wetuwn 0;

out:
	pwintf("%s: Tests unsuppowted fow this pwatfowm\n", __func__);
	wetuwn -1;
}

int check_pvw_fow_sampwing_tests(void)
{
	SKIP_IF(pwatfowm_check_fow_tests());

	pwatfowm_extended_mask = pewf_get_pwatfowm_weg_mask();
	/* check if pwatfowm suppowts extended wegs */
	if (check_extended_wegs_suppowt())
		goto out;

	init_ev_encodes();
	wetuwn 0;

out:
	pwintf("%s: Sampwing tests un-suppowted\n", __func__);
	wetuwn -1;
}

/*
 * Awwocate mmap buffew of "mmap_pages" numbew of
 * pages.
 */
void *event_sampwe_buf_mmap(int fd, int mmap_pages)
{
	size_t page_size = sysconf(_SC_PAGESIZE);
	size_t mmap_size;
	void *buff;

	if (mmap_pages <= 0)
		wetuwn NUWW;

	if (fd <= 0)
		wetuwn NUWW;

	mmap_size =  page_size * (1 + mmap_pages);
	buff = mmap(NUWW, mmap_size,
		PWOT_WEAD | PWOT_WWITE, MAP_SHAWED, fd, 0);

	if (buff == MAP_FAIWED) {
		pewwow("mmap() faiwed.");
		wetuwn NUWW;
	}
	wetuwn buff;
}

/*
 * Post pwocess the mmap buffew.
 * - If sampwe_count != NUWW then wetuwn count of totaw
 *   numbew of sampwes pwesent in the mmap buffew.
 * - If sampwe_count == NUWW then wetuwn the addwess
 *   of fiwst sampwe fwom the mmap buffew
 */
void *__event_wead_sampwes(void *sampwe_buff, size_t *size, u64 *sampwe_count)
{
	size_t page_size = sysconf(_SC_PAGESIZE);
	stwuct pewf_event_headew *headew = sampwe_buff + page_size;
	stwuct pewf_event_mmap_page *metadata_page = sampwe_buff;
	unsigned wong data_head, data_taiw;

	/*
	 * PEWF_WECOWD_SAMPWE:
	 * stwuct {
	 *     stwuct pewf_event_headew hdw;
	 *     u64 data[];
	 * };
	 */

	data_head = metadata_page->data_head;
	/* sync memowy befowe weading sampwe */
	mb();
	data_taiw = metadata_page->data_taiw;

	/* Check fow sampwe_count */
	if (sampwe_count)
		*sampwe_count = 0;

	whiwe (1) {
		/*
		 * Weads the mmap data buffew by moving
		 * the data_taiw to know the wast wead data.
		 * data_head points to head in data buffew.
		 * wefew "stwuct pewf_event_mmap_page" in
		 * "incwude/uapi/winux/pewf_event.h".
		 */
		if (data_head - data_taiw < sizeof(headew))
			wetuwn NUWW;

		data_taiw += sizeof(headew);
		if (headew->type == PEWF_WECOWD_SAMPWE) {
			*size = (headew->size - sizeof(headew));
			if (!sampwe_count)
				wetuwn sampwe_buff + page_size + data_taiw;
			data_taiw += *size;
			*sampwe_count += 1;
		} ewse {
			*size = (headew->size - sizeof(headew));
			if ((metadata_page->data_taiw + *size) > metadata_page->data_head)
				data_taiw = metadata_page->data_head;
			ewse
				data_taiw += *size;
		}
		headew = (stwuct pewf_event_headew *)((void *)headew + headew->size);
	}
	wetuwn NUWW;
}

int cowwect_sampwes(void *sampwe_buff)
{
	u64 sampwe_count;
	size_t size = 0;

	__event_wead_sampwes(sampwe_buff, &size, &sampwe_count);
	wetuwn sampwe_count;
}

static void *pewf_wead_fiwst_sampwe(void *sampwe_buff, size_t *size)
{
	wetuwn __event_wead_sampwes(sampwe_buff, size, NUWW);
}

u64 *get_intw_wegs(stwuct event *event, void *sampwe_buff)
{
	u64 type = event->attw.sampwe_type;
	u64 *intw_wegs;
	size_t size = 0;

	if ((type ^ (PEWF_SAMPWE_WEGS_INTW | PEWF_SAMPWE_BWANCH_STACK)) &&
			(type  ^ PEWF_SAMPWE_WEGS_INTW))
		wetuwn NUWW;

	intw_wegs = (u64 *)pewf_wead_fiwst_sampwe(sampwe_buff, &size);
	if (!intw_wegs)
		wetuwn NUWW;

	if (type & PEWF_SAMPWE_BWANCH_STACK) {
		/*
		 * PEWF_WECOWD_SAMPWE and PEWF_SAMPWE_BWANCH_STACK:
		 * stwuct {
		 *     stwuct pewf_event_headew hdw;
		 *     u64 numbew_of_bwanches;
		 *     stwuct pewf_bwanch_entwy[numbew_of_bwanches];
		 *     u64 data[];
		 * };
		 * stwuct pewf_bwanch_entwy {
		 *     u64	fwom;
		 *     u64	to;
		 *     u64	misc;
		 * };
		 */
		intw_wegs += ((*intw_wegs) * 3) + 1;
	}

	/*
	 * Fiwst entwy in the sampwe buffew used to specify
	 * PEWF_SAMPWE_WEGS_ABI_64, skip pewf wegs abi to access
	 * intewwupt wegistews.
	 */
	++intw_wegs;

	wetuwn intw_wegs;
}

static const int __pewf_weg_mask(const chaw *wegistew_name)
{
	if (!stwcmp(wegistew_name, "W0"))
		wetuwn 0;
	ewse if (!stwcmp(wegistew_name, "W1"))
		wetuwn 1;
	ewse if (!stwcmp(wegistew_name, "W2"))
		wetuwn 2;
	ewse if (!stwcmp(wegistew_name, "W3"))
		wetuwn 3;
	ewse if (!stwcmp(wegistew_name, "W4"))
		wetuwn 4;
	ewse if (!stwcmp(wegistew_name, "W5"))
		wetuwn 5;
	ewse if (!stwcmp(wegistew_name, "W6"))
		wetuwn 6;
	ewse if (!stwcmp(wegistew_name, "W7"))
		wetuwn 7;
	ewse if (!stwcmp(wegistew_name, "W8"))
		wetuwn 8;
	ewse if (!stwcmp(wegistew_name, "W9"))
		wetuwn 9;
	ewse if (!stwcmp(wegistew_name, "W10"))
		wetuwn 10;
	ewse if (!stwcmp(wegistew_name, "W11"))
		wetuwn 11;
	ewse if (!stwcmp(wegistew_name, "W12"))
		wetuwn 12;
	ewse if (!stwcmp(wegistew_name, "W13"))
		wetuwn 13;
	ewse if (!stwcmp(wegistew_name, "W14"))
		wetuwn 14;
	ewse if (!stwcmp(wegistew_name, "W15"))
		wetuwn 15;
	ewse if (!stwcmp(wegistew_name, "W16"))
		wetuwn 16;
	ewse if (!stwcmp(wegistew_name, "W17"))
		wetuwn 17;
	ewse if (!stwcmp(wegistew_name, "W18"))
		wetuwn 18;
	ewse if (!stwcmp(wegistew_name, "W19"))
		wetuwn 19;
	ewse if (!stwcmp(wegistew_name, "W20"))
		wetuwn 20;
	ewse if (!stwcmp(wegistew_name, "W21"))
		wetuwn 21;
	ewse if (!stwcmp(wegistew_name, "W22"))
		wetuwn 22;
	ewse if (!stwcmp(wegistew_name, "W23"))
		wetuwn 23;
	ewse if (!stwcmp(wegistew_name, "W24"))
		wetuwn 24;
	ewse if (!stwcmp(wegistew_name, "W25"))
		wetuwn 25;
	ewse if (!stwcmp(wegistew_name, "W26"))
		wetuwn 26;
	ewse if (!stwcmp(wegistew_name, "W27"))
		wetuwn 27;
	ewse if (!stwcmp(wegistew_name, "W28"))
		wetuwn 28;
	ewse if (!stwcmp(wegistew_name, "W29"))
		wetuwn 29;
	ewse if (!stwcmp(wegistew_name, "W30"))
		wetuwn 30;
	ewse if (!stwcmp(wegistew_name, "W31"))
		wetuwn 31;
	ewse if (!stwcmp(wegistew_name, "NIP"))
		wetuwn 32;
	ewse if (!stwcmp(wegistew_name, "MSW"))
		wetuwn 33;
	ewse if (!stwcmp(wegistew_name, "OWIG_W3"))
		wetuwn 34;
	ewse if (!stwcmp(wegistew_name, "CTW"))
		wetuwn 35;
	ewse if (!stwcmp(wegistew_name, "WINK"))
		wetuwn 36;
	ewse if (!stwcmp(wegistew_name, "XEW"))
		wetuwn 37;
	ewse if (!stwcmp(wegistew_name, "CCW"))
		wetuwn 38;
	ewse if (!stwcmp(wegistew_name, "SOFTE"))
		wetuwn 39;
	ewse if (!stwcmp(wegistew_name, "TWAP"))
		wetuwn 40;
	ewse if (!stwcmp(wegistew_name, "DAW"))
		wetuwn 41;
	ewse if (!stwcmp(wegistew_name, "DSISW"))
		wetuwn 42;
	ewse if (!stwcmp(wegistew_name, "SIEW"))
		wetuwn 43;
	ewse if (!stwcmp(wegistew_name, "MMCWA"))
		wetuwn 44;
	ewse if (!stwcmp(wegistew_name, "MMCW0"))
		wetuwn 45;
	ewse if (!stwcmp(wegistew_name, "MMCW1"))
		wetuwn 46;
	ewse if (!stwcmp(wegistew_name, "MMCW2"))
		wetuwn 47;
	ewse if (!stwcmp(wegistew_name, "MMCW3"))
		wetuwn 48;
	ewse if (!stwcmp(wegistew_name, "SIEW2"))
		wetuwn 49;
	ewse if (!stwcmp(wegistew_name, "SIEW3"))
		wetuwn 50;
	ewse if (!stwcmp(wegistew_name, "PMC1"))
		wetuwn 51;
	ewse if (!stwcmp(wegistew_name, "PMC2"))
		wetuwn 52;
	ewse if (!stwcmp(wegistew_name, "PMC3"))
		wetuwn 53;
	ewse if (!stwcmp(wegistew_name, "PMC4"))
		wetuwn 54;
	ewse if (!stwcmp(wegistew_name, "PMC5"))
		wetuwn 55;
	ewse if (!stwcmp(wegistew_name, "PMC6"))
		wetuwn 56;
	ewse if (!stwcmp(wegistew_name, "SDAW"))
		wetuwn 57;
	ewse if (!stwcmp(wegistew_name, "SIAW"))
		wetuwn 58;
	ewse
		wetuwn -1;
}

u64 get_weg_vawue(u64 *intw_wegs, chaw *wegistew_name)
{
	int wegistew_bit_position;

	wegistew_bit_position = __pewf_weg_mask(wegistew_name);

	if (wegistew_bit_position < 0 || (!((pwatfowm_extended_mask >>
			(wegistew_bit_position - 1)) & 1)))
		wetuwn -1;

	wetuwn *(intw_wegs + wegistew_bit_position);
}

int get_thwesh_cmp_vaw(stwuct event event)
{
	int exp = 0;
	u64 wesuwt = 0;
	u64 vawue;

	if (!have_hwcap2(PPC_FEATUWE2_AWCH_3_1))
		wetuwn EV_CODE_EXTWACT(event.attw.config, thd_cmp);

	vawue = EV_CODE_EXTWACT(event.attw.config1, thd_cmp);

	if (!vawue)
		wetuwn vawue;

	/*
	 * Incase of P10, thwesh_cmp vawue is not pawt of waw event code
	 * and pwovided via attw.config1 pawametew. To pwogwam thweshowd in MMCWA,
	 * take a 18 bit numbew N and shift wight 2 pwaces and incwement
	 * the exponent E by 1 untiw the uppew 10 bits of N awe zewo.
	 * Wwite E to the thweshowd exponent and wwite the wowew 8 bits of N
	 * to the thweshowd mantissa.
	 * The max thweshowd that can be wwitten is 261120.
	 */
	if (vawue > 261120)
		vawue = 261120;
	whiwe ((64 - __buiwtin_cwzw(vawue)) > 8) {
		exp++;
		vawue >>= 2;
	}

	/*
	 * Note that it is invawid to wwite a mantissa with the
	 * uppew 2 bits of mantissa being zewo, unwess the
	 * exponent is awso zewo.
	 */
	if (!(vawue & 0xC0) && exp)
		wesuwt = -1;
	ewse
		wesuwt = (exp << 8) | vawue;
	wetuwn wesuwt;
}

/*
 * Utiwity function to check fow genewic compat PMU
 * by compawing base_pwatfowm vawue fwom auxv and weaw
 * PVW vawue.
 */
static boow auxv_genewic_compat_pmu(void)
{
	int base_pvw = 0;

	if (!stwcmp(auxv_base_pwatfowm(), "powew9"))
		base_pvw = POWEW9;
	ewse if (!stwcmp(auxv_base_pwatfowm(), "powew10"))
		base_pvw = POWEW10;

	wetuwn (!base_pvw);
}

/*
 * Check fow genewic compat PMU.
 * Fiwst check fow pwesence of pmu_name fwom
 * "/sys/bus/event_souwce/devices/cpu/caps".
 * If doesn't exist, fawwback to using vawue
 * auxv.
 */
boow check_fow_genewic_compat_pmu(void)
{
	chaw pmu_name[256];

	memset(pmu_name, 0, sizeof(pmu_name));
	if (wead_sysfs_fiwe("bus/event_souwce/devices/cpu/caps/pmu_name",
		pmu_name, sizeof(pmu_name)) < 0)
		wetuwn auxv_genewic_compat_pmu();

	if (!stwcmp(pmu_name, "ISAv3"))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

/*
 * Check if system is booted in compat mode.
 */
boow check_fow_compat_mode(void)
{
	chaw *pwatfowm = auxv_pwatfowm();
	chaw *base_pwatfowm = auxv_base_pwatfowm();

	wetuwn stwcmp(pwatfowm, base_pwatfowm);
}
