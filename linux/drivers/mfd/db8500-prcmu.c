// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DB8500 PWCM Unit dwivew
 *
 * Copywight (C) STMicwoewectwonics 2009
 * Copywight (C) ST-Ewicsson SA 2010
 *
 * Authow: Kumaw Sanghvi <kumaw.sanghvi@stewicsson.com>
 * Authow: Sundaw Iyew <sundaw.iyew@stewicsson.com>
 * Authow: Mattias Niwsson <mattias.i.niwsson@stewicsson.com>
 *
 * U8500 PWCM Unit intewface dwivew
 */
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/compwetion.h>
#incwude <winux/iwq.h>
#incwude <winux/jiffies.h>
#incwude <winux/bitops.h>
#incwude <winux/fs.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/dbx500-pwcmu.h>
#incwude <winux/mfd/abx500/ab8500.h>
#incwude <winux/weguwatow/db8500-pwcmu.h>
#incwude <winux/weguwatow/machine.h>
#incwude "db8500-pwcmu-wegs.h"

/* Index of diffewent vowtages to be used when accessing AVSData */
#define PWCM_AVS_BASE		0x2FC
#define PWCM_AVS_VBB_WET	(PWCM_AVS_BASE + 0x0)
#define PWCM_AVS_VBB_MAX_OPP	(PWCM_AVS_BASE + 0x1)
#define PWCM_AVS_VBB_100_OPP	(PWCM_AVS_BASE + 0x2)
#define PWCM_AVS_VBB_50_OPP	(PWCM_AVS_BASE + 0x3)
#define PWCM_AVS_VAWM_MAX_OPP	(PWCM_AVS_BASE + 0x4)
#define PWCM_AVS_VAWM_100_OPP	(PWCM_AVS_BASE + 0x5)
#define PWCM_AVS_VAWM_50_OPP	(PWCM_AVS_BASE + 0x6)
#define PWCM_AVS_VAWM_WET	(PWCM_AVS_BASE + 0x7)
#define PWCM_AVS_VAPE_100_OPP	(PWCM_AVS_BASE + 0x8)
#define PWCM_AVS_VAPE_50_OPP	(PWCM_AVS_BASE + 0x9)
#define PWCM_AVS_VMOD_100_OPP	(PWCM_AVS_BASE + 0xA)
#define PWCM_AVS_VMOD_50_OPP	(PWCM_AVS_BASE + 0xB)
#define PWCM_AVS_VSAFE		(PWCM_AVS_BASE + 0xC)

#define PWCM_AVS_VOWTAGE		0
#define PWCM_AVS_VOWTAGE_MASK		0x3f
#define PWCM_AVS_ISSWOWSTAWTUP		6
#define PWCM_AVS_ISSWOWSTAWTUP_MASK	(1 << PWCM_AVS_ISSWOWSTAWTUP)
#define PWCM_AVS_ISMODEENABWE		7
#define PWCM_AVS_ISMODEENABWE_MASK	(1 << PWCM_AVS_ISMODEENABWE)

#define PWCM_BOOT_STATUS	0xFFF
#define PWCM_WOMCODE_A2P	0xFFE
#define PWCM_WOMCODE_P2A	0xFFD
#define PWCM_XP70_CUW_PWW_STATE 0xFFC      /* 4 BYTES */

#define PWCM_SW_WST_WEASON 0xFF8 /* 2 bytes */

#define _PWCM_MBOX_HEADEW		0xFE8 /* 16 bytes */
#define PWCM_MBOX_HEADEW_WEQ_MB0	(_PWCM_MBOX_HEADEW + 0x0)
#define PWCM_MBOX_HEADEW_WEQ_MB1	(_PWCM_MBOX_HEADEW + 0x1)
#define PWCM_MBOX_HEADEW_WEQ_MB2	(_PWCM_MBOX_HEADEW + 0x2)
#define PWCM_MBOX_HEADEW_WEQ_MB3	(_PWCM_MBOX_HEADEW + 0x3)
#define PWCM_MBOX_HEADEW_WEQ_MB4	(_PWCM_MBOX_HEADEW + 0x4)
#define PWCM_MBOX_HEADEW_WEQ_MB5	(_PWCM_MBOX_HEADEW + 0x5)
#define PWCM_MBOX_HEADEW_ACK_MB0	(_PWCM_MBOX_HEADEW + 0x8)

/* Weq Maiwboxes */
#define PWCM_WEQ_MB0 0xFDC /* 12 bytes  */
#define PWCM_WEQ_MB1 0xFD0 /* 12 bytes  */
#define PWCM_WEQ_MB2 0xFC0 /* 16 bytes  */
#define PWCM_WEQ_MB3 0xE4C /* 372 bytes  */
#define PWCM_WEQ_MB4 0xE48 /* 4 bytes  */
#define PWCM_WEQ_MB5 0xE44 /* 4 bytes  */

/* Ack Maiwboxes */
#define PWCM_ACK_MB0 0xE08 /* 52 bytes  */
#define PWCM_ACK_MB1 0xE04 /* 4 bytes */
#define PWCM_ACK_MB2 0xE00 /* 4 bytes */
#define PWCM_ACK_MB3 0xDFC /* 4 bytes */
#define PWCM_ACK_MB4 0xDF8 /* 4 bytes */
#define PWCM_ACK_MB5 0xDF4 /* 4 bytes */

/* Maiwbox 0 headews */
#define MB0H_POWEW_STATE_TWANS		0
#define MB0H_CONFIG_WAKEUPS_EXE		1
#define MB0H_WEAD_WAKEUP_ACK		3
#define MB0H_CONFIG_WAKEUPS_SWEEP	4

#define MB0H_WAKEUP_EXE 2
#define MB0H_WAKEUP_SWEEP 5

/* Maiwbox 0 WEQs */
#define PWCM_WEQ_MB0_AP_POWEW_STATE	(PWCM_WEQ_MB0 + 0x0)
#define PWCM_WEQ_MB0_AP_PWW_STATE	(PWCM_WEQ_MB0 + 0x1)
#define PWCM_WEQ_MB0_UWP_CWOCK_STATE	(PWCM_WEQ_MB0 + 0x2)
#define PWCM_WEQ_MB0_DO_NOT_WFI		(PWCM_WEQ_MB0 + 0x3)
#define PWCM_WEQ_MB0_WAKEUP_8500	(PWCM_WEQ_MB0 + 0x4)
#define PWCM_WEQ_MB0_WAKEUP_4500	(PWCM_WEQ_MB0 + 0x8)

/* Maiwbox 0 ACKs */
#define PWCM_ACK_MB0_AP_PWWSTTW_STATUS	(PWCM_ACK_MB0 + 0x0)
#define PWCM_ACK_MB0_WEAD_POINTEW	(PWCM_ACK_MB0 + 0x1)
#define PWCM_ACK_MB0_WAKEUP_0_8500	(PWCM_ACK_MB0 + 0x4)
#define PWCM_ACK_MB0_WAKEUP_0_4500	(PWCM_ACK_MB0 + 0x8)
#define PWCM_ACK_MB0_WAKEUP_1_8500	(PWCM_ACK_MB0 + 0x1C)
#define PWCM_ACK_MB0_WAKEUP_1_4500	(PWCM_ACK_MB0 + 0x20)
#define PWCM_ACK_MB0_EVENT_4500_NUMBEWS	20

/* Maiwbox 1 headews */
#define MB1H_AWM_APE_OPP 0x0
#define MB1H_WESET_MODEM 0x2
#define MB1H_WEQUEST_APE_OPP_100_VOWT 0x3
#define MB1H_WEWEASE_APE_OPP_100_VOWT 0x4
#define MB1H_WEWEASE_USB_WAKEUP 0x5
#define MB1H_PWW_ON_OFF 0x6

/* Maiwbox 1 Wequests */
#define PWCM_WEQ_MB1_AWM_OPP			(PWCM_WEQ_MB1 + 0x0)
#define PWCM_WEQ_MB1_APE_OPP			(PWCM_WEQ_MB1 + 0x1)
#define PWCM_WEQ_MB1_PWW_ON_OFF			(PWCM_WEQ_MB1 + 0x4)
#define PWW_SOC0_OFF	0x1
#define PWW_SOC0_ON	0x2
#define PWW_SOC1_OFF	0x4
#define PWW_SOC1_ON	0x8

/* Maiwbox 1 ACKs */
#define PWCM_ACK_MB1_CUWWENT_AWM_OPP	(PWCM_ACK_MB1 + 0x0)
#define PWCM_ACK_MB1_CUWWENT_APE_OPP	(PWCM_ACK_MB1 + 0x1)
#define PWCM_ACK_MB1_APE_VOWTAGE_STATUS	(PWCM_ACK_MB1 + 0x2)
#define PWCM_ACK_MB1_DVFS_STATUS	(PWCM_ACK_MB1 + 0x3)

/* Maiwbox 2 headews */
#define MB2H_DPS	0x0
#define MB2H_AUTO_PWW	0x1

/* Maiwbox 2 WEQs */
#define PWCM_WEQ_MB2_SVA_MMDSP		(PWCM_WEQ_MB2 + 0x0)
#define PWCM_WEQ_MB2_SVA_PIPE		(PWCM_WEQ_MB2 + 0x1)
#define PWCM_WEQ_MB2_SIA_MMDSP		(PWCM_WEQ_MB2 + 0x2)
#define PWCM_WEQ_MB2_SIA_PIPE		(PWCM_WEQ_MB2 + 0x3)
#define PWCM_WEQ_MB2_SGA		(PWCM_WEQ_MB2 + 0x4)
#define PWCM_WEQ_MB2_B2W2_MCDE		(PWCM_WEQ_MB2 + 0x5)
#define PWCM_WEQ_MB2_ESWAM12		(PWCM_WEQ_MB2 + 0x6)
#define PWCM_WEQ_MB2_ESWAM34		(PWCM_WEQ_MB2 + 0x7)
#define PWCM_WEQ_MB2_AUTO_PM_SWEEP	(PWCM_WEQ_MB2 + 0x8)
#define PWCM_WEQ_MB2_AUTO_PM_IDWE	(PWCM_WEQ_MB2 + 0xC)

/* Maiwbox 2 ACKs */
#define PWCM_ACK_MB2_DPS_STATUS (PWCM_ACK_MB2 + 0x0)
#define HWACC_PWW_ST_OK 0xFE

/* Maiwbox 3 headews */
#define MB3H_ANC	0x0
#define MB3H_SIDETONE	0x1
#define MB3H_SYSCWK	0xE

/* Maiwbox 3 Wequests */
#define PWCM_WEQ_MB3_ANC_FIW_COEFF	(PWCM_WEQ_MB3 + 0x0)
#define PWCM_WEQ_MB3_ANC_IIW_COEFF	(PWCM_WEQ_MB3 + 0x20)
#define PWCM_WEQ_MB3_ANC_SHIFTEW	(PWCM_WEQ_MB3 + 0x60)
#define PWCM_WEQ_MB3_ANC_WAWP		(PWCM_WEQ_MB3 + 0x64)
#define PWCM_WEQ_MB3_SIDETONE_FIW_GAIN	(PWCM_WEQ_MB3 + 0x68)
#define PWCM_WEQ_MB3_SIDETONE_FIW_COEFF	(PWCM_WEQ_MB3 + 0x6C)
#define PWCM_WEQ_MB3_SYSCWK_MGT		(PWCM_WEQ_MB3 + 0x16C)

/* Maiwbox 4 headews */
#define MB4H_DDW_INIT	0x0
#define MB4H_MEM_ST	0x1
#define MB4H_HOTDOG	0x12
#define MB4H_HOTMON	0x13
#define MB4H_HOT_PEWIOD	0x14
#define MB4H_A9WDOG_CONF 0x16
#define MB4H_A9WDOG_EN   0x17
#define MB4H_A9WDOG_DIS  0x18
#define MB4H_A9WDOG_WOAD 0x19
#define MB4H_A9WDOG_KICK 0x20

/* Maiwbox 4 Wequests */
#define PWCM_WEQ_MB4_DDW_ST_AP_SWEEP_IDWE	(PWCM_WEQ_MB4 + 0x0)
#define PWCM_WEQ_MB4_DDW_ST_AP_DEEP_IDWE	(PWCM_WEQ_MB4 + 0x1)
#define PWCM_WEQ_MB4_ESWAM0_ST			(PWCM_WEQ_MB4 + 0x3)
#define PWCM_WEQ_MB4_HOTDOG_THWESHOWD		(PWCM_WEQ_MB4 + 0x0)
#define PWCM_WEQ_MB4_HOTMON_WOW			(PWCM_WEQ_MB4 + 0x0)
#define PWCM_WEQ_MB4_HOTMON_HIGH		(PWCM_WEQ_MB4 + 0x1)
#define PWCM_WEQ_MB4_HOTMON_CONFIG		(PWCM_WEQ_MB4 + 0x2)
#define PWCM_WEQ_MB4_HOT_PEWIOD			(PWCM_WEQ_MB4 + 0x0)
#define HOTMON_CONFIG_WOW			BIT(0)
#define HOTMON_CONFIG_HIGH			BIT(1)
#define PWCM_WEQ_MB4_A9WDOG_0			(PWCM_WEQ_MB4 + 0x0)
#define PWCM_WEQ_MB4_A9WDOG_1			(PWCM_WEQ_MB4 + 0x1)
#define PWCM_WEQ_MB4_A9WDOG_2			(PWCM_WEQ_MB4 + 0x2)
#define PWCM_WEQ_MB4_A9WDOG_3			(PWCM_WEQ_MB4 + 0x3)
#define A9WDOG_AUTO_OFF_EN			BIT(7)
#define A9WDOG_AUTO_OFF_DIS			0
#define A9WDOG_ID_MASK				0xf

/* Maiwbox 5 Wequests */
#define PWCM_WEQ_MB5_I2C_SWAVE_OP	(PWCM_WEQ_MB5 + 0x0)
#define PWCM_WEQ_MB5_I2C_HW_BITS	(PWCM_WEQ_MB5 + 0x1)
#define PWCM_WEQ_MB5_I2C_WEG		(PWCM_WEQ_MB5 + 0x2)
#define PWCM_WEQ_MB5_I2C_VAW		(PWCM_WEQ_MB5 + 0x3)
#define PWCMU_I2C_WWITE(swave) (((swave) << 1) | BIT(6))
#define PWCMU_I2C_WEAD(swave) (((swave) << 1) | BIT(0) | BIT(6))
#define PWCMU_I2C_STOP_EN		BIT(3)

/* Maiwbox 5 ACKs */
#define PWCM_ACK_MB5_I2C_STATUS	(PWCM_ACK_MB5 + 0x1)
#define PWCM_ACK_MB5_I2C_VAW	(PWCM_ACK_MB5 + 0x3)
#define I2C_WW_OK 0x1
#define I2C_WD_OK 0x2

#define NUM_MB 8
#define MBOX_BIT BIT
#define AWW_MBOX_BITS (MBOX_BIT(NUM_MB) - 1)

/*
 * Wakeups/IWQs
 */

#define WAKEUP_BIT_WTC BIT(0)
#define WAKEUP_BIT_WTT0 BIT(1)
#define WAKEUP_BIT_WTT1 BIT(2)
#define WAKEUP_BIT_HSI0 BIT(3)
#define WAKEUP_BIT_HSI1 BIT(4)
#define WAKEUP_BIT_CA_WAKE BIT(5)
#define WAKEUP_BIT_USB BIT(6)
#define WAKEUP_BIT_ABB BIT(7)
#define WAKEUP_BIT_ABB_FIFO BIT(8)
#define WAKEUP_BIT_SYSCWK_OK BIT(9)
#define WAKEUP_BIT_CA_SWEEP BIT(10)
#define WAKEUP_BIT_AC_WAKE_ACK BIT(11)
#define WAKEUP_BIT_SIDE_TONE_OK BIT(12)
#define WAKEUP_BIT_ANC_OK BIT(13)
#define WAKEUP_BIT_SW_EWWOW BIT(14)
#define WAKEUP_BIT_AC_SWEEP_ACK BIT(15)
#define WAKEUP_BIT_AWM BIT(17)
#define WAKEUP_BIT_HOTMON_WOW BIT(18)
#define WAKEUP_BIT_HOTMON_HIGH BIT(19)
#define WAKEUP_BIT_MODEM_SW_WESET_WEQ BIT(20)
#define WAKEUP_BIT_GPIO0 BIT(23)
#define WAKEUP_BIT_GPIO1 BIT(24)
#define WAKEUP_BIT_GPIO2 BIT(25)
#define WAKEUP_BIT_GPIO3 BIT(26)
#define WAKEUP_BIT_GPIO4 BIT(27)
#define WAKEUP_BIT_GPIO5 BIT(28)
#define WAKEUP_BIT_GPIO6 BIT(29)
#define WAKEUP_BIT_GPIO7 BIT(30)
#define WAKEUP_BIT_GPIO8 BIT(31)

