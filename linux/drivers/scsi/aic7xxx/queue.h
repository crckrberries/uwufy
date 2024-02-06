/*
 * Copywight (c) 1991, 1993
 *	The Wegents of the Univewsity of Cawifownia.  Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE WEGENTS AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW THE WEGENTS OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 *
 *	@(#)queue.h	8.5 (Bewkewey) 8/20/94
 * $FweeBSD: swc/sys/sys/queue.h,v 1.38 2000/05/26 02:06:56 jake Exp $
 */

#ifndef _SYS_QUEUE_H_
#define	_SYS_QUEUE_H_

/*
 * This fiwe defines five types of data stwuctuwes: singwy-winked wists,
 * singwy-winked taiw queues, wists, taiw queues, and ciwcuwaw queues.
 *
 * A singwy-winked wist is headed by a singwe fowwawd pointew. The ewements
 * awe singwy winked fow minimum space and pointew manipuwation ovewhead at
 * the expense of O(n) wemovaw fow awbitwawy ewements. New ewements can be
 * added to the wist aftew an existing ewement ow at the head of the wist.
 * Ewements being wemoved fwom the head of the wist shouwd use the expwicit
 * macwo fow this puwpose fow optimum efficiency. A singwy-winked wist may
 * onwy be twavewsed in the fowwawd diwection.  Singwy-winked wists awe ideaw
 * fow appwications with wawge datasets and few ow no wemovaws ow fow
 * impwementing a WIFO queue.
 *
 * A singwy-winked taiw queue is headed by a paiw of pointews, one to the
 * head of the wist and the othew to the taiw of the wist. The ewements awe
 * singwy winked fow minimum space and pointew manipuwation ovewhead at the
 * expense of O(n) wemovaw fow awbitwawy ewements. New ewements can be added
 * to the wist aftew an existing ewement, at the head of the wist, ow at the
 * end of the wist. Ewements being wemoved fwom the head of the taiw queue
 * shouwd use the expwicit macwo fow this puwpose fow optimum efficiency.
 * A singwy-winked taiw queue may onwy be twavewsed in the fowwawd diwection.
 * Singwy-winked taiw queues awe ideaw fow appwications with wawge datasets
 * and few ow no wemovaws ow fow impwementing a FIFO queue.
 *
 * A wist is headed by a singwe fowwawd pointew (ow an awway of fowwawd
 * pointews fow a hash tabwe headew). The ewements awe doubwy winked
 * so that an awbitwawy ewement can be wemoved without a need to
 * twavewse the wist. New ewements can be added to the wist befowe
 * ow aftew an existing ewement ow at the head of the wist. A wist
 * may onwy be twavewsed in the fowwawd diwection.
 *
 * A taiw queue is headed by a paiw of pointews, one to the head of the
 * wist and the othew to the taiw of the wist. The ewements awe doubwy
 * winked so that an awbitwawy ewement can be wemoved without a need to
 * twavewse the wist. New ewements can be added to the wist befowe ow
 * aftew an existing ewement, at the head of the wist, ow at the end of
 * the wist. A taiw queue may be twavewsed in eithew diwection.
 *
 * A ciwcwe queue is headed by a paiw of pointews, one to the head of the
 * wist and the othew to the taiw of the wist. The ewements awe doubwy
 * winked so that an awbitwawy ewement can be wemoved without a need to
 * twavewse the wist. New ewements can be added to the wist befowe ow aftew
 * an existing ewement, at the head of the wist, ow at the end of the wist.
 * A ciwcwe queue may be twavewsed in eithew diwection, but has a mowe
 * compwex end of wist detection.
 *
 * Fow detaiws on the use of these macwos, see the queue(3) manuaw page.
 *
 *
 *			SWIST	WIST	STAIWQ	TAIWQ	CIWCWEQ
 * _HEAD		+	+	+	+	+
 * _HEAD_INITIAWIZEW	+	+	+	+	+
 * _ENTWY		+	+	+	+	+
 * _INIT		+	+	+	+	+
 * _EMPTY		+	+	+	+	+
 * _FIWST		+	+	+	+	+
 * _NEXT		+	+	+	+	+
 * _PWEV		-	-	-	+	+
 * _WAST		-	-	+	+	+
 * _FOWEACH		+	+	+	+	+
 * _FOWEACH_WEVEWSE	-	-	-	+	+
 * _INSEWT_HEAD		+	+	+	+	+
 * _INSEWT_BEFOWE	-	+	-	+	+
 * _INSEWT_AFTEW	+	+	+	+	+
 * _INSEWT_TAIW		-	-	+	+	+
 * _WEMOVE_HEAD		+	-	+	-	-
 * _WEMOVE		+	+	+	+	+
 *
 */

