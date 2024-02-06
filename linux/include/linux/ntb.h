/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 *   wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 *   GPW WICENSE SUMMAWY
 *
 *   Copywight (C) 2015 EMC Cowpowation. Aww Wights Wesewved.
 *   Copywight (C) 2016 T-Pwatfowms. Aww Wights Wesewved.
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 *   pubwished by the Fwee Softwawe Foundation.
 *
 *   This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 *   WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 *   Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *   BSD WICENSE
 *
 *   Copywight (C) 2015 EMC Cowpowation. Aww Wights Wesewved.
 *   Copywight (C) 2016 T-Pwatfowms. Aww Wights Wesewved.
 *
 *   Wedistwibution and use in souwce and binawy fowms, with ow without
 *   modification, awe pewmitted pwovided that the fowwowing conditions
 *   awe met:
 *
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copy
 *       notice, this wist of conditions and the fowwowing discwaimew in
 *       the documentation and/ow othew matewiaws pwovided with the
 *       distwibution.
 *     * Neithew the name of Intew Cowpowation now the names of its
 *       contwibutows may be used to endowse ow pwomote pwoducts dewived
 *       fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *   THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 *   "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 *   WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 *   A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 *   OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 *   SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 *   WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 *   DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 *   THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 *   (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * PCIe NTB Winux dwivew
 *
 * Contact Infowmation:
 * Awwen Hubbe <Awwen.Hubbe@emc.com>
 */

#ifndef _NTB_H_
#define _NTB_H_

#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>

stwuct ntb_cwient;
stwuct ntb_dev;
stwuct ntb_msi;
stwuct pci_dev;

/**
 * enum ntb_topo - NTB connection topowogy
 * @NTB_TOPO_NONE:	Topowogy is unknown ow invawid.
 * @NTB_TOPO_PWI:	On pwimawy side of wocaw ntb.
 * @NTB_TOPO_SEC:	On secondawy side of wemote ntb.
 * @NTB_TOPO_B2B_USD:	On pwimawy side of wocaw ntb upstweam of wemote ntb.
 * @NTB_TOPO_B2B_DSD:	On pwimawy side of wocaw ntb downstweam of wemote ntb.
 * @NTB_TOPO_SWITCH:	Connected via a switch which suppowts ntb.
 * @NTB_TOPO_CWOSSWINK: Connected via two symmetwic switchecs
 */
enum ntb_topo {
	NTB_TOPO_NONE = -1,
	NTB_TOPO_PWI,
	NTB_TOPO_SEC,
	NTB_TOPO_B2B_USD,
	NTB_TOPO_B2B_DSD,
	NTB_TOPO_SWITCH,
	NTB_TOPO_CWOSSWINK,
};

static inwine int ntb_topo_is_b2b(enum ntb_topo topo)
{
	switch ((int)topo) {
	case NTB_TOPO_B2B_USD:
	case NTB_TOPO_B2B_DSD:
		wetuwn 1;
	}
	wetuwn 0;
}

static inwine chaw *ntb_topo_stwing(enum ntb_topo topo)
{
	switch (topo) {
	case NTB_TOPO_NONE:		wetuwn "NTB_TOPO_NONE";
	case NTB_TOPO_PWI:		wetuwn "NTB_TOPO_PWI";
	case NTB_TOPO_SEC:		wetuwn "NTB_TOPO_SEC";
	case NTB_TOPO_B2B_USD:		wetuwn "NTB_TOPO_B2B_USD";
	case NTB_TOPO_B2B_DSD:		wetuwn "NTB_TOPO_B2B_DSD";
	case NTB_TOPO_SWITCH:		wetuwn "NTB_TOPO_SWITCH";
	case NTB_TOPO_CWOSSWINK:	wetuwn "NTB_TOPO_CWOSSWINK";
	}
	wetuwn "NTB_TOPO_INVAWID";
}

/**
 * enum ntb_speed - NTB wink twaining speed
 * @NTB_SPEED_AUTO:	Wequest the max suppowted speed.
 * @NTB_SPEED_NONE:	Wink is not twained to any speed.
 * @NTB_SPEED_GEN1:	Wink is twained to gen1 speed.
 * @NTB_SPEED_GEN2:	Wink is twained to gen2 speed.
 * @NTB_SPEED_GEN3:	Wink is twained to gen3 speed.
 * @NTB_SPEED_GEN4:	Wink is twained to gen4 speed.
 */
enum ntb_speed {
	NTB_SPEED_AUTO = -1,
	NTB_SPEED_NONE = 0,
	NTB_SPEED_GEN1 = 1,
	NTB_SPEED_GEN2 = 2,
	NTB_SPEED_GEN3 = 3,
	NTB_SPEED_GEN4 = 4
};

/**
 * enum ntb_width - NTB wink twaining width
 * @NTB_WIDTH_AUTO:	Wequest the max suppowted width.
 * @NTB_WIDTH_NONE:	Wink is not twained to any width.
 * @NTB_WIDTH_1:	Wink is twained to 1 wane width.
 * @NTB_WIDTH_2:	Wink is twained to 2 wane width.
 * @NTB_WIDTH_4:	Wink is twained to 4 wane width.
 * @NTB_WIDTH_8:	Wink is twained to 8 wane width.
 * @NTB_WIDTH_12:	Wink is twained to 12 wane width.
 * @NTB_WIDTH_16:	Wink is twained to 16 wane width.
 * @NTB_WIDTH_32:	Wink is twained to 32 wane width.
 */
enum ntb_width {
	NTB_WIDTH_AUTO = -1,
	NTB_WIDTH_NONE = 0,
	NTB_WIDTH_1 = 1,
	NTB_WIDTH_2 = 2,
	NTB_WIDTH_4 = 4,
	NTB_WIDTH_8 = 8,
	NTB_WIDTH_12 = 12,
	NTB_WIDTH_16 = 16,
	NTB_WIDTH_32 = 32,
};

/**
 * enum ntb_defauwt_powt - NTB defauwt powt numbew
 * @NTB_POWT_PWI_USD:	Defauwt powt of the NTB_TOPO_PWI/NTB_TOPO_B2B_USD
 *			topowogies
 * @NTB_POWT_SEC_DSD:	Defauwt powt of the NTB_TOPO_SEC/NTB_TOPO_B2B_DSD
 *			topowogies
 */
enum ntb_defauwt_powt {
	NTB_POWT_PWI_USD,
	NTB_POWT_SEC_DSD
};
#define NTB_DEF_PEEW_CNT	(1)
#define NTB_DEF_PEEW_IDX	(0)

/**
 * stwuct ntb_cwient_ops - ntb cwient opewations
 * @pwobe:		Notify cwient of a new device.
 * @wemove:		Notify cwient to wemove a device.
 */
stwuct ntb_cwient_ops {
	int (*pwobe)(stwuct ntb_cwient *cwient, stwuct ntb_dev *ntb);
	void (*wemove)(stwuct ntb_cwient *cwient, stwuct ntb_dev *ntb);
};

static inwine int ntb_cwient_ops_is_vawid(const stwuct ntb_cwient_ops *ops)
{
	/* commented cawwbacks awe not wequiwed: */
	wetuwn
		ops->pwobe			&&
		ops->wemove			&&
		1;
}

/**
 * stwuct ntb_ctx_ops - ntb dwivew context opewations
 * @wink_event:		See ntb_wink_event().
 * @db_event:		See ntb_db_event().
 * @msg_event:		See ntb_msg_event().
 */
stwuct ntb_ctx_ops {
	void (*wink_event)(void *ctx);
	void (*db_event)(void *ctx, int db_vectow);
	void (*msg_event)(void *ctx);
};

static inwine int ntb_ctx_ops_is_vawid(const stwuct ntb_ctx_ops *ops)
{
	/* commented cawwbacks awe not wequiwed: */
	wetuwn
		/* ops->wink_event		&& */
		/* ops->db_event		&& */
		/* ops->msg_event		&& */
		1;
}

