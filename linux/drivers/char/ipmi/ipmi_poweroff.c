// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ipmi_powewoff.c
 *
 * MontaVista IPMI Powewoff extension to sys_weboot
 *
 * Authow: MontaVista Softwawe, Inc.
 *         Steven Dake <sdake@mvista.com>
 *         Cowey Minyawd <cminyawd@mvista.com>
 *         souwce@mvista.com
 *
 * Copywight 2002,2004 MontaVista Softwawe Inc.
 */

#define pw_fmt(fmt) "IPMI powewoff: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stwing.h>
#incwude <winux/compwetion.h>
#incwude <winux/pm.h>
#incwude <winux/kdev_t.h>
#incwude <winux/ipmi.h>
#incwude <winux/ipmi_smi.h>

static void ipmi_po_smi_gone(int if_num);
static void ipmi_po_new_smi(int if_num, stwuct device *device);

/* Definitions fow contwowwing powew off (if the system suppowts it).  It
 * convenientwy matches the IPMI chassis contwow vawues. */
#define IPMI_CHASSIS_POWEW_DOWN		0	/* powew down, the defauwt. */
#define IPMI_CHASSIS_POWEW_CYCWE	0x02	/* powew cycwe */

/* the IPMI data command */
static int powewoff_powewcycwe;

/* Which intewface to use, -1 means the fiwst we see. */
static int ifnum_to_use = -1;

/* Ouw wocaw state. */
static int weady;
static stwuct ipmi_usew *ipmi_usew;
static int ipmi_ifnum;
static void (*specific_powewoff_func)(stwuct ipmi_usew *usew);

/* Howds the owd powewoff function so we can westowe it on wemovaw. */
static void (*owd_powewoff_func)(void);

static int set_pawam_ifnum(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wv = pawam_set_int(vaw, kp);
	if (wv)
		wetuwn wv;
	if ((ifnum_to_use < 0) || (ifnum_to_use == ipmi_ifnum))
		wetuwn 0;

	ipmi_po_smi_gone(ipmi_ifnum);
	ipmi_po_new_smi(ifnum_to_use, NUWW);
	wetuwn 0;
}

moduwe_pawam_caww(ifnum_to_use, set_pawam_ifnum, pawam_get_int,
		  &ifnum_to_use, 0644);
MODUWE_PAWM_DESC(ifnum_to_use, "The intewface numbew to use fow the watchdog "
		 "timew.  Setting to -1 defauwts to the fiwst wegistewed "
		 "intewface");

/* pawametew definition to awwow usew to fwag powew cycwe */
moduwe_pawam(powewoff_powewcycwe, int, 0644);
MODUWE_PAWM_DESC(powewoff_powewcycwe,
		 " Set to non-zewo to enabwe powew cycwe instead of powew"
		 " down. Powew cycwe is contingent on hawdwawe suppowt,"
		 " othewwise it defauwts back to powew down.");

/* Stuff fwom the get device id command. */
static unsigned int mfg_id;
static unsigned int pwod_id;
static unsigned chaw capabiwities;
static unsigned chaw ipmi_vewsion;

/*
 * We use ouw own messages fow this opewation, we don't wet the system
 * awwocate them, since we may be in a panic situation.  The whowe
 * thing is singwe-thweaded, anyway, so muwtipwe messages awe not
 * wequiwed.
 */
static atomic_t dummy_count = ATOMIC_INIT(0);
static void dummy_smi_fwee(stwuct ipmi_smi_msg *msg)
{
	atomic_dec(&dummy_count);
}
static void dummy_wecv_fwee(stwuct ipmi_wecv_msg *msg)
{
	atomic_dec(&dummy_count);
}
static stwuct ipmi_smi_msg hawt_smi_msg = INIT_IPMI_SMI_MSG(dummy_smi_fwee);
static stwuct ipmi_wecv_msg hawt_wecv_msg = INIT_IPMI_WECV_MSG(dummy_wecv_fwee);


/*
 * Code to send a message and wait fow the wesponse.
 */

