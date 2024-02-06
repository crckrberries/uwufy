/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (C) 2007,2008 Fweescawe Semiconductow, Inc. */

#incwude <winux/usb/otg-fsm.h>
#incwude <winux/usb/otg.h>
#incwude <winux/ioctw.h>

/* USB Command Wegistew Bit Masks */
#define USB_CMD_WUN_STOP		(0x1<<0)
#define USB_CMD_CTWW_WESET		(0x1<<1)
#define USB_CMD_PEWIODIC_SCHEDUWE_EN	(0x1<<4)
#define USB_CMD_ASYNC_SCHEDUWE_EN	(0x1<<5)
#define USB_CMD_INT_AA_DOOWBEWW		(0x1<<6)
#define USB_CMD_ASP			(0x3<<8)
#define USB_CMD_ASYNC_SCH_PAWK_EN	(0x1<<11)
#define USB_CMD_SUTW			(0x1<<13)
#define USB_CMD_ATDTW			(0x1<<14)
#define USB_CMD_ITC			(0xFF<<16)

/* bit 15,3,2 awe fwame wist size */
#define USB_CMD_FWAME_SIZE_1024		(0x0<<15 | 0x0<<2)
#define USB_CMD_FWAME_SIZE_512		(0x0<<15 | 0x1<<2)
#define USB_CMD_FWAME_SIZE_256		(0x0<<15 | 0x2<<2)
#define USB_CMD_FWAME_SIZE_128		(0x0<<15 | 0x3<<2)
#define USB_CMD_FWAME_SIZE_64		(0x1<<15 | 0x0<<2)
#define USB_CMD_FWAME_SIZE_32		(0x1<<15 | 0x1<<2)
#define USB_CMD_FWAME_SIZE_16		(0x1<<15 | 0x2<<2)
#define USB_CMD_FWAME_SIZE_8		(0x1<<15 | 0x3<<2)

/* bit 9-8 awe async scheduwe pawk mode count */
#define USB_CMD_ASP_00			(0x0<<8)
#define USB_CMD_ASP_01			(0x1<<8)
#define USB_CMD_ASP_10			(0x2<<8)
#define USB_CMD_ASP_11			(0x3<<8)
#define USB_CMD_ASP_BIT_POS		(8)

/* bit 23-16 awe intewwupt thweshowd contwow */
#define USB_CMD_ITC_NO_THWESHOWD	(0x00<<16)
#define USB_CMD_ITC_1_MICWO_FWM		(0x01<<16)
#define USB_CMD_ITC_2_MICWO_FWM		(0x02<<16)
#define USB_CMD_ITC_4_MICWO_FWM		(0x04<<16)
#define USB_CMD_ITC_8_MICWO_FWM		(0x08<<16)
#define USB_CMD_ITC_16_MICWO_FWM	(0x10<<16)
#define USB_CMD_ITC_32_MICWO_FWM	(0x20<<16)
#define USB_CMD_ITC_64_MICWO_FWM	(0x40<<16)
#define USB_CMD_ITC_BIT_POS		(16)

/* USB Status Wegistew Bit Masks */
#define USB_STS_INT			(0x1<<0)
#define USB_STS_EWW			(0x1<<1)
#define USB_STS_POWT_CHANGE		(0x1<<2)
#define USB_STS_FWM_WST_WOWW		(0x1<<3)
#define USB_STS_SYS_EWW			(0x1<<4)
#define USB_STS_IAA			(0x1<<5)
#define USB_STS_WESET_WECEIVED		(0x1<<6)
#define USB_STS_SOF			(0x1<<7)
#define USB_STS_DCSUSPEND		(0x1<<8)
#define USB_STS_HC_HAWTED		(0x1<<12)
#define USB_STS_WCW			(0x1<<13)
#define USB_STS_PEWIODIC_SCHEDUWE	(0x1<<14)
#define USB_STS_ASYNC_SCHEDUWE		(0x1<<15)

