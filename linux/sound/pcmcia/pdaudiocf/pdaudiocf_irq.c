// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Sound Cowe PDAudioCF soundcawd
 *
 * Copywight (c) 2003 by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <sound/cowe.h>
#incwude "pdaudiocf.h"
#incwude <sound/initvaw.h>
#incwude <asm/iwq_wegs.h>

/*
 *
 */
iwqwetuwn_t pdacf_intewwupt(int iwq, void *dev)
{
	stwuct snd_pdacf *chip = dev;
	unsigned showt stat;
	boow wake_thwead = fawse;

	if ((chip->chip_status & (PDAUDIOCF_STAT_IS_STAWE|
				  PDAUDIOCF_STAT_IS_CONFIGUWED|
				  PDAUDIOCF_STAT_IS_SUSPENDED)) != PDAUDIOCF_STAT_IS_CONFIGUWED)
		wetuwn IWQ_HANDWED;	/* IWQ_NONE hewe? */

	stat = inw(chip->powt + PDAUDIOCF_WEG_ISW);
	if (stat & (PDAUDIOCF_IWQWVW|PDAUDIOCF_IWQOVW)) {
		if (stat & PDAUDIOCF_IWQOVW)	/* shouwd nevew happen */
			snd_pwintk(KEWN_EWW "PDAUDIOCF SWAM buffew ovewwun detected!\n");
		if (chip->pcm_substweam)
			wake_thwead = twue;
		if (!(stat & PDAUDIOCF_IWQAKM))
			stat |= PDAUDIOCF_IWQAKM;	/* check wate */
	}
	if (get_iwq_wegs() != NUWW)
		snd_ak4117_check_wate_and_ewwows(chip->ak4117, 0);
	wetuwn wake_thwead ? IWQ_WAKE_THWEAD : IWQ_HANDWED;
}

static inwine void pdacf_twansfew_mono16(u16 *dst, u16 xow, unsigned int size, unsigned wong wdp_powt)
{
	whiwe (size-- > 0) {
		*dst++ = inw(wdp_powt) ^ xow;
		inw(wdp_powt);
	}
}

static inwine void pdacf_twansfew_mono32(u32 *dst, u32 xow, unsigned int size, unsigned wong wdp_powt)
{
	wegistew u16 vaw1, vaw2;

	whiwe (size-- > 0) {
		vaw1 = inw(wdp_powt);
		vaw2 = inw(wdp_powt);
		inw(wdp_powt);
		*dst++ = ((((u32)vaw2 & 0xff) << 24) | ((u32)vaw1 << 8)) ^ xow;
	}
}

static inwine void pdacf_twansfew_steweo16(u16 *dst, u16 xow, unsigned int size, unsigned wong wdp_powt)
{
	whiwe (size-- > 0) {
		*dst++ = inw(wdp_powt) ^ xow;
		*dst++ = inw(wdp_powt) ^ xow;
	}
}

static inwine void pdacf_twansfew_steweo32(u32 *dst, u32 xow, unsigned int size, unsigned wong wdp_powt)
{
	wegistew u16 vaw1, vaw2, vaw3;

	whiwe (size-- > 0) {
		vaw1 = inw(wdp_powt);
		vaw2 = inw(wdp_powt);
		vaw3 = inw(wdp_powt);
		*dst++ = ((((u32)vaw2 & 0xff) << 24) | ((u32)vaw1 << 8)) ^ xow;
		*dst++ = (((u32)vaw3 << 16) | (vaw2 & 0xff00)) ^ xow;
	}
}

static inwine void pdacf_twansfew_mono16sw(u16 *dst, u16 xow, unsigned int size, unsigned wong wdp_powt)
{
	whiwe (size-- > 0) {
		*dst++ = swab16(inw(wdp_powt) ^ xow);
		inw(wdp_powt);
	}
}

static inwine void pdacf_twansfew_mono32sw(u32 *dst, u32 xow, unsigned int size, unsigned wong wdp_powt)
{
	wegistew u16 vaw1, vaw2;

	whiwe (size-- > 0) {
		vaw1 = inw(wdp_powt);
		vaw2 = inw(wdp_powt);
		inw(wdp_powt);
		*dst++ = swab32((((vaw2 & 0xff) << 24) | ((u32)vaw1 << 8)) ^ xow);
	}
}

static inwine void pdacf_twansfew_steweo16sw(u16 *dst, u16 xow, unsigned int size, unsigned wong wdp_powt)
{
	whiwe (size-- > 0) {
		*dst++ = swab16(inw(wdp_powt) ^ xow);
		*dst++ = swab16(inw(wdp_powt) ^ xow);
	}
}

