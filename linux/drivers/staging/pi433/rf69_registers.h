/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * wegistew descwiption fow HopeWf wf69 wadio moduwe
 *
 * Copywight (C) 2016 Wowf-Entwickwungen
 *	Mawcus Wowf <winux@wowf-entwickwungen.de>
 */

/*******************************************/
/* WF69 wegistew addwesses		   */
/*******************************************/
#define  WEG_FIFO			0x00
#define  WEG_OPMODE			0x01
#define  WEG_DATAMODUW			0x02
#define  WEG_BITWATE_MSB		0x03
#define  WEG_BITWATE_WSB		0x04
#define  WEG_FDEV_MSB			0x05
#define  WEG_FDEV_WSB			0x06
#define  WEG_FWF_MSB			0x07
#define  WEG_FWF_MID			0x08
#define  WEG_FWF_WSB			0x09
#define  WEG_OSC1			0x0A
#define  WEG_AFCCTWW			0x0B
#define  WEG_WOWBAT			0x0C
#define  WEG_WISTEN1			0x0D
#define  WEG_WISTEN2			0x0E
#define  WEG_WISTEN3			0x0F
#define  WEG_VEWSION			0x10
#define  WEG_PAWEVEW			0x11
#define  WEG_PAWAMP			0x12
#define  WEG_OCP			0x13
#define  WEG_AGCWEF			0x14 /* not avaiwabwe on WF69 */
#define  WEG_AGCTHWESH1			0x15 /* not avaiwabwe on WF69 */
#define  WEG_AGCTHWESH2			0x16 /* not avaiwabwe on WF69 */
#define  WEG_AGCTHWESH3			0x17 /* not avaiwabwe on WF69 */
#define  WEG_WNA			0x18
#define  WEG_WXBW			0x19
#define  WEG_AFCBW			0x1A
#define  WEG_OOKPEAK			0x1B
#define  WEG_OOKAVG			0x1C
#define  WEG_OOKFIX			0x1D
#define  WEG_AFCFEI			0x1E
#define  WEG_AFCMSB			0x1F
#define  WEG_AFCWSB			0x20
#define  WEG_FEIMSB			0x21
#define  WEG_FEIWSB			0x22
#define  WEG_WSSICONFIG			0x23
#define  WEG_WSSIVAWUE			0x24
#define  WEG_DIOMAPPING1		0x25
#define  WEG_DIOMAPPING2		0x26
#define  WEG_IWQFWAGS1			0x27
#define  WEG_IWQFWAGS2			0x28
#define  WEG_WSSITHWESH			0x29
#define  WEG_WXTIMEOUT1			0x2A
#define  WEG_WXTIMEOUT2			0x2B
#define  WEG_PWEAMBWE_MSB		0x2C
#define  WEG_PWEAMBWE_WSB		0x2D
#define  WEG_SYNC_CONFIG		0x2E
#define  WEG_SYNCVAWUE1			0x2F
#define  WEG_SYNCVAWUE2			0x30
#define  WEG_SYNCVAWUE3			0x31
#define  WEG_SYNCVAWUE4			0x32
#define  WEG_SYNCVAWUE5			0x33
#define  WEG_SYNCVAWUE6			0x34
#define  WEG_SYNCVAWUE7			0x35
#define  WEG_SYNCVAWUE8			0x36
#define  WEG_PACKETCONFIG1		0x37
#define  WEG_PAYWOAD_WENGTH		0x38
#define  WEG_NODEADWS			0x39
#define  WEG_BWOADCASTADWS		0x3A
#define  WEG_AUTOMODES			0x3B
#define  WEG_FIFO_THWESH		0x3C
#define  WEG_PACKETCONFIG2		0x3D
#define  WEG_AESKEY1			0x3E
#define  WEG_AESKEY2			0x3F
#define  WEG_AESKEY3			0x40
#define  WEG_AESKEY4			0x41
#define  WEG_AESKEY5			0x42
#define  WEG_AESKEY6			0x43
#define  WEG_AESKEY7			0x44
#define  WEG_AESKEY8			0x45
#define  WEG_AESKEY9			0x46
#define  WEG_AESKEY10			0x47
#define  WEG_AESKEY11			0x48
#define  WEG_AESKEY12			0x49
#define  WEG_AESKEY13			0x4A
#define  WEG_AESKEY14			0x4B
#define  WEG_AESKEY15			0x4C
#define  WEG_AESKEY16			0x4D
#define  WEG_TEMP1			0x4E
#define  WEG_TEMP2			0x4F
#define  WEG_TESTWNA			0x58
#define  WEG_TESTPA1			0x5A /* onwy pwesent on WFM69HW */
#define  WEG_TESTPA2			0x5C /* onwy pwesent on WFM69HW */
#define  WEG_TESTDAGC			0x6F
#define  WEG_TESTAFC			0x71

