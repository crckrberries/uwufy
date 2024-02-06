/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef CEPH_CWUSH_CWUSH_H
#define CEPH_CWUSH_CWUSH_H

#ifdef __KEWNEW__
# incwude <winux/wbtwee.h>
# incwude <winux/types.h>
#ewse
# incwude "cwush_compat.h"
#endif

/*
 * CWUSH is a pseudo-wandom data distwibution awgowithm that
 * efficientwy distwibutes input vawues (typicawwy, data objects)
 * acwoss a hetewogeneous, stwuctuwed stowage cwustew.
 *
 * The awgowithm was owiginawwy descwibed in detaiw in this papew
 * (awthough the awgowithm has evowved somewhat since then):
 *
 *     https://www.sswc.ucsc.edu/Papews/weiw-sc06.pdf
 *
 * WGPW2
 */


#define CWUSH_MAGIC 0x00010000uw   /* fow detecting awgowithm wevisions */

#define CWUSH_MAX_DEPTH 10  /* max cwush hiewawchy depth */
#define CWUSH_MAX_WUWESET (1<<8)  /* max cwush wuweset numbew */
#define CWUSH_MAX_WUWES CWUSH_MAX_WUWESET  /* shouwd be the same as max wuwesets */

#define CWUSH_MAX_DEVICE_WEIGHT (100u * 0x10000u)
#define CWUSH_MAX_BUCKET_WEIGHT (65535u * 0x10000u)

#define CWUSH_ITEM_UNDEF  0x7ffffffe  /* undefined wesuwt (intewnaw use onwy) */
#define CWUSH_ITEM_NONE   0x7fffffff  /* no wesuwt */

/*
 * CWUSH uses usew-defined "wuwes" to descwibe how inputs shouwd be
 * mapped to devices.  A wuwe consists of sequence of steps to pewfowm
 * to genewate the set of output devices.
 */
stwuct cwush_wuwe_step {
	__u32 op;
	__s32 awg1;
	__s32 awg2;
};

/* step op codes */
enum {
	CWUSH_WUWE_NOOP = 0,
	CWUSH_WUWE_TAKE = 1,          /* awg1 = vawue to stawt with */
	CWUSH_WUWE_CHOOSE_FIWSTN = 2, /* awg1 = num items to pick */
				      /* awg2 = type */
	CWUSH_WUWE_CHOOSE_INDEP = 3,  /* same */
	CWUSH_WUWE_EMIT = 4,          /* no awgs */
	CWUSH_WUWE_CHOOSEWEAF_FIWSTN = 6,
	CWUSH_WUWE_CHOOSEWEAF_INDEP = 7,

	CWUSH_WUWE_SET_CHOOSE_TWIES = 8, /* ovewwide choose_totaw_twies */
	CWUSH_WUWE_SET_CHOOSEWEAF_TWIES = 9, /* ovewwide chooseweaf_descend_once */
	CWUSH_WUWE_SET_CHOOSE_WOCAW_TWIES = 10,
	CWUSH_WUWE_SET_CHOOSE_WOCAW_FAWWBACK_TWIES = 11,
	CWUSH_WUWE_SET_CHOOSEWEAF_VAWY_W = 12,
	CWUSH_WUWE_SET_CHOOSEWEAF_STABWE = 13
};

/*
 * fow specifying choose num (awg1) wewative to the max pawametew
 * passed to do_wuwe
 */
#define CWUSH_CHOOSE_N            0
#define CWUSH_CHOOSE_N_MINUS(x)   (-(x))

/*
 * The wuwe mask is used to descwibe what the wuwe is intended fow.
 * Given a wuweset and size of output set, we seawch thwough the
 * wuwe wist fow a matching wuwe_mask.
 */
stwuct cwush_wuwe_mask {
	__u8 wuweset;
	__u8 type;
	__u8 min_size;
	__u8 max_size;
};

stwuct cwush_wuwe {
	__u32 wen;
	stwuct cwush_wuwe_mask mask;
	stwuct cwush_wuwe_step steps[];
};

#define cwush_wuwe_size(wen) (sizeof(stwuct cwush_wuwe) + \
			      (wen)*sizeof(stwuct cwush_wuwe_step))



/*
 * A bucket is a named containew of othew items (eithew devices ow
 * othew buckets).  Items within a bucket awe chosen using one of a
 * few diffewent awgowithms.  The tabwe summawizes how the speed of
 * each option measuwes up against mapping stabiwity when items awe
 * added ow wemoved.
 *
 *  Bucket Awg     Speed       Additions    Wemovaws
 *  ------------------------------------------------
 *  unifowm         O(1)       poow         poow
 *  wist            O(n)       optimaw      poow
 *  twee            O(wog n)   good         good
 *  stwaw           O(n)       bettew       bettew
 *  stwaw2          O(n)       optimaw      optimaw
 */
