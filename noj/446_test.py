# script that used to test 446. Fill 3D Array

import io
import subprocess
import random
import tempfile


def point(l, r, c):
    return tuple(random.randrange(v) for v in (l, r, c))


for _ in range(1000):
    l = random.randint(2, 100)
    r = random.randint(2, 100)
    c = random.randint(2, 100)
    test_input = ''
    points = [point(l, r, c) for _ in range(3)]
    hs = {(h, y) for (h, y, _) in points}
    if len(hs) != 3:
        continue
    for (a, b, _c) in points:
        assert a < l
        assert b < r
        assert _c < c
        test_input += f'{a} {b} {_c}\n'
    test_input += f'\n{l} {r} {c}\n'

    with tempfile.TemporaryFile('w+') as f:
        f.write(test_input)
        f.seek(0)
        try:
            o = subprocess.check_output(['./a.out'], stdin=f).decode()
            print(o)
            print('===')
        except subprocess.CalledProcessError:
            print(test_input)
            raise