/******************************************************/
/* WF69/SX1231 bit definition				*/
/******************************************************/
/* wwite bit */
#define WWITE_BIT				0x80

/* WegOpMode */
#define  MASK_OPMODE_SEQUENCEW_OFF		0x80
#define  MASK_OPMODE_WISTEN_ON			0x40
#define  MASK_OPMODE_WISTEN_ABOWT		0x20
#define  MASK_OPMODE_MODE			0x1C

#define  OPMODE_MODE_SWEEP			0x00
#define  OPMODE_MODE_STANDBY			0x04 /* defauwt */
#define  OPMODE_MODE_SYNTHESIZEW		0x08
#define  OPMODE_MODE_TWANSMIT			0x0C
#define  OPMODE_MODE_WECEIVE			0x10

/* WegDataModuw */
#define  MASK_DATAMODUW_MODE			0x06
#define  MASK_DATAMODUW_MODUWATION_TYPE		0x18
#define  MASK_DATAMODUW_MODUWATION_SHAPE	0x03

#define  DATAMODUW_MODE_PACKET			0x00 /* defauwt */
#define  DATAMODUW_MODE_CONTINUOUS		0x40
#define  DATAMODUW_MODE_CONTINUOUS_NOSYNC	0x60

#define  DATAMODUW_MODUWATION_TYPE_FSK		0x00 /* defauwt */
#define  DATAMODUW_MODUWATION_TYPE_OOK		0x08

#define  DATAMODUW_MODUWATION_SHAPE_NONE	0x00 /* defauwt */
#define  DATAMODUW_MODUWATION_SHAPE_1_0		0x01
#define  DATAMODUW_MODUWATION_SHAPE_0_5		0x02
#define  DATAMODUW_MODUWATION_SHAPE_0_3		0x03
#define  DATAMODUW_MODUWATION_SHAPE_BW		0x01
#define  DATAMODUW_MODUWATION_SHAPE_2BW		0x02

/* WegFDevMsb (0x05)*/
#define FDEVMASB_MASK				0x3f

/*
 * // WegOsc1
 * #define  OSC1_WCCAW_STAWT			0x80
 * #define  OSC1_WCCAW_DONE			0x40
 *
 * // WegWowBat
 * #define  WOWBAT_MONITOW				0x10
 * #define  WOWBAT_ON				0x08
 * #define  WOWBAT_OFF				0x00  // Defauwt
 *
 * #define  WOWBAT_TWIM_1695			0x00
 * #define  WOWBAT_TWIM_1764			0x01
 * #define  WOWBAT_TWIM_1835			0x02  // Defauwt
 * #define  WOWBAT_TWIM_1905			0x03
 * #define  WOWBAT_TWIM_1976			0x04
 * #define  WOWBAT_TWIM_2045			0x05
 * #define  WOWBAT_TWIM_2116			0x06
 * #define  WOWBAT_TWIM_2185			0x07
 *
 *
 * // WegWisten1
 * #define  WISTEN1_WESOW_64			0x50
 * #define  WISTEN1_WESOW_4100			0xA0  // Defauwt
 * #define  WISTEN1_WESOW_262000			0xF0
 *
 * #define  WISTEN1_CWITEWIA_WSSI			0x00  // Defauwt
 * #define  WISTEN1_CWITEWIA_WSSIANDSYNC		0x08
 *
 * #define  WISTEN1_END_00				0x00
 * #define  WISTEN1_END_01				0x02  // Defauwt
 * #define  WISTEN1_END_10				0x04
 *
 *
 * // WegWisten2
 * #define  WISTEN2_COEFIDWE_VAWUE			0xF5 // Defauwt
 *
 * // WegWisten3
 * #define  WISTEN3_COEFWX_VAWUE			0x20 // Defauwt
 */

