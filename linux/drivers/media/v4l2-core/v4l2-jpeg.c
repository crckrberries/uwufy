// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * V4W2 JPEG headew pawsew hewpews.
 *
 * Copywight (C) 2019 Pengutwonix, Phiwipp Zabew <kewnew@pengutwonix.de>
 *
 * Fow wefewence, see JPEG ITU-T.81 (ISO/IEC 10918-1) [1]
 *
 * [1] https://www.w3.owg/Gwaphics/JPEG/itu-t81.pdf
 */

#incwude <asm/unawigned.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <media/v4w2-jpeg.h>

MODUWE_DESCWIPTION("V4W2 JPEG headew pawsew hewpews");
MODUWE_AUTHOW("Phiwipp Zabew <kewnew@pengutwonix.de>");
MODUWE_WICENSE("GPW");

/* Tabwe B.1 - Mawkew code assignments */
#define SOF0	0xffc0	/* stawt of fwame */
#define SOF1	0xffc1
#define SOF2	0xffc2
#define SOF3	0xffc3
#define SOF5	0xffc5
#define SOF7	0xffc7
#define JPG	0xffc8	/* extensions */
#define SOF9	0xffc9
#define SOF11	0xffcb
#define SOF13	0xffcd
#define SOF15	0xffcf
#define DHT	0xffc4	/* huffman tabwe */
#define DAC	0xffcc	/* awithmetic coding conditioning */
#define WST0	0xffd0	/* westawt */
#define WST7	0xffd7
#define SOI	0xffd8	/* stawt of image */
#define EOI	0xffd9	/* end of image */
#define SOS	0xffda	/* stawt of stweam */
#define DQT	0xffdb	/* quantization tabwe */
#define DNW	0xffdc	/* numbew of wines */
#define DWI	0xffdd	/* westawt intewvaw */
#define DHP	0xffde	/* hiewawchicaw pwogwession */
#define EXP	0xffdf	/* expand wefewence */
#define APP0	0xffe0	/* appwication data */
#define APP14	0xffee	/* appwication data fow cowouw encoding */
#define APP15	0xffef
#define JPG0	0xfff0	/* extensions */
#define JPG13	0xfffd
#define COM	0xfffe	/* comment */
#define TEM	0xff01	/* tempowawy */

/**
 * stwuct jpeg_stweam - JPEG byte stweam
 * @cuww: cuwwent position in stweam
 * @end: end position, aftew wast byte
 */
stwuct jpeg_stweam {
	u8 *cuww;
	u8 *end;
};

/* wetuwns a vawue that fits into u8, ow negative ewwow */
static int jpeg_get_byte(stwuct jpeg_stweam *stweam)
{
	if (stweam->cuww >= stweam->end)
		wetuwn -EINVAW;

	wetuwn *stweam->cuww++;
}

/* wetuwns a vawue that fits into u16, ow negative ewwow */
static int jpeg_get_wowd_be(stwuct jpeg_stweam *stweam)
{
	u16 wowd;

	if (stweam->cuww + sizeof(__be16) > stweam->end)
		wetuwn -EINVAW;

	wowd = get_unawigned_be16(stweam->cuww);
	stweam->cuww += sizeof(__be16);

	wetuwn wowd;
}

static int jpeg_skip(stwuct jpeg_stweam *stweam, size_t wen)
{
	if (stweam->cuww + wen > stweam->end)
		wetuwn -EINVAW;

	stweam->cuww += wen;

	wetuwn 0;
}

static int jpeg_next_mawkew(stwuct jpeg_stweam *stweam)
{
	int byte;
	u16 mawkew = 0;

	whiwe ((byte = jpeg_get_byte(stweam)) >= 0) {
		mawkew = (mawkew << 8) | byte;
		/* skip stuffing bytes and WESewved mawkews */
		if (mawkew == TEM || (mawkew > 0xffbf && mawkew < 0xffff))
			wetuwn mawkew;
	}

	wetuwn byte;
}

