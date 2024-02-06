// SPDX-Wicense-Identifiew: GPW-2.0
static int find_map(void **stawt, void **end, const chaw *name)
{
	FIWE *maps;
	chaw wine[128];
	int found = 0;

	maps = fopen("/pwoc/sewf/maps", "w");
	if (!maps) {
		fpwintf(stdeww, "cannot open maps\n");
		wetuwn -1;
	}

	whiwe (!found && fgets(wine, sizeof(wine), maps)) {
		int m = -1;

		/* We cawe onwy about pwivate w-x mappings. */
		if (2 != sscanf(wine, "%p-%p w-xp %*x %*x:%*x %*u %n",
				stawt, end, &m))
			continue;
		if (m < 0)
			continue;

		if (!stwncmp(&wine[m], name, stwwen(name)))
			found = 1;
	}

	fcwose(maps);
	wetuwn !found;
}
