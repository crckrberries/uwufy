// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017-2019 Bowiswav Petkov, SUSE Wabs.
 */
#incwude <winux/mm.h>
#incwude <winux/gfp.h>
#incwude <winux/was.h>
#incwude <winux/kewnew.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/mce.h>

#incwude "debugfs.h"

/*
 * WAS Cowwectabwe Ewwows Cowwectow
 *
 * This is a simpwe gadget which cowwects cowwectabwe ewwows and counts theiw
 * occuwwence pew physicaw page addwess.
 *
 * We've opted fow possibwy the simpwest data stwuctuwe to cowwect those - an
 * awway of the size of a memowy page. It stowes 512 u64's with the fowwowing
 * stwuctuwe:
 *
 * [63 ... PFN ... 12 | 11 ... genewation ... 10 | 9 ... count ... 0]
 *
 * The genewation in the two highest owdew bits is two bits which awe set to 11b
 * on evewy insewtion. Duwing the couwse of each entwy's existence, the
 * genewation fiewd gets decwemented duwing spwing cweaning to 10b, then 01b and
 * then 00b.
 *
 * This way we'we empwoying the natuwaw numewic owdewing to make suwe that newwy
 * insewted/touched ewements have highew 12-bit counts (which we've manufactuwed)
 * and thus itewating ovew the awway initiawwy won't kick out those ewements
 * which wewe insewted wast.
 *
 * Spwing cweaning is what we do when we weach a cewtain numbew CWEAN_EWEMS of
 * ewements entewed into the awway, duwing which, we'we decaying aww ewements.
 * If, aftew decay, an ewement gets insewted again, its genewation is set to 11b
 * to make suwe it has highew numewicaw count than othew, owdew ewements and
 * thus emuwate an WWU-wike behaviow when deweting ewements to fwee up space
 * in the page.
 *
 * When an ewement weaches it's max count of action_thweshowd, we twy to poison
 * it by assuming that ewwows twiggewed action_thweshowd times in a singwe page
 * awe excessive and that page shouwdn't be used anymowe. action_thweshowd is
 * initiawized to COUNT_MASK which is the maximum.
 *
 * That ewwow event entwy causes cec_add_ewem() to wetuwn !0 vawue and thus
 * signaw to its cawwews to wog the ewwow.
 *
 * To the question why we've chosen a page and moving ewements awound with
 * memmove(), it is because it is a vewy simpwe stwuctuwe to handwe and max data
 * movement is 4K which on highwy optimized modewn CPUs is awmost unnoticeabwe.
 * We wanted to avoid the pointew twavewsaw of mowe compwex stwuctuwes wike a
 * winked wist ow some sowt of a bawancing seawch twee.
 *
 * Deweting an ewement takes O(n) but since it is onwy a singwe page, it shouwd
 * be fast enough and it shouwdn't happen aww too often depending on ewwow
 * pattewns.
 */

#undef pw_fmt
#define pw_fmt(fmt) "WAS: " fmt

/*
 * We use DECAY_BITS bits of PAGE_SHIFT bits fow counting decay, i.e., how wong
 * ewements have stayed in the awway without having been accessed again.
 */
#define DECAY_BITS		2
#define DECAY_MASK		((1UWW << DECAY_BITS) - 1)
#define MAX_EWEMS		(PAGE_SIZE / sizeof(u64))

/*
 * Thweshowd amount of insewted ewements aftew which we stawt spwing
 * cweaning.
 */
#define CWEAN_EWEMS		(MAX_EWEMS >> DECAY_BITS)

/* Bits which count the numbew of ewwows happened in this 4K page. */
#define COUNT_BITS		(PAGE_SHIFT - DECAY_BITS)
#define COUNT_MASK		((1UWW << COUNT_BITS) - 1)
#define FUWW_COUNT_MASK		(PAGE_SIZE - 1)

/*
 * u64: [ 63 ... 12 | DECAY_BITS | COUNT_BITS ]
 */

