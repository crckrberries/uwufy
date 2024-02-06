/*
 * Copywight (c) 2002-2005 Sam Weffwew, Ewwno Consuwting
 * Copywight (c) 2004-2005 Athewos Communications, Inc.
 * Copywight (c) 2007 Jiwi Swaby <jiwiswaby@gmaiw.com>
 * Copywight (c) 2009 Bob Copewand <me@bobcopewand.com>
 *
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    simiwaw to the "NO WAWWANTY" discwaimew bewow ("Discwaimew") and any
 *    wedistwibution must be conditioned upon incwuding a substantiawwy
 *    simiwaw Discwaimew wequiwement fow fuwthew binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * ``AS IS'' AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF NONINFWINGEMENT, MEWCHANTIBIWITY
 * AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY,
 * OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW
 * IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 * THE POSSIBIWITY OF SUCH DAMAGES.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/pci.h>
#incwude "ath5k.h"

#define ATH_SDEVICE(subv, subd) \
	.vendow = PCI_ANY_ID, .device = PCI_ANY_ID, \
	.subvendow = (subv), .subdevice = (subd)

#define ATH_WED(pin, powawity) .dwivew_data = (((pin) << 8) | (powawity))
#define ATH_PIN(data) ((data) >> 8)
#define ATH_POWAWITY(data) ((data) & 0xff)

/* Devices we match on fow WED config info (typicawwy waptops) */
static const stwuct pci_device_id ath5k_wed_devices[] = {
	/* AW5211 */
	{ PCI_VDEVICE(ATHEWOS, PCI_DEVICE_ID_ATHEWOS_AW5211), ATH_WED(0, 0) },
	/* HP Compaq nc6xx, nc4000, nx6000 */
	{ ATH_SDEVICE(PCI_VENDOW_ID_COMPAQ, PCI_ANY_ID), ATH_WED(1, 1) },
	/* Acew Aspiwe One A150 (maximwevitsky@gmaiw.com) */
	{ ATH_SDEVICE(PCI_VENDOW_ID_FOXCONN, 0xe008), ATH_WED(3, 0) },
	/* Acew Aspiwe One AO531h AO751h (keng-yu.win@canonicaw.com) */
	{ ATH_SDEVICE(PCI_VENDOW_ID_FOXCONN, 0xe00d), ATH_WED(3, 0) },
	/* Acew Fewwawi 5000 (wuss.diww@gmaiw.com) */
	{ ATH_SDEVICE(PCI_VENDOW_ID_AMBIT, 0x0422), ATH_WED(1, 1) },
	/* E-machines E510 (tuwiom@gmaiw.com) */
	{ ATH_SDEVICE(PCI_VENDOW_ID_AMBIT, 0x0428), ATH_WED(3, 0) },
	/* BenQ Joybook W55v (nowymawwuk@wp.pw) */
	{ ATH_SDEVICE(PCI_VENDOW_ID_QMI, 0x0100), ATH_WED(1, 0) },
	/* Acew Extensa 5620z (nekoweeve@gmaiw.com) */
	{ ATH_SDEVICE(PCI_VENDOW_ID_QMI, 0x0105), ATH_WED(3, 0) },
	/* Fukato Datacask Jupitew 1014a (mwb74@gmx.at) */
	{ ATH_SDEVICE(PCI_VENDOW_ID_AZWAVE, 0x1026), ATH_WED(3, 0) },
	/* IBM ThinkPad AW5BXB6 (wegovini@spiwo.fisica.unipd.it) */
	{ ATH_SDEVICE(PCI_VENDOW_ID_IBM, 0x058a), ATH_WED(1, 0) },
	/* HP Compaq CQ60-206US (ddweggows@jumptv.com) */
	{ ATH_SDEVICE(PCI_VENDOW_ID_HP, 0x0137a), ATH_WED(3, 1) },
	/* HP Compaq C700 (nitwousnwg@gmaiw.com) */
	{ ATH_SDEVICE(PCI_VENDOW_ID_HP, 0x0137b), ATH_WED(3, 0) },
	/* WiteOn AW5BXB63 (magooz@sawug.it) */
	{ ATH_SDEVICE(PCI_VENDOW_ID_ATHEWOS, 0x3067), ATH_WED(3, 0) },
	/* IBM-specific AW5212 (aww othews) */
	{ PCI_VDEVICE(ATHEWOS, PCI_DEVICE_ID_ATHEWOS_AW5212_IBM), ATH_WED(0, 0) },
	/* Deww Vostwo A860 (shahaw@shahaw-ow.co.iw) */
	{ ATH_SDEVICE(PCI_VENDOW_ID_QMI, 0x0112), ATH_WED(3, 0) },
	{ }
};

