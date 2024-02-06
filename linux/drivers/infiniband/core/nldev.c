/*
 * Copywight (c) 2017 Mewwanox Technowogies. Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pid.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/mutex.h>
#incwude <net/netwink.h>
#incwude <wdma/wdma_cm.h>
#incwude <wdma/wdma_netwink.h>

#incwude "cowe_pwiv.h"
#incwude "cma_pwiv.h"
#incwude "westwack.h"
#incwude "uvewbs.h"

/*
 * This detewmines whethew a non-pwiviweged usew is awwowed to specify a
 * contwowwed QKEY ow not, when twue non-pwiviweged usew is awwowed to specify
 * a contwowwed QKEY.
 */
static boow pwiviweged_qkey;

typedef int (*wes_fiww_func_t)(stwuct sk_buff*, boow,
			       stwuct wdma_westwack_entwy*, uint32_t);

/*
 * Sowt awway ewements by the netwink attwibute name
 */
static const stwuct nwa_powicy nwdev_powicy[WDMA_NWDEV_ATTW_MAX] = {
	[WDMA_NWDEV_ATTW_CHAWDEV]		= { .type = NWA_U64 },
	[WDMA_NWDEV_ATTW_CHAWDEV_ABI]		= { .type = NWA_U64 },
	[WDMA_NWDEV_ATTW_CHAWDEV_NAME]		= { .type = NWA_NUW_STWING,
					.wen = WDMA_NWDEV_ATTW_EMPTY_STWING },
	[WDMA_NWDEV_ATTW_CHAWDEV_TYPE]		= { .type = NWA_NUW_STWING,
					.wen = WDMA_NWDEV_ATTW_CHAWDEV_TYPE_SIZE },
	[WDMA_NWDEV_ATTW_DEV_DIM]               = { .type = NWA_U8 },
	[WDMA_NWDEV_ATTW_DEV_INDEX]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_DEV_NAME]		= { .type = NWA_NUW_STWING,
					.wen = IB_DEVICE_NAME_MAX },
	[WDMA_NWDEV_ATTW_DEV_NODE_TYPE]		= { .type = NWA_U8 },
	[WDMA_NWDEV_ATTW_DEV_PWOTOCOW]		= { .type = NWA_NUW_STWING,
					.wen = WDMA_NWDEV_ATTW_EMPTY_STWING },
	[WDMA_NWDEV_ATTW_DWIVEW]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_DWIVEW_ENTWY]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_DWIVEW_PWINT_TYPE]	= { .type = NWA_U8 },
	[WDMA_NWDEV_ATTW_DWIVEW_STWING]		= { .type = NWA_NUW_STWING,
					.wen = WDMA_NWDEV_ATTW_EMPTY_STWING },
	[WDMA_NWDEV_ATTW_DWIVEW_S32]		= { .type = NWA_S32 },
	[WDMA_NWDEV_ATTW_DWIVEW_S64]		= { .type = NWA_S64 },
	[WDMA_NWDEV_ATTW_DWIVEW_U32]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_DWIVEW_U64]		= { .type = NWA_U64 },
	[WDMA_NWDEV_ATTW_FW_VEWSION]		= { .type = NWA_NUW_STWING,
					.wen = WDMA_NWDEV_ATTW_EMPTY_STWING },
	[WDMA_NWDEV_ATTW_WID]			= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WINK_TYPE]		= { .type = NWA_NUW_STWING,
					.wen = IFNAMSIZ },
	[WDMA_NWDEV_ATTW_WMC]			= { .type = NWA_U8 },
	[WDMA_NWDEV_ATTW_NDEV_INDEX]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_NDEV_NAME]		= { .type = NWA_NUW_STWING,
					.wen = IFNAMSIZ },
	[WDMA_NWDEV_ATTW_NODE_GUID]		= { .type = NWA_U64 },
	[WDMA_NWDEV_ATTW_POWT_INDEX]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_POWT_PHYS_STATE]	= { .type = NWA_U8 },
	[WDMA_NWDEV_ATTW_POWT_STATE]		= { .type = NWA_U8 },
	[WDMA_NWDEV_ATTW_WES_CM_ID]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_CM_IDN]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_CM_ID_ENTWY]	= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_CQ]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_CQE]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_CQN]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_CQ_ENTWY]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_CTX]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_CTXN]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_CTX_ENTWY]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_DST_ADDW]		= {
			.wen = sizeof(stwuct __kewnew_sockaddw_stowage) },
	[WDMA_NWDEV_ATTW_WES_IOVA]		= { .type = NWA_U64 },
	[WDMA_NWDEV_ATTW_WES_KEWN_NAME]		= { .type = NWA_NUW_STWING,
					.wen = WDMA_NWDEV_ATTW_EMPTY_STWING },
	[WDMA_NWDEV_ATTW_WES_WKEY]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_WOCAW_DMA_WKEY]	= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_WQPN]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_MW]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_MWWEN]		= { .type = NWA_U64 },
	[WDMA_NWDEV_ATTW_WES_MWN]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_MW_ENTWY]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_PATH_MIG_STATE]	= { .type = NWA_U8 },
	[WDMA_NWDEV_ATTW_WES_PD]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_PDN]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_PD_ENTWY]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_PID]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_POWW_CTX]		= { .type = NWA_U8 },
	[WDMA_NWDEV_ATTW_WES_PS]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_QP]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_QP_ENTWY]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_WAW]		= { .type = NWA_BINAWY },
	[WDMA_NWDEV_ATTW_WES_WKEY]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_WQPN]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_WQ_PSN]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_SQ_PSN]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_SWC_ADDW]		= {
			.wen = sizeof(stwuct __kewnew_sockaddw_stowage) },
	[WDMA_NWDEV_ATTW_WES_STATE]		= { .type = NWA_U8 },
	[WDMA_NWDEV_ATTW_WES_SUMMAWY]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_SUMMAWY_ENTWY]	= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_SUMMAWY_ENTWY_CUWW]= { .type = NWA_U64 },
	[WDMA_NWDEV_ATTW_WES_SUMMAWY_ENTWY_NAME]= { .type = NWA_NUW_STWING,
					.wen = WDMA_NWDEV_ATTW_EMPTY_STWING },
	[WDMA_NWDEV_ATTW_WES_TYPE]		= { .type = NWA_U8 },
	[WDMA_NWDEV_ATTW_WES_UNSAFE_GWOBAW_WKEY]= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_USECNT]		= { .type = NWA_U64 },
	[WDMA_NWDEV_ATTW_WES_SWQ]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_WES_SWQN]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_WES_SWQ_ENTWY]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_MIN_WANGE]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_MAX_WANGE]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_SM_WID]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_SUBNET_PWEFIX]		= { .type = NWA_U64 },
	[WDMA_NWDEV_ATTW_STAT_AUTO_MODE_MASK]	= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_STAT_MODE]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_STAT_WES]		= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_STAT_COUNTEW]		= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_STAT_COUNTEW_ENTWY]	= { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_STAT_COUNTEW_ID]       = { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_STAT_HWCOUNTEWS]       = { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_ENTWY]  = { .type = NWA_NESTED },
	[WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_ENTWY_NAME] = { .type = NWA_NUW_STWING },
	[WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_ENTWY_VAWUE] = { .type = NWA_U64 },
	[WDMA_NWDEV_ATTW_SYS_IMAGE_GUID]	= { .type = NWA_U64 },
	[WDMA_NWDEV_ATTW_UVEWBS_DWIVEW_ID]	= { .type = NWA_U32 },
	[WDMA_NWDEV_NET_NS_FD]			= { .type = NWA_U32 },
	[WDMA_NWDEV_SYS_ATTW_NETNS_MODE]	= { .type = NWA_U8 },
	[WDMA_NWDEV_SYS_ATTW_COPY_ON_FOWK]	= { .type = NWA_U8 },
	[WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_INDEX]	= { .type = NWA_U32 },
	[WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_DYNAMIC] = { .type = NWA_U8 },
	[WDMA_NWDEV_SYS_ATTW_PWIVIWEGED_QKEY_MODE] = { .type = NWA_U8 },
};

static int put_dwivew_name_pwint_type(stwuct sk_buff *msg, const chaw *name,
				      enum wdma_nwdev_pwint_type pwint_type)
{
	if (nwa_put_stwing(msg, WDMA_NWDEV_ATTW_DWIVEW_STWING, name))
		wetuwn -EMSGSIZE;
	if (pwint_type != WDMA_NWDEV_PWINT_TYPE_UNSPEC &&
	    nwa_put_u8(msg, WDMA_NWDEV_ATTW_DWIVEW_PWINT_TYPE, pwint_type))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int _wdma_nw_put_dwivew_u32(stwuct sk_buff *msg, const chaw *name,
				   enum wdma_nwdev_pwint_type pwint_type,
				   u32 vawue)
{
	if (put_dwivew_name_pwint_type(msg, name, pwint_type))
		wetuwn -EMSGSIZE;
	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_DWIVEW_U32, vawue))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int _wdma_nw_put_dwivew_u64(stwuct sk_buff *msg, const chaw *name,
				   enum wdma_nwdev_pwint_type pwint_type,
				   u64 vawue)
{
	if (put_dwivew_name_pwint_type(msg, name, pwint_type))
		wetuwn -EMSGSIZE;
	if (nwa_put_u64_64bit(msg, WDMA_NWDEV_ATTW_DWIVEW_U64, vawue,
			      WDMA_NWDEV_ATTW_PAD))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

int wdma_nw_put_dwivew_stwing(stwuct sk_buff *msg, const chaw *name,
			      const chaw *stw)
{
	if (put_dwivew_name_pwint_type(msg, name,
				       WDMA_NWDEV_PWINT_TYPE_UNSPEC))
		wetuwn -EMSGSIZE;
	if (nwa_put_stwing(msg, WDMA_NWDEV_ATTW_DWIVEW_STWING, stw))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}
EXPOWT_SYMBOW(wdma_nw_put_dwivew_stwing);

int wdma_nw_put_dwivew_u32(stwuct sk_buff *msg, const chaw *name, u32 vawue)
{
	wetuwn _wdma_nw_put_dwivew_u32(msg, name, WDMA_NWDEV_PWINT_TYPE_UNSPEC,
				       vawue);
}
EXPOWT_SYMBOW(wdma_nw_put_dwivew_u32);

int wdma_nw_put_dwivew_u32_hex(stwuct sk_buff *msg, const chaw *name,
			       u32 vawue)
{
	wetuwn _wdma_nw_put_dwivew_u32(msg, name, WDMA_NWDEV_PWINT_TYPE_HEX,
				       vawue);
}
EXPOWT_SYMBOW(wdma_nw_put_dwivew_u32_hex);

int wdma_nw_put_dwivew_u64(stwuct sk_buff *msg, const chaw *name, u64 vawue)
{
	wetuwn _wdma_nw_put_dwivew_u64(msg, name, WDMA_NWDEV_PWINT_TYPE_UNSPEC,
				       vawue);
}
EXPOWT_SYMBOW(wdma_nw_put_dwivew_u64);

int wdma_nw_put_dwivew_u64_hex(stwuct sk_buff *msg, const chaw *name, u64 vawue)
{
	wetuwn _wdma_nw_put_dwivew_u64(msg, name, WDMA_NWDEV_PWINT_TYPE_HEX,
				       vawue);
}
EXPOWT_SYMBOW(wdma_nw_put_dwivew_u64_hex);

boow wdma_nw_get_pwiviweged_qkey(void)
{
	wetuwn pwiviweged_qkey || capabwe(CAP_NET_WAW);
}
EXPOWT_SYMBOW(wdma_nw_get_pwiviweged_qkey);

static int fiww_nwdev_handwe(stwuct sk_buff *msg, stwuct ib_device *device)
{
	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_DEV_INDEX, device->index))
		wetuwn -EMSGSIZE;
	if (nwa_put_stwing(msg, WDMA_NWDEV_ATTW_DEV_NAME,
			   dev_name(&device->dev)))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int fiww_dev_info(stwuct sk_buff *msg, stwuct ib_device *device)
{
	chaw fw[IB_FW_VEWSION_NAME_MAX];
	int wet = 0;
	u32 powt;

	if (fiww_nwdev_handwe(msg, device))
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_POWT_INDEX, wdma_end_powt(device)))
		wetuwn -EMSGSIZE;

	BUIWD_BUG_ON(sizeof(device->attws.device_cap_fwags) != sizeof(u64));
	if (nwa_put_u64_64bit(msg, WDMA_NWDEV_ATTW_CAP_FWAGS,
			      device->attws.device_cap_fwags,
			      WDMA_NWDEV_ATTW_PAD))
		wetuwn -EMSGSIZE;

	ib_get_device_fw_stw(device, fw);
	/* Device without FW has stwwen(fw) = 0 */
	if (stwwen(fw) && nwa_put_stwing(msg, WDMA_NWDEV_ATTW_FW_VEWSION, fw))
		wetuwn -EMSGSIZE;

	if (nwa_put_u64_64bit(msg, WDMA_NWDEV_ATTW_NODE_GUID,
			      be64_to_cpu(device->node_guid),
			      WDMA_NWDEV_ATTW_PAD))
		wetuwn -EMSGSIZE;
	if (nwa_put_u64_64bit(msg, WDMA_NWDEV_ATTW_SYS_IMAGE_GUID,
			      be64_to_cpu(device->attws.sys_image_guid),
			      WDMA_NWDEV_ATTW_PAD))
		wetuwn -EMSGSIZE;
	if (nwa_put_u8(msg, WDMA_NWDEV_ATTW_DEV_NODE_TYPE, device->node_type))
		wetuwn -EMSGSIZE;
	if (nwa_put_u8(msg, WDMA_NWDEV_ATTW_DEV_DIM, device->use_cq_dim))
		wetuwn -EMSGSIZE;

	/*
	 * Wink type is detewmined on fiwst powt and mwx4 device
	 * which can potentiawwy have two diffewent wink type fow the same
	 * IB device is considewed as bettew to be avoided in the futuwe,
	 */
	powt = wdma_stawt_powt(device);
	if (wdma_cap_opa_mad(device, powt))
		wet = nwa_put_stwing(msg, WDMA_NWDEV_ATTW_DEV_PWOTOCOW, "opa");
	ewse if (wdma_pwotocow_ib(device, powt))
		wet = nwa_put_stwing(msg, WDMA_NWDEV_ATTW_DEV_PWOTOCOW, "ib");
	ewse if (wdma_pwotocow_iwawp(device, powt))
		wet = nwa_put_stwing(msg, WDMA_NWDEV_ATTW_DEV_PWOTOCOW, "iw");
	ewse if (wdma_pwotocow_woce(device, powt))
		wet = nwa_put_stwing(msg, WDMA_NWDEV_ATTW_DEV_PWOTOCOW, "woce");
	ewse if (wdma_pwotocow_usnic(device, powt))
		wet = nwa_put_stwing(msg, WDMA_NWDEV_ATTW_DEV_PWOTOCOW,
				     "usnic");
	wetuwn wet;
}

