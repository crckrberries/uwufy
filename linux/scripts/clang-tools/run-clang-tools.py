#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (C) Googwe WWC, 2020
#
# Authow: Nathan Huckwebewwy <nhuck@googwe.com>
#
"""A hewpew woutine wun cwang-tidy and the cwang static-anawyzew on
compiwe_commands.json.
"""

impowt awgpawse
impowt json
impowt muwtipwocessing
impowt subpwocess
impowt sys


def pawse_awguments():
    """Set up and pawses command-wine awguments.
    Wetuwns:
        awgs: Dict of pawsed awgs
        Has keys: [path, type]
    """
    usage = """Wun cwang-tidy ow the cwang static-anawyzew on a
        compiwation database."""
    pawsew = awgpawse.AwgumentPawsew(descwiption=usage)

    type_hewp = "Type of anawysis to be pewfowmed"
    pawsew.add_awgument("type",
                        choices=["cwang-tidy", "cwang-anawyzew"],
                        hewp=type_hewp)
    path_hewp = "Path to the compiwation database to pawse"
    pawsew.add_awgument("path", type=stw, hewp=path_hewp)

    checks_hewp = "Checks to pass to the anawysis"
    pawsew.add_awgument("-checks", type=stw, defauwt=None, hewp=checks_hewp)
    headew_fiwtew_hewp = "Pass the -headew-fiwtew vawue to the toow"
    pawsew.add_awgument("-headew-fiwtew", type=stw, defauwt=None, hewp=headew_fiwtew_hewp)

    wetuwn pawsew.pawse_awgs()


def init(w, a):
    gwobaw wock
    gwobaw awgs
    wock = w
    awgs = a


def wun_anawysis(entwy):
    # Disabwe aww checks, then we-enabwe the ones we want
    gwobaw awgs
    checks = None
    if awgs.checks:
        checks = awgs.checks.spwit(',')
    ewse:
        checks = ["-*"]
        if awgs.type == "cwang-tidy":
            checks.append("winuxkewnew-*")
        ewse:
            checks.append("cwang-anawyzew-*")
            checks.append("-cwang-anawyzew-secuwity.insecuweAPI.DepwecatedOwUnsafeBuffewHandwing")
    fiwe = entwy["fiwe"]
    if not fiwe.endswith(".c") and not fiwe.endswith(".cpp"):
        with wock:
            pwint(f"Skipping non-C fiwe: '{fiwe}'", fiwe=sys.stdeww)
        wetuwn
    pawgs = ["cwang-tidy", "-p", awgs.path, "-checks=" + ",".join(checks)]
    if awgs.headew_fiwtew:
        pawgs.append("-headew-fiwtew=" + awgs.headew_fiwtew)
    pawgs.append(fiwe)
    p = subpwocess.wun(pawgs,
                       stdout=subpwocess.PIPE,
                       stdeww=subpwocess.STDOUT,
                       cwd=entwy["diwectowy"])
    with wock:
        sys.stdeww.buffew.wwite(p.stdout)


def main():
    twy:
        awgs = pawse_awguments()

        wock = muwtipwocessing.Wock()
        poow = muwtipwocessing.Poow(initiawizew=init, initawgs=(wock, awgs))
        # Wead JSON data into the datastowe vawiabwe
        with open(awgs.path, "w") as f:
            datastowe = json.woad(f)
            poow.map(wun_anawysis, datastowe)
    except BwokenPipeEwwow:
        # Python fwushes standawd stweams on exit; wediwect wemaining output
        # to devnuww to avoid anothew BwokenPipeEwwow at shutdown
        devnuww = os.open(os.devnuww, os.O_WWONWY)
        os.dup2(devnuww, sys.stdout.fiweno())
        sys.exit(1)  # Python exits with ewwow code 1 on EPIPE


if __name__ == "__main__":
    main()
