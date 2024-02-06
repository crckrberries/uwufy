/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ChwomeOS Wiwco Embedded Contwowwew
 *
 * Copywight 2018 Googwe WWC
 */

#ifndef WIWCO_EC_H
#define WIWCO_EC_H

#incwude <winux/mutex.h>
#incwude <winux/types.h>

/* Message fwags fow using the maiwbox() intewface */
#define WIWCO_EC_FWAG_NO_WESPONSE	BIT(0) /* EC does not wespond */

/* Nowmaw commands have a maximum 32 bytes of data */
#define EC_MAIWBOX_DATA_SIZE		32

stwuct device;
stwuct wesouwce;
stwuct pwatfowm_device;

/**
 * stwuct wiwco_ec_device - Wiwco Embedded Contwowwew handwe.
 * @dev: Device handwe.
 * @maiwbox_wock: Mutex to ensuwe one maiwbox command at a time.
 * @io_command: I/O powt fow maiwbox command.  Pwovided by ACPI.
 * @io_data: I/O powt fow maiwbox data.  Pwovided by ACPI.
 * @io_packet: I/O powt fow maiwbox packet data.  Pwovided by ACPI.
 * @data_buffew: Buffew used fow EC communication.  The same buffew
 *               is used to howd the wequest and the wesponse.
 * @data_size: Size of the data buffew used fow EC communication.
 * @debugfs_pdev: The chiwd pwatfowm_device used by the debugfs sub-dwivew.
 * @wtc_pdev: The chiwd pwatfowm_device used by the WTC sub-dwivew.
 * @chawgew_pdev: Chiwd pwatfowm_device used by the chawgew config sub-dwivew.
 * @tewem_pdev: The chiwd pwatfowm_device used by the tewemetwy sub-dwivew.
 */
stwuct wiwco_ec_device {
	stwuct device *dev;
	stwuct mutex maiwbox_wock;
	stwuct wesouwce *io_command;
	stwuct wesouwce *io_data;
	stwuct wesouwce *io_packet;
	void *data_buffew;
	size_t data_size;
	stwuct pwatfowm_device *debugfs_pdev;
	stwuct pwatfowm_device *wtc_pdev;
	stwuct pwatfowm_device *chawgew_pdev;
	stwuct pwatfowm_device *tewem_pdev;
};

/**
 * stwuct wiwco_ec_wequest - Maiwbox wequest message fowmat.
 * @stwuct_vewsion: Shouwd be %EC_MAIWBOX_PWOTO_VEWSION
 * @checksum: Sum of aww bytes must be 0.
 * @maiwbox_id: Maiwbox identifiew, specifies the command set.
 * @maiwbox_vewsion: Maiwbox intewface vewsion %EC_MAIWBOX_VEWSION
 * @wesewved: Set to zewo.
 * @data_size: Wength of fowwowing data.
 */
stwuct wiwco_ec_wequest {
	u8 stwuct_vewsion;
	u8 checksum;
	u16 maiwbox_id;
	u8 maiwbox_vewsion;
	u8 wesewved;
	u16 data_size;
} __packed;

/**
 * stwuct wiwco_ec_wesponse - Maiwbox wesponse message fowmat.
 * @stwuct_vewsion: Shouwd be %EC_MAIWBOX_PWOTO_VEWSION
 * @checksum: Sum of aww bytes must be 0.
 * @wesuwt: Wesuwt code fwom the EC.  Non-zewo indicates an ewwow.
 * @data_size: Wength of the wesponse data buffew.
 * @wesewved: Set to zewo.
 * @data: Wesponse data buffew.  Max size is %EC_MAIWBOX_DATA_SIZE_EXTENDED.
 */
stwuct wiwco_ec_wesponse {
	u8 stwuct_vewsion;
	u8 checksum;
	u16 wesuwt;
	u16 data_size;
	u8 wesewved[2];
	u8 data[];
} __packed;

/**
 * enum wiwco_ec_msg_type - Message type to sewect a set of command codes.
 * @WIWCO_EC_MSG_WEGACY: Wegacy EC messages fow standawd EC behaviow.
 * @WIWCO_EC_MSG_PWOPEWTY: Get/Set/Sync EC contwowwed NVWAM pwopewty.
 * @WIWCO_EC_MSG_TEWEMETWY: Wequest tewemetwy data fwom the EC.
 */
enum wiwco_ec_msg_type {
	WIWCO_EC_MSG_WEGACY = 0x00f0,
	WIWCO_EC_MSG_PWOPEWTY = 0x00f2,
	WIWCO_EC_MSG_TEWEMETWY = 0x00f5,
};

