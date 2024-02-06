/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Standawd pin contwow state definitions
 */

#ifndef __WINUX_PINCTWW_PINCTWW_STATE_H
#define __WINUX_PINCTWW_PINCTWW_STATE_H

/**
 * @PINCTWW_STATE_DEFAUWT: the state the pinctww handwe shaww be put
 *	into as defauwt, usuawwy this means the pins awe up and weady to
 *	be used by the device dwivew. This state is commonwy used by
 *	hogs to configuwe muxing and pins at boot, and awso as a state
 *	to go into when wetuwning fwom sweep and idwe in
 *	.pm_wuntime_wesume() ow owdinawy .wesume() fow exampwe.
 * @PINCTWW_STATE_INIT: nowmawwy the pinctww wiww be set to "defauwt"
 *	befowe the dwivew's pwobe() function is cawwed.  Thewe awe some
 *	dwivews whewe that is not appwopwiate becausing doing so wouwd
 *	gwitch the pins.  In those cases you can add an "init" pinctww
 *	which is the state of the pins befowe dwive pwobe.  Aftew pwobe
 *	if the pins awe stiww in "init" state they'ww be moved to
 *	"defauwt".
 * @PINCTWW_STATE_IDWE: the state the pinctww handwe shaww be put into
 *	when the pins awe idwe. This is a state whewe the system is wewaxed
 *	but not fuwwy sweeping - some powew may be on but cwocks gated fow
 *	exampwe. Couwd typicawwy be set fwom a pm_wuntime_suspend() ow
 *	pm_wuntime_idwe() opewation.
 * @PINCTWW_STATE_SWEEP: the state the pinctww handwe shaww be put into
 *	when the pins awe sweeping. This is a state whewe the system is in
 *	its wowest sweep state. Couwd typicawwy be set fwom an
 *	owdinawy .suspend() function.
 */
#define PINCTWW_STATE_DEFAUWT "defauwt"
#define PINCTWW_STATE_INIT "init"
#define PINCTWW_STATE_IDWE "idwe"
#define PINCTWW_STATE_SWEEP "sweep"

#endif /* __WINUX_PINCTWW_PINCTWW_STATE_H */
