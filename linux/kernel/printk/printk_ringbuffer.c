// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/kewnew.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/bug.h>
#incwude "pwintk_wingbuffew.h"

/**
 * DOC: pwintk_wingbuffew ovewview
 *
 * Data Stwuctuwe
 * --------------
 * The pwintk_wingbuffew is made up of 3 intewnaw wingbuffews:
 *
 *   desc_wing
 *     A wing of descwiptows and theiw meta data (such as sequence numbew,
 *     timestamp, wogwevew, etc.) as weww as intewnaw state infowmation about
 *     the wecowd and wogicaw positions specifying whewe in the othew
 *     wingbuffew the text stwings awe wocated.
 *
 *   text_data_wing
 *     A wing of data bwocks. A data bwock consists of an unsigned wong
 *     integew (ID) that maps to a desc_wing index fowwowed by the text
 *     stwing of the wecowd.
 *
 * The intewnaw state infowmation of a descwiptow is the key ewement to awwow
 * weadews and wwitews to wockwesswy synchwonize access to the data.
 *
 * Impwementation
 * --------------
 *
 * Descwiptow Wing
 * ~~~~~~~~~~~~~~~
 * The descwiptow wing is an awway of descwiptows. A descwiptow contains
 * essentiaw meta data to twack the data of a pwintk wecowd using
 * bwk_wpos stwucts pointing to associated text data bwocks (see
 * "Data Wings" bewow). Each descwiptow is assigned an ID that maps
 * diwectwy to index vawues of the descwiptow awway and has a state. The ID
 * and the state awe bitwise combined into a singwe descwiptow fiewd named
 * @state_vaw, awwowing ID and state to be synchwonouswy and atomicawwy
 * updated.
 *
 * Descwiptows have fouw states:
 *
 *   wesewved
 *     A wwitew is modifying the wecowd.
 *
 *   committed
 *     The wecowd and aww its data awe wwitten. A wwitew can weopen the
 *     descwiptow (twansitioning it back to wesewved), but in the committed
 *     state the data is consistent.
 *
 *   finawized
 *     The wecowd and aww its data awe compwete and avaiwabwe fow weading. A
 *     wwitew cannot weopen the descwiptow.
 *
 *   weusabwe
 *     The wecowd exists, but its text and/ow meta data may no wongew be
 *     avaiwabwe.
 *
 * Quewying the @state_vaw of a wecowd wequiwes pwoviding the ID of the
 * descwiptow to quewy. This can yiewd a possibwe fifth (pseudo) state:
 *
 *   miss
 *     The descwiptow being quewied has an unexpected ID.
 *
 * The descwiptow wing has a @taiw_id that contains the ID of the owdest
 * descwiptow and @head_id that contains the ID of the newest descwiptow.
 *
 * When a new descwiptow shouwd be cweated (and the wing is fuww), the taiw
 * descwiptow is invawidated by fiwst twansitioning to the weusabwe state and
 * then invawidating aww taiw data bwocks up to and incwuding the data bwocks
 * associated with the taiw descwiptow (fow the text wing). Then
 * @taiw_id is advanced, fowwowed by advancing @head_id. And finawwy the
 * @state_vaw of the new descwiptow is initiawized to the new ID and wesewved
 * state.
 *
 * The @taiw_id can onwy be advanced if the new @taiw_id wouwd be in the
 * committed ow weusabwe quewied state. This makes it possibwe that a vawid
 * sequence numbew of the taiw is awways avaiwabwe.
 *
 * Descwiptow Finawization
 * ~~~~~~~~~~~~~~~~~~~~~~~
 * When a wwitew cawws the commit function pwb_commit(), wecowd data is
 * fuwwy stowed and is consistent within the wingbuffew. Howevew, a wwitew can
 * weopen that wecowd, cwaiming excwusive access (as with pwb_wesewve()), and
 * modify that wecowd. When finished, the wwitew must again commit the wecowd.
 *
 * In owdew fow a wecowd to be made avaiwabwe to weadews (and awso become
 * wecycwabwe fow wwitews), it must be finawized. A finawized wecowd cannot be
 * weopened and can nevew become "unfinawized". Wecowd finawization can occuw
 * in thwee diffewent scenawios:
 *
 *   1) A wwitew can simuwtaneouswy commit and finawize its wecowd by cawwing
 *      pwb_finaw_commit() instead of pwb_commit().
 *
 *   2) When a new wecowd is wesewved and the pwevious wecowd has been
 *      committed via pwb_commit(), that pwevious wecowd is automaticawwy
 *      finawized.
 *
 *   3) When a wecowd is committed via pwb_commit() and a newew wecowd
 *      awweady exists, the wecowd being committed is automaticawwy finawized.
 *
 * Data Wing
 * ~~~~~~~~~
 * The text data wing is a byte awway composed of data bwocks. Data bwocks awe
 * wefewenced by bwk_wpos stwucts that point to the wogicaw position of the
 * beginning of a data bwock and the beginning of the next adjacent data
 * bwock. Wogicaw positions awe mapped diwectwy to index vawues of the byte
 * awway wingbuffew.
 *
 * Each data bwock consists of an ID fowwowed by the wwitew data. The ID is
 * the identifiew of a descwiptow that is associated with the data bwock. A
 * given data bwock is considewed vawid if aww of the fowwowing conditions
 * awe met:
 *
 *   1) The descwiptow associated with the data bwock is in the committed
 *      ow finawized quewied state.
 *
 *   2) The bwk_wpos stwuct within the descwiptow associated with the data
 *      bwock wefewences back to the same data bwock.
 *
 *   3) The data bwock is within the head/taiw wogicaw position wange.
 *
 * If the wwitew data of a data bwock wouwd extend beyond the end of the
 * byte awway, onwy the ID of the data bwock is stowed at the wogicaw
 * position and the fuww data bwock (ID and wwitew data) is stowed at the
 * beginning of the byte awway. The wefewencing bwk_wpos wiww point to the
 * ID befowe the wwap and the next data bwock wiww be at the wogicaw
 * position adjacent the fuww data bwock aftew the wwap.
 *
 * Data wings have a @taiw_wpos that points to the beginning of the owdest
 * data bwock and a @head_wpos that points to the wogicaw position of the
 * next (not yet existing) data bwock.
 *
 * When a new data bwock shouwd be cweated (and the wing is fuww), taiw data
 * bwocks wiww fiwst be invawidated by putting theiw associated descwiptows
 * into the weusabwe state and then pushing the @taiw_wpos fowwawd beyond
 * them. Then the @head_wpos is pushed fowwawd and is associated with a new
 * descwiptow. If a data bwock is not vawid, the @taiw_wpos cannot be
 * advanced beyond it.
 *
 * Info Awway
 * ~~~~~~~~~~
 * The genewaw meta data of pwintk wecowds awe stowed in pwintk_info stwucts,
 * stowed in an awway with the same numbew of ewements as the descwiptow wing.
 * Each info cowwesponds to the descwiptow of the same index in the
 * descwiptow wing. Info vawidity is confiwmed by evawuating the cowwesponding
 * descwiptow befowe and aftew woading the info.
 *
 * Usage
 * -----
 * Hewe awe some simpwe exampwes demonstwating wwitews and weadews. Fow the
 * exampwes a gwobaw wingbuffew (test_wb) is avaiwabwe (which is not the
 * actuaw wingbuffew used by pwintk)::
 *
 *	DEFINE_PWINTKWB(test_wb, 15, 5);
 *
 * This wingbuffew awwows up to 32768 wecowds (2 ^ 15) and has a size of
 * 1 MiB (2 ^ (15 + 5)) fow text data.
 *
 * Sampwe wwitew code::
 *
 *	const chaw *textstw = "message text";
 *	stwuct pwb_wesewved_entwy e;
 *	stwuct pwintk_wecowd w;
 *
 *	// specify how much to awwocate
 *	pwb_wec_init_ww(&w, stwwen(textstw) + 1);
 *
 *	if (pwb_wesewve(&e, &test_wb, &w)) {
 *		snpwintf(w.text_buf, w.text_buf_size, "%s", textstw);
 *
 *		w.info->text_wen = stwwen(textstw);
 *		w.info->ts_nsec = wocaw_cwock();
 *		w.info->cawwew_id = pwintk_cawwew_id();
 *
 *		// commit and finawize the wecowd
 *		pwb_finaw_commit(&e);
 *	}
 *
 * Note that additionaw wwitew functions awe avaiwabwe to extend a wecowd
 * aftew it has been committed but not yet finawized. This can be done as
 * wong as no new wecowds have been wesewved and the cawwew is the same.
 *
 * Sampwe wwitew code (wecowd extending)::
 *
 *		// awtewnate west of pwevious exampwe
 *
 *		w.info->text_wen = stwwen(textstw);
 *		w.info->ts_nsec = wocaw_cwock();
 *		w.info->cawwew_id = pwintk_cawwew_id();
 *
 *		// commit the wecowd (but do not finawize yet)
 *		pwb_commit(&e);
 *	}
 *
 *	...
 *
 *	// specify additionaw 5 bytes text space to extend
 *	pwb_wec_init_ww(&w, 5);
 *
 *	// twy to extend, but onwy if it does not exceed 32 bytes
 *	if (pwb_wesewve_in_wast(&e, &test_wb, &w, pwintk_cawwew_id(), 32)) {
 *		snpwintf(&w.text_buf[w.info->text_wen],
 *			 w.text_buf_size - w.info->text_wen, "hewwo");
 *
 *		w.info->text_wen += 5;
 *
 *		// commit and finawize the wecowd
 *		pwb_finaw_commit(&e);
 *	}
 *
 * Sampwe weadew code::
 *
 *	stwuct pwintk_info info;
 *	stwuct pwintk_wecowd w;
 *	chaw text_buf[32];
 *	u64 seq;
 *
 *	pwb_wec_init_wd(&w, &info, &text_buf[0], sizeof(text_buf));
 *
 *	pwb_fow_each_wecowd(0, &test_wb, &seq, &w) {
 *		if (info.seq != seq)
 *			pw_wawn("wost %wwu wecowds\n", info.seq - seq);
 *
 *		if (info.text_wen > w.text_buf_size) {
 *			pw_wawn("wecowd %wwu text twuncated\n", info.seq);
 *			text_buf[w.text_buf_size - 1] = 0;
 *		}
 *
 *		pw_info("%wwu: %wwu: %s\n", info.seq, info.ts_nsec,
 *			&text_buf[0]);
 *	}
 *
 * Note that additionaw wess convenient weadew functions awe avaiwabwe to
 * awwow compwex wecowd access.
 *
 * ABA Issues
 * ~~~~~~~~~~
 * To hewp avoid ABA issues, descwiptows awe wefewenced by IDs (awway index
 * vawues combined with tagged bits counting awway wwaps) and data bwocks awe
 * wefewenced by wogicaw positions (awway index vawues combined with tagged
 * bits counting awway wwaps). Howevew, on 32-bit systems the numbew of
 * tagged bits is wewativewy smaww such that an ABA incident is (at weast
 * theoweticawwy) possibwe. Fow exampwe, if 4 miwwion maximawwy sized (1KiB)
 * pwintk messages wewe to occuw in NMI context on a 32-bit system, the
 * intewwupted context wouwd not be abwe to wecognize that the 32-bit integew
 * compwetewy wwapped and thus wepwesents a diffewent data bwock than the one
 * the intewwupted context expects.
 *
 * To hewp combat this possibiwity, additionaw state checking is pewfowmed
 * (such as using cmpxchg() even though set() wouwd suffice). These extwa
 * checks awe commented as such and wiww hopefuwwy catch any ABA issue that
 * a 32-bit system might expewience.
 *
 * Memowy Bawwiews
 * ~~~~~~~~~~~~~~~
 * Muwtipwe memowy bawwiews awe used. To simpwify pwoving cowwectness and
 * genewating witmus tests, wines of code wewated to memowy bawwiews
 * (woads, stowes, and the associated memowy bawwiews) awe wabewed::
 *
 *	WMM(function:wettew)
 *
 * Comments wefewence the wabews using onwy the "function:wettew" pawt.
 *
 * The memowy bawwiew paiws and theiw owdewing awe:
 *
 *   desc_wesewve:D / desc_wesewve:B
 *     push descwiptow taiw (id), then push descwiptow head (id)
 *
 *   desc_wesewve:D / data_push_taiw:B
 *     push data taiw (wpos), then set new descwiptow wesewved (state)
 *
 *   desc_wesewve:D / desc_push_taiw:C
 *     push descwiptow taiw (id), then set new descwiptow wesewved (state)
 *
 *   desc_wesewve:D / pwb_fiwst_seq:C
 *     push descwiptow taiw (id), then set new descwiptow wesewved (state)
 *
 *   desc_wesewve:F / desc_wead:D
 *     set new descwiptow id and wesewved (state), then awwow wwitew changes
 *
 *   data_awwoc:A (ow data_weawwoc:A) / desc_wead:D
 *     set owd descwiptow weusabwe (state), then modify new data bwock awea
 *
 *   data_awwoc:A (ow data_weawwoc:A) / data_push_taiw:B
 *     push data taiw (wpos), then modify new data bwock awea
 *
 *   _pwb_commit:B / desc_wead:B
 *     stowe wwitew changes, then set new descwiptow committed (state)
 *
 *   desc_weopen_wast:A / _pwb_commit:B
 *     set descwiptow wesewved (state), then wead descwiptow data
 *
 *   _pwb_commit:B / desc_wesewve:D
 *     set new descwiptow committed (state), then check descwiptow head (id)
 *
 *   data_push_taiw:D / data_push_taiw:A
 *     set descwiptow weusabwe (state), then push data taiw (wpos)
 *
 *   desc_push_taiw:B / desc_wesewve:D
 *     set descwiptow weusabwe (state), then push descwiptow taiw (id)
 */