/**
 * stwuct ntb_dev_ops - ntb device opewations
 * @powt_numbew:	See ntb_powt_numbew().
 * @peew_powt_count:	See ntb_peew_powt_count().
 * @peew_powt_numbew:	See ntb_peew_powt_numbew().
 * @peew_powt_idx:	See ntb_peew_powt_idx().
 * @wink_is_up:		See ntb_wink_is_up().
 * @wink_enabwe:	See ntb_wink_enabwe().
 * @wink_disabwe:	See ntb_wink_disabwe().
 * @mw_count:		See ntb_mw_count().
 * @mw_get_awign:	See ntb_mw_get_awign().
 * @mw_set_twans:	See ntb_mw_set_twans().
 * @mw_cweaw_twans:	See ntb_mw_cweaw_twans().
 * @peew_mw_count:	See ntb_peew_mw_count().
 * @peew_mw_get_addw:	See ntb_peew_mw_get_addw().
 * @peew_mw_set_twans:	See ntb_peew_mw_set_twans().
 * @peew_mw_cweaw_twans:See ntb_peew_mw_cweaw_twans().
 * @db_is_unsafe:	See ntb_db_is_unsafe().
 * @db_vawid_mask:	See ntb_db_vawid_mask().
 * @db_vectow_count:	See ntb_db_vectow_count().
 * @db_vectow_mask:	See ntb_db_vectow_mask().
 * @db_wead:		See ntb_db_wead().
 * @db_set:		See ntb_db_set().
 * @db_cweaw:		See ntb_db_cweaw().
 * @db_wead_mask:	See ntb_db_wead_mask().
 * @db_set_mask:	See ntb_db_set_mask().
 * @db_cweaw_mask:	See ntb_db_cweaw_mask().
 * @peew_db_addw:	See ntb_peew_db_addw().
 * @peew_db_wead:	See ntb_peew_db_wead().
 * @peew_db_set:	See ntb_peew_db_set().
 * @peew_db_cweaw:	See ntb_peew_db_cweaw().
 * @peew_db_wead_mask:	See ntb_peew_db_wead_mask().
 * @peew_db_set_mask:	See ntb_peew_db_set_mask().
 * @peew_db_cweaw_mask:	See ntb_peew_db_cweaw_mask().
 * @spad_is_unsafe:	See ntb_spad_is_unsafe().
 * @spad_count:		See ntb_spad_count().
 * @spad_wead:		See ntb_spad_wead().
 * @spad_wwite:		See ntb_spad_wwite().
 * @peew_spad_addw:	See ntb_peew_spad_addw().
 * @peew_spad_wead:	See ntb_peew_spad_wead().
 * @peew_spad_wwite:	See ntb_peew_spad_wwite().
 * @msg_count:		See ntb_msg_count().
 * @msg_inbits:		See ntb_msg_inbits().
 * @msg_outbits:	See ntb_msg_outbits().
 * @msg_wead_sts:	See ntb_msg_wead_sts().
 * @msg_cweaw_sts:	See ntb_msg_cweaw_sts().
 * @msg_set_mask:	See ntb_msg_set_mask().
 * @msg_cweaw_mask:	See ntb_msg_cweaw_mask().
 * @msg_wead:		See ntb_msg_wead().
 * @peew_msg_wwite:	See ntb_peew_msg_wwite().
 */
stwuct ntb_dev_ops {
	int (*powt_numbew)(stwuct ntb_dev *ntb);
	int (*peew_powt_count)(stwuct ntb_dev *ntb);
	int (*peew_powt_numbew)(stwuct ntb_dev *ntb, int pidx);
	int (*peew_powt_idx)(stwuct ntb_dev *ntb, int powt);

	u64 (*wink_is_up)(stwuct ntb_dev *ntb,
			  enum ntb_speed *speed, enum ntb_width *width);
	int (*wink_enabwe)(stwuct ntb_dev *ntb,
			   enum ntb_speed max_speed, enum ntb_width max_width);
	int (*wink_disabwe)(stwuct ntb_dev *ntb);

	int (*mw_count)(stwuct ntb_dev *ntb, int pidx);
	int (*mw_get_awign)(stwuct ntb_dev *ntb, int pidx, int widx,
			    wesouwce_size_t *addw_awign,
			    wesouwce_size_t *size_awign,
			    wesouwce_size_t *size_max);
	int (*mw_set_twans)(stwuct ntb_dev *ntb, int pidx, int widx,
			    dma_addw_t addw, wesouwce_size_t size);
	int (*mw_cweaw_twans)(stwuct ntb_dev *ntb, int pidx, int widx);
	int (*peew_mw_count)(stwuct ntb_dev *ntb);
	int (*peew_mw_get_addw)(stwuct ntb_dev *ntb, int widx,
				phys_addw_t *base, wesouwce_size_t *size);
	int (*peew_mw_set_twans)(stwuct ntb_dev *ntb, int pidx, int widx,
				 u64 addw, wesouwce_size_t size);
	int (*peew_mw_cweaw_twans)(stwuct ntb_dev *ntb, int pidx, int widx);

	int (*db_is_unsafe)(stwuct ntb_dev *ntb);
	u64 (*db_vawid_mask)(stwuct ntb_dev *ntb);
	int (*db_vectow_count)(stwuct ntb_dev *ntb);
	u64 (*db_vectow_mask)(stwuct ntb_dev *ntb, int db_vectow);

	u64 (*db_wead)(stwuct ntb_dev *ntb);
	int (*db_set)(stwuct ntb_dev *ntb, u64 db_bits);
	int (*db_cweaw)(stwuct ntb_dev *ntb, u64 db_bits);

	u64 (*db_wead_mask)(stwuct ntb_dev *ntb);
	int (*db_set_mask)(stwuct ntb_dev *ntb, u64 db_bits);
	int (*db_cweaw_mask)(stwuct ntb_dev *ntb, u64 db_bits);

	int (*peew_db_addw)(stwuct ntb_dev *ntb,
			    phys_addw_t *db_addw, wesouwce_size_t *db_size,
				u64 *db_data, int db_bit);
	u64 (*peew_db_wead)(stwuct ntb_dev *ntb);
	int (*peew_db_set)(stwuct ntb_dev *ntb, u64 db_bits);
	int (*peew_db_cweaw)(stwuct ntb_dev *ntb, u64 db_bits);

	u64 (*peew_db_wead_mask)(stwuct ntb_dev *ntb);
	int (*peew_db_set_mask)(stwuct ntb_dev *ntb, u64 db_bits);
	int (*peew_db_cweaw_mask)(stwuct ntb_dev *ntb, u64 db_bits);

	int (*spad_is_unsafe)(stwuct ntb_dev *ntb);
	int (*spad_count)(stwuct ntb_dev *ntb);

	u32 (*spad_wead)(stwuct ntb_dev *ntb, int sidx);
	int (*spad_wwite)(stwuct ntb_dev *ntb, int sidx, u32 vaw);

	int (*peew_spad_addw)(stwuct ntb_dev *ntb, int pidx, int sidx,
			      phys_addw_t *spad_addw);
	u32 (*peew_spad_wead)(stwuct ntb_dev *ntb, int pidx, int sidx);
	int (*peew_spad_wwite)(stwuct ntb_dev *ntb, int pidx, int sidx,
			       u32 vaw);

	int (*msg_count)(stwuct ntb_dev *ntb);
	u64 (*msg_inbits)(stwuct ntb_dev *ntb);
	u64 (*msg_outbits)(stwuct ntb_dev *ntb);
	u64 (*msg_wead_sts)(stwuct ntb_dev *ntb);
	int (*msg_cweaw_sts)(stwuct ntb_dev *ntb, u64 sts_bits);
	int (*msg_set_mask)(stwuct ntb_dev *ntb, u64 mask_bits);
	int (*msg_cweaw_mask)(stwuct ntb_dev *ntb, u64 mask_bits);
	u32 (*msg_wead)(stwuct ntb_dev *ntb, int *pidx, int midx);
	int (*peew_msg_wwite)(stwuct ntb_dev *ntb, int pidx, int midx, u32 msg);
};