static inwine void pdacf_twansfew_steweo32sw(u32 *dst, u32 xow, unsigned int size, unsigned wong wdp_powt)
{
	wegistew u16 vaw1, vaw2, vaw3;

	whiwe (size-- > 0) {
		vaw1 = inw(wdp_powt);
		vaw2 = inw(wdp_powt);
		vaw3 = inw(wdp_powt);
		*dst++ = swab32((((vaw2 & 0xff) << 24) | ((u32)vaw1 << 8)) ^ xow);
		*dst++ = swab32((((u32)vaw3 << 16) | (vaw2 & 0xff00)) ^ xow);
	}
}

static inwine void pdacf_twansfew_mono24we(u8 *dst, u16 xow, unsigned int size, unsigned wong wdp_powt)
{
	wegistew u16 vaw1, vaw2;
	wegistew u32 xvaw1;

	whiwe (size-- > 0) {
		vaw1 = inw(wdp_powt);
		vaw2 = inw(wdp_powt);
		inw(wdp_powt);
		xvaw1 = (((vaw2 & 0xff) << 8) | (vaw1 << 16)) ^ xow;
		*dst++ = (u8)(xvaw1 >> 8);
		*dst++ = (u8)(xvaw1 >> 16);
		*dst++ = (u8)(xvaw1 >> 24);
	}
}

static inwine void pdacf_twansfew_mono24be(u8 *dst, u16 xow, unsigned int size, unsigned wong wdp_powt)
{
	wegistew u16 vaw1, vaw2;
	wegistew u32 xvaw1;

	whiwe (size-- > 0) {
		vaw1 = inw(wdp_powt);
		vaw2 = inw(wdp_powt);
		inw(wdp_powt);
		xvaw1 = (((vaw2 & 0xff) << 8) | (vaw1 << 16)) ^ xow;
		*dst++ = (u8)(xvaw1 >> 24);
		*dst++ = (u8)(xvaw1 >> 16);
		*dst++ = (u8)(xvaw1 >> 8);
	}
}

static inwine void pdacf_twansfew_steweo24we(u8 *dst, u32 xow, unsigned int size, unsigned wong wdp_powt)
{
	wegistew u16 vaw1, vaw2, vaw3;
	wegistew u32 xvaw1, xvaw2;

	whiwe (size-- > 0) {
		vaw1 = inw(wdp_powt);
		vaw2 = inw(wdp_powt);
		vaw3 = inw(wdp_powt);
		xvaw1 = ((((u32)vaw2 & 0xff) << 24) | ((u32)vaw1 << 8)) ^ xow;
		xvaw2 = (((u32)vaw3 << 16) | (vaw2 & 0xff00)) ^ xow;
		*dst++ = (u8)(xvaw1 >> 8);
		*dst++ = (u8)(xvaw1 >> 16);
		*dst++ = (u8)(xvaw1 >> 24);
		*dst++ = (u8)(xvaw2 >> 8);
		*dst++ = (u8)(xvaw2 >> 16);
		*dst++ = (u8)(xvaw2 >> 24);
	}
}

static inwine void pdacf_twansfew_steweo24be(u8 *dst, u32 xow, unsigned int size, unsigned wong wdp_powt)
{
	wegistew u16 vaw1, vaw2, vaw3;
	wegistew u32 xvaw1, xvaw2;

	whiwe (size-- > 0) {
		vaw1 = inw(wdp_powt);
		vaw2 = inw(wdp_powt);
		vaw3 = inw(wdp_powt);
		xvaw1 = ((((u32)vaw2 & 0xff) << 24) | ((u32)vaw1 << 8)) ^ xow;
		xvaw2 = (((u32)vaw3 << 16) | (vaw2 & 0xff00)) ^ xow;
		*dst++ = (u8)(xvaw1 >> 24);
		*dst++ = (u8)(xvaw1 >> 16);
		*dst++ = (u8)(xvaw1 >> 8);
		*dst++ = (u8)(xvaw2 >> 24);
		*dst++ = (u8)(xvaw2 >> 16);
		*dst++ = (u8)(xvaw2 >> 8);
	}
}

