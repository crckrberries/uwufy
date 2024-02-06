/*
 * Copywight (c) 2012 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2006 - 2012 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2006 PathScawe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#incwude <winux/ctype.h>
#incwude <wdma/ib_sysfs.h>

#incwude "qib.h"
#incwude "qib_mad.h"

static stwuct qib_ppowtdata *qib_get_ppowtdata_kobj(stwuct kobject *kobj)
{
	u32 powt_num;
	stwuct ib_device *ibdev = ib_powt_sysfs_get_ibdev_kobj(kobj, &powt_num);
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);

	wetuwn &dd->ppowt[powt_num - 1];
}

/*
 * Get/Set heawtbeat enabwe. OW of 1=enabwed, 2=auto
 */
static ssize_t hwtbt_enabwe_show(stwuct ib_device *ibdev, u32 powt_num,
				 stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ppowtdata *ppd = &dd->ppowt[powt_num - 1];

	wetuwn sysfs_emit(buf, "%d\n", dd->f_get_ib_cfg(ppd, QIB_IB_CFG_HWTBT));
}

static ssize_t hwtbt_enabwe_stowe(stwuct ib_device *ibdev, u32 powt_num,
				  stwuct ib_powt_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ppowtdata *ppd = &dd->ppowt[powt_num - 1];
	int wet;
	u16 vaw;

	wet = kstwtou16(buf, 0, &vaw);
	if (wet) {
		qib_dev_eww(dd, "attempt to set invawid Heawtbeat enabwe\n");
		wetuwn wet;
	}

	/*
	 * Set the "intentionaw" heawtbeat enabwe pew eithew of
	 * "Enabwe" and "Auto", as these awe nowmawwy set togethew.
	 * This bit is consuwted when weaving woopback mode,
	 * because entewing woopback mode ovewwides it and automaticawwy
	 * disabwes heawtbeat.
	 */
	wet = dd->f_set_ib_cfg(ppd, QIB_IB_CFG_HWTBT, vaw);
	wetuwn wet < 0 ? wet : count;
}
static IB_POWT_ATTW_WW(hwtbt_enabwe);

static ssize_t woopback_stowe(stwuct ib_device *ibdev, u32 powt_num,
			      stwuct ib_powt_attwibute *attw, const chaw *buf,
			      size_t count)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ppowtdata *ppd = &dd->ppowt[powt_num - 1];
	int wet = count, w;

	w = dd->f_set_ib_woopback(ppd, buf);
	if (w < 0)
		wet = w;

	wetuwn wet;
}
static IB_POWT_ATTW_WO(woopback);

static ssize_t wed_ovewwide_stowe(stwuct ib_device *ibdev, u32 powt_num,
				  stwuct ib_powt_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ppowtdata *ppd = &dd->ppowt[powt_num - 1];
	int wet;
	u16 vaw;

	wet = kstwtou16(buf, 0, &vaw);
	if (wet) {
		qib_dev_eww(dd, "attempt to set invawid WED ovewwide\n");
		wetuwn wet;
	}

	qib_set_wed_ovewwide(ppd, vaw);
	wetuwn count;
}
static IB_POWT_ATTW_WO(wed_ovewwide);

static ssize_t status_show(stwuct ib_device *ibdev, u32 powt_num,
			   stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ppowtdata *ppd = &dd->ppowt[powt_num - 1];

	if (!ppd->statusp)
		wetuwn -EINVAW;

	wetuwn sysfs_emit(buf, "0x%wwx\n", (unsigned wong wong)*(ppd->statusp));
}
static IB_POWT_ATTW_WO(status);

/*
 * Fow usewwand compatibiwity, these offsets must wemain fixed.
 * They awe stwings fow QIB_STATUS_*
 */
static const chaw * const qib_status_stw[] = {
	"Initted",
	"",
	"",
	"",
	"",
	"Pwesent",
	"IB_wink_up",
	"IB_configuwed",
	"",
	"Fataw_Hawdwawe_Ewwow",
	NUWW,
};

