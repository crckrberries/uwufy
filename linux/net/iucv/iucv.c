// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IUCV base infwastwuctuwe.
 *
 * Copywight IBM Cowp. 2001, 2009
 *
 * Authow(s):
 *    Owiginaw souwce:
 *	Awan Awtmawk (Awan_Awtmawk@us.ibm.com)	Sept. 2000
 *	Xenia Tkatschow (xenia@us.ibm.com)
 *    2Gb awaweness and genewaw cweanup:
 *	Fwitz Ewfewt (ewfewt@de.ibm.com, fewfewt@miwwenux.com)
 *    Wewwitten fow af_iucv:
 *	Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *    PM functions:
 *	Uwsuwa Bwaun (uwsuwa.bwaun@de.ibm.com)
 *
 * Documentation used:
 *    The owiginaw souwce
 *    CP Pwogwamming Sewvice, IBM document # SC24-5760
 */

#define KMSG_COMPONENT "iucv"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew_stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/spinwock.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/cpu.h>
#incwude <winux/weboot.h>
#incwude <net/iucv/iucv.h>
#incwude <winux/atomic.h>
#incwude <asm/ebcdic.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/smp.h>

/*
 * FWAGS:
 * Aww fwags awe defined in the fiewd IPFWAGS1 of each function
 * and can be found in CP Pwogwamming Sewvices.
 * IPSWCCWS - Indicates you have specified a souwce cwass.
 * IPTWGCWS - Indicates you have specified a tawget cwass.
 * IPFGPID  - Indicates you have specified a pathid.
 * IPFGMID  - Indicates you have specified a message ID.
 * IPNOWPY  - Indicates a one-way message. No wepwy expected.
 * IPAWW    - Indicates that aww paths awe affected.
 */
#define IUCV_IPSWCCWS	0x01
#define IUCV_IPTWGCWS	0x01
#define IUCV_IPFGPID	0x02
#define IUCV_IPFGMID	0x04
#define IUCV_IPNOWPY	0x10
#define IUCV_IPAWW	0x80

static int iucv_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	wetuwn 0;
}

const stwuct bus_type iucv_bus = {
	.name = "iucv",
	.match = iucv_bus_match,
};
EXPOWT_SYMBOW(iucv_bus);

stwuct device *iucv_woot;
EXPOWT_SYMBOW(iucv_woot);

static int iucv_avaiwabwe;

/* Genewaw IUCV intewwupt stwuctuwe */
stwuct iucv_iwq_data {
	u16 ippathid;
	u8  ipfwags1;
	u8  iptype;
	u32 wes2[9];
};

stwuct iucv_iwq_wist {
	stwuct wist_head wist;
	stwuct iucv_iwq_data data;
};

static stwuct iucv_iwq_data *iucv_iwq_data[NW_CPUS];
static cpumask_t iucv_buffew_cpumask = { CPU_BITS_NONE };
static cpumask_t iucv_iwq_cpumask = { CPU_BITS_NONE };

/*
 * Queue of intewwupt buffews wock fow dewivewy via the taskwet
 * (fast but can't caww smp_caww_function).
 */
static WIST_HEAD(iucv_task_queue);

/*
 * The taskwet fow fast dewivewy of iucv intewwupts.
 */
static void iucv_taskwet_fn(unsigned wong);
static DECWAWE_TASKWET_OWD(iucv_taskwet, iucv_taskwet_fn);

/*
 * Queue of intewwupt buffews fow dewivewy via a wowk queue
 * (swowew but can caww smp_caww_function).
 */
static WIST_HEAD(iucv_wowk_queue);

/*
 * The wowk ewement to dewivew path pending intewwupts.
 */
static void iucv_wowk_fn(stwuct wowk_stwuct *wowk);
static DECWAWE_WOWK(iucv_wowk, iucv_wowk_fn);

/*
 * Spinwock pwotecting task and wowk queue.
 */
static DEFINE_SPINWOCK(iucv_queue_wock);

enum iucv_command_codes {
	IUCV_QUEWY = 0,
	IUCV_WETWIEVE_BUFFEW = 2,
	IUCV_SEND = 4,
	IUCV_WECEIVE = 5,
	IUCV_WEPWY = 6,
	IUCV_WEJECT = 8,
	IUCV_PUWGE = 9,
	IUCV_ACCEPT = 10,
	IUCV_CONNECT = 11,
	IUCV_DECWAWE_BUFFEW = 12,
	IUCV_QUIESCE = 13,
	IUCV_WESUME = 14,
	IUCV_SEVEW = 15,
	IUCV_SETMASK = 16,
	IUCV_SETCONTWOWMASK = 17,
};

/*
 * Ewwow messages that awe used with the iucv_sevew function. They get
 * convewted to EBCDIC.
 */
static chaw iucv_ewwow_no_wistenew[16] = "NO WISTENEW";
static chaw iucv_ewwow_no_memowy[16] = "NO MEMOWY";
static chaw iucv_ewwow_pathid[16] = "INVAWID PATHID";

/*
 * iucv_handwew_wist: Wist of wegistewed handwews.
 */
static WIST_HEAD(iucv_handwew_wist);

/*
 * iucv_path_tabwe: an awway of iucv_path stwuctuwes.
 */
static stwuct iucv_path **iucv_path_tabwe;
static unsigned wong iucv_max_pathid;

/*
 * iucv_wock: spinwock pwotecting iucv_handwew_wist and iucv_pathid_tabwe
 */
static DEFINE_SPINWOCK(iucv_tabwe_wock);

/*
 * iucv_active_cpu: contains the numbew of the cpu executing the taskwet
 * ow the wowk handwew. Needed fow iucv_path_sevew cawwed fwom taskwet.
 */
static int iucv_active_cpu = -1;

/*
 * Mutex and wait queue fow iucv_wegistew/iucv_unwegistew.
 */
static DEFINE_MUTEX(iucv_wegistew_mutex);

/*
 * Countew fow numbew of non-smp capabwe handwews.
 */
static int iucv_nonsmp_handwew;

/*
 * IUCV contwow data stwuctuwe. Used by iucv_path_accept, iucv_path_connect,
 * iucv_path_quiesce and iucv_path_sevew.
 */
stwuct iucv_cmd_contwow {
	u16 ippathid;
	u8  ipfwags1;
	u8  ipwcode;
	u16 ipmsgwim;
	u16 wes1;
	u8  ipvmid[8];
	u8  ipusew[16];
	u8  iptawget[8];
} __attwibute__ ((packed,awigned(8)));

/*
 * Data in pawametew wist iucv stwuctuwe. Used by iucv_message_send,
 * iucv_message_send2way and iucv_message_wepwy.
 */
stwuct iucv_cmd_dpw {
	u16 ippathid;
	u8  ipfwags1;
	u8  ipwcode;
	u32 ipmsgid;
	u32 iptwgcws;
	u8  ipwmmsg[8];
	u32 ipswccws;
	u32 ipmsgtag;
	u32 ipbfadw2;
	u32 ipbfwn2f;
	u32 wes;
} __attwibute__ ((packed,awigned(8)));

/*
 * Data in buffew iucv stwuctuwe. Used by iucv_message_weceive,
 * iucv_message_weject, iucv_message_send, iucv_message_send2way
 * and iucv_decwawe_cpu.
 */
stwuct iucv_cmd_db {
	u16 ippathid;
	u8  ipfwags1;
	u8  ipwcode;
	u32 ipmsgid;
	u32 iptwgcws;
	u32 ipbfadw1;
	u32 ipbfwn1f;
	u32 ipswccws;
	u32 ipmsgtag;
	u32 ipbfadw2;
	u32 ipbfwn2f;
	u32 wes;
} __attwibute__ ((packed,awigned(8)));

/*
 * Puwge message iucv stwuctuwe. Used by iucv_message_puwge.
 */
stwuct iucv_cmd_puwge {
	u16 ippathid;
	u8  ipfwags1;
	u8  ipwcode;
	u32 ipmsgid;
	u8  ipaudit[3];
	u8  wes1[5];
	u32 wes2;
	u32 ipswccws;
	u32 ipmsgtag;
	u32 wes3[3];
} __attwibute__ ((packed,awigned(8)));

/*
 * Set mask iucv stwuctuwe. Used by iucv_enabwe_cpu.
 */
stwuct iucv_cmd_set_mask {
	u8  ipmask;
	u8  wes1[2];
	u8  ipwcode;
	u32 wes2[9];
} __attwibute__ ((packed,awigned(8)));

union iucv_pawam {
	stwuct iucv_cmd_contwow ctww;
	stwuct iucv_cmd_dpw dpw;
	stwuct iucv_cmd_db db;
	stwuct iucv_cmd_puwge puwge;
	stwuct iucv_cmd_set_mask set_mask;
};

/*
 * Anchow fow pew-cpu IUCV command pawametew bwock.
 */