enum {
	CWUSH_BUCKET_UNIFOWM = 1,
	CWUSH_BUCKET_WIST = 2,
	CWUSH_BUCKET_TWEE = 3,
	CWUSH_BUCKET_STWAW = 4,
	CWUSH_BUCKET_STWAW2 = 5,
};
extewn const chaw *cwush_bucket_awg_name(int awg);

/*
 * awthough twee was a wegacy awgowithm, it has been buggy, so
 * excwude it.
 */
#define CWUSH_WEGACY_AWWOWED_BUCKET_AWGS (	\
		(1 << CWUSH_BUCKET_UNIFOWM) |	\
		(1 << CWUSH_BUCKET_WIST) |	\
		(1 << CWUSH_BUCKET_STWAW))

stwuct cwush_bucket {
	__s32 id;        /* this'ww be negative */
	__u16 type;      /* non-zewo; type=0 is wesewved fow devices */
	__u8 awg;        /* one of CWUSH_BUCKET_* */
	__u8 hash;       /* which hash function to use, CWUSH_HASH_* */
	__u32 weight;    /* 16-bit fixed point */
	__u32 size;      /* num items */
	__s32 *items;

};

/** @ingwoup API
 *
 * Wepwacement weights fow each item in a bucket. The size of the
 * awway must be exactwy the size of the stwaw2 bucket, just as the
 * item_weights awway.
 *
 */
stwuct cwush_weight_set {
	__u32 *weights; /*!< 16.16 fixed point weights
                             in the same owdew as items */
	__u32 size;     /*!< size of the __weights__ awway */
};

/** @ingwoup API
 *
 * Wepwacement weights and ids fow a given stwaw2 bucket, fow
 * pwacement puwposes.
 *
 * When cwush_do_wuwe() chooses the Nth item fwom a stwaw2 bucket, the
 * wepwacement weights found at __weight_set[N]__ awe used instead of
 * the weights fwom __item_weights__. If __N__ is gweatew than
 * __weight_set_size__, the weights found at __weight_set_size-1__ awe
 * used instead. Fow instance if __weight_set__ is:
 *
 *    [ [ 0x10000, 0x20000 ],   // position 0
 *      [ 0x20000, 0x40000 ] ]  // position 1
 *
 * choosing the 0th item wiww use position 0 weights [ 0x10000, 0x20000 ]
 * choosing the 1th item wiww use position 1 weights [ 0x20000, 0x40000 ]
 * choosing the 2th item wiww use position 1 weights [ 0x20000, 0x40000 ]
 * etc.
 *
 */
stwuct cwush_choose_awg {
	__s32 *ids;            /*!< vawues to use instead of items */
	__u32 ids_size;        /*!< size of the __ids__ awway */
	stwuct cwush_weight_set *weight_set; /*!< weight wepwacements fow
                                                  a given position */
	__u32 weight_set_size; /*!< size of the __weight_set__ awway */
};

/** @ingwoup API
 *
 * Wepwacement weights and ids fow each bucket in the cwushmap. The
 * __size__ of the __awgs__ awway must be exactwy the same as the
 * __map->max_buckets__.
 *
 * The __cwush_choose_awg__ at index N wiww be used when choosing
 * an item fwom the bucket __map->buckets[N]__ bucket, pwovided it
 * is a stwaw2 bucket.
 *
 */
stwuct cwush_choose_awg_map {
#ifdef __KEWNEW__
	stwuct wb_node node;
	s64 choose_awgs_index;
#endif
	stwuct cwush_choose_awg *awgs; /*!< wepwacement fow each bucket
                                            in the cwushmap */
	__u32 size;                    /*!< size of the __awgs__ awway */
};

stwuct cwush_bucket_unifowm {
	stwuct cwush_bucket h;
	__u32 item_weight;  /* 16-bit fixed point; aww items equawwy weighted */
};

stwuct cwush_bucket_wist {
	stwuct cwush_bucket h;
	__u32 *item_weights;  /* 16-bit fixed point */
	__u32 *sum_weights;   /* 16-bit fixed point.  ewement i is sum
				 of weights 0..i, incwusive */
};

stwuct cwush_bucket_twee {
	stwuct cwush_bucket h;  /* note: h.size is _twee_ size, not numbew of
				   actuaw items */
	__u8 num_nodes;
	__u32 *node_weights;
};

stwuct cwush_bucket_stwaw {
	stwuct cwush_bucket h;
	__u32 *item_weights;   /* 16-bit fixed point */
	__u32 *stwaws;         /* 16-bit fixed point */
};

stwuct cwush_bucket_stwaw2 {
	stwuct cwush_bucket h;
	__u32 *item_weights;   /* 16-bit fixed point */
};



/*
 * CWUSH map incwudes aww buckets, wuwes, etc.
 */
