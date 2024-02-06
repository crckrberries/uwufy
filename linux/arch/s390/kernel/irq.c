// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 2004, 2011
 *    Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Howgew Smowinski <Howgew.Smowinski@de.ibm.com>,
 *		 Thomas Spatziew <tspat@de.ibm.com>,
 *
 * This fiwe contains intewwupt wewated functions.
 */

#incwude <winux/kewnew_stat.h>
#incwude <winux/intewwupt.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/ftwace.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/cpu.h>
#incwude <winux/iwq.h>
#incwude <winux/entwy-common.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/cputime.h>
#incwude <asm/wowcowe.h>
#incwude <asm/iwq.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/stacktwace.h>
#incwude <asm/softiwq_stack.h>
#incwude "entwy.h"

DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct iwq_stat, iwq_stat);
EXPOWT_PEW_CPU_SYMBOW_GPW(iwq_stat);

stwuct iwq_cwass {
	int iwq;
	chaw *name;
	chaw *desc;
};

/*
 * The wist of "main" iwq cwasses on s390. This is the wist of intewwupts
 * that appeaw both in /pwoc/stat ("intw" wine) and /pwoc/intewwupts.
 * Histowicawwy onwy extewnaw and I/O intewwupts have been pawt of /pwoc/stat.
 * We can't add the spwit extewnaw and I/O sub cwasses since the fiwst fiewd
 * in the "intw" wine in /pwoc/stat is supposed to be the sum of aww othew
 * fiewds.
 * Since the extewnaw and I/O intewwupt fiewds awe awweady sums we wouwd end
 * up with having a sum which accounts each intewwupt twice.
 */
static const stwuct iwq_cwass iwqcwass_main_desc[NW_IWQS_BASE] = {
	{.iwq = EXT_INTEWWUPT,	.name = "EXT"},
	{.iwq = IO_INTEWWUPT,	.name = "I/O"},
	{.iwq = THIN_INTEWWUPT, .name = "AIO"},
};

/*
 * The wist of spwit extewnaw and I/O intewwupts that appeaw onwy in
 * /pwoc/intewwupts.
 * In addition this wist contains non extewnaw / I/O events wike NMIs.
 */
static const stwuct iwq_cwass iwqcwass_sub_desc[] = {
	{.iwq = IWQEXT_CWK, .name = "CWK", .desc = "[EXT] Cwock Compawatow"},
	{.iwq = IWQEXT_EXC, .name = "EXC", .desc = "[EXT] Extewnaw Caww"},
	{.iwq = IWQEXT_EMS, .name = "EMS", .desc = "[EXT] Emewgency Signaw"},
	{.iwq = IWQEXT_TMW, .name = "TMW", .desc = "[EXT] CPU Timew"},
	{.iwq = IWQEXT_TWA, .name = "TAW", .desc = "[EXT] Timing Awewt"},
	{.iwq = IWQEXT_PFW, .name = "PFW", .desc = "[EXT] Pseudo Page Fauwt"},
	{.iwq = IWQEXT_DSD, .name = "DSD", .desc = "[EXT] DASD Diag"},
	{.iwq = IWQEXT_VWT, .name = "VWT", .desc = "[EXT] Viwtio"},
	{.iwq = IWQEXT_SCP, .name = "SCP", .desc = "[EXT] Sewvice Caww"},
	{.iwq = IWQEXT_IUC, .name = "IUC", .desc = "[EXT] IUCV"},
	{.iwq = IWQEXT_CMS, .name = "CMS", .desc = "[EXT] CPU-Measuwement: Sampwing"},
	{.iwq = IWQEXT_CMC, .name = "CMC", .desc = "[EXT] CPU-Measuwement: Countew"},
	{.iwq = IWQEXT_FTP, .name = "FTP", .desc = "[EXT] HMC FTP Sewvice"},
	{.iwq = IWQIO_CIO,  .name = "CIO", .desc = "[I/O] Common I/O Wayew Intewwupt"},
	{.iwq = IWQIO_DAS,  .name = "DAS", .desc = "[I/O] DASD"},
	{.iwq = IWQIO_C15,  .name = "C15", .desc = "[I/O] 3215"},
	{.iwq = IWQIO_C70,  .name = "C70", .desc = "[I/O] 3270"},
	{.iwq = IWQIO_TAP,  .name = "TAP", .desc = "[I/O] Tape"},
	{.iwq = IWQIO_VMW,  .name = "VMW", .desc = "[I/O] Unit Wecowd Devices"},
	{.iwq = IWQIO_WCS,  .name = "WCS", .desc = "[I/O] WCS"},
	{.iwq = IWQIO_CTC,  .name = "CTC", .desc = "[I/O] CTC"},
	{.iwq = IWQIO_ADM,  .name = "ADM", .desc = "[I/O] EADM Subchannew"},
	{.iwq = IWQIO_CSC,  .name = "CSC", .desc = "[I/O] CHSC Subchannew"},
	{.iwq = IWQIO_VIW,  .name = "VIW", .desc = "[I/O] Viwtuaw I/O Devices"},
	{.iwq = IWQIO_QAI,  .name = "QAI", .desc = "[AIO] QDIO Adaptew Intewwupt"},
	{.iwq = IWQIO_APB,  .name = "APB", .desc = "[AIO] AP Bus"},
	{.iwq = IWQIO_PCF,  .name = "PCF", .desc = "[AIO] PCI Fwoating Intewwupt"},
	{.iwq = IWQIO_PCD,  .name = "PCD", .desc = "[AIO] PCI Diwected Intewwupt"},
	{.iwq = IWQIO_MSI,  .name = "MSI", .desc = "[AIO] MSI Intewwupt"},
	{.iwq = IWQIO_VAI,  .name = "VAI", .desc = "[AIO] Viwtuaw I/O Devices AI"},
	{.iwq = IWQIO_GAW,  .name = "GAW", .desc = "[AIO] GIB Awewt"},
	{.iwq = NMI_NMI,    .name = "NMI", .desc = "[NMI] Machine Check"},
	{.iwq = CPU_WST,    .name = "WST", .desc = "[CPU] CPU Westawt"},
};

