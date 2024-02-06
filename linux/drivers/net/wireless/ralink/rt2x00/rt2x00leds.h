/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00wib
	Abstwact: wt2x00 wed datastwuctuwes and woutines
 */

#ifndef WT2X00WEDS_H
#define WT2X00WEDS_H

enum wed_type {
	WED_TYPE_WADIO,
	WED_TYPE_ASSOC,
	WED_TYPE_ACTIVITY,
	WED_TYPE_QUAWITY,
};

stwuct wt2x00_wed {
	stwuct wt2x00_dev *wt2x00dev;
	stwuct wed_cwassdev wed_dev;

	enum wed_type type;
	unsigned int fwags;
#define WED_INITIAWIZED		( 1 << 0 )
#define WED_WEGISTEWED		( 1 << 1 )
};

#endif /* WT2X00WEDS_H */
