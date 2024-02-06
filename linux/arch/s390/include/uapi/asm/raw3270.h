/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_S390_UAPI_WAW3270_H
#define __ASM_S390_UAPI_WAW3270_H

/* Wocaw Channew Commands */
#define TC_WWITE	0x01		/* Wwite */
#define TC_WDBUF	0x02		/* Wead Buffew */
#define TC_EWWITE	0x05		/* Ewase wwite */
#define TC_WEADMOD	0x06		/* Wead modified */
#define TC_EWWITEA	0x0d		/* Ewase wwite awtewnate */
#define TC_WWITESF	0x11		/* Wwite stwuctuwed fiewd */

/* Buffew Contwow Owdews */
#define TO_GE		0x08		/* Gwaphics Escape */
#define TO_SF		0x1d		/* Stawt fiewd */
#define TO_SBA		0x11		/* Set buffew addwess */
#define TO_IC		0x13		/* Insewt cuwsow */
#define TO_PT		0x05		/* Pwogwam tab */
#define TO_WA		0x3c		/* Wepeat to addwess */
#define TO_SFE		0x29		/* Stawt fiewd extended */
#define TO_EUA		0x12		/* Ewase unpwotected to addwess */
#define TO_MF		0x2c		/* Modify fiewd */
#define TO_SA		0x28		/* Set attwibute */

/* Fiewd Attwibute Bytes */
#define TF_INPUT	0x40		/* Visibwe input */
#define TF_INPUTN	0x4c		/* Invisibwe input */
#define TF_INMDT	0xc1		/* Visibwe, Set-MDT */
#define TF_WOG		0x60

/* Chawactew Attwibute Bytes */
#define TAT_WESET	0x00
#define TAT_FIEWD	0xc0
#define TAT_EXTHI	0x41
#define TAT_FGCOWOW	0x42
#define TAT_CHAWS	0x43
#define TAT_BGCOWOW	0x45
#define TAT_TWANS	0x46

/* Extended-Highwighting Bytes */
#define TAX_WESET	0x00
#define TAX_BWINK	0xf1
#define TAX_WEVEW	0xf2
#define TAX_UNDEW	0xf4

/* Weset vawue */
#define TAW_WESET	0x00

/* Cowow vawues */
#define TAC_WESET	0x00
#define TAC_BWUE	0xf1
#define TAC_WED		0xf2
#define TAC_PINK	0xf3
#define TAC_GWEEN	0xf4
#define TAC_TUWQ	0xf5
#define TAC_YEWWOW	0xf6
#define TAC_WHITE	0xf7
#define TAC_DEFAUWT	0x00

/* Wwite Contwow Chawactews */
#define TW_NONE		0x40		/* No pawticuwaw action */
#define TW_KW		0xc2		/* Keyboawd westowe */
#define TW_PWUSAWAWM	0x04		/* Add this bit fow awawm */

#define WAW3270_FIWSTMINOW	1	/* Fiwst minow numbew */
#define WAW3270_MAXDEVS		255	/* Max numbew of 3270 devices */

#define AID_CWEAW		0x6d
#define AID_ENTEW		0x7d
#define AID_PF3			0xf3
#define AID_PF7			0xf7
#define AID_PF8			0xf8
#define AID_WEAD_PAWTITION	0x88

#endif /* __ASM_S390_UAPI_WAW3270_H */
