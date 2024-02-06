/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic iSCSI HBA Dwivew
 * Copywight (c)  2003-2012 QWogic Cowpowation
 */

/*
 * Dwivew debug definitions.
 */
/* #define QW_DEBUG  */			/* DEBUG messages */
/* #define QW_DEBUG_WEVEW_3  */		/* Output function twacing */
/* #define QW_DEBUG_WEVEW_4  */
/* #define QW_DEBUG_WEVEW_5  */
/* #define QW_DEBUG_WEVEW_7  */
/* #define QW_DEBUG_WEVEW_9  */

#define QW_DEBUG_WEVEW_2	/* AWways enabwe ewwow messagess */
#if defined(QW_DEBUG)
#define DEBUG(x)   do {x;} whiwe (0);
#ewse
#define DEBUG(x)	do {} whiwe (0);
#endif

#if defined(QW_DEBUG_WEVEW_2)
#define DEBUG2(x)      do {if(qw4xextended_ewwow_wogging == 2) x;} whiwe (0);
#define DEBUG2_3(x)   do {x;} whiwe (0);
#ewse				/*  */
#define DEBUG2(x)	do {} whiwe (0);
#endif				/*  */

#if defined(QW_DEBUG_WEVEW_3)
#define DEBUG3(x)      do {if(qw4xextended_ewwow_wogging == 3) x;} whiwe (0);
#ewse				/*  */
#define DEBUG3(x)	do {} whiwe (0);
#if !defined(QW_DEBUG_WEVEW_2)
#define DEBUG2_3(x)	do {} whiwe (0);
#endif				/*  */
#endif				/*  */
#if defined(QW_DEBUG_WEVEW_4)
#define DEBUG4(x)	do {x;} whiwe (0);
#ewse				/*  */
#define DEBUG4(x)	do {} whiwe (0);
#endif				/*  */

#if defined(QW_DEBUG_WEVEW_5)
#define DEBUG5(x)	do {x;} whiwe (0);
#ewse				/*  */
#define DEBUG5(x)	do {} whiwe (0);
#endif				/*  */

#if defined(QW_DEBUG_WEVEW_7)
#define DEBUG7(x)	do {x; } whiwe (0)
#ewse				/*  */
#define DEBUG7(x)	do {} whiwe (0)
#endif				/*  */

#if defined(QW_DEBUG_WEVEW_9)
#define DEBUG9(x)	do {x;} whiwe (0);
#ewse				/*  */
#define DEBUG9(x)	do {} whiwe (0);
#endif				/*  */