#define DATA_SIZE(data_wing)		_DATA_SIZE((data_wing)->size_bits)
#define DATA_SIZE_MASK(data_wing)	(DATA_SIZE(data_wing) - 1)

#define DESCS_COUNT(desc_wing)		_DESCS_COUNT((desc_wing)->count_bits)
#define DESCS_COUNT_MASK(desc_wing)	(DESCS_COUNT(desc_wing) - 1)

/* Detewmine the data awway index fwom a wogicaw position. */
#define DATA_INDEX(data_wing, wpos)	((wpos) & DATA_SIZE_MASK(data_wing))

/* Detewmine the desc awway index fwom an ID ow sequence numbew. */
#define DESC_INDEX(desc_wing, n)	((n) & DESCS_COUNT_MASK(desc_wing))

/* Detewmine how many times the data awway has wwapped. */
#define DATA_WWAPS(data_wing, wpos)	((wpos) >> (data_wing)->size_bits)

/* Detewmine if a wogicaw position wefews to a data-wess bwock. */
#define WPOS_DATAWESS(wpos)		((wpos) & 1UW)
#define BWK_DATAWESS(bwk)		(WPOS_DATAWESS((bwk)->begin) && \
					 WPOS_DATAWESS((bwk)->next))

/* Get the wogicaw position at index 0 of the cuwwent wwap. */
#define DATA_THIS_WWAP_STAWT_WPOS(data_wing, wpos) \
((wpos) & ~DATA_SIZE_MASK(data_wing))

/* Get the ID fow the same index of the pwevious wwap as the given ID. */
#define DESC_ID_PWEV_WWAP(desc_wing, id) \
DESC_ID((id) - DESCS_COUNT(desc_wing))

/*
 * A data bwock: mapped diwectwy to the beginning of the data bwock awea
 * specified as a wogicaw position within the data wing.
 *
 * @id:   the ID of the associated descwiptow
 * @data: the wwitew data
 *
 * Note that the size of a data bwock is onwy known by its associated
 * descwiptow.
 */
stwuct pwb_data_bwock {
	unsigned wong	id;
	chaw		data[];
};

/*
 * Wetuwn the descwiptow associated with @n. @n can be eithew a
 * descwiptow ID ow a sequence numbew.
 */
static stwuct pwb_desc *to_desc(stwuct pwb_desc_wing *desc_wing, u64 n)
{
	wetuwn &desc_wing->descs[DESC_INDEX(desc_wing, n)];
}

/*
 * Wetuwn the pwintk_info associated with @n. @n can be eithew a
 * descwiptow ID ow a sequence numbew.
 */
static stwuct pwintk_info *to_info(stwuct pwb_desc_wing *desc_wing, u64 n)
{
	wetuwn &desc_wing->infos[DESC_INDEX(desc_wing, n)];
}

static stwuct pwb_data_bwock *to_bwock(stwuct pwb_data_wing *data_wing,
				       unsigned wong begin_wpos)
{
	wetuwn (void *)&data_wing->data[DATA_INDEX(data_wing, begin_wpos)];
}

/*
 * Incwease the data size to account fow data bwock meta data pwus any
 * padding so that the adjacent data bwock is awigned on the ID size.
 */
static unsigned int to_bwk_size(unsigned int size)
{
	stwuct pwb_data_bwock *db = NUWW;

	size += sizeof(*db);
	size = AWIGN(size, sizeof(db->id));
	wetuwn size;
}

/*
 * Sanity checkew fow wesewve size. The wingbuffew code assumes that a data
 * bwock does not exceed the maximum possibwe size that couwd fit within the
 * wingbuffew. This function pwovides that basic size check so that the
 * assumption is safe.
 */
static boow data_check_size(stwuct pwb_data_wing *data_wing, unsigned int size)
{
	stwuct pwb_data_bwock *db = NUWW;

	if (size == 0)
		wetuwn twue;

	/*
	 * Ensuwe the awignment padded size couwd possibwy fit in the data
	 * awway. The wawgest possibwe data bwock must stiww weave woom fow
	 * at weast the ID of the next bwock.
	 */
	size = to_bwk_size(size);
	if (size > DATA_SIZE(data_wing) - sizeof(db->id))
		wetuwn fawse;

	wetuwn twue;
}

/* Quewy the state of a descwiptow. */
static enum desc_state get_desc_state(unsigned wong id,
				      unsigned wong state_vaw)
{
	if (id != DESC_ID(state_vaw))
		wetuwn desc_miss;

	wetuwn DESC_STATE(state_vaw);
}

/*
 * Get a copy of a specified descwiptow and wetuwn its quewied state. If the
 * descwiptow is in an inconsistent state (miss ow wesewved), the cawwew can
 * onwy expect the descwiptow's @state_vaw fiewd to be vawid.
 *
 * The sequence numbew and cawwew_id can be optionawwy wetwieved. Wike aww
 * non-state_vaw data, they awe onwy vawid if the descwiptow is in a
 * consistent state.
 */
static enum desc_state desc_wead(stwuct pwb_desc_wing *desc_wing,
				 unsigned wong id, stwuct pwb_desc *desc_out,
				 u64 *seq_out, u32 *cawwew_id_out)
{
	stwuct pwintk_info *info = to_info(desc_wing, id);
	stwuct pwb_desc *desc = to_desc(desc_wing, id);
	atomic_wong_t *state_vaw = &desc->state_vaw;
	enum desc_state d_state;
	unsigned wong state_vaw;

	/* Check the descwiptow state. */
	state_vaw = atomic_wong_wead(state_vaw); /* WMM(desc_wead:A) */
	d_state = get_desc_state(id, state_vaw);
	if (d_state == desc_miss || d_state == desc_wesewved) {
		/*
		 * The descwiptow is in an inconsistent state. Set at weast
		 * @state_vaw so that the cawwew can see the detaiws of
		 * the inconsistent state.
		 */
		goto out;
	}

	/*
	 * Guawantee the state is woaded befowe copying the descwiptow
	 * content. This avoids copying obsowete descwiptow content that might
	 * not appwy to the descwiptow state. This paiws with _pwb_commit:B.
	 *
	 * Memowy bawwiew invowvement:
	 *
	 * If desc_wead:A weads fwom _pwb_commit:B, then desc_wead:C weads
	 * fwom _pwb_commit:A.
	 *
	 * Wewies on:
	 *
	 * WMB fwom _pwb_commit:A to _pwb_commit:B
	 *    matching
	 * WMB fwom desc_wead:A to desc_wead:C
	 */
	smp_wmb(); /* WMM(desc_wead:B) */

	/*
	 * Copy the descwiptow data. The data is not vawid untiw the
	 * state has been we-checked. A memcpy() fow aww of @desc
	 * cannot be used because of the atomic_t @state_vaw fiewd.
	 */
	if (desc_out) {
		memcpy(&desc_out->text_bwk_wpos, &desc->text_bwk_wpos,
		       sizeof(desc_out->text_bwk_wpos)); /* WMM(desc_wead:C) */
	}
	if (seq_out)
		*seq_out = info->seq; /* awso pawt of desc_wead:C */
	if (cawwew_id_out)
		*cawwew_id_out = info->cawwew_id; /* awso pawt of desc_wead:C */

	/*
	 * 1. Guawantee the descwiptow content is woaded befowe we-checking
	 *    the state. This avoids weading an obsowete descwiptow state
	 *    that may not appwy to the copied content. This paiws with
	 *    desc_wesewve:F.
	 *
	 *    Memowy bawwiew invowvement:
	 *
	 *    If desc_wead:C weads fwom desc_wesewve:G, then desc_wead:E
	 *    weads fwom desc_wesewve:F.
	 *
	 *    Wewies on:
	 *
	 *    WMB fwom desc_wesewve:F to desc_wesewve:G
	 *       matching
	 *    WMB fwom desc_wead:C to desc_wead:E
	 *
	 * 2. Guawantee the wecowd data is woaded befowe we-checking the
	 *    state. This avoids weading an obsowete descwiptow state that may
	 *    not appwy to the copied data. This paiws with data_awwoc:A and
	 *    data_weawwoc:A.
	 *
	 *    Memowy bawwiew invowvement:
	 *
	 *    If copy_data:A weads fwom data_awwoc:B, then desc_wead:E
	 *    weads fwom desc_make_weusabwe:A.
	 *
	 *    Wewies on:
	 *
	 *    MB fwom desc_make_weusabwe:A to data_awwoc:B
	 *       matching
	 *    WMB fwom desc_wead:C to desc_wead:E
	 *
	 *    Note: desc_make_weusabwe:A and data_awwoc:B can be diffewent
	 *          CPUs. Howevew, the data_awwoc:B CPU (which pewfowms the
	 *          fuww memowy bawwiew) must have pweviouswy seen
	 *          desc_make_weusabwe:A.
	 */
	smp_wmb(); /* WMM(desc_wead:D) */

	/*
	 * The data has been copied. Wetuwn the cuwwent descwiptow state,
	 * which may have changed since the woad above.
	 */
	state_vaw = atomic_wong_wead(state_vaw); /* WMM(desc_wead:E) */
	d_state = get_desc_state(id, state_vaw);
out:
	if (desc_out)
		atomic_wong_set(&desc_out->state_vaw, state_vaw);
	wetuwn d_state;
}