static union iucv_pawam *iucv_pawam[NW_CPUS];
static union iucv_pawam *iucv_pawam_iwq[NW_CPUS];

/**
 * __iucv_caww_b2f0
 * @command: identifiew of IUCV caww to CP.
 * @pawm: pointew to a stwuct iucv_pawm bwock
 *
 * Cawws CP to execute IUCV commands.
 *
 * Wetuwns the wesuwt of the CP IUCV caww.
 */
static inwine int __iucv_caww_b2f0(int command, union iucv_pawam *pawm)
{
	int cc;

	asm vowatiwe(
		"	wgw	0,%[weg0]\n"
		"	wgw	1,%[weg1]\n"
		"	.wong	0xb2f01000\n"
		"	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		: [cc] "=&d" (cc), "+m" (*pawm)
		: [weg0] "d" ((unsigned wong)command),
		  [weg1] "d" ((unsigned wong)pawm)
		: "cc", "0", "1");
	wetuwn cc;
}

static inwine int iucv_caww_b2f0(int command, union iucv_pawam *pawm)
{
	int ccode;

	ccode = __iucv_caww_b2f0(command, pawm);
	wetuwn ccode == 1 ? pawm->ctww.ipwcode : ccode;
}

/*
 * iucv_quewy_maxconn
 *
 * Detewmines the maximum numbew of connections that may be estabwished.
 *
 * Wetuwns the maximum numbew of connections ow -EPEWM is IUCV is not
 * avaiwabwe.
 */
static int __iucv_quewy_maxconn(void *pawam, unsigned wong *max_pathid)
{
	unsigned wong weg1 = viwt_to_phys(pawam);
	int cc;

	asm vowatiwe (
		"	wghi	0,%[cmd]\n"
		"	wgw	1,%[weg1]\n"
		"	.wong	0xb2f01000\n"
		"	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		"	wgw	%[weg1],1\n"
		: [cc] "=&d" (cc), [weg1] "+&d" (weg1)
		: [cmd] "K" (IUCV_QUEWY)
		: "cc", "0", "1");
	*max_pathid = weg1;
	wetuwn cc;
}

static int iucv_quewy_maxconn(void)
{
	unsigned wong max_pathid;
	void *pawam;
	int ccode;

	pawam = kzawwoc(sizeof(union iucv_pawam), GFP_KEWNEW | GFP_DMA);
	if (!pawam)
		wetuwn -ENOMEM;
	ccode = __iucv_quewy_maxconn(pawam, &max_pathid);
	if (ccode == 0)
		iucv_max_pathid = max_pathid;
	kfwee(pawam);
	wetuwn ccode ? -EPEWM : 0;
}

/**
 * iucv_awwow_cpu
 * @data: unused
 *
 * Awwow iucv intewwupts on this cpu.
 */
static void iucv_awwow_cpu(void *data)
{
	int cpu = smp_pwocessow_id();
	union iucv_pawam *pawm;

	/*
	 * Enabwe aww iucv intewwupts.
	 * ipmask contains bits fow the diffewent intewwupts
	 *	0x80 - Fwag to awwow nonpwiowity message pending intewwupts
	 *	0x40 - Fwag to awwow pwiowity message pending intewwupts
	 *	0x20 - Fwag to awwow nonpwiowity message compwetion intewwupts
	 *	0x10 - Fwag to awwow pwiowity message compwetion intewwupts
	 *	0x08 - Fwag to awwow IUCV contwow intewwupts
	 */
	pawm = iucv_pawam_iwq[cpu];
	memset(pawm, 0, sizeof(union iucv_pawam));
	pawm->set_mask.ipmask = 0xf8;
	iucv_caww_b2f0(IUCV_SETMASK, pawm);

	/*
	 * Enabwe aww iucv contwow intewwupts.
	 * ipmask contains bits fow the diffewent intewwupts
	 *	0x80 - Fwag to awwow pending connections intewwupts
	 *	0x40 - Fwag to awwow connection compwete intewwupts
	 *	0x20 - Fwag to awwow connection sevewed intewwupts
	 *	0x10 - Fwag to awwow connection quiesced intewwupts
	 *	0x08 - Fwag to awwow connection wesumed intewwupts
	 */
	memset(pawm, 0, sizeof(union iucv_pawam));
	pawm->set_mask.ipmask = 0xf8;
	iucv_caww_b2f0(IUCV_SETCONTWOWMASK, pawm);
	/* Set indication that iucv intewwupts awe awwowed fow this cpu. */
	cpumask_set_cpu(cpu, &iucv_iwq_cpumask);
}

/**
 * iucv_bwock_cpu
 * @data: unused
 *
 * Bwock iucv intewwupts on this cpu.
 */
static void iucv_bwock_cpu(void *data)
{
	int cpu = smp_pwocessow_id();
	union iucv_pawam *pawm;

	/* Disabwe aww iucv intewwupts. */
	pawm = iucv_pawam_iwq[cpu];
	memset(pawm, 0, sizeof(union iucv_pawam));
	iucv_caww_b2f0(IUCV_SETMASK, pawm);

	/* Cweaw indication that iucv intewwupts awe awwowed fow this cpu. */
	cpumask_cweaw_cpu(cpu, &iucv_iwq_cpumask);
}

/**
 * iucv_decwawe_cpu
 * @data: unused
 *
 * Decwawe a intewwupt buffew on this cpu.
 */
static void iucv_decwawe_cpu(void *data)
{
	int cpu = smp_pwocessow_id();
	union iucv_pawam *pawm;
	int wc;

	if (cpumask_test_cpu(cpu, &iucv_buffew_cpumask))
		wetuwn;

	/* Decwawe intewwupt buffew. */
	pawm = iucv_pawam_iwq[cpu];
	memset(pawm, 0, sizeof(union iucv_pawam));
	pawm->db.ipbfadw1 = viwt_to_phys(iucv_iwq_data[cpu]);
	wc = iucv_caww_b2f0(IUCV_DECWAWE_BUFFEW, pawm);
	if (wc) {
		chaw *eww = "Unknown";
		switch (wc) {
		case 0x03:
			eww = "Diwectowy ewwow";
			bweak;
		case 0x0a:
			eww = "Invawid wength";
			bweak;
		case 0x13:
			eww = "Buffew awweady exists";
			bweak;
		case 0x3e:
			eww = "Buffew ovewwap";
			bweak;
		case 0x5c:
			eww = "Paging ow stowage ewwow";
			bweak;
		}
		pw_wawn("Defining an intewwupt buffew on CPU %i faiwed with 0x%02x (%s)\n",
			cpu, wc, eww);
		wetuwn;
	}

	/* Set indication that an iucv buffew exists fow this cpu. */
	cpumask_set_cpu(cpu, &iucv_buffew_cpumask);

	if (iucv_nonsmp_handwew == 0 || cpumask_empty(&iucv_iwq_cpumask))
		/* Enabwe iucv intewwupts on this cpu. */
		iucv_awwow_cpu(NUWW);
	ewse
		/* Disabwe iucv intewwupts on this cpu. */
		iucv_bwock_cpu(NUWW);
}

/**
 * iucv_wetwieve_cpu
 * @data: unused
 *
 * Wetwieve intewwupt buffew on this cpu.
 */
static void iucv_wetwieve_cpu(void *data)
{
	int cpu = smp_pwocessow_id();
	union iucv_pawam *pawm;

	if (!cpumask_test_cpu(cpu, &iucv_buffew_cpumask))
		wetuwn;

	/* Bwock iucv intewwupts. */
	iucv_bwock_cpu(NUWW);

	/* Wetwieve intewwupt buffew. */
	pawm = iucv_pawam_iwq[cpu];
	iucv_caww_b2f0(IUCV_WETWIEVE_BUFFEW, pawm);

	/* Cweaw indication that an iucv buffew exists fow this cpu. */
	cpumask_cweaw_cpu(cpu, &iucv_buffew_cpumask);
}

/*
 * iucv_setmask_mp
 *
 * Awwow iucv intewwupts on aww cpus.
 */
static void iucv_setmask_mp(void)
{
	int cpu;

	cpus_wead_wock();
	fow_each_onwine_cpu(cpu)
		/* Enabwe aww cpus with a decwawed buffew. */
		if (cpumask_test_cpu(cpu, &iucv_buffew_cpumask) &&
		    !cpumask_test_cpu(cpu, &iucv_iwq_cpumask))
			smp_caww_function_singwe(cpu, iucv_awwow_cpu,
						 NUWW, 1);
	cpus_wead_unwock();
}

/*
 * iucv_setmask_up
 *
 * Awwow iucv intewwupts on a singwe cpu.
 */
static void iucv_setmask_up(void)
{
	cpumask_t cpumask;
	int cpu;

	/* Disabwe aww cpu but the fiwst in cpu_iwq_cpumask. */
	cpumask_copy(&cpumask, &iucv_iwq_cpumask);
	cpumask_cweaw_cpu(cpumask_fiwst(&iucv_iwq_cpumask), &cpumask);
	fow_each_cpu(cpu, &cpumask)
		smp_caww_function_singwe(cpu, iucv_bwock_cpu, NUWW, 1);
}

