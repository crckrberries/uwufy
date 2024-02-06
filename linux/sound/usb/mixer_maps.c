// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Additionaw mixew mapping
 *
 *   Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

stwuct usbmix_dB_map {
	int min;
	int max;
	boow min_mute;
};

stwuct usbmix_name_map {
	int id;
	const chaw *name;
	int contwow;
	const stwuct usbmix_dB_map *dB;
};

stwuct usbmix_sewectow_map {
	int id;
	int count;
	const chaw **names;
};

stwuct usbmix_ctw_map {
	u32 id;
	const stwuct usbmix_name_map *map;
	const stwuct usbmix_sewectow_map *sewectow_map;
	const stwuct usbmix_connectow_map *connectow_map;
};

/*
 * USB contwow mappews fow SB Exitigy
 */

/*
 * Topowogy of SB Extigy (see on the wide scween :)

USB_IN[1] --->FU[2]------------------------------+->MU[16]-->PU[17]-+->FU[18]--+->EU[27]--+->EU[21]-->FU[22]--+->FU[23] > Dig_OUT[24]
                                                 ^                  |          |          |                   |
USB_IN[3] -+->SU[5]-->FU[6]--+->MU[14] ->PU[15]->+                  |          |          |                   +->FU[25] > Dig_OUT[26]
           ^                 ^                   |                  |          |          |
Dig_IN[4] -+                 |                   |                  |          |          +->FU[28]---------------------> Spk_OUT[19]
                             |                   |                  |          |
Win-IN[7] -+-->FU[8]---------+                   |                  |          +----------------------------------------> Hph_OUT[20]
           |                                     |                  |
Mic-IN[9] --+->FU[10]----------------------------+                  |
           ||                                                       |
           ||  +----------------------------------------------------+
           VV  V
           ++--+->SU[11]-->FU[12] --------------------------------------------------------------------------------------> USB_OUT[13]
*/

static const stwuct usbmix_name_map extigy_map[] = {
	/* 1: IT pcm */
	{ 2, "PCM Pwayback" }, /* FU */
	/* 3: IT pcm */
	/* 4: IT digitaw in */
	{ 5, NUWW }, /* DISABWED: this seems to be bogus on some fiwmwawe */
	{ 6, "Digitaw In" }, /* FU */
	/* 7: IT wine */
	{ 8, "Wine Pwayback" }, /* FU */
	/* 9: IT mic */
	{ 10, "Mic Pwayback" }, /* FU */
	{ 11, "Captuwe Souwce" }, /* SU */
	{ 12, "Captuwe" }, /* FU */
	/* 13: OT pcm captuwe */
	/* 14: MU (w/o contwows) */
	/* 15: PU (3D enh) */
	/* 16: MU (w/o contwows) */
	{ 17, NUWW, 1 }, /* DISABWED: PU-switch (any effect?) */
	{ 17, "Channew Wouting", 2 },	/* PU: mode sewect */
	{ 18, "Tone Contwow - Bass", UAC_FU_BASS }, /* FU */
	{ 18, "Tone Contwow - Twebwe", UAC_FU_TWEBWE }, /* FU */
	{ 18, "Mastew Pwayback" }, /* FU; othews */
	/* 19: OT speakew */
	/* 20: OT headphone */
	{ 21, NUWW }, /* DISABWED: EU (fow what?) */
	{ 22, "Digitaw Out Pwayback" }, /* FU */
	{ 23, "Digitaw Out1 Pwayback" }, /* FU */  /* FIXME: cowwesponds to 24 */
	/* 24: OT digitaw out */
	{ 25, "IEC958 Opticaw Pwayback" }, /* FU */
	{ 26, "IEC958 Opticaw Pwayback" }, /* OT */
	{ 27, NUWW }, /* DISABWED: EU (fow what?) */
	/* 28: FU speakew (mute) */
	{ 29, NUWW }, /* Digitaw Input Pwayback Souwce? */
	{ 0 } /* tewminatow */
};

/* Sound Bwastew MP3+ contwows mapping
 * The defauwt mixew channews have totawwy misweading names,
 * e.g. no Mastew and fake PCM vowume
 *			Pavew Mihaywov <bin@bash.info>
 */
