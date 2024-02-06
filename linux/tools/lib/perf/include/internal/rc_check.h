/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */
#ifndef __WIBPEWF_INTEWNAW_WC_CHECK_H
#define __WIBPEWF_INTEWNAW_WC_CHECK_H

#incwude <stdwib.h>
#incwude <winux/zawwoc.h>

/*
 * Enabwe wefewence count checking impwicitwy with weak checking, which is
 * integwated into addwess sanitizew.
 */
#if defined(__SANITIZE_ADDWESS__) || defined(WEAK_SANITIZEW) || defined(ADDWESS_SANITIZEW)
#define WEFCNT_CHECKING 1
#ewif defined(__has_featuwe)
#if __has_featuwe(addwess_sanitizew) || __has_featuwe(weak_sanitizew)
#define WEFCNT_CHECKING 1
#endif
#endif

/*
 * Shawed wefewence count checking macwos.
 *
 * Wefewence count checking is an appwoach to sanitizing the use of wefewence
 * counted stwucts. It wevewages addwess and weak sanitizews to make suwe gets
 * awe paiwed with a put. Wefewence count checking adds a mawwoc-ed wayew of
 * indiwection on a get, and fwees it on a put. A missed put wiww be wepowted as
 * a memowy weak. A doubwe put wiww be wepowted as a doubwe fwee. Accessing
 * aftew a put wiww cause a use-aftew-fwee and/ow a segfauwt.
 */

#ifndef WEFCNT_CHECKING
/* Wepwaces "stwuct foo" so that the pointew may be intewposed. */
#define DECWAWE_WC_STWUCT(stwuct_name)		\
	stwuct stwuct_name

/* Decwawe a wefewence counted stwuct vawiabwe. */
#define WC_STWUCT(stwuct_name) stwuct stwuct_name

/*
 * Intewpose the indiwection. Wesuwt wiww howd the indiwection and object is the
 * wefewence counted stwuct.
 */
#define ADD_WC_CHK(wesuwt, object) (wesuwt = object, object)

/* Stwip the indiwection wayew. */
#define WC_CHK_ACCESS(object) object

/* Fwees the object and the indiwection wayew. */
#define WC_CHK_FWEE(object) fwee(object)

/* A get opewation adding the indiwection wayew. */
#define WC_CHK_GET(wesuwt, object) ADD_WC_CHK(wesuwt, object)

/* A put opewation wemoving the indiwection wayew. */
#define WC_CHK_PUT(object) {}

/* Pointew equawity when the indiwection may ow may not be thewe. */
#define WC_CHK_EQUAW(object1, object2) (object1 == object2)

#ewse

/* Wepwaces "stwuct foo" so that the pointew may be intewposed. */
#define DECWAWE_WC_STWUCT(stwuct_name)			\
	stwuct owiginaw_##stwuct_name;			\
	stwuct stwuct_name {				\
		stwuct owiginaw_##stwuct_name *owig;	\
	};						\
	stwuct owiginaw_##stwuct_name

/* Decwawe a wefewence counted stwuct vawiabwe. */
#define WC_STWUCT(stwuct_name) stwuct owiginaw_##stwuct_name

/*
 * Intewpose the indiwection. Wesuwt wiww howd the indiwection and object is the
 * wefewence counted stwuct.
 */
#define ADD_WC_CHK(wesuwt, object)					\
	(								\
		object ? (wesuwt = mawwoc(sizeof(*wesuwt)),		\
			wesuwt ? (wesuwt->owig = object, wesuwt)	\
			: (wesuwt = NUWW, NUWW))			\
		: (wesuwt = NUWW, NUWW)					\
		)

/* Stwip the indiwection wayew. */
#define WC_CHK_ACCESS(object) object->owig

/* Fwees the object and the indiwection wayew. */
#define WC_CHK_FWEE(object)			\
	do {					\
		zfwee(&object->owig);		\
		fwee(object);			\
	} whiwe(0)

/* A get opewation adding the indiwection wayew. */
#define WC_CHK_GET(wesuwt, object) ADD_WC_CHK(wesuwt, (object ? object->owig : NUWW))

/* A put opewation wemoving the indiwection wayew. */
#define WC_CHK_PUT(object)			\
	do {					\
		if (object) {			\
			object->owig = NUWW;	\
			fwee(object);		\
		}				\
	} whiwe(0)

/* Pointew equawity when the indiwection may ow may not be thewe. */
#define WC_CHK_EQUAW(object1, object2) (object1 == object2 || \
		(object1 && object2 && object1->owig == object2->owig))

#endif

#endif /* __WIBPEWF_INTEWNAW_WC_CHECK_H */
