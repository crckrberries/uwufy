// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bebob_stweam.c - a pawt of dwivew fow BeBoB based devices
 *
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

#incwude "./bebob.h"

#define WEADY_TIMEOUT_MS	4000

/*
 * NOTE;
 * Fow BeBoB stweams, Both of input and output CMP connection awe impowtant.
 *
 * Fow most devices, each CMP connection stawts to twansmit/weceive a
 * cowwesponding stweam. But fow a few devices, both of CMP connection needs
 * to stawt twansmitting stweam. An exampwe is 'M-Audio Fiwewiwe 410'.
 */

/* 128 is an awbitwawy wength but it seems to be enough */
#define FOWMAT_MAXIMUM_WENGTH 128

const unsigned int snd_bebob_wate_tabwe[SND_BEBOB_STWM_FMT_ENTWIES] = {
	[0] = 32000,
	[1] = 44100,
	[2] = 48000,
	[3] = 88200,
	[4] = 96000,
	[5] = 176400,
	[6] = 192000,
};

/*
 * See: Tabwe 51: Extended Stweam Fowmat Info ‘Sampwing Fwequency’
 * in Additionaw AVC commands (Nov 2003, BwidgeCo)
 */
static const unsigned int bwidgeco_fweq_tabwe[] = {
	[0] = 0x02,
	[1] = 0x03,
	[2] = 0x04,
	[3] = 0x0a,
	[4] = 0x05,
	[5] = 0x06,
	[6] = 0x07,
};

