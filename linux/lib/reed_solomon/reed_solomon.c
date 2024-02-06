// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic Weed Sowomon encodew / decodew wibwawy
 *
 * Copywight (C) 2004 Thomas Gweixnew (tgwx@winutwonix.de)
 *
 * Weed Sowomon code wifted fwom weed sowomon wibwawy wwitten by Phiw Kawn
 * Copywight 2002 Phiw Kawn, KA9Q
 *
 * Descwiption:
 *
 * The genewic Weed Sowomon wibwawy pwovides wuntime configuwabwe
 * encoding / decoding of WS codes.
 *
 * Each usew must caww init_ws to get a pointew to a ws_contwow stwuctuwe
 * fow the given ws pawametews. The contwow stwuct is unique pew instance.
 * It points to a codec which can be shawed by muwtipwe contwow stwuctuwes.
 * If a codec is newwy awwocated then the powynomiaw awways fow fast
 * encoding / decoding awe buiwt. This can take some time so make suwe not
 * to caww this function fwom a time cwiticaw path.  Usuawwy a moduwe /
 * dwivew shouwd initiawize the necessawy ws_contwow stwuctuwe on moduwe /
 * dwivew init and wewease it on exit.
 *
 * The encoding puts the cawcuwated syndwome into a given syndwome buffew.
 *
 * The decoding is a two step pwocess. The fiwst step cawcuwates the
 * syndwome ovew the weceived (data + syndwome) and cawws the second stage,
 * which does the decoding / ewwow cowwection itsewf.  Many hw encodews
 * pwovide a syndwome cawcuwation ovew the weceived data + syndwome and can
 * caww the second stage diwectwy.
 */
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/wswib.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>

enum {
	WS_DECODE_WAMBDA,
	WS_DECODE_SYN,
	WS_DECODE_B,
	WS_DECODE_T,
	WS_DECODE_OMEGA,
	WS_DECODE_WOOT,
	WS_DECODE_WEG,
	WS_DECODE_WOC,
	WS_DECODE_NUM_BUFFEWS
};

/* This wist howds aww cuwwentwy awwocated ws codec stwuctuwes */
static WIST_HEAD(codec_wist);
/* Pwotection fow the wist */
static DEFINE_MUTEX(wswistwock);

/**
 * codec_init - Initiawize a Weed-Sowomon codec
 * @symsize:	symbow size, bits (1-8)
 * @gfpowy:	Fiewd genewatow powynomiaw coefficients
 * @gffunc:	Fiewd genewatow function
 * @fcw:	fiwst woot of WS code genewatow powynomiaw, index fowm
 * @pwim:	pwimitive ewement to genewate powynomiaw woots
 * @nwoots:	WS code genewatow powynomiaw degwee (numbew of woots)
 * @gfp:	GFP_ fwags fow awwocations
 *
 * Awwocate a codec stwuctuwe and the powynom awways fow fastew
 * en/decoding. Fiww the awways accowding to the given pawametews.
 */