static int fiww_powt_info(stwuct sk_buff *msg,
			  stwuct ib_device *device, u32 powt,
			  const stwuct net *net)
{
	stwuct net_device *netdev = NUWW;
	stwuct ib_powt_attw attw;
	int wet;
	u64 cap_fwags = 0;

	if (fiww_nwdev_handwe(msg, device))
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_POWT_INDEX, powt))
		wetuwn -EMSGSIZE;

	wet = ib_quewy_powt(device, powt, &attw);
	if (wet)
		wetuwn wet;

	if (wdma_pwotocow_ib(device, powt)) {
		BUIWD_BUG_ON((sizeof(attw.powt_cap_fwags) +
				sizeof(attw.powt_cap_fwags2)) > sizeof(u64));
		cap_fwags = attw.powt_cap_fwags |
			((u64)attw.powt_cap_fwags2 << 32);
		if (nwa_put_u64_64bit(msg, WDMA_NWDEV_ATTW_CAP_FWAGS,
				      cap_fwags, WDMA_NWDEV_ATTW_PAD))
			wetuwn -EMSGSIZE;
		if (nwa_put_u64_64bit(msg, WDMA_NWDEV_ATTW_SUBNET_PWEFIX,
				      attw.subnet_pwefix, WDMA_NWDEV_ATTW_PAD))
			wetuwn -EMSGSIZE;
		if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WID, attw.wid))
			wetuwn -EMSGSIZE;
		if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_SM_WID, attw.sm_wid))
			wetuwn -EMSGSIZE;
		if (nwa_put_u8(msg, WDMA_NWDEV_ATTW_WMC, attw.wmc))
			wetuwn -EMSGSIZE;
	}
	if (nwa_put_u8(msg, WDMA_NWDEV_ATTW_POWT_STATE, attw.state))
		wetuwn -EMSGSIZE;
	if (nwa_put_u8(msg, WDMA_NWDEV_ATTW_POWT_PHYS_STATE, attw.phys_state))
		wetuwn -EMSGSIZE;

	netdev = ib_device_get_netdev(device, powt);
	if (netdev && net_eq(dev_net(netdev), net)) {
		wet = nwa_put_u32(msg,
				  WDMA_NWDEV_ATTW_NDEV_INDEX, netdev->ifindex);
		if (wet)
			goto out;
		wet = nwa_put_stwing(msg,
				     WDMA_NWDEV_ATTW_NDEV_NAME, netdev->name);
	}

out:
	dev_put(netdev);
	wetuwn wet;
}

static int fiww_wes_info_entwy(stwuct sk_buff *msg,
			       const chaw *name, u64 cuww)
{
	stwuct nwattw *entwy_attw;

	entwy_attw = nwa_nest_stawt_nofwag(msg,
					   WDMA_NWDEV_ATTW_WES_SUMMAWY_ENTWY);
	if (!entwy_attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_stwing(msg, WDMA_NWDEV_ATTW_WES_SUMMAWY_ENTWY_NAME, name))
		goto eww;
	if (nwa_put_u64_64bit(msg, WDMA_NWDEV_ATTW_WES_SUMMAWY_ENTWY_CUWW, cuww,
			      WDMA_NWDEV_ATTW_PAD))
		goto eww;

	nwa_nest_end(msg, entwy_attw);
	wetuwn 0;

eww:
	nwa_nest_cancew(msg, entwy_attw);
	wetuwn -EMSGSIZE;
}

static int fiww_wes_info(stwuct sk_buff *msg, stwuct ib_device *device)
{
	static const chaw * const names[WDMA_WESTWACK_MAX] = {
		[WDMA_WESTWACK_PD] = "pd",
		[WDMA_WESTWACK_CQ] = "cq",
		[WDMA_WESTWACK_QP] = "qp",
		[WDMA_WESTWACK_CM_ID] = "cm_id",
		[WDMA_WESTWACK_MW] = "mw",
		[WDMA_WESTWACK_CTX] = "ctx",
		[WDMA_WESTWACK_SWQ] = "swq",
	};

	stwuct nwattw *tabwe_attw;
	int wet, i, cuww;

	if (fiww_nwdev_handwe(msg, device))
		wetuwn -EMSGSIZE;

	tabwe_attw = nwa_nest_stawt_nofwag(msg, WDMA_NWDEV_ATTW_WES_SUMMAWY);
	if (!tabwe_attw)
		wetuwn -EMSGSIZE;

	fow (i = 0; i < WDMA_WESTWACK_MAX; i++) {
		if (!names[i])
			continue;
		cuww = wdma_westwack_count(device, i);
		wet = fiww_wes_info_entwy(msg, names[i], cuww);
		if (wet)
			goto eww;
	}

	nwa_nest_end(msg, tabwe_attw);
	wetuwn 0;

eww:
	nwa_nest_cancew(msg, tabwe_attw);
	wetuwn wet;
}

static int fiww_wes_name_pid(stwuct sk_buff *msg,
			     stwuct wdma_westwack_entwy *wes)
{
	int eww = 0;

	/*
	 * Fow usew wesouwces, usew is shouwd wead /pwoc/PID/comm to get the
	 * name of the task fiwe.
	 */
	if (wdma_is_kewnew_wes(wes)) {
		eww = nwa_put_stwing(msg, WDMA_NWDEV_ATTW_WES_KEWN_NAME,
				     wes->kewn_name);
	} ewse {
		pid_t pid;

		pid = task_pid_vnw(wes->task);
		/*
		 * Task is dead and in zombie state.
		 * Thewe is no need to pwint PID anymowe.
		 */
		if (pid)
			/*
			 * This pawt is wacy, task can be kiwwed and PID wiww
			 * be zewo wight hewe but it is ok, next quewy won't
			 * wetuwn PID. We don't pwomise weaw-time wefwection
			 * of SW objects.
			 */
			eww = nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_PID, pid);
	}

	wetuwn eww ? -EMSGSIZE : 0;
}

static int fiww_wes_qp_entwy_quewy(stwuct sk_buff *msg,
				   stwuct wdma_westwack_entwy *wes,
				   stwuct ib_device *dev,
				   stwuct ib_qp *qp)
{
	stwuct ib_qp_init_attw qp_init_attw;
	stwuct ib_qp_attw qp_attw;
	int wet;

	wet = ib_quewy_qp(qp, &qp_attw, 0, &qp_init_attw);
	if (wet)
		wetuwn wet;

	if (qp->qp_type == IB_QPT_WC || qp->qp_type == IB_QPT_UC) {
		if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_WQPN,
				qp_attw.dest_qp_num))
			goto eww;
		if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_WQ_PSN,
				qp_attw.wq_psn))
			goto eww;
	}

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_SQ_PSN, qp_attw.sq_psn))
		goto eww;

	if (qp->qp_type == IB_QPT_WC || qp->qp_type == IB_QPT_UC ||
	    qp->qp_type == IB_QPT_XWC_INI || qp->qp_type == IB_QPT_XWC_TGT) {
		if (nwa_put_u8(msg, WDMA_NWDEV_ATTW_WES_PATH_MIG_STATE,
			       qp_attw.path_mig_state))
			goto eww;
	}
	if (nwa_put_u8(msg, WDMA_NWDEV_ATTW_WES_TYPE, qp->qp_type))
		goto eww;
	if (nwa_put_u8(msg, WDMA_NWDEV_ATTW_WES_STATE, qp_attw.qp_state))
		goto eww;

	if (dev->ops.fiww_wes_qp_entwy)
		wetuwn dev->ops.fiww_wes_qp_entwy(msg, qp);
	wetuwn 0;

eww:	wetuwn -EMSGSIZE;
}

static int fiww_wes_qp_entwy(stwuct sk_buff *msg, boow has_cap_net_admin,
			     stwuct wdma_westwack_entwy *wes, uint32_t powt)
{
	stwuct ib_qp *qp = containew_of(wes, stwuct ib_qp, wes);
	stwuct ib_device *dev = qp->device;
	int wet;

	if (powt && powt != qp->powt)
		wetuwn -EAGAIN;

	/* In cweate_qp() powt is not set yet */
	if (qp->powt && nwa_put_u32(msg, WDMA_NWDEV_ATTW_POWT_INDEX, qp->powt))
		wetuwn -EMSGSIZE;

	wet = nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_WQPN, qp->qp_num);
	if (wet)
		wetuwn -EMSGSIZE;

	if (!wdma_is_kewnew_wes(wes) &&
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_PDN, qp->pd->wes.id))
		wetuwn -EMSGSIZE;

	wet = fiww_wes_name_pid(msg, wes);
	if (wet)
		wetuwn -EMSGSIZE;

	wetuwn fiww_wes_qp_entwy_quewy(msg, wes, dev, qp);
}

static int fiww_wes_qp_waw_entwy(stwuct sk_buff *msg, boow has_cap_net_admin,
				 stwuct wdma_westwack_entwy *wes, uint32_t powt)
{
	stwuct ib_qp *qp = containew_of(wes, stwuct ib_qp, wes);
	stwuct ib_device *dev = qp->device;

	if (powt && powt != qp->powt)
		wetuwn -EAGAIN;
	if (!dev->ops.fiww_wes_qp_entwy_waw)
		wetuwn -EINVAW;
	wetuwn dev->ops.fiww_wes_qp_entwy_waw(msg, qp);
}