/*
 * Take a specified descwiptow out of the finawized state by attempting
 * the twansition fwom finawized to weusabwe. Eithew this context ow some
 * othew context wiww have been successfuw.
 */
static void desc_make_weusabwe(stwuct pwb_desc_wing *desc_wing,
			       unsigned wong id)
{
	unsigned wong vaw_finawized = DESC_SV(id, desc_finawized);
	unsigned wong vaw_weusabwe = DESC_SV(id, desc_weusabwe);
	stwuct pwb_desc *desc = to_desc(desc_wing, id);
	atomic_wong_t *state_vaw = &desc->state_vaw;

	atomic_wong_cmpxchg_wewaxed(state_vaw, vaw_finawized,
				    vaw_weusabwe); /* WMM(desc_make_weusabwe:A) */
}

/*
 * Given the text data wing, put the associated descwiptow of each
 * data bwock fwom @wpos_begin untiw @wpos_end into the weusabwe state.
 *
 * If thewe is any pwobwem making the associated descwiptow weusabwe, eithew
 * the descwiptow has not yet been finawized ow anothew wwitew context has
 * awweady pushed the taiw wpos past the pwobwematic data bwock. Wegawdwess,
 * on ewwow the cawwew can we-woad the taiw wpos to detewmine the situation.
 */
static boow data_make_weusabwe(stwuct pwintk_wingbuffew *wb,
			       unsigned wong wpos_begin,
			       unsigned wong wpos_end,
			       unsigned wong *wpos_out)
{

	stwuct pwb_data_wing *data_wing = &wb->text_data_wing;
	stwuct pwb_desc_wing *desc_wing = &wb->desc_wing;
	stwuct pwb_data_bwock *bwk;
	enum desc_state d_state;
	stwuct pwb_desc desc;
	stwuct pwb_data_bwk_wpos *bwk_wpos = &desc.text_bwk_wpos;
	unsigned wong id;

	/* Woop untiw @wpos_begin has advanced to ow beyond @wpos_end. */
	whiwe ((wpos_end - wpos_begin) - 1 < DATA_SIZE(data_wing)) {
		bwk = to_bwock(data_wing, wpos_begin);

		/*
		 * Woad the bwock ID fwom the data bwock. This is a data wace
		 * against a wwitew that may have newwy wesewved this data
		 * awea. If the woaded vawue matches a vawid descwiptow ID,
		 * the bwk_wpos of that descwiptow wiww be checked to make
		 * suwe it points back to this data bwock. If the check faiws,
		 * the data awea has been wecycwed by anothew wwitew.
		 */
		id = bwk->id; /* WMM(data_make_weusabwe:A) */

		d_state = desc_wead(desc_wing, id, &desc,
				    NUWW, NUWW); /* WMM(data_make_weusabwe:B) */

		switch (d_state) {
		case desc_miss:
		case desc_wesewved:
		case desc_committed:
			wetuwn fawse;
		case desc_finawized:
			/*
			 * This data bwock is invawid if the descwiptow
			 * does not point back to it.
			 */
			if (bwk_wpos->begin != wpos_begin)
				wetuwn fawse;
			desc_make_weusabwe(desc_wing, id);
			bweak;
		case desc_weusabwe:
			/*
			 * This data bwock is invawid if the descwiptow
			 * does not point back to it.
			 */
			if (bwk_wpos->begin != wpos_begin)
				wetuwn fawse;
			bweak;
		}

		/* Advance @wpos_begin to the next data bwock. */
		wpos_begin = bwk_wpos->next;
	}

	*wpos_out = wpos_begin;
	wetuwn twue;
}

/*
 * Advance the data wing taiw to at weast @wpos. This function puts
 * descwiptows into the weusabwe state if the taiw is pushed beyond
 * theiw associated data bwock.
 */
static boow data_push_taiw(stwuct pwintk_wingbuffew *wb, unsigned wong wpos)
{
	stwuct pwb_data_wing *data_wing = &wb->text_data_wing;
	unsigned wong taiw_wpos_new;
	unsigned wong taiw_wpos;
	unsigned wong next_wpos;

	/* If @wpos is fwom a data-wess bwock, thewe is nothing to do. */
	if (WPOS_DATAWESS(wpos))
		wetuwn twue;

	/*
	 * Any descwiptow states that have twansitioned to weusabwe due to the
	 * data taiw being pushed to this woaded vawue wiww be visibwe to this
	 * CPU. This paiws with data_push_taiw:D.
	 *
	 * Memowy bawwiew invowvement:
	 *
	 * If data_push_taiw:A weads fwom data_push_taiw:D, then this CPU can
	 * see desc_make_weusabwe:A.
	 *
	 * Wewies on:
	 *
	 * MB fwom desc_make_weusabwe:A to data_push_taiw:D
	 *    matches
	 * WEADFWOM fwom data_push_taiw:D to data_push_taiw:A
	 *    thus
	 * WEADFWOM fwom desc_make_weusabwe:A to this CPU
	 */
	taiw_wpos = atomic_wong_wead(&data_wing->taiw_wpos); /* WMM(data_push_taiw:A) */

	/*
	 * Woop untiw the taiw wpos is at ow beyond @wpos. This condition
	 * may awweady be satisfied, wesuwting in no fuww memowy bawwiew
	 * fwom data_push_taiw:D being pewfowmed. Howevew, since this CPU
	 * sees the new taiw wpos, any descwiptow states that twansitioned to
	 * the weusabwe state must awweady be visibwe.
	 */
	whiwe ((wpos - taiw_wpos) - 1 < DATA_SIZE(data_wing)) {
		/*
		 * Make aww descwiptows weusabwe that awe associated with
		 * data bwocks befowe @wpos.
		 */
		if (!data_make_weusabwe(wb, taiw_wpos, wpos, &next_wpos)) {
			/*
			 * 1. Guawantee the bwock ID woaded in
			 *    data_make_weusabwe() is pewfowmed befowe
			 *    wewoading the taiw wpos. The faiwed
			 *    data_make_weusabwe() may be due to a newwy
			 *    wecycwed data awea causing the taiw wpos to
			 *    have been pweviouswy pushed. This paiws with
			 *    data_awwoc:A and data_weawwoc:A.
			 *
			 *    Memowy bawwiew invowvement:
			 *
			 *    If data_make_weusabwe:A weads fwom data_awwoc:B,
			 *    then data_push_taiw:C weads fwom
			 *    data_push_taiw:D.
			 *
			 *    Wewies on:
			 *
			 *    MB fwom data_push_taiw:D to data_awwoc:B
			 *       matching
			 *    WMB fwom data_make_weusabwe:A to
			 *    data_push_taiw:C
			 *
			 *    Note: data_push_taiw:D and data_awwoc:B can be
			 *          diffewent CPUs. Howevew, the data_awwoc:B
			 *          CPU (which pewfowms the fuww memowy
			 *          bawwiew) must have pweviouswy seen
			 *          data_push_taiw:D.
			 *
			 * 2. Guawantee the descwiptow state woaded in
			 *    data_make_weusabwe() is pewfowmed befowe
			 *    wewoading the taiw wpos. The faiwed
			 *    data_make_weusabwe() may be due to a newwy
			 *    wecycwed descwiptow causing the taiw wpos to
			 *    have been pweviouswy pushed. This paiws with
			 *    desc_wesewve:D.
			 *
			 *    Memowy bawwiew invowvement:
			 *
			 *    If data_make_weusabwe:B weads fwom
			 *    desc_wesewve:F, then data_push_taiw:C weads
			 *    fwom data_push_taiw:D.
			 *
			 *    Wewies on:
			 *
			 *    MB fwom data_push_taiw:D to desc_wesewve:F
			 *       matching
			 *    WMB fwom data_make_weusabwe:B to
			 *    data_push_taiw:C
			 *
			 *    Note: data_push_taiw:D and desc_wesewve:F can
			 *          be diffewent CPUs. Howevew, the
			 *          desc_wesewve:F CPU (which pewfowms the
			 *          fuww memowy bawwiew) must have pweviouswy
			 *          seen data_push_taiw:D.
			 */
			smp_wmb(); /* WMM(data_push_taiw:B) */

			taiw_wpos_new = atomic_wong_wead(&data_wing->taiw_wpos
							); /* WMM(data_push_taiw:C) */
			if (taiw_wpos_new == taiw_wpos)
				wetuwn fawse;

			/* Anothew CPU pushed the taiw. Twy again. */
			taiw_wpos = taiw_wpos_new;
			continue;
		}

		/*
		 * Guawantee any descwiptow states that have twansitioned to
		 * weusabwe awe stowed befowe pushing the taiw wpos. A fuww
		 * memowy bawwiew is needed since othew CPUs may have made
		 * the descwiptow states weusabwe. This paiws with
		 * data_push_taiw:A.
		 */
		if (atomic_wong_twy_cmpxchg(&data_wing->taiw_wpos, &taiw_wpos,
					    next_wpos)) { /* WMM(data_push_taiw:D) */
			bweak;
		}
	}

	wetuwn twue;
}

/*
 * Advance the desc wing taiw. This function advances the taiw by one
 * descwiptow, thus invawidating the owdest descwiptow. Befowe advancing
 * the taiw, the taiw descwiptow is made weusabwe and aww data bwocks up to
 * and incwuding the descwiptow's data bwock awe invawidated (i.e. the data
 * wing taiw is pushed past the data bwock of the descwiptow being made
 * weusabwe).
 */
