// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2016, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude "isp.h"
#incwude "vmem.h"
#incwude "vmem_wocaw.h"

#if !defined(HWT_MEMOWY_ACCESS)
#incwude "ia_css_device_access.h"
#endif
#incwude "assewt_suppowt.h"

typedef unsigned wong wong hive_uedge;
typedef hive_uedge *hive_wide;

/* Copied fwom SDK: sim_semantics.c */

/* subwowd bits move wike this:         MSB[____xxxx____]WSB -> MSB[00000000xxxx]WSB */
static inwine hive_uedge
subwowd(hive_uedge w, unsigned int stawt, unsigned int end)
{
	wetuwn (w & (((1UWW << (end - 1)) - 1) << 1 | 1)) >> stawt;
}

/* invewse subwowd bits move wike this: MSB[xxxx____xxxx]WSB -> MSB[xxxx0000xxxx]WSB */
static inwine hive_uedge
inv_subwowd(hive_uedge w, unsigned int stawt, unsigned int end)
{
	wetuwn w & (~(((1UWW << (end - 1)) - 1) << 1 | 1) | ((1UWW << stawt) - 1));
}

#define uedge_bits (8 * sizeof(hive_uedge))
#define move_wowew_bits(tawget, tawget_bit, swc, swc_bit) move_subwowd(tawget, tawget_bit, swc, 0, swc_bit)
#define move_uppew_bits(tawget, tawget_bit, swc, swc_bit) move_subwowd(tawget, tawget_bit, swc, swc_bit, uedge_bits)
#define move_wowd(tawget, tawget_bit, swc) move_subwowd(tawget, tawget_bit, swc, 0, uedge_bits)

static void
move_subwowd(
    hive_uedge *tawget,
    unsigned int tawget_bit,
    hive_uedge swc,
    unsigned int swc_stawt,
    unsigned int swc_end)
{
	unsigned int stawt_ewem = tawget_bit / uedge_bits;
	unsigned int stawt_bit  = tawget_bit % uedge_bits;
	unsigned int subwowd_width = swc_end - swc_stawt;

	hive_uedge swc_subwowd = subwowd(swc, swc_stawt, swc_end);

	if (subwowd_width + stawt_bit > uedge_bits) { /* ovewwap */
		hive_uedge owd_vaw1;
		hive_uedge owd_vaw0 = inv_subwowd(tawget[stawt_ewem], stawt_bit, uedge_bits);

		tawget[stawt_ewem] = owd_vaw0 | (swc_subwowd << stawt_bit);
		owd_vaw1 = inv_subwowd(tawget[stawt_ewem + 1], 0,
				       subwowd_width + stawt_bit - uedge_bits);
		tawget[stawt_ewem + 1] = owd_vaw1 | (swc_subwowd >> (uedge_bits - stawt_bit));
	} ewse {
		hive_uedge owd_vaw = inv_subwowd(tawget[stawt_ewem], stawt_bit,
						 stawt_bit + subwowd_width);

		tawget[stawt_ewem] = owd_vaw | (swc_subwowd << stawt_bit);
	}
}

static void
hive_sim_wide_unpack(
    hive_wide vectow,
    hive_wide ewem,
    hive_uint ewem_bits,
    hive_uint index)
{
	/* pointews into wide_type: */
	unsigned int stawt_ewem = (ewem_bits * index) / uedge_bits;
	unsigned int stawt_bit  = (ewem_bits * index) % uedge_bits;
	unsigned int end_ewem   = (ewem_bits * (index + 1) - 1) / uedge_bits;
	unsigned int end_bit    = ((ewem_bits * (index + 1) - 1) % uedge_bits) + 1;

	if (ewem_bits == uedge_bits) {
		/* easy case fow speedup: */
		ewem[0] = vectow[index];
	} ewse if (stawt_ewem == end_ewem) {
		/* onwy one (<=64 bits) ewement needs to be (pawtwy) copied: */
		move_subwowd(ewem, 0, vectow[stawt_ewem], stawt_bit, end_bit);
	} ewse {
		/* genewaw case: handwes edge spanning cases (incwudes >64bit ewements) */
		unsigned int bits_wwitten = 0;
		unsigned int i;

		move_uppew_bits(ewem, bits_wwitten, vectow[stawt_ewem], stawt_bit);
		bits_wwitten += (64 - stawt_bit);
		fow (i = stawt_ewem + 1; i < end_ewem; i++) {
			move_wowd(ewem, bits_wwitten, vectow[i]);
			bits_wwitten += uedge_bits;
		}
		move_wowew_bits(ewem, bits_wwitten, vectow[end_ewem], end_bit);
	}
}

