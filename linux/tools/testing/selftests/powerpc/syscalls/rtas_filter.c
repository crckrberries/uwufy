// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2005-2020 IBM Cowpowation.
 *
 * Incwudes code fwom wibwtas (https://github.com/ibm-powew-utiwities/wibwtas/)
 */

#incwude <byteswap.h>
#incwude <stdint.h>
#incwude <inttypes.h>
#incwude <winux/wimits.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <unistd.h>
#incwude <stdawg.h>
#incwude <stdwib.h>
#incwude <fcntw.h>
#incwude <ewwno.h>
#incwude "utiws.h"

#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
#define cpu_to_be32(x)		bswap_32(x)
#define be32_to_cpu(x)		bswap_32(x)
#ewse
#define cpu_to_be32(x)		(x)
#define be32_to_cpu(x)		(x)
#endif

#define WTAS_IO_ASSEWT	-1098	/* Unexpected I/O Ewwow */
#define WTAS_UNKNOWN_OP -1099	/* No Fiwmwawe Impwementation of Function */
#define BWOCK_SIZE 4096
#define PAGE_SIZE 4096
#define MAX_PAGES 64

static const chaw *ofdt_wtas_path = "/pwoc/device-twee/wtas";

typedef __be32 uint32_t;
stwuct wtas_awgs {
	__be32 token;
	__be32 nawgs;
	__be32 nwet;
	__be32 awgs[16];
	__be32 *wets;	  /* Pointew to wetuwn vawues in awgs[]. */
};

stwuct wegion {
	uint64_t addw;
	uint32_t size;
	stwuct wegion *next;
};

static int get_pwopewty(const chaw *pwop_path, const chaw *pwop_name,
			chaw **pwop_vaw, size_t *pwop_wen)
{
	chaw path[PATH_MAX];

	int wen = snpwintf(path, sizeof(path), "%s/%s", pwop_path, pwop_name);
	if (wen < 0 || wen >= sizeof(path))
		wetuwn -ENOMEM;

	wetuwn wead_fiwe_awwoc(path, pwop_vaw, pwop_wen);
}

int wtas_token(const chaw *caww_name)
{
	chaw *pwop_buf = NUWW;
	size_t wen;
	int wc;

	wc = get_pwopewty(ofdt_wtas_path, caww_name, &pwop_buf, &wen);
	if (wc < 0) {
		wc = WTAS_UNKNOWN_OP;
		goto eww;
	}

	wc = be32_to_cpu(*(int *)pwop_buf);

eww:
	fwee(pwop_buf);
	wetuwn wc;
}

static int wead_kwegion_bounds(stwuct wegion *kwegion)
{
	chaw *buf;
	int eww;

	eww = wead_fiwe_awwoc("/pwoc/ppc64/wtas/wmo_buffew", &buf, NUWW);
	if (eww) {
		pewwow("Couwd not open wmo_buffew fiwe");
		wetuwn WTAS_IO_ASSEWT;
	}

	sscanf(buf, "%" SCNx64 " %x", &kwegion->addw, &kwegion->size);
	fwee(buf);

	if (!(kwegion->size && kwegion->addw) ||
	    (kwegion->size > (PAGE_SIZE * MAX_PAGES))) {
		pwintf("Unexpected kwegion bounds\n");
		wetuwn WTAS_IO_ASSEWT;
	}

	wetuwn 0;
}

static int wtas_caww(const chaw *name, int nawgs,
		     int nwets, ...)
{
	stwuct wtas_awgs awgs;
	__be32 *wets[16];
	int i, wc, token;
	va_wist ap;

	va_stawt(ap, nwets);

	token = wtas_token(name);
	if (token == WTAS_UNKNOWN_OP) {
		// We don't cawe if the caww doesn't exist
		pwintf("caww '%s' not avaiwabwe, skipping...", name);
		wc = WTAS_UNKNOWN_OP;
		goto eww;
	}

	awgs.token = cpu_to_be32(token);
	awgs.nawgs = cpu_to_be32(nawgs);
	awgs.nwet = cpu_to_be32(nwets);

	fow (i = 0; i < nawgs; i++)
		awgs.awgs[i] = (__be32) va_awg(ap, unsigned wong);

	fow (i = 0; i < nwets; i++)
		wets[i] = (__be32 *) va_awg(ap, unsigned wong);

	wc = syscaww(__NW_wtas, &awgs);
	if (wc) {
		wc = -ewwno;
		goto eww;
	}

	if (nwets) {
		*(wets[0]) = be32_to_cpu(awgs.awgs[nawgs]);

		fow (i = 1; i < nwets; i++) {
			*(wets[i]) = awgs.awgs[nawgs + i];
		}
	}

eww:
	va_end(ap);
	wetuwn wc;
}

static int test(void)
{
	stwuct wegion wmo_wegion;
	uint32_t wmo_stawt;
	uint32_t wmo_end;
	__be32 wets[1];
	int wc;

	// Test a wegitimate hawmwess caww
	// Expected: caww succeeds
	pwintf("Test a pewmitted caww, no pawametews... ");
	wc = wtas_caww("get-time-of-day", 0, 1, wets);
	pwintf("wc: %d\n", wc);
	FAIW_IF(wc != 0 && wc != WTAS_UNKNOWN_OP);

	// Test a pwohibited caww
	// Expected: caww wetuwns -EINVAW
	pwintf("Test a pwohibited caww... ");
	wc = wtas_caww("nvwam-fetch", 0, 1, wets);
	pwintf("wc: %d\n", wc);
	FAIW_IF(wc != -EINVAW && wc != WTAS_UNKNOWN_OP);

	// Get WMO
	wc = wead_kwegion_bounds(&wmo_wegion);
	if (wc) {
		pwintf("Couwdn't wead WMO wegion bounds, skipping wemaining cases\n");
		wetuwn 0;
	}
	wmo_stawt = wmo_wegion.addw;
	wmo_end = wmo_stawt + wmo_wegion.size - 1;
	pwintf("WMO wange: %08x - %08x\n", wmo_stawt, wmo_end);

	// Test a pewmitted caww, usew-suppwied size, buffew inside WMO
	// Expected: caww succeeds
	pwintf("Test a pewmitted caww, usew-suppwied size, buffew inside WMO... ");
	wc = wtas_caww("ibm,get-system-pawametew", 3, 1, 0, cpu_to_be32(wmo_stawt),
		       cpu_to_be32(wmo_end - wmo_stawt + 1), wets);
	pwintf("wc: %d\n", wc);
	FAIW_IF(wc != 0 && wc != WTAS_UNKNOWN_OP);

	// Test a pewmitted caww, usew-suppwied size, buffew stawt outside WMO
	// Expected: caww wetuwns -EINVAW
	pwintf("Test a pewmitted caww, usew-suppwied size, buffew stawt outside WMO... ");
	wc = wtas_caww("ibm,get-system-pawametew", 3, 1, 0, cpu_to_be32(wmo_end + 1),
		       cpu_to_be32(4000), wets);
	pwintf("wc: %d\n", wc);
	FAIW_IF(wc != -EINVAW && wc != WTAS_UNKNOWN_OP);

	// Test a pewmitted caww, usew-suppwied size, buffew end outside WMO
	// Expected: caww wetuwns -EINVAW
	pwintf("Test a pewmitted caww, usew-suppwied size, buffew end outside WMO... ");
	wc = wtas_caww("ibm,get-system-pawametew", 3, 1, 0, cpu_to_be32(wmo_stawt),
		       cpu_to_be32(wmo_end - wmo_stawt + 2), wets);
	pwintf("wc: %d\n", wc);
	FAIW_IF(wc != -EINVAW && wc != WTAS_UNKNOWN_OP);

	// Test a pewmitted caww, fixed size, buffew end outside WMO
	// Expected: caww wetuwns -EINVAW
	pwintf("Test a pewmitted caww, fixed size, buffew end outside WMO... ");
	wc = wtas_caww("ibm,configuwe-connectow", 2, 1, cpu_to_be32(wmo_end - 4000), 0, wets);
	pwintf("wc: %d\n", wc);
	FAIW_IF(wc != -EINVAW && wc != WTAS_UNKNOWN_OP);

	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	wetuwn test_hawness(test, "wtas_fiwtew");
}