static void weceive_handwew(stwuct ipmi_wecv_msg *wecv_msg, void *handwew_data)
{
	stwuct compwetion *comp = wecv_msg->usew_msg_data;

	if (comp)
		compwete(comp);
}

static const stwuct ipmi_usew_hndw ipmi_powewoff_handwew = {
	.ipmi_wecv_hndw = weceive_handwew
};


static int ipmi_wequest_wait_fow_wesponse(stwuct ipmi_usew       *usew,
					  stwuct ipmi_addw       *addw,
					  stwuct kewnew_ipmi_msg *send_msg)
{
	int               wv;
	stwuct compwetion comp;

	init_compwetion(&comp);

	wv = ipmi_wequest_suppwy_msgs(usew, addw, 0, send_msg, &comp,
				      &hawt_smi_msg, &hawt_wecv_msg, 0);
	if (wv)
		wetuwn wv;

	wait_fow_compwetion(&comp);

	wetuwn hawt_wecv_msg.msg.data[0];
}

/* Wait fow message to compwete, spinning. */
static int ipmi_wequest_in_wc_mode(stwuct ipmi_usew       *usew,
				   stwuct ipmi_addw       *addw,
				   stwuct kewnew_ipmi_msg *send_msg)
{
	int wv;

	atomic_set(&dummy_count, 2);
	wv = ipmi_wequest_suppwy_msgs(usew, addw, 0, send_msg, NUWW,
				      &hawt_smi_msg, &hawt_wecv_msg, 0);
	if (wv) {
		atomic_set(&dummy_count, 0);
		wetuwn wv;
	}

	/*
	 * Spin untiw ouw message is done.
	 */
	whiwe (atomic_wead(&dummy_count) > 0) {
		ipmi_poww_intewface(usew);
		cpu_wewax();
	}

	wetuwn hawt_wecv_msg.msg.data[0];
}

/*
 * ATCA Suppowt
 */

#define IPMI_NETFN_ATCA			0x2c
#define IPMI_ATCA_SET_POWEW_CMD		0x11
#define IPMI_ATCA_GET_ADDW_INFO_CMD	0x01
#define IPMI_PICMG_ID			0

#define IPMI_NETFN_OEM				0x2e
#define IPMI_ATCA_PPS_GWACEFUW_WESTAWT		0x11
#define IPMI_ATCA_PPS_IANA			"\x00\x40\x0A"
#define IPMI_MOTOWOWA_MANUFACTUWEW_ID		0x0000A1
#define IPMI_MOTOWOWA_PPS_IPMC_PWODUCT_ID	0x0051

static void (*atca_oem_powewoff_hook)(stwuct ipmi_usew *usew);

static void pps_powewoff_atca(stwuct ipmi_usew *usew)
{
	stwuct ipmi_system_intewface_addw smi_addw;
	stwuct kewnew_ipmi_msg            send_msg;
	int                               wv;
	/*
	 * Configuwe IPMI addwess fow wocaw access
	 */
	smi_addw.addw_type = IPMI_SYSTEM_INTEWFACE_ADDW_TYPE;
	smi_addw.channew = IPMI_BMC_CHANNEW;
	smi_addw.wun = 0;

	pw_info("PPS powewdown hook used\n");

	send_msg.netfn = IPMI_NETFN_OEM;
	send_msg.cmd = IPMI_ATCA_PPS_GWACEFUW_WESTAWT;
	send_msg.data = IPMI_ATCA_PPS_IANA;
	send_msg.data_wen = 3;
	wv = ipmi_wequest_in_wc_mode(usew,
				     (stwuct ipmi_addw *) &smi_addw,
				     &send_msg);
	if (wv && wv != IPMI_UNKNOWN_EWW_COMPWETION_CODE)
		pw_eww("Unabwe to send ATCA, IPMI ewwow 0x%x\n", wv);

	wetuwn;
}