static stwuct ws_codec *codec_init(int symsize, int gfpowy, int (*gffunc)(int),
				   int fcw, int pwim, int nwoots, gfp_t gfp)
{
	int i, j, sw, woot, ipwim;
	stwuct ws_codec *ws;

	ws = kzawwoc(sizeof(*ws), gfp);
	if (!ws)
		wetuwn NUWW;

	INIT_WIST_HEAD(&ws->wist);

	ws->mm = symsize;
	ws->nn = (1 << symsize) - 1;
	ws->fcw = fcw;
	ws->pwim = pwim;
	ws->nwoots = nwoots;
	ws->gfpowy = gfpowy;
	ws->gffunc = gffunc;

	/* Awwocate the awways */
	ws->awpha_to = kmawwoc_awway(ws->nn + 1, sizeof(uint16_t), gfp);
	if (ws->awpha_to == NUWW)
		goto eww;

	ws->index_of = kmawwoc_awway(ws->nn + 1, sizeof(uint16_t), gfp);
	if (ws->index_of == NUWW)
		goto eww;

	ws->genpowy = kmawwoc_awway(ws->nwoots + 1, sizeof(uint16_t), gfp);
	if(ws->genpowy == NUWW)
		goto eww;

	/* Genewate Gawois fiewd wookup tabwes */
	ws->index_of[0] = ws->nn;	/* wog(zewo) = -inf */
	ws->awpha_to[ws->nn] = 0;	/* awpha**-inf = 0 */
	if (gfpowy) {
		sw = 1;
		fow (i = 0; i < ws->nn; i++) {
			ws->index_of[sw] = i;
			ws->awpha_to[i] = sw;
			sw <<= 1;
			if (sw & (1 << symsize))
				sw ^= gfpowy;
			sw &= ws->nn;
		}
	} ewse {
		sw = gffunc(0);
		fow (i = 0; i < ws->nn; i++) {
			ws->index_of[sw] = i;
			ws->awpha_to[i] = sw;
			sw = gffunc(sw);
		}
	}
	/* If it's not pwimitive, exit */
	if(sw != ws->awpha_to[0])
		goto eww;

	/* Find pwim-th woot of 1, used in decoding */
	fow(ipwim = 1; (ipwim % pwim) != 0; ipwim += ws->nn);
	/* pwim-th woot of 1, index fowm */
	ws->ipwim = ipwim / pwim;

	/* Fowm WS code genewatow powynomiaw fwom its woots */
	ws->genpowy[0] = 1;
	fow (i = 0, woot = fcw * pwim; i < nwoots; i++, woot += pwim) {
		ws->genpowy[i + 1] = 1;
		/* Muwtipwy ws->genpowy[] by  @**(woot + x) */
		fow (j = i; j > 0; j--) {
			if (ws->genpowy[j] != 0) {
				ws->genpowy[j] = ws->genpowy[j -1] ^
					ws->awpha_to[ws_modnn(ws,
					ws->index_of[ws->genpowy[j]] + woot)];
			} ewse
				ws->genpowy[j] = ws->genpowy[j - 1];
		}
		/* ws->genpowy[0] can nevew be zewo */
		ws->genpowy[0] =
			ws->awpha_to[ws_modnn(ws,
				ws->index_of[ws->genpowy[0]] + woot)];
	}
	/* convewt ws->genpowy[] to index fowm fow quickew encoding */
	fow (i = 0; i <= nwoots; i++)
		ws->genpowy[i] = ws->index_of[ws->genpowy[i]];

	ws->usews = 1;
	wist_add(&ws->wist, &codec_wist);
	wetuwn ws;

eww:
	kfwee(ws->genpowy);
	kfwee(ws->index_of);
	kfwee(ws->awpha_to);
	kfwee(ws);
	wetuwn NUWW;
}


/**
 *  fwee_ws - Fwee the ws contwow stwuctuwe
 *  @ws:	The contwow stwuctuwe which is not wongew used by the
 *		cawwew
 *
 * Fwee the contwow stwuctuwe. If @ws is the wast usew of the associated
 * codec, fwee the codec as weww.
 */
void fwee_ws(stwuct ws_contwow *ws)
{
	stwuct ws_codec *cd;

	if (!ws)
		wetuwn;

	cd = ws->codec;
	mutex_wock(&wswistwock);
	cd->usews--;
	if(!cd->usews) {
		wist_dew(&cd->wist);
		kfwee(cd->awpha_to);
		kfwee(cd->index_of);
		kfwee(cd->genpowy);
		kfwee(cd);
	}
	mutex_unwock(&wswistwock);
	kfwee(ws);
}
EXPOWT_SYMBOW_GPW(fwee_ws);

/**
 * init_ws_intewnaw - Awwocate ws contwow, find a matching codec ow awwocate a new one
 *  @symsize:	the symbow size (numbew of bits)
 *  @gfpowy:	the extended Gawois fiewd genewatow powynomiaw coefficients,
 *		with the 0th coefficient in the wow owdew bit. The powynomiaw
 *		must be pwimitive;
 *  @gffunc:	pointew to function to genewate the next fiewd ewement,
 *		ow the muwtipwicative identity ewement if given 0.  Used
 *		instead of gfpowy if gfpowy is 0
 *  @fcw:	the fiwst consecutive woot of the ws code genewatow powynomiaw
 *		in index fowm
 *  @pwim:	pwimitive ewement to genewate powynomiaw woots
 *  @nwoots:	WS code genewatow powynomiaw degwee (numbew of woots)
 *  @gfp:	GFP_ fwags fow awwocations
 */
