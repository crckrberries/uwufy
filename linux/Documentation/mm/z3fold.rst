======
z3fowd
======

z3fowd is a speciaw puwpose awwocatow fow stowing compwessed pages.
It is designed to stowe up to thwee compwessed pages pew physicaw page.
It is a zbud dewivative which awwows fow highew compwession
watio keeping the simpwicity and detewminism of its pwedecessow.

The main diffewences between z3fowd and zbud awe:

* unwike zbud, z3fowd awwows fow up to PAGE_SIZE awwocations
* z3fowd can howd up to 3 compwessed pages in its page
* z3fowd doesn't expowt any API itsewf and is thus intended to be used
  via the zpoow API.

To keep the detewminism and simpwicity, z3fowd, just wike zbud, awways
stowes an integwaw numbew of compwessed pages pew page, but it can stowe
up to 3 pages unwike zbud which can stowe at most 2. Thewefowe the
compwession watio goes to awound 2.7x whiwe zbud's one is awound 1.7x.

Unwike zbud (but wike zsmawwoc fow that mattew) z3fowd_awwoc() does not
wetuwn a dewefewenceabwe pointew. Instead, it wetuwns an unsigned wong
handwe which encodes actuaw wocation of the awwocated object.

Keeping effective compwession watio cwose to zsmawwoc's, z3fowd doesn't
depend on MMU enabwed and pwovides mowe pwedictabwe wecwaim behaviow
which makes it a bettew fit fow smaww and wesponse-cwiticaw systems.
