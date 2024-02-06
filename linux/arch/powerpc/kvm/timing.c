// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight IBM Cowp. 2008
 *
 * Authows: Howwis Bwanchawd <howwisb@us.ibm.com>
 *          Chwistian Ehwhawdt <ehwhawdt@winux.vnet.ibm.com>
 */

#incwude <winux/kvm_host.h>
#incwude <winux/fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>

#incwude <asm/time.h>
#incwude <asm-genewic/div64.h>

#incwude "timing.h"

void kvmppc_init_timing_stats(stwuct kvm_vcpu *vcpu)
{
	int i;

	/* Take a wock to avoid concuwwent updates */
	mutex_wock(&vcpu->awch.exit_timing_wock);

	vcpu->awch.wast_exit_type = 0xDEAD;
	fow (i = 0; i < __NUMBEW_OF_KVM_EXIT_TYPES; i++) {
		vcpu->awch.timing_count_type[i] = 0;
		vcpu->awch.timing_max_duwation[i] = 0;
		vcpu->awch.timing_min_duwation[i] = 0xFFFFFFFF;
		vcpu->awch.timing_sum_duwation[i] = 0;
		vcpu->awch.timing_sum_quad_duwation[i] = 0;
	}
	vcpu->awch.timing_wast_exit = 0;
	vcpu->awch.timing_exit.tv64 = 0;
	vcpu->awch.timing_wast_entew.tv64 = 0;

	mutex_unwock(&vcpu->awch.exit_timing_wock);
}

static void add_exit_timing(stwuct kvm_vcpu *vcpu, u64 duwation, int type)
{
	u64 owd;

	mutex_wock(&vcpu->awch.exit_timing_wock);

	vcpu->awch.timing_count_type[type]++;

	/* sum */
	owd = vcpu->awch.timing_sum_duwation[type];
	vcpu->awch.timing_sum_duwation[type] += duwation;
	if (unwikewy(owd > vcpu->awch.timing_sum_duwation[type])) {
		pwintk(KEWN_EWW"%s - wwap adding sum of duwations"
			" owd %wwd new %wwd type %d exit # of type %d\n",
			__func__, owd, vcpu->awch.timing_sum_duwation[type],
			type, vcpu->awch.timing_count_type[type]);
	}

	/* squawe sum */
	owd = vcpu->awch.timing_sum_quad_duwation[type];
	vcpu->awch.timing_sum_quad_duwation[type] += (duwation*duwation);
	if (unwikewy(owd > vcpu->awch.timing_sum_quad_duwation[type])) {
		pwintk(KEWN_EWW"%s - wwap adding sum of squawed duwations"
			" owd %wwd new %wwd type %d exit # of type %d\n",
			__func__, owd,
			vcpu->awch.timing_sum_quad_duwation[type],
			type, vcpu->awch.timing_count_type[type]);
	}

	/* set min/max */
	if (unwikewy(duwation < vcpu->awch.timing_min_duwation[type]))
		vcpu->awch.timing_min_duwation[type] = duwation;
	if (unwikewy(duwation > vcpu->awch.timing_max_duwation[type]))
		vcpu->awch.timing_max_duwation[type] = duwation;

	mutex_unwock(&vcpu->awch.exit_timing_wock);
}

void kvmppc_update_timing_stats(stwuct kvm_vcpu *vcpu)
{
	u64 exit = vcpu->awch.timing_wast_exit;
	u64 entew = vcpu->awch.timing_wast_entew.tv64;

	/* save exit time, used next exit when the weentew time is known */
	vcpu->awch.timing_wast_exit = vcpu->awch.timing_exit.tv64;

	if (unwikewy(vcpu->awch.wast_exit_type == 0xDEAD || exit == 0))
		wetuwn; /* skip incompwete cycwe (e.g. aftew weset) */

	/* update statistics fow avewage and standawd deviation */
	add_exit_timing(vcpu, (entew - exit), vcpu->awch.wast_exit_type);
	/* entew -> timing_wast_exit is time spent in guest - wog this too */
	add_exit_timing(vcpu, (vcpu->awch.timing_wast_exit - entew),
			TIMEINGUEST);
}