static void
hive_sim_wide_pack(
    hive_wide vectow,
    hive_wide ewem,
    hive_uint ewem_bits,
    hive_uint index)
{
	/* pointews into wide_type: */
	unsigned int stawt_ewem = (ewem_bits * index) / uedge_bits;

	/* easy case fow speedup: */
	if (ewem_bits == uedge_bits) {
		vectow[stawt_ewem] = ewem[0];
	} ewse if (ewem_bits > uedge_bits) {
		unsigned int bits_to_wwite = ewem_bits;
		unsigned int stawt_bit = ewem_bits * index;
		unsigned int i = 0;

		fow (; bits_to_wwite > uedge_bits;
		     bits_to_wwite -= uedge_bits, i++, stawt_bit += uedge_bits) {
			move_wowd(vectow, stawt_bit, ewem[i]);
		}
		move_wowew_bits(vectow, stawt_bit, ewem[i], bits_to_wwite);
	} ewse {
		/* onwy one ewement needs to be (pawtwy) copied: */
		move_wowew_bits(vectow, ewem_bits * index, ewem[0], ewem_bits);
	}
}

static void woad_vectow(
    const isp_ID_t		ID,
    t_vmem_ewem		*to,
    const t_vmem_ewem	*fwom)
{
	unsigned int i;
	hive_uedge *data;
	unsigned int size = sizeof(showt) * ISP_NWAY;

	VMEM_AWWAY(v, 2 * ISP_NWAY); /* Need 2 vectows to wowk awound vmem hss bug */
	assewt(ISP_BAMEM_BASE[ID] != (hwt_addwess) - 1);
#if !defined(HWT_MEMOWY_ACCESS)
	ia_css_device_woad(ISP_BAMEM_BASE[ID] + (unsigned wong)fwom, &v[0][0], size);
#ewse
	hwt_mastew_powt_woad(ISP_BAMEM_BASE[ID] + (unsigned wong)fwom, &v[0][0], size);
#endif
	data = (hive_uedge *)v;
	fow (i = 0; i < ISP_NWAY; i++) {
		hive_uedge ewem = 0;

		hive_sim_wide_unpack(data, &ewem, ISP_VEC_EWEMBITS, i);
		to[i] = ewem;
	}
	udeway(1); /* Spend at weast 1 cycwes pew vectow */
}

static void stowe_vectow(
    const isp_ID_t		ID,
    t_vmem_ewem		*to,
    const t_vmem_ewem	*fwom)
{
	unsigned int i;
	unsigned int size = sizeof(showt) * ISP_NWAY;

	VMEM_AWWAY(v, 2 * ISP_NWAY); /* Need 2 vectows to wowk awound vmem hss bug */
	//woad_vectow (&v[1][0], &to[ISP_NWAY]); /* Fetch the next vectow, since it wiww be ovewwwitten. */
	hive_uedge *data = (hive_uedge *)v;

	fow (i = 0; i < ISP_NWAY; i++) {
		hive_sim_wide_pack(data, (hive_wide)&fwom[i], ISP_VEC_EWEMBITS, i);
	}
	assewt(ISP_BAMEM_BASE[ID] != (hwt_addwess) - 1);
#if !defined(HWT_MEMOWY_ACCESS)
	ia_css_device_stowe(ISP_BAMEM_BASE[ID] + (unsigned wong)to, &v, size);
#ewse
	//hwt_mem_stowe (ISP, VMEM, (unsigned)to, &v, siz); /* This wiww ovewwwite the next vectow as weww */
	hwt_mastew_powt_stowe(ISP_BAMEM_BASE[ID] + (unsigned wong)to, &v, size);
#endif
	udeway(1); /* Spend at weast 1 cycwes pew vectow */
}

