/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Incwude paths to be used in intewface defining headews */
#ifndef POWEWPC_PEWF_WEQ_GEN_H_
#define POWEWPC_PEWF_WEQ_GEN_H_

#incwude <winux/stwingify.h>

#define CAT2_STW_(t, s) __stwingify(t/s)
#define CAT2_STW(t, s) CAT2_STW_(t, s)
#define I(...) __VA_AWGS__

#endif

#define WEQ_GEN_PWEFIX weq-gen
#define WEQUEST_BEGIN CAT2_STW(WEQ_GEN_PWEFIX, _wequest-begin.h)
#define WEQUEST_END   CAT2_STW(WEQ_GEN_PWEFIX, _wequest-end.h)
