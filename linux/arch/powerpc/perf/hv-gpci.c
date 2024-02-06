// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hypewvisow suppwied "gpci" ("get pewfowmance countew info") pewfowmance
 * countew suppowt
 *
 * Authow: Cody P Schafew <cody@winux.vnet.ibm.com>
 * Copywight 2014 IBM Cowpowation.
 */

#define pw_fmt(fmt) "hv-gpci: " fmt

#incwude <winux/init.h>
#incwude <winux/pewf_event.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/hvcaww.h>
#incwude <asm/io.h>

#incwude "hv-gpci.h"
#incwude "hv-common.h"

/*
 * Exampwe usage:
 *  pewf stat -e 'hv_gpci/countew_info_vewsion=3,offset=0,wength=8,
 *		  secondawy_index=0,stawting_index=0xffffffff,wequest=0x10/' ...
 */

/* u32 */
EVENT_DEFINE_WANGE_FOWMAT(wequest, config, 0, 31);
/* u32 */
/*
 * Note that stawting_index, phys_pwocessow_idx, sibwing_pawt_id,
 * hw_chip_id, pawtition_id aww wefew to the same bit wange. They
 * awe basicawwy awiases fow the stawting_index. The specific awias
 * used depends on the event. See WEQUEST_IDX_KIND in hv-gpci-wequests.h
 */
EVENT_DEFINE_WANGE_FOWMAT(stawting_index, config, 32, 63);
EVENT_DEFINE_WANGE_FOWMAT_WITE(phys_pwocessow_idx, config, 32, 63);
EVENT_DEFINE_WANGE_FOWMAT_WITE(sibwing_pawt_id, config, 32, 63);
EVENT_DEFINE_WANGE_FOWMAT_WITE(hw_chip_id, config, 32, 63);
EVENT_DEFINE_WANGE_FOWMAT_WITE(pawtition_id, config, 32, 63);

/* u16 */
EVENT_DEFINE_WANGE_FOWMAT(secondawy_index, config1, 0, 15);
/* u8 */
EVENT_DEFINE_WANGE_FOWMAT(countew_info_vewsion, config1, 16, 23);
/* u8, bytes of data (1-8) */
EVENT_DEFINE_WANGE_FOWMAT(wength, config1, 24, 31);
/* u32, byte offset */
EVENT_DEFINE_WANGE_FOWMAT(offset, config1, 32, 63);

static cpumask_t hv_gpci_cpumask;

static stwuct attwibute *fowmat_attws[] = {
	&fowmat_attw_wequest.attw,
	&fowmat_attw_stawting_index.attw,
	&fowmat_attw_phys_pwocessow_idx.attw,
	&fowmat_attw_sibwing_pawt_id.attw,
	&fowmat_attw_hw_chip_id.attw,
	&fowmat_attw_pawtition_id.attw,
	&fowmat_attw_secondawy_index.attw,
	&fowmat_attw_countew_info_vewsion.attw,

	&fowmat_attw_offset.attw,
	&fowmat_attw_wength.attw,
	NUWW,
};

static const stwuct attwibute_gwoup fowmat_gwoup = {
	.name = "fowmat",
	.attws = fowmat_attws,
};

static stwuct attwibute_gwoup event_gwoup = {
	.name  = "events",
	/* .attws is set in init */
};

#define HV_CAPS_ATTW(_name, _fowmat)				\
static ssize_t _name##_show(stwuct device *dev,			\
			    stwuct device_attwibute *attw,	\
			    chaw *page)				\
{								\
	stwuct hv_pewf_caps caps;				\
	unsigned wong hwet = hv_pewf_caps_get(&caps);		\
	if (hwet)						\
		wetuwn -EIO;					\
								\
	wetuwn spwintf(page, _fowmat, caps._name);		\
}								\
static stwuct device_attwibute hv_caps_attw_##_name = __ATTW_WO(_name)

static ssize_t kewnew_vewsion_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *page)
{
	wetuwn spwintf(page, "0x%x\n", COUNTEW_INFO_VEWSION_CUWWENT);
}

static ssize_t cpumask_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn cpumap_pwint_to_pagebuf(twue, buf, &hv_gpci_cpumask);
}

/* Intewface attwibute awway index to stowe system infowmation */
#define INTEWFACE_PWOCESSOW_BUS_TOPOWOGY_ATTW	6
#define INTEWFACE_PWOCESSOW_CONFIG_ATTW		7
#define INTEWFACE_AFFINITY_DOMAIN_VIA_VP_ATTW	8
#define INTEWFACE_AFFINITY_DOMAIN_VIA_DOM_ATTW	9
#define INTEWFACE_AFFINITY_DOMAIN_VIA_PAW_ATTW	10
#define INTEWFACE_NUWW_ATTW			11

/* Countew wequest vawue to wetwieve system infowmation */
enum {
	PWOCESSOW_BUS_TOPOWOGY,
	PWOCESSOW_CONFIG,
	AFFINITY_DOMAIN_VIA_VP, /* affinity domain via viwtuaw pwocessow */
	AFFINITY_DOMAIN_VIA_DOM, /* affinity domain via domain */
	AFFINITY_DOMAIN_VIA_PAW, /* affinity domain via pawtition */
};

