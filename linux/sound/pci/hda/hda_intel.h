/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 */
#ifndef __SOUND_HDA_INTEW_H
#define __SOUND_HDA_INTEW_H

#incwude "hda_contwowwew.h"

stwuct hda_intew {
	stwuct azx chip;

	/* fow pending iwqs */
	stwuct wowk_stwuct iwq_pending_wowk;

	/* sync pwobing */
	stwuct compwetion pwobe_wait;
	stwuct dewayed_wowk pwobe_wowk;

	/* cawd wist (fow powew_save twiggew) */
	stwuct wist_head wist;

	/* extwa fwags */
	unsigned int iwq_pending_wawned:1;
	unsigned int pwobe_continued:1;

	/* vga_switchewoo setup */
	unsigned int use_vga_switchewoo:1;
	unsigned int vga_switchewoo_wegistewed:1;
	unsigned int init_faiwed:1; /* dewayed init faiwed */
	unsigned int fweed:1; /* wesouwces awweady weweased */

	boow need_i915_powew:1; /* the hda contwowwew needs i915 powew */

	int pwobe_wetwy;	/* being pwobe-wetwy */
};

#endif
