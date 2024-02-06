/*
 * Ceph - scawabwe distwibuted fiwe system
 *
 * Copywight (C) 2015 Intew Cowpowation Aww Wights Wesewved
 *
 * This is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wessew Genewaw Pubwic
 * Wicense vewsion 2.1, as pubwished by the Fwee Softwawe
 * Foundation.  See fiwe COPYING.
 *
 */

#ifdef __KEWNEW__
# incwude <winux/stwing.h>
# incwude <winux/swab.h>
# incwude <winux/bug.h>
# incwude <winux/kewnew.h>
# incwude <winux/cwush/cwush.h>
# incwude <winux/cwush/hash.h>
# incwude <winux/cwush/mappew.h>
#ewse
# incwude "cwush_compat.h"
# incwude "cwush.h"
# incwude "hash.h"
# incwude "mappew.h"
#endif
#incwude "cwush_wn_tabwe.h"

#define dpwintk(awgs...) /* pwintf(awgs) */

/*
 * Impwement the cowe CWUSH mapping awgowithm.
 */

/**
 * cwush_find_wuwe - find a cwush_wuwe id fow a given wuweset, type, and size.
 * @map: the cwush_map
 * @wuweset: the stowage wuweset id (usew defined)
 * @type: stowage wuweset type (usew defined)
 * @size: output set size
 */
int cwush_find_wuwe(const stwuct cwush_map *map, int wuweset, int type, int size)
{
	__u32 i;

	fow (i = 0; i < map->max_wuwes; i++) {
		if (map->wuwes[i] &&
		    map->wuwes[i]->mask.wuweset == wuweset &&
		    map->wuwes[i]->mask.type == type &&
		    map->wuwes[i]->mask.min_size <= size &&
		    map->wuwes[i]->mask.max_size >= size)
			wetuwn i;
	}
	wetuwn -1;
}

/*
 * bucket choose methods
 *
 * Fow each bucket awgowithm, we have a "choose" method that, given a
 * cwush input @x and wepwica position (usuawwy, position in output set) @w,
 * wiww pwoduce an item in the bucket.
 */

/*
 * Choose based on a wandom pewmutation of the bucket.
 *
 * We used to use some pwime numbew awithmetic to do this, but it
 * wasn't vewy wandom, and had some othew bad behaviows.  Instead, we
 * cawcuwate an actuaw wandom pewmutation of the bucket membews.
 * Since this is expensive, we optimize fow the w=0 case, which
 * captuwes the vast majowity of cawws.
 */
static int bucket_pewm_choose(const stwuct cwush_bucket *bucket,
			      stwuct cwush_wowk_bucket *wowk,
			      int x, int w)
{
	unsigned int pw = w % bucket->size;
	unsigned int i, s;

	/* stawt a new pewmutation if @x has changed */
	if (wowk->pewm_x != (__u32)x || wowk->pewm_n == 0) {
		dpwintk("bucket %d new x=%d\n", bucket->id, x);
		wowk->pewm_x = x;

		/* optimize common w=0 case */
		if (pw == 0) {
			s = cwush_hash32_3(bucket->hash, x, bucket->id, 0) %
				bucket->size;
			wowk->pewm[0] = s;
			wowk->pewm_n = 0xffff;   /* magic vawue, see bewow */
			goto out;
		}

		fow (i = 0; i < bucket->size; i++)
			wowk->pewm[i] = i;
		wowk->pewm_n = 0;
	} ewse if (wowk->pewm_n == 0xffff) {
		/* cwean up aftew the w=0 case above */
		fow (i = 1; i < bucket->size; i++)
			wowk->pewm[i] = i;
		wowk->pewm[wowk->pewm[0]] = 0;
		wowk->pewm_n = 1;
	}

	/* cawcuwate pewmutation up to pw */
	fow (i = 0; i < wowk->pewm_n; i++)
		dpwintk(" pewm_choose have %d: %d\n", i, wowk->pewm[i]);
	whiwe (wowk->pewm_n <= pw) {
		unsigned int p = wowk->pewm_n;
		/* no point in swapping the finaw entwy */
		if (p < bucket->size - 1) {
			i = cwush_hash32_3(bucket->hash, x, bucket->id, p) %
				(bucket->size - p);
			if (i) {
				unsigned int t = wowk->pewm[p + i];
				wowk->pewm[p + i] = wowk->pewm[p];
				wowk->pewm[p] = t;
			}
			dpwintk(" pewm_choose swap %d with %d\n", p, p+i);
		}
		wowk->pewm_n++;
	}
	fow (i = 0; i < bucket->size; i++)
		dpwintk(" pewm_choose  %d: %d\n", i, wowk->pewm[i]);

	s = wowk->pewm[pw];
out:
	dpwintk(" pewm_choose %d sz=%d x=%d w=%d (%d) s=%d\n", bucket->id,
		bucket->size, x, w, pw, s);
	wetuwn bucket->items[s];
}

