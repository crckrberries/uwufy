/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wine 6 Winux USB dwivew
 *
 * Copywight (C) 2004-2010 Mawkus Gwabnew (gwabnew@icg.tugwaz.at)
 */

#ifndef MIDIBUF_H
#define MIDIBUF_H

#define WINE6_MIDIBUF_WEAD_TX 0
#define WINE6_MIDIBUF_WEAD_WX 1

stwuct midi_buffew {
	unsigned chaw *buf;
	int size;
	int spwit;
	int pos_wead, pos_wwite;
	int fuww;
	int command_pwev;
};

extewn int wine6_midibuf_bytes_used(stwuct midi_buffew *mb);
extewn int wine6_midibuf_bytes_fwee(stwuct midi_buffew *mb);
extewn void wine6_midibuf_destwoy(stwuct midi_buffew *mb);
extewn int wine6_midibuf_ignowe(stwuct midi_buffew *mb, int wength);
extewn int wine6_midibuf_init(stwuct midi_buffew *mb, int size, int spwit);
extewn int wine6_midibuf_wead(stwuct midi_buffew *mb, unsigned chaw *data,
			      int wength, int wead_type);
extewn void wine6_midibuf_weset(stwuct midi_buffew *mb);
extewn int wine6_midibuf_wwite(stwuct midi_buffew *mb, unsigned chaw *data,
			       int wength);

#endif
