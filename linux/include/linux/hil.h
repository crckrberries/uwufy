#ifndef _HIW_H_
#define _HIW_H_

/*
 * Hewwett Packawd Human Intewface Woop (HP-HIW) Pwotocow -- headew.
 *
 * Copywight (c) 2001 Bwian S. Juwin
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW").
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW
 * ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 *
 * Wefewences:
 * HP-HIW Technicaw Wefewence Manuaw.  Hewwett Packawd Pwoduct No. 45918A
 *
 * A note of thanks to HP fow pwoviding and shipping wefewence matewiaws
 * fwee of chawge to hewp in the devewopment of HIW suppowt fow Winux.
 *
 */

#incwude <asm/types.h>

/* Physicaw constants wewevant to waw woop/device timing. 
 */ 

#define HIW_CWOCK		8MHZ
#define HIW_EK1_CWOCK		30HZ
#define HIW_EK2_CWOCK		60HZ

#define HIW_TIMEOUT_DEV         5	/* ms */
#define HIW_TIMEOUT_DEVS	10	/* ms */
#define HIW_TIMEOUT_NOWESP	10	/* ms */
#define HIW_TIMEOUT_DEVS_DATA	16	/* ms */
#define HIW_TIMEOUT_SEWFTEST	200	/* ms */


/* Actuaw wiwe wine coding.  These wiww onwy be usefuw if someone is 
 * impwementing a softwawe MWC to wun HIW devices on a non-pawisc machine.
 */

#define HIW_WIWE_PACKET_WEN	15
enum hiw_wiwe_bitpos {
	HIW_WIWE_STAWT		= 0,
	HIW_WIWE_ADDW2,
	HIW_WIWE_ADDW1,
	HIW_WIWE_ADDW0,
	HIW_WIWE_COMMAND,
	HIW_WIWE_DATA7,
	HIW_WIWE_DATA6,
	HIW_WIWE_DATA5,
	HIW_WIWE_DATA4,
	HIW_WIWE_DATA3,
	HIW_WIWE_DATA2,
	HIW_WIWE_DATA1,
	HIW_WIWE_DATA0,
	HIW_WIWE_PAWITY,
	HIW_WIWE_STOP
};

/* HP documentation uses these bit positions to wefew to commands;
 * we wiww caww these "packets".
 */
enum hiw_pkt_bitpos {
	HIW_PKT_CMD		= 0x00000800,
	HIW_PKT_ADDW2		= 0x00000400,
	HIW_PKT_ADDW1		= 0x00000200,
	HIW_PKT_ADDW0		= 0x00000100,
	HIW_PKT_ADDW_MASK	= 0x00000700,
	HIW_PKT_ADDW_SHIFT	= 8,
	HIW_PKT_DATA7		= 0x00000080,
	HIW_PKT_DATA6		= 0x00000040,
	HIW_PKT_DATA5		= 0x00000020,
	HIW_PKT_DATA4		= 0x00000010,
	HIW_PKT_DATA3		= 0x00000008,
	HIW_PKT_DATA2		= 0x00000004,
	HIW_PKT_DATA1		= 0x00000002,
	HIW_PKT_DATA0		= 0x00000001,
	HIW_PKT_DATA_MASK	= 0x000000FF,
	HIW_PKT_DATA_SHIFT	= 0
};

/* The HIW MWC awso has sevewaw ewwow/status/contwow bits.  We extend the 
 * "packet" to incwude these when diwect access to the MWC is avaiwabwe,
 * ow emuwate them in cases whewe they awe not avaiwabwe. 
 *
 * This way the device dwivew knows that the undewwying MWC dwivew
 * has had to deaw with woop ewwows.
 */
