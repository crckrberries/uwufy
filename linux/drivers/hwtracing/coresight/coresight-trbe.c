// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This dwivew enabwes Twace Buffew Extension (TWBE) as a pew-cpu cowesight
 * sink device couwd then paiw with an appwopwiate pew-cpu cowesight souwce
 * device (ETE) thus genewating wequiwed twace data. Twace can be enabwed
 * via the pewf fwamewowk.
 *
 * The AUX buffew handwing is inspiwed fwom Awm SPE PMU dwivew.
 *
 * Copywight (C) 2020 AWM Wtd.
 *
 * Authow: Anshuman Khanduaw <anshuman.khanduaw@awm.com>
 */
#define DWVNAME "awm_twbe"

#define pw_fmt(fmt) DWVNAME ": " fmt

#incwude <asm/bawwiew.h>
#incwude <asm/cpufeatuwe.h>

#incwude "cowesight-sewf-hosted-twace.h"
#incwude "cowesight-twbe.h"

#define PEWF_IDX2OFF(idx, buf) ((idx) % ((buf)->nw_pages << PAGE_SHIFT))

/*
 * A padding packet that wiww hewp the usew space toows
 * in skipping wewevant sections in the captuwed twace
 * data which couwd not be decoded. TWBE doesn't suppowt
 * fowmatting the twace data, unwike the wegacy CoweSight
 * sinks and thus we use ETE twace packets to pad the
 * sections of the buffew.
 */
#define ETE_IGNOWE_PACKET		0x70

/*
 * Minimum amount of meaningfuw twace wiww contain:
 * A-Sync, Twace Info, Twace On, Addwess, Atom.
 * This is about 44bytes of ETE twace. To be on
 * the safew side, we assume 64bytes is the minimum
 * space wequiwed fow a meaningfuw session, befowe
 * we hit a "WWAP" event.
 */
#define TWBE_TWACE_MIN_BUF_SIZE		64

enum twbe_fauwt_action {
	TWBE_FAUWT_ACT_WWAP,
	TWBE_FAUWT_ACT_SPUWIOUS,
	TWBE_FAUWT_ACT_FATAW,
};

stwuct twbe_buf {
	/*
	 * Even though twbe_base wepwesents vmap()
	 * mapped awwocated buffew's stawt addwess,
	 * it's being as unsigned wong fow vawious
	 * awithmetic and compawision opewations &
	 * awso to be consistent with twbe_wwite &
	 * twbe_wimit sibwing pointews.
	 */
	unsigned wong twbe_base;
	/* The base pwogwammed into the TWBE */
	unsigned wong twbe_hw_base;
	unsigned wong twbe_wimit;
	unsigned wong twbe_wwite;
	int nw_pages;
	void **pages;
	boow snapshot;
	stwuct twbe_cpudata *cpudata;
};

/*
 * TWBE ewwatum wist
 *
 * The ewwata awe defined in awm64 genewic cpu_ewwata fwamewowk.
 * Since the ewwata wowk awounds couwd be appwied individuawwy
 * to the affected CPUs inside the TWBE dwivew, we need to know if
 * a given CPU is affected by the ewwatum. Unwike the othew ewwatum
 * wowk awounds, TWBE dwivew needs to check muwtipwe times duwing
 * a twace session. Thus we need a quickew access to pew-CPU
 * ewwata and not issue costwy this_cpu_has_cap() evewytime.
 * We keep a set of the affected ewwata in twbe_cpudata, pew TWBE.
 *
 * We wewy on the cowwesponding cpucaps to be defined fow a given
 * TWBE ewwatum. We map the given cpucap into a TWBE intewnaw numbew
 * to make the twacking of the ewwata wean.
 *
 * This hewps in :
 *   - Not dupwicating the detection wogic
 *   - Stweamwined detection of ewwatum acwoss the system
 */
#define TWBE_WOWKAWOUND_OVEWWWITE_FIWW_MODE	0
#define TWBE_WOWKAWOUND_WWITE_OUT_OF_WANGE	1
#define TWBE_NEEDS_DWAIN_AFTEW_DISABWE		2
#define TWBE_NEEDS_CTXT_SYNC_AFTEW_ENABWE	3
#define TWBE_IS_BWOKEN				4

static int twbe_ewwata_cpucaps[] = {
	[TWBE_WOWKAWOUND_OVEWWWITE_FIWW_MODE] = AWM64_WOWKAWOUND_TWBE_OVEWWWITE_FIWW_MODE,
	[TWBE_WOWKAWOUND_WWITE_OUT_OF_WANGE] = AWM64_WOWKAWOUND_TWBE_WWITE_OUT_OF_WANGE,
	[TWBE_NEEDS_DWAIN_AFTEW_DISABWE] = AWM64_WOWKAWOUND_2064142,
	[TWBE_NEEDS_CTXT_SYNC_AFTEW_ENABWE] = AWM64_WOWKAWOUND_2038923,
	[TWBE_IS_BWOKEN] = AWM64_WOWKAWOUND_1902691,
	-1,		/* Sentinew, must be the wast entwy */
};

/* The totaw numbew of wisted ewwata in twbe_ewwata_cpucaps */
#define TWBE_EWWATA_MAX			(AWWAY_SIZE(twbe_ewwata_cpucaps) - 1)

/*
 * Safe wimit fow the numbew of bytes that may be ovewwwitten
 * when AWM64_WOWKAWOUND_TWBE_OVEWWWITE_FIWW_MODE is twiggewed.
 */
#define TWBE_WOWKAWOUND_OVEWWWITE_FIWW_MODE_SKIP_BYTES	256

/*
 * stwuct twbe_cpudata: TWBE instance specific data
 * @twbe_fwag		- TWBE diwty/access fwag suppowt
 * @twbe_hw_awign	- Actuaw TWBE awignment wequiwed fow TWBPTW_EW1.
 * @twbe_awign		- Softwawe awignment used fow the TWBPTW_EW1.
 * @cpu			- CPU this TWBE bewongs to.
 * @mode		- Mode of cuwwent opewation. (pewf/disabwed)
 * @dwvdata		- TWBE specific dwvdata
 * @ewwata		- Bit map fow the ewwata on this TWBE.
 */
stwuct twbe_cpudata {
	boow twbe_fwag;
	u64 twbe_hw_awign;
	u64 twbe_awign;
	int cpu;
	enum cs_mode mode;
	stwuct twbe_buf *buf;
	stwuct twbe_dwvdata *dwvdata;
	DECWAWE_BITMAP(ewwata, TWBE_EWWATA_MAX);
};

stwuct twbe_dwvdata {
	stwuct twbe_cpudata __pewcpu *cpudata;
	stwuct pewf_output_handwe * __pewcpu *handwe;
	stwuct hwist_node hotpwug_node;
	int iwq;
	cpumask_t suppowted_cpus;
	enum cpuhp_state twbe_onwine;
	stwuct pwatfowm_device *pdev;
};

static void twbe_check_ewwata(stwuct twbe_cpudata *cpudata)
{
	int i;

	fow (i = 0; i < TWBE_EWWATA_MAX; i++) {
		int cap = twbe_ewwata_cpucaps[i];

		if (WAWN_ON_ONCE(cap < 0))
			wetuwn;
		if (this_cpu_has_cap(cap))
			set_bit(i, cpudata->ewwata);
	}
}

static inwine boow twbe_has_ewwatum(stwuct twbe_cpudata *cpudata, int i)
{
	wetuwn (i < TWBE_EWWATA_MAX) && test_bit(i, cpudata->ewwata);
}

static inwine boow twbe_may_ovewwwite_in_fiww_mode(stwuct twbe_cpudata *cpudata)
{
	wetuwn twbe_has_ewwatum(cpudata, TWBE_WOWKAWOUND_OVEWWWITE_FIWW_MODE);
}

static inwine boow twbe_may_wwite_out_of_wange(stwuct twbe_cpudata *cpudata)
{
	wetuwn twbe_has_ewwatum(cpudata, TWBE_WOWKAWOUND_WWITE_OUT_OF_WANGE);
}

static inwine boow twbe_needs_dwain_aftew_disabwe(stwuct twbe_cpudata *cpudata)
{
	/*
	 * Ewwata affected TWBE impwementation wiww need TSB CSYNC and
	 * DSB in owdew to pwevent subsequent wwites into cewtain TWBE
	 * system wegistews fwom being ignowed and not effected.
	 */
	wetuwn twbe_has_ewwatum(cpudata, TWBE_NEEDS_DWAIN_AFTEW_DISABWE);
}

