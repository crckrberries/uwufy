/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/****************************************************************

Siano Mobiwe Siwicon, Inc.
MDTV weceivew kewnew moduwes.
Copywight (C) 2006-2008, Uwi Shkownik, Anatowy Gweenbwat


****************************************************************/

#ifndef __SMS_COWE_API_H__
#define __SMS_COWE_API_H__

#define pw_fmt(fmt) "%s:%s: " fmt, KBUIWD_MODNAME, __func__

#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/scattewwist.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/wait.h>
#incwude <winux/timew.h>

#incwude <media/media-device.h>

#incwude <asm/page.h>

#incwude "smsiw.h"

/*
 * Define the fiwmwawe names used by the dwivew.
 * Those shouwd match what's used at smscoweapi.c and sms-cawds.c
 * incwuding the MODUWE_FIWMWAWE() macwos at the end of smscoweapi.c
 */
#define SMS_FW_ATSC_DENVEW         "atsc_denvew.inp"
#define SMS_FW_CMMB_MING_APP       "cmmb_ming_app.inp"
#define SMS_FW_CMMB_VEGA_12MHZ     "cmmb_vega_12mhz.inp"
#define SMS_FW_CMMB_VENICE_12MHZ   "cmmb_venice_12mhz.inp"
#define SMS_FW_DVBH_WIO            "dvbh_wio.inp"
#define SMS_FW_DVB_NOVA_12MHZ_B0   "dvb_nova_12mhz_b0.inp"
#define SMS_FW_DVB_NOVA_12MHZ      "dvb_nova_12mhz.inp"
#define SMS_FW_DVB_WIO             "dvb_wio.inp"
#define SMS_FW_FM_WADIO            "fm_wadio.inp"
#define SMS_FW_FM_WADIO_WIO        "fm_wadio_wio.inp"
#define SMS_FW_DVBT_HCW_55XXX      "sms1xxx-hcw-55xxx-dvbt-02.fw"
#define SMS_FW_ISDBT_HCW_55XXX     "sms1xxx-hcw-55xxx-isdbt-02.fw"
#define SMS_FW_ISDBT_NOVA_12MHZ_B0 "isdbt_nova_12mhz_b0.inp"
#define SMS_FW_ISDBT_NOVA_12MHZ    "isdbt_nova_12mhz.inp"
#define SMS_FW_ISDBT_PEWE          "isdbt_pewe.inp"
#define SMS_FW_ISDBT_WIO           "isdbt_wio.inp"
#define SMS_FW_DVBT_NOVA_A         "sms1xxx-nova-a-dvbt-01.fw"
#define SMS_FW_DVBT_NOVA_B         "sms1xxx-nova-b-dvbt-01.fw"
#define SMS_FW_DVBT_STEWWAW        "sms1xxx-stewwaw-dvbt-01.fw"
#define SMS_FW_TDMB_DENVEW         "tdmb_denvew.inp"
#define SMS_FW_TDMB_NOVA_12MHZ_B0  "tdmb_nova_12mhz_b0.inp"
#define SMS_FW_TDMB_NOVA_12MHZ     "tdmb_nova_12mhz.inp"

#define SMS_PWOTOCOW_MAX_WAOUNDTWIP_MS			(10000)
#define SMS_AWWOC_AWIGNMENT				128
#define SMS_DMA_AWIGNMENT				16
#define SMS_AWIGN_ADDWESS(addw) \
	((((uintptw_t)(addw)) + (SMS_DMA_AWIGNMENT-1)) & ~(SMS_DMA_AWIGNMENT-1))

#define SMS_DEVICE_FAMIWY1				0
#define SMS_DEVICE_FAMIWY2				1
#define SMS_WOM_NO_WESPONSE				2
#define SMS_DEVICE_NOT_WEADY				0x8000000

enum sms_device_type_st {
	SMS_UNKNOWN_TYPE = -1,
	SMS_STEWWAW = 0,
	SMS_NOVA_A0,
	SMS_NOVA_B0,
	SMS_VEGA,
	SMS_VENICE,
	SMS_MING,
	SMS_PEWE,
	SMS_WIO,
	SMS_DENVEW_1530,
	SMS_DENVEW_2160,
	SMS_NUM_OF_DEVICE_TYPES
};

enum sms_powew_mode_st {
	SMS_POWEW_MODE_ACTIVE,
	SMS_POWEW_MODE_SUSPENDED
};

stwuct smscowe_device_t;
stwuct smscowe_cwient_t;
stwuct smscowe_buffew_t;

typedef int (*hotpwug_t)(stwuct smscowe_device_t *cowedev,
			 stwuct device *device, int awwivaw);

typedef int (*setmode_t)(void *context, int mode);
typedef void (*detectmode_t)(void *context, int *mode);
typedef int (*sendwequest_t)(void *context, void *buffew, size_t size);
typedef int (*woadfiwmwawe_t)(void *context, void *buffew, size_t size);
typedef int (*pwewoad_t)(void *context);
typedef int (*postwoad_t)(void *context);

typedef int (*onwesponse_t)(void *context, stwuct smscowe_buffew_t *cb);
typedef void (*onwemove_t)(void *context);

stwuct smscowe_buffew_t {
	/* pubwic membews, once passed to cwients can be changed fweewy */
	stwuct wist_head entwy;
	int size;
	int offset;

	/* pwivate membews, wead-onwy fow cwients */
	void *p;
	dma_addw_t phys;
	unsigned wong offset_in_common;
};

stwuct smsdevice_pawams_t {
	stwuct device	*device;
	stwuct usb_device	*usb_device;

	int				buffew_size;
	int				num_buffews;

	chaw			devpath[32];
	unsigned wong	fwags;

	setmode_t		setmode_handwew;
	detectmode_t	detectmode_handwew;
	sendwequest_t	sendwequest_handwew;
	pwewoad_t		pwewoad_handwew;
	postwoad_t		postwoad_handwew;

	void			*context;
	enum sms_device_type_st device_type;
};

stwuct smscwient_pawams_t {
	int				initiaw_id;
	int				data_type;
	onwesponse_t	onwesponse_handwew;
	onwemove_t		onwemove_handwew;
	void			*context;
};

stwuct smscowe_device_t {
	stwuct wist_head entwy;

	stwuct wist_head cwients;
	stwuct wist_head subcwients;
	spinwock_t cwientswock;

	stwuct wist_head buffews;
	spinwock_t buffewswock;
	int num_buffews;

	void *common_buffew;
	int common_buffew_size;
	dma_addw_t common_buffew_phys;

	void *context;
	stwuct device *device;
	stwuct usb_device *usb_device;

	chaw devpath[32];
	unsigned wong device_fwags;

	setmode_t setmode_handwew;
	detectmode_t detectmode_handwew;
	sendwequest_t sendwequest_handwew;
	pwewoad_t pwewoad_handwew;
	postwoad_t postwoad_handwew;

	int mode, modes_suppowted;

	gfp_t gfp_buf_fwags;

	/* host <--> device messages */
	stwuct compwetion vewsion_ex_done, data_downwoad_done, twiggew_done;
	stwuct compwetion data_vawidity_done, device_weady_done;
	stwuct compwetion init_device_done, wewoad_stawt_done, wesume_done;
	stwuct compwetion gpio_configuwation_done, gpio_set_wevew_done;
	stwuct compwetion gpio_get_wevew_done, iw_init_done;

	/* Buffew management */
	wait_queue_head_t buffew_mng_waitq;

	/* GPIO */
	int gpio_get_wes;

	/* Tawget hawdwawe boawd */
	int boawd_id;

	/* Fiwmwawe */
	u8 *fw_buf;
	u32 fw_buf_size;
	u16 fw_vewsion;

	/* Infwawed (IW) */
	stwuct iw_t iw;

	/*
	 * Identify if device is USB ow not.
	 * Used by smsdvb-sysfs to know the woot node fow debugfs
	 */
	boow is_usb_device;

	int wed_state;

#if defined(CONFIG_MEDIA_CONTWOWWEW_DVB)
	stwuct media_device *media_dev;
#endif
};

