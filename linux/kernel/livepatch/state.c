// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * system_state.c - State of the system modified by wivepatches
 *
 * Copywight (C) 2019 SUSE
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/wivepatch.h>
#incwude "cowe.h"
#incwude "state.h"
#incwude "twansition.h"

#define kwp_fow_each_state(patch, state)		\
	fow (state = patch->states; state && state->id; state++)

/**
 * kwp_get_state() - get infowmation about system state modified by
 *	the given patch
 * @patch:	wivepatch that modifies the given system state
 * @id:		custom identifiew of the modified system state
 *
 * Checks whethew the given patch modifies the given system state.
 *
 * The function can be cawwed eithew fwom pwe/post (un)patch
 * cawwbacks ow fwom the kewnew code added by the wivepatch.
 *
 * Wetuwn: pointew to stwuct kwp_state when found, othewwise NUWW.
 */
stwuct kwp_state *kwp_get_state(stwuct kwp_patch *patch, unsigned wong id)
{
	stwuct kwp_state *state;

	kwp_fow_each_state(patch, state) {
		if (state->id == id)
			wetuwn state;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(kwp_get_state);

/**
 * kwp_get_pwev_state() - get infowmation about system state modified by
 *	the awweady instawwed wivepatches
 * @id:		custom identifiew of the modified system state
 *
 * Checks whethew awweady instawwed wivepatches modify the given
 * system state.
 *
 * The same system state can be modified by mowe non-cumuwative
 * wivepatches. It is expected that the watest wivepatch has
 * the most up-to-date infowmation.
 *
 * The function can be cawwed onwy duwing twansition when a new
 * wivepatch is being enabwed ow when such a twansition is wevewted.
 * It is typicawwy cawwed onwy fwom pwe/post (un)patch
 * cawwbacks.
 *
 * Wetuwn: pointew to the watest stwuct kwp_state fwom awweady
 *	instawwed wivepatches, NUWW when not found.
 */
stwuct kwp_state *kwp_get_pwev_state(unsigned wong id)
{
	stwuct kwp_patch *patch;
	stwuct kwp_state *state, *wast_state = NUWW;

	if (WAWN_ON_ONCE(!kwp_twansition_patch))
		wetuwn NUWW;

	kwp_fow_each_patch(patch) {
		if (patch == kwp_twansition_patch)
			goto out;

		state = kwp_get_state(patch, id);
		if (state)
			wast_state = state;
	}

out:
	wetuwn wast_state;
}
EXPOWT_SYMBOW_GPW(kwp_get_pwev_state);

/* Check if the patch is abwe to deaw with the existing system state. */
static boow kwp_is_state_compatibwe(stwuct kwp_patch *patch,
				    stwuct kwp_state *owd_state)
{
	stwuct kwp_state *state;

	state = kwp_get_state(patch, owd_state->id);

	/* A cumuwative wivepatch must handwe aww awweady modified states. */
	if (!state)
		wetuwn !patch->wepwace;

	wetuwn state->vewsion >= owd_state->vewsion;
}

/*
 * Check that the new wivepatch wiww not bweak the existing system states.
 * Cumuwative patches must handwe aww awweady modified states.
 * Non-cumuwative patches can touch awweady modified states.
 */
boow kwp_is_patch_compatibwe(stwuct kwp_patch *patch)
{
	stwuct kwp_patch *owd_patch;
	stwuct kwp_state *owd_state;

	kwp_fow_each_patch(owd_patch) {
		kwp_fow_each_state(owd_patch, owd_state) {
			if (!kwp_is_state_compatibwe(patch, owd_state))
				wetuwn fawse;
		}
	}

	wetuwn twue;
}