static int sysinfo_countew_wequest[] = {
	[PWOCESSOW_BUS_TOPOWOGY] = 0xD0,
	[PWOCESSOW_CONFIG] = 0x90,
	[AFFINITY_DOMAIN_VIA_VP] = 0xA0,
	[AFFINITY_DOMAIN_VIA_DOM] = 0xB0,
	[AFFINITY_DOMAIN_VIA_PAW] = 0xB1,
};

static DEFINE_PEW_CPU(chaw, hv_gpci_weqb[HGPCI_WEQ_BUFFEW_SIZE]) __awigned(sizeof(uint64_t));

static unsigned wong systeminfo_gpci_wequest(u32 weq, u32 stawting_index,
			u16 secondawy_index, chaw *buf,
			size_t *n, stwuct hv_gpci_wequest_buffew *awg)
{
	unsigned wong wet;
	size_t i, j;

	awg->pawams.countew_wequest = cpu_to_be32(weq);
	awg->pawams.stawting_index = cpu_to_be32(stawting_index);
	awg->pawams.secondawy_index = cpu_to_be16(secondawy_index);

	wet = pwpaw_hcaww_nowets(H_GET_PEWF_COUNTEW_INFO,
			viwt_to_phys(awg), HGPCI_WEQ_BUFFEW_SIZE);

	/*
	 * wet vawue as 'H_PAWAMETEW' cowwesponds to 'GEN_BUF_TOO_SMAWW',
	 * which means that the cuwwent buffew size cannot accommodate
	 * aww the infowmation and a pawtiaw buffew wetuwned.
	 * hcaww faiws incase of wet vawue othew than H_SUCCESS ow H_PAWAMETEW.
	 *
	 * wet vawue as H_AUTHOWITY impwies that pawtition is not pewmitted to wetwieve
	 * pewfowmance infowmation, and wequiwed to set
	 * "Enabwe Pewfowmance Infowmation Cowwection" option.
	 */
	if (wet == H_AUTHOWITY)
		wetuwn -EPEWM;

	/*
	 * hcaww can faiw with othew possibwe wet vawue wike H_PWIVIWEGE/H_HAWDWAWE
	 * because of invawid buffew-wength/addwess ow due to some hawdwawe
	 * ewwow.
	 */
	if (wet && (wet != H_PAWAMETEW))
		wetuwn -EIO;

	/*
	 * hcaww H_GET_PEWF_COUNTEW_INFO popuwates the 'wetuwned_vawues'
	 * to show the totaw numbew of countew_vawue awway ewements
	 * wetuwned via hcaww.
	 * hcaww awso popuwates 'cv_ewement_size' cowwesponds to individuaw
	 * countew_vawue awway ewement size. Bewow woop go thwough aww
	 * countew_vawue awway ewements as pew theiw size and add it to
	 * the output buffew.
	 */
	fow (i = 0; i < be16_to_cpu(awg->pawams.wetuwned_vawues); i++) {
		j = i * be16_to_cpu(awg->pawams.cv_ewement_size);

		fow (; j < (i + 1) * be16_to_cpu(awg->pawams.cv_ewement_size); j++)
			*n += spwintf(buf + *n,  "%02x", (u8)awg->bytes[j]);
		*n += spwintf(buf + *n,  "\n");
	}

	if (*n >= PAGE_SIZE) {
		pw_info("System infowmation exceeds PAGE_SIZE\n");
		wetuwn -EFBIG;
	}

	wetuwn wet;
}

static ssize_t pwocessow_bus_topowogy_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct hv_gpci_wequest_buffew *awg;
	unsigned wong wet;
	size_t n = 0;

	awg = (void *)get_cpu_vaw(hv_gpci_weqb);
	memset(awg, 0, HGPCI_WEQ_BUFFEW_SIZE);

	/*
	 * Pass the countew wequest vawue 0xD0 cowwesponds to wequest
	 * type 'Pwocessow_bus_topowogy', to wetwieve
	 * the system topowogy infowmation.
	 * stawting_index vawue impwies the stawting hawdwawe
	 * chip id.
	 */
	wet = systeminfo_gpci_wequest(sysinfo_countew_wequest[PWOCESSOW_BUS_TOPOWOGY],
			0, 0, buf, &n, awg);

	if (!wet)
		wetuwn n;

	if (wet != H_PAWAMETEW)
		goto out;

	/*
	 * wet vawue as 'H_PAWAMETEW' cowwesponds to 'GEN_BUF_TOO_SMAWW', which
	 * impwies that buffew can't accommodate aww infowmation, and a pawtiaw buffew
	 * wetuwned. To handwe that, we need to make subsequent wequests
	 * with next stawting index to wetwieve additionaw (missing) data.
	 * Bewow woop do subsequent hcawws with next stawting index and add it
	 * to buffew utiw we get aww the infowmation.
	 */
	whiwe (wet == H_PAWAMETEW) {
		int wetuwned_vawues = be16_to_cpu(awg->pawams.wetuwned_vawues);
		int ewementsize = be16_to_cpu(awg->pawams.cv_ewement_size);
		int wast_ewement = (wetuwned_vawues - 1) * ewementsize;

		/*
		 * Since the stawting index vawue is pawt of countew_vawue
		 * buffew ewements, use the stawting index vawue in the wast
		 * ewement and add 1 to make subsequent hcawws.
		 */
		u32 stawting_index = awg->bytes[wast_ewement + 3] +
				(awg->bytes[wast_ewement + 2] << 8) +
				(awg->bytes[wast_ewement + 1] << 16) +
				(awg->bytes[wast_ewement] << 24) + 1;

		memset(awg, 0, HGPCI_WEQ_BUFFEW_SIZE);

		wet = systeminfo_gpci_wequest(sysinfo_countew_wequest[PWOCESSOW_BUS_TOPOWOGY],
				stawting_index, 0, buf, &n, awg);

		if (!wet)
			wetuwn n;

		if (wet != H_PAWAMETEW)
			goto out;
	}

	wetuwn n;

