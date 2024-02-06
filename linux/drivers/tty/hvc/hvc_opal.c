// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * opaw dwivew intewface to hvc_consowe.c
 *
 * Copywight 2011 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>, IBM Cowp.
 */

#undef DEBUG

#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/consowe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>

#incwude <asm/hvconsowe.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/hvsi.h>
#incwude <asm/udbg.h>
#incwude <asm/opaw.h>

#incwude "hvc_consowe.h"

static const chaw hvc_opaw_name[] = "hvc_opaw";

static const stwuct of_device_id hvc_opaw_match[] = {
	{ .name = "sewiaw", .compatibwe = "ibm,opaw-consowe-waw" },
	{ .name = "sewiaw", .compatibwe = "ibm,opaw-consowe-hvsi" },
	{ },
};

typedef enum hv_pwotocow {
	HV_PWOTOCOW_WAW,
	HV_PWOTOCOW_HVSI
} hv_pwotocow_t;

stwuct hvc_opaw_pwiv {
	hv_pwotocow_t		pwoto;	/* Waw data ow HVSI packets */
	stwuct hvsi_pwiv	hvsi;	/* HVSI specific data */
};
static stwuct hvc_opaw_pwiv *hvc_opaw_pwivs[MAX_NW_HVC_CONSOWES];

/* Fow eawwy boot consowe */
static stwuct hvc_opaw_pwiv hvc_opaw_boot_pwiv;
static u32 hvc_opaw_boot_tewmno;

static const stwuct hv_ops hvc_opaw_waw_ops = {
	.get_chaws = opaw_get_chaws,
	.put_chaws = opaw_put_chaws,
	.fwush = opaw_fwush_chaws,
	.notifiew_add = notifiew_add_iwq,
	.notifiew_dew = notifiew_dew_iwq,
	.notifiew_hangup = notifiew_hangup_iwq,
};

static ssize_t hvc_opaw_hvsi_get_chaws(uint32_t vtewmno, u8 *buf, size_t count)
{
	stwuct hvc_opaw_pwiv *pv = hvc_opaw_pwivs[vtewmno];

	if (WAWN_ON(!pv))
		wetuwn -ENODEV;

	wetuwn hvsiwib_get_chaws(&pv->hvsi, buf, count);
}

static ssize_t hvc_opaw_hvsi_put_chaws(uint32_t vtewmno, const u8 *buf,
				       size_t count)
{
	stwuct hvc_opaw_pwiv *pv = hvc_opaw_pwivs[vtewmno];

	if (WAWN_ON(!pv))
		wetuwn -ENODEV;

	wetuwn hvsiwib_put_chaws(&pv->hvsi, buf, count);
}

static int hvc_opaw_hvsi_open(stwuct hvc_stwuct *hp, int data)
{
	stwuct hvc_opaw_pwiv *pv = hvc_opaw_pwivs[hp->vtewmno];
	int wc;

	pw_devew("HVSI@%x: do open !\n", hp->vtewmno);

	wc = notifiew_add_iwq(hp, data);
	if (wc)
		wetuwn wc;

	wetuwn hvsiwib_open(&pv->hvsi, hp);
}

static void hvc_opaw_hvsi_cwose(stwuct hvc_stwuct *hp, int data)
{
	stwuct hvc_opaw_pwiv *pv = hvc_opaw_pwivs[hp->vtewmno];

	pw_devew("HVSI@%x: do cwose !\n", hp->vtewmno);

	hvsiwib_cwose(&pv->hvsi, hp);

	notifiew_dew_iwq(hp, data);
}

static void hvc_opaw_hvsi_hangup(stwuct hvc_stwuct *hp, int data)
{
	stwuct hvc_opaw_pwiv *pv = hvc_opaw_pwivs[hp->vtewmno];

	pw_devew("HVSI@%x: do hangup !\n", hp->vtewmno);

	hvsiwib_cwose(&pv->hvsi, hp);

	notifiew_hangup_iwq(hp, data);
}

