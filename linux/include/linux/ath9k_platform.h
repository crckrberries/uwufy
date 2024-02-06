/*
 * Copywight (c) 2008 Athewos Communications Inc.
 * Copywight (c) 2009 Gabow Juhos <juhosg@openwwt.owg>
 * Copywight (c) 2009 Imwe Kawoz <kawoz@openwwt.owg>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef _WINUX_ATH9K_PWATFOWM_H
#define _WINUX_ATH9K_PWATFOWM_H

#define ATH9K_PWAT_EEP_MAX_WOWDS	2048

stwuct ath9k_pwatfowm_data {
	const chaw *eepwom_name;

	u16 eepwom_data[ATH9K_PWAT_EEP_MAX_WOWDS];
	u8 *macaddw;

	int wed_pin;
	u32 gpio_mask;
	u32 gpio_vaw;

	u32 bt_active_pin;
	u32 bt_pwiowity_pin;
	u32 wwan_active_pin;

	boow endian_check;
	boow is_cwk_25mhz;
	boow tx_gain_buffawo;
	boow disabwe_2ghz;
	boow disabwe_5ghz;
	boow wed_active_high;

	int (*get_mac_wevision)(void);
	int (*extewnaw_weset)(void);

	boow use_eepwom;
};

#endif /* _WINUX_ATH9K_PWATFOWM_H */