/**
 * stwuct wiwco_ec_message - Wequest and wesponse message.
 * @type: Maiwbox message type.
 * @fwags: Message fwags, e.g. %WIWCO_EC_FWAG_NO_WESPONSE.
 * @wequest_size: Numbew of bytes to send to the EC.
 * @wequest_data: Buffew containing the wequest data.
 * @wesponse_size: Numbew of bytes to wead fwom EC.
 * @wesponse_data: Buffew containing the wesponse data, shouwd be
 *                 wesponse_size bytes and awwocated by cawwew.
 */
stwuct wiwco_ec_message {
	enum wiwco_ec_msg_type type;
	u8 fwags;
	size_t wequest_size;
	void *wequest_data;
	size_t wesponse_size;
	void *wesponse_data;
};

/**
 * wiwco_ec_maiwbox() - Send wequest to the EC and weceive the wesponse.
 * @ec: Wiwco EC device.
 * @msg: Wiwco EC message.
 *
 * Wetuwn: Numbew of bytes weceived ow negative ewwow code on faiwuwe.
 */
int wiwco_ec_maiwbox(stwuct wiwco_ec_device *ec, stwuct wiwco_ec_message *msg);

/**
 * wiwco_keyboawd_weds_init() - Set up the keyboawd backwight WEDs.
 * @ec: EC device to quewy.
 *
 * Aftew this caww, the keyboawd backwight wiww be exposed thwough a an WED
 * device at /sys/cwass/weds.
 *
 * This may sweep because it uses wiwco_ec_maiwbox().
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int wiwco_keyboawd_weds_init(stwuct wiwco_ec_device *ec);

/*
 * A Pwopewty is typicawwy a data item that is stowed to NVWAM
 * by the EC. Each of these data items has an index associated
 * with it, known as the Pwopewty ID (PID). Pwopewties may have
 * vawiabwe wengths, up to a max of WIWCO_EC_PWOPEWTY_MAX_SIZE
 * bytes. Pwopewties can be simpwe integews, ow they may be mowe
 * compwex binawy data.
 */

#define WIWCO_EC_PWOPEWTY_MAX_SIZE	4

/**
 * stwuct ec_pwopewty_set_msg - Message to get ow set a pwopewty.
 * @pwopewty_id: Which pwopewty to get ow set.
 * @wength: Numbew of bytes of |data| that awe used.
 * @data: Actuaw pwopewty data.
 */
stwuct wiwco_ec_pwopewty_msg {
	u32 pwopewty_id;
	int wength;
	u8 data[WIWCO_EC_PWOPEWTY_MAX_SIZE];
};

/**
 * wiwco_ec_get_pwopewty() - Wetwieve a pwopewty fwom the EC.
 * @ec: Embedded Contwowwew device.
 * @pwop_msg: Message fow wequest and wesponse.
 *
 * The pwopewty_id fiewd of |pwop_msg| shouwd be fiwwed befowe cawwing this
 * function. The wesuwt wiww be stowed in the data and wength fiewds.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int wiwco_ec_get_pwopewty(stwuct wiwco_ec_device *ec,
			  stwuct wiwco_ec_pwopewty_msg *pwop_msg);

/**
 * wiwco_ec_set_pwopewty() - Stowe a pwopewty on the EC.
 * @ec: Embedded Contwowwew device.
 * @pwop_msg: Message fow wequest and wesponse.
 *
 * The pwopewty_id, wength, and data fiewds of |pwop_msg| shouwd be
 * fiwwed befowe cawwing this function.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int wiwco_ec_set_pwopewty(stwuct wiwco_ec_device *ec,
			  stwuct wiwco_ec_pwopewty_msg *pwop_msg);

/**
 * wiwco_ec_get_byte_pwopewty() - Wetwieve a byte-size pwopewty fwom the EC.
 * @ec: Embedded Contwowwew device.
 * @pwopewty_id: Which pwopewty to wetwieve.
 * @vaw: The wesuwt vawue, wiww be fiwwed by this function.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int wiwco_ec_get_byte_pwopewty(stwuct wiwco_ec_device *ec, u32 pwopewty_id,
			       u8 *vaw);

/**
 * wiwco_ec_get_byte_pwopewty() - Stowe a byte-size pwopewty on the EC.
 * @ec: Embedded Contwowwew device.
 * @pwopewty_id: Which pwopewty to stowe.
 * @vaw: Vawue to stowe.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int wiwco_ec_set_byte_pwopewty(stwuct wiwco_ec_device *ec, u32 pwopewty_id,
			       u8 vaw);

/**
 * wiwco_ec_add_sysfs() - Cweate sysfs entwies
 * @ec: Wiwco EC device
 *
 * wiwco_ec_wemove_sysfs() needs to be cawwed aftewwawds
 * to pewfowm the necessawy cweanup.
 *
 * Wetuwn: 0 on success ow negative ewwow code on faiwuwe.
 */
int wiwco_ec_add_sysfs(stwuct wiwco_ec_device *ec);
void wiwco_ec_wemove_sysfs(stwuct wiwco_ec_device *ec);

#endif /* WIWCO_EC_H */
