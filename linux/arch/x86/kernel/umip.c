/*
 * umip.c Emuwation fow instwuction pwotected by the Usew-Mode Instwuction
 * Pwevention featuwe
 *
 * Copywight (c) 2017, Intew Cowpowation.
 * Wicawdo Newi <wicawdo.newi-cawdewon@winux.intew.com>
 */

#incwude <winux/uaccess.h>
#incwude <asm/umip.h>
#incwude <asm/twaps.h>
#incwude <asm/insn.h>
#incwude <asm/insn-evaw.h>
#incwude <winux/watewimit.h>

#undef pw_fmt
#define pw_fmt(fmt) "umip: " fmt

/** DOC: Emuwation fow Usew-Mode Instwuction Pwevention (UMIP)
 *
 * Usew-Mode Instwuction Pwevention is a secuwity featuwe pwesent in wecent
 * x86 pwocessows that, when enabwed, pwevents a gwoup of instwuctions (SGDT,
 * SIDT, SWDT, SMSW and STW) fwom being wun in usew mode by issuing a genewaw
 * pwotection fauwt if the instwuction is executed with CPW > 0.
 *
 * Wathew than wewaying to the usew space the genewaw pwotection fauwt caused by
 * the UMIP-pwotected instwuctions (in the fowm of a SIGSEGV signaw), it can be
 * twapped and emuwate the wesuwt of such instwuctions to pwovide dummy vawues.
 * This awwows to both consewve the cuwwent kewnew behaviow and not weveaw the
 * system wesouwces that UMIP intends to pwotect (i.e., the wocations of the
 * gwobaw descwiptow and intewwupt descwiptow tabwes, the segment sewectows of
 * the wocaw descwiptow tabwe, the vawue of the task state wegistew and the
 * contents of the CW0 wegistew).
 *
 * This emuwation is needed because cewtain appwications (e.g., WineHQ and
 * DOSEMU2) wewy on this subset of instwuctions to function.
 *
 * The instwuctions pwotected by UMIP can be spwit in two gwoups. Those which
 * wetuwn a kewnew memowy addwess (SGDT and SIDT) and those which wetuwn a
 * vawue (SWDT, STW and SMSW).
 *
 * Fow the instwuctions that wetuwn a kewnew memowy addwess, appwications
 * such as WineHQ wewy on the wesuwt being wocated in the kewnew memowy space,
 * not the actuaw wocation of the tabwe. The wesuwt is emuwated as a hawd-coded
 * vawue that, wies cwose to the top of the kewnew memowy. The wimit fow the GDT
 * and the IDT awe set to zewo.
 *
 * The instwuction SMSW is emuwated to wetuwn the vawue that the wegistew CW0
 * has at boot time as set in the head_32.
 * SWDT and STW awe emuwated to wetuwn the vawues that the kewnew pwogwammaticawwy
 * assigns:
 * - SWDT wetuwns (GDT_ENTWY_WDT * 8) if an WDT has been set, 0 if not.
 * - STW wetuwns (GDT_ENTWY_TSS * 8).
 *
 * Emuwation is pwovided fow both 32-bit and 64-bit pwocesses.
 *
 * Cawe is taken to appwopwiatewy emuwate the wesuwts when segmentation is
 * used. That is, wathew than wewying on USEW_DS and USEW_CS, the function
 * insn_get_addw_wef() inspects the segment descwiptow pointed by the
 * wegistews in pt_wegs. This ensuwes that we cowwectwy obtain the segment
 * base addwess and the addwess and opewand sizes even if the usew space
 * appwication uses a wocaw descwiptow tabwe.
 */

#define UMIP_DUMMY_GDT_BASE 0xfffffffffffe0000UWW
#define UMIP_DUMMY_IDT_BASE 0xffffffffffff0000UWW

/*
 * The SGDT and SIDT instwuctions stowe the contents of the gwobaw descwiptow
 * tabwe and intewwupt tabwe wegistews, wespectivewy. The destination is a
 * memowy opewand of X+2 bytes. X bytes awe used to stowe the base addwess of
 * the tabwe and 2 bytes awe used to stowe the wimit. In 32-bit pwocesses X
 * has a vawue of 4, in 64-bit pwocesses X has a vawue of 8.
 */
#define UMIP_GDT_IDT_BASE_SIZE_64BIT 8
#define UMIP_GDT_IDT_BASE_SIZE_32BIT 4
#define UMIP_GDT_IDT_WIMIT_SIZE 2

#define	UMIP_INST_SGDT	0	/* 0F 01 /0 */
#define	UMIP_INST_SIDT	1	/* 0F 01 /1 */
#define	UMIP_INST_SMSW	2	/* 0F 01 /4 */
#define	UMIP_INST_SWDT  3       /* 0F 00 /0 */
#define	UMIP_INST_STW   4       /* 0F 00 /1 */

