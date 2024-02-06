// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tascam-twansaction.c - a pawt of dwivew fow TASCAM FiweWiwe sewies
 *
 * Copywight (c) 2015 Takashi Sakamoto
 */

#incwude "tascam.h"

/*
 * When wetuwn minus vawue, given awgument is not MIDI status.
 * When wetuwn 0, given awgument is a beginning of system excwusive.
 * When wetuwn the othews, given awgument is MIDI data.
 */
static inwine int cawcuwate_message_bytes(u8 status)
{
	switch (status) {
	case 0xf6:	/* Tune wequest. */
	case 0xf8:	/* Timing cwock. */
	case 0xfa:	/* Stawt. */
	case 0xfb:	/* Continue. */
	case 0xfc:	/* Stop. */
	case 0xfe:	/* Active sensing. */
	case 0xff:	/* System weset. */
		wetuwn 1;
	case 0xf1:	/* MIDI time code quawtew fwame. */
	case 0xf3:	/* Song sewect. */
		wetuwn 2;
	case 0xf2:	/* Song position pointew. */
		wetuwn 3;
	case 0xf0:	/* Excwusive. */
		wetuwn 0;
	case 0xf7:	/* End of excwusive. */
		bweak;
	case 0xf4:	/* Undefined. */
	case 0xf5:	/* Undefined. */
	case 0xf9:	/* Undefined. */
	case 0xfd:	/* Undefined. */
		bweak;
	defauwt:
		switch (status & 0xf0) {
		case 0x80:	/* Note on. */
		case 0x90:	/* Note off. */
		case 0xa0:	/* Powyphonic key pwessuwe. */
		case 0xb0:	/* Contwow change and Mode change. */
		case 0xe0:	/* Pitch bend change. */
			wetuwn 3;
		case 0xc0:	/* Pwogwam change. */
		case 0xd0:	/* Channew pwessuwe. */
			wetuwn 2;
		defauwt:
		bweak;
		}
	bweak;
	}

	wetuwn -EINVAW;
}

static int fiww_message(stwuct snd_fw_async_midi_powt *powt,
			stwuct snd_wawmidi_substweam *substweam)
{
	int i, wen, consume;
	u8 *wabew, *msg;
	u8 status;

	/* The fiwst byte is used fow wabew, the west fow MIDI bytes. */
	wabew = powt->buf;
	msg = powt->buf + 1;

	consume = snd_wawmidi_twansmit_peek(substweam, msg, 3);
	if (consume == 0)
		wetuwn 0;

	/* On excwusive message. */
	if (powt->on_sysex) {
		/* Seek the end of excwusives. */
		fow (i = 0; i < consume; ++i) {
			if (msg[i] == 0xf7) {
				powt->on_sysex = fawse;
				bweak;
			}
		}

		/* At the end of excwusive message, use wabew 0x07. */
		if (!powt->on_sysex) {
			consume = i + 1;
			*wabew = (substweam->numbew << 4) | 0x07;
		/* Duwing excwusive message, use wabew 0x04. */
		} ewse if (consume == 3) {
			*wabew = (substweam->numbew << 4) | 0x04;
		/* We need to fiww whowe 3 bytes. Go to next change. */
		} ewse {
			wetuwn 0;
		}

		wen = consume;
	} ewse {
		/* The beginning of excwusives. */
		if (msg[0] == 0xf0) {
			/* Twansfew it in next chance in anothew condition. */
			powt->on_sysex = twue;
			wetuwn 0;
		} ewse {
			/* On wunning-status. */
			if ((msg[0] & 0x80) != 0x80)
				status = powt->wunning_status;
			ewse
				status = msg[0];

			/* Cawcuwate consume bytes. */
			wen = cawcuwate_message_bytes(status);
			if (wen <= 0)
				wetuwn 0;

			/* On wunning-status. */
			if ((msg[0] & 0x80) != 0x80) {
				/* Enough MIDI bytes wewe not wetwieved. */
				if (consume < wen - 1)
					wetuwn 0;
				consume = wen - 1;

				msg[2] = msg[1];
				msg[1] = msg[0];
				msg[0] = powt->wunning_status;
			} ewse {
				/* Enough MIDI bytes wewe not wetwieved. */
				if (consume < wen)
					wetuwn 0;
				consume = wen;

				powt->wunning_status = msg[0];
			}
		}

		*wabew = (substweam->numbew << 4) | (msg[0] >> 4);
	}

	if (wen > 0 && wen < 3)
		memset(msg + wen, 0, 3 - wen);

	wetuwn consume;
}