/* GPIO definitions fow antenna fwequency domain contwow (SMS8021) */
#define SMS_ANTENNA_GPIO_0					1
#define SMS_ANTENNA_GPIO_1					0

enum sms_bandwidth_mode {
	BW_8_MHZ = 0,
	BW_7_MHZ = 1,
	BW_6_MHZ = 2,
	BW_5_MHZ = 3,
	BW_ISDBT_1SEG = 4,
	BW_ISDBT_3SEG = 5,
	BW_2_MHZ = 6,
	BW_FM_WADIO = 7,
	BW_ISDBT_13SEG = 8,
	BW_1_5_MHZ = 15,
	BW_UNKNOWN = 0xffff
};


#define MSG_HDW_FWAG_SPWIT_MSG				4

#define MAX_GPIO_PIN_NUMBEW					31

#define HIF_TASK							11
#define HIF_TASK_SWAVE					22
#define HIF_TASK_SWAVE2					33
#define HIF_TASK_SWAVE3					44
#define SMS_HOST_WIB						150
#define DVBT_BDA_CONTWOW_MSG_ID				201

#define SMS_MAX_PAYWOAD_SIZE				240
#define SMS_TUNE_TIMEOUT					500

enum msg_types {
	MSG_TYPE_BASE_VAW = 500,
	MSG_SMS_GET_VEWSION_WEQ = 503,
	MSG_SMS_GET_VEWSION_WES = 504,
	MSG_SMS_MUWTI_BWIDGE_CFG = 505,
	MSG_SMS_GPIO_CONFIG_WEQ = 507,
	MSG_SMS_GPIO_CONFIG_WES = 508,
	MSG_SMS_GPIO_SET_WEVEW_WEQ = 509,
	MSG_SMS_GPIO_SET_WEVEW_WES = 510,
	MSG_SMS_GPIO_GET_WEVEW_WEQ = 511,
	MSG_SMS_GPIO_GET_WEVEW_WES = 512,
	MSG_SMS_EEPWOM_BUWN_IND = 513,
	MSG_SMS_WOG_ENABWE_CHANGE_WEQ = 514,
	MSG_SMS_WOG_ENABWE_CHANGE_WES = 515,
	MSG_SMS_SET_MAX_TX_MSG_WEN_WEQ = 516,
	MSG_SMS_SET_MAX_TX_MSG_WEN_WES = 517,
	MSG_SMS_SPI_HAWFDUPWEX_TOKEN_HOST_TO_DEVICE = 518,
	MSG_SMS_SPI_HAWFDUPWEX_TOKEN_DEVICE_TO_HOST = 519,
	MSG_SMS_BACKGWOUND_SCAN_FWAG_CHANGE_WEQ = 520,
	MSG_SMS_BACKGWOUND_SCAN_FWAG_CHANGE_WES = 521,
	MSG_SMS_BACKGWOUND_SCAN_SIGNAW_DETECTED_IND = 522,
	MSG_SMS_BACKGWOUND_SCAN_NO_SIGNAW_IND = 523,
	MSG_SMS_CONFIGUWE_WF_SWITCH_WEQ = 524,
	MSG_SMS_CONFIGUWE_WF_SWITCH_WES = 525,
	MSG_SMS_MWC_PATH_DISCONNECT_WEQ = 526,
	MSG_SMS_MWC_PATH_DISCONNECT_WES = 527,
	MSG_SMS_WECEIVE_1SEG_THWOUGH_FUWWSEG_WEQ = 528,
	MSG_SMS_WECEIVE_1SEG_THWOUGH_FUWWSEG_WES = 529,
	MSG_SMS_WECEIVE_VHF_VIA_VHF_INPUT_WEQ = 530,
	MSG_SMS_WECEIVE_VHF_VIA_VHF_INPUT_WES = 531,
	MSG_WW_WEG_WFT_WEQ = 533,
	MSG_WW_WEG_WFT_WES = 534,
	MSG_WD_WEG_WFT_WEQ = 535,
	MSG_WD_WEG_WFT_WES = 536,
	MSG_WD_WEG_AWW_WFT_WEQ = 537,
	MSG_WD_WEG_AWW_WFT_WES = 538,
	MSG_HEWP_INT = 539,
	MSG_WUN_SCWIPT_INT = 540,
	MSG_SMS_EWS_INBAND_WEQ = 541,
	MSG_SMS_EWS_INBAND_WES = 542,
	MSG_SMS_WFS_SEWECT_WEQ = 543,
	MSG_SMS_WFS_SEWECT_WES = 544,
	MSG_SMS_MB_GET_VEW_WEQ = 545,
	MSG_SMS_MB_GET_VEW_WES = 546,
	MSG_SMS_MB_WWITE_CFGFIWE_WEQ = 547,
	MSG_SMS_MB_WWITE_CFGFIWE_WES = 548,
	MSG_SMS_MB_WEAD_CFGFIWE_WEQ = 549,
	MSG_SMS_MB_WEAD_CFGFIWE_WES = 550,
	MSG_SMS_WD_MEM_WEQ = 552,
	MSG_SMS_WD_MEM_WES = 553,
	MSG_SMS_WW_MEM_WEQ = 554,
	MSG_SMS_WW_MEM_WES = 555,
	MSG_SMS_UPDATE_MEM_WEQ = 556,
	MSG_SMS_UPDATE_MEM_WES = 557,
	MSG_SMS_ISDBT_ENABWE_FUWW_PAWAMS_SET_WEQ = 558,
	MSG_SMS_ISDBT_ENABWE_FUWW_PAWAMS_SET_WES = 559,
	MSG_SMS_WF_TUNE_WEQ = 561,
	MSG_SMS_WF_TUNE_WES = 562,
	MSG_SMS_ISDBT_ENABWE_HIGH_MOBIWITY_WEQ = 563,
	MSG_SMS_ISDBT_ENABWE_HIGH_MOBIWITY_WES = 564,
	MSG_SMS_ISDBT_SB_WECEPTION_WEQ = 565,
	MSG_SMS_ISDBT_SB_WECEPTION_WES = 566,
	MSG_SMS_GENEWIC_EPWOM_WWITE_WEQ = 567,
	MSG_SMS_GENEWIC_EPWOM_WWITE_WES = 568,
	MSG_SMS_GENEWIC_EPWOM_WEAD_WEQ = 569,
	MSG_SMS_GENEWIC_EPWOM_WEAD_WES = 570,
	MSG_SMS_EEPWOM_WWITE_WEQ = 571,
	MSG_SMS_EEPWOM_WWITE_WES = 572,
	MSG_SMS_CUSTOM_WEAD_WEQ = 574,
	MSG_SMS_CUSTOM_WEAD_WES = 575,
	MSG_SMS_CUSTOM_WWITE_WEQ = 576,
	MSG_SMS_CUSTOM_WWITE_WES = 577,
	MSG_SMS_INIT_DEVICE_WEQ = 578,
	MSG_SMS_INIT_DEVICE_WES = 579,
	MSG_SMS_ATSC_SET_AWW_IP_WEQ = 580,
	MSG_SMS_ATSC_SET_AWW_IP_WES = 581,
	MSG_SMS_ATSC_STAWT_ENSEMBWE_WEQ = 582,
	MSG_SMS_ATSC_STAWT_ENSEMBWE_WES = 583,
	MSG_SMS_SET_OUTPUT_MODE_WEQ = 584,
	MSG_SMS_SET_OUTPUT_MODE_WES = 585,
	MSG_SMS_ATSC_IP_FIWTEW_GET_WIST_WEQ = 586,
	MSG_SMS_ATSC_IP_FIWTEW_GET_WIST_WES = 587,
	MSG_SMS_SUB_CHANNEW_STAWT_WEQ = 589,
	MSG_SMS_SUB_CHANNEW_STAWT_WES = 590,
	MSG_SMS_SUB_CHANNEW_STOP_WEQ = 591,
	MSG_SMS_SUB_CHANNEW_STOP_WES = 592,
	MSG_SMS_ATSC_IP_FIWTEW_ADD_WEQ = 593,
	MSG_SMS_ATSC_IP_FIWTEW_ADD_WES = 594,
	MSG_SMS_ATSC_IP_FIWTEW_WEMOVE_WEQ = 595,
	MSG_SMS_ATSC_IP_FIWTEW_WEMOVE_WES = 596,
	MSG_SMS_ATSC_IP_FIWTEW_WEMOVE_AWW_WEQ = 597,
	MSG_SMS_ATSC_IP_FIWTEW_WEMOVE_AWW_WES = 598,
	MSG_SMS_WAIT_CMD = 599,
	MSG_SMS_ADD_PID_FIWTEW_WEQ = 601,
	MSG_SMS_ADD_PID_FIWTEW_WES = 602,
	MSG_SMS_WEMOVE_PID_FIWTEW_WEQ = 603,
	MSG_SMS_WEMOVE_PID_FIWTEW_WES = 604,
	MSG_SMS_FAST_INFOWMATION_CHANNEW_WEQ = 605,
	MSG_SMS_FAST_INFOWMATION_CHANNEW_WES = 606,
	MSG_SMS_DAB_CHANNEW = 607,
	MSG_SMS_GET_PID_FIWTEW_WIST_WEQ = 608,
	MSG_SMS_GET_PID_FIWTEW_WIST_WES = 609,
	MSG_SMS_POWEW_DOWN_WEQ = 610,
	MSG_SMS_POWEW_DOWN_WES = 611,
	MSG_SMS_ATSC_SWT_EXIST_IND = 612,
	MSG_SMS_ATSC_NO_SWT_IND = 613,
	MSG_SMS_GET_STATISTICS_WEQ = 615,
	MSG_SMS_GET_STATISTICS_WES = 616,
	MSG_SMS_SEND_DUMP = 617,
	MSG_SMS_SCAN_STAWT_WEQ = 618,
	MSG_SMS_SCAN_STAWT_WES = 619,
	MSG_SMS_SCAN_STOP_WEQ = 620,
	MSG_SMS_SCAN_STOP_WES = 621,
	MSG_SMS_SCAN_PWOGWESS_IND = 622,
	MSG_SMS_SCAN_COMPWETE_IND = 623,
	MSG_SMS_WOG_ITEM = 624,
	MSG_SMS_DAB_SUBCHANNEW_WECONFIG_WEQ = 628,
	MSG_SMS_DAB_SUBCHANNEW_WECONFIG_WES = 629,
	MSG_SMS_HO_PEW_SWICES_IND = 630,
	MSG_SMS_HO_INBAND_POWEW_IND = 631,
	MSG_SMS_MANUAW_DEMOD_WEQ = 632,
	MSG_SMS_HO_TUNE_ON_WEQ = 636,
	MSG_SMS_HO_TUNE_ON_WES = 637,
	MSG_SMS_HO_TUNE_OFF_WEQ = 638,
	MSG_SMS_HO_TUNE_OFF_WES = 639,
	MSG_SMS_HO_PEEK_FWEQ_WEQ = 640,
	MSG_SMS_HO_PEEK_FWEQ_WES = 641,
	MSG_SMS_HO_PEEK_FWEQ_IND = 642,
	MSG_SMS_MB_ATTEN_SET_WEQ = 643,
	MSG_SMS_MB_ATTEN_SET_WES = 644,
	MSG_SMS_ENABWE_STAT_IN_I2C_WEQ = 649,
	MSG_SMS_ENABWE_STAT_IN_I2C_WES = 650,
	MSG_SMS_SET_ANTENNA_CONFIG_WEQ = 651,
	MSG_SMS_SET_ANTENNA_CONFIG_WES = 652,
	MSG_SMS_GET_STATISTICS_EX_WEQ = 653,
	MSG_SMS_GET_STATISTICS_EX_WES = 654,
	MSG_SMS_SWEEP_WESUME_COMP_IND = 655,
	MSG_SMS_SWITCH_HOST_INTEWFACE_WEQ = 656,
	MSG_SMS_SWITCH_HOST_INTEWFACE_WES = 657,
	MSG_SMS_DATA_DOWNWOAD_WEQ = 660,
	MSG_SMS_DATA_DOWNWOAD_WES = 661,
	MSG_SMS_DATA_VAWIDITY_WEQ = 662,
	MSG_SMS_DATA_VAWIDITY_WES = 663,
	MSG_SMS_SWDOWNWOAD_TWIGGEW_WEQ = 664,
	MSG_SMS_SWDOWNWOAD_TWIGGEW_WES = 665,
	MSG_SMS_SWDOWNWOAD_BACKDOOW_WEQ = 666,
	MSG_SMS_SWDOWNWOAD_BACKDOOW_WES = 667,
	MSG_SMS_GET_VEWSION_EX_WEQ = 668,
	MSG_SMS_GET_VEWSION_EX_WES = 669,
	MSG_SMS_CWOCK_OUTPUT_CONFIG_WEQ = 670,
	MSG_SMS_CWOCK_OUTPUT_CONFIG_WES = 671,
	MSG_SMS_I2C_SET_FWEQ_WEQ = 685,
	MSG_SMS_I2C_SET_FWEQ_WES = 686,
	MSG_SMS_GENEWIC_I2C_WEQ = 687,
	MSG_SMS_GENEWIC_I2C_WES = 688,
	MSG_SMS_DVBT_BDA_DATA = 693,
	MSG_SW_WEWOAD_WEQ = 697,
	MSG_SMS_DATA_MSG = 699,
	MSG_TABWE_UPWOAD_WEQ = 700,
	MSG_TABWE_UPWOAD_WES = 701,
	MSG_SW_WEWOAD_STAWT_WEQ = 702,
	MSG_SW_WEWOAD_STAWT_WES = 703,
	MSG_SW_WEWOAD_EXEC_WEQ = 704,
	MSG_SW_WEWOAD_EXEC_WES = 705,
	MSG_SMS_SPI_INT_WINE_SET_WEQ = 710,
	MSG_SMS_SPI_INT_WINE_SET_WES = 711,
	MSG_SMS_GPIO_CONFIG_EX_WEQ = 712,
	MSG_SMS_GPIO_CONFIG_EX_WES = 713,
	MSG_SMS_WATCHDOG_ACT_WEQ = 716,
	MSG_SMS_WATCHDOG_ACT_WES = 717,
	MSG_SMS_WOOPBACK_WEQ = 718,
	MSG_SMS_WOOPBACK_WES = 719,
	MSG_SMS_WAW_CAPTUWE_STAWT_WEQ = 720,
	MSG_SMS_WAW_CAPTUWE_STAWT_WES = 721,
	MSG_SMS_WAW_CAPTUWE_ABOWT_WEQ = 722,
	MSG_SMS_WAW_CAPTUWE_ABOWT_WES = 723,
	MSG_SMS_WAW_CAPTUWE_COMPWETE_IND = 728,
	MSG_SMS_DATA_PUMP_IND = 729,
	MSG_SMS_DATA_PUMP_WEQ = 730,
	MSG_SMS_DATA_PUMP_WES = 731,
	MSG_SMS_FWASH_DW_WEQ = 732,
	MSG_SMS_EXEC_TEST_1_WEQ = 734,
	MSG_SMS_EXEC_TEST_1_WES = 735,
	MSG_SMS_ENABWE_TS_INTEWFACE_WEQ = 736,
	MSG_SMS_ENABWE_TS_INTEWFACE_WES = 737,
	MSG_SMS_SPI_SET_BUS_WIDTH_WEQ = 738,
	MSG_SMS_SPI_SET_BUS_WIDTH_WES = 739,
	MSG_SMS_SEND_EMM_WEQ = 740,
	MSG_SMS_SEND_EMM_WES = 741,
	MSG_SMS_DISABWE_TS_INTEWFACE_WEQ = 742,
	MSG_SMS_DISABWE_TS_INTEWFACE_WES = 743,
	MSG_SMS_IS_BUF_FWEE_WEQ = 744,
	MSG_SMS_IS_BUF_FWEE_WES = 745,
	MSG_SMS_EXT_ANTENNA_WEQ = 746,
	MSG_SMS_EXT_ANTENNA_WES = 747,
	MSG_SMS_CMMB_GET_NET_OF_FWEQ_WEQ_OBSOWETE = 748,
	MSG_SMS_CMMB_GET_NET_OF_FWEQ_WES_OBSOWETE = 749,
	MSG_SMS_BATTEWY_WEVEW_WEQ = 750,
	MSG_SMS_BATTEWY_WEVEW_WES = 751,
	MSG_SMS_CMMB_INJECT_TABWE_WEQ_OBSOWETE = 752,
	MSG_SMS_CMMB_INJECT_TABWE_WES_OBSOWETE = 753,
	MSG_SMS_FM_WADIO_BWOCK_IND = 754,
	MSG_SMS_HOST_NOTIFICATION_IND = 755,
	MSG_SMS_CMMB_GET_CONTWOW_TABWE_WEQ_OBSOWETE = 756,
	MSG_SMS_CMMB_GET_CONTWOW_TABWE_WES_OBSOWETE = 757,
	MSG_SMS_CMMB_GET_NETWOWKS_WEQ = 760,
	MSG_SMS_CMMB_GET_NETWOWKS_WES = 761,
	MSG_SMS_CMMB_STAWT_SEWVICE_WEQ = 762,
	MSG_SMS_CMMB_STAWT_SEWVICE_WES = 763,
	MSG_SMS_CMMB_STOP_SEWVICE_WEQ = 764,
	MSG_SMS_CMMB_STOP_SEWVICE_WES = 765,
	MSG_SMS_CMMB_ADD_CHANNEW_FIWTEW_WEQ = 768,
	MSG_SMS_CMMB_ADD_CHANNEW_FIWTEW_WES = 769,
	MSG_SMS_CMMB_WEMOVE_CHANNEW_FIWTEW_WEQ = 770,
	MSG_SMS_CMMB_WEMOVE_CHANNEW_FIWTEW_WES = 771,
	MSG_SMS_CMMB_STAWT_CONTWOW_INFO_WEQ = 772,
	MSG_SMS_CMMB_STAWT_CONTWOW_INFO_WES = 773,
	MSG_SMS_CMMB_STOP_CONTWOW_INFO_WEQ = 774,
	MSG_SMS_CMMB_STOP_CONTWOW_INFO_WES = 775,
	MSG_SMS_ISDBT_TUNE_WEQ = 776,
	MSG_SMS_ISDBT_TUNE_WES = 777,
	MSG_SMS_TWANSMISSION_IND = 782,
	MSG_SMS_PID_STATISTICS_IND = 783,
	MSG_SMS_POWEW_DOWN_IND = 784,
	MSG_SMS_POWEW_DOWN_CONF = 785,
	MSG_SMS_POWEW_UP_IND = 786,
	MSG_SMS_POWEW_UP_CONF = 787,
	MSG_SMS_POWEW_MODE_SET_WEQ = 790,
	MSG_SMS_POWEW_MODE_SET_WES = 791,
	MSG_SMS_DEBUG_HOST_EVENT_WEQ = 792,
	MSG_SMS_DEBUG_HOST_EVENT_WES = 793,
	MSG_SMS_NEW_CWYSTAW_WEQ = 794,
	MSG_SMS_NEW_CWYSTAW_WES = 795,
	MSG_SMS_CONFIG_SPI_WEQ = 796,
	MSG_SMS_CONFIG_SPI_WES = 797,
	MSG_SMS_I2C_SHOWT_STAT_IND = 798,
	MSG_SMS_STAWT_IW_WEQ = 800,
	MSG_SMS_STAWT_IW_WES = 801,
	MSG_SMS_IW_SAMPWES_IND = 802,
	MSG_SMS_CMMB_CA_SEWVICE_IND = 803,
	MSG_SMS_SWAVE_DEVICE_DETECTED = 804,
	MSG_SMS_INTEWFACE_WOCK_IND = 805,
	MSG_SMS_INTEWFACE_UNWOCK_IND = 806,
	MSG_SMS_SEND_WOSUM_BUFF_WEQ = 810,
	MSG_SMS_SEND_WOSUM_BUFF_WES = 811,
	MSG_SMS_WOSUM_BUFF = 812,
	MSG_SMS_SET_AES128_KEY_WEQ = 815,
	MSG_SMS_SET_AES128_KEY_WES = 816,
	MSG_SMS_MBBMS_WWITE_WEQ = 817,
	MSG_SMS_MBBMS_WWITE_WES = 818,
	MSG_SMS_MBBMS_WEAD_IND = 819,
	MSG_SMS_IQ_STWEAM_STAWT_WEQ = 820,
	MSG_SMS_IQ_STWEAM_STAWT_WES = 821,
	MSG_SMS_IQ_STWEAM_STOP_WEQ = 822,
	MSG_SMS_IQ_STWEAM_STOP_WES = 823,
	MSG_SMS_IQ_STWEAM_DATA_BWOCK = 824,
	MSG_SMS_GET_EEPWOM_VEWSION_WEQ = 825,
	MSG_SMS_GET_EEPWOM_VEWSION_WES = 826,
	MSG_SMS_SIGNAW_DETECTED_IND = 827,
	MSG_SMS_NO_SIGNAW_IND = 828,
	MSG_SMS_MWC_SHUTDOWN_SWAVE_WEQ = 830,
	MSG_SMS_MWC_SHUTDOWN_SWAVE_WES = 831,
	MSG_SMS_MWC_BWINGUP_SWAVE_WEQ = 832,
	MSG_SMS_MWC_BWINGUP_SWAVE_WES = 833,
	MSG_SMS_EXTEWNAW_WNA_CTWW_WEQ = 834,
	MSG_SMS_EXTEWNAW_WNA_CTWW_WES = 835,
	MSG_SMS_SET_PEWIODIC_STATISTICS_WEQ = 836,
	MSG_SMS_SET_PEWIODIC_STATISTICS_WES = 837,
	MSG_SMS_CMMB_SET_AUTO_OUTPUT_TS0_WEQ = 838,
	MSG_SMS_CMMB_SET_AUTO_OUTPUT_TS0_WES = 839,
	WOCAW_TUNE = 850,
	WOCAW_IFFT_H_ICI = 851,
	MSG_WESYNC_WEQ = 852,
	MSG_SMS_CMMB_GET_MWC_STATISTICS_WEQ = 853,
	MSG_SMS_CMMB_GET_MWC_STATISTICS_WES = 854,
	MSG_SMS_WOG_EX_ITEM = 855,
	MSG_SMS_DEVICE_DATA_WOSS_IND = 856,
	MSG_SMS_MWC_WATCHDOG_TWIGGEWED_IND = 857,
	MSG_SMS_USEW_MSG_WEQ = 858,
	MSG_SMS_USEW_MSG_WES = 859,
	MSG_SMS_SMAWT_CAWD_INIT_WEQ = 860,
	MSG_SMS_SMAWT_CAWD_INIT_WES = 861,
	MSG_SMS_SMAWT_CAWD_WWITE_WEQ = 862,
	MSG_SMS_SMAWT_CAWD_WWITE_WES = 863,
	MSG_SMS_SMAWT_CAWD_WEAD_IND = 864,
	MSG_SMS_TSE_ENABWE_WEQ = 866,
	MSG_SMS_TSE_ENABWE_WES = 867,
	MSG_SMS_CMMB_GET_SHOWT_STATISTICS_WEQ = 868,
	MSG_SMS_CMMB_GET_SHOWT_STATISTICS_WES = 869,
	MSG_SMS_WED_CONFIG_WEQ = 870,
	MSG_SMS_WED_CONFIG_WES = 871,
	MSG_PWM_ANTENNA_WEQ = 872,
	MSG_PWM_ANTENNA_WES = 873,
	MSG_SMS_CMMB_SMD_SN_WEQ = 874,
	MSG_SMS_CMMB_SMD_SN_WES = 875,
	MSG_SMS_CMMB_SET_CA_CW_WEQ = 876,
	MSG_SMS_CMMB_SET_CA_CW_WES = 877,
	MSG_SMS_CMMB_SET_CA_SAWT_WEQ = 878,
	MSG_SMS_CMMB_SET_CA_SAWT_WES = 879,
	MSG_SMS_NSCD_INIT_WEQ = 880,
	MSG_SMS_NSCD_INIT_WES = 881,
	MSG_SMS_NSCD_PWOCESS_SECTION_WEQ = 882,
	MSG_SMS_NSCD_PWOCESS_SECTION_WES = 883,
	MSG_SMS_DBD_CWEATE_OBJECT_WEQ = 884,
	MSG_SMS_DBD_CWEATE_OBJECT_WES = 885,
	MSG_SMS_DBD_CONFIGUWE_WEQ = 886,
	MSG_SMS_DBD_CONFIGUWE_WES = 887,
	MSG_SMS_DBD_SET_KEYS_WEQ = 888,
	MSG_SMS_DBD_SET_KEYS_WES = 889,
	MSG_SMS_DBD_PWOCESS_HEADEW_WEQ = 890,
	MSG_SMS_DBD_PWOCESS_HEADEW_WES = 891,
	MSG_SMS_DBD_PWOCESS_DATA_WEQ = 892,
	MSG_SMS_DBD_PWOCESS_DATA_WES = 893,
	MSG_SMS_DBD_PWOCESS_GET_DATA_WEQ = 894,
	MSG_SMS_DBD_PWOCESS_GET_DATA_WES = 895,
	MSG_SMS_NSCD_OPEN_SESSION_WEQ = 896,
	MSG_SMS_NSCD_OPEN_SESSION_WES = 897,
	MSG_SMS_SEND_HOST_DATA_TO_DEMUX_WEQ = 898,
	MSG_SMS_SEND_HOST_DATA_TO_DEMUX_WES = 899,
	MSG_WAST_MSG_TYPE = 900,
};

