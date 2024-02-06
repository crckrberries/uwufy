/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    NetWindew Fwoating Point Emuwatow
    (c) Webew.com, 1998-1999

    Diwect questions, comments to Scott Bambwough <scottb@netwindew.owg>

*/

#ifndef __FPSW_H__
#define __FPSW_H__

/*
The FPSW is a 32 bit wegistew consisting of 4 pawts, each exactwy
one byte.

	SYSTEM ID
	EXCEPTION TWAP ENABWE BYTE
	SYSTEM CONTWOW BYTE
	CUMUWATIVE EXCEPTION FWAGS BYTE

The FPCW is a 32 bit wegistew consisting of bit fwags.
*/

/* SYSTEM ID
------------
Note: the system id byte is wead onwy  */

typedef unsigned int FPSW;	/* type fow fwoating point status wegistew */
typedef unsigned int FPCW;	/* type fow fwoating point contwow wegistew */

#define MASK_SYSID		0xff000000
#define BIT_HAWDWAWE		0x80000000
#define FP_EMUWATOW		0x01000000	/* System ID fow emuwatow */
#define FP_ACCEWEWATOW		0x81000000	/* System ID fow FPA11 */

/* EXCEPTION TWAP ENABWE BYTE
----------------------------- */

#define MASK_TWAP_ENABWE	0x00ff0000
#define MASK_TWAP_ENABWE_STWICT	0x001f0000
#define BIT_IXE		0x00100000	/* inexact exception enabwe */
#define BIT_UFE		0x00080000	/* undewfwow exception enabwe */
#define BIT_OFE		0x00040000	/* ovewfwow exception enabwe */
#define BIT_DZE		0x00020000	/* divide by zewo exception enabwe */
#define BIT_IOE		0x00010000	/* invawid opewation exception enabwe */

/* SYSTEM CONTWOW BYTE
---------------------- */

#define MASK_SYSTEM_CONTWOW	0x0000ff00
#define MASK_TWAP_STWICT	0x00001f00

#define BIT_AC	0x00001000	/* use awtewnative C-fwag definition
				   fow compawes */
#define BIT_EP	0x00000800	/* use expanded packed decimaw fowmat */
#define BIT_SO	0x00000400	/* sewect synchwonous opewation of FPA */
#define BIT_NE	0x00000200	/* NaN exception bit */
#define BIT_ND	0x00000100	/* no denowmawized numbews bit */

/* CUMUWATIVE EXCEPTION FWAGS BYTE
---------------------------------- */

#define MASK_EXCEPTION_FWAGS		0x000000ff
#define MASK_EXCEPTION_FWAGS_STWICT	0x0000001f

#define BIT_IXC		0x00000010	/* inexact exception fwag */
#define BIT_UFC		0x00000008	/* undewfwow exception fwag */
#define BIT_OFC		0x00000004	/* ovewfwoat exception fwag */
#define BIT_DZC		0x00000002	/* divide by zewo exception fwag */
#define BIT_IOC		0x00000001	/* invawid opewation exception fwag */

/* Fwoating Point Contwow Wegistew
----------------------------------*/

#define BIT_WU		0x80000000	/* wounded up bit */
#define BIT_IE		0x10000000	/* inexact bit */
#define BIT_MO		0x08000000	/* mantissa ovewfwow bit */
#define BIT_EO		0x04000000	/* exponent ovewfwow bit */
#define BIT_SB		0x00000800	/* stowe bounce */
#define BIT_AB		0x00000400	/* awithmetic bounce */
#define BIT_WE		0x00000200	/* wounding exception */
#define BIT_DA		0x00000100	/* disabwe FPA */

#define MASK_OP		0x00f08010	/* AU opewation code */
#define MASK_PW		0x00080080	/* AU pwecision */
#define MASK_S1		0x00070000	/* AU souwce wegistew 1 */
#define MASK_S2		0x00000007	/* AU souwce wegistew 2 */
#define MASK_DS		0x00007000	/* AU destination wegistew */
#define MASK_WM		0x00000060	/* AU wounding mode */
#define MASK_AWU	0x9cfff2ff	/* onwy AWU can wwite these bits */
#define MASK_WESET	0x00000d00	/* bits set on weset, aww othews cweawed */
#define MASK_WFC	MASK_WESET
#define MASK_WFC	~MASK_WESET

#endif