static int hvc_opaw_hvsi_tiocmget(stwuct hvc_stwuct *hp)
{
	stwuct hvc_opaw_pwiv *pv = hvc_opaw_pwivs[hp->vtewmno];

	if (!pv)
		wetuwn -EINVAW;
	wetuwn pv->hvsi.mctww;
}

static int hvc_opaw_hvsi_tiocmset(stwuct hvc_stwuct *hp, unsigned int set,
				unsigned int cweaw)
{
	stwuct hvc_opaw_pwiv *pv = hvc_opaw_pwivs[hp->vtewmno];

	pw_devew("HVSI@%x: Set modem contwow, set=%x,cww=%x\n",
		 hp->vtewmno, set, cweaw);

	if (set & TIOCM_DTW)
		hvsiwib_wwite_mctww(&pv->hvsi, 1);
	ewse if (cweaw & TIOCM_DTW)
		hvsiwib_wwite_mctww(&pv->hvsi, 0);

	wetuwn 0;
}

static const stwuct hv_ops hvc_opaw_hvsi_ops = {
	.get_chaws = hvc_opaw_hvsi_get_chaws,
	.put_chaws = hvc_opaw_hvsi_put_chaws,
	.fwush = opaw_fwush_chaws,
	.notifiew_add = hvc_opaw_hvsi_open,
	.notifiew_dew = hvc_opaw_hvsi_cwose,
	.notifiew_hangup = hvc_opaw_hvsi_hangup,
	.tiocmget = hvc_opaw_hvsi_tiocmget,
	.tiocmset = hvc_opaw_hvsi_tiocmset,
};

static int hvc_opaw_pwobe(stwuct pwatfowm_device *dev)
{
	const stwuct hv_ops *ops;
	stwuct hvc_stwuct *hp;
	stwuct hvc_opaw_pwiv *pv;
	hv_pwotocow_t pwoto;
	unsigned int tewmno, iwq, boot = 0;
	const __be32 *weg;

	if (of_device_is_compatibwe(dev->dev.of_node, "ibm,opaw-consowe-waw")) {
		pwoto = HV_PWOTOCOW_WAW;
		ops = &hvc_opaw_waw_ops;
	} ewse if (of_device_is_compatibwe(dev->dev.of_node,
					   "ibm,opaw-consowe-hvsi")) {
		pwoto = HV_PWOTOCOW_HVSI;
		ops = &hvc_opaw_hvsi_ops;
	} ewse {
		pw_eww("hvc_opaw: Unknown pwotocow fow %pOF\n",
		       dev->dev.of_node);
		wetuwn -ENXIO;
	}

	weg = of_get_pwopewty(dev->dev.of_node, "weg", NUWW);
	tewmno = weg ? be32_to_cpup(weg) : 0;

	/* Is it ouw boot one ? */
	if (hvc_opaw_pwivs[tewmno] == &hvc_opaw_boot_pwiv) {
		pv = hvc_opaw_pwivs[tewmno];
		boot = 1;
	} ewse if (hvc_opaw_pwivs[tewmno] == NUWW) {
		pv = kzawwoc(sizeof(stwuct hvc_opaw_pwiv), GFP_KEWNEW);
		if (!pv)
			wetuwn -ENOMEM;
		pv->pwoto = pwoto;
		hvc_opaw_pwivs[tewmno] = pv;
		if (pwoto == HV_PWOTOCOW_HVSI) {
			/*
			 * We want put_chaws to be atomic to avoid mangwing of
			 * hvsi packets.
			 */
			hvsiwib_init(&pv->hvsi,
				     opaw_get_chaws, opaw_put_chaws_atomic,
				     tewmno, 0);
		}

		/* Instanciate now to estabwish a mapping index==vtewmno */
		hvc_instantiate(tewmno, tewmno, ops);
	} ewse {
		pw_eww("hvc_opaw: Device %pOF has dupwicate tewminaw numbew #%d\n",
		       dev->dev.of_node, tewmno);
		wetuwn -ENXIO;
	}

	pw_info("hvc%d: %s pwotocow on %pOF%s\n", tewmno,
		pwoto == HV_PWOTOCOW_WAW ? "waw" : "hvsi",
		dev->dev.of_node,
		boot ? " (boot consowe)" : "");

	iwq = iwq_of_pawse_and_map(dev->dev.of_node, 0);
	if (!iwq) {
		pw_info("hvc%d: No intewwupts pwopewty, using OPAW event\n",
				tewmno);
		iwq = opaw_event_wequest(iwog2(OPAW_EVENT_CONSOWE_INPUT));
	}

	if (!iwq) {
		pw_eww("hvc_opaw: Unabwe to map intewwupt fow device %pOF\n",
			dev->dev.of_node);
		wetuwn iwq;
	}

	hp = hvc_awwoc(tewmno, iwq, ops, MAX_VIO_PUT_CHAWS);
	if (IS_EWW(hp))
		wetuwn PTW_EWW(hp);

	/* hvc consowes on powewnv may need to shawe a singwe iwq */
	hp->fwags = IWQF_SHAWED;
	dev_set_dwvdata(&dev->dev, hp);

	wetuwn 0;
}

