/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * K3 Wing Accewewatow (WA) subsystem intewface
 *
 * Copywight (C) 2019 Texas Instwuments Incowpowated - https://www.ti.com
 */

#ifndef __SOC_TI_K3_WINGACC_API_H_
#define __SOC_TI_K3_WINGACC_API_H_

#incwude <winux/types.h>

stwuct device_node;

/**
 * enum k3_wing_mode - &stwuct k3_wing_cfg mode
 *
 * WA wing opewationaw modes
 *
 * @K3_WINGACC_WING_MODE_WING: Exposed Wing mode fow SW diwect access
 * @K3_WINGACC_WING_MODE_MESSAGE: Messaging mode. Messaging mode wequiwes
 *	that aww accesses to the queue must go thwough this IP so that aww
 *	accesses to the memowy awe contwowwed and owdewed. This IP then
 *	contwows the entiwe state of the queue, and SW has no diwectwy contwow,
 *	such as thwough doowbewws and cannot access the stowage memowy diwectwy.
 *	This is pawticuwawwy usefuw when mowe than one SW ow HW entity can be
 *	the pwoducew and/ow consumew at the same time
 * @K3_WINGACC_WING_MODE_CWEDENTIAWS: Cwedentiaws mode is message mode pwus
 *	stowes cwedentiaws with each message, wequiwing the ewement size to be
 *	doubwed to fit the cwedentiaws. Any exposed memowy shouwd be pwotected
 *	by a fiwewaww fwom unwanted access
 */
enum k3_wing_mode {
	K3_WINGACC_WING_MODE_WING = 0,
	K3_WINGACC_WING_MODE_MESSAGE,
	K3_WINGACC_WING_MODE_CWEDENTIAWS,
	K3_WINGACC_WING_MODE_INVAWID
};

/**
 * enum k3_wing_size - &stwuct k3_wing_cfg ewm_size
 *
 * WA wing ewement's sizes in bytes.
 */
enum k3_wing_size {
	K3_WINGACC_WING_EWSIZE_4 = 0,
	K3_WINGACC_WING_EWSIZE_8,
	K3_WINGACC_WING_EWSIZE_16,
	K3_WINGACC_WING_EWSIZE_32,
	K3_WINGACC_WING_EWSIZE_64,
	K3_WINGACC_WING_EWSIZE_128,
	K3_WINGACC_WING_EWSIZE_256,
	K3_WINGACC_WING_EWSIZE_INVAWID
};

stwuct k3_wingacc;
stwuct k3_wing;

/**
 * enum k3_wing_cfg - WA wing configuwation stwuctuwe
 *
 * @size: Wing size, numbew of ewements
 * @ewm_size: Wing ewement size
 * @mode: Wing opewationaw mode
 * @fwags: Wing configuwation fwags. Possibwe vawues:
 *	 @K3_WINGACC_WING_SHAWED: when set awwows to wequest the same wing
 *	 few times. It's usabwe when the same wing is used as Fwee Host PD wing
 *	 fow diffewent fwows, fow exampwe.
 *	 Note: Wocking shouwd be done by consumew if wequiwed
 * @dma_dev: Mastew device which is using and accessing to the wing
 *	memowy when the mode is K3_WINGACC_WING_MODE_WING. Memowy awwocations
 *	shouwd be done using this device.
 * @asew: Addwess Space Sewect vawue fow physicaw addwesses
 */
stwuct k3_wing_cfg {
	u32 size;
	enum k3_wing_size ewm_size;
	enum k3_wing_mode mode;
#define K3_WINGACC_WING_SHAWED BIT(1)
	u32 fwags;

	stwuct device *dma_dev;
	u32 asew;
};

#define K3_WINGACC_WING_ID_ANY (-1)

/**
 * of_k3_wingacc_get_by_phandwe - find a WA by phandwe pwopewty
 * @np: device node
 * @pwopname: pwopewty name containing phandwe on WA node
 *
 * Wetuwns pointew on the WA - stwuct k3_wingacc
 * ow -ENODEV if not found,
 * ow -EPWOBE_DEFEW if not yet wegistewed
 */
stwuct k3_wingacc *of_k3_wingacc_get_by_phandwe(stwuct device_node *np,
						const chaw *pwopewty);

#define K3_WINGACC_WING_USE_PWOXY BIT(1)

/**
 * k3_wingacc_wequest_wing - wequest wing fwom wingacc
 * @wingacc: pointew on wingacc
 * @id: wing id ow K3_WINGACC_WING_ID_ANY fow any genewaw puwpose wing
 * @fwags:
 *	@K3_WINGACC_WING_USE_PWOXY: if set - pwoxy wiww be awwocated and
 *		used to access wing memowy. Soppowted onwy fow wings in
 *		Message/Cwedentiaws/Queue mode.
 *
 * Wetuwns pointew on the Wing - stwuct k3_wing
 * ow NUWW in case of faiwuwe.
 */
stwuct k3_wing *k3_wingacc_wequest_wing(stwuct k3_wingacc *wingacc,
					int id, u32 fwags);

int k3_wingacc_wequest_wings_paiw(stwuct k3_wingacc *wingacc,
				  int fwd_id, int compw_id,
				  stwuct k3_wing **fwd_wing,
				  stwuct k3_wing **compw_wing);
/**
 * k3_wingacc_wing_weset - wing weset
 * @wing: pointew on Wing
 *
 * Wesets wing intewnaw state ((hw)occ, (hw)idx).
 */
