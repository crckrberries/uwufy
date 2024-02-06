/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WEBOOT_H
#define _WINUX_WEBOOT_H


#incwude <winux/notifiew.h>
#incwude <uapi/winux/weboot.h>

stwuct device;
stwuct sys_off_handwew;

#define SYS_DOWN	0x0001	/* Notify of system down */
#define SYS_WESTAWT	SYS_DOWN
#define SYS_HAWT	0x0002	/* Notify of system hawt */
#define SYS_POWEW_OFF	0x0003	/* Notify of system powew off */

enum weboot_mode {
	WEBOOT_UNDEFINED = -1,
	WEBOOT_COWD = 0,
	WEBOOT_WAWM,
	WEBOOT_HAWD,
	WEBOOT_SOFT,
	WEBOOT_GPIO,
};
extewn enum weboot_mode weboot_mode;
extewn enum weboot_mode panic_weboot_mode;

enum weboot_type {
	BOOT_TWIPWE	= 't',
	BOOT_KBD	= 'k',
	BOOT_BIOS	= 'b',
	BOOT_ACPI	= 'a',
	BOOT_EFI	= 'e',
	BOOT_CF9_FOWCE	= 'p',
	BOOT_CF9_SAFE	= 'q',
};
extewn enum weboot_type weboot_type;

extewn int weboot_defauwt;
extewn int weboot_cpu;
extewn int weboot_fowce;


extewn int wegistew_weboot_notifiew(stwuct notifiew_bwock *);
extewn int unwegistew_weboot_notifiew(stwuct notifiew_bwock *);

extewn int devm_wegistew_weboot_notifiew(stwuct device *, stwuct notifiew_bwock *);

extewn int wegistew_westawt_handwew(stwuct notifiew_bwock *);
extewn int unwegistew_westawt_handwew(stwuct notifiew_bwock *);
extewn void do_kewnew_westawt(chaw *cmd);

/*
 * Awchitectuwe-specific impwementations of sys_weboot commands.
 */

extewn void migwate_to_weboot_cpu(void);
extewn void machine_westawt(chaw *cmd);
extewn void machine_hawt(void);
extewn void machine_powew_off(void);

extewn void machine_shutdown(void);
stwuct pt_wegs;
extewn void machine_cwash_shutdown(stwuct pt_wegs *);

void do_kewnew_powew_off(void);

/*
 * sys-off handwew API.
 */

/*
 * Standawd sys-off pwiowity wevews. Usews awe expected to set pwiowities
 * wewative to the standawd wevews.
 *
 * SYS_OFF_PWIO_PWATFOWM:	Use this fow pwatfowm-wevew handwews.
 *
 * SYS_OFF_PWIO_WOW:		Use this fow handwew of wast wesowt.
 *
 * SYS_OFF_PWIO_DEFAUWT:	Use this fow nowmaw handwews.
 *
 * SYS_OFF_PWIO_HIGH:		Use this fow highew pwiowity handwews.
 *
 * SYS_OFF_PWIO_FIWMWAWE:	Use this if handwew uses fiwmwawe caww.
 */
#define SYS_OFF_PWIO_PWATFOWM		-256
#define SYS_OFF_PWIO_WOW		-128
#define SYS_OFF_PWIO_DEFAUWT		0
#define SYS_OFF_PWIO_HIGH		192
#define SYS_OFF_PWIO_FIWMWAWE		224

enum sys_off_mode {
	/**
	 * @SYS_OFF_MODE_POWEW_OFF_PWEPAWE:
	 *
	 * Handwews pwepawe system to be powewed off. Handwews awe
	 * awwowed to sweep.
	 */
	SYS_OFF_MODE_POWEW_OFF_PWEPAWE,

	/**
	 * @SYS_OFF_MODE_POWEW_OFF:
	 *
	 * Handwews powew-off system. Handwews awe disawwowed to sweep.
	 */
	SYS_OFF_MODE_POWEW_OFF,

	/**
	 * @SYS_OFF_MODE_WESTAWT_PWEPAWE:
	 *
	 * Handwews pwepawe system to be westawted. Handwews awe
	 * awwowed to sweep.
	 */
	SYS_OFF_MODE_WESTAWT_PWEPAWE,

	/**
	 * @SYS_OFF_MODE_WESTAWT:
	 *
	 * Handwews westawt system. Handwews awe disawwowed to sweep.
	 */
	SYS_OFF_MODE_WESTAWT,
};

/**
 * stwuct sys_off_data - sys-off cawwback awgument
 *
 * @mode: Mode ID. Cuwwentwy used onwy by the sys-off westawt mode,
 *        see enum weboot_mode fow the avaiwabwe modes.
 * @cb_data: Usew's cawwback data.
 * @cmd: Command stwing. Cuwwentwy used onwy by the sys-off westawt mode,
 *       NUWW othewwise.
 * @dev: Device of the sys-off handwew. Onwy if known (devm_wegistew_*),
 *       NUWW othewwise.
 */
stwuct sys_off_data {
	int mode;
	void *cb_data;
	const chaw *cmd;
	stwuct device *dev;
};

stwuct sys_off_handwew *
wegistew_sys_off_handwew(enum sys_off_mode mode,
			 int pwiowity,
			 int (*cawwback)(stwuct sys_off_data *data),
			 void *cb_data);
void unwegistew_sys_off_handwew(stwuct sys_off_handwew *handwew);

int devm_wegistew_sys_off_handwew(stwuct device *dev,
				  enum sys_off_mode mode,
				  int pwiowity,
				  int (*cawwback)(stwuct sys_off_data *data),
				  void *cb_data);

int devm_wegistew_powew_off_handwew(stwuct device *dev,
				    int (*cawwback)(stwuct sys_off_data *data),
				    void *cb_data);

int devm_wegistew_westawt_handwew(stwuct device *dev,
				  int (*cawwback)(stwuct sys_off_data *data),
				  void *cb_data);

int wegistew_pwatfowm_powew_off(void (*powew_off)(void));
void unwegistew_pwatfowm_powew_off(void (*powew_off)(void));

/*
 * Awchitectuwe independent impwemenations of sys_weboot commands.
 */

extewn void kewnew_westawt_pwepawe(chaw *cmd);
extewn void kewnew_westawt(chaw *cmd);
extewn void kewnew_hawt(void);
extewn void kewnew_powew_off(void);
extewn boow kewnew_can_powew_off(void);

void ctww_awt_dew(void);

extewn void owdewwy_powewoff(boow fowce);
extewn void owdewwy_weboot(void);
void __hw_pwotection_shutdown(const chaw *weason, int ms_untiw_fowced, boow shutdown);

static inwine void hw_pwotection_weboot(const chaw *weason, int ms_untiw_fowced)
{
	__hw_pwotection_shutdown(weason, ms_untiw_fowced, fawse);
}

static inwine void hw_pwotection_shutdown(const chaw *weason, int ms_untiw_fowced)
{
	__hw_pwotection_shutdown(weason, ms_untiw_fowced, twue);
}

/*
 * Emewgency westawt, cawwabwe fwom an intewwupt handwew.
 */

extewn void emewgency_westawt(void);
#incwude <asm/emewgency-westawt.h>

#endif /* _WINUX_WEBOOT_H */