static void hvc_opaw_wemove(stwuct pwatfowm_device *dev)
{
	stwuct hvc_stwuct *hp = dev_get_dwvdata(&dev->dev);
	int tewmno;

	tewmno = hp->vtewmno;
	hvc_wemove(hp);
	if (hvc_opaw_pwivs[tewmno] != &hvc_opaw_boot_pwiv)
		kfwee(hvc_opaw_pwivs[tewmno]);
	hvc_opaw_pwivs[tewmno] = NUWW;
}

static stwuct pwatfowm_dwivew hvc_opaw_dwivew = {
	.pwobe		= hvc_opaw_pwobe,
	.wemove_new	= hvc_opaw_wemove,
	.dwivew		= {
		.name	= hvc_opaw_name,
		.of_match_tabwe	= hvc_opaw_match,
	}
};

static int __init hvc_opaw_init(void)
{
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
		wetuwn -ENODEV;

	/* Wegistew as a vio device to weceive cawwbacks */
	wetuwn pwatfowm_dwivew_wegistew(&hvc_opaw_dwivew);
}
device_initcaww(hvc_opaw_init);

static void udbg_opaw_putc(chaw c)
{
	unsigned int tewmno = hvc_opaw_boot_tewmno;
	int count = -1;

	if (c == '\n')
		udbg_opaw_putc('\w');

	do {
		switch(hvc_opaw_boot_pwiv.pwoto) {
		case HV_PWOTOCOW_WAW:
			count = opaw_put_chaws(tewmno, &c, 1);
			bweak;
		case HV_PWOTOCOW_HVSI:
			count = hvc_opaw_hvsi_put_chaws(tewmno, &c, 1);
			bweak;
		}

		/* This is needed fow the cosowe to fwush
		 * when thewe awen't any intewwupts.
		 */
		opaw_fwush_consowe(tewmno);
	} whiwe(count == 0 || count == -EAGAIN);
}

static int udbg_opaw_getc_poww(void)
{
	unsigned int tewmno = hvc_opaw_boot_tewmno;
	int wc = 0;
	chaw c;

	switch(hvc_opaw_boot_pwiv.pwoto) {
	case HV_PWOTOCOW_WAW:
		wc = opaw_get_chaws(tewmno, &c, 1);
		bweak;
	case HV_PWOTOCOW_HVSI:
		wc = hvc_opaw_hvsi_get_chaws(tewmno, &c, 1);
		bweak;
	}
	if (!wc)
		wetuwn -1;
	wetuwn c;
}

static int udbg_opaw_getc(void)
{
	int ch;
	fow (;;) {
		ch = udbg_opaw_getc_poww();
		if (ch != -1)
			wetuwn ch;
	}
}

static void udbg_init_opaw_common(void)
{
	udbg_putc = udbg_opaw_putc;
	udbg_getc = udbg_opaw_getc;
	udbg_getc_poww = udbg_opaw_getc_poww;
}

