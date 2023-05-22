In file included from /Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.cpp:12:
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/IRGenerator.hpp:19:5: error: use of class template 'IRBuilder' requires template arguments; argument deduction not allowed in non-static class member
    llvm::IRBuilder* IRBuilder;
    ^~~~
/Users/wangzijun/llvm-project/llvm/include/llvm/IR/IRBuilder.h:2564:7: note: template is declared here
class IRBuilder : public IRBuilderBase {
      ^
In file included from /Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.cpp:12:
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/IRGenerator.hpp:33:23: error: unknown type name 'BaseAST'
    void GenerateCode(BaseAST*);
                      ^
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/IRGenerator.hpp:34:24: error: unknown type name 'string'; did you mean 'std::string'?
    void GenObjectCode(string);
                       ^~~~~~
                       std::string
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/iosfwd:249:65: note: 'std::string' declared here
typedef basic_string<char, char_traits<char>, allocator<char> > string;
                                                                ^
In file included from /Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.cpp:12:
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/IRGenerator.hpp:29:9: error: use of undeclared identifier 'delte'; did you mean 'delete'?
        delte IRBuilder;
        ^~~~~
        delete
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/IRGenerator.hpp:35:2: error: expected ';' after class
}
 ^
 ;
In file included from /Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.cpp:13:
In file included from /Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.hpp:13:
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/IRGenerator.hpp:16:7: error: redefinition of 'IRGenerator'
class IRGenerator {
      ^
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.cpp:12:10: note: '/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/IRGenerator.hpp' included multiple times, additional include site here
#include "IRGenerator.hpp"
         ^
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.hpp:13:10: note: '/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/IRGenerator.hpp' included multiple times, additional include site here
#include "IRGenerator.hpp"
         ^
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/IRGenerator.hpp:16:7: note: unguarded header; consider using #ifdef guards or #pragma once
class IRGenerator {
      ^
In file included from /Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.cpp:13:
In file included from /Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.hpp:13:
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/IRGenerator.hpp:35:2: error: expected ';' after class
}
 ^
 ;
In file included from /Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.cpp:13:
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.hpp:30:13: error: unknown type name 'string'; did you mean 'std::string'?
    VarType(string name) {
            ^~~~~~
            std::string
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/iosfwd:249:65: note: 'std::string' declared here
typedef basic_string<char, char_traits<char>, allocator<char> > string;
                                                                ^
In file included from /Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.cpp:13:
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.hpp:35:5: error: C++ requires a type specifier for all declarations
    GetType() {return type;}
    ^
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.hpp:31:21: warning: multi-character character constant [-Wmultichar]
        if (name == 'int') type = Int; 
                    ^
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.hpp:31:18: error: invalid operands to binary expression ('std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>') and 'int')
        if (name == 'int') type = Int; 
            ~~~~ ^  ~~~~~
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__variant/monostate.h:40:16: note: candidate function not viable: no known conversion from 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>') to 'std::monostate' for 1st argument
constexpr bool operator==(monostate, monostate) noexcept { return true; }
               ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/system_error:392:1: note: candidate function not viable: no known conversion from 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>') to 'const std::error_code' for 1st argument
operator==(const error_code& __x, const error_code& __y) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/system_error:399:1: note: candidate function not viable: no known conversion from 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>') to 'const std::error_code' for 1st argument
operator==(const error_code& __x, const error_condition& __y) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/system_error:407:1: note: candidate function not viable: no known conversion from 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>') to 'const std::error_condition' for 1st argument
operator==(const error_condition& __x, const error_code& __y) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/system_error:414:1: note: candidate function not viable: no known conversion from 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>') to 'const std::error_condition' for 1st argument
operator==(const error_condition& __x, const error_condition& __y) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__utility/pair.h:328:1: note: candidate template ignored: could not match 'pair' against 'basic_string'
operator==(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__iterator/reverse_iterator.h:207:1: note: candidate template ignored: could not match 'reverse_iterator' against 'basic_string'
operator==(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__memory/allocator.h:262:6: note: candidate template ignored: could not match 'allocator' against 'basic_string'
bool operator==(const allocator<_Tp>&, const allocator<_Up>&) _NOEXCEPT {return true;}
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/tuple:1521:1: note: candidate template ignored: could not match 'tuple' against 'basic_string'
operator==(const tuple<_Tp...>& __x, const tuple<_Up...>& __y)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__memory/unique_ptr.h:558:1: note: candidate template ignored: could not match 'unique_ptr' against 'basic_string'
operator==(const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y) {return __x.get() == __y.get();}
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__memory/unique_ptr.h:594:1: note: candidate template ignored: could not match 'unique_ptr' against 'basic_string'
operator==(const unique_ptr<_T1, _D1>& __x, nullptr_t) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__memory/unique_ptr.h:602:1: note: candidate template ignored: could not match 'unique_ptr<_T1, _D1>' against 'int'
operator==(nullptr_t, const unique_ptr<_T1, _D1>& __x) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__memory/shared_ptr.h:1182:1: note: candidate template ignored: could not match 'shared_ptr' against 'basic_string'
operator==(const shared_ptr<_Tp>& __x, const shared_ptr<_Up>& __y) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__memory/shared_ptr.h:1236:1: note: candidate template ignored: could not match 'shared_ptr' against 'basic_string'
operator==(const shared_ptr<_Tp>& __x, nullptr_t) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__memory/shared_ptr.h:1244:1: note: candidate template ignored: could not match 'shared_ptr<_Tp>' against 'int'
operator==(nullptr_t, const shared_ptr<_Tp>& __x) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/variant:1625:16: note: candidate template ignored: could not match 'variant' against 'basic_string'
constexpr bool operator==(const variant<_Types...>& __lhs,
               ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__iterator/istream_iterator.h:86:1: note: candidate template ignored: could not match 'istream_iterator' against 'basic_string'
operator==(const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __x,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__iterator/istreambuf_iterator.h:105:6: note: candidate template ignored: could not match 'istreambuf_iterator' against 'basic_string'
bool operator==(const istreambuf_iterator<_CharT,_Traits>& __a,
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__iterator/move_iterator.h:228:6: note: candidate template ignored: could not match 'move_iterator' against 'basic_string'
bool operator==(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__iterator/wrap_iter.h:156:6: note: candidate template ignored: could not match '__wrap_iter' against 'basic_string'
bool operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__iterator/wrap_iter.h:163:6: note: candidate template ignored: could not match '__wrap_iter' against 'basic_string'
bool operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/optional:1205:1: note: candidate template ignored: could not match 'optional' against 'basic_string'
operator==(const optional<_Tp>& __x, const optional<_Up>& __y)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/optional:1298:1: note: candidate template ignored: could not match 'optional' against 'basic_string'
operator==(const optional<_Tp>& __x, nullopt_t) noexcept
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/optional:1306:1: note: candidate template ignored: could not match 'optional<_Tp>' against 'int'
operator==(nullopt_t, const optional<_Tp>& __x) noexcept
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/optional:1399:1: note: candidate template ignored: could not match 'optional' against 'basic_string'
operator==(const optional<_Tp>& __x, const _Up& __v)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/optional:1411:1: note: candidate template ignored: could not match 'optional<_Up>' against 'int'
operator==(const _Tp& __v, const optional<_Up>& __x)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__ios/fpos.h:67:6: note: candidate template ignored: could not match 'fpos' against 'basic_string'
bool operator==(const fpos<_StateT>& __x, const fpos<_StateT>& __y) {
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/array:393:1: note: candidate template ignored: could not match 'array' against 'basic_string'
operator==(const array<_Tp, _Size>& __x, const array<_Tp, _Size>& __y)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/unordered_map:1890:1: note: candidate template ignored: could not match 'unordered_map' against 'basic_string'
operator==(const unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>& __x,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/unordered_map:2596:1: note: candidate template ignored: could not match 'unordered_multimap' against 'basic_string'
operator==(const unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>& __x,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/vector:3230:1: note: candidate template ignored: could not match 'vector' against 'basic_string'
operator==(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__functional/function.h:1230:1: note: candidate template ignored: could not match 'function' against 'basic_string'
operator==(const function<_Rp(_ArgTypes...)>& __f, nullptr_t) _NOEXCEPT {return !__f;}
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__functional/function.h:1235:1: note: candidate template ignored: could not match 'function<_Rp (_ArgTypes...)>' against 'int'
operator==(nullptr_t, const function<_Rp(_ArgTypes...)>& __f) _NOEXCEPT {return !__f;}
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/string_view:755:6: note: candidate template ignored: could not match 'basic_string_view' against 'basic_string'
bool operator==(basic_string_view<_CharT, _Traits> __lhs,
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/string_view:766:6: note: candidate template ignored: could not match 'basic_string_view' against 'basic_string'
bool operator==(basic_string_view<_CharT, _Traits> __lhs,
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/string_view:775:6: note: candidate template ignored: could not match 'basic_string_view<_CharT, _Traits>' against 'int'
bool operator==(typename common_type<basic_string_view<_CharT, _Traits> >::type __lhs,
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/string:4149:1: note: candidate template ignored: could not match 'basic_string<_CharT, _Traits, _Allocator>' against 'int'
operator==(const basic_string<_CharT, _Traits, _Allocator>& __lhs,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/string:4161:1: note: candidate template ignored: could not match 'basic_string<char, char_traits<char>, _Allocator>' against 'int'
operator==(const basic_string<char, char_traits<char>, _Allocator>& __lhs,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/string:4180:1: note: candidate template ignored: could not match 'const _CharT *' against 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>')
operator==(const _CharT* __lhs,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/string:4193:1: note: candidate template ignored: could not match 'const _CharT *' against 'int'
operator==(const basic_string<_CharT,_Traits,_Allocator>& __lhs,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/set:977:1: note: candidate template ignored: could not match 'set' against 'basic_string'
operator==(const set<_Key, _Compare, _Allocator>& __x,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/set:1509:1: note: candidate template ignored: could not match 'multiset' against 'basic_string'
operator==(const multiset<_Key, _Compare, _Allocator>& __x,
^
In file included from /Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.cpp:13:
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.hpp:32:23: error: invalid operands to binary expression ('std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>') and 'int')
        else if (name == 'char') type = Char; 
                 ~~~~ ^  ~~~~~~
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__variant/monostate.h:40:16: note: candidate function not viable: no known conversion from 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>') to 'std::monostate' for 1st argument
constexpr bool operator==(monostate, monostate) noexcept { return true; }
               ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/system_error:392:1: note: candidate function not viable: no known conversion from 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>') to 'const std::error_code' for 1st argument
operator==(const error_code& __x, const error_code& __y) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/system_error:399:1: note: candidate function not viable: no known conversion from 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>') to 'const std::error_code' for 1st argument
operator==(const error_code& __x, const error_condition& __y) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/system_error:407:1: note: candidate function not viable: no known conversion from 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>') to 'const std::error_condition' for 1st argument
operator==(const error_condition& __x, const error_code& __y) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/system_error:414:1: note: candidate function not viable: no known conversion from 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>') to 'const std::error_condition' for 1st argument
operator==(const error_condition& __x, const error_condition& __y) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__utility/pair.h:328:1: note: candidate template ignored: could not match 'pair' against 'basic_string'
operator==(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__iterator/reverse_iterator.h:207:1: note: candidate template ignored: could not match 'reverse_iterator' against 'basic_string'
operator==(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__memory/allocator.h:262:6: note: candidate template ignored: could not match 'allocator' against 'basic_string'
bool operator==(const allocator<_Tp>&, const allocator<_Up>&) _NOEXCEPT {return true;}
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/tuple:1521:1: note: candidate template ignored: could not match 'tuple' against 'basic_string'
operator==(const tuple<_Tp...>& __x, const tuple<_Up...>& __y)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__memory/unique_ptr.h:558:1: note: candidate template ignored: could not match 'unique_ptr' against 'basic_string'
operator==(const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y) {return __x.get() == __y.get();}
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__memory/unique_ptr.h:594:1: note: candidate template ignored: could not match 'unique_ptr' against 'basic_string'
operator==(const unique_ptr<_T1, _D1>& __x, nullptr_t) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__memory/unique_ptr.h:602:1: note: candidate template ignored: could not match 'unique_ptr<_T1, _D1>' against 'int'
operator==(nullptr_t, const unique_ptr<_T1, _D1>& __x) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__memory/shared_ptr.h:1182:1: note: candidate template ignored: could not match 'shared_ptr' against 'basic_string'
operator==(const shared_ptr<_Tp>& __x, const shared_ptr<_Up>& __y) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__memory/shared_ptr.h:1236:1: note: candidate template ignored: could not match 'shared_ptr' against 'basic_string'
operator==(const shared_ptr<_Tp>& __x, nullptr_t) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__memory/shared_ptr.h:1244:1: note: candidate template ignored: could not match 'shared_ptr<_Tp>' against 'int'
operator==(nullptr_t, const shared_ptr<_Tp>& __x) _NOEXCEPT
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/variant:1625:16: note: candidate template ignored: could not match 'variant' against 'basic_string'
constexpr bool operator==(const variant<_Types...>& __lhs,
               ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__iterator/istream_iterator.h:86:1: note: candidate template ignored: could not match 'istream_iterator' against 'basic_string'
operator==(const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __x,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__iterator/istreambuf_iterator.h:105:6: note: candidate template ignored: could not match 'istreambuf_iterator' against 'basic_string'
bool operator==(const istreambuf_iterator<_CharT,_Traits>& __a,
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__iterator/move_iterator.h:228:6: note: candidate template ignored: could not match 'move_iterator' against 'basic_string'
bool operator==(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__iterator/wrap_iter.h:156:6: note: candidate template ignored: could not match '__wrap_iter' against 'basic_string'
bool operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) _NOEXCEPT
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__iterator/wrap_iter.h:163:6: note: candidate template ignored: could not match '__wrap_iter' against 'basic_string'
bool operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/optional:1205:1: note: candidate template ignored: could not match 'optional' against 'basic_string'
operator==(const optional<_Tp>& __x, const optional<_Up>& __y)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/optional:1298:1: note: candidate template ignored: could not match 'optional' against 'basic_string'
operator==(const optional<_Tp>& __x, nullopt_t) noexcept
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/optional:1306:1: note: candidate template ignored: could not match 'optional<_Tp>' against 'int'
operator==(nullopt_t, const optional<_Tp>& __x) noexcept
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/optional:1399:1: note: candidate template ignored: could not match 'optional' against 'basic_string'
operator==(const optional<_Tp>& __x, const _Up& __v)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/optional:1411:1: note: candidate template ignored: could not match 'optional<_Up>' against 'int'
operator==(const _Tp& __v, const optional<_Up>& __x)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__ios/fpos.h:67:6: note: candidate template ignored: could not match 'fpos' against 'basic_string'
bool operator==(const fpos<_StateT>& __x, const fpos<_StateT>& __y) {
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/array:393:1: note: candidate template ignored: could not match 'array' against 'basic_string'
operator==(const array<_Tp, _Size>& __x, const array<_Tp, _Size>& __y)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/unordered_map:1890:1: note: candidate template ignored: could not match 'unordered_map' against 'basic_string'
operator==(const unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>& __x,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/unordered_map:2596:1: note: candidate template ignored: could not match 'unordered_multimap' against 'basic_string'
operator==(const unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>& __x,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/vector:3230:1: note: candidate template ignored: could not match 'vector' against 'basic_string'
operator==(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__functional/function.h:1230:1: note: candidate template ignored: could not match 'function' against 'basic_string'
operator==(const function<_Rp(_ArgTypes...)>& __f, nullptr_t) _NOEXCEPT {return !__f;}
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/__functional/function.h:1235:1: note: candidate template ignored: could not match 'function<_Rp (_ArgTypes...)>' against 'int'
operator==(nullptr_t, const function<_Rp(_ArgTypes...)>& __f) _NOEXCEPT {return !__f;}
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/string_view:755:6: note: candidate template ignored: could not match 'basic_string_view' against 'basic_string'
bool operator==(basic_string_view<_CharT, _Traits> __lhs,
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/string_view:766:6: note: candidate template ignored: could not match 'basic_string_view' against 'basic_string'
bool operator==(basic_string_view<_CharT, _Traits> __lhs,
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/string_view:775:6: note: candidate template ignored: could not match 'basic_string_view<_CharT, _Traits>' against 'int'
bool operator==(typename common_type<basic_string_view<_CharT, _Traits> >::type __lhs,
     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/string:4149:1: note: candidate template ignored: could not match 'basic_string<_CharT, _Traits, _Allocator>' against 'int'
operator==(const basic_string<_CharT, _Traits, _Allocator>& __lhs,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/string:4161:1: note: candidate template ignored: could not match 'basic_string<char, char_traits<char>, _Allocator>' against 'int'
operator==(const basic_string<char, char_traits<char>, _Allocator>& __lhs,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/string:4180:1: note: candidate template ignored: could not match 'const _CharT *' against 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>')
operator==(const _CharT* __lhs,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/string:4193:1: note: candidate template ignored: could not match 'const _CharT *' against 'int'
operator==(const basic_string<_CharT,_Traits,_Allocator>& __lhs,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/set:977:1: note: candidate template ignored: could not match 'set' against 'basic_string'
operator==(const set<_Key, _Compare, _Allocator>& __x,
^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/set:1509:1: note: candidate template ignored: could not match 'multiset' against 'basic_string'
operator==(const multiset<_Key, _Compare, _Allocator>& __x,
^
In file included from /Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.cpp:13:
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.hpp:38:2: error: expected ';' after class
}
 ^
 ;
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.hpp:64:5: error: unknown type name 'string'; did you mean 'std::string'?
    string funcname; 
    ^~~~~~
    std::string
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/include/c++/v1/iosfwd:249:65: note: 'std::string' declared here
typedef basic_string<char, char_traits<char>, allocator<char> > string;
                                                                ^
In file included from /Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.cpp:13:
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.hpp:66:23: error: expected ';' at end of declaration list
    BlockAST* blockast
                      ^
                      ;
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.hpp:84:2: error: expected ';' after class
}
 ^
 ;
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.hpp:93:2: error: expected ';' after class
}
 ^
 ;
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.hpp:104:2: error: expected ';' after class
}
 ^
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.cpp:24:78: warning: implicit conversion of NULL constant to 'bool' [-Wnull-conversion]
    llvm::FunctionType* FuncType = llvm::FunctionType::get(ReturnType, NULL, NULL);
                                   ~~~~                                      ^~~~
                                                                             false
/Users/wangzijun/Documents/GitHub/Compiler/simple_demo/AST.cpp:26:28: error: no matching function for call to 'Create'
    llvm::Function* Func = llvm::Function::Create(FuncType, NULL, this->funcname, IRContext.Module);
                           ^~~~~~~~~~~~~~~~~~~~~~
/Users/wangzijun/llvm-project/llvm/include/llvm/IR/Function.h:143:20: note: candidate function not viable: no known conversion from 'long' to 'llvm::GlobalValue::LinkageTypes' for 2nd argument
  static Function *Create(FunctionType *Ty, LinkageTypes Linkage,
                   ^
/Users/wangzijun/llvm-project/llvm/include/llvm/IR/Function.h:152:20: note: candidate function not viable: no known conversion from 'long' to 'llvm::GlobalValue::LinkageTypes' for 2nd argument
  static Function *Create(FunctionType *Ty, LinkageTypes Linkage,
                   ^
/Users/wangzijun/llvm-project/llvm/include/llvm/IR/Function.h:136:20: note: candidate function not viable: no known conversion from 'long' to 'llvm::GlobalValue::LinkageTypes' for 2nd argument
  static Function *Create(FunctionType *Ty, LinkageTypes Linkage,
                   ^
2 warnings and 18 errors generated.
make[2]: *** [CMakeFiles/simple_demo.dir/AST.cpp.o] Error 1
make[1]: *** [CMakeFiles/simple_demo.dir/all] Error 2
make: *** [all] Error 2