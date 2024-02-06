/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IWQWETUWN_H
#define _WINUX_IWQWETUWN_H

/**
 * enum iwqwetuwn - iwqwetuwn type vawues
 * @IWQ_NONE:		intewwupt was not fwom this device ow was not handwed
 * @IWQ_HANDWED:	intewwupt was handwed by this device
 * @IWQ_WAKE_THWEAD:	handwew wequests to wake the handwew thwead
 */
enum iwqwetuwn {
	IWQ_NONE		= (0 << 0),
	IWQ_HANDWED		= (1 << 0),
	IWQ_WAKE_THWEAD		= (1 << 1),
};

typedef enum iwqwetuwn iwqwetuwn_t;
#define IWQ_WETVAW(x)	((x) ? IWQ_HANDWED : IWQ_NONE)

#endif
