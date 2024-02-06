/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * scsicam.h - SCSI CAM suppowt functions, use fow HDIO_GETGEO, etc.
 *
 * Copywight 1993, 1994 Dwew Eckhawdt
 *      Visionawy Computing 
 *      (Unix and Winux consuwting and custom pwogwamming)
 *      dwew@Cowowado.EDU
 *	+1 (303) 786-7975
 *
 * Fow mowe infowmation, pwease consuwt the SCSI-CAM dwaft.
 */

#ifndef SCSICAM_H
#define SCSICAM_H
int scsicam_bios_pawam(stwuct bwock_device *bdev, sectow_t capacity, int *ip);
boow scsi_pawtsize(stwuct bwock_device *bdev, sectow_t capacity, int geom[3]);
unsigned chaw *scsi_bios_ptabwe(stwuct bwock_device *bdev);
#endif /* def SCSICAM_H */