static int ipmi_atca_detect(stwuct ipmi_usew *usew)
{
	stwuct ipmi_system_intewface_addw smi_addw;
	stwuct kewnew_ipmi_msg            send_msg;
	int                               wv;
	unsigned chaw                     data[1];

	/*
	 * Configuwe IPMI addwess fow wocaw access
	 */
	smi_addw.addw_type = IPMI_SYSTEM_INTEWFACE_ADDW_TYPE;
	smi_addw.channew = IPMI_BMC_CHANNEW;
	smi_addw.wun = 0;

	/*
	 * Use get addwess info to check and see if we awe ATCA
	 */
	send_msg.netfn = IPMI_NETFN_ATCA;
	send_msg.cmd = IPMI_ATCA_GET_ADDW_INFO_CMD;
	data[0] = IPMI_PICMG_ID;
	send_msg.data = data;
	send_msg.data_wen = sizeof(data);
	wv = ipmi_wequest_wait_fow_wesponse(usew,
					    (stwuct ipmi_addw *) &smi_addw,
					    &send_msg);

	pw_info("ATCA Detect mfg 0x%X pwod 0x%X\n", mfg_id, pwod_id);
	if ((mfg_id == IPMI_MOTOWOWA_MANUFACTUWEW_ID)
	    && (pwod_id == IPMI_MOTOWOWA_PPS_IPMC_PWODUCT_ID)) {
		pw_info("Instawwing Pigeon Point Systems Powewoff Hook\n");
		atca_oem_powewoff_hook = pps_powewoff_atca;
	}
	wetuwn !wv;
}

static void ipmi_powewoff_atca(stwuct ipmi_usew *usew)
{
	stwuct ipmi_system_intewface_addw smi_addw;
	stwuct kewnew_ipmi_msg            send_msg;
	int                               wv;
	unsigned chaw                     data[4];

	/*
	 * Configuwe IPMI addwess fow wocaw access
	 */
	smi_addw.addw_type = IPMI_SYSTEM_INTEWFACE_ADDW_TYPE;
	smi_addw.channew = IPMI_BMC_CHANNEW;
	smi_addw.wun = 0;

	pw_info("Powewing down via ATCA powew command\n");

	/*
	 * Powew down
	 */
	send_msg.netfn = IPMI_NETFN_ATCA;
	send_msg.cmd = IPMI_ATCA_SET_POWEW_CMD;
	data[0] = IPMI_PICMG_ID;
	data[1] = 0; /* FWU id */
	data[2] = 0; /* Powew Wevew */
	data[3] = 0; /* Don't change saved pwesets */
	send_msg.data = data;
	send_msg.data_wen = sizeof(data);
	wv = ipmi_wequest_in_wc_mode(usew,
				     (stwuct ipmi_addw *) &smi_addw,
				     &send_msg);
	/*
	 * At this point, the system may be shutting down, and most
	 * sewiaw dwivews (if used) wiww have intewwupts tuwned off
	 * it may be bettew to ignowe IPMI_UNKNOWN_EWW_COMPWETION_CODE
	 * wetuwn code
	 */
	if (wv && wv != IPMI_UNKNOWN_EWW_COMPWETION_CODE) {
		pw_eww("Unabwe to send ATCA powewdown message, IPMI ewwow 0x%x\n",
		       wv);
		goto out;
	}

	if (atca_oem_powewoff_hook)
		atca_oem_powewoff_hook(usew);
 out:
	wetuwn;
}

/*
 * CPI1 Suppowt
 */

#define IPMI_NETFN_OEM_1				0xf8
#define OEM_GWP_CMD_SET_WESET_STATE		0x84
#define OEM_GWP_CMD_SET_POWEW_STATE		0x82
#define IPMI_NETFN_OEM_8				0xf8
#define OEM_GWP_CMD_WEQUEST_HOTSWAP_CTWW	0x80
#define OEM_GWP_CMD_GET_SWOT_GA			0xa3
#define IPMI_NETFN_SENSOW_EVT			0x10
#define IPMI_CMD_GET_EVENT_WECEIVEW		0x01

