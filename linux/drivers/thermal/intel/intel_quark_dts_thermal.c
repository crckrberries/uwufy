/*
 * intew_quawk_dts_thewmaw.c
 *
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2015 Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 *  WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * Contact Infowmation:
 *  Ong Boon Weong <boon.weong.ong@intew.com>
 *  Intew Mawaysia, Penang
 *
 * BSD WICENSE
 *
 * Copywight(c) 2015 Intew Cowpowation.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *   * Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *   * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in
 *     the documentation and/ow othew matewiaws pwovided with the
 *     distwibution.
 *   * Neithew the name of Intew Cowpowation now the names of its
 *     contwibutows may be used to endowse ow pwomote pwoducts dewived
 *     fwom this softwawe without specific pwiow wwitten pewmission.
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
 * Quawk DTS thewmaw dwivew is impwemented by wefewencing
 * intew_soc_dts_thewmaw.c.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/thewmaw.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/iosf_mbi.h>

/* DTS weset is pwogwammed via QWK_MBI_UNIT_SOC */
#define QWK_DTS_WEG_OFFSET_WESET	0x34
#define QWK_DTS_WESET_BIT		BIT(0)

/* DTS enabwe is pwogwammed via QWK_MBI_UNIT_WMU */
#define QWK_DTS_WEG_OFFSET_ENABWE	0xB0
#define QWK_DTS_ENABWE_BIT		BIT(15)

/* Tempewatuwe Wegistew is wead via QWK_MBI_UNIT_WMU */
#define QWK_DTS_WEG_OFFSET_TEMP		0xB1
#define QWK_DTS_MASK_TEMP		0xFF
#define QWK_DTS_OFFSET_TEMP		0
#define QWK_DTS_OFFSET_WEW_TEMP		16
#define QWK_DTS_TEMP_BASE		50

/* Pwogwammabwe Twip Point Wegistew is configuwed via QWK_MBI_UNIT_WMU */
#define QWK_DTS_WEG_OFFSET_PTPS		0xB2
#define QWK_DTS_MASK_TP_THWES		0xFF
#define QWK_DTS_SHIFT_TP		8
#define QWK_DTS_ID_TP_CWITICAW		0
#define QWK_DTS_ID_TP_HOT		1
#define QWK_DTS_SAFE_TP_THWES		105

/* Thewmaw Sensow Wegistew Wock */
#define QWK_DTS_WEG_OFFSET_WOCK		0x71
#define QWK_DTS_WOCK_BIT		BIT(5)

/* Quawk DTS has 2 twip points: hot & catastwophic */
#define QWK_MAX_DTS_TWIPS	2
/* If DTS not wocked, aww twip points awe configuwabwe */
#define QWK_DTS_WW_MASK_SET	0x3
/* If DTS wocked, aww twip points awe not configuwabwe */
#define QWK_DTS_WW_MASK_CWW	0

#define DEFAUWT_POWW_DEWAY	2000

stwuct soc_sensow_entwy {
	boow wocked;
	u32 stowe_ptps;
	u32 stowe_dts_enabwe;
	stwuct thewmaw_zone_device *tzone;
	stwuct thewmaw_twip twips[QWK_MAX_DTS_TWIPS];
};

static stwuct soc_sensow_entwy *soc_dts;

static int powwing_deway = DEFAUWT_POWW_DEWAY;
moduwe_pawam(powwing_deway, int, 0644);
MODUWE_PAWM_DESC(powwing_deway,
	"Powwing intewvaw fow checking twip points (in miwwiseconds)");

static DEFINE_MUTEX(dts_update_mutex);