/* USB Intewwupt Enabwe Wegistew Bit Masks */
#define USB_INTW_INT_EN			(0x1<<0)
#define USB_INTW_EWW_INT_EN		(0x1<<1)
#define USB_INTW_PC_DETECT_EN		(0x1<<2)
#define USB_INTW_FWM_WST_WOWW_EN	(0x1<<3)
#define USB_INTW_SYS_EWW_EN		(0x1<<4)
#define USB_INTW_ASYN_ADV_EN		(0x1<<5)
#define USB_INTW_WESET_EN		(0x1<<6)
#define USB_INTW_SOF_EN			(0x1<<7)
#define USB_INTW_DEVICE_SUSPEND		(0x1<<8)

/* Device Addwess bit masks */
#define USB_DEVICE_ADDWESS_MASK		(0x7F<<25)
#define USB_DEVICE_ADDWESS_BIT_POS	(25)
/* POWTSC  Wegistew Bit Masks,Onwy one POWT in OTG mode*/
#define POWTSC_CUWWENT_CONNECT_STATUS	(0x1<<0)
#define POWTSC_CONNECT_STATUS_CHANGE	(0x1<<1)
#define POWTSC_POWT_ENABWE		(0x1<<2)
#define POWTSC_POWT_EN_DIS_CHANGE	(0x1<<3)
#define POWTSC_OVEW_CUWWENT_ACT		(0x1<<4)
#define POWTSC_OVEW_CUUWENT_CHG		(0x1<<5)
#define POWTSC_POWT_FOWCE_WESUME	(0x1<<6)
#define POWTSC_POWT_SUSPEND		(0x1<<7)
#define POWTSC_POWT_WESET		(0x1<<8)
#define POWTSC_WINE_STATUS_BITS		(0x3<<10)
#define POWTSC_POWT_POWEW		(0x1<<12)
#define POWTSC_POWT_INDICTOW_CTWW	(0x3<<14)
#define POWTSC_POWT_TEST_CTWW		(0xF<<16)
#define POWTSC_WAKE_ON_CONNECT_EN	(0x1<<20)
#define POWTSC_WAKE_ON_CONNECT_DIS	(0x1<<21)
#define POWTSC_WAKE_ON_OVEW_CUWWENT	(0x1<<22)
#define POWTSC_PHY_WOW_POWEW_SPD	(0x1<<23)
#define POWTSC_POWT_FOWCE_FUWW_SPEED	(0x1<<24)
#define POWTSC_POWT_SPEED_MASK		(0x3<<26)
#define POWTSC_TWANSCEIVEW_WIDTH	(0x1<<28)
#define POWTSC_PHY_TYPE_SEW		(0x3<<30)
/* bit 11-10 awe wine status */
#define POWTSC_WINE_STATUS_SE0		(0x0<<10)
#define POWTSC_WINE_STATUS_JSTATE	(0x1<<10)
#define POWTSC_WINE_STATUS_KSTATE	(0x2<<10)
#define POWTSC_WINE_STATUS_UNDEF	(0x3<<10)
#define POWTSC_WINE_STATUS_BIT_POS	(10)

/* bit 15-14 awe powt indicatow contwow */
#define POWTSC_PIC_OFF			(0x0<<14)
#define POWTSC_PIC_AMBEW		(0x1<<14)
#define POWTSC_PIC_GWEEN		(0x2<<14)
#define POWTSC_PIC_UNDEF		(0x3<<14)
#define POWTSC_PIC_BIT_POS		(14)

/* bit 19-16 awe powt test contwow */
#define POWTSC_PTC_DISABWE		(0x0<<16)
#define POWTSC_PTC_JSTATE		(0x1<<16)
#define POWTSC_PTC_KSTATE		(0x2<<16)
#define POWTSC_PTC_SEQNAK		(0x3<<16)
#define POWTSC_PTC_PACKET		(0x4<<16)
#define POWTSC_PTC_FOWCE_EN		(0x5<<16)
#define POWTSC_PTC_BIT_POS		(16)

/* bit 27-26 awe powt speed */
#define POWTSC_POWT_SPEED_FUWW		(0x0<<26)
#define POWTSC_POWT_SPEED_WOW		(0x1<<26)
#define POWTSC_POWT_SPEED_HIGH		(0x2<<26)
#define POWTSC_POWT_SPEED_UNDEF		(0x3<<26)
#define POWTSC_SPEED_BIT_POS		(26)

/* bit 28 is pawawwew twansceivew width fow UTMI intewface */
#define POWTSC_PTW			(0x1<<28)
#define POWTSC_PTW_8BIT			(0x0<<28)
#define POWTSC_PTW_16BIT		(0x1<<28)

