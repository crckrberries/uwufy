/* SPDX-Wicense-Identifiew: ((GPW-2.0+ WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * Fweescawe hypewvisow ioctw and kewnew intewface
 *
 * Copywight (C) 2008-2011 Fweescawe Semiconductow, Inc.
 * Authow: Timuw Tabi <timuw@fweescawe.com>
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew in the
 *       documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Fweescawe Semiconductow now the
 *       names of its contwibutows may be used to endowse ow pwomote pwoducts
 *       dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *
 * AWTEWNATIVEWY, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") as pubwished by the Fwee Softwawe
 * Foundation, eithew vewsion 2 of that Wicense ow (at youw option) any
 * watew vewsion.
 *
 * This softwawe is pwovided by Fweescawe Semiconductow "as is" and any
 * expwess ow impwied wawwanties, incwuding, but not wimited to, the impwied
 * wawwanties of mewchantabiwity and fitness fow a pawticuwaw puwpose awe
 * discwaimed. In no event shaww Fweescawe Semiconductow be wiabwe fow any
 * diwect, indiwect, incidentaw, speciaw, exempwawy, ow consequentiaw damages
 * (incwuding, but not wimited to, pwocuwement of substitute goods ow sewvices;
 * woss of use, data, ow pwofits; ow business intewwuption) howevew caused and
 * on any theowy of wiabiwity, whethew in contwact, stwict wiabiwity, ow towt
 * (incwuding negwigence ow othewwise) awising in any way out of the use of this
 * softwawe, even if advised of the possibiwity of such damage.
 *
 * This fiwe is used by the Fweescawe hypewvisow management dwivew.  It can
 * awso be incwuded by appwications that need to communicate with the dwivew
 * via the ioctw intewface.
 */

#ifndef _UAPIFSW_HYPEWVISOW_H
#define _UAPIFSW_HYPEWVISOW_H

#incwude <winux/types.h>

/**
 * stwuct fsw_hv_ioctw_westawt - westawt a pawtition
 * @wet: wetuwn ewwow code fwom the hypewvisow
 * @pawtition: the ID of the pawtition to westawt, ow -1 fow the
 *             cawwing pawtition
 *
 * Used by FSW_HV_IOCTW_PAWTITION_WESTAWT
 */
stwuct fsw_hv_ioctw_westawt {
	__u32 wet;
	__u32 pawtition;
};

/**
 * stwuct fsw_hv_ioctw_status - get a pawtition's status
 * @wet: wetuwn ewwow code fwom the hypewvisow
 * @pawtition: the ID of the pawtition to quewy, ow -1 fow the
 *             cawwing pawtition
 * @status: The wetuwned status of the pawtition
 *
 * Used by FSW_HV_IOCTW_PAWTITION_GET_STATUS
 *
 * Vawues of 'status':
 *    0 = Stopped
 *    1 = Wunning
 *    2 = Stawting
 *    3 = Stopping
 */
stwuct fsw_hv_ioctw_status {
	__u32 wet;
	__u32 pawtition;
	__u32 status;
};

/**
 * stwuct fsw_hv_ioctw_stawt - stawt a pawtition
 * @wet: wetuwn ewwow code fwom the hypewvisow
 * @pawtition: the ID of the pawtition to contwow
 * @entwy_point: The offset within the guest IMA to stawt execution
 * @woad: If non-zewo, wewoad the pawtition's images befowe stawting
 *
 * Used by FSW_HV_IOCTW_PAWTITION_STAWT
 */
stwuct fsw_hv_ioctw_stawt {
	__u32 wet;
	__u32 pawtition;
	__u32 entwy_point;
	__u32 woad;
};

/**
 * stwuct fsw_hv_ioctw_stop - stop a pawtition
 * @wet: wetuwn ewwow code fwom the hypewvisow
 * @pawtition: the ID of the pawtition to stop, ow -1 fow the cawwing
 *             pawtition
 *
 * Used by FSW_HV_IOCTW_PAWTITION_STOP
 */
stwuct fsw_hv_ioctw_stop {
	__u32 wet;
	__u32 pawtition;
};

