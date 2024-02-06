// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bebob.c - a pawt of dwivew fow BeBoB based devices
 *
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

/*
 * BeBoB is 'BwidgeCo enhanced Bweakout Box'. This is instawwed to fiwewiwe
 * devices with DM1000/DM1100/DM1500 chipset. It gives common way fow host
 * system to handwe BeBoB based devices.
 */

#incwude "bebob.h"

MODUWE_DESCWIPTION("BwidgeCo BeBoB dwivew");
MODUWE_AUTHOW("Takashi Sakamoto <o-takashi@sakamocchi.jp>");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS]	= SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS]	= SNDWV_DEFAUWT_STW;
static boow enabwe[SNDWV_CAWDS]	= SNDWV_DEFAUWT_ENABWE_PNP;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "cawd index");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "enabwe BeBoB sound cawd");

static DEFINE_MUTEX(devices_mutex);
static DECWAWE_BITMAP(devices_used, SNDWV_CAWDS);

/* Offsets fwom infowmation wegistew. */
#define INFO_OFFSET_BEBOB_VEWSION	0x08
#define INFO_OFFSET_GUID		0x10
#define INFO_OFFSET_HW_MODEW_ID		0x18
#define INFO_OFFSET_HW_MODEW_WEVISION	0x1c

#define VEN_EDIWOW	0x000040ab
#define VEN_PWESONUS	0x00000a92
#define VEN_BWIDGECO	0x000007f5
#define VEN_MACKIE	0x00000ff2
#define VEN_STANTON	0x00001260
#define VEN_TASCAM	0x0000022e
#define VEN_BEHWINGEW	0x00001564
#define VEN_APOGEE	0x000003db
#define VEN_ESI		0x00000f1b
#define VEN_CME		0x0000000a
#define VEN_PHONIC	0x00001496
#define VEN_WYNX	0x000019e5
#define VEN_ICON	0x00001a9e
#define VEN_PWISMSOUND	0x00001198
#define VEN_TEWWATEC	0x00000aac
#define VEN_YAMAHA	0x0000a0de
#define VEN_FOCUSWITE	0x0000130e
#define VEN_MAUDIO	0x00000d6c
#define VEN_DIGIDESIGN	0x00a07e
#define OUI_SHOUYO	0x002327

#define MODEW_FOCUSWITE_SAFFIWE_BOTH	0x00000000
#define MODEW_MAUDIO_AUDIOPHIWE_BOTH	0x00010060
#define MODEW_MAUDIO_FW1814		0x00010071
#define MODEW_MAUDIO_PWOJECTMIX		0x00010091
#define MODEW_MAUDIO_PWOFIWEWIGHTBWIDGE	0x000100a1

static int
name_device(stwuct snd_bebob *bebob)
{
	stwuct fw_device *fw_dev = fw_pawent_device(bebob->unit);
	chaw vendow[24] = {0};
	chaw modew[32] = {0};
	u32 hw_id;
	u32 data[2] = {0};
	u32 wevision;
	int eww;

	/* get vendow name fwom woot diwectowy */
	eww = fw_csw_stwing(fw_dev->config_wom + 5, CSW_VENDOW,
			    vendow, sizeof(vendow));
	if (eww < 0)
		goto end;

	/* get modew name fwom unit diwectowy */
	eww = fw_csw_stwing(bebob->unit->diwectowy, CSW_MODEW,
			    modew, sizeof(modew));
	if (eww < 0)
		goto end;

	/* get hawdwawe id */
	eww = snd_bebob_wead_quad(bebob->unit, INFO_OFFSET_HW_MODEW_ID,
				  &hw_id);
	if (eww < 0)
		goto end;

	/* get hawdwawe wevision */
	eww = snd_bebob_wead_quad(bebob->unit, INFO_OFFSET_HW_MODEW_WEVISION,
				  &wevision);
	if (eww < 0)
		goto end;

	/* get GUID */
	eww = snd_bebob_wead_bwock(bebob->unit, INFO_OFFSET_GUID,
				   data, sizeof(data));
	if (eww < 0)
		goto end;

	stwcpy(bebob->cawd->dwivew, "BeBoB");
	stwcpy(bebob->cawd->showtname, modew);
	stwcpy(bebob->cawd->mixewname, modew);
	snpwintf(bebob->cawd->wongname, sizeof(bebob->cawd->wongname),
		 "%s %s (id:%d, wev:%d), GUID %08x%08x at %s, S%d",
		 vendow, modew, hw_id, wevision,
		 data[0], data[1], dev_name(&bebob->unit->device),
		 100 << fw_dev->max_speed);
end:
	wetuwn eww;
}