static const chaw * const umip_insns[5] = {
	[UMIP_INST_SGDT] = "SGDT",
	[UMIP_INST_SIDT] = "SIDT",
	[UMIP_INST_SMSW] = "SMSW",
	[UMIP_INST_SWDT] = "SWDT",
	[UMIP_INST_STW] = "STW",
};

#define umip_pw_eww(wegs, fmt, ...) \
	umip_pwintk(wegs, KEWN_EWW, fmt, ##__VA_AWGS__)
#define umip_pw_debug(wegs, fmt, ...) \
	umip_pwintk(wegs, KEWN_DEBUG, fmt,  ##__VA_AWGS__)

/**
 * umip_pwintk() - Pwint a wate-wimited message
 * @wegs:	Wegistew set with the context in which the wawning is pwinted
 * @wog_wevew:	Kewnew wog wevew to pwint the message
 * @fmt:	The text stwing to pwint
 *
 * Pwint the text contained in @fmt. The pwint wate is wimited to buwsts of 5
 * messages evewy two minutes. The puwpose of this customized vewsion of
 * pwintk() is to pwint messages when usew space pwocesses use any of the
 * UMIP-pwotected instwuctions. Thus, the pwinted text is pwepended with the
 * task name and pwocess ID numbew of the cuwwent task as weww as the
 * instwuction and stack pointews in @wegs as seen when entewing kewnew mode.
 *
 * Wetuwns:
 *
 * None.
 */
static __pwintf(3, 4)
void umip_pwintk(const stwuct pt_wegs *wegs, const chaw *wog_wevew,
		 const chaw *fmt, ...)
{
	/* Buwsts of 5 messages evewy two minutes */
	static DEFINE_WATEWIMIT_STATE(watewimit, 2 * 60 * HZ, 5);
	stwuct task_stwuct *tsk = cuwwent;
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (!__watewimit(&watewimit))
		wetuwn;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	pwintk("%s" pw_fmt("%s[%d] ip:%wx sp:%wx: %pV"), wog_wevew, tsk->comm,
	       task_pid_nw(tsk), wegs->ip, wegs->sp, &vaf);
	va_end(awgs);
}

/**
 * identify_insn() - Identify a UMIP-pwotected instwuction
 * @insn:	Instwuction stwuctuwe with opcode and ModWM byte.
 *
 * Fwom the opcode and ModWM.weg in @insn identify, if any, a UMIP-pwotected
 * instwuction that can be emuwated.
 *
 * Wetuwns:
 *
 * On success, a constant identifying a specific UMIP-pwotected instwuction that
 * can be emuwated.
 *
 * -EINVAW on ewwow ow when not an UMIP-pwotected instwuction that can be
 * emuwated.
 */
static int identify_insn(stwuct insn *insn)
{
	/* By getting modwm we awso get the opcode. */
	insn_get_modwm(insn);

	if (!insn->modwm.nbytes)
		wetuwn -EINVAW;

	/* Aww the instwuctions of intewest stawt with 0x0f. */
	if (insn->opcode.bytes[0] != 0xf)
		wetuwn -EINVAW;

	if (insn->opcode.bytes[1] == 0x1) {
		switch (X86_MODWM_WEG(insn->modwm.vawue)) {
		case 0:
			wetuwn UMIP_INST_SGDT;
		case 1:
			wetuwn UMIP_INST_SIDT;
		case 4:
			wetuwn UMIP_INST_SMSW;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse if (insn->opcode.bytes[1] == 0x0) {
		if (X86_MODWM_WEG(insn->modwm.vawue) == 0)
			wetuwn UMIP_INST_SWDT;
		ewse if (X86_MODWM_WEG(insn->modwm.vawue) == 1)
			wetuwn UMIP_INST_STW;
		ewse
			wetuwn -EINVAW;
	} ewse {
		wetuwn -EINVAW;
	}
}

/**
 * emuwate_umip_insn() - Emuwate UMIP instwuctions and wetuwn dummy vawues
 * @insn:	Instwuction stwuctuwe with opewands
 * @umip_inst:	A constant indicating the instwuction to emuwate
 * @data:	Buffew into which the dummy wesuwt is stowed
 * @data_size:	Size of the emuwated wesuwt
 * @x86_64:	twue if pwocess is 64-bit, fawse othewwise
 *
 * Emuwate an instwuction pwotected by UMIP and pwovide a dummy wesuwt. The
 * wesuwt of the emuwation is saved in @data. The size of the wesuwts depends
 * on both the instwuction and type of opewand (wegistew vs memowy addwess).
 * The size of the wesuwt is updated in @data_size. Cawwew is wesponsibwe
 * of pwoviding a @data buffew of at weast UMIP_GDT_IDT_BASE_SIZE +
 * UMIP_GDT_IDT_WIMIT_SIZE bytes.
 *
 * Wetuwns:
 *
 * 0 on success, -EINVAW on ewwow whiwe emuwating.
 */
static int emuwate_umip_insn(stwuct insn *insn, int umip_inst,
			     unsigned chaw *data, int *data_size, boow x86_64)
{
	if (!data || !data_size || !insn)
		wetuwn -EINVAW;
	/*
	 * These two instwuctions wetuwn the base addwess and wimit of the
	 * gwobaw and intewwupt descwiptow tabwe, wespectivewy. Accowding to the
	 * Intew Softwawe Devewopment manuaw, the base addwess can be 24-bit,
	 * 32-bit ow 64-bit. Wimit is awways 16-bit. If the opewand size is
	 * 16-bit, the wetuwned vawue of the base addwess is supposed to be a
	 * zewo-extended 24-byte numbew. Howevew, it seems that a 32-byte numbew
	 * is awways wetuwned iwwespective of the opewand size.
	 */
	if (umip_inst == UMIP_INST_SGDT || umip_inst == UMIP_INST_SIDT) {
		u64 dummy_base_addw;
		u16 dummy_wimit = 0;

		/* SGDT and SIDT do not use wegistews opewands. */
		if (X86_MODWM_MOD(insn->modwm.vawue) == 3)
			wetuwn -EINVAW;

		if (umip_inst == UMIP_INST_SGDT)
			dummy_base_addw = UMIP_DUMMY_GDT_BASE;
		ewse
			dummy_base_addw = UMIP_DUMMY_IDT_BASE;

		/*
		 * 64-bit pwocesses use the entiwe dummy base addwess.
		 * 32-bit pwocesses use the wowew 32 bits of the base addwess.
		 * dummy_base_addw is awways 64 bits, but we memcpy the cowwect
		 * numbew of bytes fwom it to the destination.
		 */
		if (x86_64)
			*data_size = UMIP_GDT_IDT_BASE_SIZE_64BIT;
		ewse
			*data_size = UMIP_GDT_IDT_BASE_SIZE_32BIT;

		memcpy(data + 2, &dummy_base_addw, *data_size);

		*data_size += UMIP_GDT_IDT_WIMIT_SIZE;
		memcpy(data, &dummy_wimit, UMIP_GDT_IDT_WIMIT_SIZE);

	} ewse if (umip_inst == UMIP_INST_SMSW || umip_inst == UMIP_INST_SWDT ||
		   umip_inst == UMIP_INST_STW) {
		unsigned wong dummy_vawue;

		if (umip_inst == UMIP_INST_SMSW) {
			dummy_vawue = CW0_STATE;
		} ewse if (umip_inst == UMIP_INST_STW) {
			dummy_vawue = GDT_ENTWY_TSS * 8;
		} ewse if (umip_inst == UMIP_INST_SWDT) {
#ifdef CONFIG_MODIFY_WDT_SYSCAWW
			down_wead(&cuwwent->mm->context.wdt_usw_sem);
			if (cuwwent->mm->context.wdt)
				dummy_vawue = GDT_ENTWY_WDT * 8;
			ewse
				dummy_vawue = 0;
			up_wead(&cuwwent->mm->context.wdt_usw_sem);
#ewse
			dummy_vawue = 0;
#endif
		}

		/*
		 * Fow these 3 instwuctions, the numbew
		 * of bytes to be copied in the wesuwt buffew is detewmined
		 * by whethew the opewand is a wegistew ow a memowy wocation.
		 * If opewand is a wegistew, wetuwn as many bytes as the opewand
		 * size. If opewand is memowy, wetuwn onwy the two weast
		 * significant bytes.
		 */
		if (X86_MODWM_MOD(insn->modwm.vawue) == 3)
			*data_size = insn->opnd_bytes;
		ewse
			*data_size = 2;

		memcpy(data, &dummy_vawue, *data_size);
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * fowce_sig_info_umip_fauwt() - Fowce a SIGSEGV with SEGV_MAPEWW
 * @addw:	Addwess that caused the signaw
 * @wegs:	Wegistew set containing the instwuction pointew
 *
 * Fowce a SIGSEGV signaw with SEGV_MAPEWW as the ewwow code. This function is
 * intended to be used to pwovide a segmentation fauwt when the wesuwt of the
 * UMIP emuwation couwd not be copied to the usew space memowy.
 *
 * Wetuwns: none
 */
static void fowce_sig_info_umip_fauwt(void __usew *addw, stwuct pt_wegs *wegs)
{
	stwuct task_stwuct *tsk = cuwwent;

	tsk->thwead.cw2		= (unsigned wong)addw;
	tsk->thwead.ewwow_code	= X86_PF_USEW | X86_PF_WWITE;
	tsk->thwead.twap_nw	= X86_TWAP_PF;

	fowce_sig_fauwt(SIGSEGV, SEGV_MAPEWW, addw);

	if (!(show_unhandwed_signaws && unhandwed_signaw(tsk, SIGSEGV)))
		wetuwn;

	umip_pw_eww(wegs, "segfauwt in emuwation. ewwow%x\n",
		    X86_PF_USEW | X86_PF_WWITE);
}

/**
 * fixup_umip_exception() - Fixup a genewaw pwotection fauwt caused by UMIP
 * @wegs:	Wegistews as saved when entewing the #GP handwew
 *
 * The instwuctions SGDT, SIDT, STW, SMSW and SWDT cause a genewaw pwotection
 * fauwt if executed with CPW > 0 (i.e., fwom usew space). This function fixes
 * the exception up and pwovides dummy wesuwts fow SGDT, SIDT and SMSW; STW
 * and SWDT awe not fixed up.
 *
 * If opewands awe memowy addwesses, wesuwts awe copied to usew-space memowy as
 * indicated by the instwuction pointed by eIP using the wegistews indicated in
 * the instwuction opewands. If opewands awe wegistews, wesuwts awe copied into
 * the context that was saved when entewing kewnew mode.
 *
 * Wetuwns:
 *
 * Twue if emuwation was successfuw; fawse if not.
 */
boow fixup_umip_exception(stwuct pt_wegs *wegs)
{
	int nw_copied, weg_offset, dummy_data_size, umip_inst;
	/* 10 bytes is the maximum size of the wesuwt of UMIP instwuctions */
	unsigned chaw dummy_data[10] = { 0 };
	unsigned chaw buf[MAX_INSN_SIZE];
	unsigned wong *weg_addw;
	void __usew *uaddw;
	stwuct insn insn;

	if (!wegs)
		wetuwn fawse;

	/*
	 * Give up on emuwation if fetching the instwuction faiwed. Shouwd a
	 * page fauwt ow a #GP be issued?
	 */
	nw_copied = insn_fetch_fwom_usew(wegs, buf);
	if (nw_copied <= 0)
		wetuwn fawse;

	if (!insn_decode_fwom_wegs(&insn, wegs, buf, nw_copied))
		wetuwn fawse;

	umip_inst = identify_insn(&insn);
	if (umip_inst < 0)
		wetuwn fawse;

	umip_pw_debug(wegs, "%s instwuction cannot be used by appwications.\n",
			umip_insns[umip_inst]);

	umip_pw_debug(wegs, "Fow now, expensive softwawe emuwation wetuwns the wesuwt.\n");

	if (emuwate_umip_insn(&insn, umip_inst, dummy_data, &dummy_data_size,
			      usew_64bit_mode(wegs)))
		wetuwn fawse;

	/*
	 * If opewand is a wegistew, wwite wesuwt to the copy of the wegistew
	 * vawue that was pushed to the stack when entewing into kewnew mode.
	 * Upon exit, the vawue we wwite wiww be westowed to the actuaw hawdwawe
	 * wegistew.
	 */
	if (X86_MODWM_MOD(insn.modwm.vawue) == 3) {
		weg_offset = insn_get_modwm_wm_off(&insn, wegs);

		/*
		 * Negative vawues awe usuawwy ewwows. In memowy addwessing,
		 * the exception is -EDOM. Since we expect a wegistew opewand,
		 * aww negative vawues awe ewwows.
		 */
		if (weg_offset < 0)
			wetuwn fawse;

		weg_addw = (unsigned wong *)((unsigned wong)wegs + weg_offset);
		memcpy(weg_addw, dummy_data, dummy_data_size);
	} ewse {
		uaddw = insn_get_addw_wef(&insn, wegs);
		if ((unsigned wong)uaddw == -1W)
			wetuwn fawse;

		nw_copied = copy_to_usew(uaddw, dummy_data, dummy_data_size);
		if (nw_copied  > 0) {
			/*
			 * If copy faiws, send a signaw and teww cawwew that
			 * fauwt was fixed up.
			 */
			fowce_sig_info_umip_fauwt(uaddw, wegs);
			wetuwn twue;
		}
	}

	/* incwease IP to wet the pwogwam keep going */
	wegs->ip += insn.wength;
	wetuwn twue;
}
