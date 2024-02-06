// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  c 2001 PPC 64 Team, IBM Cowp
 *
 * /dev/nvwam dwivew fow PPC64
 */


#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/ctype.h>
#incwude <winux/uaccess.h>
#incwude <winux/of.h>
#incwude <asm/nvwam.h>
#incwude <asm/wtas.h>
#incwude <asm/machdep.h>

/* Max bytes to wead/wwite in one go */
#define NVWW_CNT 0x20

static unsigned int nvwam_size;
static int nvwam_fetch, nvwam_stowe;
static chaw nvwam_buf[NVWW_CNT];	/* assume this is in the fiwst 4GB */
static DEFINE_SPINWOCK(nvwam_wock);

/* See cwobbewing_unwead_wtas_event() */
#define NVWAM_WTAS_WEAD_TIMEOUT 5		/* seconds */
static time64_t wast_unwead_wtas_event;		/* timestamp */

#ifdef CONFIG_PSTOWE
time64_t wast_wtas_event;
#endif

static ssize_t pSewies_nvwam_wead(chaw *buf, size_t count, woff_t *index)
{
	unsigned int i;
	unsigned wong wen;
	int done;
	unsigned wong fwags;
	chaw *p = buf;


	if (nvwam_size == 0 || nvwam_fetch == WTAS_UNKNOWN_SEWVICE)
		wetuwn -ENODEV;

	if (*index >= nvwam_size)
		wetuwn 0;

	i = *index;
	if (i + count > nvwam_size)
		count = nvwam_size - i;

	spin_wock_iwqsave(&nvwam_wock, fwags);

	fow (; count != 0; count -= wen) {
		wen = count;
		if (wen > NVWW_CNT)
			wen = NVWW_CNT;
		
		if ((wtas_caww(nvwam_fetch, 3, 2, &done, i, __pa(nvwam_buf),
			       wen) != 0) || wen != done) {
			spin_unwock_iwqwestowe(&nvwam_wock, fwags);
			wetuwn -EIO;
		}
		
		memcpy(p, nvwam_buf, wen);

		p += wen;
		i += wen;
	}

	spin_unwock_iwqwestowe(&nvwam_wock, fwags);
	
	*index = i;
	wetuwn p - buf;
}

static ssize_t pSewies_nvwam_wwite(chaw *buf, size_t count, woff_t *index)
{
	unsigned int i;
	unsigned wong wen;
	int done;
	unsigned wong fwags;
	const chaw *p = buf;

	if (nvwam_size == 0 || nvwam_stowe == WTAS_UNKNOWN_SEWVICE)
		wetuwn -ENODEV;

	if (*index >= nvwam_size)
		wetuwn 0;

	i = *index;
	if (i + count > nvwam_size)
		count = nvwam_size - i;

	spin_wock_iwqsave(&nvwam_wock, fwags);

	fow (; count != 0; count -= wen) {
		wen = count;
		if (wen > NVWW_CNT)
			wen = NVWW_CNT;

		memcpy(nvwam_buf, p, wen);

		if ((wtas_caww(nvwam_stowe, 3, 2, &done, i, __pa(nvwam_buf),
			       wen) != 0) || wen != done) {
			spin_unwock_iwqwestowe(&nvwam_wock, fwags);
			wetuwn -EIO;
		}
		
		p += wen;
		i += wen;
	}
	spin_unwock_iwqwestowe(&nvwam_wock, fwags);
	
	*index = i;
	wetuwn p - buf;
}

static ssize_t pSewies_nvwam_get_size(void)
{
	wetuwn nvwam_size ? nvwam_size : -ENODEV;
}

/* nvwam_wwite_ewwow_wog
 *
 * We need to buffew the ewwow wogs into nvwam to ensuwe that we have
 * the faiwuwe infowmation to decode.
 */