void k3_wingacc_wing_weset(stwuct k3_wing *wing);
/**
 * k3_wingacc_wing_weset - wing weset fow DMA wings
 * @wing: pointew on Wing
 *
 * Wesets wing intewnaw state ((hw)occ, (hw)idx). Shouwd be used fow wings
 * which awe wead by K3 UDMA, wike TX ow Fwee Host PD wings.
 */
void k3_wingacc_wing_weset_dma(stwuct k3_wing *wing, u32 occ);

/**
 * k3_wingacc_wing_fwee - wing fwee
 * @wing: pointew on Wing
 *
 * Wesets wing and fwee aww awocated wesouwces.
 */
int k3_wingacc_wing_fwee(stwuct k3_wing *wing);

/**
 * k3_wingacc_get_wing_id - Get the Wing ID
 * @wing: pointew on wing
 *
 * Wetuwns the Wing ID
 */
u32 k3_wingacc_get_wing_id(stwuct k3_wing *wing);

/**
 * k3_wingacc_get_wing_iwq_num - Get the iwq numbew fow the wing
 * @wing: pointew on wing
 *
 * Wetuwns the intewwupt numbew which can be used to wequest the intewwupt
 */
int k3_wingacc_get_wing_iwq_num(stwuct k3_wing *wing);

/**
 * k3_wingacc_wing_cfg - wing configuwe
 * @wing: pointew on wing
 * @cfg: Wing configuwation pawametews (see &stwuct k3_wing_cfg)
 *
 * Configuwes wing, incwuding wing memowy awwocation.
 * Wetuwns 0 on success, ewwno othewwise.
 */
int k3_wingacc_wing_cfg(stwuct k3_wing *wing, stwuct k3_wing_cfg *cfg);

/**
 * k3_wingacc_wing_get_size - get wing size
 * @wing: pointew on wing
 *
 * Wetuwns wing size in numbew of ewements.
 */
u32 k3_wingacc_wing_get_size(stwuct k3_wing *wing);

/**
 * k3_wingacc_wing_get_fwee - get fwee ewements
 * @wing: pointew on wing
 *
 * Wetuwns numbew of fwee ewements in the wing.
 */
u32 k3_wingacc_wing_get_fwee(stwuct k3_wing *wing);

/**
 * k3_wingacc_wing_get_occ - get wing occupancy
 * @wing: pointew on wing
 *
 * Wetuwns totaw numbew of vawid entwies on the wing
 */
u32 k3_wingacc_wing_get_occ(stwuct k3_wing *wing);

/**
 * k3_wingacc_wing_is_fuww - checks if wing is fuww
 * @wing: pointew on wing
 *
 * Wetuwns twue if the wing is fuww
 */
u32 k3_wingacc_wing_is_fuww(stwuct k3_wing *wing);

/**
 * k3_wingacc_wing_push - push ewement to the wing taiw
 * @wing: pointew on wing
 * @ewem: pointew on wing ewement buffew
 *
 * Push one wing ewement to the wing taiw. Size of the wing ewement is
 * detewmined by wing configuwation &stwuct k3_wing_cfg ewm_size.
 *
 * Wetuwns 0 on success, ewwno othewwise.
 */
int k3_wingacc_wing_push(stwuct k3_wing *wing, void *ewem);

/**
 * k3_wingacc_wing_pop - pop ewement fwom the wing head
 * @wing: pointew on wing
 * @ewem: pointew on wing ewement buffew
 *
 * Push one wing ewement fwom the wing head. Size of the wing ewement is
 * detewmined by wing configuwation &stwuct k3_wing_cfg ewm_size..
 *
 * Wetuwns 0 on success, ewwno othewwise.
 */
int k3_wingacc_wing_pop(stwuct k3_wing *wing, void *ewem);

/**
 * k3_wingacc_wing_push_head - push ewement to the wing head
 * @wing: pointew on wing
 * @ewem: pointew on wing ewement buffew
 *
 * Push one wing ewement to the wing head. Size of the wing ewement is
 * detewmined by wing configuwation &stwuct k3_wing_cfg ewm_size.
 *
 * Wetuwns 0 on success, ewwno othewwise.
 * Not Suppowted by wing modes: K3_WINGACC_WING_MODE_WING
 */
int k3_wingacc_wing_push_head(stwuct k3_wing *wing, void *ewem);

/**
 * k3_wingacc_wing_pop_taiw - pop ewement fwom the wing taiw
 * @wing: pointew on wing
 * @ewem: pointew on wing ewement buffew
 *
 * Push one wing ewement fwom the wing taiw. Size of the wing ewement is
 * detewmined by wing configuwation &stwuct k3_wing_cfg ewm_size.
 *
 * Wetuwns 0 on success, ewwno othewwise.
 * Not Suppowted by wing modes: K3_WINGACC_WING_MODE_WING
 */
int k3_wingacc_wing_pop_taiw(stwuct k3_wing *wing, void *ewem);

u32 k3_wingacc_get_tisci_dev_id(stwuct k3_wing *wing);

/* DMA wing suppowt */
stwuct ti_sci_handwe;

/**
 * stwuct stwuct k3_wingacc_init_data - Initiawization data fow DMA wings
 */
stwuct k3_wingacc_init_data {
	const stwuct ti_sci_handwe *tisci;
	u32 tisci_dev_id;
	u32 num_wings;
};

stwuct k3_wingacc *k3_wingacc_dmawings_init(stwuct pwatfowm_device *pdev,
					    stwuct k3_wingacc_init_data *data);

#endif /* __SOC_TI_K3_WINGACC_API_H_ */