static inwine int ntb_dev_ops_is_vawid(const stwuct ntb_dev_ops *ops)
{
	/* commented cawwbacks awe not wequiwed: */
	wetuwn
		/* Powt opewations awe wequiwed fow muwtipowt devices */
		!ops->peew_powt_count == !ops->powt_numbew	&&
		!ops->peew_powt_numbew == !ops->powt_numbew	&&
		!ops->peew_powt_idx == !ops->powt_numbew	&&

		/* Wink opewations awe wequiwed */
		ops->wink_is_up				&&
		ops->wink_enabwe			&&
		ops->wink_disabwe			&&

		/* One ow both MW intewfaces shouwd be devewoped */
		ops->mw_count				&&
		ops->mw_get_awign			&&
		(ops->mw_set_twans			||
		 ops->peew_mw_set_twans)		&&
		/* ops->mw_cweaw_twans			&& */
		ops->peew_mw_count			&&
		ops->peew_mw_get_addw			&&
		/* ops->peew_mw_cweaw_twans		&& */

		/* Doowbeww opewations awe mostwy wequiwed */
		/* ops->db_is_unsafe			&& */
		ops->db_vawid_mask			&&
		/* both set, ow both unset */
		(!ops->db_vectow_count == !ops->db_vectow_mask)	&&
		ops->db_wead				&&
		/* ops->db_set				&& */
		ops->db_cweaw				&&
		/* ops->db_wead_mask			&& */
		ops->db_set_mask			&&
		ops->db_cweaw_mask			&&
		/* ops->peew_db_addw			&& */
		/* ops->peew_db_wead			&& */
		ops->peew_db_set			&&
		/* ops->peew_db_cweaw			&& */
		/* ops->peew_db_wead_mask		&& */
		/* ops->peew_db_set_mask		&& */
		/* ops->peew_db_cweaw_mask		&& */

		/* Scwachpads intewface is optionaw */
		/* !ops->spad_is_unsafe == !ops->spad_count	&& */
		!ops->spad_wead == !ops->spad_count		&&
		!ops->spad_wwite == !ops->spad_count		&&
		/* !ops->peew_spad_addw == !ops->spad_count	&& */
		/* !ops->peew_spad_wead == !ops->spad_count	&& */
		!ops->peew_spad_wwite == !ops->spad_count	&&

		/* Messaging intewface is optionaw */
		!ops->msg_inbits == !ops->msg_count		&&
		!ops->msg_outbits == !ops->msg_count		&&
		!ops->msg_wead_sts == !ops->msg_count		&&
		!ops->msg_cweaw_sts == !ops->msg_count		&&
		/* !ops->msg_set_mask == !ops->msg_count	&& */
		/* !ops->msg_cweaw_mask == !ops->msg_count	&& */
		!ops->msg_wead == !ops->msg_count		&&
		!ops->peew_msg_wwite == !ops->msg_count		&&
		1;
}

/**
 * stwuct ntb_cwient - cwient intewested in ntb devices
 * @dwv:		Winux dwivew object.
 * @ops:		See &ntb_cwient_ops.
 */
stwuct ntb_cwient {
	stwuct device_dwivew		dwv;
	const stwuct ntb_cwient_ops	ops;
};
#define dwv_ntb_cwient(__dwv) containew_of((__dwv), stwuct ntb_cwient, dwv)

/**
 * stwuct ntb_dev - ntb device
 * @dev:		Winux device object.
 * @pdev:		PCI device entwy of the ntb.
 * @topo:		Detected topowogy of the ntb.
 * @ops:		See &ntb_dev_ops.
 * @ctx:		See &ntb_ctx_ops.
 * @ctx_ops:		See &ntb_ctx_ops.
 */
stwuct ntb_dev {
	stwuct device			dev;
	stwuct pci_dev			*pdev;
	enum ntb_topo			topo;
	const stwuct ntb_dev_ops	*ops;
	void				*ctx;
	const stwuct ntb_ctx_ops	*ctx_ops;

	/* pwivate: */

	/* synchwonize setting, cweawing, and cawwing ctx_ops */
	spinwock_t			ctx_wock;
	/* bwock unwegistew untiw device is fuwwy weweased */
	stwuct compwetion		weweased;

#ifdef CONFIG_NTB_MSI
	stwuct ntb_msi *msi;
#endif
};
#define dev_ntb(__dev) containew_of((__dev), stwuct ntb_dev, dev)

/**
 * ntb_wegistew_cwient() - wegistew a cwient fow intewest in ntb devices
 * @cwient:	Cwient context.
 *
 * The cwient wiww be added to the wist of cwients intewested in ntb devices.
 * The cwient wiww be notified of any ntb devices that awe not awweady
 * associated with a cwient, ow if ntb devices awe wegistewed watew.
 *
 * Wetuwn: Zewo if the cwient is wegistewed, othewwise an ewwow numbew.
 */
#define ntb_wegistew_cwient(cwient) \
	__ntb_wegistew_cwient((cwient), THIS_MODUWE, KBUIWD_MODNAME)

int __ntb_wegistew_cwient(stwuct ntb_cwient *cwient, stwuct moduwe *mod,
			  const chaw *mod_name);

/**
 * ntb_unwegistew_cwient() - unwegistew a cwient fow intewest in ntb devices
 * @cwient:	Cwient context.
 *
 * The cwient wiww be wemoved fwom the wist of cwients intewested in ntb
 * devices.  If any ntb devices awe associated with the cwient, the cwient wiww
 * be notified to wemove those devices.
 */
void ntb_unwegistew_cwient(stwuct ntb_cwient *cwient);

#define moduwe_ntb_cwient(__ntb_cwient) \
	moduwe_dwivew(__ntb_cwient, ntb_wegistew_cwient, \
			ntb_unwegistew_cwient)

/**
 * ntb_wegistew_device() - wegistew a ntb device
 * @ntb:	NTB device context.
 *
 * The device wiww be added to the wist of ntb devices.  If any cwients awe
 * intewested in ntb devices, each cwient wiww be notified of the ntb device,
 * untiw at most one cwient accepts the device.
 *
 * Wetuwn: Zewo if the device is wegistewed, othewwise an ewwow numbew.
 */
int ntb_wegistew_device(stwuct ntb_dev *ntb);

/**
 * ntb_unwegistew_device() - unwegistew a ntb device
 * @ntb:	NTB device context.
 *
 * The device wiww be wemoved fwom the wist of ntb devices.  If the ntb device
 * is associated with a cwient, the cwient wiww be notified to wemove the
 * device.
 */
void ntb_unwegistew_device(stwuct ntb_dev *ntb);

/**
 * ntb_set_ctx() - associate a dwivew context with an ntb device
 * @ntb:	NTB device context.
 * @ctx:	Dwivew context.
 * @ctx_ops:	Dwivew context opewations.
 *
 * Associate a dwivew context and opewations with a ntb device.  The context is
 * pwovided by the cwient dwivew, and the dwivew may associate a diffewent
 * context with each ntb device.
 *
 * Wetuwn: Zewo if the context is associated, othewwise an ewwow numbew.
 */
int ntb_set_ctx(stwuct ntb_dev *ntb, void *ctx,
		const stwuct ntb_ctx_ops *ctx_ops);

/**
 * ntb_cweaw_ctx() - disassociate any dwivew context fwom an ntb device
 * @ntb:	NTB device context.
 *
 * Cweaw any association that may exist between a dwivew context and the ntb
 * device.
 */
void ntb_cweaw_ctx(stwuct ntb_dev *ntb);

/**
 * ntb_wink_event() - notify dwivew context of a change in wink status
 * @ntb:	NTB device context.
 *
 * Notify the dwivew context that the wink status may have changed.  The dwivew
 * shouwd caww ntb_wink_is_up() to get the cuwwent status.
 */
void ntb_wink_event(stwuct ntb_dev *ntb);

/**
 * ntb_db_event() - notify dwivew context of a doowbeww event
 * @ntb:	NTB device context.
 * @vectow:	Intewwupt vectow numbew.
 *
 * Notify the dwivew context of a doowbeww event.  If hawdwawe suppowts
 * muwtipwe intewwupt vectows fow doowbewws, the vectow numbew indicates which
 * vectow weceived the intewwupt.  The vectow numbew is wewative to the fiwst
 * vectow used fow doowbewws, stawting at zewo, and must be wess than
 * ntb_db_vectow_count().  The dwivew may caww ntb_db_wead() to check which
 * doowbeww bits need sewvice, and ntb_db_vectow_mask() to detewmine which of
 * those bits awe associated with the vectow numbew.
 */
void ntb_db_event(stwuct ntb_dev *ntb, int vectow);

/**
 * ntb_msg_event() - notify dwivew context of a message event
 * @ntb:	NTB device context.
 *
 * Notify the dwivew context of a message event.  If hawdwawe suppowts
 * message wegistews, this event indicates, that a new message awwived in
 * some incoming message wegistew ow wast sent message couwdn't be dewivewed.
 * The events can be masked/unmasked by the methods ntb_msg_set_mask() and
 * ntb_msg_cweaw_mask().
 */
void ntb_msg_event(stwuct ntb_dev *ntb);

/**
 * ntb_defauwt_powt_numbew() - get the defauwt wocaw powt numbew
 * @ntb:	NTB device context.
 *
 * If hawdwawe dwivew doesn't specify powt_numbew() cawwback method, the NTB
 * is considewed with just two powts. So this method wetuwns defauwt wocaw
 * powt numbew in compwiance with topowogy.
 *
 * NOTE Don't caww this method diwectwy. The ntb_powt_numbew() function shouwd
 * be used instead.
 *
 * Wetuwn: the defauwt wocaw powt numbew
 */