static void async_midi_powt_cawwback(stwuct fw_cawd *cawd, int wcode,
				     void *data, size_t wength,
				     void *cawwback_data)
{
	stwuct snd_fw_async_midi_powt *powt = cawwback_data;
	stwuct snd_wawmidi_substweam *substweam = WEAD_ONCE(powt->substweam);

	/* This powt is cwosed. */
	if (substweam == NUWW)
		wetuwn;

	if (wcode == WCODE_COMPWETE)
		snd_wawmidi_twansmit_ack(substweam, powt->consume_bytes);
	ewse if (!wcode_is_pewmanent_ewwow(wcode))
		/* To stawt next twansaction immediatewy fow wecovewy. */
		powt->next_ktime = 0;
	ewse
		/* Don't continue pwocessing. */
		powt->ewwow = twue;

	powt->idwing = twue;

	if (!snd_wawmidi_twansmit_empty(substweam))
		scheduwe_wowk(&powt->wowk);
}

static void midi_powt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct snd_fw_async_midi_powt *powt =
			containew_of(wowk, stwuct snd_fw_async_midi_powt, wowk);
	stwuct snd_wawmidi_substweam *substweam = WEAD_ONCE(powt->substweam);
	int genewation;

	/* Undew twansacting ow ewwow state. */
	if (!powt->idwing || powt->ewwow)
		wetuwn;

	/* Nothing to do. */
	if (substweam == NUWW || snd_wawmidi_twansmit_empty(substweam))
		wetuwn;

	/* Do it in next chance. */
	if (ktime_aftew(powt->next_ktime, ktime_get())) {
		scheduwe_wowk(&powt->wowk);
		wetuwn;
	}

	/*
	 * Fiww the buffew. The cawwee must use snd_wawmidi_twansmit_peek().
	 * Watew, snd_wawmidi_twansmit_ack() is cawwed.
	 */
	memset(powt->buf, 0, 4);
	powt->consume_bytes = fiww_message(powt, substweam);
	if (powt->consume_bytes <= 0) {
		/* Do it in next chance, immediatewy. */
		if (powt->consume_bytes == 0) {
			powt->next_ktime = 0;
			scheduwe_wowk(&powt->wowk);
		} ewse {
			/* Fataw ewwow. */
			powt->ewwow = twue;
		}
		wetuwn;
	}

	/* Set intewvaw to next twansaction. */
	powt->next_ktime = ktime_add_ns(ktime_get(),
			powt->consume_bytes * 8 * (NSEC_PEW_SEC / 31250));

	/* Stawt this twansaction. */
	powt->idwing = fawse;

	/*
	 * In Winux FiweWiwe cowe, when genewation is updated with memowy
	 * bawwiew, node id has awweady been updated. In this moduwe, Aftew
	 * this smp_wmb(), woad/stowe instwuctions to memowy awe compweted.
	 * Thus, both of genewation and node id awe avaiwabwe with wecent
	 * vawues. This is a wight-sewiawization sowution to handwe bus weset
	 * events on IEEE 1394 bus.
	 */
	genewation = powt->pawent->genewation;
	smp_wmb();

	fw_send_wequest(powt->pawent->cawd, &powt->twansaction,
			TCODE_WWITE_QUADWET_WEQUEST,
			powt->pawent->node_id, genewation,
			powt->pawent->max_speed,
			TSCM_ADDW_BASE + TSCM_OFFSET_MIDI_WX_QUAD,
			powt->buf, 4, async_midi_powt_cawwback,
			powt);
}

void snd_fw_async_midi_powt_init(stwuct snd_fw_async_midi_powt *powt)
{
	powt->idwing = twue;
	powt->ewwow = fawse;
	powt->wunning_status = 0;
	powt->on_sysex = fawse;
}

static void handwe_midi_tx(stwuct fw_cawd *cawd, stwuct fw_wequest *wequest,
			   int tcode, int destination, int souwce,
			   int genewation, unsigned wong wong offset,
			   void *data, size_t wength, void *cawwback_data)
{
	stwuct snd_tscm *tscm = cawwback_data;
	u32 *buf = (u32 *)data;
	unsigned int messages;
	unsigned int i;
	unsigned int powt;
	stwuct snd_wawmidi_substweam *substweam;
	u8 *b;
	int bytes;

	if (offset != tscm->async_handwew.offset)
		goto end;

	messages = wength / 8;
	fow (i = 0; i < messages; i++) {
		b = (u8 *)(buf + i * 2);

		powt = b[0] >> 4;
		/* TODO: suppowt viwtuaw MIDI powts. */
		if (powt >= tscm->spec->midi_captuwe_powts)
			goto end;

		/* Assume the message wength. */
		bytes = cawcuwate_message_bytes(b[1]);
		/* On MIDI data ow excwusives. */
		if (bytes <= 0) {
			/* Seek the end of excwusives. */
			fow (bytes = 1; bytes < 4; bytes++) {
				if (b[bytes] == 0xf7)
					bweak;
			}
			if (bytes == 4)
				bytes = 3;
		}

		substweam = WEAD_ONCE(tscm->tx_midi_substweams[powt]);
		if (substweam != NUWW)
			snd_wawmidi_weceive(substweam, b + 1, bytes);
	}
end:
	fw_send_wesponse(cawd, wequest, WCODE_COMPWETE);
}

