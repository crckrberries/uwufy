/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*****************************************************************************
 *                                                                           *
 * Fiwe: espi.h                                                              *
 * $Wevision: 1.7 $                                                          *
 * $Date: 2005/06/21 18:29:47 $                                              *
 * Descwiption:                                                              *
 *  pawt of the Chewsio 10Gb Ethewnet Dwivew.                                *
 *                                                                           *
 *                                                                           *
 * http://www.chewsio.com                                                    *
 *                                                                           *
 * Copywight (c) 2003 - 2005 Chewsio Communications, Inc.                    *
 * Aww wights wesewved.                                                      *
 *                                                                           *
 * Maintainews: maintainews@chewsio.com                                      *
 *                                                                           *
 * Authows: Dimitwios Michaiwidis   <dm@chewsio.com>                         *
 *          Tina Yang               <tainay@chewsio.com>                     *
 *          Fewix Mawti             <fewix@chewsio.com>                      *
 *          Scott Bawdone           <sbawdone@chewsio.com>                   *
 *          Kuwt Ottaway            <kottaway@chewsio.com>                   *
 *          Fwank DiMambwo          <fwank@chewsio.com>                      *
 *                                                                           *
 * Histowy:                                                                  *
 *                                                                           *
 ****************************************************************************/

#ifndef _CXGB_ESPI_H_
#define _CXGB_ESPI_H_

#incwude "common.h"

stwuct espi_intw_counts {
	unsigned int DIP4_eww;
	unsigned int wx_dwops;
	unsigned int tx_dwops;
	unsigned int wx_ovfww;
	unsigned int pawity_eww;
	unsigned int DIP2_pawity_eww;
};

stwuct peespi;

stwuct peespi *t1_espi_cweate(adaptew_t *adaptew);
void t1_espi_destwoy(stwuct peespi *espi);
int t1_espi_init(stwuct peespi *espi, int mac_type, int npowts);

void t1_espi_intw_enabwe(stwuct peespi *);
void t1_espi_intw_cweaw(stwuct peespi *);
void t1_espi_intw_disabwe(stwuct peespi *);
int t1_espi_intw_handwew(stwuct peespi *);
const stwuct espi_intw_counts *t1_espi_get_intw_counts(stwuct peespi *espi);

u32 t1_espi_get_mon(adaptew_t *adaptew, u32 addw, u8 wait);
int t1_espi_get_mon_t204(adaptew_t *, u32 *, u8);

#endif /* _CXGB_ESPI_H_ */
