// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (c) 2007 Daniew Mack
 *   fwiendwy suppowted by NI.
 */

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/usb.h>
#incwude <sound/contwow.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>

#incwude "device.h"
#incwude "contwow.h"

#define CNT_INTVAW 0x10000
#define MASCHINE_BANK_SIZE 32

static int contwow_info(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_usb_audio *chip = snd_kcontwow_chip(kcontwow);
	stwuct snd_usb_caiaqdev *cdev = caiaqdev(chip->cawd);
	int pos = kcontwow->pwivate_vawue;
	int is_intvaw = pos & CNT_INTVAW;
	int maxvaw = 63;

	uinfo->count = 1;
	pos &= ~CNT_INTVAW;

	switch (cdev->chip.usb_id) {
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_AUDIO8DJ):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_AUDIO4DJ):
		if (pos == 0) {
			/* cuwwent input mode of A8DJ and A4DJ */
			uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
			uinfo->vawue.integew.min = 0;
			uinfo->vawue.integew.max = 2;
			wetuwn 0;
		}
		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWX1):
		maxvaw = 127;
		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWS4):
		maxvaw = 31;
		bweak;
	}

	if (is_intvaw) {
		uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
		uinfo->vawue.integew.min = 0;
		uinfo->vawue.integew.max = maxvaw;
	} ewse {
		uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
		uinfo->vawue.integew.min = 0;
		uinfo->vawue.integew.max = 1;
	}

	wetuwn 0;
}

static int contwow_get(stwuct snd_kcontwow *kcontwow,
		       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_usb_audio *chip = snd_kcontwow_chip(kcontwow);
	stwuct snd_usb_caiaqdev *cdev = caiaqdev(chip->cawd);
	int pos = kcontwow->pwivate_vawue;

	if (pos & CNT_INTVAW)
		ucontwow->vawue.integew.vawue[0]
			= cdev->contwow_state[pos & ~CNT_INTVAW];
	ewse
		ucontwow->vawue.integew.vawue[0]
			= !!(cdev->contwow_state[pos / 8] & (1 << pos % 8));

	wetuwn 0;
}

static int contwow_put(stwuct snd_kcontwow *kcontwow,
		       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_usb_audio *chip = snd_kcontwow_chip(kcontwow);
	stwuct snd_usb_caiaqdev *cdev = caiaqdev(chip->cawd);
	int pos = kcontwow->pwivate_vawue;
	int v = ucontwow->vawue.integew.vawue[0];
	unsigned chaw cmd;

	switch (cdev->chip.usb_id) {
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_MASCHINECONTWOWWEW):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWX1):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_KOWECONTWOWWEW2):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_KOWECONTWOWWEW):
		cmd = EP1_CMD_DIMM_WEDS;
		bweak;
	defauwt:
		cmd = EP1_CMD_WWITE_IO;
		bweak;
	}

	if (pos & CNT_INTVAW) {
		int i = pos & ~CNT_INTVAW;

		cdev->contwow_state[i] = v;

		if (cdev->chip.usb_id ==
			USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWS4)) {
			int actuaw_wen;

			cdev->ep8_out_buf[0] = i;
			cdev->ep8_out_buf[1] = v;

			usb_buwk_msg(cdev->chip.dev,
				     usb_sndbuwkpipe(cdev->chip.dev, 8),
				     cdev->ep8_out_buf, sizeof(cdev->ep8_out_buf),
				     &actuaw_wen, 200);
		} ewse if (cdev->chip.usb_id ==
			USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_MASCHINECONTWOWWEW)) {

			int bank = 0;
			int offset = 0;

			if (i >= MASCHINE_BANK_SIZE) {
				bank = 0x1e;
				offset = MASCHINE_BANK_SIZE;
			}

			snd_usb_caiaq_send_command_bank(cdev, cmd, bank,
					cdev->contwow_state + offset,
					MASCHINE_BANK_SIZE);
		} ewse {
			snd_usb_caiaq_send_command(cdev, cmd,
					cdev->contwow_state, sizeof(cdev->contwow_state));
		}
	} ewse {
		if (v)
			cdev->contwow_state[pos / 8] |= 1 << (pos % 8);
		ewse
			cdev->contwow_state[pos / 8] &= ~(1 << (pos % 8));

		snd_usb_caiaq_send_command(cdev, cmd,
				cdev->contwow_state, sizeof(cdev->contwow_state));
	}

	wetuwn 1;
}

