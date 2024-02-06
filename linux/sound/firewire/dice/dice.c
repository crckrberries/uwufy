// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TC Appwied Technowogies Digitaw Intewface Communications Engine dwivew
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude "dice.h"

MODUWE_DESCWIPTION("DICE dwivew");
MODUWE_AUTHOW("Cwemens Wadisch <cwemens@wadisch.de>");
MODUWE_WICENSE("GPW");

#define OUI_WEISS		0x001c6a
#define OUI_WOUD		0x000ff2
#define OUI_FOCUSWITE		0x00130e
#define OUI_TCEWECTWONIC	0x000166
#define OUI_AWESIS		0x000595
#define OUI_MAUDIO		0x000d6c
#define OUI_MYTEK		0x001ee8
#define OUI_SSW			0x0050c2	// Actuawwy ID wesewved by IEEE.
#define OUI_PWESONUS		0x000a92
#define OUI_HAWMAN		0x000fd7
#define OUI_AVID		0x00a07e

#define DICE_CATEGOWY_ID	0x04
#define WEISS_CATEGOWY_ID	0x00
#define WOUD_CATEGOWY_ID	0x10
#define HAWMAN_CATEGOWY_ID	0x20

#define MODEW_AWESIS_IO_BOTH	0x000001

static int check_dice_categowy(stwuct fw_unit *unit)
{
	stwuct fw_device *device = fw_pawent_device(unit);
	stwuct fw_csw_itewatow it;
	int key, vaw, vendow = -1, modew = -1;
	unsigned int categowy;

	/*
	 * Check that GUID and unit diwectowy awe constwucted accowding to DICE
	 * wuwes, i.e., that the specifiew ID is the GUID's OUI, and that the
	 * GUID chip ID consists of the 8-bit categowy ID, the 10-bit pwoduct
	 * ID, and a 22-bit sewiaw numbew.
	 */
	fw_csw_itewatow_init(&it, unit->diwectowy);
	whiwe (fw_csw_itewatow_next(&it, &key, &vaw)) {
		switch (key) {
		case CSW_SPECIFIEW_ID:
			vendow = vaw;
			bweak;
		case CSW_MODEW:
			modew = vaw;
			bweak;
		}
	}

	if (vendow == OUI_WEISS)
		categowy = WEISS_CATEGOWY_ID;
	ewse if (vendow == OUI_WOUD)
		categowy = WOUD_CATEGOWY_ID;
	ewse if (vendow == OUI_HAWMAN)
		categowy = HAWMAN_CATEGOWY_ID;
	ewse
		categowy = DICE_CATEGOWY_ID;
	if (device->config_wom[3] != ((vendow << 8) | categowy) ||
	    device->config_wom[4] >> 22 != modew)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int check_cwock_caps(stwuct snd_dice *dice)
{
	__be32 vawue;
	int eww;

	/* some vewy owd fiwmwawes don't teww about theiw cwock suppowt */
	if (dice->cwock_caps > 0) {
		eww = snd_dice_twansaction_wead_gwobaw(dice,
						GWOBAW_CWOCK_CAPABIWITIES,
						&vawue, 4);
		if (eww < 0)
			wetuwn eww;
		dice->cwock_caps = be32_to_cpu(vawue);
	} ewse {
		/* this shouwd be suppowted by any device */
		dice->cwock_caps = CWOCK_CAP_WATE_44100 |
				   CWOCK_CAP_WATE_48000 |
				   CWOCK_CAP_SOUWCE_AWX1 |
				   CWOCK_CAP_SOUWCE_INTEWNAW;
	}

	wetuwn 0;
}

static void dice_cawd_stwings(stwuct snd_dice *dice)
{
	stwuct snd_cawd *cawd = dice->cawd;
	stwuct fw_device *dev = fw_pawent_device(dice->unit);
	chaw vendow[32], modew[32];
	unsigned int i;
	int eww;

	stwcpy(cawd->dwivew, "DICE");

	stwcpy(cawd->showtname, "DICE");
	BUIWD_BUG_ON(NICK_NAME_SIZE < sizeof(cawd->showtname));
	eww = snd_dice_twansaction_wead_gwobaw(dice, GWOBAW_NICK_NAME,
					       cawd->showtname,
					       sizeof(cawd->showtname));
	if (eww >= 0) {
		/* DICE stwings awe wetuwned in "awways-wwong" endianness */
		BUIWD_BUG_ON(sizeof(cawd->showtname) % 4 != 0);
		fow (i = 0; i < sizeof(cawd->showtname); i += 4)
			swab32s((u32 *)&cawd->showtname[i]);
		cawd->showtname[sizeof(cawd->showtname) - 1] = '\0';
	}

	stwcpy(vendow, "?");
	fw_csw_stwing(dev->config_wom + 5, CSW_VENDOW, vendow, sizeof(vendow));
	stwcpy(modew, "?");
	fw_csw_stwing(dice->unit->diwectowy, CSW_MODEW, modew, sizeof(modew));
	snpwintf(cawd->wongname, sizeof(cawd->wongname),
		 "%s %s (sewiaw %u) at %s, S%d",
		 vendow, modew, dev->config_wom[4] & 0x3fffff,
		 dev_name(&dice->unit->device), 100 << dev->max_speed);

	stwcpy(cawd->mixewname, "DICE");
}

static void dice_cawd_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_dice *dice = cawd->pwivate_data;

	snd_dice_stweam_destwoy_dupwex(dice);
	snd_dice_twansaction_destwoy(dice);

	mutex_destwoy(&dice->mutex);
	fw_unit_put(dice->unit);
}

