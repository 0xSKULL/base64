#include <gtest/gtest.h>

#include <mtrp/base64.hpp>

#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>

using namespace std;
using namespace mtrp;

TEST(MtrpBase64, DeterminacyQuickCheck)
{
    srand(0);

    pair<string, string> valid_pairs[] = {
        {"", ""}, 
        {"Man", "TWFu"}, 
        {"base64", "YmFzZTY0"}, 
        {"c", "Yw"}, 
        {"cc", "Y2M"}, 
        {"cpp", "Y3Bw"}, 
        {"1234", "MTIzNA"}, 
        {"https://en.wikipedia.org/wiki/Base64", "aHR0cHM6Ly9lbi53aWtpcGVkaWEub3JnL3dpa2kvQmFzZTY0"}
    };

    vector<uint8_t> random_strings[64]; for (auto &rs : random_strings) {
        rs.resize(rand() % 10 + 10);
        generate(rs.begin(), rs.end(), rand);
    }

    for (auto const& vp : valid_pairs)
    {
        string encoded;
        string decoded;

        b64::encode(vp.first, encoded);
        bool success = b64::decode(encoded, decoded);

        EXPECT_TRUE(success);
        EXPECT_EQ(decoded, vp.first);
        EXPECT_EQ(encoded, vp.second);
    }

    for (auto const& rs : random_strings)
    {
        vector<uint8_t> encoded;
        vector<uint8_t> decoded;

        b64::encode(rs, encoded);
        bool success = b64::decode(encoded, decoded);

        EXPECT_TRUE(success);
        EXPECT_EQ(rs, decoded);
    }
}

TEST(MtrpBase64, WrongInput)
{
    string wrong_encoded[] = {
        "ABCDe", "A=B=", "AB=", "AB= ", "AB=D", "====", "A", "=", "==", 
        "&%^#%^", "!!!!", "~~~~", "    ", " "
    };

    pair<string, b64::pad> uncertain_encoded[] = {
        {"AB"  , b64::pad::MANDATORY}, 
        {"AB==", b64::pad::FORBIDDEN}, 
        {"ABC" , b64::pad::MANDATORY}, 
        {"ABC=", b64::pad::FORBIDDEN}, 
        {"ABCDAB"  , b64::pad::MANDATORY}, 
        {"ABCDAB==", b64::pad::FORBIDDEN}, 
        {"ABCDABC" , b64::pad::MANDATORY}, 
        {"ABCDABC=", b64::pad::FORBIDDEN}, 
    };

    for (auto const& we : wrong_encoded)
    {
        bool success = b64::decode(we, string());
        EXPECT_FALSE(success);
    }
    
    for (auto const& ue : uncertain_encoded)
    {
        bool success = b64::decode(ue.first, string(), ue.second);
        EXPECT_FALSE(success);
    }
}

TEST(MtrpBase64, Padding)
{
    tuple<string, string, b64::pad> padding_cases[] = {
        {"C"   , "Qw"      , b64::pad::OPTIONAL }, 
        {"C"   , "Qw=="    , b64::pad::MANDATORY}, 
        {"C"   , "Qw"      , b64::pad::FORBIDDEN}, 
        
        {"ManC", "TWFuQw"  , b64::pad::OPTIONAL }, 
        {"ManC", "TWFuQw==", b64::pad::MANDATORY}, 
        {"ManC", "TWFuQw"  , b64::pad::FORBIDDEN}, 
    };

    pair<string, size_t> various_paddings[] = {
        {"Qw=="    , 1}, 
        {"Qwe="    , 2}, 
        {"Qw"      , 1}, 
        {"Qwe"     , 2}, 
        {"ABCDQw==", 4}, 
        {"ABCDQwe=", 5}, 
        {"ABCDQw"  , 4}, 
        {"ABCDQwe" , 5}
    };

    for (auto &pc : padding_cases)
    {
        string tmp1, tmp2;
        
        string decoded = get<0>(pc);
        string encoded = get<1>(pc);
        auto pad = get<2>(pc);

        b64::encode(decoded, tmp1, pad);
        bool result = b64::decode(tmp1, tmp2, pad);

        EXPECT_TRUE(result);
        EXPECT_EQ(tmp1, encoded);
        EXPECT_EQ(tmp2, decoded);
    }

    for (auto &vp : various_paddings)
    {
        string decoded;
        bool result = b64::decode(vp.first, decoded, b64::pad::OPTIONAL);
        EXPECT_TRUE(result);
        EXPECT_EQ(decoded.size(), vp.second);
    }
}

TEST(MtrpBase64, Standard)
{
    string decoded;
    bool success;

    string encoded_classic = "+/";
    string encoded_urlsafe = "-_";
    
    success = b64::decode(encoded_classic, decoded);
    EXPECT_TRUE(success);
    EXPECT_EQ(decoded[0], '\xFB');
    
    success = b64::urlsafe::decode(encoded_urlsafe, decoded);
    EXPECT_TRUE(success);
    EXPECT_EQ(decoded[0], '\xFB');
    
    success = b64::decode(encoded_urlsafe, string());
    EXPECT_FALSE(success);
    
    success = b64::urlsafe::decode(encoded_classic, string());
    EXPECT_FALSE(success);
}
