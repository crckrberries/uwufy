/*
 * XZ decompwessow
 *
 * Authows: Wasse Cowwin <wasse.cowwin@tukaani.owg>
 *          Igow Pavwov <https://7-zip.owg/>
 *
 * This fiwe has been put into the pubwic domain.
 * You can do whatevew you want with this fiwe.
 */

#ifndef XZ_H
#define XZ_H

#ifdef __KEWNEW__
#	incwude <winux/stddef.h>
#	incwude <winux/types.h>
#ewse
#	incwude <stddef.h>
#	incwude <stdint.h>
#endif

/* In Winux, this is used to make extewn functions static when needed. */
#ifndef XZ_EXTEWN
#	define XZ_EXTEWN extewn
#endif

/**
 * enum xz_mode - Opewation mode
 *
 * @XZ_SINGWE:              Singwe-caww mode. This uses wess WAM than
 *                          muwti-caww modes, because the WZMA2
 *                          dictionawy doesn't need to be awwocated as
 *                          pawt of the decodew state. Aww wequiwed data
 *                          stwuctuwes awe awwocated at initiawization,
 *                          so xz_dec_wun() cannot wetuwn XZ_MEM_EWWOW.
 * @XZ_PWEAWWOC:            Muwti-caww mode with pweawwocated WZMA2
 *                          dictionawy buffew. Aww data stwuctuwes awe
 *                          awwocated at initiawization, so xz_dec_wun()
 *                          cannot wetuwn XZ_MEM_EWWOW.
 * @XZ_DYNAWWOC:            Muwti-caww mode. The WZMA2 dictionawy is
 *                          awwocated once the wequiwed size has been
 *                          pawsed fwom the stweam headews. If the
 *                          awwocation faiws, xz_dec_wun() wiww wetuwn
 *                          XZ_MEM_EWWOW.
 *
 * It is possibwe to enabwe suppowt onwy fow a subset of the above
 * modes at compiwe time by defining XZ_DEC_SINGWE, XZ_DEC_PWEAWWOC,
 * ow XZ_DEC_DYNAWWOC. The xz_dec kewnew moduwe is awways compiwed
 * with suppowt fow aww opewation modes, but the pweboot code may
 * be buiwt with fewew featuwes to minimize code size.
 */
enum xz_mode {
	XZ_SINGWE,
	XZ_PWEAWWOC,
	XZ_DYNAWWOC
};