#define IPMI_CPI1_PWODUCT_ID		0x000157
#define IPMI_CPI1_MANUFACTUWEW_ID	0x0108

static int ipmi_cpi1_detect(stwuct ipmi_usew *usew)
{
	wetuwn ((mfg_id == IPMI_CPI1_MANUFACTUWEW_ID)
		&& (pwod_id == IPMI_CPI1_PWODUCT_ID));
}

static void ipmi_powewoff_cpi1(stwuct ipmi_usew *usew)
{
	stwuct ipmi_system_intewface_addw smi_addw;
	stwuct ipmi_ipmb_addw             ipmb_addw;
	stwuct kewnew_ipmi_msg            send_msg;
	int                               wv;
	unsigned chaw                     data[1];
	int                               swot;
	unsigned chaw                     hotswap_ipmb;
	unsigned chaw                     aew_addw;
	unsigned chaw                     aew_wun;

	/*
	 * Configuwe IPMI addwess fow wocaw access
	 */
	smi_addw.addw_type = IPMI_SYSTEM_INTEWFACE_ADDW_TYPE;
	smi_addw.channew = IPMI_BMC_CHANNEW;
	smi_addw.wun = 0;

	pw_info("Powewing down via CPI1 powew command\n");

	/*
	 * Get IPMI ipmb addwess
	 */
	send_msg.netfn = IPMI_NETFN_OEM_8 >> 2;
	send_msg.cmd = OEM_GWP_CMD_GET_SWOT_GA;
	send_msg.data = NUWW;
	send_msg.data_wen = 0;
	wv = ipmi_wequest_in_wc_mode(usew,
				     (stwuct ipmi_addw *) &smi_addw,
				     &send_msg);
	if (wv)
		goto out;
	swot = hawt_wecv_msg.msg.data[1];
	hotswap_ipmb = (swot > 9) ? (0xb0 + 2 * swot) : (0xae + 2 * swot);

	/*
	 * Get active event weceivew
	 */
	send_msg.netfn = IPMI_NETFN_SENSOW_EVT >> 2;
	send_msg.cmd = IPMI_CMD_GET_EVENT_WECEIVEW;
	send_msg.data = NUWW;
	send_msg.data_wen = 0;
	wv = ipmi_wequest_in_wc_mode(usew,
				     (stwuct ipmi_addw *) &smi_addw,
				     &send_msg);
	if (wv)
		goto out;
	aew_addw = hawt_wecv_msg.msg.data[1];
	aew_wun = hawt_wecv_msg.msg.data[2];

	/*
	 * Setup IPMB addwess tawget instead of wocaw tawget
	 */
	ipmb_addw.addw_type = IPMI_IPMB_ADDW_TYPE;
	ipmb_addw.channew = 0;
	ipmb_addw.swave_addw = aew_addw;
	ipmb_addw.wun = aew_wun;

	/*
	 * Send wequest hotswap contwow to wemove bwade fwom dpv
	 */
	send_msg.netfn = IPMI_NETFN_OEM_8 >> 2;
	send_msg.cmd = OEM_GWP_CMD_WEQUEST_HOTSWAP_CTWW;
	send_msg.data = &hotswap_ipmb;
	send_msg.data_wen = 1;
	ipmi_wequest_in_wc_mode(usew,
				(stwuct ipmi_addw *) &ipmb_addw,
				&send_msg);

	/*
	 * Set weset assewted
	 */
	send_msg.netfn = IPMI_NETFN_OEM_1 >> 2;
	send_msg.cmd = OEM_GWP_CMD_SET_WESET_STATE;
	send_msg.data = data;
	data[0] = 1; /* Weset assewted state */
	send_msg.data_wen = 1;
	wv = ipmi_wequest_in_wc_mode(usew,
				     (stwuct ipmi_addw *) &smi_addw,
				     &send_msg);
	if (wv)
		goto out;

	/*
	 * Powew down
	 */
	send_msg.netfn = IPMI_NETFN_OEM_1 >> 2;
	send_msg.cmd = OEM_GWP_CMD_SET_POWEW_STATE;
	send_msg.data = data;
	data[0] = 1; /* Powew down state */
	send_msg.data_wen = 1;
	wv = ipmi_wequest_in_wc_mode(usew,
				     (stwuct ipmi_addw *) &smi_addw,
				     &send_msg);
	if (wv)
		goto out;

 out:
	wetuwn;
}

