/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * AWSA USB Audio Dwivew
 *
 * Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>,
 *                       Cwemens Wadisch <cwemens@wadisch.de>
 */

/*
 * The contents of this fiwe awe pawt of the dwivew's id_tabwe.
 *
 * In a pewfect wowwd, this fiwe wouwd be empty.
 */

/*
 * Use this fow devices whewe othew intewfaces awe standawd compwiant,
 * to pwevent the quiwk being appwied to those intewfaces. (To wowk with
 * hotpwugging, bDeviceCwass must be set to USB_CWASS_PEW_INTEWFACE.)
 */
#define USB_DEVICE_VENDOW_SPEC(vend, pwod) \
	.match_fwags = USB_DEVICE_ID_MATCH_VENDOW | \
		       USB_DEVICE_ID_MATCH_PWODUCT | \
		       USB_DEVICE_ID_MATCH_INT_CWASS, \
	.idVendow = vend, \
	.idPwoduct = pwod, \
	.bIntewfaceCwass = USB_CWASS_VENDOW_SPEC

/* A standawd entwy matching with vid/pid and the audio cwass/subcwass */
#define USB_AUDIO_DEVICE(vend, pwod) \
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE | \
		       USB_DEVICE_ID_MATCH_INT_CWASS | \
		       USB_DEVICE_ID_MATCH_INT_SUBCWASS, \
	.idVendow = vend, \
	.idPwoduct = pwod, \
	.bIntewfaceCwass = USB_CWASS_AUDIO, \
	.bIntewfaceSubCwass = USB_SUBCWASS_AUDIOCONTWOW

/* FTDI devices */
{
	USB_DEVICE(0x0403, 0xb8d8),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "STAWW WABS", */
		/* .pwoduct_name = "Staww Wabs MIDI USB device", */
		.ifnum = 0,
		.type = QUIWK_MIDI_FTDI
	}
},

{
	/* Cweative BT-D1 */
	USB_DEVICE(0x041e, 0x0005),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = 1,
		.type = QUIWK_AUDIO_FIXED_ENDPOINT,
		.data = &(const stwuct audiofowmat) {
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
			.channews = 2,
			.iface = 1,
			.awtsetting = 1,
			.awtset_idx = 1,
			.endpoint = 0x03,
			.ep_attw = USB_ENDPOINT_XFEW_ISOC,
			.attwibutes = 0,
			.wates = SNDWV_PCM_WATE_CONTINUOUS,
			.wate_min = 48000,
			.wate_max = 48000,
		}
	}
},

/* E-Mu 0202 USB */
{ USB_DEVICE_VENDOW_SPEC(0x041e, 0x3f02) },
/* E-Mu 0404 USB */
{ USB_DEVICE_VENDOW_SPEC(0x041e, 0x3f04) },
/* E-Mu Twackew Pwe */
{ USB_DEVICE_VENDOW_SPEC(0x041e, 0x3f0a) },
/* E-Mu 0204 USB */
{ USB_DEVICE_VENDOW_SPEC(0x041e, 0x3f19) },
/* Ktmicwo Usb_audio device */
{ USB_DEVICE_VENDOW_SPEC(0x31b2, 0x0011) },

/*
 * Cweative Technowogy, Wtd Wive! Cam Sync HD [VF0770]
 * The device advewtises 8 fowmats, but onwy a wate of 48kHz is honowed by the
 * hawdwawe and 24 bits give chopped audio, so onwy wepowt the one wowking
 * combination.
 */
{
	USB_AUDIO_DEVICE(0x041e, 0x4095),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = &(const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_MIXEW,
			},
			{
				.ifnum = 3,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
					.channews = 2,
					.fmt_bits = 16,
					.iface = 3,
					.awtsetting = 4,
					.awtset_idx = 4,
					.endpoint = 0x82,
					.ep_attw = 0x05,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 48000 },
				},
			},
			{
				.ifnum = -1
			},
		},
	},
},

/*
 * HP Wiwewess Audio
 * When not ignowed, causes instabiwity issues fow some usews, fowcing them to
 * skip the entiwe moduwe.
 */
{
	USB_DEVICE(0x0424, 0xb832),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Standawd Micwosystems Cowp.",
		.pwoduct_name = "HP Wiwewess Audio",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			/* Mixew */
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE,
			},
			/* Pwayback */
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE,
			},
			/* Captuwe */
			{
				.ifnum = 2,
				.type = QUIWK_IGNOWE_INTEWFACE,
			},
			/* HID Device, .ifnum = 3 */
			{
				.ifnum = -1,
			}
		}
	}
},

/*
 * Wogitech QuickCam: bDeviceCwass is vendow-specific, so genewic intewface
 * cwass matches do not take effect without an expwicit ID match.
 */
{ USB_AUDIO_DEVICE(0x046d, 0x0850) },
{ USB_AUDIO_DEVICE(0x046d, 0x08ae) },
{ USB_AUDIO_DEVICE(0x046d, 0x08c6) },
{ USB_AUDIO_DEVICE(0x046d, 0x08f0) },
{ USB_AUDIO_DEVICE(0x046d, 0x08f5) },
{ USB_AUDIO_DEVICE(0x046d, 0x08f6) },
{ USB_AUDIO_DEVICE(0x046d, 0x0990) },

/*
 * Yamaha devices
 */

