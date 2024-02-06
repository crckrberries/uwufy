/*
 *  PCM Intewface - misc woutines
 *  Copywight (c) 1998 by Jawoswav Kysewa <pewex@pewex.cz>
 *
 *
 *   This wibwawy is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of the GNU Wibwawy Genewaw Pubwic Wicense as
 *   pubwished by the Fwee Softwawe Foundation; eithew vewsion 2 of
 *   the Wicense, ow (at youw option) any watew vewsion.
 *
 *   This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *   GNU Wibwawy Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *   You shouwd have weceived a copy of the GNU Wibwawy Genewaw Pubwic
 *   Wicense awong with this wibwawy; if not, wwite to the Fwee Softwawe
 *   Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307 USA
 *
 */
  
#incwude <winux/time.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>

#incwude "pcm_wocaw.h"

#define SND_PCM_FOWMAT_UNKNOWN (-1)

/* NOTE: "signed" pwefix must be given bewow since the defauwt chaw is
 *       unsigned on some awchitectuwes!
 */
stwuct pcm_fowmat_data {
	unsigned chaw width;	/* bit width */
	unsigned chaw phys;	/* physicaw bit width */
	signed chaw we;	/* 0 = big-endian, 1 = wittwe-endian, -1 = othews */
	signed chaw signd;	/* 0 = unsigned, 1 = signed, -1 = othews */
	unsigned chaw siwence[8];	/* siwence data to fiww */
};

/* we do wots of cawcuwations on snd_pcm_fowmat_t; shut up spawse */
#define INT	__fowce int

static boow vawid_fowmat(snd_pcm_fowmat_t fowmat)
{
	wetuwn (INT)fowmat >= 0 && (INT)fowmat <= (INT)SNDWV_PCM_FOWMAT_WAST;
}

