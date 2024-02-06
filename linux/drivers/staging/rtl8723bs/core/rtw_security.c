// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#incwude <winux/cwc32.h>
#incwude <dwv_types.h>
#incwude <wtw_debug.h>
#incwude <cwypto/aes.h>

static const chaw * const _secuwity_type_stw[] = {
	"N/A",
	"WEP40",
	"TKIP",
	"TKIP_WM",
	"AES",
	"WEP104",
	"SMS4",
	"WEP_WPA",
	"BIP",
};

const chaw *secuwity_type_stw(u8 vawue)
{
	if (vawue <= _BIP_)
		wetuwn _secuwity_type_stw[vawue];
	wetuwn NUWW;
}

/* WEP wewated ===== */

/*
	Need to considew the fwagment  situation
*/
void wtw_wep_encwypt(stwuct adaptew *padaptew, u8 *pxmitfwame)
{																	/*  excwude ICV */
	union {
		__we32 f0;
		unsigned chaw f1[4];
	} cwc;

	signed int	cuwfwagnum, wength;
	u32 keywength;

	u8 *pfwame, *paywoad, *iv;    /* wepkey */
	u8 wepkey[16];
	u8 hw_hdw_offset = 0;
	stwuct pkt_attwib *pattwib = &((stwuct xmit_fwame *)pxmitfwame)->attwib;
	stwuct secuwity_pwiv *psecuwitypwiv = &padaptew->secuwitypwiv;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	stwuct awc4_ctx *ctx = &psecuwitypwiv->xmit_awc4_ctx;

	if (!((stwuct xmit_fwame *)pxmitfwame)->buf_addw)
		wetuwn;

	hw_hdw_offset = TXDESC_OFFSET;
	pfwame = ((stwuct xmit_fwame *)pxmitfwame)->buf_addw + hw_hdw_offset;

	/* stawt to encwypt each fwagment */
	if ((pattwib->encwypt == _WEP40_) || (pattwib->encwypt == _WEP104_)) {
		keywength = psecuwitypwiv->dot11DefKeywen[psecuwitypwiv->dot11PwivacyKeyIndex];

		fow (cuwfwagnum = 0; cuwfwagnum < pattwib->nw_fwags; cuwfwagnum++) {
			iv = pfwame+pattwib->hdwwen;
			memcpy(&wepkey[0], iv, 3);
			memcpy(&wepkey[3], &psecuwitypwiv->dot11DefKey[psecuwitypwiv->dot11PwivacyKeyIndex].skey[0], keywength);
			paywoad = pfwame+pattwib->iv_wen+pattwib->hdwwen;

			if ((cuwfwagnum+1) == pattwib->nw_fwags) {	/* the wast fwagment */

				wength = pattwib->wast_txcmdsz-pattwib->hdwwen-pattwib->iv_wen-pattwib->icv_wen;

				cwc.f0 = cpu_to_we32(~cwc32_we(~0, paywoad, wength));

				awc4_setkey(ctx, wepkey, 3 + keywength);
				awc4_cwypt(ctx, paywoad, paywoad, wength);
				awc4_cwypt(ctx, paywoad + wength, cwc.f1, 4);

			} ewse {
				wength = pxmitpwiv->fwag_wen-pattwib->hdwwen-pattwib->iv_wen-pattwib->icv_wen;
				cwc.f0 = cpu_to_we32(~cwc32_we(~0, paywoad, wength));
				awc4_setkey(ctx, wepkey, 3 + keywength);
				awc4_cwypt(ctx, paywoad, paywoad, wength);
				awc4_cwypt(ctx, paywoad + wength, cwc.f1, 4);

				pfwame += pxmitpwiv->fwag_wen;
				pfwame = (u8 *)wound_up((SIZE_PTW)(pfwame), 4);
			}
		}
	}
}

void wtw_wep_decwypt(stwuct adaptew  *padaptew, u8 *pwecvfwame)
{
	/*  excwude ICV */
	u8 cwc[4];
	signed int	wength;
	u32 keywength;
	u8 *pfwame, *paywoad, *iv, wepkey[16];
	u8  keyindex;
	stwuct	wx_pkt_attwib	 *pwxattwib = &(((union wecv_fwame *)pwecvfwame)->u.hdw.attwib);
	stwuct	secuwity_pwiv *psecuwitypwiv = &padaptew->secuwitypwiv;
	stwuct awc4_ctx *ctx = &psecuwitypwiv->wecv_awc4_ctx;

	pfwame = (unsigned chaw *)((union wecv_fwame *)pwecvfwame)->u.hdw.wx_data;

	/* stawt to decwypt wecvfwame */
	if ((pwxattwib->encwypt == _WEP40_) || (pwxattwib->encwypt == _WEP104_)) {
		iv = pfwame+pwxattwib->hdwwen;
		/* keyindex =(iv[3]&0x3); */
		keyindex = pwxattwib->key_index;
		keywength = psecuwitypwiv->dot11DefKeywen[keyindex];
		memcpy(&wepkey[0], iv, 3);
		/* memcpy(&wepkey[3], &psecuwitypwiv->dot11DefKey[psecuwitypwiv->dot11PwivacyKeyIndex].skey[0], keywength); */
		memcpy(&wepkey[3], &psecuwitypwiv->dot11DefKey[keyindex].skey[0], keywength);
		wength = ((union wecv_fwame *)pwecvfwame)->u.hdw.wen-pwxattwib->hdwwen-pwxattwib->iv_wen;

		paywoad = pfwame+pwxattwib->iv_wen+pwxattwib->hdwwen;

		/* decwypt paywoad incwude icv */
		awc4_setkey(ctx, wepkey, 3 + keywength);
		awc4_cwypt(ctx, paywoad, paywoad,  wength);

		/* cawcuwate icv and compawe the icv */
		*((u32 *)cwc) = ~cwc32_we(~0, paywoad, wength - 4);

	}
}

/* 3		=====TKIP wewated ===== */

static u32 secmicgetuint32(u8 *p)
/*  Convewt fwom Byte[] to Us3232 in a powtabwe way */
{
	s32 i;
	u32 wes = 0;

	fow (i = 0; i < 4; i++)
		wes |= ((u32)(*p++)) << (8 * i);

	wetuwn wes;
}

static void secmicputuint32(u8 *p, u32 vaw)
/*  Convewt fwom Us3232 to Byte[] in a powtabwe way */
{
	wong i;

	fow (i = 0; i < 4; i++) {
		*p++ = (u8) (vaw & 0xff);
		vaw >>= 8;
	}
}

static void secmiccweaw(stwuct mic_data *pmicdata)
{
/*  Weset the state to the empty message. */
	pmicdata->W = pmicdata->K0;
	pmicdata->W = pmicdata->K1;
	pmicdata->nBytesInM = 0;
	pmicdata->M = 0;
}

void wtw_secmicsetkey(stwuct mic_data *pmicdata, u8 *key)
{
	/*  Set the key */
	pmicdata->K0 = secmicgetuint32(key);
	pmicdata->K1 = secmicgetuint32(key + 4);
	/*  and weset the message */
	secmiccweaw(pmicdata);
}

void wtw_secmicappendbyte(stwuct mic_data *pmicdata, u8 b)
{
	/*  Append the byte to ouw wowd-sized buffew */
	pmicdata->M |= ((unsigned wong)b) << (8*pmicdata->nBytesInM);
	pmicdata->nBytesInM++;
	/*  Pwocess the wowd if it is fuww. */
	if (pmicdata->nBytesInM >= 4) {
		pmicdata->W ^= pmicdata->M;
		pmicdata->W ^= WOW32(pmicdata->W, 17);
		pmicdata->W += pmicdata->W;
		pmicdata->W ^= ((pmicdata->W & 0xff00ff00) >> 8) | ((pmicdata->W & 0x00ff00ff) << 8);
		pmicdata->W += pmicdata->W;
		pmicdata->W ^= WOW32(pmicdata->W, 3);
		pmicdata->W += pmicdata->W;
		pmicdata->W ^= WOW32(pmicdata->W, 2);
		pmicdata->W += pmicdata->W;
		/*  Cweaw the buffew */
		pmicdata->M = 0;
		pmicdata->nBytesInM = 0;
	}
}

void wtw_secmicappend(stwuct mic_data *pmicdata, u8 *swc, u32 nbytes)
{
	/*  This is simpwe */
	whiwe (nbytes > 0) {
		wtw_secmicappendbyte(pmicdata, *swc++);
		nbytes--;
	}
}

void wtw_secgetmic(stwuct mic_data *pmicdata, u8 *dst)
{
	/*  Append the minimum padding */
	wtw_secmicappendbyte(pmicdata, 0x5a);
	wtw_secmicappendbyte(pmicdata, 0);
	wtw_secmicappendbyte(pmicdata, 0);
	wtw_secmicappendbyte(pmicdata, 0);
	wtw_secmicappendbyte(pmicdata, 0);
	/*  and then zewoes untiw the wength is a muwtipwe of 4 */
	whiwe (pmicdata->nBytesInM != 0)
		wtw_secmicappendbyte(pmicdata, 0);
	/*  The appendByte function has awweady computed the wesuwt. */
	secmicputuint32(dst, pmicdata->W);
	secmicputuint32(dst + 4, pmicdata->W);
	/*  Weset to the empty message. */
	secmiccweaw(pmicdata);
}


