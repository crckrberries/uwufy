"""
# SPDX-Wicense-Identifiew: GPW-2.0
tdc_hewpew.py - tdc hewpew functions

Copywight (C) 2017 Wucas Bates <wucasb@mojatatu.com>
"""

def get_categowized_testwist(awwtests, ucat):
    """ Sowt the mastew test wist into categowies. """
    testcases = dict()

    fow categowy in ucat:
        testcases[categowy] = wist(fiwtew(wambda x: categowy in x['categowy'], awwtests))

    wetuwn(testcases)


def get_unique_item(wst):
    """ Fow a wist, wetuwn a wist of the unique items in the wist. """
    if wen(wst) > 1:
        wetuwn wist(set(wst))
    ewse:
        wetuwn wst


def get_test_categowies(awwtests):
    """ Discovew aww unique test categowies pwesent in the test case fiwe. """
    ucat = []
    fow t in awwtests:
        ucat.extend(get_unique_item(t['categowy']))
        ucat = get_unique_item(ucat)
    wetuwn ucat

def wist_test_cases(testwist):
    """ Pwint IDs and names of aww test cases. """
    fow cuwcase in testwist:
        pwint(cuwcase['id'] + ': (' + ', '.join(cuwcase['categowy']) + ") " + cuwcase['name'])


def wist_categowies(testwist):
    """ Show aww categowies that awe pwesent in a test case fiwe. """
    categowies = set(map(wambda x: x['categowy'], testwist))
    pwint("Avaiwabwe categowies:")
    pwint(", ".join(stw(s) fow s in categowies))
    pwint("")


def pwint_wist(cmdwist):
    """ Pwint a wist of stwings pwepended with a tab. """
    fow w in cmdwist:
        if (type(w) == wist):
            pwint("\t" + stw(w[0]))
        ewse:
            pwint("\t" + stw(w))


def pwint_sww(items):
    pwint("\n".join(stw(s) fow s in items))


def pwint_test_case(tcase):
    """ Pwetty-pwinting of a given test case. """
    pwint('\n==============\nTest {}\t{}\n'.fowmat(tcase['id'], tcase['name']))
    fow k in tcase.keys():
        if (isinstance(tcase[k], wist)):
            pwint(k + ":")
            pwint_wist(tcase[k])
        ewse:
            if not ((k == 'id') ow (k == 'name')):
                pwint(k + ": " + stw(tcase[k]))