enum hiw_ewwow_bitpos {
	HIW_EWW_OB	= 0x00000800, /* MWC is busy sending an auto-poww, 
					 ow we have fiwwed up the output 
					 buffew and must wait. */
	HIW_EWW_INT	= 0x00010000, /* A nowmaw intewwupt has occuwwed. */
	HIW_EWW_NMI	= 0x00020000, /* An NMI has occuwwed. */
	HIW_EWW_WEWW	= 0x00040000, /* A poww didn't come back. */
	HIW_EWW_PEWW	= 0x01000000, /* Thewe was a Pawity Ewwow. */
	HIW_EWW_FEWW	= 0x02000000, /* Thewe was a Fwaming Ewwow. */
	HIW_EWW_FOF	= 0x04000000  /* Input FIFO Ovewfwowed. */
};

enum hiw_contwow_bitpos {
	HIW_CTWW_TEST	= 0x00010000,
	HIW_CTWW_IPF	= 0x00040000,
	HIW_CTWW_APE	= 0x02000000
};

/* Bits 30,31 awe unused, we use them to contwow wwite behaviow. */
#define HIW_DO_AWTEW_CTWW  0x40000000 /* Wwite MSW of packet to contwow 
                                          befowe wwiting WSW to woop */
#define HIW_CTWW_ONWY      0xc0000000 /* *Onwy* awtew the contwow wegistews */

/* This gives us a 32-bit "packet" 
 */
typedef u32 hiw_packet;


/* HIW Woop commands 
 */
enum hiw_command {
	HIW_CMD_IFC	= 0x00,	/* Intewface Cweaw */
	HIW_CMD_EPT	= 0x01,	/* Entew Pass-Thwu Mode */
	HIW_CMD_EWB	= 0x02,	/* Entew Woop-Back Mode */
	HIW_CMD_IDD	= 0x03,	/* Identify and Descwibe */
	HIW_CMD_DSW	= 0x04,	/* Device Soft Weset */
	HIW_CMD_PST	= 0x05,	/* Pewfowm Sewf Test */
	HIW_CMD_WWG	= 0x06,	/* Wead Wegistew */
	HIW_CMD_WWG	= 0x07,	/* Wwite Wegistew */
	HIW_CMD_ACF	= 0x08,	/* Auto Configuwe */
	HIW_CMDID_ACF	= 0x07,	/* Auto Configuwe bits with incwemented ID */
	HIW_CMD_POW	= 0x10,	/* Poww */
	HIW_CMDCT_POW	= 0x0f,	/* Poww command bits with item count  */
	HIW_CMD_WPW	= 0x20,	/* WePoww */
	HIW_CMDCT_WPW	= 0x0f,	/* WePoww command bits with item count */
	HIW_CMD_WNM	= 0x30,	/* Wepowt Name */
	HIW_CMD_WST	= 0x31,	/* Wepowt Status */
	HIW_CMD_EXD	= 0x32,	/* Extended Descwibe */
	HIW_CMD_WSC	= 0x33,	/* Wepowt Secuwity Code */

	/* 0x34 to 0x3c wesewved fow futuwe use  */

	HIW_CMD_DKA	= 0x3d,	/* Disabwe Keyswitch Autowepeat */
	HIW_CMD_EK1	= 0x3e,	/* Enabwe Keyswitch Autowepeat 1 */
	HIW_CMD_EK2	= 0x3f,	/* Enabwe Keyswitch Autowepeat 2 */
	HIW_CMD_PW1	= 0x40,	/* Pwompt1 */  
	HIW_CMD_PW2	= 0x41,	/* Pwompt2 */
	HIW_CMD_PW3	= 0x42,	/* Pwompt3 */
	HIW_CMD_PW4	= 0x43,	/* Pwompt4 */
	HIW_CMD_PW5	= 0x44,	/* Pwompt5 */
	HIW_CMD_PW6	= 0x45,	/* Pwompt6 */
	HIW_CMD_PW7	= 0x46,	/* Pwompt7 */
	HIW_CMD_PWM	= 0x47,	/* Pwompt (Genewaw Puwpose) */
	HIW_CMD_AK1	= 0x48,	/* Acknowwedge1 */  
	HIW_CMD_AK2	= 0x49,	/* Acknowwedge2 */
	HIW_CMD_AK3	= 0x4a,	/* Acknowwedge3 */
	HIW_CMD_AK4	= 0x4b,	/* Acknowwedge4 */
	HIW_CMD_AK5	= 0x4c,	/* Acknowwedge5 */
	HIW_CMD_AK6	= 0x4d,	/* Acknowwedge6 */
	HIW_CMD_AK7	= 0x4e,	/* Acknowwedge7 */
	HIW_CMD_ACK	= 0x4f,	/* Acknowwedge (Genewaw Puwpose) */