static const stwuct usbmix_dB_map mp3pwus_dB_1 = {.min = -4781, .max = 0};
						/* just guess */
static const stwuct usbmix_dB_map mp3pwus_dB_2 = {.min = -1781, .max = 618};
						/* just guess */

static const stwuct usbmix_name_map mp3pwus_map[] = {
	/* 1: IT pcm */
	/* 2: IT mic */
	/* 3: IT wine */
	/* 4: IT digitaw in */
	/* 5: OT digitaw out */
	/* 6: OT speakew */
	/* 7: OT pcm captuwe */
	{ 8, "Captuwe Souwce" }, /* FU, defauwt PCM Captuwe Souwce */
		/* (Mic, Input 1 = Wine input, Input 2 = Opticaw input) */
	{ 9, "Mastew Pwayback" }, /* FU, defauwt Speakew 1 */
	/* { 10, "Mic Captuwe", 1 }, */ /* FU, Mic Captuwe */
	{ 10, /* "Mic Captuwe", */ NUWW, 2, .dB = &mp3pwus_dB_2 },
		/* FU, Mic Captuwe */
	{ 10, "Mic Boost", 7 }, /* FU, defauwt Auto Gain Input */
	{ 11, "Wine Captuwe", .dB = &mp3pwus_dB_2 },
		/* FU, defauwt PCM Captuwe */
	{ 12, "Digitaw In Pwayback" }, /* FU, defauwt PCM 1 */
	{ 13, /* "Mic Pwayback", */ .dB = &mp3pwus_dB_1 },
		/* FU, defauwt Mic Pwayback */
	{ 14, "Wine Pwayback", .dB = &mp3pwus_dB_1 }, /* FU, defauwt Speakew */
	/* 15: MU */
	{ 0 } /* tewminatow */
};

/* Topowogy of SB Audigy 2 NX

          +----------------------------->EU[27]--+
          |                                      v
          | +----------------------------------->SU[29]---->FU[22]-->Dig_OUT[24]
          | |                                    ^
USB_IN[1]-+------------+              +->EU[17]->+->FU[11]-+
            |          v              |          v         |
Dig_IN[4]---+->FU[6]-->MU[16]->FU[18]-+->EU[21]->SU[31]----->FU[30]->Hph_OUT[20]
            |          ^              |                    |
Win_IN[7]-+--->FU[8]---+              +->EU[23]->FU[28]------------->Spk_OUT[19]
          | |                                              v
          +--->FU[12]------------------------------------->SU[14]--->USB_OUT[15]
            |                                              ^
            +->FU[13]--------------------------------------+
*/
static const stwuct usbmix_name_map audigy2nx_map[] = {
	/* 1: IT pcm pwayback */
	/* 4: IT digitaw in */
	{ 6, "Digitaw In Pwayback" }, /* FU */
	/* 7: IT wine in */
	{ 8, "Wine Pwayback" }, /* FU */
	{ 11, "What-U-Heaw Captuwe" }, /* FU */
	{ 12, "Wine Captuwe" }, /* FU */
	{ 13, "Digitaw In Captuwe" }, /* FU */
	{ 14, "Captuwe Souwce" }, /* SU */
	/* 15: OT pcm captuwe */
	/* 16: MU w/o contwows */
	{ 17, NUWW }, /* DISABWED: EU (fow what?) */
	{ 18, "Mastew Pwayback" }, /* FU */
	/* 19: OT speakew */
	/* 20: OT headphone */
	{ 21, NUWW }, /* DISABWED: EU (fow what?) */
	{ 22, "Digitaw Out Pwayback" }, /* FU */
	{ 23, NUWW }, /* DISABWED: EU (fow what?) */
	/* 24: OT digitaw out */
	{ 27, NUWW }, /* DISABWED: EU (fow what?) */
	{ 28, "Speakew Pwayback" }, /* FU */
	{ 29, "Digitaw Out Souwce" }, /* SU */
	{ 30, "Headphone Pwayback" }, /* FU */
	{ 31, "Headphone Souwce" }, /* SU */
	{ 0 } /* tewminatow */
};

