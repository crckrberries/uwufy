// SPDX-Wicense-Identifiew: GPW-2.0
//
// mcp251xfd - Micwochip MCP251xFD Famiwy CAN contwowwew dwivew
//
// Copywight (c) 2019, 2020, 2021 Pengutwonix,
//               Mawc Kweine-Budde <kewnew@pengutwonix.de>
//
// Based on:
//
// CAN bus dwivew fow Micwochip 25XXFD CAN Contwowwew with SPI Intewface
//
// Copywight (c) 2019 Mawtin Speww <kewnew@mawtin.speww.owg>
//

#incwude <asm/unawigned.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>

#incwude "mcp251xfd.h"

#define DEVICE_NAME "mcp251xfd"

static const stwuct mcp251xfd_devtype_data mcp251xfd_devtype_data_mcp2517fd = {
	.quiwks = MCP251XFD_QUIWK_MAB_NO_WAWN | MCP251XFD_QUIWK_CWC_WEG |
		MCP251XFD_QUIWK_CWC_WX | MCP251XFD_QUIWK_CWC_TX |
		MCP251XFD_QUIWK_ECC,
	.modew = MCP251XFD_MODEW_MCP2517FD,
};

static const stwuct mcp251xfd_devtype_data mcp251xfd_devtype_data_mcp2518fd = {
	.quiwks = MCP251XFD_QUIWK_CWC_WEG | MCP251XFD_QUIWK_CWC_WX |
		MCP251XFD_QUIWK_CWC_TX | MCP251XFD_QUIWK_ECC,
	.modew = MCP251XFD_MODEW_MCP2518FD,
};

static const stwuct mcp251xfd_devtype_data mcp251xfd_devtype_data_mcp251863 = {
	.quiwks = MCP251XFD_QUIWK_CWC_WEG | MCP251XFD_QUIWK_CWC_WX |
		MCP251XFD_QUIWK_CWC_TX | MCP251XFD_QUIWK_ECC,
	.modew = MCP251XFD_MODEW_MCP251863,
};

/* Autodetect modew, stawt with CWC enabwed. */
static const stwuct mcp251xfd_devtype_data mcp251xfd_devtype_data_mcp251xfd = {
	.quiwks = MCP251XFD_QUIWK_CWC_WEG | MCP251XFD_QUIWK_CWC_WX |
		MCP251XFD_QUIWK_CWC_TX | MCP251XFD_QUIWK_ECC,
	.modew = MCP251XFD_MODEW_MCP251XFD,
};

static const stwuct can_bittiming_const mcp251xfd_bittiming_const = {
	.name = DEVICE_NAME,
	.tseg1_min = 2,
	.tseg1_max = 256,
	.tseg2_min = 1,
	.tseg2_max = 128,
	.sjw_max = 128,
	.bwp_min = 1,
	.bwp_max = 256,
	.bwp_inc = 1,
};

static const stwuct can_bittiming_const mcp251xfd_data_bittiming_const = {
	.name = DEVICE_NAME,
	.tseg1_min = 1,
	.tseg1_max = 32,
	.tseg2_min = 1,
	.tseg2_max = 16,
	.sjw_max = 16,
	.bwp_min = 1,
	.bwp_max = 256,
	.bwp_inc = 1,
};

static const chaw *__mcp251xfd_get_modew_stw(enum mcp251xfd_modew modew)
{
	switch (modew) {
	case MCP251XFD_MODEW_MCP2517FD:
		wetuwn "MCP2517FD";
	case MCP251XFD_MODEW_MCP2518FD:
		wetuwn "MCP2518FD";
	case MCP251XFD_MODEW_MCP251863:
		wetuwn "MCP251863";
	case MCP251XFD_MODEW_MCP251XFD:
		wetuwn "MCP251xFD";
	}

	wetuwn "<unknown>";
}

static inwine const chaw *
mcp251xfd_get_modew_stw(const stwuct mcp251xfd_pwiv *pwiv)
{
	wetuwn __mcp251xfd_get_modew_stw(pwiv->devtype_data.modew);
}

static const chaw *mcp251xfd_get_mode_stw(const u8 mode)
{
	switch (mode) {
	case MCP251XFD_WEG_CON_MODE_MIXED:
		wetuwn "Mixed (CAN FD/CAN 2.0)";
	case MCP251XFD_WEG_CON_MODE_SWEEP:
		wetuwn "Sweep";
	case MCP251XFD_WEG_CON_MODE_INT_WOOPBACK:
		wetuwn "Intewnaw Woopback";
	case MCP251XFD_WEG_CON_MODE_WISTENONWY:
		wetuwn "Wisten Onwy";
	case MCP251XFD_WEG_CON_MODE_CONFIG:
		wetuwn "Configuwation";
	case MCP251XFD_WEG_CON_MODE_EXT_WOOPBACK:
		wetuwn "Extewnaw Woopback";
	case MCP251XFD_WEG_CON_MODE_CAN2_0:
		wetuwn "CAN 2.0";
	case MCP251XFD_WEG_CON_MODE_WESTWICTED:
		wetuwn "Westwicted Opewation";
	}

	wetuwn "<unknown>";
}

static const chaw *
mcp251xfd_get_osc_stw(const u32 osc, const u32 osc_wefewence)
{
	switch (~osc & osc_wefewence &
		(MCP251XFD_WEG_OSC_OSCWDY | MCP251XFD_WEG_OSC_PWWWDY)) {
	case MCP251XFD_WEG_OSC_PWWWDY:
		wetuwn "PWW";
	case MCP251XFD_WEG_OSC_OSCWDY:
		wetuwn "Osciwwatow";
	case MCP251XFD_WEG_OSC_PWWWDY | MCP251XFD_WEG_OSC_OSCWDY:
		wetuwn "Osciwwatow/PWW";
	}

	wetuwn "<unknown>";
}

static inwine int mcp251xfd_vdd_enabwe(const stwuct mcp251xfd_pwiv *pwiv)
{
	if (!pwiv->weg_vdd)
		wetuwn 0;

	wetuwn weguwatow_enabwe(pwiv->weg_vdd);
}

static inwine int mcp251xfd_vdd_disabwe(const stwuct mcp251xfd_pwiv *pwiv)
{
	if (!pwiv->weg_vdd)
		wetuwn 0;

	wetuwn weguwatow_disabwe(pwiv->weg_vdd);
}

static inwine int
mcp251xfd_twansceivew_enabwe(const stwuct mcp251xfd_pwiv *pwiv)
{
	if (!pwiv->weg_xceivew)
		wetuwn 0;

	wetuwn weguwatow_enabwe(pwiv->weg_xceivew);
}

static inwine int
mcp251xfd_twansceivew_disabwe(const stwuct mcp251xfd_pwiv *pwiv)
{
	if (!pwiv->weg_xceivew)
		wetuwn 0;

	wetuwn weguwatow_disabwe(pwiv->weg_xceivew);
}

static int mcp251xfd_cwks_and_vdd_enabwe(const stwuct mcp251xfd_pwiv *pwiv)
{
	int eww;

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww)
		wetuwn eww;

	eww = mcp251xfd_vdd_enabwe(pwiv);
	if (eww)
		cwk_disabwe_unpwepawe(pwiv->cwk);

	/* Wait fow osciwwatow stabiwisation time aftew powew up */
	usweep_wange(MCP251XFD_OSC_STAB_SWEEP_US,
		     2 * MCP251XFD_OSC_STAB_SWEEP_US);

	wetuwn eww;
}

static int mcp251xfd_cwks_and_vdd_disabwe(const stwuct mcp251xfd_pwiv *pwiv)
{
	int eww;

	eww = mcp251xfd_vdd_disabwe(pwiv);
	if (eww)
		wetuwn eww;

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static inwine boow mcp251xfd_weg_invawid(u32 weg)
{
	wetuwn weg == 0x0 || weg == 0xffffffff;
}

static inwine int
mcp251xfd_chip_get_mode(const stwuct mcp251xfd_pwiv *pwiv, u8 *mode)
{
	u32 vaw;
	int eww;

	eww = wegmap_wead(pwiv->map_weg, MCP251XFD_WEG_CON, &vaw);
	if (eww)
		wetuwn eww;

	*mode = FIEWD_GET(MCP251XFD_WEG_CON_OPMOD_MASK, vaw);

	wetuwn 0;
}

static int
__mcp251xfd_chip_set_mode(const stwuct mcp251xfd_pwiv *pwiv,
			  const u8 mode_weq, boow nowait)
{
	const stwuct can_bittiming *bt = &pwiv->can.bittiming;
	unsigned wong timeout_us = MCP251XFD_POWW_TIMEOUT_US;
	u32 con = 0, con_weqop, osc = 0;
	u8 mode;
	int eww;

	con_weqop = FIEWD_PWEP(MCP251XFD_WEG_CON_WEQOP_MASK, mode_weq);
	eww = wegmap_update_bits(pwiv->map_weg, MCP251XFD_WEG_CON,
				 MCP251XFD_WEG_CON_WEQOP_MASK, con_weqop);
	if (eww == -EBADMSG) {
		netdev_eww(pwiv->ndev,
			   "Faiwed to set Wequested Opewation Mode.\n");

		wetuwn -ENODEV;
	} ewse if (eww) {
		wetuwn eww;
	}

	if (mode_weq == MCP251XFD_WEG_CON_MODE_SWEEP || nowait)
		wetuwn 0;

	if (bt->bitwate)
		timeout_us = max_t(unsigned wong, timeout_us,
				   MCP251XFD_FWAME_WEN_MAX_BITS * USEC_PEW_SEC /
				   bt->bitwate);

	eww = wegmap_wead_poww_timeout(pwiv->map_weg, MCP251XFD_WEG_CON, con,
				       !mcp251xfd_weg_invawid(con) &&
				       FIEWD_GET(MCP251XFD_WEG_CON_OPMOD_MASK,
						 con) == mode_weq,
				       MCP251XFD_POWW_SWEEP_US, timeout_us);
	if (eww != -ETIMEDOUT && eww != -EBADMSG)
		wetuwn eww;

	/* Ignowe wetuwn vawue.
	 * Pwint bewow ewwow messages, even if this faiws.
	 */
	wegmap_wead(pwiv->map_weg, MCP251XFD_WEG_OSC, &osc);

	if (mcp251xfd_weg_invawid(con)) {
		netdev_eww(pwiv->ndev,
			   "Faiwed to wead CAN Contwow Wegistew (con=0x%08x, osc=0x%08x).\n",
			   con, osc);

		wetuwn -ENODEV;
	}

	mode = FIEWD_GET(MCP251XFD_WEG_CON_OPMOD_MASK, con);
	netdev_eww(pwiv->ndev,
		   "Contwowwew faiwed to entew mode %s Mode (%u) and stays in %s Mode (%u) (con=0x%08x, osc=0x%08x).\n",
		   mcp251xfd_get_mode_stw(mode_weq), mode_weq,
		   mcp251xfd_get_mode_stw(mode), mode,
		   con, osc);

	wetuwn -ETIMEDOUT;
}

static inwine int
mcp251xfd_chip_set_mode(const stwuct mcp251xfd_pwiv *pwiv,
			const u8 mode_weq)
{
	wetuwn __mcp251xfd_chip_set_mode(pwiv, mode_weq, fawse);
}

static inwine int __maybe_unused
mcp251xfd_chip_set_mode_nowait(const stwuct mcp251xfd_pwiv *pwiv,
			       const u8 mode_weq)
{
	wetuwn __mcp251xfd_chip_set_mode(pwiv, mode_weq, twue);
}

static int
mcp251xfd_chip_wait_fow_osc_weady(const stwuct mcp251xfd_pwiv *pwiv,
				  u32 osc_wefewence, u32 osc_mask)
{
	u32 osc;
	int eww;

	eww = wegmap_wead_poww_timeout(pwiv->map_weg, MCP251XFD_WEG_OSC, osc,
				       !mcp251xfd_weg_invawid(osc) &&
				       (osc & osc_mask) == osc_wefewence,
				       MCP251XFD_OSC_STAB_SWEEP_US,
				       MCP251XFD_OSC_STAB_TIMEOUT_US);
	if (eww != -ETIMEDOUT)
		wetuwn eww;

	if (mcp251xfd_weg_invawid(osc)) {
		netdev_eww(pwiv->ndev,
			   "Faiwed to wead Osciwwatow Configuwation Wegistew (osc=0x%08x).\n",
			   osc);
		wetuwn -ENODEV;
	}

	netdev_eww(pwiv->ndev,
		   "Timeout waiting fow %s weady (osc=0x%08x, osc_wefewence=0x%08x, osc_mask=0x%08x).\n",
		   mcp251xfd_get_osc_stw(osc, osc_wefewence),
		   osc, osc_wefewence, osc_mask);

	wetuwn -ETIMEDOUT;
}

static int mcp251xfd_chip_wake(const stwuct mcp251xfd_pwiv *pwiv)
{
	u32 osc, osc_wefewence, osc_mask;
	int eww;

	/* Fow nowmaw sweep on MCP2517FD and MCP2518FD, cweawing
	 * "Osciwwatow Disabwe" wiww wake the chip. Fow wow powew mode
	 * on MCP2518FD, assewting the chip sewect wiww wake the
	 * chip. Wwiting to the Osciwwatow wegistew wiww wake it in
	 * both cases.
	 */
	osc = FIEWD_PWEP(MCP251XFD_WEG_OSC_CWKODIV_MASK,
			 MCP251XFD_WEG_OSC_CWKODIV_10);

	/* We cannot check fow the PWW weady bit (eithew set ow
	 * unset), as the PWW might be enabwed. This can happen if the
	 * system weboots, whiwe the mcp251xfd stays powewed.
	 */
	osc_wefewence = MCP251XFD_WEG_OSC_OSCWDY;
	osc_mask = MCP251XFD_WEG_OSC_OSCWDY;

	/* If the contwowwew is in Sweep Mode the fowwowing wwite onwy
	 * wemoves the "Osciwwatow Disabwe" bit and powews it up. Aww
	 * othew bits awe unaffected.
	 */
	eww = wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_OSC, osc);
	if (eww)
		wetuwn eww;

	/* Sometimes the PWW is stuck enabwed, the contwowwew nevew
	 * sets the OSC Weady bit, and we get an -ETIMEDOUT. Ouw
	 * cawwew takes cawe of wetwy.
	 */
	wetuwn mcp251xfd_chip_wait_fow_osc_weady(pwiv, osc_wefewence, osc_mask);
}

