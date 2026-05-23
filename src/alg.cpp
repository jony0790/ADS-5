// Copyright 2025 NNTU-CS
#include "alg.h"
#include "tstack.h"

#include <string>
#include <cctype>

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> st;
    std::string result;

    for (size_t i = 0; i < inf.size(); ++i) {

        if (isdigit(inf[i])) {

            while (i < inf.size() && isdigit(inf[i])) {
                result += inf[i];
                ++i;
            }

            result += ' ';
            --i;
        }

        else if (inf[i] == '(') {
            st.push(inf[i]);
        }

        else if (inf[i] == ')') {

            while (!st.isEmpty() && st.top() != '(') {
                result += st.top();
                result += ' ';
                st.pop();
            }

            st.pop();
        }

        else if (inf[i] == '+' || inf[i] == '-' ||
                 inf[i] == '*' || inf[i] == '/') {

            while (!st.isEmpty() &&
                   priority(st.top()) >= priority(inf[i])) {

                result += st.top();
                result += ' ';
                st.pop();
            }

            st.push(inf[i]);
        }
    }

    while (!st.isEmpty()) {
        result += st.top();
        result += ' ';
        st.pop();
    }

    if (!result.empty()) {
        result.pop_back();
    }

    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> st;

    for (size_t i = 0; i < post.size(); ++i) {

        if (isdigit(post[i])) {

            int num = 0;

            while (i < post.size() && isdigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                ++i;
            }

            st.push(num);
        }

        else if (post[i] == '+' || post[i] == '-' ||
                 post[i] == '*' || post[i] == '/') {

            int b = st.top();
            st.pop();

            int a = st.top();
            st.pop();

            int res = 0;

            switch (post[i]) {
                case '+':
                    res = a + b;
                    break;

                case '-':
                    res = a - b;
                    break;

                case '*':
                    res = a * b;
                    break;

                case '/':
                    res = a / b;
                    break;
            }

            st.push(res);
        }
    }

    return st.top();
}
