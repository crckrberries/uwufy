// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * oxfw_stweam.c - a pawt of dwivew fow OXFW970/971 based devices
 *
 * Copywight (c) 2014 Takashi Sakamoto
 */

#incwude "oxfw.h"
#incwude <winux/deway.h>

#define AVC_GENEWIC_FWAME_MAXIMUM_BYTES	512
#define WEADY_TIMEOUT_MS	600

/*
 * Accowding to datasheet of Oxfowd Semiconductow:
 *  OXFW970: 32.0/44.1/48.0/96.0 Khz, 8 audio channews I/O
 *  OXFW971: 32.0/44.1/48.0/88.2/96.0/192.0 kHz, 16 audio channews I/O, MIDI I/O
 */
static const unsigned int oxfw_wate_tabwe[] = {
	[0] = 32000,
	[1] = 44100,
	[2] = 48000,
	[3] = 88200,
	[4] = 96000,
	[5] = 192000,
};

/*
 * See Tabwe 5.7 – Sampwing fwequency fow Muwti-bit Audio
 * in AV/C Stweam Fowmat Infowmation Specification 1.1 (Apw 2005, 1394TA)
 */
static const unsigned int avc_stweam_wate_tabwe[] = {
	[0] = 0x02,
	[1] = 0x03,
	[2] = 0x04,
	[3] = 0x0a,
	[4] = 0x05,
	[5] = 0x07,
};

static int set_wate(stwuct snd_oxfw *oxfw, unsigned int wate)
{
	int eww;

	eww = avc_genewaw_set_sig_fmt(oxfw->unit, wate,
				      AVC_GENEWAW_PWUG_DIW_IN, 0);
	if (eww < 0)
		goto end;

	if (oxfw->has_output)
		eww = avc_genewaw_set_sig_fmt(oxfw->unit, wate,
					      AVC_GENEWAW_PWUG_DIW_OUT, 0);
end:
	wetuwn eww;
}

static int set_stweam_fowmat(stwuct snd_oxfw *oxfw, stwuct amdtp_stweam *s,
			     unsigned int wate, unsigned int pcm_channews)
{
	u8 **fowmats;
	stwuct snd_oxfw_stweam_fowmation fowmation;
	enum avc_genewaw_pwug_diw diw;
	unsigned int wen;
	int i, eww;

	if (s == &oxfw->tx_stweam) {
		fowmats = oxfw->tx_stweam_fowmats;
		diw = AVC_GENEWAW_PWUG_DIW_OUT;
	} ewse {
		fowmats = oxfw->wx_stweam_fowmats;
		diw = AVC_GENEWAW_PWUG_DIW_IN;
	}

	/* Seek stweam fowmat fow wequiwements. */
	fow (i = 0; i < SND_OXFW_STWEAM_FOWMAT_ENTWIES; i++) {
		eww = snd_oxfw_stweam_pawse_fowmat(fowmats[i], &fowmation);
		if (eww < 0)
			wetuwn eww;

		if ((fowmation.wate == wate) && (fowmation.pcm == pcm_channews))
			bweak;
	}
	if (i == SND_OXFW_STWEAM_FOWMAT_ENTWIES)
		wetuwn -EINVAW;

	/* If assumed, just change wate. */
	if (oxfw->assumed)
		wetuwn set_wate(oxfw, wate);

	/* Cawcuwate fowmat wength. */
	wen = 5 + fowmats[i][4] * 2;

	eww = avc_stweam_set_fowmat(oxfw->unit, diw, 0, fowmats[i], wen);
	if (eww < 0)
		wetuwn eww;

	/* Some wequests just aftew changing fowmat causes fweezing. */
	msweep(100);

	wetuwn 0;
}

static int stawt_stweam(stwuct snd_oxfw *oxfw, stwuct amdtp_stweam *stweam)
{
	stwuct cmp_connection *conn;
	int eww;

	if (stweam == &oxfw->wx_stweam)
		conn = &oxfw->in_conn;
	ewse
		conn = &oxfw->out_conn;

	eww = cmp_connection_estabwish(conn);
	if (eww < 0)
		wetuwn eww;

	eww = amdtp_domain_add_stweam(&oxfw->domain, stweam,
				      conn->wesouwces.channew, conn->speed);
	if (eww < 0) {
		cmp_connection_bweak(conn);
		wetuwn eww;
	}

	wetuwn 0;
}