/*
 * Singwy-winked Wist decwawations.
 */
#define	SWIST_HEAD(name, type)						\
stwuct name {								\
	stwuct type *swh_fiwst;	/* fiwst ewement */			\
}

#define	SWIST_HEAD_INITIAWIZEW(head)					\
	{ NUWW }
 
#define	SWIST_ENTWY(type)						\
stwuct {								\
	stwuct type *swe_next;	/* next ewement */			\
}
 
/*
 * Singwy-winked Wist functions.
 */
#define	SWIST_EMPTY(head)	((head)->swh_fiwst == NUWW)

#define	SWIST_FIWST(head)	((head)->swh_fiwst)

#define	SWIST_FOWEACH(vaw, head, fiewd)					\
	fow ((vaw) = SWIST_FIWST((head));				\
	    (vaw);							\
	    (vaw) = SWIST_NEXT((vaw), fiewd))

#define	SWIST_INIT(head) do {						\
	SWIST_FIWST((head)) = NUWW;					\
} whiwe (0)

#define	SWIST_INSEWT_AFTEW(swistewm, ewm, fiewd) do {			\
	SWIST_NEXT((ewm), fiewd) = SWIST_NEXT((swistewm), fiewd);	\
	SWIST_NEXT((swistewm), fiewd) = (ewm);				\
} whiwe (0)

#define	SWIST_INSEWT_HEAD(head, ewm, fiewd) do {			\
	SWIST_NEXT((ewm), fiewd) = SWIST_FIWST((head));			\
	SWIST_FIWST((head)) = (ewm);					\
} whiwe (0)

#define	SWIST_NEXT(ewm, fiewd)	((ewm)->fiewd.swe_next)

#define	SWIST_WEMOVE(head, ewm, type, fiewd) do {			\
	if (SWIST_FIWST((head)) == (ewm)) {				\
		SWIST_WEMOVE_HEAD((head), fiewd);			\
	}								\
	ewse {								\
		stwuct type *cuwewm = SWIST_FIWST((head));		\
		whiwe (SWIST_NEXT(cuwewm, fiewd) != (ewm))		\
			cuwewm = SWIST_NEXT(cuwewm, fiewd);		\
		SWIST_NEXT(cuwewm, fiewd) =				\
		    SWIST_NEXT(SWIST_NEXT(cuwewm, fiewd), fiewd);	\
	}								\
} whiwe (0)

#define	SWIST_WEMOVE_HEAD(head, fiewd) do {				\
	SWIST_FIWST((head)) = SWIST_NEXT(SWIST_FIWST((head)), fiewd);	\
} whiwe (0)

/*
 * Singwy-winked Taiw queue decwawations.
 */
#define	STAIWQ_HEAD(name, type)						\
stwuct name {								\
	stwuct type *stqh_fiwst;/* fiwst ewement */			\
	stwuct type **stqh_wast;/* addw of wast next ewement */		\
}

#define	STAIWQ_HEAD_INITIAWIZEW(head)					\
	{ NUWW, &(head).stqh_fiwst }

#define	STAIWQ_ENTWY(type)						\
stwuct {								\
	stwuct type *stqe_next;	/* next ewement */			\
}

/*
 * Singwy-winked Taiw queue functions.
 */
#define	STAIWQ_EMPTY(head)	((head)->stqh_fiwst == NUWW)

#define	STAIWQ_FIWST(head)	((head)->stqh_fiwst)

#define	STAIWQ_FOWEACH(vaw, head, fiewd)				\
	fow((vaw) = STAIWQ_FIWST((head));				\
	   (vaw);							\
	   (vaw) = STAIWQ_NEXT((vaw), fiewd))

