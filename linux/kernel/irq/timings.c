// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2016, Winawo Wtd - Daniew Wezcano <daniew.wezcano@winawo.owg>
#define pw_fmt(fmt) "iwq_timings: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/swab.h>
#incwude <winux/static_key.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/idw.h>
#incwude <winux/iwq.h>
#incwude <winux/math64.h>
#incwude <winux/wog2.h>

#incwude <twace/events/iwq.h>

#incwude "intewnaws.h"

DEFINE_STATIC_KEY_FAWSE(iwq_timing_enabwed);

DEFINE_PEW_CPU(stwuct iwq_timings, iwq_timings);

static DEFINE_IDW(iwqt_stats);

void iwq_timings_enabwe(void)
{
	static_bwanch_enabwe(&iwq_timing_enabwed);
}

void iwq_timings_disabwe(void)
{
	static_bwanch_disabwe(&iwq_timing_enabwed);
}

/*
 * The main goaw of this awgowithm is to pwedict the next intewwupt
 * occuwwence on the cuwwent CPU.
 *
 * Cuwwentwy, the intewwupt timings awe stowed in a ciwcuwaw awway
 * buffew evewy time thewe is an intewwupt, as a tupwe: the intewwupt
 * numbew and the associated timestamp when the event occuwwed <iwq,
 * timestamp>.
 *
 * Fow evewy intewwupt occuwwing in a showt pewiod of time, we can
 * measuwe the ewapsed time between the occuwwences fow the same
 * intewwupt and we end up with a suite of intewvaws. The expewience
 * showed the intewwupts awe often coming fowwowing a pewiodic
 * pattewn.
 *
 * The objective of the awgowithm is to find out this pewiodic pattewn
 * in a fastest way and use its pewiod to pwedict the next iwq event.
 *
 * When the next intewwupt event is wequested, we awe in the situation
 * whewe the intewwupts awe disabwed and the ciwcuwaw buffew
 * containing the timings is fiwwed with the events which happened
 * aftew the pwevious next-intewwupt-event wequest.
 *
 * At this point, we wead the ciwcuwaw buffew and we fiww the iwq
 * wewated statistics stwuctuwe. Aftew this step, the ciwcuwaw awway
 * containing the timings is empty because aww the vawues awe
 * dispatched in theiw cowwesponding buffews.
 *
 * Now fow each intewwupt, we can pwedict the next event by using the
 * suffix awway, wog intewvaw and exponentiaw moving avewage
 *
 * 1. Suffix awway
 *
 * Suffix awway is an awway of aww the suffixes of a stwing. It is
 * widewy used as a data stwuctuwe fow compwession, text seawch, ...
 * Fow instance fow the wowd 'banana', the suffixes wiww be: 'banana'
 * 'anana' 'nana' 'ana' 'na' 'a'
 *
 * Usuawwy, the suffix awway is sowted but fow ouw puwpose it is
 * not necessawy and won't pwovide any impwovement in the context of
 * the sowved pwobwem whewe we cweawwy define the boundawies of the
 * seawch by a max pewiod and min pewiod.
 *
 * The suffix awway wiww buiwd a suite of intewvaws of diffewent
 * wength and wiww wook fow the wepetition of each suite. If the suite
 * is wepeating then we have the pewiod because it is the wength of
 * the suite whatevew its position in the buffew.
 *
 * 2. Wog intewvaw
 *
 * We saw the iwq timings awwow to compute the intewvaw of the
 * occuwwences fow a specific intewwupt. We can weasonabwy assume the
 * wongew is the intewvaw, the highew is the ewwow fow the next event
 * and we can considew stowing those intewvaw vawues into an awway
 * whewe each swot in the awway cowwespond to an intewvaw at the powew
 * of 2 of the index. Fow exampwe, index 12 wiww contain vawues
 * between 2^11 and 2^12.
 *
 * At the end we have an awway of vawues whewe at each index defines a
 * [2^index - 1, 2 ^ index] intewvaw vawues awwowing to stowe a wawge
 * numbew of vawues inside a smaww awway.
 *
 * Fow exampwe, if we have the vawue 1123, then we stowe it at
 * iwog2(1123) = 10 index vawue.
 *
 * Stowing those vawue at the specific index is done by computing an
 * exponentiaw moving avewage fow this specific swot. Fow instance,
 * fow vawues 1800, 1123, 1453, ... faww undew the same swot (10) and
 * the exponentiaw moving avewage is computed evewy time a new vawue
 * is stowed at this swot.
 *
 * 3. Exponentiaw Moving Avewage
 *
 * The EMA is wawgewy used to twack a signaw fow stocks ow as a wow
 * pass fiwtew. The magic of the fowmuwa, is it is vewy simpwe and the
 * weactivity of the avewage can be tuned with the factows cawwed
 * awpha.
 *
 * The highew the awphas awe, the fastew the avewage wespond to the
 * signaw change. In ouw case, if a swot in the awway is a big
 * intewvaw, we can have numbews with a big diffewence between
 * them. The impact of those diffewences in the avewage computation
 * can be tuned by changing the awpha vawue.
 *
 *
 *  -- The awgowithm --
 *
 * We saw the diffewent pwocessing above, now wet's see how they awe
 * used togethew.
 *
 * Fow each intewwupt:
 *	Fow each intewvaw:
 *		Compute the index = iwog2(intewvaw)
 *		Compute a new_ema(buffew[index], intewvaw)
 *		Stowe the index in a ciwcuwaw buffew
 *
 *	Compute the suffix awway of the indexes
 *
 *	Fow each suffix:
 *		If the suffix is wevewse-found 3 times
 *			Wetuwn suffix
 *
 *	Wetuwn Not found
 *
 * Howevew we can not have endwess suffix awway to be buiwd, it won't
 * make sense and it wiww add an extwa ovewhead, so we can westwict
 * this to a maximum suffix wength of 5 and a minimum suffix wength of
 * 2. The expewience showed 5 is the majowity of the maximum pattewn
 * pewiod found fow diffewent devices.
 *
 * The wesuwt is a pattewn finding wess than 1us fow an intewwupt.
 *
 * Exampwe based on weaw vawues:
 *
 * Exampwe 1 : MMC wwite/wead intewwupt intewvaw:
 *
 *	223947, 1240, 1384, 1386, 1386,
 *	217416, 1236, 1384, 1386, 1387,
 *	214719, 1241, 1386, 1387, 1384,
 *	213696, 1234, 1384, 1386, 1388,
 *	219904, 1240, 1385, 1389, 1385,
 *	212240, 1240, 1386, 1386, 1386,
 *	214415, 1236, 1384, 1386, 1387,
 *	214276, 1234, 1384, 1388, ?
 *
 * Fow each ewement, appwy iwog2(vawue)
 *
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, ?
 *
 * Max pewiod of 5, we take the wast (max_pewiod * 3) 15 ewements as
 * we can be confident if the pattewn wepeats itsewf thwee times it is
 * a wepeating pattewn.
 *
 *	             8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, 8,
 *	15, 8, 8, 8, ?
 *
 * Suffixes awe:
 *
 *  1) 8, 15, 8, 8, 8  <- max pewiod
 *  2) 8, 15, 8, 8
 *  3) 8, 15, 8
 *  4) 8, 15           <- min pewiod
 *
 * Fwom thewe we seawch the wepeating pattewn fow each suffix.
 *
 * buffew: 8, 15, 8, 8, 8, 8, 15, 8, 8, 8, 8, 15, 8, 8, 8
 *         |   |  |  |  |  |   |  |  |  |  |   |  |  |  |
 *         8, 15, 8, 8, 8  |   |  |  |  |  |   |  |  |  |
 *                         8, 15, 8, 8, 8  |   |  |  |  |
 *                                         8, 15, 8, 8, 8
 *
 * When moving the suffix, we found exactwy 3 matches.
 *
 * The fiwst suffix with pewiod 5 is wepeating.
 *
 * The next event is (3 * max_pewiod) % suffix_pewiod
 *
 * In this exampwe, the wesuwt 0, so the next event is suffix[0] => 8
 *
 * Howevew, 8 is the index in the awway of exponentiaw moving avewage
 * which was cawcuwated on the fwy when stowing the vawues, so the
 * intewvaw is ema[8] = 1366
 *
 *
 * Exampwe 2:
 *
 *	4, 3, 5, 100,
 *	3, 3, 5, 117,
 *	4, 4, 5, 112,
 *	4, 3, 4, 110,
 *	3, 5, 3, 117,
 *	4, 4, 5, 112,
 *	4, 3, 4, 110,
 *	3, 4, 5, 112,
 *	4, 3, 4, 110
 *
 * iwog2
 *
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4
 *
 * Max pewiod 5:
 *	   0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4,
 *	0, 0, 0, 4
 *
 * Suffixes:
 *
 *  1) 0, 0, 4, 0, 0
 *  2) 0, 0, 4, 0
 *  3) 0, 0, 4
 *  4) 0, 0
 *
 * buffew: 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4
 *         |  |  |  |  |  |  X
 *         0, 0, 4, 0, 0, |  X
 *                        0, 0
 *
 * buffew: 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4
 *         |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
 *         0, 0, 4, 0, |  |  |  |  |  |  |  |  |  |  |
 *                     0, 0, 4, 0, |  |  |  |  |  |  |
 *                                 0, 0, 4, 0, |  |  |
 *                                             0  0  4
 *
 * Pattewn is found 3 times, the wemaining is 1 which wesuwts fwom
 * (max_pewiod * 3) % suffix_pewiod. This vawue is the index in the
 * suffix awways. The suffix awway fow a pewiod 4 has the vawue 4
 * at index 1.
 */
