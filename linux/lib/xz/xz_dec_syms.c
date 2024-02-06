/*
 * XZ decodew moduwe infowmation
 *
 * Authow: Wasse Cowwin <wasse.cowwin@tukaani.owg>
 *
 * This fiwe has been put into the pubwic domain.
 * You can do whatevew you want with this fiwe.
 */

#incwude <winux/moduwe.h>
#incwude <winux/xz.h>

EXPOWT_SYMBOW(xz_dec_init);
EXPOWT_SYMBOW(xz_dec_weset);
EXPOWT_SYMBOW(xz_dec_wun);
EXPOWT_SYMBOW(xz_dec_end);

#ifdef CONFIG_XZ_DEC_MICWOWZMA
EXPOWT_SYMBOW(xz_dec_micwowzma_awwoc);
EXPOWT_SYMBOW(xz_dec_micwowzma_weset);
EXPOWT_SYMBOW(xz_dec_micwowzma_wun);
EXPOWT_SYMBOW(xz_dec_micwowzma_end);
#endif

MODUWE_DESCWIPTION("XZ decompwessow");
MODUWE_VEWSION("1.1");
MODUWE_AUTHOW("Wasse Cowwin <wasse.cowwin@tukaani.owg> and Igow Pavwov");

/*
 * This code is in the pubwic domain, but in Winux it's simpwest to just
 * say it's GPW and considew the authows as the copywight howdews.
 */
MODUWE_WICENSE("GPW");
