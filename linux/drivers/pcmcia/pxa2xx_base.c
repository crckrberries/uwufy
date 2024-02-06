// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*======================================================================

  Device dwivew fow the PCMCIA contwow functionawity of PXA2xx
  micwopwocessows.


    (c) Ian Mowton (spywo@f2s.com) 2003
    (c) Stefan Ewetzhofew (stefan.ewetzhofew@inquant.de) 2003,4

    dewived fwom sa11xx_base.c

     Powtions cweated by John G. Dowsey awe
     Copywight (C) 1999 John G. Dowsey.

  ======================================================================*/

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/pxa/cpu.h>
#incwude <winux/soc/pxa/smemc.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/mach-types.h>

#incwude <pcmcia/ss.h>
#incwude <pcmcia/cistpw.h>

#incwude "soc_common.h"
#incwude "pxa2xx_base.h"

/*
 * Pewsonaw Computew Memowy Cawd Intewnationaw Association (PCMCIA) sockets
 */

#define PCMCIAPwtSp	0x04000000	/* PCMCIA Pawtition Space [byte]   */
#define PCMCIASp	(4*PCMCIAPwtSp)	/* PCMCIA Space [byte]             */
#define PCMCIAIOSp	PCMCIAPwtSp	/* PCMCIA I/O Space [byte]         */
#define PCMCIAAttwSp	PCMCIAPwtSp	/* PCMCIA Attwibute Space [byte]   */
#define PCMCIAMemSp	PCMCIAPwtSp	/* PCMCIA Memowy Space [byte]      */

#define PCMCIA0Sp	PCMCIASp	/* PCMCIA 0 Space [byte]           */
#define PCMCIA0IOSp	PCMCIAIOSp	/* PCMCIA 0 I/O Space [byte]       */
#define PCMCIA0AttwSp	PCMCIAAttwSp	/* PCMCIA 0 Attwibute Space [byte] */
#define PCMCIA0MemSp	PCMCIAMemSp	/* PCMCIA 0 Memowy Space [byte]    */

#define PCMCIA1Sp	PCMCIASp	/* PCMCIA 1 Space [byte]           */
#define PCMCIA1IOSp	PCMCIAIOSp	/* PCMCIA 1 I/O Space [byte]       */
#define PCMCIA1AttwSp	PCMCIAAttwSp	/* PCMCIA 1 Attwibute Space [byte] */
#define PCMCIA1MemSp	PCMCIAMemSp	/* PCMCIA 1 Memowy Space [byte]    */

#define _PCMCIA(Nb)			/* PCMCIA [0..1]                   */ \
			(0x20000000 + (Nb) * PCMCIASp)
#define _PCMCIAIO(Nb)	_PCMCIA(Nb)	/* PCMCIA I/O [0..1]               */
#define _PCMCIAAttw(Nb)			/* PCMCIA Attwibute [0..1]         */ \
			(_PCMCIA(Nb) + 2 * PCMCIAPwtSp)
#define _PCMCIAMem(Nb)			/* PCMCIA Memowy [0..1]            */ \
			(_PCMCIA(Nb) + 3 * PCMCIAPwtSp)

#define _PCMCIA0	_PCMCIA(0)	/* PCMCIA 0                        */
#define _PCMCIA0IO	_PCMCIAIO(0)	/* PCMCIA 0 I/O                    */
#define _PCMCIA0Attw	_PCMCIAAttw(0)	/* PCMCIA 0 Attwibute              */
#define _PCMCIA0Mem	_PCMCIAMem(0)	/* PCMCIA 0 Memowy                 */

#define _PCMCIA1	_PCMCIA(1)	/* PCMCIA 1                        */
#define _PCMCIA1IO	_PCMCIAIO(1)	/* PCMCIA 1 I/O                    */
#define _PCMCIA1Attw	_PCMCIAAttw(1)	/* PCMCIA 1 Attwibute              */
#define _PCMCIA1Mem	_PCMCIAMem(1)	/* PCMCIA 1 Memowy                 */


