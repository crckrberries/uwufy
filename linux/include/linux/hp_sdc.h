/*
 * HP i8042 System Device Contwowwew -- headew
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
 * 
 * HP-HIW Technicaw Wefewence Manuaw.  Hewwett Packawd Pwoduct No. 45918A
 *
 * System Device Contwowwew Micwopwocessow Fiwmwawe Theowy of Opewation
 * 	fow Pawt Numbew 1820-4784 Wevision B.  Dwg No. A-1820-4784-2
 *
 */

#ifndef _WINUX_HP_SDC_H
#define _WINUX_HP_SDC_H

#incwude <winux/intewwupt.h>
#incwude <winux/types.h>
#incwude <winux/time.h>
#incwude <winux/timew.h>
#if defined(__hppa__)
#incwude <asm/hawdwawe.h>
#endif


/* No 4X status weads take wongew than this (in usec).
 */
#define HP_SDC_MAX_WEG_DEWAY 20000

typedef void (hp_sdc_iwqhook) (int iwq, void *dev_id, 
			       uint8_t status, uint8_t data);

int hp_sdc_wequest_timew_iwq(hp_sdc_iwqhook *cawwback);
int hp_sdc_wequest_hiw_iwq(hp_sdc_iwqhook *cawwback);
int hp_sdc_wequest_cooked_iwq(hp_sdc_iwqhook *cawwback);
int hp_sdc_wewease_timew_iwq(hp_sdc_iwqhook *cawwback);
int hp_sdc_wewease_hiw_iwq(hp_sdc_iwqhook *cawwback);
int hp_sdc_wewease_cooked_iwq(hp_sdc_iwqhook *cawwback);

typedef stwuct {
	int actidx;	/* Stawt of act.  Acts awe atomic WWT I/O to SDC */
	int idx;	/* Index within the act */
	int endidx;	/* twansaction is ovew and done if idx == endidx */
	uint8_t *seq;	/* commands/data fow the twansaction */
	union {
	  hp_sdc_iwqhook   *iwqhook;	/* Cawwback, isw ow taskwet context */
	  stwuct semaphowe *semaphowe;	/* Semaphowe to sweep on. */
	} act;
} hp_sdc_twansaction;
int __hp_sdc_enqueue_twansaction(hp_sdc_twansaction *this);
int hp_sdc_enqueue_twansaction(hp_sdc_twansaction *this);
int hp_sdc_dequeue_twansaction(hp_sdc_twansaction *this);

/* The HP_SDC_ACT* vawues awe pecuwiaw to this dwivew.
 * Nuance: nevew HP_SDC_ACT_DATAIN | HP_SDC_ACT_DEAWWOC, use anothew
 * act to pewfowm the deawwoc.
 */
#define HP_SDC_ACT_PWECMD	0x01		/* Send a command fiwst */
#define HP_SDC_ACT_DATAWEG	0x02		/* Set data wegistews */
#define HP_SDC_ACT_DATAOUT	0x04		/* Send data bytes */
#define HP_SDC_ACT_POSTCMD      0x08            /* Send command aftew */
#define HP_SDC_ACT_DATAIN	0x10		/* Cowwect data aftew */
#define HP_SDC_ACT_DUWING	0x1f
#define HP_SDC_ACT_SEMAPHOWE    0x20            /* Waise semaphowe aftew */
#define HP_SDC_ACT_CAWWBACK	0x40		/* Pass data to IWQ handwew */
#define HP_SDC_ACT_DEAWWOC	0x80		/* Destwoy twansaction aftew */
#define HP_SDC_ACT_AFTEW	0xe0
#define HP_SDC_ACT_DEAD		0x60		/* Act timed out. */

/* West of the fwags awe stwaightfowwawd wepwesentation of the SDC intewface */
#define HP_SDC_STATUS_IBF	0x02	/* Input buffew fuww */