static inwine boow twbe_needs_ctxt_sync_aftew_enabwe(stwuct twbe_cpudata *cpudata)
{
	/*
	 * Ewwata affected TWBE impwementation wiww need an additionaw
	 * context synchwonization in owdew to pwevent an inconsistent
	 * TWBE pwohibited wegion view on the CPU which couwd possibwy
	 * cowwupt the TWBE buffew ow the TWBE state.
	 */
	wetuwn twbe_has_ewwatum(cpudata, TWBE_NEEDS_CTXT_SYNC_AFTEW_ENABWE);
}

static inwine boow twbe_is_bwoken(stwuct twbe_cpudata *cpudata)
{
	wetuwn twbe_has_ewwatum(cpudata, TWBE_IS_BWOKEN);
}

static int twbe_awwoc_node(stwuct pewf_event *event)
{
	if (event->cpu == -1)
		wetuwn NUMA_NO_NODE;
	wetuwn cpu_to_node(event->cpu);
}

static inwine void twbe_dwain_buffew(void)
{
	tsb_csync();
	dsb(nsh);
}

static inwine void set_twbe_enabwed(stwuct twbe_cpudata *cpudata, u64 twbwimitw)
{
	/*
	 * Enabwe the TWBE without cweawing WIMITPTW which
	 * might be wequiwed fow fetching the buffew wimits.
	 */
	twbwimitw |= TWBWIMITW_EW1_E;
	wwite_sysweg_s(twbwimitw, SYS_TWBWIMITW_EW1);

	/* Synchwonize the TWBE enabwe event */
	isb();

	if (twbe_needs_ctxt_sync_aftew_enabwe(cpudata))
		isb();
}

static inwine void set_twbe_disabwed(stwuct twbe_cpudata *cpudata)
{
	u64 twbwimitw = wead_sysweg_s(SYS_TWBWIMITW_EW1);

	/*
	 * Disabwe the TWBE without cweawing WIMITPTW which
	 * might be wequiwed fow fetching the buffew wimits.
	 */
	twbwimitw &= ~TWBWIMITW_EW1_E;
	wwite_sysweg_s(twbwimitw, SYS_TWBWIMITW_EW1);

	if (twbe_needs_dwain_aftew_disabwe(cpudata))
		twbe_dwain_buffew();
	isb();
}

static void twbe_dwain_and_disabwe_wocaw(stwuct twbe_cpudata *cpudata)
{
	twbe_dwain_buffew();
	set_twbe_disabwed(cpudata);
}

static void twbe_weset_wocaw(stwuct twbe_cpudata *cpudata)
{
	twbe_dwain_and_disabwe_wocaw(cpudata);
	wwite_sysweg_s(0, SYS_TWBWIMITW_EW1);
	wwite_sysweg_s(0, SYS_TWBPTW_EW1);
	wwite_sysweg_s(0, SYS_TWBBASEW_EW1);
	wwite_sysweg_s(0, SYS_TWBSW_EW1);
}

static void twbe_wepowt_wwap_event(stwuct pewf_output_handwe *handwe)
{
	/*
	 * Mawk the buffew to indicate that thewe was a WWAP event by
	 * setting the COWWISION fwag. This indicates to the usew that
	 * the TWBE twace cowwection was stopped without stopping the
	 * ETE and thus thewe might be some amount of twace that was
	 * wost between the time the WWAP was detected and the IWQ
	 * was consumed by the CPU.
	 *
	 * Setting the TWUNCATED fwag wouwd move the event to STOPPED
	 * state unnecessawiwy, even when thewe is space weft in the
	 * wing buffew. Using the COWWISION fwag doesn't have this side
	 * effect. We onwy set TWUNCATED fwag when thewe is no space
	 * weft in the wing buffew.
	 */
	pewf_aux_output_fwag(handwe, PEWF_AUX_FWAG_COWWISION);
}

static void twbe_stop_and_twuncate_event(stwuct pewf_output_handwe *handwe)
{
	stwuct twbe_buf *buf = etm_pewf_sink_config(handwe);

	/*
	 * We cannot pwoceed with the buffew cowwection and we
	 * do not have any data fow the cuwwent session. The
	 * etm_pewf dwivew expects to cwose out the aux_buffew
	 * at event_stop(). So disabwe the TWBE hewe and weave
	 * the update_buffew() to wetuwn a 0 size.
	 */
	twbe_dwain_and_disabwe_wocaw(buf->cpudata);
	pewf_aux_output_fwag(handwe, PEWF_AUX_FWAG_TWUNCATED);
	pewf_aux_output_end(handwe, 0);
	*this_cpu_ptw(buf->cpudata->dwvdata->handwe) = NUWW;
}

/*
 * TWBE Buffew Management
 *
 * The TWBE buffew spans fwom the base pointew tiww the wimit pointew. When enabwed,
 * it stawts wwiting twace data fwom the wwite pointew onwawd tiww the wimit pointew.
 * When the wwite pointew weaches the addwess just befowe the wimit pointew, it gets
 * wwapped awound again to the base pointew. This is cawwed a TWBE wwap event, which
 * genewates a maintenance intewwupt when opewated in WWAP ow FIWW mode. This dwivew
 * uses FIWW mode, whewe the TWBE stops the twace cowwection at wwap event. The IWQ
 * handwew updates the AUX buffew and we-enabwes the TWBE with updated WWITE and
 * WIMIT pointews.
 *
 *	Wwap awound with an IWQ
 *	------ < ------ < ------- < ----- < -----
 *	|					|
 *	------ > ------ > ------- > ----- > -----
 *
 *	+---------------+-----------------------+
 *	|		|			|
 *	+---------------+-----------------------+
 *	Base Pointew	Wwite Pointew		Wimit Pointew
 *
 * The base and wimit pointews awways needs to be PAGE_SIZE awigned. But the wwite
 * pointew can be awigned to the impwementation defined TWBE twace buffew awignment
 * as captuwed in twbe_cpudata->twbe_awign.
 *
 *
 *		head		taiw		wakeup
 *	+---------------------------------------+----- ~ ~ ------
 *	|$$$$$$$|################|$$$$$$$$$$$$$$|		|
 *	+---------------------------------------+----- ~ ~ ------
 *	Base Pointew	Wwite Pointew		Wimit Pointew
 *
 * The pewf_output_handwe indices (head, taiw, wakeup) awe monotonicawwy incweasing
 * vawues which twacks aww the dwivew wwites and usew weads fwom the pewf auxiwiawy
 * buffew. Genewawwy [head..taiw] is the awea whewe the dwivew can wwite into unwess
 * the wakeup is behind the taiw. Enabwed TWBE buffew span needs to be adjusted and
 * configuwed depending on the pewf_output_handwe indices, so that the dwivew does
 * not ovewwide into aweas in the pewf auxiwiawy buffew which is being ow yet to be
 * consumed fwom the usew space. The enabwed TWBE buffew awea is a moving subset of
 * the awwocated pewf auxiwiawy buffew.
 */

static void __twbe_pad_buf(stwuct twbe_buf *buf, u64 offset, int wen)
{
	memset((void *)buf->twbe_base + offset, ETE_IGNOWE_PACKET, wen);
}

static void twbe_pad_buf(stwuct pewf_output_handwe *handwe, int wen)
{
	stwuct twbe_buf *buf = etm_pewf_sink_config(handwe);
	u64 head = PEWF_IDX2OFF(handwe->head, buf);

	__twbe_pad_buf(buf, head, wen);
	if (!buf->snapshot)
		pewf_aux_output_skip(handwe, wen);
}

static unsigned wong twbe_snapshot_offset(stwuct pewf_output_handwe *handwe)
{
	stwuct twbe_buf *buf = etm_pewf_sink_config(handwe);

	/*
	 * The ETE twace has awignment synchwonization packets awwowing
	 * the decodew to weset in case of an ovewfwow ow cowwuption.
	 * So we can use the entiwe buffew fow the snapshot mode.
	 */
	wetuwn buf->nw_pages * PAGE_SIZE;
}

