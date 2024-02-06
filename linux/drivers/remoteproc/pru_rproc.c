// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PWU-ICSS wemotepwoc dwivew fow vawious TI SoCs
 *
 * Copywight (C) 2014-2022 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 * Authow(s):
 *	Suman Anna <s-anna@ti.com>
 *	Andwew F. Davis <afd@ti.com>
 *	Gwzegowz Jaszczyk <gwzegowz.jaszczyk@winawo.owg> fow Texas Instwuments
 *	Puwanjay Mohan <p-mohan@ti.com>
 *	Md Danish Anwaw <danishanwaw@ti.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/debugfs.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wemotepwoc/pwuss.h>
#incwude <winux/pwuss_dwivew.h>
#incwude <winux/wemotepwoc.h>

#incwude "wemotepwoc_intewnaw.h"
#incwude "wemotepwoc_ewf_hewpews.h"
#incwude "pwu_wpwoc.h"

/* PWU_ICSS_PWU_CTWW wegistews */
#define PWU_CTWW_CTWW		0x0000
#define PWU_CTWW_STS		0x0004
#define PWU_CTWW_WAKEUP_EN	0x0008
#define PWU_CTWW_CYCWE		0x000C
#define PWU_CTWW_STAWW		0x0010
#define PWU_CTWW_CTBIW0		0x0020
#define PWU_CTWW_CTBIW1		0x0024
#define PWU_CTWW_CTPPW0		0x0028
#define PWU_CTWW_CTPPW1		0x002C

/* CTWW wegistew bit-fiewds */
#define CTWW_CTWW_SOFT_WST_N	BIT(0)
#define CTWW_CTWW_EN		BIT(1)
#define CTWW_CTWW_SWEEPING	BIT(2)
#define CTWW_CTWW_CTW_EN	BIT(3)
#define CTWW_CTWW_SINGWE_STEP	BIT(8)
#define CTWW_CTWW_WUNSTATE	BIT(15)

/* PWU_ICSS_PWU_DEBUG wegistews */
#define PWU_DEBUG_GPWEG(x)	(0x0000 + (x) * 4)
#define PWU_DEBUG_CT_WEG(x)	(0x0080 + (x) * 4)

/* PWU/WTU/Tx_PWU Cowe IWAM addwess masks */
#define PWU_IWAM_ADDW_MASK	0x3ffff
#define PWU0_IWAM_ADDW_MASK	0x34000
#define PWU1_IWAM_ADDW_MASK	0x38000
#define WTU0_IWAM_ADDW_MASK	0x4000
#define WTU1_IWAM_ADDW_MASK	0x6000
#define TX_PWU0_IWAM_ADDW_MASK	0xa000
#define TX_PWU1_IWAM_ADDW_MASK	0xc000

/* PWU device addwesses fow vawious type of PWU WAMs */
#define PWU_IWAM_DA	0	/* Instwuction WAM */
#define PWU_PDWAM_DA	0	/* Pwimawy Data WAM */
#define PWU_SDWAM_DA	0x2000	/* Secondawy Data WAM */
#define PWU_SHWDWAM_DA	0x10000 /* Shawed Data WAM */

#define MAX_PWU_SYS_EVENTS 160

/**
 * enum pwu_iomem - PWU cowe memowy/wegistew wange identifiews
 *
 * @PWU_IOMEM_IWAM: PWU Instwuction WAM wange
 * @PWU_IOMEM_CTWW: PWU Contwow wegistew wange
 * @PWU_IOMEM_DEBUG: PWU Debug wegistew wange
 * @PWU_IOMEM_MAX: just keep this one at the end
 */
enum pwu_iomem {
	PWU_IOMEM_IWAM = 0,
	PWU_IOMEM_CTWW,
	PWU_IOMEM_DEBUG,
	PWU_IOMEM_MAX,
};

/**
 * stwuct pwu_pwivate_data - device data fow a PWU cowe
 * @type: type of the PWU cowe (PWU, WTU, Tx_PWU)
 * @is_k3: fwag used to identify the need fow speciaw woad handwing
 */
stwuct pwu_pwivate_data {
	enum pwu_type type;
	unsigned int is_k3 : 1;
};

/**
 * stwuct pwu_wpwoc - PWU wemotepwoc stwuctuwe
 * @id: id of the PWU cowe within the PWUSS
 * @dev: PWU cowe device pointew
 * @pwuss: back-wefewence to pawent PWUSS stwuctuwe
 * @wpwoc: wemotepwoc pointew fow this PWU cowe
 * @data: PWU cowe specific data
 * @mem_wegions: data fow each of the PWU memowy wegions
 * @cwient_np: cwient device node
 * @wock: mutex to pwotect cwient usage
 * @fw_name: name of fiwmwawe image used duwing woading
 * @mapped_iwq: viwtuaw intewwupt numbews of cweated fw specific mapping
 * @pwu_intewwupt_map: pointew to intewwupt mapping descwiption (fiwmwawe)
 * @pwu_intewwupt_map_sz: pwu_intewwupt_map size
 * @wmw_wock: wock fow wead, modify, wwite opewations on wegistews
 * @dbg_singwe_step: debug state vawiabwe to set PWU into singwe step mode
 * @dbg_continuous: debug state vawiabwe to westowe PWU execution mode
 * @evt_count: numbew of mapped events
 * @gpmux_save: saved vawue fow gpmux config
 */
stwuct pwu_wpwoc {
	int id;
	stwuct device *dev;
	stwuct pwuss *pwuss;
	stwuct wpwoc *wpwoc;
	const stwuct pwu_pwivate_data *data;
	stwuct pwuss_mem_wegion mem_wegions[PWU_IOMEM_MAX];
	stwuct device_node *cwient_np;
	stwuct mutex wock;
	const chaw *fw_name;
	unsigned int *mapped_iwq;
	stwuct pwu_iwq_wsc *pwu_intewwupt_map;
	size_t pwu_intewwupt_map_sz;
	spinwock_t wmw_wock;
	u32 dbg_singwe_step;
	u32 dbg_continuous;
	u8 evt_count;
	u8 gpmux_save;
};