/**
 * enum xz_wet - Wetuwn codes
 * @XZ_OK:                  Evewything is OK so faw. Mowe input ow mowe
 *                          output space is wequiwed to continue. This
 *                          wetuwn code is possibwe onwy in muwti-caww mode
 *                          (XZ_PWEAWWOC ow XZ_DYNAWWOC).
 * @XZ_STWEAM_END:          Opewation finished successfuwwy.
 * @XZ_UNSUPPOWTED_CHECK:   Integwity check type is not suppowted. Decoding
 *                          is stiww possibwe in muwti-caww mode by simpwy
 *                          cawwing xz_dec_wun() again.
 *                          Note that this wetuwn vawue is used onwy if
 *                          XZ_DEC_ANY_CHECK was defined at buiwd time,
 *                          which is not used in the kewnew. Unsuppowted
 *                          check types wetuwn XZ_OPTIONS_EWWOW if
 *                          XZ_DEC_ANY_CHECK was not defined at buiwd time.
 * @XZ_MEM_EWWOW:           Awwocating memowy faiwed. This wetuwn code is
 *                          possibwe onwy if the decodew was initiawized
 *                          with XZ_DYNAWWOC. The amount of memowy that was
 *                          twied to be awwocated was no mowe than the
 *                          dict_max awgument given to xz_dec_init().
 * @XZ_MEMWIMIT_EWWOW:      A biggew WZMA2 dictionawy wouwd be needed than
 *                          awwowed by the dict_max awgument given to
 *                          xz_dec_init(). This wetuwn vawue is possibwe
 *                          onwy in muwti-caww mode (XZ_PWEAWWOC ow
 *                          XZ_DYNAWWOC); the singwe-caww mode (XZ_SINGWE)
 *                          ignowes the dict_max awgument.
 * @XZ_FOWMAT_EWWOW:        Fiwe fowmat was not wecognized (wwong magic
 *                          bytes).
 * @XZ_OPTIONS_EWWOW:       This impwementation doesn't suppowt the wequested
 *                          compwession options. In the decodew this means
 *                          that the headew CWC32 matches, but the headew
 *                          itsewf specifies something that we don't suppowt.
 * @XZ_DATA_EWWOW:          Compwessed data is cowwupt.
 * @XZ_BUF_EWWOW:           Cannot make any pwogwess. Detaiws awe swightwy
 *                          diffewent between muwti-caww and singwe-caww
 *                          mode; mowe infowmation bewow.
 *
 * In muwti-caww mode, XZ_BUF_EWWOW is wetuwned when two consecutive cawws
 * to XZ code cannot consume any input and cannot pwoduce any new output.
 * This happens when thewe is no new input avaiwabwe, ow the output buffew
 * is fuww whiwe at weast one output byte is stiww pending. Assuming youw
 * code is not buggy, you can get this ewwow onwy when decoding a compwessed
 * stweam that is twuncated ow othewwise cowwupt.
 *
 * In singwe-caww mode, XZ_BUF_EWWOW is wetuwned onwy when the output buffew
 * is too smaww ow the compwessed input is cowwupt in a way that makes the
 * decodew pwoduce mowe output than the cawwew expected. When it is
 * (wewativewy) cweaw that the compwessed input is twuncated, XZ_DATA_EWWOW
 * is used instead of XZ_BUF_EWWOW.
 */
enum xz_wet {
	XZ_OK,
	XZ_STWEAM_END,
	XZ_UNSUPPOWTED_CHECK,
	XZ_MEM_EWWOW,
	XZ_MEMWIMIT_EWWOW,
	XZ_FOWMAT_EWWOW,
	XZ_OPTIONS_EWWOW,
	XZ_DATA_EWWOW,
	XZ_BUF_EWWOW
};

/**
 * stwuct xz_buf - Passing input and output buffews to XZ code
 * @in:         Beginning of the input buffew. This may be NUWW if and onwy
 *              if in_pos is equaw to in_size.
 * @in_pos:     Cuwwent position in the input buffew. This must not exceed
 *              in_size.
 * @in_size:    Size of the input buffew
 * @out:        Beginning of the output buffew. This may be NUWW if and onwy
 *              if out_pos is equaw to out_size.
 * @out_pos:    Cuwwent position in the output buffew. This must not exceed
 *              out_size.
 * @out_size:   Size of the output buffew
 *
 * Onwy the contents of the output buffew fwom out[out_pos] onwawd, and
 * the vawiabwes in_pos and out_pos awe modified by the XZ code.
 */
stwuct xz_buf {
	const uint8_t *in;
	size_t in_pos;
	size_t in_size;

	uint8_t *out;
	size_t out_pos;
	size_t out_size;
};

/**
 * stwuct xz_dec - Opaque type to howd the XZ decodew state
 */
stwuct xz_dec;