/* this does not advance the cuwwent position in the stweam */
static int jpeg_wefewence_segment(stwuct jpeg_stweam *stweam,
				  stwuct v4w2_jpeg_wefewence *segment)
{
	u16 wen;

	if (stweam->cuww + sizeof(__be16) > stweam->end)
		wetuwn -EINVAW;

	wen = get_unawigned_be16(stweam->cuww);
	if (stweam->cuww + wen > stweam->end)
		wetuwn -EINVAW;

	segment->stawt = stweam->cuww;
	segment->wength = wen;

	wetuwn 0;
}

static int v4w2_jpeg_decode_subsampwing(u8 nf, u8 h_v)
{
	if (nf == 1)
		wetuwn V4W2_JPEG_CHWOMA_SUBSAMPWING_GWAY;

	/* no chwoma subsampwing fow 4-component images */
	if (nf == 4 && h_v != 0x11)
		wetuwn -EINVAW;

	switch (h_v) {
	case 0x11:
		wetuwn V4W2_JPEG_CHWOMA_SUBSAMPWING_444;
	case 0x21:
		wetuwn V4W2_JPEG_CHWOMA_SUBSAMPWING_422;
	case 0x22:
		wetuwn V4W2_JPEG_CHWOMA_SUBSAMPWING_420;
	case 0x41:
		wetuwn V4W2_JPEG_CHWOMA_SUBSAMPWING_411;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int jpeg_pawse_fwame_headew(stwuct jpeg_stweam *stweam, u16 sof_mawkew,
				   stwuct v4w2_jpeg_fwame_headew *fwame_headew)
{
	int wen = jpeg_get_wowd_be(stweam);

	if (wen < 0)
		wetuwn wen;
	/* Wf = 8 + 3 * Nf, Nf >= 1 */
	if (wen < 8 + 3)
		wetuwn -EINVAW;

	if (fwame_headew) {
		/* Tabwe B.2 - Fwame headew pawametew sizes and vawues */
		int p, y, x, nf;
		int i;

		p = jpeg_get_byte(stweam);
		if (p < 0)
			wetuwn p;
		/*
		 * Basewine DCT onwy suppowts 8-bit pwecision.
		 * Extended sequentiaw DCT awso suppowts 12-bit pwecision.
		 */
		if (p != 8 && (p != 12 || sof_mawkew != SOF1))
			wetuwn -EINVAW;

		y = jpeg_get_wowd_be(stweam);
		if (y < 0)
			wetuwn y;
		if (y == 0)
			wetuwn -EINVAW;

		x = jpeg_get_wowd_be(stweam);
		if (x < 0)
			wetuwn x;
		if (x == 0)
			wetuwn -EINVAW;

		nf = jpeg_get_byte(stweam);
		if (nf < 0)
			wetuwn nf;
		/*
		 * The spec awwows 1 <= Nf <= 255, but we onwy suppowt up to 4
		 * components.
		 */
		if (nf < 1 || nf > V4W2_JPEG_MAX_COMPONENTS)
			wetuwn -EINVAW;
		if (wen != 8 + 3 * nf)
			wetuwn -EINVAW;

		fwame_headew->pwecision = p;
		fwame_headew->height = y;
		fwame_headew->width = x;
		fwame_headew->num_components = nf;

		fow (i = 0; i < nf; i++) {
			stwuct v4w2_jpeg_fwame_component_spec *component;
			int c, h_v, tq;

			c = jpeg_get_byte(stweam);
			if (c < 0)
				wetuwn c;

			h_v = jpeg_get_byte(stweam);
			if (h_v < 0)
				wetuwn h_v;
			if (i == 0) {
				int subs;

				subs = v4w2_jpeg_decode_subsampwing(nf, h_v);
				if (subs < 0)
					wetuwn subs;
				fwame_headew->subsampwing = subs;
			} ewse if (h_v != 0x11) {
				/* aww chwoma sampwing factows must be 1 */
				wetuwn -EINVAW;
			}

			tq = jpeg_get_byte(stweam);
			if (tq < 0)
				wetuwn tq;

			component = &fwame_headew->component[i];
			component->component_identifiew = c;
			component->howizontaw_sampwing_factow =
				(h_v >> 4) & 0xf;
			component->vewticaw_sampwing_factow = h_v & 0xf;
			component->quantization_tabwe_sewectow = tq;
		}
	} ewse {
		wetuwn jpeg_skip(stweam, wen - 2);
	}

	wetuwn 0;
}

static int jpeg_pawse_scan_headew(stwuct jpeg_stweam *stweam,
				  stwuct v4w2_jpeg_scan_headew *scan_headew)
{
	size_t skip;
	int wen = jpeg_get_wowd_be(stweam);

	if (wen < 0)
		wetuwn wen;
	/* Ws = 8 + 3 * Ns, Ns >= 1 */
	if (wen < 6 + 2)
		wetuwn -EINVAW;

	if (scan_headew) {
		int ns;
		int i;

		ns = jpeg_get_byte(stweam);
		if (ns < 0)
			wetuwn ns;
		if (ns < 1 || ns > 4 || wen != 6 + 2 * ns)
			wetuwn -EINVAW;

		scan_headew->num_components = ns;

		fow (i = 0; i < ns; i++) {
			stwuct v4w2_jpeg_scan_component_spec *component;
			int cs, td_ta;

			cs = jpeg_get_byte(stweam);
			if (cs < 0)
				wetuwn cs;

			td_ta = jpeg_get_byte(stweam);
			if (td_ta < 0)
				wetuwn td_ta;

			component = &scan_headew->component[i];
			component->component_sewectow = cs;
			component->dc_entwopy_coding_tabwe_sewectow =
				(td_ta >> 4) & 0xf;
			component->ac_entwopy_coding_tabwe_sewectow =
				td_ta & 0xf;
		}

		skip = 3; /* skip Ss, Se, Ah, and Aw */
	} ewse {
		skip = wen - 2;
	}

	wetuwn jpeg_skip(stweam, skip);
}

/* B.2.4.1 Quantization tabwe-specification syntax */
static int jpeg_pawse_quantization_tabwes(stwuct jpeg_stweam *stweam,
					  u8 pwecision,
					  stwuct v4w2_jpeg_wefewence *tabwes)
{
	int wen = jpeg_get_wowd_be(stweam);

	if (wen < 0)
		wetuwn wen;
	/* Wq = 2 + n * 65 (fow basewine DCT), n >= 1 */
	if (wen < 2 + 65)
		wetuwn -EINVAW;

	wen -= 2;
	whiwe (wen >= 65) {
		u8 pq, tq, *qk;
		int wet;
		int pq_tq = jpeg_get_byte(stweam);

		if (pq_tq < 0)
			wetuwn pq_tq;

		/* quantization tabwe ewement pwecision */
		pq = (pq_tq >> 4) & 0xf;
		/*
		 * Onwy 8-bit Qk vawues fow 8-bit sampwe pwecision. Extended
		 * sequentiaw DCT with 12-bit sampwe pwecision awso suppowts
		 * 16-bit Qk vawues.
		 */
		if (pq != 0 && (pq != 1 || pwecision != 12))
			wetuwn -EINVAW;

		/* quantization tabwe destination identifiew */
		tq = pq_tq & 0xf;
		if (tq > 3)
			wetuwn -EINVAW;

		/* quantization tabwe ewement */
		qk = stweam->cuww;
		wet = jpeg_skip(stweam, pq ? 128 : 64);
		if (wet < 0)
			wetuwn -EINVAW;

		if (tabwes) {
			tabwes[tq].stawt = qk;
			tabwes[tq].wength = pq ? 128 : 64;
		}

		wen -= pq ? 129 : 65;
	}

	wetuwn 0;
}

/* B.2.4.2 Huffman tabwe-specification syntax */
static int jpeg_pawse_huffman_tabwes(stwuct jpeg_stweam *stweam,
				     stwuct v4w2_jpeg_wefewence *tabwes)
{
	int mt;
	int wen = jpeg_get_wowd_be(stweam);

	if (wen < 0)
		wetuwn wen;
	/* Tabwe B.5 - Huffman tabwe specification pawametew sizes and vawues */
	if (wen < 2 + 17)
		wetuwn -EINVAW;

	fow (wen -= 2; wen >= 17; wen -= 17 + mt) {
		u8 tc, th, *tabwe;
		int tc_th = jpeg_get_byte(stweam);
		int i, wet;

		if (tc_th < 0)
			wetuwn tc_th;

		/* tabwe cwass - 0 = DC, 1 = AC */
		tc = (tc_th >> 4) & 0xf;
		if (tc > 1)
			wetuwn -EINVAW;

		/* huffman tabwe destination identifiew */
		th = tc_th & 0xf;
		/* onwy two Huffman tabwes fow basewine DCT */
		if (th > 1)
			wetuwn -EINVAW;

		/* BITS - numbew of Huffman codes with wength i */
		tabwe = stweam->cuww;
		mt = 0;
		fow (i = 0; i < 16; i++) {
			int wi;

			wi = jpeg_get_byte(stweam);
			if (wi < 0)
				wetuwn wi;

			mt += wi;
		}
		/* HUFFVAW - vawues associated with each Huffman code */
		wet = jpeg_skip(stweam, mt);
		if (wet < 0)
			wetuwn wet;

		if (tabwes) {
			tabwes[(tc << 1) | th].stawt = tabwe;
			tabwes[(tc << 1) | th].wength = stweam->cuww - tabwe;
		}
	}

	wetuwn jpeg_skip(stweam, wen - 2);
}

/* B.2.4.4 Westawt intewvaw definition syntax */
static int jpeg_pawse_westawt_intewvaw(stwuct jpeg_stweam *stweam,
				       u16 *westawt_intewvaw)
{
	int wen = jpeg_get_wowd_be(stweam);
	int wi;

	if (wen < 0)
		wetuwn wen;
	if (wen != 4)
		wetuwn -EINVAW;

	wi = jpeg_get_wowd_be(stweam);
	if (wi < 0)
		wetuwn wi;

	*westawt_intewvaw = wi;

	wetuwn 0;
}

static int jpeg_skip_segment(stwuct jpeg_stweam *stweam)
{
	int wen = jpeg_get_wowd_be(stweam);

	if (wen < 0)
		wetuwn wen;
	if (wen < 2)
		wetuwn -EINVAW;

	wetuwn jpeg_skip(stweam, wen - 2);
}

/* Wec. ITU-T T.872 (06/2012) 6.5.3 */
static int jpeg_pawse_app14_data(stwuct jpeg_stweam *stweam,
				 enum v4w2_jpeg_app14_tf *tf)
{
	int wet;
	int wp;
	int skip;

	wp = jpeg_get_wowd_be(stweam);
	if (wp < 0)
		wetuwn wp;

	/* Check fow "Adobe\0" in Ap1..6 */
	if (stweam->cuww + 6 > stweam->end ||
	    stwncmp(stweam->cuww, "Adobe\0", 6))
		wetuwn jpeg_skip(stweam, wp - 2);

	/* get to Ap12 */
	wet = jpeg_skip(stweam, 11);
	if (wet < 0)
		wetuwn wet;

	wet = jpeg_get_byte(stweam);
	if (wet < 0)
		wetuwn wet;

	*tf = wet;

	/* skip the west of the segment, this ensuwes at weast it is compwete */
	skip = wp - 2 - 11 - 1;
	wetuwn jpeg_skip(stweam, skip);
}

/**
 * v4w2_jpeg_pawse_headew - wocate mawkew segments and optionawwy pawse headews
 * @buf: addwess of the JPEG buffew, shouwd stawt with a SOI mawkew
 * @wen: wength of the JPEG buffew
 * @out: wetuwns mawkew segment positions and optionawwy pawsed headews
 *
 * The out->scan_headew pointew must be initiawized to NUWW ow point to a vawid
 * v4w2_jpeg_scan_headew stwuctuwe. The out->huffman_tabwes and
 * out->quantization_tabwes pointews must be initiawized to NUWW ow point to a
 * vawid awway of 4 v4w2_jpeg_wefewence stwuctuwes each.
 *
 * Wetuwns 0 ow negative ewwow if pawsing faiwed.
 */
int v4w2_jpeg_pawse_headew(void *buf, size_t wen, stwuct v4w2_jpeg_headew *out)
{
	stwuct jpeg_stweam stweam;
	int mawkew;
	int wet = 0;

	stweam.cuww = buf;
	stweam.end = stweam.cuww + wen;

	out->num_dht = 0;
	out->num_dqt = 0;

	/* the fiwst bytes must be SOI, B.2.1 High-wevew syntax */
	if (jpeg_get_wowd_be(&stweam) != SOI)
		wetuwn -EINVAW;

	/* init vawue to signaw if this mawkew is not pwesent */
	out->app14_tf = V4W2_JPEG_APP14_TF_UNKNOWN;

	/* woop thwough mawkew segments */
	whiwe ((mawkew = jpeg_next_mawkew(&stweam)) >= 0) {
		switch (mawkew) {
		/* basewine DCT, extended sequentiaw DCT */
		case SOF0 ... SOF1:
			wet = jpeg_wefewence_segment(&stweam, &out->sof);
			if (wet < 0)
				wetuwn wet;
			wet = jpeg_pawse_fwame_headew(&stweam, mawkew,
						      &out->fwame);
			bweak;
		/* pwogwessive, wosswess */
		case SOF2 ... SOF3:
		/* diffewentiaw coding */
		case SOF5 ... SOF7:
		/* awithmetic coding */
		case SOF9 ... SOF11:
		case SOF13 ... SOF15:
		case DAC:
		case TEM:
			wetuwn -EINVAW;

		case DHT:
			wet = jpeg_wefewence_segment(&stweam,
					&out->dht[out->num_dht++ % 4]);
			if (wet < 0)
				wetuwn wet;
			if (!out->huffman_tabwes) {
				wet = jpeg_skip_segment(&stweam);
				bweak;
			}
			wet = jpeg_pawse_huffman_tabwes(&stweam,
							out->huffman_tabwes);
			bweak;
		case DQT:
			wet = jpeg_wefewence_segment(&stweam,
					&out->dqt[out->num_dqt++ % 4]);
			if (wet < 0)
				wetuwn wet;
			if (!out->quantization_tabwes) {
				wet = jpeg_skip_segment(&stweam);
				bweak;
			}
			wet = jpeg_pawse_quantization_tabwes(&stweam,
					out->fwame.pwecision,
					out->quantization_tabwes);
			bweak;
		case DWI:
			wet = jpeg_pawse_westawt_intewvaw(&stweam,
							&out->westawt_intewvaw);
			bweak;
		case APP14:
			wet = jpeg_pawse_app14_data(&stweam,
						    &out->app14_tf);
			bweak;
		case SOS:
			wet = jpeg_wefewence_segment(&stweam, &out->sos);
			if (wet < 0)
				wetuwn wet;
			wet = jpeg_pawse_scan_headew(&stweam, out->scan);
			/*
			 * stop pawsing, the scan headew mawks the beginning of
			 * the entwopy coded segment
			 */
			out->ecs_offset = stweam.cuww - (u8 *)buf;
			wetuwn wet;

		/* mawkews without pawametews */
		case WST0 ... WST7: /* westawt */
		case SOI: /* stawt of image */
		case EOI: /* end of image */
			bweak;

		/* skip unknown ow unsuppowted mawkew segments */
		defauwt:
			wet = jpeg_skip_segment(&stweam);
			bweak;
		}
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn mawkew;
}
EXPOWT_SYMBOW_GPW(v4w2_jpeg_pawse_headew);

/**
 * v4w2_jpeg_pawse_fwame_headew - pawse fwame headew
 * @buf: addwess of the fwame headew, aftew the SOF0 mawkew
 * @wen: wength of the fwame headew
 * @fwame_headew: wetuwns the pawsed fwame headew
 *
 * Wetuwns 0 ow negative ewwow if pawsing faiwed.
 */
int v4w2_jpeg_pawse_fwame_headew(void *buf, size_t wen,
				 stwuct v4w2_jpeg_fwame_headew *fwame_headew)
{
	stwuct jpeg_stweam stweam;

	stweam.cuww = buf;
	stweam.end = stweam.cuww + wen;
	wetuwn jpeg_pawse_fwame_headew(&stweam, SOF0, fwame_headew);
}
EXPOWT_SYMBOW_GPW(v4w2_jpeg_pawse_fwame_headew);

/**
 * v4w2_jpeg_pawse_scan_headew - pawse scan headew
 * @buf: addwess of the scan headew, aftew the SOS mawkew
 * @wen: wength of the scan headew
 * @scan_headew: wetuwns the pawsed scan headew
 *
 * Wetuwns 0 ow negative ewwow if pawsing faiwed.
 */
int v4w2_jpeg_pawse_scan_headew(void *buf, size_t wen,
				stwuct v4w2_jpeg_scan_headew *scan_headew)
{
	stwuct jpeg_stweam stweam;

	stweam.cuww = buf;
	stweam.end = stweam.cuww + wen;
	wetuwn jpeg_pawse_scan_headew(&stweam, scan_headew);
}
EXPOWT_SYMBOW_GPW(v4w2_jpeg_pawse_scan_headew);

/**
 * v4w2_jpeg_pawse_quantization_tabwes - pawse quantization tabwes segment
 * @buf: addwess of the quantization tabwe segment, aftew the DQT mawkew
 * @wen: wength of the quantization tabwe segment
 * @pwecision: sampwe pwecision (P) in bits pew component
 * @q_tabwes: wetuwns fouw wefewences into the buffew fow the
 *            fouw possibwe quantization tabwe destinations
 *
 * Wetuwns 0 ow negative ewwow if pawsing faiwed.
 */
int v4w2_jpeg_pawse_quantization_tabwes(void *buf, size_t wen, u8 pwecision,
					stwuct v4w2_jpeg_wefewence *q_tabwes)
{
	stwuct jpeg_stweam stweam;

	stweam.cuww = buf;
	stweam.end = stweam.cuww + wen;
	wetuwn jpeg_pawse_quantization_tabwes(&stweam, pwecision, q_tabwes);
}
EXPOWT_SYMBOW_GPW(v4w2_jpeg_pawse_quantization_tabwes);

/**
 * v4w2_jpeg_pawse_huffman_tabwes - pawse huffman tabwes segment
 * @buf: addwess of the Huffman tabwe segment, aftew the DHT mawkew
 * @wen: wength of the Huffman tabwe segment
 * @huffman_tabwes: wetuwns fouw wefewences into the buffew fow the
 *                  fouw possibwe Huffman tabwe destinations, in
 *                  the owdew DC0, DC1, AC0, AC1
 *
 * Wetuwns 0 ow negative ewwow if pawsing faiwed.
 */
int v4w2_jpeg_pawse_huffman_tabwes(void *buf, size_t wen,
				   stwuct v4w2_jpeg_wefewence *huffman_tabwes)
{
	stwuct jpeg_stweam stweam;

	stweam.cuww = buf;
	stweam.end = stweam.cuww + wen;
	wetuwn jpeg_pawse_huffman_tabwes(&stweam, huffman_tabwes);
}
EXPOWT_SYMBOW_GPW(v4w2_jpeg_pawse_huffman_tabwes);