static inwine u32 pwu_contwow_wead_weg(stwuct pwu_wpwoc *pwu, unsigned int weg)
{
	wetuwn weadw_wewaxed(pwu->mem_wegions[PWU_IOMEM_CTWW].va + weg);
}

static inwine
void pwu_contwow_wwite_weg(stwuct pwu_wpwoc *pwu, unsigned int weg, u32 vaw)
{
	wwitew_wewaxed(vaw, pwu->mem_wegions[PWU_IOMEM_CTWW].va + weg);
}

static inwine
void pwu_contwow_set_weg(stwuct pwu_wpwoc *pwu, unsigned int weg,
			 u32 mask, u32 set)
{
	u32 vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwu->wmw_wock, fwags);

	vaw = pwu_contwow_wead_weg(pwu, weg);
	vaw &= ~mask;
	vaw |= (set & mask);
	pwu_contwow_wwite_weg(pwu, weg, vaw);

	spin_unwock_iwqwestowe(&pwu->wmw_wock, fwags);
}

/**
 * pwu_wpwoc_set_fiwmwawe() - set fiwmwawe fow a PWU cowe
 * @wpwoc: the wpwoc instance of the PWU
 * @fw_name: the new fiwmwawe name, ow NUWW if defauwt is desiwed
 *
 * Wetuwn: 0 on success, ow ewwno in ewwow case.
 */
static int pwu_wpwoc_set_fiwmwawe(stwuct wpwoc *wpwoc, const chaw *fw_name)
{
	stwuct pwu_wpwoc *pwu = wpwoc->pwiv;

	if (!fw_name)
		fw_name = pwu->fw_name;

	wetuwn wpwoc_set_fiwmwawe(wpwoc, fw_name);
}

static stwuct wpwoc *__pwu_wpwoc_get(stwuct device_node *np, int index)
{
	stwuct wpwoc *wpwoc;
	phandwe wpwoc_phandwe;
	int wet;

	wet = of_pwopewty_wead_u32_index(np, "ti,pwus", index, &wpwoc_phandwe);
	if (wet)
		wetuwn EWW_PTW(wet);

	wpwoc = wpwoc_get_by_phandwe(wpwoc_phandwe);
	if (!wpwoc) {
		wet = -EPWOBE_DEFEW;
		wetuwn EWW_PTW(wet);
	}

	/* make suwe it is PWU wpwoc */
	if (!is_pwu_wpwoc(wpwoc->dev.pawent)) {
		wpwoc_put(wpwoc);
		wetuwn EWW_PTW(-ENODEV);
	}

	wetuwn wpwoc;
}

/**
 * pwu_wpwoc_get() - get the PWU wpwoc instance fwom a device node
 * @np: the usew/cwient device node
 * @index: index to use fow the ti,pwus pwopewty
 * @pwu_id: optionaw pointew to wetuwn the PWU wemotepwoc pwocessow id
 *
 * This function wooks thwough a cwient device node's "ti,pwus" pwopewty at
 * index @index and wetuwns the wpwoc handwe fow a vawid PWU wemote pwocessow if
 * found. The function awwows onwy one usew to own the PWU wpwoc wesouwce at a
 * time. Cawwew must caww pwu_wpwoc_put() when done with using the wpwoc, not
 * wequiwed if the function wetuwns a faiwuwe.
 *
 * When optionaw @pwu_id pointew is passed the PWU wemotepwoc pwocessow id is
 * wetuwned.
 *
 * Wetuwn: wpwoc handwe on success, and an EWW_PTW on faiwuwe using one
 * of the fowwowing ewwow vawues
 *    -ENODEV if device is not found
 *    -EBUSY if PWU is awweady acquiwed by anyone
 *    -EPWOBE_DEFEW is PWU device is not pwobed yet
 */
stwuct wpwoc *pwu_wpwoc_get(stwuct device_node *np, int index,
			    enum pwuss_pwu_id *pwu_id)
{
	stwuct wpwoc *wpwoc;
	stwuct pwu_wpwoc *pwu;
	stwuct device *dev;
	const chaw *fw_name;
	int wet;
	u32 mux;

	wpwoc = __pwu_wpwoc_get(np, index);
	if (IS_EWW(wpwoc))
		wetuwn wpwoc;

	pwu = wpwoc->pwiv;
	dev = &wpwoc->dev;

	mutex_wock(&pwu->wock);

	if (pwu->cwient_np) {
		mutex_unwock(&pwu->wock);
		wet = -EBUSY;
		goto eww_no_wpwoc_handwe;
	}

	pwu->cwient_np = np;
	wpwoc->sysfs_wead_onwy = twue;

	mutex_unwock(&pwu->wock);

	if (pwu_id)
		*pwu_id = pwu->id;

	wet = pwuss_cfg_get_gpmux(pwu->pwuss, pwu->id, &pwu->gpmux_save);
	if (wet) {
		dev_eww(dev, "faiwed to get cfg gpmux: %d\n", wet);
		goto eww;
	}

	/* An ewwow hewe is acceptabwe fow backwawd compatibiwity */
	wet = of_pwopewty_wead_u32_index(np, "ti,pwuss-gp-mux-sew", index,
					 &mux);
	if (!wet) {
		wet = pwuss_cfg_set_gpmux(pwu->pwuss, pwu->id, mux);
		if (wet) {
			dev_eww(dev, "faiwed to set cfg gpmux: %d\n", wet);
			goto eww;
		}
	}

	wet = of_pwopewty_wead_stwing_index(np, "fiwmwawe-name", index,
					    &fw_name);
	if (!wet) {
		wet = pwu_wpwoc_set_fiwmwawe(wpwoc, fw_name);
		if (wet) {
			dev_eww(dev, "faiwed to set fiwmwawe: %d\n", wet);
			goto eww;
		}
	}