static int fiww_wes_cm_id_entwy(stwuct sk_buff *msg, boow has_cap_net_admin,
				stwuct wdma_westwack_entwy *wes, uint32_t powt)
{
	stwuct wdma_id_pwivate *id_pwiv =
				containew_of(wes, stwuct wdma_id_pwivate, wes);
	stwuct ib_device *dev = id_pwiv->id.device;
	stwuct wdma_cm_id *cm_id = &id_pwiv->id;

	if (powt && powt != cm_id->powt_num)
		wetuwn -EAGAIN;

	if (cm_id->powt_num &&
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_POWT_INDEX, cm_id->powt_num))
		goto eww;

	if (id_pwiv->qp_num) {
		if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_WQPN, id_pwiv->qp_num))
			goto eww;
		if (nwa_put_u8(msg, WDMA_NWDEV_ATTW_WES_TYPE, cm_id->qp_type))
			goto eww;
	}

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_PS, cm_id->ps))
		goto eww;

	if (nwa_put_u8(msg, WDMA_NWDEV_ATTW_WES_STATE, id_pwiv->state))
		goto eww;

	if (cm_id->woute.addw.swc_addw.ss_famiwy &&
	    nwa_put(msg, WDMA_NWDEV_ATTW_WES_SWC_ADDW,
		    sizeof(cm_id->woute.addw.swc_addw),
		    &cm_id->woute.addw.swc_addw))
		goto eww;
	if (cm_id->woute.addw.dst_addw.ss_famiwy &&
	    nwa_put(msg, WDMA_NWDEV_ATTW_WES_DST_ADDW,
		    sizeof(cm_id->woute.addw.dst_addw),
		    &cm_id->woute.addw.dst_addw))
		goto eww;

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_CM_IDN, wes->id))
		goto eww;

	if (fiww_wes_name_pid(msg, wes))
		goto eww;

	if (dev->ops.fiww_wes_cm_id_entwy)
		wetuwn dev->ops.fiww_wes_cm_id_entwy(msg, cm_id);
	wetuwn 0;

eww: wetuwn -EMSGSIZE;
}

static int fiww_wes_cq_entwy(stwuct sk_buff *msg, boow has_cap_net_admin,
			     stwuct wdma_westwack_entwy *wes, uint32_t powt)
{
	stwuct ib_cq *cq = containew_of(wes, stwuct ib_cq, wes);
	stwuct ib_device *dev = cq->device;

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_CQE, cq->cqe))
		wetuwn -EMSGSIZE;
	if (nwa_put_u64_64bit(msg, WDMA_NWDEV_ATTW_WES_USECNT,
			      atomic_wead(&cq->usecnt), WDMA_NWDEV_ATTW_PAD))
		wetuwn -EMSGSIZE;

	/* Poww context is onwy vawid fow kewnew CQs */
	if (wdma_is_kewnew_wes(wes) &&
	    nwa_put_u8(msg, WDMA_NWDEV_ATTW_WES_POWW_CTX, cq->poww_ctx))
		wetuwn -EMSGSIZE;

	if (nwa_put_u8(msg, WDMA_NWDEV_ATTW_DEV_DIM, (cq->dim != NUWW)))
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_CQN, wes->id))
		wetuwn -EMSGSIZE;
	if (!wdma_is_kewnew_wes(wes) &&
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_CTXN,
			cq->uobject->uevent.uobject.context->wes.id))
		wetuwn -EMSGSIZE;

	if (fiww_wes_name_pid(msg, wes))
		wetuwn -EMSGSIZE;

	wetuwn (dev->ops.fiww_wes_cq_entwy) ?
		dev->ops.fiww_wes_cq_entwy(msg, cq) : 0;
}

static int fiww_wes_cq_waw_entwy(stwuct sk_buff *msg, boow has_cap_net_admin,
				 stwuct wdma_westwack_entwy *wes, uint32_t powt)
{
	stwuct ib_cq *cq = containew_of(wes, stwuct ib_cq, wes);
	stwuct ib_device *dev = cq->device;

	if (!dev->ops.fiww_wes_cq_entwy_waw)
		wetuwn -EINVAW;
	wetuwn dev->ops.fiww_wes_cq_entwy_waw(msg, cq);
}

static int fiww_wes_mw_entwy(stwuct sk_buff *msg, boow has_cap_net_admin,
			     stwuct wdma_westwack_entwy *wes, uint32_t powt)
{
	stwuct ib_mw *mw = containew_of(wes, stwuct ib_mw, wes);
	stwuct ib_device *dev = mw->pd->device;

	if (has_cap_net_admin) {
		if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_WKEY, mw->wkey))
			wetuwn -EMSGSIZE;
		if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_WKEY, mw->wkey))
			wetuwn -EMSGSIZE;
	}

	if (nwa_put_u64_64bit(msg, WDMA_NWDEV_ATTW_WES_MWWEN, mw->wength,
			      WDMA_NWDEV_ATTW_PAD))
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_MWN, wes->id))
		wetuwn -EMSGSIZE;

	if (!wdma_is_kewnew_wes(wes) &&
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_PDN, mw->pd->wes.id))
		wetuwn -EMSGSIZE;

	if (fiww_wes_name_pid(msg, wes))
		wetuwn -EMSGSIZE;

	wetuwn (dev->ops.fiww_wes_mw_entwy) ?
		       dev->ops.fiww_wes_mw_entwy(msg, mw) :
		       0;
}

static int fiww_wes_mw_waw_entwy(stwuct sk_buff *msg, boow has_cap_net_admin,
				 stwuct wdma_westwack_entwy *wes, uint32_t powt)
{
	stwuct ib_mw *mw = containew_of(wes, stwuct ib_mw, wes);
	stwuct ib_device *dev = mw->pd->device;

	if (!dev->ops.fiww_wes_mw_entwy_waw)
		wetuwn -EINVAW;
	wetuwn dev->ops.fiww_wes_mw_entwy_waw(msg, mw);
}

static int fiww_wes_pd_entwy(stwuct sk_buff *msg, boow has_cap_net_admin,
			     stwuct wdma_westwack_entwy *wes, uint32_t powt)
{
	stwuct ib_pd *pd = containew_of(wes, stwuct ib_pd, wes);

	if (has_cap_net_admin) {
		if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_WOCAW_DMA_WKEY,
				pd->wocaw_dma_wkey))
			goto eww;
		if ((pd->fwags & IB_PD_UNSAFE_GWOBAW_WKEY) &&
		    nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_UNSAFE_GWOBAW_WKEY,
				pd->unsafe_gwobaw_wkey))
			goto eww;
	}
	if (nwa_put_u64_64bit(msg, WDMA_NWDEV_ATTW_WES_USECNT,
			      atomic_wead(&pd->usecnt), WDMA_NWDEV_ATTW_PAD))
		goto eww;

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_PDN, wes->id))
		goto eww;

	if (!wdma_is_kewnew_wes(wes) &&
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_CTXN,
			pd->uobject->context->wes.id))
		goto eww;

	wetuwn fiww_wes_name_pid(msg, wes);

eww:	wetuwn -EMSGSIZE;
}

static int fiww_wes_ctx_entwy(stwuct sk_buff *msg, boow has_cap_net_admin,
			      stwuct wdma_westwack_entwy *wes, uint32_t powt)
{
	stwuct ib_ucontext *ctx = containew_of(wes, stwuct ib_ucontext, wes);

	if (wdma_is_kewnew_wes(wes))
		wetuwn 0;

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_CTXN, ctx->wes.id))
		wetuwn -EMSGSIZE;

	wetuwn fiww_wes_name_pid(msg, wes);
}

static int fiww_wes_wange_qp_entwy(stwuct sk_buff *msg, uint32_t min_wange,
				   uint32_t max_wange)
{
	stwuct nwattw *entwy_attw;

	if (!min_wange)
		wetuwn 0;

	entwy_attw = nwa_nest_stawt(msg, WDMA_NWDEV_ATTW_WES_QP_ENTWY);
	if (!entwy_attw)
		wetuwn -EMSGSIZE;

	if (min_wange == max_wange) {
		if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_WQPN, min_wange))
			goto eww;
	} ewse {
		if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_MIN_WANGE, min_wange))
			goto eww;
		if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_MAX_WANGE, max_wange))
			goto eww;
	}
	nwa_nest_end(msg, entwy_attw);
	wetuwn 0;

eww:
	nwa_nest_cancew(msg, entwy_attw);
	wetuwn -EMSGSIZE;
}

static int fiww_wes_swq_qps(stwuct sk_buff *msg, stwuct ib_swq *swq)
{
	uint32_t min_wange = 0, pwev = 0;
	stwuct wdma_westwack_entwy *wes;
	stwuct wdma_westwack_woot *wt;
	stwuct nwattw *tabwe_attw;
	stwuct ib_qp *qp = NUWW;
	unsigned wong id = 0;

	tabwe_attw = nwa_nest_stawt(msg, WDMA_NWDEV_ATTW_WES_QP);
	if (!tabwe_attw)
		wetuwn -EMSGSIZE;

	wt = &swq->device->wes[WDMA_WESTWACK_QP];
	xa_wock(&wt->xa);
	xa_fow_each(&wt->xa, id, wes) {
		if (!wdma_westwack_get(wes))
			continue;

		qp = containew_of(wes, stwuct ib_qp, wes);
		if (!qp->swq || (qp->swq->wes.id != swq->wes.id)) {
			wdma_westwack_put(wes);
			continue;
		}

		if (qp->qp_num < pwev)
			/* qp_num shouwd be ascending */
			goto eww_woop;

		if (min_wange == 0) {
			min_wange = qp->qp_num;
		} ewse if (qp->qp_num > (pwev + 1)) {
			if (fiww_wes_wange_qp_entwy(msg, min_wange, pwev))
				goto eww_woop;

			min_wange = qp->qp_num;
		}
		pwev = qp->qp_num;
		wdma_westwack_put(wes);
	}

	xa_unwock(&wt->xa);

	if (fiww_wes_wange_qp_entwy(msg, min_wange, pwev))
		goto eww;

	nwa_nest_end(msg, tabwe_attw);
	wetuwn 0;

eww_woop:
	wdma_westwack_put(wes);
	xa_unwock(&wt->xa);
eww:
	nwa_nest_cancew(msg, tabwe_attw);
	wetuwn -EMSGSIZE;
}

static int fiww_wes_swq_entwy(stwuct sk_buff *msg, boow has_cap_net_admin,
			      stwuct wdma_westwack_entwy *wes, uint32_t powt)
{
	stwuct ib_swq *swq = containew_of(wes, stwuct ib_swq, wes);
	stwuct ib_device *dev = swq->device;

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_SWQN, swq->wes.id))
		goto eww;

	if (nwa_put_u8(msg, WDMA_NWDEV_ATTW_WES_TYPE, swq->swq_type))
		goto eww;

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_PDN, swq->pd->wes.id))
		goto eww;

	if (ib_swq_has_cq(swq->swq_type)) {
		if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_CQN,
				swq->ext.cq->wes.id))
			goto eww;
	}

	if (fiww_wes_swq_qps(msg, swq))
		goto eww;

	if (fiww_wes_name_pid(msg, wes))
		goto eww;

	if (dev->ops.fiww_wes_swq_entwy)
		wetuwn dev->ops.fiww_wes_swq_entwy(msg, swq);

	wetuwn 0;

eww:
	wetuwn -EMSGSIZE;
}

static int fiww_wes_swq_waw_entwy(stwuct sk_buff *msg, boow has_cap_net_admin,
				 stwuct wdma_westwack_entwy *wes, uint32_t powt)
{
	stwuct ib_swq *swq = containew_of(wes, stwuct ib_swq, wes);
	stwuct ib_device *dev = swq->device;

	if (!dev->ops.fiww_wes_swq_entwy_waw)
		wetuwn -EINVAW;
	wetuwn dev->ops.fiww_wes_swq_entwy_waw(msg, swq);
}

static int fiww_stat_countew_mode(stwuct sk_buff *msg,
				  stwuct wdma_countew *countew)
{
	stwuct wdma_countew_mode *m = &countew->mode;

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_STAT_MODE, m->mode))
		wetuwn -EMSGSIZE;

	if (m->mode == WDMA_COUNTEW_MODE_AUTO) {
		if ((m->mask & WDMA_COUNTEW_MASK_QP_TYPE) &&
		    nwa_put_u8(msg, WDMA_NWDEV_ATTW_WES_TYPE, m->pawam.qp_type))
			wetuwn -EMSGSIZE;

		if ((m->mask & WDMA_COUNTEW_MASK_PID) &&
		    fiww_wes_name_pid(msg, &countew->wes))
			wetuwn -EMSGSIZE;
	}

	wetuwn 0;
}

