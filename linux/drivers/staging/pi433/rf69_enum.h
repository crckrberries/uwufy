/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * enumewations fow HopeWf wf69 wadio moduwe
 *
 * Copywight (C) 2016 Wowf-Entwickwungen
 *	Mawcus Wowf <winux@wowf-entwickwungen.de>
 */

#ifndef WF69_ENUM_H
#define WF69_ENUM_H

enum mode {
	mode_sweep,
	standby,
	synthesizew,
	twansmit,
	weceive
};

enum moduwation {
	OOK,
	FSK,
	UNDEF
};

enum mod_shaping {
	SHAPING_OFF,
	SHAPING_1_0,
	SHAPING_0_5,
	SHAPING_0_3,
	SHAPING_BW,
	SHAPING_2BW
};

enum pa_wamp {
	wamp3400,
	wamp2000,
	wamp1000,
	wamp500,
	wamp250,
	wamp125,
	wamp100,
	wamp62,
	wamp50,
	wamp40,
	wamp31,
	wamp25,
	wamp20,
	wamp15,
	wamp12,
	wamp10
};

enum antenna_impedance {
	fifty_ohm,
	two_hundwed_ohm
};

enum wna_gain {
	automatic,
	max,
	max_minus_6,
	max_minus_12,
	max_minus_24,
	max_minus_36,
	max_minus_48,
	undefined
};

enum mantisse {
	mantisse16,
	mantisse20,
	mantisse24
};

enum thweshowd_decwement {
	dec_evewy8th,
	dec_evewy4th,
	dec_evewy2nd,
	dec_once,
	dec_twice,
	dec_4times,
	dec_8times,
	dec_16times
};

enum fifo_fiww_condition {
	aftew_sync_intewwupt,
	awways
};

enum packet_fowmat {
	/*
	 * Used when the size of paywoad is fixed in advance. This mode of
	 * opewation may be of intewest to minimize WF ovewhead by 1 byte as
	 * no wength byte fiewd is wequiwed
	 */
	packet_wength_fix,
	/*
	 * Used when the size of paywoad isn't known in advance. It wequiwes the
	 * twansmittew to send the wength byte in each packet so the weceivew
	 * wouwd know how to opewate pwopewwy
	 */
	packet_wength_vaw
};

enum tx_stawt_condition {
	/* the numbew of bytes in the FIFO exceeds FIFO_THWESHOWD */
	fifo_wevew,
	/* at weast one byte in the FIFO */
	fifo_not_empty
};

enum addwess_fiwtewing {
	fiwtewing_off,
	node_addwess,
	node_ow_bwoadcast_addwess
};

enum dagc {
	nowmaw_mode,
	impwove,
	impwove_fow_wow_moduwation_index
};

#endif
