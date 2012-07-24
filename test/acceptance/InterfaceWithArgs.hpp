class InterfaceWithArgs
{
public:
    virtual void m1(int x) = 0;
    virtual void m2(bool a, double b) = 0;
    virtual bool m3(char a, const char *b, const char *(*c)()) = 0;
};