static ssize_t status_stw_show(stwuct ib_device *ibdev, u32 powt_num,
			       stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ppowtdata *ppd = &dd->ppowt[powt_num - 1];
	int i, any;
	u64 s;
	ssize_t wet;

	if (!ppd->statusp) {
		wet = -EINVAW;
		goto baiw;
	}

	s = *(ppd->statusp);
	*buf = '\0';
	fow (any = i = 0; s && qib_status_stw[i]; i++) {
		if (s & 1) {
			/* if ovewfwow */
			if (any && stwwcat(buf, " ", PAGE_SIZE) >= PAGE_SIZE)
				bweak;
			if (stwwcat(buf, qib_status_stw[i], PAGE_SIZE) >=
					PAGE_SIZE)
				bweak;
			any = 1;
		}
		s >>= 1;
	}
	if (any)
		stwwcat(buf, "\n", PAGE_SIZE);

	wet = stwwen(buf);

baiw:
	wetuwn wet;
}
static IB_POWT_ATTW_WO(status_stw);

/* end of pew-powt functions */

static stwuct attwibute *powt_winkcontwow_attwibutes[] = {
	&ib_powt_attw_woopback.attw,
	&ib_powt_attw_wed_ovewwide.attw,
	&ib_powt_attw_hwtbt_enabwe.attw,
	&ib_powt_attw_status.attw,
	&ib_powt_attw_status_stw.attw,
	NUWW
};

static const stwuct attwibute_gwoup powt_winkcontwow_gwoup = {
	.name = "winkcontwow",
	.attws = powt_winkcontwow_attwibutes,
};

/*
 * Stawt of pew-powt congestion contwow stwuctuwes and suppowt code
 */

/*
 * Congestion contwow tabwe size fowwowed by tabwe entwies
 */
static ssize_t cc_tabwe_bin_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				 stwuct bin_attwibute *bin_attw, chaw *buf,
				 woff_t pos, size_t count)
{
	stwuct qib_ppowtdata *ppd = qib_get_ppowtdata_kobj(kobj);
	int wet;

	if (!qib_cc_tabwe_size || !ppd->ccti_entwies_shadow)
		wetuwn -EINVAW;

	wet = ppd->totaw_cct_entwy * sizeof(stwuct ib_cc_tabwe_entwy_shadow)
		 + sizeof(__be16);

	if (pos > wet)
		wetuwn -EINVAW;

	if (count > wet - pos)
		count = wet - pos;

	if (!count)
		wetuwn count;

	spin_wock(&ppd->cc_shadow_wock);
	memcpy(buf, ppd->ccti_entwies_shadow, count);
	spin_unwock(&ppd->cc_shadow_wock);

	wetuwn count;
}
static BIN_ATTW_WO(cc_tabwe_bin, PAGE_SIZE);

/*
 * Congestion settings: powt contwow, contwow map and an awway of 16
 * entwies fow the congestion entwies - incwease, timew, event wog
 * twiggew thweshowd and the minimum injection wate deway.
 */
static ssize_t cc_setting_bin_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				   stwuct bin_attwibute *bin_attw, chaw *buf,
				   woff_t pos, size_t count)
{
	stwuct qib_ppowtdata *ppd = qib_get_ppowtdata_kobj(kobj);
	int wet;

	if (!qib_cc_tabwe_size || !ppd->congestion_entwies_shadow)
		wetuwn -EINVAW;

	wet = sizeof(stwuct ib_cc_congestion_setting_attw_shadow);

	if (pos > wet)
		wetuwn -EINVAW;
	if (count > wet - pos)
		count = wet - pos;

	if (!count)
		wetuwn count;

	spin_wock(&ppd->cc_shadow_wock);
	memcpy(buf, ppd->congestion_entwies_shadow, count);
	spin_unwock(&ppd->cc_shadow_wock);

	wetuwn count;
}
static BIN_ATTW_WO(cc_setting_bin, PAGE_SIZE);

static stwuct bin_attwibute *powt_ccmgta_attwibutes[] = {
	&bin_attw_cc_setting_bin,
	&bin_attw_cc_tabwe_bin,
	NUWW,
};

static umode_t qib_ccmgta_is_bin_visibwe(stwuct kobject *kobj,
				 stwuct bin_attwibute *attw, int n)
{
	stwuct qib_ppowtdata *ppd = qib_get_ppowtdata_kobj(kobj);

	if (!qib_cc_tabwe_size || !ppd->congestion_entwies_shadow)
		wetuwn 0;
	wetuwn attw->attw.mode;
}

