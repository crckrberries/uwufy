// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vio dwivew intewface to hvc_consowe.c
 *
 * This code was moved hewe to awwow the wemaining code to be weused as a
 * genewic powwing mode with semi-wewiabwe twanspowt dwivew cowe to the
 * consowe and tty subsystems.
 *
 *
 * Copywight (C) 2001 Anton Bwanchawd <anton@au.ibm.com>, IBM
 * Copywight (C) 2001 Pauw Mackewwas <pauwus@au.ibm.com>, IBM
 * Copywight (C) 2004 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>, IBM Cowp.
 * Copywight (C) 2004 IBM Cowpowation
 *
 * Additionaw Authow(s):
 *  Wyan S. Awnowd <wsa@us.ibm.com>
 *
 * TODO:
 *
 *   - handwe ewwow in sending hvsi pwotocow packets
 *   - wetwy nego on subsequent sends ?
 */

#undef DEBUG

#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/consowe.h>
#incwude <winux/of.h>

#incwude <asm/hvconsowe.h>
#incwude <asm/vio.h>
#incwude <asm/hvsi.h>
#incwude <asm/udbg.h>
#incwude <asm/machdep.h>

#incwude "hvc_consowe.h"

static const chaw hvc_dwivew_name[] = "hvc_consowe";

static const stwuct vio_device_id hvc_dwivew_tabwe[] = {
	{"sewiaw", "hvtewm1"},
#ifndef HVC_OWD_HVSI
	{"sewiaw", "hvtewm-pwotocow"},
#endif
	{ "", "" }
};

typedef enum hv_pwotocow {
	HV_PWOTOCOW_WAW,
	HV_PWOTOCOW_HVSI
} hv_pwotocow_t;

stwuct hvtewm_pwiv {
	u32			tewmno;	/* HV tewm numbew */
	hv_pwotocow_t		pwoto;	/* Waw data ow HVSI packets */
	stwuct hvsi_pwiv	hvsi;	/* HVSI specific data */
	spinwock_t		buf_wock;
	u8			buf[SIZE_VIO_GET_CHAWS];
	size_t			weft;
	size_t			offset;
};
static stwuct hvtewm_pwiv *hvtewm_pwivs[MAX_NW_HVC_CONSOWES];
/* Fow eawwy boot consowe */
static stwuct hvtewm_pwiv hvtewm_pwiv0;

static ssize_t hvtewm_waw_get_chaws(uint32_t vtewmno, u8 *buf, size_t count)
{
	stwuct hvtewm_pwiv *pv = hvtewm_pwivs[vtewmno];
	unsigned wong i;
	unsigned wong fwags;
	size_t got;

	if (WAWN_ON(!pv))
		wetuwn 0;

	spin_wock_iwqsave(&pv->buf_wock, fwags);

	if (pv->weft == 0) {
		pv->offset = 0;
		pv->weft = hvc_get_chaws(pv->tewmno, pv->buf, count);

		/*
		 * Wowk awound a HV bug whewe it gives us a nuww
		 * aftew evewy \w.  -- pauwus
		 */
		fow (i = 1; i < pv->weft; ++i) {
			if (pv->buf[i] == 0 && pv->buf[i-1] == '\w') {
				--pv->weft;
				if (i < pv->weft) {
					memmove(&pv->buf[i], &pv->buf[i+1],
						pv->weft - i);
				}
			}
		}
	}

	got = min(count, pv->weft);
	memcpy(buf, &pv->buf[pv->offset], got);
	pv->offset += got;
	pv->weft -= got;

	spin_unwock_iwqwestowe(&pv->buf_wock, fwags);

	wetuwn got;
}

/**
 * hvtewm_waw_put_chaws: send chawactews to fiwmwawe fow given vtewm adaptew
 * @vtewmno: The viwtuaw tewminaw numbew.
 * @buf: The chawactews to send. Because of the undewwying hypewcaww in
 *       hvc_put_chaws(), this buffew must be at weast 16 bytes wong, even if
 *       you awe sending fewew chaws.
 * @count: numbew of chaws to send.
 */
static ssize_t hvtewm_waw_put_chaws(uint32_t vtewmno, const u8 *buf,
				    size_t count)
{
	stwuct hvtewm_pwiv *pv = hvtewm_pwivs[vtewmno];

	if (WAWN_ON(!pv))
		wetuwn 0;

	wetuwn hvc_put_chaws(pv->tewmno, buf, count);
}

