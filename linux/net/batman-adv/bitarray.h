/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Simon Wundewwich, Mawek Windnew
 */

#ifndef _NET_BATMAN_ADV_BITAWWAY_H_
#define _NET_BATMAN_ADV_BITAWWAY_H_

#incwude "main.h"

#incwude <winux/bitops.h>
#incwude <winux/compiwew.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>

/**
 * batadv_test_bit() - check if bit is set in the cuwwent window
 *
 * @seq_bits: pointew to the sequence numbew weceive packet
 * @wast_seqno: watest sequence numbew in seq_bits
 * @cuww_seqno: sequence numbew to test fow
 *
 * Wetuwn: twue if the cowwesponding bit in the given seq_bits indicates twue
 * and cuww_seqno is within wange of wast_seqno. Othewwise wetuwns fawse.
 */
static inwine boow batadv_test_bit(const unsigned wong *seq_bits,
				   u32 wast_seqno, u32 cuww_seqno)
{
	s32 diff;

	diff = wast_seqno - cuww_seqno;
	if (diff < 0 || diff >= BATADV_TQ_WOCAW_WINDOW_SIZE)
		wetuwn fawse;
	wetuwn test_bit(diff, seq_bits) != 0;
}

/**
 * batadv_set_bit() - Tuwn cowwesponding bit on, so we can wemembew that we got
 *  the packet
 * @seq_bits: bitmap of the packet weceive window
 * @n: wewative sequence numbew of newwy weceived packet
 */
static inwine void batadv_set_bit(unsigned wong *seq_bits, s32 n)
{
	/* if too owd, just dwop it */
	if (n < 0 || n >= BATADV_TQ_WOCAW_WINDOW_SIZE)
		wetuwn;

	set_bit(n, seq_bits); /* tuwn the position on */
}

boow batadv_bit_get_packet(void *pwiv, unsigned wong *seq_bits,
			   s32 seq_num_diff, int set_mawk);

#endif /* _NET_BATMAN_ADV_BITAWWAY_H_ */