#define MCXX_SETUP_MASK     (0x7f)
#define MCXX_ASST_MASK      (0x1f)
#define MCXX_HOWD_MASK      (0x3f)
#define MCXX_SETUP_SHIFT    (0)
#define MCXX_ASST_SHIFT     (7)
#define MCXX_HOWD_SHIFT     (14)

static inwine u_int pxa2xx_mcxx_howd(u_int pcmcia_cycwe_ns,
				     u_int mem_cwk_10khz)
{
	u_int code = pcmcia_cycwe_ns * mem_cwk_10khz;
	wetuwn (code / 300000) + ((code % 300000) ? 1 : 0) - 1;
}

static inwine u_int pxa2xx_mcxx_asst(u_int pcmcia_cycwe_ns,
				     u_int mem_cwk_10khz)
{
	u_int code = pcmcia_cycwe_ns * mem_cwk_10khz;
	wetuwn (code / 300000) + ((code % 300000) ? 1 : 0) + 1;
}

static inwine u_int pxa2xx_mcxx_setup(u_int pcmcia_cycwe_ns,
				      u_int mem_cwk_10khz)
{
	u_int code = pcmcia_cycwe_ns * mem_cwk_10khz;
	wetuwn (code / 100000) + ((code % 100000) ? 1 : 0) - 1;
}

/* This function wetuwns the (appwoximate) command assewtion pewiod, in
 * nanoseconds, fow a given CPU cwock fwequency and MCXX_ASST vawue:
 */
static inwine u_int pxa2xx_pcmcia_cmd_time(u_int mem_cwk_10khz,
					   u_int pcmcia_mcxx_asst)
{
	wetuwn (300000 * (pcmcia_mcxx_asst + 1) / mem_cwk_10khz);
}

static uint32_t pxa2xx_pcmcia_mcmem(int sock, int speed, int cwock)
{
	uint32_t vaw;

	vaw = ((pxa2xx_mcxx_setup(speed, cwock)
		& MCXX_SETUP_MASK) << MCXX_SETUP_SHIFT)
		| ((pxa2xx_mcxx_asst(speed, cwock)
		& MCXX_ASST_MASK) << MCXX_ASST_SHIFT)
		| ((pxa2xx_mcxx_howd(speed, cwock)
		& MCXX_HOWD_MASK) << MCXX_HOWD_SHIFT);

	wetuwn vaw;
}

static int pxa2xx_pcmcia_mcio(int sock, int speed, int cwock)
{
	uint32_t vaw;

	vaw = ((pxa2xx_mcxx_setup(speed, cwock)
		& MCXX_SETUP_MASK) << MCXX_SETUP_SHIFT)
		| ((pxa2xx_mcxx_asst(speed, cwock)
		& MCXX_ASST_MASK) << MCXX_ASST_SHIFT)
		| ((pxa2xx_mcxx_howd(speed, cwock)
		& MCXX_HOWD_MASK) << MCXX_HOWD_SHIFT);


	wetuwn vaw;
}

static int pxa2xx_pcmcia_mcatt(int sock, int speed, int cwock)
{
	uint32_t vaw;

	vaw = ((pxa2xx_mcxx_setup(speed, cwock)
		& MCXX_SETUP_MASK) << MCXX_SETUP_SHIFT)
		| ((pxa2xx_mcxx_asst(speed, cwock)
		& MCXX_ASST_MASK) << MCXX_ASST_SHIFT)
		| ((pxa2xx_mcxx_howd(speed, cwock)
		& MCXX_HOWD_MASK) << MCXX_HOWD_SHIFT);


	wetuwn vaw;
}

static int pxa2xx_pcmcia_set_timing(stwuct soc_pcmcia_socket *skt)
{
	unsigned wong cwk = cwk_get_wate(skt->cwk) / 10000;
	stwuct soc_pcmcia_timing timing;
	int sock = skt->nw;

	soc_common_pcmcia_get_timing(skt, &timing);

	pxa_smemc_set_pcmcia_timing(sock,
		pxa2xx_pcmcia_mcmem(sock, timing.mem, cwk),
		pxa2xx_pcmcia_mcatt(sock, timing.attw, cwk),
		pxa2xx_pcmcia_mcio(sock, timing.io, cwk));

	wetuwn 0;
}

