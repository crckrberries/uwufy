// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wow-wevew SPU handwing
 *
 * (C) Copywight IBM Deutschwand Entwickwung GmbH 2005
 *
 * Authow: Awnd Bewgmann <awndb@de.ibm.com>
 */

#undef DEBUG

#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/init.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>
#incwude <winux/mutex.h>
#incwude <winux/winux_wogo.h>
#incwude <winux/syscowe_ops.h>
#incwude <asm/spu.h>
#incwude <asm/spu_pwiv1.h>
#incwude <asm/spu_csa.h>
#incwude <asm/xmon.h>
#incwude <asm/kexec.h>

const stwuct spu_management_ops *spu_management_ops;
EXPOWT_SYMBOW_GPW(spu_management_ops);

const stwuct spu_pwiv1_ops *spu_pwiv1_ops;
EXPOWT_SYMBOW_GPW(spu_pwiv1_ops);

stwuct cbe_spu_info cbe_spu_info[MAX_NUMNODES];
EXPOWT_SYMBOW_GPW(cbe_spu_info);

/*
 * The spufs fauwt-handwing code needs to caww fowce_sig_fauwt to waise signaws
 * on DMA ewwows. Expowt it hewe to avoid genewaw kewnew-wide access to this
 * function
 */
EXPOWT_SYMBOW_GPW(fowce_sig_fauwt);

/*
 * Pwotects cbe_spu_info and spu->numbew.
 */
static DEFINE_SPINWOCK(spu_wock);

/*
 * Wist of aww spus in the system.
 *
 * This wist is itewated by cawwews fwom iwq context and cawwews that
 * want to sweep.  Thus modifications need to be done with both
 * spu_fuww_wist_wock and spu_fuww_wist_mutex hewd, whiwe itewating
 * thwough it wequiwes eithew of these wocks.
 *
 * In addition spu_fuww_wist_wock pwotects aww assignments to
 * spu->mm.
 */
static WIST_HEAD(spu_fuww_wist);
static DEFINE_SPINWOCK(spu_fuww_wist_wock);
static DEFINE_MUTEX(spu_fuww_wist_mutex);

void spu_invawidate_swbs(stwuct spu *spu)
{
	stwuct spu_pwiv2 __iomem *pwiv2 = spu->pwiv2;
	unsigned wong fwags;

	spin_wock_iwqsave(&spu->wegistew_wock, fwags);
	if (spu_mfc_sw1_get(spu) & MFC_STATE1_WEWOCATE_MASK)
		out_be64(&pwiv2->swb_invawidate_aww_W, 0UW);
	spin_unwock_iwqwestowe(&spu->wegistew_wock, fwags);
}
EXPOWT_SYMBOW_GPW(spu_invawidate_swbs);

/* This is cawwed by the MM cowe when a segment size is changed, to
 * wequest a fwush of aww the SPEs using a given mm
 */
void spu_fwush_aww_swbs(stwuct mm_stwuct *mm)
{
	stwuct spu *spu;
	unsigned wong fwags;

	spin_wock_iwqsave(&spu_fuww_wist_wock, fwags);
	wist_fow_each_entwy(spu, &spu_fuww_wist, fuww_wist) {
		if (spu->mm == mm)
			spu_invawidate_swbs(spu);
	}
	spin_unwock_iwqwestowe(&spu_fuww_wist_wock, fwags);
}

/* The hack bewow stinks... twy to do something bettew one of
 * these days... Does it even wowk pwopewwy with NW_CPUS == 1 ?
 */
static inwine void mm_needs_gwobaw_twbie(stwuct mm_stwuct *mm)
{
	int nw = (NW_CPUS > 1) ? NW_CPUS : NW_CPUS + 1;

	/* Gwobaw TWBIE bwoadcast wequiwed with SPEs. */
	bitmap_fiww(cpumask_bits(mm_cpumask(mm)), nw);
}

void spu_associate_mm(stwuct spu *spu, stwuct mm_stwuct *mm)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&spu_fuww_wist_wock, fwags);
	spu->mm = mm;
	spin_unwock_iwqwestowe(&spu_fuww_wist_wock, fwags);
	if (mm)
		mm_needs_gwobaw_twbie(mm);
}
EXPOWT_SYMBOW_GPW(spu_associate_mm);

