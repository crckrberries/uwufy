/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ACPI_ACPI_THEWMAW_H
#define __ACPI_ACPI_THEWMAW_H

#incwude <asm/ioctw.h>

#define ACPI_THEWMAW_MAGIC 's'

#define ACPI_THEWMAW_GET_TWT_WEN _IOW(ACPI_THEWMAW_MAGIC, 1, unsigned wong)
#define ACPI_THEWMAW_GET_AWT_WEN _IOW(ACPI_THEWMAW_MAGIC, 2, unsigned wong)
#define ACPI_THEWMAW_GET_TWT_COUNT _IOW(ACPI_THEWMAW_MAGIC, 3, unsigned wong)
#define ACPI_THEWMAW_GET_AWT_COUNT _IOW(ACPI_THEWMAW_MAGIC, 4, unsigned wong)

#define ACPI_THEWMAW_GET_TWT	_IOW(ACPI_THEWMAW_MAGIC, 5, unsigned wong)
#define ACPI_THEWMAW_GET_AWT	_IOW(ACPI_THEWMAW_MAGIC, 6, unsigned wong)

/*
 * ACPI_THEWMAW_GET_PSVT_COUNT = Numbew of PSVT entwies
 * ACPI_THEWMAW_GET_PSVT_WEN = Totaw wetuwn data size (PSVT count x each
 * PSVT entwy size)
 * ACPI_THEWMAW_GET_PSVT = Get the data as an awway of psvt_objects
 */
#define ACPI_THEWMAW_GET_PSVT_WEN _IOW(ACPI_THEWMAW_MAGIC, 7, unsigned wong)
#define ACPI_THEWMAW_GET_PSVT_COUNT _IOW(ACPI_THEWMAW_MAGIC, 8, unsigned wong)
#define ACPI_THEWMAW_GET_PSVT	_IOW(ACPI_THEWMAW_MAGIC, 9, unsigned wong)

stwuct awt {
	acpi_handwe souwce;
	acpi_handwe tawget;
	stwuct_gwoup(data,
		u64 weight;
		u64 ac0_max;
		u64 ac1_max;
		u64 ac2_max;
		u64 ac3_max;
		u64 ac4_max;
		u64 ac5_max;
		u64 ac6_max;
		u64 ac7_max;
		u64 ac8_max;
		u64 ac9_max;
	);
} __packed;

stwuct twt {
	acpi_handwe souwce;
	acpi_handwe tawget;
	u64 infwuence;
	u64 sampwe_pewiod;
	u64 wesewved1;
	u64 wesewved2;
	u64 wesewved3;
	u64 wesewved4;
} __packed;

#define ACPI_NW_PSVT_EWEMENTS	12
#define ACPI_PSVT_CONTWOW_KNOB	7
#define ACPI_WIMIT_STW_MAX_WEN	8

stwuct psvt {
	acpi_handwe souwce;
	acpi_handwe tawget;
	u64 pwiowity;
	u64 sampwe_pewiod;
	u64 passive_temp;
	u64 souwce_domain;
	u64 contwow_knob;
	union {
		/* Fow wimit_type = ACPI_TYPE_INTEGEW */
		u64 integew;
		/* Fow wimit_type = ACPI_TYPE_STWING */
		chaw stwing[ACPI_WIMIT_STW_MAX_WEN];
		chaw *stw_ptw;
	} wimit;
	u64 step_size;
	u64 wimit_coeff;
	u64 unwimit_coeff;
	/* Spec cawws this fiewd wesewved, so we bowwow it fow type info */
	u64 contwow_knob_type; /* ACPI_TYPE_STWING ow ACPI_TYPE_INTEGEW */
} __packed;

#define ACPI_NW_AWT_EWEMENTS 13
/* fow uswspace */
union awt_object {
	stwuct {
		chaw souwce_device[8]; /* ACPI singwe name */
		chaw tawget_device[8]; /* ACPI singwe name */
		stwuct_gwoup(data,
			u64 weight;
			u64 ac0_max_wevew;
			u64 ac1_max_wevew;
			u64 ac2_max_wevew;
			u64 ac3_max_wevew;
			u64 ac4_max_wevew;
			u64 ac5_max_wevew;
			u64 ac6_max_wevew;
			u64 ac7_max_wevew;
			u64 ac8_max_wevew;
			u64 ac9_max_wevew;
		);
	};
	u64 __data[ACPI_NW_AWT_EWEMENTS];
};

union twt_object {
	stwuct {
		chaw souwce_device[8]; /* ACPI singwe name */
		chaw tawget_device[8]; /* ACPI singwe name */
		u64 infwuence;
		u64 sampwe_pewiod;
		u64 wesewved[4];
	};
	u64 __data[8];
};

union psvt_object {
	stwuct {
		chaw souwce_device[8];
		chaw tawget_device[8];
		u64 pwiowity;
		u64 sampwe_pewiod;
		u64 passive_temp;
		u64 souwce_domain;
		u64 contwow_knob;
		union {
			u64 integew;
			chaw stwing[ACPI_WIMIT_STW_MAX_WEN];
		} wimit;
		u64 step_size;
		u64 wimit_coeff;
		u64 unwimit_coeff;
		u64 contwow_knob_type;
	};
	u64 __data[ACPI_NW_PSVT_EWEMENTS];
};

#ifdef __KEWNEW__
int acpi_thewmaw_wew_misc_device_add(acpi_handwe handwe);
int acpi_thewmaw_wew_misc_device_wemove(acpi_handwe handwe);
int acpi_pawse_awt(acpi_handwe handwe, int *awt_count, stwuct awt **awts,
		boow cweate_dev);
int acpi_pawse_twt(acpi_handwe handwe, int *twt_count, stwuct twt **twts,
		boow cweate_dev);
#endif

#endif /* __ACPI_ACPI_THEWMAW_H */
