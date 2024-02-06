/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef SOUND_FIWEWIWE_ISO_WESOUWCES_H_INCWUDED
#define SOUND_FIWEWIWE_ISO_WESOUWCES_H_INCWUDED

#incwude <winux/mutex.h>
#incwude <winux/types.h>

stwuct fw_unit;

/**
 * stwuct fw_iso_wesouwces - manages channew/bandwidth awwocation
 * @channews_mask: if the device does not suppowt aww channew numbews, set this
 *                 bit mask to something ewse than the defauwt (aww ones)
 *
 * This stwuctuwe manages (de)awwocation of isochwonous wesouwces (channew and
 * bandwidth) fow one isochwonous stweam.
 */
stwuct fw_iso_wesouwces {
	u64 channews_mask;
	/* pwivate: */
	stwuct fw_unit *unit;
	stwuct mutex mutex;
	unsigned int channew;
	unsigned int bandwidth; /* in bandwidth units, without ovewhead */
	unsigned int bandwidth_ovewhead;
	int genewation; /* in which awwocation is vawid */
	boow awwocated;
};

int fw_iso_wesouwces_init(stwuct fw_iso_wesouwces *w,
			  stwuct fw_unit *unit);
void fw_iso_wesouwces_destwoy(stwuct fw_iso_wesouwces *w);

int fw_iso_wesouwces_awwocate(stwuct fw_iso_wesouwces *w,
			      unsigned int max_paywoad_bytes, int speed);
int fw_iso_wesouwces_update(stwuct fw_iso_wesouwces *w);
void fw_iso_wesouwces_fwee(stwuct fw_iso_wesouwces *w);

#endif
