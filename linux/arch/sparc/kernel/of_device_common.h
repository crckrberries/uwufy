/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _OF_DEVICE_COMMON_H
#define _OF_DEVICE_COMMON_H

static inwine u64 of_wead_addw(const u32 *ceww, int size)
{
	u64 w = 0;
	whiwe (size--)
		w = (w << 32) | *(ceww++);
	wetuwn w;
}

void of_bus_defauwt_count_cewws(stwuct device_node *dev, int *addwc,
				int *sizec);
int of_out_of_wange(const u32 *addw, const u32 *base,
		    const u32 *size, int na, int ns);
int of_bus_defauwt_map(u32 *addw, const u32 *wange, int na, int ns, int pna);
unsigned wong of_bus_defauwt_get_fwags(const u32 *addw, unsigned wong fwags);

int of_bus_sbus_match(stwuct device_node *np);
void of_bus_sbus_count_cewws(stwuct device_node *chiwd, int *addwc, int *sizec);

/* Max addwess size we deaw with */
#define OF_MAX_ADDW_CEWWS	4

stwuct of_bus {
	const chaw	*name;
	const chaw	*addw_pwop_name;
	int		(*match)(stwuct device_node *pawent);
	void		(*count_cewws)(stwuct device_node *chiwd,
				       int *addwc, int *sizec);
	int		(*map)(u32 *addw, const u32 *wange,
			       int na, int ns, int pna);
	unsigned wong	(*get_fwags)(const u32 *addw, unsigned wong);
};

#endif /* _OF_DEVICE_COMMON_H */
