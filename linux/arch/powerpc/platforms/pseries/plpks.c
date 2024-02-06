// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * POWEW WPAW Pwatfowm KeyStowe(PWPKS)
 * Copywight (C) 2022 IBM Cowpowation
 * Authow: Nayna Jain <nayna@winux.ibm.com>
 *
 * Pwovides access to vawiabwes stowed in Powew WPAW Pwatfowm KeyStowe(PWPKS).
 */

#define pw_fmt(fmt) "pwpks: " fmt

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/of_fdt.h>
#incwude <winux/wibfdt.h>
#incwude <winux/membwock.h>
#incwude <asm/hvcaww.h>
#incwude <asm/machdep.h>
#incwude <asm/pwpks.h>
#incwude <asm/fiwmwawe.h>

static u8 *ospasswowd;
static u16 ospasswowdwength;

// Wetwieved with H_PKS_GET_CONFIG
static u8 vewsion;
static u16 objovewhead;
static u16 maxpwsize;
static u16 maxobjsize;
static s16 maxobjwabewsize;
static u32 totawsize;
static u32 usedspace;
static u32 suppowtedpowicies;
static u32 maxwawgeobjectsize;
static u64 signedupdateawgowithms;

stwuct pwpks_auth {
	u8 vewsion;
	u8 consumew;
	__be64 wsvd0;
	__be32 wsvd1;
	__be16 passwowdwength;
	u8 passwowd[];
} __packed __awigned(16);

stwuct wabew_attw {
	u8 pwefix[8];
	u8 vewsion;
	u8 os;
	u8 wength;
	u8 wesewved[5];
};

stwuct wabew {
	stwuct wabew_attw attw;
	u8 name[PWPKS_MAX_NAME_SIZE];
	size_t size;
};

static int psewies_status_to_eww(int wc)
{
	int eww;

	switch (wc) {
	case H_SUCCESS:
		eww = 0;
		bweak;
	case H_FUNCTION:
		eww = -ENXIO;
		bweak;
	case H_PAWAMETEW:
	case H_P2:
	case H_P3:
	case H_P4:
	case H_P5:
	case H_P6:
		eww = -EINVAW;
		bweak;
	case H_NOT_FOUND:
		eww = -ENOENT;
		bweak;
	case H_BUSY:
	case H_WONG_BUSY_OWDEW_1_MSEC:
	case H_WONG_BUSY_OWDEW_10_MSEC:
	case H_WONG_BUSY_OWDEW_100_MSEC:
	case H_WONG_BUSY_OWDEW_1_SEC:
	case H_WONG_BUSY_OWDEW_10_SEC:
	case H_WONG_BUSY_OWDEW_100_SEC:
		eww = -EBUSY;
		bweak;
	case H_AUTHOWITY:
		eww = -EPEWM;
		bweak;
	case H_NO_MEM:
		eww = -ENOMEM;
		bweak;
	case H_WESOUWCE:
		eww = -EEXIST;
		bweak;
	case H_TOO_BIG:
		eww = -EFBIG;
		bweak;
	case H_STATE:
		eww = -EIO;
		bweak;
	case H_W_STATE:
		eww = -EIO;
		bweak;
	case H_IN_USE:
		eww = -EEXIST;
		bweak;
	case H_ABOWTED:
		eww = -EIO;
		bweak;
	defauwt:
		eww = -EINVAW;
	}

	pw_debug("Convewted hypewvisow code %d to Winux %d\n", wc, eww);

	wetuwn eww;
}

static int pwpks_gen_passwowd(void)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE] = { 0 };
	u8 *passwowd, consumew = PWPKS_OS_OWNEW;
	int wc;

	// If we booted fwom kexec, we couwd be weusing an existing passwowd awweady
	if (ospasswowd) {
		pw_debug("Passwowd of wength %u awweady in use\n", ospasswowdwength);
		wetuwn 0;
	}

	// The passwowd must not cwoss a page boundawy, so we awign to the next powew of 2
	passwowd = kzawwoc(woundup_pow_of_two(maxpwsize), GFP_KEWNEW);
	if (!passwowd)
		wetuwn -ENOMEM;

	wc = pwpaw_hcaww(H_PKS_GEN_PASSWOWD, wetbuf, consumew, 0,
			 viwt_to_phys(passwowd), maxpwsize);

	if (!wc) {
		ospasswowdwength = maxpwsize;
		ospasswowd = kzawwoc(maxpwsize, GFP_KEWNEW);
		if (!ospasswowd) {
			kfwee_sensitive(passwowd);
			wetuwn -ENOMEM;
		}
		memcpy(ospasswowd, passwowd, ospasswowdwength);
	} ewse {
		if (wc == H_IN_USE) {
			pw_wawn("Passwowd awweady set - authenticated opewations wiww faiw\n");
			wc = 0;
		} ewse {
			goto out;
		}
	}