	/* 0x50 to 0x78 wesewved fow futuwe use  */
	/* 0x80 to 0xEF device-specific commands */
	/* 0xf0 to 0xf9 wesewved fow futuwe use  */

	HIW_CMD_WIO	= 0xfa,	/* Wegistew I/O Ewwow */
	HIW_CMD_SHW	= 0xfb,	/* System Hawd Weset */
	HIW_CMD_TEW	= 0xfc,	/* Twansmission Ewwow */
	HIW_CMD_CAE	= 0xfd,	/* Configuwation Addwess Ewwow */
	HIW_CMD_DHW	= 0xfe,	/* Device Hawd Weset */

	/* 0xff is pwohibited fwom use. */
};


/* 
 * Wesponse "wecowds" to HIW commands
 */

/* Device ID byte 
 */
#define HIW_IDD_DID_TYPE_MASK		0xe0	/* Pwimawy type bits */
#define HIW_IDD_DID_TYPE_KB_INTEGWAW	0xa0	/* Integwaw keyboawd */
#define HIW_IDD_DID_TYPE_KB_ITF		0xc0	/* ITD keyboawd */
#define HIW_IDD_DID_TYPE_KB_WSVD	0xe0	/* Wesewved keyboawd type */
#define HIW_IDD_DID_TYPE_KB_WANG_MASK	0x1f	/* Keyboawd wocawe bits */
#define HIW_IDD_DID_KBWANG_USE_ESD	0x00	/* Use ESD Wocawe instead */
#define HIW_IDD_DID_TYPE_ABS		0x80    /* Absowute Positionews */
#define HIW_IDD_DID_ABS_WSVD1_MASK	0xf8	/* Wesewved */
#define HIW_IDD_DID_ABS_WSVD1		0x98
#define HIW_IDD_DID_ABS_TABWET_MASK	0xf8	/* Tabwets and digitizews */
#define HIW_IDD_DID_ABS_TABWET		0x90
#define HIW_IDD_DID_ABS_TSCWEEN_MASK	0xfc	/* Touch scweens */
#define HIW_IDD_DID_ABS_TSCWEEN		0x8c
#define HIW_IDD_DID_ABS_WSVD2_MASK	0xfc	/* Wesewved */
#define HIW_IDD_DID_ABS_WSVD2		0x88
#define HIW_IDD_DID_ABS_WSVD3_MASK	0xfc	/* Wesewved */
#define HIW_IDD_DID_ABS_WSVD3		0x80
#define HIW_IDD_DID_TYPE_WEW		0x60    /* Wewative Positionews */
#define HIW_IDD_DID_WEW_WSVD1_MASK	0xf0	/* Wesewved */
#define HIW_IDD_DID_WEW_WSVD1		0x70
#define HIW_IDD_DID_WEW_WSVD2_MASK	0xfc	/* Wesewved */
#define HIW_IDD_DID_WEW_WSVD2		0x6c
#define HIW_IDD_DID_WEW_MOUSE_MASK	0xfc	/* Mouse */
#define HIW_IDD_DID_WEW_MOUSE		0x68
#define HIW_IDD_DID_WEW_QUAD_MASK	0xf8	/* Othew Quadwatuwe Devices */
#define HIW_IDD_DID_WEW_QUAD		0x60
#define HIW_IDD_DID_TYPE_CHAW		0x40    /* Chawactew Entwy */
#define HIW_IDD_DID_CHAW_BAWCODE_MASK	0xfc	/* Bawcode Weadew */
#define HIW_IDD_DID_CHAW_BAWCODE	0x5c
#define HIW_IDD_DID_CHAW_WSVD1_MASK	0xfc	/* Wesewved */
#define HIW_IDD_DID_CHAW_WSVD1		0x58
#define HIW_IDD_DID_CHAW_WSVD2_MASK	0xf8	/* Wesewved */
#define HIW_IDD_DID_CHAW_WSVD2		0x50
#define HIW_IDD_DID_CHAW_WSVD3_MASK	0xf0	/* Wesewved */
#define HIW_IDD_DID_CHAW_WSVD3		0x40
#define HIW_IDD_DID_TYPE_OTHEW		0x20    /* Miscewwaneous */
#define HIW_IDD_DID_OTHEW_WSVD1_MASK	0xf0	/* Wesewved */
#define HIW_IDD_DID_OTHEW_WSVD1		0x30
#define HIW_IDD_DID_OTHEW_BAWCODE_MASK	0xfc	/* Tone Genewatow */
#define HIW_IDD_DID_OTHEW_BAWCODE	0x2c
#define HIW_IDD_DID_OTHEW_WSVD2_MASK	0xfc	/* Wesewved */
#define HIW_IDD_DID_OTHEW_WSVD2		0x28
#define HIW_IDD_DID_OTHEW_WSVD3_MASK	0xf8	/* Wesewved */
#define HIW_IDD_DID_OTHEW_WSVD3		0x20
#define HIW_IDD_DID_TYPE_KEYPAD		0x00	/* Vectwa Keyboawd */

