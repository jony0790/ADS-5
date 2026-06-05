#include <string>
#include <cctype>
#include "../include/tstack.h"

int priority(char op) {
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    return 0;
}

// infiks -> postfiks
std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> st;
    std::string result;

    for (size_t i = 0; i < inf.size();) {

        if (isspace(inf[i])) {
            ++i;
            continue;
        }

        if (isdigit(inf[i])) {
            while (i < inf.size() && isdigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' ';
        }
        else if (inf[i] == '(') {
            st.push('(');
            ++i;
        }
        else if (inf[i] == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top();
                result += ' ';
                st.pop();
            }

            if (!st.empty())
                st.pop();

            ++i;
        }
        else {
            char op = inf[i];

            while (!st.empty() &&
                   st.top() != '(' &&
                   priority(st.top()) >= priority(op))
            {
                result += st.top();
                result += ' ';
                st.pop();
            }

            st.push(op);
            ++i;
        }
    }

    while (!st.empty()) {
        result += st.top();
        result += ' ';
        st.pop();
    }

    if (!result.empty() && result.back() == ' ')
        result.pop_back();

    return result;
}

// postfiks ifodani hisoblash
int eval(const std::string& post) {
    TStack<int, 100> st;

    for (size_t i = 0; i < post.size();) {

        if (isspace(post[i])) {
            ++i;
            continue;
        }

        if (isdigit(post[i])) {
            int num = 0;

            while (i < post.size() && isdigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                ++i;
            }

            st.push(num);
        }
        else {
            int b = st.top();
            st.pop();

            int a = st.top();
            st.pop();

            switch (post[i]) {
                case '+':
                    st.push(a + b);
                    break;

                case '-':
                    st.push(a - b);
                    break;

                case '*':
                    st.push(a * b);
                    break;

                case '/':
                    st.push(a / b);
                    break;
            }

            ++i;
        }
    }

    return st.top();
}