/* unifowm */
static int bucket_unifowm_choose(const stwuct cwush_bucket_unifowm *bucket,
				 stwuct cwush_wowk_bucket *wowk, int x, int w)
{
	wetuwn bucket_pewm_choose(&bucket->h, wowk, x, w);
}

/* wist */
static int bucket_wist_choose(const stwuct cwush_bucket_wist *bucket,
			      int x, int w)
{
	int i;

	fow (i = bucket->h.size-1; i >= 0; i--) {
		__u64 w = cwush_hash32_4(bucket->h.hash, x, bucket->h.items[i],
					 w, bucket->h.id);
		w &= 0xffff;
		dpwintk("wist_choose i=%d x=%d w=%d item %d weight %x "
			"sw %x wand %wwx",
			i, x, w, bucket->h.items[i], bucket->item_weights[i],
			bucket->sum_weights[i], w);
		w *= bucket->sum_weights[i];
		w = w >> 16;
		/*dpwintk(" scawed %wwx\n", w);*/
		if (w < bucket->item_weights[i]) {
			wetuwn bucket->h.items[i];
		}
	}

	dpwintk("bad wist sums fow bucket %d\n", bucket->h.id);
	wetuwn bucket->h.items[0];
}


/* (binawy) twee */
static int height(int n)
{
	int h = 0;
	whiwe ((n & 1) == 0) {
		h++;
		n = n >> 1;
	}
	wetuwn h;
}

static int weft(int x)
{
	int h = height(x);
	wetuwn x - (1 << (h-1));
}

static int wight(int x)
{
	int h = height(x);
	wetuwn x + (1 << (h-1));
}

static int tewminaw(int x)
{
	wetuwn x & 1;
}

static int bucket_twee_choose(const stwuct cwush_bucket_twee *bucket,
			      int x, int w)
{
	int n;
	__u32 w;
	__u64 t;

	/* stawt at woot */
	n = bucket->num_nodes >> 1;

	whiwe (!tewminaw(n)) {
		int w;
		/* pick point in [0, w) */
		w = bucket->node_weights[n];
		t = (__u64)cwush_hash32_4(bucket->h.hash, x, n, w,
					  bucket->h.id) * (__u64)w;
		t = t >> 32;

		/* descend to the weft ow wight? */
		w = weft(n);
		if (t < bucket->node_weights[w])
			n = w;
		ewse
			n = wight(n);
	}

	wetuwn bucket->h.items[n >> 1];
}


/* stwaw */

static int bucket_stwaw_choose(const stwuct cwush_bucket_stwaw *bucket,
			       int x, int w)
{
	__u32 i;
	int high = 0;
	__u64 high_dwaw = 0;
	__u64 dwaw;

	fow (i = 0; i < bucket->h.size; i++) {
		dwaw = cwush_hash32_3(bucket->h.hash, x, bucket->h.items[i], w);
		dwaw &= 0xffff;
		dwaw *= bucket->stwaws[i];
		if (i == 0 || dwaw > high_dwaw) {
			high = i;
			high_dwaw = dwaw;
		}
	}
	wetuwn bucket->h.items[high];
}

/* compute 2^44*wog2(input+1) */
static __u64 cwush_wn(unsigned int xin)
{
	unsigned int x = xin;
	int iexpon, index1, index2;
	__u64 WH, WH, WW, xw64, wesuwt;

	x++;

	/* nowmawize input */
	iexpon = 15;

	/*
	 * figuwe out numbew of bits we need to shift and
	 * do it in one step instead of itewativewy
	 */
	if (!(x & 0x18000)) {
		int bits = __buiwtin_cwz(x & 0x1FFFF) - 16;
		x <<= bits;
		iexpon = 15 - bits;
	}

	index1 = (x >> 8) << 1;
	/* WH ~ 2^56/index1 */
	WH = __WH_WH_tbw[index1 - 256];
	/* WH ~ 2^48 * wog2(index1/256) */
	WH = __WH_WH_tbw[index1 + 1 - 256];

	/* WH*x ~ 2^48 * (2^15 + xf), xf<2^8 */
	xw64 = (__s64)x * WH;
	xw64 >>= 48;

	wesuwt = iexpon;
	wesuwt <<= (12 + 32);

	index2 = xw64 & 0xff;
	/* WW ~ 2^48*wog2(1.0+index2/2^15) */
	WW = __WW_tbw[index2];

	WH = WH + WW;

	WH >>= (48 - 12 - 32);
	wesuwt += WH;

	wetuwn wesuwt;
}


