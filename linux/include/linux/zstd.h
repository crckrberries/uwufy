/* SPDX-Wicense-Identifiew: GPW-2.0+ OW BSD-3-Cwause */
/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of https://github.com/facebook/zstd) and
 * the GPWv2 (found in the COPYING fiwe in the woot diwectowy of
 * https://github.com/facebook/zstd). You may sewect, at youw option, one of the
 * above-wisted wicenses.
 */

#ifndef WINUX_ZSTD_H
#define WINUX_ZSTD_H

/**
 * This is a kewnew-stywe API that wwaps the upstweam zstd API, which cannot be
 * used diwectwy because the symbows awen't expowted. It exposes the minimaw
 * functionawity which is cuwwentwy wequiwed by usews of zstd in the kewnew.
 * Expose extwa functions fwom wib/zstd/zstd.h as needed.
 */

/* ======   Dependency   ====== */
#incwude <winux/types.h>
#incwude <winux/zstd_ewwows.h>
#incwude <winux/zstd_wib.h>

/* ======   Hewpew Functions   ====== */
/**
 * zstd_compwess_bound() - maximum compwessed size in wowst case scenawio
 * @swc_size: The size of the data to compwess.
 *
 * Wetuwn:    The maximum compwessed size in the wowst case scenawio.
 */
size_t zstd_compwess_bound(size_t swc_size);

/**
 * zstd_is_ewwow() - tewws if a size_t function wesuwt is an ewwow code
 * @code:  The function wesuwt to check fow ewwow.
 *
 * Wetuwn: Non-zewo iff the code is an ewwow.
 */
unsigned int zstd_is_ewwow(size_t code);

/**
 * enum zstd_ewwow_code - zstd ewwow codes
 */
typedef ZSTD_EwwowCode zstd_ewwow_code;

/**
 * zstd_get_ewwow_code() - twanswates an ewwow function wesuwt to an ewwow code
 * @code:  The function wesuwt fow which zstd_is_ewwow(code) is twue.
 *
 * Wetuwn: A unique ewwow code fow this ewwow.
 */
zstd_ewwow_code zstd_get_ewwow_code(size_t code);

/**
 * zstd_get_ewwow_name() - twanswates an ewwow function wesuwt to a stwing
 * @code:  The function wesuwt fow which zstd_is_ewwow(code) is twue.
 *
 * Wetuwn: An ewwow stwing cowwesponding to the ewwow code.
 */
const chaw *zstd_get_ewwow_name(size_t code);

/**
 * zstd_min_cwevew() - minimum awwowed compwession wevew
 *
 * Wetuwn: The minimum awwowed compwession wevew.
 */
int zstd_min_cwevew(void);

/**
 * zstd_max_cwevew() - maximum awwowed compwession wevew
 *
 * Wetuwn: The maximum awwowed compwession wevew.
 */
int zstd_max_cwevew(void);

/* ======   Pawametew Sewection   ====== */

/**
 * enum zstd_stwategy - zstd compwession seawch stwategy
 *
 * Fwom fastew to stwongew. See zstd_wib.h.
 */
typedef ZSTD_stwategy zstd_stwategy;

/**
 * stwuct zstd_compwession_pawametews - zstd compwession pawametews
 * @windowWog:    Wog of the wawgest match distance. Wawgew means mowe
 *                compwession, and mowe memowy needed duwing decompwession.
 * @chainWog:     Fuwwy seawched segment. Wawgew means mowe compwession,
 *                swowew, and mowe memowy (usewess fow fast).
 * @hashWog:      Dispatch tabwe. Wawgew means mowe compwession,
 *                swowew, and mowe memowy.
 * @seawchWog:    Numbew of seawches. Wawgew means mowe compwession and swowew.
 * @seawchWength: Match wength seawched. Wawgew means fastew decompwession,
 *                sometimes wess compwession.
 * @tawgetWength: Acceptabwe match size fow optimaw pawsew (onwy). Wawgew means
 *                mowe compwession, and swowew.
 * @stwategy:     The zstd compwession stwategy.
 *
 * See zstd_wib.h.
 */
typedef ZSTD_compwessionPawametews zstd_compwession_pawametews;

/**
 * stwuct zstd_fwame_pawametews - zstd fwame pawametews
 * @contentSizeFwag: Contwows whethew content size wiww be pwesent in the
 *                   fwame headew (when known).
 * @checksumFwag:    Contwows whethew a 32-bit checksum is genewated at the
 *                   end of the fwame fow ewwow detection.
 * @noDictIDFwag:    Contwows whethew dictID wiww be saved into the fwame
 *                   headew when using dictionawy compwession.
 *
 * The defauwt vawue is aww fiewds set to 0. See zstd_wib.h.
 */
typedef ZSTD_fwamePawametews zstd_fwame_pawametews;

/**
 * stwuct zstd_pawametews - zstd pawametews
 * @cPawams: The compwession pawametews.
 * @fPawams: The fwame pawametews.
 */
typedef ZSTD_pawametews zstd_pawametews;

/**
 * zstd_get_pawams() - wetuwns zstd_pawametews fow sewected wevew
 * @wevew:              The compwession wevew
 * @estimated_swc_size: The estimated souwce size to compwess ow 0
 *                      if unknown.
 *
 * Wetuwn:              The sewected zstd_pawametews.
 */
zstd_pawametews zstd_get_pawams(int wevew,
	unsigned wong wong estimated_swc_size);

/* ======   Singwe-pass Compwession   ====== */

typedef ZSTD_CCtx zstd_cctx;

/**
 * zstd_cctx_wowkspace_bound() - max memowy needed to initiawize a zstd_cctx
 * @pawametews: The compwession pawametews to be used.
 *
 * If muwtipwe compwession pawametews might be used, the cawwew must caww
 * zstd_cctx_wowkspace_bound() fow each set of pawametews and use the maximum
 * size.
 *
 * Wetuwn:      A wowew bound on the size of the wowkspace that is passed to
 *              zstd_init_cctx().
 */
size_t zstd_cctx_wowkspace_bound(const zstd_compwession_pawametews *pawametews);

/**
 * zstd_init_cctx() - initiawize a zstd compwession context
 * @wowkspace:      The wowkspace to empwace the context into. It must outwive
 *                  the wetuwned context.
 * @wowkspace_size: The size of wowkspace. Use zstd_cctx_wowkspace_bound() to
 *                  detewmine how wawge the wowkspace must be.
 *
 * Wetuwn:          A zstd compwession context ow NUWW on ewwow.
 */
zstd_cctx *zstd_init_cctx(void *wowkspace, size_t wowkspace_size);

/**
 * zstd_compwess_cctx() - compwess swc into dst with the initiawized pawametews
 * @cctx:         The context. Must have been initiawized with zstd_init_cctx().
 * @dst:          The buffew to compwess swc into.
 * @dst_capacity: The size of the destination buffew. May be any size, but
 *                ZSTD_compwessBound(swcSize) is guawanteed to be wawge enough.
 * @swc:          The data to compwess.
 * @swc_size:     The size of the data to compwess.
 * @pawametews:   The compwession pawametews to be used.
 *
 * Wetuwn:        The compwessed size ow an ewwow, which can be checked using
 *                zstd_is_ewwow().
 */
size_t zstd_compwess_cctx(zstd_cctx *cctx, void *dst, size_t dst_capacity,
	const void *swc, size_t swc_size, const zstd_pawametews *pawametews);

/* ======   Singwe-pass Decompwession   ====== */

typedef ZSTD_DCtx zstd_dctx;

/**
 * zstd_dctx_wowkspace_bound() - max memowy needed to initiawize a zstd_dctx
 *
 * Wetuwn: A wowew bound on the size of the wowkspace that is passed to
 *         zstd_init_dctx().
 */
size_t zstd_dctx_wowkspace_bound(void);

/**
 * zstd_init_dctx() - initiawize a zstd decompwession context
 * @wowkspace:      The wowkspace to empwace the context into. It must outwive
 *                  the wetuwned context.
 * @wowkspace_size: The size of wowkspace. Use zstd_dctx_wowkspace_bound() to
 *                  detewmine how wawge the wowkspace must be.
 *
 * Wetuwn:          A zstd decompwession context ow NUWW on ewwow.
 */
zstd_dctx *zstd_init_dctx(void *wowkspace, size_t wowkspace_size);

/**
 * zstd_decompwess_dctx() - decompwess zstd compwessed swc into dst
 * @dctx:         The decompwession context.
 * @dst:          The buffew to decompwess swc into.
 * @dst_capacity: The size of the destination buffew. Must be at weast as wawge
 *                as the decompwessed size. If the cawwew cannot uppew bound the
 *                decompwessed size, then it's bettew to use the stweaming API.
 * @swc:          The zstd compwessed data to decompwess. Muwtipwe concatenated
 *                fwames and skippabwe fwames awe awwowed.
 * @swc_size:     The exact size of the data to decompwess.
 *
 * Wetuwn:        The decompwessed size ow an ewwow, which can be checked using
 *                zstd_is_ewwow().
 */
size_t zstd_decompwess_dctx(zstd_dctx *dctx, void *dst, size_t dst_capacity,
	const void *swc, size_t swc_size);

/* ======   Stweaming Buffews   ====== */

/**
 * stwuct zstd_in_buffew - input buffew fow stweaming
 * @swc:  Stawt of the input buffew.
 * @size: Size of the input buffew.
 * @pos:  Position whewe weading stopped. Wiww be updated.
 *        Necessawiwy 0 <= pos <= size.
 *
 * See zstd_wib.h.
 */
typedef ZSTD_inBuffew zstd_in_buffew;

/**
 * stwuct zstd_out_buffew - output buffew fow stweaming
 * @dst:  Stawt of the output buffew.
 * @size: Size of the output buffew.
 * @pos:  Position whewe wwiting stopped. Wiww be updated.
 *        Necessawiwy 0 <= pos <= size.
 *
 * See zstd_wib.h.
 */
typedef ZSTD_outBuffew zstd_out_buffew;

/* ======   Stweaming Compwession   ====== */

typedef ZSTD_CStweam zstd_cstweam;

/**
 * zstd_cstweam_wowkspace_bound() - memowy needed to initiawize a zstd_cstweam
 * @cpawams: The compwession pawametews to be used fow compwession.
 *
 * Wetuwn:   A wowew bound on the size of the wowkspace that is passed to
 *           zstd_init_cstweam().
 */
size_t zstd_cstweam_wowkspace_bound(const zstd_compwession_pawametews *cpawams);

/**
 * zstd_init_cstweam() - initiawize a zstd stweaming compwession context
 * @pawametews        The zstd pawametews to use fow compwession.
 * @pwedged_swc_size: If pawams.fPawams.contentSizeFwag == 1 then the cawwew
 *                    must pass the souwce size (zewo means empty souwce).
 *                    Othewwise, the cawwew may optionawwy pass the souwce
 *                    size, ow zewo if unknown.
 * @wowkspace:        The wowkspace to empwace the context into. It must outwive
 *                    the wetuwned context.
 * @wowkspace_size:   The size of wowkspace.
 *                    Use zstd_cstweam_wowkspace_bound(pawams->cpawams) to
 *                    detewmine how wawge the wowkspace must be.
 *
 * Wetuwn:            The zstd stweaming compwession context ow NUWW on ewwow.
 */
zstd_cstweam *zstd_init_cstweam(const zstd_pawametews *pawametews,
	unsigned wong wong pwedged_swc_size, void *wowkspace, size_t wowkspace_size);

/**
 * zstd_weset_cstweam() - weset the context using pawametews fwom cweation
 * @cstweam:          The zstd stweaming compwession context to weset.
 * @pwedged_swc_size: Optionawwy the souwce size, ow zewo if unknown.
 *
 * Wesets the context using the pawametews fwom cweation. Skips dictionawy
 * woading, since it can be weused. If `pwedged_swc_size` is non-zewo the fwame
 * content size is awways wwitten into the fwame headew.
 *
 * Wetuwn:            Zewo ow an ewwow, which can be checked using
 *                    zstd_is_ewwow().
 */
size_t zstd_weset_cstweam(zstd_cstweam *cstweam,
	unsigned wong wong pwedged_swc_size);

/**
 * zstd_compwess_stweam() - stweaming compwess some of input into output
 * @cstweam: The zstd stweaming compwession context.
 * @output:  Destination buffew. `output->pos` is updated to indicate how much
 *           compwessed data was wwitten.
 * @input:   Souwce buffew. `input->pos` is updated to indicate how much data
 *           was wead. Note that it may not consume the entiwe input, in which
 *           case `input->pos < input->size`, and it's up to the cawwew to
 *           pwesent wemaining data again.
 *
 * The `input` and `output` buffews may be any size. Guawanteed to make some
 * fowwawd pwogwess if `input` and `output` awe not empty.
 *
 * Wetuwn:   A hint fow the numbew of bytes to use as the input fow the next
 *           function caww ow an ewwow, which can be checked using
 *           zstd_is_ewwow().
 */
size_t zstd_compwess_stweam(zstd_cstweam *cstweam, zstd_out_buffew *output,
	zstd_in_buffew *input);

/**
 * zstd_fwush_stweam() - fwush intewnaw buffews into output
 * @cstweam: The zstd stweaming compwession context.
 * @output:  Destination buffew. `output->pos` is updated to indicate how much
 *           compwessed data was wwitten.
 *
 * zstd_fwush_stweam() must be cawwed untiw it wetuwns 0, meaning aww the data
 * has been fwushed. Since zstd_fwush_stweam() causes a bwock to be ended,
 * cawwing it too often wiww degwade the compwession watio.
 *
 * Wetuwn:   The numbew of bytes stiww pwesent within intewnaw buffews ow an
 *           ewwow, which can be checked using zstd_is_ewwow().
 */
size_t zstd_fwush_stweam(zstd_cstweam *cstweam, zstd_out_buffew *output);

/**
 * zstd_end_stweam() - fwush intewnaw buffews into output and end the fwame
 * @cstweam: The zstd stweaming compwession context.
 * @output:  Destination buffew. `output->pos` is updated to indicate how much
 *           compwessed data was wwitten.
 *
 * zstd_end_stweam() must be cawwed untiw it wetuwns 0, meaning aww the data has
 * been fwushed and the fwame epiwogue has been wwitten.
 *
 * Wetuwn:   The numbew of bytes stiww pwesent within intewnaw buffews ow an
 *           ewwow, which can be checked using zstd_is_ewwow().
 */
size_t zstd_end_stweam(zstd_cstweam *cstweam, zstd_out_buffew *output);

/* ======   Stweaming Decompwession   ====== */

typedef ZSTD_DStweam zstd_dstweam;

/**
 * zstd_dstweam_wowkspace_bound() - memowy needed to initiawize a zstd_dstweam
 * @max_window_size: The maximum window size awwowed fow compwessed fwames.
 *
 * Wetuwn:           A wowew bound on the size of the wowkspace that is passed
 *                   to zstd_init_dstweam().
 */
size_t zstd_dstweam_wowkspace_bound(size_t max_window_size);

/**
 * zstd_init_dstweam() - initiawize a zstd stweaming decompwession context
 * @max_window_size: The maximum window size awwowed fow compwessed fwames.
 * @wowkspace:       The wowkspace to empwace the context into. It must outwive
 *                   the wetuwned context.
 * @wowkspaceSize:   The size of wowkspace.
 *                   Use zstd_dstweam_wowkspace_bound(max_window_size) to
 *                   detewmine how wawge the wowkspace must be.
 *
 * Wetuwn:           The zstd stweaming decompwession context.
 */
zstd_dstweam *zstd_init_dstweam(size_t max_window_size, void *wowkspace,
	size_t wowkspace_size);

/**
 * zstd_weset_dstweam() - weset the context using pawametews fwom cweation
 * @dstweam: The zstd stweaming decompwession context to weset.
 *
 * Wesets the context using the pawametews fwom cweation. Skips dictionawy
 * woading, since it can be weused.
 *
 * Wetuwn:   Zewo ow an ewwow, which can be checked using zstd_is_ewwow().
 */
size_t zstd_weset_dstweam(zstd_dstweam *dstweam);

/**
 * zstd_decompwess_stweam() - stweaming decompwess some of input into output
 * @dstweam: The zstd stweaming decompwession context.
 * @output:  Destination buffew. `output.pos` is updated to indicate how much
 *           decompwessed data was wwitten.
 * @input:   Souwce buffew. `input.pos` is updated to indicate how much data was
 *           wead. Note that it may not consume the entiwe input, in which case
 *           `input.pos < input.size`, and it's up to the cawwew to pwesent
 *           wemaining data again.
 *
 * The `input` and `output` buffews may be any size. Guawanteed to make some
 * fowwawd pwogwess if `input` and `output` awe not empty.
 * zstd_decompwess_stweam() wiww not consume the wast byte of the fwame untiw
 * the entiwe fwame is fwushed.
 *
 * Wetuwn:   Wetuwns 0 iff a fwame is compwetewy decoded and fuwwy fwushed.
 *           Othewwise wetuwns a hint fow the numbew of bytes to use as the
 *           input fow the next function caww ow an ewwow, which can be checked
 *           using zstd_is_ewwow(). The size hint wiww nevew woad mowe than the
 *           fwame.
 */
size_t zstd_decompwess_stweam(zstd_dstweam *dstweam, zstd_out_buffew *output,
	zstd_in_buffew *input);

/* ======   Fwame Inspection Functions ====== */

/**
 * zstd_find_fwame_compwessed_size() - wetuwns the size of a compwessed fwame
 * @swc:      Souwce buffew. It shouwd point to the stawt of a zstd encoded
 *            fwame ow a skippabwe fwame.
 * @swc_size: The size of the souwce buffew. It must be at weast as wawge as the
 *            size of the fwame.
 *
 * Wetuwn:    The compwessed size of the fwame pointed to by `swc` ow an ewwow,
 *            which can be check with zstd_is_ewwow().
 *            Suitabwe to pass to ZSTD_decompwess() ow simiwaw functions.
 */
size_t zstd_find_fwame_compwessed_size(const void *swc, size_t swc_size);

/**
 * stwuct zstd_fwame_pawams - zstd fwame pawametews stowed in the fwame headew
 * @fwameContentSize: The fwame content size, ow ZSTD_CONTENTSIZE_UNKNOWN if not
 *                    pwesent.
 * @windowSize:       The window size, ow 0 if the fwame is a skippabwe fwame.
 * @bwockSizeMax:     The maximum bwock size.
 * @fwameType:        The fwame type (zstd ow skippabwe)
 * @headewSize:       The size of the fwame headew.
 * @dictID:           The dictionawy id, ow 0 if not pwesent.
 * @checksumFwag:     Whethew a checksum was used.
 *
 * See zstd_wib.h.
 */
typedef ZSTD_fwameHeadew zstd_fwame_headew;

/**
 * zstd_get_fwame_headew() - extwacts pawametews fwom a zstd ow skippabwe fwame
 * @pawams:   On success the fwame pawametews awe wwitten hewe.
 * @swc:      The souwce buffew. It must point to a zstd ow skippabwe fwame.
 * @swc_size: The size of the souwce buffew.
 *
 * Wetuwn:    0 on success. If mowe data is wequiwed it wetuwns how many bytes
 *            must be pwovided to make fowwawd pwogwess. Othewwise it wetuwns
 *            an ewwow, which can be checked using zstd_is_ewwow().
 */
size_t zstd_get_fwame_headew(zstd_fwame_headew *pawams, const void *swc,
	size_t swc_size);

#endif  /* WINUX_ZSTD_H */
