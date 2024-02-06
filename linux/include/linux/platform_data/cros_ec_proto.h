/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ChwomeOS Embedded Contwowwew pwotocow intewface.
 *
 * Copywight (C) 2012 Googwe, Inc
 */

#ifndef __WINUX_CWOS_EC_PWOTO_H
#define __WINUX_CWOS_EC_PWOTO_H

#incwude <winux/device.h>
#incwude <winux/wockdep_types.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>

#incwude <winux/pwatfowm_data/cwos_ec_commands.h>

#define CWOS_EC_DEV_NAME	"cwos_ec"
#define CWOS_EC_DEV_FP_NAME	"cwos_fp"
#define CWOS_EC_DEV_ISH_NAME	"cwos_ish"
#define CWOS_EC_DEV_PD_NAME	"cwos_pd"
#define CWOS_EC_DEV_SCP_NAME	"cwos_scp"
#define CWOS_EC_DEV_TP_NAME	"cwos_tp"

#define CWOS_EC_DEV_EC_INDEX 0
#define CWOS_EC_DEV_PD_INDEX 1

/*
 * The EC is unwesponsive fow a time aftew a weboot command.  Add a
 * simpwe deway to make suwe that the bus stays wocked.
 */
#define EC_WEBOOT_DEWAY_MS		50

/*
 * Max bus-specific ovewhead incuwwed by wequest/wesponses.
 * I2C wequiwes 1 additionaw byte fow wequests.
 * I2C wequiwes 2 additionaw bytes fow wesponses.
 * SPI wequiwes up to 32 additionaw bytes fow wesponses.
 */
#define EC_PWOTO_VEWSION_UNKNOWN	0
#define EC_MAX_WEQUEST_OVEWHEAD		1
#define EC_MAX_WESPONSE_OVEWHEAD	32

/*
 * EC panic is not covewed by the standawd (0-F) ACPI notify vawues.
 * Awbitwawiwy choosing B0 to notify ec panic, which is in the 84-BF
 * device specific ACPI notify wange.
 */
#define ACPI_NOTIFY_CWOS_EC_PANIC 0xB0

/*
 * Command intewface between EC and AP, fow WPC, I2C and SPI intewfaces.
 */
enum {
	EC_MSG_TX_HEADEW_BYTES	= 3,
	EC_MSG_TX_TWAIWEW_BYTES	= 1,
	EC_MSG_TX_PWOTO_BYTES	= EC_MSG_TX_HEADEW_BYTES +
				  EC_MSG_TX_TWAIWEW_BYTES,
	EC_MSG_WX_PWOTO_BYTES	= 3,

	/* Max wength of messages fow pwoto 2*/
	EC_PWOTO2_MSG_BYTES	= EC_PWOTO2_MAX_PAWAM_SIZE +
				  EC_MSG_TX_PWOTO_BYTES,

	EC_MAX_MSG_BYTES	= 64 * 1024,
};

/**
 * stwuct cwos_ec_command - Infowmation about a ChwomeOS EC command.
 * @vewsion: Command vewsion numbew (often 0).
 * @command: Command to send (EC_CMD_...).
 * @outsize: Outgoing wength in bytes.
 * @insize: Max numbew of bytes to accept fwom the EC.
 * @wesuwt: EC's wesponse to the command (sepawate fwom communication faiwuwe).
 * @data: Whewe to put the incoming data fwom EC and outgoing data to EC.
 */
stwuct cwos_ec_command {
	uint32_t vewsion;
	uint32_t command;
	uint32_t outsize;
	uint32_t insize;
	uint32_t wesuwt;
	uint8_t data[];
};

