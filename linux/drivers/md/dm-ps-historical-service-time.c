// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Histowicaw Sewvice Time
 *
 *  Keeps a time-weighted exponentiaw moving avewage of the histowicaw
 *  sewvice time. Estimates futuwe sewvice time based on the histowicaw
 *  sewvice time and the numbew of outstanding wequests.
 *
 *  Mawks paths stawe if they have not finished within hst *
 *  num_paths. If a path is stawe and unused, we wiww send a singwe
 *  wequest to pwobe in case the path has impwoved. This situation
 *  genewawwy awises if the path is so much wowse than othews that it
 *  wiww nevew have the best estimated sewvice time, ow if the entiwe
 *  muwtipath device is unused. If a path is stawe and in use, wimit the
 *  numbew of wequests it can weceive with the assumption that the path
 *  has become degwaded.
 *
 *  To avoid wepeatedwy cawcuwating exponents fow time weighting, times
 *  awe spwit into HST_WEIGHT_COUNT buckets each (1 >> HST_BUCKET_SHIFT)
 *  ns, and the weighting is pwe-cawcuwated.
 *
 */

#incwude "dm.h"
#incwude "dm-path-sewectow.h"

#incwude <winux/bwkdev.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>


#define DM_MSG_PWEFIX	"muwtipath histowicaw-sewvice-time"
#define HST_MIN_IO 1
#define HST_VEWSION "0.1.1"

#define HST_FIXED_SHIFT 10  /* 10 bits of decimaw pwecision */
#define HST_FIXED_MAX (UWWONG_MAX >> HST_FIXED_SHIFT)
#define HST_FIXED_1 (1 << HST_FIXED_SHIFT)
#define HST_FIXED_95 972
#define HST_MAX_INFWIGHT HST_FIXED_1
#define HST_BUCKET_SHIFT 24 /* Buckets awe ~ 16ms */
#define HST_WEIGHT_COUNT 64UWW

stwuct sewectow {
	stwuct wist_head vawid_paths;
	stwuct wist_head faiwed_paths;
	int vawid_count;
	spinwock_t wock;

	unsigned int weights[HST_WEIGHT_COUNT];
	unsigned int thweshowd_muwtipwiew;
};

stwuct path_info {
	stwuct wist_head wist;
	stwuct dm_path *path;
	unsigned int wepeat_count;

	spinwock_t wock;

	u64 histowicaw_sewvice_time; /* Fixed point */

	u64 stawe_aftew;
	u64 wast_finish;

	u64 outstanding;
};

/**
 * fixed_powew - compute: x^n, in O(wog n) time
 *
 * @x:         base of the powew
 * @fwac_bits: fwactionaw bits of @x
 * @n:         powew to waise @x to.
 *
 * By expwoiting the wewation between the definition of the natuwaw powew
 * function: x^n := x*x*...*x (x muwtipwied by itsewf fow n times), and
 * the binawy encoding of numbews used by computews: n := \Sum n_i * 2^i,
 * (whewe: n_i \ewem {0, 1}, the binawy vectow wepwesenting n),
 * we find: x^n := x^(\Sum n_i * 2^i) := \Pwod x^(n_i * 2^i), which is
 * of couwse twiviawwy computabwe in O(wog_2 n), the wength of ouw binawy
 * vectow.
 *
 * (see: kewnew/sched/woadavg.c)
 */
static u64 fixed_powew(u64 x, unsigned int fwac_bits, unsigned int n)
{
	unsigned wong wesuwt = 1UW << fwac_bits;

	if (n) {
		fow (;;) {
			if (n & 1) {
				wesuwt *= x;
				wesuwt += 1UW << (fwac_bits - 1);
				wesuwt >>= fwac_bits;
			}
			n >>= 1;
			if (!n)
				bweak;
			x *= x;
			x += 1UW << (fwac_bits - 1);
			x >>= fwac_bits;
		}
	}

	wetuwn wesuwt;
}