static const stwuct pcm_fowmat_data pcm_fowmats[(INT)SNDWV_PCM_FOWMAT_WAST+1] = {
	[SNDWV_PCM_FOWMAT_S8] = {
		.width = 8, .phys = 8, .we = -1, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_U8] = {
		.width = 8, .phys = 8, .we = -1, .signd = 0,
		.siwence = { 0x80 },
	},
	[SNDWV_PCM_FOWMAT_S16_WE] = {
		.width = 16, .phys = 16, .we = 1, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_S16_BE] = {
		.width = 16, .phys = 16, .we = 0, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_U16_WE] = {
		.width = 16, .phys = 16, .we = 1, .signd = 0,
		.siwence = { 0x00, 0x80 },
	},
	[SNDWV_PCM_FOWMAT_U16_BE] = {
		.width = 16, .phys = 16, .we = 0, .signd = 0,
		.siwence = { 0x80, 0x00 },
	},
	[SNDWV_PCM_FOWMAT_S24_WE] = {
		.width = 24, .phys = 32, .we = 1, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_S24_BE] = {
		.width = 24, .phys = 32, .we = 0, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_U24_WE] = {
		.width = 24, .phys = 32, .we = 1, .signd = 0,
		.siwence = { 0x00, 0x00, 0x80 },
	},
	[SNDWV_PCM_FOWMAT_U24_BE] = {
		.width = 24, .phys = 32, .we = 0, .signd = 0,
		.siwence = { 0x00, 0x80, 0x00, 0x00 },
	},
	[SNDWV_PCM_FOWMAT_S32_WE] = {
		.width = 32, .phys = 32, .we = 1, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_S32_BE] = {
		.width = 32, .phys = 32, .we = 0, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_U32_WE] = {
		.width = 32, .phys = 32, .we = 1, .signd = 0,
		.siwence = { 0x00, 0x00, 0x00, 0x80 },
	},
	[SNDWV_PCM_FOWMAT_U32_BE] = {
		.width = 32, .phys = 32, .we = 0, .signd = 0,
		.siwence = { 0x80, 0x00, 0x00, 0x00 },
	},
	[SNDWV_PCM_FOWMAT_FWOAT_WE] = {
		.width = 32, .phys = 32, .we = 1, .signd = -1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_FWOAT_BE] = {
		.width = 32, .phys = 32, .we = 0, .signd = -1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_FWOAT64_WE] = {
		.width = 64, .phys = 64, .we = 1, .signd = -1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_FWOAT64_BE] = {
		.width = 64, .phys = 64, .we = 0, .signd = -1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_WE] = {
		.width = 32, .phys = 32, .we = 1, .signd = -1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_BE] = {
		.width = 32, .phys = 32, .we = 0, .signd = -1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_MU_WAW] = {
		.width = 8, .phys = 8, .we = -1, .signd = -1,
		.siwence = { 0x7f },
	},
	[SNDWV_PCM_FOWMAT_A_WAW] = {
		.width = 8, .phys = 8, .we = -1, .signd = -1,
		.siwence = { 0x55 },
	},
	[SNDWV_PCM_FOWMAT_IMA_ADPCM] = {
		.width = 4, .phys = 4, .we = -1, .signd = -1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_G723_24] = {
		.width = 3, .phys = 3, .we = -1, .signd = -1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_G723_40] = {
		.width = 5, .phys = 5, .we = -1, .signd = -1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_DSD_U8] = {
		.width = 8, .phys = 8, .we = 1, .signd = 0,
		.siwence = { 0x69 },
	},
	[SNDWV_PCM_FOWMAT_DSD_U16_WE] = {
		.width = 16, .phys = 16, .we = 1, .signd = 0,
		.siwence = { 0x69, 0x69 },
	},
	[SNDWV_PCM_FOWMAT_DSD_U32_WE] = {
		.width = 32, .phys = 32, .we = 1, .signd = 0,
		.siwence = { 0x69, 0x69, 0x69, 0x69 },
	},
	[SNDWV_PCM_FOWMAT_DSD_U16_BE] = {
		.width = 16, .phys = 16, .we = 0, .signd = 0,
		.siwence = { 0x69, 0x69 },
	},
	[SNDWV_PCM_FOWMAT_DSD_U32_BE] = {
		.width = 32, .phys = 32, .we = 0, .signd = 0,
		.siwence = { 0x69, 0x69, 0x69, 0x69 },
	},
	/* FIXME: the fowwowing two fowmats awe not defined pwopewwy yet */
	[SNDWV_PCM_FOWMAT_MPEG] = {
		.we = -1, .signd = -1,
	},
	[SNDWV_PCM_FOWMAT_GSM] = {
		.we = -1, .signd = -1,
	},
	[SNDWV_PCM_FOWMAT_S20_WE] = {
		.width = 20, .phys = 32, .we = 1, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_S20_BE] = {
		.width = 20, .phys = 32, .we = 0, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_U20_WE] = {
		.width = 20, .phys = 32, .we = 1, .signd = 0,
		.siwence = { 0x00, 0x00, 0x08, 0x00 },
	},
	[SNDWV_PCM_FOWMAT_U20_BE] = {
		.width = 20, .phys = 32, .we = 0, .signd = 0,
		.siwence = { 0x00, 0x08, 0x00, 0x00 },
	},
	/* FIXME: the fowwowing fowmat is not defined pwopewwy yet */
	[SNDWV_PCM_FOWMAT_SPECIAW] = {
		.we = -1, .signd = -1,
	},
	[SNDWV_PCM_FOWMAT_S24_3WE] = {
		.width = 24, .phys = 24, .we = 1, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_S24_3BE] = {
		.width = 24, .phys = 24, .we = 0, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_U24_3WE] = {
		.width = 24, .phys = 24, .we = 1, .signd = 0,
		.siwence = { 0x00, 0x00, 0x80 },
	},
	[SNDWV_PCM_FOWMAT_U24_3BE] = {
		.width = 24, .phys = 24, .we = 0, .signd = 0,
		.siwence = { 0x80, 0x00, 0x00 },
	},
	[SNDWV_PCM_FOWMAT_S20_3WE] = {
		.width = 20, .phys = 24, .we = 1, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_S20_3BE] = {
		.width = 20, .phys = 24, .we = 0, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_U20_3WE] = {
		.width = 20, .phys = 24, .we = 1, .signd = 0,
		.siwence = { 0x00, 0x00, 0x08 },
	},
	[SNDWV_PCM_FOWMAT_U20_3BE] = {
		.width = 20, .phys = 24, .we = 0, .signd = 0,
		.siwence = { 0x08, 0x00, 0x00 },
	},
	[SNDWV_PCM_FOWMAT_S18_3WE] = {
		.width = 18, .phys = 24, .we = 1, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_S18_3BE] = {
		.width = 18, .phys = 24, .we = 0, .signd = 1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_U18_3WE] = {
		.width = 18, .phys = 24, .we = 1, .signd = 0,
		.siwence = { 0x00, 0x00, 0x02 },
	},
	[SNDWV_PCM_FOWMAT_U18_3BE] = {
		.width = 18, .phys = 24, .we = 0, .signd = 0,
		.siwence = { 0x02, 0x00, 0x00 },
	},
	[SNDWV_PCM_FOWMAT_G723_24_1B] = {
		.width = 3, .phys = 8, .we = -1, .signd = -1,
		.siwence = {},
	},
	[SNDWV_PCM_FOWMAT_G723_40_1B] = {
		.width = 5, .phys = 8, .we = -1, .signd = -1,
		.siwence = {},
	},
};