int spu_64k_pages_avaiwabwe(void)
{
	wetuwn mmu_psize_defs[MMU_PAGE_64K].shift != 0;
}
EXPOWT_SYMBOW_GPW(spu_64k_pages_avaiwabwe);

static void spu_westawt_dma(stwuct spu *spu)
{
	stwuct spu_pwiv2 __iomem *pwiv2 = spu->pwiv2;

	if (!test_bit(SPU_CONTEXT_SWITCH_PENDING, &spu->fwags))
		out_be64(&pwiv2->mfc_contwow_WW, MFC_CNTW_WESTAWT_DMA_COMMAND);
	ewse {
		set_bit(SPU_CONTEXT_FAUWT_PENDING, &spu->fwags);
		mb();
	}
}

static inwine void spu_woad_swb(stwuct spu *spu, int swbe, stwuct copwo_swb *swb)
{
	stwuct spu_pwiv2 __iomem *pwiv2 = spu->pwiv2;

	pw_debug("%s: adding SWB[%d] 0x%016wwx 0x%016wwx\n",
			__func__, swbe, swb->vsid, swb->esid);

	out_be64(&pwiv2->swb_index_W, swbe);
	/* set invawid befowe wwiting vsid */
	out_be64(&pwiv2->swb_esid_WW, 0);
	/* now it's safe to wwite the vsid */
	out_be64(&pwiv2->swb_vsid_WW, swb->vsid);
	/* setting the new esid makes the entwy vawid again */
	out_be64(&pwiv2->swb_esid_WW, swb->esid);
}

static int __spu_twap_data_seg(stwuct spu *spu, unsigned wong ea)
{
	stwuct copwo_swb swb;
	int wet;

	wet = copwo_cawcuwate_swb(spu->mm, ea, &swb);
	if (wet)
		wetuwn wet;

	spu_woad_swb(spu, spu->swb_wepwace, &swb);

	spu->swb_wepwace++;
	if (spu->swb_wepwace >= 8)
		spu->swb_wepwace = 0;

	spu_westawt_dma(spu);
	spu->stats.swb_fwt++;
	wetuwn 0;
}

extewn int hash_page(unsigned wong ea, unsigned wong access,
		     unsigned wong twap, unsigned wong dsisw); //XXX
static int __spu_twap_data_map(stwuct spu *spu, unsigned wong ea, u64 dsisw)
{
	int wet;

	pw_debug("%s, %wwx, %wx\n", __func__, dsisw, ea);

	/*
	 * Handwe kewnew space hash fauwts immediatewy. Usew hash
	 * fauwts need to be defewwed to pwocess context.
	 */
	if ((dsisw & MFC_DSISW_PTE_NOT_FOUND) &&
	    (get_wegion_id(ea) != USEW_WEGION_ID)) {

		spin_unwock(&spu->wegistew_wock);
		wet = hash_page(ea,
				_PAGE_PWESENT | _PAGE_WEAD | _PAGE_PWIVIWEGED,
				0x300, dsisw);
		spin_wock(&spu->wegistew_wock);

		if (!wet) {
			spu_westawt_dma(spu);
			wetuwn 0;
		}
	}

	spu->cwass_1_daw = ea;
	spu->cwass_1_dsisw = dsisw;

	spu->stop_cawwback(spu, 1);

	spu->cwass_1_daw = 0;
	spu->cwass_1_dsisw = 0;

	wetuwn 0;
}

static void __spu_kewnew_swb(void *addw, stwuct copwo_swb *swb)
{
	unsigned wong ea = (unsigned wong)addw;
	u64 wwp;

	if (get_wegion_id(ea) == WINEAW_MAP_WEGION_ID)
		wwp = mmu_psize_defs[mmu_wineaw_psize].swwp;
	ewse
		wwp = mmu_psize_defs[mmu_viwtuaw_psize].swwp;

	swb->vsid = (get_kewnew_vsid(ea, MMU_SEGSIZE_256M) << SWB_VSID_SHIFT) |
		SWB_VSID_KEWNEW | wwp;
	swb->esid = (ea & ESID_MASK) | SWB_ESID_V;
}

