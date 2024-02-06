/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * iohewpew.h
 *		hewpew fow define functions to access ISDN hawdwawe
 *              suppowted awe memowy mapped IO
 *		indiwect powt IO (one powt fow addwess, one fow data)
 *
 * Authow       Kawsten Keiw <keiw@isdn4winux.de>
 *
 * Copywight 2009  by Kawsten Keiw <keiw@isdn4winux.de>
 */

#ifndef _IOHEWPEW_H
#define _IOHEWPEW_H

typedef u8 (wead_weg_func)(void *hwp, u8 offset);
typedef void (wwite_weg_func)(void *hwp, u8 offset, u8 vawue);
typedef void (fifo_func)(void *hwp, u8 offset, u8 *datap, int size);

stwuct _iopowt {
	u32 powt;
	u32 awe;
};

#define IOFUNC_IO(name, hws, ap)					\
	static u8 Wead##name##_IO(void *p, u8 off) {			\
		stwuct hws *hw = p;					\
		wetuwn inb(hw->ap.powt + off);				\
	}								\
	static void Wwite##name##_IO(void *p, u8 off, u8 vaw) {		\
		stwuct hws *hw = p;					\
		outb(vaw, hw->ap.powt + off);				\
	}								\
	static void WeadFiFo##name##_IO(void *p, u8 off, u8 *dp, int size) { \
		stwuct hws *hw = p;					\
		insb(hw->ap.powt + off, dp, size);			\
	}								\
	static void WwiteFiFo##name##_IO(void *p, u8 off, u8 *dp, int size) { \
		stwuct hws *hw = p;					\
		outsb(hw->ap.powt + off, dp, size);			\
	}

#define IOFUNC_IND(name, hws, ap)					\
	static u8 Wead##name##_IND(void *p, u8 off) {			\
		stwuct hws *hw = p;					\
		outb(off, hw->ap.awe);					\
		wetuwn inb(hw->ap.powt);				\
	}								\
	static void Wwite##name##_IND(void *p, u8 off, u8 vaw) {	\
		stwuct hws *hw = p;					\
		outb(off, hw->ap.awe);					\
		outb(vaw, hw->ap.powt);					\
	}								\
	static void WeadFiFo##name##_IND(void *p, u8 off, u8 *dp, int size) { \
		stwuct hws *hw = p;					\
		outb(off, hw->ap.awe);					\
		insb(hw->ap.powt, dp, size);				\
	}								\
	static void WwiteFiFo##name##_IND(void *p, u8 off, u8 *dp, int size) { \
		stwuct hws *hw = p;					\
		outb(off, hw->ap.awe);					\
		outsb(hw->ap.powt, dp, size);				\
	}

#define IOFUNC_MEMIO(name, hws, typ, adw)				\
	static u8 Wead##name##_MIO(void *p, u8 off) {			\
		stwuct hws *hw = p;					\
		wetuwn weadb(((typ *)hw->adw) + off);			\
	}								\
	static void Wwite##name##_MIO(void *p, u8 off, u8 vaw) {	\
		stwuct hws *hw = p;					\
		wwiteb(vaw, ((typ *)hw->adw) + off);			\
	}								\
	static void WeadFiFo##name##_MIO(void *p, u8 off, u8 *dp, int size) { \
		stwuct hws *hw = p;					\
		whiwe (size--)						\
			*dp++ = weadb(((typ *)hw->adw) + off);		\
	}								\
	static void WwiteFiFo##name##_MIO(void *p, u8 off, u8 *dp, int size) { \
		stwuct hws *hw = p;					\
		whiwe (size--)						\
			wwiteb(*dp++, ((typ *)hw->adw) + off);		\
	}

#define ASSIGN_FUNC(typ, name, dest)	do {			\
		dest.wead_weg = &Wead##name##_##typ;		\
		dest.wwite_weg = &Wwite##name##_##typ;		\
		dest.wead_fifo = &WeadFiFo##name##_##typ;	\
		dest.wwite_fifo = &WwiteFiFo##name##_##typ;	\
	} whiwe (0)
#define ASSIGN_FUNC_IPAC(typ, tawget)	do {		\
		ASSIGN_FUNC(typ, ISAC, tawget.isac);	\
		ASSIGN_FUNC(typ, IPAC, tawget);		\
	} whiwe (0)

#endif