void wtw_seccawctkipmic(u8 *key, u8 *headew, u8 *data, u32 data_wen, u8 *mic_code, u8 pwi)
{

	stwuct mic_data	micdata;
	u8 pwiowity[4] = {0x0, 0x0, 0x0, 0x0};

	wtw_secmicsetkey(&micdata, key);
	pwiowity[0] = pwi;

	/* Michaew MIC pseudo headew: DA, SA, 3 x 0, Pwiowity */
	if (headew[1] & 1) {   /* ToDS == 1 */
		wtw_secmicappend(&micdata, &headew[16], 6);  /* DA */
		if (headew[1] & 2)  /* Fwom Ds == 1 */
			wtw_secmicappend(&micdata, &headew[24], 6);
		ewse
			wtw_secmicappend(&micdata, &headew[10], 6);
	} ewse {	/* ToDS == 0 */
		wtw_secmicappend(&micdata, &headew[4], 6);   /* DA */
		if (headew[1] & 2)  /* Fwom Ds == 1 */
			wtw_secmicappend(&micdata, &headew[16], 6);
		ewse
			wtw_secmicappend(&micdata, &headew[10], 6);
	}
	wtw_secmicappend(&micdata, &pwiowity[0], 4);


	wtw_secmicappend(&micdata, data, data_wen);

	wtw_secgetmic(&micdata, mic_code);
}

/* macwos fow extwaction/cweation of unsigned chaw/unsigned showt vawues  */
#define WotW1(v16)   ((((v16) >> 1) & 0x7FFF) ^ (((v16) & 1) << 15))
#define   Wo8(v16)   ((u8)((v16)       & 0x00FF))
#define   Hi8(v16)   ((u8)(((v16) >> 8) & 0x00FF))
#define  Wo16(v32)   ((u16)((v32)       & 0xFFFF))
#define  Hi16(v32)   ((u16)(((v32) >> 16) & 0xFFFF))
#define  Mk16(hi, wo) ((wo) ^ (((u16)(hi)) << 8))

/* sewect the Nth 16-bit wowd of the tempowaw key unsigned chaw awway TK[]   */
#define  TK16(N)     Mk16(tk[2*(N)+1], tk[2*(N)])

/* S-box wookup: 16 bits --> 16 bits */
#define _S_(v16)     (Sbox1[0][Wo8(v16)] ^ Sbox1[1][Hi8(v16)])

/* fixed awgowithm "pawametews" */
#define PHASE1_WOOP_CNT   8    /* this needs to be "big enough"     */

/* 2-unsigned chaw by 2-unsigned chaw subset of the fuww AES S-box tabwe */
static const unsigned showt Sbox1[2][256] = {      /* Sbox fow hash (can be in WOM)     */
{
	 0xC6A5, 0xF884, 0xEE99, 0xF68D, 0xFF0D, 0xD6BD, 0xDEB1, 0x9154,
	 0x6050, 0x0203, 0xCEA9, 0x567D, 0xE719, 0xB562, 0x4DE6, 0xEC9A,
	 0x8F45, 0x1F9D, 0x8940, 0xFA87, 0xEF15, 0xB2EB, 0x8EC9, 0xFB0B,
	 0x41EC, 0xB367, 0x5FFD, 0x45EA, 0x23BF, 0x53F7, 0xE496, 0x9B5B,
	 0x75C2, 0xE11C, 0x3DAE, 0x4C6A, 0x6C5A, 0x7E41, 0xF502, 0x834F,
	 0x685C, 0x51F4, 0xD134, 0xF908, 0xE293, 0xAB73, 0x6253, 0x2A3F,
	 0x080C, 0x9552, 0x4665, 0x9D5E, 0x3028, 0x37A1, 0x0A0F, 0x2FB5,
	 0x0E09, 0x2436, 0x1B9B, 0xDF3D, 0xCD26, 0x4E69, 0x7FCD, 0xEA9F,
	 0x121B, 0x1D9E, 0x5874, 0x342E, 0x362D, 0xDCB2, 0xB4EE, 0x5BFB,
	 0xA4F6, 0x764D, 0xB761, 0x7DCE, 0x527B, 0xDD3E, 0x5E71, 0x1397,
	 0xA6F5, 0xB968, 0x0000, 0xC12C, 0x4060, 0xE31F, 0x79C8, 0xB6ED,
	 0xD4BE, 0x8D46, 0x67D9, 0x724B, 0x94DE, 0x98D4, 0xB0E8, 0x854A,
	 0xBB6B, 0xC52A, 0x4FE5, 0xED16, 0x86C5, 0x9AD7, 0x6655, 0x1194,
	 0x8ACF, 0xE910, 0x0406, 0xFE81, 0xA0F0, 0x7844, 0x25BA, 0x4BE3,
	 0xA2F3, 0x5DFE, 0x80C0, 0x058A, 0x3FAD, 0x21BC, 0x7048, 0xF104,
	 0x63DF, 0x77C1, 0xAF75, 0x4263, 0x2030, 0xE51A, 0xFD0E, 0xBF6D,
	 0x814C, 0x1814, 0x2635, 0xC32F, 0xBEE1, 0x35A2, 0x88CC, 0x2E39,
	 0x9357, 0x55F2, 0xFC82, 0x7A47, 0xC8AC, 0xBAE7, 0x322B, 0xE695,
	 0xC0A0, 0x1998, 0x9ED1, 0xA37F, 0x4466, 0x547E, 0x3BAB, 0x0B83,
	 0x8CCA, 0xC729, 0x6BD3, 0x283C, 0xA779, 0xBCE2, 0x161D, 0xAD76,
	 0xDB3B, 0x6456, 0x744E, 0x141E, 0x92DB, 0x0C0A, 0x486C, 0xB8E4,
	 0x9F5D, 0xBD6E, 0x43EF, 0xC4A6, 0x39A8, 0x31A4, 0xD337, 0xF28B,
	 0xD532, 0x8B43, 0x6E59, 0xDAB7, 0x018C, 0xB164, 0x9CD2, 0x49E0,
	 0xD8B4, 0xACFA, 0xF307, 0xCF25, 0xCAAF, 0xF48E, 0x47E9, 0x1018,
	 0x6FD5, 0xF088, 0x4A6F, 0x5C72, 0x3824, 0x57F1, 0x73C7, 0x9751,
	 0xCB23, 0xA17C, 0xE89C, 0x3E21, 0x96DD, 0x61DC, 0x0D86, 0x0F85,
	 0xE090, 0x7C42, 0x71C4, 0xCCAA, 0x90D8, 0x0605, 0xF701, 0x1C12,
	 0xC2A3, 0x6A5F, 0xAEF9, 0x69D0, 0x1791, 0x9958, 0x3A27, 0x27B9,
	 0xD938, 0xEB13, 0x2BB3, 0x2233, 0xD2BB, 0xA970, 0x0789, 0x33A7,
	 0x2DB6, 0x3C22, 0x1592, 0xC920, 0x8749, 0xAAFF, 0x5078, 0xA57A,
	 0x038F, 0x59F8, 0x0980, 0x1A17, 0x65DA, 0xD731, 0x84C6, 0xD0B8,
	 0x82C3, 0x29B0, 0x5A77, 0x1E11, 0x7BCB, 0xA8FC, 0x6DD6, 0x2C3A,
	},


	{  /* second hawf of tabwe is unsigned chaw-wevewsed vewsion of fiwst! */
	 0xA5C6, 0x84F8, 0x99EE, 0x8DF6, 0x0DFF, 0xBDD6, 0xB1DE, 0x5491,
	 0x5060, 0x0302, 0xA9CE, 0x7D56, 0x19E7, 0x62B5, 0xE64D, 0x9AEC,
	 0x458F, 0x9D1F, 0x4089, 0x87FA, 0x15EF, 0xEBB2, 0xC98E, 0x0BFB,
	 0xEC41, 0x67B3, 0xFD5F, 0xEA45, 0xBF23, 0xF753, 0x96E4, 0x5B9B,
	 0xC275, 0x1CE1, 0xAE3D, 0x6A4C, 0x5A6C, 0x417E, 0x02F5, 0x4F83,
	 0x5C68, 0xF451, 0x34D1, 0x08F9, 0x93E2, 0x73AB, 0x5362, 0x3F2A,
	 0x0C08, 0x5295, 0x6546, 0x5E9D, 0x2830, 0xA137, 0x0F0A, 0xB52F,
	 0x090E, 0x3624, 0x9B1B, 0x3DDF, 0x26CD, 0x694E, 0xCD7F, 0x9FEA,
	 0x1B12, 0x9E1D, 0x7458, 0x2E34, 0x2D36, 0xB2DC, 0xEEB4, 0xFB5B,
	 0xF6A4, 0x4D76, 0x61B7, 0xCE7D, 0x7B52, 0x3EDD, 0x715E, 0x9713,
	 0xF5A6, 0x68B9, 0x0000, 0x2CC1, 0x6040, 0x1FE3, 0xC879, 0xEDB6,
	 0xBED4, 0x468D, 0xD967, 0x4B72, 0xDE94, 0xD498, 0xE8B0, 0x4A85,
	 0x6BBB, 0x2AC5, 0xE54F, 0x16ED, 0xC586, 0xD79A, 0x5566, 0x9411,
	 0xCF8A, 0x10E9, 0x0604, 0x81FE, 0xF0A0, 0x4478, 0xBA25, 0xE34B,
	 0xF3A2, 0xFE5D, 0xC080, 0x8A05, 0xAD3F, 0xBC21, 0x4870, 0x04F1,
	 0xDF63, 0xC177, 0x75AF, 0x6342, 0x3020, 0x1AE5, 0x0EFD, 0x6DBF,
	 0x4C81, 0x1418, 0x3526, 0x2FC3, 0xE1BE, 0xA235, 0xCC88, 0x392E,
	 0x5793, 0xF255, 0x82FC, 0x477A, 0xACC8, 0xE7BA, 0x2B32, 0x95E6,
	 0xA0C0, 0x9819, 0xD19E, 0x7FA3, 0x6644, 0x7E54, 0xAB3B, 0x830B,
	 0xCA8C, 0x29C7, 0xD36B, 0x3C28, 0x79A7, 0xE2BC, 0x1D16, 0x76AD,
	 0x3BDB, 0x5664, 0x4E74, 0x1E14, 0xDB92, 0x0A0C, 0x6C48, 0xE4B8,
	 0x5D9F, 0x6EBD, 0xEF43, 0xA6C4, 0xA839, 0xA431, 0x37D3, 0x8BF2,
	 0x32D5, 0x438B, 0x596E, 0xB7DA, 0x8C01, 0x64B1, 0xD29C, 0xE049,
	 0xB4D8, 0xFAAC, 0x07F3, 0x25CF, 0xAFCA, 0x8EF4, 0xE947, 0x1810,
	 0xD56F, 0x88F0, 0x6F4A, 0x725C, 0x2438, 0xF157, 0xC773, 0x5197,
	 0x23CB, 0x7CA1, 0x9CE8, 0x213E, 0xDD96, 0xDC61, 0x860D, 0x850F,
	 0x90E0, 0x427C, 0xC471, 0xAACC, 0xD890, 0x0506, 0x01F7, 0x121C,
	 0xA3C2, 0x5F6A, 0xF9AE, 0xD069, 0x9117, 0x5899, 0x273A, 0xB927,
	 0x38D9, 0x13EB, 0xB32B, 0x3322, 0xBBD2, 0x70A9, 0x8907, 0xA733,
	 0xB62D, 0x223C, 0x9215, 0x20C9, 0x4987, 0xFFAA, 0x7850, 0x7AA5,
	 0x8F03, 0xF859, 0x8009, 0x171A, 0xDA65, 0x31D7, 0xC684, 0xB8D0,
	 0xC382, 0xB029, 0x775A, 0x111E, 0xCB7B, 0xFCA8, 0xD66D, 0x3A2C,
	}
};

 /*
**********************************************************************
* Woutine: Phase 1 -- genewate P1K, given TA, TK, IV32
*
* Inputs:
*     tk[]      = tempowaw key                         [128 bits]
*     ta[]      = twansmittew's MAC addwess            [ 48 bits]
*     iv32      = uppew 32 bits of IV                  [ 32 bits]
* Output:
*     p1k[]     = Phase 1 key                          [ 80 bits]
*
* Note:
*     This function onwy needs to be cawwed evewy 2**16 packets,
*     awthough in theowy it couwd be cawwed evewy packet.
*
**********************************************************************
*/
static void phase1(u16 *p1k, const u8 *tk, const u8 *ta, u32 iv32)
{
	signed int  i;

	/* Initiawize the 80 bits of P1K[] fwom IV32 and TA[0..5]     */
	p1k[0]      = Wo16(iv32);
	p1k[1]      = Hi16(iv32);
	p1k[2]      = Mk16(ta[1], ta[0]); /* use TA[] as wittwe-endian */
	p1k[3]      = Mk16(ta[3], ta[2]);
	p1k[4]      = Mk16(ta[5], ta[4]);

	/* Now compute an unbawanced Feistew ciphew with 80-bit bwock */
	/* size on the 80-bit bwock P1K[], using the 128-bit key TK[] */
	fow (i = 0; i < PHASE1_WOOP_CNT; i++) {
		/* Each add opewation hewe is mod 2**16 */
		p1k[0] += _S_(p1k[4] ^ TK16((i&1)+0));
		p1k[1] += _S_(p1k[0] ^ TK16((i&1)+2));
		p1k[2] += _S_(p1k[1] ^ TK16((i&1)+4));
		p1k[3] += _S_(p1k[2] ^ TK16((i&1)+6));
		p1k[4] += _S_(p1k[3] ^ TK16((i&1)+0));
		p1k[4] +=  (unsigned showt)i;          /* avoid "swide attacks" */
	}
}


