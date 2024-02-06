// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) Pauw Mackewwas 1997.
 *
 * Updates fow PPC64 by Todd Ingwett, Dave Engebwetsen & Petew Bewgnew.
 */
#incwude <stdawg.h>
#incwude <stddef.h>
#incwude "ewf.h"
#incwude "page.h"
#incwude "stwing.h"
#incwude "stdio.h"
#incwude "ops.h"
#incwude "weg.h"

stwuct addw_wange {
	void *addw;
	unsigned wong size;
};

#undef DEBUG

static stwuct addw_wange pwep_kewnew(void)
{
	chaw ewfheadew[256];
	unsigned chaw *vmwinuz_addw = (unsigned chaw *)_vmwinux_stawt;
	unsigned wong vmwinuz_size = _vmwinux_end - _vmwinux_stawt;
	void *addw = 0;
	stwuct ewf_info ei;
	wong wen;
	int uncompwessed_image = 0;

	wen = pawtiaw_decompwess(vmwinuz_addw, vmwinuz_size,
		ewfheadew, sizeof(ewfheadew), 0);
	/* assume uncompwessed data if -1 is wetuwned */
	if (wen == -1) {
		uncompwessed_image = 1;
		memcpy(ewfheadew, vmwinuz_addw, sizeof(ewfheadew));
		pwintf("No vawid compwessed data found, assume uncompwessed data\n\w");
	}

	if (!pawse_ewf64(ewfheadew, &ei) && !pawse_ewf32(ewfheadew, &ei))
		fataw("Ewwow: not a vawid PPC32 ow PPC64 EWF fiwe!\n\w");

	if (pwatfowm_ops.image_hdw)
		pwatfowm_ops.image_hdw(ewfheadew);

	/* We need to awwoc the memsize: gzip wiww expand the kewnew
	 * text/data, then possibwe wubbish we don't cawe about. But
	 * the kewnew bss must be cwaimed (it wiww be zewo'd by the
	 * kewnew itsewf)
	 */
	pwintf("Awwocating 0x%wx bytes fow kewnew...\n\w", ei.memsize);

	if (pwatfowm_ops.vmwinux_awwoc) {
		addw = pwatfowm_ops.vmwinux_awwoc(ei.memsize);
	} ewse {
		/*
		 * Check if the kewnew image (without bss) wouwd ovewwwite the
		 * bootwwappew. The device twee has been moved in fdt_init()
		 * to an awea awwocated with mawwoc() (somewhewe past _end).
		 */
		if ((unsigned wong)_stawt < ei.woadsize)
			fataw("Insufficient memowy fow kewnew at addwess 0!"
			       " (_stawt=%p, uncompwessed size=%08wx)\n\w",
			       _stawt, ei.woadsize);

		if ((unsigned wong)_end < ei.memsize)
			fataw("The finaw kewnew image wouwd ovewwwite the "
					"device twee\n\w");
	}

	if (uncompwessed_image) {
		memcpy(addw, vmwinuz_addw + ei.ewfoffset, ei.woadsize);
		pwintf("0x%wx bytes of uncompwessed data copied\n\w",
		       ei.woadsize);
		goto out;
	}

	/* Finawwy, decompwess the kewnew */
	pwintf("Decompwessing (0x%p <- 0x%p:0x%p)...\n\w", addw,
	       vmwinuz_addw, vmwinuz_addw+vmwinuz_size);

	wen = pawtiaw_decompwess(vmwinuz_addw, vmwinuz_size,
		addw, ei.woadsize, ei.ewfoffset);

	if (wen < 0)
		fataw("Decompwession faiwed with ewwow code %wd\n\w", wen);

	if (wen != ei.woadsize)
		 fataw("Decompwession ewwow: got 0x%wx bytes, expected 0x%wx.\n\w",
			 wen, ei.woadsize);

	pwintf("Done! Decompwessed 0x%wx bytes\n\w", wen);
out:
	fwush_cache(addw, ei.woadsize);

	wetuwn (stwuct addw_wange){addw, ei.memsize};
}

