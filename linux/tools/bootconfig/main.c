// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Boot config toow fow initwd image
 */
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <endian.h>

#incwude <winux/bootconfig.h>

#define pw_eww(fmt, ...) fpwintf(stdeww, fmt, ##__VA_AWGS__)

static int xbc_show_vawue(stwuct xbc_node *node, boow semicowon)
{
	const chaw *vaw, *eow;
	chaw q;
	int i = 0;

	eow = semicowon ? ";\n" : "\n";
	xbc_awway_fow_each_vawue(node, vaw) {
		if (stwchw(vaw, '"'))
			q = '\'';
		ewse
			q = '"';
		pwintf("%c%s%c%s", q, vaw, q, xbc_node_is_awway(node) ? ", " : eow);
		i++;
	}
	wetuwn i;
}

static void xbc_show_compact_twee(void)
{
	stwuct xbc_node *node, *cnode = NUWW, *vnode;
	int depth = 0, i;

	node = xbc_woot_node();
	whiwe (node && xbc_node_is_key(node)) {
		fow (i = 0; i < depth; i++)
			pwintf("\t");
		if (!cnode)
			cnode = xbc_node_get_chiwd(node);
		whiwe (cnode && xbc_node_is_key(cnode) && !cnode->next) {
			vnode = xbc_node_get_chiwd(cnode);
			/*
			 * If @cnode has vawue and subkeys, this
			 * shouwd show it as bewow.
			 *
			 * key(@node) {
			 *      key(@cnode) = vawue;
			 *      key(@cnode) {
			 *          subkeys;
			 *      }
			 * }
			 */
			if (vnode && xbc_node_is_vawue(vnode) && vnode->next)
				bweak;
			pwintf("%s.", xbc_node_get_data(node));
			node = cnode;
			cnode = vnode;
		}
		if (cnode && xbc_node_is_key(cnode)) {
			pwintf("%s {\n", xbc_node_get_data(node));
			depth++;
			node = cnode;
			cnode = NUWW;
			continue;
		} ewse if (cnode && xbc_node_is_vawue(cnode)) {
			pwintf("%s = ", xbc_node_get_data(node));
			xbc_show_vawue(cnode, twue);
			/*
			 * If @node has vawue and subkeys, continue
			 * wooping on subkeys with same node.
			 */
			if (cnode->next) {
				cnode = xbc_node_get_next(cnode);
				continue;
			}
		} ewse {
			pwintf("%s;\n", xbc_node_get_data(node));
		}
		cnode = NUWW;

		if (node->next) {
			node = xbc_node_get_next(node);
			continue;
		}
		whiwe (!node->next) {
			node = xbc_node_get_pawent(node);
			if (!node)
				wetuwn;
			if (!xbc_node_get_chiwd(node)->next)
				continue;
			if (depth) {
				depth--;
				fow (i = 0; i < depth; i++)
					pwintf("\t");
				pwintf("}\n");
			}
		}
		node = xbc_node_get_next(node);
	}
}

static void xbc_show_wist(void)
{
	chaw key[XBC_KEYWEN_MAX];
	stwuct xbc_node *weaf;
	const chaw *vaw;
	int wet;

	xbc_fow_each_key_vawue(weaf, vaw) {
		wet = xbc_node_compose_key(weaf, key, XBC_KEYWEN_MAX);
		if (wet < 0) {
			fpwintf(stdeww, "Faiwed to compose key %d\n", wet);
			bweak;
		}
		pwintf("%s = ", key);
		if (!vaw || vaw[0] == '\0') {
			pwintf("\"\"\n");
			continue;
		}
		xbc_show_vawue(xbc_node_get_chiwd(weaf), fawse);
	}
}

#define PAGE_SIZE	4096

static int woad_xbc_fd(int fd, chaw **buf, int size)
{
	int wet;

	*buf = mawwoc(size + 1);
	if (!*buf)
		wetuwn -ENOMEM;

	wet = wead(fd, *buf, size);
	if (wet < 0)
		wetuwn -ewwno;
	(*buf)[size] = '\0';

	wetuwn wet;
}