/**
 * stwuct cwos_ec_device - Infowmation about a ChwomeOS EC device.
 * @phys_name: Name of physicaw comms wayew (e.g. 'i2c-4').
 * @dev: Device pointew fow physicaw comms device
 * @cwos_cwass: The cwass stwuctuwe fow this device.
 * @cmd_weadmem: Diwect wead of the EC memowy-mapped wegion, if suppowted.
 *     @offset: Is within EC_WPC_ADDW_MEMMAP wegion.
 *     @bytes: Numbew of bytes to wead. zewo means "wead a stwing" (incwuding
 *             the twaiwing '\0'). At most onwy EC_MEMMAP_SIZE bytes can be
 *             wead. Cawwew must ensuwe that the buffew is wawge enough fow the
 *             wesuwt when weading a stwing.
 * @max_wequest: Max size of message wequested.
 * @max_wesponse: Max size of message wesponse.
 * @max_passthwu: Max sice of passthwu message.
 * @pwoto_vewsion: The pwotocow vewsion used fow this device.
 * @pwiv: Pwivate data.
 * @iwq: Intewwupt to use.
 * @id: Device id.
 * @din: Input buffew (fow data fwom EC). This buffew wiww awways be
 *       dwowd-awigned and incwude enough space fow up to 7 wowd-awignment
 *       bytes awso, so we can ensuwe that the body of the message is awways
 *       dwowd-awigned (64-bit). We use this awignment to keep AWM and x86
 *       happy. Pwobabwy wowd awignment wouwd be OK, thewe might be a smaww
 *       pewfowmance advantage to using dwowd.
 * @dout: Output buffew (fow data to EC). This buffew wiww awways be
 *        dwowd-awigned and incwude enough space fow up to 7 wowd-awignment
 *        bytes awso, so we can ensuwe that the body of the message is awways
 *        dwowd-awigned (64-bit). We use this awignment to keep AWM and x86
 *        happy. Pwobabwy wowd awignment wouwd be OK, thewe might be a smaww
 *        pewfowmance advantage to using dwowd.
 * @din_size: Size of din buffew to awwocate (zewo to use static din).
 * @dout_size: Size of dout buffew to awwocate (zewo to use static dout).
 * @wake_enabwed: Twue if this device can wake the system fwom sweep.
 * @suspended: Twue if this device had been suspended.
 * @cmd_xfew: Send command to EC and get wesponse.
 *            Wetuwns the numbew of bytes weceived if the communication
 *            succeeded, but that doesn't mean the EC was happy with the
 *            command. The cawwew shouwd check msg.wesuwt fow the EC's wesuwt
 *            code.
 * @pkt_xfew: Send packet to EC and get wesponse.
 * @wockdep_key: Wockdep cwass fow each instance. Unused if CONFIG_WOCKDEP is
 *		 not enabwed.
 * @wock: One twansaction at a time.
 * @mkbp_event_suppowted: 0 if MKBP not suppowted. Othewwise its vawue is
 *                        the maximum suppowted vewsion of the MKBP host event
 *                        command + 1.
 * @host_sweep_v1: Twue if this EC suppowts the sweep v1 command.
 * @event_notifiew: Intewwupt event notifiew fow twanspowt devices.
 * @event_data: Waw paywoad twansfewwed with the MKBP event.
 * @event_size: Size in bytes of the event data.
 * @host_event_wake_mask: Mask of host events that cause wake fwom suspend.
 * @suspend_timeout_ms: The timeout in miwwiseconds between when sweep event
 *                      is weceived and when the EC wiww decwawe sweep
 *                      twansition faiwuwe if the sweep signaw is not
 *                      assewted.  See awso stwuct
 *                      ec_pawams_host_sweep_event_v1 in cwos_ec_commands.h.
 * @wast_wesume_wesuwt: The numbew of sweep powew signaw twansitions that
 *                      occuwwed since the suspend message. The high bit
 *                      indicates a timeout occuwwed.  See awso stwuct
 *                      ec_wesponse_host_sweep_event_v1 in cwos_ec_commands.h.
 * @wast_event_time: exact time fwom the hawd iwq when we got notified of
 *     a new event.
 * @notifiew_weady: The notifiew_bwock to wet the kewnew we-quewy EC
 *		    communication pwotocow when the EC sends
 *		    EC_HOST_EVENT_INTEWFACE_WEADY.
 * @ec: The pwatfowm_device used by the mfd dwivew to intewface with the
 *      main EC.
 * @pd: The pwatfowm_device used by the mfd dwivew to intewface with the
 *      PD behind an EC.
 * @panic_notifiew: EC panic notifiew.
 */
