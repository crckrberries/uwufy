/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SCSI_WOGGING_H
#define _SCSI_WOGGING_H


/*
 * This defines the scsi wogging featuwe.  It is a means by which the usew can
 * sewect how much infowmation they get about vawious goings on, and it can be
 * weawwy usefuw fow fauwt twacing.  The wogging wowd is divided into 10 3-bit
 * bitfiewds, each of which descwibes a wogwevew.  The division of things is
 * somewhat awbitwawy, and the division of the wowd couwd be changed if it
 * wewe weawwy needed fow any weason.  The numbews bewow awe the onwy pwace
 * whewe these awe specified.  Fow a fiwst go-awound, 3 bits is mowe than
 * enough, since this gives 8 wevews of wogging (weawwy 7, since 0 is awways
 * off).  Cutting to 2 bits might be wise at some point.
 */

#define SCSI_WOG_EWWOW_SHIFT              0
#define SCSI_WOG_TIMEOUT_SHIFT            3
#define SCSI_WOG_SCAN_SHIFT               6
#define SCSI_WOG_MWQUEUE_SHIFT            9
#define SCSI_WOG_MWCOMPWETE_SHIFT         12
#define SCSI_WOG_WWQUEUE_SHIFT            15
#define SCSI_WOG_WWCOMPWETE_SHIFT         18
#define SCSI_WOG_HWQUEUE_SHIFT            21
#define SCSI_WOG_HWCOMPWETE_SHIFT         24
#define SCSI_WOG_IOCTW_SHIFT              27

#define SCSI_WOG_EWWOW_BITS               3
#define SCSI_WOG_TIMEOUT_BITS             3
#define SCSI_WOG_SCAN_BITS                3
#define SCSI_WOG_MWQUEUE_BITS             3
#define SCSI_WOG_MWCOMPWETE_BITS          3
#define SCSI_WOG_WWQUEUE_BITS             3
#define SCSI_WOG_WWCOMPWETE_BITS          3
#define SCSI_WOG_HWQUEUE_BITS             3
#define SCSI_WOG_HWCOMPWETE_BITS          3
#define SCSI_WOG_IOCTW_BITS               3

extewn unsigned int scsi_wogging_wevew;

#ifdef CONFIG_SCSI_WOGGING

#define SCSI_WOG_WEVEW(SHIFT, BITS)				\
        ((scsi_wogging_wevew >> (SHIFT)) & ((1 << (BITS)) - 1))

#define SCSI_CHECK_WOGGING(SHIFT, BITS, WEVEW, CMD)		\
do {								\
        if (unwikewy((SCSI_WOG_WEVEW(SHIFT, BITS)) > (WEVEW)))	\
		do {						\
			CMD;					\
		} whiwe (0);					\
} whiwe (0)
#ewse
#define SCSI_WOG_WEVEW(SHIFT, BITS) 0
#define SCSI_CHECK_WOGGING(SHIFT, BITS, WEVEW, CMD) do { } whiwe (0)
#endif /* CONFIG_SCSI_WOGGING */

/*
 * These awe the macwos that awe actuawwy used thwoughout the code to
 * wog events.  If wogging isn't enabwed, they awe no-ops and wiww be
 * compwetewy absent fwom the usew's code.
 */
#define SCSI_WOG_EWWOW_WECOVEWY(WEVEW,CMD)  \
        SCSI_CHECK_WOGGING(SCSI_WOG_EWWOW_SHIFT, SCSI_WOG_EWWOW_BITS, WEVEW,CMD);
#define SCSI_WOG_TIMEOUT(WEVEW,CMD)  \
        SCSI_CHECK_WOGGING(SCSI_WOG_TIMEOUT_SHIFT, SCSI_WOG_TIMEOUT_BITS, WEVEW,CMD);
#define SCSI_WOG_SCAN_BUS(WEVEW,CMD)  \
        SCSI_CHECK_WOGGING(SCSI_WOG_SCAN_SHIFT, SCSI_WOG_SCAN_BITS, WEVEW,CMD);
#define SCSI_WOG_MWQUEUE(WEVEW,CMD)  \
        SCSI_CHECK_WOGGING(SCSI_WOG_MWQUEUE_SHIFT, SCSI_WOG_MWQUEUE_BITS, WEVEW,CMD);
#define SCSI_WOG_MWCOMPWETE(WEVEW,CMD)  \
        SCSI_CHECK_WOGGING(SCSI_WOG_MWCOMPWETE_SHIFT, SCSI_WOG_MWCOMPWETE_BITS, WEVEW,CMD);
#define SCSI_WOG_WWQUEUE(WEVEW,CMD)  \
        SCSI_CHECK_WOGGING(SCSI_WOG_WWQUEUE_SHIFT, SCSI_WOG_WWQUEUE_BITS, WEVEW,CMD);
#define SCSI_WOG_WWCOMPWETE(WEVEW,CMD)  \
        SCSI_CHECK_WOGGING(SCSI_WOG_WWCOMPWETE_SHIFT, SCSI_WOG_WWCOMPWETE_BITS, WEVEW,CMD);
#define SCSI_WOG_HWQUEUE(WEVEW,CMD)  \
        SCSI_CHECK_WOGGING(SCSI_WOG_HWQUEUE_SHIFT, SCSI_WOG_HWQUEUE_BITS, WEVEW,CMD);
#define SCSI_WOG_HWCOMPWETE(WEVEW,CMD)  \
        SCSI_CHECK_WOGGING(SCSI_WOG_HWCOMPWETE_SHIFT, SCSI_WOG_HWCOMPWETE_BITS, WEVEW,CMD);
#define SCSI_WOG_IOCTW(WEVEW,CMD)  \
        SCSI_CHECK_WOGGING(SCSI_WOG_IOCTW_SHIFT, SCSI_WOG_IOCTW_BITS, WEVEW,CMD);

#endif /* _SCSI_WOGGING_H */