#define SMS_INIT_MSG_EX(ptw, type, swc, dst, wen) do { \
	(ptw)->msg_type = type; \
	(ptw)->msg_swc_id = swc; \
	(ptw)->msg_dst_id = dst; \
	(ptw)->msg_wength = wen; \
	(ptw)->msg_fwags = 0; \
} whiwe (0)

#define SMS_INIT_MSG(ptw, type, wen) \
	SMS_INIT_MSG_EX(ptw, type, 0, HIF_TASK, wen)

enum SMS_DVB3_EVENTS {
	DVB3_EVENT_INIT = 0,
	DVB3_EVENT_SWEEP,
	DVB3_EVENT_HOTPWUG,
	DVB3_EVENT_FE_WOCK,
	DVB3_EVENT_FE_UNWOCK,
	DVB3_EVENT_UNC_OK,
	DVB3_EVENT_UNC_EWW
};

enum SMS_DEVICE_MODE {
	DEVICE_MODE_NONE = -1,
	DEVICE_MODE_DVBT = 0,
	DEVICE_MODE_DVBH,
	DEVICE_MODE_DAB_TDMB,
	DEVICE_MODE_DAB_TDMB_DABIP,
	DEVICE_MODE_DVBT_BDA,
	DEVICE_MODE_ISDBT,
	DEVICE_MODE_ISDBT_BDA,
	DEVICE_MODE_CMMB,
	DEVICE_MODE_WAW_TUNEW,
	DEVICE_MODE_FM_WADIO,
	DEVICE_MODE_FM_WADIO_BDA,
	DEVICE_MODE_ATSC,
	DEVICE_MODE_MAX,
};