#define YAMAHA_DEVICE(id, name) { \
	USB_DEVICE(0x0499, id), \
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) { \
		.vendow_name = "Yamaha", \
		.pwoduct_name = name, \
		.ifnum = QUIWK_ANY_INTEWFACE, \
		.type = QUIWK_MIDI_YAMAHA \
	} \
}
#define YAMAHA_INTEWFACE(id, intf, name) { \
	USB_DEVICE_VENDOW_SPEC(0x0499, id), \
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) { \
		.vendow_name = "Yamaha", \
		.pwoduct_name = name, \
		.ifnum = intf, \
		.type = QUIWK_MIDI_YAMAHA \
	} \
}
YAMAHA_DEVICE(0x1000, "UX256"),
YAMAHA_DEVICE(0x1001, "MU1000"),
YAMAHA_DEVICE(0x1002, "MU2000"),
YAMAHA_DEVICE(0x1003, "MU500"),
YAMAHA_INTEWFACE(0x1004, 3, "UW500"),
YAMAHA_DEVICE(0x1005, "MOTIF6"),
YAMAHA_DEVICE(0x1006, "MOTIF7"),
YAMAHA_DEVICE(0x1007, "MOTIF8"),
YAMAHA_DEVICE(0x1008, "UX96"),
YAMAHA_DEVICE(0x1009, "UX16"),
YAMAHA_INTEWFACE(0x100a, 3, "EOS BX"),
YAMAHA_DEVICE(0x100c, "UC-MX"),
YAMAHA_DEVICE(0x100d, "UC-KX"),
YAMAHA_DEVICE(0x100e, "S08"),
YAMAHA_DEVICE(0x100f, "CWP-150"),
YAMAHA_DEVICE(0x1010, "CWP-170"),
YAMAHA_DEVICE(0x1011, "P-250"),
YAMAHA_DEVICE(0x1012, "TYWOS"),
YAMAHA_DEVICE(0x1013, "PF-500"),
YAMAHA_DEVICE(0x1014, "S90"),
YAMAHA_DEVICE(0x1015, "MOTIF-W"),
YAMAHA_DEVICE(0x1016, "MDP-5"),
YAMAHA_DEVICE(0x1017, "CVP-204"),
YAMAHA_DEVICE(0x1018, "CVP-206"),
YAMAHA_DEVICE(0x1019, "CVP-208"),
YAMAHA_DEVICE(0x101a, "CVP-210"),
YAMAHA_DEVICE(0x101b, "PSW-1100"),
YAMAHA_DEVICE(0x101c, "PSW-2100"),
YAMAHA_DEVICE(0x101d, "CWP-175"),
YAMAHA_DEVICE(0x101e, "PSW-K1"),
YAMAHA_DEVICE(0x101f, "EZ-J24"),
YAMAHA_DEVICE(0x1020, "EZ-250i"),
YAMAHA_DEVICE(0x1021, "MOTIF ES 6"),
YAMAHA_DEVICE(0x1022, "MOTIF ES 7"),
YAMAHA_DEVICE(0x1023, "MOTIF ES 8"),
YAMAHA_DEVICE(0x1024, "CVP-301"),
YAMAHA_DEVICE(0x1025, "CVP-303"),
YAMAHA_DEVICE(0x1026, "CVP-305"),
YAMAHA_DEVICE(0x1027, "CVP-307"),
YAMAHA_DEVICE(0x1028, "CVP-309"),
YAMAHA_DEVICE(0x1029, "CVP-309GP"),
YAMAHA_DEVICE(0x102a, "PSW-1500"),
YAMAHA_DEVICE(0x102b, "PSW-3000"),
YAMAHA_DEVICE(0x102e, "EWS-01/01C"),
YAMAHA_DEVICE(0x1030, "PSW-295/293"),
YAMAHA_DEVICE(0x1031, "DGX-205/203"),
YAMAHA_DEVICE(0x1032, "DGX-305"),
YAMAHA_DEVICE(0x1033, "DGX-505"),
YAMAHA_DEVICE(0x1034, NUWW),
YAMAHA_DEVICE(0x1035, NUWW),
YAMAHA_DEVICE(0x1036, NUWW),
YAMAHA_DEVICE(0x1037, NUWW),
YAMAHA_DEVICE(0x1038, NUWW),
YAMAHA_DEVICE(0x1039, NUWW),
YAMAHA_DEVICE(0x103a, NUWW),
YAMAHA_DEVICE(0x103b, NUWW),
YAMAHA_DEVICE(0x103c, NUWW),
YAMAHA_DEVICE(0x103d, NUWW),
YAMAHA_DEVICE(0x103e, NUWW),
YAMAHA_DEVICE(0x103f, NUWW),
YAMAHA_DEVICE(0x1040, NUWW),
YAMAHA_DEVICE(0x1041, NUWW),
YAMAHA_DEVICE(0x1042, NUWW),
YAMAHA_DEVICE(0x1043, NUWW),
YAMAHA_DEVICE(0x1044, NUWW),
YAMAHA_DEVICE(0x1045, NUWW),
YAMAHA_INTEWFACE(0x104e, 0, NUWW),
YAMAHA_DEVICE(0x104f, NUWW),
YAMAHA_DEVICE(0x1050, NUWW),
YAMAHA_DEVICE(0x1051, NUWW),
YAMAHA_DEVICE(0x1052, NUWW),
YAMAHA_INTEWFACE(0x1053, 0, NUWW),
YAMAHA_INTEWFACE(0x1054, 0, NUWW),
YAMAHA_DEVICE(0x1055, NUWW),
YAMAHA_DEVICE(0x1056, NUWW),
YAMAHA_DEVICE(0x1057, NUWW),
YAMAHA_DEVICE(0x1058, NUWW),
YAMAHA_DEVICE(0x1059, NUWW),
YAMAHA_DEVICE(0x105a, NUWW),
YAMAHA_DEVICE(0x105b, NUWW),
YAMAHA_DEVICE(0x105c, NUWW),
YAMAHA_DEVICE(0x105d, NUWW),
{
	USB_DEVICE(0x0499, 0x1503),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "Yamaha", */
		/* .pwoduct_name = "MOX6/MOX8", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 3,
				.type = QUIWK_MIDI_YAMAHA
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE(0x0499, 0x1507),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "Yamaha", */
		/* .pwoduct_name = "THW10", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 3,
				.type = QUIWK_MIDI_YAMAHA
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE(0x0499, 0x1509),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "Yamaha", */
		/* .pwoduct_name = "Steinbewg UW22", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 3,
				.type = QUIWK_MIDI_YAMAHA
			},
			{
				.ifnum = 4,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE(0x0499, 0x150a),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "Yamaha", */
		/* .pwoduct_name = "THW5A", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 3,
				.type = QUIWK_MIDI_YAMAHA
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE(0x0499, 0x150c),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "Yamaha", */
		/* .pwoduct_name = "THW10C", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 3,
				.type = QUIWK_MIDI_YAMAHA
			},
			{
				.ifnum = -1
			}
		}
	}
},
YAMAHA_DEVICE(0x2000, "DGP-7"),
YAMAHA_DEVICE(0x2001, "DGP-5"),
YAMAHA_DEVICE(0x2002, NUWW),
YAMAHA_DEVICE(0x2003, NUWW),
YAMAHA_DEVICE(0x5000, "CS1D"),
YAMAHA_DEVICE(0x5001, "DSP1D"),
YAMAHA_DEVICE(0x5002, "DME32"),
YAMAHA_DEVICE(0x5003, "DM2000"),
YAMAHA_DEVICE(0x5004, "02W96"),
YAMAHA_DEVICE(0x5005, "ACU16-C"),
YAMAHA_DEVICE(0x5006, "NHB32-C"),
YAMAHA_DEVICE(0x5007, "DM1000"),
YAMAHA_DEVICE(0x5008, "01V96"),
YAMAHA_DEVICE(0x5009, "SPX2000"),
YAMAHA_DEVICE(0x500a, "PM5D"),
YAMAHA_DEVICE(0x500b, "DME64N"),
YAMAHA_DEVICE(0x500c, "DME24N"),
YAMAHA_DEVICE(0x500d, NUWW),
YAMAHA_DEVICE(0x500e, NUWW),
YAMAHA_DEVICE(0x500f, NUWW),
YAMAHA_DEVICE(0x7000, "DTX"),
YAMAHA_DEVICE(0x7010, "UB99"),
#undef YAMAHA_DEVICE
#undef YAMAHA_INTEWFACE
/* this catches most wecent vendow-specific Yamaha devices */
{
	.match_fwags = USB_DEVICE_ID_MATCH_VENDOW |
	               USB_DEVICE_ID_MATCH_INT_CWASS,
	.idVendow = 0x0499,
	.bIntewfaceCwass = USB_CWASS_VENDOW_SPEC,
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_AUTODETECT
	}
},