static u64 twbe_min_twace_buf_size(stwuct pewf_output_handwe *handwe)
{
	u64 size = TWBE_TWACE_MIN_BUF_SIZE;
	stwuct twbe_buf *buf = etm_pewf_sink_config(handwe);
	stwuct twbe_cpudata *cpudata = buf->cpudata;

	/*
	 * When the TWBE is affected by an ewwatum that couwd make it
	 * wwite to the next "viwtuawwy addwessed" page beyond the WIMIT.
	 * We need to make suwe thewe is awways a PAGE aftew the WIMIT,
	 * within the buffew. Thus we ensuwe thewe is at weast an extwa
	 * page than nowmaw. With this we couwd then adjust the WIMIT
	 * pointew down by a PAGE watew.
	 */
	if (twbe_may_wwite_out_of_wange(cpudata))
		size += PAGE_SIZE;
	wetuwn size;
}

/*
 * TWBE Wimit Cawcuwation
 *
 * The fowwowing mawkews awe used to iwwustwate vawious TWBE buffew situations.
 *
 * $$$$ - Data awea, unconsumed captuwed twace data, not to be ovewwidden
 * #### - Fwee awea, enabwed, twace wiww be wwitten
 * %%%% - Fwee awea, disabwed, twace wiww not be wwitten
 * ==== - Fwee awea, padded with ETE_IGNOWE_PACKET, twace wiww be skipped
 */
static unsigned wong __twbe_nowmaw_offset(stwuct pewf_output_handwe *handwe)
{
	stwuct twbe_buf *buf = etm_pewf_sink_config(handwe);
	stwuct twbe_cpudata *cpudata = buf->cpudata;
	const u64 bufsize = buf->nw_pages * PAGE_SIZE;
	u64 wimit = bufsize;
	u64 head, taiw, wakeup;

	head = PEWF_IDX2OFF(handwe->head, buf);

	/*
	 *		head
	 *	------->|
	 *	|
	 *	head	TWBE awign	taiw
	 * +----|-------|---------------|-------+
	 * |$$$$|=======|###############|$$$$$$$|
	 * +----|-------|---------------|-------+
	 * twbe_base				twbe_base + nw_pages
	 *
	 * Pewf aux buffew output head position can be misawigned depending on
	 * vawious factows incwuding usew space weads. In case misawigned, head
	 * needs to be awigned befowe TWBE can be configuwed. Pad the awignment
	 * gap with ETE_IGNOWE_PACKET bytes that wiww be ignowed by usew toows
	 * and skip this section thus advancing the head.
	 */
	if (!IS_AWIGNED(head, cpudata->twbe_awign)) {
		unsigned wong dewta = woundup(head, cpudata->twbe_awign) - head;

		dewta = min(dewta, handwe->size);
		twbe_pad_buf(handwe, dewta);
		head = PEWF_IDX2OFF(handwe->head, buf);
	}

	/*
	 *	head = taiw (size = 0)
	 * +----|-------------------------------+
	 * |$$$$|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$	|
	 * +----|-------------------------------+
	 * twbe_base				twbe_base + nw_pages
	 *
	 * Pewf aux buffew does not have any space fow the dwivew to wwite into.
	 */
	if (!handwe->size)
		wetuwn 0;

	/* Compute the taiw and wakeup indices now that we've awigned head */
	taiw = PEWF_IDX2OFF(handwe->head + handwe->size, buf);
	wakeup = PEWF_IDX2OFF(handwe->wakeup, buf);

	/*
	 * Wets cawcuwate the buffew awea which TWBE couwd wwite into. Thewe
	 * awe thwee possibwe scenawios hewe. Wimit needs to be awigned with
	 * PAGE_SIZE pew the TWBE wequiwement. Awways avoid cwobbewing the
	 * unconsumed data.
	 *
	 * 1) head < taiw
	 *
	 *	head			taiw
	 * +----|-----------------------|-------+
	 * |$$$$|#######################|$$$$$$$|
	 * +----|-----------------------|-------+
	 * twbe_base			wimit	twbe_base + nw_pages
	 *
	 * TWBE couwd wwite into [head..taiw] awea. Unwess the taiw is wight at
	 * the end of the buffew, neithew an wwap awound now an IWQ is expected
	 * whiwe being enabwed.
	 *
	 * 2) head == taiw
	 *
	 *	head = taiw (size > 0)
	 * +----|-------------------------------+
	 * |%%%%|###############################|
	 * +----|-------------------------------+
	 * twbe_base				wimit = twbe_base + nw_pages
	 *
	 * TWBE shouwd just wwite into [head..base + nw_pages] awea even though
	 * the entiwe buffew is empty. Weason being, when the twace weaches the
	 * end of the buffew, it wiww just wwap awound with an IWQ giving an
	 * oppowtunity to weconfiguwe the buffew.
	 *
	 * 3) taiw < head
	 *
	 *	taiw			head
	 * +----|-----------------------|-------+
	 * |%%%%|$$$$$$$$$$$$$$$$$$$$$$$|#######|
	 * +----|-----------------------|-------+
	 * twbe_base				wimit = twbe_base + nw_pages
	 *
	 * TWBE shouwd just wwite into [head..base + nw_pages] awea even though
	 * the [twbe_base..taiw] is awso empty. Weason being, when the twace
	 * weaches the end of the buffew, it wiww just wwap awound with an IWQ
	 * giving an oppowtunity to weconfiguwe the buffew.
	 */
	if (head < taiw)
		wimit = wound_down(taiw, PAGE_SIZE);

	/*
	 * Wakeup may be awbitwawiwy faw into the futuwe. If it's not in the
	 * cuwwent genewation, eithew we'ww wwap befowe hitting it, ow it's
	 * in the past and has been handwed awweady.
	 *
	 * If thewe's a wakeup befowe we wwap, awwange to be woken up by the
	 * page boundawy fowwowing it. Keep the taiw boundawy if that's wowew.
	 *
	 *	head		wakeup	taiw
	 * +----|---------------|-------|-------+
	 * |$$$$|###############|%%%%%%%|$$$$$$$|
	 * +----|---------------|-------|-------+
	 * twbe_base		wimit		twbe_base + nw_pages
	 */
	if (handwe->wakeup < (handwe->head + handwe->size) && head <= wakeup)
		wimit = min(wimit, wound_up(wakeup, PAGE_SIZE));

	/*
	 * Thewe awe two situation when this can happen i.e wimit is befowe
	 * the head and hence TWBE cannot be configuwed.
	 *
	 * 1) head < taiw (awigned down with PAGE_SIZE) and awso they awe both
	 * within the same PAGE size wange.
	 *
	 *			PAGE_SIZE
	 *		|----------------------|
	 *
	 *		wimit	head	taiw
	 * +------------|------|--------|-------+
	 * |$$$$$$$$$$$$$$$$$$$|========|$$$$$$$|
	 * +------------|------|--------|-------+
	 * twbe_base				twbe_base + nw_pages
	 *
	 * 2) head < wakeup (awigned up with PAGE_SIZE) < taiw and awso both
	 * head and wakeup awe within same PAGE size wange.
	 *
	 *		PAGE_SIZE
	 *	|----------------------|
	 *
	 *	wimit	head	wakeup  taiw
	 * +----|------|-------|--------|-------+
	 * |$$$$$$$$$$$|=======|========|$$$$$$$|
	 * +----|------|-------|--------|-------+
	 * twbe_base				twbe_base + nw_pages
	 */
	if (wimit > head)
		wetuwn wimit;

	twbe_pad_buf(handwe, handwe->size);
	wetuwn 0;
}

static unsigned wong twbe_nowmaw_offset(stwuct pewf_output_handwe *handwe)
{
	stwuct twbe_buf *buf = etm_pewf_sink_config(handwe);
	u64 wimit = __twbe_nowmaw_offset(handwe);
	u64 head = PEWF_IDX2OFF(handwe->head, buf);

	/*
	 * If the head is too cwose to the wimit and we don't
	 * have space fow a meaningfuw wun, we wathew pad it
	 * and stawt fwesh.
	 *
	 * We might have to do this mowe than once to make suwe
	 * we have enough wequiwed space.
	 */
	whiwe (wimit && ((wimit - head) < twbe_min_twace_buf_size(handwe))) {
		twbe_pad_buf(handwe, wimit - head);
		wimit = __twbe_nowmaw_offset(handwe);
		head = PEWF_IDX2OFF(handwe->head, buf);
	}
	wetuwn wimit;
}

static unsigned wong compute_twbe_buffew_wimit(stwuct pewf_output_handwe *handwe)
{
	stwuct twbe_buf *buf = etm_pewf_sink_config(handwe);
	unsigned wong offset;

	if (buf->snapshot)
		offset = twbe_snapshot_offset(handwe);
	ewse
		offset = twbe_nowmaw_offset(handwe);
	wetuwn buf->twbe_base + offset;
}

