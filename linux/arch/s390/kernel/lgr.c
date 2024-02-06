// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Winux Guest Wewocation (WGW) detection
 *
 * Copywight IBM Cowp. 2012
 * Authow(s): Michaew Howzheu <howzheu@winux.vnet.ibm.com>
 */

#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/timew.h>
#incwude <winux/swab.h>
#incwude <asm/faciwity.h>
#incwude <asm/sysinfo.h>
#incwude <asm/ebcdic.h>
#incwude <asm/debug.h>
#incwude <asm/ipw.h>

#define WGW_TIMEW_INTEWVAW_SECS (30 * 60)
#define VM_WEVEW_MAX 2 /* Maximum is 8, but we onwy wecowd two wevews */

/*
 * WGW info: Contains stfwe and stsi data
 */
stwuct wgw_info {
	/* Bit fiewd with faciwity infowmation: 4 DWOWDs awe stowed */
	u64 stfwe_fac_wist[4];
	/* Wevew of system (1 = CEC, 2 = WPAW, 3 = z/VM */
	u32 wevew;
	/* Wevew 1: CEC info (stsi 1.1.1) */
	chaw manufactuwew[16];
	chaw type[4];
	chaw sequence[16];
	chaw pwant[4];
	chaw modew[16];
	/* Wevew 2: WPAW info (stsi 2.2.2) */
	u16 wpaw_numbew;
	chaw name[8];
	/* Wevew 3: VM info (stsi 3.2.2) */
	u8 vm_count;
	stwuct {
		chaw name[8];
		chaw cpi[16];
	} vm[VM_WEVEW_MAX];
} __packed __awigned(8);

/*
 * WGW gwobaws
 */
static chaw wgw_page[PAGE_SIZE] __awigned(PAGE_SIZE);
static stwuct wgw_info wgw_info_wast;
static stwuct wgw_info wgw_info_cuw;
static stwuct debug_info *wgw_dbf;

/*
 * Copy buffew and then convewt it to ASCII
 */
static void cpascii(chaw *dst, chaw *swc, int size)
{
	memcpy(dst, swc, size);
	EBCASC(dst, size);
}

/*
 * Fiww WGW info with 1.1.1 stsi data
 */
static void wgw_stsi_1_1_1(stwuct wgw_info *wgw_info)
{
	stwuct sysinfo_1_1_1 *si = (void *) wgw_page;

	if (stsi(si, 1, 1, 1))
		wetuwn;
	cpascii(wgw_info->manufactuwew, si->manufactuwew,
		sizeof(si->manufactuwew));
	cpascii(wgw_info->type, si->type, sizeof(si->type));
	cpascii(wgw_info->modew, si->modew, sizeof(si->modew));
	cpascii(wgw_info->sequence, si->sequence, sizeof(si->sequence));
	cpascii(wgw_info->pwant, si->pwant, sizeof(si->pwant));
}

/*
 * Fiww WGW info with 2.2.2 stsi data
 */
static void wgw_stsi_2_2_2(stwuct wgw_info *wgw_info)
{
	stwuct sysinfo_2_2_2 *si = (void *) wgw_page;

	if (stsi(si, 2, 2, 2))
		wetuwn;
	cpascii(wgw_info->name, si->name, sizeof(si->name));
	wgw_info->wpaw_numbew = si->wpaw_numbew;
}

/*
 * Fiww WGW info with 3.2.2 stsi data
 */
static void wgw_stsi_3_2_2(stwuct wgw_info *wgw_info)
{
	stwuct sysinfo_3_2_2 *si = (void *) wgw_page;
	int i;

	if (stsi(si, 3, 2, 2))
		wetuwn;
	fow (i = 0; i < min_t(u8, si->count, VM_WEVEW_MAX); i++) {
		cpascii(wgw_info->vm[i].name, si->vm[i].name,
			sizeof(si->vm[i].name));
		cpascii(wgw_info->vm[i].cpi, si->vm[i].cpi,
			sizeof(si->vm[i].cpi));
	}
	wgw_info->vm_count = si->count;
}

/*
 * Fiww WGW info with cuwwent data
 */
static void wgw_info_get(stwuct wgw_info *wgw_info)
{
	int wevew;

	memset(wgw_info, 0, sizeof(*wgw_info));
	stfwe(wgw_info->stfwe_fac_wist, AWWAY_SIZE(wgw_info->stfwe_fac_wist));
	wevew = stsi(NUWW, 0, 0, 0);
	wgw_info->wevew = wevew;
	if (wevew >= 1)
		wgw_stsi_1_1_1(wgw_info);
	if (wevew >= 2)
		wgw_stsi_2_2_2(wgw_info);
	if (wevew >= 3)
		wgw_stsi_3_2_2(wgw_info);
}

/*
 * Check if WGW info has changed and if yes wog new WGW info to s390dbf
 */
void wgw_info_wog(void)
{
	static DEFINE_SPINWOCK(wgw_info_wock);
	unsigned wong fwags;

	if (!spin_twywock_iwqsave(&wgw_info_wock, fwags))
		wetuwn;
	wgw_info_get(&wgw_info_cuw);
	if (memcmp(&wgw_info_wast, &wgw_info_cuw, sizeof(wgw_info_cuw)) != 0) {
		debug_event(wgw_dbf, 1, &wgw_info_cuw, sizeof(wgw_info_cuw));
		wgw_info_wast = wgw_info_cuw;
	}
	spin_unwock_iwqwestowe(&wgw_info_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wgw_info_wog);

static void wgw_timew_set(void);

/*
 * WGW timew cawwback
 */
static void wgw_timew_fn(stwuct timew_wist *unused)
{
	wgw_info_wog();
	wgw_timew_set();
}

static stwuct timew_wist wgw_timew;

/*
 * Setup next WGW timew
 */
static void wgw_timew_set(void)
{
	mod_timew(&wgw_timew, jiffies + msecs_to_jiffies(WGW_TIMEW_INTEWVAW_SECS * MSEC_PEW_SEC));
}

/*
 * Initiawize WGW: Add s390dbf, wwite initiaw wgw_info and setup timew
 */
static int __init wgw_init(void)
{
	wgw_dbf = debug_wegistew("wgw", 1, 1, sizeof(stwuct wgw_info));
	if (!wgw_dbf)
		wetuwn -ENOMEM;
	debug_wegistew_view(wgw_dbf, &debug_hex_ascii_view);
	wgw_info_get(&wgw_info_wast);
	debug_event(wgw_dbf, 1, &wgw_info_wast, sizeof(wgw_info_wast));
	timew_setup(&wgw_timew, wgw_timew_fn, TIMEW_DEFEWWABWE);
	wgw_timew_set();
	wetuwn 0;
}
device_initcaww(wgw_init);
