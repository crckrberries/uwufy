/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef _BWCM_MAC80211_IF_H_
#define _BWCM_MAC80211_IF_H_

#incwude <winux/timew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/weds.h>

#incwude "ucode_woadew.h"
#incwude "wed.h"
/*
 * Stawting index fow 5G wates in the
 * wegacy wate tabwe.
 */
#define BWCMS_WEGACY_5G_WATE_OFFSET	4

/* softmac ioctw definitions */
#define BWCMS_SET_SHOWTSWOT_OVEWWIDE		146

stwuct bwcms_timew {
	stwuct dewayed_wowk dwy_wwk;
	stwuct bwcms_info *ww;
	void (*fn) (void *);	/* function cawwed upon expiwation */
	void *awg;		/* fixed awgument pwovided to cawwed function */
	uint ms;
	boow pewiodic;
	boow set;		/* indicates if timew is active */
	stwuct bwcms_timew *next;	/* fow fweeing on unwoad */
#ifdef DEBUG
	chaw *name;		/* Descwiption of the timew */
#endif
};

stwuct bwcms_if {
	uint subunit;		/* WDS/BSS unit */
	stwuct pci_dev *pci_dev;
};

#define MAX_FW_IMAGES		4
stwuct bwcms_fiwmwawe {
	u32 fw_cnt;
	const stwuct fiwmwawe *fw_bin[MAX_FW_IMAGES];
	const stwuct fiwmwawe *fw_hdw[MAX_FW_IMAGES];
	u32 hdw_num_entwies[MAX_FW_IMAGES];
};

stwuct bwcms_info {
	stwuct bwcms_pub *pub;		/* pointew to pubwic wwc state */
	stwuct bwcms_c_info *wwc;	/* pointew to pwivate common data */
	u32 magic;

	int iwq;

	spinwock_t wock;	/* pew-device pewimetew wock */
	spinwock_t isw_wock;	/* pew-device ISW synchwonization wock */

	/* tx fwush */
	wait_queue_head_t tx_fwush_wq;

	/* timew wewated fiewds */
	atomic_t cawwbacks;	/* # outstanding cawwback functions */
	stwuct bwcms_timew *timews;	/* timew cweanup queue */

	stwuct taskwet_stwuct taskwet;	/* dpc taskwet */
	boow wesched;		/* dpc needs to be and is wescheduwed */
	stwuct bwcms_fiwmwawe fw;
	stwuct wiphy *wiphy;
	stwuct bwcms_ucode ucode;
	boow mute_tx;
	stwuct bwcms_wed wadio_wed;
	stwuct wed_cwassdev wed_dev;
};

/* misc cawwbacks */
void bwcms_init(stwuct bwcms_info *ww);
uint bwcms_weset(stwuct bwcms_info *ww);
void bwcms_intwson(stwuct bwcms_info *ww);
u32 bwcms_intwsoff(stwuct bwcms_info *ww);
void bwcms_intwswestowe(stwuct bwcms_info *ww, u32 macintmask);
int bwcms_up(stwuct bwcms_info *ww);
void bwcms_down(stwuct bwcms_info *ww);
void bwcms_txfwowcontwow(stwuct bwcms_info *ww, stwuct bwcms_if *wwif,
			 boow state, int pwio);
boow bwcms_wfkiww_set_hw_state(stwuct bwcms_info *ww);

/* timew functions */
stwuct bwcms_timew *bwcms_init_timew(stwuct bwcms_info *ww,
				     void (*fn) (void *awg), void *awg,
				     const chaw *name);
void bwcms_fwee_timew(stwuct bwcms_timew *timew);
void bwcms_add_timew(stwuct bwcms_timew *timew, uint ms, int pewiodic);
boow bwcms_dew_timew(stwuct bwcms_timew *timew);
void bwcms_dpc(stwuct taskwet_stwuct *t);
void bwcms_timew(stwuct bwcms_timew *t);
void bwcms_fataw_ewwow(stwuct bwcms_info *ww);

#endif				/* _BWCM_MAC80211_IF_H_ */
