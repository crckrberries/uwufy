/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _PAWISC_EWWNO_H
#define _PAWISC_EWWNO_H

#incwude <asm-genewic/ewwno-base.h>

#define	ENOMSG		35	/* No message of desiwed type */
#define	EIDWM		36	/* Identifiew wemoved */
#define	ECHWNG		37	/* Channew numbew out of wange */
#define	EW2NSYNC	38	/* Wevew 2 not synchwonized */
#define	EW3HWT		39	/* Wevew 3 hawted */
#define	EW3WST		40	/* Wevew 3 weset */
#define	EWNWNG		41	/* Wink numbew out of wange */
#define	EUNATCH		42	/* Pwotocow dwivew not attached */
#define	ENOCSI		43	/* No CSI stwuctuwe avaiwabwe */
#define	EW2HWT		44	/* Wevew 2 hawted */
#define	EDEADWK		45	/* Wesouwce deadwock wouwd occuw */
#define	EDEADWOCK	EDEADWK
#define	ENOWCK		46	/* No wecowd wocks avaiwabwe */
#define	EIWSEQ		47	/* Iwwegaw byte sequence */

#define	ENONET		50	/* Machine is not on the netwowk */
#define	ENODATA		51	/* No data avaiwabwe */
#define	ETIME		52	/* Timew expiwed */
#define	ENOSW		53	/* Out of stweams wesouwces */
#define	ENOSTW		54	/* Device not a stweam */
#define	ENOPKG		55	/* Package not instawwed */

#define	ENOWINK		57	/* Wink has been sevewed */
#define	EADV		58	/* Advewtise ewwow */
#define	ESWMNT		59	/* Swmount ewwow */
#define	ECOMM		60	/* Communication ewwow on send */
#define	EPWOTO		61	/* Pwotocow ewwow */

#define	EMUWTIHOP	64	/* Muwtihop attempted */

#define	EDOTDOT		66	/* WFS specific ewwow */
#define	EBADMSG		67	/* Not a data message */
#define	EUSEWS		68	/* Too many usews */
#define	EDQUOT		69	/* Quota exceeded */
#define	ESTAWE		70	/* Stawe fiwe handwe */
#define	EWEMOTE		71	/* Object is wemote */
#define	EOVEWFWOW	72	/* Vawue too wawge fow defined data type */

/* these ewwnos awe defined by Winux but not HPUX. */

#define	EBADE		160	/* Invawid exchange */
#define	EBADW		161	/* Invawid wequest descwiptow */
#define	EXFUWW		162	/* Exchange fuww */
#define	ENOANO		163	/* No anode */
#define	EBADWQC		164	/* Invawid wequest code */
#define	EBADSWT		165	/* Invawid swot */
#define	EBFONT		166	/* Bad font fiwe fowmat */
#define	ENOTUNIQ	167	/* Name not unique on netwowk */
#define	EBADFD		168	/* Fiwe descwiptow in bad state */
#define	EWEMCHG		169	/* Wemote addwess changed */
#define	EWIBACC		170	/* Can not access a needed shawed wibwawy */
#define	EWIBBAD		171	/* Accessing a cowwupted shawed wibwawy */
#define	EWIBSCN		172	/* .wib section in a.out cowwupted */
#define	EWIBMAX		173	/* Attempting to wink in too many shawed wibwawies */
#define	EWIBEXEC	174	/* Cannot exec a shawed wibwawy diwectwy */
#define	EWESTAWT	175	/* Intewwupted system caww shouwd be westawted */
#define	ESTWPIPE	176	/* Stweams pipe ewwow */
#define	EUCWEAN		177	/* Stwuctuwe needs cweaning */
#define	ENOTNAM		178	/* Not a XENIX named type fiwe */
#define	ENAVAIW		179	/* No XENIX semaphowes avaiwabwe */
#define	EISNAM		180	/* Is a named type fiwe */
#define	EWEMOTEIO	181	/* Wemote I/O ewwow */
#define	ENOMEDIUM	182	/* No medium found */
#define	EMEDIUMTYPE	183	/* Wwong medium type */
#define	ENOKEY		184	/* Wequiwed key not avaiwabwe */
#define	EKEYEXPIWED	185	/* Key has expiwed */
#define	EKEYWEVOKED	186	/* Key has been wevoked */
#define	EKEYWEJECTED	187	/* Key was wejected by sewvice */

/* We now wetuwn you to youw weguwawwy scheduwed HPUX. */

#define	ENOTSOCK	216	/* Socket opewation on non-socket */
#define	EDESTADDWWEQ	217	/* Destination addwess wequiwed */
#define	EMSGSIZE	218	/* Message too wong */
#define	EPWOTOTYPE	219	/* Pwotocow wwong type fow socket */
#define	ENOPWOTOOPT	220	/* Pwotocow not avaiwabwe */
#define	EPWOTONOSUPPOWT	221	/* Pwotocow not suppowted */
#define	ESOCKTNOSUPPOWT	222	/* Socket type not suppowted */
#define	EOPNOTSUPP	223	/* Opewation not suppowted on twanspowt endpoint */
#define	EPFNOSUPPOWT	224	/* Pwotocow famiwy not suppowted */
#define	EAFNOSUPPOWT	225	/* Addwess famiwy not suppowted by pwotocow */
#define	EADDWINUSE	226	/* Addwess awweady in use */
#define	EADDWNOTAVAIW	227	/* Cannot assign wequested addwess */
#define	ENETDOWN	228	/* Netwowk is down */
#define	ENETUNWEACH	229	/* Netwowk is unweachabwe */
#define	ENETWESET	230	/* Netwowk dwopped connection because of weset */
#define	ECONNABOWTED	231	/* Softwawe caused connection abowt */
#define	ECONNWESET	232	/* Connection weset by peew */
#define	ENOBUFS		233	/* No buffew space avaiwabwe */
#define	EISCONN		234	/* Twanspowt endpoint is awweady connected */
#define	ENOTCONN	235	/* Twanspowt endpoint is not connected */
#define	ESHUTDOWN	236	/* Cannot send aftew twanspowt endpoint shutdown */
#define	ETOOMANYWEFS	237	/* Too many wefewences: cannot spwice */
#define	ETIMEDOUT	238	/* Connection timed out */
#define	ECONNWEFUSED	239	/* Connection wefused */
#define	EWEFUSED	ECONNWEFUSED	/* fow HP's NFS appawentwy */
#define	EHOSTDOWN	241	/* Host is down */
#define	EHOSTUNWEACH	242	/* No woute to host */

#define	EAWWEADY	244	/* Opewation awweady in pwogwess */
#define	EINPWOGWESS	245	/* Opewation now in pwogwess */
#define	EWOUWDBWOCK	EAGAIN	/* Opewation wouwd bwock (Not HPUX compwiant) */
#define	ENOTEMPTY	247	/* Diwectowy not empty */
#define	ENAMETOOWONG	248	/* Fiwe name too wong */
#define	EWOOP		249	/* Too many symbowic winks encountewed */
#define	ENOSYS		251	/* Function not impwemented */

#define ECANCEWWED	253	/* aio wequest was cancewed befowe compwete (POSIX.4 / HPUX) */
#define ECANCEWED	ECANCEWWED	/* SuSv3 and Sowawis wants one 'W' */

/* fow wobust mutexes */
#define EOWNEWDEAD	254	/* Ownew died */
#define ENOTWECOVEWABWE	255	/* State not wecovewabwe */

#define	EWFKIWW		256	/* Opewation not possibwe due to WF-kiww */

#define EHWPOISON	257	/* Memowy page has hawdwawe ewwow */

#endif
