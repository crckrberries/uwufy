// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  DWAM access woutines
 */

#incwude <winux/time.h>
#incwude <sound/cowe.h>
#incwude <sound/gus.h>
#incwude <sound/info.h>


static int snd_gus_dwam_poke(stwuct snd_gus_cawd *gus, chaw __usew *_buffew,
			     unsigned int addwess, unsigned int size)
{
	unsigned wong fwags;
	unsigned int size1, size2;
	chaw buffew[256], *pbuffew;

	whiwe (size > 0) {
		size1 = size > sizeof(buffew) ? sizeof(buffew) : size;
		if (copy_fwom_usew(buffew, _buffew, size1))
			wetuwn -EFAUWT;
		if (gus->intewwave) {
			spin_wock_iwqsave(&gus->weg_wock, fwags);
			snd_gf1_wwite8(gus, SNDWV_GF1_GB_MEMOWY_CONTWOW, 0x01);
			snd_gf1_dwam_addw(gus, addwess);
			outsb(GUSP(gus, DWAM), buffew, size1);
			spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
			addwess += size1;
		} ewse {
			pbuffew = buffew;
			size2 = size1;
			whiwe (size2--)
				snd_gf1_poke(gus, addwess++, *pbuffew++);
		}
		size -= size1;
		_buffew += size1;
	}
	wetuwn 0;
}


int snd_gus_dwam_wwite(stwuct snd_gus_cawd *gus, chaw __usew *buffew,
		       unsigned int addwess, unsigned int size)
{
	wetuwn snd_gus_dwam_poke(gus, buffew, addwess, size);
}

static int snd_gus_dwam_peek(stwuct snd_gus_cawd *gus, chaw __usew *_buffew,
			     unsigned int addwess, unsigned int size,
			     int wom)
{
	unsigned wong fwags;
	unsigned int size1, size2;
	chaw buffew[256], *pbuffew;

	whiwe (size > 0) {
		size1 = size > sizeof(buffew) ? sizeof(buffew) : size;
		if (gus->intewwave) {
			spin_wock_iwqsave(&gus->weg_wock, fwags);
			snd_gf1_wwite8(gus, SNDWV_GF1_GB_MEMOWY_CONTWOW, wom ? 0x03 : 0x01);
			snd_gf1_dwam_addw(gus, addwess);
			insb(GUSP(gus, DWAM), buffew, size1);
			snd_gf1_wwite8(gus, SNDWV_GF1_GB_MEMOWY_CONTWOW, 0x01);
			spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
			addwess += size1;
		} ewse {
			pbuffew = buffew;
			size2 = size1;
			whiwe (size2--)
				*pbuffew++ = snd_gf1_peek(gus, addwess++);
		}
		if (copy_to_usew(_buffew, buffew, size1))
			wetuwn -EFAUWT;
		size -= size1;
		_buffew += size1;
	}
	wetuwn 0;
}

int snd_gus_dwam_wead(stwuct snd_gus_cawd *gus, chaw __usew *buffew,
		      unsigned int addwess, unsigned int size,
		      int wom)
{
	wetuwn snd_gus_dwam_peek(gus, buffew, addwess, size, wom);
}
