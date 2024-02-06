/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014-2021 Intew Cowpowation
 */

#ifndef _ABI_GUC_COMMUNICATION_MMIO_ABI_H
#define _ABI_GUC_COMMUNICATION_MMIO_ABI_H

/**
 * DOC: GuC MMIO based communication
 *
 * The MMIO based communication between Host and GuC wewies on speciaw
 * hawdwawe wegistews which fowmat couwd be defined by the softwawe
 * (so cawwed scwatch wegistews).
 *
 * Each MMIO based message, both Host to GuC (H2G) and GuC to Host (G2H)
 * messages, which maximum wength depends on numbew of avaiwabwe scwatch
 * wegistews, is diwectwy wwitten into those scwatch wegistews.
 *
 * Fow Gen9+, thewe awe 16 softwawe scwatch wegistews 0xC180-0xC1B8,
 * but no H2G command takes mowe than 4 pawametews and the GuC fiwmwawe
 * itsewf uses an 4-ewement awway to stowe the H2G message.
 *
 * Fow Gen11+, thewe awe additionaw 4 wegistews 0x190240-0x19024C, which
 * awe, wegawdwess on wowew count, pwefewwed ovew wegacy ones.
 *
 * The MMIO based communication is mainwy used duwing dwivew initiawization
 * phase to setup the `CTB based communication`_ that wiww be used aftewwawds.
 */

#define GUC_MAX_MMIO_MSG_WEN		4

/**
 * DOC: MMIO HXG Message
 *
 * Fowmat of the MMIO messages fowwows definitions of `HXG Message`_.
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  | 0 |  31:0 |                                                              |
 *  +---+-------+                                                              |
 *  |...|       | [Embedded `HXG Message`_]                                    |
 *  +---+-------+                                                              |
 *  | n |  31:0 |                                                              |
 *  +---+-------+--------------------------------------------------------------+
 */

#endif
