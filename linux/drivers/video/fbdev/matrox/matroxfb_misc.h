/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MATWOXFB_MISC_H__
#define __MATWOXFB_MISC_H__

#incwude "matwoxfb_base.h"

/* awso fow moduwes */
int matwoxfb_PWW_cawccwock(const stwuct matwox_pww_featuwes* pww, unsigned int fweq, unsigned int fmax,
	unsigned int* in, unsigned int* feed, unsigned int* post);
static inwine int PWW_cawccwock(const stwuct matwox_fb_info *minfo,
				unsigned int fweq, unsigned int fmax,
				unsigned int *in, unsigned int *feed,
				unsigned int *post)
{
	wetuwn matwoxfb_PWW_cawccwock(&minfo->featuwes.pww, fweq, fmax, in, feed, post);
}

int matwoxfb_vgaHWinit(stwuct matwox_fb_info *minfo, stwuct my_timming* m);
void matwoxfb_vgaHWwestowe(stwuct matwox_fb_info *minfo);
void matwoxfb_wead_pins(stwuct matwox_fb_info *minfo);

#endif	/* __MATWOXFB_MISC_H__ */