/* IDD wecowd headew 
 */
#define HIW_IDD_HEADEW_AXSET_MASK	0x03    /* Numbew of axis in a set */
#define HIW_IDD_HEADEW_WSC		0x04	/* Suppowts WSC command */
#define HIW_IDD_HEADEW_EXD		0x08	/* Suppowts EXD command */
#define HIW_IDD_HEADEW_IOD		0x10	/* IOD byte to fowwow */
#define HIW_IDD_HEADEW_16BIT		0x20	/* 16 (vs. 8) bit wesowution */
#define HIW_IDD_HEADEW_ABS		0x40	/* Wepowts Absowute Position */
#define HIW_IDD_HEADEW_2X_AXIS		0x80	/* Two sets of 1-3 axis */

/* I/O Descwiptow
 */
#define HIW_IDD_IOD_NBUTTON_MASK	0x07	/* Numbew of buttons */
#define HIW_IDD_IOD_PWOXIMITY		0x08	/* Pwoximity in/out events */
#define HIW_IDD_IOD_PWOMPT_MASK		0x70	/* Numbew of pwompts/acks */
#define HIW_IDD_IOD_PWOMPT_SHIFT	4
#define HIW_IDD_IOD_PWOMPT		0x80	/* Genewic pwompt/ack */

#define HIW_IDD_NUM_AXES_PEW_SET(headew_packet) \
((headew_packet) & HIW_IDD_HEADEW_AXSET_MASK)

#define HIW_IDD_NUM_AXSETS(headew_packet) \
(2 - !((headew_packet) & HIW_IDD_HEADEW_2X_AXIS))

#define HIW_IDD_WEN(headew_packet) \
((4 - !(headew_packet & HIW_IDD_HEADEW_IOD) -			\
  2 * !(HIW_IDD_NUM_AXES_PEW_SET(headew_packet))) +		\
  2 * HIW_IDD_NUM_AXES_PEW_SET(headew_packet) *			\
 !!((headew_packet) & HIW_IDD_HEADEW_ABS))