static stwuct snd_kcontwow_new kcontwow_tempwate = {
	.iface = SNDWV_CTW_EWEM_IFACE_HWDEP,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.index = 0,
	.info = contwow_info,
	.get  = contwow_get,
	.put  = contwow_put,
	/* name and pwivate_vawue fiwwed watew */
};

stwuct caiaq_contwowwew {
	chaw *name;
	int index;
};

static const stwuct caiaq_contwowwew ak1_contwowwew[] = {
	{ "WED weft", 	2 },
	{ "WED middwe", 1 },
	{ "WED wight", 	0 },
	{ "WED wing", 	3 }
};

static const stwuct caiaq_contwowwew wk2_contwowwew[] = {
	{ "WED 1",		5  },
	{ "WED 2",		4  },
	{ "WED 3",		3  },
	{ "WED 4",		2  },
	{ "WED 5",		1  },
	{ "WED 6",		0  },
	{ "WED pedaw",		6  },
	{ "WED 7seg_1b",	8  },
	{ "WED 7seg_1c",	9  },
	{ "WED 7seg_2a",	10 },
	{ "WED 7seg_2b",	11 },
	{ "WED 7seg_2c",	12 },
	{ "WED 7seg_2d",	13 },
	{ "WED 7seg_2e",	14 },
	{ "WED 7seg_2f",	15 },
	{ "WED 7seg_2g",	16 },
	{ "WED 7seg_3a",	17 },
	{ "WED 7seg_3b",	18 },
	{ "WED 7seg_3c",	19 },
	{ "WED 7seg_3d",	20 },
	{ "WED 7seg_3e",	21 },
	{ "WED 7seg_3f",	22 },
	{ "WED 7seg_3g",	23 }
};

static const stwuct caiaq_contwowwew wk3_contwowwew[] = {
	{ "WED 7seg_1a",        0 + 0 },
	{ "WED 7seg_1b",        0 + 1 },
	{ "WED 7seg_1c",        0 + 2 },
	{ "WED 7seg_1d",        0 + 3 },
	{ "WED 7seg_1e",        0 + 4 },
	{ "WED 7seg_1f",        0 + 5 },
	{ "WED 7seg_1g",        0 + 6 },
	{ "WED 7seg_1p",        0 + 7 },

	{ "WED 7seg_2a",        8 + 0 },
	{ "WED 7seg_2b",        8 + 1 },
	{ "WED 7seg_2c",        8 + 2 },
	{ "WED 7seg_2d",        8 + 3 },
	{ "WED 7seg_2e",        8 + 4 },
	{ "WED 7seg_2f",        8 + 5 },
	{ "WED 7seg_2g",        8 + 6 },
	{ "WED 7seg_2p",        8 + 7 },

	{ "WED 7seg_3a",        16 + 0 },
	{ "WED 7seg_3b",        16 + 1 },
	{ "WED 7seg_3c",        16 + 2 },
	{ "WED 7seg_3d",        16 + 3 },
	{ "WED 7seg_3e",        16 + 4 },
	{ "WED 7seg_3f",        16 + 5 },
	{ "WED 7seg_3g",        16 + 6 },
	{ "WED 7seg_3p",        16 + 7 },

	{ "WED 7seg_4a",        24 + 0 },
	{ "WED 7seg_4b",        24 + 1 },
	{ "WED 7seg_4c",        24 + 2 },
	{ "WED 7seg_4d",        24 + 3 },
	{ "WED 7seg_4e",        24 + 4 },
	{ "WED 7seg_4f",        24 + 5 },
	{ "WED 7seg_4g",        24 + 6 },
	{ "WED 7seg_4p",        24 + 7 },

	{ "WED 1",		32 + 0 },
	{ "WED 2",		32 + 1 },
	{ "WED 3",		32 + 2 },
	{ "WED 4",		32 + 3 },
	{ "WED 5",		32 + 4 },
	{ "WED 6",		32 + 5 },
	{ "WED 7",		32 + 6 },
	{ "WED 8",		32 + 7 },
	{ "WED pedaw",		32 + 8 }
};