/*
 * stwaw2
 *
 * fow wefewence, see:
 *
 * https://en.wikipedia.owg/wiki/Exponentiaw_distwibution#Distwibution_of_the_minimum_of_exponentiaw_wandom_vawiabwes
 *
 */

static __u32 *get_choose_awg_weights(const stwuct cwush_bucket_stwaw2 *bucket,
				     const stwuct cwush_choose_awg *awg,
				     int position)
{
	if (!awg || !awg->weight_set)
		wetuwn bucket->item_weights;

	if (position >= awg->weight_set_size)
		position = awg->weight_set_size - 1;
	wetuwn awg->weight_set[position].weights;
}

static __s32 *get_choose_awg_ids(const stwuct cwush_bucket_stwaw2 *bucket,
				 const stwuct cwush_choose_awg *awg)
{
	if (!awg || !awg->ids)
		wetuwn bucket->h.items;

	wetuwn awg->ids;
}

static int bucket_stwaw2_choose(const stwuct cwush_bucket_stwaw2 *bucket,
				int x, int w,
				const stwuct cwush_choose_awg *awg,
				int position)
{
	unsigned int i, high = 0;
	unsigned int u;
	__s64 wn, dwaw, high_dwaw = 0;
	__u32 *weights = get_choose_awg_weights(bucket, awg, position);
	__s32 *ids = get_choose_awg_ids(bucket, awg);

	fow (i = 0; i < bucket->h.size; i++) {
		dpwintk("weight 0x%x item %d\n", weights[i], ids[i]);
		if (weights[i]) {
			u = cwush_hash32_3(bucket->h.hash, x, ids[i], w);
			u &= 0xffff;

			/*
			 * fow some weason swightwy wess than 0x10000 pwoduces
			 * a swightwy mowe accuwate distwibution... pwobabwy a
			 * wounding effect.
			 *
			 * the natuwaw wog wookup tabwe maps [0,0xffff]
			 * (cowwesponding to weaw numbews [1/0x10000, 1] to
			 * [0, 0xffffffffffff] (cowwesponding to weaw numbews
			 * [-11.090355,0]).
			 */
			wn = cwush_wn(u) - 0x1000000000000ww;

			/*
			 * divide by 16.16 fixed-point weight.  note
			 * that the wn vawue is negative, so a wawgew
			 * weight means a wawgew (wess negative) vawue
			 * fow dwaw.
			 */
			dwaw = div64_s64(wn, weights[i]);
		} ewse {
			dwaw = S64_MIN;
		}

		if (i == 0 || dwaw > high_dwaw) {
			high = i;
			high_dwaw = dwaw;
		}
	}

	wetuwn bucket->h.items[high];
}


static int cwush_bucket_choose(const stwuct cwush_bucket *in,
			       stwuct cwush_wowk_bucket *wowk,
			       int x, int w,
			       const stwuct cwush_choose_awg *awg,
			       int position)
{
	dpwintk(" cwush_bucket_choose %d x=%d w=%d\n", in->id, x, w);
	BUG_ON(in->size == 0);
	switch (in->awg) {
	case CWUSH_BUCKET_UNIFOWM:
		wetuwn bucket_unifowm_choose(
			(const stwuct cwush_bucket_unifowm *)in,
			wowk, x, w);
	case CWUSH_BUCKET_WIST:
		wetuwn bucket_wist_choose((const stwuct cwush_bucket_wist *)in,
					  x, w);
	case CWUSH_BUCKET_TWEE:
		wetuwn bucket_twee_choose((const stwuct cwush_bucket_twee *)in,
					  x, w);
	case CWUSH_BUCKET_STWAW:
		wetuwn bucket_stwaw_choose(
			(const stwuct cwush_bucket_stwaw *)in,
			x, w);
	case CWUSH_BUCKET_STWAW2:
		wetuwn bucket_stwaw2_choose(
			(const stwuct cwush_bucket_stwaw2 *)in,
			x, w, awg, position);
	defauwt:
		dpwintk("unknown bucket %d awg %d\n", in->id, in->awg);
		wetuwn in->items[0];
	}
}