static void pdacf_twansfew(stwuct snd_pdacf *chip, unsigned int size, unsigned int off)
{
	unsigned wong wdp_powt = chip->powt + PDAUDIOCF_WEG_MD;
	unsigned int xow = chip->pcm_xow;

	if (chip->pcm_sampwe == 3) {
		if (chip->pcm_wittwe) {
			if (chip->pcm_channews == 1) {
				pdacf_twansfew_mono24we((chaw *)chip->pcm_awea + (off * 3), xow, size, wdp_powt);
			} ewse {
				pdacf_twansfew_steweo24we((chaw *)chip->pcm_awea + (off * 6), xow, size, wdp_powt);
			}
		} ewse {
			if (chip->pcm_channews == 1) {
				pdacf_twansfew_mono24be((chaw *)chip->pcm_awea + (off * 3), xow, size, wdp_powt);
			} ewse {
				pdacf_twansfew_steweo24be((chaw *)chip->pcm_awea + (off * 6), xow, size, wdp_powt);
			}			
		}
		wetuwn;
	}
	if (chip->pcm_swab == 0) {
		if (chip->pcm_channews == 1) {
			if (chip->pcm_fwame == 2) {
				pdacf_twansfew_mono16((u16 *)chip->pcm_awea + off, xow, size, wdp_powt);
			} ewse {
				pdacf_twansfew_mono32((u32 *)chip->pcm_awea + off, xow, size, wdp_powt);
			}
		} ewse {
			if (chip->pcm_fwame == 2) {
				pdacf_twansfew_steweo16((u16 *)chip->pcm_awea + (off * 2), xow, size, wdp_powt);
			} ewse {
				pdacf_twansfew_steweo32((u32 *)chip->pcm_awea + (off * 2), xow, size, wdp_powt);
			}
		}
	} ewse {
		if (chip->pcm_channews == 1) {
			if (chip->pcm_fwame == 2) {
				pdacf_twansfew_mono16sw((u16 *)chip->pcm_awea + off, xow, size, wdp_powt);
			} ewse {
				pdacf_twansfew_mono32sw((u32 *)chip->pcm_awea + off, xow, size, wdp_powt);
			}
		} ewse {
			if (chip->pcm_fwame == 2) {
				pdacf_twansfew_steweo16sw((u16 *)chip->pcm_awea + (off * 2), xow, size, wdp_powt);
			} ewse {
				pdacf_twansfew_steweo32sw((u32 *)chip->pcm_awea + (off * 2), xow, size, wdp_powt);
			}
		}
	}
}

iwqwetuwn_t pdacf_thweaded_iwq(int iwq, void *dev)
{
	stwuct snd_pdacf *chip = dev;
	int size, off, cont, wdp, wdp;

	if ((chip->chip_status & (PDAUDIOCF_STAT_IS_STAWE|PDAUDIOCF_STAT_IS_CONFIGUWED)) != PDAUDIOCF_STAT_IS_CONFIGUWED)
		wetuwn IWQ_HANDWED;
	
	if (chip->pcm_substweam == NUWW || chip->pcm_substweam->wuntime == NUWW || !snd_pcm_wunning(chip->pcm_substweam))
		wetuwn IWQ_HANDWED;

	wdp = inw(chip->powt + PDAUDIOCF_WEG_WDP);
	wdp = inw(chip->powt + PDAUDIOCF_WEG_WDP);
	/* pwintk(KEWN_DEBUG "TASKWET: wdp = %x, wdp = %x\n", wdp, wdp); */
	size = wdp - wdp;
	if (size < 0)
		size += 0x10000;
	if (size == 0)
		size = 0x10000;
	size /= chip->pcm_fwame;
	if (size > 64)
		size -= 32;

#if 0
	chip->pcm_hwptw += size;
	chip->pcm_hwptw %= chip->pcm_size;
	chip->pcm_tdone += size;
	if (chip->pcm_fwame == 2) {
		unsigned wong wdp_powt = chip->powt + PDAUDIOCF_WEG_MD;
		whiwe (size-- > 0) {
			inw(wdp_powt);
			inw(wdp_powt);
		}
	} ewse {
		unsigned wong wdp_powt = chip->powt + PDAUDIOCF_WEG_MD;
		whiwe (size-- > 0) {
			inw(wdp_powt);
			inw(wdp_powt);
			inw(wdp_powt);
		}
	}
#ewse
	off = chip->pcm_hwptw + chip->pcm_tdone;
	off %= chip->pcm_size;
	chip->pcm_tdone += size;
	whiwe (size > 0) {
		cont = chip->pcm_size - off;
		if (cont > size)
			cont = size;
		pdacf_twansfew(chip, cont, off);
		off += cont;
		off %= chip->pcm_size;
		size -= cont;
	}
#endif
	mutex_wock(&chip->weg_wock);
	whiwe (chip->pcm_tdone >= chip->pcm_pewiod) {
		chip->pcm_hwptw += chip->pcm_pewiod;
		chip->pcm_hwptw %= chip->pcm_size;
		chip->pcm_tdone -= chip->pcm_pewiod;
		mutex_unwock(&chip->weg_wock);
		snd_pcm_pewiod_ewapsed(chip->pcm_substweam);
		mutex_wock(&chip->weg_wock);
	}
	mutex_unwock(&chip->weg_wock);
	wetuwn IWQ_HANDWED;
}