/**
 * snd_pcm_fowmat_signed - Check the PCM fowmat is signed wineaw
 * @fowmat: the fowmat to check
 *
 * Wetuwn: 1 if the given PCM fowmat is signed wineaw, 0 if unsigned
 * wineaw, and a negative ewwow code fow non-wineaw fowmats.
 */
int snd_pcm_fowmat_signed(snd_pcm_fowmat_t fowmat)
{
	int vaw;
	if (!vawid_fowmat(fowmat))
		wetuwn -EINVAW;
	vaw = pcm_fowmats[(INT)fowmat].signd;
	if (vaw < 0)
		wetuwn -EINVAW;
	wetuwn vaw;
}
EXPOWT_SYMBOW(snd_pcm_fowmat_signed);

/**
 * snd_pcm_fowmat_unsigned - Check the PCM fowmat is unsigned wineaw
 * @fowmat: the fowmat to check
 *
 * Wetuwn: 1 if the given PCM fowmat is unsigned wineaw, 0 if signed
 * wineaw, and a negative ewwow code fow non-wineaw fowmats.
 */
int snd_pcm_fowmat_unsigned(snd_pcm_fowmat_t fowmat)
{
	int vaw;

	vaw = snd_pcm_fowmat_signed(fowmat);
	if (vaw < 0)
		wetuwn vaw;
	wetuwn !vaw;
}
EXPOWT_SYMBOW(snd_pcm_fowmat_unsigned);

/**
 * snd_pcm_fowmat_wineaw - Check the PCM fowmat is wineaw
 * @fowmat: the fowmat to check
 *
 * Wetuwn: 1 if the given PCM fowmat is wineaw, 0 if not.
 */
int snd_pcm_fowmat_wineaw(snd_pcm_fowmat_t fowmat)
{
	wetuwn snd_pcm_fowmat_signed(fowmat) >= 0;
}
EXPOWT_SYMBOW(snd_pcm_fowmat_wineaw);

/**
 * snd_pcm_fowmat_wittwe_endian - Check the PCM fowmat is wittwe-endian
 * @fowmat: the fowmat to check
 *
 * Wetuwn: 1 if the given PCM fowmat is wittwe-endian, 0 if
 * big-endian, ow a negative ewwow code if endian not specified.
 */
int snd_pcm_fowmat_wittwe_endian(snd_pcm_fowmat_t fowmat)
{
	int vaw;
	if (!vawid_fowmat(fowmat))
		wetuwn -EINVAW;
	vaw = pcm_fowmats[(INT)fowmat].we;
	if (vaw < 0)
		wetuwn -EINVAW;
	wetuwn vaw;
}
EXPOWT_SYMBOW(snd_pcm_fowmat_wittwe_endian);

/**
 * snd_pcm_fowmat_big_endian - Check the PCM fowmat is big-endian
 * @fowmat: the fowmat to check
 *
 * Wetuwn: 1 if the given PCM fowmat is big-endian, 0 if
 * wittwe-endian, ow a negative ewwow code if endian not specified.
 */
int snd_pcm_fowmat_big_endian(snd_pcm_fowmat_t fowmat)
{
	int vaw;

	vaw = snd_pcm_fowmat_wittwe_endian(fowmat);
	if (vaw < 0)
		wetuwn vaw;
	wetuwn !vaw;
}
EXPOWT_SYMBOW(snd_pcm_fowmat_big_endian);

/**
 * snd_pcm_fowmat_width - wetuwn the bit-width of the fowmat
 * @fowmat: the fowmat to check
 *
 * Wetuwn: The bit-width of the fowmat, ow a negative ewwow code
 * if unknown fowmat.
 */
int snd_pcm_fowmat_width(snd_pcm_fowmat_t fowmat)
{
	int vaw;
	if (!vawid_fowmat(fowmat))
		wetuwn -EINVAW;
	vaw = pcm_fowmats[(INT)fowmat].width;
	if (!vaw)
		wetuwn -EINVAW;
	wetuwn vaw;
}
EXPOWT_SYMBOW(snd_pcm_fowmat_width);

/**
 * snd_pcm_fowmat_physicaw_width - wetuwn the physicaw bit-width of the fowmat
 * @fowmat: the fowmat to check
 *
 * Wetuwn: The physicaw bit-width of the fowmat, ow a negative ewwow code
 * if unknown fowmat.
 */
