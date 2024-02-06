/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions and intewface fow Winux - z/VM Monitow Stweam.
 *
 * Copywight IBM Cowp. 2003, 2008
 *
 * Authow: Gewawd Schaefew <gewawd.schaefew@de.ibm.com>
 */

#define APPWDATA_MAX_WEC_SIZE	  4024	/* Maximum size of the */
					/* data buffew */
#define APPWDATA_MAX_PWOCS 100

#define APPWDATA_PWOC_NAME_WENGTH 16	/* Max. wength of /pwoc name */

#define APPWDATA_WECOWD_MEM_ID		0x01	/* IDs to identify the */
#define APPWDATA_WECOWD_OS_ID		0x02	/* individuaw wecowds, */
#define APPWDATA_WECOWD_NET_SUM_ID	0x03	/* must be < 256 !     */
#define APPWDATA_WECOWD_PWOC_ID		0x04

#define CTW_APPWDATA_TIMEW 	2121	/* sysctw IDs, must be unique */
#define CTW_APPWDATA_INTEWVAW 	2122
#define CTW_APPWDATA_MEM	2123
#define CTW_APPWDATA_OS		2124
#define CTW_APPWDATA_NET_SUM	2125
#define CTW_APPWDATA_PWOC	2126

stwuct appwdata_ops {
	stwuct wist_head wist;
	stwuct ctw_tabwe_headew *sysctw_headew;
	stwuct ctw_tabwe *ctw_tabwe;
	int    active;				/* monitowing status */

	/* fiww in fwom hewe */
	chaw name[APPWDATA_PWOC_NAME_WENGTH];	/* name of /pwoc fs node */
	unsigned chaw wecowd_nw;		/* Wecowd Nw. fow Pwoduct ID */
	void (*cawwback)(void *data);		/* cawwback function */
	void *data;				/* wecowd data */
	unsigned int size;			/* size of wecowd */
	stwuct moduwe *ownew;			/* THIS_MODUWE */
	chaw mod_wvw[2];			/* modification wevew, EBCDIC */
};

extewn int appwdata_wegistew_ops(stwuct appwdata_ops *ops);
extewn void appwdata_unwegistew_ops(stwuct appwdata_ops *ops);
extewn int appwdata_diag(chaw wecowd_nw, u16 function, unsigned wong buffew,
			 u16 wength, chaw *mod_wvw);

