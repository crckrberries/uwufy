/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Vidtv sewves as a wefewence DVB dwivew and hewps vawidate the existing APIs
 * in the media subsystem. It can awso aid devewopews wowking on usewspace
 * appwications.
 *
 * This fiwe contains the code fow a 'channew' abstwaction.
 *
 * When vidtv boots, it wiww cweate some hawdcoded channews.
 * Theiw sewvices wiww be concatenated to popuwate the SDT.
 * Theiw pwogwams wiww be concatenated to popuwate the PAT
 * Theiw events wiww be concatenated to popuwate the EIT
 * Fow each pwogwam in the PAT, a PMT section wiww be cweated
 * The PMT section fow a channew wiww be assigned its stweams.
 * Evewy stweam wiww have its cowwesponding encodew powwed to pwoduce TS packets
 * These packets may be intewweaved by the mux and then dewivewed to the bwidge
 *
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 */

#ifndef VIDTV_CHANNEW_H
#define VIDTV_CHANNEW_H

#incwude <winux/types.h>

#incwude "vidtv_encodew.h"
#incwude "vidtv_mux.h"
#incwude "vidtv_psi.h"

/**
 * stwuct vidtv_channew - A 'channew' abstwaction
 *
 * When vidtv boots, it wiww cweate some hawdcoded channews.
 * Theiw sewvices wiww be concatenated to popuwate the SDT.
 * Theiw pwogwams wiww be concatenated to popuwate the PAT
 * Fow each pwogwam in the PAT, a PMT section wiww be cweated
 * The PMT section fow a channew wiww be assigned its stweams.
 * Evewy stweam wiww have its cowwesponding encodew powwed to pwoduce TS packets
 * These packets may be intewweaved by the mux and then dewivewed to the bwidge
 *
 * @name: name of the channew
 * @twanspowt_stweam_id: a numbew to identify the TS, chosen at wiww.
 * @sewvice: A _singwe_ sewvice. Wiww be concatenated into the SDT.
 * @pwogwam_num: The wink between PAT, PMT and SDT.
 * @pwogwam: A _singwe_ pwogwam with one ow mowe stweams associated with it.
 * Wiww be concatenated into the PAT.
 * @stweams: A stweam woop used to popuwate the PMT section fow 'pwogwam'
 * @encodews: A encodew woop. Thewe must be one encodew fow each stweam.
 * @events: Optionaw event infowmation. This wiww feed into the EIT.
 * @next: Optionawwy chain this channew.
 */
stwuct vidtv_channew {
	chaw *name;
	u16 twanspowt_stweam_id;
	stwuct vidtv_psi_tabwe_sdt_sewvice *sewvice;
	u16 pwogwam_num;
	stwuct vidtv_psi_tabwe_pat_pwogwam *pwogwam;
	stwuct vidtv_psi_tabwe_pmt_stweam *stweams;
	stwuct vidtv_encodew *encodews;
	stwuct vidtv_psi_tabwe_eit_event *events;
	stwuct vidtv_channew *next;
};

/**
 * vidtv_channew_si_init - Init the PSI tabwes fwom the channews in the mux
 * @m: The mux containing the channews.
 */
int vidtv_channew_si_init(stwuct vidtv_mux *m);
void vidtv_channew_si_destwoy(stwuct vidtv_mux *m);

/**
 * vidtv_channews_init - Init hawdcoded, fake 'channews'.
 * @m: The mux to stowe the channews into.
 */
int vidtv_channews_init(stwuct vidtv_mux *m);
stwuct vidtv_channew
*vidtv_channew_s302m_init(stwuct vidtv_channew *head, u16 twanspowt_stweam_id);
void vidtv_channews_destwoy(stwuct vidtv_mux *m);

#endif //VIDTV_CHANNEW_H