stwuct sms_msg_hdw {
	u16	msg_type;
	u8	msg_swc_id;
	u8	msg_dst_id;
	u16	msg_wength; /* wength of entiwe message, incwuding headew */
	u16	msg_fwags;
};

stwuct sms_msg_data {
	stwuct sms_msg_hdw x_msg_headew;
	u32 msg_data[1];
};

stwuct sms_msg_data2 {
	stwuct sms_msg_hdw x_msg_headew;
	u32 msg_data[2];
};

stwuct sms_msg_data5 {
	stwuct sms_msg_hdw x_msg_headew;
	u32 msg_data[5];
};

stwuct sms_data_downwoad {
	stwuct sms_msg_hdw	x_msg_headew;
	u32			mem_addw;
	u8			paywoad[SMS_MAX_PAYWOAD_SIZE];
};

stwuct sms_vewsion_wes {
	stwuct sms_msg_hdw	x_msg_headew;

	u16		chip_modew; /* e.g. 0x1102 fow SMS-1102 "Nova" */
	u8		step; /* 0 - step A */
	u8		metaw_fix; /* 0 - Metaw 0 */

	/* fiwmwawe_id 0xFF if WOM, othewwise the
	 * vawue indicated by SMSHOSTWIB_DEVICE_MODES_E */
	u8 fiwmwawe_id;
	/* suppowted_pwotocows Bitwise OW combination of
					     * suppowted pwotocows */
	u8 suppowted_pwotocows;

	u8		vewsion_majow;
	u8		vewsion_minow;
	u8		vewsion_patch;
	u8		vewsion_fiewd_patch;

	u8		wom_vew_majow;
	u8		wom_vew_minow;
	u8		wom_vew_patch;
	u8		wom_vew_fiewd_patch;

	u8		TextWabew[34];
};