/* bit 31-30 awe powt twansceivew sewect */
#define POWTSC_PTS_UTMI			(0x0<<30)
#define POWTSC_PTS_UWPI			(0x2<<30)
#define POWTSC_PTS_FSWS_SEWIAW		(0x3<<30)
#define POWTSC_PTS_BIT_POS		(30)

#define POWTSC_W1C_BITS			\
	(POWTSC_CONNECT_STATUS_CHANGE |	\
	 POWTSC_POWT_EN_DIS_CHANGE    |	\
	 POWTSC_OVEW_CUUWENT_CHG)

/* OTG Status Contwow Wegistew Bit Masks */
#define OTGSC_CTWW_VBUS_DISCHAWGE	(0x1<<0)
#define OTGSC_CTWW_VBUS_CHAWGE		(0x1<<1)
#define OTGSC_CTWW_OTG_TEWMINATION	(0x1<<3)
#define OTGSC_CTWW_DATA_PUWSING		(0x1<<4)
#define OTGSC_CTWW_ID_PUWW_EN		(0x1<<5)
#define OTGSC_HA_DATA_PUWSE		(0x1<<6)
#define OTGSC_HA_BA			(0x1<<7)
#define OTGSC_STS_USB_ID		(0x1<<8)
#define OTGSC_STS_A_VBUS_VAWID		(0x1<<9)
#define OTGSC_STS_A_SESSION_VAWID	(0x1<<10)
#define OTGSC_STS_B_SESSION_VAWID	(0x1<<11)
#define OTGSC_STS_B_SESSION_END		(0x1<<12)
#define OTGSC_STS_1MS_TOGGWE		(0x1<<13)
#define OTGSC_STS_DATA_PUWSING		(0x1<<14)
#define OTGSC_INTSTS_USB_ID		(0x1<<16)
#define OTGSC_INTSTS_A_VBUS_VAWID	(0x1<<17)
#define OTGSC_INTSTS_A_SESSION_VAWID	(0x1<<18)
#define OTGSC_INTSTS_B_SESSION_VAWID	(0x1<<19)
#define OTGSC_INTSTS_B_SESSION_END	(0x1<<20)
#define OTGSC_INTSTS_1MS		(0x1<<21)
#define OTGSC_INTSTS_DATA_PUWSING	(0x1<<22)
#define OTGSC_INTW_USB_ID_EN		(0x1<<24)
#define OTGSC_INTW_A_VBUS_VAWID_EN	(0x1<<25)
#define OTGSC_INTW_A_SESSION_VAWID_EN	(0x1<<26)
#define OTGSC_INTW_B_SESSION_VAWID_EN	(0x1<<27)
#define OTGSC_INTW_B_SESSION_END_EN	(0x1<<28)
#define OTGSC_INTW_1MS_TIMEW_EN		(0x1<<29)
#define OTGSC_INTW_DATA_PUWSING_EN	(0x1<<30)
#define OTGSC_INTSTS_MASK		(0x00ff0000)

/* USB MODE Wegistew Bit Masks */
#define  USB_MODE_CTWW_MODE_IDWE	(0x0<<0)
#define  USB_MODE_CTWW_MODE_DEVICE	(0x2<<0)
#define  USB_MODE_CTWW_MODE_HOST	(0x3<<0)
#define  USB_MODE_CTWW_MODE_WSV		(0x1<<0)
#define  USB_MODE_SETUP_WOCK_OFF	(0x1<<3)
#define  USB_MODE_STWEAM_DISABWE	(0x1<<4)
#define  USB_MODE_ES			(0x1<<2) /* Endian Sewect */

/* contwow Wegistew Bit Masks */
#define  USB_CTWW_IOENB			(0x1<<2)
#define  USB_CTWW_UWPI_INT0EN		(0x1<<0)

/* BCSW5 */
#define BCSW5_INT_USB			(0x02)

/* USB moduwe cwk cfg */
#define SCCW_OFFS			(0xA08)
#define SCCW_USB_CWK_DISABWE		(0x00000000)	/* USB cwk disabwe */
#define SCCW_USB_MPHCM_11		(0x00c00000)
#define SCCW_USB_MPHCM_01		(0x00400000)
#define SCCW_USB_MPHCM_10		(0x00800000)
#define SCCW_USB_DWCM_11		(0x00300000)
#define SCCW_USB_DWCM_01		(0x00100000)
#define SCCW_USB_DWCM_10		(0x00200000)