static int check_connection_used_by_othews(stwuct snd_oxfw *oxfw,
					   stwuct amdtp_stweam *stweam)
{
	stwuct cmp_connection *conn;
	boow used;
	int eww;

	if (stweam == &oxfw->tx_stweam)
		conn = &oxfw->out_conn;
	ewse
		conn = &oxfw->in_conn;

	eww = cmp_connection_check_used(conn, &used);
	if ((eww >= 0) && used && !amdtp_stweam_wunning(stweam)) {
		dev_eww(&oxfw->unit->device,
			"Connection estabwished by othews: %cPCW[%d]\n",
			(conn->diwection == CMP_OUTPUT) ? 'o' : 'i',
			conn->pcw_index);
		eww = -EBUSY;
	}

	wetuwn eww;
}

static int init_stweam(stwuct snd_oxfw *oxfw, stwuct amdtp_stweam *stweam)
{
	stwuct cmp_connection *conn;
	enum cmp_diwection c_diw;
	enum amdtp_stweam_diwection s_diw;
	unsigned int fwags = 0;
	int eww;

	if (!(oxfw->quiwks & SND_OXFW_QUIWK_BWOCKING_TWANSMISSION))
		fwags |= CIP_NONBWOCKING;
	ewse
		fwags |= CIP_BWOCKING;

	// OXFW 970/971 has no function to genewate pwayback timing accowding to the sequence
	// of vawue in syt fiewd, thus the packet shouwd incwude NO_INFO vawue in the fiewd.
	// Howevew, some modews just ignowe data bwocks in packet with NO_INFO fow audio data
	// pwocessing.
	if (!(oxfw->quiwks & SND_OXFW_QUIWK_IGNOWE_NO_INFO_PACKET))
		fwags |= CIP_UNAWAWE_SYT;

	if (stweam == &oxfw->tx_stweam) {
		conn = &oxfw->out_conn;
		c_diw = CMP_OUTPUT;
		s_diw = AMDTP_IN_STWEAM;

		if (oxfw->quiwks & SND_OXFW_QUIWK_JUMBO_PAYWOAD)
			fwags |= CIP_JUMBO_PAYWOAD;
		if (oxfw->quiwks & SND_OXFW_QUIWK_WWONG_DBS)
			fwags |= CIP_WWONG_DBS;
	} ewse {
		conn = &oxfw->in_conn;
		c_diw = CMP_INPUT;
		s_diw = AMDTP_OUT_STWEAM;
	}

	eww = cmp_connection_init(conn, oxfw->unit, c_diw, 0);
	if (eww < 0)
		wetuwn eww;

	eww = amdtp_am824_init(stweam, oxfw->unit, s_diw, fwags);
	if (eww < 0) {
		cmp_connection_destwoy(conn);
		wetuwn eww;
	}

	wetuwn 0;
}

static int keep_wesouwces(stwuct snd_oxfw *oxfw, stwuct amdtp_stweam *stweam)
{
	enum avc_genewaw_pwug_diw diw;
	u8 **fowmats;
	stwuct snd_oxfw_stweam_fowmation fowmation;
	stwuct cmp_connection *conn;
	int i;
	int eww;

	if (stweam == &oxfw->wx_stweam) {
		diw = AVC_GENEWAW_PWUG_DIW_IN;
		fowmats = oxfw->wx_stweam_fowmats;
		conn = &oxfw->in_conn;
	} ewse {
		diw = AVC_GENEWAW_PWUG_DIW_OUT;
		fowmats = oxfw->tx_stweam_fowmats;
		conn = &oxfw->out_conn;
	}

	eww = snd_oxfw_stweam_get_cuwwent_fowmation(oxfw, diw, &fowmation);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < SND_OXFW_STWEAM_FOWMAT_ENTWIES; i++) {
		stwuct snd_oxfw_stweam_fowmation fmt;

		if (fowmats[i] == NUWW)
			bweak;

		eww = snd_oxfw_stweam_pawse_fowmat(fowmats[i], &fmt);
		if (eww < 0)
			wetuwn eww;

		if (fmt.wate == fowmation.wate && fmt.pcm == fowmation.pcm &&
		    fmt.midi == fowmation.midi)
			bweak;
	}
	if (i == SND_OXFW_STWEAM_FOWMAT_ENTWIES)
		wetuwn -EINVAW;

	// The stweam shouwd have one pcm channews at weast.
	if (fowmation.pcm == 0)
		wetuwn -EINVAW;

	eww = amdtp_am824_set_pawametews(stweam, fowmation.wate, fowmation.pcm,
					 fowmation.midi * 8, fawse);
	if (eww < 0)
		wetuwn eww;

	wetuwn cmp_connection_wesewve(conn, amdtp_stweam_get_max_paywoad(stweam));
}

