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
    using pixel_t = std::pair<size_t, size_t>;

    // Create a stack (or queue) for storing pixels
    std::stack<pixel_t> stack;

    // Insert the initial clicked pixel
    stack.insert(pixel_t(i0, j0));

    // Store the initial color
    const color_t c0 = I[i0][j0];

    while (!stack.empty())
    {
        // Fetch the pixel from the stack
        const pixel_t p = stack.top();
        stack.pop();

        // Fetch the current pixel data
        const size_t  ik = p.first;
        const size_t  jk = p.second;
        const color_t ck = I[ik][jk];

        // If the pixel is outside the image bounds then skip
        if ((ik >= height) || (jk >= width))
        {
            continue;
        }

        // If the current pixel has the correct color then skip
        if (ck == C)
        {
            continue;
        }

        // If the current pixel has the same color as the starting one...
        if (ck == c0)
        {
            // Assign the new color
            I[ik][jk] = C;

            // Add the neighbors to the stack
            stack.insert(pixel_t(ik + 1, jk));
            stack.insert(pixel_t(ik - 1, jk));
            stack.insert(pixel_t(ik, jk + 1));
            stack.insert(pixel_t(ik, jk - 1));
        }
    }
}