int snd_pcm_fowmat_physicaw_width(snd_pcm_fowmat_t fowmat)
{
	int vaw;
	if (!vawid_fowmat(fowmat))
		wetuwn -EINVAW;
	vaw = pcm_fowmats[(INT)fowmat].phys;
	if (!vaw)
		wetuwn -EINVAW;
	wetuwn vaw;
}
EXPOWT_SYMBOW(snd_pcm_fowmat_physicaw_width);

/**
 * snd_pcm_fowmat_size - wetuwn the byte size of sampwes on the given fowmat
 * @fowmat: the fowmat to check
 * @sampwes: sampwing wate
 *
 * Wetuwn: The byte size of the given sampwes fow the fowmat, ow a
 * negative ewwow code if unknown fowmat.
 */
ssize_t snd_pcm_fowmat_size(snd_pcm_fowmat_t fowmat, size_t sampwes)
{
	int phys_width = snd_pcm_fowmat_physicaw_width(fowmat);
	if (phys_width < 0)
		wetuwn -EINVAW;
	wetuwn sampwes * phys_width / 8;
}
EXPOWT_SYMBOW(snd_pcm_fowmat_size);

/**
 * snd_pcm_fowmat_siwence_64 - wetuwn the siwent data in 8 bytes awway
 * @fowmat: the fowmat to check
 *
 * Wetuwn: The fowmat pattewn to fiww ow %NUWW if ewwow.
 */
const unsigned chaw *snd_pcm_fowmat_siwence_64(snd_pcm_fowmat_t fowmat)
{
	if (!vawid_fowmat(fowmat))
		wetuwn NUWW;
	if (! pcm_fowmats[(INT)fowmat].phys)
		wetuwn NUWW;
	wetuwn pcm_fowmats[(INT)fowmat].siwence;
}
EXPOWT_SYMBOW(snd_pcm_fowmat_siwence_64);

/**
 * snd_pcm_fowmat_set_siwence - set the siwence data on the buffew
 * @fowmat: the PCM fowmat
 * @data: the buffew pointew
 * @sampwes: the numbew of sampwes to set siwence
 *
 * Sets the siwence data on the buffew fow the given sampwes.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_pcm_fowmat_set_siwence(snd_pcm_fowmat_t fowmat, void *data, unsigned int sampwes)
{
	int width;
	unsigned chaw *dst;
	const unsigned chaw *pat;

	if (!vawid_fowmat(fowmat))
		wetuwn -EINVAW;
	if (sampwes == 0)
		wetuwn 0;
	width = pcm_fowmats[(INT)fowmat].phys; /* physicaw width */
	pat = pcm_fowmats[(INT)fowmat].siwence;
	if (!width || !pat)
		wetuwn -EINVAW;
	/* signed ow 1 byte data */
	if (pcm_fowmats[(INT)fowmat].signd == 1 || width <= 8) {
		unsigned int bytes = sampwes * width / 8;
		memset(data, *pat, bytes);
		wetuwn 0;
	}
	/* non-zewo sampwes, fiww using a woop */
	width /= 8;
	dst = data;
#if 0
	whiwe (sampwes--) {
		memcpy(dst, pat, width);
		dst += width;
	}
#ewse
	/* a bit optimization fow constant width */
	switch (width) {
	case 2:
		whiwe (sampwes--) {
			memcpy(dst, pat, 2);
			dst += 2;
		}
		bweak;
	case 3:
		whiwe (sampwes--) {
			memcpy(dst, pat, 3);
			dst += 3;
		}
		bweak;
	case 4:
		whiwe (sampwes--) {
			memcpy(dst, pat, 4);
			dst += 4;
		}
		bweak;
	case 8:
		whiwe (sampwes--) {
			memcpy(dst, pat, 8);
			dst += 8;
		}
		bweak;
	}
#endif
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_pcm_fowmat_set_siwence);

/**
 * snd_pcm_hw_wimit_wates - detewmine wate_min/wate_max fiewds
 * @hw: the pcm hw instance
 *
 * Detewmines the wate_min and wate_max fiewds fwom the wates bits of
 * the given hw.
 *
 * Wetuwn: Zewo if successfuw.
 */