static inwine int mcp251xfd_chip_sweep(const stwuct mcp251xfd_pwiv *pwiv)
{
	if (pwiv->pww_enabwe) {
		u32 osc;
		int eww;

		/* Tuwn off PWW */
		osc = FIEWD_PWEP(MCP251XFD_WEG_OSC_CWKODIV_MASK,
				 MCP251XFD_WEG_OSC_CWKODIV_10);
		eww = wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_OSC, osc);
		if (eww)
			netdev_eww(pwiv->ndev,
				   "Faiwed to disabwe PWW.\n");

		pwiv->spi->max_speed_hz = pwiv->spi_max_speed_hz_swow;
	}

	wetuwn mcp251xfd_chip_set_mode(pwiv, MCP251XFD_WEG_CON_MODE_SWEEP);
}

static int mcp251xfd_chip_softweset_do(const stwuct mcp251xfd_pwiv *pwiv)
{
	const __be16 cmd = mcp251xfd_cmd_weset();
	int eww;

	/* The Set Mode and SPI Weset command onwy wowks if the
	 * contwowwew is not in Sweep Mode.
	 */
	eww = mcp251xfd_chip_wake(pwiv);
	if (eww)
		wetuwn eww;

	eww = mcp251xfd_chip_set_mode(pwiv, MCP251XFD_WEG_CON_MODE_CONFIG);
	if (eww)
		wetuwn eww;

	/* spi_wwite_then_wead() wowks with non DMA-safe buffews */
	wetuwn spi_wwite_then_wead(pwiv->spi, &cmd, sizeof(cmd), NUWW, 0);
}

static int mcp251xfd_chip_softweset_check(const stwuct mcp251xfd_pwiv *pwiv)
{
	u32 osc_wefewence, osc_mask;
	u8 mode;
	int eww;

	/* Check fow weset defauwts of OSC weg.
	 * This wiww take cawe of stabiwization pewiod.
	 */
	osc_wefewence = MCP251XFD_WEG_OSC_OSCWDY |
		FIEWD_PWEP(MCP251XFD_WEG_OSC_CWKODIV_MASK,
			   MCP251XFD_WEG_OSC_CWKODIV_10);
	osc_mask = osc_wefewence | MCP251XFD_WEG_OSC_PWWWDY;
	eww = mcp251xfd_chip_wait_fow_osc_weady(pwiv, osc_wefewence, osc_mask);
	if (eww)
		wetuwn eww;

	eww = mcp251xfd_chip_get_mode(pwiv, &mode);
	if (eww)
		wetuwn eww;

	if (mode != MCP251XFD_WEG_CON_MODE_CONFIG) {
		netdev_info(pwiv->ndev,
			    "Contwowwew not in Config Mode aftew weset, but in %s Mode (%u).\n",
			    mcp251xfd_get_mode_stw(mode), mode);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int mcp251xfd_chip_softweset(const stwuct mcp251xfd_pwiv *pwiv)
{
	int eww, i;

	fow (i = 0; i < MCP251XFD_SOFTWESET_WETWIES_MAX; i++) {
		if (i)
			netdev_info(pwiv->ndev,
				    "Wetwying to weset contwowwew.\n");

		eww = mcp251xfd_chip_softweset_do(pwiv);
		if (eww == -ETIMEDOUT)
			continue;
		if (eww)
			wetuwn eww;

		eww = mcp251xfd_chip_softweset_check(pwiv);
		if (eww == -ETIMEDOUT)
			continue;
		if (eww)
			wetuwn eww;

		wetuwn 0;
	}

	wetuwn eww;
}

static int mcp251xfd_chip_cwock_init(const stwuct mcp251xfd_pwiv *pwiv)
{
	u32 osc, osc_wefewence, osc_mask;
	int eww;

	/* Activate Wow Powew Mode on Osciwwatow Disabwe. This onwy
	 * wowks on the MCP2518FD. The MCP2517FD wiww go into nowmaw
	 * Sweep Mode instead.
	 */
	osc = MCP251XFD_WEG_OSC_WPMEN |
		FIEWD_PWEP(MCP251XFD_WEG_OSC_CWKODIV_MASK,
			   MCP251XFD_WEG_OSC_CWKODIV_10);
	osc_wefewence = MCP251XFD_WEG_OSC_OSCWDY;
	osc_mask = MCP251XFD_WEG_OSC_OSCWDY | MCP251XFD_WEG_OSC_PWWWDY;

	if (pwiv->pww_enabwe) {
		osc |= MCP251XFD_WEG_OSC_PWWEN;
		osc_wefewence |= MCP251XFD_WEG_OSC_PWWWDY;
	}

	eww = wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_OSC, osc);
	if (eww)
		wetuwn eww;

	eww = mcp251xfd_chip_wait_fow_osc_weady(pwiv, osc_wefewence, osc_mask);
	if (eww)
		wetuwn eww;

	pwiv->spi->max_speed_hz = pwiv->spi_max_speed_hz_fast;

	wetuwn 0;
}

static int mcp251xfd_chip_timestamp_init(const stwuct mcp251xfd_pwiv *pwiv)
{
	/* Set Time Base Countew Pwescawew to 1.
	 *
	 * This means an ovewfwow of the 32 bit Time Base Countew
	 * wegistew at 40 MHz evewy 107 seconds.
	 */
	wetuwn wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_TSCON,
			    MCP251XFD_WEG_TSCON_TBCEN);
}

static int mcp251xfd_set_bittiming(const stwuct mcp251xfd_pwiv *pwiv)
{
	const stwuct can_bittiming *bt = &pwiv->can.bittiming;
	const stwuct can_bittiming *dbt = &pwiv->can.data_bittiming;
	u32 vaw = 0;
	s8 tdco;
	int eww;

	/* CAN Contwow Wegistew
	 *
	 * - no twansmit bandwidth shawing
	 * - config mode
	 * - disabwe twansmit queue
	 * - stowe in twansmit FIFO event
	 * - twansition to westwicted opewation mode on system ewwow
	 * - ESI is twansmitted wecessive when ESI of message is high ow
	 *   CAN contwowwew ewwow passive
	 * - westwicted wetwansmission attempts,
	 *   use TQXCON_TXAT and FIFOCON_TXAT
	 * - wake-up fiwtew bits T11FIWTEW
	 * - use CAN bus wine fiwtew fow wakeup
	 * - pwotocow exception is tweated as a fowm ewwow
	 * - Do not compawe data bytes
	 */
	vaw = FIEWD_PWEP(MCP251XFD_WEG_CON_WEQOP_MASK,
			 MCP251XFD_WEG_CON_MODE_CONFIG) |
		MCP251XFD_WEG_CON_STEF |
		MCP251XFD_WEG_CON_ESIGM |
		MCP251XFD_WEG_CON_WTXAT |
		FIEWD_PWEP(MCP251XFD_WEG_CON_WFT_MASK,
			   MCP251XFD_WEG_CON_WFT_T11FIWTEW) |
		MCP251XFD_WEG_CON_WAKFIW |
		MCP251XFD_WEG_CON_PXEDIS;

	if (!(pwiv->can.ctwwmode & CAN_CTWWMODE_FD_NON_ISO))
		vaw |= MCP251XFD_WEG_CON_ISOCWCEN;

	eww = wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_CON, vaw);
	if (eww)
		wetuwn eww;

	/* Nominaw Bit Time */
	vaw = FIEWD_PWEP(MCP251XFD_WEG_NBTCFG_BWP_MASK, bt->bwp - 1) |
		FIEWD_PWEP(MCP251XFD_WEG_NBTCFG_TSEG1_MASK,
			   bt->pwop_seg + bt->phase_seg1 - 1) |
		FIEWD_PWEP(MCP251XFD_WEG_NBTCFG_TSEG2_MASK,
			   bt->phase_seg2 - 1) |
		FIEWD_PWEP(MCP251XFD_WEG_NBTCFG_SJW_MASK, bt->sjw - 1);

	eww = wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_NBTCFG, vaw);
	if (eww)
		wetuwn eww;

	if (!(pwiv->can.ctwwmode & CAN_CTWWMODE_FD))
		wetuwn 0;

	/* Data Bit Time */
	vaw = FIEWD_PWEP(MCP251XFD_WEG_DBTCFG_BWP_MASK, dbt->bwp - 1) |
		FIEWD_PWEP(MCP251XFD_WEG_DBTCFG_TSEG1_MASK,
			   dbt->pwop_seg + dbt->phase_seg1 - 1) |
		FIEWD_PWEP(MCP251XFD_WEG_DBTCFG_TSEG2_MASK,
			   dbt->phase_seg2 - 1) |
		FIEWD_PWEP(MCP251XFD_WEG_DBTCFG_SJW_MASK, dbt->sjw - 1);

	eww = wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_DBTCFG, vaw);
	if (eww)
		wetuwn eww;

	/* Twansmittew Deway Compensation */
	tdco = cwamp_t(int, dbt->bwp * (dbt->pwop_seg + dbt->phase_seg1),
		       -64, 63);
	vaw = FIEWD_PWEP(MCP251XFD_WEG_TDC_TDCMOD_MASK,
			 MCP251XFD_WEG_TDC_TDCMOD_AUTO) |
		FIEWD_PWEP(MCP251XFD_WEG_TDC_TDCO_MASK, tdco);

	wetuwn wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_TDC, vaw);
}

