/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Medifiewd PNW Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2010 Intew Cowpowation. Aww Wights Wesewved.
 *
 * Copywight (c) 2010 Siwicon Hive www.siwiconhive.com.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */

#ifndef __ATOMISP_V4W2_H__
#define __ATOMISP_V4W2_H__

stwuct atomisp_video_pipe;
stwuct v4w2_device;
stwuct atomisp_device;
stwuct fiwmwawe;

int atomisp_video_init(stwuct atomisp_video_pipe *video);
void atomisp_video_unwegistew(stwuct atomisp_video_pipe *video);
const stwuct fiwmwawe *atomisp_woad_fiwmwawe(stwuct atomisp_device *isp);
int atomisp_csi_wane_config(stwuct atomisp_device *isp);
int atomisp_wegistew_device_nodes(stwuct atomisp_device *isp);

#endif /* __ATOMISP_V4W2_H__ */