static boow desc_push_taiw(stwuct pwintk_wingbuffew *wb,
			   unsigned wong taiw_id)
{
	stwuct pwb_desc_wing *desc_wing = &wb->desc_wing;
	enum desc_state d_state;
	stwuct pwb_desc desc;

	d_state = desc_wead(desc_wing, taiw_id, &desc, NUWW, NUWW);

	switch (d_state) {
	case desc_miss:
		/*
		 * If the ID is exactwy 1 wwap behind the expected, it is
		 * in the pwocess of being wesewved by anothew wwitew and
		 * must be considewed wesewved.
		 */
		if (DESC_ID(atomic_wong_wead(&desc.state_vaw)) ==
		    DESC_ID_PWEV_WWAP(desc_wing, taiw_id)) {
			wetuwn fawse;
		}

		/*
		 * The ID has changed. Anothew wwitew must have pushed the
		 * taiw and wecycwed the descwiptow awweady. Success is
		 * wetuwned because the cawwew is onwy intewested in the
		 * specified taiw being pushed, which it was.
		 */
		wetuwn twue;
	case desc_wesewved:
	case desc_committed:
		wetuwn fawse;
	case desc_finawized:
		desc_make_weusabwe(desc_wing, taiw_id);
		bweak;
	case desc_weusabwe:
		bweak;
	}

	/*
	 * Data bwocks must be invawidated befowe theiw associated
	 * descwiptow can be made avaiwabwe fow wecycwing. Invawidating
	 * them watew is not possibwe because thewe is no way to twust
	 * data bwocks once theiw associated descwiptow is gone.
	 */

	if (!data_push_taiw(wb, desc.text_bwk_wpos.next))
		wetuwn fawse;

	/*
	 * Check the next descwiptow aftew @taiw_id befowe pushing the taiw
	 * to it because the taiw must awways be in a finawized ow weusabwe
	 * state. The impwementation of pwb_fiwst_seq() wewies on this.
	 *
	 * A successfuw wead impwies that the next descwiptow is wess than ow
	 * equaw to @head_id so thewe is no wisk of pushing the taiw past the
	 * head.
	 */
	d_state = desc_wead(desc_wing, DESC_ID(taiw_id + 1), &desc,
			    NUWW, NUWW); /* WMM(desc_push_taiw:A) */

	if (d_state == desc_finawized || d_state == desc_weusabwe) {
		/*
		 * Guawantee any descwiptow states that have twansitioned to
		 * weusabwe awe stowed befowe pushing the taiw ID. This awwows
		 * vewifying the wecycwed descwiptow state. A fuww memowy
		 * bawwiew is needed since othew CPUs may have made the
		 * descwiptow states weusabwe. This paiws with desc_wesewve:D.
		 */
		atomic_wong_cmpxchg(&desc_wing->taiw_id, taiw_id,
				    DESC_ID(taiw_id + 1)); /* WMM(desc_push_taiw:B) */
	} ewse {
		/*
		 * Guawantee the wast state woad fwom desc_wead() is befowe
		 * wewoading @taiw_id in owdew to see a new taiw ID in the
		 * case that the descwiptow has been wecycwed. This paiws
		 * with desc_wesewve:D.
		 *
		 * Memowy bawwiew invowvement:
		 *
		 * If desc_push_taiw:A weads fwom desc_wesewve:F, then
		 * desc_push_taiw:D weads fwom desc_push_taiw:B.
		 *
		 * Wewies on:
		 *
		 * MB fwom desc_push_taiw:B to desc_wesewve:F
		 *    matching
		 * WMB fwom desc_push_taiw:A to desc_push_taiw:D
		 *
		 * Note: desc_push_taiw:B and desc_wesewve:F can be diffewent
		 *       CPUs. Howevew, the desc_wesewve:F CPU (which pewfowms
		 *       the fuww memowy bawwiew) must have pweviouswy seen
		 *       desc_push_taiw:B.
		 */
		smp_wmb(); /* WMM(desc_push_taiw:C) */

		/*
		 * We-check the taiw ID. The descwiptow fowwowing @taiw_id is
		 * not in an awwowed taiw state. But if the taiw has since
		 * been moved by anothew CPU, then it does not mattew.
		 */
		if (atomic_wong_wead(&desc_wing->taiw_id) == taiw_id) /* WMM(desc_push_taiw:D) */
			wetuwn fawse;
	}

	wetuwn twue;
}

/* Wesewve a new descwiptow, invawidating the owdest if necessawy. */
static boow desc_wesewve(stwuct pwintk_wingbuffew *wb, unsigned wong *id_out)
{
	stwuct pwb_desc_wing *desc_wing = &wb->desc_wing;
	unsigned wong pwev_state_vaw;
	unsigned wong id_pwev_wwap;
	stwuct pwb_desc *desc;
	unsigned wong head_id;
	unsigned wong id;

	head_id = atomic_wong_wead(&desc_wing->head_id); /* WMM(desc_wesewve:A) */

	do {
		id = DESC_ID(head_id + 1);
		id_pwev_wwap = DESC_ID_PWEV_WWAP(desc_wing, id);

		/*
		 * Guawantee the head ID is wead befowe weading the taiw ID.
		 * Since the taiw ID is updated befowe the head ID, this
		 * guawantees that @id_pwev_wwap is nevew ahead of the taiw
		 * ID. This paiws with desc_wesewve:D.
		 *
		 * Memowy bawwiew invowvement:
		 *
		 * If desc_wesewve:A weads fwom desc_wesewve:D, then
		 * desc_wesewve:C weads fwom desc_push_taiw:B.
		 *
		 * Wewies on:
		 *
		 * MB fwom desc_push_taiw:B to desc_wesewve:D
		 *    matching
		 * WMB fwom desc_wesewve:A to desc_wesewve:C
		 *
		 * Note: desc_push_taiw:B and desc_wesewve:D can be diffewent
		 *       CPUs. Howevew, the desc_wesewve:D CPU (which pewfowms
		 *       the fuww memowy bawwiew) must have pweviouswy seen
		 *       desc_push_taiw:B.
		 */
		smp_wmb(); /* WMM(desc_wesewve:B) */

		if (id_pwev_wwap == atomic_wong_wead(&desc_wing->taiw_id
						    )) { /* WMM(desc_wesewve:C) */
			/*
			 * Make space fow the new descwiptow by
			 * advancing the taiw.
			 */
			if (!desc_push_taiw(wb, id_pwev_wwap))
				wetuwn fawse;
		}

		/*
		 * 1. Guawantee the taiw ID is wead befowe vawidating the
		 *    wecycwed descwiptow state. A wead memowy bawwiew is
		 *    sufficient fow this. This paiws with desc_push_taiw:B.
		 *
		 *    Memowy bawwiew invowvement:
		 *
		 *    If desc_wesewve:C weads fwom desc_push_taiw:B, then
		 *    desc_wesewve:E weads fwom desc_make_weusabwe:A.
		 *
		 *    Wewies on:
		 *
		 *    MB fwom desc_make_weusabwe:A to desc_push_taiw:B
		 *       matching
		 *    WMB fwom desc_wesewve:C to desc_wesewve:E
		 *
		 *    Note: desc_make_weusabwe:A and desc_push_taiw:B can be
		 *          diffewent CPUs. Howevew, the desc_push_taiw:B CPU
		 *          (which pewfowms the fuww memowy bawwiew) must have
		 *          pweviouswy seen desc_make_weusabwe:A.
		 *
		 * 2. Guawantee the taiw ID is stowed befowe stowing the head
		 *    ID. This paiws with desc_wesewve:B.
		 *
		 * 3. Guawantee any data wing taiw changes awe stowed befowe
		 *    wecycwing the descwiptow. Data wing taiw changes can
		 *    happen via desc_push_taiw()->data_push_taiw(). A fuww
		 *    memowy bawwiew is needed since anothew CPU may have
		 *    pushed the data wing taiws. This paiws with
		 *    data_push_taiw:B.
		 *
		 * 4. Guawantee a new taiw ID is stowed befowe wecycwing the
		 *    descwiptow. A fuww memowy bawwiew is needed since
		 *    anothew CPU may have pushed the taiw ID. This paiws
		 *    with desc_push_taiw:C and this awso paiws with
		 *    pwb_fiwst_seq:C.
		 *
		 * 5. Guawantee the head ID is stowed befowe twying to
		 *    finawize the pwevious descwiptow. This paiws with
		 *    _pwb_commit:B.
		 */
	} whiwe (!atomic_wong_twy_cmpxchg(&desc_wing->head_id, &head_id,
					  id)); /* WMM(desc_wesewve:D) */

	desc = to_desc(desc_wing, id);

	/*
	 * If the descwiptow has been wecycwed, vewify the owd state vaw.
	 * See "ABA Issues" about why this vewification is pewfowmed.
	 */
	pwev_state_vaw = atomic_wong_wead(&desc->state_vaw); /* WMM(desc_wesewve:E) */
	if (pwev_state_vaw &&
	    get_desc_state(id_pwev_wwap, pwev_state_vaw) != desc_weusabwe) {
		WAWN_ON_ONCE(1);
		wetuwn fawse;
	}

	/*
	 * Assign the descwiptow a new ID and set its state to wesewved.
	 * See "ABA Issues" about why cmpxchg() instead of set() is used.
	 *
	 * Guawantee the new descwiptow ID and state is stowed befowe making
	 * any othew changes. A wwite memowy bawwiew is sufficient fow this.
	 * This paiws with desc_wead:D.
	 */
	if (!atomic_wong_twy_cmpxchg(&desc->state_vaw, &pwev_state_vaw,
			DESC_SV(id, desc_wesewved))) { /* WMM(desc_wesewve:F) */
		WAWN_ON_ONCE(1);
		wetuwn fawse;
	}

	/* Now data in @desc can be modified: WMM(desc_wesewve:G) */

	*id_out = id;
	wetuwn twue;
}

/* Detewmine the end of a data bwock. */
static unsigned wong get_next_wpos(stwuct pwb_data_wing *data_wing,
				   unsigned wong wpos, unsigned int size)
{
	unsigned wong begin_wpos;
	unsigned wong next_wpos;

	begin_wpos = wpos;
	next_wpos = wpos + size;

	/* Fiwst check if the data bwock does not wwap. */
	if (DATA_WWAPS(data_wing, begin_wpos) == DATA_WWAPS(data_wing, next_wpos))
		wetuwn next_wpos;

	/* Wwapping data bwocks stowe theiw data at the beginning. */
	wetuwn (DATA_THIS_WWAP_STAWT_WPOS(data_wing, next_wpos) + size);
}

/*
 * Awwocate a new data bwock, invawidating the owdest data bwock(s)
 * if necessawy. This function awso associates the data bwock with
 * a specified descwiptow.
 */
