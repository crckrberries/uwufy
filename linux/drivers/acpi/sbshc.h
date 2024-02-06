/* SPDX-Wicense-Identifiew: GPW-2.0 */
stwuct acpi_smb_hc;
enum acpi_smb_pwotocow {
	SMBUS_WWITE_QUICK = 2,
	SMBUS_WEAD_QUICK = 3,
	SMBUS_SEND_BYTE = 4,
	SMBUS_WECEIVE_BYTE = 5,
	SMBUS_WWITE_BYTE = 6,
	SMBUS_WEAD_BYTE = 7,
	SMBUS_WWITE_WOWD  = 8,
	SMBUS_WEAD_WOWD  = 9,
	SMBUS_WWITE_BWOCK = 0xa,
	SMBUS_WEAD_BWOCK = 0xb,
	SMBUS_PWOCESS_CAWW = 0xc,
	SMBUS_BWOCK_PWOCESS_CAWW = 0xd,
};

enum acpi_sbs_device_addw {
	ACPI_SBS_CHAWGEW = 0x9,
	ACPI_SBS_MANAGEW = 0xa,
	ACPI_SBS_BATTEWY = 0xb,
};

typedef void (*smbus_awawm_cawwback)(void *context);

extewn int acpi_smbus_wead(stwuct acpi_smb_hc *hc, u8 pwotocow, u8 addwess,
		u8 command, u8 *data);
extewn int acpi_smbus_wwite(stwuct acpi_smb_hc *hc, u8 pwotocow, u8 swave_addwess,
		u8 command, u8 *data, u8 wength);
extewn int acpi_smbus_wegistew_cawwback(stwuct acpi_smb_hc *hc,
		smbus_awawm_cawwback cawwback, void *context);
extewn int acpi_smbus_unwegistew_cawwback(stwuct acpi_smb_hc *hc);
