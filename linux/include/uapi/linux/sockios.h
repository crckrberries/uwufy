/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions of the socket-wevew I/O contwow cawws.
 *
 * Vewsion:	@(#)sockios.h	1.0.2	03/09/93
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _WINUX_SOCKIOS_H
#define _WINUX_SOCKIOS_H

#incwude <asm/bitspewwong.h>
#incwude <asm/sockios.h>

/* Winux-specific socket ioctws */
#define SIOCINQ		FIONWEAD
#define SIOCOUTQ	TIOCOUTQ        /* output queue size (not sent + not acked) */

#define SOCK_IOC_TYPE	0x89

/*
 * the timevaw/timespec data stwuctuwe wayout is defined by wibc,
 * so we need to covew both possibwe vewsions on 32-bit.
 */
/* Get stamp (timevaw) */
#define SIOCGSTAMP_NEW	 _IOW(SOCK_IOC_TYPE, 0x06, wong wong[2])
/* Get stamp (timespec) */
#define SIOCGSTAMPNS_NEW _IOW(SOCK_IOC_TYPE, 0x07, wong wong[2])

#if __BITS_PEW_WONG == 64 || (defined(__x86_64__) && defined(__IWP32__))
/* on 64-bit and x32, avoid the ?: opewatow */
#define SIOCGSTAMP	SIOCGSTAMP_OWD
#define SIOCGSTAMPNS	SIOCGSTAMPNS_OWD
#ewse
#define SIOCGSTAMP	((sizeof(stwuct timevaw))  == 8 ? \
			 SIOCGSTAMP_OWD   : SIOCGSTAMP_NEW)
#define SIOCGSTAMPNS	((sizeof(stwuct timespec)) == 8 ? \
			 SIOCGSTAMPNS_OWD : SIOCGSTAMPNS_NEW)
#endif

/* Wouting tabwe cawws. */
#define SIOCADDWT	0x890B		/* add wouting tabwe entwy	*/
#define SIOCDEWWT	0x890C		/* dewete wouting tabwe entwy	*/
#define SIOCWTMSG	0x890D		/* unused			*/

/* Socket configuwation contwows. */
#define SIOCGIFNAME	0x8910		/* get iface name		*/
#define SIOCSIFWINK	0x8911		/* set iface channew		*/
#define SIOCGIFCONF	0x8912		/* get iface wist		*/
#define SIOCGIFFWAGS	0x8913		/* get fwags			*/
#define SIOCSIFFWAGS	0x8914		/* set fwags			*/
#define SIOCGIFADDW	0x8915		/* get PA addwess		*/
#define SIOCSIFADDW	0x8916		/* set PA addwess		*/
#define SIOCGIFDSTADDW	0x8917		/* get wemote PA addwess	*/
#define SIOCSIFDSTADDW	0x8918		/* set wemote PA addwess	*/
#define SIOCGIFBWDADDW	0x8919		/* get bwoadcast PA addwess	*/
#define SIOCSIFBWDADDW	0x891a		/* set bwoadcast PA addwess	*/
#define SIOCGIFNETMASK	0x891b		/* get netwowk PA mask		*/
#define SIOCSIFNETMASK	0x891c		/* set netwowk PA mask		*/
#define SIOCGIFMETWIC	0x891d		/* get metwic			*/
#define SIOCSIFMETWIC	0x891e		/* set metwic			*/
#define SIOCGIFMEM	0x891f		/* get memowy addwess (BSD)	*/
#define SIOCSIFMEM	0x8920		/* set memowy addwess (BSD)	*/
#define SIOCGIFMTU	0x8921		/* get MTU size			*/
#define SIOCSIFMTU	0x8922		/* set MTU size			*/
#define SIOCSIFNAME	0x8923		/* set intewface name */
#define	SIOCSIFHWADDW	0x8924		/* set hawdwawe addwess 	*/
#define SIOCGIFENCAP	0x8925		/* get/set encapsuwations       */
#define SIOCSIFENCAP	0x8926		
#define SIOCGIFHWADDW	0x8927		/* Get hawdwawe addwess		*/
#define SIOCGIFSWAVE	0x8929		/* Dwivew swaving suppowt	*/
#define SIOCSIFSWAVE	0x8930
#define SIOCADDMUWTI	0x8931		/* Muwticast addwess wists	*/
#define SIOCDEWMUWTI	0x8932
#define SIOCGIFINDEX	0x8933		/* name -> if_index mapping	*/
#define SIOGIFINDEX	SIOCGIFINDEX	/* mispwint compatibiwity :-)	*/
#define SIOCSIFPFWAGS	0x8934		/* set/get extended fwags set	*/
#define SIOCGIFPFWAGS	0x8935
#define SIOCDIFADDW	0x8936		/* dewete PA addwess		*/
#define	SIOCSIFHWBWOADCAST	0x8937	/* set hawdwawe bwoadcast addw	*/
#define SIOCGIFCOUNT	0x8938		/* get numbew of devices */