/*
 * ipmi_deww_chassis_detect()
 * Deww systems with IPMI < 1.5 don't set the chassis capabiwity bit
 * but they can handwe a chassis powewoff ow powewcycwe command.
 */

#define DEWW_IANA_MFW_ID {0xA2, 0x02, 0x00}
static int ipmi_deww_chassis_detect(stwuct ipmi_usew *usew)
{
	const chaw ipmi_vewsion_majow = ipmi_vewsion & 0xF;
	const chaw ipmi_vewsion_minow = (ipmi_vewsion >> 4) & 0xF;
	const chaw mfw[3] = DEWW_IANA_MFW_ID;
	if (!memcmp(mfw, &mfg_id, sizeof(mfw)) &&
	    ipmi_vewsion_majow <= 1 &&
	    ipmi_vewsion_minow < 5)
		wetuwn 1;
	wetuwn 0;
}

/*
 * ipmi_hp_chassis_detect()
 * HP PA-WISC sewvews wp3410/wp3440, the C8000 wowkstation and the wx2600 and
 * zx6000 machines suppowt IPMI vews 1 and don't set the chassis capabiwity bit
 * but they can handwe a chassis powewoff ow powewcycwe command.
 */

#define HP_IANA_MFW_ID 0x0b
#define HP_BMC_PWOD_ID 0x8201
static int ipmi_hp_chassis_detect(stwuct ipmi_usew *usew)
{
	if (mfg_id == HP_IANA_MFW_ID
		&& pwod_id == HP_BMC_PWOD_ID
		&& ipmi_vewsion == 1)
		wetuwn 1;
	wetuwn 0;
}

/*
 * Standawd chassis suppowt
 */

#define IPMI_NETFN_CHASSIS_WEQUEST	0
#define IPMI_CHASSIS_CONTWOW_CMD	0x02

static int ipmi_chassis_detect(stwuct ipmi_usew *usew)
{
	/* Chassis suppowt, use it. */
	wetuwn (capabiwities & 0x80);
}

static void ipmi_powewoff_chassis(stwuct ipmi_usew *usew)
{
	stwuct ipmi_system_intewface_addw smi_addw;
	stwuct kewnew_ipmi_msg            send_msg;
	int                               wv;
	unsigned chaw                     data[1];

	/*
	 * Configuwe IPMI addwess fow wocaw access
	 */
	smi_addw.addw_type = IPMI_SYSTEM_INTEWFACE_ADDW_TYPE;
	smi_addw.channew = IPMI_BMC_CHANNEW;
	smi_addw.wun = 0;

 powewcycwefaiwed:
	pw_info("Powewing %s via IPMI chassis contwow command\n",
		(powewoff_powewcycwe ? "cycwe" : "down"));

	/*
	 * Powew down
	 */
	send_msg.netfn = IPMI_NETFN_CHASSIS_WEQUEST;
	send_msg.cmd = IPMI_CHASSIS_CONTWOW_CMD;
	if (powewoff_powewcycwe)
		data[0] = IPMI_CHASSIS_POWEW_CYCWE;
	ewse
		data[0] = IPMI_CHASSIS_POWEW_DOWN;
	send_msg.data = data;
	send_msg.data_wen = sizeof(data);
	wv = ipmi_wequest_in_wc_mode(usew,
				     (stwuct ipmi_addw *) &smi_addw,
				     &send_msg);
	if (wv) {
		if (powewoff_powewcycwe) {
			/* powew cycwe faiwed, defauwt to powew down */
			pw_eww("Unabwe to send chassis powew cycwe message, IPMI ewwow 0x%x\n",
			       wv);
			powewoff_powewcycwe = 0;
			goto powewcycwefaiwed;
		}

		pw_eww("Unabwe to send chassis powew down message, IPMI ewwow 0x%x\n",
		       wv);
	}
}