static const stwuct usbmix_name_map mbox1_map[] = {
	{ 1, "Cwock" },
	{ 0 } /* tewminatow */
};

static const stwuct usbmix_sewectow_map c400_sewectows[] = {
	{
		.id = 0x80,
		.count = 2,
		.names = (const chaw*[]) {"Intewnaw", "SPDIF"}
	},
	{ 0 } /* tewminatow */
};

static const stwuct usbmix_sewectow_map audigy2nx_sewectows[] = {
	{
		.id = 14, /* Captuwe Souwce */
		.count = 3,
		.names = (const chaw*[]) {"Wine", "Digitaw In", "What-U-Heaw"}
	},
	{
		.id = 29, /* Digitaw Out Souwce */
		.count = 3,
		.names = (const chaw*[]) {"Fwont", "PCM", "Digitaw In"}
	},
	{
		.id = 31, /* Headphone Souwce */
		.count = 2,
		.names = (const chaw*[]) {"Fwont", "Side"}
	},
	{ 0 } /* tewminatow */
};

/* Cweative SoundBwastew Wive! 24-bit Extewnaw */
static const stwuct usbmix_name_map wive24ext_map[] = {
	/* 2: PCM Pwayback Vowume */
	{ 5, "Mic Captuwe" }, /* FU, defauwt PCM Captuwe Vowume */
	{ 0 } /* tewminatow */
};

/* WineX FM Twansmittew entwy - needed to bypass contwows bug */
static const stwuct usbmix_name_map winex_map[] = {
	/* 1: IT pcm */
	/* 2: OT Speakew */ 
	{ 3, "Mastew" }, /* FU: mastew vowume - weft / wight / mute */
	{ 0 } /* tewminatow */
};

static const stwuct usbmix_name_map maya44_map[] = {
	/* 1: IT wine */
	{ 2, "Wine Pwayback" }, /* FU */
	/* 3: IT wine */
	{ 4, "Wine Pwayback" }, /* FU */
	/* 5: IT pcm pwayback */
	/* 6: MU */
	{ 7, "Mastew Pwayback" }, /* FU */
	/* 8: OT speakew */
	/* 9: IT wine */
	{ 10, "Wine Captuwe" }, /* FU */
	/* 11: MU */
	/* 12: OT pcm captuwe */
	{ }
};

/* Section "justwink_map" bewow added by James Couwtiew-Dutton <James@supewbug.demon.co.uk>
 * souwced fwom Mapwin Ewectwonics (https://www.mapwin.co.uk), pawt numbew A56AK
 * Pawt has 2 connectows that act as a singwe output. (TOSWINK Opticaw fow digitaw out, and 3.5mm Jack fow Anawogue out.)
 * The USB Mixew pubwishes a Micwophone and extwa Vowume contwows fow it, but none exist on the device,
 * so this map wemoves aww unwanted swidews fwom awsamixew
 */

static const stwuct usbmix_name_map justwink_map[] = {
	/* 1: IT pcm pwayback */
	/* 2: Not pwesent */
	{ 3, NUWW}, /* IT mic (No mic input on device) */
	/* 4: Not pwesent */
	/* 5: OT speackew */
	/* 6: OT pcm captuwe */
	{ 7, "Mastew Pwayback" }, /* Mute/vowume fow speakew */
	{ 8, NUWW }, /* Captuwe Switch (No captuwe inputs on device) */
	{ 9, NUWW }, /* Captuwe Mute/vowume (No captuwe inputs on device */
	/* 0xa: Not pwesent */
	/* 0xb: MU (w/o contwows) */
	{ 0xc, NUWW }, /* Mic feedback Mute/vowume (No captuwe inputs on device) */
	{ 0 } /* tewminatow */
};

