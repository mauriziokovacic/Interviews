# Flood Fill

Imagine you are developing tools for an image processing software. It is required you implement a flood fill algorithm.

The flood fill tool, commonly depicted with the bucket icon, fills a given image with a color $C$, from an initial pixel `I(i0, j0) = c0`, to every neighboring pixel `I(ik, jk) = ck` if the condition:
- `ck == c0`

is met. In this case, the value of the new pixel should be changed as `I(ik, jk) = C`.

If a pixel has already the desired color, then we can safely skip it and its neighbors.

```
using color_t = unsigned long int;
using size_t  = unsigned long int;

void flood_fill(
    color_t** I,
    const size_t  width,
    const size_t  height,
    const size_t  i0,
    const size_t  j0,
    const color_t C)
{
    // ...
}
```