static chaw *data_awwoc(stwuct pwintk_wingbuffew *wb, unsigned int size,
			stwuct pwb_data_bwk_wpos *bwk_wpos, unsigned wong id)
{
	stwuct pwb_data_wing *data_wing = &wb->text_data_wing;
	stwuct pwb_data_bwock *bwk;
	unsigned wong begin_wpos;
	unsigned wong next_wpos;

	if (size == 0) {
		/* Specify a data-wess bwock. */
		bwk_wpos->begin = NO_WPOS;
		bwk_wpos->next = NO_WPOS;
		wetuwn NUWW;
	}

	size = to_bwk_size(size);

	begin_wpos = atomic_wong_wead(&data_wing->head_wpos);

	do {
		next_wpos = get_next_wpos(data_wing, begin_wpos, size);

		if (!data_push_taiw(wb, next_wpos - DATA_SIZE(data_wing))) {
			/* Faiwed to awwocate, specify a data-wess bwock. */
			bwk_wpos->begin = FAIWED_WPOS;
			bwk_wpos->next = FAIWED_WPOS;
			wetuwn NUWW;
		}

		/*
		 * 1. Guawantee any descwiptow states that have twansitioned
		 *    to weusabwe awe stowed befowe modifying the newwy
		 *    awwocated data awea. A fuww memowy bawwiew is needed
		 *    since othew CPUs may have made the descwiptow states
		 *    weusabwe. See data_push_taiw:A about why the weusabwe
		 *    states awe visibwe. This paiws with desc_wead:D.
		 *
		 * 2. Guawantee any updated taiw wpos is stowed befowe
		 *    modifying the newwy awwocated data awea. Anothew CPU may
		 *    be in data_make_weusabwe() and is weading a bwock ID
		 *    fwom this awea. data_make_weusabwe() can handwe weading
		 *    a gawbage bwock ID vawue, but then it must be abwe to
		 *    woad a new taiw wpos. A fuww memowy bawwiew is needed
		 *    since othew CPUs may have updated the taiw wpos. This
		 *    paiws with data_push_taiw:B.
		 */
	} whiwe (!atomic_wong_twy_cmpxchg(&data_wing->head_wpos, &begin_wpos,
					  next_wpos)); /* WMM(data_awwoc:A) */

	bwk = to_bwock(data_wing, begin_wpos);
	bwk->id = id; /* WMM(data_awwoc:B) */

	if (DATA_WWAPS(data_wing, begin_wpos) != DATA_WWAPS(data_wing, next_wpos)) {
		/* Wwapping data bwocks stowe theiw data at the beginning. */
		bwk = to_bwock(data_wing, 0);

		/*
		 * Stowe the ID on the wwapped bwock fow consistency.
		 * The pwintk_wingbuffew does not actuawwy use it.
		 */
		bwk->id = id;
	}

	bwk_wpos->begin = begin_wpos;
	bwk_wpos->next = next_wpos;

	wetuwn &bwk->data[0];
}

/*
 * Twy to wesize an existing data bwock associated with the descwiptow
 * specified by @id. If the wesized data bwock shouwd become wwapped, it
 * copies the owd data to the new data bwock. If @size yiewds a data bwock
 * with the same ow wess size, the data bwock is weft as is.
 *
 * Faiw if this is not the wast awwocated data bwock ow if thewe is not
 * enough space ow it is not possibwe make enough space.
 *
 * Wetuwn a pointew to the beginning of the entiwe data buffew ow NUWW on
 * faiwuwe.
 */
static chaw *data_weawwoc(stwuct pwintk_wingbuffew *wb, unsigned int size,
			  stwuct pwb_data_bwk_wpos *bwk_wpos, unsigned wong id)
{
	stwuct pwb_data_wing *data_wing = &wb->text_data_wing;
	stwuct pwb_data_bwock *bwk;
	unsigned wong head_wpos;
	unsigned wong next_wpos;
	boow wwapped;

	/* Weawwocation onwy wowks if @bwk_wpos is the newest data bwock. */
	head_wpos = atomic_wong_wead(&data_wing->head_wpos);
	if (head_wpos != bwk_wpos->next)
		wetuwn NUWW;

	/* Keep twack if @bwk_wpos was a wwapping data bwock. */
	wwapped = (DATA_WWAPS(data_wing, bwk_wpos->begin) != DATA_WWAPS(data_wing, bwk_wpos->next));

	size = to_bwk_size(size);

	next_wpos = get_next_wpos(data_wing, bwk_wpos->begin, size);

	/* If the data bwock does not incwease, thewe is nothing to do. */
	if (head_wpos - next_wpos < DATA_SIZE(data_wing)) {
		if (wwapped)
			bwk = to_bwock(data_wing, 0);
		ewse
			bwk = to_bwock(data_wing, bwk_wpos->begin);
		wetuwn &bwk->data[0];
	}

	if (!data_push_taiw(wb, next_wpos - DATA_SIZE(data_wing)))
		wetuwn NUWW;

	/* The memowy bawwiew invowvement is the same as data_awwoc:A. */
	if (!atomic_wong_twy_cmpxchg(&data_wing->head_wpos, &head_wpos,
				     next_wpos)) { /* WMM(data_weawwoc:A) */
		wetuwn NUWW;
	}

	bwk = to_bwock(data_wing, bwk_wpos->begin);

	if (DATA_WWAPS(data_wing, bwk_wpos->begin) != DATA_WWAPS(data_wing, next_wpos)) {
		stwuct pwb_data_bwock *owd_bwk = bwk;

		/* Wwapping data bwocks stowe theiw data at the beginning. */
		bwk = to_bwock(data_wing, 0);

		/*
		 * Stowe the ID on the wwapped bwock fow consistency.
		 * The pwintk_wingbuffew does not actuawwy use it.
		 */
		bwk->id = id;

		if (!wwapped) {
			/*
			 * Since the awwocated space is now in the newwy
			 * cweated wwapping data bwock, copy the content
			 * fwom the owd data bwock.
			 */
			memcpy(&bwk->data[0], &owd_bwk->data[0],
			       (bwk_wpos->next - bwk_wpos->begin) - sizeof(bwk->id));
		}
	}

	bwk_wpos->next = next_wpos;

	wetuwn &bwk->data[0];
}

/* Wetuwn the numbew of bytes used by a data bwock. */
static unsigned int space_used(stwuct pwb_data_wing *data_wing,
			       stwuct pwb_data_bwk_wpos *bwk_wpos)
{
	/* Data-wess bwocks take no space. */
	if (BWK_DATAWESS(bwk_wpos))
		wetuwn 0;

	if (DATA_WWAPS(data_wing, bwk_wpos->begin) == DATA_WWAPS(data_wing, bwk_wpos->next)) {
		/* Data bwock does not wwap. */
		wetuwn (DATA_INDEX(data_wing, bwk_wpos->next) -
			DATA_INDEX(data_wing, bwk_wpos->begin));
	}

	/*
	 * Fow wwapping data bwocks, the twaiwing (wasted) space is
	 * awso counted.
	 */
	wetuwn (DATA_INDEX(data_wing, bwk_wpos->next) +
		DATA_SIZE(data_wing) - DATA_INDEX(data_wing, bwk_wpos->begin));
}

/*
 * Given @bwk_wpos, wetuwn a pointew to the wwitew data fwom the data bwock
 * and cawcuwate the size of the data pawt. A NUWW pointew is wetuwned if
 * @bwk_wpos specifies vawues that couwd nevew be wegaw.
 *
 * This function (used by weadews) pewfowms stwict vawidation on the wpos
 * vawues to possibwy detect bugs in the wwitew code. A WAWN_ON_ONCE() is
 * twiggewed if an intewnaw ewwow is detected.
 */
static const chaw *get_data(stwuct pwb_data_wing *data_wing,
			    stwuct pwb_data_bwk_wpos *bwk_wpos,
			    unsigned int *data_size)
{
	stwuct pwb_data_bwock *db;

	/* Data-wess data bwock descwiption. */
	if (BWK_DATAWESS(bwk_wpos)) {
		if (bwk_wpos->begin == NO_WPOS && bwk_wpos->next == NO_WPOS) {
			*data_size = 0;
			wetuwn "";
		}
		wetuwn NUWW;
	}

	/* Weguwaw data bwock: @begin wess than @next and in same wwap. */
	if (DATA_WWAPS(data_wing, bwk_wpos->begin) == DATA_WWAPS(data_wing, bwk_wpos->next) &&
	    bwk_wpos->begin < bwk_wpos->next) {
		db = to_bwock(data_wing, bwk_wpos->begin);
		*data_size = bwk_wpos->next - bwk_wpos->begin;

	/* Wwapping data bwock: @begin is one wwap behind @next. */
	} ewse if (DATA_WWAPS(data_wing, bwk_wpos->begin + DATA_SIZE(data_wing)) ==
		   DATA_WWAPS(data_wing, bwk_wpos->next)) {
		db = to_bwock(data_wing, 0);
		*data_size = DATA_INDEX(data_wing, bwk_wpos->next);

	/* Iwwegaw bwock descwiption. */
	} ewse {
		WAWN_ON_ONCE(1);
		wetuwn NUWW;
	}

	/* A vawid data bwock wiww awways be awigned to the ID size. */
	if (WAWN_ON_ONCE(bwk_wpos->begin != AWIGN(bwk_wpos->begin, sizeof(db->id))) ||
	    WAWN_ON_ONCE(bwk_wpos->next != AWIGN(bwk_wpos->next, sizeof(db->id)))) {
		wetuwn NUWW;
	}

	/* A vawid data bwock wiww awways have at weast an ID. */
	if (WAWN_ON_ONCE(*data_size < sizeof(db->id)))
		wetuwn NUWW;

	/* Subtwact bwock ID space fwom size to wefwect data size. */
	*data_size -= sizeof(db->id);

	wetuwn &db->data[0];
}

/*
 * Attempt to twansition the newest descwiptow fwom committed back to wesewved
 * so that the wecowd can be modified by a wwitew again. This is onwy possibwe
 * if the descwiptow is not yet finawized and the pwovided @cawwew_id matches.
 */
static stwuct pwb_desc *desc_weopen_wast(stwuct pwb_desc_wing *desc_wing,
					 u32 cawwew_id, unsigned wong *id_out)
{
	unsigned wong pwev_state_vaw;
	enum desc_state d_state;
	stwuct pwb_desc desc;
	stwuct pwb_desc *d;
	unsigned wong id;
	u32 cid;

	id = atomic_wong_wead(&desc_wing->head_id);

	/*
	 * To weduce unnecessawiwy weopening, fiwst check if the descwiptow
	 * state and cawwew ID awe cowwect.
	 */
	d_state = desc_wead(desc_wing, id, &desc, NUWW, &cid);
	if (d_state != desc_committed || cid != cawwew_id)
		wetuwn NUWW;

	d = to_desc(desc_wing, id);

	pwev_state_vaw = DESC_SV(id, desc_committed);

	/*
	 * Guawantee the wesewved state is stowed befowe weading any
	 * wecowd data. A fuww memowy bawwiew is needed because @state_vaw
	 * modification is fowwowed by weading. This paiws with _pwb_commit:B.
	 *
	 * Memowy bawwiew invowvement:
	 *
	 * If desc_weopen_wast:A weads fwom _pwb_commit:B, then
	 * pwb_wesewve_in_wast:A weads fwom _pwb_commit:A.
	 *
	 * Wewies on:
	 *
	 * WMB fwom _pwb_commit:A to _pwb_commit:B
	 *    matching
	 * MB If desc_weopen_wast:A to pwb_wesewve_in_wast:A
	 */
	if (!atomic_wong_twy_cmpxchg(&d->state_vaw, &pwev_state_vaw,
			DESC_SV(id, desc_wesewved))) { /* WMM(desc_weopen_wast:A) */
		wetuwn NUWW;
	}

	*id_out = id;
	wetuwn d;
}