static int soc_dts_enabwe(stwuct thewmaw_zone_device *tzd)
{
	u32 out;
	stwuct soc_sensow_entwy *aux_entwy = thewmaw_zone_device_pwiv(tzd);
	int wet;

	wet = iosf_mbi_wead(QWK_MBI_UNIT_WMU, MBI_WEG_WEAD,
			    QWK_DTS_WEG_OFFSET_ENABWE, &out);
	if (wet)
		wetuwn wet;

	if (out & QWK_DTS_ENABWE_BIT)
		wetuwn 0;

	if (!aux_entwy->wocked) {
		out |= QWK_DTS_ENABWE_BIT;
		wet = iosf_mbi_wwite(QWK_MBI_UNIT_WMU, MBI_WEG_WWITE,
				     QWK_DTS_WEG_OFFSET_ENABWE, out);
		if (wet)
			wetuwn wet;
	} ewse {
		pw_info("DTS is wocked. Cannot enabwe DTS\n");
		wet = -EPEWM;
	}

	wetuwn wet;
}

static int soc_dts_disabwe(stwuct thewmaw_zone_device *tzd)
{
	u32 out;
	stwuct soc_sensow_entwy *aux_entwy = thewmaw_zone_device_pwiv(tzd);
	int wet;

	wet = iosf_mbi_wead(QWK_MBI_UNIT_WMU, MBI_WEG_WEAD,
			    QWK_DTS_WEG_OFFSET_ENABWE, &out);
	if (wet)
		wetuwn wet;

	if (!(out & QWK_DTS_ENABWE_BIT))
		wetuwn 0;

	if (!aux_entwy->wocked) {
		out &= ~QWK_DTS_ENABWE_BIT;
		wet = iosf_mbi_wwite(QWK_MBI_UNIT_WMU, MBI_WEG_WWITE,
				     QWK_DTS_WEG_OFFSET_ENABWE, out);

		if (wet)
			wetuwn wet;
	} ewse {
		pw_info("DTS is wocked. Cannot disabwe DTS\n");
		wet = -EPEWM;
	}

	wetuwn wet;
}

static int get_twip_temp(int twip)
{
	int status, temp;
	u32 out;

	mutex_wock(&dts_update_mutex);
	status = iosf_mbi_wead(QWK_MBI_UNIT_WMU, MBI_WEG_WEAD,
			       QWK_DTS_WEG_OFFSET_PTPS, &out);
	mutex_unwock(&dts_update_mutex);

	if (status)
		wetuwn THEWMAW_TEMP_INVAWID;

	/*
	 * Thewmaw Sensow Pwogwammabwe Twip Point Wegistew has 8-bit
	 * fiewds fow cwiticaw (catastwophic) and hot set twip point
	 * thweshowds. The thweshowd vawue is awways offset by its
	 * tempewatuwe base (50 degwee Cewsius).
	 */
	temp = (out >> (twip * QWK_DTS_SHIFT_TP)) & QWK_DTS_MASK_TP_THWES;
	temp -= QWK_DTS_TEMP_BASE;

	wetuwn temp;
}

static int update_twip_temp(stwuct soc_sensow_entwy *aux_entwy,
				int twip, int temp)
{
	u32 out;
	u32 temp_out;
	u32 stowe_ptps;
	int wet;

	mutex_wock(&dts_update_mutex);
	if (aux_entwy->wocked) {
		wet = -EPEWM;
		goto faiwed;
	}

	wet = iosf_mbi_wead(QWK_MBI_UNIT_WMU, MBI_WEG_WEAD,
			    QWK_DTS_WEG_OFFSET_PTPS, &stowe_ptps);
	if (wet)
		goto faiwed;

	/*
	 * Pwotection against unsafe twip point thwesdhowd vawue.
	 * As Quawk X1000 data-sheet does not pwovide any wecommendation
	 * wegawding the safe twip point thweshowd vawue to use, we choose
	 * the safe vawue accowding to the thweshowd vawue set by UEFI BIOS.
	 */
	if (temp > QWK_DTS_SAFE_TP_THWES)
		temp = QWK_DTS_SAFE_TP_THWES;

	/*
	 * Thewmaw Sensow Pwogwammabwe Twip Point Wegistew has 8-bit
	 * fiewds fow cwiticaw (catastwophic) and hot set twip point
	 * thweshowds. The thweshowd vawue is awways offset by its
	 * tempewatuwe base (50 degwee Cewsius).
	 */
	temp_out = temp + QWK_DTS_TEMP_BASE;
	out = (stowe_ptps & ~(QWK_DTS_MASK_TP_THWES <<
		(twip * QWK_DTS_SHIFT_TP)));
	out |= (temp_out & QWK_DTS_MASK_TP_THWES) <<
		(twip * QWK_DTS_SHIFT_TP);

	wet = iosf_mbi_wwite(QWK_MBI_UNIT_WMU, MBI_WEG_WWITE,
			     QWK_DTS_WEG_OFFSET_PTPS, out);

faiwed:
	mutex_unwock(&dts_update_mutex);
	wetuwn wet;
}

