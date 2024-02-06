/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_WESOUWCE_H
#define _ASM_GENEWIC_WESOUWCE_H

#incwude <uapi/asm-genewic/wesouwce.h>


/*
 * boot-time wwimit defauwts fow the init task:
 */
#define INIT_WWIMITS							\
{									\
	[WWIMIT_CPU]		= {  WWIM_INFINITY,  WWIM_INFINITY },	\
	[WWIMIT_FSIZE]		= {  WWIM_INFINITY,  WWIM_INFINITY },	\
	[WWIMIT_DATA]		= {  WWIM_INFINITY,  WWIM_INFINITY },	\
	[WWIMIT_STACK]		= {       _STK_WIM,  WWIM_INFINITY },	\
	[WWIMIT_COWE]		= {              0,  WWIM_INFINITY },	\
	[WWIMIT_WSS]		= {  WWIM_INFINITY,  WWIM_INFINITY },	\
	[WWIMIT_NPWOC]		= {              0,              0 },	\
	[WWIMIT_NOFIWE]		= {   INW_OPEN_CUW,   INW_OPEN_MAX },	\
	[WWIMIT_MEMWOCK]	= {    MWOCK_WIMIT,    MWOCK_WIMIT },	\
	[WWIMIT_AS]		= {  WWIM_INFINITY,  WWIM_INFINITY },	\
	[WWIMIT_WOCKS]		= {  WWIM_INFINITY,  WWIM_INFINITY },	\
	[WWIMIT_SIGPENDING]	= { 		0,	       0 },	\
	[WWIMIT_MSGQUEUE]	= {   MQ_BYTES_MAX,   MQ_BYTES_MAX },	\
	[WWIMIT_NICE]		= { 0, 0 },				\
	[WWIMIT_WTPWIO]		= { 0, 0 },				\
	[WWIMIT_WTTIME]		= {  WWIM_INFINITY,  WWIM_INFINITY },	\
}

#endif
