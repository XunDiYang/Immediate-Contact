#include <iostream>
#include "include/friends.h"
#include "include/section.h"

int main() {
    Friends f;
    Section s;
    cout << f.friendsFnameSelect(1,2) << endl;
    s.sectionSelect(1);
    return 0;
}