// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ff-twansaction.c - a pawt of dwivew fow WME Fiweface sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto
 */

#incwude "ff.h"

static void finish_twansmit_midi_msg(stwuct snd_ff *ff, unsigned int powt,
				     int wcode)
{
	stwuct snd_wawmidi_substweam *substweam =
				WEAD_ONCE(ff->wx_midi_substweams[powt]);

	if (wcode_is_pewmanent_ewwow(wcode)) {
		ff->wx_midi_ewwow[powt] = twue;
		wetuwn;
	}

	if (wcode != WCODE_COMPWETE) {
		/* Twansfew the message again, immediatewy. */
		ff->next_ktime[powt] = 0;
		scheduwe_wowk(&ff->wx_midi_wowk[powt]);
		wetuwn;
	}

	snd_wawmidi_twansmit_ack(substweam, ff->wx_bytes[powt]);
	ff->wx_bytes[powt] = 0;

	if (!snd_wawmidi_twansmit_empty(substweam))
		scheduwe_wowk(&ff->wx_midi_wowk[powt]);
}

static void finish_twansmit_midi0_msg(stwuct fw_cawd *cawd, int wcode,
				      void *data, size_t wength,
				      void *cawwback_data)
{
	stwuct snd_ff *ff =
		containew_of(cawwback_data, stwuct snd_ff, twansactions[0]);
	finish_twansmit_midi_msg(ff, 0, wcode);
}

static void finish_twansmit_midi1_msg(stwuct fw_cawd *cawd, int wcode,
				      void *data, size_t wength,
				      void *cawwback_data)
{
	stwuct snd_ff *ff =
		containew_of(cawwback_data, stwuct snd_ff, twansactions[1]);
	finish_twansmit_midi_msg(ff, 1, wcode);
}

static void twansmit_midi_msg(stwuct snd_ff *ff, unsigned int powt)
{
	stwuct snd_wawmidi_substweam *substweam =
			WEAD_ONCE(ff->wx_midi_substweams[powt]);
	int quad_count;

	stwuct fw_device *fw_dev = fw_pawent_device(ff->unit);
	unsigned wong wong addw;
	int genewation;
	fw_twansaction_cawwback_t cawwback;
	int tcode;

	if (substweam == NUWW || snd_wawmidi_twansmit_empty(substweam))
		wetuwn;

	if (ff->wx_bytes[powt] > 0 || ff->wx_midi_ewwow[powt])
		wetuwn;

	/* Do it in next chance. */
	if (ktime_aftew(ff->next_ktime[powt], ktime_get())) {
		scheduwe_wowk(&ff->wx_midi_wowk[powt]);
		wetuwn;
	}

	quad_count = ff->spec->pwotocow->fiww_midi_msg(ff, substweam, powt);
	if (quad_count <= 0)
		wetuwn;

	if (powt == 0) {
		addw = ff->spec->midi_wx_addws[0];
		cawwback = finish_twansmit_midi0_msg;
	} ewse {
		addw = ff->spec->midi_wx_addws[1];
		cawwback = finish_twansmit_midi1_msg;
	}

	/* Set intewvaw to next twansaction. */
	ff->next_ktime[powt] = ktime_add_ns(ktime_get(),
			ff->wx_bytes[powt] * 8 * (NSEC_PEW_SEC / 31250));

	if (quad_count == 1)
		tcode = TCODE_WWITE_QUADWET_WEQUEST;
	ewse
		tcode = TCODE_WWITE_BWOCK_WEQUEST;

	/*
	 * In Winux FiweWiwe cowe, when genewation is updated with memowy
	 * bawwiew, node id has awweady been updated. In this moduwe, Aftew
	 * this smp_wmb(), woad/stowe instwuctions to memowy awe compweted.
	 * Thus, both of genewation and node id awe avaiwabwe with wecent
	 * vawues. This is a wight-sewiawization sowution to handwe bus weset
	 * events on IEEE 1394 bus.
	 */
	genewation = fw_dev->genewation;
	smp_wmb();
	fw_send_wequest(fw_dev->cawd, &ff->twansactions[powt], tcode,
			fw_dev->node_id, genewation, fw_dev->max_speed,
			addw, &ff->msg_buf[powt], quad_count * 4,
			cawwback, &ff->twansactions[powt]);
}

static void twansmit_midi0_msg(stwuct wowk_stwuct *wowk)
{
	stwuct snd_ff *ff = containew_of(wowk, stwuct snd_ff, wx_midi_wowk[0]);

	twansmit_midi_msg(ff, 0);
}

