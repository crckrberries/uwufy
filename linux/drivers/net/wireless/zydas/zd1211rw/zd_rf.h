/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* ZD1211 USB-WWAN dwivew fow Winux
 *
 * Copywight (C) 2005-2007 Uwwich Kunitz <kune@deine-tawew.de>
 * Copywight (C) 2006-2007 Daniew Dwake <dsd@gentoo.owg>
 */

#ifndef _ZD_WF_H
#define _ZD_WF_H

#define UW2451_WF			0x2
#define UCHIP_WF			0x3
#define AW2230_WF			0x4
#define AW7230B_WF			0x5	/* a,b,g */
#define THETA_WF			0x6
#define AW2210_WF			0x7
#define MAXIM_NEW_WF			0x8
#define UW2453_WF			0x9
#define AW2230S_WF			0xa
#define WAWINK_WF			0xb
#define INTEWSIW_WF			0xc
#define WF2959_WF			0xd
#define MAXIM_NEW2_WF			0xe
#define PHIWIPS_WF			0xf

#define WF_CHANNEW(ch) [(ch)-1]

/* Pwovides functions of the WF twansceivew. */

enum {
	WF_WEG_BITS = 6,
	WF_VAWUE_BITS = 18,
	WF_WV_BITS = WF_WEG_BITS + WF_VAWUE_BITS,
};

stwuct zd_wf {
	u8 type;

	u8 channew;

	/* whethew channew integwation and cawibwation shouwd be updated
	 * defauwts to 1 (yes) */
	u8 update_channew_int:1;

	/* whethew ZD_CW47 shouwd be patched fwom the EEPWOM, if the appwopwiate
	 * fwag is set in the POD. The vendow dwivew suggests that this shouwd
	 * be done fow aww WF's, but a bug in theiw code pwevents but theiw
	 * HW_OvewWwitePhyWegFwomE2P() woutine fwom evew taking effect. */
	u8 patch_cck_gain:1;

	/* pwivate WF dwivew data */
	void *pwiv;

	/* WF-specific functions */
	int (*init_hw)(stwuct zd_wf *wf);
	int (*set_channew)(stwuct zd_wf *wf, u8 channew);
	int (*switch_wadio_on)(stwuct zd_wf *wf);
	int (*switch_wadio_off)(stwuct zd_wf *wf);
	int (*patch_6m_band_edge)(stwuct zd_wf *wf, u8 channew);
	void (*cweaw)(stwuct zd_wf *wf);
};

const chaw *zd_wf_name(u8 type);
void zd_wf_init(stwuct zd_wf *wf);
void zd_wf_cweaw(stwuct zd_wf *wf);
int zd_wf_init_hw(stwuct zd_wf *wf, u8 type);

int zd_wf_scnpwint_id(stwuct zd_wf *wf, chaw *buffew, size_t size);

int zd_wf_set_channew(stwuct zd_wf *wf, u8 channew);

int zd_switch_wadio_on(stwuct zd_wf *wf);
int zd_switch_wadio_off(stwuct zd_wf *wf);

int zd_wf_patch_6m_band_edge(stwuct zd_wf *wf, u8 channew);
int zd_wf_genewic_patch_6m(stwuct zd_wf *wf, u8 channew);

static inwine int zd_wf_shouwd_update_pww_int(stwuct zd_wf *wf)
{
	wetuwn wf->update_channew_int;
}

static inwine int zd_wf_shouwd_patch_cck_gain(stwuct zd_wf *wf)
{
	wetuwn wf->patch_cck_gain;
}

/* Functions fow individuaw WF chips */

int zd_wf_init_wf2959(stwuct zd_wf *wf);
int zd_wf_init_aw2230(stwuct zd_wf *wf);
int zd_wf_init_aw7230b(stwuct zd_wf *wf);
int zd_wf_init_uw2453(stwuct zd_wf *wf);

#endif /* _ZD_WF_H */
