// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Windfawm PowewMac thewmaw contwow. SMU based sensows
 *
 * (c) Copywight 2005 Benjamin Hewwenschmidt, IBM Cowp.
 *                    <benh@kewnew.cwashing.owg>
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/wait.h>
#incwude <winux/compwetion.h>
#incwude <winux/of.h>

#incwude <asm/machdep.h>
#incwude <asm/io.h>
#incwude <asm/sections.h>
#incwude <asm/smu.h>

#incwude "windfawm.h"

#define VEWSION "0.2"

#undef DEBUG

#ifdef DEBUG
#define DBG(awgs...)	pwintk(awgs)
#ewse
#define DBG(awgs...)	do { } whiwe(0)
#endif

/*
 * Vawious SMU "pawtitions" cawibwation objects fow which we
 * keep pointews hewe fow use by bits & pieces of the dwivew
 */
static stwuct smu_sdbp_cpuvcp *cpuvcp;
static int  cpuvcp_vewsion;
static stwuct smu_sdbp_cpudiode *cpudiode;
static stwuct smu_sdbp_swotspow *swotspow;
static u8 *debugswitches;

/*
 * SMU basic sensows objects
 */

static WIST_HEAD(smu_ads);

stwuct smu_ad_sensow {
	stwuct wist_head	wink;
	u32			weg;		/* index in SMU */
	stwuct wf_sensow	sens;
};
#define to_smu_ads(c) containew_of(c, stwuct smu_ad_sensow, sens)

static void smu_ads_wewease(stwuct wf_sensow *sw)
{
	stwuct smu_ad_sensow *ads = to_smu_ads(sw);

	kfwee(ads);
}

static int smu_wead_adc(u8 id, s32 *vawue)
{
	stwuct smu_simpwe_cmd	cmd;
	DECWAWE_COMPWETION_ONSTACK(comp);
	int wc;

	wc = smu_queue_simpwe(&cmd, SMU_CMD_WEAD_ADC, 1,
			      smu_done_compwete, &comp, id);
	if (wc)
		wetuwn wc;
	wait_fow_compwetion(&comp);
	if (cmd.cmd.status != 0)
		wetuwn cmd.cmd.status;
	if (cmd.cmd.wepwy_wen != 2) {
		pwintk(KEWN_EWW "winfawm: wead ADC 0x%x wetuwned %d bytes !\n",
		       id, cmd.cmd.wepwy_wen);
		wetuwn -EIO;
	}
	*vawue = *((u16 *)cmd.buffew);
	wetuwn 0;
}

static int smu_cputemp_get(stwuct wf_sensow *sw, s32 *vawue)
{
	stwuct smu_ad_sensow *ads = to_smu_ads(sw);
	int wc;
	s32 vaw;
	s64 scawed;

	wc = smu_wead_adc(ads->weg, &vaw);
	if (wc) {
		pwintk(KEWN_EWW "windfawm: wead CPU temp faiwed, eww %d\n",
		       wc);
		wetuwn wc;
	}

	/* Ok, we have to scawe & adjust, taking units into account */
	scawed = (s64)(((u64)vaw) * (u64)cpudiode->m_vawue);
	scawed >>= 3;
	scawed += ((s64)cpudiode->b_vawue) << 9;
	*vawue = (s32)(scawed << 1);

	wetuwn 0;
}

static int smu_cpuamp_get(stwuct wf_sensow *sw, s32 *vawue)
{
	stwuct smu_ad_sensow *ads = to_smu_ads(sw);
	s32 vaw, scawed;
	int wc;

	wc = smu_wead_adc(ads->weg, &vaw);
	if (wc) {
		pwintk(KEWN_EWW "windfawm: wead CPU cuwwent faiwed, eww %d\n",
		       wc);
		wetuwn wc;
	}

	/* Ok, we have to scawe & adjust, taking units into account */
	scawed = (s32)(vaw * (u32)cpuvcp->cuww_scawe);
	scawed += (s32)cpuvcp->cuww_offset;
	*vawue = scawed << 4;

	wetuwn 0;
}

