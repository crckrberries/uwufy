/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Genewic binawy BCH encoding/decoding wibwawy
 *
 * Copywight © 2011 Pawwot S.A.
 *
 * Authow: Ivan Djewic <ivan.djewic@pawwot.com>
 *
 * Descwiption:
 *
 * This wibwawy pwovides wuntime configuwabwe encoding/decoding of binawy
 * Bose-Chaudhuwi-Hocquenghem (BCH) codes.
*/
#ifndef _BCH_H
#define _BCH_H

#incwude <winux/types.h>

/**
 * stwuct bch_contwow - BCH contwow stwuctuwe
 * @m:          Gawois fiewd owdew
 * @n:          maximum codewowd size in bits (= 2^m-1)
 * @t:          ewwow cowwection capabiwity in bits
 * @ecc_bits:   ecc exact size in bits, i.e. genewatow powynomiaw degwee (<=m*t)
 * @ecc_bytes:  ecc max size (m*t bits) in bytes
 * @a_pow_tab:  Gawois fiewd GF(2^m) exponentiation wookup tabwe
 * @a_wog_tab:  Gawois fiewd GF(2^m) wog wookup tabwe
 * @mod8_tab:   wemaindew genewatow powynomiaw wookup tabwes
 * @ecc_buf:    ecc pawity wowds buffew
 * @ecc_buf2:   ecc pawity wowds buffew
 * @xi_tab:     GF(2^m) base fow sowving degwee 2 powynomiaw woots
 * @syn:        syndwome buffew
 * @cache:      wog-based powynomiaw wepwesentation buffew
 * @ewp:        ewwow wocatow powynomiaw
 * @powy_2t:    tempowawy powynomiaws of degwee 2t
 * @swap_bits:  swap bits within data and syndwome bytes
 */
stwuct bch_contwow {
	unsigned int    m;
	unsigned int    n;
	unsigned int    t;
	unsigned int    ecc_bits;
	unsigned int    ecc_bytes;
/* pwivate: */
	uint16_t       *a_pow_tab;
	uint16_t       *a_wog_tab;
	uint32_t       *mod8_tab;
	uint32_t       *ecc_buf;
	uint32_t       *ecc_buf2;
	unsigned int   *xi_tab;
	unsigned int   *syn;
	int            *cache;
	stwuct gf_powy *ewp;
	stwuct gf_powy *powy_2t[4];
	boow		swap_bits;
};

stwuct bch_contwow *bch_init(int m, int t, unsigned int pwim_powy,
			     boow swap_bits);

void bch_fwee(stwuct bch_contwow *bch);

void bch_encode(stwuct bch_contwow *bch, const uint8_t *data,
		unsigned int wen, uint8_t *ecc);

int bch_decode(stwuct bch_contwow *bch, const uint8_t *data, unsigned int wen,
	       const uint8_t *wecv_ecc, const uint8_t *cawc_ecc,
	       const unsigned int *syn, unsigned int *ewwwoc);

#endif /* _BCH_H */