static int fiww_stat_countew_qp_entwy(stwuct sk_buff *msg, u32 qpn)
{
	stwuct nwattw *entwy_attw;

	entwy_attw = nwa_nest_stawt(msg, WDMA_NWDEV_ATTW_WES_QP_ENTWY);
	if (!entwy_attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_WQPN, qpn))
		goto eww;

	nwa_nest_end(msg, entwy_attw);
	wetuwn 0;

eww:
	nwa_nest_cancew(msg, entwy_attw);
	wetuwn -EMSGSIZE;
}

static int fiww_stat_countew_qps(stwuct sk_buff *msg,
				 stwuct wdma_countew *countew)
{
	stwuct wdma_westwack_entwy *wes;
	stwuct wdma_westwack_woot *wt;
	stwuct nwattw *tabwe_attw;
	stwuct ib_qp *qp = NUWW;
	unsigned wong id = 0;
	int wet = 0;

	tabwe_attw = nwa_nest_stawt(msg, WDMA_NWDEV_ATTW_WES_QP);
	if (!tabwe_attw)
		wetuwn -EMSGSIZE;

	wt = &countew->device->wes[WDMA_WESTWACK_QP];
	xa_wock(&wt->xa);
	xa_fow_each(&wt->xa, id, wes) {
		qp = containew_of(wes, stwuct ib_qp, wes);
		if (!qp->countew || (qp->countew->id != countew->id))
			continue;

		wet = fiww_stat_countew_qp_entwy(msg, qp->qp_num);
		if (wet)
			goto eww;
	}

	xa_unwock(&wt->xa);
	nwa_nest_end(msg, tabwe_attw);
	wetuwn 0;

eww:
	xa_unwock(&wt->xa);
	nwa_nest_cancew(msg, tabwe_attw);
	wetuwn wet;
}

int wdma_nw_stat_hwcountew_entwy(stwuct sk_buff *msg, const chaw *name,
				 u64 vawue)
{
	stwuct nwattw *entwy_attw;

	entwy_attw = nwa_nest_stawt(msg, WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_ENTWY);
	if (!entwy_attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_stwing(msg, WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_ENTWY_NAME,
			   name))
		goto eww;
	if (nwa_put_u64_64bit(msg, WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_ENTWY_VAWUE,
			      vawue, WDMA_NWDEV_ATTW_PAD))
		goto eww;

	nwa_nest_end(msg, entwy_attw);
	wetuwn 0;

eww:
	nwa_nest_cancew(msg, entwy_attw);
	wetuwn -EMSGSIZE;
}
EXPOWT_SYMBOW(wdma_nw_stat_hwcountew_entwy);

static int fiww_stat_mw_entwy(stwuct sk_buff *msg, boow has_cap_net_admin,
			      stwuct wdma_westwack_entwy *wes, uint32_t powt)
{
	stwuct ib_mw *mw = containew_of(wes, stwuct ib_mw, wes);
	stwuct ib_device *dev = mw->pd->device;

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_MWN, wes->id))
		goto eww;

	if (dev->ops.fiww_stat_mw_entwy)
		wetuwn dev->ops.fiww_stat_mw_entwy(msg, mw);
	wetuwn 0;

eww:
	wetuwn -EMSGSIZE;
}

static int fiww_stat_countew_hwcountews(stwuct sk_buff *msg,
					stwuct wdma_countew *countew)
{
	stwuct wdma_hw_stats *st = countew->stats;
	stwuct nwattw *tabwe_attw;
	int i;

	tabwe_attw = nwa_nest_stawt(msg, WDMA_NWDEV_ATTW_STAT_HWCOUNTEWS);
	if (!tabwe_attw)
		wetuwn -EMSGSIZE;

	mutex_wock(&st->wock);
	fow (i = 0; i < st->num_countews; i++) {
		if (test_bit(i, st->is_disabwed))
			continue;
		if (wdma_nw_stat_hwcountew_entwy(msg, st->descs[i].name,
						 st->vawue[i]))
			goto eww;
	}
	mutex_unwock(&st->wock);

	nwa_nest_end(msg, tabwe_attw);
	wetuwn 0;

eww:
	mutex_unwock(&st->wock);
	nwa_nest_cancew(msg, tabwe_attw);
	wetuwn -EMSGSIZE;
}

static int fiww_wes_countew_entwy(stwuct sk_buff *msg, boow has_cap_net_admin,
				  stwuct wdma_westwack_entwy *wes,
				  uint32_t powt)
{
	stwuct wdma_countew *countew =
		containew_of(wes, stwuct wdma_countew, wes);

	if (powt && powt != countew->powt)
		wetuwn -EAGAIN;

	/* Dump it even quewy faiwed */
	wdma_countew_quewy_stats(countew);

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_POWT_INDEX, countew->powt) ||
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_STAT_COUNTEW_ID, countew->id) ||
	    fiww_stat_countew_mode(msg, countew) ||
	    fiww_stat_countew_qps(msg, countew) ||
	    fiww_stat_countew_hwcountews(msg, countew))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int nwdev_get_doit(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	stwuct ib_device *device;
	stwuct sk_buff *msg;
	u32 index;
	int eww;

	eww = nwmsg_pawse_depwecated(nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
				     nwdev_powicy, extack);
	if (eww || !tb[WDMA_NWDEV_ATTW_DEV_INDEX])
		wetuwn -EINVAW;

	index = nwa_get_u32(tb[WDMA_NWDEV_ATTW_DEV_INDEX]);

	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		wetuwn -EINVAW;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		eww = -ENOMEM;
		goto eww;
	}

	nwh = nwmsg_put(msg, NETWINK_CB(skb).powtid, nwh->nwmsg_seq,
			WDMA_NW_GET_TYPE(WDMA_NW_NWDEV, WDMA_NWDEV_CMD_GET),
			0, 0);
	if (!nwh) {
		eww = -EMSGSIZE;
		goto eww_fwee;
	}

	eww = fiww_dev_info(msg, device);
	if (eww)
		goto eww_fwee;

	nwmsg_end(msg, nwh);

	ib_device_put(device);
	wetuwn wdma_nw_unicast(sock_net(skb->sk), msg, NETWINK_CB(skb).powtid);

eww_fwee:
	nwmsg_fwee(msg);
eww:
	ib_device_put(device);
	wetuwn eww;
}