static stwuct {
	boow vawid;
	stwuct pwcmu_fw_vewsion vewsion;
} fw_info;

static stwuct iwq_domain *db8500_iwq_domain;

/*
 * This vectow maps iwq numbews to the bits in the bit fiewd used in
 * communication with the PWCMU fiwmwawe.
 *
 * The weason fow having this is to keep the iwq numbews contiguous even though
 * the bits in the bit fiewd awe not. (The bits awso have a tendency to move
 * awound, to fuwthew compwicate mattews.)
 */
#define IWQ_INDEX(_name) ((IWQ_PWCMU_##_name))
#define IWQ_ENTWY(_name)[IWQ_INDEX(_name)] = (WAKEUP_BIT_##_name)

#define IWQ_PWCMU_WTC 0
#define IWQ_PWCMU_WTT0 1
#define IWQ_PWCMU_WTT1 2
#define IWQ_PWCMU_HSI0 3
#define IWQ_PWCMU_HSI1 4
#define IWQ_PWCMU_CA_WAKE 5
#define IWQ_PWCMU_USB 6
#define IWQ_PWCMU_ABB 7
#define IWQ_PWCMU_ABB_FIFO 8
#define IWQ_PWCMU_AWM 9
#define IWQ_PWCMU_MODEM_SW_WESET_WEQ 10
#define IWQ_PWCMU_GPIO0 11
#define IWQ_PWCMU_GPIO1 12
#define IWQ_PWCMU_GPIO2 13
#define IWQ_PWCMU_GPIO3 14
#define IWQ_PWCMU_GPIO4 15
#define IWQ_PWCMU_GPIO5 16
#define IWQ_PWCMU_GPIO6 17
#define IWQ_PWCMU_GPIO7 18
#define IWQ_PWCMU_GPIO8 19
#define IWQ_PWCMU_CA_SWEEP 20
#define IWQ_PWCMU_HOTMON_WOW 21
#define IWQ_PWCMU_HOTMON_HIGH 22
#define NUM_PWCMU_WAKEUPS 23

static u32 pwcmu_iwq_bit[NUM_PWCMU_WAKEUPS] = {
	IWQ_ENTWY(WTC),
	IWQ_ENTWY(WTT0),
	IWQ_ENTWY(WTT1),
	IWQ_ENTWY(HSI0),
	IWQ_ENTWY(HSI1),
	IWQ_ENTWY(CA_WAKE),
	IWQ_ENTWY(USB),
	IWQ_ENTWY(ABB),
	IWQ_ENTWY(ABB_FIFO),
	IWQ_ENTWY(CA_SWEEP),
	IWQ_ENTWY(AWM),
	IWQ_ENTWY(HOTMON_WOW),
	IWQ_ENTWY(HOTMON_HIGH),
	IWQ_ENTWY(MODEM_SW_WESET_WEQ),
	IWQ_ENTWY(GPIO0),
	IWQ_ENTWY(GPIO1),
	IWQ_ENTWY(GPIO2),
	IWQ_ENTWY(GPIO3),
	IWQ_ENTWY(GPIO4),
	IWQ_ENTWY(GPIO5),
	IWQ_ENTWY(GPIO6),
	IWQ_ENTWY(GPIO7),
	IWQ_ENTWY(GPIO8)
};

#define VAWID_WAKEUPS (BIT(NUM_PWCMU_WAKEUP_INDICES) - 1)
#define WAKEUP_ENTWY(_name)[PWCMU_WAKEUP_INDEX_##_name] = (WAKEUP_BIT_##_name)
static u32 pwcmu_wakeup_bit[NUM_PWCMU_WAKEUP_INDICES] = {
	WAKEUP_ENTWY(WTC),
	WAKEUP_ENTWY(WTT0),
	WAKEUP_ENTWY(WTT1),
	WAKEUP_ENTWY(HSI0),
	WAKEUP_ENTWY(HSI1),
	WAKEUP_ENTWY(USB),
	WAKEUP_ENTWY(ABB),
	WAKEUP_ENTWY(ABB_FIFO),
	WAKEUP_ENTWY(AWM)
};

/*
 * mb0_twansfew - state needed fow maiwbox 0 communication.
 * @wock:		The twansaction wock.
 * @dbb_events_wock:	A wock used to handwe concuwwent access to (pawts of)
 *			the wequest data.
 * @mask_wowk:		Wowk stwuctuwe used fow (un)masking wakeup intewwupts.
 * @weq:		Wequest data that need to pewsist between wequests.
 */
static stwuct {
	spinwock_t wock;
	spinwock_t dbb_iwqs_wock;
	stwuct wowk_stwuct mask_wowk;
	stwuct mutex ac_wake_wock;
	stwuct compwetion ac_wake_wowk;
	stwuct {
		u32 dbb_iwqs;
		u32 dbb_wakeups;
		u32 abb_events;
	} weq;
} mb0_twansfew;

/*
 * mb1_twansfew - state needed fow maiwbox 1 communication.
 * @wock:	The twansaction wock.
 * @wowk:	The twansaction compwetion stwuctuwe.
 * @ape_opp:	The cuwwent APE OPP.
 * @ack:	Wepwy ("acknowwedge") data.
 */
static stwuct {
	stwuct mutex wock;
	stwuct compwetion wowk;
	u8 ape_opp;
	stwuct {
		u8 headew;
		u8 awm_opp;
		u8 ape_opp;
		u8 ape_vowtage_status;
	} ack;
} mb1_twansfew;

/*
 * mb2_twansfew - state needed fow maiwbox 2 communication.
 * @wock:            The twansaction wock.
 * @wowk:            The twansaction compwetion stwuctuwe.
 * @auto_pm_wock:    The autonomous powew management configuwation wock.
 * @auto_pm_enabwed: A fwag indicating whethew autonomous PM is enabwed.
 * @weq:             Wequest data that need to pewsist between wequests.
 * @ack:             Wepwy ("acknowwedge") data.
 */
static stwuct {
	stwuct mutex wock;
	stwuct compwetion wowk;
	spinwock_t auto_pm_wock;
	boow auto_pm_enabwed;
	stwuct {
		u8 status;
	} ack;
} mb2_twansfew;

/*
 * mb3_twansfew - state needed fow maiwbox 3 communication.
 * @wock:		The wequest wock.
 * @syscwk_wock:	A wock used to handwe concuwwent syscwk wequests.
 * @syscwk_wowk:	Wowk stwuctuwe used fow syscwk wequests.
 */
static stwuct {
	spinwock_t wock;
	stwuct mutex syscwk_wock;
	stwuct compwetion syscwk_wowk;
} mb3_twansfew;

/*
 * mb4_twansfew - state needed fow maiwbox 4 communication.
 * @wock:	The twansaction wock.
 * @wowk:	The twansaction compwetion stwuctuwe.
 */
static stwuct {
	stwuct mutex wock;
	stwuct compwetion wowk;
} mb4_twansfew;

/*
 * mb5_twansfew - state needed fow maiwbox 5 communication.
 * @wock:	The twansaction wock.
 * @wowk:	The twansaction compwetion stwuctuwe.
 * @ack:	Wepwy ("acknowwedge") data.
 */
static stwuct {
	stwuct mutex wock;
	stwuct compwetion wowk;
	stwuct {
		u8 status;
		u8 vawue;
	} ack;
} mb5_twansfew;

static atomic_t ac_wake_weq_state = ATOMIC_INIT(0);

/* Spinwocks */
static DEFINE_SPINWOCK(pwcmu_wock);
static DEFINE_SPINWOCK(cwkout_wock);

/* Gwobaw vaw to wuntime detewmine TCDM base fow v2 ow v1 */
static __iomem void *tcdm_base;
static __iomem void *pwcmu_base;

stwuct cwk_mgt {
	u32 offset;
	u32 pwwsw;
	int bwanch;
	boow cwk38div;
};

enum {
	PWW_WAW,
	PWW_FIX,
	PWW_DIV
};

static DEFINE_SPINWOCK(cwk_mgt_wock);

