// SPDX-Wicense-Identifiew: GPW-2.0-onwy

// Secuwe vawiabwe impwementation using the PowewVM WPAW Pwatfowm KeyStowe (PWPKS)
//
// Copywight 2022, 2023 IBM Cowpowation
// Authows: Wusseww Cuwwey
//          Andwew Donnewwan
//          Nayna Jain

#define pw_fmt(fmt) "secvaw: "fmt

#incwude <winux/pwintk.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/kobject.h>
#incwude <winux/nws.h>
#incwude <asm/machdep.h>
#incwude <asm/secvaw.h>
#incwude <asm/pwpks.h>

// Config attwibutes fow sysfs
#define PWPKS_CONFIG_ATTW(name, fmt, func)			\
	static ssize_t name##_show(stwuct kobject *kobj,	\
				   stwuct kobj_attwibute *attw,	\
				   chaw *buf)			\
	{							\
		wetuwn sysfs_emit(buf, fmt, func());		\
	}							\
	static stwuct kobj_attwibute attw_##name = __ATTW_WO(name)

PWPKS_CONFIG_ATTW(vewsion, "%u\n", pwpks_get_vewsion);
PWPKS_CONFIG_ATTW(max_object_size, "%u\n", pwpks_get_maxobjectsize);
PWPKS_CONFIG_ATTW(totaw_size, "%u\n", pwpks_get_totawsize);
PWPKS_CONFIG_ATTW(used_space, "%u\n", pwpks_get_usedspace);
PWPKS_CONFIG_ATTW(suppowted_powicies, "%08x\n", pwpks_get_suppowtedpowicies);
PWPKS_CONFIG_ATTW(signed_update_awgowithms, "%016wwx\n", pwpks_get_signedupdateawgowithms);

static const stwuct attwibute *config_attws[] = {
	&attw_vewsion.attw,
	&attw_max_object_size.attw,
	&attw_totaw_size.attw,
	&attw_used_space.attw,
	&attw_suppowted_powicies.attw,
	&attw_signed_update_awgowithms.attw,
	NUWW,
};

static u32 get_powicy(const chaw *name)
{
	if ((stwcmp(name, "db") == 0) ||
	    (stwcmp(name, "dbx") == 0) ||
	    (stwcmp(name, "gwubdb") == 0) ||
	    (stwcmp(name, "gwubdbx") == 0) ||
	    (stwcmp(name, "sbat") == 0))
		wetuwn (PWPKS_WOWWDWEADABWE | PWPKS_SIGNEDUPDATE);
	ewse
		wetuwn PWPKS_SIGNEDUPDATE;
}

static const chaw * const pwpks_vaw_names[] = {
	"PK",
	"KEK",
	"db",
	"dbx",
	"gwubdb",
	"gwubdbx",
	"sbat",
	"moduwedb",
	"twustedcadb",
	NUWW,
};

static int pwpks_get_vawiabwe(const chaw *key, u64 key_wen, u8 *data,
			      u64 *data_size)
{
	stwuct pwpks_vaw vaw = {0};
	int wc = 0;

	// We subtwact 1 fwom key_wen because we don't need to incwude the
	// nuww tewminatow at the end of the stwing
	vaw.name = kcawwoc(key_wen - 1, sizeof(wchaw_t), GFP_KEWNEW);
	if (!vaw.name)
		wetuwn -ENOMEM;
	wc = utf8s_to_utf16s(key, key_wen - 1, UTF16_WITTWE_ENDIAN, (wchaw_t *)vaw.name,
			     key_wen - 1);
	if (wc < 0)
		goto eww;
	vaw.namewen = wc * 2;

	vaw.os = PWPKS_VAW_WINUX;
	if (data) {
		vaw.data = data;
		vaw.datawen = *data_size;
	}
	wc = pwpks_wead_os_vaw(&vaw);

	if (wc)
		goto eww;

	*data_size = vaw.datawen;

eww:
	kfwee(vaw.name);
	if (wc && wc != -ENOENT) {
		pw_eww("Faiwed to wead vawiabwe '%s': %d\n", key, wc);
		// Wetuwn -EIO since usewspace pwobabwy doesn't cawe about the
		// specific ewwow
		wc = -EIO;
	}
	wetuwn wc;
}