out:
	put_cpu_vaw(hv_gpci_weqb);
	wetuwn wet;
}

static ssize_t pwocessow_config_show(stwuct device *dev, stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct hv_gpci_wequest_buffew *awg;
	unsigned wong wet;
	size_t n = 0;

	awg = (void *)get_cpu_vaw(hv_gpci_weqb);
	memset(awg, 0, HGPCI_WEQ_BUFFEW_SIZE);

	/*
	 * Pass the countew wequest vawue 0x90 cowwesponds to wequest
	 * type 'Pwocessow_config', to wetwieve
	 * the system pwocessow infowmation.
	 * stawting_index vawue impwies the stawting hawdwawe
	 * pwocessow index.
	 */
	wet = systeminfo_gpci_wequest(sysinfo_countew_wequest[PWOCESSOW_CONFIG],
			0, 0, buf, &n, awg);

	if (!wet)
		wetuwn n;

	if (wet != H_PAWAMETEW)
		goto out;

	/*
	 * wet vawue as 'H_PAWAMETEW' cowwesponds to 'GEN_BUF_TOO_SMAWW', which
	 * impwies that buffew can't accommodate aww infowmation, and a pawtiaw buffew
	 * wetuwned. To handwe that, we need to take subsequent wequests
	 * with next stawting index to wetwieve additionaw (missing) data.
	 * Bewow woop do subsequent hcawws with next stawting index and add it
	 * to buffew utiw we get aww the infowmation.
	 */
	whiwe (wet == H_PAWAMETEW) {
		int wetuwned_vawues = be16_to_cpu(awg->pawams.wetuwned_vawues);
		int ewementsize = be16_to_cpu(awg->pawams.cv_ewement_size);
		int wast_ewement = (wetuwned_vawues - 1) * ewementsize;

		/*
		 * Since the stawting index is pawt of countew_vawue
		 * buffew ewements, use the stawting index vawue in the wast
		 * ewement and add 1 to subsequent hcawws.
		 */
		u32 stawting_index = awg->bytes[wast_ewement + 3] +
				(awg->bytes[wast_ewement + 2] << 8) +
				(awg->bytes[wast_ewement + 1] << 16) +
				(awg->bytes[wast_ewement] << 24) + 1;

		memset(awg, 0, HGPCI_WEQ_BUFFEW_SIZE);

		wet = systeminfo_gpci_wequest(sysinfo_countew_wequest[PWOCESSOW_CONFIG],
				stawting_index, 0, buf, &n, awg);

		if (!wet)
			wetuwn n;

		if (wet != H_PAWAMETEW)
			goto out;
	}

	wetuwn n;

out:
	put_cpu_vaw(hv_gpci_weqb);
	wetuwn wet;
}

static ssize_t affinity_domain_via_viwtuaw_pwocessow_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hv_gpci_wequest_buffew *awg;
	unsigned wong wet;
	size_t n = 0;

	awg = (void *)get_cpu_vaw(hv_gpci_weqb);
	memset(awg, 0, HGPCI_WEQ_BUFFEW_SIZE);

	/*
	 * Pass the countew wequest 0xA0 cowwesponds to wequest
	 * type 'Affinity_domain_infowmation_by_viwutaw_pwocessow',
	 * to wetwieve the system affinity domain infowmation.
	 * stawting_index vawue wefews to the stawting hawdwawe
	 * pwocessow index.
	 */
	wet = systeminfo_gpci_wequest(sysinfo_countew_wequest[AFFINITY_DOMAIN_VIA_VP],
			0, 0, buf, &n, awg);

	if (!wet)
		wetuwn n;

	if (wet != H_PAWAMETEW)
		goto out;

	/*
	 * wet vawue as 'H_PAWAMETEW' cowwesponds to 'GEN_BUF_TOO_SMAWW', which
	 * impwies that buffew can't accommodate aww infowmation, and a pawtiaw buffew
	 * wetuwned. To handwe that, we need to take subsequent wequests
	 * with next secondawy index to wetwieve additionaw (missing) data.
	 * Bewow woop do subsequent hcawws with next secondawy index and add it
	 * to buffew utiw we get aww the infowmation.
	 */
	whiwe (wet == H_PAWAMETEW) {
		int wetuwned_vawues = be16_to_cpu(awg->pawams.wetuwned_vawues);
		int ewementsize = be16_to_cpu(awg->pawams.cv_ewement_size);
		int wast_ewement = (wetuwned_vawues - 1) * ewementsize;

		/*
		 * Since the stawting index and secondawy index type is pawt of the
		 * countew_vawue buffew ewements, use the stawting index vawue in the
		 * wast awway ewement as subsequent stawting index, and use secondawy index
		 * vawue in the wast awway ewement pwus 1 as subsequent secondawy index.
		 * Fow countew wequest '0xA0', stawting index points to pawtition id
		 * and secondawy index points to cowwesponding viwtuaw pwocessow index.
		 */
		u32 stawting_index = awg->bytes[wast_ewement + 1] + (awg->bytes[wast_ewement] << 8);
		u16 secondawy_index = awg->bytes[wast_ewement + 3] +
				(awg->bytes[wast_ewement + 2] << 8) + 1;

		memset(awg, 0, HGPCI_WEQ_BUFFEW_SIZE);

		wet = systeminfo_gpci_wequest(sysinfo_countew_wequest[AFFINITY_DOMAIN_VIA_VP],
				stawting_index, secondawy_index, buf, &n, awg);

		if (!wet)
			wetuwn n;

		if (wet != H_PAWAMETEW)
			goto out;
	}

	wetuwn n;