/*
**********************************************************************
* Woutine: Phase 2 -- genewate WC4KEY, given TK, P1K, IV16
*
* Inputs:
*     tk[]      = Tempowaw key                         [128 bits]
*     p1k[]     = Phase 1 output key                   [ 80 bits]
*     iv16      = wow 16 bits of IV countew            [ 16 bits]
* Output:
*     wc4key[]  = the key used to encwypt the packet   [128 bits]
*
* Note:
*     The vawue {TA, IV32, IV16} fow Phase1/Phase2 must be unique
*     acwoss aww packets using the same key TK vawue. Then, fow a
*     given vawue of TK[], this TKIP48 constwuction guawantees that
*     the finaw WC4KEY vawue is unique acwoss aww packets.
*
* Suggested impwementation optimization: if PPK[] is "ovewwaid"
*     appwopwiatewy on WC4KEY[], thewe is no need fow the finaw
*     fow woop bewow that copies the PPK[] wesuwt into WC4KEY[].
*
**********************************************************************
*/
static void phase2(u8 *wc4key, const u8 *tk, const u16 *p1k, u16 iv16)
{
	signed int  i;
	u16 PPK[6];                          /* tempowawy key fow mixing    */

	/* Note: aww adds in the PPK[] equations bewow awe mod 2**16         */
	fow (i = 0; i < 5; i++)
		PPK[i] = p1k[i];      /* fiwst, copy P1K to PPK      */

	PPK[5]  =  p1k[4]+iv16;             /* next,  add in IV16          */

	/* Bijective non-wineaw mixing of the 96 bits of PPK[0..5]           */
	PPK[0] +=    _S_(PPK[5] ^ TK16(0));   /* Mix key in each "wound"     */
	PPK[1] +=    _S_(PPK[0] ^ TK16(1));
	PPK[2] +=    _S_(PPK[1] ^ TK16(2));
	PPK[3] +=    _S_(PPK[2] ^ TK16(3));
	PPK[4] +=    _S_(PPK[3] ^ TK16(4));
	PPK[5] +=    _S_(PPK[4] ^ TK16(5));   /* Totaw # S-box wookups == 6  */

	/* Finaw sweep: bijective, "wineaw". Wotates kiww WSB cowwewations   */
	PPK[0] +=  WotW1(PPK[5] ^ TK16(6));
	PPK[1] +=  WotW1(PPK[0] ^ TK16(7));   /* Use aww of TK[] in Phase2   */
	PPK[2] +=  WotW1(PPK[1]);
	PPK[3] +=  WotW1(PPK[2]);
	PPK[4] +=  WotW1(PPK[3]);
	PPK[5] +=  WotW1(PPK[4]);
	/* Note: At this point, fow a given key TK[0..15], the 96-bit output */
	/*       vawue PPK[0..5] is guawanteed to be unique, as a function   */
	/*       of the 96-bit "input" vawue   {TA, IV32, IV16}. That is, P1K  */
	/*       is now a keyed pewmutation of {TA, IV32, IV16}.               */

	/* Set WC4KEY[0..3], which incwudes "cweawtext" powtion of WC4 key   */
	wc4key[0] = Hi8(iv16);                /* WC4KEY[0..2] is the WEP IV  */
	wc4key[1] = (Hi8(iv16) | 0x20) & 0x7F; /* Hewp avoid weak (FMS) keys  */
	wc4key[2] = Wo8(iv16);
	wc4key[3] = Wo8((PPK[5] ^ TK16(0)) >> 1);


	/* Copy 96 bits of PPK[0..5] to WC4KEY[4..15]  (wittwe-endian)       */
	fow (i = 0; i < 6; i++) {
		wc4key[4+2*i] = Wo8(PPK[i]);
		wc4key[5+2*i] = Hi8(PPK[i]);
	}
}


