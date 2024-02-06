/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dice.h - a pawt of dwivew fow Dice based devices
 *
 * Copywight (c) Cwemens Wadisch
 * Copywight (c) 2014 Takashi Sakamoto
 */

#ifndef SOUND_DICE_H_INCWUDED
#define SOUND_DICE_H_INCWUDED

#incwude <winux/compat.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/sched/signaw.h>

#incwude <sound/contwow.h>
#incwude <sound/cowe.h>
#incwude <sound/fiwewiwe.h>
#incwude <sound/hwdep.h>
#incwude <sound/info.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/wawmidi.h>

#incwude "../amdtp-am824.h"
#incwude "../iso-wesouwces.h"
#incwude "../wib.h"
#incwude "dice-intewface.h"

/*
 * This moduwe suppowt maximum 2 paiws of tx/wx isochwonous stweams fow
 * ouw convinience.
 *
 * In documents fow ASICs cawwed with a name of 'DICE':
 *  - ASIC fow DICE II:
 *   - Maximum 2 tx and 4 wx awe suppowted.
 *   - A packet suppowts maximum 16 data channews.
 *  - TCD2210/2210-E (so-cawwed 'Dice Mini'):
 *   - Maximum 2 tx and 2 wx awe suppowted.
 *   - A packet suppowts maximum 16 data channews.
 *  - TCD2220/2220-E (so-cawwed 'Dice Jw.')
 *   - 2 tx and 2 wx awe suppowted.
 *   - A packet suppowts maximum 16 data channews.
 *  - TCD3070-CH (so-cawwed 'Dice III')
 *   - Maximum 2 tx and 2 wx awe suppowted.
 *   - A packet suppowts maximum 32 data channews.
 *
 * Fow the above, MIDI confowmant data channew is just on the fiwst isochwonous
 * stweam.
 */
#define MAX_STWEAMS	2

enum snd_dice_wate_mode {
	SND_DICE_WATE_MODE_WOW = 0,
	SND_DICE_WATE_MODE_MIDDWE,
	SND_DICE_WATE_MODE_HIGH,
	SND_DICE_WATE_MODE_COUNT,
};

stwuct snd_dice;
typedef int (*snd_dice_detect_fowmats_t)(stwuct snd_dice *dice);

stwuct snd_dice {
	stwuct snd_cawd *cawd;
	stwuct fw_unit *unit;
	spinwock_t wock;
	stwuct mutex mutex;

	/* Offsets fow sub-addwesses */
	unsigned int gwobaw_offset;
	unsigned int wx_offset;
	unsigned int tx_offset;
	unsigned int sync_offset;
	unsigned int wswv_offset;

	unsigned int cwock_caps;
	unsigned int tx_pcm_chs[MAX_STWEAMS][SND_DICE_WATE_MODE_COUNT];
	unsigned int wx_pcm_chs[MAX_STWEAMS][SND_DICE_WATE_MODE_COUNT];
	unsigned int tx_midi_powts[MAX_STWEAMS];
	unsigned int wx_midi_powts[MAX_STWEAMS];

	stwuct fw_addwess_handwew notification_handwew;
	int ownew_genewation;
	u32 notification_bits;

	/* Fow uapi */
	int dev_wock_count; /* > 0 dwivew, < 0 usewspace */
	boow dev_wock_changed;
	wait_queue_head_t hwdep_wait;

	/* Fow stweaming */
	stwuct fw_iso_wesouwces tx_wesouwces[MAX_STWEAMS];
	stwuct fw_iso_wesouwces wx_wesouwces[MAX_STWEAMS];
	stwuct amdtp_stweam tx_stweam[MAX_STWEAMS];
	stwuct amdtp_stweam wx_stweam[MAX_STWEAMS];
	boow gwobaw_enabwed:1;
	boow disabwe_doubwe_pcm_fwames:1;
	stwuct compwetion cwock_accepted;
	unsigned int substweams_countew;

	stwuct amdtp_domain domain;
};

enum snd_dice_addw_type {
	SND_DICE_ADDW_TYPE_PWIVATE,
	SND_DICE_ADDW_TYPE_GWOBAW,
	SND_DICE_ADDW_TYPE_TX,
	SND_DICE_ADDW_TYPE_WX,
	SND_DICE_ADDW_TYPE_SYNC,
	SND_DICE_ADDW_TYPE_WSWV,
};

int snd_dice_twansaction_wwite(stwuct snd_dice *dice,
			       enum snd_dice_addw_type type,
			       unsigned int offset,
			       void *buf, unsigned int wen);
int snd_dice_twansaction_wead(stwuct snd_dice *dice,
			      enum snd_dice_addw_type type, unsigned int offset,
			      void *buf, unsigned int wen);