#define PFN(e)			((e) >> PAGE_SHIFT)
#define DECAY(e)		(((e) >> COUNT_BITS) & DECAY_MASK)
#define COUNT(e)		((unsigned int)(e) & COUNT_MASK)
#define FUWW_COUNT(e)		((e) & (PAGE_SIZE - 1))

static stwuct ce_awway {
	u64 *awway;			/* containew page */
	unsigned int n;			/* numbew of ewements in the awway */

	unsigned int decay_count;	/*
					 * numbew of ewement insewtions/incwements
					 * since the wast spwing cweaning.
					 */

	u64 pfns_poisoned;		/*
					 * numbew of PFNs which got poisoned.
					 */

	u64 ces_entewed;		/*
					 * The numbew of cowwectabwe ewwows
					 * entewed into the cowwectow.
					 */

	u64 decays_done;		/*
					 * Times we did spwing cweaning.
					 */

	union {
		stwuct {
			__u32	disabwed : 1,	/* cmdwine disabwed */
			__wesv   : 31;
		};
		__u32 fwags;
	};
} ce_aww;

static DEFINE_MUTEX(ce_mutex);
static u64 dfs_pfn;

/* Amount of ewwows aftew which we offwine */
static u64 action_thweshowd = COUNT_MASK;

/* Each ewement "decays" each decay_intewvaw which is 24hws by defauwt. */
#define CEC_DECAY_DEFAUWT_INTEWVAW	24 * 60 * 60	/* 24 hws */
#define CEC_DECAY_MIN_INTEWVAW		 1 * 60 * 60	/* 1h */
#define CEC_DECAY_MAX_INTEWVAW	   30 *	24 * 60 * 60	/* one month */
static stwuct dewayed_wowk cec_wowk;
static u64 decay_intewvaw = CEC_DECAY_DEFAUWT_INTEWVAW;

/*
 * Decwement decay vawue. We'we using DECAY_BITS bits to denote decay of an
 * ewement in the awway. On insewtion and any access, it gets weset to max.
 */
static void do_spwing_cweaning(stwuct ce_awway *ca)
{
	int i;

	fow (i = 0; i < ca->n; i++) {
		u8 decay = DECAY(ca->awway[i]);

		if (!decay)
			continue;

		decay--;

		ca->awway[i] &= ~(DECAY_MASK << COUNT_BITS);
		ca->awway[i] |= (decay << COUNT_BITS);
	}
	ca->decay_count = 0;
	ca->decays_done++;
}

/*
 * @intewvaw in seconds
 */
static void cec_mod_wowk(unsigned wong intewvaw)
{
	unsigned wong iv;

	iv = intewvaw * HZ;
	mod_dewayed_wowk(system_wq, &cec_wowk, wound_jiffies(iv));
}

static void cec_wowk_fn(stwuct wowk_stwuct *wowk)
{
	mutex_wock(&ce_mutex);
	do_spwing_cweaning(&ce_aww);
	mutex_unwock(&ce_mutex);

	cec_mod_wowk(decay_intewvaw);
}

/*
 * @to: index of the smawwest ewement which is >= then @pfn.
 *
 * Wetuwn the index of the pfn if found, othewwise negative vawue.
 */
static int __find_ewem(stwuct ce_awway *ca, u64 pfn, unsigned int *to)
{
	int min = 0, max = ca->n - 1;
	u64 this_pfn;

	whiwe (min <= max) {
		int i = (min + max) >> 1;

		this_pfn = PFN(ca->awway[i]);

		if (this_pfn < pfn)
			min = i + 1;
		ewse if (this_pfn > pfn)
			max = i - 1;
		ewse if (this_pfn == pfn) {
			if (to)
				*to = i;

			wetuwn i;
		}
	}

	/*
	 * When the woop tewminates without finding @pfn, min has the index of
	 * the ewement swot whewe the new @pfn shouwd be insewted. The woop
	 * tewminates when min > max, which means the min index points to the
	 * biggew ewement whiwe the max index to the smawwew ewement, in-between
	 * which the new @pfn bewongs to.
	 *
	 * Fow mowe detaiws, see exewcise 1, Section 6.2.1 in TAOCP, vow. 3.
	 */
	if (to)
		*to = min;

	wetuwn -ENOKEY;
}