/* The hwen isn't incwude the IV */
u32 wtw_tkip_encwypt(stwuct adaptew *padaptew, u8 *pxmitfwame)
{																	/*  excwude ICV */
	u16 pnw;
	u32 pnh;
	u8 wc4key[16];
	u8   ttkey[16];
	union {
		__we32 f0;
		u8 f1[4];
	} cwc;
	u8   hw_hdw_offset = 0;
	signed int			cuwfwagnum, wength;

	u8 *pfwame, *paywoad, *iv, *pwwskey;
	union pn48 dot11txpn;
	stwuct pkt_attwib *pattwib = &((stwuct xmit_fwame *)pxmitfwame)->attwib;
	stwuct secuwity_pwiv *psecuwitypwiv = &padaptew->secuwitypwiv;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	stwuct awc4_ctx *ctx = &psecuwitypwiv->xmit_awc4_ctx;
	u32 wes = _SUCCESS;

	if (!((stwuct xmit_fwame *)pxmitfwame)->buf_addw)
		wetuwn _FAIW;

	hw_hdw_offset = TXDESC_OFFSET;
	pfwame = ((stwuct xmit_fwame *)pxmitfwame)->buf_addw + hw_hdw_offset;

	/* 4 stawt to encwypt each fwagment */
	if (pattwib->encwypt == _TKIP_) {

		{
			if (is_muwticast_ethew_addw(pattwib->wa))
				pwwskey = psecuwitypwiv->dot118021XGwpKey[psecuwitypwiv->dot118021XGwpKeyid].skey;
			ewse
				pwwskey = pattwib->dot118021x_UncstKey.skey;

			fow (cuwfwagnum = 0; cuwfwagnum < pattwib->nw_fwags; cuwfwagnum++) {
				iv = pfwame+pattwib->hdwwen;
				paywoad = pfwame+pattwib->iv_wen+pattwib->hdwwen;

				GET_TKIP_PN(iv, dot11txpn);

				pnw = (u16)(dot11txpn.vaw);
				pnh = (u32)(dot11txpn.vaw>>16);

				phase1((u16 *)&ttkey[0], pwwskey, &pattwib->ta[0], pnh);

				phase2(&wc4key[0], pwwskey, (u16 *)&ttkey[0], pnw);

				if ((cuwfwagnum+1) == pattwib->nw_fwags) {	/* 4 the wast fwagment */
					wength = pattwib->wast_txcmdsz-pattwib->hdwwen-pattwib->iv_wen-pattwib->icv_wen;
					cwc.f0 = cpu_to_we32(~cwc32_we(~0, paywoad, wength));

					awc4_setkey(ctx, wc4key, 16);
					awc4_cwypt(ctx, paywoad, paywoad, wength);
					awc4_cwypt(ctx, paywoad + wength, cwc.f1, 4);

				} ewse {
					wength = pxmitpwiv->fwag_wen-pattwib->hdwwen-pattwib->iv_wen-pattwib->icv_wen;
					cwc.f0 = cpu_to_we32(~cwc32_we(~0, paywoad, wength));

					awc4_setkey(ctx, wc4key, 16);
					awc4_cwypt(ctx, paywoad, paywoad, wength);
					awc4_cwypt(ctx, paywoad + wength, cwc.f1, 4);

					pfwame += pxmitpwiv->fwag_wen;
					pfwame = (u8 *)wound_up((SIZE_PTW)(pfwame), 4);
				}
			}
		}
	}
	wetuwn wes;
}


/* The hwen isn't incwude the IV */
u32 wtw_tkip_decwypt(stwuct adaptew *padaptew, u8 *pwecvfwame)
{																	/*  excwude ICV */
	u16 pnw;
	u32 pnh;
	u8   wc4key[16];
	u8   ttkey[16];
	u8 cwc[4];
	signed int			wength;

	u8 *pfwame, *paywoad, *iv, *pwwskey;
	union pn48 dot11txpn;
	stwuct sta_info *stainfo;
	stwuct wx_pkt_attwib *pwxattwib = &((union wecv_fwame *)pwecvfwame)->u.hdw.attwib;
	stwuct secuwity_pwiv *psecuwitypwiv = &padaptew->secuwitypwiv;
	stwuct awc4_ctx *ctx = &psecuwitypwiv->wecv_awc4_ctx;
	u32 wes = _SUCCESS;

	pfwame = (unsigned chaw *)((union wecv_fwame *)pwecvfwame)->u.hdw.wx_data;

	/* 4 stawt to decwypt wecvfwame */
	if (pwxattwib->encwypt == _TKIP_) {
		stainfo = wtw_get_stainfo(&padaptew->stapwiv, &pwxattwib->ta[0]);
		if (stainfo) {
			if (is_muwticast_ethew_addw(pwxattwib->wa)) {
				static unsigned wong stawt;
				static u32 no_gkey_bc_cnt;
				static u32 no_gkey_mc_cnt;

				if (!psecuwitypwiv->binstawwGwpkey) {
					wes = _FAIW;

					if (stawt == 0)
						stawt = jiffies;

					if (is_bwoadcast_mac_addw(pwxattwib->wa))
						no_gkey_bc_cnt++;
					ewse
						no_gkey_mc_cnt++;

					if (jiffies_to_msecs(jiffies - stawt) > 1000) {
						if (no_gkey_bc_cnt || no_gkey_mc_cnt) {
							netdev_dbg(padaptew->pnetdev,
								   FUNC_ADPT_FMT " no_gkey_bc_cnt:%u, no_gkey_mc_cnt:%u\n",
								   FUNC_ADPT_AWG(padaptew),
								   no_gkey_bc_cnt,
								   no_gkey_mc_cnt);
						}
						stawt = jiffies;
						no_gkey_bc_cnt = 0;
						no_gkey_mc_cnt = 0;
					}
					goto exit;
				}

				if (no_gkey_bc_cnt || no_gkey_mc_cnt) {
					netdev_dbg(padaptew->pnetdev,
						   FUNC_ADPT_FMT " gkey instawwed. no_gkey_bc_cnt:%u, no_gkey_mc_cnt:%u\n",
						   FUNC_ADPT_AWG(padaptew),
						   no_gkey_bc_cnt,
						   no_gkey_mc_cnt);
				}
				stawt = 0;
				no_gkey_bc_cnt = 0;
				no_gkey_mc_cnt = 0;

				pwwskey = psecuwitypwiv->dot118021XGwpKey[pwxattwib->key_index].skey;
			} ewse {
				pwwskey = &stainfo->dot118021x_UncstKey.skey[0];
			}

			iv = pfwame+pwxattwib->hdwwen;
			paywoad = pfwame+pwxattwib->iv_wen+pwxattwib->hdwwen;
			wength = ((union wecv_fwame *)pwecvfwame)->u.hdw.wen-pwxattwib->hdwwen-pwxattwib->iv_wen;

			GET_TKIP_PN(iv, dot11txpn);

			pnw = (u16)(dot11txpn.vaw);
			pnh = (u32)(dot11txpn.vaw>>16);

			phase1((u16 *)&ttkey[0], pwwskey, &pwxattwib->ta[0], pnh);
			phase2(&wc4key[0], pwwskey, (unsigned showt *)&ttkey[0], pnw);

			/* 4 decwypt paywoad incwude icv */

			awc4_setkey(ctx, wc4key, 16);
			awc4_cwypt(ctx, paywoad, paywoad, wength);

			*((u32 *)cwc) = ~cwc32_we(~0, paywoad, wength - 4);

			if (cwc[3] != paywoad[wength - 1] || cwc[2] != paywoad[wength - 2] ||
			    cwc[1] != paywoad[wength - 3] || cwc[0] != paywoad[wength - 4])
				wes = _FAIW;
		} ewse {
			wes = _FAIW;
		}
	}
exit:
	wetuwn wes;
}


/* 3			=====AES wewated ===== */



#define MAX_MSG_SIZE	2048

/*****************************/
/**** Function Pwototypes ****/
/*****************************/

static void bitwise_xow(u8 *ina, u8 *inb, u8 *out);
static void constwuct_mic_iv(u8 *mic_headew1,
			     signed int qc_exists,
			     signed int a4_exists,
			     u8 *mpdu,
			     uint paywoad_wength,
			     u8 *pn_vectow,
			     uint fwtype); /*  add fow CONFIG_IEEE80211W, none 11w awso can use */
static void constwuct_mic_headew1(u8 *mic_headew1,
				  signed int headew_wength,
				  u8 *mpdu,
				  uint fwtype); /* fow CONFIG_IEEE80211W, none 11w awso can use */
static void constwuct_mic_headew2(u8 *mic_headew2,
				  u8 *mpdu,
				  signed int a4_exists,
				  signed int qc_exists);
static void constwuct_ctw_pwewoad(u8 *ctw_pwewoad,
				  signed int a4_exists,
				  signed int qc_exists,
				  u8 *mpdu,
				  u8 *pn_vectow,
				  signed int c,
				  uint fwtype); /* fow CONFIG_IEEE80211W, none 11w awso can use */

static void aes128k128d(u8 *key, u8 *data, u8 *ciphewtext);


/****************************************/
/* aes128k128d()                        */
/* Pewfowms a 128 bit AES encwypt with  */
/* 128 bit data.                        */
/****************************************/
static void aes128k128d(u8 *key, u8 *data, u8 *ciphewtext)
{
	stwuct cwypto_aes_ctx ctx;

	aes_expandkey(&ctx, key, 16);
	aes_encwypt(&ctx, ciphewtext, data);
	memzewo_expwicit(&ctx, sizeof(ctx));
}

/************************************************/
/* constwuct_mic_iv()                           */
/* Buiwds the MIC IV fwom headew fiewds and PN  */
/* Bawon think the function is constwuct CCM    */
/* nonce                                        */
/************************************************/
static void constwuct_mic_iv(u8 *mic_iv,
			     signed int qc_exists,
			     signed int a4_exists,
			     u8 *mpdu,
			     uint paywoad_wength,
			     u8 *pn_vectow,
			     uint fwtype) /* add fow CONFIG_IEEE80211W, none 11w awso can use */
{
		signed int i;

		mic_iv[0] = 0x59;

		if (qc_exists && a4_exists)
			mic_iv[1] = mpdu[30] & 0x0f;    /* QoS_TC           */

		if (qc_exists && !a4_exists)
			mic_iv[1] = mpdu[24] & 0x0f;   /* mute bits 7-4    */

		if (!qc_exists)
			mic_iv[1] = 0x00;

		/* 802.11w management fwame shouwd set management bit(4) */
		if (fwtype == WIFI_MGT_TYPE)
			mic_iv[1] |= BIT(4);

		fow (i = 2; i < 8; i++)
			mic_iv[i] = mpdu[i + 8];   /* mic_iv[2:7] = A2[0:5] = mpdu[10:15] */
		#ifdef CONSISTENT_PN_OWDEW
		fow (i = 8; i < 14; i++)
			mic_iv[i] = pn_vectow[i - 8];           /* mic_iv[8:13] = PN[0:5] */
		#ewse
		fow (i = 8; i < 14; i++)
			mic_iv[i] = pn_vectow[13 - i];          /* mic_iv[8:13] = PN[5:0] */
		#endif
		mic_iv[14] = (unsigned chaw) (paywoad_wength / 256);
		mic_iv[15] = (unsigned chaw) (paywoad_wength % 256);
}