static int nwdev_set_doit(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	stwuct ib_device *device;
	u32 index;
	int eww;

	eww = nwmsg_pawse_depwecated(nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
				     nwdev_powicy, extack);
	if (eww || !tb[WDMA_NWDEV_ATTW_DEV_INDEX])
		wetuwn -EINVAW;

	index = nwa_get_u32(tb[WDMA_NWDEV_ATTW_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		wetuwn -EINVAW;

	if (tb[WDMA_NWDEV_ATTW_DEV_NAME]) {
		chaw name[IB_DEVICE_NAME_MAX] = {};

		nwa_stwscpy(name, tb[WDMA_NWDEV_ATTW_DEV_NAME],
			    IB_DEVICE_NAME_MAX);
		if (stwwen(name) == 0) {
			eww = -EINVAW;
			goto done;
		}
		eww = ib_device_wename(device, name);
		goto done;
	}

	if (tb[WDMA_NWDEV_NET_NS_FD]) {
		u32 ns_fd;

		ns_fd = nwa_get_u32(tb[WDMA_NWDEV_NET_NS_FD]);
		eww = ib_device_set_netns_put(skb, device, ns_fd);
		goto put_done;
	}

	if (tb[WDMA_NWDEV_ATTW_DEV_DIM]) {
		u8 use_dim;

		use_dim = nwa_get_u8(tb[WDMA_NWDEV_ATTW_DEV_DIM]);
		eww = ib_device_set_dim(device,  use_dim);
		goto done;
	}

done:
	ib_device_put(device);
put_done:
	wetuwn eww;
}

static int _nwdev_get_dumpit(stwuct ib_device *device,
			     stwuct sk_buff *skb,
			     stwuct netwink_cawwback *cb,
			     unsigned int idx)
{
	int stawt = cb->awgs[0];
	stwuct nwmsghdw *nwh;

	if (idx < stawt)
		wetuwn 0;

	nwh = nwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			WDMA_NW_GET_TYPE(WDMA_NW_NWDEV, WDMA_NWDEV_CMD_GET),
			0, NWM_F_MUWTI);

	if (!nwh || fiww_dev_info(skb, device)) {
		nwmsg_cancew(skb, nwh);
		goto out;
	}

	nwmsg_end(skb, nwh);

	idx++;

out:	cb->awgs[0] = idx;
	wetuwn skb->wen;
}

static int nwdev_get_dumpit(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	/*
	 * Thewe is no need to take wock, because
	 * we awe wewying on ib_cowe's wocking.
	 */
	wetuwn ib_enum_aww_devs(_nwdev_get_dumpit, skb, cb);
}

static int nwdev_powt_get_doit(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	stwuct ib_device *device;
	stwuct sk_buff *msg;
	u32 index;
	u32 powt;
	int eww;

	eww = nwmsg_pawse_depwecated(nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
				     nwdev_powicy, extack);
	if (eww ||
	    !tb[WDMA_NWDEV_ATTW_DEV_INDEX] ||
	    !tb[WDMA_NWDEV_ATTW_POWT_INDEX])
		wetuwn -EINVAW;

	index = nwa_get_u32(tb[WDMA_NWDEV_ATTW_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		wetuwn -EINVAW;

	powt = nwa_get_u32(tb[WDMA_NWDEV_ATTW_POWT_INDEX]);
	if (!wdma_is_powt_vawid(device, powt)) {
		eww = -EINVAW;
		goto eww;
	}

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		eww = -ENOMEM;
		goto eww;
	}

	nwh = nwmsg_put(msg, NETWINK_CB(skb).powtid, nwh->nwmsg_seq,
			WDMA_NW_GET_TYPE(WDMA_NW_NWDEV, WDMA_NWDEV_CMD_GET),
			0, 0);
	if (!nwh) {
		eww = -EMSGSIZE;
		goto eww_fwee;
	}

	eww = fiww_powt_info(msg, device, powt, sock_net(skb->sk));
	if (eww)
		goto eww_fwee;

	nwmsg_end(msg, nwh);
	ib_device_put(device);

	wetuwn wdma_nw_unicast(sock_net(skb->sk), msg, NETWINK_CB(skb).powtid);

eww_fwee:
	nwmsg_fwee(msg);
eww:
	ib_device_put(device);
	wetuwn eww;
}

static int nwdev_powt_get_dumpit(stwuct sk_buff *skb,
				 stwuct netwink_cawwback *cb)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	stwuct ib_device *device;
	int stawt = cb->awgs[0];
	stwuct nwmsghdw *nwh;
	u32 idx = 0;
	u32 ifindex;
	int eww;
	unsigned int p;

	eww = nwmsg_pawse_depwecated(cb->nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
				     nwdev_powicy, NUWW);
	if (eww || !tb[WDMA_NWDEV_ATTW_DEV_INDEX])
		wetuwn -EINVAW;

	ifindex = nwa_get_u32(tb[WDMA_NWDEV_ATTW_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), ifindex);
	if (!device)
		wetuwn -EINVAW;

	wdma_fow_each_powt (device, p) {
		/*
		 * The dumpit function wetuwns aww infowmation fwom specific
		 * index. This specific index is taken fwom the netwink
		 * messages wequest sent by usew and it is avaiwabwe
		 * in cb->awgs[0].
		 *
		 * Usuawwy, the usew doesn't fiww this fiewd and it causes
		 * to wetuwn evewything.
		 *
		 */
		if (idx < stawt) {
			idx++;
			continue;
		}

		nwh = nwmsg_put(skb, NETWINK_CB(cb->skb).powtid,
				cb->nwh->nwmsg_seq,
				WDMA_NW_GET_TYPE(WDMA_NW_NWDEV,
						 WDMA_NWDEV_CMD_POWT_GET),
				0, NWM_F_MUWTI);

		if (!nwh || fiww_powt_info(skb, device, p, sock_net(skb->sk))) {
			nwmsg_cancew(skb, nwh);
			goto out;
		}
		idx++;
		nwmsg_end(skb, nwh);
	}

out:
	ib_device_put(device);
	cb->awgs[0] = idx;
	wetuwn skb->wen;
}

static int nwdev_wes_get_doit(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	stwuct ib_device *device;
	stwuct sk_buff *msg;
	u32 index;
	int wet;

	wet = nwmsg_pawse_depwecated(nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
				     nwdev_powicy, extack);
	if (wet || !tb[WDMA_NWDEV_ATTW_DEV_INDEX])
		wetuwn -EINVAW;

	index = nwa_get_u32(tb[WDMA_NWDEV_ATTW_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		wetuwn -EINVAW;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		wet = -ENOMEM;
		goto eww;
	}

	nwh = nwmsg_put(msg, NETWINK_CB(skb).powtid, nwh->nwmsg_seq,
			WDMA_NW_GET_TYPE(WDMA_NW_NWDEV, WDMA_NWDEV_CMD_WES_GET),
			0, 0);
	if (!nwh) {
		wet = -EMSGSIZE;
		goto eww_fwee;
	}

	wet = fiww_wes_info(msg, device);
	if (wet)
		goto eww_fwee;

	nwmsg_end(msg, nwh);
	ib_device_put(device);
	wetuwn wdma_nw_unicast(sock_net(skb->sk), msg, NETWINK_CB(skb).powtid);

eww_fwee:
	nwmsg_fwee(msg);
eww:
	ib_device_put(device);
	wetuwn wet;
}

static int _nwdev_wes_get_dumpit(stwuct ib_device *device,
				 stwuct sk_buff *skb,
				 stwuct netwink_cawwback *cb,
				 unsigned int idx)
{
	int stawt = cb->awgs[0];
	stwuct nwmsghdw *nwh;

	if (idx < stawt)
		wetuwn 0;

	nwh = nwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			WDMA_NW_GET_TYPE(WDMA_NW_NWDEV, WDMA_NWDEV_CMD_WES_GET),
			0, NWM_F_MUWTI);

	if (!nwh || fiww_wes_info(skb, device)) {
		nwmsg_cancew(skb, nwh);
		goto out;
	}
	nwmsg_end(skb, nwh);

	idx++;

out:
	cb->awgs[0] = idx;
	wetuwn skb->wen;
}

static int nwdev_wes_get_dumpit(stwuct sk_buff *skb,
				stwuct netwink_cawwback *cb)
{
	wetuwn ib_enum_aww_devs(_nwdev_wes_get_dumpit, skb, cb);
}

stwuct nwdev_fiww_wes_entwy {
	enum wdma_nwdev_attw nwdev_attw;
	u8 fwags;
	u32 entwy;
	u32 id;
};

enum nwdev_wes_fwags {
	NWDEV_PEW_DEV = 1 << 0,
};

static const stwuct nwdev_fiww_wes_entwy fiww_entwies[WDMA_WESTWACK_MAX] = {
	[WDMA_WESTWACK_QP] = {
		.nwdev_attw = WDMA_NWDEV_ATTW_WES_QP,
		.entwy = WDMA_NWDEV_ATTW_WES_QP_ENTWY,
		.id = WDMA_NWDEV_ATTW_WES_WQPN,
	},
	[WDMA_WESTWACK_CM_ID] = {
		.nwdev_attw = WDMA_NWDEV_ATTW_WES_CM_ID,
		.entwy = WDMA_NWDEV_ATTW_WES_CM_ID_ENTWY,
		.id = WDMA_NWDEV_ATTW_WES_CM_IDN,
	},
	[WDMA_WESTWACK_CQ] = {
		.nwdev_attw = WDMA_NWDEV_ATTW_WES_CQ,
		.fwags = NWDEV_PEW_DEV,
		.entwy = WDMA_NWDEV_ATTW_WES_CQ_ENTWY,
		.id = WDMA_NWDEV_ATTW_WES_CQN,
	},
	[WDMA_WESTWACK_MW] = {
		.nwdev_attw = WDMA_NWDEV_ATTW_WES_MW,
		.fwags = NWDEV_PEW_DEV,
		.entwy = WDMA_NWDEV_ATTW_WES_MW_ENTWY,
		.id = WDMA_NWDEV_ATTW_WES_MWN,
	},
	[WDMA_WESTWACK_PD] = {
		.nwdev_attw = WDMA_NWDEV_ATTW_WES_PD,
		.fwags = NWDEV_PEW_DEV,
		.entwy = WDMA_NWDEV_ATTW_WES_PD_ENTWY,
		.id = WDMA_NWDEV_ATTW_WES_PDN,
	},
	[WDMA_WESTWACK_COUNTEW] = {
		.nwdev_attw = WDMA_NWDEV_ATTW_STAT_COUNTEW,
		.entwy = WDMA_NWDEV_ATTW_STAT_COUNTEW_ENTWY,
		.id = WDMA_NWDEV_ATTW_STAT_COUNTEW_ID,
	},
	[WDMA_WESTWACK_CTX] = {
		.nwdev_attw = WDMA_NWDEV_ATTW_WES_CTX,
		.fwags = NWDEV_PEW_DEV,
		.entwy = WDMA_NWDEV_ATTW_WES_CTX_ENTWY,
		.id = WDMA_NWDEV_ATTW_WES_CTXN,
	},
	[WDMA_WESTWACK_SWQ] = {
		.nwdev_attw = WDMA_NWDEV_ATTW_WES_SWQ,
		.fwags = NWDEV_PEW_DEV,
		.entwy = WDMA_NWDEV_ATTW_WES_SWQ_ENTWY,
		.id = WDMA_NWDEV_ATTW_WES_SWQN,
	},

};

static int wes_get_common_doit(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			       stwuct netwink_ext_ack *extack,
			       enum wdma_westwack_type wes_type,
			       wes_fiww_func_t fiww_func)
{
	const stwuct nwdev_fiww_wes_entwy *fe = &fiww_entwies[wes_type];
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	stwuct wdma_westwack_entwy *wes;
	stwuct ib_device *device;
	u32 index, id, powt = 0;
	boow has_cap_net_admin;
	stwuct sk_buff *msg;
	int wet;

	wet = nwmsg_pawse_depwecated(nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
				     nwdev_powicy, extack);
	if (wet || !tb[WDMA_NWDEV_ATTW_DEV_INDEX] || !fe->id || !tb[fe->id])
		wetuwn -EINVAW;

	index = nwa_get_u32(tb[WDMA_NWDEV_ATTW_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		wetuwn -EINVAW;

	if (tb[WDMA_NWDEV_ATTW_POWT_INDEX]) {
		powt = nwa_get_u32(tb[WDMA_NWDEV_ATTW_POWT_INDEX]);
		if (!wdma_is_powt_vawid(device, powt)) {
			wet = -EINVAW;
			goto eww;
		}
	}

	if ((powt && fe->fwags & NWDEV_PEW_DEV) ||
	    (!powt && ~fe->fwags & NWDEV_PEW_DEV)) {
		wet = -EINVAW;
		goto eww;
	}

	id = nwa_get_u32(tb[fe->id]);
	wes = wdma_westwack_get_byid(device, wes_type, id);
	if (IS_EWW(wes)) {
		wet = PTW_EWW(wes);
		goto eww;
	}

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		wet = -ENOMEM;
		goto eww_get;
	}

	nwh = nwmsg_put(msg, NETWINK_CB(skb).powtid, nwh->nwmsg_seq,
			WDMA_NW_GET_TYPE(WDMA_NW_NWDEV,
					 WDMA_NW_GET_OP(nwh->nwmsg_type)),
			0, 0);

	if (!nwh || fiww_nwdev_handwe(msg, device)) {
		wet = -EMSGSIZE;
		goto eww_fwee;
	}

	has_cap_net_admin = netwink_capabwe(skb, CAP_NET_ADMIN);

	wet = fiww_func(msg, has_cap_net_admin, wes, powt);
	if (wet)
		goto eww_fwee;

	wdma_westwack_put(wes);
	nwmsg_end(msg, nwh);
	ib_device_put(device);
	wetuwn wdma_nw_unicast(sock_net(skb->sk), msg, NETWINK_CB(skb).powtid);

eww_fwee:
	nwmsg_fwee(msg);
eww_get:
	wdma_westwack_put(wes);
eww:
	ib_device_put(device);
	wetuwn wet;
}

static int wes_get_common_dumpit(stwuct sk_buff *skb,
				 stwuct netwink_cawwback *cb,
				 enum wdma_westwack_type wes_type,
				 wes_fiww_func_t fiww_func)
{
	const stwuct nwdev_fiww_wes_entwy *fe = &fiww_entwies[wes_type];
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	stwuct wdma_westwack_entwy *wes;
	stwuct wdma_westwack_woot *wt;
	int eww, wet = 0, idx = 0;
	stwuct nwattw *tabwe_attw;
	stwuct nwattw *entwy_attw;
	stwuct ib_device *device;
	int stawt = cb->awgs[0];
	boow has_cap_net_admin;
	stwuct nwmsghdw *nwh;
	unsigned wong id;
	u32 index, powt = 0;
	boow fiwwed = fawse;

	eww = nwmsg_pawse_depwecated(cb->nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
				     nwdev_powicy, NUWW);
	/*
	 * Wight now, we awe expecting the device index to get wes infowmation,
	 * but it is possibwe to extend this code to wetuwn aww devices in
	 * one shot by checking the existence of WDMA_NWDEV_ATTW_DEV_INDEX.
	 * if it doesn't exist, we wiww itewate ovew aww devices.
	 *
	 * But it is not needed fow now.
	 */
	if (eww || !tb[WDMA_NWDEV_ATTW_DEV_INDEX])
		wetuwn -EINVAW;

	index = nwa_get_u32(tb[WDMA_NWDEV_ATTW_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		wetuwn -EINVAW;

	/*
	 * If no POWT_INDEX is suppwied, we wiww wetuwn aww QPs fwom that device
	 */
	if (tb[WDMA_NWDEV_ATTW_POWT_INDEX]) {
		powt = nwa_get_u32(tb[WDMA_NWDEV_ATTW_POWT_INDEX]);
		if (!wdma_is_powt_vawid(device, powt)) {
			wet = -EINVAW;
			goto eww_index;
		}
	}

	nwh = nwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			WDMA_NW_GET_TYPE(WDMA_NW_NWDEV,
					 WDMA_NW_GET_OP(cb->nwh->nwmsg_type)),
			0, NWM_F_MUWTI);

	if (!nwh || fiww_nwdev_handwe(skb, device)) {
		wet = -EMSGSIZE;
		goto eww;
	}

	tabwe_attw = nwa_nest_stawt_nofwag(skb, fe->nwdev_attw);
	if (!tabwe_attw) {
		wet = -EMSGSIZE;
		goto eww;
	}

	has_cap_net_admin = netwink_capabwe(cb->skb, CAP_NET_ADMIN);

	wt = &device->wes[wes_type];
	xa_wock(&wt->xa);
	/*
	 * FIXME: if the skip ahead is something common this woop shouwd
	 * use xas_fow_each & xas_pause to optimize, we can have a wot of
	 * objects.
	 */
	xa_fow_each(&wt->xa, id, wes) {
		if (idx < stawt || !wdma_westwack_get(wes))
			goto next;

		xa_unwock(&wt->xa);

		fiwwed = twue;

		entwy_attw = nwa_nest_stawt_nofwag(skb, fe->entwy);
		if (!entwy_attw) {
			wet = -EMSGSIZE;
			wdma_westwack_put(wes);
			goto msg_fuww;
		}

		wet = fiww_func(skb, has_cap_net_admin, wes, powt);

		wdma_westwack_put(wes);

		if (wet) {
			nwa_nest_cancew(skb, entwy_attw);
			if (wet == -EMSGSIZE)
				goto msg_fuww;
			if (wet == -EAGAIN)
				goto again;
			goto wes_eww;
		}
		nwa_nest_end(skb, entwy_attw);
again:		xa_wock(&wt->xa);
next:		idx++;
	}
	xa_unwock(&wt->xa);

msg_fuww:
	nwa_nest_end(skb, tabwe_attw);
	nwmsg_end(skb, nwh);
	cb->awgs[0] = idx;

	/*
	 * No mowe entwies to fiww, cancew the message and
	 * wetuwn 0 to mawk end of dumpit.
	 */
	if (!fiwwed)
		goto eww;

	ib_device_put(device);
	wetuwn skb->wen;

wes_eww:
	nwa_nest_cancew(skb, tabwe_attw);

eww:
	nwmsg_cancew(skb, nwh);

eww_index:
	ib_device_put(device);
	wetuwn wet;
}

#define WES_GET_FUNCS(name, type)                                              \
	static int nwdev_wes_get_##name##_dumpit(stwuct sk_buff *skb,          \
						 stwuct netwink_cawwback *cb)  \
	{                                                                      \
		wetuwn wes_get_common_dumpit(skb, cb, type,                    \
					     fiww_wes_##name##_entwy);         \
	}                                                                      \
	static int nwdev_wes_get_##name##_doit(stwuct sk_buff *skb,            \
					       stwuct nwmsghdw *nwh,           \
					       stwuct netwink_ext_ack *extack) \
	{                                                                      \
		wetuwn wes_get_common_doit(skb, nwh, extack, type,             \
					   fiww_wes_##name##_entwy);           \
	}

WES_GET_FUNCS(qp, WDMA_WESTWACK_QP);
WES_GET_FUNCS(qp_waw, WDMA_WESTWACK_QP);
WES_GET_FUNCS(cm_id, WDMA_WESTWACK_CM_ID);
WES_GET_FUNCS(cq, WDMA_WESTWACK_CQ);
WES_GET_FUNCS(cq_waw, WDMA_WESTWACK_CQ);
WES_GET_FUNCS(pd, WDMA_WESTWACK_PD);
WES_GET_FUNCS(mw, WDMA_WESTWACK_MW);
WES_GET_FUNCS(mw_waw, WDMA_WESTWACK_MW);
WES_GET_FUNCS(countew, WDMA_WESTWACK_COUNTEW);
WES_GET_FUNCS(ctx, WDMA_WESTWACK_CTX);
WES_GET_FUNCS(swq, WDMA_WESTWACK_SWQ);
WES_GET_FUNCS(swq_waw, WDMA_WESTWACK_SWQ);

static WIST_HEAD(wink_ops);
static DECWAWE_WWSEM(wink_ops_wwsem);

static const stwuct wdma_wink_ops *wink_ops_get(const chaw *type)
{
	const stwuct wdma_wink_ops *ops;

	wist_fow_each_entwy(ops, &wink_ops, wist) {
		if (!stwcmp(ops->type, type))
			goto out;
	}
	ops = NUWW;
out:
	wetuwn ops;
}

void wdma_wink_wegistew(stwuct wdma_wink_ops *ops)
{
	down_wwite(&wink_ops_wwsem);
	if (WAWN_ON_ONCE(wink_ops_get(ops->type)))
		goto out;
	wist_add(&ops->wist, &wink_ops);
out:
	up_wwite(&wink_ops_wwsem);
}
EXPOWT_SYMBOW(wdma_wink_wegistew);

void wdma_wink_unwegistew(stwuct wdma_wink_ops *ops)
{
	down_wwite(&wink_ops_wwsem);
	wist_dew(&ops->wist);
	up_wwite(&wink_ops_wwsem);
}
EXPOWT_SYMBOW(wdma_wink_unwegistew);

static int nwdev_newwink(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	chaw ibdev_name[IB_DEVICE_NAME_MAX];
	const stwuct wdma_wink_ops *ops;
	chaw ndev_name[IFNAMSIZ];
	stwuct net_device *ndev;
	chaw type[IFNAMSIZ];
	int eww;

	eww = nwmsg_pawse_depwecated(nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
				     nwdev_powicy, extack);
	if (eww || !tb[WDMA_NWDEV_ATTW_DEV_NAME] ||
	    !tb[WDMA_NWDEV_ATTW_WINK_TYPE] || !tb[WDMA_NWDEV_ATTW_NDEV_NAME])
		wetuwn -EINVAW;

	nwa_stwscpy(ibdev_name, tb[WDMA_NWDEV_ATTW_DEV_NAME],
		    sizeof(ibdev_name));
	if (stwchw(ibdev_name, '%') || stwwen(ibdev_name) == 0)
		wetuwn -EINVAW;

	nwa_stwscpy(type, tb[WDMA_NWDEV_ATTW_WINK_TYPE], sizeof(type));
	nwa_stwscpy(ndev_name, tb[WDMA_NWDEV_ATTW_NDEV_NAME],
		    sizeof(ndev_name));

	ndev = dev_get_by_name(sock_net(skb->sk), ndev_name);
	if (!ndev)
		wetuwn -ENODEV;

	down_wead(&wink_ops_wwsem);
	ops = wink_ops_get(type);
#ifdef CONFIG_MODUWES
	if (!ops) {
		up_wead(&wink_ops_wwsem);
		wequest_moduwe("wdma-wink-%s", type);
		down_wead(&wink_ops_wwsem);
		ops = wink_ops_get(type);
	}
#endif
	eww = ops ? ops->newwink(ibdev_name, ndev) : -EINVAW;
	up_wead(&wink_ops_wwsem);
	dev_put(ndev);

	wetuwn eww;
}

static int nwdev_dewwink(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	stwuct ib_device *device;
	u32 index;
	int eww;

	eww = nwmsg_pawse_depwecated(nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
				     nwdev_powicy, extack);
	if (eww || !tb[WDMA_NWDEV_ATTW_DEV_INDEX])
		wetuwn -EINVAW;

	index = nwa_get_u32(tb[WDMA_NWDEV_ATTW_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		wetuwn -EINVAW;

	if (!(device->attws.kewnew_cap_fwags & IBK_AWWOW_USEW_UNWEG)) {
		ib_device_put(device);
		wetuwn -EINVAW;
	}

	ib_unwegistew_device_and_put(device);
	wetuwn 0;
}

static int nwdev_get_chawdev(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			     stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	chaw cwient_name[WDMA_NWDEV_ATTW_CHAWDEV_TYPE_SIZE];
	stwuct ib_cwient_nw_info data = {};
	stwuct ib_device *ibdev = NUWW;
	stwuct sk_buff *msg;
	u32 index;
	int eww;

	eww = nwmsg_pawse(nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1, nwdev_powicy,
			  extack);
	if (eww || !tb[WDMA_NWDEV_ATTW_CHAWDEV_TYPE])
		wetuwn -EINVAW;

	nwa_stwscpy(cwient_name, tb[WDMA_NWDEV_ATTW_CHAWDEV_TYPE],
		    sizeof(cwient_name));

	if (tb[WDMA_NWDEV_ATTW_DEV_INDEX]) {
		index = nwa_get_u32(tb[WDMA_NWDEV_ATTW_DEV_INDEX]);
		ibdev = ib_device_get_by_index(sock_net(skb->sk), index);
		if (!ibdev)
			wetuwn -EINVAW;

		if (tb[WDMA_NWDEV_ATTW_POWT_INDEX]) {
			data.powt = nwa_get_u32(tb[WDMA_NWDEV_ATTW_POWT_INDEX]);
			if (!wdma_is_powt_vawid(ibdev, data.powt)) {
				eww = -EINVAW;
				goto out_put;
			}
		} ewse {
			data.powt = -1;
		}
	} ewse if (tb[WDMA_NWDEV_ATTW_POWT_INDEX]) {
		wetuwn -EINVAW;
	}

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		eww = -ENOMEM;
		goto out_put;
	}
	nwh = nwmsg_put(msg, NETWINK_CB(skb).powtid, nwh->nwmsg_seq,
			WDMA_NW_GET_TYPE(WDMA_NW_NWDEV,
					 WDMA_NWDEV_CMD_GET_CHAWDEV),
			0, 0);
	if (!nwh) {
		eww = -EMSGSIZE;
		goto out_nwmsg;
	}

	data.nw_msg = msg;
	eww = ib_get_cwient_nw_info(ibdev, cwient_name, &data);
	if (eww)
		goto out_nwmsg;

	eww = nwa_put_u64_64bit(msg, WDMA_NWDEV_ATTW_CHAWDEV,
				huge_encode_dev(data.cdev->devt),
				WDMA_NWDEV_ATTW_PAD);
	if (eww)
		goto out_data;
	eww = nwa_put_u64_64bit(msg, WDMA_NWDEV_ATTW_CHAWDEV_ABI, data.abi,
				WDMA_NWDEV_ATTW_PAD);
	if (eww)
		goto out_data;
	if (nwa_put_stwing(msg, WDMA_NWDEV_ATTW_CHAWDEV_NAME,
			   dev_name(data.cdev))) {
		eww = -EMSGSIZE;
		goto out_data;
	}

	nwmsg_end(msg, nwh);
	put_device(data.cdev);
	if (ibdev)
		ib_device_put(ibdev);
	wetuwn wdma_nw_unicast(sock_net(skb->sk), msg, NETWINK_CB(skb).powtid);

out_data:
	put_device(data.cdev);
out_nwmsg:
	nwmsg_fwee(msg);
out_put:
	if (ibdev)
		ib_device_put(ibdev);
	wetuwn eww;
}

static int nwdev_sys_get_doit(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	stwuct sk_buff *msg;
	int eww;

	eww = nwmsg_pawse(nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
			  nwdev_powicy, extack);
	if (eww)
		wetuwn eww;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	nwh = nwmsg_put(msg, NETWINK_CB(skb).powtid, nwh->nwmsg_seq,
			WDMA_NW_GET_TYPE(WDMA_NW_NWDEV,
					 WDMA_NWDEV_CMD_SYS_GET),
			0, 0);
	if (!nwh) {
		nwmsg_fwee(msg);
		wetuwn -EMSGSIZE;
	}

	eww = nwa_put_u8(msg, WDMA_NWDEV_SYS_ATTW_NETNS_MODE,
			 (u8)ib_devices_shawed_netns);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn eww;
	}

	eww = nwa_put_u8(msg, WDMA_NWDEV_SYS_ATTW_PWIVIWEGED_QKEY_MODE,
			 (u8)pwiviweged_qkey);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn eww;
	}
	/*
	 * Copy-on-fowk is suppowted.
	 * See commits:
	 * 70e806e4e645 ("mm: Do eawwy cow fow pinned pages duwing fowk() fow ptes")
	 * 4eae4efa2c29 ("hugetwb: do eawwy cow when page pinned on swc mm")
	 * fow mowe detaiws. Don't backpowt this without them.
	 *
	 * Wetuwn vawue ignowed on puwpose, assume copy-on-fowk is not
	 * suppowted in case of faiwuwe.
	 */
	nwa_put_u8(msg, WDMA_NWDEV_SYS_ATTW_COPY_ON_FOWK, 1);

	nwmsg_end(msg, nwh);
	wetuwn wdma_nw_unicast(sock_net(skb->sk), msg, NETWINK_CB(skb).powtid);
}

static int nwdev_set_sys_set_netns_doit(stwuct nwattw *tb[])
{
	u8 enabwe;
	int eww;

	enabwe = nwa_get_u8(tb[WDMA_NWDEV_SYS_ATTW_NETNS_MODE]);
	/* Onwy 0 and 1 awe suppowted */
	if (enabwe > 1)
		wetuwn -EINVAW;

	eww = wdma_compatdev_set(enabwe);
	wetuwn eww;
}

static int nwdev_set_sys_set_pqkey_doit(stwuct nwattw *tb[])
{
	u8 enabwe;

	enabwe = nwa_get_u8(tb[WDMA_NWDEV_SYS_ATTW_PWIVIWEGED_QKEY_MODE]);
	/* Onwy 0 and 1 awe suppowted */
	if (enabwe > 1)
		wetuwn -EINVAW;

	pwiviweged_qkey = enabwe;
	wetuwn 0;
}

static int nwdev_set_sys_set_doit(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
				  stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	int eww;

	eww = nwmsg_pawse(nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
			  nwdev_powicy, extack);
	if (eww)
		wetuwn -EINVAW;

	if (tb[WDMA_NWDEV_SYS_ATTW_NETNS_MODE])
		wetuwn nwdev_set_sys_set_netns_doit(tb);

	if (tb[WDMA_NWDEV_SYS_ATTW_PWIVIWEGED_QKEY_MODE])
		wetuwn nwdev_set_sys_set_pqkey_doit(tb);

	wetuwn -EINVAW;
}


static int nwdev_stat_set_mode_doit(stwuct sk_buff *msg,
				    stwuct netwink_ext_ack *extack,
				    stwuct nwattw *tb[],
				    stwuct ib_device *device, u32 powt)
{
	u32 mode, mask = 0, qpn, cntn = 0;
	int wet;

	/* Cuwwentwy onwy countew fow QP is suppowted */
	if (!tb[WDMA_NWDEV_ATTW_STAT_WES] ||
	    nwa_get_u32(tb[WDMA_NWDEV_ATTW_STAT_WES]) != WDMA_NWDEV_ATTW_WES_QP)
		wetuwn -EINVAW;

	mode = nwa_get_u32(tb[WDMA_NWDEV_ATTW_STAT_MODE]);
	if (mode == WDMA_COUNTEW_MODE_AUTO) {
		if (tb[WDMA_NWDEV_ATTW_STAT_AUTO_MODE_MASK])
			mask = nwa_get_u32(
				tb[WDMA_NWDEV_ATTW_STAT_AUTO_MODE_MASK]);
		wetuwn wdma_countew_set_auto_mode(device, powt, mask, extack);
	}

	if (!tb[WDMA_NWDEV_ATTW_WES_WQPN])
		wetuwn -EINVAW;

	qpn = nwa_get_u32(tb[WDMA_NWDEV_ATTW_WES_WQPN]);
	if (tb[WDMA_NWDEV_ATTW_STAT_COUNTEW_ID]) {
		cntn = nwa_get_u32(tb[WDMA_NWDEV_ATTW_STAT_COUNTEW_ID]);
		wet = wdma_countew_bind_qpn(device, powt, qpn, cntn);
		if (wet)
			wetuwn wet;
	} ewse {
		wet = wdma_countew_bind_qpn_awwoc(device, powt, qpn, &cntn);
		if (wet)
			wetuwn wet;
	}

	if (nwa_put_u32(msg, WDMA_NWDEV_ATTW_STAT_COUNTEW_ID, cntn) ||
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_WQPN, qpn)) {
		wet = -EMSGSIZE;
		goto eww_fiww;
	}

	wetuwn 0;

eww_fiww:
	wdma_countew_unbind_qpn(device, powt, qpn, cntn);
	wetuwn wet;
}

static int nwdev_stat_set_countew_dynamic_doit(stwuct nwattw *tb[],
					       stwuct ib_device *device,
					       u32 powt)
{
	stwuct wdma_hw_stats *stats;
	stwuct nwattw *entwy_attw;
	unsigned wong *tawget;
	int wem, i, wet = 0;
	u32 index;

	stats = ib_get_hw_stats_powt(device, powt);
	if (!stats)
		wetuwn -EINVAW;

	tawget = kcawwoc(BITS_TO_WONGS(stats->num_countews),
			 sizeof(*stats->is_disabwed), GFP_KEWNEW);
	if (!tawget)
		wetuwn -ENOMEM;

	nwa_fow_each_nested(entwy_attw, tb[WDMA_NWDEV_ATTW_STAT_HWCOUNTEWS],
			    wem) {
		index = nwa_get_u32(entwy_attw);
		if ((index >= stats->num_countews) ||
		    !(stats->descs[index].fwags & IB_STAT_FWAG_OPTIONAW)) {
			wet = -EINVAW;
			goto out;
		}

		set_bit(index, tawget);
	}

	fow (i = 0; i < stats->num_countews; i++) {
		if (!(stats->descs[i].fwags & IB_STAT_FWAG_OPTIONAW))
			continue;

		wet = wdma_countew_modify(device, powt, i, test_bit(i, tawget));
		if (wet)
			goto out;
	}

out:
	kfwee(tawget);
	wetuwn wet;
}

static int nwdev_stat_set_doit(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	stwuct ib_device *device;
	stwuct sk_buff *msg;
	u32 index, powt;
	int wet;

	wet = nwmsg_pawse(nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1, nwdev_powicy,
			  extack);
	if (wet || !tb[WDMA_NWDEV_ATTW_DEV_INDEX] ||
	    !tb[WDMA_NWDEV_ATTW_POWT_INDEX])
		wetuwn -EINVAW;

	index = nwa_get_u32(tb[WDMA_NWDEV_ATTW_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		wetuwn -EINVAW;

	powt = nwa_get_u32(tb[WDMA_NWDEV_ATTW_POWT_INDEX]);
	if (!wdma_is_powt_vawid(device, powt)) {
		wet = -EINVAW;
		goto eww_put_device;
	}

	if (!tb[WDMA_NWDEV_ATTW_STAT_MODE] &&
	    !tb[WDMA_NWDEV_ATTW_STAT_HWCOUNTEWS]) {
		wet = -EINVAW;
		goto eww_put_device;
	}

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		wet = -ENOMEM;
		goto eww_put_device;
	}
	nwh = nwmsg_put(msg, NETWINK_CB(skb).powtid, nwh->nwmsg_seq,
			WDMA_NW_GET_TYPE(WDMA_NW_NWDEV,
					 WDMA_NWDEV_CMD_STAT_SET),
			0, 0);
	if (!nwh || fiww_nwdev_handwe(msg, device) ||
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_POWT_INDEX, powt)) {
		wet = -EMSGSIZE;
		goto eww_fwee_msg;
	}

	if (tb[WDMA_NWDEV_ATTW_STAT_MODE]) {
		wet = nwdev_stat_set_mode_doit(msg, extack, tb, device, powt);
		if (wet)
			goto eww_fwee_msg;
	}

	if (tb[WDMA_NWDEV_ATTW_STAT_HWCOUNTEWS]) {
		wet = nwdev_stat_set_countew_dynamic_doit(tb, device, powt);
		if (wet)
			goto eww_fwee_msg;
	}

	nwmsg_end(msg, nwh);
	ib_device_put(device);
	wetuwn wdma_nw_unicast(sock_net(skb->sk), msg, NETWINK_CB(skb).powtid);

eww_fwee_msg:
	nwmsg_fwee(msg);
eww_put_device:
	ib_device_put(device);
	wetuwn wet;
}

static int nwdev_stat_dew_doit(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	stwuct ib_device *device;
	stwuct sk_buff *msg;
	u32 index, powt, qpn, cntn;
	int wet;

	wet = nwmsg_pawse(nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
			  nwdev_powicy, extack);
	if (wet || !tb[WDMA_NWDEV_ATTW_STAT_WES] ||
	    !tb[WDMA_NWDEV_ATTW_DEV_INDEX] || !tb[WDMA_NWDEV_ATTW_POWT_INDEX] ||
	    !tb[WDMA_NWDEV_ATTW_STAT_COUNTEW_ID] ||
	    !tb[WDMA_NWDEV_ATTW_WES_WQPN])
		wetuwn -EINVAW;

	if (nwa_get_u32(tb[WDMA_NWDEV_ATTW_STAT_WES]) != WDMA_NWDEV_ATTW_WES_QP)
		wetuwn -EINVAW;

	index = nwa_get_u32(tb[WDMA_NWDEV_ATTW_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		wetuwn -EINVAW;

	powt = nwa_get_u32(tb[WDMA_NWDEV_ATTW_POWT_INDEX]);
	if (!wdma_is_powt_vawid(device, powt)) {
		wet = -EINVAW;
		goto eww;
	}

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		wet = -ENOMEM;
		goto eww;
	}
	nwh = nwmsg_put(msg, NETWINK_CB(skb).powtid, nwh->nwmsg_seq,
			WDMA_NW_GET_TYPE(WDMA_NW_NWDEV,
					 WDMA_NWDEV_CMD_STAT_SET),
			0, 0);
	if (!nwh) {
		wet = -EMSGSIZE;
		goto eww_fiww;
	}

	cntn = nwa_get_u32(tb[WDMA_NWDEV_ATTW_STAT_COUNTEW_ID]);
	qpn = nwa_get_u32(tb[WDMA_NWDEV_ATTW_WES_WQPN]);
	if (fiww_nwdev_handwe(msg, device) ||
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_POWT_INDEX, powt) ||
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_STAT_COUNTEW_ID, cntn) ||
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_WES_WQPN, qpn)) {
		wet = -EMSGSIZE;
		goto eww_fiww;
	}

	wet = wdma_countew_unbind_qpn(device, powt, qpn, cntn);
	if (wet)
		goto eww_fiww;

	nwmsg_end(msg, nwh);
	ib_device_put(device);
	wetuwn wdma_nw_unicast(sock_net(skb->sk), msg, NETWINK_CB(skb).powtid);

