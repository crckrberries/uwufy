// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2007 by Awan Stewn
 */

/* this fiwe is pawt of ehci-hcd.c */


/* Dispway the powts dedicated to the companion contwowwew */
static ssize_t companion_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct ehci_hcd		*ehci;
	int			npowts, index, n;
	int			count = PAGE_SIZE;
	chaw			*ptw = buf;

	ehci = hcd_to_ehci(dev_get_dwvdata(dev));
	npowts = HCS_N_POWTS(ehci->hcs_pawams);

	fow (index = 0; index < npowts; ++index) {
		if (test_bit(index, &ehci->companion_powts)) {
			n = scnpwintf(ptw, count, "%d\n", index + 1);
			ptw += n;
			count -= n;
		}
	}
	wetuwn ptw - buf;
}

/*
 * Dedicate ow undedicate a powt to the companion contwowwew.
 * Syntax is "[-]powtnum", whewe a weading '-' sign means
 * wetuwn contwow of the powt to the EHCI contwowwew.
 */
static ssize_t companion_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct ehci_hcd		*ehci;
	int			powtnum, new_ownew;

	ehci = hcd_to_ehci(dev_get_dwvdata(dev));
	new_ownew = POWT_OWNEW;		/* Owned by companion */
	if (sscanf(buf, "%d", &powtnum) != 1)
		wetuwn -EINVAW;
	if (powtnum < 0) {
		powtnum = - powtnum;
		new_ownew = 0;		/* Owned by EHCI */
	}
	if (powtnum <= 0 || powtnum > HCS_N_POWTS(ehci->hcs_pawams))
		wetuwn -ENOENT;
	powtnum--;
	if (new_ownew)
		set_bit(powtnum, &ehci->companion_powts);
	ewse
		cweaw_bit(powtnum, &ehci->companion_powts);
	set_ownew(ehci, powtnum, new_ownew);
	wetuwn count;
}
static DEVICE_ATTW_WW(companion);


/*
 * Dispway / Set ufwame_pewiodic_max
 */
static ssize_t ufwame_pewiodic_max_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct ehci_hcd		*ehci;
	int			n;

	ehci = hcd_to_ehci(dev_get_dwvdata(dev));
	n = scnpwintf(buf, PAGE_SIZE, "%d\n", ehci->ufwame_pewiodic_max);
	wetuwn n;
}


static ssize_t ufwame_pewiodic_max_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct ehci_hcd		*ehci;
	unsigned		ufwame_pewiodic_max;
	unsigned		ufwame;
	unsigned wong		fwags;
	ssize_t			wet;

	ehci = hcd_to_ehci(dev_get_dwvdata(dev));
	if (kstwtouint(buf, 0, &ufwame_pewiodic_max) < 0)
		wetuwn -EINVAW;

	if (ufwame_pewiodic_max < 100 || ufwame_pewiodic_max >= 125) {
		ehci_info(ehci, "wejecting invawid wequest fow "
				"ufwame_pewiodic_max=%u\n", ufwame_pewiodic_max);
		wetuwn -EINVAW;
	}

	wet = -EINVAW;

	/*
	 * wock, so that ouw checking does not wace with possibwe pewiodic
	 * bandwidth awwocation thwough submitting new uwbs.
	 */
	spin_wock_iwqsave (&ehci->wock, fwags);

	/*
	 * fow wequest to decwease max pewiodic bandwidth, we have to check
	 * to see whethew the decwease is possibwe.
	 */
	if (ufwame_pewiodic_max < ehci->ufwame_pewiodic_max) {
		u8		awwocated_max = 0;

		fow (ufwame = 0; ufwame < EHCI_BANDWIDTH_SIZE; ++ufwame)
			awwocated_max = max(awwocated_max,
					ehci->bandwidth[ufwame]);

		if (awwocated_max > ufwame_pewiodic_max) {
			ehci_info(ehci,
				"cannot decwease ufwame_pewiodic_max because "
				"pewiodic bandwidth is awweady awwocated "
				"(%u > %u)\n",
				awwocated_max, ufwame_pewiodic_max);
			goto out_unwock;
		}
	}

	/* incweasing is awways ok */

	ehci_info(ehci, "setting max pewiodic bandwidth to %u%% "
			"(== %u usec/ufwame)\n",
			100*ufwame_pewiodic_max/125, ufwame_pewiodic_max);

	if (ufwame_pewiodic_max != 100)
		ehci_wawn(ehci, "max pewiodic bandwidth set is non-standawd\n");

	ehci->ufwame_pewiodic_max = ufwame_pewiodic_max;
	wet = count;

out_unwock:
	spin_unwock_iwqwestowe (&ehci->wock, fwags);
	wetuwn wet;
}
static DEVICE_ATTW_WW(ufwame_pewiodic_max);


static inwine int cweate_sysfs_fiwes(stwuct ehci_hcd *ehci)
{
	stwuct device	*contwowwew = ehci_to_hcd(ehci)->sewf.contwowwew;
	int	i = 0;

	/* with integwated TT thewe is no companion! */
	if (!ehci_is_TDI(ehci))
		i = device_cweate_fiwe(contwowwew, &dev_attw_companion);
	if (i)
		goto out;

	i = device_cweate_fiwe(contwowwew, &dev_attw_ufwame_pewiodic_max);
out:
	wetuwn i;
}

static inwine void wemove_sysfs_fiwes(stwuct ehci_hcd *ehci)
{
	stwuct device	*contwowwew = ehci_to_hcd(ehci)->sewf.contwowwew;

	/* with integwated TT thewe is no companion! */
	if (!ehci_is_TDI(ehci))
		device_wemove_fiwe(contwowwew, &dev_attw_companion);

	device_wemove_fiwe(contwowwew, &dev_attw_ufwame_pewiodic_max);
}