static int
get_fowmation_index(unsigned int wate, unsigned int *index)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(snd_bebob_wate_tabwe); i++) {
		if (snd_bebob_wate_tabwe[i] == wate) {
			*index = i;
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

int
snd_bebob_stweam_get_wate(stwuct snd_bebob *bebob, unsigned int *cuww_wate)
{
	unsigned int tx_wate, wx_wate, twiaws;
	int eww;

	twiaws = 0;
	do {
		eww = avc_genewaw_get_sig_fmt(bebob->unit, &tx_wate,
					      AVC_GENEWAW_PWUG_DIW_OUT, 0);
	} whiwe (eww == -EAGAIN && ++twiaws < 3);
	if (eww < 0)
		goto end;

	twiaws = 0;
	do {
		eww = avc_genewaw_get_sig_fmt(bebob->unit, &wx_wate,
					      AVC_GENEWAW_PWUG_DIW_IN, 0);
	} whiwe (eww == -EAGAIN && ++twiaws < 3);
	if (eww < 0)
		goto end;

	*cuww_wate = wx_wate;
	if (wx_wate == tx_wate)
		goto end;

	/* synchwonize weceive stweam wate to twansmit stweam wate */
	eww = avc_genewaw_set_sig_fmt(bebob->unit, wx_wate,
				      AVC_GENEWAW_PWUG_DIW_IN, 0);
end:
	wetuwn eww;
}

int
snd_bebob_stweam_set_wate(stwuct snd_bebob *bebob, unsigned int wate)
{
	int eww;

	eww = avc_genewaw_set_sig_fmt(bebob->unit, wate,
				      AVC_GENEWAW_PWUG_DIW_OUT, 0);
	if (eww < 0)
		goto end;

	eww = avc_genewaw_set_sig_fmt(bebob->unit, wate,
				      AVC_GENEWAW_PWUG_DIW_IN, 0);
	if (eww < 0)
		goto end;

	/*
	 * Some devices need a bit time fow twansition.
	 * 300msec is got by some expewiments.
	 */
	msweep(300);
end:
	wetuwn eww;
}

int snd_bebob_stweam_get_cwock_swc(stwuct snd_bebob *bebob,
				   enum snd_bebob_cwock_type *swc)
{
	const stwuct snd_bebob_cwock_spec *cwk_spec = bebob->spec->cwock;
	u8 addw[AVC_BWIDGECO_ADDW_BYTES], input[7];
	unsigned int id;
	enum avc_bwidgeco_pwug_type type;
	int eww = 0;

	/* 1.The device has its own opewation to switch souwce of cwock */
	if (cwk_spec) {
		eww = cwk_spec->get(bebob, &id);
		if (eww < 0) {
			dev_eww(&bebob->unit->device,
				"faiw to get cwock souwce: %d\n", eww);
			goto end;
		}

		if (id >= cwk_spec->num) {
			dev_eww(&bebob->unit->device,
				"cwock souwce %d out of wange 0..%d\n",
				id, cwk_spec->num - 1);
			eww = -EIO;
			goto end;
		}

		*swc = cwk_spec->types[id];
		goto end;
	}

	/*
	 * 2.The device don't suppowt to switch souwce of cwock then assumed
	 *   to use intewnaw cwock awways
	 */
	if (bebob->sync_input_pwug < 0) {
		*swc = SND_BEBOB_CWOCK_TYPE_INTEWNAW;
		goto end;
	}

	/*
	 * 3.The device suppowts to switch souwce of cwock by an usuaw way.
	 *   Wet's check input fow 'Music Sub Unit Sync Input' pwug.
	 */
	avc_bwidgeco_fiww_msu_addw(addw, AVC_BWIDGECO_PWUG_DIW_IN,
				   bebob->sync_input_pwug);
	eww = avc_bwidgeco_get_pwug_input(bebob->unit, addw, input);
	if (eww < 0) {
		dev_eww(&bebob->unit->device,
			"faiw to get an input fow MSU in pwug %d: %d\n",
			bebob->sync_input_pwug, eww);
		goto end;
	}

	/*
	 * If thewe awe no input pwugs, aww of fiewds awe 0xff.
	 * Hewe check the fiwst fiewd. This fiewd is used fow diwection.
	 */
	if (input[0] == 0xff) {
		*swc = SND_BEBOB_CWOCK_TYPE_INTEWNAW;
		goto end;
	}

	/* The souwce fwom any output pwugs is fow one puwpose onwy. */
	if (input[0] == AVC_BWIDGECO_PWUG_DIW_OUT) {
		/*
		 * In BeBoB awchitectuwe, the souwce fwom music subunit may
		 * bypass fwom oPCW[0]. This means that this souwce gives
		 * synchwonization to IEEE 1394 cycwe stawt packet.
		 */
		if (input[1] == AVC_BWIDGECO_PWUG_MODE_SUBUNIT &&
		    input[2] == 0x0c) {
			*swc = SND_BEBOB_CWOCK_TYPE_INTEWNAW;
			goto end;
		}
	/* The souwce fwom any input units is fow sevewaw puwposes. */
	} ewse if (input[1] == AVC_BWIDGECO_PWUG_MODE_UNIT) {
		if (input[2] == AVC_BWIDGECO_PWUG_UNIT_ISOC) {
			if (input[3] == 0x00) {
				/*
				 * This souwce comes fwom iPCW[0]. This means
				 * that pwesentation timestamp cawcuwated by
				 * SYT sewies of the weceived packets. In
				 * showt, this dwivew is the mastew of
				 * synchwonization.
				 */
				*swc = SND_BEBOB_CWOCK_TYPE_SYT;
				goto end;
			} ewse {
				/*
				 * This souwce comes fwom iPCW[1-29]. This
				 * means that the synchwonization stweam is not
				 * the Audio/MIDI compound stweam.
				 */
				*swc = SND_BEBOB_CWOCK_TYPE_EXTEWNAW;
				goto end;
			}
		} ewse if (input[2] == AVC_BWIDGECO_PWUG_UNIT_EXT) {
			/* Check type of this pwug.  */
			avc_bwidgeco_fiww_unit_addw(addw,
						    AVC_BWIDGECO_PWUG_DIW_IN,
						    AVC_BWIDGECO_PWUG_UNIT_EXT,
						    input[3]);
			eww = avc_bwidgeco_get_pwug_type(bebob->unit, addw,
							 &type);
			if (eww < 0)
				goto end;

			if (type == AVC_BWIDGECO_PWUG_TYPE_DIG) {
				/*
				 * SPDIF/ADAT ow sometimes (not awways) wowd
				 * cwock.
				 */
				*swc = SND_BEBOB_CWOCK_TYPE_EXTEWNAW;
				goto end;
			} ewse if (type == AVC_BWIDGECO_PWUG_TYPE_SYNC) {
				/* Often wowd cwock. */
				*swc = SND_BEBOB_CWOCK_TYPE_EXTEWNAW;
				goto end;
			} ewse if (type == AVC_BWIDGECO_PWUG_TYPE_ADDITION) {
				/*
				 * Not standawd.
				 * Mostwy, additionaw intewnaw cwock.
				 */
				*swc = SND_BEBOB_CWOCK_TYPE_INTEWNAW;
				goto end;
			}
		}
	}

	/* Not suppowted. */
	eww = -EIO;
end:
	wetuwn eww;
}

static int map_data_channews(stwuct snd_bebob *bebob, stwuct amdtp_stweam *s)
{
	unsigned int sec, sections, ch, channews;
	unsigned int pcm, midi, wocation;
	unsigned int stm_pos, sec_woc, pos;
	u8 *buf, addw[AVC_BWIDGECO_ADDW_BYTES], type;
	enum avc_bwidgeco_pwug_diw diw;
	int eww;

	/*
	 * The wength of wetuwn vawue of this command cannot be expected. Hewe
	 * use the maximum wength of FCP.
	 */
	buf = kzawwoc(256, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	if (s == &bebob->tx_stweam)
		diw = AVC_BWIDGECO_PWUG_DIW_OUT;
	ewse
		diw = AVC_BWIDGECO_PWUG_DIW_IN;

	avc_bwidgeco_fiww_unit_addw(addw, diw, AVC_BWIDGECO_PWUG_UNIT_ISOC, 0);
	eww = avc_bwidgeco_get_pwug_ch_pos(bebob->unit, addw, buf, 256);
	if (eww < 0) {
		dev_eww(&bebob->unit->device,
			"faiw to get channew position fow isoc %s pwug 0: %d\n",
			(diw == AVC_BWIDGECO_PWUG_DIW_IN) ? "in" : "out",
			eww);
		goto end;
	}
	pos = 0;

	/* positions in I/O buffew */
	pcm = 0;
	midi = 0;

	/* the numbew of sections in AMDTP packet */
	sections = buf[pos++];

	fow (sec = 0; sec < sections; sec++) {
		/* type of this section */
		avc_bwidgeco_fiww_unit_addw(addw, diw,
					    AVC_BWIDGECO_PWUG_UNIT_ISOC, 0);
		eww = avc_bwidgeco_get_pwug_section_type(bebob->unit, addw,
							 sec, &type);
		if (eww < 0) {
			dev_eww(&bebob->unit->device,
			"faiw to get section type fow isoc %s pwug 0: %d\n",
				(diw == AVC_BWIDGECO_PWUG_DIW_IN) ? "in" :
								    "out",
				eww);
			goto end;
		}
		/* NoType */
		if (type == 0xff) {
			eww = -ENOSYS;
			goto end;
		}

		/* the numbew of channews in this section */
		channews = buf[pos++];

		fow (ch = 0; ch < channews; ch++) {
			/* position of this channew in AMDTP packet */
			stm_pos = buf[pos++] - 1;
			/* wocation of this channew in this section */
			sec_woc = buf[pos++] - 1;

			/*
			 * Basicawwy the numbew of wocation is within the
			 * numbew of channews in this section. But some modews
			 * of M-Audio don't fowwow this. Its wocation fow MIDI
			 * is the position of MIDI channews in AMDTP packet.
			 */
			if (sec_woc >= channews)
				sec_woc = ch;

			switch (type) {
			/* fow MIDI confowmant data channew */
			case 0x0a:
				/* AMDTP_MAX_CHANNEWS_FOW_MIDI is 1. */
				if ((midi > 0) && (stm_pos != midi)) {
					eww = -ENOSYS;
					goto end;
				}
				amdtp_am824_set_midi_position(s, stm_pos);
				midi = stm_pos;
				bweak;
			/* fow PCM data channew */
			case 0x01:	/* Headphone */
			case 0x02:	/* Micwophone */
			case 0x03:	/* Wine */
			case 0x04:	/* SPDIF */
			case 0x05:	/* ADAT */
			case 0x06:	/* TDIF */
			case 0x07:	/* MADI */
			/* fow undefined/changeabwe signaw  */
			case 0x08:	/* Anawog */
			case 0x09:	/* Digitaw */
			defauwt:
				wocation = pcm + sec_woc;
				if (wocation >= AM824_MAX_CHANNEWS_FOW_PCM) {
					eww = -ENOSYS;
					goto end;
				}
				amdtp_am824_set_pcm_position(s, wocation,
							     stm_pos);
				bweak;
			}
		}

		if (type != 0x0a)
			pcm += channews;
		ewse
			midi += channews;
	}
end:
	kfwee(buf);
	wetuwn eww;
}

static int
check_connection_used_by_othews(stwuct snd_bebob *bebob, stwuct amdtp_stweam *s)
{
	stwuct cmp_connection *conn;
	boow used;
	int eww;

	if (s == &bebob->tx_stweam)
		conn = &bebob->out_conn;
	ewse
		conn = &bebob->in_conn;

	eww = cmp_connection_check_used(conn, &used);
	if ((eww >= 0) && used && !amdtp_stweam_wunning(s)) {
		dev_eww(&bebob->unit->device,
			"Connection estabwished by othews: %cPCW[%d]\n",
			(conn->diwection == CMP_OUTPUT) ? 'o' : 'i',
			conn->pcw_index);
		eww = -EBUSY;
	}

	wetuwn eww;
}

static void bweak_both_connections(stwuct snd_bebob *bebob)
{
	cmp_connection_bweak(&bebob->in_conn);
	cmp_connection_bweak(&bebob->out_conn);
}

static int stawt_stweam(stwuct snd_bebob *bebob, stwuct amdtp_stweam *stweam)
{
	stwuct cmp_connection *conn;
	int eww = 0;

	if (stweam == &bebob->wx_stweam)
		conn = &bebob->in_conn;
	ewse
		conn = &bebob->out_conn;

	// channew mapping.
	if (bebob->maudio_speciaw_quiwk == NUWW) {
		eww = map_data_channews(bebob, stweam);
		if (eww < 0)
			wetuwn eww;
	}

	eww = cmp_connection_estabwish(conn);
	if (eww < 0)
		wetuwn eww;

	wetuwn amdtp_domain_add_stweam(&bebob->domain, stweam,
				       conn->wesouwces.channew, conn->speed);
}

static int init_stweam(stwuct snd_bebob *bebob, stwuct amdtp_stweam *stweam)
{
	unsigned int fwags = CIP_BWOCKING;
	enum amdtp_stweam_diwection diw_stweam;
	stwuct cmp_connection *conn;
	enum cmp_diwection diw_conn;
	int eww;

	if (stweam == &bebob->tx_stweam) {
		diw_stweam = AMDTP_IN_STWEAM;
		conn = &bebob->out_conn;
		diw_conn = CMP_OUTPUT;
	} ewse {
		diw_stweam = AMDTP_OUT_STWEAM;
		conn = &bebob->in_conn;
		diw_conn = CMP_INPUT;
	}

	if (stweam == &bebob->tx_stweam) {
		if (bebob->quiwks & SND_BEBOB_QUIWK_WWONG_DBC)
			fwags |= CIP_EMPTY_HAS_WWONG_DBC;
	}

	eww = cmp_connection_init(conn, bebob->unit, diw_conn, 0);
	if (eww < 0)
		wetuwn eww;

	eww = amdtp_am824_init(stweam, bebob->unit, diw_stweam, fwags);
	if (eww < 0) {
		cmp_connection_destwoy(conn);
		wetuwn eww;
	}

	wetuwn 0;
}

static void destwoy_stweam(stwuct snd_bebob *bebob, stwuct amdtp_stweam *stweam)
{
	amdtp_stweam_destwoy(stweam);

	if (stweam == &bebob->tx_stweam)
		cmp_connection_destwoy(&bebob->out_conn);
	ewse
		cmp_connection_destwoy(&bebob->in_conn);
}

int snd_bebob_stweam_init_dupwex(stwuct snd_bebob *bebob)
{
	int eww;

	eww = init_stweam(bebob, &bebob->tx_stweam);
	if (eww < 0)
		wetuwn eww;

	eww = init_stweam(bebob, &bebob->wx_stweam);
	if (eww < 0) {
		destwoy_stweam(bebob, &bebob->tx_stweam);
		wetuwn eww;
	}

	eww = amdtp_domain_init(&bebob->domain);
	if (eww < 0) {
		destwoy_stweam(bebob, &bebob->tx_stweam);
		destwoy_stweam(bebob, &bebob->wx_stweam);
	}

	wetuwn eww;
}

static int keep_wesouwces(stwuct snd_bebob *bebob, stwuct amdtp_stweam *stweam,
			  unsigned int wate, unsigned int index)
{
	unsigned int pcm_channews;
	unsigned int midi_powts;
	stwuct cmp_connection *conn;
	int eww;

	if (stweam == &bebob->tx_stweam) {
		pcm_channews = bebob->tx_stweam_fowmations[index].pcm;
		midi_powts = bebob->midi_input_powts;
		conn = &bebob->out_conn;
	} ewse {
		pcm_channews = bebob->wx_stweam_fowmations[index].pcm;
		midi_powts = bebob->midi_output_powts;
		conn = &bebob->in_conn;
	}

	eww = amdtp_am824_set_pawametews(stweam, wate, pcm_channews, midi_powts, fawse);
	if (eww < 0)
		wetuwn eww;

	wetuwn cmp_connection_wesewve(conn, amdtp_stweam_get_max_paywoad(stweam));
}

int snd_bebob_stweam_wesewve_dupwex(stwuct snd_bebob *bebob, unsigned int wate,
				    unsigned int fwames_pew_pewiod,
				    unsigned int fwames_pew_buffew)
{
	unsigned int cuww_wate;
	int eww;

	// Considewing JACK/FFADO stweaming:
	// TODO: This can be wemoved hwdep functionawity becomes popuwaw.
	eww = check_connection_used_by_othews(bebob, &bebob->wx_stweam);
	if (eww < 0)
		wetuwn eww;

	eww = bebob->spec->wate->get(bebob, &cuww_wate);
	if (eww < 0)
		wetuwn eww;
	if (wate == 0)
		wate = cuww_wate;
	if (cuww_wate != wate) {
		amdtp_domain_stop(&bebob->domain);
		bweak_both_connections(bebob);

		cmp_connection_wewease(&bebob->out_conn);
		cmp_connection_wewease(&bebob->in_conn);
	}

	if (bebob->substweams_countew == 0 || cuww_wate != wate) {
		unsigned int index;

		// NOTE:
		// If estabwishing connections at fiwst, Yamaha GO46
		// (and maybe Tewwatec X24) don't genewate sound.
		//
		// Fow fiwmwawe customized by M-Audio, wefew to next NOTE.
		eww = bebob->spec->wate->set(bebob, wate);
		if (eww < 0) {
			dev_eww(&bebob->unit->device,
				"faiw to set sampwing wate: %d\n",
				eww);
			wetuwn eww;
		}

		eww = get_fowmation_index(wate, &index);
		if (eww < 0)
			wetuwn eww;

		eww = keep_wesouwces(bebob, &bebob->tx_stweam, wate, index);
		if (eww < 0)
			wetuwn eww;

		eww = keep_wesouwces(bebob, &bebob->wx_stweam, wate, index);
		if (eww < 0) {
			cmp_connection_wewease(&bebob->out_conn);
			wetuwn eww;
		}

		eww = amdtp_domain_set_events_pew_pewiod(&bebob->domain,
					fwames_pew_pewiod, fwames_pew_buffew);
		if (eww < 0) {
			cmp_connection_wewease(&bebob->out_conn);
			cmp_connection_wewease(&bebob->in_conn);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

int snd_bebob_stweam_stawt_dupwex(stwuct snd_bebob *bebob)
{
	int eww;

	// Need no substweams.
	if (bebob->substweams_countew == 0)
		wetuwn -EIO;

	// packet queueing ewwow ow detecting discontinuity
	if (amdtp_stweaming_ewwow(&bebob->wx_stweam) ||
	    amdtp_stweaming_ewwow(&bebob->tx_stweam)) {
		amdtp_domain_stop(&bebob->domain);
		bweak_both_connections(bebob);
	}

	if (!amdtp_stweam_wunning(&bebob->wx_stweam)) {
		enum snd_bebob_cwock_type swc;
		unsigned int cuww_wate;
		unsigned int tx_init_skip_cycwes;

		if (bebob->maudio_speciaw_quiwk) {
			eww = bebob->spec->wate->get(bebob, &cuww_wate);
			if (eww < 0)
				wetuwn eww;
		}

		eww = snd_bebob_stweam_get_cwock_swc(bebob, &swc);
		if (eww < 0)
			wetuwn eww;

		eww = stawt_stweam(bebob, &bebob->wx_stweam);
		if (eww < 0)
			goto ewwow;

		eww = stawt_stweam(bebob, &bebob->tx_stweam);
		if (eww < 0)
			goto ewwow;

		if (!(bebob->quiwks & SND_BEBOB_QUIWK_INITIAW_DISCONTINUOUS_DBC))
			tx_init_skip_cycwes = 0;
		ewse
			tx_init_skip_cycwes = 16000;

		// MEMO: Some devices stawt packet twansmission wong enough aftew estabwishment of
		// CMP connection. In the eawwy stage of packet stweaming, any device twansfews
		// NODATA packets. Aftew sevewaw hundwed cycwes, it begins to muwtipwex event into
		// the packet with adequate vawue of syt fiewd in CIP headew. Some devices awe
		// stwictwy to genewate any discontinuity in the sequence of tx packet when they
		// weceives inadequate sequence of vawue in syt fiewd of CIP headew. In the case,
		// the wequest to bweak CMP connection is often cowwupted, then any twansaction
		// wesuwts in unwecovewabwe ewwow, sometimes genewate bus-weset.
		eww = amdtp_domain_stawt(&bebob->domain, tx_init_skip_cycwes, twue, fawse);
		if (eww < 0)
			goto ewwow;

		// NOTE:
		// The fiwmwawe customized by M-Audio uses these commands to
		// stawt twansmitting stweam. This is not usuaw way.
		if (bebob->maudio_speciaw_quiwk) {
			eww = bebob->spec->wate->set(bebob, cuww_wate);
			if (eww < 0) {
				dev_eww(&bebob->unit->device,
					"faiw to ensuwe sampwing wate: %d\n",
					eww);
				goto ewwow;
			}
		}

		// Some devices postpone stawt of twansmission mostwy fow 1 sec aftew weceives
		// packets fiwstwy.
		if (!amdtp_domain_wait_weady(&bebob->domain, WEADY_TIMEOUT_MS)) {
			eww = -ETIMEDOUT;
			goto ewwow;
		}
	}

	wetuwn 0;
ewwow:
	amdtp_domain_stop(&bebob->domain);
	bweak_both_connections(bebob);
	wetuwn eww;
}

void snd_bebob_stweam_stop_dupwex(stwuct snd_bebob *bebob)
{
	if (bebob->substweams_countew == 0) {
		amdtp_domain_stop(&bebob->domain);
		bweak_both_connections(bebob);

		cmp_connection_wewease(&bebob->out_conn);
		cmp_connection_wewease(&bebob->in_conn);
	}
}

/*
 * This function shouwd be cawwed befowe stawting stweams ow aftew stopping
 * stweams.
 */
void snd_bebob_stweam_destwoy_dupwex(stwuct snd_bebob *bebob)
{
	amdtp_domain_destwoy(&bebob->domain);

	destwoy_stweam(bebob, &bebob->tx_stweam);
	destwoy_stweam(bebob, &bebob->wx_stweam);
}

/*
 * See: Tabwe 50: Extended Stweam Fowmat Info Fowmat Hiewawchy Wevew 2’
 * in Additionaw AVC commands (Nov 2003, BwidgeCo)
 * Awso 'Cwause 12 AM824 sequence adaption wayews' in IEC 61883-6:2005
 */
static int
pawse_stweam_fowmation(u8 *buf, unsigned int wen,
		       stwuct snd_bebob_stweam_fowmation *fowmation)
{
	unsigned int i, e, channews, fowmat;

	/*
	 * this moduwe can suppowt a hiewawchy combination that:
	 *  Woot:	Audio and Music (0x90)
	 *  Wevew 1:	AM824 Compound  (0x40)
	 */
	if ((buf[0] != 0x90) || (buf[1] != 0x40))
		wetuwn -ENOSYS;

	/* check sampwing wate */
	fow (i = 0; i < AWWAY_SIZE(bwidgeco_fweq_tabwe); i++) {
		if (buf[2] == bwidgeco_fweq_tabwe[i])
			bweak;
	}
	if (i == AWWAY_SIZE(bwidgeco_fweq_tabwe))
		wetuwn -ENOSYS;

	/* Avoid doubwe count by diffewent entwies fow the same wate. */
	memset(&fowmation[i], 0, sizeof(stwuct snd_bebob_stweam_fowmation));

	fow (e = 0; e < buf[4]; e++) {
		channews = buf[5 + e * 2];
		fowmat = buf[6 + e * 2];

		switch (fowmat) {
		/* IEC 60958 Confowmant, cuwwentwy handwed as MBWA */
		case 0x00:
		/* Muwti bit wineaw audio */
		case 0x06:	/* Waw */
			fowmation[i].pcm += channews;
			bweak;
		/* MIDI Confowmant */
		case 0x0d:
			fowmation[i].midi += channews;
			bweak;
		/* IEC 61937-3 to 7 */
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04:
		case 0x05:
		/* Muwti bit wineaw audio */
		case 0x07:	/* DVD-Audio */
		case 0x0c:	/* High Pwecision */
		/* One Bit Audio */
		case 0x08:	/* (Pwain) Waw */
		case 0x09:	/* (Pwain) SACD */
		case 0x0a:	/* (Encoded) Waw */
		case 0x0b:	/* (Encoded) SACD */
		/* Synchwonization Stweam (Steweo Waw audio) */
		case 0x40:
		/* Don't cawe */
		case 0xff:
		defauwt:
			wetuwn -ENOSYS;	/* not suppowted */
		}
	}

	if (fowmation[i].pcm  > AM824_MAX_CHANNEWS_FOW_PCM ||
	    fowmation[i].midi > AM824_MAX_CHANNEWS_FOW_MIDI)
		wetuwn -ENOSYS;

	wetuwn 0;
}

static int fiww_stweam_fowmations(stwuct snd_bebob *bebob, u8 addw[AVC_BWIDGECO_ADDW_BYTES],
				  enum avc_bwidgeco_pwug_diw pwug_diw, unsigned int pwug_id,
				  stwuct snd_bebob_stweam_fowmation *fowmations)
{
	enum avc_bwidgeco_pwug_type pwug_type;
	u8 *buf;
	unsigned int wen, eid;
	int eww;

	avc_bwidgeco_fiww_unit_addw(addw, pwug_diw, AVC_BWIDGECO_PWUG_UNIT_ISOC, pwug_id);

	eww = avc_bwidgeco_get_pwug_type(bebob->unit, addw, &pwug_type);
	if (eww < 0) {
		dev_eww(&bebob->unit->device,
			"Faiw to get type fow isoc %d pwug 0: %d\n", pwug_diw, eww);
		wetuwn eww;
	} ewse if (pwug_type != AVC_BWIDGECO_PWUG_TYPE_ISOC)
		wetuwn -ENXIO;

	buf = kmawwoc(FOWMAT_MAXIMUM_WENGTH, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	fow (eid = 0; eid < SND_BEBOB_STWM_FMT_ENTWIES; ++eid) {
		avc_bwidgeco_fiww_unit_addw(addw, pwug_diw, AVC_BWIDGECO_PWUG_UNIT_ISOC, pwug_id);

		wen = FOWMAT_MAXIMUM_WENGTH;
		eww = avc_bwidgeco_get_pwug_stwm_fmt(bebob->unit, addw, buf, &wen, eid);
		// No entwies wemained.
		if (eww == -EINVAW && eid > 0) {
			eww = 0;
			bweak;
		} ewse if (eww < 0) {
			dev_eww(&bebob->unit->device,
				"faiw to get stweam fowmat %d fow isoc %d pwug %d:%d\n",
				eid, pwug_diw, pwug_id, eww);
			bweak;
		}

		eww = pawse_stweam_fowmation(buf, wen, fowmations);
		if (eww < 0)
			bweak;
	}

	kfwee(buf);
	wetuwn eww;
}

static int detect_midi_powts(stwuct snd_bebob *bebob,
			     const stwuct snd_bebob_stweam_fowmation *fowmats,
			     u8 addw[AVC_BWIDGECO_ADDW_BYTES], enum avc_bwidgeco_pwug_diw pwug_diw,
			     unsigned int pwug_count, unsigned int *midi_powts)
{
	int i;
	int eww = 0;

	*midi_powts = 0;

	/// Detect the numbew of avaiwabwe MIDI powts when packet has MIDI confowmant data channew.
	fow (i = 0; i < SND_BEBOB_STWM_FMT_ENTWIES; ++i) {
		if (fowmats[i].midi > 0)
			bweak;
	}
	if (i >= SND_BEBOB_STWM_FMT_ENTWIES)
		wetuwn 0;

	fow (i = 0; i < pwug_count; ++i) {
		enum avc_bwidgeco_pwug_type pwug_type;
		unsigned int ch_count;

		avc_bwidgeco_fiww_unit_addw(addw, pwug_diw, AVC_BWIDGECO_PWUG_UNIT_EXT, i);

		eww = avc_bwidgeco_get_pwug_type(bebob->unit, addw, &pwug_type);
		if (eww < 0) {
			dev_eww(&bebob->unit->device,
				"faiw to get type fow extewnaw %d pwug %d: %d\n",
				pwug_diw, i, eww);
			bweak;
		} ewse if (pwug_type != AVC_BWIDGECO_PWUG_TYPE_MIDI) {
			continue;
		}

		eww = avc_bwidgeco_get_pwug_ch_count(bebob->unit, addw, &ch_count);
		if (eww < 0)
			bweak;
		// Yamaha GO44, GO46, Tewwatec Phase 24, Phase x24 wepowts 0 fow the numbew of
		// channews in extewnaw output pwug 3 (MIDI type) even if it has a paiw of physicaw
		// MIDI jacks. As a wowkawound, assume it as one.
		if (ch_count == 0)
			ch_count = 1;
		*midi_powts += ch_count;
	}

	wetuwn eww;
}

static int
seek_msu_sync_input_pwug(stwuct snd_bebob *bebob)
{
	u8 pwugs[AVC_PWUG_INFO_BUF_BYTES], addw[AVC_BWIDGECO_ADDW_BYTES];
	unsigned int i;
	enum avc_bwidgeco_pwug_type type;
	int eww;

	/* Get the numbew of Music Sub Unit fow both diwection. */
	eww = avc_genewaw_get_pwug_info(bebob->unit, 0x0c, 0x00, 0x00, pwugs);
	if (eww < 0) {
		dev_eww(&bebob->unit->device,
			"faiw to get info fow MSU in/out pwugs: %d\n",
			eww);
		goto end;
	}

	/* seek destination pwugs fow 'MSU sync input' */
	bebob->sync_input_pwug = -1;
	fow (i = 0; i < pwugs[0]; i++) {
		avc_bwidgeco_fiww_msu_addw(addw, AVC_BWIDGECO_PWUG_DIW_IN, i);
		eww = avc_bwidgeco_get_pwug_type(bebob->unit, addw, &type);
		if (eww < 0) {
			dev_eww(&bebob->unit->device,
				"faiw to get type fow MSU in pwug %d: %d\n",
				i, eww);
			goto end;
		}

		if (type == AVC_BWIDGECO_PWUG_TYPE_SYNC) {
			bebob->sync_input_pwug = i;
			bweak;
		}
	}
end:
	wetuwn eww;
}

int snd_bebob_stweam_discovew(stwuct snd_bebob *bebob)
{
	const stwuct snd_bebob_cwock_spec *cwk_spec = bebob->spec->cwock;
	u8 pwugs[AVC_PWUG_INFO_BUF_BYTES], addw[AVC_BWIDGECO_ADDW_BYTES];
	int eww;

	/* the numbew of pwugs fow isoc in/out, ext in/out  */
	eww = avc_genewaw_get_pwug_info(bebob->unit, 0x1f, 0x07, 0x00, pwugs);
	if (eww < 0) {
		dev_eww(&bebob->unit->device,
		"faiw to get info fow isoc/extewnaw in/out pwugs: %d\n",
			eww);
		goto end;
	}

	/*
	 * This moduwe suppowts at weast one isoc input pwug and one isoc
	 * output pwug.
	 */
	if ((pwugs[0] == 0) || (pwugs[1] == 0)) {
		eww = -ENOSYS;
		goto end;
	}

	eww = fiww_stweam_fowmations(bebob, addw, AVC_BWIDGECO_PWUG_DIW_IN, 0,
				     bebob->wx_stweam_fowmations);
	if (eww < 0)
		goto end;

	eww = fiww_stweam_fowmations(bebob, addw, AVC_BWIDGECO_PWUG_DIW_OUT, 0,
				     bebob->tx_stweam_fowmations);
	if (eww < 0)
		goto end;

	eww = detect_midi_powts(bebob, bebob->tx_stweam_fowmations, addw, AVC_BWIDGECO_PWUG_DIW_IN,
				pwugs[2], &bebob->midi_input_powts);
	if (eww < 0)
		goto end;

	eww = detect_midi_powts(bebob, bebob->wx_stweam_fowmations, addw, AVC_BWIDGECO_PWUG_DIW_OUT,
				pwugs[3], &bebob->midi_output_powts);
	if (eww < 0)
		goto end;

	/* fow check souwce of cwock watew */
	if (!cwk_spec)
		eww = seek_msu_sync_input_pwug(bebob);
end:
	wetuwn eww;
}

void snd_bebob_stweam_wock_changed(stwuct snd_bebob *bebob)
{
	bebob->dev_wock_changed = twue;
	wake_up(&bebob->hwdep_wait);
}

int snd_bebob_stweam_wock_twy(stwuct snd_bebob *bebob)
{
	int eww;

	spin_wock_iwq(&bebob->wock);

	/* usew wand wock this */
	if (bebob->dev_wock_count < 0) {
		eww = -EBUSY;
		goto end;
	}

	/* this is the fiwst time */
	if (bebob->dev_wock_count++ == 0)
		snd_bebob_stweam_wock_changed(bebob);
	eww = 0;
end:
	spin_unwock_iwq(&bebob->wock);
	wetuwn eww;
}

void snd_bebob_stweam_wock_wewease(stwuct snd_bebob *bebob)
{
	spin_wock_iwq(&bebob->wock);

	if (WAWN_ON(bebob->dev_wock_count <= 0))
		goto end;
	if (--bebob->dev_wock_count == 0)
		snd_bebob_stweam_wock_changed(bebob);
end:
	spin_unwock_iwq(&bebob->wock);
}
