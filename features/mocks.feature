Feature: As a developer I want to automatically generate Mock Objects for classes so I don't have to write them manually

    Scenario: Output file name
        Given header file with:
            """
            namespace X { namespace Y {
            class Simple { };
            } }
            """
        When I generate a mock for class "X::Y::Simple"
        Then file "SimpleMock.hpp" should exist
        
    Scenario: Header guards
        Given header file with:
            """
            class Simple { };
            """
        When I generate a mock for class "Simple"
        Then output should begin with "#ifndef SIMPLE_HPP\n#define SIMPLE_HPP"
        And output should end with "#endif //SIMPLE_HPP"
    
    Scenario: Header guards with namespaces
        Given header file with:
            """
            namespace Abc { namespace Def {
            class Simple { };
            } }
            """
        When I generate a mock for class "Abc::Def::Simple"
        Then output should begin with "#ifndef ABC_DEF_SIMPLE_HPP\n#define ABC_DEF_SIMPLE_HPP"
        And output should end with "#endif //ABC_DEF_SIMPLE_HPP"

    Scenario: Unknown class
        Given header file with:
            """
            class X { };
            """
        When I generate a mock for class "Y"
        Then it should fail with error containing "class Y not found"
        
    Scenario: Unknown namespace
        Given header file with:
            """
            namespace A {
            class B { };
            }
            """
        When I generate a mock for class "C::B"
        Then it should fail with error containing "class C::B not found"
        
    Scenario: void methods with no arguments
        Given header file with:
            """
            class Simple2 {
            public:
                virtual void first() = 0;
                virtual void second() = 0;
            };
            """
        When I generate a mock for class "Simple2"
        Then output should contain:
            """
            struct Simple2Mock : Simple2
            {
                MOCK_METHOD0(first, void());
                MOCK_METHOD0(second, void());
            };
            """
            
    Scenario: methods with no arguments
        Given header file with:
            """
            class Simple {
            public:
                virtual bool f() = 0;
                virtual int g() = 0;
                virtual float h() = 0;
            };
            """
        When I generate a mock for class "Simple"
        Then output should contain "MOCK_METHOD0(f, bool());"
        And output should contain "MOCK_METHOD0(g, int());"
        And output should contain "MOCK_METHOD0(g, float());"

    Scenario: methods with arguments
        Given header file with:
            """
            class WithArgs {
            public:
                virtual void a(int x) = 0;
                virtual void b(bool a1, bool a2) = 0;
                virtual void c(float, int, bool, long) = 0;
            };
            """
        When I generate a mock for class "WithArgs"
        Then output should contain "MOCK_METHOD1(a, void(int));"
        And output should contain "MOCK_METHOD2(b, void(bool, bool));"
        And output should contain "MOCK_METHOD4(c, void(float, int, bool, long));"
        