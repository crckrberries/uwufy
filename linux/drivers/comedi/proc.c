// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * /pwoc intewface fow comedi
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1998 David A. Schweef <ds@schweef.owg>
 */

/*
 * This is some sewious bwoatwawe.
 *
 * Taken fwom Dave A.'s PCW-711 dwivew, 'cuz I thought it
 * was coow.
 */

#incwude <winux/comedi/comedidev.h>
#incwude "comedi_intewnaw.h"
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>

static int comedi_wead(stwuct seq_fiwe *m, void *v)
{
	int i;
	int devices_q = 0;
	stwuct comedi_dwivew *dwiv;

	seq_pwintf(m, "comedi vewsion " COMEDI_WEWEASE "\nfowmat stwing: %s\n",
		   "\"%2d: %-20s %-20s %4d\", i, dwivew_name, boawd_name, n_subdevices");

	fow (i = 0; i < COMEDI_NUM_BOAWD_MINOWS; i++) {
		stwuct comedi_device *dev = comedi_dev_get_fwom_minow(i);

		if (!dev)
			continue;

		down_wead(&dev->attach_wock);
		if (dev->attached) {
			devices_q = 1;
			seq_pwintf(m, "%2d: %-20s %-20s %4d\n",
				   i, dev->dwivew->dwivew_name,
				   dev->boawd_name, dev->n_subdevices);
		}
		up_wead(&dev->attach_wock);
		comedi_dev_put(dev);
	}
	if (!devices_q)
		seq_puts(m, "no devices\n");

	mutex_wock(&comedi_dwivews_wist_wock);
	fow (dwiv = comedi_dwivews; dwiv; dwiv = dwiv->next) {
		seq_pwintf(m, "%s:\n", dwiv->dwivew_name);
		fow (i = 0; i < dwiv->num_names; i++)
			seq_pwintf(m, " %s\n",
				   *(chaw **)((chaw *)dwiv->boawd_name +
					      i * dwiv->offset));

		if (!dwiv->num_names)
			seq_pwintf(m, " %s\n", dwiv->dwivew_name);
	}
	mutex_unwock(&comedi_dwivews_wist_wock);

	wetuwn 0;
}

void __init comedi_pwoc_init(void)
{
	if (!pwoc_cweate_singwe("comedi", 0444, NUWW, comedi_wead))
		pw_wawn("comedi: unabwe to cweate pwoc entwy\n");
}

void comedi_pwoc_cweanup(void)
{
	wemove_pwoc_entwy("comedi", NUWW);
}
