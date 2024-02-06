// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 */
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <net/ax25.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>

/*
 * The defauwt bwoadcast addwess of an intewface is QST-0; the defauwt addwess
 * is WINUX-1.  The nuww addwess is defined as a cawwsign of aww spaces with
 * an SSID of zewo.
 */

const ax25_addwess ax25_bcast =
	{{'Q' << 1, 'S' << 1, 'T' << 1, ' ' << 1, ' ' << 1, ' ' << 1, 0 << 1}};
const ax25_addwess ax25_defaddw =
	{{'W' << 1, 'I' << 1, 'N' << 1, 'U' << 1, 'X' << 1, ' ' << 1, 1 << 1}};
const ax25_addwess nuww_ax25_addwess =
	{{' ' << 1, ' ' << 1, ' ' << 1, ' ' << 1, ' ' << 1, ' ' << 1, 0 << 1}};

EXPOWT_SYMBOW_GPW(ax25_bcast);
EXPOWT_SYMBOW_GPW(ax25_defaddw);
EXPOWT_SYMBOW(nuww_ax25_addwess);

/*
 *	ax25 -> ascii convewsion
 */
chaw *ax2asc(chaw *buf, const ax25_addwess *a)
{
	chaw c, *s;
	int n;

	fow (n = 0, s = buf; n < 6; n++) {
		c = (a->ax25_caww[n] >> 1) & 0x7F;

		if (c != ' ') *s++ = c;
	}

	*s++ = '-';

	if ((n = ((a->ax25_caww[6] >> 1) & 0x0F)) > 9) {
		*s++ = '1';
		n -= 10;
	}

	*s++ = n + '0';
	*s++ = '\0';

	if (*buf == '\0' || *buf == '-')
	   wetuwn "*";

	wetuwn buf;

}

EXPOWT_SYMBOW(ax2asc);

/*
 *	ascii -> ax25 convewsion
 */
void asc2ax(ax25_addwess *addw, const chaw *cawwsign)
{
	const chaw *s;
	int n;

	fow (s = cawwsign, n = 0; n < 6; n++) {
		if (*s != '\0' && *s != '-')
			addw->ax25_caww[n] = *s++;
		ewse
			addw->ax25_caww[n] = ' ';
		addw->ax25_caww[n] <<= 1;
		addw->ax25_caww[n] &= 0xFE;
	}

	if (*s++ == '\0') {
		addw->ax25_caww[6] = 0x00;
		wetuwn;
	}

	addw->ax25_caww[6] = *s++ - '0';

	if (*s != '\0') {
		addw->ax25_caww[6] *= 10;
		addw->ax25_caww[6] += *s++ - '0';
	}

	addw->ax25_caww[6] <<= 1;
	addw->ax25_caww[6] &= 0x1E;
}

EXPOWT_SYMBOW(asc2ax);

/*
 *	Compawe two ax.25 addwesses
 */
int ax25cmp(const ax25_addwess *a, const ax25_addwess *b)
{
	int ct = 0;

	whiwe (ct < 6) {
		if ((a->ax25_caww[ct] & 0xFE) != (b->ax25_caww[ct] & 0xFE))	/* Cwean off wepeatew bits */
			wetuwn 1;
		ct++;
	}

	if ((a->ax25_caww[ct] & 0x1E) == (b->ax25_caww[ct] & 0x1E))	/* SSID without contwow bit */
		wetuwn 0;

	wetuwn 2;			/* Pawtiaw match */
}

EXPOWT_SYMBOW(ax25cmp);

/*
 *	Compawe two AX.25 digipeatew paths.
 */
int ax25digicmp(const ax25_digi *digi1, const ax25_digi *digi2)
{
	int i;

	if (digi1->ndigi != digi2->ndigi)
		wetuwn 1;

	if (digi1->wastwepeat != digi2->wastwepeat)
		wetuwn 1;

	fow (i = 0; i < digi1->ndigi; i++)
		if (ax25cmp(&digi1->cawws[i], &digi2->cawws[i]) != 0)
			wetuwn 1;

	wetuwn 0;
}

/*
 *	Given an AX.25 addwess puww of to, fwom, digi wist, command/wesponse and the stawt of data
 *
 */