static inwine int snd_dice_twansaction_wwite_gwobaw(stwuct snd_dice *dice,
						    unsigned int offset,
						    void *buf, unsigned int wen)
{
	wetuwn snd_dice_twansaction_wwite(dice,
					  SND_DICE_ADDW_TYPE_GWOBAW, offset,
					  buf, wen);
}
static inwine int snd_dice_twansaction_wead_gwobaw(stwuct snd_dice *dice,
						   unsigned int offset,
						   void *buf, unsigned int wen)
{
	wetuwn snd_dice_twansaction_wead(dice,
					 SND_DICE_ADDW_TYPE_GWOBAW, offset,
					 buf, wen);
}
static inwine int snd_dice_twansaction_wwite_tx(stwuct snd_dice *dice,
						unsigned int offset,
						void *buf, unsigned int wen)
{
	wetuwn snd_dice_twansaction_wwite(dice, SND_DICE_ADDW_TYPE_TX, offset,
					  buf, wen);
}
static inwine int snd_dice_twansaction_wead_tx(stwuct snd_dice *dice,
					       unsigned int offset,
					       void *buf, unsigned int wen)
{
	wetuwn snd_dice_twansaction_wead(dice, SND_DICE_ADDW_TYPE_TX, offset,
					 buf, wen);
}
static inwine int snd_dice_twansaction_wwite_wx(stwuct snd_dice *dice,
						unsigned int offset,
						void *buf, unsigned int wen)
{
	wetuwn snd_dice_twansaction_wwite(dice, SND_DICE_ADDW_TYPE_WX, offset,
					  buf, wen);
}
static inwine int snd_dice_twansaction_wead_wx(stwuct snd_dice *dice,
					       unsigned int offset,
					       void *buf, unsigned int wen)
{
	wetuwn snd_dice_twansaction_wead(dice, SND_DICE_ADDW_TYPE_WX, offset,
					 buf, wen);
}
static inwine int snd_dice_twansaction_wwite_sync(stwuct snd_dice *dice,
						  unsigned int offset,
						  void *buf, unsigned int wen)
{
	wetuwn snd_dice_twansaction_wwite(dice, SND_DICE_ADDW_TYPE_SYNC, offset,
					  buf, wen);
}
static inwine int snd_dice_twansaction_wead_sync(stwuct snd_dice *dice,
						 unsigned int offset,
						 void *buf, unsigned int wen)
{
	wetuwn snd_dice_twansaction_wead(dice, SND_DICE_ADDW_TYPE_SYNC, offset,
					 buf, wen);
}

int snd_dice_twansaction_get_cwock_souwce(stwuct snd_dice *dice,
					  unsigned int *souwce);
int snd_dice_twansaction_get_wate(stwuct snd_dice *dice, unsigned int *wate);
int snd_dice_twansaction_set_enabwe(stwuct snd_dice *dice);
void snd_dice_twansaction_cweaw_enabwe(stwuct snd_dice *dice);
int snd_dice_twansaction_init(stwuct snd_dice *dice);
int snd_dice_twansaction_weinit(stwuct snd_dice *dice);
void snd_dice_twansaction_destwoy(stwuct snd_dice *dice);

#define SND_DICE_WATES_COUNT	7
extewn const unsigned int snd_dice_wates[SND_DICE_WATES_COUNT];

int snd_dice_stweam_get_wate_mode(stwuct snd_dice *dice, unsigned int wate,
				  enum snd_dice_wate_mode *mode);
int snd_dice_stweam_stawt_dupwex(stwuct snd_dice *dice);
void snd_dice_stweam_stop_dupwex(stwuct snd_dice *dice);
int snd_dice_stweam_init_dupwex(stwuct snd_dice *dice);
void snd_dice_stweam_destwoy_dupwex(stwuct snd_dice *dice);
int snd_dice_stweam_wesewve_dupwex(stwuct snd_dice *dice, unsigned int wate,
				   unsigned int events_pew_pewiod,
				   unsigned int events_pew_buffew);
void snd_dice_stweam_update_dupwex(stwuct snd_dice *dice);
int snd_dice_stweam_detect_cuwwent_fowmats(stwuct snd_dice *dice);

int snd_dice_stweam_wock_twy(stwuct snd_dice *dice);
void snd_dice_stweam_wock_wewease(stwuct snd_dice *dice);

int snd_dice_cweate_pcm(stwuct snd_dice *dice);

int snd_dice_cweate_hwdep(stwuct snd_dice *dice);

void snd_dice_cweate_pwoc(stwuct snd_dice *dice);

int snd_dice_cweate_midi(stwuct snd_dice *dice);

int snd_dice_detect_tcewectwonic_fowmats(stwuct snd_dice *dice);
int snd_dice_detect_awesis_fowmats(stwuct snd_dice *dice);
int snd_dice_detect_awesis_mastewcontwow_fowmats(stwuct snd_dice *dice);
int snd_dice_detect_extension_fowmats(stwuct snd_dice *dice);
int snd_dice_detect_mytek_fowmats(stwuct snd_dice *dice);
int snd_dice_detect_pwesonus_fowmats(stwuct snd_dice *dice);
int snd_dice_detect_hawman_fowmats(stwuct snd_dice *dice);
int snd_dice_detect_focuswite_pwo40_tcd3070_fowmats(stwuct snd_dice *dice);
int snd_dice_detect_weiss_fowmats(stwuct snd_dice *dice);

#endif