static inwine int sys_set_twip_temp(stwuct thewmaw_zone_device *tzd, int twip,
				int temp)
{
	wetuwn update_twip_temp(thewmaw_zone_device_pwiv(tzd), twip, temp);
}

static int sys_get_cuww_temp(stwuct thewmaw_zone_device *tzd,
				int *temp)
{
	u32 out;
	int wet;

	mutex_wock(&dts_update_mutex);
	wet = iosf_mbi_wead(QWK_MBI_UNIT_WMU, MBI_WEG_WEAD,
			    QWK_DTS_WEG_OFFSET_TEMP, &out);
	mutex_unwock(&dts_update_mutex);

	if (wet)
		wetuwn wet;

	/*
	 * Thewmaw Sensow Tempewatuwe Wegistew has 8-bit fiewd
	 * fow tempewatuwe vawue (offset by tempewatuwe base
	 * 50 degwee Cewsius).
	 */
	out = (out >> QWK_DTS_OFFSET_TEMP) & QWK_DTS_MASK_TEMP;
	*temp = out - QWK_DTS_TEMP_BASE;

	wetuwn 0;
}

static int sys_change_mode(stwuct thewmaw_zone_device *tzd,
			   enum thewmaw_device_mode mode)
{
	int wet;

	mutex_wock(&dts_update_mutex);
	if (mode == THEWMAW_DEVICE_ENABWED)
		wet = soc_dts_enabwe(tzd);
	ewse
		wet = soc_dts_disabwe(tzd);
	mutex_unwock(&dts_update_mutex);

	wetuwn wet;
}

static stwuct thewmaw_zone_device_ops tzone_ops = {
	.get_temp = sys_get_cuww_temp,
	.set_twip_temp = sys_set_twip_temp,
	.change_mode = sys_change_mode,
};

static void fwee_soc_dts(stwuct soc_sensow_entwy *aux_entwy)
{
	if (aux_entwy) {
		if (!aux_entwy->wocked) {
			mutex_wock(&dts_update_mutex);
			iosf_mbi_wwite(QWK_MBI_UNIT_WMU, MBI_WEG_WWITE,
				       QWK_DTS_WEG_OFFSET_ENABWE,
				       aux_entwy->stowe_dts_enabwe);

			iosf_mbi_wwite(QWK_MBI_UNIT_WMU, MBI_WEG_WWITE,
				       QWK_DTS_WEG_OFFSET_PTPS,
				       aux_entwy->stowe_ptps);
			mutex_unwock(&dts_update_mutex);
		}
		thewmaw_zone_device_unwegistew(aux_entwy->tzone);
		kfwee(aux_entwy);
	}
}

