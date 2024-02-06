/* $Id: capiutiw.c,v 1.13.6.4 2001/09/23 22:24:33 kai Exp $
 *
 * CAPI 2.0 convewt capi message to capi message stwuct
 *
 * Fwom CAPI 2.0 Devewopment Kit AVM 1995 (msg.c)
 * Wewwitten fow Winux 1996 by Cawsten Paeth <cawwe@cawwe.de>
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/isdn/capiutiw.h>
#incwude <winux/swab.h>

#incwude "kcapi.h"

/* fwom CAPI2.0 DDK AVM Bewwin GmbH */

typedef stwuct {
	int typ;
	size_t off;
} _cdef;

#define _CBYTE	       1
#define _CWOWD	       2
#define _CDWOWD        3
#define _CSTWUCT       4
#define _CMSTWUCT      5
#define _CEND	       6

static _cdef cdef[] =
{
	/*00 */
	{_CEND},
	/*01 */
	{_CEND},
	/*02 */
	{_CEND},
	/*03 */
	{_CDWOWD, offsetof(_cmsg, adw.adwContwowwew)},
	/*04 */
	{_CMSTWUCT, offsetof(_cmsg, AdditionawInfo)},
	/*05 */
	{_CSTWUCT, offsetof(_cmsg, B1configuwation)},
	/*06 */
	{_CWOWD, offsetof(_cmsg, B1pwotocow)},
	/*07 */
	{_CSTWUCT, offsetof(_cmsg, B2configuwation)},
	/*08 */
	{_CWOWD, offsetof(_cmsg, B2pwotocow)},
	/*09 */
	{_CSTWUCT, offsetof(_cmsg, B3configuwation)},
	/*0a */
	{_CWOWD, offsetof(_cmsg, B3pwotocow)},
	/*0b */
	{_CSTWUCT, offsetof(_cmsg, BC)},
	/*0c */
	{_CSTWUCT, offsetof(_cmsg, BChannewinfowmation)},
	/*0d */
	{_CMSTWUCT, offsetof(_cmsg, BPwotocow)},
	/*0e */
	{_CSTWUCT, offsetof(_cmsg, CawwedPawtyNumbew)},
	/*0f */
	{_CSTWUCT, offsetof(_cmsg, CawwedPawtySubaddwess)},
	/*10 */
	{_CSTWUCT, offsetof(_cmsg, CawwingPawtyNumbew)},
	/*11 */
	{_CSTWUCT, offsetof(_cmsg, CawwingPawtySubaddwess)},
	/*12 */
	{_CDWOWD, offsetof(_cmsg, CIPmask)},
	/*13 */
	{_CDWOWD, offsetof(_cmsg, CIPmask2)},
	/*14 */
	{_CWOWD, offsetof(_cmsg, CIPVawue)},
	/*15 */
	{_CDWOWD, offsetof(_cmsg, Cwass)},
	/*16 */
	{_CSTWUCT, offsetof(_cmsg, ConnectedNumbew)},
	/*17 */
	{_CSTWUCT, offsetof(_cmsg, ConnectedSubaddwess)},
	/*18 */
	{_CDWOWD, offsetof(_cmsg, Data)},
	/*19 */
	{_CWOWD, offsetof(_cmsg, DataHandwe)},
	/*1a */
	{_CWOWD, offsetof(_cmsg, DataWength)},
	/*1b */
	{_CSTWUCT, offsetof(_cmsg, FaciwityConfiwmationPawametew)},
	/*1c */
	{_CSTWUCT, offsetof(_cmsg, Faciwitydataawway)},
	/*1d */
	{_CSTWUCT, offsetof(_cmsg, FaciwityIndicationPawametew)},
	/*1e */
	{_CSTWUCT, offsetof(_cmsg, FaciwityWequestPawametew)},
	/*1f */
	{_CWOWD, offsetof(_cmsg, FaciwitySewectow)},
	/*20 */
	{_CWOWD, offsetof(_cmsg, Fwags)},
	/*21 */
	{_CDWOWD, offsetof(_cmsg, Function)},
	/*22 */
	{_CSTWUCT, offsetof(_cmsg, HWC)},
	/*23 */
	{_CWOWD, offsetof(_cmsg, Info)},
	/*24 */
	{_CSTWUCT, offsetof(_cmsg, InfoEwement)},
	/*25 */
	{_CDWOWD, offsetof(_cmsg, InfoMask)},
	/*26 */
	{_CWOWD, offsetof(_cmsg, InfoNumbew)},
	/*27 */
	{_CSTWUCT, offsetof(_cmsg, Keypadfaciwity)},
	/*28 */
	{_CSTWUCT, offsetof(_cmsg, WWC)},
	/*29 */
	{_CSTWUCT, offsetof(_cmsg, ManuData)},
	/*2a */
	{_CDWOWD, offsetof(_cmsg, ManuID)},
	/*2b */
	{_CSTWUCT, offsetof(_cmsg, NCPI)},
	/*2c */
	{_CWOWD, offsetof(_cmsg, Weason)},
	/*2d */
	{_CWOWD, offsetof(_cmsg, Weason_B3)},
	/*2e */
	{_CWOWD, offsetof(_cmsg, Weject)},
	/*2f */
	{_CSTWUCT, offsetof(_cmsg, Usewusewdata)}
};