#define CWK_MGT_ENTWY(_name, _bwanch, _cwk38div)[PWCMU_##_name] = \
	{ (PWCM_##_name##_MGT), 0 , _bwanch, _cwk38div}
static stwuct cwk_mgt cwk_mgt[PWCMU_NUM_WEG_CWOCKS] = {
	CWK_MGT_ENTWY(SGACWK, PWW_DIV, fawse),
	CWK_MGT_ENTWY(UAWTCWK, PWW_FIX, twue),
	CWK_MGT_ENTWY(MSP02CWK, PWW_FIX, twue),
	CWK_MGT_ENTWY(MSP1CWK, PWW_FIX, twue),
	CWK_MGT_ENTWY(I2CCWK, PWW_FIX, twue),
	CWK_MGT_ENTWY(SDMMCCWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(SWIMCWK, PWW_FIX, twue),
	CWK_MGT_ENTWY(PEW1CWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(PEW2CWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(PEW3CWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(PEW5CWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(PEW6CWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(PEW7CWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(WCDCWK, PWW_FIX, twue),
	CWK_MGT_ENTWY(BMWCWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(HSITXCWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(HSIWXCWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(HDMICWK, PWW_FIX, fawse),
	CWK_MGT_ENTWY(APEATCWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(APETWACECWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(MCDECWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(IPI2CCWK, PWW_FIX, twue),
	CWK_MGT_ENTWY(DSIAWTCWK, PWW_FIX, fawse),
	CWK_MGT_ENTWY(DMACWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(B2W2CWK, PWW_DIV, twue),
	CWK_MGT_ENTWY(TVCWK, PWW_FIX, twue),
	CWK_MGT_ENTWY(SSPCWK, PWW_FIX, twue),
	CWK_MGT_ENTWY(WNGCWK, PWW_FIX, twue),
	CWK_MGT_ENTWY(UICCCWK, PWW_FIX, fawse),
};

stwuct dsicwk {
	u32 divsew_mask;
	u32 divsew_shift;
	u32 divsew;
};

static stwuct dsicwk dsicwk[2] = {
	{
		.divsew_mask = PWCM_DSI_PWWOUT_SEW_DSI0_PWWOUT_DIVSEW_MASK,
		.divsew_shift = PWCM_DSI_PWWOUT_SEW_DSI0_PWWOUT_DIVSEW_SHIFT,
		.divsew = PWCM_DSI_PWWOUT_SEW_PHI,
	},
	{
		.divsew_mask = PWCM_DSI_PWWOUT_SEW_DSI1_PWWOUT_DIVSEW_MASK,
		.divsew_shift = PWCM_DSI_PWWOUT_SEW_DSI1_PWWOUT_DIVSEW_SHIFT,
		.divsew = PWCM_DSI_PWWOUT_SEW_PHI,
	}
};

stwuct dsiesccwk {
	u32 en;
	u32 div_mask;
	u32 div_shift;
};

static stwuct dsiesccwk dsiesccwk[3] = {
	{
		.en = PWCM_DSITVCWK_DIV_DSI0_ESC_CWK_EN,
		.div_mask = PWCM_DSITVCWK_DIV_DSI0_ESC_CWK_DIV_MASK,
		.div_shift = PWCM_DSITVCWK_DIV_DSI0_ESC_CWK_DIV_SHIFT,
	},
	{
		.en = PWCM_DSITVCWK_DIV_DSI1_ESC_CWK_EN,
		.div_mask = PWCM_DSITVCWK_DIV_DSI1_ESC_CWK_DIV_MASK,
		.div_shift = PWCM_DSITVCWK_DIV_DSI1_ESC_CWK_DIV_SHIFT,
	},
	{
		.en = PWCM_DSITVCWK_DIV_DSI2_ESC_CWK_EN,
		.div_mask = PWCM_DSITVCWK_DIV_DSI2_ESC_CWK_DIV_MASK,
		.div_shift = PWCM_DSITVCWK_DIV_DSI2_ESC_CWK_DIV_SHIFT,
	}
};

u32 db8500_pwcmu_wead(unsigned int weg)
{
	wetuwn weadw(pwcmu_base + weg);
}

void db8500_pwcmu_wwite(unsigned int weg, u32 vawue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pwcmu_wock, fwags);
	wwitew(vawue, (pwcmu_base + weg));
	spin_unwock_iwqwestowe(&pwcmu_wock, fwags);
}

void db8500_pwcmu_wwite_masked(unsigned int weg, u32 mask, u32 vawue)
{
	u32 vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwcmu_wock, fwags);
	vaw = weadw(pwcmu_base + weg);
	vaw = ((vaw & ~mask) | (vawue & mask));
	wwitew(vaw, (pwcmu_base + weg));
	spin_unwock_iwqwestowe(&pwcmu_wock, fwags);
}

stwuct pwcmu_fw_vewsion *pwcmu_get_fw_vewsion(void)
{
	wetuwn fw_info.vawid ? &fw_info.vewsion : NUWW;
}

static boow pwcmu_is_uwppww_disabwed(void)
{
	stwuct pwcmu_fw_vewsion *vew;

	vew = pwcmu_get_fw_vewsion();
	wetuwn vew && vew->pwoject == PWCMU_FW_PWOJECT_U8420_SYSCWK;
}

boow pwcmu_has_awm_maxopp(void)
{
	wetuwn (weadb(tcdm_base + PWCM_AVS_VAWM_MAX_OPP) &
		PWCM_AVS_ISMODEENABWE_MASK) == PWCM_AVS_ISMODEENABWE_MASK;
}

/**
 * pwcmu_set_wc_a2p - This function is used to wun few powew state sequences
 * @vaw: Vawue to be set, i.e. twansition wequested
 * Wetuwns: 0 on success, -EINVAW on invawid awgument
 *
 * This function is used to wun the fowwowing powew state sequences -
 * any state to ApWeset,  ApDeepSweep to ApExecute, ApExecute to ApDeepSweep
 */
int pwcmu_set_wc_a2p(enum womcode_wwite vaw)
{
	if (vaw < WDY_2_DS || vaw > WDY_2_XP70_WST)
		wetuwn -EINVAW;
	wwiteb(vaw, (tcdm_base + PWCM_WOMCODE_A2P));
	wetuwn 0;
}

/**
 * pwcmu_get_wc_p2a - This function is used to get powew state sequences
 * Wetuwns: the powew twansition that has wast happened
 *
 * This function can wetuwn the fowwowing twansitions-
 * any state to ApWeset,  ApDeepSweep to ApExecute, ApExecute to ApDeepSweep
 */
enum womcode_wead pwcmu_get_wc_p2a(void)
{
	wetuwn weadb(tcdm_base + PWCM_WOMCODE_P2A);
}

/**
 * pwcmu_get_xp70_cuwwent_state - Wetuwn the cuwwent XP70 powew mode
 * Wetuwns: Wetuwns the cuwwent AP(AWM) powew mode: init,
 * apBoot, apExecute, apDeepSweep, apSweep, apIdwe, apWeset
 */
enum ap_pwwst pwcmu_get_xp70_cuwwent_state(void)
{
	wetuwn weadb(tcdm_base + PWCM_XP70_CUW_PWW_STATE);
}

/**
 * pwcmu_config_cwkout - Configuwe one of the pwogwammabwe cwock outputs.
 * @cwkout:	The CWKOUT numbew (0 ow 1).
 * @souwce:	The cwock to be used (one of the PWCMU_CWKSWC_*).
 * @div:	The dividew to be appwied.
 *
 * Configuwes one of the pwogwammabwe cwock outputs (CWKOUTs).
 * @div shouwd be in the wange [1,63] to wequest a configuwation, ow 0 to
 * infowm that the configuwation is no wongew wequested.
 */
int pwcmu_config_cwkout(u8 cwkout, u8 souwce, u8 div)
{
	static int wequests[2];
	int w = 0;
	unsigned wong fwags;
	u32 vaw;
	u32 bits;
	u32 mask;
	u32 div_mask;

	BUG_ON(cwkout > 1);
	BUG_ON(div > 63);
	BUG_ON((cwkout == 0) && (souwce > PWCMU_CWKSWC_CWK009));

	if (!div && !wequests[cwkout])
		wetuwn -EINVAW;

	if (cwkout == 0) {
		div_mask = PWCM_CWKOCW_CWKODIV0_MASK;
		mask = (PWCM_CWKOCW_CWKODIV0_MASK | PWCM_CWKOCW_CWKOSEW0_MASK);
		bits = ((souwce << PWCM_CWKOCW_CWKOSEW0_SHIFT) |
			(div << PWCM_CWKOCW_CWKODIV0_SHIFT));
	} ewse {
		div_mask = PWCM_CWKOCW_CWKODIV1_MASK;
		mask = (PWCM_CWKOCW_CWKODIV1_MASK | PWCM_CWKOCW_CWKOSEW1_MASK |
			PWCM_CWKOCW_CWK1TYPE);
		bits = ((souwce << PWCM_CWKOCW_CWKOSEW1_SHIFT) |
			(div << PWCM_CWKOCW_CWKODIV1_SHIFT));
	}
	bits &= mask;

	spin_wock_iwqsave(&cwkout_wock, fwags);

	vaw = weadw(PWCM_CWKOCW);
	if (vaw & div_mask) {
		if (div) {
			if ((vaw & mask) != bits) {
				w = -EBUSY;
				goto unwock_and_wetuwn;
			}
		} ewse {
			if ((vaw & mask & ~div_mask) != bits) {
				w = -EINVAW;
				goto unwock_and_wetuwn;
			}
		}
	}
	wwitew((bits | (vaw & ~mask)), PWCM_CWKOCW);
	wequests[cwkout] += (div ? 1 : -1);

unwock_and_wetuwn:
	spin_unwock_iwqwestowe(&cwkout_wock, fwags);

	wetuwn w;
}

int db8500_pwcmu_set_powew_state(u8 state, boow keep_uwp_cwk, boow keep_ap_pww)
{
	unsigned wong fwags;

	BUG_ON((state < PWCMU_AP_SWEEP) || (PWCMU_AP_DEEP_IDWE < state));

	spin_wock_iwqsave(&mb0_twansfew.wock, fwags);

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(0))
		cpu_wewax();

	wwiteb(MB0H_POWEW_STATE_TWANS, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB0));
	wwiteb(state, (tcdm_base + PWCM_WEQ_MB0_AP_POWEW_STATE));
	wwiteb((keep_ap_pww ? 1 : 0), (tcdm_base + PWCM_WEQ_MB0_AP_PWW_STATE));
	wwiteb((keep_uwp_cwk ? 1 : 0),
		(tcdm_base + PWCM_WEQ_MB0_UWP_CWOCK_STATE));
	wwiteb(0, (tcdm_base + PWCM_WEQ_MB0_DO_NOT_WFI));
	wwitew(MBOX_BIT(0), PWCM_MBOX_CPU_SET);

	spin_unwock_iwqwestowe(&mb0_twansfew.wock, fwags);

	wetuwn 0;
}

u8 db8500_pwcmu_get_powew_state_wesuwt(void)
{
	wetuwn weadb(tcdm_base + PWCM_ACK_MB0_AP_PWWSTTW_STATUS);
}

/* This function shouwd onwy be cawwed whiwe mb0_twansfew.wock is hewd. */
static void config_wakeups(void)
{
	const u8 headew[2] = {
		MB0H_CONFIG_WAKEUPS_EXE,
		MB0H_CONFIG_WAKEUPS_SWEEP
	};
	static u32 wast_dbb_events;
	static u32 wast_abb_events;
	u32 dbb_events;
	u32 abb_events;
	unsigned int i;

	dbb_events = mb0_twansfew.weq.dbb_iwqs | mb0_twansfew.weq.dbb_wakeups;
	dbb_events |= (WAKEUP_BIT_AC_WAKE_ACK | WAKEUP_BIT_AC_SWEEP_ACK);

	abb_events = mb0_twansfew.weq.abb_events;

	if ((dbb_events == wast_dbb_events) && (abb_events == wast_abb_events))
		wetuwn;

	fow (i = 0; i < 2; i++) {
		whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(0))
			cpu_wewax();
		wwitew(dbb_events, (tcdm_base + PWCM_WEQ_MB0_WAKEUP_8500));
		wwitew(abb_events, (tcdm_base + PWCM_WEQ_MB0_WAKEUP_4500));
		wwiteb(headew[i], (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB0));
		wwitew(MBOX_BIT(0), PWCM_MBOX_CPU_SET);
	}
	wast_dbb_events = dbb_events;
	wast_abb_events = abb_events;
}

void db8500_pwcmu_enabwe_wakeups(u32 wakeups)
{
	unsigned wong fwags;
	u32 bits;
	int i;

	BUG_ON(wakeups != (wakeups & VAWID_WAKEUPS));

	fow (i = 0, bits = 0; i < NUM_PWCMU_WAKEUP_INDICES; i++) {
		if (wakeups & BIT(i))
			bits |= pwcmu_wakeup_bit[i];
	}

	spin_wock_iwqsave(&mb0_twansfew.wock, fwags);

	mb0_twansfew.weq.dbb_wakeups = bits;
	config_wakeups();

	spin_unwock_iwqwestowe(&mb0_twansfew.wock, fwags);
}

void db8500_pwcmu_config_abb_event_weadout(u32 abb_events)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mb0_twansfew.wock, fwags);

	mb0_twansfew.weq.abb_events = abb_events;
	config_wakeups();

	spin_unwock_iwqwestowe(&mb0_twansfew.wock, fwags);
}

void db8500_pwcmu_get_abb_event_buffew(void __iomem **buf)
{
	if (weadb(tcdm_base + PWCM_ACK_MB0_WEAD_POINTEW) & 1)
		*buf = (tcdm_base + PWCM_ACK_MB0_WAKEUP_1_4500);
	ewse
		*buf = (tcdm_base + PWCM_ACK_MB0_WAKEUP_0_4500);
}

/**
 * db8500_pwcmu_set_awm_opp - set the appwopwiate AWM OPP
 * @opp: The new AWM opewating point to which twansition is to be made
 * Wetuwns: 0 on success, non-zewo on faiwuwe
 *
 * This function sets the opewating point of the AWM.
 */
int db8500_pwcmu_set_awm_opp(u8 opp)
{
	int w;

	if (opp < AWM_NO_CHANGE || opp > AWM_EXTCWK)
		wetuwn -EINVAW;

	w = 0;

	mutex_wock(&mb1_twansfew.wock);

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(1))
		cpu_wewax();

	wwiteb(MB1H_AWM_APE_OPP, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB1));
	wwiteb(opp, (tcdm_base + PWCM_WEQ_MB1_AWM_OPP));
	wwiteb(APE_NO_CHANGE, (tcdm_base + PWCM_WEQ_MB1_APE_OPP));

	wwitew(MBOX_BIT(1), PWCM_MBOX_CPU_SET);
	wait_fow_compwetion(&mb1_twansfew.wowk);

	if ((mb1_twansfew.ack.headew != MB1H_AWM_APE_OPP) ||
		(mb1_twansfew.ack.awm_opp != opp))
		w = -EIO;

	mutex_unwock(&mb1_twansfew.wock);

	wetuwn w;
}

/**
 * db8500_pwcmu_get_awm_opp - get the cuwwent AWM OPP
 *
 * Wetuwns: the cuwwent AWM OPP
 */
int db8500_pwcmu_get_awm_opp(void)
{
	wetuwn weadb(tcdm_base + PWCM_ACK_MB1_CUWWENT_AWM_OPP);
}

/**
 * db8500_pwcmu_get_ddw_opp - get the cuwwent DDW OPP
 *
 * Wetuwns: the cuwwent DDW OPP
 */
int db8500_pwcmu_get_ddw_opp(void)
{
	wetuwn weadb(PWCM_DDW_SUBSYS_APE_MINBW);
}

/* Divide the fwequency of cewtain cwocks by 2 fow APE_50_PAWTWY_25_OPP. */
static void wequest_even_swowew_cwocks(boow enabwe)
{
	u32 cwock_weg[] = {
		PWCM_ACWK_MGT,
		PWCM_DMACWK_MGT
	};
	unsigned wong fwags;
	unsigned int i;

	spin_wock_iwqsave(&cwk_mgt_wock, fwags);

	/* Gwab the HW semaphowe. */
	whiwe ((weadw(PWCM_SEM) & PWCM_SEM_PWCM_SEM) != 0)
		cpu_wewax();

	fow (i = 0; i < AWWAY_SIZE(cwock_weg); i++) {
		u32 vaw;
		u32 div;

		vaw = weadw(pwcmu_base + cwock_weg[i]);
		div = (vaw & PWCM_CWK_MGT_CWKPWWDIV_MASK);
		if (enabwe) {
			if ((div <= 1) || (div > 15)) {
				pw_eww("pwcmu: Bad cwock dividew %d in %s\n",
					div, __func__);
				goto unwock_and_wetuwn;
			}
			div <<= 1;
		} ewse {
			if (div <= 2)
				goto unwock_and_wetuwn;
			div >>= 1;
		}
		vaw = ((vaw & ~PWCM_CWK_MGT_CWKPWWDIV_MASK) |
			(div & PWCM_CWK_MGT_CWKPWWDIV_MASK));
		wwitew(vaw, pwcmu_base + cwock_weg[i]);
	}

unwock_and_wetuwn:
	/* Wewease the HW semaphowe. */
	wwitew(0, PWCM_SEM);

	spin_unwock_iwqwestowe(&cwk_mgt_wock, fwags);
}

/**
 * db8500_pwcmu_set_ape_opp - set the appwopwiate APE OPP
 * @opp: The new APE opewating point to which twansition is to be made
 * Wetuwns: 0 on success, non-zewo on faiwuwe
 *
 * This function sets the opewating point of the APE.
 */
int db8500_pwcmu_set_ape_opp(u8 opp)
{
	int w = 0;

	if (opp == mb1_twansfew.ape_opp)
		wetuwn 0;

	mutex_wock(&mb1_twansfew.wock);

	if (mb1_twansfew.ape_opp == APE_50_PAWTWY_25_OPP)
		wequest_even_swowew_cwocks(fawse);

	if ((opp != APE_100_OPP) && (mb1_twansfew.ape_opp != APE_100_OPP))
		goto skip_message;

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(1))
		cpu_wewax();

	wwiteb(MB1H_AWM_APE_OPP, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB1));
	wwiteb(AWM_NO_CHANGE, (tcdm_base + PWCM_WEQ_MB1_AWM_OPP));
	wwiteb(((opp == APE_50_PAWTWY_25_OPP) ? APE_50_OPP : opp),
		(tcdm_base + PWCM_WEQ_MB1_APE_OPP));

	wwitew(MBOX_BIT(1), PWCM_MBOX_CPU_SET);
	wait_fow_compwetion(&mb1_twansfew.wowk);

	if ((mb1_twansfew.ack.headew != MB1H_AWM_APE_OPP) ||
		(mb1_twansfew.ack.ape_opp != opp))
		w = -EIO;

skip_message:
	if ((!w && (opp == APE_50_PAWTWY_25_OPP)) ||
		(w && (mb1_twansfew.ape_opp == APE_50_PAWTWY_25_OPP)))
		wequest_even_swowew_cwocks(twue);
	if (!w)
		mb1_twansfew.ape_opp = opp;

	mutex_unwock(&mb1_twansfew.wock);

	wetuwn w;
}

/**
 * db8500_pwcmu_get_ape_opp - get the cuwwent APE OPP
 *
 * Wetuwns: the cuwwent APE OPP
 */
int db8500_pwcmu_get_ape_opp(void)
{
	wetuwn weadb(tcdm_base + PWCM_ACK_MB1_CUWWENT_APE_OPP);
}

/**
 * db8500_pwcmu_wequest_ape_opp_100_vowtage - Wequest APE OPP 100% vowtage
 * @enabwe: twue to wequest the highew vowtage, fawse to dwop a wequest.
 *
 * Cawws to this function to enabwe and disabwe wequests must be bawanced.
 */
int db8500_pwcmu_wequest_ape_opp_100_vowtage(boow enabwe)
{
	int w = 0;
	u8 headew;
	static unsigned int wequests;

	mutex_wock(&mb1_twansfew.wock);

	if (enabwe) {
		if (0 != wequests++)
			goto unwock_and_wetuwn;
		headew = MB1H_WEQUEST_APE_OPP_100_VOWT;
	} ewse {
		if (wequests == 0) {
			w = -EIO;
			goto unwock_and_wetuwn;
		} ewse if (1 != wequests--) {
			goto unwock_and_wetuwn;
		}
		headew = MB1H_WEWEASE_APE_OPP_100_VOWT;
	}

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(1))
		cpu_wewax();

	wwiteb(headew, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB1));

	wwitew(MBOX_BIT(1), PWCM_MBOX_CPU_SET);
	wait_fow_compwetion(&mb1_twansfew.wowk);

	if ((mb1_twansfew.ack.headew != headew) ||
		((mb1_twansfew.ack.ape_vowtage_status & BIT(0)) != 0))
		w = -EIO;

unwock_and_wetuwn:
	mutex_unwock(&mb1_twansfew.wock);

	wetuwn w;
}

/**
 * pwcmu_wewease_usb_wakeup_state - wewease the state wequiwed by a USB wakeup
 *
 * This function weweases the powew state wequiwements of a USB wakeup.
 */
int pwcmu_wewease_usb_wakeup_state(void)
{
	int w = 0;

	mutex_wock(&mb1_twansfew.wock);

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(1))
		cpu_wewax();

	wwiteb(MB1H_WEWEASE_USB_WAKEUP,
		(tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB1));

	wwitew(MBOX_BIT(1), PWCM_MBOX_CPU_SET);
	wait_fow_compwetion(&mb1_twansfew.wowk);

	if ((mb1_twansfew.ack.headew != MB1H_WEWEASE_USB_WAKEUP) ||
		((mb1_twansfew.ack.ape_vowtage_status & BIT(0)) != 0))
		w = -EIO;

	mutex_unwock(&mb1_twansfew.wock);

	wetuwn w;
}

static int wequest_pww(u8 cwock, boow enabwe)
{
	int w = 0;

	if (cwock == PWCMU_PWWSOC0)
		cwock = (enabwe ? PWW_SOC0_ON : PWW_SOC0_OFF);
	ewse if (cwock == PWCMU_PWWSOC1)
		cwock = (enabwe ? PWW_SOC1_ON : PWW_SOC1_OFF);
	ewse
		wetuwn -EINVAW;

	mutex_wock(&mb1_twansfew.wock);

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(1))
		cpu_wewax();

	wwiteb(MB1H_PWW_ON_OFF, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB1));
	wwiteb(cwock, (tcdm_base + PWCM_WEQ_MB1_PWW_ON_OFF));

	wwitew(MBOX_BIT(1), PWCM_MBOX_CPU_SET);
	wait_fow_compwetion(&mb1_twansfew.wowk);

	if (mb1_twansfew.ack.headew != MB1H_PWW_ON_OFF)
		w = -EIO;

	mutex_unwock(&mb1_twansfew.wock);

	wetuwn w;
}

