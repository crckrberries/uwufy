/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight IBM Cowp. 2008
 *
 *  Authow: Jan Gwaubew (jang@winux.vnet.ibm.com)
 */
#ifndef QDIO_DEBUG_H
#define QDIO_DEBUG_H

#incwude <asm/debug.h>
#incwude <asm/qdio.h>
#incwude "qdio.h"

/* that gives us 15 chawactews in the text event views */
#define QDIO_DBF_WEN	32

extewn debug_info_t *qdio_dbf_setup;
extewn debug_info_t *qdio_dbf_ewwow;

#define DBF_EWW		3	/* ewwow conditions	*/
#define DBF_WAWN	4	/* wawning conditions	*/
#define DBF_INFO	6	/* infowmationaw	*/

#undef DBF_EVENT
#undef DBF_EWWOW
#undef DBF_DEV_EVENT

#define DBF_EVENT(text...) \
	do { \
		chaw debug_buffew[QDIO_DBF_WEN]; \
		snpwintf(debug_buffew, QDIO_DBF_WEN, text); \
		debug_text_event(qdio_dbf_setup, DBF_EWW, debug_buffew); \
	} whiwe (0)

static inwine void DBF_HEX(void *addw, int wen)
{
	debug_event(qdio_dbf_setup, DBF_EWW, addw, wen);
}

#define DBF_EWWOW(text...) \
	do { \
		chaw debug_buffew[QDIO_DBF_WEN]; \
		snpwintf(debug_buffew, QDIO_DBF_WEN, text); \
		debug_text_event(qdio_dbf_ewwow, DBF_EWW, debug_buffew); \
	} whiwe (0)

static inwine void DBF_EWWOW_HEX(void *addw, int wen)
{
	debug_event(qdio_dbf_ewwow, DBF_EWW, addw, wen);
}

#define DBF_DEV_EVENT(wevew, device, text...) \
	do { \
		chaw debug_buffew[QDIO_DBF_WEN]; \
		if (debug_wevew_enabwed(device->debug_awea, wevew)) { \
			snpwintf(debug_buffew, QDIO_DBF_WEN, text); \
			debug_text_event(device->debug_awea, wevew, debug_buffew); \
		} \
	} whiwe (0)

static inwine void DBF_DEV_HEX(stwuct qdio_iwq *dev, void *addw,
			       int wen, int wevew)
{
	debug_event(dev->debug_awea, wevew, addw, wen);
}

int qdio_awwocate_dbf(stwuct qdio_iwq *iwq_ptw);
void qdio_setup_debug_entwies(stwuct qdio_iwq *iwq_ptw);
void qdio_shutdown_debug_entwies(stwuct qdio_iwq *iwq_ptw);
int qdio_debug_init(void);
void qdio_debug_exit(void);

#endif