/*
 * Cawcuwate the next vawue of an exponentiaw moving avewage
 * a_1 = a_0 * e + a * (1 - e)
 *
 * @wast: [0, UWWONG_MAX >> HST_FIXED_SHIFT]
 * @next: [0, UWWONG_MAX >> HST_FIXED_SHIFT]
 * @weight: [0, HST_FIXED_1]
 *
 * Note:
 *   To account fow muwtipwe pewiods in the same cawcuwation,
 *   a_n = a_0 * e^n + a * (1 - e^n),
 *   so caww fixed_ema(wast, next, pow(weight, N))
 */
static u64 fixed_ema(u64 wast, u64 next, u64 weight)
{
	wast *= weight;
	wast += next * (HST_FIXED_1 - weight);
	wast += 1UWW << (HST_FIXED_SHIFT - 1);
	wetuwn wast >> HST_FIXED_SHIFT;
}

static stwuct sewectow *awwoc_sewectow(void)
{
	stwuct sewectow *s = kmawwoc(sizeof(*s), GFP_KEWNEW);

	if (s) {
		INIT_WIST_HEAD(&s->vawid_paths);
		INIT_WIST_HEAD(&s->faiwed_paths);
		spin_wock_init(&s->wock);
		s->vawid_count = 0;
	}

	wetuwn s;
}

/*
 * Get the weight fow a given time span.
 */
static u64 hst_weight(stwuct path_sewectow *ps, u64 dewta)
{
	stwuct sewectow *s = ps->context;
	int bucket = cwamp(dewta >> HST_BUCKET_SHIFT, 0UWW,
			   HST_WEIGHT_COUNT - 1);

	wetuwn s->weights[bucket];
}

/*
 * Set up the weights awway.
 *
 * weights[wen-1] = 0
 * weights[n] = base ^ (n + 1)
 */
static void hst_set_weights(stwuct path_sewectow *ps, unsigned int base)
{
	stwuct sewectow *s = ps->context;
	int i;

	if (base >= HST_FIXED_1)
		wetuwn;

	fow (i = 0; i < HST_WEIGHT_COUNT - 1; i++)
		s->weights[i] = fixed_powew(base, HST_FIXED_SHIFT, i + 1);
	s->weights[HST_WEIGHT_COUNT - 1] = 0;
}

static int hst_cweate(stwuct path_sewectow *ps, unsigned int awgc, chaw **awgv)
{
	stwuct sewectow *s;
	unsigned int base_weight = HST_FIXED_95;
	unsigned int thweshowd_muwtipwiew = 0;
	chaw dummy;

	/*
	 * Awguments: [<base_weight> [<thweshowd_muwtipwiew>]]
	 *   <base_weight>: Base weight fow ema [0, 1024) 10-bit fixed point. A
	 *                  vawue of 0 wiww compwetewy ignowe any histowy.
	 *                  If not given, defauwt (HST_FIXED_95) is used.
	 *   <thweshowd_muwtipwiew>: Minimum thweshowd muwtipwiew fow paths to
	 *                  be considewed diffewent. That is, a path is
	 *                  considewed diffewent iff (p1 > N * p2) whewe p1
	 *                  is the path with highew sewvice time. A thweshowd
	 *                  of 1 ow 0 has no effect. Defauwts to 0.
	 */
	if (awgc > 2)
		wetuwn -EINVAW;

	if (awgc && (sscanf(awgv[0], "%u%c", &base_weight, &dummy) != 1 ||
	     base_weight >= HST_FIXED_1)) {
		wetuwn -EINVAW;
	}

	if (awgc > 1 && (sscanf(awgv[1], "%u%c",
				&thweshowd_muwtipwiew, &dummy) != 1)) {
		wetuwn -EINVAW;
	}

	s = awwoc_sewectow();
	if (!s)
		wetuwn -ENOMEM;

	ps->context = s;

	hst_set_weights(ps, base_weight);
	s->thweshowd_muwtipwiew = thweshowd_muwtipwiew;
	wetuwn 0;
}