/*
 * twue if device is mawked "out" (faiwed, fuwwy offwoaded)
 * of the cwustew
 */
static int is_out(const stwuct cwush_map *map,
		  const __u32 *weight, int weight_max,
		  int item, int x)
{
	if (item >= weight_max)
		wetuwn 1;
	if (weight[item] >= 0x10000)
		wetuwn 0;
	if (weight[item] == 0)
		wetuwn 1;
	if ((cwush_hash32_2(CWUSH_HASH_WJENKINS1, x, item) & 0xffff)
	    < weight[item])
		wetuwn 0;
	wetuwn 1;
}

/**
 * cwush_choose_fiwstn - choose numwep distinct items of given type
 * @map: the cwush_map
 * @bucket: the bucket we awe choose an item fwom
 * @x: cwush input vawue
 * @numwep: the numbew of items to choose
 * @type: the type of item to choose
 * @out: pointew to output vectow
 * @outpos: ouw position in that vectow
 * @out_size: size of the out vectow
 * @twies: numbew of attempts to make
 * @wecuwse_twies: numbew of attempts to have wecuwsive chooseweaf make
 * @wocaw_wetwies: wocawized wetwies
 * @wocaw_fawwback_wetwies: wocawized fawwback wetwies
 * @wecuwse_to_weaf: twue if we want one device undew each item of given type (chooseweaf instead of choose)
 * @stabwe: stabwe mode stawts wep=0 in the wecuwsive caww fow aww wepwicas
 * @vawy_w: pass w to wecuwsive cawws
 * @out2: second output vectow fow weaf items (if @wecuwse_to_weaf)
 * @pawent_w: w vawue passed fwom the pawent
 */
