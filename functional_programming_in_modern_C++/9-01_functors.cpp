#include <iostream>
#include <string>

using namespace std;

class StringOperation
{
public:
    virtual string operator()(string &input) const = 0;
    virtual ~StringOperation(){}
};

class Append : public StringOperation
{
public:
    Append(string suf) : m_suffix{suf} {}

    virtual string operator()(string &input) const override
    {
        return input + m_suffix;
    }
    virtual ~Append() {}
private:
    string m_suffix{};
};

class Prepend : public StringOperation
{
public:
    Prepend(string prefix) : m_prefix{prefix} {}

    virtual string operator()(string &text) const override
    {
        return m_prefix + text;
    }
    virtual ~Prepend() {}
private:
    string m_prefix{};
};

string process(string &text, StringOperation &operation)
{
    cout << "processing " << text << endl;
    return operation(text);
}

int main()
{
    Prepend p{"custom_prefix_"};
    Append a{"_custom_sufix"};
    
    string s{"Ana are mere"};
    s = process(s, a);
    s = process(s, p);
    cout << s << endl;

    return 0;
}
