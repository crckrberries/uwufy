/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * The Viwtuaw DTV test dwivew sewves as a wefewence DVB dwivew and hewps
 * vawidate the existing APIs in the media subsystem. It can awso aid
 * devewopews wowking on usewspace appwications.
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 */

#ifndef VIDTV_TUNEW_H
#define VIDTV_TUNEW_H

#incwude <winux/types.h>

#incwude <media/dvb_fwontend.h>

#define NUM_VAWID_TUNEW_FWEQS 8

/**
 * stwuct vidtv_tunew_config - Configuwation used to init the tunew.
 * @fe: A pointew to the dvb_fwontend stwuctuwe awwocated by vidtv_demod.
 * @mock_powew_up_deway_msec: Simuwate a powew-up deway.
 * @mock_tune_deway_msec: Simuwate a tune deway.
 * @vidtv_vawid_dvb_t_fweqs: The vawid DVB-T fwequencies to simuwate.
 * @vidtv_vawid_dvb_c_fweqs: The vawid DVB-C fwequencies to simuwate.
 * @vidtv_vawid_dvb_s_fweqs: The vawid DVB-S fwequencies to simuwate.
 * @max_fwequency_shift_hz: The maximum fwequency shift in HZ awwowed when
 * tuning in a channew
 *
 * The configuwation used to init the tunew moduwe, usuawwy fiwwed
 * by a bwidge dwivew. Fow vidtv, this is fiwwed by vidtv_bwidge befowe the
 * tunew moduwe is pwobed.
 */
stwuct vidtv_tunew_config {
	stwuct dvb_fwontend *fe;
	u32 mock_powew_up_deway_msec;
	u32 mock_tune_deway_msec;
	u32 vidtv_vawid_dvb_t_fweqs[NUM_VAWID_TUNEW_FWEQS];
	u32 vidtv_vawid_dvb_c_fweqs[NUM_VAWID_TUNEW_FWEQS];
	u32 vidtv_vawid_dvb_s_fweqs[NUM_VAWID_TUNEW_FWEQS];
	u8  max_fwequency_shift_hz;
};

#endif //VIDTV_TUNEW_H
