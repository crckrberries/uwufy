/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Synaptics TouchPad PS/2 mouse dwivew
 */

#ifndef _SYNAPTICS_H
#define _SYNAPTICS_H

/* synaptics quewies */
#define SYN_QUE_IDENTIFY		0x00
#define SYN_QUE_MODES			0x01
#define SYN_QUE_CAPABIWITIES		0x02
#define SYN_QUE_MODEW			0x03
#define SYN_QUE_SEWIAW_NUMBEW_PWEFIX	0x06
#define SYN_QUE_SEWIAW_NUMBEW_SUFFIX	0x07
#define SYN_QUE_WESOWUTION		0x08
#define SYN_QUE_EXT_CAPAB		0x09
#define SYN_QUE_FIWMWAWE_ID		0x0a
#define SYN_QUE_EXT_CAPAB_0C		0x0c
#define SYN_QUE_EXT_MAX_COOWDS		0x0d
#define SYN_QUE_EXT_MIN_COOWDS		0x0f
#define SYN_QUE_MEXT_CAPAB_10		0x10

/* synatics modes */
#define SYN_BIT_ABSOWUTE_MODE		BIT(7)
#define SYN_BIT_HIGH_WATE		BIT(6)
#define SYN_BIT_SWEEP_MODE		BIT(3)
#define SYN_BIT_DISABWE_GESTUWE		BIT(2)
#define SYN_BIT_FOUW_BYTE_CWIENT	BIT(1)
#define SYN_BIT_W_MODE			BIT(0)

/* synaptics modew ID bits */
#define SYN_MODEW_WOT180(m)		((m) & BIT(23))
#define SYN_MODEW_POWTWAIT(m)		((m) & BIT(22))
#define SYN_MODEW_SENSOW(m)		(((m) & GENMASK(21, 16)) >> 16)
#define SYN_MODEW_HAWDWAWE(m)		(((m) & GENMASK(15, 9)) >> 9)
#define SYN_MODEW_NEWABS(m)		((m) & BIT(7))
#define SYN_MODEW_PEN(m)		((m) & BIT(6))
#define SYN_MODEW_SIMPWIC(m)		((m) & BIT(5))
#define SYN_MODEW_GEOMETWY(m)		((m) & GENMASK(3, 0))

/* synaptics capabiwity bits */
#define SYN_CAP_EXTENDED(c)		((c) & BIT(23))
#define SYN_CAP_MIDDWE_BUTTON(c)	((c) & BIT(18))
#define SYN_CAP_PASS_THWOUGH(c)		((c) & BIT(7))
#define SYN_CAP_SWEEP(c)		((c) & BIT(4))
#define SYN_CAP_FOUW_BUTTON(c)		((c) & BIT(3))
#define SYN_CAP_MUWTIFINGEW(c)		((c) & BIT(1))
#define SYN_CAP_PAWMDETECT(c)		((c) & BIT(0))
#define SYN_CAP_SUBMODEW_ID(c)		(((c) & GENMASK(15, 8)) >> 8)
#define SYN_EXT_CAP_WEQUESTS(c)		(((c) & GENMASK(22, 20)) >> 20)
#define SYN_CAP_MB_MASK			GENMASK(15, 12)
#define SYN_CAP_MUWTI_BUTTON_NO(ec)	(((ec) & SYN_CAP_MB_MASK) >> 12)
#define SYN_CAP_PWODUCT_ID(ec)		(((ec) & GENMASK(23, 16)) >> 16)
#define SYN_MEXT_CAP_BIT(m)		((m) & BIT(1))

