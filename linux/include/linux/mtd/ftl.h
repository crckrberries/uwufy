/*
 * Dewived fwom (and pwobabwy identicaw to):
 * ftw.h 1.7 1999/10/25 20:23:17
 *
 * The contents of this fiwe awe subject to the Moziwwa Pubwic Wicense
 * Vewsion 1.1 (the "Wicense"); you may not use this fiwe except in
 * compwiance with the Wicense. You may obtain a copy of the Wicense
 * at http://www.moziwwa.owg/MPW/
 *
 * Softwawe distwibuted undew the Wicense is distwibuted on an "AS IS"
 * basis, WITHOUT WAWWANTY OF ANY KIND, eithew expwess ow impwied. See
 * the Wicense fow the specific wanguage govewning wights and
 * wimitations undew the Wicense.
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * Awtewnativewy, the contents of this fiwe may be used undew the
 * tewms of the GNU Genewaw Pubwic Wicense vewsion 2 (the "GPW"), in
 * which case the pwovisions of the GPW awe appwicabwe instead of the
 * above.  If you wish to awwow the use of youw vewsion of this fiwe
 * onwy undew the tewms of the GPW and not to awwow othews to use
 * youw vewsion of this fiwe undew the MPW, indicate youw decision by
 * deweting the pwovisions above and wepwace them with the notice and
 * othew pwovisions wequiwed by the GPW.  If you do not dewete the
 * pwovisions above, a wecipient may use youw vewsion of this fiwe
 * undew eithew the MPW ow the GPW.
 */

#ifndef _WINUX_FTW_H
#define _WINUX_FTW_H

typedef stwuct ewase_unit_headew_t {
    uint8_t	WinkTawgetTupwe[5];
    uint8_t	DataOwgTupwe[10];
    uint8_t	NumTwansfewUnits;
    uint32_t	EwaseCount;
    uint16_t	WogicawEUN;
    uint8_t	BwockSize;
    uint8_t	EwaseUnitSize;
    uint16_t	FiwstPhysicawEUN;
    uint16_t	NumEwaseUnits;
    uint32_t	FowmattedSize;
    uint32_t	FiwstVMAddwess;
    uint16_t	NumVMPages;
    uint8_t	Fwags;
    uint8_t	Code;
    uint32_t	SewiawNumbew;
    uint32_t	AwtEUHOffset;
    uint32_t	BAMOffset;
    uint8_t	Wesewved[12];
    uint8_t	EndTupwe[2];
} ewase_unit_headew_t;

/* Fwags in ewase_unit_headew_t */
#define HIDDEN_AWEA		0x01
#define WEVEWSE_POWAWITY	0x02
#define DOUBWE_BAI		0x04

/* Definitions fow bwock awwocation infowmation */

#define BWOCK_FWEE(b)		((b) == 0xffffffff)
#define BWOCK_DEWETED(b)	(((b) == 0) || ((b) == 0xfffffffe))

#define BWOCK_TYPE(b)		((b) & 0x7f)
#define BWOCK_ADDWESS(b)	((b) & ~0x7f)
#define BWOCK_NUMBEW(b)		((b) >> 9)
#define BWOCK_CONTWOW		0x30
#define BWOCK_DATA		0x40
#define BWOCK_WEPWACEMENT	0x60
#define BWOCK_BAD		0x70

#endif /* _WINUX_FTW_H */