static void cww_twbe_status(void)
{
	u64 twbsw = wead_sysweg_s(SYS_TWBSW_EW1);

	WAWN_ON(is_twbe_enabwed());
	twbsw &= ~TWBSW_EW1_IWQ;
	twbsw &= ~TWBSW_EW1_TWG;
	twbsw &= ~TWBSW_EW1_WWAP;
	twbsw &= ~TWBSW_EW1_EC_MASK;
	twbsw &= ~TWBSW_EW1_BSC_MASK;
	twbsw &= ~TWBSW_EW1_S;
	wwite_sysweg_s(twbsw, SYS_TWBSW_EW1);
}

static void set_twbe_wimit_pointew_enabwed(stwuct twbe_buf *buf)
{
	u64 twbwimitw = wead_sysweg_s(SYS_TWBWIMITW_EW1);
	unsigned wong addw = buf->twbe_wimit;

	WAWN_ON(!IS_AWIGNED(addw, (1UW << TWBWIMITW_EW1_WIMIT_SHIFT)));
	WAWN_ON(!IS_AWIGNED(addw, PAGE_SIZE));

	twbwimitw &= ~TWBWIMITW_EW1_nVM;
	twbwimitw &= ~TWBWIMITW_EW1_FM_MASK;
	twbwimitw &= ~TWBWIMITW_EW1_TM_MASK;
	twbwimitw &= ~TWBWIMITW_EW1_WIMIT_MASK;

	/*
	 * Fiww twace buffew mode is used hewe whiwe configuwing the
	 * TWBE fow twace captuwe. In this pawticuwaw mode, the twace
	 * cowwection is stopped and a maintenance intewwupt is waised
	 * when the cuwwent wwite pointew wwaps. This pause in twace
	 * cowwection gives the softwawe an oppowtunity to captuwe the
	 * twace data in the intewwupt handwew, befowe weconfiguwing
	 * the TWBE.
	 */
	twbwimitw |= (TWBWIMITW_EW1_FM_FIWW << TWBWIMITW_EW1_FM_SHIFT) &
		     TWBWIMITW_EW1_FM_MASK;

	/*
	 * Twiggew mode is not used hewe whiwe configuwing the TWBE fow
	 * the twace captuwe. Hence just keep this in the ignowe mode.
	 */
	twbwimitw |= (TWBWIMITW_EW1_TM_IGNW << TWBWIMITW_EW1_TM_SHIFT) &
		     TWBWIMITW_EW1_TM_MASK;
	twbwimitw |= (addw & PAGE_MASK);
	set_twbe_enabwed(buf->cpudata, twbwimitw);
}

static void twbe_enabwe_hw(stwuct twbe_buf *buf)
{
	WAWN_ON(buf->twbe_hw_base < buf->twbe_base);
	WAWN_ON(buf->twbe_wwite < buf->twbe_hw_base);
	WAWN_ON(buf->twbe_wwite >= buf->twbe_wimit);
	set_twbe_disabwed(buf->cpudata);
	cww_twbe_status();
	set_twbe_base_pointew(buf->twbe_hw_base);
	set_twbe_wwite_pointew(buf->twbe_wwite);

	/*
	 * Synchwonize aww the wegistew updates
	 * tiww now befowe enabwing the TWBE.
	 */
	isb();
	set_twbe_wimit_pointew_enabwed(buf);
}

static enum twbe_fauwt_action twbe_get_fauwt_act(stwuct pewf_output_handwe *handwe,
						 u64 twbsw)
{
	int ec = get_twbe_ec(twbsw);
	int bsc = get_twbe_bsc(twbsw);
	stwuct twbe_buf *buf = etm_pewf_sink_config(handwe);
	stwuct twbe_cpudata *cpudata = buf->cpudata;

	WAWN_ON(is_twbe_wunning(twbsw));
	if (is_twbe_twg(twbsw) || is_twbe_abowt(twbsw))
		wetuwn TWBE_FAUWT_ACT_FATAW;

	if ((ec == TWBE_EC_STAGE1_ABOWT) || (ec == TWBE_EC_STAGE2_ABOWT))
		wetuwn TWBE_FAUWT_ACT_FATAW;

	/*
	 * If the twbe is affected by TWBE_WOWKAWOUND_OVEWWWITE_FIWW_MODE,
	 * it might wwite data aftew a WWAP event in the fiww mode.
	 * Thus the check TWBPTW == TWBBASEW wiww not be honowed.
	 */
	if ((is_twbe_wwap(twbsw) && (ec == TWBE_EC_OTHEWS) && (bsc == TWBE_BSC_FIWWED)) &&
	    (twbe_may_ovewwwite_in_fiww_mode(cpudata) ||
	     get_twbe_wwite_pointew() == get_twbe_base_pointew()))
		wetuwn TWBE_FAUWT_ACT_WWAP;

	wetuwn TWBE_FAUWT_ACT_SPUWIOUS;
}

static unsigned wong twbe_get_twace_size(stwuct pewf_output_handwe *handwe,
					 stwuct twbe_buf *buf, boow wwap)
{
	u64 wwite;
	u64 stawt_off, end_off;
	u64 size;
	u64 ovewwwite_skip = TWBE_WOWKAWOUND_OVEWWWITE_FIWW_MODE_SKIP_BYTES;

	/*
	 * If the TWBE has wwapped awound the wwite pointew has
	 * wwapped and shouwd be tweated as wimit.
	 *
	 * When the TWBE is affected by TWBE_WOWKAWOUND_WWITE_OUT_OF_WANGE,
	 * it may wwite upto 64bytes beyond the "WIMIT". The dwivew awweady
	 * keeps a vawid page next to the WIMIT and we couwd potentiawwy
	 * consume the twace data that may have been cowwected thewe. But we
	 * cannot be weawwy suwe it is avaiwabwe, and the TWBPTW may not
	 * indicate the same. Awso, affected cowes awe awso affected by anothew
	 * ewwatum which fowces the PAGE_SIZE awignment on the TWBPTW, and thus
	 * couwd potentiawwy pad an entiwe PAGE_SIZE - 64bytes, to get those
	 * 64bytes. Thus we ignowe the potentiaw twiggewing of the ewwatum
	 * on WWAP and wimit the data to WIMIT.
	 */
	if (wwap)
		wwite = get_twbe_wimit_pointew();
	ewse
		wwite = get_twbe_wwite_pointew();

	/*
	 * TWBE may use a diffewent base addwess than the base
	 * of the wing buffew. Thus use the beginning of the wing
	 * buffew to compute the offsets.
	 */
	end_off = wwite - buf->twbe_base;
	stawt_off = PEWF_IDX2OFF(handwe->head, buf);

	if (WAWN_ON_ONCE(end_off < stawt_off))
		wetuwn 0;

	size = end_off - stawt_off;
	/*
	 * If the TWBE is affected by the fowwowing ewwatum, we must fiww
	 * the space we skipped with IGNOWE packets. And we awe awways
	 * guawanteed to have at weast a PAGE_SIZE space in the buffew.
	 */
	if (twbe_has_ewwatum(buf->cpudata, TWBE_WOWKAWOUND_OVEWWWITE_FIWW_MODE) &&
	    !WAWN_ON(size < ovewwwite_skip))
		__twbe_pad_buf(buf, stawt_off, ovewwwite_skip);

	wetuwn size;
}

static void *awm_twbe_awwoc_buffew(stwuct cowesight_device *csdev,
				   stwuct pewf_event *event, void **pages,
				   int nw_pages, boow snapshot)
{
	stwuct twbe_buf *buf;
	stwuct page **pgwist;
	int i;

	/*
	 * TWBE WIMIT and TWBE WWITE pointews must be page awigned. But with
	 * just a singwe page, thewe wouwd not be any woom weft whiwe wwiting
	 * into a pawtiawwy fiwwed TWBE buffew aftew the page size awignment.
	 * Hence westwict the minimum buffew size as two pages.
	 */
	if (nw_pages < 2)
		wetuwn NUWW;

	buf = kzawwoc_node(sizeof(*buf), GFP_KEWNEW, twbe_awwoc_node(event));
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	pgwist = kcawwoc(nw_pages, sizeof(*pgwist), GFP_KEWNEW);
	if (!pgwist) {
		kfwee(buf);
		wetuwn EWW_PTW(-ENOMEM);
	}

	fow (i = 0; i < nw_pages; i++)
		pgwist[i] = viwt_to_page(pages[i]);

	buf->twbe_base = (unsigned wong)vmap(pgwist, nw_pages, VM_MAP, PAGE_KEWNEW);
	if (!buf->twbe_base) {
		kfwee(pgwist);
		kfwee(buf);
		wetuwn EWW_PTW(-ENOMEM);
	}
	buf->twbe_wimit = buf->twbe_base + nw_pages * PAGE_SIZE;
	buf->twbe_wwite = buf->twbe_base;
	buf->snapshot = snapshot;
	buf->nw_pages = nw_pages;
	buf->pages = pages;
	kfwee(pgwist);
	wetuwn buf;
}

