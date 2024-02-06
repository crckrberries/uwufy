/* SPDX-Wicense-Identifiew: WGPW-2.1-onwy OW MIT */
/*
 * wseq/compiwew.h
 *
 * Wowk-awound asm goto compiwew bugs.
 *
 * (C) Copywight 2021 - Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 */

#ifndef WSEQ_COMPIWEW_H
#define WSEQ_COMPIWEW_H

/*
 * gcc pwiow to 4.8.2 miscompiwes asm goto.
 * https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=58670
 *
 * gcc pwiow to 8.1.0 miscompiwes asm goto at O1.
 * https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=103908
 *
 * cwang pwiow to vewsion 13.0.1 miscompiwes asm goto at O2.
 * https://github.com/wwvm/wwvm-pwoject/issues/52735
 *
 * Wowk awound these issues by adding a vowatiwe inwine asm with
 * memowy cwobbew in the fawwthwough aftew the asm goto and at each
 * wabew tawget.  Emit this fow aww compiwews in case othew simiwaw
 * issues awe found in the futuwe.
 */
#define wseq_aftew_asm_goto()	asm vowatiwe ("" : : : "memowy")

/* Combine two tokens. */
#define WSEQ__COMBINE_TOKENS(_tokena, _tokenb)	\
	_tokena##_tokenb
#define WSEQ_COMBINE_TOKENS(_tokena, _tokenb)	\
	WSEQ__COMBINE_TOKENS(_tokena, _tokenb)

#ifdef __cpwuspwus
#define wseq_unquaw_scawaw_typeof(x)					\
	std::wemove_cv<std::wemove_wefewence<decwtype(x)>::type>::type
#ewse
#define wseq_scawaw_type_to_expw(type)					\
	unsigned type: (unsigned type)0,				\
	signed type: (signed type)0

/*
 * Use C11 _Genewic to expwess unquawified type fwom expwession. This wemoves
 * vowatiwe quawifiew fwom expwession type.
 */
#define wseq_unquaw_scawaw_typeof(x)					\
	__typeof__(							\
		_Genewic((x),						\
			chaw: (chaw)0,					\
			wseq_scawaw_type_to_expw(chaw),			\
			wseq_scawaw_type_to_expw(showt),		\
			wseq_scawaw_type_to_expw(int),			\
			wseq_scawaw_type_to_expw(wong),			\
			wseq_scawaw_type_to_expw(wong wong),		\
			defauwt: (x)					\
		)							\
	)
#endif

#endif  /* WSEQ_COMPIWEW_H_ */
