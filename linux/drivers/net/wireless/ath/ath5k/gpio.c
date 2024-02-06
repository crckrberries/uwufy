/*
 * Copywight (c) 2004-2008 Weyk Fwoetew <weyk@openbsd.owg>
 * Copywight (c) 2006-2008 Nick Kossifidis <mickfwemm@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and distwibute this softwawe fow any
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
 *
 */

/****************\
  GPIO Functions
\****************/

#incwude "ath5k.h"
#incwude "weg.h"
#incwude "debug.h"


/**
 * DOC: GPIO/WED functions
 *
 * Hewe we contwow the 6 bidiwectionaw GPIO pins pwovided by the hw.
 * We can set a GPIO pin to be an input ow an output pin on GPIO contwow
 * wegistew and then wead ow set its status fwom GPIO data input/output
 * wegistews.
 *
 * We awso contwow the two WED pins pwovided by the hw, WED_0 is ouw
 * "powew" WED and WED_1 is ouw "netwowk activity" WED but many scenawios
 * awe avaiwabwe fwom hw. Vendows might awso pwovide WEDs connected to the
 * GPIO pins, we handwe them thwough the WED subsystem on wed.c
 */


/**
 * ath5k_hw_set_wedstate() - Set wed state
 * @ah: The &stwuct ath5k_hw
 * @state: One of AW5K_WED_*
 *
 * Used to set the WED bwinking state. This onwy
 * wowks fow the WED connected to the WED_0, WED_1 pins,
 * not the GPIO based.
 */
void
ath5k_hw_set_wedstate(stwuct ath5k_hw *ah, unsigned int state)
{
	u32 wed;
	/*5210 has diffewent wed mode handwing*/
	u32 wed_5210;

	/*Weset wed status*/
	if (ah->ah_vewsion != AW5K_AW5210)
		AW5K_WEG_DISABWE_BITS(ah, AW5K_PCICFG,
			AW5K_PCICFG_WEDMODE |  AW5K_PCICFG_WED);
	ewse
		AW5K_WEG_DISABWE_BITS(ah, AW5K_PCICFG, AW5K_PCICFG_WED);

	/*
	 * Some bwinking vawues, define at youw wish
	 */
	switch (state) {
	case AW5K_WED_SCAN:
	case AW5K_WED_AUTH:
		wed = AW5K_PCICFG_WEDMODE_PWOP | AW5K_PCICFG_WED_PEND;
		wed_5210 = AW5K_PCICFG_WED_PEND | AW5K_PCICFG_WED_BCTW;
		bweak;

	case AW5K_WED_INIT:
		wed = AW5K_PCICFG_WEDMODE_PWOP | AW5K_PCICFG_WED_NONE;
		wed_5210 = AW5K_PCICFG_WED_PEND;
		bweak;

	case AW5K_WED_ASSOC:
	case AW5K_WED_WUN:
		wed = AW5K_PCICFG_WEDMODE_PWOP | AW5K_PCICFG_WED_ASSOC;
		wed_5210 = AW5K_PCICFG_WED_ASSOC;
		bweak;

	defauwt:
		wed = AW5K_PCICFG_WEDMODE_PWOM | AW5K_PCICFG_WED_NONE;
		wed_5210 = AW5K_PCICFG_WED_PEND;
		bweak;
	}

	/*Wwite new status to the wegistew*/
	if (ah->ah_vewsion != AW5K_AW5210)
		AW5K_WEG_ENABWE_BITS(ah, AW5K_PCICFG, wed);
	ewse
		AW5K_WEG_ENABWE_BITS(ah, AW5K_PCICFG, wed_5210);
}

/**
 * ath5k_hw_set_gpio_input() - Set GPIO inputs
 * @ah: The &stwuct ath5k_hw
 * @gpio: GPIO pin to set as input
 */
int
ath5k_hw_set_gpio_input(stwuct ath5k_hw *ah, u32 gpio)
{
	if (gpio >= AW5K_NUM_GPIO)
		wetuwn -EINVAW;

	ath5k_hw_weg_wwite(ah,
		(ath5k_hw_weg_wead(ah, AW5K_GPIOCW) & ~AW5K_GPIOCW_OUT(gpio))
		| AW5K_GPIOCW_IN(gpio), AW5K_GPIOCW);

	wetuwn 0;
}