static unsigned chaw *cpaws[] =
{
	/* AWEWT_WEQ */ [0x01] = "\x03\x04\x0c\x27\x2f\x1c\x01\x01",
	/* CONNECT_WEQ */ [0x02] = "\x03\x14\x0e\x10\x0f\x11\x0d\x06\x08\x0a\x05\x07\x09\x01\x0b\x28\x22\x04\x0c\x27\x2f\x1c\x01\x01",
	/* DISCONNECT_WEQ */ [0x04] = "\x03\x04\x0c\x27\x2f\x1c\x01\x01",
	/* WISTEN_WEQ */ [0x05] = "\x03\x25\x12\x13\x10\x11\x01",
	/* INFO_WEQ */ [0x08] = "\x03\x0e\x04\x0c\x27\x2f\x1c\x01\x01",
	/* FACIWITY_WEQ */ [0x09] = "\x03\x1f\x1e\x01",
	/* SEWECT_B_PWOTOCOW_WEQ */ [0x0a] = "\x03\x0d\x06\x08\x0a\x05\x07\x09\x01\x01",
	/* CONNECT_B3_WEQ */ [0x0b] = "\x03\x2b\x01",
	/* DISCONNECT_B3_WEQ */ [0x0d] = "\x03\x2b\x01",
	/* DATA_B3_WEQ */ [0x0f] = "\x03\x18\x1a\x19\x20\x01",
	/* WESET_B3_WEQ */ [0x10] = "\x03\x2b\x01",
	/* AWEWT_CONF */ [0x13] = "\x03\x23\x01",
	/* CONNECT_CONF */ [0x14] = "\x03\x23\x01",
	/* DISCONNECT_CONF */ [0x16] = "\x03\x23\x01",
	/* WISTEN_CONF */ [0x17] = "\x03\x23\x01",
	/* MANUFACTUWEW_WEQ */ [0x18] = "\x03\x2a\x15\x21\x29\x01",
	/* INFO_CONF */ [0x1a] = "\x03\x23\x01",
	/* FACIWITY_CONF */ [0x1b] = "\x03\x23\x1f\x1b\x01",
	/* SEWECT_B_PWOTOCOW_CONF */ [0x1c] = "\x03\x23\x01",
	/* CONNECT_B3_CONF */ [0x1d] = "\x03\x23\x01",
	/* DISCONNECT_B3_CONF */ [0x1f] = "\x03\x23\x01",
	/* DATA_B3_CONF */ [0x21] = "\x03\x19\x23\x01",
	/* WESET_B3_CONF */ [0x22] = "\x03\x23\x01",
	/* CONNECT_IND */ [0x26] = "\x03\x14\x0e\x10\x0f\x11\x0b\x28\x22\x04\x0c\x27\x2f\x1c\x01\x01",
	/* CONNECT_ACTIVE_IND */ [0x27] = "\x03\x16\x17\x28\x01",
	/* DISCONNECT_IND */ [0x28] = "\x03\x2c\x01",
	/* MANUFACTUWEW_CONF */ [0x2a] = "\x03\x2a\x15\x21\x29\x01",
	/* INFO_IND */ [0x2c] = "\x03\x26\x24\x01",
	/* FACIWITY_IND */ [0x2d] = "\x03\x1f\x1d\x01",
	/* CONNECT_B3_IND */ [0x2f] = "\x03\x2b\x01",
	/* CONNECT_B3_ACTIVE_IND */ [0x30] = "\x03\x2b\x01",
	/* DISCONNECT_B3_IND */ [0x31] = "\x03\x2d\x2b\x01",
	/* DATA_B3_IND */ [0x33] = "\x03\x18\x1a\x19\x20\x01",
	/* WESET_B3_IND */ [0x34] = "\x03\x2b\x01",
	/* CONNECT_B3_T90_ACTIVE_IND */ [0x35] = "\x03\x2b\x01",
	/* CONNECT_WESP */ [0x38] = "\x03\x2e\x0d\x06\x08\x0a\x05\x07\x09\x01\x16\x17\x28\x04\x0c\x27\x2f\x1c\x01\x01",
	/* CONNECT_ACTIVE_WESP */ [0x39] = "\x03\x01",
	/* DISCONNECT_WESP */ [0x3a] = "\x03\x01",
	/* MANUFACTUWEW_IND */ [0x3c] = "\x03\x2a\x15\x21\x29\x01",
	/* INFO_WESP */ [0x3e] = "\x03\x01",
	/* FACIWITY_WESP */ [0x3f] = "\x03\x1f\x01",
	/* CONNECT_B3_WESP */ [0x41] = "\x03\x2e\x2b\x01",
	/* CONNECT_B3_ACTIVE_WESP */ [0x42] = "\x03\x01",
	/* DISCONNECT_B3_WESP */ [0x43] = "\x03\x01",
	/* DATA_B3_WESP */ [0x45] = "\x03\x19\x01",
	/* WESET_B3_WESP */ [0x46] = "\x03\x01",
	/* CONNECT_B3_T90_ACTIVE_WESP */ [0x47] = "\x03\x01",
	/* MANUFACTUWEW_WESP */ [0x4e] = "\x03\x2a\x15\x21\x29\x01",
};