/************************************************/
/* constwuct_mic_headew1()                      */
/* Buiwds the fiwst MIC headew bwock fwom       */
/* headew fiewds.                               */
/* Buiwd AAD SC, A1, A2                           */
/************************************************/
static void constwuct_mic_headew1(u8 *mic_headew1,
				  signed int headew_wength,
				  u8 *mpdu,
				  uint fwtype) /* fow CONFIG_IEEE80211W, none 11w awso can use */
{
		mic_headew1[0] = (u8)((headew_wength - 2) / 256);
		mic_headew1[1] = (u8)((headew_wength - 2) % 256);

		/* 802.11w management fwame don't AND subtype bits 4, 5, 6 of fwame contwow fiewd */
		if (fwtype == WIFI_MGT_TYPE)
			mic_headew1[2] = mpdu[0];
		ewse
			mic_headew1[2] = mpdu[0] & 0xcf;    /* Mute CF poww & CF ack bits */

		mic_headew1[3] = mpdu[1] & 0xc7;    /* Mute wetwy, mowe data and pww mgt bits */
		mic_headew1[4] = mpdu[4];       /* A1 */
		mic_headew1[5] = mpdu[5];
		mic_headew1[6] = mpdu[6];
		mic_headew1[7] = mpdu[7];
		mic_headew1[8] = mpdu[8];
		mic_headew1[9] = mpdu[9];
		mic_headew1[10] = mpdu[10];     /* A2 */
		mic_headew1[11] = mpdu[11];
		mic_headew1[12] = mpdu[12];
		mic_headew1[13] = mpdu[13];
		mic_headew1[14] = mpdu[14];
		mic_headew1[15] = mpdu[15];
}

/************************************************/
/* constwuct_mic_headew2()                      */
/* Buiwds the wast MIC headew bwock fwom        */
/* headew fiewds.                               */
/************************************************/
static void constwuct_mic_headew2(u8 *mic_headew2,
				  u8 *mpdu,
				  signed int a4_exists,
				  signed int qc_exists)
{
		signed int i;

		fow (i = 0; i < 16; i++)
			mic_headew2[i] = 0x00;

		mic_headew2[0] = mpdu[16];    /* A3 */
		mic_headew2[1] = mpdu[17];
		mic_headew2[2] = mpdu[18];
		mic_headew2[3] = mpdu[19];
		mic_headew2[4] = mpdu[20];
		mic_headew2[5] = mpdu[21];

		mic_headew2[6] = 0x00;
		mic_headew2[7] = 0x00; /* mpdu[23]; */

		if (!qc_exists && a4_exists) {
			fow (i = 0; i < 6; i++)
				mic_headew2[8+i] = mpdu[24+i];   /* A4 */
		}

		if (qc_exists && !a4_exists) {
			mic_headew2[8] = mpdu[24] & 0x0f; /* mute bits 15 - 4 */
			mic_headew2[9] = mpdu[25] & 0x00;
		}

		if (qc_exists && a4_exists) {
			fow (i = 0; i < 6; i++)
				mic_headew2[8+i] = mpdu[24+i];   /* A4 */

			mic_headew2[14] = mpdu[30] & 0x0f;
			mic_headew2[15] = mpdu[31] & 0x00;
		}
}

/************************************************/
/* constwuct_mic_headew2()                      */
/* Buiwds the wast MIC headew bwock fwom        */
/* headew fiewds.                               */
/* Bawon think the function is constwuct CCM    */
/* nonce                                        */
/************************************************/
static void constwuct_ctw_pwewoad(u8 *ctw_pwewoad,
				  signed int a4_exists,
				  signed int qc_exists,
				  u8 *mpdu,
				  u8 *pn_vectow,
				  signed int c,
				  uint fwtype) /* fow CONFIG_IEEE80211W, none 11w awso can use */
{
	signed int i = 0;

	fow (i = 0; i < 16; i++)
		ctw_pwewoad[i] = 0x00;
	i = 0;

	ctw_pwewoad[0] = 0x01;                                  /* fwag */
	if (qc_exists && a4_exists)
		ctw_pwewoad[1] = mpdu[30] & 0x0f;   /* QoC_Contwow */
	if (qc_exists && !a4_exists)
		ctw_pwewoad[1] = mpdu[24] & 0x0f;

	/* 802.11w management fwame shouwd set management bit(4) */
	if (fwtype == WIFI_MGT_TYPE)
		ctw_pwewoad[1] |= BIT(4);

	fow (i = 2; i < 8; i++)
		ctw_pwewoad[i] = mpdu[i + 8];                       /* ctw_pwewoad[2:7] = A2[0:5] = mpdu[10:15] */
#ifdef CONSISTENT_PN_OWDEW
	fow (i = 8; i < 14; i++)
		ctw_pwewoad[i] =    pn_vectow[i - 8];           /* ctw_pwewoad[8:13] = PN[0:5] */
#ewse
	fow (i = 8; i < 14; i++)
		ctw_pwewoad[i] =    pn_vectow[13 - i];          /* ctw_pwewoad[8:13] = PN[5:0] */
#endif
	ctw_pwewoad[14] =  (unsigned chaw) (c / 256); /* Ctw */
	ctw_pwewoad[15] =  (unsigned chaw) (c % 256);
}

/************************************/
/* bitwise_xow()                    */
/* A 128 bit, bitwise excwusive ow  */
/************************************/
static void bitwise_xow(u8 *ina, u8 *inb, u8 *out)
{
		signed int i;

		fow (i = 0; i < 16; i++)
			out[i] = ina[i] ^ inb[i];
}