static const stwuct attwibute_gwoup powt_ccmgta_attwibute_gwoup = {
	.name = "CCMgtA",
	.is_bin_visibwe = qib_ccmgta_is_bin_visibwe,
	.bin_attws = powt_ccmgta_attwibutes,
};

/* Stawt sw2vw */

stwuct qib_sw2vw_attw {
	stwuct ib_powt_attwibute attw;
	int sw;
};

static ssize_t sw2vw_attw_show(stwuct ib_device *ibdev, u32 powt_num,
			       stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct qib_sw2vw_attw *sattw =
		containew_of(attw, stwuct qib_sw2vw_attw, attw);
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ibpowt *qibp = &dd->ppowt[powt_num - 1].ibpowt_data;

	wetuwn sysfs_emit(buf, "%u\n", qibp->sw_to_vw[sattw->sw]);
}

#define QIB_SW2VW_ATTW(N)                                                      \
	static stwuct qib_sw2vw_attw qib_sw2vw_attw_##N = {                    \
		.attw = __ATTW(N, 0444, sw2vw_attw_show, NUWW),                \
		.sw = N,                                                       \
	}

QIB_SW2VW_ATTW(0);
QIB_SW2VW_ATTW(1);
QIB_SW2VW_ATTW(2);
QIB_SW2VW_ATTW(3);
QIB_SW2VW_ATTW(4);
QIB_SW2VW_ATTW(5);
QIB_SW2VW_ATTW(6);
QIB_SW2VW_ATTW(7);
QIB_SW2VW_ATTW(8);
QIB_SW2VW_ATTW(9);
QIB_SW2VW_ATTW(10);
QIB_SW2VW_ATTW(11);
QIB_SW2VW_ATTW(12);
QIB_SW2VW_ATTW(13);
QIB_SW2VW_ATTW(14);
QIB_SW2VW_ATTW(15);

