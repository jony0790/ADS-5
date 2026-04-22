#include <string>
#include <cctype>
#include "tstack.h"


int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}


std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string result;

    for (size_t i = 0; i < inf.size(); i++) {
        char c = inf[i];

        
        if (isdigit(c)) {
            while (i < inf.size() && isdigit(inf[i])) {
                result += inf[i];
                i++;
            }
            result += ' ';
            i--; 
        }


        else if (c == '(') {
            stack.push(c);
        }

        
        else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                result += stack.top();
                result += ' ';
                stack.pop();
            }
            stack.pop(); 
        }


        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!stack.empty() && priority(stack.top()) >= priority(c)) {
                result += stack.top();
                result += ' ';
                stack.pop();
            }
            stack.push(c);
        }
    }


    while (!stack.empty()) {
        result += stack.top();
        result += ' ';
        stack.pop();
    }

    return result;
}



int eval(const std::string& post) {
    TStack<int, 100> stack;

    for (size_t i = 0; i < post.size(); i++) {

   
        if (post[i] == ' ')
            continue;

        // число
        if (isdigit(post[i])) {
            int num = 0;

            while (i < post.size() && isdigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                i++;
            }

            stack.push(num);
            i--; 
        }

       
        else {
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();

            int res = 0;

            if (post[i] == '+') res = a + b;
            else if (post[i] == '-') res = a - b;
            else if (post[i] == '*') res = a * b;
            else if (post[i] == '/') res = a / b;

            stack.push(res);
        }
    }

    return stack.top();
}