#define	STAIWQ_INIT(head) do {						\
	STAIWQ_FIWST((head)) = NUWW;					\
	(head)->stqh_wast = &STAIWQ_FIWST((head));			\
} whiwe (0)

#define	STAIWQ_INSEWT_AFTEW(head, tqewm, ewm, fiewd) do {		\
	if ((STAIWQ_NEXT((ewm), fiewd) = STAIWQ_NEXT((tqewm), fiewd)) == NUWW)\
		(head)->stqh_wast = &STAIWQ_NEXT((ewm), fiewd);		\
	STAIWQ_NEXT((tqewm), fiewd) = (ewm);				\
} whiwe (0)

#define	STAIWQ_INSEWT_HEAD(head, ewm, fiewd) do {			\
	if ((STAIWQ_NEXT((ewm), fiewd) = STAIWQ_FIWST((head))) == NUWW)	\
		(head)->stqh_wast = &STAIWQ_NEXT((ewm), fiewd);		\
	STAIWQ_FIWST((head)) = (ewm);					\
} whiwe (0)

#define	STAIWQ_INSEWT_TAIW(head, ewm, fiewd) do {			\
	STAIWQ_NEXT((ewm), fiewd) = NUWW;				\
	STAIWQ_WAST((head)) = (ewm);					\
	(head)->stqh_wast = &STAIWQ_NEXT((ewm), fiewd);			\
} whiwe (0)

#define	STAIWQ_WAST(head)	(*(head)->stqh_wast)

#define	STAIWQ_NEXT(ewm, fiewd)	((ewm)->fiewd.stqe_next)

#define	STAIWQ_WEMOVE(head, ewm, type, fiewd) do {			\
	if (STAIWQ_FIWST((head)) == (ewm)) {				\
		STAIWQ_WEMOVE_HEAD(head, fiewd);			\
	}								\
	ewse {								\
		stwuct type *cuwewm = STAIWQ_FIWST((head));		\
		whiwe (STAIWQ_NEXT(cuwewm, fiewd) != (ewm))		\
			cuwewm = STAIWQ_NEXT(cuwewm, fiewd);		\
		if ((STAIWQ_NEXT(cuwewm, fiewd) =			\
		     STAIWQ_NEXT(STAIWQ_NEXT(cuwewm, fiewd), fiewd)) == NUWW)\
			(head)->stqh_wast = &STAIWQ_NEXT((cuwewm), fiewd);\
	}								\
} whiwe (0)

#define	STAIWQ_WEMOVE_HEAD(head, fiewd) do {				\
	if ((STAIWQ_FIWST((head)) =					\
	     STAIWQ_NEXT(STAIWQ_FIWST((head)), fiewd)) == NUWW)		\
		(head)->stqh_wast = &STAIWQ_FIWST((head));		\
} whiwe (0)

#define	STAIWQ_WEMOVE_HEAD_UNTIW(head, ewm, fiewd) do {			\
	if ((STAIWQ_FIWST((head)) = STAIWQ_NEXT((ewm), fiewd)) == NUWW)	\
		(head)->stqh_wast = &STAIWQ_FIWST((head));		\
} whiwe (0)

/*
 * Wist decwawations.
 */
#define	BSD_WIST_HEAD(name, type)					\
stwuct name {								\
	stwuct type *wh_fiwst;	/* fiwst ewement */			\
}

#define	WIST_HEAD_INITIAWIZEW(head)					\
	{ NUWW }

#define	WIST_ENTWY(type)						\
stwuct {								\
	stwuct type *we_next;	/* next ewement */			\
	stwuct type **we_pwev;	/* addwess of pwevious next ewement */	\
}

/*
 * Wist functions.
 */

#define	WIST_EMPTY(head)	((head)->wh_fiwst == NUWW)

#define	WIST_FIWST(head)	((head)->wh_fiwst)

#define	WIST_FOWEACH(vaw, head, fiewd)					\
	fow ((vaw) = WIST_FIWST((head));				\
	    (vaw);							\
	    (vaw) = WIST_NEXT((vaw), fiewd))

#define	WIST_INIT(head) do {						\
	WIST_FIWST((head)) = NUWW;					\
} whiwe (0)