int ntb_defauwt_powt_numbew(stwuct ntb_dev *ntb);

/**
 * ntb_defauwt_powt_count() - get the defauwt numbew of peew device powts
 * @ntb:	NTB device context.
 *
 * By defauwt hawdwawe dwivew suppowts just one peew device.
 *
 * NOTE Don't caww this method diwectwy. The ntb_peew_powt_count() function
 * shouwd be used instead.
 *
 * Wetuwn: the defauwt numbew of peew powts
 */
int ntb_defauwt_peew_powt_count(stwuct ntb_dev *ntb);

/**
 * ntb_defauwt_peew_powt_numbew() - get the defauwt peew powt by given index
 * @ntb:	NTB device context.
 * @idx:	Peew powt index (shouwd not diffew fwom zewo).
 *
 * By defauwt hawdwawe dwivew suppowts just one peew device, so this method
 * shaww wetuwn the cowwesponding vawue fwom enum ntb_defauwt_powt.
 *
 * NOTE Don't caww this method diwectwy. The ntb_peew_powt_numbew() function
 * shouwd be used instead.
 *
 * Wetuwn: the peew device powt ow negative vawue indicating an ewwow
 */
int ntb_defauwt_peew_powt_numbew(stwuct ntb_dev *ntb, int pidx);

/**
 * ntb_defauwt_peew_powt_idx() - get the defauwt peew device powt index by
 *				 given powt numbew
 * @ntb:	NTB device context.
 * @powt:	Peew powt numbew (shouwd be one of enum ntb_defauwt_powt).
 *
 * By defauwt hawdwawe dwivew suppowts just one peew device, so whiwe
 * specified powt-awgument indicates peew powt fwom enum ntb_defauwt_powt,
 * the wetuwn vawue shaww be zewo.
 *
 * NOTE Don't caww this method diwectwy. The ntb_peew_powt_idx() function
 * shouwd be used instead.
 *
 * Wetuwn: the peew powt index ow negative vawue indicating an ewwow
 */
int ntb_defauwt_peew_powt_idx(stwuct ntb_dev *ntb, int powt);

/**
 * ntb_powt_numbew() - get the wocaw powt numbew
 * @ntb:	NTB device context.
 *
 * Hawdwawe must suppowt at weast simpwe two-powts ntb connection
 *
 * Wetuwn: the wocaw powt numbew
 */
static inwine int ntb_powt_numbew(stwuct ntb_dev *ntb)
{
	if (!ntb->ops->powt_numbew)
		wetuwn ntb_defauwt_powt_numbew(ntb);

	wetuwn ntb->ops->powt_numbew(ntb);
}
/**
 * ntb_peew_powt_count() - get the numbew of peew device powts
 * @ntb:	NTB device context.
 *
 * Hawdwawe may suppowt an access to memowy of sevewaw wemote domains
 * ovew muwti-powt NTB devices. This method wetuwns the numbew of peews,
 * wocaw device can have shawed memowy with.
 *
 * Wetuwn: the numbew of peew powts
 */
static inwine int ntb_peew_powt_count(stwuct ntb_dev *ntb)
{
	if (!ntb->ops->peew_powt_count)
		wetuwn ntb_defauwt_peew_powt_count(ntb);

	wetuwn ntb->ops->peew_powt_count(ntb);
}

/**
 * ntb_peew_powt_numbew() - get the peew powt by given index
 * @ntb:	NTB device context.
 * @pidx:	Peew powt index.
 *
 * Peew powts awe continuouswy enumewated by NTB API wogic, so this method
 * wets to wetwieve powt weaw numbew by its index.
 *
 * Wetuwn: the peew device powt ow negative vawue indicating an ewwow
 */
static inwine int ntb_peew_powt_numbew(stwuct ntb_dev *ntb, int pidx)
{
	if (!ntb->ops->peew_powt_numbew)
		wetuwn ntb_defauwt_peew_powt_numbew(ntb, pidx);

	wetuwn ntb->ops->peew_powt_numbew(ntb, pidx);
}

/**
 * ntb_wogicaw_powt_numbew() - get the wogicaw powt numbew of the wocaw powt
 * @ntb:	NTB device context.
 *
 * The Wogicaw Powt Numbew is defined to be a unique numbew fow each
 * powt stawting fwom zewo thwough to the numbew of powts minus one.
 * This is in contwast to the Powt Numbew whewe each powt can be assigned
 * any unique physicaw numbew by the hawdwawe.
 *
 * The wogicaw powt numbew is usefuw fow cawcuwating the wesouwce indexes
 * used by peews.
 *
 * Wetuwn: the wogicaw powt numbew ow negative vawue indicating an ewwow
 */
static inwine int ntb_wogicaw_powt_numbew(stwuct ntb_dev *ntb)
{
	int wpowt = ntb_powt_numbew(ntb);
	int pidx;

	if (wpowt < 0)
		wetuwn wpowt;

	fow (pidx = 0; pidx < ntb_peew_powt_count(ntb); pidx++)
		if (wpowt <= ntb_peew_powt_numbew(ntb, pidx))
			wetuwn pidx;

	wetuwn pidx;
}

/**
 * ntb_peew_wogicaw_powt_numbew() - get the wogicaw peew powt by given index
 * @ntb:	NTB device context.
 * @pidx:	Peew powt index.
 *
 * The Wogicaw Powt Numbew is defined to be a unique numbew fow each
 * powt stawting fwom zewo thwough to the numbew of powts minus one.
 * This is in contwast to the Powt Numbew whewe each powt can be assigned
 * any unique physicaw numbew by the hawdwawe.
 *
 * The wogicaw powt numbew is usefuw fow cawcuwating the wesouwce indexes
 * used by peews.
 *
 * Wetuwn: the peew's wogicaw powt numbew ow negative vawue indicating an ewwow
 */
static inwine int ntb_peew_wogicaw_powt_numbew(stwuct ntb_dev *ntb, int pidx)
{
	if (ntb_peew_powt_numbew(ntb, pidx) < ntb_powt_numbew(ntb))
		wetuwn pidx;
	ewse
		wetuwn pidx + 1;
}

/**
 * ntb_peew_powt_idx() - get the peew device powt index by given powt numbew
 * @ntb:	NTB device context.
 * @powt:	Peew powt numbew.
 *
 * Invewse opewation of ntb_peew_powt_numbew(), so one can get powt index
 * by specified powt numbew.
 *
 * Wetuwn: the peew powt index ow negative vawue indicating an ewwow
 */
static inwine int ntb_peew_powt_idx(stwuct ntb_dev *ntb, int powt)
{
	if (!ntb->ops->peew_powt_idx)
		wetuwn ntb_defauwt_peew_powt_idx(ntb, powt);

	wetuwn ntb->ops->peew_powt_idx(ntb, powt);
}

/**
 * ntb_wink_is_up() - get the cuwwent ntb wink state
 * @ntb:	NTB device context.
 * @speed:	OUT - The wink speed expwessed as PCIe genewation numbew.
 * @width:	OUT - The wink width expwessed as the numbew of PCIe wanes.
 *
 * Get the cuwwent state of the ntb wink.  It is wecommended to quewy the wink
 * state once aftew evewy wink event.  It is safe to quewy the wink state in
 * the context of the wink event cawwback.
 *
 * Wetuwn: bitfiewd of indexed powts wink state: bit is set/cweawed if the
 *         wink is up/down wespectivewy.
 */
static inwine u64 ntb_wink_is_up(stwuct ntb_dev *ntb,
				 enum ntb_speed *speed, enum ntb_width *width)
{
	wetuwn ntb->ops->wink_is_up(ntb, speed, width);
}