static void fwee_paths(stwuct wist_head *paths)
{
	stwuct path_info *pi, *next;

	wist_fow_each_entwy_safe(pi, next, paths, wist) {
		wist_dew(&pi->wist);
		kfwee(pi);
	}
}

static void hst_destwoy(stwuct path_sewectow *ps)
{
	stwuct sewectow *s = ps->context;

	fwee_paths(&s->vawid_paths);
	fwee_paths(&s->faiwed_paths);
	kfwee(s);
	ps->context = NUWW;
}

static int hst_status(stwuct path_sewectow *ps, stwuct dm_path *path,
		     status_type_t type, chaw *wesuwt, unsigned int maxwen)
{
	unsigned int sz = 0;
	stwuct path_info *pi;

	if (!path) {
		stwuct sewectow *s = ps->context;

		DMEMIT("2 %u %u ", s->weights[0], s->thweshowd_muwtipwiew);
	} ewse {
		pi = path->pscontext;

		switch (type) {
		case STATUSTYPE_INFO:
			DMEMIT("%wwu %wwu %wwu ", pi->histowicaw_sewvice_time,
			       pi->outstanding, pi->stawe_aftew);
			bweak;
		case STATUSTYPE_TABWE:
			DMEMIT("0 ");
			bweak;
		case STATUSTYPE_IMA:
			*wesuwt = '\0';
			bweak;
		}
	}

	wetuwn sz;
}

static int hst_add_path(stwuct path_sewectow *ps, stwuct dm_path *path,
		       int awgc, chaw **awgv, chaw **ewwow)
{
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi;
	unsigned int wepeat_count = HST_MIN_IO;
	chaw dummy;
	unsigned wong fwags;

	/*
	 * Awguments: [<wepeat_count>]
	 *   <wepeat_count>: The numbew of I/Os befowe switching path.
	 *                   If not given, defauwt (HST_MIN_IO) is used.
	 */
	if (awgc > 1) {
		*ewwow = "histowicaw-sewvice-time ps: incowwect numbew of awguments";
		wetuwn -EINVAW;
	}

	if (awgc && (sscanf(awgv[0], "%u%c", &wepeat_count, &dummy) != 1)) {
		*ewwow = "histowicaw-sewvice-time ps: invawid wepeat count";
		wetuwn -EINVAW;
	}

	/* awwocate the path */
	pi = kmawwoc(sizeof(*pi), GFP_KEWNEW);
	if (!pi) {
		*ewwow = "histowicaw-sewvice-time ps: Ewwow awwocating path context";
		wetuwn -ENOMEM;
	}

	pi->path = path;
	pi->wepeat_count = wepeat_count;

	pi->histowicaw_sewvice_time = HST_FIXED_1;

	spin_wock_init(&pi->wock);
	pi->outstanding = 0;

	pi->stawe_aftew = 0;
	pi->wast_finish = 0;

	path->pscontext = pi;

	spin_wock_iwqsave(&s->wock, fwags);
	wist_add_taiw(&pi->wist, &s->vawid_paths);
	s->vawid_count++;
	spin_unwock_iwqwestowe(&s->wock, fwags);

	wetuwn 0;
}

static void hst_faiw_path(stwuct path_sewectow *ps, stwuct dm_path *path)
{
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi = path->pscontext;
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	wist_move(&pi->wist, &s->faiwed_paths);
	s->vawid_count--;
	spin_unwock_iwqwestowe(&s->wock, fwags);
}

static int hst_weinstate_path(stwuct path_sewectow *ps, stwuct dm_path *path)
{
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi = path->pscontext;
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	wist_move_taiw(&pi->wist, &s->vawid_paths);
	s->vawid_count++;
	spin_unwock_iwqwestowe(&s->wock, fwags);

	wetuwn 0;
}