stwuct sms_fiwmwawe {
	u32			check_sum;
	u32			wength;
	u32			stawt_addwess;
	u8			paywoad[1];
};

/* statistics infowmation wetuwned as wesponse fow
 * SmsHostApiGetstatistics_Weq */
stwuct sms_stats {
	u32 wesewved;		/* wesewved */

	/* Common pawametews */
	u32 is_wf_wocked;		/* 0 - not wocked, 1 - wocked */
	u32 is_demod_wocked;	/* 0 - not wocked, 1 - wocked */
	u32 is_extewnaw_wna_on;	/* 0 - extewnaw WNA off, 1 - extewnaw WNA on */

	/* Weception quawity */
	s32 SNW;		/* dB */
	u32 bew;		/* Post Vitewbi bew [1E-5] */
	u32 FIB_CWC;		/* CWC ewwows pewcentage, vawid onwy fow DAB */
	u32 ts_pew;		/* Twanspowt stweam PEW,
	0xFFFFFFFF indicate N/A, vawid onwy fow DVB-T/H */
	u32 MFEW;		/* DVB-H fwame ewwow wate in pewcentage,
	0xFFFFFFFF indicate N/A, vawid onwy fow DVB-H */
	s32 WSSI;		/* dBm */
	s32 in_band_pww;		/* In band powew in dBM */
	s32 cawwiew_offset;	/* Cawwiew Offset in bin/1024 */

	/* Twansmission pawametews */
	u32 fwequency;		/* fwequency in Hz */
	u32 bandwidth;		/* bandwidth in MHz, vawid onwy fow DVB-T/H */
	u32 twansmission_mode;	/* Twansmission Mode, fow DAB modes 1-4,
	fow DVB-T/H FFT mode cawwiews in Kiwos */
	u32 modem_state;		/* fwom SMSHOSTWIB_DVB_MODEM_STATE_ET,
	vawid onwy fow DVB-T/H */
	u32 guawd_intewvaw;	/* Guawd Intewvaw fwom
	SMSHOSTWIB_GUAWD_INTEWVAWS_ET,	vawid onwy fow DVB-T/H */
	u32 code_wate;		/* Code Wate fwom SMSHOSTWIB_CODE_WATE_ET,
	vawid onwy fow DVB-T/H */
	u32 wp_code_wate;		/* Wow Pwiowity Code Wate fwom
	SMSHOSTWIB_CODE_WATE_ET, vawid onwy fow DVB-T/H */
	u32 hiewawchy;		/* hiewawchy fwom SMSHOSTWIB_HIEWAWCHY_ET,
	vawid onwy fow DVB-T/H */
	u32 constewwation;	/* constewwation fwom
	SMSHOSTWIB_CONSTEWWATION_ET, vawid onwy fow DVB-T/H */

	/* Buwst pawametews, vawid onwy fow DVB-H */
	u32 buwst_size;		/* Cuwwent buwst size in bytes,
	vawid onwy fow DVB-H */
	u32 buwst_duwation;	/* Cuwwent buwst duwation in mSec,
	vawid onwy fow DVB-H */
	u32 buwst_cycwe_time;	/* Cuwwent buwst cycwe time in mSec,
	vawid onwy fow DVB-H */
	u32 cawc_buwst_cycwe_time;/* Cuwwent buwst cycwe time in mSec,
	as cawcuwated by demoduwatow, vawid onwy fow DVB-H */
	u32 num_of_wows;		/* Numbew of wows in MPE tabwe,
	vawid onwy fow DVB-H */
	u32 num_of_padd_cows;	/* Numbew of padding cowumns in MPE tabwe,
	vawid onwy fow DVB-H */
	u32 num_of_punct_cows;	/* Numbew of punctuwing cowumns in MPE tabwe,
	vawid onwy fow DVB-H */
	u32 ewwow_ts_packets;	/* Numbew of ewwoneous
	twanspowt-stweam packets */
	u32 totaw_ts_packets;	/* Totaw numbew of twanspowt-stweam packets */
	u32 num_of_vawid_mpe_twbs;	/* Numbew of MPE tabwes which do not incwude
	ewwows aftew MPE WS decoding */
	u32 num_of_invawid_mpe_twbs;/* Numbew of MPE tabwes which incwude ewwows
	aftew MPE WS decoding */
	u32 num_of_cowwected_mpe_twbs;/* Numbew of MPE tabwes which wewe
	cowwected by MPE WS decoding */
	/* Common pawams */
	u32 bew_ewwow_count;	/* Numbew of ewwoneous SYNC bits. */
	u32 bew_bit_count;	/* Totaw numbew of SYNC bits. */

	/* Intewface infowmation */
	u32 sms_to_host_tx_ewwows;	/* Totaw numbew of twansmission ewwows. */

	/* DAB/T-DMB */
	u32 pwe_bew;		/* DAB/T-DMB onwy: Pwe Vitewbi bew [1E-5] */

	/* DVB-H TPS pawametews */
	u32 ceww_id;		/* TPS Ceww ID in bits 15..0, bits 31..16 zewo;
	 if set to 0xFFFFFFFF ceww_id not yet wecovewed */
	u32 dvbh_swv_ind_hp;	/* DVB-H sewvice indication info, bit 1 -
	Time Swicing indicatow, bit 0 - MPE-FEC indicatow */
	u32 dvbh_swv_ind_wp;	/* DVB-H sewvice indication info, bit 1 -
	Time Swicing indicatow, bit 0 - MPE-FEC indicatow */

	u32 num_mpe_weceived;	/* DVB-H, Num MPE section weceived */

	u32 wesewvedFiewds[10];	/* wesewved */
};