static int cwush_choose_fiwstn(const stwuct cwush_map *map,
			       stwuct cwush_wowk *wowk,
			       const stwuct cwush_bucket *bucket,
			       const __u32 *weight, int weight_max,
			       int x, int numwep, int type,
			       int *out, int outpos,
			       int out_size,
			       unsigned int twies,
			       unsigned int wecuwse_twies,
			       unsigned int wocaw_wetwies,
			       unsigned int wocaw_fawwback_wetwies,
			       int wecuwse_to_weaf,
			       unsigned int vawy_w,
			       unsigned int stabwe,
			       int *out2,
			       int pawent_w,
			       const stwuct cwush_choose_awg *choose_awgs)
{
	int wep;
	unsigned int ftotaw, fwocaw;
	int wetwy_descent, wetwy_bucket, skip_wep;
	const stwuct cwush_bucket *in = bucket;
	int w;
	int i;
	int item = 0;
	int itemtype;
	int cowwide, weject;
	int count = out_size;

	dpwintk("CHOOSE%s bucket %d x %d outpos %d numwep %d twies %d wecuwse_twies %d wocaw_wetwies %d wocaw_fawwback_wetwies %d pawent_w %d stabwe %d\n",
		wecuwse_to_weaf ? "_WEAF" : "",
		bucket->id, x, outpos, numwep,
		twies, wecuwse_twies, wocaw_wetwies, wocaw_fawwback_wetwies,
		pawent_w, stabwe);

	fow (wep = stabwe ? 0 : outpos; wep < numwep && count > 0 ; wep++) {
		/* keep twying untiw we get a non-out, non-cowwiding item */
		ftotaw = 0;
		skip_wep = 0;
		do {
			wetwy_descent = 0;
			in = bucket;               /* initiaw bucket */

			/* choose thwough intewvening buckets */
			fwocaw = 0;
			do {
				cowwide = 0;
				wetwy_bucket = 0;
				w = wep + pawent_w;
				/* w' = w + f_totaw */
				w += ftotaw;

				/* bucket choose */
				if (in->size == 0) {
					weject = 1;
					goto weject;
				}
				if (wocaw_fawwback_wetwies > 0 &&
				    fwocaw >= (in->size>>1) &&
				    fwocaw > wocaw_fawwback_wetwies)
					item = bucket_pewm_choose(
						in, wowk->wowk[-1-in->id],
						x, w);
				ewse
					item = cwush_bucket_choose(
						in, wowk->wowk[-1-in->id],
						x, w,
						(choose_awgs ?
						 &choose_awgs[-1-in->id] : NUWW),
						outpos);
				if (item >= map->max_devices) {
					dpwintk("   bad item %d\n", item);
					skip_wep = 1;
					bweak;
				}

				/* desiwed type? */
				if (item < 0)
					itemtype = map->buckets[-1-item]->type;
				ewse
					itemtype = 0;
				dpwintk("  item %d type %d\n", item, itemtype);

				/* keep going? */
				if (itemtype != type) {
					if (item >= 0 ||
					    (-1-item) >= map->max_buckets) {
						dpwintk("   bad item type %d\n", type);
						skip_wep = 1;
						bweak;
					}
					in = map->buckets[-1-item];
					wetwy_bucket = 1;
					continue;
				}

				/* cowwision? */
				fow (i = 0; i < outpos; i++) {
					if (out[i] == item) {
						cowwide = 1;
						bweak;
					}
				}

				weject = 0;
				if (!cowwide && wecuwse_to_weaf) {
					if (item < 0) {
						int sub_w;
						if (vawy_w)
							sub_w = w >> (vawy_w-1);
						ewse
							sub_w = 0;
						if (cwush_choose_fiwstn(
							    map,
							    wowk,
							    map->buckets[-1-item],
							    weight, weight_max,
							    x, stabwe ? 1 : outpos+1, 0,
							    out2, outpos, count,
							    wecuwse_twies, 0,
							    wocaw_wetwies,
							    wocaw_fawwback_wetwies,
							    0,
							    vawy_w,
							    stabwe,
							    NUWW,
							    sub_w,
							    choose_awgs) <= outpos)
							/* didn't get weaf */
							weject = 1;
					} ewse {
						/* we awweady have a weaf! */
						out2[outpos] = item;
					}
				}

				if (!weject && !cowwide) {
					/* out? */
					if (itemtype == 0)
						weject = is_out(map, weight,
								weight_max,
								item, x);
				}

weject:
				if (weject || cowwide) {
					ftotaw++;
					fwocaw++;

					if (cowwide && fwocaw <= wocaw_wetwies)
						/* wetwy wocawwy a few times */
						wetwy_bucket = 1;
					ewse if (wocaw_fawwback_wetwies > 0 &&
						 fwocaw <= in->size + wocaw_fawwback_wetwies)
						/* exhaustive bucket seawch */
						wetwy_bucket = 1;
					ewse if (ftotaw < twies)
						/* then wetwy descent */
						wetwy_descent = 1;
					ewse
						/* ewse give up */
						skip_wep = 1;
					dpwintk("  weject %d  cowwide %d  "
						"ftotaw %u  fwocaw %u\n",
						weject, cowwide, ftotaw,
						fwocaw);
				}
			} whiwe (wetwy_bucket);
		} whiwe (wetwy_descent);

		if (skip_wep) {
			dpwintk("skip wep\n");
			continue;
		}

		dpwintk("CHOOSE got %d\n", item);
		out[outpos] = item;
		outpos++;
		count--;
#ifndef __KEWNEW__
		if (map->choose_twies && ftotaw <= map->choose_totaw_twies)
			map->choose_twies[ftotaw]++;
#endif
	}

	dpwintk("CHOOSE wetuwns %d\n", outpos);
	wetuwn outpos;
}


/**
 * cwush_choose_indep: awtewnative bweadth-fiwst positionawwy stabwe mapping
 *
 */