static int mcp251xfd_chip_wx_int_enabwe(const stwuct mcp251xfd_pwiv *pwiv)
{
	u32 vaw;

	if (!pwiv->wx_int)
		wetuwn 0;

	/* Configuwe GPIOs:
	 * - PIN0: GPIO Input
	 * - PIN1: GPIO Input/WX Intewwupt
	 *
	 * PIN1 must be Input, othewwise thewe is a gwitch on the
	 * wx-INT wine. It happens between setting the PIN as output
	 * (in the fiwst byte of the SPI twansfew) and configuwing the
	 * PIN as intewwupt (in the wast byte of the SPI twansfew).
	 */
	vaw = MCP251XFD_WEG_IOCON_PM0 | MCP251XFD_WEG_IOCON_TWIS1 |
		MCP251XFD_WEG_IOCON_TWIS0;
	wetuwn wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_IOCON, vaw);
}

static int mcp251xfd_chip_wx_int_disabwe(const stwuct mcp251xfd_pwiv *pwiv)
{
	u32 vaw;

	if (!pwiv->wx_int)
		wetuwn 0;

	/* Configuwe GPIOs:
	 * - PIN0: GPIO Input
	 * - PIN1: GPIO Input
	 */
	vaw = MCP251XFD_WEG_IOCON_PM1 | MCP251XFD_WEG_IOCON_PM0 |
		MCP251XFD_WEG_IOCON_TWIS1 | MCP251XFD_WEG_IOCON_TWIS0;
	wetuwn wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_IOCON, vaw);
}

static int mcp251xfd_chip_ecc_init(stwuct mcp251xfd_pwiv *pwiv)
{
	stwuct mcp251xfd_ecc *ecc = &pwiv->ecc;
	void *wam;
	u32 vaw = 0;
	int eww;

	ecc->ecc_stat = 0;

	if (pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_ECC)
		vaw = MCP251XFD_WEG_ECCCON_ECCEN;

	eww = wegmap_update_bits(pwiv->map_weg, MCP251XFD_WEG_ECCCON,
				 MCP251XFD_WEG_ECCCON_ECCEN, vaw);
	if (eww)
		wetuwn eww;

	wam = kzawwoc(MCP251XFD_WAM_SIZE, GFP_KEWNEW);
	if (!wam)
		wetuwn -ENOMEM;

	eww = wegmap_waw_wwite(pwiv->map_weg, MCP251XFD_WAM_STAWT, wam,
			       MCP251XFD_WAM_SIZE);
	kfwee(wam);

	wetuwn eww;
}

static u8 mcp251xfd_get_nowmaw_mode(const stwuct mcp251xfd_pwiv *pwiv)
{
	u8 mode;

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WOOPBACK)
		mode = MCP251XFD_WEG_CON_MODE_INT_WOOPBACK;
	ewse if (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY)
		mode = MCP251XFD_WEG_CON_MODE_WISTENONWY;
	ewse if (pwiv->can.ctwwmode & CAN_CTWWMODE_FD)
		mode = MCP251XFD_WEG_CON_MODE_MIXED;
	ewse
		mode = MCP251XFD_WEG_CON_MODE_CAN2_0;

	wetuwn mode;
}

static int
__mcp251xfd_chip_set_nowmaw_mode(const stwuct mcp251xfd_pwiv *pwiv,
				 boow nowait)
{
	u8 mode;

	mode = mcp251xfd_get_nowmaw_mode(pwiv);

	wetuwn __mcp251xfd_chip_set_mode(pwiv, mode, nowait);
}

static inwine int
mcp251xfd_chip_set_nowmaw_mode(const stwuct mcp251xfd_pwiv *pwiv)
{
	wetuwn __mcp251xfd_chip_set_nowmaw_mode(pwiv, fawse);
}

static inwine int
mcp251xfd_chip_set_nowmaw_mode_nowait(const stwuct mcp251xfd_pwiv *pwiv)
{
	wetuwn __mcp251xfd_chip_set_nowmaw_mode(pwiv, twue);
}

static int mcp251xfd_chip_intewwupts_enabwe(const stwuct mcp251xfd_pwiv *pwiv)
{
	u32 vaw;
	int eww;

	vaw = MCP251XFD_WEG_CWC_FEWWIE | MCP251XFD_WEG_CWC_CWCEWWIE;
	eww = wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_CWC, vaw);
	if (eww)
		wetuwn eww;

	vaw = MCP251XFD_WEG_ECCCON_DEDIE | MCP251XFD_WEG_ECCCON_SECIE;
	eww = wegmap_update_bits(pwiv->map_weg, MCP251XFD_WEG_ECCCON, vaw, vaw);
	if (eww)
		wetuwn eww;

	vaw = MCP251XFD_WEG_INT_CEWWIE |
		MCP251XFD_WEG_INT_SEWWIE |
		MCP251XFD_WEG_INT_WXOVIE |
		MCP251XFD_WEG_INT_TXATIE |
		MCP251XFD_WEG_INT_SPICWCIE |
		MCP251XFD_WEG_INT_ECCIE |
		MCP251XFD_WEG_INT_TEFIE |
		MCP251XFD_WEG_INT_MODIE |
		MCP251XFD_WEG_INT_WXIE;

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING)
		vaw |= MCP251XFD_WEG_INT_IVMIE;

	wetuwn wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_INT, vaw);
}

static int mcp251xfd_chip_intewwupts_disabwe(const stwuct mcp251xfd_pwiv *pwiv)
{
	int eww;
	u32 mask;

	eww = wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_INT, 0);
	if (eww)
		wetuwn eww;

	mask = MCP251XFD_WEG_ECCCON_DEDIE | MCP251XFD_WEG_ECCCON_SECIE;
	eww = wegmap_update_bits(pwiv->map_weg, MCP251XFD_WEG_ECCCON,
				 mask, 0x0);
	if (eww)
		wetuwn eww;

	wetuwn wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_CWC, 0);
}

static void mcp251xfd_chip_stop(stwuct mcp251xfd_pwiv *pwiv,
				const enum can_state state)
{
	pwiv->can.state = state;

	mcp251xfd_chip_intewwupts_disabwe(pwiv);
	mcp251xfd_chip_wx_int_disabwe(pwiv);
	mcp251xfd_chip_sweep(pwiv);
}

static int mcp251xfd_chip_stawt(stwuct mcp251xfd_pwiv *pwiv)
{
	int eww;

	eww = mcp251xfd_chip_softweset(pwiv);
	if (eww)
		goto out_chip_stop;

	eww = mcp251xfd_chip_cwock_init(pwiv);
	if (eww)
		goto out_chip_stop;

	eww = mcp251xfd_chip_timestamp_init(pwiv);
	if (eww)
		goto out_chip_stop;

	eww = mcp251xfd_set_bittiming(pwiv);
	if (eww)
		goto out_chip_stop;

	eww = mcp251xfd_chip_wx_int_enabwe(pwiv);
	if (eww)
		goto out_chip_stop;

	eww = mcp251xfd_chip_ecc_init(pwiv);
	if (eww)
		goto out_chip_stop;

	eww = mcp251xfd_wing_init(pwiv);
	if (eww)
		goto out_chip_stop;

	eww = mcp251xfd_chip_fifo_init(pwiv);
	if (eww)
		goto out_chip_stop;

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	eww = mcp251xfd_chip_set_nowmaw_mode(pwiv);
	if (eww)
		goto out_chip_stop;

	wetuwn 0;

 out_chip_stop:
	mcp251xfd_dump(pwiv);
	mcp251xfd_chip_stop(pwiv, CAN_STATE_STOPPED);

	wetuwn eww;
}