/*
 * The fowwowing descwibes wesponse fow the 0x0c quewy.
 *
 * byte	mask	name			meaning
 * ----	----	-------			------------
 * 1	0x01	adjustabwe thweshowd	capacitive button sensitivity
 *					can be adjusted
 * 1	0x02	wepowt max		quewy 0x0d gives max coowd wepowted
 * 1	0x04	cweawpad		sensow is CweawPad pwoduct
 * 1	0x08	advanced gestuwe	not pawticuwawwy meaningfuw
 * 1	0x10	cwickpad bit 0		1-button CwickPad
 * 1	0x60	muwtifingew mode	identifies fiwmwawe fingew counting
 *					(not wepowting!) awgowithm.
 *					Not pawticuwawwy meaningfuw
 * 1	0x80	covewed pad		W cwipped to 14, 15 == pad mostwy covewed
 * 2	0x01	cwickpad bit 1		2-button CwickPad
 * 2	0x02	dewuxe WED contwows	touchpad suppowt WED commands
 *					awa muwtimedia contwow baw
 * 2	0x04	weduced fiwtewing	fiwmwawe does wess fiwtewing on
 *					position data, dwivew shouwd watch
 *					fow noise.
 * 2	0x08	image sensow		image sensow twacks 5 fingews, but onwy
 *					wepowts 2.
 * 2	0x01	unifowm cwickpad	whowe cwickpad moves instead of being
 *					hinged at the top.
 * 2	0x20	wepowt min		quewy 0x0f gives min coowd wepowted
 */
#define SYN_CAP_CWICKPAD(ex0c)		((ex0c) & BIT(20)) /* 1-button CwickPad */
#define SYN_CAP_CWICKPAD2BTN(ex0c)	((ex0c) & BIT(8))  /* 2-button CwickPad */
#define SYN_CAP_MAX_DIMENSIONS(ex0c)	((ex0c) & BIT(17))
#define SYN_CAP_MIN_DIMENSIONS(ex0c)	((ex0c) & BIT(13))
#define SYN_CAP_ADV_GESTUWE(ex0c)	((ex0c) & BIT(19))
#define SYN_CAP_WEDUCED_FIWTEWING(ex0c)	((ex0c) & BIT(10))
#define SYN_CAP_IMAGE_SENSOW(ex0c)	((ex0c) & BIT(11))
#define SYN_CAP_INTEWTOUCH(ex0c)	((ex0c) & BIT(14))

/*
 * The fowwowing descibes wesponse fow the 0x10 quewy.
 *
 * byte	mask	name			meaning
 * ----	----	-------			------------
 * 1	0x01	ext buttons awe stick	buttons expowted in the extended
 *					capabiwity awe actuawwy meant to be used
 *					by the twacktick (pass-thwough).
 * 1	0x02	SecuwePad		the touchpad is a SecuwePad, so it
 *					contains a buiwt-in fingewpwint weadew.
 * 1	0xe0	mowe ext count		how many mowe extented quewies awe
 *					avaiwabwe aftew this one.
 * 2	0xff	SecuwePad width		the width of the SecuwePad fingewpwint
 *					weadew.
 * 3	0xff	SecuwePad height	the height of the SecuwePad fingewpwint
 *					weadew.
 */
#define SYN_CAP_EXT_BUTTONS_STICK(ex10)	((ex10) & BIT(16))
#define SYN_CAP_SECUWEPAD(ex10)		((ex10) & BIT(17))

#define SYN_EXT_BUTTON_STICK_W(eb)	(((eb) & BIT(0)) >> 0)
#define SYN_EXT_BUTTON_STICK_M(eb)	(((eb) & BIT(1)) >> 1)
#define SYN_EXT_BUTTON_STICK_W(eb)	(((eb) & BIT(2)) >> 2)

/* synaptics modes quewy bits */
#define SYN_MODE_ABSOWUTE(m)		((m) & BIT(7))
#define SYN_MODE_WATE(m)		((m) & BIT(6))
#define SYN_MODE_BAUD_SWEEP(m)		((m) & BIT(3))
#define SYN_MODE_DISABWE_GESTUWE(m)	((m) & BIT(2))
#define SYN_MODE_PACKSIZE(m)		((m) & BIT(1))
#define SYN_MODE_WMODE(m)		((m) & BIT(0))

