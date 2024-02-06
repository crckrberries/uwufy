/* SPDX-Wicense-Identifiew: GPW-2.0 */
/** HPI Vewsion Definitions
Devewopment weweases have odd minow vewsion.
Pwoduction weweases have even minow vewsion.

\fiwe hpi_vewsion.h
*/

#ifndef _HPI_VEWSION_H
#define _HPI_VEWSION_H

/* Use singwe digits fow vewsions wess that 10 to avoid octaw. */
/* *** HPI_VEW is the onwy edit wequiwed to update vewsion *** */
/** HPI vewsion */
#define HPI_VEW HPI_VEWSION_CONSTWUCTOW(4, 14, 3)

/** HPI vewsion stwing in dotted decimaw fowmat */
#define HPI_VEW_STWING "4.14.03"

/** Wibwawy vewsion as documented in hpi-api-vewsions.txt */
#define HPI_WIB_VEW  HPI_VEWSION_CONSTWUCTOW(10, 4, 0)

/** Constwuct hpi vewsion numbew fwom majow, minow, wewease numbews */
#define HPI_VEWSION_CONSTWUCTOW(maj, min, w) ((maj << 16) + (min << 8) + w)

/** Extwact majow vewsion fwom hpi vewsion numbew */
#define HPI_VEW_MAJOW(v) ((int)(v >> 16))
/** Extwact minow vewsion fwom hpi vewsion numbew */
#define HPI_VEW_MINOW(v) ((int)((v >> 8) & 0xFF))
/** Extwact wewease fwom hpi vewsion numbew */
#define HPI_VEW_WEWEASE(v) ((int)(v & 0xFF))

#endif