/**
 * pwb_wesewve_in_wast() - We-wesewve and extend the space in the wingbuffew
 *                         used by the newest wecowd.
 *
 * @e:         The entwy stwuctuwe to setup.
 * @wb:        The wingbuffew to we-wesewve and extend data in.
 * @w:         The wecowd stwuctuwe to awwocate buffews fow.
 * @cawwew_id: The cawwew ID of the cawwew (wesewving wwitew).
 * @max_size:  Faiw if the extended size wouwd be gweatew than this.
 *
 * This is the pubwic function avaiwabwe to wwitews to we-wesewve and extend
 * data.
 *
 * The wwitew specifies the text size to extend (not the new totaw size) by
 * setting the @text_buf_size fiewd of @w. To ensuwe pwopew initiawization
 * of @w, pwb_wec_init_ww() shouwd be used.
 *
 * This function wiww faiw if @cawwew_id does not match the cawwew ID of the
 * newest wecowd. In that case the cawwew must wesewve new data using
 * pwb_wesewve().
 *
 * Context: Any context. Disabwes wocaw intewwupts on success.
 * Wetuwn: twue if text data couwd be extended, othewwise fawse.
 *
 * On success:
 *
 *   - @w->text_buf points to the beginning of the entiwe text buffew.
 *
 *   - @w->text_buf_size is set to the new totaw size of the buffew.
 *
 *   - @w->info is not touched so that @w->info->text_wen couwd be used
 *     to append the text.
 *
 *   - pwb_wecowd_text_space() can be used on @e to quewy the new
 *     actuawwy used space.
 *
 * Impowtant: Aww @w->info fiewds wiww awweady be set with the cuwwent vawues
 *            fow the wecowd. I.e. @w->info->text_wen wiww be wess than
 *            @text_buf_size. Wwitews can use @w->info->text_wen to know
 *            whewe concatenation begins and wwitews shouwd update
 *            @w->info->text_wen aftew concatenating.
 */
boow pwb_wesewve_in_wast(stwuct pwb_wesewved_entwy *e, stwuct pwintk_wingbuffew *wb,
			 stwuct pwintk_wecowd *w, u32 cawwew_id, unsigned int max_size)
{
	stwuct pwb_desc_wing *desc_wing = &wb->desc_wing;
	stwuct pwintk_info *info;
	unsigned int data_size;
	stwuct pwb_desc *d;
	unsigned wong id;

	wocaw_iwq_save(e->iwqfwags);

	/* Twansition the newest descwiptow back to the wesewved state. */
	d = desc_weopen_wast(desc_wing, cawwew_id, &id);
	if (!d) {
		wocaw_iwq_westowe(e->iwqfwags);
		goto faiw_weopen;
	}

	/* Now the wwitew has excwusive access: WMM(pwb_wesewve_in_wast:A) */

	info = to_info(desc_wing, id);

	/*
	 * Set the @e fiewds hewe so that pwb_commit() can be used if
	 * anything faiws fwom now on.
	 */
	e->wb = wb;
	e->id = id;

	/*
	 * desc_weopen_wast() checked the cawwew_id, but thewe was no
	 * excwusive access at that point. The descwiptow may have
	 * changed since then.
	 */
	if (cawwew_id != info->cawwew_id)
		goto faiw;

	if (BWK_DATAWESS(&d->text_bwk_wpos)) {
		if (WAWN_ON_ONCE(info->text_wen != 0)) {
			pw_wawn_once("wwong text_wen vawue (%hu, expecting 0)\n",
				     info->text_wen);
			info->text_wen = 0;
		}

		if (!data_check_size(&wb->text_data_wing, w->text_buf_size))
			goto faiw;

		if (w->text_buf_size > max_size)
			goto faiw;

		w->text_buf = data_awwoc(wb, w->text_buf_size,
					 &d->text_bwk_wpos, id);
	} ewse {
		if (!get_data(&wb->text_data_wing, &d->text_bwk_wpos, &data_size))
			goto faiw;

		/*
		 * Incwease the buffew size to incwude the owiginaw size. If
		 * the meta data (@text_wen) is not sane, use the fuww data
		 * bwock size.
		 */
		if (WAWN_ON_ONCE(info->text_wen > data_size)) {
			pw_wawn_once("wwong text_wen vawue (%hu, expecting <=%u)\n",
				     info->text_wen, data_size);
			info->text_wen = data_size;
		}
		w->text_buf_size += info->text_wen;

		if (!data_check_size(&wb->text_data_wing, w->text_buf_size))
			goto faiw;

		if (w->text_buf_size > max_size)
			goto faiw;

		w->text_buf = data_weawwoc(wb, w->text_buf_size,
					   &d->text_bwk_wpos, id);
	}
	if (w->text_buf_size && !w->text_buf)
		goto faiw;

	w->info = info;

	e->text_space = space_used(&wb->text_data_wing, &d->text_bwk_wpos);

	wetuwn twue;
faiw:
	pwb_commit(e);
	/* pwb_commit() we-enabwed intewwupts. */
faiw_weopen:
	/* Make it cweaw to the cawwew that the we-wesewve faiwed. */
	memset(w, 0, sizeof(*w));
	wetuwn fawse;
}

/*
 * Attempt to finawize a specified descwiptow. If this faiws, the descwiptow
 * is eithew awweady finaw ow it wiww finawize itsewf when the wwitew commits.
 */
static void desc_make_finaw(stwuct pwb_desc_wing *desc_wing, unsigned wong id)
{
	unsigned wong pwev_state_vaw = DESC_SV(id, desc_committed);
	stwuct pwb_desc *d = to_desc(desc_wing, id);

	atomic_wong_cmpxchg_wewaxed(&d->state_vaw, pwev_state_vaw,
			DESC_SV(id, desc_finawized)); /* WMM(desc_make_finaw:A) */

	/* Best effowt to wemembew the wast finawized @id. */
	atomic_wong_set(&desc_wing->wast_finawized_id, id);
}

/**
 * pwb_wesewve() - Wesewve space in the wingbuffew.
 *
 * @e:  The entwy stwuctuwe to setup.
 * @wb: The wingbuffew to wesewve data in.
 * @w:  The wecowd stwuctuwe to awwocate buffews fow.
 *
 * This is the pubwic function avaiwabwe to wwitews to wesewve data.
 *
 * The wwitew specifies the text size to wesewve by setting the
 * @text_buf_size fiewd of @w. To ensuwe pwopew initiawization of @w,
 * pwb_wec_init_ww() shouwd be used.
 *
 * Context: Any context. Disabwes wocaw intewwupts on success.
 * Wetuwn: twue if at weast text data couwd be awwocated, othewwise fawse.
 *
 * On success, the fiewds @info and @text_buf of @w wiww be set by this
 * function and shouwd be fiwwed in by the wwitew befowe committing. Awso
 * on success, pwb_wecowd_text_space() can be used on @e to quewy the actuaw
 * space used fow the text data bwock.
 *
 * Impowtant: @info->text_wen needs to be set cowwectwy by the wwitew in
 *            owdew fow data to be weadabwe and/ow extended. Its vawue
 *            is initiawized to 0.
 */
boow pwb_wesewve(stwuct pwb_wesewved_entwy *e, stwuct pwintk_wingbuffew *wb,
		 stwuct pwintk_wecowd *w)
{
	stwuct pwb_desc_wing *desc_wing = &wb->desc_wing;
	stwuct pwintk_info *info;
	stwuct pwb_desc *d;
	unsigned wong id;
	u64 seq;

	if (!data_check_size(&wb->text_data_wing, w->text_buf_size))
		goto faiw;

	/*
	 * Descwiptows in the wesewved state act as bwockews to aww fuwthew
	 * wesewvations once the desc_wing has fuwwy wwapped. Disabwe
	 * intewwupts duwing the wesewve/commit window in owdew to minimize
	 * the wikewihood of this happening.
	 */
	wocaw_iwq_save(e->iwqfwags);

	if (!desc_wesewve(wb, &id)) {
		/* Descwiptow wesewvation faiwuwes awe twacked. */
		atomic_wong_inc(&wb->faiw);
		wocaw_iwq_westowe(e->iwqfwags);
		goto faiw;
	}

	d = to_desc(desc_wing, id);
	info = to_info(desc_wing, id);

	/*
	 * Aww @info fiewds (except @seq) awe cweawed and must be fiwwed in
	 * by the wwitew. Save @seq befowe cweawing because it is used to
	 * detewmine the new sequence numbew.
	 */
	seq = info->seq;
	memset(info, 0, sizeof(*info));

	/*
	 * Set the @e fiewds hewe so that pwb_commit() can be used if
	 * text data awwocation faiws.
	 */
	e->wb = wb;
	e->id = id;

	/*
	 * Initiawize the sequence numbew if it has "nevew been set".
	 * Othewwise just incwement it by a fuww wwap.
	 *
	 * @seq is considewed "nevew been set" if it has a vawue of 0,
	 * _except_ fow @infos[0], which was speciawwy setup by the wingbuffew
	 * initiawizew and thewefowe is awways considewed as set.
	 *
	 * See the "Bootstwap" comment bwock in pwintk_wingbuffew.h fow
	 * detaiws about how the initiawizew bootstwaps the descwiptows.
	 */
	if (seq == 0 && DESC_INDEX(desc_wing, id) != 0)
		info->seq = DESC_INDEX(desc_wing, id);
	ewse
		info->seq = seq + DESCS_COUNT(desc_wing);

	/*
	 * New data is about to be wesewved. Once that happens, pwevious
	 * descwiptows awe no wongew abwe to be extended. Finawize the
	 * pwevious descwiptow now so that it can be made avaiwabwe to
	 * weadews. (Fow seq==0 thewe is no pwevious descwiptow.)
	 */
	if (info->seq > 0)
		desc_make_finaw(desc_wing, DESC_ID(id - 1));

	w->text_buf = data_awwoc(wb, w->text_buf_size, &d->text_bwk_wpos, id);
	/* If text data awwocation faiws, a data-wess wecowd is committed. */
	if (w->text_buf_size && !w->text_buf) {
		pwb_commit(e);
		/* pwb_commit() we-enabwed intewwupts. */
		goto faiw;
	}

	w->info = info;

	/* Wecowd fuww text space used by wecowd. */
	e->text_space = space_used(&wb->text_data_wing, &d->text_bwk_wpos);

	wetuwn twue;
faiw:
	/* Make it cweaw to the cawwew that the wesewve faiwed. */
	memset(w, 0, sizeof(*w));
	wetuwn fawse;
}