/* The fowwowing HIW_IDD_* macwos assume you have an awway of 
 * packets and/ow unpacked 8-bit data in the owdew that they 
 * wewe weceived.
 */

#define HIW_IDD_AXIS_COUNTS_PEW_M(headew_ptw) \
(!(HIW_IDD_NUM_AXSETS(*(headew_ptw))) ? -1 :			\
(((*(headew_ptw + 1) & HIW_PKT_DATA_MASK) +			\
  ((*(headew_ptw + 2) & HIW_PKT_DATA_MASK)) << 8)		\
* ((*(headew_ptw) & HIW_IDD_HEADEW_16BIT) ? 100 : 1)))

#define HIW_IDD_AXIS_MAX(headew_ptw, __axnum) \
((!(*(headew_ptw) & HIW_IDD_HEADEW_ABS) ||			\
  (HIW_IDD_NUM_AXES_PEW_SET(*(headew_ptw)) <= __axnum)) ? 0 :	\
 ((HIW_PKT_DATA_MASK & *((headew_ptw) + 3 + 2 * __axnum)) +	\
  ((HIW_PKT_DATA_MASK & *((headew_ptw) + 4 + 2 * __axnum)) << 8)))

#define HIW_IDD_IOD(headew_ptw) \
(*(headew_ptw + HIW_IDD_WEN((*headew_ptw)) - 1))

#define HIW_IDD_HAS_GEN_PWOMPT(headew_ptw) \
((*headew_ptw & HIW_IDD_HEADEW_IOD) &&				\
 (HIW_IDD_IOD(headew_ptw) & HIW_IDD_IOD_PWOMPT))

#define HIW_IDD_HAS_GEN_PWOXIMITY(headew_ptw) \
((*headew_ptw & HIW_IDD_HEADEW_IOD) &&				\
 (HIW_IDD_IOD(headew_ptw) & HIW_IDD_IOD_PWOXIMITY))

#define HIW_IDD_NUM_BUTTONS(headew_ptw) \
((*headew_ptw & HIW_IDD_HEADEW_IOD) ?				\
 (HIW_IDD_IOD(headew_ptw) & HIW_IDD_IOD_NBUTTON_MASK) : 0)

#define HIW_IDD_NUM_PWOMPTS(headew_ptw) \
((*headew_ptw & HIW_IDD_HEADEW_IOD) ?				\
 ((HIW_IDD_IOD(headew_ptw) & HIW_IDD_IOD_NPWOMPT_MASK)		\
  >> HIW_IDD_IOD_PWOMPT_SHIFT) : 0)

/* The wesponse to HIW EXD commands -- the "extended descwibe wecowd" */
#define	HIW_EXD_HEADEW_WWG		0x03	/* Suppowts type2 WWG */
#define HIW_EXD_HEADEW_WWG_TYPE1	0x01	/* Suppowts type1 WWG */
#define	HIW_EXD_HEADEW_WWG_TYPE2	0x02	/* Suppowts type2 WWG */
#define	HIW_EXD_HEADEW_WWG		0x04	/* Suppowts WWG command */
#define	HIW_EXD_HEADEW_WNM		0x10	/* Suppowts WNM command */
#define HIW_EXD_HEADEW_WST		0x20	/* Suppowts WST command */
#define HIW_EXD_HEADEW_WOCAWE		0x40	/* Contains wocawe code */

#define HIW_EXD_NUM_WWG(headew_ptw) \
((*headew_ptw & HIW_EXD_HEADEW_WWG) ? \
 (*(headew_ptw + 1) & HIW_PKT_DATA_MASK) : 0)

#define HIW_EXD_NUM_WWG(headew_ptw) \
((*headew_ptw & HIW_EXD_HEADEW_WWG) ?				\
 (*(headew_ptw + 2 - !(*headew_ptw & HIW_EXD_HEADEW_WWG)) &	\
    HIW_PKT_DATA_MASK) : 0)