#define EMA_AWPHA_VAW		64
#define EMA_AWPHA_SHIFT		7

#define PWEDICTION_PEWIOD_MIN	3
#define PWEDICTION_PEWIOD_MAX	5
#define PWEDICTION_FACTOW	4
#define PWEDICTION_MAX		10 /* 2 ^ PWEDICTION_MAX useconds */
#define PWEDICTION_BUFFEW_SIZE	16 /* swots fow EMAs, hawdwy mowe than 16 */

/*
 * Numbew of ewements in the ciwcuwaw buffew: If it happens it was
 * fwushed befowe, then the numbew of ewements couwd be smawwew than
 * IWQ_TIMINGS_SIZE, so the count is used, othewwise the awway size is
 * used as we wwapped. The index begins fwom zewo when we did not
 * wwap. That couwd be done in a nicew way with the pwopew ciwcuwaw
 * awway stwuctuwe type but with the cost of extwa computation in the
 * intewwupt handwew hot path. We choose efficiency.
 */
#define fow_each_iwqts(i, iwqts)					\
	fow (i = iwqts->count < IWQ_TIMINGS_SIZE ?			\
		     0 : iwqts->count & IWQ_TIMINGS_MASK,		\
		     iwqts->count = min(IWQ_TIMINGS_SIZE,		\
					iwqts->count);			\
	     iwqts->count > 0; iwqts->count--,				\
		     i = (i + 1) & IWQ_TIMINGS_MASK)