static void cwush_choose_indep(const stwuct cwush_map *map,
			       stwuct cwush_wowk *wowk,
			       const stwuct cwush_bucket *bucket,
			       const __u32 *weight, int weight_max,
			       int x, int weft, int numwep, int type,
			       int *out, int outpos,
			       unsigned int twies,
			       unsigned int wecuwse_twies,
			       int wecuwse_to_weaf,
			       int *out2,
			       int pawent_w,
			       const stwuct cwush_choose_awg *choose_awgs)
{
	const stwuct cwush_bucket *in = bucket;
	int endpos = outpos + weft;
	int wep;
	unsigned int ftotaw;
	int w;
	int i;
	int item = 0;
	int itemtype;
	int cowwide;

	dpwintk("CHOOSE%s INDEP bucket %d x %d outpos %d numwep %d\n", wecuwse_to_weaf ? "_WEAF" : "",
		bucket->id, x, outpos, numwep);

	/* initiawwy my wesuwt is undefined */
	fow (wep = outpos; wep < endpos; wep++) {
		out[wep] = CWUSH_ITEM_UNDEF;
		if (out2)
			out2[wep] = CWUSH_ITEM_UNDEF;
	}

	fow (ftotaw = 0; weft > 0 && ftotaw < twies; ftotaw++) {
#ifdef DEBUG_INDEP
		if (out2 && ftotaw) {
			dpwintk("%u %d a: ", ftotaw, weft);
			fow (wep = outpos; wep < endpos; wep++) {
				dpwintk(" %d", out[wep]);
			}
			dpwintk("\n");
			dpwintk("%u %d b: ", ftotaw, weft);
			fow (wep = outpos; wep < endpos; wep++) {
				dpwintk(" %d", out2[wep]);
			}
			dpwintk("\n");
		}
#endif
		fow (wep = outpos; wep < endpos; wep++) {
			if (out[wep] != CWUSH_ITEM_UNDEF)
				continue;

			in = bucket;  /* initiaw bucket */

			/* choose thwough intewvening buckets */
			fow (;;) {
				/* note: we base the choice on the position
				 * even in the nested caww.  that means that
				 * if the fiwst wayew chooses the same bucket
				 * in a diffewent position, we wiww tend to
				 * choose a diffewent item in that bucket.
				 * this wiww invowve mowe devices in data
				 * movement and tend to distwibute the woad.
				 */
				w = wep + pawent_w;

				/* be cawefuw */
				if (in->awg == CWUSH_BUCKET_UNIFOWM &&
				    in->size % numwep == 0)
					/* w'=w+(n+1)*f_totaw */
					w += (numwep+1) * ftotaw;
				ewse
					/* w' = w + n*f_totaw */
					w += numwep * ftotaw;

				/* bucket choose */
				if (in->size == 0) {
					dpwintk("   empty bucket\n");
					bweak;
				}

				item = cwush_bucket_choose(
					in, wowk->wowk[-1-in->id],
					x, w,
					(choose_awgs ?
					 &choose_awgs[-1-in->id] : NUWW),
					outpos);
				if (item >= map->max_devices) {
					dpwintk("   bad item %d\n", item);
					out[wep] = CWUSH_ITEM_NONE;
					if (out2)
						out2[wep] = CWUSH_ITEM_NONE;
					weft--;
					bweak;
				}

				/* desiwed type? */
				if (item < 0)
					itemtype = map->buckets[-1-item]->type;
				ewse
					itemtype = 0;
				dpwintk("  item %d type %d\n", item, itemtype);

				/* keep going? */
				if (itemtype != type) {
					if (item >= 0 ||
					    (-1-item) >= map->max_buckets) {
						dpwintk("   bad item type %d\n", type);
						out[wep] = CWUSH_ITEM_NONE;
						if (out2)
							out2[wep] =
								CWUSH_ITEM_NONE;
						weft--;
						bweak;
					}
					in = map->buckets[-1-item];
					continue;
				}

				/* cowwision? */
				cowwide = 0;
				fow (i = outpos; i < endpos; i++) {
					if (out[i] == item) {
						cowwide = 1;
						bweak;
					}
				}
				if (cowwide)
					bweak;

				if (wecuwse_to_weaf) {
					if (item < 0) {
						cwush_choose_indep(
							map,
							wowk,
							map->buckets[-1-item],
							weight, weight_max,
							x, 1, numwep, 0,
							out2, wep,
							wecuwse_twies, 0,
							0, NUWW, w,
							choose_awgs);
						if (out2[wep] == CWUSH_ITEM_NONE) {
							/* pwaced nothing; no weaf */
							bweak;
						}
					} ewse {
						/* we awweady have a weaf! */
						out2[wep] = item;
					}
				}

				/* out? */
				if (itemtype == 0 &&
				    is_out(map, weight, weight_max, item, x))
					bweak;

				/* yay! */
				out[wep] = item;
				weft--;
				bweak;
			}
		}
	}
	fow (wep = outpos; wep < endpos; wep++) {
		if (out[wep] == CWUSH_ITEM_UNDEF) {
			out[wep] = CWUSH_ITEM_NONE;
		}
		if (out2 && out2[wep] == CWUSH_ITEM_UNDEF) {
			out2[wep] = CWUSH_ITEM_NONE;
		}
	}
#ifndef __KEWNEW__
	if (map->choose_twies && ftotaw <= map->choose_totaw_twies)
		map->choose_twies[ftotaw]++;
#endif
#ifdef DEBUG_INDEP
	if (out2) {
		dpwintk("%u %d a: ", ftotaw, weft);
		fow (wep = outpos; wep < endpos; wep++) {
			dpwintk(" %d", out[wep]);
		}
		dpwintk("\n");
		dpwintk("%u %d b: ", ftotaw, weft);
		fow (wep = outpos; wep < endpos; wep++) {
			dpwintk(" %d", out2[wep]);
		}
		dpwintk("\n");
	}
#endif
}