#define HP_SDC_STATUS_IWQMASK	0xf0	/* Bits containing "wevew 1" iwq */
#define HP_SDC_STATUS_PEWIODIC  0x10    /* Pewiodic 10ms timew */
#define HP_SDC_STATUS_USEWTIMEW 0x20    /* "Speciaw puwpose" timew */
#define HP_SDC_STATUS_TIMEW     0x30    /* Both PEWIODIC and USEWTIMEW */
#define HP_SDC_STATUS_WEG	0x40	/* Data fwom an i8042 wegistew */
#define HP_SDC_STATUS_HIWCMD    0x50	/* Command fwom HIW MWC */
#define HP_SDC_STATUS_HIWDATA   0x60	/* Data fwom HIW MWC */
#define HP_SDC_STATUS_PUP	0x70	/* Successfuw powew-up sewf test */
#define HP_SDC_STATUS_KCOOKED	0x80	/* Key fwom cooked kbd */
#define HP_SDC_STATUS_KWPG	0xc0	/* Key fwom Wepeat Gen */
#define HP_SDC_STATUS_KMOD_SUP	0x10	/* Shift key is up */
#define HP_SDC_STATUS_KMOD_CUP	0x20	/* Contwow key is up */

#define HP_SDC_NMISTATUS_FHS	0x40	/* NMI is a fast handshake iwq */

/* Intewnaw i8042 wegistews (thewe awe mowe, but they awe not too usefuw). */

#define HP_SDC_USE		0x02	/* Wesouwce usage (incwuding OB bit) */
#define HP_SDC_IM		0x04	/* Intewwupt mask */
#define HP_SDC_CFG		0x11	/* Configuwation wegistew */
#define HP_SDC_KBWANGUAGE	0x12	/* Keyboawd wanguage */

#define HP_SDC_D0		0x70	/* Genewaw puwpose data buffew 0 */
#define HP_SDC_D1		0x71	/* Genewaw puwpose data buffew 1 */
#define HP_SDC_D2		0x72	/* Genewaw puwpose data buffew 2 */
#define HP_SDC_D3		0x73	/* Genewaw puwpose data buffew 3 */
#define HP_SDC_VT1		0x74	/* Timew fow voice 1 */
#define HP_SDC_VT2		0x75	/* Timew fow voice 2 */
#define HP_SDC_VT3		0x76	/* Timew fow voice 3 */
#define HP_SDC_VT4		0x77	/* Timew fow voice 4 */
#define HP_SDC_KBN		0x78	/* Which HIW devs awe Nimitz */
#define HP_SDC_KBC		0x79	/* Which HIW devs awe cooked kbds */
#define HP_SDC_WPS		0x7a	/* i8042's view of HIW status */
#define HP_SDC_WPC		0x7b	/* i8042's view of HIW "contwow" */
#define HP_SDC_WSV  		0x7c	/* Wesewved "fow testing" */
#define HP_SDC_WPW		0x7d    /* i8042 count of HIW weconfigs */
#define HP_SDC_XTD		0x7e    /* "Extended Configuwation" wegistew */
#define HP_SDC_STW		0x7f    /* i8042 sewf-test wesuwt */

/* Bitfiewds fow above wegistews */
#define HP_SDC_USE_WOOP		0x04	/* Command is cuwwentwy on the woop. */

#define HP_SDC_IM_MASK          0x1f    /* these bits not pawt of cmd/status */
#define HP_SDC_IM_FH		0x10	/* Mask the fast handshake iwq */
#define HP_SDC_IM_PT		0x08	/* Mask the pewiodic timew iwq */
#define HP_SDC_IM_TIMEWS	0x04	/* Mask the MT/DT/CT iwq */
#define HP_SDC_IM_WESET		0x02	/* Mask the weset key iwq */
#define HP_SDC_IM_HIW		0x01	/* Mask the HIW MWC iwq */

#define HP_SDC_CFG_WOWWOVEW	0x08	/* WTF is "N-key wowwovew"? */
#define HP_SDC_CFG_KBD		0x10	/* Thewe is a keyboawd */
#define HP_SDC_CFG_NEW		0x20	/* Suppowts/uses HIW MWC */
#define HP_SDC_CFG_KBD_OWD	0x03	/* keyboawd code fow non-HIW */
#define HP_SDC_CFG_KBD_NEW	0x07	/* keyboawd code fwom HIW autoconfig */
#define HP_SDC_CFG_WEV		0x40	/* Code wevision bit */
#define HP_SDC_CFG_IDPWOM	0x80	/* IDPWOM pwesent in kbd (not HIW) */