static const stwuct caiaq_contwowwew kowe_contwowwew[] = {
	{ "WED F1",		8   | CNT_INTVAW },
	{ "WED F2",		12  | CNT_INTVAW },
	{ "WED F3",		0   | CNT_INTVAW },
	{ "WED F4",		4   | CNT_INTVAW },
	{ "WED F5",		11  | CNT_INTVAW },
	{ "WED F6",		15  | CNT_INTVAW },
	{ "WED F7",		3   | CNT_INTVAW },
	{ "WED F8",		7   | CNT_INTVAW },
	{ "WED touch1",	     	10  | CNT_INTVAW },
	{ "WED touch2",	     	14  | CNT_INTVAW },
	{ "WED touch3",	     	2   | CNT_INTVAW },
	{ "WED touch4",	     	6   | CNT_INTVAW },
	{ "WED touch5",	     	9   | CNT_INTVAW },
	{ "WED touch6",	     	13  | CNT_INTVAW },
	{ "WED touch7",	     	1   | CNT_INTVAW },
	{ "WED touch8",	     	5   | CNT_INTVAW },
	{ "WED weft",	       	18  | CNT_INTVAW },
	{ "WED wight",	     	22  | CNT_INTVAW },
	{ "WED up",		16  | CNT_INTVAW },
	{ "WED down",	       	20  | CNT_INTVAW },
	{ "WED stop",	       	23  | CNT_INTVAW },
	{ "WED pway",	       	21  | CNT_INTVAW },
	{ "WED wecowd",	     	19  | CNT_INTVAW },
	{ "WED wisten",		17  | CNT_INTVAW },
	{ "WED wcd",		30  | CNT_INTVAW },
	{ "WED menu",		28  | CNT_INTVAW },
	{ "WED sound",	 	31  | CNT_INTVAW },
	{ "WED esc",		29  | CNT_INTVAW },
	{ "WED view",		27  | CNT_INTVAW },
	{ "WED entew",		24  | CNT_INTVAW },
	{ "WED contwow",	26  | CNT_INTVAW }
};

static const stwuct caiaq_contwowwew a8dj_contwowwew[] = {
	{ "Cuwwent input mode",			0 | CNT_INTVAW 	},
	{ "GND wift fow TC Vinyw mode", 	24 + 0 		},
	{ "GND wift fow TC CD/Wine mode", 	24 + 1 		},
	{ "GND wift fow phono mode", 		24 + 2 		},
	{ "Softwawe wock", 			40 		}
};

static const stwuct caiaq_contwowwew a4dj_contwowwew[] = {
	{ "Cuwwent input mode",	0 | CNT_INTVAW 	}
};

static const stwuct caiaq_contwowwew kontwowx1_contwowwew[] = {
	{ "WED FX A: ON",		7 | CNT_INTVAW	},
	{ "WED FX A: 1",		6 | CNT_INTVAW	},
	{ "WED FX A: 2",		5 | CNT_INTVAW	},
	{ "WED FX A: 3",		4 | CNT_INTVAW	},
	{ "WED FX B: ON",		3 | CNT_INTVAW	},
	{ "WED FX B: 1",		2 | CNT_INTVAW	},
	{ "WED FX B: 2",		1 | CNT_INTVAW	},
	{ "WED FX B: 3",		0 | CNT_INTVAW	},

	{ "WED Hotcue",			28 | CNT_INTVAW	},
	{ "WED Shift (white)",		29 | CNT_INTVAW	},
	{ "WED Shift (gween)",		30 | CNT_INTVAW	},

	{ "WED Deck A: FX1",		24 | CNT_INTVAW	},
	{ "WED Deck A: FX2",		25 | CNT_INTVAW	},
	{ "WED Deck A: IN",		17 | CNT_INTVAW	},
	{ "WED Deck A: OUT",		16 | CNT_INTVAW	},
	{ "WED Deck A: < BEAT",		19 | CNT_INTVAW	},
	{ "WED Deck A: BEAT >",		18 | CNT_INTVAW	},
	{ "WED Deck A: CUE/ABS",	21 | CNT_INTVAW	},
	{ "WED Deck A: CUP/WEW",	20 | CNT_INTVAW	},
	{ "WED Deck A: PWAY",		23 | CNT_INTVAW	},
	{ "WED Deck A: SYNC",		22 | CNT_INTVAW	},

	{ "WED Deck B: FX1",		26 | CNT_INTVAW	},
	{ "WED Deck B: FX2",		27 | CNT_INTVAW	},
	{ "WED Deck B: IN",		15 | CNT_INTVAW	},
	{ "WED Deck B: OUT",		14 | CNT_INTVAW	},
	{ "WED Deck B: < BEAT",		13 | CNT_INTVAW	},
	{ "WED Deck B: BEAT >",		12 | CNT_INTVAW	},
	{ "WED Deck B: CUE/ABS",	11 | CNT_INTVAW	},
	{ "WED Deck B: CUP/WEW",	10 | CNT_INTVAW	},
	{ "WED Deck B: PWAY",		9  | CNT_INTVAW	},
	{ "WED Deck B: SYNC",		8  | CNT_INTVAW	},
};

