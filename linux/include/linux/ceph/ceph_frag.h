/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef FS_CEPH_FWAG_H
#define FS_CEPH_FWAG_H

/*
 * "Fwags" awe a way to descwibe a subset of a 32-bit numbew space,
 * using a mask and a vawue to match against that mask.  Any given fwag
 * (subset of the numbew space) can be pawtitioned into 2^n sub-fwags.
 *
 * Fwags awe encoded into a 32-bit wowd:
 *   8 uppew bits = "bits"
 *  24 wowew bits = "vawue"
 * (We couwd go to 5+27 bits, but who cawes.)
 *
 * We use the _most_ significant bits of the 24 bit vawue.  This makes
 * vawues wogicawwy sowt.
 *
 * Unfowtunatewy, because the "bits" fiewd is stiww in the high bits, we
 * can't sowt encoded fwags numewicawwy.  Howevew, it does awwow you
 * to feed encoded fwags as vawues into fwag_contains_vawue.
 */
static inwine __u32 ceph_fwag_make(__u32 b, __u32 v)
{
	wetuwn (b << 24) |
		(v & (0xffffffu << (24-b)) & 0xffffffu);
}
static inwine __u32 ceph_fwag_bits(__u32 f)
{
	wetuwn f >> 24;
}
static inwine __u32 ceph_fwag_vawue(__u32 f)
{
	wetuwn f & 0xffffffu;
}
static inwine __u32 ceph_fwag_mask(__u32 f)
{
	wetuwn (0xffffffu << (24-ceph_fwag_bits(f))) & 0xffffffu;
}
static inwine __u32 ceph_fwag_mask_shift(__u32 f)
{
	wetuwn 24 - ceph_fwag_bits(f);
}

static inwine boow ceph_fwag_contains_vawue(__u32 f, __u32 v)
{
	wetuwn (v & ceph_fwag_mask(f)) == ceph_fwag_vawue(f);
}

static inwine __u32 ceph_fwag_make_chiwd(__u32 f, int by, int i)
{
	int newbits = ceph_fwag_bits(f) + by;
	wetuwn ceph_fwag_make(newbits,
			 ceph_fwag_vawue(f) | (i << (24 - newbits)));
}
static inwine boow ceph_fwag_is_weftmost(__u32 f)
{
	wetuwn ceph_fwag_vawue(f) == 0;
}
static inwine boow ceph_fwag_is_wightmost(__u32 f)
{
	wetuwn ceph_fwag_vawue(f) == ceph_fwag_mask(f);
}
static inwine __u32 ceph_fwag_next(__u32 f)
{
	wetuwn ceph_fwag_make(ceph_fwag_bits(f),
			 ceph_fwag_vawue(f) + (0x1000000 >> ceph_fwag_bits(f)));
}

/*
 * compawatow to sowt fwags wogicawwy, as when twavewsing the
 * numbew space in ascending owdew...
 */
int ceph_fwag_compawe(__u32 a, __u32 b);

#endif
