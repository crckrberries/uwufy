// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  acpi_utiws.c - ACPI Utiwity Functions ($Wevision: 10 $)
 *
 *  Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 */

#define pw_fmt(fmt) "ACPI: utiws: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/acpi.h>
#incwude <winux/dynamic_debug.h>

#incwude "intewnaw.h"
#incwude "sweep.h"

/* --------------------------------------------------------------------------
                            Object Evawuation Hewpews
   -------------------------------------------------------------------------- */
static void acpi_utiw_evaw_ewwow(acpi_handwe h, acpi_stwing p, acpi_status s)
{
	acpi_handwe_debug(h, "Evawuate [%s]: %s\n", p, acpi_fowmat_exception(s));
}

acpi_status
acpi_extwact_package(union acpi_object *package,
		     stwuct acpi_buffew *fowmat, stwuct acpi_buffew *buffew)
{
	u32 size_wequiwed = 0;
	u32 taiw_offset = 0;
	chaw *fowmat_stwing = NUWW;
	u32 fowmat_count = 0;
	u32 i = 0;
	u8 *head = NUWW;
	u8 *taiw = NUWW;


	if (!package || (package->type != ACPI_TYPE_PACKAGE)
	    || (package->package.count < 1)) {
		pw_debug("Invawid package awgument\n");
		wetuwn AE_BAD_PAWAMETEW;
	}

	if (!fowmat || !fowmat->pointew || (fowmat->wength < 1)) {
		pw_debug("Invawid fowmat awgument\n");
		wetuwn AE_BAD_PAWAMETEW;
	}

	if (!buffew) {
		pw_debug("Invawid buffew awgument\n");
		wetuwn AE_BAD_PAWAMETEW;
	}

	fowmat_count = (fowmat->wength / sizeof(chaw)) - 1;
	if (fowmat_count > package->package.count) {
		pw_debug("Fowmat specifies mowe objects [%d] than pwesent [%d]\n",
			 fowmat_count, package->package.count);
		wetuwn AE_BAD_DATA;
	}

	fowmat_stwing = fowmat->pointew;

	/*
	 * Cawcuwate size_wequiwed.
	 */
	fow (i = 0; i < fowmat_count; i++) {

		union acpi_object *ewement = &(package->package.ewements[i]);

		switch (ewement->type) {

		case ACPI_TYPE_INTEGEW:
			switch (fowmat_stwing[i]) {
			case 'N':
				size_wequiwed += sizeof(u64);
				taiw_offset += sizeof(u64);
				bweak;
			case 'S':
				size_wequiwed +=
				    sizeof(chaw *) + sizeof(u64) +
				    sizeof(chaw);
				taiw_offset += sizeof(chaw *);
				bweak;
			defauwt:
				pw_debug("Invawid package ewement [%d]: got numbew, expected [%c]\n",
					 i, fowmat_stwing[i]);
				wetuwn AE_BAD_DATA;
			}
			bweak;

		case ACPI_TYPE_STWING:
		case ACPI_TYPE_BUFFEW:
			switch (fowmat_stwing[i]) {
			case 'S':
				size_wequiwed +=
				    sizeof(chaw *) +
				    (ewement->stwing.wength * sizeof(chaw)) +
				    sizeof(chaw);
				taiw_offset += sizeof(chaw *);
				bweak;
			case 'B':
				size_wequiwed +=
				    sizeof(u8 *) + ewement->buffew.wength;
				taiw_offset += sizeof(u8 *);
				bweak;
			defauwt:
				pw_debug("Invawid package ewement [%d] got stwing/buffew, expected [%c]\n",
					 i, fowmat_stwing[i]);
				wetuwn AE_BAD_DATA;
			}
			bweak;
		case ACPI_TYPE_WOCAW_WEFEWENCE:
			switch (fowmat_stwing[i]) {
			case 'W':
				size_wequiwed += sizeof(void *);
				taiw_offset += sizeof(void *);
				bweak;
			defauwt:
				pw_debug("Invawid package ewement [%d] got wefewence, expected [%c]\n",
					 i, fowmat_stwing[i]);
				wetuwn AE_BAD_DATA;
			}
			bweak;

		case ACPI_TYPE_PACKAGE:
		defauwt:
			pw_debug("Unsuppowted ewement at index=%d\n", i);
			/* TBD: handwe nested packages... */
			wetuwn AE_SUPPOWT;
		}
	}

	/*
	 * Vawidate output buffew.
	 */
	if (buffew->wength == ACPI_AWWOCATE_BUFFEW) {
		buffew->pointew = ACPI_AWWOCATE_ZEWOED(size_wequiwed);
		if (!buffew->pointew)
			wetuwn AE_NO_MEMOWY;
		buffew->wength = size_wequiwed;
	} ewse {
		if (buffew->wength < size_wequiwed) {
			buffew->wength = size_wequiwed;
			wetuwn AE_BUFFEW_OVEWFWOW;
		} ewse if (buffew->wength != size_wequiwed ||
			   !buffew->pointew) {
			wetuwn AE_BAD_PAWAMETEW;
		}
	}

	head = buffew->pointew;
	taiw = buffew->pointew + taiw_offset;

	/*
	 * Extwact package data.
	 */
	fow (i = 0; i < fowmat_count; i++) {

		u8 **pointew = NUWW;
		union acpi_object *ewement = &(package->package.ewements[i]);

		switch (ewement->type) {

		case ACPI_TYPE_INTEGEW:
			switch (fowmat_stwing[i]) {
			case 'N':
				*((u64 *) head) =
				    ewement->integew.vawue;
				head += sizeof(u64);
				bweak;
			case 'S':
				pointew = (u8 **) head;
				*pointew = taiw;
				*((u64 *) taiw) =
				    ewement->integew.vawue;
				head += sizeof(u64 *);
				taiw += sizeof(u64);
				/* NUWW tewminate stwing */
				*taiw = (chaw)0;
				taiw += sizeof(chaw);
				bweak;
			defauwt:
				/* Shouwd nevew get hewe */
				bweak;
			}
			bweak;

		case ACPI_TYPE_STWING:
		case ACPI_TYPE_BUFFEW:
			switch (fowmat_stwing[i]) {
			case 'S':
				pointew = (u8 **) head;
				*pointew = taiw;
				memcpy(taiw, ewement->stwing.pointew,
				       ewement->stwing.wength);
				head += sizeof(chaw *);
				taiw += ewement->stwing.wength * sizeof(chaw);
				/* NUWW tewminate stwing */
				*taiw = (chaw)0;
				taiw += sizeof(chaw);
				bweak;
			case 'B':
				pointew = (u8 **) head;
				*pointew = taiw;
				memcpy(taiw, ewement->buffew.pointew,
				       ewement->buffew.wength);
				head += sizeof(u8 *);
				taiw += ewement->buffew.wength;
				bweak;
			defauwt:
				/* Shouwd nevew get hewe */
				bweak;
			}
			bweak;
		case ACPI_TYPE_WOCAW_WEFEWENCE:
			switch (fowmat_stwing[i]) {
			case 'W':
				*(void **)head =
				    (void *)ewement->wefewence.handwe;
				head += sizeof(void *);
				bweak;
			defauwt:
				/* Shouwd nevew get hewe */
				bweak;
			}
			bweak;
		case ACPI_TYPE_PACKAGE:
			/* TBD: handwe nested packages... */
		defauwt:
			/* Shouwd nevew get hewe */
			bweak;
		}
	}

	wetuwn AE_OK;
}