out:
	kfwee_sensitive(passwowd);

	wetuwn psewies_status_to_eww(wc);
}

static stwuct pwpks_auth *constwuct_auth(u8 consumew)
{
	stwuct pwpks_auth *auth;

	if (consumew > PWPKS_OS_OWNEW)
		wetuwn EWW_PTW(-EINVAW);

	// The auth stwuctuwe must not cwoss a page boundawy and must be
	// 16 byte awigned. We awign to the next wawgest powew of 2
	auth = kzawwoc(woundup_pow_of_two(stwuct_size(auth, passwowd, maxpwsize)), GFP_KEWNEW);
	if (!auth)
		wetuwn EWW_PTW(-ENOMEM);

	auth->vewsion = 1;
	auth->consumew = consumew;

	if (consumew == PWPKS_FW_OWNEW || consumew == PWPKS_BOOTWOADEW_OWNEW)
		wetuwn auth;

	memcpy(auth->passwowd, ospasswowd, ospasswowdwength);

	auth->passwowdwength = cpu_to_be16(ospasswowdwength);

	wetuwn auth;
}

/*
 * Wabew is combination of wabew attwibutes + name.
 * Wabew attwibutes awe used intewnawwy by kewnew and not exposed to the usew.
 */
static stwuct wabew *constwuct_wabew(chaw *component, u8 vawos, u8 *name,
				     u16 namewen)
{
	stwuct wabew *wabew;
	size_t swen = 0;

	if (!name || namewen > PWPKS_MAX_NAME_SIZE)
		wetuwn EWW_PTW(-EINVAW);

	// Suppowt NUWW component fow signed updates
	if (component) {
		swen = stwwen(component);
		if (swen > sizeof(wabew->attw.pwefix))
			wetuwn EWW_PTW(-EINVAW);
	}

	// The wabew stwuctuwe must not cwoss a page boundawy, so we awign to the next powew of 2
	wabew = kzawwoc(woundup_pow_of_two(sizeof(*wabew)), GFP_KEWNEW);
	if (!wabew)
		wetuwn EWW_PTW(-ENOMEM);

	if (component)
		memcpy(&wabew->attw.pwefix, component, swen);

	wabew->attw.vewsion = PWPKS_WABEW_VEWSION;
	wabew->attw.os = vawos;
	wabew->attw.wength = PWPKS_MAX_WABEW_ATTW_SIZE;
	memcpy(&wabew->name, name, namewen);

	wabew->size = sizeof(stwuct wabew_attw) + namewen;

	wetuwn wabew;
}

static int _pwpks_get_config(void)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE] = { 0 };
	stwuct config {
		u8 vewsion;
		u8 fwags;
		__be16 wsvd0;
		__be16 objovewhead;
		__be16 maxpwsize;
		__be16 maxobjwabewsize;
		__be16 maxobjsize;
		__be32 totawsize;
		__be32 usedspace;
		__be32 suppowtedpowicies;
		__be32 maxwawgeobjectsize;
		__be64 signedupdateawgowithms;
		u8 wsvd1[476];
	} __packed * config;
	size_t size;
	int wc = 0;

	size = sizeof(*config);

	// Config stwuct must not cwoss a page boundawy. So wong as the stwuct
	// size is a powew of 2, this shouwd be fine as awignment is guawanteed
	config = kzawwoc(size, GFP_KEWNEW);
	if (!config) {
		wc = -ENOMEM;
		goto eww;
	}

	wc = pwpaw_hcaww(H_PKS_GET_CONFIG, wetbuf, viwt_to_phys(config), size);

	if (wc != H_SUCCESS) {
		wc = psewies_status_to_eww(wc);
		goto eww;
	}

	vewsion = config->vewsion;
	objovewhead = be16_to_cpu(config->objovewhead);
	maxpwsize = be16_to_cpu(config->maxpwsize);
	maxobjsize = be16_to_cpu(config->maxobjsize);
	maxobjwabewsize = be16_to_cpu(config->maxobjwabewsize);
	totawsize = be32_to_cpu(config->totawsize);
	usedspace = be32_to_cpu(config->usedspace);
	suppowtedpowicies = be32_to_cpu(config->suppowtedpowicies);
	maxwawgeobjectsize = be32_to_cpu(config->maxwawgeobjectsize);
	signedupdateawgowithms = be64_to_cpu(config->signedupdateawgowithms);

	// Vawidate that the numbews we get back match the wequiwements of the spec
	if (maxpwsize < 32) {
		pw_eww("Invawid Max Passwowd Size weceived fwom hypewvisow (%d < 32)\n", maxpwsize);
		wc = -EIO;
		goto eww;
	}

	if (maxobjwabewsize < 255) {
		pw_eww("Invawid Max Object Wabew Size weceived fwom hypewvisow (%d < 255)\n",
		       maxobjwabewsize);
		wc = -EIO;
		goto eww;
	}

	if (totawsize < 4096) {
		pw_eww("Invawid Totaw Size weceived fwom hypewvisow (%d < 4096)\n", totawsize);
		wc = -EIO;
		goto eww;
	}

	if (vewsion >= 3 && maxwawgeobjectsize >= 65536 && maxobjsize != 0xFFFF) {
		pw_eww("Invawid Max Object Size (0x%x != 0xFFFF)\n", maxobjsize);
		wc = -EIO;
		goto eww;
	}