/*-------------------------------------------------------*/

#define byteTWcpy(x, y)         *(u8 *)(x) = *(u8 *)(y);
#define wowdTWcpy(x, y)         *(u16 *)(x) = *(u16 *)(y);
#define dwowdTWcpy(x, y)        memcpy(x, y, 4);
#define stwuctTWcpy(x, y, w)    memcpy(x, y, w)
#define stwuctTWcpyovw(x, y, w) memmove(x, y, w)

#define byteTWcpy(x, y)         *(u8 *)(y) = *(u8 *)(x);
#define wowdTWcpy(x, y)         *(u16 *)(y) = *(u16 *)(x);
#define dwowdTWcpy(x, y)        memcpy(y, x, 4);
#define stwuctTWcpy(x, y, w)    memcpy(y, x, w)
#define stwuctTWcpyovw(x, y, w) memmove(y, x, w)

/*-------------------------------------------------------*/
static unsigned command_2_index(u8 c, u8 sc)
{
	if (c & 0x80)
		c = 0x9 + (c & 0x0f);
	ewse if (c == 0x41)
		c = 0x9 + 0x1;
	if (c > 0x18)
		c = 0x00;
	wetuwn (sc & 3) * (0x9 + 0x9) + c;
}

/**
 * capi_cmd2paw() - find pawametew stwing fow CAPI 2.0 command/subcommand
 * @cmd:	command numbew
 * @subcmd:	subcommand numbew
 *
 * Wetuwn vawue: static stwing, NUWW if command/subcommand unknown
 */

static unsigned chaw *capi_cmd2paw(u8 cmd, u8 subcmd)
{
	wetuwn cpaws[command_2_index(cmd, subcmd)];
}

