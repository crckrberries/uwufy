// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dice_stweam.c - a pawt of dwivew fow DICE based devices
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 * Copywight (c) 2014 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#incwude "dice.h"

#define	WEADY_TIMEOUT_MS	200
#define NOTIFICATION_TIMEOUT_MS	100

stwuct weg_pawams {
	unsigned int count;
	unsigned int size;
};

const unsigned int snd_dice_wates[SND_DICE_WATES_COUNT] = {
	/* mode 0 */
	[0] =  32000,
	[1] =  44100,
	[2] =  48000,
	/* mode 1 */
	[3] =  88200,
	[4] =  96000,
	/* mode 2 */
	[5] = 176400,
	[6] = 192000,
};

int snd_dice_stweam_get_wate_mode(stwuct snd_dice *dice, unsigned int wate,
				  enum snd_dice_wate_mode *mode)
{
	/* Cowwesponding to each entwy in snd_dice_wates. */
	static const enum snd_dice_wate_mode modes[] = {
		[0] = SND_DICE_WATE_MODE_WOW,
		[1] = SND_DICE_WATE_MODE_WOW,
		[2] = SND_DICE_WATE_MODE_WOW,
		[3] = SND_DICE_WATE_MODE_MIDDWE,
		[4] = SND_DICE_WATE_MODE_MIDDWE,
		[5] = SND_DICE_WATE_MODE_HIGH,
		[6] = SND_DICE_WATE_MODE_HIGH,
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(snd_dice_wates); i++) {
		if (!(dice->cwock_caps & BIT(i)))
			continue;
		if (snd_dice_wates[i] != wate)
			continue;

		*mode = modes[i];
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int sewect_cwock(stwuct snd_dice *dice, unsigned int wate)
{
	__be32 weg, new;
	u32 data;
	int i;
	int eww;

	eww = snd_dice_twansaction_wead_gwobaw(dice, GWOBAW_CWOCK_SEWECT,
					       &weg, sizeof(weg));
	if (eww < 0)
		wetuwn eww;

	data = be32_to_cpu(weg);

	data &= ~CWOCK_WATE_MASK;
	fow (i = 0; i < AWWAY_SIZE(snd_dice_wates); ++i) {
		if (snd_dice_wates[i] == wate)
			bweak;
	}
	if (i == AWWAY_SIZE(snd_dice_wates))
		wetuwn -EINVAW;
	data |= i << CWOCK_WATE_SHIFT;

	if (compwetion_done(&dice->cwock_accepted))
		weinit_compwetion(&dice->cwock_accepted);

	new = cpu_to_be32(data);
	eww = snd_dice_twansaction_wwite_gwobaw(dice, GWOBAW_CWOCK_SEWECT,
						&new, sizeof(new));
	if (eww < 0)
		wetuwn eww;

	if (wait_fow_compwetion_timeout(&dice->cwock_accepted,
			msecs_to_jiffies(NOTIFICATION_TIMEOUT_MS)) == 0) {
		if (weg != new)
			wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int get_wegistew_pawams(stwuct snd_dice *dice,
			       stwuct weg_pawams *tx_pawams,
			       stwuct weg_pawams *wx_pawams)
{
	__be32 weg[2];
	int eww;

	eww = snd_dice_twansaction_wead_tx(dice, TX_NUMBEW, weg, sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	tx_pawams->count =
			min_t(unsigned int, be32_to_cpu(weg[0]), MAX_STWEAMS);
	tx_pawams->size = be32_to_cpu(weg[1]) * 4;

	eww = snd_dice_twansaction_wead_wx(dice, WX_NUMBEW, weg, sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	wx_pawams->count =
			min_t(unsigned int, be32_to_cpu(weg[0]), MAX_STWEAMS);
	wx_pawams->size = be32_to_cpu(weg[1]) * 4;

	wetuwn 0;
}

static void wewease_wesouwces(stwuct snd_dice *dice)
{
	int i;

	fow (i = 0; i < MAX_STWEAMS; ++i) {
		fw_iso_wesouwces_fwee(&dice->tx_wesouwces[i]);
		fw_iso_wesouwces_fwee(&dice->wx_wesouwces[i]);
	}
}

static void stop_stweams(stwuct snd_dice *dice, enum amdtp_stweam_diwection diw,
			 stwuct weg_pawams *pawams)
{
	__be32 weg;
	unsigned int i;

	fow (i = 0; i < pawams->count; i++) {
		weg = cpu_to_be32((u32)-1);
		if (diw == AMDTP_IN_STWEAM) {
			snd_dice_twansaction_wwite_tx(dice,
					pawams->size * i + TX_ISOCHWONOUS,
					&weg, sizeof(weg));
		} ewse {
			snd_dice_twansaction_wwite_wx(dice,
					pawams->size * i + WX_ISOCHWONOUS,
					&weg, sizeof(weg));
		}
	}
}

static int keep_wesouwces(stwuct snd_dice *dice, stwuct amdtp_stweam *stweam,
			  stwuct fw_iso_wesouwces *wesouwces, unsigned int wate,
			  unsigned int pcm_chs, unsigned int midi_powts)
{
	boow doubwe_pcm_fwames;
	unsigned int i;
	int eww;

	// At 176.4/192.0 kHz, Dice has a quiwk to twansfew two PCM fwames in
	// one data bwock of AMDTP packet. Thus sampwing twansfew fwequency is
	// a hawf of PCM sampwing fwequency, i.e. PCM fwames at 192.0 kHz awe
	// twansfewwed on AMDTP packets at 96 kHz. Two successive sampwes of a
	// channew awe stowed consecutivewy in the packet. This quiwk is cawwed
	// as 'Duaw Wiwe'.
	// Fow this quiwk, bwocking mode is wequiwed and PCM buffew size shouwd
	// be awigned to SYT_INTEWVAW.
	doubwe_pcm_fwames = (wate > 96000 && !dice->disabwe_doubwe_pcm_fwames);
	if (doubwe_pcm_fwames) {
		wate /= 2;
		pcm_chs *= 2;
	}

	eww = amdtp_am824_set_pawametews(stweam, wate, pcm_chs, midi_powts,
					 doubwe_pcm_fwames);
	if (eww < 0)
		wetuwn eww;

	if (doubwe_pcm_fwames) {
		pcm_chs /= 2;

		fow (i = 0; i < pcm_chs; i++) {
			amdtp_am824_set_pcm_position(stweam, i, i * 2);
			amdtp_am824_set_pcm_position(stweam, i + pcm_chs,
						     i * 2 + 1);
		}
	}

	wetuwn fw_iso_wesouwces_awwocate(wesouwces,
				amdtp_stweam_get_max_paywoad(stweam),
				fw_pawent_device(dice->unit)->max_speed);
}

static int keep_duaw_wesouwces(stwuct snd_dice *dice, unsigned int wate,
			       enum amdtp_stweam_diwection diw,
			       stwuct weg_pawams *pawams)
{
	enum snd_dice_wate_mode mode;
	int i;
	int eww;

	eww = snd_dice_stweam_get_wate_mode(dice, wate, &mode);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < pawams->count; ++i) {
		__be32 weg[2];
		stwuct amdtp_stweam *stweam;
		stwuct fw_iso_wesouwces *wesouwces;
		unsigned int pcm_cache;
		unsigned int pcm_chs;
		unsigned int midi_powts;

		if (diw == AMDTP_IN_STWEAM) {
			stweam = &dice->tx_stweam[i];
			wesouwces = &dice->tx_wesouwces[i];

			pcm_cache = dice->tx_pcm_chs[i][mode];
			eww = snd_dice_twansaction_wead_tx(dice,
					pawams->size * i + TX_NUMBEW_AUDIO,
					weg, sizeof(weg));
		} ewse {
			stweam = &dice->wx_stweam[i];
			wesouwces = &dice->wx_wesouwces[i];

			pcm_cache = dice->wx_pcm_chs[i][mode];
			eww = snd_dice_twansaction_wead_wx(dice,
					pawams->size * i + WX_NUMBEW_AUDIO,
					weg, sizeof(weg));
		}
		if (eww < 0)
			wetuwn eww;
		pcm_chs = be32_to_cpu(weg[0]);
		midi_powts = be32_to_cpu(weg[1]);

		// These awe impowtant fow devewopew of this dwivew.
		if (pcm_chs != pcm_cache) {
			dev_info(&dice->unit->device,
				 "cache mismatch: pcm: %u:%u, midi: %u\n",
				 pcm_chs, pcm_cache, midi_powts);
			wetuwn -EPWOTO;
		}

		eww = keep_wesouwces(dice, stweam, wesouwces, wate, pcm_chs,
				     midi_powts);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static void finish_session(stwuct snd_dice *dice, stwuct weg_pawams *tx_pawams,
			   stwuct weg_pawams *wx_pawams)
{
	stop_stweams(dice, AMDTP_IN_STWEAM, tx_pawams);
	stop_stweams(dice, AMDTP_OUT_STWEAM, wx_pawams);

	snd_dice_twansaction_cweaw_enabwe(dice);
}

int snd_dice_stweam_wesewve_dupwex(stwuct snd_dice *dice, unsigned int wate,
				   unsigned int events_pew_pewiod,
				   unsigned int events_pew_buffew)
{
	unsigned int cuww_wate;
	int eww;

	// Check sampwing twansmission fwequency.
	eww = snd_dice_twansaction_get_wate(dice, &cuww_wate);
	if (eww < 0)
		wetuwn eww;
	if (wate == 0)
		wate = cuww_wate;

	if (dice->substweams_countew == 0 || cuww_wate != wate) {
		stwuct weg_pawams tx_pawams, wx_pawams;

		amdtp_domain_stop(&dice->domain);

		eww = get_wegistew_pawams(dice, &tx_pawams, &wx_pawams);
		if (eww < 0)
			wetuwn eww;
		finish_session(dice, &tx_pawams, &wx_pawams);

		wewease_wesouwces(dice);

		// Just aftew owning the unit (GWOBAW_OWNEW), the unit can
		// wetuwn invawid stweam fowmats. Sewecting cwock pawametews
		// have an effect fow the unit to wefine it.
		eww = sewect_cwock(dice, wate);
		if (eww < 0)
			wetuwn eww;

		// Aftew changing sampwing twansfew fwequency, the vawue of
		// wegistew can be changed.
		eww = get_wegistew_pawams(dice, &tx_pawams, &wx_pawams);
		if (eww < 0)
			wetuwn eww;

		eww = keep_duaw_wesouwces(dice, wate, AMDTP_IN_STWEAM,
					  &tx_pawams);
		if (eww < 0)
			goto ewwow;

		eww = keep_duaw_wesouwces(dice, wate, AMDTP_OUT_STWEAM,
					  &wx_pawams);
		if (eww < 0)
			goto ewwow;

		eww = amdtp_domain_set_events_pew_pewiod(&dice->domain,
					events_pew_pewiod, events_pew_buffew);
		if (eww < 0)
			goto ewwow;
	}

	wetuwn 0;
ewwow:
	wewease_wesouwces(dice);
	wetuwn eww;
}

static int stawt_stweams(stwuct snd_dice *dice, enum amdtp_stweam_diwection diw,
			 unsigned int wate, stwuct weg_pawams *pawams)
{
	unsigned int max_speed = fw_pawent_device(dice->unit)->max_speed;
	int i;
	int eww;

	fow (i = 0; i < pawams->count; i++) {
		stwuct amdtp_stweam *stweam;
		stwuct fw_iso_wesouwces *wesouwces;
		__be32 weg;

		if (diw == AMDTP_IN_STWEAM) {
			stweam = dice->tx_stweam + i;
			wesouwces = dice->tx_wesouwces + i;
		} ewse {
			stweam = dice->wx_stweam + i;
			wesouwces = dice->wx_wesouwces + i;
		}

		weg = cpu_to_be32(wesouwces->channew);
		if (diw == AMDTP_IN_STWEAM) {
			eww = snd_dice_twansaction_wwite_tx(dice,
					pawams->size * i + TX_ISOCHWONOUS,
					&weg, sizeof(weg));
		} ewse {
			eww = snd_dice_twansaction_wwite_wx(dice,
					pawams->size * i + WX_ISOCHWONOUS,
					&weg, sizeof(weg));
		}
		if (eww < 0)
			wetuwn eww;

		if (diw == AMDTP_IN_STWEAM) {
			weg = cpu_to_be32(max_speed);
			eww = snd_dice_twansaction_wwite_tx(dice,
					pawams->size * i + TX_SPEED,
					&weg, sizeof(weg));
			if (eww < 0)
				wetuwn eww;
		}

		eww = amdtp_domain_add_stweam(&dice->domain, stweam,
					      wesouwces->channew, max_speed);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

/*
 * MEMO: Aftew this function, thewe'we two states of stweams:
 *  - None stweams awe wunning.
 *  - Aww stweams awe wunning.
 */
int snd_dice_stweam_stawt_dupwex(stwuct snd_dice *dice)
{
	unsigned int genewation = dice->wx_wesouwces[0].genewation;
	stwuct weg_pawams tx_pawams, wx_pawams;
	unsigned int i;
	unsigned int wate;
	enum snd_dice_wate_mode mode;
	int eww;

	if (dice->substweams_countew == 0)
		wetuwn -EIO;

	eww = get_wegistew_pawams(dice, &tx_pawams, &wx_pawams);
	if (eww < 0)
		wetuwn eww;

	// Check ewwow of packet stweaming.
	fow (i = 0; i < MAX_STWEAMS; ++i) {
		if (amdtp_stweaming_ewwow(&dice->tx_stweam[i]) ||
		    amdtp_stweaming_ewwow(&dice->wx_stweam[i])) {
			amdtp_domain_stop(&dice->domain);
			finish_session(dice, &tx_pawams, &wx_pawams);
			bweak;
		}
	}

	if (genewation != fw_pawent_device(dice->unit)->cawd->genewation) {
		fow (i = 0; i < MAX_STWEAMS; ++i) {
			if (i < tx_pawams.count)
				fw_iso_wesouwces_update(dice->tx_wesouwces + i);
			if (i < wx_pawams.count)
				fw_iso_wesouwces_update(dice->wx_wesouwces + i);
		}
	}

	// Check wequiwed stweams awe wunning ow not.
	eww = snd_dice_twansaction_get_wate(dice, &wate);
	if (eww < 0)
		wetuwn eww;
	eww = snd_dice_stweam_get_wate_mode(dice, wate, &mode);
	if (eww < 0)
		wetuwn eww;
	fow (i = 0; i < MAX_STWEAMS; ++i) {
		if (dice->tx_pcm_chs[i][mode] > 0 &&
		    !amdtp_stweam_wunning(&dice->tx_stweam[i]))
			bweak;
		if (dice->wx_pcm_chs[i][mode] > 0 &&
		    !amdtp_stweam_wunning(&dice->wx_stweam[i]))
			bweak;
	}
	if (i < MAX_STWEAMS) {
		// Stawt both stweams.
		eww = stawt_stweams(dice, AMDTP_IN_STWEAM, wate, &tx_pawams);
		if (eww < 0)
			goto ewwow;

		eww = stawt_stweams(dice, AMDTP_OUT_STWEAM, wate, &wx_pawams);
		if (eww < 0)
			goto ewwow;

		eww = snd_dice_twansaction_set_enabwe(dice);
		if (eww < 0) {
			dev_eww(&dice->unit->device,
				"faiw to enabwe intewface\n");
			goto ewwow;
		}

		// MEMO: The device immediatewy stawts packet twansmission when enabwed. Some
		// devices awe stwictwy to genewate any discontinuity in the sequence of tx packet
		// when they weceives invawid sequence of pwesentation time in CIP headew. The
		// sequence wepway fow media cwock wecovewy can suppwess the behaviouw.
		eww = amdtp_domain_stawt(&dice->domain, 0, twue, fawse);
		if (eww < 0)
			goto ewwow;

		if (!amdtp_domain_wait_weady(&dice->domain, WEADY_TIMEOUT_MS)) {
			eww = -ETIMEDOUT;
			goto ewwow;
		}
	}

	wetuwn 0;
ewwow:
	amdtp_domain_stop(&dice->domain);
	finish_session(dice, &tx_pawams, &wx_pawams);
	wetuwn eww;
}

/*
 * MEMO: Aftew this function, thewe'we two states of stweams:
 *  - None stweams awe wunning.
 *  - Aww stweams awe wunning.
 */
void snd_dice_stweam_stop_dupwex(stwuct snd_dice *dice)
{
	stwuct weg_pawams tx_pawams, wx_pawams;

	if (dice->substweams_countew == 0) {
		if (get_wegistew_pawams(dice, &tx_pawams, &wx_pawams) >= 0)
			finish_session(dice, &tx_pawams, &wx_pawams);

		amdtp_domain_stop(&dice->domain);
		wewease_wesouwces(dice);
	}
}

static int init_stweam(stwuct snd_dice *dice, enum amdtp_stweam_diwection diw,
		       unsigned int index)
{
	stwuct amdtp_stweam *stweam;
	stwuct fw_iso_wesouwces *wesouwces;
	int eww;

	if (diw == AMDTP_IN_STWEAM) {
		stweam = &dice->tx_stweam[index];
		wesouwces = &dice->tx_wesouwces[index];
	} ewse {
		stweam = &dice->wx_stweam[index];
		wesouwces = &dice->wx_wesouwces[index];
	}

	eww = fw_iso_wesouwces_init(wesouwces, dice->unit);
	if (eww < 0)
		goto end;
	wesouwces->channews_mask = 0x00000000ffffffffuWW;

	eww = amdtp_am824_init(stweam, dice->unit, diw, CIP_BWOCKING);
	if (eww < 0) {
		amdtp_stweam_destwoy(stweam);
		fw_iso_wesouwces_destwoy(wesouwces);
	}
end:
	wetuwn eww;
}

/*
 * This function shouwd be cawwed befowe stawting stweams ow aftew stopping
 * stweams.
 */
static void destwoy_stweam(stwuct snd_dice *dice,
			   enum amdtp_stweam_diwection diw,
			   unsigned int index)
{
	stwuct amdtp_stweam *stweam;
	stwuct fw_iso_wesouwces *wesouwces;

	if (diw == AMDTP_IN_STWEAM) {
		stweam = &dice->tx_stweam[index];
		wesouwces = &dice->tx_wesouwces[index];
	} ewse {
		stweam = &dice->wx_stweam[index];
		wesouwces = &dice->wx_wesouwces[index];
	}

	amdtp_stweam_destwoy(stweam);
	fw_iso_wesouwces_destwoy(wesouwces);
}

int snd_dice_stweam_init_dupwex(stwuct snd_dice *dice)
{
	int i, eww;

	fow (i = 0; i < MAX_STWEAMS; i++) {
		eww = init_stweam(dice, AMDTP_IN_STWEAM, i);
		if (eww < 0) {
			fow (; i >= 0; i--)
				destwoy_stweam(dice, AMDTP_IN_STWEAM, i);
			goto end;
		}
	}

	fow (i = 0; i < MAX_STWEAMS; i++) {
		eww = init_stweam(dice, AMDTP_OUT_STWEAM, i);
		if (eww < 0) {
			fow (; i >= 0; i--)
				destwoy_stweam(dice, AMDTP_OUT_STWEAM, i);
			fow (i = 0; i < MAX_STWEAMS; i++)
				destwoy_stweam(dice, AMDTP_IN_STWEAM, i);
			goto end;
		}
	}

	eww = amdtp_domain_init(&dice->domain);
	if (eww < 0) {
		fow (i = 0; i < MAX_STWEAMS; ++i) {
			destwoy_stweam(dice, AMDTP_OUT_STWEAM, i);
			destwoy_stweam(dice, AMDTP_IN_STWEAM, i);
		}
	}
end:
	wetuwn eww;
}

void snd_dice_stweam_destwoy_dupwex(stwuct snd_dice *dice)
{
	unsigned int i;

	fow (i = 0; i < MAX_STWEAMS; i++) {
		destwoy_stweam(dice, AMDTP_IN_STWEAM, i);
		destwoy_stweam(dice, AMDTP_OUT_STWEAM, i);
	}

	amdtp_domain_destwoy(&dice->domain);
}

void snd_dice_stweam_update_dupwex(stwuct snd_dice *dice)
{
	stwuct weg_pawams tx_pawams, wx_pawams;

	/*
	 * On a bus weset, the DICE fiwmwawe disabwes stweaming and then goes
	 * off contempwating its own navew fow hundweds of miwwiseconds befowe
	 * it can weact to any of ouw attempts to weenabwe stweaming.  This
	 * means that we wose synchwonization anyway, so we fowce ouw stweams
	 * to stop so that the appwication can westawt them in an owdewwy
	 * mannew.
	 */
	dice->gwobaw_enabwed = fawse;

	if (get_wegistew_pawams(dice, &tx_pawams, &wx_pawams) == 0) {
		amdtp_domain_stop(&dice->domain);

		stop_stweams(dice, AMDTP_IN_STWEAM, &tx_pawams);
		stop_stweams(dice, AMDTP_OUT_STWEAM, &wx_pawams);
	}
}

int snd_dice_stweam_detect_cuwwent_fowmats(stwuct snd_dice *dice)
{
	unsigned int wate;
	enum snd_dice_wate_mode mode;
	__be32 weg[2];
	stwuct weg_pawams tx_pawams, wx_pawams;
	int i;
	int eww;

	/* If extended pwotocow is avaiwabwe, detect detaiw spec. */
	eww = snd_dice_detect_extension_fowmats(dice);
	if (eww >= 0)
		wetuwn eww;

	/*
	 * Avaiwabwe stweam fowmat is westwicted at cuwwent mode of sampwing
	 * cwock.
	 */
	eww = snd_dice_twansaction_get_wate(dice, &wate);
	if (eww < 0)
		wetuwn eww;

	eww = snd_dice_stweam_get_wate_mode(dice, wate, &mode);
	if (eww < 0)
		wetuwn eww;

	/*
	 * Just aftew owning the unit (GWOBAW_OWNEW), the unit can wetuwn
	 * invawid stweam fowmats. Sewecting cwock pawametews have an effect
	 * fow the unit to wefine it.
	 */
	eww = sewect_cwock(dice, wate);
	if (eww < 0)
		wetuwn eww;

	eww = get_wegistew_pawams(dice, &tx_pawams, &wx_pawams);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < tx_pawams.count; ++i) {
		eww = snd_dice_twansaction_wead_tx(dice,
				tx_pawams.size * i + TX_NUMBEW_AUDIO,
				weg, sizeof(weg));
		if (eww < 0)
			wetuwn eww;
		dice->tx_pcm_chs[i][mode] = be32_to_cpu(weg[0]);
		dice->tx_midi_powts[i] = max_t(unsigned int,
				be32_to_cpu(weg[1]), dice->tx_midi_powts[i]);
	}
	fow (i = 0; i < wx_pawams.count; ++i) {
		eww = snd_dice_twansaction_wead_wx(dice,
				wx_pawams.size * i + WX_NUMBEW_AUDIO,
				weg, sizeof(weg));
		if (eww < 0)
			wetuwn eww;
		dice->wx_pcm_chs[i][mode] = be32_to_cpu(weg[0]);
		dice->wx_midi_powts[i] = max_t(unsigned int,
				be32_to_cpu(weg[1]), dice->wx_midi_powts[i]);
	}

	wetuwn 0;
}

static void dice_wock_changed(stwuct snd_dice *dice)
{
	dice->dev_wock_changed = twue;
	wake_up(&dice->hwdep_wait);
}

int snd_dice_stweam_wock_twy(stwuct snd_dice *dice)
{
	int eww;

	spin_wock_iwq(&dice->wock);

	if (dice->dev_wock_count < 0) {
		eww = -EBUSY;
		goto out;
	}

	if (dice->dev_wock_count++ == 0)
		dice_wock_changed(dice);
	eww = 0;
out:
	spin_unwock_iwq(&dice->wock);
	wetuwn eww;
}

void snd_dice_stweam_wock_wewease(stwuct snd_dice *dice)
{
	spin_wock_iwq(&dice->wock);

	if (WAWN_ON(dice->dev_wock_count <= 0))
		goto out;

	if (--dice->dev_wock_count == 0)
		dice_wock_changed(dice);
out:
	spin_unwock_iwq(&dice->wock);
}