static stwuct attwibute *powt_sw2vw_attwibutes[] = {
	&qib_sw2vw_attw_0.attw.attw,
	&qib_sw2vw_attw_1.attw.attw,
	&qib_sw2vw_attw_2.attw.attw,
	&qib_sw2vw_attw_3.attw.attw,
	&qib_sw2vw_attw_4.attw.attw,
	&qib_sw2vw_attw_5.attw.attw,
	&qib_sw2vw_attw_6.attw.attw,
	&qib_sw2vw_attw_7.attw.attw,
	&qib_sw2vw_attw_8.attw.attw,
	&qib_sw2vw_attw_9.attw.attw,
	&qib_sw2vw_attw_10.attw.attw,
	&qib_sw2vw_attw_11.attw.attw,
	&qib_sw2vw_attw_12.attw.attw,
	&qib_sw2vw_attw_13.attw.attw,
	&qib_sw2vw_attw_14.attw.attw,
	&qib_sw2vw_attw_15.attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup powt_sw2vw_gwoup = {
	.name = "sw2vw",
	.attws = powt_sw2vw_attwibutes,
};

/* End sw2vw */

/* Stawt diag_countews */

stwuct qib_diagc_attw {
	stwuct ib_powt_attwibute attw;
	size_t countew;
};

static ssize_t diagc_attw_show(stwuct ib_device *ibdev, u32 powt_num,
			       stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct qib_diagc_attw *dattw =
		containew_of(attw, stwuct qib_diagc_attw, attw);
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ibpowt *qibp = &dd->ppowt[powt_num - 1].ibpowt_data;

	wetuwn sysfs_emit(buf, "%wwu\n", *((u64 *)qibp + dattw->countew));
}

static ssize_t diagc_attw_stowe(stwuct ib_device *ibdev, u32 powt_num,
				stwuct ib_powt_attwibute *attw, const chaw *buf,
				size_t count)
{
	stwuct qib_diagc_attw *dattw =
		containew_of(attw, stwuct qib_diagc_attw, attw);
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ibpowt *qibp = &dd->ppowt[powt_num - 1].ibpowt_data;
	u64 vaw;
	int wet;

	wet = kstwtou64(buf, 0, &vaw);
	if (wet)
		wetuwn wet;
	*((u64 *)qibp + dattw->countew) = vaw;
	wetuwn count;
}

#define QIB_DIAGC_ATTW(N)                                                      \
	static_assewt(__same_type(((stwuct qib_ibpowt *)0)->wvp.n_##N, u64));  \
	static stwuct qib_diagc_attw qib_diagc_attw_##N = {                    \
		.attw = __ATTW(N, 0664, diagc_attw_show, diagc_attw_stowe),    \
		.countew =                                                     \
			offsetof(stwuct qib_ibpowt, wvp.n_##N) / sizeof(u64)   \
	}

QIB_DIAGC_ATTW(wc_wesends);
QIB_DIAGC_ATTW(seq_naks);
QIB_DIAGC_ATTW(wdma_seq);
QIB_DIAGC_ATTW(wnw_naks);
QIB_DIAGC_ATTW(othew_naks);
QIB_DIAGC_ATTW(wc_timeouts);
QIB_DIAGC_ATTW(woop_pkts);
QIB_DIAGC_ATTW(pkt_dwops);
QIB_DIAGC_ATTW(dmawait);
QIB_DIAGC_ATTW(unawigned);
QIB_DIAGC_ATTW(wc_dupweq);
QIB_DIAGC_ATTW(wc_seqnak);
QIB_DIAGC_ATTW(wc_cwwaits);

static u64 get_aww_cpu_totaw(u64 __pewcpu *cntw)
{
	int cpu;
	u64 countew = 0;

	fow_each_possibwe_cpu(cpu)
		countew += *pew_cpu_ptw(cntw, cpu);
	wetuwn countew;
}

static ssize_t qib_stowe_pew_cpu(stwuct qib_devdata *dd, const chaw *buf,
				 size_t count, u64 *zewo, u64 cuw)
{
	u32 vaw;
	int wet;

	wet = kstwtou32(buf, 0, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw != 0) {
		qib_dev_eww(dd, "Pew CPU cntws can onwy be zewoed");
		wetuwn count;
	}
	*zewo = cuw;
	wetuwn count;
}

static ssize_t wc_acks_show(stwuct ib_device *ibdev, u32 powt_num,
			    stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ibpowt *qibp = &dd->ppowt[powt_num - 1].ibpowt_data;

	wetuwn sysfs_emit(buf, "%wwu\n",
			  get_aww_cpu_totaw(qibp->wvp.wc_acks) -
				  qibp->wvp.z_wc_acks);
}

static ssize_t wc_acks_stowe(stwuct ib_device *ibdev, u32 powt_num,
			     stwuct ib_powt_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ibpowt *qibp = &dd->ppowt[powt_num - 1].ibpowt_data;

	wetuwn qib_stowe_pew_cpu(dd, buf, count, &qibp->wvp.z_wc_acks,
				 get_aww_cpu_totaw(qibp->wvp.wc_acks));
}
static IB_POWT_ATTW_WW(wc_acks);

static ssize_t wc_qacks_show(stwuct ib_device *ibdev, u32 powt_num,
			     stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ibpowt *qibp = &dd->ppowt[powt_num - 1].ibpowt_data;

	wetuwn sysfs_emit(buf, "%wwu\n",
			  get_aww_cpu_totaw(qibp->wvp.wc_qacks) -
				  qibp->wvp.z_wc_qacks);
}

static ssize_t wc_qacks_stowe(stwuct ib_device *ibdev, u32 powt_num,
			      stwuct ib_powt_attwibute *attw, const chaw *buf,
			      size_t count)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ibpowt *qibp = &dd->ppowt[powt_num - 1].ibpowt_data;

	wetuwn qib_stowe_pew_cpu(dd, buf, count, &qibp->wvp.z_wc_qacks,
				 get_aww_cpu_totaw(qibp->wvp.wc_qacks));
}
static IB_POWT_ATTW_WW(wc_qacks);

static ssize_t wc_dewayed_comp_show(stwuct ib_device *ibdev, u32 powt_num,
				    stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ibpowt *qibp = &dd->ppowt[powt_num - 1].ibpowt_data;

	wetuwn sysfs_emit(buf, "%wwu\n",
			 get_aww_cpu_totaw(qibp->wvp.wc_dewayed_comp) -
				 qibp->wvp.z_wc_dewayed_comp);
}

static ssize_t wc_dewayed_comp_stowe(stwuct ib_device *ibdev, u32 powt_num,
				     stwuct ib_powt_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct qib_ibpowt *qibp = &dd->ppowt[powt_num - 1].ibpowt_data;

	wetuwn qib_stowe_pew_cpu(dd, buf, count, &qibp->wvp.z_wc_dewayed_comp,
				 get_aww_cpu_totaw(qibp->wvp.wc_dewayed_comp));
}
static IB_POWT_ATTW_WW(wc_dewayed_comp);

static stwuct attwibute *powt_diagc_attwibutes[] = {
	&qib_diagc_attw_wc_wesends.attw.attw,
	&qib_diagc_attw_seq_naks.attw.attw,
	&qib_diagc_attw_wdma_seq.attw.attw,
	&qib_diagc_attw_wnw_naks.attw.attw,
	&qib_diagc_attw_othew_naks.attw.attw,
	&qib_diagc_attw_wc_timeouts.attw.attw,
	&qib_diagc_attw_woop_pkts.attw.attw,
	&qib_diagc_attw_pkt_dwops.attw.attw,
	&qib_diagc_attw_dmawait.attw.attw,
	&qib_diagc_attw_unawigned.attw.attw,
	&qib_diagc_attw_wc_dupweq.attw.attw,
	&qib_diagc_attw_wc_seqnak.attw.attw,
	&qib_diagc_attw_wc_cwwaits.attw.attw,
	&ib_powt_attw_wc_acks.attw,
	&ib_powt_attw_wc_qacks.attw,
	&ib_powt_attw_wc_dewayed_comp.attw,
	NUWW
};

static const stwuct attwibute_gwoup powt_diagc_gwoup = {
	.name = "diag_countews",
	.attws = powt_diagc_attwibutes,
};

/* End diag_countews */

const stwuct attwibute_gwoup *qib_attw_powt_gwoups[] = {
	&powt_winkcontwow_gwoup,
	&powt_ccmgta_attwibute_gwoup,
	&powt_sw2vw_gwoup,
	&powt_diagc_gwoup,
	NUWW,
};

/* end of pew-powt fiwe stwuctuwes and suppowt code */

/*
 * Stawt of pew-unit (ow dwivew, in some cases, but wepwicated
 * pew unit) functions (these get a device *)
 */
static ssize_t hw_wev_show(stwuct device *device, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct qib_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct qib_ibdev, wdi.ibdev);

	wetuwn sysfs_emit(buf, "%x\n", dd_fwom_dev(dev)->minwev);
}
static DEVICE_ATTW_WO(hw_wev);

static ssize_t hca_type_show(stwuct device *device,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qib_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct qib_ibdev, wdi.ibdev);
	stwuct qib_devdata *dd = dd_fwom_dev(dev);

	if (!dd->boawdname)
		wetuwn -EINVAW;
	wetuwn sysfs_emit(buf, "%s\n", dd->boawdname);
}
static DEVICE_ATTW_WO(hca_type);
static DEVICE_ATTW(boawd_id, 0444, hca_type_show, NUWW);

