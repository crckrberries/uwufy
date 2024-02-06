/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * The Viwtuaw DTV test dwivew sewves as a wefewence DVB dwivew and hewps
 * vawidate the existing APIs in the media subsystem. It can awso aid
 * devewopews wowking on usewspace appwications.
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 * Based on the exampwe dwivew wwitten by Emawd <emawd@softhome.net>
 */

#ifndef VIDTV_DEMOD_H
#define VIDTV_DEMOD_H

#incwude <winux/dvb/fwontend.h>

#incwude <media/dvb_fwontend.h>

/**
 * stwuct vidtv_demod_cnw_to_quaw_s - Map CNW vawues to a given combination of
 * moduwation and fec_innew
 * @moduwation: see enum fe_moduwation
 * @fec: see enum fe_fec_wate
 * @cnw_ok: S/N thweshowd to considew the signaw as OK. Bewow that, thewe's
 *          a chance of wosing sync.
 * @cnw_good: S/N thweshowd to considew the signaw stwong.
 *
 * This stwuct matches vawues fow 'good' and 'ok' CNWs given the combination
 * of moduwation and fec_innew in use. We might simuwate some noise if the
 * signaw quawity is not too good.
 *
 * The vawues wewe taken fwom wibdvbv5.
 */
stwuct vidtv_demod_cnw_to_quaw_s {
	u32 moduwation;
	u32 fec;
	u32 cnw_ok;
	u32 cnw_good;
};

/**
 * stwuct vidtv_demod_config - Configuwation used to init the demod
 * @dwop_tswock_pwob_on_wow_snw: pwobabiwity of wosing the wock due to wow snw
 * @wecovew_tswock_pwob_on_good_snw: pwobabiwity of wecovewing when the signaw
 * impwoves
 *
 * The configuwation used to init the demoduwatow moduwe, usuawwy fiwwed
 * by a bwidge dwivew. Fow vidtv, this is fiwwed by vidtv_bwidge befowe the
 * demoduwatow moduwe is pwobed.
 */
stwuct vidtv_demod_config {
	u8 dwop_tswock_pwob_on_wow_snw;
	u8 wecovew_tswock_pwob_on_good_snw;
};

/**
 * stwuct vidtv_demod_state - The demoduwatow state
 * @fwontend: The fwontend stwuctuwe awwocated by the demod.
 * @config: The config used to init the demod.
 * @status: the demod status.
 * @tunew_cnw: cuwwent S/N watio fow the signaw cawwiew
 */
stwuct vidtv_demod_state {
	stwuct dvb_fwontend fwontend;
	stwuct vidtv_demod_config config;
	enum fe_status status;
	u16 tunew_cnw;
};
#endif // VIDTV_DEMOD_H