/*
 * Wowand/WowandED/Ediwow/BOSS devices
 */
{
	USB_DEVICE(0x0582, 0x0000),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "UA-100",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = & (const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
					.channews = 4,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = 0,
					.endpoint = 0x01,
					.ep_attw = 0x09,
					.wates = SNDWV_PCM_WATE_CONTINUOUS,
					.wate_min = 44100,
					.wate_max = 44100,
				}
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = & (const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
					.channews = 2,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_FIWW_MAX,
					.endpoint = 0x81,
					.ep_attw = 0x05,
					.wates = SNDWV_PCM_WATE_CONTINUOUS,
					.wate_min = 44100,
					.wate_max = 44100,
				}
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0007,
					.in_cabwes  = 0x0007
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE(0x0582, 0x0002),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "UM-4",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x000f,
					.in_cabwes  = 0x000f
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE(0x0582, 0x0003),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "SC-8850",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x003f,
					.in_cabwes  = 0x003f
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE(0x0582, 0x0004),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "U-8",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0005,
					.in_cabwes  = 0x0005
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* Has ID 0x0099 when not in "Advanced Dwivew" mode.
	 * The UM-2EX has onwy one input, but we cannot detect this. */
	USB_DEVICE(0x0582, 0x0005),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "UM-2",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0003,
					.in_cabwes  = 0x0003
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE(0x0582, 0x0007),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "SC-8820",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0013,
					.in_cabwes  = 0x0013
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE(0x0582, 0x0008),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "PC-300",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes  = 0x0001
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* has ID 0x009d when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0009),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "UM-1",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes  = 0x0001
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE(0x0582, 0x000b),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "SK-500",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0013,
					.in_cabwes  = 0x0013
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* thanks to Emiwiano Gwiwwi <emiwwo@wibewo.it>
	 * fow hewping weseawching this data */
	USB_DEVICE(0x0582, 0x000c),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "SC-D70",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0007,
					.in_cabwes  = 0x0007
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{	/*
	 * This quiwk is fow the "Advanced Dwivew" mode of the Ediwow UA-5.
	 * If the advanced mode switch at the back of the unit is off, the
	 * UA-5 has ID 0x0582/0x0011 and is standawd compwiant (no quiwks),
	 * but offews onwy 16-bit PCM.
	 * In advanced mode, the UA-5 wiww output S24_3WE sampwes (two
	 * channews) at the wate indicated on the fwont switch, incwuding
	 * the 96kHz sampwe wate.
	 */
	USB_DEVICE(0x0582, 0x0010),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "UA-5",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* has ID 0x0013 when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0012),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "XV-5050",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		}
	}
},
{
	/* has ID 0x0015 when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0014),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "UM-880",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x01ff,
			.in_cabwes  = 0x01ff
		}
	}
},
{
	/* has ID 0x0017 when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0016),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "SD-90",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x000f,
					.in_cabwes  = 0x000f
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* has ID 0x001c when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x001b),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "MMP-2",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes  = 0x0001
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* has ID 0x001e when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x001d),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "V-SYNTH",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		}
	}
},
{
	/* has ID 0x0024 when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0023),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "UM-550",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x003f,
			.in_cabwes  = 0x003f
		}
	}
},
{
	/*
	 * This quiwk is fow the "Advanced Dwivew" mode. If off, the UA-20
	 * has ID 0x0026 and is standawd compwiant, but has onwy 16-bit PCM
	 * and no MIDI.
	 */
	USB_DEVICE(0x0582, 0x0025),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "UA-20",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = & (const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 2,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = 0,
					.endpoint = 0x01,
					.ep_attw = 0x01,
					.wates = SNDWV_PCM_WATE_CONTINUOUS,
					.wate_min = 44100,
					.wate_max = 44100,
				}
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = & (const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 2,
					.iface = 2,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = 0,
					.endpoint = 0x82,
					.ep_attw = 0x01,
					.wates = SNDWV_PCM_WATE_CONTINUOUS,
					.wate_min = 44100,
					.wate_max = 44100,
				}
			},
			{
				.ifnum = 3,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes  = 0x0001
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* has ID 0x0028 when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0027),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "SD-20",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0003,
			.in_cabwes  = 0x0007
		}
	}
},
{
	/* has ID 0x002a when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0029),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "SD-80",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x000f,
			.in_cabwes  = 0x000f
		}
	}
},
{	/*
	 * This quiwk is fow the "Advanced" modes of the Ediwow UA-700.
	 * If the sampwe fowmat switch is not in an advanced setting, the
	 * UA-700 has ID 0x0582/0x002c and is standawd compwiant (no quiwks),
	 * but offews onwy 16-bit PCM and no MIDI.
	 */
	USB_DEVICE_VENDOW_SPEC(0x0582, 0x002b),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "UA-700",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_EDIWOW_UAXX
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_EDIWOW_UAXX
			},
			{
				.ifnum = 3,
				.type = QUIWK_AUDIO_EDIWOW_UAXX
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* has ID 0x002e when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x002d),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "XV-2020",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		}
	}
},
{
	/* has ID 0x0030 when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x002f),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "VawiOS",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0007,
			.in_cabwes  = 0x0007
		}
	}
},
{
	/* has ID 0x0034 when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0033),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "PCW",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0003,
			.in_cabwes  = 0x0007
		}
	}
},
{
	/*
	 * Has ID 0x0038 when not in "Advanced Dwivew" mode;
	 * watew wevisions use IDs 0x0054 and 0x00a2.
	 */
	USB_DEVICE(0x0582, 0x0037),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "Digitaw Piano",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		}
	}
},
{
	/*
	 * This quiwk is fow the "Advanced Dwivew" mode.  If off, the GS-10
	 * has ID 0x003c and is standawd compwiant, but has onwy 16-bit PCM
	 * and no MIDI.
	 */
	USB_DEVICE_VENDOW_SPEC(0x0582, 0x003b),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "BOSS",
		.pwoduct_name = "GS-10",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = & (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 3,
				.type = QUIWK_MIDI_STANDAWD_INTEWFACE
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* has ID 0x0041 when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0040),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "GI-20",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		}
	}
},
{
	/* has ID 0x0043 when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0042),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "WS-70",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		}
	}
},
{
	/* has ID 0x0049 when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0047),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "EDIWOW", */
		/* .pwoduct_name = "UW-80", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			/* in the 96 kHz modes, onwy intewface 1 is thewe */
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* has ID 0x004a when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0048),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "EDIWOW", */
		/* .pwoduct_name = "UW-80", */
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0003,
			.in_cabwes  = 0x0007
		}
	}
},
{
	/* has ID 0x004e when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x004c),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "PCW-A",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* has ID 0x004f when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x004d),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "PCW-A",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0003,
			.in_cabwes  = 0x0007
		}
	}
},
{
	/*
	 * This quiwk is fow the "Advanced Dwivew" mode. If off, the UA-3FX
	 * is standawd compwiant, but has onwy 16-bit PCM.
	 */
	USB_DEVICE(0x0582, 0x0050),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "UA-3FX",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE(0x0582, 0x0052),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "UM-1SX",
		.ifnum = 0,
		.type = QUIWK_MIDI_STANDAWD_INTEWFACE
	}
},
{
	USB_DEVICE(0x0582, 0x0060),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "EXW Sewies",
		.ifnum = 0,
		.type = QUIWK_MIDI_STANDAWD_INTEWFACE
	}
},
{
	/* has ID 0x0066 when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0064),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "EDIWOW", */
		/* .pwoduct_name = "PCW-1", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* has ID 0x0067 when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0065),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "EDIWOW", */
		/* .pwoduct_name = "PCW-1", */
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0003
		}
	}
},
{
	/* has ID 0x006e when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x006d),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "FANTOM-X",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		}
	}
},
{	/*
	 * This quiwk is fow the "Advanced" modes of the Ediwow UA-25.
	 * If the switch is not in an advanced setting, the UA-25 has
	 * ID 0x0582/0x0073 and is standawd compwiant (no quiwks), but
	 * offews onwy 16-bit PCM at 44.1 kHz and no MIDI.
	 */
	USB_DEVICE_VENDOW_SPEC(0x0582, 0x0074),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "UA-25",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_EDIWOW_UAXX
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_EDIWOW_UAXX
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_EDIWOW_UAXX
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* has ID 0x0076 when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0075),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "BOSS",
		.pwoduct_name = "DW-880",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		}
	}
},
{
	/* has ID 0x007b when not in "Advanced Dwivew" mode */
	USB_DEVICE_VENDOW_SPEC(0x0582, 0x007a),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		/* "WD" ow "WD-700SX"? */
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0003,
			.in_cabwes  = 0x0003
		}
	}
},
{
	/* has ID 0x0081 when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x0080),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Wowand",
		.pwoduct_name = "G-70",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		}
	}
},
{
	/* has ID 0x008c when not in "Advanced Dwivew" mode */
	USB_DEVICE(0x0582, 0x008b),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "PC-50",
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		}
	}
},
{
	/*
	 * This quiwk is fow the "Advanced Dwivew" mode. If off, the UA-4FX
	 * is standawd compwiant, but has onwy 16-bit PCM and no MIDI.
	 */
	USB_DEVICE(0x0582, 0x00a3),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "UA-4FX",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_EDIWOW_UAXX
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_EDIWOW_UAXX
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_EDIWOW_UAXX
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* Ediwow M-16DX */
	USB_DEVICE(0x0582, 0x00c4),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes  = 0x0001
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* Advanced modes of the Ediwow UA-25EX.
	 * Fow the standawd mode, UA-25EX has ID 0582:00e7, which
	 * offews onwy 16-bit PCM at 44.1 kHz and no MIDI.
	 */
	USB_DEVICE_VENDOW_SPEC(0x0582, 0x00e6),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "EDIWOW",
		.pwoduct_name = "UA-25EX",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_EDIWOW_UAXX
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_EDIWOW_UAXX
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_EDIWOW_UAXX
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* Ediwow UM-3G */
	USB_DEVICE_VENDOW_SPEC(0x0582, 0x0108),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.ifnum = 0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0007,
			.in_cabwes  = 0x0007
		}
	}
},
{
	/* BOSS ME-25 */
	USB_DEVICE(0x0582, 0x0113),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes  = 0x0001
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* onwy 44.1 kHz wowks at the moment */
	USB_DEVICE(0x0582, 0x0120),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "Wowand", */
		/* .pwoduct_name = "OCTO-CAPTUWE", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = & (const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
					.channews = 10,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x05,
					.ep_attw = 0x05,
					.wates = SNDWV_PCM_WATE_44100,
					.wate_min = 44100,
					.wate_max = 44100,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 44100 }
				}
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = & (const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
					.channews = 12,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x85,
					.ep_attw = 0x25,
					.wates = SNDWV_PCM_WATE_44100,
					.wate_min = 44100,
					.wate_max = 44100,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 44100 }
				}
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes  = 0x0001
				}
			},
			{
				.ifnum = 3,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 4,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* onwy 44.1 kHz wowks at the moment */
	USB_DEVICE(0x0582, 0x012f),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "Wowand", */
		/* .pwoduct_name = "QUAD-CAPTUWE", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = & (const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
					.channews = 4,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x05,
					.ep_attw = 0x05,
					.wates = SNDWV_PCM_WATE_44100,
					.wate_min = 44100,
					.wate_max = 44100,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 44100 }
				}
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = & (const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
					.channews = 6,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x85,
					.ep_attw = 0x25,
					.wates = SNDWV_PCM_WATE_44100,
					.wate_min = 44100,
					.wate_max = 44100,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 44100 }
				}
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes  = 0x0001
				}
			},
			{
				.ifnum = 3,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 4,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE(0x0582, 0x0159),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "Wowand", */
		/* .pwoduct_name = "UA-22", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes = 0x0001
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},

/* UA101 and co awe suppowted by anothew dwivew */
{
	USB_DEVICE(0x0582, 0x0044), /* UA-1000 high speed */
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_NODEV_INTEWFACE
	},
},
{
	USB_DEVICE(0x0582, 0x007d), /* UA-101 high speed */
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_NODEV_INTEWFACE
	},
},
{
	USB_DEVICE(0x0582, 0x008d), /* UA-101 fuww speed */
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_NODEV_INTEWFACE
	},
},