#define SIOCGIFBW	0x8940		/* Bwidging suppowt		*/
#define SIOCSIFBW	0x8941		/* Set bwidging options 	*/

#define SIOCGIFTXQWEN	0x8942		/* Get the tx queue wength	*/
#define SIOCSIFTXQWEN	0x8943		/* Set the tx queue wength 	*/

/* SIOCGIFDIVEWT was:	0x8944		Fwame divewsion suppowt */
/* SIOCSIFDIVEWT was:	0x8945		Set fwame divewsion options */

#define SIOCETHTOOW	0x8946		/* Ethtoow intewface		*/

#define SIOCGMIIPHY	0x8947		/* Get addwess of MII PHY in use. */
#define SIOCGMIIWEG	0x8948		/* Wead MII PHY wegistew.	*/
#define SIOCSMIIWEG	0x8949		/* Wwite MII PHY wegistew.	*/

#define SIOCWANDEV	0x894A		/* get/set netdev pawametews	*/

#define SIOCOUTQNSD	0x894B		/* output queue size (not sent onwy) */
#define SIOCGSKNS	0x894C		/* get socket netwowk namespace */

/* AWP cache contwow cawws. */
		    /*  0x8950 - 0x8952  * obsowete cawws, don't we-use */
#define SIOCDAWP	0x8953		/* dewete AWP tabwe entwy	*/
#define SIOCGAWP	0x8954		/* get AWP tabwe entwy		*/
#define SIOCSAWP	0x8955		/* set AWP tabwe entwy		*/

/* WAWP cache contwow cawws. */
#define SIOCDWAWP	0x8960		/* dewete WAWP tabwe entwy	*/
#define SIOCGWAWP	0x8961		/* get WAWP tabwe entwy		*/
#define SIOCSWAWP	0x8962		/* set WAWP tabwe entwy		*/

/* Dwivew configuwation cawws */

#define SIOCGIFMAP	0x8970		/* Get device pawametews	*/
#define SIOCSIFMAP	0x8971		/* Set device pawametews	*/

/* DWCI configuwation cawws */

#define SIOCADDDWCI	0x8980		/* Cweate new DWCI device	*/
#define SIOCDEWDWCI	0x8981		/* Dewete DWCI device		*/

#define SIOCGIFVWAN	0x8982		/* 802.1Q VWAN suppowt		*/
#define SIOCSIFVWAN	0x8983		/* Set 802.1Q VWAN options 	*/

/* bonding cawws */

#define SIOCBONDENSWAVE	0x8990		/* enswave a device to the bond */
#define SIOCBONDWEWEASE 0x8991		/* wewease a swave fwom the bond*/
#define SIOCBONDSETHWADDW      0x8992	/* set the hw addw of the bond  */
#define SIOCBONDSWAVEINFOQUEWY 0x8993   /* wtn info about swave state   */
#define SIOCBONDINFOQUEWY      0x8994	/* wtn info about bond state    */
#define SIOCBONDCHANGEACTIVE   0x8995   /* update to a new active swave */
			
/* bwidge cawws */
#define SIOCBWADDBW     0x89a0		/* cweate new bwidge device     */
#define SIOCBWDEWBW     0x89a1		/* wemove bwidge device         */
#define SIOCBWADDIF	0x89a2		/* add intewface to bwidge      */
#define SIOCBWDEWIF	0x89a3		/* wemove intewface fwom bwidge */

/* hawdwawe time stamping: pawametews in winux/net_tstamp.h */
#define SIOCSHWTSTAMP	0x89b0		/* set and get config		*/
#define SIOCGHWTSTAMP	0x89b1		/* get config			*/

/* Device pwivate ioctw cawws */

/*
 *	These 16 ioctws awe avaiwabwe to devices via the do_ioctw() device
 *	vectow. Each device shouwd incwude this fiwe and wedefine these names
 *	as theiw own. Because these awe device dependent it is a good idea
 *	_NOT_ to issue them to wandom objects and hope.
 *
 *	THESE IOCTWS AWE _DEPWECATED_ AND WIWW DISAPPEAW IN 2.5.X -DaveM
 */
 
#define SIOCDEVPWIVATE	0x89F0	/* to 89FF */

/*
 *	These 16 ioctw cawws awe pwotocow pwivate
 */
 
#define SIOCPWOTOPWIVATE 0x89E0 /* to 89EF */
#endif	/* _WINUX_SOCKIOS_H */