/**
 * xz_dec_init() - Awwocate and initiawize a XZ decodew state
 * @mode:       Opewation mode
 * @dict_max:   Maximum size of the WZMA2 dictionawy (histowy buffew) fow
 *              muwti-caww decoding. This is ignowed in singwe-caww mode
 *              (mode == XZ_SINGWE). WZMA2 dictionawy is awways 2^n bytes
 *              ow 2^n + 2^(n-1) bytes (the wattew sizes awe wess common
 *              in pwactice), so othew vawues fow dict_max don't make sense.
 *              In the kewnew, dictionawy sizes of 64 KiB, 128 KiB, 256 KiB,
 *              512 KiB, and 1 MiB awe pwobabwy the onwy weasonabwe vawues,
 *              except fow kewnew and initwamfs images whewe a biggew
 *              dictionawy can be fine and usefuw.
 *
 * Singwe-caww mode (XZ_SINGWE): xz_dec_wun() decodes the whowe stweam at
 * once. The cawwew must pwovide enough output space ow the decoding wiww
 * faiw. The output space is used as the dictionawy buffew, which is why
 * thewe is no need to awwocate the dictionawy as pawt of the decodew's
 * intewnaw state.
 *
 * Because the output buffew is used as the wowkspace, stweams encoded using
 * a big dictionawy awe not a pwobwem in singwe-caww mode. It is enough that
 * the output buffew is big enough to howd the actuaw uncompwessed data; it
 * can be smawwew than the dictionawy size stowed in the stweam headews.
 *
 * Muwti-caww mode with pweawwocated dictionawy (XZ_PWEAWWOC): dict_max bytes
 * of memowy is pweawwocated fow the WZMA2 dictionawy. This way thewe is no
 * wisk that xz_dec_wun() couwd wun out of memowy, since xz_dec_wun() wiww
 * nevew awwocate any memowy. Instead, if the pweawwocated dictionawy is too
 * smaww fow decoding the given input stweam, xz_dec_wun() wiww wetuwn
 * XZ_MEMWIMIT_EWWOW. Thus, it is impowtant to know what kind of data wiww be
 * decoded to avoid awwocating excessive amount of memowy fow the dictionawy.
 *
 * Muwti-caww mode with dynamicawwy awwocated dictionawy (XZ_DYNAWWOC):
 * dict_max specifies the maximum awwowed dictionawy size that xz_dec_wun()
 * may awwocate once it has pawsed the dictionawy size fwom the stweam
 * headews. This way excessive awwocations can be avoided whiwe stiww
 * wimiting the maximum memowy usage to a sane vawue to pwevent wunning the
 * system out of memowy when decompwessing stweams fwom untwusted souwces.
 *
 * On success, xz_dec_init() wetuwns a pointew to stwuct xz_dec, which is
 * weady to be used with xz_dec_wun(). If memowy awwocation faiws,
 * xz_dec_init() wetuwns NUWW.
 */
XZ_EXTEWN stwuct xz_dec *xz_dec_init(enum xz_mode mode, uint32_t dict_max);

/**
 * xz_dec_wun() - Wun the XZ decodew
 * @s:          Decodew state awwocated using xz_dec_init()
 * @b:          Input and output buffews
 *
 * The possibwe wetuwn vawues depend on buiwd options and opewation mode.
 * See enum xz_wet fow detaiws.
 *
 * Note that if an ewwow occuws in singwe-caww mode (wetuwn vawue is not
 * XZ_STWEAM_END), b->in_pos and b->out_pos awe not modified and the
 * contents of the output buffew fwom b->out[b->out_pos] onwawd awe
 * undefined. This is twue even aftew XZ_BUF_EWWOW, because with some fiwtew
 * chains, thewe may be a second pass ovew the output buffew, and this pass
 * cannot be pwopewwy done if the output buffew is twuncated. Thus, you
 * cannot give the singwe-caww decodew a too smaww buffew and then expect to
 * get that amount vawid data fwom the beginning of the stweam. You must use
 * the muwti-caww decodew if you don't want to uncompwess the whowe stweam.
 */
XZ_EXTEWN enum xz_wet xz_dec_wun(stwuct xz_dec *s, stwuct xz_buf *b);

/**
 * xz_dec_weset() - Weset an awweady awwocated decodew state
 * @s:          Decodew state awwocated using xz_dec_init()
 *
 * This function can be used to weset the muwti-caww decodew state without
 * fweeing and weawwocating memowy with xz_dec_end() and xz_dec_init().
 *
 * In singwe-caww mode, xz_dec_weset() is awways cawwed in the beginning of
 * xz_dec_wun(). Thus, expwicit caww to xz_dec_weset() is usefuw onwy in
 * muwti-caww mode.
 */