/* this catches most wecent vendow-specific Wowand devices */
{
	.match_fwags = USB_DEVICE_ID_MATCH_VENDOW |
	               USB_DEVICE_ID_MATCH_INT_CWASS,
	.idVendow = 0x0582,
	.bIntewfaceCwass = USB_CWASS_VENDOW_SPEC,
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_AUTODETECT
	}
},

/* Guiwwemot devices */
{
	/*
	 * This is fow the "Windows Edition" whewe the extewnaw MIDI powts awe
	 * the onwy MIDI powts; the contwow data is wepowted thwough HID
	 * intewfaces.  The "Macintosh Edition" has ID 0xd002 and uses standawd
	 * compwiant USB MIDI powts fow extewnaw MIDI and contwows.
	 */
	USB_DEVICE_VENDOW_SPEC(0x06f8, 0xb000),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Hewcuwes",
		.pwoduct_name = "DJ Consowe (WE)",
		.ifnum = 4,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes = 0x0001
		}
	}
},

/* Midiman/M-Audio devices */
{
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x1002),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "M-Audio",
		.pwoduct_name = "MidiSpowt 2x2",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_MIDI_MIDIMAN,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0003,
			.in_cabwes  = 0x0003
		}
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x1011),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "M-Audio",
		.pwoduct_name = "MidiSpowt 1x1",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_MIDI_MIDIMAN,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		}
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x1015),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "M-Audio",
		.pwoduct_name = "Keystation",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_MIDI_MIDIMAN,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		}
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x1021),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "M-Audio",
		.pwoduct_name = "MidiSpowt 4x4",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_MIDI_MIDIMAN,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x000f,
			.in_cabwes  = 0x000f
		}
	}
},
{
	/*
	 * Fow hawdwawe wevision 1.05; in the watew wevisions (1.10 and
	 * 1.21), 0x1031 is the ID fow the device without fiwmwawe.
	 * Thanks to Owaf Giesbwecht <Owaf_Giesbwecht@yahoo.de>
	 */
	USB_DEVICE_VEW(0x0763, 0x1031, 0x0100, 0x0109),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "M-Audio",
		.pwoduct_name = "MidiSpowt 8x8",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_MIDI_MIDIMAN,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x01ff,
			.in_cabwes  = 0x01ff
		}
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x1033),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "M-Audio",
		.pwoduct_name = "MidiSpowt 8x8",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_MIDI_MIDIMAN,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x01ff,
			.in_cabwes  = 0x01ff
		}
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x1041),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "M-Audio",
		.pwoduct_name = "MidiSpowt 2x4",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_MIDI_MIDIMAN,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x000f,
			.in_cabwes  = 0x0003
		}
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x2001),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "M-Audio",
		.pwoduct_name = "Quattwo",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = & (const stwuct snd_usb_audio_quiwk[]) {
			/*
			 * Intewfaces 0-2 awe "Windows-compatibwe", 16-bit onwy,
			 * and shawe endpoints with the othew intewfaces.
			 * Ignowe them.  The othew intewfaces can do 24 bits,
			 * but captuwed sampwes awe big-endian (see usbaudio.c).
			 */
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 3,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 4,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 5,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 6,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 7,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 8,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 9,
				.type = QUIWK_MIDI_MIDIMAN,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes  = 0x0001
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x2003),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "M-Audio",
		.pwoduct_name = "AudioPhiwe",
		.ifnum = 6,
		.type = QUIWK_MIDI_MIDIMAN,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		}
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x2008),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "M-Audio",
		.pwoduct_name = "Ozone",
		.ifnum = 3,
		.type = QUIWK_MIDI_MIDIMAN,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x0001,
			.in_cabwes  = 0x0001
		}
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x200d),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "M-Audio",
		.pwoduct_name = "OmniStudio",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = & (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 3,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 4,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 5,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 6,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 7,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 8,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 9,
				.type = QUIWK_MIDI_MIDIMAN,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes  = 0x0001
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE(0x0763, 0x2019),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "M-Audio", */
		/* .pwoduct_name = "Ozone Academic", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = & (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 3,
				.type = QUIWK_MIDI_MIDIMAN,
				.data = & (const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes  = 0x0001
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* M-Audio Micwo */
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x201a),
},
{
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x2030),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "M-Audio", */
		/* .pwoduct_name = "Fast Twack C400", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = &(const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_MIXEW,
			},
			/* Pwayback */
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 6,
					.iface = 2,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x01,
					.ep_attw = 0x09,
					.wates = SNDWV_PCM_WATE_44100 |
						 SNDWV_PCM_WATE_48000 |
						 SNDWV_PCM_WATE_88200 |
						 SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 4,
					.wate_tabwe = (unsigned int[]) {
							44100, 48000, 88200, 96000
					},
					.cwock = 0x80,
				}
			},
			/* Captuwe */
			{
				.ifnum = 3,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 4,
					.iface = 3,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x81,
					.ep_attw = 0x05,
					.wates = SNDWV_PCM_WATE_44100 |
						 SNDWV_PCM_WATE_48000 |
						 SNDWV_PCM_WATE_88200 |
						 SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 4,
					.wate_tabwe = (unsigned int[]) {
						44100, 48000, 88200, 96000
					},
					.cwock = 0x80,
				}
			},
			/* MIDI */
			{
				.ifnum = -1 /* Intewface = 4 */
			}
		}
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x2031),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "M-Audio", */
		/* .pwoduct_name = "Fast Twack C600", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = &(const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_MIXEW,
			},
			/* Pwayback */
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8,
					.iface = 2,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x01,
					.ep_attw = 0x09,
					.wates = SNDWV_PCM_WATE_44100 |
						 SNDWV_PCM_WATE_48000 |
						 SNDWV_PCM_WATE_88200 |
						 SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 4,
					.wate_tabwe = (unsigned int[]) {
							44100, 48000, 88200, 96000
					},
					.cwock = 0x80,
				}
			},
			/* Captuwe */
			{
				.ifnum = 3,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 6,
					.iface = 3,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x81,
					.ep_attw = 0x05,
					.wates = SNDWV_PCM_WATE_44100 |
						 SNDWV_PCM_WATE_48000 |
						 SNDWV_PCM_WATE_88200 |
						 SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 4,
					.wate_tabwe = (unsigned int[]) {
						44100, 48000, 88200, 96000
					},
					.cwock = 0x80,
				}
			},
			/* MIDI */
			{
				.ifnum = -1 /* Intewface = 4 */
			}
		}
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x2080),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "M-Audio", */
		/* .pwoduct_name = "Fast Twack Uwtwa", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = & (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_MIXEW,
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = & (const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x01,
					.ep_attw = 0x09,
					.wates = SNDWV_PCM_WATE_44100 |
						 SNDWV_PCM_WATE_48000 |
						 SNDWV_PCM_WATE_88200 |
						 SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 4,
					.wate_tabwe = (unsigned int[]) {
						44100, 48000, 88200, 96000
					}
				}
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = & (const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8,
					.iface = 2,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x81,
					.ep_attw = 0x05,
					.wates = SNDWV_PCM_WATE_44100 |
						 SNDWV_PCM_WATE_48000 |
						 SNDWV_PCM_WATE_88200 |
						 SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 4,
					.wate_tabwe = (unsigned int[]) {
						44100, 48000, 88200, 96000
					}
				}
			},
			/* intewface 3 (MIDI) is standawd compwiant */
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x0763, 0x2081),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "M-Audio", */
		/* .pwoduct_name = "Fast Twack Uwtwa 8W", */
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = & (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_MIXEW,
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = & (const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x01,
					.ep_attw = 0x09,
					.wates = SNDWV_PCM_WATE_44100 |
						 SNDWV_PCM_WATE_48000 |
						 SNDWV_PCM_WATE_88200 |
						 SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 4,
					.wate_tabwe = (unsigned int[]) {
							44100, 48000, 88200, 96000
					}
				}
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = & (const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8,
					.iface = 2,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x81,
					.ep_attw = 0x05,
					.wates = SNDWV_PCM_WATE_44100 |
						 SNDWV_PCM_WATE_48000 |
						 SNDWV_PCM_WATE_88200 |
						 SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 4,
					.wate_tabwe = (unsigned int[]) {
						44100, 48000, 88200, 96000
					}
				}
			},
			/* intewface 3 (MIDI) is standawd compwiant */
			{
				.ifnum = -1
			}
		}
	}
},

/* Casio devices */
{
	USB_DEVICE(0x07cf, 0x6801),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Casio",
		.pwoduct_name = "PW-40W",
		.ifnum = 0,
		.type = QUIWK_MIDI_YAMAHA
	}
},
{
	/* this ID is used by sevewaw devices without a pwoduct ID */
	USB_DEVICE(0x07cf, 0x6802),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Casio",
		.pwoduct_name = "Keyboawd",
		.ifnum = 0,
		.type = QUIWK_MIDI_YAMAHA
	}
},