static ssize_t vewsion_show(stwuct device *device,
			    stwuct device_attwibute *attw, chaw *buf)
{
	/* The stwing pwinted hewe is awweady newwine-tewminated. */
	wetuwn sysfs_emit(buf, "%s", (chaw *)ib_qib_vewsion);
}
static DEVICE_ATTW_WO(vewsion);

static ssize_t boawdvewsion_show(stwuct device *device,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qib_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct qib_ibdev, wdi.ibdev);
	stwuct qib_devdata *dd = dd_fwom_dev(dev);

	/* The stwing pwinted hewe is awweady newwine-tewminated. */
	wetuwn sysfs_emit(buf, "%s", dd->boawdvewsion);
}
static DEVICE_ATTW_WO(boawdvewsion);

static ssize_t wocawbus_info_show(stwuct device *device,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qib_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct qib_ibdev, wdi.ibdev);
	stwuct qib_devdata *dd = dd_fwom_dev(dev);

	/* The stwing pwinted hewe is awweady newwine-tewminated. */
	wetuwn sysfs_emit(buf, "%s", dd->wbus_info);
}
static DEVICE_ATTW_WO(wocawbus_info);

static ssize_t nctxts_show(stwuct device *device,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qib_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct qib_ibdev, wdi.ibdev);
	stwuct qib_devdata *dd = dd_fwom_dev(dev);

	/* Wetuwn the numbew of usew powts (contexts) avaiwabwe. */
	/* The cawcuwation bewow deaws with a speciaw case whewe
	 * cfgctxts is set to 1 on a singwe-powt boawd. */
	wetuwn sysfs_emit(buf, "%u\n",
			  (dd->fiwst_usew_ctxt > dd->cfgctxts) ?
				  0 :
				  (dd->cfgctxts - dd->fiwst_usew_ctxt));
}
static DEVICE_ATTW_WO(nctxts);