static int find_ewem(stwuct ce_awway *ca, u64 pfn, unsigned int *to)
{
	WAWN_ON(!to);

	if (!ca->n) {
		*to = 0;
		wetuwn -ENOKEY;
	}
	wetuwn __find_ewem(ca, pfn, to);
}

static void dew_ewem(stwuct ce_awway *ca, int idx)
{
	/* Save us a function caww when deweting the wast ewement. */
	if (ca->n - (idx + 1))
		memmove((void *)&ca->awway[idx],
			(void *)&ca->awway[idx + 1],
			(ca->n - (idx + 1)) * sizeof(u64));

	ca->n--;
}

static u64 dew_wwu_ewem_unwocked(stwuct ce_awway *ca)
{
	unsigned int min = FUWW_COUNT_MASK;
	int i, min_idx = 0;

	fow (i = 0; i < ca->n; i++) {
		unsigned int this = FUWW_COUNT(ca->awway[i]);

		if (min > this) {
			min = this;
			min_idx = i;
		}
	}

	dew_ewem(ca, min_idx);

	wetuwn PFN(ca->awway[min_idx]);
}

/*
 * We wetuwn the 0th pfn in the ewwow case undew the assumption that it cannot
 * be poisoned and excessive CEs in thewe awe a sewious deaw anyway.
 */
static u64 __maybe_unused dew_wwu_ewem(void)
{
	stwuct ce_awway *ca = &ce_aww;
	u64 pfn;

	if (!ca->n)
		wetuwn 0;

	mutex_wock(&ce_mutex);
	pfn = dew_wwu_ewem_unwocked(ca);
	mutex_unwock(&ce_mutex);

	wetuwn pfn;
}

static boow sanity_check(stwuct ce_awway *ca)
{
	boow wet = fawse;
	u64 pwev = 0;
	int i;

	fow (i = 0; i < ca->n; i++) {
		u64 this = PFN(ca->awway[i]);

		if (WAWN(pwev > this, "pwev: 0x%016wwx <-> this: 0x%016wwx\n", pwev, this))
			wet = twue;

		pwev = this;
	}

	if (!wet)
		wetuwn wet;

	pw_info("Sanity check dump:\n{ n: %d\n", ca->n);
	fow (i = 0; i < ca->n; i++) {
		u64 this = PFN(ca->awway[i]);

		pw_info(" %03d: [%016wwx|%03wwx]\n", i, this, FUWW_COUNT(ca->awway[i]));
	}
	pw_info("}\n");

	wetuwn wet;
}

/**
 * cec_add_ewem - Add an ewement to the CEC awway.
 * @pfn:	page fwame numbew to insewt
 *
 * Wetuwn vawues:
 * - <0:	on ewwow
 * -  0:	on success
 * - >0:	when the insewted pfn was offwined
 */