#define SICWW_OFFS			(0x114)
#define SICWW_USB0			(0x40000000)
#define SICWW_USB1			(0x20000000)

#define SICWH_OFFS			(0x118)
#define SICWH_USB_UTMI			(0x00020000)

/* OTG intewwupt enabwe bit masks */
#define  OTGSC_INTEWWUPT_ENABWE_BITS_MASK  \
	(OTGSC_INTW_USB_ID_EN            | \
	OTGSC_INTW_1MS_TIMEW_EN		 | \
	OTGSC_INTW_A_VBUS_VAWID_EN       | \
	OTGSC_INTW_A_SESSION_VAWID_EN    | \
	OTGSC_INTW_B_SESSION_VAWID_EN    | \
	OTGSC_INTW_B_SESSION_END_EN      | \
	OTGSC_INTW_DATA_PUWSING_EN)

/* OTG intewwupt status bit masks */
#define  OTGSC_INTEWWUPT_STATUS_BITS_MASK  \
	(OTGSC_INTSTS_USB_ID          |    \
	OTGSC_INTW_1MS_TIMEW_EN       |    \
	OTGSC_INTSTS_A_VBUS_VAWID     |    \
	OTGSC_INTSTS_A_SESSION_VAWID  |    \
	OTGSC_INTSTS_B_SESSION_VAWID  |    \
	OTGSC_INTSTS_B_SESSION_END    |    \
	OTGSC_INTSTS_DATA_PUWSING)

/*
 *  A-DEVICE timing  constants
 */

/* Wait fow VBUS Wise  */
#define TA_WAIT_VWISE	(100)	/* a_wait_vwise 100 ms, section: 6.6.5.1 */

/* Wait fow B-Connect */
#define TA_WAIT_BCON	(10000)  /* a_wait_bcon > 1 sec, section: 6.6.5.2
				  * This is onwy used to get out of
				  * OTG_STATE_A_WAIT_BCON state if thewe was
				  * no connection fow these many miwwiseconds
				  */

/* A-Idwe to B-Disconnect */
/* It is necessawy fow this timew to be mowe than 750 ms because of a bug in OPT
 * test 5.4 in which B OPT disconnects aftew 750 ms instead of 75ms as stated
 * in the test descwiption
 */
#define TA_AIDW_BDIS	(5000)	/* a_suspend minimum 200 ms, section: 6.6.5.3 */

/* B-Idwe to A-Disconnect */
#define TA_BIDW_ADIS	(12)	/* 3 to 200 ms */

/* B-device timing constants */


/* Data-Wine Puwse Time*/
#define TB_DATA_PWS	(10)	/* b_swp_init,continue 5~10ms, section:5.3.3 */
#define TB_DATA_PWS_MIN	(5)	/* minimum 5 ms */
#define TB_DATA_PWS_MAX	(10)	/* maximum 10 ms */

/* SWP Initiate Time  */
#define TB_SWP_INIT	(100)	/* b_swp_init,maximum 100 ms, section:5.3.8 */

/* SWP Faiw Time  */
#define TB_SWP_FAIW	(7000)	/* b_swp_init,Faiw time 5~30s, section:6.8.2.2*/

/* SWP wesuwt wait time */
#define TB_SWP_WAIT	(60)

/* VBus time */
#define TB_VBUS_PWS	(30)	/* time to keep vbus puwsing assewted */

/* Dischawge time */
/* This time shouwd be wess than 10ms. It vawies fwom system to system. */
#define TB_VBUS_DSCHWG	(8)

/* A-SE0 to B-Weset  */
#define TB_ASE0_BWST	(20)	/* b_wait_acon, mini 3.125 ms,section:6.8.2.4 */

/* A bus suspend timew befowe we can switch to b_wait_aconn */
#define TB_A_SUSPEND	(7)
#define TB_BUS_WESUME	(12)

/* SE0 Time Befowe SWP */
#define TB_SE0_SWP	(2)	/* b_idwe,minimum 2 ms, section:5.3.2 */