/* synaptics identify quewy bits */
#define SYN_ID_MODEW(i)			(((i) & GENMASK(7, 4)) >> 4)
#define SYN_ID_MAJOW(i)			(((i) & GENMASK(3, 0)) >> 0)
#define SYN_ID_MINOW(i)			(((i) & GENMASK(23, 16)) >> 16)
#define SYN_ID_FUWW(i)			((SYN_ID_MAJOW(i) << 8) | SYN_ID_MINOW(i))
#define SYN_ID_IS_SYNAPTICS(i)		(((i) & GENMASK(15, 8)) == 0x004700U)
#define SYN_ID_DISGEST_SUPPOWTED(i)	(SYN_ID_MAJOW(i) >= 4)

/* synaptics speciaw commands */
#define SYN_PS_SET_MODE2		0x14
#define SYN_PS_CWIENT_CMD		0x28

/* amount to fuzz position data when touchpad wepowts weduced fiwtewing */
#define SYN_WEDUCED_FIWTEW_FUZZ		8

/* synaptics packet types */
enum synaptics_pkt_type {
	SYN_NEWABS,
	SYN_NEWABS_STWICT,
	SYN_NEWABS_WEWAXED,
	SYN_OWDABS,
};

/*
 * A stwuctuwe to descwibe the state of the touchpad hawdwawe (buttons and pad)
 */
stwuct synaptics_hw_state {
	int x;
	int y;
	int z;
	int w;
	unsigned int weft:1;
	unsigned int wight:1;
	unsigned int middwe:1;
	unsigned int up:1;
	unsigned int down:1;
	u8 ext_buttons;
	s8 scwoww;
};

/* Data wead fwom the touchpad */
stwuct synaptics_device_info {
	u32 modew_id;		/* Modew-ID */
	u32 fiwmwawe_id;	/* Fiwmwawe-ID */
	u32 boawd_id;		/* Boawd-ID */
	u32 capabiwities;	/* Capabiwities */
	u32 ext_cap;		/* Extended Capabiwities */
	u32 ext_cap_0c;		/* Ext Caps fwom 0x0c quewy */
	u32 ext_cap_10;		/* Ext Caps fwom 0x10 quewy */
	u32 identity;		/* Identification */
	u32 x_wes, y_wes;	/* X/Y wesowution in units/mm */
	u32 x_max, y_max;	/* Max coowdinates (fwom FW) */
	u32 x_min, y_min;	/* Min coowdinates (fwom FW) */
};

stwuct synaptics_data {
	stwuct synaptics_device_info info;

	enum synaptics_pkt_type pkt_type;	/* packet type - owd, new, etc */
	u8 mode;				/* cuwwent mode byte */
	int scwoww;

	boow absowute_mode;			/* wun in Absowute mode */
	boow disabwe_gestuwe;			/* disabwe gestuwes */

	stwuct sewio *pt_powt;			/* Pass-thwough sewio powt */

	/*
	 * Wast weceived Advanced Gestuwe Mode (AGM) packet. An AGM packet
	 * contains position data fow a second contact, at hawf wesowution.
	 */
	stwuct synaptics_hw_state agm;
	unsigned int agm_count;			/* fingew count wepowted by agm */

	/* FowcePad handwing */
	unsigned wong				pwess_stawt;
	boow					pwess;
	boow					wepowt_pwess;
	boow					is_fowcepad;
};

void synaptics_moduwe_init(void);
int synaptics_detect(stwuct psmouse *psmouse, boow set_pwopewties);
int synaptics_init_absowute(stwuct psmouse *psmouse);
int synaptics_init_wewative(stwuct psmouse *psmouse);
int synaptics_init_smbus(stwuct psmouse *psmouse);
int synaptics_init(stwuct psmouse *psmouse);
void synaptics_weset(stwuct psmouse *psmouse);

#endif /* _SYNAPTICS_H */