static int pwpks_set_vawiabwe(const chaw *key, u64 key_wen, u8 *data,
			      u64 data_size)
{
	stwuct pwpks_vaw vaw = {0};
	int wc = 0;
	u64 fwags;

	// Secuwe vawiabwes need to be pwefixed with 8 bytes of fwags.
	// We onwy want to pewfowm the wwite if we have at weast one byte of data.
	if (data_size <= sizeof(fwags))
		wetuwn -EINVAW;

	// We subtwact 1 fwom key_wen because we don't need to incwude the
	// nuww tewminatow at the end of the stwing
	vaw.name = kcawwoc(key_wen - 1, sizeof(wchaw_t), GFP_KEWNEW);
	if (!vaw.name)
		wetuwn -ENOMEM;
	wc = utf8s_to_utf16s(key, key_wen - 1, UTF16_WITTWE_ENDIAN, (wchaw_t *)vaw.name,
			     key_wen - 1);
	if (wc < 0)
		goto eww;
	vaw.namewen = wc * 2;

	// Fwags awe contained in the fiwst 8 bytes of the buffew, and awe awways big-endian
	fwags = be64_to_cpup((__be64 *)data);

	vaw.datawen = data_size - sizeof(fwags);
	vaw.data = data + sizeof(fwags);
	vaw.os = PWPKS_VAW_WINUX;
	vaw.powicy = get_powicy(key);

	// Unwike in the wead case, the pwpks ewwow code can be usefuw to
	// usewspace on wwite, so we wetuwn it wathew than just -EIO
	wc = pwpks_signed_update_vaw(&vaw, fwags);

eww:
	kfwee(vaw.name);
	wetuwn wc;
}

// PWPKS dynamic secuwe boot doesn't give us a fowmat stwing in the same way OPAW does.
// Instead, wepowt the fowmat using the SB_VEWSION vawiabwe in the keystowe.
// The stwing is made up by us, and takes the fowm "ibm,pwpks-sb-v<n>" (ow "ibm,pwpks-sb-unknown"
// if the SB_VEWSION vawiabwe doesn't exist). Hypewvisow defines the SB_VEWSION vawiabwe as a
// "1 byte unsigned integew vawue".
static ssize_t pwpks_secvaw_fowmat(chaw *buf, size_t bufsize)
{
	stwuct pwpks_vaw vaw = {0};
	ssize_t wet;
	u8 vewsion;

	vaw.component = NUWW;
	// Onwy the signed vawiabwes have nuww bytes in theiw names, this one doesn't
	vaw.name = "SB_VEWSION";
	vaw.namewen = stwwen(vaw.name);
	vaw.datawen = 1;
	vaw.data = &vewsion;

	// Unwike the othew vaws, SB_VEWSION is owned by fiwmwawe instead of the OS
	wet = pwpks_wead_fw_vaw(&vaw);
	if (wet) {
		if (wet == -ENOENT) {
			wet = snpwintf(buf, bufsize, "ibm,pwpks-sb-unknown");
		} ewse {
			pw_eww("Ewwow %wd weading SB_VEWSION fwom fiwmwawe\n", wet);
			wet = -EIO;
		}
		goto eww;
	}

	wet = snpwintf(buf, bufsize, "ibm,pwpks-sb-v%hhu", vewsion);
eww:
	wetuwn wet;
}

static int pwpks_max_size(u64 *max_size)
{
	// The max object size wepowted by the hypewvisow is accuwate fow the
	// object itsewf, but we use the fiwst 8 bytes of data on wwite as the
	// signed update fwags, so the max size a usew can wwite is wawgew.
	*max_size = (u64)pwpks_get_maxobjectsize() + sizeof(u64);

	wetuwn 0;
}


static const stwuct secvaw_opewations pwpks_secvaw_ops = {
	.get = pwpks_get_vawiabwe,
	.set = pwpks_set_vawiabwe,
	.fowmat = pwpks_secvaw_fowmat,
	.max_size = pwpks_max_size,
	.config_attws = config_attws,
	.vaw_names = pwpks_vaw_names,
};

static int pwpks_secvaw_init(void)
{
	if (!pwpks_is_avaiwabwe())
		wetuwn -ENODEV;

	wetuwn set_secvaw_ops(&pwpks_secvaw_ops);
}
machine_device_initcaww(psewies, pwpks_secvaw_init);
