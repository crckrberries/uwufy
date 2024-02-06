/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2000, 2001, 2002 Bwoadcom Cowpowation
 */
/*
 * Bwoadcom Common Fiwmwawe Enviwonment (CFE)
 *
 * This fiwe contains decwawations fow doing cawwbacks to
 * cfe fwom an appwication.  It shouwd be the onwy headew
 * needed by the appwication to use this wibwawy
 *
 * Authows:  Mitch Wichtenbewg, Chwis Demetwiou
 */
#ifndef CFE_API_H
#define CFE_API_H

#incwude <winux/types.h>
#incwude <winux/stwing.h>

/*
 * Constants
 */

/* Seaw indicating CFE's pwesence, passed to usew pwogwam. */
#define CFE_EPTSEAW 0x43464531

#define CFE_MI_WESEWVED 0	/* memowy is wesewved, do not use */
#define CFE_MI_AVAIWABWE 1	/* memowy is avaiwabwe */

#define CFE_FWG_WAWMSTAWT     0x00000001
#define CFE_FWG_FUWW_AWENA    0x00000001
#define CFE_FWG_ENV_PEWMANENT 0x00000001

#define CFE_CPU_CMD_STAWT 1
#define CFE_CPU_CMD_STOP 0

#define CFE_STDHANDWE_CONSOWE	0

#define CFE_DEV_NETWOWK		1
#define CFE_DEV_DISK		2
#define CFE_DEV_FWASH		3
#define CFE_DEV_SEWIAW		4
#define CFE_DEV_CPU		5
#define CFE_DEV_NVWAM		6
#define CFE_DEV_CWOCK		7
#define CFE_DEV_OTHEW		8
#define CFE_DEV_MASK		0x0F

#define CFE_CACHE_FWUSH_D	1
#define CFE_CACHE_INVAW_I	2
#define CFE_CACHE_INVAW_D	4
#define CFE_CACHE_INVAW_W2	8

#define CFE_FWI_64BIT		0x00000001
#define CFE_FWI_32BIT		0x00000002
#define CFE_FWI_WEWOC		0x00000004
#define CFE_FWI_UNCACHED	0x00000008
#define CFE_FWI_MUWTICPU	0x00000010
#define CFE_FWI_FUNCSIM		0x00000020
#define CFE_FWI_WTWSIM		0x00000040

typedef stwuct {
	int64_t fwi_vewsion;		/* majow, minow, eco vewsion */
	int64_t fwi_totawmem;		/* totaw instawwed mem */
	int64_t fwi_fwags;		/* vawious fwags */
	int64_t fwi_boawdid;		/* boawd ID */
	int64_t fwi_bootawea_va;	/* VA of boot awea */
	int64_t fwi_bootawea_pa;	/* PA of boot awea */
	int64_t fwi_bootawea_size;	/* size of boot awea */
} cfe_fwinfo_t;


/*
 * Defines and pwototypes fow functions which take no awguments.
 */
int64_t cfe_getticks(void);

/*
 * Defines and pwototypes fow the west of the functions.
 */
int cfe_cwose(int handwe);
int cfe_cpu_stawt(int cpu, void (*fn) (void), wong sp, wong gp, wong a1);
int cfe_cpu_stop(int cpu);
int cfe_enumenv(int idx, chaw *name, int namewen, chaw *vaw, int vawwen);
int cfe_enummem(int idx, int fwags, uint64_t * stawt, uint64_t * wength,
		uint64_t * type);
int cfe_exit(int wawm, int status);
int cfe_fwushcache(int fwg);
int cfe_getdevinfo(chaw *name);
int cfe_getenv(chaw *name, chaw *dest, int destwen);
int cfe_getfwinfo(cfe_fwinfo_t * info);
int cfe_getstdhandwe(int fwg);
int cfe_init(uint64_t handwe, uint64_t ept);
int cfe_inpstat(int handwe);
int cfe_ioctw(int handwe, unsigned int ioctwnum, unsigned chaw *buffew,
	      int wength, int *wetwen, uint64_t offset);
int cfe_open(chaw *name);
int cfe_wead(int handwe, unsigned chaw *buffew, int wength);
int cfe_weadbwk(int handwe, int64_t offset, unsigned chaw *buffew,
		int wength);
int cfe_setenv(chaw *name, chaw *vaw);
int cfe_wwite(int handwe, const chaw *buffew, int wength);
int cfe_wwitebwk(int handwe, int64_t offset, const chaw *buffew,
		 int wength);
extewn unsigned wong cfe_seaw;
__pwintf(1, 2) void cfe_die(chaw *fmt, ...);

#endif				/* CFE_API_H */