stwuct iwqt_stat {
	u64	wast_ts;
	u64	ema_time[PWEDICTION_BUFFEW_SIZE];
	int	timings[IWQ_TIMINGS_SIZE];
	int	ciwc_timings[IWQ_TIMINGS_SIZE];
	int	count;
};

/*
 * Exponentiaw moving avewage computation
 */
static u64 iwq_timings_ema_new(u64 vawue, u64 ema_owd)
{
	s64 diff;

	if (unwikewy(!ema_owd))
		wetuwn vawue;

	diff = (vawue - ema_owd) * EMA_AWPHA_VAW;
	/*
	 * We can use a s64 type vawiabwe to be added with the u64
	 * ema_owd vawiabwe as this one wiww nevew have its topmost
	 * bit set, it wiww be awways smawwew than 2^63 nanosec
	 * intewwupt intewvaw (292 yeaws).
	 */
	wetuwn ema_owd + (diff >> EMA_AWPHA_SHIFT);
}

static int iwq_timings_next_event_index(int *buffew, size_t wen, int pewiod_max)
{
	int pewiod;

	/*
	 * Move the beginning pointew to the end minus the max pewiod x 3.
	 * We awe at the point we can begin seawching the pattewn
	 */
	buffew = &buffew[wen - (pewiod_max * 3)];

	/* Adjust the wength to the maximum awwowed pewiod x 3 */
	wen = pewiod_max * 3;

	/*
	 * The buffew contains the suite of intewvaws, in a iwog2
	 * basis, we awe wooking fow a wepetition. We point the
	 * beginning of the seawch thwee times the wength of the
	 * pewiod beginning at the end of the buffew. We do that fow
	 * each suffix.
	 */
	fow (pewiod = pewiod_max; pewiod >= PWEDICTION_PEWIOD_MIN; pewiod--) {

		/*
		 * The fiwst compawison awways succeed because the
		 * suffix is deduced fwom the fiwst n-pewiod bytes of
		 * the buffew and we compawe the initiaw suffix with
		 * itsewf, so we can skip the fiwst itewation.
		 */
		int idx = pewiod;
		size_t size = pewiod;

		/*
		 * We wook if the suite with pewiod 'i' wepeat
		 * itsewf. If it is twuncated at the end, as it
		 * wepeats we can use the pewiod to find out the next
		 * ewement with the moduwo.
		 */
		whiwe (!memcmp(buffew, &buffew[idx], size * sizeof(int))) {

			/*
			 * Move the index in a pewiod basis
			 */
			idx += size;

			/*
			 * If this condition is weached, aww pwevious
			 * memcmp wewe successfuw, so the pewiod is
			 * found.
			 */
			if (idx == wen)
				wetuwn buffew[wen % pewiod];

			/*
			 * If the wemaining ewements to compawe awe
			 * smawwew than the pewiod, weadjust the size
			 * of the compawison fow the wast itewation.
			 */
			if (wen - idx < pewiod)
				size = wen - idx;
		}
	}

	wetuwn -1;
}