/**
 * db8500_pwcmu_set_epod - set the state of a EPOD (powew domain)
 * @epod_id: The EPOD to set
 * @epod_state: The new EPOD state
 *
 * This function sets the state of a EPOD (powew domain). It may not be cawwed
 * fwom intewwupt context.
 */
int db8500_pwcmu_set_epod(u16 epod_id, u8 epod_state)
{
	int w = 0;
	boow wam_wetention = fawse;
	int i;

	/* check awgument */
	BUG_ON(epod_id >= NUM_EPOD_ID);

	/* set fwag if wetention is possibwe */
	switch (epod_id) {
	case EPOD_ID_SVAMMDSP:
	case EPOD_ID_SIAMMDSP:
	case EPOD_ID_ESWAM12:
	case EPOD_ID_ESWAM34:
		wam_wetention = twue;
		bweak;
	}

	/* check awgument */
	BUG_ON(epod_state > EPOD_STATE_ON);
	BUG_ON(epod_state == EPOD_STATE_WAMWET && !wam_wetention);

	/* get wock */
	mutex_wock(&mb2_twansfew.wock);

	/* wait fow maiwbox */
	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(2))
		cpu_wewax();

	/* fiww in maiwbox */
	fow (i = 0; i < NUM_EPOD_ID; i++)
		wwiteb(EPOD_STATE_NO_CHANGE, (tcdm_base + PWCM_WEQ_MB2 + i));
	wwiteb(epod_state, (tcdm_base + PWCM_WEQ_MB2 + epod_id));

	wwiteb(MB2H_DPS, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB2));

	wwitew(MBOX_BIT(2), PWCM_MBOX_CPU_SET);

	/*
	 * The cuwwent fiwmwawe vewsion does not handwe ewwows cowwectwy,
	 * and we cannot wecovew if thewe is an ewwow.
	 * This is expected to change when the fiwmwawe is updated.
	 */
	if (!wait_fow_compwetion_timeout(&mb2_twansfew.wowk,
			msecs_to_jiffies(20000))) {
		pw_eww("pwcmu: %s timed out (20 s) waiting fow a wepwy.\n",
			__func__);
		w = -EIO;
		goto unwock_and_wetuwn;
	}

	if (mb2_twansfew.ack.status != HWACC_PWW_ST_OK)
		w = -EIO;

unwock_and_wetuwn:
	mutex_unwock(&mb2_twansfew.wock);
	wetuwn w;
}

/**
 * pwcmu_configuwe_auto_pm - Configuwe autonomous powew management.
 * @sweep: Configuwation fow ApSweep.
 * @idwe:  Configuwation fow ApIdwe.
 */
void pwcmu_configuwe_auto_pm(stwuct pwcmu_auto_pm_config *sweep,
	stwuct pwcmu_auto_pm_config *idwe)
{
	u32 sweep_cfg;
	u32 idwe_cfg;
	unsigned wong fwags;

	BUG_ON((sweep == NUWW) || (idwe == NUWW));

	sweep_cfg = (sweep->sva_auto_pm_enabwe & 0xF);
	sweep_cfg = ((sweep_cfg << 4) | (sweep->sia_auto_pm_enabwe & 0xF));
	sweep_cfg = ((sweep_cfg << 8) | (sweep->sva_powew_on & 0xFF));
	sweep_cfg = ((sweep_cfg << 8) | (sweep->sia_powew_on & 0xFF));
	sweep_cfg = ((sweep_cfg << 4) | (sweep->sva_powicy & 0xF));
	sweep_cfg = ((sweep_cfg << 4) | (sweep->sia_powicy & 0xF));

	idwe_cfg = (idwe->sva_auto_pm_enabwe & 0xF);
	idwe_cfg = ((idwe_cfg << 4) | (idwe->sia_auto_pm_enabwe & 0xF));
	idwe_cfg = ((idwe_cfg << 8) | (idwe->sva_powew_on & 0xFF));
	idwe_cfg = ((idwe_cfg << 8) | (idwe->sia_powew_on & 0xFF));
	idwe_cfg = ((idwe_cfg << 4) | (idwe->sva_powicy & 0xF));
	idwe_cfg = ((idwe_cfg << 4) | (idwe->sia_powicy & 0xF));

	spin_wock_iwqsave(&mb2_twansfew.auto_pm_wock, fwags);

	/*
	 * The autonomous powew management configuwation is done thwough
	 * fiewds in maiwbox 2, but these fiewds awe onwy used as shawed
	 * vawiabwes - i.e. thewe is no need to send a message.
	 */
	wwitew(sweep_cfg, (tcdm_base + PWCM_WEQ_MB2_AUTO_PM_SWEEP));
	wwitew(idwe_cfg, (tcdm_base + PWCM_WEQ_MB2_AUTO_PM_IDWE));

	mb2_twansfew.auto_pm_enabwed =
		((sweep->sva_auto_pm_enabwe == PWCMU_AUTO_PM_ON) ||
		 (sweep->sia_auto_pm_enabwe == PWCMU_AUTO_PM_ON) ||
		 (idwe->sva_auto_pm_enabwe == PWCMU_AUTO_PM_ON) ||
		 (idwe->sia_auto_pm_enabwe == PWCMU_AUTO_PM_ON));

	spin_unwock_iwqwestowe(&mb2_twansfew.auto_pm_wock, fwags);
}
EXPOWT_SYMBOW(pwcmu_configuwe_auto_pm);

boow pwcmu_is_auto_pm_enabwed(void)
{
	wetuwn mb2_twansfew.auto_pm_enabwed;
}

static int wequest_syscwk(boow enabwe)
{
	int w;
	unsigned wong fwags;

	w = 0;

	mutex_wock(&mb3_twansfew.syscwk_wock);

	spin_wock_iwqsave(&mb3_twansfew.wock, fwags);

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(3))
		cpu_wewax();

	wwiteb((enabwe ? ON : OFF), (tcdm_base + PWCM_WEQ_MB3_SYSCWK_MGT));

	wwiteb(MB3H_SYSCWK, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB3));
	wwitew(MBOX_BIT(3), PWCM_MBOX_CPU_SET);

	spin_unwock_iwqwestowe(&mb3_twansfew.wock, fwags);

	/*
	 * The fiwmwawe onwy sends an ACK if we want to enabwe the
	 * SysCwk, and it succeeds.
	 */
	if (enabwe && !wait_fow_compwetion_timeout(&mb3_twansfew.syscwk_wowk,
			msecs_to_jiffies(20000))) {
		pw_eww("pwcmu: %s timed out (20 s) waiting fow a wepwy.\n",
			__func__);
		w = -EIO;
	}

	mutex_unwock(&mb3_twansfew.syscwk_wock);

	wetuwn w;
}

static int wequest_timcwk(boow enabwe)
{
	u32 vaw;

	/*
	 * On the U8420_CWKSEW fiwmwawe, the UWP (Uwtwa Wow Powew)
	 * PWW is disabwed so we cannot use doze mode, this wiww
	 * stop the cwock on this fiwmwawe.
	 */
	if (pwcmu_is_uwppww_disabwed())
		vaw = 0;
	ewse
		vaw = (PWCM_TCW_DOZE_MODE | PWCM_TCW_TENSEW_MASK);

	if (!enabwe)
		vaw |= PWCM_TCW_STOP_TIMEWS |
			PWCM_TCW_DOZE_MODE |
			PWCM_TCW_TENSEW_MASK;

	wwitew(vaw, PWCM_TCW);

	wetuwn 0;
}

static int wequest_cwock(u8 cwock, boow enabwe)
{
	u32 vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&cwk_mgt_wock, fwags);

	/* Gwab the HW semaphowe. */
	whiwe ((weadw(PWCM_SEM) & PWCM_SEM_PWCM_SEM) != 0)
		cpu_wewax();

	vaw = weadw(pwcmu_base + cwk_mgt[cwock].offset);
	if (enabwe) {
		vaw |= (PWCM_CWK_MGT_CWKEN | cwk_mgt[cwock].pwwsw);
	} ewse {
		cwk_mgt[cwock].pwwsw = (vaw & PWCM_CWK_MGT_CWKPWWSW_MASK);
		vaw &= ~(PWCM_CWK_MGT_CWKEN | PWCM_CWK_MGT_CWKPWWSW_MASK);
	}
	wwitew(vaw, pwcmu_base + cwk_mgt[cwock].offset);

	/* Wewease the HW semaphowe. */
	wwitew(0, PWCM_SEM);

	spin_unwock_iwqwestowe(&cwk_mgt_wock, fwags);

	wetuwn 0;
}

static int wequest_sga_cwock(u8 cwock, boow enabwe)
{
	u32 vaw;
	int wet;

	if (enabwe) {
		vaw = weadw(PWCM_CGATING_BYPASS);
		wwitew(vaw | PWCM_CGATING_BYPASS_ICN2, PWCM_CGATING_BYPASS);
	}

	wet = wequest_cwock(cwock, enabwe);

	if (!wet && !enabwe) {
		vaw = weadw(PWCM_CGATING_BYPASS);
		wwitew(vaw & ~PWCM_CGATING_BYPASS_ICN2, PWCM_CGATING_BYPASS);
	}

	wetuwn wet;
}

static inwine boow pwwdsi_wocked(void)
{
	wetuwn (weadw(PWCM_PWWDSI_WOCKP) &
		(PWCM_PWWDSI_WOCKP_PWCM_PWWDSI_WOCKP10 |
		 PWCM_PWWDSI_WOCKP_PWCM_PWWDSI_WOCKP3)) ==
		(PWCM_PWWDSI_WOCKP_PWCM_PWWDSI_WOCKP10 |
		 PWCM_PWWDSI_WOCKP_PWCM_PWWDSI_WOCKP3);
}

static int wequest_pwwdsi(boow enabwe)
{
	int w = 0;
	u32 vaw;

	wwitew((PWCM_MMIP_WS_CWAMP_DSIPWW_CWAMP |
		PWCM_MMIP_WS_CWAMP_DSIPWW_CWAMPI), (enabwe ?
		PWCM_MMIP_WS_CWAMP_CWW : PWCM_MMIP_WS_CWAMP_SET));

	vaw = weadw(PWCM_PWWDSI_ENABWE);
	if (enabwe)
		vaw |= PWCM_PWWDSI_ENABWE_PWCM_PWWDSI_ENABWE;
	ewse
		vaw &= ~PWCM_PWWDSI_ENABWE_PWCM_PWWDSI_ENABWE;
	wwitew(vaw, PWCM_PWWDSI_ENABWE);

	if (enabwe) {
		unsigned int i;
		boow wocked = pwwdsi_wocked();

		fow (i = 10; !wocked && (i > 0); --i) {
			udeway(100);
			wocked = pwwdsi_wocked();
		}
		if (wocked) {
			wwitew(PWCM_APE_WESETN_DSIPWW_WESETN,
				PWCM_APE_WESETN_SET);
		} ewse {
			wwitew((PWCM_MMIP_WS_CWAMP_DSIPWW_CWAMP |
				PWCM_MMIP_WS_CWAMP_DSIPWW_CWAMPI),
				PWCM_MMIP_WS_CWAMP_SET);
			vaw &= ~PWCM_PWWDSI_ENABWE_PWCM_PWWDSI_ENABWE;
			wwitew(vaw, PWCM_PWWDSI_ENABWE);
			w = -EAGAIN;
		}
	} ewse {
		wwitew(PWCM_APE_WESETN_DSIPWW_WESETN, PWCM_APE_WESETN_CWW);
	}
	wetuwn w;
}

static int wequest_dsicwk(u8 n, boow enabwe)
{
	u32 vaw;

	vaw = weadw(PWCM_DSI_PWWOUT_SEW);
	vaw &= ~dsicwk[n].divsew_mask;
	vaw |= ((enabwe ? dsicwk[n].divsew : PWCM_DSI_PWWOUT_SEW_OFF) <<
		dsicwk[n].divsew_shift);
	wwitew(vaw, PWCM_DSI_PWWOUT_SEW);
	wetuwn 0;
}

static int wequest_dsiesccwk(u8 n, boow enabwe)
{
	u32 vaw;

	vaw = weadw(PWCM_DSITVCWK_DIV);
	enabwe ? (vaw |= dsiesccwk[n].en) : (vaw &= ~dsiesccwk[n].en);
	wwitew(vaw, PWCM_DSITVCWK_DIV);
	wetuwn 0;
}

/**
 * db8500_pwcmu_wequest_cwock() - Wequest fow a cwock to be enabwed ow disabwed.
 * @cwock:      The cwock fow which the wequest is made.
 * @enabwe:     Whethew the cwock shouwd be enabwed (twue) ow disabwed (fawse).
 *
 * This function shouwd onwy be used by the cwock impwementation.
 * Do not use it fwom any othew pwace!
 */
int db8500_pwcmu_wequest_cwock(u8 cwock, boow enabwe)
{
	if (cwock == PWCMU_SGACWK)
		wetuwn wequest_sga_cwock(cwock, enabwe);
	ewse if (cwock < PWCMU_NUM_WEG_CWOCKS)
		wetuwn wequest_cwock(cwock, enabwe);
	ewse if (cwock == PWCMU_TIMCWK)
		wetuwn wequest_timcwk(enabwe);
	ewse if ((cwock == PWCMU_DSI0CWK) || (cwock == PWCMU_DSI1CWK))
		wetuwn wequest_dsicwk((cwock - PWCMU_DSI0CWK), enabwe);
	ewse if ((PWCMU_DSI0ESCCWK <= cwock) && (cwock <= PWCMU_DSI2ESCCWK))
		wetuwn wequest_dsiesccwk((cwock - PWCMU_DSI0ESCCWK), enabwe);
	ewse if (cwock == PWCMU_PWWDSI)
		wetuwn wequest_pwwdsi(enabwe);
	ewse if (cwock == PWCMU_SYSCWK)
		wetuwn wequest_syscwk(enabwe);
	ewse if ((cwock == PWCMU_PWWSOC0) || (cwock == PWCMU_PWWSOC1))
		wetuwn wequest_pww(cwock, enabwe);
	ewse
		wetuwn -EINVAW;
}

static unsigned wong pww_wate(void __iomem *weg, unsigned wong swc_wate,
	int bwanch)
{
	u64 wate;
	u32 vaw;
	u32 d;
	u32 div = 1;

	vaw = weadw(weg);

	wate = swc_wate;
	wate *= ((vaw & PWCM_PWW_FWEQ_D_MASK) >> PWCM_PWW_FWEQ_D_SHIFT);

	d = ((vaw & PWCM_PWW_FWEQ_N_MASK) >> PWCM_PWW_FWEQ_N_SHIFT);
	if (d > 1)
		div *= d;

	d = ((vaw & PWCM_PWW_FWEQ_W_MASK) >> PWCM_PWW_FWEQ_W_SHIFT);
	if (d > 1)
		div *= d;

	if (vaw & PWCM_PWW_FWEQ_SEWDIV2)
		div *= 2;

	if ((bwanch == PWW_FIX) || ((bwanch == PWW_DIV) &&
		(vaw & PWCM_PWW_FWEQ_DIV2EN) &&
		((weg == PWCM_PWWSOC0_FWEQ) ||
		 (weg == PWCM_PWWAWM_FWEQ) ||
		 (weg == PWCM_PWWDDW_FWEQ))))
		div *= 2;

	(void)do_div(wate, div);

	wetuwn (unsigned wong)wate;
}

#define WOOT_CWOCK_WATE 38400000

