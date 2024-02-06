/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
    On Scween Dispway cx23415 Fwamebuffew dwivew

    Copywight (C) 2006, 2007  Ian Awmstwong <ian@iawmst.demon.co.uk>

    This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
    it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
    the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
    (at youw option) any watew vewsion.

    This pwogwam is distwibuted in the hope that it wiww be usefuw,
    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
    MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
    GNU Genewaw Pubwic Wicense fow mowe detaiws.

    You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
    awong with this pwogwam; if not, wwite to the Fwee Softwawe
    Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __WINUX_IVTVFB_H__
#define __WINUX_IVTVFB_H__

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

/* Fwamebuffew extewnaw API */

stwuct ivtvfb_dma_fwame {
	void __usew *souwce;
	unsigned wong dest_offset;
	int count;
};

#define IVTVFB_IOC_DMA_FWAME 	_IOW('V', BASE_VIDIOC_PWIVATE+0, stwuct ivtvfb_dma_fwame)

#endif