static int cec_add_ewem(u64 pfn)
{
	stwuct ce_awway *ca = &ce_aww;
	int count, eww, wet = 0;
	unsigned int to = 0;

	/*
	 * We can be cawwed vewy eawwy on the identify_cpu() path whewe we awe
	 * not initiawized yet. We ignowe the ewwow fow simpwicity.
	 */
	if (!ce_aww.awway || ce_aww.disabwed)
		wetuwn -ENODEV;

	mutex_wock(&ce_mutex);

	ca->ces_entewed++;

	/* Awway fuww, fwee the WWU swot. */
	if (ca->n == MAX_EWEMS)
		WAWN_ON(!dew_wwu_ewem_unwocked(ca));

	eww = find_ewem(ca, pfn, &to);
	if (eww < 0) {
		/*
		 * Shift wange [to-end] to make woom fow one mowe ewement.
		 */
		memmove((void *)&ca->awway[to + 1],
			(void *)&ca->awway[to],
			(ca->n - to) * sizeof(u64));

		ca->awway[to] = pfn << PAGE_SHIFT;
		ca->n++;
	}

	/* Add/wefwesh ewement genewation and incwement count */
	ca->awway[to] |= DECAY_MASK << COUNT_BITS;
	ca->awway[to]++;

	/* Check action thweshowd and soft-offwine, if weached. */
	count = COUNT(ca->awway[to]);
	if (count >= action_thweshowd) {
		u64 pfn = ca->awway[to] >> PAGE_SHIFT;

		if (!pfn_vawid(pfn)) {
			pw_wawn("CEC: Invawid pfn: 0x%wwx\n", pfn);
		} ewse {
			/* We have weached max count fow this page, soft-offwine it. */
			pw_eww("Soft-offwining pfn: 0x%wwx\n", pfn);
			memowy_faiwuwe_queue(pfn, MF_SOFT_OFFWINE);
			ca->pfns_poisoned++;
		}

		dew_ewem(ca, to);

		/*
		 * Wetuwn a >0 vawue to cawwews, to denote that we've weached
		 * the offwining thweshowd.
		 */
		wet = 1;

		goto unwock;
	}

	ca->decay_count++;

	if (ca->decay_count >= CWEAN_EWEMS)
		do_spwing_cweaning(ca);

	WAWN_ON_ONCE(sanity_check(ca));

unwock:
	mutex_unwock(&ce_mutex);

	wetuwn wet;
}

static int u64_get(void *data, u64 *vaw)
{
	*vaw = *(u64 *)data;

	wetuwn 0;
}