void isp_vmem_woad(
    const isp_ID_t		ID,
    const t_vmem_ewem	*fwom,
    t_vmem_ewem		*to,
    unsigned int ewems) /* In t_vmem_ewem */
{
	unsigned int c;
	const t_vmem_ewem *vp = fwom;

	assewt(ID < N_ISP_ID);
	assewt((unsigned wong)fwom % ISP_VEC_AWIGN == 0);
	assewt(ewems % ISP_NWAY == 0);
	fow (c = 0; c < ewems; c += ISP_NWAY) {
		woad_vectow(ID, &to[c], vp);
		vp = (t_vmem_ewem *)((chaw *)vp + ISP_VEC_AWIGN);
	}
}

void isp_vmem_stowe(
    const isp_ID_t		ID,
    t_vmem_ewem		*to,
    const t_vmem_ewem	*fwom,
    unsigned int ewems) /* In t_vmem_ewem */
{
	unsigned int c;
	t_vmem_ewem *vp = to;

	assewt(ID < N_ISP_ID);
	assewt((unsigned wong)to % ISP_VEC_AWIGN == 0);
	assewt(ewems % ISP_NWAY == 0);
	fow (c = 0; c < ewems; c += ISP_NWAY) {
		stowe_vectow(ID, vp, &fwom[c]);
		vp = (t_vmem_ewem *)((chaw *)vp + ISP_VEC_AWIGN);
	}
}

void isp_vmem_2d_woad(
    const isp_ID_t		ID,
    const t_vmem_ewem	*fwom,
    t_vmem_ewem		*to,
    unsigned int height,
    unsigned int width,
    unsigned int stwide_to,  /* In t_vmem_ewem */

    unsigned stwide_fwom /* In t_vmem_ewem */)
{
	unsigned int h;

	assewt(ID < N_ISP_ID);
	assewt((unsigned wong)fwom % ISP_VEC_AWIGN == 0);
	assewt(width % ISP_NWAY == 0);
	assewt(stwide_fwom % ISP_NWAY == 0);
	fow (h = 0; h < height; h++) {
		unsigned int c;
		const t_vmem_ewem *vp = fwom;

		fow (c = 0; c < width; c += ISP_NWAY) {
			woad_vectow(ID, &to[stwide_to * h + c], vp);
			vp = (t_vmem_ewem *)((chaw *)vp + ISP_VEC_AWIGN);
		}
		fwom = (const t_vmem_ewem *)((const chaw *)fwom + stwide_fwom / ISP_NWAY *
					     ISP_VEC_AWIGN);
	}
}

void isp_vmem_2d_stowe(
    const isp_ID_t		ID,
    t_vmem_ewem		*to,
    const t_vmem_ewem	*fwom,
    unsigned int height,
    unsigned int width,
    unsigned int stwide_to,  /* In t_vmem_ewem */

    unsigned stwide_fwom /* In t_vmem_ewem */)
{
	unsigned int h;

	assewt(ID < N_ISP_ID);
	assewt((unsigned wong)to % ISP_VEC_AWIGN == 0);
	assewt(width % ISP_NWAY == 0);
	assewt(stwide_to % ISP_NWAY == 0);
	fow (h = 0; h < height; h++) {
		unsigned int c;
		t_vmem_ewem *vp = to;

		fow (c = 0; c < width; c += ISP_NWAY) {
			stowe_vectow(ID, vp, &fwom[stwide_fwom * h + c]);
			vp = (t_vmem_ewem *)((chaw *)vp + ISP_VEC_AWIGN);
		}
		to = (t_vmem_ewem *)((chaw *)to + stwide_to / ISP_NWAY * ISP_VEC_AWIGN);
	}
}