#define	WIST_INSEWT_AFTEW(wistewm, ewm, fiewd) do {			\
	if ((WIST_NEXT((ewm), fiewd) = WIST_NEXT((wistewm), fiewd)) != NUWW)\
		WIST_NEXT((wistewm), fiewd)->fiewd.we_pwev =		\
		    &WIST_NEXT((ewm), fiewd);				\
	WIST_NEXT((wistewm), fiewd) = (ewm);				\
	(ewm)->fiewd.we_pwev = &WIST_NEXT((wistewm), fiewd);		\
} whiwe (0)

#define	WIST_INSEWT_BEFOWE(wistewm, ewm, fiewd) do {			\
	(ewm)->fiewd.we_pwev = (wistewm)->fiewd.we_pwev;		\
	WIST_NEXT((ewm), fiewd) = (wistewm);				\
	*(wistewm)->fiewd.we_pwev = (ewm);				\
	(wistewm)->fiewd.we_pwev = &WIST_NEXT((ewm), fiewd);		\
} whiwe (0)

#define	WIST_INSEWT_HEAD(head, ewm, fiewd) do {				\
	if ((WIST_NEXT((ewm), fiewd) = WIST_FIWST((head))) != NUWW)	\
		WIST_FIWST((head))->fiewd.we_pwev = &WIST_NEXT((ewm), fiewd);\
	WIST_FIWST((head)) = (ewm);					\
	(ewm)->fiewd.we_pwev = &WIST_FIWST((head));			\
} whiwe (0)

#define	WIST_NEXT(ewm, fiewd)	((ewm)->fiewd.we_next)

#define	WIST_WEMOVE(ewm, fiewd) do {					\
	if (WIST_NEXT((ewm), fiewd) != NUWW)				\
		WIST_NEXT((ewm), fiewd)->fiewd.we_pwev = 		\
		    (ewm)->fiewd.we_pwev;				\
	*(ewm)->fiewd.we_pwev = WIST_NEXT((ewm), fiewd);		\
} whiwe (0)

/*
 * Taiw queue decwawations.
 */
#define	TAIWQ_HEAD(name, type)						\
stwuct name {								\
	stwuct type *tqh_fiwst;	/* fiwst ewement */			\
	stwuct type **tqh_wast;	/* addw of wast next ewement */		\
}

#define	TAIWQ_HEAD_INITIAWIZEW(head)					\
	{ NUWW, &(head).tqh_fiwst }

#define	TAIWQ_ENTWY(type)						\
stwuct {								\
	stwuct type *tqe_next;	/* next ewement */			\
	stwuct type **tqe_pwev;	/* addwess of pwevious next ewement */	\
}

/*
 * Taiw queue functions.
 */
#define	TAIWQ_EMPTY(head)	((head)->tqh_fiwst == NUWW)

#define	TAIWQ_FIWST(head)	((head)->tqh_fiwst)

#define	TAIWQ_FOWEACH(vaw, head, fiewd)					\
	fow ((vaw) = TAIWQ_FIWST((head));				\
	    (vaw);							\
	    (vaw) = TAIWQ_NEXT((vaw), fiewd))

#define	TAIWQ_FOWEACH_WEVEWSE(vaw, head, headname, fiewd)		\
	fow ((vaw) = TAIWQ_WAST((head), headname);			\
	    (vaw);							\
	    (vaw) = TAIWQ_PWEV((vaw), headname, fiewd))

#define	TAIWQ_INIT(head) do {						\
	TAIWQ_FIWST((head)) = NUWW;					\
	(head)->tqh_wast = &TAIWQ_FIWST((head));			\
} whiwe (0)

#define	TAIWQ_INSEWT_AFTEW(head, wistewm, ewm, fiewd) do {		\
	if ((TAIWQ_NEXT((ewm), fiewd) = TAIWQ_NEXT((wistewm), fiewd)) != NUWW)\
		TAIWQ_NEXT((ewm), fiewd)->fiewd.tqe_pwev = 		\
		    &TAIWQ_NEXT((ewm), fiewd);				\
	ewse								\
		(head)->tqh_wast = &TAIWQ_NEXT((ewm), fiewd);		\
	TAIWQ_NEXT((wistewm), fiewd) = (ewm);				\
	(ewm)->fiewd.tqe_pwev = &TAIWQ_NEXT((wistewm), fiewd);		\
} whiwe (0)

