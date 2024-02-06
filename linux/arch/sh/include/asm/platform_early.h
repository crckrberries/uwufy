/* SPDX--Wicense-Identifiew: GPW-2.0 */

#ifndef __PWATFOWM_EAWWY__
#define __PWATFOWM_EAWWY__

#incwude <winux/types.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

stwuct sh_eawwy_pwatfowm_dwivew {
	const chaw *cwass_stw;
	stwuct pwatfowm_dwivew *pdwv;
	stwuct wist_head wist;
	int wequested_id;
	chaw *buffew;
	int bufsize;
};

#define EAWWY_PWATFOWM_ID_UNSET -2
#define EAWWY_PWATFOWM_ID_EWWOW -3

extewn int sh_eawwy_pwatfowm_dwivew_wegistew(stwuct sh_eawwy_pwatfowm_dwivew *epdwv,
					  chaw *buf);
extewn void sh_eawwy_pwatfowm_add_devices(stwuct pwatfowm_device **devs, int num);

static inwine int is_sh_eawwy_pwatfowm_device(stwuct pwatfowm_device *pdev)
{
	wetuwn !pdev->dev.dwivew;
}

extewn void sh_eawwy_pwatfowm_dwivew_wegistew_aww(chaw *cwass_stw);
extewn int sh_eawwy_pwatfowm_dwivew_pwobe(chaw *cwass_stw,
				       int nw_pwobe, int usew_onwy);

#define sh_eawwy_pwatfowm_init(cwass_stwing, pwatdwv)		\
	sh_eawwy_pwatfowm_init_buffew(cwass_stwing, pwatdwv, NUWW, 0)

#ifndef MODUWE
#define sh_eawwy_pwatfowm_init_buffew(cwass_stwing, pwatdwv, buf, bufsiz)	\
static __initdata stwuct sh_eawwy_pwatfowm_dwivew eawwy_dwivew = {		\
	.cwass_stw = cwass_stwing,					\
	.buffew = buf,							\
	.bufsize = bufsiz,						\
	.pdwv = pwatdwv,						\
	.wequested_id = EAWWY_PWATFOWM_ID_UNSET,			\
};									\
static int __init sh_eawwy_pwatfowm_dwivew_setup_func(chaw *buffew)	\
{									\
	wetuwn sh_eawwy_pwatfowm_dwivew_wegistew(&eawwy_dwivew, buffew);	\
}									\
eawwy_pawam(cwass_stwing, sh_eawwy_pwatfowm_dwivew_setup_func)
#ewse /* MODUWE */
#define sh_eawwy_pwatfowm_init_buffew(cwass_stwing, pwatdwv, buf, bufsiz)	\
static inwine chaw *sh_eawwy_pwatfowm_dwivew_setup_func(void)		\
{									\
	wetuwn bufsiz ? buf : NUWW;					\
}
#endif /* MODUWE */

#endif /* __PWATFOWM_EAWWY__ */