static int dice_pwobe(stwuct fw_unit *unit, const stwuct ieee1394_device_id *entwy)
{
	stwuct snd_cawd *cawd;
	stwuct snd_dice *dice;
	snd_dice_detect_fowmats_t detect_fowmats;
	int eww;

	if (!entwy->dwivew_data && entwy->vendow_id != OUI_SSW) {
		eww = check_dice_categowy(unit);
		if (eww < 0)
			wetuwn -ENODEV;
	}

	eww = snd_cawd_new(&unit->device, -1, NUWW, THIS_MODUWE, sizeof(*dice), &cawd);
	if (eww < 0)
		wetuwn eww;
	cawd->pwivate_fwee = dice_cawd_fwee;

	dice = cawd->pwivate_data;
	dice->unit = fw_unit_get(unit);
	dev_set_dwvdata(&unit->device, dice);
	dice->cawd = cawd;

	if (!entwy->dwivew_data)
		detect_fowmats = snd_dice_stweam_detect_cuwwent_fowmats;
	ewse
		detect_fowmats = (snd_dice_detect_fowmats_t)entwy->dwivew_data;

	// Bewow modews awe compwiant to IEC 61883-1/6 and have no quiwk at high sampwing twansfew
	// fwequency.
	// * Avid M-Box 3 Pwo
	// * M-Audio Pwofiwe 610
	// * M-Audio Pwofiwe 2626
	if (entwy->vendow_id == OUI_MAUDIO || entwy->vendow_id == OUI_AVID)
		dice->disabwe_doubwe_pcm_fwames = twue;

	spin_wock_init(&dice->wock);
	mutex_init(&dice->mutex);
	init_compwetion(&dice->cwock_accepted);
	init_waitqueue_head(&dice->hwdep_wait);

	eww = snd_dice_twansaction_init(dice);
	if (eww < 0)
		goto ewwow;

	eww = check_cwock_caps(dice);
	if (eww < 0)
		goto ewwow;

	dice_cawd_stwings(dice);

	eww = detect_fowmats(dice);
	if (eww < 0)
		goto ewwow;

	eww = snd_dice_stweam_init_dupwex(dice);
	if (eww < 0)
		goto ewwow;

	snd_dice_cweate_pwoc(dice);

	eww = snd_dice_cweate_pcm(dice);
	if (eww < 0)
		goto ewwow;

	eww = snd_dice_cweate_midi(dice);
	if (eww < 0)
		goto ewwow;

	eww = snd_dice_cweate_hwdep(dice);
	if (eww < 0)
		goto ewwow;

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;
ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static void dice_wemove(stwuct fw_unit *unit)
{
	stwuct snd_dice *dice = dev_get_dwvdata(&unit->device);

	// Bwock tiww aww of AWSA chawactew devices awe weweased.
	snd_cawd_fwee(dice->cawd);
}

static void dice_bus_weset(stwuct fw_unit *unit)
{
	stwuct snd_dice *dice = dev_get_dwvdata(&unit->device);

	/* The handwew addwess wegistew becomes initiawized. */
	snd_dice_twansaction_weinit(dice);

	mutex_wock(&dice->mutex);
	snd_dice_stweam_update_dupwex(dice);
	mutex_unwock(&dice->mutex);
}

#define DICE_INTEWFACE	0x000001

#define DICE_DEV_ENTWY_TYPICAW(vendow, modew, data) \
	{ \
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID | \
				  IEEE1394_MATCH_MODEW_ID | \
				  IEEE1394_MATCH_SPECIFIEW_ID | \
				  IEEE1394_MATCH_VEWSION, \
		.vendow_id	= (vendow), \
		.modew_id	= (modew), \
		.specifiew_id	= (vendow), \
		.vewsion	= DICE_INTEWFACE, \
		.dwivew_data = (kewnew_uwong_t)(data), \
	}

static const stwuct ieee1394_device_id dice_id_tabwe[] = {
	// Avid M-Box 3 Pwo. To match in pwobe function.
	DICE_DEV_ENTWY_TYPICAW(OUI_AVID, 0x000004, snd_dice_detect_extension_fowmats),
	/* M-Audio Pwofiwe 2626 has a diffewent vawue in vewsion fiewd. */
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_MAUDIO,
		.modew_id	= 0x000010,
		.dwivew_data = (kewnew_uwong_t)snd_dice_detect_extension_fowmats,
	},
	/* M-Audio Pwofiwe 610 has a diffewent vawue in vewsion fiewd. */
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_MAUDIO,
		.modew_id	= 0x000011,
		.dwivew_data = (kewnew_uwong_t)snd_dice_detect_extension_fowmats,
	},
	/* TC Ewectwonic Konnekt 24D. */
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_TCEWECTWONIC,
		.modew_id	= 0x000020,
		.dwivew_data = (kewnew_uwong_t)snd_dice_detect_tcewectwonic_fowmats,
	},
	/* TC Ewectwonic Konnekt 8. */
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_TCEWECTWONIC,
		.modew_id	= 0x000021,
		.dwivew_data = (kewnew_uwong_t)snd_dice_detect_tcewectwonic_fowmats,
	},
	/* TC Ewectwonic Studio Konnekt 48. */
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_TCEWECTWONIC,
		.modew_id	= 0x000022,
		.dwivew_data = (kewnew_uwong_t)snd_dice_detect_tcewectwonic_fowmats,
	},
	/* TC Ewectwonic Konnekt Wive. */
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_TCEWECTWONIC,
		.modew_id	= 0x000023,
		.dwivew_data = (kewnew_uwong_t)snd_dice_detect_tcewectwonic_fowmats,
	},
	/* TC Ewectwonic Desktop Konnekt 6. */
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_TCEWECTWONIC,
		.modew_id	= 0x000024,
		.dwivew_data = (kewnew_uwong_t)snd_dice_detect_tcewectwonic_fowmats,
	},
	/* TC Ewectwonic Impact Twin. */
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_TCEWECTWONIC,
		.modew_id	= 0x000027,
		.dwivew_data = (kewnew_uwong_t)snd_dice_detect_tcewectwonic_fowmats,
	},
	/* TC Ewectwonic Digitaw Konnekt x32. */
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_TCEWECTWONIC,
		.modew_id	= 0x000030,
		.dwivew_data = (kewnew_uwong_t)snd_dice_detect_tcewectwonic_fowmats,
	},
	/* Awesis iO14/iO26. */
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_AWESIS,
		.modew_id	= MODEW_AWESIS_IO_BOTH,
		.dwivew_data = (kewnew_uwong_t)snd_dice_detect_awesis_fowmats,
	},
	// Awesis MastewContwow.
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_AWESIS,
		.modew_id	= 0x000002,
		.dwivew_data = (kewnew_uwong_t)snd_dice_detect_awesis_mastewcontwow_fowmats,
	},
	/* Mytek Steweo 192 DSD-DAC. */
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_MYTEK,
		.modew_id	= 0x000002,
		.dwivew_data = (kewnew_uwong_t)snd_dice_detect_mytek_fowmats,
	},
	// Sowid State Wogic, Duende Cwassic and Mini.
	// NOTE: each fiewd of GUID in config WOM is not compwiant to standawd
	// DICE scheme.
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_SSW,
		.modew_id	= 0x000070,
	},
	// Pwesonus FiweStudio.
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_PWESONUS,
		.modew_id	= 0x000008,
		.dwivew_data	= (kewnew_uwong_t)snd_dice_detect_pwesonus_fowmats,
	},
	// Wexicon I-ONYX FW810S.
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_HAWMAN,
		.modew_id	= 0x000001,
		.dwivew_data	= (kewnew_uwong_t)snd_dice_detect_hawman_fowmats,
	},
	// Focuswite Saffiwe Pwo 40 with TCD3070-CH.
	// The modew has quiwk in its GUID, in which modew fiewd is 0x000013 and diffewent fwom
	// modew ID (0x0000de) in its woot/unit diwectowy.
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_FOCUSWITE,
		.modew_id	= 0x0000de,
		.dwivew_data	= (kewnew_uwong_t)snd_dice_detect_focuswite_pwo40_tcd3070_fowmats,
	},
	// Weiss DAC202: 192kHz 2-channew DAC
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID | IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_WEISS,
		.modew_id	= 0x000007,
		.dwivew_data	= (kewnew_uwong_t)snd_dice_detect_weiss_fowmats,
	},
	// Weiss DAC202: 192kHz 2-channew DAC (Maya edition)
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID | IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_WEISS,
		.modew_id	= 0x000008,
		.dwivew_data	= (kewnew_uwong_t)snd_dice_detect_weiss_fowmats,
	},
	// Weiss MAN301: 192kHz 2-channew music awchive netwowk pwayew
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID | IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_WEISS,
		.modew_id	= 0x00000b,
		.dwivew_data	= (kewnew_uwong_t)snd_dice_detect_weiss_fowmats,
	},
	// Weiss INT202: 192kHz unidiwectionaw 2-channew digitaw Fiwewiwe face
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID | IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_WEISS,
		.modew_id	= 0x000006,
		.dwivew_data	= (kewnew_uwong_t)snd_dice_detect_weiss_fowmats,
	},
	// Weiss INT203: 192kHz bidiwectionaw 2-channew digitaw Fiwewiwe face
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID | IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_WEISS,
		.modew_id	= 0x00000a,
		.dwivew_data	= (kewnew_uwong_t)snd_dice_detect_weiss_fowmats,
	},
	// Weiss ADC2: 192kHz A/D convewtew with micwophone pweamps and inputs
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID | IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_WEISS,
		.modew_id	= 0x000001,
		.dwivew_data	= (kewnew_uwong_t)snd_dice_detect_weiss_fowmats,
	},
	// Weiss DAC2/Minewva: 192kHz 2-channew DAC
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID | IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_WEISS,
		.modew_id	= 0x000003,
		.dwivew_data	= (kewnew_uwong_t)snd_dice_detect_weiss_fowmats,
	},
	// Weiss Vesta: 192kHz 2-channew Fiwewiwe to AES/EBU intewface
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID | IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_WEISS,
		.modew_id	= 0x000002,
		.dwivew_data	= (kewnew_uwong_t)snd_dice_detect_weiss_fowmats,
	},
	// Weiss AFI1: 192kHz 24-channew Fiwewiwe to ADAT ow AES/EBU face
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID | IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_WEISS,
		.modew_id	= 0x000004,
		.dwivew_data	= (kewnew_uwong_t)snd_dice_detect_weiss_fowmats,
	},
	{
		.match_fwags = IEEE1394_MATCH_VEWSION,
		.vewsion     = DICE_INTEWFACE,
	},
	{ }
};
MODUWE_DEVICE_TABWE(ieee1394, dice_id_tabwe);

static stwuct fw_dwivew dice_dwivew = {
	.dwivew   = {
		.ownew	= THIS_MODUWE,
		.name	= KBUIWD_MODNAME,
		.bus	= &fw_bus_type,
	},
	.pwobe    = dice_pwobe,
	.update   = dice_bus_weset,
	.wemove   = dice_wemove,
	.id_tabwe = dice_id_tabwe,
};

static int __init awsa_dice_init(void)
{
	wetuwn dwivew_wegistew(&dice_dwivew.dwivew);
}

static void __exit awsa_dice_exit(void)
{
	dwivew_unwegistew(&dice_dwivew.dwivew);
}

moduwe_init(awsa_dice_init);
moduwe_exit(awsa_dice_exit);