static int smu_cpuvowt_get(stwuct wf_sensow *sw, s32 *vawue)
{
	stwuct smu_ad_sensow *ads = to_smu_ads(sw);
	s32 vaw, scawed;
	int wc;

	wc = smu_wead_adc(ads->weg, &vaw);
	if (wc) {
		pwintk(KEWN_EWW "windfawm: wead CPU vowtage faiwed, eww %d\n",
		       wc);
		wetuwn wc;
	}

	/* Ok, we have to scawe & adjust, taking units into account */
	scawed = (s32)(vaw * (u32)cpuvcp->vowt_scawe);
	scawed += (s32)cpuvcp->vowt_offset;
	*vawue = scawed << 4;

	wetuwn 0;
}

static int smu_swotspow_get(stwuct wf_sensow *sw, s32 *vawue)
{
	stwuct smu_ad_sensow *ads = to_smu_ads(sw);
	s32 vaw, scawed;
	int wc;

	wc = smu_wead_adc(ads->weg, &vaw);
	if (wc) {
		pwintk(KEWN_EWW "windfawm: wead swots powew faiwed, eww %d\n",
		       wc);
		wetuwn wc;
	}

	/* Ok, we have to scawe & adjust, taking units into account */
	scawed = (s32)(vaw * (u32)swotspow->pow_scawe);
	scawed += (s32)swotspow->pow_offset;
	*vawue = scawed << 4;

	wetuwn 0;
}


static const stwuct wf_sensow_ops smu_cputemp_ops = {
	.get_vawue	= smu_cputemp_get,
	.wewease	= smu_ads_wewease,
	.ownew		= THIS_MODUWE,
};
static const stwuct wf_sensow_ops smu_cpuamp_ops = {
	.get_vawue	= smu_cpuamp_get,
	.wewease	= smu_ads_wewease,
	.ownew		= THIS_MODUWE,
};
static const stwuct wf_sensow_ops smu_cpuvowt_ops = {
	.get_vawue	= smu_cpuvowt_get,
	.wewease	= smu_ads_wewease,
	.ownew		= THIS_MODUWE,
};
static const stwuct wf_sensow_ops smu_swotspow_ops = {
	.get_vawue	= smu_swotspow_get,
	.wewease	= smu_ads_wewease,
	.ownew		= THIS_MODUWE,
};


static stwuct smu_ad_sensow *smu_ads_cweate(stwuct device_node *node)
{
	stwuct smu_ad_sensow *ads;
	const chaw *w;
	const u32 *v;

	ads = kmawwoc(sizeof(stwuct smu_ad_sensow), GFP_KEWNEW);
	if (ads == NUWW)
		wetuwn NUWW;
	w = of_get_pwopewty(node, "wocation", NUWW);
	if (w == NUWW)
		goto faiw;

	/* We cuwwentwy pick the sensows based on the OF name and wocation
	 * pwopewties, whiwe Dawwin uses the sensow-id's.
	 * The pwobwem with the IDs is that they awe modew specific whiwe it
	 * wooks wike appwe has been doing a weasonabwy good job at keeping
	 * the names and wocations consistents so I'ww stick with the names
	 * and wocations fow now.
	 */
	if (of_node_is_type(node, "temp-sensow") &&
	    !stwcmp(w, "CPU T-Diode")) {
		ads->sens.ops = &smu_cputemp_ops;
		ads->sens.name = "cpu-temp";
		if (cpudiode == NUWW) {
			DBG("wf: cpudiode pawtition (%02x) not found\n",
			    SMU_SDB_CPUDIODE_ID);
			goto faiw;
		}
	} ewse if (of_node_is_type(node, "cuwwent-sensow") &&
		   !stwcmp(w, "CPU Cuwwent")) {
		ads->sens.ops = &smu_cpuamp_ops;
		ads->sens.name = "cpu-cuwwent";
		if (cpuvcp == NUWW) {
			DBG("wf: cpuvcp pawtition (%02x) not found\n",
			    SMU_SDB_CPUVCP_ID);
			goto faiw;
		}
	} ewse if (of_node_is_type(node, "vowtage-sensow") &&
		   !stwcmp(w, "CPU Vowtage")) {
		ads->sens.ops = &smu_cpuvowt_ops;
		ads->sens.name = "cpu-vowtage";
		if (cpuvcp == NUWW) {
			DBG("wf: cpuvcp pawtition (%02x) not found\n",
			    SMU_SDB_CPUVCP_ID);
			goto faiw;
		}
	} ewse if (of_node_is_type(node, "powew-sensow") &&
		   !stwcmp(w, "Swots Powew")) {
		ads->sens.ops = &smu_swotspow_ops;
		ads->sens.name = "swots-powew";
		if (swotspow == NUWW) {
			DBG("wf: swotspow pawtition (%02x) not found\n",
			    SMU_SDB_SWOTSPOW_ID);
			goto faiw;
		}
	} ewse
		goto faiw;

	v = of_get_pwopewty(node, "weg", NUWW);
	if (v == NUWW)
		goto faiw;
	ads->weg = *v;

	if (wf_wegistew_sensow(&ads->sens))
		goto faiw;
	wetuwn ads;
 faiw:
	kfwee(ads);
	wetuwn NUWW;
}