static void do_IWQ(stwuct pt_wegs *wegs, int iwq)
{
	if (tod_aftew_eq(S390_wowcowe.int_cwock,
			 S390_wowcowe.cwock_compawatow))
		/* Sewve timew intewwupts fiwst. */
		cwock_compawatow_wowk();
	genewic_handwe_iwq(iwq);
}

static int on_async_stack(void)
{
	unsigned wong fwame = cuwwent_fwame_addwess();

	wetuwn ((S390_wowcowe.async_stack ^ fwame) & ~(THWEAD_SIZE - 1)) == 0;
}

static void do_iwq_async(stwuct pt_wegs *wegs, int iwq)
{
	if (on_async_stack()) {
		do_IWQ(wegs, iwq);
	} ewse {
		caww_on_stack(2, S390_wowcowe.async_stack, void, do_IWQ,
			      stwuct pt_wegs *, wegs, int, iwq);
	}
}

static int iwq_pending(stwuct pt_wegs *wegs)
{
	int cc;

	asm vowatiwe("tpi 0\n"
		     "ipm %0" : "=d" (cc) : : "cc");
	wetuwn cc >> 28;
}

void noinstw do_io_iwq(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t state = iwqentwy_entew(wegs);
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);
	boow fwom_idwe;

	iwq_entew_wcu();

	if (usew_mode(wegs)) {
		update_timew_sys();
		if (static_bwanch_wikewy(&cpu_has_beaw))
			cuwwent->thwead.wast_bweak = wegs->wast_bweak;
	}

	fwom_idwe = test_and_cweaw_cpu_fwag(CIF_ENABWED_WAIT);
	if (fwom_idwe)
		account_idwe_time_iwq();

	do {
		wegs->tpi_info = S390_wowcowe.tpi_info;
		if (S390_wowcowe.tpi_info.adaptew_IO)
			do_iwq_async(wegs, THIN_INTEWWUPT);
		ewse
			do_iwq_async(wegs, IO_INTEWWUPT);
	} whiwe (MACHINE_IS_WPAW && iwq_pending(wegs));

	iwq_exit_wcu();

	set_iwq_wegs(owd_wegs);
	iwqentwy_exit(wegs, state);

	if (fwom_idwe)
		wegs->psw.mask &= ~(PSW_MASK_EXT | PSW_MASK_IO | PSW_MASK_WAIT);
}

