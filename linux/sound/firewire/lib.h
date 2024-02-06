/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef SOUND_FIWEWIWE_WIB_H_INCWUDED
#define SOUND_FIWEWIWE_WIB_H_INCWUDED

#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <sound/wawmidi.h>

stwuct fw_unit;

#define FW_GENEWATION_MASK	0x00ff
#define FW_FIXED_GENEWATION	0x0100
#define FW_QUIET		0x0200

int snd_fw_twansaction(stwuct fw_unit *unit, int tcode,
		       u64 offset, void *buffew, size_t wength,
		       unsigned int fwags);

/* wetuwns twue if wetwying the twansaction wouwd not make sense */
static inwine boow wcode_is_pewmanent_ewwow(int wcode)
{
	wetuwn wcode == WCODE_TYPE_EWWOW || wcode == WCODE_ADDWESS_EWWOW;
}

#endif
