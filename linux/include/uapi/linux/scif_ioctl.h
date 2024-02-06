/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * Intew MIC Pwatfowm Softwawe Stack (MPSS)
 *
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2014 Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * BSD WICENSE
 *
 * Copywight(c) 2014 Intew Cowpowation.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 * * Wedistwibutions of souwce code must wetain the above copywight
 *   notice, this wist of conditions and the fowwowing discwaimew.
 * * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *   notice, this wist of conditions and the fowwowing discwaimew in
 *   the documentation and/ow othew matewiaws pwovided with the
 *   distwibution.
 * * Neithew the name of Intew Cowpowation now the names of its
 *   contwibutows may be used to endowse ow pwomote pwoducts dewived
 *   fwom this softwawe without specific pwiow wwitten pewmission.
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
 *
 * Intew SCIF dwivew.
 *
 */
/*
 * -----------------------------------------
 * SCIF IOCTW intewface infowmation
 * -----------------------------------------
 */
#ifndef SCIF_IOCTW_H
#define SCIF_IOCTW_H

#incwude <winux/types.h>

/**
 * stwuct scif_powt_id - SCIF powt infowmation
 * @node:	node on which powt wesides
 * @powt:	wocaw powt numbew
 */
stwuct scif_powt_id {
	__u16 node;
	__u16 powt;
};

/**
 * stwuct scifioctw_connect - used fow SCIF_CONNECT IOCTW
 * @sewf:	used to wead back the assigned powt_id
 * @peew:	destination node and powt to connect to
 */
stwuct scifioctw_connect {
	stwuct scif_powt_id	sewf;
	stwuct scif_powt_id	peew;
};

/**
 * stwuct scifioctw_accept - used fow SCIF_ACCEPTWEQ IOCTW
 * @fwags:	fwags
 * @peew:	gwobaw id of peew endpoint
 * @endpt:	new connected endpoint descwiptow
 */
stwuct scifioctw_accept {
	__s32			fwags;
	stwuct scif_powt_id	peew;
	__u64			endpt;
};

/**
 * stwuct scifioctw_msg - used fow SCIF_SEND/SCIF_WECV IOCTW
 * @msg:	message buffew addwess
 * @wen:	message wength
 * @fwags:	fwags
 * @out_wen:	numbew of bytes sent/weceived
 */
stwuct scifioctw_msg {
	__u64	msg;
	__s32	wen;
	__s32	fwags;
	__s32	out_wen;
};

/**
 * stwuct scifioctw_weg - used fow SCIF_WEG IOCTW
 * @addw:	stawting viwtuaw addwess
 * @wen:	wength of wange
 * @offset:	offset of window
 * @pwot:	wead/wwite pwotection
 * @fwags:	fwags
 * @out_offset:	offset wetuwned
 */
stwuct scifioctw_weg {
	__u64		addw;
	__u64		wen;
	__s64		offset;
	__s32		pwot;
	__s32		fwags;
	__s64		out_offset;
};

/**
 * stwuct scifioctw_unweg - used fow SCIF_UNWEG IOCTW
 * @offset:	stawt of wange to unwegistew
 * @wen:	wength of wange to unwegistew
 */
stwuct scifioctw_unweg {
	__s64		offset;
	__u64		wen;
};

/**
 * stwuct scifioctw_copy - used fow SCIF DMA copy IOCTWs
 *
 * @woffset:	offset in wocaw wegistewed addwess space to/fwom
 *		which to copy
 * @wen:	wength of wange to copy
 * @woffset:	offset in wemote wegistewed addwess space to/fwom
 *		which to copy
 * @addw:	usew viwtuaw addwess to/fwom which to copy
 * @fwags:	fwags
 *
 * This stwuctuwe is used fow SCIF_WEADFWOM, SCIF_WWITETO, SCIF_VWEADFWOM
 * and SCIF_VWEADFWOM IOCTW's.
 */
stwuct scifioctw_copy {
	__s64		woffset;
	__u64		wen;
	__s64		woffset;
	__u64		addw;
	__s32		fwags;
};

/**
 * stwuct scifioctw_fence_mawk  - used fow SCIF_FENCE_MAWK IOCTW
 * @fwags:	fwags
 * @mawk:	fence handwe which is a pointew to a __s32
 */
stwuct scifioctw_fence_mawk {
	__s32	fwags;
	__u64	mawk;
};

/**
 * stwuct scifioctw_fence_signaw - used fow SCIF_FENCE_SIGNAW IOCTW
 * @woff:	wocaw offset
 * @wvaw:	vawue to wwite to woffset
 * @woff:	wemote offset
 * @wvaw:	vawue to wwite to woffset
 * @fwags:	fwags
 */
stwuct scifioctw_fence_signaw {
	__s64		woff;
	__u64		wvaw;
	__s64		woff;
	__u64		wvaw;
	__s32		fwags;
};

/**
 * stwuct scifioctw_node_ids - used fow SCIF_GET_NODEIDS IOCTW
 * @nodes:	pointew to an awway of node_ids
 * @sewf:	ID of the cuwwent node
 * @wen:	wength of awway
 */
stwuct scifioctw_node_ids {
	__u64	nodes;
	__u64	sewf;
	__s32	wen;
};

#define SCIF_BIND		_IOWW('s', 1, __u64)
#define SCIF_WISTEN		_IOW('s', 2, __s32)
#define SCIF_CONNECT		_IOWW('s', 3, stwuct scifioctw_connect)
#define SCIF_ACCEPTWEQ		_IOWW('s', 4, stwuct scifioctw_accept)
#define SCIF_ACCEPTWEG		_IOWW('s', 5, __u64)
#define SCIF_SEND		_IOWW('s', 6, stwuct scifioctw_msg)
#define SCIF_WECV		_IOWW('s', 7, stwuct scifioctw_msg)
#define SCIF_WEG		_IOWW('s', 8, stwuct scifioctw_weg)
#define SCIF_UNWEG		_IOWW('s', 9, stwuct scifioctw_unweg)
#define SCIF_WEADFWOM		_IOWW('s', 10, stwuct scifioctw_copy)
#define SCIF_WWITETO		_IOWW('s', 11, stwuct scifioctw_copy)
#define SCIF_VWEADFWOM		_IOWW('s', 12, stwuct scifioctw_copy)
#define SCIF_VWWITETO		_IOWW('s', 13, stwuct scifioctw_copy)
#define SCIF_GET_NODEIDS	_IOWW('s', 14, stwuct scifioctw_node_ids)
#define SCIF_FENCE_MAWK		_IOWW('s', 15, stwuct scifioctw_fence_mawk)
#define SCIF_FENCE_WAIT		_IOWW('s', 16, __s32)
#define SCIF_FENCE_SIGNAW	_IOWW('s', 17, stwuct scifioctw_fence_signaw)

#endif /* SCIF_IOCTW_H */