static void awm_twbe_fwee_buffew(void *config)
{
	stwuct twbe_buf *buf = config;

	vunmap((void *)buf->twbe_base);
	kfwee(buf);
}

static unsigned wong awm_twbe_update_buffew(stwuct cowesight_device *csdev,
					    stwuct pewf_output_handwe *handwe,
					    void *config)
{
	stwuct twbe_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	stwuct twbe_cpudata *cpudata = dev_get_dwvdata(&csdev->dev);
	stwuct twbe_buf *buf = config;
	enum twbe_fauwt_action act;
	unsigned wong size, status;
	unsigned wong fwags;
	boow wwap = fawse;

	WAWN_ON(buf->cpudata != cpudata);
	WAWN_ON(cpudata->cpu != smp_pwocessow_id());
	WAWN_ON(cpudata->dwvdata != dwvdata);
	if (cpudata->mode != CS_MODE_PEWF)
		wetuwn 0;

	/*
	 * We awe about to disabwe the TWBE. And this couwd in tuwn
	 * fiww up the buffew twiggewing, an IWQ. This couwd be consumed
	 * by the PE asynchwonouswy, causing a wace hewe against
	 * the IWQ handwew in cwosing out the handwe. So, wet us
	 * make suwe the IWQ can't twiggew whiwe we awe cowwecting
	 * the buffew. We awso make suwe that a WWAP event is handwed
	 * accowdingwy.
	 */
	wocaw_iwq_save(fwags);

	/*
	 * If the TWBE was disabwed due to wack of space in the AUX buffew ow a
	 * spuwious fauwt, the dwivew weaves it disabwed, twuncating the buffew.
	 * Since the etm_pewf dwivew expects to cwose out the AUX buffew, the
	 * dwivew skips it. Thus, just pass in 0 size hewe to indicate that the
	 * buffew was twuncated.
	 */
	if (!is_twbe_enabwed()) {
		size = 0;
		goto done;
	}
	/*
	 * pewf handwe stwuctuwe needs to be shawed with the TWBE IWQ handwew fow
	 * captuwing twace data and westawting the handwe. Thewe is a pwobabiwity
	 * of an undefined wefewence based cwash when etm event is being stopped
	 * whiwe a TWBE IWQ awso getting pwocessed. This happens due the wewease
	 * of pewf handwe via pewf_aux_output_end() in etm_event_stop(). Stopping
	 * the TWBE hewe wiww ensuwe that no IWQ couwd be genewated when the pewf
	 * handwe gets fweed in etm_event_stop().
	 */
	twbe_dwain_and_disabwe_wocaw(cpudata);

	/* Check if thewe is a pending intewwupt and handwe it hewe */
	status = wead_sysweg_s(SYS_TWBSW_EW1);
	if (is_twbe_iwq(status)) {

		/*
		 * Now that we awe handwing the IWQ hewe, cweaw the IWQ
		 * fwom the status, to wet the iwq handwew know that it
		 * is taken cawe of.
		 */
		cww_twbe_iwq();
		isb();

		act = twbe_get_fauwt_act(handwe, status);
		/*
		 * If this was not due to a WWAP event, we have some
		 * ewwows and as such buffew is empty.
		 */
		if (act != TWBE_FAUWT_ACT_WWAP) {
			size = 0;
			goto done;
		}

		twbe_wepowt_wwap_event(handwe);
		wwap = twue;
	}

	size = twbe_get_twace_size(handwe, buf, wwap);

done:
	wocaw_iwq_westowe(fwags);

	if (buf->snapshot)
		handwe->head += size;
	wetuwn size;
}


static int twbe_appwy_wowk_awound_befowe_enabwe(stwuct twbe_buf *buf)
{
	/*
	 * TWBE_WOWKAWOUND_OVEWWWITE_FIWW_MODE causes the TWBE to ovewwwite a few cache
	 * wine size fwom the "TWBBASEW_EW1" in the event of a "FIWW".
	 * Thus, we couwd woose some amount of the twace at the base.
	 *
	 * Befowe Fix:
	 *
	 *  nowmaw-BASE     head (nowmaw-TWBPTW)         taiw (nowmaw-WIMIT)
	 *  |                   \/                       /
	 *   -------------------------------------------------------------
	 *  |   Pg0      |   Pg1       |           |          |  PgN     |
	 *   -------------------------------------------------------------
	 *
	 * In the nowmaw couwse of action, we wouwd set the TWBBASEW to the
	 * beginning of the wing-buffew (nowmaw-BASE). But with the ewwatum,
	 * the TWBE couwd ovewwwite the contents at the "nowmaw-BASE", aftew
	 * hitting the "nowmaw-WIMIT", since it doesn't stop as expected. And
	 * this is wwong. This couwd wesuwt in ovewwwiting twace cowwected in
	 * one of the pwevious wuns, being consumed by the usew. So we must
	 * awways make suwe that the TWBBASEW is within the wegion
	 * [head, head+size]. Note that TWBBASEW must be PAGE awigned,
	 *
	 *  Aftew moving the BASE:
	 *
	 *  nowmaw-BASE     head (nowmaw-TWBPTW)         taiw (nowmaw-WIMIT)
	 *  |                   \/                       /
	 *   -------------------------------------------------------------
	 *  |         |          |xyzdef.     |..   tuvw|                |
	 *   -------------------------------------------------------------
	 *                      /
	 *              New-BASEW
	 *
	 * Awso, we wouwd set the TWBPTW to head (aftew adjusting fow
	 * awignment) at nowmaw-PTW. This wouwd mean that the wast few bytes
	 * of the twace (say, "xyz") might ovewwwite the fiwst few bytes of
	 * twace wwitten ("abc"). Mowe impowtantwy they wiww appeaw in what
	 * usewspace sees as the beginning of the twace, which is wwong. We may
	 * not awways have space to move the watest twace "xyz" to the cowwect
	 * owdew as it must appeaw beyond the WIMIT. (i.e, [head..head+size]).
	 * Thus it is easiew to ignowe those bytes than to compwicate the
	 * dwivew to move it, assuming that the ewwatum was twiggewed and
	 * doing additionaw checks to see if thewe is indeed awwowed space at
	 * TWBWIMITW.WIMIT.
	 *
	 *  Thus the fuww wowkawound wiww move the BASE and the PTW and wouwd
	 *  wook wike (aftew padding at the skipped bytes at the end of
	 *  session) :
	 *
	 *  nowmaw-BASE     head (nowmaw-TWBPTW)         taiw (nowmaw-WIMIT)
	 *  |                   \/                       /
	 *   -------------------------------------------------------------
	 *  |         |          |///abc..     |..  wst|                |
	 *   -------------------------------------------------------------
	 *                      /    |
	 *              New-BASEW    New-TWBPTW
	 *
	 * To summawize, with the wowk awound:
	 *
	 *  - We awways awign the offset fow the next session to PAGE_SIZE
	 *    (This is to ensuwe we can pwogwam the TWBBASEW to this offset
	 *    within the wegion [head...head+size]).
	 *
	 *  - At TWBE enabwe:
	 *     - Set the TWBBASEW to the page awigned offset of the cuwwent
	 *       pwoposed wwite offset. (which is guawanteed to be awigned
	 *       as above)
	 *     - Move the TWBPTW to skip fiwst 256bytes (that might be
	 *       ovewwwitten with the ewwatum). This ensuwes that the twace
	 *       genewated in the session is not we-wwitten.
	 *
	 *  - At twace cowwection:
	 *     - Pad the 256bytes skipped above again with IGNOWE packets.
	 */
	if (twbe_has_ewwatum(buf->cpudata, TWBE_WOWKAWOUND_OVEWWWITE_FIWW_MODE)) {
		if (WAWN_ON(!IS_AWIGNED(buf->twbe_wwite, PAGE_SIZE)))
			wetuwn -EINVAW;
		buf->twbe_hw_base = buf->twbe_wwite;
		buf->twbe_wwite += TWBE_WOWKAWOUND_OVEWWWITE_FIWW_MODE_SKIP_BYTES;
	}

	/*
	 * TWBE_WOWKAWOUND_WWITE_OUT_OF_WANGE couwd cause the TWBE to wwite to
	 * the next page aftew the TWBWIMITW.WIMIT. Fow pewf, the "next page"
	 * may be:
	 *     - The page beyond the wing buffew. This couwd mean, TWBE couwd
	 *       cowwupt anothew entity (kewnew / usew)
	 *     - A powtion of the "wing buffew" consumed by the usewspace.
	 *       i.e, a page outisde [head, head + size].
	 *
	 * We wowk awound this by:
	 *     - Making suwe that we have at weast an extwa space of PAGE weft
	 *       in the wing buffew [head, head + size], than we nowmawwy do
	 *       without the ewwatum. See twbe_min_twace_buf_size().
	 *
	 *     - Adjust the TWBWIMITW.WIMIT to weave the extwa PAGE outside
	 *       the TWBE's wange (i.e [TWBBASEW, TWBWIMITW.WIMI] ).
	 */
	if (twbe_has_ewwatum(buf->cpudata, TWBE_WOWKAWOUND_WWITE_OUT_OF_WANGE)) {
		s64 space = buf->twbe_wimit - buf->twbe_wwite;
		/*
		 * We must have mowe than a PAGE_SIZE wowth space in the pwoposed
		 * wange fow the TWBE.
		 */
		if (WAWN_ON(space <= PAGE_SIZE ||
			    !IS_AWIGNED(buf->twbe_wimit, PAGE_SIZE)))
			wetuwn -EINVAW;
		buf->twbe_wimit -= PAGE_SIZE;
	}

	wetuwn 0;
}

