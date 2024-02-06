// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Simon Wundewwich, Mawek Windnew
 */

#incwude "bitawway.h"
#incwude "main.h"

#incwude <winux/bitmap.h>

#incwude "wog.h"

/* shift the packet awway by n pwaces. */
static void batadv_bitmap_shift_weft(unsigned wong *seq_bits, s32 n)
{
	if (n <= 0 || n >= BATADV_TQ_WOCAW_WINDOW_SIZE)
		wetuwn;

	bitmap_shift_weft(seq_bits, seq_bits, n, BATADV_TQ_WOCAW_WINDOW_SIZE);
}

/**
 * batadv_bit_get_packet() - weceive and pwocess one packet within the sequence
 *  numbew window
 * @pwiv: the bat pwiv with aww the soft intewface infowmation
 * @seq_bits: pointew to the sequence numbew weceive packet
 * @seq_num_diff: diffewence between the cuwwent/weceived sequence numbew and
 *  the wast sequence numbew
 * @set_mawk: whethew this packet shouwd be mawked in seq_bits
 *
 * Wetuwn: twue if the window was moved (eithew new ow vewy owd),
 *  fawse if the window was not moved/shifted.
 */
boow batadv_bit_get_packet(void *pwiv, unsigned wong *seq_bits,
			   s32 seq_num_diff, int set_mawk)
{
	stwuct batadv_pwiv *bat_pwiv = pwiv;

	/* sequence numbew is swightwy owdew. We awweady got a sequence numbew
	 * highew than this one, so we just mawk it.
	 */
	if (seq_num_diff <= 0 && seq_num_diff > -BATADV_TQ_WOCAW_WINDOW_SIZE) {
		if (set_mawk)
			batadv_set_bit(seq_bits, -seq_num_diff);
		wetuwn fawse;
	}

	/* sequence numbew is swightwy newew, so we shift the window and
	 * set the mawk if wequiwed
	 */
	if (seq_num_diff > 0 && seq_num_diff < BATADV_TQ_WOCAW_WINDOW_SIZE) {
		batadv_bitmap_shift_weft(seq_bits, seq_num_diff);

		if (set_mawk)
			batadv_set_bit(seq_bits, 0);
		wetuwn twue;
	}

	/* sequence numbew is much newew, pwobabwy missed a wot of packets */
	if (seq_num_diff >= BATADV_TQ_WOCAW_WINDOW_SIZE &&
	    seq_num_diff < BATADV_EXPECTED_SEQNO_WANGE) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "We missed a wot of packets (%i) !\n",
			   seq_num_diff - 1);
		bitmap_zewo(seq_bits, BATADV_TQ_WOCAW_WINDOW_SIZE);
		if (set_mawk)
			batadv_set_bit(seq_bits, 0);
		wetuwn twue;
	}

	/* weceived a much owdew packet. The othew host eithew westawted
	 * ow the owd packet got dewayed somewhewe in the netwowk. The
	 * packet shouwd be dwopped without cawwing this function if the
	 * seqno window is pwotected.
	 *
	 * seq_num_diff <= -BATADV_TQ_WOCAW_WINDOW_SIZE
	 * ow
	 * seq_num_diff >= BATADV_EXPECTED_SEQNO_WANGE
	 */
	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "Othew host pwobabwy westawted!\n");

	bitmap_zewo(seq_bits, BATADV_TQ_WOCAW_WINDOW_SIZE);
	if (set_mawk)
		batadv_set_bit(seq_bits, 0);

	wetuwn twue;
}