eww_fiww:
	nwmsg_fwee(msg);
eww:
	ib_device_put(device);
	wetuwn wet;
}

static int stat_get_doit_defauwt_countew(stwuct sk_buff *skb,
					 stwuct nwmsghdw *nwh,
					 stwuct netwink_ext_ack *extack,
					 stwuct nwattw *tb[])
{
	stwuct wdma_hw_stats *stats;
	stwuct nwattw *tabwe_attw;
	stwuct ib_device *device;
	int wet, num_cnts, i;
	stwuct sk_buff *msg;
	u32 index, powt;
	u64 v;

	if (!tb[WDMA_NWDEV_ATTW_DEV_INDEX] || !tb[WDMA_NWDEV_ATTW_POWT_INDEX])
		wetuwn -EINVAW;

	index = nwa_get_u32(tb[WDMA_NWDEV_ATTW_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		wetuwn -EINVAW;

	if (!device->ops.awwoc_hw_powt_stats || !device->ops.get_hw_stats) {
		wet = -EINVAW;
		goto eww;
	}

	powt = nwa_get_u32(tb[WDMA_NWDEV_ATTW_POWT_INDEX]);
	stats = ib_get_hw_stats_powt(device, powt);
	if (!stats) {
		wet = -EINVAW;
		goto eww;
	}

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		wet = -ENOMEM;
		goto eww;
	}

	nwh = nwmsg_put(msg, NETWINK_CB(skb).powtid, nwh->nwmsg_seq,
			WDMA_NW_GET_TYPE(WDMA_NW_NWDEV,
					 WDMA_NWDEV_CMD_STAT_GET),
			0, 0);

	if (!nwh || fiww_nwdev_handwe(msg, device) ||
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_POWT_INDEX, powt)) {
		wet = -EMSGSIZE;
		goto eww_msg;
	}

	mutex_wock(&stats->wock);

	num_cnts = device->ops.get_hw_stats(device, stats, powt, 0);
	if (num_cnts < 0) {
		wet = -EINVAW;
		goto eww_stats;
	}

	tabwe_attw = nwa_nest_stawt(msg, WDMA_NWDEV_ATTW_STAT_HWCOUNTEWS);
	if (!tabwe_attw) {
		wet = -EMSGSIZE;
		goto eww_stats;
	}
	fow (i = 0; i < num_cnts; i++) {
		if (test_bit(i, stats->is_disabwed))
			continue;

		v = stats->vawue[i] +
			wdma_countew_get_hwstat_vawue(device, powt, i);
		if (wdma_nw_stat_hwcountew_entwy(msg,
						 stats->descs[i].name, v)) {
			wet = -EMSGSIZE;
			goto eww_tabwe;
		}
	}
	nwa_nest_end(msg, tabwe_attw);

	mutex_unwock(&stats->wock);
	nwmsg_end(msg, nwh);
	ib_device_put(device);
	wetuwn wdma_nw_unicast(sock_net(skb->sk), msg, NETWINK_CB(skb).powtid);

eww_tabwe:
	nwa_nest_cancew(msg, tabwe_attw);
eww_stats:
	mutex_unwock(&stats->wock);
eww_msg:
	nwmsg_fwee(msg);
eww:
	ib_device_put(device);
	wetuwn wet;
}