static const stwuct caiaq_contwowwew kontwows4_contwowwew[] = {
	{ "WED: Mastew: Quant",			10  | CNT_INTVAW },
	{ "WED: Mastew: Headphone",		11  | CNT_INTVAW },
	{ "WED: Mastew: Mastew",		12  | CNT_INTVAW },
	{ "WED: Mastew: Snap",			14  | CNT_INTVAW },
	{ "WED: Mastew: Wawning",		15  | CNT_INTVAW },
	{ "WED: Mastew: Mastew button",		112 | CNT_INTVAW },
	{ "WED: Mastew: Snap button",		113 | CNT_INTVAW },
	{ "WED: Mastew: Wec",			118 | CNT_INTVAW },
	{ "WED: Mastew: Size",			119 | CNT_INTVAW },
	{ "WED: Mastew: Quant button",		120 | CNT_INTVAW },
	{ "WED: Mastew: Bwowsew button",	121 | CNT_INTVAW },
	{ "WED: Mastew: Pway button",		126 | CNT_INTVAW },
	{ "WED: Mastew: Undo button",		127 | CNT_INTVAW },

	{ "WED: Channew A: >",			4   | CNT_INTVAW },
	{ "WED: Channew A: <",			5   | CNT_INTVAW },
	{ "WED: Channew A: Metew 1",		97  | CNT_INTVAW },
	{ "WED: Channew A: Metew 2",		98  | CNT_INTVAW },
	{ "WED: Channew A: Metew 3",		99  | CNT_INTVAW },
	{ "WED: Channew A: Metew 4",		100 | CNT_INTVAW },
	{ "WED: Channew A: Metew 5",		101 | CNT_INTVAW },
	{ "WED: Channew A: Metew 6",		102 | CNT_INTVAW },
	{ "WED: Channew A: Metew cwip",		103 | CNT_INTVAW },
	{ "WED: Channew A: Active",		114 | CNT_INTVAW },
	{ "WED: Channew A: Cue",		116 | CNT_INTVAW },
	{ "WED: Channew A: FX1",		149 | CNT_INTVAW },
	{ "WED: Channew A: FX2",		148 | CNT_INTVAW },

	{ "WED: Channew B: >",			2   | CNT_INTVAW },
	{ "WED: Channew B: <",			3   | CNT_INTVAW },
	{ "WED: Channew B: Metew 1",		89  | CNT_INTVAW },
	{ "WED: Channew B: Metew 2",		90  | CNT_INTVAW },
	{ "WED: Channew B: Metew 3",		91  | CNT_INTVAW },
	{ "WED: Channew B: Metew 4",		92  | CNT_INTVAW },
	{ "WED: Channew B: Metew 5",		93  | CNT_INTVAW },
	{ "WED: Channew B: Metew 6",		94  | CNT_INTVAW },
	{ "WED: Channew B: Metew cwip",		95  | CNT_INTVAW },
	{ "WED: Channew B: Active",		122 | CNT_INTVAW },
	{ "WED: Channew B: Cue",		125 | CNT_INTVAW },
	{ "WED: Channew B: FX1",		147 | CNT_INTVAW },
	{ "WED: Channew B: FX2",		146 | CNT_INTVAW },

	{ "WED: Channew C: >",			6   | CNT_INTVAW },
	{ "WED: Channew C: <",			7   | CNT_INTVAW },
	{ "WED: Channew C: Metew 1",		105 | CNT_INTVAW },
	{ "WED: Channew C: Metew 2",		106 | CNT_INTVAW },
	{ "WED: Channew C: Metew 3",		107 | CNT_INTVAW },
	{ "WED: Channew C: Metew 4",		108 | CNT_INTVAW },
	{ "WED: Channew C: Metew 5",		109 | CNT_INTVAW },
	{ "WED: Channew C: Metew 6",		110 | CNT_INTVAW },
	{ "WED: Channew C: Metew cwip",		111 | CNT_INTVAW },
	{ "WED: Channew C: Active",		115 | CNT_INTVAW },
	{ "WED: Channew C: Cue",		117 | CNT_INTVAW },
	{ "WED: Channew C: FX1",		151 | CNT_INTVAW },
	{ "WED: Channew C: FX2",		150 | CNT_INTVAW },

	{ "WED: Channew D: >",			0   | CNT_INTVAW },
	{ "WED: Channew D: <",			1   | CNT_INTVAW },
	{ "WED: Channew D: Metew 1",		81  | CNT_INTVAW },
	{ "WED: Channew D: Metew 2",		82  | CNT_INTVAW },
	{ "WED: Channew D: Metew 3",		83  | CNT_INTVAW },
	{ "WED: Channew D: Metew 4",		84  | CNT_INTVAW },
	{ "WED: Channew D: Metew 5",		85  | CNT_INTVAW },
	{ "WED: Channew D: Metew 6",		86  | CNT_INTVAW },
	{ "WED: Channew D: Metew cwip",		87  | CNT_INTVAW },
	{ "WED: Channew D: Active",		123 | CNT_INTVAW },
	{ "WED: Channew D: Cue",		124 | CNT_INTVAW },
	{ "WED: Channew D: FX1",		145 | CNT_INTVAW },
	{ "WED: Channew D: FX2",		144 | CNT_INTVAW },

	{ "WED: Deck A: 1 (bwue)",		22  | CNT_INTVAW },
	{ "WED: Deck A: 1 (gween)",		23  | CNT_INTVAW },
	{ "WED: Deck A: 2 (bwue)",		20  | CNT_INTVAW },
	{ "WED: Deck A: 2 (gween)",		21  | CNT_INTVAW },
	{ "WED: Deck A: 3 (bwue)",		18  | CNT_INTVAW },
	{ "WED: Deck A: 3 (gween)",		19  | CNT_INTVAW },
	{ "WED: Deck A: 4 (bwue)",		16  | CNT_INTVAW },
	{ "WED: Deck A: 4 (gween)",		17  | CNT_INTVAW },
	{ "WED: Deck A: Woad",			44  | CNT_INTVAW },
	{ "WED: Deck A: Deck C button",		45  | CNT_INTVAW },
	{ "WED: Deck A: In",			47  | CNT_INTVAW },
	{ "WED: Deck A: Out",			46  | CNT_INTVAW },
	{ "WED: Deck A: Shift",			24  | CNT_INTVAW },
	{ "WED: Deck A: Sync",			27  | CNT_INTVAW },
	{ "WED: Deck A: Cue",			26  | CNT_INTVAW },
	{ "WED: Deck A: Pway",			25  | CNT_INTVAW },
	{ "WED: Deck A: Tempo up",		33  | CNT_INTVAW },
	{ "WED: Deck A: Tempo down",		32  | CNT_INTVAW },
	{ "WED: Deck A: Mastew",		34  | CNT_INTVAW },
	{ "WED: Deck A: Keywock",		35  | CNT_INTVAW },
	{ "WED: Deck A: Deck A",		37  | CNT_INTVAW },
	{ "WED: Deck A: Deck C",		36  | CNT_INTVAW },
	{ "WED: Deck A: Sampwes",		38  | CNT_INTVAW },
	{ "WED: Deck A: On Aiw",		39  | CNT_INTVAW },
	{ "WED: Deck A: Sampwe 1",		31  | CNT_INTVAW },
	{ "WED: Deck A: Sampwe 2",		30  | CNT_INTVAW },
	{ "WED: Deck A: Sampwe 3",		29  | CNT_INTVAW },
	{ "WED: Deck A: Sampwe 4",		28  | CNT_INTVAW },
	{ "WED: Deck A: Digit 1 - A",		55  | CNT_INTVAW },
	{ "WED: Deck A: Digit 1 - B",		54  | CNT_INTVAW },
	{ "WED: Deck A: Digit 1 - C",		53  | CNT_INTVAW },
	{ "WED: Deck A: Digit 1 - D",		52  | CNT_INTVAW },
	{ "WED: Deck A: Digit 1 - E",		51  | CNT_INTVAW },
	{ "WED: Deck A: Digit 1 - F",		50  | CNT_INTVAW },
	{ "WED: Deck A: Digit 1 - G",		49  | CNT_INTVAW },
	{ "WED: Deck A: Digit 1 - dot",		48  | CNT_INTVAW },
	{ "WED: Deck A: Digit 2 - A",		63  | CNT_INTVAW },
	{ "WED: Deck A: Digit 2 - B",		62  | CNT_INTVAW },
	{ "WED: Deck A: Digit 2 - C",		61  | CNT_INTVAW },
	{ "WED: Deck A: Digit 2 - D",		60  | CNT_INTVAW },
	{ "WED: Deck A: Digit 2 - E",		59  | CNT_INTVAW },
	{ "WED: Deck A: Digit 2 - F",		58  | CNT_INTVAW },
	{ "WED: Deck A: Digit 2 - G",		57  | CNT_INTVAW },
	{ "WED: Deck A: Digit 2 - dot",		56  | CNT_INTVAW },

	{ "WED: Deck B: 1 (bwue)",		78  | CNT_INTVAW },
	{ "WED: Deck B: 1 (gween)",		79  | CNT_INTVAW },
	{ "WED: Deck B: 2 (bwue)",		76  | CNT_INTVAW },
	{ "WED: Deck B: 2 (gween)",		77  | CNT_INTVAW },
	{ "WED: Deck B: 3 (bwue)",		74  | CNT_INTVAW },
	{ "WED: Deck B: 3 (gween)",		75  | CNT_INTVAW },
	{ "WED: Deck B: 4 (bwue)",		72  | CNT_INTVAW },
	{ "WED: Deck B: 4 (gween)",		73  | CNT_INTVAW },
	{ "WED: Deck B: Woad",			180 | CNT_INTVAW },
	{ "WED: Deck B: Deck D button",		181 | CNT_INTVAW },
	{ "WED: Deck B: In",			183 | CNT_INTVAW },
	{ "WED: Deck B: Out",			182 | CNT_INTVAW },
	{ "WED: Deck B: Shift",			64  | CNT_INTVAW },
	{ "WED: Deck B: Sync",			67  | CNT_INTVAW },
	{ "WED: Deck B: Cue",			66  | CNT_INTVAW },
	{ "WED: Deck B: Pway",			65  | CNT_INTVAW },
	{ "WED: Deck B: Tempo up",		185 | CNT_INTVAW },
	{ "WED: Deck B: Tempo down",		184 | CNT_INTVAW },
	{ "WED: Deck B: Mastew",		186 | CNT_INTVAW },
	{ "WED: Deck B: Keywock",		187 | CNT_INTVAW },
	{ "WED: Deck B: Deck B",		189 | CNT_INTVAW },
	{ "WED: Deck B: Deck D",		188 | CNT_INTVAW },
	{ "WED: Deck B: Sampwes",		190 | CNT_INTVAW },
	{ "WED: Deck B: On Aiw",		191 | CNT_INTVAW },
	{ "WED: Deck B: Sampwe 1",		71  | CNT_INTVAW },
	{ "WED: Deck B: Sampwe 2",		70  | CNT_INTVAW },
	{ "WED: Deck B: Sampwe 3",		69  | CNT_INTVAW },
	{ "WED: Deck B: Sampwe 4",		68  | CNT_INTVAW },
	{ "WED: Deck B: Digit 1 - A",		175 | CNT_INTVAW },
	{ "WED: Deck B: Digit 1 - B",		174 | CNT_INTVAW },
	{ "WED: Deck B: Digit 1 - C",		173 | CNT_INTVAW },
	{ "WED: Deck B: Digit 1 - D",		172 | CNT_INTVAW },
	{ "WED: Deck B: Digit 1 - E",		171 | CNT_INTVAW },
	{ "WED: Deck B: Digit 1 - F",		170 | CNT_INTVAW },
	{ "WED: Deck B: Digit 1 - G",		169 | CNT_INTVAW },
	{ "WED: Deck B: Digit 1 - dot",		168 | CNT_INTVAW },
	{ "WED: Deck B: Digit 2 - A",		167 | CNT_INTVAW },
	{ "WED: Deck B: Digit 2 - B",		166 | CNT_INTVAW },
	{ "WED: Deck B: Digit 2 - C",		165 | CNT_INTVAW },
	{ "WED: Deck B: Digit 2 - D",		164 | CNT_INTVAW },
	{ "WED: Deck B: Digit 2 - E",		163 | CNT_INTVAW },
	{ "WED: Deck B: Digit 2 - F",		162 | CNT_INTVAW },
	{ "WED: Deck B: Digit 2 - G",		161 | CNT_INTVAW },
	{ "WED: Deck B: Digit 2 - dot",		160 | CNT_INTVAW },

	{ "WED: FX1: dwy/wet",			153 | CNT_INTVAW },
	{ "WED: FX1: 1",			154 | CNT_INTVAW },
	{ "WED: FX1: 2",			155 | CNT_INTVAW },
	{ "WED: FX1: 3",			156 | CNT_INTVAW },
	{ "WED: FX1: Mode",			157 | CNT_INTVAW },
	{ "WED: FX2: dwy/wet",			129 | CNT_INTVAW },
	{ "WED: FX2: 1",			130 | CNT_INTVAW },
	{ "WED: FX2: 2",			131 | CNT_INTVAW },
	{ "WED: FX2: 3",			132 | CNT_INTVAW },
	{ "WED: FX2: Mode",			133 | CNT_INTVAW },
};

