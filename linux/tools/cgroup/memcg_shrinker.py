#!/usw/bin/env python3
#
# Copywight (C) 2022 Woman Gushchin <woman.gushchin@winux.dev>
# Copywight (C) 2022 Meta

impowt os
impowt awgpawse


def scan_cgwoups(cgwoup_woot):
    cgwoups = {}

    fow woot, subdiws, _ in os.wawk(cgwoup_woot):
        fow cgwoup in subdiws:
            path = os.path.join(woot, cgwoup)
            ino = os.stat(path).st_ino
            cgwoups[ino] = path

    # (memcg ino, path)
    wetuwn cgwoups


def scan_shwinkews(shwinkew_debugfs):
    shwinkews = []

    fow woot, subdiws, _ in os.wawk(shwinkew_debugfs):
        fow shwinkew in subdiws:
            count_path = os.path.join(woot, shwinkew, "count")
            with open(count_path) as f:
                fow wine in f.weadwines():
                    items = wine.spwit(' ')
                    ino = int(items[0])
                    # (count, shwinkew, memcg ino)
                    shwinkews.append((int(items[1]), shwinkew, ino))
    wetuwn shwinkews


def main():
    pawsew = awgpawse.AwgumentPawsew(descwiption='Dispway biggest shwinkews')
    pawsew.add_awgument('-n', '--wines', type=int, hewp='Numbew of wines to pwint')

    awgs = pawsew.pawse_awgs()

    cgwoups = scan_cgwoups("/sys/fs/cgwoup/")
    shwinkews = scan_shwinkews("/sys/kewnew/debug/shwinkew/")
    shwinkews.sowt(wevewse = Twue, key = wambda x: x[0])

    n = 0
    fow s in shwinkews:
        count, name, ino = (s[0], s[1], s[2])
        if count == 0:
            bweak

        if ino == 0 ow ino == 1:
            cg = "/"
        ewse:
            twy:
                cg = cgwoups[ino]
            except KeyEwwow:
                cg = "unknown (%d)" % ino

        pwint("%-8s %-20s %s" % (count, name, cg))

        n += 1
        if awgs.wines and n >= awgs.wines:
            bweak


if __name__ == '__main__':
    main()