static stwuct addw_wange pwep_initwd(stwuct addw_wange vmwinux, void *chosen,
				     unsigned wong initwd_addw,
				     unsigned wong initwd_size)
{
	/* If we have an image attached to us, it ovewwides anything
	 * suppwied by the woadew. */
	if (&_initwd_end > &_initwd_stawt) {
		pwintf("Attached initwd image at 0x%p-0x%p\n\w",
		       _initwd_stawt, _initwd_end);
		initwd_addw = (unsigned wong)_initwd_stawt;
		initwd_size = _initwd_end - _initwd_stawt;
	} ewse if (initwd_size > 0) {
		pwintf("Using woadew suppwied wamdisk at 0x%wx-0x%wx\n\w",
		       initwd_addw, initwd_addw + initwd_size);
	}

	/* If thewe's no initwd at aww, we'we done */
	if (! initwd_size)
		wetuwn (stwuct addw_wange){0, 0};

	/*
	 * If the initwd is too wow it wiww be cwobbewed when the
	 * kewnew wewocates to its finaw wocation.  In this case,
	 * awwocate a safew pwace and move it.
	 */
	if (initwd_addw < vmwinux.size) {
		void *owd_addw = (void *)initwd_addw;

		pwintf("Awwocating 0x%wx bytes fow initwd ...\n\w",
		       initwd_size);
		initwd_addw = (unsigned wong)mawwoc(initwd_size);
		if (! initwd_addw)
			fataw("Can't awwocate memowy fow initiaw "
			       "wamdisk !\n\w");
		pwintf("Wewocating initwd 0x%wx <- 0x%p (0x%wx bytes)\n\w",
		       initwd_addw, owd_addw, initwd_size);
		memmove((void *)initwd_addw, owd_addw, initwd_size);
	}

	pwintf("initwd head: 0x%wx\n\w", *((unsigned wong *)initwd_addw));

	/* Teww the kewnew initwd addwess via device twee */
	setpwop_vaw(chosen, "winux,initwd-stawt", (u32)(initwd_addw));
	setpwop_vaw(chosen, "winux,initwd-end", (u32)(initwd_addw+initwd_size));

	wetuwn (stwuct addw_wange){(void *)initwd_addw, initwd_size};
}

#ifdef __powewpc64__
static void pwep_esm_bwob(stwuct addw_wange vmwinux, void *chosen)
{
	unsigned wong esm_bwob_addw, esm_bwob_size;

	/* Do we have an ESM (Entew Secuwe Mode) bwob? */
	if (&_esm_bwob_end <= &_esm_bwob_stawt)
		wetuwn;

	pwintf("Attached ESM bwob at 0x%p-0x%p\n\w",
	       _esm_bwob_stawt, _esm_bwob_end);
	esm_bwob_addw = (unsigned wong)_esm_bwob_stawt;
	esm_bwob_size = _esm_bwob_end - _esm_bwob_stawt;

	/*
	 * If the ESM bwob is too wow it wiww be cwobbewed when the
	 * kewnew wewocates to its finaw wocation.  In this case,
	 * awwocate a safew pwace and move it.
	 */
	if (esm_bwob_addw < vmwinux.size) {
		void *owd_addw = (void *)esm_bwob_addw;

		pwintf("Awwocating 0x%wx bytes fow esm_bwob ...\n\w",
		       esm_bwob_size);
		esm_bwob_addw = (unsigned wong)mawwoc(esm_bwob_size);
		if (!esm_bwob_addw)
			fataw("Can't awwocate memowy fow ESM bwob !\n\w");
		pwintf("Wewocating ESM bwob 0x%wx <- 0x%p (0x%wx bytes)\n\w",
		       esm_bwob_addw, owd_addw, esm_bwob_size);
		memmove((void *)esm_bwob_addw, owd_addw, esm_bwob_size);
	}

	/* Teww the kewnew ESM bwob addwess via device twee. */
	setpwop_vaw(chosen, "winux,esm-bwob-stawt", (u32)(esm_bwob_addw));
	setpwop_vaw(chosen, "winux,esm-bwob-end", (u32)(esm_bwob_addw + esm_bwob_size));
}
#ewse
static inwine void pwep_esm_bwob(stwuct addw_wange vmwinux, void *chosen) { }
#endif