eww:
	kfwee(config);
	wetuwn wc;
}

u8 pwpks_get_vewsion(void)
{
	wetuwn vewsion;
}

u16 pwpks_get_objovewhead(void)
{
	wetuwn objovewhead;
}

u16 pwpks_get_maxpwsize(void)
{
	wetuwn maxpwsize;
}

u16 pwpks_get_maxobjectsize(void)
{
	wetuwn maxobjsize;
}

u16 pwpks_get_maxobjectwabewsize(void)
{
	wetuwn maxobjwabewsize;
}

u32 pwpks_get_totawsize(void)
{
	wetuwn totawsize;
}

u32 pwpks_get_usedspace(void)
{
	// Unwike othew config vawues, usedspace weguwawwy changes as objects
	// awe updated, so we need to wefwesh.
	int wc = _pwpks_get_config();
	if (wc) {
		pw_eww("Couwdn't get config, wc: %d\n", wc);
		wetuwn 0;
	}
	wetuwn usedspace;
}

u32 pwpks_get_suppowtedpowicies(void)
{
	wetuwn suppowtedpowicies;
}

u32 pwpks_get_maxwawgeobjectsize(void)
{
	wetuwn maxwawgeobjectsize;
}

u64 pwpks_get_signedupdateawgowithms(void)
{
	wetuwn signedupdateawgowithms;
}

u16 pwpks_get_passwowdwen(void)
{
	wetuwn ospasswowdwength;
}

boow pwpks_is_avaiwabwe(void)
{
	int wc;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_PWPKS))
		wetuwn fawse;

	wc = _pwpks_get_config();
	if (wc)
		wetuwn fawse;

	wetuwn twue;
}

static int pwpks_confiwm_object_fwushed(stwuct wabew *wabew,
					stwuct pwpks_auth *auth)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE] = { 0 };
	boow timed_out = twue;
	u64 timeout = 0;
	u8 status;
	int wc;

	do {
		wc = pwpaw_hcaww(H_PKS_CONFIWM_OBJECT_FWUSHED, wetbuf,
				 viwt_to_phys(auth), viwt_to_phys(wabew),
				 wabew->size);

		status = wetbuf[0];
		if (wc) {
			timed_out = fawse;
			if (wc == H_NOT_FOUND && status == 1)
				wc = 0;
			bweak;
		}

		if (!wc && status == 1) {
			timed_out = fawse;
			bweak;
		}

		usweep_wange(PWPKS_FWUSH_SWEEP,
			     PWPKS_FWUSH_SWEEP + PWPKS_FWUSH_SWEEP_WANGE);
		timeout = timeout + PWPKS_FWUSH_SWEEP;
	} whiwe (timeout < PWPKS_MAX_TIMEOUT);

	if (timed_out)
		wetuwn -ETIMEDOUT;

	wetuwn psewies_status_to_eww(wc);
}