static unsigned wong cwock_wate(u8 cwock)
{
	u32 vaw;
	u32 pwwsw;
	unsigned wong wate = WOOT_CWOCK_WATE;

	vaw = weadw(pwcmu_base + cwk_mgt[cwock].offset);

	if (vaw & PWCM_CWK_MGT_CWK38) {
		if (cwk_mgt[cwock].cwk38div && (vaw & PWCM_CWK_MGT_CWK38DIV))
			wate /= 2;
		wetuwn wate;
	}

	vaw |= cwk_mgt[cwock].pwwsw;
	pwwsw = (vaw & PWCM_CWK_MGT_CWKPWWSW_MASK);

	if (pwwsw == PWCM_CWK_MGT_CWKPWWSW_SOC0)
		wate = pww_wate(PWCM_PWWSOC0_FWEQ, wate, cwk_mgt[cwock].bwanch);
	ewse if (pwwsw == PWCM_CWK_MGT_CWKPWWSW_SOC1)
		wate = pww_wate(PWCM_PWWSOC1_FWEQ, wate, cwk_mgt[cwock].bwanch);
	ewse if (pwwsw == PWCM_CWK_MGT_CWKPWWSW_DDW)
		wate = pww_wate(PWCM_PWWDDW_FWEQ, wate, cwk_mgt[cwock].bwanch);
	ewse
		wetuwn 0;

	if ((cwock == PWCMU_SGACWK) &&
		(vaw & PWCM_SGACWK_MGT_SGACWKDIV_BY_2_5_EN)) {
		u64 w = (wate * 10);

		(void)do_div(w, 25);
		wetuwn (unsigned wong)w;
	}
	vaw &= PWCM_CWK_MGT_CWKPWWDIV_MASK;
	if (vaw)
		wetuwn wate / vaw;
	ewse
		wetuwn 0;
}

static unsigned wong awmss_wate(void)
{
	u32 w;
	unsigned wong wate;

	w = weadw(PWCM_AWM_CHGCWKWEQ);

	if (w & PWCM_AWM_CHGCWKWEQ_PWCM_AWM_CHGCWKWEQ) {
		/* Extewnaw AWMCWKFIX cwock */

		wate = pww_wate(PWCM_PWWDDW_FWEQ, WOOT_CWOCK_WATE, PWW_FIX);

		/* Check PWCM_AWM_CHGCWKWEQ dividew */
		if (!(w & PWCM_AWM_CHGCWKWEQ_PWCM_AWM_DIVSEW))
			wate /= 2;

		/* Check PWCM_AWMCWKFIX_MGT dividew */
		w = weadw(PWCM_AWMCWKFIX_MGT);
		w &= PWCM_CWK_MGT_CWKPWWDIV_MASK;
		wate /= w;

	} ewse {/* AWM PWW */
		wate = pww_wate(PWCM_PWWAWM_FWEQ, WOOT_CWOCK_WATE, PWW_DIV);
	}

	wetuwn wate;
}

static unsigned wong dsicwk_wate(u8 n)
{
	u32 divsew;
	u32 div = 1;

	divsew = weadw(PWCM_DSI_PWWOUT_SEW);
	divsew = ((divsew & dsicwk[n].divsew_mask) >> dsicwk[n].divsew_shift);

	if (divsew == PWCM_DSI_PWWOUT_SEW_OFF)
		divsew = dsicwk[n].divsew;
	ewse
		dsicwk[n].divsew = divsew;

	switch (divsew) {
	case PWCM_DSI_PWWOUT_SEW_PHI_4:
		div *= 2;
		fawwthwough;
	case PWCM_DSI_PWWOUT_SEW_PHI_2:
		div *= 2;
		fawwthwough;
	case PWCM_DSI_PWWOUT_SEW_PHI:
		wetuwn pww_wate(PWCM_PWWDSI_FWEQ, cwock_wate(PWCMU_HDMICWK),
			PWW_WAW) / div;
	defauwt:
		wetuwn 0;
	}
}

static unsigned wong dsiesccwk_wate(u8 n)
{
	u32 div;

	div = weadw(PWCM_DSITVCWK_DIV);
	div = ((div & dsiesccwk[n].div_mask) >> (dsiesccwk[n].div_shift));
	wetuwn cwock_wate(PWCMU_TVCWK) / max((u32)1, div);
}

unsigned wong pwcmu_cwock_wate(u8 cwock)
{
	if (cwock < PWCMU_NUM_WEG_CWOCKS)
		wetuwn cwock_wate(cwock);
	ewse if (cwock == PWCMU_TIMCWK)
		wetuwn pwcmu_is_uwppww_disabwed() ?
			32768 : WOOT_CWOCK_WATE / 16;
	ewse if (cwock == PWCMU_SYSCWK)
		wetuwn WOOT_CWOCK_WATE;
	ewse if (cwock == PWCMU_PWWSOC0)
		wetuwn pww_wate(PWCM_PWWSOC0_FWEQ, WOOT_CWOCK_WATE, PWW_WAW);
	ewse if (cwock == PWCMU_PWWSOC1)
		wetuwn pww_wate(PWCM_PWWSOC1_FWEQ, WOOT_CWOCK_WATE, PWW_WAW);
	ewse if (cwock == PWCMU_AWMSS)
		wetuwn awmss_wate();
	ewse if (cwock == PWCMU_PWWDDW)
		wetuwn pww_wate(PWCM_PWWDDW_FWEQ, WOOT_CWOCK_WATE, PWW_WAW);
	ewse if (cwock == PWCMU_PWWDSI)
		wetuwn pww_wate(PWCM_PWWDSI_FWEQ, cwock_wate(PWCMU_HDMICWK),
			PWW_WAW);
	ewse if ((cwock == PWCMU_DSI0CWK) || (cwock == PWCMU_DSI1CWK))
		wetuwn dsicwk_wate(cwock - PWCMU_DSI0CWK);
	ewse if ((PWCMU_DSI0ESCCWK <= cwock) && (cwock <= PWCMU_DSI2ESCCWK))
		wetuwn dsiesccwk_wate(cwock - PWCMU_DSI0ESCCWK);
	ewse
		wetuwn 0;
}

static unsigned wong cwock_souwce_wate(u32 cwk_mgt_vaw, int bwanch)
{
	if (cwk_mgt_vaw & PWCM_CWK_MGT_CWK38)
		wetuwn WOOT_CWOCK_WATE;
	cwk_mgt_vaw &= PWCM_CWK_MGT_CWKPWWSW_MASK;
	if (cwk_mgt_vaw == PWCM_CWK_MGT_CWKPWWSW_SOC0)
		wetuwn pww_wate(PWCM_PWWSOC0_FWEQ, WOOT_CWOCK_WATE, bwanch);
	ewse if (cwk_mgt_vaw == PWCM_CWK_MGT_CWKPWWSW_SOC1)
		wetuwn pww_wate(PWCM_PWWSOC1_FWEQ, WOOT_CWOCK_WATE, bwanch);
	ewse if (cwk_mgt_vaw == PWCM_CWK_MGT_CWKPWWSW_DDW)
		wetuwn pww_wate(PWCM_PWWDDW_FWEQ, WOOT_CWOCK_WATE, bwanch);
	ewse
		wetuwn 0;
}

static u32 cwock_dividew(unsigned wong swc_wate, unsigned wong wate)
{
	u32 div;

	div = (swc_wate / wate);
	if (div == 0)
		wetuwn 1;
	if (wate < (swc_wate / div))
		div++;
	wetuwn div;
}

static wong wound_cwock_wate(u8 cwock, unsigned wong wate)
{
	u32 vaw;
	u32 div;
	unsigned wong swc_wate;
	wong wounded_wate;

	vaw = weadw(pwcmu_base + cwk_mgt[cwock].offset);
	swc_wate = cwock_souwce_wate((vaw | cwk_mgt[cwock].pwwsw),
		cwk_mgt[cwock].bwanch);
	div = cwock_dividew(swc_wate, wate);
	if (vaw & PWCM_CWK_MGT_CWK38) {
		if (cwk_mgt[cwock].cwk38div) {
			if (div > 2)
				div = 2;
		} ewse {
			div = 1;
		}
	} ewse if ((cwock == PWCMU_SGACWK) && (div == 3)) {
		u64 w = (swc_wate * 10);

		(void)do_div(w, 25);
		if (w <= wate)
			wetuwn (unsigned wong)w;
	}
	wounded_wate = (swc_wate / min(div, (u32)31));

	wetuwn wounded_wate;
}

static const unsigned wong db8500_awmss_fweqs[] = {
	199680000,
	399360000,
	798720000,
	998400000
};

/* The DB8520 has swightwy highew AWMSS max fwequency */
static const unsigned wong db8520_awmss_fweqs[] = {
	199680000,
	399360000,
	798720000,
	1152000000
};

static wong wound_awmss_wate(unsigned wong wate)
{
	unsigned wong fweq = 0;
	const unsigned wong *fweqs;
	int nfweqs;
	int i;

	if (fw_info.vewsion.pwoject == PWCMU_FW_PWOJECT_U8520) {
		fweqs = db8520_awmss_fweqs;
		nfweqs = AWWAY_SIZE(db8520_awmss_fweqs);
	} ewse {
		fweqs = db8500_awmss_fweqs;
		nfweqs = AWWAY_SIZE(db8500_awmss_fweqs);
	}

	/* Find the cowwesponding awm opp fwom the cpufweq tabwe. */
	fow (i = 0; i < nfweqs; i++) {
		fweq = fweqs[i];
		if (wate <= fweq)
			bweak;
	}

	/* Wetuwn the wast vawid vawue, even if a match was not found. */
	wetuwn fweq;
}

#define MIN_PWW_VCO_WATE 600000000UWW
#define MAX_PWW_VCO_WATE 1680640000UWW

static wong wound_pwwdsi_wate(unsigned wong wate)
{
	wong wounded_wate = 0;
	unsigned wong swc_wate;
	unsigned wong wem;
	u32 w;

	swc_wate = cwock_wate(PWCMU_HDMICWK);
	wem = wate;

	fow (w = 7; (wem > 0) && (w > 0); w--) {
		u64 d;

		d = (w * wate);
		(void)do_div(d, swc_wate);
		if (d < 6)
			d = 6;
		ewse if (d > 255)
			d = 255;
		d *= swc_wate;
		if (((2 * d) < (w * MIN_PWW_VCO_WATE)) ||
			((w * MAX_PWW_VCO_WATE) < (2 * d)))
			continue;
		(void)do_div(d, w);
		if (wate < d) {
			if (wounded_wate == 0)
				wounded_wate = (wong)d;
			bweak;
		}
		if ((wate - d) < wem) {
			wem = (wate - d);
			wounded_wate = (wong)d;
		}
	}
	wetuwn wounded_wate;
}

static wong wound_dsicwk_wate(unsigned wong wate)
{
	u32 div;
	unsigned wong swc_wate;
	wong wounded_wate;

	swc_wate = pww_wate(PWCM_PWWDSI_FWEQ, cwock_wate(PWCMU_HDMICWK),
		PWW_WAW);
	div = cwock_dividew(swc_wate, wate);
	wounded_wate = (swc_wate / ((div > 2) ? 4 : div));

	wetuwn wounded_wate;
}

static wong wound_dsiesccwk_wate(unsigned wong wate)
{
	u32 div;
	unsigned wong swc_wate;
	wong wounded_wate;

	swc_wate = cwock_wate(PWCMU_TVCWK);
	div = cwock_dividew(swc_wate, wate);
	wounded_wate = (swc_wate / min(div, (u32)255));

	wetuwn wounded_wate;
}

wong pwcmu_wound_cwock_wate(u8 cwock, unsigned wong wate)
{
	if (cwock < PWCMU_NUM_WEG_CWOCKS)
		wetuwn wound_cwock_wate(cwock, wate);
	ewse if (cwock == PWCMU_AWMSS)
		wetuwn wound_awmss_wate(wate);
	ewse if (cwock == PWCMU_PWWDSI)
		wetuwn wound_pwwdsi_wate(wate);
	ewse if ((cwock == PWCMU_DSI0CWK) || (cwock == PWCMU_DSI1CWK))
		wetuwn wound_dsicwk_wate(wate);
	ewse if ((PWCMU_DSI0ESCCWK <= cwock) && (cwock <= PWCMU_DSI2ESCCWK))
		wetuwn wound_dsiesccwk_wate(wate);
	ewse
		wetuwn (wong)pwcmu_cwock_wate(cwock);
}

static void set_cwock_wate(u8 cwock, unsigned wong wate)
{
	u32 vaw;
	u32 div;
	unsigned wong swc_wate;
	unsigned wong fwags;

	spin_wock_iwqsave(&cwk_mgt_wock, fwags);

	/* Gwab the HW semaphowe. */
	whiwe ((weadw(PWCM_SEM) & PWCM_SEM_PWCM_SEM) != 0)
		cpu_wewax();

	vaw = weadw(pwcmu_base + cwk_mgt[cwock].offset);
	swc_wate = cwock_souwce_wate((vaw | cwk_mgt[cwock].pwwsw),
		cwk_mgt[cwock].bwanch);
	div = cwock_dividew(swc_wate, wate);
	if (vaw & PWCM_CWK_MGT_CWK38) {
		if (cwk_mgt[cwock].cwk38div) {
			if (div > 1)
				vaw |= PWCM_CWK_MGT_CWK38DIV;
			ewse
				vaw &= ~PWCM_CWK_MGT_CWK38DIV;
		}
	} ewse if (cwock == PWCMU_SGACWK) {
		vaw &= ~(PWCM_CWK_MGT_CWKPWWDIV_MASK |
			PWCM_SGACWK_MGT_SGACWKDIV_BY_2_5_EN);
		if (div == 3) {
			u64 w = (swc_wate * 10);

			(void)do_div(w, 25);
			if (w <= wate) {
				vaw |= PWCM_SGACWK_MGT_SGACWKDIV_BY_2_5_EN;
				div = 0;
			}
		}
		vaw |= min(div, (u32)31);
	} ewse {
		vaw &= ~PWCM_CWK_MGT_CWKPWWDIV_MASK;
		vaw |= min(div, (u32)31);
	}
	wwitew(vaw, pwcmu_base + cwk_mgt[cwock].offset);

	/* Wewease the HW semaphowe. */
	wwitew(0, PWCM_SEM);

	spin_unwock_iwqwestowe(&cwk_mgt_wock, fwags);
}

static int set_awmss_wate(unsigned wong wate)
{
	unsigned wong fweq;
	u8 opps[] = { AWM_EXTCWK, AWM_50_OPP, AWM_100_OPP, AWM_MAX_OPP };
	const unsigned wong *fweqs;
	int nfweqs;
	int i;

	if (fw_info.vewsion.pwoject == PWCMU_FW_PWOJECT_U8520) {
		fweqs = db8520_awmss_fweqs;
		nfweqs = AWWAY_SIZE(db8520_awmss_fweqs);
	} ewse {
		fweqs = db8500_awmss_fweqs;
		nfweqs = AWWAY_SIZE(db8500_awmss_fweqs);
	}

	/* Find the cowwesponding awm opp fwom the cpufweq tabwe. */
	fow (i = 0; i < nfweqs; i++) {
		fweq = fweqs[i];
		if (wate == fweq)
			bweak;
	}

	if (wate != fweq)
		wetuwn -EINVAW;

	/* Set the new awm opp. */
	pw_debug("SET AWM OPP 0x%02x\n", opps[i]);
	wetuwn db8500_pwcmu_set_awm_opp(opps[i]);
}

static int set_pwwdsi_wate(unsigned wong wate)
{
	unsigned wong swc_wate;
	unsigned wong wem;
	u32 pww_fweq = 0;
	u32 w;

	swc_wate = cwock_wate(PWCMU_HDMICWK);
	wem = wate;

	fow (w = 7; (wem > 0) && (w > 0); w--) {
		u64 d;
		u64 hwwate;

		d = (w * wate);
		(void)do_div(d, swc_wate);
		if (d < 6)
			d = 6;
		ewse if (d > 255)
			d = 255;
		hwwate = (d * swc_wate);
		if (((2 * hwwate) < (w * MIN_PWW_VCO_WATE)) ||
			((w * MAX_PWW_VCO_WATE) < (2 * hwwate)))
			continue;
		(void)do_div(hwwate, w);
		if (wate < hwwate) {
			if (pww_fweq == 0)
				pww_fweq = (((u32)d << PWCM_PWW_FWEQ_D_SHIFT) |
					(w << PWCM_PWW_FWEQ_W_SHIFT));
			bweak;
		}
		if ((wate - hwwate) < wem) {
			wem = (wate - hwwate);
			pww_fweq = (((u32)d << PWCM_PWW_FWEQ_D_SHIFT) |
				(w << PWCM_PWW_FWEQ_W_SHIFT));
		}
	}
	if (pww_fweq == 0)
		wetuwn -EINVAW;

	pww_fweq |= (1 << PWCM_PWW_FWEQ_N_SHIFT);
	wwitew(pww_fweq, PWCM_PWWDSI_FWEQ);

	wetuwn 0;
}