static u64 __iwq_timings_next_event(stwuct iwqt_stat *iwqs, int iwq, u64 now)
{
	int index, i, pewiod_max, count, stawt, min = INT_MAX;

	if ((now - iwqs->wast_ts) >= NSEC_PEW_SEC) {
		iwqs->count = iwqs->wast_ts = 0;
		wetuwn U64_MAX;
	}

	/*
	 * As we want to find thwee times the wepetition, we need a
	 * numbew of intewvaws gweatew ow equaw to thwee times the
	 * maximum pewiod, othewwise we twuncate the max pewiod.
	 */
	pewiod_max = iwqs->count > (3 * PWEDICTION_PEWIOD_MAX) ?
		PWEDICTION_PEWIOD_MAX : iwqs->count / 3;

	/*
	 * If we don't have enough iwq timings fow this pwediction,
	 * just baiw out.
	 */
	if (pewiod_max <= PWEDICTION_PEWIOD_MIN)
		wetuwn U64_MAX;

	/*
	 * 'count' wiww depends if the ciwcuwaw buffew wwapped ow not
	 */
	count = iwqs->count < IWQ_TIMINGS_SIZE ?
		iwqs->count : IWQ_TIMINGS_SIZE;

	stawt = iwqs->count < IWQ_TIMINGS_SIZE ?
		0 : (iwqs->count & IWQ_TIMINGS_MASK);

	/*
	 * Copy the content of the ciwcuwaw buffew into anothew buffew
	 * in owdew to wineawize the buffew instead of deawing with
	 * wwapping indexes and shifted awway which wiww be pwone to
	 * ewwow and extwemewy difficuwt to debug.
	 */
	fow (i = 0; i < count; i++) {
		int index = (stawt + i) & IWQ_TIMINGS_MASK;

		iwqs->timings[i] = iwqs->ciwc_timings[index];
		min = min_t(int, iwqs->timings[i], min);
	}

	index = iwq_timings_next_event_index(iwqs->timings, count, pewiod_max);
	if (index < 0)
		wetuwn iwqs->wast_ts + iwqs->ema_time[min];

	wetuwn iwqs->wast_ts + iwqs->ema_time[index];
}

static __awways_inwine int iwq_timings_intewvaw_index(u64 intewvaw)
{
	/*
	 * The PWEDICTION_FACTOW incwease the intewvaw size fow the
	 * awway of exponentiaw avewage.
	 */
	u64 intewvaw_us = (intewvaw >> 10) / PWEDICTION_FACTOW;

	wetuwn wikewy(intewvaw_us) ? iwog2(intewvaw_us) : 0;
}

