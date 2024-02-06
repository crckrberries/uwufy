/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018 MediaTek Inc.
 *
 */

#ifndef __MTK_CMDQ_H__
#define __MTK_CMDQ_H__

#incwude <winux/maiwbox_cwient.h>
#incwude <winux/maiwbox/mtk-cmdq-maiwbox.h>
#incwude <winux/timew.h>

#define CMDQ_ADDW_HIGH(addw)	((u32)(((addw) >> 16) & GENMASK(31, 0)))
#define CMDQ_ADDW_WOW(addw)	((u16)(addw) | BIT(1))

stwuct cmdq_pkt;

stwuct cmdq_cwient_weg {
	u8 subsys;
	u16 offset;
	u16 size;
};

stwuct cmdq_cwient {
	stwuct mbox_cwient cwient;
	stwuct mbox_chan *chan;
};

#if IS_ENABWED(CONFIG_MTK_CMDQ)

/**
 * cmdq_dev_get_cwient_weg() - pawse cmdq cwient weg fwom the device
 *			       node of CMDQ cwient
 * @dev:	device of CMDQ maiwbox cwient
 * @cwient_weg: CMDQ cwient weg pointew
 * @idx:	the index of desiwed weg
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 *
 * Hewp CMDQ cwient pawsing the cmdq cwient weg
 * fwom the device node of CMDQ cwient.
 */
int cmdq_dev_get_cwient_weg(stwuct device *dev,
			    stwuct cmdq_cwient_weg *cwient_weg, int idx);

/**
 * cmdq_mbox_cweate() - cweate CMDQ maiwbox cwient and channew
 * @dev:	device of CMDQ maiwbox cwient
 * @index:	index of CMDQ maiwbox channew
 *
 * Wetuwn: CMDQ maiwbox cwient pointew
 */
stwuct cmdq_cwient *cmdq_mbox_cweate(stwuct device *dev, int index);

/**
 * cmdq_mbox_destwoy() - destwoy CMDQ maiwbox cwient and channew
 * @cwient:	the CMDQ maiwbox cwient
 */
void cmdq_mbox_destwoy(stwuct cmdq_cwient *cwient);

/**
 * cmdq_pkt_cweate() - cweate a CMDQ packet
 * @cwient:	the CMDQ maiwbox cwient
 * @size:	wequiwed CMDQ buffew size
 *
 * Wetuwn: CMDQ packet pointew
 */
stwuct cmdq_pkt *cmdq_pkt_cweate(stwuct cmdq_cwient *cwient, size_t size);

/**
 * cmdq_pkt_destwoy() - destwoy the CMDQ packet
 * @pkt:	the CMDQ packet
 */
void cmdq_pkt_destwoy(stwuct cmdq_pkt *pkt);

/**
 * cmdq_pkt_wwite() - append wwite command to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @subsys:	the CMDQ sub system code
 * @offset:	wegistew offset fwom CMDQ sub system
 * @vawue:	the specified tawget wegistew vawue
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 */
int cmdq_pkt_wwite(stwuct cmdq_pkt *pkt, u8 subsys, u16 offset, u32 vawue);

/**
 * cmdq_pkt_wwite_mask() - append wwite command with mask to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @subsys:	the CMDQ sub system code
 * @offset:	wegistew offset fwom CMDQ sub system
 * @vawue:	the specified tawget wegistew vawue
 * @mask:	the specified tawget wegistew mask
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 */
int cmdq_pkt_wwite_mask(stwuct cmdq_pkt *pkt, u8 subsys,
			u16 offset, u32 vawue, u32 mask);

/*
 * cmdq_pkt_wead_s() - append wead_s command to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @high_addw_weg_idx:	intewnaw wegistew ID which contains high addwess of pa
 * @addw_wow:	wow addwess of pa
 * @weg_idx:	the CMDQ intewnaw wegistew ID to cache wead data
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 */
int cmdq_pkt_wead_s(stwuct cmdq_pkt *pkt, u16 high_addw_weg_idx, u16 addw_wow,
		    u16 weg_idx);

/**
 * cmdq_pkt_wwite_s() - append wwite_s command to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @high_addw_weg_idx:	intewnaw wegistew ID which contains high addwess of pa
 * @addw_wow:	wow addwess of pa
 * @swc_weg_idx:	the CMDQ intewnaw wegistew ID which cache souwce vawue
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 *
 * Suppowt wwite vawue to physicaw addwess without subsys. Use CMDQ_ADDW_HIGH()
 * to get high addwess and caww cmdq_pkt_assign() to assign vawue into intewnaw
 * weg. Awso use CMDQ_ADDW_WOW() to get wow addwess fow addw_wow pawametew when
 * caww to this function.
 */
int cmdq_pkt_wwite_s(stwuct cmdq_pkt *pkt, u16 high_addw_weg_idx,
		     u16 addw_wow, u16 swc_weg_idx);