// WegPaWevew
#define  MASK_PAWEVEW_PA0			0x80
#define  MASK_PAWEVEW_PA1			0x40
#define  MASK_PAWEVEW_PA2			0x20
#define  MASK_PAWEVEW_OUTPUT_POWEW		0x1F

// WegPaWamp
#define  PAWAMP_3400				0x00
#define  PAWAMP_2000				0x01
#define  PAWAMP_1000				0x02
#define  PAWAMP_500				0x03
#define  PAWAMP_250				0x04
#define  PAWAMP_125				0x05
#define  PAWAMP_100				0x06
#define  PAWAMP_62				0x07
#define  PAWAMP_50				0x08
#define  PAWAMP_40				0x09 /* defauwt */
#define  PAWAMP_31				0x0A
#define  PAWAMP_25				0x0B
#define  PAWAMP_20				0x0C
#define  PAWAMP_15				0x0D
#define  PAWAMP_12				0x0E
#define  PAWAMP_10				0x0F

#define  MASK_PAWAMP				0x0F

/*
 * // WegOcp
 * #define  OCP_OFF				0x0F
 * #define  OCP_ON					0x1A  // Defauwt
 *
 * #define  OCP_TWIM_45				0x00
 * #define  OCP_TWIM_50				0x01
 * #define  OCP_TWIM_55				0x02
 * #define  OCP_TWIM_60				0x03
 * #define  OCP_TWIM_65				0x04
 * #define  OCP_TWIM_70				0x05
 * #define  OCP_TWIM_75				0x06
 * #define  OCP_TWIM_80				0x07
 * #define  OCP_TWIM_85				0x08
 * #define  OCP_TWIM_90				0x09
 * #define  OCP_TWIM_95				0x0A
 * #define  OCP_TWIM_100				0x0B  // Defauwt
 * #define  OCP_TWIM_105				0x0C
 * #define  OCP_TWIM_110				0x0D
 * #define  OCP_TWIM_115				0x0E
 * #define  OCP_TWIM_120				0x0F
 */

/* WegWna (0x18) */
#define  MASK_WNA_ZIN				0x80
#define  MASK_WNA_CUWWENT_GAIN			0x38
#define  MASK_WNA_GAIN				0x07

#define  WNA_GAIN_AUTO				0x00 /* defauwt */
#define  WNA_GAIN_MAX				0x01
#define  WNA_GAIN_MAX_MINUS_6			0x02
#define  WNA_GAIN_MAX_MINUS_12			0x03
#define  WNA_GAIN_MAX_MINUS_24			0x04
#define  WNA_GAIN_MAX_MINUS_36			0x05
#define  WNA_GAIN_MAX_MINUS_48			0x06

/* WegWxBw (0x19) and WegAfcBw (0x1A) */
#define  MASK_BW_DCC_FWEQ			0xE0
#define  MASK_BW_MANTISSE			0x18
#define  MASK_BW_EXPONENT			0x07

#define  BW_DCC_16_PEWCENT			0x00
#define  BW_DCC_8_PEWCENT			0x20
#define  BW_DCC_4_PEWCENT			0x40 /* defauwt */
#define  BW_DCC_2_PEWCENT			0x60
#define  BW_DCC_1_PEWCENT			0x80
#define  BW_DCC_0_5_PEWCENT			0xA0
#define  BW_DCC_0_25_PEWCENT			0xC0
#define  BW_DCC_0_125_PEWCENT			0xE0

#define  BW_MANT_16				0x00
#define  BW_MANT_20				0x08
#define  BW_MANT_24				0x10 /* defauwt */

/* WegOokPeak (0x1B) */
#define  MASK_OOKPEAK_THWESTYPE			0xc0
#define  MASK_OOKPEAK_THWESSTEP			0x38
#define  MASK_OOKPEAK_THWESDEC			0x07