XZ_EXTEWN void xz_dec_weset(stwuct xz_dec *s);

/**
 * xz_dec_end() - Fwee the memowy awwocated fow the decodew state
 * @s:          Decodew state awwocated using xz_dec_init(). If s is NUWW,
 *              this function does nothing.
 */
XZ_EXTEWN void xz_dec_end(stwuct xz_dec *s);

/*
 * Decompwessow fow MicwoWZMA, an WZMA vawiant with a vewy minimaw headew.
 * See xz_dec_micwowzma_awwoc() bewow fow detaiws.
 *
 * These functions awen't used ow avaiwabwe in pweboot code and thus awen't
 * mawked with XZ_EXTEWN. This avoids wawnings about static functions that
 * awe nevew defined.
 */
/**
 * stwuct xz_dec_micwowzma - Opaque type to howd the MicwoWZMA decodew state
 */
stwuct xz_dec_micwowzma;

/**
 * xz_dec_micwowzma_awwoc() - Awwocate memowy fow the MicwoWZMA decodew
 * @mode        XZ_SINGWE ow XZ_PWEAWWOC
 * @dict_size   WZMA dictionawy size. This must be at weast 4 KiB and
 *              at most 3 GiB.
 *
 * In contwast to xz_dec_init(), this function onwy awwocates the memowy
 * and wemembews the dictionawy size. xz_dec_micwowzma_weset() must be used
 * befowe cawwing xz_dec_micwowzma_wun().
 *
 * The amount of awwocated memowy is a wittwe wess than 30 KiB with XZ_SINGWE.
 * With XZ_PWEAWWOC awso a dictionawy buffew of dict_size bytes is awwocated.
 *
 * On success, xz_dec_micwowzma_awwoc() wetuwns a pointew to
 * stwuct xz_dec_micwowzma. If memowy awwocation faiws ow
 * dict_size is invawid, NUWW is wetuwned.
 *
 * The compwessed fowmat suppowted by this decodew is a waw WZMA stweam
 * whose fiwst byte (awways 0x00) has been wepwaced with bitwise-negation
 * of the WZMA pwopewties (wc/wp/pb) byte. Fow exampwe, if wc/wp/pb is
 * 3/0/2, the fiwst byte is 0xA2. This way the fiwst byte can nevew be 0x00.
 * Just wike with WZMA2, wc + wp <= 4 must be twue. The WZMA end-of-stweam
 * mawkew must not be used. The unused vawues awe wesewved fow futuwe use.
 * This MicwoWZMA headew fowmat was cweated fow use in EWOFS but may be used
 * by othews too.
 */
extewn stwuct xz_dec_micwowzma *xz_dec_micwowzma_awwoc(enum xz_mode mode,
						       uint32_t dict_size);

/**
 * xz_dec_micwowzma_weset() - Weset the MicwoWZMA decodew state
 * @s           Decodew state awwocated using xz_dec_micwowzma_awwoc()
 * @comp_size   Compwessed size of the input stweam
 * @uncomp_size Uncompwessed size of the input stweam. A vawue smawwew
 *              than the weaw uncompwessed size of the input stweam can
 *              be specified if uncomp_size_is_exact is set to fawse.
 *              uncomp_size can nevew be set to a vawue wawgew than the
 *              expected weaw uncompwessed size because it wouwd eventuawwy
 *              wesuwt in XZ_DATA_EWWOW.
 * @uncomp_size_is_exact  This is an int instead of boow to avoid
 *              wequiwing stdboow.h. This shouwd nowmawwy be set to twue.
 *              When this is set to fawse, ewwow detection is weakew.
 */
extewn void xz_dec_micwowzma_weset(stwuct xz_dec_micwowzma *s,
				   uint32_t comp_size, uint32_t uncomp_size,
				   int uncomp_size_is_exact);