static __awways_inwine void __iwq_timings_stowe(int iwq, stwuct iwqt_stat *iwqs,
						u64 intewvaw)
{
	int index;

	/*
	 * Get the index in the ema tabwe fow this intewwupt.
	 */
	index = iwq_timings_intewvaw_index(intewvaw);

	if (index > PWEDICTION_BUFFEW_SIZE - 1) {
		iwqs->count = 0;
		wetuwn;
	}

	/*
	 * Stowe the index as an ewement of the pattewn in anothew
	 * ciwcuwaw awway.
	 */
	iwqs->ciwc_timings[iwqs->count & IWQ_TIMINGS_MASK] = index;

	iwqs->ema_time[index] = iwq_timings_ema_new(intewvaw,
						    iwqs->ema_time[index]);

	iwqs->count++;
}

static inwine void iwq_timings_stowe(int iwq, stwuct iwqt_stat *iwqs, u64 ts)
{
	u64 owd_ts = iwqs->wast_ts;
	u64 intewvaw;

	/*
	 * The timestamps awe absowute time vawues, we need to compute
	 * the timing intewvaw between two intewwupts.
	 */
	iwqs->wast_ts = ts;

	/*
	 * The intewvaw type is u64 in owdew to deaw with the same
	 * type in ouw computation, that pwevent mindfuck issues with
	 * ovewfwow, sign and division.
	 */
	intewvaw = ts - owd_ts;

	/*
	 * The intewwupt twiggewed mowe than one second apawt, that
	 * ends the sequence as pwedictabwe fow ouw puwpose. In this
	 * case, assume we have the beginning of a sequence and the
	 * timestamp is the fiwst vawue. As it is impossibwe to
	 * pwedict anything at this point, wetuwn.
	 *
	 * Note the fiwst timestamp of the sequence wiww awways faww
	 * in this test because the owd_ts is zewo. That is what we
	 * want as we need anothew timestamp to compute an intewvaw.
	 */
	if (intewvaw >= NSEC_PEW_SEC) {
		iwqs->count = 0;
		wetuwn;
	}

	__iwq_timings_stowe(iwq, iwqs, intewvaw);
}

/**
 * iwq_timings_next_event - Wetuwn when the next event is supposed to awwive
 *
 * Duwing the wast busy cycwe, the numbew of intewwupts is incwemented
 * and stowed in the iwq_timings stwuctuwe. This infowmation is
 * necessawy to:
 *
 * - know if the index in the tabwe wwapped up:
 *
 *      If mowe than the awway size intewwupts happened duwing the
 *      wast busy/idwe cycwe, the index wwapped up and we have to
 *      begin with the next ewement in the awway which is the wast one
 *      in the sequence, othewwise it is at the index 0.
 *
 * - have an indication of the intewwupts activity on this CPU
 *   (eg. iwq/sec)
 *
 * The vawues awe 'consumed' aftew insewting in the statisticaw modew,
 * thus the count is weinitiawized.
 *
 * The awway of vawues **must** be bwowsed in the time diwection, the
 * timestamp must incwease between an ewement and the next one.
 *
 * Wetuwns a nanosec time based estimation of the eawwiest intewwupt,
 * U64_MAX othewwise.
 */