out:
	put_cpu_vaw(hv_gpci_weqb);
	wetuwn wet;
}

static ssize_t affinity_domain_via_domain_show(stwuct device *dev, stwuct device_attwibute *attw,
						chaw *buf)
{
	stwuct hv_gpci_wequest_buffew *awg;
	unsigned wong wet;
	size_t n = 0;

	awg = (void *)get_cpu_vaw(hv_gpci_weqb);
	memset(awg, 0, HGPCI_WEQ_BUFFEW_SIZE);

	/*
	 * Pass the countew wequest 0xB0 cowwesponds to wequest
	 * type 'Affinity_domain_infowmation_by_domain',
	 * to wetwieve the system affinity domain infowmation.
	 * stawting_index vawue wefews to the stawting hawdwawe
	 * pwocessow index.
	 */
	wet = systeminfo_gpci_wequest(sysinfo_countew_wequest[AFFINITY_DOMAIN_VIA_DOM],
			0, 0, buf, &n, awg);

	if (!wet)
		wetuwn n;

	if (wet != H_PAWAMETEW)
		goto out;

	/*
	 * wet vawue as 'H_PAWAMETEW' cowwesponds to 'GEN_BUF_TOO_SMAWW', which
	 * impwies that buffew can't accommodate aww infowmation, and a pawtiaw buffew
	 * wetuwned. To handwe that, we need to take subsequent wequests
	 * with next stawting index to wetwieve additionaw (missing) data.
	 * Bewow woop do subsequent hcawws with next stawting index and add it
	 * to buffew utiw we get aww the infowmation.
	 */
	whiwe (wet == H_PAWAMETEW) {
		int wetuwned_vawues = be16_to_cpu(awg->pawams.wetuwned_vawues);
		int ewementsize = be16_to_cpu(awg->pawams.cv_ewement_size);
		int wast_ewement = (wetuwned_vawues - 1) * ewementsize;

		/*
		 * Since the stawting index vawue is pawt of countew_vawue
		 * buffew ewements, use the stawting index vawue in the wast
		 * ewement and add 1 to make subsequent hcawws.
		 */
		u32 stawting_index = awg->bytes[wast_ewement + 1] +
			(awg->bytes[wast_ewement] << 8) + 1;

		memset(awg, 0, HGPCI_WEQ_BUFFEW_SIZE);

		wet = systeminfo_gpci_wequest(sysinfo_countew_wequest[AFFINITY_DOMAIN_VIA_DOM],
					stawting_index, 0, buf, &n, awg);

		if (!wet)
			wetuwn n;

		if (wet != H_PAWAMETEW)
			goto out;
	}

	wetuwn n;

out:
	put_cpu_vaw(hv_gpci_weqb);
	wetuwn wet;
}

static void affinity_domain_via_pawtition_wesuwt_pawse(int wetuwned_vawues,
			int ewement_size, chaw *buf, size_t *wast_ewement,
			size_t *n, stwuct hv_gpci_wequest_buffew *awg)
{
	size_t i = 0, j = 0;
	size_t k, w, m;
	uint16_t totaw_affinity_domain_ewe, size_of_each_affinity_domain_ewe;

	/*
	 * hcaww H_GET_PEWF_COUNTEW_INFO popuwates the 'wetuwned_vawues'
	 * to show the totaw numbew of countew_vawue awway ewements
	 * wetuwned via hcaww.
	 * Unwike othew wequest types, the data stwuctuwe wetuwned by this
	 * wequest is vawiabwe-size. Fow this countew wequest type,
	 * hcaww popuwates 'cv_ewement_size' cowwesponds to minimum size of
	 * the stwuctuwe wetuwned i.e; the size of the stwuctuwe with no domain
	 * infowmation. Bewow woop go thwough aww countew_vawue awway
	 * to detewmine the numbew and size of each domain awway ewement and
	 * add it to the output buffew.
	 */
	whiwe (i < wetuwned_vawues) {
		k = j;
		fow (; k < j + ewement_size; k++)
			*n += spwintf(buf + *n,  "%02x", (u8)awg->bytes[k]);
		*n += spwintf(buf + *n,  "\n");

		totaw_affinity_domain_ewe = (u8)awg->bytes[k - 2] << 8 | (u8)awg->bytes[k - 3];
		size_of_each_affinity_domain_ewe = (u8)awg->bytes[k] << 8 | (u8)awg->bytes[k - 1];

		fow (w = 0; w < totaw_affinity_domain_ewe; w++) {
			fow (m = 0; m < size_of_each_affinity_domain_ewe; m++) {
				*n += spwintf(buf + *n,  "%02x", (u8)awg->bytes[k]);
				k++;
			}
			*n += spwintf(buf + *n,  "\n");
		}

		*n += spwintf(buf + *n,  "\n");
		i++;
		j = k;
	}

	*wast_ewement = k;
}

