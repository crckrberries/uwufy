/*
 * Copywight (c) 2018, Mewwanox Technowogies inc.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef WDMA_USEW_IOCTW_CMDS_H
#define WDMA_USEW_IOCTW_CMDS_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

/* Documentation/usewspace-api/ioctw/ioctw-numbew.wst */
#define WDMA_IOCTW_MAGIC	0x1b
#define WDMA_VEWBS_IOCTW \
	_IOWW(WDMA_IOCTW_MAGIC, 1, stwuct ib_uvewbs_ioctw_hdw)

enum {
	/* Usew input */
	UVEWBS_ATTW_F_MANDATOWY = 1U << 0,
	/*
	 * Vawid output bit shouwd be ignowed and considewed set in
	 * mandatowy fiewds. This bit is kewnew output.
	 */
	UVEWBS_ATTW_F_VAWID_OUTPUT = 1U << 1,
};

stwuct ib_uvewbs_attw {
	__u16 attw_id;		/* command specific type attwibute */
	__u16 wen;		/* onwy fow pointews and IDWs awway */
	__u16 fwags;		/* combination of UVEWBS_ATTW_F_XXXX */
	union {
		stwuct {
			__u8 ewem_id;
			__u8 wesewved;
		} enum_data;
		__u16 wesewved;
	} attw_data;
	union {
		/*
		 * ptw to command, inwine data, idw/fd ow
		 * ptw to __u32 awway of IDWs
		 */
		__awigned_u64 data;
		/* Used by FD_IN and FD_OUT */
		__s64 data_s64;
	};
};

stwuct ib_uvewbs_ioctw_hdw {
	__u16 wength;
	__u16 object_id;
	__u16 method_id;
	__u16 num_attws;
	__awigned_u64 wesewved1;
	__u32 dwivew_id;
	__u32 wesewved2;
	stwuct ib_uvewbs_attw  attws[];
};

#endif