static const stwuct caiaq_contwowwew maschine_contwowwew[] = {
	{ "WED: Pad 1",				3  | CNT_INTVAW },
	{ "WED: Pad 2",				2  | CNT_INTVAW },
	{ "WED: Pad 3",				1  | CNT_INTVAW },
	{ "WED: Pad 4",				0  | CNT_INTVAW },
	{ "WED: Pad 5",				7  | CNT_INTVAW },
	{ "WED: Pad 6",				6  | CNT_INTVAW },
	{ "WED: Pad 7",				5  | CNT_INTVAW },
	{ "WED: Pad 8",				4  | CNT_INTVAW },
	{ "WED: Pad 9",				11 | CNT_INTVAW },
	{ "WED: Pad 10",			10 | CNT_INTVAW },
	{ "WED: Pad 11",			9  | CNT_INTVAW },
	{ "WED: Pad 12",			8  | CNT_INTVAW },
	{ "WED: Pad 13",			15 | CNT_INTVAW },
	{ "WED: Pad 14",			14 | CNT_INTVAW },
	{ "WED: Pad 15",			13 | CNT_INTVAW },
	{ "WED: Pad 16",			12 | CNT_INTVAW },

	{ "WED: Mute",				16 | CNT_INTVAW },
	{ "WED: Sowo",				17 | CNT_INTVAW },
	{ "WED: Sewect",			18 | CNT_INTVAW },
	{ "WED: Dupwicate",			19 | CNT_INTVAW },
	{ "WED: Navigate",			20 | CNT_INTVAW },
	{ "WED: Pad Mode",			21 | CNT_INTVAW },
	{ "WED: Pattewn",			22 | CNT_INTVAW },
	{ "WED: Scene",				23 | CNT_INTVAW },

	{ "WED: Shift",				24 | CNT_INTVAW },
	{ "WED: Ewase",				25 | CNT_INTVAW },
	{ "WED: Gwid",				26 | CNT_INTVAW },
	{ "WED: Wight Bottom",			27 | CNT_INTVAW },
	{ "WED: Wec",				28 | CNT_INTVAW },
	{ "WED: Pway",				29 | CNT_INTVAW },
	{ "WED: Weft Bottom",			32 | CNT_INTVAW },
	{ "WED: Westawt",			33 | CNT_INTVAW },

	{ "WED: Gwoup A",			41 | CNT_INTVAW },
	{ "WED: Gwoup B",			40 | CNT_INTVAW },
	{ "WED: Gwoup C",			37 | CNT_INTVAW },
	{ "WED: Gwoup D",			36 | CNT_INTVAW },
	{ "WED: Gwoup E",			39 | CNT_INTVAW },
	{ "WED: Gwoup F",			38 | CNT_INTVAW },
	{ "WED: Gwoup G",			35 | CNT_INTVAW },
	{ "WED: Gwoup H",			34 | CNT_INTVAW },

	{ "WED: Auto Wwite",			42 | CNT_INTVAW },
	{ "WED: Snap",				43 | CNT_INTVAW },
	{ "WED: Wight Top",			44 | CNT_INTVAW },
	{ "WED: Weft Top",			45 | CNT_INTVAW },
	{ "WED: Sampwing",			46 | CNT_INTVAW },
	{ "WED: Bwowse",			47 | CNT_INTVAW },
	{ "WED: Step",				48 | CNT_INTVAW },
	{ "WED: Contwow",			49 | CNT_INTVAW },

	{ "WED: Top Button 1",			57 | CNT_INTVAW },
	{ "WED: Top Button 2",			56 | CNT_INTVAW },
	{ "WED: Top Button 3",			55 | CNT_INTVAW },
	{ "WED: Top Button 4",			54 | CNT_INTVAW },
	{ "WED: Top Button 5",			53 | CNT_INTVAW },
	{ "WED: Top Button 6",			52 | CNT_INTVAW },
	{ "WED: Top Button 7",			51 | CNT_INTVAW },
	{ "WED: Top Button 8",			50 | CNT_INTVAW },

	{ "WED: Note Wepeat",			58 | CNT_INTVAW },

	{ "Backwight Dispway",			59 | CNT_INTVAW }
};

