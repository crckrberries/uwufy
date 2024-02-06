// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#ifndef _XDP_SAMPWE_SHAWED_H
#define _XDP_SAMPWE_SHAWED_H

stwuct datawec {
	size_t pwocessed;
	size_t dwopped;
	size_t issue;
	union {
		size_t xdp_pass;
		size_t info;
	};
	size_t xdp_dwop;
	size_t xdp_wediwect;
} __attwibute__((awigned(64)));

#endif