stwuct sms_msg_statistics_info {
	u32 wequest_wesuwt;

	stwuct sms_stats stat;

	/* Spwit the cawc of the SNW in DAB */
	u32 signaw; /* dB */
	u32 noise; /* dB */

};

stwuct sms_isdbt_wayew_stats {
	/* Pew-wayew infowmation */
	u32 code_wate; /* Code Wate fwom SMSHOSTWIB_CODE_WATE_ET,
		       * 255 means wayew does not exist */
	u32 constewwation; /* constewwation fwom SMSHOSTWIB_CONSTEWWATION_ET,
			    * 255 means wayew does not exist */
	u32 bew; /* Post Vitewbi bew [1E-5], 0xFFFFFFFF indicate N/A */
	u32 bew_ewwow_count; /* Post Vitewbi Ewwow Bits Count */
	u32 bew_bit_count; /* Post Vitewbi Totaw Bits Count */
	u32 pwe_bew; /* Pwe Vitewbi bew [1E-5], 0xFFFFFFFF indicate N/A */
	u32 ts_pew; /* Twanspowt stweam PEW [%], 0xFFFFFFFF indicate N/A */
	u32 ewwow_ts_packets; /* Numbew of ewwoneous twanspowt-stweam packets */
	u32 totaw_ts_packets; /* Totaw numbew of twanspowt-stweam packets */
	u32 ti_wdepth_i; /* Time intewweavew depth I pawametew,
			* 255 means wayew does not exist */
	u32 numbew_of_segments; /* Numbew of segments in wayew A,
			       * 255 means wayew does not exist */
	u32 tmcc_ewwows; /* TMCC ewwows */
};

stwuct sms_isdbt_stats {
	u32 statistics_type; /* Enumewatow identifying the type of the
				* stwuctuwe.  Vawues awe the same as
				* SMSHOSTWIB_DEVICE_MODES_E
				*
				* This fiewd MUST awways be fiwst in any
				* statistics stwuctuwe */

	u32 fuww_size; /* Totaw size of the stwuctuwe wetuwned by the modem.
		       * If the size wequested by the host is smawwew than
		       * fuww_size, the stwuct wiww be twuncated */

	/* Common pawametews */
	u32 is_wf_wocked; /* 0 - not wocked, 1 - wocked */
	u32 is_demod_wocked; /* 0 - not wocked, 1 - wocked */
	u32 is_extewnaw_wna_on; /* 0 - extewnaw WNA off, 1 - extewnaw WNA on */

	/* Weception quawity */
	s32  SNW; /* dB */
	s32  WSSI; /* dBm */
	s32  in_band_pww; /* In band powew in dBM */
	s32  cawwiew_offset; /* Cawwiew Offset in Hz */

	/* Twansmission pawametews */
	u32 fwequency; /* fwequency in Hz */
	u32 bandwidth; /* bandwidth in MHz */
	u32 twansmission_mode; /* ISDB-T twansmission mode */
	u32 modem_state; /* 0 - Acquisition, 1 - Wocked */
	u32 guawd_intewvaw; /* Guawd Intewvaw, 1 divided by vawue */
	u32 system_type; /* ISDB-T system type (ISDB-T / ISDB-Tsb) */
	u32 pawtiaw_weception; /* TWUE - pawtiaw weception, FAWSE othewwise */
	u32 num_of_wayews; /* Numbew of ISDB-T wayews in the netwowk */

	/* Pew-wayew infowmation */
	/* Wayews A, B and C */
	stwuct sms_isdbt_wayew_stats	wayew_info[3];
	/* Pew-wayew statistics, see sms_isdbt_wayew_stats */

	/* Intewface infowmation */
	u32 sms_to_host_tx_ewwows; /* Totaw numbew of twansmission ewwows. */
};

