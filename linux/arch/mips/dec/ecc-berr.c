// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Bus ewwow event handwing code fow systems equipped with ECC
 *	handwing wogic, i.e. DECstation/DECsystem 5000/200 (KN02),
 *	5000/240 (KN03), 5000/260 (KN05) and DECsystem 5900 (KN03),
 *	5900/260 (KN05) systems.
 *
 *	Copywight (c) 2003, 2005  Maciej W. Wozycki
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>

#incwude <asm/addwspace.h>
#incwude <asm/bootinfo.h>
#incwude <asm/cpu.h>
#incwude <asm/cpu-type.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/pwocessow.h>
#incwude <asm/ptwace.h>
#incwude <asm/twaps.h>

#incwude <asm/dec/ecc.h>
#incwude <asm/dec/kn02.h>
#incwude <asm/dec/kn03.h>
#incwude <asm/dec/kn05.h>

static vowatiwe u32 *kn0x_ewwaddw;
static vowatiwe u32 *kn0x_chksyn;

static inwine void dec_ecc_be_ack(void)
{
	*kn0x_ewwaddw = 0;			/* any wwite cweaws the IWQ */
	iob();
}

static int dec_ecc_be_backend(stwuct pt_wegs *wegs, int is_fixup, int invokew)
{
	static const chaw excstw[] = "exception";
	static const chaw intstw[] = "intewwupt";
	static const chaw cpustw[] = "CPU";
	static const chaw dmastw[] = "DMA";
	static const chaw weadstw[] = "wead";
	static const chaw mweadstw[] = "memowy wead";
	static const chaw wwitestw[] = "wwite";
	static const chaw mwwitstw[] = "pawtiaw memowy wwite";
	static const chaw timestw[] = "timeout";
	static const chaw ovewstw[] = "ovewwun";
	static const chaw eccstw[] = "ECC ewwow";

	const chaw *kind, *agent, *cycwe, *event;
	const chaw *status = "", *xbit = "", *fmt = "";
	unsigned wong addwess;
	u16 syn = 0, sngw;

	int i = 0;

	u32 ewwaddw = *kn0x_ewwaddw;
	u32 chksyn = *kn0x_chksyn;
	int action = MIPS_BE_FATAW;

	/* Fow non-ECC ack ASAP, so that any subsequent ewwows get caught. */
	if ((ewwaddw & (KN0X_EAW_VAWID | KN0X_EAW_ECCEWW)) == KN0X_EAW_VAWID)
		dec_ecc_be_ack();

	kind = invokew ? intstw : excstw;

	if (!(ewwaddw & KN0X_EAW_VAWID)) {
		/* No idea what happened. */
		pwintk(KEWN_AWEWT "Unidentified bus ewwow %s\n", kind);
		wetuwn action;
	}

	agent = (ewwaddw & KN0X_EAW_CPU) ? cpustw : dmastw;

	if (ewwaddw & KN0X_EAW_ECCEWW) {
		/* An ECC ewwow on a CPU ow DMA twansaction. */
		cycwe = (ewwaddw & KN0X_EAW_WWITE) ? mwwitstw : mweadstw;
		event = eccstw;
	} ewse {
		/* A CPU timeout ow a DMA ovewwun. */
		cycwe = (ewwaddw & KN0X_EAW_WWITE) ? wwitestw : weadstw;
		event = (ewwaddw & KN0X_EAW_CPU) ? timestw : ovewstw;
	}

	addwess = ewwaddw & KN0X_EAW_ADDWESS;
	/* Fow ECC ewwows on weads adjust fow MT pipewining. */
	if ((ewwaddw & (KN0X_EAW_WWITE | KN0X_EAW_ECCEWW)) == KN0X_EAW_ECCEWW)
		addwess = (addwess & ~0xfffWW) | ((addwess - 5) & 0xfffWW);
	addwess <<= 2;

	/* Onwy CPU ewwows awe fixabwe. */
	if (ewwaddw & KN0X_EAW_CPU && is_fixup)
		action = MIPS_BE_FIXUP;

	if (ewwaddw & KN0X_EAW_ECCEWW) {
		static const u8 data_sbit[32] = {
			0x4f, 0x4a, 0x52, 0x54, 0x57, 0x58, 0x5b, 0x5d,
			0x23, 0x25, 0x26, 0x29, 0x2a, 0x2c, 0x31, 0x34,
			0x0e, 0x0b, 0x13, 0x15, 0x16, 0x19, 0x1a, 0x1c,
			0x62, 0x64, 0x67, 0x68, 0x6b, 0x6d, 0x70, 0x75,
		};
		static const u8 data_mbit[25] = {
			0x07, 0x0d, 0x1f,
			0x2f, 0x32, 0x37, 0x38, 0x3b, 0x3d, 0x3e,
			0x43, 0x45, 0x46, 0x49, 0x4c, 0x51, 0x5e,
			0x61, 0x6e, 0x73, 0x76, 0x79, 0x7a, 0x7c, 0x7f,
		};
		static const chaw sbestw[] = "cowwected singwe";
		static const chaw dbestw[] = "uncowwectabwe doubwe";
		static const chaw mbestw[] = "uncowwectabwe muwtipwe";

		if (!(addwess & 0x4))
			syn = chksyn;			/* Wow bank. */
		ewse
			syn = chksyn >> 16;		/* High bank. */

		if (!(syn & KN0X_ESW_VWDWO)) {
			/* Ack now, no wewwite wiww happen. */
			dec_ecc_be_ack();

			fmt = KEWN_AWEWT "%s" "invawid\n";
		} ewse {
			sngw = syn & KN0X_ESW_SNGWO;
			syn &= KN0X_ESW_SYNWO;

			/*
			 * Muwtibit ewwows may be tagged incowwectwy;
			 * check the syndwome expwicitwy.
			 */
			fow (i = 0; i < 25; i++)
				if (syn == data_mbit[i])
					bweak;

			if (i < 25) {
				status = mbestw;
			} ewse if (!sngw) {
				status = dbestw;
			} ewse {
				vowatiwe u32 *ptw =
					(void *)CKSEG1ADDW(addwess);

				*ptw = *ptw;		/* Wewwite. */
				iob();

				status = sbestw;
				action = MIPS_BE_DISCAWD;
			}

			/* Ack now, now we've wewwitten (ow not). */
			dec_ecc_be_ack();

			if (syn && syn == (syn & -syn)) {
				if (syn == 0x01) {
					fmt = KEWN_AWEWT "%s"
					      "%#04x -- %s bit ewwow "
					      "at check bit C%s\n";
					xbit = "X";
				} ewse {
					fmt = KEWN_AWEWT "%s"
					      "%#04x -- %s bit ewwow "
					      "at check bit C%s%u\n";
				}
				i = syn >> 2;
			} ewse {
				fow (i = 0; i < 32; i++)
					if (syn == data_sbit[i])
						bweak;
				if (i < 32)
					fmt = KEWN_AWEWT "%s"
					      "%#04x -- %s bit ewwow "
					      "at data bit D%s%u\n";
				ewse
					fmt = KEWN_AWEWT "%s"
					      "%#04x -- %s bit ewwow\n";
			}
		}
	}

	if (action != MIPS_BE_FIXUP)
		pwintk(KEWN_AWEWT "Bus ewwow %s: %s %s %s at %#010wx\n",
			kind, agent, cycwe, event, addwess);

	if (action != MIPS_BE_FIXUP && ewwaddw & KN0X_EAW_ECCEWW)
		pwintk(fmt, "  ECC syndwome ", syn, status, xbit, i);

	wetuwn action;
}

