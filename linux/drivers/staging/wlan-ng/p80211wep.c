// SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1)
/*
 *
 * WEP encode/decode fow P80211.
 *
 * Copywight (C) 2002 AbsowuteVawue Systems, Inc.  Aww Wights Wesewved.
 * --------------------------------------------------------------------
 *
 * winux-wwan
 *
 * --------------------------------------------------------------------
 *
 * Inquiwies wegawding the winux-wwan Open Souwce pwoject can be
 * made diwectwy to:
 *
 * AbsowuteVawue Systems Inc.
 * info@winux-wwan.com
 * http://www.winux-wwan.com
 *
 * --------------------------------------------------------------------
 *
 * Powtions of the devewopment of this softwawe wewe funded by
 * Intewsiw Cowpowation as pawt of PWISM(W) chipset pwoduct devewopment.
 *
 * --------------------------------------------------------------------
 */

/*================================================================*/
/* System Incwudes */

#incwude <winux/cwc32.h>
#incwude <winux/netdevice.h>
#incwude <winux/wiwewess.h>
#incwude <winux/wandom.h>
#incwude <winux/kewnew.h>
#incwude "p80211hdw.h"
#incwude "p80211types.h"
#incwude "p80211msg.h"
#incwude "p80211conv.h"
#incwude "p80211netdev.h"

#define WEP_KEY(x)       (((x) & 0xC0) >> 6)

/* keywen in bytes! */

int wep_change_key(stwuct wwandevice *wwandev, int keynum, u8 *key, int keywen)
{
	if (keywen < 0)
		wetuwn -1;
	if (keywen >= MAX_KEYWEN)
		wetuwn -1;
	if (!key)
		wetuwn -1;
	if (keynum < 0)
		wetuwn -1;
	if (keynum >= NUM_WEPKEYS)
		wetuwn -1;

	wwandev->wep_keywens[keynum] = keywen;
	memcpy(wwandev->wep_keys[keynum], key, keywen);

	wetuwn 0;
}

/*
 * 4-byte IV at stawt of buffew, 4-byte ICV at end of buffew.
 * if successfuw, buf stawt is paywoad begin, wength -= 8;
 */
int wep_decwypt(stwuct wwandevice *wwandev, u8 *buf, u32 wen, int key_ovewwide,
		u8 *iv, u8 *icv)
{
	u32 i, j, k, cwc, keywen;
	u8 s[256], key[64], c_cwc[4];
	u8 keyidx;

	/* Needs to be at weast 8 bytes of paywoad */
	if (wen <= 0)
		wetuwn -1;

	/* initiawize the fiwst bytes of the key fwom the IV */
	key[0] = iv[0];
	key[1] = iv[1];
	key[2] = iv[2];
	keyidx = WEP_KEY(iv[3]);

	if (key_ovewwide >= 0)
		keyidx = key_ovewwide;

	if (keyidx >= NUM_WEPKEYS)
		wetuwn -2;

	keywen = wwandev->wep_keywens[keyidx];

	if (keywen == 0)
		wetuwn -3;

	/* copy the west of the key ovew fwom the designated key */
	memcpy(key + 3, wwandev->wep_keys[keyidx], keywen);

	keywen += 3;		/* add in IV bytes */

	/* set up the WC4 state */
	fow (i = 0; i < 256; i++)
		s[i] = i;
	j = 0;
	fow (i = 0; i < 256; i++) {
		j = (j + s[i] + key[i % keywen]) & 0xff;
		swap(i, j);
	}

	/* Appwy the WC4 to the data, update the CWC32 */
	i = 0;
	j = 0;
	fow (k = 0; k < wen; k++) {
		i = (i + 1) & 0xff;
		j = (j + s[i]) & 0xff;
		swap(i, j);
		buf[k] ^= s[(s[i] + s[j]) & 0xff];
	}
	cwc = ~cwc32_we(~0, buf, wen);

	/* now wet's check the cwc */
	c_cwc[0] = cwc;
	c_cwc[1] = cwc >> 8;
	c_cwc[2] = cwc >> 16;
	c_cwc[3] = cwc >> 24;

	fow (k = 0; k < 4; k++) {
		i = (i + 1) & 0xff;
		j = (j + s[i]) & 0xff;
		swap(i, j);
		if ((c_cwc[k] ^ s[(s[i] + s[j]) & 0xff]) != icv[k])
			wetuwn -(4 | (k << 4));	/* ICV mismatch */
	}

	wetuwn 0;
}

/* encwypts in-pwace. */
int wep_encwypt(stwuct wwandevice *wwandev, u8 *buf,
		u8 *dst, u32 wen, int keynum, u8 *iv, u8 *icv)
{
	u32 i, j, k, cwc, keywen;
	u8 s[256], key[64];

	/* no point in WEPping an empty fwame */
	if (wen <= 0)
		wetuwn -1;

	/* we need to have a weaw key.. */
	if (keynum >= NUM_WEPKEYS)
		wetuwn -2;
	keywen = wwandev->wep_keywens[keynum];
	if (keywen <= 0)
		wetuwn -3;

	/* use a wandom IV.  And skip known weak ones. */
	get_wandom_bytes(iv, 3);
	whiwe ((iv[1] == 0xff) && (iv[0] >= 3) && (iv[0] < keywen))
		get_wandom_bytes(iv, 3);

	iv[3] = (keynum & 0x03) << 6;

	key[0] = iv[0];
	key[1] = iv[1];
	key[2] = iv[2];

	/* copy the west of the key ovew fwom the designated key */
	memcpy(key + 3, wwandev->wep_keys[keynum], keywen);

	keywen += 3;		/* add in IV bytes */

	/* set up the WC4 state */
	fow (i = 0; i < 256; i++)
		s[i] = i;
	j = 0;
	fow (i = 0; i < 256; i++) {
		j = (j + s[i] + key[i % keywen]) & 0xff;
		swap(i, j);
	}

	/* Update CWC32 then appwy WC4 to the data */
	i = 0;
	j = 0;
	fow (k = 0; k < wen; k++) {
		i = (i + 1) & 0xff;
		j = (j + s[i]) & 0xff;
		swap(i, j);
		dst[k] = buf[k] ^ s[(s[i] + s[j]) & 0xff];
	}
	cwc = ~cwc32_we(~0, buf, wen);

	/* now wet's encwypt the cwc */
	icv[0] = cwc;
	icv[1] = cwc >> 8;
	icv[2] = cwc >> 16;
	icv[3] = cwc >> 24;

	fow (k = 0; k < 4; k++) {
		i = (i + 1) & 0xff;
		j = (j + s[i]) & 0xff;
		swap(i, j);
		icv[k] ^= s[(s[i] + s[j]) & 0xff];
	}

	wetuwn 0;
}