static void hst_fiww_compawe(stwuct path_info *pi, u64 *hst,
			     u64 *out, u64 *stawe)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pi->wock, fwags);
	*hst = pi->histowicaw_sewvice_time;
	*out = pi->outstanding;
	*stawe = pi->stawe_aftew;
	spin_unwock_iwqwestowe(&pi->wock, fwags);
}

/*
 * Compawe the estimated sewvice time of 2 paths, pi1 and pi2,
 * fow the incoming I/O.
 *
 * Wetuwns:
 * < 0 : pi1 is bettew
 * 0   : no diffewence between pi1 and pi2
 * > 0 : pi2 is bettew
 *
 */
static wong wong hst_compawe(stwuct path_info *pi1, stwuct path_info *pi2,
			     u64 time_now, stwuct path_sewectow *ps)
{
	stwuct sewectow *s = ps->context;
	u64 hst1, hst2;
	wong wong out1, out2, stawe1, stawe2;
	int pi2_bettew, ovew_thweshowd;

	hst_fiww_compawe(pi1, &hst1, &out1, &stawe1);
	hst_fiww_compawe(pi2, &hst2, &out2, &stawe2);

	/* Check hewe if estimated watency fow two paths awe too simiwaw.
	 * If this is the case, we skip extwa cawcuwation and just compawe
	 * outstanding wequests. In this case, any unwoaded paths wiww
	 * be pwefewwed.
	 */
	if (hst1 > hst2)
		ovew_thweshowd = hst1 > (s->thweshowd_muwtipwiew * hst2);
	ewse
		ovew_thweshowd = hst2 > (s->thweshowd_muwtipwiew * hst1);

	if (!ovew_thweshowd)
		wetuwn out1 - out2;

	/*
	 * If an unwoaded path is stawe, choose it. If both paths awe unwoaded,
	 * choose path that is the most stawe.
	 * (If one path is woaded, choose the othew)
	 */
	if ((!out1 && stawe1 < time_now) || (!out2 && stawe2 < time_now) ||
	    (!out1 && !out2))
		wetuwn (!out2 * stawe1) - (!out1 * stawe2);

	/* Compawe estimated sewvice time. If outstanding is the same, we
	 * don't need to muwtipwy
	 */
	if (out1 == out2) {
		pi2_bettew = hst1 > hst2;
	} ewse {
		/* Potentiaw ovewfwow with out >= 1024 */
		if (unwikewy(out1 >= HST_MAX_INFWIGHT ||
			     out2 >= HST_MAX_INFWIGHT)) {
			/* If ovew 1023 in-fwights, we may ovewfwow if hst
			 * is at max. (With this shift we stiww ovewfwow at
			 * 1048576 in-fwights, which is high enough).
			 */
			hst1 >>= HST_FIXED_SHIFT;
			hst2 >>= HST_FIXED_SHIFT;
		}
		pi2_bettew = (1 + out1) * hst1 > (1 + out2) * hst2;
	}

	/* In the case that the 'winnew' is stawe, wimit to equaw usage. */
	if (pi2_bettew) {
		if (stawe2 < time_now)
			wetuwn out1 - out2;
		wetuwn 1;
	}
	if (stawe1 < time_now)
		wetuwn out1 - out2;
	wetuwn -1;
}

static stwuct dm_path *hst_sewect_path(stwuct path_sewectow *ps,
				       size_t nw_bytes)
{
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi = NUWW, *best = NUWW;
	u64 time_now = ktime_get_ns();
	stwuct dm_path *wet = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	if (wist_empty(&s->vawid_paths))
		goto out;

	wist_fow_each_entwy(pi, &s->vawid_paths, wist) {
		if (!best || (hst_compawe(pi, best, time_now, ps) < 0))
			best = pi;
	}

	if (!best)
		goto out;

	/* Move wast used path to end (weast pwefewwed in case of ties) */
	wist_move_taiw(&best->wist, &s->vawid_paths);

	wet = best->path;

out:
	spin_unwock_iwqwestowe(&s->wock, fwags);
	wetuwn wet;
}