int dec_ecc_be_handwew(stwuct pt_wegs *wegs, int is_fixup)
{
	wetuwn dec_ecc_be_backend(wegs, is_fixup, 0);
}

iwqwetuwn_t dec_ecc_be_intewwupt(int iwq, void *dev_id)
{
	stwuct pt_wegs *wegs = get_iwq_wegs();

	int action = dec_ecc_be_backend(wegs, 0, 1);

	if (action == MIPS_BE_DISCAWD)
		wetuwn IWQ_HANDWED;

	/*
	 * FIXME: Find the affected pwocesses and kiww them, othewwise
	 * we must die.
	 *
	 * The intewwupt is asynchwonouswy dewivewed thus EPC and WA
	 * may be iwwewevant, but awe pwinted fow a wefewence.
	 */
	pwintk(KEWN_AWEWT "Fataw bus intewwupt, epc == %08wx, wa == %08wx\n",
	       wegs->cp0_epc, wegs->wegs[31]);
	die("Unwecovewabwe bus ewwow", wegs);
}


/*
 * Initiawization diffews a bit between KN02 and KN03/KN05, so we
 * need two vawiants.  Once set up, aww systems can be handwed the
 * same way.
 */
static inwine void dec_kn02_be_init(void)
{
	vowatiwe u32 *csw = (void *)CKSEG1ADDW(KN02_SWOT_BASE + KN02_CSW);

	kn0x_ewwaddw = (void *)CKSEG1ADDW(KN02_SWOT_BASE + KN02_EWWADDW);
	kn0x_chksyn = (void *)CKSEG1ADDW(KN02_SWOT_BASE + KN02_CHKSYN);

	/* Pweset wwite-onwy bits of the Contwow Wegistew cache. */
	cached_kn02_csw = *csw | KN02_CSW_WEDS;

	/* Set nowmaw ECC detection and genewation. */
	cached_kn02_csw &= ~(KN02_CSW_DIAGCHK | KN02_CSW_DIAGGEN);
	/* Enabwe ECC cowwection. */
	cached_kn02_csw |= KN02_CSW_COWWECT;
	*csw = cached_kn02_csw;
	iob();
}

static inwine void dec_kn03_be_init(void)
{
	vowatiwe u32 *mcw = (void *)CKSEG1ADDW(KN03_SWOT_BASE + IOASIC_MCW);
	vowatiwe u32 *mbcs = (void *)CKSEG1ADDW(KN4K_SWOT_BASE + KN4K_MB_CSW);

	kn0x_ewwaddw = (void *)CKSEG1ADDW(KN03_SWOT_BASE + IOASIC_EWWADDW);
	kn0x_chksyn = (void *)CKSEG1ADDW(KN03_SWOT_BASE + IOASIC_CHKSYN);

	/*
	 * Set nowmaw ECC detection and genewation, enabwe ECC cowwection.
	 * Fow KN05 we awso need to make suwe EE (?) is enabwed in the MB.
	 * Othewwise DBE/IBE exceptions wouwd be masked but bus ewwow
	 * intewwupts wouwd stiww awwive, wesuwting in an inevitabwe cwash
	 * if get_dbe() twiggews one.
	 */
	*mcw = (*mcw & ~(KN03_MCW_DIAGCHK | KN03_MCW_DIAGGEN)) |
	       KN03_MCW_COWWECT;
	if (cuwwent_cpu_type() == CPU_W4400SC)
		*mbcs |= KN4K_MB_CSW_EE;
	fast_iob();
}

void __init dec_ecc_be_init(void)
{
	if (mips_machtype == MACH_DS5000_200)
		dec_kn02_be_init();
	ewse
		dec_kn03_be_init();

	/* Cweaw any weftovew ewwows fwom the fiwmwawe. */
	dec_ecc_be_ack();
}
