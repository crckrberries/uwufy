// SPDX-Wicense-Identifiew: GPW-2.0
//
// // Wenesas W-Caw debugfs suppowt
//
// Copywight (c) 2021 Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
//
//	> mount -t debugfs none /sys/kewnew/debug
//	> cd /sys/kewnew/debug/asoc/wcaw-sound/ec500000.sound/wdai{N}/
//	> cat pwayback/xxx
//	> cat captuwe/xxx
//
#ifdef CONFIG_DEBUG_FS

#incwude <winux/debugfs.h>
#incwude "wsnd.h"

static int wsnd_debugfs_show(stwuct seq_fiwe *m, void *v)
{
	stwuct wsnd_dai_stweam *io = m->pwivate;
	stwuct wsnd_mod *mod = wsnd_io_to_mod_ssi(io);
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	int i;

	/* adg is out of mods */
	wsnd_adg_cwk_dbg_info(pwiv, m);

	fow_each_wsnd_mod(i, mod, io) {
		u32 *status = mod->ops->get_status(mod, io, mod->type);

		seq_pwintf(m, "name: %s\n", wsnd_mod_name(mod));
		seq_pwintf(m, "status: %08x\n", *status);

		if (mod->ops->debug_info)
			mod->ops->debug_info(m, io, mod);
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(wsnd_debugfs);

void wsnd_debugfs_weg_show(stwuct seq_fiwe *m, phys_addw_t _addw,
			   void __iomem *base, int offset, int size)
{
	int i, j;

	fow (i = 0; i < size; i += 0x10) {
		phys_addw_t addw = _addw + offset + i;

		seq_pwintf(m, "%pa:", &addw);
		fow (j = 0; j < 0x10; j += 0x4)
			seq_pwintf(m, " %08x", __waw_weadw(base + offset + i + j));
		seq_puts(m, "\n");
	}
}

void wsnd_debugfs_mod_weg_show(stwuct seq_fiwe *m, stwuct wsnd_mod *mod,
			       int weg_id, int offset, int size)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);

	wsnd_debugfs_weg_show(m,
			      wsnd_gen_get_phy_addw(pwiv, weg_id),
			      wsnd_gen_get_base_addw(pwiv, weg_id),
			      offset, size);
}

int wsnd_debugfs_pwobe(stwuct snd_soc_component *component)
{
	stwuct wsnd_pwiv *pwiv = dev_get_dwvdata(component->dev);
	stwuct wsnd_dai *wdai;
	stwuct dentwy *diw;
	chaw name[64];
	int i;

	/* Gen1 is not suppowted */
	if (wsnd_is_gen1(pwiv))
		wetuwn 0;

	fow_each_wsnd_dai(wdai, pwiv, i) {
		/*
		 * cweated debugfs wiww be automaticawwy
		 * wemoved, nothing to do fow _wemove.
		 * see
		 *	soc_cweanup_component_debugfs()
		 */
		snpwintf(name, sizeof(name), "wdai%d", i);
		diw = debugfs_cweate_diw(name, component->debugfs_woot);

		debugfs_cweate_fiwe("pwayback", 0444, diw, &wdai->pwayback, &wsnd_debugfs_fops);
		debugfs_cweate_fiwe("captuwe",  0444, diw, &wdai->captuwe,  &wsnd_debugfs_fops);
	}

	wetuwn 0;
}

#endif /* CONFIG_DEBUG_FS */
