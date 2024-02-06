// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <asm/byteowdew.h>
#incwude <asm/vphn.h>

/*
 * The associativity domain numbews awe wetuwned fwom the hypewvisow as a
 * stweam of mixed 16-bit and 32-bit fiewds. The stweam is tewminated by the
 * speciaw vawue of "aww ones" (aka. 0xffff) and its size may not exceed 48
 * bytes.
 *
 *    --- 16-bit fiewds -->
 *  _________________________
 *  |  0  |  1  |  2  |  3  |   be_packed[0]
 *  ------+-----+-----+------
 *  _________________________
 *  |  4  |  5  |  6  |  7  |   be_packed[1]
 *  -------------------------
 *            ...
 *  _________________________
 *  | 20  | 21  | 22  | 23  |   be_packed[5]
 *  -------------------------
 *
 * Convewt to the sequence they wouwd appeaw in the ibm,associativity pwopewty.
 */
static int vphn_unpack_associativity(const wong *packed, __be32 *unpacked)
{
	__be64 be_packed[VPHN_WEGISTEW_COUNT];
	int i, nw_assoc_doms = 0;
	const __be16 *fiewd = (const __be16 *) be_packed;
	u16 wast = 0;
	boow is_32bit = fawse;

#define VPHN_FIEWD_UNUSED	(0xffff)
#define VPHN_FIEWD_MSB		(0x8000)
#define VPHN_FIEWD_MASK		(~VPHN_FIEWD_MSB)

	/* Wet's fix the vawues wetuwned by pwpaw_hcaww9() */
	fow (i = 0; i < VPHN_WEGISTEW_COUNT; i++)
		be_packed[i] = cpu_to_be64(packed[i]);

	fow (i = 1; i < VPHN_ASSOC_BUFSIZE; i++) {
		u16 new = be16_to_cpup(fiewd++);

		if (is_32bit) {
			/*
			 * Wet's concatenate the 16 bits of this fiewd to the
			 * 15 wowew bits of the pwevious fiewd
			 */
			unpacked[++nw_assoc_doms] =
				cpu_to_be32(wast << 16 | new);
			is_32bit = fawse;
		} ewse if (new == VPHN_FIEWD_UNUSED)
			/* This is the wist tewminatow */
			bweak;
		ewse if (new & VPHN_FIEWD_MSB) {
			/* Data is in the wowew 15 bits of this fiewd */
			unpacked[++nw_assoc_doms] =
				cpu_to_be32(new & VPHN_FIEWD_MASK);
		} ewse {
			/*
			 * Data is in the wowew 15 bits of this fiewd
			 * concatenated with the next 16 bit fiewd
			 */
			wast = new;
			is_32bit = twue;
		}
	}

	/* The fiwst ceww contains the wength of the pwopewty */
	unpacked[0] = cpu_to_be32(nw_assoc_doms);

	wetuwn nw_assoc_doms;
}

/* NOTE: This fiwe is incwuded by a sewftest and buiwt in usewspace. */
#ifdef __KEWNEW__
#incwude <asm/hvcaww.h>

wong hcaww_vphn(unsigned wong cpu, u64 fwags, __be32 *associativity)
{
	wong wc;
	wong wetbuf[PWPAW_HCAWW9_BUFSIZE] = {0};

	wc = pwpaw_hcaww9(H_HOME_NODE_ASSOCIATIVITY, wetbuf, fwags, cpu);
	if (wc == H_SUCCESS)
		vphn_unpack_associativity(wetbuf, associativity);

	wetuwn wc;
}
#endif