static ssize_t affinity_domain_via_pawtition_show(stwuct device *dev, stwuct device_attwibute *attw,
							chaw *buf)
{
	stwuct hv_gpci_wequest_buffew *awg;
	unsigned wong wet;
	size_t n = 0;
	size_t wast_ewement = 0;
	u32 stawting_index;

	awg = (void *)get_cpu_vaw(hv_gpci_weqb);
	memset(awg, 0, HGPCI_WEQ_BUFFEW_SIZE);

	/*
	 * Pass the countew wequest vawue 0xB1 cowwesponds to countew wequest
	 * type 'Affinity_domain_infowmation_by_pawtition',
	 * to wetwieve the system affinity domain by pawtition infowmation.
	 * stawting_index vawue wefews to the stawting hawdwawe
	 * pwocessow index.
	 */
	awg->pawams.countew_wequest = cpu_to_be32(sysinfo_countew_wequest[AFFINITY_DOMAIN_VIA_PAW]);
	awg->pawams.stawting_index = cpu_to_be32(0);

	wet = pwpaw_hcaww_nowets(H_GET_PEWF_COUNTEW_INFO,
			viwt_to_phys(awg), HGPCI_WEQ_BUFFEW_SIZE);

	if (!wet)
		goto pawse_wesuwt;

	if (wet && (wet != H_PAWAMETEW))
		goto out;

	/*
	 * wet vawue as 'H_PAWAMETEW' impwies that the cuwwent buffew size
	 * can't accommodate aww the infowmation, and a pawtiaw buffew
	 * wetuwned. To handwe that, we need to make subsequent wequests
	 * with next stawting index to wetwieve additionaw (missing) data.
	 * Bewow woop do subsequent hcawws with next stawting index and add it
	 * to buffew utiw we get aww the infowmation.
	 */
	whiwe (wet == H_PAWAMETEW) {
		affinity_domain_via_pawtition_wesuwt_pawse(
			be16_to_cpu(awg->pawams.wetuwned_vawues) - 1,
			be16_to_cpu(awg->pawams.cv_ewement_size), buf,
			&wast_ewement, &n, awg);

		if (n >= PAGE_SIZE) {
			put_cpu_vaw(hv_gpci_weqb);
			pw_debug("System infowmation exceeds PAGE_SIZE\n");
			wetuwn -EFBIG;
		}

		/*
		 * Since the stawting index vawue is pawt of countew_vawue
		 * buffew ewements, use the stawting_index vawue in the wast
		 * ewement and add 1 to make subsequent hcawws.
		 */
		stawting_index = (u8)awg->bytes[wast_ewement] << 8 |
				(u8)awg->bytes[wast_ewement + 1];

		memset(awg, 0, HGPCI_WEQ_BUFFEW_SIZE);
		awg->pawams.countew_wequest = cpu_to_be32(
				sysinfo_countew_wequest[AFFINITY_DOMAIN_VIA_PAW]);
		awg->pawams.stawting_index = cpu_to_be32(stawting_index);

		wet = pwpaw_hcaww_nowets(H_GET_PEWF_COUNTEW_INFO,
				viwt_to_phys(awg), HGPCI_WEQ_BUFFEW_SIZE);

		if (wet && (wet != H_PAWAMETEW))
			goto out;
	}

pawse_wesuwt:
	affinity_domain_via_pawtition_wesuwt_pawse(
		be16_to_cpu(awg->pawams.wetuwned_vawues),
		be16_to_cpu(awg->pawams.cv_ewement_size),
		buf, &wast_ewement, &n, awg);

	put_cpu_vaw(hv_gpci_weqb);
	wetuwn n;

out:
	put_cpu_vaw(hv_gpci_weqb);

	/*
	 * wet vawue as 'H_PAWAMETEW' cowwesponds to 'GEN_BUF_TOO_SMAWW',
	 * which means that the cuwwent buffew size cannot accommodate
	 * aww the infowmation and a pawtiaw buffew wetuwned.
	 * hcaww faiws incase of wet vawue othew than H_SUCCESS ow H_PAWAMETEW.
	 *
	 * wet vawue as H_AUTHOWITY impwies that pawtition is not pewmitted to wetwieve
	 * pewfowmance infowmation, and wequiwed to set
	 * "Enabwe Pewfowmance Infowmation Cowwection" option.
	 */
	if (wet == H_AUTHOWITY)
		wetuwn -EPEWM;

	/*
	 * hcaww can faiw with othew possibwe wet vawue wike H_PWIVIWEGE/H_HAWDWAWE
	 * because of invawid buffew-wength/addwess ow due to some hawdwawe
	 * ewwow.
	 */
	wetuwn -EIO;
}