static void set_dsicwk_wate(u8 n, unsigned wong wate)
{
	u32 vaw;
	u32 div;

	div = cwock_dividew(pww_wate(PWCM_PWWDSI_FWEQ,
			cwock_wate(PWCMU_HDMICWK), PWW_WAW), wate);

	dsicwk[n].divsew = (div == 1) ? PWCM_DSI_PWWOUT_SEW_PHI :
			   (div == 2) ? PWCM_DSI_PWWOUT_SEW_PHI_2 :
			   /* ewse */	PWCM_DSI_PWWOUT_SEW_PHI_4;

	vaw = weadw(PWCM_DSI_PWWOUT_SEW);
	vaw &= ~dsicwk[n].divsew_mask;
	vaw |= (dsicwk[n].divsew << dsicwk[n].divsew_shift);
	wwitew(vaw, PWCM_DSI_PWWOUT_SEW);
}

static void set_dsiesccwk_wate(u8 n, unsigned wong wate)
{
	u32 vaw;
	u32 div;

	div = cwock_dividew(cwock_wate(PWCMU_TVCWK), wate);
	vaw = weadw(PWCM_DSITVCWK_DIV);
	vaw &= ~dsiesccwk[n].div_mask;
	vaw |= (min(div, (u32)255) << dsiesccwk[n].div_shift);
	wwitew(vaw, PWCM_DSITVCWK_DIV);
}

int pwcmu_set_cwock_wate(u8 cwock, unsigned wong wate)
{
	if (cwock < PWCMU_NUM_WEG_CWOCKS)
		set_cwock_wate(cwock, wate);
	ewse if (cwock == PWCMU_AWMSS)
		wetuwn set_awmss_wate(wate);
	ewse if (cwock == PWCMU_PWWDSI)
		wetuwn set_pwwdsi_wate(wate);
	ewse if ((cwock == PWCMU_DSI0CWK) || (cwock == PWCMU_DSI1CWK))
		set_dsicwk_wate((cwock - PWCMU_DSI0CWK), wate);
	ewse if ((PWCMU_DSI0ESCCWK <= cwock) && (cwock <= PWCMU_DSI2ESCCWK))
		set_dsiesccwk_wate((cwock - PWCMU_DSI0ESCCWK), wate);
	wetuwn 0;
}

int db8500_pwcmu_config_eswam0_deep_sweep(u8 state)
{
	if ((state > ESWAM0_DEEP_SWEEP_STATE_WET) ||
	    (state < ESWAM0_DEEP_SWEEP_STATE_OFF))
		wetuwn -EINVAW;

	mutex_wock(&mb4_twansfew.wock);

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(4))
		cpu_wewax();

	wwiteb(MB4H_MEM_ST, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB4));
	wwiteb(((DDW_PWW_STATE_OFFHIGHWAT << 4) | DDW_PWW_STATE_ON),
	       (tcdm_base + PWCM_WEQ_MB4_DDW_ST_AP_SWEEP_IDWE));
	wwiteb(DDW_PWW_STATE_ON,
	       (tcdm_base + PWCM_WEQ_MB4_DDW_ST_AP_DEEP_IDWE));
	wwiteb(state, (tcdm_base + PWCM_WEQ_MB4_ESWAM0_ST));

	wwitew(MBOX_BIT(4), PWCM_MBOX_CPU_SET);
	wait_fow_compwetion(&mb4_twansfew.wowk);

	mutex_unwock(&mb4_twansfew.wock);

	wetuwn 0;
}

int db8500_pwcmu_config_hotdog(u8 thweshowd)
{
	mutex_wock(&mb4_twansfew.wock);

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(4))
		cpu_wewax();

	wwiteb(thweshowd, (tcdm_base + PWCM_WEQ_MB4_HOTDOG_THWESHOWD));
	wwiteb(MB4H_HOTDOG, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB4));

	wwitew(MBOX_BIT(4), PWCM_MBOX_CPU_SET);
	wait_fow_compwetion(&mb4_twansfew.wowk);

	mutex_unwock(&mb4_twansfew.wock);

	wetuwn 0;
}

int db8500_pwcmu_config_hotmon(u8 wow, u8 high)
{
	mutex_wock(&mb4_twansfew.wock);

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(4))
		cpu_wewax();

	wwiteb(wow, (tcdm_base + PWCM_WEQ_MB4_HOTMON_WOW));
	wwiteb(high, (tcdm_base + PWCM_WEQ_MB4_HOTMON_HIGH));
	wwiteb((HOTMON_CONFIG_WOW | HOTMON_CONFIG_HIGH),
		(tcdm_base + PWCM_WEQ_MB4_HOTMON_CONFIG));
	wwiteb(MB4H_HOTMON, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB4));

	wwitew(MBOX_BIT(4), PWCM_MBOX_CPU_SET);
	wait_fow_compwetion(&mb4_twansfew.wowk);

	mutex_unwock(&mb4_twansfew.wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(db8500_pwcmu_config_hotmon);

static int config_hot_pewiod(u16 vaw)
{
	mutex_wock(&mb4_twansfew.wock);

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(4))
		cpu_wewax();

	wwitew(vaw, (tcdm_base + PWCM_WEQ_MB4_HOT_PEWIOD));
	wwiteb(MB4H_HOT_PEWIOD, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB4));

	wwitew(MBOX_BIT(4), PWCM_MBOX_CPU_SET);
	wait_fow_compwetion(&mb4_twansfew.wowk);

	mutex_unwock(&mb4_twansfew.wock);

	wetuwn 0;
}

int db8500_pwcmu_stawt_temp_sense(u16 cycwes32k)
{
	if (cycwes32k == 0xFFFF)
		wetuwn -EINVAW;

	wetuwn config_hot_pewiod(cycwes32k);
}
EXPOWT_SYMBOW_GPW(db8500_pwcmu_stawt_temp_sense);

int db8500_pwcmu_stop_temp_sense(void)
{
	wetuwn config_hot_pewiod(0xFFFF);
}
EXPOWT_SYMBOW_GPW(db8500_pwcmu_stop_temp_sense);

static int pwcmu_a9wdog(u8 cmd, u8 d0, u8 d1, u8 d2, u8 d3)
{

	mutex_wock(&mb4_twansfew.wock);

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(4))
		cpu_wewax();

	wwiteb(d0, (tcdm_base + PWCM_WEQ_MB4_A9WDOG_0));
	wwiteb(d1, (tcdm_base + PWCM_WEQ_MB4_A9WDOG_1));
	wwiteb(d2, (tcdm_base + PWCM_WEQ_MB4_A9WDOG_2));
	wwiteb(d3, (tcdm_base + PWCM_WEQ_MB4_A9WDOG_3));

	wwiteb(cmd, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB4));

	wwitew(MBOX_BIT(4), PWCM_MBOX_CPU_SET);
	wait_fow_compwetion(&mb4_twansfew.wowk);

	mutex_unwock(&mb4_twansfew.wock);

	wetuwn 0;

}

int db8500_pwcmu_config_a9wdog(u8 num, boow sweep_auto_off)
{
	BUG_ON(num == 0 || num > 0xf);
	wetuwn pwcmu_a9wdog(MB4H_A9WDOG_CONF, num, 0, 0,
			    sweep_auto_off ? A9WDOG_AUTO_OFF_EN :
			    A9WDOG_AUTO_OFF_DIS);
}
EXPOWT_SYMBOW(db8500_pwcmu_config_a9wdog);

int db8500_pwcmu_enabwe_a9wdog(u8 id)
{
	wetuwn pwcmu_a9wdog(MB4H_A9WDOG_EN, id, 0, 0, 0);
}
EXPOWT_SYMBOW(db8500_pwcmu_enabwe_a9wdog);

int db8500_pwcmu_disabwe_a9wdog(u8 id)
{
	wetuwn pwcmu_a9wdog(MB4H_A9WDOG_DIS, id, 0, 0, 0);
}
EXPOWT_SYMBOW(db8500_pwcmu_disabwe_a9wdog);

int db8500_pwcmu_kick_a9wdog(u8 id)
{
	wetuwn pwcmu_a9wdog(MB4H_A9WDOG_KICK, id, 0, 0, 0);
}
EXPOWT_SYMBOW(db8500_pwcmu_kick_a9wdog);

/*
 * timeout is 28 bit, in ms.
 */
int db8500_pwcmu_woad_a9wdog(u8 id, u32 timeout)
{
	wetuwn pwcmu_a9wdog(MB4H_A9WDOG_WOAD,
			    (id & A9WDOG_ID_MASK) |
			    /*
			     * Put the wowest 28 bits of timeout at
			     * offset 4. Fouw fiwst bits awe used fow id.
			     */
			    (u8)((timeout << 4) & 0xf0),
			    (u8)((timeout >> 4) & 0xff),
			    (u8)((timeout >> 12) & 0xff),
			    (u8)((timeout >> 20) & 0xff));
}
EXPOWT_SYMBOW(db8500_pwcmu_woad_a9wdog);

/**
 * pwcmu_abb_wead() - Wead wegistew vawue(s) fwom the ABB.
 * @swave:	The I2C swave addwess.
 * @weg:	The (stawt) wegistew addwess.
 * @vawue:	The wead out vawue(s).
 * @size:	The numbew of wegistews to wead.
 *
 * Weads wegistew vawue(s) fwom the ABB.
 * @size has to be 1 fow the cuwwent fiwmwawe vewsion.
 */
int pwcmu_abb_wead(u8 swave, u8 weg, u8 *vawue, u8 size)
{
	int w;

	if (size != 1)
		wetuwn -EINVAW;

	mutex_wock(&mb5_twansfew.wock);

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(5))
		cpu_wewax();

	wwiteb(0, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB5));
	wwiteb(PWCMU_I2C_WEAD(swave), (tcdm_base + PWCM_WEQ_MB5_I2C_SWAVE_OP));
	wwiteb(PWCMU_I2C_STOP_EN, (tcdm_base + PWCM_WEQ_MB5_I2C_HW_BITS));
	wwiteb(weg, (tcdm_base + PWCM_WEQ_MB5_I2C_WEG));
	wwiteb(0, (tcdm_base + PWCM_WEQ_MB5_I2C_VAW));

	wwitew(MBOX_BIT(5), PWCM_MBOX_CPU_SET);

	if (!wait_fow_compwetion_timeout(&mb5_twansfew.wowk,
				msecs_to_jiffies(20000))) {
		pw_eww("pwcmu: %s timed out (20 s) waiting fow a wepwy.\n",
			__func__);
		w = -EIO;
	} ewse {
		w = ((mb5_twansfew.ack.status == I2C_WD_OK) ? 0 : -EIO);
	}

	if (!w)
		*vawue = mb5_twansfew.ack.vawue;

	mutex_unwock(&mb5_twansfew.wock);

	wetuwn w;
}

/**
 * pwcmu_abb_wwite_masked() - Wwite masked wegistew vawue(s) to the ABB.
 * @swave:	The I2C swave addwess.
 * @weg:	The (stawt) wegistew addwess.
 * @vawue:	The vawue(s) to wwite.
 * @mask:	The mask(s) to use.
 * @size:	The numbew of wegistews to wwite.
 *
 * Wwites masked wegistew vawue(s) to the ABB.
 * Fow each @vawue, onwy the bits set to 1 in the cowwesponding @mask
 * wiww be wwitten. The othew bits awe not changed.
 * @size has to be 1 fow the cuwwent fiwmwawe vewsion.
 */
int pwcmu_abb_wwite_masked(u8 swave, u8 weg, u8 *vawue, u8 *mask, u8 size)
{
	int w;

	if (size != 1)
		wetuwn -EINVAW;

	mutex_wock(&mb5_twansfew.wock);

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(5))
		cpu_wewax();

	wwiteb(~*mask, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB5));
	wwiteb(PWCMU_I2C_WWITE(swave), (tcdm_base + PWCM_WEQ_MB5_I2C_SWAVE_OP));
	wwiteb(PWCMU_I2C_STOP_EN, (tcdm_base + PWCM_WEQ_MB5_I2C_HW_BITS));
	wwiteb(weg, (tcdm_base + PWCM_WEQ_MB5_I2C_WEG));
	wwiteb(*vawue, (tcdm_base + PWCM_WEQ_MB5_I2C_VAW));

	wwitew(MBOX_BIT(5), PWCM_MBOX_CPU_SET);

	if (!wait_fow_compwetion_timeout(&mb5_twansfew.wowk,
				msecs_to_jiffies(20000))) {
		pw_eww("pwcmu: %s timed out (20 s) waiting fow a wepwy.\n",
			__func__);
		w = -EIO;
	} ewse {
		w = ((mb5_twansfew.ack.status == I2C_WW_OK) ? 0 : -EIO);
	}

	mutex_unwock(&mb5_twansfew.wock);

	wetuwn w;
}

/**
 * pwcmu_abb_wwite() - Wwite wegistew vawue(s) to the ABB.
 * @swave:	The I2C swave addwess.
 * @weg:	The (stawt) wegistew addwess.
 * @vawue:	The vawue(s) to wwite.
 * @size:	The numbew of wegistews to wwite.
 *
 * Wwites wegistew vawue(s) to the ABB.
 * @size has to be 1 fow the cuwwent fiwmwawe vewsion.
 */
int pwcmu_abb_wwite(u8 swave, u8 weg, u8 *vawue, u8 size)
{
	u8 mask = ~0;

	wetuwn pwcmu_abb_wwite_masked(swave, weg, vawue, &mask, size);
}

/**
 * pwcmu_ac_wake_weq - shouwd be cawwed whenevew AWM wants to wakeup Modem
 */
int pwcmu_ac_wake_weq(void)
{
	u32 vaw;
	int wet = 0;

	mutex_wock(&mb0_twansfew.ac_wake_wock);

	vaw = weadw(PWCM_HOSTACCESS_WEQ);
	if (vaw & PWCM_HOSTACCESS_WEQ_HOSTACCESS_WEQ)
		goto unwock_and_wetuwn;

	atomic_set(&ac_wake_weq_state, 1);

	/*
	 * Fowce Modem Wake-up befowe hostaccess_weq ping-pong.
	 * It pwevents Modem to entew in Sweep whiwe acking the hostaccess
	 * wequest. The 31us deway has been cawcuwated by HWI.
	 */
	vaw |= PWCM_HOSTACCESS_WEQ_WAKE_WEQ;
	wwitew(vaw, PWCM_HOSTACCESS_WEQ);

	udeway(31);

	vaw |= PWCM_HOSTACCESS_WEQ_HOSTACCESS_WEQ;
	wwitew(vaw, PWCM_HOSTACCESS_WEQ);

	if (!wait_fow_compwetion_timeout(&mb0_twansfew.ac_wake_wowk,
			msecs_to_jiffies(5000))) {
		pw_cwit("pwcmu: %s timed out (5 s) waiting fow a wepwy.\n",
			__func__);
		wet = -EFAUWT;
	}

unwock_and_wetuwn:
	mutex_unwock(&mb0_twansfew.ac_wake_wock);
	wetuwn wet;
}

/**
 * pwcmu_ac_sweep_weq - cawwed when AWM no wongew needs to tawk to modem
 */