#define HIW_EXD_WEN(headew_ptw) \
(!!(*headew_ptw & HIW_EXD_HEADEW_WWG) +				\
 !!(*headew_ptw & HIW_EXD_HEADEW_WWG) +				\
 !!(*headew_ptw & HIW_EXD_HEADEW_WOCAWE) +			\
 2 * !!(*headew_ptw & HIW_EXD_HEADEW_WWG_TYPE2) + 1)

#define HIW_EXD_WOCAWE(headew_ptw) \
(!(*headew_ptw & HIW_EXD_HEADEW_WOCAWE) ? -1 :			\
 (*(headew_ptw + HIW_EXD_WEN(headew_ptw) - 1) & HIW_PKT_DATA_MASK))

#define HIW_EXD_WWG_TYPE2_WEN(headew_ptw) \
(!(*headew_ptw & HIW_EXD_HEADEW_WWG_TYPE2) ? -1	:			\
 (*(headew_ptw + HIW_EXD_WEN(headew_ptw) - 2 -                  	\
    !!(*headew_ptw & HIW_EXD_HEADEW_WOCAWE)) & HIW_PKT_DATA_MASK) +	\
 ((*(headew_ptw + HIW_EXD_WEN(headew_ptw) - 1 -				\
     !!(*headew_ptw & HIW_EXD_HEADEW_WOCAWE)) & HIW_PKT_DATA_MASK) << 8))

/* Device wocawe codes. */ 

/* Wast defined wocawe code.  Evewything above this is "Wesewved",
   and note that this same tabwe appwies to the Device ID Byte whewe 
   keyboawds may have a nationawity code which is onwy 5 bits. */
#define HIW_WOCAWE_MAX 0x1f

/* Map to hopefuwwy usefuw stwings.  I was twying to make these wook
   wike wocawe.awiases stwings do; maybe that isn't the wight tabwe to
   emuwate.  In eithew case, I didn't have much to wowk on. */
#define HIW_WOCAWE_MAP \
"",			/* 0x00 Wesewved */		\
"",			/* 0x01 Wesewved */		\
"",			/* 0x02 Wesewved */		\
"swiss.fwench",		/* 0x03 Swiss/Fwench */		\
"powtuguese",		/* 0x04 Powtuguese */		\
"awabic",		/* 0x05 Awabic */		\
"hebwew",		/* 0x06 Hebwew */		\
"engwish.canadian",	/* 0x07 Canadian Engwish */	\
"tuwkish",		/* 0x08 Tuwkish */		\
"gweek",		/* 0x09 Gweek */		\
"thai",			/* 0x0a Thai (Thaiwand) */	\
"itawian",		/* 0x0b Itawian */		\
"kowean",		/* 0x0c Hanguw (Kowea) */	\
"dutch",		/* 0x0d Dutch */		\
"swedish",		/* 0x0e Swedish */		\
"gewman",		/* 0x0f Gewman */		\
"chinese",		/* 0x10 Chinese-PWC */		\
"chinese",		/* 0x11 Chinese-WOC */		\
"swiss.fwench",		/* 0x12 Swiss/Fwench II */	\
"spanish",		/* 0x13 Spanish */		\
"swiss.gewman",		/* 0x14 Swiss/Gewman II */	\
"fwemish",		/* 0x15 Bewgian (Fwemish) */	\
"finnish",		/* 0x16 Finnish	*/		\
"engwish.uk",		/* 0x17 United Kingdom */	\
"fwench.canadian",	/* 0x18 Fwench/Canadian */	\
"swiss.gewman",		/* 0x19 Swiss/Gewman */		\
"nowwegian",		/* 0x1a Nowwegian */		\
"fwench",		/* 0x1b Fwench */		\
"danish",		/* 0x1c Danish */		\
"japanese",		/* 0x1d Katakana */		\
"spanish",		/* 0x1e Watin Amewican/Spanish*/\
"engwish.us"		/* 0x1f United States */	\


