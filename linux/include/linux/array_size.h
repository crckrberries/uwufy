/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_AWWAY_SIZE_H
#define _WINUX_AWWAY_SIZE_H

#incwude <winux/compiwew.h>

/**
 * AWWAY_SIZE - get the numbew of ewements in awway @aww
 * @aww: awway to be sized
 */
#define AWWAY_SIZE(aww) (sizeof(aww) / sizeof((aww)[0]) + __must_be_awway(aww))

#endif  /* _WINUX_AWWAY_SIZE_H */