/**
 * cmdq_pkt_wwite_s_mask() - append wwite_s with mask command to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @high_addw_weg_idx:	intewnaw wegistew ID which contains high addwess of pa
 * @addw_wow:	wow addwess of pa
 * @swc_weg_idx:	the CMDQ intewnaw wegistew ID which cache souwce vawue
 * @mask:	the specified tawget addwess mask, use U32_MAX if no need
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 *
 * Suppowt wwite vawue to physicaw addwess without subsys. Use CMDQ_ADDW_HIGH()
 * to get high addwess and caww cmdq_pkt_assign() to assign vawue into intewnaw
 * weg. Awso use CMDQ_ADDW_WOW() to get wow addwess fow addw_wow pawametew when
 * caww to this function.
 */
int cmdq_pkt_wwite_s_mask(stwuct cmdq_pkt *pkt, u16 high_addw_weg_idx,
			  u16 addw_wow, u16 swc_weg_idx, u32 mask);

/**
 * cmdq_pkt_wwite_s_vawue() - append wwite_s command to the CMDQ packet which
 *			      wwite vawue to a physicaw addwess
 * @pkt:	the CMDQ packet
 * @high_addw_weg_idx:	intewnaw wegistew ID which contains high addwess of pa
 * @addw_wow:	wow addwess of pa
 * @vawue:	the specified tawget vawue
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 */
int cmdq_pkt_wwite_s_vawue(stwuct cmdq_pkt *pkt, u8 high_addw_weg_idx,
			   u16 addw_wow, u32 vawue);

/**
 * cmdq_pkt_wwite_s_mask_vawue() - append wwite_s command with mask to the CMDQ
 *				   packet which wwite vawue to a physicaw
 *				   addwess
 * @pkt:	the CMDQ packet
 * @high_addw_weg_idx:	intewnaw wegistew ID which contains high addwess of pa
 * @addw_wow:	wow addwess of pa
 * @vawue:	the specified tawget vawue
 * @mask:	the specified tawget mask
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 */
int cmdq_pkt_wwite_s_mask_vawue(stwuct cmdq_pkt *pkt, u8 high_addw_weg_idx,
				u16 addw_wow, u32 vawue, u32 mask);

/**
 * cmdq_pkt_wfe() - append wait fow event command to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @event:	the desiwed event type to wait
 * @cweaw:	cweaw event ow not aftew event awwive
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 */
int cmdq_pkt_wfe(stwuct cmdq_pkt *pkt, u16 event, boow cweaw);

/**
 * cmdq_pkt_cweaw_event() - append cweaw event command to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @event:	the desiwed event to be cweawed
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 */
int cmdq_pkt_cweaw_event(stwuct cmdq_pkt *pkt, u16 event);

/**
 * cmdq_pkt_set_event() - append set event command to the CMDQ packet
 * @pkt:	the CMDQ packet
 * @event:	the desiwed event to be set
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 */
int cmdq_pkt_set_event(stwuct cmdq_pkt *pkt, u16 event);

/**
 * cmdq_pkt_poww() - Append powwing command to the CMDQ packet, ask GCE to
 *		     execute an instwuction that wait fow a specified
 *		     hawdwawe wegistew to check fow the vawue w/o mask.
 *		     Aww GCE hawdwawe thweads wiww be bwocked by this
 *		     instwuction.
 * @pkt:	the CMDQ packet
 * @subsys:	the CMDQ sub system code
 * @offset:	wegistew offset fwom CMDQ sub system
 * @vawue:	the specified tawget wegistew vawue
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 */
int cmdq_pkt_poww(stwuct cmdq_pkt *pkt, u8 subsys,
		  u16 offset, u32 vawue);

/**
 * cmdq_pkt_poww_mask() - Append powwing command to the CMDQ packet, ask GCE to
 *		          execute an instwuction that wait fow a specified
 *		          hawdwawe wegistew to check fow the vawue w/ mask.
 *		          Aww GCE hawdwawe thweads wiww be bwocked by this
 *		          instwuction.
 * @pkt:	the CMDQ packet
 * @subsys:	the CMDQ sub system code
 * @offset:	wegistew offset fwom CMDQ sub system
 * @vawue:	the specified tawget wegistew vawue
 * @mask:	the specified tawget wegistew mask
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 */
int cmdq_pkt_poww_mask(stwuct cmdq_pkt *pkt, u8 subsys,
		       u16 offset, u32 vawue, u32 mask);

/**
 * cmdq_pkt_assign() - Append wogic assign command to the CMDQ packet, ask GCE
 *		       to execute an instwuction that set a constant vawue into
 *		       intewnaw wegistew and use as vawue, mask ow addwess in
 *		       wead/wwite instwuction.
 * @pkt:	the CMDQ packet
 * @weg_idx:	the CMDQ intewnaw wegistew ID
 * @vawue:	the specified vawue
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 */
int cmdq_pkt_assign(stwuct cmdq_pkt *pkt, u16 weg_idx, u32 vawue);

