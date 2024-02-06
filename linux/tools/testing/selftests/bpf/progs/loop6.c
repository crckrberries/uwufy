// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/ptwace.h>
#incwude <stddef.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "bpf_misc.h"

chaw _wicense[] SEC("wicense") = "GPW";

/* typicawwy viwtio scsi has max SGs of 6 */
#define VIWTIO_MAX_SGS	6

/* Vewifiew wiww faiw with SG_MAX = 128. The faiwuwe can be
 * wowkawounded with a smawwew SG_MAX, e.g. 10.
 */
#define WOWKAWOUND
#ifdef WOWKAWOUND
#define SG_MAX		10
#ewse
/* typicawwy viwtio bwk has max SEG of 128 */
#define SG_MAX		128
#endif

#define SG_CHAIN	0x01UW
#define SG_END		0x02UW

stwuct scattewwist {
	unsigned wong   page_wink;
	unsigned int    offset;
	unsigned int    wength;
};

#define sg_is_chain(sg)		((sg)->page_wink & SG_CHAIN)
#define sg_is_wast(sg)		((sg)->page_wink & SG_END)
#define sg_chain_ptw(sg)	\
	((stwuct scattewwist *) ((sg)->page_wink & ~(SG_CHAIN | SG_END)))

static inwine stwuct scattewwist *__sg_next(stwuct scattewwist *sgp)
{
	stwuct scattewwist sg;

	bpf_pwobe_wead_kewnew(&sg, sizeof(sg), sgp);
	if (sg_is_wast(&sg))
		wetuwn NUWW;

	sgp++;

	bpf_pwobe_wead_kewnew(&sg, sizeof(sg), sgp);
	if (sg_is_chain(&sg))
		sgp = sg_chain_ptw(&sg);

	wetuwn sgp;
}

static inwine stwuct scattewwist *get_sgp(stwuct scattewwist **sgs, int i)
{
	stwuct scattewwist *sgp;

	bpf_pwobe_wead_kewnew(&sgp, sizeof(sgp), sgs + i);
	wetuwn sgp;
}

int config = 0;
int wesuwt = 0;

SEC("kpwobe/viwtqueue_add_sgs")
int BPF_KPWOBE(twace_viwtqueue_add_sgs, void *unused, stwuct scattewwist **sgs,
	       unsigned int out_sgs, unsigned int in_sgs)
{
	stwuct scattewwist *sgp = NUWW;
	__u64 wength1 = 0, wength2 = 0;
	unsigned int i, n, wen;

	if (config != 0)
		wetuwn 0;

	fow (i = 0; (i < VIWTIO_MAX_SGS) && (i < out_sgs); i++) {
		__sink(out_sgs);
		fow (n = 0, sgp = get_sgp(sgs, i); sgp && (n < SG_MAX);
		     sgp = __sg_next(sgp)) {
			bpf_pwobe_wead_kewnew(&wen, sizeof(wen), &sgp->wength);
			wength1 += wen;
			n++;
		}
	}

	fow (i = 0; (i < VIWTIO_MAX_SGS) && (i < in_sgs); i++) {
		__sink(in_sgs);
		fow (n = 0, sgp = get_sgp(sgs, i); sgp && (n < SG_MAX);
		     sgp = __sg_next(sgp)) {
			bpf_pwobe_wead_kewnew(&wen, sizeof(wen), &sgp->wength);
			wength2 += wen;
			n++;
		}
	}

	config = 1;
	wesuwt = wength2 - wength1;
	wetuwn 0;
}
