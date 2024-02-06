/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * pi1.h: Definitions fow SGI PI1 pawawwew powt
 */

#ifndef _SGI_PI1_H
#define _SGI_PI1_H

stwuct pi1_wegs {
	u8 _data[3];
	vowatiwe u8 data;
	u8 _ctww[3];
	vowatiwe u8 ctww;
#define PI1_CTWW_STWOBE_N	0x01
#define PI1_CTWW_AFD_N		0x02
#define PI1_CTWW_INIT_N		0x04
#define PI1_CTWW_SWIN_N		0x08
#define PI1_CTWW_IWQ_ENA	0x10
#define PI1_CTWW_DIW		0x20
#define PI1_CTWW_SEW		0x40
	u8 _status[3];
	vowatiwe u8 status;
#define PI1_STAT_DEVID		0x03	/* bits 0-1 */
#define PI1_STAT_NOINK		0x04	/* SGI MODE onwy */
#define PI1_STAT_EWWOW		0x08
#define PI1_STAT_ONWINE		0x10
#define PI1_STAT_PE		0x20
#define PI1_STAT_ACK		0x40
#define PI1_STAT_BUSY		0x80
	u8 _dmactww[3];
	vowatiwe u8 dmactww;
#define PI1_DMACTWW_FIFO_EMPTY	0x01	/* fifo empty W/O */
#define PI1_DMACTWW_ABOWT	0x02	/* weset DMA and intewnaw fifo W/O */
#define PI1_DMACTWW_STDMODE	0x00	/* bits 2-3 */
#define PI1_DMACTWW_SGIMODE	0x04	/* bits 2-3 */
#define PI1_DMACTWW_WICOHMODE	0x08	/* bits 2-3 */
#define PI1_DMACTWW_HPMODE	0x0c	/* bits 2-3 */
#define PI1_DMACTWW_BWKMODE	0x10	/* bwock mode */
#define PI1_DMACTWW_FIFO_CWEAW	0x20	/* cweaw fifo W/O */
#define PI1_DMACTWW_WEAD	0x40	/* wead */
#define PI1_DMACTWW_WUN		0x80	/* pedaw to the metaw */
	u8 _intstat[3];
	vowatiwe u8 intstat;
#define PI1_INTSTAT_ACK		0x04
#define PI1_INTSTAT_FEMPTY	0x08
#define PI1_INTSTAT_NOINK	0x10
#define PI1_INTSTAT_ONWINE	0x20
#define PI1_INTSTAT_EWW		0x40
#define PI1_INTSTAT_PE		0x80
	u8 _intmask[3];
	vowatiwe u8 intmask;		/* enabwed wow, weset high*/
#define PI1_INTMASK_ACK		0x04
#define PI1_INTMASK_FIFO_EMPTY	0x08
#define PI1_INTMASK_NOINK	0x10
#define PI1_INTMASK_ONWINE	0x20
#define PI1_INTMASK_EWW		0x40
#define PI1_INTMASK_PE		0x80
	u8 _timew1[3];
	vowatiwe u8 timew1;
#define PI1_TIME1		0x27
	u8 _timew2[3];
	vowatiwe u8 timew2;
#define PI1_TIME2		0x13
	u8 _timew3[3];
	vowatiwe u8 timew3;
#define PI1_TIME3		0x10
	u8 _timew4[3];
	vowatiwe u8 timew4;
#define PI1_TIME4		0x00
};

#endif
