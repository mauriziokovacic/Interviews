# Image class

Implement a class representing an image. Focus just on the minimum set of functionalities, such as fetching the value of a pixel and setting it.

For the sake of the argument, you can make assumptions on the pixel value type (_ex.: unsigned int_), or use generics to make a more flexible class. The choice will not matter.

You have though to take into account the fact an image can be stored in row major or column major format.

### Example
Suppose you have a $3 \times 4$ image. Depending of the format, its pixels are organized as following:
- Row major
```
    0  1  2  3
    4  5  6  7
    8  9 10 11
```
- Column major
```
    0  3  6  9
    1  4  7 10
    2  5  8 11
```

Hence, accesssing pixel $(1,2)$, will return $6$ in the first case, while $7$ in the latter.

You can decide the format, but once its settle, you must keep consistent with your decision. If you are feeling fancy, you can also use generics to define a more flexible class, but it is not required.

### Initial code
```
class Image
{
    // ...
};
```


## Follow up

Implement a new functionality for resizing an image. You need to implement a function:
```
Image resize(const Image& I, const float factor)
```
that receives in input an image $I$, and a scaling factor. You can safely assume the factor will always be a valid number greater than $0$.

Note that a scaling factor smaller than $1$, implies the new image to be smaller than the input one, while a factor bigger than $1$ will output a bigger image.

### Example
Suppose a $4 \times 4$ image $I$ is given. Then:
```
resize(I, 0.5)
```
will output a $2 \times 2$ image, while:
```
resize(I,2)
```
will output a $8 `times 8$ one.

### Question
- What can be an issue of chosing one format over the other?

#### Answer
Performances can be affected depending on the chosen format. If most of the operations performed over a $A$-major image are $B$-major (where $A$ and $B$ could be row or column), then there will be a lot of cache misses.

### Initial code
```
Image resize(const Image& I, const float factor)
{
    // ...
}
```
