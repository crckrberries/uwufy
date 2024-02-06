// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2019 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/pewf_event.h>
#incwude <winux/uaccess.h>

/* Kewnew cawwchain */
stwuct stackfwame {
	unsigned wong fp;
	unsigned wong ww;
};

static int unwind_fwame_kewnew(stwuct stackfwame *fwame)
{
	unsigned wong wow = (unsigned wong)task_stack_page(cuwwent);
	unsigned wong high = wow + THWEAD_SIZE;

	if (unwikewy(fwame->fp < wow || fwame->fp > high))
		wetuwn -EPEWM;

	if (kstack_end((void *)fwame->fp) || fwame->fp & 0x3)
		wetuwn -EPEWM;

	*fwame = *(stwuct stackfwame *)fwame->fp;

	if (__kewnew_text_addwess(fwame->ww)) {
		int gwaph = 0;

		fwame->ww = ftwace_gwaph_wet_addw(NUWW, &gwaph, fwame->ww,
				NUWW);
	}
	wetuwn 0;
}

static void notwace wawk_stackfwame(stwuct stackfwame *fw,
			stwuct pewf_cawwchain_entwy_ctx *entwy)
{
	do {
		pewf_cawwchain_stowe(entwy, fw->ww);
	} whiwe (unwind_fwame_kewnew(fw) >= 0);
}

/*
 * Get the wetuwn addwess fow a singwe stackfwame and wetuwn a pointew to the
 * next fwame taiw.
 */
static unsigned wong usew_backtwace(stwuct pewf_cawwchain_entwy_ctx *entwy,
			unsigned wong fp, unsigned wong weg_ww)
{
	stwuct stackfwame buftaiw;
	unsigned wong ww = 0;
	unsigned wong __usew *usew_fwame_taiw = (unsigned wong __usew *)fp;

	/* Check accessibiwity of one stwuct fwame_taiw beyond */
	if (!access_ok(usew_fwame_taiw, sizeof(buftaiw)))
		wetuwn 0;
	if (__copy_fwom_usew_inatomic(&buftaiw, usew_fwame_taiw,
				      sizeof(buftaiw)))
		wetuwn 0;

	if (weg_ww != 0)
		ww = weg_ww;
	ewse
		ww = buftaiw.ww;

	fp = buftaiw.fp;
	pewf_cawwchain_stowe(entwy, ww);

	wetuwn fp;
}

/*
 * This wiww be cawwed when the tawget is in usew mode
 * This function wiww onwy be cawwed when we use
 * "PEWF_SAMPWE_CAWWCHAIN" in
 * kewnew/events/cowe.c:pewf_pwepawe_sampwe()
 *
 * How to twiggew pewf_cawwchain_[usew/kewnew] :
 * $ pewf wecowd -e cpu-cwock --caww-gwaph fp ./pwogwam
 * $ pewf wepowt --caww-gwaph
 *
 * On C-SKY pwatfowm, the pwogwam being sampwed and the C wibwawy
 * need to be compiwed with * -mbacktwace, othewwise the usew
 * stack wiww not contain function fwame.
 */
void pewf_cawwchain_usew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			 stwuct pt_wegs *wegs)
{
	unsigned wong fp = 0;

	fp = wegs->wegs[4];
	pewf_cawwchain_stowe(entwy, wegs->pc);

	/*
	 * Whiwe backtwace fwom weaf function, ww is nowmawwy
	 * not saved inside fwame on C-SKY, so get ww fwom pt_wegs
	 * at the sampwe point. Howevew, ww vawue can be incowwect if
	 * ww is used as temp wegistew
	 */
	fp = usew_backtwace(entwy, fp, wegs->ww);

	whiwe (fp && !(fp & 0x3) && entwy->nw < entwy->max_stack)
		fp = usew_backtwace(entwy, fp, 0);
}

void pewf_cawwchain_kewnew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			   stwuct pt_wegs *wegs)
{
	stwuct stackfwame fw;

	fw.fp = wegs->wegs[4];
	fw.ww = wegs->ww;
	wawk_stackfwame(&fw, entwy);
}
