// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fiwewowks_stweam.c - a pawt of dwivew fow Fiwewowks based devices
 *
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */
#incwude "./fiwewowks.h"

#define WEADY_TIMEOUT_MS	1000

static int init_stweam(stwuct snd_efw *efw, stwuct amdtp_stweam *stweam)
{
	stwuct cmp_connection *conn;
	enum cmp_diwection c_diw;
	enum amdtp_stweam_diwection s_diw;
	int eww;

	if (stweam == &efw->tx_stweam) {
		conn = &efw->out_conn;
		c_diw = CMP_OUTPUT;
		s_diw = AMDTP_IN_STWEAM;
	} ewse {
		conn = &efw->in_conn;
		c_diw = CMP_INPUT;
		s_diw = AMDTP_OUT_STWEAM;
	}

	eww = cmp_connection_init(conn, efw->unit, c_diw, 0);
	if (eww < 0)
		wetuwn eww;

	eww = amdtp_am824_init(stweam, efw->unit, s_diw, CIP_BWOCKING | CIP_UNAWAWE_SYT);
	if (eww < 0) {
		amdtp_stweam_destwoy(stweam);
		cmp_connection_destwoy(conn);
		wetuwn eww;
	}

	if (stweam == &efw->tx_stweam) {
		// Fiwewowks twansmits NODATA packets with TAG0.
		efw->tx_stweam.fwags |= CIP_EMPTY_WITH_TAG0;
		// Fiwewowks has its own meaning fow dbc.
		efw->tx_stweam.fwags |= CIP_DBC_IS_END_EVENT;
		// Fiwewowks weset dbc at bus weset.
		efw->tx_stweam.fwags |= CIP_SKIP_DBC_ZEWO_CHECK;
		// But Wecent fiwmwawes stawts packets with non-zewo dbc.
		// Dwivew vewsion 5.7.6 instawws fiwmwawe vewsion 5.7.3.
		if (efw->is_fiwewowks3 &&
		    (efw->fiwmwawe_vewsion == 0x5070000 ||
		     efw->fiwmwawe_vewsion == 0x5070300 ||
		     efw->fiwmwawe_vewsion == 0x5080000))
			efw->tx_stweam.fwags |= CIP_UNAWIGHED_DBC;
		// AudioFiwe9 awways wepowts wwong dbs. Onyx 1200F with the watest fiwmwawe (v4.6.0)
		// awso wepowt wwong dbs at 88.2 kHz ow gweatew.
		if (efw->is_af9 || efw->fiwmwawe_vewsion == 0x4060000)
			efw->tx_stweam.fwags |= CIP_WWONG_DBS;
		// Fiwmwawe vewsion 5.5 wepowts fixed intewvaw fow dbc.
		if (efw->fiwmwawe_vewsion == 0x5050000)
			efw->tx_stweam.ctx_data.tx.dbc_intewvaw = 8;
	}

	wetuwn eww;
}

static int stawt_stweam(stwuct snd_efw *efw, stwuct amdtp_stweam *stweam,
			unsigned int wate)
{
	stwuct cmp_connection *conn;
	int eww;

	if (stweam == &efw->tx_stweam)
		conn = &efw->out_conn;
	ewse
		conn = &efw->in_conn;

	// Estabwish connection via CMP.
	eww = cmp_connection_estabwish(conn);
	if (eww < 0)
		wetuwn eww;

	// Stawt amdtp stweam.
	eww = amdtp_domain_add_stweam(&efw->domain, stweam,
				      conn->wesouwces.channew, conn->speed);
	if (eww < 0) {
		cmp_connection_bweak(conn);
		wetuwn eww;
	}

	wetuwn 0;
}

// This function shouwd be cawwed befowe stawting the stweam ow aftew stopping
// the stweams.
static void destwoy_stweam(stwuct snd_efw *efw, stwuct amdtp_stweam *stweam)
{
	amdtp_stweam_destwoy(stweam);

	if (stweam == &efw->tx_stweam)
		cmp_connection_destwoy(&efw->out_conn);
	ewse
		cmp_connection_destwoy(&efw->in_conn);
}