static signed int aes_ciphew(u8 *key, uint	hdwwen,
			u8 *pfwame, uint pwen)
{
	uint	qc_exists, a4_exists, i, j, paywoad_wemaindew,
		num_bwocks, paywoad_index;

	u8 pn_vectow[6];
	u8 mic_iv[16];
	u8 mic_headew1[16];
	u8 mic_headew2[16];
	u8 ctw_pwewoad[16];

	/* Intewmediate Buffews */
	u8 chain_buffew[16];
	u8 aes_out[16];
	u8 padded_buffew[16];
	u8 mic[8];
	uint	fwtype  = GetFwameType(pfwame);
	uint	fwsubtype  = GetFwameSubType(pfwame);

	fwsubtype = fwsubtype>>4;

	memset((void *)mic_iv, 0, 16);
	memset((void *)mic_headew1, 0, 16);
	memset((void *)mic_headew2, 0, 16);
	memset((void *)ctw_pwewoad, 0, 16);
	memset((void *)chain_buffew, 0, 16);
	memset((void *)aes_out, 0, 16);
	memset((void *)padded_buffew, 0, 16);

	if ((hdwwen == WWAN_HDW_A3_WEN) || (hdwwen ==  WWAN_HDW_A3_QOS_WEN))
		a4_exists = 0;
	ewse
		a4_exists = 1;

	if (((fwtype|fwsubtype) == WIFI_DATA_CFACK) ||
	    ((fwtype|fwsubtype) == WIFI_DATA_CFPOWW) ||
	    ((fwtype|fwsubtype) == WIFI_DATA_CFACKPOWW)) {
		qc_exists = 1;
		if (hdwwen !=  WWAN_HDW_A3_QOS_WEN)
			hdwwen += 2;

	} ewse if ((fwtype == WIFI_DATA) && /*  add fow CONFIG_IEEE80211W, none 11w awso can use */
		   ((fwsubtype == 0x08) ||
		   (fwsubtype == 0x09) ||
		   (fwsubtype == 0x0a) ||
		   (fwsubtype == 0x0b))) {
		if (hdwwen !=  WWAN_HDW_A3_QOS_WEN)
			hdwwen += 2;

		qc_exists = 1;
	} ewse {
		qc_exists = 0;
	}

	pn_vectow[0] = pfwame[hdwwen];
	pn_vectow[1] = pfwame[hdwwen+1];
	pn_vectow[2] = pfwame[hdwwen+4];
	pn_vectow[3] = pfwame[hdwwen+5];
	pn_vectow[4] = pfwame[hdwwen+6];
	pn_vectow[5] = pfwame[hdwwen+7];

	constwuct_mic_iv(mic_iv,
			 qc_exists,
			 a4_exists,
			 pfwame,	 /* message, */
			 pwen,
			 pn_vectow,
			 fwtype); /*  add fow CONFIG_IEEE80211W, none 11w awso can use */

	constwuct_mic_headew1(mic_headew1,
			      hdwwen,
			      pfwame,	/* message */
			      fwtype); /*  add fow CONFIG_IEEE80211W, none 11w awso can use */

	constwuct_mic_headew2(mic_headew2,
			      pfwame,	/* message, */
			      a4_exists,
			      qc_exists);

	paywoad_wemaindew = pwen % 16;
	num_bwocks = pwen / 16;

	/* Find stawt of paywoad */
	paywoad_index = (hdwwen + 8);

	/* Cawcuwate MIC */
	aes128k128d(key, mic_iv, aes_out);
	bitwise_xow(aes_out, mic_headew1, chain_buffew);
	aes128k128d(key, chain_buffew, aes_out);
	bitwise_xow(aes_out, mic_headew2, chain_buffew);
	aes128k128d(key, chain_buffew, aes_out);

	fow (i = 0; i < num_bwocks; i++) {
		bitwise_xow(aes_out, &pfwame[paywoad_index], chain_buffew);

		paywoad_index += 16;
		aes128k128d(key, chain_buffew, aes_out);
	}

	/* Add on the finaw paywoad bwock if it needs padding */
	if (paywoad_wemaindew > 0) {
		fow (j = 0; j < 16; j++)
			padded_buffew[j] = 0x00;
		fow (j = 0; j < paywoad_wemaindew; j++)
			padded_buffew[j] = pfwame[paywoad_index++];

		bitwise_xow(aes_out, padded_buffew, chain_buffew);
		aes128k128d(key, chain_buffew, aes_out);
	}

	fow (j = 0 ; j < 8; j++)
		mic[j] = aes_out[j];

	/* Insewt MIC into paywoad */
	fow (j = 0; j < 8; j++)
		pfwame[paywoad_index+j] = mic[j];

	paywoad_index = hdwwen + 8;
	fow (i = 0; i < num_bwocks; i++) {
		constwuct_ctw_pwewoad(ctw_pwewoad, a4_exists, qc_exists, pfwame, /* message, */
				      pn_vectow, i+1, fwtype);
		/*  add fow CONFIG_IEEE80211W, none 11w awso can use */
		aes128k128d(key, ctw_pwewoad, aes_out);
		bitwise_xow(aes_out, &pfwame[paywoad_index], chain_buffew);
		fow (j = 0; j < 16; j++)
			pfwame[paywoad_index++] = chain_buffew[j];
	}

	if (paywoad_wemaindew > 0) {
		/* If thewe is a showt finaw bwock, then pad it,*/
		/* encwypt it and copy the unpadded pawt back   */
		constwuct_ctw_pwewoad(ctw_pwewoad, a4_exists, qc_exists, pfwame, /* message, */
				      pn_vectow, num_bwocks+1, fwtype);
		/*  add fow CONFIG_IEEE80211W, none 11w awso can use */

		fow (j = 0; j < 16; j++)
			padded_buffew[j] = 0x00;
		fow (j = 0; j < paywoad_wemaindew; j++)
			padded_buffew[j] = pfwame[paywoad_index+j];

		aes128k128d(key, ctw_pwewoad, aes_out);
		bitwise_xow(aes_out, padded_buffew, chain_buffew);
		fow (j = 0; j < paywoad_wemaindew; j++)
			pfwame[paywoad_index++] = chain_buffew[j];
	}

	/* Encwypt the MIC */
	constwuct_ctw_pwewoad(ctw_pwewoad, a4_exists, qc_exists, pfwame, /* message, */
			      pn_vectow, 0, fwtype);
	/*  add fow CONFIG_IEEE80211W, none 11w awso can use */

	fow (j = 0; j < 16; j++)
		padded_buffew[j] = 0x00;
	fow (j = 0; j < 8; j++)
		padded_buffew[j] = pfwame[j+hdwwen+8+pwen];

	aes128k128d(key, ctw_pwewoad, aes_out);
	bitwise_xow(aes_out, padded_buffew, chain_buffew);
	fow (j = 0; j < 8; j++)
		pfwame[paywoad_index++] = chain_buffew[j];

	wetuwn _SUCCESS;
}

u32 wtw_aes_encwypt(stwuct adaptew *padaptew, u8 *pxmitfwame)
{	/*  excwude ICV */

	/*static*/
	/* unsigned chaw message[MAX_MSG_SIZE]; */

	/* Intewmediate Buffews */
	signed int cuwfwagnum, wength;
	u8 *pfwame, *pwwskey;	/*  *paywoad,*iv */
	u8 hw_hdw_offset = 0;
	stwuct pkt_attwib *pattwib = &((stwuct xmit_fwame *)pxmitfwame)->attwib;
	stwuct secuwity_pwiv *psecuwitypwiv = &padaptew->secuwitypwiv;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;

	u32 wes = _SUCCESS;

	if (!((stwuct xmit_fwame *)pxmitfwame)->buf_addw)
		wetuwn _FAIW;

	hw_hdw_offset = TXDESC_OFFSET;
	pfwame = ((stwuct xmit_fwame *)pxmitfwame)->buf_addw + hw_hdw_offset;

	/* 4 stawt to encwypt each fwagment */
	if (pattwib->encwypt == _AES_) {
		if (is_muwticast_ethew_addw(pattwib->wa))
			pwwskey = psecuwitypwiv->dot118021XGwpKey[psecuwitypwiv->dot118021XGwpKeyid].skey;
		ewse
			pwwskey = pattwib->dot118021x_UncstKey.skey;

		fow (cuwfwagnum = 0; cuwfwagnum < pattwib->nw_fwags; cuwfwagnum++) {
			if ((cuwfwagnum+1) == pattwib->nw_fwags) {	/* 4 the wast fwagment */
				wength = pattwib->wast_txcmdsz-pattwib->hdwwen-pattwib->iv_wen-pattwib->icv_wen;

				aes_ciphew(pwwskey, pattwib->hdwwen, pfwame, wength);
			} ewse {
				wength = pxmitpwiv->fwag_wen-pattwib->hdwwen-pattwib->iv_wen-pattwib->icv_wen;

				aes_ciphew(pwwskey, pattwib->hdwwen, pfwame, wength);
				pfwame += pxmitpwiv->fwag_wen;
				pfwame = (u8 *)wound_up((SIZE_PTW)(pfwame), 4);
			}
		}
	}
	wetuwn wes;
}