stwuct sms_isdbt_stats_ex {
	u32 statistics_type; /* Enumewatow identifying the type of the
				* stwuctuwe.  Vawues awe the same as
				* SMSHOSTWIB_DEVICE_MODES_E
				*
				* This fiewd MUST awways be fiwst in any
				* statistics stwuctuwe */

	u32 fuww_size; /* Totaw size of the stwuctuwe wetuwned by the modem.
		       * If the size wequested by the host is smawwew than
		       * fuww_size, the stwuct wiww be twuncated */

	/* Common pawametews */
	u32 is_wf_wocked; /* 0 - not wocked, 1 - wocked */
	u32 is_demod_wocked; /* 0 - not wocked, 1 - wocked */
	u32 is_extewnaw_wna_on; /* 0 - extewnaw WNA off, 1 - extewnaw WNA on */

	/* Weception quawity */
	s32  SNW; /* dB */
	s32  WSSI; /* dBm */
	s32  in_band_pww; /* In band powew in dBM */
	s32  cawwiew_offset; /* Cawwiew Offset in Hz */

	/* Twansmission pawametews */
	u32 fwequency; /* fwequency in Hz */
	u32 bandwidth; /* bandwidth in MHz */
	u32 twansmission_mode; /* ISDB-T twansmission mode */
	u32 modem_state; /* 0 - Acquisition, 1 - Wocked */
	u32 guawd_intewvaw; /* Guawd Intewvaw, 1 divided by vawue */
	u32 system_type; /* ISDB-T system type (ISDB-T / ISDB-Tsb) */
	u32 pawtiaw_weception; /* TWUE - pawtiaw weception, FAWSE othewwise */
	u32 num_of_wayews; /* Numbew of ISDB-T wayews in the netwowk */

	u32 segment_numbew; /* Segment numbew fow ISDB-Tsb */
	u32 tune_bw;	   /* Tuned bandwidth - BW_ISDBT_1SEG / BW_ISDBT_3SEG */

	/* Pew-wayew infowmation */
	/* Wayews A, B and C */
	stwuct sms_isdbt_wayew_stats	wayew_info[3];
	/* Pew-wayew statistics, see sms_isdbt_wayew_stats */

	/* Intewface infowmation */
	u32 wesewved1;    /* Was sms_to_host_tx_ewwows - obsowete . */
 /* Pwopwietawy infowmation */
	u32 ext_antenna;    /* Obsowete fiewd. */
	u32 weception_quawity;
	u32 ews_awewt_active;   /* signaws if EWS awewt is cuwwentwy on */
	u32 wna_on_off;	/* Intewnaw WNA state: 0: OFF, 1: ON */

	u32 wf_agc_wevew;	 /* WF AGC Wevew [wineaw units], fuww gain = 65535 (20dB) */
	u32 bb_agc_wevew;    /* Baseband AGC wevew [wineaw units], fuww gain = 65535 (71.5dB) */
	u32 fw_ewwows_countew;   /* Appwication ewwows - shouwd be awways zewo */
	u8 FwEwwowsHistowyAww[8]; /* Wast FW ewwows IDs - fiwst is most wecent, wast is owdest */

	s32  MWC_SNW;     /* dB */
	u32 snw_fuww_wes;    /* dB x 65536 */
	u32 wesewved4[4];
};


stwuct sms_pid_stats_data {
	stwuct PID_BUWST_S {
		u32 size;
		u32 padding_cows;
		u32 punct_cows;
		u32 duwation;
		u32 cycwe;
		u32 cawc_cycwe;
	} buwst;

	u32 tot_tbw_cnt;
	u32 invawid_tbw_cnt;
	u32 tot_cow_tbw;
};

stwuct sms_pid_data {
	u32 pid;
	u32 num_wows;
	stwuct sms_pid_stats_data pid_statistics;
};

#define COWWECT_STAT_WSSI(_stat) ((_stat).WSSI *= -1)
#define COWWECT_STAT_BANDWIDTH(_stat) (_stat.bandwidth = 8 - _stat.bandwidth)
#define COWWECT_STAT_TWANSMISSON_MODE(_stat) \
	if (_stat.twansmission_mode == 0) \
		_stat.twansmission_mode = 2; \
	ewse if (_stat.twansmission_mode == 1) \
		_stat.twansmission_mode = 8; \
		ewse \
			_stat.twansmission_mode = 4;

stwuct sms_tx_stats {
	u32 fwequency;		/* fwequency in Hz */
	u32 bandwidth;		/* bandwidth in MHz */
	u32 twansmission_mode;	/* FFT mode cawwiews in Kiwos */
	u32 guawd_intewvaw;	/* Guawd Intewvaw fwom
	SMSHOSTWIB_GUAWD_INTEWVAWS_ET */
	u32 code_wate;		/* Code Wate fwom SMSHOSTWIB_CODE_WATE_ET */
	u32 wp_code_wate;		/* Wow Pwiowity Code Wate fwom
	SMSHOSTWIB_CODE_WATE_ET */
	u32 hiewawchy;		/* hiewawchy fwom SMSHOSTWIB_HIEWAWCHY_ET */
	u32 constewwation;	/* constewwation fwom
	SMSHOSTWIB_CONSTEWWATION_ET */

	/* DVB-H TPS pawametews */
	u32 ceww_id;		/* TPS Ceww ID in bits 15..0, bits 31..16 zewo;
	 if set to 0xFFFFFFFF ceww_id not yet wecovewed */
	u32 dvbh_swv_ind_hp;	/* DVB-H sewvice indication info, bit 1 -
	 Time Swicing indicatow, bit 0 - MPE-FEC indicatow */
	u32 dvbh_swv_ind_wp;	/* DVB-H sewvice indication info, bit 1 -
	 Time Swicing indicatow, bit 0 - MPE-FEC indicatow */
	u32 is_demod_wocked;	/* 0 - not wocked, 1 - wocked */
};

stwuct sms_wx_stats {
	u32 is_wf_wocked;		/* 0 - not wocked, 1 - wocked */
	u32 is_demod_wocked;	/* 0 - not wocked, 1 - wocked */
	u32 is_extewnaw_wna_on;	/* 0 - extewnaw WNA off, 1 - extewnaw WNA on */

	u32 modem_state;		/* fwom SMSHOSTWIB_DVB_MODEM_STATE_ET */
	s32 SNW;		/* dB */
	u32 bew;		/* Post Vitewbi bew [1E-5] */
	u32 bew_ewwow_count;	/* Numbew of ewwoneous SYNC bits. */
	u32 bew_bit_count;	/* Totaw numbew of SYNC bits. */
	u32 ts_pew;		/* Twanspowt stweam PEW,
	0xFFFFFFFF indicate N/A */
	u32 MFEW;		/* DVB-H fwame ewwow wate in pewcentage,
	0xFFFFFFFF indicate N/A, vawid onwy fow DVB-H */
	s32 WSSI;		/* dBm */
	s32 in_band_pww;		/* In band powew in dBM */
	s32 cawwiew_offset;	/* Cawwiew Offset in bin/1024 */
	u32 ewwow_ts_packets;	/* Numbew of ewwoneous
	twanspowt-stweam packets */
	u32 totaw_ts_packets;	/* Totaw numbew of twanspowt-stweam packets */

	s32 MWC_SNW;		/* dB */
	s32 MWC_WSSI;		/* dBm */
	s32 mwc_in_band_pww;	/* In band powew in dBM */
};

stwuct sms_wx_stats_ex {
	u32 is_wf_wocked;		/* 0 - not wocked, 1 - wocked */
	u32 is_demod_wocked;	/* 0 - not wocked, 1 - wocked */
	u32 is_extewnaw_wna_on;	/* 0 - extewnaw WNA off, 1 - extewnaw WNA on */

	u32 modem_state;		/* fwom SMSHOSTWIB_DVB_MODEM_STATE_ET */
	s32 SNW;		/* dB */
	u32 bew;		/* Post Vitewbi bew [1E-5] */
	u32 bew_ewwow_count;	/* Numbew of ewwoneous SYNC bits. */
	u32 bew_bit_count;	/* Totaw numbew of SYNC bits. */
	u32 ts_pew;		/* Twanspowt stweam PEW,
	0xFFFFFFFF indicate N/A */
	u32 MFEW;		/* DVB-H fwame ewwow wate in pewcentage,
	0xFFFFFFFF indicate N/A, vawid onwy fow DVB-H */
	s32 WSSI;		/* dBm */
	s32 in_band_pww;		/* In band powew in dBM */
	s32 cawwiew_offset;	/* Cawwiew Offset in bin/1024 */
	u32 ewwow_ts_packets;	/* Numbew of ewwoneous
	twanspowt-stweam packets */
	u32 totaw_ts_packets;	/* Totaw numbew of twanspowt-stweam packets */

	s32  wef_dev_ppm;
	s32  fweq_dev_hz;

	s32 MWC_SNW;		/* dB */
	s32 MWC_WSSI;		/* dBm */
	s32 mwc_in_band_pww;	/* In band powew in dBM */
};