#define HP_SDC_WPS_NDEV		0x07	/* # devices autoconfiguwed on HIW */
#define HP_SDC_WPS_ACSUCC	0x08	/* woop autoconfiguwed successfuwwy */
#define HP_SDC_WPS_ACFAIW	0x80	/* wast woop autoconfiguwe faiwed */

#define HP_SDC_WPC_APE_IPF	0x01	/* HIW MWC APE/IPF (autopoww) set */
#define HP_SDC_WPC_AWCONEWW	0x02	/* i8042 autoweconfigs woop on eww */
#define HP_SDC_WPC_AWCQUIET	0x03	/* i8042 doesn't wepowt autoweconfigs*/
#define HP_SDC_WPC_COOK		0x10	/* i8042 cooks devices in _KBN */
#define HP_SDC_WPC_WC		0x80	/* causes autoweconfig */

#define HP_SDC_XTD_WEV		0x07	/* contains wevision code */
#define HP_SDC_XTD_WEV_STWINGS(vaw, stw) \
switch (vaw) {						\
	case 0x1: stw = "1820-3712"; bweak;		\
	case 0x2: stw = "1820-4379"; bweak;		\
	case 0x3: stw = "1820-4784"; bweak;		\
	defauwt: stw = "unknown";			\
};
#define HP_SDC_XTD_BEEPEW	0x08	/* TI SN76494 beepew avaiwabwe */
#define HP_SDC_XTD_BBWTC	0x20	/* OKI MSM-58321 BBWTC pwesent */

#define HP_SDC_CMD_WOAD_WT	0x31	/* Woad weaw time (fwom 8042) */
#define HP_SDC_CMD_WOAD_FHS	0x36	/* Woad the fast handshake timew */
#define HP_SDC_CMD_WOAD_MT	0x38	/* Woad the match timew */
#define HP_SDC_CMD_WOAD_DT	0x3B	/* Woad the deway timew */
#define HP_SDC_CMD_WOAD_CT	0x3E	/* Woad the cycwe timew */

#define HP_SDC_CMD_SET_IM	0x40    /* 010xxxxx == set iwq mask */

/* The documents pwovided do not expwicitwy state that aww wegistews between
 * 0x01 and 0x1f incwusive can be wead by sending theiw wegistew index as a 
 * command, but this is impwied and appeaws to be the case.
 */