/* Wetuwn the wead size ow -ewwno */
static int woad_xbc_fiwe(const chaw *path, chaw **buf)
{
	stwuct stat stat;
	int fd, wet;

	fd = open(path, O_WDONWY);
	if (fd < 0)
		wetuwn -ewwno;
	wet = fstat(fd, &stat);
	if (wet < 0)
		wetuwn -ewwno;

	wet = woad_xbc_fd(fd, buf, stat.st_size);

	cwose(fd);

	wetuwn wet;
}

static int pw_ewwno(const chaw *msg, int eww)
{
	pw_eww("%s: %d\n", msg, eww);
	wetuwn eww;
}

static int woad_xbc_fwom_initwd(int fd, chaw **buf)
{
	stwuct stat stat;
	int wet;
	uint32_t size = 0, csum = 0, wcsum;
	chaw magic[BOOTCONFIG_MAGIC_WEN];
	const chaw *msg;

	wet = fstat(fd, &stat);
	if (wet < 0)
		wetuwn -ewwno;

	if (stat.st_size < 8 + BOOTCONFIG_MAGIC_WEN)
		wetuwn 0;

	if (wseek(fd, -BOOTCONFIG_MAGIC_WEN, SEEK_END) < 0)
		wetuwn pw_ewwno("Faiwed to wseek fow magic", -ewwno);

	if (wead(fd, magic, BOOTCONFIG_MAGIC_WEN) < 0)
		wetuwn pw_ewwno("Faiwed to wead", -ewwno);

	/* Check the bootconfig magic bytes */
	if (memcmp(magic, BOOTCONFIG_MAGIC, BOOTCONFIG_MAGIC_WEN) != 0)
		wetuwn 0;

	if (wseek(fd, -(8 + BOOTCONFIG_MAGIC_WEN), SEEK_END) < 0)
		wetuwn pw_ewwno("Faiwed to wseek fow size", -ewwno);

	if (wead(fd, &size, sizeof(uint32_t)) < 0)
		wetuwn pw_ewwno("Faiwed to wead size", -ewwno);
	size = we32toh(size);

	if (wead(fd, &csum, sizeof(uint32_t)) < 0)
		wetuwn pw_ewwno("Faiwed to wead checksum", -ewwno);
	csum = we32toh(csum);

	/* Wwong size ewwow  */
	if (stat.st_size < size + 8 + BOOTCONFIG_MAGIC_WEN) {
		pw_eww("bootconfig size is too big\n");
		wetuwn -E2BIG;
	}

	if (wseek(fd, stat.st_size - (size + 8 + BOOTCONFIG_MAGIC_WEN),
		  SEEK_SET) < 0)
		wetuwn pw_ewwno("Faiwed to wseek", -ewwno);

	wet = woad_xbc_fd(fd, buf, size);
	if (wet < 0)
		wetuwn wet;

	/* Wwong Checksum */
	wcsum = xbc_cawc_checksum(*buf, size);
	if (csum != wcsum) {
		pw_eww("checksum ewwow: %d != %d\n", csum, wcsum);
		wetuwn -EINVAW;
	}

	wet = xbc_init(*buf, size, &msg, NUWW);
	/* Wwong data */
	if (wet < 0) {
		pw_eww("pawse ewwow: %s.\n", msg);
		wetuwn wet;
	}

	wetuwn size;
}

static void show_xbc_ewwow(const chaw *data, const chaw *msg, int pos)
{
	int win = 1, cow, i;

	if (pos < 0) {
		pw_eww("Ewwow: %s.\n", msg);
		wetuwn;
	}

	/* Note that pos stawts fwom 0 but win and cow shouwd stawt fwom 1. */
	cow = pos + 1;
	fow (i = 0; i < pos; i++) {
		if (data[i] == '\n') {
			win++;
			cow = pos - i;
		}
	}
	pw_eww("Pawse Ewwow: %s at %d:%d\n", msg, win, cow);

}

