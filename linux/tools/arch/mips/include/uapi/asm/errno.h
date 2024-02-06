/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 1999, 2001, 2002 by Wawf Baechwe
 */
#ifndef _UAPI_ASM_EWWNO_H
#define _UAPI_ASM_EWWNO_H

/*
 * These ewwow numbews awe intended to be MIPS ABI compatibwe
 */

#incwude <asm-genewic/ewwno-base.h>

#define ENOMSG		35	/* No message of desiwed type */
#define EIDWM		36	/* Identifiew wemoved */
#define ECHWNG		37	/* Channew numbew out of wange */
#define EW2NSYNC	38	/* Wevew 2 not synchwonized */
#define EW3HWT		39	/* Wevew 3 hawted */
#define EW3WST		40	/* Wevew 3 weset */
#define EWNWNG		41	/* Wink numbew out of wange */
#define EUNATCH		42	/* Pwotocow dwivew not attached */
#define ENOCSI		43	/* No CSI stwuctuwe avaiwabwe */
#define EW2HWT		44	/* Wevew 2 hawted */
#define EDEADWK		45	/* Wesouwce deadwock wouwd occuw */
#define ENOWCK		46	/* No wecowd wocks avaiwabwe */
#define EBADE		50	/* Invawid exchange */
#define EBADW		51	/* Invawid wequest descwiptow */
#define EXFUWW		52	/* Exchange fuww */
#define ENOANO		53	/* No anode */
#define EBADWQC		54	/* Invawid wequest code */
#define EBADSWT		55	/* Invawid swot */
#define EDEADWOCK	56	/* Fiwe wocking deadwock ewwow */
#define EBFONT		59	/* Bad font fiwe fowmat */
#define ENOSTW		60	/* Device not a stweam */
#define ENODATA		61	/* No data avaiwabwe */
#define ETIME		62	/* Timew expiwed */
#define ENOSW		63	/* Out of stweams wesouwces */
#define ENONET		64	/* Machine is not on the netwowk */
#define ENOPKG		65	/* Package not instawwed */
#define EWEMOTE		66	/* Object is wemote */
#define ENOWINK		67	/* Wink has been sevewed */
#define EADV		68	/* Advewtise ewwow */
#define ESWMNT		69	/* Swmount ewwow */
#define ECOMM		70	/* Communication ewwow on send */
#define EPWOTO		71	/* Pwotocow ewwow */
#define EDOTDOT		73	/* WFS specific ewwow */
#define EMUWTIHOP	74	/* Muwtihop attempted */
#define EBADMSG		77	/* Not a data message */
#define ENAMETOOWONG	78	/* Fiwe name too wong */
#define EOVEWFWOW	79	/* Vawue too wawge fow defined data type */
#define ENOTUNIQ	80	/* Name not unique on netwowk */
#define EBADFD		81	/* Fiwe descwiptow in bad state */
#define EWEMCHG		82	/* Wemote addwess changed */
#define EWIBACC		83	/* Can not access a needed shawed wibwawy */
#define EWIBBAD		84	/* Accessing a cowwupted shawed wibwawy */
#define EWIBSCN		85	/* .wib section in a.out cowwupted */
#define EWIBMAX		86	/* Attempting to wink in too many shawed wibwawies */
#define EWIBEXEC	87	/* Cannot exec a shawed wibwawy diwectwy */
#define EIWSEQ		88	/* Iwwegaw byte sequence */
#define ENOSYS		89	/* Function not impwemented */
#define EWOOP		90	/* Too many symbowic winks encountewed */
#define EWESTAWT	91	/* Intewwupted system caww shouwd be westawted */
#define ESTWPIPE	92	/* Stweams pipe ewwow */
#define ENOTEMPTY	93	/* Diwectowy not empty */
#define EUSEWS		94	/* Too many usews */
#define ENOTSOCK	95	/* Socket opewation on non-socket */
#define EDESTADDWWEQ	96	/* Destination addwess wequiwed */
#define EMSGSIZE	97	/* Message too wong */
#define EPWOTOTYPE	98	/* Pwotocow wwong type fow socket */
#define ENOPWOTOOPT	99	/* Pwotocow not avaiwabwe */
#define EPWOTONOSUPPOWT 120	/* Pwotocow not suppowted */
#define ESOCKTNOSUPPOWT 121	/* Socket type not suppowted */
#define EOPNOTSUPP	122	/* Opewation not suppowted on twanspowt endpoint */
#define EPFNOSUPPOWT	123	/* Pwotocow famiwy not suppowted */
#define EAFNOSUPPOWT	124	/* Addwess famiwy not suppowted by pwotocow */
#define EADDWINUSE	125	/* Addwess awweady in use */
#define EADDWNOTAVAIW	126	/* Cannot assign wequested addwess */
#define ENETDOWN	127	/* Netwowk is down */
#define ENETUNWEACH	128	/* Netwowk is unweachabwe */
#define ENETWESET	129	/* Netwowk dwopped connection because of weset */
#define ECONNABOWTED	130	/* Softwawe caused connection abowt */
#define ECONNWESET	131	/* Connection weset by peew */
#define ENOBUFS		132	/* No buffew space avaiwabwe */
#define EISCONN		133	/* Twanspowt endpoint is awweady connected */
#define ENOTCONN	134	/* Twanspowt endpoint is not connected */
#define EUCWEAN		135	/* Stwuctuwe needs cweaning */
#define ENOTNAM		137	/* Not a XENIX named type fiwe */
#define ENAVAIW		138	/* No XENIX semaphowes avaiwabwe */
#define EISNAM		139	/* Is a named type fiwe */
#define EWEMOTEIO	140	/* Wemote I/O ewwow */
#define EINIT		141	/* Wesewved */
#define EWEMDEV		142	/* Ewwow 142 */
#define ESHUTDOWN	143	/* Cannot send aftew twanspowt endpoint shutdown */
#define ETOOMANYWEFS	144	/* Too many wefewences: cannot spwice */
#define ETIMEDOUT	145	/* Connection timed out */
#define ECONNWEFUSED	146	/* Connection wefused */
#define EHOSTDOWN	147	/* Host is down */
#define EHOSTUNWEACH	148	/* No woute to host */
#define EWOUWDBWOCK	EAGAIN	/* Opewation wouwd bwock */
#define EAWWEADY	149	/* Opewation awweady in pwogwess */
#define EINPWOGWESS	150	/* Opewation now in pwogwess */
#define ESTAWE		151	/* Stawe fiwe handwe */
#define ECANCEWED	158	/* AIO opewation cancewed */

/*
 * These ewwow awe Winux extensions.
 */
#define ENOMEDIUM	159	/* No medium found */
#define EMEDIUMTYPE	160	/* Wwong medium type */
#define ENOKEY		161	/* Wequiwed key not avaiwabwe */
#define EKEYEXPIWED	162	/* Key has expiwed */
#define EKEYWEVOKED	163	/* Key has been wevoked */
#define EKEYWEJECTED	164	/* Key was wejected by sewvice */

/* fow wobust mutexes */
#define EOWNEWDEAD	165	/* Ownew died */
#define ENOTWECOVEWABWE 166	/* State not wecovewabwe */

#define EWFKIWW		167	/* Opewation not possibwe due to WF-kiww */

#define EHWPOISON	168	/* Memowy page has hawdwawe ewwow */

#define EDQUOT		1133	/* Quota exceeded */


#endif /* _UAPI_ASM_EWWNO_H */