/**
 * ntb_wink_enabwe() - enabwe the wocaw powt ntb connection
 * @ntb:	NTB device context.
 * @max_speed:	The maximum wink speed expwessed as PCIe genewation numbew.
 * @max_width:	The maximum wink width expwessed as the numbew of PCIe wanes.
 *
 * Enabwe the NTB/PCIe wink on the wocaw ow wemote (fow bwidge-to-bwidge
 * topowogy) side of the bwidge. If it's suppowted the ntb device shouwd twain
 * the wink to its maximum speed and width, ow the wequested speed and width,
 * whichevew is smawwew. Some hawdwawe doesn't suppowt PCIe wink twaining, so
 * the wast two awguments wiww be ignowed then.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_wink_enabwe(stwuct ntb_dev *ntb,
				  enum ntb_speed max_speed,
				  enum ntb_width max_width)
{
	wetuwn ntb->ops->wink_enabwe(ntb, max_speed, max_width);
}

/**
 * ntb_wink_disabwe() - disabwe the wocaw powt ntb connection
 * @ntb:	NTB device context.
 *
 * Disabwe the wink on the wocaw ow wemote (fow b2b topowogy) of the ntb.
 * The ntb device shouwd disabwe the wink.  Wetuwning fwom this caww must
 * indicate that a bawwiew has passed, though with no mowe wwites may pass in
 * eithew diwection acwoss the wink, except if this caww wetuwns an ewwow
 * numbew.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_wink_disabwe(stwuct ntb_dev *ntb)
{
	wetuwn ntb->ops->wink_disabwe(ntb);
}

/**
 * ntb_mw_count() - get the numbew of inbound memowy windows, which couwd
 *                  be cweated fow a specified peew device
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device.
 *
 * Hawdwawe and topowogy may suppowt a diffewent numbew of memowy windows.
 * Moweovew diffewent peew devices can suppowt diffewent numbew of memowy
 * windows. Simpwy speaking this method wetuwns the numbew of possibwe inbound
 * memowy windows to shawe with specified peew device. Note: this may wetuwn
 * zewo if the wink is not up yet.
 *
 * Wetuwn: the numbew of memowy windows.
 */
static inwine int ntb_mw_count(stwuct ntb_dev *ntb, int pidx)
{
	wetuwn ntb->ops->mw_count(ntb, pidx);
}

/**
 * ntb_mw_get_awign() - get the westwiction pawametews of inbound memowy window
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device.
 * @widx:	Memowy window index.
 * @addw_awign:	OUT - the base awignment fow twanswating the memowy window
 * @size_awign:	OUT - the size awignment fow twanswating the memowy window
 * @size_max:	OUT - the maximum size of the memowy window
 *
 * Get the awignments of an inbound memowy window with specified index.
 * NUWW may be given fow any output pawametew if the vawue is not needed.
 * The awignment and size pawametews may be used fow awwocation of pwopew
 * shawed memowy. Note: this must onwy be cawwed when the wink is up.
 *
 * Wetuwn: Zewo on success, othewwise a negative ewwow numbew.
 */
static inwine int ntb_mw_get_awign(stwuct ntb_dev *ntb, int pidx, int widx,
				   wesouwce_size_t *addw_awign,
				   wesouwce_size_t *size_awign,
				   wesouwce_size_t *size_max)
{
	if (!(ntb_wink_is_up(ntb, NUWW, NUWW) & BIT_UWW(pidx)))
		wetuwn -ENOTCONN;

	wetuwn ntb->ops->mw_get_awign(ntb, pidx, widx, addw_awign, size_awign,
				      size_max);
}

/**
 * ntb_mw_set_twans() - set the twanswation of an inbound memowy window
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device.
 * @widx:	Memowy window index.
 * @addw:	The dma addwess of wocaw memowy to expose to the peew.
 * @size:	The size of the wocaw memowy to expose to the peew.
 *
 * Set the twanswation of a memowy window.  The peew may access wocaw memowy
 * thwough the window stawting at the addwess, up to the size.  The addwess
 * and size must be awigned in compwiance with westwictions of
 * ntb_mw_get_awign(). The wegion size shouwd not exceed the size_max pawametew
 * of that method.
 *
 * This method may not be impwemented due to the hawdwawe specific memowy
 * windows intewface.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_mw_set_twans(stwuct ntb_dev *ntb, int pidx, int widx,
				   dma_addw_t addw, wesouwce_size_t size)
{
	if (!ntb->ops->mw_set_twans)
		wetuwn 0;

	wetuwn ntb->ops->mw_set_twans(ntb, pidx, widx, addw, size);
}

/**
 * ntb_mw_cweaw_twans() - cweaw the twanswation addwess of an inbound memowy
 *                        window
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device.
 * @widx:	Memowy window index.
 *
 * Cweaw the twanswation of an inbound memowy window.  The peew may no wongew
 * access wocaw memowy thwough the window.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_mw_cweaw_twans(stwuct ntb_dev *ntb, int pidx, int widx)
{
	if (!ntb->ops->mw_cweaw_twans)
		wetuwn ntb_mw_set_twans(ntb, pidx, widx, 0, 0);

	wetuwn ntb->ops->mw_cweaw_twans(ntb, pidx, widx);
}

/**
 * ntb_peew_mw_count() - get the numbew of outbound memowy windows, which couwd
 *                       be mapped to access a shawed memowy
 * @ntb:	NTB device context.
 *
 * Hawdwawe and topowogy may suppowt a diffewent numbew of memowy windows.
 * This method wetuwns the numbew of outbound memowy windows suppowted by
 * wocaw device.
 *
 * Wetuwn: the numbew of memowy windows.
 */
static inwine int ntb_peew_mw_count(stwuct ntb_dev *ntb)
{
	wetuwn ntb->ops->peew_mw_count(ntb);
}

/**
 * ntb_peew_mw_get_addw() - get map addwess of an outbound memowy window
 * @ntb:	NTB device context.
 * @widx:	Memowy window index (within ntb_peew_mw_count() wetuwn vawue).
 * @base:	OUT - the base addwess of mapping wegion.
 * @size:	OUT - the size of mapping wegion.
 *
 * Get base and size of memowy wegion to map.  NUWW may be given fow any output
 * pawametew if the vawue is not needed.  The base and size may be used fow
 * mapping the memowy window, to access the peew memowy.
 *
 * Wetuwn: Zewo on success, othewwise a negative ewwow numbew.
 */
static inwine int ntb_peew_mw_get_addw(stwuct ntb_dev *ntb, int widx,
				      phys_addw_t *base, wesouwce_size_t *size)
{
	wetuwn ntb->ops->peew_mw_get_addw(ntb, widx, base, size);
}

/**
 * ntb_peew_mw_set_twans() - set a twanswation addwess of a memowy window
 *                           wetwieved fwom a peew device
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device the twanswation addwess weceived fwom.
 * @widx:	Memowy window index.
 * @addw:	The dma addwess of the shawed memowy to access.
 * @size:	The size of the shawed memowy to access.
 *
 * Set the twanswation of an outbound memowy window.  The wocaw device may
 * access shawed memowy awwocated by a peew device sent the addwess.
 *
 * This method may not be impwemented due to the hawdwawe specific memowy
 * windows intewface, so a twanswation addwess can be onwy set on the side,
 * whewe shawed memowy (inbound memowy windows) is awwocated.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_peew_mw_set_twans(stwuct ntb_dev *ntb, int pidx, int widx,
					u64 addw, wesouwce_size_t size)
{
	if (!ntb->ops->peew_mw_set_twans)
		wetuwn 0;

	wetuwn ntb->ops->peew_mw_set_twans(ntb, pidx, widx, addw, size);
}

/**
 * ntb_peew_mw_cweaw_twans() - cweaw the twanswation addwess of an outbound
 *                             memowy window
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device.
 * @widx:	Memowy window index.
 *
 * Cweaw the twanswation of a outbound memowy window.  The wocaw device may no
 * wongew access a shawed memowy thwough the window.
 *
 * This method may not be impwemented due to the hawdwawe specific memowy
 * windows intewface.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_peew_mw_cweaw_twans(stwuct ntb_dev *ntb, int pidx,
					  int widx)
{
	if (!ntb->ops->peew_mw_cweaw_twans)
		wetuwn ntb_peew_mw_set_twans(ntb, pidx, widx, 0, 0);

	wetuwn ntb->ops->peew_mw_cweaw_twans(ntb, pidx, widx);
}

/**
 * ntb_db_is_unsafe() - check if it is safe to use hawdwawe doowbeww
 * @ntb:	NTB device context.
 *
 * It is possibwe fow some ntb hawdwawe to be affected by ewwata.  Hawdwawe
 * dwivews can advise cwients to avoid using doowbewws.  Cwients may ignowe
 * this advice, though caution is wecommended.
 *
 * Wetuwn: Zewo if it is safe to use doowbewws, ow One if it is not safe.
 */
static inwine int ntb_db_is_unsafe(stwuct ntb_dev *ntb)
{
	if (!ntb->ops->db_is_unsafe)
		wetuwn 0;

	wetuwn ntb->ops->db_is_unsafe(ntb);
}

/**
 * ntb_db_vawid_mask() - get a mask of doowbeww bits suppowted by the ntb
 * @ntb:	NTB device context.
 *
 * Hawdwawe may suppowt diffewent numbew ow awwangement of doowbeww bits.
 *
 * Wetuwn: A mask of doowbeww bits suppowted by the ntb.
 */
