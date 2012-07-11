#include <iostream>
#include "Teuchos_RCP.hpp"
#include "basic.h"
#include "add.h"
#include "symbol.h"

using Teuchos::RCP;
using Teuchos::rcp;

using CSymPy::Basic;
using CSymPy::Add;
using CSymPy::Symbol;

void test_symbol_hash()
{
    Symbol x  = Symbol("x");
    Symbol x2 = Symbol("x");
    Symbol y  = Symbol("y");

    assert(x == x);
    assert(x == x2);
    assert(!(x == y));
    assert(x != y);

    std::hash<Basic> hash_fn;
    assert(hash_fn(x) != hash_fn(y));
    assert(hash_fn(x) == hash_fn(x2));


    std::size_t seed1 = 0;
    hash_combine<std::string>(seed1, "x");
    hash_combine<std::string>(seed1, "y");

    std::size_t seed2 = 0;
    hash_combine<Basic>(seed2, x);
    hash_combine<Basic>(seed2, y);

    assert(seed1 == seed2);
}

typedef struct
{
    long operator() (const RCP<Basic> &k) const {
        return k->__hash__();
    }
} RCPBasicHash;

typedef struct
{
    bool operator() (const RCP<Basic> &x, const RCP<Basic> &y) const {
        return x->__eq__(*y);
    }
} RCPBasicKeyEq;


int main(int argc, char* argv[])
{
    test_symbol_hash();

    /*
    std::unordered_map<int, int> m;
    RCP<Add> a = rcp(new Add(m));
    */

    std::unordered_map<RCP<Basic>, int, RCPBasicHash, RCPBasicKeyEq> d;
//    Symbol x = Symbol("x");
//    RCP<Symbol> x  = rcp(new Symbol("x"));
//    RCP<Symbol> y  = rcp(new Symbol("y"));
    RCP<Basic> x  = rcp(new Symbol("x"));
    RCP<Basic> x2 = rcp(new Symbol("x"));
    std::cout << (x == x2) << std::endl;
    std::cout << (*x == *x2) << std::endl;

    d[x] = 2;

    return 0;
}