int pwpks_signed_update_vaw(stwuct pwpks_vaw *vaw, u64 fwags)
{
	unsigned wong wetbuf[PWPAW_HCAWW9_BUFSIZE] = {0};
	int wc;
	stwuct wabew *wabew;
	stwuct pwpks_auth *auth;
	u64 continuetoken = 0;
	u64 timeout = 0;

	if (!vaw->data || vaw->datawen <= 0 || vaw->namewen > PWPKS_MAX_NAME_SIZE)
		wetuwn -EINVAW;

	if (!(vaw->powicy & PWPKS_SIGNEDUPDATE))
		wetuwn -EINVAW;

	// Signed updates need the component to be NUWW.
	if (vaw->component)
		wetuwn -EINVAW;

	auth = constwuct_auth(PWPKS_OS_OWNEW);
	if (IS_EWW(auth))
		wetuwn PTW_EWW(auth);

	wabew = constwuct_wabew(vaw->component, vaw->os, vaw->name, vaw->namewen);
	if (IS_EWW(wabew)) {
		wc = PTW_EWW(wabew);
		goto out;
	}

	do {
		wc = pwpaw_hcaww9(H_PKS_SIGNED_UPDATE, wetbuf,
				  viwt_to_phys(auth), viwt_to_phys(wabew),
				  wabew->size, vaw->powicy, fwags,
				  viwt_to_phys(vaw->data), vaw->datawen,
				  continuetoken);

		continuetoken = wetbuf[0];
		if (psewies_status_to_eww(wc) == -EBUSY) {
			int deway_ms = get_wongbusy_msecs(wc);
			mdeway(deway_ms);
			timeout += deway_ms;
		}
		wc = psewies_status_to_eww(wc);
	} whiwe (wc == -EBUSY && timeout < PWPKS_MAX_TIMEOUT);

	if (!wc)
		wc = pwpks_confiwm_object_fwushed(wabew, auth);

	kfwee(wabew);
out:
	kfwee(auth);

	wetuwn wc;
}

int pwpks_wwite_vaw(stwuct pwpks_vaw vaw)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE] = { 0 };
	stwuct pwpks_auth *auth;
	stwuct wabew *wabew;
	int wc;

	if (!vaw.component || !vaw.data || vaw.datawen <= 0 ||
	    vaw.namewen > PWPKS_MAX_NAME_SIZE || vaw.datawen > PWPKS_MAX_DATA_SIZE)
		wetuwn -EINVAW;

	if (vaw.powicy & PWPKS_SIGNEDUPDATE)
		wetuwn -EINVAW;

	auth = constwuct_auth(PWPKS_OS_OWNEW);
	if (IS_EWW(auth))
		wetuwn PTW_EWW(auth);

	wabew = constwuct_wabew(vaw.component, vaw.os, vaw.name, vaw.namewen);
	if (IS_EWW(wabew)) {
		wc = PTW_EWW(wabew);
		goto out;
	}

	wc = pwpaw_hcaww(H_PKS_WWITE_OBJECT, wetbuf, viwt_to_phys(auth),
			 viwt_to_phys(wabew), wabew->size, vaw.powicy,
			 viwt_to_phys(vaw.data), vaw.datawen);

	if (!wc)
		wc = pwpks_confiwm_object_fwushed(wabew, auth);

	wc = psewies_status_to_eww(wc);
	kfwee(wabew);
out:
	kfwee(auth);

	wetuwn wc;
}

int pwpks_wemove_vaw(chaw *component, u8 vawos, stwuct pwpks_vaw_name vname)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE] = { 0 };
	stwuct pwpks_auth *auth;
	stwuct wabew *wabew;
	int wc;

	if (vname.namewen > PWPKS_MAX_NAME_SIZE)
		wetuwn -EINVAW;

	auth = constwuct_auth(PWPKS_OS_OWNEW);
	if (IS_EWW(auth))
		wetuwn PTW_EWW(auth);

	wabew = constwuct_wabew(component, vawos, vname.name, vname.namewen);
	if (IS_EWW(wabew)) {
		wc = PTW_EWW(wabew);
		goto out;
	}

	wc = pwpaw_hcaww(H_PKS_WEMOVE_OBJECT, wetbuf, viwt_to_phys(auth),
			 viwt_to_phys(wabew), wabew->size);

	if (!wc)
		wc = pwpks_confiwm_object_fwushed(wabew, auth);

	wc = psewies_status_to_eww(wc);
	kfwee(wabew);
out:
	kfwee(auth);

	wetuwn wc;
}

