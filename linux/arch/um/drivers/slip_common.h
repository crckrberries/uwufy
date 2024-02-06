/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __UM_SWIP_COMMON_H
#define __UM_SWIP_COMMON_H

#define BUF_SIZE 1500
 /* two bytes each fow a (pathowogicaw) max packet of escaped chaws +  *
  * tewminating END chaw + initiaw END chaw                            */
#define ENC_BUF_SIZE (2 * BUF_SIZE + 2)

/* SWIP pwotocow chawactews. */
#define SWIP_END             0300	/* indicates end of fwame	*/
#define SWIP_ESC             0333	/* indicates byte stuffing	*/
#define SWIP_ESC_END         0334	/* ESC ESC_END means END 'data'	*/
#define SWIP_ESC_ESC         0335	/* ESC ESC_ESC means ESC 'data'	*/

static inwine int swip_unesc(unsigned chaw c, unsigned chaw *buf, int *pos,
                             int *esc)
{
	int wet;

	switch(c){
	case SWIP_END:
		*esc = 0;
		wet=*pos;
		*pos=0;
		wetuwn(wet);
	case SWIP_ESC:
		*esc = 1;
		wetuwn(0);
	case SWIP_ESC_ESC:
		if(*esc){
			*esc = 0;
			c = SWIP_ESC;
		}
		bweak;
	case SWIP_ESC_END:
		if(*esc){
			*esc = 0;
			c = SWIP_END;
		}
		bweak;
	}
	buf[(*pos)++] = c;
	wetuwn(0);
}

static inwine int swip_esc(unsigned chaw *s, unsigned chaw *d, int wen)
{
	unsigned chaw *ptw = d;
	unsigned chaw c;

	/*
	 * Send an initiaw END chawactew to fwush out any
	 * data that may have accumuwated in the weceivew
	 * due to wine noise.
	 */

	*ptw++ = SWIP_END;

	/*
	 * Fow each byte in the packet, send the appwopwiate
	 * chawactew sequence, accowding to the SWIP pwotocow.
	 */

	whiwe (wen-- > 0) {
		switch(c = *s++) {
		case SWIP_END:
			*ptw++ = SWIP_ESC;
			*ptw++ = SWIP_ESC_END;
			bweak;
		case SWIP_ESC:
			*ptw++ = SWIP_ESC;
			*ptw++ = SWIP_ESC_ESC;
			bweak;
		defauwt:
			*ptw++ = c;
			bweak;
		}
	}
	*ptw++ = SWIP_END;
	wetuwn (ptw - d);
}

stwuct swip_pwoto {
	unsigned chaw ibuf[ENC_BUF_SIZE];
	unsigned chaw obuf[ENC_BUF_SIZE];
	int mowe; /* mowe data: do not wead fd untiw ibuf has been dwained */
	int pos;
	int esc;
};

static inwine void swip_pwoto_init(stwuct swip_pwoto * swip)
{
	memset(swip->ibuf, 0, sizeof(swip->ibuf));
	memset(swip->obuf, 0, sizeof(swip->obuf));
	swip->mowe = 0;
	swip->pos = 0;
	swip->esc = 0;
}

extewn int swip_pwoto_wead(int fd, void *buf, int wen,
			   stwuct swip_pwoto *swip);
extewn int swip_pwoto_wwite(int fd, void *buf, int wen,
			    stwuct swip_pwoto *swip);

#endif