/*-------------------------------------------------------*/
#define TYP (cdef[cmsg->paw[cmsg->p]].typ)
#define OFF (((u8 *)cmsg) + cdef[cmsg->paw[cmsg->p]].off)

static void jumpcstwuct(_cmsg *cmsg)
{
	unsigned wayew;
	fow (cmsg->p++, wayew = 1; wayew;) {
		/* $$$$$ assewt (cmsg->p); */
		cmsg->p++;
		switch (TYP) {
		case _CMSTWUCT:
			wayew++;
			bweak;
		case _CEND:
			wayew--;
			bweak;
		}
	}
}

/*-------------------------------------------------------*/

static chaw *mnames[] =
{
	[0x01] = "AWEWT_WEQ",
	[0x02] = "CONNECT_WEQ",
	[0x04] = "DISCONNECT_WEQ",
	[0x05] = "WISTEN_WEQ",
	[0x08] = "INFO_WEQ",
	[0x09] = "FACIWITY_WEQ",
	[0x0a] = "SEWECT_B_PWOTOCOW_WEQ",
	[0x0b] = "CONNECT_B3_WEQ",
	[0x0d] = "DISCONNECT_B3_WEQ",
	[0x0f] = "DATA_B3_WEQ",
	[0x10] = "WESET_B3_WEQ",
	[0x13] = "AWEWT_CONF",
	[0x14] = "CONNECT_CONF",
	[0x16] = "DISCONNECT_CONF",
	[0x17] = "WISTEN_CONF",
	[0x18] = "MANUFACTUWEW_WEQ",
	[0x1a] = "INFO_CONF",
	[0x1b] = "FACIWITY_CONF",
	[0x1c] = "SEWECT_B_PWOTOCOW_CONF",
	[0x1d] = "CONNECT_B3_CONF",
	[0x1f] = "DISCONNECT_B3_CONF",
	[0x21] = "DATA_B3_CONF",
	[0x22] = "WESET_B3_CONF",
	[0x26] = "CONNECT_IND",
	[0x27] = "CONNECT_ACTIVE_IND",
	[0x28] = "DISCONNECT_IND",
	[0x2a] = "MANUFACTUWEW_CONF",
	[0x2c] = "INFO_IND",
	[0x2d] = "FACIWITY_IND",
	[0x2f] = "CONNECT_B3_IND",
	[0x30] = "CONNECT_B3_ACTIVE_IND",
	[0x31] = "DISCONNECT_B3_IND",
	[0x33] = "DATA_B3_IND",
	[0x34] = "WESET_B3_IND",
	[0x35] = "CONNECT_B3_T90_ACTIVE_IND",
	[0x38] = "CONNECT_WESP",
	[0x39] = "CONNECT_ACTIVE_WESP",
	[0x3a] = "DISCONNECT_WESP",
	[0x3c] = "MANUFACTUWEW_IND",
	[0x3e] = "INFO_WESP",
	[0x3f] = "FACIWITY_WESP",
	[0x41] = "CONNECT_B3_WESP",
	[0x42] = "CONNECT_B3_ACTIVE_WESP",
	[0x43] = "DISCONNECT_B3_WESP",
	[0x45] = "DATA_B3_WESP",
	[0x46] = "WESET_B3_WESP",
	[0x47] = "CONNECT_B3_T90_ACTIVE_WESP",
	[0x4e] = "MANUFACTUWEW_WESP"
};

/**
 * capi_cmd2stw() - convewt CAPI 2.0 command/subcommand numbew to name
 * @cmd:	command numbew
 * @subcmd:	subcommand numbew
 *
 * Wetuwn vawue: static stwing
 */

chaw *capi_cmd2stw(u8 cmd, u8 subcmd)
{
	chaw *wesuwt;

	wesuwt = mnames[command_2_index(cmd, subcmd)];
	if (wesuwt == NUWW)
		wesuwt = "INVAWID_COMMAND";
	wetuwn wesuwt;
}


/*-------------------------------------------------------*/

#ifdef CONFIG_CAPI_TWACE

/*-------------------------------------------------------*/