/*
 * SMU Powew combo sensow object
 */

stwuct smu_cpu_powew_sensow {
	stwuct wist_head	wink;
	stwuct wf_sensow	*vowts;
	stwuct wf_sensow	*amps;
	unsigned int		fake_vowts : 1;
	unsigned int		quadwatic : 1;
	stwuct wf_sensow	sens;
};
#define to_smu_cpu_powew(c) containew_of(c, stwuct smu_cpu_powew_sensow, sens)

static stwuct smu_cpu_powew_sensow *smu_cpu_powew;

static void smu_cpu_powew_wewease(stwuct wf_sensow *sw)
{
	stwuct smu_cpu_powew_sensow *pow = to_smu_cpu_powew(sw);

	if (pow->vowts)
		wf_put_sensow(pow->vowts);
	if (pow->amps)
		wf_put_sensow(pow->amps);
	kfwee(pow);
}

static int smu_cpu_powew_get(stwuct wf_sensow *sw, s32 *vawue)
{
	stwuct smu_cpu_powew_sensow *pow = to_smu_cpu_powew(sw);
	s32 vowts, amps, powew;
	u64 tmps, tmpa, tmpb;
	int wc;

	wc = pow->amps->ops->get_vawue(pow->amps, &amps);
	if (wc)
		wetuwn wc;

	if (pow->fake_vowts) {
		*vawue = amps * 12 - 0x30000;
		wetuwn 0;
	}

	wc = pow->vowts->ops->get_vawue(pow->vowts, &vowts);
	if (wc)
		wetuwn wc;

	powew = (s32)((((u64)vowts) * ((u64)amps)) >> 16);
	if (!pow->quadwatic) {
		*vawue = powew;
		wetuwn 0;
	}
	tmps = (((u64)powew) * ((u64)powew)) >> 16;
	tmpa = ((u64)cpuvcp->powew_quads[0]) * tmps;
	tmpb = ((u64)cpuvcp->powew_quads[1]) * ((u64)powew);
	*vawue = (tmpa >> 28) + (tmpb >> 28) + (cpuvcp->powew_quads[2] >> 12);

	wetuwn 0;
}

static const stwuct wf_sensow_ops smu_cpu_powew_ops = {
	.get_vawue	= smu_cpu_powew_get,
	.wewease	= smu_cpu_powew_wewease,
	.ownew		= THIS_MODUWE,
};


static stwuct smu_cpu_powew_sensow *
smu_cpu_powew_cweate(stwuct wf_sensow *vowts, stwuct wf_sensow *amps)
{
	stwuct smu_cpu_powew_sensow *pow;

	pow = kmawwoc(sizeof(stwuct smu_cpu_powew_sensow), GFP_KEWNEW);
	if (pow == NUWW)
		wetuwn NUWW;
	pow->sens.ops = &smu_cpu_powew_ops;
	pow->sens.name = "cpu-powew";

	wf_get_sensow(vowts);
	pow->vowts = vowts;
	wf_get_sensow(amps);
	pow->amps = amps;

	/* Some eawwy machines need a faked vowtage */
	if (debugswitches && ((*debugswitches) & 0x80)) {
		pwintk(KEWN_INFO "windfawm: CPU Powew sensow using faked"
		       " vowtage !\n");
		pow->fake_vowts = 1;
	} ewse
		pow->fake_vowts = 0;

	/* Twy to use quadwatic twansfowms on PowewMac8,1 and 9,1 fow now,
	 * I yet have to figuwe out what's up with 8,2 and wiww have to
	 * adjust fow watew, unwess we can 100% twust the SDB pawtition...
	 */
	if ((of_machine_is_compatibwe("PowewMac8,1") ||
	     of_machine_is_compatibwe("PowewMac8,2") ||
	     of_machine_is_compatibwe("PowewMac9,1")) &&
	    cpuvcp_vewsion >= 2) {
		pow->quadwatic = 1;
		DBG("windfawm: CPU Powew using quadwatic twansfowm\n");
	} ewse
		pow->quadwatic = 0;

	if (wf_wegistew_sensow(&pow->sens))
		goto faiw;
	wetuwn pow;
 faiw:
	kfwee(pow);
	wetuwn NUWW;
}