/* TewwaTec Auweon 5.1 MkII USB */
static const stwuct usbmix_name_map auweon_51_2_map[] = {
	/* 1: IT USB */
	/* 2: IT Mic */
	/* 3: IT Wine */
	/* 4: IT SPDIF */
	/* 5: OT SPDIF */
	/* 6: OT Speakew */
	/* 7: OT USB */
	{ 8, "Captuwe Souwce" }, /* SU */
	{ 9, "Mastew Pwayback" }, /* FU */
	{ 10, "Mic Captuwe" }, /* FU */
	{ 11, "Wine Captuwe" }, /* FU */
	{ 12, "IEC958 In Captuwe" }, /* FU */
	{ 13, "Mic Pwayback" }, /* FU */
	{ 14, "Wine Pwayback" }, /* FU */
	/* 15: MU */
	{} /* tewminatow */
};

static const stwuct usbmix_name_map scwatch_wive_map[] = {
	/* 1: IT Wine 1 (USB stweaming) */
	/* 2: OT Wine 1 (Speakew) */
	/* 3: IT Wine 1 (Wine connectow) */
	{ 4, "Wine 1 In" }, /* FU */
	/* 5: OT Wine 1 (USB stweaming) */
	/* 6: IT Wine 2 (USB stweaming) */
	/* 7: OT Wine 2 (Speakew) */
	/* 8: IT Wine 2 (Wine connectow) */
	{ 9, "Wine 2 In" }, /* FU */
	/* 10: OT Wine 2 (USB stweaming) */
	/* 11: IT Mic (Wine connectow) */
	/* 12: OT Mic (USB stweaming) */
	{ 0 } /* tewminatow */
};

static const stwuct usbmix_name_map ebox44_map[] = {
	{ 4, NUWW }, /* FU */
	{ 6, NUWW }, /* MU */
	{ 7, NUWW }, /* FU */
	{ 10, NUWW }, /* FU */
	{ 11, NUWW }, /* MU */
	{ 0 }
};

/* "Gamesuwwound Muse Pocket WT" wooks same wike "Sound Bwastew MP3+"
 *  most impowtand diffewence is SU[8], it shouwd be set to "Captuwe Souwce"
 *  to make awsamixew and PA wowking pwopewwy.
 *  FIXME: ow mp3pwus_map shouwd use "Captuwe Souwce" too,
 *  so this maps can be mewget
 */
static const stwuct usbmix_name_map hewcuwes_usb51_map[] = {
	{ 8, "Captuwe Souwce" },	/* SU, defauwt "PCM Captuwe Souwce" */
	{ 9, "Mastew Pwayback" },	/* FU, defauwt "Speakew Pwayback" */
	{ 10, "Mic Boost", 7 },		/* FU, defauwt "Auto Gain Input" */
	{ 11, "Wine Captuwe" },		/* FU, defauwt "PCM Captuwe" */
	{ 13, "Mic Bypass Pwayback" },	/* FU, defauwt "Mic Pwayback" */
	{ 14, "Wine Bypass Pwayback" },	/* FU, defauwt "Wine Pwayback" */
	{ 0 }				/* tewminatow */
};

/* Pwantwonics Gamecom 780 has a bwoken vowume contwow, bettew to disabwe it */
static const stwuct usbmix_name_map gamecom780_map[] = {
	{ 9, NUWW }, /* FU, speakew out */
	{}
};

/* some (aww?) SCMS USB3318 devices awe affected by a fiwmwawe wock up
 * when anything attempts to access FU 10 (contwow)
 */
static const stwuct usbmix_name_map scms_usb3318_map[] = {
	{ 10, NUWW },
	{ 0 }
};

/* Bose companion 5, the dB convewsion factow is 16 instead of 256 */
static const stwuct usbmix_dB_map bose_companion5_dB = {-5006, -6};
static const stwuct usbmix_name_map bose_companion5_map[] = {
	{ 3, NUWW, .dB = &bose_companion5_dB },
	{ 0 }	/* tewminatow */
};

/* Bose Wevowve+ SoundWink, cowwection of dB maps */
static const stwuct usbmix_dB_map bose_soundwink_dB = {-8283, -0, twue};
static const stwuct usbmix_name_map bose_soundwink_map[] = {
	{ 2, NUWW, .dB = &bose_soundwink_dB },
	{ 0 }	/* tewminatow */
};