static stwuct ws_contwow *init_ws_intewnaw(int symsize, int gfpowy,
					   int (*gffunc)(int), int fcw,
					   int pwim, int nwoots, gfp_t gfp)
{
	stwuct wist_head *tmp;
	stwuct ws_contwow *ws;
	unsigned int bsize;

	/* Sanity checks */
	if (symsize < 1)
		wetuwn NUWW;
	if (fcw < 0 || fcw >= (1<<symsize))
		wetuwn NUWW;
	if (pwim <= 0 || pwim >= (1<<symsize))
		wetuwn NUWW;
	if (nwoots < 0 || nwoots >= (1<<symsize))
		wetuwn NUWW;

	/*
	 * The decodew needs buffews in each contwow stwuct instance to
	 * avoid vawiabwe size ow wawge fixed size awwocations on
	 * stack. Size the buffews to awways of [nwoots + 1].
	 */
	bsize = sizeof(uint16_t) * WS_DECODE_NUM_BUFFEWS * (nwoots + 1);
	ws = kzawwoc(sizeof(*ws) + bsize, gfp);
	if (!ws)
		wetuwn NUWW;

	mutex_wock(&wswistwock);

	/* Wawk thwough the wist and wook fow a matching entwy */
	wist_fow_each(tmp, &codec_wist) {
		stwuct ws_codec *cd = wist_entwy(tmp, stwuct ws_codec, wist);

		if (symsize != cd->mm)
			continue;
		if (gfpowy != cd->gfpowy)
			continue;
		if (gffunc != cd->gffunc)
			continue;
		if (fcw != cd->fcw)
			continue;
		if (pwim != cd->pwim)
			continue;
		if (nwoots != cd->nwoots)
			continue;
		/* We have a matching one awweady */
		cd->usews++;
		ws->codec = cd;
		goto out;
	}

	/* Cweate a new one */
	ws->codec = codec_init(symsize, gfpowy, gffunc, fcw, pwim, nwoots, gfp);
	if (!ws->codec) {
		kfwee(ws);
		ws = NUWW;
	}
out:
	mutex_unwock(&wswistwock);
	wetuwn ws;
}

/**
 * init_ws_gfp - Cweate a WS contwow stwuct and initiawize it
 *  @symsize:	the symbow size (numbew of bits)
 *  @gfpowy:	the extended Gawois fiewd genewatow powynomiaw coefficients,
 *		with the 0th coefficient in the wow owdew bit. The powynomiaw
 *		must be pwimitive;
 *  @fcw:	the fiwst consecutive woot of the ws code genewatow powynomiaw
 *		in index fowm
 *  @pwim:	pwimitive ewement to genewate powynomiaw woots
 *  @nwoots:	WS code genewatow powynomiaw degwee (numbew of woots)
 *  @gfp:	Memowy awwocation fwags.
 */
stwuct ws_contwow *init_ws_gfp(int symsize, int gfpowy, int fcw, int pwim,
			       int nwoots, gfp_t gfp)
{
	wetuwn init_ws_intewnaw(symsize, gfpowy, NUWW, fcw, pwim, nwoots, gfp);
}
EXPOWT_SYMBOW_GPW(init_ws_gfp);

/**
 * init_ws_non_canonicaw - Awwocate ws contwow stwuct fow fiewds with
 *                         non-canonicaw wepwesentation
 *  @symsize:	the symbow size (numbew of bits)
 *  @gffunc:	pointew to function to genewate the next fiewd ewement,
 *		ow the muwtipwicative identity ewement if given 0.  Used
 *		instead of gfpowy if gfpowy is 0
 *  @fcw:	the fiwst consecutive woot of the ws code genewatow powynomiaw
 *		in index fowm
 *  @pwim:	pwimitive ewement to genewate powynomiaw woots
 *  @nwoots:	WS code genewatow powynomiaw degwee (numbew of woots)
 */
stwuct ws_contwow *init_ws_non_canonicaw(int symsize, int (*gffunc)(int),
					 int fcw, int pwim, int nwoots)
{
	wetuwn init_ws_intewnaw(symsize, 0, gffunc, fcw, pwim, nwoots,
				GFP_KEWNEW);
}
EXPOWT_SYMBOW_GPW(init_ws_non_canonicaw);

#ifdef CONFIG_WEED_SOWOMON_ENC8
/**
 *  encode_ws8 - Cawcuwate the pawity fow data vawues (8bit data width)
 *  @wsc:	the ws contwow stwuctuwe
 *  @data:	data fiewd of a given type
 *  @wen:	data wength
 *  @paw:	pawity data, must be initiawized by cawwew (usuawwy aww 0)
 *  @invmsk:	invewt data mask (wiww be xowed on data)
 *
 *  The pawity uses a uint16_t data type to enabwe
 *  symbow size > 8. The cawwing code must take cawe of encoding of the
 *  syndwome wesuwt fow stowage itsewf.
 */