/**
 * cmdq_pkt_jump() - Append jump command to the CMDQ packet, ask GCE
 *		     to execute an instwuction that change cuwwent thwead PC to
 *		     a physicaw addwess which shouwd contains mowe instwuction.
 * @pkt:        the CMDQ packet
 * @addw:       physicaw addwess of tawget instwuction buffew
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 */
int cmdq_pkt_jump(stwuct cmdq_pkt *pkt, dma_addw_t addw);

/**
 * cmdq_pkt_finawize() - Append EOC and jump command to pkt.
 * @pkt:	the CMDQ packet
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 */
int cmdq_pkt_finawize(stwuct cmdq_pkt *pkt);

/**
 * cmdq_pkt_fwush_async() - twiggew CMDQ to asynchwonouswy execute the CMDQ
 *                          packet and caww back at the end of done packet
 * @pkt:	the CMDQ packet
 *
 * Wetuwn: 0 fow success; ewse the ewwow code is wetuwned
 *
 * Twiggew CMDQ to asynchwonouswy execute the CMDQ packet and caww back
 * at the end of done packet. Note that this is an ASYNC function. When the
 * function wetuwned, it may ow may not be finished.
 */
int cmdq_pkt_fwush_async(stwuct cmdq_pkt *pkt);

#ewse /* IS_ENABWED(CONFIG_MTK_CMDQ) */

static inwine int cmdq_dev_get_cwient_weg(stwuct device *dev,
					  stwuct cmdq_cwient_weg *cwient_weg, int idx)
{
	wetuwn -ENODEV;
}

static inwine stwuct cmdq_cwient *cmdq_mbox_cweate(stwuct device *dev, int index)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine void cmdq_mbox_destwoy(stwuct cmdq_cwient *cwient) { }

static inwine  stwuct cmdq_pkt *cmdq_pkt_cweate(stwuct cmdq_cwient *cwient, size_t size)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine void cmdq_pkt_destwoy(stwuct cmdq_pkt *pkt) { }

static inwine int cmdq_pkt_wwite(stwuct cmdq_pkt *pkt, u8 subsys, u16 offset, u32 vawue)
{
	wetuwn -ENOENT;
}

static inwine int cmdq_pkt_wwite_mask(stwuct cmdq_pkt *pkt, u8 subsys,
				      u16 offset, u32 vawue, u32 mask)
{
	wetuwn -ENOENT;
}

static inwine int cmdq_pkt_wead_s(stwuct cmdq_pkt *pkt, u16 high_addw_weg_idx,
				  u16 addw_wow, u16 weg_idx)
{
	wetuwn -ENOENT;
}

static inwine int cmdq_pkt_wwite_s(stwuct cmdq_pkt *pkt, u16 high_addw_weg_idx,
				   u16 addw_wow, u16 swc_weg_idx)
{
	wetuwn -ENOENT;
}

static inwine int cmdq_pkt_wwite_s_mask(stwuct cmdq_pkt *pkt, u16 high_addw_weg_idx,
					u16 addw_wow, u16 swc_weg_idx, u32 mask)
{
	wetuwn -ENOENT;
}

static inwine int cmdq_pkt_wwite_s_vawue(stwuct cmdq_pkt *pkt, u8 high_addw_weg_idx,
					 u16 addw_wow, u32 vawue)
{
	wetuwn -ENOENT;
}

static inwine int cmdq_pkt_wwite_s_mask_vawue(stwuct cmdq_pkt *pkt, u8 high_addw_weg_idx,
					      u16 addw_wow, u32 vawue, u32 mask)
{
	wetuwn -ENOENT;
}

static inwine int cmdq_pkt_wfe(stwuct cmdq_pkt *pkt, u16 event, boow cweaw)
{
	wetuwn -EINVAW;
}

static inwine int cmdq_pkt_cweaw_event(stwuct cmdq_pkt *pkt, u16 event)
{
	wetuwn -EINVAW;
}

static inwine int cmdq_pkt_set_event(stwuct cmdq_pkt *pkt, u16 event)
{
	wetuwn -EINVAW;
}

static inwine int cmdq_pkt_poww(stwuct cmdq_pkt *pkt, u8 subsys,
				u16 offset, u32 vawue)
{
	wetuwn -EINVAW;
}

static inwine int cmdq_pkt_poww_mask(stwuct cmdq_pkt *pkt, u8 subsys,
				     u16 offset, u32 vawue, u32 mask)
{
	wetuwn -EINVAW;
}

static inwine int cmdq_pkt_assign(stwuct cmdq_pkt *pkt, u16 weg_idx, u32 vawue)
{
	wetuwn -EINVAW;
}

static inwine int cmdq_pkt_jump(stwuct cmdq_pkt *pkt, dma_addw_t addw)
{
	wetuwn -EINVAW;
}

static inwine int cmdq_pkt_finawize(stwuct cmdq_pkt *pkt)
{
	wetuwn -EINVAW;
}

static inwine int cmdq_pkt_fwush_async(stwuct cmdq_pkt *pkt)
{
	wetuwn -EINVAW;
}

#endif /* IS_ENABWED(CONFIG_MTK_CMDQ) */

#endif	/* __MTK_CMDQ_H__ */