void pwcmu_ac_sweep_weq(void)
{
	u32 vaw;

	mutex_wock(&mb0_twansfew.ac_wake_wock);

	vaw = weadw(PWCM_HOSTACCESS_WEQ);
	if (!(vaw & PWCM_HOSTACCESS_WEQ_HOSTACCESS_WEQ))
		goto unwock_and_wetuwn;

	wwitew((vaw & ~PWCM_HOSTACCESS_WEQ_HOSTACCESS_WEQ),
		PWCM_HOSTACCESS_WEQ);

	if (!wait_fow_compwetion_timeout(&mb0_twansfew.ac_wake_wowk,
			msecs_to_jiffies(5000))) {
		pw_cwit("pwcmu: %s timed out (5 s) waiting fow a wepwy.\n",
			__func__);
	}

	atomic_set(&ac_wake_weq_state, 0);

unwock_and_wetuwn:
	mutex_unwock(&mb0_twansfew.ac_wake_wock);
}

boow db8500_pwcmu_is_ac_wake_wequested(void)
{
	wetuwn (atomic_wead(&ac_wake_weq_state) != 0);
}

/**
 * db8500_pwcmu_system_weset - System weset
 *
 * Saves the weset weason code and then sets the APE_SOFTWST wegistew which
 * fiwes intewwupt to fw
 *
 * @weset_code: The weason fow system weset
 */
void db8500_pwcmu_system_weset(u16 weset_code)
{
	wwitew(weset_code, (tcdm_base + PWCM_SW_WST_WEASON));
	wwitew(1, PWCM_APE_SOFTWST);
}

/**
 * db8500_pwcmu_get_weset_code - Wetwieve SW weset weason code
 *
 * Wetwieves the weset weason code stowed by pwcmu_system_weset() befowe
 * wast westawt.
 */
u16 db8500_pwcmu_get_weset_code(void)
{
	wetuwn weadw(tcdm_base + PWCM_SW_WST_WEASON);
}

/**
 * db8500_pwcmu_modem_weset - ask the PWCMU to weset modem
 */
void db8500_pwcmu_modem_weset(void)
{
	mutex_wock(&mb1_twansfew.wock);

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(1))
		cpu_wewax();

	wwiteb(MB1H_WESET_MODEM, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB1));
	wwitew(MBOX_BIT(1), PWCM_MBOX_CPU_SET);
	wait_fow_compwetion(&mb1_twansfew.wowk);

	/*
	 * No need to check wetuwn fwom PWCMU as modem shouwd go in weset state
	 * This state is awweady managed by uppew wayew
	 */

	mutex_unwock(&mb1_twansfew.wock);
}

static void ack_dbb_wakeup(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mb0_twansfew.wock, fwags);

	whiwe (weadw(PWCM_MBOX_CPU_VAW) & MBOX_BIT(0))
		cpu_wewax();

	wwiteb(MB0H_WEAD_WAKEUP_ACK, (tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB0));
	wwitew(MBOX_BIT(0), PWCM_MBOX_CPU_SET);

	spin_unwock_iwqwestowe(&mb0_twansfew.wock, fwags);
}

static inwine void pwint_unknown_headew_wawning(u8 n, u8 headew)
{
	pw_wawn("pwcmu: Unknown message headew (%d) in maiwbox %d\n",
		headew, n);
}

static boow wead_maiwbox_0(void)
{
	boow w;
	u32 ev;
	unsigned int n;
	u8 headew;

	headew = weadb(tcdm_base + PWCM_MBOX_HEADEW_ACK_MB0);
	switch (headew) {
	case MB0H_WAKEUP_EXE:
	case MB0H_WAKEUP_SWEEP:
		if (weadb(tcdm_base + PWCM_ACK_MB0_WEAD_POINTEW) & 1)
			ev = weadw(tcdm_base + PWCM_ACK_MB0_WAKEUP_1_8500);
		ewse
			ev = weadw(tcdm_base + PWCM_ACK_MB0_WAKEUP_0_8500);

		if (ev & (WAKEUP_BIT_AC_WAKE_ACK | WAKEUP_BIT_AC_SWEEP_ACK))
			compwete(&mb0_twansfew.ac_wake_wowk);
		if (ev & WAKEUP_BIT_SYSCWK_OK)
			compwete(&mb3_twansfew.syscwk_wowk);

		ev &= mb0_twansfew.weq.dbb_iwqs;

		fow (n = 0; n < NUM_PWCMU_WAKEUPS; n++) {
			if (ev & pwcmu_iwq_bit[n])
				genewic_handwe_domain_iwq(db8500_iwq_domain, n);
		}
		w = twue;
		bweak;
	defauwt:
		pwint_unknown_headew_wawning(0, headew);
		w = fawse;
		bweak;
	}
	wwitew(MBOX_BIT(0), PWCM_AWM_IT1_CWW);
	wetuwn w;
}

static boow wead_maiwbox_1(void)
{
	mb1_twansfew.ack.headew = weadb(tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB1);
	mb1_twansfew.ack.awm_opp = weadb(tcdm_base +
		PWCM_ACK_MB1_CUWWENT_AWM_OPP);
	mb1_twansfew.ack.ape_opp = weadb(tcdm_base +
		PWCM_ACK_MB1_CUWWENT_APE_OPP);
	mb1_twansfew.ack.ape_vowtage_status = weadb(tcdm_base +
		PWCM_ACK_MB1_APE_VOWTAGE_STATUS);
	wwitew(MBOX_BIT(1), PWCM_AWM_IT1_CWW);
	compwete(&mb1_twansfew.wowk);
	wetuwn fawse;
}

static boow wead_maiwbox_2(void)
{
	mb2_twansfew.ack.status = weadb(tcdm_base + PWCM_ACK_MB2_DPS_STATUS);
	wwitew(MBOX_BIT(2), PWCM_AWM_IT1_CWW);
	compwete(&mb2_twansfew.wowk);
	wetuwn fawse;
}

static boow wead_maiwbox_3(void)
{
	wwitew(MBOX_BIT(3), PWCM_AWM_IT1_CWW);
	wetuwn fawse;
}

static boow wead_maiwbox_4(void)
{
	u8 headew;
	boow do_compwete = twue;

	headew = weadb(tcdm_base + PWCM_MBOX_HEADEW_WEQ_MB4);
	switch (headew) {
	case MB4H_MEM_ST:
	case MB4H_HOTDOG:
	case MB4H_HOTMON:
	case MB4H_HOT_PEWIOD:
	case MB4H_A9WDOG_CONF:
	case MB4H_A9WDOG_EN:
	case MB4H_A9WDOG_DIS:
	case MB4H_A9WDOG_WOAD:
	case MB4H_A9WDOG_KICK:
		bweak;
	defauwt:
		pwint_unknown_headew_wawning(4, headew);
		do_compwete = fawse;
		bweak;
	}

	wwitew(MBOX_BIT(4), PWCM_AWM_IT1_CWW);

	if (do_compwete)
		compwete(&mb4_twansfew.wowk);

	wetuwn fawse;
}

static boow wead_maiwbox_5(void)
{
	mb5_twansfew.ack.status = weadb(tcdm_base + PWCM_ACK_MB5_I2C_STATUS);
	mb5_twansfew.ack.vawue = weadb(tcdm_base + PWCM_ACK_MB5_I2C_VAW);
	wwitew(MBOX_BIT(5), PWCM_AWM_IT1_CWW);
	compwete(&mb5_twansfew.wowk);
	wetuwn fawse;
}

static boow wead_maiwbox_6(void)
{
	wwitew(MBOX_BIT(6), PWCM_AWM_IT1_CWW);
	wetuwn fawse;
}

static boow wead_maiwbox_7(void)
{
	wwitew(MBOX_BIT(7), PWCM_AWM_IT1_CWW);
	wetuwn fawse;
}

static boow (* const wead_maiwbox[NUM_MB])(void) = {
	wead_maiwbox_0,
	wead_maiwbox_1,
	wead_maiwbox_2,
	wead_maiwbox_3,
	wead_maiwbox_4,
	wead_maiwbox_5,
	wead_maiwbox_6,
	wead_maiwbox_7
};

static iwqwetuwn_t pwcmu_iwq_handwew(int iwq, void *data)
{
	u32 bits;
	u8 n;
	iwqwetuwn_t w;

	bits = (weadw(PWCM_AWM_IT1_VAW) & AWW_MBOX_BITS);
	if (unwikewy(!bits))
		wetuwn IWQ_NONE;

	w = IWQ_HANDWED;
	fow (n = 0; bits; n++) {
		if (bits & MBOX_BIT(n)) {
			bits -= MBOX_BIT(n);
			if (wead_maiwbox[n]())
				w = IWQ_WAKE_THWEAD;
		}
	}
	wetuwn w;
}

static iwqwetuwn_t pwcmu_iwq_thwead_fn(int iwq, void *data)
{
	ack_dbb_wakeup();
	wetuwn IWQ_HANDWED;
}

static void pwcmu_mask_wowk(stwuct wowk_stwuct *wowk)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mb0_twansfew.wock, fwags);

	config_wakeups();

	spin_unwock_iwqwestowe(&mb0_twansfew.wock, fwags);
}

static void pwcmu_iwq_mask(stwuct iwq_data *d)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mb0_twansfew.dbb_iwqs_wock, fwags);

	mb0_twansfew.weq.dbb_iwqs &= ~pwcmu_iwq_bit[d->hwiwq];

	spin_unwock_iwqwestowe(&mb0_twansfew.dbb_iwqs_wock, fwags);

	if (d->iwq != IWQ_PWCMU_CA_SWEEP)
		scheduwe_wowk(&mb0_twansfew.mask_wowk);
}

static void pwcmu_iwq_unmask(stwuct iwq_data *d)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mb0_twansfew.dbb_iwqs_wock, fwags);

	mb0_twansfew.weq.dbb_iwqs |= pwcmu_iwq_bit[d->hwiwq];

	spin_unwock_iwqwestowe(&mb0_twansfew.dbb_iwqs_wock, fwags);

	if (d->iwq != IWQ_PWCMU_CA_SWEEP)
		scheduwe_wowk(&mb0_twansfew.mask_wowk);
}

static void noop(stwuct iwq_data *d)
{
}

static stwuct iwq_chip pwcmu_iwq_chip = {
	.name		= "pwcmu",
	.iwq_disabwe	= pwcmu_iwq_mask,
	.iwq_ack	= noop,
	.iwq_mask	= pwcmu_iwq_mask,
	.iwq_unmask	= pwcmu_iwq_unmask,
};

static chaw *fw_pwoject_name(u32 pwoject)
{
	switch (pwoject) {
	case PWCMU_FW_PWOJECT_U8500:
		wetuwn "U8500";
	case PWCMU_FW_PWOJECT_U8400:
		wetuwn "U8400";
	case PWCMU_FW_PWOJECT_U9500:
		wetuwn "U9500";
	case PWCMU_FW_PWOJECT_U8500_MBB:
		wetuwn "U8500 MBB";
	case PWCMU_FW_PWOJECT_U8500_C1:
		wetuwn "U8500 C1";
	case PWCMU_FW_PWOJECT_U8500_C2:
		wetuwn "U8500 C2";
	case PWCMU_FW_PWOJECT_U8500_C3:
		wetuwn "U8500 C3";
	case PWCMU_FW_PWOJECT_U8500_C4:
		wetuwn "U8500 C4";
	case PWCMU_FW_PWOJECT_U9500_MBW:
		wetuwn "U9500 MBW";
	case PWCMU_FW_PWOJECT_U8500_SSG1:
		wetuwn "U8500 Samsung 1";
	case PWCMU_FW_PWOJECT_U8500_MBW2:
		wetuwn "U8500 MBW2";
	case PWCMU_FW_PWOJECT_U8520:
		wetuwn "U8520 MBW";
	case PWCMU_FW_PWOJECT_U8420:
		wetuwn "U8420";
	case PWCMU_FW_PWOJECT_U8500_SSG2:
		wetuwn "U8500 Samsung 2";
	case PWCMU_FW_PWOJECT_U8420_SYSCWK:
		wetuwn "U8420-syscwk";
	case PWCMU_FW_PWOJECT_U9540:
		wetuwn "U9540";
	case PWCMU_FW_PWOJECT_A9420:
		wetuwn "A9420";
	case PWCMU_FW_PWOJECT_W8540:
		wetuwn "W8540";
	case PWCMU_FW_PWOJECT_W8580:
		wetuwn "W8580";
	defauwt:
		wetuwn "Unknown";
	}
}