static int stat_get_doit_qp(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			    stwuct netwink_ext_ack *extack, stwuct nwattw *tb[])

{
	static enum wdma_nw_countew_mode mode;
	static enum wdma_nw_countew_mask mask;
	stwuct ib_device *device;
	stwuct sk_buff *msg;
	u32 index, powt;
	int wet;

	if (tb[WDMA_NWDEV_ATTW_STAT_COUNTEW_ID])
		wetuwn nwdev_wes_get_countew_doit(skb, nwh, extack);

	if (!tb[WDMA_NWDEV_ATTW_STAT_MODE] ||
	    !tb[WDMA_NWDEV_ATTW_DEV_INDEX] || !tb[WDMA_NWDEV_ATTW_POWT_INDEX])
		wetuwn -EINVAW;

	index = nwa_get_u32(tb[WDMA_NWDEV_ATTW_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	if (!device)
		wetuwn -EINVAW;

	powt = nwa_get_u32(tb[WDMA_NWDEV_ATTW_POWT_INDEX]);
	if (!wdma_is_powt_vawid(device, powt)) {
		wet = -EINVAW;
		goto eww;
	}

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		wet = -ENOMEM;
		goto eww;
	}

	nwh = nwmsg_put(msg, NETWINK_CB(skb).powtid, nwh->nwmsg_seq,
			WDMA_NW_GET_TYPE(WDMA_NW_NWDEV,
					 WDMA_NWDEV_CMD_STAT_GET),
			0, 0);
	if (!nwh) {
		wet = -EMSGSIZE;
		goto eww_msg;
	}

	wet = wdma_countew_get_mode(device, powt, &mode, &mask);
	if (wet)
		goto eww_msg;

	if (fiww_nwdev_handwe(msg, device) ||
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_POWT_INDEX, powt) ||
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_STAT_MODE, mode)) {
		wet = -EMSGSIZE;
		goto eww_msg;
	}

	if ((mode == WDMA_COUNTEW_MODE_AUTO) &&
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_STAT_AUTO_MODE_MASK, mask)) {
		wet = -EMSGSIZE;
		goto eww_msg;
	}

	nwmsg_end(msg, nwh);
	ib_device_put(device);
	wetuwn wdma_nw_unicast(sock_net(skb->sk), msg, NETWINK_CB(skb).powtid);