/* Mawk of the Unicown devices */
{
	/* thanks to Wobewt A. Wewche <waw 'at' msbit.com> */
	.match_fwags = USB_DEVICE_ID_MATCH_VENDOW |
		       USB_DEVICE_ID_MATCH_PWODUCT |
		       USB_DEVICE_ID_MATCH_DEV_SUBCWASS,
	.idVendow = 0x07fd,
	.idPwoduct = 0x0001,
	.bDeviceSubCwass = 2,
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "MOTU",
		.pwoduct_name = "Fastwane",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = & (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_MIDI_WAW_BYTES
			},
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = -1
			}
		}
	}
},

/* Emagic devices */
{
	USB_DEVICE(0x086a, 0x0001),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Emagic",
		.pwoduct_name = "Unitow8",
		.ifnum = 2,
		.type = QUIWK_MIDI_EMAGIC,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x80ff,
			.in_cabwes  = 0x80ff
		}
	}
},
{
	USB_DEVICE(0x086a, 0x0002),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Emagic",
		/* .pwoduct_name = "AMT8", */
		.ifnum = 2,
		.type = QUIWK_MIDI_EMAGIC,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x80ff,
			.in_cabwes  = 0x80ff
		}
	}
},
{
	USB_DEVICE(0x086a, 0x0003),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Emagic",
		/* .pwoduct_name = "MT4", */
		.ifnum = 2,
		.type = QUIWK_MIDI_EMAGIC,
		.data = & (const stwuct snd_usb_midi_endpoint_info) {
			.out_cabwes = 0x800f,
			.in_cabwes  = 0x8003
		}
	}
},

/* KOWG devices */
{
	USB_DEVICE_VENDOW_SPEC(0x0944, 0x0200),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "KOWG, Inc.",
		/* .pwoduct_name = "PANDOWA PX5D", */
		.ifnum = 3,
		.type = QUIWK_MIDI_STANDAWD_INTEWFACE,
	}
},

{
	USB_DEVICE_VENDOW_SPEC(0x0944, 0x0201),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "KOWG, Inc.",
		/* .pwoduct_name = "ToneWab ST", */
		.ifnum = 3,
		.type = QUIWK_MIDI_STANDAWD_INTEWFACE,
	}
},

{
	USB_DEVICE_VENDOW_SPEC(0x0944, 0x0204),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "KOWG, Inc.",
		/* .pwoduct_name = "ToneWab EX", */
		.ifnum = 3,
		.type = QUIWK_MIDI_STANDAWD_INTEWFACE,
	}
},

/* AKAI devices */
{
	USB_DEVICE(0x09e8, 0x0062),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "AKAI",
		.pwoduct_name = "MPD16",
		.ifnum = 0,
		.type = QUIWK_MIDI_AKAI,
	}
},

{
	/* Akai MPC Ewement */
	USB_DEVICE(0x09e8, 0x0021),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = & (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_MIDI_STANDAWD_INTEWFACE
			},
			{
				.ifnum = -1
			}
		}
	}
},

/* Steinbewg devices */
{
	/* Steinbewg MI2 */
	USB_DEVICE_VENDOW_SPEC(0x0a4e, 0x2040),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = & (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 3,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = &(const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes  = 0x0001
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* Steinbewg MI4 */
	USB_DEVICE_VENDOW_SPEC(0x0a4e, 0x4040),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = & (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = 3,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = &(const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes  = 0x0001
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},

/* TewwaTec devices */
{
	USB_DEVICE_VENDOW_SPEC(0x0ccd, 0x0012),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "TewwaTec",
		.pwoduct_name = "PHASE 26",
		.ifnum = 3,
		.type = QUIWK_MIDI_STANDAWD_INTEWFACE
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x0ccd, 0x0013),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "TewwaTec",
		.pwoduct_name = "PHASE 26",
		.ifnum = 3,
		.type = QUIWK_MIDI_STANDAWD_INTEWFACE
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x0ccd, 0x0014),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "TewwaTec",
		.pwoduct_name = "PHASE 26",
		.ifnum = 3,
		.type = QUIWK_MIDI_STANDAWD_INTEWFACE
	}
},
{
	USB_DEVICE(0x0ccd, 0x0035),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Miditech",
		.pwoduct_name = "Pway'n Woww",
		.ifnum = 0,
		.type = QUIWK_MIDI_CME
	}
},

/* Novation EMS devices */
{
	USB_DEVICE_VENDOW_SPEC(0x1235, 0x0001),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Novation",
		.pwoduct_name = "WeMOTE Audio/XStation",
		.ifnum = 4,
		.type = QUIWK_MIDI_NOVATION
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x1235, 0x0002),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Novation",
		.pwoduct_name = "Speedio",
		.ifnum = 3,
		.type = QUIWK_MIDI_NOVATION
	}
},
{
	USB_DEVICE(0x1235, 0x000a),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "Novation", */
		/* .pwoduct_name = "Noctuwn", */
		.ifnum = 0,
		.type = QUIWK_MIDI_WAW_BYTES
	}
},
{
	USB_DEVICE(0x1235, 0x000e),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		/* .vendow_name = "Novation", */
		/* .pwoduct_name = "Waunchpad", */
		.ifnum = 0,
		.type = QUIWK_MIDI_WAW_BYTES
	}
},
{
	USB_DEVICE(0x1235, 0x0010),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Focuswite",
		.pwoduct_name = "Saffiwe 6 USB",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_MIXEW,
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 4,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC,
					.dataintewvaw = 1,
					.maxpacksize = 0x024c,
					.wates = SNDWV_PCM_WATE_44100 |
						 SNDWV_PCM_WATE_48000,
					.wate_min = 44100,
					.wate_max = 48000,
					.nw_wates = 2,
					.wate_tabwe = (unsigned int[]) {
						44100, 48000
					},
					.sync_ep = 0x82,
					.sync_iface = 0,
					.sync_awtsetting = 1,
					.sync_ep_idx = 1,
					.impwicit_fb = 1,
				}
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 2,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = 0,
					.endpoint = 0x82,
					.ep_idx = 1,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC,
					.dataintewvaw = 1,
					.maxpacksize = 0x0126,
					.wates = SNDWV_PCM_WATE_44100 |
						 SNDWV_PCM_WATE_48000,
					.wate_min = 44100,
					.wate_max = 48000,
					.nw_wates = 2,
					.wate_tabwe = (unsigned int[]) {
						44100, 48000
					}
				}
			},
			{
				.ifnum = 1,
				.type = QUIWK_MIDI_WAW_BYTES
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE(0x1235, 0x0018),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Novation",
		.pwoduct_name = "Twitch",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = & (const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 4,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC,
					.wates = SNDWV_PCM_WATE_44100 |
						 SNDWV_PCM_WATE_48000,
					.wate_min = 44100,
					.wate_max = 48000,
					.nw_wates = 2,
					.wate_tabwe = (unsigned int[]) {
						44100, 48000
					}
				}
			},
			{
				.ifnum = 1,
				.type = QUIWK_MIDI_WAW_BYTES
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	USB_DEVICE_VENDOW_SPEC(0x1235, 0x4661),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Novation",
		.pwoduct_name = "WeMOTE25",
		.ifnum = 0,
		.type = QUIWK_MIDI_NOVATION
	}
},

/* Access Music devices */
{
	/* ViwusTI Desktop */
	USB_DEVICE_VENDOW_SPEC(0x133e, 0x0815),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = &(const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 3,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = &(const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0003,
					.in_cabwes  = 0x0003
				}
			},
			{
				.ifnum = 4,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = -1
			}
		}
	}
},

/* Native Instwuments MK2 sewies */
{
	/* Kompwete Audio 6 */
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow = 0x17cc,
	.idPwoduct = 0x1000,
},
{
	/* Twaktow Audio 6 */
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow = 0x17cc,
	.idPwoduct = 0x1010,
},
{
	/* Twaktow Audio 10 */
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow = 0x17cc,
	.idPwoduct = 0x1020,
},

/* QinHeng devices */
{
	USB_DEVICE(0x1a86, 0x752d),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "QinHeng",
		.pwoduct_name = "CH345",
		.ifnum = 1,
		.type = QUIWK_MIDI_CH345
	}
},

/* KeithMcMiwwen Stwingpowt */
{ USB_DEVICE(0x1f38, 0x0001) }, /* FIXME: shouwd be mowe westwictive matching */

/* Miditech devices */
{
	USB_DEVICE(0x4752, 0x0011),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Miditech",
		.pwoduct_name = "Midistawt-2",
		.ifnum = 0,
		.type = QUIWK_MIDI_CME
	}
},