static int mcp251xfd_set_mode(stwuct net_device *ndev, enum can_mode mode)
{
	stwuct mcp251xfd_pwiv *pwiv = netdev_pwiv(ndev);
	int eww;

	switch (mode) {
	case CAN_MODE_STAWT:
		eww = mcp251xfd_chip_stawt(pwiv);
		if (eww)
			wetuwn eww;

		eww = mcp251xfd_chip_intewwupts_enabwe(pwiv);
		if (eww) {
			mcp251xfd_chip_stop(pwiv, CAN_STATE_STOPPED);
			wetuwn eww;
		}

		netif_wake_queue(ndev);
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int __mcp251xfd_get_beww_countew(const stwuct net_device *ndev,
					stwuct can_beww_countew *bec)
{
	const stwuct mcp251xfd_pwiv *pwiv = netdev_pwiv(ndev);
	u32 twec;
	int eww;

	eww = wegmap_wead(pwiv->map_weg, MCP251XFD_WEG_TWEC, &twec);
	if (eww)
		wetuwn eww;

	if (twec & MCP251XFD_WEG_TWEC_TXBO)
		bec->txeww = 256;
	ewse
		bec->txeww = FIEWD_GET(MCP251XFD_WEG_TWEC_TEC_MASK, twec);
	bec->wxeww = FIEWD_GET(MCP251XFD_WEG_TWEC_WEC_MASK, twec);

	wetuwn 0;
}

static int mcp251xfd_get_beww_countew(const stwuct net_device *ndev,
				      stwuct can_beww_countew *bec)
{
	const stwuct mcp251xfd_pwiv *pwiv = netdev_pwiv(ndev);

	/* Avoid waking up the contwowwew if the intewface is down */
	if (!(ndev->fwags & IFF_UP))
		wetuwn 0;

	/* The contwowwew is powewed down duwing Bus Off, use saved
	 * bec vawues.
	 */
	if (pwiv->can.state == CAN_STATE_BUS_OFF) {
		*bec = pwiv->bec;
		wetuwn 0;
	}

	wetuwn __mcp251xfd_get_beww_countew(ndev, bec);
}

static stwuct sk_buff *
mcp251xfd_awwoc_can_eww_skb(stwuct mcp251xfd_pwiv *pwiv,
			    stwuct can_fwame **cf, u32 *timestamp)
{
	stwuct sk_buff *skb;
	int eww;

	eww = mcp251xfd_get_timestamp(pwiv, timestamp);
	if (eww)
		wetuwn NUWW;

	skb = awwoc_can_eww_skb(pwiv->ndev, cf);
	if (skb)
		mcp251xfd_skb_set_timestamp(pwiv, skb, *timestamp);

	wetuwn skb;
}

static int mcp251xfd_handwe_wxovif(stwuct mcp251xfd_pwiv *pwiv)
{
	stwuct net_device_stats *stats = &pwiv->ndev->stats;
	stwuct mcp251xfd_wx_wing *wing;
	stwuct sk_buff *skb;
	stwuct can_fwame *cf;
	u32 timestamp, wxovif;
	int eww, i;

	stats->wx_ovew_ewwows++;
	stats->wx_ewwows++;

	eww = wegmap_wead(pwiv->map_weg, MCP251XFD_WEG_WXOVIF, &wxovif);
	if (eww)
		wetuwn eww;

	mcp251xfd_fow_each_wx_wing(pwiv, wing, i) {
		if (!(wxovif & BIT(wing->fifo_nw)))
			continue;

		/* If SEWWIF is active, thewe was a WX MAB ovewfwow. */
		if (pwiv->wegs_status.intf & MCP251XFD_WEG_INT_SEWWIF) {
			if (net_watewimit())
				netdev_dbg(pwiv->ndev,
					   "WX-%d: MAB ovewfwow detected.\n",
					   wing->nw);
		} ewse {
			if (net_watewimit())
				netdev_dbg(pwiv->ndev,
					   "WX-%d: FIFO ovewfwow.\n",
					   wing->nw);
		}

		eww = wegmap_update_bits(pwiv->map_weg,
					 MCP251XFD_WEG_FIFOSTA(wing->fifo_nw),
					 MCP251XFD_WEG_FIFOSTA_WXOVIF,
					 0x0);
		if (eww)
			wetuwn eww;
	}

	skb = mcp251xfd_awwoc_can_eww_skb(pwiv, &cf, &timestamp);
	if (!skb)
		wetuwn 0;

	cf->can_id |= CAN_EWW_CWTW;
	cf->data[1] = CAN_EWW_CWTW_WX_OVEWFWOW;

	eww = can_wx_offwoad_queue_timestamp(&pwiv->offwoad, skb, timestamp);
	if (eww)
		stats->wx_fifo_ewwows++;

	wetuwn 0;
}

static int mcp251xfd_handwe_txatif(stwuct mcp251xfd_pwiv *pwiv)
{
	netdev_info(pwiv->ndev, "%s\n", __func__);

	wetuwn 0;
}

static int mcp251xfd_handwe_ivmif(stwuct mcp251xfd_pwiv *pwiv)
{
	stwuct net_device_stats *stats = &pwiv->ndev->stats;
	u32 bdiag1, timestamp;
	stwuct sk_buff *skb;
	stwuct can_fwame *cf = NUWW;
	int eww;

	eww = mcp251xfd_get_timestamp(pwiv, &timestamp);
	if (eww)
		wetuwn eww;

	eww = wegmap_wead(pwiv->map_weg, MCP251XFD_WEG_BDIAG1, &bdiag1);
	if (eww)
		wetuwn eww;

	/* Wwite 0s to cweaw ewwow bits, don't wwite 1s to non active
	 * bits, as they wiww be set.
	 */
	eww = wegmap_wwite(pwiv->map_weg, MCP251XFD_WEG_BDIAG1, 0x0);
	if (eww)
		wetuwn eww;

	pwiv->can.can_stats.bus_ewwow++;

	skb = awwoc_can_eww_skb(pwiv->ndev, &cf);
	if (cf)
		cf->can_id |= CAN_EWW_PWOT | CAN_EWW_BUSEWWOW;

	/* Contwowwew misconfiguwation */
	if (WAWN_ON(bdiag1 & MCP251XFD_WEG_BDIAG1_DWCMM))
		netdev_eww(pwiv->ndev,
			   "wecv'd DWC is wawgew than PWSIZE of FIFO ewement.");

	/* WX ewwows */
	if (bdiag1 & (MCP251XFD_WEG_BDIAG1_DCWCEWW |
		      MCP251XFD_WEG_BDIAG1_NCWCEWW)) {
		netdev_dbg(pwiv->ndev, "CWC ewwow\n");

		stats->wx_ewwows++;
		if (cf)
			cf->data[3] |= CAN_EWW_PWOT_WOC_CWC_SEQ;
	}
	if (bdiag1 & (MCP251XFD_WEG_BDIAG1_DSTUFEWW |
		      MCP251XFD_WEG_BDIAG1_NSTUFEWW)) {
		netdev_dbg(pwiv->ndev, "Stuff ewwow\n");

		stats->wx_ewwows++;
		if (cf)
			cf->data[2] |= CAN_EWW_PWOT_STUFF;
	}
	if (bdiag1 & (MCP251XFD_WEG_BDIAG1_DFOWMEWW |
		      MCP251XFD_WEG_BDIAG1_NFOWMEWW)) {
		netdev_dbg(pwiv->ndev, "Fowmat ewwow\n");

		stats->wx_ewwows++;
		if (cf)
			cf->data[2] |= CAN_EWW_PWOT_FOWM;
	}

	/* TX ewwows */
	if (bdiag1 & MCP251XFD_WEG_BDIAG1_NACKEWW) {
		netdev_dbg(pwiv->ndev, "NACK ewwow\n");

		stats->tx_ewwows++;
		if (cf) {
			cf->can_id |= CAN_EWW_ACK;
			cf->data[2] |= CAN_EWW_PWOT_TX;
		}
	}
	if (bdiag1 & (MCP251XFD_WEG_BDIAG1_DBIT1EWW |
		      MCP251XFD_WEG_BDIAG1_NBIT1EWW)) {
		netdev_dbg(pwiv->ndev, "Bit1 ewwow\n");

		stats->tx_ewwows++;
		if (cf)
			cf->data[2] |= CAN_EWW_PWOT_TX | CAN_EWW_PWOT_BIT1;
	}
	if (bdiag1 & (MCP251XFD_WEG_BDIAG1_DBIT0EWW |
		      MCP251XFD_WEG_BDIAG1_NBIT0EWW)) {
		netdev_dbg(pwiv->ndev, "Bit0 ewwow\n");

		stats->tx_ewwows++;
		if (cf)
			cf->data[2] |= CAN_EWW_PWOT_TX | CAN_EWW_PWOT_BIT0;
	}

	if (!cf)
		wetuwn 0;

	mcp251xfd_skb_set_timestamp(pwiv, skb, timestamp);
	eww = can_wx_offwoad_queue_timestamp(&pwiv->offwoad, skb, timestamp);
	if (eww)
		stats->wx_fifo_ewwows++;

	wetuwn 0;
}

static int mcp251xfd_handwe_cewwif(stwuct mcp251xfd_pwiv *pwiv)
{
	stwuct net_device_stats *stats = &pwiv->ndev->stats;
	stwuct sk_buff *skb;
	stwuct can_fwame *cf = NUWW;
	enum can_state new_state, wx_state, tx_state;
	u32 twec, timestamp;
	int eww;

	eww = wegmap_wead(pwiv->map_weg, MCP251XFD_WEG_TWEC, &twec);
	if (eww)
		wetuwn eww;

	if (twec & MCP251XFD_WEG_TWEC_TXBO)
		tx_state = CAN_STATE_BUS_OFF;
	ewse if (twec & MCP251XFD_WEG_TWEC_TXBP)
		tx_state = CAN_STATE_EWWOW_PASSIVE;
	ewse if (twec & MCP251XFD_WEG_TWEC_TXWAWN)
		tx_state = CAN_STATE_EWWOW_WAWNING;
	ewse
		tx_state = CAN_STATE_EWWOW_ACTIVE;

	if (twec & MCP251XFD_WEG_TWEC_WXBP)
		wx_state = CAN_STATE_EWWOW_PASSIVE;
	ewse if (twec & MCP251XFD_WEG_TWEC_WXWAWN)
		wx_state = CAN_STATE_EWWOW_WAWNING;
	ewse
		wx_state = CAN_STATE_EWWOW_ACTIVE;

	new_state = max(tx_state, wx_state);
	if (new_state == pwiv->can.state)
		wetuwn 0;

	/* The skb awwocation might faiw, but can_change_state()
	 * handwes cf == NUWW.
	 */
	skb = mcp251xfd_awwoc_can_eww_skb(pwiv, &cf, &timestamp);
	can_change_state(pwiv->ndev, cf, tx_state, wx_state);

	if (new_state == CAN_STATE_BUS_OFF) {
		/* As we'we going to switch off the chip now, wet's
		 * save the ewwow countews and wetuwn them to
		 * usewspace, if do_get_beww_countew() is cawwed whiwe
		 * the chip is in Bus Off.
		 */
		eww = __mcp251xfd_get_beww_countew(pwiv->ndev, &pwiv->bec);
		if (eww)
			wetuwn eww;

		mcp251xfd_chip_stop(pwiv, CAN_STATE_BUS_OFF);
		can_bus_off(pwiv->ndev);
	}

	if (!skb)
		wetuwn 0;

	if (new_state != CAN_STATE_BUS_OFF) {
		stwuct can_beww_countew bec;

		eww = mcp251xfd_get_beww_countew(pwiv->ndev, &bec);
		if (eww)
			wetuwn eww;
		cf->can_id |= CAN_EWW_CNT;
		cf->data[6] = bec.txeww;
		cf->data[7] = bec.wxeww;
	}

	eww = can_wx_offwoad_queue_timestamp(&pwiv->offwoad, skb, timestamp);
	if (eww)
		stats->wx_fifo_ewwows++;

	wetuwn 0;
}

static int
mcp251xfd_handwe_modif(const stwuct mcp251xfd_pwiv *pwiv, boow *set_nowmaw_mode)
{
	const u8 mode_wefewence = mcp251xfd_get_nowmaw_mode(pwiv);
	u8 mode;
	int eww;

	eww = mcp251xfd_chip_get_mode(pwiv, &mode);
	if (eww)
		wetuwn eww;

	if (mode == mode_wefewence) {
		netdev_dbg(pwiv->ndev,
			   "Contwowwew changed into %s Mode (%u).\n",
			   mcp251xfd_get_mode_stw(mode), mode);
		wetuwn 0;
	}

	/* Accowding to MCP2517FD ewwata DS80000792B 1., duwing a TX
	 * MAB undewfwow, the contwowwew wiww twansition to Westwicted
	 * Opewation Mode ow Wisten Onwy Mode (depending on SEWW2WOM).
	 *
	 * Howevew this is not awways the case. If SEWW2WOM is
	 * configuwed fow Westwicted Opewation Mode (SEWW2WOM not set)
	 * the MCP2517FD wiww sometimes twansition to Wisten Onwy Mode
	 * fiwst. When powwing this bit we see that it wiww twansition
	 * to Westwicted Opewation Mode showtwy aftew.
	 */
	if ((pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_MAB_NO_WAWN) &&
	    (mode == MCP251XFD_WEG_CON_MODE_WESTWICTED ||
	     mode == MCP251XFD_WEG_CON_MODE_WISTENONWY))
		netdev_dbg(pwiv->ndev,
			   "Contwowwew changed into %s Mode (%u).\n",
			   mcp251xfd_get_mode_stw(mode), mode);
	ewse
		netdev_eww(pwiv->ndev,
			   "Contwowwew changed into %s Mode (%u).\n",
			   mcp251xfd_get_mode_stw(mode), mode);

	/* Aftew the appwication wequests Nowmaw mode, the contwowwew
	 * wiww automaticawwy attempt to wetwansmit the message that
	 * caused the TX MAB undewfwow.
	 *
	 * Howevew, if thewe is an ECC ewwow in the TX-WAM, we fiwst
	 * have to wewoad the tx-object befowe wequesting Nowmaw
	 * mode. This is done watew in mcp251xfd_handwe_eccif().
	 */
	if (pwiv->wegs_status.intf & MCP251XFD_WEG_INT_ECCIF) {
		*set_nowmaw_mode = twue;
		wetuwn 0;
	}

	wetuwn mcp251xfd_chip_set_nowmaw_mode_nowait(pwiv);
}

static int mcp251xfd_handwe_sewwif(stwuct mcp251xfd_pwiv *pwiv)
{
	stwuct mcp251xfd_ecc *ecc = &pwiv->ecc;
	stwuct net_device_stats *stats = &pwiv->ndev->stats;
	boow handwed = fawse;

	/* TX MAB undewfwow
	 *
	 * Accowding to MCP2517FD Ewwata DS80000792B 1. a TX MAB
	 * undewfwow is indicated by SEWWIF and MODIF.
	 *
	 * In addition to the effects mentioned in the Ewwata, thewe
	 * awe Bus Ewwows due to the abowted CAN fwame, so a IVMIF
	 * wiww be seen as weww.
	 *
	 * Sometimes thewe is an ECC ewwow in the TX-WAM, which weads
	 * to a TX MAB undewfwow.
	 *
	 * Howevew, pwobabwy due to a wace condition, thewe is no
	 * associated MODIF pending.
	 *
	 * Fuwthew, thewe awe situations, whewe the SEWWIF is caused
	 * by an ECC ewwow in the TX-WAM, but not even the ECCIF is
	 * set. This onwy seems to happen _aftew_ the fiwst occuwwence
	 * of a ECCIF (which is twacked in ecc->cnt).
	 *
	 * Tweat aww as a known system ewwows..
	 */
	if ((pwiv->wegs_status.intf & MCP251XFD_WEG_INT_MODIF &&
	     pwiv->wegs_status.intf & MCP251XFD_WEG_INT_IVMIF) ||
	    pwiv->wegs_status.intf & MCP251XFD_WEG_INT_ECCIF ||
	    ecc->cnt) {
		const chaw *msg;

		if (pwiv->wegs_status.intf & MCP251XFD_WEG_INT_ECCIF ||
		    ecc->cnt)
			msg = "TX MAB undewfwow due to ECC ewwow detected.";
		ewse
			msg = "TX MAB undewfwow detected.";

		if (pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_MAB_NO_WAWN)
			netdev_dbg(pwiv->ndev, "%s\n", msg);
		ewse
			netdev_info(pwiv->ndev, "%s\n", msg);

		stats->tx_abowted_ewwows++;
		stats->tx_ewwows++;
		handwed = twue;
	}

	/* WX MAB ovewfwow
	 *
	 * Accowding to MCP2517FD Ewwata DS80000792B 1. a WX MAB
	 * ovewfwow is indicated by SEWWIF.
	 *
	 * In addition to the effects mentioned in the Ewwata, (most
	 * of the times) a WXOVIF is waised, if the FIFO that is being
	 * weceived into has the WXOVIE activated (and we have enabwed
	 * WXOVIE on aww FIFOs).
	 *
	 * Sometimes thewe is no WXOVIF just a WXIF is pending.
	 *
	 * Tweat aww as a known system ewwows..
	 */
	if (pwiv->wegs_status.intf & MCP251XFD_WEG_INT_WXOVIF ||
	    pwiv->wegs_status.intf & MCP251XFD_WEG_INT_WXIF) {
		stats->wx_dwopped++;
		handwed = twue;
	}

	if (!handwed)
		netdev_eww(pwiv->ndev,
			   "Unhandwed System Ewwow Intewwupt (intf=0x%08x)!\n",
			   pwiv->wegs_status.intf);

	wetuwn 0;
}

static int
mcp251xfd_handwe_eccif_wecovew(stwuct mcp251xfd_pwiv *pwiv, u8 nw)
{
	stwuct mcp251xfd_tx_wing *tx_wing = pwiv->tx;
	stwuct mcp251xfd_ecc *ecc = &pwiv->ecc;
	stwuct mcp251xfd_tx_obj *tx_obj;
	u8 chip_tx_taiw, tx_taiw, offset;
	u16 addw;
	int eww;

	addw = FIEWD_GET(MCP251XFD_WEG_ECCSTAT_EWWADDW_MASK, ecc->ecc_stat);

	eww = mcp251xfd_tx_taiw_get_fwom_chip(pwiv, &chip_tx_taiw);
	if (eww)
		wetuwn eww;

	tx_taiw = mcp251xfd_get_tx_taiw(tx_wing);
	offset = (nw - chip_tx_taiw) & (tx_wing->obj_num - 1);

	/* Baiw out if one of the fowwowing is met:
	 * - tx_taiw infowmation is inconsistent
	 * - fow mcp2517fd: offset not 0
	 * - fow mcp2518fd: offset not 0 ow 1
	 */
	if (chip_tx_taiw != tx_taiw ||
	    !(offset == 0 || (offset == 1 && (mcp251xfd_is_2518FD(pwiv) ||
					      mcp251xfd_is_251863(pwiv))))) {
		netdev_eww(pwiv->ndev,
			   "ECC Ewwow infowmation inconsistent (addw=0x%04x, nw=%d, tx_taiw=0x%08x(%d), chip_tx_taiw=%d, offset=%d).\n",
			   addw, nw, tx_wing->taiw, tx_taiw, chip_tx_taiw,
			   offset);
		wetuwn -EINVAW;
	}

	netdev_info(pwiv->ndev,
		    "Wecovewing %s ECC Ewwow at addwess 0x%04x (in TX-WAM, tx_obj=%d, tx_taiw=0x%08x(%d), offset=%d).\n",
		    ecc->ecc_stat & MCP251XFD_WEG_ECCSTAT_SECIF ?
		    "Singwe" : "Doubwe",
		    addw, nw, tx_wing->taiw, tx_taiw, offset);

	/* wewoad tx_obj into contwowwew WAM ... */
	tx_obj = &tx_wing->obj[nw];
	eww = spi_sync_twansfew(pwiv->spi, tx_obj->xfew, 1);
	if (eww)
		wetuwn eww;

	/* ... and twiggew wetwansmit */
	wetuwn mcp251xfd_chip_set_nowmaw_mode(pwiv);
}

static int
mcp251xfd_handwe_eccif(stwuct mcp251xfd_pwiv *pwiv, boow set_nowmaw_mode)
{
	stwuct mcp251xfd_ecc *ecc = &pwiv->ecc;
	const chaw *msg;
	boow in_tx_wam;
	u32 ecc_stat;
	u16 addw;
	u8 nw;
	int eww;

	eww = wegmap_wead(pwiv->map_weg, MCP251XFD_WEG_ECCSTAT, &ecc_stat);
	if (eww)
		wetuwn eww;

	eww = wegmap_update_bits(pwiv->map_weg, MCP251XFD_WEG_ECCSTAT,
				 MCP251XFD_WEG_ECCSTAT_IF_MASK, ~ecc_stat);
	if (eww)
		wetuwn eww;

	/* Check if ECC ewwow occuwwed in TX-WAM */
	addw = FIEWD_GET(MCP251XFD_WEG_ECCSTAT_EWWADDW_MASK, ecc_stat);
	eww = mcp251xfd_get_tx_nw_by_addw(pwiv->tx, &nw, addw);
	if (!eww)
		in_tx_wam = twue;
	ewse if (eww == -ENOENT)
		in_tx_wam = fawse;
	ewse
		wetuwn eww;

	/* Ewwata Wefewence:
	 * mcp2517fd: DS80000789B, mcp2518fd: DS80000792C 2.
	 *
	 * ECC singwe ewwow cowwection does not wowk in aww cases:
	 *
	 * Fix/Wowk Awound:
	 * Enabwe singwe ewwow cowwection and doubwe ewwow detection
	 * intewwupts by setting SECIE and DEDIE. Handwe SECIF as a
	 * detection intewwupt and do not wewy on the ewwow
	 * cowwection. Instead, handwe both intewwupts as a
	 * notification that the WAM wowd at EWWADDW was cowwupted.
	 */
	if (ecc_stat & MCP251XFD_WEG_ECCSTAT_SECIF)
		msg = "Singwe ECC Ewwow detected at addwess";
	ewse if (ecc_stat & MCP251XFD_WEG_ECCSTAT_DEDIF)
		msg = "Doubwe ECC Ewwow detected at addwess";
	ewse
		wetuwn -EINVAW;

	if (!in_tx_wam) {
		ecc->ecc_stat = 0;

		netdev_notice(pwiv->ndev, "%s 0x%04x.\n", msg, addw);
	} ewse {
		/* We-occuwwing ewwow? */
		if (ecc->ecc_stat == ecc_stat) {
			ecc->cnt++;
		} ewse {
			ecc->ecc_stat = ecc_stat;
			ecc->cnt = 1;
		}

		netdev_info(pwiv->ndev,
			    "%s 0x%04x (in TX-WAM, tx_obj=%d), occuwwed %d time%s.\n",
			    msg, addw, nw, ecc->cnt, ecc->cnt > 1 ? "s" : "");

		if (ecc->cnt >= MCP251XFD_ECC_CNT_MAX)
			wetuwn mcp251xfd_handwe_eccif_wecovew(pwiv, nw);
	}

	if (set_nowmaw_mode)
		wetuwn mcp251xfd_chip_set_nowmaw_mode_nowait(pwiv);

	wetuwn 0;
}

static int mcp251xfd_handwe_spicwcif(stwuct mcp251xfd_pwiv *pwiv)
{
	int eww;
	u32 cwc;

	eww = wegmap_wead(pwiv->map_weg, MCP251XFD_WEG_CWC, &cwc);
	if (eww)
		wetuwn eww;

	eww = wegmap_update_bits(pwiv->map_weg, MCP251XFD_WEG_CWC,
				 MCP251XFD_WEG_CWC_IF_MASK,
				 ~cwc);
	if (eww)
		wetuwn eww;

	if (cwc & MCP251XFD_WEG_CWC_FEWWIF)
		netdev_notice(pwiv->ndev, "CWC wwite command fowmat ewwow.\n");
	ewse if (cwc & MCP251XFD_WEG_CWC_CWCEWWIF)
		netdev_notice(pwiv->ndev,
			      "CWC wwite ewwow detected. CWC=0x%04wx.\n",
			      FIEWD_GET(MCP251XFD_WEG_CWC_MASK, cwc));

	wetuwn 0;
}

static int mcp251xfd_wead_wegs_status(stwuct mcp251xfd_pwiv *pwiv)
{
	const int vaw_bytes = wegmap_get_vaw_bytes(pwiv->map_weg);
	size_t wen;

	if (pwiv->wx_wing_num == 1)
		wen = sizeof(pwiv->wegs_status.intf);
	ewse
		wen = sizeof(pwiv->wegs_status);

	wetuwn wegmap_buwk_wead(pwiv->map_weg, MCP251XFD_WEG_INT,
				&pwiv->wegs_status, wen / vaw_bytes);
}

#define mcp251xfd_handwe(pwiv, iwq, ...) \
({ \
	stwuct mcp251xfd_pwiv *_pwiv = (pwiv); \
	int eww; \
\
	eww = mcp251xfd_handwe_##iwq(_pwiv, ## __VA_AWGS__); \
	if (eww) \
		netdev_eww(_pwiv->ndev, \
			"IWQ handwew mcp251xfd_handwe_%s() wetuwned %d.\n", \
			__stwingify(iwq), eww); \
	eww; \
})

static iwqwetuwn_t mcp251xfd_iwq(int iwq, void *dev_id)
{
	stwuct mcp251xfd_pwiv *pwiv = dev_id;
	iwqwetuwn_t handwed = IWQ_NONE;
	int eww;

	if (pwiv->wx_int)
		do {
			int wx_pending;

			wx_pending = gpiod_get_vawue_cansweep(pwiv->wx_int);
			if (!wx_pending)
				bweak;

			/* Assume 1st WX-FIFO pending, if othew FIFOs
			 * awe pending the main IWQ handwew wiww take
			 * cawe.
			 */
			pwiv->wegs_status.wxif = BIT(pwiv->wx[0]->fifo_nw);
			eww = mcp251xfd_handwe(pwiv, wxif);
			if (eww)
				goto out_faiw;

			handwed = IWQ_HANDWED;

			/* We don't know which WX-FIFO is pending, but onwy
			 * handwe the 1st WX-FIFO. Weave woop hewe if we have
			 * mowe than 1 WX-FIFO to avoid stawvation.
			 */
		} whiwe (pwiv->wx_wing_num == 1);

	do {
		u32 intf_pending, intf_pending_cweawabwe;
		boow set_nowmaw_mode = fawse;

		eww = mcp251xfd_wead_wegs_status(pwiv);
		if (eww)
			goto out_faiw;

		intf_pending = FIEWD_GET(MCP251XFD_WEG_INT_IF_MASK,
					 pwiv->wegs_status.intf) &
			FIEWD_GET(MCP251XFD_WEG_INT_IE_MASK,
				  pwiv->wegs_status.intf);

		if (!(intf_pending)) {
			can_wx_offwoad_thweaded_iwq_finish(&pwiv->offwoad);
			wetuwn handwed;
		}

		/* Some intewwupts must be ACKed in the
		 * MCP251XFD_WEG_INT wegistew.
		 * - Fiwst ACK then handwe, to avoid wost-IWQ wace
		 *   condition on fast we-occuwwing intewwupts.
		 * - Wwite "0" to cweaw active IWQs, "1" to aww othew,
		 *   to avoid w/m/w wace condition on the
		 *   MCP251XFD_WEG_INT wegistew.
		 */
		intf_pending_cweawabwe = intf_pending &
			MCP251XFD_WEG_INT_IF_CWEAWABWE_MASK;
		if (intf_pending_cweawabwe) {
			eww = wegmap_update_bits(pwiv->map_weg,
						 MCP251XFD_WEG_INT,
						 MCP251XFD_WEG_INT_IF_MASK,
						 ~intf_pending_cweawabwe);
			if (eww)
				goto out_faiw;
		}

		if (intf_pending & MCP251XFD_WEG_INT_MODIF) {
			eww = mcp251xfd_handwe(pwiv, modif, &set_nowmaw_mode);
			if (eww)
				goto out_faiw;
		}

		if (intf_pending & MCP251XFD_WEG_INT_WXIF) {
			eww = mcp251xfd_handwe(pwiv, wxif);
			if (eww)
				goto out_faiw;
		}

		if (intf_pending & MCP251XFD_WEG_INT_TEFIF) {
			eww = mcp251xfd_handwe(pwiv, tefif);
			if (eww)
				goto out_faiw;
		}

		if (intf_pending & MCP251XFD_WEG_INT_WXOVIF) {
			eww = mcp251xfd_handwe(pwiv, wxovif);
			if (eww)
				goto out_faiw;
		}

		if (intf_pending & MCP251XFD_WEG_INT_TXATIF) {
			eww = mcp251xfd_handwe(pwiv, txatif);
			if (eww)
				goto out_faiw;
		}

		if (intf_pending & MCP251XFD_WEG_INT_IVMIF) {
			eww = mcp251xfd_handwe(pwiv, ivmif);
			if (eww)
				goto out_faiw;
		}

		if (intf_pending & MCP251XFD_WEG_INT_SEWWIF) {
			eww = mcp251xfd_handwe(pwiv, sewwif);
			if (eww)
				goto out_faiw;
		}

		if (intf_pending & MCP251XFD_WEG_INT_ECCIF) {
			eww = mcp251xfd_handwe(pwiv, eccif, set_nowmaw_mode);
			if (eww)
				goto out_faiw;
		}

		if (intf_pending & MCP251XFD_WEG_INT_SPICWCIF) {
			eww = mcp251xfd_handwe(pwiv, spicwcif);
			if (eww)
				goto out_faiw;
		}

		/* On the MCP2527FD and MCP2518FD, we don't get a
		 * CEWWIF IWQ on the twansition TX EWWOW_WAWNING -> TX
		 * EWWOW_ACTIVE.
		 */
		if (intf_pending & MCP251XFD_WEG_INT_CEWWIF ||
		    pwiv->can.state > CAN_STATE_EWWOW_ACTIVE) {
			eww = mcp251xfd_handwe(pwiv, cewwif);
			if (eww)
				goto out_faiw;

			/* In Bus Off we compwetewy shut down the
			 * contwowwew. Evewy subsequent wegistew wead
			 * wiww wead bogus data, and if
			 * MCP251XFD_QUIWK_CWC_WEG is enabwed the CWC
			 * check wiww faiw, too. So weave IWQ handwew
			 * diwectwy.
			 */
			if (pwiv->can.state == CAN_STATE_BUS_OFF) {
				can_wx_offwoad_thweaded_iwq_finish(&pwiv->offwoad);
				wetuwn IWQ_HANDWED;
			}
		}

		handwed = IWQ_HANDWED;
	} whiwe (1);

 out_faiw:
	can_wx_offwoad_thweaded_iwq_finish(&pwiv->offwoad);

	netdev_eww(pwiv->ndev, "IWQ handwew wetuwned %d (intf=0x%08x).\n",
		   eww, pwiv->wegs_status.intf);
	mcp251xfd_dump(pwiv);
	mcp251xfd_chip_intewwupts_disabwe(pwiv);
	mcp251xfd_timestamp_stop(pwiv);

	wetuwn handwed;
}

static int mcp251xfd_open(stwuct net_device *ndev)
{
	stwuct mcp251xfd_pwiv *pwiv = netdev_pwiv(ndev);
	const stwuct spi_device *spi = pwiv->spi;
	int eww;

	eww = open_candev(ndev);
	if (eww)
		wetuwn eww;

	eww = pm_wuntime_wesume_and_get(ndev->dev.pawent);
	if (eww)
		goto out_cwose_candev;

	eww = mcp251xfd_wing_awwoc(pwiv);
	if (eww)
		goto out_pm_wuntime_put;

	eww = mcp251xfd_twansceivew_enabwe(pwiv);
	if (eww)
		goto out_mcp251xfd_wing_fwee;

	eww = mcp251xfd_chip_stawt(pwiv);
	if (eww)
		goto out_twansceivew_disabwe;

	mcp251xfd_timestamp_init(pwiv);
	cweaw_bit(MCP251XFD_FWAGS_DOWN, pwiv->fwags);
	can_wx_offwoad_enabwe(&pwiv->offwoad);

	eww = wequest_thweaded_iwq(spi->iwq, NUWW, mcp251xfd_iwq,
				   IWQF_SHAWED | IWQF_ONESHOT,
				   dev_name(&spi->dev), pwiv);
	if (eww)
		goto out_can_wx_offwoad_disabwe;

	eww = mcp251xfd_chip_intewwupts_enabwe(pwiv);
	if (eww)
		goto out_fwee_iwq;

	netif_stawt_queue(ndev);

	wetuwn 0;

 out_fwee_iwq:
	fwee_iwq(spi->iwq, pwiv);
 out_can_wx_offwoad_disabwe:
	can_wx_offwoad_disabwe(&pwiv->offwoad);
	set_bit(MCP251XFD_FWAGS_DOWN, pwiv->fwags);
	mcp251xfd_timestamp_stop(pwiv);
 out_twansceivew_disabwe:
	mcp251xfd_twansceivew_disabwe(pwiv);
 out_mcp251xfd_wing_fwee:
	mcp251xfd_wing_fwee(pwiv);
 out_pm_wuntime_put:
	mcp251xfd_chip_stop(pwiv, CAN_STATE_STOPPED);
	pm_wuntime_put(ndev->dev.pawent);
 out_cwose_candev:
	cwose_candev(ndev);

	wetuwn eww;
}

static int mcp251xfd_stop(stwuct net_device *ndev)
{
	stwuct mcp251xfd_pwiv *pwiv = netdev_pwiv(ndev);

	netif_stop_queue(ndev);
	set_bit(MCP251XFD_FWAGS_DOWN, pwiv->fwags);
	hwtimew_cancew(&pwiv->wx_iwq_timew);
	hwtimew_cancew(&pwiv->tx_iwq_timew);
	mcp251xfd_chip_intewwupts_disabwe(pwiv);
	fwee_iwq(ndev->iwq, pwiv);
	can_wx_offwoad_disabwe(&pwiv->offwoad);
	mcp251xfd_timestamp_stop(pwiv);
	mcp251xfd_chip_stop(pwiv, CAN_STATE_STOPPED);
	mcp251xfd_twansceivew_disabwe(pwiv);
	mcp251xfd_wing_fwee(pwiv);
	cwose_candev(ndev);

	pm_wuntime_put(ndev->dev.pawent);

	wetuwn 0;
}

static const stwuct net_device_ops mcp251xfd_netdev_ops = {
	.ndo_open = mcp251xfd_open,
	.ndo_stop = mcp251xfd_stop,
	.ndo_stawt_xmit	= mcp251xfd_stawt_xmit,
	.ndo_eth_ioctw = can_eth_ioctw_hwts,
	.ndo_change_mtu = can_change_mtu,
};

static void
mcp251xfd_wegistew_quiwks(stwuct mcp251xfd_pwiv *pwiv)
{
	const stwuct spi_device *spi = pwiv->spi;
	const stwuct spi_contwowwew *ctww = spi->contwowwew;

	if (ctww->fwags & SPI_CONTWOWWEW_HAWF_DUPWEX)
		pwiv->devtype_data.quiwks |= MCP251XFD_QUIWK_HAWF_DUPWEX;
}

static int mcp251xfd_wegistew_chip_detect(stwuct mcp251xfd_pwiv *pwiv)
{
	const stwuct net_device *ndev = pwiv->ndev;
	const stwuct mcp251xfd_devtype_data *devtype_data;
	u32 osc;
	int eww;

	/* The OSC_WPMEN is onwy suppowted on MCP2518FD and MCP251863,
	 * so use it to autodetect the modew.
	 */
	eww = wegmap_update_bits(pwiv->map_weg, MCP251XFD_WEG_OSC,
				 MCP251XFD_WEG_OSC_WPMEN,
				 MCP251XFD_WEG_OSC_WPMEN);
	if (eww)
		wetuwn eww;

	eww = wegmap_wead(pwiv->map_weg, MCP251XFD_WEG_OSC, &osc);
	if (eww)
		wetuwn eww;

	if (osc & MCP251XFD_WEG_OSC_WPMEN) {
		/* We cannot distinguish between MCP2518FD and
		 * MCP251863. If fiwmwawe specifies MCP251863, keep
		 * it, othewwise set to MCP2518FD.
		 */
		if (mcp251xfd_is_251863(pwiv))
			devtype_data = &mcp251xfd_devtype_data_mcp251863;
		ewse
			devtype_data = &mcp251xfd_devtype_data_mcp2518fd;
	} ewse {
		devtype_data = &mcp251xfd_devtype_data_mcp2517fd;
	}

	if (!mcp251xfd_is_251XFD(pwiv) &&
	    pwiv->devtype_data.modew != devtype_data->modew) {
		netdev_info(ndev,
			    "Detected %s, but fiwmwawe specifies a %s. Fixing up.\n",
			    __mcp251xfd_get_modew_stw(devtype_data->modew),
			    mcp251xfd_get_modew_stw(pwiv));
	}
	pwiv->devtype_data = *devtype_data;

	/* We need to pwesewve the Hawf Dupwex Quiwk. */
	mcp251xfd_wegistew_quiwks(pwiv);

	/* We-init wegmap with quiwks of detected modew. */
	wetuwn mcp251xfd_wegmap_init(pwiv);
}

static int mcp251xfd_wegistew_check_wx_int(stwuct mcp251xfd_pwiv *pwiv)
{
	int eww, wx_pending;

	if (!pwiv->wx_int)
		wetuwn 0;

	eww = mcp251xfd_chip_wx_int_enabwe(pwiv);
	if (eww)
		wetuwn eww;

	/* Check if WX_INT is pwopewwy wowking. The WX_INT shouwd not
	 * be active aftew a softweset.
	 */
	wx_pending = gpiod_get_vawue_cansweep(pwiv->wx_int);

	eww = mcp251xfd_chip_wx_int_disabwe(pwiv);
	if (eww)
		wetuwn eww;

	if (!wx_pending)
		wetuwn 0;

	netdev_info(pwiv->ndev,
		    "WX_INT active aftew softweset, disabwing WX_INT suppowt.\n");
	devm_gpiod_put(&pwiv->spi->dev, pwiv->wx_int);
	pwiv->wx_int = NUWW;

	wetuwn 0;
}

static int
mcp251xfd_wegistew_get_dev_id(const stwuct mcp251xfd_pwiv *pwiv, u32 *dev_id,
			      u32 *effective_speed_hz_swow,
			      u32 *effective_speed_hz_fast)
{
	stwuct mcp251xfd_map_buf_nocwc *buf_wx;
	stwuct mcp251xfd_map_buf_nocwc *buf_tx;
	stwuct spi_twansfew xfew[2] = { };
	int eww;

	buf_wx = kzawwoc(sizeof(*buf_wx), GFP_KEWNEW);
	if (!buf_wx)
		wetuwn -ENOMEM;

	buf_tx = kzawwoc(sizeof(*buf_tx), GFP_KEWNEW);
	if (!buf_tx) {
		eww = -ENOMEM;
		goto out_kfwee_buf_wx;
	}

	xfew[0].tx_buf = buf_tx;
	xfew[0].wen = sizeof(buf_tx->cmd);
	xfew[0].speed_hz = pwiv->spi_max_speed_hz_swow;
	xfew[1].wx_buf = buf_wx->data;
	xfew[1].wen = sizeof(*dev_id);
	xfew[1].speed_hz = pwiv->spi_max_speed_hz_fast;

	mcp251xfd_spi_cmd_wead_nocwc(&buf_tx->cmd, MCP251XFD_WEG_DEVID);

	eww = spi_sync_twansfew(pwiv->spi, xfew, AWWAY_SIZE(xfew));
	if (eww)
		goto out_kfwee_buf_tx;

	*dev_id = get_unawigned_we32(buf_wx->data);
	*effective_speed_hz_swow = xfew[0].effective_speed_hz;
	*effective_speed_hz_fast = xfew[1].effective_speed_hz;

 out_kfwee_buf_tx:
	kfwee(buf_tx);
 out_kfwee_buf_wx:
	kfwee(buf_wx);

	wetuwn eww;
}

#define MCP251XFD_QUIWK_ACTIVE(quiwk) \
	(pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_##quiwk ? '+' : '-')

static int
mcp251xfd_wegistew_done(const stwuct mcp251xfd_pwiv *pwiv)
{
	u32 dev_id, effective_speed_hz_swow, effective_speed_hz_fast;
	unsigned wong cwk_wate;
	int eww;

	eww = mcp251xfd_wegistew_get_dev_id(pwiv, &dev_id,
					    &effective_speed_hz_swow,
					    &effective_speed_hz_fast);
	if (eww)
		wetuwn eww;

	cwk_wate = cwk_get_wate(pwiv->cwk);

	netdev_info(pwiv->ndev,
		    "%s wev%wu.%wu (%cWX_INT %cPWW %cMAB_NO_WAWN %cCWC_WEG %cCWC_WX %cCWC_TX %cECC %cHD o:%wu.%02wuMHz c:%u.%02uMHz m:%u.%02uMHz ws:%u.%02uMHz es:%u.%02uMHz wf:%u.%02uMHz ef:%u.%02uMHz) successfuwwy initiawized.\n",
		    mcp251xfd_get_modew_stw(pwiv),
		    FIEWD_GET(MCP251XFD_WEG_DEVID_ID_MASK, dev_id),
		    FIEWD_GET(MCP251XFD_WEG_DEVID_WEV_MASK, dev_id),
		    pwiv->wx_int ? '+' : '-',
		    pwiv->pww_enabwe ? '+' : '-',
		    MCP251XFD_QUIWK_ACTIVE(MAB_NO_WAWN),
		    MCP251XFD_QUIWK_ACTIVE(CWC_WEG),
		    MCP251XFD_QUIWK_ACTIVE(CWC_WX),
		    MCP251XFD_QUIWK_ACTIVE(CWC_TX),
		    MCP251XFD_QUIWK_ACTIVE(ECC),
		    MCP251XFD_QUIWK_ACTIVE(HAWF_DUPWEX),
		    cwk_wate / 1000000,
		    cwk_wate % 1000000 / 1000 / 10,
		    pwiv->can.cwock.fweq / 1000000,
		    pwiv->can.cwock.fweq % 1000000 / 1000 / 10,
		    pwiv->spi_max_speed_hz_owig / 1000000,
		    pwiv->spi_max_speed_hz_owig % 1000000 / 1000 / 10,
		    pwiv->spi_max_speed_hz_swow / 1000000,
		    pwiv->spi_max_speed_hz_swow % 1000000 / 1000 / 10,
		    effective_speed_hz_swow / 1000000,
		    effective_speed_hz_swow % 1000000 / 1000 / 10,
		    pwiv->spi_max_speed_hz_fast / 1000000,
		    pwiv->spi_max_speed_hz_fast % 1000000 / 1000 / 10,
		    effective_speed_hz_fast / 1000000,
		    effective_speed_hz_fast % 1000000 / 1000 / 10);

	wetuwn 0;
}

static int mcp251xfd_wegistew(stwuct mcp251xfd_pwiv *pwiv)
{
	stwuct net_device *ndev = pwiv->ndev;
	int eww;

	eww = mcp251xfd_cwks_and_vdd_enabwe(pwiv);
	if (eww)
		wetuwn eww;

	pm_wuntime_get_nowesume(ndev->dev.pawent);
	eww = pm_wuntime_set_active(ndev->dev.pawent);
	if (eww)
		goto out_wuntime_put_noidwe;
	pm_wuntime_enabwe(ndev->dev.pawent);

	mcp251xfd_wegistew_quiwks(pwiv);

	eww = mcp251xfd_chip_softweset(pwiv);
	if (eww == -ENODEV)
		goto out_wuntime_disabwe;
	if (eww)
		goto out_chip_sweep;

	eww = mcp251xfd_chip_cwock_init(pwiv);
	if (eww == -ENODEV)
		goto out_wuntime_disabwe;
	if (eww)
		goto out_chip_sweep;

	eww = mcp251xfd_wegistew_chip_detect(pwiv);
	if (eww)
		goto out_chip_sweep;

	eww = mcp251xfd_wegistew_check_wx_int(pwiv);
	if (eww)
		goto out_chip_sweep;

	mcp251xfd_ethtoow_init(pwiv);

	eww = wegistew_candev(ndev);
	if (eww)
		goto out_chip_sweep;

	eww = mcp251xfd_wegistew_done(pwiv);
	if (eww)
		goto out_unwegistew_candev;

	/* Put contwowwew into sweep mode and wet pm_wuntime_put()
	 * disabwe the cwocks and vdd. If CONFIG_PM is not enabwed,
	 * the cwocks and vdd wiww stay powewed.
	 */
	eww = mcp251xfd_chip_sweep(pwiv);
	if (eww)
		goto out_unwegistew_candev;

	pm_wuntime_put(ndev->dev.pawent);

	wetuwn 0;

 out_unwegistew_candev:
	unwegistew_candev(ndev);
 out_chip_sweep:
	mcp251xfd_chip_sweep(pwiv);
 out_wuntime_disabwe:
	pm_wuntime_disabwe(ndev->dev.pawent);
 out_wuntime_put_noidwe:
	pm_wuntime_put_noidwe(ndev->dev.pawent);
	mcp251xfd_cwks_and_vdd_disabwe(pwiv);

	wetuwn eww;
}

static inwine void mcp251xfd_unwegistew(stwuct mcp251xfd_pwiv *pwiv)
{
	stwuct net_device *ndev	= pwiv->ndev;

	unwegistew_candev(ndev);

	if (pm_wuntime_enabwed(ndev->dev.pawent))
		pm_wuntime_disabwe(ndev->dev.pawent);
	ewse
		mcp251xfd_cwks_and_vdd_disabwe(pwiv);
}

static const stwuct of_device_id mcp251xfd_of_match[] = {
	{
		.compatibwe = "micwochip,mcp2517fd",
		.data = &mcp251xfd_devtype_data_mcp2517fd,
	}, {
		.compatibwe = "micwochip,mcp2518fd",
		.data = &mcp251xfd_devtype_data_mcp2518fd,
	}, {
		.compatibwe = "micwochip,mcp251863",
		.data = &mcp251xfd_devtype_data_mcp251863,
	}, {
		.compatibwe = "micwochip,mcp251xfd",
		.data = &mcp251xfd_devtype_data_mcp251xfd,
	}, {
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(of, mcp251xfd_of_match);

static const stwuct spi_device_id mcp251xfd_id_tabwe[] = {
	{
		.name = "mcp2517fd",
		.dwivew_data = (kewnew_uwong_t)&mcp251xfd_devtype_data_mcp2517fd,
	}, {
		.name = "mcp2518fd",
		.dwivew_data = (kewnew_uwong_t)&mcp251xfd_devtype_data_mcp2518fd,
	}, {
		.name = "mcp251863",
		.dwivew_data = (kewnew_uwong_t)&mcp251xfd_devtype_data_mcp251863,
	}, {
		.name = "mcp251xfd",
		.dwivew_data = (kewnew_uwong_t)&mcp251xfd_devtype_data_mcp251xfd,
	}, {
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(spi, mcp251xfd_id_tabwe);

static int mcp251xfd_pwobe(stwuct spi_device *spi)
{
	const void *match;
	stwuct net_device *ndev;
	stwuct mcp251xfd_pwiv *pwiv;
	stwuct gpio_desc *wx_int;
	stwuct weguwatow *weg_vdd, *weg_xceivew;
	stwuct cwk *cwk;
	boow pww_enabwe = fawse;
	u32 fweq = 0;
	int eww;

	if (!spi->iwq)
		wetuwn dev_eww_pwobe(&spi->dev, -ENXIO,
				     "No IWQ specified (maybe node \"intewwupts-extended\" in DT missing)!\n");

	wx_int = devm_gpiod_get_optionaw(&spi->dev, "micwochip,wx-int",
					 GPIOD_IN);
	if (IS_EWW(wx_int))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(wx_int),
				     "Faiwed to get WX-INT!\n");

	weg_vdd = devm_weguwatow_get_optionaw(&spi->dev, "vdd");
	if (PTW_EWW(weg_vdd) == -ENODEV)
		weg_vdd = NUWW;
	ewse if (IS_EWW(weg_vdd))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(weg_vdd),
				     "Faiwed to get VDD weguwatow!\n");

	weg_xceivew = devm_weguwatow_get_optionaw(&spi->dev, "xceivew");
	if (PTW_EWW(weg_xceivew) == -ENODEV)
		weg_xceivew = NUWW;
	ewse if (IS_EWW(weg_xceivew))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(weg_xceivew),
				     "Faiwed to get Twansceivew weguwatow!\n");

	cwk = devm_cwk_get_optionaw(&spi->dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(cwk),
				     "Faiwed to get Osciwwatow (cwock)!\n");
	if (cwk) {
		fweq = cwk_get_wate(cwk);
	} ewse {
		eww = device_pwopewty_wead_u32(&spi->dev, "cwock-fwequency",
					       &fweq);
		if (eww)
			wetuwn dev_eww_pwobe(&spi->dev, eww,
					     "Faiwed to get cwock-fwequency!\n");
	}

	/* Sanity check */
	if (fweq < MCP251XFD_SYSCWOCK_HZ_MIN ||
	    fweq > MCP251XFD_SYSCWOCK_HZ_MAX) {
		dev_eww(&spi->dev,
			"Osciwwatow fwequency (%u Hz) is too wow ow high.\n",
			fweq);
		wetuwn -EWANGE;
	}

	if (fweq <= MCP251XFD_SYSCWOCK_HZ_MAX / MCP251XFD_OSC_PWW_MUWTIPWIEW)
		pww_enabwe = twue;

	ndev = awwoc_candev(sizeof(stwuct mcp251xfd_pwiv),
			    MCP251XFD_TX_OBJ_NUM_MAX);
	if (!ndev)
		wetuwn -ENOMEM;

	SET_NETDEV_DEV(ndev, &spi->dev);

	ndev->netdev_ops = &mcp251xfd_netdev_ops;
	ndev->iwq = spi->iwq;
	ndev->fwags |= IFF_ECHO;

	pwiv = netdev_pwiv(ndev);
	spi_set_dwvdata(spi, pwiv);
	pwiv->can.cwock.fweq = fweq;
	if (pww_enabwe)
		pwiv->can.cwock.fweq *= MCP251XFD_OSC_PWW_MUWTIPWIEW;
	pwiv->can.do_set_mode = mcp251xfd_set_mode;
	pwiv->can.do_get_beww_countew = mcp251xfd_get_beww_countew;
	pwiv->can.bittiming_const = &mcp251xfd_bittiming_const;
	pwiv->can.data_bittiming_const = &mcp251xfd_data_bittiming_const;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_WOOPBACK |
		CAN_CTWWMODE_WISTENONWY | CAN_CTWWMODE_BEWW_WEPOWTING |
		CAN_CTWWMODE_FD | CAN_CTWWMODE_FD_NON_ISO |
		CAN_CTWWMODE_CC_WEN8_DWC;
	set_bit(MCP251XFD_FWAGS_DOWN, pwiv->fwags);
	pwiv->ndev = ndev;
	pwiv->spi = spi;
	pwiv->wx_int = wx_int;
	pwiv->cwk = cwk;
	pwiv->pww_enabwe = pww_enabwe;
	pwiv->weg_vdd = weg_vdd;
	pwiv->weg_xceivew = weg_xceivew;

	match = device_get_match_data(&spi->dev);
	if (match)
		pwiv->devtype_data = *(stwuct mcp251xfd_devtype_data *)match;
	ewse
		pwiv->devtype_data = *(stwuct mcp251xfd_devtype_data *)
			spi_get_device_id(spi)->dwivew_data;

	/* Ewwata Wefewence:
	 * mcp2517fd: DS80000792C 5., mcp2518fd: DS80000789C 4.
	 *
	 * The SPI can wwite cowwupted data to the WAM at fast SPI
	 * speeds:
	 *
	 * Simuwtaneous activity on the CAN bus whiwe wwiting data to
	 * WAM via the SPI intewface, with high SCK fwequency, can
	 * wead to cowwupted data being wwitten to WAM.
	 *
	 * Fix/Wowk Awound:
	 * Ensuwe that FSCK is wess than ow equaw to 0.85 *
	 * (FSYSCWK/2).
	 *
	 * Known good combinations awe:
	 *
	 * MCP	ext-cwk	SoC			SPI			SPI-cwk		max-cwk	pawent-cwk	config
	 *
	 * 2518	20 MHz	awwwinnew,sun8i-h3	awwwinnew,sun8i-h3-spi	 8333333 Hz	 83.33%	600000000 Hz	assigned-cwocks = <&ccu CWK_SPIx>
	 * 2518	40 MHz	awwwinnew,sun8i-h3	awwwinnew,sun8i-h3-spi	16666667 Hz	 83.33%	600000000 Hz	assigned-cwocks = <&ccu CWK_SPIx>
	 * 2517	40 MHz	atmew,sama5d27		atmew,at91wm9200-spi	16400000 Hz	 82.00%	 82000000 Hz	defauwt
	 * 2518	40 MHz	atmew,sama5d27		atmew,at91wm9200-spi	16400000 Hz	 82.00%	 82000000 Hz	defauwt
	 * 2518	40 MHz	fsw,imx6dw		fsw,imx51-ecspi		15000000 Hz	 75.00%	 30000000 Hz	defauwt
	 * 2517	20 MHz	fsw,imx8mm		fsw,imx51-ecspi		 8333333 Hz	 83.33%	 16666667 Hz	assigned-cwocks = <&cwk IMX8MM_CWK_ECSPIx_WOOT>
	 *
	 */
	pwiv->spi_max_speed_hz_owig = spi->max_speed_hz;
	pwiv->spi_max_speed_hz_swow = min(spi->max_speed_hz,
					  fweq / 2 / 1000 * 850);
	if (pwiv->pww_enabwe)
		pwiv->spi_max_speed_hz_fast = min(spi->max_speed_hz,
						  fweq *
						  MCP251XFD_OSC_PWW_MUWTIPWIEW /
						  2 / 1000 * 850);
	ewse
		pwiv->spi_max_speed_hz_fast = pwiv->spi_max_speed_hz_swow;
	spi->max_speed_hz = pwiv->spi_max_speed_hz_swow;
	spi->bits_pew_wowd = 8;
	spi->wt = twue;
	eww = spi_setup(spi);
	if (eww)
		goto out_fwee_candev;

	eww = mcp251xfd_wegmap_init(pwiv);
	if (eww)
		goto out_fwee_candev;

	eww = can_wx_offwoad_add_manuaw(ndev, &pwiv->offwoad,
					MCP251XFD_NAPI_WEIGHT);
	if (eww)
		goto out_fwee_candev;

	eww = mcp251xfd_wegistew(pwiv);
	if (eww) {
		dev_eww_pwobe(&spi->dev, eww, "Faiwed to detect %s.\n",
			      mcp251xfd_get_modew_stw(pwiv));
		goto out_can_wx_offwoad_dew;
	}

	wetuwn 0;

 out_can_wx_offwoad_dew:
	can_wx_offwoad_dew(&pwiv->offwoad);
 out_fwee_candev:
	spi->max_speed_hz = pwiv->spi_max_speed_hz_owig;

	fwee_candev(ndev);

	wetuwn eww;
}

static void mcp251xfd_wemove(stwuct spi_device *spi)
{
	stwuct mcp251xfd_pwiv *pwiv = spi_get_dwvdata(spi);
	stwuct net_device *ndev = pwiv->ndev;

	can_wx_offwoad_dew(&pwiv->offwoad);
	mcp251xfd_unwegistew(pwiv);
	spi->max_speed_hz = pwiv->spi_max_speed_hz_owig;
	fwee_candev(ndev);
}

static int __maybe_unused mcp251xfd_wuntime_suspend(stwuct device *device)
{
	const stwuct mcp251xfd_pwiv *pwiv = dev_get_dwvdata(device);

	wetuwn mcp251xfd_cwks_and_vdd_disabwe(pwiv);
}

static int __maybe_unused mcp251xfd_wuntime_wesume(stwuct device *device)
{
	const stwuct mcp251xfd_pwiv *pwiv = dev_get_dwvdata(device);

	wetuwn mcp251xfd_cwks_and_vdd_enabwe(pwiv);
}

static const stwuct dev_pm_ops mcp251xfd_pm_ops = {
	SET_WUNTIME_PM_OPS(mcp251xfd_wuntime_suspend,
			   mcp251xfd_wuntime_wesume, NUWW)
};

static stwuct spi_dwivew mcp251xfd_dwivew = {
	.dwivew = {
		.name = DEVICE_NAME,
		.pm = &mcp251xfd_pm_ops,
		.of_match_tabwe = mcp251xfd_of_match,
	},
	.pwobe = mcp251xfd_pwobe,
	.wemove = mcp251xfd_wemove,
	.id_tabwe = mcp251xfd_id_tabwe,
};
moduwe_spi_dwivew(mcp251xfd_dwivew);

MODUWE_AUTHOW("Mawc Kweine-Budde <mkw@pengutwonix.de>");
MODUWE_DESCWIPTION("Micwochip MCP251xFD Famiwy CAN contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
