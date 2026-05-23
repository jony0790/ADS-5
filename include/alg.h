#ifndef INCLUDE_ALG_H_
#define INCLUDE_ALG_H_

#include <string>

// infix -> postfix
std::string infx2pstfx(const std::string& inf);

// postfix evaluation
int eval(const std::string& post);

#endif  // INCLUDE_ALG_H_