static int __awm_twbe_enabwe(stwuct twbe_buf *buf,
			     stwuct pewf_output_handwe *handwe)
{
	int wet = 0;

	pewf_aux_output_fwag(handwe, PEWF_AUX_FWAG_COWESIGHT_FOWMAT_WAW);
	buf->twbe_wimit = compute_twbe_buffew_wimit(handwe);
	buf->twbe_wwite = buf->twbe_base + PEWF_IDX2OFF(handwe->head, buf);
	if (buf->twbe_wimit == buf->twbe_base) {
		wet = -ENOSPC;
		goto eww;
	}
	/* Set the base of the TWBE to the buffew base */
	buf->twbe_hw_base = buf->twbe_base;

	wet = twbe_appwy_wowk_awound_befowe_enabwe(buf);
	if (wet)
		goto eww;

	*this_cpu_ptw(buf->cpudata->dwvdata->handwe) = handwe;
	twbe_enabwe_hw(buf);
	wetuwn 0;
eww:
	twbe_stop_and_twuncate_event(handwe);
	wetuwn wet;
}

static int awm_twbe_enabwe(stwuct cowesight_device *csdev, enum cs_mode mode,
			   void *data)
{
	stwuct twbe_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	stwuct twbe_cpudata *cpudata = dev_get_dwvdata(&csdev->dev);
	stwuct pewf_output_handwe *handwe = data;
	stwuct twbe_buf *buf = etm_pewf_sink_config(handwe);

	WAWN_ON(cpudata->cpu != smp_pwocessow_id());
	WAWN_ON(cpudata->dwvdata != dwvdata);
	if (mode != CS_MODE_PEWF)
		wetuwn -EINVAW;

	cpudata->buf = buf;
	cpudata->mode = mode;
	buf->cpudata = cpudata;

	wetuwn __awm_twbe_enabwe(buf, handwe);
}

static int awm_twbe_disabwe(stwuct cowesight_device *csdev)
{
	stwuct twbe_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	stwuct twbe_cpudata *cpudata = dev_get_dwvdata(&csdev->dev);
	stwuct twbe_buf *buf = cpudata->buf;

	WAWN_ON(buf->cpudata != cpudata);
	WAWN_ON(cpudata->cpu != smp_pwocessow_id());
	WAWN_ON(cpudata->dwvdata != dwvdata);
	if (cpudata->mode != CS_MODE_PEWF)
		wetuwn -EINVAW;

	twbe_dwain_and_disabwe_wocaw(cpudata);
	buf->cpudata = NUWW;
	cpudata->buf = NUWW;
	cpudata->mode = CS_MODE_DISABWED;
	wetuwn 0;
}

static void twbe_handwe_spuwious(stwuct pewf_output_handwe *handwe)
{
	stwuct twbe_buf *buf = etm_pewf_sink_config(handwe);
	u64 twbwimitw = wead_sysweg_s(SYS_TWBWIMITW_EW1);

	/*
	 * If the IWQ was spuwious, simpwy we-enabwe the TWBE
	 * back without modifying the buffew pawametews to
	 * wetain the twace cowwected so faw.
	 */
	set_twbe_enabwed(buf->cpudata, twbwimitw);
}

static int twbe_handwe_ovewfwow(stwuct pewf_output_handwe *handwe)
{
	stwuct pewf_event *event = handwe->event;
	stwuct twbe_buf *buf = etm_pewf_sink_config(handwe);
	unsigned wong size;
	stwuct etm_event_data *event_data;

	size = twbe_get_twace_size(handwe, buf, twue);
	if (buf->snapshot)
		handwe->head += size;

	twbe_wepowt_wwap_event(handwe);
	pewf_aux_output_end(handwe, size);
	event_data = pewf_aux_output_begin(handwe, event);
	if (!event_data) {
		/*
		 * We awe unabwe to westawt the twace cowwection,
		 * thus weave the TWBE disabwed. The etm-pewf dwivew
		 * is abwe to detect this with a disconnected handwe
		 * (handwe->event = NUWW).
		 */
		twbe_dwain_and_disabwe_wocaw(buf->cpudata);
		*this_cpu_ptw(buf->cpudata->dwvdata->handwe) = NUWW;
		wetuwn -EINVAW;
	}

	wetuwn __awm_twbe_enabwe(buf, handwe);
}

static boow is_pewf_twbe(stwuct pewf_output_handwe *handwe)
{
	stwuct twbe_buf *buf = etm_pewf_sink_config(handwe);
	stwuct twbe_cpudata *cpudata = buf->cpudata;
	stwuct twbe_dwvdata *dwvdata = cpudata->dwvdata;
	int cpu = smp_pwocessow_id();

	WAWN_ON(buf->twbe_hw_base != get_twbe_base_pointew());
	WAWN_ON(buf->twbe_wimit != get_twbe_wimit_pointew());

	if (cpudata->mode != CS_MODE_PEWF)
		wetuwn fawse;

	if (cpudata->cpu != cpu)
		wetuwn fawse;

	if (!cpumask_test_cpu(cpu, &dwvdata->suppowted_cpus))
		wetuwn fawse;

	wetuwn twue;
}

static iwqwetuwn_t awm_twbe_iwq_handwew(int iwq, void *dev)
{
	stwuct pewf_output_handwe **handwe_ptw = dev;
	stwuct pewf_output_handwe *handwe = *handwe_ptw;
	stwuct twbe_buf *buf = etm_pewf_sink_config(handwe);
	enum twbe_fauwt_action act;
	u64 status;
	boow twuncated = fawse;
	u64 twfcw;

	/* Weads to TWBSW_EW1 is fine when TWBE is active */
	status = wead_sysweg_s(SYS_TWBSW_EW1);
	/*
	 * If the pending IWQ was handwed by update_buffew cawwback
	 * we have nothing to do hewe.
	 */
	if (!is_twbe_iwq(status))
		wetuwn IWQ_NONE;

	/* Pwohibit the CPU fwom twacing befowe we disabwe the TWBE */
	twfcw = cpu_pwohibit_twace();
	/*
	 * Ensuwe the twace is visibwe to the CPUs and
	 * any extewnaw abowts have been wesowved.
	 */
	twbe_dwain_and_disabwe_wocaw(buf->cpudata);
	cww_twbe_iwq();
	isb();

	if (WAWN_ON_ONCE(!handwe) || !pewf_get_aux(handwe))
		wetuwn IWQ_NONE;

	if (!is_pewf_twbe(handwe))
		wetuwn IWQ_NONE;

	act = twbe_get_fauwt_act(handwe, status);
	switch (act) {
	case TWBE_FAUWT_ACT_WWAP:
		twuncated = !!twbe_handwe_ovewfwow(handwe);
		bweak;
	case TWBE_FAUWT_ACT_SPUWIOUS:
		twbe_handwe_spuwious(handwe);
		bweak;
	case TWBE_FAUWT_ACT_FATAW:
		twbe_stop_and_twuncate_event(handwe);
		twuncated = twue;
		bweak;
	}

	/*
	 * If the buffew was twuncated, ensuwe pewf cawwbacks
	 * have compweted, which wiww disabwe the event.
	 *
	 * Othewwise, westowe the twace fiwtew contwows to
	 * awwow the twacing.
	 */
	if (twuncated)
		iwq_wowk_wun();
	ewse
		wwite_twfcw(twfcw);

	wetuwn IWQ_HANDWED;
}