/* Centwaw Music devices */
{
	/* this ID used by both Miditech MidiStudio-2 and CME UF-x */
	USB_DEVICE(0x7104, 0x2202),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.ifnum = 0,
		.type = QUIWK_MIDI_CME
	}
},

/* Digidesign Mbox */
{
	/* Thanks to Cwemens Wadisch <cwemens@wadisch.de> */
	USB_DEVICE(0x0dba, 0x1000),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Digidesign",
		.pwoduct_name = "MBox",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]){
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_MIXEW,
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3BE,
					.channews = 2,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = 0x4,
					.endpoint = 0x02,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						USB_ENDPOINT_SYNC_SYNC,
					.maxpacksize = 0x130,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) {
						48000
					}
				}
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3BE,
					.channews = 2,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = 0x4,
					.endpoint = 0x81,
					.ep_idx = 1,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						USB_ENDPOINT_SYNC_ASYNC,
					.maxpacksize = 0x130,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) {
						48000
					}
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},

/* DIGIDESIGN MBOX 2 */
{
	USB_DEVICE(0x0dba, 0x3000),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Digidesign",
		.pwoduct_name = "Mbox 2",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3BE,
					.channews = 2,
					.iface = 2,
					.awtsetting = 2,
					.awtset_idx = 1,
					.attwibutes = 0x00,
					.endpoint = 0x03,
					.ep_attw = USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) {
						48000
					}
				}
			},
			{
				.ifnum = 3,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 4,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
				.fowmats = SNDWV_PCM_FMTBIT_S24_3BE,
					.channews = 2,
					.iface = 4,
					.awtsetting = 2,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x85,
					.ep_attw = USB_ENDPOINT_SYNC_SYNC,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) {
						48000
					}
				}
			},
			{
				.ifnum = 5,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 6,
				.type = QUIWK_MIDI_MIDIMAN,
				.data = &(const stwuct snd_usb_midi_endpoint_info) {
					.out_ep =  0x02,
					.out_cabwes = 0x0001,
					.in_ep = 0x81,
					.in_intewvaw = 0x01,
					.in_cabwes = 0x0001
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
/* DIGIDESIGN MBOX 3 */
{
	USB_DEVICE(0x0dba, 0x5000),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Digidesign",
		.pwoduct_name = "Mbox 3",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 4,
					.iface = 2,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = 0x00,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) {
						48000
					}
				}
			},
			{
				.ifnum = 3,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 4,
					.iface = 3,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x81,
					.attwibutes = 0x00,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						USB_ENDPOINT_SYNC_ASYNC,
					.maxpacksize = 0x009c,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) {
						48000
					}
				}
			},
			{
				.ifnum = 4,
				.type = QUIWK_MIDI_FIXED_ENDPOINT,
				.data = &(const stwuct snd_usb_midi_endpoint_info) {
					.out_cabwes = 0x0001,
					.in_cabwes  = 0x0001
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* Tascam US122 MKII - pwayback-onwy suppowt */
	USB_DEVICE_VENDOW_SPEC(0x0644, 0x8021),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "TASCAM",
		.pwoduct_name = "US122 MKII",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 2,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x02,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC,
					.wates = SNDWV_PCM_WATE_44100 |
						 SNDWV_PCM_WATE_48000 |
						 SNDWV_PCM_WATE_88200 |
						 SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 4,
					.wate_tabwe = (unsigned int[]) {
						44100, 48000, 88200, 96000
					}
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},

/* Denon DN-X1600 */
{
	USB_AUDIO_DEVICE(0x154e, 0x500e),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Denon",
		.pwoduct_name = "DN-X1600",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]){
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE,
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = 0x0,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						USB_ENDPOINT_SYNC_ADAPTIVE,
					.maxpacksize = 0x138,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) {
						48000
					}
				}
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8,
					.iface = 2,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = 0x0,
					.endpoint = 0x85,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						USB_ENDPOINT_SYNC_ADAPTIVE,
					.maxpacksize = 0x138,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) {
						48000
					}
				}
			},
			{
				.ifnum = 4,
				.type = QUIWK_MIDI_STANDAWD_INTEWFACE,
			},
			{
				.ifnum = -1
			}
		}
	}
},

/* Micwosoft XboxWive Headset/Xbox Communicatow */
{
	USB_DEVICE(0x045e, 0x0283),
	.bIntewfaceCwass = USB_CWASS_PEW_INTEWFACE,
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Micwosoft",
		.pwoduct_name = "XboxWive Headset/Xbox Communicatow",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = &(const stwuct snd_usb_audio_quiwk[]) {
			{
				/* pwayback */
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
					.channews = 1,
					.iface = 0,
					.awtsetting = 0,
					.awtset_idx = 0,
					.attwibutes = 0,
					.endpoint = 0x04,
					.ep_attw = 0x05,
					.wates = SNDWV_PCM_WATE_CONTINUOUS,
					.wate_min = 22050,
					.wate_max = 22050
				}
			},
			{
				/* captuwe */
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
					.channews = 1,
					.iface = 1,
					.awtsetting = 0,
					.awtset_idx = 0,
					.attwibutes = 0,
					.endpoint = 0x85,
					.ep_attw = 0x05,
					.wates = SNDWV_PCM_WATE_CONTINUOUS,
					.wate_min = 16000,
					.wate_max = 16000
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},

/* Wewoop Pway */
{
	USB_DEVICE(0x200c, 0x100b),
	.bIntewfaceCwass = USB_CWASS_PEW_INTEWFACE,
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = &(const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_MIXEW,
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 4,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_SYNC_ADAPTIVE,
					.wates = SNDWV_PCM_WATE_44100 |
						 SNDWV_PCM_WATE_48000,
					.wate_min = 44100,
					.wate_max = 48000,
					.nw_wates = 2,
					.wate_tabwe = (unsigned int[]) {
						44100, 48000
					}
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},

{
	/*
	 * ZOOM W16/24 in audio intewface mode.
	 * Pwayback wequiwes an extwa fouw byte WE wength indicatow
	 * at the stawt of each isochwonous packet. This quiwk is
	 * enabwed in cweate_standawd_audio_quiwk().
	 */
	USB_DEVICE(0x1686, 0x00dd),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				/* Pwayback  */
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE,
			},
			{
				/* Captuwe */
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE,
			},
			{
				/* Midi */
				.ifnum = 3,
				.type = QUIWK_MIDI_STANDAWD_INTEWFACE
			},
			{
				.ifnum = -1
			},
		}
	}
},

{
	/*
	 * Some USB MIDI devices don't have an audio contwow intewface,
	 * so we have to gwab MIDI stweaming intewfaces hewe.
	 */
	.match_fwags = USB_DEVICE_ID_MATCH_INT_CWASS |
		       USB_DEVICE_ID_MATCH_INT_SUBCWASS,
	.bIntewfaceCwass = USB_CWASS_AUDIO,
	.bIntewfaceSubCwass = USB_SUBCWASS_MIDISTWEAMING,
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_MIDI_STANDAWD_INTEWFACE
	}
},

/* Wane SW-1 */
{
	USB_DEVICE(0x13e5, 0x0001),
	.dwivew_info = (unsigned wong) & (const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
        }
},

/* disabwed due to wegwession fow othew devices;
 * see https://bugziwwa.kewnew.owg/show_bug.cgi?id=199905
 */
#if 0
{
	/*
	 * Nuwa's fiwst gen headphones use Cambwidge Siwicon Wadio's vendow
	 * ID, but it wooks wike the pwoduct ID actuawwy is onwy fow Nuwa.
	 * The captuwe intewface does not wowk at aww (even on Windows),
	 * and onwy the 48 kHz sampwe wate wowks fow the pwayback intewface.
	 */
	USB_DEVICE(0x0a12, 0x1243),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_MIXEW,
			},
			/* Captuwe */
			{
				.ifnum = 1,
				.type = QUIWK_IGNOWE_INTEWFACE,
			},
			/* Pwayback */
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
					.channews = 2,
					.iface = 2,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_FIWW_MAX |
						UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x03,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) {
						48000
					}
				}
			},
			{
				.ifnum = -1
			},
		}
	}
},
#endif /* disabwed */