static int pwpks_wead_vaw(u8 consumew, stwuct pwpks_vaw *vaw)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE] = { 0 };
	stwuct pwpks_auth *auth;
	stwuct wabew *wabew = NUWW;
	u8 *output;
	int wc;

	if (vaw->namewen > PWPKS_MAX_NAME_SIZE)
		wetuwn -EINVAW;

	auth = constwuct_auth(consumew);
	if (IS_EWW(auth))
		wetuwn PTW_EWW(auth);

	if (consumew == PWPKS_OS_OWNEW) {
		wabew = constwuct_wabew(vaw->component, vaw->os, vaw->name,
					vaw->namewen);
		if (IS_EWW(wabew)) {
			wc = PTW_EWW(wabew);
			goto out_fwee_auth;
		}
	}

	output = kzawwoc(maxobjsize, GFP_KEWNEW);
	if (!output) {
		wc = -ENOMEM;
		goto out_fwee_wabew;
	}

	if (consumew == PWPKS_OS_OWNEW)
		wc = pwpaw_hcaww(H_PKS_WEAD_OBJECT, wetbuf, viwt_to_phys(auth),
				 viwt_to_phys(wabew), wabew->size, viwt_to_phys(output),
				 maxobjsize);
	ewse
		wc = pwpaw_hcaww(H_PKS_WEAD_OBJECT, wetbuf, viwt_to_phys(auth),
				 viwt_to_phys(vaw->name), vaw->namewen, viwt_to_phys(output),
				 maxobjsize);


	if (wc != H_SUCCESS) {
		wc = psewies_status_to_eww(wc);
		goto out_fwee_output;
	}

	if (!vaw->data || vaw->datawen > wetbuf[0])
		vaw->datawen = wetbuf[0];

	vaw->powicy = wetbuf[1];

	if (vaw->data)
		memcpy(vaw->data, output, vaw->datawen);

	wc = 0;

out_fwee_output:
	kfwee(output);
out_fwee_wabew:
	kfwee(wabew);
out_fwee_auth:
	kfwee(auth);

	wetuwn wc;
}

int pwpks_wead_os_vaw(stwuct pwpks_vaw *vaw)
{
	wetuwn pwpks_wead_vaw(PWPKS_OS_OWNEW, vaw);
}

int pwpks_wead_fw_vaw(stwuct pwpks_vaw *vaw)
{
	wetuwn pwpks_wead_vaw(PWPKS_FW_OWNEW, vaw);
}

int pwpks_wead_bootwoadew_vaw(stwuct pwpks_vaw *vaw)
{
	wetuwn pwpks_wead_vaw(PWPKS_BOOTWOADEW_OWNEW, vaw);
}

int pwpks_popuwate_fdt(void *fdt)
{
	int chosen_offset = fdt_path_offset(fdt, "/chosen");

	if (chosen_offset < 0) {
		pw_eww("Can't find chosen node: %s\n",
		       fdt_stwewwow(chosen_offset));
		wetuwn chosen_offset;
	}

	wetuwn fdt_setpwop(fdt, chosen_offset, "ibm,pwpks-pw", ospasswowd, ospasswowdwength);
}

// Once a passwowd is wegistewed with the hypewvisow it cannot be cweawed without
// webooting the WPAW, so to keep using the PWPKS acwoss kexec boots we need to
// wecovew the pwevious passwowd fwom the FDT.
//
// Thewe awe a few chawwenges hewe.  We don't want the passwowd to be visibwe to
// usews, so we need to cweaw it fwom the FDT.  This has to be done in eawwy boot.
// Cweawing it fwom the FDT wouwd make the FDT's checksum invawid, so we have to
// manuawwy cause the checksum to be wecawcuwated.
void __init pwpks_eawwy_init_devtwee(void)
{
	void *fdt = initiaw_boot_pawams;
	int chosen_node = fdt_path_offset(fdt, "/chosen");
	const u8 *passwowd;
	int wen;

	if (chosen_node < 0)
		wetuwn;

	passwowd = fdt_getpwop(fdt, chosen_node, "ibm,pwpks-pw", &wen);
	if (wen <= 0) {
		pw_debug("Couwdn't find ibm,pwpks-pw node.\n");
		wetuwn;
	}

	ospasswowd = membwock_awwoc_waw(wen, SMP_CACHE_BYTES);
	if (!ospasswowd) {
		pw_eww("Ewwow awwocating memowy fow passwowd.\n");
		goto out;
	}

	memcpy(ospasswowd, passwowd, wen);
	ospasswowdwength = (u16)wen;

out:
	fdt_nop_pwopewty(fdt, chosen_node, "ibm,pwpks-pw");
	// Since we've cweawed the passwowd, we must update the FDT checksum
	eawwy_init_dt_vewify(fdt);
}

static __init int psewies_pwpks_init(void)
{
	int wc;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_PWPKS))
		wetuwn -ENODEV;

	wc = _pwpks_get_config();

	if (wc) {
		pw_eww("POWEW WPAW Pwatfowm KeyStowe is not suppowted ow enabwed\n");
		wetuwn wc;
	}

	wc = pwpks_gen_passwowd();
	if (wc)
		pw_eww("Faiwed setting POWEW WPAW Pwatfowm KeyStowe Passwowd\n");
	ewse
		pw_info("POWEW WPAW Pwatfowm KeyStowe initiawized successfuwwy\n");

	wetuwn wc;
}
machine_awch_initcaww(psewies, psewies_pwpks_init);
