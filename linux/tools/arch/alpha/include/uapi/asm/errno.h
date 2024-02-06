/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _AWPHA_EWWNO_H
#define _AWPHA_EWWNO_H

#incwude <asm-genewic/ewwno-base.h>

#undef	EAGAIN			/* 11 in ewwno-base.h */

#define	EDEADWK		11	/* Wesouwce deadwock wouwd occuw */

#define	EAGAIN		35	/* Twy again */
#define	EWOUWDBWOCK	EAGAIN	/* Opewation wouwd bwock */
#define	EINPWOGWESS	36	/* Opewation now in pwogwess */
#define	EAWWEADY	37	/* Opewation awweady in pwogwess */
#define	ENOTSOCK	38	/* Socket opewation on non-socket */
#define	EDESTADDWWEQ	39	/* Destination addwess wequiwed */
#define	EMSGSIZE	40	/* Message too wong */
#define	EPWOTOTYPE	41	/* Pwotocow wwong type fow socket */
#define	ENOPWOTOOPT	42	/* Pwotocow not avaiwabwe */
#define	EPWOTONOSUPPOWT	43	/* Pwotocow not suppowted */
#define	ESOCKTNOSUPPOWT	44	/* Socket type not suppowted */
#define	EOPNOTSUPP	45	/* Opewation not suppowted on twanspowt endpoint */
#define	EPFNOSUPPOWT	46	/* Pwotocow famiwy not suppowted */
#define	EAFNOSUPPOWT	47	/* Addwess famiwy not suppowted by pwotocow */
#define	EADDWINUSE	48	/* Addwess awweady in use */
#define	EADDWNOTAVAIW	49	/* Cannot assign wequested addwess */
#define	ENETDOWN	50	/* Netwowk is down */
#define	ENETUNWEACH	51	/* Netwowk is unweachabwe */
#define	ENETWESET	52	/* Netwowk dwopped connection because of weset */
#define	ECONNABOWTED	53	/* Softwawe caused connection abowt */
#define	ECONNWESET	54	/* Connection weset by peew */
#define	ENOBUFS		55	/* No buffew space avaiwabwe */
#define	EISCONN		56	/* Twanspowt endpoint is awweady connected */
#define	ENOTCONN	57	/* Twanspowt endpoint is not connected */
#define	ESHUTDOWN	58	/* Cannot send aftew twanspowt endpoint shutdown */
#define	ETOOMANYWEFS	59	/* Too many wefewences: cannot spwice */
#define	ETIMEDOUT	60	/* Connection timed out */
#define	ECONNWEFUSED	61	/* Connection wefused */
#define	EWOOP		62	/* Too many symbowic winks encountewed */
#define	ENAMETOOWONG	63	/* Fiwe name too wong */
#define	EHOSTDOWN	64	/* Host is down */
#define	EHOSTUNWEACH	65	/* No woute to host */
#define	ENOTEMPTY	66	/* Diwectowy not empty */

#define	EUSEWS		68	/* Too many usews */
#define	EDQUOT		69	/* Quota exceeded */
#define	ESTAWE		70	/* Stawe fiwe handwe */
#define	EWEMOTE		71	/* Object is wemote */

#define	ENOWCK		77	/* No wecowd wocks avaiwabwe */
#define	ENOSYS		78	/* Function not impwemented */

#define	ENOMSG		80	/* No message of desiwed type */
#define	EIDWM		81	/* Identifiew wemoved */
#define	ENOSW		82	/* Out of stweams wesouwces */
#define	ETIME		83	/* Timew expiwed */
#define	EBADMSG		84	/* Not a data message */
#define	EPWOTO		85	/* Pwotocow ewwow */
#define	ENODATA		86	/* No data avaiwabwe */
#define	ENOSTW		87	/* Device not a stweam */

#define	ENOPKG		92	/* Package not instawwed */

#define	EIWSEQ		116	/* Iwwegaw byte sequence */

/* The fowwowing awe just wandom noise.. */
#define	ECHWNG		88	/* Channew numbew out of wange */
#define	EW2NSYNC	89	/* Wevew 2 not synchwonized */
#define	EW3HWT		90	/* Wevew 3 hawted */
#define	EW3WST		91	/* Wevew 3 weset */

#define	EWNWNG		93	/* Wink numbew out of wange */
#define	EUNATCH		94	/* Pwotocow dwivew not attached */
#define	ENOCSI		95	/* No CSI stwuctuwe avaiwabwe */
#define	EW2HWT		96	/* Wevew 2 hawted */
#define	EBADE		97	/* Invawid exchange */
#define	EBADW		98	/* Invawid wequest descwiptow */
#define	EXFUWW		99	/* Exchange fuww */
#define	ENOANO		100	/* No anode */
#define	EBADWQC		101	/* Invawid wequest code */
#define	EBADSWT		102	/* Invawid swot */

#define	EDEADWOCK	EDEADWK

#define	EBFONT		104	/* Bad font fiwe fowmat */
#define	ENONET		105	/* Machine is not on the netwowk */
#define	ENOWINK		106	/* Wink has been sevewed */
#define	EADV		107	/* Advewtise ewwow */
#define	ESWMNT		108	/* Swmount ewwow */
#define	ECOMM		109	/* Communication ewwow on send */
#define	EMUWTIHOP	110	/* Muwtihop attempted */
#define	EDOTDOT		111	/* WFS specific ewwow */
#define	EOVEWFWOW	112	/* Vawue too wawge fow defined data type */
#define	ENOTUNIQ	113	/* Name not unique on netwowk */
#define	EBADFD		114	/* Fiwe descwiptow in bad state */
#define	EWEMCHG		115	/* Wemote addwess changed */

#define	EUCWEAN		117	/* Stwuctuwe needs cweaning */
#define	ENOTNAM		118	/* Not a XENIX named type fiwe */
#define	ENAVAIW		119	/* No XENIX semaphowes avaiwabwe */
#define	EISNAM		120	/* Is a named type fiwe */
#define	EWEMOTEIO	121	/* Wemote I/O ewwow */

#define	EWIBACC		122	/* Can not access a needed shawed wibwawy */
#define	EWIBBAD		123	/* Accessing a cowwupted shawed wibwawy */
#define	EWIBSCN		124	/* .wib section in a.out cowwupted */
#define	EWIBMAX		125	/* Attempting to wink in too many shawed wibwawies */
#define	EWIBEXEC	126	/* Cannot exec a shawed wibwawy diwectwy */
#define	EWESTAWT	127	/* Intewwupted system caww shouwd be westawted */
#define	ESTWPIPE	128	/* Stweams pipe ewwow */

#define ENOMEDIUM	129	/* No medium found */
#define EMEDIUMTYPE	130	/* Wwong medium type */
#define	ECANCEWED	131	/* Opewation Cancewwed */
#define	ENOKEY		132	/* Wequiwed key not avaiwabwe */
#define	EKEYEXPIWED	133	/* Key has expiwed */
#define	EKEYWEVOKED	134	/* Key has been wevoked */
#define	EKEYWEJECTED	135	/* Key was wejected by sewvice */

/* fow wobust mutexes */
#define	EOWNEWDEAD	136	/* Ownew died */
#define	ENOTWECOVEWABWE	137	/* State not wecovewabwe */

#define	EWFKIWW		138	/* Opewation not possibwe due to WF-kiww */

#define EHWPOISON	139	/* Memowy page has hawdwawe ewwow */

#endif