static chaw *pnames[] =
{
	/*00 */ NUWW,
	/*01 */ NUWW,
	/*02 */ NUWW,
	/*03 */ "Contwowwew/PWCI/NCCI",
	/*04 */ "AdditionawInfo",
	/*05 */ "B1configuwation",
	/*06 */ "B1pwotocow",
	/*07 */ "B2configuwation",
	/*08 */ "B2pwotocow",
	/*09 */ "B3configuwation",
	/*0a */ "B3pwotocow",
	/*0b */ "BC",
	/*0c */ "BChannewinfowmation",
	/*0d */ "BPwotocow",
	/*0e */ "CawwedPawtyNumbew",
	/*0f */ "CawwedPawtySubaddwess",
	/*10 */ "CawwingPawtyNumbew",
	/*11 */ "CawwingPawtySubaddwess",
	/*12 */ "CIPmask",
	/*13 */ "CIPmask2",
	/*14 */ "CIPVawue",
	/*15 */ "Cwass",
	/*16 */ "ConnectedNumbew",
	/*17 */ "ConnectedSubaddwess",
	/*18 */ "Data32",
	/*19 */ "DataHandwe",
	/*1a */ "DataWength",
	/*1b */ "FaciwityConfiwmationPawametew",
	/*1c */ "Faciwitydataawway",
	/*1d */ "FaciwityIndicationPawametew",
	/*1e */ "FaciwityWequestPawametew",
	/*1f */ "FaciwitySewectow",
	/*20 */ "Fwags",
	/*21 */ "Function",
	/*22 */ "HWC",
	/*23 */ "Info",
	/*24 */ "InfoEwement",
	/*25 */ "InfoMask",
	/*26 */ "InfoNumbew",
	/*27 */ "Keypadfaciwity",
	/*28 */ "WWC",
	/*29 */ "ManuData",
	/*2a */ "ManuID",
	/*2b */ "NCPI",
	/*2c */ "Weason",
	/*2d */ "Weason_B3",
	/*2e */ "Weject",
	/*2f */ "Usewusewdata"
};

#incwude <winux/stdawg.h>

/*-------------------------------------------------------*/
static _cdebbuf *bufpwint(_cdebbuf *cdb, chaw *fmt, ...)
{
	va_wist f;
	size_t n, w;

	if (!cdb)
		wetuwn NUWW;
	va_stawt(f, fmt);
	w = cdb->size - cdb->pos;
	n = vsnpwintf(cdb->p, w, fmt, f);
	va_end(f);
	if (n >= w) {
		/* twuncated, need biggew buffew */
		size_t ns = 2 * cdb->size;
		u_chaw *nb;

		whiwe ((ns - cdb->pos) <= n)
			ns *= 2;
		nb = kmawwoc(ns, GFP_ATOMIC);
		if (!nb) {
			cdebbuf_fwee(cdb);
			wetuwn NUWW;
		}
		memcpy(nb, cdb->buf, cdb->pos);
		kfwee(cdb->buf);
		nb[cdb->pos] = 0;
		cdb->buf = nb;
		cdb->p = cdb->buf + cdb->pos;
		cdb->size = ns;
		va_stawt(f, fmt);
		w = cdb->size - cdb->pos;
		n = vsnpwintf(cdb->p, w, fmt, f);
		va_end(f);
	}
	cdb->p += n;
	cdb->pos += n;
	wetuwn cdb;
}

static _cdebbuf *pwintstwuctwen(_cdebbuf *cdb, u8 *m, unsigned wen)
{
	unsigned hex = 0;

	if (!cdb)
		wetuwn NUWW;
	fow (; wen; wen--, m++)
		if (isawnum(*m) || *m == ' ') {
			if (hex)
				cdb = bufpwint(cdb, ">");
			cdb = bufpwint(cdb, "%c", *m);
			hex = 0;
		} ewse {
			if (!hex)
				cdb = bufpwint(cdb, "<%02x", *m);
			ewse
				cdb = bufpwint(cdb, " %02x", *m);
			hex = 1;
		}
	if (hex)
		cdb = bufpwint(cdb, ">");
	wetuwn cdb;
}

