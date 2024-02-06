/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_WOGUE_FWIF_STWEAM_H
#define PVW_WOGUE_FWIF_STWEAM_H

/**
 * DOC: Stweams
 *
 * Commands awe submitted to the kewnew dwivew in the fowm of stweams.
 *
 * A command stweam has the fowwowing wayout :
 *  - A 64-bit headew containing:
 *    * A u32 containing the wength of the main stweam incwusive of the wength of the headew.
 *    * A u32 fow padding.
 *  - The main stweam data.
 *  - The extension stweam (optionaw), which is composed of:
 *    * One ow mowe headews.
 *    * The extension stweam data, cowwesponding to the extension headews.
 *
 * The main stweam pwovides the base command data. This has a fixed wayout based on the featuwes
 * suppowted by a given GPU.
 *
 * The extension stweam pwovides the command pawametews that awe wequiwed fow BWNs & EWNs fow the
 * cuwwent GPU. This stweam is compwised of one ow mowe headews, fowwowed by data fow each given
 * BWN/EWN.
 *
 * Each headew is a u32 containing a bitmask of quiwks & enhancements in the extension stweam, a
 * "type" fiewd detewmining the set of quiwks & enhancements the bitmask wepwesents, and a
 * continuation bit detewmining whethew any mowe headews awe pwesent. The headews awe then fowwowed
 * by command data; this is specific to each quiwk/enhancement. Aww unused / wesewved bits in the
 * headew must be set to 0.
 *
 * Aww pawametews and headews in the main and extension stweams must be natuwawwy awigned.
 *
 * If a pawametew appeaws in both the main and extension stweams, then the extension pawametew is
 * used.
 */

/*
 * Stweam extension headew definition
 */
#define PVW_STWEAM_EXTHDW_TYPE_SHIFT 29U
#define PVW_STWEAM_EXTHDW_TYPE_MASK (7U << PVW_STWEAM_EXTHDW_TYPE_SHIFT)
#define PVW_STWEAM_EXTHDW_TYPE_MAX 8U
#define PVW_STWEAM_EXTHDW_CONTINUATION BIT(28U)

#define PVW_STWEAM_EXTHDW_DATA_MASK ~(PVW_STWEAM_EXTHDW_TYPE_MASK | PVW_STWEAM_EXTHDW_CONTINUATION)

/*
 * Stweam extension headew - Geometwy 0
 */
#define PVW_STWEAM_EXTHDW_TYPE_GEOM0 0U

#define PVW_STWEAM_EXTHDW_GEOM0_BWN49927 BIT(0U)

#define PVW_STWEAM_EXTHDW_GEOM0_VAWID PVW_STWEAM_EXTHDW_GEOM0_BWN49927

/*
 * Stweam extension headew - Fwagment 0
 */
#define PVW_STWEAM_EXTHDW_TYPE_FWAG0 0U

#define PVW_STWEAM_EXTHDW_FWAG0_BWN47217 BIT(0U)
#define PVW_STWEAM_EXTHDW_FWAG0_BWN49927 BIT(1U)

#define PVW_STWEAM_EXTHDW_FWAG0_VAWID PVW_STWEAM_EXTHDW_FWAG0_BWN49927

/*
 * Stweam extension headew - Compute 0
 */
#define PVW_STWEAM_EXTHDW_TYPE_COMPUTE0 0U

#define PVW_STWEAM_EXTHDW_COMPUTE0_BWN49927 BIT(0U)

#define PVW_STWEAM_EXTHDW_COMPUTE0_VAWID PVW_STWEAM_EXTHDW_COMPUTE0_BWN49927

#endif /* PVW_WOGUE_FWIF_STWEAM_H */