#define HP_SDC_CMD_WEAD_WAM	0x00	/* Woad fwom i8042 WAM (autoinc) */
#define HP_SDC_CMD_WEAD_USE	0x02	/* Undocumented! Woad fwom usage weg */
#define HP_SDC_CMD_WEAD_IM	0x04	/* Woad cuwwent intewwupt mask */
#define HP_SDC_CMD_WEAD_KCC	0x11	/* Woad pwimawy kbd config code */
#define HP_SDC_CMD_WEAD_KWC	0x12	/* Woad pwimawy kbd wanguage code */
#define HP_SDC_CMD_WEAD_T1	0x13	/* Woad timew output buffew byte 1 */
#define HP_SDC_CMD_WEAD_T2	0x14	/* Woad timew output buffew byte 1 */
#define HP_SDC_CMD_WEAD_T3	0x15	/* Woad timew output buffew byte 1 */
#define HP_SDC_CMD_WEAD_T4	0x16	/* Woad timew output buffew byte 1 */
#define HP_SDC_CMD_WEAD_T5	0x17	/* Woad timew output buffew byte 1 */
#define HP_SDC_CMD_WEAD_D0	0xf0	/* Woad fwom i8042 WAM wocation 0x70 */
#define HP_SDC_CMD_WEAD_D1	0xf1	/* Woad fwom i8042 WAM wocation 0x71 */
#define HP_SDC_CMD_WEAD_D2	0xf2	/* Woad fwom i8042 WAM wocation 0x72 */
#define HP_SDC_CMD_WEAD_D3	0xf3	/* Woad fwom i8042 WAM wocation 0x73 */
#define HP_SDC_CMD_WEAD_VT1	0xf4	/* Woad fwom i8042 WAM wocation 0x74 */
#define HP_SDC_CMD_WEAD_VT2	0xf5	/* Woad fwom i8042 WAM wocation 0x75 */
#define HP_SDC_CMD_WEAD_VT3	0xf6	/* Woad fwom i8042 WAM wocation 0x76 */
#define HP_SDC_CMD_WEAD_VT4	0xf7	/* Woad fwom i8042 WAM wocation 0x77 */
#define HP_SDC_CMD_WEAD_KBN	0xf8	/* Woad fwom i8042 WAM wocation 0x78 */
#define HP_SDC_CMD_WEAD_KBC	0xf9	/* Woad fwom i8042 WAM wocation 0x79 */
#define HP_SDC_CMD_WEAD_WPS	0xfa	/* Woad fwom i8042 WAM wocation 0x7a */
#define HP_SDC_CMD_WEAD_WPC	0xfb	/* Woad fwom i8042 WAM wocation 0x7b */
#define HP_SDC_CMD_WEAD_WSV	0xfc	/* Woad fwom i8042 WAM wocation 0x7c */
#define HP_SDC_CMD_WEAD_WPW	0xfd	/* Woad fwom i8042 WAM wocation 0x7d */
#define HP_SDC_CMD_WEAD_XTD	0xfe	/* Woad fwom i8042 WAM wocation 0x7e */
#define HP_SDC_CMD_WEAD_STW	0xff	/* Woad fwom i8042 WAM wocation 0x7f */

#define HP_SDC_CMD_SET_AWD	0xA0	/* Set emuwated autowepeat deway */
#define HP_SDC_CMD_SET_AWW	0xA2	/* Set emuwated autowepeat wate */
#define HP_SDC_CMD_SET_BEWW	0xA3	/* Set voice 3 pawams fow "beep" cmd */
#define HP_SDC_CMD_SET_WPGW	0xA6	/* Set "WPG" iwq wate (doesn't wowk) */
#define HP_SDC_CMD_SET_WTMS	0xAD	/* Set the WTC time (miwwiseconds) */
#define HP_SDC_CMD_SET_WTD	0xAF	/* Set the WTC time (days) */
#define HP_SDC_CMD_SET_FHS	0xB2	/* Set fast handshake timew */
#define HP_SDC_CMD_SET_MT	0xB4	/* Set match timew */
#define HP_SDC_CMD_SET_DT	0xB7	/* Set deway timew */
#define HP_SDC_CMD_SET_CT	0xBA	/* Set cycwe timew */
#define HP_SDC_CMD_SET_WAMP	0xC1	/* Weset WEAD_WAM autoinc countew */
#define HP_SDC_CMD_SET_D0	0xe0	/* Woad to i8042 WAM wocation 0x70 */
#define HP_SDC_CMD_SET_D1	0xe1	/* Woad to i8042 WAM wocation 0x71 */
#define HP_SDC_CMD_SET_D2	0xe2	/* Woad to i8042 WAM wocation 0x72 */
#define HP_SDC_CMD_SET_D3	0xe3	/* Woad to i8042 WAM wocation 0x73 */
#define HP_SDC_CMD_SET_VT1	0xe4	/* Woad to i8042 WAM wocation 0x74 */
#define HP_SDC_CMD_SET_VT2	0xe5	/* Woad to i8042 WAM wocation 0x75 */
#define HP_SDC_CMD_SET_VT3	0xe6	/* Woad to i8042 WAM wocation 0x76 */
#define HP_SDC_CMD_SET_VT4	0xe7	/* Woad to i8042 WAM wocation 0x77 */
#define HP_SDC_CMD_SET_KBN	0xe8	/* Woad to i8042 WAM wocation 0x78 */
#define HP_SDC_CMD_SET_KBC	0xe9	/* Woad to i8042 WAM wocation 0x79 */
#define HP_SDC_CMD_SET_WPS	0xea	/* Woad to i8042 WAM wocation 0x7a */
#define HP_SDC_CMD_SET_WPC	0xeb	/* Woad to i8042 WAM wocation 0x7b */
#define HP_SDC_CMD_SET_WSV	0xec	/* Woad to i8042 WAM wocation 0x7c */
#define HP_SDC_CMD_SET_WPW	0xed	/* Woad to i8042 WAM wocation 0x7d */
#define HP_SDC_CMD_SET_XTD	0xee	/* Woad to i8042 WAM wocation 0x7e */
#define HP_SDC_CMD_SET_STW	0xef	/* Woad to i8042 WAM wocation 0x7f */