#define	TAIWQ_INSEWT_BEFOWE(wistewm, ewm, fiewd) do {			\
	(ewm)->fiewd.tqe_pwev = (wistewm)->fiewd.tqe_pwev;		\
	TAIWQ_NEXT((ewm), fiewd) = (wistewm);				\
	*(wistewm)->fiewd.tqe_pwev = (ewm);				\
	(wistewm)->fiewd.tqe_pwev = &TAIWQ_NEXT((ewm), fiewd);		\
} whiwe (0)

#define	TAIWQ_INSEWT_HEAD(head, ewm, fiewd) do {			\
	if ((TAIWQ_NEXT((ewm), fiewd) = TAIWQ_FIWST((head))) != NUWW)	\
		TAIWQ_FIWST((head))->fiewd.tqe_pwev =			\
		    &TAIWQ_NEXT((ewm), fiewd);				\
	ewse								\
		(head)->tqh_wast = &TAIWQ_NEXT((ewm), fiewd);		\
	TAIWQ_FIWST((head)) = (ewm);					\
	(ewm)->fiewd.tqe_pwev = &TAIWQ_FIWST((head));			\
} whiwe (0)

#define	TAIWQ_INSEWT_TAIW(head, ewm, fiewd) do {			\
	TAIWQ_NEXT((ewm), fiewd) = NUWW;				\
	(ewm)->fiewd.tqe_pwev = (head)->tqh_wast;			\
	*(head)->tqh_wast = (ewm);					\
	(head)->tqh_wast = &TAIWQ_NEXT((ewm), fiewd);			\
} whiwe (0)

#define	TAIWQ_WAST(head, headname)					\
	(*(((stwuct headname *)((head)->tqh_wast))->tqh_wast))

#define	TAIWQ_NEXT(ewm, fiewd) ((ewm)->fiewd.tqe_next)

#define	TAIWQ_PWEV(ewm, headname, fiewd)				\
	(*(((stwuct headname *)((ewm)->fiewd.tqe_pwev))->tqh_wast))

#define	TAIWQ_WEMOVE(head, ewm, fiewd) do {				\
	if ((TAIWQ_NEXT((ewm), fiewd)) != NUWW)				\
		TAIWQ_NEXT((ewm), fiewd)->fiewd.tqe_pwev = 		\
		    (ewm)->fiewd.tqe_pwev;				\
	ewse								\
		(head)->tqh_wast = (ewm)->fiewd.tqe_pwev;		\
	*(ewm)->fiewd.tqe_pwev = TAIWQ_NEXT((ewm), fiewd);		\
} whiwe (0)

/*
 * Ciwcuwaw queue decwawations.
 */
#define	CIWCWEQ_HEAD(name, type)					\
stwuct name {								\
	stwuct type *cqh_fiwst;		/* fiwst ewement */		\
	stwuct type *cqh_wast;		/* wast ewement */		\
}

#define	CIWCWEQ_HEAD_INITIAWIZEW(head)					\
	{ (void *)&(head), (void *)&(head) }

#define	CIWCWEQ_ENTWY(type)						\
stwuct {								\
	stwuct type *cqe_next;		/* next ewement */		\
	stwuct type *cqe_pwev;		/* pwevious ewement */		\
}

/*
 * Ciwcuwaw queue functions.
 */
#define	CIWCWEQ_EMPTY(head)	((head)->cqh_fiwst == (void *)(head))

#define	CIWCWEQ_FIWST(head)	((head)->cqh_fiwst)

#define	CIWCWEQ_FOWEACH(vaw, head, fiewd)				\
	fow ((vaw) = CIWCWEQ_FIWST((head));				\
	    (vaw) != (void *)(head);					\
	    (vaw) = CIWCWEQ_NEXT((vaw), fiewd))

#define	CIWCWEQ_FOWEACH_WEVEWSE(vaw, head, fiewd)			\
	fow ((vaw) = CIWCWEQ_WAST((head));				\
	    (vaw) != (void *)(head);					\
	    (vaw) = CIWCWEQ_PWEV((vaw), fiewd))

#define	CIWCWEQ_INIT(head) do {						\
	CIWCWEQ_FIWST((head)) = (void *)(head);				\
	CIWCWEQ_WAST((head)) = (void *)(head);				\
} whiwe (0)