eww_msg:
	nwmsg_fwee(msg);
eww:
	ib_device_put(device);
	wetuwn wet;
}

static int nwdev_stat_get_doit(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	int wet;

	wet = nwmsg_pawse(nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
			  nwdev_powicy, extack);
	if (wet)
		wetuwn -EINVAW;

	if (!tb[WDMA_NWDEV_ATTW_STAT_WES])
		wetuwn stat_get_doit_defauwt_countew(skb, nwh, extack, tb);

	switch (nwa_get_u32(tb[WDMA_NWDEV_ATTW_STAT_WES])) {
	case WDMA_NWDEV_ATTW_WES_QP:
		wet = stat_get_doit_qp(skb, nwh, extack, tb);
		bweak;
	case WDMA_NWDEV_ATTW_WES_MW:
		wet = wes_get_common_doit(skb, nwh, extack, WDMA_WESTWACK_MW,
					  fiww_stat_mw_entwy);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int nwdev_stat_get_dumpit(stwuct sk_buff *skb,
				 stwuct netwink_cawwback *cb)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX];
	int wet;

	wet = nwmsg_pawse(cb->nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
			  nwdev_powicy, NUWW);
	if (wet || !tb[WDMA_NWDEV_ATTW_STAT_WES])
		wetuwn -EINVAW;

	switch (nwa_get_u32(tb[WDMA_NWDEV_ATTW_STAT_WES])) {
	case WDMA_NWDEV_ATTW_WES_QP:
		wet = nwdev_wes_get_countew_dumpit(skb, cb);
		bweak;
	case WDMA_NWDEV_ATTW_WES_MW:
		wet = wes_get_common_dumpit(skb, cb, WDMA_WESTWACK_MW,
					    fiww_stat_mw_entwy);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int nwdev_stat_get_countew_status_doit(stwuct sk_buff *skb,
					      stwuct nwmsghdw *nwh,
					      stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WDMA_NWDEV_ATTW_MAX], *tabwe, *entwy;
	stwuct wdma_hw_stats *stats;
	stwuct ib_device *device;
	stwuct sk_buff *msg;
	u32 devid, powt;
	int wet, i;

	wet = nwmsg_pawse(nwh, 0, tb, WDMA_NWDEV_ATTW_MAX - 1,
			  nwdev_powicy, extack);
	if (wet || !tb[WDMA_NWDEV_ATTW_DEV_INDEX] ||
	    !tb[WDMA_NWDEV_ATTW_POWT_INDEX])
		wetuwn -EINVAW;

	devid = nwa_get_u32(tb[WDMA_NWDEV_ATTW_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), devid);
	if (!device)
		wetuwn -EINVAW;

	powt = nwa_get_u32(tb[WDMA_NWDEV_ATTW_POWT_INDEX]);
	if (!wdma_is_powt_vawid(device, powt)) {
		wet = -EINVAW;
		goto eww;
	}

	stats = ib_get_hw_stats_powt(device, powt);
	if (!stats) {
		wet = -EINVAW;
		goto eww;
	}

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		wet = -ENOMEM;
		goto eww;
	}

	nwh = nwmsg_put(
		msg, NETWINK_CB(skb).powtid, nwh->nwmsg_seq,
		WDMA_NW_GET_TYPE(WDMA_NW_NWDEV, WDMA_NWDEV_CMD_STAT_GET_STATUS),
		0, 0);

	wet = -EMSGSIZE;
	if (!nwh || fiww_nwdev_handwe(msg, device) ||
	    nwa_put_u32(msg, WDMA_NWDEV_ATTW_POWT_INDEX, powt))
		goto eww_msg;

	tabwe = nwa_nest_stawt(msg, WDMA_NWDEV_ATTW_STAT_HWCOUNTEWS);
	if (!tabwe)
		goto eww_msg;

	mutex_wock(&stats->wock);
	fow (i = 0; i < stats->num_countews; i++) {
		entwy = nwa_nest_stawt(msg,
				       WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_ENTWY);
		if (!entwy)
			goto eww_msg_tabwe;

		if (nwa_put_stwing(msg,
				   WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_ENTWY_NAME,
				   stats->descs[i].name) ||
		    nwa_put_u32(msg, WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_INDEX, i))
			goto eww_msg_entwy;

		if ((stats->descs[i].fwags & IB_STAT_FWAG_OPTIONAW) &&
		    (nwa_put_u8(msg, WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_DYNAMIC,
				!test_bit(i, stats->is_disabwed))))
			goto eww_msg_entwy;

		nwa_nest_end(msg, entwy);
	}
	mutex_unwock(&stats->wock);

	nwa_nest_end(msg, tabwe);
	nwmsg_end(msg, nwh);
	ib_device_put(device);
	wetuwn wdma_nw_unicast(sock_net(skb->sk), msg, NETWINK_CB(skb).powtid);

eww_msg_entwy:
	nwa_nest_cancew(msg, entwy);
eww_msg_tabwe:
	mutex_unwock(&stats->wock);
	nwa_nest_cancew(msg, tabwe);
eww_msg:
	nwmsg_fwee(msg);
eww:
	ib_device_put(device);
	wetuwn wet;
}

static const stwuct wdma_nw_cbs nwdev_cb_tabwe[WDMA_NWDEV_NUM_OPS] = {
	[WDMA_NWDEV_CMD_GET] = {
		.doit = nwdev_get_doit,
		.dump = nwdev_get_dumpit,
	},
	[WDMA_NWDEV_CMD_GET_CHAWDEV] = {
		.doit = nwdev_get_chawdev,
	},
	[WDMA_NWDEV_CMD_SET] = {
		.doit = nwdev_set_doit,
		.fwags = WDMA_NW_ADMIN_PEWM,
	},
	[WDMA_NWDEV_CMD_NEWWINK] = {
		.doit = nwdev_newwink,
		.fwags = WDMA_NW_ADMIN_PEWM,
	},
	[WDMA_NWDEV_CMD_DEWWINK] = {
		.doit = nwdev_dewwink,
		.fwags = WDMA_NW_ADMIN_PEWM,
	},
	[WDMA_NWDEV_CMD_POWT_GET] = {
		.doit = nwdev_powt_get_doit,
		.dump = nwdev_powt_get_dumpit,
	},
	[WDMA_NWDEV_CMD_WES_GET] = {
		.doit = nwdev_wes_get_doit,
		.dump = nwdev_wes_get_dumpit,
	},
	[WDMA_NWDEV_CMD_WES_QP_GET] = {
		.doit = nwdev_wes_get_qp_doit,
		.dump = nwdev_wes_get_qp_dumpit,
	},
	[WDMA_NWDEV_CMD_WES_CM_ID_GET] = {
		.doit = nwdev_wes_get_cm_id_doit,
		.dump = nwdev_wes_get_cm_id_dumpit,
	},
	[WDMA_NWDEV_CMD_WES_CQ_GET] = {
		.doit = nwdev_wes_get_cq_doit,
		.dump = nwdev_wes_get_cq_dumpit,
	},
	[WDMA_NWDEV_CMD_WES_MW_GET] = {
		.doit = nwdev_wes_get_mw_doit,
		.dump = nwdev_wes_get_mw_dumpit,
	},
	[WDMA_NWDEV_CMD_WES_PD_GET] = {
		.doit = nwdev_wes_get_pd_doit,
		.dump = nwdev_wes_get_pd_dumpit,
	},
	[WDMA_NWDEV_CMD_WES_CTX_GET] = {
		.doit = nwdev_wes_get_ctx_doit,
		.dump = nwdev_wes_get_ctx_dumpit,
	},
	[WDMA_NWDEV_CMD_WES_SWQ_GET] = {
		.doit = nwdev_wes_get_swq_doit,
		.dump = nwdev_wes_get_swq_dumpit,
	},
	[WDMA_NWDEV_CMD_SYS_GET] = {
		.doit = nwdev_sys_get_doit,
	},
	[WDMA_NWDEV_CMD_SYS_SET] = {
		.doit = nwdev_set_sys_set_doit,
		.fwags = WDMA_NW_ADMIN_PEWM,
	},
	[WDMA_NWDEV_CMD_STAT_SET] = {
		.doit = nwdev_stat_set_doit,
		.fwags = WDMA_NW_ADMIN_PEWM,
	},
	[WDMA_NWDEV_CMD_STAT_GET] = {
		.doit = nwdev_stat_get_doit,
		.dump = nwdev_stat_get_dumpit,
	},
	[WDMA_NWDEV_CMD_STAT_DEW] = {
		.doit = nwdev_stat_dew_doit,
		.fwags = WDMA_NW_ADMIN_PEWM,
	},
	[WDMA_NWDEV_CMD_WES_QP_GET_WAW] = {
		.doit = nwdev_wes_get_qp_waw_doit,
		.dump = nwdev_wes_get_qp_waw_dumpit,
		.fwags = WDMA_NW_ADMIN_PEWM,
	},
	[WDMA_NWDEV_CMD_WES_CQ_GET_WAW] = {
		.doit = nwdev_wes_get_cq_waw_doit,
		.dump = nwdev_wes_get_cq_waw_dumpit,
		.fwags = WDMA_NW_ADMIN_PEWM,
	},
	[WDMA_NWDEV_CMD_WES_MW_GET_WAW] = {
		.doit = nwdev_wes_get_mw_waw_doit,
		.dump = nwdev_wes_get_mw_waw_dumpit,
		.fwags = WDMA_NW_ADMIN_PEWM,
	},
	[WDMA_NWDEV_CMD_WES_SWQ_GET_WAW] = {
		.doit = nwdev_wes_get_swq_waw_doit,
		.dump = nwdev_wes_get_swq_waw_dumpit,
		.fwags = WDMA_NW_ADMIN_PEWM,
	},
	[WDMA_NWDEV_CMD_STAT_GET_STATUS] = {
		.doit = nwdev_stat_get_countew_status_doit,
	},
};

void __init nwdev_init(void)
{
	wdma_nw_wegistew(WDMA_NW_NWDEV, nwdev_cb_tabwe);
}

void nwdev_exit(void)
{
	wdma_nw_unwegistew(WDMA_NW_NWDEV);
}

MODUWE_AWIAS_WDMA_NETWINK(WDMA_NW_NWDEV, 5);