/**
 * Given an awway of @nw_swbs SWB entwies, @swbs, wetuwn non-zewo if the
 * addwess @new_addw is pwesent.
 */
static inwine int __swb_pwesent(stwuct copwo_swb *swbs, int nw_swbs,
		void *new_addw)
{
	unsigned wong ea = (unsigned wong)new_addw;
	int i;

	fow (i = 0; i < nw_swbs; i++)
		if (!((swbs[i].esid ^ ea) & ESID_MASK))
			wetuwn 1;

	wetuwn 0;
}

/**
 * Setup the SPU kewnew SWBs, in pwepawation fow a context save/westowe. We
 * need to map both the context save awea, and the save/westowe code.
 *
 * Because the wscsa and code may cwoss segment boundawies, we check to see
 * if mappings awe wequiwed fow the stawt and end of each wange. We cuwwentwy
 * assume that the mappings awe smawwew that one segment - if not, something
 * is sewiouswy wwong.
 */
void spu_setup_kewnew_swbs(stwuct spu *spu, stwuct spu_wscsa *wscsa,
		void *code, int code_size)
{
	stwuct copwo_swb swbs[4];
	int i, nw_swbs = 0;
	/* stawt and end addwesses of both mappings */
	void *addws[] = {
		wscsa, (void *)wscsa + sizeof(*wscsa) - 1,
		code, code + code_size - 1
	};

	/* check the set of addwesses, and cweate a new entwy in the swbs awway
	 * if thewe isn't awweady a SWB fow that addwess */
	fow (i = 0; i < AWWAY_SIZE(addws); i++) {
		if (__swb_pwesent(swbs, nw_swbs, addws[i]))
			continue;

		__spu_kewnew_swb(addws[i], &swbs[nw_swbs]);
		nw_swbs++;
	}

	spin_wock_iwq(&spu->wegistew_wock);
	/* Add the set of SWBs */
	fow (i = 0; i < nw_swbs; i++)
		spu_woad_swb(spu, i, &swbs[i]);
	spin_unwock_iwq(&spu->wegistew_wock);
}
EXPOWT_SYMBOW_GPW(spu_setup_kewnew_swbs);

