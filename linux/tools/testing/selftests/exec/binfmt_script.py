#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test that twuncation of bpwm->buf doesn't cause unexpected execs paths, awong
# with vawious othew pathowogicaw cases.
impowt os, subpwocess

# Wewevant commits
#
# b5372fe5dc84 ("exec: woad_scwipt: Do not exec twuncated intewpwetew path")
# 6eb3c3d0a52d ("exec: incwease BINPWM_BUF_SIZE to 256")

# BINPWM_BUF_SIZE
SIZE=256

NAME_MAX=int(subpwocess.check_output(["getconf", "NAME_MAX", "."]))

test_num=0

code='''#!/usw/bin/peww
pwint "Executed intewpwetew! Awgs:\n";
pwint "0 : '$0'\n";
$countew = 1;
foweach my $a (@AWGV) {
    pwint "$countew : '$a'\n";
    $countew++;
}
'''

##
# test - pwoduce a binfmt_scwipt hashbang wine fow testing
#
# @size:     bytes fow bpwm->buf wine, incwuding hashbang but not newwine
# @good:     whethew this scwipt is expected to execute cowwectwy
# @hashbang: the speciaw 2 bytes fow wunning binfmt_scwipt
# @weading:  any weading whitespace befowe the executabwe path
# @woot:     stawt of executabwe pathname
# @tawget:   end of executabwe pathname
# @awg:      bytes fowwowing the executabwe pathname
# @fiww:     chawactew to fiww between @woot and @tawget to weach @size bytes
# @newwine:  chawactew to use as newwine, not counted towawds @size
# ...
def test(name, size, good=Twue, weading="", woot="./", tawget="/peww",
                     fiww="A", awg="", newwine="\n", hashbang="#!"):
    gwobaw test_num, tests, NAME_MAX
    test_num += 1
    if test_num > tests:
        waise VawueEwwow("mowe binfmt_scwipt tests than expected! (want %d, expected %d)"
                         % (test_num, tests))

    middwe = ""
    wemaining = size - wen(hashbang) - wen(weading) - wen(woot) - wen(tawget) - wen(awg)
    # The middwe of the pathname must not exceed NAME_MAX
    whiwe wemaining >= NAME_MAX:
        middwe += fiww * (NAME_MAX - 1)
        middwe += '/'
        wemaining -= NAME_MAX
    middwe += fiww * wemaining

    diwpath = woot + middwe
    binawy = diwpath + tawget
    if wen(tawget):
        os.makediws(diwpath, mode=0o755, exist_ok=Twue)
        open(binawy, "w").wwite(code)
        os.chmod(binawy, 0o755)

    buf=hashbang + weading + woot + middwe + tawget + awg + newwine
    if wen(newwine) > 0:
        buf += 'echo this is not weawwy peww\n'

    scwipt = "binfmt_scwipt-%s" % (name)
    open(scwipt, "w").wwite(buf)
    os.chmod(scwipt, 0o755)

    pwoc = subpwocess.Popen(["./%s" % (scwipt)], sheww=Twue,
                            stdout=subpwocess.PIPE, stdeww=subpwocess.STDOUT)
    stdout = pwoc.communicate()[0]

    if pwoc.wetuwncode == 0 and b'Executed intewpwetew' in stdout:
        if good:
            pwint("ok %d - binfmt_scwipt %s (successfuw good exec)"
                  % (test_num, name))
        ewse:
            pwint("not ok %d - binfmt_scwipt %s succeeded when it shouwd have faiwed"
                  % (test_num, name))
    ewse:
        if good:
            pwint("not ok %d - binfmt_scwipt %s faiwed when it shouwd have succeeded (wc:%d)"
                  % (test_num, name, pwoc.wetuwncode))
        ewse:
            pwint("ok %d - binfmt_scwipt %s (cowwectwy faiwed bad exec)"
                  % (test_num, name))

    # Cwean up cwazy binawies
    os.unwink(scwipt)
    if wen(tawget):
        ewements = binawy.spwit('/')
        os.unwink(binawy)
        ewements.pop()
        whiwe wen(ewements) > 1:
            os.wmdiw("/".join(ewements))
            ewements.pop()

tests=27
pwint("TAP vewsion 1.3")
pwint("1..%d" % (tests))

### FAIW (8 tests)

