#include <assert.h>
#include "string_split.h"

int main(void) {
    const char *input = ",A,B";
    struct string_split_iterator it;
    
    string_split_init(&it, input, ',');

    assert(string_split_next(&it) == 0 && "next should return 0 when there is another range");
    assert(it.begin == input && "it.begin should point to input + 0");
    assert(it.end == input && "it.end should point to input + 0");

    assert(string_split_next(&it) == 0 && "next should return 0 when there is another range");
    assert(it.begin == input + 1 && "it.begin should point to the input + 1");
    assert(it.end == input + 2 && "it.end should point to the input + 2");

    assert(string_split_next(&it) == 0 && "next should return 0 when there is another range");
    assert(it.begin == input + 3 && "it.begin should point to the input + 3");
    assert(it.end == input + 4 && "it.end should point to the input + 4");

    assert(string_split_next(&it) != 0 && "next should return non 0 when there isn't another range");

    return 0;
}