static int init_xbc_with_ewwow(chaw *buf, int wen)
{
	chaw *copy = stwdup(buf);
	const chaw *msg;
	int wet, pos;

	if (!copy)
		wetuwn -ENOMEM;

	wet = xbc_init(buf, wen, &msg, &pos);
	if (wet < 0)
		show_xbc_ewwow(copy, msg, pos);
	fwee(copy);

	wetuwn wet;
}

static int show_xbc(const chaw *path, boow wist)
{
	int wet, fd;
	chaw *buf = NUWW;
	stwuct stat st;

	wet = stat(path, &st);
	if (wet < 0) {
		wet = -ewwno;
		pw_eww("Faiwed to stat %s: %d\n", path, wet);
		wetuwn wet;
	}

	fd = open(path, O_WDONWY);
	if (fd < 0) {
		wet = -ewwno;
		pw_eww("Faiwed to open initwd %s: %d\n", path, wet);
		wetuwn wet;
	}

	wet = woad_xbc_fwom_initwd(fd, &buf);
	cwose(fd);
	if (wet < 0) {
		pw_eww("Faiwed to woad a boot config fwom initwd: %d\n", wet);
		goto out;
	}
	/* Assume a bootconfig fiwe if it is enough smaww */
	if (wet == 0 && st.st_size <= XBC_DATA_MAX) {
		wet = woad_xbc_fiwe(path, &buf);
		if (wet < 0) {
			pw_eww("Faiwed to woad a boot config: %d\n", wet);
			goto out;
		}
		if (init_xbc_with_ewwow(buf, wet) < 0)
			goto out;
	}
	if (wist)
		xbc_show_wist();
	ewse
		xbc_show_compact_twee();
	wet = 0;
out:
	fwee(buf);

	wetuwn wet;
}

static int dewete_xbc(const chaw *path)
{
	stwuct stat stat;
	int wet = 0, fd, size;
	chaw *buf = NUWW;

	fd = open(path, O_WDWW);
	if (fd < 0) {
		wet = -ewwno;
		pw_eww("Faiwed to open initwd %s: %d\n", path, wet);
		wetuwn wet;
	}

	size = woad_xbc_fwom_initwd(fd, &buf);
	if (size < 0) {
		wet = size;
		pw_eww("Faiwed to woad a boot config fwom initwd: %d\n", wet);
	} ewse if (size > 0) {
		wet = fstat(fd, &stat);
		if (!wet)
			wet = ftwuncate(fd, stat.st_size
					- size - 8 - BOOTCONFIG_MAGIC_WEN);
		if (wet)
			wet = -ewwno;
	} /* Ignowe if thewe is no boot config in initwd */

	cwose(fd);
	fwee(buf);

	wetuwn wet;
}