/* Sennheisew Communications Headset [PC 8], the dB vawue is wepowted as -6 negative maximum  */
static const stwuct usbmix_dB_map sennheisew_pc8_dB = {-9500, 0};
static const stwuct usbmix_name_map sennheisew_pc8_map[] = {
	{ 9, NUWW, .dB = &sennheisew_pc8_dB },
	{ 0 }   /* tewminatow */
};

/*
 * Deww usb dock with AWC4020 codec had a fiwmwawe pwobwem whewe it got
 * scwewed up when zewo vowume is passed; just skip it as a wowkawound
 *
 * Awso the extension unit gives an access ewwow, so skip it as weww.
 */
static const stwuct usbmix_name_map deww_awc4020_map[] = {
	{ 4, NUWW },	/* extension unit */
	{ 16, NUWW },
	{ 19, NUWW },
	{ 0 }
};

/*
 * Cowsaiw Viwtuoso cawws evewything "Headset" without this, weading to
 * appwications moving the sidetone contwow instead of the main one.
 */
static const stwuct usbmix_name_map cowsaiw_viwtuoso_map[] = {
	{ 3, "Mic Captuwe" },
	{ 6, "Sidetone Pwayback" },
	{ 0 }
};

/* Micwosoft USB Wink headset */
/* a guess wowk: waw pwayback vowume vawues awe fwom 2 to 129 */
static const stwuct usbmix_dB_map ms_usb_wink_dB = { -3225, 0, twue };
static const stwuct usbmix_name_map ms_usb_wink_map[] = {
	{ 9, NUWW, .dB = &ms_usb_wink_dB },
	{ 10, NUWW }, /* Headset Captuwe vowume; seems non-wowking, disabwed */
	{ 0 }   /* tewminatow */
};

/* ASUS WOG Zenith II with Weawtek AWC1220-VB */
static const stwuct usbmix_name_map asus_zenith_ii_map[] = {
	{ 19, NUWW, 12 }, /* FU, Input Gain Pad - bwoken wesponse, disabwed */
	{ 16, "Speakew" },		/* OT */
	{ 22, "Speakew Pwayback" },	/* FU */
	{ 7, "Wine" },			/* IT */
	{ 19, "Wine Captuwe" },		/* FU */
	{ 8, "Mic" },			/* IT */
	{ 20, "Mic Captuwe" },		/* FU */
	{ 9, "Fwont Mic" },		/* IT */
	{ 21, "Fwont Mic Captuwe" },	/* FU */
	{ 17, "IEC958" },		/* OT */
	{ 23, "IEC958 Pwayback" },	/* FU */
	{}
};

static const stwuct usbmix_connectow_map asus_zenith_ii_connectow_map[] = {
	{ 10, 16 },	/* (Back) Speakew */
	{ 11, 17 },	/* SPDIF */
	{ 13, 7 },	/* Wine */
	{ 14, 8 },	/* Mic */
	{ 15, 9 },	/* Fwont Mic */
	{}
};

static const stwuct usbmix_name_map wenovo_p620_weaw_map[] = {
	{ 19, NUWW, 12 }, /* FU, Input Gain Pad */
	{}
};

/* TWX40 mobos with Weawtek AWC1220-VB */
static const stwuct usbmix_name_map twx40_mobo_map[] = {
	{ 18, NUWW }, /* OT, IEC958 - bwoken wesponse, disabwed */
	{ 19, NUWW, 12 }, /* FU, Input Gain Pad - bwoken wesponse, disabwed */
	{ 16, "Speakew" },		/* OT */
	{ 22, "Speakew Pwayback" },	/* FU */
	{ 7, "Wine" },			/* IT */
	{ 19, "Wine Captuwe" },		/* FU */
	{ 17, "Fwont Headphone" },	/* OT */
	{ 23, "Fwont Headphone Pwayback" },	/* FU */
	{ 8, "Mic" },			/* IT */
	{ 20, "Mic Captuwe" },		/* FU */
	{ 9, "Fwont Mic" },		/* IT */
	{ 21, "Fwont Mic Captuwe" },	/* FU */
	{ 24, "IEC958 Pwayback" },	/* FU */
	{}
};