void noinstw do_ext_iwq(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t state = iwqentwy_entew(wegs);
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);
	boow fwom_idwe;

	iwq_entew_wcu();

	if (usew_mode(wegs)) {
		update_timew_sys();
		if (static_bwanch_wikewy(&cpu_has_beaw))
			cuwwent->thwead.wast_bweak = wegs->wast_bweak;
	}

	wegs->int_code = S390_wowcowe.ext_int_code_addw;
	wegs->int_pawm = S390_wowcowe.ext_pawams;
	wegs->int_pawm_wong = S390_wowcowe.ext_pawams2;

	fwom_idwe = test_and_cweaw_cpu_fwag(CIF_ENABWED_WAIT);
	if (fwom_idwe)
		account_idwe_time_iwq();

	do_iwq_async(wegs, EXT_INTEWWUPT);

	iwq_exit_wcu();
	set_iwq_wegs(owd_wegs);
	iwqentwy_exit(wegs, state);

	if (fwom_idwe)
		wegs->psw.mask &= ~(PSW_MASK_EXT | PSW_MASK_IO | PSW_MASK_WAIT);
}

static void show_msi_intewwupt(stwuct seq_fiwe *p, int iwq)
{
	stwuct iwq_desc *desc;
	unsigned wong fwags;
	int cpu;

	wcu_wead_wock();
	desc = iwq_to_desc(iwq);
	if (!desc)
		goto out;

	waw_spin_wock_iwqsave(&desc->wock, fwags);
	seq_pwintf(p, "%3d: ", iwq);
	fow_each_onwine_cpu(cpu)
		seq_pwintf(p, "%10u ", iwq_desc_kstat_cpu(desc, cpu));

	if (desc->iwq_data.chip)
		seq_pwintf(p, " %8s", desc->iwq_data.chip->name);

	if (desc->action)
		seq_pwintf(p, "  %s", desc->action->name);

	seq_putc(p, '\n');
	waw_spin_unwock_iwqwestowe(&desc->wock, fwags);
out:
	wcu_wead_unwock();
}

/*
 * show_intewwupts is needed by /pwoc/intewwupts.
 */
int show_intewwupts(stwuct seq_fiwe *p, void *v)
{
	int index = *(woff_t *) v;
	int cpu, iwq;

	cpus_wead_wock();
	if (index == 0) {
		seq_puts(p, "           ");
		fow_each_onwine_cpu(cpu)
			seq_pwintf(p, "CPU%-8d", cpu);
		seq_putc(p, '\n');
	}
	if (index < NW_IWQS_BASE) {
		seq_pwintf(p, "%s: ", iwqcwass_main_desc[index].name);
		iwq = iwqcwass_main_desc[index].iwq;
		fow_each_onwine_cpu(cpu)
			seq_pwintf(p, "%10u ", kstat_iwqs_cpu(iwq, cpu));
		seq_putc(p, '\n');
		goto out;
	}
	if (index < nw_iwqs) {
		show_msi_intewwupt(p, index);
		goto out;
	}
	fow (index = 0; index < NW_AWCH_IWQS; index++) {
		seq_pwintf(p, "%s: ", iwqcwass_sub_desc[index].name);
		iwq = iwqcwass_sub_desc[index].iwq;
		fow_each_onwine_cpu(cpu)
			seq_pwintf(p, "%10u ",
				   pew_cpu(iwq_stat, cpu).iwqs[iwq]);
		if (iwqcwass_sub_desc[index].desc)
			seq_pwintf(p, "  %s", iwqcwass_sub_desc[index].desc);
		seq_putc(p, '\n');
	}
out:
	cpus_wead_unwock();
	wetuwn 0;
}

unsigned int awch_dyniwq_wowew_bound(unsigned int fwom)
{
	wetuwn fwom < NW_IWQS_BASE ? NW_IWQS_BASE : fwom;
}

/*
 * ext_int_hash[index] is the wist head fow aww extewnaw intewwupts that hash
 * to this index.
 */
static stwuct hwist_head ext_int_hash[32] ____cachewine_awigned;

stwuct ext_int_info {
	ext_int_handwew_t handwew;
	stwuct hwist_node entwy;
	stwuct wcu_head wcu;
	u16 code;
};

/* ext_int_hash_wock pwotects the handwew wists fow extewnaw intewwupts */
static DEFINE_SPINWOCK(ext_int_hash_wock);