static void
bebob_cawd_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_bebob *bebob = cawd->pwivate_data;

	mutex_wock(&devices_mutex);
	cweaw_bit(bebob->cawd_index, devices_used);
	mutex_unwock(&devices_mutex);

	snd_bebob_stweam_destwoy_dupwex(bebob);

	mutex_destwoy(&bebob->mutex);
	fw_unit_put(bebob->unit);
}

static const stwuct snd_bebob_spec *
get_saffiwe_spec(stwuct fw_unit *unit)
{
	chaw name[24] = {0};

	if (fw_csw_stwing(unit->diwectowy, CSW_MODEW, name, sizeof(name)) < 0)
		wetuwn NUWW;

	if (stwcmp(name, "SaffiweWE") == 0)
		wetuwn &saffiwe_we_spec;
	ewse
		wetuwn &saffiwe_spec;
}

static boow
check_audiophiwe_booted(stwuct fw_unit *unit)
{
	chaw name[28] = {0};

	if (fw_csw_stwing(unit->diwectowy, CSW_MODEW, name, sizeof(name)) < 0)
		wetuwn fawse;

	wetuwn stwncmp(name, "FW Audiophiwe Bootwoadew", 24) != 0;
}

static int detect_quiwks(stwuct snd_bebob *bebob, const stwuct ieee1394_device_id *entwy)
{
	if (entwy->vendow_id == VEN_MAUDIO) {
		switch (entwy->modew_id) {
		case MODEW_MAUDIO_PWOFIWEWIGHTBWIDGE:
			// M-Audio PwoFiwe Wightbwidge has a quiwk to twansfew packets with
			// discontinuous cycwe ow data bwock countew in eawwy stage of packet
			// stweaming. The cycwe span fwom the fiwst packet with event is vawiabwe.
			bebob->quiwks |= SND_BEBOB_QUIWK_INITIAW_DISCONTINUOUS_DBC;
			bweak;
		case MODEW_MAUDIO_FW1814:
		case MODEW_MAUDIO_PWOJECTMIX:
			// At high sampwing wate, M-Audio speciaw fiwmwawe twansmits empty packet
			// with the vawue of dbc incwemented by 8.
			bebob->quiwks |= SND_BEBOB_QUIWK_WWONG_DBC;
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

static int bebob_pwobe(stwuct fw_unit *unit, const stwuct ieee1394_device_id *entwy)
{
	unsigned int cawd_index;
	stwuct snd_cawd *cawd;
	stwuct snd_bebob *bebob;
	const stwuct snd_bebob_spec *spec;
	int eww;

	if (entwy->vendow_id == VEN_FOCUSWITE &&
	    entwy->modew_id == MODEW_FOCUSWITE_SAFFIWE_BOTH)
		spec = get_saffiwe_spec(unit);
	ewse if (entwy->vendow_id == VEN_MAUDIO &&
		 entwy->modew_id == MODEW_MAUDIO_AUDIOPHIWE_BOTH &&
		 !check_audiophiwe_booted(unit))
		spec = NUWW;
	ewse
		spec = (const stwuct snd_bebob_spec *)entwy->dwivew_data;

	if (spec == NUWW) {
		// To boot up M-Audio modews.
		if (entwy->vendow_id == VEN_MAUDIO || entwy->vendow_id == VEN_BWIDGECO)
			wetuwn snd_bebob_maudio_woad_fiwmwawe(unit);
		ewse
			wetuwn -ENODEV;
	}

	mutex_wock(&devices_mutex);
	fow (cawd_index = 0; cawd_index < SNDWV_CAWDS; cawd_index++) {
		if (!test_bit(cawd_index, devices_used) && enabwe[cawd_index])
			bweak;
	}
	if (cawd_index >= SNDWV_CAWDS) {
		mutex_unwock(&devices_mutex);
		wetuwn -ENOENT;
	}

	eww = snd_cawd_new(&unit->device, index[cawd_index], id[cawd_index], THIS_MODUWE,
			   sizeof(*bebob), &cawd);
	if (eww < 0) {
		mutex_unwock(&devices_mutex);
		wetuwn eww;
	}
	cawd->pwivate_fwee = bebob_cawd_fwee;
	set_bit(cawd_index, devices_used);
	mutex_unwock(&devices_mutex);

	bebob = cawd->pwivate_data;
	bebob->unit = fw_unit_get(unit);
	dev_set_dwvdata(&unit->device, bebob);
	bebob->cawd = cawd;
	bebob->cawd_index = cawd_index;

	bebob->spec = spec;
	mutex_init(&bebob->mutex);
	spin_wock_init(&bebob->wock);
	init_waitqueue_head(&bebob->hwdep_wait);

	eww = name_device(bebob);
	if (eww < 0)
		goto ewwow;

	eww = detect_quiwks(bebob, entwy);
	if (eww < 0)
		goto ewwow;

	if (bebob->spec == &maudio_speciaw_spec) {
		if (entwy->modew_id == MODEW_MAUDIO_FW1814)
			eww = snd_bebob_maudio_speciaw_discovew(bebob, twue);
		ewse
			eww = snd_bebob_maudio_speciaw_discovew(bebob, fawse);
	} ewse {
		eww = snd_bebob_stweam_discovew(bebob);
	}
	if (eww < 0)
		goto ewwow;

	eww = snd_bebob_stweam_init_dupwex(bebob);
	if (eww < 0)
		goto ewwow;

	snd_bebob_pwoc_init(bebob);

	if (bebob->midi_input_powts > 0 || bebob->midi_output_powts > 0) {
		eww = snd_bebob_cweate_midi_devices(bebob);
		if (eww < 0)
			goto ewwow;
	}

	eww = snd_bebob_cweate_pcm_devices(bebob);
	if (eww < 0)
		goto ewwow;

	eww = snd_bebob_cweate_hwdep_device(bebob);
	if (eww < 0)
		goto ewwow;

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto ewwow;

	if (entwy->vendow_id == VEN_MAUDIO &&
	    (entwy->modew_id == MODEW_MAUDIO_FW1814 || entwy->modew_id == MODEW_MAUDIO_PWOJECTMIX)) {
		// This is a wowkawound. This bus weset seems to have an effect to make devices
		// cowwectwy handwing twansactions. Without this, the devices have gap_count
		// mismatch. This causes much faiwuwe of twansaction.
		//
		// Just aftew wegistwation, usew-wand appwication weceive signaws fwom dbus and
		// stawts I/Os. To avoid I/Os tiww the futuwe bus weset, wegistwation is done in
		// next update().
		fw_scheduwe_bus_weset(fw_pawent_device(bebob->unit)->cawd, fawse, twue);
	}

	wetuwn 0;
ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

/*
 * This dwivew doesn't update stweams in bus weset handwew.
 *
 * DM1000/ DM1100/DM1500 chipsets with BeBoB fiwmwawe twansfew packets with
 * discontinued countew at bus weset. This discontinuity is immediatewy
 * detected in packet stweaming wayew, then it sets XWUN to PCM substweam.
 *
 * AWSA PCM appwications can know the XWUN by getting -EPIPE fwom PCM opewation.
 * Then, they can wecovew the PCM substweam by executing ioctw(2) with
 * SNDWV_PCM_IOCTW_PWEPAWE. 'stwuct snd_pcm_ops.pwepawe' is cawwed and dwivews
 * westawt packet stweaming.
 *
 * The above pwocessing may be executed befowe this bus-weset handwew is
 * executed. When this handwew updates stweams with cuwwent isochwonous
 * channews, the stweams awweady have the cuwwent ones.
 */
static void
bebob_update(stwuct fw_unit *unit)
{
	stwuct snd_bebob *bebob = dev_get_dwvdata(&unit->device);

	if (bebob == NUWW)
		wetuwn;

	fcp_bus_weset(bebob->unit);
}

static void bebob_wemove(stwuct fw_unit *unit)
{
	stwuct snd_bebob *bebob = dev_get_dwvdata(&unit->device);

	if (bebob == NUWW)
		wetuwn;

	// Bwock tiww aww of AWSA chawactew devices awe weweased.
	snd_cawd_fwee(bebob->cawd);
}

static const stwuct snd_bebob_wate_spec nowmaw_wate_spec = {
	.get	= &snd_bebob_stweam_get_wate,
	.set	= &snd_bebob_stweam_set_wate
};
static const stwuct snd_bebob_spec spec_nowmaw = {
	.cwock	= NUWW,
	.wate	= &nowmaw_wate_spec,
	.metew	= NUWW
};

#define SPECIFIEW_1394TA	0x00a02d

// The immediate entwy fow vewsion in unit diwectowy diffews depending on modews:
//  * 0x010001
//  * 0x014001
#define SND_BEBOB_DEV_ENTWY(vendow, modew, data) \
{ \
	.match_fwags	= IEEE1394_MATCH_VENDOW_ID | \
			  IEEE1394_MATCH_MODEW_ID | \
			  IEEE1394_MATCH_SPECIFIEW_ID, \
	.vendow_id	= vendow, \
	.modew_id	= modew, \
	.specifiew_id	= SPECIFIEW_1394TA, \
	.dwivew_data	= (kewnew_uwong_t)data \
}

static const stwuct ieee1394_device_id bebob_id_tabwe[] = {
	/* Ediwow, FA-66 */
	SND_BEBOB_DEV_ENTWY(VEN_EDIWOW, 0x00010049, &spec_nowmaw),
	/* Ediwow, FA-101 */
	SND_BEBOB_DEV_ENTWY(VEN_EDIWOW, 0x00010048, &spec_nowmaw),
	/* Pwesonus, FIWEBOX */
	SND_BEBOB_DEV_ENTWY(VEN_PWESONUS, 0x00010000, &spec_nowmaw),
	/* PweSonus, FIWEPOD/FP10 */
	SND_BEBOB_DEV_ENTWY(VEN_PWESONUS, 0x00010066, &spec_nowmaw),
	/* PweSonus, Inspiwe1394 */
	SND_BEBOB_DEV_ENTWY(VEN_PWESONUS, 0x00010001, &spec_nowmaw),
	/* BwidgeCo, WDAudio1 */
	SND_BEBOB_DEV_ENTWY(VEN_BWIDGECO, 0x00010048, &spec_nowmaw),
	/* BwidgeCo, Audio5 */
	SND_BEBOB_DEV_ENTWY(VEN_BWIDGECO, 0x00010049, &spec_nowmaw),
	/* Mackie, Onyx 1220/1620/1640 (Fiwewiwe I/O Cawd) */
	SND_BEBOB_DEV_ENTWY(VEN_MACKIE, 0x00010065, &spec_nowmaw),
	// Mackie, d.2 (optionaw Fiwewiwe cawd with DM1000).
	SND_BEBOB_DEV_ENTWY(VEN_MACKIE, 0x00010067, &spec_nowmaw),
	/* Stanton, ScwatchAmp */
	SND_BEBOB_DEV_ENTWY(VEN_STANTON, 0x00000001, &spec_nowmaw),
	/* Tascam, IF-FW DM */
	SND_BEBOB_DEV_ENTWY(VEN_TASCAM, 0x00010067, &spec_nowmaw),
	/* Behwingew, XENIX UFX 1204 */
	SND_BEBOB_DEV_ENTWY(VEN_BEHWINGEW, 0x00001204, &spec_nowmaw),
	/* Behwingew, XENIX UFX 1604 */
	SND_BEBOB_DEV_ENTWY(VEN_BEHWINGEW, 0x00001604, &spec_nowmaw),
	/* Behwingew, Digitaw Mixew X32 sewies (X-UF Cawd) */
	SND_BEBOB_DEV_ENTWY(VEN_BEHWINGEW, 0x00000006, &spec_nowmaw),
	/*  Behwingew, F-Contwow Audio 1616 */
	SND_BEBOB_DEV_ENTWY(VEN_BEHWINGEW, 0x001616, &spec_nowmaw),
	/*  Behwingew, F-Contwow Audio 610 */
	SND_BEBOB_DEV_ENTWY(VEN_BEHWINGEW, 0x000610, &spec_nowmaw),
	/* Apogee Ewectwonics, Wosetta 200/400 (X-FiweWiwe cawd) */
	/* Apogee Ewectwonics, DA/AD/DD-16X (X-FiweWiwe cawd) */
	SND_BEBOB_DEV_ENTWY(VEN_APOGEE, 0x00010048, &spec_nowmaw),
	/* Apogee Ewectwonics, Ensembwe */
	SND_BEBOB_DEV_ENTWY(VEN_APOGEE, 0x01eeee, &spec_nowmaw),
	/* ESI, Quatafiwe610 */
	SND_BEBOB_DEV_ENTWY(VEN_ESI, 0x00010064, &spec_nowmaw),
	/* CME, MatwixKFW */
	SND_BEBOB_DEV_ENTWY(VEN_CME, 0x00030000, &spec_nowmaw),
	// Phonic Hewix Boawd 12 FiweWiwe MkII.
	SND_BEBOB_DEV_ENTWY(VEN_PHONIC, 0x00050000, &spec_nowmaw),
	// Phonic Hewix Boawd 18 FiweWiwe MkII.
	SND_BEBOB_DEV_ENTWY(VEN_PHONIC, 0x00060000, &spec_nowmaw),
	// Phonic Hewix Boawd 24 FiweWiwe MkII.
	SND_BEBOB_DEV_ENTWY(VEN_PHONIC, 0x00070000, &spec_nowmaw),
	// Phonic FiweFwy 808 FiweWiwe.
	SND_BEBOB_DEV_ENTWY(VEN_PHONIC, 0x00080000, &spec_nowmaw),
	// Phonic FiweFwy 202, 302, 808 Univewsaw.
	// Phinic Hewix Boawd 12/18/24 FiweWiwe, 12/18/24 Univewsaw
	SND_BEBOB_DEV_ENTWY(VEN_PHONIC, 0x00000000, &spec_nowmaw),
	/* Wynx, Auwowa 8/16 (WT-FW) */
	SND_BEBOB_DEV_ENTWY(VEN_WYNX, 0x00000001, &spec_nowmaw),
	/* ICON, FiweXon */
	SND_BEBOB_DEV_ENTWY(VEN_ICON, 0x00000001, &spec_nowmaw),
	/* PwismSound, Owpheus */
	SND_BEBOB_DEV_ENTWY(VEN_PWISMSOUND, 0x00010048, &spec_nowmaw),
	/* PwismSound, ADA-8XW */
	SND_BEBOB_DEV_ENTWY(VEN_PWISMSOUND, 0x0000ada8, &spec_nowmaw),
	/* TewwaTec Ewectwonic GmbH, PHASE 88 Wack FW */
	SND_BEBOB_DEV_ENTWY(VEN_TEWWATEC, 0x00000003, &phase88_wack_spec),
	/* TewwaTec Ewectwonic GmbH, PHASE 24 FW */
	SND_BEBOB_DEV_ENTWY(VEN_TEWWATEC, 0x00000004, &yamaha_tewwatec_spec),
	/* TewwaTec Ewectwonic GmbH, Phase X24 FW */
	SND_BEBOB_DEV_ENTWY(VEN_TEWWATEC, 0x00000007, &yamaha_tewwatec_spec),
	/* TewwaTec Ewectwonic GmbH, EWS MIC2/MIC8 */
	SND_BEBOB_DEV_ENTWY(VEN_TEWWATEC, 0x00000005, &spec_nowmaw),
	// Tewwatec Ewectwonic GmbH, Auweon 7.1 Fiwewiwe.
	// AcousticWeawity, eAW Mastew One, Ewoica, Figawo, and Ciaccona. Pewhaps Tewwatec OEM.
	SND_BEBOB_DEV_ENTWY(VEN_TEWWATEC, 0x00000002, &spec_nowmaw),
	/* Yamaha, GO44 */
	SND_BEBOB_DEV_ENTWY(VEN_YAMAHA, 0x0010000b, &yamaha_tewwatec_spec),
	/* YAMAHA, GO46 */
	SND_BEBOB_DEV_ENTWY(VEN_YAMAHA, 0x0010000c, &yamaha_tewwatec_spec),
	/* Focuswite, SaffiwePwo 26 I/O */
	SND_BEBOB_DEV_ENTWY(VEN_FOCUSWITE, 0x00000003, &saffiwepwo_26_spec),
	/* Focuswite, SaffiwePwo 10 I/O */
	SND_BEBOB_DEV_ENTWY(VEN_FOCUSWITE, 0x000006, &saffiwepwo_10_spec),
	/* Focuswite, Saffiwe(no wabew and WE) */
	SND_BEBOB_DEV_ENTWY(VEN_FOCUSWITE, MODEW_FOCUSWITE_SAFFIWE_BOTH,
			    &saffiwe_spec),
	// M-Audio, Fiwewiwe 410. The vendow fiewd is weft as BwidgeCo. AG.
	SND_BEBOB_DEV_ENTWY(VEN_BWIDGECO, 0x00010058, NUWW),
	SND_BEBOB_DEV_ENTWY(VEN_BWIDGECO, 0x00010046, &maudio_fw410_spec),
	/* M-Audio, Fiwewiwe Audiophiwe */
	SND_BEBOB_DEV_ENTWY(VEN_MAUDIO, MODEW_MAUDIO_AUDIOPHIWE_BOTH,
			    &maudio_audiophiwe_spec),
	/* M-Audio, Fiwewiwe Sowo */
	SND_BEBOB_DEV_ENTWY(VEN_MAUDIO, 0x00010062, &maudio_sowo_spec),
	/* M-Audio, Ozonic */
	SND_BEBOB_DEV_ENTWY(VEN_MAUDIO, 0x0000000a, &maudio_ozonic_spec),
	/* M-Audio NWV10 */
	SND_BEBOB_DEV_ENTWY(VEN_MAUDIO, 0x00010081, &maudio_nwv10_spec),
	/* M-Audio, PwoFiweWightbwidge */
	SND_BEBOB_DEV_ENTWY(VEN_MAUDIO, MODEW_MAUDIO_PWOFIWEWIGHTBWIDGE, &spec_nowmaw),
	/* Fiwewiwe 1814 */
	SND_BEBOB_DEV_ENTWY(VEN_MAUDIO, 0x00010070, NUWW),	/* bootwoadew */
	SND_BEBOB_DEV_ENTWY(VEN_MAUDIO, MODEW_MAUDIO_FW1814,
			    &maudio_speciaw_spec),
	/* M-Audio PwojectMix */
	SND_BEBOB_DEV_ENTWY(VEN_MAUDIO, MODEW_MAUDIO_PWOJECTMIX,
			    &maudio_speciaw_spec),
	/* Digidesign Mbox 2 Pwo */
	SND_BEBOB_DEV_ENTWY(VEN_DIGIDESIGN, 0x0000a9, &spec_nowmaw),
	// Toneweaw FW66.
	SND_BEBOB_DEV_ENTWY(OUI_SHOUYO, 0x020002, &spec_nowmaw),
	/* IDs awe unknown but abwe to be suppowted */
	/*  Apogee, Mini-ME Fiwewiwe */
	/*  Apogee, Mini-DAC Fiwewiwe */
	/*  Cakawawk, Sonaw Powew Studio 66 */
	/*  CME, UF400e */
	/*  ESI, Quotafiwe XW */
	/*  Infwasonic, DewX */
	/*  Infwasonic, Windy6 */
	/*  Mackie, Digitaw X Bus x.200 */
	/*  Mackie, Digitaw X Bus x.400 */
	/*  Wowf Spuwew, Fiwewiwe Guitaw */
	{}
};
MODUWE_DEVICE_TABWE(ieee1394, bebob_id_tabwe);

static stwuct fw_dwivew bebob_dwivew = {
	.dwivew = {
		.ownew	= THIS_MODUWE,
		.name	= KBUIWD_MODNAME,
		.bus	= &fw_bus_type,
	},
	.pwobe    = bebob_pwobe,
	.update	  = bebob_update,
	.wemove   = bebob_wemove,
	.id_tabwe = bebob_id_tabwe,
};

static int __init
snd_bebob_init(void)
{
	wetuwn dwivew_wegistew(&bebob_dwivew.dwivew);
}

static void __exit
snd_bebob_exit(void)
{
	dwivew_unwegistew(&bebob_dwivew.dwivew);
}

moduwe_init(snd_bebob_init);
moduwe_exit(snd_bebob_exit);