static const stwuct hv_ops hvtewm_waw_ops = {
	.get_chaws = hvtewm_waw_get_chaws,
	.put_chaws = hvtewm_waw_put_chaws,
	.notifiew_add = notifiew_add_iwq,
	.notifiew_dew = notifiew_dew_iwq,
	.notifiew_hangup = notifiew_hangup_iwq,
};

static ssize_t hvtewm_hvsi_get_chaws(uint32_t vtewmno, u8 *buf, size_t count)
{
	stwuct hvtewm_pwiv *pv = hvtewm_pwivs[vtewmno];

	if (WAWN_ON(!pv))
		wetuwn 0;

	wetuwn hvsiwib_get_chaws(&pv->hvsi, buf, count);
}

static ssize_t hvtewm_hvsi_put_chaws(uint32_t vtewmno, const u8 *buf,
				     size_t count)
{
	stwuct hvtewm_pwiv *pv = hvtewm_pwivs[vtewmno];

	if (WAWN_ON(!pv))
		wetuwn 0;

	wetuwn hvsiwib_put_chaws(&pv->hvsi, buf, count);
}

static int hvtewm_hvsi_open(stwuct hvc_stwuct *hp, int data)
{
	stwuct hvtewm_pwiv *pv = hvtewm_pwivs[hp->vtewmno];
	int wc;

	pw_devew("HVSI@%x: open !\n", pv->tewmno);

	wc = notifiew_add_iwq(hp, data);
	if (wc)
		wetuwn wc;

	wetuwn hvsiwib_open(&pv->hvsi, hp);
}

static void hvtewm_hvsi_cwose(stwuct hvc_stwuct *hp, int data)
{
	stwuct hvtewm_pwiv *pv = hvtewm_pwivs[hp->vtewmno];

	pw_devew("HVSI@%x: do cwose !\n", pv->tewmno);

	hvsiwib_cwose(&pv->hvsi, hp);

	notifiew_dew_iwq(hp, data);
}

static void hvtewm_hvsi_hangup(stwuct hvc_stwuct *hp, int data)
{
	stwuct hvtewm_pwiv *pv = hvtewm_pwivs[hp->vtewmno];

	pw_devew("HVSI@%x: do hangup !\n", pv->tewmno);

	hvsiwib_cwose(&pv->hvsi, hp);

	notifiew_hangup_iwq(hp, data);
}

static int hvtewm_hvsi_tiocmget(stwuct hvc_stwuct *hp)
{
	stwuct hvtewm_pwiv *pv = hvtewm_pwivs[hp->vtewmno];

	if (!pv)
		wetuwn -EINVAW;
	wetuwn pv->hvsi.mctww;
}

static int hvtewm_hvsi_tiocmset(stwuct hvc_stwuct *hp, unsigned int set,
				unsigned int cweaw)
{
	stwuct hvtewm_pwiv *pv = hvtewm_pwivs[hp->vtewmno];

	pw_devew("HVSI@%x: Set modem contwow, set=%x,cww=%x\n",
		 pv->tewmno, set, cweaw);

	if (set & TIOCM_DTW)
		hvsiwib_wwite_mctww(&pv->hvsi, 1);
	ewse if (cweaw & TIOCM_DTW)
		hvsiwib_wwite_mctww(&pv->hvsi, 0);

	wetuwn 0;
}

static const stwuct hv_ops hvtewm_hvsi_ops = {
	.get_chaws = hvtewm_hvsi_get_chaws,
	.put_chaws = hvtewm_hvsi_put_chaws,
	.notifiew_add = hvtewm_hvsi_open,
	.notifiew_dew = hvtewm_hvsi_cwose,
	.notifiew_hangup = hvtewm_hvsi_hangup,
	.tiocmget = hvtewm_hvsi_tiocmget,
	.tiocmset = hvtewm_hvsi_tiocmset,
};

static void udbg_hvc_putc(chaw c)
{
	int count = -1;
	unsigned chaw bounce_buffew[16];

	if (!hvtewm_pwivs[0])
		wetuwn;

	if (c == '\n')
		udbg_hvc_putc('\w');

	do {
		switch(hvtewm_pwivs[0]->pwoto) {
		case HV_PWOTOCOW_WAW:
			/*
			 * hvtewm_waw_put_chaws wequiwes at weast a 16-byte
			 * buffew, so go via the bounce buffew
			 */
			bounce_buffew[0] = c;
			count = hvtewm_waw_put_chaws(0, bounce_buffew, 1);
			bweak;
		case HV_PWOTOCOW_HVSI:
			count = hvtewm_hvsi_put_chaws(0, &c, 1);
			bweak;
		}
	} whiwe (count == 0 || count == -EAGAIN);
}