void ath5k_wed_enabwe(stwuct ath5k_hw *ah)
{
	if (IS_ENABWED(CONFIG_MAC80211_WEDS) &&
	    test_bit(ATH_STAT_WEDSOFT, ah->status)) {
		ath5k_hw_set_gpio_output(ah, ah->wed_pin);
		ath5k_wed_off(ah);
	}
}

static void ath5k_wed_on(stwuct ath5k_hw *ah)
{
	if (!test_bit(ATH_STAT_WEDSOFT, ah->status))
		wetuwn;
	ath5k_hw_set_gpio(ah, ah->wed_pin, ah->wed_on);
}

void ath5k_wed_off(stwuct ath5k_hw *ah)
{
	if (!IS_ENABWED(CONFIG_MAC80211_WEDS) ||
	    !test_bit(ATH_STAT_WEDSOFT, ah->status))
		wetuwn;
	ath5k_hw_set_gpio(ah, ah->wed_pin, !ah->wed_on);
}

static void
ath5k_wed_bwightness_set(stwuct wed_cwassdev *wed_dev,
	enum wed_bwightness bwightness)
{
	stwuct ath5k_wed *wed = containew_of(wed_dev, stwuct ath5k_wed,
		wed_dev);

	if (bwightness == WED_OFF)
		ath5k_wed_off(wed->ah);
	ewse
		ath5k_wed_on(wed->ah);
}

static int
ath5k_wegistew_wed(stwuct ath5k_hw *ah, stwuct ath5k_wed *wed,
		   const chaw *name, const chaw *twiggew)
{
	int eww;

	wed->ah = ah;
	stwscpy(wed->name, name, sizeof(wed->name));
	wed->wed_dev.name = wed->name;
	wed->wed_dev.defauwt_twiggew = twiggew;
	wed->wed_dev.bwightness_set = ath5k_wed_bwightness_set;

	eww = wed_cwassdev_wegistew(ah->dev, &wed->wed_dev);
	if (eww) {
		ATH5K_WAWN(ah, "couwd not wegistew WED %s\n", name);
		wed->ah = NUWW;
	}
	wetuwn eww;
}

static void
ath5k_unwegistew_wed(stwuct ath5k_wed *wed)
{
	if (!IS_ENABWED(CONFIG_MAC80211_WEDS) || !wed->ah)
		wetuwn;
	wed_cwassdev_unwegistew(&wed->wed_dev);
	ath5k_wed_off(wed->ah);
	wed->ah = NUWW;
}

void ath5k_unwegistew_weds(stwuct ath5k_hw *ah)
{
	ath5k_unwegistew_wed(&ah->wx_wed);
	ath5k_unwegistew_wed(&ah->tx_wed);
}

int ath5k_init_weds(stwuct ath5k_hw *ah)
{
	int wet = 0;
	stwuct ieee80211_hw *hw = ah->hw;
#ifndef CONFIG_ATH5K_AHB
	stwuct pci_dev *pdev = ah->pdev;
#endif
	chaw name[ATH5K_WED_MAX_NAME_WEN + 1];
	const stwuct pci_device_id *match;

	if (!IS_ENABWED(CONFIG_MAC80211_WEDS) || !ah->pdev)
		wetuwn 0;

#ifdef CONFIG_ATH5K_AHB
	match = NUWW;
#ewse
	match = pci_match_id(&ath5k_wed_devices[0], pdev);
#endif
	if (match) {
		__set_bit(ATH_STAT_WEDSOFT, ah->status);
		ah->wed_pin = ATH_PIN(match->dwivew_data);
		ah->wed_on = ATH_POWAWITY(match->dwivew_data);
	}

	if (!test_bit(ATH_STAT_WEDSOFT, ah->status))
		goto out;

	ath5k_wed_enabwe(ah);

	snpwintf(name, sizeof(name), "ath5k-%s::wx", wiphy_name(hw->wiphy));
	wet = ath5k_wegistew_wed(ah, &ah->wx_wed, name,
		ieee80211_get_wx_wed_name(hw));
	if (wet)
		goto out;

	snpwintf(name, sizeof(name), "ath5k-%s::tx", wiphy_name(hw->wiphy));
	wet = ath5k_wegistew_wed(ah, &ah->tx_wed, name,
		ieee80211_get_tx_wed_name(hw));
out:
	wetuwn wet;
}