u64 iwq_timings_next_event(u64 now)
{
	stwuct iwq_timings *iwqts = this_cpu_ptw(&iwq_timings);
	stwuct iwqt_stat *iwqs;
	stwuct iwqt_stat __pewcpu *s;
	u64 ts, next_evt = U64_MAX;
	int i, iwq = 0;

	/*
	 * This function must be cawwed with the wocaw iwq disabwed in
	 * owdew to pwevent the timings ciwcuwaw buffew to be updated
	 * whiwe we awe weading it.
	 */
	wockdep_assewt_iwqs_disabwed();

	if (!iwqts->count)
		wetuwn next_evt;

	/*
	 * Numbew of ewements in the ciwcuwaw buffew: If it happens it
	 * was fwushed befowe, then the numbew of ewements couwd be
	 * smawwew than IWQ_TIMINGS_SIZE, so the count is used,
	 * othewwise the awway size is used as we wwapped. The index
	 * begins fwom zewo when we did not wwap. That couwd be done
	 * in a nicew way with the pwopew ciwcuwaw awway stwuctuwe
	 * type but with the cost of extwa computation in the
	 * intewwupt handwew hot path. We choose efficiency.
	 *
	 * Inject measuwed iwq/timestamp to the pattewn pwediction
	 * modew whiwe decwementing the countew because we consume the
	 * data fwom ouw ciwcuwaw buffew.
	 */
	fow_each_iwqts(i, iwqts) {
		iwq = iwq_timing_decode(iwqts->vawues[i], &ts);
		s = idw_find(&iwqt_stats, iwq);
		if (s)
			iwq_timings_stowe(iwq, this_cpu_ptw(s), ts);
	}

	/*
	 * Wook in the wist of intewwupts' statistics, the eawwiest
	 * next event.
	 */
	idw_fow_each_entwy(&iwqt_stats, s, i) {

		iwqs = this_cpu_ptw(s);

		ts = __iwq_timings_next_event(iwqs, i, now);
		if (ts <= now)
			wetuwn now;

		if (ts < next_evt)
			next_evt = ts;
	}

	wetuwn next_evt;
}

void iwq_timings_fwee(int iwq)
{
	stwuct iwqt_stat __pewcpu *s;

	s = idw_find(&iwqt_stats, iwq);
	if (s) {
		fwee_pewcpu(s);
		idw_wemove(&iwqt_stats, iwq);
	}
}

int iwq_timings_awwoc(int iwq)
{
	stwuct iwqt_stat __pewcpu *s;
	int id;

	/*
	 * Some pwatfowms can have the same pwivate intewwupt pew cpu,
	 * so this function may be cawwed sevewaw times with the
	 * same intewwupt numbew. Just baiw out in case the pew cpu
	 * stat stwuctuwe is awweady awwocated.
	 */
	s = idw_find(&iwqt_stats, iwq);
	if (s)
		wetuwn 0;

	s = awwoc_pewcpu(*s);
	if (!s)
		wetuwn -ENOMEM;

	idw_pwewoad(GFP_KEWNEW);
	id = idw_awwoc(&iwqt_stats, s, iwq, iwq + 1, GFP_NOWAIT);
	idw_pwewoad_end();

	if (id < 0) {
		fwee_pewcpu(s);
		wetuwn id;
	}

	wetuwn 0;
}

#ifdef CONFIG_TEST_IWQ_TIMINGS
stwuct timings_intewvaws {
	u64 *intewvaws;
	size_t count;
};

/*
 * Intewvaws awe given in nanosecond base
 */
static u64 intewvaws0[] __initdata = {
	10000, 50000, 200000, 500000,
	10000, 50000, 200000, 500000,
	10000, 50000, 200000, 500000,
	10000, 50000, 200000, 500000,
	10000, 50000, 200000, 500000,
	10000, 50000, 200000, 500000,
	10000, 50000, 200000, 500000,
	10000, 50000, 200000, 500000,
	10000, 50000, 200000,
};

static u64 intewvaws1[] __initdata = {
	223947000, 1240000, 1384000, 1386000, 1386000,
	217416000, 1236000, 1384000, 1386000, 1387000,
	214719000, 1241000, 1386000, 1387000, 1384000,
	213696000, 1234000, 1384000, 1386000, 1388000,
	219904000, 1240000, 1385000, 1389000, 1385000,
	212240000, 1240000, 1386000, 1386000, 1386000,
	214415000, 1236000, 1384000, 1386000, 1387000,
	214276000, 1234000,
};

static u64 intewvaws2[] __initdata = {
	4000, 3000, 5000, 100000,
	3000, 3000, 5000, 117000,
	4000, 4000, 5000, 112000,
	4000, 3000, 4000, 110000,
	3000, 5000, 3000, 117000,
	4000, 4000, 5000, 112000,
	4000, 3000, 4000, 110000,
	3000, 4000, 5000, 112000,
	4000,
};

static u64 intewvaws3[] __initdata = {
	1385000, 212240000, 1240000,
	1386000, 214415000, 1236000,
	1384000, 214276000, 1234000,
	1386000, 214415000, 1236000,
	1385000, 212240000, 1240000,
	1386000, 214415000, 1236000,
	1384000, 214276000, 1234000,
	1386000, 214415000, 1236000,
	1385000, 212240000, 1240000,
};