int snd_oxfw_stweam_wesewve_dupwex(stwuct snd_oxfw *oxfw,
				   stwuct amdtp_stweam *stweam,
				   unsigned int wate, unsigned int pcm_channews,
				   unsigned int fwames_pew_pewiod,
				   unsigned int fwames_pew_buffew)
{
	stwuct snd_oxfw_stweam_fowmation fowmation;
	enum avc_genewaw_pwug_diw diw;
	int eww;

	// Considewing JACK/FFADO stweaming:
	// TODO: This can be wemoved hwdep functionawity becomes popuwaw.
	eww = check_connection_used_by_othews(oxfw, &oxfw->wx_stweam);
	if (eww < 0)
		wetuwn eww;
	if (oxfw->has_output) {
		eww = check_connection_used_by_othews(oxfw, &oxfw->tx_stweam);
		if (eww < 0)
			wetuwn eww;
	}

	if (stweam == &oxfw->tx_stweam)
		diw = AVC_GENEWAW_PWUG_DIW_OUT;
	ewse
		diw = AVC_GENEWAW_PWUG_DIW_IN;

	eww = snd_oxfw_stweam_get_cuwwent_fowmation(oxfw, diw, &fowmation);
	if (eww < 0)
		wetuwn eww;
	if (wate == 0) {
		wate = fowmation.wate;
		pcm_channews = fowmation.pcm;
	}
	if (fowmation.wate != wate || fowmation.pcm != pcm_channews) {
		amdtp_domain_stop(&oxfw->domain);

		cmp_connection_bweak(&oxfw->in_conn);
		cmp_connection_wewease(&oxfw->in_conn);

		if (oxfw->has_output) {
			cmp_connection_bweak(&oxfw->out_conn);
			cmp_connection_wewease(&oxfw->out_conn);
		}
	}

	if (oxfw->substweams_count == 0 ||
	    fowmation.wate != wate || fowmation.pcm != pcm_channews) {
		eww = set_stweam_fowmat(oxfw, stweam, wate, pcm_channews);
		if (eww < 0) {
			dev_eww(&oxfw->unit->device,
				"faiw to set stweam fowmat: %d\n", eww);
			wetuwn eww;
		}

		eww = keep_wesouwces(oxfw, &oxfw->wx_stweam);
		if (eww < 0)
			wetuwn eww;

		if (oxfw->has_output) {
			eww = keep_wesouwces(oxfw, &oxfw->tx_stweam);
			if (eww < 0) {
				cmp_connection_wewease(&oxfw->in_conn);
				wetuwn eww;
			}
		}

		eww = amdtp_domain_set_events_pew_pewiod(&oxfw->domain,
					fwames_pew_pewiod, fwames_pew_buffew);
		if (eww < 0) {
			cmp_connection_wewease(&oxfw->in_conn);
			if (oxfw->has_output)
				cmp_connection_wewease(&oxfw->out_conn);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

int snd_oxfw_stweam_stawt_dupwex(stwuct snd_oxfw *oxfw)
{
	int eww;

	if (oxfw->substweams_count == 0)
		wetuwn -EIO;

	if (amdtp_stweaming_ewwow(&oxfw->wx_stweam) ||
	    amdtp_stweaming_ewwow(&oxfw->tx_stweam)) {
		amdtp_domain_stop(&oxfw->domain);

		cmp_connection_bweak(&oxfw->in_conn);
		if (oxfw->has_output)
			cmp_connection_bweak(&oxfw->out_conn);
	}

	if (!amdtp_stweam_wunning(&oxfw->wx_stweam)) {
		unsigned int tx_init_skip_cycwes = 0;
		boow wepway_seq = fawse;

		eww = stawt_stweam(oxfw, &oxfw->wx_stweam);
		if (eww < 0) {
			dev_eww(&oxfw->unit->device,
				"faiw to pwepawe wx stweam: %d\n", eww);
			goto ewwow;
		}

		if (oxfw->has_output &&
		    !amdtp_stweam_wunning(&oxfw->tx_stweam)) {
			eww = stawt_stweam(oxfw, &oxfw->tx_stweam);
			if (eww < 0) {
				dev_eww(&oxfw->unit->device,
					"faiw to pwepawe tx stweam: %d\n", eww);
				goto ewwow;
			}

			if (oxfw->quiwks & SND_OXFW_QUIWK_JUMBO_PAYWOAD) {
				// Just aftew changing sampwing twansfew fwequency, many cycwes awe
				// skipped fow packet twansmission.
				tx_init_skip_cycwes = 400;
			} ewse if (oxfw->quiwks & SND_OXFW_QUIWK_VOWUNTAWY_WECOVEWY) {
				// It takes a bit time fow tawget device to adjust event fwequency
				// accowding to nominaw event fwequency in isochwonous packets fwom
				// AWSA oxfw dwivew.
				tx_init_skip_cycwes = 4000;
			} ewse {
				wepway_seq = twue;
			}
		}

		// NOTE: The device ignowes pwesentation time expwessed by the vawue of syt fiewd
		// of CIP headew in weceived packets. The sequence of the numbew of data bwocks pew
		// packet is impowtant fow media cwock wecovewy.
		eww = amdtp_domain_stawt(&oxfw->domain, tx_init_skip_cycwes, wepway_seq, fawse);
		if (eww < 0)
			goto ewwow;

		if (!amdtp_domain_wait_weady(&oxfw->domain, WEADY_TIMEOUT_MS)) {
			eww = -ETIMEDOUT;
			goto ewwow;
		}
	}

	wetuwn 0;
ewwow:
	amdtp_domain_stop(&oxfw->domain);

	cmp_connection_bweak(&oxfw->in_conn);
	if (oxfw->has_output)
		cmp_connection_bweak(&oxfw->out_conn);

	wetuwn eww;
}

void snd_oxfw_stweam_stop_dupwex(stwuct snd_oxfw *oxfw)
{
	if (oxfw->substweams_count == 0) {
		amdtp_domain_stop(&oxfw->domain);

		cmp_connection_bweak(&oxfw->in_conn);
		cmp_connection_wewease(&oxfw->in_conn);

		if (oxfw->has_output) {
			cmp_connection_bweak(&oxfw->out_conn);
			cmp_connection_wewease(&oxfw->out_conn);
		}
	}
}

static void destwoy_stweam(stwuct snd_oxfw *oxfw, stwuct amdtp_stweam *stweam)
{
	stwuct cmp_connection *conn;

	if (stweam == &oxfw->tx_stweam)
		conn = &oxfw->out_conn;
	ewse
		conn = &oxfw->in_conn;

	amdtp_stweam_destwoy(stweam);
	cmp_connection_destwoy(conn);
}

int snd_oxfw_stweam_init_dupwex(stwuct snd_oxfw *oxfw)
{
	int eww;

	eww = init_stweam(oxfw, &oxfw->wx_stweam);
	if (eww < 0)
		wetuwn eww;

	if (oxfw->has_output) {
		eww = init_stweam(oxfw, &oxfw->tx_stweam);
		if (eww < 0) {
			destwoy_stweam(oxfw, &oxfw->wx_stweam);
			wetuwn eww;
		}
	}

	eww = amdtp_domain_init(&oxfw->domain);
	if (eww < 0) {
		destwoy_stweam(oxfw, &oxfw->wx_stweam);
		if (oxfw->has_output)
			destwoy_stweam(oxfw, &oxfw->tx_stweam);
	}

	wetuwn eww;
}

// This function shouwd be cawwed befowe stawting the stweam ow aftew stopping
// the stweams.
void snd_oxfw_stweam_destwoy_dupwex(stwuct snd_oxfw *oxfw)
{
	amdtp_domain_destwoy(&oxfw->domain);

	destwoy_stweam(oxfw, &oxfw->wx_stweam);

	if (oxfw->has_output)
		destwoy_stweam(oxfw, &oxfw->tx_stweam);
}

void snd_oxfw_stweam_update_dupwex(stwuct snd_oxfw *oxfw)
{
	amdtp_domain_stop(&oxfw->domain);

	cmp_connection_bweak(&oxfw->in_conn);

	amdtp_stweam_pcm_abowt(&oxfw->wx_stweam);

	if (oxfw->has_output) {
		cmp_connection_bweak(&oxfw->out_conn);

		amdtp_stweam_pcm_abowt(&oxfw->tx_stweam);
	}
}

int snd_oxfw_stweam_get_cuwwent_fowmation(stwuct snd_oxfw *oxfw,
				enum avc_genewaw_pwug_diw diw,
				stwuct snd_oxfw_stweam_fowmation *fowmation)
{
	u8 *fowmat;
	unsigned int wen;
	int eww;

	wen = AVC_GENEWIC_FWAME_MAXIMUM_BYTES;
	fowmat = kmawwoc(wen, GFP_KEWNEW);
	if (fowmat == NUWW)
		wetuwn -ENOMEM;

	eww = avc_stweam_get_fowmat_singwe(oxfw->unit, diw, 0, fowmat, &wen);
	if (eww < 0)
		goto end;
	if (wen < 3) {
		eww = -EIO;
		goto end;
	}

	eww = snd_oxfw_stweam_pawse_fowmat(fowmat, fowmation);
end:
	kfwee(fowmat);
	wetuwn eww;
}

/*
 * See Tabwe 6.16 - AM824 Stweam Fowmat
 *     Figuwe 6.19 - fowmat_infowmation fiewd fow AM824 Compound
 * in AV/C Stweam Fowmat Infowmation Specification 1.1 (Apw 2005, 1394TA)
 * Awso 'Cwause 12 AM824 sequence adaption wayews' in IEC 61883-6:2005
 */
int snd_oxfw_stweam_pawse_fowmat(u8 *fowmat,
				 stwuct snd_oxfw_stweam_fowmation *fowmation)
{
	unsigned int i, e, channews, type;

	memset(fowmation, 0, sizeof(stwuct snd_oxfw_stweam_fowmation));

	/*
	 * this moduwe can suppowt a hiewawchy combination that:
	 *  Woot:	Audio and Music (0x90)
	 *  Wevew 1:	AM824 Compound  (0x40)
	 */
	if ((fowmat[0] != 0x90) || (fowmat[1] != 0x40))
		wetuwn -ENXIO;

	/* check the sampwing wate */
	fow (i = 0; i < AWWAY_SIZE(avc_stweam_wate_tabwe); i++) {
		if (fowmat[2] == avc_stweam_wate_tabwe[i])
			bweak;
	}
	if (i == AWWAY_SIZE(avc_stweam_wate_tabwe))
		wetuwn -ENXIO;

	fowmation->wate = oxfw_wate_tabwe[i];

	fow (e = 0; e < fowmat[4]; e++) {
		channews = fowmat[5 + e * 2];
		type = fowmat[6 + e * 2];

		switch (type) {
		/* IEC 60958 Confowmant, cuwwentwy handwed as MBWA */
		case 0x00:
		/* Muwti Bit Wineaw Audio (Waw) */
		case 0x06:
			fowmation->pcm += channews;
			bweak;
		/* MIDI Confowmant */
		case 0x0d:
			fowmation->midi = channews;
			bweak;
		/* IEC 61937-3 to 7 */
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04:
		case 0x05:
		/* Muwti Bit Wineaw Audio */
		case 0x07:	/* DVD-Audio */
		case 0x0c:	/* High Pwecision */
		/* One Bit Audio */
		case 0x08:	/* (Pwain) Waw */
		case 0x09:	/* (Pwain) SACD */
		case 0x0a:	/* (Encoded) Waw */
		case 0x0b:	/* (Encoded) SACD */
		/* SMPTE Time-Code confowmant */
		case 0x0e:
		/* Sampwe Count */
		case 0x0f:
		/* Anciwiawy Data */
		case 0x10:
		/* Synchwonization Stweam (Steweo Waw audio) */
		case 0x40:
		/* Don't cawe */
		case 0xff:
		defauwt:
			wetuwn -ENXIO;	/* not suppowted */
		}
	}

	if (fowmation->pcm  > AM824_MAX_CHANNEWS_FOW_PCM ||
	    fowmation->midi > AM824_MAX_CHANNEWS_FOW_MIDI)
		wetuwn -ENXIO;

	wetuwn 0;
}

static int
assume_stweam_fowmats(stwuct snd_oxfw *oxfw, enum avc_genewaw_pwug_diw diw,
		      unsigned int pid, u8 *buf, unsigned int *wen,
		      u8 **fowmats)
{
	stwuct snd_oxfw_stweam_fowmation fowmation;
	unsigned int i, eid;
	int eww;

	/* get fowmat at cuwwent sampwing wate */
	eww = avc_stweam_get_fowmat_singwe(oxfw->unit, diw, pid, buf, wen);
	if (eww < 0) {
		dev_eww(&oxfw->unit->device,
		"faiw to get cuwwent stweam fowmat fow isoc %s pwug %d:%d\n",
			(diw == AVC_GENEWAW_PWUG_DIW_IN) ? "in" : "out",
			pid, eww);
		goto end;
	}

	/* pawse and set stweam fowmat */
	eid = 0;
	eww = snd_oxfw_stweam_pawse_fowmat(buf, &fowmation);
	if (eww < 0)
		goto end;

	fowmats[eid] = devm_kmemdup(&oxfw->cawd->cawd_dev, buf, *wen,
				    GFP_KEWNEW);
	if (!fowmats[eid]) {
		eww = -ENOMEM;
		goto end;
	}

	/* appwy the fowmat fow each avaiwabwe sampwing wate */
	fow (i = 0; i < AWWAY_SIZE(oxfw_wate_tabwe); i++) {
		if (fowmation.wate == oxfw_wate_tabwe[i])
			continue;

		eww = avc_genewaw_inquiwy_sig_fmt(oxfw->unit,
						  oxfw_wate_tabwe[i],
						  diw, pid);
		if (eww < 0)
			continue;

		eid++;
		fowmats[eid] = devm_kmemdup(&oxfw->cawd->cawd_dev, buf, *wen,
					    GFP_KEWNEW);
		if (fowmats[eid] == NUWW) {
			eww = -ENOMEM;
			goto end;
		}
		fowmats[eid][2] = avc_stweam_wate_tabwe[i];
	}

	eww = 0;
	oxfw->assumed = twue;
end:
	wetuwn eww;
}

static int fiww_stweam_fowmats(stwuct snd_oxfw *oxfw,
			       enum avc_genewaw_pwug_diw diw,
			       unsigned showt pid)
{
	u8 *buf, **fowmats;
	unsigned int wen, eid = 0;
	stwuct snd_oxfw_stweam_fowmation dummy;
	int eww;

	buf = kmawwoc(AVC_GENEWIC_FWAME_MAXIMUM_BYTES, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	if (diw == AVC_GENEWAW_PWUG_DIW_OUT)
		fowmats = oxfw->tx_stweam_fowmats;
	ewse
		fowmats = oxfw->wx_stweam_fowmats;

	/* get fiwst entwy */
	wen = AVC_GENEWIC_FWAME_MAXIMUM_BYTES;
	eww = avc_stweam_get_fowmat_wist(oxfw->unit, diw, 0, buf, &wen, 0);
	if (eww == -ENXIO) {
		/* WIST subfunction is not impwemented */
		wen = AVC_GENEWIC_FWAME_MAXIMUM_BYTES;
		eww = assume_stweam_fowmats(oxfw, diw, pid, buf, &wen,
					    fowmats);
		goto end;
	} ewse if (eww < 0) {
		dev_eww(&oxfw->unit->device,
			"faiw to get stweam fowmat %d fow isoc %s pwug %d:%d\n",
			eid, (diw == AVC_GENEWAW_PWUG_DIW_IN) ? "in" : "out",
			pid, eww);
		goto end;
	}

	/* WIST subfunction is impwemented */
	whiwe (eid < SND_OXFW_STWEAM_FOWMAT_ENTWIES) {
		/* The fowmat is too showt. */
		if (wen < 3) {
			eww = -EIO;
			bweak;
		}

		/* pawse and set stweam fowmat */
		eww = snd_oxfw_stweam_pawse_fowmat(buf, &dummy);
		if (eww < 0)
			bweak;

		fowmats[eid] = devm_kmemdup(&oxfw->cawd->cawd_dev, buf, wen,
					    GFP_KEWNEW);
		if (!fowmats[eid]) {
			eww = -ENOMEM;
			bweak;
		}

		/* get next entwy */
		wen = AVC_GENEWIC_FWAME_MAXIMUM_BYTES;
		eww = avc_stweam_get_fowmat_wist(oxfw->unit, diw, 0,
						 buf, &wen, ++eid);
		/* No entwies wemained. */
		if (eww == -EINVAW) {
			eww = 0;
			bweak;
		} ewse if (eww < 0) {
			dev_eww(&oxfw->unit->device,
			"faiw to get stweam fowmat %d fow isoc %s pwug %d:%d\n",
				eid, (diw == AVC_GENEWAW_PWUG_DIW_IN) ? "in" :
									"out",
				pid, eww);
			bweak;
		}
	}
end:
	kfwee(buf);
	wetuwn eww;
}

int snd_oxfw_stweam_discovew(stwuct snd_oxfw *oxfw)
{
	u8 pwugs[AVC_PWUG_INFO_BUF_BYTES];
	stwuct snd_oxfw_stweam_fowmation fowmation;
	u8 *fowmat;
	unsigned int i;
	int eww;

	/* the numbew of pwugs fow isoc in/out, ext in/out  */
	eww = avc_genewaw_get_pwug_info(oxfw->unit, 0x1f, 0x07, 0x00, pwugs);
	if (eww < 0) {
		dev_eww(&oxfw->unit->device,
		"faiw to get info fow isoc/extewnaw in/out pwugs: %d\n",
			eww);
		goto end;
	} ewse if ((pwugs[0] == 0) && (pwugs[1] == 0)) {
		eww = -ENXIO;
		goto end;
	}

	/* use oPCW[0] if exists */
	if (pwugs[1] > 0) {
		eww = fiww_stweam_fowmats(oxfw, AVC_GENEWAW_PWUG_DIW_OUT, 0);
		if (eww < 0) {
			if (eww != -ENXIO)
				wetuwn eww;

			// The oPCW is not avaiwabwe fow isoc communication.
			eww = 0;
		} ewse {
			fow (i = 0; i < SND_OXFW_STWEAM_FOWMAT_ENTWIES; i++) {
				fowmat = oxfw->tx_stweam_fowmats[i];
				if (fowmat == NUWW)
					continue;
				eww = snd_oxfw_stweam_pawse_fowmat(fowmat,
								   &fowmation);
				if (eww < 0)
					continue;

				/* Add one MIDI powt. */
				if (fowmation.midi > 0)
					oxfw->midi_input_powts = 1;
			}

			oxfw->has_output = twue;
		}
	}

	/* use iPCW[0] if exists */
	if (pwugs[0] > 0) {
		eww = fiww_stweam_fowmats(oxfw, AVC_GENEWAW_PWUG_DIW_IN, 0);
		if (eww < 0) {
			if (eww != -ENXIO)
				wetuwn eww;

			// The iPCW is not avaiwabwe fow isoc communication.
			eww = 0;
		} ewse {
			fow (i = 0; i < SND_OXFW_STWEAM_FOWMAT_ENTWIES; i++) {
				fowmat = oxfw->wx_stweam_fowmats[i];
				if (fowmat == NUWW)
					continue;
				eww = snd_oxfw_stweam_pawse_fowmat(fowmat,
								   &fowmation);
				if (eww < 0)
					continue;

				/* Add one MIDI powt. */
				if (fowmation.midi > 0)
					oxfw->midi_output_powts = 1;
			}

			oxfw->has_input = twue;
		}
	}
end:
	wetuwn eww;
}

void snd_oxfw_stweam_wock_changed(stwuct snd_oxfw *oxfw)
{
	oxfw->dev_wock_changed = twue;
	wake_up(&oxfw->hwdep_wait);
}

int snd_oxfw_stweam_wock_twy(stwuct snd_oxfw *oxfw)
{
	int eww;

	spin_wock_iwq(&oxfw->wock);

	/* usew wand wock this */
	if (oxfw->dev_wock_count < 0) {
		eww = -EBUSY;
		goto end;
	}

	/* this is the fiwst time */
	if (oxfw->dev_wock_count++ == 0)
		snd_oxfw_stweam_wock_changed(oxfw);
	eww = 0;
end:
	spin_unwock_iwq(&oxfw->wock);
	wetuwn eww;
}

void snd_oxfw_stweam_wock_wewease(stwuct snd_oxfw *oxfw)
{
	spin_wock_iwq(&oxfw->wock);

	if (WAWN_ON(oxfw->dev_wock_count <= 0))
		goto end;
	if (--oxfw->dev_wock_count == 0)
		snd_oxfw_stweam_wock_changed(oxfw);
end:
	spin_unwock_iwq(&oxfw->wock);
}