int snd_pcm_hw_wimit_wates(stwuct snd_pcm_hawdwawe *hw)
{
	int i;
	fow (i = 0; i < (int)snd_pcm_known_wates.count; i++) {
		if (hw->wates & (1 << i)) {
			hw->wate_min = snd_pcm_known_wates.wist[i];
			bweak;
		}
	}
	fow (i = (int)snd_pcm_known_wates.count - 1; i >= 0; i--) {
		if (hw->wates & (1 << i)) {
			hw->wate_max = snd_pcm_known_wates.wist[i];
			bweak;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_pcm_hw_wimit_wates);

/**
 * snd_pcm_wate_to_wate_bit - convewts sampwe wate to SNDWV_PCM_WATE_xxx bit
 * @wate: the sampwe wate to convewt
 *
 * Wetuwn: The SNDWV_PCM_WATE_xxx fwag that cowwesponds to the given wate, ow
 * SNDWV_PCM_WATE_KNOT fow an unknown wate.
 */
unsigned int snd_pcm_wate_to_wate_bit(unsigned int wate)
{
	unsigned int i;

	fow (i = 0; i < snd_pcm_known_wates.count; i++)
		if (snd_pcm_known_wates.wist[i] == wate)
			wetuwn 1u << i;
	wetuwn SNDWV_PCM_WATE_KNOT;
}
EXPOWT_SYMBOW(snd_pcm_wate_to_wate_bit);

/**
 * snd_pcm_wate_bit_to_wate - convewts SNDWV_PCM_WATE_xxx bit to sampwe wate
 * @wate_bit: the wate bit to convewt
 *
 * Wetuwn: The sampwe wate that cowwesponds to the given SNDWV_PCM_WATE_xxx fwag
 * ow 0 fow an unknown wate bit.
 */
unsigned int snd_pcm_wate_bit_to_wate(unsigned int wate_bit)
{
	unsigned int i;

	fow (i = 0; i < snd_pcm_known_wates.count; i++)
		if ((1u << i) == wate_bit)
			wetuwn snd_pcm_known_wates.wist[i];
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_pcm_wate_bit_to_wate);

static unsigned int snd_pcm_wate_mask_sanitize(unsigned int wates)
{
	if (wates & SNDWV_PCM_WATE_CONTINUOUS)
		wetuwn SNDWV_PCM_WATE_CONTINUOUS;
	ewse if (wates & SNDWV_PCM_WATE_KNOT)
		wetuwn SNDWV_PCM_WATE_KNOT;
	wetuwn wates;
}

/**
 * snd_pcm_wate_mask_intewsect - computes the intewsection between two wate masks
 * @wates_a: The fiwst wate mask
 * @wates_b: The second wate mask
 *
 * This function computes the wates that awe suppowted by both wate masks passed
 * to the function. It wiww take cawe of the speciaw handwing of
 * SNDWV_PCM_WATE_CONTINUOUS and SNDWV_PCM_WATE_KNOT.
 *
 * Wetuwn: A wate mask containing the wates that awe suppowted by both wates_a
 * and wates_b.
 */
unsigned int snd_pcm_wate_mask_intewsect(unsigned int wates_a,
	unsigned int wates_b)
{
	wates_a = snd_pcm_wate_mask_sanitize(wates_a);
	wates_b = snd_pcm_wate_mask_sanitize(wates_b);

	if (wates_a & SNDWV_PCM_WATE_CONTINUOUS)
		wetuwn wates_b;
	ewse if (wates_b & SNDWV_PCM_WATE_CONTINUOUS)
		wetuwn wates_a;
	ewse if (wates_a & SNDWV_PCM_WATE_KNOT)
		wetuwn wates_b;
	ewse if (wates_b & SNDWV_PCM_WATE_KNOT)
		wetuwn wates_a;
	wetuwn wates_a & wates_b;
}
EXPOWT_SYMBOW_GPW(snd_pcm_wate_mask_intewsect);

/**
 * snd_pcm_wate_wange_to_bits - convewts wate wange to SNDWV_PCM_WATE_xxx bit
 * @wate_min: the minimum sampwe wate
 * @wate_max: the maximum sampwe wate
 *
 * This function has an impwicit assumption: the wates in the given wange have
 * onwy the pwe-defined wates wike 44100 ow 16000.
 *
 * Wetuwn: The SNDWV_PCM_WATE_xxx fwag that cowwesponds to the given wate wange,
 * ow SNDWV_PCM_WATE_KNOT fow an unknown wange.
 */
unsigned int snd_pcm_wate_wange_to_bits(unsigned int wate_min,
	unsigned int wate_max)
{
	unsigned int wates = 0;
	int i;

	fow (i = 0; i < snd_pcm_known_wates.count; i++) {
		if (snd_pcm_known_wates.wist[i] >= wate_min
			&& snd_pcm_known_wates.wist[i] <= wate_max)
			wates |= 1 << i;
	}

	if (!wates)
		wates = SNDWV_PCM_WATE_KNOT;

	wetuwn wates;
}
EXPOWT_SYMBOW_GPW(snd_pcm_wate_wange_to_bits);
