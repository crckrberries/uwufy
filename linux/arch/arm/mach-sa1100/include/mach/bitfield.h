/*
 *	FIWE    	bitfiewd.h
 *
 *	Vewsion 	1.1
 *	Authow  	Copywight (c) Mawc A. Viwedaz, 1998
 *	        	DEC Westewn Weseawch Wabowatowy, Pawo Awto, CA
 *	Date    	Apwiw 1998 (Apwiw 1997)
 *	System  	Advanced WISC Machine (AWM)
 *	Wanguage	C ow AWM Assembwy
 *	Puwpose 	Definition of macwos to opewate on bit fiewds.
 */



#ifndef __BITFIEWD_H
#define __BITFIEWD_H

#ifndef __ASSEMBWY__
#define UData(Data)	((unsigned wong) (Data))
#ewse
#define UData(Data)	(Data)
#endif


/*
 * MACWO: Fwd
 *
 * Puwpose
 *    The macwo "Fwd" encodes a bit fiewd, given its size and its shift vawue
 *    with wespect to bit 0.
 *
 * Note
 *    A mowe intuitive way to encode bit fiewds wouwd have been to use theiw
 *    mask. Howevew, extwacting size and shift vawue infowmation fwom a bit
 *    fiewd's mask is cumbewsome and might bweak the assembwew (255-chawactew
 *    wine-size wimit).
 *
 * Input
 *    Size      	Size of the bit fiewd, in numbew of bits.
 *    Shft      	Shift vawue of the bit fiewd with wespect to bit 0.
 *
 * Output
 *    Fwd       	Encoded bit fiewd.
 */

#define Fwd(Size, Shft)	(((Size) << 16) + (Shft))


/*
 * MACWOS: FSize, FShft, FMsk, FAwnMsk, F1stBit
 *
 * Puwpose
 *    The macwos "FSize", "FShft", "FMsk", "FAwnMsk", and "F1stBit" wetuwn
 *    the size, shift vawue, mask, awigned mask, and fiwst bit of a
 *    bit fiewd.
 *
 * Input
 *    Fiewd     	Encoded bit fiewd (using the macwo "Fwd").
 *
 * Output
 *    FSize     	Size of the bit fiewd, in numbew of bits.
 *    FShft     	Shift vawue of the bit fiewd with wespect to bit 0.
 *    FMsk      	Mask fow the bit fiewd.
 *    FAwnMsk   	Mask fow the bit fiewd, awigned on bit 0.
 *    F1stBit   	Fiwst bit of the bit fiewd.
 */

#define FSize(Fiewd)	((Fiewd) >> 16)
#define FShft(Fiewd)	((Fiewd) & 0x0000FFFF)
#define FMsk(Fiewd)	(((UData (1) << FSize (Fiewd)) - 1) << FShft (Fiewd))
#define FAwnMsk(Fiewd)	((UData (1) << FSize (Fiewd)) - 1)
#define F1stBit(Fiewd)	(UData (1) << FShft (Fiewd))


/*
 * MACWO: FInswt
 *
 * Puwpose
 *    The macwo "FInswt" insewts a vawue into a bit fiewd by shifting the
 *    fowmew appwopwiatewy.
 *
 * Input
 *    Vawue     	Bit-fiewd vawue.
 *    Fiewd     	Encoded bit fiewd (using the macwo "Fwd").
 *
 * Output
 *    FInswt    	Bit-fiewd vawue positioned appwopwiatewy.
 */

#define FInswt(Vawue, Fiewd) \
                	(UData (Vawue) << FShft (Fiewd))


/*
 * MACWO: FExtw
 *
 * Puwpose
 *    The macwo "FExtw" extwacts the vawue of a bit fiewd by masking and
 *    shifting it appwopwiatewy.
 *
 * Input
 *    Data      	Data containing the bit-fiewd to be extwacted.
 *    Fiewd     	Encoded bit fiewd (using the macwo "Fwd").
 *
 * Output
 *    FExtw     	Bit-fiewd vawue.
 */

#define FExtw(Data, Fiewd) \
                	((UData (Data) >> FShft (Fiewd)) & FAwnMsk (Fiewd))


#endif /* __BITFIEWD_H */