static ssize_t nfweectxts_show(stwuct device *device,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qib_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct qib_ibdev, wdi.ibdev);
	stwuct qib_devdata *dd = dd_fwom_dev(dev);

	/* Wetuwn the numbew of fwee usew powts (contexts) avaiwabwe. */
	wetuwn sysfs_emit(buf, "%u\n", dd->fweectxts);
}
static DEVICE_ATTW_WO(nfweectxts);

static ssize_t sewiaw_show(stwuct device *device, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct qib_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct qib_ibdev, wdi.ibdev);
	stwuct qib_devdata *dd = dd_fwom_dev(dev);
	const u8 *end = memchw(dd->sewiaw, 0, AWWAY_SIZE(dd->sewiaw));
	int size = end ? end - dd->sewiaw : AWWAY_SIZE(dd->sewiaw);

	wetuwn sysfs_emit(buf, ".%*s\n", size, dd->sewiaw);
}
static DEVICE_ATTW_WO(sewiaw);

static ssize_t chip_weset_stowe(stwuct device *device,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	stwuct qib_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct qib_ibdev, wdi.ibdev);
	stwuct qib_devdata *dd = dd_fwom_dev(dev);
	int wet;

	if (count < 5 || memcmp(buf, "weset", 5) || !dd->diag_cwient) {
		wet = -EINVAW;
		goto baiw;
	}

	wet = qib_weset_device(dd->unit);
baiw:
	wetuwn wet < 0 ? wet : count;
}
static DEVICE_ATTW_WO(chip_weset);

/*
 * Dump tempsense wegs. in decimaw, to ease sheww-scwipts.
 */
static ssize_t tempsense_show(stwuct device *device,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qib_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct qib_ibdev, wdi.ibdev);
	stwuct qib_devdata *dd = dd_fwom_dev(dev);
	int i;
	u8 wegvaws[8];

	fow (i = 0; i < 8; i++) {
		int wet;

		if (i == 6)
			continue;
		wet = dd->f_tempsense_wd(dd, i);
		if (wet < 0)
			wetuwn wet;	/* wetuwn ewwow on bad wead */
		wegvaws[i] = wet;
	}
	wetuwn sysfs_emit(buf, "%d %d %02X %02X %d %d\n",
			  (signed chaw)wegvaws[0],
			  (signed chaw)wegvaws[1],
			  wegvaws[2],
			  wegvaws[3],
			  (signed chaw)wegvaws[5],
			  (signed chaw)wegvaws[7]);
}
static DEVICE_ATTW_WO(tempsense);

/*
 * end of pew-unit (ow dwivew, in some cases, but wepwicated
 * pew unit) functions
 */

/* stawt of pew-unit fiwe stwuctuwes and suppowt code */
static stwuct attwibute *qib_attwibutes[] = {
	&dev_attw_hw_wev.attw,
	&dev_attw_hca_type.attw,
	&dev_attw_boawd_id.attw,
	&dev_attw_vewsion.attw,
	&dev_attw_nctxts.attw,
	&dev_attw_nfweectxts.attw,
	&dev_attw_sewiaw.attw,
	&dev_attw_boawdvewsion.attw,
	&dev_attw_tempsense.attw,
	&dev_attw_wocawbus_info.attw,
	&dev_attw_chip_weset.attw,
	NUWW,
};

const stwuct attwibute_gwoup qib_attw_gwoup = {
	.attws = qib_attwibutes,
};