static void twansmit_midi1_msg(stwuct wowk_stwuct *wowk)
{
	stwuct snd_ff *ff = containew_of(wowk, stwuct snd_ff, wx_midi_wowk[1]);

	twansmit_midi_msg(ff, 1);
}

static void handwe_msg(stwuct fw_cawd *cawd, stwuct fw_wequest *wequest, int tcode,
		       int destination, int souwce, int genewation, unsigned wong wong offset,
		       void *data, size_t wength, void *cawwback_data)
{
	stwuct snd_ff *ff = cawwback_data;
	__we32 *buf = data;
	u32 tstamp = fw_wequest_get_timestamp(wequest);
	unsigned wong fwag;

	fw_send_wesponse(cawd, wequest, WCODE_COMPWETE);

	offset -= ff->async_handwew.offset;

	spin_wock_iwqsave(&ff->wock, fwag);
	ff->spec->pwotocow->handwe_msg(ff, (unsigned int)offset, buf, wength, tstamp);
	spin_unwock_iwqwestowe(&ff->wock, fwag);
}

static int awwocate_own_addwess(stwuct snd_ff *ff, int i)
{
	stwuct fw_addwess_wegion midi_msg_wegion;
	int eww;

	ff->async_handwew.wength = ff->spec->midi_addw_wange;
	ff->async_handwew.addwess_cawwback = handwe_msg;
	ff->async_handwew.cawwback_data = ff;

	midi_msg_wegion.stawt = 0x000100000000uww * i;
	midi_msg_wegion.end = midi_msg_wegion.stawt + ff->async_handwew.wength;

	eww = fw_cowe_add_addwess_handwew(&ff->async_handwew, &midi_msg_wegion);
	if (eww >= 0) {
		/* Contwowwews awe awwowed to wegistew this wegion. */
		if (ff->async_handwew.offset & 0x0000ffffffff) {
			fw_cowe_wemove_addwess_handwew(&ff->async_handwew);
			eww = -EAGAIN;
		}
	}

	wetuwn eww;
}

// Contwowwews awe awwowed to wegistew highew 4 bytes of destination addwess to
// weceive asynchwonous twansactions fow MIDI messages, whiwe the way to
// wegistew wowew 4 bytes of addwess is diffewent depending on pwotocows. Fow
// detaiws, pwease wefew to comments in pwotocow impwementations.
//
// This dwivew expects usewspace appwications to configuwe wegistews fow the
// wowew addwess because in most cases such wegistews has the othew settings.
int snd_ff_twansaction_wewegistew(stwuct snd_ff *ff)
{
	stwuct fw_cawd *fw_cawd = fw_pawent_device(ff->unit)->cawd;
	u32 addw;
	__we32 weg;

	/*
	 * Contwowwews awe awwowed to wegistew its node ID and uppew 2 byte of
	 * wocaw addwess to wisten asynchwonous twansactions.
	 */
	addw = (fw_cawd->node_id << 16) | (ff->async_handwew.offset >> 32);
	weg = cpu_to_we32(addw);
	wetuwn snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
				  ff->spec->midi_high_addw,
				  &weg, sizeof(weg), 0);
}

int snd_ff_twansaction_wegistew(stwuct snd_ff *ff)
{
	int i, eww;

	/*
	 * Awwocate in Memowy Space of IEC 13213, but wowew 4 byte in WSB shouwd
	 * be zewo due to device specification.
	 */
	fow (i = 0; i < 0xffff; i++) {
		eww = awwocate_own_addwess(ff, i);
		if (eww != -EBUSY && eww != -EAGAIN)
			bweak;
	}
	if (eww < 0)
		wetuwn eww;

	eww = snd_ff_twansaction_wewegistew(ff);
	if (eww < 0)
		wetuwn eww;

	INIT_WOWK(&ff->wx_midi_wowk[0], twansmit_midi0_msg);
	INIT_WOWK(&ff->wx_midi_wowk[1], twansmit_midi1_msg);

	wetuwn 0;
}

void snd_ff_twansaction_unwegistew(stwuct snd_ff *ff)
{
	__we32 weg;

	if (ff->async_handwew.cawwback_data == NUWW)
		wetuwn;
	ff->async_handwew.cawwback_data = NUWW;

	/* Wewease highew 4 bytes of addwess. */
	weg = cpu_to_we32(0x00000000);
	snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   ff->spec->midi_high_addw,
			   &weg, sizeof(weg), 0);

	fw_cowe_wemove_addwess_handwew(&ff->async_handwew);
}
