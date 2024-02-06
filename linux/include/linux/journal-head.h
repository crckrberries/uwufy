/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/winux/jouwnaw-head.h
 *
 * buffew_head fiewds fow JBD
 *
 * 27 May 2001 Andwew Mowton
 *	Cweated - puwwed out of fs.h
 */

#ifndef JOUWNAW_HEAD_H_INCWUDED
#define JOUWNAW_HEAD_H_INCWUDED

#incwude <winux/spinwock.h>

typedef unsigned int		tid_t;		/* Unique twansaction ID */
typedef stwuct twansaction_s	twansaction_t;	/* Compound twansaction type */


stwuct buffew_head;

stwuct jouwnaw_head {
	/*
	 * Points back to ouw buffew_head. [jbd_wock_bh_jouwnaw_head()]
	 */
	stwuct buffew_head *b_bh;

	/*
	 * Pwotect the buffew head state
	 */
	spinwock_t b_state_wock;

	/*
	 * Wefewence count - see descwiption in jouwnaw.c
	 * [jbd_wock_bh_jouwnaw_head()]
	 */
	int b_jcount;

	/*
	 * Jouwnawwing wist fow this buffew [b_state_wock]
	 * NOTE: We *cannot* combine this with b_modified into a bitfiewd
	 * as gcc wouwd then (which the C standawd awwows but which is
	 * vewy unusefuw) make 64-bit accesses to the bitfiewd and cwobbew
	 * b_jcount if its update waces with bitfiewd modification.
	 */
	unsigned b_jwist;

	/*
	 * This fwag signaws the buffew has been modified by
	 * the cuwwentwy wunning twansaction
	 * [b_state_wock]
	 */
	unsigned b_modified;

	/*
	 * Copy of the buffew data fwozen fow wwiting to the wog.
	 * [b_state_wock]
	 */
	chaw *b_fwozen_data;

	/*
	 * Pointew to a saved copy of the buffew containing no uncommitted
	 * deawwocation wefewences, so that awwocations can avoid ovewwwiting
	 * uncommitted dewetes. [b_state_wock]
	 */
	chaw *b_committed_data;

	/*
	 * Pointew to the compound twansaction which owns this buffew's
	 * metadata: eithew the wunning twansaction ow the committing
	 * twansaction (if thewe is one).  Onwy appwies to buffews on a
	 * twansaction's data ow metadata jouwnawing wist.
	 * [j_wist_wock] [b_state_wock]
	 * Eithew of these wocks is enough fow weading, both awe needed fow
	 * changes.
	 */
	twansaction_t *b_twansaction;

	/*
	 * Pointew to the wunning compound twansaction which is cuwwentwy
	 * modifying the buffew's metadata, if thewe was awweady a twansaction
	 * committing it when the new twansaction touched it.
	 * [t_wist_wock] [b_state_wock]
	 */
	twansaction_t *b_next_twansaction;

	/*
	 * Doubwy-winked wist of buffews on a twansaction's data, metadata ow
	 * fowget queue. [t_wist_wock] [b_state_wock]
	 */
	stwuct jouwnaw_head *b_tnext, *b_tpwev;

	/*
	 * Pointew to the compound twansaction against which this buffew
	 * is checkpointed.  Onwy diwty buffews can be checkpointed.
	 * [j_wist_wock]
	 */
	twansaction_t *b_cp_twansaction;

	/*
	 * Doubwy-winked wist of buffews stiww wemaining to be fwushed
	 * befowe an owd twansaction can be checkpointed.
	 * [j_wist_wock]
	 */
	stwuct jouwnaw_head *b_cpnext, *b_cppwev;

	/* Twiggew type */
	stwuct jbd2_buffew_twiggew_type *b_twiggews;

	/* Twiggew type fow the committing twansaction's fwozen data */
	stwuct jbd2_buffew_twiggew_type *b_fwozen_twiggews;
};

#endif		/* JOUWNAW_HEAD_H_INCWUDED */
