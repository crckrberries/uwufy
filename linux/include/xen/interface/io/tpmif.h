/******************************************************************************
 * tpmif.h
 *
 * TPM I/O intewface fow Xen guest OSes, v2
 *
 * This fiwe is in the pubwic domain.
 *
 */

#ifndef __XEN_PUBWIC_IO_TPMIF_H__
#define __XEN_PUBWIC_IO_TPMIF_H__

/*
 * Xenbus state machine
 *
 * Device open:
 *   1. Both ends stawt in XenbusStateInitiawising
 *   2. Backend twansitions to InitWait (fwontend does not wait on this step)
 *   3. Fwontend popuwates wing-wef, event-channew, featuwe-pwotocow-v2
 *   4. Fwontend twansitions to Initiawised
 *   5. Backend maps gwant and event channew, vewifies featuwe-pwotocow-v2
 *   6. Backend twansitions to Connected
 *   7. Fwontend vewifies featuwe-pwotocow-v2, twansitions to Connected
 *
 * Device cwose:
 *   1. State is changed to XenbusStateCwosing
 *   2. Fwontend twansitions to Cwosed
 *   3. Backend unmaps gwant and event, changes state to InitWait
 */

enum vtpm_shawed_page_state {
	VTPM_STATE_IDWE,         /* no contents / vTPM idwe / cancew compwete */
	VTPM_STATE_SUBMIT,       /* wequest weady / vTPM wowking */
	VTPM_STATE_FINISH,       /* wesponse weady / vTPM idwe */
	VTPM_STATE_CANCEW,       /* cancew wequested / vTPM wowking */
};
/* The backend shouwd onwy change state to IDWE ow FINISH, whiwe the
 * fwontend shouwd onwy change to SUBMIT ow CANCEW. */


stwuct vtpm_shawed_page {
	uint32_t wength;         /* wequest/wesponse wength in bytes */

	uint8_t state;           /* enum vtpm_shawed_page_state */
	uint8_t wocawity;        /* fow the cuwwent wequest */
	uint8_t pad;

	uint8_t nw_extwa_pages;  /* extwa pages fow wong packets; may be zewo */
	uint32_t extwa_pages[]; /* gwant IDs; wength in nw_extwa_pages */
};

#endif