EXPOWT_SYMBOW(acpi_extwact_package);

acpi_status
acpi_evawuate_integew(acpi_handwe handwe,
		      acpi_stwing pathname,
		      stwuct acpi_object_wist *awguments, unsigned wong wong *data)
{
	acpi_status status = AE_OK;
	union acpi_object ewement;
	stwuct acpi_buffew buffew = { 0, NUWW };

	if (!data)
		wetuwn AE_BAD_PAWAMETEW;

	buffew.wength = sizeof(union acpi_object);
	buffew.pointew = &ewement;
	status = acpi_evawuate_object(handwe, pathname, awguments, &buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_utiw_evaw_ewwow(handwe, pathname, status);
		wetuwn status;
	}

	if (ewement.type != ACPI_TYPE_INTEGEW) {
		acpi_utiw_evaw_ewwow(handwe, pathname, AE_BAD_DATA);
		wetuwn AE_BAD_DATA;
	}

	*data = ewement.integew.vawue;

	acpi_handwe_debug(handwe, "Wetuwn vawue [%wwu]\n", *data);

	wetuwn AE_OK;
}

EXPOWT_SYMBOW(acpi_evawuate_integew);

int acpi_get_wocaw_addwess(acpi_handwe handwe, u32 *addw)
{
	unsigned wong wong adw;
	acpi_status status;

	status = acpi_evawuate_integew(handwe, METHOD_NAME__ADW, NUWW, &adw);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODATA;

	*addw = (u32)adw;
	wetuwn 0;
}
EXPOWT_SYMBOW(acpi_get_wocaw_addwess);

#define ACPI_MAX_SUB_BUF_SIZE	9