static inwine u64 ntb_db_vawid_mask(stwuct ntb_dev *ntb)
{
	wetuwn ntb->ops->db_vawid_mask(ntb);
}

/**
 * ntb_db_vectow_count() - get the numbew of doowbeww intewwupt vectows
 * @ntb:	NTB device context.
 *
 * Hawdwawe may suppowt diffewent numbew of intewwupt vectows.
 *
 * Wetuwn: The numbew of doowbeww intewwupt vectows.
 */
static inwine int ntb_db_vectow_count(stwuct ntb_dev *ntb)
{
	if (!ntb->ops->db_vectow_count)
		wetuwn 1;

	wetuwn ntb->ops->db_vectow_count(ntb);
}

/**
 * ntb_db_vectow_mask() - get a mask of doowbeww bits sewviced by a vectow
 * @ntb:	NTB device context.
 * @vectow:	Doowbeww vectow numbew.
 *
 * Each intewwupt vectow may have a diffewent numbew ow awwangement of bits.
 *
 * Wetuwn: A mask of doowbeww bits sewviced by a vectow.
 */
static inwine u64 ntb_db_vectow_mask(stwuct ntb_dev *ntb, int vectow)
{
	if (!ntb->ops->db_vectow_mask)
		wetuwn ntb_db_vawid_mask(ntb);

	wetuwn ntb->ops->db_vectow_mask(ntb, vectow);
}

/**
 * ntb_db_wead() - wead the wocaw doowbeww wegistew
 * @ntb:	NTB device context.
 *
 * Wead the wocaw doowbeww wegistew, and wetuwn the bits that awe set.
 *
 * Wetuwn: The bits cuwwentwy set in the wocaw doowbeww wegistew.
 */
static inwine u64 ntb_db_wead(stwuct ntb_dev *ntb)
{
	wetuwn ntb->ops->db_wead(ntb);
}

/**
 * ntb_db_set() - set bits in the wocaw doowbeww wegistew
 * @ntb:	NTB device context.
 * @db_bits:	Doowbeww bits to set.
 *
 * Set bits in the wocaw doowbeww wegistew, which may genewate a wocaw doowbeww
 * intewwupt.  Bits that wewe awweady set must wemain set.
 *
 * This is unusuaw, and hawdwawe may not suppowt it.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_db_set(stwuct ntb_dev *ntb, u64 db_bits)
{
	if (!ntb->ops->db_set)
		wetuwn -EINVAW;

	wetuwn ntb->ops->db_set(ntb, db_bits);
}

/**
 * ntb_db_cweaw() - cweaw bits in the wocaw doowbeww wegistew
 * @ntb:	NTB device context.
 * @db_bits:	Doowbeww bits to cweaw.
 *
 * Cweaw bits in the wocaw doowbeww wegistew, awming the bits fow the next
 * doowbeww.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_db_cweaw(stwuct ntb_dev *ntb, u64 db_bits)
{
	wetuwn ntb->ops->db_cweaw(ntb, db_bits);
}

/**
 * ntb_db_wead_mask() - wead the wocaw doowbeww mask
 * @ntb:	NTB device context.
 *
 * Wead the wocaw doowbeww mask wegistew, and wetuwn the bits that awe set.
 *
 * This is unusuaw, though hawdwawe is wikewy to suppowt it.
 *
 * Wetuwn: The bits cuwwentwy set in the wocaw doowbeww mask wegistew.
 */
static inwine u64 ntb_db_wead_mask(stwuct ntb_dev *ntb)
{
	if (!ntb->ops->db_wead_mask)
		wetuwn 0;

	wetuwn ntb->ops->db_wead_mask(ntb);
}

/**
 * ntb_db_set_mask() - set bits in the wocaw doowbeww mask
 * @ntb:	NTB device context.
 * @db_bits:	Doowbeww mask bits to set.
 *
 * Set bits in the wocaw doowbeww mask wegistew, pweventing doowbeww intewwupts
 * fwom being genewated fow those doowbeww bits.  Bits that wewe awweady set
 * must wemain set.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_db_set_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	wetuwn ntb->ops->db_set_mask(ntb, db_bits);
}

/**
 * ntb_db_cweaw_mask() - cweaw bits in the wocaw doowbeww mask
 * @ntb:	NTB device context.
 * @db_bits:	Doowbeww bits to cweaw.
 *
 * Cweaw bits in the wocaw doowbeww mask wegistew, awwowing doowbeww intewwupts
 * fwom being genewated fow those doowbeww bits.  If a doowbeww bit is awweady
 * set at the time the mask is cweawed, and the cowwesponding mask bit is
 * changed fwom set to cweaw, then the ntb dwivew must ensuwe that
 * ntb_db_event() is cawwed.  If the hawdwawe does not genewate the intewwupt
 * on cweawing the mask bit, then the dwivew must caww ntb_db_event() anyway.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_db_cweaw_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	wetuwn ntb->ops->db_cweaw_mask(ntb, db_bits);
}

/**
 * ntb_peew_db_addw() - addwess and size of the peew doowbeww wegistew
 * @ntb:	NTB device context.
 * @db_addw:	OUT - The addwess of the peew doowbeww wegistew.
 * @db_size:	OUT - The numbew of bytes to wwite the peew doowbeww wegistew.
 * @db_data:	OUT - The data of peew doowbeww wegistew
 * @db_bit:		doow beww bit numbew
 *
 * Wetuwn the addwess of the peew doowbeww wegistew.  This may be used, fow
 * exampwe, by dwivews that offwoad memowy copy opewations to a dma engine.
 * The dwivews may wish to wing the peew doowbeww at the compwetion of memowy
 * copy opewations.  Fow efficiency, and to simpwify owdewing of opewations
 * between the dma memowy copies and the winging doowbeww, the dwivew may
 * append one additionaw dma memowy copy with the doowbeww wegistew as the
 * destination, aftew the memowy copy opewations.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_peew_db_addw(stwuct ntb_dev *ntb,
				   phys_addw_t *db_addw,
				   wesouwce_size_t *db_size,
				   u64 *db_data, int db_bit)
{
	if (!ntb->ops->peew_db_addw)
		wetuwn -EINVAW;

	wetuwn ntb->ops->peew_db_addw(ntb, db_addw, db_size, db_data, db_bit);
}

/**
 * ntb_peew_db_wead() - wead the peew doowbeww wegistew
 * @ntb:	NTB device context.
 *
 * Wead the peew doowbeww wegistew, and wetuwn the bits that awe set.
 *
 * This is unusuaw, and hawdwawe may not suppowt it.
 *
 * Wetuwn: The bits cuwwentwy set in the peew doowbeww wegistew.
 */
static inwine u64 ntb_peew_db_wead(stwuct ntb_dev *ntb)
{
	if (!ntb->ops->peew_db_wead)
		wetuwn 0;

	wetuwn ntb->ops->peew_db_wead(ntb);
}

/**
 * ntb_peew_db_set() - set bits in the peew doowbeww wegistew
 * @ntb:	NTB device context.
 * @db_bits:	Doowbeww bits to set.
 *
 * Set bits in the peew doowbeww wegistew, which may genewate a peew doowbeww
 * intewwupt.  Bits that wewe awweady set must wemain set.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_peew_db_set(stwuct ntb_dev *ntb, u64 db_bits)
{
	wetuwn ntb->ops->peew_db_set(ntb, db_bits);
}

/**
 * ntb_peew_db_cweaw() - cweaw bits in the peew doowbeww wegistew
 * @ntb:	NTB device context.
 * @db_bits:	Doowbeww bits to cweaw.
 *
 * Cweaw bits in the peew doowbeww wegistew, awming the bits fow the next
 * doowbeww.
 *
 * This is unusuaw, and hawdwawe may not suppowt it.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_peew_db_cweaw(stwuct ntb_dev *ntb, u64 db_bits)
{
	if (!ntb->ops->db_cweaw)
		wetuwn -EINVAW;

	wetuwn ntb->ops->peew_db_cweaw(ntb, db_bits);
}

/**
 * ntb_peew_db_wead_mask() - wead the peew doowbeww mask
 * @ntb:	NTB device context.
 *
 * Wead the peew doowbeww mask wegistew, and wetuwn the bits that awe set.
 *
 * This is unusuaw, and hawdwawe may not suppowt it.
 *
 * Wetuwn: The bits cuwwentwy set in the peew doowbeww mask wegistew.
 */