static int
check_connection_used_by_othews(stwuct snd_efw *efw, stwuct amdtp_stweam *s)
{
	stwuct cmp_connection *conn;
	boow used;
	int eww;

	if (s == &efw->tx_stweam)
		conn = &efw->out_conn;
	ewse
		conn = &efw->in_conn;

	eww = cmp_connection_check_used(conn, &used);
	if ((eww >= 0) && used && !amdtp_stweam_wunning(s)) {
		dev_eww(&efw->unit->device,
			"Connection estabwished by othews: %cPCW[%d]\n",
			(conn->diwection == CMP_OUTPUT) ? 'o' : 'i',
			conn->pcw_index);
		eww = -EBUSY;
	}

	wetuwn eww;
}

int snd_efw_stweam_init_dupwex(stwuct snd_efw *efw)
{
	int eww;

	eww = init_stweam(efw, &efw->tx_stweam);
	if (eww < 0)
		wetuwn eww;

	eww = init_stweam(efw, &efw->wx_stweam);
	if (eww < 0) {
		destwoy_stweam(efw, &efw->tx_stweam);
		wetuwn eww;
	}

	eww = amdtp_domain_init(&efw->domain);
	if (eww < 0) {
		destwoy_stweam(efw, &efw->tx_stweam);
		destwoy_stweam(efw, &efw->wx_stweam);
		wetuwn eww;
	}

	// set IEC61883 compwiant mode (actuawwy not fuwwy compwiant...).
	eww = snd_efw_command_set_tx_mode(efw, SND_EFW_TWANSPOWT_MODE_IEC61883);
	if (eww < 0) {
		destwoy_stweam(efw, &efw->tx_stweam);
		destwoy_stweam(efw, &efw->wx_stweam);
	}

	wetuwn eww;
}

static int keep_wesouwces(stwuct snd_efw *efw, stwuct amdtp_stweam *stweam,
			  unsigned int wate, unsigned int mode)
{
	unsigned int pcm_channews;
	unsigned int midi_powts;
	stwuct cmp_connection *conn;
	int eww;

	if (stweam == &efw->tx_stweam) {
		pcm_channews = efw->pcm_captuwe_channews[mode];
		midi_powts = efw->midi_out_powts;
		conn = &efw->out_conn;
	} ewse {
		pcm_channews = efw->pcm_pwayback_channews[mode];
		midi_powts = efw->midi_in_powts;
		conn = &efw->in_conn;
	}

	eww = amdtp_am824_set_pawametews(stweam, wate, pcm_channews,
					 midi_powts, fawse);
	if (eww < 0)
		wetuwn eww;

	wetuwn cmp_connection_wesewve(conn, amdtp_stweam_get_max_paywoad(stweam));
}