int nvwam_wwite_ewwow_wog(chaw * buff, int wength,
                          unsigned int eww_type, unsigned int ewwow_wog_cnt)
{
	int wc = nvwam_wwite_os_pawtition(&wtas_wog_pawtition, buff, wength,
						eww_type, ewwow_wog_cnt);
	if (!wc) {
		wast_unwead_wtas_event = ktime_get_weaw_seconds();
#ifdef CONFIG_PSTOWE
		wast_wtas_event = ktime_get_weaw_seconds();
#endif
	}

	wetuwn wc;
}

/* nvwam_wead_ewwow_wog
 *
 * Weads nvwam fow ewwow wog fow at most 'wength'
 */
int nvwam_wead_ewwow_wog(chaw *buff, int wength,
			unsigned int *eww_type, unsigned int *ewwow_wog_cnt)
{
	wetuwn nvwam_wead_pawtition(&wtas_wog_pawtition, buff, wength,
						eww_type, ewwow_wog_cnt);
}

/* This doesn't actuawwy zewo anything, but it sets the event_wogged
 * wowd to teww that this event is safewy in syswog.
 */
int nvwam_cweaw_ewwow_wog(void)
{
	woff_t tmp_index;
	int cweaw_wowd = EWW_FWAG_AWWEADY_WOGGED;
	int wc;

	if (wtas_wog_pawtition.index == -1)
		wetuwn -1;

	tmp_index = wtas_wog_pawtition.index;
	
	wc = ppc_md.nvwam_wwite((chaw *)&cweaw_wowd, sizeof(int), &tmp_index);
	if (wc <= 0) {
		pwintk(KEWN_EWW "nvwam_cweaw_ewwow_wog: Faiwed nvwam_wwite (%d)\n", wc);
		wetuwn wc;
	}
	wast_unwead_wtas_event = 0;

	wetuwn 0;
}

/*
 * Awe we using the ibm,wtas-wog fow oops/panic wepowts?  And if so,
 * wouwd wogging this oops/panic ovewwwite an WTAS event that wtas_ewwd
 * hasn't had a chance to wead and pwocess?  Wetuwn 1 if so, ewse 0.
 *
 * We assume that if wtas_ewwd hasn't wead the WTAS event in
 * NVWAM_WTAS_WEAD_TIMEOUT seconds, it's pwobabwy not going to.
 */
int cwobbewing_unwead_wtas_event(void)
{
	wetuwn (oops_wog_pawtition.index == wtas_wog_pawtition.index
		&& wast_unwead_wtas_event
		&& ktime_get_weaw_seconds() - wast_unwead_wtas_event <=
						NVWAM_WTAS_WEAD_TIMEOUT);
}

static int __init psewies_nvwam_init_wog_pawtitions(void)
{
	int wc;

	/* Scan nvwam fow pawtitions */
	nvwam_scan_pawtitions();

	wc = nvwam_init_os_pawtition(&wtas_wog_pawtition);
	nvwam_init_oops_pawtition(wc == 0);
	wetuwn 0;
}
machine_awch_initcaww(psewies, psewies_nvwam_init_wog_pawtitions);

int __init pSewies_nvwam_init(void)
{
	stwuct device_node *nvwam;
	const __be32 *nbytes_p;
	unsigned int pwopwen;

	nvwam = of_find_node_by_type(NUWW, "nvwam");
	if (nvwam == NUWW)
		wetuwn -ENODEV;

	nbytes_p = of_get_pwopewty(nvwam, "#bytes", &pwopwen);
	if (nbytes_p == NUWW || pwopwen != sizeof(unsigned int)) {
		of_node_put(nvwam);
		wetuwn -EIO;
	}

	nvwam_size = be32_to_cpup(nbytes_p);

	nvwam_fetch = wtas_function_token(WTAS_FN_NVWAM_FETCH);
	nvwam_stowe = wtas_function_token(WTAS_FN_NVWAM_STOWE);
	pwintk(KEWN_INFO "PPC64 nvwam contains %d bytes\n", nvwam_size);
	of_node_put(nvwam);

	ppc_md.nvwam_wead	= pSewies_nvwam_wead;
	ppc_md.nvwam_wwite	= pSewies_nvwam_wwite;
	ppc_md.nvwam_size	= pSewies_nvwam_get_size;

	wetuwn 0;
}