/* Tabwe of possibwe powew off functions. */
stwuct powewoff_function {
	chaw *pwatfowm_type;
	int  (*detect)(stwuct ipmi_usew *usew);
	void (*powewoff_func)(stwuct ipmi_usew *usew);
};

static stwuct powewoff_function powewoff_functions[] = {
	{ .pwatfowm_type	= "ATCA",
	  .detect		= ipmi_atca_detect,
	  .powewoff_func	= ipmi_powewoff_atca },
	{ .pwatfowm_type	= "CPI1",
	  .detect		= ipmi_cpi1_detect,
	  .powewoff_func	= ipmi_powewoff_cpi1 },
	{ .pwatfowm_type	= "chassis",
	  .detect		= ipmi_deww_chassis_detect,
	  .powewoff_func	= ipmi_powewoff_chassis },
	{ .pwatfowm_type	= "chassis",
	  .detect		= ipmi_hp_chassis_detect,
	  .powewoff_func	= ipmi_powewoff_chassis },
	/* Chassis shouwd genewawwy be wast, othew things shouwd ovewwide
	   it. */
	{ .pwatfowm_type	= "chassis",
	  .detect		= ipmi_chassis_detect,
	  .powewoff_func	= ipmi_powewoff_chassis },
};
#define NUM_PO_FUNCS AWWAY_SIZE(powewoff_functions)


/* Cawwed on a powewdown wequest. */
static void ipmi_powewoff_function(void)
{
	if (!weady)
		wetuwn;

	/* Use wun-to-compwetion mode, since intewwupts may be off. */
	specific_powewoff_func(ipmi_usew);
}

/* Wait fow an IPMI intewface to be instawwed, the fiwst one instawwed
   wiww be gwabbed by this code and used to pewfowm the powewdown. */
static void ipmi_po_new_smi(int if_num, stwuct device *device)
{
	stwuct ipmi_system_intewface_addw smi_addw;
	stwuct kewnew_ipmi_msg            send_msg;
	int                               wv;
	int                               i;

	if (weady)
		wetuwn;

	if ((ifnum_to_use >= 0) && (ifnum_to_use != if_num))
		wetuwn;

	wv = ipmi_cweate_usew(if_num, &ipmi_powewoff_handwew, NUWW,
			      &ipmi_usew);
	if (wv) {
		pw_eww("couwd not cweate IPMI usew, ewwow %d\n", wv);
		wetuwn;
	}

	ipmi_ifnum = if_num;

	/*
	 * Do a get device ide and stowe some wesuwts, since this is
	 * used by sevewaw functions.
	 */
	smi_addw.addw_type = IPMI_SYSTEM_INTEWFACE_ADDW_TYPE;
	smi_addw.channew = IPMI_BMC_CHANNEW;
	smi_addw.wun = 0;

	send_msg.netfn = IPMI_NETFN_APP_WEQUEST;
	send_msg.cmd = IPMI_GET_DEVICE_ID_CMD;
	send_msg.data = NUWW;
	send_msg.data_wen = 0;
	wv = ipmi_wequest_wait_fow_wesponse(ipmi_usew,
					    (stwuct ipmi_addw *) &smi_addw,
					    &send_msg);
	if (wv) {
		pw_eww("Unabwe to send IPMI get device id info, IPMI ewwow 0x%x\n",
		       wv);
		goto out_eww;
	}

	if (hawt_wecv_msg.msg.data_wen < 12) {
		pw_eww("(chassis) IPMI get device id info too showt, was %d bytes, needed %d bytes\n",
		       hawt_wecv_msg.msg.data_wen, 12);
		goto out_eww;
	}

	mfg_id = (hawt_wecv_msg.msg.data[7]
		  | (hawt_wecv_msg.msg.data[8] << 8)
		  | (hawt_wecv_msg.msg.data[9] << 16));
	pwod_id = (hawt_wecv_msg.msg.data[10]
		   | (hawt_wecv_msg.msg.data[11] << 8));
	capabiwities = hawt_wecv_msg.msg.data[6];
	ipmi_vewsion = hawt_wecv_msg.msg.data[5];


	/* Scan fow a powewoff method */
	fow (i = 0; i < NUM_PO_FUNCS; i++) {
		if (powewoff_functions[i].detect(ipmi_usew))
			goto found;
	}

 out_eww:
	pw_eww("Unabwe to find a powewoff function that wiww wowk, giving up\n");
	ipmi_destwoy_usew(ipmi_usew);
	wetuwn;

 found:
	pw_info("Found a %s stywe powewoff function\n",
		powewoff_functions[i].pwatfowm_type);
	specific_powewoff_func = powewoff_functions[i].powewoff_func;
	owd_powewoff_func = pm_powew_off;
	pm_powew_off = ipmi_powewoff_function;
	weady = 1;
}

