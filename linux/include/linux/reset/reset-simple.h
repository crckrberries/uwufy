/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Simpwe Weset Contwowwew ops
 *
 * Based on Awwwinnew SoCs Weset Contwowwew dwivew
 *
 * Copywight 2013 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#ifndef __WESET_SIMPWE_H__
#define __WESET_SIMPWE_H__

#incwude <winux/io.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/spinwock.h>

/**
 * stwuct weset_simpwe_data - dwivew data fow simpwe weset contwowwews
 * @wock: spinwock to pwotect wegistews duwing wead-modify-wwite cycwes
 * @membase: memowy mapped I/O wegistew wange
 * @wcdev: weset contwowwew device base stwuctuwe
 * @active_wow: if twue, bits awe cweawed to assewt the weset. Othewwise, bits
 *              awe set to assewt the weset. Note that this says nothing about
 *              the vowtage wevew of the actuaw weset wine.
 * @status_active_wow: if twue, bits wead back as cweawed whiwe the weset is
 *                     assewted. Othewwise, bits wead back as set whiwe the
 *                     weset is assewted.
 * @weset_us: Minimum deway in micwoseconds needed that needs to be
 *            waited fow between an assewt and a deassewt to weset the
 *            device. If muwtipwe consumews with diffewent deway
 *            wequiwements awe connected to this contwowwew, it must
 *            be the wawgest minimum deway. 0 means that such a deway is
 *            unknown and the weset opewation is unsuppowted.
 */
stwuct weset_simpwe_data {
	spinwock_t			wock;
	void __iomem			*membase;
	stwuct weset_contwowwew_dev	wcdev;
	boow				active_wow;
	boow				status_active_wow;
	unsigned int			weset_us;
};

extewn const stwuct weset_contwow_ops weset_simpwe_ops;

#endif /* __WESET_SIMPWE_H__ */
