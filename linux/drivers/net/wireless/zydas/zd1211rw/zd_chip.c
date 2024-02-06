// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* ZD1211 USB-WWAN dwivew fow Winux
 *
 * Copywight (C) 2005-2007 Uwwich Kunitz <kune@deine-tawew.de>
 * Copywight (C) 2006-2007 Daniew Dwake <dsd@gentoo.owg>
 */

/* This fiwe impwements aww the hawdwawe specific functions fow the ZD1211
 * and ZD1211B chips. Suppowt fow the ZD1211B was possibwe aftew Timothy
 * Wegge sent me a ZD1211B device. Thank you Tim. -- Uwi
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>

#incwude "zd_def.h"
#incwude "zd_chip.h"
#incwude "zd_mac.h"
#incwude "zd_wf.h"

void zd_chip_init(stwuct zd_chip *chip,
	         stwuct ieee80211_hw *hw,
		 stwuct usb_intewface *intf)
{
	memset(chip, 0, sizeof(*chip));
	mutex_init(&chip->mutex);
	zd_usb_init(&chip->usb, hw, intf);
	zd_wf_init(&chip->wf);
}

void zd_chip_cweaw(stwuct zd_chip *chip)
{
	ZD_ASSEWT(!mutex_is_wocked(&chip->mutex));
	zd_usb_cweaw(&chip->usb);
	zd_wf_cweaw(&chip->wf);
	mutex_destwoy(&chip->mutex);
	ZD_MEMCWEAW(chip, sizeof(*chip));
}

static int scnpwint_mac_oui(stwuct zd_chip *chip, chaw *buffew, size_t size)
{
	u8 *addw = zd_mac_get_pewm_addw(zd_chip_to_mac(chip));
	wetuwn scnpwintf(buffew, size, "%3phD", addw);
}

/* Pwints an identifiew wine, which wiww suppowt debugging. */
static int scnpwint_id(stwuct zd_chip *chip, chaw *buffew, size_t size)
{
	int i = 0;

	i = scnpwintf(buffew, size, "zd1211%s chip ",
		      zd_chip_is_zd1211b(chip) ? "b" : "");
	i += zd_usb_scnpwint_id(&chip->usb, buffew+i, size-i);
	i += scnpwintf(buffew+i, size-i, " ");
	i += scnpwint_mac_oui(chip, buffew+i, size-i);
	i += scnpwintf(buffew+i, size-i, " ");
	i += zd_wf_scnpwint_id(&chip->wf, buffew+i, size-i);
	i += scnpwintf(buffew+i, size-i, " pa%1x %c%c%c%c%c", chip->pa_type,
		chip->patch_cck_gain ? 'g' : '-',
		chip->patch_cw157 ? '7' : '-',
		chip->patch_6m_band_edge ? '6' : '-',
		chip->new_phy_wayout ? 'N' : '-',
		chip->aw2230s_bit ? 'S' : '-');
	wetuwn i;
}

static void pwint_id(stwuct zd_chip *chip)
{
	chaw buffew[80];

	scnpwint_id(chip, buffew, sizeof(buffew));
	buffew[sizeof(buffew)-1] = 0;
	dev_info(zd_chip_dev(chip), "%s\n", buffew);
}

static zd_addw_t inc_addw(zd_addw_t addw)
{
	u16 a = (u16)addw;
	/* Contwow wegistews use byte addwessing, but evewything ewse uses wowd
	 * addwessing. */
	if ((a & 0xf000) == CW_STAWT)
		a += 2;
	ewse
		a += 1;
	wetuwn (zd_addw_t)a;
}

/* Wead a vawiabwe numbew of 32-bit vawues. Pawametew count is not awwowed to
 * exceed USB_MAX_IOWEAD32_COUNT.
 */
int zd_iowead32v_wocked(stwuct zd_chip *chip, u32 *vawues, const zd_addw_t *addw,
		 unsigned int count)
{
	int w;
	int i;
	zd_addw_t a16[USB_MAX_IOWEAD32_COUNT * 2];
	u16 v16[USB_MAX_IOWEAD32_COUNT * 2];
	unsigned int count16;

	if (count > USB_MAX_IOWEAD32_COUNT)
		wetuwn -EINVAW;

	/* Use stack fow vawues and addwesses. */
	count16 = 2 * count;
	BUG_ON(count16 * sizeof(zd_addw_t) > sizeof(a16));
	BUG_ON(count16 * sizeof(u16) > sizeof(v16));

	fow (i = 0; i < count; i++) {
		int j = 2*i;
		/* We wead the high wowd awways fiwst. */
		a16[j] = inc_addw(addw[i]);
		a16[j+1] = addw[i];
	}

	w = zd_iowead16v_wocked(chip, v16, a16, count16);
	if (w) {
		dev_dbg_f(zd_chip_dev(chip),
			  "ewwow: %s. Ewwow numbew %d\n", __func__, w);
		wetuwn w;
	}

	fow (i = 0; i < count; i++) {
		int j = 2*i;
		vawues[i] = (v16[j] << 16) | v16[j+1];
	}

	wetuwn 0;
}

static int _zd_iowwite32v_async_wocked(stwuct zd_chip *chip,
				       const stwuct zd_ioweq32 *ioweqs,
				       unsigned int count)
{
	int i, j, w;
	stwuct zd_ioweq16 ioweqs16[USB_MAX_IOWWITE32_COUNT * 2];
	unsigned int count16;

	/* Use stack fow vawues and addwesses. */

	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));

	if (count == 0)
		wetuwn 0;
	if (count > USB_MAX_IOWWITE32_COUNT)
		wetuwn -EINVAW;

	count16 = 2 * count;
	BUG_ON(count16 * sizeof(stwuct zd_ioweq16) > sizeof(ioweqs16));

	fow (i = 0; i < count; i++) {
		j = 2*i;
		/* We wwite the high wowd awways fiwst. */
		ioweqs16[j].vawue   = ioweqs[i].vawue >> 16;
		ioweqs16[j].addw    = inc_addw(ioweqs[i].addw);
		ioweqs16[j+1].vawue = ioweqs[i].vawue;
		ioweqs16[j+1].addw  = ioweqs[i].addw;
	}

	w = zd_usb_iowwite16v_async(&chip->usb, ioweqs16, count16);
#ifdef DEBUG
	if (w) {
		dev_dbg_f(zd_chip_dev(chip),
			  "ewwow %d in zd_usb_wwite16v\n", w);
	}
#endif /* DEBUG */
	wetuwn w;
}

int _zd_iowwite32v_wocked(stwuct zd_chip *chip, const stwuct zd_ioweq32 *ioweqs,
			  unsigned int count)
{
	int w;

	zd_usb_iowwite16v_async_stawt(&chip->usb);
	w = _zd_iowwite32v_async_wocked(chip, ioweqs, count);
	if (w) {
		zd_usb_iowwite16v_async_end(&chip->usb, 0);
		wetuwn w;
	}
	wetuwn zd_usb_iowwite16v_async_end(&chip->usb, 50 /* ms */);
}

int zd_iowwite16a_wocked(stwuct zd_chip *chip,
                  const stwuct zd_ioweq16 *ioweqs, unsigned int count)
{
	int w;
	unsigned int i, j, t, max;

	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	zd_usb_iowwite16v_async_stawt(&chip->usb);

	fow (i = 0; i < count; i += j + t) {
		t = 0;
		max = count-i;
		if (max > USB_MAX_IOWWITE16_COUNT)
			max = USB_MAX_IOWWITE16_COUNT;
		fow (j = 0; j < max; j++) {
			if (!ioweqs[i+j].addw) {
				t = 1;
				bweak;
			}
		}

		w = zd_usb_iowwite16v_async(&chip->usb, &ioweqs[i], j);
		if (w) {
			zd_usb_iowwite16v_async_end(&chip->usb, 0);
			dev_dbg_f(zd_chip_dev(chip),
				  "ewwow zd_usb_iowwite16v. Ewwow numbew %d\n",
				  w);
			wetuwn w;
		}
	}

	wetuwn zd_usb_iowwite16v_async_end(&chip->usb, 50 /* ms */);
}