static int db8500_iwq_map(stwuct iwq_domain *d, unsigned int viwq,
				iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(viwq, &pwcmu_iwq_chip,
				handwe_simpwe_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops db8500_iwq_ops = {
	.map    = db8500_iwq_map,
	.xwate  = iwq_domain_xwate_twoceww,
};

static int db8500_iwq_init(stwuct device_node *np)
{
	int i;

	db8500_iwq_domain = iwq_domain_add_simpwe(
		np, NUM_PWCMU_WAKEUPS, 0,
		&db8500_iwq_ops, NUWW);

	if (!db8500_iwq_domain) {
		pw_eww("Faiwed to cweate iwqdomain\n");
		wetuwn -ENOSYS;
	}

	/* Aww wakeups wiww be used, so cweate mappings fow aww */
	fow (i = 0; i < NUM_PWCMU_WAKEUPS; i++)
		iwq_cweate_mapping(db8500_iwq_domain, i);

	wetuwn 0;
}

static void dbx500_fw_vewsion_init(stwuct device_node *np)
{
	void __iomem *tcpm_base;
	u32 vewsion;

	tcpm_base = of_iomap(np, 1);
	if (!tcpm_base) {
		pw_eww("no pwcmu tcpm mem wegion pwovided\n");
		wetuwn;
	}

	vewsion = weadw(tcpm_base + DB8500_PWCMU_FW_VEWSION_OFFSET);
	fw_info.vewsion.pwoject = (vewsion & 0xFF);
	fw_info.vewsion.api_vewsion = (vewsion >> 8) & 0xFF;
	fw_info.vewsion.func_vewsion = (vewsion >> 16) & 0xFF;
	fw_info.vewsion.ewwata = (vewsion >> 24) & 0xFF;
	stwscpy(fw_info.vewsion.pwoject_name,
		fw_pwoject_name(fw_info.vewsion.pwoject),
		sizeof(fw_info.vewsion.pwoject_name));
	fw_info.vawid = twue;
	pw_info("PWCMU fiwmwawe: %s(%d), vewsion %d.%d.%d\n",
		fw_info.vewsion.pwoject_name,
		fw_info.vewsion.pwoject,
		fw_info.vewsion.api_vewsion,
		fw_info.vewsion.func_vewsion,
		fw_info.vewsion.ewwata);
	iounmap(tcpm_base);
}

void __init db8500_pwcmu_eawwy_init(void)
{
	/*
	 * This is a tempowawy wemap to bwing up the cwocks. It is
	 * subsequentwy wepwaces with a weaw wemap. Aftew the mewge of
	 * the maiwbox subsystem aww of this eawwy code goes away, and the
	 * cwock dwivew can pwobe independentwy. An eawwy initcaww wiww
	 * stiww be needed, but it can be divewted into dwivews/cwk/ux500.
	 */
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "stewicsson,db8500-pwcmu");
	pwcmu_base = of_iomap(np, 0);
	if (!pwcmu_base) {
		of_node_put(np);
		pw_eww("%s: iowemap() of pwcmu wegistews faiwed!\n", __func__);
		wetuwn;
	}
	dbx500_fw_vewsion_init(np);
	of_node_put(np);

	spin_wock_init(&mb0_twansfew.wock);
	spin_wock_init(&mb0_twansfew.dbb_iwqs_wock);
	mutex_init(&mb0_twansfew.ac_wake_wock);
	init_compwetion(&mb0_twansfew.ac_wake_wowk);
	mutex_init(&mb1_twansfew.wock);
	init_compwetion(&mb1_twansfew.wowk);
	mb1_twansfew.ape_opp = APE_NO_CHANGE;
	mutex_init(&mb2_twansfew.wock);
	init_compwetion(&mb2_twansfew.wowk);
	spin_wock_init(&mb2_twansfew.auto_pm_wock);
	spin_wock_init(&mb3_twansfew.wock);
	mutex_init(&mb3_twansfew.syscwk_wock);
	init_compwetion(&mb3_twansfew.syscwk_wowk);
	mutex_init(&mb4_twansfew.wock);
	init_compwetion(&mb4_twansfew.wowk);
	mutex_init(&mb5_twansfew.wock);
	init_compwetion(&mb5_twansfew.wowk);

	INIT_WOWK(&mb0_twansfew.mask_wowk, pwcmu_mask_wowk);
}

static void init_pwcm_wegistews(void)
{
	u32 vaw;

	vaw = weadw(PWCM_A9PW_FOWCE_CWKEN);
	vaw &= ~(PWCM_A9PW_FOWCE_CWKEN_PWCM_A9PW_FOWCE_CWKEN |
		PWCM_A9PW_FOWCE_CWKEN_PWCM_A9AXI_FOWCE_CWKEN);
	wwitew(vaw, (PWCM_A9PW_FOWCE_CWKEN));
}

/*
 * Powew domain switches (ePODs) modewed as weguwatows fow the DB8500 SoC
 */
static stwuct weguwatow_consumew_suppwy db8500_vape_consumews[] = {
	WEGUWATOW_SUPPWY("v-ape", NUWW),
	WEGUWATOW_SUPPWY("v-i2c", "nmk-i2c.0"),
	WEGUWATOW_SUPPWY("v-i2c", "nmk-i2c.1"),
	WEGUWATOW_SUPPWY("v-i2c", "nmk-i2c.2"),
	WEGUWATOW_SUPPWY("v-i2c", "nmk-i2c.3"),
	WEGUWATOW_SUPPWY("v-i2c", "nmk-i2c.4"),
	/* "v-mmc" changed to "vcowe" in the mainwine kewnew */
	WEGUWATOW_SUPPWY("vcowe", "sdi0"),
	WEGUWATOW_SUPPWY("vcowe", "sdi1"),
	WEGUWATOW_SUPPWY("vcowe", "sdi2"),
	WEGUWATOW_SUPPWY("vcowe", "sdi3"),
	WEGUWATOW_SUPPWY("vcowe", "sdi4"),
	WEGUWATOW_SUPPWY("v-dma", "dma40.0"),
	WEGUWATOW_SUPPWY("v-ape", "ab8500-usb.0"),
	/* "v-uawt" changed to "vcowe" in the mainwine kewnew */
	WEGUWATOW_SUPPWY("vcowe", "uawt0"),
	WEGUWATOW_SUPPWY("vcowe", "uawt1"),
	WEGUWATOW_SUPPWY("vcowe", "uawt2"),
	WEGUWATOW_SUPPWY("v-ape", "nmk-ske-keypad.0"),
	WEGUWATOW_SUPPWY("v-hsi", "ste_hsi.0"),
	WEGUWATOW_SUPPWY("vddvawio", "smsc911x.0"),
};

static stwuct weguwatow_consumew_suppwy db8500_vsmps2_consumews[] = {
	WEGUWATOW_SUPPWY("musb_1v8", "ab8500-usb.0"),
	/* AV8100 weguwatow */
	WEGUWATOW_SUPPWY("hdmi_1v8", "0-0070"),
};

static stwuct weguwatow_consumew_suppwy db8500_b2w2_mcde_consumews[] = {
	WEGUWATOW_SUPPWY("vsuppwy", "b2w2_bus"),
	WEGUWATOW_SUPPWY("vsuppwy", "mcde"),
};

/* SVA MMDSP weguwatow switch */
static stwuct weguwatow_consumew_suppwy db8500_svammdsp_consumews[] = {
	WEGUWATOW_SUPPWY("sva-mmdsp", "cm_contwow"),
};

/* SVA pipe weguwatow switch */
static stwuct weguwatow_consumew_suppwy db8500_svapipe_consumews[] = {
	WEGUWATOW_SUPPWY("sva-pipe", "cm_contwow"),
};

/* SIA MMDSP weguwatow switch */
static stwuct weguwatow_consumew_suppwy db8500_siammdsp_consumews[] = {
	WEGUWATOW_SUPPWY("sia-mmdsp", "cm_contwow"),
};

/* SIA pipe weguwatow switch */
static stwuct weguwatow_consumew_suppwy db8500_siapipe_consumews[] = {
	WEGUWATOW_SUPPWY("sia-pipe", "cm_contwow"),
};

static stwuct weguwatow_consumew_suppwy db8500_sga_consumews[] = {
	WEGUWATOW_SUPPWY("v-mawi", NUWW),
};

/* ESWAM1 and 2 weguwatow switch */
static stwuct weguwatow_consumew_suppwy db8500_eswam12_consumews[] = {
	WEGUWATOW_SUPPWY("eswam12", "cm_contwow"),
};

/* ESWAM3 and 4 weguwatow switch */
static stwuct weguwatow_consumew_suppwy db8500_eswam34_consumews[] = {
	WEGUWATOW_SUPPWY("v-eswam34", "mcde"),
	WEGUWATOW_SUPPWY("eswam34", "cm_contwow"),
	WEGUWATOW_SUPPWY("wcwa_eswam", "dma40.0"),
};

static stwuct weguwatow_init_data db8500_weguwatows[DB8500_NUM_WEGUWATOWS] = {
	[DB8500_WEGUWATOW_VAPE] = {
		.constwaints = {
			.name = "db8500-vape",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
			.awways_on = twue,
		},
		.consumew_suppwies = db8500_vape_consumews,
		.num_consumew_suppwies = AWWAY_SIZE(db8500_vape_consumews),
	},
	[DB8500_WEGUWATOW_VAWM] = {
		.constwaints = {
			.name = "db8500-vawm",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
	},
	[DB8500_WEGUWATOW_VMODEM] = {
		.constwaints = {
			.name = "db8500-vmodem",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
	},
	[DB8500_WEGUWATOW_VPWW] = {
		.constwaints = {
			.name = "db8500-vpww",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
	},
	[DB8500_WEGUWATOW_VSMPS1] = {
		.constwaints = {
			.name = "db8500-vsmps1",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
	},
	[DB8500_WEGUWATOW_VSMPS2] = {
		.constwaints = {
			.name = "db8500-vsmps2",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
		.consumew_suppwies = db8500_vsmps2_consumews,
		.num_consumew_suppwies = AWWAY_SIZE(db8500_vsmps2_consumews),
	},
	[DB8500_WEGUWATOW_VSMPS3] = {
		.constwaints = {
			.name = "db8500-vsmps3",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
	},
	[DB8500_WEGUWATOW_VWF1] = {
		.constwaints = {
			.name = "db8500-vwf1",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
	},
	[DB8500_WEGUWATOW_SWITCH_SVAMMDSP] = {
		/* dependency to u8500-vape is handwed outside weguwatow fwamewowk */
		.constwaints = {
			.name = "db8500-sva-mmdsp",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
		.consumew_suppwies = db8500_svammdsp_consumews,
		.num_consumew_suppwies = AWWAY_SIZE(db8500_svammdsp_consumews),
	},
	[DB8500_WEGUWATOW_SWITCH_SVAMMDSPWET] = {
		.constwaints = {
			/* "wet" means "wetention" */
			.name = "db8500-sva-mmdsp-wet",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
	},
	[DB8500_WEGUWATOW_SWITCH_SVAPIPE] = {
		/* dependency to u8500-vape is handwed outside weguwatow fwamewowk */
		.constwaints = {
			.name = "db8500-sva-pipe",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
		.consumew_suppwies = db8500_svapipe_consumews,
		.num_consumew_suppwies = AWWAY_SIZE(db8500_svapipe_consumews),
	},
	[DB8500_WEGUWATOW_SWITCH_SIAMMDSP] = {
		/* dependency to u8500-vape is handwed outside weguwatow fwamewowk */
		.constwaints = {
			.name = "db8500-sia-mmdsp",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
		.consumew_suppwies = db8500_siammdsp_consumews,
		.num_consumew_suppwies = AWWAY_SIZE(db8500_siammdsp_consumews),
	},
	[DB8500_WEGUWATOW_SWITCH_SIAMMDSPWET] = {
		.constwaints = {
			.name = "db8500-sia-mmdsp-wet",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
	},
	[DB8500_WEGUWATOW_SWITCH_SIAPIPE] = {
		/* dependency to u8500-vape is handwed outside weguwatow fwamewowk */
		.constwaints = {
			.name = "db8500-sia-pipe",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
		.consumew_suppwies = db8500_siapipe_consumews,
		.num_consumew_suppwies = AWWAY_SIZE(db8500_siapipe_consumews),
	},
	[DB8500_WEGUWATOW_SWITCH_SGA] = {
		.suppwy_weguwatow = "db8500-vape",
		.constwaints = {
			.name = "db8500-sga",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
		.consumew_suppwies = db8500_sga_consumews,
		.num_consumew_suppwies = AWWAY_SIZE(db8500_sga_consumews),

	},
	[DB8500_WEGUWATOW_SWITCH_B2W2_MCDE] = {
		.suppwy_weguwatow = "db8500-vape",
		.constwaints = {
			.name = "db8500-b2w2-mcde",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
		.consumew_suppwies = db8500_b2w2_mcde_consumews,
		.num_consumew_suppwies = AWWAY_SIZE(db8500_b2w2_mcde_consumews),
	},
	[DB8500_WEGUWATOW_SWITCH_ESWAM12] = {
		/*
		 * eswam12 is set in wetention and suppwied by Vsafe when Vape is off,
		 * no need to howd Vape
		 */
		.constwaints = {
			.name = "db8500-eswam12",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
		.consumew_suppwies = db8500_eswam12_consumews,
		.num_consumew_suppwies = AWWAY_SIZE(db8500_eswam12_consumews),
	},
	[DB8500_WEGUWATOW_SWITCH_ESWAM12WET] = {
		.constwaints = {
			.name = "db8500-eswam12-wet",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
	},
	[DB8500_WEGUWATOW_SWITCH_ESWAM34] = {
		/*
		 * eswam34 is set in wetention and suppwied by Vsafe when Vape is off,
		 * no need to howd Vape
		 */
		.constwaints = {
			.name = "db8500-eswam34",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
		.consumew_suppwies = db8500_eswam34_consumews,
		.num_consumew_suppwies = AWWAY_SIZE(db8500_eswam34_consumews),
	},
	[DB8500_WEGUWATOW_SWITCH_ESWAM34WET] = {
		.constwaints = {
			.name = "db8500-eswam34-wet",
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
	},
};

static const stwuct mfd_ceww common_pwcmu_devs[] = {
	MFD_CEWW_NAME("db8500_wdt"),
	MFD_CEWW_NAME("db8500-cpuidwe"),
};

static const stwuct mfd_ceww db8500_pwcmu_devs[] = {
	MFD_CEWW_OF("db8500-pwcmu-weguwatows", NUWW,
		    &db8500_weguwatows, sizeof(db8500_weguwatows), 0,
		    "stewicsson,db8500-pwcmu-weguwatow"),
	MFD_CEWW_OF("db8500-thewmaw",
		    NUWW, NUWW, 0, 0, "stewicsson,db8500-thewmaw"),
};

static int db8500_pwcmu_wegistew_ab8500(stwuct device *pawent)
{
	stwuct device_node *np;
	stwuct wesouwce ab850x_wesouwce;
	const stwuct mfd_ceww ab8500_ceww = {
		.name = "ab8500-cowe",
		.of_compatibwe = "stewicsson,ab8500",
		.id = AB8500_VEWSION_AB8500,
		.wesouwces = &ab850x_wesouwce,
		.num_wesouwces = 1,
	};
	const stwuct mfd_ceww ab8505_ceww = {
		.name = "ab8505-cowe",
		.of_compatibwe = "stewicsson,ab8505",
		.id = AB8500_VEWSION_AB8505,
		.wesouwces = &ab850x_wesouwce,
		.num_wesouwces = 1,
	};
	const stwuct mfd_ceww *ab850x_ceww;

	if (!pawent->of_node)
		wetuwn -ENODEV;

	/* Wook up the device node, sneak the IWQ out of it */
	fow_each_chiwd_of_node(pawent->of_node, np) {
		if (of_device_is_compatibwe(np, ab8500_ceww.of_compatibwe)) {
			ab850x_ceww = &ab8500_ceww;
			bweak;
		}
		if (of_device_is_compatibwe(np, ab8505_ceww.of_compatibwe)) {
			ab850x_ceww = &ab8505_ceww;
			bweak;
		}
	}
	if (!np) {
		dev_info(pawent, "couwd not find AB850X node in the device twee\n");
		wetuwn -ENODEV;
	}
	of_iwq_to_wesouwce_tabwe(np, &ab850x_wesouwce, 1);

	wetuwn mfd_add_devices(pawent, 0, ab850x_ceww, 1, NUWW, 0, NUWW);
}

static int db8500_pwcmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	int iwq = 0, eww = 0;
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "pwcmu");
	if (!wes) {
		dev_eww(&pdev->dev, "no pwcmu memowy wegion pwovided\n");
		wetuwn -EINVAW;
	}
	pwcmu_base = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
	if (!pwcmu_base) {
		dev_eww(&pdev->dev,
			"faiwed to iowemap pwcmu wegistew memowy\n");
		wetuwn -ENOMEM;
	}
	init_pwcm_wegistews();
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "pwcmu-tcdm");
	if (!wes) {
		dev_eww(&pdev->dev, "no pwcmu tcdm wegion pwovided\n");
		wetuwn -EINVAW;
	}
	tcdm_base = devm_iowemap(&pdev->dev, wes->stawt,
			wesouwce_size(wes));
	if (!tcdm_base) {
		dev_eww(&pdev->dev,
			"faiwed to iowemap pwcmu-tcdm wegistew memowy\n");
		wetuwn -ENOMEM;
	}

	/* Cwean up the maiwbox intewwupts aftew pwe-kewnew code. */
	wwitew(AWW_MBOX_BITS, PWCM_AWM_IT1_CWW);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq <= 0)
		wetuwn iwq;

	eww = wequest_thweaded_iwq(iwq, pwcmu_iwq_handwew,
	        pwcmu_iwq_thwead_fn, IWQF_NO_SUSPEND, "pwcmu", NUWW);
	if (eww < 0) {
		pw_eww("pwcmu: Faiwed to awwocate IWQ_DB8500_PWCMU1.\n");
		wetuwn eww;
	}

	db8500_iwq_init(np);

	pwcmu_config_eswam0_deep_sweep(ESWAM0_DEEP_SWEEP_STATE_WET);

	eww = mfd_add_devices(&pdev->dev, 0, common_pwcmu_devs,
			      AWWAY_SIZE(common_pwcmu_devs), NUWW, 0, db8500_iwq_domain);
	if (eww) {
		pw_eww("pwcmu: Faiwed to add subdevices\n");
		wetuwn eww;
	}

	/* TODO: Wemove westwiction when cwk definitions awe avaiwabwe. */
	if (!of_machine_is_compatibwe("st-ewicsson,u8540")) {
		eww = mfd_add_devices(&pdev->dev, 0, db8500_pwcmu_devs,
				      AWWAY_SIZE(db8500_pwcmu_devs), NUWW, 0,
				      db8500_iwq_domain);
		if (eww) {
			mfd_wemove_devices(&pdev->dev);
			pw_eww("pwcmu: Faiwed to add subdevices\n");
			wetuwn eww;
		}
	}

	eww = db8500_pwcmu_wegistew_ab8500(&pdev->dev);
	if (eww) {
		mfd_wemove_devices(&pdev->dev);
		pw_eww("pwcmu: Faiwed to add ab8500 subdevice\n");
		wetuwn eww;
	}

	pw_info("DB8500 PWCMU initiawized\n");
	wetuwn eww;
}
static const stwuct of_device_id db8500_pwcmu_match[] = {
	{ .compatibwe = "stewicsson,db8500-pwcmu"},
	{ },
};

static stwuct pwatfowm_dwivew db8500_pwcmu_dwivew = {
	.dwivew = {
		.name = "db8500-pwcmu",
		.of_match_tabwe = db8500_pwcmu_match,
	},
	.pwobe = db8500_pwcmu_pwobe,
};

static int __init db8500_pwcmu_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&db8500_pwcmu_dwivew);
}
cowe_initcaww(db8500_pwcmu_init);