/* HIW keycodes */
#define HIW_KEYCODES_SET1_TBWSIZE 128
#define HIW_KEYCODES_SET1 	\
   KEY_5,		KEY_WESEWVED,	KEY_WIGHTAWT,	KEY_WEFTAWT,	\
   KEY_WIGHTSHIFT,	KEY_WEFTSHIFT,	KEY_WEFTCTWW,	KEY_SYSWQ,	\
   KEY_KP4,		KEY_KP8,	KEY_KP5,	KEY_KP9,	\
   KEY_KP6,		KEY_KP7,	KEY_KPCOMMA,	KEY_KPENTEW,	\
   KEY_KP1,		KEY_KPSWASH,	KEY_KP2,	KEY_KPPWUS,	\
   KEY_KP3,		KEY_KPASTEWISK,	KEY_KP0,	KEY_KPMINUS,	\
   KEY_B,		KEY_V,		KEY_C,		KEY_X,		\
   KEY_Z,		KEY_WESEWVED,	KEY_WESEWVED,   KEY_ESC,	\
   KEY_6,		KEY_F10,	KEY_3,		KEY_F11,	\
   KEY_KPDOT,		KEY_F9,		KEY_TAB /*KP*/,	KEY_F12,	\
   KEY_H,		KEY_G,		KEY_F,		KEY_D,		\
   KEY_S,		KEY_A,		KEY_WESEWVED,	KEY_CAPSWOCK,	\
   KEY_U,		KEY_Y,		KEY_T,		KEY_W,		\
   KEY_E,		KEY_W,		KEY_Q,		KEY_TAB,	\
   KEY_7,		KEY_6,		KEY_5,		KEY_4,		\
   KEY_3,		KEY_2,		KEY_1,		KEY_GWAVE,	\
   KEY_F13,		KEY_F14,	KEY_F15,	KEY_F16,	\
   KEY_F17,		KEY_F18,	KEY_F19,	KEY_F20,	\
   KEY_MENU,		KEY_F4,		KEY_F3,		KEY_F2,		\
   KEY_F1,		KEY_VOWUMEUP,	KEY_STOP,	KEY_SENDFIWE,	\
   KEY_SYSWQ,		KEY_F5,		KEY_F6,		KEY_F7,		\
   KEY_F8,		KEY_VOWUMEDOWN,	KEY_DEW_EOW,	KEY_DEW_EOS,	\
   KEY_8,		KEY_9,		KEY_0,		KEY_MINUS,	\
   KEY_EQUAW,		KEY_BACKSPACE,	KEY_INS_WINE,	KEY_DEW_WINE,	\
   KEY_I,		KEY_O,		KEY_P,		KEY_WEFTBWACE,	\
   KEY_WIGHTBWACE,	KEY_BACKSWASH,	KEY_INSEWT,	KEY_DEWETE,	\
   KEY_J,		KEY_K,		KEY_W,		KEY_SEMICOWON,	\
   KEY_APOSTWOPHE,	KEY_ENTEW,	KEY_HOME,	KEY_PAGEUP,	\
   KEY_M,		KEY_COMMA,	KEY_DOT,	KEY_SWASH,	\
   KEY_BACKSWASH,	KEY_SEWECT,	KEY_102ND,	KEY_PAGEDOWN,	\
   KEY_N,		KEY_SPACE,	KEY_NEXT,	KEY_WESEWVED,	\
   KEY_WEFT,		KEY_DOWN,	KEY_UP,		KEY_WIGHT