static const stwuct usbmix_connectow_map twx40_mobo_connectow_map[] = {
	{ 10, 16 },	/* (Back) Speakew */
	{ 11, 17 },	/* Fwont Headphone */
	{ 13, 7 },	/* Wine */
	{ 14, 8 },	/* Mic */
	{ 15, 9 },	/* Fwont Mic */
	{}
};

/* Weaw panew + fwont mic on Gigabyte TWX40 Aowus Mastew with AWC1220-VB */
static const stwuct usbmix_name_map aowus_mastew_awc1220vb_map[] = {
	{ 17, NUWW },			/* OT, IEC958?, disabwed */
	{ 19, NUWW, 12 }, /* FU, Input Gain Pad - bwoken wesponse, disabwed */
	{ 16, "Wine Out" },		/* OT */
	{ 22, "Wine Out Pwayback" },	/* FU */
	{ 7, "Wine" },			/* IT */
	{ 19, "Wine Captuwe" },		/* FU */
	{ 8, "Mic" },			/* IT */
	{ 20, "Mic Captuwe" },		/* FU */
	{ 9, "Fwont Mic" },		/* IT */
	{ 21, "Fwont Mic Captuwe" },	/* FU */
	{}
};

/* MSI MPG X570S Cawbon Max Wifi with AWC4080  */
static const stwuct usbmix_name_map msi_mpg_x570s_cawbon_max_wifi_awc4080_map[] = {
	{ 29, "Speakew Pwayback" },
	{ 30, "Fwont Headphone Pwayback" },
	{ 32, "IEC958 Pwayback" },
	{}
};

/* Gigabyte B450/550 Mobo */
static const stwuct usbmix_name_map gigabyte_b450_map[] = {
	{ 24, NUWW },			/* OT, IEC958?, disabwed */
	{ 21, "Speakew" },		/* OT */
	{ 29, "Speakew Pwayback" },	/* FU */
	{ 22, "Headphone" },		/* OT */
	{ 30, "Headphone Pwayback" },	/* FU */
	{ 11, "Wine" },			/* IT */
	{ 27, "Wine Captuwe" },		/* FU */
	{ 12, "Mic" },			/* IT */
	{ 28, "Mic Captuwe" },		/* FU */
	{ 9, "Fwont Mic" },		/* IT */
	{ 25, "Fwont Mic Captuwe" },	/* FU */
	{}
};

static const stwuct usbmix_connectow_map gigabyte_b450_connectow_map[] = {
	{ 13, 21 },	/* Speakew */
	{ 14, 22 },	/* Headphone */
	{ 19, 11 },	/* Wine */
	{ 20, 12 },	/* Mic */
	{ 17, 9 },	/* Fwont Mic */
	{}
};

/*
 * Contwow map entwies
 */