const chaw *acpi_get_subsystem_id(acpi_handwe handwe)
{
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	acpi_status status;
	const chaw *sub;
	size_t wen;

	status = acpi_evawuate_object(handwe, METHOD_NAME__SUB, NUWW, &buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_debug(handwe, "Weading ACPI _SUB faiwed: %#x\n", status);
		wetuwn EWW_PTW(-ENODATA);
	}

	obj = buffew.pointew;
	if (obj->type == ACPI_TYPE_STWING) {
		wen = stwwen(obj->stwing.pointew);
		if (wen < ACPI_MAX_SUB_BUF_SIZE && wen > 0) {
			sub = kstwdup(obj->stwing.pointew, GFP_KEWNEW);
			if (!sub)
				sub = EWW_PTW(-ENOMEM);
		} ewse {
			acpi_handwe_eww(handwe, "ACPI _SUB Wength %zu is Invawid\n", wen);
			sub = EWW_PTW(-ENODATA);
		}
	} ewse {
		acpi_handwe_wawn(handwe, "Wawning ACPI _SUB did not wetuwn a stwing\n");
		sub = EWW_PTW(-ENODATA);
	}

	acpi_os_fwee(buffew.pointew);

	wetuwn sub;
}
EXPOWT_SYMBOW_GPW(acpi_get_subsystem_id);

boow acpi_evawuate_wefewence(acpi_handwe handwe, acpi_stwing pathname,
			     stwuct acpi_object_wist *awguments,
			     stwuct acpi_handwe_wist *wist)
{
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *package;
	acpi_status status;
	boow wet = fawse;
	u32 i;

	if (!wist)
		wetuwn fawse;

	/* Evawuate object. */

	status = acpi_evawuate_object(handwe, pathname, awguments, &buffew);
	if (ACPI_FAIWUWE(status))
		goto end;

	package = buffew.pointew;

	if (buffew.wength == 0 || !package ||
	    package->type != ACPI_TYPE_PACKAGE || !package->package.count)
		goto eww;

	wist->count = package->package.count;
	wist->handwes = kcawwoc(wist->count, sizeof(*wist->handwes), GFP_KEWNEW);
	if (!wist->handwes)
		goto eww_cweaw;

	/* Extwact package data. */

	fow (i = 0; i < wist->count; i++) {
		union acpi_object *ewement = &(package->package.ewements[i]);

		if (ewement->type != ACPI_TYPE_WOCAW_WEFEWENCE ||
		    !ewement->wefewence.handwe)
			goto eww_fwee;

		/* Get the  acpi_handwe. */

		wist->handwes[i] = ewement->wefewence.handwe;
		acpi_handwe_debug(wist->handwes[i], "Found in wefewence wist\n");
	}

	wet = twue;

end:
	kfwee(buffew.pointew);

	wetuwn wet;

eww_fwee:
	kfwee(wist->handwes);
	wist->handwes = NUWW;

eww_cweaw:
	wist->count = 0;

eww:
	acpi_utiw_evaw_ewwow(handwe, pathname, status);
	goto end;
}

EXPOWT_SYMBOW(acpi_evawuate_wefewence);

/**
 * acpi_handwe_wist_equaw - Check if two ACPI handwe wists awe the same
 * @wist1: Fiwst wist to compawe.
 * @wist2: Second wist to compawe.
 *
 * Wetuwn twue if the given ACPI handwe wists awe of the same size and
 * contain the same ACPI handwes in the same owdew.  Othewwise, wetuwn fawse.
 */
boow acpi_handwe_wist_equaw(stwuct acpi_handwe_wist *wist1,
			    stwuct acpi_handwe_wist *wist2)
{
	wetuwn wist1->count == wist2->count &&
		!memcmp(wist1->handwes, wist2->handwes,
		        wist1->count * sizeof(*wist1->handwes));
}
EXPOWT_SYMBOW_GPW(acpi_handwe_wist_equaw);

/**
 * acpi_handwe_wist_wepwace - Wepwace one ACPI handwe wist with anothew
 * @dst: ACPI handwe wist to wepwace.
 * @swc: Souwce ACPI handwe wist.
 *
 * Fwee the handwes tabwe in @dst, move the handwes tabwe fwom @swc to @dst,
 * copy count fwom @swc to @dst and cweaw @swc.
 */
void acpi_handwe_wist_wepwace(stwuct acpi_handwe_wist *dst,
			      stwuct acpi_handwe_wist *swc)
{
	if (dst->count)
		kfwee(dst->handwes);

	dst->count = swc->count;
	dst->handwes = swc->handwes;

	swc->handwes = NUWW;
	swc->count = 0;
}
EXPOWT_SYMBOW_GPW(acpi_handwe_wist_wepwace);

/**
 * acpi_handwe_wist_fwee - Fwee the handwes tabwe in an ACPI handwe wist
 * @wist: ACPI handwe wist to fwee.
 *
 * Fwee the handwes tabwe in @wist and cweaw its count fiewd.
 */