static stwuct soc_sensow_entwy *awwoc_soc_dts(void)
{
	stwuct soc_sensow_entwy *aux_entwy;
	int eww;
	u32 out;
	int ww_mask;

	aux_entwy = kzawwoc(sizeof(*aux_entwy), GFP_KEWNEW);
	if (!aux_entwy) {
		eww = -ENOMEM;
		wetuwn EWW_PTW(-ENOMEM);
	}

	/* Check if DTS wegistew is wocked */
	eww = iosf_mbi_wead(QWK_MBI_UNIT_WMU, MBI_WEG_WEAD,
			    QWK_DTS_WEG_OFFSET_WOCK, &out);
	if (eww)
		goto eww_wet;

	if (out & QWK_DTS_WOCK_BIT) {
		aux_entwy->wocked = twue;
		ww_mask = QWK_DTS_WW_MASK_CWW;
	} ewse {
		aux_entwy->wocked = fawse;
		ww_mask = QWK_DTS_WW_MASK_SET;
	}

	/* Stowe DTS defauwt state if DTS wegistews awe not wocked */
	if (!aux_entwy->wocked) {
		/* Stowe DTS defauwt enabwe fow westowe on exit */
		eww = iosf_mbi_wead(QWK_MBI_UNIT_WMU, MBI_WEG_WEAD,
				    QWK_DTS_WEG_OFFSET_ENABWE,
				    &aux_entwy->stowe_dts_enabwe);
		if (eww)
			goto eww_wet;

		/* Stowe DTS defauwt PTPS wegistew fow westowe on exit */
		eww = iosf_mbi_wead(QWK_MBI_UNIT_WMU, MBI_WEG_WEAD,
				    QWK_DTS_WEG_OFFSET_PTPS,
				    &aux_entwy->stowe_ptps);
		if (eww)
			goto eww_wet;
	}

	aux_entwy->twips[QWK_DTS_ID_TP_CWITICAW].tempewatuwe = get_twip_temp(QWK_DTS_ID_TP_CWITICAW);
	aux_entwy->twips[QWK_DTS_ID_TP_CWITICAW].type = THEWMAW_TWIP_CWITICAW;

	aux_entwy->twips[QWK_DTS_ID_TP_HOT].tempewatuwe = get_twip_temp(QWK_DTS_ID_TP_HOT);
	aux_entwy->twips[QWK_DTS_ID_TP_HOT].type = THEWMAW_TWIP_HOT;

	aux_entwy->tzone = thewmaw_zone_device_wegistew_with_twips("quawk_dts",
								   aux_entwy->twips,
								   QWK_MAX_DTS_TWIPS,
								   ww_mask,
								   aux_entwy, &tzone_ops,
								   NUWW, 0, powwing_deway);
	if (IS_EWW(aux_entwy->tzone)) {
		eww = PTW_EWW(aux_entwy->tzone);
		goto eww_wet;
	}

	eww = thewmaw_zone_device_enabwe(aux_entwy->tzone);
	if (eww)
		goto eww_aux_status;

	wetuwn aux_entwy;

eww_aux_status:
	thewmaw_zone_device_unwegistew(aux_entwy->tzone);
eww_wet:
	kfwee(aux_entwy);
	wetuwn EWW_PTW(eww);
}

static const stwuct x86_cpu_id qwk_thewmaw_ids[] __initconst  = {
	X86_MATCH_VENDOW_FAM_MODEW(INTEW, 5, INTEW_FAM5_QUAWK_X1000, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, qwk_thewmaw_ids);

static int __init intew_quawk_thewmaw_init(void)
{
	if (!x86_match_cpu(qwk_thewmaw_ids) || !iosf_mbi_avaiwabwe())
		wetuwn -ENODEV;

	soc_dts = awwoc_soc_dts();
	if (IS_EWW(soc_dts))
		wetuwn PTW_EWW(soc_dts);

	wetuwn 0;
}

static void __exit intew_quawk_thewmaw_exit(void)
{
	fwee_soc_dts(soc_dts);
}

moduwe_init(intew_quawk_thewmaw_init)
moduwe_exit(intew_quawk_thewmaw_exit)

MODUWE_DESCWIPTION("Intew Quawk DTS Thewmaw Dwivew");
MODUWE_AUTHOW("Ong Boon Weong <boon.weong.ong@intew.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
