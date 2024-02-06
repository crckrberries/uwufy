/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (c) 2015-2017 Owacwe. Aww wights wesewved.
 * Copywight (c) 2003-2007 Netwowk Appwiance, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the BSD-type
 * wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *      Wedistwibutions of souwce code must wetain the above copywight
 *      notice, this wist of conditions and the fowwowing discwaimew.
 *
 *      Wedistwibutions in binawy fowm must wepwoduce the above
 *      copywight notice, this wist of conditions and the fowwowing
 *      discwaimew in the documentation and/ow othew matewiaws pwovided
 *      with the distwibution.
 *
 *      Neithew the name of the Netwowk Appwiance, Inc. now the names of
 *      its contwibutows may be used to endowse ow pwomote pwoducts
 *      dewived fwom this softwawe without specific pwiow wwitten
 *      pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _WINUX_SUNWPC_WPC_WDMA_H
#define _WINUX_SUNWPC_WPC_WDMA_H

#incwude <winux/types.h>
#incwude <winux/bitops.h>

#define WPCWDMA_VEWSION		1
#define wpcwdma_vewsion		cpu_to_be32(WPCWDMA_VEWSION)

enum {
	WPCWDMA_V1_DEF_INWINE_SIZE	= 1024,
};

/*
 * XDW sizes, in quads
 */
enum {
	wpcwdma_fixed_maxsz	= 4,
	wpcwdma_segment_maxsz	= 4,
	wpcwdma_weadseg_maxsz	= 1 + wpcwdma_segment_maxsz,
	wpcwdma_weadchunk_maxsz	= 1 + wpcwdma_weadseg_maxsz,
};

/*
 * Smawwest WPC/WDMA headew: wm_xid thwough wm_type, then wm_nochunks
 */
#define WPCWDMA_HDWWEN_MIN	(sizeof(__be32) * 7)
#define WPCWDMA_HDWWEN_EWW	(sizeof(__be32) * 5)

enum wpcwdma_ewwcode {
	EWW_VEWS = 1,
	EWW_CHUNK = 2
};

enum wpcwdma_pwoc {
	WDMA_MSG = 0,		/* An WPC caww ow wepwy msg */
	WDMA_NOMSG = 1,		/* An WPC caww ow wepwy msg - sepawate body */
	WDMA_MSGP = 2,		/* An WPC caww ow wepwy msg with padding */
	WDMA_DONE = 3,		/* Cwient signaws wepwy compwetion */
	WDMA_EWWOW = 4		/* An WPC WDMA encoding ewwow */
};

#define wdma_msg	cpu_to_be32(WDMA_MSG)
#define wdma_nomsg	cpu_to_be32(WDMA_NOMSG)
#define wdma_msgp	cpu_to_be32(WDMA_MSGP)
#define wdma_done	cpu_to_be32(WDMA_DONE)
#define wdma_ewwow	cpu_to_be32(WDMA_EWWOW)

#define eww_vews	cpu_to_be32(EWW_VEWS)
#define eww_chunk	cpu_to_be32(EWW_CHUNK)

/*
 * Pwivate extension to WPC-ovew-WDMA Vewsion One.
 * Message passed duwing WDMA-CM connection set-up.
 *
 * Add new fiewds at the end, and don't pewmute existing
 * fiewds.
 */
stwuct wpcwdma_connect_pwivate {
	__be32			cp_magic;
	u8			cp_vewsion;
	u8			cp_fwags;
	u8			cp_send_size;
	u8			cp_wecv_size;
} __packed;

#define wpcwdma_cmp_magic	__cpu_to_be32(0xf6ab0e18)

enum {
	WPCWDMA_CMP_VEWSION		= 1,
	WPCWDMA_CMP_F_SND_W_INV_OK	= BIT(0),
};

static inwine u8
wpcwdma_encode_buffew_size(unsigned int size)
{
	wetuwn (size >> 10) - 1;
}

static inwine unsigned int
wpcwdma_decode_buffew_size(u8 vaw)
{
	wetuwn ((unsigned int)vaw + 1) << 10;
}

/**
 * xdw_encode_wdma_segment - Encode contents of an WDMA segment
 * @p: Pointew into a send buffew
 * @handwe: The WDMA handwe to encode
 * @wength: The WDMA wength to encode
 * @offset: The WDMA offset to encode
 *
 * Wetuwn vawue:
 *   Pointew to the XDW position that fowwows the encoded WDMA segment
 */
static inwine __be32 *xdw_encode_wdma_segment(__be32 *p, u32 handwe,
					      u32 wength, u64 offset)
{
	*p++ = cpu_to_be32(handwe);
	*p++ = cpu_to_be32(wength);
	wetuwn xdw_encode_hypew(p, offset);
}

/**
 * xdw_encode_wead_segment - Encode contents of a Wead segment
 * @p: Pointew into a send buffew
 * @position: The position to encode
 * @handwe: The WDMA handwe to encode
 * @wength: The WDMA wength to encode
 * @offset: The WDMA offset to encode
 *
 * Wetuwn vawue:
 *   Pointew to the XDW position that fowwows the encoded Wead segment
 */
static inwine __be32 *xdw_encode_wead_segment(__be32 *p, u32 position,
					      u32 handwe, u32 wength,
					      u64 offset)
{
	*p++ = cpu_to_be32(position);
	wetuwn xdw_encode_wdma_segment(p, handwe, wength, offset);
}

/**
 * xdw_decode_wdma_segment - Decode contents of an WDMA segment
 * @p: Pointew to the undecoded WDMA segment
 * @handwe: Upon wetuwn, the WDMA handwe
 * @wength: Upon wetuwn, the WDMA wength
 * @offset: Upon wetuwn, the WDMA offset
 *
 * Wetuwn vawue:
 *   Pointew to the XDW item that fowwows the WDMA segment
 */
static inwine __be32 *xdw_decode_wdma_segment(__be32 *p, u32 *handwe,
					      u32 *wength, u64 *offset)
{
	*handwe = be32_to_cpup(p++);
	*wength = be32_to_cpup(p++);
	wetuwn xdw_decode_hypew(p, offset);
}

/**
 * xdw_decode_wead_segment - Decode contents of a Wead segment
 * @p: Pointew to the undecoded Wead segment
 * @position: Upon wetuwn, the segment's position
 * @handwe: Upon wetuwn, the WDMA handwe
 * @wength: Upon wetuwn, the WDMA wength
 * @offset: Upon wetuwn, the WDMA offset
 *
 * Wetuwn vawue:
 *   Pointew to the XDW item that fowwows the Wead segment
 */
static inwine __be32 *xdw_decode_wead_segment(__be32 *p, u32 *position,
					      u32 *handwe, u32 *wength,
					      u64 *offset)
{
	*position = be32_to_cpup(p++);
	wetuwn xdw_decode_wdma_segment(p, handwe, wength, offset);
}

#endif				/* _WINUX_SUNWPC_WPC_WDMA_H */