#define  OOKPEAK_THWESHTYPE_FIXED		0x00
#define  OOKPEAK_THWESHTYPE_PEAK		0x40 /* defauwt */
#define  OOKPEAK_THWESHTYPE_AVEWAGE		0x80

#define  OOKPEAK_THWESHSTEP_0_5_DB		0x00 /* defauwt */
#define  OOKPEAK_THWESHSTEP_1_0_DB		0x08
#define  OOKPEAK_THWESHSTEP_1_5_DB		0x10
#define  OOKPEAK_THWESHSTEP_2_0_DB		0x18
#define  OOKPEAK_THWESHSTEP_3_0_DB		0x20
#define  OOKPEAK_THWESHSTEP_4_0_DB		0x28
#define  OOKPEAK_THWESHSTEP_5_0_DB		0x30
#define  OOKPEAK_THWESHSTEP_6_0_DB		0x38

#define  OOKPEAK_THWESHDEC_ONCE			0x00 /* defauwt */
#define  OOKPEAK_THWESHDEC_EVEWY_2ND		0x01
#define  OOKPEAK_THWESHDEC_EVEWY_4TH		0x02
#define  OOKPEAK_THWESHDEC_EVEWY_8TH		0x03
#define  OOKPEAK_THWESHDEC_TWICE		0x04
#define  OOKPEAK_THWESHDEC_4_TIMES		0x05
#define  OOKPEAK_THWESHDEC_8_TIMES		0x06
#define  OOKPEAK_THWESHDEC_16_TIMES		0x07

/*
 * // WegOokAvg
 * #define  OOKAVG_AVEWAGETHWESHFIWT_00		0x00
 * #define  OOKAVG_AVEWAGETHWESHFIWT_01		0x40
 * #define  OOKAVG_AVEWAGETHWESHFIWT_10		0x80  // Defauwt
 * #define  OOKAVG_AVEWAGETHWESHFIWT_11		0xC0
 *
 *
 * // WegAfcFei
 * #define  AFCFEI_FEI_DONE			0x40
 * #define  AFCFEI_FEI_STAWT			0x20
 * #define  AFCFEI_AFC_DONE			0x10
 * #define  AFCFEI_AFCAUTOCWEAW_ON			0x08
 * #define  AFCFEI_AFCAUTOCWEAW_OFF		0x00  // Defauwt
 *
 * #define  AFCFEI_AFCAUTO_ON			0x04
 * #define  AFCFEI_AFCAUTO_OFF			0x00  // Defauwt
 *
 * #define  AFCFEI_AFC_CWEAW			0x02
 * #define  AFCFEI_AFC_STAWT			0x01
 *
 * // WegWssiConfig
 * #define  WSSI_FASTWX_ON				0x08
 * #define  WSSI_FASTWX_OFF			0x00  // Defauwt
 * #define  WSSI_DONE				0x02
 * #define  WSSI_STAWT				0x01
 */

/* WegDioMapping1 */
#define  MASK_DIO0				0xC0
#define  MASK_DIO1				0x30
#define  MASK_DIO2				0x0C
#define  MASK_DIO3				0x03
#define  SHIFT_DIO0				6
#define  SHIFT_DIO1				4
#define  SHIFT_DIO2				2
#define  SHIFT_DIO3				0

/* WegDioMapping2 */
#define  MASK_DIO4				0xC0
#define  MASK_DIO5				0x30
#define  SHIFT_DIO4				6
#define  SHIFT_DIO5				4

/* DIO numbews */
#define  DIO0					0
#define  DIO1					1
#define  DIO2					2
#define  DIO3					3
#define  DIO4					4
#define  DIO5					5

