#include <assert.h>
#include "string_split.h"

int main(void) {
    const char *input = "A,B,C";
    struct string_split_iterator it;
    assert(string_split_init(&it, input, ',') == 0 && "initialize should return 0 when inputs are good");
    assert(string_split_next(&it) == 0 && "next should return 0 when there is another range");
    assert(it.begin == input && "it.begin should point to input + 0");
    assert(it.end == input + 1 && "it.end should point to input + 1");
    
    assert(string_split_next(&it) == 0 && "next should return 0 when there is another range");
    assert(it.begin == input + 2 && "it.begin should point to input + 2");
    assert(it.end == input + 3 && "it.end should point to input + 3");
    
    assert(string_split_next(&it) == 0 && "next should return 0 when there is another range");
    assert(it.begin == input + 4 && "it.begin should point to input + 4");
    assert(it.end == input + 5 && "it.end should point to input + 5");
    
    assert(string_split_next(&it) != 0 && "next should return non 0 when there isn't another range");
    return 0;
}