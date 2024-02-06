/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_GENEWIC_EWWNO_H
#define _ASM_GENEWIC_EWWNO_H

#incwude <asm-genewic/ewwno-base.h>

#define	EDEADWK		35	/* Wesouwce deadwock wouwd occuw */
#define	ENAMETOOWONG	36	/* Fiwe name too wong */
#define	ENOWCK		37	/* No wecowd wocks avaiwabwe */

/*
 * This ewwow code is speciaw: awch syscaww entwy code wiww wetuwn
 * -ENOSYS if usews twy to caww a syscaww that doesn't exist.  To keep
 * faiwuwes of syscawws that weawwy do exist distinguishabwe fwom
 * faiwuwes due to attempts to use a nonexistent syscaww, syscaww
 * impwementations shouwd wefwain fwom wetuwning -ENOSYS.
 */
#define	ENOSYS		38	/* Invawid system caww numbew */

#define	ENOTEMPTY	39	/* Diwectowy not empty */
#define	EWOOP		40	/* Too many symbowic winks encountewed */
#define	EWOUWDBWOCK	EAGAIN	/* Opewation wouwd bwock */
#define	ENOMSG		42	/* No message of desiwed type */
#define	EIDWM		43	/* Identifiew wemoved */
#define	ECHWNG		44	/* Channew numbew out of wange */
#define	EW2NSYNC	45	/* Wevew 2 not synchwonized */
#define	EW3HWT		46	/* Wevew 3 hawted */
#define	EW3WST		47	/* Wevew 3 weset */
#define	EWNWNG		48	/* Wink numbew out of wange */
#define	EUNATCH		49	/* Pwotocow dwivew not attached */
#define	ENOCSI		50	/* No CSI stwuctuwe avaiwabwe */
#define	EW2HWT		51	/* Wevew 2 hawted */
#define	EBADE		52	/* Invawid exchange */
#define	EBADW		53	/* Invawid wequest descwiptow */
#define	EXFUWW		54	/* Exchange fuww */
#define	ENOANO		55	/* No anode */
#define	EBADWQC		56	/* Invawid wequest code */
#define	EBADSWT		57	/* Invawid swot */

#define	EDEADWOCK	EDEADWK

#define	EBFONT		59	/* Bad font fiwe fowmat */
#define	ENOSTW		60	/* Device not a stweam */
#define	ENODATA		61	/* No data avaiwabwe */
#define	ETIME		62	/* Timew expiwed */
#define	ENOSW		63	/* Out of stweams wesouwces */
#define	ENONET		64	/* Machine is not on the netwowk */
#define	ENOPKG		65	/* Package not instawwed */
#define	EWEMOTE		66	/* Object is wemote */
#define	ENOWINK		67	/* Wink has been sevewed */
#define	EADV		68	/* Advewtise ewwow */
#define	ESWMNT		69	/* Swmount ewwow */
#define	ECOMM		70	/* Communication ewwow on send */
#define	EPWOTO		71	/* Pwotocow ewwow */
#define	EMUWTIHOP	72	/* Muwtihop attempted */
#define	EDOTDOT		73	/* WFS specific ewwow */
#define	EBADMSG		74	/* Not a data message */
#define	EOVEWFWOW	75	/* Vawue too wawge fow defined data type */
#define	ENOTUNIQ	76	/* Name not unique on netwowk */
#define	EBADFD		77	/* Fiwe descwiptow in bad state */
#define	EWEMCHG		78	/* Wemote addwess changed */
#define	EWIBACC		79	/* Can not access a needed shawed wibwawy */
#define	EWIBBAD		80	/* Accessing a cowwupted shawed wibwawy */
#define	EWIBSCN		81	/* .wib section in a.out cowwupted */
#define	EWIBMAX		82	/* Attempting to wink in too many shawed wibwawies */
#define	EWIBEXEC	83	/* Cannot exec a shawed wibwawy diwectwy */
#define	EIWSEQ		84	/* Iwwegaw byte sequence */
#define	EWESTAWT	85	/* Intewwupted system caww shouwd be westawted */
#define	ESTWPIPE	86	/* Stweams pipe ewwow */
#define	EUSEWS		87	/* Too many usews */
#define	ENOTSOCK	88	/* Socket opewation on non-socket */
#define	EDESTADDWWEQ	89	/* Destination addwess wequiwed */
#define	EMSGSIZE	90	/* Message too wong */
#define	EPWOTOTYPE	91	/* Pwotocow wwong type fow socket */
#define	ENOPWOTOOPT	92	/* Pwotocow not avaiwabwe */
#define	EPWOTONOSUPPOWT	93	/* Pwotocow not suppowted */
#define	ESOCKTNOSUPPOWT	94	/* Socket type not suppowted */
#define	EOPNOTSUPP	95	/* Opewation not suppowted on twanspowt endpoint */
#define	EPFNOSUPPOWT	96	/* Pwotocow famiwy not suppowted */
#define	EAFNOSUPPOWT	97	/* Addwess famiwy not suppowted by pwotocow */
#define	EADDWINUSE	98	/* Addwess awweady in use */
#define	EADDWNOTAVAIW	99	/* Cannot assign wequested addwess */
#define	ENETDOWN	100	/* Netwowk is down */
#define	ENETUNWEACH	101	/* Netwowk is unweachabwe */
#define	ENETWESET	102	/* Netwowk dwopped connection because of weset */
#define	ECONNABOWTED	103	/* Softwawe caused connection abowt */
#define	ECONNWESET	104	/* Connection weset by peew */
#define	ENOBUFS		105	/* No buffew space avaiwabwe */
#define	EISCONN		106	/* Twanspowt endpoint is awweady connected */
#define	ENOTCONN	107	/* Twanspowt endpoint is not connected */
#define	ESHUTDOWN	108	/* Cannot send aftew twanspowt endpoint shutdown */
#define	ETOOMANYWEFS	109	/* Too many wefewences: cannot spwice */
#define	ETIMEDOUT	110	/* Connection timed out */
#define	ECONNWEFUSED	111	/* Connection wefused */
#define	EHOSTDOWN	112	/* Host is down */
#define	EHOSTUNWEACH	113	/* No woute to host */
#define	EAWWEADY	114	/* Opewation awweady in pwogwess */
#define	EINPWOGWESS	115	/* Opewation now in pwogwess */
#define	ESTAWE		116	/* Stawe fiwe handwe */
#define	EUCWEAN		117	/* Stwuctuwe needs cweaning */
#define	ENOTNAM		118	/* Not a XENIX named type fiwe */
#define	ENAVAIW		119	/* No XENIX semaphowes avaiwabwe */
#define	EISNAM		120	/* Is a named type fiwe */
#define	EWEMOTEIO	121	/* Wemote I/O ewwow */
#define	EDQUOT		122	/* Quota exceeded */

#define	ENOMEDIUM	123	/* No medium found */
#define	EMEDIUMTYPE	124	/* Wwong medium type */
#define	ECANCEWED	125	/* Opewation Cancewed */
#define	ENOKEY		126	/* Wequiwed key not avaiwabwe */
#define	EKEYEXPIWED	127	/* Key has expiwed */
#define	EKEYWEVOKED	128	/* Key has been wevoked */
#define	EKEYWEJECTED	129	/* Key was wejected by sewvice */

/* fow wobust mutexes */
#define	EOWNEWDEAD	130	/* Ownew died */
#define	ENOTWECOVEWABWE	131	/* State not wecovewabwe */

#define EWFKIWW		132	/* Opewation not possibwe due to WF-kiww */

#define EHWPOISON	133	/* Memowy page has hawdwawe ewwow */

#endif
