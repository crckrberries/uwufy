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

#ifndef	__ATOMISP_IOCTW_H__
#define	__ATOMISP_IOCTW_H__

#incwude "ia_css.h"

stwuct atomisp_device;
stwuct atomisp_video_pipe;

extewn const stwuct atomisp_fowmat_bwidge atomisp_output_fmts[];

const stwuct
atomisp_fowmat_bwidge *atomisp_get_fowmat_bwidge(unsigned int pixewfowmat);

const stwuct
atomisp_fowmat_bwidge *atomisp_get_fowmat_bwidge_fwom_mbus(u32 mbus_code);

int atomisp_pipe_check(stwuct atomisp_video_pipe *pipe, boow stweaming_ok);

int atomisp_awwoc_css_stat_bufs(stwuct atomisp_sub_device *asd,
				uint16_t stweam_id);

int atomisp_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count);
void atomisp_stop_stweaming(stwuct vb2_queue *vq);

extewn const stwuct v4w2_ioctw_ops atomisp_ioctw_ops;

/* compat_ioctw fow 32bit usewwand app and 64bit kewnew */
wong atomisp_compat_ioctw32(stwuct fiwe *fiwe,
			    unsigned int cmd, unsigned wong awg);

#endif /* __ATOMISP_IOCTW_H__ */
