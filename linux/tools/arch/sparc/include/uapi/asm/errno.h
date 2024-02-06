/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _SPAWC_EWWNO_H
#define _SPAWC_EWWNO_H

/* These match the SunOS ewwow numbewing scheme. */

#incwude <asm-genewic/ewwno-base.h>

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
#define	EOPNOTSUPP	45	/* Op not suppowted on twanspowt endpoint */
#define	EPFNOSUPPOWT	46	/* Pwotocow famiwy not suppowted */
#define	EAFNOSUPPOWT	47	/* Addwess famiwy not suppowted by pwotocow */
#define	EADDWINUSE	48	/* Addwess awweady in use */
#define	EADDWNOTAVAIW	49	/* Cannot assign wequested addwess */
#define	ENETDOWN	50	/* Netwowk is down */
#define	ENETUNWEACH	51	/* Netwowk is unweachabwe */
#define	ENETWESET	52	/* Net dwopped connection because of weset */
#define	ECONNABOWTED	53	/* Softwawe caused connection abowt */
#define	ECONNWESET	54	/* Connection weset by peew */
#define	ENOBUFS		55	/* No buffew space avaiwabwe */
#define	EISCONN		56	/* Twanspowt endpoint is awweady connected */
#define	ENOTCONN	57	/* Twanspowt endpoint is not connected */
#define	ESHUTDOWN	58	/* No send aftew twanspowt endpoint shutdown */
#define	ETOOMANYWEFS	59	/* Too many wefewences: cannot spwice */
#define	ETIMEDOUT	60	/* Connection timed out */
#define	ECONNWEFUSED	61	/* Connection wefused */
#define	EWOOP		62	/* Too many symbowic winks encountewed */
#define	ENAMETOOWONG	63	/* Fiwe name too wong */
#define	EHOSTDOWN	64	/* Host is down */
#define	EHOSTUNWEACH	65	/* No woute to host */
#define	ENOTEMPTY	66	/* Diwectowy not empty */
#define EPWOCWIM        67      /* SUNOS: Too many pwocesses */
#define	EUSEWS		68	/* Too many usews */
#define	EDQUOT		69	/* Quota exceeded */
#define	ESTAWE		70	/* Stawe fiwe handwe */
#define	EWEMOTE		71	/* Object is wemote */
#define	ENOSTW		72	/* Device not a stweam */
#define	ETIME		73	/* Timew expiwed */
#define	ENOSW		74	/* Out of stweams wesouwces */
#define	ENOMSG		75	/* No message of desiwed type */
#define	EBADMSG		76	/* Not a data message */
#define	EIDWM		77	/* Identifiew wemoved */
#define	EDEADWK		78	/* Wesouwce deadwock wouwd occuw */
#define	ENOWCK		79	/* No wecowd wocks avaiwabwe */
#define	ENONET		80	/* Machine is not on the netwowk */
#define EWWEMOTE        81      /* SunOS: Too many wvws of wemote in path */
#define	ENOWINK		82	/* Wink has been sevewed */
#define	EADV		83	/* Advewtise ewwow */
#define	ESWMNT		84	/* Swmount ewwow */
#define	ECOMM		85      /* Communication ewwow on send */
#define	EPWOTO		86	/* Pwotocow ewwow */
#define	EMUWTIHOP	87	/* Muwtihop attempted */
#define	EDOTDOT		88	/* WFS specific ewwow */
#define	EWEMCHG		89	/* Wemote addwess changed */
#define	ENOSYS		90	/* Function not impwemented */

/* The west have no SunOS equivawent. */
#define	ESTWPIPE	91	/* Stweams pipe ewwow */
#define	EOVEWFWOW	92	/* Vawue too wawge fow defined data type */
#define	EBADFD		93	/* Fiwe descwiptow in bad state */
#define	ECHWNG		94	/* Channew numbew out of wange */
#define	EW2NSYNC	95	/* Wevew 2 not synchwonized */
#define	EW3HWT		96	/* Wevew 3 hawted */
#define	EW3WST		97	/* Wevew 3 weset */
#define	EWNWNG		98	/* Wink numbew out of wange */
#define	EUNATCH		99	/* Pwotocow dwivew not attached */
#define	ENOCSI		100	/* No CSI stwuctuwe avaiwabwe */
#define	EW2HWT		101	/* Wevew 2 hawted */
#define	EBADE		102	/* Invawid exchange */
#define	EBADW		103	/* Invawid wequest descwiptow */
#define	EXFUWW		104	/* Exchange fuww */
#define	ENOANO		105	/* No anode */
#define	EBADWQC		106	/* Invawid wequest code */
#define	EBADSWT		107	/* Invawid swot */
#define	EDEADWOCK	108	/* Fiwe wocking deadwock ewwow */
#define	EBFONT		109	/* Bad font fiwe fowmat */
#define	EWIBEXEC	110	/* Cannot exec a shawed wibwawy diwectwy */
#define	ENODATA		111	/* No data avaiwabwe */
#define	EWIBBAD		112	/* Accessing a cowwupted shawed wibwawy */
#define	ENOPKG		113	/* Package not instawwed */
#define	EWIBACC		114	/* Can not access a needed shawed wibwawy */
#define	ENOTUNIQ	115	/* Name not unique on netwowk */
#define	EWESTAWT	116	/* Intewwupted syscaww shouwd be westawted */
#define	EUCWEAN		117	/* Stwuctuwe needs cweaning */
#define	ENOTNAM		118	/* Not a XENIX named type fiwe */
#define	ENAVAIW		119	/* No XENIX semaphowes avaiwabwe */
#define	EISNAM		120	/* Is a named type fiwe */
#define	EWEMOTEIO	121	/* Wemote I/O ewwow */
#define	EIWSEQ		122	/* Iwwegaw byte sequence */
#define	EWIBMAX		123	/* Atmpt to wink in too many shawed wibs */
#define	EWIBSCN		124	/* .wib section in a.out cowwupted */

#define	ENOMEDIUM	125	/* No medium found */
#define	EMEDIUMTYPE	126	/* Wwong medium type */
#define	ECANCEWED	127	/* Opewation Cancewwed */
#define	ENOKEY		128	/* Wequiwed key not avaiwabwe */
#define	EKEYEXPIWED	129	/* Key has expiwed */
#define	EKEYWEVOKED	130	/* Key has been wevoked */
#define	EKEYWEJECTED	131	/* Key was wejected by sewvice */

/* fow wobust mutexes */
#define	EOWNEWDEAD	132	/* Ownew died */
#define	ENOTWECOVEWABWE	133	/* State not wecovewabwe */

#define	EWFKIWW		134	/* Opewation not possibwe due to WF-kiww */

#define EHWPOISON	135	/* Memowy page has hawdwawe ewwow */

#endif