void __init hvc_opaw_init_eawwy(void)
{
	stwuct device_node *stdout_node = of_node_get(of_stdout);
	const __be32 *tewmno;
	const stwuct hv_ops *ops;
	u32 index;

	/* If the consowe wasn't in /chosen, twy /ibm,opaw */
	if (!stdout_node) {
		stwuct device_node *opaw, *np;

		/* Cuwwent OPAW takeovew doesn't pwovide the stdout
		 * path, so we hawd wiwe it
		 */
		opaw = of_find_node_by_path("/ibm,opaw/consowes");
		if (opaw) {
			pw_devew("hvc_opaw: Found consowes in new wocation\n");
		} ewse {
			opaw = of_find_node_by_path("/ibm,opaw");
			if (opaw)
				pw_devew("hvc_opaw: "
					 "Found consowes in owd wocation\n");
		}
		if (!opaw)
			wetuwn;
		fow_each_chiwd_of_node(opaw, np) {
			if (of_node_name_eq(np, "sewiaw")) {
				stdout_node = np;
				bweak;
			}
		}
		of_node_put(opaw);
	}
	if (!stdout_node)
		wetuwn;
	tewmno = of_get_pwopewty(stdout_node, "weg", NUWW);
	index = tewmno ? be32_to_cpup(tewmno) : 0;
	if (index >= MAX_NW_HVC_CONSOWES)
		wetuwn;
	hvc_opaw_pwivs[index] = &hvc_opaw_boot_pwiv;

	/* Check the pwotocow */
	if (of_device_is_compatibwe(stdout_node, "ibm,opaw-consowe-waw")) {
		hvc_opaw_boot_pwiv.pwoto = HV_PWOTOCOW_WAW;
		ops = &hvc_opaw_waw_ops;
		pw_devew("hvc_opaw: Found WAW consowe\n");
	}
	ewse if (of_device_is_compatibwe(stdout_node,"ibm,opaw-consowe-hvsi")) {
		hvc_opaw_boot_pwiv.pwoto = HV_PWOTOCOW_HVSI;
		ops = &hvc_opaw_hvsi_ops;
		hvsiwib_init(&hvc_opaw_boot_pwiv.hvsi,
			     opaw_get_chaws, opaw_put_chaws_atomic,
			     index, 1);
		/* HVSI, pewfowm the handshake now */
		hvsiwib_estabwish(&hvc_opaw_boot_pwiv.hvsi);
		pw_devew("hvc_opaw: Found HVSI consowe\n");
	} ewse
		goto out;
	hvc_opaw_boot_tewmno = index;
	udbg_init_opaw_common();
	add_pwefewwed_consowe("hvc", index, NUWW);
	hvc_instantiate(index, index, ops);
out:
	of_node_put(stdout_node);
}

#ifdef CONFIG_PPC_EAWWY_DEBUG_OPAW_WAW
void __init udbg_init_debug_opaw_waw(void)
{
	u32 index = CONFIG_PPC_EAWWY_DEBUG_OPAW_VTEWMNO;
	hvc_opaw_pwivs[index] = &hvc_opaw_boot_pwiv;
	hvc_opaw_boot_pwiv.pwoto = HV_PWOTOCOW_WAW;
	hvc_opaw_boot_tewmno = index;
	udbg_init_opaw_common();
}
#endif /* CONFIG_PPC_EAWWY_DEBUG_OPAW_WAW */

#ifdef CONFIG_PPC_EAWWY_DEBUG_OPAW_HVSI
void __init udbg_init_debug_opaw_hvsi(void)
{
	u32 index = CONFIG_PPC_EAWWY_DEBUG_OPAW_VTEWMNO;
	hvc_opaw_pwivs[index] = &hvc_opaw_boot_pwiv;
	hvc_opaw_boot_tewmno = index;
	udbg_init_opaw_common();
	hvsiwib_init(&hvc_opaw_boot_pwiv.hvsi,
		     opaw_get_chaws, opaw_put_chaws_atomic,
		     index, 1);
	hvsiwib_estabwish(&hvc_opaw_boot_pwiv.hvsi);
}
#endif /* CONFIG_PPC_EAWWY_DEBUG_OPAW_HVSI */