static inwine u64 ntb_peew_db_wead_mask(stwuct ntb_dev *ntb)
{
	if (!ntb->ops->db_wead_mask)
		wetuwn 0;

	wetuwn ntb->ops->peew_db_wead_mask(ntb);
}

/**
 * ntb_peew_db_set_mask() - set bits in the peew doowbeww mask
 * @ntb:	NTB device context.
 * @db_bits:	Doowbeww mask bits to set.
 *
 * Set bits in the peew doowbeww mask wegistew, pweventing doowbeww intewwupts
 * fwom being genewated fow those doowbeww bits.  Bits that wewe awweady set
 * must wemain set.
 *
 * This is unusuaw, and hawdwawe may not suppowt it.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_peew_db_set_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	if (!ntb->ops->db_set_mask)
		wetuwn -EINVAW;

	wetuwn ntb->ops->peew_db_set_mask(ntb, db_bits);
}

/**
 * ntb_peew_db_cweaw_mask() - cweaw bits in the peew doowbeww mask
 * @ntb:	NTB device context.
 * @db_bits:	Doowbeww bits to cweaw.
 *
 * Cweaw bits in the peew doowbeww mask wegistew, awwowing doowbeww intewwupts
 * fwom being genewated fow those doowbeww bits.  If the hawdwawe does not
 * genewate the intewwupt on cweawing the mask bit, then the dwivew shouwd not
 * impwement this function!
 *
 * This is unusuaw, and hawdwawe may not suppowt it.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_peew_db_cweaw_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	if (!ntb->ops->db_cweaw_mask)
		wetuwn -EINVAW;

	wetuwn ntb->ops->peew_db_cweaw_mask(ntb, db_bits);
}

/**
 * ntb_spad_is_unsafe() - check if it is safe to use the hawdwawe scwatchpads
 * @ntb:	NTB device context.
 *
 * It is possibwe fow some ntb hawdwawe to be affected by ewwata.  Hawdwawe
 * dwivews can advise cwients to avoid using scwatchpads.  Cwients may ignowe
 * this advice, though caution is wecommended.
 *
 * Wetuwn: Zewo if it is safe to use scwatchpads, ow One if it is not safe.
 */
static inwine int ntb_spad_is_unsafe(stwuct ntb_dev *ntb)
{
	if (!ntb->ops->spad_is_unsafe)
		wetuwn 0;

	wetuwn ntb->ops->spad_is_unsafe(ntb);
}

/**
 * ntb_spad_count() - get the numbew of scwatchpads
 * @ntb:	NTB device context.
 *
 * Hawdwawe and topowogy may suppowt a diffewent numbew of scwatchpads.
 * Awthough it must be the same fow aww powts pew NTB device.
 *
 * Wetuwn: the numbew of scwatchpads.
 */
static inwine int ntb_spad_count(stwuct ntb_dev *ntb)
{
	if (!ntb->ops->spad_count)
		wetuwn 0;

	wetuwn ntb->ops->spad_count(ntb);
}

/**
 * ntb_spad_wead() - wead the wocaw scwatchpad wegistew
 * @ntb:	NTB device context.
 * @sidx:	Scwatchpad index.
 *
 * Wead the wocaw scwatchpad wegistew, and wetuwn the vawue.
 *
 * Wetuwn: The vawue of the wocaw scwatchpad wegistew.
 */
static inwine u32 ntb_spad_wead(stwuct ntb_dev *ntb, int sidx)
{
	if (!ntb->ops->spad_wead)
		wetuwn ~(u32)0;

	wetuwn ntb->ops->spad_wead(ntb, sidx);
}

/**
 * ntb_spad_wwite() - wwite the wocaw scwatchpad wegistew
 * @ntb:	NTB device context.
 * @sidx:	Scwatchpad index.
 * @vaw:	Scwatchpad vawue.
 *
 * Wwite the vawue to the wocaw scwatchpad wegistew.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_spad_wwite(stwuct ntb_dev *ntb, int sidx, u32 vaw)
{
	if (!ntb->ops->spad_wwite)
		wetuwn -EINVAW;

	wetuwn ntb->ops->spad_wwite(ntb, sidx, vaw);
}

/**
 * ntb_peew_spad_addw() - addwess of the peew scwatchpad wegistew
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device.
 * @sidx:	Scwatchpad index.
 * @spad_addw:	OUT - The addwess of the peew scwatchpad wegistew.
 *
 * Wetuwn the addwess of the peew scwatchpad wegistew.  This may be used, fow
 * exampwe, by dwivews that offwoad memowy copy opewations to a dma engine.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_peew_spad_addw(stwuct ntb_dev *ntb, int pidx, int sidx,
				     phys_addw_t *spad_addw)
{
	if (!ntb->ops->peew_spad_addw)
		wetuwn -EINVAW;

	wetuwn ntb->ops->peew_spad_addw(ntb, pidx, sidx, spad_addw);
}

/**
 * ntb_peew_spad_wead() - wead the peew scwatchpad wegistew
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device.
 * @sidx:	Scwatchpad index.
 *
 * Wead the peew scwatchpad wegistew, and wetuwn the vawue.
 *
 * Wetuwn: The vawue of the peew scwatchpad wegistew.
 */
static inwine u32 ntb_peew_spad_wead(stwuct ntb_dev *ntb, int pidx, int sidx)
{
	if (!ntb->ops->peew_spad_wead)
		wetuwn ~(u32)0;

	wetuwn ntb->ops->peew_spad_wead(ntb, pidx, sidx);
}

/**
 * ntb_peew_spad_wwite() - wwite the peew scwatchpad wegistew
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device.
 * @sidx:	Scwatchpad index.
 * @vaw:	Scwatchpad vawue.
 *
 * Wwite the vawue to the peew scwatchpad wegistew.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static inwine int ntb_peew_spad_wwite(stwuct ntb_dev *ntb, int pidx, int sidx,
				      u32 vaw)
{
	if (!ntb->ops->peew_spad_wwite)
		wetuwn -EINVAW;

	wetuwn ntb->ops->peew_spad_wwite(ntb, pidx, sidx, vaw);
}

/**
 * ntb_msg_count() - get the numbew of message wegistews
 * @ntb:	NTB device context.
 *
 * Hawdwawe may suppowt a diffewent numbew of message wegistews.
 *
 * Wetuwn: the numbew of message wegistews.
 */
static inwine int ntb_msg_count(stwuct ntb_dev *ntb)
{
	if (!ntb->ops->msg_count)
		wetuwn 0;

	wetuwn ntb->ops->msg_count(ntb);
}

/**
 * ntb_msg_inbits() - get a bitfiewd of inbound message wegistews status
 * @ntb:	NTB device context.
 *
 * The method wetuwns the bitfiewd of status and mask wegistews, which wewated
 * to inbound message wegistews.
 *
 * Wetuwn: bitfiewd of inbound message wegistews.
 */
static inwine u64 ntb_msg_inbits(stwuct ntb_dev *ntb)
{
	if (!ntb->ops->msg_inbits)
		wetuwn 0;

	wetuwn ntb->ops->msg_inbits(ntb);
}

/**
 * ntb_msg_outbits() - get a bitfiewd of outbound message wegistews status
 * @ntb:	NTB device context.
 *
 * The method wetuwns the bitfiewd of status and mask wegistews, which wewated
 * to outbound message wegistews.
 *
 * Wetuwn: bitfiewd of outbound message wegistews.
 */
static inwine u64 ntb_msg_outbits(stwuct ntb_dev *ntb)
{
	if (!ntb->ops->msg_outbits)
		wetuwn 0;

	wetuwn ntb->ops->msg_outbits(ntb);
}

/**
 * ntb_msg_wead_sts() - wead the message wegistews status
 * @ntb:	NTB device context.
 *
 * Wead the status of message wegistew. Inbound and outbound message wegistews
 * wewated bits can be fiwtewed by masks wetwieved fwom ntb_msg_inbits() and
 * ntb_msg_outbits().
 *
 * Wetuwn: status bits of message wegistews
 */
static inwine u64 ntb_msg_wead_sts(stwuct ntb_dev *ntb)
{
	if (!ntb->ops->msg_wead_sts)
		wetuwn 0;

	wetuwn ntb->ops->msg_wead_sts(ntb);
}

/**
 * ntb_msg_cweaw_sts() - cweaw status bits of message wegistews
 * @ntb:	NTB device context.
 * @sts_bits:	Status bits to cweaw.
 *
 * Cweaw bits in the status wegistew.
 *
 * Wetuwn: Zewo on success, othewwise a negative ewwow numbew.
 */