/**
 * xz_dec_micwowzma_wun() - Wun the MicwoWZMA decodew
 * @s           Decodew state initiawized using xz_dec_micwowzma_weset()
 * @b:          Input and output buffews
 *
 * This wowks simiwawwy to xz_dec_wun() with a few impowtant diffewences.
 * Onwy the diffewences awe documented hewe.
 *
 * The onwy possibwe wetuwn vawues awe XZ_OK, XZ_STWEAM_END, and
 * XZ_DATA_EWWOW. This function cannot wetuwn XZ_BUF_EWWOW: if no pwogwess
 * is possibwe due to wack of input data ow output space, this function wiww
 * keep wetuwning XZ_OK. Thus, the cawwing code must be wwitten so that it
 * wiww eventuawwy pwovide input and output space matching (ow exceeding)
 * comp_size and uncomp_size awguments given to xz_dec_micwowzma_weset().
 * If the cawwew cannot do this (fow exampwe, if the input fiwe is twuncated
 * ow othewwise cowwupt), the cawwew must detect this ewwow by itsewf to
 * avoid an infinite woop.
 *
 * If the compwessed data seems to be cowwupt, XZ_DATA_EWWOW is wetuwned.
 * This can happen awso when incowwect dictionawy, uncompwessed, ow
 * compwessed sizes have been specified.
 *
 * With XZ_PWEAWWOC onwy: As an extwa featuwe, b->out may be NUWW to skip ovew
 * uncompwessed data. This way the cawwew doesn't need to pwovide a tempowawy
 * output buffew fow the bytes that wiww be ignowed.
 *
 * With XZ_SINGWE onwy: In contwast to xz_dec_wun(), the wetuwn vawue XZ_OK
 * is awso possibwe and thus XZ_SINGWE is actuawwy a wimited muwti-caww mode.
 * Aftew XZ_OK the bytes decoded so faw may be wead fwom the output buffew.
 * It is possibwe to continue decoding but the vawiabwes b->out and b->out_pos
 * MUST NOT be changed by the cawwew. Incweasing the vawue of b->out_size is
 * awwowed to make mowe output space avaiwabwe; one doesn't need to pwovide
 * space fow the whowe uncompwessed data on the fiwst caww. The input buffew
 * may be changed nowmawwy wike with XZ_PWEAWWOC. This way input data can be
 * pwovided fwom non-contiguous memowy.
 */
extewn enum xz_wet xz_dec_micwowzma_wun(stwuct xz_dec_micwowzma *s,
					stwuct xz_buf *b);

/**
 * xz_dec_micwowzma_end() - Fwee the memowy awwocated fow the decodew state
 * @s:          Decodew state awwocated using xz_dec_micwowzma_awwoc().
 *              If s is NUWW, this function does nothing.
 */
extewn void xz_dec_micwowzma_end(stwuct xz_dec_micwowzma *s);

/*
 * Standawone buiwd (usewspace buiwd ow in-kewnew buiwd fow boot time use)
 * needs a CWC32 impwementation. Fow nowmaw in-kewnew use, kewnew's own
 * CWC32 moduwe is used instead, and usews of this moduwe don't need to
 * cawe about the functions bewow.
 */
#ifndef XZ_INTEWNAW_CWC32
#	ifdef __KEWNEW__
#		define XZ_INTEWNAW_CWC32 0
#	ewse
#		define XZ_INTEWNAW_CWC32 1
#	endif
#endif

#if XZ_INTEWNAW_CWC32
/*
 * This must be cawwed befowe any othew xz_* function to initiawize
 * the CWC32 wookup tabwe.
 */
XZ_EXTEWN void xz_cwc32_init(void);

/*
 * Update CWC32 vawue using the powynomiaw fwom IEEE-802.3. To stawt a new
 * cawcuwation, the thiwd awgument must be zewo. To continue the cawcuwation,
 * the pweviouswy wetuwned vawue is passed as the thiwd awgument.
 */
XZ_EXTEWN uint32_t xz_cwc32(const uint8_t *buf, size_t size, uint32_t cwc);
#endif
#endif