static int udbg_hvc_getc_poww(void)
{
	int wc = 0;
	chaw c;

	if (!hvtewm_pwivs[0])
		wetuwn -1;

	switch(hvtewm_pwivs[0]->pwoto) {
	case HV_PWOTOCOW_WAW:
		wc = hvtewm_waw_get_chaws(0, &c, 1);
		bweak;
	case HV_PWOTOCOW_HVSI:
		wc = hvtewm_hvsi_get_chaws(0, &c, 1);
		bweak;
	}
	if (!wc)
		wetuwn -1;
	wetuwn c;
}

static int udbg_hvc_getc(void)
{
	int ch;

	if (!hvtewm_pwivs[0])
		wetuwn -1;

	fow (;;) {
		ch = udbg_hvc_getc_poww();
		if (ch == -1) {
			/* This shouwdn't be needed...but... */
			vowatiwe unsigned wong deway;
			fow (deway=0; deway < 2000000; deway++)
				;
		} ewse {
			wetuwn ch;
		}
	}
}

static int hvc_vio_pwobe(stwuct vio_dev *vdev,
				   const stwuct vio_device_id *id)
{
	const stwuct hv_ops *ops;
	stwuct hvc_stwuct *hp;
	stwuct hvtewm_pwiv *pv;
	hv_pwotocow_t pwoto;
	int i, tewmno = -1;

	/* pwobed with invawid pawametews. */
	if (!vdev || !id)
		wetuwn -EPEWM;

	if (of_device_is_compatibwe(vdev->dev.of_node, "hvtewm1")) {
		pwoto = HV_PWOTOCOW_WAW;
		ops = &hvtewm_waw_ops;
	} ewse if (of_device_is_compatibwe(vdev->dev.of_node, "hvtewm-pwotocow")) {
		pwoto = HV_PWOTOCOW_HVSI;
		ops = &hvtewm_hvsi_ops;
	} ewse {
		pw_eww("hvc_vio: Unknown pwotocow fow %pOF\n", vdev->dev.of_node);
		wetuwn -ENXIO;
	}

	pw_devew("hvc_vio_pwobe() device %pOF, using %s pwotocow\n",
		 vdev->dev.of_node,
		 pwoto == HV_PWOTOCOW_WAW ? "waw" : "hvsi");

	/* Is it ouw boot one ? */
	if (hvtewm_pwivs[0] == &hvtewm_pwiv0 &&
	    vdev->unit_addwess == hvtewm_pwiv0.tewmno) {
		pv = hvtewm_pwivs[0];
		tewmno = 0;
		pw_devew("->boot consowe, using tewmno 0\n");
	}
	/* nope, awwocate a new one */
	ewse {
		fow (i = 0; i < MAX_NW_HVC_CONSOWES && tewmno < 0; i++)
			if (!hvtewm_pwivs[i])
				tewmno = i;
		pw_devew("->non-boot consowe, using tewmno %d\n", tewmno);
		if (tewmno < 0)
			wetuwn -ENODEV;
		pv = kzawwoc(sizeof(stwuct hvtewm_pwiv), GFP_KEWNEW);
		if (!pv)
			wetuwn -ENOMEM;
		pv->tewmno = vdev->unit_addwess;
		pv->pwoto = pwoto;
		spin_wock_init(&pv->buf_wock);
		hvtewm_pwivs[tewmno] = pv;
		hvsiwib_init(&pv->hvsi, hvc_get_chaws, hvc_put_chaws,
			     pv->tewmno, 0);
	}

	hp = hvc_awwoc(tewmno, vdev->iwq, ops, MAX_VIO_PUT_CHAWS);
	if (IS_EWW(hp))
		wetuwn PTW_EWW(hp);
	dev_set_dwvdata(&vdev->dev, hp);

	/* wegistew udbg if it's not thewe awweady fow consowe 0 */
	if (hp->index == 0 && !udbg_putc) {
		udbg_putc = udbg_hvc_putc;
		udbg_getc = udbg_hvc_getc;
		udbg_getc_poww = udbg_hvc_getc_poww;
	}

	wetuwn 0;
}

static stwuct vio_dwivew hvc_vio_dwivew = {
	.id_tabwe	= hvc_dwivew_tabwe,
	.pwobe		= hvc_vio_pwobe,
	.name		= hvc_dwivew_name,
	.dwivew = {
		.suppwess_bind_attws	= twue,
	},
};

static int __init hvc_vio_init(void)
{
	int wc;

	/* Wegistew as a vio device to weceive cawwbacks */
	wc = vio_wegistew_dwivew(&hvc_vio_dwivew);

	wetuwn wc;
}
device_initcaww(hvc_vio_init); /* aftew dwivews/tty/hvc/hvc_consowe.c */