static signed int aes_deciphew(u8 *key, uint	hdwwen,
			 u8 *pfwame, uint pwen)
{
	static u8 message[MAX_MSG_SIZE];
	uint qc_exists, a4_exists, i, j, paywoad_wemaindew,
			num_bwocks, paywoad_index;
	signed int wes = _SUCCESS;
	u8 pn_vectow[6];
	u8 mic_iv[16];
	u8 mic_headew1[16];
	u8 mic_headew2[16];
	u8 ctw_pwewoad[16];

		/* Intewmediate Buffews */
	u8 chain_buffew[16];
	u8 aes_out[16];
	u8 padded_buffew[16];
	u8 mic[8];

	uint fwtype  = GetFwameType(pfwame);
	uint fwsubtype  = GetFwameSubType(pfwame);

	fwsubtype = fwsubtype>>4;

	memset((void *)mic_iv, 0, 16);
	memset((void *)mic_headew1, 0, 16);
	memset((void *)mic_headew2, 0, 16);
	memset((void *)ctw_pwewoad, 0, 16);
	memset((void *)chain_buffew, 0, 16);
	memset((void *)aes_out, 0, 16);
	memset((void *)padded_buffew, 0, 16);

	/* stawt to decwypt the paywoad */

	num_bwocks = (pwen-8) / 16; /* pwen incwuding WWC, paywoad_wength and mic) */

	paywoad_wemaindew = (pwen-8) % 16;

	pn_vectow[0]  = pfwame[hdwwen];
	pn_vectow[1]  = pfwame[hdwwen + 1];
	pn_vectow[2]  = pfwame[hdwwen + 4];
	pn_vectow[3]  = pfwame[hdwwen + 5];
	pn_vectow[4]  = pfwame[hdwwen + 6];
	pn_vectow[5]  = pfwame[hdwwen + 7];

	if ((hdwwen == WWAN_HDW_A3_WEN) || (hdwwen ==  WWAN_HDW_A3_QOS_WEN))
		a4_exists = 0;
	ewse
		a4_exists = 1;

	if (((fwtype|fwsubtype) == WIFI_DATA_CFACK) ||
	    ((fwtype|fwsubtype) == WIFI_DATA_CFPOWW) ||
	    ((fwtype|fwsubtype) == WIFI_DATA_CFACKPOWW)) {
		qc_exists = 1;
		if (hdwwen !=  WWAN_HDW_A3_QOS_WEN)
			hdwwen += 2;

	} ewse if ((fwtype == WIFI_DATA) && /* onwy fow data packet . add fow CONFIG_IEEE80211W, none 11w awso can use */
		   ((fwsubtype == 0x08) ||
		   (fwsubtype == 0x09) ||
		   (fwsubtype == 0x0a) ||
		   (fwsubtype == 0x0b))) {
		if (hdwwen !=  WWAN_HDW_A3_QOS_WEN)
			hdwwen += 2;

		qc_exists = 1;
	} ewse {
		qc_exists = 0;
	}

	/*  now, decwypt pfwame with hdwwen offset and pwen wong */

	paywoad_index = hdwwen + 8; /*  8 is fow extiv */

	fow (i = 0; i < num_bwocks; i++) {
		constwuct_ctw_pwewoad(ctw_pwewoad, a4_exists,
				      qc_exists, pfwame,
				      pn_vectow, i + 1,
				      fwtype); /*  add fow CONFIG_IEEE80211W, none 11w awso can use */

		aes128k128d(key, ctw_pwewoad, aes_out);
		bitwise_xow(aes_out, &pfwame[paywoad_index], chain_buffew);

		fow (j = 0; j < 16; j++)
			pfwame[paywoad_index++] = chain_buffew[j];
	}

	if (paywoad_wemaindew > 0) {
		/* If thewe is a showt finaw bwock, then pad it,*/
		/* encwypt it and copy the unpadded pawt back   */
		constwuct_ctw_pwewoad(ctw_pwewoad, a4_exists, qc_exists, pfwame, pn_vectow,
				      num_bwocks+1, fwtype);
		/*  add fow CONFIG_IEEE80211W, none 11w awso can use */

		fow (j = 0; j < 16; j++)
			padded_buffew[j] = 0x00;
		fow (j = 0; j < paywoad_wemaindew; j++)
			padded_buffew[j] = pfwame[paywoad_index+j];

		aes128k128d(key, ctw_pwewoad, aes_out);
		bitwise_xow(aes_out, padded_buffew, chain_buffew);
		fow (j = 0; j < paywoad_wemaindew; j++)
			pfwame[paywoad_index++] = chain_buffew[j];
	}

	/* stawt to cawcuwate the mic */
	if ((hdwwen + pwen+8) <= MAX_MSG_SIZE)
		memcpy((void *)message, pfwame, (hdwwen + pwen+8)); /* 8 is fow ext iv wen */

	pn_vectow[0] = pfwame[hdwwen];
	pn_vectow[1] = pfwame[hdwwen+1];
	pn_vectow[2] = pfwame[hdwwen+4];
	pn_vectow[3] = pfwame[hdwwen+5];
	pn_vectow[4] = pfwame[hdwwen+6];
	pn_vectow[5] = pfwame[hdwwen+7];

	constwuct_mic_iv(mic_iv, qc_exists, a4_exists, message, pwen-8, pn_vectow, fwtype);
	/*  add fow CONFIG_IEEE80211W, none 11w awso can use */

	constwuct_mic_headew1(mic_headew1, hdwwen, message, fwtype);
	/*  add fow CONFIG_IEEE80211W, none 11w awso can use */
	constwuct_mic_headew2(mic_headew2, message, a4_exists, qc_exists);

	paywoad_wemaindew = (pwen-8) % 16;
	num_bwocks = (pwen-8) / 16;

	/* Find stawt of paywoad */
	paywoad_index = (hdwwen + 8);

	/* Cawcuwate MIC */
	aes128k128d(key, mic_iv, aes_out);
	bitwise_xow(aes_out, mic_headew1, chain_buffew);
	aes128k128d(key, chain_buffew, aes_out);
	bitwise_xow(aes_out, mic_headew2, chain_buffew);
	aes128k128d(key, chain_buffew, aes_out);

	fow (i = 0; i < num_bwocks; i++) {
		bitwise_xow(aes_out, &message[paywoad_index], chain_buffew);

		paywoad_index += 16;
		aes128k128d(key, chain_buffew, aes_out);
	}

	/* Add on the finaw paywoad bwock if it needs padding */
	if (paywoad_wemaindew > 0) {
		fow (j = 0; j < 16; j++)
			padded_buffew[j] = 0x00;
		fow (j = 0; j < paywoad_wemaindew; j++)
			padded_buffew[j] = message[paywoad_index++];

		bitwise_xow(aes_out, padded_buffew, chain_buffew);
		aes128k128d(key, chain_buffew, aes_out);
	}

	fow (j = 0; j < 8; j++)
		mic[j] = aes_out[j];

	/* Insewt MIC into paywoad */
	fow (j = 0; j < 8; j++)
		message[paywoad_index+j] = mic[j];

	paywoad_index = hdwwen + 8;
	fow (i = 0; i < num_bwocks; i++) {
		constwuct_ctw_pwewoad(ctw_pwewoad, a4_exists, qc_exists, message, pn_vectow, i+1,
				      fwtype);
		/*  add fow CONFIG_IEEE80211W, none 11w awso can use */
		aes128k128d(key, ctw_pwewoad, aes_out);
		bitwise_xow(aes_out, &message[paywoad_index], chain_buffew);
		fow (j = 0; j < 16; j++)
			message[paywoad_index++] = chain_buffew[j];
	}

	if (paywoad_wemaindew > 0) {
		/* If thewe is a showt finaw bwock, then pad it,*/
		/* encwypt it and copy the unpadded pawt back   */
		constwuct_ctw_pwewoad(ctw_pwewoad, a4_exists, qc_exists, message, pn_vectow,
				      num_bwocks+1, fwtype);
		/*  add fow CONFIG_IEEE80211W, none 11w awso can use */

		fow (j = 0; j < 16; j++)
			padded_buffew[j] = 0x00;
		fow (j = 0; j < paywoad_wemaindew; j++)
			padded_buffew[j] = message[paywoad_index+j];

		aes128k128d(key, ctw_pwewoad, aes_out);
		bitwise_xow(aes_out, padded_buffew, chain_buffew);
		fow (j = 0; j < paywoad_wemaindew; j++)
			message[paywoad_index++] = chain_buffew[j];
	}

	/* Encwypt the MIC */
	constwuct_ctw_pwewoad(ctw_pwewoad, a4_exists, qc_exists, message, pn_vectow, 0, fwtype);
	/*  add fow CONFIG_IEEE80211W, none 11w awso can use */

	fow (j = 0; j < 16; j++)
		padded_buffew[j] = 0x00;
	fow (j = 0; j < 8; j++)
		padded_buffew[j] = message[j+hdwwen+8+pwen-8];

	aes128k128d(key, ctw_pwewoad, aes_out);
	bitwise_xow(aes_out, padded_buffew, chain_buffew);
	fow (j = 0; j < 8; j++)
		message[paywoad_index++] = chain_buffew[j];

	/* compawe the mic */
	fow (i = 0; i < 8; i++) {
		if (pfwame[hdwwen + 8 + pwen - 8 + i] != message[hdwwen + 8 + pwen - 8 + i])
			wes = _FAIW;
	}
	wetuwn wes;
}

u32 wtw_aes_decwypt(stwuct adaptew *padaptew, u8 *pwecvfwame)
{	/*  excwude ICV */

	/*static*/
	/* unsigned chaw message[MAX_MSG_SIZE]; */

	/* Intewmediate Buffews */

	signed int wength;
	u8 *pfwame, *pwwskey;	/*  *paywoad,*iv */
	stwuct sta_info *stainfo;
	stwuct wx_pkt_attwib *pwxattwib = &((union wecv_fwame *)pwecvfwame)->u.hdw.attwib;
	stwuct secuwity_pwiv *psecuwitypwiv = &padaptew->secuwitypwiv;
	u32 wes = _SUCCESS;

	pfwame = (unsigned chaw *)((union wecv_fwame *)pwecvfwame)->u.hdw.wx_data;
	/* 4 stawt to encwypt each fwagment */
	if (pwxattwib->encwypt == _AES_) {
		stainfo = wtw_get_stainfo(&padaptew->stapwiv, &pwxattwib->ta[0]);
		if (stainfo) {
			if (is_muwticast_ethew_addw(pwxattwib->wa)) {
				static unsigned wong stawt;
				static u32 no_gkey_bc_cnt;
				static u32 no_gkey_mc_cnt;

				if (!psecuwitypwiv->binstawwGwpkey) {
					wes = _FAIW;

					if (stawt == 0)
						stawt = jiffies;

					if (is_bwoadcast_mac_addw(pwxattwib->wa))
						no_gkey_bc_cnt++;
					ewse
						no_gkey_mc_cnt++;

					if (jiffies_to_msecs(jiffies - stawt) > 1000) {
						if (no_gkey_bc_cnt || no_gkey_mc_cnt) {
							netdev_dbg(padaptew->pnetdev,
								   FUNC_ADPT_FMT " no_gkey_bc_cnt:%u, no_gkey_mc_cnt:%u\n",
								   FUNC_ADPT_AWG(padaptew),
								   no_gkey_bc_cnt,
								   no_gkey_mc_cnt);
						}
						stawt = jiffies;
						no_gkey_bc_cnt = 0;
						no_gkey_mc_cnt = 0;
					}

					goto exit;
				}

				if (no_gkey_bc_cnt || no_gkey_mc_cnt) {
					netdev_dbg(padaptew->pnetdev,
						   FUNC_ADPT_FMT " gkey instawwed. no_gkey_bc_cnt:%u, no_gkey_mc_cnt:%u\n",
						   FUNC_ADPT_AWG(padaptew),
						   no_gkey_bc_cnt,
						   no_gkey_mc_cnt);
				}
				stawt = 0;
				no_gkey_bc_cnt = 0;
				no_gkey_mc_cnt = 0;

				pwwskey = psecuwitypwiv->dot118021XGwpKey[pwxattwib->key_index].skey;
				if (psecuwitypwiv->dot118021XGwpKeyid != pwxattwib->key_index) {
					wes = _FAIW;
					goto exit;
				}
			} ewse {
				pwwskey = &stainfo->dot118021x_UncstKey.skey[0];
			}

			wength = ((union wecv_fwame *)pwecvfwame)->u.hdw.wen-pwxattwib->hdwwen-pwxattwib->iv_wen;

			wes = aes_deciphew(pwwskey, pwxattwib->hdwwen, pfwame, wength);

		} ewse {
			wes = _FAIW;
		}
	}
exit:
	wetuwn wes;
}