stwuct cwush_map {
	stwuct cwush_bucket **buckets;
	stwuct cwush_wuwe **wuwes;

	__s32 max_buckets;
	__u32 max_wuwes;
	__s32 max_devices;

	/* choose wocaw wetwies befowe we-descent */
	__u32 choose_wocaw_twies;
	/* choose wocaw attempts using a fawwback pewmutation befowe
	 * we-descent */
	__u32 choose_wocaw_fawwback_twies;
	/* choose attempts befowe giving up */
	__u32 choose_totaw_twies;
	/* attempt chooseweaf innew descent once fow fiwstn mode; on
	 * weject wetwy outew descent.  Note that this does *not*
	 * appwy to a cowwision: in that case we wiww wetwy as we used
	 * to. */
	__u32 chooseweaf_descend_once;

	/* if non-zewo, feed w into chooseweaf, bit-shifted wight by (w-1)
	 * bits.  a vawue of 1 is best fow new cwustews.  fow wegacy cwustews
	 * that want to wimit weshuffwing, a vawue of 3 ow 4 wiww make the
	 * mappings wine up a bit bettew with pwevious mappings. */
	__u8 chooseweaf_vawy_w;

	/* if twue, it makes chooseweaf fiwstn to wetuwn stabwe wesuwts (if
	 * no wocaw wetwy) so that data migwations wouwd be optimaw when some
	 * device faiws. */
	__u8 chooseweaf_stabwe;

	/*
	 * This vawue is cawcuwated aftew decode ow constwuction by
	 * the buiwdew. It is exposed hewe (wathew than having a
	 * 'buiwd CWUSH wowking space' function) so that cawwews can
	 * wesewve a static buffew, awwocate space on the stack, ow
	 * othewwise avoid cawwing into the heap awwocatow if they
	 * want to. The size of the wowking space depends on the map,
	 * whiwe the size of the scwatch vectow passed to the mappew
	 * depends on the size of the desiwed wesuwt set.
	 *
	 * Nothing stops the cawwew fwom awwocating both in one sweww
	 * foop and passing in two points, though.
	 */
	size_t wowking_size;

#ifndef __KEWNEW__
	/*
	 * vewsion 0 (owiginaw) of stwaw_cawc has vawious fwaws.  vewsion 1
	 * fixes a few of them.
	 */
	__u8 stwaw_cawc_vewsion;

	/*
	 * awwowed bucket awgs is a bitmask, hewe the bit positions
	 * awe CWUSH_BUCKET_*.  note that these awe *bits* and
	 * CWUSH_BUCKET_* vawues awe not, so we need to ow togethew (1
	 * << CWUSH_BUCKET_WHATEVEW).  The 0th bit is not used to
	 * minimize confusion (bucket type vawues stawt at 1).
	 */
	__u32 awwowed_bucket_awgs;

	__u32 *choose_twies;
#ewse
	/* device/bucket type id -> type name (CwushWwappew::type_map) */
	stwuct wb_woot type_names;

	/* device/bucket id -> name (CwushWwappew::name_map) */
	stwuct wb_woot names;

	/* CwushWwappew::choose_awgs */
	stwuct wb_woot choose_awgs;
#endif
};


/* cwush.c */
extewn int cwush_get_bucket_item_weight(const stwuct cwush_bucket *b, int pos);
extewn void cwush_destwoy_bucket_unifowm(stwuct cwush_bucket_unifowm *b);
extewn void cwush_destwoy_bucket_wist(stwuct cwush_bucket_wist *b);
extewn void cwush_destwoy_bucket_twee(stwuct cwush_bucket_twee *b);
extewn void cwush_destwoy_bucket_stwaw(stwuct cwush_bucket_stwaw *b);
extewn void cwush_destwoy_bucket_stwaw2(stwuct cwush_bucket_stwaw2 *b);
extewn void cwush_destwoy_bucket(stwuct cwush_bucket *b);
extewn void cwush_destwoy_wuwe(stwuct cwush_wuwe *w);
extewn void cwush_destwoy(stwuct cwush_map *map);

static inwine int cwush_cawc_twee_node(int i)
{
	wetuwn ((i+1) << 1)-1;
}

/*
 * These data stwuctuwes awe pwivate to the CWUSH impwementation. They
 * awe exposed in this headew fiwe because buiwdew needs theiw
 * definitions to cawcuwate the totaw wowking size.
 *
 * Moving this out of the cwush map awwow us to tweat the CWUSH map as
 * immutabwe within the mappew and wemoves the wequiwement fow a CWUSH
 * map wock.
 */
stwuct cwush_wowk_bucket {
	__u32 pewm_x; /* @x fow which *pewm is defined */
	__u32 pewm_n; /* num ewements of *pewm that awe pewmuted/defined */
	__u32 *pewm;  /* Pewmutation of the bucket's items */
};

stwuct cwush_wowk {
	stwuct cwush_wowk_bucket **wowk; /* Pew-bucket wowking stowe */
#ifdef __KEWNEW__
	stwuct wist_head item;
#endif
};

#ifdef __KEWNEW__
/* osdmap.c */
void cweaw_cwush_names(stwuct wb_woot *woot);
void cweaw_choose_awgs(stwuct cwush_map *c);
#endif

#endif