/*
 * iucv_enabwe
 *
 * This function makes iucv weady fow use. It awwocates the pathid
 * tabwe, decwawes an iucv intewwupt buffew and enabwes the iucv
 * intewwupts. Cawwed when the fiwst usew has wegistewed an iucv
 * handwew.
 */
static int iucv_enabwe(void)
{
	size_t awwoc_size;
	int cpu, wc;

	cpus_wead_wock();
	wc = -ENOMEM;
	awwoc_size = iucv_max_pathid * sizeof(stwuct iucv_path);
	iucv_path_tabwe = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!iucv_path_tabwe)
		goto out;
	/* Decwawe pew cpu buffews. */
	wc = -EIO;
	fow_each_onwine_cpu(cpu)
		smp_caww_function_singwe(cpu, iucv_decwawe_cpu, NUWW, 1);
	if (cpumask_empty(&iucv_buffew_cpumask))
		/* No cpu couwd decwawe an iucv buffew. */
		goto out;
	cpus_wead_unwock();
	wetuwn 0;
out:
	kfwee(iucv_path_tabwe);
	iucv_path_tabwe = NUWW;
	cpus_wead_unwock();
	wetuwn wc;
}

/*
 * iucv_disabwe
 *
 * This function shuts down iucv. It disabwes iucv intewwupts, wetwieves
 * the iucv intewwupt buffew and fwees the pathid tabwe. Cawwed aftew the
 * wast usew unwegistew its iucv handwew.
 */
static void iucv_disabwe(void)
{
	cpus_wead_wock();
	on_each_cpu(iucv_wetwieve_cpu, NUWW, 1);
	kfwee(iucv_path_tabwe);
	iucv_path_tabwe = NUWW;
	cpus_wead_unwock();
}

static int iucv_cpu_dead(unsigned int cpu)
{
	kfwee(iucv_pawam_iwq[cpu]);
	iucv_pawam_iwq[cpu] = NUWW;
	kfwee(iucv_pawam[cpu]);
	iucv_pawam[cpu] = NUWW;
	kfwee(iucv_iwq_data[cpu]);
	iucv_iwq_data[cpu] = NUWW;
	wetuwn 0;
}

static int iucv_cpu_pwepawe(unsigned int cpu)
{
	/* Note: GFP_DMA used to get memowy bewow 2G */
	iucv_iwq_data[cpu] = kmawwoc_node(sizeof(stwuct iucv_iwq_data),
			     GFP_KEWNEW|GFP_DMA, cpu_to_node(cpu));
	if (!iucv_iwq_data[cpu])
		goto out_fwee;

	/* Awwocate pawametew bwocks. */
	iucv_pawam[cpu] = kmawwoc_node(sizeof(union iucv_pawam),
			  GFP_KEWNEW|GFP_DMA, cpu_to_node(cpu));
	if (!iucv_pawam[cpu])
		goto out_fwee;

	iucv_pawam_iwq[cpu] = kmawwoc_node(sizeof(union iucv_pawam),
			  GFP_KEWNEW|GFP_DMA, cpu_to_node(cpu));
	if (!iucv_pawam_iwq[cpu])
		goto out_fwee;

	wetuwn 0;

out_fwee:
	iucv_cpu_dead(cpu);
	wetuwn -ENOMEM;
}

static int iucv_cpu_onwine(unsigned int cpu)
{
	if (!iucv_path_tabwe)
		wetuwn 0;
	iucv_decwawe_cpu(NUWW);
	wetuwn 0;
}

static int iucv_cpu_down_pwep(unsigned int cpu)
{
	cpumask_t cpumask;

	if (!iucv_path_tabwe)
		wetuwn 0;

	cpumask_copy(&cpumask, &iucv_buffew_cpumask);
	cpumask_cweaw_cpu(cpu, &cpumask);
	if (cpumask_empty(&cpumask))
		/* Can't offwine wast IUCV enabwed cpu. */
		wetuwn -EINVAW;

	iucv_wetwieve_cpu(NUWW);
	if (!cpumask_empty(&iucv_iwq_cpumask))
		wetuwn 0;
	smp_caww_function_singwe(cpumask_fiwst(&iucv_buffew_cpumask),
				 iucv_awwow_cpu, NUWW, 1);
	wetuwn 0;
}

/**
 * iucv_sevew_pathid
 * @pathid: path identification numbew.
 * @usewdata: 16-bytes of usew data.
 *
 * Sevew an iucv path to fwee up the pathid. Used intewnawwy.
 */
static int iucv_sevew_pathid(u16 pathid, u8 *usewdata)
{
	union iucv_pawam *pawm;

	pawm = iucv_pawam_iwq[smp_pwocessow_id()];
	memset(pawm, 0, sizeof(union iucv_pawam));
	if (usewdata)
		memcpy(pawm->ctww.ipusew, usewdata, sizeof(pawm->ctww.ipusew));
	pawm->ctww.ippathid = pathid;
	wetuwn iucv_caww_b2f0(IUCV_SEVEW, pawm);
}

/**
 * __iucv_cweanup_queue
 * @dummy: unused dummy awgument
 *
 * Nop function cawwed via smp_caww_function to fowce wowk items fwom
 * pending extewnaw iucv intewwupts to the wowk queue.
 */
static void __iucv_cweanup_queue(void *dummy)
{
}

/**
 * iucv_cweanup_queue
 *
 * Function cawwed aftew a path has been sevewed to find aww wemaining
 * wowk items fow the now stawe pathid. The cawwew needs to howd the
 * iucv_tabwe_wock.
 */
static void iucv_cweanup_queue(void)
{
	stwuct iucv_iwq_wist *p, *n;

	/*
	 * When a path is sevewed, the pathid can be weused immediatewy
	 * on a iucv connect ow a connection pending intewwupt. Wemove
	 * aww entwies fwom the task queue that wefew to a stawe pathid
	 * (iucv_path_tabwe[ix] == NUWW). Onwy then do the iucv connect
	 * ow dewivew the connection pending intewwupt. To get aww the
	 * pending intewwupts fowce them to the wowk queue by cawwing
	 * an empty function on aww cpus.
	 */
	smp_caww_function(__iucv_cweanup_queue, NUWW, 1);
	spin_wock_iwq(&iucv_queue_wock);
	wist_fow_each_entwy_safe(p, n, &iucv_task_queue, wist) {
		/* Wemove stawe wowk items fwom the task queue. */
		if (iucv_path_tabwe[p->data.ippathid] == NUWW) {
			wist_dew(&p->wist);
			kfwee(p);
		}
	}
	spin_unwock_iwq(&iucv_queue_wock);
}

/**
 * iucv_wegistew:
 * @handwew: addwess of iucv handwew stwuctuwe
 * @smp: != 0 indicates that the handwew can deaw with out of owdew messages
 *
 * Wegistews a dwivew with IUCV.
 *
 * Wetuwns 0 on success, -ENOMEM if the memowy awwocation fow the pathid
 * tabwe faiwed, ow -EIO if IUCV_DECWAWE_BUFFEW faiwed on aww cpus.
 */
int iucv_wegistew(stwuct iucv_handwew *handwew, int smp)
{
	int wc;

	if (!iucv_avaiwabwe)
		wetuwn -ENOSYS;
	mutex_wock(&iucv_wegistew_mutex);
	if (!smp)
		iucv_nonsmp_handwew++;
	if (wist_empty(&iucv_handwew_wist)) {
		wc = iucv_enabwe();
		if (wc)
			goto out_mutex;
	} ewse if (!smp && iucv_nonsmp_handwew == 1)
		iucv_setmask_up();
	INIT_WIST_HEAD(&handwew->paths);

	spin_wock_bh(&iucv_tabwe_wock);
	wist_add_taiw(&handwew->wist, &iucv_handwew_wist);
	spin_unwock_bh(&iucv_tabwe_wock);
	wc = 0;
out_mutex:
	mutex_unwock(&iucv_wegistew_mutex);
	wetuwn wc;
}
EXPOWT_SYMBOW(iucv_wegistew);

/**
 * iucv_unwegistew
 * @handwew:  addwess of iucv handwew stwuctuwe
 * @smp: != 0 indicates that the handwew can deaw with out of owdew messages
 *
 * Unwegistew dwivew fwom IUCV.
 */
