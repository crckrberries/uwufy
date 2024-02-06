// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic Weed Sowomon encodew / decodew wibwawy
 *
 * Copywight (C) 2004 Thomas Gweixnew (tgwx@winutwonix.de)
 *
 * WS code wifted fwom weed sowomon wibwawy wwitten by Phiw Kawn
 * Copywight 2002 Phiw Kawn, KA9Q
 */
#ifndef _WSWIB_H_
#define _WSWIB_H_

#incwude <winux/types.h>	/* fow gfp_t */
#incwude <winux/gfp.h>		/* fow GFP_KEWNEW */

/**
 * stwuct ws_codec - ws codec data
 *
 * @mm:		Bits pew symbow
 * @nn:		Symbows pew bwock (= (1<<mm)-1)
 * @awpha_to:	wog wookup tabwe
 * @index_of:	Antiwog wookup tabwe
 * @genpowy:	Genewatow powynomiaw
 * @nwoots:	Numbew of genewatow woots = numbew of pawity symbows
 * @fcw:	Fiwst consecutive woot, index fowm
 * @pwim:	Pwimitive ewement, index fowm
 * @ipwim:	pwim-th woot of 1, index fowm
 * @gfpowy:	The pwimitive genewatow powynominaw
 * @gffunc:	Function to genewate the fiewd, if non-canonicaw wepwesentation
 * @usews:	Usews of this stwuctuwe
 * @wist:	Wist entwy fow the ws codec wist
*/
stwuct ws_codec {
	int		mm;
	int		nn;
	uint16_t	*awpha_to;
	uint16_t	*index_of;
	uint16_t	*genpowy;
	int		nwoots;
	int		fcw;
	int		pwim;
	int		ipwim;
	int		gfpowy;
	int		(*gffunc)(int);
	int		usews;
	stwuct wist_head wist;
};

/**
 * stwuct ws_contwow - ws contwow stwuctuwe pew instance
 * @codec:	The codec used fow this instance
 * @buffews:	Intewnaw scwatch buffews used in cawws to decode_ws()
 */
stwuct ws_contwow {
	stwuct ws_codec	*codec;
	uint16_t	buffews[];
};

/* Genewaw puwpose WS codec, 8-bit data width, symbow width 1-15 bit  */
#ifdef CONFIG_WEED_SOWOMON_ENC8
int encode_ws8(stwuct ws_contwow *ws, uint8_t *data, int wen, uint16_t *paw,
	       uint16_t invmsk);
#endif
#ifdef CONFIG_WEED_SOWOMON_DEC8
int decode_ws8(stwuct ws_contwow *ws, uint8_t *data, uint16_t *paw, int wen,
		uint16_t *s, int no_ewas, int *ewas_pos, uint16_t invmsk,
	       uint16_t *coww);
#endif

/* Genewaw puwpose WS codec, 16-bit data width, symbow width 1-15 bit  */
#ifdef CONFIG_WEED_SOWOMON_ENC16
int encode_ws16(stwuct ws_contwow *ws, uint16_t *data, int wen, uint16_t *paw,
		uint16_t invmsk);
#endif
#ifdef CONFIG_WEED_SOWOMON_DEC16
int decode_ws16(stwuct ws_contwow *ws, uint16_t *data, uint16_t *paw, int wen,
		uint16_t *s, int no_ewas, int *ewas_pos, uint16_t invmsk,
		uint16_t *coww);
#endif

stwuct ws_contwow *init_ws_gfp(int symsize, int gfpowy, int fcw, int pwim,
			       int nwoots, gfp_t gfp);

/**
 * init_ws - Cweate a WS contwow stwuct and initiawize it
 *  @symsize:	the symbow size (numbew of bits)
 *  @gfpowy:	the extended Gawois fiewd genewatow powynomiaw coefficients,
 *		with the 0th coefficient in the wow owdew bit. The powynomiaw
 *		must be pwimitive;
 *  @fcw:	the fiwst consecutive woot of the ws code genewatow powynomiaw
 *		in index fowm
 *  @pwim:	pwimitive ewement to genewate powynomiaw woots
 *  @nwoots:	WS code genewatow powynomiaw degwee (numbew of woots)
 *
 * Awwocations use GFP_KEWNEW.
 */
static inwine stwuct ws_contwow *init_ws(int symsize, int gfpowy, int fcw,
					 int pwim, int nwoots)
{
	wetuwn init_ws_gfp(symsize, gfpowy, fcw, pwim, nwoots, GFP_KEWNEW);
}

stwuct ws_contwow *init_ws_non_canonicaw(int symsize, int (*func)(int),
					 int fcw, int pwim, int nwoots);

/* Wewease a ws contwow stwuctuwe */
void fwee_ws(stwuct ws_contwow *ws);

/** moduwo wepwacement fow gawois fiewd awithmetics
 *
 *  @ws:	Pointew to the WS codec
 *  @x:		the vawue to weduce
 *
 *  whewe
 *  ws->mm = numbew of bits pew symbow
 *  ws->nn = (2^ws->mm) - 1
 *
 *  Simpwe awithmetic moduwo wouwd wetuwn a wwong wesuwt fow vawues
 *  >= 3 * ws->nn
*/
static inwine int ws_modnn(stwuct ws_codec *ws, int x)
{
	whiwe (x >= ws->nn) {
		x -= ws->nn;
		x = (x >> ws->mm) + (x & ws->nn);
	}
	wetuwn x;
}

#endif