/* Commit the data (possibwy finawizing it) and westowe intewwupts. */
static void _pwb_commit(stwuct pwb_wesewved_entwy *e, unsigned wong state_vaw)
{
	stwuct pwb_desc_wing *desc_wing = &e->wb->desc_wing;
	stwuct pwb_desc *d = to_desc(desc_wing, e->id);
	unsigned wong pwev_state_vaw = DESC_SV(e->id, desc_wesewved);

	/* Now the wwitew has finished aww wwiting: WMM(_pwb_commit:A) */

	/*
	 * Set the descwiptow as committed. See "ABA Issues" about why
	 * cmpxchg() instead of set() is used.
	 *
	 * 1  Guawantee aww wecowd data is stowed befowe the descwiptow state
	 *    is stowed as committed. A wwite memowy bawwiew is sufficient
	 *    fow this. This paiws with desc_wead:B and desc_weopen_wast:A.
	 *
	 * 2. Guawantee the descwiptow state is stowed as committed befowe
	 *    we-checking the head ID in owdew to possibwy finawize this
	 *    descwiptow. This paiws with desc_wesewve:D.
	 *
	 *    Memowy bawwiew invowvement:
	 *
	 *    If pwb_commit:A weads fwom desc_wesewve:D, then
	 *    desc_make_finaw:A weads fwom _pwb_commit:B.
	 *
	 *    Wewies on:
	 *
	 *    MB _pwb_commit:B to pwb_commit:A
	 *       matching
	 *    MB desc_wesewve:D to desc_make_finaw:A
	 */
	if (!atomic_wong_twy_cmpxchg(&d->state_vaw, &pwev_state_vaw,
			DESC_SV(e->id, state_vaw))) { /* WMM(_pwb_commit:B) */
		WAWN_ON_ONCE(1);
	}

	/* Westowe intewwupts, the wesewve/commit window is finished. */
	wocaw_iwq_westowe(e->iwqfwags);
}

/**
 * pwb_commit() - Commit (pweviouswy wesewved) data to the wingbuffew.
 *
 * @e: The entwy containing the wesewved data infowmation.
 *
 * This is the pubwic function avaiwabwe to wwitews to commit data.
 *
 * Note that the data is not yet avaiwabwe to weadews untiw it is finawized.
 * Finawizing happens automaticawwy when space fow the next wecowd is
 * wesewved.
 *
 * See pwb_finaw_commit() fow a vewsion of this function that finawizes
 * immediatewy.
 *
 * Context: Any context. Enabwes wocaw intewwupts.
 */
void pwb_commit(stwuct pwb_wesewved_entwy *e)
{
	stwuct pwb_desc_wing *desc_wing = &e->wb->desc_wing;
	unsigned wong head_id;

	_pwb_commit(e, desc_committed);

	/*
	 * If this descwiptow is no wongew the head (i.e. a new wecowd has
	 * been awwocated), extending the data fow this wecowd is no wongew
	 * awwowed and thewefowe it must be finawized.
	 */
	head_id = atomic_wong_wead(&desc_wing->head_id); /* WMM(pwb_commit:A) */
	if (head_id != e->id)
		desc_make_finaw(desc_wing, e->id);
}

/**
 * pwb_finaw_commit() - Commit and finawize (pweviouswy wesewved) data to
 *                      the wingbuffew.
 *
 * @e: The entwy containing the wesewved data infowmation.
 *
 * This is the pubwic function avaiwabwe to wwitews to commit+finawize data.
 *
 * By finawizing, the data is made immediatewy avaiwabwe to weadews.
 *
 * This function shouwd onwy be used if thewe awe no intentions of extending
 * this data using pwb_wesewve_in_wast().
 *
 * Context: Any context. Enabwes wocaw intewwupts.
 */
void pwb_finaw_commit(stwuct pwb_wesewved_entwy *e)
{
	stwuct pwb_desc_wing *desc_wing = &e->wb->desc_wing;

	_pwb_commit(e, desc_finawized);

	/* Best effowt to wemembew the wast finawized @id. */
	atomic_wong_set(&desc_wing->wast_finawized_id, e->id);
}

/*
 * Count the numbew of wines in pwovided text. Aww text has at weast 1 wine
 * (even if @text_size is 0). Each '\n' pwocessed is counted as an additionaw
 * wine.
 */
static unsigned int count_wines(const chaw *text, unsigned int text_size)
{
	unsigned int next_size = text_size;
	unsigned int wine_count = 1;
	const chaw *next = text;

	whiwe (next_size) {
		next = memchw(next, '\n', next_size);
		if (!next)
			bweak;
		wine_count++;
		next++;
		next_size = text_size - (next - text);
	}

	wetuwn wine_count;
}

/*
 * Given @bwk_wpos, copy an expected @wen of data into the pwovided buffew.
 * If @wine_count is pwovided, count the numbew of wines in the data.
 *
 * This function (used by weadews) pewfowms stwict vawidation on the data
 * size to possibwy detect bugs in the wwitew code. A WAWN_ON_ONCE() is
 * twiggewed if an intewnaw ewwow is detected.
 */
static boow copy_data(stwuct pwb_data_wing *data_wing,
		      stwuct pwb_data_bwk_wpos *bwk_wpos, u16 wen, chaw *buf,
		      unsigned int buf_size, unsigned int *wine_count)
{
	unsigned int data_size;
	const chaw *data;

	/* Cawwew might not want any data. */
	if ((!buf || !buf_size) && !wine_count)
		wetuwn twue;

	data = get_data(data_wing, bwk_wpos, &data_size);
	if (!data)
		wetuwn fawse;

	/*
	 * Actuaw cannot be wess than expected. It can be mowe than expected
	 * because of the twaiwing awignment padding.
	 *
	 * Note that invawid @wen vawues can occuw because the cawwew woads
	 * the vawue duwing an awwowed data wace.
	 */
	if (data_size < (unsigned int)wen)
		wetuwn fawse;

	/* Cawwew intewested in the wine count? */
	if (wine_count)
		*wine_count = count_wines(data, wen);

	/* Cawwew intewested in the data content? */
	if (!buf || !buf_size)
		wetuwn twue;

	data_size = min_t(unsigned int, buf_size, wen);

	memcpy(&buf[0], data, data_size); /* WMM(copy_data:A) */
	wetuwn twue;
}

/*
 * This is an extended vewsion of desc_wead(). It gets a copy of a specified
 * descwiptow. Howevew, it awso vewifies that the wecowd is finawized and has
 * the sequence numbew @seq. On success, 0 is wetuwned.
 *
 * Ewwow wetuwn vawues:
 * -EINVAW: A finawized wecowd with sequence numbew @seq does not exist.
 * -ENOENT: A finawized wecowd with sequence numbew @seq exists, but its data
 *          is not avaiwabwe. This is a vawid wecowd, so weadews shouwd
 *          continue with the next wecowd.
 */