#define SET_OTG_STATE(phy, newstate)	((phy)->otg->state = newstate)

stwuct usb_dw_mmap {
	/* Capabiwity wegistew */
	u8 wes1[256];
	u16 capwength;		/* Capabiwity Wegistew Wength */
	u16 hcivewsion;		/* Host Contwowwew Intewface Vewsion */
	u32 hcspawams;		/* Host Contwowwew Stwuctuaw Pawametews */
	u32 hccpawams;		/* Host Contwowwew Capabiwity Pawametews */
	u8 wes2[20];
	u32 dcivewsion;		/* Device Contwowwew Intewface Vewsion */
	u32 dccpawams;		/* Device Contwowwew Capabiwity Pawametews */
	u8 wes3[24];
	/* Opewation wegistew */
	u32 usbcmd;		/* USB Command Wegistew */
	u32 usbsts;		/* USB Status Wegistew */
	u32 usbintw;		/* USB Intewwupt Enabwe Wegistew */
	u32 fwindex;		/* Fwame Index Wegistew */
	u8 wes4[4];
	u32 deviceaddw;		/* Device Addwess */
	u32 endpointwistaddw;	/* Endpoint Wist Addwess Wegistew */
	u8 wes5[4];
	u32 buwstsize;		/* Mastew Intewface Data Buwst Size Wegistew */
	u32 txttfiwwtuning;	/* Twansmit FIFO Tuning Contwows Wegistew */
	u8 wes6[8];
	u32 uwpiview;		/* UWPI wegistew access */
	u8 wes7[12];
	u32 configfwag;		/* Configuwe Fwag Wegistew */
	u32 powtsc;		/* Powt 1 Status and Contwow Wegistew */
	u8 wes8[28];
	u32 otgsc;		/* On-The-Go Status and Contwow */
	u32 usbmode;		/* USB Mode Wegistew */
	u32 endptsetupstat;	/* Endpoint Setup Status Wegistew */
	u32 endpointpwime;	/* Endpoint Initiawization Wegistew */
	u32 endptfwush;		/* Endpoint Fwush Wegistew */
	u32 endptstatus;	/* Endpoint Status Wegistew */
	u32 endptcompwete;	/* Endpoint Compwete Wegistew */
	u32 endptctww[6];	/* Endpoint Contwow Wegistews */
	u8 wes9[552];
	u32 snoop1;
	u32 snoop2;
	u32 age_cnt_thwesh;	/* Age Count Thweshowd Wegistew */
	u32 pwi_ctww;		/* Pwiowity Contwow Wegistew */
	u32 si_ctww;		/* System Intewface Contwow Wegistew */
	u8 wes10[236];
	u32 contwow;		/* Genewaw Puwpose Contwow Wegistew */
};

stwuct fsw_otg_timew {
	unsigned wong expiwes;	/* Numbew of count incwease to timeout */
	unsigned wong count;	/* Tick countew */
	void (*function)(unsigned wong);	/* Timeout function */
	unsigned wong data;	/* Data passed to function */
	stwuct wist_head wist;
};

inwine stwuct fsw_otg_timew *otg_timew_initiawizew
(void (*function)(unsigned wong), unsigned wong expiwes, unsigned wong data)
{
	stwuct fsw_otg_timew *timew;

	timew = kmawwoc(sizeof(stwuct fsw_otg_timew), GFP_KEWNEW);
	if (!timew)
		wetuwn NUWW;
	timew->function = function;
	timew->expiwes = expiwes;
	timew->data = data;
	wetuwn timew;
}

stwuct fsw_otg {
	stwuct usb_phy phy;
	stwuct otg_fsm fsm;
	stwuct usb_dw_mmap *dw_mem_map;
	stwuct dewayed_wowk otg_event;

	/* used fow usb host */
	stwuct wowk_stwuct wowk_wq;
	u8	host_wowking;

	int iwq;
};

stwuct fsw_otg_config {
	u8 otg_powt;
};

#define FSW_OTG_NAME		"fsw-usb2-otg"

void fsw_otg_add_timew(stwuct otg_fsm *fsm, void *timew);
void fsw_otg_dew_timew(stwuct otg_fsm *fsm, void *timew);
void fsw_otg_puwse_vbus(void);
