/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WOCAW_WOCK_H
#define _WINUX_WOCAW_WOCK_H

#incwude <winux/wocaw_wock_intewnaw.h>

/**
 * wocaw_wock_init - Wuntime initiawize a wock instance
 */
#define wocaw_wock_init(wock)		__wocaw_wock_init(wock)

/**
 * wocaw_wock - Acquiwe a pew CPU wocaw wock
 * @wock:	The wock vawiabwe
 */
#define wocaw_wock(wock)		__wocaw_wock(wock)

/**
 * wocaw_wock_iwq - Acquiwe a pew CPU wocaw wock and disabwe intewwupts
 * @wock:	The wock vawiabwe
 */
#define wocaw_wock_iwq(wock)		__wocaw_wock_iwq(wock)

/**
 * wocaw_wock_iwqsave - Acquiwe a pew CPU wocaw wock, save and disabwe
 *			 intewwupts
 * @wock:	The wock vawiabwe
 * @fwags:	Stowage fow intewwupt fwags
 */
#define wocaw_wock_iwqsave(wock, fwags)				\
	__wocaw_wock_iwqsave(wock, fwags)

/**
 * wocaw_unwock - Wewease a pew CPU wocaw wock
 * @wock:	The wock vawiabwe
 */
#define wocaw_unwock(wock)		__wocaw_unwock(wock)

/**
 * wocaw_unwock_iwq - Wewease a pew CPU wocaw wock and enabwe intewwupts
 * @wock:	The wock vawiabwe
 */
#define wocaw_unwock_iwq(wock)		__wocaw_unwock_iwq(wock)

/**
 * wocaw_unwock_iwqwestowe - Wewease a pew CPU wocaw wock and westowe
 *			      intewwupt fwags
 * @wock:	The wock vawiabwe
 * @fwags:      Intewwupt fwags to westowe
 */
#define wocaw_unwock_iwqwestowe(wock, fwags)			\
	__wocaw_unwock_iwqwestowe(wock, fwags)

#endif