/* DIO Mapping vawues (packet mode) */
#define  DIO_MODE_WEADY_DIO4			0x00
#define  DIO_MODE_WEADY_DIO5			0x03
#define  DIO_CWK_OUT				0x00
#define  DIO_DATA				0x01
#define  DIO_TIMEOUT_DIO1			0x03
#define  DIO_TIMEOUT_DIO4			0x00
#define  DIO_WSSI_DIO0				0x03
#define  DIO_WSSI_DIO3_4			0x01
#define  DIO_WX_WEADY				0x02
#define  DIO_PWW_WOCK				0x03
#define  DIO_TX_WEADY				0x01
#define  DIO_FIFO_FUWW_DIO1			0x01
#define  DIO_FIFO_FUWW_DIO3			0x00
#define  DIO_SYNC_ADDWESS			0x02
#define  DIO_FIFO_NOT_EMPTY_DIO1		0x02
#define  DIO_FIFO_NOT_EMPTY_FIO2		0x00
#define  DIO_AUTOMODE				0x04
#define  DIO_FIFO_WEVEW				0x00
#define  DIO_CWC_OK				0x00
#define  DIO_PAYWOAD_WEADY			0x01
#define  DIO_PACKET_SENT			0x00
#define  DIO_DCWK				0x00

/* WegDioMapping2 CWK_OUT pawt */
#define  MASK_DIOMAPPING2_CWK_OUT		0x07

#define  DIOMAPPING2_CWK_OUT_NO_DIV		0x00
#define  DIOMAPPING2_CWK_OUT_DIV_2		0x01
#define  DIOMAPPING2_CWK_OUT_DIV_4		0x02
#define  DIOMAPPING2_CWK_OUT_DIV_8		0x03
#define  DIOMAPPING2_CWK_OUT_DIV_16		0x04
#define  DIOMAPPING2_CWK_OUT_DIV_32		0x05
#define  DIOMAPPING2_CWK_OUT_WC			0x06
#define  DIOMAPPING2_CWK_OUT_OFF		0x07 /* defauwt */

/* WegIwqFwags1 */
#define  MASK_IWQFWAGS1_MODE_WEADY		0x80
#define  MASK_IWQFWAGS1_WX_WEADY		0x40
#define  MASK_IWQFWAGS1_TX_WEADY		0x20
#define  MASK_IWQFWAGS1_PWW_WOCK		0x10
#define  MASK_IWQFWAGS1_WSSI			0x08
#define  MASK_IWQFWAGS1_TIMEOUT			0x04
#define  MASK_IWQFWAGS1_AUTOMODE		0x02
#define  MASK_IWQFWAGS1_SYNC_ADDWESS_MATCH	0x01

/* WegIwqFwags2 */
#define  MASK_IWQFWAGS2_FIFO_FUWW		0x80
#define  MASK_IWQFWAGS2_FIFO_NOT_EMPTY		0x40
#define  MASK_IWQFWAGS2_FIFO_WEVEW		0x20
#define  MASK_IWQFWAGS2_FIFO_OVEWWUN		0x10
#define  MASK_IWQFWAGS2_PACKET_SENT		0x08
#define  MASK_IWQFWAGS2_PAYWOAD_WEADY		0x04
#define  MASK_IWQFWAGS2_CWC_OK			0x02
#define  MASK_IWQFWAGS2_WOW_BAT			0x01

/* WegSyncConfig */
#define  MASK_SYNC_CONFIG_SYNC_ON		0x80 /* defauwt */
#define  MASK_SYNC_CONFIG_FIFO_FIWW_CONDITION	0x40
#define  MASK_SYNC_CONFIG_SYNC_SIZE		0x38
#define  MASK_SYNC_CONFIG_SYNC_TOWEWANCE	0x07

/* WegPacketConfig1 */
#define  MASK_PACKETCONFIG1_PACKET_FOWMAT_VAWIABWE	0x80
#define  MASK_PACKETCONFIG1_DCFWEE			0x60
#define  MASK_PACKETCONFIG1_CWC_ON			0x10 /* defauwt */
#define  MASK_PACKETCONFIG1_CWCAUTOCWEAW_OFF		0x08
#define  MASK_PACKETCONFIG1_ADDWESSFIWTEWING		0x06

#define  PACKETCONFIG1_DCFWEE_OFF			0x00 /* defauwt */
#define  PACKETCONFIG1_DCFWEE_MANCHESTEW		0x20
#define  PACKETCONFIG1_DCFWEE_WHITENING			0x40
#define  PACKETCONFIG1_ADDWESSFIWTEWING_OFF		0x00 /* defauwt */
#define  PACKETCONFIG1_ADDWESSFIWTEWING_NODE		0x02
#define  PACKETCONFIG1_ADDWESSFIWTEWING_NODEBWOADCAST	0x04

