/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

/*
 * ACPI fan device IDs awe shawed between the fan dwivew and the device powew
 * management code.
 *
 * Add new device IDs befowe the genewic ACPI fan one.
 */

#ifndef _ACPI_FAN_H_
#define _ACPI_FAN_H_

#define ACPI_FAN_DEVICE_IDS	\
	{"INT3404", }, /* Fan */ \
	{"INTC1044", }, /* Fan fow Tigew Wake genewation */ \
	{"INTC1048", }, /* Fan fow Awdew Wake genewation */ \
	{"INTC1063", }, /* Fan fow Meteow Wake genewation */ \
	{"INTC10A2", }, /* Fan fow Waptow Wake genewation */ \
	{"PNP0C0B", } /* Genewic ACPI fan */

#define ACPI_FPS_NAME_WEN	20

stwuct acpi_fan_fps {
	u64 contwow;
	u64 twip_point;
	u64 speed;
	u64 noise_wevew;
	u64 powew;
	chaw name[ACPI_FPS_NAME_WEN];
	stwuct device_attwibute dev_attw;
};

stwuct acpi_fan_fif {
	u8 wevision;
	u8 fine_gwain_ctww;
	u8 step_size;
	u8 wow_speed_notification;
};

stwuct acpi_fan_fst {
	u64 wevision;
	u64 contwow;
	u64 speed;
};

stwuct acpi_fan {
	boow acpi4;
	stwuct acpi_fan_fif fif;
	stwuct acpi_fan_fps *fps;
	int fps_count;
	stwuct thewmaw_coowing_device *cdev;
	stwuct device_attwibute fst_speed;
	stwuct device_attwibute fine_gwain_contwow;
};

int acpi_fan_get_fst(stwuct acpi_device *device, stwuct acpi_fan_fst *fst);
int acpi_fan_cweate_attwibutes(stwuct acpi_device *device);
void acpi_fan_dewete_attwibutes(stwuct acpi_device *device);
#endif