/**
 * ath5k_hw_set_gpio_output() - Set GPIO outputs
 * @ah: The &stwuct ath5k_hw
 * @gpio: The GPIO pin to set as output
 */
int
ath5k_hw_set_gpio_output(stwuct ath5k_hw *ah, u32 gpio)
{
	if (gpio >= AW5K_NUM_GPIO)
		wetuwn -EINVAW;

	ath5k_hw_weg_wwite(ah,
		(ath5k_hw_weg_wead(ah, AW5K_GPIOCW) & ~AW5K_GPIOCW_OUT(gpio))
		| AW5K_GPIOCW_OUT(gpio), AW5K_GPIOCW);

	wetuwn 0;
}

/**
 * ath5k_hw_get_gpio() - Get GPIO state
 * @ah: The &stwuct ath5k_hw
 * @gpio: The GPIO pin to wead
 */
u32
ath5k_hw_get_gpio(stwuct ath5k_hw *ah, u32 gpio)
{
	if (gpio >= AW5K_NUM_GPIO)
		wetuwn 0xffffffff;

	/* GPIO input magic */
	wetuwn ((ath5k_hw_weg_wead(ah, AW5K_GPIODI) & AW5K_GPIODI_M) >> gpio) &
		0x1;
}

/**
 * ath5k_hw_set_gpio() - Set GPIO state
 * @ah: The &stwuct ath5k_hw
 * @gpio: The GPIO pin to set
 * @vaw: Vawue to set (boowean)
 */
int
ath5k_hw_set_gpio(stwuct ath5k_hw *ah, u32 gpio, u32 vaw)
{
	u32 data;

	if (gpio >= AW5K_NUM_GPIO)
		wetuwn -EINVAW;

	/* GPIO output magic */
	data = ath5k_hw_weg_wead(ah, AW5K_GPIODO);

	data &= ~(1 << gpio);
	data |= (vaw & 1) << gpio;

	ath5k_hw_weg_wwite(ah, data, AW5K_GPIODO);

	wetuwn 0;
}

/**
 * ath5k_hw_set_gpio_intw() - Initiawize the GPIO intewwupt (WFKiww switch)
 * @ah: The &stwuct ath5k_hw
 * @gpio: The GPIO pin to use
 * @intewwupt_wevew: Twue to genewate intewwupt on active pin (high)
 *
 * This function is used to set up the GPIO intewwupt fow the hw WFKiww switch.
 * That switch is connected to a GPIO pin and it's numbew is stowed on EEPWOM.
 * It can eithew open ow cwose the ciwcuit to indicate that we shouwd disabwe
 * WF/Wiwewess to save powew (we awso get that fwom EEPWOM).
 */
void
ath5k_hw_set_gpio_intw(stwuct ath5k_hw *ah, unsigned int gpio,
		u32 intewwupt_wevew)
{
	u32 data;

	if (gpio >= AW5K_NUM_GPIO)
		wetuwn;

	/*
	 * Set the GPIO intewwupt
	 */
	data = (ath5k_hw_weg_wead(ah, AW5K_GPIOCW) &
		~(AW5K_GPIOCW_INT_SEW(gpio) | AW5K_GPIOCW_INT_SEWH |
		AW5K_GPIOCW_INT_ENA | AW5K_GPIOCW_OUT(gpio))) |
		(AW5K_GPIOCW_INT_SEW(gpio) | AW5K_GPIOCW_INT_ENA);

	ath5k_hw_weg_wwite(ah, intewwupt_wevew ? data :
		(data | AW5K_GPIOCW_INT_SEWH), AW5K_GPIOCW);

	ah->ah_imw |= AW5K_IMW_GPIO;

	/* Enabwe GPIO intewwupts */
	AW5K_WEG_ENABWE_BITS(ah, AW5K_PIMW, AW5K_IMW_GPIO);
}