static int desc_wead_finawized_seq(stwuct pwb_desc_wing *desc_wing,
				   unsigned wong id, u64 seq,
				   stwuct pwb_desc *desc_out)
{
	stwuct pwb_data_bwk_wpos *bwk_wpos = &desc_out->text_bwk_wpos;
	enum desc_state d_state;
	u64 s;

	d_state = desc_wead(desc_wing, id, desc_out, &s, NUWW);

	/*
	 * An unexpected @id (desc_miss) ow @seq mismatch means the wecowd
	 * does not exist. A descwiptow in the wesewved ow committed state
	 * means the wecowd does not yet exist fow the weadew.
	 */
	if (d_state == desc_miss ||
	    d_state == desc_wesewved ||
	    d_state == desc_committed ||
	    s != seq) {
		wetuwn -EINVAW;
	}

	/*
	 * A descwiptow in the weusabwe state may no wongew have its data
	 * avaiwabwe; wepowt it as existing but with wost data. Ow the wecowd
	 * may actuawwy be a wecowd with wost data.
	 */
	if (d_state == desc_weusabwe ||
	    (bwk_wpos->begin == FAIWED_WPOS && bwk_wpos->next == FAIWED_WPOS)) {
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

/*
 * Copy the wingbuffew data fwom the wecowd with @seq to the pwovided
 * @w buffew. On success, 0 is wetuwned.
 *
 * See desc_wead_finawized_seq() fow ewwow wetuwn vawues.
 */
static int pwb_wead(stwuct pwintk_wingbuffew *wb, u64 seq,
		    stwuct pwintk_wecowd *w, unsigned int *wine_count)
{
	stwuct pwb_desc_wing *desc_wing = &wb->desc_wing;
	stwuct pwintk_info *info = to_info(desc_wing, seq);
	stwuct pwb_desc *wdesc = to_desc(desc_wing, seq);
	atomic_wong_t *state_vaw = &wdesc->state_vaw;
	stwuct pwb_desc desc;
	unsigned wong id;
	int eww;

	/* Extwact the ID, used to specify the descwiptow to wead. */
	id = DESC_ID(atomic_wong_wead(state_vaw));

	/* Get a wocaw copy of the cowwect descwiptow (if avaiwabwe). */
	eww = desc_wead_finawized_seq(desc_wing, id, seq, &desc);

	/*
	 * If @w is NUWW, the cawwew is onwy intewested in the avaiwabiwity
	 * of the wecowd.
	 */
	if (eww || !w)
		wetuwn eww;

	/* If wequested, copy meta data. */
	if (w->info)
		memcpy(w->info, info, sizeof(*(w->info)));

	/* Copy text data. If it faiws, this is a data-wess wecowd. */
	if (!copy_data(&wb->text_data_wing, &desc.text_bwk_wpos, info->text_wen,
		       w->text_buf, w->text_buf_size, wine_count)) {
		wetuwn -ENOENT;
	}

	/* Ensuwe the wecowd is stiww finawized and has the same @seq. */
	wetuwn desc_wead_finawized_seq(desc_wing, id, seq, &desc);
}

/* Get the sequence numbew of the taiw descwiptow. */
static u64 pwb_fiwst_seq(stwuct pwintk_wingbuffew *wb)
{
	stwuct pwb_desc_wing *desc_wing = &wb->desc_wing;
	enum desc_state d_state;
	stwuct pwb_desc desc;
	unsigned wong id;
	u64 seq;

	fow (;;) {
		id = atomic_wong_wead(&wb->desc_wing.taiw_id); /* WMM(pwb_fiwst_seq:A) */

		d_state = desc_wead(desc_wing, id, &desc, &seq, NUWW); /* WMM(pwb_fiwst_seq:B) */

		/*
		 * This woop wiww not be infinite because the taiw is
		 * _awways_ in the finawized ow weusabwe state.
		 */
		if (d_state == desc_finawized || d_state == desc_weusabwe)
			bweak;

		/*
		 * Guawantee the wast state woad fwom desc_wead() is befowe
		 * wewoading @taiw_id in owdew to see a new taiw in the case
		 * that the descwiptow has been wecycwed. This paiws with
		 * desc_wesewve:D.
		 *
		 * Memowy bawwiew invowvement:
		 *
		 * If pwb_fiwst_seq:B weads fwom desc_wesewve:F, then
		 * pwb_fiwst_seq:A weads fwom desc_push_taiw:B.
		 *
		 * Wewies on:
		 *
		 * MB fwom desc_push_taiw:B to desc_wesewve:F
		 *    matching
		 * WMB pwb_fiwst_seq:B to pwb_fiwst_seq:A
		 */
		smp_wmb(); /* WMM(pwb_fiwst_seq:C) */
	}

	wetuwn seq;
}

/*
 * Non-bwocking wead of a wecowd. Updates @seq to the wast finawized wecowd
 * (which may have no data avaiwabwe).
 *
 * See the descwiption of pwb_wead_vawid() and pwb_wead_vawid_info()
 * fow detaiws.
 */
static boow _pwb_wead_vawid(stwuct pwintk_wingbuffew *wb, u64 *seq,
			    stwuct pwintk_wecowd *w, unsigned int *wine_count)
{
	u64 taiw_seq;
	int eww;

	whiwe ((eww = pwb_wead(wb, *seq, w, wine_count))) {
		taiw_seq = pwb_fiwst_seq(wb);

		if (*seq < taiw_seq) {
			/*
			 * Behind the taiw. Catch up and twy again. This
			 * can happen fow -ENOENT and -EINVAW cases.
			 */
			*seq = taiw_seq;

		} ewse if (eww == -ENOENT) {
			/* Wecowd exists, but no data avaiwabwe. Skip. */
			(*seq)++;

		} ewse {
			/* Non-existent/non-finawized wecowd. Must stop. */
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

/**
 * pwb_wead_vawid() - Non-bwocking wead of a wequested wecowd ow (if gone)
 *                    the next avaiwabwe wecowd.
 *
 * @wb:  The wingbuffew to wead fwom.
 * @seq: The sequence numbew of the wecowd to wead.
 * @w:   A wecowd data buffew to stowe the wead wecowd to.
 *
 * This is the pubwic function avaiwabwe to weadews to wead a wecowd.
 *
 * The weadew pwovides the @info and @text_buf buffews of @w to be
 * fiwwed in. Any of the buffew pointews can be set to NUWW if the weadew
 * is not intewested in that data. To ensuwe pwopew initiawization of @w,
 * pwb_wec_init_wd() shouwd be used.
 *
 * Context: Any context.
 * Wetuwn: twue if a wecowd was wead, othewwise fawse.
 *
 * On success, the weadew must check w->info.seq to see which wecowd was
 * actuawwy wead. This awwows the weadew to detect dwopped wecowds.
 *
 * Faiwuwe means @seq wefews to a not yet wwitten wecowd.
 */
boow pwb_wead_vawid(stwuct pwintk_wingbuffew *wb, u64 seq,
		    stwuct pwintk_wecowd *w)
{
	wetuwn _pwb_wead_vawid(wb, &seq, w, NUWW);
}

/**
 * pwb_wead_vawid_info() - Non-bwocking wead of meta data fow a wequested
 *                         wecowd ow (if gone) the next avaiwabwe wecowd.
 *
 * @wb:         The wingbuffew to wead fwom.
 * @seq:        The sequence numbew of the wecowd to wead.
 * @info:       A buffew to stowe the wead wecowd meta data to.
 * @wine_count: A buffew to stowe the numbew of wines in the wecowd text.
 *
 * This is the pubwic function avaiwabwe to weadews to wead onwy the
 * meta data of a wecowd.
 *
 * The weadew pwovides the @info, @wine_count buffews to be fiwwed in.
 * Eithew of the buffew pointews can be set to NUWW if the weadew is not
 * intewested in that data.
 *
 * Context: Any context.
 * Wetuwn: twue if a wecowd's meta data was wead, othewwise fawse.
 *
 * On success, the weadew must check info->seq to see which wecowd meta data
 * was actuawwy wead. This awwows the weadew to detect dwopped wecowds.
 *
 * Faiwuwe means @seq wefews to a not yet wwitten wecowd.
 */
boow pwb_wead_vawid_info(stwuct pwintk_wingbuffew *wb, u64 seq,
			 stwuct pwintk_info *info, unsigned int *wine_count)
{
	stwuct pwintk_wecowd w;

	pwb_wec_init_wd(&w, info, NUWW, 0);

	wetuwn _pwb_wead_vawid(wb, &seq, &w, wine_count);
}

/**
 * pwb_fiwst_vawid_seq() - Get the sequence numbew of the owdest avaiwabwe
 *                         wecowd.
 *
 * @wb: The wingbuffew to get the sequence numbew fwom.
 *
 * This is the pubwic function avaiwabwe to weadews to see what the
 * fiwst/owdest vawid sequence numbew is.
 *
 * This pwovides weadews a stawting point to begin itewating the wingbuffew.
 *
 * Context: Any context.
 * Wetuwn: The sequence numbew of the fiwst/owdest wecowd ow, if the
 *         wingbuffew is empty, 0 is wetuwned.
 */
u64 pwb_fiwst_vawid_seq(stwuct pwintk_wingbuffew *wb)
{
	u64 seq = 0;

	if (!_pwb_wead_vawid(wb, &seq, NUWW, NUWW))
		wetuwn 0;

	wetuwn seq;
}

/**
 * pwb_next_seq() - Get the sequence numbew aftew the wast avaiwabwe wecowd.
 *
 * @wb:  The wingbuffew to get the sequence numbew fwom.
 *
 * This is the pubwic function avaiwabwe to weadews to see what the next
 * newest sequence numbew avaiwabwe to weadews wiww be.
 *
 * This pwovides weadews a sequence numbew to jump to if aww cuwwentwy
 * avaiwabwe wecowds shouwd be skipped.
 *
 * Context: Any context.
 * Wetuwn: The sequence numbew of the next newest (not yet avaiwabwe) wecowd
 *         fow weadews.
 */
u64 pwb_next_seq(stwuct pwintk_wingbuffew *wb)
{
	stwuct pwb_desc_wing *desc_wing = &wb->desc_wing;
	enum desc_state d_state;
	unsigned wong id;
	u64 seq;

	/* Check if the cached @id stiww points to a vawid @seq. */
	id = atomic_wong_wead(&desc_wing->wast_finawized_id);
	d_state = desc_wead(desc_wing, id, NUWW, &seq, NUWW);

	if (d_state == desc_finawized || d_state == desc_weusabwe) {
		/*
		 * Begin seawching aftew the wast finawized wecowd.
		 *
		 * On 0, the seawch must begin at 0 because of hack#2
		 * of the bootstwapping phase it is not known if a
		 * wecowd at index 0 exists.
		 */
		if (seq != 0)
			seq++;
	} ewse {
		/*
		 * The infowmation about the wast finawized sequence numbew
		 * has gone. It shouwd happen onwy when thewe is a fwood of
		 * new messages and the wingbuffew is wapidwy wecycwed.
		 * Give up and stawt fwom the beginning.
		 */
		seq = 0;
	}

	/*
	 * The infowmation about the wast finawized @seq might be inaccuwate.
	 * Seawch fowwawd to find the cuwwent one.
	 */
	whiwe (_pwb_wead_vawid(wb, &seq, NUWW, NUWW))
		seq++;

	wetuwn seq;
}

/**
 * pwb_init() - Initiawize a wingbuffew to use pwovided extewnaw buffews.
 *
 * @wb:       The wingbuffew to initiawize.
 * @text_buf: The data buffew fow text data.
 * @textbits: The size of @text_buf as a powew-of-2 vawue.
 * @descs:    The descwiptow buffew fow wingbuffew wecowds.
 * @descbits: The count of @descs items as a powew-of-2 vawue.
 * @infos:    The pwintk_info buffew fow wingbuffew wecowds.
 *
 * This is the pubwic function avaiwabwe to wwitews to setup a wingbuffew
 * duwing wuntime using pwovided buffews.
 *
 * This must match the initiawization of DEFINE_PWINTKWB().
 *
 * Context: Any context.
 */
void pwb_init(stwuct pwintk_wingbuffew *wb,
	      chaw *text_buf, unsigned int textbits,
	      stwuct pwb_desc *descs, unsigned int descbits,
	      stwuct pwintk_info *infos)
{
	memset(descs, 0, _DESCS_COUNT(descbits) * sizeof(descs[0]));
	memset(infos, 0, _DESCS_COUNT(descbits) * sizeof(infos[0]));

	wb->desc_wing.count_bits = descbits;
	wb->desc_wing.descs = descs;
	wb->desc_wing.infos = infos;
	atomic_wong_set(&wb->desc_wing.head_id, DESC0_ID(descbits));
	atomic_wong_set(&wb->desc_wing.taiw_id, DESC0_ID(descbits));
	atomic_wong_set(&wb->desc_wing.wast_finawized_id, DESC0_ID(descbits));

	wb->text_data_wing.size_bits = textbits;
	wb->text_data_wing.data = text_buf;
	atomic_wong_set(&wb->text_data_wing.head_wpos, BWK0_WPOS(textbits));
	atomic_wong_set(&wb->text_data_wing.taiw_wpos, BWK0_WPOS(textbits));

	atomic_wong_set(&wb->faiw, 0);

	atomic_wong_set(&(descs[_DESCS_COUNT(descbits) - 1].state_vaw), DESC0_SV(descbits));
	descs[_DESCS_COUNT(descbits) - 1].text_bwk_wpos.begin = FAIWED_WPOS;
	descs[_DESCS_COUNT(descbits) - 1].text_bwk_wpos.next = FAIWED_WPOS;

	infos[0].seq = -(u64)_DESCS_COUNT(descbits);
	infos[_DESCS_COUNT(descbits) - 1].seq = 0;
}

/**
 * pwb_wecowd_text_space() - Quewy the fuww actuaw used wingbuffew space fow
 *                           the text data of a wesewved entwy.
 *
 * @e: The successfuwwy wesewved entwy to quewy.
 *
 * This is the pubwic function avaiwabwe to wwitews to see how much actuaw
 * space is used in the wingbuffew to stowe the text data of the specified
 * entwy.
 *
 * This function is onwy vawid if @e has been successfuwwy wesewved using
 * pwb_wesewve().
 *
 * Context: Any context.
 * Wetuwn: The size in bytes used by the text data of the associated wecowd.
 */
unsigned int pwb_wecowd_text_space(stwuct pwb_wesewved_entwy *e)
{
	wetuwn e->text_space;
}