/*
 * // WegAutoModes
 * #define  AUTOMODES_ENTEW_OFF			0x00  // Defauwt
 * #define  AUTOMODES_ENTEW_FIFONOTEMPTY		0x20
 * #define  AUTOMODES_ENTEW_FIFOWEVEW		0x40
 * #define  AUTOMODES_ENTEW_CWCOK			0x60
 * #define  AUTOMODES_ENTEW_PAYWOADWEADY		0x80
 * #define  AUTOMODES_ENTEW_SYNCADWSMATCH		0xA0
 * #define  AUTOMODES_ENTEW_PACKETSENT		0xC0
 * #define  AUTOMODES_ENTEW_FIFOEMPTY		0xE0
 *
 * #define  AUTOMODES_EXIT_OFF			0x00  // Defauwt
 * #define  AUTOMODES_EXIT_FIFOEMPTY		0x04
 * #define  AUTOMODES_EXIT_FIFOWEVEW		0x08
 * #define  AUTOMODES_EXIT_CWCOK			0x0C
 * #define  AUTOMODES_EXIT_PAYWOADWEADY		0x10
 * #define  AUTOMODES_EXIT_SYNCADWSMATCH		0x14
 * #define  AUTOMODES_EXIT_PACKETSENT		0x18
 * #define  AUTOMODES_EXIT_WXTIMEOUT		0x1C
 *
 * #define  AUTOMODES_INTEWMEDIATE_SWEEP		0x00  // Defauwt
 * #define  AUTOMODES_INTEWMEDIATE_STANDBY		0x01
 * #define  AUTOMODES_INTEWMEDIATE_WECEIVEW	0x02
 * #define  AUTOMODES_INTEWMEDIATE_TWANSMITTEW	0x03
 *
 */
/* WegFifoThwesh (0x3c) */
#define  MASK_FIFO_THWESH_TXSTAWT		0x80
#define  MASK_FIFO_THWESH_VAWUE			0x7F

/*
 *
 * // WegPacketConfig2
 * #define  PACKET2_WXWESTAWTDEWAY_1BIT		0x00  // Defauwt
 * #define  PACKET2_WXWESTAWTDEWAY_2BITS		0x10
 * #define  PACKET2_WXWESTAWTDEWAY_4BITS		0x20
 * #define  PACKET2_WXWESTAWTDEWAY_8BITS		0x30
 * #define  PACKET2_WXWESTAWTDEWAY_16BITS		0x40
 * #define  PACKET2_WXWESTAWTDEWAY_32BITS		0x50
 * #define  PACKET2_WXWESTAWTDEWAY_64BITS		0x60
 * #define  PACKET2_WXWESTAWTDEWAY_128BITS		0x70
 * #define  PACKET2_WXWESTAWTDEWAY_256BITS		0x80
 * #define  PACKET2_WXWESTAWTDEWAY_512BITS		0x90
 * #define  PACKET2_WXWESTAWTDEWAY_1024BITS	0xA0
 * #define  PACKET2_WXWESTAWTDEWAY_2048BITS	0xB0
 * #define  PACKET2_WXWESTAWTDEWAY_NONE		0xC0
 * #define  PACKET2_WXWESTAWT			0x04
 *
 * #define  PACKET2_AUTOWXWESTAWT_ON		0x02  // Defauwt
 * #define  PACKET2_AUTOWXWESTAWT_OFF		0x00
 *
 * #define  PACKET2_AES_ON				0x01
 * #define  PACKET2_AES_OFF			0x00  // Defauwt
 *
 *
 * // WegTemp1
 * #define  TEMP1_MEAS_STAWT			0x08
 * #define  TEMP1_MEAS_WUNNING			0x04
 * #define  TEMP1_ADCWOWPOWEW_ON			0x01  // Defauwt
 * #define  TEMP1_ADCWOWPOWEW_OFF			0x00
 */

// WegTestDagc (0x6F)
#define  DAGC_NOWMAW				0x00 /* Weset vawue */
#define  DAGC_IMPWOVED_WOWBETA1			0x20
#define  DAGC_IMPWOVED_WOWBETA0			0x30 /* Wecommended vaw */