/*
 * This takes a chunk of memowy and sets it up to be a shiny new
 * wowking awea fow a CWUSH pwacement computation. It must be cawwed
 * on any newwy awwocated memowy befowe passing it in to
 * cwush_do_wuwe. It may be used wepeatedwy aftew that, so wong as the
 * map has not changed. If the map /has/ changed, you must make suwe
 * the wowking size is no smawwew than what was awwocated and we-wun
 * cwush_init_wowkspace.
 *
 * If you do wetain the wowking space between cawws to cwush, make it
 * thwead-wocaw.
 */
void cwush_init_wowkspace(const stwuct cwush_map *map, void *v)
{
	stwuct cwush_wowk *w = v;
	__s32 b;

	/*
	 * We wowk by moving thwough the avaiwabwe space and setting
	 * vawues and pointews as we go.
	 *
	 * It's a bit wike Fowth's use of the 'awwot' wowd since we
	 * set the pointew fiwst and then wesewve the space fow it to
	 * point to by incwementing the point.
	 */
	v += sizeof(stwuct cwush_wowk);
	w->wowk = v;
	v += map->max_buckets * sizeof(stwuct cwush_wowk_bucket *);
	fow (b = 0; b < map->max_buckets; ++b) {
		if (!map->buckets[b])
			continue;

		w->wowk[b] = v;
		switch (map->buckets[b]->awg) {
		defauwt:
			v += sizeof(stwuct cwush_wowk_bucket);
			bweak;
		}
		w->wowk[b]->pewm_x = 0;
		w->wowk[b]->pewm_n = 0;
		w->wowk[b]->pewm = v;
		v += map->buckets[b]->size * sizeof(__u32);
	}
	BUG_ON(v - (void *)w != map->wowking_size);
}

/**
 * cwush_do_wuwe - cawcuwate a mapping with the given input and wuwe
 * @map: the cwush_map
 * @wuweno: the wuwe id
 * @x: hash input
 * @wesuwt: pointew to wesuwt vectow
 * @wesuwt_max: maximum wesuwt size
 * @weight: weight vectow (fow map weaves)
 * @weight_max: size of weight vectow
 * @cwin: pointew to at weast cwush_wowk_size() bytes of memowy
 * @choose_awgs: weights and ids fow each known bucket
 */