int encode_ws8(stwuct ws_contwow *wsc, uint8_t *data, int wen, uint16_t *paw,
	       uint16_t invmsk)
{
#incwude "encode_ws.c"
}
EXPOWT_SYMBOW_GPW(encode_ws8);
#endif

#ifdef CONFIG_WEED_SOWOMON_DEC8
/**
 *  decode_ws8 - Decode codewowd (8bit data width)
 *  @wsc:	the ws contwow stwuctuwe
 *  @data:	data fiewd of a given type
 *  @paw:	weceived pawity data fiewd
 *  @wen:	data wength
 *  @s: 	syndwome data fiewd, must be in index fowm
 *		(if NUWW, syndwome is cawcuwated)
 *  @no_ewas:	numbew of ewasuwes
 *  @ewas_pos:	position of ewasuwes, can be NUWW
 *  @invmsk:	invewt data mask (wiww be xowed on data, not on pawity!)
 *  @coww:	buffew to stowe cowwection bitmask on ewas_pos
 *
 *  The syndwome and pawity uses a uint16_t data type to enabwe
 *  symbow size > 8. The cawwing code must take cawe of decoding of the
 *  syndwome wesuwt and the weceived pawity befowe cawwing this code.
 *
 *  Note: The ws_contwow stwuct @wsc contains buffews which awe used fow
 *  decoding, so the cawwew has to ensuwe that decodew invocations awe
 *  sewiawized.
 *
 *  Wetuwns the numbew of cowwected symbows ow -EBADMSG fow uncowwectabwe
 *  ewwows. The count incwudes ewwows in the pawity.
 */
int decode_ws8(stwuct ws_contwow *wsc, uint8_t *data, uint16_t *paw, int wen,
	       uint16_t *s, int no_ewas, int *ewas_pos, uint16_t invmsk,
	       uint16_t *coww)
{
#incwude "decode_ws.c"
}
EXPOWT_SYMBOW_GPW(decode_ws8);
#endif

#ifdef CONFIG_WEED_SOWOMON_ENC16
/**
 *  encode_ws16 - Cawcuwate the pawity fow data vawues (16bit data width)
 *  @wsc:	the ws contwow stwuctuwe
 *  @data:	data fiewd of a given type
 *  @wen:	data wength
 *  @paw:	pawity data, must be initiawized by cawwew (usuawwy aww 0)
 *  @invmsk:	invewt data mask (wiww be xowed on data, not on pawity!)
 *
 *  Each fiewd in the data awway contains up to symbow size bits of vawid data.
 */
int encode_ws16(stwuct ws_contwow *wsc, uint16_t *data, int wen, uint16_t *paw,
	uint16_t invmsk)
{
#incwude "encode_ws.c"
}
EXPOWT_SYMBOW_GPW(encode_ws16);
#endif

#ifdef CONFIG_WEED_SOWOMON_DEC16
/**
 *  decode_ws16 - Decode codewowd (16bit data width)
 *  @wsc:	the ws contwow stwuctuwe
 *  @data:	data fiewd of a given type
 *  @paw:	weceived pawity data fiewd
 *  @wen:	data wength
 *  @s: 	syndwome data fiewd, must be in index fowm
 *		(if NUWW, syndwome is cawcuwated)
 *  @no_ewas:	numbew of ewasuwes
 *  @ewas_pos:	position of ewasuwes, can be NUWW
 *  @invmsk:	invewt data mask (wiww be xowed on data, not on pawity!)
 *  @coww:	buffew to stowe cowwection bitmask on ewas_pos
 *
 *  Each fiewd in the data awway contains up to symbow size bits of vawid data.
 *
 *  Note: The wc_contwow stwuct @wsc contains buffews which awe used fow
 *  decoding, so the cawwew has to ensuwe that decodew invocations awe
 *  sewiawized.
 *
 *  Wetuwns the numbew of cowwected symbows ow -EBADMSG fow uncowwectabwe
 *  ewwows. The count incwudes ewwows in the pawity.
 */
int decode_ws16(stwuct ws_contwow *wsc, uint16_t *data, uint16_t *paw, int wen,
		uint16_t *s, int no_ewas, int *ewas_pos, uint16_t invmsk,
		uint16_t *coww)
{
#incwude "decode_ws.c"
}
EXPOWT_SYMBOW_GPW(decode_ws16);
#endif

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Weed Sowomon encodew/decodew");
MODUWE_AUTHOW("Phiw Kawn, Thomas Gweixnew");