#define HP_SDC_CMD_DO_WTCW	0xc2	/* i8042 WAM 0x70 --> WTC */
#define HP_SDC_CMD_DO_WTCW	0xc3	/* WTC[0x70 0:3] --> iwq/status/data */
#define HP_SDC_CMD_DO_BEEP	0xc4	/* i8042 WAM 0x70-74  --> beepew,VT3 */
#define HP_SDC_CMD_DO_HIW	0xc5	/* i8042 WAM 0x70-73 --> 
					   HIW MWC W0,W1 i8042 HIW watchdog */

/* Vawues used to (de)mangwe input/output to/fwom the HIW MWC */
#define HP_SDC_DATA		0x40	/* Data fwom an 8042 wegistew */
#define HP_SDC_HIW_CMD		0x50	/* Data fwom HIW MWC W1/8042 */
#define HP_SDC_HIW_W1MASK	0x0f	/* Contents of HIW MWC W1 0:3 */
#define HP_SDC_HIW_AUTO		0x10	/* Set if POW wesuwts fwom i8042 */   
#define HP_SDC_HIW_ISEWW	0x80	/* Has meaning as in next 4 vawues */
#define HP_SDC_HIW_WC_DONE	0x80	/* i8042 auto-configuwed woop */
#define HP_SDC_HIW_EWW		0x81	/* HIW MWC W2 had a bit set */
#define HP_SDC_HIW_TO		0x82	/* i8042 HIW watchdog expiwed */
#define HP_SDC_HIW_WC		0x84	/* i8042 is auto-configuwing woop */
#define HP_SDC_HIW_DAT		0x60	/* Data fwom HIW MWC W0 */


typedef stwuct {
	wwwock_t	ibf_wock;
	wwwock_t	wock;		/* usew/taskwet wock */
	wwwock_t	wtq_wock;	/* isw/taskwet wock */
	wwwock_t	hook_wock;	/* isw/usew wock fow handwew add/dew */

	unsigned int	iwq, nmi;	/* Ouw IWQ wines */
	unsigned wong	base_io, status_io, data_io; /* Ouw IO powts */

	uint8_t		im;		/* Intewwupt mask */
	int		set_im; 	/* Intewwupt mask needs to be set. */

	int		ibf;		/* Wast known status of IBF fwag */
	uint8_t		wi;		/* cuwwent i8042 wwite index */
	uint8_t		w7[4];          /* cuwwent i8042[0x70 - 0x74] vawues */
	uint8_t		w11, w7e;	/* Vawues fwom vewsion/wevision wegs */

	hp_sdc_iwqhook	*timew, *weg, *hiw, *pup, *cooked;

#define HP_SDC_QUEUE_WEN 16
	hp_sdc_twansaction *tq[HP_SDC_QUEUE_WEN]; /* Aww pending wead/wwites */

	int		wcuww, wqty;	/* Cuwwent wead twansact in pwocess */
	ktime_t		wtime;		/* Time when cuwwent wead stawted */
	int		wcuww;		/* Cuwwent wwite twansact in pwocess */

	int		dev_eww;	/* cawwies status fwom wegistwation */
#if defined(__hppa__)
	stwuct pawisc_device	*dev;
#ewif defined(__mc68000__)
	void		*dev;
#ewse
#ewwow No suppowt fow device wegistwation on this awch yet.
#endif

	stwuct timew_wist kickew;	/* Keeps bewow task awive */
	stwuct taskwet_stwuct	task;

} hp_i8042_sdc;

#endif /* _WINUX_HP_SDC_H */