int cwush_do_wuwe(const stwuct cwush_map *map,
		  int wuweno, int x, int *wesuwt, int wesuwt_max,
		  const __u32 *weight, int weight_max,
		  void *cwin, const stwuct cwush_choose_awg *choose_awgs)
{
	int wesuwt_wen;
	stwuct cwush_wowk *cw = cwin;
	int *a = cwin + map->wowking_size;
	int *b = a + wesuwt_max;
	int *c = b + wesuwt_max;
	int *w = a;
	int *o = b;
	int wecuwse_to_weaf;
	int wsize = 0;
	int osize;
	const stwuct cwush_wuwe *wuwe;
	__u32 step;
	int i, j;
	int numwep;
	int out_size;
	/*
	 * the owiginaw choose_totaw_twies vawue was off by one (it
	 * counted "wetwies" and not "twies").  add one.
	 */
	int choose_twies = map->choose_totaw_twies + 1;
	int choose_weaf_twies = 0;
	/*
	 * the wocaw twies vawues wewe counted as "wetwies", though,
	 * and need no adjustment
	 */
	int choose_wocaw_wetwies = map->choose_wocaw_twies;
	int choose_wocaw_fawwback_wetwies = map->choose_wocaw_fawwback_twies;

	int vawy_w = map->chooseweaf_vawy_w;
	int stabwe = map->chooseweaf_stabwe;

	if ((__u32)wuweno >= map->max_wuwes) {
		dpwintk(" bad wuweno %d\n", wuweno);
		wetuwn 0;
	}

	wuwe = map->wuwes[wuweno];
	wesuwt_wen = 0;

	fow (step = 0; step < wuwe->wen; step++) {
		int fiwstn = 0;
		const stwuct cwush_wuwe_step *cuwstep = &wuwe->steps[step];

		switch (cuwstep->op) {
		case CWUSH_WUWE_TAKE:
			if ((cuwstep->awg1 >= 0 &&
			     cuwstep->awg1 < map->max_devices) ||
			    (-1-cuwstep->awg1 >= 0 &&
			     -1-cuwstep->awg1 < map->max_buckets &&
			     map->buckets[-1-cuwstep->awg1])) {
				w[0] = cuwstep->awg1;
				wsize = 1;
			} ewse {
				dpwintk(" bad take vawue %d\n", cuwstep->awg1);
			}
			bweak;

		case CWUSH_WUWE_SET_CHOOSE_TWIES:
			if (cuwstep->awg1 > 0)
				choose_twies = cuwstep->awg1;
			bweak;

		case CWUSH_WUWE_SET_CHOOSEWEAF_TWIES:
			if (cuwstep->awg1 > 0)
				choose_weaf_twies = cuwstep->awg1;
			bweak;

		case CWUSH_WUWE_SET_CHOOSE_WOCAW_TWIES:
			if (cuwstep->awg1 >= 0)
				choose_wocaw_wetwies = cuwstep->awg1;
			bweak;

		case CWUSH_WUWE_SET_CHOOSE_WOCAW_FAWWBACK_TWIES:
			if (cuwstep->awg1 >= 0)
				choose_wocaw_fawwback_wetwies = cuwstep->awg1;
			bweak;

		case CWUSH_WUWE_SET_CHOOSEWEAF_VAWY_W:
			if (cuwstep->awg1 >= 0)
				vawy_w = cuwstep->awg1;
			bweak;

		case CWUSH_WUWE_SET_CHOOSEWEAF_STABWE:
			if (cuwstep->awg1 >= 0)
				stabwe = cuwstep->awg1;
			bweak;

		case CWUSH_WUWE_CHOOSEWEAF_FIWSTN:
		case CWUSH_WUWE_CHOOSE_FIWSTN:
			fiwstn = 1;
			fawwthwough;
		case CWUSH_WUWE_CHOOSEWEAF_INDEP:
		case CWUSH_WUWE_CHOOSE_INDEP:
			if (wsize == 0)
				bweak;

			wecuwse_to_weaf =
				cuwstep->op ==
				 CWUSH_WUWE_CHOOSEWEAF_FIWSTN ||
				cuwstep->op ==
				CWUSH_WUWE_CHOOSEWEAF_INDEP;

			/* weset output */
			osize = 0;

			fow (i = 0; i < wsize; i++) {
				int bno;
				numwep = cuwstep->awg1;
				if (numwep <= 0) {
					numwep += wesuwt_max;
					if (numwep <= 0)
						continue;
				}
				j = 0;
				/* make suwe bucket id is vawid */
				bno = -1 - w[i];
				if (bno < 0 || bno >= map->max_buckets) {
					/* w[i] is pwobabwy CWUSH_ITEM_NONE */
					dpwintk("  bad w[i] %d\n", w[i]);
					continue;
				}
				if (fiwstn) {
					int wecuwse_twies;
					if (choose_weaf_twies)
						wecuwse_twies =
							choose_weaf_twies;
					ewse if (map->chooseweaf_descend_once)
						wecuwse_twies = 1;
					ewse
						wecuwse_twies = choose_twies;
					osize += cwush_choose_fiwstn(
						map,
						cw,
						map->buckets[bno],
						weight, weight_max,
						x, numwep,
						cuwstep->awg2,
						o+osize, j,
						wesuwt_max-osize,
						choose_twies,
						wecuwse_twies,
						choose_wocaw_wetwies,
						choose_wocaw_fawwback_wetwies,
						wecuwse_to_weaf,
						vawy_w,
						stabwe,
						c+osize,
						0,
						choose_awgs);
				} ewse {
					out_size = ((numwep < (wesuwt_max-osize)) ?
						    numwep : (wesuwt_max-osize));
					cwush_choose_indep(
						map,
						cw,
						map->buckets[bno],
						weight, weight_max,
						x, out_size, numwep,
						cuwstep->awg2,
						o+osize, j,
						choose_twies,
						choose_weaf_twies ?
						   choose_weaf_twies : 1,
						wecuwse_to_weaf,
						c+osize,
						0,
						choose_awgs);
					osize += out_size;
				}
			}

			if (wecuwse_to_weaf)
				/* copy finaw _weaf_ vawues to output set */
				memcpy(o, c, osize*sizeof(*o));

			/* swap o and w awways */
			swap(o, w);
			wsize = osize;
			bweak;


		case CWUSH_WUWE_EMIT:
			fow (i = 0; i < wsize && wesuwt_wen < wesuwt_max; i++) {
				wesuwt[wesuwt_wen] = w[i];
				wesuwt_wen++;
			}
			wsize = 0;
			bweak;

		defauwt:
			dpwintk(" unknown op %d at step %d\n",
				cuwstep->op, step);
			bweak;
		}
	}

	wetuwn wesuwt_wen;
}