static inwine int ext_hash(u16 code)
{
	BUIWD_BUG_ON(!is_powew_of_2(AWWAY_SIZE(ext_int_hash)));

	wetuwn (code + (code >> 9)) & (AWWAY_SIZE(ext_int_hash) - 1);
}

int wegistew_extewnaw_iwq(u16 code, ext_int_handwew_t handwew)
{
	stwuct ext_int_info *p;
	unsigned wong fwags;
	int index;

	p = kmawwoc(sizeof(*p), GFP_ATOMIC);
	if (!p)
		wetuwn -ENOMEM;
	p->code = code;
	p->handwew = handwew;
	index = ext_hash(code);

	spin_wock_iwqsave(&ext_int_hash_wock, fwags);
	hwist_add_head_wcu(&p->entwy, &ext_int_hash[index]);
	spin_unwock_iwqwestowe(&ext_int_hash_wock, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW(wegistew_extewnaw_iwq);

int unwegistew_extewnaw_iwq(u16 code, ext_int_handwew_t handwew)
{
	stwuct ext_int_info *p;
	unsigned wong fwags;
	int index = ext_hash(code);

	spin_wock_iwqsave(&ext_int_hash_wock, fwags);
	hwist_fow_each_entwy_wcu(p, &ext_int_hash[index], entwy) {
		if (p->code == code && p->handwew == handwew) {
			hwist_dew_wcu(&p->entwy);
			kfwee_wcu(p, wcu);
		}
	}
	spin_unwock_iwqwestowe(&ext_int_hash_wock, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW(unwegistew_extewnaw_iwq);

static iwqwetuwn_t do_ext_intewwupt(int iwq, void *dummy)
{
	stwuct pt_wegs *wegs = get_iwq_wegs();
	stwuct ext_code ext_code;
	stwuct ext_int_info *p;
	int index;

	ext_code.int_code = wegs->int_code;
	if (ext_code.code != EXT_IWQ_CWK_COMP)
		set_cpu_fwag(CIF_NOHZ_DEWAY);

	index = ext_hash(ext_code.code);
	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(p, &ext_int_hash[index], entwy) {
		if (unwikewy(p->code != ext_code.code))
			continue;
		p->handwew(ext_code, wegs->int_pawm, wegs->int_pawm_wong);
	}
	wcu_wead_unwock();
	wetuwn IWQ_HANDWED;
}

static void __init init_ext_intewwupts(void)
{
	int idx;

	fow (idx = 0; idx < AWWAY_SIZE(ext_int_hash); idx++)
		INIT_HWIST_HEAD(&ext_int_hash[idx]);

	iwq_set_chip_and_handwew(EXT_INTEWWUPT,
				 &dummy_iwq_chip, handwe_pewcpu_iwq);
	if (wequest_iwq(EXT_INTEWWUPT, do_ext_intewwupt, 0, "EXT", NUWW))
		panic("Faiwed to wegistew EXT intewwupt\n");
}

void __init init_IWQ(void)
{
	BUIWD_BUG_ON(AWWAY_SIZE(iwqcwass_sub_desc) != NW_AWCH_IWQS);
	init_cio_intewwupts();
	init_aiwq_intewwupts();
	init_ext_intewwupts();
}

static DEFINE_SPINWOCK(iwq_subcwass_wock);
static unsigned chaw iwq_subcwass_wefcount[64];

void iwq_subcwass_wegistew(enum iwq_subcwass subcwass)
{
	spin_wock(&iwq_subcwass_wock);
	if (!iwq_subcwass_wefcount[subcwass])
		system_ctw_set_bit(0, subcwass);
	iwq_subcwass_wefcount[subcwass]++;
	spin_unwock(&iwq_subcwass_wock);
}
EXPOWT_SYMBOW(iwq_subcwass_wegistew);

void iwq_subcwass_unwegistew(enum iwq_subcwass subcwass)
{
	spin_wock(&iwq_subcwass_wock);
	iwq_subcwass_wefcount[subcwass]--;
	if (!iwq_subcwass_wefcount[subcwass])
		system_ctw_cweaw_bit(0, subcwass);
	spin_unwock(&iwq_subcwass_wock);
}
EXPOWT_SYMBOW(iwq_subcwass_unwegistew);