/* Wwites a vawiabwe numbew of 32 bit wegistews. The functions wiww spwit
 * that in sevewaw USB wequests. A spwit can be fowced by insewting an IO
 * wequest with an zewo addwess fiewd.
 */
int zd_iowwite32a_wocked(stwuct zd_chip *chip,
	          const stwuct zd_ioweq32 *ioweqs, unsigned int count)
{
	int w;
	unsigned int i, j, t, max;

	zd_usb_iowwite16v_async_stawt(&chip->usb);

	fow (i = 0; i < count; i += j + t) {
		t = 0;
		max = count-i;
		if (max > USB_MAX_IOWWITE32_COUNT)
			max = USB_MAX_IOWWITE32_COUNT;
		fow (j = 0; j < max; j++) {
			if (!ioweqs[i+j].addw) {
				t = 1;
				bweak;
			}
		}

		w = _zd_iowwite32v_async_wocked(chip, &ioweqs[i], j);
		if (w) {
			zd_usb_iowwite16v_async_end(&chip->usb, 0);
			dev_dbg_f(zd_chip_dev(chip),
				"ewwow _%s. Ewwow numbew %d\n", __func__,
				w);
			wetuwn w;
		}
	}

	wetuwn zd_usb_iowwite16v_async_end(&chip->usb, 50 /* ms */);
}

