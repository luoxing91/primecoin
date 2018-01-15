
BOOST_FIXTURE_TEST_SUITE(scriptnum_tests, BasicTestingSetup)

static const int64_t values[] = { 0, 1, -2, 127, 128, -255, 256, (1LL << 15) - 1,
                                  -(1LL << 16), (1LL << 24) - 1, (1LL << 31),
                                  1 - (1LL << 32), 1LL << 40 };

static const int64_t offsets[] = { 1, 0x79, 0x80, 0x81, 0xFF, 0x7FFF, 0x8000, 0xFFFF,
                                   0x10000};
static bool verify(const CScriptNum10& bignum, const CScriptNum& scriptnum){
    return bignum.getvch() == scriptnum.getvch() && bignum.getint() == scriptnum.getint();
}
static void CheckCreateVch(const int64_t& num){
    CScriptNum10 bignum(num);
    CScriptNum scriptnum(num);
    BOOST_CHECK(verify(bignum, scriptnum));

    CScriptNum10 bignum2(bignum.getvch(), false);
    CScriptNum scriptnum2(scriptnum.getvch(), false);
    BOOST_CHECK(verify(bignum2, scriptnum2));

    CScriptNum10 bignum3(scriptnum2.getvch(), false);
    CScriptNum scriptnum3(bignum2.getvch(), false);
    BOOST_CHECK(verify(bignum3, scriptnum3));
}

static void CheckCreateInt(const int64_t& num){
    CScriptNum10 bignum(num);
    CScriptNum scriptnum(num);
    BOOST_CHECK(verify(bignum, scriptnum));
    BOOST_CHECK(verify(CScriptNum10(bignum.getint()), CScriptNum(scriptnum.getint())));
    BOOST_CHECK(verify(CScriptNum10(scriptnum.getint()), CScriptNum(bignum.getint())));
    BOOST_CHECK(verify(CScriptNum10(CScriptNum10(scriptnum.getint()).getint()),
                       CScriptNum(CScriptNum(bignum.getint()).getint())));
}

