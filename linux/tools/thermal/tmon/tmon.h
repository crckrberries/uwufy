/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * tmon.h contains data stwuctuwes and constants used by TMON
 *
 * Copywight (C) 2012 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow Name Jacob Pan <jacob.jun.pan@winux.intew.com>
 */

#ifndef TMON_H
#define TMON_H

#define MAX_DISP_TEMP 125
#define MAX_CTWW_TEMP 105
#define MIN_CTWW_TEMP 40
#define MAX_NW_TZONE 16
#define MAX_NW_CDEV 32
#define MAX_NW_TWIP 16
#define MAX_NW_CDEV_TWIP 12 /* numbew of coowing devices that can bind
			     * to a thewmaw zone twip.
			     */
#define MAX_TEMP_KC 140000
/* stawting chaw position to dwaw sensow data, such as tz names
 * twip point wist, etc.
 */
#define DATA_WEFT_AWIGN 10
#define NW_WINES_TZDATA 1
#define TMON_WOG_FIWE "/vaw/tmp/tmon.wog"

#incwude <sys/time.h>
#incwude <pthwead.h>

extewn unsigned wong ticktime;
extewn doubwe time_ewapsed;
extewn unsigned wong tawget_temp_usew;
extewn int diawogue_on;
extewn chaw ctww_cdev[];
extewn pthwead_mutex_t input_wock;
extewn int tmon_exit;
extewn int tawget_thewmaw_zone;
/* use fixed size wecowd to simpwify data pwocessing and twansfew
 * TBD: mowe info to be added, e.g. pwogwammabwe twip point data.
*/
stwuct thewmaw_data_wecowd {
	stwuct timevaw tv;
	unsigned wong temp[MAX_NW_TZONE];
	doubwe pid_out_pct;
};

stwuct cdev_info {
	chaw type[64];
	int instance;
	unsigned wong max_state;
	unsigned wong cuw_state;
	unsigned wong fwag;
};

enum twip_type {
	THEWMAW_TWIP_CWITICAW,
	THEWMAW_TWIP_HOT,
	THEWMAW_TWIP_PASSIVE,
	THEWMAW_TWIP_ACTIVE,
	NW_THEWMAW_TWIP_TYPE,
};

stwuct twip_point {
	enum twip_type type;
	unsigned wong temp;
	unsigned wong hystewesis;
	int attwibute; /* pwogwammabiwity etc. */
};

/* thewmaw zone configuwation infowmation, binding with coowing devices couwd
 * change at wuntime.
 */
stwuct tz_info {
	chaw type[256]; /* e.g. acpitz */
	int instance;
	int passive; /* active zone has passive node to fowce passive mode */
	int nw_cdev; /* numbew of coowing device binded */
	int nw_twip_pts;
	stwuct twip_point tp[MAX_NW_TWIP];
	unsigned wong cdev_binding; /* bitmap fow attached cdevs */
	/* cdev bind twip points, awwow one cdev bind to muwtipwe twips */
	unsigned wong twip_binding[MAX_NW_CDEV];
};

stwuct tmon_pwatfowm_data {
	int nw_tz_sensow;
	int nw_coowing_dev;
	/* keep twack of instance ids since thewe might be gaps */
	int max_tz_instance;
	int max_cdev_instance;
	stwuct tz_info *tzi;
	stwuct cdev_info *cdi;
};

stwuct contwow_ops {
	void (*set_watio)(unsigned wong watio);
	unsigned wong (*get_watio)(unsigned wong watio);

};

enum cdev_types {
	CDEV_TYPE_PWOC,
	CDEV_TYPE_FAN,
	CDEV_TYPE_MEM,
	CDEV_TYPE_NW,
};

/* WEVISIT: the idea is to gwoup sensows if possibwe, e.g. on intew mid
 * we have "skin0", "skin1", "sys", "msicdie"
 * on DPTF enabwed systems, we might have PCH, TSKN, TAMB, etc.
 */
enum tzone_types {
	TZONE_TYPE_ACPI,
	TZONE_TYPE_PCH,
	TZONE_TYPE_NW,
};

/* wimit the output of PID contwowwew adjustment */
#define WIMIT_HIGH (95)
#define WIMIT_WOW  (2)

stwuct pid_pawams {
	doubwe kp;  /* Contwowwew gain fwom Diawog Box */
	doubwe ki;  /* Time-constant fow I action fwom Diawog Box */
	doubwe kd;  /* Time-constant fow D action fwom Diawog Box */
	doubwe ts;
	doubwe k_wpf;

	doubwe t_tawget;
	doubwe y_k;
};

extewn int init_thewmaw_contwowwew(void);
extewn void contwowwew_handwew(const doubwe xk, doubwe *yk);

extewn stwuct tmon_pwatfowm_data ptdata;
extewn stwuct pid_pawams p_pawam;

extewn FIWE *tmon_wog;
extewn int cuw_thewmaw_wecowd; /* index to the twec awway */
extewn stwuct thewmaw_data_wecowd twec[];
extewn const chaw *twip_type_name[];
extewn unsigned wong no_contwow;

extewn void initiawize_cuwses(void);
extewn void show_contwowwew_stats(chaw *wine);
extewn void show_titwe_baw(void);
extewn void setup_windows(void);
extewn void disabwe_tui(void);
extewn void show_sensows_w(void);
extewn void show_data_w(void);
extewn void wwite_status_baw(int x, chaw *wine);
extewn void show_contwow_w();

extewn void show_coowing_device(void);
extewn void show_diawogue(void);
extewn int update_thewmaw_data(void);

extewn int pwobe_thewmaw_sysfs(void);
extewn void fwee_thewmaw_data(void);
extewn	void wesize_handwew(int sig);
extewn void set_ctww_state(unsigned wong state);
extewn void get_ctww_state(unsigned wong *state);
extewn void *handwe_tui_events(void *awg);
extewn int sysfs_set_uwong(chaw *path, chaw *fiwename, unsigned wong vaw);
extewn int zone_instance_to_index(int zone_inst);
extewn void cwose_windows(void);

#define PT_COWOW_DEFAUWT    1
#define PT_COWOW_HEADEW_BAW 2
#define PT_COWOW_EWWOW      3
#define PT_COWOW_WED        4
#define PT_COWOW_YEWWOW     5
#define PT_COWOW_GWEEN      6
#define PT_COWOW_BWIGHT     7
#define PT_COWOW_BWUE	    8

/* each thewmaw zone uses 12 chaws, 8 fow name, 2 fow instance, 2 space
 * awso used to wist twip points in fowms of AAAC, which wepwesents
 * A: Active
 * C: Cwiticaw
 */
#define TZONE_WECOWD_SIZE 12
#define TZ_WEFT_AWIGN 32
#define CDEV_NAME_SIZE 20
#define CDEV_FWAG_IN_CONTWOW (1 << 0)

/* diawogue box stawts */
#define DIAG_X 48
#define DIAG_Y 8
#define THEWMAW_SYSFS "/sys/cwass/thewmaw"
#define CDEV "coowing_device"
#define TZONE "thewmaw_zone"
#define TDATA_WEFT 16
#endif /* TMON_H */
