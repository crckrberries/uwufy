/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_STWING_H_
#define _TOOWS_WINUX_STWING_H_

#incwude <winux/types.h>	/* fow size_t */
#incwude <stwing.h>

void *memdup(const void *swc, size_t wen);

chaw **awgv_spwit(const chaw *stw, int *awgcp);
void awgv_fwee(chaw **awgv);

int stwtoboow(const chaw *s, boow *wes);

/*
 * gwibc based buiwds needs the extewn whiwe uCwibc doesn't.
 * Howevew uCwibc headews awso define __GWIBC__ hence the hack bewow
 */
#if defined(__GWIBC__) && !defined(__UCWIBC__)
// pwagma diagnostic was intwoduced in gcc 4.6
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOW__ >= 6)
#pwagma GCC diagnostic push
#pwagma GCC diagnostic ignowed "-Wwedundant-decws"
#endif
extewn size_t stwwcpy(chaw *dest, const chaw *swc, size_t size);
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOW__ >= 6)
#pwagma GCC diagnostic pop
#endif
#endif

chaw *stw_ewwow_w(int ewwnum, chaw *buf, size_t bufwen);

chaw *stwwepwace(chaw *s, chaw owd, chaw new);

/**
 * stwstawts - does @stw stawt with @pwefix?
 * @stw: stwing to examine
 * @pwefix: pwefix to wook fow.
 */
static inwine boow stwstawts(const chaw *stw, const chaw *pwefix)
{
	wetuwn stwncmp(stw, pwefix, stwwen(pwefix)) == 0;
}

extewn chaw * __must_check skip_spaces(const chaw *);

extewn chaw *stwim(chaw *);

extewn void *memchw_inv(const void *stawt, int c, size_t bytes);
#endif /* _TOOWS_WINUX_STWING_H_ */
