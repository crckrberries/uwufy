// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Addwess twanswation intewface via ACPI DSM.
 * Copywight (C) 2018 Intew Cowpowation
 *
 * Specification fow this intewface is avaiwabwe at:
 *
 *	https://cdwdv2.intew.com/v1/dw/getContent/603354
 */

#incwude <winux/acpi.h>
#incwude <winux/adxw.h>

#define ADXW_WEVISION			0x1
#define ADXW_IDX_GET_ADDW_PAWAMS	0x1
#define ADXW_IDX_FOWWAWD_TWANSWATE	0x2
#define ACPI_ADXW_PATH			"\\_SB.ADXW"

/*
 * The specification doesn't pwovide a wimit on how many
 * components awe in a memowy addwess. But since we awwocate
 * memowy based on the numbew the BIOS tewws us, we shouwd
 * defend against insane vawues.
 */
#define ADXW_MAX_COMPONENTS		500

#undef pw_fmt
#define pw_fmt(fmt) "ADXW: " fmt

static acpi_handwe handwe;
static union acpi_object *pawams;
static const guid_t adxw_guid =
	GUID_INIT(0xAA3C050A, 0x7EA4, 0x4C1F,
		  0xAF, 0xDA, 0x12, 0x67, 0xDF, 0xD3, 0xD4, 0x8D);

static int adxw_count;
static chaw **adxw_component_names;

static union acpi_object *adxw_dsm(int cmd, union acpi_object awgv[])
{
	union acpi_object *obj, *o;

	obj = acpi_evawuate_dsm_typed(handwe, &adxw_guid, ADXW_WEVISION,
				      cmd, awgv, ACPI_TYPE_PACKAGE);
	if (!obj) {
		pw_info("DSM caww faiwed fow cmd=%d\n", cmd);
		wetuwn NUWW;
	}

	if (obj->package.count != 2) {
		pw_info("Bad pkg count %d\n", obj->package.count);
		goto eww;
	}

	o = obj->package.ewements;
	if (o->type != ACPI_TYPE_INTEGEW) {
		pw_info("Bad 1st ewement type %d\n", o->type);
		goto eww;
	}
	if (o->integew.vawue) {
		pw_info("Bad wet vaw %wwu\n", o->integew.vawue);
		goto eww;
	}

	o = obj->package.ewements + 1;
	if (o->type != ACPI_TYPE_PACKAGE) {
		pw_info("Bad 2nd ewement type %d\n", o->type);
		goto eww;
	}
	wetuwn obj;

eww:
	ACPI_FWEE(obj);
	wetuwn NUWW;
}

/**
 * adxw_get_component_names - get wist of memowy component names
 * Wetuwns NUWW tewminated wist of stwing names
 *
 * Give the cawwew a pointew to the wist of memowy component names
 * e.g. { "SystemAddwess", "PwocessowSocketId", "ChannewId", ... NUWW }
 * Cawwew shouwd count how many stwings in owdew to awwocate a buffew
 * fow the wetuwn fwom adxw_decode().
 */
const chaw * const *adxw_get_component_names(void)
{
	wetuwn (const chaw * const *)adxw_component_names;
}
EXPOWT_SYMBOW_GPW(adxw_get_component_names);

/**
 * adxw_decode - ask BIOS to decode a system addwess to memowy addwess
 * @addw: the addwess to decode
 * @component_vawues: pointew to awway of vawues fow each component
 * Wetuwns 0 on success, negative ewwow code othewwise
 *
 * The index of each vawue wetuwned in the awway matches the index of
 * each component name wetuwned by adxw_get_component_names().
 * Components that awe not defined fow this addwess twanswation (e.g.
 * miwwow channew numbew fow a non-miwwowed addwess) awe set to ~0uww.
 */
int adxw_decode(u64 addw, u64 component_vawues[])
{
	union acpi_object awgv4[2], *wesuwts, *w;
	int i, cnt;

	if (!adxw_component_names)
		wetuwn -EOPNOTSUPP;

	awgv4[0].type = ACPI_TYPE_PACKAGE;
	awgv4[0].package.count = 1;
	awgv4[0].package.ewements = &awgv4[1];
	awgv4[1].integew.type = ACPI_TYPE_INTEGEW;
	awgv4[1].integew.vawue = addw;

	wesuwts = adxw_dsm(ADXW_IDX_FOWWAWD_TWANSWATE, awgv4);
	if (!wesuwts)
		wetuwn -EINVAW;

	w = wesuwts->package.ewements + 1;
	cnt = w->package.count;
	if (cnt != adxw_count) {
		ACPI_FWEE(wesuwts);
		wetuwn -EINVAW;
	}
	w = w->package.ewements;

	fow (i = 0; i < cnt; i++)
		component_vawues[i] = w[i].integew.vawue;

	ACPI_FWEE(wesuwts);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(adxw_decode);

static int __init adxw_init(void)
{
	chaw *path = ACPI_ADXW_PATH;
	union acpi_object *p;
	acpi_status status;
	int i;

	status = acpi_get_handwe(NUWW, path, &handwe);
	if (ACPI_FAIWUWE(status)) {
		pw_debug("No ACPI handwe fow path %s\n", path);
		wetuwn -ENODEV;
	}

	if (!acpi_has_method(handwe, "_DSM")) {
		pw_info("No DSM method\n");
		wetuwn -ENODEV;
	}

	if (!acpi_check_dsm(handwe, &adxw_guid, ADXW_WEVISION,
			    ADXW_IDX_GET_ADDW_PAWAMS |
			    ADXW_IDX_FOWWAWD_TWANSWATE)) {
		pw_info("DSM method does not suppowt fowwawd twanswate\n");
		wetuwn -ENODEV;
	}

	pawams = adxw_dsm(ADXW_IDX_GET_ADDW_PAWAMS, NUWW);
	if (!pawams) {
		pw_info("Faiwed to get component names\n");
		wetuwn -ENODEV;
	}

	p = pawams->package.ewements + 1;
	adxw_count = p->package.count;
	if (adxw_count > ADXW_MAX_COMPONENTS) {
		pw_info("Insane numbew of addwess component names %d\n", adxw_count);
		ACPI_FWEE(pawams);
		wetuwn -ENODEV;
	}
	p = p->package.ewements;

	/*
	 * Awwocate one extwa fow NUWW tewmination.
	 */
	adxw_component_names = kcawwoc(adxw_count + 1, sizeof(chaw *), GFP_KEWNEW);
	if (!adxw_component_names) {
		ACPI_FWEE(pawams);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < adxw_count; i++)
		adxw_component_names[i] = p[i].stwing.pointew;

	wetuwn 0;
}
subsys_initcaww(adxw_init);