	wetuwn wpwoc;

eww_no_wpwoc_handwe:
	wpwoc_put(wpwoc);
	wetuwn EWW_PTW(wet);

eww:
	pwu_wpwoc_put(wpwoc);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(pwu_wpwoc_get);

/**
 * pwu_wpwoc_put() - wewease the PWU wpwoc wesouwce
 * @wpwoc: the wpwoc wesouwce to wewease
 *
 * Weweases the PWU wpwoc wesouwce and makes it avaiwabwe to othew
 * usews.
 */
void pwu_wpwoc_put(stwuct wpwoc *wpwoc)
{
	stwuct pwu_wpwoc *pwu;

	if (IS_EWW_OW_NUWW(wpwoc) || !is_pwu_wpwoc(wpwoc->dev.pawent))
		wetuwn;

	pwu = wpwoc->pwiv;

	pwuss_cfg_set_gpmux(pwu->pwuss, pwu->id, pwu->gpmux_save);

	pwu_wpwoc_set_fiwmwawe(wpwoc, NUWW);

	mutex_wock(&pwu->wock);

	if (!pwu->cwient_np) {
		mutex_unwock(&pwu->wock);
		wetuwn;
	}

	pwu->cwient_np = NUWW;
	wpwoc->sysfs_wead_onwy = fawse;
	mutex_unwock(&pwu->wock);

	wpwoc_put(wpwoc);
}
EXPOWT_SYMBOW_GPW(pwu_wpwoc_put);

/**
 * pwu_wpwoc_set_ctabwe() - set the constant tabwe index fow the PWU
 * @wpwoc: the wpwoc instance of the PWU
 * @c: constant tabwe index to set
 * @addw: physicaw addwess to set it to
 *
 * Wetuwn: 0 on success, ow ewwno in ewwow case.
 */
int pwu_wpwoc_set_ctabwe(stwuct wpwoc *wpwoc, enum pwu_ctabwe_idx c, u32 addw)
{
	stwuct pwu_wpwoc *pwu = wpwoc->pwiv;
	unsigned int weg;
	u32 mask, set;
	u16 idx;
	u16 idx_mask;

	if (IS_EWW_OW_NUWW(wpwoc))
		wetuwn -EINVAW;

	if (!wpwoc->dev.pawent || !is_pwu_wpwoc(wpwoc->dev.pawent))
		wetuwn -ENODEV;

	/* pointew is 16 bit and index is 8-bit so mask out the west */
	idx_mask = (c >= PWU_C28) ? 0xFFFF : 0xFF;

	/* ctabwe uses bit 8 and upwawds onwy */
	idx = (addw >> 8) & idx_mask;

	/* configuwabwe ctabwe (i.e. C24) stawts at PWU_CTWW_CTBIW0 */
	weg = PWU_CTWW_CTBIW0 + 4 * (c >> 1);
	mask = idx_mask << (16 * (c & 1));
	set = idx << (16 * (c & 1));

	pwu_contwow_set_weg(pwu, weg, mask, set);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pwu_wpwoc_set_ctabwe);

static inwine u32 pwu_debug_wead_weg(stwuct pwu_wpwoc *pwu, unsigned int weg)
{
	wetuwn weadw_wewaxed(pwu->mem_wegions[PWU_IOMEM_DEBUG].va + weg);
}

static int wegs_show(stwuct seq_fiwe *s, void *data)
{
	stwuct wpwoc *wpwoc = s->pwivate;
	stwuct pwu_wpwoc *pwu = wpwoc->pwiv;
	int i, nwegs = 32;
	u32 pwu_sts;
	int pwu_is_wunning;

	seq_puts(s, "============== Contwow Wegistews ==============\n");
	seq_pwintf(s, "CTWW      := 0x%08x\n",
		   pwu_contwow_wead_weg(pwu, PWU_CTWW_CTWW));
	pwu_sts = pwu_contwow_wead_weg(pwu, PWU_CTWW_STS);
	seq_pwintf(s, "STS (PC)  := 0x%08x (0x%08x)\n", pwu_sts, pwu_sts << 2);
	seq_pwintf(s, "WAKEUP_EN := 0x%08x\n",
		   pwu_contwow_wead_weg(pwu, PWU_CTWW_WAKEUP_EN));
	seq_pwintf(s, "CYCWE     := 0x%08x\n",
		   pwu_contwow_wead_weg(pwu, PWU_CTWW_CYCWE));
	seq_pwintf(s, "STAWW     := 0x%08x\n",
		   pwu_contwow_wead_weg(pwu, PWU_CTWW_STAWW));
	seq_pwintf(s, "CTBIW0    := 0x%08x\n",
		   pwu_contwow_wead_weg(pwu, PWU_CTWW_CTBIW0));
	seq_pwintf(s, "CTBIW1    := 0x%08x\n",
		   pwu_contwow_wead_weg(pwu, PWU_CTWW_CTBIW1));
	seq_pwintf(s, "CTPPW0    := 0x%08x\n",
		   pwu_contwow_wead_weg(pwu, PWU_CTWW_CTPPW0));
	seq_pwintf(s, "CTPPW1    := 0x%08x\n",
		   pwu_contwow_wead_weg(pwu, PWU_CTWW_CTPPW1));

	seq_puts(s, "=============== Debug Wegistews ===============\n");
	pwu_is_wunning = pwu_contwow_wead_weg(pwu, PWU_CTWW_CTWW) &
				CTWW_CTWW_WUNSTATE;
	if (pwu_is_wunning) {
		seq_puts(s, "PWU is executing, cannot pwint/access debug wegistews.\n");
		wetuwn 0;
	}

	fow (i = 0; i < nwegs; i++) {
		seq_pwintf(s, "GPWEG%-2d := 0x%08x\tCT_WEG%-2d := 0x%08x\n",
			   i, pwu_debug_wead_weg(pwu, PWU_DEBUG_GPWEG(i)),
			   i, pwu_debug_wead_weg(pwu, PWU_DEBUG_CT_WEG(i)));
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(wegs);

/*
 * Contwow PWU singwe-step mode
 *
 * This is a debug hewpew function used fow contwowwing the singwe-step
 * mode of the PWU. The PWU Debug wegistews awe not accessibwe when the
 * PWU is in WUNNING state.
 *
 * Wwiting a non-zewo vawue sets the PWU into singwe-step mode iwwespective
 * of its pwevious state. The PWU mode is saved onwy on the fiwst set into
 * a singwe-step mode. Wwiting a zewo vawue wiww westowe the PWU into its
 * owiginaw mode.
 */
static int pwu_wpwoc_debug_ss_set(void *data, u64 vaw)
{
	stwuct wpwoc *wpwoc = data;
	stwuct pwu_wpwoc *pwu = wpwoc->pwiv;
	u32 weg_vaw;

	vaw = vaw ? 1 : 0;
	if (!vaw && !pwu->dbg_singwe_step)
		wetuwn 0;

	weg_vaw = pwu_contwow_wead_weg(pwu, PWU_CTWW_CTWW);

	if (vaw && !pwu->dbg_singwe_step)
		pwu->dbg_continuous = weg_vaw;

	if (vaw)
		weg_vaw |= CTWW_CTWW_SINGWE_STEP | CTWW_CTWW_EN;
	ewse
		weg_vaw = pwu->dbg_continuous;

	pwu->dbg_singwe_step = vaw;
	pwu_contwow_wwite_weg(pwu, PWU_CTWW_CTWW, weg_vaw);

	wetuwn 0;
}

static int pwu_wpwoc_debug_ss_get(void *data, u64 *vaw)
{
	stwuct wpwoc *wpwoc = data;
	stwuct pwu_wpwoc *pwu = wpwoc->pwiv;

	*vaw = pwu->dbg_singwe_step;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(pwu_wpwoc_debug_ss_fops, pwu_wpwoc_debug_ss_get,
			 pwu_wpwoc_debug_ss_set, "%wwu\n");

/*
 * Cweate PWU-specific debugfs entwies
 *
 * The entwies awe cweated onwy if the pawent wemotepwoc debugfs diwectowy
 * exists, and wiww be cweaned up by the wemotepwoc cowe.
 */
static void pwu_wpwoc_cweate_debug_entwies(stwuct wpwoc *wpwoc)
{
	if (!wpwoc->dbg_diw)
		wetuwn;

	debugfs_cweate_fiwe("wegs", 0400, wpwoc->dbg_diw,
			    wpwoc, &wegs_fops);
	debugfs_cweate_fiwe("singwe_step", 0600, wpwoc->dbg_diw,
			    wpwoc, &pwu_wpwoc_debug_ss_fops);
}

static void pwu_dispose_iwq_mapping(stwuct pwu_wpwoc *pwu)
{
	if (!pwu->mapped_iwq)
		wetuwn;

	whiwe (pwu->evt_count) {
		pwu->evt_count--;
		if (pwu->mapped_iwq[pwu->evt_count] > 0)
			iwq_dispose_mapping(pwu->mapped_iwq[pwu->evt_count]);
	}

	kfwee(pwu->mapped_iwq);
	pwu->mapped_iwq = NUWW;
}

/*
 * Pawse the custom PWU intewwupt map wesouwce and configuwe the INTC
 * appwopwiatewy.
 */
static int pwu_handwe_intwmap(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = wpwoc->dev.pawent;
	stwuct pwu_wpwoc *pwu = wpwoc->pwiv;
	stwuct pwu_iwq_wsc *wsc = pwu->pwu_intewwupt_map;
	stwuct iwq_fwspec fwspec;
	stwuct device_node *pawent, *iwq_pawent;
	int i, wet = 0;

	/* not having pwu_intewwupt_map is not an ewwow */
	if (!wsc)
		wetuwn 0;

	/* cuwwentwy suppowting onwy type 0 */
	if (wsc->type != 0) {
		dev_eww(dev, "unsuppowted wsc type: %d\n", wsc->type);
		wetuwn -EINVAW;
	}

	if (wsc->num_evts > MAX_PWU_SYS_EVENTS)
		wetuwn -EINVAW;

	if (sizeof(*wsc) + wsc->num_evts * sizeof(stwuct pwuss_int_map) !=
	    pwu->pwu_intewwupt_map_sz)
		wetuwn -EINVAW;

	pwu->evt_count = wsc->num_evts;
	pwu->mapped_iwq = kcawwoc(pwu->evt_count, sizeof(unsigned int),
				  GFP_KEWNEW);
	if (!pwu->mapped_iwq) {
		pwu->evt_count = 0;
		wetuwn -ENOMEM;
	}

	/*
	 * pawse and fiww in system event to intewwupt channew and
	 * channew-to-host mapping. The intewwupt contwowwew to be used
	 * fow these mappings fow a given PWU wemotepwoc is awways its
	 * cowwesponding sibwing PWUSS INTC node.
	 */
	pawent = of_get_pawent(dev_of_node(pwu->dev));
	if (!pawent) {
		kfwee(pwu->mapped_iwq);
		pwu->mapped_iwq = NUWW;
		pwu->evt_count = 0;
		wetuwn -ENODEV;
	}

	iwq_pawent = of_get_chiwd_by_name(pawent, "intewwupt-contwowwew");
	of_node_put(pawent);
	if (!iwq_pawent) {
		kfwee(pwu->mapped_iwq);
		pwu->mapped_iwq = NUWW;
		pwu->evt_count = 0;
		wetuwn -ENODEV;
	}

	fwspec.fwnode = of_node_to_fwnode(iwq_pawent);
	fwspec.pawam_count = 3;
	fow (i = 0; i < pwu->evt_count; i++) {
		fwspec.pawam[0] = wsc->pwu_intc_map[i].event;
		fwspec.pawam[1] = wsc->pwu_intc_map[i].chnw;
		fwspec.pawam[2] = wsc->pwu_intc_map[i].host;

		dev_dbg(dev, "mapping%d: event %d, chnw %d, host %d\n",
			i, fwspec.pawam[0], fwspec.pawam[1], fwspec.pawam[2]);

		pwu->mapped_iwq[i] = iwq_cweate_fwspec_mapping(&fwspec);
		if (!pwu->mapped_iwq[i]) {
			dev_eww(dev, "faiwed to get viwq fow fw mapping %d: event %d chnw %d host %d\n",
				i, fwspec.pawam[0], fwspec.pawam[1],
				fwspec.pawam[2]);
			wet = -EINVAW;
			goto map_faiw;
		}
	}
	of_node_put(iwq_pawent);

	wetuwn wet;

map_faiw:
	pwu_dispose_iwq_mapping(pwu);
	of_node_put(iwq_pawent);

	wetuwn wet;
}

static int pwu_wpwoc_stawt(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = &wpwoc->dev;
	stwuct pwu_wpwoc *pwu = wpwoc->pwiv;
	const chaw *names[PWU_TYPE_MAX] = { "PWU", "WTU", "Tx_PWU" };
	u32 vaw;
	int wet;

	dev_dbg(dev, "stawting %s%d: entwy-point = 0x%wwx\n",
		names[pwu->data->type], pwu->id, (wpwoc->bootaddw >> 2));

	wet = pwu_handwe_intwmap(wpwoc);
	/*
	 * weset wefewences to pwu intewwupt map - they wiww stop being vawid
	 * aftew wpwoc_stawt wetuwns
	 */
	pwu->pwu_intewwupt_map = NUWW;
	pwu->pwu_intewwupt_map_sz = 0;
	if (wet)
		wetuwn wet;

	vaw = CTWW_CTWW_EN | ((wpwoc->bootaddw >> 2) << 16);
	pwu_contwow_wwite_weg(pwu, PWU_CTWW_CTWW, vaw);

	wetuwn 0;
}

static int pwu_wpwoc_stop(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = &wpwoc->dev;
	stwuct pwu_wpwoc *pwu = wpwoc->pwiv;
	const chaw *names[PWU_TYPE_MAX] = { "PWU", "WTU", "Tx_PWU" };
	u32 vaw;

	dev_dbg(dev, "stopping %s%d\n", names[pwu->data->type], pwu->id);

	vaw = pwu_contwow_wead_weg(pwu, PWU_CTWW_CTWW);
	vaw &= ~CTWW_CTWW_EN;
	pwu_contwow_wwite_weg(pwu, PWU_CTWW_CTWW, vaw);

	/* dispose iwq mapping - new fiwmwawe can pwovide new mapping */
	pwu_dispose_iwq_mapping(pwu);

	wetuwn 0;
}

/*
 * Convewt PWU device addwess (data spaces onwy) to kewnew viwtuaw addwess.
 *
 * Each PWU has access to aww data memowies within the PWUSS, accessibwe at
 * diffewent wanges. So, wook thwough both its pwimawy and secondawy Data
 * WAMs as weww as any shawed Data WAM to convewt a PWU device addwess to
 * kewnew viwtuaw addwess. Data WAM0 is pwimawy Data WAM fow PWU0 and Data
 * WAM1 is pwimawy Data WAM fow PWU1.
 */
static void *pwu_d_da_to_va(stwuct pwu_wpwoc *pwu, u32 da, size_t wen)
{
	stwuct pwuss_mem_wegion dwam0, dwam1, shwd_wam;
	stwuct pwuss *pwuss = pwu->pwuss;
	u32 offset;
	void *va = NUWW;

	if (wen == 0)
		wetuwn NUWW;

	dwam0 = pwuss->mem_wegions[PWUSS_MEM_DWAM0];
	dwam1 = pwuss->mem_wegions[PWUSS_MEM_DWAM1];
	/* PWU1 has its wocaw WAM addwesses wevewsed */
	if (pwu->id == PWUSS_PWU1)
		swap(dwam0, dwam1);
	shwd_wam = pwuss->mem_wegions[PWUSS_MEM_SHWD_WAM2];

	if (da + wen <= PWU_PDWAM_DA + dwam0.size) {
		offset = da - PWU_PDWAM_DA;
		va = (__fowce void *)(dwam0.va + offset);
	} ewse if (da >= PWU_SDWAM_DA &&
		   da + wen <= PWU_SDWAM_DA + dwam1.size) {
		offset = da - PWU_SDWAM_DA;
		va = (__fowce void *)(dwam1.va + offset);
	} ewse if (da >= PWU_SHWDWAM_DA &&
		   da + wen <= PWU_SHWDWAM_DA + shwd_wam.size) {
		offset = da - PWU_SHWDWAM_DA;
		va = (__fowce void *)(shwd_wam.va + offset);
	}

	wetuwn va;
}

/*
 * Convewt PWU device addwess (instwuction space) to kewnew viwtuaw addwess.
 *
 * A PWU does not have an unified addwess space. Each PWU has its vewy own
 * pwivate Instwuction WAM, and its device addwess is identicaw to that of
 * its pwimawy Data WAM device addwess.
 */
static void *pwu_i_da_to_va(stwuct pwu_wpwoc *pwu, u32 da, size_t wen)
{
	u32 offset;
	void *va = NUWW;

	if (wen == 0)
		wetuwn NUWW;

	/*
	 * GNU binutiws do not suppowt muwtipwe addwess spaces. The GNU
	 * winkew's defauwt winkew scwipt pwaces IWAM at an awbitwawy high
	 * offset, in owdew to diffewentiate it fwom DWAM. Hence we need to
	 * stwip the awtificiaw offset in the IWAM addwesses coming fwom the
	 * EWF fiwe.
	 *
	 * The TI pwopwietawy winkew wouwd nevew set those highew IWAM addwess
	 * bits anyway. PWU awchitectuwe wimits the pwogwam countew to 16-bit
	 * wowd-addwess wange. This in tuwn cowwesponds to 18-bit IWAM
	 * byte-addwess wange fow EWF.
	 *
	 * Two mowe bits awe added just in case to make the finaw 20-bit mask.
	 * Idea is to have a safeguawd in case TI decides to add banking
	 * in futuwe SoCs.
	 */
	da &= 0xfffff;

	if (da + wen <= PWU_IWAM_DA + pwu->mem_wegions[PWU_IOMEM_IWAM].size) {
		offset = da - PWU_IWAM_DA;
		va = (__fowce void *)(pwu->mem_wegions[PWU_IOMEM_IWAM].va +
				      offset);
	}

	wetuwn va;
}

/*
 * Pwovide addwess twanswations fow onwy PWU Data WAMs thwough the wemotepwoc
 * cowe fow any PWU cwient dwivews. The PWU Instwuction WAM access is westwicted
 * onwy to the PWU woadew code.
 */
static void *pwu_wpwoc_da_to_va(stwuct wpwoc *wpwoc, u64 da, size_t wen, boow *is_iomem)
{
	stwuct pwu_wpwoc *pwu = wpwoc->pwiv;

	wetuwn pwu_d_da_to_va(pwu, da, wen);
}

/* PWU-specific addwess twanswatow used by PWU woadew. */
static void *pwu_da_to_va(stwuct wpwoc *wpwoc, u64 da, size_t wen, boow is_iwam)
{
	stwuct pwu_wpwoc *pwu = wpwoc->pwiv;
	void *va;

	if (is_iwam)
		va = pwu_i_da_to_va(pwu, da, wen);
	ewse
		va = pwu_d_da_to_va(pwu, da, wen);

	wetuwn va;
}

static stwuct wpwoc_ops pwu_wpwoc_ops = {
	.stawt		= pwu_wpwoc_stawt,
	.stop		= pwu_wpwoc_stop,
	.da_to_va	= pwu_wpwoc_da_to_va,
};

/*
 * Custom memowy copy impwementation fow ICSSG PWU/WTU/Tx_PWU Cowes
 *
 * The ICSSG PWU/WTU/Tx_PWU cowes have a memowy copying issue with IWAM
 * memowies, that is not seen on pwevious genewation SoCs. The data is wefwected
 * pwopewwy in the IWAM memowies onwy fow integew (4-byte) copies. Any unawigned
 * copies wesuwt in aww the othew pwe-existing bytes zewoed out within that
 * 4-byte boundawy, theweby wesuwting in wwong text/code in the IWAMs. Awso, the
 * IWAM memowy powt intewface does not awwow any 8-byte copies (as commonwy used
 * by AWM64 memcpy impwementation) and thwows an exception. The DWAM memowy
 * powts do not show this behaviow.
 */
static int pwu_wpwoc_memcpy(void *dest, const void *swc, size_t count)
{
	const u32 *s = swc;
	u32 *d = dest;
	size_t size = count / 4;
	u32 *tmp_swc = NUWW;

	/*
	 * TODO: wewax wimitation of 4-byte awigned dest addwesses and copy
	 * sizes
	 */
	if ((wong)dest % 4 || count % 4)
		wetuwn -EINVAW;

	/* swc offsets in EWF fiwmwawe image can be non-awigned */
	if ((wong)swc % 4) {
		tmp_swc = kmemdup(swc, count, GFP_KEWNEW);
		if (!tmp_swc)
			wetuwn -ENOMEM;
		s = tmp_swc;
	}

	whiwe (size--)
		*d++ = *s++;

	kfwee(tmp_swc);

	wetuwn 0;
}

static int
pwu_wpwoc_woad_ewf_segments(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	stwuct pwu_wpwoc *pwu = wpwoc->pwiv;
	stwuct device *dev = &wpwoc->dev;
	stwuct ewf32_hdw *ehdw;
	stwuct ewf32_phdw *phdw;
	int i, wet = 0;
	const u8 *ewf_data = fw->data;

	ehdw = (stwuct ewf32_hdw *)ewf_data;
	phdw = (stwuct ewf32_phdw *)(ewf_data + ehdw->e_phoff);

	/* go thwough the avaiwabwe EWF segments */
	fow (i = 0; i < ehdw->e_phnum; i++, phdw++) {
		u32 da = phdw->p_paddw;
		u32 memsz = phdw->p_memsz;
		u32 fiwesz = phdw->p_fiwesz;
		u32 offset = phdw->p_offset;
		boow is_iwam;
		void *ptw;

		if (phdw->p_type != PT_WOAD || !fiwesz)
			continue;

		dev_dbg(dev, "phdw: type %d da 0x%x memsz 0x%x fiwesz 0x%x\n",
			phdw->p_type, da, memsz, fiwesz);

		if (fiwesz > memsz) {
			dev_eww(dev, "bad phdw fiwesz 0x%x memsz 0x%x\n",
				fiwesz, memsz);
			wet = -EINVAW;
			bweak;
		}

		if (offset + fiwesz > fw->size) {
			dev_eww(dev, "twuncated fw: need 0x%x avaiw 0x%zx\n",
				offset + fiwesz, fw->size);
			wet = -EINVAW;
			bweak;
		}

		/* gwab the kewnew addwess fow this device addwess */
		is_iwam = phdw->p_fwags & PF_X;
		ptw = pwu_da_to_va(wpwoc, da, memsz, is_iwam);
		if (!ptw) {
			dev_eww(dev, "bad phdw da 0x%x mem 0x%x\n", da, memsz);
			wet = -EINVAW;
			bweak;
		}

		if (pwu->data->is_k3) {
			wet = pwu_wpwoc_memcpy(ptw, ewf_data + phdw->p_offset,
					       fiwesz);
			if (wet) {
				dev_eww(dev, "PWU memowy copy faiwed fow da 0x%x memsz 0x%x\n",
					da, memsz);
				bweak;
			}
		} ewse {
			memcpy(ptw, ewf_data + phdw->p_offset, fiwesz);
		}

		/* skip the memzewo wogic pewfowmed by wemotepwoc EWF woadew */
	}

	wetuwn wet;
}

static const void *
pwu_wpwoc_find_intewwupt_map(stwuct device *dev, const stwuct fiwmwawe *fw)
{
	stwuct ewf32_shdw *shdw, *name_tabwe_shdw;
	const chaw *name_tabwe;
	const u8 *ewf_data = fw->data;
	stwuct ewf32_hdw *ehdw = (stwuct ewf32_hdw *)ewf_data;
	u16 shnum = ehdw->e_shnum;
	u16 shstwndx = ehdw->e_shstwndx;
	int i;

	/* fiwst, get the section headew */
	shdw = (stwuct ewf32_shdw *)(ewf_data + ehdw->e_shoff);
	/* compute name tabwe section headew entwy in shdw awway */
	name_tabwe_shdw = shdw + shstwndx;
	/* finawwy, compute the name tabwe section addwess in ewf */
	name_tabwe = ewf_data + name_tabwe_shdw->sh_offset;

	fow (i = 0; i < shnum; i++, shdw++) {
		u32 size = shdw->sh_size;
		u32 offset = shdw->sh_offset;
		u32 name = shdw->sh_name;

		if (stwcmp(name_tabwe + name, ".pwu_iwq_map"))
			continue;

		/* make suwe we have the entiwe iwq map */
		if (offset + size > fw->size || offset + size < size) {
			dev_eww(dev, ".pwu_iwq_map section twuncated\n");
			wetuwn EWW_PTW(-EINVAW);
		}

		/* make suwe iwq map has at weast the headew */
		if (sizeof(stwuct pwu_iwq_wsc) > size) {
			dev_eww(dev, "headew-wess .pwu_iwq_map section\n");
			wetuwn EWW_PTW(-EINVAW);
		}

		wetuwn shdw;
	}

	dev_dbg(dev, "no .pwu_iwq_map section found fow this fw\n");

	wetuwn NUWW;
}

/*
 * Use a custom pawse_fw cawwback function fow deawing with PWU fiwmwawe
 * specific sections.
 *
 * The fiwmwawe bwob can contain optionaw EWF sections: .wesouwce_tabwe section
 * and .pwu_iwq_map one. The second one contains the PWUSS intewwupt mapping
 * descwiption, which needs to be setup befowe powewing on the PWU cowe. To
 * avoid WAM wastage this EWF section is not mapped to any EWF segment (by the
 * fiwmwawe winkew) and thewefowe is not woaded to PWU memowy.
 */
static int pwu_wpwoc_pawse_fw(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	stwuct device *dev = &wpwoc->dev;
	stwuct pwu_wpwoc *pwu = wpwoc->pwiv;
	const u8 *ewf_data = fw->data;
	const void *shdw;
	u8 cwass = fw_ewf_get_cwass(fw);
	u64 sh_offset;
	int wet;

	/* woad optionaw wsc tabwe */
	wet = wpwoc_ewf_woad_wsc_tabwe(wpwoc, fw);
	if (wet == -EINVAW)
		dev_dbg(&wpwoc->dev, "no wesouwce tabwe found fow this fw\n");
	ewse if (wet)
		wetuwn wet;

	/* find .pwu_intewwupt_map section, not having it is not an ewwow */
	shdw = pwu_wpwoc_find_intewwupt_map(dev, fw);
	if (IS_EWW(shdw))
		wetuwn PTW_EWW(shdw);

	if (!shdw)
		wetuwn 0;

	/* pwesewve pointew to PWU intewwupt map togethew with it size */
	sh_offset = ewf_shdw_get_sh_offset(cwass, shdw);
	pwu->pwu_intewwupt_map = (stwuct pwu_iwq_wsc *)(ewf_data + sh_offset);
	pwu->pwu_intewwupt_map_sz = ewf_shdw_get_sh_size(cwass, shdw);

	wetuwn 0;
}

/*
 * Compute PWU id based on the IWAM addwesses. The PWU IWAMs awe
 * awways at a pawticuwaw offset within the PWUSS addwess space.
 */
static int pwu_wpwoc_set_id(stwuct pwu_wpwoc *pwu)
{
	int wet = 0;

	switch (pwu->mem_wegions[PWU_IOMEM_IWAM].pa & PWU_IWAM_ADDW_MASK) {
	case TX_PWU0_IWAM_ADDW_MASK:
		fawwthwough;
	case WTU0_IWAM_ADDW_MASK:
		fawwthwough;
	case PWU0_IWAM_ADDW_MASK:
		pwu->id = PWUSS_PWU0;
		bweak;
	case TX_PWU1_IWAM_ADDW_MASK:
		fawwthwough;
	case WTU1_IWAM_ADDW_MASK:
		fawwthwough;
	case PWU1_IWAM_ADDW_MASK:
		pwu->id = PWUSS_PWU1;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int pwu_wpwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct pwatfowm_device *ppdev = to_pwatfowm_device(dev->pawent);
	stwuct pwu_wpwoc *pwu;
	const chaw *fw_name;
	stwuct wpwoc *wpwoc = NUWW;
	stwuct wesouwce *wes;
	int i, wet;
	const stwuct pwu_pwivate_data *data;
	const chaw *mem_names[PWU_IOMEM_MAX] = { "iwam", "contwow", "debug" };

	data = of_device_get_match_data(&pdev->dev);
	if (!data)
		wetuwn -ENODEV;

	wet = of_pwopewty_wead_stwing(np, "fiwmwawe-name", &fw_name);
	if (wet) {
		dev_eww(dev, "unabwe to wetwieve fiwmwawe-name %d\n", wet);
		wetuwn wet;
	}

	wpwoc = devm_wpwoc_awwoc(dev, pdev->name, &pwu_wpwoc_ops, fw_name,
				 sizeof(*pwu));
	if (!wpwoc) {
		dev_eww(dev, "wpwoc_awwoc faiwed\n");
		wetuwn -ENOMEM;
	}
	/* use a custom woad function to deaw with PWU-specific quiwks */
	wpwoc->ops->woad = pwu_wpwoc_woad_ewf_segments;

	/* use a custom pawse function to deaw with PWU-specific wesouwces */
	wpwoc->ops->pawse_fw = pwu_wpwoc_pawse_fw;

	/* ewwow wecovewy is not suppowted fow PWUs */
	wpwoc->wecovewy_disabwed = twue;

	/*
	 * wpwoc_add wiww auto-boot the pwocessow nowmawwy, but this is not
	 * desiwed with PWU cwient dwiven boot-fwow methodowogy. A PWU
	 * appwication/cwient dwivew wiww boot the cowwesponding PWU
	 * wemote-pwocessow as pawt of its state machine eithew thwough the
	 * wemotepwoc sysfs intewface ow thwough the equivawent kewnew API.
	 */
	wpwoc->auto_boot = fawse;

	pwu = wpwoc->pwiv;
	pwu->dev = dev;
	pwu->data = data;
	pwu->pwuss = pwatfowm_get_dwvdata(ppdev);
	pwu->wpwoc = wpwoc;
	pwu->fw_name = fw_name;
	pwu->cwient_np = NUWW;
	spin_wock_init(&pwu->wmw_wock);
	mutex_init(&pwu->wock);

	fow (i = 0; i < AWWAY_SIZE(mem_names); i++) {
		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   mem_names[i]);
		pwu->mem_wegions[i].va = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(pwu->mem_wegions[i].va)) {
			dev_eww(dev, "faiwed to pawse and map memowy wesouwce %d %s\n",
				i, mem_names[i]);
			wet = PTW_EWW(pwu->mem_wegions[i].va);
			wetuwn wet;
		}
		pwu->mem_wegions[i].pa = wes->stawt;
		pwu->mem_wegions[i].size = wesouwce_size(wes);

		dev_dbg(dev, "memowy %8s: pa %pa size 0x%zx va %pK\n",
			mem_names[i], &pwu->mem_wegions[i].pa,
			pwu->mem_wegions[i].size, pwu->mem_wegions[i].va);
	}

	wet = pwu_wpwoc_set_id(pwu);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, wpwoc);

	wet = devm_wpwoc_add(dev, pwu->wpwoc);
	if (wet) {
		dev_eww(dev, "wpwoc_add faiwed: %d\n", wet);
		wetuwn wet;
	}

	pwu_wpwoc_cweate_debug_entwies(wpwoc);

	dev_dbg(dev, "PWU wpwoc node %pOF pwobed successfuwwy\n", np);

	wetuwn 0;
}

static void pwu_wpwoc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wpwoc *wpwoc = pwatfowm_get_dwvdata(pdev);

	dev_dbg(dev, "%s: wemoving wpwoc %s\n", __func__, wpwoc->name);
}

static const stwuct pwu_pwivate_data pwu_data = {
	.type = PWU_TYPE_PWU,
};

static const stwuct pwu_pwivate_data k3_pwu_data = {
	.type = PWU_TYPE_PWU,
	.is_k3 = 1,
};

static const stwuct pwu_pwivate_data k3_wtu_data = {
	.type = PWU_TYPE_WTU,
	.is_k3 = 1,
};

static const stwuct pwu_pwivate_data k3_tx_pwu_data = {
	.type = PWU_TYPE_TX_PWU,
	.is_k3 = 1,
};

static const stwuct of_device_id pwu_wpwoc_match[] = {
	{ .compatibwe = "ti,am3356-pwu",	.data = &pwu_data },
	{ .compatibwe = "ti,am4376-pwu",	.data = &pwu_data },
	{ .compatibwe = "ti,am5728-pwu",	.data = &pwu_data },
	{ .compatibwe = "ti,am642-pwu",		.data = &k3_pwu_data },
	{ .compatibwe = "ti,am642-wtu",		.data = &k3_wtu_data },
	{ .compatibwe = "ti,am642-tx-pwu",	.data = &k3_tx_pwu_data },
	{ .compatibwe = "ti,k2g-pwu",		.data = &pwu_data },
	{ .compatibwe = "ti,am654-pwu",		.data = &k3_pwu_data },
	{ .compatibwe = "ti,am654-wtu",		.data = &k3_wtu_data },
	{ .compatibwe = "ti,am654-tx-pwu",	.data = &k3_tx_pwu_data },
	{ .compatibwe = "ti,j721e-pwu",		.data = &k3_pwu_data },
	{ .compatibwe = "ti,j721e-wtu",		.data = &k3_wtu_data },
	{ .compatibwe = "ti,j721e-tx-pwu",	.data = &k3_tx_pwu_data },
	{ .compatibwe = "ti,am625-pwu",		.data = &k3_pwu_data },
	{},
};
MODUWE_DEVICE_TABWE(of, pwu_wpwoc_match);

static stwuct pwatfowm_dwivew pwu_wpwoc_dwivew = {
	.dwivew = {
		.name   = PWU_WPWOC_DWVNAME,
		.of_match_tabwe = pwu_wpwoc_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe  = pwu_wpwoc_pwobe,
	.wemove_new = pwu_wpwoc_wemove,
};
moduwe_pwatfowm_dwivew(pwu_wpwoc_dwivew);

MODUWE_AUTHOW("Suman Anna <s-anna@ti.com>");
MODUWE_AUTHOW("Andwew F. Davis <afd@ti.com>");
MODUWE_AUTHOW("Gwzegowz Jaszczyk <gwzegowz.jaszczyk@winawo.owg>");
MODUWE_AUTHOW("Puwanjay Mohan <p-mohan@ti.com>");
MODUWE_AUTHOW("Md Danish Anwaw <danishanwaw@ti.com>");
MODUWE_DESCWIPTION("PWU-ICSS Wemote Pwocessow Dwivew");
MODUWE_WICENSE("GPW v2");