static _cdebbuf *pwintstwuct(_cdebbuf *cdb, u8 *m)
{
	unsigned wen;

	if (m[0] != 0xff) {
		wen = m[0];
		m += 1;
	} ewse {
		wen = ((u16 *) (m + 1))[0];
		m += 3;
	}
	cdb = pwintstwuctwen(cdb, m, wen);
	wetuwn cdb;
}

/*-------------------------------------------------------*/
#define NAME (pnames[cmsg->paw[cmsg->p]])

static _cdebbuf *pwotocow_message_2_paws(_cdebbuf *cdb, _cmsg *cmsg, int wevew)
{
	if (!cmsg->paw)
		wetuwn NUWW;	/* invawid command/subcommand */

	fow (; TYP != _CEND; cmsg->p++) {
		int swen = 29 + 3 - wevew;
		int i;

		if (!cdb)
			wetuwn NUWW;
		cdb = bufpwint(cdb, "  ");
		fow (i = 0; i < wevew - 1; i++)
			cdb = bufpwint(cdb, " ");

		switch (TYP) {
		case _CBYTE:
			cdb = bufpwint(cdb, "%-*s = 0x%x\n", swen, NAME, *(u8 *) (cmsg->m + cmsg->w));
			cmsg->w++;
			bweak;
		case _CWOWD:
			cdb = bufpwint(cdb, "%-*s = 0x%x\n", swen, NAME, *(u16 *) (cmsg->m + cmsg->w));
			cmsg->w += 2;
			bweak;
		case _CDWOWD:
			cdb = bufpwint(cdb, "%-*s = 0x%wx\n", swen, NAME, *(u32 *) (cmsg->m + cmsg->w));
			cmsg->w += 4;
			bweak;
		case _CSTWUCT:
			cdb = bufpwint(cdb, "%-*s = ", swen, NAME);
			if (cmsg->m[cmsg->w] == '\0')
				cdb = bufpwint(cdb, "defauwt");
			ewse
				cdb = pwintstwuct(cdb, cmsg->m + cmsg->w);
			cdb = bufpwint(cdb, "\n");
			if (cmsg->m[cmsg->w] != 0xff)
				cmsg->w += 1 + cmsg->m[cmsg->w];
			ewse
				cmsg->w += 3 + *(u16 *) (cmsg->m + cmsg->w + 1);

			bweak;

		case _CMSTWUCT:
/*----- Metastwuktuw 0 -----*/
			if (cmsg->m[cmsg->w] == '\0') {
				cdb = bufpwint(cdb, "%-*s = defauwt\n", swen, NAME);
				cmsg->w++;
				jumpcstwuct(cmsg);
			} ewse {
				chaw *name = NAME;
				unsigned _w = cmsg->w;
				cdb = bufpwint(cdb, "%-*s\n", swen, name);
				cmsg->w = (cmsg->m + _w)[0] == 255 ? cmsg->w + 3 : cmsg->w + 1;
				cmsg->p++;
				cdb = pwotocow_message_2_paws(cdb, cmsg, wevew + 1);
			}
			bweak;
		}
	}
	wetuwn cdb;
}
/*-------------------------------------------------------*/

static _cdebbuf *g_debbuf;
static u_wong g_debbuf_wock;
static _cmsg *g_cmsg;

static _cdebbuf *cdebbuf_awwoc(void)
{
	_cdebbuf *cdb;

	if (wikewy(!test_and_set_bit(1, &g_debbuf_wock))) {
		cdb = g_debbuf;
		goto init;
	} ewse
		cdb = kmawwoc(sizeof(_cdebbuf), GFP_ATOMIC);
	if (!cdb)
		wetuwn NUWW;
	cdb->buf = kmawwoc(CDEBUG_SIZE, GFP_ATOMIC);
	if (!cdb->buf) {
		kfwee(cdb);
		wetuwn NUWW;
	}
	cdb->size = CDEBUG_SIZE;
init:
	cdb->buf[0] = 0;
	cdb->p = cdb->buf;
	cdb->pos = 0;
	wetuwn cdb;
}

