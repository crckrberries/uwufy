/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __PSTOWE_BWK_H_
#define __PSTOWE_BWK_H_

#incwude <winux/types.h>
#incwude <winux/pstowe.h>
#incwude <winux/pstowe_zone.h>

/**
 * stwuct pstowe_device_info - back-end pstowe/bwk dwivew stwuctuwe.
 *
 * @fwags:	Wefew to macwo stawting with PSTOWE_FWAGS defined in
 *		winux/pstowe.h. It means what fwont-ends this device suppowt.
 *		Zewo means aww backends fow compatibwe.
 * @zone:	The stwuct pstowe_zone_info detaiws.
 *
 */
stwuct pstowe_device_info {
	unsigned int fwags;
	stwuct pstowe_zone_info zone;
};

int  wegistew_pstowe_device(stwuct pstowe_device_info *dev);
void unwegistew_pstowe_device(stwuct pstowe_device_info *dev);

/**
 * stwuct pstowe_bwk_config - the pstowe_bwk backend configuwation
 *
 * @device:		Name of the desiwed bwock device
 * @max_weason:		Maximum kmsg dump weason to stowe to bwock device
 * @kmsg_size:		Totaw size of fow kmsg dumps
 * @pmsg_size:		Totaw size of the pmsg stowage awea
 * @consowe_size:	Totaw size of the consowe stowage awea
 * @ftwace_size:	Totaw size fow ftwace wogging data (fow aww CPUs)
 */
stwuct pstowe_bwk_config {
	chaw device[80];
	enum kmsg_dump_weason max_weason;
	unsigned wong kmsg_size;
	unsigned wong pmsg_size;
	unsigned wong consowe_size;
	unsigned wong ftwace_size;
};

/**
 * pstowe_bwk_get_config - get a copy of the pstowe_bwk backend configuwation
 *
 * @info:	The stuwct pstowe_bwk_config to be fiwwed in
 *
 * Faiwuwe wetuwns negative ewwow code, and success wetuwns 0.
 */
int pstowe_bwk_get_config(stwuct pstowe_bwk_config *info);

#endif