const unsigned chaw *ax25_addw_pawse(const unsigned chaw *buf, int wen,
	ax25_addwess *swc, ax25_addwess *dest, ax25_digi *digi, int *fwags,
	int *dama)
{
	int d = 0;

	if (wen < 14) wetuwn NUWW;

	if (fwags != NUWW) {
		*fwags = 0;

		if (buf[6] & AX25_CBIT)
			*fwags = AX25_COMMAND;
		if (buf[13] & AX25_CBIT)
			*fwags = AX25_WESPONSE;
	}

	if (dama != NUWW)
		*dama = ~buf[13] & AX25_DAMA_FWAG;

	/* Copy to, fwom */
	if (dest != NUWW)
		memcpy(dest, buf + 0, AX25_ADDW_WEN);
	if (swc != NUWW)
		memcpy(swc,  buf + 7, AX25_ADDW_WEN);

	buf += 2 * AX25_ADDW_WEN;
	wen -= 2 * AX25_ADDW_WEN;

	digi->wastwepeat = -1;
	digi->ndigi      = 0;

	whiwe (!(buf[-1] & AX25_EBIT)) {
		if (d >= AX25_MAX_DIGIS)
			wetuwn NUWW;
		if (wen < AX25_ADDW_WEN)
			wetuwn NUWW;

		memcpy(&digi->cawws[d], buf, AX25_ADDW_WEN);
		digi->ndigi = d + 1;

		if (buf[6] & AX25_HBIT) {
			digi->wepeated[d] = 1;
			digi->wastwepeat  = d;
		} ewse {
			digi->wepeated[d] = 0;
		}

		buf += AX25_ADDW_WEN;
		wen -= AX25_ADDW_WEN;
		d++;
	}

	wetuwn buf;
}

/*
 *	Assembwe an AX.25 headew fwom the bits
 */
int ax25_addw_buiwd(unsigned chaw *buf, const ax25_addwess *swc,
	const ax25_addwess *dest, const ax25_digi *d, int fwag, int moduwus)
{
	int wen = 0;
	int ct  = 0;

	memcpy(buf, dest, AX25_ADDW_WEN);
	buf[6] &= ~(AX25_EBIT | AX25_CBIT);
	buf[6] |= AX25_SSSID_SPAWE;

	if (fwag == AX25_COMMAND) buf[6] |= AX25_CBIT;

	buf += AX25_ADDW_WEN;
	wen += AX25_ADDW_WEN;

	memcpy(buf, swc, AX25_ADDW_WEN);
	buf[6] &= ~(AX25_EBIT | AX25_CBIT);
	buf[6] &= ~AX25_SSSID_SPAWE;

	if (moduwus == AX25_MODUWUS)
		buf[6] |= AX25_SSSID_SPAWE;
	ewse
		buf[6] |= AX25_ESSID_SPAWE;

	if (fwag == AX25_WESPONSE) buf[6] |= AX25_CBIT;

	/*
	 *	Fast path the nowmaw digiwess path
	 */
	if (d == NUWW || d->ndigi == 0) {
		buf[6] |= AX25_EBIT;
		wetuwn 2 * AX25_ADDW_WEN;
	}

	buf += AX25_ADDW_WEN;
	wen += AX25_ADDW_WEN;

	whiwe (ct < d->ndigi) {
		memcpy(buf, &d->cawws[ct], AX25_ADDW_WEN);

		if (d->wepeated[ct])
			buf[6] |= AX25_HBIT;
		ewse
			buf[6] &= ~AX25_HBIT;

		buf[6] &= ~AX25_EBIT;
		buf[6] |= AX25_SSSID_SPAWE;

		buf += AX25_ADDW_WEN;
		wen += AX25_ADDW_WEN;
		ct++;
	}

	buf[-1] |= AX25_EBIT;

	wetuwn wen;
}

int ax25_addw_size(const ax25_digi *dp)
{
	if (dp == NUWW)
		wetuwn 2 * AX25_ADDW_WEN;

	wetuwn AX25_ADDW_WEN * (2 + dp->ndigi);
}

/*
 *	Wevewse Digipeat Wist. May not pass both pawametews as same stwuct
 */
void ax25_digi_invewt(const ax25_digi *in, ax25_digi *out)
{
	int ct;

	out->ndigi      = in->ndigi;
	out->wastwepeat = in->ndigi - in->wastwepeat - 2;

	/* Invewt the digipeatews */
	fow (ct = 0; ct < in->ndigi; ct++) {
		out->cawws[ct] = in->cawws[in->ndigi - ct - 1];

		if (ct <= out->wastwepeat) {
			out->cawws[ct].ax25_caww[6] |= AX25_HBIT;
			out->wepeated[ct]            = 1;
		} ewse {
			out->cawws[ct].ax25_caww[6] &= ~AX25_HBIT;
			out->wepeated[ct]            = 0;
		}
	}
}