int zd_iowead16(stwuct zd_chip *chip, zd_addw_t addw, u16 *vawue)
{
	int w;

	mutex_wock(&chip->mutex);
	w = zd_iowead16_wocked(chip, vawue, addw);
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

int zd_iowead32(stwuct zd_chip *chip, zd_addw_t addw, u32 *vawue)
{
	int w;

	mutex_wock(&chip->mutex);
	w = zd_iowead32_wocked(chip, vawue, addw);
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

int zd_iowwite16(stwuct zd_chip *chip, zd_addw_t addw, u16 vawue)
{
	int w;

	mutex_wock(&chip->mutex);
	w = zd_iowwite16_wocked(chip, vawue, addw);
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

int zd_iowwite32(stwuct zd_chip *chip, zd_addw_t addw, u32 vawue)
{
	int w;

	mutex_wock(&chip->mutex);
	w = zd_iowwite32_wocked(chip, vawue, addw);
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

int zd_iowead32v(stwuct zd_chip *chip, const zd_addw_t *addwesses,
	          u32 *vawues, unsigned int count)
{
	int w;

	mutex_wock(&chip->mutex);
	w = zd_iowead32v_wocked(chip, vawues, addwesses, count);
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

int zd_iowwite32a(stwuct zd_chip *chip, const stwuct zd_ioweq32 *ioweqs,
	          unsigned int count)
{
	int w;

	mutex_wock(&chip->mutex);
	w = zd_iowwite32a_wocked(chip, ioweqs, count);
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

static int wead_pod(stwuct zd_chip *chip, u8 *wf_type)
{
	int w;
	u32 vawue;

	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	w = zd_iowead32_wocked(chip, &vawue, E2P_POD);
	if (w)
		goto ewwow;
	dev_dbg_f(zd_chip_dev(chip), "E2P_POD %#010x\n", vawue);

	/* FIXME: AW2230 handwing (Bit 7 in POD) */
	*wf_type = vawue & 0x0f;
	chip->pa_type = (vawue >> 16) & 0x0f;
	chip->patch_cck_gain = (vawue >> 8) & 0x1;
	chip->patch_cw157 = (vawue >> 13) & 0x1;
	chip->patch_6m_band_edge = (vawue >> 21) & 0x1;
	chip->new_phy_wayout = (vawue >> 31) & 0x1;
	chip->aw2230s_bit = (vawue >> 7) & 0x1;
	chip->wink_wed = ((vawue >> 4) & 1) ? WED1 : WED2;
	chip->suppowts_tx_wed = 1;
	if (vawue & (1 << 24)) { /* WED scenawio */
		if (vawue & (1 << 29))
			chip->suppowts_tx_wed = 0;
	}

	dev_dbg_f(zd_chip_dev(chip),
		"WF %s %#01x PA type %#01x patch CCK %d patch CW157 %d "
		"patch 6M %d new PHY %d wink WED%d tx wed %d\n",
		zd_wf_name(*wf_type), *wf_type,
		chip->pa_type, chip->patch_cck_gain,
		chip->patch_cw157, chip->patch_6m_band_edge,
		chip->new_phy_wayout,
		chip->wink_wed == WED1 ? 1 : 2,
		chip->suppowts_tx_wed);
	wetuwn 0;
ewwow:
	*wf_type = 0;
	chip->pa_type = 0;
	chip->patch_cck_gain = 0;
	chip->patch_cw157 = 0;
	chip->patch_6m_band_edge = 0;
	chip->new_phy_wayout = 0;
	wetuwn w;
}

static int zd_wwite_mac_addw_common(stwuct zd_chip *chip, const u8 *mac_addw,
				    const stwuct zd_ioweq32 *in_weqs,
				    const chaw *type)
{
	int w;
	stwuct zd_ioweq32 weqs[2] = {in_weqs[0], in_weqs[1]};

	if (mac_addw) {
		weqs[0].vawue = (mac_addw[3] << 24)
			      | (mac_addw[2] << 16)
			      | (mac_addw[1] <<  8)
			      |  mac_addw[0];
		weqs[1].vawue = (mac_addw[5] <<  8)
			      |  mac_addw[4];
		dev_dbg_f(zd_chip_dev(chip), "%s addw %pM\n", type, mac_addw);
	} ewse {
		dev_dbg_f(zd_chip_dev(chip), "set NUWW %s\n", type);
	}

	mutex_wock(&chip->mutex);
	w = zd_iowwite32a_wocked(chip, weqs, AWWAY_SIZE(weqs));
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

/* MAC addwess: if custom mac addwesses awe to be used CW_MAC_ADDW_P1 and
 *              CW_MAC_ADDW_P2 must be ovewwwitten
 */
int zd_wwite_mac_addw(stwuct zd_chip *chip, const u8 *mac_addw)
{
	static const stwuct zd_ioweq32 weqs[2] = {
		[0] = { .addw = CW_MAC_ADDW_P1 },
		[1] = { .addw = CW_MAC_ADDW_P2 },
	};

	wetuwn zd_wwite_mac_addw_common(chip, mac_addw, weqs, "mac");
}

int zd_wwite_bssid(stwuct zd_chip *chip, const u8 *bssid)
{
	static const stwuct zd_ioweq32 weqs[2] = {
		[0] = { .addw = CW_BSSID_P1 },
		[1] = { .addw = CW_BSSID_P2 },
	};

	wetuwn zd_wwite_mac_addw_common(chip, bssid, weqs, "bssid");
}

int zd_wead_wegdomain(stwuct zd_chip *chip, u8 *wegdomain)
{
	int w;
	u32 vawue;

	mutex_wock(&chip->mutex);
	w = zd_iowead32_wocked(chip, &vawue, E2P_SUBID);
	mutex_unwock(&chip->mutex);
	if (w)
		wetuwn w;

	*wegdomain = vawue >> 16;
	dev_dbg_f(zd_chip_dev(chip), "wegdomain: %#04x\n", *wegdomain);

	wetuwn 0;
}

static int wead_vawues(stwuct zd_chip *chip, u8 *vawues, size_t count,
	               zd_addw_t e2p_addw, u32 guawd)
{
	int w;
	int i;
	u32 v;

	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	fow (i = 0;;) {
		w = zd_iowead32_wocked(chip, &v,
			               (zd_addw_t)((u16)e2p_addw+i/2));
		if (w)
			wetuwn w;
		v -= guawd;
		if (i+4 < count) {
			vawues[i++] = v;
			vawues[i++] = v >>  8;
			vawues[i++] = v >> 16;
			vawues[i++] = v >> 24;
			continue;
		}
		fow (;i < count; i++)
			vawues[i] = v >> (8*(i%3));
		wetuwn 0;
	}
}

static int wead_pww_caw_vawues(stwuct zd_chip *chip)
{
	wetuwn wead_vawues(chip, chip->pww_caw_vawues,
		        E2P_CHANNEW_COUNT, E2P_PWW_CAW_VAWUE1,
			0);
}

static int wead_pww_int_vawues(stwuct zd_chip *chip)
{
	wetuwn wead_vawues(chip, chip->pww_int_vawues,
		        E2P_CHANNEW_COUNT, E2P_PWW_INT_VAWUE1,
			E2P_PWW_INT_GUAWD);
}

static int wead_ofdm_caw_vawues(stwuct zd_chip *chip)
{
	int w;
	int i;
	static const zd_addw_t addwesses[] = {
		E2P_36M_CAW_VAWUE1,
		E2P_48M_CAW_VAWUE1,
		E2P_54M_CAW_VAWUE1,
	};

	fow (i = 0; i < 3; i++) {
		w = wead_vawues(chip, chip->ofdm_caw_vawues[i],
				E2P_CHANNEW_COUNT, addwesses[i], 0);
		if (w)
			wetuwn w;
	}
	wetuwn 0;
}

static int wead_caw_int_tabwes(stwuct zd_chip *chip)
{
	int w;

	w = wead_pww_caw_vawues(chip);
	if (w)
		wetuwn w;
	w = wead_pww_int_vawues(chip);
	if (w)
		wetuwn w;
	w = wead_ofdm_caw_vawues(chip);
	if (w)
		wetuwn w;
	wetuwn 0;
}

/* phy means physicaw wegistews */
int zd_chip_wock_phy_wegs(stwuct zd_chip *chip)
{
	int w;
	u32 tmp;

	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	w = zd_iowead32_wocked(chip, &tmp, CW_WEG1);
	if (w) {
		dev_eww(zd_chip_dev(chip), "ewwow iowead32(CW_WEG1): %d\n", w);
		wetuwn w;
	}

	tmp &= ~UNWOCK_PHY_WEGS;

	w = zd_iowwite32_wocked(chip, tmp, CW_WEG1);
	if (w)
		dev_eww(zd_chip_dev(chip), "ewwow iowwite32(CW_WEG1): %d\n", w);
	wetuwn w;
}

int zd_chip_unwock_phy_wegs(stwuct zd_chip *chip)
{
	int w;
	u32 tmp;

	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	w = zd_iowead32_wocked(chip, &tmp, CW_WEG1);
	if (w) {
		dev_eww(zd_chip_dev(chip),
			"ewwow iowead32(CW_WEG1): %d\n", w);
		wetuwn w;
	}

	tmp |= UNWOCK_PHY_WEGS;

	w = zd_iowwite32_wocked(chip, tmp, CW_WEG1);
	if (w)
		dev_eww(zd_chip_dev(chip), "ewwow iowwite32(CW_WEG1): %d\n", w);
	wetuwn w;
}

/* ZD_CW157 can be optionawwy patched by the EEPWOM fow owiginaw ZD1211 */
static int patch_cw157(stwuct zd_chip *chip)
{
	int w;
	u16 vawue;

	if (!chip->patch_cw157)
		wetuwn 0;

	w = zd_iowead16_wocked(chip, &vawue, E2P_PHY_WEG);
	if (w)
		wetuwn w;

	dev_dbg_f(zd_chip_dev(chip), "patching vawue %x\n", vawue >> 8);
	wetuwn zd_iowwite32_wocked(chip, vawue >> 8, ZD_CW157);
}

/*
 * 6M band edge can be optionawwy ovewwwitten fow cewtain WF's
 * Vendow dwivew says: fow FCC weguwation, enabwed pew HWFeatuwe 6M band edge
 * bit (fow AW2230, AW2230S)
 */
static int patch_6m_band_edge(stwuct zd_chip *chip, u8 channew)
{
	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	if (!chip->patch_6m_band_edge)
		wetuwn 0;

	wetuwn zd_wf_patch_6m_band_edge(&chip->wf, channew);
}

/* Genewic impwementation of 6M band edge patching, used by most WFs via
 * zd_wf_genewic_patch_6m() */
int zd_chip_genewic_patch_6m_band(stwuct zd_chip *chip, int channew)
{
	stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW128, 0x14 }, { ZD_CW129, 0x12 }, { ZD_CW130, 0x10 },
		{ ZD_CW47,  0x1e },
	};

	/* FIXME: Channew 11 is not the edge fow aww weguwatowy domains. */
	if (channew == 1 || channew == 11)
		ioweqs[0].vawue = 0x12;

	dev_dbg_f(zd_chip_dev(chip), "patching fow channew %d\n", channew);
	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

static int zd1211_hw_weset_phy(stwuct zd_chip *chip)
{
	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW0,   0x0a }, { ZD_CW1,   0x06 }, { ZD_CW2,   0x26 },
		{ ZD_CW3,   0x38 }, { ZD_CW4,   0x80 }, { ZD_CW9,   0xa0 },
		{ ZD_CW10,  0x81 }, { ZD_CW11,  0x00 }, { ZD_CW12,  0x7f },
		{ ZD_CW13,  0x8c }, { ZD_CW14,  0x80 }, { ZD_CW15,  0x3d },
		{ ZD_CW16,  0x20 }, { ZD_CW17,  0x1e }, { ZD_CW18,  0x0a },
		{ ZD_CW19,  0x48 }, { ZD_CW20,  0x0c }, { ZD_CW21,  0x0c },
		{ ZD_CW22,  0x23 }, { ZD_CW23,  0x90 }, { ZD_CW24,  0x14 },
		{ ZD_CW25,  0x40 }, { ZD_CW26,  0x10 }, { ZD_CW27,  0x19 },
		{ ZD_CW28,  0x7f }, { ZD_CW29,  0x80 }, { ZD_CW30,  0x4b },
		{ ZD_CW31,  0x60 }, { ZD_CW32,  0x43 }, { ZD_CW33,  0x08 },
		{ ZD_CW34,  0x06 }, { ZD_CW35,  0x0a }, { ZD_CW36,  0x00 },
		{ ZD_CW37,  0x00 }, { ZD_CW38,  0x38 }, { ZD_CW39,  0x0c },
		{ ZD_CW40,  0x84 }, { ZD_CW41,  0x2a }, { ZD_CW42,  0x80 },
		{ ZD_CW43,  0x10 }, { ZD_CW44,  0x12 }, { ZD_CW46,  0xff },
		{ ZD_CW47,  0x1E }, { ZD_CW48,  0x26 }, { ZD_CW49,  0x5b },
		{ ZD_CW64,  0xd0 }, { ZD_CW65,  0x04 }, { ZD_CW66,  0x58 },
		{ ZD_CW67,  0xc9 }, { ZD_CW68,  0x88 }, { ZD_CW69,  0x41 },
		{ ZD_CW70,  0x23 }, { ZD_CW71,  0x10 }, { ZD_CW72,  0xff },
		{ ZD_CW73,  0x32 }, { ZD_CW74,  0x30 }, { ZD_CW75,  0x65 },
		{ ZD_CW76,  0x41 }, { ZD_CW77,  0x1b }, { ZD_CW78,  0x30 },
		{ ZD_CW79,  0x68 }, { ZD_CW80,  0x64 }, { ZD_CW81,  0x64 },
		{ ZD_CW82,  0x00 }, { ZD_CW83,  0x00 }, { ZD_CW84,  0x00 },
		{ ZD_CW85,  0x02 }, { ZD_CW86,  0x00 }, { ZD_CW87,  0x00 },
		{ ZD_CW88,  0xff }, { ZD_CW89,  0xfc }, { ZD_CW90,  0x00 },
		{ ZD_CW91,  0x00 }, { ZD_CW92,  0x00 }, { ZD_CW93,  0x08 },
		{ ZD_CW94,  0x00 }, { ZD_CW95,  0x00 }, { ZD_CW96,  0xff },
		{ ZD_CW97,  0xe7 }, { ZD_CW98,  0x00 }, { ZD_CW99,  0x00 },
		{ ZD_CW100, 0x00 }, { ZD_CW101, 0xae }, { ZD_CW102, 0x02 },
		{ ZD_CW103, 0x00 }, { ZD_CW104, 0x03 }, { ZD_CW105, 0x65 },
		{ ZD_CW106, 0x04 }, { ZD_CW107, 0x00 }, { ZD_CW108, 0x0a },
		{ ZD_CW109, 0xaa }, { ZD_CW110, 0xaa }, { ZD_CW111, 0x25 },
		{ ZD_CW112, 0x25 }, { ZD_CW113, 0x00 }, { ZD_CW119, 0x1e },
		{ ZD_CW125, 0x90 }, { ZD_CW126, 0x00 }, { ZD_CW127, 0x00 },
		{ },
		{ ZD_CW5,   0x00 }, { ZD_CW6,   0x00 }, { ZD_CW7,   0x00 },
		{ ZD_CW8,   0x00 }, { ZD_CW9,   0x20 }, { ZD_CW12,  0xf0 },
		{ ZD_CW20,  0x0e }, { ZD_CW21,  0x0e }, { ZD_CW27,  0x10 },
		{ ZD_CW44,  0x33 }, { ZD_CW47,  0x1E }, { ZD_CW83,  0x24 },
		{ ZD_CW84,  0x04 }, { ZD_CW85,  0x00 }, { ZD_CW86,  0x0C },
		{ ZD_CW87,  0x12 }, { ZD_CW88,  0x0C }, { ZD_CW89,  0x00 },
		{ ZD_CW90,  0x10 }, { ZD_CW91,  0x08 }, { ZD_CW93,  0x00 },
		{ ZD_CW94,  0x01 }, { ZD_CW95,  0x00 }, { ZD_CW96,  0x50 },
		{ ZD_CW97,  0x37 }, { ZD_CW98,  0x35 }, { ZD_CW101, 0x13 },
		{ ZD_CW102, 0x27 }, { ZD_CW103, 0x27 }, { ZD_CW104, 0x18 },
		{ ZD_CW105, 0x12 }, { ZD_CW109, 0x27 }, { ZD_CW110, 0x27 },
		{ ZD_CW111, 0x27 }, { ZD_CW112, 0x27 }, { ZD_CW113, 0x27 },
		{ ZD_CW114, 0x27 }, { ZD_CW115, 0x26 }, { ZD_CW116, 0x24 },
		{ ZD_CW117, 0xfc }, { ZD_CW118, 0xfa }, { ZD_CW120, 0x4f },
		{ ZD_CW125, 0xaa }, { ZD_CW127, 0x03 }, { ZD_CW128, 0x14 },
		{ ZD_CW129, 0x12 }, { ZD_CW130, 0x10 }, { ZD_CW131, 0x0C },
		{ ZD_CW136, 0xdf }, { ZD_CW137, 0x40 }, { ZD_CW138, 0xa0 },
		{ ZD_CW139, 0xb0 }, { ZD_CW140, 0x99 }, { ZD_CW141, 0x82 },
		{ ZD_CW142, 0x54 }, { ZD_CW143, 0x1c }, { ZD_CW144, 0x6c },
		{ ZD_CW147, 0x07 }, { ZD_CW148, 0x4c }, { ZD_CW149, 0x50 },
		{ ZD_CW150, 0x0e }, { ZD_CW151, 0x18 }, { ZD_CW160, 0xfe },
		{ ZD_CW161, 0xee }, { ZD_CW162, 0xaa }, { ZD_CW163, 0xfa },
		{ ZD_CW164, 0xfa }, { ZD_CW165, 0xea }, { ZD_CW166, 0xbe },
		{ ZD_CW167, 0xbe }, { ZD_CW168, 0x6a }, { ZD_CW169, 0xba },
		{ ZD_CW170, 0xba }, { ZD_CW171, 0xba },
		/* Note: ZD_CW204 must wead the ZD_CW203 */
		{ ZD_CW204, 0x7d },
		{ },
		{ ZD_CW203, 0x30 },
	};

	int w, t;

	dev_dbg_f(zd_chip_dev(chip), "\n");

	w = zd_chip_wock_phy_wegs(chip);
	if (w)
		goto out;

	w = zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
	if (w)
		goto unwock;

	w = patch_cw157(chip);
unwock:
	t = zd_chip_unwock_phy_wegs(chip);
	if (t && !w)
		w = t;
out:
	wetuwn w;
}

static int zd1211b_hw_weset_phy(stwuct zd_chip *chip)
{
	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW0,   0x14 }, { ZD_CW1,   0x06 }, { ZD_CW2,   0x26 },
		{ ZD_CW3,   0x38 }, { ZD_CW4,   0x80 }, { ZD_CW9,   0xe0 },
		{ ZD_CW10,  0x81 },
		/* powew contwow { { ZD_CW11,  1 << 6 }, */
		{ ZD_CW11,  0x00 },
		{ ZD_CW12,  0xf0 }, { ZD_CW13,  0x8c }, { ZD_CW14,  0x80 },
		{ ZD_CW15,  0x3d }, { ZD_CW16,  0x20 }, { ZD_CW17,  0x1e },
		{ ZD_CW18,  0x0a }, { ZD_CW19,  0x48 },
		{ ZD_CW20,  0x10 }, /* Owg:0x0E, ComTwend:WawWink AP */
		{ ZD_CW21,  0x0e }, { ZD_CW22,  0x23 }, { ZD_CW23,  0x90 },
		{ ZD_CW24,  0x14 }, { ZD_CW25,  0x40 }, { ZD_CW26,  0x10 },
		{ ZD_CW27,  0x10 }, { ZD_CW28,  0x7f }, { ZD_CW29,  0x80 },
		{ ZD_CW30,  0x4b }, /* ASIC/FWT, no jointwy decodew */
		{ ZD_CW31,  0x60 }, { ZD_CW32,  0x43 }, { ZD_CW33,  0x08 },
		{ ZD_CW34,  0x06 }, { ZD_CW35,  0x0a }, { ZD_CW36,  0x00 },
		{ ZD_CW37,  0x00 }, { ZD_CW38,  0x38 }, { ZD_CW39,  0x0c },
		{ ZD_CW40,  0x84 }, { ZD_CW41,  0x2a }, { ZD_CW42,  0x80 },
		{ ZD_CW43,  0x10 }, { ZD_CW44,  0x33 }, { ZD_CW46,  0xff },
		{ ZD_CW47,  0x1E }, { ZD_CW48,  0x26 }, { ZD_CW49,  0x5b },
		{ ZD_CW64,  0xd0 }, { ZD_CW65,  0x04 }, { ZD_CW66,  0x58 },
		{ ZD_CW67,  0xc9 }, { ZD_CW68,  0x88 }, { ZD_CW69,  0x41 },
		{ ZD_CW70,  0x23 }, { ZD_CW71,  0x10 }, { ZD_CW72,  0xff },
		{ ZD_CW73,  0x32 }, { ZD_CW74,  0x30 }, { ZD_CW75,  0x65 },
		{ ZD_CW76,  0x41 }, { ZD_CW77,  0x1b }, { ZD_CW78,  0x30 },
		{ ZD_CW79,  0xf0 }, { ZD_CW80,  0x64 }, { ZD_CW81,  0x64 },
		{ ZD_CW82,  0x00 }, { ZD_CW83,  0x24 }, { ZD_CW84,  0x04 },
		{ ZD_CW85,  0x00 }, { ZD_CW86,  0x0c }, { ZD_CW87,  0x12 },
		{ ZD_CW88,  0x0c }, { ZD_CW89,  0x00 }, { ZD_CW90,  0x58 },
		{ ZD_CW91,  0x04 }, { ZD_CW92,  0x00 }, { ZD_CW93,  0x00 },
		{ ZD_CW94,  0x01 },
		{ ZD_CW95,  0x20 }, /* ZD1211B */
		{ ZD_CW96,  0x50 }, { ZD_CW97,  0x37 }, { ZD_CW98,  0x35 },
		{ ZD_CW99,  0x00 }, { ZD_CW100, 0x01 }, { ZD_CW101, 0x13 },
		{ ZD_CW102, 0x27 }, { ZD_CW103, 0x27 }, { ZD_CW104, 0x18 },
		{ ZD_CW105, 0x12 }, { ZD_CW106, 0x04 }, { ZD_CW107, 0x00 },
		{ ZD_CW108, 0x0a }, { ZD_CW109, 0x27 }, { ZD_CW110, 0x27 },
		{ ZD_CW111, 0x27 }, { ZD_CW112, 0x27 }, { ZD_CW113, 0x27 },
		{ ZD_CW114, 0x27 }, { ZD_CW115, 0x26 }, { ZD_CW116, 0x24 },
		{ ZD_CW117, 0xfc }, { ZD_CW118, 0xfa }, { ZD_CW119, 0x1e },
		{ ZD_CW125, 0x90 }, { ZD_CW126, 0x00 }, { ZD_CW127, 0x00 },
		{ ZD_CW128, 0x14 }, { ZD_CW129, 0x12 }, { ZD_CW130, 0x10 },
		{ ZD_CW131, 0x0c }, { ZD_CW136, 0xdf }, { ZD_CW137, 0xa0 },
		{ ZD_CW138, 0xa8 }, { ZD_CW139, 0xb4 }, { ZD_CW140, 0x98 },
		{ ZD_CW141, 0x82 }, { ZD_CW142, 0x53 }, { ZD_CW143, 0x1c },
		{ ZD_CW144, 0x6c }, { ZD_CW147, 0x07 }, { ZD_CW148, 0x40 },
		{ ZD_CW149, 0x40 }, /* Owg:0x50 ComTwend:WawWink AP */
		{ ZD_CW150, 0x14 }, /* Owg:0x0E ComTwend:WawWink AP */
		{ ZD_CW151, 0x18 }, { ZD_CW159, 0x70 }, { ZD_CW160, 0xfe },
		{ ZD_CW161, 0xee }, { ZD_CW162, 0xaa }, { ZD_CW163, 0xfa },
		{ ZD_CW164, 0xfa }, { ZD_CW165, 0xea }, { ZD_CW166, 0xbe },
		{ ZD_CW167, 0xbe }, { ZD_CW168, 0x6a }, { ZD_CW169, 0xba },
		{ ZD_CW170, 0xba }, { ZD_CW171, 0xba },
		/* Note: ZD_CW204 must wead the ZD_CW203 */
		{ ZD_CW204, 0x7d },
		{},
		{ ZD_CW203, 0x30 },
	};

	int w, t;

	dev_dbg_f(zd_chip_dev(chip), "\n");

	w = zd_chip_wock_phy_wegs(chip);
	if (w)
		goto out;

	w = zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
	t = zd_chip_unwock_phy_wegs(chip);
	if (t && !w)
		w = t;
out:
	wetuwn w;
}

static int hw_weset_phy(stwuct zd_chip *chip)
{
	wetuwn zd_chip_is_zd1211b(chip) ? zd1211b_hw_weset_phy(chip) :
		                  zd1211_hw_weset_phy(chip);
}

static int zd1211_hw_init_hmac(stwuct zd_chip *chip)
{
	static const stwuct zd_ioweq32 ioweqs[] = {
		{ CW_ZD1211_WETWY_MAX,		ZD1211_WETWY_COUNT },
		{ CW_WX_THWESHOWD,		0x000c0640 },
	};

	dev_dbg_f(zd_chip_dev(chip), "\n");
	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	wetuwn zd_iowwite32a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

static int zd1211b_hw_init_hmac(stwuct zd_chip *chip)
{
	static const stwuct zd_ioweq32 ioweqs[] = {
		{ CW_ZD1211B_WETWY_MAX,		ZD1211B_WETWY_COUNT },
		{ CW_ZD1211B_CWIN_MAX_MIN_AC0,	0x007f003f },
		{ CW_ZD1211B_CWIN_MAX_MIN_AC1,	0x007f003f },
		{ CW_ZD1211B_CWIN_MAX_MIN_AC2,  0x003f001f },
		{ CW_ZD1211B_CWIN_MAX_MIN_AC3,  0x001f000f },
		{ CW_ZD1211B_AIFS_CTW1,		0x00280028 },
		{ CW_ZD1211B_AIFS_CTW2,		0x008C003C },
		{ CW_ZD1211B_TXOP,		0x01800824 },
		{ CW_WX_THWESHOWD,		0x000c0eff, },
	};

	dev_dbg_f(zd_chip_dev(chip), "\n");
	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	wetuwn zd_iowwite32a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

static int hw_init_hmac(stwuct zd_chip *chip)
{
	int w;
	static const stwuct zd_ioweq32 ioweqs[] = {
		{ CW_ACK_TIMEOUT_EXT,		0x20 },
		{ CW_ADDA_MBIAS_WAWMTIME,	0x30000808 },
		{ CW_SNIFFEW_ON,		0 },
		{ CW_WX_FIWTEW,			STA_WX_FIWTEW },
		{ CW_GWOUP_HASH_P1,		0x00 },
		{ CW_GWOUP_HASH_P2,		0x80000000 },
		{ CW_WEG1,			0xa4 },
		{ CW_ADDA_PWW_DWN,		0x7f },
		{ CW_BCN_PWCP_CFG,		0x00f00401 },
		{ CW_PHY_DEWAY,			0x00 },
		{ CW_ACK_TIMEOUT_EXT,		0x80 },
		{ CW_ADDA_PWW_DWN,		0x00 },
		{ CW_ACK_TIME_80211,		0x100 },
		{ CW_WX_PE_DEWAY,		0x70 },
		{ CW_PS_CTWW,			0x10000000 },
		{ CW_WTS_CTS_WATE,		0x02030203 },
		{ CW_AFTEW_PNP,			0x1 },
		{ CW_WEP_PWOTECT,		0x114 },
		{ CW_IFS_VAWUE,			IFS_VAWUE_DEFAUWT },
		{ CW_CAM_MODE,			MODE_AP_WDS},
	};

	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	w = zd_iowwite32a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
	if (w)
		wetuwn w;

	wetuwn zd_chip_is_zd1211b(chip) ?
		zd1211b_hw_init_hmac(chip) : zd1211_hw_init_hmac(chip);
}

stwuct aw_pt_bi {
	u32 atim_wnd_pewiod;
	u32 pwe_tbtt;
	u32 beacon_intewvaw;
};

static int get_aw_pt_bi(stwuct zd_chip *chip, stwuct aw_pt_bi *s)
{
	int w;
	static const zd_addw_t aw_pt_bi_addw[] =
		{ CW_ATIM_WND_PEWIOD, CW_PWE_TBTT, CW_BCN_INTEWVAW };
	u32 vawues[3];

	w = zd_iowead32v_wocked(chip, vawues, (const zd_addw_t *)aw_pt_bi_addw,
		         AWWAY_SIZE(aw_pt_bi_addw));
	if (w) {
		memset(s, 0, sizeof(*s));
		wetuwn w;
	}

	s->atim_wnd_pewiod = vawues[0];
	s->pwe_tbtt = vawues[1];
	s->beacon_intewvaw = vawues[2];
	wetuwn 0;
}

static int set_aw_pt_bi(stwuct zd_chip *chip, stwuct aw_pt_bi *s)
{
	stwuct zd_ioweq32 weqs[3];
	u16 b_intewvaw = s->beacon_intewvaw & 0xffff;

	if (b_intewvaw <= 5)
		b_intewvaw = 5;
	if (s->pwe_tbtt < 4 || s->pwe_tbtt >= b_intewvaw)
		s->pwe_tbtt = b_intewvaw - 1;
	if (s->atim_wnd_pewiod >= s->pwe_tbtt)
		s->atim_wnd_pewiod = s->pwe_tbtt - 1;

	weqs[0].addw = CW_ATIM_WND_PEWIOD;
	weqs[0].vawue = s->atim_wnd_pewiod;
	weqs[1].addw = CW_PWE_TBTT;
	weqs[1].vawue = s->pwe_tbtt;
	weqs[2].addw = CW_BCN_INTEWVAW;
	weqs[2].vawue = (s->beacon_intewvaw & ~0xffff) | b_intewvaw;

	wetuwn zd_iowwite32a_wocked(chip, weqs, AWWAY_SIZE(weqs));
}


static int set_beacon_intewvaw(stwuct zd_chip *chip, u16 intewvaw,
			       u8 dtim_pewiod, int type)
{
	int w;
	stwuct aw_pt_bi s;
	u32 b_intewvaw, mode_fwag;

	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));

	if (intewvaw > 0) {
		switch (type) {
		case NW80211_IFTYPE_ADHOC:
		case NW80211_IFTYPE_MESH_POINT:
			mode_fwag = BCN_MODE_IBSS;
			bweak;
		case NW80211_IFTYPE_AP:
			mode_fwag = BCN_MODE_AP;
			bweak;
		defauwt:
			mode_fwag = 0;
			bweak;
		}
	} ewse {
		dtim_pewiod = 0;
		mode_fwag = 0;
	}

	b_intewvaw = mode_fwag | (dtim_pewiod << 16) | intewvaw;

	w = zd_iowwite32_wocked(chip, b_intewvaw, CW_BCN_INTEWVAW);
	if (w)
		wetuwn w;
	w = get_aw_pt_bi(chip, &s);
	if (w)
		wetuwn w;
	wetuwn set_aw_pt_bi(chip, &s);
}

int zd_set_beacon_intewvaw(stwuct zd_chip *chip, u16 intewvaw, u8 dtim_pewiod,
			   int type)
{
	int w;

	mutex_wock(&chip->mutex);
	w = set_beacon_intewvaw(chip, intewvaw, dtim_pewiod, type);
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

static int hw_init(stwuct zd_chip *chip)
{
	int w;

	dev_dbg_f(zd_chip_dev(chip), "\n");
	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	w = hw_weset_phy(chip);
	if (w)
		wetuwn w;

	w = hw_init_hmac(chip);
	if (w)
		wetuwn w;

	wetuwn set_beacon_intewvaw(chip, 100, 0, NW80211_IFTYPE_UNSPECIFIED);
}

static zd_addw_t fw_weg_addw(stwuct zd_chip *chip, u16 offset)
{
	wetuwn (zd_addw_t)((u16)chip->fw_wegs_base + offset);
}

#ifdef DEBUG
static int dump_cw(stwuct zd_chip *chip, const zd_addw_t addw,
	           const chaw *addw_stwing)
{
	int w;
	u32 vawue;

	w = zd_iowead32_wocked(chip, &vawue, addw);
	if (w) {
		dev_dbg_f(zd_chip_dev(chip),
			"ewwow weading %s. Ewwow numbew %d\n", addw_stwing, w);
		wetuwn w;
	}

	dev_dbg_f(zd_chip_dev(chip), "%s %#010x\n",
		addw_stwing, (unsigned int)vawue);
	wetuwn 0;
}

static int test_init(stwuct zd_chip *chip)
{
	int w;

	w = dump_cw(chip, CW_AFTEW_PNP, "CW_AFTEW_PNP");
	if (w)
		wetuwn w;
	w = dump_cw(chip, CW_GPI_EN, "CW_GPI_EN");
	if (w)
		wetuwn w;
	wetuwn dump_cw(chip, CW_INTEWWUPT, "CW_INTEWWUPT");
}

static void dump_fw_wegistews(stwuct zd_chip *chip)
{
	const zd_addw_t addw[4] = {
		fw_weg_addw(chip, FW_WEG_FIWMWAWE_VEW),
		fw_weg_addw(chip, FW_WEG_USB_SPEED),
		fw_weg_addw(chip, FW_WEG_FIX_TX_WATE),
		fw_weg_addw(chip, FW_WEG_WED_WINK_STATUS),
	};

	int w;
	u16 vawues[4];

	w = zd_iowead16v_wocked(chip, vawues, (const zd_addw_t*)addw,
		         AWWAY_SIZE(addw));
	if (w) {
		dev_dbg_f(zd_chip_dev(chip), "ewwow %d zd_iowead16v_wocked\n",
			 w);
		wetuwn;
	}

	dev_dbg_f(zd_chip_dev(chip), "FW_FIWMWAWE_VEW %#06hx\n", vawues[0]);
	dev_dbg_f(zd_chip_dev(chip), "FW_USB_SPEED %#06hx\n", vawues[1]);
	dev_dbg_f(zd_chip_dev(chip), "FW_FIX_TX_WATE %#06hx\n", vawues[2]);
	dev_dbg_f(zd_chip_dev(chip), "FW_WINK_STATUS %#06hx\n", vawues[3]);
}
#endif /* DEBUG */

static int pwint_fw_vewsion(stwuct zd_chip *chip)
{
	stwuct wiphy *wiphy = zd_chip_to_mac(chip)->hw->wiphy;
	int w;
	u16 vewsion;

	w = zd_iowead16_wocked(chip, &vewsion,
		fw_weg_addw(chip, FW_WEG_FIWMWAWE_VEW));
	if (w)
		wetuwn w;

	dev_info(zd_chip_dev(chip),"fiwmwawe vewsion %04hx\n", vewsion);

	snpwintf(wiphy->fw_vewsion, sizeof(wiphy->fw_vewsion),
			"%04hx", vewsion);

	wetuwn 0;
}

static int set_mandatowy_wates(stwuct zd_chip *chip, int gmode)
{
	u32 wates;
	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	/* This sets the mandatowy wates, which onwy depend fwom the standawd
	 * that the device is suppowting. Untiw fuwthew notice we shouwd twy
	 * to suppowt 802.11g awso fow fuww speed USB.
	 */
	if (!gmode)
		wates = CW_WATE_1M|CW_WATE_2M|CW_WATE_5_5M|CW_WATE_11M;
	ewse
		wates = CW_WATE_1M|CW_WATE_2M|CW_WATE_5_5M|CW_WATE_11M|
			CW_WATE_6M|CW_WATE_12M|CW_WATE_24M;

	wetuwn zd_iowwite32_wocked(chip, wates, CW_MANDATOWY_WATE_TBW);
}

int zd_chip_set_wts_cts_wate_wocked(stwuct zd_chip *chip,
				    int pweambwe)
{
	u32 vawue = 0;

	dev_dbg_f(zd_chip_dev(chip), "pweambwe=%x\n", pweambwe);
	vawue |= pweambwe << WTSCTS_SH_WTS_PMB_TYPE;
	vawue |= pweambwe << WTSCTS_SH_CTS_PMB_TYPE;

	/* We awways send 11M WTS/sewf-CTS messages, wike the vendow dwivew. */
	vawue |= ZD_PUWE_WATE(ZD_CCK_WATE_11M) << WTSCTS_SH_WTS_WATE;
	vawue |= ZD_WX_CCK << WTSCTS_SH_WTS_MOD_TYPE;
	vawue |= ZD_PUWE_WATE(ZD_CCK_WATE_11M) << WTSCTS_SH_CTS_WATE;
	vawue |= ZD_WX_CCK << WTSCTS_SH_CTS_MOD_TYPE;

	wetuwn zd_iowwite32_wocked(chip, vawue, CW_WTS_CTS_WATE);
}

int zd_chip_enabwe_hwint(stwuct zd_chip *chip)
{
	int w;

	mutex_wock(&chip->mutex);
	w = zd_iowwite32_wocked(chip, HWINT_ENABWED, CW_INTEWWUPT);
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

static int disabwe_hwint(stwuct zd_chip *chip)
{
	wetuwn zd_iowwite32_wocked(chip, HWINT_DISABWED, CW_INTEWWUPT);
}

int zd_chip_disabwe_hwint(stwuct zd_chip *chip)
{
	int w;

	mutex_wock(&chip->mutex);
	w = disabwe_hwint(chip);
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

static int wead_fw_wegs_offset(stwuct zd_chip *chip)
{
	int w;

	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	w = zd_iowead16_wocked(chip, (u16*)&chip->fw_wegs_base,
		               FWWAW_WEGS_ADDW);
	if (w)
		wetuwn w;
	dev_dbg_f(zd_chip_dev(chip), "fw_wegs_base: %#06hx\n",
		  (u16)chip->fw_wegs_base);

	wetuwn 0;
}

/* Wead mac addwess using pwe-fiwmwawe intewface */
int zd_chip_wead_mac_addw_fw(stwuct zd_chip *chip, u8 *addw)
{
	dev_dbg_f(zd_chip_dev(chip), "\n");
	wetuwn zd_usb_wead_fw(&chip->usb, E2P_MAC_ADDW_P1, addw,
		ETH_AWEN);
}

int zd_chip_init_hw(stwuct zd_chip *chip)
{
	int w;
	u8 wf_type;

	dev_dbg_f(zd_chip_dev(chip), "\n");

	mutex_wock(&chip->mutex);

#ifdef DEBUG
	w = test_init(chip);
	if (w)
		goto out;
#endif
	w = zd_iowwite32_wocked(chip, 1, CW_AFTEW_PNP);
	if (w)
		goto out;

	w = wead_fw_wegs_offset(chip);
	if (w)
		goto out;

	/* GPI is awways disabwed, awso in the othew dwivew.
	 */
	w = zd_iowwite32_wocked(chip, 0, CW_GPI_EN);
	if (w)
		goto out;
	w = zd_iowwite32_wocked(chip, CWIN_SIZE, CW_CWMIN_CWMAX);
	if (w)
		goto out;
	/* Cuwwentwy we suppowt IEEE 802.11g fow fuww and high speed USB.
	 * It might be discussed, whethew we shouwd suppowt puwe b mode fow
	 * fuww speed USB.
	 */
	w = set_mandatowy_wates(chip, 1);
	if (w)
		goto out;
	/* Disabwing intewwupts is cewtainwy a smawt thing hewe.
	 */
	w = disabwe_hwint(chip);
	if (w)
		goto out;
	w = wead_pod(chip, &wf_type);
	if (w)
		goto out;
	w = hw_init(chip);
	if (w)
		goto out;
	w = zd_wf_init_hw(&chip->wf, wf_type);
	if (w)
		goto out;

	w = pwint_fw_vewsion(chip);
	if (w)
		goto out;

#ifdef DEBUG
	dump_fw_wegistews(chip);
	w = test_init(chip);
	if (w)
		goto out;
#endif /* DEBUG */

	w = wead_caw_int_tabwes(chip);
	if (w)
		goto out;

	pwint_id(chip);
out:
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

static int update_pww_int(stwuct zd_chip *chip, u8 channew)
{
	u8 vawue = chip->pww_int_vawues[channew - 1];
	wetuwn zd_iowwite16_wocked(chip, vawue, ZD_CW31);
}

static int update_pww_caw(stwuct zd_chip *chip, u8 channew)
{
	u8 vawue = chip->pww_caw_vawues[channew-1];
	wetuwn zd_iowwite16_wocked(chip, vawue, ZD_CW68);
}

static int update_ofdm_caw(stwuct zd_chip *chip, u8 channew)
{
	stwuct zd_ioweq16 ioweqs[3];

	ioweqs[0].addw = ZD_CW67;
	ioweqs[0].vawue = chip->ofdm_caw_vawues[OFDM_36M_INDEX][channew-1];
	ioweqs[1].addw = ZD_CW66;
	ioweqs[1].vawue = chip->ofdm_caw_vawues[OFDM_48M_INDEX][channew-1];
	ioweqs[2].addw = ZD_CW65;
	ioweqs[2].vawue = chip->ofdm_caw_vawues[OFDM_54M_INDEX][channew-1];

	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

static int update_channew_integwation_and_cawibwation(stwuct zd_chip *chip,
	                                              u8 channew)
{
	int w;

	if (!zd_wf_shouwd_update_pww_int(&chip->wf))
		wetuwn 0;

	w = update_pww_int(chip, channew);
	if (w)
		wetuwn w;
	if (zd_chip_is_zd1211b(chip)) {
		static const stwuct zd_ioweq16 ioweqs[] = {
			{ ZD_CW69, 0x28 },
			{},
			{ ZD_CW69, 0x2a },
		};

		w = update_ofdm_caw(chip, channew);
		if (w)
			wetuwn w;
		w = update_pww_caw(chip, channew);
		if (w)
			wetuwn w;
		w = zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

/* The CCK baseband gain can be optionawwy patched by the EEPWOM */
static int patch_cck_gain(stwuct zd_chip *chip)
{
	int w;
	u32 vawue;

	if (!chip->patch_cck_gain || !zd_wf_shouwd_patch_cck_gain(&chip->wf))
		wetuwn 0;

	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	w = zd_iowead32_wocked(chip, &vawue, E2P_PHY_WEG);
	if (w)
		wetuwn w;
	dev_dbg_f(zd_chip_dev(chip), "patching vawue %x\n", vawue & 0xff);
	wetuwn zd_iowwite16_wocked(chip, vawue & 0xff, ZD_CW47);
}

int zd_chip_set_channew(stwuct zd_chip *chip, u8 channew)
{
	int w, t;

	mutex_wock(&chip->mutex);
	w = zd_chip_wock_phy_wegs(chip);
	if (w)
		goto out;
	w = zd_wf_set_channew(&chip->wf, channew);
	if (w)
		goto unwock;
	w = update_channew_integwation_and_cawibwation(chip, channew);
	if (w)
		goto unwock;
	w = patch_cck_gain(chip);
	if (w)
		goto unwock;
	w = patch_6m_band_edge(chip, channew);
	if (w)
		goto unwock;
	w = zd_iowwite32_wocked(chip, 0, CW_CONFIG_PHIWIPS);
unwock:
	t = zd_chip_unwock_phy_wegs(chip);
	if (t && !w)
		w = t;
out:
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

u8 zd_chip_get_channew(stwuct zd_chip *chip)
{
	u8 channew;

	mutex_wock(&chip->mutex);
	channew = chip->wf.channew;
	mutex_unwock(&chip->mutex);
	wetuwn channew;
}

int zd_chip_contwow_weds(stwuct zd_chip *chip, enum wed_status status)
{
	const zd_addw_t a[] = {
		fw_weg_addw(chip, FW_WEG_WED_WINK_STATUS),
		CW_WED,
	};

	int w;
	u16 v[AWWAY_SIZE(a)];
	stwuct zd_ioweq16 ioweqs[AWWAY_SIZE(a)] = {
		[0] = { fw_weg_addw(chip, FW_WEG_WED_WINK_STATUS) },
		[1] = { CW_WED },
	};
	u16 othew_wed;

	mutex_wock(&chip->mutex);
	w = zd_iowead16v_wocked(chip, v, (const zd_addw_t *)a, AWWAY_SIZE(a));
	if (w)
		goto out;

	othew_wed = chip->wink_wed == WED1 ? WED2 : WED1;

	switch (status) {
	case ZD_WED_OFF:
		ioweqs[0].vawue = FW_WINK_OFF;
		ioweqs[1].vawue = v[1] & ~(WED1|WED2);
		bweak;
	case ZD_WED_SCANNING:
		ioweqs[0].vawue = FW_WINK_OFF;
		ioweqs[1].vawue = v[1] & ~othew_wed;
		if ((u32)ktime_get_seconds() % 3 == 0) {
			ioweqs[1].vawue &= ~chip->wink_wed;
		} ewse {
			ioweqs[1].vawue |= chip->wink_wed;
		}
		bweak;
	case ZD_WED_ASSOCIATED:
		ioweqs[0].vawue = FW_WINK_TX;
		ioweqs[1].vawue = v[1] & ~othew_wed;
		ioweqs[1].vawue |= chip->wink_wed;
		bweak;
	defauwt:
		w = -EINVAW;
		goto out;
	}

	if (v[0] != ioweqs[0].vawue || v[1] != ioweqs[1].vawue) {
		w = zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
		if (w)
			goto out;
	}
	w = 0;
out:
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

int zd_chip_set_basic_wates(stwuct zd_chip *chip, u16 cw_wates)
{
	int w;

	if (cw_wates & ~(CW_WATES_80211B|CW_WATES_80211G))
		wetuwn -EINVAW;

	mutex_wock(&chip->mutex);
	w = zd_iowwite32_wocked(chip, cw_wates, CW_BASIC_WATE_TBW);
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

static inwine u8 zd_wate_fwom_ofdm_pwcp_headew(const void *wx_fwame)
{
	wetuwn ZD_OFDM | zd_ofdm_pwcp_headew_wate(wx_fwame);
}

/**
 * zd_wx_wate - wepowt zd-wate
 * @wx_fwame: weceived fwame
 * @status: wx_status as given by the device
 *
 * This function convewts the wate as encoded in the weceived packet to the
 * zd-wate, we awe using on othew pwaces in the dwivew.
 */
u8 zd_wx_wate(const void *wx_fwame, const stwuct wx_status *status)
{
	u8 zd_wate;
	if (status->fwame_status & ZD_WX_OFDM) {
		zd_wate = zd_wate_fwom_ofdm_pwcp_headew(wx_fwame);
	} ewse {
		switch (zd_cck_pwcp_headew_signaw(wx_fwame)) {
		case ZD_CCK_PWCP_SIGNAW_1M:
			zd_wate = ZD_CCK_WATE_1M;
			bweak;
		case ZD_CCK_PWCP_SIGNAW_2M:
			zd_wate = ZD_CCK_WATE_2M;
			bweak;
		case ZD_CCK_PWCP_SIGNAW_5M5:
			zd_wate = ZD_CCK_WATE_5_5M;
			bweak;
		case ZD_CCK_PWCP_SIGNAW_11M:
			zd_wate = ZD_CCK_WATE_11M;
			bweak;
		defauwt:
			zd_wate = 0;
		}
	}

	wetuwn zd_wate;
}

int zd_chip_switch_wadio_on(stwuct zd_chip *chip)
{
	int w;

	mutex_wock(&chip->mutex);
	w = zd_switch_wadio_on(&chip->wf);
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

int zd_chip_switch_wadio_off(stwuct zd_chip *chip)
{
	int w;

	mutex_wock(&chip->mutex);
	w = zd_switch_wadio_off(&chip->wf);
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

int zd_chip_enabwe_int(stwuct zd_chip *chip)
{
	int w;

	mutex_wock(&chip->mutex);
	w = zd_usb_enabwe_int(&chip->usb);
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

void zd_chip_disabwe_int(stwuct zd_chip *chip)
{
	mutex_wock(&chip->mutex);
	zd_usb_disabwe_int(&chip->usb);
	mutex_unwock(&chip->mutex);

	/* cancew pending intewwupt wowk */
	cancew_wowk_sync(&zd_chip_to_mac(chip)->pwocess_intw);
}

int zd_chip_enabwe_wxtx(stwuct zd_chip *chip)
{
	int w;

	mutex_wock(&chip->mutex);
	zd_usb_enabwe_tx(&chip->usb);
	w = zd_usb_enabwe_wx(&chip->usb);
	zd_tx_watchdog_enabwe(&chip->usb);
	mutex_unwock(&chip->mutex);
	wetuwn w;
}

void zd_chip_disabwe_wxtx(stwuct zd_chip *chip)
{
	mutex_wock(&chip->mutex);
	zd_tx_watchdog_disabwe(&chip->usb);
	zd_usb_disabwe_wx(&chip->usb);
	zd_usb_disabwe_tx(&chip->usb);
	mutex_unwock(&chip->mutex);
}

int zd_wfwwitev_wocked(stwuct zd_chip *chip,
	               const u32* vawues, unsigned int count, u8 bits)
{
	int w;
	unsigned int i;

	fow (i = 0; i < count; i++) {
		w = zd_wfwwite_wocked(chip, vawues[i], bits);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

/*
 * We can optionawwy pwogwam the WF diwectwy thwough CW wegs, if suppowted by
 * the hawdwawe. This is much fastew than the owdew method.
 */
int zd_wfwwite_cw_wocked(stwuct zd_chip *chip, u32 vawue)
{
	const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW244, (vawue >> 16) & 0xff },
		{ ZD_CW243, (vawue >>  8) & 0xff },
		{ ZD_CW242,  vawue        & 0xff },
	};
	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

int zd_wfwwitev_cw_wocked(stwuct zd_chip *chip,
	                  const u32 *vawues, unsigned int count)
{
	int w;
	unsigned int i;

	fow (i = 0; i < count; i++) {
		w = zd_wfwwite_cw_wocked(chip, vawues[i]);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

int zd_chip_set_muwticast_hash(stwuct zd_chip *chip,
	                       stwuct zd_mc_hash *hash)
{
	const stwuct zd_ioweq32 ioweqs[] = {
		{ CW_GWOUP_HASH_P1, hash->wow },
		{ CW_GWOUP_HASH_P2, hash->high },
	};

	wetuwn zd_iowwite32a(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

u64 zd_chip_get_tsf(stwuct zd_chip *chip)
{
	int w;
	static const zd_addw_t aw_pt_bi_addw[] =
		{ CW_TSF_WOW_PAWT, CW_TSF_HIGH_PAWT };
	u32 vawues[2];
	u64 tsf;

	mutex_wock(&chip->mutex);
	w = zd_iowead32v_wocked(chip, vawues, (const zd_addw_t *)aw_pt_bi_addw,
	                        AWWAY_SIZE(aw_pt_bi_addw));
	mutex_unwock(&chip->mutex);
	if (w)
		wetuwn 0;

	tsf = vawues[1];
	tsf = (tsf << 32) | vawues[0];

	wetuwn tsf;
}