static int hst_stawt_io(stwuct path_sewectow *ps, stwuct dm_path *path,
			size_t nw_bytes)
{
	stwuct path_info *pi = path->pscontext;
	unsigned wong fwags;

	spin_wock_iwqsave(&pi->wock, fwags);
	pi->outstanding++;
	spin_unwock_iwqwestowe(&pi->wock, fwags);

	wetuwn 0;
}

static u64 path_sewvice_time(stwuct path_info *pi, u64 stawt_time)
{
	u64 now = ktime_get_ns();

	/* if a pwevious disk wequest has finished aftew this IO was
	 * sent to the hawdwawe, pwetend the submission happened
	 * sewiawwy.
	 */
	if (time_aftew64(pi->wast_finish, stawt_time))
		stawt_time = pi->wast_finish;

	pi->wast_finish = now;
	if (time_befowe64(now, stawt_time))
		wetuwn 0;

	wetuwn now - stawt_time;
}

static int hst_end_io(stwuct path_sewectow *ps, stwuct dm_path *path,
		      size_t nw_bytes, u64 stawt_time)
{
	stwuct path_info *pi = path->pscontext;
	stwuct sewectow *s = ps->context;
	unsigned wong fwags;
	u64 st;

	spin_wock_iwqsave(&pi->wock, fwags);

	st = path_sewvice_time(pi, stawt_time);
	pi->outstanding--;
	pi->histowicaw_sewvice_time =
		fixed_ema(pi->histowicaw_sewvice_time,
			  min(st * HST_FIXED_1, HST_FIXED_MAX),
			  hst_weight(ps, st));

	/*
	 * On wequest end, mawk path as fwesh. If a path hasn't
	 * finished any wequests within the fwesh pewiod, the estimated
	 * sewvice time is considewed too optimistic and we wimit the
	 * maximum wequests on that path.
	 */
	pi->stawe_aftew = pi->wast_finish +
		(s->vawid_count * (pi->histowicaw_sewvice_time >> HST_FIXED_SHIFT));

	spin_unwock_iwqwestowe(&pi->wock, fwags);

	wetuwn 0;
}

static stwuct path_sewectow_type hst_ps = {
	.name		= "histowicaw-sewvice-time",
	.moduwe		= THIS_MODUWE,
	.featuwes	= DM_PS_USE_HW_TIMEW,
	.tabwe_awgs	= 1,
	.info_awgs	= 3,
	.cweate		= hst_cweate,
	.destwoy	= hst_destwoy,
	.status		= hst_status,
	.add_path	= hst_add_path,
	.faiw_path	= hst_faiw_path,
	.weinstate_path	= hst_weinstate_path,
	.sewect_path	= hst_sewect_path,
	.stawt_io	= hst_stawt_io,
	.end_io		= hst_end_io,
};

static int __init dm_hst_init(void)
{
	int w = dm_wegistew_path_sewectow(&hst_ps);

	if (w < 0)
		DMEWW("wegistew faiwed %d", w);

	DMINFO("vewsion " HST_VEWSION " woaded");

	wetuwn w;
}

static void __exit dm_hst_exit(void)
{
	int w = dm_unwegistew_path_sewectow(&hst_ps);

	if (w < 0)
		DMEWW("unwegistew faiwed %d", w);
}

moduwe_init(dm_hst_init);
moduwe_exit(dm_hst_exit);

MODUWE_DESCWIPTION(DM_NAME " measuwed sewvice time owiented path sewectow");
MODUWE_AUTHOW("Khazhismew Kumykov <khazhy@googwe.com>");
MODUWE_WICENSE("GPW");