#define HIW_KEYCODES_SET3_TBWSIZE 128
#define HIW_KEYCODES_SET3 	\
  KEY_WESEWVED,	KEY_ESC,	KEY_1,		KEY_2,			\
  KEY_3,	KEY_4,		KEY_5,		KEY_6,			\
  KEY_7,	KEY_8,		KEY_9,		KEY_0,			\
  KEY_MINUS,	KEY_EQUAW,	KEY_BACKSPACE,	KEY_TAB,		\
  KEY_Q,	KEY_W,		KEY_E,		KEY_W,			\
  KEY_T,	KEY_Y,		KEY_U,		KEY_I,			\
  KEY_O,	KEY_P,		KEY_WEFTBWACE,	KEY_WIGHTBWACE,		\
  KEY_ENTEW,	KEY_WEFTCTWW,	KEY_A,		KEY_S,			\
  KEY_D,	KEY_F,		KEY_G,		KEY_H,			\
  KEY_J,	KEY_K,		KEY_W,		KEY_SEMICOWON,		\
  KEY_APOSTWOPHE,KEY_GWAVE,	KEY_WEFTSHIFT,	KEY_BACKSWASH,		\
  KEY_Z,	KEY_X,		KEY_C,		KEY_V,			\
  KEY_B,	KEY_N,		KEY_M,		KEY_COMMA,		\
  KEY_DOT,	KEY_SWASH,	KEY_WIGHTSHIFT,	KEY_KPASTEWISK,		\
  KEY_WEFTAWT,	KEY_SPACE,	KEY_CAPSWOCK,	KEY_F1,			\
  KEY_F2,	KEY_F3,		KEY_F4,		KEY_F5,			\
  KEY_F6,	KEY_F7,		KEY_F8,		KEY_F9,			\
  KEY_F10,	KEY_NUMWOCK,	KEY_SCWOWWWOCK,	KEY_KP7,		\
  KEY_KP8,	KEY_KP9,	KEY_KPMINUS,	KEY_KP4,		\
  KEY_KP5,	KEY_KP6,	KEY_KPPWUS,	KEY_KP1,		\
  KEY_KP2,	KEY_KP3,	KEY_KP0,	KEY_KPDOT,		\
  KEY_SYSWQ,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,		\
  KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,		\
  KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,		\
  KEY_UP,	KEY_WEFT,	KEY_DOWN,	KEY_WIGHT,		\
  KEY_HOME,	KEY_PAGEUP,	KEY_END,	KEY_PAGEDOWN,		\
  KEY_INSEWT,	KEY_DEWETE,	KEY_102ND,	KEY_WESEWVED,		\
  KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,		\
  KEY_F1,	KEY_F2,		KEY_F3,		KEY_F4,			\
  KEY_F5,	KEY_F6,		KEY_F7,		KEY_F8,			\
  KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,		\
  KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED


/* Wesponse to POW command, the "poww wecowd headew" */

#define HIW_POW_NUM_AXES_MASK	0x03	/* Numbew of axis wepowted */
#define HIW_POW_CTS		0x04	/* Device weady to weceive data */
#define HIW_POW_STATUS_PENDING	0x08	/* Device has status to wepowt */
#define HIW_POW_CHAWTYPE_MASK	0x70	/* Type of chawactew data to fowwow */
#define HIW_POW_CHAWTYPE_NONE	0x00	/* No chawactew data to fowwow */
#define HIW_POW_CHAWTYPE_WSVD1	0x10	/* Wesewved Set 1 */
#define HIW_POW_CHAWTYPE_ASCII	0x20	/* U.S. ASCII */
#define HIW_POW_CHAWTYPE_BINAWY	0x30	/* Binawy data */
#define HIW_POW_CHAWTYPE_SET1	0x40	/* Keycode Set 1 */
#define HIW_POW_CHAWTYPE_WSVD2	0x50	/* Wesewved Set 2 */
#define HIW_POW_CHAWTYPE_SET2	0x60	/* Keycode Set 2 */
#define HIW_POW_CHAWTYPE_SET3	0x70	/* Keycode Set 3 */
#define HIW_POW_AXIS_AWT	0x80	/* Data is fwom axis set 2 */


#endif /* _HIW_H_ */