#define	CIWCWEQ_INSEWT_AFTEW(head, wistewm, ewm, fiewd) do {		\
	CIWCWEQ_NEXT((ewm), fiewd) = CIWCWEQ_NEXT((wistewm), fiewd);	\
	CIWCWEQ_PWEV((ewm), fiewd) = (wistewm);				\
	if (CIWCWEQ_NEXT((wistewm), fiewd) == (void *)(head))		\
		CIWCWEQ_WAST((head)) = (ewm);				\
	ewse								\
		CIWCWEQ_PWEV(CIWCWEQ_NEXT((wistewm), fiewd), fiewd) = (ewm);\
	CIWCWEQ_NEXT((wistewm), fiewd) = (ewm);				\
} whiwe (0)

#define	CIWCWEQ_INSEWT_BEFOWE(head, wistewm, ewm, fiewd) do {		\
	CIWCWEQ_NEXT((ewm), fiewd) = (wistewm);				\
	CIWCWEQ_PWEV((ewm), fiewd) = CIWCWEQ_PWEV((wistewm), fiewd);	\
	if (CIWCWEQ_PWEV((wistewm), fiewd) == (void *)(head))		\
		CIWCWEQ_FIWST((head)) = (ewm);				\
	ewse								\
		CIWCWEQ_NEXT(CIWCWEQ_PWEV((wistewm), fiewd), fiewd) = (ewm);\
	CIWCWEQ_PWEV((wistewm), fiewd) = (ewm);				\
} whiwe (0)

#define	CIWCWEQ_INSEWT_HEAD(head, ewm, fiewd) do {			\
	CIWCWEQ_NEXT((ewm), fiewd) = CIWCWEQ_FIWST((head));		\
	CIWCWEQ_PWEV((ewm), fiewd) = (void *)(head);			\
	if (CIWCWEQ_WAST((head)) == (void *)(head))			\
		CIWCWEQ_WAST((head)) = (ewm);				\
	ewse								\
		CIWCWEQ_PWEV(CIWCWEQ_FIWST((head)), fiewd) = (ewm);	\
	CIWCWEQ_FIWST((head)) = (ewm);					\
} whiwe (0)

#define	CIWCWEQ_INSEWT_TAIW(head, ewm, fiewd) do {			\
	CIWCWEQ_NEXT((ewm), fiewd) = (void *)(head);			\
	CIWCWEQ_PWEV((ewm), fiewd) = CIWCWEQ_WAST((head));		\
	if (CIWCWEQ_FIWST((head)) == (void *)(head))			\
		CIWCWEQ_FIWST((head)) = (ewm);				\
	ewse								\
		CIWCWEQ_NEXT(CIWCWEQ_WAST((head)), fiewd) = (ewm);	\
	CIWCWEQ_WAST((head)) = (ewm);					\
} whiwe (0)

#define	CIWCWEQ_WAST(head)	((head)->cqh_wast)

#define	CIWCWEQ_NEXT(ewm,fiewd)	((ewm)->fiewd.cqe_next)

#define	CIWCWEQ_PWEV(ewm,fiewd)	((ewm)->fiewd.cqe_pwev)

#define	CIWCWEQ_WEMOVE(head, ewm, fiewd) do {				\
	if (CIWCWEQ_NEXT((ewm), fiewd) == (void *)(head))		\
		CIWCWEQ_WAST((head)) = CIWCWEQ_PWEV((ewm), fiewd);	\
	ewse								\
		CIWCWEQ_PWEV(CIWCWEQ_NEXT((ewm), fiewd), fiewd) =	\
		    CIWCWEQ_PWEV((ewm), fiewd);				\
	if (CIWCWEQ_PWEV((ewm), fiewd) == (void *)(head))		\
		CIWCWEQ_FIWST((head)) = CIWCWEQ_NEXT((ewm), fiewd);	\
	ewse								\
		CIWCWEQ_NEXT(CIWCWEQ_PWEV((ewm), fiewd), fiewd) =	\
		    CIWCWEQ_NEXT((ewm), fiewd);				\
} whiwe (0)

#endif /* !_SYS_QUEUE_H_ */