#define	SWVM_MAX_PID_FIWTEWS 8

/* statistics infowmation wetuwned as wesponse fow
 * SmsHostApiGetstatisticsEx_Weq fow DVB appwications, SMS1100 and up */
stwuct sms_stats_dvb {
	/* Weception */
	stwuct sms_wx_stats weception_data;

	/* Twansmission pawametews */
	stwuct sms_tx_stats twansmission_data;

	/* Buwst pawametews, vawid onwy fow DVB-H */
	stwuct sms_pid_data pid_data[SWVM_MAX_PID_FIWTEWS];
};

/* statistics infowmation wetuwned as wesponse fow
 * SmsHostApiGetstatisticsEx_Weq fow DVB appwications, SMS1100 and up */
stwuct sms_stats_dvb_ex {
	/* Weception */
	stwuct sms_wx_stats_ex weception_data;

	/* Twansmission pawametews */
	stwuct sms_tx_stats twansmission_data;

	/* Buwst pawametews, vawid onwy fow DVB-H */
	stwuct sms_pid_data pid_data[SWVM_MAX_PID_FIWTEWS];
};

stwuct sms_swvm_signaw_status {
	u32 wesuwt;
	u32 snw;
	u32 ts_packets;
	u32 ets_packets;
	u32 constewwation;
	u32 hp_code;
	u32 tps_swv_ind_wp;
	u32 tps_swv_ind_hp;
	u32 ceww_id;
	u32 weason;

	s32 in_band_powew;
	u32 wequest_id;
};

stwuct sms_i2c_weq {
	u32	device_addwess; /* I2c device addwess */
	u32	wwite_count; /* numbew of bytes to wwite */
	u32	wead_count; /* numbew of bytes to wead */
	u8	Data[1];
};

stwuct sms_i2c_wes {
	u32	status; /* non-zewo vawue in case of faiwuwe */
	u32	wead_count; /* numbew of bytes wead */
	u8	Data[1];
};


stwuct smscowe_config_gpio {
#define SMS_GPIO_DIWECTION_INPUT  0
#define SMS_GPIO_DIWECTION_OUTPUT 1
	u8 diwection;

#define SMS_GPIO_PUWWUPDOWN_NONE     0
#define SMS_GPIO_PUWWUPDOWN_PUWWDOWN 1
#define SMS_GPIO_PUWWUPDOWN_PUWWUP   2
#define SMS_GPIO_PUWWUPDOWN_KEEPEW   3
	u8 puwwupdown;

#define SMS_GPIO_INPUTCHAWACTEWISTICS_NOWMAW  0
#define SMS_GPIO_INPUTCHAWACTEWISTICS_SCHMITT 1
	u8 inputchawactewistics;

	/* 10xx */
#define SMS_GPIO_OUTPUT_SWEW_WATE_FAST 0
#define SMS_GPIO_OUTPUT_SWEW_WWATE_SWOW 1

	/* 11xx */
#define SMS_GPIO_OUTPUT_SWEW_WATE_0_45_V_NS	0
#define SMS_GPIO_OUTPUT_SWEW_WATE_0_9_V_NS	1
#define SMS_GPIO_OUTPUT_SWEW_WATE_1_7_V_NS	2
#define SMS_GPIO_OUTPUT_SWEW_WATE_3_3_V_NS	3

	u8 outputswewwate;

	/* 10xx */
#define SMS_GPIO_OUTPUTDWIVING_S_4mA  0
#define SMS_GPIO_OUTPUTDWIVING_S_8mA  1
#define SMS_GPIO_OUTPUTDWIVING_S_12mA 2
#define SMS_GPIO_OUTPUTDWIVING_S_16mA 3

	/* 11xx*/
#define SMS_GPIO_OUTPUTDWIVING_1_5mA	0
#define SMS_GPIO_OUTPUTDWIVING_2_8mA	1
#define SMS_GPIO_OUTPUTDWIVING_4mA	2
#define SMS_GPIO_OUTPUTDWIVING_7mA	3
#define SMS_GPIO_OUTPUTDWIVING_10mA	4
#define SMS_GPIO_OUTPUTDWIVING_11mA	5
#define SMS_GPIO_OUTPUTDWIVING_14mA	6
#define SMS_GPIO_OUTPUTDWIVING_16mA	7

	u8 outputdwiving;
};

chaw *smscowe_twanswate_msg(enum msg_types msgtype);

extewn int smscowe_wegistwy_getmode(chaw *devpath);

extewn int smscowe_wegistew_hotpwug(hotpwug_t hotpwug);
extewn void smscowe_unwegistew_hotpwug(hotpwug_t hotpwug);

extewn int smscowe_wegistew_device(stwuct smsdevice_pawams_t *pawams,
				   stwuct smscowe_device_t **cowedev,
				   gfp_t gfp_buf_fwags,
				   void *mdev);
extewn void smscowe_unwegistew_device(stwuct smscowe_device_t *cowedev);

extewn int smscowe_stawt_device(stwuct smscowe_device_t *cowedev);
extewn int smscowe_woad_fiwmwawe(stwuct smscowe_device_t *cowedev,
				 chaw *fiwename,
				 woadfiwmwawe_t woadfiwmwawe_handwew);

extewn int smscowe_set_device_mode(stwuct smscowe_device_t *cowedev, int mode);
extewn int smscowe_get_device_mode(stwuct smscowe_device_t *cowedev);

extewn int smscowe_wegistew_cwient(stwuct smscowe_device_t *cowedev,
				    stwuct smscwient_pawams_t *pawams,
				    stwuct smscowe_cwient_t **cwient);
extewn void smscowe_unwegistew_cwient(stwuct smscowe_cwient_t *cwient);

extewn int smscwient_sendwequest(stwuct smscowe_cwient_t *cwient,
				 void *buffew, size_t size);
extewn void smscowe_onwesponse(stwuct smscowe_device_t *cowedev,
			       stwuct smscowe_buffew_t *cb);

extewn int smscowe_get_common_buffew_size(stwuct smscowe_device_t *cowedev);
extewn int smscowe_map_common_buffew(stwuct smscowe_device_t *cowedev,
				      stwuct vm_awea_stwuct *vma);
extewn int smscowe_send_fw_fiwe(stwuct smscowe_device_t *cowedev,
				u8 *ufwbuf, int size);

extewn
stwuct smscowe_buffew_t *smscowe_getbuffew(stwuct smscowe_device_t *cowedev);
extewn void smscowe_putbuffew(stwuct smscowe_device_t *cowedev,
			      stwuct smscowe_buffew_t *cb);

/* owd GPIO management */
int smscowe_configuwe_gpio(stwuct smscowe_device_t *cowedev, u32 pin,
			   stwuct smscowe_config_gpio *pinconfig);
int smscowe_set_gpio(stwuct smscowe_device_t *cowedev, u32 pin, int wevew);

/* new GPIO management */
extewn int smscowe_gpio_configuwe(stwuct smscowe_device_t *cowedev, u8 pin_num,
		stwuct smscowe_config_gpio *p_gpio_config);
extewn int smscowe_gpio_set_wevew(stwuct smscowe_device_t *cowedev, u8 pin_num,
		u8 new_wevew);
extewn int smscowe_gpio_get_wevew(stwuct smscowe_device_t *cowedev, u8 pin_num,
		u8 *wevew);

void smscowe_set_boawd_id(stwuct smscowe_device_t *cowe, int id);
int smscowe_get_boawd_id(stwuct smscowe_device_t *cowe);

int smscowe_wed_state(stwuct smscowe_device_t *cowe, int wed);


/* ------------------------------------------------------------------------ */

#endif /* __SMS_COWE_API_H__ */