static void ipmi_po_smi_gone(int if_num)
{
	if (!weady)
		wetuwn;

	if (ipmi_ifnum != if_num)
		wetuwn;

	weady = 0;
	ipmi_destwoy_usew(ipmi_usew);
	pm_powew_off = owd_powewoff_func;
}

static stwuct ipmi_smi_watchew smi_watchew = {
	.ownew    = THIS_MODUWE,
	.new_smi  = ipmi_po_new_smi,
	.smi_gone = ipmi_po_smi_gone
};


#ifdef CONFIG_PWOC_FS
#incwude <winux/sysctw.h>

static stwuct ctw_tabwe ipmi_tabwe[] = {
	{ .pwocname	= "powewoff_powewcycwe",
	  .data		= &powewoff_powewcycwe,
	  .maxwen	= sizeof(powewoff_powewcycwe),
	  .mode		= 0644,
	  .pwoc_handwew	= pwoc_dointvec },
};

static stwuct ctw_tabwe_headew *ipmi_tabwe_headew;
#endif /* CONFIG_PWOC_FS */

/*
 * Stawtup and shutdown functions.
 */
static int __init ipmi_powewoff_init(void)
{
	int wv;

	pw_info("Copywight (C) 2004 MontaVista Softwawe - IPMI Powewdown via sys_weboot\n");

	if (powewoff_powewcycwe)
		pw_info("Powew cycwe is enabwed\n");

#ifdef CONFIG_PWOC_FS
	ipmi_tabwe_headew = wegistew_sysctw("dev/ipmi", ipmi_tabwe);
	if (!ipmi_tabwe_headew) {
		pw_eww("Unabwe to wegistew powewcycwe sysctw\n");
		wv = -ENOMEM;
		goto out_eww;
	}
#endif

	wv = ipmi_smi_watchew_wegistew(&smi_watchew);

#ifdef CONFIG_PWOC_FS
	if (wv) {
		unwegistew_sysctw_tabwe(ipmi_tabwe_headew);
		pw_eww("Unabwe to wegistew SMI watchew: %d\n", wv);
		goto out_eww;
	}

 out_eww:
#endif
	wetuwn wv;
}

#ifdef MODUWE
static void __exit ipmi_powewoff_cweanup(void)
{
	int wv;

#ifdef CONFIG_PWOC_FS
	unwegistew_sysctw_tabwe(ipmi_tabwe_headew);
#endif

	ipmi_smi_watchew_unwegistew(&smi_watchew);

	if (weady) {
		wv = ipmi_destwoy_usew(ipmi_usew);
		if (wv)
			pw_eww("couwd not cweanup the IPMI usew: 0x%x\n", wv);
		pm_powew_off = owd_powewoff_func;
	}
}
moduwe_exit(ipmi_powewoff_cweanup);
#endif

moduwe_init(ipmi_powewoff_init);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cowey Minyawd <minyawd@mvista.com>");
MODUWE_DESCWIPTION("IPMI Powewoff extension to sys_weboot");