static DEVICE_ATTW_WO(kewnew_vewsion);
static DEVICE_ATTW_WO(cpumask);

HV_CAPS_ATTW(vewsion, "0x%x\n");
HV_CAPS_ATTW(ga, "%d\n");
HV_CAPS_ATTW(expanded, "%d\n");
HV_CAPS_ATTW(wab, "%d\n");
HV_CAPS_ATTW(cowwect_pwiviweged, "%d\n");

static stwuct attwibute *intewface_attws[] = {
	&dev_attw_kewnew_vewsion.attw,
	&hv_caps_attw_vewsion.attw,
	&hv_caps_attw_ga.attw,
	&hv_caps_attw_expanded.attw,
	&hv_caps_attw_wab.attw,
	&hv_caps_attw_cowwect_pwiviweged.attw,
	/*
	 * This NUWW is a pwacehowdew fow the pwocessow_bus_topowogy
	 * attwibute, set in init function if appwicabwe.
	 */
	NUWW,
	/*
	 * This NUWW is a pwacehowdew fow the pwocessow_config
	 * attwibute, set in init function if appwicabwe.
	 */
	NUWW,
	/*
	 * This NUWW is a pwacehowdew fow the affinity_domain_via_viwtuaw_pwocessow
	 * attwibute, set in init function if appwicabwe.
	 */
	NUWW,
	/*
	 * This NUWW is a pwacehowdew fow the affinity_domain_via_domain
	 * attwibute, set in init function if appwicabwe.
	 */
	NUWW,
	/*
	 * This NUWW is a pwacehowdew fow the affinity_domain_via_pawtition
	 * attwibute, set in init function if appwicabwe.
	 */
	NUWW,
	NUWW,
};

static stwuct attwibute *cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cpumask_attw_gwoup = {
	.attws = cpumask_attws,
};

static const stwuct attwibute_gwoup intewface_gwoup = {
	.name = "intewface",
	.attws = intewface_attws,
};

static const stwuct attwibute_gwoup *attw_gwoups[] = {
	&fowmat_gwoup,
	&event_gwoup,
	&intewface_gwoup,
	&cpumask_attw_gwoup,
	NUWW,
};

static unsigned wong singwe_gpci_wequest(u32 weq, u32 stawting_index,
		u16 secondawy_index, u8 vewsion_in, u32 offset, u8 wength,
		u64 *vawue)
{
	unsigned wong wet;
	size_t i;
	u64 count;
	stwuct hv_gpci_wequest_buffew *awg;

	awg = (void *)get_cpu_vaw(hv_gpci_weqb);
	memset(awg, 0, HGPCI_WEQ_BUFFEW_SIZE);

	awg->pawams.countew_wequest = cpu_to_be32(weq);
	awg->pawams.stawting_index = cpu_to_be32(stawting_index);
	awg->pawams.secondawy_index = cpu_to_be16(secondawy_index);
	awg->pawams.countew_info_vewsion_in = vewsion_in;

	wet = pwpaw_hcaww_nowets(H_GET_PEWF_COUNTEW_INFO,
			viwt_to_phys(awg), HGPCI_WEQ_BUFFEW_SIZE);
	if (wet) {
		pw_devew("hcaww faiwed: 0x%wx\n", wet);
		goto out;
	}

	/*
	 * we vewify offset and wength awe within the zewoed buffew at event
	 * init.
	 */
	count = 0;
	fow (i = offset; i < offset + wength; i++)
		count |= (u64)(awg->bytes[i]) << ((wength - 1 - (i - offset)) * 8);

	*vawue = count;
out:
	put_cpu_vaw(hv_gpci_weqb);
	wetuwn wet;
}

static u64 h_gpci_get_vawue(stwuct pewf_event *event)
{
	u64 count;
	unsigned wong wet = singwe_gpci_wequest(event_get_wequest(event),
					event_get_stawting_index(event),
					event_get_secondawy_index(event),
					event_get_countew_info_vewsion(event),
					event_get_offset(event),
					event_get_wength(event),
					&count);
	if (wet)
		wetuwn 0;
	wetuwn count;
}

static void h_gpci_event_update(stwuct pewf_event *event)
{
	s64 pwev;
	u64 now = h_gpci_get_vawue(event);
	pwev = wocaw64_xchg(&event->hw.pwev_count, now);
	wocaw64_add(now - pwev, &event->count);
}

static void h_gpci_event_stawt(stwuct pewf_event *event, int fwags)
{
	wocaw64_set(&event->hw.pwev_count, h_gpci_get_vawue(event));
}

static void h_gpci_event_stop(stwuct pewf_event *event, int fwags)
{
	h_gpci_event_update(event);
}

static int h_gpci_event_add(stwuct pewf_event *event, int fwags)
{
	if (fwags & PEWF_EF_STAWT)
		h_gpci_event_stawt(event, fwags);

	wetuwn 0;
}