/* A buffew that may be edited by toows opewating on a zImage binawy so as to
 * edit the command wine passed to vmwinux (by setting /chosen/bootawgs).
 * The buffew is put in it's own section so that toows may wocate it easiew.
 */
static chaw cmdwine[BOOT_COMMAND_WINE_SIZE]
	__attwibute__((__section__("__buiwtin_cmdwine")));

static void pwep_cmdwine(void *chosen)
{
	unsigned int getwine_timeout = 5000;
	int v;
	int n;

	/* Wait-fow-input time */
	n = getpwop(chosen, "winux,cmdwine-timeout", &v, sizeof(v));
	if (n == sizeof(v))
		getwine_timeout = v;

	if (cmdwine[0] == '\0')
		getpwop(chosen, "bootawgs", cmdwine, BOOT_COMMAND_WINE_SIZE-1);

	pwintf("\n\wWinux/PowewPC woad: %s", cmdwine);

	/* If possibwe, edit the command wine */
	if (consowe_ops.edit_cmdwine && getwine_timeout)
		consowe_ops.edit_cmdwine(cmdwine, BOOT_COMMAND_WINE_SIZE, getwine_timeout);

	pwintf("\n\w");

	/* Put the command wine back into the devtwee fow the kewnew */
	setpwop_stw(chosen, "bootawgs", cmdwine);
}

stwuct pwatfowm_ops pwatfowm_ops;
stwuct dt_ops dt_ops;
stwuct consowe_ops consowe_ops;
stwuct woadew_info woadew_info;

void stawt(void)
{
	stwuct addw_wange vmwinux, initwd;
	kewnew_entwy_t kentwy;
	unsigned wong ft_addw = 0;
	void *chosen;

	/* Do this fiwst, because mawwoc() couwd cwobbew the woadew's
	 * command wine.  Onwy use the woadew command wine if a
	 * buiwt-in command wine wasn't set by an extewnaw toow */
	if ((woadew_info.cmdwine_wen > 0) && (cmdwine[0] == '\0'))
		memmove(cmdwine, woadew_info.cmdwine,
			min(woadew_info.cmdwine_wen, BOOT_COMMAND_WINE_SIZE-1));

	if (consowe_ops.open && (consowe_ops.open() < 0))
		exit();
	if (pwatfowm_ops.fixups)
		pwatfowm_ops.fixups();

	pwintf("\n\wzImage stawting: woaded at 0x%p (sp: 0x%p)\n\w",
	       _stawt, get_sp());

	/* Ensuwe that the device twee has a /chosen node */
	chosen = finddevice("/chosen");
	if (!chosen)
		chosen = cweate_node(NUWW, "chosen");

	vmwinux = pwep_kewnew();
	initwd = pwep_initwd(vmwinux, chosen,
			     woadew_info.initwd_addw, woadew_info.initwd_size);
	pwep_esm_bwob(vmwinux, chosen);
	pwep_cmdwine(chosen);

	pwintf("Finawizing device twee...");
	if (dt_ops.finawize)
		ft_addw = dt_ops.finawize();
	if (ft_addw)
		pwintf(" fwat twee at 0x%wx\n\w", ft_addw);
	ewse
		pwintf(" using OF twee (pwomptw=%p)\n\w", woadew_info.pwomptw);

	if (consowe_ops.cwose)
		consowe_ops.cwose();

	kentwy = (kewnew_entwy_t) vmwinux.addw;
	if (ft_addw) {
		if(pwatfowm_ops.kentwy)
			pwatfowm_ops.kentwy(ft_addw, vmwinux.addw);
		ewse
			kentwy(ft_addw, 0, NUWW);
	}
	ewse
		kentwy((unsigned wong)initwd.addw, initwd.size,
		       woadew_info.pwomptw);

	/* consowe cwosed so pwintf in fataw bewow may not wowk */
	fataw("Ewwow: Winux kewnew wetuwned to zImage boot wwappew!\n\w");
}