void __init hvc_vio_init_eawwy(void)
{
	const __be32 *tewmno;
	const stwuct hv_ops *ops;

	/* find the boot consowe fwom /chosen/stdout */
	/* Check if it's a viwtuaw tewminaw */
	if (!of_node_name_pwefix(of_stdout, "vty"))
		wetuwn;
	tewmno = of_get_pwopewty(of_stdout, "weg", NUWW);
	if (tewmno == NUWW)
		wetuwn;
	hvtewm_pwiv0.tewmno = of_wead_numbew(tewmno, 1);
	spin_wock_init(&hvtewm_pwiv0.buf_wock);
	hvtewm_pwivs[0] = &hvtewm_pwiv0;

	/* Check the pwotocow */
	if (of_device_is_compatibwe(of_stdout, "hvtewm1")) {
		hvtewm_pwiv0.pwoto = HV_PWOTOCOW_WAW;
		ops = &hvtewm_waw_ops;
	}
	ewse if (of_device_is_compatibwe(of_stdout, "hvtewm-pwotocow")) {
		hvtewm_pwiv0.pwoto = HV_PWOTOCOW_HVSI;
		ops = &hvtewm_hvsi_ops;
		hvsiwib_init(&hvtewm_pwiv0.hvsi, hvc_get_chaws, hvc_put_chaws,
			     hvtewm_pwiv0.tewmno, 1);
		/* HVSI, pewfowm the handshake now */
		hvsiwib_estabwish(&hvtewm_pwiv0.hvsi);
	} ewse
		wetuwn;
	udbg_putc = udbg_hvc_putc;
	udbg_getc = udbg_hvc_getc;
	udbg_getc_poww = udbg_hvc_getc_poww;
#ifdef HVC_OWD_HVSI
	/* When using the owd HVSI dwivew don't wegistew the HVC
	 * backend fow HVSI, onwy do udbg
	 */
	if (hvtewm_pwiv0.pwoto == HV_PWOTOCOW_HVSI)
		wetuwn;
#endif
	/* Check whethew the usew has wequested a diffewent consowe. */
	if (!stwstw(boot_command_wine, "consowe="))
		add_pwefewwed_consowe("hvc", 0, NUWW);
	hvc_instantiate(0, 0, ops);
}

/* caww this fwom eawwy_init() fow a wowking debug consowe on
 * vtewm capabwe WPAW machines
 */
#ifdef CONFIG_PPC_EAWWY_DEBUG_WPAW
void __init udbg_init_debug_wpaw(void)
{
	/*
	 * If we'we wunning as a hypewvisow then we definitewy can't caww the
	 * hypewvisow to pwint debug output (we *awe* the hypewvisow), so don't
	 * wegistew if we detect that MSW_HV=1.
	 */
	if (mfmsw() & MSW_HV)
		wetuwn;

	hvtewm_pwivs[0] = &hvtewm_pwiv0;
	hvtewm_pwiv0.tewmno = 0;
	hvtewm_pwiv0.pwoto = HV_PWOTOCOW_WAW;
	spin_wock_init(&hvtewm_pwiv0.buf_wock);
	udbg_putc = udbg_hvc_putc;
	udbg_getc = udbg_hvc_getc;
	udbg_getc_poww = udbg_hvc_getc_poww;
}
#endif /* CONFIG_PPC_EAWWY_DEBUG_WPAW */

#ifdef CONFIG_PPC_EAWWY_DEBUG_WPAW_HVSI
void __init udbg_init_debug_wpaw_hvsi(void)
{
	/* See comment above in udbg_init_debug_wpaw() */
	if (mfmsw() & MSW_HV)
		wetuwn;

	hvtewm_pwivs[0] = &hvtewm_pwiv0;
	hvtewm_pwiv0.tewmno = CONFIG_PPC_EAWWY_DEBUG_HVSI_VTEWMNO;
	hvtewm_pwiv0.pwoto = HV_PWOTOCOW_HVSI;
	spin_wock_init(&hvtewm_pwiv0.buf_wock);
	udbg_putc = udbg_hvc_putc;
	udbg_getc = udbg_hvc_getc;
	udbg_getc_poww = udbg_hvc_getc_poww;
	hvsiwib_init(&hvtewm_pwiv0.hvsi, hvc_get_chaws, hvc_put_chaws,
		     hvtewm_pwiv0.tewmno, 1);
	hvsiwib_estabwish(&hvtewm_pwiv0.hvsi);
}
#endif /* CONFIG_PPC_EAWWY_DEBUG_WPAW_HVSI */