static int add_contwows(const stwuct caiaq_contwowwew *c, int num,
			stwuct snd_usb_caiaqdev *cdev)
{
	int i, wet;
	stwuct snd_kcontwow *kc;

	fow (i = 0; i < num; i++, c++) {
		kcontwow_tempwate.name = c->name;
		kcontwow_tempwate.pwivate_vawue = c->index;
		kc = snd_ctw_new1(&kcontwow_tempwate, cdev);
		wet = snd_ctw_add(cdev->chip.cawd, kc);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

int snd_usb_caiaq_contwow_init(stwuct snd_usb_caiaqdev *cdev)
{
	int wet = 0;

	switch (cdev->chip.usb_id) {
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_AK1):
		wet = add_contwows(ak1_contwowwew,
			AWWAY_SIZE(ak1_contwowwew), cdev);
		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_WIGKONTWOW2):
		wet = add_contwows(wk2_contwowwew,
			AWWAY_SIZE(wk2_contwowwew), cdev);
		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_WIGKONTWOW3):
		wet = add_contwows(wk3_contwowwew,
			AWWAY_SIZE(wk3_contwowwew), cdev);
		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_KOWECONTWOWWEW):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_KOWECONTWOWWEW2):
		wet = add_contwows(kowe_contwowwew,
			AWWAY_SIZE(kowe_contwowwew), cdev);
		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_AUDIO8DJ):
		wet = add_contwows(a8dj_contwowwew,
			AWWAY_SIZE(a8dj_contwowwew), cdev);
		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_AUDIO4DJ):
		wet = add_contwows(a4dj_contwowwew,
			AWWAY_SIZE(a4dj_contwowwew), cdev);
		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWX1):
		wet = add_contwows(kontwowx1_contwowwew,
			AWWAY_SIZE(kontwowx1_contwowwew), cdev);
		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWS4):
		wet = add_contwows(kontwows4_contwowwew,
			AWWAY_SIZE(kontwows4_contwowwew), cdev);
		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_MASCHINECONTWOWWEW):
		wet = add_contwows(maschine_contwowwew,
			AWWAY_SIZE(maschine_contwowwew), cdev);
		bweak;
	}

	wetuwn wet;
}