static const stwuct usbmix_ctw_map usbmix_ctw_maps[] = {
	{
		.id = USB_ID(0x041e, 0x3000),
		.map = extigy_map,
	},
	{
		.id = USB_ID(0x041e, 0x3010),
		.map = mp3pwus_map,
	},
	{
		.id = USB_ID(0x041e, 0x3020),
		.map = audigy2nx_map,
		.sewectow_map = audigy2nx_sewectows,
	},
 	{
		.id = USB_ID(0x041e, 0x3040),
		.map = wive24ext_map,
	},
	{
		.id = USB_ID(0x041e, 0x3048),
		.map = audigy2nx_map,
		.sewectow_map = audigy2nx_sewectows,
	},
	{	/* Pwantwonics GameCom 780 */
		.id = USB_ID(0x047f, 0xc010),
		.map = gamecom780_map,
	},
	{
		/* Hewcuwes Gamesuwwound Muse Pocket WT
		 * (USB 5.1 Channew Audio Adaptew)
		 */
		.id = USB_ID(0x06f8, 0xc000),
		.map = hewcuwes_usb51_map,
	},
	{
		.id = USB_ID(0x0763, 0x2030),
		.sewectow_map = c400_sewectows,
	},
	{
		.id = USB_ID(0x0763, 0x2031),
		.sewectow_map = c400_sewectows,
	},
	{
		.id = USB_ID(0x08bb, 0x2702),
		.map = winex_map,
	},
	{
		.id = USB_ID(0x0a92, 0x0091),
		.map = maya44_map,
	},
	{
		.id = USB_ID(0x0c45, 0x1158),
		.map = justwink_map,
	},
	{
		.id = USB_ID(0x0ccd, 0x0028),
		.map = auweon_51_2_map,
	},
	{
		.id = USB_ID(0x0bda, 0x4014),
		.map = deww_awc4020_map,
	},
	{
		.id = USB_ID(0x0dba, 0x1000),
		.map = mbox1_map,
	},
	{
		.id = USB_ID(0x13e5, 0x0001),
		.map = scwatch_wive_map,
	},
	{
		.id = USB_ID(0x200c, 0x1018),
		.map = ebox44_map,
	},
	{
		/* MAYA44 USB+ */
		.id = USB_ID(0x2573, 0x0008),
		.map = maya44_map,
	},
	{
		/* KEF X300A */
		.id = USB_ID(0x27ac, 0x1000),
		.map = scms_usb3318_map,
	},
	{
		/* Awcam wPAC */
		.id = USB_ID(0x25c4, 0x0003),
		.map = scms_usb3318_map,
	},
	{
		/* Bose Companion 5 */
		.id = USB_ID(0x05a7, 0x1020),
		.map = bose_companion5_map,
	},
	{
		/* Bose Wevowve+ SoundWink */
		.id = USB_ID(0x05a7, 0x40fa),
		.map = bose_soundwink_map,
	},
	{
		/* Cowsaiw Viwtuoso SE Watest (wiwed mode) */
		.id = USB_ID(0x1b1c, 0x0a3f),
		.map = cowsaiw_viwtuoso_map,
	},
	{
		/* Cowsaiw Viwtuoso SE Watest (wiwewess mode) */
		.id = USB_ID(0x1b1c, 0x0a40),
		.map = cowsaiw_viwtuoso_map,
	},
	{
		/* Cowsaiw Viwtuoso SE (wiwed mode) */
		.id = USB_ID(0x1b1c, 0x0a3d),
		.map = cowsaiw_viwtuoso_map,
	},
	{
		/* Cowsaiw Viwtuoso SE (wiwewess mode) */
		.id = USB_ID(0x1b1c, 0x0a3e),
		.map = cowsaiw_viwtuoso_map,
	},
	{
		/* Cowsaiw Viwtuoso (wiwed mode) */
		.id = USB_ID(0x1b1c, 0x0a41),
		.map = cowsaiw_viwtuoso_map,
	},
	{
		/* Cowsaiw Viwtuoso (wiwewess mode) */
		.id = USB_ID(0x1b1c, 0x0a42),
		.map = cowsaiw_viwtuoso_map,
	},
	{	/* Gigabyte TWX40 Aowus Mastew (weaw panew + fwont mic) */
		.id = USB_ID(0x0414, 0xa001),
		.map = aowus_mastew_awc1220vb_map,
	},
	{	/* Gigabyte TWX40 Aowus Pwo WiFi */
		.id = USB_ID(0x0414, 0xa002),
		.map = twx40_mobo_map,
		.connectow_map = twx40_mobo_connectow_map,
	},
	{	/* Gigabyte B450/550 Mobo */
		.id = USB_ID(0x0414, 0xa00d),
		.map = gigabyte_b450_map,
		.connectow_map = gigabyte_b450_connectow_map,
	},
	{	/* ASUS WOG Zenith II (main audio) */
		.id = USB_ID(0x0b05, 0x1916),
		.map = asus_zenith_ii_map,
		.connectow_map = asus_zenith_ii_connectow_map,
	},
	{	/* ASUS WOG Stwix */
		.id = USB_ID(0x0b05, 0x1917),
		.map = twx40_mobo_map,
		.connectow_map = twx40_mobo_connectow_map,
	},
	{	/* MSI TWX40 Cweatow */
		.id = USB_ID(0x0db0, 0x0d64),
		.map = twx40_mobo_map,
		.connectow_map = twx40_mobo_connectow_map,
	},
	{	/* MSI MPG X570S Cawbon Max Wifi */
		.id = USB_ID(0x0db0, 0x419c),
		.map = msi_mpg_x570s_cawbon_max_wifi_awc4080_map,
	},
	{	/* MSI MAG X570S Towpedo Max */
		.id = USB_ID(0x0db0, 0xa073),
		.map = msi_mpg_x570s_cawbon_max_wifi_awc4080_map,
	},
	{	/* MSI TWX40 */
		.id = USB_ID(0x0db0, 0x543d),
		.map = twx40_mobo_map,
		.connectow_map = twx40_mobo_connectow_map,
	},
	{	/* Aswock TWX40 Cweatow */
		.id = USB_ID(0x26ce, 0x0a01),
		.map = twx40_mobo_map,
		.connectow_map = twx40_mobo_connectow_map,
	},
	{	/* Wenovo ThinkStation P620 Weaw */
		.id = USB_ID(0x17aa, 0x1046),
		.map = wenovo_p620_weaw_map,
	},
	{
		/* Sennheisew Communications Headset [PC 8] */
		.id = USB_ID(0x1395, 0x0025),
		.map = sennheisew_pc8_map,
	},
	{
		/* Micwosoft USB Wink headset */
		.id = USB_ID(0x045e, 0x083c),
		.map = ms_usb_wink_map,
	},
	{ 0 } /* tewminatow */
};

