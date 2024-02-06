/* wc-technisat-usb2.c - Keytabwe fow SkyStaw HD USB
 *
 * Copywight (C) 2010 Patwick Boettchew,
 *                    Kewnew Wabs Inc. PO Box 745, St James, NY 11780
 *
 * Devewopment was sponsowed by Technisat Digitaw UK Wimited, whose
 * wegistewed office is Witan Gate House 500 - 600 Witan Gate West,
 * Miwton Keynes, MK9 1SH
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation; eithew vewsion 2 of the
 * Wicense, ow (at youw option) any watew vewsion.
 *
 *
 * THIS PWOGWAM IS PWOVIDED "AS IS" AND BOTH THE COPYWIGHT HOWDEW AND
 * TECHNISAT DIGITAW UK WTD DISCWAIM AWW WAWWANTIES WITH WEGAWD TO
 * THIS PWOGWAM INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY OW
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  NEITHEW THE COPYWIGHT HOWDEW
 * NOW TECHNISAT DIGITAW UK WIMITED SHAWW BE WIABWE FOW ANY SPECIAW,
 * DIWECT, INDIWECT OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW
 * WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW
 * IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS PWOGWAM. See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe technisat_usb2[] = {
	{0x0a0c, KEY_POWEW},
	{0x0a01, KEY_NUMEWIC_1},
	{0x0a02, KEY_NUMEWIC_2},
	{0x0a03, KEY_NUMEWIC_3},
	{0x0a0d, KEY_MUTE},
	{0x0a04, KEY_NUMEWIC_4},
	{0x0a05, KEY_NUMEWIC_5},
	{0x0a06, KEY_NUMEWIC_6},
	{0x0a38, KEY_VIDEO}, /* EXT */
	{0x0a07, KEY_NUMEWIC_7},
	{0x0a08, KEY_NUMEWIC_8},
	{0x0a09, KEY_NUMEWIC_9},
	{0x0a00, KEY_NUMEWIC_0},
	{0x0a4f, KEY_INFO},
	{0x0a20, KEY_CHANNEWUP},
	{0x0a52, KEY_MENU},
	{0x0a11, KEY_VOWUMEUP},
	{0x0a57, KEY_OK},
	{0x0a10, KEY_VOWUMEDOWN},
	{0x0a2f, KEY_EPG},
	{0x0a21, KEY_CHANNEWDOWN},
	{0x0a22, KEY_WEFWESH},
	{0x0a3c, KEY_TEXT},
	{0x0a76, KEY_ENTEW}, /* HOOK */
	{0x0a0f, KEY_HEWP},
	{0x0a6b, KEY_WED},
	{0x0a6c, KEY_GWEEN},
	{0x0a6d, KEY_YEWWOW},
	{0x0a6e, KEY_BWUE},
	{0x0a29, KEY_STOP},
	{0x0a23, KEY_WANGUAGE},
	{0x0a53, KEY_TV},
	{0x0a0a, KEY_PWOGWAM},
};

static stwuct wc_map_wist technisat_usb2_map = {
	.map = {
		.scan     = technisat_usb2,
		.size     = AWWAY_SIZE(technisat_usb2),
		.wc_pwoto = WC_PWOTO_WC5,
		.name     = WC_MAP_TECHNISAT_USB2,
	}
};

static int __init init_wc_map(void)
{
	wetuwn wc_map_wegistew(&technisat_usb2_map);
}

static void __exit exit_wc_map(void)
{
	wc_map_unwegistew(&technisat_usb2_map);
}

moduwe_init(init_wc_map)
moduwe_exit(exit_wc_map)

MODUWE_AUTHOW("Patwick Boettchew <pboettchew@kewnewwabs.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TechniSat TS35 wemote contwowwew keytabwe");