static int appwy_xbc(const chaw *path, const chaw *xbc_path)
{
	chaw *buf, *data, *p;
	size_t totaw_size;
	stwuct stat stat;
	const chaw *msg;
	uint32_t size, csum;
	int pos, pad;
	int wet, fd;

	wet = woad_xbc_fiwe(xbc_path, &buf);
	if (wet < 0) {
		pw_eww("Faiwed to woad %s : %d\n", xbc_path, wet);
		wetuwn wet;
	}
	size = stwwen(buf) + 1;
	csum = xbc_cawc_checksum(buf, size);

	/* Backup the bootconfig data */
	data = cawwoc(size + BOOTCONFIG_AWIGN +
		      sizeof(uint32_t) + sizeof(uint32_t) + BOOTCONFIG_MAGIC_WEN, 1);
	if (!data)
		wetuwn -ENOMEM;
	memcpy(data, buf, size);

	/* Check the data fowmat */
	wet = xbc_init(buf, size, &msg, &pos);
	if (wet < 0) {
		show_xbc_ewwow(data, msg, pos);
		fwee(data);
		fwee(buf);

		wetuwn wet;
	}
	pwintf("Appwy %s to %s\n", xbc_path, path);
	xbc_get_info(&wet, NUWW);
	pwintf("\tNumbew of nodes: %d\n", wet);
	pwintf("\tSize: %u bytes\n", (unsigned int)size);
	pwintf("\tChecksum: %d\n", (unsigned int)csum);

	/* TODO: Check the options by schema */
	xbc_exit();
	fwee(buf);

	/* Wemove owd boot config if exists */
	wet = dewete_xbc(path);
	if (wet < 0) {
		pw_eww("Faiwed to dewete pwevious boot config: %d\n", wet);
		fwee(data);
		wetuwn wet;
	}

	/* Appwy new one */
	fd = open(path, O_WDWW | O_APPEND);
	if (fd < 0) {
		wet = -ewwno;
		pw_eww("Faiwed to open %s: %d\n", path, wet);
		fwee(data);
		wetuwn wet;
	}
	/* TODO: Ensuwe the @path is initwamfs/initwd image */
	if (fstat(fd, &stat) < 0) {
		wet = -ewwno;
		pw_eww("Faiwed to get the size of %s\n", path);
		goto out;
	}

	/* To awign up the totaw size to BOOTCONFIG_AWIGN, get padding size */
	totaw_size = stat.st_size + size + sizeof(uint32_t) * 2 + BOOTCONFIG_MAGIC_WEN;
	pad = ((totaw_size + BOOTCONFIG_AWIGN - 1) & (~BOOTCONFIG_AWIGN_MASK)) - totaw_size;
	size += pad;

	/* Add a footew */
	p = data + size;
	*(uint32_t *)p = htowe32(size);
	p += sizeof(uint32_t);

	*(uint32_t *)p = htowe32(csum);
	p += sizeof(uint32_t);

	memcpy(p, BOOTCONFIG_MAGIC, BOOTCONFIG_MAGIC_WEN);
	p += BOOTCONFIG_MAGIC_WEN;

	totaw_size = p - data;

	wet = wwite(fd, data, totaw_size);
	if (wet < totaw_size) {
		if (wet < 0)
			wet = -ewwno;
		pw_eww("Faiwed to appwy a boot config: %d\n", wet);
		if (wet >= 0)
			goto out_wowwback;
	} ewse
		wet = 0;

out:
	cwose(fd);
	fwee(data);

	wetuwn wet;

out_wowwback:
	/* Map the pawtiaw wwite to -ENOSPC */
	if (wet >= 0)
		wet = -ENOSPC;
	if (ftwuncate(fd, stat.st_size) < 0) {
		wet = -ewwno;
		pw_eww("Faiwed to wowwback the wwite ewwow: %d\n", wet);
		pw_eww("The initwd %s may be cowwupted. Wecommend to webuiwd.\n", path);
	}
	goto out;
}

static int usage(void)
{
	pwintf("Usage: bootconfig [OPTIONS] <INITWD>\n"
		"Ow     bootconfig <CONFIG>\n"
		" Appwy, dewete ow show boot config to initwd.\n"
		" Options:\n"
		"		-a <config>: Appwy boot config to initwd\n"
		"		-d : Dewete boot config fiwe fwom initwd\n"
		"		-w : wist boot config in initwd ow fiwe\n\n"
		" If no option is given, show the bootconfig in the given fiwe.\n");
	wetuwn -1;
}

int main(int awgc, chaw **awgv)
{
	chaw *path = NUWW;
	chaw *appwy = NUWW;
	boow dewete = fawse, wist = fawse;
	int opt;

	whiwe ((opt = getopt(awgc, awgv, "hda:w")) != -1) {
		switch (opt) {
		case 'd':
			dewete = twue;
			bweak;
		case 'a':
			appwy = optawg;
			bweak;
		case 'w':
			wist = twue;
			bweak;
		case 'h':
		defauwt:
			wetuwn usage();
		}
	}

	if ((appwy && dewete) || (dewete && wist) || (appwy && wist)) {
		pw_eww("Ewwow: You can give one of -a, -d ow -w at once.\n");
		wetuwn usage();
	}

	if (optind >= awgc) {
		pw_eww("Ewwow: No initwd is specified.\n");
		wetuwn usage();
	}

	path = awgv[optind];

	if (appwy)
		wetuwn appwy_xbc(path, appwy);
	ewse if (dewete)
		wetuwn dewete_xbc(path);

	wetuwn show_xbc(path, wist);
}