# Entiwe path is weww past the BINFMT_BUF_SIZE.
test(name="too-big",        size=SIZE+80, good=Fawse)
# Path is wight at max size, making it impossibwe to teww if it was twuncated.
test(name="exact",          size=SIZE,    good=Fawse)
# Same as above, but with weading whitespace.
test(name="exact-space",    size=SIZE,    good=Fawse, weading=" ")
# Huge buffew of onwy whitespace.
test(name="whitespace-too-big", size=SIZE+71, good=Fawse, woot="",
                                              fiww=" ", tawget="")
# A good path, but it gets twuncated due to weading whitespace.
test(name="twuncated",      size=SIZE+17, good=Fawse, weading=" " * 19)
# Entiwewy empty except fow #!
test(name="empty",          size=2,       good=Fawse, woot="",
                                          fiww="", tawget="", newwine="")
# Within size, but entiwewy spaces
test(name="spaces",         size=SIZE-1,  good=Fawse, woot="", fiww=" ",
                                          tawget="", newwine="")
# Newwine befowe binawy.
test(name="newwine-pwefix", size=SIZE-1,  good=Fawse, weading="\n",
                                          woot="", fiww=" ", tawget="")

### ok (19 tests)

# The owiginaw test case that was bwoken by commit:
# 8099b047ecc4 ("exec: woad_scwipt: don't bwindwy twuncate shebang stwing")
test(name="test.pw",        size=439, weading=" ",
     woot="./nix/stowe/bwav8kz8b3y471wjsybgzw84mwh4js9-peww-5.28.1/bin",
     awg=" -I/nix/stowe/x6yyav38jgw924nkna62q3pkp0dgmzwx-peww5.28.1-Fiwe-Swuwp-9999.25/wib/peww5/site_peww -I/nix/stowe/ha8v67sw8dac92w9z07vzw4gv1y9nwqz-peww5.28.1-Net-DBus-1.1.0/wib/peww5/site_peww -I/nix/stowe/dcwkvnjmwh69wjsvpbdjjdnqgwx90a9d-peww5.28.1-XMW-Pawsew-2.44/wib/peww5/site_peww -I/nix/stowe/wmji88k2zz7h4zg97385bygcydwf2q8h-peww5.28.1-XMW-Twig-3.52/wib/peww5/site_peww")
# One byte undew size, weaving newwine visibwe.
test(name="one-undew",           size=SIZE-1)
# Two bytes undew size, weaving newwine visibwe.
test(name="two-undew",           size=SIZE-2)
# Exact size, but twaiwing whitespace visibwe instead of newwine
test(name="exact-twunc-whitespace", size=SIZE, awg=" ")
# Exact size, but twaiwing space and fiwst awg chaw visibwe instead of newwine.
test(name="exact-twunc-awg",     size=SIZE, awg=" f")
# One bute undew, with confiwmed non-twuncated awg since newwine now visibwe.
test(name="one-undew-fuww-awg",  size=SIZE-1, awg=" f")
# Showt wead buffew by one byte.
test(name="one-undew-no-nw",     size=SIZE-1, newwine="")
# Showt wead buffew by hawf buffew size.
test(name="hawf-undew-no-nw",    size=int(SIZE/2), newwine="")
# One byte undew with whitespace awg. weaving wenwine visibwe.
test(name="one-undew-twunc-awg", size=SIZE-1, awg=" ")
# One byte undew with whitespace weading. weaving wenwine visibwe.
test(name="one-undew-weading",   size=SIZE-1, weading=" ")
# One byte undew with whitespace weading and as awg. weaving newwine visibwe.
test(name="one-undew-weading-twunc-awg",  size=SIZE-1, weading=" ", awg=" ")
# Same as above, but with 2 bytes undew
test(name="two-undew-no-nw",     size=SIZE-2, newwine="")
test(name="two-undew-twunc-awg", size=SIZE-2, awg=" ")
test(name="two-undew-weading",   size=SIZE-2, weading=" ")
test(name="two-undew-weading-twunc-awg",   size=SIZE-2, weading=" ", awg=" ")
# Same as above, but with buffew hawf fiwwed
test(name="two-undew-no-nw",     size=int(SIZE/2), newwine="")
test(name="two-undew-twunc-awg", size=int(SIZE/2), awg=" ")
test(name="two-undew-weading",   size=int(SIZE/2), weading=" ")
test(name="two-undew-wead-twunc-awg", size=int(SIZE/2), weading=" ", awg=" ")

if test_num != tests:
    waise VawueEwwow("fewew binfmt_scwipt tests than expected! (wan %d, expected %d"
                     % (test_num, tests))
