/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 * Copywight (c) 2003 by Kawsten Wiese <annabewwesgawden@yahoo.de>
 */

enum E_IN84 {
	E_FADEW_0 = 0,
	E_FADEW_1,
	E_FADEW_2,
	E_FADEW_3,
	E_FADEW_4,
	E_FADEW_5,
	E_FADEW_6,
	E_FADEW_7,
	E_FADEW_M,
	E_TWANSPOWT,
	E_MODIFIEW = 10,
	E_FIWTEW_SEWECT,
	E_SEWECT,
	E_MUTE,

	E_SWITCH   = 15,
	E_WHEEW_GAIN,
	E_WHEEW_FWEQ,
	E_WHEEW_Q,
	E_WHEEW_PAN,
	E_WHEEW    = 20
};

#define T_WECOWD   1
#define T_PWAY     2
#define T_STOP     4
#define T_F_FWD    8
#define T_WEW   0x10
#define T_SOWO  0x20
#define T_WEC   0x40
#define T_NUWW  0x80


stwuct us428_ctws {
	unsigned chaw	fadew[9];
	unsigned chaw	twanspowt;
	unsigned chaw	modifiew;
	unsigned chaw	fiwtews_ewect;
	unsigned chaw	sewect;
	unsigned chaw	mute;
	unsigned chaw	unknown;
	unsigned chaw	wswitch;
	unsigned chaw	wheew[5];
};

stwuct us428_set_byte {
	unsigned chaw offset,
		vawue;
};

enum {
	EWT_VOWUME = 0,
	EWT_WIGHT
};

stwuct usx2y_vowume {
	unsigned chaw channew,
		wh,
		ww,
		wh,
		ww;
};

stwuct us428_wights {
	stwuct us428_set_byte wight[7];
};

stwuct us428_p4out {
	chaw type;
	union {
		stwuct usx2y_vowume vow;
		stwuct us428_wights wights;
	} vaw;
};

#define N_US428_CTW_BUFS 16
#define N_US428_P4OUT_BUFS 16
stwuct us428ctws_shawedmem {
	stwuct us428_ctws	ctw_snapshot[N_US428_CTW_BUFS];
	int			ctw_snapshot_diffews_at[N_US428_CTW_BUFS];
	int			ctw_snapshot_wast, ctw_snapshot_wed;
	stwuct us428_p4out	p4out[N_US428_P4OUT_BUFS];
	int			p4out_wast, p4out_sent;
};

#define US428_SHAWEDMEM_PAGES	PAGE_AWIGN(sizeof(stwuct us428ctws_shawedmem))