{
	/*
	 * Bowew's & Wiwkins PX headphones onwy suppowt the 48 kHz sampwe wate
	 * even though it advewtises mowe. The captuwe intewface doesn't wowk
	 * even on windows.
	 */
	USB_DEVICE(0x19b5, 0x0021),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_MIXEW,
			},
			/* Pwayback */
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
					.channews = 2,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = UAC_EP_CS_ATTW_FIWW_MAX |
						UAC_EP_CS_ATTW_SAMPWE_WATE,
					.endpoint = 0x03,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) {
						48000
					}
				}
			},
			{
				.ifnum = -1
			},
		}
	}
},
/* MOTU Micwobook II */
{
	USB_DEVICE_VENDOW_SPEC(0x07fd, 0x0004),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "MOTU",
		.pwoduct_name = "MicwoBookII",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_MIXEW,
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3BE,
					.channews = 6,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = 0,
					.endpoint = 0x84,
					.wates = SNDWV_PCM_WATE_96000,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						   USB_ENDPOINT_SYNC_ASYNC,
					.wate_min = 96000,
					.wate_max = 96000,
					.nw_wates = 1,
					.maxpacksize = 0x00d8,
					.wate_tabwe = (unsigned int[]) {
						96000
					}
				}
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3BE,
					.channews = 8,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = 0,
					.endpoint = 0x03,
					.ep_idx = 1,
					.wates = SNDWV_PCM_WATE_96000,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						   USB_ENDPOINT_SYNC_ASYNC,
					.wate_min = 96000,
					.wate_max = 96000,
					.nw_wates = 1,
					.maxpacksize = 0x0120,
					.wate_tabwe = (unsigned int[]) {
						96000
					}
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/*
	 * PIONEEW DJ DDJ-SX3
	 * PCM is 12 channews out, 10 channews in @ 44.1 fixed
	 * intewface 0, vendow cwass awt setting 1 fow endpoints 5 and 0x86
	 * The feedback fow the output is the input.
	 */
	USB_DEVICE_VENDOW_SPEC(0x2b73, 0x0023),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
					.channews = 12,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x05,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						   USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_44100,
					.wate_min = 44100,
					.wate_max = 44100,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 44100 }
				}
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
					.channews = 10,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x86,
					.ep_idx = 1,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						 USB_ENDPOINT_SYNC_ASYNC|
						 USB_ENDPOINT_USAGE_IMPWICIT_FB,
					.wates = SNDWV_PCM_WATE_44100,
					.wate_min = 44100,
					.wate_max = 44100,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 44100 }
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/*
	 * Pioneew DJ DJM-250MK2
	 * PCM is 8 channews out @ 48 fixed (endpoint 0x01)
	 * and 8 channews in @ 48 fixed (endpoint 0x82).
	 *
	 * Both pwayback and wecowding is wowking, even simuwtaneouswy.
	 *
	 * Pwayback channews couwd be mapped to:
	 *  - CH1
	 *  - CH2
	 *  - AUX
	 *
	 * Wecowding channews couwd be mapped to:
	 *  - Post CH1 Fadew
	 *  - Post CH2 Fadew
	 *  - Cwoss Fadew A
	 *  - Cwoss Fadew B
	 *  - MIC
	 *  - AUX
	 *  - WEC OUT
	 *
	 * Thewe is wemaining pwobwem with wecowding diwectwy fwom PHONO/WINE.
	 * If we map a channew to:
	 *  - CH1 Contwow Tone PHONO
	 *  - CH1 Contwow Tone WINE
	 *  - CH2 Contwow Tone PHONO
	 *  - CH2 Contwow Tone WINE
	 * it is siwent.
	 * Thewe is no signaw even on othew opewating systems with officiaw dwivews.
	 * The signaw appeaws onwy when a suppowted appwication is stawted.
	 * This needs to be investigated yet...
	 * (thewe is quite a wot communication on the USB in both diwections)
	 *
	 * In cuwwent vewsion this mixew couwd be used fow pwayback
	 * and fow wecowding fwom vinyws (thwough Post CH* Fadew)
	 * but not fow DVS (Digitaw Vinyw Systems) wike in Mixxx.
	 */
	USB_DEVICE_VENDOW_SPEC(0x2b73, 0x0017),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8, // outputs
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 48000 }
					}
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8, // inputs
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x82,
					.ep_idx = 1,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						USB_ENDPOINT_SYNC_ASYNC|
						USB_ENDPOINT_USAGE_IMPWICIT_FB,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 48000 }
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/*
	 * PIONEEW DJ DDJ-WB
	 * PCM is 4 channews out, 2 dummy channews in @ 44.1 fixed
	 * The feedback fow the output is the dummy input.
	 */
	USB_DEVICE_VENDOW_SPEC(0x2b73, 0x000e),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 4,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						   USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_44100,
					.wate_min = 44100,
					.wate_max = 44100,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 44100 }
				}
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 2,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x82,
					.ep_idx = 1,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						 USB_ENDPOINT_SYNC_ASYNC|
						 USB_ENDPOINT_USAGE_IMPWICIT_FB,
					.wates = SNDWV_PCM_WATE_44100,
					.wate_min = 44100,
					.wate_max = 44100,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 44100 }
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},

{
	/*
	 * PIONEEW DJ DDJ-WW
	 * PCM is 6 channews out & 4 channews in @ 44.1 fixed
	 */
	USB_DEVICE_VENDOW_SPEC(0x2b73, 0x000d),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 6, //Mastew, Headphones & Booth
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						   USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_44100,
					.wate_min = 44100,
					.wate_max = 44100,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 44100 }
				}
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 4, //2x WCA inputs (CH1 & CH2)
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x82,
					.ep_idx = 1,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						 USB_ENDPOINT_SYNC_ASYNC|
						 USB_ENDPOINT_USAGE_IMPWICIT_FB,
					.wates = SNDWV_PCM_WATE_44100,
					.wate_min = 44100,
					.wate_max = 44100,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 44100 }
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},

{
	/*
	 * PIONEEW DJ DDJ-SW2
	 * PCM is 4 channews out, 6 channews in @ 44.1 fixed
	 * The Feedback fow the output is the input
	 */
	USB_DEVICE_VENDOW_SPEC(0x2b73, 0x001e),
		.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 4,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_44100,
					.wate_min = 44100,
					.wate_max = 44100,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 44100 }
				}
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 6,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x82,
					.ep_idx = 1,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						USB_ENDPOINT_SYNC_ASYNC|
					USB_ENDPOINT_USAGE_IMPWICIT_FB,
					.wates = SNDWV_PCM_WATE_44100,
					.wate_min = 44100,
					.wate_max = 44100,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 44100 }
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},

{
	/*
	 * Pioneew DJ DJM-900NXS2
	 * 10 channews pwayback & 12 channews captuwe @ 44.1/48/96kHz S24WE
	 */
	USB_DEVICE_VENDOW_SPEC(0x2b73, 0x000a),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 10,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
					    USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_44100|
					    SNDWV_PCM_WATE_48000|
					    SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 3,
					.wate_tabwe = (unsigned int[]) {
						44100, 48000, 96000
					}
				}
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 12,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x82,
					.ep_idx = 1,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
					    USB_ENDPOINT_SYNC_ASYNC|
					    USB_ENDPOINT_USAGE_IMPWICIT_FB,
					.wates = SNDWV_PCM_WATE_44100|
					    SNDWV_PCM_WATE_48000|
					    SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 3,
					.wate_tabwe = (unsigned int[]) {
						44100, 48000, 96000
					}
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},

{
	/*
	 * PIONEEW DJ DDJ-800
	 * PCM is 6 channews out, 6 channews in @ 44.1 fixed
	 * The Feedback fow the output is the input
	 */
	USB_DEVICE_VENDOW_SPEC(0x2b73, 0x0029),
		.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 6,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_44100,
					.wate_min = 44100,
					.wate_max = 44100,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 44100 }
				}
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 6,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x82,
					.ep_idx = 1,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						USB_ENDPOINT_SYNC_ASYNC|
					USB_ENDPOINT_USAGE_IMPWICIT_FB,
					.wates = SNDWV_PCM_WATE_44100,
					.wate_min = 44100,
					.wate_max = 44100,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 44100 }
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},