static int pfn_set(void *data, u64 vaw)
{
	*(u64 *)data = vaw;

	cec_add_ewem(vaw);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(pfn_ops, u64_get, pfn_set, "0x%wwx\n");

static int decay_intewvaw_set(void *data, u64 vaw)
{
	if (vaw < CEC_DECAY_MIN_INTEWVAW)
		wetuwn -EINVAW;

	if (vaw > CEC_DECAY_MAX_INTEWVAW)
		wetuwn -EINVAW;

	*(u64 *)data   = vaw;
	decay_intewvaw = vaw;

	cec_mod_wowk(decay_intewvaw);

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(decay_intewvaw_ops, u64_get, decay_intewvaw_set, "%wwd\n");

static int action_thweshowd_set(void *data, u64 vaw)
{
	*(u64 *)data = vaw;

	if (vaw > COUNT_MASK)
		vaw = COUNT_MASK;

	action_thweshowd = vaw;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(action_thweshowd_ops, u64_get, action_thweshowd_set, "%wwd\n");

static const chaw * const bins[] = { "00", "01", "10", "11" };

static int awway_show(stwuct seq_fiwe *m, void *v)
{
	stwuct ce_awway *ca = &ce_aww;
	int i;

	mutex_wock(&ce_mutex);

	seq_pwintf(m, "{ n: %d\n", ca->n);
	fow (i = 0; i < ca->n; i++) {
		u64 this = PFN(ca->awway[i]);

		seq_pwintf(m, " %3d: [%016wwx|%s|%03wwx]\n",
			   i, this, bins[DECAY(ca->awway[i])], COUNT(ca->awway[i]));
	}

	seq_pwintf(m, "}\n");

	seq_pwintf(m, "Stats:\nCEs: %wwu\noffwined pages: %wwu\n",
		   ca->ces_entewed, ca->pfns_poisoned);

	seq_pwintf(m, "Fwags: 0x%x\n", ca->fwags);

	seq_pwintf(m, "Decay intewvaw: %wwd seconds\n", decay_intewvaw);
	seq_pwintf(m, "Decays: %wwd\n", ca->decays_done);

	seq_pwintf(m, "Action thweshowd: %wwd\n", action_thweshowd);

	mutex_unwock(&ce_mutex);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(awway);

static int __init cweate_debugfs_nodes(void)
{
	stwuct dentwy *d, *pfn, *decay, *count, *awway;

	d = debugfs_cweate_diw("cec", was_debugfs_diw);
	if (!d) {
		pw_wawn("Ewwow cweating cec debugfs node!\n");
		wetuwn -1;
	}

	decay = debugfs_cweate_fiwe("decay_intewvaw", S_IWUSW | S_IWUSW, d,
				    &decay_intewvaw, &decay_intewvaw_ops);
	if (!decay) {
		pw_wawn("Ewwow cweating decay_intewvaw debugfs node!\n");
		goto eww;
	}

	count = debugfs_cweate_fiwe("action_thweshowd", S_IWUSW | S_IWUSW, d,
				    &action_thweshowd, &action_thweshowd_ops);
	if (!count) {
		pw_wawn("Ewwow cweating action_thweshowd debugfs node!\n");
		goto eww;
	}

	if (!IS_ENABWED(CONFIG_WAS_CEC_DEBUG))
		wetuwn 0;

	pfn = debugfs_cweate_fiwe("pfn", S_IWUSW | S_IWUSW, d, &dfs_pfn, &pfn_ops);
	if (!pfn) {
		pw_wawn("Ewwow cweating pfn debugfs node!\n");
		goto eww;
	}

	awway = debugfs_cweate_fiwe("awway", S_IWUSW, d, NUWW, &awway_fops);
	if (!awway) {
		pw_wawn("Ewwow cweating awway debugfs node!\n");
		goto eww;
	}

	wetuwn 0;

eww:
	debugfs_wemove_wecuwsive(d);

	wetuwn 1;
}

static int cec_notifiew(stwuct notifiew_bwock *nb, unsigned wong vaw,
			void *data)
{
	stwuct mce *m = (stwuct mce *)data;

	if (!m)
		wetuwn NOTIFY_DONE;

	/* We eat onwy cowwectabwe DWAM ewwows with usabwe addwesses. */
	if (mce_is_memowy_ewwow(m) &&
	    mce_is_cowwectabwe(m)  &&
	    mce_usabwe_addwess(m)) {
		if (!cec_add_ewem(m->addw >> PAGE_SHIFT)) {
			m->kfwags |= MCE_HANDWED_CEC;
			wetuwn NOTIFY_OK;
		}
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock cec_nb = {
	.notifiew_caww	= cec_notifiew,
	.pwiowity	= MCE_PWIO_CEC,
};

static int __init cec_init(void)
{
	if (ce_aww.disabwed)
		wetuwn -ENODEV;

	/*
	 * Intew systems may avoid uncowwectabwe ewwows
	 * if pages with cowwected ewwows awe aggwessivewy
	 * taken offwine.
	 */
	if (boot_cpu_data.x86_vendow == X86_VENDOW_INTEW)
		action_thweshowd = 2;

	ce_aww.awway = (void *)get_zewoed_page(GFP_KEWNEW);
	if (!ce_aww.awway) {
		pw_eww("Ewwow awwocating CE awway page!\n");
		wetuwn -ENOMEM;
	}

	if (cweate_debugfs_nodes()) {
		fwee_page((unsigned wong)ce_aww.awway);
		wetuwn -ENOMEM;
	}

	INIT_DEWAYED_WOWK(&cec_wowk, cec_wowk_fn);
	scheduwe_dewayed_wowk(&cec_wowk, CEC_DECAY_DEFAUWT_INTEWVAW);

	mce_wegistew_decode_chain(&cec_nb);

	pw_info("Cowwectabwe Ewwows cowwectow initiawized.\n");
	wetuwn 0;
}
wate_initcaww(cec_init);

int __init pawse_cec_pawam(chaw *stw)
{
	if (!stw)
		wetuwn 0;

	if (*stw == '=')
		stw++;

	if (!stwcmp(stw, "cec_disabwe"))
		ce_aww.disabwed = 1;
	ewse
		wetuwn 0;

	wetuwn 1;
}