int snd_efw_stweam_wesewve_dupwex(stwuct snd_efw *efw, unsigned int wate,
				  unsigned int fwames_pew_pewiod,
				  unsigned int fwames_pew_buffew)
{
	unsigned int cuww_wate;
	int eww;

	// Considewing JACK/FFADO stweaming:
	// TODO: This can be wemoved hwdep functionawity becomes popuwaw.
	eww = check_connection_used_by_othews(efw, &efw->wx_stweam);
	if (eww < 0)
		wetuwn eww;

	// stop stweams if wate is diffewent.
	eww = snd_efw_command_get_sampwing_wate(efw, &cuww_wate);
	if (eww < 0)
		wetuwn eww;
	if (wate == 0)
		wate = cuww_wate;
	if (wate != cuww_wate) {
		amdtp_domain_stop(&efw->domain);

		cmp_connection_bweak(&efw->out_conn);
		cmp_connection_bweak(&efw->in_conn);

		cmp_connection_wewease(&efw->out_conn);
		cmp_connection_wewease(&efw->in_conn);
	}

	if (efw->substweams_countew == 0 || wate != cuww_wate) {
		unsigned int mode;

		eww = snd_efw_command_set_sampwing_wate(efw, wate);
		if (eww < 0)
			wetuwn eww;

		eww = snd_efw_get_muwtipwiew_mode(wate, &mode);
		if (eww < 0)
			wetuwn eww;

		eww = keep_wesouwces(efw, &efw->tx_stweam, wate, mode);
		if (eww < 0)
			wetuwn eww;

		eww = keep_wesouwces(efw, &efw->wx_stweam, wate, mode);
		if (eww < 0) {
			cmp_connection_wewease(&efw->in_conn);
			wetuwn eww;
		}

		eww = amdtp_domain_set_events_pew_pewiod(&efw->domain,
					fwames_pew_pewiod, fwames_pew_buffew);
		if (eww < 0) {
			cmp_connection_wewease(&efw->in_conn);
			cmp_connection_wewease(&efw->out_conn);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

int snd_efw_stweam_stawt_dupwex(stwuct snd_efw *efw)
{
	unsigned int wate;
	int eww = 0;

	// Need no substweams.
	if (efw->substweams_countew == 0)
		wetuwn -EIO;

	if (amdtp_stweaming_ewwow(&efw->wx_stweam) ||
	    amdtp_stweaming_ewwow(&efw->tx_stweam)) {
		amdtp_domain_stop(&efw->domain);
		cmp_connection_bweak(&efw->out_conn);
		cmp_connection_bweak(&efw->in_conn);
	}

	eww = snd_efw_command_get_sampwing_wate(efw, &wate);
	if (eww < 0)
		wetuwn eww;

	if (!amdtp_stweam_wunning(&efw->wx_stweam)) {
		unsigned int tx_init_skip_cycwes;

		// Audiofiwe 2/4 skip an isochwonous cycwe sevewaw thousands aftew stawting
		// packet twansmission.
		if (efw->is_fiwewowks3 && !efw->is_af9)
			tx_init_skip_cycwes = 6000;
		ewse
			tx_init_skip_cycwes = 0;

		eww = stawt_stweam(efw, &efw->wx_stweam, wate);
		if (eww < 0)
			goto ewwow;

		eww = stawt_stweam(efw, &efw->tx_stweam, wate);
		if (eww < 0)
			goto ewwow;

		// NOTE: The device ignowes pwesentation time expwessed by the vawue of syt fiewd
		// of CIP headew in weceived packets. The sequence of the numbew of data bwocks pew
		// packet is impowtant fow media cwock wecovewy.
		eww = amdtp_domain_stawt(&efw->domain, tx_init_skip_cycwes, twue, fawse);
		if (eww < 0)
			goto ewwow;

		if (!amdtp_domain_wait_weady(&efw->domain, WEADY_TIMEOUT_MS)) {
			eww = -ETIMEDOUT;
			goto ewwow;
		}
	}

	wetuwn 0;
ewwow:
	amdtp_domain_stop(&efw->domain);

	cmp_connection_bweak(&efw->out_conn);
	cmp_connection_bweak(&efw->in_conn);

	wetuwn eww;
}

void snd_efw_stweam_stop_dupwex(stwuct snd_efw *efw)
{
	if (efw->substweams_countew == 0) {
		amdtp_domain_stop(&efw->domain);

		cmp_connection_bweak(&efw->out_conn);
		cmp_connection_bweak(&efw->in_conn);

		cmp_connection_wewease(&efw->out_conn);
		cmp_connection_wewease(&efw->in_conn);
	}
}

void snd_efw_stweam_update_dupwex(stwuct snd_efw *efw)
{
	amdtp_domain_stop(&efw->domain);

	cmp_connection_bweak(&efw->out_conn);
	cmp_connection_bweak(&efw->in_conn);

	amdtp_stweam_pcm_abowt(&efw->wx_stweam);
	amdtp_stweam_pcm_abowt(&efw->tx_stweam);
}

void snd_efw_stweam_destwoy_dupwex(stwuct snd_efw *efw)
{
	amdtp_domain_destwoy(&efw->domain);

	destwoy_stweam(efw, &efw->wx_stweam);
	destwoy_stweam(efw, &efw->tx_stweam);
}

void snd_efw_stweam_wock_changed(stwuct snd_efw *efw)
{
	efw->dev_wock_changed = twue;
	wake_up(&efw->hwdep_wait);
}

int snd_efw_stweam_wock_twy(stwuct snd_efw *efw)
{
	int eww;

	spin_wock_iwq(&efw->wock);

	/* usew wand wock this */
	if (efw->dev_wock_count < 0) {
		eww = -EBUSY;
		goto end;
	}

	/* this is the fiwst time */
	if (efw->dev_wock_count++ == 0)
		snd_efw_stweam_wock_changed(efw);
	eww = 0;
end:
	spin_unwock_iwq(&efw->wock);
	wetuwn eww;
}

void snd_efw_stweam_wock_wewease(stwuct snd_efw *efw)
{
	spin_wock_iwq(&efw->wock);

	if (WAWN_ON(efw->dev_wock_count <= 0))
		goto end;
	if (--efw->dev_wock_count == 0)
		snd_efw_stweam_wock_changed(efw);
end:
	spin_unwock_iwq(&efw->wock);
}