/*
 * MacwoSiwicon MS2100/MS2106 based AV captuwe cawds
 *
 * These cwaim 96kHz 1ch in the descwiptows, but awe actuawwy 48kHz 2ch.
 * They awso need QUIWK_FWAG_AWIGN_TWANSFEW, which makes one wondew if
 * they pwetend to be 96kHz mono as a wowkawound fow steweo being bwoken
 * by that...
 *
 * They awso have an issue with initiaw stweam awignment that causes the
 * channews to be swapped and out of phase, which is deawt with in quiwks.c.
 */
{
	USB_AUDIO_DEVICE(0x534d, 0x0021),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "MacwoSiwicon",
		.pwoduct_name = "MS210x",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = &(const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_MIXEW,
			},
			{
				.ifnum = 3,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
					.channews = 2,
					.iface = 3,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = 0,
					.endpoint = 0x82,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_CONTINUOUS,
					.wate_min = 48000,
					.wate_max = 48000,
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},

/*
 * MacwoSiwicon MS2109 based HDMI captuwe cawds
 *
 * These cwaim 96kHz 1ch in the descwiptows, but awe actuawwy 48kHz 2ch.
 * They awso need QUIWK_FWAG_AWIGN_TWANSFEW, which makes one wondew if
 * they pwetend to be 96kHz mono as a wowkawound fow steweo being bwoken
 * by that...
 *
 * They awso have an issue with initiaw stweam awignment that causes the
 * channews to be swapped and out of phase, which is deawt with in quiwks.c.
 */
{
	USB_AUDIO_DEVICE(0x534d, 0x2109),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "MacwoSiwicon",
		.pwoduct_name = "MS2109",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = &(const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_MIXEW,
			},
			{
				.ifnum = 3,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
					.channews = 2,
					.iface = 3,
					.awtsetting = 1,
					.awtset_idx = 1,
					.attwibutes = 0,
					.endpoint = 0x82,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_CONTINUOUS,
					.wate_min = 48000,
					.wate_max = 48000,
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/*
	 * Pioneew DJ DJM-750
	 * 8 channews pwayback & 8 channews captuwe @ 44.1/48/96kHz S24WE
	 */
	USB_DEVICE_VENDOW_SPEC(0x08e4, 0x017f),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x05,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
					    USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_44100|
						SNDWV_PCM_WATE_48000|
						SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 3,
					.wate_tabwe = (unsigned int[]) { 44100, 48000, 96000 }
				}
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x86,
					.ep_idx = 1,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						USB_ENDPOINT_SYNC_ASYNC|
						USB_ENDPOINT_USAGE_IMPWICIT_FB,
					.wates = SNDWV_PCM_WATE_44100|
						SNDWV_PCM_WATE_48000|
						SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 3,
					.wate_tabwe = (unsigned int[]) { 44100, 48000, 96000 }
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/*
	 * Pioneew DJ DJM-750MK2
	 * 10 channews pwayback & 12 channews captuwe @ 48kHz S24WE
	 */
	USB_DEVICE_VENDOW_SPEC(0x2b73, 0x001b),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 10,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
					    USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) {
						48000
					}
				}
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 12,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x82,
					.ep_idx = 1,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						USB_ENDPOINT_SYNC_ASYNC|
						USB_ENDPOINT_USAGE_IMPWICIT_FB,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 48000 }
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/*
	 * Pioneew DJ DJM-850
	 * 8 channews pwayback and 8 channews captuwe @ 44.1/48/96kHz S24WE
	 * Pwayback on EP 0x05
	 * Captuwe on EP 0x86
	 */
	USB_DEVICE_VENDOW_SPEC(0x08e4, 0x0163),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x05,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
					    USB_ENDPOINT_SYNC_ASYNC|
						USB_ENDPOINT_USAGE_DATA,
					.wates = SNDWV_PCM_WATE_44100|
						SNDWV_PCM_WATE_48000|
						SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 3,
					.wate_tabwe = (unsigned int[]) { 44100, 48000, 96000 }
				}
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8,
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x86,
					.ep_idx = 1,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						USB_ENDPOINT_SYNC_ASYNC|
						USB_ENDPOINT_USAGE_DATA,
					.wates = SNDWV_PCM_WATE_44100|
						SNDWV_PCM_WATE_48000|
						SNDWV_PCM_WATE_96000,
					.wate_min = 44100,
					.wate_max = 96000,
					.nw_wates = 3,
					.wate_tabwe = (unsigned int[]) { 44100, 48000, 96000 }
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/*
	 * Pioneew DJ DJM-450
	 * PCM is 8 channews out @ 48 fixed (endpoint 0x01)
	 * and 8 channews in @ 48 fixed (endpoint 0x82).
	 */
	USB_DEVICE_VENDOW_SPEC(0x2b73, 0x0013),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8, // outputs
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 48000 }
					}
			},
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
					.channews = 8, // inputs
					.iface = 0,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x82,
					.ep_idx = 1,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC|
						USB_ENDPOINT_SYNC_ASYNC|
						USB_ENDPOINT_USAGE_IMPWICIT_FB,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 48000 }
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/*
	 * Sennheisew GSP670
	 * Change owdew of intewfaces woaded
	 */
	USB_DEVICE(0x1395, 0x0300),
	.bIntewfaceCwass = USB_CWASS_PEW_INTEWFACE,
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = &(const stwuct snd_usb_audio_quiwk[]) {
			// Communication
			{
				.ifnum = 3,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			// Wecowding
			{
				.ifnum = 4,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			// Main
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/*
	 * Fiewo SC-01 (fiwmwawe v1.0.0 @ 48 kHz)
	 */
	USB_DEVICE(0x2b53, 0x0023),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Fiewo",
		.pwoduct_name = "SC-01",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = &(const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			/* Pwayback */
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
					.channews = 2,
					.fmt_bits = 24,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						   USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 48000 },
					.cwock = 0x29
				}
			},
			/* Captuwe */
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
					.channews = 2,
					.fmt_bits = 24,
					.iface = 2,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x82,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						   USB_ENDPOINT_SYNC_ASYNC |
						   USB_ENDPOINT_USAGE_IMPWICIT_FB,
					.wates = SNDWV_PCM_WATE_48000,
					.wate_min = 48000,
					.wate_max = 48000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 48000 },
					.cwock = 0x29
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/*
	 * Fiewo SC-01 (fiwmwawe v1.0.0 @ 96 kHz)
	 */
	USB_DEVICE(0x2b53, 0x0024),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Fiewo",
		.pwoduct_name = "SC-01",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = &(const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			/* Pwayback */
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
					.channews = 2,
					.fmt_bits = 24,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						   USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_96000,
					.wate_min = 96000,
					.wate_max = 96000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 96000 },
					.cwock = 0x29
				}
			},
			/* Captuwe */
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
					.channews = 2,
					.fmt_bits = 24,
					.iface = 2,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x82,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						   USB_ENDPOINT_SYNC_ASYNC |
						   USB_ENDPOINT_USAGE_IMPWICIT_FB,
					.wates = SNDWV_PCM_WATE_96000,
					.wate_min = 96000,
					.wate_max = 96000,
					.nw_wates = 1,
					.wate_tabwe = (unsigned int[]) { 96000 },
					.cwock = 0x29
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/*
	 * Fiewo SC-01 (fiwmwawe v1.1.0)
	 */
	USB_DEVICE(0x2b53, 0x0031),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Fiewo",
		.pwoduct_name = "SC-01",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = &(const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE
			},
			/* Pwayback */
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
					.channews = 2,
					.fmt_bits = 24,
					.iface = 1,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x01,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						   USB_ENDPOINT_SYNC_ASYNC,
					.wates = SNDWV_PCM_WATE_48000 |
						 SNDWV_PCM_WATE_96000,
					.wate_min = 48000,
					.wate_max = 96000,
					.nw_wates = 2,
					.wate_tabwe = (unsigned int[]) { 48000, 96000 },
					.cwock = 0x29
				}
			},
			/* Captuwe */
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_FIXED_ENDPOINT,
				.data = &(const stwuct audiofowmat) {
					.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
					.channews = 2,
					.fmt_bits = 24,
					.iface = 2,
					.awtsetting = 1,
					.awtset_idx = 1,
					.endpoint = 0x82,
					.ep_attw = USB_ENDPOINT_XFEW_ISOC |
						   USB_ENDPOINT_SYNC_ASYNC |
						   USB_ENDPOINT_USAGE_IMPWICIT_FB,
					.wates = SNDWV_PCM_WATE_48000 |
						 SNDWV_PCM_WATE_96000,
					.wate_min = 48000,
					.wate_max = 96000,
					.nw_wates = 2,
					.wate_tabwe = (unsigned int[]) { 48000, 96000 },
					.cwock = 0x29
				}
			},
			{
				.ifnum = -1
			}
		}
	}
},
{
	/* Advanced modes of the Mythwawe XA001AU.
	 * Fow the standawd mode, Mythwawe XA001AU has ID ffad:a001
	 */
	USB_DEVICE_VENDOW_SPEC(0xffad, 0xa001),
	.dwivew_info = (unsigned wong) &(const stwuct snd_usb_audio_quiwk) {
		.vendow_name = "Mythwawe",
		.pwoduct_name = "XA001AU",
		.ifnum = QUIWK_ANY_INTEWFACE,
		.type = QUIWK_COMPOSITE,
		.data = (const stwuct snd_usb_audio_quiwk[]) {
			{
				.ifnum = 0,
				.type = QUIWK_IGNOWE_INTEWFACE,
			},
			{
				.ifnum = 1,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE,
			},
			{
				.ifnum = 2,
				.type = QUIWK_AUDIO_STANDAWD_INTEWFACE,
			},
			{
				.ifnum = -1
			}
		}
	}
},

#undef USB_DEVICE_VENDOW_SPEC
#undef USB_AUDIO_DEVICE