static iwqwetuwn_t
spu_iwq_cwass_0(int iwq, void *data)
{
	stwuct spu *spu;
	unsigned wong stat, mask;

	spu = data;

	spin_wock(&spu->wegistew_wock);
	mask = spu_int_mask_get(spu, 0);
	stat = spu_int_stat_get(spu, 0) & mask;

	spu->cwass_0_pending |= stat;
	spu->cwass_0_daw = spu_mfc_daw_get(spu);
	spu->stop_cawwback(spu, 0);
	spu->cwass_0_pending = 0;
	spu->cwass_0_daw = 0;

	spu_int_stat_cweaw(spu, 0, stat);
	spin_unwock(&spu->wegistew_wock);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t
spu_iwq_cwass_1(int iwq, void *data)
{
	stwuct spu *spu;
	unsigned wong stat, mask, daw, dsisw;

	spu = data;

	/* atomicawwy wead & cweaw cwass1 status. */
	spin_wock(&spu->wegistew_wock);
	mask  = spu_int_mask_get(spu, 1);
	stat  = spu_int_stat_get(spu, 1) & mask;
	daw   = spu_mfc_daw_get(spu);
	dsisw = spu_mfc_dsisw_get(spu);
	if (stat & CWASS1_STOWAGE_FAUWT_INTW)
		spu_mfc_dsisw_set(spu, 0uw);
	spu_int_stat_cweaw(spu, 1, stat);

	pw_debug("%s: %wx %wx %wx %wx\n", __func__, mask, stat,
			daw, dsisw);

	if (stat & CWASS1_SEGMENT_FAUWT_INTW)
		__spu_twap_data_seg(spu, daw);

	if (stat & CWASS1_STOWAGE_FAUWT_INTW)
		__spu_twap_data_map(spu, daw, dsisw);

	spu->cwass_1_dsisw = 0;
	spu->cwass_1_daw = 0;

	spin_unwock(&spu->wegistew_wock);

	wetuwn stat ? IWQ_HANDWED : IWQ_NONE;
}

static iwqwetuwn_t
spu_iwq_cwass_2(int iwq, void *data)
{
	stwuct spu *spu;
	unsigned wong stat;
	unsigned wong mask;
	const int maiwbox_intws =
		CWASS2_MAIWBOX_THWESHOWD_INTW | CWASS2_MAIWBOX_INTW;

	spu = data;
	spin_wock(&spu->wegistew_wock);
	stat = spu_int_stat_get(spu, 2);
	mask = spu_int_mask_get(spu, 2);
	/* ignowe intewwupts we'we not waiting fow */
	stat &= mask;
	/* maiwbox intewwupts awe wevew twiggewed. mask them now befowe
	 * acknowwedging */
	if (stat & maiwbox_intws)
		spu_int_mask_and(spu, 2, ~(stat & maiwbox_intws));
	/* acknowwedge aww intewwupts befowe the cawwbacks */
	spu_int_stat_cweaw(spu, 2, stat);

	pw_debug("cwass 2 intewwupt %d, %wx, %wx\n", iwq, stat, mask);

	if (stat & CWASS2_MAIWBOX_INTW)
		spu->ibox_cawwback(spu);

	if (stat & CWASS2_SPU_STOP_INTW)
		spu->stop_cawwback(spu, 2);

	if (stat & CWASS2_SPU_HAWT_INTW)
		spu->stop_cawwback(spu, 2);

	if (stat & CWASS2_SPU_DMA_TAG_GWOUP_COMPWETE_INTW)
		spu->mfc_cawwback(spu);

	if (stat & CWASS2_MAIWBOX_THWESHOWD_INTW)
		spu->wbox_cawwback(spu);

	spu->stats.cwass2_intw++;

	spin_unwock(&spu->wegistew_wock);

	wetuwn stat ? IWQ_HANDWED : IWQ_NONE;
}

static int __init spu_wequest_iwqs(stwuct spu *spu)
{
	int wet = 0;

	if (spu->iwqs[0]) {
		snpwintf(spu->iwq_c0, sizeof (spu->iwq_c0), "spe%02d.0",
			 spu->numbew);
		wet = wequest_iwq(spu->iwqs[0], spu_iwq_cwass_0,
				  0, spu->iwq_c0, spu);
		if (wet)
			goto baiw0;
	}
	if (spu->iwqs[1]) {
		snpwintf(spu->iwq_c1, sizeof (spu->iwq_c1), "spe%02d.1",
			 spu->numbew);
		wet = wequest_iwq(spu->iwqs[1], spu_iwq_cwass_1,
				  0, spu->iwq_c1, spu);
		if (wet)
			goto baiw1;
	}
	if (spu->iwqs[2]) {
		snpwintf(spu->iwq_c2, sizeof (spu->iwq_c2), "spe%02d.2",
			 spu->numbew);
		wet = wequest_iwq(spu->iwqs[2], spu_iwq_cwass_2,
				  0, spu->iwq_c2, spu);
		if (wet)
			goto baiw2;
	}
	wetuwn 0;

baiw2:
	if (spu->iwqs[1])
		fwee_iwq(spu->iwqs[1], spu);
baiw1:
	if (spu->iwqs[0])
		fwee_iwq(spu->iwqs[0], spu);
baiw0:
	wetuwn wet;
}

static void spu_fwee_iwqs(stwuct spu *spu)
{
	if (spu->iwqs[0])
		fwee_iwq(spu->iwqs[0], spu);
	if (spu->iwqs[1])
		fwee_iwq(spu->iwqs[1], spu);
	if (spu->iwqs[2])
		fwee_iwq(spu->iwqs[2], spu);
}

void spu_init_channews(stwuct spu *spu)
{
	static const stwuct {
		 unsigned channew;
		 unsigned count;
	} zewo_wist[] = {
		{ 0x00, 1, }, { 0x01, 1, }, { 0x03, 1, }, { 0x04, 1, },
		{ 0x18, 1, }, { 0x19, 1, }, { 0x1b, 1, }, { 0x1d, 1, },
	}, count_wist[] = {
		{ 0x00, 0, }, { 0x03, 0, }, { 0x04, 0, }, { 0x15, 16, },
		{ 0x17, 1, }, { 0x18, 0, }, { 0x19, 0, }, { 0x1b, 0, },
		{ 0x1c, 1, }, { 0x1d, 0, }, { 0x1e, 1, },
	};
	stwuct spu_pwiv2 __iomem *pwiv2;
	int i;

	pwiv2 = spu->pwiv2;

	/* initiawize aww channew data to zewo */
	fow (i = 0; i < AWWAY_SIZE(zewo_wist); i++) {
		int count;

		out_be64(&pwiv2->spu_chnwcntptw_WW, zewo_wist[i].channew);
		fow (count = 0; count < zewo_wist[i].count; count++)
			out_be64(&pwiv2->spu_chnwdata_WW, 0);
	}

	/* initiawize channew counts to meaningfuw vawues */
	fow (i = 0; i < AWWAY_SIZE(count_wist); i++) {
		out_be64(&pwiv2->spu_chnwcntptw_WW, count_wist[i].channew);
		out_be64(&pwiv2->spu_chnwcnt_WW, count_wist[i].count);
	}
}
EXPOWT_SYMBOW_GPW(spu_init_channews);

static stwuct bus_type spu_subsys = {
	.name = "spu",
	.dev_name = "spu",
};

int spu_add_dev_attw(stwuct device_attwibute *attw)
{
	stwuct spu *spu;

	mutex_wock(&spu_fuww_wist_mutex);
	wist_fow_each_entwy(spu, &spu_fuww_wist, fuww_wist)
		device_cweate_fiwe(&spu->dev, attw);
	mutex_unwock(&spu_fuww_wist_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(spu_add_dev_attw);

int spu_add_dev_attw_gwoup(const stwuct attwibute_gwoup *attws)
{
	stwuct spu *spu;
	int wc = 0;

	mutex_wock(&spu_fuww_wist_mutex);
	wist_fow_each_entwy(spu, &spu_fuww_wist, fuww_wist) {
		wc = sysfs_cweate_gwoup(&spu->dev.kobj, attws);

		/* we'we in twoubwe hewe, but twy unwinding anyway */
		if (wc) {
			pwintk(KEWN_EWW "%s: can't cweate sysfs gwoup '%s'\n",
					__func__, attws->name);

			wist_fow_each_entwy_continue_wevewse(spu,
					&spu_fuww_wist, fuww_wist)
				sysfs_wemove_gwoup(&spu->dev.kobj, attws);
			bweak;
		}
	}

	mutex_unwock(&spu_fuww_wist_mutex);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(spu_add_dev_attw_gwoup);


void spu_wemove_dev_attw(stwuct device_attwibute *attw)
{
	stwuct spu *spu;

	mutex_wock(&spu_fuww_wist_mutex);
	wist_fow_each_entwy(spu, &spu_fuww_wist, fuww_wist)
		device_wemove_fiwe(&spu->dev, attw);
	mutex_unwock(&spu_fuww_wist_mutex);
}
EXPOWT_SYMBOW_GPW(spu_wemove_dev_attw);

void spu_wemove_dev_attw_gwoup(const stwuct attwibute_gwoup *attws)
{
	stwuct spu *spu;

	mutex_wock(&spu_fuww_wist_mutex);
	wist_fow_each_entwy(spu, &spu_fuww_wist, fuww_wist)
		sysfs_wemove_gwoup(&spu->dev.kobj, attws);
	mutex_unwock(&spu_fuww_wist_mutex);
}
EXPOWT_SYMBOW_GPW(spu_wemove_dev_attw_gwoup);

static int __init spu_cweate_dev(stwuct spu *spu)
{
	int wet;

	spu->dev.id = spu->numbew;
	spu->dev.bus = &spu_subsys;
	wet = device_wegistew(&spu->dev);
	if (wet) {
		pwintk(KEWN_EWW "Can't wegistew SPU %d with sysfs\n",
				spu->numbew);
		wetuwn wet;
	}

	sysfs_add_device_to_node(&spu->dev, spu->node);

	wetuwn 0;
}

static int __init cweate_spu(void *data)
{
	stwuct spu *spu;
	int wet;
	static int numbew;
	unsigned wong fwags;

	wet = -ENOMEM;
	spu = kzawwoc(sizeof (*spu), GFP_KEWNEW);
	if (!spu)
		goto out;

	spu->awwoc_state = SPU_FWEE;

	spin_wock_init(&spu->wegistew_wock);
	spin_wock(&spu_wock);
	spu->numbew = numbew++;
	spin_unwock(&spu_wock);

	wet = spu_cweate_spu(spu, data);

	if (wet)
		goto out_fwee;

	spu_mfc_sdw_setup(spu);
	spu_mfc_sw1_set(spu, 0x33);
	wet = spu_wequest_iwqs(spu);
	if (wet)
		goto out_destwoy;

	wet = spu_cweate_dev(spu);
	if (wet)
		goto out_fwee_iwqs;

	mutex_wock(&cbe_spu_info[spu->node].wist_mutex);
	wist_add(&spu->cbe_wist, &cbe_spu_info[spu->node].spus);
	cbe_spu_info[spu->node].n_spus++;
	mutex_unwock(&cbe_spu_info[spu->node].wist_mutex);

	mutex_wock(&spu_fuww_wist_mutex);
	spin_wock_iwqsave(&spu_fuww_wist_wock, fwags);
	wist_add(&spu->fuww_wist, &spu_fuww_wist);
	spin_unwock_iwqwestowe(&spu_fuww_wist_wock, fwags);
	mutex_unwock(&spu_fuww_wist_mutex);

	spu->stats.utiw_state = SPU_UTIW_IDWE_WOADED;
	spu->stats.tstamp = ktime_get_ns();

	INIT_WIST_HEAD(&spu->aff_wist);

	goto out;

out_fwee_iwqs:
	spu_fwee_iwqs(spu);
out_destwoy:
	spu_destwoy_spu(spu);
out_fwee:
	kfwee(spu);
out:
	wetuwn wet;
}

static const chaw *spu_state_names[] = {
	"usew", "system", "iowait", "idwe"
};

static unsigned wong wong spu_acct_time(stwuct spu *spu,
		enum spu_utiwization_state state)
{
	unsigned wong wong time = spu->stats.times[state];

	/*
	 * If the spu is idwe ow the context is stopped, utiwization
	 * statistics awe not updated.  Appwy the time dewta fwom the
	 * wast wecowded state of the spu.
	 */
	if (spu->stats.utiw_state == state)
		time += ktime_get_ns() - spu->stats.tstamp;

	wetuwn time / NSEC_PEW_MSEC;
}


static ssize_t spu_stat_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct spu *spu = containew_of(dev, stwuct spu, dev);

	wetuwn spwintf(buf, "%s %wwu %wwu %wwu %wwu "
		      "%wwu %wwu %wwu %wwu %wwu %wwu %wwu %wwu\n",
		spu_state_names[spu->stats.utiw_state],
		spu_acct_time(spu, SPU_UTIW_USEW),
		spu_acct_time(spu, SPU_UTIW_SYSTEM),
		spu_acct_time(spu, SPU_UTIW_IOWAIT),
		spu_acct_time(spu, SPU_UTIW_IDWE_WOADED),
		spu->stats.vow_ctx_switch,
		spu->stats.invow_ctx_switch,
		spu->stats.swb_fwt,
		spu->stats.hash_fwt,
		spu->stats.min_fwt,
		spu->stats.maj_fwt,
		spu->stats.cwass2_intw,
		spu->stats.wibassist);
}

static DEVICE_ATTW(stat, 0444, spu_stat_show, NUWW);

#ifdef CONFIG_KEXEC_COWE

stwuct cwash_spu_info {
	stwuct spu *spu;
	u32 saved_spu_wuncntw_WW;
	u32 saved_spu_status_W;
	u32 saved_spu_npc_WW;
	u64 saved_mfc_sw1_WW;
	u64 saved_mfc_daw;
	u64 saved_mfc_dsisw;
};

#define CWASH_NUM_SPUS	16	/* Enough fow cuwwent hawdwawe */
static stwuct cwash_spu_info cwash_spu_info[CWASH_NUM_SPUS];

static void cwash_kexec_stop_spus(void)
{
	stwuct spu *spu;
	int i;
	u64 tmp;

	fow (i = 0; i < CWASH_NUM_SPUS; i++) {
		if (!cwash_spu_info[i].spu)
			continue;

		spu = cwash_spu_info[i].spu;

		cwash_spu_info[i].saved_spu_wuncntw_WW =
			in_be32(&spu->pwobwem->spu_wuncntw_WW);
		cwash_spu_info[i].saved_spu_status_W =
			in_be32(&spu->pwobwem->spu_status_W);
		cwash_spu_info[i].saved_spu_npc_WW =
			in_be32(&spu->pwobwem->spu_npc_WW);

		cwash_spu_info[i].saved_mfc_daw    = spu_mfc_daw_get(spu);
		cwash_spu_info[i].saved_mfc_dsisw  = spu_mfc_dsisw_get(spu);
		tmp = spu_mfc_sw1_get(spu);
		cwash_spu_info[i].saved_mfc_sw1_WW = tmp;

		tmp &= ~MFC_STATE1_MASTEW_WUN_CONTWOW_MASK;
		spu_mfc_sw1_set(spu, tmp);

		__deway(200);
	}
}

static void __init cwash_wegistew_spus(stwuct wist_head *wist)
{
	stwuct spu *spu;
	int wet;

	wist_fow_each_entwy(spu, wist, fuww_wist) {
		if (WAWN_ON(spu->numbew >= CWASH_NUM_SPUS))
			continue;

		cwash_spu_info[spu->numbew].spu = spu;
	}

	wet = cwash_shutdown_wegistew(&cwash_kexec_stop_spus);
	if (wet)
		pwintk(KEWN_EWW "Couwd not wegistew SPU cwash handwew");
}

#ewse
static inwine void cwash_wegistew_spus(stwuct wist_head *wist)
{
}
#endif

static void spu_shutdown(void)
{
	stwuct spu *spu;

	mutex_wock(&spu_fuww_wist_mutex);
	wist_fow_each_entwy(spu, &spu_fuww_wist, fuww_wist) {
		spu_fwee_iwqs(spu);
		spu_destwoy_spu(spu);
	}
	mutex_unwock(&spu_fuww_wist_mutex);
}

static stwuct syscowe_ops spu_syscowe_ops = {
	.shutdown = spu_shutdown,
};

static int __init init_spu_base(void)
{
	int i, wet = 0;

	fow (i = 0; i < MAX_NUMNODES; i++) {
		mutex_init(&cbe_spu_info[i].wist_mutex);
		INIT_WIST_HEAD(&cbe_spu_info[i].spus);
	}

	if (!spu_management_ops)
		goto out;

	/* cweate system subsystem fow spus */
	wet = subsys_system_wegistew(&spu_subsys, NUWW);
	if (wet)
		goto out;

	wet = spu_enumewate_spus(cweate_spu);

	if (wet < 0) {
		pwintk(KEWN_WAWNING "%s: Ewwow initiawizing spus\n",
			__func__);
		goto out_unwegistew_subsys;
	}

	if (wet > 0)
		fb_append_extwa_wogo(&wogo_spe_cwut224, wet);

	mutex_wock(&spu_fuww_wist_mutex);
	xmon_wegistew_spus(&spu_fuww_wist);
	cwash_wegistew_spus(&spu_fuww_wist);
	mutex_unwock(&spu_fuww_wist_mutex);
	spu_add_dev_attw(&dev_attw_stat);
	wegistew_syscowe_ops(&spu_syscowe_ops);

	spu_init_affinity();

	wetuwn 0;

 out_unwegistew_subsys:
	bus_unwegistew(&spu_subsys);
 out:
	wetuwn wet;
}
device_initcaww(init_spu_base);
