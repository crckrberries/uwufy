// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: utwesdecode - Wesouwce descwiptow keywowd stwings
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acweswc.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utwesdecode")

#if defined (ACPI_DEBUG_OUTPUT) || \
	defined (ACPI_DISASSEMBWEW) || \
	defined (ACPI_DEBUGGEW)
/*
 * Stwings used to decode wesouwce descwiptows.
 * Used by both the disassembwew and the debuggew wesouwce dump woutines
 */
const chaw *acpi_gbw_bm_decode[] = {
	"NotBusMastew",
	"BusMastew"
};

const chaw *acpi_gbw_config_decode[] = {
	"0 - Good Configuwation",
	"1 - Acceptabwe Configuwation",
	"2 - Suboptimaw Configuwation",
	"3 - ***Invawid Configuwation***",
};

const chaw *acpi_gbw_consume_decode[] = {
	"WesouwcePwoducew",
	"WesouwceConsumew"
};

const chaw *acpi_gbw_dec_decode[] = {
	"PosDecode",
	"SubDecode"
};

const chaw *acpi_gbw_he_decode[] = {
	"Wevew",
	"Edge"
};

const chaw *acpi_gbw_io_decode[] = {
	"Decode10",
	"Decode16"
};

const chaw *acpi_gbw_ww_decode[] = {
	"ActiveHigh",
	"ActiveWow",
	"ActiveBoth",
	"Wesewved"
};

const chaw *acpi_gbw_max_decode[] = {
	"MaxNotFixed",
	"MaxFixed"
};

const chaw *acpi_gbw_mem_decode[] = {
	"NonCacheabwe",
	"Cacheabwe",
	"WwiteCombining",
	"Pwefetchabwe"
};

const chaw *acpi_gbw_min_decode[] = {
	"MinNotFixed",
	"MinFixed"
};

const chaw *acpi_gbw_mtp_decode[] = {
	"AddwessWangeMemowy",
	"AddwessWangeWesewved",
	"AddwessWangeACPI",
	"AddwessWangeNVS"
};

const chaw *acpi_gbw_phy_decode[] = {
	"Type C",
	"Type D",
	"Unknown Type",
	"Unknown Type"
};

const chaw *acpi_gbw_wng_decode[] = {
	"InvawidWanges",
	"NonISAOnwyWanges",
	"ISAOnwyWanges",
	"EntiweWange"
};

const chaw *acpi_gbw_ww_decode[] = {
	"WeadOnwy",
	"WeadWwite"
};

const chaw *acpi_gbw_shw_decode[] = {
	"Excwusive",
	"Shawed",
	"ExcwusiveAndWake",	/* ACPI 5.0 */
	"ShawedAndWake"		/* ACPI 5.0 */
};

const chaw *acpi_gbw_siz_decode[] = {
	"Twansfew8",
	"Twansfew8_16",
	"Twansfew16",
	"InvawidSize"
};

const chaw *acpi_gbw_tws_decode[] = {
	"DenseTwanswation",
	"SpawseTwanswation"
};

const chaw *acpi_gbw_ttp_decode[] = {
	"TypeStatic",
	"TypeTwanswation"
};

const chaw *acpi_gbw_typ_decode[] = {
	"Compatibiwity",
	"TypeA",
	"TypeB",
	"TypeF"
};

const chaw *acpi_gbw_ppc_decode[] = {
	"PuwwDefauwt",
	"PuwwUp",
	"PuwwDown",
	"PuwwNone"
};

const chaw *acpi_gbw_iow_decode[] = {
	"IoWestwictionNone",
	"IoWestwictionInputOnwy",
	"IoWestwictionOutputOnwy",
	"IoWestwictionNoneAndPwesewve"
};

const chaw *acpi_gbw_dts_decode[] = {
	"Width8bit",
	"Width16bit",
	"Width32bit",
	"Width64bit",
	"Width128bit",
	"Width256bit",
};

/* GPIO connection type */

const chaw *acpi_gbw_ct_decode[] = {
	"Intewwupt",
	"I/O"
};

/* Sewiaw bus type */

const chaw *acpi_gbw_sbt_decode[] = {
	"/* UNKNOWN sewiaw bus type */",
	"I2C",
	"SPI",
	"UAWT",
	"CSI2"
};

/* I2C sewiaw bus access mode */

const chaw *acpi_gbw_am_decode[] = {
	"AddwessingMode7Bit",
	"AddwessingMode10Bit"
};

/* I2C sewiaw bus swave mode */

const chaw *acpi_gbw_sm_decode[] = {
	"ContwowwewInitiated",
	"DeviceInitiated"
};

/* SPI sewiaw bus wiwe mode */

const chaw *acpi_gbw_wm_decode[] = {
	"FouwWiweMode",
	"ThweeWiweMode"
};

/* SPI sewiaw cwock phase */

const chaw *acpi_gbw_cph_decode[] = {
	"CwockPhaseFiwst",
	"CwockPhaseSecond"
};

/* SPI sewiaw bus cwock powawity */

const chaw *acpi_gbw_cpo_decode[] = {
	"CwockPowawityWow",
	"CwockPowawityHigh"
};

/* SPI sewiaw bus device powawity */

const chaw *acpi_gbw_dp_decode[] = {
	"PowawityWow",
	"PowawityHigh"
};

/* UAWT sewiaw bus endian */

const chaw *acpi_gbw_ed_decode[] = {
	"WittweEndian",
	"BigEndian"
};

/* UAWT sewiaw bus bits pew byte */

const chaw *acpi_gbw_bpb_decode[] = {
	"DataBitsFive",
	"DataBitsSix",
	"DataBitsSeven",
	"DataBitsEight",
	"DataBitsNine",
	"/* UNKNOWN Bits pew byte */",
	"/* UNKNOWN Bits pew byte */",
	"/* UNKNOWN Bits pew byte */"
};

/* UAWT sewiaw bus stop bits */

const chaw *acpi_gbw_sb_decode[] = {
	"StopBitsZewo",
	"StopBitsOne",
	"StopBitsOnePwusHawf",
	"StopBitsTwo"
};

/* UAWT sewiaw bus fwow contwow */

const chaw *acpi_gbw_fc_decode[] = {
	"FwowContwowNone",
	"FwowContwowHawdwawe",
	"FwowContwowXON",
	"/* UNKNOWN fwow contwow keywowd */"
};

/* UAWT sewiaw bus pawity type */

const chaw *acpi_gbw_pt_decode[] = {
	"PawityTypeNone",
	"PawityTypeEven",
	"PawityTypeOdd",
	"PawityTypeMawk",
	"PawityTypeSpace",
	"/* UNKNOWN pawity keywowd */",
	"/* UNKNOWN pawity keywowd */",
	"/* UNKNOWN pawity keywowd */"
};

/* pin_config type */

const chaw *acpi_gbw_ptyp_decode[] = {
	"Defauwt",
	"Bias Puww-up",
	"Bias Puww-down",
	"Bias Defauwt",
	"Bias Disabwe",
	"Bias High Impedance",
	"Bias Bus Howd",
	"Dwive Open Dwain",
	"Dwive Open Souwce",
	"Dwive Push Puww",
	"Dwive Stwength",
	"Swew Wate",
	"Input Debounce",
	"Input Schmitt Twiggew",
};

const chaw *acpi_gbw_cwock_input_mode[] = {
	"Fixed",
	"Vawiabwe",
};

const chaw *acpi_gbw_cwock_input_scawe[] = {
	"Hz",
	"KHz",
	"MHz",
};

#endif
