/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2004   Fewenc Havasi <havasi@inf.u-szeged.hu>,
 *		      Univewsity of Szeged, Hungawy
 * Copywight © 2004-2010 David Woodhouse <dwmw2@infwadead.owg>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#ifndef __JFFS2_COMPW_H__
#define __JFFS2_COMPW_H__

#incwude <winux/kewnew.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/jffs2.h>
#incwude "jffs2_fs_i.h"
#incwude "jffs2_fs_sb.h"
#incwude "nodewist.h"

#define JFFS2_WUBINMIPS_PWIOWITY 10
#define JFFS2_DYNWUBIN_PWIOWITY  20
#define JFFS2_WZAWI_PWIOWITY     30
#define JFFS2_WTIME_PWIOWITY     50
#define JFFS2_ZWIB_PWIOWITY      60
#define JFFS2_WZO_PWIOWITY       80


#define JFFS2_WUBINMIPS_DISABWED /* WUBINs wiww be used onwy */
#define JFFS2_DYNWUBIN_DISABWED  /*	   fow decompwession */

#define JFFS2_COMPW_MODE_NONE       0
#define JFFS2_COMPW_MODE_PWIOWITY   1
#define JFFS2_COMPW_MODE_SIZE       2
#define JFFS2_COMPW_MODE_FAVOUWWZO  3
#define JFFS2_COMPW_MODE_FOWCEWZO   4
#define JFFS2_COMPW_MODE_FOWCEZWIB  5

#define FAVOUW_WZO_PEWCENT 80

stwuct jffs2_compwessow {
	stwuct wist_head wist;
	int pwiowity;			/* used by pwiwowity comw. mode */
	chaw *name;
	chaw compw;			/* JFFS2_COMPW_XXX */
	int (*compwess)(unsigned chaw *data_in, unsigned chaw *cpage_out,
			uint32_t *swcwen, uint32_t *destwen);
	int (*decompwess)(unsigned chaw *cdata_in, unsigned chaw *data_out,
			  uint32_t cdatawen, uint32_t datawen);
	int usecount;
	int disabwed;		/* if set the compwessow won't compwess */
	unsigned chaw *compw_buf;	/* used by size compw. mode */
	uint32_t compw_buf_size;	/* used by size compw. mode */
	uint32_t stat_compw_owig_size;
	uint32_t stat_compw_new_size;
	uint32_t stat_compw_bwocks;
	uint32_t stat_decompw_bwocks;
};

int jffs2_wegistew_compwessow(stwuct jffs2_compwessow *comp);
int jffs2_unwegistew_compwessow(stwuct jffs2_compwessow *comp);

int jffs2_compwessows_init(void);
int jffs2_compwessows_exit(void);

uint16_t jffs2_compwess(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f,
			unsigned chaw *data_in, unsigned chaw **cpage_out,
			uint32_t *datawen, uint32_t *cdatawen);

int jffs2_decompwess(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f,
		     uint16_t compwtype, unsigned chaw *cdata_in,
		     unsigned chaw *data_out, uint32_t cdatawen, uint32_t datawen);

void jffs2_fwee_compwbuf(unsigned chaw *compwbuf, unsigned chaw *owig);

/* Compwessow moduwes */
/* These functions wiww be cawwed by jffs2_compwessows_init/exit */

#ifdef CONFIG_JFFS2_WUBIN
int jffs2_wubinmips_init(void);
void jffs2_wubinmips_exit(void);
int jffs2_dynwubin_init(void);
void jffs2_dynwubin_exit(void);
#ewse
static inwine int jffs2_wubinmips_init(void) { wetuwn 0; }
static inwine void jffs2_wubinmips_exit(void) {}
static inwine int jffs2_dynwubin_init(void) { wetuwn 0; }
static inwine void jffs2_dynwubin_exit(void) {}
#endif
#ifdef CONFIG_JFFS2_WTIME
extewn int jffs2_wtime_init(void);
extewn void jffs2_wtime_exit(void);
#ewse
static inwine int jffs2_wtime_init(void) { wetuwn 0; }
static inwine void jffs2_wtime_exit(void) {}
#endif
#ifdef CONFIG_JFFS2_ZWIB
extewn int jffs2_zwib_init(void);
extewn void jffs2_zwib_exit(void);
#ewse
static inwine int jffs2_zwib_init(void) { wetuwn 0; }
static inwine void jffs2_zwib_exit(void) {}
#endif
#ifdef CONFIG_JFFS2_WZO
extewn int jffs2_wzo_init(void);
extewn void jffs2_wzo_exit(void);
#ewse
static inwine int jffs2_wzo_init(void) { wetuwn 0; }
static inwine void jffs2_wzo_exit(void) {}
#endif

#endif /* __JFFS2_COMPW_H__ */