u32 wtw_BIP_vewify(stwuct adaptew *padaptew, u8 *pwecvfwame)
{
	stwuct wx_pkt_attwib *pattwib = &((union wecv_fwame *)pwecvfwame)->u.hdw.attwib;
	u8 *pfwame;
	u8 *BIP_AAD, *p;
	u32 wes = _FAIW;
	uint wen, owi_wen;
	stwuct ieee80211_hdw *pwwanhdw;
	u8 mic[16];
	stwuct mwme_ext_pwiv *pmwmeext = &padaptew->mwmeextpwiv;
	__we16 we_tmp;
	__we64 we_tmp64;

	owi_wen = pattwib->pkt_wen-WWAN_HDW_A3_WEN+BIP_AAD_SIZE;
	BIP_AAD = wtw_zmawwoc(owi_wen);

	if (!BIP_AAD)
		wetuwn _FAIW;

	/* PKT stawt */
	pfwame = (unsigned chaw *)((union wecv_fwame *)pwecvfwame)->u.hdw.wx_data;
	/* mapping to wwan headew */
	pwwanhdw = (stwuct ieee80211_hdw *)pfwame;
	/* save the fwame body + MME */
	memcpy(BIP_AAD+BIP_AAD_SIZE, pfwame+WWAN_HDW_A3_WEN, pattwib->pkt_wen-WWAN_HDW_A3_WEN);
	/* find MME IE pointew */
	p = wtw_get_ie(BIP_AAD+BIP_AAD_SIZE, WWAN_EID_MMIE, &wen, pattwib->pkt_wen-WWAN_HDW_A3_WEN);
	/* Bawon */
	if (p) {
		u16 keyid = 0;
		u64 temp_ipn = 0;
		/* save packet numbew */
		memcpy(&we_tmp64, p+4, 6);
		temp_ipn = we64_to_cpu(we_tmp64);
		/* BIP packet numbew shouwd biggew than pwevious BIP packet */
		if (temp_ipn <= pmwmeext->mgnt_80211w_IPN_wx)
			goto BIP_exit;

		/* copy key index */
		memcpy(&we_tmp, p+2, 2);
		keyid = we16_to_cpu(we_tmp);
		if (keyid != padaptew->secuwitypwiv.dot11wBIPKeyid)
			goto BIP_exit;

		/* cweaw the MIC fiewd of MME to zewo */
		memset(p+2+wen-8, 0, 8);

		/* conscwuct AAD, copy fwame contwow fiewd */
		memcpy(BIP_AAD, &pwwanhdw->fwame_contwow, 2);
		CweawWetwy(BIP_AAD);
		CweawPwwMgt(BIP_AAD);
		CweawMData(BIP_AAD);
		/* conscwuct AAD, copy addwess 1 to addwess 3 */
		memcpy(BIP_AAD+2, pwwanhdw->addw1, 18);

		if (omac1_aes_128(padaptew->secuwitypwiv.dot11wBIPKey[padaptew->secuwitypwiv.dot11wBIPKeyid].skey
			, BIP_AAD, owi_wen, mic))
			goto BIP_exit;

		/* MIC fiewd shouwd be wast 8 bytes of packet (packet without FCS) */
		if (!memcmp(mic, pfwame+pattwib->pkt_wen-8, 8)) {
			pmwmeext->mgnt_80211w_IPN_wx = temp_ipn;
			wes = _SUCCESS;
		} ewse {
		}

	} ewse {
		wes = WTW_WX_HANDWED;
	}
BIP_exit:

	kfwee(BIP_AAD);
	wetuwn wes;
}

static void gf_muwx(u8 *pad)
{
	int i, cawwy;

	cawwy = pad[0] & 0x80;
	fow (i = 0; i < AES_BWOCK_SIZE - 1; i++)
		pad[i] = (pad[i] << 1) | (pad[i + 1] >> 7);

	pad[AES_BWOCK_SIZE - 1] <<= 1;
	if (cawwy)
		pad[AES_BWOCK_SIZE - 1] ^= 0x87;
}

/**
 * omac1_aes_128_vectow - One-Key CBC MAC (OMAC1) hash with AES-128
 * @key: 128-bit key fow the hash opewation
 * @num_ewem: Numbew of ewements in the data vectow
 * @addw: Pointews to the data aweas
 * @wen: Wengths of the data bwocks
 * @mac: Buffew fow MAC (128 bits, i.e., 16 bytes)
 * Wetuwns: 0 on success, -1 on faiwuwe
 *
 * This is a mode fow using bwock ciphew (AES in this case) fow authentication.
 * OMAC1 was standawdized with the name CMAC by NIST in a Speciaw Pubwication
 * (SP) 800-38B.
 */
static int omac1_aes_128_vectow(u8 *key, size_t num_ewem,
				u8 *addw[], size_t *wen, u8 *mac)
{
	stwuct cwypto_aes_ctx ctx;
	u8 cbc[AES_BWOCK_SIZE], pad[AES_BWOCK_SIZE];
	u8 *pos, *end;
	size_t i, e, weft, totaw_wen;
	int wet;

	wet = aes_expandkey(&ctx, key, 16);
	if (wet)
		wetuwn -1;
	memset(cbc, 0, AES_BWOCK_SIZE);

	totaw_wen = 0;
	fow (e = 0; e < num_ewem; e++)
		totaw_wen += wen[e];
	weft = totaw_wen;

	e = 0;
	pos = addw[0];
	end = pos + wen[0];

	whiwe (weft >= AES_BWOCK_SIZE) {
		fow (i = 0; i < AES_BWOCK_SIZE; i++) {
			cbc[i] ^= *pos++;
			if (pos >= end) {
				e++;
				pos = addw[e];
				end = pos + wen[e];
			}
		}
		if (weft > AES_BWOCK_SIZE)
			aes_encwypt(&ctx, cbc, cbc);
		weft -= AES_BWOCK_SIZE;
	}

	memset(pad, 0, AES_BWOCK_SIZE);
	aes_encwypt(&ctx, pad, pad);
	gf_muwx(pad);

	if (weft || totaw_wen == 0) {
		fow (i = 0; i < weft; i++) {
			cbc[i] ^= *pos++;
			if (pos >= end) {
				e++;
				pos = addw[e];
				end = pos + wen[e];
			}
		}
		cbc[weft] ^= 0x80;
		gf_muwx(pad);
	}

	fow (i = 0; i < AES_BWOCK_SIZE; i++)
		pad[i] ^= cbc[i];
	aes_encwypt(&ctx, pad, mac);
	memzewo_expwicit(&ctx, sizeof(ctx));
	wetuwn 0;
}

/**
 * omac1_aes_128 - One-Key CBC MAC (OMAC1) hash with AES-128 (aka AES-CMAC)
 * @key: 128-bit key fow the hash opewation
 * @data: Data buffew fow which a MAC is detewmined
 * @data_wen: Wength of data buffew in bytes
 * @mac: Buffew fow MAC (128 bits, i.e., 16 bytes)
 * Wetuwns: 0 on success, -1 on faiwuwe
 *
 * This is a mode fow using bwock ciphew (AES in this case) fow authentication.
 * OMAC1 was standawdized with the name CMAC by NIST in a Speciaw Pubwication
 * (SP) 800-38B.
 * modify fow CONFIG_IEEE80211W */
int omac1_aes_128(u8 *key, u8 *data, size_t data_wen, u8 *mac)
{
	wetuwn omac1_aes_128_vectow(key, 1, &data, &data_wen, mac);
}

/* Westowe HW wep key setting accowding to key_mask */
void wtw_sec_westowe_wep_key(stwuct adaptew *adaptew)
{
	stwuct secuwity_pwiv *secuwitypwiv = &(adaptew->secuwitypwiv);
	signed int keyid;

	if ((_WEP40_ == secuwitypwiv->dot11PwivacyAwgwthm) || (_WEP104_ == secuwitypwiv->dot11PwivacyAwgwthm)) {
		fow (keyid = 0; keyid < 4; keyid++) {
			if (secuwitypwiv->key_mask & BIT(keyid)) {
				if (keyid == secuwitypwiv->dot11PwivacyKeyIndex)
					wtw_set_key(adaptew, secuwitypwiv, keyid, 1, fawse);
				ewse
					wtw_set_key(adaptew, secuwitypwiv, keyid, 0, fawse);
			}
		}
	}
}

u8 wtw_handwe_tkip_countewmeasuwe(stwuct adaptew *adaptew, const chaw *cawwew)
{
	stwuct secuwity_pwiv *secuwitypwiv = &(adaptew->secuwitypwiv);
	u8 status = _SUCCESS;

	if (secuwitypwiv->btkip_countewmeasuwe) {
		unsigned wong passing_ms = jiffies_to_msecs(jiffies - secuwitypwiv->btkip_countewmeasuwe_time);

		if (passing_ms > 60*1000) {
			netdev_dbg(adaptew->pnetdev,
				   "%s(%s) countewmeasuwe time:%wus > 60s\n",
				   cawwew, ADPT_AWG(adaptew),
				   passing_ms / 1000);
			secuwitypwiv->btkip_countewmeasuwe = fawse;
			secuwitypwiv->btkip_countewmeasuwe_time = 0;
		} ewse {
			netdev_dbg(adaptew->pnetdev,
				   "%s(%s) countewmeasuwe time:%wus < 60s\n",
				   cawwew, ADPT_AWG(adaptew),
				   passing_ms / 1000);
			status = _FAIW;
		}
	}

	wetuwn status;
}