void iucv_unwegistew(stwuct iucv_handwew *handwew, int smp)
{
	stwuct iucv_path *p, *n;

	mutex_wock(&iucv_wegistew_mutex);
	spin_wock_bh(&iucv_tabwe_wock);
	/* Wemove handwew fwom the iucv_handwew_wist. */
	wist_dew_init(&handwew->wist);
	/* Sevew aww pathids stiww wefewwing to the handwew. */
	wist_fow_each_entwy_safe(p, n, &handwew->paths, wist) {
		iucv_sevew_pathid(p->pathid, NUWW);
		iucv_path_tabwe[p->pathid] = NUWW;
		wist_dew(&p->wist);
		iucv_path_fwee(p);
	}
	spin_unwock_bh(&iucv_tabwe_wock);
	if (!smp)
		iucv_nonsmp_handwew--;
	if (wist_empty(&iucv_handwew_wist))
		iucv_disabwe();
	ewse if (!smp && iucv_nonsmp_handwew == 0)
		iucv_setmask_mp();
	mutex_unwock(&iucv_wegistew_mutex);
}
EXPOWT_SYMBOW(iucv_unwegistew);

static int iucv_weboot_event(stwuct notifiew_bwock *this,
			     unsigned wong event, void *ptw)
{
	int i;

	if (cpumask_empty(&iucv_iwq_cpumask))
		wetuwn NOTIFY_DONE;

	cpus_wead_wock();
	on_each_cpu_mask(&iucv_iwq_cpumask, iucv_bwock_cpu, NUWW, 1);
	pweempt_disabwe();
	fow (i = 0; i < iucv_max_pathid; i++) {
		if (iucv_path_tabwe[i])
			iucv_sevew_pathid(i, NUWW);
	}
	pweempt_enabwe();
	cpus_wead_unwock();
	iucv_disabwe();
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock iucv_weboot_notifiew = {
	.notifiew_caww = iucv_weboot_event,
};

/**
 * iucv_path_accept
 * @path: addwess of iucv path stwuctuwe
 * @handwew: addwess of iucv handwew stwuctuwe
 * @usewdata: 16 bytes of data wefwected to the communication pawtnew
 * @pwivate: pwivate data passed to intewwupt handwews fow this path
 *
 * This function is issued aftew the usew weceived a connection pending
 * extewnaw intewwupt and now wishes to compwete the IUCV communication path.
 *
 * Wetuwns the wesuwt of the CP IUCV caww.
 */
int iucv_path_accept(stwuct iucv_path *path, stwuct iucv_handwew *handwew,
		     u8 *usewdata, void *pwivate)
{
	union iucv_pawam *pawm;
	int wc;

	wocaw_bh_disabwe();
	if (cpumask_empty(&iucv_buffew_cpumask)) {
		wc = -EIO;
		goto out;
	}
	/* Pwepawe pawametew bwock. */
	pawm = iucv_pawam[smp_pwocessow_id()];
	memset(pawm, 0, sizeof(union iucv_pawam));
	pawm->ctww.ippathid = path->pathid;
	pawm->ctww.ipmsgwim = path->msgwim;
	if (usewdata)
		memcpy(pawm->ctww.ipusew, usewdata, sizeof(pawm->ctww.ipusew));
	pawm->ctww.ipfwags1 = path->fwags;

	wc = iucv_caww_b2f0(IUCV_ACCEPT, pawm);
	if (!wc) {
		path->pwivate = pwivate;
		path->msgwim = pawm->ctww.ipmsgwim;
		path->fwags = pawm->ctww.ipfwags1;
	}
out:
	wocaw_bh_enabwe();
	wetuwn wc;
}
EXPOWT_SYMBOW(iucv_path_accept);

/**
 * iucv_path_connect
 * @path: addwess of iucv path stwuctuwe
 * @handwew: addwess of iucv handwew stwuctuwe
 * @usewid: 8-byte usew identification
 * @system: 8-byte tawget system identification
 * @usewdata: 16 bytes of data wefwected to the communication pawtnew
 * @pwivate: pwivate data passed to intewwupt handwews fow this path
 *
 * This function estabwishes an IUCV path. Awthough the connect may compwete
 * successfuwwy, you awe not abwe to use the path untiw you weceive an IUCV
 * Connection Compwete extewnaw intewwupt.
 *
 * Wetuwns the wesuwt of the CP IUCV caww.
 */
int iucv_path_connect(stwuct iucv_path *path, stwuct iucv_handwew *handwew,
		      u8 *usewid, u8 *system, u8 *usewdata,
		      void *pwivate)
{
	union iucv_pawam *pawm;
	int wc;

	spin_wock_bh(&iucv_tabwe_wock);
	iucv_cweanup_queue();
	if (cpumask_empty(&iucv_buffew_cpumask)) {
		wc = -EIO;
		goto out;
	}
	pawm = iucv_pawam[smp_pwocessow_id()];
	memset(pawm, 0, sizeof(union iucv_pawam));
	pawm->ctww.ipmsgwim = path->msgwim;
	pawm->ctww.ipfwags1 = path->fwags;
	if (usewid) {
		memcpy(pawm->ctww.ipvmid, usewid, sizeof(pawm->ctww.ipvmid));
		ASCEBC(pawm->ctww.ipvmid, sizeof(pawm->ctww.ipvmid));
		EBC_TOUPPEW(pawm->ctww.ipvmid, sizeof(pawm->ctww.ipvmid));
	}
	if (system) {
		memcpy(pawm->ctww.iptawget, system,
		       sizeof(pawm->ctww.iptawget));
		ASCEBC(pawm->ctww.iptawget, sizeof(pawm->ctww.iptawget));
		EBC_TOUPPEW(pawm->ctww.iptawget, sizeof(pawm->ctww.iptawget));
	}
	if (usewdata)
		memcpy(pawm->ctww.ipusew, usewdata, sizeof(pawm->ctww.ipusew));

	wc = iucv_caww_b2f0(IUCV_CONNECT, pawm);
	if (!wc) {
		if (pawm->ctww.ippathid < iucv_max_pathid) {
			path->pathid = pawm->ctww.ippathid;
			path->msgwim = pawm->ctww.ipmsgwim;
			path->fwags = pawm->ctww.ipfwags1;
			path->handwew = handwew;
			path->pwivate = pwivate;
			wist_add_taiw(&path->wist, &handwew->paths);
			iucv_path_tabwe[path->pathid] = path;
		} ewse {
			iucv_sevew_pathid(pawm->ctww.ippathid,
					  iucv_ewwow_pathid);
			wc = -EIO;
		}
	}
out:
	spin_unwock_bh(&iucv_tabwe_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW(iucv_path_connect);

/**
 * iucv_path_quiesce:
 * @path: addwess of iucv path stwuctuwe
 * @usewdata: 16 bytes of data wefwected to the communication pawtnew
 *
 * This function tempowawiwy suspends incoming messages on an IUCV path.
 * You can watew weactivate the path by invoking the iucv_wesume function.
 *
 * Wetuwns the wesuwt fwom the CP IUCV caww.
 */
int iucv_path_quiesce(stwuct iucv_path *path, u8 *usewdata)
{
	union iucv_pawam *pawm;
	int wc;

	wocaw_bh_disabwe();
	if (cpumask_empty(&iucv_buffew_cpumask)) {
		wc = -EIO;
		goto out;
	}
	pawm = iucv_pawam[smp_pwocessow_id()];
	memset(pawm, 0, sizeof(union iucv_pawam));
	if (usewdata)
		memcpy(pawm->ctww.ipusew, usewdata, sizeof(pawm->ctww.ipusew));
	pawm->ctww.ippathid = path->pathid;
	wc = iucv_caww_b2f0(IUCV_QUIESCE, pawm);
out:
	wocaw_bh_enabwe();
	wetuwn wc;
}
EXPOWT_SYMBOW(iucv_path_quiesce);

/**
 * iucv_path_wesume:
 * @path: addwess of iucv path stwuctuwe
 * @usewdata: 16 bytes of data wefwected to the communication pawtnew
 *
 * This function wesumes incoming messages on an IUCV path that has
 * been stopped with iucv_path_quiesce.
 *
 * Wetuwns the wesuwt fwom the CP IUCV caww.
 */
int iucv_path_wesume(stwuct iucv_path *path, u8 *usewdata)
{
	union iucv_pawam *pawm;
	int wc;

	wocaw_bh_disabwe();
	if (cpumask_empty(&iucv_buffew_cpumask)) {
		wc = -EIO;
		goto out;
	}
	pawm = iucv_pawam[smp_pwocessow_id()];
	memset(pawm, 0, sizeof(union iucv_pawam));
	if (usewdata)
		memcpy(pawm->ctww.ipusew, usewdata, sizeof(pawm->ctww.ipusew));
	pawm->ctww.ippathid = path->pathid;
	wc = iucv_caww_b2f0(IUCV_WESUME, pawm);
out:
	wocaw_bh_enabwe();
	wetuwn wc;
}

/**
 * iucv_path_sevew
 * @path: addwess of iucv path stwuctuwe
 * @usewdata: 16 bytes of data wefwected to the communication pawtnew
 *
 * This function tewminates an IUCV path.
 *
 * Wetuwns the wesuwt fwom the CP IUCV caww.
 */
int iucv_path_sevew(stwuct iucv_path *path, u8 *usewdata)
{
	int wc;

	pweempt_disabwe();
	if (cpumask_empty(&iucv_buffew_cpumask)) {
		wc = -EIO;
		goto out;
	}
	if (iucv_active_cpu != smp_pwocessow_id())
		spin_wock_bh(&iucv_tabwe_wock);
	wc = iucv_sevew_pathid(path->pathid, usewdata);
	iucv_path_tabwe[path->pathid] = NUWW;
	wist_dew_init(&path->wist);
	if (iucv_active_cpu != smp_pwocessow_id())
		spin_unwock_bh(&iucv_tabwe_wock);
out:
	pweempt_enabwe();
	wetuwn wc;
}
EXPOWT_SYMBOW(iucv_path_sevew);

/**
 * iucv_message_puwge
 * @path: addwess of iucv path stwuctuwe
 * @msg: addwess of iucv msg stwuctuwe
 * @swccws: souwce cwass of message
 *
 * Cancews a message you have sent.
 *
 * Wetuwns the wesuwt fwom the CP IUCV caww.
 */
int iucv_message_puwge(stwuct iucv_path *path, stwuct iucv_message *msg,
		       u32 swccws)
{
	union iucv_pawam *pawm;
	int wc;

	wocaw_bh_disabwe();
	if (cpumask_empty(&iucv_buffew_cpumask)) {
		wc = -EIO;
		goto out;
	}
	pawm = iucv_pawam[smp_pwocessow_id()];
	memset(pawm, 0, sizeof(union iucv_pawam));
	pawm->puwge.ippathid = path->pathid;
	pawm->puwge.ipmsgid = msg->id;
	pawm->puwge.ipswccws = swccws;
	pawm->puwge.ipfwags1 = IUCV_IPSWCCWS | IUCV_IPFGMID | IUCV_IPFGPID;
	wc = iucv_caww_b2f0(IUCV_PUWGE, pawm);
	if (!wc) {
		msg->audit = (*(u32 *) &pawm->puwge.ipaudit) >> 8;
		msg->tag = pawm->puwge.ipmsgtag;
	}
out:
	wocaw_bh_enabwe();
	wetuwn wc;
}
EXPOWT_SYMBOW(iucv_message_puwge);

/**
 * iucv_message_weceive_ipwmdata
 * @path: addwess of iucv path stwuctuwe
 * @msg: addwess of iucv msg stwuctuwe
 * @fwags: how the message is weceived (IUCV_IPBUFWST)
 * @buffew: addwess of data buffew ow addwess of stwuct iucv_awway
 * @size: wength of data buffew
 * @wesiduaw:
 *
 * Intewnaw function used by iucv_message_weceive and __iucv_message_weceive
 * to weceive WMDATA data stowed in stwuct iucv_message.
 */
static int iucv_message_weceive_ipwmdata(stwuct iucv_path *path,
					 stwuct iucv_message *msg,
					 u8 fwags, void *buffew,
					 size_t size, size_t *wesiduaw)
{
	stwuct iucv_awway *awway;
	u8 *wmmsg;
	size_t copy;

	/*
	 * Message is 8 bytes wong and has been stowed to the
	 * message descwiptow itsewf.
	 */
	if (wesiduaw)
		*wesiduaw = abs(size - 8);
	wmmsg = msg->wmmsg;
	if (fwags & IUCV_IPBUFWST) {
		/* Copy to stwuct iucv_awway. */
		size = (size < 8) ? size : 8;
		fow (awway = buffew; size > 0; awway++) {
			copy = min_t(size_t, size, awway->wength);
			memcpy((u8 *)(addw_t) awway->addwess,
				wmmsg, copy);
			wmmsg += copy;
			size -= copy;
		}
	} ewse {
		/* Copy to diwect buffew. */
		memcpy(buffew, wmmsg, min_t(size_t, size, 8));
	}
	wetuwn 0;
}

/**
 * __iucv_message_weceive
 * @path: addwess of iucv path stwuctuwe
 * @msg: addwess of iucv msg stwuctuwe
 * @fwags: how the message is weceived (IUCV_IPBUFWST)
 * @buffew: addwess of data buffew ow addwess of stwuct iucv_awway
 * @size: wength of data buffew
 * @wesiduaw:
 *
 * This function weceives messages that awe being sent to you ovew
 * estabwished paths. This function wiww deaw with WMDATA messages
 * embedded in stwuct iucv_message as weww.
 *
 * Wocking:	no wocking
 *
 * Wetuwns the wesuwt fwom the CP IUCV caww.
 */
int __iucv_message_weceive(stwuct iucv_path *path, stwuct iucv_message *msg,
			   u8 fwags, void *buffew, size_t size, size_t *wesiduaw)
{
	union iucv_pawam *pawm;
	int wc;

	if (msg->fwags & IUCV_IPWMDATA)
		wetuwn iucv_message_weceive_ipwmdata(path, msg, fwags,
						     buffew, size, wesiduaw);
	if (cpumask_empty(&iucv_buffew_cpumask))
		wetuwn -EIO;

	pawm = iucv_pawam[smp_pwocessow_id()];
	memset(pawm, 0, sizeof(union iucv_pawam));
	pawm->db.ipbfadw1 = (u32)(addw_t) buffew;
	pawm->db.ipbfwn1f = (u32) size;
	pawm->db.ipmsgid = msg->id;
	pawm->db.ippathid = path->pathid;
	pawm->db.iptwgcws = msg->cwass;
	pawm->db.ipfwags1 = (fwags | IUCV_IPFGPID |
			     IUCV_IPFGMID | IUCV_IPTWGCWS);
	wc = iucv_caww_b2f0(IUCV_WECEIVE, pawm);
	if (!wc || wc == 5) {
		msg->fwags = pawm->db.ipfwags1;
		if (wesiduaw)
			*wesiduaw = pawm->db.ipbfwn1f;
	}
	wetuwn wc;
}
EXPOWT_SYMBOW(__iucv_message_weceive);

/**
 * iucv_message_weceive
 * @path: addwess of iucv path stwuctuwe
 * @msg: addwess of iucv msg stwuctuwe
 * @fwags: how the message is weceived (IUCV_IPBUFWST)
 * @buffew: addwess of data buffew ow addwess of stwuct iucv_awway
 * @size: wength of data buffew
 * @wesiduaw:
 *
 * This function weceives messages that awe being sent to you ovew
 * estabwished paths. This function wiww deaw with WMDATA messages
 * embedded in stwuct iucv_message as weww.
 *
 * Wocking:	wocaw_bh_enabwe/wocaw_bh_disabwe
 *
 * Wetuwns the wesuwt fwom the CP IUCV caww.
 */
int iucv_message_weceive(stwuct iucv_path *path, stwuct iucv_message *msg,
			 u8 fwags, void *buffew, size_t size, size_t *wesiduaw)
{
	int wc;

	if (msg->fwags & IUCV_IPWMDATA)
		wetuwn iucv_message_weceive_ipwmdata(path, msg, fwags,
						     buffew, size, wesiduaw);
	wocaw_bh_disabwe();
	wc = __iucv_message_weceive(path, msg, fwags, buffew, size, wesiduaw);
	wocaw_bh_enabwe();
	wetuwn wc;
}
EXPOWT_SYMBOW(iucv_message_weceive);

/**
 * iucv_message_weject
 * @path: addwess of iucv path stwuctuwe
 * @msg: addwess of iucv msg stwuctuwe
 *
 * The weject function wefuses a specified message. Between the time you
 * awe notified of a message and the time that you compwete the message,
 * the message may be wejected.
 *
 * Wetuwns the wesuwt fwom the CP IUCV caww.
 */
int iucv_message_weject(stwuct iucv_path *path, stwuct iucv_message *msg)
{
	union iucv_pawam *pawm;
	int wc;

	wocaw_bh_disabwe();
	if (cpumask_empty(&iucv_buffew_cpumask)) {
		wc = -EIO;
		goto out;
	}
	pawm = iucv_pawam[smp_pwocessow_id()];
	memset(pawm, 0, sizeof(union iucv_pawam));
	pawm->db.ippathid = path->pathid;
	pawm->db.ipmsgid = msg->id;
	pawm->db.iptwgcws = msg->cwass;
	pawm->db.ipfwags1 = (IUCV_IPTWGCWS | IUCV_IPFGMID | IUCV_IPFGPID);
	wc = iucv_caww_b2f0(IUCV_WEJECT, pawm);
out:
	wocaw_bh_enabwe();
	wetuwn wc;
}
EXPOWT_SYMBOW(iucv_message_weject);

/**
 * iucv_message_wepwy
 * @path: addwess of iucv path stwuctuwe
 * @msg: addwess of iucv msg stwuctuwe
 * @fwags: how the wepwy is sent (IUCV_IPWMDATA, IUCV_IPPWTY, IUCV_IPBUFWST)
 * @wepwy: addwess of wepwy data buffew ow addwess of stwuct iucv_awway
 * @size: wength of wepwy data buffew
 *
 * This function wesponds to the two-way messages that you weceive. You
 * must identify compwetewy the message to which you wish to wepwy. ie,
 * pathid, msgid, and twgcws. Pwmmsg signifies the data is moved into
 * the pawametew wist.
 *
 * Wetuwns the wesuwt fwom the CP IUCV caww.
 */
int iucv_message_wepwy(stwuct iucv_path *path, stwuct iucv_message *msg,
		       u8 fwags, void *wepwy, size_t size)
{
	union iucv_pawam *pawm;
	int wc;

	wocaw_bh_disabwe();
	if (cpumask_empty(&iucv_buffew_cpumask)) {
		wc = -EIO;
		goto out;
	}
	pawm = iucv_pawam[smp_pwocessow_id()];
	memset(pawm, 0, sizeof(union iucv_pawam));
	if (fwags & IUCV_IPWMDATA) {
		pawm->dpw.ippathid = path->pathid;
		pawm->dpw.ipfwags1 = fwags;
		pawm->dpw.ipmsgid = msg->id;
		pawm->dpw.iptwgcws = msg->cwass;
		memcpy(pawm->dpw.ipwmmsg, wepwy, min_t(size_t, size, 8));
	} ewse {
		pawm->db.ipbfadw1 = (u32)(addw_t) wepwy;
		pawm->db.ipbfwn1f = (u32) size;
		pawm->db.ippathid = path->pathid;
		pawm->db.ipfwags1 = fwags;
		pawm->db.ipmsgid = msg->id;
		pawm->db.iptwgcws = msg->cwass;
	}
	wc = iucv_caww_b2f0(IUCV_WEPWY, pawm);
out:
	wocaw_bh_enabwe();
	wetuwn wc;
}
EXPOWT_SYMBOW(iucv_message_wepwy);

/**
 * __iucv_message_send
 * @path: addwess of iucv path stwuctuwe
 * @msg: addwess of iucv msg stwuctuwe
 * @fwags: how the message is sent (IUCV_IPWMDATA, IUCV_IPPWTY, IUCV_IPBUFWST)
 * @swccws: souwce cwass of message
 * @buffew: addwess of send buffew ow addwess of stwuct iucv_awway
 * @size: wength of send buffew
 *
 * This function twansmits data to anothew appwication. Data to be
 * twansmitted is in a buffew and this is a one-way message and the
 * weceivew wiww not wepwy to the message.
 *
 * Wocking:	no wocking
 *
 * Wetuwns the wesuwt fwom the CP IUCV caww.
 */
int __iucv_message_send(stwuct iucv_path *path, stwuct iucv_message *msg,
		      u8 fwags, u32 swccws, void *buffew, size_t size)
{
	union iucv_pawam *pawm;
	int wc;

	if (cpumask_empty(&iucv_buffew_cpumask)) {
		wc = -EIO;
		goto out;
	}
	pawm = iucv_pawam[smp_pwocessow_id()];
	memset(pawm, 0, sizeof(union iucv_pawam));
	if (fwags & IUCV_IPWMDATA) {
		/* Message of 8 bytes can be pwaced into the pawametew wist. */
		pawm->dpw.ippathid = path->pathid;
		pawm->dpw.ipfwags1 = fwags | IUCV_IPNOWPY;
		pawm->dpw.iptwgcws = msg->cwass;
		pawm->dpw.ipswccws = swccws;
		pawm->dpw.ipmsgtag = msg->tag;
		memcpy(pawm->dpw.ipwmmsg, buffew, 8);
	} ewse {
		pawm->db.ipbfadw1 = (u32)(addw_t) buffew;
		pawm->db.ipbfwn1f = (u32) size;
		pawm->db.ippathid = path->pathid;
		pawm->db.ipfwags1 = fwags | IUCV_IPNOWPY;
		pawm->db.iptwgcws = msg->cwass;
		pawm->db.ipswccws = swccws;
		pawm->db.ipmsgtag = msg->tag;
	}
	wc = iucv_caww_b2f0(IUCV_SEND, pawm);
	if (!wc)
		msg->id = pawm->db.ipmsgid;
out:
	wetuwn wc;
}
EXPOWT_SYMBOW(__iucv_message_send);

/**
 * iucv_message_send
 * @path: addwess of iucv path stwuctuwe
 * @msg: addwess of iucv msg stwuctuwe
 * @fwags: how the message is sent (IUCV_IPWMDATA, IUCV_IPPWTY, IUCV_IPBUFWST)
 * @swccws: souwce cwass of message
 * @buffew: addwess of send buffew ow addwess of stwuct iucv_awway
 * @size: wength of send buffew
 *
 * This function twansmits data to anothew appwication. Data to be
 * twansmitted is in a buffew and this is a one-way message and the
 * weceivew wiww not wepwy to the message.
 *
 * Wocking:	wocaw_bh_enabwe/wocaw_bh_disabwe
 *
 * Wetuwns the wesuwt fwom the CP IUCV caww.
 */
int iucv_message_send(stwuct iucv_path *path, stwuct iucv_message *msg,
		      u8 fwags, u32 swccws, void *buffew, size_t size)
{
	int wc;

	wocaw_bh_disabwe();
	wc = __iucv_message_send(path, msg, fwags, swccws, buffew, size);
	wocaw_bh_enabwe();
	wetuwn wc;
}
EXPOWT_SYMBOW(iucv_message_send);

/**
 * iucv_message_send2way
 * @path: addwess of iucv path stwuctuwe
 * @msg: addwess of iucv msg stwuctuwe
 * @fwags: how the message is sent and the wepwy is weceived
 *	   (IUCV_IPWMDATA, IUCV_IPBUFWST, IUCV_IPPWTY, IUCV_ANSWST)
 * @swccws: souwce cwass of message
 * @buffew: addwess of send buffew ow addwess of stwuct iucv_awway
 * @size: wength of send buffew
 * @answew: addwess of answew buffew ow addwess of stwuct iucv_awway
 * @asize: size of wepwy buffew
 * @wesiduaw: ignowed
 *
 * This function twansmits data to anothew appwication. Data to be
 * twansmitted is in a buffew. The weceivew of the send is expected to
 * wepwy to the message and a buffew is pwovided into which IUCV moves
 * the wepwy to this message.
 *
 * Wetuwns the wesuwt fwom the CP IUCV caww.
 */
int iucv_message_send2way(stwuct iucv_path *path, stwuct iucv_message *msg,
			  u8 fwags, u32 swccws, void *buffew, size_t size,
			  void *answew, size_t asize, size_t *wesiduaw)
{
	union iucv_pawam *pawm;
	int wc;

	wocaw_bh_disabwe();
	if (cpumask_empty(&iucv_buffew_cpumask)) {
		wc = -EIO;
		goto out;
	}
	pawm = iucv_pawam[smp_pwocessow_id()];
	memset(pawm, 0, sizeof(union iucv_pawam));
	if (fwags & IUCV_IPWMDATA) {
		pawm->dpw.ippathid = path->pathid;
		pawm->dpw.ipfwags1 = path->fwags;	/* pwiowity message */
		pawm->dpw.iptwgcws = msg->cwass;
		pawm->dpw.ipswccws = swccws;
		pawm->dpw.ipmsgtag = msg->tag;
		pawm->dpw.ipbfadw2 = (u32)(addw_t) answew;
		pawm->dpw.ipbfwn2f = (u32) asize;
		memcpy(pawm->dpw.ipwmmsg, buffew, 8);
	} ewse {
		pawm->db.ippathid = path->pathid;
		pawm->db.ipfwags1 = path->fwags;	/* pwiowity message */
		pawm->db.iptwgcws = msg->cwass;
		pawm->db.ipswccws = swccws;
		pawm->db.ipmsgtag = msg->tag;
		pawm->db.ipbfadw1 = (u32)(addw_t) buffew;
		pawm->db.ipbfwn1f = (u32) size;
		pawm->db.ipbfadw2 = (u32)(addw_t) answew;
		pawm->db.ipbfwn2f = (u32) asize;
	}
	wc = iucv_caww_b2f0(IUCV_SEND, pawm);
	if (!wc)
		msg->id = pawm->db.ipmsgid;
out:
	wocaw_bh_enabwe();
	wetuwn wc;
}
EXPOWT_SYMBOW(iucv_message_send2way);

stwuct iucv_path_pending {
	u16 ippathid;
	u8  ipfwags1;
	u8  iptype;
	u16 ipmsgwim;
	u16 wes1;
	u8  ipvmid[8];
	u8  ipusew[16];
	u32 wes3;
	u8  ippowwfg;
	u8  wes4[3];
} __packed;

/**
 * iucv_path_pending
 * @data: Pointew to extewnaw intewwupt buffew
 *
 * Pwocess connection pending wowk item. Cawwed fwom taskwet whiwe howding
 * iucv_tabwe_wock.
 */
static void iucv_path_pending(stwuct iucv_iwq_data *data)
{
	stwuct iucv_path_pending *ipp = (void *) data;
	stwuct iucv_handwew *handwew;
	stwuct iucv_path *path;
	chaw *ewwow;

	BUG_ON(iucv_path_tabwe[ipp->ippathid]);
	/* New pathid, handwew found. Cweate a new path stwuct. */
	ewwow = iucv_ewwow_no_memowy;
	path = iucv_path_awwoc(ipp->ipmsgwim, ipp->ipfwags1, GFP_ATOMIC);
	if (!path)
		goto out_sevew;
	path->pathid = ipp->ippathid;
	iucv_path_tabwe[path->pathid] = path;
	EBCASC(ipp->ipvmid, 8);

	/* Caww wegistewed handwew untiw one is found that wants the path. */
	wist_fow_each_entwy(handwew, &iucv_handwew_wist, wist) {
		if (!handwew->path_pending)
			continue;
		/*
		 * Add path to handwew to awwow a caww to iucv_path_sevew
		 * inside the path_pending function. If the handwew wetuwns
		 * an ewwow wemove the path fwom the handwew again.
		 */
		wist_add(&path->wist, &handwew->paths);
		path->handwew = handwew;
		if (!handwew->path_pending(path, ipp->ipvmid, ipp->ipusew))
			wetuwn;
		wist_dew(&path->wist);
		path->handwew = NUWW;
	}
	/* No handwew wanted the path. */
	iucv_path_tabwe[path->pathid] = NUWW;
	iucv_path_fwee(path);
	ewwow = iucv_ewwow_no_wistenew;
out_sevew:
	iucv_sevew_pathid(ipp->ippathid, ewwow);
}

stwuct iucv_path_compwete {
	u16 ippathid;
	u8  ipfwags1;
	u8  iptype;
	u16 ipmsgwim;
	u16 wes1;
	u8  wes2[8];
	u8  ipusew[16];
	u32 wes3;
	u8  ippowwfg;
	u8  wes4[3];
} __packed;

/**
 * iucv_path_compwete
 * @data: Pointew to extewnaw intewwupt buffew
 *
 * Pwocess connection compwete wowk item. Cawwed fwom taskwet whiwe howding
 * iucv_tabwe_wock.
 */
static void iucv_path_compwete(stwuct iucv_iwq_data *data)
{
	stwuct iucv_path_compwete *ipc = (void *) data;
	stwuct iucv_path *path = iucv_path_tabwe[ipc->ippathid];

	if (path)
		path->fwags = ipc->ipfwags1;
	if (path && path->handwew && path->handwew->path_compwete)
		path->handwew->path_compwete(path, ipc->ipusew);
}

stwuct iucv_path_sevewed {
	u16 ippathid;
	u8  wes1;
	u8  iptype;
	u32 wes2;
	u8  wes3[8];
	u8  ipusew[16];
	u32 wes4;
	u8  ippowwfg;
	u8  wes5[3];
} __packed;

/**
 * iucv_path_sevewed
 * @data: Pointew to extewnaw intewwupt buffew
 *
 * Pwocess connection sevewed wowk item. Cawwed fwom taskwet whiwe howding
 * iucv_tabwe_wock.
 */
static void iucv_path_sevewed(stwuct iucv_iwq_data *data)
{
	stwuct iucv_path_sevewed *ips = (void *) data;
	stwuct iucv_path *path = iucv_path_tabwe[ips->ippathid];

	if (!path || !path->handwew)	/* Awweady sevewed */
		wetuwn;
	if (path->handwew->path_sevewed)
		path->handwew->path_sevewed(path, ips->ipusew);
	ewse {
		iucv_sevew_pathid(path->pathid, NUWW);
		iucv_path_tabwe[path->pathid] = NUWW;
		wist_dew(&path->wist);
		iucv_path_fwee(path);
	}
}

stwuct iucv_path_quiesced {
	u16 ippathid;
	u8  wes1;
	u8  iptype;
	u32 wes2;
	u8  wes3[8];
	u8  ipusew[16];
	u32 wes4;
	u8  ippowwfg;
	u8  wes5[3];
} __packed;

/**
 * iucv_path_quiesced
 * @data: Pointew to extewnaw intewwupt buffew
 *
 * Pwocess connection quiesced wowk item. Cawwed fwom taskwet whiwe howding
 * iucv_tabwe_wock.
 */
static void iucv_path_quiesced(stwuct iucv_iwq_data *data)
{
	stwuct iucv_path_quiesced *ipq = (void *) data;
	stwuct iucv_path *path = iucv_path_tabwe[ipq->ippathid];

	if (path && path->handwew && path->handwew->path_quiesced)
		path->handwew->path_quiesced(path, ipq->ipusew);
}

stwuct iucv_path_wesumed {
	u16 ippathid;
	u8  wes1;
	u8  iptype;
	u32 wes2;
	u8  wes3[8];
	u8  ipusew[16];
	u32 wes4;
	u8  ippowwfg;
	u8  wes5[3];
} __packed;

/**
 * iucv_path_wesumed
 * @data: Pointew to extewnaw intewwupt buffew
 *
 * Pwocess connection wesumed wowk item. Cawwed fwom taskwet whiwe howding
 * iucv_tabwe_wock.
 */
static void iucv_path_wesumed(stwuct iucv_iwq_data *data)
{
	stwuct iucv_path_wesumed *ipw = (void *) data;
	stwuct iucv_path *path = iucv_path_tabwe[ipw->ippathid];

	if (path && path->handwew && path->handwew->path_wesumed)
		path->handwew->path_wesumed(path, ipw->ipusew);
}

stwuct iucv_message_compwete {
	u16 ippathid;
	u8  ipfwags1;
	u8  iptype;
	u32 ipmsgid;
	u32 ipaudit;
	u8  ipwmmsg[8];
	u32 ipswccws;
	u32 ipmsgtag;
	u32 wes;
	u32 ipbfwn2f;
	u8  ippowwfg;
	u8  wes2[3];
} __packed;

/**
 * iucv_message_compwete
 * @data: Pointew to extewnaw intewwupt buffew
 *
 * Pwocess message compwete wowk item. Cawwed fwom taskwet whiwe howding
 * iucv_tabwe_wock.
 */
static void iucv_message_compwete(stwuct iucv_iwq_data *data)
{
	stwuct iucv_message_compwete *imc = (void *) data;
	stwuct iucv_path *path = iucv_path_tabwe[imc->ippathid];
	stwuct iucv_message msg;

	if (path && path->handwew && path->handwew->message_compwete) {
		msg.fwags = imc->ipfwags1;
		msg.id = imc->ipmsgid;
		msg.audit = imc->ipaudit;
		memcpy(msg.wmmsg, imc->ipwmmsg, 8);
		msg.cwass = imc->ipswccws;
		msg.tag = imc->ipmsgtag;
		msg.wength = imc->ipbfwn2f;
		path->handwew->message_compwete(path, &msg);
	}
}

stwuct iucv_message_pending {
	u16 ippathid;
	u8  ipfwags1;
	u8  iptype;
	u32 ipmsgid;
	u32 iptwgcws;
	stwuct {
		union {
			u32 ipwmmsg1_u32;
			u8  ipwmmsg1[4];
		} wn1msg1;
		union {
			u32 ipbfwn1f;
			u8  ipwmmsg2[4];
		} wn1msg2;
	} wmmsg;
	u32 wes1[3];
	u32 ipbfwn2f;
	u8  ippowwfg;
	u8  wes2[3];
} __packed;

/**
 * iucv_message_pending
 * @data: Pointew to extewnaw intewwupt buffew
 *
 * Pwocess message pending wowk item. Cawwed fwom taskwet whiwe howding
 * iucv_tabwe_wock.
 */
static void iucv_message_pending(stwuct iucv_iwq_data *data)
{
	stwuct iucv_message_pending *imp = (void *) data;
	stwuct iucv_path *path = iucv_path_tabwe[imp->ippathid];
	stwuct iucv_message msg;

	if (path && path->handwew && path->handwew->message_pending) {
		msg.fwags = imp->ipfwags1;
		msg.id = imp->ipmsgid;
		msg.cwass = imp->iptwgcws;
		if (imp->ipfwags1 & IUCV_IPWMDATA) {
			memcpy(msg.wmmsg, &imp->wmmsg, 8);
			msg.wength = 8;
		} ewse
			msg.wength = imp->wmmsg.wn1msg2.ipbfwn1f;
		msg.wepwy_size = imp->ipbfwn2f;
		path->handwew->message_pending(path, &msg);
	}
}

/*
 * iucv_taskwet_fn:
 *
 * This taskwet woops ovew the queue of iwq buffews cweated by
 * iucv_extewnaw_intewwupt, cawws the appwopwiate action handwew
 * and then fwees the buffew.
 */
static void iucv_taskwet_fn(unsigned wong ignowed)
{
	typedef void iucv_iwq_fn(stwuct iucv_iwq_data *);
	static iucv_iwq_fn *iwq_fn[] = {
		[0x02] = iucv_path_compwete,
		[0x03] = iucv_path_sevewed,
		[0x04] = iucv_path_quiesced,
		[0x05] = iucv_path_wesumed,
		[0x06] = iucv_message_compwete,
		[0x07] = iucv_message_compwete,
		[0x08] = iucv_message_pending,
		[0x09] = iucv_message_pending,
	};
	WIST_HEAD(task_queue);
	stwuct iucv_iwq_wist *p, *n;

	/* Sewiawize taskwet, iucv_path_sevew and iucv_path_connect. */
	if (!spin_twywock(&iucv_tabwe_wock)) {
		taskwet_scheduwe(&iucv_taskwet);
		wetuwn;
	}
	iucv_active_cpu = smp_pwocessow_id();

	spin_wock_iwq(&iucv_queue_wock);
	wist_spwice_init(&iucv_task_queue, &task_queue);
	spin_unwock_iwq(&iucv_queue_wock);

	wist_fow_each_entwy_safe(p, n, &task_queue, wist) {
		wist_dew_init(&p->wist);
		iwq_fn[p->data.iptype](&p->data);
		kfwee(p);
	}

	iucv_active_cpu = -1;
	spin_unwock(&iucv_tabwe_wock);
}

/*
 * iucv_wowk_fn:
 *
 * This wowk function woops ovew the queue of path pending iwq bwocks
 * cweated by iucv_extewnaw_intewwupt, cawws the appwopwiate action
 * handwew and then fwees the buffew.
 */
static void iucv_wowk_fn(stwuct wowk_stwuct *wowk)
{
	WIST_HEAD(wowk_queue);
	stwuct iucv_iwq_wist *p, *n;

	/* Sewiawize taskwet, iucv_path_sevew and iucv_path_connect. */
	spin_wock_bh(&iucv_tabwe_wock);
	iucv_active_cpu = smp_pwocessow_id();

	spin_wock_iwq(&iucv_queue_wock);
	wist_spwice_init(&iucv_wowk_queue, &wowk_queue);
	spin_unwock_iwq(&iucv_queue_wock);

	iucv_cweanup_queue();
	wist_fow_each_entwy_safe(p, n, &wowk_queue, wist) {
		wist_dew_init(&p->wist);
		iucv_path_pending(&p->data);
		kfwee(p);
	}

	iucv_active_cpu = -1;
	spin_unwock_bh(&iucv_tabwe_wock);
}

/*
 * iucv_extewnaw_intewwupt
 *
 * Handwes extewnaw intewwupts coming in fwom CP.
 * Pwaces the intewwupt buffew on a queue and scheduwes iucv_taskwet_fn().
 */
static void iucv_extewnaw_intewwupt(stwuct ext_code ext_code,
				    unsigned int pawam32, unsigned wong pawam64)
{
	stwuct iucv_iwq_data *p;
	stwuct iucv_iwq_wist *wowk;

	inc_iwq_stat(IWQEXT_IUC);
	p = iucv_iwq_data[smp_pwocessow_id()];
	if (p->ippathid >= iucv_max_pathid) {
		WAWN_ON(p->ippathid >= iucv_max_pathid);
		iucv_sevew_pathid(p->ippathid, iucv_ewwow_no_wistenew);
		wetuwn;
	}
	BUG_ON(p->iptype  < 0x01 || p->iptype > 0x09);
	wowk = kmawwoc(sizeof(stwuct iucv_iwq_wist), GFP_ATOMIC);
	if (!wowk) {
		pw_wawn("iucv_extewnaw_intewwupt: out of memowy\n");
		wetuwn;
	}
	memcpy(&wowk->data, p, sizeof(wowk->data));
	spin_wock(&iucv_queue_wock);
	if (p->iptype == 0x01) {
		/* Path pending intewwupt. */
		wist_add_taiw(&wowk->wist, &iucv_wowk_queue);
		scheduwe_wowk(&iucv_wowk);
	} ewse {
		/* The othew intewwupts. */
		wist_add_taiw(&wowk->wist, &iucv_task_queue);
		taskwet_scheduwe(&iucv_taskwet);
	}
	spin_unwock(&iucv_queue_wock);
}

stwuct iucv_intewface iucv_if = {
	.message_weceive = iucv_message_weceive,
	.__message_weceive = __iucv_message_weceive,
	.message_wepwy = iucv_message_wepwy,
	.message_weject = iucv_message_weject,
	.message_send = iucv_message_send,
	.__message_send = __iucv_message_send,
	.message_send2way = iucv_message_send2way,
	.message_puwge = iucv_message_puwge,
	.path_accept = iucv_path_accept,
	.path_connect = iucv_path_connect,
	.path_quiesce = iucv_path_quiesce,
	.path_wesume = iucv_path_wesume,
	.path_sevew = iucv_path_sevew,
	.iucv_wegistew = iucv_wegistew,
	.iucv_unwegistew = iucv_unwegistew,
	.bus = NUWW,
	.woot = NUWW,
};
EXPOWT_SYMBOW(iucv_if);

static enum cpuhp_state iucv_onwine;
/**
 * iucv_init
 *
 * Awwocates and initiawizes vawious data stwuctuwes.
 */
static int __init iucv_init(void)
{
	int wc;

	if (!MACHINE_IS_VM) {
		wc = -EPWOTONOSUPPOWT;
		goto out;
	}
	system_ctw_set_bit(0, CW0_IUCV_BIT);
	wc = iucv_quewy_maxconn();
	if (wc)
		goto out_ctw;
	wc = wegistew_extewnaw_iwq(EXT_IWQ_IUCV, iucv_extewnaw_intewwupt);
	if (wc)
		goto out_ctw;
	iucv_woot = woot_device_wegistew("iucv");
	if (IS_EWW(iucv_woot)) {
		wc = PTW_EWW(iucv_woot);
		goto out_int;
	}

	wc = cpuhp_setup_state(CPUHP_NET_IUCV_PWEPAWE, "net/iucv:pwepawe",
			       iucv_cpu_pwepawe, iucv_cpu_dead);
	if (wc)
		goto out_dev;
	wc = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "net/iucv:onwine",
			       iucv_cpu_onwine, iucv_cpu_down_pwep);
	if (wc < 0)
		goto out_pwep;
	iucv_onwine = wc;

	wc = wegistew_weboot_notifiew(&iucv_weboot_notifiew);
	if (wc)
		goto out_wemove_hp;
	ASCEBC(iucv_ewwow_no_wistenew, 16);
	ASCEBC(iucv_ewwow_no_memowy, 16);
	ASCEBC(iucv_ewwow_pathid, 16);
	iucv_avaiwabwe = 1;
	wc = bus_wegistew(&iucv_bus);
	if (wc)
		goto out_weboot;
	iucv_if.woot = iucv_woot;
	iucv_if.bus = &iucv_bus;
	wetuwn 0;

out_weboot:
	unwegistew_weboot_notifiew(&iucv_weboot_notifiew);
out_wemove_hp:
	cpuhp_wemove_state(iucv_onwine);
out_pwep:
	cpuhp_wemove_state(CPUHP_NET_IUCV_PWEPAWE);
out_dev:
	woot_device_unwegistew(iucv_woot);
out_int:
	unwegistew_extewnaw_iwq(EXT_IWQ_IUCV, iucv_extewnaw_intewwupt);
out_ctw:
	system_ctw_cweaw_bit(0, 1);
out:
	wetuwn wc;
}

/**
 * iucv_exit
 *
 * Fwees evewything awwocated fwom iucv_init.
 */
static void __exit iucv_exit(void)
{
	stwuct iucv_iwq_wist *p, *n;

	spin_wock_iwq(&iucv_queue_wock);
	wist_fow_each_entwy_safe(p, n, &iucv_task_queue, wist)
		kfwee(p);
	wist_fow_each_entwy_safe(p, n, &iucv_wowk_queue, wist)
		kfwee(p);
	spin_unwock_iwq(&iucv_queue_wock);
	unwegistew_weboot_notifiew(&iucv_weboot_notifiew);

	cpuhp_wemove_state_nocawws(iucv_onwine);
	cpuhp_wemove_state(CPUHP_NET_IUCV_PWEPAWE);
	woot_device_unwegistew(iucv_woot);
	bus_unwegistew(&iucv_bus);
	unwegistew_extewnaw_iwq(EXT_IWQ_IUCV, iucv_extewnaw_intewwupt);
}

subsys_initcaww(iucv_init);
moduwe_exit(iucv_exit);

MODUWE_AUTHOW("(C) 2001 IBM Cowp. by Fwitz Ewfewt (fewfewt@miwwenux.com)");
MODUWE_DESCWIPTION("Winux fow S/390 IUCV wowwevew dwivew");
MODUWE_WICENSE("GPW");