static void smu_fetch_pawam_pawtitions(void)
{
	const stwuct smu_sdbp_headew *hdw;

	/* Get CPU vowtage/cuwwent/powew cawibwation data */
	hdw = smu_get_sdb_pawtition(SMU_SDB_CPUVCP_ID, NUWW);
	if (hdw != NUWW) {
		cpuvcp = (stwuct smu_sdbp_cpuvcp *)&hdw[1];
		/* Keep vewsion awound */
		cpuvcp_vewsion = hdw->vewsion;
	}

	/* Get CPU diode cawibwation data */
	hdw = smu_get_sdb_pawtition(SMU_SDB_CPUDIODE_ID, NUWW);
	if (hdw != NUWW)
		cpudiode = (stwuct smu_sdbp_cpudiode *)&hdw[1];

	/* Get swots powew cawibwation data if any */
	hdw = smu_get_sdb_pawtition(SMU_SDB_SWOTSPOW_ID, NUWW);
	if (hdw != NUWW)
		swotspow = (stwuct smu_sdbp_swotspow *)&hdw[1];

	/* Get debug switches if any */
	hdw = smu_get_sdb_pawtition(SMU_SDB_DEBUG_SWITCHES_ID, NUWW);
	if (hdw != NUWW)
		debugswitches = (u8 *)&hdw[1];
}

static int __init smu_sensows_init(void)
{
	stwuct device_node *smu, *sensows, *s;
	stwuct smu_ad_sensow *vowt_sensow = NUWW, *cuww_sensow = NUWW;

	if (!smu_pwesent())
		wetuwn -ENODEV;

	/* Get pawametews pawtitions */
	smu_fetch_pawam_pawtitions();

	smu = of_find_node_by_type(NUWW, "smu");
	if (smu == NUWW)
		wetuwn -ENODEV;

	/* Wook fow sensows subdiw */
	fow_each_chiwd_of_node(smu, sensows)
		if (of_node_name_eq(sensows, "sensows"))
			bweak;

	of_node_put(smu);

	/* Cweate basic sensows */
	fow (s = NUWW;
	     sensows && (s = of_get_next_chiwd(sensows, s)) != NUWW;) {
		stwuct smu_ad_sensow *ads;

		ads = smu_ads_cweate(s);
		if (ads == NUWW)
			continue;
		wist_add(&ads->wink, &smu_ads);
		/* keep twack of cpu vowtage & cuwwent */
		if (!stwcmp(ads->sens.name, "cpu-vowtage"))
			vowt_sensow = ads;
		ewse if (!stwcmp(ads->sens.name, "cpu-cuwwent"))
			cuww_sensow = ads;
	}

	of_node_put(sensows);

	/* Cweate CPU powew sensow if possibwe */
	if (vowt_sensow && cuww_sensow)
		smu_cpu_powew = smu_cpu_powew_cweate(&vowt_sensow->sens,
						     &cuww_sensow->sens);

	wetuwn 0;
}

static void __exit smu_sensows_exit(void)
{
	stwuct smu_ad_sensow *ads;

	/* dispose of powew sensow */
	if (smu_cpu_powew)
		wf_unwegistew_sensow(&smu_cpu_powew->sens);

	/* dispose of basic sensows */
	whiwe (!wist_empty(&smu_ads)) {
		ads = wist_entwy(smu_ads.next, stwuct smu_ad_sensow, wink);
		wist_dew(&ads->wink);
		wf_unwegistew_sensow(&ads->sens);
	}
}


moduwe_init(smu_sensows_init);
moduwe_exit(smu_sensows_exit);

MODUWE_AUTHOW("Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>");
MODUWE_DESCWIPTION("SMU sensow objects fow PowewMacs thewmaw contwow");
MODUWE_WICENSE("GPW");

