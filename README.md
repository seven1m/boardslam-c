# Boardslam in C

This is a port of my [boardslam.rb script](https://gist.github.com/seven1m/6a36782b93f10fa15a2fc381fd91bfb1) to C.

Explanation here: [seven1m.sdf.org/experiments/boardslam.cgi](http://seven1m.sdf.org/experiments/boardslam.cgi)

## Build

1. Run `make`

## Usage

```
./boardslam 1 2 3

1   + 2^0 - 3^0 = 1
1   + 2   - 3^0 = 2
1   + 2^0 + 3^0 = 3
1   + 2   + 3^0 = 4
1   + 2^0 + 3   = 5
1   + 2   + 3   = 6
2^2 + 3   * 1   = 7
1   + 2^2 + 3   = 8
1   + 3^2 - 2^0 = 9
1   + 2^3 + 3^0 = 10
1   + 2^0 + 3^2 = 11
1   + 2   + 3^2 = 12
2^2 + 3^2 * 1   = 13
1   + 2^2 + 3^2 = 14
1   + 2^2 * 3   = 15
2^3 + 3^2 - 1   = 16
2^3 + 3^2 * 1   = 17
1   + 2^3 + 3^2 = 18
3^3 - 2^3 * 1   = 19
1   + 3^3 - 2^3 = 20
2^3 - 1   * 3   = 21
3^3 - 1   - 2^2 = 22
3^3 - 2^2 * 1   = 23
1   + 3^3 - 2^2 = 24
3^3 - 1   - 2^0 = 25
1   + 3^3 - 2   = 26
1   + 3^3 - 2^0 = 27
2   + 3^3 - 1   = 28
1   + 2^0 + 3^3 = 29
1   + 2   + 3^3 = 30
2^2 + 3^3 * 1   = 31
1   + 2^2 + 3^3 = 32
2^3 + 3^3 - 1   = 34
2^3 + 3^3 * 1   = 35
1   + 2^3 + 3^3 = 36

missing: 33
```

License: MIT