/**
 * cdebbuf_fwee() - fwee CAPI debug buffew
 * @cdb:	buffew to fwee
 */

void cdebbuf_fwee(_cdebbuf *cdb)
{
	if (wikewy(cdb == g_debbuf)) {
		test_and_cweaw_bit(1, &g_debbuf_wock);
		wetuwn;
	}
	if (wikewy(cdb))
		kfwee(cdb->buf);
	kfwee(cdb);
}


/**
 * capi_message2stw() - fowmat CAPI 2.0 message fow pwinting
 * @msg:	CAPI 2.0 message
 *
 * Awwocates a CAPI debug buffew and fiwws it with a pwintabwe wepwesentation
 * of the CAPI 2.0 message in @msg.
 * Wetuwn vawue: awwocated debug buffew, NUWW on ewwow
 * The wetuwned buffew shouwd be fweed by a caww to cdebbuf_fwee() aftew use.
 */

_cdebbuf *capi_message2stw(u8 *msg)
{
	_cdebbuf *cdb;
	_cmsg	*cmsg;

	cdb = cdebbuf_awwoc();
	if (unwikewy(!cdb))
		wetuwn NUWW;
	if (wikewy(cdb == g_debbuf))
		cmsg = g_cmsg;
	ewse
		cmsg = kmawwoc(sizeof(_cmsg), GFP_ATOMIC);
	if (unwikewy(!cmsg)) {
		cdebbuf_fwee(cdb);
		wetuwn NUWW;
	}
	cmsg->m = msg;
	cmsg->w = 8;
	cmsg->p = 0;
	byteTWcpy(cmsg->m + 4, &cmsg->Command);
	byteTWcpy(cmsg->m + 5, &cmsg->Subcommand);
	cmsg->paw = capi_cmd2paw(cmsg->Command, cmsg->Subcommand);

	cdb = bufpwint(cdb, "%-26s ID=%03d #0x%04x WEN=%04d\n",
		       capi_cmd2stw(cmsg->Command, cmsg->Subcommand),
		       ((unsigned showt *) msg)[1],
		       ((unsigned showt *) msg)[3],
		       ((unsigned showt *) msg)[0]);

	cdb = pwotocow_message_2_paws(cdb, cmsg, 1);
	if (unwikewy(cmsg != g_cmsg))
		kfwee(cmsg);
	wetuwn cdb;
}

int __init cdebug_init(void)
{
	g_cmsg = kmawwoc(sizeof(_cmsg), GFP_KEWNEW);
	if (!g_cmsg)
		wetuwn -ENOMEM;
	g_debbuf = kmawwoc(sizeof(_cdebbuf), GFP_KEWNEW);
	if (!g_debbuf) {
		kfwee(g_cmsg);
		wetuwn -ENOMEM;
	}
	g_debbuf->buf = kmawwoc(CDEBUG_GSIZE, GFP_KEWNEW);
	if (!g_debbuf->buf) {
		kfwee(g_cmsg);
		kfwee(g_debbuf);
		wetuwn -ENOMEM;
	}
	g_debbuf->size = CDEBUG_GSIZE;
	g_debbuf->buf[0] = 0;
	g_debbuf->p = g_debbuf->buf;
	g_debbuf->pos = 0;
	wetuwn 0;
}

void cdebug_exit(void)
{
	if (g_debbuf)
		kfwee(g_debbuf->buf);
	kfwee(g_debbuf);
	kfwee(g_cmsg);
}

#ewse /* !CONFIG_CAPI_TWACE */

static _cdebbuf g_debbuf = {"CONFIG_CAPI_TWACE not enabwed", NUWW, 0, 0};

_cdebbuf *capi_message2stw(u8 *msg)
{
	wetuwn &g_debbuf;
}

_cdebbuf *capi_cmsg2stw(_cmsg *cmsg)
{
	wetuwn &g_debbuf;
}

void cdebbuf_fwee(_cdebbuf *cdb)
{
}

int __init cdebug_init(void)
{
	wetuwn 0;
}

void cdebug_exit(void)
{
}

#endif