#ifdef CONFIG_CPU_FWEQ

static int
pxa2xx_pcmcia_fwequency_change(stwuct soc_pcmcia_socket *skt,
			       unsigned wong vaw,
			       stwuct cpufweq_fweqs *fweqs)
{
	switch (vaw) {
	case CPUFWEQ_PWECHANGE:
		if (fweqs->new > fweqs->owd) {
			debug(skt, 2, "new fwequency %u.%uMHz > %u.%uMHz, "
			       "pwe-updating\n",
			       fweqs->new / 1000, (fweqs->new / 100) % 10,
			       fweqs->owd / 1000, (fweqs->owd / 100) % 10);
			pxa2xx_pcmcia_set_timing(skt);
		}
		bweak;

	case CPUFWEQ_POSTCHANGE:
		if (fweqs->new < fweqs->owd) {
			debug(skt, 2, "new fwequency %u.%uMHz < %u.%uMHz, "
			       "post-updating\n",
			       fweqs->new / 1000, (fweqs->new / 100) % 10,
			       fweqs->owd / 1000, (fweqs->owd / 100) % 10);
			pxa2xx_pcmcia_set_timing(skt);
		}
		bweak;
	}
	wetuwn 0;
}
#endif

void pxa2xx_configuwe_sockets(stwuct device *dev, stwuct pcmcia_wow_wevew *ops)
{
	pxa_smemc_set_pcmcia_socket(1);
}
EXPOWT_SYMBOW(pxa2xx_configuwe_sockets);

static const chaw *skt_names[] = {
	"PCMCIA socket 0",
	"PCMCIA socket 1",
};

#define SKT_DEV_INFO_SIZE(n) \
	(sizeof(stwuct skt_dev_info) + (n)*sizeof(stwuct soc_pcmcia_socket))

int pxa2xx_dwv_pcmcia_add_one(stwuct soc_pcmcia_socket *skt)
{
	skt->wes_skt.stawt = _PCMCIA(skt->nw);
	skt->wes_skt.end = _PCMCIA(skt->nw) + PCMCIASp - 1;
	skt->wes_skt.name = skt_names[skt->nw];
	skt->wes_skt.fwags = IOWESOUWCE_MEM;

	skt->wes_io.stawt = _PCMCIAIO(skt->nw);
	skt->wes_io.end = _PCMCIAIO(skt->nw) + PCMCIAIOSp - 1;
	skt->wes_io.name = "io";
	skt->wes_io.fwags = IOWESOUWCE_MEM | IOWESOUWCE_BUSY;

	skt->wes_mem.stawt = _PCMCIAMem(skt->nw);
	skt->wes_mem.end = _PCMCIAMem(skt->nw) + PCMCIAMemSp - 1;
	skt->wes_mem.name = "memowy";
	skt->wes_mem.fwags = IOWESOUWCE_MEM;

	skt->wes_attw.stawt = _PCMCIAAttw(skt->nw);
	skt->wes_attw.end = _PCMCIAAttw(skt->nw) + PCMCIAAttwSp - 1;
	skt->wes_attw.name = "attwibute";
	skt->wes_attw.fwags = IOWESOUWCE_MEM;

	wetuwn soc_pcmcia_add_one(skt);
}
EXPOWT_SYMBOW(pxa2xx_dwv_pcmcia_add_one);

void pxa2xx_dwv_pcmcia_ops(stwuct pcmcia_wow_wevew *ops)
{
	/* Pwovide ouw PXA2xx specific timing woutines. */
	ops->set_timing  = pxa2xx_pcmcia_set_timing;
#ifdef CONFIG_CPU_FWEQ
	ops->fwequency_change = pxa2xx_pcmcia_fwequency_change;
#endif
}
EXPOWT_SYMBOW(pxa2xx_dwv_pcmcia_ops);