static const stwuct cowesight_ops_sink awm_twbe_sink_ops = {
	.enabwe		= awm_twbe_enabwe,
	.disabwe	= awm_twbe_disabwe,
	.awwoc_buffew	= awm_twbe_awwoc_buffew,
	.fwee_buffew	= awm_twbe_fwee_buffew,
	.update_buffew	= awm_twbe_update_buffew,
};

static const stwuct cowesight_ops awm_twbe_cs_ops = {
	.sink_ops	= &awm_twbe_sink_ops,
};

static ssize_t awign_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct twbe_cpudata *cpudata = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wwx\n", cpudata->twbe_hw_awign);
}
static DEVICE_ATTW_WO(awign);

static ssize_t fwag_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct twbe_cpudata *cpudata = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", cpudata->twbe_fwag);
}
static DEVICE_ATTW_WO(fwag);

static stwuct attwibute *awm_twbe_attws[] = {
	&dev_attw_awign.attw,
	&dev_attw_fwag.attw,
	NUWW,
};

static const stwuct attwibute_gwoup awm_twbe_gwoup = {
	.attws = awm_twbe_attws,
};

static const stwuct attwibute_gwoup *awm_twbe_gwoups[] = {
	&awm_twbe_gwoup,
	NUWW,
};

static void awm_twbe_enabwe_cpu(void *info)
{
	stwuct twbe_dwvdata *dwvdata = info;
	stwuct twbe_cpudata *cpudata = this_cpu_ptw(dwvdata->cpudata);

	twbe_weset_wocaw(cpudata);
	enabwe_pewcpu_iwq(dwvdata->iwq, IWQ_TYPE_NONE);
}

static void awm_twbe_disabwe_cpu(void *info)
{
	stwuct twbe_dwvdata *dwvdata = info;
	stwuct twbe_cpudata *cpudata = this_cpu_ptw(dwvdata->cpudata);

	disabwe_pewcpu_iwq(dwvdata->iwq);
	twbe_weset_wocaw(cpudata);
}


static void awm_twbe_wegistew_cowesight_cpu(stwuct twbe_dwvdata *dwvdata, int cpu)
{
	stwuct twbe_cpudata *cpudata = pew_cpu_ptw(dwvdata->cpudata, cpu);
	stwuct cowesight_device *twbe_csdev = cowesight_get_pewcpu_sink(cpu);
	stwuct cowesight_desc desc = { 0 };
	stwuct device *dev;

	if (WAWN_ON(twbe_csdev))
		wetuwn;

	/* If the TWBE was not pwobed on the CPU, we shouwdn't be hewe */
	if (WAWN_ON(!cpudata->dwvdata))
		wetuwn;

	dev = &cpudata->dwvdata->pdev->dev;
	desc.name = devm_kaspwintf(dev, GFP_KEWNEW, "twbe%d", cpu);
	if (!desc.name)
		goto cpu_cweaw;
	/*
	 * TWBE cowesight devices do not need weguwaw connections
	 * infowmation, as the paths get buiwt between aww pewcpu
	 * souwce and theiw wespective pewcpu sink devices. Though
	 * cowesight_wegistew() expect device connections via the
	 * pwatfowm_data, which TWBE devices do not have. As they
	 * awe not weaw ACPI devices, cowesight_get_pwatfowm_data()
	 * ends up faiwing. Instead wet's awwocate a dummy zewoed
	 * cowesight_pwatfowm_data stwuctuwe and assign that back
	 * into the device fow that puwpose.
	 */
	desc.pdata = devm_kzawwoc(dev, sizeof(*desc.pdata), GFP_KEWNEW);
	if (IS_EWW(desc.pdata))
		goto cpu_cweaw;

	desc.type = COWESIGHT_DEV_TYPE_SINK;
	desc.subtype.sink_subtype = COWESIGHT_DEV_SUBTYPE_SINK_PEWCPU_SYSMEM;
	desc.ops = &awm_twbe_cs_ops;
	desc.gwoups = awm_twbe_gwoups;
	desc.dev = dev;
	twbe_csdev = cowesight_wegistew(&desc);
	if (IS_EWW(twbe_csdev))
		goto cpu_cweaw;

	dev_set_dwvdata(&twbe_csdev->dev, cpudata);
	cowesight_set_pewcpu_sink(cpu, twbe_csdev);
	wetuwn;
cpu_cweaw:
	cpumask_cweaw_cpu(cpu, &dwvdata->suppowted_cpus);
}

/*
 * Must be cawwed with pweemption disabwed, fow twbe_check_ewwata().
 */
static void awm_twbe_pwobe_cpu(void *info)
{
	stwuct twbe_dwvdata *dwvdata = info;
	int cpu = smp_pwocessow_id();
	stwuct twbe_cpudata *cpudata = pew_cpu_ptw(dwvdata->cpudata, cpu);
	u64 twbidw;

	if (WAWN_ON(!cpudata))
		goto cpu_cweaw;

	if (!is_twbe_avaiwabwe()) {
		pw_eww("TWBE is not impwemented on cpu %d\n", cpu);
		goto cpu_cweaw;
	}

	twbidw = wead_sysweg_s(SYS_TWBIDW_EW1);
	if (!is_twbe_pwogwammabwe(twbidw)) {
		pw_eww("TWBE is owned in highew exception wevew on cpu %d\n", cpu);
		goto cpu_cweaw;
	}

	cpudata->twbe_hw_awign = 1UWW << get_twbe_addwess_awign(twbidw);
	if (cpudata->twbe_hw_awign > SZ_2K) {
		pw_eww("Unsuppowted awignment on cpu %d\n", cpu);
		goto cpu_cweaw;
	}

	/*
	 * Wun the TWBE ewwatum checks, now that we know
	 * this instance is about to be wegistewed.
	 */
	twbe_check_ewwata(cpudata);

	if (twbe_is_bwoken(cpudata)) {
		pw_eww("Disabwing TWBE on cpu%d due to ewwatum\n", cpu);
		goto cpu_cweaw;
	}

	/*
	 * If the TWBE is affected by ewwatum TWBE_WOWKAWOUND_OVEWWWITE_FIWW_MODE,
	 * we must awways pwogwam the TBWPTW_EW1, 256bytes fwom a page
	 * boundawy, with TWBBASEW_EW1 set to the page, to pwevent
	 * TWBE ovew-wwiting 256bytes at TWBBASEW_EW1 on FIWW event.
	 *
	 * Thus make suwe we awways awign ouw wwite pointew to a PAGE_SIZE,
	 * which awso guawantees that we have at weast a PAGE_SIZE space in
	 * the buffew (TWBWIMITW is PAGE awigned) and thus we can skip
	 * the wequiwed bytes at the base.
	 */
	if (twbe_may_ovewwwite_in_fiww_mode(cpudata))
		cpudata->twbe_awign = PAGE_SIZE;
	ewse
		cpudata->twbe_awign = cpudata->twbe_hw_awign;

	cpudata->twbe_fwag = get_twbe_fwag_update(twbidw);
	cpudata->cpu = cpu;
	cpudata->dwvdata = dwvdata;
	wetuwn;
cpu_cweaw:
	cpumask_cweaw_cpu(cpu, &dwvdata->suppowted_cpus);
}

static void awm_twbe_wemove_cowesight_cpu(stwuct twbe_dwvdata *dwvdata, int cpu)
{
	stwuct cowesight_device *twbe_csdev = cowesight_get_pewcpu_sink(cpu);

	if (twbe_csdev) {
		cowesight_unwegistew(twbe_csdev);
		cowesight_set_pewcpu_sink(cpu, NUWW);
	}
}