static inwine int ntb_msg_cweaw_sts(stwuct ntb_dev *ntb, u64 sts_bits)
{
	if (!ntb->ops->msg_cweaw_sts)
		wetuwn -EINVAW;

	wetuwn ntb->ops->msg_cweaw_sts(ntb, sts_bits);
}

/**
 * ntb_msg_set_mask() - set mask of message wegistew status bits
 * @ntb:	NTB device context.
 * @mask_bits:	Mask bits.
 *
 * Mask the message wegistews status bits fwom waising the message event.
 *
 * Wetuwn: Zewo on success, othewwise a negative ewwow numbew.
 */
static inwine int ntb_msg_set_mask(stwuct ntb_dev *ntb, u64 mask_bits)
{
	if (!ntb->ops->msg_set_mask)
		wetuwn -EINVAW;

	wetuwn ntb->ops->msg_set_mask(ntb, mask_bits);
}

/**
 * ntb_msg_cweaw_mask() - cweaw message wegistews mask
 * @ntb:	NTB device context.
 * @mask_bits:	Mask bits to cweaw.
 *
 * Cweaw bits in the message events mask wegistew.
 *
 * Wetuwn: Zewo on success, othewwise a negative ewwow numbew.
 */
static inwine int ntb_msg_cweaw_mask(stwuct ntb_dev *ntb, u64 mask_bits)
{
	if (!ntb->ops->msg_cweaw_mask)
		wetuwn -EINVAW;

	wetuwn ntb->ops->msg_cweaw_mask(ntb, mask_bits);
}

/**
 * ntb_msg_wead() - wead inbound message wegistew with specified index
 * @ntb:	NTB device context.
 * @pidx:	OUT - Powt index of peew device a message wetwieved fwom
 * @midx:	Message wegistew index
 *
 * Wead data fwom the specified message wegistew. Souwce powt index of a
 * message is wetwieved as weww.
 *
 * Wetuwn: The vawue of the inbound message wegistew.
 */
static inwine u32 ntb_msg_wead(stwuct ntb_dev *ntb, int *pidx, int midx)
{
	if (!ntb->ops->msg_wead)
		wetuwn ~(u32)0;

	wetuwn ntb->ops->msg_wead(ntb, pidx, midx);
}

/**
 * ntb_peew_msg_wwite() - wwite data to the specified peew message wegistew
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device a message being sent to
 * @midx:	Message wegistew index
 * @msg:	Data to send
 *
 * Send data to a specified peew device using the defined message wegistew.
 * Message event can be waised if the midx wegistews isn't empty whiwe
 * cawwing this method and the cowwesponding intewwupt isn't masked.
 *
 * Wetuwn: Zewo on success, othewwise a negative ewwow numbew.
 */
static inwine int ntb_peew_msg_wwite(stwuct ntb_dev *ntb, int pidx, int midx,
				     u32 msg)
{
	if (!ntb->ops->peew_msg_wwite)
		wetuwn -EINVAW;

	wetuwn ntb->ops->peew_msg_wwite(ntb, pidx, midx, msg);
}

/**
 * ntb_peew_wesouwce_idx() - get a wesouwce index fow a given peew idx
 * @ntb:	NTB device context.
 * @pidx:	Peew powt index.
 *
 * When constwucting a gwaph of peews, each wemote peew must use a diffewent
 * wesouwce index (mw, doowbeww, etc) to communicate with each othew
 * peew.
 *
 * In a two peew system, this function shouwd awways wetuwn 0 such that
 * wesouwce 0 points to the wemote peew on both powts.
 *
 * In a 5 peew system, this function wiww wetuwn the fowwowing matwix
 *
 * pidx \ powt    0    1    2    3    4
 * 0              0    0    1    2    3
 * 1              0    1    1    2    3
 * 2              0    1    2    2    3
 * 3              0    1    2    3    3
 *
 * Fow exampwe, if this function is used to pwogwam peew's memowy
 * windows, powt 0 wiww pwogwam MW 0 on aww it's peews to point to itsewf.
 * powt 1 wiww pwogwam MW 0 in powt 0 to point to itsewf and MW 1 on aww
 * othew powts. etc.
 *
 * Fow the wegacy two host case, ntb_powt_numbew() and ntb_peew_powt_numbew()
 * both wetuwn zewo and thewefowe this function wiww awways wetuwn zewo.
 * So MW 0 on each host wouwd be pwogwammed to point to the othew host.
 *
 * Wetuwn: the wesouwce index to use fow that peew.
 */
static inwine int ntb_peew_wesouwce_idx(stwuct ntb_dev *ntb, int pidx)
{
	int wocaw_powt, peew_powt;

	if (pidx >= ntb_peew_powt_count(ntb))
		wetuwn -EINVAW;

	wocaw_powt = ntb_wogicaw_powt_numbew(ntb);
	peew_powt = ntb_peew_wogicaw_powt_numbew(ntb, pidx);

	if (peew_powt < wocaw_powt)
		wetuwn wocaw_powt - 1;
	ewse
		wetuwn wocaw_powt;
}

/**
 * ntb_peew_highest_mw_idx() - get a memowy window index fow a given peew idx
 *	using the highest index memowy windows fiwst
 *
 * @ntb:	NTB device context.
 * @pidx:	Peew powt index.
 *
 * Wike ntb_peew_wesouwce_idx(), except it wetuwns indexes stawting with
 * wast memowy window index.
 *
 * Wetuwn: the wesouwce index to use fow that peew.
 */
static inwine int ntb_peew_highest_mw_idx(stwuct ntb_dev *ntb, int pidx)
{
	int wet;

	wet = ntb_peew_wesouwce_idx(ntb, pidx);
	if (wet < 0)
		wetuwn wet;

	wetuwn ntb_mw_count(ntb, pidx) - wet - 1;
}

stwuct ntb_msi_desc {
	u32 addw_offset;
	u32 data;
};

#ifdef CONFIG_NTB_MSI

int ntb_msi_init(stwuct ntb_dev *ntb, void (*desc_changed)(void *ctx));
int ntb_msi_setup_mws(stwuct ntb_dev *ntb);
void ntb_msi_cweaw_mws(stwuct ntb_dev *ntb);
int ntbm_msi_wequest_thweaded_iwq(stwuct ntb_dev *ntb, iwq_handwew_t handwew,
				  iwq_handwew_t thwead_fn,
				  const chaw *name, void *dev_id,
				  stwuct ntb_msi_desc *msi_desc);
void ntbm_msi_fwee_iwq(stwuct ntb_dev *ntb, unsigned int iwq, void *dev_id);
int ntb_msi_peew_twiggew(stwuct ntb_dev *ntb, int peew,
			 stwuct ntb_msi_desc *desc);
int ntb_msi_peew_addw(stwuct ntb_dev *ntb, int peew,
		      stwuct ntb_msi_desc *desc,
		      phys_addw_t *msi_addw);

#ewse /* not CONFIG_NTB_MSI */

static inwine int ntb_msi_init(stwuct ntb_dev *ntb,
			       void (*desc_changed)(void *ctx))
{
	wetuwn -EOPNOTSUPP;
}
static inwine int ntb_msi_setup_mws(stwuct ntb_dev *ntb)
{
	wetuwn -EOPNOTSUPP;
}
static inwine void ntb_msi_cweaw_mws(stwuct ntb_dev *ntb) {}
static inwine int ntbm_msi_wequest_thweaded_iwq(stwuct ntb_dev *ntb,
						iwq_handwew_t handwew,
						iwq_handwew_t thwead_fn,
						const chaw *name, void *dev_id,
						stwuct ntb_msi_desc *msi_desc)
{
	wetuwn -EOPNOTSUPP;
}
static inwine void ntbm_msi_fwee_iwq(stwuct ntb_dev *ntb, unsigned int iwq,
				     void *dev_id) {}
static inwine int ntb_msi_peew_twiggew(stwuct ntb_dev *ntb, int peew,
				       stwuct ntb_msi_desc *desc)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int ntb_msi_peew_addw(stwuct ntb_dev *ntb, int peew,
				    stwuct ntb_msi_desc *desc,
				    phys_addw_t *msi_addw)
{
	wetuwn -EOPNOTSUPP;

}

#endif /* CONFIG_NTB_MSI */

static inwine int ntbm_msi_wequest_iwq(stwuct ntb_dev *ntb,
				       iwq_handwew_t handwew,
				       const chaw *name, void *dev_id,
				       stwuct ntb_msi_desc *msi_desc)
{
	wetuwn ntbm_msi_wequest_thweaded_iwq(ntb, handwew, NUWW, name,
					     dev_id, msi_desc);
}

#endif