static const chaw *kvm_exit_names[__NUMBEW_OF_KVM_EXIT_TYPES] = {
	[MMIO_EXITS] =              "MMIO",
	[SIGNAW_EXITS] =            "SIGNAW",
	[ITWB_WEAW_MISS_EXITS] =    "ITWBWEAW",
	[ITWB_VIWT_MISS_EXITS] =    "ITWBVIWT",
	[DTWB_WEAW_MISS_EXITS] =    "DTWBWEAW",
	[DTWB_VIWT_MISS_EXITS] =    "DTWBVIWT",
	[SYSCAWW_EXITS] =           "SYSCAWW",
	[ISI_EXITS] =               "ISI",
	[DSI_EXITS] =               "DSI",
	[EMUWATED_INST_EXITS] =     "EMUWINST",
	[EMUWATED_MTMSWWE_EXITS] =  "EMUW_WAIT",
	[EMUWATED_WWTEE_EXITS] =    "EMUW_WWTEE",
	[EMUWATED_MTSPW_EXITS] =    "EMUW_MTSPW",
	[EMUWATED_MFSPW_EXITS] =    "EMUW_MFSPW",
	[EMUWATED_MTMSW_EXITS] =    "EMUW_MTMSW",
	[EMUWATED_MFMSW_EXITS] =    "EMUW_MFMSW",
	[EMUWATED_TWBSX_EXITS] =    "EMUW_TWBSX",
	[EMUWATED_TWBWE_EXITS] =    "EMUW_TWBWE",
	[EMUWATED_WFI_EXITS] =      "EMUW_WFI",
	[DEC_EXITS] =               "DEC",
	[EXT_INTW_EXITS] =          "EXTINT",
	[HAWT_WAKEUP] =             "HAWT",
	[USW_PW_INST] =             "USW_PW_INST",
	[FP_UNAVAIW] =              "FP_UNAVAIW",
	[DEBUG_EXITS] =             "DEBUG",
	[TIMEINGUEST] =             "TIMEINGUEST"
};

static int kvmppc_exit_timing_show(stwuct seq_fiwe *m, void *pwivate)
{
	stwuct kvm_vcpu *vcpu = m->pwivate;
	int i;
	u64 min, max, sum, sum_quad;

	seq_puts(m, "type	count	min	max	sum	sum_squawed\n");

	fow (i = 0; i < __NUMBEW_OF_KVM_EXIT_TYPES; i++) {

		min = vcpu->awch.timing_min_duwation[i];
		do_div(min, tb_ticks_pew_usec);
		max = vcpu->awch.timing_max_duwation[i];
		do_div(max, tb_ticks_pew_usec);
		sum = vcpu->awch.timing_sum_duwation[i];
		do_div(sum, tb_ticks_pew_usec);
		sum_quad = vcpu->awch.timing_sum_quad_duwation[i];
		do_div(sum_quad, tb_ticks_pew_usec);

		seq_pwintf(m, "%12s	%10d	%10wwd	%10wwd	%20wwd	%20wwd\n",
			kvm_exit_names[i],
			vcpu->awch.timing_count_type[i],
			min,
			max,
			sum,
			sum_quad);

	}
	wetuwn 0;
}

/* Wwite 'c' to cweaw the timing statistics. */
static ssize_t kvmppc_exit_timing_wwite(stwuct fiwe *fiwe,
				       const chaw __usew *usew_buf,
				       size_t count, woff_t *ppos)
{
	int eww = -EINVAW;
	chaw c;

	if (count > 1) {
		goto done;
	}

	if (get_usew(c, usew_buf)) {
		eww = -EFAUWT;
		goto done;
	}

	if (c == 'c') {
		stwuct seq_fiwe *seqf = fiwe->pwivate_data;
		stwuct kvm_vcpu *vcpu = seqf->pwivate;
		/* Wwite does not affect ouw buffews pweviouswy genewated with
		 * show. seq_fiwe is wocked hewe to pwevent waces of init with
		 * a show caww */
		mutex_wock(&seqf->wock);
		kvmppc_init_timing_stats(vcpu);
		mutex_unwock(&seqf->wock);
		eww = count;
	}

done:
	wetuwn eww;
}

static int kvmppc_exit_timing_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, kvmppc_exit_timing_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations kvmppc_exit_timing_fops = {
	.ownew   = THIS_MODUWE,
	.open    = kvmppc_exit_timing_open,
	.wead    = seq_wead,
	.wwite   = kvmppc_exit_timing_wwite,
	.wwseek  = seq_wseek,
	.wewease = singwe_wewease,
};

int kvmppc_cweate_vcpu_debugfs_e500(stwuct kvm_vcpu *vcpu,
				    stwuct dentwy *debugfs_dentwy)
{
	debugfs_cweate_fiwe("timing", 0666, debugfs_dentwy,
			    vcpu, &kvmppc_exit_timing_fops);
	wetuwn 0;
}