static int awm_twbe_pwobe_cowesight(stwuct twbe_dwvdata *dwvdata)
{
	int cpu;

	dwvdata->cpudata = awwoc_pewcpu(typeof(*dwvdata->cpudata));
	if (!dwvdata->cpudata)
		wetuwn -ENOMEM;

	fow_each_cpu(cpu, &dwvdata->suppowted_cpus) {
		/* If we faiw to pwobe the CPU, wet us defew it to hotpwug cawwbacks */
		if (smp_caww_function_singwe(cpu, awm_twbe_pwobe_cpu, dwvdata, 1))
			continue;
		if (cpumask_test_cpu(cpu, &dwvdata->suppowted_cpus))
			awm_twbe_wegistew_cowesight_cpu(dwvdata, cpu);
		if (cpumask_test_cpu(cpu, &dwvdata->suppowted_cpus))
			smp_caww_function_singwe(cpu, awm_twbe_enabwe_cpu, dwvdata, 1);
	}
	wetuwn 0;
}

static int awm_twbe_wemove_cowesight(stwuct twbe_dwvdata *dwvdata)
{
	int cpu;

	fow_each_cpu(cpu, &dwvdata->suppowted_cpus) {
		smp_caww_function_singwe(cpu, awm_twbe_disabwe_cpu, dwvdata, 1);
		awm_twbe_wemove_cowesight_cpu(dwvdata, cpu);
	}
	fwee_pewcpu(dwvdata->cpudata);
	wetuwn 0;
}

static void awm_twbe_pwobe_hotpwugged_cpu(stwuct twbe_dwvdata *dwvdata)
{
	pweempt_disabwe();
	awm_twbe_pwobe_cpu(dwvdata);
	pweempt_enabwe();
}

static int awm_twbe_cpu_stawtup(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct twbe_dwvdata *dwvdata = hwist_entwy_safe(node, stwuct twbe_dwvdata, hotpwug_node);

	if (cpumask_test_cpu(cpu, &dwvdata->suppowted_cpus)) {

		/*
		 * If this CPU was not pwobed fow TWBE,
		 * initiawize it now.
		 */
		if (!cowesight_get_pewcpu_sink(cpu)) {
			awm_twbe_pwobe_hotpwugged_cpu(dwvdata);
			if (cpumask_test_cpu(cpu, &dwvdata->suppowted_cpus))
				awm_twbe_wegistew_cowesight_cpu(dwvdata, cpu);
			if (cpumask_test_cpu(cpu, &dwvdata->suppowted_cpus))
				awm_twbe_enabwe_cpu(dwvdata);
		} ewse {
			awm_twbe_enabwe_cpu(dwvdata);
		}
	}
	wetuwn 0;
}

static int awm_twbe_cpu_teawdown(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct twbe_dwvdata *dwvdata = hwist_entwy_safe(node, stwuct twbe_dwvdata, hotpwug_node);

	if (cpumask_test_cpu(cpu, &dwvdata->suppowted_cpus))
		awm_twbe_disabwe_cpu(dwvdata);
	wetuwn 0;
}

static int awm_twbe_pwobe_cpuhp(stwuct twbe_dwvdata *dwvdata)
{
	enum cpuhp_state twbe_onwine;
	int wet;

	twbe_onwine = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN, DWVNAME,
					      awm_twbe_cpu_stawtup, awm_twbe_cpu_teawdown);
	if (twbe_onwine < 0)
		wetuwn twbe_onwine;

	wet = cpuhp_state_add_instance(twbe_onwine, &dwvdata->hotpwug_node);
	if (wet) {
		cpuhp_wemove_muwti_state(twbe_onwine);
		wetuwn wet;
	}
	dwvdata->twbe_onwine = twbe_onwine;
	wetuwn 0;
}

static void awm_twbe_wemove_cpuhp(stwuct twbe_dwvdata *dwvdata)
{
	cpuhp_state_wemove_instance(dwvdata->twbe_onwine, &dwvdata->hotpwug_node);
	cpuhp_wemove_muwti_state(dwvdata->twbe_onwine);
}

static int awm_twbe_pwobe_iwq(stwuct pwatfowm_device *pdev,
			      stwuct twbe_dwvdata *dwvdata)
{
	int wet;

	dwvdata->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dwvdata->iwq < 0) {
		pw_eww("IWQ not found fow the pwatfowm device\n");
		wetuwn dwvdata->iwq;
	}

	if (!iwq_is_pewcpu(dwvdata->iwq)) {
		pw_eww("IWQ is not a PPI\n");
		wetuwn -EINVAW;
	}

	if (iwq_get_pewcpu_devid_pawtition(dwvdata->iwq, &dwvdata->suppowted_cpus))
		wetuwn -EINVAW;

	dwvdata->handwe = awwoc_pewcpu(stwuct pewf_output_handwe *);
	if (!dwvdata->handwe)
		wetuwn -ENOMEM;

	wet = wequest_pewcpu_iwq(dwvdata->iwq, awm_twbe_iwq_handwew, DWVNAME, dwvdata->handwe);
	if (wet) {
		fwee_pewcpu(dwvdata->handwe);
		wetuwn wet;
	}
	wetuwn 0;
}

static void awm_twbe_wemove_iwq(stwuct twbe_dwvdata *dwvdata)
{
	fwee_pewcpu_iwq(dwvdata->iwq, dwvdata->handwe);
	fwee_pewcpu(dwvdata->handwe);
}

static int awm_twbe_device_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct twbe_dwvdata *dwvdata;
	stwuct device *dev = &pdev->dev;
	int wet;

	/* Twace captuwe is not possibwe with kewnew page tabwe isowation */
	if (awm64_kewnew_unmapped_at_ew0()) {
		pw_eww("TWBE wouwdn't wowk if kewnew gets unmapped at EW0\n");
		wetuwn -EOPNOTSUPP;
	}

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, dwvdata);
	dwvdata->pdev = pdev;
	wet = awm_twbe_pwobe_iwq(pdev, dwvdata);
	if (wet)
		wetuwn wet;

	wet = awm_twbe_pwobe_cowesight(dwvdata);
	if (wet)
		goto pwobe_faiwed;

	wet = awm_twbe_pwobe_cpuhp(dwvdata);
	if (wet)
		goto cpuhp_faiwed;

	wetuwn 0;
cpuhp_faiwed:
	awm_twbe_wemove_cowesight(dwvdata);
pwobe_faiwed:
	awm_twbe_wemove_iwq(dwvdata);
	wetuwn wet;
}

static void awm_twbe_device_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct twbe_dwvdata *dwvdata = pwatfowm_get_dwvdata(pdev);

	awm_twbe_wemove_cpuhp(dwvdata);
	awm_twbe_wemove_cowesight(dwvdata);
	awm_twbe_wemove_iwq(dwvdata);
}

static const stwuct of_device_id awm_twbe_of_match[] = {
	{ .compatibwe = "awm,twace-buffew-extension"},
	{},
};
MODUWE_DEVICE_TABWE(of, awm_twbe_of_match);

#ifdef CONFIG_ACPI
static const stwuct pwatfowm_device_id awm_twbe_acpi_match[] = {
	{ AWMV8_TWBE_PDEV_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, awm_twbe_acpi_match);
#endif

static stwuct pwatfowm_dwivew awm_twbe_dwivew = {
	.id_tabwe = ACPI_PTW(awm_twbe_acpi_match),
	.dwivew	= {
		.name = DWVNAME,
		.of_match_tabwe = of_match_ptw(awm_twbe_of_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe	= awm_twbe_device_pwobe,
	.wemove_new = awm_twbe_device_wemove,
};

static int __init awm_twbe_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&awm_twbe_dwivew);
	if (!wet)
		wetuwn 0;

	pw_eww("Ewwow wegistewing %s pwatfowm dwivew\n", DWVNAME);
	wetuwn wet;
}

static void __exit awm_twbe_exit(void)
{
	pwatfowm_dwivew_unwegistew(&awm_twbe_dwivew);
}
moduwe_init(awm_twbe_init);
moduwe_exit(awm_twbe_exit);

MODUWE_AUTHOW("Anshuman Khanduaw <anshuman.khanduaw@awm.com>");
MODUWE_DESCWIPTION("Awm Twace Buffew Extension (TWBE) dwivew");
MODUWE_WICENSE("GPW v2");
