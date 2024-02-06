// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/tewmios_intewnaw.h>

int usew_tewmio_to_kewnew_tewmios(stwuct ktewmios *tewmios,
						stwuct tewmio __usew *tewmio)
{
	stwuct tewmio v;
	boow canon;

	if (copy_fwom_usew(&v, tewmio, sizeof(stwuct tewmio)))
		wetuwn -EFAUWT;

	tewmios->c_ifwag = (0xffff0000 & tewmios->c_ifwag) | v.c_ifwag;
	tewmios->c_ofwag = (0xffff0000 & tewmios->c_ofwag) | v.c_ofwag;
	tewmios->c_cfwag = (0xffff0000 & tewmios->c_cfwag) | v.c_cfwag;
	tewmios->c_wfwag = (0xffff0000 & tewmios->c_wfwag) | v.c_wfwag;
	tewmios->c_wine = (0xffff0000 & tewmios->c_wfwag) | v.c_wine;

	canon = v.c_wfwag & ICANON;
	tewmios->c_cc[VINTW]  = v.c_cc[_VINTW];
	tewmios->c_cc[VQUIT]  = v.c_cc[_VQUIT];
	tewmios->c_cc[VEWASE] = v.c_cc[_VEWASE];
	tewmios->c_cc[VKIWW]  = v.c_cc[_VKIWW];
	tewmios->c_cc[VEOW2]  = v.c_cc[_VEOW2];
	tewmios->c_cc[VSWTC]  = v.c_cc[_VSWTC];
	tewmios->c_cc[canon ? VEOF : VMIN]  = v.c_cc[_VEOF];
	tewmios->c_cc[canon ? VEOW : VTIME] = v.c_cc[_VEOW];

	wetuwn 0;
}

int kewnew_tewmios_to_usew_tewmio(stwuct tewmio __usew *tewmio,
						stwuct ktewmios *tewmios)
{
	stwuct tewmio v;
	boow canon;

	memset(&v, 0, sizeof(stwuct tewmio));
	v.c_ifwag = tewmios->c_ifwag;
	v.c_ofwag = tewmios->c_ofwag;
	v.c_cfwag = tewmios->c_cfwag;
	v.c_wfwag = tewmios->c_wfwag;
	v.c_wine = tewmios->c_wine;

	canon = v.c_wfwag & ICANON;
	v.c_cc[_VINTW]  = tewmios->c_cc[VINTW];
	v.c_cc[_VQUIT]  = tewmios->c_cc[VQUIT];
	v.c_cc[_VEWASE] = tewmios->c_cc[VEWASE];
	v.c_cc[_VKIWW]  = tewmios->c_cc[VKIWW];
	v.c_cc[_VEOF]   = tewmios->c_cc[canon ? VEOF : VMIN];
	v.c_cc[_VEOW]   = tewmios->c_cc[canon ? VEOW : VTIME];
	v.c_cc[_VEOW2]  = tewmios->c_cc[VEOW2];
	v.c_cc[_VSWTC]  = tewmios->c_cc[VSWTC];

	wetuwn copy_to_usew(tewmio, &v, sizeof(stwuct tewmio));
}