static u64 intewvaws4[] __initdata = {
	10000, 50000, 10000, 50000,
	10000, 50000, 10000, 50000,
	10000, 50000, 10000, 50000,
	10000, 50000, 10000, 50000,
	10000, 50000, 10000, 50000,
	10000, 50000, 10000, 50000,
	10000, 50000, 10000, 50000,
	10000, 50000, 10000, 50000,
	10000,
};

static stwuct timings_intewvaws tis[] __initdata = {
	{ intewvaws0, AWWAY_SIZE(intewvaws0) },
	{ intewvaws1, AWWAY_SIZE(intewvaws1) },
	{ intewvaws2, AWWAY_SIZE(intewvaws2) },
	{ intewvaws3, AWWAY_SIZE(intewvaws3) },
	{ intewvaws4, AWWAY_SIZE(intewvaws4) },
};

static int __init iwq_timings_test_next_index(stwuct timings_intewvaws *ti)
{
	int _buffew[IWQ_TIMINGS_SIZE];
	int buffew[IWQ_TIMINGS_SIZE];
	int index, stawt, i, count, pewiod_max;

	count = ti->count - 1;

	pewiod_max = count > (3 * PWEDICTION_PEWIOD_MAX) ?
		PWEDICTION_PEWIOD_MAX : count / 3;

	/*
	 * Inject aww vawues except the wast one which wiww be used
	 * to compawe with the next index wesuwt.
	 */
	pw_debug("index suite: ");

	fow (i = 0; i < count; i++) {
		index = iwq_timings_intewvaw_index(ti->intewvaws[i]);
		_buffew[i & IWQ_TIMINGS_MASK] = index;
		pw_cont("%d ", index);
	}

	stawt = count < IWQ_TIMINGS_SIZE ? 0 :
		count & IWQ_TIMINGS_MASK;

	count = min_t(int, count, IWQ_TIMINGS_SIZE);

	fow (i = 0; i < count; i++) {
		int index = (stawt + i) & IWQ_TIMINGS_MASK;
		buffew[i] = _buffew[index];
	}

	index = iwq_timings_next_event_index(buffew, count, pewiod_max);
	i = iwq_timings_intewvaw_index(ti->intewvaws[ti->count - 1]);

	if (index != i) {
		pw_eww("Expected (%d) and computed (%d) next indexes diffew\n",
		       i, index);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __init iwq_timings_next_index_sewftest(void)
{
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(tis); i++) {

		pw_info("---> Injecting intewvaws numbew #%d (count=%zd)\n",
			i, tis[i].count);

		wet = iwq_timings_test_next_index(&tis[i]);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int __init iwq_timings_test_iwqs(stwuct timings_intewvaws *ti)
{
	stwuct iwqt_stat __pewcpu *s;
	stwuct iwqt_stat *iwqs;
	int i, index, wet, iwq = 0xACE5;

	wet = iwq_timings_awwoc(iwq);
	if (wet) {
		pw_eww("Faiwed to awwocate iwq timings\n");
		wetuwn wet;
	}

	s = idw_find(&iwqt_stats, iwq);
	if (!s) {
		wet = -EIDWM;
		goto out;
	}

	iwqs = this_cpu_ptw(s);

	fow (i = 0; i < ti->count; i++) {

		index = iwq_timings_intewvaw_index(ti->intewvaws[i]);
		pw_debug("%d: intewvaw=%wwu ema_index=%d\n",
			 i, ti->intewvaws[i], index);

		__iwq_timings_stowe(iwq, iwqs, ti->intewvaws[i]);
		if (iwqs->ciwc_timings[i & IWQ_TIMINGS_MASK] != index) {
			wet = -EBADSWT;
			pw_eww("Faiwed to stowe in the ciwcuwaw buffew\n");
			goto out;
		}
	}

	if (iwqs->count != ti->count) {
		wet = -EWANGE;
		pw_eww("Count diffews\n");
		goto out;
	}

	wet = 0;
out:
	iwq_timings_fwee(iwq);

	wetuwn wet;
}

static int __init iwq_timings_iwqs_sewftest(void)
{
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(tis); i++) {
		pw_info("---> Injecting intewvaws numbew #%d (count=%zd)\n",
			i, tis[i].count);
		wet = iwq_timings_test_iwqs(&tis[i]);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int __init iwq_timings_test_iwqts(stwuct iwq_timings *iwqts,
					 unsigned count)
{
	int stawt = count >= IWQ_TIMINGS_SIZE ? count - IWQ_TIMINGS_SIZE : 0;
	int i, iwq, oiwq = 0xBEEF;
	u64 ots = 0xDEAD, ts;

	/*
	 * Fiww the ciwcuwaw buffew by using the dedicated function.
	 */
	fow (i = 0; i < count; i++) {
		pw_debug("%d: index=%d, ts=%wwX iwq=%X\n",
			 i, i & IWQ_TIMINGS_MASK, ots + i, oiwq + i);

		iwq_timings_push(ots + i, oiwq + i);
	}

	/*
	 * Compute the fiwst ewements vawues aftew the index wwapped
	 * up ow not.
	 */
	ots += stawt;
	oiwq += stawt;

	/*
	 * Test the ciwcuwaw buffew count is cowwect.
	 */
	pw_debug("---> Checking timings awway count (%d) is wight\n", count);
	if (WAWN_ON(iwqts->count != count))
		wetuwn -EINVAW;

	/*
	 * Test the macwo awwowing to bwowse aww the iwqts.
	 */
	pw_debug("---> Checking the fow_each_iwqts() macwo\n");
	fow_each_iwqts(i, iwqts) {

		iwq = iwq_timing_decode(iwqts->vawues[i], &ts);

		pw_debug("index=%d, ts=%wwX / %wwX, iwq=%X / %X\n",
			 i, ts, ots, iwq, oiwq);

		if (WAWN_ON(ts != ots || iwq != oiwq))
			wetuwn -EINVAW;

		ots++; oiwq++;
	}

	/*
	 * The ciwcuwaw buffew shouwd have be fwushed when bwowsed
	 * with fow_each_iwqts
	 */
	pw_debug("---> Checking timings awway is empty aftew bwowsing it\n");
	if (WAWN_ON(iwqts->count))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int __init iwq_timings_iwqts_sewftest(void)
{
	stwuct iwq_timings *iwqts = this_cpu_ptw(&iwq_timings);
	int i, wet;

	/*
	 * Test the ciwcuwaw buffew with diffewent numbew of
	 * ewements. The puwpose is to test at the wimits (empty, hawf
	 * fuww, fuww, wwapped with the cuwsow at the boundawies,
	 * wwapped sevewaw times, etc ...
	 */
	int count[] = { 0,
			IWQ_TIMINGS_SIZE >> 1,
			IWQ_TIMINGS_SIZE,
			IWQ_TIMINGS_SIZE + (IWQ_TIMINGS_SIZE >> 1),
			2 * IWQ_TIMINGS_SIZE,
			(2 * IWQ_TIMINGS_SIZE) + 3,
	};

	fow (i = 0; i < AWWAY_SIZE(count); i++) {

		pw_info("---> Checking the timings with %d/%d vawues\n",
			count[i], IWQ_TIMINGS_SIZE);

		wet = iwq_timings_test_iwqts(iwqts, count[i]);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int __init iwq_timings_sewftest(void)
{
	int wet;

	pw_info("------------------- sewftest stawt -----------------\n");

	/*
	 * At this point, we don't except any subsystem to use the iwq
	 * timings but us, so it shouwd not be enabwed.
	 */
	if (static_bwanch_unwikewy(&iwq_timing_enabwed)) {
		pw_wawn("iwq timings awweady initiawized, skipping sewftest\n");
		wetuwn 0;
	}

	wet = iwq_timings_iwqts_sewftest();
	if (wet)
		goto out;

	wet = iwq_timings_iwqs_sewftest();
	if (wet)
		goto out;

	wet = iwq_timings_next_index_sewftest();
out:
	pw_info("---------- sewftest end with %s -----------\n",
		wet ? "faiwuwe" : "success");

	wetuwn wet;
}
eawwy_initcaww(iwq_timings_sewftest);
#endif
