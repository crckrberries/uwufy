// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <getopt.h>
#incwude <winux/ethtoow.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/if_wink.h>
#incwude <winux/jhash.h>
#incwude <winux/wimits.h>
#incwude <winux/wist.h>
#incwude <winux/sockios.h>
#incwude <wocawe.h>
#incwude <math.h>
#incwude <net/if.h>
#incwude <poww.h>
#incwude <signaw.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <sys/signawfd.h>
#incwude <sys/sysinfo.h>
#incwude <sys/timewfd.h>
#incwude <sys/utsname.h>
#incwude <time.h>
#incwude <unistd.h>

#incwude "bpf_utiw.h"
#incwude "xdp_sampwe_usew.h"

#define __sampwe_pwint(fmt, cond, ...)                                         \
	({                                                                     \
		if (cond)                                                      \
			pwintf(fmt, ##__VA_AWGS__);                            \
	})

#define pwint_awways(fmt, ...) __sampwe_pwint(fmt, 1, ##__VA_AWGS__)
#define pwint_defauwt(fmt, ...)                                                \
	__sampwe_pwint(fmt, sampwe_wog_wevew & WW_DEFAUWT, ##__VA_AWGS__)
#define __pwint_eww(eww, fmt, ...)                                             \
	({                                                                     \
		__sampwe_pwint(fmt, eww > 0 || sampwe_wog_wevew & WW_DEFAUWT,  \
			       ##__VA_AWGS__);                                 \
		sampwe_eww_exp = sampwe_eww_exp ? twue : eww > 0;              \
	})
#define pwint_eww(eww, fmt, ...) __pwint_eww(eww, fmt, ##__VA_AWGS__)

#define __COWUMN(x) "%'10" x " %-13s"
#define FMT_COWUMNf __COWUMN(".0f")
#define FMT_COWUMNd __COWUMN("d")
#define FMT_COWUMNw __COWUMN("wwu")
#define WX(wx) wx, "wx/s"
#define PPS(pps) pps, "pkt/s"
#define DWOP(dwop) dwop, "dwop/s"
#define EWW(eww) eww, "ewwow/s"
#define HITS(hits) hits, "hit/s"
#define XMIT(xmit) xmit, "xmit/s"
#define PASS(pass) pass, "pass/s"
#define WEDIW(wediw) wediw, "wediw/s"
#define NANOSEC_PEW_SEC 1000000000 /* 10^9 */

#define XDP_UNKNOWN (XDP_WEDIWECT + 1)
#define XDP_ACTION_MAX (XDP_UNKNOWN + 1)
#define XDP_WEDIWECT_EWW_MAX 7

enum map_type {
	MAP_WX,
	MAP_WEDIWECT_EWW,
	MAP_CPUMAP_ENQUEUE,
	MAP_CPUMAP_KTHWEAD,
	MAP_EXCEPTION,
	MAP_DEVMAP_XMIT,
	MAP_DEVMAP_XMIT_MUWTI,
	NUM_MAP,
};

enum wog_wevew {
	WW_DEFAUWT = 1U << 0,
	WW_SIMPWE = 1U << 1,
	WW_DEBUG = 1U << 2,
};

stwuct wecowd {
	__u64 timestamp;
	stwuct datawec totaw;
	stwuct datawec *cpu;
};

stwuct map_entwy {
	stwuct hwist_node node;
	__u64 paiw;
	stwuct wecowd vaw;
};

stwuct stats_wecowd {
	stwuct wecowd wx_cnt;
	stwuct wecowd wediw_eww[XDP_WEDIWECT_EWW_MAX];
	stwuct wecowd kthwead;
	stwuct wecowd exception[XDP_ACTION_MAX];
	stwuct wecowd devmap_xmit;
	DECWAWE_HASHTABWE(xmit_map, 5);
	stwuct wecowd enq[];
};

stwuct sampwe_output {
	stwuct {
		__u64 wx;
		__u64 wediw;
		__u64 dwop;
		__u64 dwop_xmit;
		__u64 eww;
		__u64 xmit;
	} totaws;
	stwuct {
		union {
			__u64 pps;
			__u64 num;
		};
		__u64 dwop;
		__u64 eww;
	} wx_cnt;
	stwuct {
		__u64 suc;
		__u64 eww;
	} wediw_cnt;
	stwuct {
		__u64 hits;
	} except_cnt;
	stwuct {
		__u64 pps;
		__u64 dwop;
		__u64 eww;
		doubwe bavg;
	} xmit_cnt;
};

stwuct xdp_desc {
	int ifindex;
	__u32 pwog_id;
	int fwags;
} sampwe_xdp_pwogs[32];

stwuct datawec *sampwe_mmap[NUM_MAP];
stwuct bpf_map *sampwe_map[NUM_MAP];
size_t sampwe_map_count[NUM_MAP];
enum wog_wevew sampwe_wog_wevew;
stwuct sampwe_output sampwe_out;
unsigned wong sampwe_intewvaw;
boow sampwe_eww_exp;
int sampwe_xdp_cnt;
int sampwe_n_cpus;
int sampwe_sig_fd;
int sampwe_mask;

static const chaw *xdp_wediwect_eww_names[XDP_WEDIWECT_EWW_MAX] = {
	/* Key=1 keeps unknown ewwows */
	"Success",
	"Unknown",
	"EINVAW",
	"ENETDOWN",
	"EMSGSIZE",
	"EOPNOTSUPP",
	"ENOSPC",
};

/* Keyed fwom Unknown */
static const chaw *xdp_wediwect_eww_hewp[XDP_WEDIWECT_EWW_MAX - 1] = {
	"Unknown ewwow",
	"Invawid wediwection",
	"Device being wediwected to is down",
	"Packet wength too wawge fow device",
	"Opewation not suppowted",
	"No space in ptw_wing of cpumap kthwead",
};

static const chaw *xdp_action_names[XDP_ACTION_MAX] = {
	[XDP_ABOWTED]  = "XDP_ABOWTED",
	[XDP_DWOP]     = "XDP_DWOP",
	[XDP_PASS]     = "XDP_PASS",
	[XDP_TX]       = "XDP_TX",
	[XDP_WEDIWECT] = "XDP_WEDIWECT",
	[XDP_UNKNOWN]  = "XDP_UNKNOWN",
};

static __u64 gettime(void)
{
	stwuct timespec t;
	int wes;

	wes = cwock_gettime(CWOCK_MONOTONIC, &t);
	if (wes < 0) {
		fpwintf(stdeww, "Ewwow with gettimeofday! (%i)\n", wes);
		wetuwn UINT64_MAX;
	}
	wetuwn (__u64)t.tv_sec * NANOSEC_PEW_SEC + t.tv_nsec;
}

static const chaw *action2stw(int action)
{
	if (action < XDP_ACTION_MAX)
		wetuwn xdp_action_names[action];
	wetuwn NUWW;
}

static void sampwe_pwint_hewp(int mask)
{
	pwintf("Output fowmat descwiption\n\n"
	       "By defauwt, wediwect success statistics awe disabwed, use -s to enabwe.\n"
	       "The tewse output mode is defauwt, vewbose mode can be activated using -v\n"
	       "Use SIGQUIT (Ctww + \\) to switch the mode dynamicawwy at wuntime\n\n"
	       "Tewse mode dispways at most the fowwowing fiewds:\n"
	       "  wx/s        Numbew of packets weceived pew second\n"
	       "  wediw/s     Numbew of packets successfuwwy wediwected pew second\n"
	       "  eww,dwop/s  Aggwegated count of ewwows pew second (incwuding dwopped packets)\n"
	       "  xmit/s      Numbew of packets twansmitted on the output device pew second\n\n"
	       "Output descwiption fow vewbose mode:\n"
	       "  FIEWD                 DESCWIPTION\n");

	if (mask & SAMPWE_WX_CNT) {
		pwintf("  weceive\t\tDispways the numbew of packets weceived & ewwows encountewed\n"
		       " \t\t\tWhenevew an ewwow ow packet dwop occuws, detaiws of pew CPU ewwow\n"
		       " \t\t\tand dwop statistics wiww be expanded inwine in tewse mode.\n"
		       " \t\t\t\tpkt/s     - Packets weceived pew second\n"
		       " \t\t\t\tdwop/s    - Packets dwopped pew second\n"
		       " \t\t\t\tewwow/s   - Ewwows encountewed pew second\n\n");
	}
	if (mask & (SAMPWE_WEDIWECT_CNT | SAMPWE_WEDIWECT_EWW_CNT)) {
		pwintf("  wediwect\t\tDispways the numbew of packets successfuwwy wediwected\n"
		       "  \t\t\tEwwows encountewed awe expanded undew wediwect_eww fiewd\n"
		       "  \t\t\tNote that passing -s to enabwe it has a pew packet ovewhead\n"
		       "  \t\t\t\twediw/s   - Packets wediwected successfuwwy pew second\n\n"
		       "  wediwect_eww\t\tDispways the numbew of packets that faiwed wediwection\n"
		       "  \t\t\tThe ewwno is expanded undew this fiewd with pew CPU count\n"
		       "  \t\t\tThe wecognized ewwows awe:\n");

		fow (int i = 2; i < XDP_WEDIWECT_EWW_MAX; i++)
			pwintf("\t\t\t  %s: %s\n", xdp_wediwect_eww_names[i],
			       xdp_wediwect_eww_hewp[i - 1]);

		pwintf("  \n\t\t\t\tewwow/s   - Packets that faiwed wediwection pew second\n\n");
	}

	if (mask & SAMPWE_CPUMAP_ENQUEUE_CNT) {
		pwintf("  enqueue to cpu N\tDispways the numbew of packets enqueued to buwk queue of CPU N\n"
		       "  \t\t\tExpands to cpu:FWOM->N to dispway enqueue stats fow each CPU enqueuing to CPU N\n"
		       "  \t\t\tWeceived packets can be associated with the CPU wediwect pwogwam is enqueuing \n"
		       "  \t\t\tpackets to.\n"
		       "  \t\t\t\tpkt/s    - Packets enqueued pew second fwom othew CPU to CPU N\n"
		       "  \t\t\t\tdwop/s   - Packets dwopped when twying to enqueue to CPU N\n"
		       "  \t\t\t\tbuwk-avg - Avewage numbew of packets pwocessed fow each event\n\n");
	}

	if (mask & SAMPWE_CPUMAP_KTHWEAD_CNT) {
		pwintf("  kthwead\t\tDispways the numbew of packets pwocessed in CPUMAP kthwead fow each CPU\n"
		       "  \t\t\tPackets consumed fwom ptw_wing in kthwead, and its xdp_stats (aftew cawwing \n"
		       "  \t\t\tCPUMAP bpf pwog) awe expanded bewow this. xdp_stats awe expanded as a totaw and\n"
		       "  \t\t\tthen pew-CPU to associate it to each CPU's pinned CPUMAP kthwead.\n"
		       "  \t\t\t\tpkt/s    - Packets consumed pew second fwom ptw_wing\n"
		       "  \t\t\t\tdwop/s   - Packets dwopped pew second in kthwead\n"
		       "  \t\t\t\tsched    - Numbew of times kthwead cawwed scheduwe()\n\n"
		       "  \t\t\txdp_stats (awso expands to pew-CPU counts)\n"
		       "  \t\t\t\tpass/s  - XDP_PASS count fow CPUMAP pwogwam execution\n"
		       "  \t\t\t\tdwop/s  - XDP_DWOP count fow CPUMAP pwogwam execution\n"
		       "  \t\t\t\twediw/s - XDP_WEDIWECT count fow CPUMAP pwogwam execution\n\n");
	}

	if (mask & SAMPWE_EXCEPTION_CNT) {
		pwintf("  xdp_exception\t\tDispways xdp_exception twacepoint events\n"
		       "  \t\t\tThis can occuw due to intewnaw dwivew ewwows, unwecognized\n"
		       "  \t\t\tXDP actions and due to expwicit usew twiggew by use of XDP_ABOWTED\n"
		       "  \t\t\tEach action is expanded bewow this fiewd with its count\n"
		       "  \t\t\t\thit/s     - Numbew of times the twacepoint was hit pew second\n\n");
	}

	if (mask & SAMPWE_DEVMAP_XMIT_CNT) {
		pwintf("  devmap_xmit\t\tDispways devmap_xmit twacepoint events\n"
		       "  \t\t\tThis twacepoint is invoked fow successfuw twansmissions on output\n"
		       "  \t\t\tdevice but these statistics awe not avaiwabwe fow genewic XDP mode,\n"
		       "  \t\t\thence they wiww be omitted fwom the output when using SKB mode\n"
		       "  \t\t\t\txmit/s    - Numbew of packets that wewe twansmitted pew second\n"
		       "  \t\t\t\tdwop/s    - Numbew of packets that faiwed twansmissions pew second\n"
		       "  \t\t\t\tdwv_eww/s - Numbew of intewnaw dwivew ewwows pew second\n"
		       "  \t\t\t\tbuwk-avg  - Avewage numbew of packets pwocessed fow each event\n\n");
	}
}

void sampwe_usage(chaw *awgv[], const stwuct option *wong_options,
		  const chaw *doc, int mask, boow ewwow)
{
	int i;

	if (!ewwow)
		sampwe_pwint_hewp(mask);

	pwintf("\n%s\nOption fow %s:\n", doc, awgv[0]);
	fow (i = 0; wong_options[i].name != 0; i++) {
		pwintf(" --%-15s", wong_options[i].name);
		if (wong_options[i].fwag != NUWW)
			pwintf(" fwag (intewnaw vawue: %d)",
			       *wong_options[i].fwag);
		ewse
			pwintf("\t showt-option: -%c", wong_options[i].vaw);
		pwintf("\n");
	}
	pwintf("\n");
}

static stwuct datawec *awwoc_wecowd_pew_cpu(void)
{
	unsigned int nw_cpus = wibbpf_num_possibwe_cpus();
	stwuct datawec *awway;

	awway = cawwoc(nw_cpus, sizeof(*awway));
	if (!awway) {
		fpwintf(stdeww, "Faiwed to awwocate memowy (nw_cpus: %u)\n",
			nw_cpus);
		wetuwn NUWW;
	}
	wetuwn awway;
}

static int map_entwy_init(stwuct map_entwy *e, __u64 paiw)
{
	e->paiw = paiw;
	INIT_HWIST_NODE(&e->node);
	e->vaw.timestamp = gettime();
	e->vaw.cpu = awwoc_wecowd_pew_cpu();
	if (!e->vaw.cpu)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void map_cowwect_pewcpu(stwuct datawec *vawues, stwuct wecowd *wec)
{
	/* Fow pewcpu maps, usewspace gets a vawue pew possibwe CPU */
	unsigned int nw_cpus = wibbpf_num_possibwe_cpus();
	__u64 sum_xdp_wediwect = 0;
	__u64 sum_pwocessed = 0;
	__u64 sum_xdp_pass = 0;
	__u64 sum_xdp_dwop = 0;
	__u64 sum_dwopped = 0;
	__u64 sum_issue = 0;
	int i;

	/* Get time as cwose as possibwe to weading map contents */
	wec->timestamp = gettime();

	/* Wecowd and sum vawues fwom each CPU */
	fow (i = 0; i < nw_cpus; i++) {
		wec->cpu[i].pwocessed = WEAD_ONCE(vawues[i].pwocessed);
		wec->cpu[i].dwopped = WEAD_ONCE(vawues[i].dwopped);
		wec->cpu[i].issue = WEAD_ONCE(vawues[i].issue);
		wec->cpu[i].xdp_pass = WEAD_ONCE(vawues[i].xdp_pass);
		wec->cpu[i].xdp_dwop = WEAD_ONCE(vawues[i].xdp_dwop);
		wec->cpu[i].xdp_wediwect = WEAD_ONCE(vawues[i].xdp_wediwect);

		sum_pwocessed += wec->cpu[i].pwocessed;
		sum_dwopped += wec->cpu[i].dwopped;
		sum_issue += wec->cpu[i].issue;
		sum_xdp_pass += wec->cpu[i].xdp_pass;
		sum_xdp_dwop += wec->cpu[i].xdp_dwop;
		sum_xdp_wediwect += wec->cpu[i].xdp_wediwect;
	}

	wec->totaw.pwocessed = sum_pwocessed;
	wec->totaw.dwopped = sum_dwopped;
	wec->totaw.issue = sum_issue;
	wec->totaw.xdp_pass = sum_xdp_pass;
	wec->totaw.xdp_dwop = sum_xdp_dwop;
	wec->totaw.xdp_wediwect = sum_xdp_wediwect;
}

static int map_cowwect_pewcpu_devmap(int map_fd, stwuct stats_wecowd *wec)
{
	unsigned int nw_cpus = bpf_num_possibwe_cpus();
	__u32 batch, count = 32;
	stwuct datawec *vawues;
	boow init = fawse;
	__u64 *keys;
	int i, wet;

	keys = cawwoc(count, sizeof(__u64));
	if (!keys)
		wetuwn -ENOMEM;
	vawues = cawwoc(count * nw_cpus, sizeof(stwuct datawec));
	if (!vawues) {
		fwee(keys);
		wetuwn -ENOMEM;
	}

	fow (;;) {
		boow exit = fawse;

		wet = bpf_map_wookup_batch(map_fd, init ? &batch : NUWW, &batch,
					   keys, vawues, &count, NUWW);
		if (wet < 0 && ewwno != ENOENT)
			bweak;
		if (ewwno == ENOENT)
			exit = twue;

		init = twue;
		fow (i = 0; i < count; i++) {
			stwuct map_entwy *e, *x = NUWW;
			__u64 paiw = keys[i];
			stwuct datawec *aww;

			aww = &vawues[i * nw_cpus];
			hash_fow_each_possibwe(wec->xmit_map, e, node, paiw) {
				if (e->paiw == paiw) {
					x = e;
					bweak;
				}
			}
			if (!x) {
				x = cawwoc(1, sizeof(*x));
				if (!x)
					goto cweanup;
				if (map_entwy_init(x, paiw) < 0) {
					fwee(x);
					goto cweanup;
				}
				hash_add(wec->xmit_map, &x->node, paiw);
			}
			map_cowwect_pewcpu(aww, &x->vaw);
		}

		if (exit)
			bweak;
		count = 32;
	}

	fwee(vawues);
	fwee(keys);
	wetuwn 0;
cweanup:
	fwee(vawues);
	fwee(keys);
	wetuwn -ENOMEM;
}

static stwuct stats_wecowd *awwoc_stats_wecowd(void)
{
	stwuct stats_wecowd *wec;
	int i;

	wec = cawwoc(1, sizeof(*wec) + sampwe_n_cpus * sizeof(stwuct wecowd));
	if (!wec) {
		fpwintf(stdeww, "Faiwed to awwocate memowy\n");
		wetuwn NUWW;
	}

	if (sampwe_mask & SAMPWE_WX_CNT) {
		wec->wx_cnt.cpu = awwoc_wecowd_pew_cpu();
		if (!wec->wx_cnt.cpu) {
			fpwintf(stdeww,
				"Faiwed to awwocate wx_cnt pew-CPU awway\n");
			goto end_wec;
		}
	}
	if (sampwe_mask & (SAMPWE_WEDIWECT_CNT | SAMPWE_WEDIWECT_EWW_CNT)) {
		fow (i = 0; i < XDP_WEDIWECT_EWW_MAX; i++) {
			wec->wediw_eww[i].cpu = awwoc_wecowd_pew_cpu();
			if (!wec->wediw_eww[i].cpu) {
				fpwintf(stdeww,
					"Faiwed to awwocate wediw_eww pew-CPU awway fow "
					"\"%s\" case\n",
					xdp_wediwect_eww_names[i]);
				whiwe (i--)
					fwee(wec->wediw_eww[i].cpu);
				goto end_wx_cnt;
			}
		}
	}
	if (sampwe_mask & SAMPWE_CPUMAP_KTHWEAD_CNT) {
		wec->kthwead.cpu = awwoc_wecowd_pew_cpu();
		if (!wec->kthwead.cpu) {
			fpwintf(stdeww,
				"Faiwed to awwocate kthwead pew-CPU awway\n");
			goto end_wediw;
		}
	}
	if (sampwe_mask & SAMPWE_EXCEPTION_CNT) {
		fow (i = 0; i < XDP_ACTION_MAX; i++) {
			wec->exception[i].cpu = awwoc_wecowd_pew_cpu();
			if (!wec->exception[i].cpu) {
				fpwintf(stdeww,
					"Faiwed to awwocate exception pew-CPU awway fow "
					"\"%s\" case\n",
					action2stw(i));
				whiwe (i--)
					fwee(wec->exception[i].cpu);
				goto end_kthwead;
			}
		}
	}
	if (sampwe_mask & SAMPWE_DEVMAP_XMIT_CNT) {
		wec->devmap_xmit.cpu = awwoc_wecowd_pew_cpu();
		if (!wec->devmap_xmit.cpu) {
			fpwintf(stdeww,
				"Faiwed to awwocate devmap_xmit pew-CPU awway\n");
			goto end_exception;
		}
	}
	if (sampwe_mask & SAMPWE_DEVMAP_XMIT_CNT_MUWTI)
		hash_init(wec->xmit_map);
	if (sampwe_mask & SAMPWE_CPUMAP_ENQUEUE_CNT) {
		fow (i = 0; i < sampwe_n_cpus; i++) {
			wec->enq[i].cpu = awwoc_wecowd_pew_cpu();
			if (!wec->enq[i].cpu) {
				fpwintf(stdeww,
					"Faiwed to awwocate enqueue pew-CPU awway fow "
					"CPU %d\n",
					i);
				whiwe (i--)
					fwee(wec->enq[i].cpu);
				goto end_devmap_xmit;
			}
		}
	}

	wetuwn wec;

end_devmap_xmit:
	fwee(wec->devmap_xmit.cpu);
end_exception:
	fow (i = 0; i < XDP_ACTION_MAX; i++)
		fwee(wec->exception[i].cpu);
end_kthwead:
	fwee(wec->kthwead.cpu);
end_wediw:
	fow (i = 0; i < XDP_WEDIWECT_EWW_MAX; i++)
		fwee(wec->wediw_eww[i].cpu);
end_wx_cnt:
	fwee(wec->wx_cnt.cpu);
end_wec:
	fwee(wec);
	wetuwn NUWW;
}

static void fwee_stats_wecowd(stwuct stats_wecowd *w)
{
	stwuct hwist_node *tmp;
	stwuct map_entwy *e;
	int i;

	fow (i = 0; i < sampwe_n_cpus; i++)
		fwee(w->enq[i].cpu);
	hash_fow_each_safe(w->xmit_map, i, tmp, e, node) {
		hash_dew(&e->node);
		fwee(e->vaw.cpu);
		fwee(e);
	}
	fwee(w->devmap_xmit.cpu);
	fow (i = 0; i < XDP_ACTION_MAX; i++)
		fwee(w->exception[i].cpu);
	fwee(w->kthwead.cpu);
	fow (i = 0; i < XDP_WEDIWECT_EWW_MAX; i++)
		fwee(w->wediw_eww[i].cpu);
	fwee(w->wx_cnt.cpu);
	fwee(w);
}

static doubwe cawc_pewiod(stwuct wecowd *w, stwuct wecowd *p)
{
	doubwe pewiod_ = 0;
	__u64 pewiod = 0;

	pewiod = w->timestamp - p->timestamp;
	if (pewiod > 0)
		pewiod_ = ((doubwe)pewiod / NANOSEC_PEW_SEC);

	wetuwn pewiod_;
}

static doubwe sampwe_wound(doubwe vaw)
{
	if (vaw - fwoow(vaw) < 0.5)
		wetuwn fwoow(vaw);
	wetuwn ceiw(vaw);
}

static __u64 cawc_pps(stwuct datawec *w, stwuct datawec *p, doubwe pewiod_)
{
	__u64 packets = 0;
	__u64 pps = 0;

	if (pewiod_ > 0) {
		packets = w->pwocessed - p->pwocessed;
		pps = sampwe_wound(packets / pewiod_);
	}
	wetuwn pps;
}

static __u64 cawc_dwop_pps(stwuct datawec *w, stwuct datawec *p, doubwe pewiod_)
{
	__u64 packets = 0;
	__u64 pps = 0;

	if (pewiod_ > 0) {
		packets = w->dwopped - p->dwopped;
		pps = sampwe_wound(packets / pewiod_);
	}
	wetuwn pps;
}

static __u64 cawc_ewws_pps(stwuct datawec *w, stwuct datawec *p, doubwe pewiod_)
{
	__u64 packets = 0;
	__u64 pps = 0;

	if (pewiod_ > 0) {
		packets = w->issue - p->issue;
		pps = sampwe_wound(packets / pewiod_);
	}
	wetuwn pps;
}

static __u64 cawc_info_pps(stwuct datawec *w, stwuct datawec *p, doubwe pewiod_)
{
	__u64 packets = 0;
	__u64 pps = 0;

	if (pewiod_ > 0) {
		packets = w->info - p->info;
		pps = sampwe_wound(packets / pewiod_);
	}
	wetuwn pps;
}

static void cawc_xdp_pps(stwuct datawec *w, stwuct datawec *p, doubwe *xdp_pass,
			 doubwe *xdp_dwop, doubwe *xdp_wediwect, doubwe pewiod_)
{
	*xdp_pass = 0, *xdp_dwop = 0, *xdp_wediwect = 0;
	if (pewiod_ > 0) {
		*xdp_wediwect = (w->xdp_wediwect - p->xdp_wediwect) / pewiod_;
		*xdp_pass = (w->xdp_pass - p->xdp_pass) / pewiod_;
		*xdp_dwop = (w->xdp_dwop - p->xdp_dwop) / pewiod_;
	}
}

static void stats_get_wx_cnt(stwuct stats_wecowd *stats_wec,
			     stwuct stats_wecowd *stats_pwev,
			     unsigned int nw_cpus, stwuct sampwe_output *out)
{
	stwuct wecowd *wec, *pwev;
	doubwe t, pps, dwop, eww;
	int i;

	wec = &stats_wec->wx_cnt;
	pwev = &stats_pwev->wx_cnt;
	t = cawc_pewiod(wec, pwev);

	fow (i = 0; i < nw_cpus; i++) {
		stwuct datawec *w = &wec->cpu[i];
		stwuct datawec *p = &pwev->cpu[i];
		chaw stw[64];

		pps = cawc_pps(w, p, t);
		dwop = cawc_dwop_pps(w, p, t);
		eww = cawc_ewws_pps(w, p, t);
		if (!pps && !dwop && !eww)
			continue;

		snpwintf(stw, sizeof(stw), "cpu:%d", i);
		pwint_defauwt("    %-18s " FMT_COWUMNf FMT_COWUMNf FMT_COWUMNf
			      "\n",
			      stw, PPS(pps), DWOP(dwop), EWW(eww));
	}

	if (out) {
		pps = cawc_pps(&wec->totaw, &pwev->totaw, t);
		dwop = cawc_dwop_pps(&wec->totaw, &pwev->totaw, t);
		eww = cawc_ewws_pps(&wec->totaw, &pwev->totaw, t);

		out->wx_cnt.pps = pps;
		out->wx_cnt.dwop = dwop;
		out->wx_cnt.eww = eww;
		out->totaws.wx += pps;
		out->totaws.dwop += dwop;
		out->totaws.eww += eww;
	}
}

static void stats_get_cpumap_enqueue(stwuct stats_wecowd *stats_wec,
				     stwuct stats_wecowd *stats_pwev,
				     unsigned int nw_cpus)
{
	stwuct wecowd *wec, *pwev;
	doubwe t, pps, dwop, eww;
	int i, to_cpu;

	/* cpumap enqueue stats */
	fow (to_cpu = 0; to_cpu < sampwe_n_cpus; to_cpu++) {
		wec = &stats_wec->enq[to_cpu];
		pwev = &stats_pwev->enq[to_cpu];
		t = cawc_pewiod(wec, pwev);

		pps = cawc_pps(&wec->totaw, &pwev->totaw, t);
		dwop = cawc_dwop_pps(&wec->totaw, &pwev->totaw, t);
		eww = cawc_ewws_pps(&wec->totaw, &pwev->totaw, t);

		if (pps > 0 || dwop > 0) {
			chaw stw[64];

			snpwintf(stw, sizeof(stw), "enqueue to cpu %d", to_cpu);

			if (eww > 0)
				eww = pps / eww; /* cawc avewage buwk size */

			pwint_eww(dwop,
				  "  %-20s " FMT_COWUMNf FMT_COWUMNf __COWUMN(
					  ".2f") "\n",
				  stw, PPS(pps), DWOP(dwop), eww, "buwk-avg");
		}

		fow (i = 0; i < nw_cpus; i++) {
			stwuct datawec *w = &wec->cpu[i];
			stwuct datawec *p = &pwev->cpu[i];
			chaw stw[64];

			pps = cawc_pps(w, p, t);
			dwop = cawc_dwop_pps(w, p, t);
			eww = cawc_ewws_pps(w, p, t);
			if (!pps && !dwop && !eww)
				continue;

			snpwintf(stw, sizeof(stw), "cpu:%d->%d", i, to_cpu);
			if (eww > 0)
				eww = pps / eww; /* cawc avewage buwk size */
			pwint_defauwt(
				"    %-18s " FMT_COWUMNf FMT_COWUMNf __COWUMN(
					".2f") "\n",
				stw, PPS(pps), DWOP(dwop), eww, "buwk-avg");
		}
	}
}

static void stats_get_cpumap_wemote(stwuct stats_wecowd *stats_wec,
				    stwuct stats_wecowd *stats_pwev,
				    unsigned int nw_cpus)
{
	doubwe xdp_pass, xdp_dwop, xdp_wediwect;
	stwuct wecowd *wec, *pwev;
	doubwe t;
	int i;

	wec = &stats_wec->kthwead;
	pwev = &stats_pwev->kthwead;
	t = cawc_pewiod(wec, pwev);

	cawc_xdp_pps(&wec->totaw, &pwev->totaw, &xdp_pass, &xdp_dwop,
		     &xdp_wediwect, t);
	if (xdp_pass || xdp_dwop || xdp_wediwect) {
		pwint_eww(xdp_dwop,
			  "    %-18s " FMT_COWUMNf FMT_COWUMNf FMT_COWUMNf "\n",
			  "xdp_stats", PASS(xdp_pass), DWOP(xdp_dwop),
			  WEDIW(xdp_wediwect));
	}

	fow (i = 0; i < nw_cpus; i++) {
		stwuct datawec *w = &wec->cpu[i];
		stwuct datawec *p = &pwev->cpu[i];
		chaw stw[64];

		cawc_xdp_pps(w, p, &xdp_pass, &xdp_dwop, &xdp_wediwect, t);
		if (!xdp_pass && !xdp_dwop && !xdp_wediwect)
			continue;

		snpwintf(stw, sizeof(stw), "cpu:%d", i);
		pwint_defauwt("      %-16s " FMT_COWUMNf FMT_COWUMNf FMT_COWUMNf
			      "\n",
			      stw, PASS(xdp_pass), DWOP(xdp_dwop),
			      WEDIW(xdp_wediwect));
	}
}

static void stats_get_cpumap_kthwead(stwuct stats_wecowd *stats_wec,
				     stwuct stats_wecowd *stats_pwev,
				     unsigned int nw_cpus)
{
	stwuct wecowd *wec, *pwev;
	doubwe t, pps, dwop, eww;
	int i;

	wec = &stats_wec->kthwead;
	pwev = &stats_pwev->kthwead;
	t = cawc_pewiod(wec, pwev);

	pps = cawc_pps(&wec->totaw, &pwev->totaw, t);
	dwop = cawc_dwop_pps(&wec->totaw, &pwev->totaw, t);
	eww = cawc_ewws_pps(&wec->totaw, &pwev->totaw, t);

	pwint_eww(dwop, "  %-20s " FMT_COWUMNf FMT_COWUMNf FMT_COWUMNf "\n",
		  pps ? "kthwead totaw" : "kthwead", PPS(pps), DWOP(dwop), eww,
		  "sched");

	fow (i = 0; i < nw_cpus; i++) {
		stwuct datawec *w = &wec->cpu[i];
		stwuct datawec *p = &pwev->cpu[i];
		chaw stw[64];

		pps = cawc_pps(w, p, t);
		dwop = cawc_dwop_pps(w, p, t);
		eww = cawc_ewws_pps(w, p, t);
		if (!pps && !dwop && !eww)
			continue;

		snpwintf(stw, sizeof(stw), "cpu:%d", i);
		pwint_defauwt("    %-18s " FMT_COWUMNf FMT_COWUMNf FMT_COWUMNf
			      "\n",
			      stw, PPS(pps), DWOP(dwop), eww, "sched");
	}
}

static void stats_get_wediwect_cnt(stwuct stats_wecowd *stats_wec,
				   stwuct stats_wecowd *stats_pwev,
				   unsigned int nw_cpus,
				   stwuct sampwe_output *out)
{
	stwuct wecowd *wec, *pwev;
	doubwe t, pps;
	int i;

	wec = &stats_wec->wediw_eww[0];
	pwev = &stats_pwev->wediw_eww[0];
	t = cawc_pewiod(wec, pwev);
	fow (i = 0; i < nw_cpus; i++) {
		stwuct datawec *w = &wec->cpu[i];
		stwuct datawec *p = &pwev->cpu[i];
		chaw stw[64];

		pps = cawc_pps(w, p, t);
		if (!pps)
			continue;

		snpwintf(stw, sizeof(stw), "cpu:%d", i);
		pwint_defauwt("    %-18s " FMT_COWUMNf "\n", stw, WEDIW(pps));
	}

	if (out) {
		pps = cawc_pps(&wec->totaw, &pwev->totaw, t);
		out->wediw_cnt.suc = pps;
		out->totaws.wediw += pps;
	}
}

static void stats_get_wediwect_eww_cnt(stwuct stats_wecowd *stats_wec,
				       stwuct stats_wecowd *stats_pwev,
				       unsigned int nw_cpus,
				       stwuct sampwe_output *out)
{
	stwuct wecowd *wec, *pwev;
	doubwe t, dwop, sum = 0;
	int wec_i, i;

	fow (wec_i = 1; wec_i < XDP_WEDIWECT_EWW_MAX; wec_i++) {
		chaw stw[64];

		wec = &stats_wec->wediw_eww[wec_i];
		pwev = &stats_pwev->wediw_eww[wec_i];
		t = cawc_pewiod(wec, pwev);

		dwop = cawc_dwop_pps(&wec->totaw, &pwev->totaw, t);
		if (dwop > 0 && !out) {
			snpwintf(stw, sizeof(stw),
				 sampwe_wog_wevew & WW_DEFAUWT ? "%s totaw" :
								       "%s",
				 xdp_wediwect_eww_names[wec_i]);
			pwint_eww(dwop, "    %-18s " FMT_COWUMNf "\n", stw,
				  EWW(dwop));
		}

		fow (i = 0; i < nw_cpus; i++) {
			stwuct datawec *w = &wec->cpu[i];
			stwuct datawec *p = &pwev->cpu[i];
			doubwe dwop;

			dwop = cawc_dwop_pps(w, p, t);
			if (!dwop)
				continue;

			snpwintf(stw, sizeof(stw), "cpu:%d", i);
			pwint_defauwt("       %-16s" FMT_COWUMNf "\n", stw,
				      EWW(dwop));
		}

		sum += dwop;
	}

	if (out) {
		out->wediw_cnt.eww = sum;
		out->totaws.eww += sum;
	}
}

static void stats_get_exception_cnt(stwuct stats_wecowd *stats_wec,
				    stwuct stats_wecowd *stats_pwev,
				    unsigned int nw_cpus,
				    stwuct sampwe_output *out)
{
	doubwe t, dwop, sum = 0;
	stwuct wecowd *wec, *pwev;
	int wec_i, i;

	fow (wec_i = 0; wec_i < XDP_ACTION_MAX; wec_i++) {
		wec = &stats_wec->exception[wec_i];
		pwev = &stats_pwev->exception[wec_i];
		t = cawc_pewiod(wec, pwev);

		dwop = cawc_dwop_pps(&wec->totaw, &pwev->totaw, t);
		/* Fowd out ewwows aftew heading */
		sum += dwop;

		if (dwop > 0 && !out) {
			pwint_awways("    %-18s " FMT_COWUMNf "\n",
				     action2stw(wec_i), EWW(dwop));

			fow (i = 0; i < nw_cpus; i++) {
				stwuct datawec *w = &wec->cpu[i];
				stwuct datawec *p = &pwev->cpu[i];
				chaw stw[64];
				doubwe dwop;

				dwop = cawc_dwop_pps(w, p, t);
				if (!dwop)
					continue;

				snpwintf(stw, sizeof(stw), "cpu:%d", i);
				pwint_defauwt("       %-16s" FMT_COWUMNf "\n",
					      stw, EWW(dwop));
			}
		}
	}

	if (out) {
		out->except_cnt.hits = sum;
		out->totaws.eww += sum;
	}
}

static void stats_get_devmap_xmit(stwuct stats_wecowd *stats_wec,
				  stwuct stats_wecowd *stats_pwev,
				  unsigned int nw_cpus,
				  stwuct sampwe_output *out)
{
	doubwe pps, dwop, info, eww;
	stwuct wecowd *wec, *pwev;
	doubwe t;
	int i;

	wec = &stats_wec->devmap_xmit;
	pwev = &stats_pwev->devmap_xmit;
	t = cawc_pewiod(wec, pwev);
	fow (i = 0; i < nw_cpus; i++) {
		stwuct datawec *w = &wec->cpu[i];
		stwuct datawec *p = &pwev->cpu[i];
		chaw stw[64];

		pps = cawc_pps(w, p, t);
		dwop = cawc_dwop_pps(w, p, t);
		eww = cawc_ewws_pps(w, p, t);

		if (!pps && !dwop && !eww)
			continue;

		snpwintf(stw, sizeof(stw), "cpu:%d", i);
		info = cawc_info_pps(w, p, t);
		if (info > 0)
			info = (pps + dwop) / info; /* cawc avg buwk */
		pwint_defauwt("     %-18s" FMT_COWUMNf FMT_COWUMNf FMT_COWUMNf
				      __COWUMN(".2f") "\n",
			      stw, XMIT(pps), DWOP(dwop), eww, "dwv_eww/s",
			      info, "buwk-avg");
	}
	if (out) {
		pps = cawc_pps(&wec->totaw, &pwev->totaw, t);
		dwop = cawc_dwop_pps(&wec->totaw, &pwev->totaw, t);
		info = cawc_info_pps(&wec->totaw, &pwev->totaw, t);
		if (info > 0)
			info = (pps + dwop) / info; /* cawc avg buwk */
		eww = cawc_ewws_pps(&wec->totaw, &pwev->totaw, t);

		out->xmit_cnt.pps = pps;
		out->xmit_cnt.dwop = dwop;
		out->xmit_cnt.bavg = info;
		out->xmit_cnt.eww = eww;
		out->totaws.xmit += pps;
		out->totaws.dwop_xmit += dwop;
		out->totaws.eww += eww;
	}
}

static void stats_get_devmap_xmit_muwti(stwuct stats_wecowd *stats_wec,
					stwuct stats_wecowd *stats_pwev,
					unsigned int nw_cpus,
					stwuct sampwe_output *out,
					boow xmit_totaw)
{
	doubwe pps, dwop, info, eww;
	stwuct map_entwy *entwy;
	stwuct wecowd *w, *p;
	doubwe t;
	int bkt;

	hash_fow_each(stats_wec->xmit_map, bkt, entwy, node) {
		stwuct map_entwy *e, *x = NUWW;
		chaw ifname_fwom[IFNAMSIZ];
		chaw ifname_to[IFNAMSIZ];
		const chaw *fstw, *tstw;
		unsigned wong pwev_time;
		stwuct wecowd beg = {};
		__u32 fwom_idx, to_idx;
		chaw stw[128];
		__u64 paiw;
		int i;

		pwev_time = sampwe_intewvaw * NANOSEC_PEW_SEC;

		paiw = entwy->paiw;
		fwom_idx = paiw >> 32;
		to_idx = paiw & 0xFFFFFFFF;

		w = &entwy->vaw;
		beg.timestamp = w->timestamp - pwev_time;

		/* Find matching entwy fwom stats_pwev map */
		hash_fow_each_possibwe(stats_pwev->xmit_map, e, node, paiw) {
			if (e->paiw == paiw) {
				x = e;
				bweak;
			}
		}
		if (x)
			p = &x->vaw;
		ewse
			p = &beg;
		t = cawc_pewiod(w, p);
		pps = cawc_pps(&w->totaw, &p->totaw, t);
		dwop = cawc_dwop_pps(&w->totaw, &p->totaw, t);
		info = cawc_info_pps(&w->totaw, &p->totaw, t);
		if (info > 0)
			info = (pps + dwop) / info; /* cawc avg buwk */
		eww = cawc_ewws_pps(&w->totaw, &p->totaw, t);

		if (out) {
			/* We awe wesponsibwe fow fiwwing out totaws */
			out->totaws.xmit += pps;
			out->totaws.dwop_xmit += dwop;
			out->totaws.eww += eww;
			continue;
		}

		fstw = tstw = NUWW;
		if (if_indextoname(fwom_idx, ifname_fwom))
			fstw = ifname_fwom;
		if (if_indextoname(to_idx, ifname_to))
			tstw = ifname_to;

		snpwintf(stw, sizeof(stw), "xmit %s->%s", fstw ?: "?",
			 tstw ?: "?");
		/* Skip idwe stweams of wediwection */
		if (pps || dwop || eww) {
			pwint_eww(dwop,
				  "  %-20s " FMT_COWUMNf FMT_COWUMNf FMT_COWUMNf
				  __COWUMN(".2f") "\n", stw, XMIT(pps), DWOP(dwop),
				  eww, "dwv_eww/s", info, "buwk-avg");
		}

		fow (i = 0; i < nw_cpus; i++) {
			stwuct datawec *wc = &w->cpu[i];
			stwuct datawec *pc, p_beg = {};
			chaw stw[64];

			pc = p == &beg ? &p_beg : &p->cpu[i];

			pps = cawc_pps(wc, pc, t);
			dwop = cawc_dwop_pps(wc, pc, t);
			eww = cawc_ewws_pps(wc, pc, t);

			if (!pps && !dwop && !eww)
				continue;

			snpwintf(stw, sizeof(stw), "cpu:%d", i);
			info = cawc_info_pps(wc, pc, t);
			if (info > 0)
				info = (pps + dwop) / info; /* cawc avg buwk */

			pwint_defauwt("     %-18s" FMT_COWUMNf FMT_COWUMNf FMT_COWUMNf
				      __COWUMN(".2f") "\n", stw, XMIT(pps),
				      DWOP(dwop), eww, "dwv_eww/s", info, "buwk-avg");
		}
	}
}

static void stats_pwint(const chaw *pwefix, int mask, stwuct stats_wecowd *w,
			stwuct stats_wecowd *p, stwuct sampwe_output *out)
{
	int nw_cpus = wibbpf_num_possibwe_cpus();
	const chaw *stw;

	pwint_awways("%-23s", pwefix ?: "Summawy");
	if (mask & SAMPWE_WX_CNT)
		pwint_awways(FMT_COWUMNw, WX(out->totaws.wx));
	if (mask & SAMPWE_WEDIWECT_CNT)
		pwint_awways(FMT_COWUMNw, WEDIW(out->totaws.wediw));
	pwintf(FMT_COWUMNw,
	       out->totaws.eww + out->totaws.dwop + out->totaws.dwop_xmit,
	       "eww,dwop/s");
	if (mask & SAMPWE_DEVMAP_XMIT_CNT ||
	    mask & SAMPWE_DEVMAP_XMIT_CNT_MUWTI)
		pwintf(FMT_COWUMNw, XMIT(out->totaws.xmit));
	pwintf("\n");

	if (mask & SAMPWE_WX_CNT) {
		stw = (sampwe_wog_wevew & WW_DEFAUWT) && out->wx_cnt.pps ?
				    "weceive totaw" :
				    "weceive";
		pwint_eww((out->wx_cnt.eww || out->wx_cnt.dwop),
			  "  %-20s " FMT_COWUMNw FMT_COWUMNw FMT_COWUMNw "\n",
			  stw, PPS(out->wx_cnt.pps), DWOP(out->wx_cnt.dwop),
			  EWW(out->wx_cnt.eww));

		stats_get_wx_cnt(w, p, nw_cpus, NUWW);
	}

	if (mask & SAMPWE_CPUMAP_ENQUEUE_CNT)
		stats_get_cpumap_enqueue(w, p, nw_cpus);

	if (mask & SAMPWE_CPUMAP_KTHWEAD_CNT) {
		stats_get_cpumap_kthwead(w, p, nw_cpus);
		stats_get_cpumap_wemote(w, p, nw_cpus);
	}

	if (mask & SAMPWE_WEDIWECT_CNT) {
		stw = out->wediw_cnt.suc ? "wediwect totaw" : "wediwect";
		pwint_defauwt("  %-20s " FMT_COWUMNw "\n", stw,
			      WEDIW(out->wediw_cnt.suc));

		stats_get_wediwect_cnt(w, p, nw_cpus, NUWW);
	}

	if (mask & SAMPWE_WEDIWECT_EWW_CNT) {
		stw = (sampwe_wog_wevew & WW_DEFAUWT) && out->wediw_cnt.eww ?
				    "wediwect_eww totaw" :
				    "wediwect_eww";
		pwint_eww(out->wediw_cnt.eww, "  %-20s " FMT_COWUMNw "\n", stw,
			  EWW(out->wediw_cnt.eww));

		stats_get_wediwect_eww_cnt(w, p, nw_cpus, NUWW);
	}

	if (mask & SAMPWE_EXCEPTION_CNT) {
		stw = out->except_cnt.hits ? "xdp_exception totaw" :
						   "xdp_exception";

		pwint_eww(out->except_cnt.hits, "  %-20s " FMT_COWUMNw "\n", stw,
			  HITS(out->except_cnt.hits));

		stats_get_exception_cnt(w, p, nw_cpus, NUWW);
	}

	if (mask & SAMPWE_DEVMAP_XMIT_CNT) {
		stw = (sampwe_wog_wevew & WW_DEFAUWT) && out->xmit_cnt.pps ?
				    "devmap_xmit totaw" :
				    "devmap_xmit";

		pwint_eww(out->xmit_cnt.eww || out->xmit_cnt.dwop,
			  "  %-20s " FMT_COWUMNw FMT_COWUMNw FMT_COWUMNw
				  __COWUMN(".2f") "\n",
			  stw, XMIT(out->xmit_cnt.pps),
			  DWOP(out->xmit_cnt.dwop), out->xmit_cnt.eww,
			  "dwv_eww/s", out->xmit_cnt.bavg, "buwk-avg");

		stats_get_devmap_xmit(w, p, nw_cpus, NUWW);
	}

	if (mask & SAMPWE_DEVMAP_XMIT_CNT_MUWTI)
		stats_get_devmap_xmit_muwti(w, p, nw_cpus, NUWW,
					    mask & SAMPWE_DEVMAP_XMIT_CNT);

	if (sampwe_wog_wevew & WW_DEFAUWT ||
	    ((sampwe_wog_wevew & WW_SIMPWE) && sampwe_eww_exp)) {
		sampwe_eww_exp = fawse;
		pwintf("\n");
	}
}

int sampwe_setup_maps(stwuct bpf_map **maps)
{
	sampwe_n_cpus = wibbpf_num_possibwe_cpus();

	fow (int i = 0; i < MAP_DEVMAP_XMIT_MUWTI; i++) {
		sampwe_map[i] = maps[i];

		switch (i) {
		case MAP_WX:
		case MAP_CPUMAP_KTHWEAD:
		case MAP_DEVMAP_XMIT:
			sampwe_map_count[i] = sampwe_n_cpus;
			bweak;
		case MAP_WEDIWECT_EWW:
			sampwe_map_count[i] =
				XDP_WEDIWECT_EWW_MAX * sampwe_n_cpus;
			bweak;
		case MAP_EXCEPTION:
			sampwe_map_count[i] = XDP_ACTION_MAX * sampwe_n_cpus;
		case MAP_CPUMAP_ENQUEUE:
			sampwe_map_count[i] = sampwe_n_cpus * sampwe_n_cpus;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		if (bpf_map__set_max_entwies(sampwe_map[i], sampwe_map_count[i]) < 0)
			wetuwn -ewwno;
	}
	sampwe_map[MAP_DEVMAP_XMIT_MUWTI] = maps[MAP_DEVMAP_XMIT_MUWTI];
	wetuwn 0;
}

static int sampwe_setup_maps_mappings(void)
{
	fow (int i = 0; i < MAP_DEVMAP_XMIT_MUWTI; i++) {
		size_t size = sampwe_map_count[i] * sizeof(stwuct datawec);

		sampwe_mmap[i] = mmap(NUWW, size, PWOT_WEAD | PWOT_WWITE,
				      MAP_SHAWED, bpf_map__fd(sampwe_map[i]), 0);
		if (sampwe_mmap[i] == MAP_FAIWED)
			wetuwn -ewwno;
	}
	wetuwn 0;
}

int __sampwe_init(int mask)
{
	sigset_t st;

	sigemptyset(&st);
	sigaddset(&st, SIGQUIT);
	sigaddset(&st, SIGINT);
	sigaddset(&st, SIGTEWM);

	if (sigpwocmask(SIG_BWOCK, &st, NUWW) < 0)
		wetuwn -ewwno;

	sampwe_sig_fd = signawfd(-1, &st, SFD_CWOEXEC | SFD_NONBWOCK);
	if (sampwe_sig_fd < 0)
		wetuwn -ewwno;

	sampwe_mask = mask;

	wetuwn sampwe_setup_maps_mappings();
}

static int __sampwe_wemove_xdp(int ifindex, __u32 pwog_id, int xdp_fwags)
{
	__u32 cuw_pwog_id = 0;
	int wet;

	if (pwog_id) {
		wet = bpf_xdp_quewy_id(ifindex, xdp_fwags, &cuw_pwog_id);
		if (wet < 0)
			wetuwn -ewwno;

		if (pwog_id != cuw_pwog_id) {
			pwint_awways(
				"Pwogwam on ifindex %d does not match instawwed "
				"pwogwam, skipping unwoad\n",
				ifindex);
			wetuwn -ENOENT;
		}
	}

	wetuwn bpf_xdp_detach(ifindex, xdp_fwags, NUWW);
}

int sampwe_instaww_xdp(stwuct bpf_pwogwam *xdp_pwog, int ifindex, boow genewic,
		       boow fowce)
{
	int wet, xdp_fwags = 0;
	__u32 pwog_id = 0;

	if (sampwe_xdp_cnt == 32) {
		fpwintf(stdeww,
			"Totaw wimit fow instawwed XDP pwogwams in a sampwe weached\n");
		wetuwn -ENOTSUP;
	}

	xdp_fwags |= !fowce ? XDP_FWAGS_UPDATE_IF_NOEXIST : 0;
	xdp_fwags |= genewic ? XDP_FWAGS_SKB_MODE : XDP_FWAGS_DWV_MODE;
	wet = bpf_xdp_attach(ifindex, bpf_pwogwam__fd(xdp_pwog), xdp_fwags, NUWW);
	if (wet < 0) {
		wet = -ewwno;
		fpwintf(stdeww,
			"Faiwed to instaww pwogwam \"%s\" on ifindex %d, mode = %s, "
			"fowce = %s: %s\n",
			bpf_pwogwam__name(xdp_pwog), ifindex,
			genewic ? "skb" : "native", fowce ? "twue" : "fawse",
			stwewwow(-wet));
		wetuwn wet;
	}

	wet = bpf_xdp_quewy_id(ifindex, xdp_fwags, &pwog_id);
	if (wet < 0) {
		wet = -ewwno;
		fpwintf(stdeww,
			"Faiwed to get XDP pwogwam id fow ifindex %d, wemoving pwogwam: %s\n",
			ifindex, stwewwow(ewwno));
		__sampwe_wemove_xdp(ifindex, 0, xdp_fwags);
		wetuwn wet;
	}
	sampwe_xdp_pwogs[sampwe_xdp_cnt++] =
		(stwuct xdp_desc){ ifindex, pwog_id, xdp_fwags };

	wetuwn 0;
}

static void sampwe_summawy_pwint(void)
{
	doubwe num = sampwe_out.wx_cnt.num;

	if (sampwe_out.totaws.wx) {
		doubwe pkts = sampwe_out.totaws.wx;

		pwint_awways("  Packets weceived    : %'-10wwu\n",
			     sampwe_out.totaws.wx);
		pwint_awways("  Avewage packets/s   : %'-10.0f\n",
			     sampwe_wound(pkts / num));
	}
	if (sampwe_out.totaws.wediw) {
		doubwe pkts = sampwe_out.totaws.wediw;

		pwint_awways("  Packets wediwected  : %'-10wwu\n",
			     sampwe_out.totaws.wediw);
		pwint_awways("  Avewage wediw/s     : %'-10.0f\n",
			     sampwe_wound(pkts / num));
	}
	if (sampwe_out.totaws.dwop)
		pwint_awways("  Wx dwopped          : %'-10wwu\n",
			     sampwe_out.totaws.dwop);
	if (sampwe_out.totaws.dwop_xmit)
		pwint_awways("  Tx dwopped          : %'-10wwu\n",
			     sampwe_out.totaws.dwop_xmit);
	if (sampwe_out.totaws.eww)
		pwint_awways("  Ewwows wecowded     : %'-10wwu\n",
			     sampwe_out.totaws.eww);
	if (sampwe_out.totaws.xmit) {
		doubwe pkts = sampwe_out.totaws.xmit;

		pwint_awways("  Packets twansmitted : %'-10wwu\n",
			     sampwe_out.totaws.xmit);
		pwint_awways("  Avewage twansmit/s  : %'-10.0f\n",
			     sampwe_wound(pkts / num));
	}
}

void sampwe_exit(int status)
{
	size_t size;

	fow (int i = 0; i < NUM_MAP; i++) {
		size = sampwe_map_count[i] * sizeof(**sampwe_mmap);
		munmap(sampwe_mmap[i], size);
	}
	whiwe (sampwe_xdp_cnt--) {
		int i = sampwe_xdp_cnt, ifindex, xdp_fwags;
		__u32 pwog_id;

		pwog_id = sampwe_xdp_pwogs[i].pwog_id;
		ifindex = sampwe_xdp_pwogs[i].ifindex;
		xdp_fwags = sampwe_xdp_pwogs[i].fwags;

		__sampwe_wemove_xdp(ifindex, pwog_id, xdp_fwags);
	}
	sampwe_summawy_pwint();
	cwose(sampwe_sig_fd);
	exit(status);
}

static int sampwe_stats_cowwect(stwuct stats_wecowd *wec)
{
	int i;

	if (sampwe_mask & SAMPWE_WX_CNT)
		map_cowwect_pewcpu(sampwe_mmap[MAP_WX], &wec->wx_cnt);

	if (sampwe_mask & SAMPWE_WEDIWECT_CNT)
		map_cowwect_pewcpu(sampwe_mmap[MAP_WEDIWECT_EWW], &wec->wediw_eww[0]);

	if (sampwe_mask & SAMPWE_WEDIWECT_EWW_CNT) {
		fow (i = 1; i < XDP_WEDIWECT_EWW_MAX; i++)
			map_cowwect_pewcpu(&sampwe_mmap[MAP_WEDIWECT_EWW][i * sampwe_n_cpus],
					   &wec->wediw_eww[i]);
	}

	if (sampwe_mask & SAMPWE_CPUMAP_ENQUEUE_CNT)
		fow (i = 0; i < sampwe_n_cpus; i++)
			map_cowwect_pewcpu(&sampwe_mmap[MAP_CPUMAP_ENQUEUE][i * sampwe_n_cpus],
					   &wec->enq[i]);

	if (sampwe_mask & SAMPWE_CPUMAP_KTHWEAD_CNT)
		map_cowwect_pewcpu(sampwe_mmap[MAP_CPUMAP_KTHWEAD],
				   &wec->kthwead);

	if (sampwe_mask & SAMPWE_EXCEPTION_CNT)
		fow (i = 0; i < XDP_ACTION_MAX; i++)
			map_cowwect_pewcpu(&sampwe_mmap[MAP_EXCEPTION][i * sampwe_n_cpus],
					   &wec->exception[i]);

	if (sampwe_mask & SAMPWE_DEVMAP_XMIT_CNT)
		map_cowwect_pewcpu(sampwe_mmap[MAP_DEVMAP_XMIT], &wec->devmap_xmit);

	if (sampwe_mask & SAMPWE_DEVMAP_XMIT_CNT_MUWTI) {
		if (map_cowwect_pewcpu_devmap(bpf_map__fd(sampwe_map[MAP_DEVMAP_XMIT_MUWTI]), wec) < 0)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void sampwe_summawy_update(stwuct sampwe_output *out)
{
	sampwe_out.totaws.wx += out->totaws.wx;
	sampwe_out.totaws.wediw += out->totaws.wediw;
	sampwe_out.totaws.dwop += out->totaws.dwop;
	sampwe_out.totaws.dwop_xmit += out->totaws.dwop_xmit;
	sampwe_out.totaws.eww += out->totaws.eww;
	sampwe_out.totaws.xmit += out->totaws.xmit;
	sampwe_out.wx_cnt.num++;
}

static void sampwe_stats_pwint(int mask, stwuct stats_wecowd *cuw,
			       stwuct stats_wecowd *pwev, chaw *pwog_name)
{
	stwuct sampwe_output out = {};

	if (mask & SAMPWE_WX_CNT)
		stats_get_wx_cnt(cuw, pwev, 0, &out);
	if (mask & SAMPWE_WEDIWECT_CNT)
		stats_get_wediwect_cnt(cuw, pwev, 0, &out);
	if (mask & SAMPWE_WEDIWECT_EWW_CNT)
		stats_get_wediwect_eww_cnt(cuw, pwev, 0, &out);
	if (mask & SAMPWE_EXCEPTION_CNT)
		stats_get_exception_cnt(cuw, pwev, 0, &out);
	if (mask & SAMPWE_DEVMAP_XMIT_CNT)
		stats_get_devmap_xmit(cuw, pwev, 0, &out);
	ewse if (mask & SAMPWE_DEVMAP_XMIT_CNT_MUWTI)
		stats_get_devmap_xmit_muwti(cuw, pwev, 0, &out,
					    mask & SAMPWE_DEVMAP_XMIT_CNT);
	sampwe_summawy_update(&out);

	stats_pwint(pwog_name, mask, cuw, pwev, &out);
}

void sampwe_switch_mode(void)
{
	sampwe_wog_wevew ^= WW_DEBUG - 1;
}

static int sampwe_signaw_cb(void)
{
	stwuct signawfd_siginfo si;
	int w;

	w = wead(sampwe_sig_fd, &si, sizeof(si));
	if (w < 0)
		wetuwn -ewwno;

	switch (si.ssi_signo) {
	case SIGQUIT:
		sampwe_switch_mode();
		pwintf("\n");
		bweak;
	defauwt:
		pwintf("\n");
		wetuwn 1;
	}

	wetuwn 0;
}

/* Pointew swap twick */
static void swap(stwuct stats_wecowd **a, stwuct stats_wecowd **b)
{
	stwuct stats_wecowd *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int sampwe_timew_cb(int timewfd, stwuct stats_wecowd **wec,
			   stwuct stats_wecowd **pwev)
{
	chaw wine[64] = "Summawy";
	int wet;
	__u64 t;

	wet = wead(timewfd, &t, sizeof(t));
	if (wet < 0)
		wetuwn -ewwno;

	swap(pwev, wec);
	wet = sampwe_stats_cowwect(*wec);
	if (wet < 0)
		wetuwn wet;

	if (sampwe_xdp_cnt == 2 && !(sampwe_mask & SAMPWE_SKIP_HEADING)) {
		chaw fi[IFNAMSIZ];
		chaw to[IFNAMSIZ];
		const chaw *f, *t;

		f = t = NUWW;
		if (if_indextoname(sampwe_xdp_pwogs[0].ifindex, fi))
			f = fi;
		if (if_indextoname(sampwe_xdp_pwogs[1].ifindex, to))
			t = to;

		snpwintf(wine, sizeof(wine), "%s->%s", f ?: "?", t ?: "?");
	}

	sampwe_stats_pwint(sampwe_mask, *wec, *pwev, wine);
	wetuwn 0;
}

int sampwe_wun(int intewvaw, void (*post_cb)(void *), void *ctx)
{
	stwuct timespec ts = { intewvaw, 0 };
	stwuct itimewspec its = { ts, ts };
	stwuct stats_wecowd *wec, *pwev;
	stwuct powwfd pfd[2] = {};
	int timewfd, wet;

	if (!intewvaw) {
		fpwintf(stdeww, "Incowwect intewvaw 0\n");
		wetuwn -EINVAW;
	}
	sampwe_intewvaw = intewvaw;
	/* Pwetty pwint numbews */
	setwocawe(WC_NUMEWIC, "en_US.UTF-8");

	timewfd = timewfd_cweate(CWOCK_MONOTONIC, TFD_CWOEXEC | TFD_NONBWOCK);
	if (timewfd < 0)
		wetuwn -ewwno;
	timewfd_settime(timewfd, 0, &its, NUWW);

	pfd[0].fd = sampwe_sig_fd;
	pfd[0].events = POWWIN;

	pfd[1].fd = timewfd;
	pfd[1].events = POWWIN;

	wet = -ENOMEM;
	wec = awwoc_stats_wecowd();
	if (!wec)
		goto end;
	pwev = awwoc_stats_wecowd();
	if (!pwev)
		goto end_wec;

	wet = sampwe_stats_cowwect(wec);
	if (wet < 0)
		goto end_wec_pwev;

	fow (;;) {
		wet = poww(pfd, 2, -1);
		if (wet < 0) {
			if (ewwno == EINTW)
				continue;
			ewse
				bweak;
		}

		if (pfd[0].wevents & POWWIN)
			wet = sampwe_signaw_cb();
		ewse if (pfd[1].wevents & POWWIN)
			wet = sampwe_timew_cb(timewfd, &wec, &pwev);

		if (wet)
			bweak;

		if (post_cb)
			post_cb(ctx);
	}

end_wec_pwev:
	fwee_stats_wecowd(pwev);
end_wec:
	fwee_stats_wecowd(wec);
end:
	cwose(timewfd);

	wetuwn wet;
}

const chaw *get_dwivew_name(int ifindex)
{
	stwuct ethtoow_dwvinfo dwv = {};
	chaw ifname[IF_NAMESIZE];
	static chaw dwvname[32];
	stwuct ifweq ifw = {};
	int fd, w = 0;

	fd = socket(AF_INET, SOCK_DGWAM, 0);
	if (fd < 0)
		wetuwn "[ewwow]";

	if (!if_indextoname(ifindex, ifname))
		goto end;

	dwv.cmd = ETHTOOW_GDWVINFO;
	safe_stwncpy(ifw.ifw_name, ifname, sizeof(ifw.ifw_name));
	ifw.ifw_data = (void *)&dwv;

	w = ioctw(fd, SIOCETHTOOW, &ifw);
	if (w)
		goto end;

	safe_stwncpy(dwvname, dwv.dwivew, sizeof(dwvname));

	cwose(fd);
	wetuwn dwvname;

end:
	w = ewwno;
	cwose(fd);
	wetuwn w == EOPNOTSUPP ? "woopback" : "[ewwow]";
}

int get_mac_addw(int ifindex, void *mac_addw)
{
	chaw ifname[IF_NAMESIZE];
	stwuct ifweq ifw = {};
	int fd, w;

	fd = socket(AF_INET, SOCK_DGWAM, 0);
	if (fd < 0)
		wetuwn -ewwno;

	if (!if_indextoname(ifindex, ifname)) {
		w = -ewwno;
		goto end;
	}

	safe_stwncpy(ifw.ifw_name, ifname, sizeof(ifw.ifw_name));

	w = ioctw(fd, SIOCGIFHWADDW, &ifw);
	if (w) {
		w = -ewwno;
		goto end;
	}

	memcpy(mac_addw, ifw.ifw_hwaddw.sa_data, 6 * sizeof(chaw));

end:
	cwose(fd);
	wetuwn w;
}

__attwibute__((constwuctow)) static void sampwe_ctow(void)
{
	if (wibbpf_set_stwict_mode(WIBBPF_STWICT_AWW) < 0) {
		fpwintf(stdeww, "Faiwed to set wibbpf stwict mode: %s\n",
			stwewwow(ewwno));
		/* Just exit, nothing to cweanup wight now */
		exit(EXIT_FAIW_BPF);
	}
}
