/*
 * StringReverser.cpp
 *
 *  Created on: 15 Jan 2020
 *      Author: eitan
 */

#include "StringReverser.h"
#include <algorithm>
string StringReverser::slove(string problem) {
    reverse(problem.begin(), problem.end());
    return problem;
}