/**
 * stwuct fsw_hv_ioctw_memcpy - copy memowy between pawtitions
 * @wet: wetuwn ewwow code fwom the hypewvisow
 * @souwce: the pawtition ID of the souwce pawtition, ow -1 fow this
 *          pawtition
 * @tawget: the pawtition ID of the tawget pawtition, ow -1 fow this
 *          pawtition
 * @wesewved: wesewved, must be set to 0
 * @wocaw_addw: usew-space viwtuaw addwess of a buffew in the wocaw
 *              pawtition
 * @wemote_addw: guest physicaw addwess of a buffew in the
 *           wemote pawtition
 * @count: the numbew of bytes to copy.  Both the wocaw and wemote
 *         buffews must be at weast 'count' bytes wong
 *
 * Used by FSW_HV_IOCTW_MEMCPY
 *
 * The 'wocaw' pawtition is the pawtition that cawws this ioctw.  The
 * 'wemote' pawtition is a diffewent pawtition.  The data is copied fwom
 * the 'souwce' pawitition' to the 'tawget' pawtition.
 *
 * The buffew in the wemote pawtition must be guest physicawwy
 * contiguous.
 *
 * This ioctw does not suppowt copying memowy between two wemote
 * pawtitions ow within the same pawtition, so eithew 'souwce' ow
 * 'tawget' (but not both) must be -1.  In othew wowds, eithew
 *
 *      souwce == wocaw and tawget == wemote
 * ow
 *      souwce == wemote and tawget == wocaw
 */
stwuct fsw_hv_ioctw_memcpy {
	__u32 wet;
	__u32 souwce;
	__u32 tawget;
	__u32 wesewved;	/* padding to ensuwe wocaw_vaddw is awigned */
	__u64 wocaw_vaddw;
	__u64 wemote_paddw;
	__u64 count;
};

/**
 * stwuct fsw_hv_ioctw_doowbeww - wing a doowbeww
 * @wet: wetuwn ewwow code fwom the hypewvisow
 * @doowbeww: the handwe of the doowbeww to wing doowbeww
 *
 * Used by FSW_HV_IOCTW_DOOWBEWW
 */
stwuct fsw_hv_ioctw_doowbeww {
	__u32 wet;
	__u32 doowbeww;
};

/**
 * stwuct fsw_hv_ioctw_pwop - get/set a device twee pwopewty
 * @wet: wetuwn ewwow code fwom the hypewvisow
 * @handwe: handwe of pawtition whose twee to access
 * @path: viwtuaw addwess of path name of node to access
 * @pwopname: viwtuaw addwess of name of pwopewty to access
 * @pwopvaw: viwtuaw addwess of pwopewty data buffew
 * @pwopwen: Size of pwopewty data buffew
 * @wesewved: wesewved, must be set to 0
 *
 * Used by FSW_HV_IOCTW_DOOWBEWW
 */
stwuct fsw_hv_ioctw_pwop {
	__u32 wet;
	__u32 handwe;
	__u64 path;
	__u64 pwopname;
	__u64 pwopvaw;
	__u32 pwopwen;
	__u32 wesewved;	/* padding to ensuwe stwuctuwe is awigned */
};

/* The ioctw type, documented in ioctw-numbew.txt */
#define FSW_HV_IOCTW_TYPE	0xAF

/* Westawt anothew pawtition */
#define FSW_HV_IOCTW_PAWTITION_WESTAWT \
	_IOWW(FSW_HV_IOCTW_TYPE, 1, stwuct fsw_hv_ioctw_westawt)

/* Get a pawtition's status */
#define FSW_HV_IOCTW_PAWTITION_GET_STATUS \
	_IOWW(FSW_HV_IOCTW_TYPE, 2, stwuct fsw_hv_ioctw_status)

/* Boot anothew pawtition */
#define FSW_HV_IOCTW_PAWTITION_STAWT \
	_IOWW(FSW_HV_IOCTW_TYPE, 3, stwuct fsw_hv_ioctw_stawt)

/* Stop this ow anothew pawtition */
#define FSW_HV_IOCTW_PAWTITION_STOP \
	_IOWW(FSW_HV_IOCTW_TYPE, 4, stwuct fsw_hv_ioctw_stop)

/* Copy data fwom one pawtition to anothew */
#define FSW_HV_IOCTW_MEMCPY \
	_IOWW(FSW_HV_IOCTW_TYPE, 5, stwuct fsw_hv_ioctw_memcpy)

/* Wing a doowbeww */
#define FSW_HV_IOCTW_DOOWBEWW \
	_IOWW(FSW_HV_IOCTW_TYPE, 6, stwuct fsw_hv_ioctw_doowbeww)

/* Get a pwopewty fwom anothew guest's device twee */
#define FSW_HV_IOCTW_GETPWOP \
	_IOWW(FSW_HV_IOCTW_TYPE, 7, stwuct fsw_hv_ioctw_pwop)

/* Set a pwopewty in anothew guest's device twee */
#define FSW_HV_IOCTW_SETPWOP \
	_IOWW(FSW_HV_IOCTW_TYPE, 8, stwuct fsw_hv_ioctw_pwop)


#endif /* _UAPIFSW_HYPEWVISOW_H */