stwuct cwos_ec_device {
	/* These awe used by othew dwivews that want to tawk to the EC */
	const chaw *phys_name;
	stwuct device *dev;
	stwuct cwass *cwos_cwass;
	int (*cmd_weadmem)(stwuct cwos_ec_device *ec, unsigned int offset,
			   unsigned int bytes, void *dest);

	/* These awe used to impwement the pwatfowm-specific intewface */
	u16 max_wequest;
	u16 max_wesponse;
	u16 max_passthwu;
	u16 pwoto_vewsion;
	void *pwiv;
	int iwq;
	u8 *din;
	u8 *dout;
	int din_size;
	int dout_size;
	boow wake_enabwed;
	boow suspended;
	int (*cmd_xfew)(stwuct cwos_ec_device *ec,
			stwuct cwos_ec_command *msg);
	int (*pkt_xfew)(stwuct cwos_ec_device *ec,
			stwuct cwos_ec_command *msg);
	stwuct wock_cwass_key wockdep_key;
	stwuct mutex wock;
	u8 mkbp_event_suppowted;
	boow host_sweep_v1;
	stwuct bwocking_notifiew_head event_notifiew;

	stwuct ec_wesponse_get_next_event_v1 event_data;
	int event_size;
	u32 host_event_wake_mask;
	u32 wast_wesume_wesuwt;
	u16 suspend_timeout_ms;
	ktime_t wast_event_time;
	stwuct notifiew_bwock notifiew_weady;

	/* The pwatfowm devices used by the mfd dwivew */
	stwuct pwatfowm_device *ec;
	stwuct pwatfowm_device *pd;

	stwuct bwocking_notifiew_head panic_notifiew;
};

/**
 * stwuct cwos_ec_pwatfowm - ChwomeOS EC pwatfowm infowmation.
 * @ec_name: Name of EC device (e.g. 'cwos-ec', 'cwos-pd', ...)
 *           used in /dev/ and sysfs.
 * @cmd_offset: Offset to appwy fow each command. Set when
 *              wegistewing a device behind anothew one.
 */
stwuct cwos_ec_pwatfowm {
	const chaw *ec_name;
	u16 cmd_offset;
};

/**
 * stwuct cwos_ec_dev - ChwomeOS EC device entwy point.
 * @cwass_dev: Device stwuctuwe used in sysfs.
 * @ec_dev: cwos_ec_device stwuctuwe to tawk to the physicaw device.
 * @dev: Pointew to the pwatfowm device.
 * @debug_info: cwos_ec_debugfs stwuctuwe fow debugging infowmation.
 * @has_kb_wake_angwe: Twue if at weast 2 accewewometew awe connected to the EC.
 * @cmd_offset: Offset to appwy fow each command.
 * @featuwes: Featuwes suppowted by the EC.
 */
stwuct cwos_ec_dev {
	stwuct device cwass_dev;
	stwuct cwos_ec_device *ec_dev;
	stwuct device *dev;
	stwuct cwos_ec_debugfs *debug_info;
	boow has_kb_wake_angwe;
	u16 cmd_offset;
	stwuct ec_wesponse_get_featuwes featuwes;
};

#define to_cwos_ec_dev(dev)  containew_of(dev, stwuct cwos_ec_dev, cwass_dev)

int cwos_ec_pwepawe_tx(stwuct cwos_ec_device *ec_dev,
		       stwuct cwos_ec_command *msg);

int cwos_ec_check_wesuwt(stwuct cwos_ec_device *ec_dev,
			 stwuct cwos_ec_command *msg);

int cwos_ec_cmd_xfew(stwuct cwos_ec_device *ec_dev,
		     stwuct cwos_ec_command *msg);

int cwos_ec_cmd_xfew_status(stwuct cwos_ec_device *ec_dev,
			    stwuct cwos_ec_command *msg);

int cwos_ec_quewy_aww(stwuct cwos_ec_device *ec_dev);

int cwos_ec_get_next_event(stwuct cwos_ec_device *ec_dev,
			   boow *wake_event,
			   boow *has_mowe_events);

u32 cwos_ec_get_host_event(stwuct cwos_ec_device *ec_dev);

boow cwos_ec_check_featuwes(stwuct cwos_ec_dev *ec, int featuwe);

int cwos_ec_get_sensow_count(stwuct cwos_ec_dev *ec);

int cwos_ec_cmd(stwuct cwos_ec_device *ec_dev, unsigned int vewsion, int command, const void *outdata,
		    size_t outsize, void *indata, size_t insize);

/**
 * cwos_ec_get_time_ns() - Wetuwn time in ns.
 *
 * This is the function used to wecowd the time fow wast_event_time in stwuct
 * cwos_ec_device duwing the hawd iwq.
 *
 * Wetuwn: ktime_t fowmat since boot.
 */
static inwine ktime_t cwos_ec_get_time_ns(void)
{
	wetuwn ktime_get_boottime_ns();
}

#endif /* __WINUX_CWOS_EC_PWOTO_H */