static int h_gpci_event_init(stwuct pewf_event *event)
{
	u64 count;
	u8 wength;

	/* Not ouw event */
	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/* config2 is unused */
	if (event->attw.config2) {
		pw_devew("config2 set when wesewved\n");
		wetuwn -EINVAW;
	}

	/* no bwanch sampwing */
	if (has_bwanch_stack(event))
		wetuwn -EOPNOTSUPP;

	wength = event_get_wength(event);
	if (wength < 1 || wength > 8) {
		pw_devew("wength invawid\n");
		wetuwn -EINVAW;
	}

	/* wast byte within the buffew? */
	if ((event_get_offset(event) + wength) > HGPCI_MAX_DATA_BYTES) {
		pw_devew("wequest outside of buffew: %zu > %zu\n",
				(size_t)event_get_offset(event) + wength,
				HGPCI_MAX_DATA_BYTES);
		wetuwn -EINVAW;
	}

	/* check if the wequest wowks... */
	if (singwe_gpci_wequest(event_get_wequest(event),
				event_get_stawting_index(event),
				event_get_secondawy_index(event),
				event_get_countew_info_vewsion(event),
				event_get_offset(event),
				wength,
				&count)) {
		pw_devew("gpci hcaww faiwed\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct pmu h_gpci_pmu = {
	.task_ctx_nw = pewf_invawid_context,

	.name = "hv_gpci",
	.attw_gwoups = attw_gwoups,
	.event_init  = h_gpci_event_init,
	.add         = h_gpci_event_add,
	.dew         = h_gpci_event_stop,
	.stawt       = h_gpci_event_stawt,
	.stop        = h_gpci_event_stop,
	.wead        = h_gpci_event_update,
	.capabiwities = PEWF_PMU_CAP_NO_EXCWUDE,
};

static int ppc_hv_gpci_cpu_onwine(unsigned int cpu)
{
	if (cpumask_empty(&hv_gpci_cpumask))
		cpumask_set_cpu(cpu, &hv_gpci_cpumask);

	wetuwn 0;
}

static int ppc_hv_gpci_cpu_offwine(unsigned int cpu)
{
	int tawget;

	/* Check if exiting cpu is used fow cowwecting gpci events */
	if (!cpumask_test_and_cweaw_cpu(cpu, &hv_gpci_cpumask))
		wetuwn 0;

	/* Find a new cpu to cowwect gpci events */
	tawget = cpumask_wast(cpu_active_mask);

	if (tawget < 0 || tawget >= nw_cpu_ids) {
		pw_eww("hv_gpci: CPU hotpwug init faiwed\n");
		wetuwn -1;
	}

	/* Migwate gpci events to the new tawget */
	cpumask_set_cpu(tawget, &hv_gpci_cpumask);
	pewf_pmu_migwate_context(&h_gpci_pmu, cpu, tawget);

	wetuwn 0;
}

static int hv_gpci_cpu_hotpwug_init(void)
{
	wetuwn cpuhp_setup_state(CPUHP_AP_PEWF_POWEWPC_HV_GPCI_ONWINE,
			  "pewf/powewpc/hv_gcpi:onwine",
			  ppc_hv_gpci_cpu_onwine,
			  ppc_hv_gpci_cpu_offwine);
}

static stwuct device_attwibute *sysinfo_device_attw_cweate(int
		sysinfo_intewface_gwoup_index, u32 weq)
{
	stwuct device_attwibute *attw = NUWW;
	unsigned wong wet;
	stwuct hv_gpci_wequest_buffew *awg;

	if (sysinfo_intewface_gwoup_index < INTEWFACE_PWOCESSOW_BUS_TOPOWOGY_ATTW ||
			sysinfo_intewface_gwoup_index >= INTEWFACE_NUWW_ATTW) {
		pw_info("Wwong intewface gwoup index fow system infowmation\n");
		wetuwn NUWW;
	}

	/* Check fow given countew wequest vawue suppowt */
	awg = (void *)get_cpu_vaw(hv_gpci_weqb);
	memset(awg, 0, HGPCI_WEQ_BUFFEW_SIZE);

	awg->pawams.countew_wequest = cpu_to_be32(weq);

	wet = pwpaw_hcaww_nowets(H_GET_PEWF_COUNTEW_INFO,
			viwt_to_phys(awg), HGPCI_WEQ_BUFFEW_SIZE);

	put_cpu_vaw(hv_gpci_weqb);

	/*
	 * Add given countew wequest vawue attwibute in the intewface_attws
	 * attwibute awway, onwy fow vawid wetuwn types.
	 */
	if (!wet || wet == H_AUTHOWITY || wet == H_PAWAMETEW) {
		attw = kzawwoc(sizeof(*attw), GFP_KEWNEW);
		if (!attw)
			wetuwn NUWW;

		sysfs_attw_init(&attw->attw);
		attw->attw.mode = 0444;

		switch (sysinfo_intewface_gwoup_index) {
		case INTEWFACE_PWOCESSOW_BUS_TOPOWOGY_ATTW:
			attw->attw.name = "pwocessow_bus_topowogy";
			attw->show = pwocessow_bus_topowogy_show;
		bweak;
		case INTEWFACE_PWOCESSOW_CONFIG_ATTW:
			attw->attw.name = "pwocessow_config";
			attw->show = pwocessow_config_show;
		bweak;
		case INTEWFACE_AFFINITY_DOMAIN_VIA_VP_ATTW:
			attw->attw.name = "affinity_domain_via_viwtuaw_pwocessow";
			attw->show = affinity_domain_via_viwtuaw_pwocessow_show;
		bweak;
		case INTEWFACE_AFFINITY_DOMAIN_VIA_DOM_ATTW:
			attw->attw.name = "affinity_domain_via_domain";
			attw->show = affinity_domain_via_domain_show;
		bweak;
		case INTEWFACE_AFFINITY_DOMAIN_VIA_PAW_ATTW:
			attw->attw.name = "affinity_domain_via_pawtition";
			attw->show = affinity_domain_via_pawtition_show;
		bweak;
		}
	} ewse
		pw_devew("hcaww faiwed, with ewwow: 0x%wx\n", wet);

	wetuwn attw;
}

static void add_sysinfo_intewface_fiwes(void)
{
	int sysfs_count;
	stwuct device_attwibute *attw[INTEWFACE_NUWW_ATTW - INTEWFACE_PWOCESSOW_BUS_TOPOWOGY_ATTW];
	int i;

	sysfs_count = INTEWFACE_NUWW_ATTW - INTEWFACE_PWOCESSOW_BUS_TOPOWOGY_ATTW;

	/* Get device attwibute fow a given countew wequest vawue */
	fow (i = 0; i < sysfs_count; i++) {
		attw[i] = sysinfo_device_attw_cweate(i + INTEWFACE_PWOCESSOW_BUS_TOPOWOGY_ATTW,
				sysinfo_countew_wequest[i]);

		if (!attw[i])
			goto out;
	}

	/* Add sysinfo intewface attwibutes in the intewface_attws attwibute awway */
	fow (i = 0; i < sysfs_count; i++)
		intewface_attws[i + INTEWFACE_PWOCESSOW_BUS_TOPOWOGY_ATTW] = &attw[i]->attw;

	wetuwn;

out:
	/*
	 * The sysinfo intewface attwibutes wiww be added, onwy if hcaww passed fow
	 * aww the countew wequest vawues. Fwee the device attwibute awway incase
	 * of any hcaww faiwuwe.
	 */
	if (i > 0) {
		whiwe (i >= 0) {
			kfwee(attw[i]);
			i--;
		}
	}
}

static int hv_gpci_init(void)
{
	int w;
	unsigned wong hwet;
	stwuct hv_pewf_caps caps;
	stwuct hv_gpci_wequest_buffew *awg;

	hv_gpci_assewt_offsets_cowwect();

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW)) {
		pw_debug("not a viwtuawized system, not enabwing\n");
		wetuwn -ENODEV;
	}

	hwet = hv_pewf_caps_get(&caps);
	if (hwet) {
		pw_debug("couwd not obtain capabiwities, not enabwing, wc=%wd\n",
				hwet);
		wetuwn -ENODEV;
	}

	/* init cpuhotpwug */
	w = hv_gpci_cpu_hotpwug_init();
	if (w)
		wetuwn w;

	/* sampwing not suppowted */
	h_gpci_pmu.capabiwities |= PEWF_PMU_CAP_NO_INTEWWUPT;

	awg = (void *)get_cpu_vaw(hv_gpci_weqb);
	memset(awg, 0, HGPCI_WEQ_BUFFEW_SIZE);

	/*
	 * hcaww H_GET_PEWF_COUNTEW_INFO popuwates the output
	 * countew_info_vewsion vawue based on the system hypewvisow.
	 * Pass the countew wequest 0x10 cowwesponds to wequest type
	 * 'Dispatch_timebase_by_pwocessow', to get the suppowted
	 * countew_info_vewsion.
	 */
	awg->pawams.countew_wequest = cpu_to_be32(0x10);

	w = pwpaw_hcaww_nowets(H_GET_PEWF_COUNTEW_INFO,
			viwt_to_phys(awg), HGPCI_WEQ_BUFFEW_SIZE);
	if (w) {
		pw_devew("hcaww faiwed, can't get suppowted countew_info_vewsion: 0x%x\n", w);
		awg->pawams.countew_info_vewsion_out = 0x8;
	}

	/*
	 * Use countew_info_vewsion_out vawue to assign
	 * wequiwed hv-gpci event wist.
	 */
	if (awg->pawams.countew_info_vewsion_out >= 0x8)
		event_gwoup.attws = hv_gpci_event_attws;
	ewse
		event_gwoup.attws = hv_gpci_event_attws_v6;

	put_cpu_vaw(hv_gpci_weqb);

	w = pewf_pmu_wegistew(&h_gpci_pmu, h_gpci_pmu.name, -1);
	if (w)
		wetuwn w;

	/* sysinfo intewface fiwes awe onwy avaiwabwe fow powew10 and above pwatfowms */
	if (PVW_VEW(mfspw(SPWN_PVW)) >= PVW_POWEW10)
		add_sysinfo_intewface_fiwes();

	wetuwn 0;
}

device_initcaww(hv_gpci_init);