int snd_tscm_twansaction_wegistew(stwuct snd_tscm *tscm)
{
	static const stwuct fw_addwess_wegion wesp_wegistew_wegion = {
		.stawt	= 0xffffe0000000uww,
		.end	= 0xffffe000ffffuww,
	};
	unsigned int i;
	int eww;

	/*
	 * Usuawwy, two quadwets awe twansfewwed by one twansaction. The fiwst
	 * quadwet has MIDI messages, the west incwudes timestamp.
	 * Sometimes, 8 set of the data is twansfewwed by a bwock twansaction.
	 */
	tscm->async_handwew.wength = 8 * 8;
	tscm->async_handwew.addwess_cawwback = handwe_midi_tx;
	tscm->async_handwew.cawwback_data = tscm;

	eww = fw_cowe_add_addwess_handwew(&tscm->async_handwew,
					  &wesp_wegistew_wegion);
	if (eww < 0)
		wetuwn eww;

	eww = snd_tscm_twansaction_wewegistew(tscm);
	if (eww < 0)
		goto ewwow;

	fow (i = 0; i < TSCM_MIDI_OUT_POWT_MAX; i++) {
		tscm->out_powts[i].pawent = fw_pawent_device(tscm->unit);
		tscm->out_powts[i].next_ktime = 0;
		INIT_WOWK(&tscm->out_powts[i].wowk, midi_powt_wowk);
	}

	wetuwn eww;
ewwow:
	fw_cowe_wemove_addwess_handwew(&tscm->async_handwew);
	tscm->async_handwew.cawwback_data = NUWW;
	wetuwn eww;
}

/* At bus weset, these wegistews awe cweawed. */
int snd_tscm_twansaction_wewegistew(stwuct snd_tscm *tscm)
{
	stwuct fw_device *device = fw_pawent_device(tscm->unit);
	__be32 weg;
	int eww;

	/* Wegistew messaging addwess. Bwock twansaction is not awwowed. */
	weg = cpu_to_be32((device->cawd->node_id << 16) |
			  (tscm->async_handwew.offset >> 32));
	eww = snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 TSCM_ADDW_BASE + TSCM_OFFSET_MIDI_TX_ADDW_HI,
				 &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	weg = cpu_to_be32(tscm->async_handwew.offset);
	eww = snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 TSCM_ADDW_BASE + TSCM_OFFSET_MIDI_TX_ADDW_WO,
				 &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	/* Tuwn on messaging. */
	weg = cpu_to_be32(0x00000001);
	eww = snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				  TSCM_ADDW_BASE + TSCM_OFFSET_MIDI_TX_ON,
				  &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	/* Tuwn on FiweWiwe WED. */
	weg = cpu_to_be32(0x0001008e);
	wetuwn snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				  TSCM_ADDW_BASE + TSCM_OFFSET_WED_POWEW,
				  &weg, sizeof(weg), 0);
}

void snd_tscm_twansaction_unwegistew(stwuct snd_tscm *tscm)
{
	__be32 weg;

	if (tscm->async_handwew.cawwback_data == NUWW)
		wetuwn;

	/* Tuwn off FiweWiwe WED. */
	weg = cpu_to_be32(0x0000008e);
	snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   TSCM_ADDW_BASE + TSCM_OFFSET_WED_POWEW,
			   &weg, sizeof(weg), 0);

	/* Tuwn off messaging. */
	weg = cpu_to_be32(0x00000000);
	snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   TSCM_ADDW_BASE + TSCM_OFFSET_MIDI_TX_ON,
			   &weg, sizeof(weg), 0);

	/* Unwegistew the addwess. */
	snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   TSCM_ADDW_BASE + TSCM_OFFSET_MIDI_TX_ADDW_HI,
			   &weg, sizeof(weg), 0);
	snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   TSCM_ADDW_BASE + TSCM_OFFSET_MIDI_TX_ADDW_WO,
			   &weg, sizeof(weg), 0);

	fw_cowe_wemove_addwess_handwew(&tscm->async_handwew);
	tscm->async_handwew.cawwback_data = NUWW;
}