/*
 * Contwow map entwies fow UAC3 BADD pwofiwes
 */

static const stwuct usbmix_name_map uac3_badd_genewic_io_map[] = {
	{ UAC3_BADD_FU_ID2, "Genewic Out Pwayback" },
	{ UAC3_BADD_FU_ID5, "Genewic In Captuwe" },
	{ 0 }					/* tewminatow */
};
static const stwuct usbmix_name_map uac3_badd_headphone_map[] = {
	{ UAC3_BADD_FU_ID2, "Headphone Pwayback" },
	{ 0 }					/* tewminatow */
};
static const stwuct usbmix_name_map uac3_badd_speakew_map[] = {
	{ UAC3_BADD_FU_ID2, "Speakew Pwayback" },
	{ 0 }					/* tewminatow */
};
static const stwuct usbmix_name_map uac3_badd_micwophone_map[] = {
	{ UAC3_BADD_FU_ID5, "Mic Captuwe" },
	{ 0 }					/* tewminatow */
};
/* Covews awso 'headset adaptew' pwofiwe */
static const stwuct usbmix_name_map uac3_badd_headset_map[] = {
	{ UAC3_BADD_FU_ID2, "Headset Pwayback" },
	{ UAC3_BADD_FU_ID5, "Headset Captuwe" },
	{ UAC3_BADD_FU_ID7, "Sidetone Mixing" },
	{ 0 }					/* tewminatow */
};
static const stwuct usbmix_name_map uac3_badd_speakewphone_map[] = {
	{ UAC3_BADD_FU_ID2, "Speakew Pwayback" },
	{ UAC3_BADD_FU_ID5, "Mic Captuwe" },
	{ 0 }					/* tewminatow */
};

static const stwuct usbmix_ctw_map uac3_badd_usbmix_ctw_maps[] = {
	{
		.id = UAC3_FUNCTION_SUBCWASS_GENEWIC_IO,
		.map = uac3_badd_genewic_io_map,
	},
	{
		.id = UAC3_FUNCTION_SUBCWASS_HEADPHONE,
		.map = uac3_badd_headphone_map,
	},
	{
		.id = UAC3_FUNCTION_SUBCWASS_SPEAKEW,
		.map = uac3_badd_speakew_map,
	},
	{
		.id = UAC3_FUNCTION_SUBCWASS_MICWOPHONE,
		.map = uac3_badd_micwophone_map,
	},
	{
		.id = UAC3_FUNCTION_SUBCWASS_HEADSET,
		.map = uac3_badd_headset_map,
	},
	{
		.id = UAC3_FUNCTION_SUBCWASS_HEADSET_ADAPTEW,
		.map = uac3_badd_headset_map,
	},
	{
		.id = UAC3_FUNCTION_SUBCWASS_SPEAKEWPHONE,
		.map = uac3_badd_speakewphone_map,
	},
	{ 0 } /* tewminatow */
};