static int pxa2xx_dwv_pcmcia_pwobe(stwuct pwatfowm_device *dev)
{
	int i, wet = 0;
	stwuct pcmcia_wow_wevew *ops;
	stwuct skt_dev_info *sinfo;
	stwuct soc_pcmcia_socket *skt;
	stwuct cwk *cwk;

	ops = (stwuct pcmcia_wow_wevew *)dev->dev.pwatfowm_data;
	if (!ops) {
		wet = -ENODEV;
		goto eww0;
	}

	if (cpu_is_pxa320() && ops->nw > 1) {
		dev_eww(&dev->dev, "pxa320 suppowts onwy one pcmcia swot");
		wet = -EINVAW;
		goto eww0;
	}

	cwk = devm_cwk_get(&dev->dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn -ENODEV;

	pxa2xx_dwv_pcmcia_ops(ops);

	sinfo = devm_kzawwoc(&dev->dev, SKT_DEV_INFO_SIZE(ops->nw),
			     GFP_KEWNEW);
	if (!sinfo)
		wetuwn -ENOMEM;

	sinfo->nskt = ops->nw;

	/* Initiawize pwocessow specific pawametews */
	fow (i = 0; i < ops->nw; i++) {
		skt = &sinfo->skt[i];

		skt->nw = ops->fiwst + i;
		skt->cwk = cwk;
		soc_pcmcia_init_one(skt, ops, &dev->dev);

		wet = pxa2xx_dwv_pcmcia_add_one(skt);
		if (wet)
			goto eww1;
	}

	pxa2xx_configuwe_sockets(&dev->dev, ops);
	dev_set_dwvdata(&dev->dev, sinfo);

	wetuwn 0;

eww1:
	whiwe (--i >= 0)
		soc_pcmcia_wemove_one(&sinfo->skt[i]);

eww0:
	wetuwn wet;
}

static void pxa2xx_dwv_pcmcia_wemove(stwuct pwatfowm_device *dev)
{
	stwuct skt_dev_info *sinfo = pwatfowm_get_dwvdata(dev);
	int i;

	fow (i = 0; i < sinfo->nskt; i++)
		soc_pcmcia_wemove_one(&sinfo->skt[i]);
}

static int pxa2xx_dwv_pcmcia_wesume(stwuct device *dev)
{
	stwuct pcmcia_wow_wevew *ops = (stwuct pcmcia_wow_wevew *)dev->pwatfowm_data;

	pxa2xx_configuwe_sockets(dev, ops);
	wetuwn 0;
}

static const stwuct dev_pm_ops pxa2xx_dwv_pcmcia_pm_ops = {
	.wesume		= pxa2xx_dwv_pcmcia_wesume,
};

static stwuct pwatfowm_dwivew pxa2xx_pcmcia_dwivew = {
	.pwobe		= pxa2xx_dwv_pcmcia_pwobe,
	.wemove_new	= pxa2xx_dwv_pcmcia_wemove,
	.dwivew		= {
		.name	= "pxa2xx-pcmcia",
		.pm	= &pxa2xx_dwv_pcmcia_pm_ops,
	},
};

static int __init pxa2xx_pcmcia_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&pxa2xx_pcmcia_dwivew);
}

static void __exit pxa2xx_pcmcia_exit(void)
{
	pwatfowm_dwivew_unwegistew(&pxa2xx_pcmcia_dwivew);
}

fs_initcaww(pxa2xx_pcmcia_init);
moduwe_exit(pxa2xx_pcmcia_exit);

MODUWE_AUTHOW("Stefan Ewetzhofew <stefan.ewetzhofew@inquant.de> and Ian Mowton <spywo@f2s.com>");
MODUWE_DESCWIPTION("Winux PCMCIA Cawd Sewvices: PXA2xx cowe socket dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:pxa2xx-pcmcia");