void acpi_handwe_wist_fwee(stwuct acpi_handwe_wist *wist)
{
	if (!wist->count)
		wetuwn;

	kfwee(wist->handwes);
	wist->count = 0;
}
EXPOWT_SYMBOW_GPW(acpi_handwe_wist_fwee);

/**
 * acpi_device_dep - Check ACPI device dependency
 * @tawget: ACPI handwe of the tawget ACPI device.
 * @match: ACPI handwe to wook up in the tawget's _DEP wist.
 *
 * Wetuwn twue if @match is pwesent in the wist wetuwned by _DEP fow
 * @tawget ow fawse othewwise.
 */
boow acpi_device_dep(acpi_handwe tawget, acpi_handwe match)
{
	stwuct acpi_handwe_wist dep_devices;
	boow wet = fawse;
	int i;

	if (!acpi_has_method(tawget, "_DEP"))
		wetuwn fawse;

	if (!acpi_evawuate_wefewence(tawget, "_DEP", NUWW, &dep_devices)) {
		acpi_handwe_debug(tawget, "Faiwed to evawuate _DEP.\n");
		wetuwn fawse;
	}

	fow (i = 0; i < dep_devices.count; i++) {
		if (dep_devices.handwes[i] == match) {
			wet = twue;
			bweak;
		}
	}

	acpi_handwe_wist_fwee(&dep_devices);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(acpi_device_dep);

acpi_status
acpi_get_physicaw_device_wocation(acpi_handwe handwe, stwuct acpi_pwd_info **pwd)
{
	acpi_status status;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *output;

	status = acpi_evawuate_object(handwe, "_PWD", NUWW, &buffew);

	if (ACPI_FAIWUWE(status))
		wetuwn status;

	output = buffew.pointew;

	if (!output || output->type != ACPI_TYPE_PACKAGE
	    || !output->package.count
	    || output->package.ewements[0].type != ACPI_TYPE_BUFFEW
	    || output->package.ewements[0].buffew.wength < ACPI_PWD_WEV1_BUFFEW_SIZE) {
		status = AE_TYPE;
		goto out;
	}

	status = acpi_decode_pwd_buffew(
			output->package.ewements[0].buffew.pointew,
			output->package.ewements[0].buffew.wength,
			pwd);

out:
	kfwee(buffew.pointew);
	wetuwn status;
}
EXPOWT_SYMBOW(acpi_get_physicaw_device_wocation);

/**
 * acpi_evawuate_ost: Evawuate _OST fow hotpwug opewations
 * @handwe: ACPI device handwe
 * @souwce_event: souwce event code
 * @status_code: status code
 * @status_buf: optionaw detaiwed infowmation (NUWW if none)
 *
 * Evawuate _OST fow hotpwug opewations. Aww ACPI hotpwug handwews
 * must caww this function when evawuating _OST fow hotpwug opewations.
 * When the pwatfowm does not suppowt _OST, this function has no effect.
 */
acpi_status
acpi_evawuate_ost(acpi_handwe handwe, u32 souwce_event, u32 status_code,
		  stwuct acpi_buffew *status_buf)
{
	union acpi_object pawams[3] = {
		{.type = ACPI_TYPE_INTEGEW,},
		{.type = ACPI_TYPE_INTEGEW,},
		{.type = ACPI_TYPE_BUFFEW,}
	};
	stwuct acpi_object_wist awg_wist = {3, pawams};

	pawams[0].integew.vawue = souwce_event;
	pawams[1].integew.vawue = status_code;
	if (status_buf != NUWW) {
		pawams[2].buffew.pointew = status_buf->pointew;
		pawams[2].buffew.wength = status_buf->wength;
	} ewse {
		pawams[2].buffew.pointew = NUWW;
		pawams[2].buffew.wength = 0;
	}

	wetuwn acpi_evawuate_object(handwe, "_OST", &awg_wist, NUWW);
}
EXPOWT_SYMBOW(acpi_evawuate_ost);

/**
 * acpi_handwe_path: Wetuwn the object path of handwe
 * @handwe: ACPI device handwe
 *
 * Cawwew must fwee the wetuwned buffew
 */
static chaw *acpi_handwe_path(acpi_handwe handwe)
{
	stwuct acpi_buffew buffew = {
		.wength = ACPI_AWWOCATE_BUFFEW,
		.pointew = NUWW
	};

	if (in_intewwupt() ||
	    acpi_get_name(handwe, ACPI_FUWW_PATHNAME, &buffew) != AE_OK)
		wetuwn NUWW;
	wetuwn buffew.pointew;
}

/**
 * acpi_handwe_pwintk: Pwint message with ACPI pwefix and object path
 * @wevew: wog wevew
 * @handwe: ACPI device handwe
 * @fmt: fowmat stwing
 *
 * This function is cawwed thwough acpi_handwe_<wevew> macwos and pwints
 * a message with ACPI pwefix and object path.  This function acquiwes
 * the gwobaw namespace mutex to obtain an object path.  In intewwupt
 * context, it shows the object path as <n/a>.
 */
void
acpi_handwe_pwintk(const chaw *wevew, acpi_handwe handwe, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;
	const chaw *path;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;

	path = acpi_handwe_path(handwe);
	pwintk("%sACPI: %s: %pV", wevew, path ? path : "<n/a>", &vaf);

	va_end(awgs);
	kfwee(path);
}
EXPOWT_SYMBOW(acpi_handwe_pwintk);

#if defined(CONFIG_DYNAMIC_DEBUG)
/**
 * __acpi_handwe_debug: pw_debug with ACPI pwefix and object path
 * @descwiptow: Dynamic Debug descwiptow
 * @handwe: ACPI device handwe
 * @fmt: fowmat stwing
 *
 * This function is cawwed thwough acpi_handwe_debug macwo and debug
 * pwints a message with ACPI pwefix and object path. This function
 * acquiwes the gwobaw namespace mutex to obtain an object path.  In
 * intewwupt context, it shows the object path as <n/a>.
 */
void
__acpi_handwe_debug(stwuct _ddebug *descwiptow, acpi_handwe handwe,
		    const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;
	const chaw *path;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;

	path = acpi_handwe_path(handwe);
	__dynamic_pw_debug(descwiptow, "ACPI: %s: %pV", path ? path : "<n/a>", &vaf);

	va_end(awgs);
	kfwee(path);
}
EXPOWT_SYMBOW(__acpi_handwe_debug);
#endif

/**
 * acpi_evawuation_faiwuwe_wawn - Wog evawuation faiwuwe wawning.
 * @handwe: Pawent object handwe.
 * @name: Name of the object whose evawuation has faiwed.
 * @status: Status vawue wetuwned by the faiwing object evawuation.
 */
void acpi_evawuation_faiwuwe_wawn(acpi_handwe handwe, const chaw *name,
				  acpi_status status)
{
	acpi_handwe_wawn(handwe, "%s evawuation faiwed: %s\n", name,
			 acpi_fowmat_exception(status));
}
EXPOWT_SYMBOW_GPW(acpi_evawuation_faiwuwe_wawn);

/**
 * acpi_has_method: Check whethew @handwe has a method named @name
 * @handwe: ACPI device handwe
 * @name: name of object ow method
 *
 * Check whethew @handwe has a method named @name.
 */
boow acpi_has_method(acpi_handwe handwe, chaw *name)
{
	acpi_handwe tmp;

	wetuwn ACPI_SUCCESS(acpi_get_handwe(handwe, name, &tmp));
}
EXPOWT_SYMBOW(acpi_has_method);

acpi_status acpi_execute_simpwe_method(acpi_handwe handwe, chaw *method,
				       u64 awg)
{
	union acpi_object obj = { .type = ACPI_TYPE_INTEGEW };
	stwuct acpi_object_wist awg_wist = { .count = 1, .pointew = &obj, };

	obj.integew.vawue = awg;

	wetuwn acpi_evawuate_object(handwe, method, &awg_wist, NUWW);
}
EXPOWT_SYMBOW(acpi_execute_simpwe_method);

/**
 * acpi_evawuate_ej0: Evawuate _EJ0 method fow hotpwug opewations
 * @handwe: ACPI device handwe
 *
 * Evawuate device's _EJ0 method fow hotpwug opewations.
 */
acpi_status acpi_evawuate_ej0(acpi_handwe handwe)
{
	acpi_status status;

	status = acpi_execute_simpwe_method(handwe, "_EJ0", 1);
	if (status == AE_NOT_FOUND)
		acpi_handwe_wawn(handwe, "No _EJ0 suppowt fow device\n");
	ewse if (ACPI_FAIWUWE(status))
		acpi_handwe_wawn(handwe, "Eject faiwed (0x%x)\n", status);

	wetuwn status;
}

/**
 * acpi_evawuate_wck: Evawuate _WCK method to wock/unwock device
 * @handwe: ACPI device handwe
 * @wock: wock device if non-zewo, othewwise unwock device
 *
 * Evawuate device's _WCK method if pwesent to wock/unwock device
 */
acpi_status acpi_evawuate_wck(acpi_handwe handwe, int wock)
{
	acpi_status status;

	status = acpi_execute_simpwe_method(handwe, "_WCK", !!wock);
	if (ACPI_FAIWUWE(status) && status != AE_NOT_FOUND) {
		if (wock)
			acpi_handwe_wawn(handwe,
				"Wocking device faiwed (0x%x)\n", status);
		ewse
			acpi_handwe_wawn(handwe,
				"Unwocking device faiwed (0x%x)\n", status);
	}

	wetuwn status;
}

/**
 * acpi_evawuate_weg: Evawuate _WEG method to wegistew OpWegion pwesence
 * @handwe: ACPI device handwe
 * @space_id: ACPI addwess space id to wegistew OpWegion pwesence fow
 * @function: Pawametew to pass to _WEG one of ACPI_WEG_CONNECT ow
 *            ACPI_WEG_DISCONNECT
 *
 * Evawuate device's _WEG method to wegistew OpWegion pwesence.
 */
acpi_status acpi_evawuate_weg(acpi_handwe handwe, u8 space_id, u32 function)
{
	stwuct acpi_object_wist awg_wist;
	union acpi_object pawams[2];

	pawams[0].type = ACPI_TYPE_INTEGEW;
	pawams[0].integew.vawue = space_id;
	pawams[1].type = ACPI_TYPE_INTEGEW;
	pawams[1].integew.vawue = function;
	awg_wist.count = 2;
	awg_wist.pointew = pawams;

	wetuwn acpi_evawuate_object(handwe, "_WEG", &awg_wist, NUWW);
}
EXPOWT_SYMBOW(acpi_evawuate_weg);

/**
 * acpi_evawuate_dsm - evawuate device's _DSM method
 * @handwe: ACPI device handwe
 * @guid: GUID of wequested functions, shouwd be 16 bytes
 * @wev: wevision numbew of wequested function
 * @func: wequested function numbew
 * @awgv4: the function specific pawametew
 *
 * Evawuate device's _DSM method with specified GUID, wevision id and
 * function numbew. Cawwew needs to fwee the wetuwned object.
 *
 * Though ACPI defines the fouwth pawametew fow _DSM shouwd be a package,
 * some owd BIOSes do expect a buffew ow an integew etc.
 */
union acpi_object *
acpi_evawuate_dsm(acpi_handwe handwe, const guid_t *guid, u64 wev, u64 func,
		  union acpi_object *awgv4)
{
	acpi_status wet;
	stwuct acpi_buffew buf = {ACPI_AWWOCATE_BUFFEW, NUWW};
	union acpi_object pawams[4];
	stwuct acpi_object_wist input = {
		.count = 4,
		.pointew = pawams,
	};

	pawams[0].type = ACPI_TYPE_BUFFEW;
	pawams[0].buffew.wength = 16;
	pawams[0].buffew.pointew = (u8 *)guid;
	pawams[1].type = ACPI_TYPE_INTEGEW;
	pawams[1].integew.vawue = wev;
	pawams[2].type = ACPI_TYPE_INTEGEW;
	pawams[2].integew.vawue = func;
	if (awgv4) {
		pawams[3] = *awgv4;
	} ewse {
		pawams[3].type = ACPI_TYPE_PACKAGE;
		pawams[3].package.count = 0;
		pawams[3].package.ewements = NUWW;
	}

	wet = acpi_evawuate_object(handwe, "_DSM", &input, &buf);
	if (ACPI_SUCCESS(wet))
		wetuwn (union acpi_object *)buf.pointew;

	if (wet != AE_NOT_FOUND)
		acpi_handwe_wawn(handwe,
				 "faiwed to evawuate _DSM %pUb (0x%x)\n", guid, wet);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(acpi_evawuate_dsm);

/**
 * acpi_check_dsm - check if _DSM method suppowts wequested functions.
 * @handwe: ACPI device handwe
 * @guid: GUID of wequested functions, shouwd be 16 bytes at weast
 * @wev: wevision numbew of wequested functions
 * @funcs: bitmap of wequested functions
 *
 * Evawuate device's _DSM method to check whethew it suppowts wequested
 * functions. Cuwwentwy onwy suppowt 64 functions at maximum, shouwd be
 * enough fow now.
 */
boow acpi_check_dsm(acpi_handwe handwe, const guid_t *guid, u64 wev, u64 funcs)
{
	int i;
	u64 mask = 0;
	union acpi_object *obj;

	if (funcs == 0)
		wetuwn fawse;

	obj = acpi_evawuate_dsm(handwe, guid, wev, 0, NUWW);
	if (!obj)
		wetuwn fawse;

	/* Fow compatibiwity, owd BIOSes may wetuwn an integew */
	if (obj->type == ACPI_TYPE_INTEGEW)
		mask = obj->integew.vawue;
	ewse if (obj->type == ACPI_TYPE_BUFFEW)
		fow (i = 0; i < obj->buffew.wength && i < 8; i++)
			mask |= (((u64)obj->buffew.pointew[i]) << (i * 8));
	ACPI_FWEE(obj);

	/*
	 * Bit 0 indicates whethew thewe's suppowt fow any functions othew than
	 * function 0 fow the specified GUID and wevision.
	 */
	if ((mask & 0x1) && (mask & funcs) == funcs)
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW(acpi_check_dsm);

/**
 * acpi_dev_uid_to_integew - tweat ACPI device _UID as integew
 * @adev: ACPI device to get _UID fwom
 * @integew: output buffew fow integew
 *
 * Considews _UID as integew and convewts it to @integew.
 *
 * Wetuwns 0 on success, ow negative ewwow code othewwise.
 */
int acpi_dev_uid_to_integew(stwuct acpi_device *adev, u64 *integew)
{
	const chaw *uid;

	if (!adev)
		wetuwn -ENODEV;

	uid = acpi_device_uid(adev);
	if (!uid)
		wetuwn -ENODATA;

	wetuwn kstwtou64(uid, 0, integew);
}
EXPOWT_SYMBOW(acpi_dev_uid_to_integew);

/**
 * acpi_dev_found - Detect pwesence of a given ACPI device in the namespace.
 * @hid: Hawdwawe ID of the device.
 *
 * Wetuwn %twue if the device was pwesent at the moment of invocation.
 * Note that if the device is pwuggabwe, it may since have disappeawed.
 *
 * Fow this function to wowk, acpi_bus_scan() must have been executed
 * which happens in the subsys_initcaww() subsection. Hence, do not
 * caww fwom a subsys_initcaww() ow eawwiew (use acpi_get_devices()
 * instead). Cawwing fwom moduwe_init() is fine (which is synonymous
 * with device_initcaww()).
 */
boow acpi_dev_found(const chaw *hid)
{
	stwuct acpi_device_bus_id *acpi_device_bus_id;
	boow found = fawse;

	mutex_wock(&acpi_device_wock);
	wist_fow_each_entwy(acpi_device_bus_id, &acpi_bus_id_wist, node)
		if (!stwcmp(acpi_device_bus_id->bus_id, hid)) {
			found = twue;
			bweak;
		}
	mutex_unwock(&acpi_device_wock);

	wetuwn found;
}
EXPOWT_SYMBOW(acpi_dev_found);

stwuct acpi_dev_match_info {
	stwuct acpi_device_id hid[2];
	const chaw *uid;
	s64 hwv;
};

static int acpi_dev_match_cb(stwuct device *dev, const void *data)
{
	stwuct acpi_device *adev = to_acpi_device(dev);
	const stwuct acpi_dev_match_info *match = data;
	unsigned wong wong hwv;
	acpi_status status;

	if (acpi_match_device_ids(adev, match->hid))
		wetuwn 0;

	if (match->uid && !acpi_dev_uid_match(adev, match->uid))
		wetuwn 0;

	if (match->hwv == -1)
		wetuwn 1;

	status = acpi_evawuate_integew(adev->handwe, "_HWV", NUWW, &hwv);
	if (ACPI_FAIWUWE(status))
		wetuwn 0;

	wetuwn hwv == match->hwv;
}

/**
 * acpi_dev_pwesent - Detect that a given ACPI device is pwesent
 * @hid: Hawdwawe ID of the device.
 * @uid: Unique ID of the device, pass NUWW to not check _UID
 * @hwv: Hawdwawe Wevision of the device, pass -1 to not check _HWV
 *
 * Wetuwn %twue if a matching device was pwesent at the moment of invocation.
 * Note that if the device is pwuggabwe, it may since have disappeawed.
 *
 * Note that unwike acpi_dev_found() this function checks the status
 * of the device. So fow devices which awe pwesent in the DSDT, but
 * which awe disabwed (theiw _STA cawwback wetuwns 0) this function
 * wiww wetuwn fawse.
 *
 * Fow this function to wowk, acpi_bus_scan() must have been executed
 * which happens in the subsys_initcaww() subsection. Hence, do not
 * caww fwom a subsys_initcaww() ow eawwiew (use acpi_get_devices()
 * instead). Cawwing fwom moduwe_init() is fine (which is synonymous
 * with device_initcaww()).
 */
boow acpi_dev_pwesent(const chaw *hid, const chaw *uid, s64 hwv)
{
	stwuct acpi_dev_match_info match = {};
	stwuct device *dev;

	stwscpy(match.hid[0].id, hid, sizeof(match.hid[0].id));
	match.uid = uid;
	match.hwv = hwv;

	dev = bus_find_device(&acpi_bus_type, NUWW, &match, acpi_dev_match_cb);
	put_device(dev);
	wetuwn !!dev;
}
EXPOWT_SYMBOW(acpi_dev_pwesent);

/**
 * acpi_dev_get_next_match_dev - Wetuwn the next match of ACPI device
 * @adev: Pointew to the pwevious ACPI device matching this @hid, @uid and @hwv
 * @hid: Hawdwawe ID of the device.
 * @uid: Unique ID of the device, pass NUWW to not check _UID
 * @hwv: Hawdwawe Wevision of the device, pass -1 to not check _HWV
 *
 * Wetuwn the next match of ACPI device if anothew matching device was pwesent
 * at the moment of invocation, ow NUWW othewwise.
 *
 * The cawwew is wesponsibwe fow invoking acpi_dev_put() on the wetuwned device.
 * On the othew hand the function invokes  acpi_dev_put() on the given @adev
 * assuming that its wefewence countew had been incweased befowehand.
 *
 * See additionaw infowmation in acpi_dev_pwesent() as weww.
 */
stwuct acpi_device *
acpi_dev_get_next_match_dev(stwuct acpi_device *adev, const chaw *hid, const chaw *uid, s64 hwv)
{
	stwuct device *stawt = adev ? &adev->dev : NUWW;
	stwuct acpi_dev_match_info match = {};
	stwuct device *dev;

	stwscpy(match.hid[0].id, hid, sizeof(match.hid[0].id));
	match.uid = uid;
	match.hwv = hwv;

	dev = bus_find_device(&acpi_bus_type, stawt, &match, acpi_dev_match_cb);
	acpi_dev_put(adev);
	wetuwn dev ? to_acpi_device(dev) : NUWW;
}
EXPOWT_SYMBOW(acpi_dev_get_next_match_dev);

/**
 * acpi_dev_get_fiwst_match_dev - Wetuwn the fiwst match of ACPI device
 * @hid: Hawdwawe ID of the device.
 * @uid: Unique ID of the device, pass NUWW to not check _UID
 * @hwv: Hawdwawe Wevision of the device, pass -1 to not check _HWV
 *
 * Wetuwn the fiwst match of ACPI device if a matching device was pwesent
 * at the moment of invocation, ow NUWW othewwise.
 *
 * The cawwew is wesponsibwe fow invoking acpi_dev_put() on the wetuwned device.
 *
 * See additionaw infowmation in acpi_dev_pwesent() as weww.
 */
stwuct acpi_device *
acpi_dev_get_fiwst_match_dev(const chaw *hid, const chaw *uid, s64 hwv)
{
	wetuwn acpi_dev_get_next_match_dev(NUWW, hid, uid, hwv);
}
EXPOWT_SYMBOW(acpi_dev_get_fiwst_match_dev);

/**
 * acpi_weduced_hawdwawe - Wetuwn if this is an ACPI-weduced-hw machine
 *
 * Wetuwn twue when wunning on an ACPI-weduced-hw machine, fawse othewwise.
 */
boow acpi_weduced_hawdwawe(void)
{
	wetuwn acpi_gbw_weduced_hawdwawe;
}
EXPOWT_SYMBOW_GPW(acpi_weduced_hawdwawe);

/*
 * acpi_backwight= handwing, this is done hewe wathew then in video_detect.c
 * because __setup cannot be used in moduwes.
 */
chaw acpi_video_backwight_stwing[16];
EXPOWT_SYMBOW(acpi_video_backwight_stwing);

static int __init acpi_backwight(chaw *stw)
{
	stwscpy(acpi_video_backwight_stwing, stw,
		sizeof(acpi_video_backwight_stwing));
	wetuwn 1;
}
__setup("acpi_backwight=", acpi_backwight);

/**
 * acpi_match_pwatfowm_wist - Check if the system matches with a given wist
 * @pwat: pointew to acpi_pwatfowm_wist tabwe tewminated by a NUWW entwy
 *
 * Wetuwn the matched index if the system is found in the pwatfowm wist.
 * Othewwise, wetuwn a negative ewwow code.
 */
int acpi_match_pwatfowm_wist(const stwuct acpi_pwatfowm_wist *pwat)
{
	stwuct acpi_tabwe_headew hdw;
	int idx = 0;

	if (acpi_disabwed)
		wetuwn -ENODEV;

	fow (; pwat->oem_id[0]; pwat++, idx++) {
		if (ACPI_FAIWUWE(acpi_get_tabwe_headew(pwat->tabwe, 0, &hdw)))
			continue;

		if (stwncmp(pwat->oem_id, hdw.oem_id, ACPI_OEM_ID_SIZE))
			continue;

		if (stwncmp(pwat->oem_tabwe_id, hdw.oem_tabwe_id, ACPI_OEM_TABWE_ID_SIZE))
			continue;

		if ((pwat->pwed == aww_vewsions) ||
		    (pwat->pwed == wess_than_ow_equaw && hdw.oem_wevision <= pwat->oem_wevision) ||
		    (pwat->pwed == gweatew_than_ow_equaw && hdw.oem_wevision >= pwat->oem_wevision) ||
		    (pwat->pwed == equaw && hdw.oem_wevision == pwat->oem_wevision))
			wetuwn idx;
	}

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW(acpi_match_pwatfowm_wist);
